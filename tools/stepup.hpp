#pragma once

// Step-up diagnostics, test and tool code only (they read the agent state back every step): the floor
// under an agent, its rise in one step, the floor classes of the baked terrace venue (walkway, tread rows, aisle, the
// rear platform, wall tops) and riser climbs (an agent arriving on a higher tread row other than through the aisle).
// Used by tools/stepup/step_probe.cpp and test_gpu (physics.step_up_limit).

#include <glm/glm.hpp>

#include <swarm/gpu_types.hpp>
#include <swarm/metrics.hpp>
#include <swarm/sdf.hpp>
#include <swarm/sim_params.hpp>

#include "scene.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <limits>
#include <vector>

namespace swarm::stepup {

// --- The baked terrace's floor levels (crowd_sim.cpp TREADS; run_experiment's INV-row rows) ---
// Rows ROW_RISE apart: row 0 the walkway (z 0), rows 1-7 the treads, row 8 (PLATFORM_ROW) the rear platform behind
// the top row (z 0.141, 0.55 m above tread 7's top). A floor point of the TREAD zone (metrics::sampleZone: the treads
// and the platform) within ROW_TOLERANCE rises of a row's height is on that row; between rows (a riser ramp of the
// bake, a tread lip) it is on none.
constexpr float ROW_RISE = 0.0176f;
constexpr float ROW_TOLERANCE = 0.3f;
constexpr int PLATFORM_ROW = 8;
constexpr int NO_ROW = -1;
// Every floor of the venue lies below metrics::FLOOR_PROBE_TOP_Z (the highest, the platform, at z 0.141) and every
// wall top above it (the avenue side walls 0.164, the outer wall 0.28): a floor at or above it is a wall top
constexpr float WALL_TOP_Z = metrics::FLOOR_PROBE_TOP_Z;

// Floor under a centre c (exact CPU sampler; the selected venue's field, swarm::scene): the zero crossing of the
// field on the vertical through c.xy, the
// first one below c.z. A grounded centre (BODY_RADIUS above its floor, where physics.comp places it) is confirmed with
// two samples; otherwise the floor is searched in SEARCH_STEP steps down to SEARCH_DEPTH below the centre and bisected.
// NaN if there is none in reach or the centre itself is in solid. grounded: the centre rests on it (within
// GROUNDED_TOL).
constexpr float GROUNDED_TOL = 1e-4f;
constexpr float SEARCH_STEP = 5e-4f;
constexpr float SEARCH_DEPTH = 0.08f;
inline float floorUnder(glm::vec3 c, bool* grounded = nullptr) {
    if (grounded) *grounded = false;
    constexpr float NaN = std::numeric_limits<float>::quiet_NaN();
    if (swarm::scene::sdf(c) <= 0.0f) return NaN;
    const float rest = c.z - BODY_RADIUS;
    if (swarm::scene::sdf(glm::vec3(c.x, c.y, rest - GROUNDED_TOL)) <= 0.0f && swarm::scene::sdf(glm::vec3(c.x, c.y, rest + GROUNDED_TOL)) > 0.0f) {
        if (grounded) *grounded = true;
        return rest;
    }
    float hi = c.z, lo = c.z;
    while (swarm::scene::sdf(glm::vec3(c.x, c.y, lo)) > 0.0f) {
        hi = lo;
        lo -= SEARCH_STEP;
        if (lo < c.z - SEARCH_DEPTH) return NaN;
    }
    for (int i = 0; i < 30 && hi - lo > 1e-7f; ++i) {
        const float mid = 0.5f * (lo + hi);
        (swarm::scene::sdf(glm::vec3(c.x, c.y, mid)) > 0.0f ? hi : lo) = mid;
    }
    const float z = 0.5f * (lo + hi);
    if (grounded) *grounded = std::abs(rest - z) <= GROUNDED_TOL;
    return z;
}

// Normal n_z of the baked floor at (xy, zFloor): central differences of the exact CPU sampler (1 where the gradient
// vanishes). <= WALL_MAX_NZ: a wall-steep surface (the bake's riser ramps, n_z ~0.58; the aisle's bottom sub-step)
inline float floorNormalZ(glm::vec2 xy, float zFloor) {
    const glm::vec3 q(xy, zFloor);
    const float h = 1e-4f;
    const glm::vec3 g(swarm::scene::sdf(q + glm::vec3(h, 0, 0)) - swarm::scene::sdf(q - glm::vec3(h, 0, 0)),
                      swarm::scene::sdf(q + glm::vec3(0, h, 0)) - swarm::scene::sdf(q - glm::vec3(0, h, 0)),
                      swarm::scene::sdf(q + glm::vec3(0, 0, h)) - swarm::scene::sdf(q - glm::vec3(0, 0, h)));
    const float l = glm::length(g);
    return l > 0.0f ? g.z / l : 1.0f;
}

// The floor class of an agent at xy standing on (or above) a floor at height zFloor
struct FloorClass {
    uint32_t zone = metrics::ZONE_COUNT;   // metrics::sampleZone of xy
    int row = NO_ROW;                      // TREAD zone: tread row 1-7 or PLATFORM_ROW; walkway / avenue / exit: 0 at ground
    bool wallTop = false;                  // zFloor >= WALL_TOP_Z
    bool platform() const { return zone == metrics::ZONE_TREAD && row == PLATFORM_ROW; }
    // Floors off the egress route (step_probe's count): wall tops (above every walkable floor, unreachable) and the rear
    // platform, 0.55 m above tread 7: reachable on foot only up the aisle's sub-steps, which the router sends everyone down
    // What the step-up limit forbids is reaching it over the riser: a riser climb (ClimbTracker)
    bool offRoute() const { return wallTop || platform(); }
};

inline FloorClass classify(glm::vec2 xy, float zFloor, float outerWallInnerDepth) {
    FloorClass f;
    f.zone = metrics::sampleZone(xy, outerWallInnerDepth);
    if (std::isnan(zFloor)) return f;
    f.wallTop = zFloor >= WALL_TOP_Z;
    const float r = zFloor / ROW_RISE;
    const int k = int(std::lround(r));
    const bool onRow = std::abs(r - float(k)) <= ROW_TOLERANCE;
    if (f.zone == metrics::ZONE_TREAD) f.row = onRow && k >= 1 && k <= PLATFORM_ROW ? k : NO_ROW;
    else if (f.zone == metrics::ZONE_WALKWAY || f.zone == metrics::ZONE_AVENUE || f.zone == metrics::ZONE_EXIT) f.row = onRow && k == 0 ? 0 : NO_ROW;
    return f;
}

// Riser climbs: per agent its last row (the walkway, row 0, or a tread row, as classify gives it); the aisle zone resets
// it (the aisle's sub-steps are the legal way between rows). Arriving on a higher row than the last one is a riser climb
// (0.55 m per row), however many steps it took; it records the steps since the agent last stood on the lower row and
// the largest single-step floor rise in between (a climb in steps smaller than a per-step limit would show there),
// and how many of its steps rose onto a wall-steep floor (steepUp: the caller's flag, a rise ending on n_z <=
// WALL_MAX_NZ).
struct ClimbEvent { int agent, fromRow, toRow, steps; float maxStepRise; int steepUpSteps; };
struct ClimbTracker {
    std::vector<int> lastRow, lastRowStep, steepUp;
    std::vector<float> maxRise;
    explicit ClimbTracker(size_t n = 0) : lastRow(n, NO_ROW), lastRowStep(n, 0), steepUp(n, 0), maxRise(n, 0.0f) {}
    // One agent after a step: its floor class, this step's floor rise and whether it rose onto a wall-steep floor.
    // Returns true and fills e on a climb.
    bool update(int agent, int step, const FloorClass& f, float rise, bool steepUpStep, ClimbEvent& e) {
        const size_t i = size_t(agent);
        if (!std::isnan(rise)) maxRise[i] = std::max(maxRise[i], rise);
        steepUp[i] += steepUpStep;
        if (f.zone == metrics::ZONE_AISLE) { lastRow[i] = NO_ROW; return false; }
        if (f.row == NO_ROW) return false;   // between rows: the climb (or fall) is not over
        bool climbed = false;
        if (lastRow[i] != NO_ROW && f.row > lastRow[i]) {
            e = { agent, lastRow[i], f.row, step - lastRowStep[i], maxRise[i], steepUp[i] };
            climbed = true;
        }
        lastRow[i] = f.row;
        lastRowStep[i] = step;
        maxRise[i] = 0.0f;
        steepUp[i] = 0;
        return climbed;
    }
};

// --- The step-up invariants over a run (test_gpu physics.step_up_limit) ---
// Per active agent and step: the floor rise (floorUnder after - before; a rise above MAX_STEP_UP + RISE_CHECK_TOL
// violates the limit), riser climbs (ClimbTracker, the platform behind tread 7 included as row 8), wall tops, fence
// midline crossings (against the spawn side), and the rear platform: agent-steps on it and arrivals from the aisle zone
// (up the aisle's sub-steps, which the limit allows) or from the tread zone (over the riser: a climb). Every
// overlapEvery-th step (0: never) the overlap depth of every pair closer than BODY_DIAM (3D), / BODY_DIAM, above 1e-4, into
// a histogram of OVERLAP_BINS bins over [0, 1] (percentiles to 1/OVERLAP_BINS; at N = 65536 the depths of a run do not fit
// in memory).
// RISE_CHECK_TOL: floorUnder's own resolution for an agent within GROUNDED_TOL of its rest height
constexpr float RISE_CHECK_TOL = GROUNDED_TOL;
struct RunCheck {
    float wallDep;
    std::vector<float> floorPrev;
    std::vector<FloorClass> classPrev;
    std::vector<char> spawnSide;
    ClimbTracker climbs;
    int overlapEvery;
    long agentSteps = 0, risesAbove = 0, climbCount = 0, wallTopAgentSteps = 0, fenceCrossings = 0;
    long platformAgentSteps = 0, platformFromAisle = 0, platformFromTread = 0, airborneAgentSteps = 0;
    float maxRise = 0.0f;
    std::vector<ClimbEvent> climbEvents;   // the first MAX_EVENTS
    static constexpr int OVERLAP_BINS = 2000;
    std::vector<long long> overlapHist = std::vector<long long>(OVERLAP_BINS + 1, 0);   // sampled steps only; the last bin: depth >= 1
    long long overlapPairs = 0;
    float overlapMax = 0.0f;
    int overlapSteps = 0;
    static constexpr size_t MAX_EVENTS = 20;
    // Nearest-rank percentile of the sampled overlap depths, to the upper edge of its bin
    float overlapPercentile(double p) const {
        if (overlapPairs == 0) return 0.0f;
        const long long rank = std::max<long long>(1, (long long)std::ceil(p * double(overlapPairs)));
        long long acc = 0;
        for (int b = 0; b <= OVERLAP_BINS; ++b)
            if ((acc += overlapHist[size_t(b)]) >= rank) return std::min(overlapMax, float(b + 1) / float(OVERLAP_BINS));
        return overlapMax;
    }

