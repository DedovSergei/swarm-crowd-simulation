#include <swarm/cpu_crowd_sim.hpp>

#include <swarm/nav_field.hpp>
#include <swarm/sdf.hpp>

#include <glm/glm.hpp>
#include <omp.h>

#ifdef SWARM_CPU_PROFILE
#include <intrin.h>
#endif

#include <algorithm>
#include <chrono>
#include <cmath>
#include <stdexcept>
#include <string>
#include <utility>

// Numerics vs the GPU pipeline
// - The only intentional difference: map(). The GPU samples the baked SDF through hardware
//   trilinear filtering, which quantizes the weights to 8 fractional bits (up to ~h/256 = 6e-5 of
//   position near a wall). The CPU uses the exact CPU sampler (sampleSDF, full float weights).
//   The texelFetch-based functions (columnLevel, floorUnder, mapExactGrad) are exact on both.
// - Every shared constant is bit-identical, including the constant expressions the GLSL compiler
//   folds (FEELER_REACH, R_SEP * R_SEP, GRAVITY * DT, exp(-DT / TAU_RELAX), 1.0 / DT, ...): the port uses
// sim_params.hpp's folded values in their place. Enforced by test_gpu parity.constants.
// - Everything else is rounding-level arithmetic: GPU transcendentals and inversesqrt are
//   approximations (cos, sin, sqrt), and the shader compiler may fuse multiply-adds or turn
//   divisions into reciprocal multiplies. MSVC under /fp:precise does neither.
// - SortMode::Counting also sums neighbours in a different order within a cell (see the header).
// Operation order otherwise follows the shaders expression by expression.

namespace swarm {

#ifdef SWARM_CPU_PROFILE
namespace cpu_profile {
ThreadSlot slots[MAX_THREADS];
bool skipSeparation = false;
void reset() { for (ThreadSlot& s : slots) s = ThreadSlot{}; }
} // namespace cpu_profile
// Per-agent phase marks: cycles since the previous mark go to phase ph of this thread's slot
#define PROF_BEGIN() cpu_profile::ThreadSlot& profSlot = cpu_profile::slots[omp_get_thread_num()]; uint64_t profT = __rdtsc()
#define PROF_MARK(ph) do { const uint64_t profNow = __rdtsc(); profSlot.cycles[cpu_profile::ph] += profNow - profT; profT = profNow; } while (0)
#define PROF_COUNT(c, v) (profSlot.counts[cpu_profile::c] += (v))
#define PROF_COUNT_TLS(c) (cpu_profile::slots[omp_get_thread_num()].counts[cpu_profile::c]++)
#define PROF_SEPARATION_ON (!cpu_profile::skipSeparation)
#else
#define PROF_BEGIN() ((void)0)
#define PROF_MARK(ph) ((void)0)
#define PROF_COUNT(c, v) ((void)0)
#define PROF_COUNT_TLS(c) ((void)0)
#define PROF_SEPARATION_ON true
#endif

namespace {

using glm::ivec2;
using glm::ivec3;
using glm::vec2;
using glm::vec3;
using glm::vec4;

// physics.comp's slotPlanes flags
constexpr float PLANE_WALL = 1.0f, PLANE_GROUNDED = 2.0f;

// --- Uniforms, as CrowdSim::step sets them ---
const vec3 U_SDF_MIN = SDF_MIN;
const float U_SDF_INV_SPACING = 1.0f / SDF_SPACING;
const vec2 FENCE_C(FENCE_CENTER.x, FENCE_CENTER.y);
const vec2 FENCE_MID(FENCE_HALF_MID.x, FENCE_HALF_MID.y);
// Every model constant comes from sim_params.hpp, like the shaders' preamble

// GLSL built-ins and swizzle writes
inline float inversesqrt(float x) { return 1.0f / std::sqrt(x); }
inline void setXY(vec3& v, vec2 xy) { v.x = xy.x; v.y = xy.y; }
inline vec2 feelerDir(int i) { return vec2(FEELER_DIRS[size_t(i)].x, FEELER_DIRS[size_t(i)].y); }
inline vec2 feelerOffset(int i) { return vec2(FEELER_OFFSETS[size_t(i)].x, FEELER_OFFSETS[size_t(i)].y); }
inline vec2 probeOffset(int i) { return vec2(PROBE_OFFSETS[size_t(i)].x, PROBE_OFFSETS[size_t(i)].y); }

// --- calc_grid.comp (the venue's GRID_RES, DOMAIN_MIN, DOMAIN_SPAN) ---
uint32_t cellID(vec2 p, float domainMin, float domainSpan, int gridRes) {
    int x = std::clamp(int((p.x - domainMin) / domainSpan * float(gridRes)), 0, gridRes - 1);
    int y = std::clamp(int((p.y - domainMin) / domainSpan * float(gridRes)), 0, gridRes - 1);
    return uint32_t(x + y * gridRes);
}

// --- physics.comp: functions without buffer or texture access ---
vec2 safeNormalize(vec2 v) { float l = glm::length(v); return l > SAFE_NORMALIZE_EPS ? v / l : vec2(0.0f); }
vec3 safeNormalize(vec3 v) { float l = glm::length(v); return l > SAFE_NORMALIZE_EPS ? v / l : vec3(0.0f); }

// @fence block: sdBox2, sdBox2Grad, sdFence and sdFenceGradient are the CPU mirrors in sdf.cpp
// (test_gpu parity.fence_sdf checks them against the GPU block)
bool fenceCCD(vec3 pOld, vec3& pNew, vec3& vel) {   // true if the step was clamped
    float sOld = sdBox2(vec2(pOld) - FENCE_C, FENCE_MID);
    float sNew = sdBox2(vec2(pNew) - FENCE_C, FENCE_MID);
    if (sOld * sNew >= 0.0f) return false;
    float side = sOld > 0.0f ? 1.0f : -1.0f;
    float lo = 0.0f;
    if (side * sOld > FENCE_HALF_THK_COLL) {
        float hi = 1.0f;
        for (int i = 0; i < FENCE_CCD_BISECTIONS; ++i) {
            float t = 0.5f * (lo + hi);
            if (side * sdBox2(glm::mix(vec2(pOld), vec2(pNew), t) - FENCE_C, FENCE_MID) > FENCE_HALF_THK_COLL) lo = t;
            else hi = t;
        }
    }
    setXY(pNew, glm::mix(vec2(pOld), vec2(pNew), lo));
    vec2 n = vec2(sdFenceGradient(pNew));
    float vn = glm::dot(vec2(vel), n);
    if (vn < 0.0f) setXY(vel, vec2(vel) - n * vn);
    return true;
}

// @sep-kernel block
uint32_t hash32(uint32_t x) {  // lowbias32
    x ^= x >> 16; x *= 0x7feb352du;
    x ^= x >> 15; x *= 0x846ca68bu;
    x ^= x >> 16;
    return x;
}

vec2 pairDirection(uint32_t self, uint32_t other) {
    uint32_t lo = std::min(self, other);
    uint32_t hi = std::max(self, other);
    float angle = float(hash32(hash32(lo) ^ hi)) * HASH_TO_RADIANS;   // (6.28318530718 / 4294967296.0)
    vec2 dir(std::cos(angle), std::sin(angle));
    return self == lo ? dir : -dir;
}

vec2 separationForce(vec3 offset, uint32_t self, uint32_t other) {
    float d2 = glm::dot(offset, offset);
    if (d2 >= R_SEP2) return vec2(0.0f);   // R_SEP * R_SEP
    float w = 1.0f - std::sqrt(d2) / R_SEP;
    float magnitude = K_SEP * w * w;
    float dxy2 = glm::dot(vec2(offset), vec2(offset));
    if (dxy2 <= SEP_STACKED_XY2) return magnitude * pairDirection(self, other);
    return magnitude * vec2(offset) * inversesqrt(dxy2);
}

vec2 contactCorrection(vec3 offset, uint32_t self, uint32_t other) {
    float dxy2 = glm::dot(vec2(offset), vec2(offset));
    if (std::abs(offset.z) >= BODY_DIAM || dxy2 >= BODY_DIAM2) return vec2(0.0f);   // BODY_DIAM * BODY_DIAM
    float dxy = std::sqrt(dxy2);
    float shift = 0.5f * (BODY_DIAM - dxy);
    if (dxy2 <= SEP_STACKED_XY2) return shift * pairDirection(self, other);
    return shift * (vec2(offset) / dxy);
}

vec2 egressTarget(vec3 p) {
    vec2 s(p.x < 0.0f ? -1.0f : 1.0f, p.y < 0.0f ? -1.0f : 1.0f);
    vec2 a = glm::abs(vec2(p));
    bool alongX = a.y >= a.x;
    float lat = alongX ? a.x : a.y;
    float dep = alongX ? a.y : a.x;

    vec2 t;
    if (lat < AVENUE_HALF && dep >= WALKWAY_MIN) t = vec2(0.0f, AVENUE_TARGET_DEPTH);
    else if (dep >= WALKWAY_MIN && dep < WALKWAY_MAX) t = vec2(0.0f, WALKWAY_CENTRE);
    else if (dep >= WALKWAY_MAX && lat < AISLE_MAX) t = vec2(AISLE_CENTRE, WALKWAY_CENTRE);
    else if (dep >= WALKWAY_MAX) t = vec2(AISLE_CENTRE, dep);
    else t = vec2(0.0f, PITCH_RECOVERY_DEPTH);   // WALKWAY_MIN + PITCH_RECOVERY_MARGIN

    return alongX ? s * t : s * vec2(t.y, t.x);
}

// physics.comp goalDirection (production branch): the unit direction to the egress waypoint, 0 within GOAL_DEADZONE
vec2 egressDirection(vec3 p) {
    vec2 toTarget = egressTarget(p) - vec2(p);
    return glm::length(toTarget) > GOAL_DEADZONE ? safeNormalize(toTarget) : vec2(0.0f);
}

float rootStep(vec4& br, float t, vec4 g, vec3 u) {   // br = (a, f(a), b, f(b))
    if (g.w > 0.0f) { br.x = t; br.y = g.w; } else { br.z = t; br.w = g.w; }
    float du = glm::dot(vec3(g), u);
    float tn = du < 0.0f ? t - g.w / du : -1.0f;
    return tn > br.x && tn < br.z ? tn : (br.x * br.w - br.z * br.y) / (br.w - br.y);
}

float newtonStep(float t, vec4 g, vec3 u) {
    float du = glm::dot(vec3(g), u);
    return du < 0.0f ? t - g.w / du : t;
}

// physics.comp's buffers and SDF texture, with its functions that read them as members
struct Physics {
    const std::vector<float>& sdf;
    const float* texels;   // sdf.data(): raw reads, unchecked in Debug builds too (hot path)
    const GpuBoid* boidsIn;     // agent order, start of step
    const GpuGridInfo* gridInfo;
    const GpuCellData* cells;
    GpuBoid* boidsOut;          // agent order, end of step (final pass)
    uint8_t* contacts;
    uint32_t numBoids;
    const GpuBoid* slotIn;      // slot order: the previous projection iteration (project, final)
    GpuBoid* slotOut;           // slot order: the predicted state (predict), the next iteration (project)
    vec4* planes;               // slot order: the predict pass's wall plane and grounded flag (physics.comp slotPlanes)
    // The venue: its neighbour grid and exit test (the preamble's GRID_RES, DOMAIN_*, EXIT_*), a seated venue's
    // layout (VENUE_ANALYTIC; nullptr: the baked terrace), and the forced-motion table (TEST_DRIVE_TABLE; nullptr: none)
    const SeatedLayout* seated;
    int gridRes;
    float domainMax, exitDepth, exitMaxZ;
    const vec2* drive;
    const nav::Field* navField;   // a seated venue's navigation field (VENUE_NAV_FIELD); nullptr: the terrace
    const nav::ChoiceTable* choice;   // queue-aware exit choice (VENUE_EXIT_CHOICE): the candidate table; nullptr: none
    const uint32_t* assign;           // and the assigned exit per agent
    bool inclineSpeed;                // the incline speed (VENUE_INCLINE_SPEED; seated venues)
    bool stairHeadway;                // the stair spacing (VENUE_STAIR_HEADWAY; with the incline speed)
    vec2 stairT;                      // its time gaps on a full-slope incline, {ascending, descending} (T_HEADWAY_STAIR_UP / _DOWN)

