#include <swarm/nav_field.hpp>

#include <swarm/assets.hpp>
#include <swarm/sdf.hpp>
#include <swarm/shader.hpp>
#include <swarm/venue.hpp>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <limits>
#include <map>
#include <memory>
#include <mutex>
#include <queue>
#include <sstream>
#include <stdexcept>

namespace swarm::nav {

int dirIndex(int dx, int dy) {
    for (int k = 0; k < DIR_COUNT; ++k)
        if (DIR_X[k] == dx && DIR_Y[k] == dy) return k;
    return -1;
}

glm::vec2 Grid::centre(int ix, int iy) const {
    const double c = double(cell);
    return glm::vec2(float(double(origin) + (double(ix) + 0.5) * c), float(double(origin) + (double(iy) + 0.5) * c));
}

glm::ivec2 Grid::cellOf(glm::vec2 p) const {
    const glm::vec2 g = (p - glm::vec2(origin)) * invCell;   // physics.comp navDirection: (xy - NAV_ORIGIN) * NAV_INV_CELL
    return glm::clamp(glm::ivec2(glm::floor(g)), glm::ivec2(0), glm::ivec2(res - 1));
}

Grid venueGrid(const Venue& v) {
    if (!v.seated()) throw std::invalid_argument(std::string("nav::venueGrid: venue ") + v.name + " has no navigation field");
    const double cell = CELL_M / units::M_PER_UNIT;   // 0.0016 model units
    Grid g;
    g.res = int(std::lround(double(v.domainSpan) / cell));
    // a whole number of cells: exactly in float (a span such as 3.8 is not exact in float; venue S's 2.0 is)
    if (float(g.res * cell) != v.domainSpan) throw std::logic_error("nav::venueGrid: the domain is not a whole number of cells");
    g.origin = v.domainMin;
    g.cell = float(double(v.domainSpan) / g.res);
    g.invCell = float(double(g.res) / double(v.domainSpan));
    return g;
}

// --- Seated venue ---

float SeatedGeometry::floor(glm::vec2 xy) const { return seated::floorHeight(L_, xy); }

bool SeatedGeometry::fits(glm::vec2 xy, float floorZ) const {
    if (sdFence(glm::vec3(xy, 0.0f)) < 0.0f) return false;   // in the fence's collision band (sdFence is inflated by BODY_RADIUS)
    // physics.comp clearWalls on VENUE_ANALYTIC: the walls of the plane at the body's top (the centre at floor + BODY_RADIUS, the
    // plane VS_WALL_ABOVE higher), none closer than BODY_RADIUS (seated::wall finds those within its reach only: WALL_NONE)
    const glm::vec3 w = seated::wall(L_, glm::vec3(xy, floorZ + BODY_RADIUS + L_.wallAbove), BODY_RADIUS);
    return w.z >= BODY_RADIUS;
}

int SeatedGeometry::moveVerdict(glm::vec2 from, float fromZ, glm::vec2 to, float toZ) const {
    const glm::vec2 mid(FENCE_HALF_MID.x, FENCE_HALF_MID.y), c(FENCE_CENTER.x, FENCE_CENTER.y);
    if (sdBox2(from - c, mid) * sdBox2(to - c, mid) < 0.0f) return 1;   // physics.comp fenceCCD: the step crosses the midline
    if (toZ < fromZ - MAX_STEP_UP) return 2;                             // a drop deeper than a step: a fall
    if (toZ > fromZ + MAX_STEP_UP) return 3;                             // the step-up limit's rule (a)
    glm::vec2 n;
    if (seated::stepUpScan(L_, from, to, fromZ, n) < 1.0f) return 4;     // rule (b) on S: a climb over a vertical face
    // SEAT ROWS ARE EXITS ONLY. No route enters a row's clearway from outside it (a gangway, the walkway, the
    // concourse, another row): its occupants walk it out, nobody walks into it. The physics allows a level step from the incline onto
    // a clearway at its back edge, so the queue-aware choice's fields would route agents on a gangway back through rows towards other
    // gangways' doors: against the rows' own outflow, and from a centre a few cm lower on the incline than its cell's straight up a
    // clearway's side face the step-up rule refuses (on venue M, 7 agents stood for good on a corner gangway)
    int rowTo = -1;
    if (seated::cellAt(L_, to, &rowTo) == seated::TREAD) {
        int rowFrom = -1;
        if (seated::cellAt(L_, from, &rowFrom) != seated::TREAD || rowFrom != rowTo) return 5;
    }
    return 0;
}

bool SeatedGeometry::moveLegal(glm::vec2 from, float fromZ, glm::vec2 to, float toZ) const { return moveVerdict(from, fromZ, to, toZ) == 0; }

int SeatedGeometry::exitAt(glm::vec2 xy) const {
    const glm::vec2 f = seated::fold(xy);
    if (!(f.y > L_.outerFace)) return -1;   // the physics' exit test: past the outer wall's outer face
    const int e = seated::exitByLat(L_, xy);
    if (e < 4) return e;                     // the avenues reach the domain's edge; a door's region ends with its landing
    return f.y <= L_.landingEnd ? e : -1;
}

int SeatedGeometry::exitCount() const { return seated::exitCount(L_); }

std::string SeatedGeometry::exitName(int e) const { return seated::exitName(L_, e); }

double SeatedGeometry::exitWidthM(int e) const { return seated::exitWidthM(L_, e); }

// --- Rectangle worlds (known answers) ---

namespace {
bool segmentHitsRect(glm::vec2 a, glm::vec2 b, const Rect& r) {   // slab test on the closed rectangle
    float t0 = 0.0f, t1 = 1.0f;
    const glm::vec2 d = b - a;
    for (int ax = 0; ax < 2; ++ax) {
        if (std::abs(d[ax]) < 1e-12f) {
            if (a[ax] < r.lo[ax] || a[ax] > r.hi[ax]) return false;
            continue;
        }
        float u0 = (r.lo[ax] - a[ax]) / d[ax], u1 = (r.hi[ax] - a[ax]) / d[ax];
        if (u0 > u1) std::swap(u0, u1);
        t0 = std::max(t0, u0);
        t1 = std::min(t1, u1);
        if (t0 > t1) return false;
    }
    return true;
}
float rectDistance(glm::vec2 p, const Rect& r) {
    const glm::vec2 q = glm::clamp(p, r.lo, r.hi);
    return glm::length(p - q);
}
} // namespace

float RectGeometry::floor(glm::vec2 xy) const {
    for (const Rect& r : ledges_)
        if (r.contains(xy)) return ledgeH_;
    return 0.0f;
}

bool RectGeometry::fits(glm::vec2 xy, float) const {
    for (const Rect& r : walls_)
        if (r.contains(xy) || rectDistance(xy, r) < body_) return false;
    return true;
}

bool RectGeometry::moveLegal(glm::vec2 from, float fromZ, glm::vec2 to, float) const {
    for (const Rect& r : walls_)
        if (segmentHitsRect(from, to, r)) return false;
    for (int k = 1; k <= 8; ++k)   // no climb onto a ledge anywhere along the move (dropping off one is allowed)
        if (floor(from + (to - from) * (float(k) / 8.0f)) > fromZ + 1e-6f) return false;
    return true;
}

double RectGeometry::exitWidthM(int e) const {
    if (e < 0 || e >= int(exits_.size())) return 0.0;
    if (size_t(e) < exitWidths_.size()) return double(exitWidths_[size_t(e)]);
    const glm::vec2 d = exits_[size_t(e)].hi - exits_[size_t(e)].lo;
    return double(std::max(d.x, d.y));
}

int RectGeometry::exitAt(glm::vec2 xy) const {
    for (size_t e = 0; e < exits_.size(); ++e)
        if (exits_[e].contains(xy)) return int(e);
    return -1;
}

// --- Progress and cancellation (BuildMonitor) ---

namespace {
std::atomic<BuildMonitor*> g_buildMonitor{ nullptr };
}

void setBuildMonitor(BuildMonitor* m) { g_buildMonitor.store(m); }

void reportBuild(const std::string& stage, double fraction) {
    if (BuildMonitor* m = g_buildMonitor.load()) m->progress(stage, fraction);
}

bool buildCancelRequested() {
    BuildMonitor* m = g_buildMonitor.load();
    return m && m->cancelled();
}

void throwIfBuildCancelled() {
    if (buildCancelRequested()) throw BuildCancelled();
}

// --- The grid ---

Field buildGrid(const Geometry& geo, const Grid& grid) {
    const auto t0 = std::chrono::steady_clock::now();
    Field f;
    f.grid = grid;
    const size_t n = grid.cells();
    const int res = grid.res;
    f.floorZ.resize(n);
    f.cls.resize(n);
    f.out.assign(n, 0);
    f.exitRegion.resize(n);
    f.exitCount = geo.exitCount();
    for (int e = 0; e < f.exitCount; ++e) f.exitNames.push_back(geo.exitName(e));
    // (a cancelled build skips the remaining rows and throws after the loop: an exception may not leave an OpenMP region)
    reportBuild("navigation field: floors and classes", -1.0);
#pragma omp parallel for schedule(dynamic, 8)
    for (int iy = 0; iy < res; ++iy) {
        if (buildCancelRequested()) continue;
        for (int ix = 0; ix < res; ++ix) {
            const size_t i = size_t(grid.index(ix, iy));
            const glm::vec2 c = grid.centre(ix, iy);
            const float z = geo.floor(c);
            f.floorZ[i] = z;
            f.cls[i] = geo.fits(c, z) ? FIT : NOFIT;
            f.exitRegion[i] = int8_t(geo.exitAt(c));
        }
    }
    throwIfBuildCancelled();
    reportBuild("navigation field: legal moves", -1.0);
#pragma omp parallel for schedule(dynamic, 8)
    for (int iy = 0; iy < res; ++iy) {
        if (buildCancelRequested()) continue;
        for (int ix = 0; ix < res; ++ix) {
            const size_t i = size_t(grid.index(ix, iy));
            const glm::vec2 c = grid.centre(ix, iy);
            uint8_t mask = 0;
            for (int k = 0; k < DIR_COUNT; ++k) {
                const int nx = ix + DIR_X[k], ny = iy + DIR_Y[k];
                if (nx < 0 || ny < 0 || nx >= res || ny >= res) continue;
                const size_t j = size_t(grid.index(nx, ny));
                // a diagonal between two cells a body fits does not cut the corner of a cell it does not fit
                if (DIR_X[k] != 0 && DIR_Y[k] != 0 && f.cls[i] == FIT && f.cls[j] == FIT &&
                    (f.cls[size_t(grid.index(nx, iy))] != FIT || f.cls[size_t(grid.index(ix, ny))] != FIT))
                    continue;
                if (geo.moveLegal(c, f.floorZ[i], grid.centre(nx, ny), f.floorZ[j])) mask = uint8_t(mask | (1u << k));
            }
            f.out[i] = mask;
        }
    }
    throwIfBuildCancelled();
    f.buildSeconds = std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count();
    return f;
}

// --- The distance field ---

bool lineLegal(const Field& f, int a, int b, long long* cellSteps) {
    const int res = f.grid.res;
    int x = a % res, y = a / res;
    const int x1 = b % res, y1 = b / res;
    const int dx = std::abs(x1 - x), dy = std::abs(y1 - y), sx = x1 > x ? 1 : -1, sy = y1 > y ? 1 : -1;
    long long ix = 0, iy = 0, steps = 0;
    bool ok = true;
    // The segment between the two centres crosses the k-th vertical cell boundary at parameter (2k + 1) / (2 dx) and the k-th
    // horizontal one at (2k + 1) / (2 dy): compared exactly in integers. Equal: it passes through the corner (a diagonal step).
    while (ix < dx || iy < dy) {
        const long long cx = (2 * ix + 1) * dy, cy = (2 * iy + 1) * dx;
        int nx = x, ny = y;
        if (cx < cy) { nx += sx; ++ix; }
        else if (cx > cy) { ny += sy; ++iy; }
        else { nx += sx; ny += sy; ++ix; ++iy; }
        const int k = dirIndex(nx - x, ny - y);
        const size_t c = size_t(f.grid.index(x, y)), n = size_t(f.grid.index(nx, ny));
        ++steps;
        if (!((f.out[c] >> k) & 1u) || (f.cls[c] == FIT && f.cls[n] != FIT)) { ok = false; break; }
        x = nx;
        y = ny;
    }
    if (cellSteps) *cellSteps += steps;
    return ok;
}

// The Lazy Theta* search over f's grid (cls, out, exitRegion) from the FIT cells of the exit regions: every region (exitFilter
// -1, the nearest-exit field) or region exitFilter alone (a per-exit field). g: the path length (grid units; INFINITY:
// none), par: the anchor (-1: none), closed: expanded; exitId (optional): the exit each cell's path leads to.
void lazyThetaStar(const Field& f, int exitFilter, std::vector<double>& g, std::vector<int32_t>& par, std::vector<uint8_t>& closed,
                   std::vector<uint8_t>* exitIdOut, long long* losChecks, long long* losFallbacks, long long* losCellSteps) {
    const Grid& grid = f.grid;
    const size_t n = grid.cells();
    const int res = grid.res;
    constexpr double INF = std::numeric_limits<double>::infinity();
    g.assign(n, INF);
    par.assign(n, -1);
    closed.assign(n, 0);
    std::vector<uint8_t> scratch;
    std::vector<uint8_t>& exitId = exitIdOut ? *exitIdOut : scratch;
    exitId.assign(n, NO_EXIT);
    const double h = double(grid.cell);
    auto cellDist = [&](int a, int b) {
        const double dx = double(a % res - b % res), dy = double(a / res - b / res);
        return h * std::sqrt(dx * dx + dy * dy);
    };
    // FIT cells route over FIT cells only (a body fits along the whole path); NOFIT cells over anything
    auto classOk = [&](size_t from, size_t to) { return f.cls[from] != FIT || f.cls[to] == FIT; };
    using Entry = std::pair<double, int32_t>;
    std::priority_queue<Entry, std::vector<Entry>, std::greater<Entry>> open;
    for (size_t i = 0; i < n; ++i)
        if (f.exitRegion[i] >= 0 && (exitFilter < 0 || f.exitRegion[i] == exitFilter) && f.cls[i] == FIT) {
            g[i] = 0.0;
            par[i] = int32_t(i);
            open.push({ 0.0, int32_t(i) });
        }
    // Lazy Theta* over the reversed edges: a cell u reached from a closed cell v (the edge u -> v legal) takes v's anchor as its
    // own, at the straight-line length; the segment is checked when u is expanded, and if it is not legal u falls back to the
    // best closed neighbour it has a legal edge to (Theta*'s 'path 1').
    // A cancelled build (BuildMonitor) stops here early, checked every 65536 expansions; the caller throws BuildCancelled (this runs
    // inside OpenMP regions too) and discards the partial arrays.
    uint32_t pops = 0;
    while (!open.empty()) {
        if ((++pops & 0xFFFFu) == 0u && buildCancelRequested()) return;
        const auto [d, v] = open.top();
        open.pop();
        if (closed[size_t(v)] || d > g[size_t(v)]) continue;
        const int vx = v % res, vy = v / res;
        if (par[size_t(v)] != v) {
            if (losChecks) ++*losChecks;
            if (!lineLegal(f, v, par[size_t(v)], losCellSteps)) {
                if (losFallbacks) ++*losFallbacks;
                double best = INF;
                int32_t bp = -1;
                for (int k = 0; k < DIR_COUNT; ++k) {
                    const int wx = vx + DIR_X[k], wy = vy + DIR_Y[k];
                    if (wx < 0 || wy < 0 || wx >= res || wy >= res || !((f.out[size_t(v)] >> k) & 1u)) continue;
                    const size_t w = size_t(grid.index(wx, wy));
                    if (!closed[w] || !classOk(size_t(v), w)) continue;
                    const double c = g[w] + cellDist(v, int(w));
                    if (c < best) { best = c; bp = int32_t(w); }
                }
                g[size_t(v)] = best;
                par[size_t(v)] = bp;
            }
        }
        closed[size_t(v)] = 1;
        if (par[size_t(v)] < 0) continue;   // cannot happen (v was reached over a legal edge from a closed cell): defensive
        exitId[size_t(v)] = par[size_t(v)] == v ? uint8_t(f.exitRegion[size_t(v)]) : exitId[size_t(par[size_t(v)])];
        const int32_t p = par[size_t(v)];
        for (int k = 0; k < DIR_COUNT; ++k) {
            const int ux = vx + DIR_X[k], uy = vy + DIR_Y[k];
            if (ux < 0 || uy < 0 || ux >= res || uy >= res) continue;
            const size_t u = size_t(grid.index(ux, uy));
            if (closed[u] || !((f.out[u] >> opposite(k)) & 1u) || !classOk(u, size_t(v))) continue;   // the edge u -> v
            const double c = g[size_t(p)] + cellDist(int(u), p);
            if (c < g[u]) {
                g[u] = c;
                par[u] = p;
                open.push({ c, int32_t(u) });
            }
        }
    }
}

Field build(const Geometry& geo, const Grid& grid) {
    Field f = buildGrid(geo, grid);
    const auto t0 = std::chrono::steady_clock::now();
    const size_t n = grid.cells();
    std::vector<double> g;
    std::vector<int32_t> par;
    std::vector<uint8_t> closed;
    reportBuild("navigation field: distances to the nearest exit", -1.0);
    lazyThetaStar(f, -1, g, par, closed, &f.exitId, &f.losChecks, &f.losFallbacks, &f.losCellSteps);
    throwIfBuildCancelled();
    f.dist.resize(n);
    f.anchor = par;
    f.anchorXY.resize(n);
    for (size_t i = 0; i < n; ++i) {
        const bool reach = closed[i] && std::isfinite(g[i]);
        f.dist[i] = reach ? float(g[i]) : std::numeric_limits<float>::infinity();
        if (!reach) { f.anchor[i] = -1; f.exitId[i] = NO_EXIT; }
        f.anchorXY[i] = grid.centre(reach ? int(f.anchor[i]) : int(i));
    }
    f.searchSeconds = std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count();
    f.buildSeconds += f.searchSeconds;
    return f;
}

float Field::value(glm::vec2 x) const {
    const glm::ivec2 c = grid.cellOf(x);
    const size_t i = size_t(grid.index(c.x, c.y));
    if (!std::isfinite(dist[i])) return std::numeric_limits<float>::infinity();
    return dist[size_t(anchor[i])] + glm::length(x - anchorXY[i]);
}

glm::vec2 surfaceCellCentre(const Grid& gr, int i) {   // physics.comp navCellCentre
    const float cx = float(i % gr.res) + 0.5f, cy = float(i / gr.res) + 0.5f;
    const float px = cx * gr.cell, py = cy * gr.cell;
    return glm::vec2(gr.origin + px, gr.origin + py);
}

bool surfaceReaches(const SeatedLayout& L, glm::vec2 x, glm::vec2 c) {   // physics.comp navReaches
    if (seated::cellKey(L, c) == seated::cellKey(L, x)) return true;
    glm::vec2 n;
    return seated::stepUpScan(L, x, c, seated::floorHeight(L, x), n) >= 1.0f;
}

int directionCell(const Field& f, glm::vec2 x) {   // physics.comp navDirection's cell
    const Grid& gr = f.grid;
    const glm::vec2 g = (x - glm::vec2(gr.origin)) * gr.invCell;
    const glm::ivec2 c = gr.cellOf(x);
    int i = gr.index(c.x, c.y);
    if (f.cls[size_t(i)] != FIT) {   // a NOFIT cell: the FIT neighbour whose centre is nearest to x (none: its own)
        float best = 1e9f;
        for (int dy = -1; dy <= 1; dy++)
            for (int dx = -1; dx <= 1; dx++) {
                const glm::ivec2 m = c + glm::ivec2(dx, dy);
                if ((dx == 0 && dy == 0) || m.x < 0 || m.y < 0 || m.x >= gr.res || m.y >= gr.res) continue;
                const int j = gr.index(m.x, m.y);
                if (f.cls[size_t(j)] != FIT || !std::isfinite(f.dist[size_t(j)])) continue;
                const glm::vec2 q = g - (glm::vec2(m) + 0.5f);
                const float d2 = q.x * q.x + q.y * q.y;
                if (d2 < best) { best = d2; i = j; }
            }
    }
    if (f.surface && !surfaceReaches(*f.surface, x, surfaceCellCentre(gr, i))) {   // the surface rule (physics.comp navCell)
        float best = 1e9f;
        int pick = i;
        for (int dy = -1; dy <= 1; dy++)
            for (int dx = -1; dx <= 1; dx++) {
                const glm::ivec2 m = c + glm::ivec2(dx, dy);
                if (m.x < 0 || m.y < 0 || m.x >= gr.res || m.y >= gr.res) continue;
                const int j = gr.index(m.x, m.y);
                if (j == i || f.cls[size_t(j)] != FIT || !std::isfinite(f.dist[size_t(j)])) continue;
                const glm::vec2 q = g - (glm::vec2(m) + 0.5f);
                const float d2 = q.x * q.x + q.y * q.y;
                if (d2 < best && surfaceReaches(*f.surface, x, surfaceCellCentre(gr, j))) { best = d2; pick = j; }
            }
        i = pick;
    }
    return i;
}

glm::vec2 direction(const Field& f, glm::vec2 x) {   // physics.comp navDirection
    const size_t i = size_t(directionCell(f, x));
    if (!std::isfinite(f.dist[i])) return glm::vec2(0.0f);   // (info & NAV_REACHABLE) == 0
    const glm::vec2 d = f.anchorXY[i] - x;
    const float l = glm::length(d);
    return l > GOAL_DEADZONE ? d / l : glm::vec2(0.0f);
}

glm::vec2 goal(const Field& f, const SeatedLayout& L, glm::vec3 p) {   // physics.comp navGoal
    glm::vec2 e = direction(f, glm::vec2(p));
    const glm::vec3 w = seated::wall(L, p, FEELER_REACH);
    const float into = glm::dot(e, glm::vec2(w));
    if (w.z < FEELER_REACH && into < 0.0f) {
        e -= glm::vec2(w) * into;
        const float l = glm::length(e);
        e = l > SAFE_NORMALIZE_EPS ? e / l : glm::vec2(0.0f);
    }
    return e;
}

std::vector<GpuNavCell> gpuCells(const Field& f) {
    std::vector<GpuNavCell> out(f.grid.cells());
    for (size_t i = 0; i < out.size(); ++i) {
        GpuNavCell& c = out[i];
        c.anchorX = f.anchorXY[i].x;
        c.anchorY = f.anchorXY[i].y;
        c.dist = f.dist[i];
        c.info = uint32_t(f.exitId[i]) | (f.cls[i] == FIT ? NAV_FIT : 0u) | (f.reachable(i) ? NAV_REACHABLE : 0u);
    }
    return out;
}

std::string preambleDefines(const Grid& g) {
    std::ostringstream s;
    s << "#define VENUE_NAV_FIELD 1\n"
      << "#define NAV_RES " << g.res << "\n"
      << "#define NAV_ORIGIN " << glslFloatLiteral(g.origin) << "\n"
      << "#define NAV_INV_CELL " << glslFloatLiteral(g.invCell) << "\n"
      << "#define NAV_FIT " << NAV_FIT << "u\n"
      << "#define NAV_REACHABLE " << NAV_REACHABLE << "u\n"
      << "#define NAV_SURFACE_RULE 1\n"   // physics.comp navCell / navChoiceCell, nav::directionCell / choiceCell
      << "#define NAV_SURF_CELL " << glslFloatLiteral(g.cell) << "\n";
    return s.str();
}

// --- The cache ---

namespace {

struct Fnv {
    uint64_t h = 0xcbf29ce484222325ull;
    void bytes(const void* p, size_t n) {
        const unsigned char* b = static_cast<const unsigned char*>(p);
        for (size_t i = 0; i < n; ++i) { h ^= b[i]; h *= 0x100000001b3ull; }
    }
    template <class T> void vec(const std::vector<T>& v) { bytes(v.data(), v.size() * sizeof(T)); }
};

constexpr char MAGIC[8] = { 'S', 'W', 'N', 'A', 'V', 'F', '0', '1' };

std::string hexFloat(float v) {
    uint32_t b;
    std::memcpy(&b, &v, 4);
    char s[16];
    std::snprintf(s, sizeof s, "%08x", b);
    return s;
}

} // namespace

bool hasField(const Venue& v) { return v.seated(); }

uint64_t cacheKey(const Venue& v) {
    if (!hasField(v)) throw std::invalid_argument(std::string("nav::cacheKey: venue ") + v.name + " has no navigation field");
    // Everything the field depends on: the algorithm version, the grid, the generator's parameters and the layout they give
    // (float bits), the contact constants of the traversability rules and the step-up scan
    std::ostringstream s;
    const SeatedVenueParams& p = v.params;
    const SeatedLayout& L = v.layout;
    char b[64];
    auto d = [&](double x) { std::snprintf(b, sizeof b, "%.17g|", x); s << b; };
    s << "swarm-nav|" << VERSION << "|" << v.name << "|";
    const Grid g = venueGrid(v);
    s << g.res << "|" << hexFloat(g.origin) << "|" << hexFloat(g.cell) << "|" << hexFloat(g.invCell) << "|";
    for (double x : { p.walkwayWidthM, p.barrierThicknessM, p.avenueWidthM, p.sideWallThicknessM, double(p.rows), p.rowDepthM, p.clearwayM,
                      p.seatWidthM, p.gangwayWidthM, p.seatBlockInsetM, double(p.maxSeatsBetweenGangways), double(p.maxSeatsDeadEnd),
                      p.concourseWidthM, p.outerWallThicknessM, p.landingDepthM, p.rowRiseM, p.seatBlockTopM, p.barrierTopM,
                      p.wallTopAboveConcourseM, double(p.exitsPerQuadrant), p.exitRatePerMMin, p.egressTimeMin, p.minExitWidthM })
        d(x);
    for (const SeatedConstant& c : seatedConstants(L)) s << c.name << "=" << hexFloat(c.value) << "|";
    for (float x : { BODY_RADIUS, MAX_STEP_UP, STEP_UP_TOL, STEP_UP_SAMPLE, FENCE_HALF_MID.x, FENCE_HALF_MID.y, FENCE_CENTER.x, FENCE_CENTER.y,
                     FENCE_HALF_THK_COLL, v.domainMin, v.domainSpan })
        s << hexFloat(x) << "|";
    s << STEP_UP_MAX_SAMPLES << "|" << seated::SCAN_CROSSINGS << "|" << seated::SCAN_BISECTIONS;
    // The generated venues' exit layout, grids, straight gangways and doors (only where they differ from venue S's single
    // gangway and door per wing, so S's key and its cache files stay valid). The literal tag is part of the key: changing it renames every cache file.
    if (p.exitLayout != SeatedVenueParams::ExitLayout::DoorPerWing || p.gridRes != 0 || L.gangways != 1 || L.doors != 1 || L.cornerDoorLo < 1e8f) {
        s << "|5.7|" << int(p.exitLayout) << "|" << p.gridRes << "|" << L.gangways << "|" << L.doors << "|" << hexFloat(L.cornerDoorLo);
        for (int i = 0; i < L.gangways; ++i) s << "|" << hexFloat(L.gwLo[size_t(i)]) << "," << hexFloat(L.gwHi[size_t(i)]) << "," << L.gwRow[size_t(i)] << "," << L.gwSeated[size_t(i)];
        for (int i = 0; i < L.doors; ++i) s << "|" << hexFloat(L.doorLo[size_t(i)]) << "," << hexFloat(L.doorHi[size_t(i)]);
    }
    const std::string text = s.str();
    Fnv h;
    h.bytes(text.data(), text.size());
    return h.h;
}

std::filesystem::path cacheDir() {
    if (const char* env = std::getenv("SWARM_NAV_CACHE"); env && *env) return std::filesystem::path(env);
    return executableDirectory() / "navcache";
}

std::filesystem::path cacheFile(const Venue& v) {
    char b[64];
    std::snprintf(b, sizeof b, "nav_%s_%016llx.bin", v.name, (unsigned long long)cacheKey(v));
    return cacheDir() / b;
}

uint64_t contentHash(const Field& f) {
    Fnv h;
    h.bytes(&f.grid.res, sizeof f.grid.res);
    h.vec(f.floorZ);
    h.vec(f.cls);
    h.vec(f.out);
    h.vec(f.exitRegion);
    h.vec(f.dist);
    h.vec(f.anchor);
    h.vec(f.exitId);
    return h.h;
}

bool save(const Field& f, const std::filesystem::path& file) {
    std::error_code ec;
    std::filesystem::create_directories(file.parent_path(), ec);
    std::ostringstream body(std::ios::binary);
    auto put = [&](const void* p, size_t n) { body.write(static_cast<const char*>(p), std::streamsize(n)); };
    auto putVec = [&](const auto& v) { put(v.data(), v.size() * sizeof(v[0])); };
    const uint32_t version = VERSION, res = uint32_t(f.grid.res), exits = uint32_t(f.exitCount);
    put(&version, 4);
    put(&res, 4);
    put(&f.grid.origin, 4);
    put(&f.grid.cell, 4);
    put(&f.grid.invCell, 4);
    put(&exits, 4);
    put(&f.key, 8);
    putVec(f.floorZ);
    putVec(f.cls);
    putVec(f.out);
    putVec(f.exitRegion);
    putVec(f.dist);
    putVec(f.anchor);
    putVec(f.exitId);
    for (const std::string& name : f.exitNames) {
        const uint32_t len = uint32_t(name.size());
        put(&len, 4);
        put(name.data(), len);
    }
    const std::string payload = body.str();
    Fnv h;
    h.bytes(payload.data(), payload.size());
    // Written to a temporary file and renamed: a concurrent reader never sees a partial file
    const std::filesystem::path tmp = file.string() + ".tmp" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count());
    {
        std::ofstream o(tmp, std::ios::binary | std::ios::trunc);
        if (!o) return false;
        o.write(MAGIC, 8);
        o.write(payload.data(), std::streamsize(payload.size()));
        o.write(reinterpret_cast<const char*>(&h.h), 8);
        if (!o) return false;
    }
    std::filesystem::rename(tmp, file, ec);
    if (ec) { std::filesystem::remove(tmp, ec); return false; }
    return true;
}

