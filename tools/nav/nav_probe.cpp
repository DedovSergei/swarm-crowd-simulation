// nav_probe: the navigation field of an analytic venue, its reports and checks. Run from the repository root.
//
//   nav_probe grid [--venue S] [--out out/results/nav_s]
// The traversability grid (cell size, classes, floor heights, the directed edges and why an edge is not legal,
//       the one-way edges, the seats' cells, the clearways' standing strip, the exit regions) -> <out>/grid.md, grid.png
//       (a map of the classes and the one-way edges).
//   nav_probe field [--venue S] [--out out/results/nav_s] [--max 60]
// Builds the distance field (not the cache), prints the build statistics and the seats per nearest exit ->
//       <out>/field.png (the distance, dark near the exits; grey: no path).
//   nav_probe validate [--venue S] [--out out/results/nav_s]
// (a) the known-answer geometries against the exact geodesic, (b) venue S's paths and unreachable floor, (c) the
//       descent along e_goal from every seat, (d) the exit choice, (e) the gangway rule -> <out>/validation.md.
//   nav_probe known --case K --x X --y Y   (diagnostics) the anchor chain of one known-answer cell against the reference
// (trace and jam take --exit-choice nearest|queue-aware and --incline-speed 0|1, default the venue's; e_goal as the engine
//   computes it: queue-aware, on the field of the agent's assigned exit after the step)
//   nav_probe trace --agent I [--from S] [--to E] [--load L] [--engine cpu|gpu] [--dt-div k] [--agents I,J,...]
// (diagnostics) the routed seat spawn: one agent's position, e_goal, contact branches (CPU) and nearest
//       neighbours per step; --dt-div k (GPU) steps DT / k (run_experiment's shader variant); --agents: several agents per step
//   nav_probe jam --x X --y Y [--r 3] --steps S1,S2,... [--load L] [--dt-div k] [--engine cpu|gpu]
// (diagnostics) the agents within r metres of (X, Y) at the given steps: place, speed, e_goal, the
//       headway leader by physics.comp's rule (lane, mutual standoff), v_des; the leader chains' roots, leader cycles
//   nav_probe cells --x X --y Y [--n 3]   (diagnostics) the field's cells around (X, Y) m: class, distance, anchor (folded,
//       relative to the gangway's low edge and row 0's front), and whether the cell sees each neighbour's anchor
// nav_probe timing [--steps 250] [--calls 64] [--reps 15] [--out out/results/nav_s]   (a quiet GPU) the GPU cost
//       of e_goal on venue S: ns per navGoal / navDirection call (physics.comp's @nav block) at the positions of the routed state
//       after --steps steps, and the e_goal evaluations of one step there (the agent's own and the mutual-standoff test's for
//       each in-lane neighbour ahead) -> <out>/nav_timing.md
// nav_probe choice [--venue S] [--out out/results/nav_s] [--run [--load L] [--steps M] [--incline]]   the exit choice's
//       candidate table: build time, memory (and the largest planned venue's), accuracy against every exit's own field and the
//       nearest-exit field, each seat's candidates; --run: a queue-aware CPU evacuation, at every evaluation whether the best exit over
//       all exits lay outside the cell's candidates -> <out>/choice.md
// nav_probe drive [--x 6 --y 11.9] [--dx 1 --dy 0] [--steps 40] [--incline 1]   (diagnostics) one agent at (x, y) m driven in a
//       fixed plane direction (forced motion), CPU reference: position, speed, cell, contacts per step
// nav_probe build [--venues S,M,L] [--out out/results/venues]   builds each venue's navigation field and exit choice table
//       fresh (no cache), saves them to the cache (nav::cacheFile / choiceCacheFile: keyed by the venue's parameters), and reports the
//       grid, the build times, the memory (the table, the field arrays, this process's peak working set) and the load time from the
//       cache -> <out>/nav_build.md
// nav_probe choice-timing [--steps 250] [--reps 15] [--evals 40] [--out out/results/nav_s]   (a quiet GPU) the choice pass's GPU
//       cost alone (agents at rest) between and at evaluations, at the seat spawn and after --steps steps, against the whole step
//       -> <out>/choice_timing.md
// nav_probe excluded [--venue M] [--times 3,30,60,...] [--sample N] [--label X] [--out out/results/nav_m]   a GPU
//       evacuation of the default model; at evaluation steps near the given times, every exit's exact field against the agents'
//       candidates: agents for whom an EXCLUDED exit (not a candidate of their cell) has a lower E than their assigned exit / every
//       candidate; the cells and seats without an avenue candidate; hypothetical candidate rules -> <out>/excluded[_X].md, .csv
// nav_probe travel [--venue S] [--out out/results/nav_<v>]   every seat's unimpeded walking time to its fastest exit at the model's
//       free speeds (the incline speed model) along the exits' own fields: the travel bound of the bottleneck analysis -> <out>/travel.md
// nav_probe goaldiff [--venue S] [--variant none|precise-d2|precise-proj|precise-all] [--out out/results/nav_s]   GPU navGoal /
// navChoiceGoal against the CPU mirror at test_gpu's points (nav.field, nav.exit_choice): the difference's distribution, each differing point's
//       flipped decision and its CPU margins (tools/nav_goal_check.hpp); --variant: the probe with one GLSL operation unfused
//       -> <out>/goal_diff[_variant].md, .csv
#include "../benchmark/bench_common.hpp"
#include "../nav_check.hpp"
#include "../nav_goal_check.hpp"
#include "../venue_s.hpp"

#include <swarm/assets.hpp>
#include <swarm/cpu_crowd_sim.hpp>
#include <swarm/crowd_sim.hpp>
#include <swarm/exit_choice.hpp>
#include <swarm/nav_field.hpp>
#include <swarm/sdf.hpp>
#include <swarm/shader.hpp>
#include <swarm/venue.hpp>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include <algorithm>
#include <array>
#include <fstream>
#include <iomanip>
#include <map>
#include <memory>
#include <random>
#include <set>
#include <sstream>

#include <omp.h>
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <psapi.h>
#pragma comment(lib, "psapi.lib")

namespace fs = std::filesystem;
using namespace swarm;

