#pragma once

// Forced-motion validation of a seated venue, test and tool code only (readbacks every step): test_gpu's
// venue S sections and venue_probe's scenario runs. The router is bypassed as in the FD harness: the TEST_DRIVE_TABLE variant
// of physics.comp reads every agent's desired direction e_goal from a table that the scenario writes before every step, from
// the state the step starts from (the CPU reference: CpuCrowdSim::setDriveTable). Directions are fields of the venue's cells
// (where an agent is: clearway, gangway, walkway, ...) and of a per-agent plan.
// Checks per step (Checker): row changes (an agent seated in row k on another row's clearway), agents off their row, walls
// (horizontal clearance, plausibility's ring test), tunnelling (the step's straight path through a solid column: seat block,
// barrier, wall), the step-up rules (a floor rise above MAX_STEP_UP; a climb over a vertical face: a discontinuous rise of
// the floor along the path), fence crossings, front-row agents on the walkway, places and arrivals.

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <swarm/cpu_crowd_sim.hpp>
#include <swarm/crowd_sim.hpp>
#include <swarm/gpu_types.hpp>
#include <swarm/metrics.hpp>
#include <swarm/sdf.hpp>
#include <swarm/sim_params.hpp>
#include <swarm/venue.hpp>

#include "plausibility.hpp"
#include <swarm/assets.hpp>
#include "scene.hpp"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <functional>
#include <sstream>
#include <string>
#include <vector>

