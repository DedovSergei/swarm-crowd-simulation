#pragma once

// GPU / CPU agreement of an analytic venue's e_goal: test_gpu nav.field / nav.exit_choice and
// nav_probe goaldiff.
// e_goal (physics.comp navGoal / navChoiceGoal; CPU nav::goal / choiceGoal) = the field's direction e with its component into the nearest
// wall or step face within FEELER_REACH removed and renormalized. Its decisions: whether a face lies within reach (the wall query's squared
// distance d2 < FEELER_REACH^2), which face is nearest, whether a cell is a wall at the query's height (its top above c.z), whether e leads
// into the face (into = e . n < 0) and the renormalization (|e - n into| > SAFE_NORMALIZE_EPS); the cell (the field's lookup) is compared
// apart, bit for bit. Away from those decisions e_goal is continuous in its inputs and the two sides agree to rounding; at a decision a
// rounding-level difference of an input selects the other branch. On AMD 26.10.1 the GPU's band and cell bounds of venue S differ from the
// CPU's by up to 1 ulp (the compiler reassociates vsRowFront(k) + VS_CLEARWAY into (VS_ROW0 + VS_CLEARWAY) + k VS_ROW_DEPTH, a constant pair
// folded, and folds literal pairs such as VS_GANGWAY_HI + VS_SEAT_INSET in double), and every seat lies exactly FEELER_REACH from the faces in
// front of and behind it (a clearway's centre, 0.25 m from each), so about half the seats take the other side of the reach decision.
//
// THE CRITERION:
//   (1) away from every decision (each CPU margin > DECISION_TOL, the projection's length >= SHORT_LEN): max |GPU - CPU| <= CONT_TOL;
//   (2) every point with |GPU - CPU| > CONT_TOL lies at a decision, and the GPU's value is the CPU's on the decision's other side (within
//       CONT_TOL): the CPU's e_goal with the reach moved by DECISION_TOL (the reach decision), or at the point moved by at most REPRO_ULPS ulps
//       in x, y or z (any decision);
//   (3) of the random points at most MAX_RANDOM_SHARE differ (a uniform sample rarely meets a decision's rounding band); the seats are exact
//       ties by construction and may take either side;
//   (4) the GPU's band and cell bounds and tops lie within BOUND_TOL of the CPU's (the assumption behind DECISION_TOL; compareCellTable).

#include <swarm/sim_params.hpp>
#include <swarm/venue.hpp>

#include <glm/glm.hpp>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <limits>
#include <vector>