namespace {

std::string fmt(const char* f, double v) { char b[96]; std::snprintf(b, sizeof b, f, v); return b; }

struct Report {
    std::ostringstream md;
    void line(const std::string& s) { md << s << "\n"; std::printf("%s\n", s.c_str()); }
    void write(const fs::path& path) const {
        fs::create_directories(path.parent_path());
        std::ofstream(path) << md.str();
        std::printf("-> %s\n", path.string().c_str());
    }
};

std::string header(const char* tool) {
    return std::string("nav_probe ") + tool + " | commit " + bench::gitCommit() + " (dirty " + bench::gitDirty() + ") | " SWARM_BUILD_TYPE " | " +
           bench::localTimestamp("%Y-%m-%d %H:%M");
}

// The model options of a diagnostic run (--exit-choice, --incline-speed, --stair-flow; default: the venue's), and e_goal of every agent as
// the engine computes it (queue-aware: the field of the agent's assigned exit)
ModelOptions modelOptionsOf(const bench::Args& a, const Venue& v) {
    ModelOptions mo = defaultModelOptions(v);
    if (a.has("exit-choice")) mo.exitChoice = exitChoiceByName(a.get("exit-choice", "nearest"));
    if (a.has("incline-speed")) mo.inclineSpeed = a.getInt("incline-speed", 0) != 0;
    if (a.has("stair-flow")) mo.stairFlow = stairFlowByName(a.get("stair-flow", "off"));
    return effectiveModelOptions(v, mo);
}
glm::vec2 goalOf(const Venue& v, const ModelOptions& mo, const std::vector<uint32_t>& assign, size_t i, glm::vec3 p) {
    if (mo.exitChoice == ExitChoice::QueueAware) return nav::choiceGoal(nav::choiceForVenue(v), v.layout, p, assign[i]);
    return nav::goal(nav::forVenue(v), v.layout, p);
}

// A top-down RGB image of the grid, one pixel per cell, +y up
struct Image {
    int w, h;
    std::vector<uint8_t> px;
    Image(int w_, int h_) : w(w_), h(h_), px(size_t(w_) * size_t(h_) * 3, 255) {}
    void set(int x, int y, std::array<uint8_t, 3> c) {
        const size_t o = (size_t(h - 1 - y) * size_t(w) + size_t(x)) * 3;
        px[o] = c[0]; px[o + 1] = c[1]; px[o + 2] = c[2];
    }
    void save(const fs::path& p) const {
        fs::create_directories(p.parent_path());
        stbi_write_png(p.string().c_str(), w, h, 3, px.data(), w * 3);
        std::printf("-> %s\n", p.string().c_str());
    }
};

// --- grid ---
int runGrid(const bench::Args& a) {
    const Venue& v = venueByName(a.get("venue", "S"));
    const SeatedLayout& L = v.layout;
    const fs::path out = a.get("out", "out/results/nav_s");
    const nav::Grid grid = nav::venueGrid(v);
    const nav::SeatedGeometry geo(L);
    const nav::Field f = nav::buildGrid(geo, grid);
    const size_t n = grid.cells();
    const double cellM2 = nav::CELL_M * nav::CELL_M;

    Report r;
    r.line("# Venue " + std::string(v.name) + ": traversability grid");
    r.line("");
    r.line(header("grid"));
    r.line("");
    r.line("## Grid");
    r.line("");
    r.line("| quantity | value |");
    r.line("|---|---|");
    r.line("| cell size | " + fmt("%.3f m", nav::CELL_M) + " (" + fmt("%.7g", double(grid.cell)) + " model units) |");
    r.line("| cells | " + std::to_string(grid.res) + " x " + std::to_string(grid.res) + " = " + std::to_string(n) + " over the domain [" +
           fmt("%.2f", units::metres(v.domainMin)) + ", " + fmt("%.2f", units::metres(v.domainMax())) + "] m in x and y |");
    r.line("| built in | " + fmt("%.2f s", f.buildSeconds) + " (" + std::to_string(bench::logicalCores()) + " logical cores, OpenMP) |");
    r.line("");
    r.line("Per cell, at its centre: the floor (seated::floorHeight, the physics' floor); FIT if a standing body fits (the centre at");
    r.line("floor + BODY_RADIUS clears the walls of the plane at the body's top, floor + 2 BODY_RADIUS (seated::wall), by");
    r.line("BODY_RADIUS, and lies outside the fence's collision band), else NOFIT. Edges to the 8 neighbours, directed: legal if the");
    r.line("move from centre to centre crosses no fence midline, drops at most MAX_STEP_UP (deeper: a fall), rises at most");
    r.line("MAX_STEP_UP and passes the step-up limit's own scan (seated::stepUpScan = physics.comp venueStepUpScan, with the start");
    r.line("cell's floor as f0: no climb over a vertical face onto a floor above it); a diagonal between FIT cells needs both side");
    r.line("cells FIT (no corner cutting).");
    r.line("");

    // Classes per cell kind (the seated cell under the centre)
    struct KindRow { long fit = 0, nofit = 0; float zMin = 1e9f, zMax = -1e9f; };
    std::map<std::string, KindRow> kinds;
    auto kindName = [&](glm::vec2 c) -> std::string {
        if (sdFence(glm::vec3(c, 0.0f)) < 0.0f) return "fence band";
        const glm::vec2 fo = seated::fold(c);
        if (fo.y < FENCE_HALF_INNER) return "pitch";
        if (fo.y > L.outerFace) return fo.x < L.avenueHalf ? "beyond the outer face: avenue ends" : "beyond the outer face: landings, outside ground";
        int row = -1, band = 0;
        const int k = seated::cellAt(L, c, &row, &band);
        if (k == seated::GROUND) return band == 0 ? "walkway" : band == 1 ? "barrier gaps (gangway feet)" : "avenues";
        if (k == seated::CONC) return band == seated::bandCount(L) - 4 ? "rear concourse" : "concourse exits (through the outer wall)";
        if (k == seated::TREAD) return "clearways";
        if (k == seated::INCLINE) return "gangways (incline)";
        return std::string("tops of ") + seated::cellKindName(k);
    };
    long fit = 0, nofit = 0;
    for (size_t i = 0; i < n; ++i) {
        const glm::vec2 c = grid.centre(int(i));
        KindRow& k = kinds[kindName(c)];
        (f.cls[i] == nav::FIT ? k.fit : k.nofit)++;
        (f.cls[i] == nav::FIT ? fit : nofit)++;
        k.zMin = std::min(k.zMin, f.floorZ[i]);
        k.zMax = std::max(k.zMax, f.floorZ[i]);
    }
    r.line("## Classes");
    r.line("");
    r.line("| where (the venue cell under the centre) | FIT cells | FIT m^2 | NOFIT cells | NOFIT m^2 | floor [m] |");
    r.line("|---|---:|---:|---:|---:|---|");
    for (const auto& [name, k] : kinds)
        r.line("| " + name + " | " + std::to_string(k.fit) + " | " + fmt("%.1f", k.fit * cellM2) + " | " + std::to_string(k.nofit) + " | " +
               fmt("%.1f", k.nofit * cellM2) + " | " + fmt("%.2f", units::metres(k.zMin)) + " .. " + fmt("%.2f", units::metres(k.zMax)) + " |");
    r.line("| **all** | " + std::to_string(fit) + " | " + fmt("%.1f", fit * cellM2) + " | " + std::to_string(nofit) + " | " + fmt("%.1f", nofit * cellM2) + " | |");
    r.line("");

    // Edges: legal both ways, one way only (by the reverse direction's verdict), neither (by verdict)
    long both = 0, oneWay = 0, neither = 0, oneWayFitFit = 0;
    std::array<long, 6> oneWayWhy{}, neitherWhy{};
    std::map<std::string, long> oneWayWhere;
    Image img(grid.res, grid.res);
    for (int iy = 0; iy < grid.res; ++iy)
        for (int ix = 0; ix < grid.res; ++ix) {
            const size_t i = size_t(grid.index(ix, iy));
            const glm::vec2 c = grid.centre(ix, iy);
            const int k = seated::cellAt(L, c);
            std::array<uint8_t, 3> col;
            if (f.cls[i] == nav::NOFIT) col = { 150, 150, 150 };
            else if (k == seated::TREAD) col = { 66, 133, 244 };
            else if (k == seated::INCLINE) col = { 52, 168, 83 };
            else if (k == seated::CONC) col = { 251, 188, 4 };
            else if (k == seated::GROUND) col = { 230, 230, 220 };
            else col = { 90, 60, 60 };   // the top of a seat block, the barrier or a wall: a body fits there, unreachable
            if (f.exitRegion[i] >= 0 && f.cls[i] == nav::FIT) col = { 234, 67, 53 };
            bool marked = false;
            for (int d = 0; d < 4; ++d) {   // each undirected pair once: directions 0..3 (+x, +x+y, +y, -x+y)
                const int nx = ix + nav::DIR_X[d], ny = iy + nav::DIR_Y[d];
                if (nx < 0 || ny < 0 || nx >= grid.res || ny >= grid.res) continue;
                const size_t j = size_t(grid.index(nx, ny));
                const bool fwd = (f.out[i] >> d) & 1u, back = (f.out[j] >> nav::opposite(d)) & 1u;
                if (fwd && back) { ++both; continue; }
                const glm::vec2 cj = grid.centre(nx, ny);
                if (fwd || back) {
                    ++oneWay;
                    if (f.cls[i] == nav::FIT && f.cls[j] == nav::FIT) {
                        ++oneWayFitFit;
                        marked = true;
                        ++oneWayWhere[kindName(c) + " -> " + kindName(cj)];
                    }
                    const int why = fwd ? geo.moveVerdict(cj, f.floorZ[j], c, f.floorZ[i]) : geo.moveVerdict(c, f.floorZ[i], cj, f.floorZ[j]);
                    ++oneWayWhy[size_t(std::clamp(why, 0, 5))];
                } else {
                    ++neither;
                    ++neitherWhy[size_t(std::clamp(geo.moveVerdict(c, f.floorZ[i], cj, f.floorZ[j]), 0, 5))];
                }
            }
            if (marked) col = { 0, 0, 0 };
            img.set(ix, iy, col);
        }
    const char* why[6] = { "legal (a diagonal cutting a NOFIT corner)", "fence crossing", "drop deeper than MAX_STEP_UP", "rise above MAX_STEP_UP",
                           "climb over a vertical face (step-up scan)", "into a seat row from outside it (rows are exits only)" };
    r.line("## Directed edges");
    r.line("");
    r.line("Neighbour pairs (each pair once): legal both ways " + std::to_string(both) + ", one way only " + std::to_string(oneWay) +
           " (between two FIT cells: " + std::to_string(oneWayFitFit) + "), neither way " + std::to_string(neither) + ".");
    r.line("");
    r.line("| reason the other direction (one-way pairs) / both directions (neither) is not legal | one way | neither |");
    r.line("|---|---:|---:|");
    for (int k = 0; k < 6; ++k) r.line(std::string("| ") + why[k] + " | " + std::to_string(oneWayWhy[size_t(k)]) + " | " + std::to_string(neitherWhy[size_t(k)]) + " |");
    r.line("");
    r.line("One-way pairs between FIT cells, by where they are (legal direction first is not distinguished):");
    r.line("");
    r.line("| pair (cell -> its +x / +x+y / +y / -x+y neighbour) | pairs |");
    r.line("|---|---:|");
    for (const auto& [w, c] : oneWayWhere) r.line("| " + w + " | " + std::to_string(c) + " |");
    r.line("");

    // Seats: the cell of every seat's spawn position; the clearway's standing strip per row
    const std::vector<seated::Seat> seats = seated::seats(L);
    long seatsFit = 0;
    for (const seated::Seat& s : seats) seatsFit += f.cls[size_t(grid.index(grid.cellOf(glm::vec2(s.pos)).x, grid.cellOf(glm::vec2(s.pos)).y))] == nav::FIT;
    r.line("## Seats and clearways");
    r.line("");
    r.line("Seats whose spawn position (clearway centre) lies in a FIT cell: " + std::to_string(seatsFit) + " of " + std::to_string(seats.size()) + ".");
    r.line("");
    r.line("The clearway's standing strip: the FIT cells across a clearway (along its depth, at the middle of the wing's dead-end");
    r.line("segment), per row; a body (0.40 m) in a 0.50 m clearway between two seat blocks leaves its centre a 0.10 m strip.");
    r.line("");
    r.line("| row | FIT cells across the clearway | strip [m] |");
    r.line("|---:|---:|---|");
    const float latMid = 0.5f * (L.lat0 + L.gangwayLo - L.seatInset);
    int minStrip = 1 << 30;
    for (int k = 0; k < L.rows; ++k) {
        const float d0 = L.row0 + float(k) * L.rowDepth, d1 = d0 + L.clearway;
        int count = 0;
        float lo = 1e9f, hi = -1e9f;
        for (int iy = 0; iy < grid.res; ++iy) {
            const glm::vec2 c = grid.centre(grid.cellOf(glm::vec2(latMid, 0.0f)).x, iy);
            if (c.y < d0 || c.y > d1) continue;
            if (f.cls[size_t(grid.index(grid.cellOf(glm::vec2(latMid, 0.0f)).x, iy))] != nav::FIT) continue;
            ++count;
            lo = std::min(lo, c.y - d0);
            hi = std::max(hi, c.y - d0);
        }
        minStrip = std::min(minStrip, count);
        r.line("| " + std::to_string(k) + " | " + std::to_string(count) + " | " +
               (count ? fmt("%.3f", units::metres(lo)) + " .. " + fmt("%.3f", units::metres(hi)) + " behind the row front" : std::string("none")) + " |");
    }
    r.line("");

    // Exit regions
    std::vector<long> exitFit(size_t(f.exitCount), 0);
    for (size_t i = 0; i < n; ++i)
        if (f.exitRegion[i] >= 0 && f.cls[i] == nav::FIT) ++exitFit[size_t(f.exitRegion[i])];
    r.line("## Exit regions");
    r.line("");
    r.line("The physics parks an agent past the outer wall's outer face (" + fmt("%.2f m", units::metres(L.outerFace)) + "); the exit regions are");
    r.line("the four avenue ends (lat < " + fmt("%.2f m", units::metres(L.avenueHalf)) + ") and the eight concourse door landings (lat " +
           fmt("%.2f", units::metres(L.exitLo)) + " .. " + fmt("%.2f m", units::metres(L.exitHi)) + ", dep up to " + fmt("%.2f m", units::metres(L.landingEnd)) + ").");
    r.line("");
    r.line("| exit | FIT cells | m^2 |");
    r.line("|---|---:|---:|");
    for (int e = 0; e < f.exitCount; ++e)
        r.line("| " + f.exitNames[size_t(e)] + " | " + std::to_string(exitFit[size_t(e)]) + " | " + fmt("%.2f", exitFit[size_t(e)] * cellM2) + " |");
    r.line("");
    r.line("Map (grid.png, one pixel per cell, +x right, +y up): clearways blue, gangways green, concourse and exits yellow, ground light,");
    r.line("NOFIT grey, seat-block / barrier / wall tops dark red, exit cells red, FIT cells with a one-way edge black.");

    const bool ok = seatsFit == long(seats.size()) && minStrip >= 1;
    r.line("");
    r.line(std::string("**Checks: ") + (ok ? "PASS" : "FAIL") + "** (every seat's cell FIT; every row's clearway has FIT cells across it)");
    r.write(out / "grid.md");
    img.save(out / "grid.png");
    return ok ? 0 : 1;
}

// Distance colour (0 .. maxM metres): a perceptual-ish ramp, dark blue near the exits to yellow far away
std::array<uint8_t, 3> ramp(double t) {
    t = std::clamp(t, 0.0, 1.0);
    static const double stops[5][3] = { { 13, 8, 135 }, { 126, 3, 168 }, { 204, 71, 120 }, { 248, 149, 64 }, { 240, 249, 33 } };
    const double x = t * 4.0;
    const int i = std::min(3, int(x));
    const double u = x - i;
    std::array<uint8_t, 3> c;
    for (int k = 0; k < 3; ++k) c[size_t(k)] = uint8_t(std::lround(stops[i][k] + (stops[i + 1][k] - stops[i][k]) * u));
    return c;
}

// --- field ---
int runField(const bench::Args& a) {
    const Venue& v = venueByName(a.get("venue", "S"));
    const fs::path out = a.get("out", "out/results/nav_s");
    const nav::Grid grid = nav::venueGrid(v);
    const nav::Field f = nav::build(nav::SeatedGeometry(v.layout), grid);
    const size_t n = grid.cells();
    long reachFit = 0, reachNofit = 0, unreach = 0;
    float maxD = 0.0f;
    for (size_t i = 0; i < n; ++i) {
        if (!f.reachable(i)) { ++unreach; continue; }
        (f.cls[i] == nav::FIT ? reachFit : reachNofit)++;
        maxD = std::max(maxD, f.dist[i]);
    }
    std::printf("field: built in %.2f s (search %.2f s): LoS checks %lld, fallbacks %lld, cell steps %lld\n", f.buildSeconds, f.searchSeconds,
                f.losChecks, f.losFallbacks, f.losCellSteps);
    std::printf("reachable FIT %ld, NOFIT %ld, unreachable %ld; max distance %.2f m; content hash %016llx\n", reachFit, reachNofit, unreach,
                units::metres(maxD), (unsigned long long)nav::contentHash(f));
    const std::vector<seated::Seat> seats = seated::seats(v.layout);
    std::vector<long> perExit(size_t(f.exitCount), 0);
    long noPath = 0;
    for (const seated::Seat& s : seats) {
        const glm::ivec2 c = grid.cellOf(glm::vec2(s.pos));
        const size_t i = size_t(grid.index(c.x, c.y));
        if (!f.reachable(i)) { ++noPath; continue; }
        ++perExit[f.exitId[i]];
    }
    for (int e = 0; e < f.exitCount; ++e) std::printf("  %-22s %ld seats\n", f.exitNames[size_t(e)].c_str(), perExit[size_t(e)]);
    std::printf("  seats without a path: %ld\n", noPath);
    Image img(grid.res, grid.res);
    const double maxM = a.has("max") ? std::stod(a.get("max", "60")) : units::metres(maxD);
    for (int iy = 0; iy < grid.res; ++iy)
        for (int ix = 0; ix < grid.res; ++ix) {
            const size_t i = size_t(grid.index(ix, iy));
            if (!f.reachable(i)) { img.set(ix, iy, { 60, 60, 60 }); continue; }
            std::array<uint8_t, 3> c = ramp(units::metres(f.dist[i]) / maxM);
            if (f.cls[i] == nav::NOFIT) for (uint8_t& x : c) x = uint8_t(x / 2 + 64);
            img.set(ix, iy, c);
        }
    img.save(out / "field.png");
    return 0;
}

// --- known (diagnostics): one known-answer case, the anchor chain of the cell at (x, y) against the reference ---
int runKnownDebug(const bench::Args& a) {
    const std::vector<nav_check::KnownCase> cs = nav_check::knownCases();
    const nav_check::KnownCase& c = cs[size_t(a.getInt("case", 0))];
    const nav::RectGeometry geo(c.walls, c.exits, 0.0f, c.ledges);
    const nav::Field f = nav::build(geo, c.grid);
    const glm::vec2 p(std::stof(a.get("x", "11.975")), std::stof(a.get("y", "8.975")));
    std::vector<nav::Rect> obs = c.walls;
    obs.insert(obs.end(), c.ledges.begin(), c.ledges.end());
    const nav_check::Geodesic ref(obs, c.exits[0]);
    glm::ivec2 cc = c.grid.cellOf(p);
    int i = c.grid.index(cc.x, cc.y);
    std::printf("%s: cell (%d, %d) centre (%.3f, %.3f): D %.4f, reference %.4f, exit %d, class %d, out 0x%02x\n", c.name.c_str(), cc.x, cc.y,
                c.grid.centre(i).x, c.grid.centre(i).y, f.dist[size_t(i)], ref(glm::dvec2(c.grid.centre(i))), f.exitId[size_t(i)], f.cls[size_t(i)], f.out[size_t(i)]);
    for (int k = 0; k < 40 && i >= 0; ++k) {
        const int an = f.anchor[size_t(i)];
        std::printf("  -> anchor %d (%.3f, %.3f) D %.4f, seg %.4f, line legal %d, exit region %d\n", an, c.grid.centre(an).x, c.grid.centre(an).y,
                    f.dist[size_t(an)], glm::length(c.grid.centre(i) - c.grid.centre(an)), int(nav::lineLegal(f, i, an)), f.exitRegion[size_t(an)]);
        if (an == i) break;
        i = an;
    }
    std::printf("LoS checks %lld, fallbacks %lld\n", f.losChecks, f.losFallbacks);
    return 0;
}

// --- trace (diagnostics): the routed seat spawn on the CPU reference; one agent's state per step and its nearest neighbours ---
// A copy of the shader directory with DT / k in physics.comp (run_experiment's dtVariant; the line follows #version)
fs::path dtVariant(const fs::path& shaderDir, int k) {
    const fs::path dir = processTempPath("swarm_shaders_navprobe_dt" + std::to_string(k));
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
    char b[96];
    std::snprintf(b, sizeof b, "#undef DT\n#define DT %.9g\n", double(DT / float(k)));
    src.insert(src.find('\n') + 1, b);
    std::ofstream(dir / "physics.comp", std::ios::binary | std::ios::trunc) << src;
    return dir;
}

int runTrace(const bench::Args& a) {
    const Venue& v = venueByName(a.get("venue", "S"));
    const SeatedLayout& L = v.layout;
    const int agent = a.getInt("agent", 0), from = a.getInt("from", 0), to = a.getInt("to", 100);
    const double load = std::stod(a.get("load", "1"));
    const int nBuf = [&] { int b = 256; while (b < int(std::lround(load * double(seated::seats(v.layout).size())))) b *= 2; return b; }();   // the venue's buffer
    const int dtDiv = a.getInt("dt-div", 1);
    const bool gpu = a.get("engine", "cpu") == "gpu" || dtDiv > 1;
    std::vector<int> agents;
    {
        std::stringstream ss(a.get("agents", std::to_string(agent)));
        for (std::string t; std::getline(ss, t, ',');) agents.push_back(std::stoi(t));
    }
    if (gpu) bench::createHiddenContext("nav_probe");
    const ModelOptions mo = modelOptionsOf(a, v);
    std::printf("model: %s\n", modelOptionsLabel(v, mo).c_str());
    std::unique_ptr<CrowdSim> gsim;
    CpuCrowdSim cpu(v, mo, {}, 0, CpuCrowdSim::SortMode::Counting);
    const std::vector<GpuBoid> spawn = spawnSeatedCrowd(v, nBuf, load, 1337);
    const fs::path shaders = dtDiv > 1 ? dtVariant(resolveAsset("shaders"), dtDiv) : resolveAsset("shaders");
    if (gpu) { gsim = std::make_unique<CrowdSim>(shaders, nBuf, v, mo); gsim->upload(spawn); }
    else cpu.setState(spawn);
    std::vector<GpuBoid> gstate;
    std::vector<uint32_t> assign;   // the exits the last step steered to (queue-aware)
    auto stepAll = [&]() {
        if (gpu) {
            gsim->step(0);
            gstate = bench::readBuffer<GpuBoid>(gsim->currentStateBuffer(), size_t(nBuf));
            if (gsim->assignBuffer()) assign = bench::readBuffer<uint32_t>(gsim->assignBuffer(), size_t(nBuf));
        } else {
            cpu.step();
            assign = cpu.assignedExits();
        }
    };
    auto state = [&]() -> const std::vector<GpuBoid>& { return gpu ? gstate : cpu.state(); };
    const nav::Field& f = nav::forVenue(v);
    auto rel = [&](glm::vec2 p) {
        const glm::vec2 fo = seated::fold(p);
        return glm::vec2(float(units::metres(fo.x - L.gangwayLo)), float(units::metres(fo.y - L.row0)));
    };
    for (int s = 1; s <= to; ++s) {
        stepAll();
        if (s < from) continue;
        for (const int agent : agents) {
        const GpuBoid& b = state()[size_t(agent)];
        if (b.position.w == 0.0f) { std::printf("step %d #%d: left\n", s, agent); continue; }
        const glm::vec2 r = rel(glm::vec2(b.position));
        const glm::vec2 e = goalOf(v, mo, assign, size_t(agent), glm::vec3(b.position));
        const glm::vec2 fe = seated::fold(glm::vec2(b.position) + e * 0.001f) - seated::fold(glm::vec2(b.position));
        const uint8_t c = gpu ? uint8_t(0) : cpu.contacts()[size_t(agent)];
        const glm::vec3 w = seated::wall(L, glm::vec3(b.position) + glm::vec3(0, 0, L.wallAbove), 0.02f);
        const glm::vec2 fv = seated::fold(glm::vec2(b.position) + glm::vec2(b.velocity) * 0.001f) - seated::fold(glm::vec2(b.position));
        std::printf("step %d #%d: lat-gLo %+.4f dep-row0 %.4f z %.4f | v %.3f m/s (%+.3f, %+.3f, z %+.3f) | e_goal folded (%+.2f, %+.2f) | contacts%s%s%s%s%s | wall %.4f m",
                    s, agent, r.x, r.y, units::metres(b.position.z), units::metresPerSecond(glm::length(glm::vec2(b.velocity))),
                    units::metresPerSecond(fv.x * 1000.0f), units::metresPerSecond(fv.y * 1000.0f), units::metresPerSecond(b.velocity.z), fe.x * 1000.0f, fe.y * 1000.0f,
                    c & CpuCrowdSim::CONTACT_FLOOR ? " floor" : "", c & CpuCrowdSim::CONTACT_WALL ? " wall" : "", c & CpuCrowdSim::CONTACT_AGENT ? " agent" : "",
                    c & CpuCrowdSim::CONTACT_STEP_UP ? " STEP-UP" : "", c & CpuCrowdSim::CONTACT_SWEEP ? " sweep" : "", w.z < 1e8f ? units::metres(w.z) : -1.0);
        // nearest three neighbours
        std::vector<std::pair<float, int>> nb;
        for (int j = 0; j < nBuf; ++j) {
            const GpuBoid& o = state()[size_t(j)];
            if (j == agent || o.position.w == 0.0f) continue;
            nb.push_back({ glm::length(glm::vec3(o.position) - glm::vec3(b.position)), j });
        }
        std::sort(nb.begin(), nb.end());
        for (size_t k = 0; k < std::min<size_t>(3, nb.size()); ++k) {
            const GpuBoid& o = state()[size_t(nb[k].second)];
            const glm::vec2 ro = rel(glm::vec2(o.position));
            std::printf(" | #%d d %.3f (%+.3f, %.3f, z %.3f)", nb[k].second, units::metres(nb[k].first), ro.x, ro.y, units::metres(o.position.z));
        }
        std::printf("\n");
        }
    }
    if (dtDiv > 1) fs::remove_all(shaders);
    return 0;
}

// --- timing ---
int runTiming(const bench::Args& a) {
    const Venue& v = venueByName(a.get("venue", "S"));
    const SeatedLayout& L = v.layout;
    const int steps = a.getInt("steps", 250), calls = a.getInt("calls", 64), reps = a.getInt("reps", 15), invocations = 262144;
    bench::createHiddenContext("nav_probe");
    const std::string throttle = bench::optOutOfPowerThrottling();
    const fs::path shaderDir = resolveAsset("shaders");
    const nav::Field& f = nav::forVenue(v);
    // The routed state after 'steps' steps of the full seat spawn (GPU)
    const int nBuf = 4096;
    std::vector<GpuBoid> st;
    {
        CrowdSim sim(shaderDir, nBuf, v);
        sim.upload(spawnSeatedCrowd(v, nBuf, 1.0, 1337));
        for (int i = 0; i < steps; ++i) sim.step(0);
        st = bench::readBuffer<GpuBoid>(sim.currentStateBuffer(), size_t(nBuf));
    }
    std::vector<glm::vec4> agents;
    for (const GpuBoid& b : st)
        if (b.position.w != 0.0f) agents.push_back(b.position);
    // e_goal evaluations of one step (physics.comp's predict pass): one for the agent itself, one for each neighbour within R_PERC
    // that is ahead in its lane and nearer than the nearest such one met so far (the mutual-standoff test). The order depends on
    // the cell order; counted here: every in-lane neighbour ahead (an upper bound) and the agents with at least one (a lower bound)
    long inLane = 0, withOne = 0, viaFit = 0;
    for (size_t i = 0; i < agents.size(); ++i) {
        const glm::vec3 p(agents[i]);
        const glm::vec2 e = nav::goal(f, L, p);
        const glm::ivec2 own = f.grid.cellOf(glm::vec2(p));
        viaFit += nav::directionCell(f, glm::vec2(p)) != f.grid.index(own.x, own.y);
        long k = 0;
        for (size_t j = 0; j < agents.size(); ++j) {
            if (j == i) continue;
            const glm::vec3 off = p - glm::vec3(agents[j]);
            const float d2 = glm::dot(glm::vec2(off), glm::vec2(off));
            if (d2 >= R_PERC2) continue;
            if (-glm::dot(glm::vec2(off), e) > 0.0f && std::abs(off.x * e.y - off.y * e.x) < BODY_DIAM) ++k;
        }
        inLane += k;
        withOne += k > 0;
    }
    // The @nav block of physics.comp on the venue's preamble; each invocation calls the function 'calls' times along a short walk
    std::string phys;
    {
        std::ifstream pf(shaderDir / "physics.comp");
        std::stringstream ss;
        ss << pf.rdbuf();
        phys = ss.str();
    }
    const size_t b0 = phys.find("// @nav-begin"), b1 = phys.find("// @nav-end");
    if (b0 == std::string::npos || b1 == std::string::npos) throw std::runtime_error("physics.comp has no @nav block");
    auto program = [&](const std::string& expr) {
        const fs::path tmp = processTempPath("swarm_nav_timing.comp");
        std::ofstream(tmp) << "#version 430 core\n" + phys.substr(b0, b1 - b0) +
            "layout(local_size_x = 64) in;\n"
            "layout(std430, binding = 5) buffer P { vec4 pts[]; };\n"
            "layout(std430, binding = 6) buffer R { vec2 outs[]; };\n"
            "uniform int count; uniform int calls;\n"
            "void main() { uint i = gl_GlobalInvocationID.x; if (i >= uint(count)) return; vec3 p = pts[i].xyz; vec2 acc = vec2(0.0);\n"
            "  for (int c = 0; c < calls; ++c) { vec2 e = " + expr + "; acc += e; p.xy += vec2(2e-5) * (e + vec2(0.3, -0.2)); }\n"
            "  outs[i] = acc; }\n";
        const GLuint prog = loadComputeProgram(tmp, {}, &v);
        fs::remove(tmp);
        return prog;
    };
    std::vector<glm::vec4> pts(static_cast<size_t>(invocations));
    for (size_t i = 0; i < pts.size(); ++i) pts[i] = agents[i % agents.size()];
    auto makeBuf = [](const void* data, size_t bytes) {
        GLuint b;
        glGenBuffers(1, &b);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, b);
        glBufferData(GL_SHADER_STORAGE_BUFFER, GLsizeiptr(bytes), data, GL_DYNAMIC_COPY);
        return b;
    };
    const std::vector<GpuNavCell> table = nav::gpuCells(f);
    const GLuint bp = makeBuf(pts.data(), pts.size() * sizeof(glm::vec4)), bo = makeBuf(nullptr, pts.size() * sizeof(glm::vec2)),
                 bn = makeBuf(table.data(), table.size() * sizeof(GpuNavCell));
    struct Case { const char* name; const char* expr; double median = 0, min = 0, max = 0; };
    Case cases[] = { { "navGoal (e_goal: the field's direction, the wall projection)", "navGoal(p)" },
                     { "navDirection (the field's direction alone)", "navDirection(p.xy)" },
                     { "baseline (the loop without a call)", "vec2(0.3, 0.1)" } };
    GLuint q;
    glGenQueries(1, &q);
    for (Case& c : cases) {
        const GLuint prog = program(c.expr);
        glUseProgram(prog);
        glUniform1i(glGetUniformLocation(prog, "count"), invocations);
        glUniform1i(glGetUniformLocation(prog, "calls"), calls);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, bp);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, bo);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_NAV, bn);
        std::vector<double> ns;
        for (int rep = 0; rep < reps + 3; ++rep) {
            glBeginQuery(GL_TIME_ELAPSED, q);
            glDispatchCompute(GLuint((invocations + 63) / 64), 1, 1);
            glEndQuery(GL_TIME_ELAPSED);
            GLuint64 t = 0;
            glGetQueryObjectui64v(q, GL_QUERY_RESULT, &t);
            if (rep >= 3) ns.push_back(double(t) / (double(invocations) * calls));
        }
        const bench::Stats sts = bench::stats(ns);
        c.median = sts.median;
        c.min = sts.min;
        c.max = sts.max;
        glDeleteProgram(prog);
    }
    glDeleteQueries(1, &q);
    for (GLuint b : { bp, bo, bn }) glDeleteBuffers(1, &b);
    const double goalNs = cases[0].median - cases[2].median;
    const double upper = double(agents.size() + size_t(inLane)), lower = double(agents.size() + size_t(withOne));
    Report r;
    r.line("# Venue " + std::string(v.name) + ": GPU cost of e_goal from the navigation field");
    r.line("");
    r.line(header("timing") + " | " + bench::glRenderer() + " | " + bench::glDriver() + " | " + throttle);
    r.line("");
    r.line("Positions: the " + std::to_string(agents.size()) + " active agents of the routed state after " + std::to_string(steps) +
           " steps of the full seat spawn (GPU), repeated to " + std::to_string(invocations) + " invocations; each calls the function " +
           std::to_string(calls) + " times along a short walk from its position (dependent inputs), GL_TIME_ELAPSED per dispatch, " +
           std::to_string(reps) + " repetitions after 3 warm-up dispatches. ns per call = time / (invocations x calls): a throughput over the "
           "whole GPU, not one call's latency. physics.comp's own @nav block on the venue's preamble.");
    r.line("");
    r.line("| function | median ns/call | min | max |");
    r.line("|---|---:|---:|---:|");
    for (const Case& c : cases) r.line("| " + std::string(c.name) + " | " + fmt("%.4f", c.median) + " | " + fmt("%.4f", c.min) + " | " + fmt("%.4f", c.max) + " |");
    r.line("");
    r.line("e_goal evaluations in one step at this state (physics.comp's predict pass): one per active agent (" + std::to_string(agents.size()) +
           ") plus one per in-lane neighbour ahead that the mutual-standoff test reaches (the nearest met so far: order-dependent): between " +
           fmt("%.0f", lower) + " (one such neighbour per agent that has any: " + std::to_string(withOne) + ") and " + fmt("%.0f", upper) +
           " (every in-lane neighbour ahead: " + std::to_string(inLane) + "). " + std::to_string(viaFit) + " agents' centres lie in a NOFIT cell "
           "(their direction comes from the nearest FIT neighbour).");
    r.line("");
    r.line("Estimated e_goal time per step = evaluations x (navGoal - baseline) = " + fmt("%.4f", lower * goalNs * 1e-6) + " to " +
           fmt("%.4f", upper * goalNs * 1e-6) + " ms (throughput estimate; in the step the calls overlap the neighbour loop's other work).");
    r.write(fs::path(a.get("out", "out/results/nav_s")) / "nav_timing.md");
    std::printf("navGoal %.4f ns/call, navDirection %.4f, baseline %.4f; evaluations per step %.0f - %.0f -> %.4f - %.4f ms\n", cases[0].median,
                cases[1].median, cases[2].median, lower, upper, lower * goalNs * 1e-6, upper * goalNs * 1e-6);
    return 0;
}