namespace swarm::venue_s {

namespace fs = std::filesystem;

// Copy of the shader directory with '#define TEST_DRIVE_TABLE' in physics.comp (after the preamble: the variant line follows
// #version, the loader inserts the preamble before it)
inline fs::path driveVariant(const fs::path& shaderDir, const std::string& name = "venue_drive") {
    const fs::path dir = processTempPath("swarm_shaders_" + name);
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
    src.insert(src.find('\n') + 1, "#define TEST_DRIVE_TABLE\n");
    std::ofstream(dir / "physics.comp", std::ios::binary | std::ios::trunc) << src;
    return dir;
}

// --- Where an agent is ---
enum Place { P_CLEARWAY, P_GANGWAY, P_CORNER, P_WALKWAY, P_AVENUE, P_CONCOURSE, P_EXIT, P_SOLID, P_OTHER, P_LEFT, P_COUNT };
inline const char* placeName(int p) {
    static const char* n[P_COUNT] = { "clearway", "straight gangway", "corner gangway", "walkway", "avenue", "concourse", "exit", "solid", "other", "left" };
    return p >= 0 && p < P_COUNT ? n[p] : "?";
}
struct Where { Place place; int row; glm::vec2 f; };
inline Where where(const SeatedLayout& L, const glm::vec4& pos) {
    if (pos.w == 0.0f) return { P_LEFT, -1, glm::vec2(0.0f) };
    const glm::vec2 xy(pos), f = seated::fold(xy);
    if (f.y < L.standFront) return { P_WALKWAY, -1, f };
    if (f.x < L.avenueHalf) return { P_AVENUE, -1, f };
    int row = -1, band = 0;
    const int kind = seated::cellAt(L, xy, &row, &band);
    switch (kind) {
    case seated::TREAD: return { P_CLEARWAY, row, f };
    // straight or corner by seated::gangwayAt (venue S: the same as lat <= gangwayHi + seatInset)
    case seated::INCLINE: return { seated::gangwayAt(L, xy) % L.gangwaysPerQuadrant() < 2 * L.gangways ? P_GANGWAY : P_CORNER, -1, f };
    case seated::GROUND:   // the barrier's gaps
        return { band == 1 ? (seated::gangwayAt(L, xy) % L.gangwaysPerQuadrant() < 2 * L.gangways ? P_GANGWAY : P_CORNER) : P_OTHER, -1, f };
    case seated::CONC: return { band == seated::bandCount(L) - 4 ? P_CONCOURSE : P_EXIT, -1, f };
    default: return { P_SOLID, -1, f };
    }
}

// --- Plans and drive fields ---
enum Mode {
    M_CONST,        // the plane direction 'dir' throughout
    M_EGRESS_DOWN,  // along the row (folded lat direction 'rowSign') to a gangway, down it, along the walkway to the nearer
                    // avenue, out through it
    M_GANGWAY,      // down (dirSign -1) or up (+1) the gangway it stands on to the walkway (down) or the concourse (up), then on
                    // out of the way: down along the walkway and out through the nearer avenue, up through the concourse exit
    M_RING,         // around the quadrant's ring (clockwise from above for ringSign +1) until it reaches the next wing's
                    // arrival lateral 'arriveLat' (the other avenue's mouth, the other side wall); then out through the avenue
                    // (walkway) or stops (concourse)
    M_STOP,
};
struct Plan {
    Mode mode = M_STOP;
    glm::vec2 dir{ 0.0f };
    float rowSign = 0.0f;
    float dirSign = -1.0f;
    float ringSign = 1.0f;
    int row = -1;               // M_EGRESS_DOWN: the agent's own row (another row's clearway: a stray from a gangway)
    int startWingAxis = 1;      // M_RING: the plane axis (0 x, 1 y) that is the start wing's depth axis
    float arriveLat = 0.0f;     // M_RING: arrived once |coordinate of the start wing's depth axis| < arriveLat
};

inline glm::vec2 planeDir(glm::vec2 xy, glm::vec2 folded) {
    const glm::vec2 d = seated::unfoldDir(xy, folded);
    const float l = glm::length(d);
    return l > 0.0f ? d / l : glm::vec2(0.0f);
}

// Along a gangway (sign -1 down, +1 up), steering towards its middle as a walker does: a straight gangway's centre line, a
// corner gangway's valley (the diagonal). Without the steering an agent that enters at a gangway's edge walks straight into
// the end of the seat block below (its wall normal opposite the drive: no slide) and stops, blocking the gangway.
// The straight gangway whose centre line is nearest to the folded lateral x (venue S: gangway 0)
inline int nearestStraight(const SeatedLayout& L, float x) {
    int best = 0;
    float bd = 1e30f;
    for (int i = 0; i < L.gangways; ++i) {
        const float d = std::abs(x - 0.5f * (L.gwLo[size_t(i)] + L.gwHi[size_t(i)]));
        if (d < bd) { bd = d; best = i; }
    }
    return best;
}
inline glm::vec2 straightDir(const SeatedLayout& L, glm::vec2 f, float sign) {
    const int i = nearestStraight(L, f.x);
    const float centre = 0.5f * (L.gwLo[size_t(i)] + L.gwHi[size_t(i)]), half = 0.5f * (L.gwHi[size_t(i)] - L.gwLo[size_t(i)]);
    return glm::vec2(0.5f * std::clamp((centre - f.x) / half, -1.0f, 1.0f), sign);
}
// The seat segment of row 'row' around the folded lateral x: its low edge a (the side wall's face, or the gangway below's
// high edge) and high edge b (the next gangway's low edge, or the clearway's end at the corner gangway); segment 0: the dead end
inline int segmentAround(const SeatedLayout& L, int row, float x, float& a, float& b) {
    const int n = L.activeGangways(row);
    const float end = L.row0 + float(row) * L.rowDepth - L.cornerInset;   // the clearway's end at the corner gangway
    int seg = 0;
    while (seg < n && x >= L.gwLo[size_t(seg)]) ++seg;
    a = seg == 0 ? L.lat0 : L.gwHi[size_t(seg - 1)];
    b = seg < n ? L.gwLo[size_t(seg)] : end;
    return seg;
}
inline glm::vec2 cornerDir(const SeatedLayout& L, glm::vec2 f, float sign) {
    // along the diagonal (sign, sign), plus (1, -1) per cornerInset of distance from it (dep - lat > 0 in the folded frame)
    const float k = (f.y - f.x) / L.cornerInset;
    // Generated venues (several straight gangways): where a straight gangway merges with the corner gangway the incline
    // reaches up to ~15 m from the diagonal; an uncapped pull drives whole streams sideways onto the diagonal from both wings and
    // deadlocks two agents in L's junction scenario. Capped like straightDir's steering (venue S unchanged:
    // its corner gangway is at most cornerInset wide, k <= ~1, and its forced pins stay)
    if (L.gangways > 1) return glm::vec2(sign, sign) + glm::vec2(1.0f, -1.0f) * std::min(k, 1.0f);
    return glm::vec2(sign, sign) + glm::vec2(1.0f, -1.0f) * k;
}

// Back to the nearer gangway from a clearway end it strayed onto (sign -1 down, +1 up): a gangway agent walking along a
// gangway's edge steps onto a row's clearway where the tread lies less than STEP_UP_SAMPLE above the incline (the clearway's
// back edge). Lateral towards the nearer gangway edge, half as much along the gangway.
inline glm::vec2 strayDir(const SeatedLayout& L, glm::vec2 f, int row, float sign) {
    float a, b;
    const int seg = segmentAround(L, row, f.x, a, b);   // venue S: the dead end below the gangway, else between it and the corner
    const float lateral = seg == 0 ? 1.0f : (f.x - a <= b - f.x ? -1.0f : 1.0f);
    return glm::vec2(lateral, 0.5f * sign);
}

// Whether the plan's goal is reached (the agent then stops: M_STOP)
inline bool arrived(const SeatedLayout& L, const Plan& pl, const GpuBoid& b) {
    const Where w = where(L, b.position);
    switch (pl.mode) {
    case M_GANGWAY: return pl.dirSign < 0.0f ? w.place == P_WALKWAY : w.place == P_CONCOURSE;
    case M_RING: {
        const glm::vec2 a = glm::abs(glm::vec2(b.position));
        const float startDepth = pl.startWingAxis == 1 ? a.y : a.x, otherDepth = pl.startWingAxis == 1 ? a.x : a.y;
        return otherDepth > startDepth && startDepth < pl.arriveLat;
    }
    default: return false;
    }
}

// Out of the venue from the walkway (along it to the nearer avenue, out through it) or the rear concourse (along it to the
// nearer concourse exit, out through it); zero elsewhere
inline glm::vec2 outDir(const SeatedLayout& L, const Where& w) {
    switch (w.place) {
    case P_WALKWAY: return w.f.x < L.avenueHalf - BODY_RADIUS ? glm::vec2(0.0f, 1.0f) : glm::vec2(-1.0f, 0.0f);
    case P_AVENUE: return glm::vec2(0.0f, 1.0f);
    case P_CONCOURSE: {   // the nearest door (venue S: its wing's one door)
        if (L.cornerDoorLo < 1e8f && w.f.x >= L.cornerDoorLo + BODY_RADIUS) return glm::vec2(0.0f, 1.0f);
        int best = 0;
        float bd = 1e30f;
        for (int i = 0; i < L.doors; ++i) {
            const float d = std::abs(w.f.x - 0.5f * (L.doorLo[size_t(i)] + L.doorHi[size_t(i)]));
            if (d < bd) { bd = d; best = i; }
        }
        const float mid = 0.5f * (L.doorLo[size_t(best)] + L.doorHi[size_t(best)]), half = 0.5f * (L.doorHi[size_t(best)] - L.doorLo[size_t(best)]) - BODY_RADIUS;
        if (L.cornerDoorLo < 1e8f && w.f.x > mid && w.f.x - mid > L.cornerDoorLo - w.f.x) return glm::vec2(1.0f, 0.0f);   // nearer the corner door
        if (std::abs(w.f.x - mid) <= half) return glm::vec2(0.0f, 1.0f);
        return glm::vec2(w.f.x < mid ? 1.0f : -1.0f, 0.0f);
    }
    case P_EXIT: return glm::vec2(0.0f, 1.0f);
    default: return glm::vec2(0.0f);
    }
}

inline glm::vec2 driveDir(const SeatedLayout& L, const Plan& pl, const GpuBoid& b) {
    if (b.position.w == 0.0f) return glm::vec2(0.0f);
    const glm::vec2 xy(b.position);
    const Where w = where(L, b.position);
    switch (pl.mode) {
    case M_CONST: return pl.dir;
    case M_EGRESS_DOWN:
        switch (w.place) {
        case P_CLEARWAY:
            if (pl.row >= 0 && w.row != pl.row) return planeDir(xy, strayDir(L, w.f, w.row, -1.0f));
            return planeDir(xy, glm::vec2(pl.rowSign, 0.0f));
        case P_GANGWAY: return planeDir(xy, straightDir(L, w.f, -1.0f));
        case P_CORNER: return planeDir(xy, cornerDir(L, w.f, -1.0f));
        case P_WALKWAY: case P_AVENUE: return planeDir(xy, outDir(L, w));
        default: return glm::vec2(0.0f);
        }
    case M_GANGWAY:
        if (pl.dirSign < 0.0f ? (w.place == P_WALKWAY || w.place == P_AVENUE) : (w.place == P_CONCOURSE || w.place == P_EXIT))
            return planeDir(xy, outDir(L, w));   // arrived: on out of the way
        if (w.place == P_CORNER) return planeDir(xy, cornerDir(L, w.f, pl.dirSign));
        if (w.place == P_GANGWAY) return planeDir(xy, straightDir(L, w.f, pl.dirSign));
        if (w.place == P_CLEARWAY) return planeDir(xy, strayDir(L, w.f, w.row, pl.dirSign));
        return planeDir(xy, glm::vec2(0.0f, pl.dirSign));
    case M_RING: {
        // arrived: on the walkway out through the avenue it reached (a file stopping in the avenue's mouth blocks the rest);
        // on the concourse it stops (beside the side wall, out of the ring's way)
        if (arrived(L, pl, b)) return w.place == P_WALKWAY || w.place == P_AVENUE ? planeDir(xy, outDir(L, w)) : glm::vec2(0.0f);
        const glm::vec2 a = glm::abs(xy);
        const glm::vec2 cw = a.y >= a.x ? glm::vec2(xy.y < 0.0f ? -1.0f : 1.0f, 0.0f) : glm::vec2(0.0f, xy.x < 0.0f ? 1.0f : -1.0f);
        return cw * pl.ringSign;
    }
    default: return glm::vec2(0.0f);
    }
}

inline void driveTable(const SeatedLayout& L, const std::vector<Plan>& plans, const std::vector<GpuBoid>& state, std::vector<glm::vec2>& out) {
    out.resize(state.size());
#pragma omp parallel for schedule(static)
    for (int i = 0; i < int(state.size()); ++i) out[size_t(i)] = i < int(plans.size()) ? driveDir(L, plans[size_t(i)], state[size_t(i)]) : glm::vec2(0.0f);
}

// --- Spawns ---
inline GpuBoid parked() {
    GpuBoid b;
    b.position = glm::vec4(PARK_COORD, PARK_COORD, PARK_COORD, 0.0f);
    b.velocity = glm::vec4(0.0f);
    return b;
}
inline GpuBoid restingAt(const SeatedLayout& L, glm::vec2 xy) {
    GpuBoid b;
    b.position = glm::vec4(xy, seated::floorHeight(L, xy) + BODY_RADIUS, 1.0f);
    b.velocity = glm::vec4(0.0f);
    return b;
}
inline int bufferSize(size_t agents) {
    int n = 256;
    while (size_t(n) < agents) n *= 2;
    return n;
}
// Folded (lat, dep) -> the plane point in quadrant q (0 (+x +y), 1 (-x +y), 2 (-x -y), 3 (+x -y)), wing w (0: depth |y|)
inline glm::vec2 unfoldPoint(glm::vec2 f, int q, int wing) {
    const float sx = (q == 1 || q == 2) ? -1.0f : 1.0f, sy = q >= 2 ? -1.0f : 1.0f;
    return wing == 0 ? glm::vec2(sx * f.x, sy * f.y) : glm::vec2(sx * f.y, sy * f.x);
}

// --- Per-step checks ---
struct Checker {
    const SeatedLayout* L = nullptr;
    std::vector<int> seatRow;          // the row each agent was seated in (-1: not seated)
    std::vector<char> spawnFenceOut;
    std::vector<int> enteredGangway;   // first step on a gangway (straight or corner), -1: never
    std::vector<int> arrivedStep;      // first step its plan's goal was reached / it left, -1: never
    std::vector<char> visitedWalkway;
    std::vector<int> lastRow;          // the row of the last clearway the agent stood on (-1: none yet)
    std::vector<char> viaAisle;        // since then on a gangway, the walkway, an avenue, the concourse or an exit
    // rowChanges: from one row's clearway to another's without an aisle in between (across a riser, a seat block or the
    // barrier: INV-row); rowEntries: onto another row's clearway from an aisle (not INV-row: the row is entered from its
    // aisle), strayRowSteps the agent-steps a seated agent spends on another row's clearway
    long rowEntries = 0, strayRowSteps = 0;
    long agentSteps = 0, rowChanges = 0, offRowSteps = 0, solidSteps = 0, tunnels = 0, risesAbove = 0, verticalClimbs = 0;
    // verticalClimbs: steps whose path climbs a vertical face (a discontinuous floor rise of any height) onto a floor above the
    // start-of-step floor (the step-up rule's climb); descentFaces: faces crossed upwards in a step that stays at or below its
    // start floor (it dipped first: 'level and downward moves are never blocked'), information only
    long descentFaces = 0, fenceCrossings = 0, wallViolations = 0, frontRowOnWalkway = 0, frontRowOnWalkwayViaGap = 0;
    float minWallClearance = 1e9f, maxRise = 0.0f, maxVerticalRise = 0.0f, maxDescentFace = 0.0f;
    long placeSteps[P_COUNT] = {};
    bool wallCheck = true;   // plausibility's ring test per agent and step (the costliest check)