bool CacheFileReader::open(const std::filesystem::path& file, const char* magic8) {
    std::error_code ec;
    const uintmax_t size = std::filesystem::file_size(file, ec);
    if (ec || size < 16 || size > uintmax_t(std::numeric_limits<std::streamsize>::max())) return false;
    in_.open(file, std::ios::binary);
    if (!in_) return false;
    char magic[8];
    in_.read(magic, 8);
    if (!in_ || std::memcmp(magic, magic8, 8) != 0) return false;
    left_ = size_t(size) - 16;   // between the magic and the checksum
    return true;
}

bool CacheFileReader::read(void* dst, size_t bytes) {
    if (bytes > left_) return false;
    in_.read(static_cast<char*>(dst), std::streamsize(bytes));
    if (!in_) return false;
    Fnv h;
    h.h = hash_;
    h.bytes(dst, bytes);
    hash_ = h.h;
    left_ -= bytes;
    return true;
}

bool CacheFileReader::finish() {
    uint64_t sum = 0;
    in_.read(reinterpret_cast<char*>(&sum), 8);
    return in_ && left_ == 0 && sum == hash_;
}

bool load(Field& f, const std::filesystem::path& file, uint64_t expectedKey) {
    CacheFileReader in;
    if (!in.open(file, MAGIC)) return false;
    uint32_t version = 0, res = 0, exits = 0;
    Field r;
    if (!in.read(&version, 4) || !in.read(&res, 4) || !in.read(&r.grid.origin, 4) || !in.read(&r.grid.cell, 4) || !in.read(&r.grid.invCell, 4) || !in.read(&exits, 4) ||
        !in.read(&r.key, 8))
        return false;
    if (version != VERSION || r.key != expectedKey || res == 0 || res > 100000 || exits > 255) return false;
    r.grid.res = int(res);
    r.exitCount = int(exits);
    const size_t n = r.grid.cells();
    if (!in.readVector(r.floorZ, n) || !in.readVector(r.cls, n) || !in.readVector(r.out, n) || !in.readVector(r.exitRegion, n) || !in.readVector(r.dist, n) ||
        !in.readVector(r.anchor, n) || !in.readVector(r.exitId, n))
        return false;
    for (uint32_t e = 0; e < exits; ++e) {
        uint32_t len = 0;
        if (!in.read(&len, 4) || len > 1000) return false;
        std::string name(len, '\0');
        if (!in.read(name.data(), len)) return false;
        r.exitNames.push_back(name);
    }
    if (!in.finish()) return false;
    r.anchorXY.resize(n);
    for (size_t i = 0; i < n; ++i) r.anchorXY[i] = r.grid.centre(r.anchor[i] >= 0 ? int(r.anchor[i]) : int(i));
    f = std::move(r);
    return true;
}