// --- cells (diagnostics) ---
int runCells(const bench::Args& a) {
    const Venue& v = venueByName(a.get("venue", "S"));
    const SeatedLayout& L = v.layout;
    const nav::Field& f = nav::forVenue(v);
    const nav::Grid& g = f.grid;
    const glm::vec2 c(float(std::stod(a.get("x", "0")) / WORLD_SCALE_M_PER_UNIT), float(std::stod(a.get("y", "0")) / WORLD_SCALE_M_PER_UNIT));
    const int n = a.getInt("n", 3);
    auto rel = [&](glm::vec2 p) {
        const glm::vec2 fo = seated::fold(p);
        return glm::vec2(float(units::metres(fo.x - L.gangwayLo)), float(units::metres(fo.y - L.row0)));
    };
    const glm::ivec2 c0 = g.cellOf(c);
    for (int dy = n; dy >= -n; --dy)
        for (int dx = -n; dx <= n; ++dx) {
            const glm::ivec2 q = c0 + glm::ivec2(dx, dy);
            if (q.x < 0 || q.y < 0 || q.x >= g.res || q.y >= g.res) continue;
            const int i = q.x + q.y * g.res;
            const glm::vec2 rc = rel(g.centre(i)), ra = rel(f.anchorXY[size_t(i)]);
            std::printf("cell (%d, %d) centre (%+.3f, %.3f) %s z %.3f  dist %.3f m  anchor (%+.3f, %.3f) exit %d  sees:", dx, dy, rc.x, rc.y,
                        f.cls[size_t(i)] == uint8_t(nav::Class::FIT) ? "FIT  " : (f.cls[size_t(i)] == uint8_t(nav::Class::NOFIT) ? "NOFIT" : "other"),
                        units::metres(f.floorZ[size_t(i)]), f.reachable(size_t(i)) ? units::metres(f.dist[size_t(i)]) : -1.0, ra.x, ra.y,
                        int(f.exitId[size_t(i)]));
            for (int ny = -1; ny <= 1; ++ny)
                for (int nx = -1; nx <= 1; ++nx) {
                    if (!nx && !ny) continue;
                    const glm::ivec2 m = q + glm::ivec2(nx, ny);
                    if (m.x < 0 || m.y < 0 || m.x >= g.res || m.y >= g.res) continue;
                    const int j = m.x + m.y * g.res;
                    if (f.anchor[size_t(j)] < 0 || f.anchor[size_t(j)] == f.anchor[size_t(i)]) continue;
                    std::printf(" [%+d%+d: %s]", nx, ny, nav::lineLegal(f, i, f.anchor[size_t(j)]) ? "yes" : "no");
                }
            std::printf("\n");
        }
    return 0;
}

// --- jam (diagnostics) ---
int runJam(const bench::Args& a) {
    const Venue& v = venueByName(a.get("venue", "S"));
    const SeatedLayout& L = v.layout;
    const double load = std::stod(a.get("load", "1"));
    const int nBuf = [&] { int b = 256; while (b < int(std::lround(load * double(seated::seats(v.layout).size())))) b *= 2; return b; }();   // the venue's buffer
    const int dtDiv = a.getInt("dt-div", 1);
    const bool gpu = a.get("engine", "gpu") == "gpu" || dtDiv > 1;
    const glm::vec2 c(float(std::stod(a.get("x", "0")) / WORLD_SCALE_M_PER_UNIT), float(std::stod(a.get("y", "0")) / WORLD_SCALE_M_PER_UNIT));
    const float r = float(std::stod(a.get("r", "3")) / WORLD_SCALE_M_PER_UNIT);
    std::vector<int> steps;
    {
        std::stringstream ss(a.get("steps", "100"));
        for (std::string t; std::getline(ss, t, ',');) steps.push_back(std::stoi(t));
    }
    if (gpu) bench::createHiddenContext("nav_probe");
    const ModelOptions mo = modelOptionsOf(a, v);
    std::printf("model: %s\n", modelOptionsLabel(v, mo).c_str());
    std::unique_ptr<CrowdSim> gsim;
    CpuCrowdSim cpu(v, mo, {}, 0, CpuCrowdSim::SortMode::Counting);
    const std::vector<GpuBoid> spawn = spawnSeatedCrowd(v, nBuf, load, 1337);
    const fs::path shaders = dtDiv > 1 ? dtVariant(resolveAsset("shaders"), dtDiv) : resolveAsset("shaders");
    if (gpu) { gsim = std::make_unique<CrowdSim>(shaders, nBuf, v, mo); gsim->upload(spawn); }
    else cpu.setState(spawn);
    auto rel = [&](glm::vec2 p) {
        const glm::vec2 fo = seated::fold(p);
        return glm::vec2(float(units::metres(fo.x - L.gangwayLo)), float(units::metres(fo.y - L.row0)));
    };
    int done = 0;
    for (const int target : steps) {
        for (; done < target; ++done) { if (gpu) gsim->step(0); else cpu.step(); }
        const std::vector<GpuBoid> st = gpu ? bench::readBuffer<GpuBoid>(gsim->currentStateBuffer(), size_t(nBuf)) : cpu.state();
        const std::vector<uint32_t> assign = gpu ? (gsim->assignBuffer() ? bench::readBuffer<uint32_t>(gsim->assignBuffer(), size_t(nBuf))
                                                                          : std::vector<uint32_t>{})
                                                 : cpu.assignedExits();
        std::vector<glm::vec2> eg(st.size(), glm::vec2(0.0f));
        for (size_t i = 0; i < st.size(); ++i)
            if (st[i].position.w != 0.0f) eg[i] = goalOf(v, mo, assign, i, glm::vec3(st[i].position));
        std::vector<int> leader(st.size(), -1);
        std::vector<float> sAh(st.size(), 1e9f);
        std::vector<int> mutualYield(st.size(), 0);
        for (size_t i = 0; i < st.size(); ++i) {
            if (st[i].position.w == 0.0f) continue;
            const glm::vec3 p(st[i].position);
            for (size_t j = 0; j < st.size(); ++j) {
                if (j == i || st[j].position.w == 0.0f) continue;
                const glm::vec3 offset = p - glm::vec3(st[j].position);
                const float dxy2 = glm::dot(glm::vec2(offset), glm::vec2(offset));
                if (dxy2 >= R_PERC2) continue;
                const float ahead = -glm::dot(glm::vec2(offset), eg[i]);
                const float lateral = std::abs(offset.x * eg[i].y - offset.y * eg[i].x);
                const float dxy = std::sqrt(dxy2);
                if (ahead > 0.0f && lateral < BODY_DIAM && dxy < sAh[i]) {
                    const glm::vec2 eo = eg[j];
                    const float aheadOther = glm::dot(glm::vec2(offset), eo);
                    const bool mutual = aheadOther > 0.0f && std::abs(offset.x * eo.y - offset.y * eo.x) < BODY_DIAM;
                    if (!mutual || ahead > aheadOther || (ahead == aheadOther && i > j)) { sAh[i] = dxy; leader[i] = int(j); mutualYield[i] = mutual; }
                }
            }
        }
        std::printf("step %d (t %.1f s): agents within %.2f m of (%.2f, %.2f) m\n", target, target * DT_REAL_S / dtDiv, units::metres(r),
                    units::metres(c.x), units::metres(c.y));
        std::printf("  agent  lat-gLo  dep-row0      z  | speed  e_goal(folded)  | leader  s[m]   v_des  mutual\n");
        std::vector<int> inside;
        for (size_t i = 0; i < st.size(); ++i)
            if (st[i].position.w != 0.0f && glm::length(glm::vec2(st[i].position) - c) < r) inside.push_back(int(i));
        for (const int i : inside) {
            const GpuBoid& b = st[size_t(i)];
            const glm::vec2 q = rel(glm::vec2(b.position));
            const glm::vec2 fe = seated::fold(glm::vec2(b.position) + eg[size_t(i)] * 0.001f) - seated::fold(glm::vec2(b.position));
            const float vDes = std::clamp((sAh[size_t(i)] - BODY_DIAM) * HEADWAY_RATE, 0.0f, V_MAX) * glm::length(eg[size_t(i)]);
            std::printf("  %5d  %+7.3f  %8.3f  %6.3f | %5.3f  (%+.2f, %+.2f)  | %6d  %5.3f  %5.3f  %s\n", i, q.x, q.y, units::metres(b.position.z),
                        units::metresPerSecond(glm::length(glm::vec2(b.velocity))), fe.x * 1000.0f, fe.y * 1000.0f, leader[size_t(i)],
                        leader[size_t(i)] >= 0 ? units::metres(sAh[size_t(i)]) : -1.0, units::metresPerSecond(vDes), mutualYield[size_t(i)] ? "yes" : "");
        }
        // the chains' roots (an agent without a leader) and leader cycles
        std::vector<int> roots;
        for (const int i : inside) {
            int k = i, n = 0;
            while (leader[size_t(k)] >= 0 && n++ < 256) k = leader[size_t(k)];
            if (leader[size_t(k)] < 0 && std::find(roots.begin(), roots.end(), k) == roots.end()) roots.push_back(k);
        }
        for (const int i : roots) {
            const GpuBoid& b = st[size_t(i)];
            const glm::vec2 q = rel(glm::vec2(b.position));
            const glm::vec2 fe = seated::fold(glm::vec2(b.position) + eg[size_t(i)] * 0.001f) - seated::fold(glm::vec2(b.position));
            const glm::vec3 w = seated::wall(L, glm::vec3(b.position) + glm::vec3(0, 0, L.wallAbove), 0.02f);
            std::printf("  root %5d at (%.3f, %.3f) m: lat-gLo %+.3f dep-row0 %.3f z %.3f | speed %.3f | e_goal (%+.2f, %+.2f) | v (%+.3f, %+.3f) m/s | wall %.4f m (n %+.2f %+.2f)",
                        i, units::metres(b.position.x), units::metres(b.position.y), q.x, q.y, units::metres(b.position.z),
                        units::metresPerSecond(glm::length(glm::vec2(b.velocity))), fe.x * 1000.0f, fe.y * 1000.0f,
                        units::metresPerSecond(b.velocity.x), units::metresPerSecond(b.velocity.y), w.z < 1e8f ? units::metres(w.z) : -1.0, w.x, w.y);
            std::vector<std::pair<float, int>> nb;
            for (size_t j = 0; j < st.size(); ++j)
                if (int(j) != i && st[j].position.w != 0.0f) nb.push_back({ glm::length(glm::vec3(st[j].position) - glm::vec3(b.position)), int(j) });
            std::sort(nb.begin(), nb.end());
            for (size_t k = 0; k < std::min<size_t>(4, nb.size()); ++k) {
                const glm::vec2 ro = rel(glm::vec2(st[size_t(nb[k].second)].position));
                std::printf(" | #%d d %.3f (%+.3f, %.3f, z %.3f)", nb[k].second, units::metres(nb[k].first), ro.x, ro.y, units::metres(st[size_t(nb[k].second)].position.z));
            }
            std::printf("\n");
        }
        for (const int i : inside) {
            std::vector<int> chain{ i };
            int k = leader[size_t(i)];
            while (k >= 0 && chain.size() < 64) {
                const auto it = std::find(chain.begin(), chain.end(), k);
                if (it != chain.end()) {
                    if (it == chain.begin()) {
                        std::printf("  leader cycle:");
                        for (const int m : chain) std::printf(" %d", m);
                        std::printf("\n");
                    }
                    break;
                }
                chain.push_back(k);
                k = leader[size_t(k)];
            }
        }
    }
    if (dtDiv > 1) fs::remove_all(shaders);
    return 0;
}