    void init(const SeatedLayout& layout, const std::vector<GpuBoid>& spawn, const std::vector<int>& rows) {
        L = &layout;
        const size_t n = spawn.size();
        seatRow = rows;
        seatRow.resize(n, -1);
        spawnFenceOut.assign(n, 0);
        for (size_t i = 0; i < n; ++i) spawnFenceOut[i] = plausibility::detail::fenceSide(glm::vec2(spawn[i].position)) > 0.0f;
        enteredGangway.assign(n, -1);
        arrivedStep.assign(n, -1);
        visitedWalkway.assign(n, 0);
        lastRow.assign(n, -1);
        viaAisle.assign(n, 1);
        for (size_t i = 0; i < n; ++i)
            if (seatRow[i] >= 0) { lastRow[i] = seatRow[i]; viaAisle[i] = 0; }
    }

    // The floor along the step's straight horizontal path (every 2 mm): the largest discontinuous rise onto a floor above the
    // start floor (a vertical face climbed: vertRise) and at or below it (dipRise), and whether the path passes through a solid
    // column above the agent (seat block, barrier, wall)
    void path(const glm::vec4& p0, const glm::vec4& p1, float& vertRise, bool& tunnel, float* dipRise = nullptr) const {
        vertRise = 0.0f;
        if (dipRise) *dipRise = 0.0f;
        tunnel = false;
        const glm::vec2 a(p0), b(p1);
        const float len = glm::length(b - a);
        const float ds = 0.002f * float(units::modelLength(1.0));   // 2 mm
        const int ns = std::max(1, int(std::ceil(len / ds)));
        float hPrev = seated::floorHeight(*L, a);
        const float hStart = hPrev, zTop = std::max(p0.z, p1.z);
        for (int k = 1; k <= ns; ++k) {
            // a + (b - a) t, b at the end: exact on a path along a cell boundary (glm::mix's a (1 - t) + b t rounds across it)
            const glm::vec2 q = k == ns ? b : a + (b - a) * (float(k) / float(ns));
            const float h = seated::floorHeight(*L, q);
            const float cont = L->rake * (len / float(ns)) + 1e-5f;   // the steepest continuous rise over one sample (the incline)
            if (h - hPrev > cont) {
                if (h > hStart + STEP_UP_TOL) vertRise = std::max(vertRise, h - hPrev);
                else if (dipRise) *dipRise = std::max(*dipRise, h - hPrev);
            }
            const int kind = seated::cellAt(*L, q);
            if ((kind == seated::SEAT || kind == seated::BARRIER || kind == seated::WALL || kind == seated::SIDE) && h > zTop) tunnel = true;
            hPrev = h;
        }
    }

