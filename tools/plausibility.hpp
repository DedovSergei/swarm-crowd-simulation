#pragma once

// Plausibility of the hard-body model, checked after every step of a full evacuation: the permanent
// test_gpu validation.plausibility_terrace and the calibration's constraint (tools/fd). Readbacks every step: test and tool code only.
//   - hard bodies: overlap depth of every pair closer than BODY_DIAM (3D), in units of BODY_DIAM, split into crowd and
//     venue-geometry cases; the crowd cases within CROWD_P99_LIMIT / CROWD_MAX_LIMIT, the venue-geometry cases as well
// except in the baked terrace reference venue (below);
//   - neighbour grid: no pair ends a step closer than BODY_DIAM unless its start-of-step cells are 3x3 neighbours,
//     and no agent moves more than (cell - BODY_DIAM) / 2 horizontally in a step (the bound that guarantees it);
//   - floors: the centre is in free space and at least BODY_RADIUS - FLOOR_TOL above the floor under it (the point
//     BODY_RADIUS - FLOOR_TOL below the centre is free); airborne runs (bottom more than FLOOR_TOL above the floor)
//     are counted for the report;
//   - fence: no agent changes side of the fence midline or ends inside the collision band;
//   - walls: no wall surface (normal n_z <= WALL_MAX_NZ - 0.1, reaching a body diameter above the hit, or the
//     fence's visual face) within BODY_RADIUS - WALL_TOL of the centre in its horizontal plane (16 directions; a
//     hit is located by bisection, its normal from central differences; walkable slopes and the low lips at the
//     tread fronts are the floor contact's and are not walls);
//   - speed: |v_xy| <= V_MAX;
//   - density: the peak cloud-in-cell density of every fully walkable 1 m cell <= DENSITY_CEILING_P_M2.

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <swarm/crowd_sim.hpp>
#include <swarm/gpu_types.hpp>
#include <swarm/metrics.hpp>
#include <swarm/sdf.hpp>
#include <swarm/sim_params.hpp>
#include <swarm/venue_capacity.hpp>

#include "scene.hpp"
#include "stepup.hpp"

#include <algorithm>
#include <functional>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>