// --- validate ---
int runValidate(const bench::Args& a) {
    const Venue& v = venueByName(a.get("venue", "S"));
    const SeatedLayout& L = v.layout;
    const std::string lower = v.name[0] == 'S' ? "s" : v.name[0] == 'M' ? "m" : "l";
    const fs::path out = a.get("out", "out/results/nav_" + lower);   // out/results/nav_m, nav_l
    const int sample = a.getInt("sample", 0);                    // the descent from a seeded sample of seats (0: all)
    const unsigned sampleSeed = unsigned(a.getInt("seed", 7));
    Report r;
    bool allOk = true;
    r.line("# Venue " + std::string(v.name) + ": navigation field validation");
    r.line("");
    r.line(header("validate"));
    r.line("");
    r.line("## (a) Known answers");
    r.line("");
    r.line("Rectangle worlds (nav::RectGeometry, point agents: a cell is FIT where its centre is outside every wall), the same");
    r.line("builder (nav::build) on a 0.05 m grid whose cell edges lie on the walls; the exit regions start on a line of cell centres.");
    r.line("Reference: the exact geodesic distance (a shortest path over the visibility graph of the obstacles' corners, the last leg");
    r.line("to the nearest point of the exit region; a ledge is an obstacle for paths on the floor and none for a path that starts on");
    r.line("it). Compared over every cell of the room's (corridor's) interior; limit: one cell (0.05 m), two for the ledge (its floor");
    r.line("path bends at two corners; a grid path bends at a cell centre, up to h/sqrt(2) from the true corner).");
    r.line("");
    r.line("| case | cells | without a path | max \\|D - D_ref\\| | mean | beyond the limit | worst at | result |");
    r.line("|---|---:|---:|---:|---:|---:|---|---|");
    std::vector<nav_check::KnownResult> known;
    for (const nav_check::KnownCase& c : nav_check::knownCases()) {
        const nav_check::KnownResult k = nav_check::runKnown(c);
        known.push_back(k);
        allOk &= k.ok;
        r.line("| " + c.name + " | " + std::to_string(k.compared) + " | " + std::to_string(k.unreachable) + " | " + fmt("%.4f m", k.maxErr) + " (" +
               fmt("%.2f", k.maxErrCells) + " cells) | " + fmt("%.4f m", k.meanErr) + " | " + std::to_string(k.beyond) + " | (" + fmt("%.3f", k.worst.x) +
               ", " + fmt("%.3f", k.worst.y) + ") | " + (k.ok ? "PASS" : "FAIL") + " |");
    }
    r.line("");
    for (const nav_check::KnownCase& c : nav_check::knownCases()) r.line("- " + c.name + ": " + c.description + ".");
    r.line("");
    for (const nav_check::KnownResult& k : known) {
        if (k.splitA + k.splitB > 0)
            r.line("Two doors: " + std::to_string(k.splitA) + " cells lead to door A, " + std::to_string(k.splitB) + " to door B; " +
                   std::to_string(k.splitMismatch) + " take the farther one by the reference, all within " + fmt("%.4f m", k.splitMaxMargin) +
                   " of the equal-distance line (|D_A - D_B|; limit two cells, 0.10 m): the split lies where the two paths are equal.");
        if (k.ledgeDetourMean > 0.0)
            r.line("One-way ledge: the floor cells left of the ledge route around it, on average " + fmt("%.2f m", k.ledgeDetourMean) +
                   " longer than the straight line over it (the reference treats the ledge as an obstacle for them and matches); the ledge's "
                   "own cells step straight down off it.");
    }
    r.line("");

    const nav::Field& f = nav::forVenue(v);
    const nav_check::VenueResult vr = nav_check::runVenue(v, f, sample, sampleSeed);
    const double cellM2 = nav::CELL_M * nav::CELL_M;
    r.line("## (b) Venue " + std::string(v.name) + ": paths");
    r.line("");
    char hashText[32];
    std::snprintf(hashText, sizeof hashText, "%016llx", (unsigned long long)nav::contentHash(f));
    r.line("Field: " + std::string(f.fromCache ? "loaded from the cache" : "built") + fmt(" (%.2f s)", f.buildSeconds) + ", content hash " + hashText + ".");
    r.line("");
    r.line("- seats: " + std::to_string(vr.seats) + "; with a finite distance: " + std::to_string(vr.seats - vr.seatsNoPath) + "; their cell FIT: " +
           std::to_string(vr.seats - vr.seatsNotFit) + ".");
    r.line("- cells an agent can walk to from a seat (forward over the legal directed edges, FIT and NOFIT): " + std::to_string(vr.walkable) + " (" +
           fmt("%.1f m^2", vr.walkable * cellM2) + "); of them without a path to an exit: " + std::to_string(vr.walkableNoPath) + ".");
    r.line("");
    r.line("Unreachable floor (no legal path to an exit), by kind:");
    r.line("");
    r.line("| kind | cells | m^2 |");
    r.line("|---|---:|---:|");
    for (const auto& u : vr.unreachable) r.line("| " + u.kind + " | " + std::to_string(u.cells) + " | " + fmt("%.1f", u.cells * cellM2) + " |");
    const bool bOk = vr.seatsNoPath == 0 && vr.seatsNotFit == 0 && vr.walkableNoPath == 0;
    allOk &= bOk;
    r.line("");
    r.line(std::string("(b): ") + (bOk ? "PASS" : "FAIL") + " (every seat has a path; no cell an agent can reach is without one)");
    r.line("");
    r.line(sample > 0 && sample < vr.seats ? "## (c) Descent from a seeded sample of " + std::to_string(sample) + " seats (mt19937 seed " + std::to_string(sampleSeed) + ")"
                                            : std::string("## (c) Descent from every seat"));
    r.line("");
    r.line("A point at each seat's spawn position follows e_goal (nav::goal at the rest height, the GPU's navGoal) in steps of 0.05 m until");
    r.line("it passes the outer wall's outer face (the exit test). Limit: no stall, path <= 1.2 x the field's distance at the seat.");
    r.line("");
    r.line("- descents " + std::to_string(vr.descents) + ", stalls " + std::to_string(vr.stalls) + ", longest " + std::to_string(vr.maxSteps) + " steps;");
    r.line("- path / field distance: mean " + fmt("%.4f", vr.meanRatio) + ", worst " + fmt("%.4f", vr.worstRatio) + " (seat " + std::to_string(vr.worstSeat) +
           ": path " + fmt("%.2f m", vr.worstPathM) + ", field " + fmt("%.2f m", vr.worstFieldM) + ");");
    r.line("- information (not a criterion: a point has no contacts): steps that are not a legal move (seated geometry: fence, drop, rise, the step-up");
    r.line("  scan): " + std::to_string(vr.illegalSteps) + ", the longest part beyond the face " + fmt("%.4f m", vr.maxOvershootM) + ";");
    for (const auto& [k, c] : vr.illegalWhere) r.line("  - " + k + ": " + std::to_string(c));
    const bool cOk = vr.stalls == 0 && vr.worstRatio <= 1.2;
    allOk &= cOk;
    r.line("");
    r.line(std::string("(c): ") + (cOk ? "PASS" : "FAIL"));
    r.line("");
    r.line("## (d) Exit choice (each seat's nearest exit)");
    r.line("");
    r.line("| exit | seats |");
    r.line("|---|---:|");
    long doors = 0, avenues = 0;
    for (int e = 0; e < f.exitCount; ++e) {
        r.line("| " + f.exitNames[size_t(e)] + " | " + std::to_string(vr.perExit[size_t(e)]) + " |");
        (e < 4 ? avenues : doors) += vr.perExit[size_t(e)];
    }
    r.line("");
    r.line("Rear doors: " + std::to_string(doors) + " seats (" + fmt("%.1f%%", 100.0 * double(doors) / double(vr.seats)) + "), avenues: " +
           std::to_string(avenues) + " (" + fmt("%.1f%%", 100.0 * double(avenues) / double(vr.seats)) + ").");
    r.line("");
    r.line("| row | avenue | door |");
    r.line("|---:|---:|---:|");
    for (int k = 0; k < L.rows; ++k) r.line("| " + std::to_string(k) + " | " + std::to_string(vr.perRow[size_t(k)][0]) + " | " + std::to_string(vr.perRow[size_t(k)][1]) + " |");
    r.line("");
    r.line("## (e) The 28-seat gangway rule");
    r.line("");
    r.line("Seats per row in each wing: the dead-end segment (side wall .. straight gangway: one gangway, limit " +
           std::to_string(v.params.maxSeatsDeadEnd) + ") and the segment between the straight and the corner gangway (limit " +
           std::to_string(v.params.maxSeatsBetweenGangways) + ").");
    r.line("");
    r.line("| row | dead-end segment | between gangways | over 28 |");
    r.line("|---:|---:|---:|---|");
    for (int k = 0; k < L.rows; ++k) {
        const seated::RowSeats& rs = vr.rowSeats[size_t(k)];
        r.line("| " + std::to_string(k) + " | " + std::to_string(rs.deadEnd) + " | " + std::to_string(rs.between) + " | " + (rs.between > 28 ? "**FLAG**" : "no") + " |");
    }
    r.line("");
    r.line("Maximum consecutive seats between two gangways: " + std::to_string(vr.maxBetween) + " (rows over 28: " + std::to_string(vr.rowsOver28) +
           "); in a dead-end segment: " + std::to_string(vr.maxDeadEnd) + ".");
    r.line("");
    r.line(std::string("**Validation: ") + (allOk ? "ALL PASS" : "FAILED") + "**");
    r.write(out / "validation.md");
    return allOk ? 0 : 1;
}

// --- choice: the exit choice's candidate table, its memory and accuracy ---
int runChoice(const bench::Args& a) {
    const Venue& v = venueByName(a.get("venue", "S"));
    const fs::path out = a.get("out", "out/results/nav_s");
    Report rep;
    rep.line("# Exit choice: candidate table of venue " + std::string(v.name));
    rep.line("");
    rep.line(header("choice"));
    rep.line("");
    const nav::Field& f = nav::forVenue(v);   // the nearest-exit field and the grid
    std::vector<nav::ExitField> all;
    const nav::ChoiceTable t = nav::buildChoiceTable(nav::SeatedGeometry(v.layout), f, &all);
    const size_t n = t.grid.cells();
    const nav::ChoiceTable& cached = nav::choiceForVenue(v);
    char hash[32];
    std::snprintf(hash, sizeof hash, "%016llx", (unsigned long long)nav::choiceContentHash(t));
    rep.line("## Build and memory");
    rep.line("");
    rep.line("- " + std::to_string(t.exitCount) + " per-exit fields (Lazy Theta* from each exit's region alone, nav::lazyThetaStar), " +
             std::to_string(t.grid.res) + " x " + std::to_string(t.grid.res) + " cells of " + fmt("%.3f", nav::CELL_M) + " m, built in " +
             fmt("%.2f", t.buildSeconds) + " s (" + std::to_string(omp_get_max_threads()) + " threads, " SWARM_BUILD_TYPE "); the cache " +
             (nav::choiceContentHash(t) == nav::choiceContentHash(cached) ? "equals" : "DIFFERS FROM") + " this build (content " + hash + ").");
    const double fullS = double(n) * double(t.exitCount) * 8.0, tableS = double(t.bytes());
    const double bigCells = 5000.0 * 5000.0;   // the largest planned venue: outer half-width ~4 model units (125 m), a 250 m domain
    rep.line("- Full per-exit fields at this resolution (anchor + distance, 8 B per cell and exit): venue S " + fmt("%.0f", fullS / 1048576.0) +
             " MB; the largest planned venue (5000^2 cells of 0.05 m, ~40 exits) " + fmt("%.1f", bigCells * 40.0 * 8.0 / 1073741824.0) + " GB.");
    rep.line("- Candidate table (CHOICE_K = " + std::to_string(nav::CHOICE_K) + " candidates per cell, " + std::to_string(sizeof(GpuNavChoiceCell)) + " B per cell): venue S " +
             fmt("%.1f", tableS / 1048576.0) + " MB; the largest planned venue " + fmt("%.0f", bigCells * 32.0 / 1048576.0) +
             " MB (budget 1 GB = 1024 MB). Queue-aware simulations upload the table only (the nearest-exit field, 16 B per cell, is not "
             "needed: the viewer's distance overlay uploads it on demand).");
    rep.line("");
    // Static accuracy: min over the exits' own fields vs the nearest-exit field; candidates per cell
    long reach = 0, mism = 0, kHist[nav::CHOICE_K + 1] = {};
    double maxDiff = 0.0, sumDiff = 0.0;
    for (size_t i = 0; i < n; ++i) {
        const int k = t.candidates(i);
        if (k == 0) continue;
        ++kHist[k];
        if (!f.reachable(i)) { ++mism; continue; }
        ++reach;
        const double d = std::abs(double(nav::slotDist(t, t.at(i), 0)) - double(f.dist[i]));
        maxDiff = std::max(maxDiff, d);
        sumDiff += d;
    }
    long fReach = 0;
    for (size_t i = 0; i < n; ++i) fReach += f.reachable(i);
    rep.line("## Accuracy");
    rep.line("");
    rep.line("- The distances are each exit's exact field (float, no reduced precision or resolution). The nearest candidate against the "
             "nearest-exit field (one search from every exit at once; Lazy Theta*'s paths depend on the expansion order): " +
             std::to_string(reach) + " cells reachable in both (" + std::to_string(fReach) + " in the nearest-exit field, " + std::to_string(mism) +
             " only in the table), |difference| max " + fmt("%.4f", units::metres(maxDiff)) + " m (" + fmt("%.2f", maxDiff / double(t.grid.cell)) +
             " cells), mean " + fmt("%.5f", units::metres(sumDiff / double(std::max(reach, 1L)))) + " m.");
    std::string kh;
    for (int k = 1; k <= nav::CHOICE_K; ++k) kh += (k > 1 ? ", " : "") + std::to_string(k) + ": " + std::to_string(kHist[k]);
    rep.line("- Reachable cells by the number of candidates (" + kh + ").");
    // Per seat: the candidate exits
    const std::vector<seated::Seat> seats = seated::seats(v.layout);
    std::map<std::string, long> setCount;
    long withAvenue = 0;
    std::vector<long> rankOfNearestAvenue(nav::CHOICE_K + 2, 0);
    for (const seated::Seat& s : seats) {
        const size_t c = size_t(nav::choiceCell(t, glm::vec2(s.pos)));
        std::string key;
        int firstAvenue = nav::CHOICE_K + 1;
        for (int k = 0; k < nav::CHOICE_K; ++k) {
            const uint32_t e = nav::slotExit(t.at(c).slot[k]);
            if (e == nav::CHOICE_EMPTY) break;
            key += (k ? " | " : "") + t.exitNames[e];
            if (e < 4 && firstAvenue > nav::CHOICE_K) firstAvenue = k + 1;
        }
        ++setCount[key];
        withAvenue += firstAvenue <= nav::CHOICE_K;
        ++rankOfNearestAvenue[size_t(firstAvenue)];
    }
    rep.line("- Seats with an avenue among their candidates: " + std::to_string(withAvenue) + " of " + std::to_string(seats.size()) +
             " (the nearest avenue is candidate 1 / 2 / 3 / 4 / none: " + std::to_string(rankOfNearestAvenue[1]) + " / " + std::to_string(rankOfNearestAvenue[2]) +
             " / " + std::to_string(rankOfNearestAvenue[3]) + " / " + std::to_string(rankOfNearestAvenue[4]) + " / " + std::to_string(rankOfNearestAvenue[5]) + ").");
    rep.line("");
    rep.line("| candidate exits of a seat (nearest first) | seats |");
    rep.line("|---|---:|");
    std::vector<std::pair<long, std::string>> sets;
    for (const auto& kv : setCount) sets.push_back({ kv.second, kv.first });
    std::sort(sets.rbegin(), sets.rend());
    for (const auto& s : sets) rep.line("| " + s.second + " | " + std::to_string(s.first) + " |");
    rep.line("");

    // Dynamic accuracy: a queue-aware run on the CPU reference; at every evaluation, the best exit over ALL exits (each exit's own field
    // at the agent's cell, the same counts) against the best of the cell's candidates
    if (a.has("run")) {
        const double load = std::stod(a.get("load", "1"));
        const int nBuf = [&] { int b = 256; while (b < int(std::lround(load * double(seated::seats(v.layout).size())))) b *= 2; return b; }();   // the venue's buffer
        const int maxSteps = a.getInt("steps", 3000);
        ModelOptions opts;
        opts.exitChoice = ExitChoice::QueueAware;
        opts.inclineSpeed = a.has("incline");
        CpuCrowdSim cpu(v, opts, {}, 0, CpuCrowdSim::SortMode::Counting);
        const std::vector<GpuBoid> spawn = spawnSeatedCrowd(v, nBuf, load, 1337);
        cpu.setState(spawn);
        const int steps = choiceSteps(DT);
        long evals = 0, outside = 0;
        double maxGain = 0.0, sumGain = 0.0;
        int lastStep = 0;
        for (int s = 1; s <= maxSteps; ++s) {
            const std::vector<GpuBoid>& st = cpu.state();
            const std::vector<uint32_t> asg = cpu.assignedExits();
            const uint32_t step = cpu.choiceStep();
            const std::vector<uint32_t> aheadP = cpu.choiceState().aheadPrefix();   // the queue ahead this step's pass reads
            (void)step;
            long active = 0;
            const bool evalStep = nav::evaluationStep(step, steps);
            for (int id = 0; id < nBuf; ++id) {
                const glm::vec4 p = st[size_t(id)].position;
                if (p.w == 0.0f) continue;
                ++active;
                const size_t c = size_t(nav::choiceCell(t, glm::vec2(p)));
                if (!t.reachable(c)) continue;
                const bool isCand = nav::slotOf(t.at(c), asg[size_t(id)]) >= 0;
                if (isCand && !evalStep) continue;   // evaluated: every agent on an evaluation step, a forced choice any step
                ++evals;
                float bestK = 1e30f, bestAll = 1e30f;
                for (int k = 0; k < nav::CHOICE_K; ++k) {
                    const uint32_t e = nav::slotExit(t.at(c).slot[k]);
                    if (e == nav::CHOICE_EMPTY) break;
                    bestK = std::min(bestK, nav::estimatedTime(t, nav::slotDist(t, t.at(c), k), e, nav::aheadOf(aheadP.data(), e, nav::slotDistQ(t.at(c), k))));
                }
                for (int e = 0; e < t.exitCount; ++e) {
                    const float d = all[size_t(e)].dist[c];
                    if (std::isfinite(d))
                        bestAll = std::min(bestAll, nav::estimatedTime(t, d, uint32_t(e), nav::aheadOf(aheadP.data(), uint32_t(e), uint32_t(std::nearbyint(double(d) / double(t.distQuantum))))));
                }
                if (bestAll < bestK) {
                    ++outside;
                    maxGain = std::max(maxGain, double(bestK - bestAll));
                    sumGain += double(bestK - bestAll);
                }
            }
            if (active == 0) { lastStep = s - 1; break; }
            cpu.step();
            lastStep = s;
        }
        const GpuChoiceCounters& cc = cpu.choiceCounters();
        rep.line("## Candidate limit during a queue-aware evacuation (CPU reference, " + fmt("%.0f", 100.0 * load) + "% load" + (opts.inclineSpeed ? ", incline speed" : "") + ")");
        rep.line("");
        rep.line("- " + std::to_string(lastStep) + " steps" + (lastStep < maxSteps ? " (everyone left)" : " (the step limit)") + "; " + std::to_string(evals) +
                 " evaluations (re-evaluations and forced choices; the pass counted " + std::to_string(cc.evaluations) + ", switches " +
                 std::to_string(cc.switches) + ", forced " + std::to_string(cc.forced) + ").");
        rep.line("- The best exit over all " + std::to_string(t.exitCount) + " exits (each exit's own field at the agent's cell, the same counts) lay outside "
                 "the cell's " + std::to_string(nav::CHOICE_K) + " candidates in " + std::to_string(outside) + " evaluations (" +
                 fmt("%.3f", 100.0 * double(outside) / double(std::max(evals, 1L))) + "%); its estimate was better by " +
                 (outside ? "mean " + fmt("%.1f", sumGain / double(outside)) + " s, max " + fmt("%.1f", maxGain) + " s" : std::string("-")) + ".");
        rep.line("");
    }
    rep.write(out / "choice.md");
    return 0;
}

// --- drive (diagnostics): one agent at (x, y) m driven in a fixed plane direction (dx, dy), CPU reference ---
int runDrive(const bench::Args& a) {
    const Venue& v = venueByName(a.get("venue", "S"));
    const SeatedLayout& L = v.layout;
    const glm::vec2 start(float(units::modelLength(std::stod(a.get("x", "6")))), float(units::modelLength(std::stod(a.get("y", "11.9")))));
    glm::vec2 dir(std::stof(a.get("dx", "1")), std::stof(a.get("dy", "0")));
    dir = glm::normalize(dir);
    ModelOptions mo;
    mo.inclineSpeed = a.getInt("incline", 1) != 0;
    CpuCrowdSim cpu(v, mo, {}, 1, CpuCrowdSim::SortMode::Counting);
    std::vector<GpuBoid> st(256);
    for (GpuBoid& b : st) b.position = glm::vec4(PARK_COORD, PARK_COORD, PARK_COORD, 0.0f);
    st[0].position = glm::vec4(start, seated::floorHeight(L, start) + BODY_RADIUS, 1.0f);
    std::vector<glm::vec2> table(st.size(), glm::vec2(0.0f));
    table[0] = dir;
    cpu.setState(st);
    cpu.setDriveTable(&table);
    const int steps = a.getInt("steps", 40);
    std::printf("start (%.3f, %.3f) m, cell kind %s, floor %.3f m\n", units::metres(start.x), units::metres(start.y),
                seated::cellKindName(seated::cellAt(L, start)), units::metres(seated::floorHeight(L, start)));
    for (int s = 1; s <= steps; ++s) {
        cpu.step();
        const GpuBoid& b = cpu.state()[0];
        const uint8_t c = cpu.contacts()[0];
        std::printf("step %3d: (%.3f, %.3f, %.3f) m, v %.4f m/s (%+.3f, %+.3f), %s%s%s%s%s%s\n", s, units::metres(b.position.x), units::metres(b.position.y),
                    units::metres(b.position.z), units::metresPerSecond(glm::length(glm::vec2(b.velocity))), b.velocity.x, b.velocity.y,
                    seated::cellKindName(seated::cellAt(L, glm::vec2(b.position))), c & CpuCrowdSim::CONTACT_FLOOR ? " floor" : "",
                    c & CpuCrowdSim::CONTACT_WALL ? " wall" : "", c & CpuCrowdSim::CONTACT_FENCE ? " fence" : "", c & CpuCrowdSim::CONTACT_STEP_UP ? " STEP-UP" : "",
                    b.position.w == 0.0f ? " LEFT" : "");
    }
    return 0;
}