    void step(int s, const std::vector<GpuBoid>& prev, const std::vector<GpuBoid>& cur, const std::vector<Plan>* plans = nullptr) {
        const int n = int(cur.size());
        std::vector<float> wall(size_t(n), 1e9f), vrise(size_t(n), 0.0f), drise(size_t(n), 0.0f);
        std::vector<char> tun(size_t(n), 0);
#pragma omp parallel for schedule(dynamic, 64)
        for (int i = 0; i < n; ++i) {
            if (cur[size_t(i)].position.w == 0.0f || prev[size_t(i)].position.w == 0.0f) continue;
            bool slope = false;
            if (wallCheck) wall[size_t(i)] = plausibility::detail::wallClearance(glm::vec3(cur[size_t(i)].position), slope);
            bool t = false;
            path(prev[size_t(i)].position, cur[size_t(i)].position, vrise[size_t(i)], t, &drise[size_t(i)]);
            tun[size_t(i)] = t;
        }
        for (int i = 0; i < n; ++i) {
            const GpuBoid& b = cur[size_t(i)];
            if (b.position.w == 0.0f) {
                if (prev[size_t(i)].position.w != 0.0f && arrivedStep[size_t(i)] < 0) arrivedStep[size_t(i)] = s;   // left the venue
                continue;
            }
            ++agentSteps;
            const Where w = where(*L, b.position);
            ++placeSteps[w.place];
            if (w.place == P_SOLID) ++solidSteps;
            const int seat = seatRow[size_t(i)];
            if (w.place == P_CLEARWAY) {
                if (lastRow[size_t(i)] >= 0 && w.row != lastRow[size_t(i)]) (viaAisle[size_t(i)] ? rowEntries : rowChanges)++;
                lastRow[size_t(i)] = w.row;
                viaAisle[size_t(i)] = 0;
                if (seat >= 0 && w.row != seat) ++strayRowSteps;
            } else if (w.place != P_SOLID && w.place != P_OTHER) viaAisle[size_t(i)] = 1;
            if (seat >= 0 && !(w.place == P_CLEARWAY && w.row == seat)) ++offRowSteps;
            if ((w.place == P_GANGWAY || w.place == P_CORNER) && enteredGangway[size_t(i)] < 0) enteredGangway[size_t(i)] = s;
            if (w.place == P_WALKWAY && !visitedWalkway[size_t(i)]) {
                visitedWalkway[size_t(i)] = 1;
                if (seat == 0) { ++frontRowOnWalkway; if (enteredGangway[size_t(i)] >= 0) ++frontRowOnWalkwayViaGap; }
            }
            if (plans && arrivedStep[size_t(i)] < 0 && arrived(*L, (*plans)[size_t(i)], b)) arrivedStep[size_t(i)] = s;
            const float rise = seated::floorHeight(*L, glm::vec2(b.position)) - seated::floorHeight(*L, glm::vec2(prev[size_t(i)].position));
            maxRise = std::max(maxRise, rise);
            if (rise > MAX_STEP_UP + plausibility::FLOOR_TOL) ++risesAbove;
            if (vrise[size_t(i)] > 0.0f) {
                maxVerticalRise = std::max(maxVerticalRise, vrise[size_t(i)]);
                ++verticalClimbs;
            }
            if (drise[size_t(i)] > 0.0f) {
                maxDescentFace = std::max(maxDescentFace, drise[size_t(i)]);
                ++descentFaces;
            }
            tunnels += tun[size_t(i)];
            fenceCrossings += (plausibility::detail::fenceSide(glm::vec2(b.position)) > 0.0f) != (spawnFenceOut[size_t(i)] != 0);
            if (wallCheck) {
                minWallClearance = std::min(minWallClearance, wall[size_t(i)]);
                if (wall[size_t(i)] < BODY_RADIUS - plausibility::WALL_TOL) ++wallViolations;
            }
        }
    }
};

// --- Engines: the GPU pipeline (the TEST_DRIVE_TABLE variant) or the CPU reference, both on the venue ---
struct GpuEngine {
    CrowdSim sim;
    GLuint drive = 0;
    // The forced scenarios run the nearest-exit, level-speed model (ModelOptions{}: the exit is unused under the drive table) unless
    // options are given, whatever the venue's defaults, so their pins (GOLDEN_S_FORCED) do not move with the defaults
    GpuEngine(const fs::path& variantDir, int n, const Venue& v, const ModelOptions& options = {}) : sim(variantDir, n, v, options) {
        glGenBuffers(1, &drive);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, drive);
        glBufferData(GL_SHADER_STORAGE_BUFFER, GLsizeiptr(size_t(n) * sizeof(glm::vec2)), nullptr, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
        sim.setDriveBuffer(drive);
    }
    ~GpuEngine() { glDeleteBuffers(1, &drive); }
    void upload(const std::vector<GpuBoid>& s) { sim.upload(s); }
    void setDrive(const std::vector<glm::vec2>& d) {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, drive);
        glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, GLsizeiptr(d.size() * sizeof(glm::vec2)), d.data());
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }
    void step() { sim.step(0); }
    std::vector<GpuBoid> state() const {
        glMemoryBarrier(GL_BUFFER_UPDATE_BARRIER_BIT);
        std::vector<GpuBoid> out(size_t(sim.numBoids()));
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, sim.currentStateBuffer());
        glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, GLsizeiptr(out.size() * sizeof(GpuBoid)), out.data());
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
        return out;
    }
};

