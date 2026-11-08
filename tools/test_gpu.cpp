// Headless GPU verification for the SWARM pipeline.
// Runs the real swarm_core code in a hidden OpenGL 4.3 core debug context and exits non-zero
// if any check fails. Readbacks here are for verification only; the app never reads back.
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <swarm/assets.hpp>
#include <swarm/async_counters.hpp>
#include <swarm/build_info.hpp>
#include <swarm/cpu_crowd_sim.hpp>
#include <swarm/crowd_sim.hpp>
#include <swarm/exit_choice.hpp>
#include <swarm/gpu_caps.hpp>
#include <swarm/gpu_types.hpp>
#include <swarm/sdf.hpp>
#include <swarm/shader.hpp>
#include <swarm/sim_params.hpp>
#include <swarm/fixed_step_clock.hpp>
#include <swarm/metrics.hpp>
#include <swarm/nav_field.hpp>
#include <swarm/venue.hpp>
#include <swarm/venue_capacity.hpp>

#include "choice_check.hpp"
#include "golden_state.hpp"
#include "nav_check.hpp"
#include "nav_goal_check.hpp"
#include "plausibility.hpp"
#include "stepup.hpp"
#include "tiebreak.hpp"
#include "venue_s.hpp"

#include <algorithm>
#include <array>
#include <cctype>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#ifdef _MSC_VER
#include <intrin.h>
#endif

namespace fs = std::filesystem;
using namespace swarm;

namespace {

constexpr int NUM_AGENTS = 4096;   // matches the app's NUM_BOIDS

int g_failures = 0;

void check(bool ok, const std::string& what) {
    std::printf("  [%s] %s\n", ok ? "PASS" : "FAIL", what.c_str());
    if (!ok) ++g_failures;
}

// Test tiers. The LONG tier adds the slow checks: the CPU reference's full evacuations and long CPU runs (parity.grid at
// N = 65536, parity.thread_invariance, parity.cpu_determinism, parity.terrace_evacuation), the step-up limit's evacuations
// (physics.step_up_limit), venue S's dense forced scenario (venue.s_forced_dense) and the CPU runs of parity.s_forced. It runs by default
// in Release; in Debug (the CPU steps ~16x slower) it is opt-in: --long or
// SWARM_TEST_LONG=1 (--quick or SWARM_TEST_LONG=0 skip it in Release). Without it every section still runs its quick checks.
bool g_longTier = false;
// Prints why a long-tier block is skipped; true if it runs
bool longTier(const char* what) {
    if (g_longTier) return true;
    std::printf("  [long tier] skipped: %s (run with --long or SWARM_TEST_LONG=1)\n", what);
    return false;
}

// Wall-clock time per section (the test tiers' runtimes), printed as a table at the end of the run
struct SectionTimes {
    std::string title;   // the running section's ("" before the first)
    std::chrono::steady_clock::time_point start;
    std::vector<std::pair<std::string, double>> done;   // finished sections: title, seconds
    void end() {
        if (title.empty()) return;
        done.emplace_back(title, std::chrono::duration<double>(std::chrono::steady_clock::now() - start).count());
        title.clear();
    }
};
SectionTimes g_sectionTimes;

void section(const char* title) {
    g_sectionTimes.end();
    std::printf("\n== %s\n", title);
    g_sectionTimes.title = title;
    g_sectionTimes.start = std::chrono::steady_clock::now();
}

// --- GL debug output: count driver errors/warnings while enabled ---
struct DebugLog {
    bool enabled = false;
    int errors = 0, warnings = 0;
    std::vector<std::string> samples;
} g_debug;

void APIENTRY onDebugMessage(GLenum, GLenum type, GLuint, GLenum severity, GLsizei, const GLchar* msg, const void*) {
    if (!g_debug.enabled || severity == GL_DEBUG_SEVERITY_NOTIFICATION) return;
    if (type == GL_DEBUG_TYPE_ERROR) ++g_debug.errors; else ++g_debug.warnings;
    if (g_debug.samples.size() < 8) g_debug.samples.emplace_back(msg);
}

// Collects everything the loader prints to std::cerr (warnings/errors) while alive
struct CerrCapture {
    std::ostringstream buf;
    std::streambuf* old = std::cerr.rdbuf(buf.rdbuf());
    std::string release() { std::cerr.rdbuf(old); return buf.str(); }
    ~CerrCapture() { std::cerr.rdbuf(old); }
};

template <class T>
std::vector<T> readBuffer(GLuint buffer, size_t count) {
    glMemoryBarrier(GL_BUFFER_UPDATE_BARRIER_BIT);  // make shader writes visible to glGetBufferSubData
    std::vector<T> out(count);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer);
    glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, GLsizeiptr(count * sizeof(T)), out.data());
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    return out;
}

template <class T>
GLuint makeBuffer(const std::vector<T>& data) {
    GLuint b;
    glGenBuffers(1, &b);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, b);
    glBufferData(GL_SHADER_STORAGE_BUFFER, GLsizeiptr(data.size() * sizeof(T)), data.data(), GL_DYNAMIC_READ);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    return b;
}

// CPU mirror of calc_grid.comp's cellID() at a given resolution
uint32_t cellOf(const glm::vec4& p, int res) {
    int x = std::clamp(int((p.x - DOMAIN_MIN) / DOMAIN_SPAN * float(res)), 0, res - 1);
    int y = std::clamp(int((p.y - DOMAIN_MIN) / DOMAIN_SPAN * float(res)), 0, res - 1);
    return uint32_t(x + y * res);
}

// --- CPU mirror of the @sep-kernel block in physics.comp ---
uint32_t hash32(uint32_t x) {
    x ^= x >> 16; x *= 0x7feb352du;
    x ^= x >> 15; x *= 0x846ca68bu;
    x ^= x >> 16;
    return x;
}

glm::vec2 pairDirection(uint32_t self, uint32_t other) {
    uint32_t lo = std::min(self, other), hi = std::max(self, other);
    float angle = float(hash32(hash32(lo) ^ hi)) * (6.28318530718f / 4294967296.0f);
    glm::vec2 dir(std::cos(angle), std::sin(angle));
    return self == lo ? dir : -dir;
}

float separationMagnitude(float d) {
    if (d >= R_SEP) return 0.0f;
    float w = 1.0f - d / R_SEP;
    return K_SEP * w * w;
}

glm::vec2 separationForce(glm::vec3 offset, uint32_t self, uint32_t other) {
    float d2 = glm::dot(offset, offset);
    if (d2 >= R_SEP2) return glm::vec2(0.0f);
    float magnitude = separationMagnitude(std::sqrt(d2));
    float dxy2 = glm::dot(glm::vec2(offset), glm::vec2(offset));
    if (dxy2 <= SEP_STACKED_XY2) return magnitude * pairDirection(self, other);  // |xy offset| <= 1e-6
    return magnitude * glm::vec2(offset) / std::sqrt(dxy2);
}

// The kernel this task replaces, for comparison only
float oldSeparationMagnitude(float d) { return d < R_SEP ? d / (d * d + 0.0004f) : 0.0f; }

// CPU mirror of contactCorrection (the hard-body projection's pair correction, @sep-kernel block)
glm::vec2 contactCorrection(glm::vec3 offset, uint32_t self, uint32_t other) {
    float dxy2 = glm::dot(glm::vec2(offset), glm::vec2(offset));
    if (std::abs(offset.z) >= BODY_DIAM || dxy2 >= BODY_DIAM2) return glm::vec2(0.0f);
    float dxy = std::sqrt(dxy2);
    float shift = 0.5f * (BODY_DIAM - dxy);
    if (dxy2 <= SEP_STACKED_XY2) return shift * pairDirection(self, other);
    return shift * (glm::vec2(offset) / dxy);
}

// Where an agent physically is (for reporting). PITCH means past the fence midline, i.e. inside
// the fence; an agent resting on the fence's outer face is on the walkway.
enum Zone { TREAD, AISLE, WALKWAY, AVENUE, PITCH, ZONE_COUNT };

float fenceSide(const glm::vec4& p);

Zone zoneOf(const glm::vec4& p) {
    if (fenceSide(p) < 0.0f) return PITCH;
    glm::vec2 a = glm::abs(glm::vec2(p));
    bool alongX = a.y >= a.x;
    float lat = alongX ? a.x : a.y, dep = alongX ? a.y : a.x;
    if (lat < AVENUE_HALF) return AVENUE;
    if (dep < WALKWAY_MAX) return WALKWAY;
    if (lat < AISLE_MAX) return AISLE;
    return TREAD;
}

// Agent that egressTarget() in physics.comp sends down its pitch-recovery branch
bool inRouterPitchBranch(const glm::vec4& p) {
    glm::vec2 a = glm::abs(glm::vec2(p));
    return std::max(a.x, a.y) < WALKWAY_MIN;   // every other branch requires dep >= WALKWAY_MIN
}

// Pairs within R_PERC (horizontal distance) whose cells are more than 'ring' cells apart at this resolution
long missedNeighbourPairs(const std::vector<GpuBoid>& s, int res, int ring, long* pairsOut) {
    std::vector<glm::vec4> act;
    for (const GpuBoid& b : s) if (b.position.w != 0.0f) act.push_back(b.position);
    long pairs = 0, missed = 0;
    for (size_t i = 0; i < act.size(); ++i) {
        uint32_t ci = cellOf(act[i], res);
        for (size_t j = i + 1; j < act.size(); ++j) {
            float d = glm::length(glm::vec2(act[i]) - glm::vec2(act[j]));
            if (d >= R_PERC) continue;
            ++pairs;
            uint32_t cj = cellOf(act[j], res);
            int dx = std::abs(int(ci % res) - int(cj % res)), dy = std::abs(int(ci / res) - int(cj / res));
            if (dx > ring || dy > ring) ++missed;
        }
    }
    if (pairsOut) *pairsOut = pairs;
    return missed;
}

// Overlapping pairs of active agents (3D distance < BODY_DIAM; depth = BODY_DIAM - distance), found
// through a grid of the hash's cells (wider than BODY_DIAM). Appends each pair's depth / BODY_DIAM to 'depths'
// and calls onPair(i, j, depth) for each.
struct OverlapScan { long pairs = 0, agents = 0; float maxDepth = 0.0f; };
OverlapScan scanOverlaps(const std::vector<GpuBoid>& s, std::vector<float>* depths,
                         const std::function<void(int, int, float)>& onPair = nullptr) {
    std::vector<std::vector<int>> cells(size_t(GRID_RES) * GRID_RES);
    for (size_t i = 0; i < s.size(); ++i)
        if (s[i].position.w != 0.0f) cells[cellOf(s[i].position, GRID_RES)].push_back(int(i));
    std::vector<char> overlapping(s.size(), 0);
    OverlapScan r;
    for (int c = 0; c < GRID_RES * GRID_RES; ++c) {
        const int cx = c % GRID_RES, cy = c / GRID_RES;
        for (int i : cells[size_t(c)])
            for (int y = std::max(cy - 1, 0); y <= std::min(cy + 1, GRID_RES - 1); ++y)
                for (int x = std::max(cx - 1, 0); x <= std::min(cx + 1, GRID_RES - 1); ++x)
                    for (int j : cells[size_t(x + y * GRID_RES)]) {
                        if (j <= i) continue;
                        const float d = glm::length(glm::vec3(s[size_t(i)].position) - glm::vec3(s[size_t(j)].position));
                        if (d >= BODY_DIAM) continue;
                        ++r.pairs;
                        r.maxDepth = std::max(r.maxDepth, BODY_DIAM - d);
                        overlapping[size_t(i)] = overlapping[size_t(j)] = 1;
                        if (depths) depths->push_back((BODY_DIAM - d) / BODY_DIAM);
                        if (onPair) onPair(i, j, BODY_DIAM - d);
                    }
    }
    for (char o : overlapping) r.agents += o;
    return r;
}

bool hasNaN(const GpuBoid& b) {
    const float* f = &b.position.x;
    for (int k = 0; k < 8; ++k) if (std::isnan(f[k])) return true;
    return false;
}

struct StepInvariants {
    long unsorted = 0, badPermutation = 0, hashMismatch = 0, inactiveNotAtTail = 0;
    long cellRangeErrors = 0, cellTotalMismatch = 0, inactiveChanged = 0, nanStates = 0, inputOverwritten = 0;
    long active = 0;
    bool ok() const {
        return !(unsorted || badPermutation || hashMismatch || inactiveNotAtTail || cellRangeErrors ||
                 cellTotalMismatch || inactiveChanged || nanStates || inputOverwritten);
    }
};

// before: state read before the step; prevAfter: the physics input buffer read after the step
StepInvariants verifyStep(const std::vector<GpuBoid>& before, const std::vector<GpuBoid>& prevAfter,
                          const std::vector<GpuBoid>& cur, const std::vector<GpuGridInfo>& grid,
                          const std::vector<GpuCellData>& cells) {
    StepInvariants r;
    const size_t n = grid.size();
    if (std::memcmp(before.data(), prevAfter.data(), n * sizeof(GpuBoid)) != 0) r.inputOverwritten = 1;

    std::vector<char> seen(n, 0);
    bool inactiveSeen = false;
    for (size_t s = 0; s < n; ++s) {
        if (s > 0 && grid[s - 1].gridID > grid[s].gridID) ++r.unsorted;
        uint32_t b = grid[s].boidID;
        if (b >= n || seen[b]++) { ++r.badPermutation; continue; }
        uint32_t expected = before[b].position.w == 0.0f ? INACTIVE_CELL : cellOf(before[b].position, GRID_RES);
        if (grid[s].gridID != expected) ++r.hashMismatch;
        if (grid[s].gridID == INACTIVE_CELL) inactiveSeen = true;
        else { ++r.active; if (inactiveSeen) ++r.inactiveNotAtTail; }
    }

    long total = 0;
    for (size_t c = 0; c < cells.size(); ++c) {
        const GpuCellData& cell = cells[c];
        total += cell.agentCount;
        if (cell.agentCount == 0) continue;
        size_t start = cell.startIndex, end = size_t(cell.startIndex) + cell.agentCount;
        if (end > n) { ++r.cellRangeErrors; continue; }
        for (size_t s = start; s < end; ++s) if (grid[s].gridID != c) ++r.cellRangeErrors;
        if (start > 0 && grid[start - 1].gridID == c) ++r.cellRangeErrors;
        if (end < n && grid[end].gridID == c) ++r.cellRangeErrors;
    }
    if (total != r.active) r.cellTotalMismatch = 1;

    for (size_t i = 0; i < n; ++i) {
        if (before[i].position.w == 0.0f && std::memcmp(&before[i], &cur[i], sizeof(GpuBoid)) != 0) ++r.inactiveChanged;
        if (hasNaN(cur[i])) ++r.nanStates;
    }
    return r;
}

// Compiles a probe: a block of physics.comp between two markers plus a test entry point
GLuint loadPhysicsBlockProbe(const fs::path& shaderDir, const char* begin, const char* end, const std::string& entry) {
    std::ifstream pf(shaderDir / "physics.comp");
    std::stringstream ss;
    ss << pf.rdbuf();
    std::string phys = ss.str();
    size_t b = phys.find(begin), e = phys.find(end);
    if (b == std::string::npos || e == std::string::npos)
        throw std::runtime_error(std::string("physics.comp lacks ") + begin + " / " + end + " markers");
    std::string src = "#version 430 core\n" + phys.substr(b, e - b) + entry;
    fs::path tmp = processTempPath("swarm_physics_probe.comp");
    { std::ofstream(tmp) << src; }
    GLuint prog = loadComputeProgram(tmp);
    fs::remove(tmp);
    return prog;
}

std::vector<float> gpuSdfProbe(GLuint prog, GLuint sdfTex, const std::vector<glm::vec3>& points) {
    std::vector<glm::vec4> pts;
    for (const glm::vec3& p : points) pts.emplace_back(p, 1.0f);
    GLuint in = makeBuffer(pts), out = makeBuffer(std::vector<float>(pts.size()));
    glUseProgram(prog);
    glUniform3fv(glGetUniformLocation(prog, "u_sdfMin"), 1, &SDF_MIN[0]);
    glUniform1f(glGetUniformLocation(prog, "u_sdfInvSpacing"), 1.0f / SDF_SPACING);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_3D, sdfTex);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, in);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, out);
    glDispatchCompute(GLuint(pts.size()), 1, 1);
    std::vector<float> result = readBuffer<float>(out, pts.size());
    glDeleteBuffers(1, &in);
    glDeleteBuffers(1, &out);
    return result;
}

struct KernelCase { glm::vec4 offset; glm::uvec4 ids; };  // std430: vec4 + uvec4

std::vector<glm::vec2> gpuKernel(GLuint prog, const std::vector<KernelCase>& cases) {
    GLuint in = makeBuffer(cases), out = makeBuffer(std::vector<glm::vec2>(cases.size()));
    glUseProgram(prog);
    glUniform1i(glGetUniformLocation(prog, "count"), GLint(cases.size()));
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, in);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, out);
    glDispatchCompute(GLuint((cases.size() + 63) / 64), 1, 1);
    std::vector<glm::vec2> result = readBuffer<glm::vec2>(out, cases.size());
    glDeleteBuffers(1, &in);
    glDeleteBuffers(1, &out);
    return result;
}

// Runs a probe with 'count' vec4 inputs at binding 5 and vec4 outputs at binding 6
std::vector<glm::vec4> gpuVec4Probe(GLuint prog, const std::vector<glm::vec4>& inputs) {
    GLuint in = makeBuffer(inputs), out = makeBuffer(std::vector<glm::vec4>(inputs.size()));
    glUseProgram(prog);
    glUniform1i(glGetUniformLocation(prog, "count"), GLint(inputs.size()));
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, in);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, out);
    glDispatchCompute(GLuint((inputs.size() + 63) / 64), 1, 1);
    std::vector<glm::vec4> result = readBuffer<glm::vec4>(out, inputs.size());
    glDeleteBuffers(1, &in);
    glDeleteBuffers(1, &out);
    return result;
}

const glm::vec2 FENCE_C(FENCE_CENTER.x, FENCE_CENTER.y);
const glm::vec2 FENCE_MID(FENCE_HALF_MID.x, FENCE_HALF_MID.y);

// Signed distance to the fence midline rectangle: > 0 outside (stand side), < 0 on the pitch side
float fenceSide(const glm::vec4& p) { return sdBox2(glm::vec2(p) - FENCE_C, FENCE_MID); }

// Point on the fence midline rectangle; t in [0, 4) walks the four sides
glm::vec2 fenceMidlinePoint(float t) {
    int side = std::min(int(t), 3);
    float u = (t - float(side)) * 2.0f - 1.0f;
    glm::vec2 q = side == 0 ? glm::vec2(u * FENCE_MID.x, FENCE_MID.y)
                : side == 1 ? glm::vec2(FENCE_MID.x, -u * FENCE_MID.y)
                : side == 2 ? glm::vec2(-u * FENCE_MID.x, -FENCE_MID.y)
                            : glm::vec2(-FENCE_MID.x, u * FENCE_MID.y);
    return FENCE_C + q;
}

// Near a kink of the fence field (midline, interior diagonals, or ring corners), where the
// gradient legitimately depends on which side is picked
bool nearFenceKink(glm::vec2 p) {
    glm::vec2 rel = glm::abs(p - FENCE_C);
    bool corner = rel.x > FENCE_MID.x - 0.05f && rel.y > FENCE_MID.y - 0.05f;
    bool midline = std::abs(sdBox2(p - FENCE_C, FENCE_MID)) < 1e-3f;
    bool diagonal = std::abs((rel.x - FENCE_MID.x) - (rel.y - FENCE_MID.y)) < 1e-3f;
    return corner || midline || diagonal;
}

// --- Scene on the CPU sampler: what physics sees ---
// Distance to the visible geometry: baked SDF union the fence's visual faces (sdFence is inflated
// by BODY_RADIUS for contact). Inside the fence's collision band the baked field is a blurred
// copy of the fence mesh; there the analytic fence stands for it, as in physics (clearWalls).
float sceneRawCPU(glm::vec3 p) {
    const float fence = sdFence(p) + BODY_RADIUS;
    return fence < BODY_RADIUS ? fence : std::min(sampleSDF_CPU(p), fence);
}

// Height of the stadium surface under xy (floors are stadium surfaces; the fence is an infinite
// vertical extrusion, never a floor): bracket the first crossing going down, then bisect to 1e-7
float floorHeight(glm::vec2 xy, float zTop = 0.2f) {
    float hi = zTop, lo = zTop;
    while (lo > -0.05f && sampleSDF_CPU(glm::vec3(xy, lo)) > 0.0f) { hi = lo; lo -= 0.0005f; }
    for (int i = 0; i < 40 && hi - lo > 1e-7f; ++i) {
        float mid = 0.5f * (lo + hi);
        (sampleSDF_CPU(glm::vec3(xy, mid)) > 0.0f ? hi : lo) = mid;
    }
    return 0.5f * (lo + hi);
}

// Free distance from c along u until the visible geometry is closer than 'margin'
float freeRun(glm::vec3 c, glm::vec3 u, float margin, float maxDist = 0.4f) {
    const float step = 0.0002f;
    float prev = sceneRawCPU(c) - margin;
    for (float t = step; t <= maxDist; t += step) {
        float d = sceneRawCPU(c + u * t) - margin;
        if (d <= 0.0f) return t - step + step * prev / (prev - d);
        prev = d;
    }
    return maxDist;
}

// Distance from c along the horizontal unit u to the visible surface (zero level), capped at
// maxDist. The baked field is not a unit-gradient distance (|grad| 0.4-0.9 at the stands), so its
// value is not the clearance; it is a lower bound (|grad| <= 1), so sphere tracing on it
// converges onto the zero level without passing it.
float rayToSurface(glm::vec3 c, glm::vec3 u, float maxDist) {
    float t = 0.0f;
    for (int i = 0; i < 200 && t < maxDist; ++i) {
        float d = sceneRawCPU(c + u * t);
        if (d < 1e-7f) return t;
        t += d;
    }
    return std::min(t, maxDist);
}

// Horizontal clearance at c: min over horizontal directions (all of them, or a fan of
// +/-40 degrees around 'towards') of the distance to the visible surface in the plane z = c.z
float horizontalClearance(glm::vec3 c, float maxDist, glm::vec2 towards = glm::vec2(0.0f)) {
    float best = maxDist;
    const bool fan = towards != glm::vec2(0.0f);
    const int n = fan ? 9 : 64;
    for (int i = 0; i < n; ++i) {
        float a = fan ? glm::radians(-40.0f + 10.0f * float(i)) : 6.2831853f * float(i) / float(n);
        glm::vec2 b = fan ? towards : glm::vec2(1.0f, 0.0f);
        glm::vec2 u(b.x * std::cos(a) - b.y * std::sin(a), b.x * std::sin(a) + b.y * std::cos(a));
        best = std::min(best, rayToSurface(c, glm::vec3(u, 0.0f), best));
    }
    return best;
}

// horizontalClearance restricted to walls: the fan's rays that end on a wall surface
// (plausibility::detail::isWallHit); rays ending on a walkable slope or a tread lip do not count
float wallFanClearance(glm::vec3 c, float maxDist, glm::vec2 towards) {
    float best = maxDist;
    for (int i = 0; i < 9; ++i) {
        float a = glm::radians(-40.0f + 10.0f * float(i));
        glm::vec2 u(towards.x * std::cos(a) - towards.y * std::sin(a), towards.x * std::sin(a) + towards.y * std::cos(a));
        const float t = rayToSurface(c, glm::vec3(u, 0.0f), maxDist);
        if (t < maxDist && swarm::plausibility::detail::isWallHit(c + glm::vec3(u, 0.0f) * t, glm::vec3(u, 0.0f))) best = std::min(best, t);
    }
    return best;
}

// Rest height of the agent-centre plane above the local floor: + for a centre above floor + R
float aboveRest(const glm::vec4& p) { return p.z - (floorHeight(glm::vec2(p)) + BODY_RADIUS); }

// Width across a passage through c (xy) along u, in the plane of the rest height floor(c) +
// BODY_RADIUS: geometric clear width, and the centre-accessible extent (where the horizontal
// clearance to every wall is >= BODY_RADIUS), found by bisection towards each geometric end
struct Passage { float geometric, accessible; };
Passage passageWidth(glm::vec2 c, glm::vec2 u) {
    glm::vec3 p(c, floorHeight(c) + BODY_RADIUS), dir(u, 0.0f);
    Passage r{ 0.0f, 0.0f };
    for (float sgn : { 1.0f, -1.0f }) {
        float end = freeRun(p, dir * sgn, 0.0f);
        r.geometric += end;
        float lo = 0.0f, hi = end;   // clearance(lo) >= R > clearance(hi) = 0
        if (horizontalClearance(p, BODY_RADIUS + 1e-3f) < BODY_RADIUS) continue;
        for (int i = 0; i < 24; ++i) {
            float mid = 0.5f * (lo + hi);
            (horizontalClearance(p + dir * (sgn * mid), BODY_RADIUS + 1e-3f) >= BODY_RADIUS ? lo : hi) = mid;
        }
        r.accessible += lo;
    }
    return r;
}

// --- Fence tunneling scenarios ---
struct FenceRun {
    std::vector<long> crossStepsPerGroup;    // agent-steps spent on the other side of the midline
    std::vector<long> crossedAgentsPerGroup; // agents that were ever on the other side
    std::vector<long> touchedPerGroup;       // agents that reached their collision face
    float maxRise = 0.0f;                    // max height above floor + R at each agent's highest point (fence riding)
    bool nan = false;
};

// Steps 'boids' (equal-sized groups, in order) and tracks each agent's side of the fence midline
FenceRun runFenceScenario(const fs::path& shaderDir, GLuint sdfTex, const std::vector<GpuBoid>& boids, int groups, int steps) {
    const int n = int(boids.size()), perGroup = n / groups;
    FenceRun r;
    r.crossStepsPerGroup.assign(groups, 0);
    r.crossedAgentsPerGroup.assign(groups, 0);
    r.touchedPerGroup.assign(groups, 0);
    std::vector<char> touched(n, 0), crossed(n, 0);
    std::vector<glm::vec4> highest(boids.size());
    for (int i = 0; i < n; ++i) highest[i] = boids[i].position;
    CrowdSim sim(shaderDir, n);
    sim.upload(boids);
    for (int step = 0; step < steps; ++step) {
        sim.step(sdfTex);
        auto s = readBuffer<GpuBoid>(sim.currentStateBuffer(), n);
        for (int i = 0; i < n; ++i) {
            if (s[i].position.w == 0.0f) continue;   // evacuated through an avenue
            const int g = i / perGroup;
            r.nan |= hasNaN(s[i]);
            if ((fenceSide(s[i].position) > 0.0f) != (fenceSide(boids[i].position) > 0.0f)) {
                ++r.crossStepsPerGroup[g];
                if (!crossed[i]) { crossed[i] = 1; ++r.crossedAgentsPerGroup[g]; }
            }
            if (s[i].position.z > highest[i].z) highest[i] = s[i].position;
            if (sdFence(glm::vec3(s[i].position)) < 1e-4f && !touched[i]) { touched[i] = 1; ++r.touchedPerGroup[g]; }
        }
    }
    // Riding the fence would lift an agent above the floor under it; its highest point shows it
    for (int i = 0; i < n; ++i) r.maxRise = std::max(r.maxRise, aboveRest(highest[i]));
    return r;
}

// Group 0: 'perGroup' agents 1 mm outside the outer collision face (stand side); group 1: 1 mm
// inside the inner face (pitch side, where the router drives them into the fence every step).
// Spread along all four sides clear of the corners, moving into the fence at V_MAX.
std::vector<GpuBoid> faceScenario(int perGroup) {
    std::vector<GpuBoid> boids(2 * perGroup);
    for (int i = 0; i < perGroup; ++i) {
        int side = i % 4;
        float u = -0.8f + 1.6f * float(i / 4) / float(perGroup / 4 - 1);
        glm::vec2 nrm = side == 0 ? glm::vec2(0, 1) : side == 1 ? glm::vec2(1, 0) : side == 2 ? glm::vec2(0, -1) : glm::vec2(-1, 0);
        glm::vec2 along = glm::vec2(-nrm.y, nrm.x) * (u * FENCE_MID.x);
        glm::vec2 outside = FENCE_C + nrm * (FENCE_MID.x + FENCE_HALF_THK_COLL + 0.001f) + along;
        glm::vec2 inside = FENCE_C + nrm * (FENCE_MID.x - FENCE_HALF_THK_COLL - 0.001f) + along;
        boids[i] = { glm::vec4(outside, floorHeight(outside) + BODY_RADIUS, 1.0f), glm::vec4(-nrm * V_MAX, 0.0f, V_MAX) };
        boids[perGroup + i] = { glm::vec4(inside, floorHeight(inside) + BODY_RADIUS, 1.0f), glm::vec4(nrm * V_MAX, 0.0f, V_MAX) };
    }
    return boids;
}

// 'perCorner' agents per ring corner aimed diagonally at it at V_MAX: half from the stand side
// (group 0, all corners), half from the pitch side (group 1), spread +/-1 cm across the diagonal
// and each started 1 mm clear of its collision face.
std::vector<GpuBoid> cornerScenario(int perCorner) {
    const int half = perCorner / 2;
    std::vector<GpuBoid> boids(4 * perCorner);
    for (int c = 0; c < 4; ++c) {
        glm::vec2 sgn(c & 1 ? -1.0f : 1.0f, c & 2 ? -1.0f : 1.0f);
        glm::vec2 vertex = FENCE_C + sgn * FENCE_MID;
        glm::vec2 d = glm::normalize(sgn), e(-d.y, d.x);
        for (int k = 0; k < half; ++k) {
            float b = -0.01f + 0.02f * float(k) / float(half - 1);
            for (int grp = 0; grp < 2; ++grp) {
                float dir = grp == 0 ? 1.0f : -1.0f;   // +: beyond the corner (stand side), -: pitch side
                float a = FENCE_HALF_THK_COLL + 0.001f;
                glm::vec2 pos = vertex + d * (dir * a) + e * b;
                while (dir * sdBox2(pos - FENCE_C, FENCE_MID) < FENCE_HALF_THK_COLL + 0.001f) {
                    a += 0.0005f;
                    pos = vertex + d * (dir * a) + e * b;
                }
                boids[grp * 4 * half + c * half + k] = { glm::vec4(pos, floorHeight(pos) + BODY_RADIUS, 1.0f), glm::vec4(-dir * d * V_MAX, 0.0f, V_MAX) };
            }
        }
    }
    return boids;
}

// Copy of the shader directory with extra #defines inserted into physics.comp right after its
// #version line (after the generated preamble, so an #undef/#define pair overrides a preamble value)
fs::path makeShaderVariant(const fs::path& shaderDir, const std::string& name, const std::string& defines) {
    fs::path dir = processTempPath("swarm_shaders_" + name);
    fs::remove_all(dir);
    fs::create_directories(dir);
    for (const auto& e : fs::directory_iterator(shaderDir)) fs::copy_file(e.path(), dir / e.path().filename());
    std::string src;
    {
        std::ifstream in(dir / "physics.comp", std::ios::binary);
        std::stringstream ss;
        ss << in.rdbuf();
        src = ss.str();
    }
    src.insert(src.find('\n') + 1, defines);
    std::ofstream(dir / "physics.comp", std::ios::binary | std::ios::trunc) << src;
    return dir;
}

std::string dtOverride(float dt) {
    char b[96];
    std::snprintf(b, sizeof(b), "#undef DT\n#define DT %.9g\n", dt);
    return b;
}

std::string driveDir(glm::vec2 d) {
    char b[96];
    std::snprintf(b, sizeof(b), "#define TEST_DRIVE_DIR vec2(%.9g, %.9g)\n", d.x, d.y);
    return b;
}

// Stadium frame for one of the four avenues: 'out' along the avenue away from the pitch, 'lat'
// across it
struct Avenue { const char* name; glm::vec2 out, lat; };
const Avenue AVENUES[] = { { "+y", { 0, 1 }, { 1, 0 } }, { "-y", { 0, -1 }, { 1, 0 } },
                           { "+x", { 1, 0 }, { 0, 1 } }, { "-x", { -1, 0 }, { 0, 1 } } };

GpuBoid restingAgent(glm::vec2 xy, float extraHeight = 0.0f) {
    GpuBoid b;
    b.position = glm::vec4(xy, floorHeight(xy) + BODY_RADIUS + extraHeight, 1.0f);
    b.velocity = glm::vec4(0.0f);
    return b;
}

std::vector<GpuBoid> padInactive(std::vector<GpuBoid> boids) {
    size_t n = 256;
    while (n < boids.size()) n *= 2;
    GpuBoid parked;
    parked.position = glm::vec4(PARK_COORD, PARK_COORD, PARK_COORD, 0.0f);
    parked.velocity = glm::vec4(0.0f);
    boids.resize(n, parked);
    return boids;
}

// --- CPU reference (parity.*, perf.cpu_stage_timings) ---
using SortMode = CpuCrowdSim::SortMode;
constexpr SortMode SORT_MODES[] = { SortMode::Counting, SortMode::GpuBitonic };
const char* modeName(SortMode m) { return m == SortMode::Counting ? "counting" : "bitonic"; }

// --- Golden state (parity.golden_terrace): the pins live in golden_state.hpp, shared with tools/benchmark ---
using golden::GOLDEN;
using golden::GOLDEN_COUNT;
using golden::GOLDEN_DRIVER;
using golden::stateHash;

// --- CPU/GPU constant parity (parity.constants) ---
// A shared constant: the GLSL expression physics.comp evaluates and the value CpuCrowdSim uses in
// its place, as raw bits (floats) or as an integer
struct ParityEntry { std::string name, glsl; uint32_t cpuBits; bool isFloat, derived; };

uint32_t floatBits(float f) { uint32_t u; std::memcpy(&u, &f, sizeof u); return u; }
float bitsFloat(uint32_t u) { float f; std::memcpy(&f, &u, sizeof f); return f; }

std::vector<ParityEntry> parityEntries() {
    std::vector<ParityEntry> e;
    auto f = [&](const std::string& glsl, float cpu) { e.push_back({ glsl, glsl, floatBits(cpu), true, false }); };
    auto i = [&](const std::string& glsl, long long cpu) { e.push_back({ glsl, glsl, uint32_t(cpu), false, false }); };
    auto d = [&](const std::string& glsl, float cpu) { e.push_back({ glsl, glsl, floatBits(cpu), true, true }); };
    // Every constant of the generated preamble, read back through its macro
    i("GRID_RES", GRID_RES);
    f("DOMAIN_MIN", DOMAIN_MIN); f("DOMAIN_SPAN", DOMAIN_SPAN); f("DOMAIN_MAX", DOMAIN_MAX);
    i("SDF_RES", SDF_RES);
    f("R_PERC", R_PERC); i("PERC_RING", PERC_RING); f("K_SEP", K_SEP); f("DT", DT); f("V_MAX", V_MAX);
    f("GRAVITY", GRAVITY); f("TAU_RELAX", TAU_RELAX); f("T_HEADWAY", T_HEADWAY);
    f("W_OBS", W_OBS);
    f("GOAL_DEADZONE", GOAL_DEADZONE); f("TORSO_HEIGHT", TORSO_HEIGHT); f("OBSTACLE_RANGE", OBSTACLE_RANGE);
    f("OBSTACLE_GAIN", OBSTACLE_GAIN); f("OBSTACLE_MIN_NORMAL", OBSTACLE_MIN_NORMAL); f("OBSTACLE_GRAD_H", OBSTACLE_GRAD_H);
    f("SAFE_NORMALIZE_EPS", SAFE_NORMALIZE_EPS); f("SEP_STACKED_XY2", SEP_STACKED_XY2);
    f("PERSONAL_RADIUS", PERSONAL_RADIUS); f("BODY_RADIUS", BODY_RADIUS);
    f("PROJ_RELAX", PROJ_RELAX); f("PROJ_MAX_SHIFT_RADII", PROJ_MAX_SHIFT_RADII);
    i("FLOOR_SEARCH_CELLS", FLOOR_SEARCH_CELLS); f("FLOOR_SETTLE_RADII", FLOOR_SETTLE_RADII); f("FEELER_REACH_RADII", FEELER_REACH_RADII); i("FEELER_COUNT", FEELER_COUNT);
    for (int k = 0; k < FEELER_COUNT; ++k) {
        f("FEELER_DIRS[" + std::to_string(k) + "].x", FEELER_DIRS[size_t(k)].x);
        f("FEELER_DIRS[" + std::to_string(k) + "].y", FEELER_DIRS[size_t(k)].y);
    }
    i("WALL_ROOT_STEPS", WALL_ROOT_STEPS); i("WALL_RECAST_STEPS", WALL_RECAST_STEPS);
    f("WALL_RECAST_TOL_RADII", WALL_RECAST_TOL_RADII); f("WALL_MAX_NZ", WALL_MAX_NZ); i("WALL_PASSES", WALL_PASSES);
    f("CENTRE_GRAD_MIN", CENTRE_GRAD_MIN); i("STATIC_SWEEP_BISECTIONS", STATIC_SWEEP_BISECTIONS); f("PLANE_PROBE_RADII", PLANE_PROBE_RADII);
    // The step-up limit
    f("MAX_STEP_UP", MAX_STEP_UP); f("STEP_UP_TOL", STEP_UP_TOL); f("STEP_UP_FLOOR_REACH_RADII", STEP_UP_FLOOR_REACH_RADII);
    i("STEP_UP_BISECTIONS", STEP_UP_BISECTIONS); f("STEP_UP_SAMPLE_RADII", STEP_UP_SAMPLE_RADII); i("STEP_UP_MAX_SAMPLES", STEP_UP_MAX_SAMPLES);
    i("STEP_UP_SLIDE_TRIES", STEP_UP_SLIDE_TRIES);
    for (int k = 0; k < STEP_UP_SLIDE_TRIES; ++k) {
        f("STEP_UP_SLIDE_DIRS[" + std::to_string(k) + "].x", STEP_UP_SLIDE_DIRS[size_t(k)].x);
        f("STEP_UP_SLIDE_DIRS[" + std::to_string(k) + "].y", STEP_UP_SLIDE_DIRS[size_t(k)].y);
    }
    f("FENCE_CENTER.x", FENCE_CENTER.x); f("FENCE_CENTER.y", FENCE_CENTER.y);
    f("FENCE_HALF_MID.x", FENCE_HALF_MID.x); f("FENCE_HALF_MID.y", FENCE_HALF_MID.y);
    f("FENCE_HALF_THK_VISUAL", FENCE_HALF_THK_VISUAL); f("FENCE_HALF_THK_COLL", FENCE_HALF_THK_COLL);
    i("FENCE_CCD_BISECTIONS", FENCE_CCD_BISECTIONS);
    f("WALKWAY_MIN", WALKWAY_MIN); f("WALKWAY_MAX", WALKWAY_MAX); f("WALKWAY_CENTRE", WALKWAY_CENTRE);
    f("AVENUE_HALF", AVENUE_HALF); f("AISLE_MAX", AISLE_MAX); f("AISLE_CENTRE", AISLE_CENTRE);
    f("AVENUE_TARGET_DEPTH", AVENUE_TARGET_DEPTH); f("PITCH_RECOVERY_MARGIN", PITCH_RECOVERY_MARGIN);
    f("EXIT_DEPTH", EXIT_DEPTH); f("EXIT_MAX_Z", EXIT_MAX_Z); f("PARK_COORD", PARK_COORD);
    i("FENCE_GATE_COUNT", (long long)FENCE_GATES.size()); i("INACTIVE_CELL", INACTIVE_CELL);
    // Constant expressions physics.comp folds, against the value CpuCrowdSim uses in their place
    d("R_SEP", R_SEP);
    d("BODY_DIAM", BODY_DIAM);
    d("PROJ_MAX_SHIFT", PROJ_MAX_SHIFT);
    d("FLOOR_SETTLE_REACH", FLOOR_SETTLE_REACH);
    d("PLANE_PROBE_REACH", PLANE_PROBE_REACH);
    d("STEP_UP_FLOOR_REACH", STEP_UP_FLOOR_REACH);
    d("STEP_UP_SAMPLE", STEP_UP_SAMPLE);
    d("BODY_DIAM * BODY_DIAM", BODY_DIAM2);
    d("FEELER_REACH", FEELER_REACH);
    d("WALL_RECAST_TOL", WALL_RECAST_TOL);
    d("R_SEP * R_SEP", R_SEP2);
    d("R_PERC * R_PERC", R_PERC2);
    d("GRAVITY * DT", GRAVITY_DT);
    d("exp(-DT / TAU_RELAX)", RELAX_STEP);
    d("1.0 / T_HEADWAY", HEADWAY_RATE);
    d("0.25 / OBSTACLE_GRAD_H", OBSTACLE_GRAD_SCALE);
    d("WALKWAY_MIN + PITCH_RECOVERY_MARGIN", PITCH_RECOVERY_DEPTH);
    d("6.28318530718 / 4294967296.0", HASH_TO_RADIANS);
    d("float(SDF_RES) - 0.5", float(SDF_RES) - 0.5f);
    d("float(SDF_RES) - 1.0", float(SDF_RES) - 1.0f);
    for (int k = 0; k < FEELER_COUNT; ++k) {   // the feeler offsets are preamble arrays (sim_params.hpp feelerOffsets)
        f("FEELER_OFFSETS[" + std::to_string(k) + "].x", FEELER_OFFSETS[size_t(k)].x);
        f("FEELER_OFFSETS[" + std::to_string(k) + "].y", FEELER_OFFSETS[size_t(k)].y);
        f("PROBE_OFFSETS[" + std::to_string(k) + "].x", PROBE_OFFSETS[size_t(k)].x);
        f("PROBE_OFFSETS[" + std::to_string(k) + "].y", PROBE_OFFSETS[size_t(k)].y);
    }
    return e;
}

// Numeric literals in a line of GLSL (identifiers such as vec2 or FEELER_DIRS are skipped)
std::vector<double> numericLiterals(const std::string& s) {
    std::vector<double> out;
    for (size_t i = 0; i < s.size();) {
        const char c = s[i];
        if (std::isalpha((unsigned char)c) || c == '_') {
            while (i < s.size() && (std::isalnum((unsigned char)s[i]) || s[i] == '_')) ++i;
        } else if (std::isdigit((unsigned char)c) || c == '.' || (c == '-' && i + 1 < s.size() && (std::isdigit((unsigned char)s[i + 1]) || s[i + 1] == '.'))) {
            char* end = nullptr;
            out.push_back(std::strtod(s.c_str() + i, &end));
            i = size_t(end - s.c_str());
        } else {
            ++i;
        }
    }
    return out;
}

// 64-bit FNV-1a of the compute shaders the CPU reference ports, carriage returns removed (bitonic_sort_shared.comp: the same
// network, its j < 512 passes in shared memory; venue_seated.glsl: the analytic seated venue that src/venue.cpp ports)
uint64_t portedShadersHash(const fs::path& shaderDir) {
    uint64_t h = 0xcbf29ce484222325ull;
    for (const char* name : { "calc_grid.comp", "bitonic_sort.comp", "bitonic_sort_shared.comp", "reorder.comp", "physics.comp", "venue_seated.glsl" }) {
        std::ifstream in(shaderDir / name, std::ios::binary);
        if (!in) throw std::runtime_error(std::string("cannot read ") + name);
        for (char c; in.get(c);)
            if (c != '\r') { h ^= uint8_t(c); h *= 0x100000001b3ull; }
    }
    return h;
}

std::string cpuBrandString() {
#ifdef _MSC_VER
    int regs[4] = {};
    __cpuid(regs, int(0x80000000u));
    if (unsigned(regs[0]) < 0x80000004u) return "unknown";
    char brand[49] = {};
    for (int i = 0; i < 3; ++i) {
        __cpuid(regs, int(0x80000002u + i));
        std::memcpy(brand + 16 * i, regs, 16);
    }
    std::string s(brand);
    s.erase(0, s.find_first_not_of(' '));
    return s;
#else
    return "unknown";
#endif
}

std::string contactLabel(uint8_t c) {
    if (c == 0) return "none";
    std::string s;
    auto add = [&](uint8_t bit, const char* name) { if (c & bit) s += (s.empty() ? "" : "+") + std::string(name); };
    add(CpuCrowdSim::CONTACT_EXIT, "exit");
    add(CpuCrowdSim::CONTACT_FENCE_CCD, "fenceCCD");
    add(CpuCrowdSim::CONTACT_FENCE, "fence");
    add(CpuCrowdSim::CONTACT_FLOOR, "floor");
    add(CpuCrowdSim::CONTACT_WALL, "wall");
    add(CpuCrowdSim::CONTACT_AGENT, "agent");
    add(CpuCrowdSim::CONTACT_SWEEP, "sweep");
    add(CpuCrowdSim::CONTACT_STEP_UP, "stepUp");
    return s;
}

// One step from the same input on the GPU and on the CPU in both sort modes (parity.grid, parity.one_step)
struct EquivCase {
    int n = 0;
    std::string stateName;
    long active = 0;
    std::vector<GpuBoid> in, gpuOut;
    std::vector<GpuGridInfo> gpuGrid;   // sorted pairs of 'in'
    std::vector<GpuCellData> gpuCells;
    struct Cpu { std::vector<GpuBoid> out; std::vector<GpuGridInfo> grid; std::vector<GpuCellData> cells; std::vector<uint8_t> contacts; };
    Cpu cpu[2];                         // indexed like SORT_MODES
};

EquivCase runEquivCase(const fs::path& shaderDir, GLuint sdfTex, const std::vector<GpuBoid>& in, const std::string& stateName) {
    EquivCase c;
    c.n = int(in.size());
    c.stateName = stateName;
    c.in = in;
    for (const GpuBoid& b : in) c.active += b.position.w != 0.0f;
    CrowdSim gpu(shaderDir, c.n);
    gpu.upload(in);
    gpu.step(sdfTex);
    c.gpuOut = readBuffer<GpuBoid>(gpu.currentStateBuffer(), c.n);
    c.gpuGrid = readBuffer<GpuGridInfo>(gpu.gridBuffer(), c.n);
    c.gpuCells = readBuffer<GpuCellData>(gpu.cellBuffer(), size_t(GRID_RES) * GRID_RES);
    for (int m = 0; m < 2; ++m) {
        CpuCrowdSim cpu(sdfVolumeCPU(), 0, SORT_MODES[m]);
        cpu.setState(in);
        cpu.step();
        c.cpu[m] = { cpu.state(), cpu.grid(), cpu.cells(), cpu.contacts() };
    }
    return c;
}

struct Dist { float p50 = 0, p99 = 0, max = 0; };
Dist distribution(std::vector<float> v) {   // nearest-rank percentiles
    if (v.empty()) return {};
    std::sort(v.begin(), v.end());
    auto rank = [&](double p) { return v[std::max<size_t>(1, size_t(std::ceil(p * double(v.size())))) - 1]; };
    return { rank(0.50), rank(0.99), v.back() };
}

// Evacuation run with zone tables at checkpoints (parity.terrace_evacuation). stepAndRead advances one step and
// returns the new state.
using ZoneRow = std::array<int, ZONE_COUNT + 1>;   // active per zone, then active in total
struct EvacRun { int evacStep = -1; std::vector<ZoneRow> rows; long pitchAgentSteps = 0; bool nan = false; };

template <class StepAndRead>
EvacRun runEvacuation(const std::vector<int>& checkpoints, StepAndRead stepAndRead) {
    EvacRun r;
    for (int step = 1; step <= checkpoints.back(); ++step) {
        const std::vector<GpuBoid>& st = stepAndRead();
        ZoneRow row = {};
        for (const GpuBoid& b : st) {
            if (b.position.w == 0.0f) continue;
            ++row[zoneOf(b.position)];
            ++row[ZONE_COUNT];
            r.nan |= hasNaN(b);
            if (fenceSide(b.position) < 0.0f) ++r.pitchAgentSteps;
        }
        if (std::find(checkpoints.begin(), checkpoints.end(), step) != checkpoints.end()) r.rows.push_back(row);
        if (row[ZONE_COUNT] == 0) { r.evacStep = step; break; }
    }
    r.rows.resize(checkpoints.size(), ZoneRow{});   // checkpoints after the evacuation: nobody left
    return r;
}

} // namespace

// A navigation cache file through its reader (nav::CacheFileReader): it loads as written and saves back byte for byte (the format is
// unchanged), and any damage refuses it. loads(path): the load function's result; resave(path): the loaded table's save
template <class Loads, class Resave>
void checkCacheFile(const char* what, const fs::path& original, Loads loads, Resave resave) {
    const auto bytesOf = [](const fs::path& p) {
        std::string s(size_t(fs::file_size(p)), '\0');
        std::ifstream(p, std::ios::binary).read(s.data(), std::streamsize(s.size()));
        return s;
    };
    const fs::path dir = swarm::processTempPath("nav_cache_check");
    fs::create_directories(dir);
    const fs::path copy = dir / "copy.bin", again = dir / "again.bin";
    const std::string good = bytesOf(original);
    const auto loadsWith = [&](const std::string& content) {
        std::ofstream(copy, std::ios::binary | std::ios::trunc).write(content.data(), std::streamsize(content.size()));
        return loads(copy);
    };
    const auto flipped = [&](size_t at) {
        std::string b = good;
        b[at] = char(b[at] ^ 0x40);
        return b;
    };
    const bool intact = loadsWith(good);
    bool same = false;
    if (intact && resave(again)) same = bytesOf(again) == good;
    check(intact && same, std::string(what) + ": the file loads, and the loaded table saves back byte for byte (" + std::to_string(good.size()) + " bytes)");
    check(!loadsWith(flipped(0)) && !loadsWith(flipped(8)) && !loadsWith(flipped(good.size() / 2)) && !loadsWith(flipped(good.size() - 1)) &&
              !loadsWith(good.substr(0, good.size() - 1)) && !loadsWith(good.substr(0, 40)) && !loadsWith(good + "x") && !loadsWith(std::string()),
          std::string(what) + ": refused with a damaged magic, header, array or checksum, cut short, or with a byte too many");
    std::error_code ec;
    fs::remove_all(dir, ec);
}

int main(int argc, char** argv) {
#ifdef NDEBUG
    g_longTier = true;   // the long tier: default in Release, opt-in in Debug
#endif
    if (const char* env = std::getenv("SWARM_TEST_LONG"); env && *env) g_longTier = std::strcmp(env, "0") != 0;
    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "--long") == 0) g_longTier = true;
        else if (std::strcmp(argv[i], "--quick") == 0) g_longTier = false;
        else { std::printf("usage: test_gpu [--long | --quick]\n"); return 2; }
    }
    if (!glfwInit()) { std::printf("glfwInit failed\n"); return 2; }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow(64, 64, "test_gpu", nullptr, nullptr);
    if (!window) { std::printf("no OpenGL 4.3 core context\n"); return 2; }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { std::printf("glad failed\n"); return 2; }
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(onDebugMessage, nullptr);
    std::printf("test_gpu | commit %s (dirty %s) | %s\n", buildinfo::gitCommit(), buildinfo::gitDirtyField(), buildinfo::buildConfig());
    std::printf("GL %s | %s\n", (const char*)glGetString(GL_VERSION), (const char*)glGetString(GL_RENDERER));
    std::printf("test tier: %s\n", g_longTier ? "long (all checks)" : "quick (the long tier is skipped: --long or SWARM_TEST_LONG=1 runs it)");

    try {
        const fs::path shaderDir = resolveAsset("shaders");
        std::printf("assets: %s\n", shaderDir.parent_path().string().c_str());
        g_debug.enabled = true;

        section("engine.shaders_compile: Shader files compile and link with empty driver logs");
        std::printf("  generated preamble (inserted after #version in every shader):\n");
        std::istringstream pre(shaderPreamble());
        for (std::string line; std::getline(pre, line);) std::printf("    %s\n", line.c_str());
        {
            CerrCapture cap;
            GLuint boid = loadRenderProgram(shaderDir / "boid.vert", shaderDir / "boid.frag");
            GLuint stadium = loadRenderProgram(shaderDir / "stadium.vert", shaderDir / "stadium.frag");
            std::string log = cap.release();
            check(boid && stadium && log.empty(), "boid + stadium render programs" + (log.empty() ? std::string() : ":\n" + log));
            glDeleteProgram(boid);
            glDeleteProgram(stadium);
        }
        {
            CerrCapture cap;
            CrowdSim probeSim(shaderDir, 256);  // loads calc_grid, bitonic_sort, bitonic_sort_shared, reorder, physics
            std::string log = cap.release();
            check(log.empty(), "compute programs (calc_grid, bitonic_sort, bitonic_sort_shared, reorder, physics)" + (log.empty() ? std::string() : ":\n" + log));
        }
        {   // the same programs on venue S's preamble (its grid and exit test, the analytic venue, no router)
            CerrCapture cap;
            CrowdSim probeSim(shaderDir, 256, venueS());
            std::string log = cap.release();
            check(log.empty(), "compute programs on venue S's preamble (analytic seated venue)" + (log.empty() ? std::string() : ":\n" + log));
        }
        {   // venue S's programs with the queue-aware exit choice (its preamble; the choice pass, physics.comp PHYSICS_PASS 0)
            CerrCapture cap;
            ModelOptions qa;
            qa.exitChoice = ExitChoice::QueueAware;
            qa.inclineSpeed = true;
            CrowdSim probeSim(shaderDir, 256, venueS(), qa);
            std::string log = cap.release();
            check(log.empty(), "compute programs on venue S with the queue-aware exit choice (the choice pass included) and the incline speed" +
                  (log.empty() ? std::string() : ":\n" + log));
        }

        section("engine.shader_loader: Loader diagnostics");
        g_debug.enabled = false;  // the broken shader below is expected to produce driver messages
        {
            fs::path bad = processTempPath("swarm_broken_test.comp");
            { std::ofstream(bad) << "#version 430 core\nlayout(local_size_x = 1) in;\nvoid main() { undeclared_var = 1.0 }\n"; }
            CerrCapture cap;
            bool threw = false;
            try { loadComputeProgram(bad); } catch (const ShaderError&) { threw = true; }
            std::string log = cap.release();
            fs::remove(bad);
            check(threw && log.find("undeclared_var") != std::string::npos, "broken shader throws ShaderError after printing the driver log");
            bool line3 = log.find("0:3:") != std::string::npos || log.find("0(3)") != std::string::npos;
            check(line3, "driver reports the error on source line 3 despite the inserted preamble");
        }
        {
            bool threw = false;
            try { resolveAsset("does_not_exist.bin"); } catch (const std::runtime_error&) { threw = true; }
            check(threw, "missing asset throws with the searched paths");
        }
        g_debug.enabled = true;

        section("parity.sdf_sampling: SDF sampling (GPU map() from physics.comp vs CPU)");
        GLuint sdfTex = loadSDFTexture3D(resolveAsset("stadium.sdf"));
        check(sdfTex != 0, "stadium.sdf loaded");
        {
            GLuint probe = loadPhysicsBlockProbe(shaderDir, "// @sdf-begin", "// @sdf-end",
                "layout(local_size_x = 1) in;\n"
                "layout(std430, binding = 5) buffer P { vec4 pts[]; };\n"
                "layout(std430, binding = 6) buffer R { float outd[]; };\n"
                "void main() { uint i = gl_GlobalInvocationID.x; outd[i] = map(pts[i].xyz); }\n");
            std::vector<glm::vec3> pts = { {0, 0, 0.05f}, {0, 0, 0.1f}, {0, 0, 0.2f}, {0, 0, 0.3f}, {0, 0, 0.4f}, {0, 0, 0.5f},
                                           {0, 0, -0.1f}, {0.45f, 0.55f, 0.03f}, {0.45f, 0.55f, 0.08f} };
            std::vector<float> gpu = gpuSdfProbe(probe, sdfTex, pts);
            float maxDiff = 0.0f, maxZErr = 0.0f;
            for (size_t i = 0; i < pts.size(); ++i) maxDiff = std::max(maxDiff, std::abs(gpu[i] - sampleSDF_CPU(pts[i])));
            for (size_t i = 0; i < 6; ++i) maxZErr = std::max(maxZErr, std::abs(gpu[i] - pts[i].z));
            std::printf("  +Z probe:");
            for (size_t i = 0; i < 6; ++i) std::printf(" %.2f->%+.4f", pts[i].z, gpu[i]);
            std::printf("\n");
            check(maxZErr < 1e-3f, "vertical probe above the pitch equals height (max err " + std::to_string(maxZErr) + ")");
            check(gpu[6] < 0.0f && gpu[7] < 0.0f && gpu[8] > 0.0f, "underground and under-tread solid, above-tread free");
            check(maxDiff < 1e-4f, "CPU sampler matches GPU (max diff " + std::to_string(maxDiff) + ")");
            glDeleteProgram(probe);
        }
        {
            // floorUnder (the floor contact) vs the CPU bisection floorHeight, at centres that
            // dropped 1 mm under gravity below floor + BODY_RADIUS, all over the stadium
            GLuint probe = loadPhysicsBlockProbe(shaderDir, "// @sdf-begin", "// @sdf-end",
                "layout(local_size_x = 1) in;\n"
                "layout(std430, binding = 5) buffer P { vec4 pts[]; };\n"
                "layout(std430, binding = 6) buffer R { float outd[]; };\n"
                "void main() { uint i = gl_GlobalInvocationID.x; float z; outd[i] = floorUnder(pts[i].xyz, pts[i].z, z) ? z : -1.0; }\n");
            std::mt19937 rng(11);
            std::uniform_real_distribution<float> xy(-0.9f, 0.9f);
            std::vector<glm::vec3> pts;
            std::vector<float> cpu;
            while (pts.size() < 4096) {
                glm::vec2 q(xy(rng), xy(rng));
                if (sampleSDF_CPU(glm::vec3(q, 0.2f)) <= 0.0f) continue;   // under a roof or wall top
                float fl = floorHeight(q);
                pts.emplace_back(q, fl + BODY_RADIUS - 0.001f);
                cpu.push_back(fl);
            }
            std::vector<float> gpu = gpuSdfProbe(probe, sdfTex, pts);
            float maxDiff = 0.0f;
            int missed = 0;
            for (size_t i = 0; i < pts.size(); ++i) {
                if (gpu[i] == -1.0f) { ++missed; continue; }
                maxDiff = std::max(maxDiff, std::abs(gpu[i] - cpu[i]));
            }
            check(missed == 0 && maxDiff < 1e-5f, "floorUnder (texelFetch column) finds the CPU floor at 4096 random xy (max diff " +
                  std::to_string(maxDiff) + ", " + std::to_string(missed) + " missed)");
            glDeleteProgram(probe);
            // mapExactGrad (wall contacts) vs the CPU sampler at the same centres and 2 cm above:
            // the value, and the gradient vs central differences of the CPU sampler (h = 1e-4) at
            // points at least 2h from a voxel face, where the trilinear gradient is continuous.
            // Invocation i writes component i % 4 of point i / 4.
            probe = loadPhysicsBlockProbe(shaderDir, "// @sdf-begin", "// @sdf-end",
                "layout(local_size_x = 1) in;\n"
                "layout(std430, binding = 5) buffer P { vec4 pts[]; };\n"
                "layout(std430, binding = 6) buffer R { float outd[]; };\n"
                "void main() { uint i = gl_GlobalInvocationID.x; outd[i] = mapExactGrad(pts[i >> 2].xyz)[i & 3u]; }\n");
            const size_t n = pts.size();
            for (size_t i = 0; i < n; ++i) pts.push_back(pts[i] + glm::vec3(0.0f, 0.0f, 0.02f));
            const size_t m = pts.size();
            pts.resize(4 * m);
            gpu = gpuSdfProbe(probe, sdfTex, pts);
            pts.resize(m);
            float maxExact = 0.0f, maxGrad = 0.0f;
            int gradPoints = 0;
            const float h = 1e-4f;
            for (size_t i = 0; i < m; ++i) {
                const glm::vec4 g(gpu[4 * i], gpu[4 * i + 1], gpu[4 * i + 2], gpu[4 * i + 3]);
                maxExact = std::max(maxExact, std::abs(g.w - sampleSDF_CPU(pts[i])));
                const glm::vec3 f = (pts[i] - SDF_MIN) / SDF_SPACING, frac = f - glm::floor(f);
                if (glm::any(glm::lessThan(glm::min(frac, 1.0f - frac), glm::vec3(2.0f * h / SDF_SPACING)))) continue;
                glm::vec3 fd;
                for (int a = 0; a < 3; ++a) {
                    glm::vec3 e(0.0f);
                    e[a] = h;
                    fd[a] = (sampleSDF_CPU(pts[i] + e) - sampleSDF_CPU(pts[i] - e)) / (2.0f * h);
                }
                maxGrad = std::max(maxGrad, glm::length(glm::vec3(g) - fd));
                ++gradPoints;
            }
            check(maxExact < 1e-6f, "mapExactGrad value (texelFetch trilinear) matches the CPU sampler at " + std::to_string(m) +
                  " points (max diff " + std::to_string(maxExact) + ")");
            check(gradPoints > int(m / 2) && maxGrad < 2e-3f, "mapExactGrad gradient matches central differences of the CPU sampler at " +
                  std::to_string(gradPoints) + " points off voxel faces (max |diff| " + std::to_string(maxGrad) + ")");
            glDeleteProgram(probe);
        }

        section("parity.separation_kernel: Separation kernel: CPU mirror, then GPU block from physics.comp vs mirror");
        {
            const int samples = 1000;
            bool decreasing = true, oldIncreasing = true, finite = true;
            float prev = separationMagnitude(0.0f), prevOld = 0.0f, maxF = 0.0f;
            for (int i = 1; i <= samples; ++i) {
                float d = R_SEP * float(i) / float(samples + 1);   // 1000 points strictly inside (0, R_SEP)
                float f = separationMagnitude(d), fo = oldSeparationMagnitude(d);
                decreasing &= f < prev;
                oldIncreasing &= fo > prevOld;
                finite &= std::isfinite(f);
                maxF = std::max(maxF, f);
                prev = f;
                prevOld = fo;
            }
            float tail = separationMagnitude(R_SEP - 1e-6f);
            std::printf("  |F| at d/R_SEP = 0, 0.25, 0.5, 0.75, 0.999, 1:  new %.3f %.3f %.3f %.3f %.6f %.3f   old %.3f %.3f %.3f %.3f %.3f %.3f\n",
                        separationMagnitude(0.0f), separationMagnitude(0.25f * R_SEP), separationMagnitude(0.5f * R_SEP),
                        separationMagnitude(0.75f * R_SEP), separationMagnitude(0.999f * R_SEP), separationMagnitude(R_SEP),
                        oldSeparationMagnitude(0.0f), oldSeparationMagnitude(0.25f * R_SEP), oldSeparationMagnitude(0.5f * R_SEP),
                        oldSeparationMagnitude(0.75f * R_SEP), oldSeparationMagnitude(0.999f * R_SEP), oldSeparationMagnitude(R_SEP));
            std::printf("  (old kernel increasing over its whole support: %s)\n", oldIncreasing ? "yes, as reported" : "no");
            check(decreasing && finite, "|F| strictly decreasing on (0, R_SEP) at 1000 samples, bounded by K_SEP (max " + std::to_string(maxF) + ")");
            check(tail < 1e-3f, "|F(R_SEP - 1e-6)| = " + std::to_string(tail) + " < 1e-3 (C0 at the cutoff)");

            // GPU: the real kernel block, spliced out of physics.comp
            GLuint probe = loadPhysicsBlockProbe(shaderDir, "// @sep-kernel-begin", "// @sep-kernel-end",
                "layout(local_size_x = 64) in;\n"
                "struct Case { vec4 offset; uvec4 ids; };\n"
                "layout(std430, binding = 5) readonly buffer In { Case cases[]; };\n"
                "layout(std430, binding = 6) writeonly buffer Out { vec2 forces[]; };\n"
                "uniform int count;\n"
                "void main() { uint i = gl_GlobalInvocationID.x; if (i >= uint(count)) return;\n"
                "    forces[i] = separationForce(cases[i].offset.xyz, cases[i].ids.x, cases[i].ids.y); }\n");
            std::vector<KernelCase> cases;
            const glm::vec3 axis = glm::normalize(glm::vec3(1.0f, 2.0f, 0.5f));
            for (int i = 1; i <= samples; ++i) cases.push_back({ glm::vec4(axis * (R_SEP * float(i) / float(samples + 1)), 0.0f), glm::uvec4(3, 9, 0, 0) });
            const size_t special = cases.size();
            // stacked (xy = 0) and coincident pairs, both orders, plus just outside the support
            cases.push_back({ glm::vec4(0, 0, 0.001f, 0), glm::uvec4(7, 1234, 0, 0) });
            cases.push_back({ glm::vec4(0, 0, -0.001f, 0), glm::uvec4(1234, 7, 0, 0) });
            cases.push_back({ glm::vec4(0, 0, 0, 0), glm::uvec4(42, 43, 0, 0) });
            cases.push_back({ glm::vec4(0, 0, 0, 0), glm::uvec4(43, 42, 0, 0) });
            cases.push_back({ glm::vec4(R_SEP * 1.0001f, 0, 0, 0), glm::uvec4(1, 2, 0, 0) });
            std::vector<glm::vec2> gpu = gpuKernel(probe, cases);
            float maxDiff = 0.0f;
            bool gpuFinite = true;
            for (size_t i = 0; i < cases.size(); ++i) {
                glm::vec2 cpu = separationForce(glm::vec3(cases[i].offset), cases[i].ids.x, cases[i].ids.y);
                maxDiff = std::max(maxDiff, glm::length(gpu[i] - cpu));
                gpuFinite &= std::isfinite(gpu[i].x) && std::isfinite(gpu[i].y);
            }
            glm::vec2 s0 = gpu[special], s1 = gpu[special + 1], c0 = gpu[special + 2], c1 = gpu[special + 3];
            std::printf("  GPU stacked pair (dz = 1 mm): F_i = (%+.3f, %+.3f), F_j = (%+.3f, %+.3f); coincident: F_i = (%+.3f, %+.3f), F_j = (%+.3f, %+.3f)\n",
                        s0.x, s0.y, s1.x, s1.y, c0.x, c0.y, c1.x, c1.y);
            check(gpuFinite && maxDiff < 1e-3f, "GPU kernel matches CPU mirror on 1005 cases (max |diff| " + std::to_string(maxDiff) + "), all finite");
            check(glm::length(s0 + s1) < 1e-5f && glm::length(c0 + c1) < 1e-5f && glm::length(s0) > 1.0f && glm::length(c0) > 1.0f,
                  "stacked and coincident pairs get equal and opposite nonzero XY pushes");
            check(glm::length(gpu[special + 4]) == 0.0f, "zero force beyond R_SEP");
            glDeleteProgram(probe);

            // The hard-body contact correction from the same block vs its CPU mirror. Each member of
            // an isolated pair moves by its correction, the other by the opposite. Bodies are vertical disks: a pair
            // is in contact if |dz| < BODY_DIAM and its XY distance < BODY_DIAM, and one application must leave it
            // exactly BODY_DIAM apart in XY (so >= BODY_DIAM in 3D); zero correction otherwise.
            probe = loadPhysicsBlockProbe(shaderDir, "// @sep-kernel-begin", "// @sep-kernel-end",
                "layout(local_size_x = 64) in;\n"
                "struct Case { vec4 offset; uvec4 ids; };\n"
                "layout(std430, binding = 5) readonly buffer In { Case cases[]; };\n"
                "layout(std430, binding = 6) writeonly buffer Out { vec2 forces[]; };\n"
                "uniform int count;\n"
                "void main() { uint i = gl_GlobalInvocationID.x; if (i >= uint(count)) return;\n"
                "    forces[i] = contactCorrection(cases[i].offset.xyz, cases[i].ids.x, cases[i].ids.y); }\n");
            std::vector<KernelCase> ccases;
            for (int i = 1; i <= samples; ++i) {   // XY distance 0 .. 1.2 BODY_DIAM, vertical offset -1.2 .. 1.2 BODY_DIAM
                const float dxy = 1.2f * BODY_DIAM * float(i) / float(samples + 1), dz = 1.2f * BODY_DIAM * (float(i % 21) / 10.0f - 1.0f);
                const float ang = 0.37f * float(i);
                ccases.push_back({ glm::vec4(dxy * std::cos(ang), dxy * std::sin(ang), dz, 0.0f), glm::uvec4(5, 77, 0, 0) });
            }
            const size_t cspecial = ccases.size();
            ccases.push_back({ glm::vec4(0, 0, 0.001f, 0), glm::uvec4(7, 1234, 0, 0) });    // stacked, both orders
            ccases.push_back({ glm::vec4(0, 0, -0.001f, 0), glm::uvec4(1234, 7, 0, 0) });
            ccases.push_back({ glm::vec4(0, 0, 0, 0), glm::uvec4(42, 43, 0, 0) });          // coincident, both orders
            ccases.push_back({ glm::vec4(0, 0, 0, 0), glm::uvec4(43, 42, 0, 0) });
            ccases.push_back({ glm::vec4(BODY_DIAM * 1.0001f, 0, 0, 0), glm::uvec4(1, 2, 0, 0) });
            const std::vector<glm::vec2> cg = gpuKernel(probe, ccases);
            float cMaxDiff = 0.0f, resolveErr = 0.0f;
            bool outsideZero = true;
            for (size_t i = 0; i < ccases.size(); ++i) {
                const glm::vec3 off(ccases[i].offset);
                const glm::vec2 cpu = contactCorrection(off, ccases[i].ids.x, ccases[i].ids.y);
                cMaxDiff = std::max(cMaxDiff, glm::length(cg[i] - cpu));
                if (std::abs(off.z) >= BODY_DIAM || glm::length(glm::vec2(off)) >= BODY_DIAM) { outsideZero &= cg[i] == glm::vec2(0.0f); continue; }
                const glm::vec2 after = glm::vec2(off) + 2.0f * cg[i];
                resolveErr = std::max(resolveErr, std::abs(glm::length(after) - BODY_DIAM));
            }
            const glm::vec2 cs0 = cg[cspecial], cs1 = cg[cspecial + 1], cc0 = cg[cspecial + 2], cc1 = cg[cspecial + 3];
            std::printf("  contact correction (BODY_DIAM %.4f): GPU vs CPU mirror max |diff| %.2e over %zu cases; an isolated pair after one\n"
                        "  correction is BODY_DIAM apart in XY within %.2e; stacked (dz = 1 mm) %.5f each, coincident %.5f each\n",
                        BODY_DIAM, cMaxDiff, ccases.size(), resolveErr, glm::length(cs0), glm::length(cc0));
            check(cMaxDiff < 1e-7f && resolveErr < 1e-6f && outsideZero && glm::length(cg[cspecial + 4]) == 0.0f,
                  "hard-body contact correction: GPU matches the CPU mirror, restores the XY distance BODY_DIAM in one application for |dz| < BODY_DIAM, zero otherwise");
            check(glm::length(cs0 + cs1) < 1e-7f && glm::length(cc0 + cc1) < 1e-7f && glm::length(cs0) > 0.4f * BODY_DIAM && glm::length(cc0) > 0.4f * BODY_DIAM,
                  "stacked and coincident pairs get equal and opposite XY corrections along their hash direction");
            glDeleteProgram(probe);
        }

        section("physics.stacked_pair: Stacked pair across z = 0.05: one real pipeline step");
        {
            std::vector<GpuBoid> boids(256);
            for (GpuBoid& b : boids) { b.position = glm::vec4(PARK_COORD, PARK_COORD, PARK_COORD, 0.0f); b.velocity = glm::vec4(0.0f); }
            boids[0].position = glm::vec4(0.1f, 0.1f, 0.0495f, 1.0f);
            boids[1].position = glm::vec4(0.1f, 0.1f, 0.0505f, 1.0f);
            CrowdSim sim(shaderDir, 256);
            sim.upload(boids);
            sim.step(sdfTex);
            auto s = readBuffer<GpuBoid>(sim.currentStateBuffer(), 256);
            auto g = readBuffer<GpuGridInfo>(sim.gridBuffer(), 256);
            uint32_t cell0 = 0, cell1 = 0;
            for (const GpuGridInfo& e : g) { if (e.boidID == 0) cell0 = e.gridID; if (e.boidID == 1) cell1 = e.gridID; }
            glm::vec2 gap = glm::vec2(s[0].position) - glm::vec2(s[1].position);
            std::printf("  cells: agent 0 -> %u, agent 1 -> %u (2D column hash: z ignored); xy gap after 1 step = %.6f\n",
                        cell0, cell1, glm::length(gap));
            check(cell0 == cell1, "both agents hashed to the same column cell");
            check(!hasNaN(s[0]) && !hasNaN(s[1]) && glm::length(gap) > 1e-5f && glm::dot(gap, pairDirection(0, 1)) > 0.0f,
                  "nonzero, finite separation along the pair direction after 1 step");
        }

        section("parity.fence_sdf: Pitch fence SDF: CPU mirror (a) and GPU @fence block vs CPU (b)");
        std::printf("  FENCE_HALF_MID %.7f, visual half-thickness %.7f, collision half-thickness %.7f (%.2fx visual), gates %zu\n",
                    FENCE_HALF_MID.x, FENCE_HALF_THK_VISUAL, FENCE_HALF_THK_COLL, FENCE_HALF_THK_COLL / FENCE_HALF_THK_VISUAL, FENCE_GATES.size());
        {
            float midMax = -1e9f;
            for (int i = 0; i < 4000; ++i) midMax = std::max(midMax, sdFence(glm::vec3(fenceMidlinePoint(4.0f * i / 4000.0f), 0.02f)));
            check(midMax < 0.0f, "sdFence < 0 along the whole midline (max " + std::to_string(midMax) + ")");

            float atCentre = sdFence(glm::vec3(FENCE_C, 0.0f));
            float innerFace = std::min(FENCE_MID.x, FENCE_MID.y) - FENCE_HALF_THK_COLL;
            check(std::abs(atCentre - innerFace) < 1e-5f, "sdFence at the pitch centre = distance to the inner collision face (" +
                  std::to_string(atCentre) + " vs " + std::to_string(innerFace) + ")");

            std::mt19937 rng(7);
            std::uniform_real_distribution<float> uxy(-0.6f, 0.6f), uz(-0.1f, 0.5f);
            float maxUnitErr = 0.0f, maxFdErr = 0.0f;
            bool allHorizontal = true;
            int tested = 0;
            for (int i = 0; i < 20000; ++i) {
                glm::vec3 p(uxy(rng), uxy(rng), uz(rng));
                glm::vec3 g = sdFenceGradient(p);
                allHorizontal &= g.z == 0.0f;
                if (nearFenceKink(glm::vec2(p))) continue;
                ++tested;
                const float h = 1e-4f;
                glm::vec2 fd((sdFence(p + glm::vec3(h, 0, 0)) - sdFence(p - glm::vec3(h, 0, 0))) / (2 * h),
                             (sdFence(p + glm::vec3(0, h, 0)) - sdFence(p - glm::vec3(0, h, 0))) / (2 * h));
                maxUnitErr = std::max(maxUnitErr, std::abs(glm::length(g) - 1.0f));
                maxFdErr = std::max(maxFdErr, glm::length(glm::vec2(g) - fd));
            }
            check(maxUnitErr < 1e-3f && maxFdErr < 1e-3f, "|grad| = 1 and matches central differences away from corners/kinks (" +
                  std::to_string(tested) + " points; max |len-1| " + std::to_string(maxUnitErr) + ", max |grad-fd| " + std::to_string(maxFdErr) + ")");
            check(allHorizontal, "grad.z == 0 at all 20000 points");

            // b) the real @fence block from physics.comp on the GPU
            GLuint probe = loadPhysicsBlockProbe(shaderDir, "// @fence-begin", "// @fence-end",
                "layout(local_size_x = 64) in;\n"
                "layout(std430, binding = 5) readonly buffer P { vec4 pts[]; };\n"
                "layout(std430, binding = 6) writeonly buffer R { vec4 res[]; };\n"
                "uniform int count;\n"
                "void main() { uint i = gl_GlobalInvocationID.x; if (i >= uint(count)) return;\n"
                "    vec3 p = pts[i].xyz; res[i] = vec4(sdFence(p), sdFenceGradient(p)); }\n");
            std::vector<glm::vec4> pts;
            std::uniform_real_distribution<float> band(-0.05f, 0.05f), u4(0.0f, 4.0f);
            for (int i = 0; i < 500; ++i) {  // half near the fence, half anywhere
                glm::vec2 m = fenceMidlinePoint(u4(rng));
                glm::vec2 outward = glm::abs(m.x - FENCE_C.x) >= glm::abs(m.y - FENCE_C.y) ? glm::vec2(glm::sign(m.x - FENCE_C.x), 0) : glm::vec2(0, glm::sign(m.y - FENCE_C.y));
                pts.emplace_back(m + outward * band(rng), uz(rng), 0.0f);
            }
            for (int i = 0; i < 500; ++i) pts.emplace_back(uxy(rng), uxy(rng), uz(rng), 0.0f);
            std::vector<glm::vec4> gpu = gpuVec4Probe(probe, pts);
            float maxD = 0.0f, maxG = 0.0f;
            for (size_t i = 0; i < pts.size(); ++i) {
                glm::vec3 p(pts[i]);
                maxD = std::max(maxD, std::abs(gpu[i].x - sdFence(p)));
                if (!nearFenceKink(glm::vec2(p))) maxG = std::max(maxG, glm::length(glm::vec3(gpu[i].y, gpu[i].z, gpu[i].w) - sdFenceGradient(p)));
            }
            check(maxD < 1e-5f, "GPU sdFence matches CPU at 1000 points (max |diff| " + std::to_string(maxD) + ")");
            check(maxG < 1e-5f, "GPU sdFenceGradient matches CPU away from kinks (max |diff| " + std::to_string(maxG) + ")");
            glDeleteProgram(probe);
        }

        section("physics.fence_ccd: Fence tunneling with CCD: agents driven into the fence at V_MAX, 500 steps");
        // 256 on the stand side as specified, plus 256 on the pitch side: the router sends pitch
        // agents to an avenue mouth across the fence, so those push into it on every step.
        const std::vector<GpuBoid> faceAgents = faceScenario(256);
        std::printf("  collision half-thickness %.7f (visual + BODY_RADIUS) vs step V_MAX*DT %.4f\n", FENCE_HALF_THK_COLL, V_MAX * DT);
        {
            FenceRun r = runFenceScenario(shaderDir, sdfTex, faceAgents, 2, 500);
            std::printf("  agents that reached the collision face: stand side %ld/256, pitch side %ld/256\n", r.touchedPerGroup[0], r.touchedPerGroup[1]);
            check(r.touchedPerGroup[0] > 0 && r.touchedPerGroup[1] > 0, "test is not vacuous: agents in both groups were pressed onto the fence");
            check(r.crossStepsPerGroup[0] == 0 && r.crossStepsPerGroup[1] == 0 && !r.nan, "no agent changes side of the fence midline (stand side " +
                  std::to_string(r.crossStepsPerGroup[0]) + ", pitch side " + std::to_string(r.crossStepsPerGroup[1]) + " agent-steps)");
            check(r.maxRise <= 0.001f, "no fence riding: max height above floor + BODY_RADIUS at each agent's highest point " + std::to_string(r.maxRise));
            if (FENCE_GATES.empty()) std::printf("  gate pass-through test: not applicable, the measured fence has no gates\n");
        }

        section("physics.fence_ccd_needed: CCD non-vacuity: tunneling without CCD once a step exceeds the collision half-thickness");
        {
            auto report = [](const char* what, const FenceRun& r) {
                std::printf("  %-36s far side: stand %ld/256 (%ld agent-steps), pitch %ld/256 (%ld agent-steps)\n", what,
                            r.crossedAgentsPerGroup[0], r.crossStepsPerGroup[0], r.crossedAgentsPerGroup[1], r.crossStepsPerGroup[1]);
            };
            // At DT the half-thickness exceeds one step, so thickness alone already holds (reported);
            // at 2*DT a step (V_MAX*2*DT) is longer than the half-thickness and only CCD can stop it.
            // Driven along +y (TEST_DRIVE_DIR), so the -y side's stand group and the +y side's pitch group
            // walk into the fence at full speed; the router would not ram them into it (the headway rule slows an
            // agent behind the one across the fence, and the stand group's goal runs along the walkway)
            const float dt2 = 2.0f * DT;
            const std::string drive = driveDir(glm::vec2(0.0f, 1.0f));
            fs::path noCcd = makeShaderVariant(shaderDir, "no_ccd", "#define DISABLE_FENCE_CCD\n" + drive);
            fs::path noCcd2 = makeShaderVariant(shaderDir, "no_ccd_dt2", "#define DISABLE_FENCE_CCD\n" + drive + dtOverride(dt2));
            fs::path ccd2 = makeShaderVariant(shaderDir, "ccd_dt2", drive + dtOverride(dt2));
            FenceRun a = runFenceScenario(noCcd, sdfTex, faceAgents, 2, 500);
            FenceRun b = runFenceScenario(noCcd2, sdfTex, faceAgents, 2, 500);
            FenceRun c = runFenceScenario(ccd2, sdfTex, faceAgents, 2, 500);
            for (const fs::path& d : { noCcd, noCcd2, ccd2 }) fs::remove_all(d);
            std::printf("  step at 2*DT: %.4f > half-thickness %.7f\n", V_MAX * dt2, FENCE_HALF_THK_COLL);
            report("CCD off, DT (thickness holds):", a);
            report("CCD off, 2*DT:", b);
            report("CCD on,  2*DT:", c);
            check(b.crossedAgentsPerGroup[0] + b.crossedAgentsPerGroup[1] > 0, "without CCD agents tunnel once a step exceeds the half-thickness");
            check(c.crossStepsPerGroup[0] == 0 && c.crossStepsPerGroup[1] == 0 && !c.nan && c.touchedPerGroup[0] > 0 && c.touchedPerGroup[1] > 0,
                  "with CCD, same 2*DT scenario: zero crossings with both groups pressed onto the fence, so CCD is what stops them");
        }

        section("physics.fence_corners: Ring corners: 64 agents per corner aimed diagonally at V_MAX, 500 steps");
        {
            FenceRun r = runFenceScenario(shaderDir, sdfTex, cornerScenario(64), 2, 500);
            std::printf("  agents that reached the collision face: stand side %ld/128, pitch side %ld/128\n", r.touchedPerGroup[0], r.touchedPerGroup[1]);
            check(r.touchedPerGroup[0] > 0 && r.touchedPerGroup[1] > 0, "test is not vacuous: agents on both sides reached the corners' faces");
            check(r.crossStepsPerGroup[0] == 0 && r.crossStepsPerGroup[1] == 0 && !r.nan, "zero crossings at the corners (stand side " +
                  std::to_string(r.crossStepsPerGroup[0]) + ", pitch side " + std::to_string(r.crossStepsPerGroup[1]) + " agent-steps)");
            check(r.maxRise <= 0.001f, "no fence riding at the corners: max height above floor + BODY_RADIUS " + std::to_string(r.maxRise));
        }

        section("physics.rest_height: Rest height: no goal force, 200 steps; centre vs floor + BODY_RADIUS per surface");
        {
            enum Surface { S_TREAD, S_AISLE, S_WALKWAY, S_AVENUE, S_GROUND, S_COUNT };
            const char* names[S_COUNT] = { "tread (mid-tread)", "aisle (centreline)", "walkway (dep 0.38)", "avenue (lat 0)", "ground plane (pitch)" };
            const float treadMid[] = { 0.4485f, 0.4950f, 0.5425f, 0.5890f, 0.6360f, 0.6835f, 0.7305f };
            std::vector<GpuBoid> boids;
            std::vector<int> surface;
            auto add = [&](glm::vec2 xy, int s) { boids.push_back(restingAgent(xy, 0.003f)); surface.push_back(s); };  // dropped from 3 mm
            for (const Avenue& a : AVENUES) {   // agents >= 0.05 apart: no agent-agent interaction
                for (float d : treadMid) add(a.lat * 0.30f + a.out * d, S_TREAD);
                for (int k = 0; k < 7; ++k) add(a.lat * 0.13f + a.out * (0.45f + 0.05f * k), S_AISLE);
                for (float lat : { -0.25f, -0.15f, 0.15f, 0.25f }) add(a.lat * lat + a.out * 0.38f, S_WALKWAY);
                for (int k = 0; k < 5; ++k) add(a.out * (0.45f + 0.10f * k), S_AVENUE);
            }
            for (int i = -2; i <= 2; ++i) for (int j = -2; j <= 2; ++j) add(glm::vec2(0.1f * i, 0.1f * j), S_GROUND);
            const std::vector<GpuBoid> all = padInactive(boids);
            fs::path noGoal = makeShaderVariant(shaderDir, "no_goal", "#define TEST_NO_GOAL\n");
            CrowdSim sim(noGoal, int(all.size()));
            fs::remove_all(noGoal);
            sim.upload(all);
            for (int i = 0; i < 200; ++i) sim.step(sdfTex);
            auto s = readBuffer<GpuBoid>(sim.currentStateBuffer(), all.size());
            float maxDev[S_COUNT] = {};
            int count[S_COUNT] = {}, lost = 0;
            for (size_t i = 0; i < boids.size(); ++i) {
                if (s[i].position.w == 0.0f || hasNaN(s[i])) { ++lost; continue; }
                float dev = s[i].position.z - (floorHeight(glm::vec2(s[i].position)) + BODY_RADIUS);
                maxDev[surface[i]] = std::max(maxDev[surface[i]], std::abs(dev));
                ++count[surface[i]];
            }
            bool ok = lost == 0;
            for (int k = 0; k < S_COUNT; ++k) {
                std::printf("  %-22s %3d agents, max |z - (floor + BODY_RADIUS)| = %.3e\n", names[k], count[k], maxDev[k]);
                ok &= maxDev[k] < 1e-4f;
            }
            check(ok, "every agent rests within 1e-4 of floor + BODY_RADIUS on every surface type (" + std::to_string(lost) + " lost)");
        }

        section("physics.wall_hold: Wall hold: 256 agents driven at V_MAX into walls and the fence, 200 steps");
        {
            enum Group { G_OUTER, G_SIDE_AVE, G_SIDE_AISLE, G_FENCE_OUT, G_FENCE_IN, G_COUNT };
            const char* names[G_COUNT] = { "outer wall (from the platform)", "aisle side wall, avenue side", "aisle side wall, aisle side",
                                           "fence, stand side", "fence, pitch side" };
            float minClear[G_COUNT], minD[G_COUNT];
            int pressed[G_COUNT] = {}, total[G_COUNT] = {};
            std::fill(std::begin(minClear), std::end(minClear), 1e9f);
            std::fill(std::begin(minD), std::end(minD), 1e9f);
            long fenceCrossings = 0;
            bool nan = false;
            for (glm::vec2 D : { glm::vec2(0, 1), glm::vec2(0, -1), glm::vec2(1, 0), glm::vec2(-1, 0) }) {
                const glm::vec2 e(std::abs(D.y), std::abs(D.x));   // across the drive direction
                std::vector<GpuBoid> boids;
                std::vector<int> group;
                // Every agent starts at V_MAX towards its wall. From rest, the torso-height obstacle
                // avoidance holds some aisle agents ~1.4 cm off the aisle wall, short of BODY_RADIUS + 1e-3
                // (the pressed criterion).
                auto add = [&](glm::vec2 xy, int g) {
                    GpuBoid b = restingAgent(xy);
                    b.velocity = glm::vec4(D * V_MAX, 0.0f, V_MAX);
                    boids.push_back(b);
                    group.push_back(g);
                };
                for (int k = 0; k < 8; ++k) for (float sgn : { -1.0f, 1.0f }) add(D * 0.88f + e * (sgn * (0.15f + 0.1f * k)), G_OUTER);
                for (int k = 0; k < 6; ++k) for (float sgn : { -1.0f, 1.0f }) {
                    float along = sgn * (0.45f + 0.05f * k);
                    add(e * along + D * 0.05f, G_SIDE_AVE);      // inside a crossing avenue, below its side wall
                    add(e * along - D * 0.13f, G_SIDE_AISLE);    // in the aisle behind the opposite side wall
                }
                for (int k = 0; k < 12; ++k) {
                    float lat = -0.275f + 0.05f * k;
                    add(e * lat - D * 0.38f, G_FENCE_OUT);        // walkway, heading for the fence
                    add(e * lat + D * 0.25f, G_FENCE_IN);         // pitch, heading for the fence
                }
                const std::vector<GpuBoid> all = padInactive(boids);
                fs::path drive = makeShaderVariant(shaderDir, "drive", driveDir(D));
                CrowdSim sim(drive, int(all.size()));
                fs::remove_all(drive);
                sim.upload(all);
                std::vector<char> wasPressed(boids.size(), 0);
                for (int step = 0; step < 200; ++step) {
                    sim.step(sdfTex);
                    auto s = readBuffer<GpuBoid>(sim.currentStateBuffer(), all.size());
                    for (size_t i = 0; i < boids.size(); ++i) {
                        if (s[i].position.w == 0.0f) continue;
                        nan |= hasNaN(s[i]);
                        const int g = group[i];
                        const glm::vec3 c(s[i].position);
                        const float d = sceneRawCPU(c), cap = BODY_RADIUS + 2e-3f;
                        // |grad| <= 1: an SDF value >= cap already guarantees the clearance. Walls only
                        // (plausibility::detail::isWallHit, the physics' classification); with the 6.4 mm body the
                        // centre's plane is low enough for the fan to reach walkable slopes between aisle sub-steps
                        float clear = d >= cap ? cap : wallFanClearance(c, cap, D);
                        minClear[g] = std::min(minClear[g], clear);
                        minD[g] = std::min(minD[g], d);
                        // pressed (non-vacuity): against any surface in the fan, a wall or a blocking aisle step
                        if (std::min(clear, d >= cap ? cap : horizontalClearance(c, cap, D)) < BODY_RADIUS + 1e-3f) wasPressed[i] = 1;
                        if ((fenceSide(s[i].position) > 0.0f) != (fenceSide(boids[i].position) > 0.0f)) ++fenceCrossings;
                    }
                }
                for (size_t i = 0; i < boids.size(); ++i) { ++total[group[i]]; pressed[group[i]] += wasPressed[i]; }
            }
            bool holds = !nan, allPressed = true;
            for (int g = 0; g < G_COUNT; ++g) {
                std::printf("  %-32s pressed %2d/%2d | min horizontal clearance %.6f | min SDF value at the centre %.6f\n",
                            names[g], pressed[g], total[g], minClear[g], minD[g]);
                // The plausibility check's wall tolerance (plausibility::WALL_TOL, 3e-4): with
                // the driving term agents slide along the aisle side walls to their convex ends at the walkway (dep
                // 0.4225), where the feelers' foot point lies up to 2.4e-4 beyond the true nearest surface
                holds &= minClear[g] >= BODY_RADIUS - swarm::plausibility::WALL_TOL;
                allPressed &= pressed[g] == total[g];
            }
            std::printf("  horizontal clearance: distance from the centre to the nearest wall surface in the centre's plane (\n"
                        "  walls only, n_z <= 0.5 and a body diameter tall (plausibility.hpp); not the walkable slopes between aisle\n"
                        "  sub-steps), min over a +/-40 degree fan around the drive direction, after every step. The SDF value is\n"
                        "  for reference only: the baked field is not a unit-gradient distance (|grad| 0.4-0.9), and at\n"
                        "  the centre it is the floor's (a vertical clearance of BODY_RADIUS reads below BODY_RADIUS)\n");
            check(allPressed, "test is not vacuous: every agent was pressed against its wall");
            check(holds, "min horizontal clearance >= BODY_RADIUS - 3e-4 (plausibility::WALL_TOL) for every group");
            check(fenceCrossings == 0, "zero fence midline crossings (" + std::to_string(fenceCrossings) + " agent-steps)");
        }

        section("physics.aisle_tread_step: Aisle-to-tread step: 64 agents driven from the aisle across it at V_MAX");
        {
            // Mesh: beside each tread the aisle descends in 4.4 mm sub-steps, so the step up from the
            // aisle onto the tread is 0, 4.4, 8.8 or 13.2 mm depending on depth
            std::printf("  step heights in the mesh: 0 / 4.4 / 8.8 / 13.2 mm; BODY_RADIUS = %.1f mm\n", BODY_RADIUS * 1000.0f);
            struct Probe { float stepH, nzAtContact; bool climbed; };
            std::vector<Probe> probes;
            for (float sgnX : { 1.0f, -1.0f }) {
                std::vector<GpuBoid> boids;
                for (float sgnY : { 1.0f, -1.0f })
                    for (int k = 0; k < 16; ++k) boids.push_back(restingAgent(glm::vec2(sgnX * 0.13f, sgnY * (0.43f + 0.02f * k))));
                const std::vector<GpuBoid> all = padInactive(boids);
                fs::path drive = makeShaderVariant(shaderDir, "drive", driveDir(glm::vec2(sgnX, 0.0f)));
                CrowdSim sim(drive, int(all.size()));
                fs::remove_all(drive);
                sim.upload(all);
                std::vector<float> maxLat(boids.size(), 0.0f);
                for (int step = 0; step < 20; ++step) {
                    sim.step(sdfTex);
                    auto s = readBuffer<GpuBoid>(sim.currentStateBuffer(), all.size());
                    for (size_t i = 0; i < boids.size(); ++i) maxLat[i] = std::max(maxLat[i], std::abs(s[i].position.x));
                }
                for (size_t i = 0; i < boids.size(); ++i) {
                    glm::vec2 xy(boids[i].position);
                    float aisleFloor = floorHeight(xy), treadFloor = floorHeight(glm::vec2(sgnX * 0.17f, xy.y));
                    // Contact as physics sees it: the first surface along the drive direction in the
                    // centre's plane (aisle floor + BODY_RADIUS), and its normal there. None if the
                    // step stays below that plane.
                    glm::vec3 c(xy, aisleFloor + BODY_RADIUS), dir(sgnX, 0.0f, 0.0f);
                    float t = rayToSurface(c, dir, 0.06f);
                    float nz = 2.0f;
                    if (t < 0.06f) {
                        glm::vec3 q = c + dir * t;
                        const float h = 0.0015f;
                        glm::vec3 g((sampleSDF_CPU(q + glm::vec3(h, 0, 0)) - sampleSDF_CPU(q - glm::vec3(h, 0, 0))),
                                    (sampleSDF_CPU(q + glm::vec3(0, h, 0)) - sampleSDF_CPU(q - glm::vec3(0, h, 0))),
                                    (sampleSDF_CPU(q + glm::vec3(0, 0, h)) - sampleSDF_CPU(q - glm::vec3(0, 0, h))));
                        nz = glm::normalize(g).z;
                    }
                    probes.push_back({ treadFloor - aisleFloor, nz, maxLat[i] > 0.156f });
                }
            }
            struct Bucket { const char* name; float lo, hi; int climbed = 0, blocked = 0, noContact = 0; float minNz = 1, maxNz = -1; };
            Bucket buckets[] = { { "< 2 mm", -1, 0.002f }, { "2 - 6 mm", 0.002f, 0.006f }, { "6 - 10 mm", 0.006f, 0.010f }, { ">= 10 mm", 0.010f, 1 } };
            int climbed = 0;
            for (const Probe& p : probes) {
                climbed += p.climbed;
                for (Bucket& b : buckets) if (p.stepH >= b.lo && p.stepH < b.hi) {
                    (p.climbed ? b.climbed : b.blocked)++;
                    if (p.nzAtContact > 1.0f) { ++b.noContact; continue; }
                    b.minNz = std::min(b.minNz, p.nzAtContact);
                    b.maxNz = std::max(b.maxNz, p.nzAtContact);
                }
            }
            std::printf("  %-10s %8s %8s  contact in the centre's plane: none (step below it) | n_z range (<= 0.6: wall)\n", "SDF step", "climbed", "blocked");
            for (const Bucket& b : buckets) {
                if (!(b.climbed + b.blocked)) continue;
                std::printf("  %-10s %8d %8d  none %2d", b.name, b.climbed, b.blocked, b.noContact);
                if (b.noContact < b.climbed + b.blocked) std::printf(" | %.3f .. %.3f", b.minNz, b.maxNz);
                std::printf("\n");
            }
            std::printf("  outcome: %d/64 climbed onto the tread (floor contact), %d/64 blocked (wall contact)\n", climbed, 64 - climbed);
        }

        section("venue.terrace_spawn: Spawn on the measured treads");
        std::vector<GpuBoid> spawn = spawnBleacherCrowd(NUM_AGENTS);
        {
            const float treadZ[] = { 0.0176f, 0.0352f, 0.0528f, 0.0704f, 0.0880f, 0.1056f, 0.1231f };
            int perTread[7] = {}, offTread = 0, badSdf = 0;
            for (const GpuBoid& b : spawn) {
                glm::vec3 p(b.position);
                int best = 0;
                for (int k = 1; k < 7; ++k) if (std::abs(p.z - treadZ[k]) < std::abs(p.z - treadZ[best])) best = k;
                if (std::abs(p.z - treadZ[best] - BODY_RADIUS) > 1e-4f) ++offTread; else ++perTread[best];
                if (!(sampleSDF_CPU(p) > 0.0f && sampleSDF_CPU(p - glm::vec3(0, 0, 0.02f)) < 0.0f)) ++badSdf;
            }
            std::printf("  agents per tread (z = 0.0176 .. 0.1231):");
            for (int k = 0; k < 7; ++k) std::printf(" %d", perTread[k]);
            std::printf("\n");
            check(offTread == 0 && badSdf == 0, "every agent BODY_RADIUS (6.4 mm) above a tread, in free space over solid (" +
                  std::to_string(offTread) + " off-tread, " + std::to_string(badSdf) + " SDF failures)");
            // A load that fits the spawn bands starts free of overlap (spawnBleacherCrowd relaxes it)
            const OverlapScan o = scanOverlaps(spawn, nullptr);
            const OverlapScan o8 = scanOverlaps(spawnBleacherCrowd(8192), nullptr);
            std::printf("  spawn capacity (spawn bands at random close packing of BODY_RADIUS disks): %.0f agents; N = %d: %ld overlapping\n"
                        "  pairs (max depth %.2e); N = 8192 (over capacity, left as placed): %ld overlapping pairs, %ld of 8192 agents\n",
                        spawnCapacity(), NUM_AGENTS, o.pairs, o.maxDepth, o8.pairs, o8.agents);
            check(double(NUM_AGENTS) <= spawnCapacity() && o.maxDepth <= 1e-6f, "N = " + std::to_string(NUM_AGENTS) +
                  " spawns without overlap (max overlap depth " + std::to_string(o.maxDepth) + " <= 1e-6)");
        }

        section("engine.pipeline_invariants: Pipeline invariants, ping-pong and full evacuation (4096 agents)");
        const std::vector<int> checkpoints = { 1, 100, 250, 500, 1000, 2000, 4000, 6000 };
        std::vector<GpuBoid> snapshot500, finalState;
        bool pingPongOk = true, glErrorFree = true, invariantsOk = true;
        int fullyEvacuatedAt = -1;
        long pitchAgentSteps = 0, routerPitchAgentSteps = 0;   // summed over every step until all have left
        {
            CrowdSim sim(shaderDir, NUM_AGENTS);
            sim.upload(spawn);
            std::printf("  near fence = |distance to the fence midline| < 2 * V_MAX * DT = %.4f; speed = |v_xy|\n", 2.0f * V_MAX * DT);
            std::printf("  %6s %7s %9s  %-45s %11s %8s  %s\n", "step", "active", "evacuated", "active by zone (tread/aisle/walk/avenue/pitch)",
                        "near fence", "speed", "invariants");
            for (int step = 1; step <= checkpoints.back(); ++step) {
                const bool cp = std::find(checkpoints.begin(), checkpoints.end(), step) != checkpoints.end();
                const int r = sim.readIndex();
                std::vector<GpuBoid> before;
                if (cp) before = readBuffer<GpuBoid>(sim.currentStateBuffer(), NUM_AGENTS);

                sim.step(sdfTex);

                pingPongOk &= sim.readIndex() == 1 - r && sim.currentStateBuffer() == sim.boidBuffer(1 - r);
                glErrorFree &= glGetError() == GL_NO_ERROR;
                if (fullyEvacuatedAt < 0) {
                    auto st = readBuffer<GpuBoid>(sim.currentStateBuffer(), NUM_AGENTS);
                    int activeNow = 0;
                    for (const GpuBoid& b : st) {
                        if (b.position.w == 0.0f) continue;
                        ++activeNow;
                        if (fenceSide(b.position) < 0.0f) ++pitchAgentSteps;
                        if (inRouterPitchBranch(b.position)) ++routerPitchAgentSteps;
                    }
                    if (activeNow == 0) fullyEvacuatedAt = step;
                }
                if (!cp) continue;

                auto prevAfter = readBuffer<GpuBoid>(sim.boidBuffer(r), NUM_AGENTS);
                auto cur = readBuffer<GpuBoid>(sim.currentStateBuffer(), NUM_AGENTS);
                auto grid = readBuffer<GpuGridInfo>(sim.gridBuffer(), NUM_AGENTS);
                auto cells = readBuffer<GpuCellData>(sim.cellBuffer(), size_t(GRID_RES) * GRID_RES);
                StepInvariants inv = verifyStep(before, prevAfter, cur, grid, cells);
                invariantsOk &= inv.ok();

                int zones[ZONE_COUNT] = {}, active = 0, nearFence = 0;
                double nearSpeed = 0.0;
                for (const GpuBoid& b : cur) {
                    if (b.position.w == 0.0f) continue;
                    ++active;
                    ++zones[zoneOf(b.position)];
                    if (std::abs(fenceSide(b.position)) < 2.0f * V_MAX * DT) {
                        ++nearFence;
                        nearSpeed += glm::length(glm::vec2(b.velocity));
                    }
                }
                char zoneStr[128];
                std::snprintf(zoneStr, sizeof(zoneStr), "%5d / %5d / %5d / %5d / %5d", zones[0], zones[1], zones[2], zones[3], zones[4]);
                std::printf("  %6d %7d %8.1f%%  %-45s %11d %8.4f  %s\n", step, active, 100.0 * (NUM_AGENTS - active) / NUM_AGENTS, zoneStr,
                            nearFence, nearFence ? nearSpeed / nearFence : 0.0, inv.ok() ? "ok" : "VIOLATED");
                if (!inv.ok())
                    std::printf("         unsorted=%ld perm=%ld hash=%ld tail=%ld cellRange=%ld cellTotal=%ld inactiveChanged=%ld nan=%ld inputOverwritten=%ld\n",
                                inv.unsorted, inv.badPermutation, inv.hashMismatch, inv.inactiveNotAtTail, inv.cellRangeErrors,
                                inv.cellTotalMismatch, inv.inactiveChanged, inv.nanStates, inv.inputOverwritten);

                if (step == 1 || step == 500) {
                    long pairs = 0;
                    long missed = missedNeighbourPairs(before, GRID_RES, PERC_RING, &pairs);
                    long missed3x3 = missedNeighbourPairs(before, GRID_RES, 1, nullptr);
                    std::printf("         neighbour coverage: %ld pairs within R_PERC=%.4f (horizontal) -> missed by the %dx%d search: %ld (by a 3x3 "
                                "search: %ld)\n", pairs, R_PERC, 2 * PERC_RING + 1, 2 * PERC_RING + 1, missed, missed3x3);
                    invariantsOk &= missed == 0;
                }
                if (step == 500) snapshot500 = cur;
                if (step == checkpoints.back()) finalState = cur;
            }
        }
        if (fullyEvacuatedAt > 0) {
            std::printf("  100%% evacuated at step %d (t = %.2f model time units at DT = %g)\n", fullyEvacuatedAt, fullyEvacuatedAt * DT, DT);
        } else {
            std::ofstream csv("fence_stuck.csv");
            csv << "id,x,y,z,vx,vy,vz,zone,fence_midline_dist\n";
            int remaining = 0;
            for (size_t i = 0; i < finalState.size(); ++i) {
                const GpuBoid& b = finalState[i];
                if (b.position.w == 0.0f) continue;
                ++remaining;
                csv << i << ',' << b.position.x << ',' << b.position.y << ',' << b.position.z << ',' << b.velocity.x << ','
                    << b.velocity.y << ',' << b.velocity.z << ',' << zoneOf(b.position) << ',' << fenceSide(b.position) << '\n';
            }
            std::printf("  %d agents remain after step %d; positions/velocities written to %s\n", remaining, checkpoints.back(),
                        fs::absolute("fence_stuck.csv").string().c_str());
        }
        check(fullyEvacuatedAt > 0, "all agents reach an exit by step " + std::to_string(checkpoints.back()));
        check(pitchAgentSteps == 0, "no agent on the pitch (past the fence midline) at any step (" + std::to_string(pitchAgentSteps) + " agent-steps)");
        check(routerPitchAgentSteps == 0, "router pitch-recovery branch never taken at any step (" + std::to_string(routerPitchAgentSteps) + " agent-steps)");
        check(pingPongOk, "readIdx/writeIdx swap every step; physics output becomes the state buffer");
        check(invariantsOk, "sorted grid, permutation, hash == CPU, inactive only at tail, exact cell ranges, "
                            "inactive agents untouched, no NaN, physics never writes its input, the PERC_RING ring covers R_PERC");
        check(glErrorFree, "glGetError() == GL_NO_ERROR after every step");

        section("engine.determinism: Determinism (no read/write race in physics)");
        {
            CrowdSim sim2(shaderDir, NUM_AGENTS);
            sim2.upload(spawn);
            for (int step = 0; step < 500; ++step) sim2.step(sdfTex);
            auto state = readBuffer<GpuBoid>(sim2.currentStateBuffer(), NUM_AGENTS);
            check(std::memcmp(state.data(), snapshot500.data(), state.size() * sizeof(GpuBoid)) == 0,
                  "independent run is bit-identical after 500 steps");
        }

        section("engine.frame_rate_independence: Frame-rate independence: 600 steps driven by a 144 Hz vs a 30 Hz clock");
        {
            struct Driven { std::vector<GpuBoid> curr, prev; int frames = 0; };
            auto runDriven = [&](double hz, int K) {
                CrowdSim sim(shaderDir, NUM_AGENTS);
                sim.upload(spawn);
                FixedStepClock clock;
                Driven d;
                int done = 0;
                while (done < K) {
                    int n = clock.advance(1.0 / hz);   // synthetic frame deltas
                    for (int i = 0; i < n && done < K; ++i, ++done) sim.step(sdfTex);
                    ++d.frames;
                }
                d.curr = readBuffer<GpuBoid>(sim.currentStateBuffer(), NUM_AGENTS);
                d.prev = readBuffer<GpuBoid>(sim.previousStateBuffer(), NUM_AGENTS);
                return d;
            };
            Driven fast = runDriven(144.0, 600), slow = runDriven(30.0, 600);
            std::printf("  144 Hz: %d frames, 30 Hz: %d frames, 600 steps each\n", fast.frames, slow.frames);
            const size_t bytes = size_t(NUM_AGENTS) * sizeof(GpuBoid);
            check(std::memcmp(fast.curr.data(), slow.curr.data(), bytes) == 0 && std::memcmp(fast.prev.data(), slow.prev.data(), bytes) == 0,
                  "current and previous state buffers bit-identical: the simulation is frame-rate independent");
        }

        section("engine.interpolation_buffers: Previous/current state buffers vs a separately stepped run");
        {
            const size_t bytes = size_t(NUM_AGENTS) * sizeof(GpuBoid);
            for (int k : { 0, 7, 8 }) {
                CrowdSim a(shaderDir, NUM_AGENTS);
                a.upload(spawn);
                for (int i = 0; i < k; ++i) a.step(sdfTex);
                auto aPrev = readBuffer<GpuBoid>(a.previousStateBuffer(), NUM_AGENTS);
                auto aCurr = readBuffer<GpuBoid>(a.currentStateBuffer(), NUM_AGENTS);
                if (k == 0) {
                    check(std::memcmp(aPrev.data(), spawn.data(), bytes) == 0 && std::memcmp(aCurr.data(), spawn.data(), bytes) == 0,
                          "before the first step: previous == current == spawn state");
                    continue;
                }
                CrowdSim b(shaderDir, NUM_AGENTS);
                b.upload(spawn);
                for (int i = 0; i < k - 1; ++i) b.step(sdfTex);
                auto bAtKm1 = readBuffer<GpuBoid>(b.currentStateBuffer(), NUM_AGENTS);
                b.step(sdfTex);
                auto bAtK = readBuffer<GpuBoid>(b.currentStateBuffer(), NUM_AGENTS);
                check(std::memcmp(aPrev.data(), bAtKm1.data(), bytes) == 0 && std::memcmp(aCurr.data(), bAtK.data(), bytes) == 0 &&
                      std::memcmp(aPrev.data(), aCurr.data(), bytes) != 0,
                      std::string("after ") + std::to_string(k) + (k % 2 ? " (odd)" : " (even)") +
                      " steps: previous = state after " + std::to_string(k - 1) + ", current = state after " + std::to_string(k));
            }
        }

        section("validation.dt_convergence_terrace: DT convergence (report only): evacuation at DT, DT/2, DT/4 (preamble override)");
        {
            struct Variant { int div; float dt; int evacStep = -1; std::vector<std::array<int, ZONE_COUNT + 1>> tables; };
            std::vector<Variant> vs = { { 1, DT }, { 2, DT / 2.0f }, { 4, DT / 4.0f } };
            const double reportT[] = { 1.0, 2.5, 5.0 };
            for (Variant& v : vs) {
                fs::path dir = v.div == 1 ? shaderDir : makeShaderVariant(shaderDir, "dt_div" + std::to_string(v.div), dtOverride(v.dt));
                CrowdSim sim(dir, NUM_AGENTS);
                if (v.div != 1) fs::remove_all(dir);
                sim.upload(spawn);
                size_t next = 0;
                for (int step = 1; step <= 6000 * v.div; ++step) {
                    sim.step(sdfTex);
                    const bool atReport = next < 3 && step == int(std::lround(reportT[next] / v.dt));
                    auto st = readBuffer<GpuBoid>(sim.currentStateBuffer(), NUM_AGENTS);
                    std::array<int, ZONE_COUNT + 1> row = {};   // zones..., active
                    for (const GpuBoid& b : st) if (b.position.w != 0.0f) { ++row[zoneOf(b.position)]; ++row[ZONE_COUNT]; }
                    if (atReport) { v.tables.push_back(row); ++next; }
                    if (row[ZONE_COUNT] == 0) { v.evacStep = step; break; }
                }
                while (v.tables.size() < 3) v.tables.push_back({});   // evacuated before a report time
            }
            std::printf("  %-6s %10s %8s %10s %14s\n", "dt", "steps", "t", "change", "(vs previous)");
            for (size_t i = 0; i < vs.size(); ++i) {
                const double t = vs[i].evacStep * double(vs[i].dt);
                std::string change = "-";
                if (i > 0 && vs[i - 1].evacStep > 0) {
                    const double tp = vs[i - 1].evacStep * double(vs[i - 1].dt);
                    char b[32];
                    std::snprintf(b, sizeof(b), "%+.2f%%", 100.0 * (t - tp) / tp);
                    change = b;
                }
                std::printf("  DT/%-3d %10d %8.3f %10s\n", vs[i].div, vs[i].evacStep, t, change.c_str());
            }
            std::printf("  zone tables (active: tread / aisle / walkway / avenue / pitch)\n");
            for (int r = 0; r < 3; ++r)
                for (const Variant& v : vs) {
                    const auto& z = v.tables[r];
                    std::printf("    t = %.1f  DT/%d (step %5ld): active %4d  %4d / %4d / %4d / %4d / %4d\n", reportT[r], v.div,
                                std::lround(reportT[r] / v.dt), z[ZONE_COUNT], z[0], z[1], z[2], z[3], z[4]);
                }
        }

        section("perf.gpu_pass_timings: Compute timings (GPU timestamps, mean over 300 steps after 30 warm-up)");
        std::printf("  %7s %8s %8s %8s %8s %8s  (ms)\n", "agents", "hash", "sort", "cells", "physics", "total");
        for (int n : { NUM_AGENTS, 65536 }) {
            CrowdSim sim(shaderDir, n);
            sim.upload(spawnBleacherCrowd(n));
            sim.setTimingEnabled(true);
            for (int i = 0; i < 30; ++i) sim.step(sdfTex);
            CrowdSim::PassTimesMs sum;
            const int runs = 300;
            for (int i = 0; i < runs; ++i) {
                sim.step(sdfTex);
                CrowdSim::PassTimesMs t = sim.readTimings();
                sum.hash += t.hash; sum.sort += t.sort; sum.cells += t.cells; sum.physics += t.physics; sum.total += t.total;
            }
            std::printf("  %7d %8.4f %8.4f %8.4f %8.4f %8.4f\n", n, sum.hash / runs, sum.sort / runs, sum.cells / runs,
                        sum.physics / runs, sum.total / runs);
        }
        glErrorFree &= glGetError() == GL_NO_ERROR;

        section("venue.terrace_passage_widths: Passage widths (report only) at the rest height floor + BODY_RADIUS: geometric | centre-accessible (horizontal clearance >= BODY_RADIUS)");
        {
            const float body = 2.0f * BODY_RADIUS;
            // Tread starts (crowd_sim.cpp TREADS): just past each one the aisle floor is lowest
            // relative to the tread beside it (up to 13 mm), so the aisle is most channel-like there
            const float treadStart[] = { 0.427f, 0.473f, 0.520f, 0.568f, 0.615f, 0.662f, 0.708f };
            // Widths per kind of passage (geometric), for the real-units table below
            std::map<std::string, std::vector<float>> widths;
            auto line = [&](const std::string& kind, const std::string& what, glm::vec2 c, glm::vec2 u) {
                Passage w = passageWidth(c, u);
                float geo = w.geometric, acc = w.accessible;
                widths[kind].push_back(geo);
                std::printf("  %-40s %.4f (%5.2f bodies) | %.4f (%5.2f bodies)\n", what.c_str(), geo, geo / body, acc, acc / body);
            };
            std::printf("  walkway: fence -> stand front, radial section through dep 0.38\n");
            for (const Avenue& a : AVENUES)
                for (float lat : { -0.25f, 0.25f })
                    line("walkway", std::string("    walkway beside avenue ") + a.name + (lat < 0 ? ", lat -0.25" : ", lat +0.25"),
                         a.lat * lat + a.out * 0.38f, a.out);
            std::printf("  aisles: side wall -> tread edge, lateral sections at 7 tread starts (+4 mm), min / median of each\n");
            // A section wider than the aisle's band has no avenue wall on its inner side: it lies in front of the wall's end, so the probe crosses
            // the avenue's mouth to the opposite wall. That length is no aisle width, so it is listed and not counted.
            const float aisleBand = AISLE_MAX - AVENUE_HALF;
            std::vector<std::string> runOut;
            for (const Avenue& a : AVENUES)
                for (float sgn : { -1.0f, 1.0f }) {
                    const std::string aisle = std::string("aisle beside avenue ") + a.name + (sgn < 0 ? ", lat -" : ", lat +");
                    std::vector<float> geo, acc;
                    int tread = 0;
                    for (float d : treadStart) {
                        ++tread;
                        glm::vec2 c = a.lat * (sgn * AISLE_CENTRE) + a.out * (d + 0.004f);
                        Passage w = passageWidth(c, a.lat);
                        if (w.geometric > aisleBand) {
                            const glm::vec3 p(c, floorHeight(c) + BODY_RADIUS), outward(a.lat * sgn, 0.0f);
                            char b[200];
                            std::snprintf(b, sizeof(b), "%s, tread %d: %.4f = %.2f m, from %+.2f m to %+.2f m of the avenue's centre line", aisle.c_str(), tread, w.geometric,
                                          units::metres(w.geometric), units::metres(AISLE_CENTRE + freeRun(p, outward, 0.0f)), units::metres(AISLE_CENTRE - freeRun(p, -outward, 0.0f)));
                            runOut.push_back(b);
                            continue;
                        }
                        geo.push_back(w.geometric);
                        acc.push_back(w.accessible);
                        widths["aisle"].push_back(w.geometric);
                    }
                    std::sort(geo.begin(), geo.end());
                    std::sort(acc.begin(), acc.end());
                    const size_t g = geo.size() / 2, h = acc.size() / 2;
                    std::printf("    %-38s %.4f / %.4f (%4.2f / %4.2f bodies) | %.4f / %.4f (%4.2f / %4.2f bodies)\n", aisle.c_str(),
                                geo.front(), geo[g], geo.front() / body, geo[g] / body, acc.front(), acc[h], acc.front() / body, acc[h] / body);
                }
            std::printf("    sections in front of an avenue wall's end, crossing the avenue's mouth, not counted (wider than the aisle's band %.4f = %.2f m): %d\n", aisleBand, units::metres(aisleBand), int(runOut.size()));
            for (const std::string& r : runOut) std::printf("      %s\n", r.c_str());
            std::printf("  avenue mouths: between the side walls, lateral section at dep 0.44\n");
            for (const Avenue& a : AVENUES) line("avenue", std::string("    avenue ") + a.name + " mouth", a.out * 0.44f, a.lat);
            std::printf("  outer-wall exit gaps: lateral section at dep 0.93 (outer wall 0.915..0.95)\n");
            for (const Avenue& a : AVENUES) line("exit", std::string("    avenue ") + a.name + " exit gap", a.out * 0.93f, a.lat);

            // The venue in real units (WORLD_SCALE_M_PER_UNIT and TIME_SCALE_S_PER_UNIT,
            // sim_params.hpp)
            // Rows of the stands, on a radial line through every stand wing at lat 0.3: plateau heights at the
            // centre of each band (walkway, the 7 treads of crowd_sim.cpp TREADS, the back platform), risers
            // where the floor crosses the mid-height between two plateaus (bisection), tread depth = distance
            // between successive risers.
            const float bandCentre[] = { 0.380f, 0.4485f, 0.495f, 0.5425f, 0.589f, 0.636f, 0.6835f, 0.7305f, 0.830f };
            constexpr int BANDS = int(std::size(bandCentre));
            std::vector<float> risers, treads;
            for (const Avenue& a : AVENUES)
                for (float sgn : { -1.0f, 1.0f }) {
                    auto at = [&](float dep) { return a.lat * (sgn * 0.3f) + a.out * dep; };
                    float h[BANDS], cross[BANDS] = {};
                    for (int k = 0; k < BANDS; ++k) h[k] = floorHeight(at(bandCentre[k]));
                    for (int k = 1; k < BANDS; ++k) {
                        const float level = 0.5f * (h[k - 1] + h[k]);
                        float lo = bandCentre[k - 1], hi = bandCentre[k];   // floor(lo) < level <= floor(hi)
                        for (int i = 0; i < 30; ++i) {
                            const float mid = 0.5f * (lo + hi);
                            (floorHeight(at(mid)) < level ? lo : hi) = mid;
                        }
                        cross[k] = 0.5f * (lo + hi);
                        risers.push_back(h[k] - h[k - 1]);
                    }
                    for (int k = 1; k + 1 < BANDS; ++k) treads.push_back(cross[k + 1] - cross[k]);
                }
            auto range = [](std::vector<float> v) {   // min, median, max (single sections can run into an open side)
                std::sort(v.begin(), v.end());
                const size_t m = v.size() / 2;
                return std::array<double, 3>{ v.front(), v.size() % 2 ? v[m] : 0.5 * (double(v[m - 1]) + double(v[m])), v.back() };
            };
            auto row = [&](const char* what, const std::array<double, 3>& r, const char* note) {
                std::printf("    %-34s %8.4f %8.4f %8.4f | %7.2f %7.2f %7.2f  %s\n", what, r[0], r[1], r[2], units::metres(r[0]),
                            units::metres(r[1]), units::metres(r[2]), note);
            };
            auto one = [&](const char* what, double model, const char* note) { row(what, { model, model, model }, note); };
            std::printf("  venue in real units: %.4g m per model unit (hard body BODY_RADIUS_M %.2f m = BODY_RADIUS %.4f; personal space\n"
                        "  PERSONAL_RADIUS_M %.2f m = %.3f), %.6g s per model time unit (V_MAX %.2f = V_FREE_M_S %.2f m/s)\n",
                        WORLD_SCALE_M_PER_UNIT, BODY_RADIUS_M, BODY_RADIUS, PERSONAL_RADIUS_M, PERSONAL_RADIUS, TIME_SCALE_S_PER_UNIT, V_MAX,
                        V_FREE_M_S);
            std::printf("    %-34s %8s %8s %8s | %7s %7s %7s\n", "length", "min", "median", "max", "min m", "med m", "max m");
            one("overall span (SDF volume, x and y)", 2.0 * 0.95, "outer faces of the outer wall");
            one("simulation domain (x and y)", DOMAIN_SPAN, "agents beyond it are removed");
            one("pitch (fence inner faces)", 2.0 * FENCE_HALF_INNER, "square, fenced off (no gates)");
            one("pitch fence height", 0.025802, "stadium.obj (tools/measure_fence.py)");
            row("walkway width (geometric)", range(widths["walkway"]), "8 radial sections");
            row("aisle width (geometric)", range(widths["aisle"]), (std::to_string(widths["aisle"].size()) + " of 56 lateral sections, those between an avenue wall and a tread edge").c_str());
            row("avenue mouth width (geometric)", range(widths["avenue"]), "4 avenues, dep 0.44");
            row("exit gap width (geometric)", range(widths["exit"]), "4 exits, dep 0.93");
            row("tread depth (riser to riser)", range(treads), "7 treads x 8 wings");
            row("riser height", range(risers), "walkway-T1 .. T7-platform, 8 wings");
            one("hard body diameter 2 * BODY_RADIUS", 2.0 * BODY_RADIUS, "the hard body");
            one("separation support R_SEP", R_SEP, "2 * PERSONAL_RADIUS (body ellipse circle equivalent)");
            one("perception radius R_PERC", R_PERC, "separation partners and the headway look-ahead");
            std::printf("    %-34s %8.4f model time = %.4f s (static_assert: 0.01-0.25 s)\n", "DT", double(DT), DT_REAL_S);
            std::printf("    %-34s %8.4f model = %.4f m/s\n", "V_MAX", double(V_MAX), units::metresPerSecond(V_MAX));
            std::printf("    %-34s %8.4f model = %.4f m/s^2 (%.3f g)\n", "GRAVITY", double(GRAVITY),
                        units::metres(GRAVITY) / (units::S_PER_UNIT * units::S_PER_UNIT),
                        units::metres(GRAVITY) / (units::S_PER_UNIT * units::S_PER_UNIT) / 9.80665);
            std::printf("    %-34s %8.5f model time = %.4f s (driving term: velocity relaxation)\n", "TAU_RELAX", double(TAU_RELAX),
                        units::seconds(TAU_RELAX));
            std::printf("    %-34s %8.5f model time = %.4f s (headway rule's time gap)\n", "T_HEADWAY", double(T_HEADWAY), units::seconds(T_HEADWAY));
            std::printf("    %-34s %8.4f model = %.4f m (covers the headway look-ahead BODY_DIAM + V_MAX T_HEADWAY = %.4f m; %dx%d cells)\n",
                        "R_PERC (horizontal)", double(R_PERC), units::metres(R_PERC), units::metres(BODY_DIAM + V_MAX * T_HEADWAY),
                        2 * PERC_RING + 1, 2 * PERC_RING + 1);
        }

        section("parity.grid: CPU reference: grid equivalence, CPU sorted pairs and cell table vs GPU");
        std::vector<EquivCase> equiv;
        {
            const uint64_t h = portedShadersHash(shaderDir);
            std::printf("  ported shaders (calc_grid, bitonic_sort, bitonic_sort_shared, reorder, physics .comp, venue_seated.glsl) FNV-1a %016llx, CPU port pinned to %016llx\n",
                        (unsigned long long)h, (unsigned long long)PORTED_SHADERS_FNV1A);
            check(h == PORTED_SHADERS_FNV1A, "the compute shaders are the ones cpu_crowd_sim.cpp ports (else: port the change, re-verify, update the pin)");
            std::printf("  the GPU bitonic sort compares gridID only: within a cell its boidID order is the network's own\n"
                        "  deterministic permutation, not ascending. 'bitonic' replays that network; 'counting' is the\n"
                        "  O(N) stable counting sort (boidID ascending within a cell) that the benchmark uses.\n");
            std::printf("  states: spawn, and the GPU state after 250 steps from spawn (congested); one step each side\n");
            for (int n : { NUM_AGENTS, 65536 }) {
                if (n != NUM_AGENTS && !longTier("the equivalence cases at N = 65536 (parity.grid, parity.one_step)")) continue;
                const std::vector<GpuBoid> start = n == NUM_AGENTS ? spawn : spawnBleacherCrowd(n);
                CrowdSim sim(shaderDir, n);
                sim.upload(start);
                for (int i = 0; i < 250; ++i) sim.step(sdfTex);
                const std::vector<GpuBoid> congested = readBuffer<GpuBoid>(sim.currentStateBuffer(), n);
                equiv.push_back(runEquivCase(shaderDir, sdfTex, start, "spawn"));
                equiv.push_back(runEquivCase(shaderDir, sdfTex, congested, "step 250"));
            }
            for (const EquivCase& c : equiv) {
                const int n = c.n;
                const size_t cellCount = c.gpuCells.size();
                auto cellsDiffer = [&](const std::vector<GpuCellData>& cells) {
                    long d = 0;
                    for (size_t k = 0; k < cellCount; ++k)
                        d += cells[k].startIndex != c.gpuCells[k].startIndex || cells[k].agentCount != c.gpuCells[k].agentCount;
                    return d;
                };
                std::printf("  N = %5d, %-8s (%ld active, %ld inactive):\n", n, c.stateName.c_str(), c.active, long(n) - c.active);

                // Bitonic replay: the whole (gridID, boidID) sequence
                const EquivCase::Cpu& b = c.cpu[1];
                long pairDiff = 0;
                for (int s = 0; s < n; ++s) pairDiff += b.grid[s].gridID != c.gpuGrid[s].gridID || b.grid[s].boidID != c.gpuGrid[s].boidID;
                const long bitonicCells = cellsDiffer(b.cells);
                std::printf("    bitonic:  (gridID, boidID) slots != GPU %ld of %d | cells != GPU %ld of %zu\n", pairDiff, n, bitonicCells, cellCount);
                check(pairDiff == 0 && bitonicCells == 0, "N = " + std::to_string(n) + ", " + c.stateName +
                      ", bitonic: sorted (gridID, boidID) array and cell table exactly equal to the GPU's");

                // Counting sort: gridID sequence and cell table exact, same boidID set in every run of
                // equal gridID (cells, then the inactive tail), boidID ascending within each run
                const EquivCase::Cpu& k = c.cpu[0];
                long gridIdDiff = 0, boidIdDiff = 0, setDiff = 0, runs = 0, notAscending = 0;
                for (int s = 0; s < n; ++s) {
                    gridIdDiff += k.grid[s].gridID != c.gpuGrid[s].gridID;
                    boidIdDiff += k.grid[s].boidID != c.gpuGrid[s].boidID;
                    if (s > 0 && k.grid[s].gridID == k.grid[s - 1].gridID && k.grid[s].boidID <= k.grid[s - 1].boidID) ++notAscending;
                }
                for (int s = 0; s < n && gridIdDiff == 0;) {
                    int e = s;
                    while (e < n && c.gpuGrid[e].gridID == c.gpuGrid[s].gridID) ++e;
                    std::vector<uint32_t> gpuIds, cpuIds;
                    for (int q = s; q < e; ++q) { gpuIds.push_back(c.gpuGrid[q].boidID); cpuIds.push_back(k.grid[q].boidID); }
                    std::sort(gpuIds.begin(), gpuIds.end());
                    std::sort(cpuIds.begin(), cpuIds.end());
                    setDiff += gpuIds != cpuIds;
                    ++runs;
                    s = e;
                }
                const long countingCells = cellsDiffer(k.cells);
                std::printf("    counting: gridID slots != GPU %ld | cells != GPU %ld | runs with a different boidID set %ld of %ld |"
                            " boidID order differs at %ld slots (within-cell order only)\n",
                            gridIdDiff, countingCells, setDiff, runs, boidIdDiff);
                check(gridIdDiff == 0 && countingCells == 0 && setDiff == 0 && notAscending == 0, "N = " + std::to_string(n) + ", " +
                      c.stateName + ", counting: gridID sequence and cell table exactly equal, same boidIDs per cell, ascending within each");
            }
        }

        section("parity.one_step: CPU reference: single-step equivalence, same input on both, per-agent difference after one step");
        {
            std::printf("  over agents active in the input; outlier: |dpos| > 2e-4 (limit: < 0.5%% of active); w !=: evacuation flag differs\n");
            std::printf("  %5s %-8s %-8s %6s  %-30s  %-30s %4s %16s  %s\n", "N", "state", "mode", "active", "|dpos| p50 / p99 / max",
                        "|dvel| p50 / p99 / max", "w !=", "outliers", "outliers by CPU contact branch");
            for (const EquivCase& c : equiv) {
                for (int m = 0; m < 2; ++m) {
                    const EquivCase::Cpu& cpu = c.cpu[m];
                    std::vector<float> dpos, dvel;
                    long outliers = 0, flagDiff = 0;
                    std::map<std::string, int> branches;
                    for (int i = 0; i < c.n; ++i) {
                        if (c.in[i].position.w == 0.0f) continue;
                        const float dp = glm::length(glm::vec3(cpu.out[i].position) - glm::vec3(c.gpuOut[i].position));
                        dpos.push_back(dp);
                        dvel.push_back(glm::length(glm::vec3(cpu.out[i].velocity) - glm::vec3(c.gpuOut[i].velocity)));
                        flagDiff += cpu.out[i].position.w != c.gpuOut[i].position.w;
                        if (dp > 2e-4f) { ++outliers; ++branches[contactLabel(cpu.contacts[i])]; }
                    }
                    const Dist p = distribution(dpos), v = distribution(dvel);
                    std::string branchStr;
                    for (const auto& [label, count] : branches) branchStr += (branchStr.empty() ? "" : ", ") + label + " " + std::to_string(count);
                    char pos[64], vel[64], out[32];
                    std::snprintf(pos, sizeof(pos), "%.2e / %.2e / %.2e", p.p50, p.p99, p.max);
                    std::snprintf(vel, sizeof(vel), "%.2e / %.2e / %.2e", v.p50, v.p99, v.max);
                    std::snprintf(out, sizeof(out), "%ld (%.3f%%)", outliers, 100.0 * double(outliers) / double(c.active));
                    std::printf("  %5d %-8s %-8s %6ld  %-30s  %-30s %4ld %16s  %s\n", c.n, c.stateName.c_str(), modeName(SORT_MODES[m]), c.active,
                                pos, vel, flagDiff, out, branchStr.empty() ? "-" : branchStr.c_str());
                    check(outliers * 1000 < c.active * 5, "N = " + std::to_string(c.n) + ", " + c.stateName + ", " + modeName(SORT_MODES[m]) +
                          ": " + std::to_string(outliers) + " agents with |dpos| > 2e-4, < 0.5% of " + std::to_string(c.active) + " active");
                }
                float maxPos = 0.0f, maxVel = 0.0f;
                for (int i = 0; i < c.n; ++i) {
                    maxPos = std::max(maxPos, glm::length(glm::vec3(c.cpu[0].out[i].position) - glm::vec3(c.cpu[1].out[i].position)));
                    maxVel = std::max(maxVel, glm::length(glm::vec3(c.cpu[0].out[i].velocity) - glm::vec3(c.cpu[1].out[i].velocity)));
                }
                std::printf("  %5d %-8s counting vs bitonic on the CPU (neighbour summation order only): max |dpos| %.2e, max |dvel| %.2e\n",
                            c.n, c.stateName.c_str(), maxPos, maxVel);
            }
            std::printf("  intentional difference: GPU map() uses hardware trilinear filtering (8-bit weights, ~h/256 = 6e-5),\n"
                        "  the CPU the exact sampler; plus rounding-level GPU/CPU arithmetic differences (see cpu_crowd_sim.cpp)\n");
        }
        equiv.clear();

        // CPU runs from spawn at max threads, shared by parity.thread_invariance, parity.cpu_determinism, parity.terrace_evacuation and
        // parity.golden_terrace (a Debug build steps the CPU ~16x slower than Release): one per sort mode, stepped to full evacuation
        // and snapshotted after 100 steps (thread-invariance reference), 500 steps
        // (first determinism run) and GOLDEN_STEPS steps (golden state).
        // The full evacuation in the long tier; the quick tier steps to GOLDEN_STEPS only (the golden pins)
        struct SharedCpuRun { EvacRun evac; std::vector<GpuBoid> at100, at500, atGolden; };
        SharedCpuRun sharedCpu[2];
        for (int m = 0; m < 2; ++m) {
            CpuCrowdSim cpu(sdfVolumeCPU(), 0, SORT_MODES[m]);
            cpu.setState(spawn);
            int steps = 0;
            auto stepOnce = [&]() -> const std::vector<GpuBoid>& {
                cpu.step();
                ++steps;
                if (steps == 100) sharedCpu[m].at100 = cpu.state();
                if (steps == 500) sharedCpu[m].at500 = cpu.state();
                if (steps == golden::GOLDEN_STEPS) sharedCpu[m].atGolden = cpu.state();
                return cpu.state();
            };
            if (g_longTier) {
                sharedCpu[m].evac = runEvacuation(checkpoints, stepOnce);
                while (steps < std::max(500, golden::GOLDEN_STEPS)) stepOnce();   // evacuated earlier: the snapshots still get taken
            } else {
                while (steps < golden::GOLDEN_STEPS) stepOnce();
            }
        }

        section("parity.thread_invariance: CPU reference: thread invariance, 100 steps from spawn at N = 4096");
        if (longTier("CPU runs at 1 and 2 threads")) {
            const int maxThreads = CpuCrowdSim::maxThreads();
            for (int m = 0; m < 2; ++m) {
                const std::vector<GpuBoid>& ref = sharedCpu[m].at100;   // maxThreads
                bool identical = true;
                for (int threads : { 1, 2 }) {
                    CpuCrowdSim cpu(sdfVolumeCPU(), threads, SORT_MODES[m]);
                    cpu.setState(spawn);
                    for (int i = 0; i < 100; ++i) cpu.step();
                    identical &= std::memcmp(ref.data(), cpu.state().data(), ref.size() * sizeof(GpuBoid)) == 0;
                }
                long active = 0;
                for (const GpuBoid& b : ref) active += b.position.w != 0.0f;
                check(identical, std::string(modeName(SORT_MODES[m])) + ": states bit-identical with 1, 2, " + std::to_string(maxThreads) +
                      " threads (" + std::to_string(active) + " still active)");
            }
        }

        section("parity.cpu_determinism: CPU reference: determinism, two independent runs, 500 steps from spawn at N = 4096");
        if (longTier("two CPU runs of 500 steps")) {
            for (int m = 0; m < 2; ++m) {
                const std::vector<GpuBoid>& first = sharedCpu[m].at500;
                CpuCrowdSim cpu(sdfVolumeCPU(), 0, SORT_MODES[m]);
                cpu.setState(spawn);
                for (int i = 0; i < 500; ++i) cpu.step();
                long active = 0;
                for (const GpuBoid& b : first) active += b.position.w != 0.0f;
                check(std::memcmp(first.data(), cpu.state().data(), first.size() * sizeof(GpuBoid)) == 0,
                      std::string(modeName(SORT_MODES[m])) + ": bit-identical after 500 steps (" + std::to_string(active) + " still active)");
            }
        }

        section("parity.terrace_evacuation: CPU reference: full evacuation at N = 4096, CPU vs GPU");
        if (longTier("the full CPU evacuations")) {
            EvacRun gpuRun;
            {
                CrowdSim sim(shaderDir, NUM_AGENTS);
                sim.upload(spawn);
                std::vector<GpuBoid> st;
                gpuRun = runEvacuation(checkpoints, [&]() -> const std::vector<GpuBoid>& {
                    sim.step(sdfTex);
                    st = readBuffer<GpuBoid>(sim.currentStateBuffer(), NUM_AGENTS);
                    return st;
                });
            }
            const EvacRun* cpuRuns[2] = { &sharedCpu[0].evac, &sharedCpu[1].evac };
            std::printf("  active, then active by zone (tread / aisle / walkway / avenue / pitch)\n");
            std::printf("  %6s | %-33s | %-33s | %-33s\n", "step", "GPU", "CPU counting", "CPU bitonic");
            auto cell = [](const ZoneRow& z) {
                char b[64];
                std::snprintf(b, sizeof(b), "%4d  %4d/%4d/%4d/%4d/%4d", z[ZONE_COUNT], z[0], z[1], z[2], z[3], z[4]);
                return std::string(b);
            };
            for (size_t i = 0; i < checkpoints.size(); ++i)
                std::printf("  %6d | %-33s | %-33s | %-33s\n", checkpoints[i], cell(gpuRun.rows[i]).c_str(), cell(cpuRuns[0]->rows[i]).c_str(),
                            cell(cpuRuns[1]->rows[i]).c_str());
            auto rel = [&](int s) { return gpuRun.evacStep > 0 && s > 0 ? 100.0 * double(s - gpuRun.evacStep) / double(gpuRun.evacStep) : 0.0; };
            std::printf("  100%% evacuated at step: GPU %d | CPU counting %d (%+.2f%%) | CPU bitonic %d (%+.2f%%)\n", gpuRun.evacStep,
                        cpuRuns[0]->evacStep, rel(cpuRuns[0]->evacStep), cpuRuns[1]->evacStep, rel(cpuRuns[1]->evacStep));
            check(gpuRun.evacStep > 0 && gpuRun.evacStep == fullyEvacuatedAt, "GPU rerun evacuates at the same step as engine.pipeline_invariants (" +
                  std::to_string(gpuRun.evacStep) + ")");
            for (int m = 0; m < 2; ++m) {
                const int s = cpuRuns[m]->evacStep;
                check(s > 0 && std::abs(s - gpuRun.evacStep) * 20 <= gpuRun.evacStep, std::string("CPU ") + modeName(SORT_MODES[m]) +
                      ": evacuation time within +/-5% of the GPU's (" + std::to_string(s) + " vs " + std::to_string(gpuRun.evacStep) + ")");
                check(cpuRuns[m]->pitchAgentSteps == 0 && !cpuRuns[m]->nan, std::string("CPU ") + modeName(SORT_MODES[m]) +
                      ": no agent on the pitch at any step, no NaN (" + std::to_string(cpuRuns[m]->pitchAgentSteps) + " agent-steps on the pitch)");
            }
        }

        section("perf.cpu_stage_timings: CPU reference: smoke timing (not the benchmark), wall clock per stage");
#ifdef NDEBUG
        {
            // The projection's 32 iterations make a 1-thread CPU step at N = 65536 (stacked spawn) ~14 s, so
            // that cell runs 1 warm-up + 3 steps; every other cell 3 + 50
            const int steps = 50, warmup = 3, slowSteps = 3, slowWarmup = 1;
            std::printf("  CPU: %s | logical cores: %u | OpenMP max threads: %d\n", cpuBrandString().c_str(),
                        std::thread::hardware_concurrency(), CpuCrowdSim::maxThreads());
            std::printf("  SortMode::counting, from spawn: %d warm-up steps, then the mean of %d steps (total: min / max); N = 65536 on 1 thread: %d + %d\n",
                        warmup, steps, slowWarmup, slowSteps);
            std::printf("  %7s %7s %9s %9s %9s %9s %9s %21s  (ms)\n", "agents", "threads", "hash", "sort", "cells", "physics", "total", "total min / max");
            for (int n : { NUM_AGENTS, 65536 }) {
                const std::vector<GpuBoid> start = n == NUM_AGENTS ? spawn : spawnBleacherCrowd(n);
                for (int threads : { 1, CpuCrowdSim::maxThreads() }) {
                    CpuCrowdSim cpu(sdfVolumeCPU(), threads, SortMode::Counting);
                    cpu.setState(start);
                    const bool slow = n == 65536 && threads == 1;
                    for (int i = 0; i < (slow ? slowWarmup : warmup); ++i) cpu.step();
                    CpuCrowdSim::StageTimesMs sum;
                    double tMin = 1e30, tMax = 0.0;
                    const int runSteps = slow ? slowSteps : steps;
                    for (int i = 0; i < runSteps; ++i) {
                        cpu.step();
                        const CpuCrowdSim::StageTimesMs& t = cpu.timings();
                        sum.hash += t.hash; sum.sort += t.sort; sum.cells += t.cells; sum.physics += t.physics; sum.total += t.total;
                        tMin = std::min(tMin, t.total);
                        tMax = std::max(tMax, t.total);
                    }
                    std::printf("  %7d %7d %9.4f %9.4f %9.4f %9.3f %9.3f %10.3f / %8.3f\n", n, cpu.numThreads(), sum.hash / runSteps, sum.sort / runSteps,
                                sum.cells / runSteps, sum.physics / runSteps, sum.total / runSteps, tMin, tMax);
                }
            }
        }
#else
        std::printf("  skipped in Debug: timing is Release-only\n");
#endif

        section(("parity.golden_terrace: Golden state: FNV-1a 64 of the raw agent state after GOLDEN_STEPS = " + std::to_string(golden::GOLDEN_STEPS) +
                 " steps from spawn").c_str());
        {
            const std::string driver = std::string((const char*)glGetString(GL_RENDERER)) + " | " + (const char*)glGetString(GL_VERSION);
            uint64_t hashes[GOLDEN_COUNT];
            long activeLeft[GOLDEN_COUNT] = {}, golden_n[GOLDEN_COUNT] = { NUM_AGENTS, 65536, NUM_AGENTS, NUM_AGENTS };
            for (int k = 0; k < 2; ++k) {   // GPU, N = 4096 and 65536
                const int n = k == 0 ? NUM_AGENTS : 65536;
                CrowdSim sim(shaderDir, n);
                sim.upload(n == NUM_AGENTS ? spawn : spawnBleacherCrowd(n));
                for (int i = 0; i < golden::GOLDEN_STEPS; ++i) sim.step(sdfTex);
                const std::vector<GpuBoid> st = readBuffer<GpuBoid>(sim.currentStateBuffer(), n);
                hashes[k] = stateHash(st);
                for (const GpuBoid& b : st) activeLeft[k] += b.position.w != 0.0f;
            }
            for (int m = 0; m < 2; ++m) {   // CPU counting, bitonic (N = 4096)
                hashes[2 + m] = stateHash(sharedCpu[m].atGolden);
                for (const GpuBoid& b : sharedCpu[m].atGolden) activeLeft[2 + m] += b.position.w != 0.0f;
            }
            bool allActive = true;
            std::string activeList;
            for (int k = 0; k < GOLDEN_COUNT; ++k) {
                allActive &= activeLeft[k] > 0;
                activeList += (k ? ", " : "") + std::to_string(activeLeft[k]) + " of " + std::to_string(golden_n[k]);
            }
            // A golden state must not be (close to) the all-parked state of a finished evacuation
            check(allActive, "every golden state still has active agents (" + activeList + ")");
            const bool sameDriver = driver == GOLDEN_DRIVER;
            std::printf("  driver: %s\n  pinned: %s%s\n", driver.c_str(), GOLDEN_DRIVER, sameDriver ? "" : "  (DIFFERENT)");
            for (int k = 0; k < GOLDEN_COUNT; ++k)
                std::printf("  %-22s %016llx  pinned %016llx  %s\n", GOLDEN[k].name, (unsigned long long)hashes[k],
                            (unsigned long long)GOLDEN[k].hash, hashes[k] == GOLDEN[k].hash ? "match" : "MISMATCH");
            if (sameDriver) {
                for (int k = 0; k < GOLDEN_COUNT; ++k)
                    check(hashes[k] == GOLDEN[k].hash, std::string(GOLDEN[k].name) + ": state after " + std::to_string(golden::GOLDEN_STEPS) +
                          " steps matches the pinned golden hash");
            } else {
                std::printf("  [WARN] different driver: the golden hashes are not compared (a new driver may legitimately change\n"
                            "         GPU results bit for bit). The hashes above are this driver's. Re-pin them in\n"
                            "         tools/golden_state.hpp (GOLDEN_DRIVER, GOLDEN) only after verifying the evacuation step\n"
                            "         (engine.pipeline_invariants) and the parity sections on this driver.\n");
            }
        }

        section("parity.constants: CPU/GPU constant parity: every shared constant read back from the GPU, bit-compared with the CPU");
        {
            const std::vector<ParityEntry> entries = parityEntries();
            std::string src = "#version 430 core\nlayout(local_size_x = 1) in;\n"
                              "layout(std430, binding = 6) writeonly buffer R { uint outv[]; };\nvoid main() {\n";
            for (size_t k = 0; k < entries.size(); ++k)
                src += "    outv[" + std::to_string(k) + "] = " +
                       (entries[k].isFloat ? "floatBitsToUint(" + entries[k].glsl + ")" : "uint(" + entries[k].glsl + ")") + ";\n";
            src += "}\n";
            const fs::path tmp = processTempPath("swarm_constant_parity.comp");
            { std::ofstream(tmp) << src; }
            GLuint prog = loadComputeProgram(tmp);
            fs::remove(tmp);
            GLuint out = makeBuffer(std::vector<uint32_t>(entries.size()));
            glUseProgram(prog);
            glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, out);
            glDispatchCompute(1, 1, 1);
            const std::vector<uint32_t> gpu = readBuffer<uint32_t>(out, entries.size());
            glDeleteBuffers(1, &out);
            glDeleteProgram(prog);

            long derived = 0, mismatches = 0;
            std::printf("  GLSL folds constant expressions over the preamble's decimal literals in double and rounds once;\n"
                        "  CpuCrowdSim uses sim_params.hpp's glsl_fold values in their place. Derived constants:\n");
            for (size_t k = 0; k < entries.size(); ++k) {
                const ParityEntry& p = entries[k];
                derived += p.derived;
                const bool same = gpu[k] == p.cpuBits;
                if (p.derived || !same)
                    std::printf("    %-40s GPU %08x  CPU %08x  %s\n", p.name.c_str(), gpu[k], p.cpuBits, same ? "same" : "MISMATCH");
                if (!same) {
                    ++mismatches;
                    char b[200];
                    if (p.isFloat) std::snprintf(b, sizeof b, "%s: GPU bits %08x (%.9g), CPU bits %08x (%.9g)", p.name.c_str(), gpu[k],
                                                 bitsFloat(gpu[k]), p.cpuBits, bitsFloat(p.cpuBits));
                    else std::snprintf(b, sizeof b, "%s: GPU %u, CPU %u", p.name.c_str(), gpu[k], p.cpuBits);
                    check(false, b);
                }
            }
            if (mismatches == 0)
                check(true, "all " + std::to_string(entries.size()) + " shared constants bit-identical on the GPU and the CPU (" +
                      std::to_string(long(entries.size()) - derived) + " preamble constants, " + std::to_string(derived) +
                      " derived: folded expressions)");

            // Coverage: every constant the preamble defines has an entry. And glsl_fold's model input:
            // decimal(value) is the double of the literal the preamble actually emits.
            auto find = [&](const std::string& name) -> const ParityEntry* {
                for (const ParityEntry& p : entries) if (p.name == name) return &p;
                return nullptr;
            };
            std::vector<std::string> uncovered, badDecimal;
            int defines = 0, decimals = 0;
            auto checkDecimal = [&](const std::string& name, double literal) {
                const ParityEntry* p = find(name);
                if (!p) return;
                ++decimals;
                if (glsl_fold::decimal(bitsFloat(p->cpuBits)) != literal) badDecimal.push_back(name);
            };
            std::istringstream pre(shaderPreamble());
            for (std::string line; std::getline(pre, line);) {
                if (line.rfind("const vec2 ", 0) == 0) {   // FEELER_DIRS, FEELER_OFFSETS, PROBE_OFFSETS
                    const std::string name = line.substr(11, line.find('[') - 11);
                    const std::vector<double> v = numericLiterals(line.substr(line.find('=')));
                    for (size_t k = 0; k < v.size(); ++k) {
                        const std::string entry = name + "[" + std::to_string(k / 2) + "]." + (k % 2 ? "y" : "x");
                        if (!find(entry)) uncovered.push_back(entry);
                        checkDecimal(entry, v[k]);
                    }
                    continue;
                }
                if (line.rfind("#define ", 0) != 0) continue;
                ++defines;
                std::istringstream ls(line.substr(8));
                std::string name, value;
                ls >> name;
                std::getline(ls, value);
                const ParityEntry* p = find(name);
                const ParityEntry* px = find(name + ".x");
                if (!p && !px) { uncovered.push_back(name); continue; }
                if (p && (!p->isFloat || p->derived)) continue;   // integers; expressions have no literal
                const std::vector<double> v = numericLiterals(value);
                if (p && v.size() == 1) checkDecimal(name, v[0]);
                if (px && v.size() == 2) { checkDecimal(name + ".x", v[0]); checkDecimal(name + ".y", v[1]); }
            }
            std::string list;
            for (const std::string& n : uncovered) list += " " + n;
            check(uncovered.empty(), "every preamble #define (" + std::to_string(defines) + ") and every element of its const arrays has a parity entry" +
                  (list.empty() ? "" : "; missing:" + list));
            list.clear();
            for (const std::string& n : badDecimal) list += " " + n;
            check(badDecimal.empty() && decimals > 0, "glsl_fold::decimal equals the emitted preamble literal for all " + std::to_string(decimals) +
                  " float literals" + (list.empty() ? "" : "; differs:" + list));
        }
        {   // venue S's preamble. Its neighbour grid and exit test (the venue's GRID_RES, DOMAIN_*, EXIT_*), every VS_*
            // layout literal, and the breakpoints shaders/venue_seated.glsl derives from them ('precise': no fused multiply-add),
            // read back from the GPU and bit-compared with swarm/venue.hpp's floats (src/venue.cpp computes them the same way)
            const Venue& vs = venueS();
            const SeatedLayout& L = vs.layout;
            struct E { std::string glsl; uint32_t cpu; bool isFloat; };
            std::vector<E> es = { { "GRID_RES", uint32_t(vs.gridRes), false }, { "DOMAIN_MIN", floatBits(vs.domainMin), true },
                                  { "DOMAIN_SPAN", floatBits(vs.domainSpan), true }, { "DOMAIN_MAX", floatBits(vs.domainMax()), true },
                                  { "EXIT_DEPTH", floatBits(vs.exitDepth), true }, { "EXIT_MAX_Z", floatBits(vs.exitMaxZ), true } };
            const size_t preambleEntries = es.size() + seatedConstants(L).size();
            for (const SeatedConstant& c : seatedConstants(L)) es.push_back({ c.name, c.isInt ? uint32_t(int(c.value)) : floatBits(c.value), !c.isInt });
            for (int k = 0; k <= L.rows; ++k) {
                es.push_back({ "vsRowFront(" + std::to_string(k) + ")", floatBits(L.row0 + float(k) * L.rowDepth), true });
                es.push_back({ "vsRowTread(" + std::to_string(k) + ")", floatBits(L.firstRow + float(k) * L.rowRise), true });
                es.push_back({ "vsCellTop(VS_SEAT, " + std::to_string(k) + ", 0.0)", floatBits(seated::cellTop(L, seated::SEAT, k, 0.0f)), true });
            }
            std::string src = "#version 430 core\nlayout(local_size_x = 1) in;\n"
                              "layout(std430, binding = 6) writeonly buffer R { uint outv[]; };\nvoid main() {\n";
            for (size_t k = 0; k < es.size(); ++k)
                src += "    outv[" + std::to_string(k) + "] = " + (es[k].isFloat ? "floatBitsToUint(" + es[k].glsl + ")" : "uint(" + es[k].glsl + ")") + ";\n";
            src += "}\n";
            const fs::path tmp = processTempPath("swarm_venue_parity.comp");
            { std::ofstream(tmp) << src; }
            GLuint prog = loadComputeProgram(tmp, {}, &vs);
            fs::remove(tmp);
            GLuint out = makeBuffer(std::vector<uint32_t>(es.size()));
            glUseProgram(prog);
            glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, out);
            glDispatchCompute(1, 1, 1);
            const std::vector<uint32_t> gpu = readBuffer<uint32_t>(out, es.size());
            glDeleteBuffers(1, &out);
            glDeleteProgram(prog);
            long bad = 0;
            for (size_t k = 0; k < es.size(); ++k)
                if (gpu[k] != es[k].cpu) {
                    ++bad;
                    std::printf("    venue S %-36s GPU %08x  CPU %08x  MISMATCH\n", es[k].glsl.c_str(), gpu[k], es[k].cpu);
                }
            check(bad == 0, "venue S: all " + std::to_string(preambleEntries) + " preamble constants (grid, exit test, " + std::to_string(seatedConstants(L).size()) +
                  " VS_* layout literals) and " + std::to_string(es.size() - preambleEntries) +
                  " derived breakpoints (row fronts, treads, seat tops) bit-identical on the GPU and the CPU");
            // glsl_fold's model input: the decimal of each emitted VS_* literal is the float's (the preamble text)
            long badDec = 0;
            std::istringstream pre(seatedDefines(L));
            for (std::string line; std::getline(pre, line);) {
                std::istringstream ls(line.substr(8));
                std::string name, value;
                ls >> name >> value;
                for (const SeatedConstant& c : seatedConstants(L))
                    if (c.name == name && !c.isInt && glsl_fold::decimal(c.value) != std::strtod(value.c_str(), nullptr)) ++badDec;
            }
            check(badDec == 0, "venue S: glsl_fold::decimal equals every emitted VS_* literal");
        }
        {   // the queue-aware exit choice's preamble constants (sim_params.hpp's and venue S's table: the exits' capacities) and
            // the derived CHOICE_STEPS, read back from the GPU and bit-compared with the CPU's
            const Venue& vs = venueS();
            const nav::ChoiceTable& t = nav::choiceForVenue(vs);
            struct E { std::string glsl; uint32_t cpu; bool isFloat; };
            std::vector<E> es = { { "NAV_CELL", floatBits(t.grid.cell), true }, { "NAV_EXITS", uint32_t(t.exitCount), false },
                                  { "NAV_CHOICE_EXIT_SHIFT", uint32_t(nav::CHOICE_EXIT_SHIFT), false }, { "NAV_CHOICE_ANCHOR_MASK", nav::CHOICE_ANCHOR_MASK, false },
                                  { "NAV_CHOICE_EMPTY", nav::CHOICE_EMPTY, false }, { "NAV_CHOICE_FIT", nav::CHOICE_FIT, false },
                                  { "NAV_CHOICE_NONE", nav::CHOICE_NONE, false }, { "NAV_CHOICE_QUEUE_STRIDE", uint32_t(nav::CHOICE_QUEUE_STRIDE), false },
                                  { "NAV_CHOICE_S_PER_UNIT", floatBits(CHOICE_S_PER_UNIT), true }, { "T_CHOICE", floatBits(T_CHOICE), true },
                                  { "CHOICE_REL_MARGIN", floatBits(CHOICE_REL_MARGIN), true }, { "CHOICE_ABS_MARGIN_S", floatBits(CHOICE_ABS_MARGIN_S), true },
                                  { "CHOICE_SWITCH_SHARE", floatBits(CHOICE_SWITCH_SHARE), true }, { "CHOICE_MIN_SWITCHES", uint32_t(CHOICE_MIN_SWITCHES), false },
                                  { "CHOICE_GAIN_BINS", uint32_t(CHOICE_GAIN_BINS), false },
                                  { "NAV_CHOICE_K", uint32_t(nav::CHOICE_K), false }, { "NAV_CHOICE_DIST_EMPTY", nav::CHOICE_DIST_EMPTY, false },
                                  { "NAV_CHOICE_DIST_QUANTUM", floatBits(nav::CHOICE_DIST_QUANTUM), true },
                                  { "NAV_CHOICE_DIST_WORDS", uint32_t(nav::CHOICE_DIST_WORDS), false },
                                  { "NAV_CHOICE_INDEX_MASK", nav::CHOICE_INDEX_MASK, false } };
            for (int e = 0; e < t.exitCount; ++e) es.push_back({ "NAV_EXIT_INV_CAP[" + std::to_string(e) + "]", floatBits(t.invCapS[size_t(e)]), true });
            // The incline speed's constants (host-folded from m/s and tan(27 deg))
            es.push_back({ "V_STAIR_UP", floatBits(V_STAIR_UP), true });
            es.push_back({ "V_STAIR_DOWN", floatBits(V_STAIR_DOWN), true });
            es.push_back({ "INCLINE_INV_REF_SLOPE", floatBits(INCLINE_INV_REF_SLOPE), true });
            const size_t literals = es.size();
            es.push_back({ "max(1, int(T_CHOICE / DT + 0.5))", uint32_t(CHOICE_STEPS), false });   // physics.comp's CHOICE_STEPS
            std::string src = "#version 430 core\nlayout(local_size_x = 1) in;\n"
                              "layout(std430, binding = 6) writeonly buffer R { uint outv[]; };\nvoid main() {\n";
            for (size_t k = 0; k < es.size(); ++k)
                src += "    outv[" + std::to_string(k) + "] = " + (es[k].isFloat ? "floatBitsToUint(" + es[k].glsl + ")" : "uint(" + es[k].glsl + ")") + ";\n";
            src += "}\n";
            const fs::path tmp = processTempPath("swarm_choice_parity.comp");
            { std::ofstream(tmp) << src; }
            GLuint prog = loadComputeProgram(tmp, modelPreamble(vs, { ExitChoice::QueueAware, true }), &vs);
            fs::remove(tmp);
            GLuint out = makeBuffer(std::vector<uint32_t>(es.size()));
            glUseProgram(prog);
            glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, out);
            glDispatchCompute(1, 1, 1);
            const std::vector<uint32_t> gpu = readBuffer<uint32_t>(out, es.size());
            glDeleteBuffers(1, &out);
            glDeleteProgram(prog);
            long bad = 0;
            for (size_t k = 0; k < es.size(); ++k)
                if (gpu[k] != es[k].cpu) {
                    ++bad;
                    std::printf("    exit choice %-36s GPU %08x  CPU %08x  MISMATCH\n", es[k].glsl.c_str(), gpu[k], es[k].cpu);
                }
            check(bad == 0, "queue-aware exit choice and incline speed on venue S: all " + std::to_string(literals) + " preamble constants (" + std::to_string(t.exitCount) +
                  " exit capacities, 3 incline speed constants) and CHOICE_STEPS = " + std::to_string(CHOICE_STEPS) + " (int(T_CHOICE / DT + 0.5)) bit-identical on the GPU and the CPU");
        }

        section("metrics.safety: Safety metrics: write-only side outputs of the step");
        std::vector<GpuMetricCellInfo> metricCellInfo;   // the venue's metric table, shared with metrics.async_counters
        {
            namespace mt = swarm::metrics;
            const std::string driver = std::string((const char*)glGetString(GL_RENDERER)) + " | " + (const char*)glGetString(GL_VERSION);
            const bool sameDriver = driver == GOLDEN_DRIVER;
            auto lastMassTotal = [](const std::vector<GpuMetricCell>& cells) {
                uint64_t t = 0;
                for (const GpuMetricCell& c : cells) t += c.lastMass;
                return t;
            };
            auto countActive = [](const std::vector<GpuBoid>& s) {
                long a = 0;
                for (const GpuBoid& b : s) a += b.position.w != 0.0f;
                return a;
            };

            // (a) Venue: walkable floor area and zone per 1 m cell (CPU sampler)
            const mt::MetricVenue venue = mt::computeMetricVenue(sdfVolumeCPU());
            const std::vector<GpuMetricCellInfo> cellInfo = venue.cellInfo();
            metricCellInfo = cellInfo;
            {
                int withFloor = 0, included = 0, slivers = 0, full = 0;
                double area[mt::ZONE_COUNT] = {}, totalArea = 0.0, sliverArea = 0.0;
                int cellsByZone[mt::ZONE_COUNT] = {};
                for (int c = 0; c < mt::CELLS; ++c) {
                    const float w = venue.walkableM2[size_t(c)];
                    if (w <= 0.0f) continue;
                    ++withFloor;
                    full += w == 1.0f;
                    if (!venue.included[size_t(c)]) { ++slivers; sliverArea += w; continue; }
                    ++included;
                    totalArea += w;
                    area[venue.zone[size_t(c)]] += w;
                    ++cellsByZone[venue.zone[size_t(c)]];
                }
                std::printf("  floor grid: %d x %d cells of %.0f m from (%.0f, %.0f) m; %d x %d samples per cell; walkable = inside the mesh\n"
                            "  footprint, free at z %.3f, solid at z %.3f, outside the fence band. Outer wall inner face at dep %.4f (%.2f m): EXIT zone from there\n",
                            mt::GRID_RES, mt::GRID_RES, mt::CELL_M, mt::GRID_MIN_M, mt::GRID_MIN_M, mt::SUBSAMPLES, mt::SUBSAMPLES,
                            mt::FLOOR_PROBE_TOP_Z, mt::FLOOR_PROBE_BOTTOM_Z, venue.outerWallInnerDepth, units::metres(venue.outerWallInnerDepth));
                std::printf("  cells with walkable floor %d (fully walkable %d); included %d (%.1f m^2); excluded below %.2f m^2: %d (%.3f m^2)\n",
                            withFloor, full, included, totalArea, mt::MIN_WALKABLE_M2, slivers, sliverArea);
                std::printf("  by zone (included cells, area):");
                for (uint32_t z = 0; z < mt::ZONE_COUNT; ++z) std::printf(" %s %d / %.1f m^2%s", mt::zoneName(z), cellsByZone[z], area[z], z + 1 < mt::ZONE_COUNT ? "," : "\n");
                std::printf("  exit gap widths at dep %.2f (geometric, m):", EXIT_DEPTH);
                for (int e = 0; e < mt::EXIT_GAPS; ++e) std::printf(" %s %.3f", mt::exitName(e).c_str(), venue.exitWidthM[size_t(e)]);
                std::printf("\n");
                bool exitsOk = true;
                for (int e = 0; e < mt::EXIT_GAPS; ++e) exitsOk &= venue.exitWidthM[size_t(e)] > 5.0f && venue.exitWidthM[size_t(e)] < 6.5f;
                check(cellsByZone[mt::ZONE_EXIT] >= 4 && cellsByZone[mt::ZONE_TREAD] > 0 && cellsByZone[mt::ZONE_AISLE] > 0 &&
                      cellsByZone[mt::ZONE_WALKWAY] > 0 && cellsByZone[mt::ZONE_AVENUE] > 0 && cellsByZone[mt::ZONE_PITCH] > 0 && exitsOk,
                      "venue: every zone has cells, the 4 exits have EXIT cells, exit gaps 5-6.5 m wide (venue.terrace_passage_widths: 5.67-5.72 m)");

                // The venue's capacity metadata (swarm/venue_capacity.hpp) from this table: the occupiable floor is
                // every cell's walkable area minus the pitch's (fenced, no gates), the jam capacity that floor at hexagonal packing
                double walkable = 0.0, pitchArea = 0.0;
                for (int c = 0; c < mt::CELLS; ++c) {
                    walkable += venue.walkableM2[size_t(c)];
                    if (venue.zone[size_t(c)] == mt::ZONE_PITCH) pitchArea += venue.walkableM2[size_t(c)];
                }
                const swarm::venue::Capacity& cap = swarm::venue::TERRACE;
                const double occupiable = walkable - pitchArea;
                const long jam = std::lround(occupiable * swarm::venue::HEX_PACKING_P_M2);
                std::printf("  capacity: walkable %.1f m^2 - pitch %.1f m^2 = occupiable %.1f m^2, x %.4f persons/m^2 = jam capacity %ld; "
                            "venue_capacity.hpp: %.1f m^2, jam %d, design %d\n", walkable, pitchArea, occupiable, swarm::venue::HEX_PACKING_P_M2, jam,
                            cap.occupiableM2, cap.jam, cap.design);
                check(std::abs(occupiable - cap.occupiableM2) < 0.05 && jam == cap.jam,
                      "venue capacity metadata matches stadium.sdf: occupiable " + std::to_string(occupiable) + " m^2, jam capacity " + std::to_string(jam));
            }

            // (b) The metric shaders compile with empty logs; every metric constant is bit-identical on the GPU
            {
                CerrCapture cap;
                mt::CrowdMetrics probe(shaderDir, 256, cellInfo);
                std::string log = cap.release();
                check(log.empty(), "metrics_deposit.comp + metrics_finalize.comp compile and link with empty logs" + (log.empty() ? std::string() : ":\n" + log));

                struct C { const char* glsl; uint32_t bits; bool isFloat; };
                const C consts[] = {
                    { "METRIC_GRID_RES", uint32_t(mt::GRID_RES), false }, { "METRIC_CELLS", uint32_t(mt::CELLS), false },
                    { "METRIC_CELLS_PER_UNIT", floatBits(mt::CELLS_PER_UNIT), true }, { "METRIC_GRID_OFFSET", floatBits(mt::GRID_OFFSET), true },
                    { "METRIC_SUBCELL", mt::SUBCELL, false }, { "METRIC_SPEED_M_S_PER_UNIT", floatBits(mt::SPEED_M_S_PER_UNIT), true },
                    { "METRIC_CRUSH_INDEX", uint32_t(mt::CRUSH_INDEX), false }, { "METRIC_EXIT_SLOTS", uint32_t(mt::EXIT_SLOTS), false },
                    { "METRIC_EXIT_POS_X", uint32_t(mt::EXIT_POS_X), false }, { "METRIC_EXIT_NEG_X", uint32_t(mt::EXIT_NEG_X), false },
                    { "METRIC_EXIT_POS_Y", uint32_t(mt::EXIT_POS_Y), false }, { "METRIC_EXIT_NEG_Y", uint32_t(mt::EXIT_NEG_Y), false },
                    { "METRIC_EXIT_OTHER", uint32_t(mt::EXIT_OTHER), false }, { "METRIC_EXIT_DOOR0", uint32_t(mt::EXIT_DOOR0), false },
                    { "METRIC_GANGWAY_SLOTS", uint32_t(mt::GANGWAY_SLOTS), false } };
                std::string src = "#version 430 core\nlayout(local_size_x = 1) in;\n"
                                  "layout(std430, binding = 6) writeonly buffer R { uint outv[]; };\nvoid main() {\n";
                for (size_t k = 0; k < std::size(consts); ++k)
                    src += "    outv[" + std::to_string(k) + "] = " + (consts[k].isFloat ? "floatBitsToUint(" : "uint(") + consts[k].glsl + ");\n";
                src += "}\n";
                const fs::path tmp = processTempPath("swarm_metric_parity.comp");
                { std::ofstream(tmp) << src; }
                GLuint prog = loadComputeProgram(tmp, mt::metricsPreamble());
                fs::remove(tmp);
                GLuint out = makeBuffer(std::vector<uint32_t>(std::size(consts)));
                glUseProgram(prog);
                glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, out);
                glDispatchCompute(1, 1, 1);
                const std::vector<uint32_t> gpu = readBuffer<uint32_t>(out, std::size(consts));
                glDeleteBuffers(1, &out);
                glDeleteProgram(prog);
                std::string bad;
                int defines = 0;
                for (size_t k = 0; k < std::size(consts); ++k)
                    if (gpu[k] != consts[k].bits) bad += std::string(" ") + consts[k].glsl;
                std::istringstream pre(mt::metricsPreamble());
                for (std::string line; std::getline(pre, line);) defines += line.rfind("#define ", 0) == 0;
                check(bad.empty() && defines == int(std::size(consts)), "metric preamble: all " + std::to_string(defines) +
                      " constants bit-identical on the GPU and the CPU (CELLS_PER_UNIT 31.25, GRID_OFFSET 31.5, SPEED_M_S_PER_UNIT " +
                      std::to_string(mt::SPEED_M_S_PER_UNIT) + ")" + (bad.empty() ? "" : "; differ:" + bad));
            }

            // (c) Synthetic placements with known answers. Blocks of K = 1, 2, 3, 5, 6 agents stacked on the centre
            // of 5 fully walkable avenue cells (1.00 m^2: density K / m^2, all mass in that cell), one agent on a grid
            // vertex (a quarter person in each of 4 cells), speed 0.5 model = 0.8933 m/s. Steps 1-20 this state;
            // step 21 the same plus 5 agents leaving (one per exit slot, other included); steps 22-31 nobody active.
            {
                std::vector<int> blockCells;
                for (int c = 0; c < mt::CELLS && blockCells.size() < 5; ++c) {
                    if (venue.walkableM2[size_t(c)] != 1.0f || venue.zone[size_t(c)] != mt::ZONE_AVENUE) continue;
                    bool apart = true;   // no shared neighbourhood with an earlier block
                    for (int b : blockCells) apart &= std::abs(b % mt::GRID_RES - c % mt::GRID_RES) > 2 || std::abs(b / mt::GRID_RES - c / mt::GRID_RES) > 2;
                    if (apart) blockCells.push_back(c);
                }
                int vertexCell = -1;   // lower-left of 4 fully walkable avenue cells, apart from the blocks
                for (int c = 0; c < mt::CELLS && vertexCell < 0; ++c) {
                    const int ix = c % mt::GRID_RES, iy = c / mt::GRID_RES;
                    if (ix + 1 >= mt::GRID_RES || iy + 1 >= mt::GRID_RES) continue;
                    bool ok = true;
                    for (int d : { 0, 1, mt::GRID_RES, mt::GRID_RES + 1 })
                        ok &= venue.walkableM2[size_t(c + d)] == 1.0f && venue.zone[size_t(c + d)] == mt::ZONE_AVENUE;
                    for (int b : blockCells) ok &= std::abs(b % mt::GRID_RES - ix) > 3 || std::abs(b / mt::GRID_RES - iy) > 3;
                    if (ok) vertexCell = c;
                }
                // A model position whose deposit is exactly the expected one (nudged by ulps if float rounding moves it)
                auto exactPos = [&](glm::vec2 metres, int cell, uint32_t weight0) {
                    glm::vec2 p(float(units::modelLength(metres.x)), float(units::modelLength(metres.y)));
                    for (int i = 0; i < 64; ++i) {
                        const mt::CicDeposit d = mt::cicDeposit(p);
                        if (d.cell[0] == cell && d.weight[0] == weight0 && (weight0 != mt::MASS_ONE / 4 || d.weight[3] == weight0)) return p;
                        p.x = std::nextafter(p.x, (i & 1) ? 1.0f : -1.0f);
                        p.y = std::nextafter(p.y, (i & 2) ? 1.0f : -1.0f);
                    }
                    throw std::runtime_error("metrics.safety: no exact synthetic position");
                };
                const int K[5] = { 1, 2, 3, 5, 6 };
                const int N = 256;
                GpuBoid parked;
                parked.position = glm::vec4(PARK_COORD, PARK_COORD, PARK_COORD, 0.0f);
                parked.velocity = glm::vec4(0.0f);
                std::vector<GpuBoid> s1(N, parked);
                const glm::vec4 vel(0.3f, 0.4f, 0.0f, 0.5f);
                int n = 0;
                for (int b = 0; b < 5 && blockCells.size() == 5; ++b) {
                    const glm::vec2 p = exactPos(mt::cellCentreM(blockCells[size_t(b)]), blockCells[size_t(b)], mt::MASS_ONE);
                    for (int k = 0; k < K[b]; ++k) s1[size_t(n++)] = { glm::vec4(p, 0.01f, 1.0f), vel };
                }
                if (vertexCell >= 0)
                    s1[size_t(n++)] = { glm::vec4(exactPos(mt::cellCentreM(vertexCell) + glm::vec2(0.5f), vertexCell, mt::MASS_ONE / 4), 0.01f, 1.0f), vel };
                // Leaving in step 21: last active positions in each exit gap (+x, -x, +y, -y) and one outside the avenues
                const glm::vec2 leaving[5] = { { 0.94f, 0.01f }, { -0.94f, -0.02f }, { 0.03f, 0.94f }, { -0.01f, -0.94f }, { 0.30f, 0.94f } };
                const int firstLeaving = n;
                std::vector<GpuBoid> s2 = s1;   // prev of step 21
                for (int e = 0; e < 5; ++e) s2[size_t(n + e)] = { glm::vec4(leaving[e], 0.01f, 1.0f), vel };
                const std::vector<GpuBoid> none(N, parked);

                GLuint b1 = makeBuffer(s1), b2 = makeBuffer(s2), b0 = makeBuffer(none);
                mt::CrowdMetrics gm(shaderDir, N, cellInfo);
                mt::MetricsReference ref(N, cellInfo);
                std::vector<GpuMetricCell> after20;
                for (int step = 1; step <= 31; ++step) {
                    const GLuint prev = step <= 20 ? b1 : step == 21 ? b2 : b0, cur = step <= 21 ? b1 : b0;
                    const std::vector<GpuBoid>& sp = step <= 20 ? s1 : step == 21 ? s2 : none;
                    const std::vector<GpuBoid>& sc = step <= 21 ? s1 : none;
                    gm.record(prev, cur);
                    ref.record(sp, sc);
                    if (step == 20) after20 = gm.readCells();
                }
                const std::vector<GpuMetricCell> cells = gm.readCells();
                const GpuMetricCounters ctr = gm.readCounters();
                const std::vector<uint32_t> evac = gm.readEvacSteps();
                glDeleteBuffers(1, &b1);
                glDeleteBuffers(1, &b2);
                glDeleteBuffers(1, &b0);

                const double dt = DT_REAL_S;
                const float speedExpected = 0.5f * mt::SPEED_M_S_PER_UNIT;
                std::printf("  synthetic: blocks of K agents on fully walkable avenue cells, 21 steps occupied (DT %.4f s), then 10 empty\n", dt);
                std::printf("  %3s %6s %9s %9s | %10s %10s %10s | %12s %13s\n", "K", "cell", "density", "peak", "LoS E s", "LoS F s", "crush s",
                            "exposure p.s", "mean speed");
                bool blocksOk = blockCells.size() == 5;
                for (int b = 0; b < 5 && blocksOk; ++b) {
                    const GpuMetricCell& c = cells[size_t(blockCells[size_t(b)])];
                    const double density = double(after20[size_t(blockCells[size_t(b)])].lastMass) / mt::MASS_ONE / 1.0;
                    const double peak = double(c.peakMass) / mt::MASS_ONE;
                    const double tE = c.stepsAbove[0] * dt, tF = c.stepsAbove[1] * dt, tC = c.stepsAbove[2] * dt;
                    const double exposure = double(mt::sum64(c.exposureMassSteps)) / mt::MASS_ONE * dt;
                    const double meanSpeed = double(mt::sum64(c.speedMassSteps)) / double(mt::sum64(c.massSteps));
                    std::printf("  %3d %6d %9.4f %9.4f | %10.4f %10.4f %10.4f | %12.4f %9.4f m/s\n", K[b], blockCells[size_t(b)], density, peak, tE, tF, tC,
                                exposure, meanSpeed);
                    const uint32_t k = uint32_t(K[b]);
                    const uint32_t expAbove[3] = { k >= 2 ? 21u : 0u, k >= 3 ? 21u : 0u, k >= 5 ? 21u : 0u };   // 1.08, 2.17, 5 p/m^2
                    blocksOk &= after20[size_t(blockCells[size_t(b)])].lastMass == k * mt::MASS_ONE && c.peakMass == k * mt::MASS_ONE &&
                                c.lastMass == 0 && c.occupiedSteps == 21 && c.stepsAbove[0] == expAbove[0] && c.stepsAbove[1] == expAbove[1] &&
                                c.stepsAbove[2] == expAbove[2] && c.stepsAbove[3] == 0 && mt::sum64(c.massSteps) == 21ull * k * mt::MASS_ONE &&
                                mt::sum64(c.exposureMassSteps) == (k >= 5 ? 21ull * k * mt::MASS_ONE : 0ull) &&
                                std::abs(meanSpeed - double(speedExpected)) < 1e-4;
                }
                check(blocksOk, "known answers: density K / 1 m^2 exactly (all mass in the block's cell); time above LoS E (1.08), LoS F (2.17), "
                                "crush (5, reached exactly at K = 5) = 21 steps x DT where K reaches it, else 0; exposure = 21 x K x DT person-s "
                                "for K >= 5; mean speed 0.8933 m/s; nothing counted in the 10 empty steps");
                bool vertexOk = vertexCell >= 0;
                for (int d : { 0, 1, mt::GRID_RES, mt::GRID_RES + 1 })
                    vertexOk &= vertexCell >= 0 && after20[size_t(vertexCell + d)].lastMass == mt::MASS_ONE / 4 && cells[size_t(vertexCell + d)].stepsAbove[0] == 0;
                check(vertexOk, "an agent on a grid vertex deposits exactly a quarter person (16384) in each of the 4 cells around it");
                long massEverywhere = 0;
                for (const GpuMetricCell& c : after20) massEverywhere += c.lastMass;
                check(massEverywhere == long(n) * long(mt::MASS_ONE), "step 20: deposited mass = " + std::to_string(n) + " active x MASS_ONE exactly");
                bool exitsOk = ctr.evacuated == 5 && ctr.active == 0 && ctr.step == 31;
                for (int e = 0; e < mt::EXIT_SLOTS; ++e) exitsOk &= ctr.exits[e] == (e <= mt::EXIT_OTHER ? 1u : 0u);   // the terrace has no doors
                for (int i = 0; i < N; ++i) exitsOk &= evac[size_t(i)] == (i >= firstLeaving && i < firstLeaving + 5 ? 21u : 0u);
                check(exitsOk, "evacuation events: one agent per exit slot (+x, -x, +y, -y, other) counted once, evacuated total 5, "
                               "evacuation step 21 recorded for exactly those 5 agents; counters step 31, active 0");
                bool refOk = std::memcmp(&ctr, &ref.counters, sizeof ctr) == 0 && evac == ref.evacStep;
                for (int c = 0; c < mt::CELLS; ++c) {
                    GpuMetricCell a = cells[size_t(c)], r = ref.cells[size_t(c)];
                    refOk &= std::memcmp(&a, &r, sizeof a) == 0;
                }
                check(refOk, "GPU counters, evacuation steps and all 4096 cell accumulators bit-identical to the CPU reference (MetricsReference)");
            }

            // (d) Real run, N = 4096 from spawn to full evacuation with metrics ON, against the CPU reference
            // every step: conservation, exit totals, evacuation steps; the step itself unchanged
            {
                CrowdSim sim(shaderDir, NUM_AGENTS);
                sim.upload(spawn);
                mt::CrowdMetrics gm(shaderDir, NUM_AGENTS, cellInfo);
                mt::MetricsReference ref(NUM_AGENTS, cellInfo);
                std::vector<uint32_t> leftAt(NUM_AGENTS, 0);
                long conservationBad = 0, countersBad = 0, otherExits = 0;
                int evacStep = -1;
                uint64_t hashGolden = 0;
                double maxSpeedDev = 0.0;
                for (int step = 1; step <= 6000 && evacStep < 0; ++step) {
                    sim.step(sdfTex);
                    gm.afterStep(sim);
                    const std::vector<GpuBoid> prev = readBuffer<GpuBoid>(sim.previousStateBuffer(), NUM_AGENTS);
                    const std::vector<GpuBoid> cur = readBuffer<GpuBoid>(sim.currentStateBuffer(), NUM_AGENTS);
                    ref.record(prev, cur);
                    for (int i = 0; i < NUM_AGENTS; ++i)
                        if (prev[size_t(i)].position.w != 0.0f && cur[size_t(i)].position.w == 0.0f) leftAt[size_t(i)] = uint32_t(step);
                    const long active = countActive(cur);
                    const std::vector<GpuMetricCell> cells = gm.readCells();
                    const GpuMetricCounters ctr = gm.readCounters();
                    conservationBad += lastMassTotal(cells) != uint64_t(active) * mt::MASS_ONE;
                    uint32_t exitSum = 0;
                    for (uint32_t e : ctr.exits) exitSum += e;
                    countersBad += ctr.step != uint32_t(step) || ctr.active != uint32_t(active) || ctr.evacuated != uint32_t(NUM_AGENTS - active) ||
                                   exitSum != ctr.evacuated || ctr.activeAccum != 0;
                    otherExits = ctr.exits[mt::EXIT_OTHER];
                    if (step == golden::GOLDEN_STEPS) hashGolden = stateHash(cur);
                    if (active == 0) evacStep = step;
                }
                const GpuMetricCounters ctr = gm.readCounters();
                const std::vector<uint32_t> evac = gm.readEvacSteps();
                const std::vector<GpuMetricCell> cells = gm.readCells();
                long cellMismatch = 0;
                uint64_t excludedMass = 0, totalMass = 0;
                for (int c = 0; c < mt::CELLS; ++c) {
                    const GpuMetricCell& a = cells[size_t(c)];
                    const GpuMetricCell& r = ref.cells[size_t(c)];
                    // every mass-derived field exactly; the speed sums within one unit per deposit (GPU length() vs std::sqrt)
                    cellMismatch += a.lastMass != r.lastMass || a.peakMass != r.peakMass || a.occupiedSteps != r.occupiedSteps ||
                                    std::memcmp(a.stepsAbove, r.stepsAbove, sizeof a.stepsAbove) != 0 || mt::sum64(a.massSteps) != mt::sum64(r.massSteps) ||
                                    mt::sum64(a.exposureMassSteps) != mt::sum64(r.exposureMassSteps);
                    const double ds = std::abs(double(mt::sum64(a.speedMassSteps)) - double(mt::sum64(r.speedMassSteps)));
                    if (mt::sum64(r.massSteps) > 0) maxSpeedDev = std::max(maxSpeedDev, ds / double(mt::sum64(r.massSteps)));
                    totalMass += mt::sum64(a.massSteps);
                    if (!venue.included[size_t(c)]) excludedMass += mt::sum64(a.massSteps);
                }
                std::printf("  N = %d with metrics ON: 100%% evacuated at step %d; exits +x %u, -x %u, +y %u, -y %u, other %u\n", NUM_AGENTS, evacStep,
                            ctr.exits[0], ctr.exits[1], ctr.exits[2], ctr.exits[3], ctr.exits[4]);
                std::printf("  person-steps deposited %.1f, of them in excluded cells (walkable < %.2f m^2) %.2f (%.4f%%); GPU vs CPU mean-speed\n"
                            "  difference max %.2e m/s per cell (GPU length() vs std::sqrt)\n", double(totalMass) / mt::MASS_ONE, mt::MIN_WALKABLE_M2,
                            double(excludedMass) / mt::MASS_ONE, totalMass ? 100.0 * double(excludedMass) / double(totalMass) : 0.0, maxSpeedDev);
                check(evacStep == fullyEvacuatedAt, "metrics ON: full evacuation at the same step as engine.pipeline_invariants (" + std::to_string(evacStep) + ")");
                if (sameDriver)
                    check(hashGolden == GOLDEN[golden::GOLDEN_GPU_4096].hash, "metrics ON: GPU N = 4096 state after " + std::to_string(golden::GOLDEN_STEPS) +
                          " steps matches the pinned golden hash (metrics OFF: parity.golden_terrace)");
                check(conservationBad == 0, "every step: deposited mass = active agents x MASS_ONE exactly (round-off bound of the total: 0; " +
                      std::to_string(conservationBad) + " steps off)");
                check(countersBad == 0 && otherExits == 0, "every step: counters step, active and evacuated match the state; the 4 exits' total = "
                      "evacuated = N - active; exit 'other' never used");
                check(evac == leftAt && evac == ref.evacStep && std::memcmp(&ctr, &ref.counters, sizeof ctr) == 0,
                      "evacuation step per agent = the step its state turned inactive; exits and counters equal the CPU reference");
                check(cellMismatch == 0 && maxSpeedDev < 1e-5, "all cell accumulators equal the CPU reference: mass, peak, occupied, steps above "
                      "each threshold, mass and exposure sums exactly; mean speed within 1e-5 m/s (" + std::to_string(cellMismatch) + " cells differ)");
            }

            // (e) Golden with metrics ON at N = 65536 (GOLDEN_STEPS steps)
            {
                const int n = 65536;
                CrowdSim sim(shaderDir, n);
                sim.upload(spawnBleacherCrowd(n));
                mt::CrowdMetrics gm(shaderDir, n, cellInfo);
                for (int i = 0; i < golden::GOLDEN_STEPS; ++i) { sim.step(sdfTex); gm.afterStep(sim); }
                const std::vector<GpuBoid> st = readBuffer<GpuBoid>(sim.currentStateBuffer(), n);
                const std::vector<GpuMetricCell> cells = gm.readCells();
                const GpuMetricCounters ctr = gm.readCounters();
                const long active = countActive(st);
                if (sameDriver)
                    check(stateHash(st) == GOLDEN[golden::GOLDEN_GPU_65536].hash, "metrics ON: GPU N = 65536 state after " +
                          std::to_string(golden::GOLDEN_STEPS) + " steps matches the pinned golden hash");
                check(lastMassTotal(cells) == uint64_t(active) * mt::MASS_ONE && ctr.active == uint32_t(active) &&
                      ctr.evacuated == uint32_t(n - active), "N = 65536, step " + std::to_string(golden::GOLDEN_STEPS) + ": mass = " +
                      std::to_string(active) + " active x MASS_ONE exactly, counters match");
            }
            glErrorFree &= glGetError() == GL_NO_ERROR;
        }

        section("metrics.async_counters: Diagnostic counters for UIs: fence-gated asynchronous reads that never wait");
        {
            using Clock = std::chrono::steady_clock;
            auto ms = [](Clock::duration d) { return std::chrono::duration<double, std::milli>(d).count(); };
            // That capture() and poll() never wait is checked without a clock (a poll that returns no data while
            // its copy is still in flight did not wait for the fence; a capture that skips because every ring slot is in
            // flight did not wait for a slot). Their CPU cost is judged over many calls instead of the slowest single call:
            // a single slow call can be an OS scheduling or first-use
            // spike that says nothing about waiting. Every capture and poll call of the three phases below is a sample (at
            // least TIMING_MIN_CALLS of each); limits: p99 < TIMING_P99_MS and max < TIMING_MAX_MS.
            constexpr size_t TIMING_MIN_CALLS = 1000;
            constexpr double TIMING_P99_MS = 2.0, TIMING_MAX_MS = 10.0;
            std::vector<double> captureMs, pollMs;
            auto timedCaptureAndPoll = [&](AsyncCounterReader& rd, GLuint src) {
                const Clock::time_point t0 = Clock::now();
                rd.capture(src);
                const Clock::time_point t1 = Clock::now();
                const bool fresh = rd.poll();
                const Clock::time_point t2 = Clock::now();
                captureMs.push_back(ms(t1 - t0));
                pollMs.push_back(ms(t2 - t1));
                return fresh;
            };
            const int n = 65536, warm = 5, burst = 40;
            CrowdSim sim(shaderDir, n);
            sim.upload(spawnBleacherCrowd(n));
            metrics::CrowdMetrics gm(shaderDir, n, metricCellInfo);
            AsyncCounterReader reader(sizeof(GpuMetricCounters), 4);
            for (int i = 0; i < warm; ++i) { sim.step(sdfTex); gm.afterStep(sim); }
            glFinish();
            // A burst of steps far ahead of the GPU (N = 65536, metrics ON), one capture and one poll after each,
            // as an application would per frame
            int pollsPending = 0, received = 0;
            uint64_t maxLag = 0;
            bool monotonic = true, consistent = true;
            uint32_t lastStep = 0;
            const Clock::time_point b0 = Clock::now();
            for (int i = 0; i < burst; ++i) {
                sim.step(sdfTex);
                gm.afterStep(sim);
                const bool fresh = timedCaptureAndPoll(reader, gm.countersBuffer());
                if (!fresh && reader.inFlight() > 0) ++pollsPending;   // returned while the GPU had not reached the fence
                if (fresh) {
                    ++received;
                    const GpuMetricCounters c = reader.latestAs<GpuMetricCounters>();
                    uint32_t exitSum = 0;
                    for (uint32_t e : c.exits) exitSum += e;
                    monotonic &= c.step > lastStep;
                    consistent &= c.active + c.evacuated == uint32_t(n) && exitSum == c.evacuated && c.step >= uint32_t(warm + 1);
                    lastStep = c.step;
                }
                maxLag = std::max(maxLag, reader.capturedSequence() - reader.latestSequence());
            }
            const double queued = ms(Clock::now() - b0);
            const int burstPending = pollsPending, burstReceived = received;
            const uint64_t burstSkipped = reader.skipped();
            // A synchronous read right now waits for the whole burst on the GPU (for contrast)
            const Clock::time_point s0 = Clock::now();
            gm.readCounters();
            const double syncMs = ms(Clock::now() - s0);
            glFinish();
            reader.poll();   // collects everything in flight
            std::printf("  burst: N = %d, metrics ON, %d steps queued in %.2f ms (CPU), ring of %d, capture + poll after every step:\n"
                        "    %d of %d polls returned while their copy was still in flight, %d readings; %llu captures skipped (ring full);\n"
                        "    a synchronous read after the burst took %.3f ms (it waits)\n",
                        n, burst, queued, reader.ringSize(), burstPending, burst, burstReceived, (unsigned long long)burstSkipped, syncMs);
            check(burstPending > 0 && burstSkipped > 0,
                  "never waits: with the GPU " + std::to_string(int(syncMs)) + " ms behind, polls return without data while their copy is in flight (" +
                  std::to_string(burstPending) + " of " + std::to_string(burst) + ") and captures skip when every ring slot is in flight (" +
                  std::to_string(burstSkipped) + ") instead of waiting");

            // Frame-paced, as an application: one step, one capture, one poll, then other frame work (CPU) for the rest
            // of the frame. A step at N = 65536 (32 projection iterations) takes longer on the GPU than a
            // 2 ms frame, so the frame is max(2 ms, 1.5 x one step's GPU time, measured here); with a frame
            // shorter than the GPU work the backlog grows without bound and few copies can complete
            glFinish();
            const Clock::time_point m0 = Clock::now();
            sim.step(sdfTex);
            gm.afterStep(sim);
            glFinish();
            const double frameMs = std::max(2.0, 1.5 * ms(Clock::now() - m0));
            const int frames = 60;
            uint64_t pacedLag = 0;
            for (int f = 0; f < frames; ++f) {
                sim.step(sdfTex);
                gm.afterStep(sim);
                const bool fresh = timedCaptureAndPoll(reader, gm.countersBuffer());
                const Clock::time_point t2 = Clock::now();
                if (fresh) {
                    ++received;
                    const GpuMetricCounters c = reader.latestAs<GpuMetricCounters>();
                    uint32_t exitSum = 0;
                    for (uint32_t e : c.exits) exitSum += e;
                    monotonic &= c.step > lastStep;
                    consistent &= c.active + c.evacuated == uint32_t(n) && exitSum == c.evacuated && c.step >= uint32_t(warm + 1);
                    lastStep = c.step;
                }
                maxLag = std::max(maxLag, reader.capturedSequence() - reader.latestSequence());
                pacedLag = std::max(pacedLag, reader.capturedSequence() - reader.latestSequence());
                while (ms(Clock::now() - t2) < frameMs) {}
            }
            const int pacedReceived = received - burstReceived;
            // Settled: everything finished, the newest capture read; equals a synchronous read
            glFinish();
            reader.poll();
            reader.capture(gm.countersBuffer());   // a capture of the current state (the last frame's may have been skipped)
            glFinish();
            reader.poll();
            const GpuMetricCounters settled = reader.latestAs<GpuMetricCounters>();
            const GpuMetricCounters syncRead = gm.readCounters();
            std::printf("  paced: %d frames (1 step + capture + poll + %.2f ms): %d readings, latest reading at most %llu frames behind\n", frames,
                        frameMs, pacedReceived, (unsigned long long)pacedLag);
            std::printf("  settled: step %u, active %u, evacuated %u; synchronous read: step %u, active %u, evacuated %u\n", settled.step,
                        settled.active, settled.evacuated, syncRead.step, syncRead.active, syncRead.evacuated);
            check(pacedReceived >= frames / 2 && monotonic && consistent && maxLag <= uint64_t(reader.ringSize()),
                  "frame-paced: readings arrive (" + std::to_string(pacedReceived) + " of " + std::to_string(frames) +
                  " frames), each a consistent snapshot (active + evacuated = N, exits' total = evacuated), steps increase, at most ring-size (" +
                  std::to_string(reader.ringSize()) + ") captures late");
            check(reader.latestSequence() == reader.capturedSequence() && std::memcmp(&settled, &syncRead, sizeof settled) == 0 &&
                  settled.step == uint32_t(warm + burst + 1 + frames),
                  "once settled, the latest reading equals a synchronous read (step " + std::to_string(settled.step) + ")");

            // Sustained: TIMING_MIN_CALLS frames of 2 ms at N = 4096 (the GPU keeps up: every capture queues a
            // copy and most polls read one), the bulk of the timing samples
            {
                const int n2 = NUM_AGENTS, frames2 = int(TIMING_MIN_CALLS);
                const double frame2Ms = 2.0;
                CrowdSim sim2(shaderDir, n2);
                sim2.upload(spawn);
                metrics::CrowdMetrics gm2(shaderDir, n2, metricCellInfo);
                AsyncCounterReader reader2(sizeof(GpuMetricCounters), 4);
                int received2 = 0;
                bool ok2 = true;
                uint32_t last2 = 0;
                for (int f = 0; f < frames2; ++f) {
                    sim2.step(sdfTex);
                    gm2.afterStep(sim2);
                    const bool fresh = timedCaptureAndPoll(reader2, gm2.countersBuffer());
                    const Clock::time_point t2 = Clock::now();
                    if (fresh) {
                        ++received2;
                        const GpuMetricCounters c = reader2.latestAs<GpuMetricCounters>();
                        uint32_t exitSum = 0;
                        for (uint32_t e : c.exits) exitSum += e;
                        ok2 &= c.step > last2 && c.active + c.evacuated == uint32_t(n2) && exitSum == c.evacuated;
                        last2 = c.step;
                    }
                    ok2 &= reader2.capturedSequence() - reader2.latestSequence() <= uint64_t(reader2.ringSize());
                    while (ms(Clock::now() - t2) < frame2Ms) {}
                }
                glFinish();
                std::printf("  sustained: N = %d, %d frames (1 step + capture + poll + %.1f ms): %d readings, %llu captures skipped\n", n2,
                            frames2, frame2Ms, received2, (unsigned long long)reader2.skipped());
                check(received2 >= frames2 / 2 && ok2, "sustained: readings arrive (" + std::to_string(received2) + " of " +
                      std::to_string(frames2) + " frames), each consistent, steps increase, at most ring-size captures late");
            }

            // CPU cost per call over every phase (nearest-rank percentiles)
            auto stats = [](std::vector<double> v) {
                std::sort(v.begin(), v.end());
                auto q = [&](double p) { return v.empty() ? 0.0 : v[std::max<size_t>(1, size_t(std::ceil(p * double(v.size())))) - 1]; };
                return std::array<double, 3>{ q(0.50), q(0.99), v.empty() ? 0.0 : v.back() };
            };
            const std::array<double, 3> cs = stats(captureMs), ps = stats(pollMs);
            std::printf("  CPU per call over the three phases: capture %zu calls, p50 %.4f / p99 %.4f / max %.4f ms; poll %zu calls, p50 %.4f / p99 "
                        "%.4f / max %.4f ms\n", captureMs.size(), cs[0], cs[1], cs[2], pollMs.size(), ps[0], ps[1], ps[2]);
            char tb[320];
            std::snprintf(tb, sizeof tb, "CPU cost per call over >= %zu calls each: capture p99 %.4f / max %.4f ms, poll p99 %.4f / max %.4f ms "
                          "(limits p99 < %.0f ms, max < %.0f ms)", TIMING_MIN_CALLS, cs[1], cs[2], ps[1], ps[2], TIMING_P99_MS, TIMING_MAX_MS);
            check(captureMs.size() >= TIMING_MIN_CALLS && pollMs.size() >= TIMING_MIN_CALLS && cs[1] < TIMING_P99_MS && ps[1] < TIMING_P99_MS &&
                  cs[2] < TIMING_MAX_MS && ps[2] < TIMING_MAX_MS, tb);
            glErrorFree &= glGetError() == GL_NO_ERROR;
        }

        section("validation.plausibility_terrace: Plausibility: hard bodies, neighbour grid, floors, fence, walls, speed, density after every step of a full N = 4096 evacuation");
        {
            namespace pl = swarm::plausibility;
            CrowdSim sim(shaderDir, NUM_AGENTS);
            sim.upload(spawn);
            metrics::CrowdMetrics gm(shaderDir, NUM_AGENTS, metricCellInfo);
            // The stadium is the baked terrace reference venue (pl::VenueKind): its venue-geometry overlap cases are exempt
            // from the crowd limits; an analytic venue runs this with VenueKind::Analytic, no exemption
            const pl::Result r = pl::runEvacuation(sim, sdfTex, spawn, gm, metricCellInfo, checkpoints.back(), pl::VenueKind::BakedTerrace);
            pl::print(r);
            std::printf("  overlap depth by population: pair-steps (share), p50 / p99 / max, pair-steps above 2 / 5 / 10 / 20%% of BODY_DIAM\n");
            pl::printOverlapCases(r, "    ");
            check(r.evacStep == fullyEvacuatedAt && !r.nan, "the checked run evacuates at the step of engine.pipeline_invariants (" + std::to_string(r.evacStep) + "), no NaN");
            char b[512];
            // Crowd cases p99 <= 5%, max <= 20% of BODY_DIAM (2 / 8 cm): body compression of a few centimetres under
            // crowd pressure (not yet checked against the literature); tools/plausibility.hpp gives the reasoning
            std::snprintf(b, sizeof b, "hard bodies, crowd cases (both agents steadily grounded on walkable floor; %zu pair-steps): overlap depth p99 "
                          "%.4f <= %.2f and max %.4f <= %.2f of BODY_DIAM over every step (body compression of a few cm under crowd pressure)",
                          r.crowdStats.n, r.crowdStats.p99, pl::CROWD_P99_LIMIT, r.crowdStats.max, pl::CROWD_MAX_LIMIT);
            check(r.crowdOverlapOk(), b);
            if (r.venueOverlapExempt()) {
                std::printf("  NOTE venue-geometry cases (%zu pair-steps, p99 %.4f, max %.4f: falls between treads, step-downs, landings, the bake's "
                            "riser ramps): EXEMPT from the crowd limits, in the %s only. Analytic venues must meet the crowd limits "
                            "for ALL cases, with no exemption.\n", r.venueStats.n, r.venueStats.p99, r.venueStats.max, pl::venueKindName(r.venue));
            } else {
                std::snprintf(b, sizeof b, "hard bodies, every case (%s, no exemption): venue-geometry cases (%zu pair-steps) p99 %.4f <= %.2f and max %.4f "
                              "<= %.2f of BODY_DIAM", pl::venueKindName(r.venue), r.venueStats.n, r.venueStats.p99, pl::CROWD_P99_LIMIT, r.venueStats.max,
                              pl::CROWD_MAX_LIMIT);
                check(r.overlapOk(), b);
            }
            {   // The rule itself (known answer, synthetic statistics): crowd cases within the limits and venue-geometry cases
                // beyond them pass in the baked terrace and fail in an analytic venue; within the limits both pass; crowd cases
                // beyond them fail in both
                pl::Result t;
                t.crowdStats.p99 = 0.01f;
                t.crowdStats.max = 0.05f;
                t.venueStats.p99 = 0.30f;
                t.venueStats.max = 0.50f;
                bool rule = t.overlapOk();                                     // terrace: venue cases exempt
                t.venue = pl::VenueKind::Analytic;
                rule &= !t.overlapOk();                                        // analytic: no exemption
                t.venueStats = t.crowdStats;
                rule &= t.overlapOk();
                t.crowdStats.max = 0.25f;
                rule &= !t.overlapOk();
                t.venue = pl::VenueKind::BakedTerrace;
                rule &= !t.overlapOk();
                check(rule, "overlap rule (known answer): venue-geometry cases beyond the crowd limits pass only in the baked terrace; crowd cases "
                      "beyond them fail in every venue");
            }
            std::snprintf(b, sizeof b, "neighbour grid valid: max displacement %.5f <= %.5f in every step, 0 contact pairs from non-adjacent start cells (%ld)",
                          r.maxDisplacement, pl::displacementBound(), r.gridMisses);
            check(r.gridOk(), b);
            std::snprintf(b, sizeof b, "density ceiling: peak %.2f p/m^2 over fully walkable cells <= %.2f (hexagonal packing %.2f + CIC allowance)",
                          r.peakFull, pl::DENSITY_CEILING_P_M2, pl::HEX_PACKING_P_M2);
            check(r.densityOk(), b);
            check(r.floorOk(), "no agent below a floor: centre in free space and >= floor + BODY_RADIUS - 1e-4 after every step (" +
                  std::to_string(r.centreInSolid) + " in solid, " + std::to_string(r.floorViolations) + " below)");
            check(r.fenceOk(), "no fence crossing, no agent inside the fence collision band (" + std::to_string(r.fenceCrossings) + ", " +
                  std::to_string(r.fenceBand) + " agent-steps)");
            check(r.wallOk(), "wall clearance >= BODY_RADIUS - 3e-4 after every step (walls: n_z <= 0.5, a body diameter tall; tolerance: the curved-corner foot point; " + std::to_string(r.wallViolations) + " agent-steps below)");
            check(r.speedOk(), "no velocity spike: |v_xy| <= V_MAX after every step (max " + std::to_string(r.maxSpeed) + ")");

            // How often the headway rule's mutual-standoff tie-break acts in this evacuation (report only), counted by
            // the predict pass built with DIAG_TIEBREAK (tools/tiebreak.hpp; a shader variant, never in production). The counts
            // describe the production run only if the instrumented shaders compute it bit for bit: checked on every step's state
            namespace tb = swarm::tiebreak;
            const fs::path diag = makeShaderVariant(shaderDir, "tiebreak", tb::DEFINE);
            const tb::Run t = tb::run(diag, sdfTex, spawn, checkpoints.back());
            fs::remove_all(diag);
            uint64_t agentSteps = 0;
            for (int a : t.active) agentSteps += uint64_t(a);
            std::printf("  mutual-standoff tie-break over the evacuation (%d steps, %llu agent-steps; per step: total, max (step), steps with any, "
                        "mean):\n", t.steps, (unsigned long long)agentSteps);
            for (int c = 0; c < tb::COUNTERS; ++c) {
                int at = 0;
                const uint32_t mx = t.maxPerStep(c, &at);
                std::printf("    %-34s %9llu  max %5u (step %4d)  steps %4d  mean %.2f\n", tb::counterName(c), (unsigned long long)t.total(c), mx, at,
                            t.stepsWith(c), double(t.total(c)) / double(std::max(t.steps, 1)));
            }
            check(t.evacStep == r.evacStep && t.trajectoryHash == r.trajectoryHash,
                  "tie-break counters: the instrumented run is the production run bit for bit (every step's state, evacuation at step " +
                  std::to_string(t.evacStep) + ")");
            glErrorFree &= glGetError() == GL_NO_ERROR;
        }
        {   // The free walking speed is V0 = V_MAX by construction. One agent on the open pitch, from rest,
            // driven along +x (no neighbour, no wall in obstacle range): the driving term's exact solution
            // |v| = V_MAX (1 - exp(-k DT / TAU_RELAX)) after k steps, and the speed after 8 TAU_RELAX within 1% of V0.
            GpuBoid a = restingAgent(glm::vec2(-0.25f, 0.0f));
            const std::vector<GpuBoid> all = padInactive({ a });
            const fs::path drive = makeShaderVariant(shaderDir, "free_speed", driveDir(glm::vec2(1.0f, 0.0f)));
            CrowdSim sim(drive, int(all.size()));
            fs::remove_all(drive);
            sim.upload(all);
            const int steps = int(std::ceil(8.0 * TAU_RELAX / DT));
            double maxRelErr = 0.0, speed = 0.0;
            for (int k = 1; k <= steps; ++k) {
                sim.step(sdfTex);
                const GpuBoid s = readBuffer<GpuBoid>(sim.currentStateBuffer(), 1)[0];
                speed = glm::length(glm::vec2(s.velocity));
                const double exact = double(V_MAX) * (1.0 - std::pow(double(RELAX_STEP), k));
                maxRelErr = std::max(maxRelErr, std::abs(speed - exact) / exact);
            }
            const double v0 = units::metresPerSecond(V_MAX), vReal = units::metresPerSecond(speed);
            std::printf("  free walking speed (one agent, open pitch, from rest): %.4f m/s after %d steps (8 TAU_RELAX = %.2f s); V0 %.4f m/s;\n"
                        "  max relative deviation from V0 (1 - exp(-t / TAU_RELAX)) over the steps: %.2e\n", vReal, steps,
                        units::seconds(steps * double(DT)), v0, maxRelErr);
            check(std::abs(vReal - double(V_FREE_M_S)) <= 0.01 * double(V_FREE_M_S) && maxRelErr < 1e-4,
                  "free walking speed: within 1% of V0 = " + std::to_string(V_FREE_M_S) + " m/s after 8 TAU_RELAX (" + std::to_string(vReal) +
                  "), and the exact relaxation from rest (max relative deviation " + std::to_string(maxRelErr) + ")");
        }

        section("physics.step_up_limit: Step-up limit: no move up more than MAX_STEP_UP or up a wall-steep face; the aisles stay climbable");
        if (longTier("the evacuations with and without the step-up limit")) {
            namespace su = swarm::stepup;
            const auto t0 = std::chrono::steady_clock::now();
            const float wallDep = metrics::computeMetricVenue(sdfVolumeCPU()).outerWallInnerDepth;
            std::printf("  MAX_STEP_UP %.4f (%.2f m); a climbed face is wall-steep at n_z <= %.1f; path samples every %.4f (%.1f cm); checker "
                        "resolution %.0e\n", MAX_STEP_UP, double(MAX_STEP_UP_M), WALL_MAX_NZ, STEP_UP_SAMPLE, 100.0 * units::metres(STEP_UP_SAMPLE),
                        double(su::RISE_CHECK_TOL));
            const float platformLevel = (float(su::PLATFORM_ROW) - su::ROW_TOLERANCE) * su::ROW_RISE;

            // (a) The aisles' sub-steps: 0.14 m (4.4 mm model) in the mesh, a walkable slope in the bake (n_z 0.82-0.96). In each of the
            //     8 aisles 4 agents (lateral AISLE_CENTRE, depths 0.47-0.65: above the bake's steep bottom step at dep 0.456-0.461, part
            //     (b)) are driven up the aisle, along their wing's outward axis at V_MAX, for 120 steps, with and without the limit
            //     (DISABLE_STEP_UP_LIMIT): each must reach the platform level at the aisle's top (dep >= 0.79), and the limit must
            //     never act (bit-identical states every step)
            auto driveUpAisles = [&](const float* deps, int count, int steps, int& agents, int& reached, bool& identical, float& maxRise,
                                     float reachDep) {
                agents = reached = 0;
                identical = true;
                maxRise = 0.0f;
                for (const Avenue& av : AVENUES) {
                    std::vector<GpuBoid> boids;
                    for (float side : { -1.0f, 1.0f })
                        for (int k = 0; k < count; ++k) boids.push_back(restingAgent(av.lat * (side * AISLE_CENTRE) + av.out * deps[k]));
                    const std::vector<GpuBoid> all = padInactive(boids);
                    const fs::path on = makeShaderVariant(shaderDir, "aisle_on", driveDir(av.out));
                    const fs::path off = makeShaderVariant(shaderDir, "aisle_off", "#define DISABLE_STEP_UP_LIMIT\n" + driveDir(av.out));
                    CrowdSim simOn(on, int(all.size())), simOff(off, int(all.size()));
                    fs::remove_all(on);
                    fs::remove_all(off);
                    simOn.upload(all);
                    simOff.upload(all);
                    std::vector<float> fPrev(boids.size());
                    std::vector<char> done(boids.size(), 0);
                    for (size_t i = 0; i < boids.size(); ++i) fPrev[i] = su::floorUnder(glm::vec3(boids[i].position));
                    for (int step = 0; step < steps; ++step) {
                        simOn.step(sdfTex);
                        simOff.step(sdfTex);
                        const auto a = readBuffer<GpuBoid>(simOn.currentStateBuffer(), all.size());
                        const auto b = readBuffer<GpuBoid>(simOff.currentStateBuffer(), all.size());
                        identical = identical && std::memcmp(a.data(), b.data(), a.size() * sizeof(GpuBoid)) == 0;
                        for (size_t i = 0; i < boids.size(); ++i) {
                            const glm::vec3 c(a[i].position);
                            const float f = su::floorUnder(c);
                            if (!std::isnan(f) && !std::isnan(fPrev[i])) maxRise = std::max(maxRise, f - fPrev[i]);
                            fPrev[i] = f;
                            done[i] |= glm::dot(glm::vec2(c), av.out) >= reachDep && f >= (reachDep > 0.7f ? platformLevel : 0.0f);
                        }
                    }
                    agents += int(boids.size());
                    for (char d : done) reached += d;
                }
            };
            {
                const float deps[] = { 0.47f, 0.53f, 0.59f, 0.65f };
                int agents = 0, reached = 0;
                bool identical = true;
                float maxRise = 0.0f;
                driveUpAisles(deps, 4, 120, agents, reached, identical, maxRise, 0.79f);
                std::printf("  (a) aisle climb: %d/%d driven agents reached the platform level (floor >= %.4f) at the aisle's top; largest floor rise "
                            "in a step %.3f m; with and without the limit %s\n", reached, agents, platformLevel, units::metres(maxRise),
                            identical ? "bit-identical every step" : "DIFFERENT");
                check(agents == 32 && reached == agents, "the aisles' sub-steps stay climbable: every driven agent (" + std::to_string(reached) + "/" +
                                                             std::to_string(agents) + ") climbs to the platform level at the aisle's top");
                check(identical, "the limit never acts on the aisle climb (states bit-identical with and without it, every step)");
            }
            // (b) Report only: from the walkway into the aisle. The bake has no 0.14 m first sub-step there: the aisle floor rises
            //     0.0055 -> 0.0144 (0.28 m) within 4.5 mm (model) at dep 0.456-0.461, a wall-steep face (n_z ~0.27) that the limit
            //     does not let anyone climb (egress only ever descends it)
            {
                const float deps[] = { 0.43f, 0.44f };
                int agents = 0, reached = 0;
                bool identical = true;
                float maxRise = 0.0f;
                driveUpAisles(deps, 2, 60, agents, reached, identical, maxRise, 0.465f);
                std::printf("  (b) report: from the walkway (dep 0.43-0.44) up the aisle's bottom: %d/%d past the bake's steep bottom step "
                            "(dep >= 0.465) with the limit (without it %s)\n", reached, agents, identical ? "the same states" : "different states");
            }

            // (c) Non-vacuity: N = 16384 from spawn (over the spawn capacity: stacked) for 100 steps WITHOUT the limit
            const int bigN = 16384;
            const std::vector<GpuBoid> bigSpawn = spawnBleacherCrowd(bigN);
            {
                const fs::path off = makeShaderVariant(shaderDir, "stepup_off", "#define DISABLE_STEP_UP_LIMIT\n");
                CrowdSim sim(off, bigN);
                fs::remove_all(off);
                sim.upload(bigSpawn);
                su::RunCheck rc(bigSpawn, wallDep);
                for (int step = 1; step <= 100; ++step) {
                    sim.step(sdfTex);
                    rc.step(step, readBuffer<GpuBoid>(sim.currentStateBuffer(), size_t(bigN)));
                }
                std::printf("  (c) without the limit, N = %d, 100 steps: %ld floor rises above MAX_STEP_UP (largest %.3f m), %ld riser climbs\n", bigN,
                            rc.risesAbove, units::metres(rc.maxRise), rc.climbCount);
                check(rc.risesAbove > 0 && rc.climbCount > 0, "not vacuous: without the limit the same crowd climbs (" + std::to_string(rc.risesAbove) +
                                                                  " rises above MAX_STEP_UP, " + std::to_string(rc.climbCount) + " riser climbs)");
            }

            // (d) The terrace with the limit: N = 4096 (full evacuation), 16384 and 65536 (2000 steps; over the venue's capacity, labelled
            // physically impossible: their overlap statistics are a report)
            for (int n : { NUM_AGENTS, bigN, 65536 }) {
                const std::vector<GpuBoid> sp = n == bigN ? bigSpawn : spawnBleacherCrowd(n);
                CrowdSim sim(shaderDir, n);
                sim.upload(sp);
                su::RunCheck rc(sp, wallDep, n > NUM_AGENTS ? 10 : 0);
                const int maxSteps = n == NUM_AGENTS ? 6000 : 2000;
                int evac = -1, steps = 0;
                for (int step = 1; step <= maxSteps; ++step) {
                    sim.step(sdfTex);
                    const std::vector<GpuBoid> cur = readBuffer<GpuBoid>(sim.currentStateBuffer(), size_t(n));
                    rc.step(step, cur);
                    steps = step;
                    long active = 0;
                    for (const GpuBoid& b : cur) active += b.position.w != 0.0f;
                    if (active == 0) { evac = step; break; }
                }
                std::printf("  (d) N = %d, %d steps%s: floor rises above MAX_STEP_UP %ld (largest %.3f m), riser climbs %ld, agent-steps on wall tops "
                            "%ld, fence crossings %ld; rear platform %ld agent-steps, arrivals up the aisle %ld, from the tread zone %ld; airborne "
                            "%ld agent-steps\n", n, steps, evac > 0 ? (" (evacuated at step " + std::to_string(evac) + ")").c_str() : "", rc.risesAbove,
                            units::metres(rc.maxRise), rc.climbCount, rc.wallTopAgentSteps, rc.fenceCrossings, rc.platformAgentSteps, rc.platformFromAisle,
                            rc.platformFromTread, rc.airborneAgentSteps);
                for (const su::ClimbEvent& e : rc.climbEvents)
                    std::printf("      climb: agent %d row %d -> %d in %d steps\n", e.agent, e.fromRow, e.toRow, e.steps);
                if (rc.overlapSteps > 0)
                    std::printf("      report only (physically impossible density): overlap depth over every 10th step (%d steps, %lld pair-steps): "
                                "p50 %.4f, p99 %.4f, max %.4f of BODY_DIAM\n", rc.overlapSteps, rc.overlapPairs, rc.overlapPercentile(0.50),
                                rc.overlapPercentile(0.99), rc.overlapMax);
                const std::string tag = "N = " + std::to_string(n) + ": ";
                check(rc.risesAbove == 0, tag + "no floor rise above MAX_STEP_UP in a step (" + std::to_string(rc.risesAbove) + ")");
                check(rc.climbCount == 0 && rc.wallTopAgentSteps == 0, tag + "no agent on an unreachable floor: no riser climb, the platform "
                                                                             "behind tread 7 included (" + std::to_string(rc.climbCount) +
                                                                             "), no agent on a wall top (" + std::to_string(rc.wallTopAgentSteps) + ")");
                check(rc.fenceCrossings == 0, tag + "no fence midline crossing (" + std::to_string(rc.fenceCrossings) + ")");
                if (n == NUM_AGENTS) check(evac == fullyEvacuatedAt, tag + "the run evacuates at the step of engine.pipeline_invariants (" + std::to_string(evac) + ")");
            }
            std::printf("  section time %.0f s\n", std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count());
        }

        section("venue.s_distance: Venue S: the analytic distance, exact; GPU against its CPU mirror; the heightfield's floor");
        {
            const Venue& vs = venueS();
            const SeatedLayout& L = vs.layout;
            const std::vector<seated::Primitive> prims = seated::primitives(L);
            // Random points over the venue, 0.5 m below to 1.5 m above the floor (venue_probe exact runs 100k of them)
            std::mt19937 rng(11);
            std::uniform_real_distribution<float> xy(-L.landingEnd, L.landingEnd), dz(float(units::modelLength(-0.5)), float(units::modelLength(1.5)));
            const int np = 20000;
            std::vector<glm::vec3> pts;
            while (int(pts.size()) < np) {
                const glm::vec2 q(xy(rng), xy(rng));
                pts.emplace_back(q, seated::floorHeight(L, q) + dz(rng));
            }
            long signErr = 0, outside = 0;
            double maxOut = 0.0;
            std::vector<glm::vec4> cpu(pts.size());
#pragma omp parallel for schedule(dynamic, 256) reduction(+ : signErr, outside)
            for (int i = 0; i < np; ++i) {
                cpu[size_t(i)] = seated::sdfGrad(L, pts[size_t(i)]);
                const glm::dvec3 pd(pts[size_t(i)]);
                const bool in = seated::bruteForceInside(prims, pd);
                if ((cpu[size_t(i)].w > 0.0f) == in) ++signErr;
                if (in) continue;
                ++outside;
                const double d = std::abs(double(cpu[size_t(i)].w) - seated::bruteForceDistance(prims, pd));
#pragma omp critical
                maxOut = std::max(maxOut, d);
            }
            std::printf("  brute force: %zu solid primitives (unfolded) and the ground; %d random points, %ld outside the solid\n", prims.size(), np, outside);
            check(signErr == 0, "the sign (solid iff z <= the heightfield's floor) agrees with the primitive list at all " + std::to_string(np) +
                  " points (" + std::to_string(signErr) + " disagree)");
            char b[200];
            std::snprintf(b, sizeof b, "outside the solid the CPU mirror equals the brute-force distance to the union: max |diff| %.3g <= 1e-6", maxOut);
            check(maxOut <= 1e-6, b);
            // Eikonal: central differences (h = 1e-4) where the analytic gradient is the same at all six stencil points
            long tested = 0, eikBad = 0;
            double maxEik = 0.0;
            for (int i = 0; i < 4000; ++i) {
                const glm::vec3 p = pts[size_t(i)];
                const glm::vec3 g0(cpu[size_t(i)]);
                const float h = 1e-4f;
                if (std::abs(cpu[size_t(i)].w) <= 2.0f * h) continue;
                glm::vec3 fd(0.0f);
                bool smooth = true;
                for (int ax = 0; ax < 3 && smooth; ++ax) {
                    glm::vec3 e(0.0f);
                    e[ax] = h;
                    const glm::vec4 gp = seated::sdfGrad(L, p + e), gm = seated::sdfGrad(L, p - e);
                    smooth = glm::length(glm::vec3(gp) - g0) <= 1e-3f && glm::length(glm::vec3(gm) - g0) <= 1e-3f;
                    fd[ax] = (gp.w - gm.w) / (2.0f * h);
                }
                if (!smooth) continue;
                ++tested;
                const double dev = std::abs(double(glm::length(fd)) - 1.0);
                maxEik = std::max(maxEik, dev);
                eikBad += dev > 1e-3;
            }
            std::snprintf(b, sizeof b, "Eikonal: | |grad| - 1 | <= 1e-3 by central differences at %ld points away from kinks (max %.2e)", tested, maxEik);
            check(eikBad == 0 && tested > 2000, b);
            // The wall query (clearWalls / wallPlaneProbe on the analytic venue) against the brute force in each point's plane
            {
                const float reach = float(units::modelLength(1.5));
                long wOut = 0, wBad = 0;
                double maxW = 0.0;
                for (int i = 0; i < np; ++i) {
                    if (pts[size_t(i)].z < 0.0f) continue;   // below ground: no body centre is
                    const glm::vec3 w = seated::wall(L, pts[size_t(i)], reach);
                    bool inside = false;
                    const double bw = seated::bruteForceWall(prims, glm::dvec3(pts[size_t(i)]), inside);
                    if (inside != (w.z < 0.0f)) { ++wBad; continue; }
                    if (inside || bw >= double(reach)) continue;
                    ++wOut;
                    maxW = std::max(maxW, std::abs(double(w.z) - bw));
                }
                std::snprintf(b, sizeof b, "wall query: the clearance to the nearest wall in the point's plane equals the brute force within 1e-6 at %ld points "
                              "(max %.3g); inside / outside agrees at all", wOut, maxW);
                check(wBad == 0 && maxW <= 1e-6 && wOut > 1000, b);
            }
            // GPU: physics.comp's map / mapExactGrad / floorUnderReach (@sdf block) on venue S's preamble
            std::ifstream pf(shaderDir / "physics.comp");
            std::stringstream ss;
            ss << pf.rdbuf();
            const std::string phys = ss.str();
            const size_t b0 = phys.find("// @sdf-begin"), b1 = phys.find("// @sdf-end");
            const fs::path tmp = processTempPath("swarm_venue_sdf_probe.comp");
            { std::ofstream(tmp) << "#version 430 core\n" + phys.substr(b0, b1 - b0) +
                  "layout(local_size_x = 64) in;\n"
                  "layout(std430, binding = 5) buffer P { vec4 pts[]; };\n"
                  "layout(std430, binding = 6) buffer R { vec4 outg[]; };\n"
                  "layout(std430, binding = 7) buffer F { vec4 outf[]; };\n"
                  "uniform int count;\n"
                  "void main() { uint i = gl_GlobalInvocationID.x; if (i >= uint(count)) return; vec3 p = pts[i].xyz;\n"
                  "  outg[i] = mapExactGrad(p); float zf; bool ok = floorUnderReach(p, p.z, 1.0, zf);\n"
                  "  outf[i] = vec4(map(p), venueFloor(p.xy), ok ? zf : -1.0, 0.0); }\n"; }
            GLuint prog = loadComputeProgram(tmp, {}, &vs);
            fs::remove(tmp);
            std::vector<glm::vec4> in;
            for (const glm::vec3& p : pts) in.emplace_back(p, 1.0f);
            GLuint bin = makeBuffer(in), bg = makeBuffer(std::vector<glm::vec4>(in.size())), bf = makeBuffer(std::vector<glm::vec4>(in.size()));
            glUseProgram(prog);
            glUniform1i(glGetUniformLocation(prog, "count"), np);
            glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, bin);
            glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, bg);
            glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 7, bf);
            glDispatchCompute(GLuint((np + 63) / 64), 1, 1);
            const std::vector<glm::vec4> gg = readBuffer<glm::vec4>(bg, in.size()), gfl = readBuffer<glm::vec4>(bf, in.size());
            glDeleteBuffers(1, &bin);
            glDeleteBuffers(1, &bg);
            glDeleteBuffers(1, &bf);
            glDeleteProgram(prog);
            double maxVal = 0.0;
            long floorDiff = 0, reachDiff = 0;
            for (int i = 0; i < np; ++i) {
                maxVal = std::max(maxVal, double(std::abs(gg[size_t(i)].w - cpu[size_t(i)].w)));
                maxVal = std::max(maxVal, double(std::abs(gfl[size_t(i)].x - cpu[size_t(i)].w)));
                const float hc = seated::floorHeight(L, glm::vec2(pts[size_t(i)]));
                floorDiff += gfl[size_t(i)].y != hc;
                const glm::vec3 c = pts[size_t(i)];
                reachDiff += gfl[size_t(i)].z != ((c.z > hc || hc <= c.z + BODY_RADIUS) ? hc : -1.0f);
            }
            std::snprintf(b, sizeof b, "GPU map() and mapExactGrad() on venue S's preamble equal the CPU mirror to %.2g (<= 1e-6, rounding level)", maxVal);
            check(maxVal <= 1e-6, b);
            check(floorDiff == 0 && reachDiff == 0, "GPU venueFloor bit-identical to the CPU floor height at all " + std::to_string(np) +
                  " points; floorUnderReach finds it within its reach (" + std::to_string(floorDiff) + " / " + std::to_string(reachDiff) + " differ)");
        }

        section("venue.s_mesh: Venue S: the render mesh venue_s.obj (generated from the same parameters)");
        {
            const SeatedLayout& L = venueS().layout;
            // The asset is the generator's output (venue_probe obj): equal to seated::meshOBJ apart from comment lines and
            // carriage returns (git may check the file out with CRLF)
            auto content = [](const std::string& text) {
                std::string out;
                std::istringstream in(text);
                for (std::string line; std::getline(in, line);) {
                    if (!line.empty() && line.back() == '\r') line.pop_back();
                    if (!line.empty() && line[0] != '#') out += line + "\n";
                }
                return out;
            };
            std::ifstream f(resolveAsset(venueS().objAsset), std::ios::binary);
            std::stringstream fs_;
            fs_ << f.rdbuf();
            const bool same = content(fs_.str()) == content(seated::meshOBJ(L, ""));
            check(same, std::string(venueS().objAsset) + " equals the mesh generated from venue S's layout (seated::meshOBJ)");
            // Every triangle faces out of the solid (counter-clockwise from outside): just outside along its normal is free,
            // just inside is solid, for the venue or, for the fence's faces, its visual box
            const std::vector<float> mesh = seated::mesh(L);
            const glm::vec2 mid(FENCE_HALF_MID.x, FENCE_HALF_MID.y);
            auto fenceBox = [&](glm::vec3 q) {
                return std::max(std::abs(sdBox2(glm::vec2(q), mid)) - FENCE_HALF_THK_VISUAL, std::max(-q.z, q.z - 0.025802f));
            };
            long tris = long(mesh.size() / 18), bad = 0, fenceTris = 0, up = 0;
            const float eps = 1e-4f;
            for (long t = 0; t < tris; ++t) {
                const float* v = &mesh[size_t(t) * 18];
                const glm::vec3 a(v[0], v[1], v[2]), b2(v[6], v[7], v[8]), c(v[12], v[13], v[14]), nrm(v[3], v[4], v[5]);
                const glm::vec3 ctr = (a + b2 + c) / 3.0f;
                const bool venueOk = seated::sdf(L, ctr + nrm * eps) > 0.0f && seated::sdf(L, ctr - nrm * eps) <= 0.0f;
                const bool fenceOk = fenceBox(ctr + nrm * eps) > 0.0f && fenceBox(ctr - nrm * eps) < 0.0f;
                if (!venueOk && fenceOk) ++fenceTris;
                if ((!venueOk && !fenceOk) || glm::dot(glm::cross(b2 - a, c - a), nrm) <= 0.0f) ++bad;
                up += nrm.z > 0.5f;
            }
            std::printf("  %ld triangles (%ld floor-like, n_z > 0.5; %ld the fence's)\n", tris, up, fenceTris);
            check(tris > 1000 && bad == 0, "every triangle's normal points out of the solid and its winding is counter-clockwise from outside (" +
                  std::to_string(bad) + " of " + std::to_string(tris) + " not)");
        }

        section("venue.s_spawn_capacity: Venue S: seat spawn (one agent per seat) and capacity");
        {
            const Venue& vs = venueS();
            const SeatedLayout& L = vs.layout;
            const scene::Select sel(vs);
            const std::vector<seated::Seat> seats = seated::seats(L);
            const std::vector<seated::RowSeats> perRow = seated::seatsPerRow(L);
            long total = 0;
            bool limits = true;
            std::printf("  seats per wing (8 wings) by row, dead-end + between the gangways:");
            for (int k = 0; k < L.rows; ++k) {
                total += 8L * (perRow[size_t(k)].deadEnd + perRow[size_t(k)].between);
                limits = limits && perRow[size_t(k)].deadEnd <= vs.params.maxSeatsDeadEnd && perRow[size_t(k)].between <= vs.params.maxSeatsBetweenGangways &&
                         perRow[size_t(k)].between >= 1;
                std::printf("%s %d+%d", k % 6 == 0 ? "\n   " : "", perRow[size_t(k)].deadEnd, perRow[size_t(k)].between);
            }
            std::printf("\n");
            check(long(seats.size()) == total && total == 3728, "venue S has " + std::to_string(total) + " seats (17 rows; pinned: 3728), and lists them all");
            check(limits, "every row segment within the seat limits: dead-end <= 14, between gangways 1 .. 28");
            // The full spawn
            int active = 0;
            const std::vector<GpuBoid> boids = spawnSeatedCrowd(vs, 4096, 1.0, 1337, &active);
            long parkedOk = 0;
            for (size_t i = size_t(active); i < boids.size(); ++i) parkedOk += boids[i].position.w == 0.0f && boids[i].position.x == PARK_COORD;
            check(active == int(seats.size()) && parkedOk == long(boids.size()) - active,
                  "100% load: " + std::to_string(active) + " agents, one per seat in seat order, the other " + std::to_string(boids.size() - size_t(active)) + " parked");
            long wrongFloor = 0, wrongZ = 0, notFree = 0, wallBad = 0;
            float minWall = 1e9f;
#pragma omp parallel for schedule(dynamic, 64) reduction(+ : wrongFloor, wrongZ, notFree, wallBad)
            for (int i = 0; i < active; ++i) {
                const glm::vec3 c(boids[size_t(i)].position);
                int row = -1;
                const int kind = seated::cellAt(L, glm::vec2(c), &row);
                if (kind != seated::TREAD || row != seats[size_t(i)].row) ++wrongFloor;
                if (c.z != L.firstRow + float(row) * L.rowRise + BODY_RADIUS) ++wrongZ;   // the rest height above its own tread, exactly
                if (seated::sdf(L, c) <= 0.0f) ++notFree;
                // Horizontal clearance in the centre's plane: 64 rays, sphere-traced on the exact distance (the floor lies
                // BODY_RADIUS below the plane, so a ray ends on a wall), up to 0.5 m
                float w = float(units::modelLength(0.5));
                for (int k = 0; k < 64; ++k) {
                    const float ang = 6.28318530718f * float(k) / 64.0f;
                    const glm::vec3 u(std::cos(ang), std::sin(ang), 0.0f);
                    float t = 0.0f;
                    for (int it = 0; it < 200 && t < w; ++it) {
                        const float d = seated::sdf(L, c + u * t);
                        if (d < 1e-7f) break;
                        t += d;
                    }
                    w = std::min(w, t);
                }
                if (w < BODY_RADIUS - plausibility::WALL_TOL) ++wallBad;
#pragma omp critical
                minWall = std::min(minWall, w);
            }
            check(wrongFloor == 0 && wrongZ == 0 && notFree == 0, "every seated agent stands on its own row's clearway, at the rest height above it, in free space (" +
                  std::to_string(wrongFloor) + " / " + std::to_string(wrongZ) + " / " + std::to_string(notFree) + " not)");
            char b[200];
            std::snprintf(b, sizeof b, "wall clearance >= BODY_RADIUS for every seated agent (min %.4f m, body radius 0.20 m: the clearway's walls; %ld below)",
                          units::metres(minWall), wallBad);
            check(wallBad == 0, b);
            // Exact seat spacing within each segment (the seat pitch), and no overlap anywhere at t = 0
            double maxDev = 0.0;
            for (size_t i = 1; i < seats.size(); ++i) {
                const seated::Seat& a = seats[i - 1];
                const seated::Seat& c = seats[i];
                if (a.quadrant != c.quadrant || a.wing != c.wing || a.row != c.row || a.segment != c.segment) continue;
                maxDev = std::max(maxDev, std::abs(double(c.lat - a.lat) - double(L.seatWidth)));
            }
            std::vector<float> depth;
            const OverlapScan ov = scanOverlaps(boids, &depth);
            std::snprintf(b, sizeof b, "seat pitch exact: neighbouring seats %.4f m apart within %.1e m; no two bodies overlap at t = 0 (%ld pairs closer than BODY_DIAM)",
                          units::metres(L.seatWidth), units::metres(maxDev), ov.pairs);
            check(maxDev <= 1e-6 && ov.pairs == 0, b);
            // A load below 100%: a seeded subset, the same for the same seed
            int a50 = 0, a50b = 0, a0 = 0;
            const std::vector<GpuBoid> h1 = spawnSeatedCrowd(vs, 4096, 0.5, 7, &a50), h2 = spawnSeatedCrowd(vs, 4096, 0.5, 7, &a50b), none = spawnSeatedCrowd(vs, 4096, 0.0, 7, &a0);
            const std::vector<int> pick = seatedSpawnSeats(vs, 4096, 0.5, 7);
            bool onSeats = true, ascending = true;
            for (int i = 0; i < a50; ++i) {
                onSeats = onSeats && pick[size_t(i)] >= 0 && glm::vec3(h1[size_t(i)].position) == seats[size_t(pick[size_t(i)])].pos;
                if (i > 0) ascending = ascending && pick[size_t(i)] > pick[size_t(i - 1)];
            }
            check(a50 == int(std::lround(0.5 * double(seats.size()))) && a50b == a50 && std::memcmp(h1.data(), h2.data(), h1.size() * sizeof(GpuBoid)) == 0 &&
                  onSeats && ascending && a0 == 0,
                  "load 50%: " + std::to_string(a50) + " agents on distinct seats in seat order, the same for the same seed; load 0: none");
            // Capacity metadata: design = the seat count, jam = the occupiable floor at hexagonal packing; the
            // metric grid's walkable floor of S agrees with the exact areas
            const venue::Capacity cap = venue::capacityOf(vs);
            const seated::Areas A = seated::areas(L);
            const metrics::MetricVenue mv = metrics::computeMetricVenueSeated(L);
            double walkable = 0.0, pitch = 0.0;
            for (int c = 0; c < metrics::CELLS; ++c) {
                walkable += mv.walkableM2[size_t(c)];
                if (mv.zone[size_t(c)] == metrics::ZONE_PITCH) pitch += mv.walkableM2[size_t(c)];
            }
            std::printf("  capacity: design %d, occupiable %.1f m^2 (exact), jam %d; metric grid: walkable %.1f m^2 (exact occupiable + pitch %.1f)\n",
                        cap.design, cap.occupiableM2, cap.jam, walkable, A.occupiable() + A.pitch);
            check(cap.design == int(seats.size()) && cap.jam == int(std::lround(A.occupiable() * venue::HEX_PACKING_P_M2)) && cap.jam == 18138 &&
                  venue::label(cap.design, cap) == "within design capacity" && venue::load(cap.design + 1, cap) == venue::Load::AboveDesign,
                  "capacity: design = the seat count (3728), jam = round(2513.3 m^2 x 7.2169) = 18138 (pinned), labels as for the terrace");
            check(std::abs(walkable - (A.occupiable() + A.pitch)) <= 0.005 * (A.occupiable() + A.pitch),
                  "the metric grid's walkable floor of S (2.5 cm samples) within 0.5% of the exact occupiable floor + pitch");
        }

        // Venue S forced motion (tools/venue_s.hpp): the router bypassed by the TEST_DRIVE_TABLE variant
        const fs::path driveDir = venue_s::driveVariant(shaderDir, "test_gpu_drive");
        std::vector<const venue_s::Checker*> sChecks;   // (f) over every scenario
        auto checkerSummary = [](const venue_s::Checker& c) {
            char b[400];
            std::snprintf(b, sizeof b, "    %ld agent-steps: row changes %ld, in a solid column %ld, tunnelling %ld, wall clearance below BODY_RADIUS %ld (min %s), "
                          "fence crossings %ld, rises > MAX_STEP_UP %ld, vertical-face climbs %ld (faces crossed in a net descent %ld)\n",
                          c.agentSteps, c.rowChanges, c.solidSteps, c.tunnels, c.wallViolations,
                          c.minWallClearance < 1e8f ? (std::to_string(units::metres(c.minWallClearance)).substr(0, 6) + " m").c_str() : "none within 0.197 m",
                          c.fenceCrossings, c.risesAbove, c.verticalClimbs, c.descentFaces);
            std::printf("%s", b);
        };
        auto structural = [](const venue_s::Checker& c) {   // the checks every scenario must pass
            return c.rowChanges == 0 && c.solidSteps == 0 && c.tunnels == 0 && c.wallViolations == 0 && c.fenceCrossings == 0;
        };
        const scene::Select sceneS(venueS());
        const SeatedLayout& LS = venueS().layout;

        section("venue.s_forced_inv_row: Venue S: INV-row, every seat occupied, driven towards / away from the pitch at V0 for 300 steps");
        static venue_s::InvRow invRow;   // the checkers outlive their sections: (f) sums them in venue.s_forced_dense
        {
            const auto t0 = std::chrono::steady_clock::now();
            invRow = venue_s::runInvRow(driveDir, venueS(), 300);
            const venue_s::InvRow& r = invRow;
            for (int k = 0; k < 2; ++k) {
                const venue_s::RunResult& rr = k == 0 ? r.runToward : r.runAway;
                const std::string what = k == 0 ? "towards the pitch" : "away from the pitch";
                checkerSummary(rr.checks);
                check(rr.checks.offRowSteps == 0 && rr.checks.rowChanges == 0, what + ": every agent stays on its own row's clearway in every step (row changes " +
                      std::to_string(rr.checks.rowChanges) + ", agent-steps off it " + std::to_string(rr.checks.offRowSteps) + ")");
                check(structural(rr.checks), what + ": no seat-block / barrier / wall crossing or tunnelling, wall clearance >= BODY_RADIUS, no fence crossing");
                check(rr.checks.frontRowOnWalkway == 0, what + ": no front-row agent reaches the walkway (the barrier; only the gangway feet lead there)");
                sChecks.push_back(&rr.checks);
            }
            std::printf("  section time %.0f s\n", std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count());
        }

        section("venue.s_forced_junctions: Venue S: junctions, every row: one segment's agents driven along the row towards an adjacent gangway");
        static std::vector<venue_s::Junction> junctions;
        {
            const auto t0 = std::chrono::steady_clock::now();
            junctions = venue_s::runJunctions(driveDir, venueS(), 2400);
            for (const venue_s::Junction& j : junctions) {
                int agents = 0, entered = 0, rowsAll = 0;
                std::vector<int> st;
                for (const venue_s::GroupStats& g : j.perRow) {
                    agents += g.agents;
                    entered += g.arrived;
                    rowsAll += g.agents > 0 && g.arrived == g.agents;
                    st.insert(st.end(), g.steps.begin(), g.steps.end());
                }
                std::sort(st.begin(), st.end());
                std::printf("  %-38s %4d agents, entered %4d, rows complete %2d of %d; entry median %.1f s, last %.1f s\n", j.name, agents, entered, rowsAll,
                            LS.rows, st.empty() ? 0.0 : venue_s::seconds(st[st.size() / 2]), st.empty() ? 0.0 : venue_s::seconds(st.back()));
                checkerSummary(j.run.checks);
                check(entered == agents && rowsAll == LS.rows, std::string(j.name) + ": all " + std::to_string(agents) + " agents of all 17 rows enter the gangway (" +
                      std::to_string(agents - entered) + " stuck)");
                check(structural(j.run.checks), std::string(j.name) + ": no row change, crossing or tunnelling; wall clearance; no fence crossing");
                sChecks.push_back(&j.run.checks);
            }
            std::printf("  section time %.0f s\n", std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count());
        }

        section("venue.s_forced_gangways: Venue S: every gangway, 17 agents driven down to the walkway and up to the rear concourse");
        static venue_s::Gangways gangways;
        {
            const auto t0 = std::chrono::steady_clock::now();
            gangways = venue_s::runGangways(driveDir, venueS(), 1200);
            for (int d = 0; d < 2; ++d) {
                const std::vector<venue_s::GroupStats>& st = d == 0 ? gangways.statsDown : gangways.statsUp;
                int agents = 0, arrived = 0, last = 0, complete = 0;
                for (const venue_s::GroupStats& g : st) { agents += g.agents; arrived += g.arrived; last = std::max(last, g.lastStep); complete += g.arrived == g.agents; }
                const std::string what = d == 0 ? "down to the walkway" : "up to the rear concourse";
                std::printf("  %s: %d of %d agents arrived, %d of 12 gangways complete, the last at %.1f s\n", what.c_str(), arrived, agents, complete, venue_s::seconds(last));
                checkerSummary(d == 0 ? gangways.runDown.checks : gangways.runUp.checks);
                check(arrived == agents && complete == 12, what + ": 100% traverse all 12 gangways (8 straight, 4 corner)");
                check(structural(d == 0 ? gangways.runDown.checks : gangways.runUp.checks), what + ": no crossing, tunnelling, wall or fence violation");
                sChecks.push_back(d == 0 ? &gangways.runDown.checks : &gangways.runUp.checks);
            }
            std::printf("  section time %.0f s\n", std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count());
        }

        section("venue.s_forced_circulation: Venue S: walkway and rear concourse rings, the four avenues and the eight concourse exits");
        static venue_s::Passages passages;
        {
            const auto t0 = std::chrono::steady_clock::now();
            passages = venue_s::runPassages(driveDir, venueS(), 1500);
            const char* names[] = { "walkway rings", "concourse rings", "avenues out through their exits", "concourse exits" };
            const int from[] = { 0, 4, 8, 12 }, to[] = { 4, 8, 12, 20 };
            for (int k = 0; k < 4; ++k) {
                const std::vector<venue_s::GroupStats>& st = k < 2 ? passages.statsRings : passages.statsExits;
                int agents = 0, arrived = 0, last = 0;
                for (int g = from[k]; g < to[k]; ++g) { agents += st[size_t(g)].agents; arrived += st[size_t(g)].arrived; last = std::max(last, st[size_t(g)].lastStep); }
                std::printf("  %-32s %d of %d arrived, the last at %.1f s\n", names[k], arrived, agents, venue_s::seconds(last));
                check(agents > 0 && arrived == agents, std::string(names[k]) + ": every agent arrives");
            }
            checkerSummary(passages.runRings.checks);
            checkerSummary(passages.runExits.checks);
            check(structural(passages.runRings.checks) && structural(passages.runExits.checks), "no fence crossing, crossing, tunnelling or wall violation");
            sChecks.push_back(&passages.runRings.checks);
            sChecks.push_back(&passages.runExits.checks);
            std::printf("  section time %.0f s\n", std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count());
        }

        section("venue.s_forced_dense: Venue S: dense forced scenario, every seat occupied, along the row, down the gangway, out; plausibility with NO exemption; the step-up rules");
        static venue_s::Dense dense;
        if (longTier("the dense forced scenario to the last agent out, with plausibility after every step")) {
            const auto t0 = std::chrono::steady_clock::now();
            dense = venue_s::runDense(driveDir, shaderDir, venueS(), 6000, golden::GOLDEN_STEPS);
            plausibility::print(dense.plaus);
            plausibility::printOverlapCases(dense.plaus);
            checkerSummary(dense.checks);
            const plausibility::Result& r = dense.plaus;
            check(r.venue == plausibility::VenueKind::Analytic && !r.venueOverlapExempt(), "venue S is held to the crowd limits for ALL overlap cases (analytic venue)");
            char b[300];
            std::snprintf(b, sizeof b, "overlap depth over ALL %zu pair-steps: p99 %.4f <= 0.05 and max %.4f <= 0.20 of BODY_DIAM (crowd %zu: p99 %.4f max %.4f; venue-geometry %zu: p99 %.4f max %.4f)",
                          r.allStats.n, r.allStats.p99, r.allStats.max, r.crowdStats.n, r.crowdStats.p99, r.crowdStats.max, r.venueStats.n, r.venueStats.p99, r.venueStats.max);
            check(r.overlapOk() && plausibility::Result::withinCrowdLimits(r.allStats), b);
            check(r.evacStep > 0 && !r.nan, "everyone leaves along the forced route (step " + std::to_string(r.evacStep) + ", " +
                  std::to_string(venue_s::seconds(r.evacStep)).substr(0, 6) + " s), no NaN");
            check(r.gridOk() && r.floorOk() && r.fenceOk() && r.wallOk() && r.speedOk() && r.densityOk(),
                  "plausibility: neighbour grid, floors, fence, walls, speed, density ceiling");
            check(structural(dense.checks), "no row change, seat-block crossing or tunnelling (" + std::to_string(dense.checks.rowChanges) + ", " +
                  std::to_string(dense.checks.tunnels) + ")");
            sChecks.push_back(&dense.checks);
            std::printf("  section time %.0f s\n", std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count());
        }
        {   // (f) over the scenarios that ran (36-39, and 40 in the long tier)
            long rises = 0, climbs = 0, dips = 0, steps = 0;
            for (const venue_s::Checker* c : sChecks) { rises += c->risesAbove; climbs += c->verticalClimbs; dips += c->descentFaces; steps += c->agentSteps; }
            std::printf("  (f) over the forced scenarios (%ld agent-steps): rises above MAX_STEP_UP %ld, climbs over a vertical face %ld, faces crossed in a net descent %ld (information)\n",
                        steps, rises, climbs, dips);
            check(rises == 0 && climbs == 0, "(f) the step-up rules hold on S in every scenario: 0 rises above MAX_STEP_UP, 0 climbs over a vertical face (any height, onto a floor above the start-of-step floor)");
        }

        section("parity.s_forced: Venue S: CPU/GPU equivalence on S (the dense scenario's drive field) and its golden hashes");
        {
            const auto t0 = std::chrono::steady_clock::now();
            const venue_s::Setup su = venue_s::denseSetup(LS);
            const int nS = int(su.boids.size());
            std::vector<GpuBoid> mid;
            {
                venue_s::GpuEngine e(driveDir, nS, venueS());
                mid = venue_s::run(e, LS, su.boids, su.plans, su.rows, 200, false, false).finalState;
            }
            const venue_s::OneStep o = venue_s::oneStep(driveDir, venueS(), mid, su.plans);
            long active = 0;
            for (const GpuBoid& b : mid) active += b.position.w != 0.0f;
            for (int m = 0; m < 2; ++m) {
                const bool cellsSame = std::memcmp(o.cpuCells[m].data(), o.gpuCells.data(), o.gpuCells.size() * sizeof(GpuCellData)) == 0;
                long seqDiff = 0, pairDiff = 0, out = 0;
                for (size_t i = 0; i < o.gpuGrid.size(); ++i) { seqDiff += o.cpuGrid[m][i].gridID != o.gpuGrid[i].gridID; pairDiff += o.cpuGrid[m][i].boidID != o.gpuGrid[i].boidID; }
                for (size_t i = 0; i < mid.size(); ++i)
                    if (mid[i].position.w != 0.0f) out += glm::length(glm::vec3(o.cpu[m][i].position) - glm::vec3(o.gpu[i].position)) > 2e-4f;
                const std::string mode = m == 0 ? "counting" : "bitonic";
                check(cellsSame && seqDiff == 0 && (m == 0 || pairDiff == 0), "grid exact (" + mode + "): cell table and gridID sequence identical" +
                      (m == 1 ? ", (gridID, boidID) pairs identical" : std::string(" (boidID order within a cell differs by design)")));
                check(double(out) < 0.005 * double(active), "one step from the GPU state after 200 steps (" + std::to_string(active) + " active), CPU " + mode +
                      ": |dpos| > 2e-4 for " + std::to_string(out) + " agents (< 0.5%)");
            }
            auto cpuRun = [&](int threads, CpuCrowdSim::SortMode mode, int steps, bool stop) {
                venue_s::CpuEngine c(venueS(), threads, mode);
                return venue_s::run(c, LS, su.boids, su.plans, su.rows, steps, stop, false);
            };
            if (longTier("CPU thread invariance on S (1 thread, 100 steps)")) {
                const venue_s::RunResult t1 = cpuRun(1, CpuCrowdSim::SortMode::Counting, 100, false), tmax = cpuRun(0, CpuCrowdSim::SortMode::Counting, 100, false);
                check(t1.trajectoryHash == tmax.trajectoryHash, "CPU thread invariance: 1 thread and " + std::to_string(CpuCrowdSim::maxThreads()) +
                      " threads compute the same 100 steps bit for bit");
            }
            venue_s::RunResult g2;
            {
                venue_s::GpuEngine e(driveDir, nS, venueS());
                g2 = venue_s::run(e, LS, su.boids, su.plans, su.rows, golden::GOLDEN_STEPS, false, false);
            }
            const venue_s::RunResult c1 = cpuRun(0, CpuCrowdSim::SortMode::Counting, golden::GOLDEN_STEPS, false),
                                     cb = cpuRun(0, CpuCrowdSim::SortMode::GpuBitonic, golden::GOLDEN_STEPS, false);
            const uint64_t hg = golden::stateHash(g2.finalState), hc = golden::stateHash(c1.finalState), hb = golden::stateHash(cb.finalState);
            if (longTier("the determinism runs on S (a second CPU run; venue.s_forced_dense's GPU run)")) {
                const venue_s::RunResult c2 = cpuRun(0, CpuCrowdSim::SortMode::Counting, golden::GOLDEN_STEPS, false);
                check(hg == dense.goldenHash && c1.trajectoryHash == c2.trajectoryHash, "determinism: the GPU state after " + std::to_string(golden::GOLDEN_STEPS) +
                      " steps equals venue.s_forced_dense's run; two CPU runs identical step for step");
            }
            long act[3] = {};
            for (const GpuBoid& b : g2.finalState) act[0] += b.position.w != 0.0f;
            for (const GpuBoid& b : c1.finalState) act[1] += b.position.w != 0.0f;
            for (const GpuBoid& b : cb.finalState) act[2] += b.position.w != 0.0f;
            std::printf("  golden S (state after %d steps of the dense scenario; active %ld / %ld / %ld): GPU %016llx, CPU counting %016llx, CPU bitonic %016llx\n",
                        golden::GOLDEN_STEPS, act[0], act[1], act[2], (unsigned long long)hg, (unsigned long long)hc, (unsigned long long)hb);
            const std::string driverNow = std::string((const char*)glGetString(GL_RENDERER)) + " | " + (const char*)glGetString(GL_VERSION);
            const uint64_t pins[3] = { golden::GOLDEN_S_FORCED[0].hash, golden::GOLDEN_S_FORCED[1].hash, golden::GOLDEN_S_FORCED[2].hash };
            if (driverNow == golden::GOLDEN_DRIVER) check(hg == pins[0], std::string("GPU venue S: matches the pinned golden hash ") + golden::GOLDEN_S_FORCED[0].name);
            else std::printf("  [WARN] driver differs from the golden pin's; GPU venue S not compared\n");
            check(hc == pins[1] && hb == pins[2], "CPU venue S (counting, bitonic): match the pinned golden hashes");
            check(act[0] > 0 && act[1] > 0 && act[2] > 0, "the golden states still have active agents");
            if (longTier("the full CPU run of the dense scenario (Debug: the CPU steps ~16x slower)")) {
                const venue_s::RunResult cfull = cpuRun(0, CpuCrowdSim::SortMode::Counting, 6000, true);
                const double rel = (double(cfull.evacStep) - double(dense.plaus.evacStep)) / double(std::max(dense.plaus.evacStep, 1));
                check(cfull.evacStep > 0 && std::abs(rel) <= 0.05, "the dense scenario to the last agent out: CPU counting step " + std::to_string(cfull.evacStep) +
                      " vs GPU " + std::to_string(dense.plaus.evacStep) + " (" + std::to_string(100.0 * rel).substr(0, 6) + "%, within +-5%)");
            }
            std::printf("  section time %.0f s\n", std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count());
        }

        section("nav.field: Navigation field: venue S's traversability grid and distance field, the cache, GPU navDirection / navGoal = CPU");
        {
            const Venue& vs = venueS();
            const nav::Field& f = nav::forVenue(vs);
            const size_t cells = f.grid.cells();
            long fit = 0, reach = 0, oneWay = 0;
            for (size_t i = 0; i < cells; ++i) {
                fit += f.cls[i] == nav::FIT;
                reach += f.reachable(i);
                const int x = int(i) % f.grid.res, y = int(i) / f.grid.res;
                for (int k = 0; k < 4; ++k) {   // each neighbour pair once
                    const int nx = x + nav::DIR_X[k], ny = y + nav::DIR_Y[k];
                    if (nx < 0 || ny < 0 || nx >= f.grid.res || ny >= f.grid.res) continue;
                    const size_t j = size_t(f.grid.index(nx, ny));
                    oneWay += (((f.out[i] >> k) & 1u) != 0) != (((f.out[j] >> nav::opposite(k)) & 1u) != 0);
                }
            }
            std::printf("  grid %d x %d of %.3f m (%.7g model units); FIT %ld, reachable %ld; one-way neighbour pairs %ld; %s in %.2f s; key %016llx, "
                        "content %016llx\n", f.grid.res, f.grid.res, nav::CELL_M, double(f.grid.cell), fit, reach, oneWay,
                        f.fromCache ? "loaded from the cache" : "built", f.buildSeconds, (unsigned long long)f.key, (unsigned long long)nav::contentHash(f));
            check(std::abs(double(f.grid.cell) * units::M_PER_UNIT - nav::CELL_M) < 1e-6 && nav::CELL_M <= 0.10, "cell size 0.05 m (at most 0.10 m)");
            check(oneWay > 0, "the graph is directed: " + std::to_string(oneWay) + " neighbour pairs are legal one way only (a clearway steps down onto the "
                  "incline beside it, never up from it)");
            check(f.key == nav::cacheKey(vs) && nav::cacheFile(vs).filename().string().find("nav_S_") == 0, "the field is keyed by the hash of the venue's parameters");
            {
                nav::Field loaded;
                checkCacheFile("the field's cache file", nav::cacheFile(vs), [&](const fs::path& p) { return nav::load(loaded, p, f.key); },
                               [&](const fs::path& p) { return nav::save(loaded, p); });
                check(nav::load(loaded, nav::cacheFile(vs), f.key) && nav::contentHash(loaded) == nav::contentHash(f) && !nav::load(loaded, nav::cacheFile(vs), f.key ^ 1),
                      "the field read from its file = the field in memory; another key refuses it");
            }
            if (longTier("a fresh build of the field compared with the cached one")) {
                const nav::Field fresh = nav::build(nav::SeatedGeometry(vs.layout), nav::venueGrid(vs));
                std::printf("  fresh build: %.2f s (grid %.2f s, search %.2f s; line-of-sight checks %lld, fallbacks %lld)\n", fresh.buildSeconds,
                            fresh.buildSeconds - fresh.searchSeconds, fresh.searchSeconds, fresh.losChecks, fresh.losFallbacks);
                check(nav::contentHash(fresh) == nav::contentHash(f), "the cached field equals a fresh build bit for bit");
            }
            // GPU navDirection (physics.comp @nav block, venue S's preamble, the field's SSBO) against nav::direction at random points
            std::ifstream pf(shaderDir / "physics.comp");
            std::stringstream ss;
            ss << pf.rdbuf();
            const std::string phys = ss.str();
            const size_t b0 = phys.find("// @nav-begin"), b1 = phys.find("// @nav-end");
            check(b0 != std::string::npos && b1 != std::string::npos, "physics.comp has the @nav block");
            const fs::path tmp = processTempPath("swarm_nav_probe.comp");
            { std::ofstream(tmp) << "#version 430 core\n" + phys.substr(b0, b1 - b0) +
                  "layout(local_size_x = 64) in;\n"
                  "layout(std430, binding = 5) buffer P { vec4 pts[]; };\n"
                  "layout(std430, binding = 6) buffer R { vec4 outd[]; };\n"
                  "layout(std430, binding = 7) buffer G { vec2 outg[]; };\n"
                  "uniform int count;\n"
                  "void main() { uint i = gl_GlobalInvocationID.x; if (i >= uint(count)) return;\n"
                  "  int c = navCell(pts[i].xy);\n"
                  "  outd[i] = vec4(navDirection(pts[i].xy), float(c % NAV_RES), float(c / NAV_RES)); outg[i] = navGoal(pts[i].xyz); }\n"; }
            GLuint prog = loadComputeProgram(tmp, {}, &vs);
            fs::remove(tmp);
            std::mt19937 rng(23);
            std::uniform_real_distribution<float> u(vs.domainMin, vs.domainMax());
            const int np = 50000;
            std::vector<glm::vec4> pts;   // at the rest height above the floor
            for (int i = 0; i < np; ++i) {
                const glm::vec2 q(u(rng), u(rng));
                pts.emplace_back(q, seated::floorHeight(vs.layout, q) + BODY_RADIUS, 1.0f);
            }
            for (const seated::Seat& s : seated::seats(vs.layout)) pts.emplace_back(s.pos, 1.0f);   // and every seat
            const std::vector<GpuNavCell> table = nav::gpuCells(f);
            GLuint bp = makeBuffer(pts), bo = makeBuffer(std::vector<glm::vec4>(pts.size())), bg = makeBuffer(std::vector<glm::vec2>(pts.size())),
                   bn = makeBuffer(table);
            glUseProgram(prog);
            glUniform1i(glGetUniformLocation(prog, "count"), GLint(pts.size()));
            glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, bp);
            glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, bo);
            glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 7, bg);
            glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_NAV, bn);
            glDispatchCompute(GLuint((pts.size() + 63) / 64), 1, 1);
            const std::vector<glm::vec4> gd = readBuffer<glm::vec4>(bo, pts.size());
            const std::vector<glm::vec2> gg = readBuffer<glm::vec2>(bg, pts.size());
            for (GLuint b : { bp, bo, bg, bn }) glDeleteBuffers(1, &b);
            glDeleteProgram(prog);
            long cellDiff = 0, zeroDiff = 0, bitDiff = 0, closeToWall = 0, viaFit = 0;
            double maxDiff = 0.0, gMaxClose = 0.0;
            nav_goal_check::Agreement agr;   // the criterion of tools/nav_goal_check.hpp
            for (size_t i = 0; i < pts.size(); ++i) {
                const glm::vec2 xy(pts[i]);
                const int c = nav::directionCell(f, xy);   // the containing cell, or for a NOFIT one its nearest FIT neighbour
                const glm::ivec2 own = f.grid.cellOf(xy);
                viaFit += c != f.grid.index(own.x, own.y);
                cellDiff += int(gd[i].z) != c % f.grid.res || int(gd[i].w) != c / f.grid.res;
                const glm::vec2 cd = nav::direction(f, xy), g(gd[i]);
                zeroDiff += (cd == glm::vec2(0.0f)) != (g == glm::vec2(0.0f));
                bitDiff += cd != g;
                maxDiff = std::max(maxDiff, double(glm::length(cd - g)));
                const glm::vec2 cg = nav::goal(f, vs.layout, glm::vec3(pts[i]));
                // Points closer to a wall than a centre can stand (the contacts keep >= BODY_RADIUS; plausibility's tolerance): the wall
                // direction (point - nearest) / distance amplifies rounding there; compared apart (information)
                if (seated::wall(vs.layout, glm::vec3(pts[i]), FEELER_REACH).z < BODY_RADIUS - 3e-4f) {
                    ++closeToWall;
                    gMaxClose = std::max(gMaxClose, double(glm::length(cg - gg[i])));
                    continue;
                }
                agr.add(vs.layout, glm::vec3(pts[i]), cd, cg, gg[i], i < size_t(np), [&](glm::vec3 q) { return nav::goal(f, vs.layout, q); });
            }
            char b[900];
            std::snprintf(b, sizeof b, "GPU navDirection = CPU nav::direction at %zu points (every seat and random ones): the same cell everywhere "
                          "(%ld points in a NOFIT cell took a FIT neighbour's), max |difference| %.2g (<= 1e-6; bit-identical at %ld)", pts.size(), viaFit,
                          maxDiff, long(pts.size()) - bitDiff);
            check(cellDiff == 0 && zeroDiff == 0 && maxDiff <= 1e-6, b);
            std::snprintf(b, sizeof b, "GPU navGoal = CPU nav::goal (e_goal: the field's direction without its component into a wall or step face beside the agent; "
                          "%ld of %ld points beside one, bit-identical at %ld), the criterion of tools/nav_goal_check.hpp: (1) away from every decision (%ld points) max |difference| %.2g "
                          "(<= 1e-5); (2) beyond 1e-5: %ld points (seats %ld), all at a decision: %s, each the CPU's value on the decision's other side (the reach "
                          "-+ %.2g: %ld; a point <= %d ulps away: %ld; neither: %ld); (3) random points beyond 1e-5: %ld of %ld (<= 0.1%%); %ld points closer to a "
                          "wall than BODY_RADIUS - 3e-4: max %.2g, information", agr.projected, agr.compared, agr.bitSame, agr.compared - agr.atDecision, agr.maxAway,
                          agr.differ, agr.differSeats, agr.unexplained == 0 ? "yes" : "NO", double(nav_goal_check::DECISION_TOL), agr.byReach,
                          nav_goal_check::REPRO_ULPS, agr.byMove, agr.notReproduced, agr.differRandom, agr.comparedRandom, closeToWall, gMaxClose);
            check(agr.pass() && agr.projected > 0, b);
            {   // (4) The GPU's cell table at run time (vsBand / vsCell / vsCellTop) against the CPU's: the criterion's assumption
                const fs::path ct = processTempPath("swarm_cell_probe.comp");
                std::ofstream(ct) << nav_goal_check::cellTableProbeSource();
                GLuint cp = loadComputeProgram(ct, {}, &vs);
                fs::remove(ct);
                const size_t n = size_t(seated::bandCount(vs.layout)) * size_t(nav_goal_check::CELL_PROBE_CELLS);
                GLuint c0 = makeBuffer(std::vector<glm::vec4>(n)), c1 = makeBuffer(std::vector<glm::vec4>(n));
                glUseProgram(cp);
                glUniform1i(glGetUniformLocation(cp, "count"), GLint(n));
                glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, c0);
                glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 7, c1);
                glDispatchCompute(GLuint((n + 63) / 64), 1, 1);
                const nav_goal_check::CellParity par = nav_goal_check::compareCellTable(vs.layout, readBuffer<glm::vec4>(c0, n), readBuffer<glm::vec4>(c1, n));
                for (GLuint x : { c0, c1 }) glDeleteBuffers(1, &x);
                glDeleteProgram(cp);
                std::snprintf(b, sizeof b, "(4) venue S's cell table on the GPU at run time = the CPU's within %.2g model units (%ld bands, %ld cells; differing: %ld band(s), "
                              "%ld cell(s), largest %.2g model units = %ld ulp(s) of a bound; the same kinds, rows and cells: %s; AMD 26.10.1 reassociates and folds "
                              "the bounds' constant sums)", double(nav_goal_check::BOUND_TOL), par.bands, par.cells, par.bandDiff, par.cellDiff, par.maxAbs,
                              par.maxBoundUlps, par.structDiff == 0 ? "yes" : "NO");
                check(par.pass(), b);
            }
        }

        section("nav.field_validation: Navigation field validation: known answers; venue S's paths, descent, exit choice, the gangway rule");
        {
            for (const nav_check::KnownCase& c : nav_check::knownCases()) {
                const nav_check::KnownResult k = nav_check::runKnown(c);
                char b[300];
                std::snprintf(b, sizeof b, "(a) %s: %ld cells, max |D - D_ref| %.4f m (%.2f cells, limit %.0f), mean %.4f m, %ld without a path%s", c.name.c_str(),
                              k.compared, k.maxErr, k.maxErrCells, c.limitCells, k.meanErr, k.unreachable,
                              k.splitA + k.splitB > 0 ? (std::string("; split: ") + std::to_string(k.splitMismatch) + " cells on the farther door, all within " +
                                                         std::to_string(k.splitMaxMargin).substr(0, 6) + " m of equal distance").c_str() : "");
                check(k.ok, b);
            }
            const nav::Field& f = nav::forVenue(venueS());
            const nav_check::VenueResult r = nav_check::runVenue(venueS(), f);
            check(r.seatsNoPath == 0 && r.seatsNotFit == 0, "(b) all " + std::to_string(r.seats) + " seats lie in FIT cells with a path to an exit");
            check(r.walkableNoPath == 0, "(b) every cell an agent can walk to from a seat (" + std::to_string(r.walkable) + ") has a path to an exit");
            for (const auto& un : r.unreachable) std::printf("  unreachable: %-40s %8ld cells %8.1f m^2\n", un.kind.c_str(), un.cells, un.cells * nav::CELL_M * nav::CELL_M);
            char b[300];
            std::snprintf(b, sizeof b, "(c) descent from every seat along e_goal (0.05 m steps): %ld stalls, path / field distance mean %.4f, worst %.4f (<= 1.2); "
                          "%ld point steps clip a face (information, at most %.4f m beyond it)", r.stalls, r.meanRatio, r.worstRatio, r.illegalSteps, r.maxOvershootM);
            check(r.stalls == 0 && r.worstRatio <= 1.2, b);
            long doors = 0;
            for (size_t e = 4; e < r.perExit.size(); ++e) doors += r.perExit[e];
            std::printf("  (d) nearest exit: rear doors %ld seats (%.1f%%), avenues %ld\n", doors, 100.0 * double(doors) / double(r.seats), r.seats - doors);
            std::printf("  (e) most seats between two gangways in a row %d (rows over 28: %d), in a dead-end segment %d\n", r.maxBetween, r.rowsOver28, r.maxDeadEnd);
            check(doors + (r.seats - doors) == r.seats && r.maxDeadEnd <= venueS().params.maxSeatsDeadEnd, "(d, e) every seat has a nearest exit; dead-end segments "
                  "within the rule (rows over 28 between gangways: " + std::to_string(r.rowsOver28) + ", reported)");
        }

        section("validation.s_evacuation: Venue S routed by the navigation field: CPU/GPU equivalence, the golden state, full evacuations with every check");
        {
            const Venue& vs = venueS();
            const SeatedLayout& L = vs.layout;
            const int nS = 4096;
            const std::vector<GpuBoid> spawnS = spawnSeatedCrowd(vs, nS, 1.0, 1337);
            const std::vector<int> rowsS = venue_s::seatRows(vs, seatedSpawnSeats(vs, nS, 1.0, 1337));
            auto gpuRun = [&](int steps) {
                CrowdSim sim(shaderDir, nS, vs);
                sim.upload(spawnS);
                for (int i = 0; i < steps; ++i) sim.step(0);
                return readBuffer<GpuBoid>(sim.currentStateBuffer(), size_t(nS));
            };
            auto cpuRun = [&](CpuCrowdSim::SortMode mode, int steps, int threads = 0) {
                CpuCrowdSim cpu(vs, {}, threads, mode);
                cpu.setState(spawnS);
                for (int i = 0; i < steps; ++i) cpu.step();
                return cpu.state();
            };
            // One step from the same mid-evacuation state
            const std::vector<GpuBoid> mid = gpuRun(200);
            long active = 0;
            for (const GpuBoid& b : mid) active += b.position.w != 0.0f;
            std::vector<GpuBoid> g1;
            std::vector<GpuGridInfo> gGrid;
            std::vector<GpuCellData> gCells;
            {
                CrowdSim sim(shaderDir, nS, vs);
                sim.upload(mid);
                sim.step(0);
                g1 = readBuffer<GpuBoid>(sim.currentStateBuffer(), size_t(nS));
                gGrid = readBuffer<GpuGridInfo>(sim.gridBuffer(), size_t(nS));
                gCells = readBuffer<GpuCellData>(sim.cellBuffer(), size_t(vs.gridRes) * vs.gridRes);
            }
            for (int m = 0; m < 2; ++m) {
                CpuCrowdSim cpu(vs, {}, 0, SORT_MODES[m]);
                cpu.setState(mid);
                cpu.step();
                long out = 0, seqDiff = 0, pairDiff = 0;
                for (size_t i = 0; i < mid.size(); ++i) {
                    if (mid[i].position.w != 0.0f) out += glm::length(glm::vec3(cpu.state()[i].position) - glm::vec3(g1[i].position)) > 2e-4f;
                    seqDiff += cpu.grid()[i].gridID != gGrid[i].gridID;
                    pairDiff += cpu.grid()[i].boidID != gGrid[i].boidID;
                }
                const bool cellsSame = std::memcmp(cpu.cells().data(), gCells.data(), gCells.size() * sizeof(GpuCellData)) == 0;
                const std::string mode = modeName(SORT_MODES[m]);
                check(cellsSame && seqDiff == 0 && (m == 0 || pairDiff == 0), "routed, grid exact (" + mode + ")");
                check(double(out) < 0.005 * double(active), "routed, one step from the GPU state after 200 steps (" + std::to_string(active) + " active), CPU " +
                      mode + ": |dpos| > 2e-4 for " + std::to_string(out) + " agents (< 0.5%)");
            }
            // The golden state of routed S: 250 steps from the full seat spawn (GOLDEN_S)
            const std::vector<GpuBoid> gs = gpuRun(golden::GOLDEN_STEPS);
            const std::vector<GpuBoid> cs = cpuRun(CpuCrowdSim::SortMode::Counting, golden::GOLDEN_STEPS), cb = cpuRun(CpuCrowdSim::SortMode::GpuBitonic, golden::GOLDEN_STEPS);
            const uint64_t h[3] = { golden::stateHash(gs), golden::stateHash(cs), golden::stateHash(cb) };
            long act[3] = {};
            for (const GpuBoid& b : gs) act[0] += b.position.w != 0.0f;
            for (const GpuBoid& b : cs) act[1] += b.position.w != 0.0f;
            for (const GpuBoid& b : cb) act[2] += b.position.w != 0.0f;
            std::printf("  golden S (routed; the state after %d steps of the full seat spawn; active %ld / %ld / %ld): GPU %016llx, CPU counting %016llx, "
                        "CPU bitonic %016llx\n", golden::GOLDEN_STEPS, act[0], act[1], act[2], (unsigned long long)h[0], (unsigned long long)h[1],
                        (unsigned long long)h[2]);
            check(act[0] > 0 && act[1] > 0 && act[2] > 0 && act[0] < 3728, "the routed golden states have active agents, and agents have left (" +
                  std::to_string(act[0]) + " of 3728 active on the GPU)");
            const std::string driverNow = std::string((const char*)glGetString(GL_RENDERER)) + " | " + (const char*)glGetString(GL_VERSION);
            if (driverNow == golden::GOLDEN_DRIVER) check(h[0] == golden::GOLDEN_S[0].hash, std::string("GPU venue S routed: matches the pinned ") + golden::GOLDEN_S[0].name);
            else std::printf("  [WARN] driver differs from the golden pin's; GPU venue S not compared\n");
            check(h[1] == golden::GOLDEN_S[1].hash && h[2] == golden::GOLDEN_S[2].hash, "CPU venue S routed (counting, bitonic): match the pinned golden hashes");
            {   // The nearest-exit, level-speed model stays selectable bit for bit: its state after GOLDEN_STEPS steps equals
            // its pin (GOLDEN_S_NEAREST)
                CrowdSim simN(shaderDir, nS, vs, ModelOptions{});
                simN.upload(spawnS);
                for (int i = 0; i < golden::GOLDEN_STEPS; ++i) simN.step(0);
                const uint64_t hn = golden::stateHash(readBuffer<GpuBoid>(simN.currentStateBuffer(), size_t(nS)));
                uint64_t hc[2];
                for (int m = 0; m < 2; ++m) {
                    CpuCrowdSim cpu(vs, ModelOptions{}, {}, 0, SORT_MODES[m]);
                    cpu.setState(spawnS);
                    for (int i = 0; i < golden::GOLDEN_STEPS; ++i) cpu.step();
                    hc[m] = golden::stateHash(cpu.state());
                }
                std::printf("  nearest exit, level speed: GPU %016llx, CPU counting %016llx, CPU bitonic %016llx\n", (unsigned long long)hn,
                            (unsigned long long)hc[0], (unsigned long long)hc[1]);
                if (driverNow == golden::GOLDEN_DRIVER) check(hn == golden::GOLDEN_S_NEAREST[0].hash, std::string("nearest exit, level speed selectable: ") + golden::GOLDEN_S_NEAREST[0].name + " matches its pin");
                check(hc[0] == golden::GOLDEN_S_NEAREST[1].hash && hc[1] == golden::GOLDEN_S_NEAREST[2].hash, "nearest exit, level speed selectable: CPU counting and bitonic match their pins");
            }
            {   // The queue-aware, incline-speed model with the level spacing on the inclines stays selectable bit for bit: its state
            // after GOLDEN_STEPS steps equals its pin (GOLDEN_S_LEVEL_SPACING)
                const ModelOptions levelSpacing{ ExitChoice::QueueAware, true, StairFlow::Off };
                CrowdSim simL(shaderDir, nS, vs, levelSpacing);
                simL.upload(spawnS);
                for (int i = 0; i < golden::GOLDEN_STEPS; ++i) simL.step(0);
                const uint64_t hl = golden::stateHash(readBuffer<GpuBoid>(simL.currentStateBuffer(), size_t(nS)));
                uint64_t hc[2];
                for (int m = 0; m < 2; ++m) {
                    CpuCrowdSim cpu(vs, levelSpacing, {}, 0, SORT_MODES[m]);
                    cpu.setState(spawnS);
                    for (int i = 0; i < golden::GOLDEN_STEPS; ++i) cpu.step();
                    hc[m] = golden::stateHash(cpu.state());
                }
                std::printf("  queue-aware, incline speed, level spacing: GPU %016llx, CPU counting %016llx, CPU bitonic %016llx\n",
                            (unsigned long long)hl, (unsigned long long)hc[0], (unsigned long long)hc[1]);
                if (driverNow == golden::GOLDEN_DRIVER) check(hl == golden::GOLDEN_S_LEVEL_SPACING[0].hash, std::string("level spacing selectable: ") + golden::GOLDEN_S_LEVEL_SPACING[0].name + " matches its pin");
                check(hc[0] == golden::GOLDEN_S_LEVEL_SPACING[1].hash && hc[1] == golden::GOLDEN_S_LEVEL_SPACING[2].hash, "level spacing selectable: CPU counting and bitonic match their pins");
            }
            if (longTier("the full routed evacuations of S (GPU 100% and 50% load with every check; the CPU reference's evacuation time; DT / 2 and DT / 4)")) {
                CrowdSim sim(shaderDir, nS, vs);
                sim.upload(spawnS);
                const std::vector<GpuMetricCellInfo> info = metrics::computeMetricVenueSeated(L).cellInfo();
                metrics::CrowdMetrics gm(shaderDir, nS, info, &vs);
                venue_s::Checker chk;
                chk.init(L, spawnS, rowsS);
                std::vector<GpuBoid> before = spawnS;
                const plausibility::Result r = plausibility::runEvacuation(sim, 0, spawnS, gm, info, 6000, plausibility::VenueKind::Analytic,
                    [&](int s, const std::vector<GpuBoid>& state) {
                        if (s > 1) chk.step(s - 1, before, state);
                        before = state;
                    });
                chk.step(r.steps, before, readBuffer<GpuBoid>(sim.currentStateBuffer(), size_t(nS)));
                plausibility::print(r);
                checkerSummary(chk);
                const GpuMetricCounters ctr = gm.readCounters();
                long doors = 0;
                for (int e = metrics::EXIT_DOOR0; e < metrics::EXIT_SLOTS; ++e) doors += ctr.exits[e];
                std::printf("  exits: avenues +x %u -x %u +y %u -y %u, doors %ld, other %u\n", ctr.exits[0], ctr.exits[1], ctr.exits[2], ctr.exits[3], doors,
                            ctr.exits[metrics::EXIT_OTHER]);
                long unusedExits = 0;   // the default queue-aware exit choice uses every exit
                for (int e = 0; e < metrics::exitSlotsUsed(&L); ++e) unusedExits += e != metrics::EXIT_OTHER && ctr.exits[e] == 0;
                check(sim.options().exitChoice != ExitChoice::QueueAware || unusedExits == 0, "the default model (" + modelOptionsLabel(vs, sim.options()) +
                      "): every one of the 12 exits used (" + std::to_string(unusedExits) + " unused)");
                check(r.evacStep > 0 && !r.nan && ctr.evacuated == 3728 && ctr.exits[metrics::EXIT_OTHER] == 0, "100% load: all 3728 agents leave (step " +
                      std::to_string(r.evacStep) + ", " + std::to_string(r.evacStep * DT_REAL_S).substr(0, 6) + " s), each through an avenue or a door");
                char b[300];
                std::snprintf(b, sizeof b, "plausibility with NO exemption: overlap over ALL %zu pair-steps p99 %.4f <= 0.05, max %.4f <= 0.20; grid, floors, fence, "
                              "walls, speed, density ceiling", r.allStats.n, r.allStats.p99, r.allStats.max);
                check(r.overlapOk() && plausibility::Result::withinCrowdLimits(r.allStats) && r.gridOk() && r.floorOk() && r.fenceOk() && r.wallOk() &&
                      r.speedOk() && r.densityOk(), b);
                check(chk.rowChanges == 0 && structural(chk), "INV-row over the whole evacuation: 0 row changes; no seat-block crossing, tunnelling or wall top");
                check(chk.risesAbove == 0 && chk.verticalClimbs == 0, "0 rises above MAX_STEP_UP, 0 climbs over a vertical face");
                // the CPU reference to the last agent out (counting sort)
                CpuCrowdSim cpu(vs, {}, 0, CpuCrowdSim::SortMode::Counting);
                cpu.setState(spawnS);
                int cpuEvac = -1;
                for (int s = 1; s <= 6000 && cpuEvac < 0; ++s) {
                    cpu.step();
                    long a = 0;
                    for (const GpuBoid& q : cpu.state()) a += q.position.w != 0.0f;
                    if (a == 0) cpuEvac = s;
                }
                const double rel = (double(cpuEvac) - double(r.evacStep)) / double(std::max(r.evacStep, 1));
                check(cpuEvac > 0 && std::abs(rel) <= 0.05, "CPU reference (counting) evacuates at step " + std::to_string(cpuEvac) + " vs GPU " +
                      std::to_string(r.evacStep) + " (" + std::to_string(100.0 * rel).substr(0, 6) + "%, within +-5%)");
                // 50% load
                const std::vector<GpuBoid> half = spawnSeatedCrowd(vs, 2048, 0.5, 1337);
                CrowdSim sim2(shaderDir, 2048, vs);
                sim2.upload(half);
                metrics::CrowdMetrics gm2(shaderDir, 2048, info, &vs);
                venue_s::Checker chk2;
                chk2.init(L, half, venue_s::seatRows(vs, seatedSpawnSeats(vs, 2048, 0.5, 1337)));
                before = half;
                const plausibility::Result r2 = plausibility::runEvacuation(sim2, 0, half, gm2, info, 6000, plausibility::VenueKind::Analytic,
                    [&](int s, const std::vector<GpuBoid>& state) {
                        if (s > 1) chk2.step(s - 1, before, state);
                        before = state;
                    });
                chk2.step(r2.steps, before, readBuffer<GpuBoid>(sim2.currentStateBuffer(), size_t(2048)));
                check(r2.evacStep > 0 && r2.allOk() && plausibility::Result::withinCrowdLimits(r2.allStats) && chk2.rowChanges == 0 && structural(chk2) &&
                      chk2.risesAbove == 0 && chk2.verticalClimbs == 0, "50% load (1864 agents): everyone leaves (step " + std::to_string(r2.evacStep) +
                      "), plausibility with no exemption, INV-row 0, step-up rules hold");
                // DT convergence at 100% load: t100 at DT / 2 and DT / 4 within 5% of the step before. Without the
                // NOFIT rule (navDirection) a standoff that flips at a FIT / NOFIT cell boundary holds 40 agents until the run's end at DT / 4.
                double tPrev = r.evacStep * double(DT);
                int divPrev = 1;
                for (int div : { 2, 4 }) {
                    const float dtD = DT / float(div);
                    const fs::path dir = makeShaderVariant(shaderDir, "s_dt_div" + std::to_string(div), dtOverride(dtD));
                    CrowdSim simD(dir, nS, vs);
                    fs::remove_all(dir);
                    simD.upload(spawnS);
                    int evac = -1;
                    for (int s = 1; s <= 6000 * div && evac < 0; ++s) {
                        simD.step(0);
                        long a = 0;
                        for (const GpuBoid& q : readBuffer<GpuBoid>(simD.currentStateBuffer(), size_t(nS))) a += q.position.w != 0.0f;
                        if (a == 0) evac = s;
                    }
                    const double t = evac * double(dtD), rel = (t - tPrev) / tPrev;
                    char d[200];
                    std::snprintf(d, sizeof d, "DT / %d: everyone leaves at step %d (t100 %.1f s), %+.2f%% vs DT / %d (within 5%%)", div, evac, units::seconds(t),
                                  100.0 * rel, divPrev);
                    check(evac > 0 && std::abs(rel) <= 0.05, d);
                    tPrev = t;
                    divPrev = div;
                }
            }
        }

        section("nav.exit_choice: Exit choice: known answers, hysteresis without oscillation, venue S's candidate table, GPU = CPU, a valid exit for every agent");
        {
            using choice_check::agentAt;
            const choice_check::Room room;
            const nav::ChoiceTable& rt = room.table;
            const int cs = choiceSteps(DT);
            std::printf("  two-door room: %d x %d cells of 0.1 m, exits %s / %s (1.20 m: %.4f s per queued person), V0 %.4f s per m; T_CHOICE %.1f s = %d steps, "
                        "margins %.0f%% / %.1f s, switch cap %.0f%% of Q_e (at least %d)\n", rt.grid.res, rt.grid.res, rt.exitNames[0].c_str(), rt.exitNames[1].c_str(),
                        double(rt.invCapS[0]), double(rt.secondsPerUnit), double(T_CHOICE_S), cs, 100.0 * double(CHOICE_REL_MARGIN), double(CHOICE_ABS_MARGIN_S),
                        100.0 * double(CHOICE_SWITCH_SHARE), CHOICE_MIN_SWITCHES);
            // (a) Known answer: two doors at equal distance, one already queued. 50 agents in front of the left door choose it (the nearer,
            // step 0); 8 newcomers on either side of the centre line (x 9.95 / 10.05 m, inactive in step 0) then choose the free right door.
            // Control: the newcomers alone take the nearer door; mirrored: a queue at the right door sends them left.
            auto knownAnswer = [&](bool queueLeft, bool withQueue, std::vector<uint32_t>& gpuOut, std::vector<uint32_t>& cpuOut, float* eFree, float* eQueued) {
                std::vector<GpuBoid> st;
                for (int k = 0; k < 50 && withQueue; ++k) {
                    const float x = 0.55f + 0.1f * float(k % 25);
                    st.push_back(agentAt(queueLeft ? x : 20.0f - x, 4.65f + 0.2f * float(k / 25)));
                }
                const size_t first = st.size();
                for (float y : { 4.75f, 4.95f, 5.05f, 5.25f })
                    for (float x : { 9.95f, 10.05f }) st.push_back(agentAt(x, y, false));
                std::vector<GpuBoid> active = st;
                for (size_t i = first; i < st.size(); ++i) active[i].position.w = 1.0f;
                choice_check::GpuHarness g(shaderDir, rt, st);
                nav::ChoiceState c;
                c.reset(st.size());
                g.run();
                nav::choiceStep(rt, st, c, cs);
                g.setState(active);
                g.run();
                nav::choiceStep(rt, active, c, cs);
                gpuOut = g.readAssign();
                cpuOut = c.assign;
                if (eFree) {   // the estimates a newcomer compared (the counts of step 0)
                    const glm::vec2 q(active[first].position);
                    const GpuNavChoiceCell& cell = rt.at(size_t(nav::choiceCell(rt, q)));
                    // step 1 read parity 1's prefix sums (the queue ahead)
                    const uint32_t* aR = c.ahead.data() + size_t(nav::CHOICE_QUEUE_STRIDE) * nav::CHOICE_AHEAD_BINS;
                    for (int k = 0; k < nav::CHOICE_K; ++k) {
                        const uint32_t e = nav::slotExit(cell.slot[k]);
                        if (e == nav::CHOICE_EMPTY) break;
                        const float t = nav::estimatedTime(rt, nav::slotDist(rt, cell, k), e, nav::aheadOf(aR, e, nav::slotDistQ(cell, k)));
                        (e == (queueLeft ? 1u : 0u) ? *eFree : *eQueued) = t;
                    }
                }
                return first;
            };
            {
                std::vector<uint32_t> g, c, g2, c2, g3, c3;
                float eFree = 0.0f, eQueued = 0.0f;
                const size_t first = knownAnswer(true, true, g, c, &eFree, &eQueued);
                long queuedLeft = 0, newRight = 0;
                for (size_t i = 0; i < first; ++i) queuedLeft += g[i] == 0u && c[i] == 0u;
                for (size_t i = first; i < g.size(); ++i) newRight += g[i] == 1u && c[i] == 1u;
                char b[300];
                std::snprintf(b, sizeof b, "(a) one door queued: the 50 queued agents chose the left door (%ld), all 8 newcomers the free right door (%ld; E right %.2f s, "
                              "left %.2f s); GPU pass = CPU mirror", queuedLeft, newRight, double(eFree), double(eQueued));
                check(queuedLeft == 50 && newRight == 8 && g == c, b);
                knownAnswer(false, true, g2, c2, nullptr, nullptr);
                long newLeft = 0;
                for (size_t i = 50; i < g2.size(); ++i) newLeft += g2[i] == 0u && c2[i] == 0u;
                knownAnswer(true, false, g3, c3, nullptr, nullptr);
                long nearer = 0;   // x 9.95: left (exit 0), x 10.05: right (exit 1), alternating in the list
                for (size_t i = 0; i < g3.size(); ++i) nearer += g3[i] == uint32_t(i % 2) && c3[i] == uint32_t(i % 2);
                check(newLeft == 8 && g2 == c2 && nearer == 8 && g3 == c3, "(a) mirrored, the right door queued: all 8 newcomers chose the left door (" +
                      std::to_string(newLeft) + "); without a queue each newcomer took the nearer door (" + std::to_string(nearer) + " of 8); GPU = CPU");
            }
            // (b) Hysteresis. (i) The margins: two agents at x 11.05 m assigned to the left door (2.1 m farther than the right one): equal
            // counts give a gain below the margins (no switch); 20 more agents counted at the left door make it eligible.
            {
                auto oneEvaluation = [&](uint32_t qLeft, uint32_t qRight, GpuChoiceCounters& gc, std::vector<uint32_t>& ga, nav::ChoiceState& c) {
                    const std::vector<GpuBoid> st = { agentAt(11.05f, 4.95f), agentAt(11.05f, 5.05f) };
                    choice_check::GpuHarness g(shaderDir, rt, st);
                    c.reset(st.size());
                    c.step = g.step = uint32_t(cs);   // an evaluation step
                    c.assign = { 0u, 0u };
                    g.setAssign(c.assign);
                    c.counters.queue[(c.step & 1u) * nav::CHOICE_QUEUE_STRIDE + 0] = qLeft;
                    c.counters.queue[(c.step & 1u) * nav::CHOICE_QUEUE_STRIDE + 1] = qRight;
                    g.setCounters(c.counters);
                    // The queues ahead: qLeft / qRight agents in the doors' nearest distance bin (ahead of both test agents)
                    const size_t par = size_t(c.step & 1u) * nav::CHOICE_QUEUE_STRIDE * nav::CHOICE_AHEAD_BINS;
                    c.ahead[par + 0 * nav::CHOICE_AHEAD_BINS] = qLeft;
                    c.ahead[par + 1 * nav::CHOICE_AHEAD_BINS] = qRight;
                    g.setAhead(c.ahead);
                    g.run();
                    nav::choiceStep(rt, st, c, cs);
                    gc = g.readCounters();
                    ga = g.readAssign();
                };
                GpuChoiceCounters g1, g2;
                std::vector<uint32_t> a1, a2;
                nav::ChoiceState c1, c2;
                oneEvaluation(100, 100, g1, a1, c1);
                oneEvaluation(120, 100, g2, a2, c2);
                nav::ChoiceState pre;   // the prefix sums the evaluation read (the queue ahead)
                pre.reset(1);
                pre.ahead[size_t(uint32_t(cs) & 1u) * nav::CHOICE_QUEUE_STRIDE * nav::CHOICE_AHEAD_BINS + 0 * nav::CHOICE_AHEAD_BINS] = 100u;
                pre.ahead[size_t(uint32_t(cs) & 1u) * nav::CHOICE_QUEUE_STRIDE * nav::CHOICE_AHEAD_BINS + 1 * nav::CHOICE_AHEAD_BINS] = 100u;
                pre.step = uint32_t(cs);
                {   // exclusive prefix of the read parity, as the prefix stage
                    uint32_t* a = pre.ahead.data() + size_t(uint32_t(cs) & 1u) * nav::CHOICE_QUEUE_STRIDE * nav::CHOICE_AHEAD_BINS;
                    for (int e = 0; e < 2; ++e) {
                        uint32_t run = 0;
                        for (int b = 0; b < nav::CHOICE_AHEAD_BINS; ++b) { const uint32_t h = a[e * nav::CHOICE_AHEAD_BINS + b]; a[e * nav::CHOICE_AHEAD_BINS + b] = run; run += h; }
                    }
                }
                const nav::Evaluation e1 = nav::evaluate(rt, glm::vec3(11.05f, 4.95f, 0.0f), 0u, pre.aheadRead());
                char b[300];
                std::snprintf(b, sizeof b, "(b) hysteresis margins: equal counts, gain %.2f s below max(%.0f%% of E, %.0f s): no switch (GPU %u eligible, %u switched); "
                              "20 more queued at the left door: both switch right (GPU %u, CPU %u); GPU = CPU", double(e1.gain), 100.0 * double(CHOICE_REL_MARGIN),
                              double(CHOICE_ABS_MARGIN_S), g1.eligible, g1.switches, g2.switches, c2.counters.switches);
                check(g1.eligible == 0 && g1.switches == 0 && a1 == std::vector<uint32_t>{ 0u, 0u } && a1 == c1.assign && g2.switches == 2 && a2 == c2.assign &&
                      a2 == std::vector<uint32_t>{ 1u, 1u }, b);
            }
            // (ii) No oscillation: 190 agents on the room's centre line (x 0.55 .. 19.45 m), all assigned to the left door; the closed loop
            // (each step's counts from the agents' assignments) over 40 evaluations. Expected: the switch cap moves the agents nearest the right
            // door first, the split stays one boundary (all right-door agents right of all left-door agents), no agent switches back, and the
            // assignments come to rest.
            {
                std::vector<GpuBoid> st;
                for (int k = 0; k < 190; ++k) st.push_back(agentAt(0.55f + 0.1f * float(k), 5.05f));
                choice_check::GpuHarness g(shaderDir, rt, st);
                nav::ChoiceState c;
                c.reset(st.size());
                c.assign.assign(st.size(), 0u);
                c.counters.queue[0] = uint32_t(st.size());   // step 0 reads parity 0
                g.setAssign(c.assign);
                g.setCounters(c.counters);
                std::vector<int> switches(st.size(), 0);
                std::vector<uint32_t> prev = c.assign;
                bool same = true, monotone = true;
                int lastSwitchEval = 0, evals = 0;
                std::string trail;
                for (int s = 0; s < 40 * cs + 1; ++s) {
                    g.run();
                    nav::choiceStep(rt, st, c, cs);
                    const std::vector<uint32_t> ga = g.readAssign();
                    same &= ga == c.assign;
                    if (!nav::evaluationStep(uint32_t(s), cs)) continue;
                    ++evals;
                    long moved = 0, right = 0;
                    for (size_t i = 0; i < st.size(); ++i) {
                        if (c.assign[i] != prev[i]) { ++switches[i]; ++moved; }
                        right += c.assign[i] == 1u;
                        if (i > 0 && c.assign[i] < c.assign[i - 1]) monotone = false;   // left (0) then right (1) along x
                    }
                    if (moved) lastSwitchEval = evals;
                    if (evals <= 8 || moved) trail += " " + std::to_string(right);
                    prev = c.assign;
                }
                const int maxSw = *std::max_element(switches.begin(), switches.end());
                long right = 0;
                for (uint32_t a : c.assign) right += a == 1u;
                const float splitX = 0.55f + 0.1f * float(st.size() - size_t(right));
                std::printf("  (b) closed loop: right-door agents after each evaluation:%s\n", trail.c_str());
                char b[300];
                std::snprintf(b, sizeof b, "(b) no oscillation: from all 190 at the left door the split moved in %d evaluations to x %.2f m (%ld right, %ld left) and stayed "
                              "(no switch in the last %d of %d evaluations); one boundary at every evaluation; no agent switched more than once (max %d); GPU = CPU "
                              "every step", lastSwitchEval, double(splitX), right, long(st.size()) - right, evals - lastSwitchEval, evals, maxSw);
                check(same && monotone && maxSw <= 1 && evals - lastSwitchEval >= 10 && right > 0, b);
            }
            // (c) Venue S's candidate table: GPU navChoiceCell / navChoiceDirection / navChoiceGoal = CPU at random points and every seat
            const Venue& vs = venueS();
            const nav::ChoiceTable& st = nav::choiceForVenue(vs);
            {
                std::printf("  venue S: candidate table %d x %d cells, %d per cell, %.1f MB (%s, %.2f s; key %016llx, content %016llx)\n", st.grid.res, st.grid.res,
                            nav::CHOICE_K, double(st.bytes()) / 1048576.0, st.fromCache ? "from the cache" : "built", st.buildSeconds, (unsigned long long)st.key,
                            (unsigned long long)nav::choiceContentHash(st));
                {
                    nav::ChoiceTable loaded;
                    checkCacheFile("the candidate table's cache file", nav::choiceCacheFile(vs), [&](const fs::path& p) { return nav::loadChoice(loaded, p, st.key, units::M_PER_UNIT); },
                                   [&](const fs::path& p) { return nav::saveChoice(loaded, p); });
                    check(nav::loadChoice(loaded, nav::choiceCacheFile(vs), st.key, units::M_PER_UNIT) && nav::choiceContentHash(loaded) == nav::choiceContentHash(st) &&
                              !nav::loadChoice(loaded, nav::choiceCacheFile(vs), st.key ^ 1, units::M_PER_UNIT),
                          "the candidate table read from its file = the table in memory; another key refuses it");
                }
                if (longTier("a fresh build of the candidate table compared with the cached one")) {
                    const nav::ChoiceTable fresh = nav::buildChoiceTable(nav::SeatedGeometry(vs.layout), nav::forVenue(vs));
                    check(nav::choiceContentHash(fresh) == nav::choiceContentHash(st), "venue S: the cached candidate table equals a fresh build bit for bit (" +
                          std::to_string(fresh.buildSeconds).substr(0, 5) + " s)");
                }
                std::ifstream pf(shaderDir / "physics.comp");
                std::stringstream ss;
                ss << pf.rdbuf();
                const std::string phys = ss.str();
                const size_t b0 = phys.find("// @nav-begin"), b1 = phys.find("// @nav-end");
                const fs::path tmp = processTempPath("swarm_choice_probe.comp");
                { std::ofstream(tmp) << "#version 430 core\n" + nav::choicePreambleDefines(st) + phys.substr(b0, b1 - b0) +
                      "layout(local_size_x = 64) in;\n"
                      "layout(std430, binding = 5) buffer P { vec4 pts[]; };\n"
                      "layout(std430, binding = 6) buffer R { vec4 outd[]; };\n"
                      "layout(std430, binding = 7) buffer G { vec2 outg[]; };\n"
                      "layout(std430, binding = 8) buffer X { uint ex[]; };\n"
                      "uniform int count;\n"
                      "void main() { uint i = gl_GlobalInvocationID.x; if (i >= uint(count)) return;\n"
                      "  int c = navChoiceCell(pts[i].xy);\n"
                      "  outd[i] = vec4(navChoiceDirection(pts[i].xy, ex[i]), float(c % NAV_RES), float(c / NAV_RES)); outg[i] = navChoiceGoal(pts[i].xyz, ex[i]); }\n"; }
                GLuint prog = loadComputeProgram(tmp, {}, &vs);
                fs::remove(tmp);
                std::mt19937 rng(29);
                std::uniform_real_distribution<float> u(vs.domainMin, vs.domainMax());
                std::vector<glm::vec4> pts;
                std::vector<uint32_t> exs;
                for (int i = 0; i < 50000; ++i) {
                    const glm::vec2 q(u(rng), u(rng));
                    pts.emplace_back(q, seated::floorHeight(vs.layout, q) + BODY_RADIUS, 1.0f);
                }
                for (const seated::Seat& s : seated::seats(vs.layout)) pts.emplace_back(s.pos, 1.0f);
                for (size_t i = 0; i < pts.size(); ++i) {   // each point asks for one of its cell's candidates (cycling through them), or an exit that is none
                    const GpuNavChoiceCell& c = st.at(size_t(nav::choiceCell(st, glm::vec2(pts[i]))));
                    const int k = int(i % 5);
                    exs.push_back(k < nav::CHOICE_K ? nav::slotExit(c.slot[k]) : nav::CHOICE_NONE);
                }
                GLuint bp = makeBuffer(pts), bo = makeBuffer(std::vector<glm::vec4>(pts.size())), bg = makeBuffer(std::vector<glm::vec2>(pts.size())),
                       bx = makeBuffer(exs), bt = makeBuffer(st.index), be = makeBuffer(st.entries);
                glUseProgram(prog);
                glUniform1i(glGetUniformLocation(prog, "count"), GLint(pts.size()));
                glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, bp);
                glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, bo);
                glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 7, bg);
                glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 8, bx);
                glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_NAV_CHOICE, bt);
                glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_NAV_CHOICE_ENTRY, be);
                glDispatchCompute(GLuint((pts.size() + 63) / 64), 1, 1);
                const std::vector<glm::vec4> gd = readBuffer<glm::vec4>(bo, pts.size());
                const std::vector<glm::vec2> gg = readBuffer<glm::vec2>(bg, pts.size());
                for (GLuint b : { bp, bo, bg, bx, bt, be }) glDeleteBuffers(1, &b);
                glDeleteProgram(prog);
                long cellDiff = 0, zeroDiff = 0, closeToWall = 0, zeros = 0;
                double maxDiff = 0.0;
                nav_goal_check::Agreement agr;   // the criterion of tools/nav_goal_check.hpp (nav.field's)
                for (size_t i = 0; i < pts.size(); ++i) {
                    const glm::vec2 xy(pts[i]);
                    const int c = nav::choiceCell(st, xy);
                    cellDiff += int(gd[i].z) != c % st.grid.res || int(gd[i].w) != c / st.grid.res;
                    const glm::vec2 cd = nav::choiceDirection(st, xy, exs[i]), g(gd[i]);
                    zeros += cd == glm::vec2(0.0f);
                    zeroDiff += (cd == glm::vec2(0.0f)) != (g == glm::vec2(0.0f));
                    maxDiff = std::max(maxDiff, double(glm::length(cd - g)));
                    const glm::vec2 cg = nav::choiceGoal(st, vs.layout, glm::vec3(pts[i]), exs[i]);
                    if (seated::wall(vs.layout, glm::vec3(pts[i]), FEELER_REACH).z < BODY_RADIUS - 3e-4f) { ++closeToWall; continue; }
                    agr.add(vs.layout, glm::vec3(pts[i]), cd, cg, gg[i], i < 50000, [&](glm::vec3 q) { return nav::choiceGoal(st, vs.layout, q, exs[i]); });
                }
                char b[900];
                std::snprintf(b, sizeof b, "(c) venue S: GPU navChoiceCell / navChoiceDirection = CPU at %zu points (every seat and random ones; each asking for one of "
                              "its cell's 4 candidates or an exit that is none): the same cell everywhere, max |difference| %.2g (<= 1e-6; %ld zero directions, the "
                              "same on both)", pts.size(), maxDiff, zeros);
                check(cellDiff == 0 && zeroDiff == 0 && maxDiff <= 1e-6, b);
                std::snprintf(b, sizeof b, "(c) venue S: GPU navChoiceGoal = CPU (the field's wall rule) where a centre can stand (%ld points; %ld closer to a wall than "
                              "BODY_RADIUS - 3e-4 skipped), the criterion of tools/nav_goal_check.hpp: (1) away from every decision (%ld points) max |difference| %.2g "
                              "(<= 1e-5); (2) beyond 1e-5: %ld points (seats %ld), all at a decision: %s, each the CPU's value on the decision's other side (the reach "
                              "-+ %.2g: %ld; a point <= %d ulps away: %ld; neither: %ld); (3) random points beyond 1e-5: %ld of %ld (<= 0.1%%)", agr.compared,
                              closeToWall, agr.compared - agr.atDecision, agr.maxAway, agr.differ, agr.differSeats, agr.unexplained == 0 ? "yes" : "NO",
                              double(nav_goal_check::DECISION_TOL), agr.byReach, nav_goal_check::REPRO_ULPS, agr.byMove, agr.notReproduced, agr.differRandom,
                              agr.comparedRandom);
                check(agr.pass(), b);
            }
            // (d) Routed S, queue-aware: the choice pass of CrowdSim = CpuCrowdSim's from the same state (assignments and counts bit-identical);
            // one physics step; 250 steps from the full seat spawn with every agent's assigned exit a candidate of its cell at every step
            {
                ModelOptions qa;
                qa.exitChoice = ExitChoice::QueueAware;
                const int nS = 4096;
                const std::vector<GpuBoid> spawnS = spawnSeatedCrowd(vs, nS, 1.0, 1337);
                CrowdSim sim(shaderDir, nS, vs, qa);
                sim.upload(spawnS);
                CpuCrowdSim cpuSim(vs, qa, {}, 0, CpuCrowdSim::SortMode::Counting);
                cpuSim.setState(spawnS);
                long invalid = 0, checkedSteps = 0, assignDiffSteps = 0, assignDiffMax = 0;
                std::vector<GpuBoid> state = spawnS;
                for (int s = 1; s <= golden::GOLDEN_STEPS; ++s) {
                    sim.step(0);
                    cpuSim.step();
                    const std::vector<uint32_t> ga = readBuffer<uint32_t>(sim.assignBuffer(), size_t(nS));
                    // the exits this step's predict pass used, from the start-of-step positions
                    for (int i = 0; i < nS; ++i) {
                        if (state[size_t(i)].position.w == 0.0f) continue;
                        const size_t c = size_t(nav::choiceCell(st, glm::vec2(state[size_t(i)].position)));
                        invalid += st.reachable(c) && nav::slotOf(st.at(c), ga[size_t(i)]) < 0;
                    }
                    long diff = 0;
                    for (int i = 0; i < nS; ++i) diff += ga[size_t(i)] != cpuSim.assignedExits()[size_t(i)];
                    assignDiffSteps += diff > 0;
                    assignDiffMax = std::max(assignDiffMax, diff);
                    ++checkedSteps;
                    state = readBuffer<GpuBoid>(sim.currentStateBuffer(), size_t(nS));
                }
                const GpuChoiceCounters gc = sim.readChoiceCounters();
                const uint64_t hq[2] = { golden::stateHash(state), golden::stateHash(cpuSim.state()) };
                std::printf("  (d) queue-aware S, %d steps from the full seat spawn: GPU %u evaluations, %u eligible, %u switches, %u forced; CPU %u / %u / %u / %u; "
                            "assignments GPU != CPU at %ld steps (max %ld agents: the states diverge by rounding); state hashes GPU %016llx, CPU counting %016llx\n",
                            golden::GOLDEN_STEPS, gc.evaluations, gc.eligible, gc.switches, gc.forced, cpuSim.choiceCounters().evaluations,
                            cpuSim.choiceCounters().eligible, cpuSim.choiceCounters().switches, cpuSim.choiceCounters().forced, assignDiffSteps, assignDiffMax,
                            (unsigned long long)hq[0], (unsigned long long)hq[1]);
                check(invalid == 0 && gc.switches > 0, "(d) queue-aware S: at every one of " + std::to_string(checkedSteps) + " steps every active agent's assigned "
                      "exit was a candidate of its cell (" + std::to_string(invalid) + " otherwise); " + std::to_string(gc.switches) + " switches");
                // the choice pass alone from the same state: bit-identical
                CrowdSim simA(shaderDir, nS, vs, qa);
                simA.upload(state);
                CpuCrowdSim cpuA(vs, qa, {}, 0, CpuCrowdSim::SortMode::Counting);
                cpuA.setState(state);
                bool passSame = true;
                for (int k = 0; k < 3 * cs + 1; ++k) {   // static agents: forced choices, then three evaluations
                    simA.stepExitChoice();
                    cpuA.stepExitChoice();
                    passSame &= readBuffer<uint32_t>(simA.assignBuffer(), size_t(nS)) == cpuA.assignedExits();
                }
                const GpuChoiceCounters ga = simA.readChoiceCounters(), ca = cpuA.choiceCounters();
                passSame &= std::memcmp(&ga, &ca, sizeof ga) == 0;
                check(passSame, "(d) the choice pass alone (agents at rest, " + std::to_string(3 * cs + 1) + " steps: the first choice and three evaluations, " +
                      std::to_string(ca.switches) + " switches): GPU assignments and counters = CPU bit for bit at every step");
                // one physics step from the same state (both start a fresh choice: upload resets it)
                CrowdSim simB(shaderDir, nS, vs, qa);
                simB.upload(state);
                simB.step(0);
                const std::vector<GpuBoid> g1 = readBuffer<GpuBoid>(simB.currentStateBuffer(), size_t(nS));
                const std::vector<GpuGridInfo> gGrid = readBuffer<GpuGridInfo>(simB.gridBuffer(), size_t(nS));
                long active = 0;
                for (const GpuBoid& b : state) active += b.position.w != 0.0f;
                for (int m = 0; m < 2; ++m) {
                    CpuCrowdSim cpu(vs, qa, {}, 0, SORT_MODES[m]);
                    cpu.setState(state);
                    cpu.step();
                    long out = 0, seqDiff = 0;
                    for (size_t i = 0; i < state.size(); ++i) {
                        if (state[i].position.w != 0.0f) out += glm::length(glm::vec3(cpu.state()[i].position) - glm::vec3(g1[i].position)) > 2e-4f;
                        seqDiff += cpu.grid()[i].gridID != gGrid[i].gridID;
                    }
                    check(seqDiff == 0 && double(out) < 0.005 * double(active), "(d) queue-aware, one step from the GPU state after 250 steps (" + std::to_string(active) +
                          " active), CPU " + modeName(SORT_MODES[m]) + ": grid exact, |dpos| > 2e-4 for " + std::to_string(out) + " agents (< 0.5%)");
                }
            }
        }

        section("physics.incline_speed: Incline speed: the free speed on venue S's gangway incline by the slope along the travel direction; a single agent up and down a gangway; GPU = CPU");
        {
            const Venue& vs = venueS();
            const SeatedLayout& L = vs.layout;
            ModelOptions inc;
            inc.inclineSpeed = true;
            ModelOptions incStair = inc;   // with the stair spacing (EMPIRICAL)
            incStair.stairFlow = StairFlow::Empirical;
            std::printf("  stair speeds (horizontal): ascending %.3f m/s, descending %.3f m/s (Fruin 1971 at 27 deg, as tabulated by Fujiyama & Tyler 2004; not yet checked against the originals); "
                        "full from the slope tan(27 deg) = %.4f on; the level V0 %.2f m/s\n", double(V_STAIR_UP_M_S), double(V_STAIR_DOWN_M_S),
                        double(INCLINE_REF_SLOPE), double(V_FREE_M_S));
            std::printf("  inclineFreeSpeed by slope g:");
            for (float g : { -0.6f, -0.5f, -0.4f, -0.3f, -0.2f, -0.1f, 0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f })
                std::printf(" %+.1f: %.3f", double(g), units::metresPerSecond(seated::inclineFreeSpeed(g)));
            std::printf(" m/s\n");
            check(seated::inclineFreeSpeed(0.0f) == V_MAX && seated::inclineFreeSpeed(0.6f) == V_STAIR_UP && seated::inclineFreeSpeed(-0.6f) == V_STAIR_DOWN &&
                  seated::floorSlope(L, glm::vec2(0.0f, units::modelLength(14.0)), glm::vec2(0.0f, 1.0f)) == 0.0f,
                  "the function: exactly V_MAX on the level (and on a level floor: an avenue gives slope 0), exactly the stair speeds beyond the reference slope");
            // The stair spacing's time gap, the same blend
            for (StairFlow sf : { StairFlow::Empirical, StairFlow::Conservative }) {
                const glm::vec2 t = stairHeadwayTimes(sf);
                std::printf("  stair spacing %s: T_stair ascending %.3f s, descending %.3f s; inclineHeadwayTime by slope g:", stairFlowName(sf),
                            double(t.x) * double(TIME_SCALE_S_PER_UNIT), double(t.y) * double(TIME_SCALE_S_PER_UNIT));
                for (float g : { -0.6f, -0.5f, -0.3f, -0.1f, 0.0f, 0.1f, 0.3f, 0.5f, 0.6f })
                    std::printf(" %+.1f: %.3f", double(g), double(seated::inclineHeadwayTime(g, t.x, t.y)) * double(TIME_SCALE_S_PER_UNIT));
                std::printf(" s\n");
                check(seated::inclineHeadwayTime(0.0f, t.x, t.y) == T_HEADWAY && seated::inclineHeadwayTime(0.6f, t.x, t.y) == t.x &&
                      seated::inclineHeadwayTime(-0.6f, t.x, t.y) == t.y && t.x > T_HEADWAY && t.y > T_HEADWAY,
                      std::string("stair spacing (") + stairFlowName(sf) + "): exactly T_HEADWAY on the level, exactly T_stair beyond the reference slope, "
                      "larger than the level gap");
            }
            // GPU = CPU: the @incline block (venueFloorSlope, inclineFreeSpeed) at random points and directions
            {
                std::ifstream pf(shaderDir / "physics.comp");
                std::stringstream ss;
                ss << pf.rdbuf();
                const std::string phys = ss.str();
                const size_t b0 = phys.find("// @incline-begin"), b1 = phys.find("// @incline-end");
                check(b0 != std::string::npos && b1 != std::string::npos, "physics.comp has the @incline block");
                const fs::path tmp = processTempPath("swarm_incline_probe.comp");
                { std::ofstream(tmp) << "#version 430 core\n" + phys.substr(b0, b1 - b0) +
                      "layout(local_size_x = 64) in;\n"
                      "layout(std430, binding = 5) buffer P { vec4 pts[]; };\n"
                      "layout(std430, binding = 6) buffer R { vec4 outv[]; };\n"
                      "uniform int count;\n"
                      "void main() { uint i = gl_GlobalInvocationID.x; if (i >= uint(count)) return;\n"
                      "  float g = venueFloorSlope(pts[i].xy, pts[i].zw); outv[i] = vec4(g, inclineFreeSpeed(g), inclineHeadwayTime(g), 0.0); }\n"; }
                GLuint prog = loadComputeProgram(tmp, modelPreamble(vs, incStair), &vs);
                fs::remove(tmp);
                std::mt19937 rng(31);
                std::uniform_real_distribution<float> u(vs.domainMin, vs.domainMax()), ang(0.0f, 6.2831853f);
                std::vector<glm::vec4> pts;
                for (int i = 0; i < 50000; ++i) {
                    const float a = ang(rng);
                    pts.emplace_back(u(rng), u(rng), std::cos(a), std::sin(a));
                }
                GLuint bp = makeBuffer(pts), bo = makeBuffer(std::vector<glm::vec4>(pts.size()));
                glUseProgram(prog);
                glUniform1i(glGetUniformLocation(prog, "count"), GLint(pts.size()));
                glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, bp);
                glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, bo);
                glDispatchCompute(GLuint((pts.size() + 63) / 64), 1, 1);
                const std::vector<glm::vec4> gv = readBuffer<glm::vec4>(bo, pts.size());
                glDeleteBuffers(1, &bp);
                glDeleteBuffers(1, &bo);
                glDeleteProgram(prog);
                long diff = 0, onIncline = 0, diffT = 0;
                const glm::vec2 tE = stairHeadwayTimes(StairFlow::Empirical);
                for (size_t i = 0; i < pts.size(); ++i) {
                    const float g = seated::floorSlope(L, glm::vec2(pts[i]), glm::vec2(pts[i].z, pts[i].w));
                    onIncline += g != 0.0f;
                    diff += g != gv[i].x || seated::inclineFreeSpeed(g) != gv[i].y;
                    diffT += seated::inclineHeadwayTime(g, tE.x, tE.y) != gv[i].z;
                }
                check(diff == 0 && onIncline > 0, "GPU venueFloorSlope / inclineFreeSpeed = CPU seated::floorSlope / inclineFreeSpeed bit for bit at " +
                      std::to_string(pts.size()) + " random points and directions (" + std::to_string(onIncline) + " on an incline)");
                check(diffT == 0, "GPU inclineHeadwayTime = CPU seated::inclineHeadwayTime bit for bit at the same points (EMPIRICAL's literals)");
            }
            // A single agent driven straight up / down the straight gangway of quadrant +x+y, wing 0 (rows along x, the gangway along y), on its
            // centre line (forced motion: TEST_DRIVE_TABLE), and along the walkway (the level control); GPU and CPU
            const fs::path dir = venue_s::driveVariant(shaderDir, "incline_drive");
            const float latC = 0.5f * (L.gangwayLo + L.gangwayHi);
            struct Case { const char* name; glm::vec2 start; glm::vec2 drive; float depStop; };
            const float depWalk = 0.5f * (L.standFront + float(FENCE_HALF_MID.y + FENCE_HALF_THK_COLL));
            const Case cases[] = {
                { "ascending", glm::vec2(latC, L.row0 + 2.5f * L.rowDepth), glm::vec2(0.0f, 1.0f), L.row0 + 13.0f * L.rowDepth },
                { "descending", glm::vec2(latC, L.row0 + 15.5f * L.rowDepth), glm::vec2(0.0f, -1.0f), L.row0 + 4.0f * L.rowDepth },
                { "level (walkway)", glm::vec2(units::modelLength(-10.0), depWalk), glm::vec2(1.0f, 0.0f), 0.0f },   // along its straight stretch (|x| < 11.9 m)
            };
            for (const Case& c : cases) {
                for (int engine = 0; engine < 2; ++engine) {
                    std::vector<GpuBoid> st(256);
                    for (GpuBoid& b : st) b.position = glm::vec4(PARK_COORD, PARK_COORD, PARK_COORD, 0.0f);
                    st[0].position = glm::vec4(c.start, seated::floorHeight(L, c.start) + BODY_RADIUS, 1.0f);
                    std::vector<glm::vec2> drive(st.size(), glm::vec2(0.0f));
                    drive[0] = c.drive;
                    std::unique_ptr<venue_s::GpuEngine> g;
                    std::unique_ptr<venue_s::CpuEngine> cpu;
                    if (engine == 0) { g = std::make_unique<venue_s::GpuEngine>(dir, 256, vs, inc); g->upload(st); g->setDrive(drive); }
                    else { cpu = std::make_unique<venue_s::CpuEngine>(vs, 0, CpuCrowdSim::SortMode::Counting, inc); cpu->upload(st); cpu->setDrive(drive); }
                    double sum = 0.0, maxErr = 0.0, target = 0.0;
                    int n = 0, steps = 0;
                    for (int s = 1; s <= 400; ++s) {
                        const glm::vec4 p0 = (engine == 0 ? g->state() : cpu->state())[0].position;
                        if (engine == 0) g->step(); else cpu->step();
                        steps = s;
                        const GpuBoid b = (engine == 0 ? g->state() : cpu->state())[0];
                        const float dep = seated::fold(glm::vec2(b.position)).y;
                        if (c.drive.y > 0.0f ? dep > c.depStop : (c.drive.y < 0.0f ? dep < c.depStop : s > 85)) break;   // level: 85 steps, ~19 m
                        if (s <= 30) continue;   // 5.2 s: the relaxation from rest (TAU_RELAX 0.5 s) is complete
                        const float slope = seated::floorSlope(L, glm::vec2(p0), c.drive);
                        target = units::metresPerSecond(c.drive.y == 0.0f ? V_MAX : seated::inclineFreeSpeed(slope));
                        const double v = units::metresPerSecond(glm::length(glm::vec2(b.velocity)));
                        sum += v;
                        maxErr = std::max(maxErr, std::abs(v - target) / target);
                        ++n;
                    }
                    char b[260];
                    std::snprintf(b, sizeof b, "%s %s: horizontal speed %.4f m/s (mean of %d steps after 5.2 s, until step %d), target %.4f m/s: worst step %.3f%% off "
                                  "(within 1%%)", engine == 0 ? "GPU" : "CPU", c.name, n ? sum / n : 0.0, n, steps, target, 100.0 * maxErr);
                    check(n >= 30 && maxErr <= 0.01, b);
                }
            }
            fs::remove_all(dir);
        }

        section("venue.generated_m_l: Generated venues M and L: layout rules, the analytic distance, GPU = CPU, exits; long tier: the golden pins, one-step equivalence, the exit choice's type diversity on S");
        for (const Venue* vg : { &venueM(), &venueL() }) {
            const SeatedLayout& L = vg->layout;
            const bool isM = vg == &venueM();
            const std::string nm = std::string("venue ") + vg->name;
            // Layout: the pinned seat counts, the gangway rule on every row, a door at every gangway head, the exit rule, the limits
            long total = 0;
            int bad = 0, maxB = 0, maxD = 0;
            for (const seated::RowSeats& rs : seated::seatsPerRow(L)) {
                total += 8L * rs.total;
                maxB = std::max(maxB, rs.between);
                maxD = std::max(maxD, rs.deadEnd);
                bad += rs.between > vg->params.maxSeatsBetweenGangways || rs.deadEnd > vg->params.maxSeatsDeadEnd;
            }
            const long pinned = isM ? 15832 : 63424;
            check(L.rows == (isM ? 43 : 95) && total == pinned && long(seated::seats(L).size()) == total,
                  nm + ": " + std::to_string(L.rows) + " rows, " + std::to_string(total) + " seats (pinned " + std::to_string(pinned) + "), seated::seats lists them all");
            check(bad == 0 && maxB == 28 && maxD == 14, nm + ": every row within the gangway rule (at most 28 seats between gangways: " + std::to_string(maxB) +
                  ", 14 in a dead end: " + std::to_string(maxD) + ")");
            const nav::Grid ng = nav::venueGrid(*vg);
            check(L.cornerDoorLo < 1e8f && L.doors == L.gangways && L.doorsPerQuadrant() == L.gangwaysPerQuadrant() &&
                      L.totalExitWidthM >= L.requiredExitWidthM && seated::exitCount(L) <= nav::CHOICE_MAX_EXITS &&
                      seated::gangwayCount(L) <= metrics::GANGWAY_SLOTS && 4 * L.doorsPerQuadrant() <= metrics::EXIT_DOORS &&
                      ng.cells() <= size_t(nav::CHOICE_ANCHOR_MASK) + 1,
                  nm + ": a door at every gangway head (" + std::to_string(seated::gangwayCount(L)) + "), total exit width " +
                  std::to_string(L.totalExitWidthM).substr(0, 6) + " m >= the rule's " + std::to_string(L.requiredExitWidthM).substr(0, 6) +
                  " m, within the exit / gangway / cell limits");
            // The analytic distance against the brute force (outside), the sign, at a sample (venue_probe exact runs 100 000)
            const std::vector<seated::Primitive> prims = seated::primitives(L);
            std::mt19937 rng(isM ? 11u : 13u);
            std::uniform_real_distribution<float> uxy(-L.landingEnd, L.landingEnd), udz(float(units::modelLength(-0.5)), float(units::modelLength(1.5)));
            const int np = 2000;
            std::vector<glm::vec3> pts;
            for (int i = 0; i < np; ++i) {
                const glm::vec2 q(uxy(rng), uxy(rng));
                pts.emplace_back(q, seated::floorHeight(L, q) + udz(rng));
            }
            double maxOut = 0.0;
            int signBad = 0;
            for (const glm::vec3& p : pts) {
                const float d = seated::sdf(L, p);
                const bool in = seated::bruteForceInside(prims, glm::dvec3(p));
                signBad += (d <= 0.0f) != in && std::abs(d) > 1e-6f;
                if (!in) maxOut = std::max(maxOut, std::abs(double(d) - seated::bruteForceDistance(prims, glm::dvec3(p))));
            }
            char b[300];
            std::snprintf(b, sizeof b, "%s: the analytic distance equals the brute force over its %zu primitives outside the solid (max %.3g <= 1e-6) and its sign "
                          "agrees at all %d points (%d disagree)", nm.c_str(), prims.size(), maxOut, np, signBad);
            check(maxOut <= 1e-6 && signBad == 0, b);
            // GPU (physics.comp's @sdf block on the venue's preamble: VS_GENERATED 1) = the CPU mirror
            {
                std::ifstream pf(shaderDir / "physics.comp");
                std::stringstream ss;
                ss << pf.rdbuf();
                const std::string phys = ss.str();
                const size_t b0 = phys.find("// @sdf-begin"), b1 = phys.find("// @sdf-end");
                const fs::path tmp = processTempPath("swarm_generated_sdf_probe.comp");
                { std::ofstream(tmp) << "#version 430 core\n" + phys.substr(b0, b1 - b0) +
                      "layout(local_size_x = 64) in;\n"
                      "layout(std430, binding = 5) buffer P { vec4 pts[]; };\n"
                      "layout(std430, binding = 7) buffer F { vec4 outf[]; };\n"
                      "uniform int count;\n"
                      "void main() { uint i = gl_GlobalInvocationID.x; if (i >= uint(count)) return; vec3 p = pts[i].xyz;\n"
                      "  outf[i] = vec4(map(p), venueFloor(p.xy), float(venueGangwayAt(p.xy)), 0.0); }\n"; }
                GLuint prog = loadComputeProgram(tmp, {}, vg);
                fs::remove(tmp);
                std::vector<glm::vec4> in;
                for (const glm::vec3& p : pts) in.emplace_back(p, 1.0f);
                GLuint bin = makeBuffer(in), bf = makeBuffer(std::vector<glm::vec4>(in.size()));
                glUseProgram(prog);
                glUniform1i(glGetUniformLocation(prog, "count"), np);
                glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, bin);
                glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 7, bf);
                glDispatchCompute(GLuint((np + 63) / 64), 1, 1);
                const std::vector<glm::vec4> gf = readBuffer<glm::vec4>(bf, in.size());
                glDeleteBuffers(1, &bin);
                glDeleteBuffers(1, &bf);
                glDeleteProgram(prog);
                double maxMap = 0.0;
                int floorBad = 0, gwBad = 0;
                for (int i = 0; i < np; ++i) {
                    maxMap = std::max(maxMap, std::abs(double(gf[size_t(i)].x) - double(seated::sdf(L, pts[size_t(i)]))));
                    floorBad += gf[size_t(i)].y != seated::floorHeight(L, glm::vec2(pts[size_t(i)]));
                    gwBad += int(gf[size_t(i)].z) != seated::gangwayAt(L, glm::vec2(pts[size_t(i)]));
                }
                std::snprintf(b, sizeof b, "%s: GPU map() = the CPU mirror within %.2g (<= 1e-6), venueFloor bit-identical (%d differ), venueGangwayAt = "
                              "seated::gangwayAt (%d differ)", nm.c_str(), maxMap, floorBad, gwBad);
                check(maxMap <= 1e-6 && floorBad == 0 && gwBad == 0, b);
            }
            // Exits: the metrics' slot of a point in a door's opening = the navigation field's exit region beyond it
            int exitBad = 0, doorsSeen = 0;
            for (int q = 0; q < 4; ++q)
                for (int wing = 0; wing < 2; ++wing)
                    for (int d = 0; d <= L.doors; ++d) {
                        const bool corner = d == L.doors;
                        if (corner && wing == 1) continue;
                        // the opening's middle (a corner door's: between its low edge and the outer face, below the diagonal)
                        const float lat = corner ? 0.5f * (L.cornerDoorLo + L.outerFace) : 0.5f * (L.doorLo[size_t(d)] + L.doorHi[size_t(d)]);
                        const float dep = 0.5f * (L.outerFace + L.landingEnd);
                        const glm::vec2 f = corner ? glm::vec2(lat, dep) : glm::vec2(lat, dep);
                        const glm::vec2 xy = venue_s::unfoldPoint(f, q, wing);
                        const nav::SeatedGeometry geo(L);
                        const int e = geo.exitAt(xy);
                        ++doorsSeen;
                        const int slot = metrics::exitSlot(glm::vec4(xy, 0.0f, 1.0f), &L);
                        if (e < 4 || slot != metrics::EXIT_DOOR0 + e - 4) {
                            ++exitBad;
                            std::printf("    %s door q%d wing%d #%d (folded lat %.3f dep %.3f m): navigation exit %d, metric slot %d\n", nm.c_str(), q, wing, d,
                                        units::metres(lat), units::metres(dep), e, slot);
                        }
                    }
            check(exitBad == 0, nm + ": every door's landing is its navigation exit region and its metric slot (" + std::to_string(doorsSeen) + " doors)");
        }
        if (longTier("the generated venues' golden pins GOLDEN_M / GOLDEN_L (GPU, CPU counting, CPU bitonic; L's CPU in Release only), M's one-step "
                     "equivalence, the exit choice's type diversity leaving S's candidate table unchanged")) {
            const std::string driverNow = std::string((const char*)glGetString(GL_RENDERER)) + " | " + (const char*)glGetString(GL_VERSION);
            for (const Venue* vg : { &venueM(), &venueL() }) {
                const bool isM = vg == &venueM();
                const golden::Golden* pin = isM ? golden::GOLDEN_M : golden::GOLDEN_L;
                int seatedN = 0;
                const int nb = isM ? 16384 : 65536;
                const std::vector<GpuBoid> sp = spawnSeatedCrowd(*vg, nb, 1.0, 1337, &seatedN);
                CrowdSim sim(shaderDir, nb, *vg);
                sim.upload(sp);
                for (int i = 0; i < golden::GOLDEN_STEPS; ++i) sim.step(0);
                const uint64_t hg = golden::stateHash(readBuffer<GpuBoid>(sim.currentStateBuffer(), size_t(nb)));
                std::printf("  venue %s (%d seated, N = %d): GPU %016llx\n", vg->name, seatedN, nb, (unsigned long long)hg);
                if (driverNow == golden::GOLDEN_DRIVER) check(hg == pin[0].hash, std::string(pin[0].name) + " matches its pin");
                else std::printf("  [WARN] driver differs from the golden pin's; %s not compared\n", pin[0].name);
                {   // The level spacing on the inclines stays selectable bit for bit (GPU)
                    const golden::Golden* pinL = isM ? golden::GOLDEN_M_LEVEL_SPACING : golden::GOLDEN_L_LEVEL_SPACING;
                    CrowdSim simL(shaderDir, nb, *vg, ModelOptions{ ExitChoice::QueueAware, true, StairFlow::Off });
                    simL.upload(sp);
                    for (int i = 0; i < golden::GOLDEN_STEPS; ++i) simL.step(0);
                    const uint64_t hl = golden::stateHash(readBuffer<GpuBoid>(simL.currentStateBuffer(), size_t(nb)));
                    std::printf("  venue %s, level spacing: GPU %016llx\n", vg->name, (unsigned long long)hl);
                    if (driverNow == golden::GOLDEN_DRIVER) check(hl == pinL[0].hash, std::string(pinL[0].name) + " matches its pin (level spacing selectable)");
                }
#ifdef NDEBUG
                const bool cpuToo = true;
#else
                const bool cpuToo = isM;   // L's CPU goldens (2 x 250 steps of 63 424 agents) are Release only: Debug would take most of an hour
#endif
                if (cpuToo) {
                    uint64_t hc[2];
                    for (int m = 0; m < 2; ++m) {
                        CpuCrowdSim cpu(*vg, defaultModelOptions(*vg), {}, 0, SORT_MODES[m]);
                        cpu.setState(sp);
                        for (int i = 0; i < golden::GOLDEN_STEPS; ++i) cpu.step();
                        hc[m] = golden::stateHash(cpu.state());
                    }
                    std::printf("  venue %s: CPU counting %016llx, CPU bitonic %016llx\n", vg->name, (unsigned long long)hc[0], (unsigned long long)hc[1]);
                    check(hc[0] == pin[1].hash && hc[1] == pin[2].hash, std::string("venue ") + vg->name + ": CPU counting and bitonic match their pins");
                } else {
                    std::printf("  venue %s: CPU goldens not run in Debug (Release checks them)\n", vg->name);
                }
                if (isM) {   // one step from the GPU state after 200 steps, both sorts (venue_probe equiv's check)
                    CrowdSim s2(shaderDir, nb, *vg);
                    s2.upload(sp);
                    for (int i = 0; i < 200; ++i) s2.step(0);
                    const std::vector<GpuBoid> mid = readBuffer<GpuBoid>(s2.currentStateBuffer(), size_t(nb));
                    CrowdSim s3(shaderDir, nb, *vg);
                    s3.upload(mid);
                    s3.step(0);
                    const std::vector<GpuBoid> g1 = readBuffer<GpuBoid>(s3.currentStateBuffer(), size_t(nb));
                    const std::vector<GpuGridInfo> gGrid = readBuffer<GpuGridInfo>(s3.gridBuffer(), size_t(nb));
                    long active = 0;
                    for (const GpuBoid& q : mid) active += q.position.w != 0.0f;
                    for (int m = 0; m < 2; ++m) {
                        CpuCrowdSim cpu(*vg, defaultModelOptions(*vg), {}, 0, SORT_MODES[m]);
                        cpu.setState(mid);
                        cpu.step();
                        long out = 0, seqDiff = 0;
                        for (size_t i = 0; i < mid.size(); ++i) {
                            seqDiff += cpu.grid()[i].gridID != gGrid[i].gridID;
                            if (mid[i].position.w != 0.0f) out += glm::length(glm::vec3(cpu.state()[i].position) - glm::vec3(g1[i].position)) > 2e-4f;
                        }
                        check(seqDiff == 0 && double(out) < 0.005 * double(active), "venue M, one step from the GPU state after 200 steps (" + std::to_string(active) +
                              " active), CPU " + modeName(SORT_MODES[m]) + ": gridID sequence exact, |dpos| > 2e-4 for " + std::to_string(out) + " agents (< 0.5%)");
                    }
                }
            }
            {   // Every seat's candidates hold an avenue and a door (the type rule), and the table fits the budget
                for (const Venue* vv : { &venueS(), &venueM(), &venueL() }) {
                    const nav::ChoiceTable& ct = nav::choiceForVenue(*vv);
                    long missing = 0;
                    const std::vector<seated::Seat> seatsV = seated::seats(vv->layout);
                    for (const seated::Seat& s : seatsV) {
                        const GpuNavChoiceCell& c = ct.at(size_t(nav::choiceCell(ct, glm::vec2(s.pos))));
                        int has[2] = { 0, 0 };
                        for (int k = 0; k < nav::CHOICE_K; ++k) {
                            const uint32_t e = nav::slotExit(c.slot[k]);
                            if (e != nav::CHOICE_EMPTY) ++has[e < 4 ? 0 : 1];
                        }
                        missing += !(has[0] >= nav::CHOICE_TYPE_MIN[0] && has[1] >= nav::CHOICE_TYPE_MIN[1]);
                    }
                    check(missing == 0 && ct.bytes() <= (size_t(1) << 30),
                          std::string("venue ") + vv->name + ": every seat's " + std::to_string(nav::CHOICE_K) + " exit-choice candidates hold 2 avenues and a door (" +
                          std::to_string(missing) + " of " + std::to_string(seatsV.size()) + " seats without; the type rule); the table " +
                          std::to_string(ct.bytes() / 1048576) + " MB <= 1 GB");
                }
            }
        }

        section("venue.overcrowding_spawn: Overcrowding spawn: every seat as at 100%, people standing on the walkway and the rear concourse (S: also the gangway variant); "
                "no overlap, the density cap, additive (the seat spawn unchanged)");
        {
            auto sameBoids = [](const std::vector<GpuBoid>& a, const std::vector<GpuBoid>& b, size_t n) {
                return a.size() >= n && b.size() >= n && std::memcmp(a.data(), b.data(), n * sizeof(GpuBoid)) == 0;
            };
            struct Case { const Venue* v; double load; unsigned seed; StandingAreas areas; };
            const Case cases[] = { { &venueS(), 1.5, 1, StandingAreas::Circulation }, { &venueS(), 1.5, 1, StandingAreas::WithGangways },
                                   { &venueM(), 1.5, 1, StandingAreas::Circulation }, { &venueL(), 1.25, 1, StandingAreas::Circulation } };
            for (const Case& cs : cases) {
                const Venue& v = *cs.v;
                const SeatedLayout& L = v.layout;
                const bool gw = cs.areas == StandingAreas::WithGangways;
                const std::string tag = std::string("venue ") + v.name + " at " + std::to_string(int(std::lround(cs.load * 100.0))) + "% (" + standingAreasName(cs.areas) + ")";
                const OvercrowdSpawn sp = spawnOvercrowdedCrowd(v, cs.load, cs.seed, cs.areas);
                const int n = int(sp.boids.size());
                int seatedN = 0;
                const std::vector<GpuBoid> full = spawnSeatedCrowd(v, n, 1.0, 1337, &seatedN);
                const std::vector<int> fullSeats = seatedSpawnSeats(v, n, 1.0, 1337);
                const bool seatsSame = seatedN == sp.seats && sameBoids(full, sp.boids, size_t(sp.seats)) &&
                                       std::equal(fullSeats.begin(), fullSeats.begin() + sp.seats, sp.seat.begin());
                check(seatsSame, tag + ": agents 0 .. " + std::to_string(sp.seats - 1) + " are the 100% seat spawn bit for bit (every seat, in seat order)");
                const seated::Areas A = seated::areas(L);
                const double area = A.walkway + A.concourse + (gw ? A.gangways : 0.0);
                const int maxStanding = int(std::floor(OVERCROWD_STANDING_MAX_P_M2 * area));
                const int requested = int(std::lround((cs.load - 1.0) * double(sp.seats)));
                check(!sp.placementExhausted && sp.standingMax == maxStanding && sp.standing == std::min(requested, maxStanding) &&
                          double(sp.standing) <= OVERCROWD_STANDING_MAX_P_M2 * area && n >= sp.seats + sp.standing && (n & (n - 1)) == 0 &&
                          sp.load == double(sp.seats + sp.standing) / double(sp.seats),
                      tag + ": " + std::to_string(sp.standing) + " standing (requested " + std::to_string(requested) + ", at most " + std::to_string(maxStanding) +
                          " = " + std::to_string(OVERCROWD_STANDING_MAX_P_M2).substr(0, 3) + " p/m^2 x " + std::to_string(int(std::lround(area))) +
                          " m^2), achievable load " + std::to_string(sp.load).substr(0, 6) + ", buffer " + std::to_string(n));
                // Every standing agent on the standing floor (walkway from the fence's outer face, the concourse's CONC cells, a gangway in the
                // variant), at rest height exactly, a body's clearance from walls and the fence, at rest; the per-area counts as reported
                long offFloor = 0, wrongZ = 0, wallBad = 0, fenceBad = 0, moving = 0, notStanding = 0, parkedBad = 0;
                int counts[3] = {};
                for (int i = 0; i < n; ++i) {
                    const GpuBoid& b = sp.boids[size_t(i)];
                    if (i >= sp.seats + sp.standing) { parkedBad += b.position.w != 0.0f; continue; }
                    if (i < sp.seats) continue;
                    notStanding += sp.seat[size_t(i)] != -1 || b.position.w != 1.0f;
                    const glm::vec2 xy(b.position);
                    const glm::vec2 f = seated::fold(xy);
                    int row = -1, band = -1;
                    const int kind = seated::cellAt(L, xy, &row, &band);
                    int z = -1;
                    if (band == 0 && f.y >= FENCE_HALF_OUTER) z = 0;
                    else if (band == seated::bandCount(L) - 4 && kind == seated::CONC) z = 1;
                    else if (gw && seated::gangwayAt(L, xy) >= 0) z = 2;
                    if (z < 0) { ++offFloor; continue; }
                    ++counts[z];
                    const float fz = seated::floorHeight(L, xy);
                    wrongZ += b.position.z != fz + BODY_RADIUS;
                    wallBad += seated::wall(L, glm::vec3(xy, fz + BODY_RADIUS + L.wallAbove), 2.0f * BODY_RADIUS).z < L.wallClear;
                    fenceBad += sdFence(glm::vec3(xy, 0.0f)) < 0.0f;
                    moving += b.velocity != glm::vec4(0.0f);
                }
                check(offFloor == 0 && wrongZ == 0 && wallBad == 0 && fenceBad == 0 && moving == 0 && notStanding == 0 && parkedBad == 0 &&
                          counts[0] == sp.standingWalkway && counts[1] == sp.standingConcourse && counts[2] == sp.standingGangways && counts[0] > 0 &&
                          counts[1] > 0 && (counts[2] > 0) == gw,
                      tag + ": every standing agent on the standing floor (walkway / concourse / gangways " + std::to_string(counts[0]) + " / " +
                          std::to_string(counts[1]) + " / " + std::to_string(counts[2]) + "), at rest at floor + BODY_RADIUS exactly, clear of walls and the fence "
                          "(off the floor " + std::to_string(offFloor) + ", height " + std::to_string(wrongZ) + ", walls " + std::to_string(wallBad) + ", fence " +
                          std::to_string(fenceBad) + ")");
                // No two bodies overlap (3D centre distance >= BODY_DIAM), every active agent against every other within a cell of the hash grid
                {
                    const float cellSz = BODY_DIAM;
                    std::map<std::pair<int, int>, std::vector<int>> grid;
                    for (int i = 0; i < sp.seats + sp.standing; ++i)
                        grid[{ int(std::floor(sp.boids[size_t(i)].position.x / cellSz)), int(std::floor(sp.boids[size_t(i)].position.y / cellSz)) }].push_back(i);
                    long overlaps = 0;
                    float minD = 1e9f;
                    for (int i = sp.seats; i < sp.seats + sp.standing; ++i) {
                        const glm::vec3 c(sp.boids[size_t(i)].position);
                        const int gx = int(std::floor(c.x / cellSz)), gy = int(std::floor(c.y / cellSz));
                        for (int dy = -1; dy <= 1; ++dy)
                            for (int dx = -1; dx <= 1; ++dx) {
                                const auto it = grid.find({ gx + dx, gy + dy });
                                if (it == grid.end()) continue;
                                for (int j : it->second) {
                                    if (j == i) continue;
                                    const float d = glm::length(c - glm::vec3(sp.boids[size_t(j)].position));
                                    minD = std::min(minD, d);
                                    overlaps += d < BODY_DIAM;
                                }
                            }
                    }
                    check(overlaps == 0, tag + ": no standing body overlaps another agent (closest centre distance " + std::to_string(units::metres(minD)).substr(0, 5) +
                                             " m, BODY_DIAM 0.40 m)");
                }
                // Seeded and deterministic; another seed places the standing crowd elsewhere, the seats unchanged
                const OvercrowdSpawn again = spawnOvercrowdedCrowd(v, cs.load, cs.seed, cs.areas);
                const OvercrowdSpawn other = spawnOvercrowdedCrowd(v, cs.load, cs.seed + 1, cs.areas);
                check(sameBoids(again.boids, sp.boids, size_t(n)) && again.seat == sp.seat && sameBoids(other.boids, sp.boids, size_t(sp.seats)) &&
                          !sameBoids(other.boids, sp.boids, size_t(n)),
                      tag + ": the same seed gives the same spawn bit for bit; seed " + std::to_string(cs.seed + 1) + " the same seats and another standing crowd");
            }
            // Loads up to 100%: exactly the seat spawn (spawnOvercrowdedCrowd delegates), and the cap's achievable maximum on M
            {
                const Venue& vs = venueS();
                const OvercrowdSpawn p100 = spawnOvercrowdedCrowd(vs, 1.0, 1337), p95 = spawnOvercrowdedCrowd(vs, 0.95, 3, StandingAreas::Circulation, 4096);
                const std::vector<int> s95 = seatedSpawnSeats(vs, 4096, 0.95, 3);
                check(p100.boids.size() == 4096 && sameBoids(p100.boids, spawnSeatedCrowd(vs, 4096, 1.0, 1337), 4096) && p100.standing == 0 &&
                          sameBoids(p95.boids, spawnSeatedCrowd(vs, 4096, 0.95, 3), 4096) && p95.seat == s95 && p95.standing == 0 && p95.seats == 3542,
                      "venue S at 100% and at 95% (seed 3): spawnOvercrowdedCrowd = spawnSeatedCrowd bit for bit, nobody standing (" + std::to_string(p95.seats) + " seated at 95%)");
                const OvercrowdSpawn m2 = spawnOvercrowdedCrowd(venueM(), 2.0, 1);
                check(m2.standing == m2.standingMax && m2.standingRequested == m2.seats && m2.load < 2.0 && !m2.placementExhausted,
                      "venue M at a requested 200%: the floor takes " + std::to_string(m2.standingMax) + " standing, the achievable load " +
                          std::to_string(100.0 * m2.load).substr(0, 6) + "% is used (reported)");
            }
        }

        section("engine.program_cache: Program binary cache: programs loaded from their cached driver binaries step bit for bit as compiled ones");
        {
            const fs::path cacheDir = processTempPath("swarm_program_cache");
            std::error_code ec;
            fs::remove_all(cacheDir, ec);
            struct Case { std::string name; const Venue* venue; int n; std::vector<GpuBoid> spawn; uint64_t pin; };
            std::vector<Case> cases;
            cases.push_back({ "terrace N = 4096", &terraceVenue(), NUM_AGENTS, spawn, golden::GOLDEN[golden::GOLDEN_GPU_4096].hash });
            cases.push_back({ "venue S routed (default model, N = 4096)", &venueS(), 4096, spawnSeatedCrowd(venueS(), 4096, 1.0, 1337), golden::GOLDEN_S[0].hash });
            if (longTier("venues M and L with the program binary cache (their programs compiled twice more)")) {
                cases.push_back({ "venue M routed (N = 16384)", &venueM(), 16384, spawnSeatedCrowd(venueM(), 16384, 1.0, 1337), golden::GOLDEN_M[0].hash });
                cases.push_back({ "venue L routed (N = 65536)", &venueL(), 65536, spawnSeatedCrowd(venueL(), 65536, 1.0, 1337), golden::GOLDEN_L[0].hash });
            }
            auto runCase = [&](const Case& c) {
                CrowdSim sim(shaderDir, c.n, *c.venue);
                sim.upload(c.spawn);
                for (int i = 0; i < golden::GOLDEN_STEPS; ++i) sim.step(c.venue->seated() ? 0 : sdfTex);
                return stateHash(readBuffer<GpuBoid>(sim.currentStateBuffer(), size_t(c.n)));
            };
            auto delta = [](const ProgramCacheStats& a, const ProgramCacheStats& b) {
                ProgramCacheStats d;
                d.loaded = a.loaded - b.loaded;
                d.compiled = a.compiled - b.compiled;
                d.stored = a.stored - b.stored;
                d.rejected = a.rejected - b.rejected;
                d.loadSeconds = a.loadSeconds - b.loadSeconds;
                d.compileSeconds = a.compileSeconds - b.compileSeconds;
                return d;
            };
            // every cache file damaged (one byte of the binary flipped: its checksum no longer matches; the loader must refuse it, not the driver)
            auto damage = [&] {
                for (const fs::directory_entry& e : fs::directory_iterator(cacheDir)) {
                    if (e.path().extension() != ".bin") continue;
                    std::fstream f(e.path(), std::ios::in | std::ios::out | std::ios::binary);
                    f.seekg(0, std::ios::end);
                    const std::streamoff size = f.tellg();
                    if (size <= 64) continue;
                    char byte = 0;
                    f.seekg(size - 1);
                    f.read(&byte, 1);
                    byte = char(byte ^ 0x5a);
                    f.seekp(size - 1);
                    f.write(&byte, 1);
                }
            };
            const std::string driverNow = std::string((const char*)glGetString(GL_RENDERER)) + " | " + (const char*)glGetString(GL_VERSION);
            const char* modes[4] = { "off (compiled)", "on, empty (compiled, stored)", "on, filled (loaded)", "on, damaged (refused, compiled, stored)" };
            for (const Case& c : cases) {
                uint64_t h[4];
                ProgramCacheStats s[4];
                for (int m = 0; m < 4; ++m) {
                    if (m == 0) setProgramCache({});
                    else setProgramCache(cacheDir);
                    if (m == 1) { fs::remove_all(cacheDir, ec); fs::create_directories(cacheDir, ec); }
                    if (m == 3) damage();
                    const ProgramCacheStats before = programCacheStats();
                    h[m] = runCase(c);
                    s[m] = delta(programCacheStats(), before);
                    std::printf("  %s, cache %-38s state %016llx | programs compiled %d (%.2f s), loaded %d (%.2f s), stored %d, refused %d\n", c.name.c_str(),
                                modes[m], (unsigned long long)h[m], s[m].compiled, s[m].compileSeconds, s[m].loaded, s[m].loadSeconds, s[m].stored, s[m].rejected);
                }
                setProgramCache({});
                check(h[1] == h[0] && h[2] == h[0] && h[3] == h[0] && s[1].compiled > 0 && s[1].stored == s[1].compiled && s[2].compiled == 0 &&
                          s[2].loaded == s[1].stored && s[3].rejected == s[1].stored && s[3].compiled == s[1].stored,
                      c.name + ": the state after " + std::to_string(golden::GOLDEN_STEPS) + " steps is the same with the cache off, empty, filled (every program "
                      "loaded: " + std::to_string(s[2].loaded) + ") and damaged (every file refused, the programs compiled again)");
                char pinHex[20];
                std::snprintf(pinHex, sizeof pinHex, "%016llx", (unsigned long long)c.pin);
                if (driverNow == GOLDEN_DRIVER) check(h[0] == c.pin, c.name + ": equals its golden pin " + pinHex);
            }
            fs::remove_all(cacheDir, ec);
        }

        section("engine.gpu_capabilities: GPU capability check: the shortfall's known answers, CrowdSim refuses before any table or program, the buffer lists = the real buffers");
        {
            GpuRequirements need;
            need.ssboBindings = 20;
            need.computeSsboBlocks = 11;
            need.ssboBlockBytes = 884000000;
            need.largestBuffer = "the exit choice table";
            GpuLimits have;
            have.glMajor = 4;
            have.glMinor = 6;
            have.ssboBindings = 20;
            have.computeSsboBlocks = 11;
            have.ssboBlockBytes = 884000000;
            check(gpuShortfall(need, have).empty(), "limits equal to the requirements: no shortfall");
            GpuLimits l = have;
            l.ssboBindings = 19;
            check(gpuShortfall(need, l) == "needs 20 SSBO bindings, this GPU has 19", "one binding short: " + gpuShortfall(need, l));
            l = have;
            l.computeSsboBlocks = 10;
            check(gpuShortfall(need, l) == "needs 11 SSBOs per compute program, this GPU has 10", "one block short: " + gpuShortfall(need, l));
            l = have;
            l.ssboBlockBytes = 883999999;
            check(gpuShortfall(need, l).find("needs a buffer of 884 MB (the exit choice table)") == 0, "one byte short: " + gpuShortfall(need, l));
            l = have;
            l.glMajor = 4;
            l.glMinor = 2;
            check(gpuShortfall(need, l) == "needs OpenGL 4.3, this GPU has 4.2", "the OpenGL version: " + gpuShortfall(need, l));
            {
                GpuRequirements render = need;
                render.vertexSsboBlocks = 4;
                render.fragmentSsboBlocks = 3;
                GpuLimits s = have;
                s.vertexSsboBlocks = 4;
                s.fragmentSsboBlocks = 3;
                check(gpuShortfall(render, s).empty(), "the render stages' limits equal to the requirements: no shortfall");
                s.vertexSsboBlocks = 3;
                check(gpuShortfall(render, s) == "needs 4 SSBOs per vertex shader, this GPU has 3", "one vertex block short: " + gpuShortfall(render, s));
                s.vertexSsboBlocks = 4;
                s.fragmentSsboBlocks = 2;
                check(gpuShortfall(render, s) == "needs 3 SSBOs per fragment shader, this GPU has 2", "one fragment block short: " + gpuShortfall(render, s));
                const GpuRequirements fromLists = gpuRequirements({ { "a", false, { 0, 1, 8, 9 }, {} }, { "b", false, {}, { 8, 9, 12 } } }, {});
                check(fromLists.vertexSsboBlocks == 4 && fromLists.fragmentSsboBlocks == 3 && fromLists.computeSsboBlocks == 0 && fromLists.ssboBindings == 13,
                      "a render program's stages count apart, and the fragment stage's bindings count towards the highest binding");
            }
            l = applyGpuLimitsOverride(have, "gl=4.1,bindings=16,blocks=12,vertexblocks=4,fragmentblocks=8,blocksize=134217728");
            check(l.simulated && l.glMajor == 4 && l.glMinor == 1 && l.ssboBindings == 16 && l.computeSsboBlocks == 12 && l.vertexSsboBlocks == 4 && l.fragmentSsboBlocks == 8 &&
                      l.ssboBlockBytes == 134217728, "SWARM_GPU_LIMITS's text");

            // CrowdSim, with another GPU's limits (SWARM_GPU_LIMITS): the numbers from its own programs and table
            const Venue& vs = venueS();
            const ModelOptions model = defaultModelOptions(vs);
            const GpuRequirements real = gpuRequirements(CrowdSim::programBindings(vs, model), CrowdSim::bufferUses(vs, model, 4096));
            const nav::ChoiceTable& table = nav::choiceForVenue(vs);
            const int64_t entryBytes = int64_t(table.entries.size() * sizeof(GpuNavChoiceCell));
            std::printf("  venue S's simulation: %d SSBO bindings, %d SSBOs per compute program, largest buffer without the table %s, the table %s\n", real.ssboBindings,
                        real.computeSsboBlocks, formatBytes(real.ssboBlockBytes).c_str(), formatBytes(entryBytes).c_str());
            check(real.ssboBindings == int(BIND_NAV_CHOICE_ENTRY) + 1 && real.computeSsboBlocks == 11, "venue S queue-aware: the highest binding + 1 and the choice pass's 11 blocks");
            const auto refusal = [&](const std::string& limits) {
                _putenv_s("SWARM_GPU_LIMITS", limits.c_str());
                std::string what;
                try {
                    CrowdSim refused(shaderDir, 4096, vs, model);
                } catch (const std::runtime_error& e) {
                    what = e.what();
                }
                _putenv_s("SWARM_GPU_LIMITS", "");
                return what;
            };
            const std::string short1 = refusal("bindings=" + std::to_string(real.ssboBindings - 1));
            check(short1.find("needs " + std::to_string(real.ssboBindings) + " SSBO bindings") != std::string::npos, "one binding short: CrowdSim refuses: " + short1);
            const std::string short2 = refusal("blocks=" + std::to_string(real.computeSsboBlocks - 1));
            check(short2.find("SSBOs per compute program") != std::string::npos, "one block short: CrowdSim refuses: " + short2);
            const std::string short3 = refusal("blocksize=" + std::to_string(entryBytes - 1));
            check(short3.find("the exit choice table") != std::string::npos && short3.find("up to") == std::string::npos, "the table one byte too large: CrowdSim refuses, the exact size: " + short3);
            check(refusal("bindings=" + std::to_string(real.ssboBindings) + ",blocks=" + std::to_string(real.computeSsboBlocks) + ",blocksize=" + std::to_string(entryBytes)).empty(),
                  "limits exactly the requirements: CrowdSim runs");
            bool metricsRefused = false;
            _putenv_s("SWARM_GPU_LIMITS", "bindings=18");
            try {
                metrics::CrowdMetrics refused(shaderDir, 4096, metrics::computeMetricVenue(vs).cellInfo(), &vs);
            } catch (const std::runtime_error&) {
                metricsRefused = true;
            }
            _putenv_s("SWARM_GPU_LIMITS", "");
            check(metricsRefused, "CrowdMetrics refuses a seated venue with 18 bindings (its gangway state at binding 18)");

            // The buffer lists against the buffers the constructors really make
            const auto realBytes = [](GLuint b) {
                GLint64 size = 0;
                glBindBuffer(GL_SHADER_STORAGE_BUFFER, b);
                glGetBufferParameteri64v(GL_SHADER_STORAGE_BUFFER, GL_BUFFER_SIZE, &size);
                glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
                return int64_t(size);
            };
            {
                CrowdSim sim(shaderDir, 4096, vs, model);
                const std::vector<GpuBufferUse> uses = CrowdSim::bufferUses(vs, model, 4096);
                const auto listed = [&](const char* name) {
                    for (const GpuBufferUse& u : uses)
                        if (u.name == name) return u.bytes;
                    return int64_t(-1);
                };
                check(listed("the agent state") == realBytes(sim.currentStateBuffer()) && listed("the sorted grid") == realBytes(sim.gridBuffer()) &&
                          listed("the neighbour cells") == realBytes(sim.cellBuffer()) && listed("the navigation field") == realBytes(sim.navBuffer()) &&
                          listed("the exit choice index") == realBytes(sim.choiceTableBuffer()) && listed("the exit assignments") == realBytes(sim.assignBuffer()) &&
                          listed("the exit choice counters") == realBytes(sim.choiceCounterBuffer()) && listed("the exit choice work") == realBytes(sim.choiceWorkBuffer()) &&
                          entryBytes == realBytes(sim.choiceEntryBuffer()),
                      "CrowdSim's buffer list = its real buffers (venue S)");
                metrics::CrowdMetrics m(shaderDir, 4096, metrics::computeMetricVenue(vs).cellInfo(), &vs);
                const std::vector<GpuBufferUse> mUses = metrics::CrowdMetrics::bufferUses(4096, vs.metricGridRes);
                const auto mListed = [&](const char* name) {
                    for (const GpuBufferUse& u : mUses)
                        if (u.name == name) return u.bytes;
                    return int64_t(-1);
                };
                check(mListed("the metric counters") == realBytes(m.countersBuffer()) && mListed("the evacuation steps") == realBytes(m.evacStepBuffer()) &&
                          mListed("the metric mass") == realBytes(m.massBuffer()) && mListed("the metric cells") == realBytes(m.cellBuffer()),
                      "CrowdMetrics' buffer list = its real buffers (venue S)");
            }

            // The size known before any table is built: the cache header's count, and the bound for a venue without a cache file
            const nav::ChoiceEntryCount countS = nav::choiceEntryCountBeforeBuild(vs);
            check(countS.exact && countS.entries == table.entries.size(), "venue S: the cache file's header gives the table's exact entry count (" + std::to_string(countS.entries) + ")");
            check(nav::choiceEntryUpperBound(vs) >= table.entries.size(), "venue S: the upper bound " + std::to_string(nav::choiceEntryUpperBound(vs)) + " >= the " +
                  std::to_string(table.entries.size()) + " entries");
            if (longTier("the entry count's bound on venues M and L")) {
                for (const Venue* vg : { &venueM(), &venueL() }) {
                    const nav::ChoiceTable& tg = nav::choiceForVenue(*vg);
                    const nav::ChoiceEntryCount count = nav::choiceEntryCountBeforeBuild(*vg);
                    check(count.exact && count.entries == tg.entries.size() && nav::choiceEntryUpperBound(*vg) >= tg.entries.size(),
                          std::string("venue ") + vg->name + ": the header's count = the " + std::to_string(tg.entries.size()) + " entries, the bound " +
                              std::to_string(nav::choiceEntryUpperBound(*vg)) + " holds them");
                }
            }
        }

        section("engine.gl_debug_output: OpenGL debug output");
        for (const std::string& m : g_debug.samples) std::printf("  driver: %s\n", m.c_str());
        check(g_debug.errors == 0 && g_debug.warnings == 0 && glErrorFree,
              "no driver errors or warnings (" + std::to_string(g_debug.errors) + " errors, " +
              std::to_string(g_debug.warnings) + " warnings)");
    } catch (const std::exception& e) {
        std::printf("\nFATAL: %s\n", e.what());
        ++g_failures;
    }
    g_sectionTimes.end();
    std::printf("\nSection times (wall clock):\n");
    double totalS = 0.0;
    for (const auto& [title, s] : g_sectionTimes.done) {
        std::printf("  %8.1f s  %.70s\n", s, title.c_str());
        totalS += s;
    }
    std::printf("  %8.1f s  total\n", totalS);

    std::printf("\n%s: %d check(s) failed\n", g_failures ? "FAILED" : "ALL PASSED", g_failures);
    glfwTerminate();
    return g_failures ? 1 : 0;
}