// --- choice-timing (a quiet GPU): the GPU cost of the choice pass (physics.comp PHYSICS_PASS 0) ---
int runChoiceTiming(const bench::Args& a) {
    const Venue& v = venueByName(a.get("venue", "S"));
    const fs::path out = a.get("out", "out/results/nav_s");
    const int warm = a.getInt("steps", 250), reps = a.getInt("reps", 15), evals = a.getInt("evals", 40);
    bench::createHiddenContext("nav_probe");
    ModelOptions qa;
    qa.exitChoice = ExitChoice::QueueAware;
    qa.inclineSpeed = true;
    const int nBuf = 4096;
    const std::vector<GpuBoid> spawn = spawnSeatedCrowd(v, nBuf, 1.0, 1337);
    // The states: the seat spawn, and the default model's state after --steps steps (congested)
    CrowdSim sim(resolveAsset("shaders"), nBuf, v, qa);
    sim.upload(spawn);
    for (int i = 0; i < warm; ++i) sim.step(0);
    const std::vector<GpuBoid> congested = bench::readBuffer<GpuBoid>(sim.currentStateBuffer(), size_t(nBuf));
    GLuint q[2];
    glGenQueries(2, q);
    auto timeChoice = [&](const std::vector<GpuBoid>& st, bool evalSteps) {
        // per repetition: a fresh choice (upload), then CHOICE_STEPS * evals choice steps, timing either the evaluation steps or the
        // steps between them; agents at rest (the choice pass alone)
        std::vector<double> perStep;
        const int cs = choiceSteps(DT);
        for (int r = 0; r < reps; ++r) {
            sim.upload(st);
            sim.stepExitChoice();   // the first step: every agent's forced first choice
            double sum = 0.0;
            int n = 0;
            for (int s = 1; s <= cs * evals; ++s) {
                const bool isEval = s % cs == 0;
                if (isEval == evalSteps) glQueryCounter(q[0], GL_TIMESTAMP);
                sim.stepExitChoice();
                if (isEval == evalSteps) {
                    glQueryCounter(q[1], GL_TIMESTAMP);
                    GLuint64 t0 = 0, t1 = 0;
                    glGetQueryObjectui64v(q[0], GL_QUERY_RESULT, &t0);
                    glGetQueryObjectui64v(q[1], GL_QUERY_RESULT, &t1);
                    sum += double(t1 - t0) * 1e-6;
                    ++n;
                }
            }
            perStep.push_back(sum / std::max(n, 1));
        }
        std::sort(perStep.begin(), perStep.end());
        return std::pair<double, double>(perStep[perStep.size() / 2], perStep.back() - perStep.front());
    };
    // and the whole step of the default model (GPU timestamps, physics interval and total), for scale
    auto timeStep = [&](const std::vector<GpuBoid>& st) {
        std::vector<double> tot;
        for (int r = 0; r < reps; ++r) {
            sim.upload(st);
            sim.setTimingEnabled(true);
            double sum = 0.0;
            for (int s = 0; s < 34; ++s) { sim.step(0); sum += sim.readTimings().total; }
            sim.setTimingEnabled(false);
            tot.push_back(sum / 34.0);
        }
        std::sort(tot.begin(), tot.end());
        return tot[tot.size() / 2];
    };
    Report rep;
    rep.line("# The exit choice's GPU cost");
    rep.line("");
    rep.line(header("choice-timing") + " | " + bench::glRenderer());
    rep.line("");
    rep.line("The choice pass (physics.comp PHYSICS_PASS 0: evaluate, thresholds, apply) alone (CrowdSim::stepExitChoice, agents at rest), GPU "
             "timestamps around it, venue S, N = 4096 buffers (3728 agents at spawn), the default model (queue-aware, incline speed); median of " +
             std::to_string(reps) + " repetitions of " + std::to_string(evals) + " evaluation intervals (" + std::to_string(choiceSteps(DT)) +
             " steps each); the whole step of the default model for scale (GPU timestamps, mean of 34 steps, median of the repetitions). A quiet GPU.");
    rep.line("");
    rep.line("| state | active | choice pass, between evaluations [ms] | choice pass, an evaluation step [ms] | mean per step [ms] | whole step [ms] | share |");
    rep.line("|---|---:|---:|---:|---:|---:|---:|");
    for (int k = 0; k < 2; ++k) {
        const std::vector<GpuBoid>& st = k == 0 ? spawn : congested;
        long active = 0;
        for (const GpuBoid& b : st) active += b.position.w != 0.0f;
        const auto between = timeChoice(st, false), atEval = timeChoice(st, true);
        const double mean = (between.first * double(choiceSteps(DT) - 1) + atEval.first) / double(choiceSteps(DT));
        const double step = timeStep(st);
        rep.line("| " + std::string(k == 0 ? "spawn" : "after " + std::to_string(warm) + " steps") + " | " + std::to_string(active) + " | " +
                 fmt("%.4f", between.first) + " (spread " + fmt("%.4f", between.second) + ") | " + fmt("%.4f", atEval.first) + " (spread " +
                 fmt("%.4f", atEval.second) + ") | " + fmt("%.4f", mean) + " | " + fmt("%.3f", step) + " | " + fmt("%.1f%%", 100.0 * mean / step) + " |");
    }
    glDeleteQueries(2, q);
    rep.write(out / "choice_timing.md");
    return 0;
}

// --- build ---
double peakWorkingSetGB() {
    PROCESS_MEMORY_COUNTERS pmc{};
    if (!GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof pmc)) return NAN;
    return double(pmc.PeakWorkingSetSize) / double(1u << 30);
}

// --- travel (the bottleneck analysis' travel bound) ---
// Every seat's UNIMPEDED walking time to its fastest exit at the model's free speeds: from the seat (its clearway centre) along e_goal of
// an exit's own field (nav::choiceGoal: the queue-aware model's steering; the exits are the seat cell's candidates, the 24 nearest by
// walking distance), in 0.05 m steps until the exit test (past the outer wall's outer face), each step at the free speed of the incline
// speed model (seated::inclineFreeSpeed of the floor's slope along the step at its middle: V_MAX = 1.34 m/s level, V_STAIR_UP / _DOWN
// on the 26.6 deg gangways). A candidate whose distance at V_MAX already exceeds the best time is skipped (exact pruning). No other agent,
// no reaction time: a lower bound on any agent's evacuation time (t_lb (c) of the bottleneck analysis).
int runTravel(const bench::Args& a) {
    const Venue& v = venueByName(a.get("venue", "S"));
    const SeatedLayout& L = v.layout;
    const nav::ChoiceTable& ct = nav::choiceForVenue(v);
    const std::vector<seated::Seat> seats = seated::seats(L);
    const float step = float(units::modelLength(0.05));
    const double sPerTime = TIME_SCALE_S_PER_UNIT;
    struct SeatTravel { double t = INFINITY, lenM = 0.0, upM = 0.0, downM = 0.0; int exit = -1, tried = 0; bool stalledAny = false; };
    std::vector<SeatTravel> res(seats.size());
    long stalls = 0;
    const auto t0 = bench::Clock::now();
#pragma omp parallel for schedule(dynamic, 8) reduction(+ : stalls)
    for (int s = 0; s < int(seats.size()); ++s) {
        const glm::vec2 p0(seats[size_t(s)].pos);
        const GpuNavChoiceCell& c = ct.at(size_t(nav::choiceCell(ct, p0)));
        std::vector<std::pair<float, uint32_t>> cand;
        for (int k = 0; k < nav::CHOICE_K; ++k) {
            const uint32_t e = nav::slotExit(c.slot[k]);
            if (e != nav::CHOICE_EMPTY) cand.push_back({ nav::slotDist(ct, c, k), e });
        }
        std::sort(cand.begin(), cand.end());
        SeatTravel& best = res[size_t(s)];
        for (const auto& [d, e] : cand) {
            if (double(d) * double(ct.secondsPerUnit) >= best.t) break;   // even level at V_MAX it cannot beat the best (sorted: none after it)
            glm::vec2 p = p0;
            double tModel = 0.0, len = 0.0, up = 0.0, down = 0.0;
            long n = 0;
            const long limit = long(double(d) * double(ct.grid.cell) / double(step) * 3.0) + 4000;
            bool stalled = false;
            while (seated::fold(p).y <= L.outerFace) {
                const glm::vec2 g = nav::choiceGoal(ct, L, glm::vec3(p, seated::floorHeight(L, p) + BODY_RADIUS), e);
                if (glm::length(g) < 0.5f || ++n > limit) { stalled = true; break; }
                const float slope = seated::floorSlope(L, p + g * (0.5f * step), g);
                tModel += double(step) / double(seated::inclineFreeSpeed(slope));
                len += double(step);
                if (slope > 1e-4f) up += double(step);
                else if (slope < -1e-4f) down += double(step);
                p += g * step;
            }
            ++best.tried;
            if (stalled) { best.stalledAny = true; ++stalls; continue; }
            const double ts = tModel * sPerTime;
            if (ts < best.t) {
                best.t = ts;
                best.exit = int(e);
                best.lenM = units::metres(len);
                best.upM = units::metres(up);
                best.downM = units::metres(down);
            }
        }
    }
    const double wallS = bench::msSince(t0) / 1000.0;
    std::vector<double> ts;
    int worst = -1, noExit = 0;
    long tried = 0;
    std::map<std::string, long> byType;
    for (size_t s = 0; s < res.size(); ++s) {
        tried += res[s].tried;
        if (res[s].exit < 0) { ++noExit; continue; }
        ts.push_back(res[s].t);
        if (worst < 0 || res[s].t > res[size_t(worst)].t) worst = int(s);
        ++byType[res[s].exit < 4 ? "avenue" : "door"];
    }
    std::sort(ts.begin(), ts.end());
    auto pct = [&](double p) { return ts.empty() ? NAN : ts[std::min(ts.size() - 1, size_t(p * double(ts.size() - 1) + 0.5))]; };
    double mean = 0.0;
    for (double t : ts) mean += t;
    mean = ts.empty() ? NAN : mean / double(ts.size());
    Report r;
    r.line(std::string("# Unimpeded travel time from every seat, venue ") + v.name);
    r.line("");
    r.line(header("travel") + " | " + std::to_string(omp_get_max_threads()) + " OpenMP threads | " + fmt("%.1f", wallS) + " s");
    r.line("");
    r.line("Each seat's walking time to its fastest exit with nobody else in the venue: along e_goal of each candidate exit's own field (nav::choiceGoal, "
           "the default model's steering) in 0.05 m steps to the exit test, every step at the incline speed model's free speed for the floor's "
           "slope along it (level " + fmt("%.2f", V_FREE_M_S) + " m/s; the 26.6 deg gangways up " + fmt("%.3f", units::metresPerSecond(V_STAIR_UP)) + " / down " +
           fmt("%.3f", units::metresPerSecond(V_STAIR_DOWN)) + " m/s, horizontal). The candidates: the seat cell's " + std::to_string(nav::CHOICE_K) +
           " (the 2 nearest avenues, the nearest door, the nearest others), in increasing distance, stopped once the distance at the level speed "
           "exceeds the best time. No reaction time, no other agent: a lower bound on t100.");
    r.line("");
    r.line("| seats | descents | stalled descents | seats without an exit | fastest exit: doors / avenues | min [s] | p50 [s] | p90 [s] | p99 [s] | **max [s]** | mean [s] |");
    r.line("|---:|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|");
    r.line("| " + std::to_string(seats.size()) + " | " + std::to_string(tried) + " | " + std::to_string(stalls) + " | " + std::to_string(noExit) + " | " +
           std::to_string(byType["door"]) + " / " + std::to_string(byType["avenue"]) + " | " + fmt("%.1f", pct(0.0)) + " | " + fmt("%.1f", pct(0.5)) + " | " +
           fmt("%.1f", pct(0.9)) + " | " + fmt("%.1f", pct(0.99)) + " | **" + fmt("%.1f", pct(1.0)) + "** | " + fmt("%.1f", mean) + " |");
    r.line("");
    if (worst >= 0) {
        const seated::Seat& w = seats[size_t(worst)];
        const SeatTravel& t = res[size_t(worst)];
        r.line("**The farthest seat** (in time): quadrant " + std::to_string(w.quadrant) + ", wing " + std::to_string(w.wing) + ", row " + std::to_string(w.row) +
               ", segment " + std::to_string(w.segment) + ", seat " + std::to_string(w.index) + " at (" + fmt("%.2f", units::metres(w.pos.x)) + ", " +
               fmt("%.2f", units::metres(w.pos.y)) + ") m: **" + fmt("%.1f", t.t) + " s** to " + seated::exitName(L, t.exit) + " over " + fmt("%.1f", t.lenM) +
               " m (up the incline " + fmt("%.1f", t.upM) + " m, down " + fmt("%.1f", t.downM) + " m, level " + fmt("%.1f", t.lenM - t.upM - t.downM) + " m).");
        r.line("");
    }
    // The slowest seat per row (the travel bound's dependence on depth)
    r.line("| row | seats | max [s] | mean [s] |");
    r.line("|---:|---:|---:|---:|");
    std::vector<double> rowMax(size_t(L.rows), 0.0), rowSum(size_t(L.rows), 0.0);
    std::vector<int> rowN(size_t(L.rows), 0);
    for (size_t s = 0; s < res.size(); ++s) {
        if (res[s].exit < 0) continue;
        const int k = seats[s].row;
        rowMax[size_t(k)] = std::max(rowMax[size_t(k)], res[s].t);
        rowSum[size_t(k)] += res[s].t;
        ++rowN[size_t(k)];
    }
    for (int k = 0; k < L.rows; ++k)
        if (k < 3 || k + 3 >= L.rows || k % 5 == 0)
            r.line("| " + std::to_string(k) + " | " + std::to_string(rowN[size_t(k)]) + " | " + fmt("%.1f", rowMax[size_t(k)]) + " | " +
                   fmt("%.1f", rowN[size_t(k)] ? rowSum[size_t(k)] / rowN[size_t(k)] : NAN) + " |");
    std::string vn = v.name;
    std::transform(vn.begin(), vn.end(), vn.begin(), [](unsigned char ch) { return char(std::tolower(ch)); });
    const fs::path outDir = a.get("out", "out/results/nav_" + vn);
    r.write(outDir / "travel.md");
    {   // the figures the bottleneck analysis reads (tools/figures/bottleneck.py)
        std::ofstream j(outDir / "travel.json");
        j << "{\n  \"venue\": \"" << v.name << "\",\n  \"commit\": \"" << bench::gitCommit() << "\",\n  \"dirty\": \"" << bench::gitDirty() << "\",\n"
          << "  \"seats\": " << seats.size() << ",\n  \"stalled_descents\": " << stalls << ",\n  \"seats_without_exit\": " << noExit << ",\n"
          << "  \"p50_s\": " << fmt("%.3f", pct(0.5)) << ",\n  \"p90_s\": " << fmt("%.3f", pct(0.9)) << ",\n  \"max_s\": " << fmt("%.3f", pct(1.0)) << ",\n"
          << "  \"mean_s\": " << fmt("%.3f", mean) << "\n}\n";
    }
    return 0;
}

int runBuild(const bench::Args& a) {
    Report r;
    r.line("# Navigation fields and exit choice tables of the seated venues");
    r.line("");
    r.line(std::string("nav_probe build | commit ") + bench::gitCommit() + " (dirty " + bench::gitDirty() + ") | " SWARM_BUILD_TYPE " | " +
           bench::localTimestamp("%Y-%m-%d %H:%M") + " | " + std::to_string(omp_get_max_threads()) + " OpenMP threads");
    r.line("");
    r.line("Fresh builds (no cache), then saved to the cache (keyed by the venue's parameters, layout, contact constants and the algorithms' "
           "versions: nav::cacheKey) and loaded back. Navigation field: the traversability grid (parallel) and the nearest-exit Lazy Theta* "
           "search (sequential). Exit choice table: every exit's own Lazy Theta* field, in parallel batches (at most 4 GB of searches in "
           "flight), merged into CHOICE_K = 24 candidates per reachable FIT cell (the 2 nearest avenues and the nearest "
           "door, then the nearest other exits; 16-bit distances; 144 B per entry plus a 4 B index per grid cell; budget 1 GB = 1024 MB). Peak working set: this process "
           "after the venue's builds (cumulative over the venues built so far).");
    r.line("");
    r.line("| venue | grid (0.05 m cells) | cells | exits | field: grid [s] | field: search [s] | field arrays [MB] | GPU field [MB] | choice table: build [s] | "
           "choice table [MB] | cells changed by the type rule | largest candidate distance [m] | load both from the cache [s] | peak working set [GB] | content hashes (field / table) |");
    r.line("|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---|");
    for (const std::string& name : bench::parseList(a.get("venues", "S,M,L"))) {
        const Venue& v = venueByName(name);
        const nav::Grid g = nav::venueGrid(v);
        const nav::SeatedGeometry geo(v.layout);
        nav::Field f = nav::build(geo, g);
        f.key = nav::cacheKey(v);
        const nav::ChoiceTable t0 = [&] { nav::ChoiceTable t = nav::buildChoiceTable(geo, f); t.key = nav::choiceCacheKey(v); return t; }();
        const double peak = peakWorkingSetGB();
        const bool saved = nav::save(f, nav::cacheFile(v)) && nav::saveChoice(t0, nav::choiceCacheFile(v));
        const auto tl = bench::Clock::now();
        nav::Field fl;
        nav::ChoiceTable tl2;
        const bool loaded = nav::load(fl, nav::cacheFile(v), f.key) && nav::loadChoice(tl2, nav::choiceCacheFile(v), t0.key, units::M_PER_UNIT);
        const double loadS = bench::msSince(tl) / 1000.0;
        const bool same = loaded && nav::contentHash(fl) == nav::contentHash(f) && nav::choiceContentHash(tl2) == nav::choiceContentHash(t0);
        const double fieldMB = double(f.grid.cells()) * (4 + 1 + 1 + 1 + 4 + 4 + 8 + 1) / 1048576.0;
        const double gpuMB = double(f.grid.cells()) * sizeof(GpuNavCell) / 1048576.0;
        char hashes[64];
        std::snprintf(hashes, sizeof hashes, "%016llx / %016llx", (unsigned long long)nav::contentHash(f), (unsigned long long)nav::choiceContentHash(t0));
        r.line("| " + std::string(v.name) + " | " + std::to_string(g.res) + " x " + std::to_string(g.res) + " | " + std::to_string(f.grid.cells()) + " | " +
               std::to_string(f.exitCount) + " | " + fmt("%.2f", f.buildSeconds - f.searchSeconds) + " | " + fmt("%.2f", f.searchSeconds) + " | " + fmt("%.0f", fieldMB) +
               " | " + fmt("%.0f", gpuMB) + " | " + fmt("%.2f", t0.buildSeconds) + " | " + fmt("%.0f", double(t0.bytes()) / 1048576.0) + " | " +
               std::to_string(t0.typeSwaps) + " | " + fmt("%.1f", units::metres(t0.maxDist)) + " | " +
               fmt("%.2f", loadS) + (same ? "" : (saved ? " (**reload differs**)" : " (**not saved**)")) + " | " + fmt("%.2f", peak) + " | " + hashes + " |");
    }
    r.line("");
    r.line("Field arrays: the CPU field's per-cell arrays (floor, class, edges, exit region, distance, anchor, anchor centre, exit id: 24 B per cell). "
           "GPU field: GpuNavCell, 16 B per cell (nearest-exit mode only; the queue-aware default uploads the choice table instead).");
    r.write(fs::path(a.get("out", "out/results/venues")) / "nav_build.md");
    return 0;
}