struct CpuEngine {
    CpuCrowdSim sim;
    std::vector<glm::vec2> table;
    CpuEngine(const Venue& v, int threads, CpuCrowdSim::SortMode mode, const ModelOptions& options = {}) : sim(v, options, {}, threads, mode) {}
    void upload(const std::vector<GpuBoid>& s) { sim.setState(s); table.assign(s.size(), glm::vec2(0.0f)); sim.setDriveTable(&table); }
    void setDrive(const std::vector<glm::vec2>& d) { table = d; }
    void step() { sim.step(); }
    std::vector<GpuBoid> state() const { return sim.state(); }
};

struct RunResult {
    int steps = 0, evacStep = -1;
    Checker checks;
    std::vector<GpuBoid> finalState;
    uint64_t trajectoryHash = 0xcbf29ce484222325ull;   // plausibility::chainHash over every step's state
};

// Runs 'steps' steps (or until nobody is active, stopWhenEmpty), the drive table from the plans before every step, the
// checks after it; onStep(step, state) after the checks (optional)
template <class Engine>
RunResult run(Engine& e, const SeatedLayout& L, const std::vector<GpuBoid>& spawn, const std::vector<Plan>& plans, const std::vector<int>& seatRows,
              int steps, bool stopWhenEmpty, bool wallCheck = true, const std::function<void(int, const std::vector<GpuBoid>&)>& onStep = nullptr) {
    RunResult r;
    r.checks.wallCheck = wallCheck;
    r.checks.init(L, spawn, seatRows);
    e.upload(spawn);
    std::vector<GpuBoid> prev = spawn;
    std::vector<glm::vec2> table;
    for (int s = 1; s <= steps; ++s) {
        driveTable(L, plans, prev, table);
        e.setDrive(table);
        e.step();
        std::vector<GpuBoid> cur = e.state();
        r.checks.step(s, prev, cur, &plans);
        plausibility::chainHash(r.trajectoryHash, cur);
        if (onStep) onStep(s, cur);
        r.steps = s;
        long active = 0;
        for (const GpuBoid& b : cur) active += b.position.w != 0.0f;
        prev.swap(cur);
        if (active == 0) { r.evacStep = s; if (stopWhenEmpty) break; }
    }
    r.finalState = prev;
    return r;
}

// The seats of a spawn (seatedSpawnSeats) -> each agent's row (-1: parked)
inline std::vector<int> seatRows(const Venue& v, const std::vector<int>& seatIndex) {
    const std::vector<seated::Seat> all = seated::seats(v.layout);
    std::vector<int> rows(seatIndex.size(), -1);
    for (size_t i = 0; i < seatIndex.size(); ++i)
        if (seatIndex[i] >= 0) rows[i] = all[size_t(seatIndex[i])].row;
    return rows;
}

// The dense scenario's plan for a seated agent: along its row to the nearer gangway (the dead-end segment: the straight
// gangway), down it, along the walkway, out through the nearer avenue
inline Plan egressPlan(const SeatedLayout& L, const seated::Seat& s) {
    Plan p;
    p.mode = M_EGRESS_DOWN;
    p.row = s.row;
    if (s.segment == 0) p.rowSign = 1.0f;
    else {   // the nearer of the segment's two gangways (straight gangway segment - 1 below, the next one or the corner above)
        float a, b;
        segmentAround(L, s.row, s.lat, a, b);
        p.rowSign = (s.lat - a) <= (b - s.lat) ? -1.0f : 1.0f;
    }
    return p;
}

// --- Scenario setups (agents in seat order or by place; padded to a power of two >= 256 with parked agents) ---
struct Setup {
    std::vector<GpuBoid> boids;
    std::vector<Plan> plans;   // per agent (parked: M_STOP)
    std::vector<int> rows;     // the seat row per agent (-1: not seated)
    std::vector<int> group;    // a scenario-defined group per agent (-1: parked)
    int active = 0;
    void add(const GpuBoid& b, const Plan& p, int row, int g) {
        boids.push_back(b);
        plans.push_back(p);
        rows.push_back(row);
        group.push_back(g);
        ++active;
    }
    void pad() {
        const size_t n = size_t(bufferSize(boids.size()));
        boids.resize(n, parked());
        plans.resize(n);
        rows.resize(n, -1);
        group.resize(n, -1);
    }
};