namespace swarm::plausibility {

constexpr float FLOOR_TOL = 1e-4f;   // the rest-height tolerance of test_gpu physics.rest_height
// Wall clearance tolerance: 3e-4 (5% of BODY_RADIUS; test_gpu physics.wall_hold's driven-wall scenarios use 1e-4).
// clearWalls places a centre BODY_RADIUS from the foot point its feeler root-finding reaches; at a curved corner that
// point lies up to ~1.6e-4 farther than the true nearest surface (measured: one agent-step at 6.245e-3 in the
// N = 4096 evacuation), which this checker's dense ring finds
constexpr float WALL_TOL = 3e-4f;
constexpr int RING_DIRS = 16;
// Wall test margin: physics.comp classifies a contact by n_z at its own root-found contact point (exact gradient), this
// checker at its ray hit (central differences); on the steep fillets at a wall's foot (n_z 0.5-0.6) the two can differ,
// so a surface counts as a wall here only below WALL_MAX_NZ - WALL_NZ_MARGIN
constexpr float WALL_NZ_MARGIN = 0.1f;
constexpr double PI = 3.14159265358979323846;
// Hexagonal packing of BODY_RADIUS_M disks: the densest any floor can hold (7.22 persons/m^2)
const double HEX_PACKING_P_M2 = venue::HEX_PACKING_P_M2;
// The ceiling: disks covering the floor completely, 1 / (pi r^2) = 7.96 persons/m^2, i.e. hexagonal packing + 10.3%.
// The allowance absorbs the cloud-in-cell estimate (a 2 x 2 m tent window: lattice alignment and the finite window
// let a packing read above its mean density) and the residual overlaps the projection leaves (crowd cases: p99 <= 5% of
// BODY_DIAM, below).
const double DENSITY_CEILING_P_M2 = 1.0 / (PI * double(BODY_RADIUS_M) * double(BODY_RADIUS_M));
constexpr double OVERLAP_NOISE = 1e-4;   // depths below 1e-4 BODY_DIAM (1.3e-6, float rounding of a resolved contact)
// Overlap populations. A pair-step
// is a venue-geometry case if (FALL) either agent is airborne now or was within the last AIRBORNE_MEMORY steps, or stepped
// down within them (a fall off a tread front, a step-down into an aisle, the drop after a lift onto a riser ramp, the
// landing), or else (RAMP, the baked terrace only) either agent's floor point lies on a ramp of the baked floor (floor normal n_z < RAMP_NZ: the
// one-voxel riser ramps at the tread backs, the aisle's steep sub-steps; tread tops have n_z > 0.99, the aisle slope blends
// 0.82-0.96). Otherwise it is a CROWD case: both agents steadily grounded on walkable floor.
// A step-down is a step whose floor dropped (by more than FLOOR_TOL) along a horizontal path that crosses a
// wall-steep surface (n_z <= WALL_MAX_NZ, sampled every STEP_UP_SAMPLE): a descent of a step face, the mirror of the
// step-up limit's climb. The floor settle keeps a centre grounded
// down to FLOOR_SETTLE_REACH (0.29 m) below it, so under an airborne-only rule step-downs off the bake's riser ramps and the aisle's
// steep bottom step would count as crowd cases. Walking down a walkable slope (the aisle) is not a step-down. Result::crowdLegacyStats keeps
// the airborne-only classification for comparison.
constexpr int AIRBORNE_MEMORY = 5;
constexpr float RAMP_NZ = 0.8f;
enum OverlapCase { CASE_CROWD, CASE_FALL, CASE_RAMP, CASE_COUNT };
inline const char* caseName(int c) { return c == CASE_CROWD ? "crowd" : c == CASE_FALL ? "fall / step-down / landing" : "riser / step ramp"; }
// The pair's zone (its first agent's position; the router layout of sim_params.hpp, as metrics::sampleZone without the
// exit zone)
enum PairZone { PZ_TREAD, PZ_AISLE, PZ_WALKWAY, PZ_AVENUE, PZ_PITCH, PZ_COUNT };
inline const char* pairZoneName(int z) {
    static const char* names[PZ_COUNT] = { "tread", "aisle", "walkway", "avenue", "pitch" };
    return names[z];
}

// Overlap limits, depth in units of BODY_DIAM = 2 BODY_RADIUS (0.40 m) over every
// overlapping pair-step of the run (nearest-rank p99, and the maximum):
//   CROWD cases: p99 <= CROWD_P99_LIMIT (5%: 2 cm) and max <= CROWD_MAX_LIMIT (20%: 8 cm). The 0.40 m disk is the body's
//   envelope at shoulder width, not an incompressible core: under crowd pressure soft tissue, clothing and posture let two
// bodies come a few centimetres closer than their envelopes (not yet checked against the literature). Stricter targets (p99 < 2%,
// max < 10%) are beyond the Jacobi projection: crowd p99 0.035 and max 0.160 at K = 32 (results/validation/level_calibration),
// and more iterations do not move the tail.
//   Venue-geometry cases (FALL, RAMP): reported in full, and exempt from the limits ONLY in the baked terrace reference
// venue (VenueKind::BakedTerrace, stadium.sdf): its bake turns every tread riser into a one-voxel ramp that
//   lifts agents and pushes them off the tread's back, and its bare treads let agents fall onto the row below, landing
// among that row's agents. Analytic venues (VenueKind::Analytic) must meet the crowd limits for ALL
//   cases, with no exemption.
constexpr double CROWD_P99_LIMIT = 0.05, CROWD_MAX_LIMIT = 0.20;
enum class VenueKind { BakedTerrace, Analytic };
inline const char* venueKindName(VenueKind v) { return v == VenueKind::BakedTerrace ? "baked terrace reference venue" : "analytic venue"; }

// Order statistics of a set of overlap depths (nearest-rank percentiles)
struct DepthStats {
    size_t n = 0;
    float p50 = 0, p99 = 0, max = 0;
    long above2 = 0, above5 = 0, above10 = 0, above20 = 0;   // depths above 2%, 5%, 10%, 20% of BODY_DIAM
};
inline DepthStats depthStats(std::vector<float> d) {
    DepthStats s;
    s.n = d.size();
    if (d.empty()) return s;
    std::sort(d.begin(), d.end());
    auto q = [&](double p) { return d[std::max<size_t>(1, size_t(std::ceil(p * double(d.size())))) - 1]; };
    s.p50 = q(0.50);
    s.p99 = q(0.99);
    s.max = d.back();
    for (float x : d) { s.above2 += x > 0.02f; s.above5 += x > 0.05f; s.above10 += x > 0.10f; s.above20 += x > 0.20f; }
    return s;
}

// FNV-1a 64 continued over the raw bytes of an agent state (golden::stateHash's function, chained over the steps of a
// run: two runs with equal chains computed bit-identical states at every step)
inline void chainHash(uint64_t& h, const std::vector<GpuBoid>& state) {
    const unsigned char* b = reinterpret_cast<const unsigned char*>(state.data());
    for (size_t i = 0; i < state.size() * sizeof(GpuBoid); ++i) { h ^= b[i]; h *= 0x100000001b3ull; }
}

inline float cellSize() { return DOMAIN_SPAN / float(GRID_RES); }
inline float displacementBound() { return 0.5f * (cellSize() - BODY_DIAM); }

struct Result {
    VenueKind venue = VenueKind::BakedTerrace;
    int steps = 0, evacStep = -1;
    int s50 = -1, s90 = -1;      // steps at which 50% / 90% of the agents have left (t50 / t90)
    std::vector<float> depths;   // per overlapping pair and step, / BODY_DIAM, above OVERLAP_NOISE
    std::vector<float> caseDepths[CASE_COUNT][PZ_COUNT];   // the same depths by population and zone
    long contactPairs = 0;       // pair-steps closer than BODY_DIAM at all (incl. rounding-level contacts)
    double meanOverlappingAgents = 0.0;   // per step, agents in a pair above OVERLAP_NOISE / active
    float p50 = 0, p99 = 0, maxDepth = 0;
    DepthStats allStats, crowdStats, venueStats;   // every case / CROWD / FALL + RAMP, at the end of the run
    std::vector<float> crowdLegacy;                 // CROWD cases under the airborne-only fall rule
    DepthStats crowdLegacyStats;
    long stepDowns = 0;                             // agent-steps that stepped down a wall-steep face
    long gridMisses = 0;
    float maxDisplacement = 0.0f;
    long floorViolations = 0, centreInSolid = 0;
    long airborneRuns = 0, airborneRunHist[5] = {};   // runs of 1, 2, 3, 4, >= 5 steps
    int longestAirborne = 0;
    long fenceCrossings = 0, fenceBand = 0;
    long wallViolations = 0, slopeContacts = 0;
    // Diagnostics: the first violations (x, y, z, clearance; step, agent), for tools that locate them
    struct Sample { glm::vec4 p; int step, agent; };
    std::vector<Sample> wallViolationSamples;
    std::vector<Sample> floorViolationSamples;   // p.w = the floor height under the centre (stepup::floorUnder)
    struct PairSample { float depth; int step, i, j, kind; glm::vec4 pi, pj; };   // kind: OverlapCase
    std::vector<PairSample> venuePairSamples;   // the venue-geometry overlap pair-steps above 2% of BODY_DIAM (first 2000)
    float minWallClearance = 1e9f;
    float maxSpeed = 0.0f;
    long speedViolations = 0;
    double peakFull = 0.0, peakAny = 0.0;   // peak density over fully walkable / all included cells [p/m^2]
    int peakFullCell = -1, peakAnyCell = -1;
    double peakZone[metrics::ZONE_COUNT] = {};   // peak density per metric zone over its included cells [p/m^2]
    bool nan = false;
    uint64_t trajectoryHash = 0xcbf29ce484222325ull;   // chainHash over every step's agent state