// --- excluded: the candidate table against every exit, during a queue-aware evacuation ---
// A GPU evacuation of the default model (the production program); at evaluation steps near the requested times the choice pass's own
// inputs are read back before the step: every active agent's start-of-step position, its assigned exit and the counts Q_e the pass
// reads. Then every exit's exact field (nav::buildExitField, one Lazy Theta* search per exit, in parallel batches) gives d_e at each
// sampled agent's choice cell, and E_e = d_e / V0 + Q_e / (w_e J) (nav::estimatedTime) for ALL exits. An exit is EXCLUDED for an agent
// if it is not among its cell's candidates. Counted per time: agents with an excluded exit whose E is lower than (A) their assigned
// exit's, (B) every candidate's, (C) every candidate's and their assigned exit's by more than the switching margins (the pass would
// have made the agent eligible to switch there). The same counts for hypothetical candidate sets (the K nearest by walking distance;
// the K - 1 nearest plus the nearest exit of each type) show what a candidate rule would have missed on the same snapshots.
int runExcluded(const bench::Args& a) {
    const Venue& v = venueByName(a.get("venue", "M"));
    const SeatedLayout& L = v.layout;
    const double load = std::stod(a.get("load", "1"));
    const int nBuf = [&] { int b = 256; while (b < int(std::lround(load * double(seated::seats(L).size())))) b *= 2; return b; }();
    const std::string label = a.get("label", "");
    const fs::path out = fs::path(a.get("out", std::string("out/results/nav_") + char(std::tolower(v.name[0])))) /
                         (std::string("excluded") + (label.empty() ? "" : "_" + label) + ".md");
    std::vector<double> times;
    {
        std::stringstream ss(a.get("times", "3,30,60,120,240,480,720,960,1500,2000"));
        for (std::string t; std::getline(ss, t, ',');) times.push_back(std::stod(t));
    }
    const int maxSample = a.getInt("sample", 0);   // agents per time (0: every active agent), a seeded draw
    const ModelOptions mo = modelOptionsOf(a, v);
    if (mo.exitChoice != ExitChoice::QueueAware) throw std::invalid_argument("excluded: the queue-aware exit choice only");
    bench::createHiddenContext("nav_probe");
    const nav::ChoiceTable& t = nav::choiceForVenue(v);
    const int E = t.exitCount;
    const nav::SeatedGeometry geo(L);
    std::vector<int> type(static_cast<size_t>(E));
    for (int e = 0; e < E; ++e) type[size_t(e)] = geo.exitType(e);
    const int K = nav::CHOICE_K;

    // Static: reachable cells and seats whose candidates hold no exit of a type
    long cellsReach = 0, cellsNoAvenue = 0, cellsNoDoor = 0;
    for (size_t i = 0; i < t.cellCount(); ++i) {
        if (!t.fit(i) || !t.reachable(i)) continue;
        ++cellsReach;
        bool has[2] = { false, false };
        for (int k = 0; k < K; ++k) {
            const uint32_t e = nav::slotExit(t.at(i).slot[k]);
            if (e != nav::CHOICE_EMPTY) has[type[e]] = true;
        }
        cellsNoAvenue += !has[0];
        cellsNoDoor += !has[1];
    }
    const std::vector<seated::Seat> seats = seated::seats(L);
    long seatsNoAvenue = 0;
    for (const seated::Seat& s : seats) {
        const size_t c = size_t(nav::choiceCell(t, glm::vec2(s.pos)));
        bool av = false;
        for (int k = 0; k < K; ++k) { const uint32_t e = nav::slotExit(t.at(c).slot[k]); av |= e != nav::CHOICE_EMPTY && type[e] == 0; }
        seatsNoAvenue += !av;
    }

    // The run: snapshots of the choice pass's inputs
    struct Rec { uint32_t cell, assigned; };
    struct Snap { double t; uint32_t step; std::vector<uint32_t> q, ahead; std::vector<Rec> rec; };
    std::vector<Snap> snaps;
    CrowdSim sim(resolveAsset("shaders"), nBuf, v, mo);
    sim.upload(spawnSeatedCrowd(v, nBuf, load, 1337));
    const int cs = choiceSteps(DT);
    std::mt19937 rng(7);
    size_t ti = 0;
    int stepsRun = 0;
    const int maxSteps = a.getInt("max-steps", 20000);
    long evalAgentSteps = 0, nofitAgentSteps = 0;
    std::set<int> nofitAgents;
    while (ti < times.size() && stepsRun < maxSteps) {
        const uint32_t step = sim.choiceStep();
        const double now = double(step) * DT_REAL_S;
        if (nav::evaluationStep(step, cs)) {   // agents whose lookup returns a NOFIT cell (no FIT neighbour with candidates)
            const std::vector<GpuBoid> st = bench::readBuffer<GpuBoid>(sim.currentStateBuffer(), size_t(nBuf));
            for (int i = 0; i < nBuf; ++i) {
                if (st[size_t(i)].position.w == 0.0f) continue;
                ++evalAgentSteps;
                const int c = nav::choiceCell(t, glm::vec2(st[size_t(i)].position));
                if (!t.fit(size_t(c))) { ++nofitAgentSteps; nofitAgents.insert(i); }
            }
        }
        // the first evaluation step at or after the requested time
        if (nav::evaluationStep(step, cs) && now + 1e-9 >= times[ti]) {
            const std::vector<GpuBoid> st = bench::readBuffer<GpuBoid>(sim.currentStateBuffer(), size_t(nBuf));
            const std::vector<uint32_t> asg = bench::readBuffer<uint32_t>(sim.assignBuffer(), size_t(nBuf));
            const GpuChoiceCounters cc = sim.readChoiceCounters();
            Snap s;
            s.t = now;
            s.step = step;
            s.q.assign(cc.queue + (step & 1u) * uint32_t(nav::CHOICE_QUEUE_STRIDE), cc.queue + (step & 1u) * uint32_t(nav::CHOICE_QUEUE_STRIDE) + E);
            {   // the queue ahead the step's pass reads (the read parity's histograms, prefixed as its prefix stage does)
                const std::vector<uint32_t> work = bench::readBuffer<uint32_t>(sim.choiceWorkBuffer(), sizeof(GpuChoiceWork) / 4);
                s.ahead = nav::aheadPrefixOf(work.data() + offsetof(GpuChoiceWork, ahead) / 4 + size_t(step & 1u) * nav::CHOICE_QUEUE_STRIDE * nav::CHOICE_AHEAD_BINS);
            }
            std::vector<int> act;
            for (int i = 0; i < nBuf; ++i)
                if (st[size_t(i)].position.w != 0.0f) act.push_back(i);
            if (act.empty()) break;
            if (maxSample > 0 && int(act.size()) > maxSample) {
                for (int i = 0; i < maxSample; ++i) std::swap(act[size_t(i)], act[size_t(i) + rng() % (act.size() - size_t(i))]);
                act.resize(size_t(maxSample));
                std::sort(act.begin(), act.end());
            }
            for (const int i : act) {
                const uint32_t c = uint32_t(nav::choiceCell(t, glm::vec2(st[size_t(i)].position)));
                if (!t.reachable(c)) continue;
                s.rec.push_back({ c, asg[size_t(i)] });
            }
            std::printf("  snapshot t = %.1f s (step %u): %zu agents\n", now, step, s.rec.size());
            std::fflush(stdout);
            snaps.push_back(std::move(s));
            ++ti;
            continue;
        }
        sim.step(0);
        ++stepsRun;
    }

    // Every exit's exact field at the sampled cells (batches of searches in parallel, as buildChoiceTable)
    std::vector<std::vector<float>> d(snaps.size());
    for (size_t si = 0; si < snaps.size(); ++si) d[si].assign(snaps[si].rec.size() * size_t(E), std::numeric_limits<float>::infinity());
    const nav::Field& grid = nav::forVenue(v);
    const size_t n = grid.grid.cells(), perExit = n * 32, budget = size_t(4) << 30;
    const int batch = std::max(1, std::min({ omp_get_max_threads(), int(std::max<size_t>(1, budget / perExit)), E }));
    const auto tf = bench::Clock::now();
    for (int e0 = 0; e0 < E; e0 += batch) {
        const int e1 = std::min(E, e0 + batch);
#pragma omp parallel for schedule(dynamic, 1)
        for (int e = e0; e < e1; ++e) {
            const nav::ExitField f = nav::buildExitField(grid, e);
            for (size_t si = 0; si < snaps.size(); ++si)
                for (size_t r = 0; r < snaps[si].rec.size(); ++r) d[si][r * size_t(E) + size_t(e)] = f.dist[snaps[si].rec[r].cell];
        }
        std::printf("  exact fields %d .. %d of %d (%.0f s)\n", e0, e1 - 1, E, bench::msSince(tf) / 1000.0);
        std::fflush(stdout);
    }

    // The counts
    // a rule: k slots; the minAv nearest avenues and the minDoor nearest doors first, then the nearest others
    // a rule: k slots; the minAv nearest avenues, the minDoor nearest straight-gangway doors and the minCorner nearest corner doors first,
    // then the nearest others (types: 0 avenue, 1 a straight gangway's door, 2 a corner gangway's door)
    struct Rule { std::string name; int k, minAv, minDoor, minCorner; };
    const std::vector<Rule> rules = { { "the 4 nearest", 4, 0, 0, 0 }, { "4: the nearest avenue and door, then the nearest", 4, 1, 1, 0 },
                                      { "the 8 nearest", 8, 0, 0, 0 }, { "8: the 2 nearest avenues, the nearest door, then the nearest", 8, 2, 1, 0 },
                                      { "the 10 nearest", 10, 0, 0, 0 }, { "10: the 2 nearest avenues, the nearest door, then the nearest", 10, 2, 1, 0 },
                                      { "10: the 2 nearest avenues, the nearest straight door, the nearest corner door, then the nearest", 10, 2, 1, 1 },
                                      { "10: the nearest avenue, the nearest straight door, the nearest corner door, then the nearest", 10, 1, 1, 1 },
                                      { "10: the 2 nearest avenues, the nearest straight door, the 2 nearest corner doors, then the nearest", 10, 2, 1, 2 },
                                      { "the 12 nearest", 12, 0, 0, 0 }, { "12: the 2 nearest avenues, the nearest straight door, the nearest corner door, then the nearest", 12, 2, 1, 1 },
                                      { "the 16 nearest", 16, 0, 0, 0 }, { "the 20 nearest", 20, 0, 0, 0 }, { "the 24 nearest", 24, 0, 0, 0 },
                                      { "24: the 2 nearest avenues, the nearest straight door, the nearest corner door, then the nearest", 24, 2, 1, 1 },
                                      { "the 28 nearest", 28, 0, 0, 0 } };
    std::vector<int> type3(static_cast<size_t>(E), 0);   // 0 avenue, 1 straight door, 2 corner door
    for (int e = 4; e < E; ++e) type3[size_t(e)] = (L.cornerDoorLo < 1e8f && (e - 4) % L.doorsPerQuadrant() == L.doorsPerQuadrant() - 1) ? 2 : 1;
    Report rep;
    rep.line("# Exit choice: excluded exits during a queue-aware evacuation of venue " + std::string(v.name));
    rep.line("");
    rep.line(header("excluded") + " | " + modelOptionsLabel(v, mo) + " | " + fmt("%.0f", 100.0 * load) + "% load, seed 1337 | GPU");
    rep.line("");
    rep.line("Candidate table in use: CHOICE_K = " + std::to_string(K) + " slots per cell, " + std::to_string(E) + " exits (" +
             std::to_string(std::count(type.begin(), type.end(), 0)) + " avenues, " + std::to_string(std::count(type.begin(), type.end(), 1)) +
             " doors), content " + [&] { char b[24]; std::snprintf(b, sizeof b, "%016llx", (unsigned long long)nav::choiceContentHash(t)); return std::string(b); }() + ".");
    rep.line("");
    rep.line("- Reachable FIT cells whose candidates hold **no avenue**: " + std::to_string(cellsNoAvenue) + " of " + std::to_string(cellsReach) + " (" +
             fmt("%.1f", 100.0 * double(cellsNoAvenue) / double(std::max(cellsReach, 1L))) + "%); no door: " + std::to_string(cellsNoDoor) + ".");
    rep.line("- Seats whose cell's candidates hold no avenue: " + std::to_string(seatsNoAvenue) + " of " + std::to_string(seats.size()) + ".");
    rep.line("- Agents whose cell lookup returned a NOFIT cell (no FIT neighbour with candidates), on every evaluation step until the last "
             "snapshot: " + std::to_string(nofitAgentSteps) + " of " + std::to_string(evalAgentSteps) + " agent-steps, " +
             std::to_string(nofitAgents.size()) + " distinct agents.");
    rep.line("");
    rep.line("E_e = d_e / V0 + Q_e / (w_e J) for every exit e: d_e from e's own exact field at the agent's choice cell (nav::buildExitField, float), "
             "Q_e the counts the choice pass read at that step, the pass's own arithmetic (nav::estimatedTime). EXCLUDED: not a candidate of the "
             "agent's cell. (A) an excluded exit's E below the assigned exit's; (B) below every candidate's; (C) below every candidate's and the "
             "assigned exit's by more than the switching margins max(10% E, 5 s) (the pass would have made the agent eligible to switch there).");
    rep.line("");
    // Two estimates: (0) the model's E (Q_e = every agent assigned to e); (1) E with the QUEUE AHEAD (Q_e = the agents assigned to e
    // nearer to e than this agent, by their exact distances at this snapshot): a diagnostic of the queue term
    std::vector<std::vector<std::vector<float>>> assignedD(snaps.size());
    for (size_t si = 0; si < snaps.size(); ++si) {
        assignedD[si].assign(size_t(E), {});
        for (size_t r = 0; r < snaps[si].rec.size(); ++r) {
            const uint32_t as = snaps[si].rec[r].assigned;
            if (as < uint32_t(E)) assignedD[si][as].push_back(d[si][r * size_t(E) + as]);
        }
        for (auto& v : assignedD[si]) std::sort(v.begin(), v.end());
    }
    fs::create_directories(out.parent_path());
    std::ofstream csv(out.parent_path() / (out.stem().string() + ".csv"));
    csv << "estimate,t_s,step,cell,assigned,E_assigned,best_candidate,E_best_candidate,best_excluded,E_best_excluded\n";
    for (int variant = 0; variant < 2; ++variant) {
    rep.line(variant == 0 ? "### The model's estimate (the queue ahead A_e: the pass's prefix sums, agents assigned to e in nearer 0.49 m distance bins)"
                          : "### Diagnostic: the queue ahead by exact distances (the agents assigned to e nearer to it than the agent at this snapshot)");
    rep.line("");
    rep.line("| t [s] | step | agents | assigned to an avenue | (A) excluded exit better than the assigned | (A) split: cap / margins / no better candidate | (B) better than every candidate | (C) better by more than the margins | best excluded: avenue / door | max gain over the assigned [s] |");
    rep.line("|---:|---:|---:|---:|---:|---|---:|---:|---|---:|");
    long totA = 0, totB = 0, totC = 0, totN = 0, totAcap = 0, totAmargin = 0;
    std::vector<long> ruleB(rules.size(), 0), ruleA(rules.size(), 0);
    for (size_t si = 0; si < snaps.size(); ++si) {
        const Snap& s = snaps[si];
        long A = 0, B = 0, C = 0, toAvenue = 0, exAv = 0, exDoor = 0, Acap = 0, Amargin = 0;
        double maxGain = 0.0;
        std::vector<std::pair<float, int>> order(static_cast<size_t>(E));
        for (size_t r = 0; r < s.rec.size(); ++r) {
            const float* dr = &d[si][r * size_t(E)];
            std::vector<float> Ee(static_cast<size_t>(E));
            for (int e = 0; e < E; ++e) {
                if (!std::isfinite(dr[e])) { Ee[size_t(e)] = INFINITY; continue; }
                const std::vector<float>& ad = assignedD[si][size_t(e)];
                // the model's E: the queue ahead from the pass's own prefix sums at the distance's bin (the distance in quanta as the table
                // rounds it); the diagnostic: every agent assigned to e nearer than this one, by exact distances
                const uint32_t q = variant == 0 ? nav::aheadOf(s.ahead.data(), uint32_t(e), uint32_t(std::nearbyint(double(dr[e]) / double(t.distQuantum))))
                                                : uint32_t(std::lower_bound(ad.begin(), ad.end(), dr[e]) - ad.begin());
                Ee[size_t(e)] = nav::estimatedTime(t, dr[e], uint32_t(e), q);
            }
            const GpuNavChoiceCell& c = t.at(s.rec[r].cell);
            std::vector<char> cand(size_t(E), 0);
            float eBestCand = INFINITY;
            int bestCand = -1;
            for (int k = 0; k < K; ++k) {
                const uint32_t e = nav::slotExit(c.slot[k]);
                if (e == nav::CHOICE_EMPTY) break;
                cand[e] = 1;
                if (Ee[e] < eBestCand) { eBestCand = Ee[e]; bestCand = int(e); }
            }
            float eEx = INFINITY;
            int bestEx = -1;
            for (int e = 0; e < E; ++e)
                if (!cand[size_t(e)] && Ee[size_t(e)] < eEx) { eEx = Ee[size_t(e)]; bestEx = e; }
            const uint32_t as = s.rec[r].assigned;
            const float eAs = as < uint32_t(E) ? Ee[as] : INFINITY;
            toAvenue += as < uint32_t(E) && type[as] == 0;
            const bool a1 = eEx < eAs, b1 = eEx < eBestCand;
            const bool c1 = b1 && eAs - eEx > std::max(CHOICE_REL_MARGIN * eAs, CHOICE_ABS_MARGIN_S);
            A += a1; B += b1; C += c1;
            if (a1 && !b1) {   // (A) split: a candidate beats the excluded exit too; is the agent eligible to switch to it (the switch cap held it)?
                const bool eligible = eAs - eBestCand > std::max(CHOICE_REL_MARGIN * eAs, CHOICE_ABS_MARGIN_S);
                (eligible ? Acap : Amargin)++;
            }
            if (a1) { (type[size_t(bestEx)] == 0 ? exAv : exDoor)++; maxGain = std::max(maxGain, double(eAs - eEx)); }
            if (a1 || b1)
                csv << variant << "," << fmt("%.1f", s.t) << "," << s.step << "," << s.rec[r].cell << "," << as << "," << eAs << "," << bestCand << "," << eBestCand << "," << bestEx << "," << eEx << "\n";
            // hypothetical rules on the same snapshot
            for (int e = 0; e < E; ++e) order[size_t(e)] = { dr[e], e };
            std::sort(order.begin(), order.end());
            for (size_t ri = 0; ri < rules.size(); ++ri) {
                const Rule& ru = rules[ri];
                std::vector<char> in(size_t(E), 0);
                int taken = 0, ofType[3] = { 0, 0, 0 };
                for (int m = 0; m < E && taken < ru.k; ++m) {   // the guaranteed nearest of each type
                    const int e = order[size_t(m)].second, ty = type3[size_t(e)];
                    if (!std::isfinite(order[size_t(m)].first) || ofType[ty] >= (ty == 0 ? ru.minAv : ty == 1 ? ru.minDoor : ru.minCorner)) continue;
                    in[size_t(e)] = 1; ++ofType[ty]; ++taken;
                }
                for (int m = 0; m < E && taken < ru.k; ++m)     // then the nearest others
                    if (std::isfinite(order[size_t(m)].first) && !in[size_t(order[size_t(m)].second)]) { in[size_t(order[size_t(m)].second)] = 1; ++taken; }
                float bIn = INFINITY, bOut = INFINITY;
                for (int e = 0; e < E; ++e) (in[size_t(e)] ? bIn : bOut) = std::min(in[size_t(e)] ? bIn : bOut, Ee[size_t(e)]);
                ruleB[ri] += bOut < bIn;
                ruleA[ri] += bOut < eAs;
            }
        }
        totA += A; totB += B; totC += C; totN += long(s.rec.size()); totAcap += Acap; totAmargin += Amargin;
        rep.line("| " + fmt("%.1f", s.t) + " | " + std::to_string(s.step) + " | " + std::to_string(s.rec.size()) + " | " + std::to_string(toAvenue) + " | " +
                 std::to_string(A) + " | " + std::to_string(Acap) + " / " + std::to_string(Amargin) + " / " + std::to_string(A - Acap - Amargin) + " | " +
                 std::to_string(B) + " | " + std::to_string(C) + " | " + std::to_string(exAv) + " / " + std::to_string(exDoor) + " | " +
                 (A ? fmt("%.1f", maxGain) : std::string("-")) + " |");
    }
    rep.line("| **all** | | " + std::to_string(totN) + " | | **" + std::to_string(totA) + "** | **" + std::to_string(totAcap) + " / " + std::to_string(totAmargin) +
             " / " + std::to_string(totA - totAcap - totAmargin) + "** | **" + std::to_string(totB) + "** | **" + std::to_string(totC) + "** | | |");
    rep.line("");
    rep.line("(A) split: a candidate is better still than the excluded exit, and the agent is eligible to switch to it (its gain over the assigned "
             "exit exceeds the margins: the per-exit switch cap holds it back this evaluation) / a candidate is better still, within the margins (the "
             "hysteresis keeps the assigned exit) / no candidate is better than the excluded exit (counted in (B) too).");
    rep.line("");
    rep.line("Hypothetical candidate rules on the same snapshots (agent-snapshots with an exit outside the rule's set better than every exit in it / "
             "better than the agent's assigned exit; the dynamics are the run's, not the rule's):");
    rep.line("");
    rep.line("| candidate rule | slots | outside better than every candidate | outside better than the assigned |");
    rep.line("|---|---:|---:|---:|");
    for (size_t ri = 0; ri < rules.size(); ++ri)
        rep.line("| " + rules[ri].name + " | " + std::to_string(rules[ri].k) + " | " + std::to_string(ruleB[ri]) + " | " + std::to_string(ruleA[ri]) + " |");
    rep.line("");
    }
    rep.line("");
    rep.line("Per-agent rows with (A) or (B): " + (out.stem().string() + ".csv") + ".");
    rep.write(out);
    return 0;
}