    // physics.comp goalDirection: TEST_DRIVE_TABLE, the navigation field (VENUE_NAV_FIELD: seated venues; VENUE_EXIT_CHOICE:
    // the assigned exit's field), else the egress route
    vec2 goalDirection(vec3 p, uint32_t id) const {
        if (drive) return drive[id];
        if (choice) return nav::choiceGoal(*choice, *seated, p, assign[id]);   // physics.comp navChoiceGoal
        if (navField) return nav::goal(*navField, *seated, p);   // physics.comp navGoal
        return egressDirection(p);
    }

    // texelFetch(u_sdfTexture, ivec3(z, y, x), 0): the texture's s axis is the file's z
    float texel(int x, int y, int z) const { return texels[(size_t(x) * SDF_RES + y) * SDF_RES + z]; }

    // @sdf block
    // THE intentional numeric difference: the GPU's map() is hardware-filtered (8-bit weights),
    // this is the exact CPU sampler
    float map(vec3 p) const {
        PROF_COUNT_TLS(MAP_CALLS);
        if (seated) return seated::sdf(*seated, p);   // VENUE_ANALYTIC: venueMap
        return sampleSDF(sdf, p);
    }

    float columnLevel(ivec2 i0, vec2 w, int k) const {
        k = std::clamp(k, 0, SDF_RES - 1);
        float c0 = glm::mix(texel(i0.x, i0.y, k), texel(i0.x + 1, i0.y, k), w.x);
        float c1 = glm::mix(texel(i0.x, i0.y + 1, k), texel(i0.x + 1, i0.y + 1, k), w.x);
        return glm::mix(c0, c1, w.y);
    }

    vec4 mapExactGrad(vec3 p) const {
        PROF_COUNT_TLS(EXACT_GRAD_CALLS);
        if (seated) return seated::sdfGrad(*seated, p);   // VENUE_ANALYTIC: venueMapGrad
        vec3 f = 1.0f + (p - U_SDF_MIN) * U_SDF_INV_SPACING;
        bool outside = glm::any(glm::lessThan(f, vec3(-0.5f))) || glm::any(glm::greaterThan(f, vec3(float(SDF_RES) - 0.5f)));
        ivec3 i = glm::clamp(ivec3(glm::floor(f)), ivec3(0), ivec3(SDF_RES - 2));
        vec3 w = f - vec3(i);
        // c<x><y><z>
        float c000 = texel(i.x,     i.y,     i.z);
        float c100 = texel(i.x + 1, i.y,     i.z);
        float c010 = texel(i.x,     i.y + 1, i.z);
        float c110 = texel(i.x + 1, i.y + 1, i.z);
        float c001 = texel(i.x,     i.y,     i.z + 1);
        float c101 = texel(i.x + 1, i.y,     i.z + 1);
        float c011 = texel(i.x,     i.y + 1, i.z + 1);
        float c111 = texel(i.x + 1, i.y + 1, i.z + 1);
        float x00 = glm::mix(c000, c100, w.x), x10 = glm::mix(c010, c110, w.x);
        float x01 = glm::mix(c001, c101, w.x), x11 = glm::mix(c011, c111, w.x);
        float y0 = glm::mix(x00, x10, w.y), y1 = glm::mix(x01, x11, w.y);
        vec3 g(glm::mix(glm::mix(c100 - c000, c110 - c010, w.y), glm::mix(c101 - c001, c111 - c011, w.y), w.z),
               glm::mix(x10 - x00, x11 - x01, w.z),
               y1 - y0);
        return outside ? vec4(0.0f, 0.0f, 0.0f, 1.0f) : vec4(g * U_SDF_INV_SPACING, glm::mix(y0, y1, w.z));
    }