// The seated agents of every kept seat, at the seat's spawn (seated::seats), each with plan(seat), in group(seat)
inline Setup seatSetup(const SeatedLayout& L, const std::function<bool(const seated::Seat&)>& keep,
                       const std::function<Plan(const seated::Seat&)>& plan, const std::function<int(const seated::Seat&)>& group) {
    Setup s;
    for (const seated::Seat& seat : seated::seats(L)) {
        if (keep && !keep(seat)) continue;
        GpuBoid b;
        b.position = glm::vec4(seat.pos, 1.0f);
        b.velocity = glm::vec4(0.0f);
        s.add(b, plan(seat), seat.row, group ? group(seat) : 0);
    }
    s.pad();
    return s;
}

// The plane direction along a seat's wing depth axis: sign -1 towards the pitch, +1 away from it
inline glm::vec2 depthDir(const seated::Seat& s, float sign) {
    return s.wing == 0 ? glm::vec2(0.0f, s.pos.y < 0.0f ? -sign : sign) : glm::vec2(s.pos.x < 0.0f ? -sign : sign, 0.0f);
}

// (c) Agents on every gangway, one per row band (mid-band, 0.8 m apart): the straight gangways on their centre line (groups
// (q * 2 + wing) * gangways + i; venue S: q * 2 + wing) and the 4 corner gangways on the diagonal (groups 8 gangways + q), driven
// down (-1) or up (+1). A straight gangway from the first row it exists in; rowKeep (optional) selects the row bands
inline int gangwayGroups(const SeatedLayout& L) { return 8 * L.gangways + 4; }
// Each gangway's floor area in m^2 (seated::gangwayAt sampled every 0.05 m over the domain: the incline and the barrier gap
// at its foot; a straight gangway merged with the corner gangway counts there): the flow analysis' gangway densities
inline std::vector<double> gangwayAreasM2(const SeatedLayout& L, float domainMin, float domainSpan) {
    std::vector<double> area(size_t(seated::gangwayCount(L)), 0.0);
    const float step = float(0.05 / units::M_PER_UNIT);
    const int n = int(domainSpan / step);
    const double cellM2 = 0.05 * 0.05;
    for (int iy = 0; iy < n; ++iy)
        for (int ix = 0; ix < n; ++ix) {
            const int g = seated::gangwayAt(L, glm::vec2(domainMin + (float(ix) + 0.5f) * step, domainMin + (float(iy) + 0.5f) * step));
            if (g >= 0) area[size_t(g)] += cellM2;
        }
    return area;
}
inline Setup gangwaySetup(const SeatedLayout& L, float dirSign, const std::function<bool(int)>& rowKeep = nullptr) {
    Setup s;
    Plan p;
    p.mode = M_GANGWAY;
    p.dirSign = dirSign;
    for (int q = 0; q < 4; ++q) {
        for (int wing = 0; wing < 2; ++wing)
            for (int i = 0; i < L.gangways; ++i) {
                const float centre = 0.5f * (L.gwLo[size_t(i)] + L.gwHi[size_t(i)]);
                for (int k = 0; k < L.rows; ++k) {
                    if (k < L.gwRow[size_t(i)] || (rowKeep && !rowKeep(k))) continue;
                    // a merged row: the straight gangway's footprint there is the corner gangway's (the agent starts on the corner gangway)
                    s.add(restingAt(L, unfoldPoint(glm::vec2(centre, L.row0 + (float(k) + 0.5f) * L.rowDepth), q, wing)), p, -1, (q * 2 + wing) * L.gangways + i);
                }
            }
        for (int k = 0; k < L.rows; ++k) {
            if (rowKeep && !rowKeep(k)) continue;
            const float d = L.row0 + (float(k) + 0.5f) * L.rowDepth;
            s.add(restingAt(L, unfoldPoint(glm::vec2(d, d), q, 0)), p, -1, 8 * L.gangways + q);
        }
    }
    s.pad();
    return s;
}

// (d) Passages. rings: per quadrant 8 agents on the walkway (groups 0-3: two files, from beside the avenue the clockwise ring
// leaves, to the next avenue's mouth) and 4 on the rear concourse (groups 4-7: from beside a side wall around the corner to
// within 1 m of the other side wall). exits: 4 agents per avenue mouth driven out through it (groups 8-11) and 2 in front of
// every concourse exit driven out through it (groups 12-19: q * 2 + wing)
inline Setup passageSetup(const SeatedLayout& L, bool rings) {
    Setup s;
    const float m = float(units::modelLength(1.0));
    for (int q = 0; q < 4; ++q) {
        const int startWing = q % 2;   // the clockwise ring leaves the avenue of this wing's depth axis
        Plan ring;
        ring.mode = M_RING;
        ring.ringSign = 1.0f;
        ring.startWingAxis = startWing == 0 ? 1 : 0;
        if (rings) {
            ring.arriveLat = L.avenueHalf;
            for (int file = 0; file < 2; ++file)
                for (int i = 0; i < 4; ++i) {
                    const float dep = file == 0 ? FENCE_HALF_OUTER + 0.7f * m : L.standFront - 0.7f * m;
                    s.add(restingAt(L, unfoldPoint(glm::vec2(L.avenueHalf + (0.5f + 0.8f * float(i)) * m, dep), q, startWing)), ring, -1, q);
                }
            ring.arriveLat = L.lat0 + 1.0f * m;
            for (int i = 0; i < 4; ++i)
                s.add(restingAt(L, unfoldPoint(glm::vec2(L.lat0 + (0.6f + 0.8f * float(i)) * m, 0.5f * (L.concFront + L.concBack)), q, startWing)), ring,
                      -1, 4 + q);
        } else {
            Plan out;
            out.mode = M_CONST;
            const glm::vec2 axisOut = q == 0 ? glm::vec2(0, 1) : q == 1 ? glm::vec2(-1, 0) : q == 2 ? glm::vec2(0, -1) : glm::vec2(1, 0);
            out.dir = axisOut;   // avenue q: +y, -x, -y, +x
            const glm::vec2 lat = glm::vec2(axisOut.y, axisOut.x);
            const float dep = 0.5f * (FENCE_HALF_OUTER + L.standFront);
            for (int i = 0; i < 4; ++i)
                s.add(restingAt(L, axisOut * dep + lat * ((float(i) - 1.5f) * 1.0f * m)), out, -1, 8 + q);
            // In front of every door (venue S: one per wing, groups 12 + q * 2 + wing), the corner door's on the diagonal
            for (int wing = 0; wing < 2; ++wing)
                for (int d = 0; d < L.doors; ++d) {
                    const float centre = 0.5f * (L.doorLo[size_t(d)] + L.doorHi[size_t(d)]);
                    for (int i = 0; i < 2; ++i) {
                        const glm::vec2 xy = unfoldPoint(glm::vec2(centre + (float(i) - 0.5f) * 0.5f * m, L.concBack - 1.0f * m), q, wing);
                        Plan e;
                        e.mode = M_CONST;
                        e.dir = planeDir(xy, glm::vec2(0.0f, 1.0f));
                        s.add(restingAt(L, xy), e, -1, 12 + q * L.doorsPerQuadrant() + wing * L.doors + d);
                    }
                }
            if (L.cornerDoorLo < 1e8f)
                for (int i = 0; i < 2; ++i) {
                    const float c = L.concBack - (1.0f + 0.5f * float(i)) * m;
                    const glm::vec2 xy = unfoldPoint(glm::vec2(c, c), q, 0);
                    Plan e;
                    e.mode = M_CONST;
                    e.dir = glm::normalize(glm::sign(xy));
                    s.add(restingAt(L, xy), e, -1, 12 + q * L.doorsPerQuadrant() + 2 * L.doors);
                }
        }
    }
    s.pad();
    return s;
}