// --- anchors (diagnostics): per reachable FIT cell, the number of DISTINCT anchors over every exit's own field
// (how many first vertices all exits' shortest paths from the cell start through), and the maximum distance; by place ---
int runAnchors(const bench::Args& a) {
    const Venue& v = venueByName(a.get("venue", "M"));
    const nav::Field& grid = nav::forVenue(v);
    const nav::ChoiceTable& t = nav::choiceForVenue(v);
    const size_t n = grid.grid.cells();
    const int E = grid.exitCount;
    constexpr int TRACK = 24;
    std::vector<uint32_t> fitIdx(n, 0xFFFFFFFFu);
    std::vector<size_t> cells;
    for (size_t i = 0; i < n; ++i)
        if (t.fit(i) && t.reachable(i)) { fitIdx[i] = uint32_t(cells.size()); cells.push_back(i); }
    std::vector<int32_t> anchors(cells.size() * TRACK, -1);
    std::vector<uint8_t> count(cells.size(), 0), over(cells.size(), 0);
    std::vector<float> maxD(cells.size(), 0.0f);
    const size_t perExit = n * 32, budget = size_t(4) << 30;
    const int batch = std::max(1, std::min({ omp_get_max_threads(), int(std::max<size_t>(1, budget / perExit)), E }));
    for (int e0 = 0; e0 < E; e0 += batch) {
        const int e1 = std::min(E, e0 + batch);
        std::vector<nav::ExitField> fs(size_t(e1 - e0));
#pragma omp parallel for schedule(dynamic, 1)
        for (int e = e0; e < e1; ++e) fs[size_t(e - e0)] = nav::buildExitField(grid, e);
        for (int e = e0; e < e1; ++e) {
            const nav::ExitField& f = fs[size_t(e - e0)];
#pragma omp parallel for schedule(static)
            for (long long kk = 0; kk < (long long)cells.size(); ++kk) {
                const size_t k = size_t(kk), i = cells[k];
                if (!std::isfinite(f.dist[i])) continue;
                maxD[k] = std::max(maxD[k], f.dist[i]);
                const int32_t an = f.anchor[i];
                int32_t* list = &anchors[k * TRACK];
                bool found = false;
                for (int m = 0; m < count[k]; ++m) found |= list[m] == an;
                if (found) continue;
                if (count[k] < TRACK) list[count[k]++] = an;
                else over[k] = 1;
            }
        }
        std::printf("  fields %d .. %d of %d\n", e0, e1 - 1, E);
        std::fflush(stdout);
    }
    std::map<std::string, std::vector<long>> hist;   // place -> counts 1..TRACK+1
    for (size_t k = 0; k < cells.size(); ++k) {
        const glm::vec2 c = grid.grid.centre(int(cells[k] % size_t(grid.grid.res)), int(cells[k] / size_t(grid.grid.res)));
        const venue_s::Where w = venue_s::where(v.layout, glm::vec4(c, 0.1f, 1.0f));
        std::string pl = venue_s::placeName(w.place);
        std::vector<long>& h = hist[pl];
        if (h.empty()) h.assign(TRACK + 2, 0);
        ++h[over[k] ? TRACK + 1 : count[k]];
        std::vector<long>& all = hist["all"];
        if (all.empty()) all.assign(TRACK + 2, 0);
        ++all[over[k] ? TRACK + 1 : count[k]];
    }
    float md = 0.0f;
    for (float x : maxD) md = std::max(md, x);
    std::printf("venue %s: %zu reachable FIT cells, %d exits, the largest distance to any reachable exit %.1f m\n", v.name, cells.size(), E, units::metres(md));
    std::printf("| place | cells | distinct anchors <= 2 | <= 4 | <= 7 | <= 8 | <= 15 | > 15 | max |\n|---|---:|---:|---:|---:|---:|---:|---:|---:|\n");
    for (const auto& kv : hist) {
        const std::vector<long>& h = kv.second;
        long tot = 0, c2 = 0, c4 = 0, c7 = 0, c8 = 0, c15 = 0;
        int mx = 0;
        for (int m = 0; m <= TRACK + 1; ++m) {
            tot += h[size_t(m)];
            if (m <= 2) c2 += h[size_t(m)];
            if (m <= 4) c4 += h[size_t(m)];
            if (m <= 7) c7 += h[size_t(m)];
            if (m <= 8) c8 += h[size_t(m)];
            if (m <= 15) c15 += h[size_t(m)];
            if (h[size_t(m)]) mx = m;
        }
        auto pc = [&](long c) { return fmt("%.2f%%", 100.0 * double(c) / double(std::max(tot, 1L))); };
        std::printf("| %s | %ld | %s | %s | %s | %s | %s | %s | %s |\n", kv.first.c_str(), tot, pc(c2).c_str(), pc(c4).c_str(), pc(c7).c_str(), pc(c8).c_str(),
                    pc(c15).c_str(), pc(tot - c15).c_str(), mx > TRACK ? (">" + std::to_string(TRACK)).c_str() : std::to_string(mx).c_str());
    }
    return 0;
}