    bool floorUnderReach(vec3 c, float zFrom, float down, float& zFloor) const {
        zFloor = 0.0f;
        if (seated) {   // VENUE_ANALYTIC: the heightfield's floor
            const float h = seated::floorHeight(*seated, vec2(c));
            zFloor = h;
            if (c.z <= h) return h <= std::max(zFrom, c.z) + BODY_RADIUS;
            return h >= c.z - down;
        }
        vec3 f = 1.0f + (c - U_SDF_MIN) * U_SDF_INV_SPACING;
        if (glm::any(glm::lessThan(vec2(f), vec2(0.0f))) || glm::any(glm::greaterThan(vec2(f), vec2(float(SDF_RES) - 1.0f)))) return false;
        ivec2 i0 = glm::min(ivec2(glm::floor(vec2(f))), ivec2(SDF_RES - 2));
        vec2 w = vec2(f) - vec2(i0);
        int k = int(std::floor(f.z));
        float vLo = columnLevel(i0, w, k), vHi = columnLevel(i0, w, k + 1);
        bool inSolid = glm::mix(vLo, vHi, f.z - float(k)) <= 0.0f;
        float fLimit = f.z + (inSolid ? std::max(zFrom, c.z) + BODY_RADIUS - c.z : -down) * U_SDF_INV_SPACING;
        for (int cell = 0; cell < FLOOR_SEARCH_CELLS; ++cell) {
            float fEnd = inSolid ? std::min(float(k + 1), fLimit) : std::max(float(k), fLimit);
            float vEnd = glm::mix(vLo, vHi, fEnd - float(k));
            if (inSolid ? vEnd > 0.0f : vEnd <= 0.0f) {
                float fRoot = float(k) + vLo / (vLo - vHi);
                zFloor = U_SDF_MIN.z + (fRoot - 1.0f) / U_SDF_INV_SPACING;
                return true;
            }
            if (fEnd == fLimit) return false;
            if (inSolid) { ++k; vLo = vHi; vHi = columnLevel(i0, w, k + 1); }
            else         { --k; vHi = vLo; vLo = columnLevel(i0, w, k); }
        }
        return false;
    }

    bool floorUnder(vec3 c, float zFrom, float& zFloor) const { return floorUnderReach(c, zFrom, BODY_RADIUS, zFloor); }

    vec3 calcGradient(vec3 p) const {
        const vec3 kxyy(1.0f, -1.0f, -1.0f), kyyx(-1.0f, -1.0f, 1.0f), kyxy(-1.0f, 1.0f, -1.0f), kxxx(1.0f, 1.0f, 1.0f);  // k = vec2(1, -1)
        return (kxyy * map(p + kxyy * OBSTACLE_GRAD_H) +
                kyyx * map(p + kyyx * OBSTACLE_GRAD_H) +
                kyxy * map(p + kyxy * OBSTACLE_GRAD_H) +
                kxxx * map(p + kxxx * OBSTACLE_GRAD_H)) * OBSTACLE_GRAD_SCALE;   // (0.25 / OBSTACLE_GRAD_H)
    }

    vec3 calcNormal(vec3 p) const { return safeNormalize(calcGradient(p)); }

    float sceneDist(vec3 p, bool& fenceActive) const {
        float dStadium = map(p);
        float dFence = sdFence(p) + BODY_RADIUS;
        fenceActive = dFence < dStadium;
        return fenceActive ? dFence : dStadium;
    }

    vec3 sceneNormal(vec3 p, bool fenceActive) const {
        return fenceActive ? sdFenceGradient(p) : calcNormal(p);
    }

    bool restOnFloor(vec3& np, vec3& nv, float zFrom) const {   // true if it lifted the centre
        float zFloor;
        if (floorUnder(np, zFrom, zFloor) && np.z < zFloor + BODY_RADIUS) {
            np.z = zFloor + BODY_RADIUS;
            nv.z = 0.0f;
            return true;
        }
        return false;
    }

    bool settleOnFloor(vec3& np, vec3& nv, float zFrom) const {   // true if it found the floor
        float zFloor;
        if (floorUnderReach(np, zFrom, FLOOR_SETTLE_REACH, zFloor)) {
            np.z = zFloor + BODY_RADIUS;
            nv.z = 0.0f;
            return true;
        }
        return false;
    }

    float wallContact(vec3 np, float fc, vec3 u, float fr, float reach, vec2& away) const {
        vec4 br(0.0f, fc, reach, fr);
        float t = reach * fc / (fc - fr);
        vec4 g(0.0f);
        for (int i = 0; i < WALL_ROOT_STEPS; ++i) {
            g = mapExactGrad(np + u * t);
            t = rootStep(br, t, g, u);
        }
        bool wall = g.z <= WALL_MAX_NZ * glm::length(vec3(g));
        float e = wall ? t : 1e9f;
        away = -vec2(u);

        vec2 n = safeNormalize(vec2(g));
        vec3 u2(-n, 0.0f);
        float t2 = 0.0f, t3 = t * glm::dot(u, u2);   // t2: last Newton start, t3: last Newton result
        vec4 g2(0.0f);
        for (int i = 0; i < WALL_RECAST_STEPS; ++i) {
            t2 = t3;
            g2 = mapExactGrad(np + u2 * t2);
            t3 = newtonStep(t2, g2, u2);
        }
        bool ok = wall && glm::dot(vec3(g2), u2) < 0.0f && std::abs(t3 - t2) < WALL_RECAST_TOL && t3 > 0.0f &&
                  g2.z <= WALL_MAX_NZ * glm::length(vec3(g2));
        if (ok && t3 < e) { e = t3; away = n; }
        return e;
    }

    bool clearWalls(vec3& np, vec3& nv, vec3& wall) const {   // wall: physics.comp clearWalls
        bool moved = false;
        wall = vec3(0.0f);
        if (seated) {   // VENUE_ANALYTIC: the exact wall query (seated::wall, the GLSL venueWall)
            for (int pass = 0; pass < WALL_PASSES; ++pass) {
                const vec3 w = seated::wall(*seated, np + vec3(0.0f, 0.0f, seated->wallAbove), FEELER_REACH);   // walls reach the body's top
                if (w.z >= seated->wallClear) {   // BODY_RADIUS + faceMargin (VS_WALL_CLEAR)
                    if (w.z < seated::WALL_NONE) wall = vec3(vec2(w), w.z - seated->wallClear);
                    break;
                }
                setXY(np, vec2(np) + vec2(w) * (seated->wallClear - w.z));
                moved = true;
                wall = vec3(vec2(w), 0.0f);
                const float vDotN = glm::dot(vec2(nv), vec2(w));
                if (vDotN < 0.0f) setXY(nv, vec2(nv) - vec2(w) * vDotN);
            }
            return moved;
        }
        for (int pass = 0; pass < WALL_PASSES; ++pass) {
            bool nearFence = sdFence(np) < FEELER_REACH;
            float fc = map(np);
            float fr1 = 0.0f, fr2 = 0.0f;
            int i1 = -1, i2 = -1;
            for (int i = 0; i < FEELER_COUNT; ++i) {
                vec3 f = np + vec3(feelerOffset(i), 0.0f);
                float v = map(f);
                if (nearFence && sdFence(f) < 0.0f) v = 1.0f;
                if (v < fr1)      { fr2 = fr1; i2 = i1; fr1 = v; i1 = i; }
                else if (v < fr2) { fr2 = v; i2 = i; }
            }
            if (i1 < 0) break;
            vec2 hNorm;
            float clearance;
            if (fc > 0.0f) {
                clearance = wallContact(np, fc, vec3(feelerDir(i1), 0.0f), fr1, FEELER_REACH, hNorm);
                if (i2 >= 0) {
                    vec2 h2;
                    float c2 = wallContact(np, fc, vec3(feelerDir(i2), 0.0f), fr2, FEELER_REACH, h2);
                    if (c2 < clearance) { clearance = c2; hNorm = h2; }
                }
            } else {
                vec4 g = mapExactGrad(np);
                hNorm = safeNormalize(vec2(g));
                clearance = g.w / std::max(glm::length(vec2(g)), CENTRE_GRAD_MIN);
            }
            if (clearance >= BODY_RADIUS) {
                if (clearance < 1e9f) wall = vec3(hNorm, clearance - BODY_RADIUS);
                break;
            }
            setXY(np, vec2(np) + hNorm * (BODY_RADIUS - clearance));
            moved = true;
            wall = vec3(hNorm, 0.0f);
            float vDotN = glm::dot(vec2(nv), hNorm);
            if (vDotN < 0.0f) setXY(nv, vec2(nv) - hNorm * vDotN);
        }
        return moved;
    }