    static bool fenceOutside(glm::vec2 p) {
        return sdBox2(p - glm::vec2(FENCE_CENTER.x, FENCE_CENTER.y), glm::vec2(FENCE_HALF_MID.x, FENCE_HALF_MID.y)) > 0.0f;
    }

    RunCheck(const std::vector<GpuBoid>& spawn, float outerWallInnerDepth, int overlapEveryK = 0)
        : wallDep(outerWallInnerDepth), floorPrev(spawn.size()), classPrev(spawn.size()), spawnSide(spawn.size()), climbs(spawn.size()),
          overlapEvery(overlapEveryK) {
        for (size_t i = 0; i < spawn.size(); ++i) {
            const glm::vec3 c(spawn[i].position);
            floorPrev[i] = floorUnder(c);
            classPrev[i] = classify(glm::vec2(c), floorPrev[i], wallDep);
            spawnSide[i] = fenceOutside(glm::vec2(c));
            ClimbEvent e;
            climbs.update(int(i), 0, classPrev[i], 0.0f, false, e);
        }
    }

    void step(int s, const std::vector<GpuBoid>& cur) {
        const int n = int(cur.size());
        std::vector<float> floorCur(cur.size(), std::numeric_limits<float>::quiet_NaN());
        std::vector<FloorClass> classCur(cur.size());
        std::vector<char> grounded(cur.size(), 1);
#pragma omp parallel for schedule(dynamic, 256)
        for (int i = 0; i < n; ++i) {
            if (cur[size_t(i)].position.w == 0.0f) continue;
            bool g = false;
            const glm::vec3 c(cur[size_t(i)].position);
            floorCur[size_t(i)] = floorUnder(c, &g);
            grounded[size_t(i)] = g;
            classCur[size_t(i)] = classify(glm::vec2(c), floorCur[size_t(i)], wallDep);
        }
        for (int i = 0; i < n; ++i) {
            const GpuBoid& b = cur[size_t(i)];
            if (b.position.w == 0.0f) continue;
            ++agentSteps;
            airborneAgentSteps += !grounded[size_t(i)];
            const float rise = floorCur[size_t(i)] - floorPrev[size_t(i)];
            if (!std::isnan(rise)) {
                maxRise = std::max(maxRise, rise);
                risesAbove += rise > MAX_STEP_UP + RISE_CHECK_TOL;
            }
            const FloorClass& c2 = classCur[size_t(i)];
            const FloorClass& c0 = classPrev[size_t(i)];
            ClimbEvent e;
            if (climbs.update(i, s, c2, rise, false, e)) {
                ++climbCount;
                if (climbEvents.size() < MAX_EVENTS) climbEvents.push_back(e);
            }
            wallTopAgentSteps += c2.wallTop;
            if (c2.platform()) {
                ++platformAgentSteps;
                if (!c0.platform()) (c0.zone == metrics::ZONE_AISLE ? platformFromAisle : platformFromTread)++;
            }
            fenceCrossings += fenceOutside(glm::vec2(b.position)) != (spawnSide[size_t(i)] != 0);
        }
        if (overlapEvery > 0 && s % overlapEvery == 0) sampleOverlaps(cur);
        floorPrev.swap(floorCur);
        classPrev.swap(classCur);
    }