// --- goaldiff ---
// GPU navGoal / navChoiceGoal against the CPU mirror at test_gpu's points (nav.field and nav.exit_choice (c): the same seeds, points and exits), with the
// branch inputs of every point that differs: which decision each side took (a face within reach, which face, into the face), the CPU margins
// of those decisions (tools/nav_goal_check.hpp), and the nearest point (in float ulps of x, y, z) where the CPU function gives the GPU's value.
// --variant NAME compiles the probe with one change, to find the GLSL operation responsible: precise-d2 (the wall query's squared distance
// unfused: 'precise' dd.x * dd.x + dd.y * dd.y), precise-proj (the projection's into and e - n into unfused), precise-all (both).
int runGoalDiff(const bench::Args& a) {
    namespace ngc = nav_goal_check;
    const Venue& v = venueByName(a.get("venue", "S"));
    const SeatedLayout& L = v.layout;
    const std::string variant = a.get("variant", "none");
    const fs::path out = a.get("out", "out/results/nav_s");
    const std::string tag = variant == "none" ? "" : "_" + variant;
    bench::createHiddenContext("nav_probe");
    const std::string driver = std::string((const char*)glGetString(GL_RENDERER)) + " | " + (const char*)glGetString(GL_VERSION);
    const fs::path shaderDir = resolveAsset("shaders");
    auto readText = [](const fs::path& p) {   // line ends normalized (the checkout may have CRLF; the variants' anchors use LF)
        std::ifstream in(p, std::ios::binary);
        std::stringstream ss;
        ss << in.rdbuf();
        std::string s = ss.str();
        s.erase(std::remove(s.begin(), s.end(), '\r'), s.end());
        return s;
    };
    auto replaceOnce = [](std::string& s, const std::string& from, const std::string& to, const char* what) {
        const size_t at = s.find(from);
        if (at == std::string::npos || s.find(from, at + 1) != std::string::npos) throw std::runtime_error(std::string("variant anchor not found once: ") + what);
        s.replace(at, from.size(), to);
    };
    std::string venueCode = readText(shaderDir / "venue_seated.glsl"), phys = readText(shaderDir / "physics.comp");
    if (variant == "precise-d2" || variant == "precise-all")
        replaceOnce(venueCode, "vec2 dd = f - q;\n                float d2 = dot(dd, dd);", "precise vec2 dd = f - q;\n                precise float d2 = dd.x * dd.x + dd.y * dd.y;",
                    "venueWall's d2");
    if (variant == "precise-bounds") {   // the band and cell bounds' sums of a row front and a layout literal 'precise' (S's cell table, VS_GENERATED 0)
        replaceOnce(venueCode, "        if (((j - 2) & 1) == 0) { lo = d; hi = d + VS_CLEARWAY; }\n        else { lo = d + VS_CLEARWAY; hi = vsRowFront(k + 1); }",
                    "        precise float dc = d + VS_CLEARWAY;\n        if (((j - 2) & 1) == 0) { lo = d; hi = dc; }\n        else { lo = dc; hi = vsRowFront(k + 1); }", "vsBand's clearway");
        replaceOnce(venueCode, "    float corner = hi - VS_CORNER_INSET - VS_SEAT_INSET, gLo = VS_GANGWAY_LO - VS_SEAT_INSET, gHi = VS_GANGWAY_HI + VS_SEAT_INSET;",
                    "    precise float corner = hi - VS_CORNER_INSET - VS_SEAT_INSET;\n    float gLo = VS_GANGWAY_LO - VS_SEAT_INSET, gHi = VS_GANGWAY_HI + VS_SEAT_INSET;", "vsCell's corner");
        replaceOnce(venueCode, "        if (!seatBand) { corner = lo - VS_CORNER_INSET; gLo = VS_GANGWAY_LO; gHi = VS_GANGWAY_HI; }",
                    "        if (!seatBand) { precise float cl = lo - VS_CORNER_INSET; corner = cl; gLo = VS_GANGWAY_LO; gHi = VS_GANGWAY_HI; }", "vsCell's clearway corner");
    }
    if (variant == "runtime-reach2")   // reach * reach rounded in float at run time (probeOne = 1 is a uniform: the compiler cannot fold it)
        replaceOnce(venueCode, "float best = inWall ? VS_BIG : reach * reach;\n    vec2 bestQ = f;\n    vec4 bestRect = vec4(0.0);\n    bool found",
                    "float best = inWall ? VS_BIG : (reach * probeOne) * reach;\n    vec2 bestQ = f;\n    vec4 bestRect = vec4(0.0);\n    bool found",
                    "venueWall's reach * reach");
    const size_t b0 = phys.find("// @nav-begin"), b1 = phys.find("// @nav-end");
    if (b0 == std::string::npos || b1 == std::string::npos) throw std::runtime_error("physics.comp has no @nav block");
    std::string navBlock = phys.substr(b0, b1 - b0);
    if (variant == "precise-proj" || variant == "precise-all") {
        for (const char* fn : { "vec2 navGoal(vec3 p) {", "vec2 navChoiceGoal(vec3 p, uint ex) {" }) {
            const size_t at = navBlock.find(fn);
            if (at == std::string::npos) throw std::runtime_error("no " + std::string(fn));
            std::string body = navBlock.substr(at, navBlock.find("\n}\n", at) - at);
            const std::string orig = body;
            replaceOnce(body, "float into = dot(e, w.xy);", "precise float into = e.x * w.x + e.y * w.y;", "into");
            replaceOnce(body, "e -= w.xy * into;", "precise vec2 pe = e - w.xy * into; e = pe;", "the projection");
            navBlock.replace(at, orig.size(), body);
        }
    } else if (variant != "none" && variant != "precise-d2" && variant != "runtime-reach2" && variant != "precise-bounds") {
        throw std::runtime_error("unknown --variant " + variant + " (none, precise-d2, precise-proj, precise-all, runtime-reach2, precise-bounds)");
    }
    if (variant == "runtime-reach2") venueCode = "uniform float probeOne;\n" + venueCode;
    const fs::path dir = processTempPath("swarm_goaldiff");
    fs::create_directories(dir);
    std::ofstream(dir / "venue_seated.glsl", std::ios::binary) << venueCode;   // venuePreamble reads the copy beside the shader
    auto program = [&](bool choice, const std::string& choiceDefines) {
        const fs::path tmp = dir / "probe.comp";
        std::ofstream(tmp, std::ios::binary) << "#version 430 core\n" + choiceDefines + navBlock +
            "layout(local_size_x = 64) in;\n"
            "layout(std430, binding = 5) buffer P { vec4 pts[]; };\n"
            "layout(std430, binding = 6) buffer R0 { vec4 o0[]; };\n"
            "layout(std430, binding = 7) buffer R1 { vec4 o1[]; };\n"
            "layout(std430, binding = 8) buffer X { uint ex[]; };\n"
            "layout(std430, binding = 9) buffer R2 { vec4 o2[]; };\n"
            "uniform int count;\n"
            // venueWall's search over every band within VS_MAX_BAND_STEPS, the nearest face of the other kind at any distance below 2 FEELER_REACH:
            // its squared distance d2, its nearest point q's dep, and the point's folded dep (the inputs of d2 < reach^2)
            "vec4 diagNearest(vec3 c) {\n"
            "  vec2 f = vsFold(c.xy); int jp = vsBandOf(f.y); float l0, l1; int kind, row; vsOwnCell(jp, f.x, l0, l1, kind, row);\n"
            "  bool inWall = kind != VS_INCLINE && vsCellTop(kind, row, f.y) > c.z; float best = 1e9; vec2 bq = vec2(0.0);\n"
            "  for (int j = max(jp - VS_MAX_BAND_STEPS, 0); j <= min(jp + VS_MAX_BAND_STEPS, VS_BANDS - 1); ++j) {\n"
            "    float lo, hi; vsBand(j, lo, hi);\n"
            "    for (int cc = 0; cc < VS_MAX_CELLS; ++cc) { float a, b; int k, r; if (!vsCell(j, cc, a, b, k, r)) break;\n"
            "      bool wall = k != VS_INCLINE && vsCellTop(k, r, lo) > c.z; if (wall == inWall) continue;\n"
            "      vec2 q = clamp(f, vec2(a, lo), vec2(b, hi)); vec2 dd = f - q; float d2 = dot(dd, dd);\n"
            "      if (d2 < best) { best = d2; bq = q; } } }\n"
            "  return vec4(best, bq, f.y); }\n"
            "void main() { uint i = gl_GlobalInvocationID.x; if (i >= uint(count)) return; vec3 p = pts[i].xyz;\n"
            "  o2[i] = diagNearest(p);\n" +
            (choice ? "  vec2 e = navChoiceDirection(p.xy, ex[i]); vec2 g = navChoiceGoal(p, ex[i]);\n"
                    : "  vec2 e = navDirection(p.xy); vec2 g = navGoal(p);\n") +
            "  vec3 w = venueWall(p, FEELER_REACH);\n"
            "  o0[i] = vec4(e, w.xy); o1[i] = vec4(w.z, g, FEELER_REACH * FEELER_REACH); }\n";   // .w: the compiler's FEELER_REACH^2
        const GLuint prog = loadComputeProgram(tmp, {}, &v);
        return prog;
    };
    auto makeBuf = [](const void* data, size_t bytes) {
        GLuint b;
        glGenBuffers(1, &b);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, b);
        glBufferData(GL_SHADER_STORAGE_BUFFER, GLsizeiptr(std::max<size_t>(bytes, 16)), data, GL_DYNAMIC_COPY);
        return b;
    };

    const nav::Field& f = nav::forVenue(v);
    const nav::ChoiceTable& st = nav::choiceForVenue(v);
    Report r;
    r.line("# GPU e_goal against the CPU mirror at test_gpu's points");
    r.line("");
    r.line(header("goaldiff") + " | venue " + v.name + " | variant " + variant);
    r.line("");
    r.line("Driver: " + driver);
    r.line("");
    {   // the cell table (vsBand / vsCell / vsCellTop) evaluated by the GPU at run time (band and cell from the invocation id) against the CPU's
        const int nb = seated::bandCount(L), mc = ngc::CELL_PROBE_CELLS;
        const fs::path tmp = dir / "cells.comp";
        std::ofstream(tmp, std::ios::binary) << ngc::cellTableProbeSource();
        const GLuint prog = loadComputeProgram(tmp, {}, &v);
        const size_t n = size_t(nb) * size_t(mc);
        const GLuint c0 = makeBuf(nullptr, n * 16), c1 = makeBuf(nullptr, n * 16);
        glUseProgram(prog);
        glUniform1i(glGetUniformLocation(prog, "count"), GLint(n));
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, c0);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 7, c1);
        glDispatchCompute(GLuint((n + 63) / 64), 1, 1);
        const std::vector<glm::vec4> g0 = bench::readBuffer<glm::vec4>(c0, n), g1 = bench::readBuffer<glm::vec4>(c1, n);
        glDeleteBuffers(1, &c0);
        glDeleteBuffers(1, &c1);
        glDeleteProgram(prog);
        const ngc::CellParity cp = ngc::compareCellTable(L, g0, g1);
        r.line("## The cell table on the GPU at run time");
        r.line("");
        r.line("vsBand / vsCell / vsCellTop for every band and cell (indices from the invocation id) against seated::band / cell / cellTop: " +
               std::to_string(cp.bands) + " bands, " + std::to_string(cp.cells) + " cells; bands with a differing bound " + std::to_string(cp.bandDiff) +
               ", cells with a differing bound or top " + std::to_string(cp.cellDiff) + ", cells of another kind, row or count " + std::to_string(cp.structDiff) +
               "; the largest difference " + fmt("%.2g", cp.maxAbs) + " model units (criterion (4): at most " + fmt("%.2g", double(ngc::BOUND_TOL)) + ": " +
               (cp.pass() ? "PASS" : "FAIL") + "), " + std::to_string(cp.maxBoundUlps) + " ulp(s) of a bound. Each distinct differing bound:");
        r.line("");
        r.line("| bound | CPU | GPU | ulps | where (band: cell) |");
        r.line("|---|---:|---:|---:|---|");
        std::map<std::pair<float, float>, std::pair<std::string, std::string>> distinct;   // (CPU, GPU) -> (kind of bound, where)
        auto note = [&](const char* what, float cpu, float gpu, int j, int c) {
            if (cpu == gpu) return;
            auto& e = distinct[{ cpu, gpu }];
            if (e.first.empty()) e.first = what;
            if (e.second.size() < 80) e.second += (e.second.empty() ? "" : ", ") + std::to_string(j) + (c < 0 ? std::string() : ": " + std::to_string(c));
        };
        for (int j = 0; j < nb; ++j) {
            float lo, hi;
            seated::band(L, j, lo, hi);
            const glm::vec4 gb = g0[size_t(j) * mc];
            note("band lo", lo, gb.x, j, -1);
            note("band hi", hi, gb.y, j, -1);
            for (int c = 0; c < mc; ++c) {
                float a = 0.0f, b = 0.0f;
                int k = -1, rr = -1;
                const bool ok = seated::cell(L, j, c, a, b, k, rr);
                const glm::vec4 x = g0[size_t(j) * mc + size_t(c)];
                if (!ok) continue;
                note("cell l0", a, x.z, j, c);
                note("cell l1", b, x.w, j, c);
            }
        }
        for (const auto& kv : distinct) {
            char b[400];
            std::snprintf(b, sizeof b, "| %s | %.9g | %.9g | %ld | %s |", kv.second.first.c_str(), double(kv.first.first), double(kv.first.second),
                          ngc::ulpDistance(kv.first.first, kv.first.second), kv.second.second.c_str());
            r.line(b);
        }
        r.line("");
        r.line("The layout's literals (seatedDefines):");
        r.line("");
        r.line("```");
        std::string defs = seatedDefines(L);
        defs.erase(std::remove(defs.begin(), defs.end(), '\r'), defs.end());
        if (!defs.empty() && defs.back() == '\n') defs.pop_back();
        r.line(defs);
        r.line("```");
        r.line("");
    }
    std::ofstream csv;
    fs::create_directories(out);
    csv.open(out / ("goal_diff" + tag + ".csv"));
    csv << "probe,point,x_m,y_m,z,lat_m,dep_m,kind,band,diff,category,cpu_found,gpu_found,cpu_proj,gpu_proj,e_cpu_x,e_cpu_y,e_gpu_x,e_gpu_y,"
           "w_cpu_x,w_cpu_y,w_cpu_z,w_gpu_x,w_gpu_y,w_gpu_z,g_cpu_x,g_cpu_y,g_gpu_x,g_gpu_y,into_cpu,len_cpu,reach_gap,face_gap,top_gap,"
           "perturb_ulps,perturb_axis,d2_cpu,d2_gpu,qdep_gpu,fdep_gpu\n";
    csv << std::setprecision(9);
    for (int probe = 0; probe < 2; ++probe) {
        const bool choice = probe == 1;
        // test_gpu's points: nav.field (seed 23) / nav.exit_choice (c) (seed 29): 50 000 random plan points at the rest height above the floor, then every seat
        std::mt19937 rng(choice ? 29 : 23);
        std::uniform_real_distribution<float> u(v.domainMin, v.domainMax());
        std::vector<glm::vec4> pts;
        for (int i = 0; i < 50000; ++i) {
            const glm::vec2 q(u(rng), u(rng));
            pts.emplace_back(q, seated::floorHeight(L, q) + BODY_RADIUS, 1.0f);
        }
        for (const seated::Seat& s : seated::seats(L)) pts.emplace_back(s.pos, 1.0f);
        std::vector<uint32_t> exs(pts.size(), 0u);
        if (choice)
            for (size_t i = 0; i < pts.size(); ++i) {
                const GpuNavChoiceCell& c = st.at(size_t(nav::choiceCell(st, glm::vec2(pts[i]))));
                const int k = int(i % 5);
                exs[i] = k < nav::CHOICE_K ? nav::slotExit(c.slot[k]) : nav::CHOICE_NONE;
            }
        const GLuint prog = program(choice, choice ? nav::choicePreambleDefines(st) : std::string());
        const std::vector<GpuNavCell> table = nav::gpuCells(f);
        const GLuint b2b = makeBuf(nullptr, pts.size() * 16);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 9, b2b);
        const GLuint bp = makeBuf(pts.data(), pts.size() * 16), b0b = makeBuf(nullptr, pts.size() * 16), b1b = makeBuf(nullptr, pts.size() * 16),
                     bx = makeBuf(exs.data(), exs.size() * 4), bn = makeBuf(table.data(), table.size() * sizeof(GpuNavCell)),
                     bt = makeBuf(st.index.data(), st.index.size() * 4), be = makeBuf(st.entries.data(), st.entries.size() * sizeof(GpuNavChoiceCell));
        glUseProgram(prog);
        glUniform1i(glGetUniformLocation(prog, "count"), GLint(pts.size()));
        if (variant == "runtime-reach2") glUniform1f(glGetUniformLocation(prog, "probeOne"), 1.0f);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, bp);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, b0b);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 7, b1b);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 8, bx);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_NAV, bn);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_NAV_CHOICE, bt);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_NAV_CHOICE_ENTRY, be);
        glDispatchCompute(GLuint((pts.size() + 63) / 64), 1, 1);
        const std::vector<glm::vec4> o0 = bench::readBuffer<glm::vec4>(b0b, pts.size()), o1 = bench::readBuffer<glm::vec4>(b1b, pts.size()),
                                     o2 = bench::readBuffer<glm::vec4>(b2b, pts.size());
        for (GLuint b : { bp, b0b, b1b, b2b, bx, bn, bt, be }) glDeleteBuffers(1, &b);
        glDeleteProgram(prog);

        auto cpuDir = [&](glm::vec3 p, size_t i) { return choice ? nav::choiceDirection(st, glm::vec2(p), exs[i]) : nav::direction(f, glm::vec2(p)); };
        auto cpuGoal = [&](glm::vec3 p, size_t i) { return choice ? nav::choiceGoal(st, L, p, exs[i]) : nav::goal(f, L, p); };
        const char* name = choice ? "navChoiceGoal" : "navGoal";
        // every point: the difference's distribution; the differing ones: categories and margins
        const double edges[] = { 0.0, 1e-7, 1e-6, 1e-5, 1e-4, 1e-3, 1e-2, 1e-1, 1.0, 10.0 };
        long hist[10] = {}, close = 0, compared = 0, bitSame = 0, dirDiff = 0;
        ngc::Agreement agr;   // the criterion (tools/nav_goal_check.hpp), as test_gpu evaluates it
        double dirMax = 0.0;
        std::map<std::string, long> cats;
        struct Row { size_t i; double diff; std::string cat; ngc::Margins m; int ulps; char axis; };
        std::vector<Row> rows;
        // margins over ALL compared points (how often a point lies this close to a decision: the share the bounds allow)
        const double gapEdges[] = { 1e-8, 1e-7, 1e-6, 1e-5, 1e-4 };
        long nearReach[5] = {}, nearFace[5] = {}, nearInto[5] = {}, shortLen[5] = {};
        for (size_t i = 0; i < pts.size(); ++i) {
            const glm::vec3 p(pts[i]);
            const glm::vec2 ec = cpuDir(p, i), eg(o0[i].x, o0[i].y);
            dirMax = std::max(dirMax, double(glm::length(ec - eg)));
            dirDiff += ec != eg;
            const glm::vec3 wc = seated::wall(L, p, FEELER_REACH), wg(o0[i].z, o0[i].w, o1[i].x);
            const glm::vec2 gc = cpuGoal(p, i), gg(o1[i].y, o1[i].z);
            if (wc.z < BODY_RADIUS - 3e-4f) { ++close; continue; }   // test_gpu's exclusion: closer to a wall than a centre can stand
            agr.add(L, p, ec, gc, gg, i < 50000, [&](glm::vec3 q) { return cpuGoal(q, i); });
            ++compared;
            bitSame += gc == gg;
            const double d = glm::length(gc - gg);
            int h = 0;
            while (h < 9 && d > edges[h]) ++h;
            ++hist[h];
            const ngc::Margins m = ngc::margins(L, p, ec);
            for (int k = 0; k < 5; ++k) {
                nearReach[k] += m.reachGap < gapEdges[k];
                nearFace[k] += m.faceGap < gapEdges[k];
                nearInto[k] += m.found && std::abs(m.into) < gapEdges[k];
                shortLen[k] += m.projected && m.len < gapEdges[k] * 1e4;
            }
            const bool zeroMismatch = (gc == glm::vec2(0.0f)) != (gg == glm::vec2(0.0f));
            if (d <= 1e-5 && !zeroMismatch) continue;
            const bool fc = wc.z < FEELER_REACH, fg = wg.z < FEELER_REACH;
            const bool pc = fc && glm::dot(ec, glm::vec2(wc)) < 0.0f, pg = fg && glm::dot(eg, glm::vec2(wg)) < 0.0f;
            std::string cat;
            if (glm::length(ec - eg) > 1e-6) cat = "direction";
            else if (fc != fg) cat = "reach";
            else if (fc && glm::length(glm::vec2(wc) - glm::vec2(wg)) > 1e-3) cat = "face";
            else if (pc != pg) cat = "into";
            else if (pc) cat = "renormalization";
            else cat = "other";
            ++cats[cat];
            // the nearest point where the CPU function gives the GPU's value (within 1e-5): x, y or z moved by 1, 2, 4, ... 4096 ulps
            int ulps = -1;
            char axis = '-';
            for (int s = 1; s <= 4096 && ulps < 0; s *= 2)
                for (int ax = 0; ax < 3 && ulps < 0; ++ax)
                    for (int sg = -1; sg <= 1 && ulps < 0; sg += 2) {
                        glm::vec3 q = p;
                        for (int k = 0; k < s; ++k) q[ax] = std::nextafter(q[ax], sg < 0 ? -INFINITY : INFINITY);
                        if (glm::length(cpuGoal(q, i) - gg) <= 1e-5) { ulps = s; axis = "xyz"[ax]; }
                    }
            rows.push_back({ i, d, cat, m, ulps, axis });
            int row = -1, band = -1;
            const int kind = seated::cellAt(L, glm::vec2(p), &row, &band);
            const glm::vec2 fo = seated::fold(glm::vec2(p));
            csv << name << "," << i << "," << p.x * units::M_PER_UNIT << "," << p.y * units::M_PER_UNIT << "," << p.z << "," << fo.x * units::M_PER_UNIT << ","
                << fo.y * units::M_PER_UNIT << "," << seated::cellKindName(kind) << "," << band << "," << d << "," << cat << "," << fc << "," << fg << "," << pc << ","
                << pg << "," << ec.x << "," << ec.y << "," << eg.x << "," << eg.y << "," << wc.x << "," << wc.y << "," << wc.z << "," << wg.x << "," << wg.y << ","
                << wg.z << "," << gc.x << "," << gc.y << "," << gg.x << "," << gg.y << "," << m.into << "," << m.len << "," << m.reachGap << "," << m.faceGap
                << "," << m.wall.topGap << "," << ulps << "," << axis << "," << m.wall.d2 << "," << o2[i].x << "," << o2[i].z << "," << o2[i].w << "\n";
        }
        r.line("## " + std::string(name) + (choice ? " (nav.exit_choice (c): seed 29, each point asking for one of its cell's first 5 candidates)" : " (nav.field: seed 23)"));
        r.line("");
        {   // the reach threshold: the GPU compiler's FEELER_REACH * FEELER_REACH against the CPU's float product and the product rounded once from double
            const float reach2Gpu = o1[0].w, reach2Cpu = FEELER_REACH * FEELER_REACH, reach2Once = float(double(FEELER_REACH) * double(FEELER_REACH));
            uint32_t bg, bc, bo;
            std::memcpy(&bg, &reach2Gpu, 4);
            std::memcpy(&bc, &reach2Cpu, 4);
            std::memcpy(&bo, &reach2Once, 4);
            char b[300];
            std::snprintf(b, sizeof b, "FEELER_REACH = %.9g (0x%08x); FEELER_REACH^2: GPU (compiler) %.9g (0x%08x), CPU float product %.9g (0x%08x), the exact product rounded "
                          "once %.9g (0x%08x)", double(FEELER_REACH), [] { uint32_t u; std::memcpy(&u, &FEELER_REACH, 4); return u; }(), double(reach2Gpu), bg,
                          double(reach2Cpu), bc, double(reach2Once), bo);
            r.line(b);
            r.line("");
        }
        r.line(std::to_string(pts.size()) + " points (50 000 random plan points at the rest height, every seat); " + std::to_string(close) +
               " closer to a wall than BODY_RADIUS - 3e-4 (excluded, as in the test); compared " + std::to_string(compared) + ", bit-identical " +
               std::to_string(bitSame) + ". The field's direction alone: max |GPU - CPU| " + fmt("%.2g", dirMax) + " (" + std::to_string(dirDiff) +
               " points not bit-identical).");
        r.line("");
        r.line("| \\|GPU - CPU\\| | 0 | (0, 1e-7] | (1e-7, 1e-6] | (1e-6, 1e-5] | (1e-5, 1e-4] | (1e-4, 1e-3] | (1e-3, 1e-2] | (1e-2, 0.1] | (0.1, 1] | > 1 |");
        r.line("|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|");
        std::string hl = "| points |";
        for (long c : hist) hl += " " + std::to_string(c) + " |";
        r.line(hl);
        r.line("");
        r.line("How many of the compared points lie within a distance of each decision (CPU margins; the share a bound would allow):");
        r.line("");
        r.line("| margin below | 1e-8 | 1e-7 | 1e-6 | 1e-5 | 1e-4 |");
        r.line("|---|---:|---:|---:|---:|---:|");
        auto rowOf = [&](const char* what, const long* c) { std::string s = std::string("| ") + what + " |"; for (int k = 0; k < 5; ++k) s += " " + std::to_string(c[k]) + " |"; r.line(s); };
        rowOf("\\|d - FEELER_REACH\\| (model units)", nearReach);
        rowOf("nearest other face - nearest face (model units)", nearFace);
        rowOf("\\|into\\| (a face within reach)", nearInto);
        r.line("| projected length l below 1e4 x the margin (1e-4 ... 1) | " + std::to_string(shortLen[0]) + " | " + std::to_string(shortLen[1]) + " | " +
               std::to_string(shortLen[2]) + " | " + std::to_string(shortLen[3]) + " | " + std::to_string(shortLen[4]) + " |");
        r.line("");
        {
            char b[900];
            std::snprintf(b, sizeof b, "**The criterion (tools/nav_goal_check.hpp): %s.** (1) away from every decision (%ld of %ld points; margins > %.2g model units, "
                          "projected length >= %.2g): max |GPU - CPU| %.2g (<= %.0e; there the projected length %.3g); (2) points beyond %.0e: %ld (random %ld, seats %ld), at a decision %ld; the "
                          "GPU's value is the CPU's on the decision's other side: the reach moved by %.2g %ld, the point moved by at most %d ulps %ld (largest %d), "
                          "neither %ld; (3) random points differing %ld of %ld (at most %.1f%%); at a decision: %ld points, %ld of them random",
                          agr.pass() ? "PASS" : "FAIL", agr.compared - agr.atDecision, agr.compared, double(ngc::DECISION_TOL), double(ngc::SHORT_LEN), agr.maxAway,
                          ngc::CONT_TOL, double(agr.maxAwayLen), ngc::CONT_TOL, agr.differ, agr.differRandom, agr.differSeats, agr.differ - agr.unexplained, double(ngc::DECISION_TOL),
                          agr.byReach, ngc::REPRO_ULPS, agr.byMove, agr.maxUlps, agr.notReproduced, agr.differRandom, agr.comparedRandom,
                          100.0 * ngc::MAX_RANDOM_SHARE, agr.atDecision, agr.atDecisionRandom);
            r.line(b);
            r.line("");
        }
        std::string cl = "Points with \\|GPU - CPU\\| > 1e-5 (or a zero on one side only): " + std::to_string(rows.size()) + " (";
        bool firstCat = true;
        for (const auto& kv : cats) { cl += (firstCat ? "" : ", ") + kv.first + " " + std::to_string(kv.second); firstCat = false; }
        r.line(cl + ").");
        r.line("");
        if (!rows.empty()) {
            r.line("| point | (x, y) m | lat, dep m | cell | \\|GPU - CPU\\| | decision flipped | CPU found / GPU found | CPU proj / GPU proj | into | l | \\|d - reach\\| | face gap | top gap | CPU = GPU at |");
            r.line("|---:|---|---|---|---:|---|---|---|---:|---:|---:|---:|---:|---|");
            std::sort(rows.begin(), rows.end(), [](const Row& x, const Row& y) { return x.diff > y.diff; });
            for (size_t k = 0; k < rows.size() && k < 60; ++k) {
                const Row& w = rows[k];
                const glm::vec3 p(pts[w.i]);
                const glm::vec2 fo = seated::fold(glm::vec2(p));
                int row = -1, band = -1;
                const int kind = seated::cellAt(L, glm::vec2(p), &row, &band);
                const glm::vec3 wc = seated::wall(L, p, FEELER_REACH), wg(o0[w.i].z, o0[w.i].w, o1[w.i].x);
                const glm::vec2 ec = cpuDir(p, w.i), eg(o0[w.i].x, o0[w.i].y);
                const bool fc = wc.z < FEELER_REACH, fg = wg.z < FEELER_REACH;
                const bool pc = fc && glm::dot(ec, glm::vec2(wc)) < 0.0f, pg = fg && glm::dot(eg, glm::vec2(wg)) < 0.0f;
                char b[600];
                std::snprintf(b, sizeof b, "| %zu | (%.4f, %.4f) | %.4f, %.4f | %s (band %d) | %.3g | %s | %d / %d | %d / %d | %.3g | %.3g | %.3g | %.3g | %.3g | %s |", w.i,
                              p.x * units::M_PER_UNIT, p.y * units::M_PER_UNIT, fo.x * units::M_PER_UNIT, fo.y * units::M_PER_UNIT, seated::cellKindName(kind), band, w.diff,
                              w.cat.c_str(), fc, fg, pc, pg, w.m.into, w.m.len, w.m.reachGap, w.m.faceGap, w.m.wall.topGap,
                              w.ulps < 0 ? "none within 4096 ulps" : (std::to_string(w.ulps) + " ulp(s) of " + w.axis).c_str());
                r.line(b);
            }
            r.line("");
        }
    }
    r.write(out / ("goal_diff" + tag + ".md"));
    std::printf("-> %s\n", (out / ("goal_diff" + tag + ".csv")).string().c_str());
    std::error_code ec;
    fs::remove_all(dir, ec);
    return 0;
}

} // namespace

int main(int argc, char** argv) {
    if (argc < 2) {
        std::printf("usage: nav_probe grid [--venue S] [--out out/results/nav_s]\n");
        return 2;
    }
    try {
        const std::string cmd = argv[1];
        const bench::Args a(argc, argv, 2);
        if (cmd == "grid") return runGrid(a);
        if (cmd == "field") return runField(a);
        if (cmd == "validate") return runValidate(a);
        if (cmd == "known") return runKnownDebug(a);
        if (cmd == "trace") return runTrace(a);
        if (cmd == "jam") return runJam(a);
        if (cmd == "cells") return runCells(a);
        if (cmd == "timing") return runTiming(a);
        if (cmd == "choice") return runChoice(a);
        if (cmd == "drive") return runDrive(a);
        if (cmd == "choice-timing") return runChoiceTiming(a);
        if (cmd == "build") return runBuild(a);
        if (cmd == "travel") return runTravel(a);
        if (cmd == "excluded") return runExcluded(a);
        if (cmd == "anchors") return runAnchors(a);
        if (cmd == "goaldiff") return runGoalDiff(a);
        std::printf("unknown command '%s'\n", cmd.c_str());
        return 2;
    } catch (const std::exception& e) {
        std::printf("FATAL: %s\n", e.what());
        return 1;
    }
}