    vec3 wallPlaneProbe(vec3 np) const {   // physics.comp wallPlaneProbe
        if (seated) {   // VENUE_ANALYTIC: the exact wall query
            const vec3 w = seated::wall(*seated, np + vec3(0.0f, 0.0f, seated->wallAbove), PLANE_PROBE_REACH);
            return w.z >= 0.0f && w.z < seated::WALL_NONE ? vec3(vec2(w), std::max(w.z - seated->wallClear, 0.0f)) : vec3(0.0f);
        }
        bool nearFence = sdFence(np) < PLANE_PROBE_REACH;
        float fc = map(np);
        float fr = 0.0f;
        int i1 = -1;
        for (int i = 0; i < FEELER_COUNT; ++i) {
            vec3 f = np + vec3(probeOffset(i), 0.0f);
            float v = map(f);
            if (nearFence && sdFence(f) < 0.0f) v = 1.0f;
            if (v < fr) { fr = v; i1 = i; }
        }
        if (i1 < 0 || fc <= 0.0f) return vec3(0.0f);
        vec2 away;
        float c = wallContact(np, fc, vec3(feelerDir(i1), 0.0f), fr, PLANE_PROBE_REACH, away);
        return c < 1e9f ? vec3(away, std::max(c - BODY_RADIUS, 0.0f)) : vec3(0.0f);
    }

    bool bakedSolid(vec3 p) const { return sdFence(p) >= 0.0f && mapExactGrad(p).w <= 0.0f; }

    bool sweepBack(vec3 pOld, vec3& np, vec3& nv) const {   // physics.comp sweepBack: true if it moved the centre
        if (!bakedSolid(np)) return false;
        float lo = 0.0f, hi = 1.0f;
        if (!bakedSolid(vec3(vec2(np), pOld.z))) lo = 1.0f;
        for (int i = 0; i < STATIC_SWEEP_BISECTIONS; ++i) {
            float t = 0.5f * (lo + hi);
            if (bakedSolid(vec3(glm::mix(vec2(pOld), vec2(np), t), pOld.z))) hi = t;
            else lo = t;
        }
        vec2 d = safeNormalize(vec2(np) - vec2(pOld));
        np = vec3(glm::mix(vec2(pOld), vec2(np), lo), pOld.z);
        float vd = glm::dot(vec2(nv), d);
        if (vd > 0.0f) setXY(nv, vec2(nv) - d * vd);
        nv.z = 0.0f;
        return true;
    }

    // physics.comp resolveStatic: the static contacts of a centre that moved from pOld to np in this step;
    // returns whether it is grounded, wallN: the last wall push's normal. Contact bits into 'contact'.
    bool resolveStatic(vec3 pOld, vec3& np, vec3& nv, bool settle, vec3& wall, uint8_t& contact) const {
        PROF_BEGIN();
        if (fenceCCD(pOld, np, nv)) contact |= CpuCrowdSim::CONTACT_FENCE_CCD;
        float dFence = sdFence(np);
        if (dFence < 0.0f) {
            vec2 n = vec2(sdFenceGradient(np));
            setXY(np, vec2(np) - n * dFence);
            float vDotN = glm::dot(vec2(nv), n);
            if (vDotN < 0.0f) setXY(nv, vec2(nv) - n * vDotN);
            contact |= CpuCrowdSim::CONTACT_FENCE;
        }
        PROF_MARK(FENCE);
        bool grounded = settle ? settleOnFloor(np, nv, pOld.z) : restOnFloor(np, nv, pOld.z);
        if (!grounded && sweepBack(pOld, np, nv)) {
            contact |= CpuCrowdSim::CONTACT_SWEEP;
            grounded = restOnFloor(np, nv, pOld.z);
        }
        if (grounded) contact |= CpuCrowdSim::CONTACT_FLOOR;
        PROF_MARK(FLOOR);
        const bool walls = clearWalls(np, nv, wall);
        PROF_MARK(WALLS);
        if (walls) {
            contact |= CpuCrowdSim::CONTACT_WALL;
            if (grounded) {
                if (settleOnFloor(np, nv, pOld.z)) contact |= CpuCrowdSim::CONTACT_FLOOR;
                vec3 w2;
                const bool again = clearWalls(np, nv, w2);
                if (vec2(w2) != vec2(0.0f)) wall = w2;
                if (again && restOnFloor(np, nv, pOld.z)) contact |= CpuCrowdSim::CONTACT_FLOOR;
            } else if (restOnFloor(np, nv, pOld.z)) {
                contact |= CpuCrowdSim::CONTACT_FLOOR;
            }
        }
        PROF_MARK(FLOOR);
        return grounded;
    }

    // physics.comp stepUpWindow: 0 free down to the window's bottom, 1 floor in the window (g there), 2 solid
    // at the window's top
    int stepUpWindow(vec2 xy, float f0, vec4& g) const {
        g = vec4(0.0f, 0.0f, 1.0f, 0.0f);
        vec3 f = 1.0f + (vec3(xy, f0) - U_SDF_MIN) * U_SDF_INV_SPACING;
        if (glm::any(glm::lessThan(vec2(f), vec2(0.0f))) || glm::any(glm::greaterThan(vec2(f), vec2(float(SDF_RES) - 1.0f)))) return 0;
        ivec2 i0 = glm::min(ivec2(glm::floor(vec2(f))), ivec2(SDF_RES - 2));
        vec2 w = vec2(f) - vec2(i0);
        float fLo = f.z + STEP_UP_TOL * U_SDF_INV_SPACING, fHi = f.z + MAX_STEP_UP * U_SDF_INV_SPACING;
        int k = int(std::floor(fHi));
        float a = columnLevel(i0, w, k), b = columnLevel(i0, w, k + 1);
        if (glm::mix(a, b, fHi - float(k)) <= 0.0f) {
            g = mapExactGrad(vec3(xy, U_SDF_MIN.z + (fHi - 1.0f) / U_SDF_INV_SPACING));
            return 2;
        }
        for (int cell = 0; cell < 2; ++cell) {
            float fBot = std::max(float(k), fLo);
            if (glm::mix(a, b, fBot - float(k)) <= 0.0f) {
                float fRoot = float(k) + a / (a - b);
                g = mapExactGrad(vec3(xy, U_SDF_MIN.z + (fRoot - 1.0f) / U_SDF_INV_SPACING));
                return 1;
            }
            if (fBot == fLo) return 0;
            --k; b = a; a = columnLevel(i0, w, k);
        }
        return 0;
    }

    static bool stepUpBlocked(int r, vec4 g, vec2 dir, bool end) {   // physics.comp stepUpBlocked
        if (r == 2) return end;
        return r == 1 && glm::dot(vec2(g), dir) < 0.0f && g.z <= WALL_MAX_NZ * glm::length(vec3(g));
    }