    // Overlap depths of one population (zone < 0: every zone), of the venue-geometry cases (FALL + RAMP)
    DepthStats overlapCase(int c, int zone = -1) const {
        std::vector<float> d;
        for (int z = 0; z < PZ_COUNT; ++z)
            if (zone < 0 || zone == z) d.insert(d.end(), caseDepths[c][z].begin(), caseDepths[c][z].end());
        return depthStats(std::move(d));
    }
    DepthStats overlapVenue() const {
        std::vector<float> d;
        for (int c = CASE_FALL; c < CASE_COUNT; ++c)
            for (int z = 0; z < PZ_COUNT; ++z) d.insert(d.end(), caseDepths[c][z].begin(), caseDepths[c][z].end());
        return depthStats(std::move(d));
    }

    static bool withinCrowdLimits(const DepthStats& s) { return s.p99 <= CROWD_P99_LIMIT && s.max <= CROWD_MAX_LIMIT; }
    bool crowdOverlapOk() const { return withinCrowdLimits(crowdStats); }
    bool venueOverlapExempt() const { return venue == VenueKind::BakedTerrace; }
    // The crowd cases within the limits and, outside the baked terrace, the venue-geometry cases too (then every case is:
    // a mixture's p99 lies between its parts')
    bool overlapOk() const { return crowdOverlapOk() && (venueOverlapExempt() || withinCrowdLimits(venueStats)); }
    bool gridOk() const { return gridMisses == 0 && maxDisplacement <= displacementBound(); }
    bool floorOk() const { return floorViolations == 0 && centreInSolid == 0; }
    bool fenceOk() const { return fenceCrossings == 0 && fenceBand == 0; }
    bool wallOk() const { return wallViolations == 0; }
    bool speedOk() const { return speedViolations == 0; }
    bool densityOk() const { return peakFull <= DENSITY_CEILING_P_M2; }
    bool allOk() const { return evacStep > 0 && !nan && overlapOk() && gridOk() && floorOk() && fenceOk() && wallOk() && speedOk() && densityOk(); }
};

namespace detail {

template <class T>
std::vector<T> read(GLuint buffer, size_t count) {
    glMemoryBarrier(GL_BUFFER_UPDATE_BARRIER_BIT);
    std::vector<T> out(count);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer);
    glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, GLsizeiptr(count * sizeof(T)), out.data());
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    return out;
}

// The neighbour grid of the selected venue (venues M and L have their own; the terrace and S: sim_params.hpp's)
inline int gridRes() { const Venue* v = swarm::scene::selected(); return v ? v->gridRes : GRID_RES; }
inline int cellOf(glm::vec2 p) {
    const Venue* v = swarm::scene::selected();
    const float dmin = v ? v->domainMin : DOMAIN_MIN, dspan = v ? v->domainSpan : DOMAIN_SPAN;
    const int res = v ? v->gridRes : GRID_RES;
    const int x = std::clamp(int((p.x - dmin) / dspan * float(res)), 0, res - 1);
    const int y = std::clamp(int((p.y - dmin) / dspan * float(res)), 0, res - 1);
    return x + y * res;
}

inline float fenceSide(glm::vec2 p) {
    return sdBox2(p - glm::vec2(FENCE_CENTER.x, FENCE_CENTER.y), glm::vec2(FENCE_HALF_MID.x, FENCE_HALF_MID.y));
}