// Per group: agents, arrivals (the plan's goal or leaving the venue), the last arrival step
struct GroupStats { int agents = 0, arrived = 0, lastStep = -1, firstStep = -1; std::vector<int> steps; };
inline std::vector<GroupStats> groupStats(const Setup& s, const std::vector<int>& stepOf, int groups) {
    std::vector<GroupStats> g(static_cast<size_t>(groups));
    for (size_t i = 0; i < s.group.size(); ++i) {
        if (s.group[i] < 0 || s.group[i] >= groups) continue;
        GroupStats& t = g[size_t(s.group[i])];
        ++t.agents;
        if (stepOf[i] >= 0) {
            ++t.arrived;
            t.steps.push_back(stepOf[i]);
            t.lastStep = std::max(t.lastStep, stepOf[i]);
            t.firstStep = t.firstStep < 0 ? stepOf[i] : std::min(t.firstStep, stepOf[i]);
        }
    }
    return g;
}

inline double seconds(int steps) { return double(steps) * DT_REAL_S; }

// --- The scenarios (a)-(f) on the GPU, (g) GPU against the CPU reference ---
// (a) INV-row: every seat occupied, every agent driven towards the pitch (then, from a fresh spawn, away from it) along its
// wing's depth axis at V0 for 'steps' steps
struct InvRow { Setup toward, away; RunResult runToward, runAway; };
// rowKeep (optional) selects the seat rows (a sample of a large venue's rows: in every wing)
using RowKeep = std::function<bool(int)>;
inline InvRow runInvRow(const fs::path& variant, const Venue& v, int steps, const RowKeep& rowKeep = nullptr) {
    const SeatedLayout& L = v.layout;
    InvRow r;
    for (int dir = 0; dir < 2; ++dir) {
        const float sign = dir == 0 ? -1.0f : 1.0f;
        Setup s = seatSetup(L, rowKeep ? std::function<bool(const seated::Seat&)>([&](const seated::Seat& seat) { return rowKeep(seat.row); }) : nullptr,
                            [&](const seated::Seat& seat) { Plan p; p.mode = M_CONST; p.dir = depthDir(seat, sign); return p; },
                            [](const seated::Seat& seat) { return seat.row; });
        GpuEngine e(variant, int(s.boids.size()), v);
        RunResult res = run(e, L, s.boids, s.plans, s.rows, steps, false);
        (dir == 0 ? r.toward : r.away) = std::move(s);
        (dir == 0 ? r.runToward : r.runAway) = std::move(res);
    }
    return r;
}

// (b) Junctions: in every row, the seated agents of one segment driven along the row towards one adjacent gangway (then down
// it and out along the walkway, so the junction clears): dead-end segment -> straight gangway, the other segment -> straight
// gangway, the other segment -> corner gangway (three runs). Group: the row. Entering: the first step on a gangway.
// "the other segment" is every segment after a straight gangway, driven to the gangway below it (-1) or the one above (+1: the next
// straight gangway, or the corner gangway).
struct Junction { const char* name; Setup setup; RunResult run; std::vector<GroupStats> perRow; };
inline std::vector<Junction> runJunctions(const fs::path& variant, const Venue& v, int steps, const RowKeep& rowKeep = nullptr) {
    const SeatedLayout& L = v.layout;
    std::vector<Junction> out;
    const struct { const char* name; int segment; float sign; } cases[] = {
        { "dead-end segment -> straight gangway", 0, 1.0f }, { "segment -> straight gangway", 1, -1.0f }, { "segment -> corner gangway", 1, 1.0f } };
    for (const auto& c : cases) {
        Junction j;
        j.name = c.name;
        j.setup = seatSetup(L, [&](const seated::Seat& s) { return (c.segment == 0 ? s.segment == 0 : s.segment >= 1) && (!rowKeep || rowKeep(s.row)); },
                            [&](const seated::Seat& seat) { Plan p; p.mode = M_EGRESS_DOWN; p.rowSign = c.sign; p.row = seat.row; return p; },
                            [](const seated::Seat& s) { return s.row; });
        GpuEngine e(variant, int(j.setup.boids.size()), v);
        j.run = run(e, L, j.setup.boids, j.setup.plans, j.setup.rows, steps, true);
        j.perRow = groupStats(j.setup, j.run.checks.enteredGangway, L.rows);
        out.push_back(std::move(j));
    }
    return out;
}