    // physics.comp venueStepUpScan (VENUE_ANALYTIC): the step-up scan over the path's cell boundaries (the port is
    // seated::stepUpScan, shared with the navigation field's edges)
    float venueStepUpScan(vec2 p0, vec2 p1, float f0, vec2& n) const { return seated::stepUpScan(*seated, p0, p1, f0, n); }

    float stepUpScan(vec2 p0, vec2 p1, float f0, vec2& n) const {   // physics.comp stepUpScan
        n = vec2(0.0f);
        vec2 d = p1 - p0;
        float len = glm::length(d);
        vec2 dir = len > 0.0f ? d / len : vec2(0.0f);
        int ns = std::clamp(int(std::ceil(len / STEP_UP_SAMPLE)), 1, STEP_UP_MAX_SAMPLES);   // STEP_UP_SAMPLE_RADII * BODY_RADIUS
        int lastOk = 0;
        bool blocked = false;
        for (int i = 1; i <= ns; ++i) {
            vec4 g;
            int r = stepUpWindow(glm::mix(p0, p1, float(i) / float(ns)), f0, g);
            if (stepUpBlocked(r, g, dir, i == ns)) { blocked = true; n = safeNormalize(vec2(g)); break; }
            if (r != 2) lastOk = i;
        }
        if (!blocked) return 1.0f;
        float lo = float(lastOk) / float(ns), hi = float(lastOk + 1) / float(ns);
        for (int i = 0; i < STEP_UP_BISECTIONS; ++i) {
            float t = 0.5f * (lo + hi);
            vec4 g;
            int r = stepUpWindow(glm::mix(p0, p1, t), f0, g);
            if (stepUpBlocked(r, g, dir, true)) { hi = t; n = safeNormalize(vec2(g)); }
            else lo = t;
        }
        return lo;
    }

    // physics.comp limitStepUp: true if it blocked the move
    bool limitStepUp(vec3 pOld, vec3& np, vec3& nv) const {
        float f0;
        if (!floorUnderReach(pOld, pOld.z, STEP_UP_FLOOR_REACH, f0)) f0 = pOld.z - STEP_UP_FLOOR_REACH;   // STEP_UP_FLOOR_REACH_RADII * BODY_RADIUS
        vec2 n;
        float t = seated ? venueStepUpScan(vec2(pOld), vec2(np), f0, n) : stepUpScan(vec2(pOld), vec2(np), f0, n);
        if (t >= 1.0f) {
            if (seated) venueEdgeMargin(pOld, f0, np, nv);
            return false;
        }
        vec2 q = glm::mix(vec2(pOld), vec2(np), t);
        vec2 rest = vec2(np) - q;
        vec2 tangent = rest - n * glm::dot(rest, n);
        float lt = glm::length(tangent);
        if (lt > 0.0f) {
            for (int k = 0; k < STEP_UP_SLIDE_TRIES; ++k) {
                vec2 slide = q + tangent * STEP_UP_SLIDE_DIRS[size_t(k)].x + n * (lt * STEP_UP_SLIDE_DIRS[size_t(k)].y);
                vec2 n2;
                if (sdFence(vec3(slide, 0.0f)) >= 0.0f && (seated ? venueStepUpScan(q, slide, f0, n2) : stepUpScan(q, slide, f0, n2)) >= 1.0f) { q = slide; break; }
            }
        }
        float vn = glm::dot(vec2(nv), n);
        if (vn < 0.0f) setXY(nv, vec2(nv) - n * vn);
        float zFloor;
        if (floorUnderReach(vec3(q, pOld.z), pOld.z, FLOOR_SETTLE_REACH, zFloor)) {
            np = vec3(q, zFloor + BODY_RADIUS);
            nv.z = 0.0f;
        } else {
            np = vec3(q, std::min(np.z, pOld.z));
        }
        if (seated) {
            venueBlockedWall(f0, pOld, np, nv);
            venueEdgeMargin(pOld, f0, np, nv);
        }
        return true;
    }

    // physics.comp venueBlockedWall (VENUE_ANALYTIC): a blocked move's point (the face, the slide along it) may lie in a
    // wall's clearance band; the exact wall contact there, kept only if the push climbs no face
    void venueBlockedWall(float f0, vec3 pOld, vec3& np, vec3& nv) const {
        const vec3 w = seated::wall(*seated, np + vec3(0.0f, 0.0f, seated->wallAbove), FEELER_REACH);
        if (w.z >= seated->wallClear) return;
        const vec2 pushed = vec2(np) + vec2(w) * (seated->wallClear - w.z);
        vec2 n;
        if (venueStepUpScan(vec2(np), pushed, f0, n) < 1.0f) return;
        const float vDotN = glm::dot(vec2(nv), vec2(w));
        if (vDotN < 0.0f) setXY(nv, vec2(nv) - vec2(w) * vDotN);
        float zFloor;
        if (floorUnderReach(vec3(pushed, pOld.z), pOld.z, FLOOR_SETTLE_REACH, zFloor)) {
            np = vec3(pushed, zFloor + BODY_RADIUS);
            nv.z = 0.0f;
        } else {
            setXY(np, pushed);
        }
    }

    // physics.comp venueEdgeMargin (VENUE_ANALYTIC), the end of limitStepUp on a seated venue: every centre VS_FACE_MARGIN off
    // the side face of a column higher than its feet; standing on such a column's edge: onto it unless that climbs; lifted
    // this step and left over a lower floor: settled from the start-of-step height; airborne: off the face, still falling
    void venueEdgeMargin(vec3 pOld, float f0, vec3& np, vec3& nv) const {
        const float margin = seated->faceMargin;
        float feet = np.z - BODY_RADIUS;
        const float fl = seated::floorHeight(*seated, vec2(np));
        if (feet > fl + margin) {
            const vec3 w = seated::wall(*seated, vec3(vec2(np), fl + STEP_UP_TOL), margin);
            if (w.z < margin) {
                const vec2 into = vec2(np) - vec2(w) * (w.z + margin);
                const float top = seated::floorHeight(*seated, into);
                if (std::abs(top - feet) <= margin && top <= f0 + STEP_UP_TOL) { setXY(np, into); return; }
            }
            if (np.z <= pOld.z) {   // airborne: off the face of a column higher than its feet, still falling
                const vec3 wa = seated::wall(*seated, vec3(vec2(np), feet + STEP_UP_TOL), margin);
                if (wa.z < margin) setXY(np, vec2(np) + vec2(wa) * (margin - wa.z));
                return;
            }
            float zFloor;
            if (!floorUnderReach(vec3(vec2(np), pOld.z), pOld.z, FLOOR_SETTLE_REACH, zFloor)) { np.z = pOld.z; return; }
            np.z = zFloor + BODY_RADIUS;
            nv.z = 0.0f;
            feet = zFloor;
        }
        const vec3 w = seated::wall(*seated, vec3(vec2(np), feet + STEP_UP_TOL), margin);
        if (w.z >= margin) return;
        setXY(np, vec2(np) + vec2(w) * (margin - w.z));
        np.z = seated::floorHeight(*seated, vec2(np)) + BODY_RADIUS;
    }