// Visible geometry (as test_gpu's sceneRawCPU): baked field union the fence's visual faces; true if the fence won
inline float scene(glm::vec3 p, bool* fence = nullptr) {
    const float f = sdFence(p) + BODY_RADIUS, d = f < BODY_RADIUS ? f : std::min(swarm::scene::sdf(p), f);
    if (fence) *fence = d == f;
    return d;
}

// Wall check in the centre's plane: the nearest wall surface point among RING_DIRS directions within
// BODY_RADIUS - WALL_TOL. Returns the clearance to it (>= the probe radius: none); slope: a walkable slope was hit.
// Is the surface point q, reached along the horizontal unit u, a wall? The fence's visual face, or a stadium surface
// with normal n_z <= WALL_MAX_NZ (central differences; physics.comp's classification) that reaches at least
// BODY_RADIUS above q (risers, aisle and outer walls). The bake's lips at the tread fronts and the slopes between
// aisle sub-steps, convex ridges and ramps that just reach the centre's plane, are walked over by the floor contact
// (the feelers step over them): not walls.
inline bool isWallHit(glm::vec3 q, glm::vec3 u) {
    bool fence = false;
    scene(q, &fence);
    if (fence) return true;
    if (scene(q + u * (0.5f * BODY_RADIUS) + glm::vec3(0.0f, 0.0f, BODY_DIAM)) > 0.0f) return false;   // half a radius inside, a body diameter higher
    const float h = 1e-4f;
    const glm::vec3 g((swarm::scene::sdf(q + glm::vec3(h, 0, 0)) - swarm::scene::sdf(q - glm::vec3(h, 0, 0))),
                      (swarm::scene::sdf(q + glm::vec3(0, h, 0)) - swarm::scene::sdf(q - glm::vec3(0, h, 0))),
                      (swarm::scene::sdf(q + glm::vec3(0, 0, h)) - swarm::scene::sdf(q - glm::vec3(0, 0, h))));
    const float len = glm::length(g);
    return len > 0.0f && g.z <= (WALL_MAX_NZ - WALL_NZ_MARGIN) * len;
}

inline float wallClearance(glm::vec3 c, bool& slope) {
    const float r = BODY_RADIUS - WALL_TOL;
    float best = 1e9f;
    slope = false;
    for (int k = 0; k < RING_DIRS; ++k) {
        const float a = float(2.0 * PI * k / RING_DIRS);
        const glm::vec3 u(std::cos(a), std::sin(a), 0.0f);
        if (scene(c + u * r) > 0.0f) continue;
        float lo = 0.0f, hi = r;   // scene(c + u lo) > 0 >= scene(c + u hi)
        if (scene(c) <= 0.0f) lo = hi = 0.0f;
        for (int i = 0; i < 30 && hi - lo > 1e-7f; ++i) {
            const float mid = 0.5f * (lo + hi);
            (scene(c + u * mid) > 0.0f ? lo : hi) = mid;
        }
        const glm::vec3 q = c + u * hi;
        if (isWallHit(q, u)) best = std::min(best, hi);
        else slope = true;
    }
    return best;
}

inline int pairZoneOf(glm::vec2 p) {
    if (fenceSide(p) < 0.0f) return PZ_PITCH;
    if (swarm::scene::seatedSelected()) {   // a seated venue: its cells (aisle = the gangways)
        const SeatedLayout& L = swarm::scene::selected()->layout;
        const glm::vec2 f = seated::fold(p);
        if (f.y < L.standFront) return PZ_WALKWAY;
        if (f.x < L.avenueHalf) return PZ_AVENUE;
        const int kind = seated::cellAt(L, p);
        if (kind == seated::TREAD || kind == seated::SEAT) return PZ_TREAD;
        if (kind == seated::INCLINE || kind == seated::GROUND) return PZ_AISLE;   // gangways and the barrier's gaps at their feet
        return PZ_WALKWAY;   // the rear concourse and its exits (no zone of their own)
    }
    const glm::vec2 a = glm::abs(p);
    const bool alongX = a.y >= a.x;
    const float lat = alongX ? a.x : a.y, dep = alongX ? a.y : a.x;
    if (lat < AVENUE_HALF) return PZ_AVENUE;
    if (dep < WALKWAY_MAX) return PZ_WALKWAY;
    if (lat < AISLE_MAX) return PZ_AISLE;
    return PZ_TREAD;
}

// Normal n_z of the floor under a centre: the first zero crossing of the baked field below it (0.5 mm steps over 5 cm,
// then bisection), its normal by central differences (CPU sampler); 1 where no floor is found
inline float floorNormalZ(glm::vec3 c) {
    float hi = c.z, lo = c.z;
    while (lo > c.z - 0.05f && swarm::scene::sdf(glm::vec3(c.x, c.y, lo)) > 0.0f) { hi = lo; lo -= 0.0005f; }
    for (int i = 0; i < 30 && hi - lo > 1e-7f; ++i) {
        const float mid = 0.5f * (lo + hi);
        (swarm::scene::sdf(glm::vec3(c.x, c.y, mid)) > 0.0f ? hi : lo) = mid;
    }
    const glm::vec3 q(c.x, c.y, 0.5f * (lo + hi));
    const float h = 1e-4f;
    const glm::vec3 g(swarm::scene::sdf(q + glm::vec3(h, 0, 0)) - swarm::scene::sdf(q - glm::vec3(h, 0, 0)),
                      swarm::scene::sdf(q + glm::vec3(0, h, 0)) - swarm::scene::sdf(q - glm::vec3(0, h, 0)),
                      swarm::scene::sdf(q + glm::vec3(0, 0, h)) - swarm::scene::sdf(q - glm::vec3(0, 0, h)));
    const float l = glm::length(g);
    return l > 0.0f ? g.z / l : 1.0f;
}