    void sampleOverlaps(const std::vector<GpuBoid>& cur) {
        ++overlapSteps;
        const float cell = DOMAIN_SPAN / float(GRID_RES);
        auto cellOf = [&](glm::vec2 p) {
            const int x = std::clamp(int((p.x - DOMAIN_MIN) / cell), 0, GRID_RES - 1), y = std::clamp(int((p.y - DOMAIN_MIN) / cell), 0, GRID_RES - 1);
            return x + y * GRID_RES;
        };
        std::vector<std::vector<int>> cells(size_t(GRID_RES) * GRID_RES);
        for (size_t i = 0; i < cur.size(); ++i)
            if (cur[i].position.w != 0.0f) cells[size_t(cellOf(glm::vec2(cur[i].position)))].push_back(int(i));
        std::vector<std::vector<long long>> hist(cells.size());
        std::vector<float> cellMax(cells.size(), 0.0f);
#pragma omp parallel for schedule(dynamic, 4)
        for (int c = 0; c < GRID_RES * GRID_RES; ++c) {
            if (cells[size_t(c)].empty()) continue;
            hist[size_t(c)].assign(OVERLAP_BINS + 1, 0);
            const int cx = c % GRID_RES, cy = c / GRID_RES;
            for (int i : cells[size_t(c)])
                for (int y = std::max(cy - 1, 0); y <= std::min(cy + 1, GRID_RES - 1); ++y)
                    for (int x = std::max(cx - 1, 0); x <= std::min(cx + 1, GRID_RES - 1); ++x)
                        for (int j : cells[size_t(x + y * GRID_RES)]) {
                            if (j <= i) continue;
                            const float d = glm::length(glm::vec3(cur[size_t(i)].position) - glm::vec3(cur[size_t(j)].position));
                            const float depth = (BODY_DIAM - d) / BODY_DIAM;
                            if (depth <= 1e-4f) continue;
                            ++hist[size_t(c)][size_t(std::min(int(depth * float(OVERLAP_BINS)), OVERLAP_BINS))];
                            cellMax[size_t(c)] = std::max(cellMax[size_t(c)], depth);
                        }
        }
        for (size_t c = 0; c < cells.size(); ++c) {
            if (hist[c].empty()) continue;
            for (int b = 0; b <= OVERLAP_BINS; ++b) { overlapHist[size_t(b)] += hist[c][size_t(b)]; overlapPairs += hist[c][size_t(b)]; }
            overlapMax = std::max(overlapMax, cellMax[c]);
        }
    }
};

} // namespace swarm::stepup