    // physics.comp PHYSICS_PASS 1 (predict) for one sorted slot: desired velocity + driving term + integration -> slotOut[slot].
    // The TEST_DRIVE_DIR / TEST_NO_GOAL / DISABLE_FENCE_CCD / DISABLE_STEP_UP_LIMIT variants exist only for test_gpu's GPU
    // scenarios and are not ported.
    void predict(uint32_t slot) const {
        if (slot >= numBoids) return;
        PROF_BEGIN();
        PROF_COUNT(AGENTS, 1);

        uint32_t self = gridInfo[slot].boidID;
        uint32_t cid = gridInfo[slot].gridID;
        uint8_t& contact = contacts[self];
        contact = 0;

        if (cid == INACTIVE_CELL) {   // the final pass carries it over
            PROF_MARK(OTHER);
            return;
        }
        vec4 p = boidsIn[self].position;
        vec4 v = boidsIn[self].velocity;

        vec2 ap = glm::abs(vec2(p));
        if ((std::max(ap.x, ap.y) > exitDepth && p.z < exitMaxZ) || std::max(ap.x, ap.y) > domainMax) {
            slotOut[slot].position = vec4(vec3(PARK_COORD), 0.0f);
            slotOut[slot].velocity = vec4(0.0f);
            contact = CpuCrowdSim::CONTACT_EXIT;
            PROF_MARK(OTHER);
            return;
        }

        // Desired direction e_goal: the egress route's waypoint
        vec2 eGoal = goalDirection(vec3(p), self);

        PROF_MARK(OTHER);
        int cx = int(cid % uint32_t(gridRes));
        int cy = int(cid / uint32_t(gridRes));

        vec2 sep(0.0f);
        float sAhead = 1e9f;   // horizontal centre distance to the nearest agent ahead (1e9: none within R_PERC)
        int cnt = 0;

        for (int y = -PERC_RING; y <= PERC_RING; y++) {
            for (int x = -PERC_RING; x <= PERC_RING; x++) {
                int nx = cx + x;
                int ny = cy + y;
                if (nx < 0 || nx >= gridRes || ny < 0 || ny >= gridRes) continue;
                GpuCellData cell = cells[nx + ny * gridRes];
                PROF_COUNT(CANDIDATES, cell.agentCount);
                for (uint32_t k = cell.startIndex; k < cell.startIndex + cell.agentCount; k++) {
                    if (k == slot) continue;
                    uint32_t other = gridInfo[k].boidID;
                    vec4 op = boidsIn[other].position;
                    vec3 offset = vec3(p) - vec3(op);   // from the other agent to this one
                    float dxy2 = glm::dot(vec2(offset), vec2(offset));

                    if (dxy2 < R_PERC2) {   // R_PERC * R_PERC
                        cnt++;
                        PROF_COUNT(SEP_PAIRS, glm::dot(offset, offset) < R_SEP2);
                        if (PROF_SEPARATION_ON) sep += separationForce(offset, self, other);
                        float ahead = -glm::dot(vec2(offset), eGoal);                        // along the path
                        float lateral = std::abs(offset.x * eGoal.y - offset.y * eGoal.x);   // off the path
                        float dxy = std::sqrt(dxy2);
                        if (ahead > 0.0f && lateral < BODY_DIAM && dxy < sAhead) {
                            // Mutual standoff: only the agent that has the other more directly ahead yields
                            vec2 eOther = goalDirection(vec3(op), other);
                            float aheadOther = glm::dot(vec2(offset), eOther);
                            bool mutual = aheadOther > 0.0f && std::abs(offset.x * eOther.y - offset.y * eOther.x) < BODY_DIAM;
                            if (!mutual || ahead > aheadOther || (ahead == aheadOther && self > other)) sAhead = dxy;
                        }
                    }
                }
            }
        }

        // Headway speed rule, none without a goal direction; desired direction: e_goal deflected by
        // the personal-space repulsion
        // The free speed, on an incline the stair speed by the slope along e_goal (physics.comp inclineFreeSpeed)
        const float slope = inclineSpeed ? seated::floorSlope(*seated, vec2(p), eGoal) : 0.0f;
        const float vFree = inclineSpeed ? seated::inclineFreeSpeed(slope) : V_MAX;
        // On an incline the stair spacing's time gap by the slope (physics.comp inclineHeadwayTime; level floors: the level rule)
        float vDes = (stairHeadway && slope != 0.0f
                          ? std::clamp((sAhead - BODY_DIAM) / seated::inclineHeadwayTime(slope, stairT.x, stairT.y), 0.0f, vFree)
                          : std::clamp((sAhead - BODY_DIAM) * HEADWAY_RATE, 0.0f, vFree)) * glm::length(eGoal);   // (1.0 / T_HEADWAY)
        vec2 eDir = safeNormalize(eGoal + sep);
        PROF_COUNT(NEIGHBOURS, cnt);
        PROF_MARK(NEIGHBOUR);

        // Obstacle avoidance, an acceleration, at torso height
        vec2 aObs(0.0f);
        vec3 torsoPos = vec3(p) + vec3(0.0f, 0.0f, TORSO_HEIGHT);
        bool torsoOnFence;
        float dTorso = sceneDist(torsoPos, torsoOnFence);
        if (dTorso < OBSTACLE_RANGE) {
            vec2 norm = vec2(sceneNormal(torsoPos, torsoOnFence));
            if (glm::length(norm) > OBSTACLE_MIN_NORMAL) {
                aObs = safeNormalize(norm) * (OBSTACLE_RANGE - dTorso) * W_OBS * OBSTACLE_GAIN;
            }
        }

        PROF_MARK(OBSTACLE);

        // Kinematics: the driving term (velocity relaxation), exact over the step for constant inputs, then the
        // headway speed as an upper bound along e_goal
        vec2 vEq = eDir * vDes + aObs * TAU_RELAX;
        vec3 nv = vec3(v);
        setXY(nv, vEq + (vec2(nv) - vEq) * RELAX_STEP);   // exp(-DT / TAU_RELAX)
        float along = glm::dot(vec2(nv), eGoal);
        if (along > vDes) setXY(nv, vec2(nv) - eGoal * (along - vDes));
        nv.z -= GRAVITY_DT;   // GRAVITY * DT
        nv.z = std::min(nv.z, 0.0f);                 // Prevent upward self-propulsion

        if (glm::length(vec2(nv)) > V_MAX) {
            setXY(nv, safeNormalize(vec2(nv)) * V_MAX);
        }

        vec3 np = vec3(p) + nv * DT;
        PROF_MARK(STEER);

        // Static contacts of the predicted step; the wall plane and the grounded flag bound the projection
        vec3 wall;
        const bool grounded = resolveStatic(vec3(p), np, nv, false, wall, contact);
        if (vec2(wall) == vec2(0.0f)) wall = wallPlaneProbe(np);
        slotOut[slot].position = vec4(np, 1.0f);
        slotOut[slot].velocity = vec4(nv, 0.0f);   // w: the projection's displacement so far
        const vec2 wn(wall);
        planes[slot] = vec4(wn, glm::dot(vec2(np), wn) - wall.z, (wn != vec2(0.0f) ? PLANE_WALL : 0.0f) + (grounded ? PLANE_GROUNDED : 0.0f));
    }

    // physics.comp projectSlot: one Jacobi iteration of the hard-body projection for one sorted slot,
    // reading slotIn (the previous iteration), in the GPU's neighbour order
    GpuBoid projectSlot(uint32_t slot, uint32_t self, uint32_t cid) const {
        GpuBoid b = slotIn[slot];
        if (b.position.w == 0.0f) return b;   // parked this step
        int cx = int(cid % uint32_t(gridRes));
        int cy = int(cid / uint32_t(gridRes));
        vec2 corr(0.0f);
        int nContacts = 0;
        for (int y = -1; y <= 1; y++) {
            for (int x = -1; x <= 1; x++) {
                int nx = cx + x;
                int ny = cy + y;
                if (nx < 0 || nx >= gridRes || ny < 0 || ny >= gridRes) continue;
                GpuCellData cell = cells[nx + ny * gridRes];
                for (uint32_t k = cell.startIndex; k < cell.startIndex + cell.agentCount; k++) {
                    if (k == slot) continue;
                    vec4 op = slotIn[k].position;
                    vec3 offset = vec3(b.position) - vec3(op);
                    if (op.w != 0.0f && std::abs(offset.z) < BODY_DIAM && glm::dot(vec2(offset), vec2(offset)) < BODY_DIAM2) {   // BODY_DIAM * BODY_DIAM
                        corr += contactCorrection(offset, self, gridInfo[k].boidID);
                        ++nContacts;
                    }
                }
            }
        }
        corr *= PROJ_RELAX / float(std::max(nContacts, 1));
        float len = glm::length(corr);
        if (len > PROJ_MAX_SHIFT) corr *= PROJ_MAX_SHIFT / len;
        vec3 q = vec3(b.position);
        setXY(q, vec2(q) + corr);
        float dFence = sdFence(q);
        if (dFence < 0.0f) setXY(q, vec2(q) - vec2(sdFenceGradient(q)) * dFence);
        const vec4 plane = planes[slot];
        if (std::fmod(plane.w, 2.0f) == PLANE_WALL) {
            float s = plane.z - glm::dot(vec2(q), vec2(plane));
            if (s > 0.0f) setXY(q, vec2(q) + vec2(plane) * s);
        }
        const vec2 d = vec2(q) - vec2(b.position);
        if (d != vec2(0.0f)) contacts[self] |= CpuCrowdSim::CONTACT_AGENT;
        b.position.x = q.x; b.position.y = q.y;
        b.velocity.w += glm::length(d);
        return b;
    }