inline float percentile(std::vector<float>& v, double p) {   // nearest rank; sorts v
    if (v.empty()) return 0.0f;
    std::sort(v.begin(), v.end());
    return v[std::max<size_t>(1, size_t(std::ceil(p * double(v.size())))) - 1];
}

} // namespace detail

// The checks of one run, after every step (a class of their own, so that tools apply them to any engine, the GPU
// pipeline or the CPU reference; runEvacuation below is the GPU loop over it)
class Monitor {
public:
    // spawn: the state the run starts from; venue: which overlap limits apply (VenueKind above)
    Monitor(const std::vector<GpuBoid>& spawn, VenueKind venue)
        : spawn(spawn), prev(spawn), airborne(spawn.size(), 0), lastAir(spawn.size(), -1000), lastStepDown(spawn.size(), -1000), n(int(spawn.size())) {
        r.venue = venue;
    }
    // After step 'step' (1, 2, ...), cur: the state it produced. Returns the agents still active.
    long step(int step, const std::vector<GpuBoid>& cur) {
        using namespace detail;
        r.steps = step;
        chainHash(r.trajectoryHash, cur);

        // Pairs: overlap depths and the start-of-step grid
        const int gres = gridRes();
        std::vector<std::vector<int>> cells(size_t(gres) * gres);
        long active = 0;
        for (int i = 0; i < n; ++i)
            if (cur[size_t(i)].position.w != 0.0f) { cells[size_t(cellOf(glm::vec2(cur[size_t(i)].position)))].push_back(i); ++active; }
        std::vector<char> overlapping(size_t(n), 0);
        std::vector<OverlapPair> pairs;   // this step's overlapping pairs, classified below
        for (int c = 0; c < gres * gres; ++c) {
            const int cx = c % gres, cy = c / gres;
            for (int i : cells[size_t(c)])
                for (int y = std::max(cy - 1, 0); y <= std::min(cy + 1, gres - 1); ++y)
                    for (int x = std::max(cx - 1, 0); x <= std::min(cx + 1, gres - 1); ++x)
                        for (int j : cells[size_t(x + y * gres)]) {
                            if (j <= i) continue;
                            const float d = glm::length(glm::vec3(cur[size_t(i)].position) - glm::vec3(cur[size_t(j)].position));
                            if (d >= BODY_DIAM) continue;
                            ++r.contactPairs;
                            const float depth = (BODY_DIAM - d) / BODY_DIAM;
                            if (depth > OVERLAP_NOISE) {
                                r.depths.push_back(depth);
                                pairs.push_back({ i, j, depth });
                                overlapping[size_t(i)] = overlapping[size_t(j)] = 1;
                            }
                            const int a = cellOf(glm::vec2(prev[size_t(i)].position)), b = cellOf(glm::vec2(prev[size_t(j)].position));
                            if (std::abs(a % gres - b % gres) > 1 || std::abs(a / gres - b / gres) > 1) ++r.gridMisses;
                        }
        }
        long ov = 0;
        for (char o : overlapping) ov += o;
        if (active > 0) overlappingSum += double(ov) / double(active);
        if (r.s50 < 0 && active <= n / 2) r.s50 = step;
        if (r.s90 < 0 && active <= n / 10) r.s90 = step;

        // Per agent: displacement, floor, fence, walls, speed
        std::vector<float> disp(size_t(n), 0.0f), wallClear(size_t(n), 1e9f), speed(size_t(n), 0.0f);
        std::vector<char> floorBad(size_t(n), 0), inSolid(size_t(n), 0), air(size_t(n), 0), crossed(size_t(n), 0), band(size_t(n), 0),
            slope(size_t(n), 0), nanBad(size_t(n), 0), stepDown(size_t(n), 0);
#pragma omp parallel for schedule(dynamic, 64)
        for (int i = 0; i < n; ++i) {
            const GpuBoid& b = cur[size_t(i)];
            if (b.position.w == 0.0f) continue;
            const glm::vec3 c(b.position);
            nanBad[size_t(i)] = std::isnan(c.x) || std::isnan(c.y) || std::isnan(c.z);
            if (prev[size_t(i)].position.w != 0.0f) disp[size_t(i)] = glm::length(glm::vec2(c) - glm::vec2(prev[size_t(i)].position));
            inSolid[size_t(i)] = swarm::scene::sdf(c) <= 0.0f;
            floorBad[size_t(i)] = swarm::scene::sdf(c - glm::vec3(0.0f, 0.0f, BODY_RADIUS - FLOOR_TOL)) <= 0.0f;
            air[size_t(i)] = swarm::scene::sdf(c - glm::vec3(0.0f, 0.0f, BODY_RADIUS + FLOOR_TOL)) > 0.0f;
            crossed[size_t(i)] = (fenceSide(glm::vec2(c)) > 0.0f) != (fenceSide(glm::vec2(spawn[size_t(i)].position)) > 0.0f);
            band[size_t(i)] = sdFence(c) < -1e-5f;
            bool sl = false;
            wallClear[size_t(i)] = wallClearance(c, sl);
            slope[size_t(i)] = sl;
            speed[size_t(i)] = glm::length(glm::vec2(b.velocity));
            if (prev[size_t(i)].position.w != 0.0f) {   // step-down: the floor dropped along a path over a wall-steep face
                const glm::vec3 p0(prev[size_t(i)].position);
                const float f0 = stepup::floorUnder(p0), f1 = stepup::floorUnder(c);
                if (f1 < f0 - FLOOR_TOL) {
                    const float zTop = std::max(p0.z, c.z) + BODY_RADIUS;
                    const float len = glm::length(glm::vec2(c) - glm::vec2(p0));
                    const int ns = std::max(1, int(std::ceil(len / STEP_UP_SAMPLE)));
                    for (int k = 0; k <= ns && !stepDown[size_t(i)]; ++k) {
                        const glm::vec2 xy = glm::mix(glm::vec2(p0), glm::vec2(c), float(k) / float(ns));
                        const float f = stepup::floorUnder(glm::vec3(xy, zTop));
                        stepDown[size_t(i)] = !std::isnan(f) && stepup::floorNormalZ(xy, f) <= WALL_MAX_NZ;
                    }
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            if (cur[size_t(i)].position.w == 0.0f) {
                if (airborne[size_t(i)] > 0) { ++r.airborneRuns; ++r.airborneRunHist[std::min(airborne[size_t(i)], 5) - 1]; airborne[size_t(i)] = 0; }
                continue;
            }
            r.nan |= nanBad[size_t(i)] != 0;
            r.maxDisplacement = std::max(r.maxDisplacement, disp[size_t(i)]);
            r.centreInSolid += inSolid[size_t(i)];
            r.floorViolations += floorBad[size_t(i)];
            if (floorBad[size_t(i)] && r.floorViolationSamples.size() < 4000)
                r.floorViolationSamples.push_back({ glm::vec4(glm::vec3(cur[size_t(i)].position), stepup::floorUnder(glm::vec3(cur[size_t(i)].position))), step, i });
            r.fenceCrossings += crossed[size_t(i)];
            r.fenceBand += band[size_t(i)];
            r.slopeContacts += slope[size_t(i)];
            if (wallClear[size_t(i)] < BODY_RADIUS - WALL_TOL) {
                ++r.wallViolations;
                if (r.wallViolationSamples.size() < 4000) r.wallViolationSamples.push_back({ glm::vec4(glm::vec3(cur[size_t(i)].position), wallClear[size_t(i)]), step, i });
            }
            r.minWallClearance = std::min(r.minWallClearance, wallClear[size_t(i)]);
            r.maxSpeed = std::max(r.maxSpeed, speed[size_t(i)]);
            if (speed[size_t(i)] > V_MAX * (1.0f + 1e-6f)) ++r.speedViolations;
            if (stepDown[size_t(i)]) { lastStepDown[size_t(i)] = step; ++r.stepDowns; }
            if (air[size_t(i)]) {
                ++airborne[size_t(i)];
                r.longestAirborne = std::max(r.longestAirborne, airborne[size_t(i)]);
                lastAir[size_t(i)] = step;
            } else if (airborne[size_t(i)] > 0) {
                ++r.airborneRuns;
                ++r.airborneRunHist[std::min(airborne[size_t(i)], 5) - 1];
                airborne[size_t(i)] = 0;
            }
        }

        // Overlap populations of this step's pairs: FALL (airborne or a step-down within AIRBORNE_MEMORY steps), else RAMP
        // (floor n_z < RAMP_NZ under either agent), else CROWD; and the CROWD cases of the airborne-only rule (legacy)
        std::vector<char> needNz(size_t(n), 0);
        std::vector<char> fall(pairs.size(), 0), fallLegacy(pairs.size(), 0);
        for (size_t k = 0; k < pairs.size(); ++k) {
            const OverlapPair& o = pairs[k];
            fallLegacy[k] = lastAir[size_t(o.i)] >= step - AIRBORNE_MEMORY || lastAir[size_t(o.j)] >= step - AIRBORNE_MEMORY;
            fall[k] = fallLegacy[k] || lastStepDown[size_t(o.i)] >= step - AIRBORNE_MEMORY || lastStepDown[size_t(o.j)] >= step - AIRBORNE_MEMORY;
            if (!fallLegacy[k]) needNz[size_t(o.i)] = needNz[size_t(o.j)] = 1;
        }
        std::vector<float> nz(size_t(n), 1.0f);
#pragma omp parallel for schedule(dynamic, 16)
        for (int i = 0; i < n; ++i)
            if (needNz[size_t(i)]) nz[size_t(i)] = floorNormalZ(glm::vec3(cur[size_t(i)].position));
        for (size_t k = 0; k < pairs.size(); ++k) {
            const OverlapPair& o = pairs[k];
            // RAMP: a ramp of the BAKED floor (only the baked terrace has them; an analytic venue's steepest walkable floor is
            // an exact plane above RAMP_NZ, venue S's incline n_z 0.894, and n_z < RAMP_NZ there is the central differences straddling
            // an exact edge, so its pairs are crowd cases unless they fall)
            const bool ramp = r.venue == VenueKind::BakedTerrace && (nz[size_t(o.i)] < RAMP_NZ || nz[size_t(o.j)] < RAMP_NZ);
            const int c = fall[k] ? CASE_FALL : ramp ? CASE_RAMP : CASE_CROWD;
            r.caseDepths[c][pairZoneOf(glm::vec2(cur[size_t(o.i)].position))].push_back(o.depth);
            if (c != CASE_CROWD && o.depth > 0.02f && r.venuePairSamples.size() < 2000)
                r.venuePairSamples.push_back({ o.depth, step, o.i, o.j, c, cur[size_t(o.i)].position, cur[size_t(o.j)].position });
            if (!fallLegacy[k] && !ramp) r.crowdLegacy.push_back(o.depth);
        }
        prev = cur;
        if (active == 0) r.evacStep = step;
        return active;
    }
    // The end of the run: the overlap statistics, and the density peaks from the metric cells (mc: the run's GpuMetricCell
    // accumulators, cellInfo: their venue table; fully walkable cells: walkableM2 == 1)
    Result finish(const std::vector<GpuMetricCell>& mc, const std::vector<GpuMetricCellInfo>& cellInfo) {
        using namespace detail;
    r.meanOverlappingAgents = overlappingSum / double(std::max(r.steps, 1));
    std::vector<float> d = r.depths;
    r.p50 = percentile(d, 0.50);
    r.p99 = percentile(d, 0.99);
    r.maxDepth = d.empty() ? 0.0f : d.back();
    r.allStats = depthStats(std::move(d));
    r.crowdStats = r.overlapCase(CASE_CROWD);
    r.venueStats = r.overlapVenue();
    r.crowdLegacyStats = depthStats(r.crowdLegacy);

    for (size_t c = 0; c < mc.size(); ++c) {
        const float w = cellInfo[c].walkableM2;
        if (w <= 0.0f || cellInfo[c].thresholdMass[0] == 0xFFFFFFFFu) continue;   // excluded cell
        const double dens = double(mc[c].peakMass) / double(metrics::MASS_ONE) / double(w);
        if (dens > r.peakAny) { r.peakAny = dens; r.peakAnyCell = int(c); }
        if (w >= 1.0f && dens > r.peakFull) { r.peakFull = dens; r.peakFullCell = int(c); }
        if (cellInfo[c].zone < uint32_t(metrics::ZONE_COUNT)) r.peakZone[cellInfo[c].zone] = std::max(r.peakZone[cellInfo[c].zone], dens);
    }
        return r;
    }
    const Result& result() const { return r; }

private:
    struct OverlapPair { int i, j; float depth; };
    Result r;
    std::vector<GpuBoid> spawn, prev;
    std::vector<int> airborne;
    std::vector<int> lastAir;        // the last step in which the agent was airborne
    std::vector<int> lastStepDown;   // the last step in which it stepped down a wall-steep face
    double overlappingSum = 0.0;
    int n;
};

// Steps 'sim' (spawn already uploaded as 'spawn') with the metrics after every step until every agent has left or
// maxSteps, checking after every step. 'cellInfo': the venue table of 'gm' (fully walkable cells: walkableM2 == 1).
// 'venue': which overlap limits apply (VenueKind above). The CPU checks sample the venue swarm::scene selects
// (the terrace unless a seated venue is selected); beforeStep(step, state), if set, runs before every step with the state
// it starts from (forced-motion drives).
inline Result runEvacuation(CrowdSim& sim, GLuint sdfTex, const std::vector<GpuBoid>& spawn, metrics::CrowdMetrics& gm,
                            const std::vector<GpuMetricCellInfo>& cellInfo, int maxSteps, VenueKind venue = VenueKind::BakedTerrace,
                            const std::function<void(int, const std::vector<GpuBoid>&)>& beforeStep = nullptr) {
    Monitor m(spawn, venue);
    std::vector<GpuBoid> prev = spawn;
    for (int step = 1; step <= maxSteps; ++step) {
        if (beforeStep) beforeStep(step, prev);
        sim.step(sdfTex);
        gm.afterStep(sim);
        const std::vector<GpuBoid> cur = detail::read<GpuBoid>(sim.currentStateBuffer(), spawn.size());
        const long active = m.step(step, cur);
        prev = cur;
        if (active == 0) break;
    }
    return m.finish(gm.readCells(), cellInfo);
}

inline void print(const Result& r, const char* indent = "  ") {
    std::printf("%sevacuated at step %d (%d steps checked)\n", indent, r.evacStep, r.steps);
    std::printf("%soverlap depth (pairs closer than BODY_DIAM, / BODY_DIAM, above %.0e): %zu pair-steps, p50 %.4f, p99 %.4f, max %.4f;"
                " %ld pair-steps in contact incl. rounding level; agents overlapping per step: mean %.2f%%\n",
                indent, OVERLAP_NOISE, r.depths.size(), r.p50, r.p99, r.maxDepth, r.contactPairs, 100.0 * r.meanOverlappingAgents);
    std::printf("%soverlap limits: crowd cases %zu pair-steps, p99 %.4f, max %.4f (limits p99 <= %.2f, max <= %.2f); venue-geometry"
                " cases %zu pair-steps, p99 %.4f, max %.4f: %s\n", indent, r.crowdStats.n, r.crowdStats.p99, r.crowdStats.max, CROWD_P99_LIMIT,
                CROWD_MAX_LIMIT, r.venueStats.n, r.venueStats.p99, r.venueStats.max,
                r.venueOverlapExempt() ? "exempt (baked terrace reference venue)" : "held to the crowd limits (analytic venue)");
    std::printf("%sstep-downs of a wall-steep face: %ld agent-steps (FALL cases); crowd cases under the airborne-only rule "
                "(for comparison): %zu pair-steps, p99 %.4f, max %.4f\n", indent, r.stepDowns, r.crowdLegacyStats.n, r.crowdLegacyStats.p99,
                r.crowdLegacyStats.max);
    std::printf("%sneighbour grid: max horizontal displacement in a step %.5f (bound (cell - BODY_DIAM) / 2 = %.5f); pairs closer than "
                "BODY_DIAM from non-adjacent start-of-step cells: %ld\n", indent, r.maxDisplacement, displacementBound(), r.gridMisses);
    std::printf("%sfloors: centre in solid %ld, centre below floor + BODY_RADIUS - %.0e: %ld agent-steps; airborne runs %ld (1 / 2 / 3 / 4 / 5+ steps:"
                " %ld / %ld / %ld / %ld / %ld), longest %d\n", indent, r.centreInSolid, FLOOR_TOL, r.floorViolations, r.airborneRuns,
                r.airborneRunHist[0], r.airborneRunHist[1], r.airborneRunHist[2], r.airborneRunHist[3], r.airborneRunHist[4], r.longestAirborne);
    // wallClearance searches only within BODY_RADIUS - WALL_TOL: no wall that close leaves the minimum at its 1e9 sentinel
    char minClear[64];
    if (r.minWallClearance < 1e8f) std::snprintf(minClear, sizeof minClear, "%.6f", r.minWallClearance);
    else std::snprintf(minClear, sizeof minClear, "none within %.4f", BODY_RADIUS - WALL_TOL);
    std::printf("%sfence: midline crossings %ld, inside the collision band %ld agent-steps; walls: clearance < BODY_RADIUS - %.0e %ld agent-steps,"
                " min wall clearance %s (BODY_RADIUS %.4f), walkable-slope contacts within it %ld (not walls)\n", indent, r.fenceCrossings,
                r.fenceBand, WALL_TOL, r.wallViolations, minClear, BODY_RADIUS, r.slopeContacts);
    std::printf("%sspeed: max |v_xy| %.6f (V_MAX %.2f), %ld above; density: peak %.2f p/m^2 over fully walkable cells (cell %d), %.2f over all "
                "included cells (cell %d); hexagonal packing %.2f, ceiling %.2f\n", indent, r.maxSpeed, V_MAX, r.speedViolations, r.peakFull,
                r.peakFullCell, r.peakAny, r.peakAnyCell, HEX_PACKING_P_M2, DENSITY_CEILING_P_M2);
}

// The overlap depths by population (and zone), one row each: pair-steps, share, p50, p99, max, above 2 / 5 / 10 / 20%
inline void printOverlapCases(const Result& r, const char* indent = "  ") {
    const size_t total = std::max<size_t>(r.depths.size(), 1);
    auto row = [&](const std::string& what, const DepthStats& s) {
        std::printf("%s%-44s %7zu (%5.1f%%)  p50 %.4f  p99 %.4f  max %.4f  > 2%% %5ld  > 5%% %5ld  > 10%% %4ld  > 20%% %4ld\n", indent, what.c_str(), s.n,
                    100.0 * double(s.n) / double(total), s.p50, s.p99, s.max, s.above2, s.above5, s.above10, s.above20);
    };
    row("all overlapping pair-steps", depthStats(r.depths));
    row("venue geometry (fall + ramp)", r.overlapVenue());
    for (int c = CASE_FALL; c < CASE_COUNT; ++c) {
        row(std::string(". ") + caseName(c), r.overlapCase(c));
        for (int z = 0; z < PZ_COUNT; ++z)
            if (!r.caseDepths[c][z].empty()) row(std::string(".   ") + pairZoneName(z), r.overlapCase(c, z));
    }
    row("crowd (steadily grounded, walkable floor)", r.overlapCase(CASE_CROWD));
    for (int z = 0; z < PZ_COUNT; ++z)
        if (!r.caseDepths[CASE_CROWD][z].empty()) row(std::string(".   ") + pairZoneName(z), r.overlapCase(CASE_CROWD, z));
}

} // namespace swarm::plausibility
