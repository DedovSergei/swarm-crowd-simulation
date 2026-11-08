#pragma once

// Navigation field validation, test and tool code: nav_probe validate and test_gpu's navigation sections.
//   (a) known answers: rectangle worlds (nav::RectGeometry, point agents) against the exact geodesic distance, a shortest path
//       over the visibility graph of the obstacles' corners (Dijkstra; the last leg to the nearest point of the exit region):
//       an empty room with one door, an L-shaped corridor, a room with two doors (which exit each cell's path takes vs the
//       nearer one by the reference), a one-way ledge (directed: stepping down off it is allowed, up onto it not);
//   (b) the venue: every seat's cell has a path; every cell an agent can walk to from a seat has one; the unreachable floor
//       by kind;
//   (c) descent: a point following e_goal (nav::goal at the rest height) from every seat in 0.05 m steps reaches an exit region without a
//       stall, its path at most 1.2x the field's distance; every step a legal move;
//   (d) exit choice: seats per exit, per row door vs avenue;
//   (e) the 28-seat gangway rule: seats in a row between two gangways (and with one gangway, the dead-end segment).

#include <swarm/nav_field.hpp>
#include <swarm/sdf.hpp>
#include <swarm/venue.hpp>

#include <glm/glm.hpp>

#include <algorithm>
#include <random>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <map>
#include <queue>
#include <string>
#include <vector>