    // physics.comp PHYSICS_PASS 2 (project): slotIn -> slotOut
    void project(uint32_t slot) const {
        if (slot >= numBoids) return;
        PROF_BEGIN();
        uint32_t cid = gridInfo[slot].gridID;
        if (cid != INACTIVE_CELL) slotOut[slot] = projectSlot(slot, gridInfo[slot].boidID, cid);
        PROF_MARK(PROJECT);
    }

    // physics.comp PHYSICS_PASS 3 (final): the last projection iteration, the final static
    // contacts of every agent the projection moved; writes boidsOut[boidID]
    void finalPass(uint32_t slot, bool projectHere) const {
        if (slot >= numBoids) return;
        PROF_BEGIN();
        uint32_t self = gridInfo[slot].boidID;
        uint32_t cid = gridInfo[slot].gridID;

        if (cid == INACTIVE_CELL) {
            boidsOut[self] = boidsIn[self];
            PROF_MARK(OTHER);
            return;
        }
        const GpuBoid b = projectHere ? projectSlot(slot, self, cid) : slotIn[slot];
        PROF_MARK(PROJECT);
        if (b.position.w == 0.0f) {   // parked this step
            boidsOut[self] = b;
            PROF_MARK(OTHER);
            return;
        }
        vec3 np = vec3(b.position);
        vec3 nv = vec3(b.velocity);

        const vec3 pOld(boidsIn[self].position);
        if (b.velocity.w > 0.0f) {   // the projection moved it: the final static contacts
            vec3 wall;
            resolveStatic(pOld, np, nv, planes[slot].w >= PLANE_GROUNDED, wall, contacts[self]);
        }
        if (limitStepUp(pOld, np, nv)) contacts[self] |= CpuCrowdSim::CONTACT_STEP_UP;   // every agent, last

        boidsOut[self].position = vec4(np, 1.0f);
        boidsOut[self].velocity = vec4(nv, glm::length(nv));
        PROF_MARK(FLOOR);
    }
};

double msBetween(std::chrono::steady_clock::time_point a, std::chrono::steady_clock::time_point b) {
    return std::chrono::duration<double, std::milli>(b - a).count();
}

// body(i) for i in [0, n) on 'threads' OpenMP threads under schedule s. OpenMP 2.0 (MSVC /openmp)
// has no omp_set_schedule, so each schedule is its own loop.
template <class Body>
void parallelFor(CpuCrowdSim::Schedule s, int threads, int n, const Body& body) {
    using S = CpuCrowdSim::Schedule;
    switch (s) {
    case S::Static: {
#pragma omp parallel for schedule(static) num_threads(threads)
        for (int i = 0; i < n; ++i) body(i);
        break;
    }
    case S::Dynamic64: {
#pragma omp parallel for schedule(dynamic, 64) num_threads(threads)
        for (int i = 0; i < n; ++i) body(i);
        break;
    }
    case S::Dynamic256: {
#pragma omp parallel for schedule(dynamic, 256) num_threads(threads)
        for (int i = 0; i < n; ++i) body(i);
        break;
    }
    case S::Dynamic1024: {
#pragma omp parallel for schedule(dynamic, 1024) num_threads(threads)
        for (int i = 0; i < n; ++i) body(i);
        break;
    }
    case S::Guided: {
#pragma omp parallel for schedule(guided) num_threads(threads)
        for (int i = 0; i < n; ++i) body(i);
        break;
    }
    }
}

} // namespace

CpuCrowdSim::CpuCrowdSim(std::vector<float> sdfVolume, int numThreads, SortMode sortMode)
    : CpuCrowdSim(terraceVenue(), std::move(sdfVolume), numThreads, sortMode) {}

CpuCrowdSim::CpuCrowdSim(const Venue& venue, std::vector<float> sdfVolume, int numThreads, SortMode sortMode)
    : CpuCrowdSim(venue, defaultModelOptions(venue), std::move(sdfVolume), numThreads, sortMode) {}

CpuCrowdSim::CpuCrowdSim(const Venue& venue, const ModelOptions& options, std::vector<float> sdfVolume, int numThreads, SortMode sortMode)
    : venue_(&venue), options_(effectiveModelOptions(venue, options)), sdf_(std::move(sdfVolume)),
      threads_(numThreads > 0 ? numThreads : maxThreads()), sortMode_(sortMode),
      cells_(size_t(venue.gridRes) * venue.gridRes), bucketStart_(size_t(venue.gridRes) * venue.gridRes + 2) {
    if (!venue.seated() && sdf_.size() != SDF_VOXELS)
        throw std::invalid_argument("CpuCrowdSim: SDF volume has " + std::to_string(sdf_.size()) + " samples, expected " +
                                    std::to_string(SDF_VOXELS));
    if (venue.seated()) sdf_.clear();   // the analytic venue samples no volume
    if (nav::hasField(venue)) navField_ = &nav::forVenue(venue);   // e_goal from the navigation field
    if (options_.exitChoice == ExitChoice::QueueAware) choice_ = &nav::choiceForVenue(venue);
}

int CpuCrowdSim::maxThreads() { return omp_get_max_threads(); }

void CpuCrowdSim::setNumThreads(int numThreads) { threads_ = numThreads > 0 ? numThreads : maxThreads(); }

const char* CpuCrowdSim::scheduleName(Schedule s) {
    switch (s) {
    case Schedule::Static: return "static";
    case Schedule::Dynamic64: return "dynamic64";
    case Schedule::Dynamic256: return "dynamic256";
    case Schedule::Dynamic1024: return "dynamic1024";
    case Schedule::Guided: return "guided";
    }
    return "?";
}

void CpuCrowdSim::setState(const std::vector<GpuBoid>& boids) {
    const size_t n = boids.size();
    if (n == 0 || n > size_t(INT32_MAX))
        throw std::invalid_argument("CpuCrowdSim::setState: agent count " + std::to_string(n) + " out of range");
    if (sortMode_ == SortMode::GpuBitonic && (n & (n - 1)) != 0)
        throw std::invalid_argument("CpuCrowdSim::setState: GpuBitonic needs a power-of-two agent count, got " + std::to_string(n));
    boids_[0] = boids;
    boids_[1] = boids;
    grid_.assign(n, GpuGridInfo{});
    gridScratch_.assign(n, GpuGridInfo{});
    slotA_.assign(n, GpuBoid{});
    planes_.assign(n, glm::vec4(0.0f));
    slotB_.assign(n, GpuBoid{});
    contacts_.assign(n, 0);
    if (choice_) choiceState_.reset(n);   // a fresh exit choice (CrowdSim::upload)
}

void CpuCrowdSim::restoreAgentState(const std::vector<GpuBoid>& boids) {
    if (boids.size() != boids_[0].size())
        throw std::invalid_argument("CpuCrowdSim::restoreAgentState: expected " + std::to_string(boids_[0].size()) + " agents, got " +
                                    std::to_string(boids.size()));
    boids_[0] = boids;
    boids_[1] = boids;
}

void CpuCrowdSim::step() {
    if (boids_[0].empty()) throw std::logic_error("CpuCrowdSim::step: no state (call setState first)");
    using Clock = std::chrono::steady_clock;
    const Clock::time_point t0 = Clock::now();
    hash();
    const Clock::time_point t1 = Clock::now();
    if (sortMode_ == SortMode::Counting) sortCounting(); else sortBitonic();
    const Clock::time_point t2 = Clock::now();
    buildCells();
    const Clock::time_point t3 = Clock::now();
    physics();
    const Clock::time_point t4 = Clock::now();
    times_ = { msBetween(t0, t1), msBetween(t1, t2), msBetween(t2, t3), msBetween(t3, t4), msBetween(t0, t4), choiceMs_, predictMs_, projectMs_, finalMs_ };
}

// calc_grid.comp. Also clears a NaN position in the input state, as the shader does.
void CpuCrowdSim::hash() {
    GpuBoid* boids = boids_[readIdx_].data();
    GpuGridInfo* grid = grid_.data();
    const float domainMin = venue_->domainMin, domainSpan = venue_->domainSpan;
    const int gridRes = venue_->gridRes;
    parallelFor(Schedule::Static, threads_, numBoids(), [boids, grid, domainMin, domainSpan, gridRes](int id) {
        if (std::isnan(boids[id].position.x)) boids[id].position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        const glm::vec4 p = boids[id].position;
        grid[id] = { p.w == 0.0f ? INACTIVE_CELL : cellID(glm::vec2(p), domainMin, domainSpan, gridRes), uint32_t(id), 0u, 0u };
    });
}

// Stable counting sort of the hash output (boidID order) into GRID_RES^2 cell buckets plus one
// bucket for INACTIVE_CELL after them
void CpuCrowdSim::sortCounting() {
    const uint32_t inactiveBucket = uint32_t(venue_->gridRes * venue_->gridRes);
    auto bucketOf = [inactiveBucket](uint32_t g) { return g == INACTIVE_CELL ? inactiveBucket : g; };
    const int n = numBoids();
    std::fill(bucketStart_.begin(), bucketStart_.end(), 0u);
    for (int i = 0; i < n; ++i) ++bucketStart_[bucketOf(grid_[i].gridID) + 1];
    for (size_t b = 1; b < bucketStart_.size(); ++b) bucketStart_[b] += bucketStart_[b - 1];
    for (int i = 0; i < n; ++i) gridScratch_[bucketStart_[bucketOf(grid_[i].gridID)]++] = grid_[i];
    std::swap(grid_, gridScratch_);
}

// bitonic_sort.comp: the same compare-exchange network, pass by pass. Each pass writes disjoint
// pairs (only the lower index of a pair acts), and the loop's implicit barrier orders the passes.
// The GPU runs the passes j < 512 in shared memory (bitonic_sort_shared.comp), in the
// same order per element: the same network, so the same permutation.
void CpuCrowdSim::sortBitonic() {
    GpuGridInfo* g = grid_.data();
    const int n = numBoids();
#pragma omp parallel num_threads(threads_)
    for (int k = 2; k <= n; k <<= 1) {
        for (int j = k >> 1; j > 0; j >>= 1) {
#pragma omp for schedule(static)
            for (int id = 0; id < n; ++id) {
                const int ixj = id ^ j;
                if (ixj > id) {
                    const bool asc = (id & k) == 0;
                    const uint32_t gi = g[id].gridID, gj = g[ixj].gridID;
                    if ((asc && gi > gj) || (!asc && gi < gj)) std::swap(g[id], g[ixj]);
                }
            }
        }
    }
}

// reorder.comp: each cell's run [startIndex, startIndex + agentCount) in the sorted pairs. Its gather
// of the agent state into slot order is a GPU memory layout only and is not ported:
// physics below reads the same values from boids[read] by boidID.
void CpuCrowdSim::buildCells() {
    std::fill(cells_.begin(), cells_.end(), GpuCellData{});
    const int n = numBoids();
    for (int id = 0; id < n; ++id) {
        const uint32_t g = grid_[id].gridID;
        if (g == INACTIVE_CELL) continue;
        ++cells_[g].agentCount;
        if (id == 0 || g != grid_[id - 1].gridID) cells_[g].startIndex = uint32_t(id);
    }
}

// physics.comp's three passes, one parallel loop each over the sorted slots, in the GPU's
// order: predict into slotA_, PROJ_ITERATIONS - 1 projection iterations ping-ponging slotA_ / slotB_, the
// final pass (last iteration + static contacts) boids[read] -> boids[write]; then swap
// physics.comp PHYSICS_PASS 0 (queue-aware): every active agent's exit for this step from the start-of-step state, and its
// count for the next step: nav::choiceStep (the GPU's atomics give the same integers)
void CpuCrowdSim::chooseExits() {
    if (!choice_) return;
    nav::choiceStep(*choice_, boids_[readIdx_], choiceState_, choiceSteps(DT), parallelChoice_ ? threads_ : 1);   // physics.comp CHOICE_STEPS = max(1, int(T_CHOICE / DT + 0.5))
}

void CpuCrowdSim::physics() {
    if (drive_ && drive_->size() != boids_[0].size()) throw std::logic_error("CpuCrowdSim: the drive table must have one entry per agent");
    using Clock = std::chrono::steady_clock;
    const Clock::time_point c0 = Clock::now();
    chooseExits();   // queue-aware only
    const Clock::time_point c1 = Clock::now();
    Physics phys{ sdf_, sdf_.data(), boids_[readIdx_].data(), grid_.data(), cells_.data(), boids_[writeIdx_].data(),
                  contacts_.data(), uint32_t(numBoids()), nullptr, slotA_.data(), planes_.data(),
                  venue_->seated() ? &venue_->layout : nullptr, venue_->gridRes, venue_->domainMax(), venue_->exitDepth, venue_->exitMaxZ,
                  drive_ ? drive_->data() : nullptr, navField_, choice_, choice_ ? choiceState_.assign.data() : nullptr,
                  options_.inclineSpeed && venue_->seated(), options_.stairFlow != StairFlow::Off && venue_->seated(),
                  stairHeadwayTimes(options_.stairFlow) };
    parallelFor(schedule_, threads_, numBoids(), [&phys](int slot) { phys.predict(uint32_t(slot)); });
    const Clock::time_point c2 = Clock::now();
    GpuBoid* in = slotA_.data();
    GpuBoid* out = slotB_.data();
    for (int it = 1; it < projIterations_; ++it) {
        phys.slotIn = in;
        phys.slotOut = out;
        parallelFor(projSchedule_, threads_, numBoids(), [&phys](int slot) { phys.project(uint32_t(slot)); });
        std::swap(in, out);
    }
    const Clock::time_point c3 = Clock::now();
    phys.slotIn = in;
    phys.slotOut = nullptr;
    const bool projectInFinal = projIterations_ > 0;
    parallelFor(schedule_, threads_, numBoids(), [&phys, projectInFinal](int slot) { phys.finalPass(uint32_t(slot), projectInFinal); });
    std::swap(readIdx_, writeIdx_);
    const Clock::time_point c4 = Clock::now();
    choiceMs_ = msBetween(c0, c1);
    predictMs_ = msBetween(c1, c2);
    projectMs_ = msBetween(c2, c3);
    finalMs_ = msBetween(c3, c4);
}

void CpuCrowdSim::setProjectionIterations(int iterations) {
    if (iterations < 0) throw std::invalid_argument("CpuCrowdSim::setProjectionIterations: iterations must be >= 0");
    projIterations_ = iterations;
}

} // namespace swarm