// (c) Gangways down and up (gangwaySetup); arrival: the walkway (down), the rear concourse (up)
struct Gangways { Setup down, up; RunResult runDown, runUp; std::vector<GroupStats> statsDown, statsUp; };
inline Gangways runGangways(const fs::path& variant, const Venue& v, int steps, const RowKeep& rowKeep = nullptr) {
    const SeatedLayout& L = v.layout;
    Gangways g;
    g.down = gangwaySetup(L, -1.0f, rowKeep);
    g.up = gangwaySetup(L, 1.0f, rowKeep);
    {
        GpuEngine e(variant, int(g.down.boids.size()), v);
        g.runDown = run(e, L, g.down.boids, g.down.plans, g.down.rows, steps, false);
    }
    {
        GpuEngine e(variant, int(g.up.boids.size()), v);
        g.runUp = run(e, L, g.up.boids, g.up.plans, g.up.rows, steps, false);
    }
    g.statsDown = groupStats(g.down, g.runDown.checks.arrivedStep, gangwayGroups(L));
    g.statsUp = groupStats(g.up, g.runUp.checks.arrivedStep, gangwayGroups(L));
    return g;
}

// (d) Passages: the walkway and concourse rings, then the avenue and concourse exits (passageSetup)
struct Passages { Setup rings, exits; RunResult runRings, runExits; std::vector<GroupStats> statsRings, statsExits; };
inline Passages runPassages(const fs::path& variant, const Venue& v, int steps) {
    const SeatedLayout& L = v.layout;
    Passages p;
    p.rings = passageSetup(L, true);
    p.exits = passageSetup(L, false);
    {
        GpuEngine e(variant, int(p.rings.boids.size()), v);
        p.runRings = run(e, L, p.rings.boids, p.rings.plans, p.rings.rows, steps, false);
    }
    {
        GpuEngine e(variant, int(p.exits.boids.size()), v);
        p.runExits = run(e, L, p.exits.boids, p.exits.plans, p.exits.rows, steps, true);
    }
    p.statsRings = groupStats(p.rings, p.runRings.checks.arrivedStep, 8);
    p.statsExits = groupStats(p.exits, p.runExits.checks.arrivedStep, 12 + 4 * L.doorsPerQuadrant());
    return p;
}

// (e) The dense forced scenario: every seat occupied, each agent along its row to the nearer gangway (egressPlan), down it,
// along the walkway, out through the nearer avenue; plausibility's checks after every step, analytic venue (no exemption),
// with the metrics (S's cell table); the Checker's checks on every step too
inline Setup denseSetup(const SeatedLayout& L) {
    return seatSetup(L, nullptr, [&](const seated::Seat& s) { return egressPlan(L, s); }, [](const seated::Seat& s) { return s.row; });
}
struct Dense { Setup setup; plausibility::Result plaus; Checker checks; uint64_t goldenHash = 0; };
inline Dense runDense(const fs::path& variant, const fs::path& shaderDir, const Venue& v, int maxSteps, int goldenSteps) {
    const SeatedLayout& L = v.layout;
    Dense d;
    d.setup = denseSetup(L);
    const int n = int(d.setup.boids.size());
    GpuEngine e(variant, n, v);
    e.upload(d.setup.boids);
    const std::vector<GpuMetricCellInfo> info = metrics::computeMetricVenue(v).cellInfo();
    metrics::CrowdMetrics gm(shaderDir, n, info, &v);
    d.checks.init(L, d.setup.boids, d.setup.rows);
    std::vector<GpuBoid> before = d.setup.boids;
    std::vector<glm::vec2> table;
    const scene::Select sel(v);
    d.plaus = plausibility::runEvacuation(e.sim, 0, d.setup.boids, gm, info, maxSteps, plausibility::VenueKind::Analytic,
        [&](int s, const std::vector<GpuBoid>& state) {
            if (s > 1) d.checks.step(s - 1, before, state, &d.setup.plans);   // the previous step's move
            if (s - 1 == goldenSteps) {   // the state after goldenSteps steps: FNV-1a 64 of its raw bytes (golden::stateHash)
                d.goldenHash = 0xcbf29ce484222325ull;
                plausibility::chainHash(d.goldenHash, state);
            }
            before = state;
            driveTable(L, d.setup.plans, state, table);
            e.setDrive(table);
        });
    const std::vector<GpuBoid> last = e.state();
    d.checks.step(d.plaus.steps, before, last, &d.setup.plans);
    return d;
}

// (g) Equivalence: one step from the same state on the GPU and the CPU (both sort modes) with the same drive table
struct OneStep { std::vector<GpuBoid> in, gpu, cpu[2]; std::vector<GpuGridInfo> gpuGrid, cpuGrid[2]; std::vector<GpuCellData> gpuCells, cpuCells[2]; };
inline OneStep oneStep(const fs::path& variant, const Venue& v, const std::vector<GpuBoid>& in, const std::vector<Plan>& plans) {
    OneStep o;
    o.in = in;
    std::vector<glm::vec2> table;
    driveTable(v.layout, plans, in, table);
    {
        GpuEngine e(variant, int(in.size()), v);
        e.upload(in);
        e.setDrive(table);
        e.step();
        o.gpu = e.state();
        o.gpuGrid = plausibility::detail::read<GpuGridInfo>(e.sim.gridBuffer(), in.size());
        o.gpuCells = plausibility::detail::read<GpuCellData>(e.sim.cellBuffer(), size_t(v.gridRes) * v.gridRes);
    }
    for (int m = 0; m < 2; ++m) {
        CpuEngine c(v, 0, m == 0 ? CpuCrowdSim::SortMode::Counting : CpuCrowdSim::SortMode::GpuBitonic);
        c.upload(in);
        c.setDrive(table);
        c.step();
        o.cpu[m] = c.state();
        o.cpuGrid[m] = c.sim.grid();
        o.cpuCells[m] = c.sim.cells();
    }
    return o;
}

} // namespace swarm::venue_s