namespace swarm::nav_check {

using nav::Rect;

// --- Exact reference: geodesic distance among rectangular obstacles to a rectangular exit region ---
// Obstacles block a segment that passes through their open interior, inflated by SEAM_EPS so that two walls that touch along an
// edge leave no seam between them (a path could otherwise slip through it); the corners used as path vertices lie CORNER_EPS
// outside their own rectangle, and corners inside another obstacle (a seam) are no vertices. Both far below the grid's cell.
constexpr double SEAM_EPS = 1e-6, CORNER_EPS = 4e-6;
inline bool blocks(const Rect& r, glm::dvec2 a, glm::dvec2 b) {
    double t0 = 0.0, t1 = 1.0;
    const glm::dvec2 d = b - a;
    for (int ax = 0; ax < 2; ++ax) {
        const double lo = double(r.lo[ax]) - SEAM_EPS, hi = double(r.hi[ax]) + SEAM_EPS;
        if (std::abs(d[ax]) < 1e-15) {
            if (!(a[ax] > lo && a[ax] < hi)) return false;
            continue;
        }
        double u0 = (lo - a[ax]) / d[ax], u1 = (hi - a[ax]) / d[ax];
        if (u0 > u1) std::swap(u0, u1);
        t0 = std::max(t0, u0);
        t1 = std::min(t1, u1);
    }
    return t1 - t0 > 1e-12;   // an open interval of the segment inside the open rectangle
}
inline bool visible(const std::vector<Rect>& obstacles, glm::dvec2 a, glm::dvec2 b) {
    for (const Rect& r : obstacles)
        if (blocks(r, a, b)) return false;
    return true;
}
inline glm::dvec2 nearestIn(const Rect& r, glm::dvec2 p) { return glm::clamp(p, glm::dvec2(r.lo), glm::dvec2(r.hi)); }

struct Geodesic {
    std::vector<Rect> obstacles;
    Rect exit;
    std::vector<glm::dvec2> vertices;   // the obstacles' corners
    std::vector<double> dv;             // their distance to the exit
    Geodesic(std::vector<Rect> obs, Rect ex) : obstacles(std::move(obs)), exit(ex) {
        for (const Rect& r : obstacles)
            for (int k = 0; k < 4; ++k) {
                const double sx = (k == 1 || k == 2) ? 1.0 : -1.0, sy = k >= 2 ? 1.0 : -1.0;
                const glm::dvec2 c(sx > 0 ? r.hi.x : r.lo.x, sy > 0 ? r.hi.y : r.lo.y);
                const glm::dvec2 v = c + glm::dvec2(sx, sy) * CORNER_EPS;
                bool inside = false;
                for (const Rect& o : obstacles)
                    inside |= v.x > o.lo.x - SEAM_EPS && v.x < o.hi.x + SEAM_EPS && v.y > o.lo.y - SEAM_EPS && v.y < o.hi.y + SEAM_EPS;
                if (!inside) vertices.push_back(v);
            }
        const size_t n = vertices.size();
        constexpr double INF = std::numeric_limits<double>::infinity();
        dv.assign(n, INF);
        using E = std::pair<double, size_t>;
        std::priority_queue<E, std::vector<E>, std::greater<E>> q;
        for (size_t i = 0; i < n; ++i) {
            const glm::dvec2 t = nearestIn(exit, vertices[i]);
            if (visible(obstacles, vertices[i], t)) { dv[i] = glm::length(vertices[i] - t); q.push({ dv[i], i }); }
        }
        std::vector<char> done(n, 0);
        while (!q.empty()) {
            const auto [d, i] = q.top();
            q.pop();
            if (done[i] || d > dv[i]) continue;
            done[i] = 1;
            for (size_t j = 0; j < n; ++j) {
                if (done[j]) continue;
                const double c = d + glm::length(vertices[i] - vertices[j]);
                if (c < dv[j] && visible(obstacles, vertices[i], vertices[j])) { dv[j] = c; q.push({ c, j }); }
            }
        }
    }
    // From p: direct (the nearest exit point visible) or via a visible corner
    double operator()(glm::dvec2 p) const {
        double best = std::numeric_limits<double>::infinity();
        const glm::dvec2 t = nearestIn(exit, p);
        if (visible(obstacles, p, t)) best = glm::length(p - t);
        for (size_t i = 0; i < vertices.size(); ++i) {
            const double c = glm::length(p - vertices[i]) + dv[i];
            if (c < best && visible(obstacles, p, vertices[i])) best = c;
        }
        return best;
    }
};

// --- (a) Known-answer cases ---
struct KnownCase {
    std::string name, description;
    std::vector<Rect> walls, exits, ledges;
    std::vector<Rect> regions;   // the cells compared (the room's or corridor's interior)
    double limitCells = 1.0;     // |D - D_ref| limit in cells (a path bends at cell centres, up to ~one cell per corner)
    nav::Grid grid;
};

inline nav::Grid testGrid(float x0, float span, double cell = nav::CELL_M) {   // a grid in metres, cell edges on multiples of 'cell' from x0
    nav::Grid g;
    g.res = int(std::lround(span / cell));
    g.origin = x0;
    g.cell = float(cell);
    g.invCell = float(1.0 / cell);
    return g;
}

// Walls of a rectangular room [x0, x1] x [y0, y1] (interior), thickness t, with gaps (door openings) in its sides: side 0 bottom,
// 1 right, 2 top, 3 left; each gap (side, from, to) along the side's axis
struct Gap { int side; float from, to; };
inline std::vector<Rect> roomWalls(float x0, float y0, float x1, float y1, float t, const std::vector<Gap>& gaps) {
    std::vector<Rect> out;
    auto addSide = [&](int side, float a0, float a1, auto make) {   // the side's extent along its axis, minus the gaps
        std::vector<std::pair<float, float>> cuts;
        for (const Gap& g : gaps)
            if (g.side == side) cuts.push_back({ g.from, g.to });
        std::sort(cuts.begin(), cuts.end());
        float a = a0;
        for (const auto& c : cuts) { if (c.first > a) out.push_back(make(a, c.first)); a = c.second; }
        if (a1 > a) out.push_back(make(a, a1));
    };
    addSide(0, x0 - t, x1 + t, [&](float a, float b) { return Rect{ { a, y0 - t }, { b, y0 } }; });
    addSide(2, x0 - t, x1 + t, [&](float a, float b) { return Rect{ { a, y1 }, { b, y1 + t } }; });
    addSide(3, y0, y1, [&](float a, float b) { return Rect{ { x0 - t, a }, { x0, b } }; });
    addSide(1, y0, y1, [&](float a, float b) { return Rect{ { x1, a }, { x1 + t, b } }; });
    return out;
}

inline std::vector<KnownCase> knownCases() {
    std::vector<KnownCase> cs;
    {   // a1: a 12 m x 9 m room, one 1.2 m door in the top wall (0.3 m), the exit region beyond the wall's outer face
        KnownCase c;
        c.name = "room, one door";
        c.description = "12 x 9 m room, 0.3 m walls, a 1.2 m door in the top wall (x 5.4 .. 6.6); exit: beyond the wall (y > 9.3)";
        c.walls = roomWalls(0, 0, 12, 9, 0.3f, { { 2, 5.4f, 6.6f } });
        c.exits = { { { -1.0f, 9.325f }, { 13.0f, 10.5f } } };
        c.regions = { { { 0, 0 }, { 12, 9 } } };
        c.grid = testGrid(-1.0f, 14.0f);
        cs.push_back(c);
    }
    {   // a2: an L-shaped corridor, 2 m wide, 20 m along x then 13 m up y, the exit at the top end
        KnownCase c;
        c.name = "L corridor";
        c.description = "2 m wide L-shaped corridor: x 0 .. 20 (y 0 .. 2), then up x 18 .. 20 to y 15; 0.3 m walls; exit: beyond its top end (y > 15)";
        c.walls = { { { -0.3f, -0.3f }, { 20.3f, 0.0f } }, { { -0.3f, 0.0f }, { 0.0f, 2.3f } }, { { 0.0f, 2.0f }, { 18.0f, 2.3f } },
                    { { 17.7f, 2.3f }, { 18.0f, 15.0f } }, { { 20.0f, 0.0f }, { 20.3f, 15.0f } } };
        c.exits = { { { 17.0f, 15.025f }, { 21.0f, 16.0f } } };
        c.regions = { { { 0, 0 }, { 20, 2 } }, { { 18, 2 }, { 20, 15 } } };
        c.grid = testGrid(-1.0f, 22.5f);
        cs.push_back(c);
    }
    {   // a3: a room with two doors: the split between them
        KnownCase c;
        c.name = "room, two doors";
        c.description = "16 x 10 m room, 0.3 m walls, door A (1.2 m) in the top wall at x 2 .. 3.2, door B (1.2 m) in the right wall at y 7 .. 8.2; "
                        "exits beyond each";
        c.walls = roomWalls(0, 0, 16, 10, 0.3f, { { 2, 2.0f, 3.2f }, { 1, 7.0f, 8.2f } });
        c.exits = { { { 1.0f, 10.325f }, { 4.2f, 11.0f } }, { { 16.325f, 6.0f }, { 17.0f, 9.2f } } };
        c.regions = { { { 0, 0 }, { 16, 10 } } };
        c.grid = testGrid(-1.0f, 18.5f);
        cs.push_back(c);
    }
    {   // a4: a one-way ledge (directed graph): stepping down off it is allowed, up onto it not
        KnownCase c;
        c.name = "one-way ledge";
        c.description = "12 x 8 m room, a 0.3 m high ledge x 4 .. 8, y 0 .. 5 (one-way: down off it, never up), a 1.2 m door in the right wall at "
                        "y 0.5 .. 1.7; from the floor left of the ledge the path goes around it, from the ledge straight down off it";
        c.walls = roomWalls(0, 0, 12, 8, 0.3f, { { 1, 0.5f, 1.7f } });
        c.exits = { { { 12.325f, -1.0f }, { 13.0f, 9.0f } } };
        c.ledges = { { { 4.0f, 0.0f }, { 8.0f, 5.0f } } };
        c.regions = { { { 0, 0 }, { 12, 8 } } };
        c.limitCells = 2.0;   // the floor's path around the ledge bends at two of its corners
        c.grid = testGrid(-1.0f, 14.5f);
        cs.push_back(c);
    }
    return cs;
}

struct KnownResult {
    std::string name;
    long compared = 0, unreachable = 0, beyond = 0;   // cells compared; of them without a path; |error| > one cell
    double maxErr = 0.0, meanErr = 0.0, maxErrCells = 0.0;
    glm::vec2 worst{ 0.0f };
    // two doors: cells whose path takes the other exit than the reference's nearer one, and the largest reference margin
    // |D_A - D_B| among them (the split's position error)
    long splitMismatch = 0;
    double splitMaxMargin = 0.0;
    long splitA = 0, splitB = 0;
    // one-way ledge: floor cells left of the ledge, their mean detour over the straight line (the ledge is an obstacle for them)
    double ledgeDetourMean = 0.0;
    bool ok = false;
};

inline KnownResult runKnown(const KnownCase& c) {
    KnownResult r;
    r.name = c.name;
    const nav::RectGeometry geo(c.walls, c.exits, 0.0f, c.ledges);
    const nav::Field f = nav::build(geo, c.grid);
    const double h = double(c.grid.cell);
    // References: one per exit (the nearest of them); floor cells route around ledges (obstacles), ledge cells step off them
    std::vector<Geodesic> floorRef, ledgeRef;
    for (const Rect& e : c.exits) {
        std::vector<Rect> withLedges = c.walls;
        withLedges.insert(withLedges.end(), c.ledges.begin(), c.ledges.end());
        floorRef.emplace_back(withLedges, e);
        ledgeRef.emplace_back(c.walls, e);
    }
    double sumErr = 0.0, detour = 0.0;
    long detourN = 0;
    for (int iy = 0; iy < c.grid.res; ++iy)
        for (int ix = 0; ix < c.grid.res; ++ix) {
            const glm::vec2 p = c.grid.centre(ix, iy);
            bool in = false;
            for (const Rect& rg : c.regions) in |= p.x > rg.lo.x && p.x < rg.hi.x && p.y > rg.lo.y && p.y < rg.hi.y;
            const size_t i = size_t(c.grid.index(ix, iy));
            if (!in || f.cls[i] != nav::FIT) continue;   // point agents: NOFIT = inside a wall
            bool onLedge = false;
            for (const Rect& l : c.ledges) onLedge |= l.contains(p);
            std::vector<double> ref;
            for (size_t e = 0; e < c.exits.size(); ++e) {
                if (!onLedge) { ref.push_back(floorRef[e](glm::dvec2(p))); continue; }
                // from a ledge: a direct segment, or via a corner whose own path avoids the ledge (convex: the segment leaves it once)
                const Geodesic& g = floorRef[e];
                double best = std::numeric_limits<double>::infinity();
                const glm::dvec2 t = nearestIn(g.exit, glm::dvec2(p));
                if (visible(c.walls, glm::dvec2(p), t)) best = glm::length(glm::dvec2(p) - t);
                for (size_t v = 0; v < g.vertices.size(); ++v) {
                    const double cst = glm::length(glm::dvec2(p) - g.vertices[v]) + g.dv[v];
                    if (cst < best && visible(c.walls, glm::dvec2(p), g.vertices[v])) best = cst;
                }
                ref.push_back(best);
            }
            const double dRef = *std::min_element(ref.begin(), ref.end());
            ++r.compared;
            if (!f.reachable(i)) { ++r.unreachable; continue; }
            const double err = double(f.dist[i]) - dRef;
            sumErr += std::abs(err);
            if (std::abs(err) > r.maxErr) { r.maxErr = std::abs(err); r.worst = p; }
            if (std::abs(err) > c.limitCells * h) ++r.beyond;
            if (ref.size() == 2) {
                const int nearer = ref[0] <= ref[1] ? 0 : 1;
                (f.exitId[i] == 0 ? r.splitA : r.splitB)++;
                if (int(f.exitId[i]) != nearer) {
                    ++r.splitMismatch;
                    r.splitMaxMargin = std::max(r.splitMaxMargin, std::abs(ref[0] - ref[1]));
                }
            }
            if (!c.ledges.empty() && !onLedge && p.x < c.ledges[0].lo.x && p.y < c.ledges[0].hi.y) {
                detour += dRef - ledgeRef[0](glm::dvec2(p));
                ++detourN;
            }
        }
    r.meanErr = r.compared > r.unreachable ? sumErr / double(r.compared - r.unreachable) : 0.0;
    r.maxErrCells = r.maxErr / h;
    r.ledgeDetourMean = detourN ? detour / double(detourN) : 0.0;
    r.ok = r.compared > 0 && r.unreachable == 0 && r.beyond == 0 && (c.exits.size() < 2 || r.splitMaxMargin <= 2.0 * h);
    return r;
}

// --- (b)-(e) on a seated venue ---
struct VenueResult {
    // (b)
    long seats = 0, seatsNoPath = 0, seatsNotFit = 0;
    long walkable = 0, walkableNoPath = 0;   // cells reachable from the seats by legal moves (FIT and NOFIT), of them without a path
    struct Unreach { std::string kind; long cells = 0; };
    std::vector<Unreach> unreachable;        // unreachable floor by kind
    // (c)
    long descents = 0, stalls = 0, illegalSteps = 0, maxSteps = 0;
    std::map<std::string, long> illegalWhere;   // the illegal steps by verdict and by the venue cells they join
    double maxOvershootM = 0.0;                 // the longest part of an illegal step beyond the face it climbs (metres)
    double worstRatio = 0.0, meanRatio = 0.0;
    int worstSeat = -1;
    double worstPathM = 0.0, worstFieldM = 0.0;
    // (d)
    std::vector<long> perExit;
    std::vector<std::array<long, 2>> perRow;   // [row] = { avenue, door }
    // (e)
    std::vector<seated::RowSeats> rowSeats;
    int maxBetween = 0, maxDeadEnd = 0, rowsOver28 = 0;
};

inline std::string unreachableKind(const SeatedLayout& L, glm::vec2 c) {
    if (sdFence(glm::vec3(c, 0.0f)) < 0.0f) return "fence collision band";
    const glm::vec2 f = seated::fold(c);
    if (f.y < FENCE_HALF_INNER) return "pitch (fenced off)";
    if (f.y > L.outerFace) return "outside the outer wall";
    const int k = seated::cellAt(L, c);
    switch (k) {
    case seated::SEAT: return "top of a seat block";
    case seated::BARRIER: return "top of the front barrier";
    case seated::WALL: return "top of an outer / concourse side wall";
    case seated::SIDE: return "top of a side parapet";
    default: return std::string("other: ") + seated::cellKindName(k);
    }
}

// sample: the descent (c) from a seeded sample of that many seats (mt19937 partial Fisher-Yates, seed 'seed'; 0: every
// seat); the other checks cover every seat
inline VenueResult runVenue(const Venue& v, const nav::Field& f, int sample = 0, unsigned seed = 7) {
    const SeatedLayout& L = v.layout;
    const nav::Grid& g = f.grid;
    const nav::SeatedGeometry geo(L);
    VenueResult r;
    const std::vector<seated::Seat> seats = seated::seats(L);
    r.seats = long(seats.size());
    // (b) seats; forward reachability from the seats over legal edges
    std::vector<char> seen(g.cells(), 0);
    std::vector<int> stack;
    for (const seated::Seat& s : seats) {
        const glm::ivec2 c = g.cellOf(glm::vec2(s.pos));
        const size_t i = size_t(g.index(c.x, c.y));
        r.seatsNoPath += !f.reachable(i);
        r.seatsNotFit += f.cls[i] != nav::FIT;
        if (!seen[i]) { seen[i] = 1; stack.push_back(int(i)); }
    }
    while (!stack.empty()) {
        const int i = stack.back();
        stack.pop_back();
        ++r.walkable;
        r.walkableNoPath += !f.reachable(size_t(i));
        const int x = i % g.res, y = i / g.res;
        for (int k = 0; k < nav::DIR_COUNT; ++k) {
            if (!((f.out[size_t(i)] >> k) & 1u)) continue;
            const int j = g.index(x + nav::DIR_X[k], y + nav::DIR_Y[k]);
            if (!seen[size_t(j)]) { seen[size_t(j)] = 1; stack.push_back(j); }
        }
    }
    std::map<std::string, long> kinds;
    for (size_t i = 0; i < g.cells(); ++i)
        if (!f.reachable(i)) ++kinds[unreachableKind(L, g.centre(int(i)))];
    for (const auto& [k, n] : kinds) r.unreachable.push_back({ k, n });
    // (c) descent from every seat (or a seeded sample): 0.05 m steps along e_goal until the exit test (past the outer wall's outer face)
    const float step = float(units::modelLength(0.05));
    double sumRatio = 0.0;
    std::vector<int> order(seats.size());
    for (size_t i = 0; i < order.size(); ++i) order[i] = int(i);
    if (sample > 0 && size_t(sample) < order.size()) {
        std::mt19937 rng(seed);
        for (int i = 0; i < sample; ++i) std::swap(order[size_t(i)], order[size_t(i) + std::uniform_int_distribution<size_t>(0, order.size() - 1 - size_t(i))(rng)]);
        order.resize(size_t(sample));
        std::sort(order.begin(), order.end());
    }
#pragma omp parallel for schedule(dynamic, 16) reduction(+ : sumRatio)
    for (int oi = 0; oi < int(order.size()); ++oi) {
        const int s = order[size_t(oi)];
        glm::vec2 p(seats[size_t(s)].pos);
        const double field = double(f.value(p));
        double len = 0.0;
        long n = 0, illegal = 0;
        bool stalled = false;
        const long limit = long(field / double(step) * 2.0) + 2000;
        while (seated::fold(p).y <= L.outerFace) {
            const glm::vec2 e = nav::goal(f, L, glm::vec3(p, seated::floorHeight(L, p) + BODY_RADIUS));   // e_goal at the rest height
            if (glm::length(e) < 0.5f || ++n > limit) { stalled = true; break; }
            const glm::vec2 q = p + e * step;
            if (const int why = geo.moveVerdict(p, geo.floor(p), q, geo.floor(q)); why != 0) {
                ++illegal;
                glm::vec2 nrm;
                const double over = units::metres((1.0 - double(seated::stepUpScan(L, p, q, geo.floor(p), nrm))) * double(glm::length(q - p)));
#pragma omp critical
                r.maxOvershootM = std::max(r.maxOvershootM, over);
                static const char* names[5] = { "", "fence", "drop", "rise", "face climb" };
                const std::string key = std::string(names[why]) + ": " + seated::cellKindName(seated::cellAt(L, p)) + " -> " + seated::cellKindName(seated::cellAt(L, q)) +
                                        (f.cls[size_t(g.index(g.cellOf(p).x, g.cellOf(p).y))] == nav::FIT ? " (from a FIT cell)" : " (from a NOFIT cell)");
#pragma omp critical
                ++r.illegalWhere[key];
            }
            p = q;
            len += double(step);
        }
        const double ratio = len / field;
#pragma omp critical
        {
            ++r.descents;
            r.stalls += stalled;
            r.illegalSteps += illegal;
            r.maxSteps = std::max(r.maxSteps, n);
            if (!stalled && ratio > r.worstRatio) {
                r.worstRatio = ratio;
                r.worstSeat = s;
                r.worstPathM = units::metres(len);
                r.worstFieldM = units::metres(field);
            }
        }
        if (!stalled) sumRatio += ratio;
    }
    r.meanRatio = r.descents > r.stalls ? sumRatio / double(r.descents - r.stalls) : 0.0;
    // (d) exit choice
    r.perExit.assign(size_t(f.exitCount), 0);
    r.perRow.assign(size_t(L.rows), { 0, 0 });
    for (const seated::Seat& s : seats) {
        const glm::ivec2 c = g.cellOf(glm::vec2(s.pos));
        const size_t i = size_t(g.index(c.x, c.y));
        if (f.exitId[i] == nav::NO_EXIT) continue;
        ++r.perExit[f.exitId[i]];
        ++r.perRow[size_t(s.row)][f.exitId[i] < 4 ? 0 : 1];
    }
    // (e) the gangway rule
    r.rowSeats = seated::seatsPerRow(L);
    for (const seated::RowSeats& rs : r.rowSeats) {
        r.maxBetween = std::max(r.maxBetween, rs.between);
        r.maxDeadEnd = std::max(r.maxDeadEnd, rs.deadEnd);
        r.rowsOver28 += rs.between > 28;
    }
    return r;
}

} // namespace swarm::nav_check