const Field& forVenue(const Venue& v) {
    if (!hasField(v)) throw std::invalid_argument(std::string("nav::forVenue: venue ") + v.name + " has no navigation field");
    static std::mutex mutex;
    static std::map<const Venue*, std::unique_ptr<Field>> fields;
    std::lock_guard<std::mutex> lock(mutex);
    std::unique_ptr<Field>& slot = fields[&v];
    if (slot) return *slot;
    const auto t0 = std::chrono::steady_clock::now();
    const uint64_t key = cacheKey(v);
    const std::filesystem::path file = cacheFile(v);
    auto f = std::make_unique<Field>();
    reportBuild("navigation field: reading the cache file", -1.0);
    if (load(*f, file, key)) {
        f->fromCache = true;
        f->buildSeconds = std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count();
        std::printf("navigation field of venue %s: loaded from %s (%.2f s)\n", v.name, file.string().c_str(), f->buildSeconds);
    } else {
        *f = build(SeatedGeometry(v.layout), venueGrid(v));   // BuildCancelled leaves the slot empty and writes nothing
        f->key = key;
        reportBuild("navigation field: saving the cache file", -1.0);
        const bool saved = save(*f, file);   // a temporary file renamed when complete
        std::printf("navigation field of venue %s: built in %.2f s (grid %.2f s, search %.2f s), %s %s\n", v.name, f->buildSeconds,
                    f->buildSeconds - f->searchSeconds, f->searchSeconds, saved ? "saved to" : "NOT saved to", file.string().c_str());
    }
    std::fflush(stdout);
    f->surface = &v.layout;   // the surface rule (directionCell)
    slot = std::move(f);
    return *slot;
}

} // namespace swarm::nav