namespace swarm::nav_goal_check {

constexpr float INF = std::numeric_limits<float>::infinity();

// The bounds. S's coordinates lie below 1.0 model units (outer half-width 0.97), where a float's ulp is at
// most 5.96e-8. BOUND_TOL = 2 such ulps: the GPU's bounds differ by 1 ulp on 26.10.1 (tops of inclines by 3e-8, following their bounds). A
// distance is the difference of two coordinates, each off by up to BOUND_TOL: DECISION_TOL = 2.5e-7 model units (7.8 um, about 4 ulps at
// 1.0). The flipped seats lie 4.4e-8 inside reach on the CPU. SHORT_LEN: renormalizing a projected vector of length l scales its rounding by
// 1 / l; at l >= 1e-2 a GPU rounding of 1e-7 stays below CONT_TOL.
// MAX_RANDOM_SHARE: 0 of 50 000 random points differ (nav.field, nav.exit_choice); 6 lie at a decision.
constexpr float DECISION_TOL = 2.5e-7f;
constexpr float BOUND_TOL = 1.2e-7f;
constexpr float SHORT_LEN = 1e-2f;
constexpr double CONT_TOL = 1e-5;
constexpr int REPRO_ULPS = 4;
constexpr double MAX_RANDOM_SHARE = 1e-3;

// The wall query's decision inputs at c (seated::wall's search, every band within 2 reach): the nearest face's squared distance in the folded
// plane (whatever the reach), the nearest OTHER face's (a candidate cell whose nearest point differs: a different face or corner), and the
// least |top - c.z| of the cells within 2 reach that are not inclines (a top at the query's height decides whether the cell is a wall)
struct WallInputs {
    bool inWall = false;
    float d2 = INF, d2Other = INF, topGap = INF;
};

inline WallInputs wallInputs(const SeatedLayout& L, glm::vec3 c, float reach) {
    using namespace seated;
    WallInputs w;
    const glm::vec2 f = fold(glm::vec2(c));
    const int nb = bandCount(L);
    const int jp = bandOf(L, f.y);
    {   // the own cell (venue.cpp ownCell): the band's cell containing lat, else its last
        float a, b;
        int k, r, kind = GROUND, row = -1;
        for (int cc = 0; cell(L, jp, cc, a, b, k, r); ++cc) {
            kind = k;
            row = r;
            if (f.x < b) break;
        }
        w.inWall = kind != INCLINE && cellTop(L, kind, row, f.y) > c.z;
    }
    const float R = 2.0f * reach, R2 = R * R;
    std::vector<std::pair<float, glm::vec2>> cand;
    for (int j = std::max(jp - L.maxBandSteps, 0); j <= std::min(jp + L.maxBandSteps, nb - 1); ++j) {
        float lo, hi;
        band(L, j, lo, hi);
        const float g = std::max(std::max(lo - f.y, f.y - hi), 0.0f);
        if (g * g >= R2) continue;
        float a, b;
        int k, r;
        for (int cc = 0; cell(L, j, cc, a, b, k, r); ++cc) {
            const glm::vec2 q = glm::clamp(f, glm::vec2(a, lo), glm::vec2(b, hi));
            const glm::vec2 dd = f - q;
            const float d2 = glm::dot(dd, dd);
            if (d2 >= R2) continue;
            if (k != INCLINE) w.topGap = std::min(w.topGap, std::abs(cellTop(L, k, r, lo) - c.z));
            const bool isWall = k != INCLINE && cellTop(L, k, r, lo) > c.z;
            if (isWall == w.inWall) continue;
            cand.emplace_back(d2, q);
        }
    }
    std::sort(cand.begin(), cand.end(), [](const auto& x, const auto& y) { return x.first < y.first; });
    if (!cand.empty()) {
        w.d2 = cand[0].first;
        for (size_t i = 1; i < cand.size(); ++i)
            if (cand[i].second != cand[0].second) { w.d2Other = cand[i].first; break; }
    }
    return w;
}

// The decision margins of e_goal at p for the field direction e (CPU values): each a distance to the decision's threshold
struct Margins {
    WallInputs wall;
    bool found = false;        // a face within reach (seated::wall, the production query)
    bool projected = false;    // e leads into it: the projection applies
    float reachGap = INF;      // |d - FEELER_REACH| (model units), d the nearest face's distance
    float faceGap = INF;       // the nearest other face's distance minus the nearest's (model units)
    float into = 0.0f;         // e . n (the face's normal away from it); 0 without a face
    float len = 1.0f;          // |e - n into| before the renormalization (1 without the projection)
};

inline Margins margins(const SeatedLayout& L, glm::vec3 p, glm::vec2 e) {
    Margins m;
    m.wall = wallInputs(L, p, FEELER_REACH);
    const glm::vec3 w = seated::wall(L, p, FEELER_REACH);
    m.found = w.z < FEELER_REACH;
    if (m.wall.d2 < INF) m.reachGap = std::abs(std::sqrt(m.wall.d2) - FEELER_REACH);
    if (m.wall.d2Other < INF) m.faceGap = std::sqrt(m.wall.d2Other) - std::sqrt(m.wall.d2);
    if (m.found) {
        m.into = glm::dot(e, glm::vec2(w));
        m.projected = m.into < 0.0f;
        if (m.projected) m.len = glm::length(e - glm::vec2(w) * m.into);
    }
    return m;
}

inline bool isAtDecision(const Margins& m) {
    return m.reachGap <= DECISION_TOL || m.faceGap <= DECISION_TOL || m.wall.topGap <= DECISION_TOL || (m.projected && m.len < SHORT_LEN);
}

// The CPU's e_goal for the direction e with the wall query at another reach (nav::goal's rule with FEELER_REACH replaced)
inline glm::vec2 goalAtReach(const SeatedLayout& L, glm::vec3 p, glm::vec2 e, float reach) {
    const glm::vec3 w = seated::wall(L, p, reach);
    const float into = glm::dot(e, glm::vec2(w));
    if (w.z < reach && into < 0.0f) {
        e -= glm::vec2(w) * into;
        const float l = glm::length(e);
        e = l > SAFE_NORMALIZE_EPS ? e / l : glm::vec2(0.0f);
    }
    return e;
}

// (2): how the CPU reproduces the GPU's value 'target' at p (e: the CPU's direction there; cpuAt(q): the CPU's e_goal at q). REACH: the reach
// decision's other side (reach -+ DECISION_TOL, if the point lies at it); MOVED: the point moved by 'ulps' (1, 2, 4 ... REPRO_ULPS) along 'axis'
struct Repro {
    enum How { NONE, REACH, MOVED } how = NONE;
    int ulps = 0;
    char axis = '-';
};
template <class F>
Repro reproduce(const SeatedLayout& L, glm::vec3 p, glm::vec2 e, const Margins& m, glm::vec2 target, F&& cpuAt) {
    Repro r;
    if (m.reachGap <= DECISION_TOL)
        for (float reach : { FEELER_REACH - DECISION_TOL, FEELER_REACH + DECISION_TOL })
            if (double(glm::length(goalAtReach(L, p, e, reach) - target)) <= CONT_TOL) { r.how = Repro::REACH; return r; }
    for (int s = 1; s <= REPRO_ULPS; s *= 2)
        for (int ax = 0; ax < 3; ++ax)
            for (int sg = -1; sg <= 1; sg += 2) {
                glm::vec3 q = p;
                for (int k = 0; k < s; ++k) q[ax] = std::nextafter(q[ax], sg < 0 ? -INF : INF);
                if (double(glm::length(cpuAt(q) - target)) <= CONT_TOL) {
                    r.how = Repro::MOVED;
                    r.ulps = s;
                    r.axis = "xyz"[ax];
                    return r;
                }
            }
    return r;
}

// The criterion's tallies over the compared points
struct Agreement {
    long compared = 0, comparedRandom = 0, bitSame = 0, atDecision = 0, atDecisionRandom = 0, projected = 0;
    long differ = 0, differRandom = 0, differSeats = 0, unexplained = 0, byReach = 0, byMove = 0, notReproduced = 0;
    double maxAway = 0.0, maxAll = 0.0;
    float maxAwayLen = 1.0f;   // the projected length at the largest difference away from the decisions
    int maxUlps = 0;
    bool pass() const {
        return maxAway <= CONT_TOL && unexplained == 0 && notReproduced == 0 && double(differRandom) <= MAX_RANDOM_SHARE * double(comparedRandom);
    }
    // the point at p (a random point or a seat): the CPU's direction eCpu and e_goal gCpu, the GPU's e_goal gGpu; cpuAt: the CPU's e_goal elsewhere
    template <class F>
    void add(const SeatedLayout& L, glm::vec3 p, glm::vec2 eCpu, glm::vec2 gCpu, glm::vec2 gGpu, bool random, F&& cpuAt) {
        const double d = glm::length(gCpu - gGpu);
        ++compared;
        comparedRandom += random;
        bitSame += gCpu == gGpu;
        projected += gCpu != eCpu;
        maxAll = std::max(maxAll, d);
        const Margins m = margins(L, p, eCpu);
        const bool at = isAtDecision(m);
        atDecision += at;
        atDecisionRandom += at && random;
        if (!at && d > maxAway) { maxAway = d; maxAwayLen = m.len; }
        if (d <= CONT_TOL) return;
        ++differ;
        (random ? differRandom : differSeats) += 1;
        unexplained += !at;
        const Repro r = reproduce(L, p, eCpu, m, gGpu, cpuAt);
        if (r.how == Repro::REACH) ++byReach;
        else if (r.how == Repro::MOVED) { ++byMove; maxUlps = std::max(maxUlps, r.ulps); }
        else ++notReproduced;
    }
};

// ulps between two finite floats of the same sign (0 if equal)
inline long ulpDistance(float a, float b) {
    int32_t ia, ib;
    std::memcpy(&ia, &a, 4);
    std::memcpy(&ib, &b, 4);
    return std::labs(long(ia) - long(ib));
}

// (4) The GPU's cell table at run time: a compute program (compiled with the venue's preamble) evaluates vsBand / vsCell / vsCellTop for
// band i / CELL_PROBE_CELLS, cell i % CELL_PROBE_CELLS (the invocation id: no constant folding of the indices) into o0[i] = (lo, hi, l0, l1),
// o1[i] = (exists, kind, row, top at lo); compareCellTable compares them with seated::band / cell / cellTop.
constexpr int CELL_PROBE_CELLS = 64;   // >= VS_MAX_CELLS of every venue
inline const char* cellTableProbeSource() {
    return "#version 430 core\n"
           "layout(local_size_x = 64) in;\n"
           "layout(std430, binding = 6) buffer R0 { vec4 o0[]; };\n"
           "layout(std430, binding = 7) buffer R1 { vec4 o1[]; };\n"
           "uniform int count;\n"
           "void main() { int i = int(gl_GlobalInvocationID.x); if (i >= count) return; int j = i / 64, c = i % 64;\n"
           "  float lo, hi, a = 0.0, b = 0.0; int k = -1, r = -1; vsBand(j, lo, hi); bool ok = c < VS_MAX_CELLS && vsCell(j, c, a, b, k, r);\n"
           "  o0[i] = vec4(lo, hi, a, b); o1[i] = vec4(ok ? 1.0 : 0.0, float(k), float(r), ok ? vsCellTop(k, r, lo) : 0.0); }\n";
}
struct CellParity {
    long bands = 0, cells = 0, bandDiff = 0, cellDiff = 0, structDiff = 0;   // structDiff: a cell's existence, kind or row differs
    long maxBoundUlps = 0;                                                   // the largest bound difference in ulps of the bound
    double maxAbs = 0.0;                                                     // the largest bound or top difference, model units
    bool pass() const { return structDiff == 0 && maxAbs <= BOUND_TOL; }
};
inline CellParity compareCellTable(const SeatedLayout& L, const std::vector<glm::vec4>& g0, const std::vector<glm::vec4>& g1) {
    CellParity p;
    auto diff = [&](float gpu, float cpu, bool bound) {
        p.maxAbs = std::max(p.maxAbs, std::abs(double(gpu) - double(cpu)));
        if (bound) p.maxBoundUlps = std::max(p.maxBoundUlps, ulpDistance(gpu, cpu));
        return gpu != cpu;
    };
    const int nb = seated::bandCount(L);
    for (int j = 0; j < nb; ++j) {
        float lo, hi;
        seated::band(L, j, lo, hi);
        const glm::vec4 gb = g0[size_t(j) * CELL_PROBE_CELLS];
        ++p.bands;
        p.bandDiff += diff(gb.x, lo, true) | diff(gb.y, hi, true);
        for (int c = 0; c < CELL_PROBE_CELLS; ++c) {
            float a = 0.0f, b = 0.0f;
            int k = -1, r = -1;
            const bool ok = seated::cell(L, j, c, a, b, k, r);
            const glm::vec4 x = g0[size_t(j) * CELL_PROBE_CELLS + size_t(c)], y = g1[size_t(j) * CELL_PROBE_CELLS + size_t(c)];
            if (!ok && y.x == 0.0f) continue;
            ++p.cells;
            if (ok != (y.x != 0.0f) || int(y.y) != k || int(y.z) != r) { ++p.structDiff; continue; }
            p.cellDiff += diff(x.z, a, true) | diff(x.w, b, true) | diff(y.w, seated::cellTop(L, k, r, lo), false);
        }
    }
    return p;
}

} // namespace swarm::nav_goal_check
