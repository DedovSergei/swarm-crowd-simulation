// venue_probe: the seated venue generator's checks and reports. Run from the repository root.
//
//   venue_probe layout [--venue S] [--out out/results/venue_s]
//       The parameter table (real and model units), derived values, seats per row and in total, floor areas and the
//     jam capacity, the design rules -> <out>/layout.md (and stdout). --venue M | L (out out/results/venue_m | venue_l by
//       default); the straight gangways, the doors and the exit sizing rule, the exit width per 1000 seats.
//   venue_probe golden [--venue S] [--steps 250] [--forced 1] [--cpu 0]   the state hashes after --steps steps (GPU; --cpu 1:
//     also the CPU reference, both sort modes): the routed full seat spawn with the default model and with the nearest exit, level speed
//       ({nearest, level}), and (--forced 1) the dense forced scenario (tools/venue_s.hpp) -> stdout (the GOLDEN_S* pins' runs)
//   venue_probe gangways [--venue S]   each gangway's floor area (the flow analysis' densities), CSV on stdout
//   venue_probe capacity [--out out/results/venues]
//     The generated venues' seat count, size and height for every row count 1 .. 140 (generatedVenueParams), the row
//       counts nearest 16 000 and 64 000 seats and the grids they need -> <out>/capacity.md; and the S / M / L table.
//   venue_probe overcrowd [--out out/results/venues]   each venue's standing floor, the overcrowding spawn's cap and achievable loads,
//       the experiment matrix's overcrowded spawns (seeds 1-3) with their initial densities -> <out>/overcrowding.md
//   venue_probe catchments [--venue S] [--out out/results/venue_<v>]   every row segment's seats and the gangways at its two ends
//       -> <out>/catchments.csv (the bottleneck analysis' attainable gangway balance)
//   venue_probe exact [--venue S] [--points 100000] [--seed 7] [--out out/results/venue_s]
//       The analytic distance against the brute force over the explicit primitive list (seated::primitives) at random
//       points within 1.5 m above / 0.5 m below the floor: outside the solid |sdf - brute| (limit 1e-6), the sign
//       everywhere, inside the solid the sphere test (the ball of radius |sdf| lies in the solid and the point moved by
//       |sdf| along the gradient is on its surface), the Eikonal property (central differences, h = 1e-4, at points away
//       from kinks: the analytic gradient equal at all 6 stencil points), the GPU (physics.comp's map / mapExactGrad on the
//       venue preamble) against the CPU mirror, the floor heights bit for bit, the cells visited -> <out>/sdf_exactness.md.
//   venue_probe timing [--venue S] [--points 262144] [--calls 64] [--reps 15] [--out out/results/venue_s]
//       GPU ns per map() / mapExactGrad() call, the analytic venue against the baked texture (physics.comp's own
//       functions in a probe; quiet GPU required) -> <out>/map_timing.md.
//   venue_probe forced [--venue S] [--only abcdefg] [--out out/results/venue_s]
//     The forced-motion scenarios of tools/venue_s.hpp on the GPU (the TEST_DRIVE_TABLE variant) and the CPU
//       reference: (a) INV-row, (b) junctions, (c) gangways down and up, (d) passages and exits, (e) the dense scenario with
//       plausibility, (f) the step-up rules over all of them, (g) CPU/GPU equivalence and the golden hashes ->
//       <out>/forced_<timestamp>/summary.md (+ junctions.csv, gangways.csv).
//     Venues M and L: --rows sample (their default) runs (a)-(c) on a sample of rows in every wing: the first, middle and
//       last rows, each straight gangway's first row and first seated row, and --sample-rows (default 5) more drawn with --seed (default
//       7); --rows all every row. Their default --only abcdf (the dense scenario and (g) for S; M / L: `venue_probe equiv`); step counts
//     scaled by the venue's depth; out out/results/venue_m | venue_l.
//   venue_probe equiv [--venue S] [--steps 200] [--golden 250]   the production program (routed, the default model) on the
//       GPU and the CPU reference: one step from the GPU state after --steps steps (grid exact, |dpos| > 2e-4 for < 0.5% of the active
//       agents, both sort modes), CPU thread invariance (1 vs all threads, 100 steps), GPU and CPU determinism, the golden hashes after
//       --golden steps (GPU, CPU counting, CPU bitonic) -> <out>/equivalence.md
//   venue_probe obj [--venue S] [--out .]
//       Writes the render mesh (seated::meshOBJ) to <out>/<venue obj asset> and checks every triangle's normal points
//       out of the solid (the analytic distance; the fence against its box).
#include "../benchmark/bench_common.hpp"
#include "../golden_state.hpp"
#include "../venue_s.hpp"

#include <swarm/assets.hpp>
#include <swarm/crowd_sim.hpp>
#include <swarm/metrics.hpp>
#include <swarm/sdf.hpp>
#include <swarm/shader.hpp>
#include <swarm/venue.hpp>
#include <swarm/venue_capacity.hpp>

#include <array>
#include <memory>
#include <map>
#include <random>

namespace fs = std::filesystem;
using namespace swarm;

namespace {

std::string fmt(const char* f, double v) { char b[64]; std::snprintf(b, sizeof b, f, v); return b; }
double m(float u) { return units::metres(double(u)); }

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
    return std::string("venue_probe ") + tool + " | commit " + bench::gitCommit() + " (dirty " + bench::gitDirty() + ") | " SWARM_BUILD_TYPE " | " +
           bench::localTimestamp("%Y-%m-%d %H:%M");
}

// --- layout ---
int runLayout(const bench::Args& a) {
    const Venue& v = venueByName(a.get("venue", "S"));
    if (!v.seated()) throw std::runtime_error("layout: not a seated venue");
    const SeatedVenueParams& p = v.params;
    const SeatedLayout& L = v.layout;
    Report r;
    r.line("# Venue " + std::string(v.name) + ": layout" + std::string(v.params.exitLayout == SeatedVenueParams::ExitLayout::DoorPerWing ? "" : " (generated venue)"));
    r.line("");
    r.line(header("layout"));
    r.line("");
    r.line("## Parameters (real units; model units = metres / 31.25)");
    r.line("");
    r.line("| parameter | value | model units |");
    r.line("|---|---:|---:|");
    auto row = [&](const std::string& name, double metres, const char* unit = "m") {
        r.line("| " + name + " | " + fmt("%.3f", metres) + " " + unit + " | " + fmt("%.6f", units::modelLength(metres)) + " |");
    };
    row("walkway width (fence outer face -> barrier front; the terrace's measured walkway)", p.walkwayWidthM);
    row("front barrier thickness", p.barrierThicknessM);
    row("front barrier top above the walkway", p.barrierTopM);
    row("avenue clear width (the terrace's measured avenue mouths)", p.avenueWidthM);
    row("side wall thickness", p.sideWallThicknessM);
    r.line("| rows | " + std::to_string(p.rows) + " | |");
    row("row (tread) depth", p.rowDepthM);
    row("row rise", p.rowRiseM);
    row("clearway (front of each tread)", p.clearwayM);
    row("seat block depth (rowDepth - clearway)", p.rowDepthM - p.clearwayM);
    row("seat block top above its tread", p.seatBlockTopM);
    row("seat block top above the next row's tread", p.seatBlockTopM - p.rowRiseM);
    row("seat pitch", p.seatWidthM);
    row("gangway width", p.gangwayWidthM);
    r.line("| max seats between two gangways / with a gangway at one end (Green Guide; not yet checked against the cited edition) | " +
           std::to_string(p.maxSeatsBetweenGangways) + " / " + std::to_string(p.maxSeatsDeadEnd) + " | |");
    row("rear concourse width", p.concourseWidthM);
    row("outer wall thickness", p.outerWallThicknessM);
    row("side / outer wall top above the concourse", p.wallTopAboveConcourseM);
    row("exterior landing depth", p.landingDepthM);
    r.line("| concourse exit rule: rate of passage (stairways) / egress time / minimum width / exits per quadrant (not yet checked against the cited edition) | " +
           fmt("%.0f", p.exitRatePerMMin) + " p/(m min) / " + fmt("%.0f", p.egressTimeMin) + " min / " + fmt("%.2f", p.minExitWidthM) +
           " m / " + (p.exitLayout == SeatedVenueParams::ExitLayout::DoorPerWing ? std::to_string(p.exitsPerQuadrant) : std::string("one per gangway head")) + " | |");
    r.line("| neighbour grid: cells per axis (0.05 model units = 1.5625 m) / domain half-width | " + std::to_string(v.gridRes) + " / " +
           fmt("%.3f m", m(v.domainMax())) + " | " + fmt("%.4f", double(v.domainMax())) + " |");
    r.line("| metric grid: 1 m cells per axis | " + std::to_string(v.metricGridRes) + " | |");
    r.line("");
    r.line("## Derived layout (Chebyshev depth dep = max(|x|, |y|), lateral lat = min(|x|, |y|))");
    r.line("");
    r.line("| quantity | m | model units |");
    r.line("|---|---:|---:|");
    auto drow = [&](const std::string& name, float u) { r.line("| " + name + " | " + fmt("%.4f", m(u)) + " | " + fmt("%.7f", double(u)) + " |"); };
    drow("fence outer face (dep)", FENCE_HALF_OUTER);
    drow("barrier front = stand front (dep)", L.standFront);
    drow("row 0 front (dep)", L.row0);
    drow("concourse front = last row's back (dep)", L.concFront);
    drow("outer wall inner face (dep)", L.concBack);
    drow("outer wall outer face = exit depth (dep): the outer half-width", L.outerFace);
    drow("exterior landings end (dep)", L.landingEnd);
    drow("avenue half-width (lat)", L.avenueHalf);
    drow("stand side (side wall's stand face, lat)", L.lat0);
    drow("straight gangway (lat, low edge)", L.gangwayLo);
    drow("straight gangway (lat, high edge)", L.gangwayHi);
    drow("concourse exit (lat, low edge)", L.exitLo);
    drow("concourse exit (lat, high edge)", L.exitHi);
    drow("concourse exit width", L.exitHi - L.exitLo);
    drow("corner gangway inset of a clearway (from the diagonal at its row front)", L.cornerInset);
    drow("seat blocks and barrier end short of the gangways' edges", L.seatInset);
    drow("row 0 tread height H0 = rake x clearway", L.firstRow);
    drow("concourse level = rows x rise", L.concourseZ);
    drow("wall tops", L.wallTop);
    r.line("| gangway rake | " + fmt("%.2f deg", std::atan(double(L.rake)) * 180.0 / 3.14159265358979) + " (n_z " +
           fmt("%.3f", 1.0 / std::sqrt(1.0 + double(L.rake) * L.rake)) + ") | " + fmt("%.3f", double(L.rake)) + " |");
    r.line("| corner gangway clear width (narrowest, between two mirrored seat-block corners) | " +
           fmt("%.3f", std::sqrt(2.0) * (m(L.cornerInset + L.seatInset) - (p.rowDepthM - p.clearwayM))) + " | |");
    r.line("| straight gangway clear width: between clearway ends / between seat-block ends | " + fmt("%.3f", m(L.gangwayHi - L.gangwayLo)) +
           " / " + fmt("%.3f", m(L.gangwayHi - L.gangwayLo + 2.0f * L.seatInset)) + " | |");
    r.line("");
    r.line("## Straight gangways, doors and the exit sizing rule");
    r.line("");
    r.line("Gangway placement rule (Green Guide, seated accommodation; not yet checked against the cited edition): at most " + std::to_string(p.maxSeatsBetweenGangways) +
           " seats in a row between two gangways and " + std::to_string(p.maxSeatsDeadEnd) + " between a gangway and a dead end, applied to every row. Straight "
           "gangway i + 1 lies exactly " + std::to_string(p.maxSeatsBetweenGangways) + " seats beyond gangway i and starts at the first row whose front reaches it "
           "(its foot opens onto the corner gangway); while no seat fits after it, it merges with the corner gangway.");
    r.line("");
    r.line("| straight gangway | lat low edge (m) | lat high edge (m) | first row | merged with the corner gangway in rows |");
    r.line("|---:|---:|---:|---:|---|");
    for (int i = 0; i < L.gangways; ++i) {
        const int first = L.gwRow[size_t(i)], seatedFrom = L.gwSeated[size_t(i)];
        r.line("| " + std::to_string(i) + " | " + fmt("%.3f", m(L.gwLo[size_t(i)])) + " | " + fmt("%.3f", m(L.gwHi[size_t(i)])) + " | " + std::to_string(first) + " | " +
               (seatedFrom > first ? std::to_string(first) + " .. " + std::to_string(std::min(seatedFrom, L.rows) - 1) + " (while it is the last)" : std::string("-")) + " |");
    }
    r.line("");
    r.line("Per quadrant " + std::to_string(2 * L.gangways) + " straight gangways and 1 corner gangway: " + std::to_string(seated::gangwayCount(L)) + " gangway heads.");
    r.line("");
    const bool perHead = p.exitLayout == SeatedVenueParams::ExitLayout::DoorPerGangwayHead;
    r.line("Exit sizing rule (rate of passage and egress time from the Green Guide; not yet checked against the cited edition): the total exit "
           "width, concourse doors and avenues, clears every seat within the egress time at the planning rate: W >= seats / (" + fmt("%.0f", p.exitRatePerMMin) +
           " p/(m min) x " + fmt("%.0f", p.egressTimeMin) + " min) = **" + fmt("%.2f", L.requiredExitWidthM) + " m**. " +
           (perHead ? std::string("A door at every gangway head (straight and corner), all of one width: the doors carry what the avenues leave, split evenly, "
                                  "rounded up to 0.1 m, at least the gangway's width (wider doors rather than more doors).")
                    : std::string("Venue S: per quadrant the doors alone clear the quadrant's seats; one door per wing, centred on its straight "
                                  "gangway; the corner gangways' heads lead to concourse corners without doors.")));
    r.line("");
    r.line("| door (per wing) | lat low (m) | lat high (m) | clear width (m) |");
    r.line("|---|---:|---:|---:|");
    for (int i = 0; i < L.doors; ++i)
        r.line("| straight " + std::to_string(i) + " | " + fmt("%.3f", m(L.doorLo[size_t(i)])) + " | " + fmt("%.3f", m(L.doorHi[size_t(i)])) + " | " +
               fmt("%.2f", seated::exitWidthM(L, 4 + i)) + " |");
    if (L.cornerDoorLo < 1e8f)
        r.line("| corner (both wings, from lat to the diagonal) | " + fmt("%.3f", m(L.cornerDoorLo)) + " | diagonal | " + fmt("%.2f", L.cornerDoorWidthM) +
               " (sqrt 2 x (outer wall inner face - lat): the gap between the wall ends) |");
    const double avenuesM = 4.0 * p.avenueWidthM, doorsM = L.totalExitWidthM - avenuesM;
    r.line("");
    r.line("| exits | count | width (m) |");
    r.line("|---|---:|---:|");
    r.line("| concourse doors | " + std::to_string(4 * L.doorsPerQuadrant()) + " | " + fmt("%.2f", doorsM) + " |");
    r.line("| avenues | 4 | " + fmt("%.2f", avenuesM) + " |");
    r.line("| **total** | " + std::to_string(4 + 4 * L.doorsPerQuadrant()) + " | **" + fmt("%.2f", L.totalExitWidthM) + "** (rule: >= " + fmt("%.2f", L.requiredExitWidthM) + ") |");
    r.line("");
    r.line("**Exit width per 1000 seats: " + fmt("%.2f", 1000.0 * L.totalExitWidthM / L.seatTotal) + " m** (doors " + fmt("%.2f", 1000.0 * doorsM / L.seatTotal) +
           ", avenues " + fmt("%.2f", 1000.0 * avenuesM / L.seatTotal) + "); design egress time at the planning rate " +
           fmt("%.1f", L.seatTotal / (p.exitRatePerMMin * L.totalExitWidthM)) + " min (target <= " + fmt("%.0f", p.egressTimeMin) + " min). Every gangway head leads to a door: " +
           (L.cornerDoorLo < 1e8f ? "**yes** (straight and corner)." : "**no** (the corner gangways' heads have no door)."));
    r.line("");
    {   // Gangway loading, a design check (information): each seat to the nearer gangway end of its row segment
        std::vector<long> served(size_t(L.gangways) + 1, 0);   // per wing: straight gangways; [gangways]: the corner gangway (both wings)
        for (const seated::Seat& st : seated::seats(L)) {
            if (st.quadrant != 0 || st.wing != 0) continue;
            const int n = L.activeGangways(st.row);
            int g;
            if (st.segment == 0) g = 0;
            else {
                const float a = L.gwHi[size_t(st.segment - 1)];
                const float b = st.segment < n ? L.gwLo[size_t(st.segment)] : L.row0 + float(st.row) * L.rowDepth - L.cornerInset;
                g = st.lat - a <= b - st.lat ? st.segment - 1 : (st.segment < n ? st.segment : L.gangways);
            }
            ++served[size_t(g)];
        }
        served[size_t(L.gangways)] *= 2;   // the corner gangway takes the corner segments of both wings of its quadrant
        r.line("Gangway loading (design check, information; not a rule of this generator): each seat counted for the nearer end of its row segment, "
               "the time to pass those seats through the gangway's " + fmt("%.2f", p.gangwayWidthM) + " m at the planning rate of " + fmt("%.0f", p.exitRatePerMMin) +
               " p/(m min) (the exit rule's figures; not yet checked against the cited edition):");
        r.line("");
        r.line("| gangway (one wing; corner: one quadrant) | seats served | at the planning rate (min) |");
        r.line("|---|---:|---:|");
        for (int i = 0; i <= L.gangways; ++i)
            r.line("| " + (i < L.gangways ? "straight " + std::to_string(i) : std::string("corner")) + " | " + std::to_string(served[size_t(i)]) + " | " +
                   fmt("%.1f", double(served[size_t(i)]) / (p.exitRatePerMMin * p.gangwayWidthM)) + " |");
        r.line("");
    }
    r.line("## Seats");
    r.line("");
    r.line("Per wing (8 wings: 4 quadrants x 2), per row: the dead-end segment (side wall .. straight gangway 0) and the segments after");
    r.line("each straight gangway (the last up to the corner gangway). Seats centred in their segment at the seat pitch.");
    r.line("");
    r.line("| row | front dep (m) | tread z (m) | dead-end | after the straight gangways | largest between | per wing | all 8 wings |");
    r.line("|---:|---:|---:|---:|---|---:|---:|---:|");
    const std::vector<seated::RowSeats> rows = seated::seatsPerRow(L);
    long total = 0;
    for (int k = 0; k < L.rows; ++k) {
        const int w = rows[size_t(k)].total;
        total += 8L * w;
        std::string segs;
        for (int sg = 1; sg < seated::segmentCount(L, k); ++sg) {
            float a0, b0;
            (void)a0; (void)b0;
            int n = 0;
            for (const seated::Seat& st : seated::seats(L))
                if (st.quadrant == 0 && st.wing == 0 && st.row == k && st.segment == sg) ++n;
            segs += (segs.empty() ? "" : " + ") + std::to_string(n);
        }
        r.line("| " + std::to_string(k) + " | " + fmt("%.3f", m(L.row0 + float(k) * L.rowDepth)) + " | " +
               fmt("%.3f", m(L.firstRow + float(k) * L.rowRise)) + " | " + std::to_string(rows[size_t(k)].deadEnd) + " | " + segs + " | " +
               std::to_string(rows[size_t(k)].between) + " | " + std::to_string(w) + " | " + std::to_string(8 * w) + " |");
    }
    const size_t listed = seated::seats(L).size();
    r.line("");
    r.line("**Seats: " + std::to_string(total) + "** (seated::seats lists " + std::to_string(listed) + "); per quadrant " +
           std::to_string(total / 4) + ".");
    const seated::Areas A = seated::areas(L);
    const venue::Capacity cap = venue::capacityOf(v);
    r.line("");
    r.line("## Floor areas (exact, m^2) and capacity");
    r.line("");
    r.line("| floor | m^2 |");
    r.line("|---|---:|");
    r.line("| walkway (fence outer face -> barrier front) | " + fmt("%.1f", A.walkway) + " |");
    r.line("| avenues (barrier front -> outer face) | " + fmt("%.1f", A.avenues) + " |");
    r.line("| clearways | " + fmt("%.1f", A.clearways) + " |");
    r.line("| gangways (straight + corner, with the barrier gaps) | " + fmt("%.1f", A.gangways) + " |");
    r.line("| rear concourse | " + fmt("%.1f", A.concourse) + " |");
    r.line("| concourse exits (through the outer wall) | " + fmt("%.1f", A.exits) + " |");
    r.line("| **occupiable** | **" + fmt("%.1f", A.occupiable()) + "** |");
    r.line("| not occupiable: seat blocks / barrier / walls / pitch / landings (beyond the exit test) | " + fmt("%.1f", A.seatBlocks) +
           " / " + fmt("%.1f", A.barrier) + " / " + fmt("%.1f", A.walls) + " / " + fmt("%.1f", A.pitch) + " / " + fmt("%.1f", A.landings) + " |");
    r.line("");
    r.line("Design capacity = seats = " + std::to_string(cap.design) + "; jam capacity = occupiable x hexagonal packing " +
           fmt("%.4f", venue::HEX_PACKING_P_M2) + " p/m^2 = " + std::to_string(cap.jam) + ".");
    r.write(fs::path(a.get("out", std::string("out/results/venue_") + (v.name[0] == 'S' ? "s" : v.name[0] == 'M' ? "m" : "l"))) / "layout.md");
    return 0;
}

// --- golden ---
int runGolden(const bench::Args& a) {
    const Venue& v = venueByName(a.get("venue", "S"));
    const int steps = a.getInt("steps", 250);
    const bool cpu = a.getInt("cpu", 0) != 0;
    bench::createHiddenContext("venue_probe");
    const fs::path shaderDir = resolveAsset("shaders");
    auto hashOf = [](const std::vector<GpuBoid>& st) { uint64_t h = 0xcbf29ce484222325ull; plausibility::chainHash(h, st); return h; };
    auto active = [](const std::vector<GpuBoid>& st) { long n = 0; for (const GpuBoid& b : st) n += b.position.w != 0.0f; return n; };
    std::printf("venue_probe golden | venue %s | commit %s (dirty %s) | %s | %d steps\n", v.name, bench::gitCommit().c_str(), bench::gitDirty().c_str(),
                bench::glDriver().c_str(), steps);
    int seated = 0;
    const std::vector<GpuBoid> spawn = spawnSeatedCrowd(v, venue_s::bufferSize(seated::seats(v.layout).size()), 1.0, 1337, &seated);
    const int n = int(spawn.size());
    for (int m = 0; m < 2; ++m) {
        const ModelOptions mo = m == 0 ? defaultModelOptions(v) : ModelOptions{};
        const auto t0 = bench::Clock::now();
        CrowdSim sim(shaderDir, n, v, mo);
        sim.upload(spawn);
        for (int k = 0; k < steps; ++k) sim.step(0);
        const std::vector<GpuBoid> st = bench::readBuffer<GpuBoid>(sim.currentStateBuffer(), size_t(n));
        std::printf("  routed (%s), N %d (%d seated): GPU %016llx, active %ld (%.1f s)\n", modelOptionsLabel(v, mo).c_str(), n, seated,
                    (unsigned long long)hashOf(st), active(st), bench::msSince(t0) / 1000.0);
        if (cpu)
            for (int sm = 0; sm < 2; ++sm) {
                const auto t1 = bench::Clock::now();
                CpuCrowdSim c(v, mo, {}, 0, sm == 0 ? CpuCrowdSim::SortMode::Counting : CpuCrowdSim::SortMode::GpuBitonic);
                c.setState(spawn);
                for (int k = 0; k < steps; ++k) c.step();
                std::printf("    CPU %s %016llx, active %ld (%.1f s)\n", sm == 0 ? "counting" : "bitonic", (unsigned long long)hashOf(c.state()),
                            active(c.state()), bench::msSince(t1) / 1000.0);
            }
        std::fflush(stdout);
    }
    if (a.getInt("forced", 1)) {
        const fs::path variant = venue_s::driveVariant(shaderDir, "golden_drive");
        const venue_s::Setup d = venue_s::denseSetup(v.layout);
        auto runForced = [&](auto& e) {
            e.upload(d.boids);
            std::vector<GpuBoid> prev = d.boids;
            std::vector<glm::vec2> table;
            for (int k = 0; k < steps; ++k) {
                venue_s::driveTable(v.layout, d.plans, prev, table);
                e.setDrive(table);
                e.step();
                prev = e.state();
            }
            return prev;
        };
        {
            venue_s::GpuEngine e(variant, int(d.boids.size()), v);
            const std::vector<GpuBoid> st = runForced(e);
            std::printf("  forced dense, N %zu: GPU %016llx, active %ld\n", d.boids.size(), (unsigned long long)hashOf(st), active(st));
        }
        if (cpu)
            for (int sm = 0; sm < 2; ++sm) {
                venue_s::CpuEngine e(v, 0, sm == 0 ? CpuCrowdSim::SortMode::Counting : CpuCrowdSim::SortMode::GpuBitonic);
                const std::vector<GpuBoid> st = runForced(e);
                std::printf("    CPU %s %016llx, active %ld\n", sm == 0 ? "counting" : "bitonic", (unsigned long long)hashOf(st), active(st));
            }
        fs::remove_all(variant);
    }
    return 0;
}

// --- equiv: the production program, GPU against the CPU reference ---
int runEquiv(const bench::Args& a) {
    const Venue& v = venueByName(a.get("venue", "S"));
    const int midSteps = a.getInt("steps", 200), goldenSteps = a.getInt("golden", golden::GOLDEN_STEPS);
    bench::createHiddenContext("venue_probe");
    const std::string throttle = bench::optOutOfPowerThrottling();
    const fs::path shaderDir = resolveAsset("shaders");
    const std::string lower = v.name[0] == 'S' ? "s" : v.name[0] == 'M' ? "m" : "l";
    const fs::path out = a.get("out", "out/results/venue_" + lower);
    const scene::Select sel(v);
    int seated = 0;
    const std::vector<GpuBoid> spawn = spawnSeatedCrowd(v, venue_s::bufferSize(seated::seats(v.layout).size()), 1.0, 1337, &seated);
    const int n = int(spawn.size());
    const ModelOptions mo = defaultModelOptions(v);
    Report r;
    r.line("# Venue " + std::string(v.name) + ": CPU/GPU equivalence of the production program");
    r.line("");
    r.line(header("equiv") + " | " + bench::glRenderer() + " | " + bench::glDriver() + " | " + throttle);
    r.line("");
    r.line("The full seat spawn (spawnSeatedCrowd, 100%, seed 1337: " + std::to_string(seated) + " agents, buffer N = " + std::to_string(n) + "), routed by the "
           "default model (" + modelOptionsLabel(v, mo) + "), the GPU pipeline (CrowdSim) against the CPU reference (CpuCrowdSim), both sort modes.");
    r.line("");
    auto hashOf = [](const std::vector<GpuBoid>& st) { return golden::stateHash(st); };
    auto activeOf = [](const std::vector<GpuBoid>& st) { long k = 0; for (const GpuBoid& b : st) k += b.position.w != 0.0f; return k; };
    auto gpuRun = [&](const std::vector<GpuBoid>& from, int steps, uint64_t* chain = nullptr) {
        CrowdSim sim(shaderDir, n, v, mo);
        sim.upload(from);
        for (int i = 0; i < steps; ++i) {
            sim.step(0);
            if (chain) plausibility::chainHash(*chain, bench::readBuffer<GpuBoid>(sim.currentStateBuffer(), size_t(n)));
        }
        return bench::readBuffer<GpuBoid>(sim.currentStateBuffer(), size_t(n));
    };
    auto cpuRun = [&](CpuCrowdSim::SortMode mode, int threads, int steps, uint64_t* chain = nullptr) {
        CpuCrowdSim c(v, mo, {}, threads, mode);
        c.setState(spawn);
        for (int i = 0; i < steps; ++i) {
            c.step();
            if (chain) plausibility::chainHash(*chain, c.state());
        }
        return c.state();
    };
    bool ok = true;
    // one step from the GPU state after midSteps steps
    const auto t0 = bench::Clock::now();
    const std::vector<GpuBoid> mid = gpuRun(spawn, midSteps);
    const long active = activeOf(mid);
    std::vector<GpuBoid> g1;
    std::vector<GpuGridInfo> gGrid;
    std::vector<GpuCellData> gCells;
    {
        CrowdSim sim(shaderDir, n, v, mo);
        sim.upload(mid);
        // the exit choice restarts at the upload (CrowdSim::upload / CpuCrowdSim::setState reset it): the same on both sides
        sim.step(0);
        g1 = bench::readBuffer<GpuBoid>(sim.currentStateBuffer(), size_t(n));
        gGrid = bench::readBuffer<GpuGridInfo>(sim.gridBuffer(), size_t(n));
        gCells = bench::readBuffer<GpuCellData>(sim.cellBuffer(), size_t(v.gridRes) * size_t(v.gridRes));
    }
    for (int m = 0; m < 2; ++m) {
        CpuCrowdSim c(v, mo, {}, 0, m == 0 ? CpuCrowdSim::SortMode::Counting : CpuCrowdSim::SortMode::GpuBitonic);
        c.setState(mid);
        c.step();
        long outl = 0, seqDiff = 0, pairDiff = 0;
        float maxD = 0.0f;
        for (size_t i = 0; i < mid.size(); ++i) {
            seqDiff += c.grid()[i].gridID != gGrid[i].gridID;
            pairDiff += c.grid()[i].boidID != gGrid[i].boidID;
            if (mid[i].position.w == 0.0f) continue;
            const float d = glm::length(glm::vec3(c.state()[i].position) - glm::vec3(g1[i].position));
            maxD = std::max(maxD, d);
            outl += d > 2e-4f;
        }
        const bool cellsSame = c.cells().size() == gCells.size() && std::memcmp(c.cells().data(), gCells.data(), gCells.size() * sizeof(GpuCellData)) == 0;
        const bool gridOk = cellsSame && seqDiff == 0 && (m == 0 || pairDiff == 0);
        const bool stepOk = double(outl) < 0.005 * double(active);
        ok &= gridOk && stepOk;
        r.line(std::string("- one step from the GPU state after ") + std::to_string(midSteps) + " steps (" + std::to_string(active) + " active), CPU " +
               (m == 0 ? "counting" : "bitonic") + ": cell table " + (cellsSame ? "identical" : "DIFFERS") + ", gridID sequence differs at " + std::to_string(seqDiff) +
               " slots, (gridID, boidID) pairs at " + std::to_string(pairDiff) + (m == 0 ? " (counting: boidID order within a cell)" : "") + " -> grid " +
               (gridOk ? "**exact**" : "**NOT exact**") + "; |dpos| > 2e-4 for " + std::to_string(outl) + " agents (" + fmt("%.3f%%", 100.0 * double(outl) / double(std::max(active, 1L))) +
               ", limit < 0.5%: " + (stepOk ? "PASS" : "FAIL") + "), max " + fmt("%.2e", maxD));
    }
    // CPU thread invariance, determinism, golden
    uint64_t c1h = 0xcbf29ce484222325ull, cmh = c1h;
    cpuRun(CpuCrowdSim::SortMode::Counting, 1, 100, &c1h);
    cpuRun(CpuCrowdSim::SortMode::Counting, 0, 100, &cmh);
    ok &= c1h == cmh;
    r.line(std::string("- CPU thread invariance (counting, 1 thread vs ") + std::to_string(CpuCrowdSim::maxThreads()) + ", 100 steps, every step's state chained): " +
           (c1h == cmh ? "identical" : "**DIFFER**"));
    const std::vector<GpuBoid> ga = gpuRun(spawn, goldenSteps), gb = gpuRun(spawn, goldenSteps);
    const std::vector<GpuBoid> cc = cpuRun(CpuCrowdSim::SortMode::Counting, 0, goldenSteps), cc2 = cpuRun(CpuCrowdSim::SortMode::Counting, 0, goldenSteps);
    const std::vector<GpuBoid> cb = cpuRun(CpuCrowdSim::SortMode::GpuBitonic, 0, goldenSteps);
    const bool det = hashOf(ga) == hashOf(gb) && hashOf(cc) == hashOf(cc2);
    ok &= det;
    r.line(std::string("- determinism: two GPU runs and two CPU runs of ") + std::to_string(goldenSteps) + " steps: " + (det ? "identical" : "**DIFFER**"));
    char hb[320];
    std::snprintf(hb, sizeof hb, "- **golden** (FNV-1a 64 of the state after %d steps): GPU **%016llx**, CPU counting **%016llx**, CPU bitonic **%016llx** (active %ld / %ld / %ld of %d)",
                  goldenSteps, (unsigned long long)hashOf(ga), (unsigned long long)hashOf(cc), (unsigned long long)hashOf(cb), activeOf(ga), activeOf(cc), activeOf(cb), seated);
    r.line(hb);
    r.line("");
    r.line(std::string("Result: ") + (ok ? "PASS" : "FAIL") + fmt(" (%.0f s)", bench::msSince(t0) / 1000.0));
    r.write(out / "equivalence.md");
    return ok ? 0 : 3;
}

// --- capacity ---
int runCapacity(const bench::Args& a) {
    Report r;
    r.line("# Generated venues: capacity by row count");
    r.line("");
    r.line(header("capacity"));
    r.line("");
    r.line("Venue S's plan and row geometry (generatedVenueParams: every parameter of S but the rows, a door at every gangway head, the exit "
           "sizing rule); the row count chosen for a target capacity is the one whose seat total lies nearest to it. Neighbour grid: the "
           "smallest multiple of 4 cells of 0.05 model units whose half-width exceeds the landings' end by one cell (and whose float cell size is exactly 0.05); metric grid: the smallest "
           "multiple of 16 one-metre cells covering that domain.");
    r.line("");
    r.line("| rows | seats | straight gangways per wing | doors | door width (m) | total exit width (m) | per 1000 seats (m) | outer half-width (m) | concourse z (m) | wall top (m) | grid res | metric res |");
    r.line("|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|");
    struct Best { int rows = 0, seats = 0; } best[2];
    const int targets[2] = { 16000, 64000 };
    for (int rows = 1; rows <= a.getInt("max-rows", 140); ++rows) {
        SeatedVenueParams p = generatedVenueParams("probe", rows, 0, 0);
        SeatedLayout L;
        try { L = buildSeatedLayout(p, 1e9f); } catch (const std::exception& e) { r.line("| " + std::to_string(rows) + " | " + e.what() + " |"); continue; }
        const double cell = double(DOMAIN_SPAN) / GRID_RES;
        int res = 4;
        // (and whose float cell size is exactly DOMAIN_SPAN / GRID_RES, makeSeated's check: 72 and 124 are not)
        auto exact = [&](int r) { const float span = float(double(r) * cell); return span / float(r) == DOMAIN_SPAN / float(GRID_RES); };
        while (0.5 * res * cell <= double(L.landingEnd) + cell || !exact(res)) res += 4;
        const double halfM = units::metres(0.5 * res * cell);
        int mres = 16;
        while (0.5 * mres < halfM) mres += 16;
        if (rows <= 20 || rows % 4 == 0 || std::abs(L.seatTotal - 16000) < 900 || std::abs(L.seatTotal - 64000) < 1800)
            r.line("| " + std::to_string(rows) + " | " + std::to_string(L.seatTotal) + " | " + std::to_string(L.gangways) + " | " + std::to_string(4 * L.doorsPerQuadrant()) + " | " +
                   fmt("%.1f", L.doorWidthM) + " | " + fmt("%.1f", L.totalExitWidthM) + " | " + fmt("%.2f", 1000.0 * L.totalExitWidthM / L.seatTotal) + " | " +
                   fmt("%.2f", m(L.outerFace)) + " | " + fmt("%.2f", m(L.concourseZ)) + " | " + fmt("%.2f", m(L.wallTop)) + " | " + std::to_string(res) + " | " + std::to_string(mres) + " |");
        for (int t = 0; t < 2; ++t)
            if (best[t].rows == 0 || std::abs(L.seatTotal - targets[t]) < std::abs(best[t].seats - targets[t])) best[t] = { rows, L.seatTotal };
    }
    r.line("");
    for (int t = 0; t < 2; ++t) r.line("Nearest " + std::to_string(targets[t]) + " seats: **" + std::to_string(best[t].rows) + " rows, " + std::to_string(best[t].seats) + " seats**.");
    r.line("");
    r.line("## Venues S, M, L");
    r.line("");
    r.line("| venue | rows | seats | outer half-width (m) | concourse z (m) | wall top (m) | straight gangways per wing | gangway heads | doors | door width (m) | corner door (m) | "
           "total exit width (m) | required (m) | exit width per 1000 (m) | design egress time (min) | grid res | domain half-width (m) | metric res |");
    r.line("|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|");
    for (const Venue* v : seatedVenues()) {
        const SeatedLayout& L = v->layout;
        r.line("| " + std::string(v->name) + " | " + std::to_string(L.rows) + " | " + std::to_string(L.seatTotal) + " | " + fmt("%.2f", m(L.outerFace)) + " | " +
               fmt("%.2f", m(L.concourseZ)) + " | " + fmt("%.2f", m(L.wallTop)) + " | " + std::to_string(L.gangways) + " | " + std::to_string(seated::gangwayCount(*&L)) + " | " +
               std::to_string(4 * L.doorsPerQuadrant()) + " | " + fmt("%.1f", L.doorWidthM) + " | " + (L.cornerDoorLo < 1e8f ? fmt("%.2f", L.cornerDoorWidthM) : std::string("-")) + " | " +
               fmt("%.2f", L.totalExitWidthM) + " | " + fmt("%.2f", L.requiredExitWidthM) + " | " + fmt("%.2f", 1000.0 * L.totalExitWidthM / L.seatTotal) + " | " +
               fmt("%.1f", L.seatTotal / (v->params.exitRatePerMMin * L.totalExitWidthM)) + " | " + std::to_string(v->gridRes) + " | " + fmt("%.2f", m(v->domainMax())) + " | " +
               std::to_string(v->metricGridRes) + " |");
    }
    r.write(fs::path(a.get("out", "out/results/venues")) / "capacity.md");
    return 0;
}

// --- overcrowd ---
std::string hex16(uint64_t v) { char b[24]; std::snprintf(b, sizeof b, "%016llx", (unsigned long long)v); return b; }
// Each seated venue's standing floor, the density cap's maximum and the achievable loads; the spawns of the experiment matrix's
// overcrowded cases (requested 125% / 150%, the gangway variant on S; seeds 1-3): who stands where, the closest centre distance, the
// initial densities by the metric's own cloud-in-cell deposit on the venue's metric grid (cells of at least PEAK_MIN_WALKABLE_M2)
int runOvercrowd(const bench::Args& a) {
    namespace mt = swarm::metrics;
    Report r;
    r.line("# Overcrowding spawn: standing floor, capacity, initial densities");
    r.line("");
    r.line(header("overcrowd"));
    r.line("");
    r.line("spawnOvercrowdedCrowd (include/swarm/crowd_sim.hpp): every seat filled (the 100% seat spawn, bit for bit), plus round((load - 1) x seats) "
           "people standing at rest on the walkway (fence's outer face -> barrier) and the rear concourse (the gangway variant: also the gangways), "
           "seeded uniform random placement, no body overlap, at most OVERCROWD_STANDING_MAX_P_M2 = " + fmt("%.1f", OVERCROWD_STANDING_MAX_P_M2) +
           " persons/m^2 of standing floor initially. A load the floor cannot take is reduced to the achievable maximum.");
    r.line("");
    r.line("## Standing floor and the achievable maximum");
    r.line("");
    r.line("| venue | seats | walkway (m^2) | concourse (m^2) | gangways (m^2) | standing floor (m^2) | max standing | **max load** | with gangways: floor (m^2) | max standing | max load | jam capacity |");
    r.line("|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|");
    for (const Venue* v : seatedVenues()) {
        const seated::Areas A = seated::areas(v->layout);
        const int seats = int(seated::seats(v->layout).size());
        const double f1 = A.walkway + A.concourse, f2 = f1 + A.gangways;
        const int m1 = int(std::floor(OVERCROWD_STANDING_MAX_P_M2 * f1)), m2 = int(std::floor(OVERCROWD_STANDING_MAX_P_M2 * f2));
        r.line("| " + std::string(v->name) + " | " + std::to_string(seats) + " | " + fmt("%.1f", A.walkway) + " | " + fmt("%.1f", A.concourse) + " | " +
               fmt("%.1f", A.gangways) + " | " + fmt("%.1f", f1) + " | " + std::to_string(m1) + " | **" + fmt("%.2f", 100.0 * (seats + m1) / seats) + "%** | " +
               fmt("%.1f", f2) + " | " + std::to_string(m2) + " | " + fmt("%.2f", 100.0 * (seats + m2) / seats) + "% | " +
               std::to_string(swarm::venue::capacityOf(*v).jam) + " |");
    }
    r.line("");
    r.line("## The matrix's spawns");
    r.line("");
    r.line("Initial density: the metric's cloud-in-cell deposit of the spawn (every agent, seated ones included) per 1 m cell of the venue's metric grid, "
           "over cells of at least " + fmt("%.1f", mt::PEAK_MIN_WALKABLE_M2) + " m^2 of floor; standing cells: the walkway zone (walkway and concourse; "
           "the gangway variant: and the gangways).");
    r.line("");
    r.line("| venue | requested | standing areas | seed | standing (requested / max) | walkway / concourse / gangways | **load** | draws | closest centres (m) | "
           "mean standing density (p/m^2) | max standing cell (p/m^2) | standing cells >= LoS F / crush | spawn FNV-1a |");
    r.line("|---|---:|---|---:|---|---|---:|---:|---:|---:|---:|---|---|");
    struct Case { const Venue* v; double load; StandingAreas areas; };
    std::vector<Case> cases;
    for (const Venue* v : seatedVenues())
        for (double l : { 1.25, 1.5 }) cases.push_back({ v, l, StandingAreas::Circulation });
    cases.push_back({ &venueS(), 1.5, StandingAreas::WithGangways });
    for (const Case& c : cases) {
        const mt::MetricVenue mv = mt::computeMetricVenue(*c.v);
        for (unsigned seed : { 1u, 2u, 3u }) {
            const OvercrowdSpawn sp = spawnOvercrowdedCrowd(*c.v, c.load, seed, c.areas);
            // closest centre distance of a standing agent to any other agent (hash grid of BODY_DIAM cells)
            std::map<std::pair<int, int>, std::vector<int>> grid;
            for (int i = 0; i < sp.seats + sp.standing; ++i)
                grid[{ int(std::floor(sp.boids[size_t(i)].position.x / BODY_DIAM)), int(std::floor(sp.boids[size_t(i)].position.y / BODY_DIAM)) }].push_back(i);
            float minD = 1e9f;
            for (int i = sp.seats; i < sp.seats + sp.standing; ++i) {
                const glm::vec3 p(sp.boids[size_t(i)].position);
                const int gx = int(std::floor(p.x / BODY_DIAM)), gy = int(std::floor(p.y / BODY_DIAM));
                for (int dy = -1; dy <= 1; ++dy)
                    for (int dx = -1; dx <= 1; ++dx) {
                        const auto it = grid.find({ gx + dx, gy + dy });
                        if (it == grid.end()) continue;
                        for (int j : it->second)
                            if (j != i) minD = std::min(minD, glm::length(p - glm::vec3(sp.boids[size_t(j)].position)));
                    }
            }
            std::vector<uint64_t> mass(mv.walkableM2.size(), 0);
            for (const GpuBoid& b : sp.boids) {
                if (b.position.w == 0.0f) continue;
                const mt::CicDeposit d = mt::cicDeposit(glm::vec2(b.position), mv.res);
                for (int k = 0; k < 4; ++k) mass[size_t(d.cell[k])] += d.weight[k];
            }
            double maxCell = 0.0;
            int aboveF = 0, aboveCrush = 0, cellsN = 0;
            for (size_t cI = 0; cI < mass.size(); ++cI) {
                if (!mv.included[cI] || mv.walkableM2[cI] < mt::PEAK_MIN_WALKABLE_M2) continue;
                const bool standing = mv.zone[cI] == mt::ZONE_WALKWAY || (c.areas == StandingAreas::WithGangways && mv.zone[cI] == mt::ZONE_AISLE);
                if (!standing) continue;
                const double dens = double(mass[cI]) / mt::MASS_ONE / double(mv.walkableM2[cI]);
                ++cellsN;
                maxCell = std::max(maxCell, dens);
                aboveF += dens >= mt::LOS_F_P_M2;
                aboveCrush += dens >= mt::CRUSH_P_M2;
            }
            r.line("| " + std::string(c.v->name) + " | " + fmt("%.0f%%", 100.0 * c.load) + " | " + standingAreasName(c.areas) + " | " + std::to_string(seed) + " | " +
                   std::to_string(sp.standing) + " (" + std::to_string(sp.standingRequested) + " / " + std::to_string(sp.standingMax) + ")" +
                   (sp.placementExhausted ? " EXHAUSTED" : "") + " | " + std::to_string(sp.standingWalkway) + " / " + std::to_string(sp.standingConcourse) + " / " +
                   std::to_string(sp.standingGangways) + " | **" + fmt("%.2f%%", 100.0 * sp.load) + "** | " + std::to_string(sp.draws) + " | " +
                   fmt("%.3f", m(minD)) + " | " + fmt("%.3f", sp.standing / sp.standingAreaM2) + " | " + fmt("%.2f", maxCell) + " | " + std::to_string(aboveF) +
                   " / " + std::to_string(aboveCrush) + " of " + std::to_string(cellsN) + " | " + hex16(golden::stateHash(sp.boids)) + " |");
        }
    }
    r.line("");
    r.line("Closest centres: of a standing agent to any other agent (3D); BODY_DIAM = 0.40 m, the placement keeps BODY_DIAM + " +
           fmt("%.2f", m(STANDING_CLEARANCE_MARGIN)) + " m. A requested load whose standing crowd exceeds the cap gets the cap: M and L reach the same "
           "maximum at 125% and 150% (the same spawn for a seed).");
    r.write(fs::path(a.get("out", "out/results/venues")) / "overcrowding.md");
    return 0;
}

// --- exact ---
// physics.comp's @sdf block (map, mapExactGrad, floorUnderReach) compiled with the venue's preamble, plus an entry
GLuint sdfBlockProbe(const fs::path& shaderDir, const Venue& v, const std::string& entry) {
    std::ifstream pf(shaderDir / "physics.comp");
    std::stringstream ss;
    ss << pf.rdbuf();
    const std::string phys = ss.str();
    const size_t b = phys.find("// @sdf-begin"), e = phys.find("// @sdf-end");
    if (b == std::string::npos || e == std::string::npos) throw std::runtime_error("physics.comp lacks the @sdf markers");
    const fs::path tmp = processTempPath("swarm_venue_probe.comp");
    { std::ofstream(tmp) << "#version 430 core\n" + phys.substr(b, e - b) + entry; }
    GLuint prog = loadComputeProgram(tmp, {}, &v);
    fs::remove(tmp);
    return prog;
}

template <class T>
GLuint makeBuffer(const std::vector<T>& data) {
    GLuint buf = 0;
    glGenBuffers(1, &buf);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, buf);
    glBufferData(GL_SHADER_STORAGE_BUFFER, GLsizeiptr(data.size() * sizeof(T)), data.data(), GL_DYNAMIC_COPY);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    return buf;
}

// Random points in the venue: x, y uniform over the landings' square, z from 0.5 m below to 1.5 m above the floor
std::vector<glm::vec3> randomPoints(const SeatedLayout& L, int n, unsigned seed) {
    std::mt19937 gen(seed);
    std::uniform_real_distribution<float> xy(-L.landingEnd, L.landingEnd), dz(float(units::modelLength(-0.5)), float(units::modelLength(1.5)));
    std::vector<glm::vec3> pts;
    pts.reserve(size_t(n));
    while (int(pts.size()) < n) {
        const glm::vec2 q(xy(gen), xy(gen));
        pts.emplace_back(q, seated::floorHeight(L, q) + dz(gen));
    }
    return pts;
}

int runExact(const bench::Args& a) {
    const Venue& v = venueByName(a.get("venue", "S"));
    const SeatedLayout& L = v.layout;
    const int n = a.getInt("points", 100000);
    const unsigned seed = unsigned(a.getInt("seed", 7));
    const std::vector<seated::Primitive> prims = seated::primitives(L);
    const std::vector<glm::vec3> pts = randomPoints(L, n, seed);
    Report r;
    r.line("# Venue " + std::string(v.name) + ": analytic distance, exactness");
    r.line("");
    r.line(header("exact"));
    r.line("");
    r.line(std::to_string(n) + " random points (seed " + std::to_string(seed) + "): x, y uniform over |x|, |y| <= " + fmt("%.2f m", m(L.landingEnd)) +
           ", z uniform from 0.5 m below to 1.5 m above the floor there. Brute force: " + std::to_string(prims.size()) +
           " solid primitives (seated::primitives, unfolded) and the ground half-space, double precision.");
    r.line("");

    // CPU mirror against the brute force
    std::vector<float> val(static_cast<size_t>(n));
    std::vector<glm::vec4> grad(static_cast<size_t>(n));
    std::vector<int> bandsVisited(static_cast<size_t>(n)), cellsVisited(static_cast<size_t>(n));
    std::vector<char> insideBF(static_cast<size_t>(n));
    std::vector<double> bf(static_cast<size_t>(n));
#pragma omp parallel for schedule(dynamic, 256)
    for (int i = 0; i < n; ++i) {
        seated::EvalStats st;
        grad[size_t(i)] = seated::sdfGradStats(L, pts[size_t(i)], st);
        val[size_t(i)] = grad[size_t(i)].w;
        bandsVisited[size_t(i)] = st.bands;
        cellsVisited[size_t(i)] = st.cells;
        const glm::dvec3 pd(pts[size_t(i)]);
        insideBF[size_t(i)] = seated::bruteForceInside(prims, pd);
        bf[size_t(i)] = insideBF[size_t(i)] ? 0.0 : seated::bruteForceDistance(prims, pd);
    }
    long outside = 0, inside = 0, signErr = 0;
    double maxOut = 0.0, maxOutRel = 0.0;
    for (int i = 0; i < n; ++i) {
        const bool in = insideBF[size_t(i)] != 0;
        if ((val[size_t(i)] > 0.0f) == in) ++signErr;
        if (in) { ++inside; continue; }
        ++outside;
        const double d = std::abs(double(val[size_t(i)]) - bf[size_t(i)]);
        maxOut = std::max(maxOut, d);
        maxOutRel = std::max(maxOutRel, d / std::max(bf[size_t(i)], 1e-12));
    }
    r.line("## CPU mirror (seated::sdf) vs brute force");
    r.line("");
    r.line("- sign (solid iff z <= floorHeight vs the primitive list): " + std::to_string(signErr) + " disagreements of " + std::to_string(n));
    r.line("- outside the solid (" + std::to_string(outside) + " points): max |sdf - brute force| = " + fmt("%.3g", maxOut) +
           " model units (" + fmt("%.3g", units::metres(maxOut)) + " m), limit 1e-6: " + (maxOut <= 1e-6 ? "PASS" : "FAIL"));

    // Inside: the sphere test (and on the surface: the point moved along the gradient)
    long sphereBad = 0, surfBad = 0;
    double maxSurf = 0.0;
    const int dirs = 64;
#pragma omp parallel for schedule(dynamic, 256) reduction(+ : sphereBad, surfBad)
    for (int i = 0; i < n; ++i) {
        if (!insideBF[size_t(i)]) continue;
        const float d = -val[size_t(i)];
        const glm::dvec3 p(pts[size_t(i)]);
        bool bad = false;
        for (int k = 0; k < dirs && !bad; ++k) {   // Fibonacci sphere at 0.999 d: inside the solid
            const double zz = 1.0 - 2.0 * (k + 0.5) / dirs, rr = std::sqrt(1.0 - zz * zz), ph = 2.39996322972865 * k;
            const glm::dvec3 u(rr * std::cos(ph), rr * std::sin(ph), zz);
            if (!seated::bruteForceInside(prims, p + u * (0.999 * double(d)))) bad = true;
        }
        sphereBad += bad;
        const glm::dvec3 g(grad[size_t(i)]);
        const glm::dvec3 beyond = p + g * (double(d) + 1e-6), before = p + g * std::max(double(d) - 1e-6, 0.0);
        if (d > 2e-6f && (seated::bruteForceInside(prims, beyond) || !seated::bruteForceInside(prims, before))) ++surfBad;
    }
    r.line("- inside the solid (" + std::to_string(inside) + " points): the ball of radius 0.999 |sdf| (64 directions) lies in the solid at " +
           std::to_string(inside - sphereBad) + "; the point moved |sdf| along the gradient leaves the solid within 1e-6 at " +
           std::to_string(inside - surfBad) + " (" + (sphereBad == 0 && surfBad == 0 ? "PASS: exact" : "FAIL") + ")");
    (void)maxSurf;

    // Eikonal: central differences at points away from kinks
    const float h = 1e-4f;
    long tested = 0, eikBad = 0;
    double maxEik = 0.0, maxFdVsAnalytic = 0.0;
#pragma omp parallel for schedule(dynamic, 256) reduction(+ : tested, eikBad)
    for (int i = 0; i < n; ++i) {
        const glm::vec3 p = pts[size_t(i)];
        const glm::vec3 g0(grad[size_t(i)]);
        // h scales with the coordinates' magnitude beyond 1 unit (float steps of a point near |x| = 3, venue L's edge, are 2.4e-7:
        // a fixed h of 1e-4 would leave the differences' own rounding at ~1e-3), and the difference divides by the step actually taken
        const float hp = h * std::max(1.0f, std::max(std::abs(p.x), std::abs(p.y)));
        bool smooth = std::abs(val[size_t(i)]) > 2.0f * hp;
        glm::vec3 fd(0.0f);
        for (int ax = 0; ax < 3 && smooth; ++ax) {
            glm::vec3 e(0.0f);
            e[ax] = hp;
            const glm::vec3 pp = p + e, pm = p - e;
            const glm::vec4 gp = seated::sdfGrad(L, pp), gm = seated::sdfGrad(L, pm);
            if (glm::length(glm::vec3(gp) - g0) > 1e-3f || glm::length(glm::vec3(gm) - g0) > 1e-3f) smooth = false;
            fd[ax] = float((double(gp.w) - double(gm.w)) / (double(pp[ax]) - double(pm[ax])));
        }
        if (!smooth) continue;
        ++tested;
        const double dev = std::abs(double(glm::length(fd)) - 1.0);
        if (dev > 1e-3) ++eikBad;
#pragma omp critical
        {
            maxEik = std::max(maxEik, dev);
            maxFdVsAnalytic = std::max(maxFdVsAnalytic, double(glm::length(fd - g0)));
        }
    }
    r.line("- Eikonal (central differences h = 1e-4 x max(1, |x|, |y|), at " + std::to_string(tested) + " points away from kinks, |sdf| > 2h): max ||grad| - 1| = " +
           fmt("%.2e", maxEik) + " (limit 1e-3: " + (eikBad == 0 && tested > n / 2 ? "PASS" : "FAIL") + "); max |finite differences - analytic gradient| = " +
           fmt("%.2e", maxFdVsAnalytic));
    {
        std::vector<int> b = bandsVisited, c = cellsVisited;
        std::sort(b.begin(), b.end());
        std::sort(c.begin(), c.end());
        r.line("- cost: bands visited per evaluation median " + std::to_string(b[b.size() / 2]) + ", max " + std::to_string(b.back()) +
               "; cells evaluated median " + std::to_string(c[c.size() / 2]) + ", p99 " + std::to_string(c[c.size() * 99 / 100]) + ", max " +
               std::to_string(c.back()) + " (of " + std::to_string(seated::bandCount(L)) + " bands, <= 6 cells each)");
    }

    // The wall query (physics.comp clearWalls / wallPlaneProbe on the analytic venue) against the brute force in each point's
    // horizontal plane: outside every wall the 2D distance to the nearest taller box footprint, inside the sign
    const float wallReach = float(units::modelLength(1.5));
    long wallOut = 0, wallIn = 0, wallSignErr = 0;
    double maxWall = 0.0;
    std::vector<glm::vec3> wq(static_cast<size_t>(n));
#pragma omp parallel for schedule(dynamic, 256) reduction(+ : wallOut, wallIn, wallSignErr)
    for (int i = 0; i < n; ++i) {
        const glm::vec3 w = seated::wall(L, pts[size_t(i)], wallReach);
        wq[size_t(i)] = w;
        if (pts[size_t(i)].z < 0.0f) continue;   // below ground: no body centre is (the ground is a half-space in the brute force)
        bool inside = false;
        const double bfw = seated::bruteForceWall(prims, glm::dvec3(pts[size_t(i)]), inside);
        if (inside != (w.z < 0.0f)) { ++wallSignErr; continue; }
        if (inside) { ++wallIn; continue; }
        if (bfw >= double(wallReach)) { wallSignErr += w.z < seated::WALL_NONE && double(w.z) < double(wallReach) - 1e-6; continue; }
        ++wallOut;
        const double d = std::abs(double(w.z) - bfw);
#pragma omp critical
        {
            maxWall = std::max(maxWall, d);
            if (d > 1e-6 && a.has("verbose")) {
                const glm::vec2 f = seated::fold(glm::vec2(pts[size_t(i)]));
                std::printf("  wall mismatch at (%.5f %.5f %.5f) folded (%.5f %.5f) band %d: query %.6f brute %.6f\n", pts[size_t(i)].x, pts[size_t(i)].y,
                            pts[size_t(i)].z, f.x, f.y, seated::bandOf(L, f.y), w.z, bfw);
            }
        }
    }
    r.line("- wall query (seated::wall: the nearest vertical face reaching a point's horizontal plane; physics' clearWalls on S; points above ground): " +
           std::to_string(wallOut) + " points outside every wall with one within 1.5 m: max |clearance - brute force| = " + fmt("%.3g", maxWall) +
           " (limit 1e-6: " + (maxWall <= 1e-6 ? "PASS" : "FAIL") + "); inside a wall at " + std::to_string(wallIn) + "; sign / reach disagreements " +
           std::to_string(wallSignErr));

    // GPU: physics.comp's map / mapExactGrad / floorUnderReach on the venue preamble
    bench::createHiddenContext("venue_probe");
    const fs::path shaderDir = resolveAsset("shaders");
    GLuint prog = sdfBlockProbe(shaderDir, v,
        "layout(local_size_x = 64) in;\n"
        "layout(std430, binding = 5) buffer P { vec4 pts[]; };\n"
        "layout(std430, binding = 6) buffer R { vec4 outg[]; };\n"
        "layout(std430, binding = 7) buffer F { vec4 outf[]; };\n"
        "layout(std430, binding = 8) buffer W { vec4 outw[]; };\n"
        "uniform int count; uniform float wallReach;\n"
        "void main() { uint i = gl_GlobalInvocationID.x; if (i >= uint(count)) return; vec3 p = pts[i].xyz;\n"
        "  outg[i] = mapExactGrad(p); float zf; bool ok = floorUnderReach(p, p.z, 1.0, zf);\n"
        "  outf[i] = vec4(map(p), venueFloor(p.xy), ok ? zf : -1.0, 0.0); outw[i] = vec4(venueWall(p, wallReach), 0.0); }\n");
    std::vector<glm::vec4> in;
    for (const glm::vec3& p : pts) in.emplace_back(p, 1.0f);
    GLuint bin = makeBuffer(in), bg = makeBuffer(std::vector<glm::vec4>(in.size())), bfz = makeBuffer(std::vector<glm::vec4>(in.size())),
           bw = makeBuffer(std::vector<glm::vec4>(in.size()));
    glUseProgram(prog);
    glUniform1i(glGetUniformLocation(prog, "count"), n);
    glUniform1f(glGetUniformLocation(prog, "wallReach"), wallReach);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, bin);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, bg);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 7, bfz);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 8, bw);
    glDispatchCompute(GLuint((n + 63) / 64), 1, 1);
    const std::vector<glm::vec4> gg = bench::readBuffer<glm::vec4>(bg, size_t(n)), gf = bench::readBuffer<glm::vec4>(bfz, size_t(n)),
                                 gw = bench::readBuffer<glm::vec4>(bw, size_t(n));
    double maxWallGpu = 0.0;
    for (int i = 0; i < n; ++i)
        if (wq[size_t(i)].z < seated::WALL_NONE) maxWallGpu = std::max(maxWallGpu, double(std::abs(gw[size_t(i)].z - wq[size_t(i)].z)));
    glDeleteBuffers(1, &bw);
    double maxVal = 0.0, maxGrad = 0.0, maxMapVsGrad = 0.0;
    long floorDiff = 0, floorMiss = 0;
    for (int i = 0; i < n; ++i) {
        maxVal = std::max(maxVal, double(std::abs(gg[size_t(i)].w - val[size_t(i)])));
        maxMapVsGrad = std::max(maxMapVsGrad, double(std::abs(gf[size_t(i)].x - gg[size_t(i)].w)));
        if (std::abs(val[size_t(i)]) > 1e-5f) maxGrad = std::max(maxGrad, double(glm::length(glm::vec3(gg[size_t(i)]) - glm::vec3(grad[size_t(i)]))));
        const float hc = seated::floorHeight(L, glm::vec2(pts[size_t(i)]));
        if (gf[size_t(i)].y != hc) ++floorDiff;
        // floorUnderReach (reach 1.0 down from a free centre; BODY_RADIUS up from one in solid) returns the floor height itself
        const glm::vec3 c = pts[size_t(i)];
        const bool expect = c.z > hc || hc <= c.z + BODY_RADIUS;
        if (gf[size_t(i)].z != (expect ? hc : -1.0f)) ++floorMiss;
    }
    r.line("");
    r.line("## GPU (physics.comp map / mapExactGrad / floorUnderReach on the venue preamble) vs the CPU mirror, " + std::to_string(n) + " points");
    r.line("");
    r.line("- value: max |GPU - CPU| = " + fmt("%.3g", maxVal) + " (rounding level: GPU sqrt and division); map() vs mapExactGrad().w on the GPU: " +
           fmt("%.3g", maxMapVsGrad));
    r.line("- gradient (|sdf| > 1e-5): max |GPU - CPU| = " + fmt("%.3g", maxGrad));
    r.line("- gradient: the largest differences are at points within ~1e-5 of the surface, where |q - p| is a few float steps (relative rounding)");
    r.line("- wall query (venueWall): max |GPU - CPU| clearance = " + fmt("%.3g", maxWallGpu));
    r.line("- floor height (venueFloor): " + std::to_string(n - floorDiff) + " of " + std::to_string(n) + " bit-identical; floorUnderReach returns it " +
           "(found or not found as its reach rule says: down 1.0 from a free centre, up BODY_RADIUS from one in solid) at " +
           std::to_string(n - floorMiss) + " (" + (floorDiff == 0 && floorMiss == 0 ? "PASS" : "FAIL") + ")");
    glDeleteBuffers(1, &bin);
    glDeleteBuffers(1, &bg);
    glDeleteBuffers(1, &bfz);
    glDeleteProgram(prog);
    r.write(fs::path(a.get("out", std::string("out/results/venue_") + (v.name[0] == 'S' ? "s" : v.name[0] == 'M' ? "m" : "l"))) / "sdf_exactness.md");
    const bool ok = signErr == 0 && maxOut <= 1e-6 && sphereBad == 0 && surfBad == 0 && eikBad == 0 && floorDiff == 0 && floorMiss == 0 &&
                    maxWall <= 1e-6 && wallSignErr == 0 && maxWallGpu <= 1e-6;
    std::printf("%s\n", ok ? "ALL PASSED" : "FAILED");
    return ok ? 0 : 1;
}

// --- timing ---
int runTiming(const bench::Args& a) {
    const Venue& v = venueByName(a.get("venue", "S"));
    const int n = a.getInt("points", 262144), calls = a.getInt("calls", 64), reps = a.getInt("reps", 15);
    bench::createHiddenContext("venue_probe");
    const std::string throttle = bench::optOutOfPowerThrottling();
    const fs::path shaderDir = resolveAsset("shaders");
    GLuint sdfTex = loadSDFTexture3D(resolveAsset("stadium.sdf"));
    // Near-surface points: S's floor + rest height, jittered; the terrace's the same over its baked floor (CPU sampler)
    std::mt19937 gen(3);
    std::uniform_real_distribution<float> xy(-0.9f, 0.9f), jit(-0.004f, 0.004f);
    std::vector<glm::vec4> ptsS, ptsT;
    while (int(ptsS.size()) < n) {
        const glm::vec2 q(xy(gen), xy(gen));
        ptsS.emplace_back(q, seated::floorHeight(v.layout, q) + BODY_RADIUS + jit(gen), 1.0f);
    }
    while (int(ptsT.size()) < n) {
        const glm::vec2 q(xy(gen), xy(gen));
        float z = 0.2f;
        while (z > -0.05f && sampleSDF_CPU(glm::vec3(q, z)) > 0.0f) z -= 0.002f;
        ptsT.emplace_back(q, z + BODY_RADIUS + jit(gen), 1.0f);
    }
    // Each invocation calls the function 'calls' times along a short jittered walk (dependent inputs: no reuse)
    auto probe = [&](const Venue& venue, const char* fn) {
        return sdfBlockProbe(shaderDir, venue, std::string(
            "layout(local_size_x = 64) in;\n"
            "layout(std430, binding = 5) buffer P { vec4 pts[]; };\n"
            "layout(std430, binding = 6) buffer R { float outs[]; };\n"
            "uniform int count; uniform int calls;\n"
            "void main() { uint i = gl_GlobalInvocationID.x; if (i >= uint(count)) return; vec3 p = pts[i].xyz; float acc = 0.0;\n"
            "  for (int c = 0; c < calls; ++c) { float d = ") + fn + "; acc += d; p += vec3(1e-4 * sign(d), 7e-5, -3e-5); }\n"
            "  outs[i] = acc; }\n");
    };
    struct Case { const char* name; const Venue* venue; std::vector<glm::vec4>* pts; const char* fn; };
    const Case cases[] = { { "baked texture map()", &terraceVenue(), &ptsT, "map(p)" },
                           { "analytic S map()", &v, &ptsS, "map(p)" },
                           { "baked texture mapExactGrad()", &terraceVenue(), &ptsT, "mapExactGrad(p).w" },
                           { "analytic S mapExactGrad()", &v, &ptsS, "mapExactGrad(p).w" } };
    Report r;
    r.line("# Venue " + std::string(v.name) + ": GPU cost of map()");
    r.line("");
    r.line(header("timing") + " | " + bench::glRenderer() + " | " + bench::glDriver() + " | " + throttle);
    r.line("");
    r.line(std::to_string(n) + " invocations x " + std::to_string(calls) + " calls each (a dependent walk from near-surface points: the rest height above the floor, +-4 mm),"
           " GL_TIME_ELAPSED per dispatch, " + std::to_string(reps) + " repetitions after 3 warm-up dispatches; ns per call = time / calls. "
           "Physics.comp's own functions (the @sdf block on each venue's preamble).");
    r.line("");
    r.line("| function | median ns/call | min | max | ratio to the baked texture |");
    r.line("|---|---:|---:|---:|---:|");
    double baked[2] = { 0, 0 };
    GLuint q;
    glGenQueries(1, &q);
    for (int ci = 0; ci < 4; ++ci) {
        const Case& c = cases[ci];
        GLuint prog = probe(*c.venue, c.fn);
        GLuint bin = makeBuffer(*c.pts), bout = makeBuffer(std::vector<float>(size_t(n)));
        glUseProgram(prog);
        glUniform1i(glGetUniformLocation(prog, "count"), n);
        glUniform1i(glGetUniformLocation(prog, "calls"), calls);
        glUniform3fv(glGetUniformLocation(prog, "u_sdfMin"), 1, &SDF_MIN[0]);
        glUniform1f(glGetUniformLocation(prog, "u_sdfInvSpacing"), 1.0f / SDF_SPACING);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_3D, sdfTex);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, bin);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, bout);
        std::vector<double> ns;
        for (int rep = 0; rep < reps + 3; ++rep) {
            glBeginQuery(GL_TIME_ELAPSED, q);
            glDispatchCompute(GLuint((n + 63) / 64), 1, 1);
            glEndQuery(GL_TIME_ELAPSED);
            GLuint64 t = 0;
            glGetQueryObjectui64v(q, GL_QUERY_RESULT, &t);
            if (rep >= 3) ns.push_back(double(t) / (double(n) * calls));
        }
        const bench::Stats s = bench::stats(ns);
        if (ci == 0) baked[0] = s.median;
        if (ci == 2) baked[1] = s.median;
        const double ref = baked[ci / 2];
        r.line("| " + std::string(c.name) + " | " + fmt("%.4f", s.median) + " | " + fmt("%.4f", s.min) + " | " + fmt("%.4f", s.max) + " | " +
               (ci % 2 ? fmt("%.1fx", s.median / ref) : std::string("1.0x")) + " |");
        glDeleteBuffers(1, &bin);
        glDeleteBuffers(1, &bout);
        glDeleteProgram(prog);
    }
    glDeleteQueries(1, &q);
    r.line("");
    r.line("Note: ns per call over the whole GPU (all compute units in parallel): a throughput figure, not the latency of one call.");
    r.write(fs::path(a.get("out", std::string("out/results/venue_") + (v.name[0] == 'S' ? "s" : v.name[0] == 'M' ? "m" : "l"))) / "map_timing.md");
    return 0;
}

// --- obj ---
int runObj(const bench::Args& a) {
    const Venue& v = venueByName(a.get("venue", "S"));
    const SeatedLayout& L = v.layout;
    const std::vector<float> mesh = seated::mesh(L);
    long tris = long(mesh.size() / 18), bad = 0, fenceTris = 0;
    const float eps = 1e-4f;
    const glm::vec2 mid(FENCE_HALF_MID.x, FENCE_HALF_MID.y);
    auto fenceBox = [&](glm::vec3 p) {   // the visual fence ring as a box SDF sign: < 0 inside
        const float ring = std::abs(sdBox2(glm::vec2(p), mid)) - FENCE_HALF_THK_VISUAL;
        return std::max(ring, std::max(-p.z, p.z - 0.025802f));
    };
    for (long t = 0; t < tris; ++t) {
        const float* f = &mesh[size_t(t) * 18];
        const glm::vec3 c = (glm::vec3(f[0], f[1], f[2]) + glm::vec3(f[6], f[7], f[8]) + glm::vec3(f[12], f[13], f[14])) / 3.0f;
        const glm::vec3 nrm(f[3], f[4], f[5]);
        // Outward: just outside along the normal is free, just inside is solid, for the venue or (the fence's faces) its box
        const bool venueOk = seated::sdf(L, c + nrm * eps) > 0.0f && seated::sdf(L, c - nrm * eps) <= 0.0f;
        const bool fenceOk = fenceBox(c + nrm * eps) > 0.0f && fenceBox(c - nrm * eps) < 0.0f;
        if (!venueOk && fenceOk) ++fenceTris;
        const glm::vec3 cr = glm::cross(glm::vec3(f[6], f[7], f[8]) - glm::vec3(f[0], f[1], f[2]), glm::vec3(f[12], f[13], f[14]) - glm::vec3(f[0], f[1], f[2]));
        if ((!venueOk && !fenceOk) || glm::dot(cr, nrm) <= 0.0f) {
            if (bad < 12 && a.has("verbose"))
                std::printf("  bad: centroid (%.5f %.5f %.5f) normal (%.3f %.3f %.3f) sdf out %.3g in %.3g, winding %s, area %.3g\n", c.x, c.y, c.z,
                            nrm.x, nrm.y, nrm.z, seated::sdf(L, c + nrm * eps), seated::sdf(L, c - nrm * eps),
                            glm::dot(cr, nrm) > 0.0f ? "ok" : "clockwise", 0.5f * glm::length(cr));
            ++bad;
        }
    }
    const fs::path out = fs::path(a.get("out", ".")) / v.objAsset;
    const std::string obj = seated::meshOBJ(L, (std::string("venue ") + v.name + ": generated by venue_probe obj from swarm/venue.hpp; do not edit").c_str());
    std::ofstream(out, std::ios::binary) << obj;
    std::printf("%s: %ld triangles (%ld of them the fence), %ld with a normal not pointing out of the solid or wound clockwise -> %s (%zu bytes)\n",
                v.name, tris, fenceTris, bad, out.string().c_str(), obj.size());
    return bad == 0 ? 0 : 1;
}


// --- forced ---
std::string mm(double modelLength) { return fmt("%.4f m", units::metres(modelLength)); }

void checkerLines(Report& r, const venue_s::Checker& c, const std::string& indent = "  - ") {
    r.line(indent + "agent-steps " + std::to_string(c.agentSteps) + "; row changes (clearway to clearway without an aisle: across a riser, seat block "
           "or the barrier) " + std::to_string(c.rowChanges) + "; entries onto another row's clearway from an aisle " + std::to_string(c.rowEntries) +
           " (seated agents' agent-steps there " + std::to_string(c.strayRowSteps) + ")" +
           "; in a solid column " + std::to_string(c.solidSteps) + "; paths through a seat block / barrier / wall (tunnelling) " +
           std::to_string(c.tunnels));
    r.line(indent + "walls: min clearance " + (c.minWallClearance < 1e8f ? mm(c.minWallClearance) : std::string("none within the probe")) +
           " (BODY_RADIUS 0.2000 m), below BODY_RADIUS - 3e-4: " + std::to_string(c.wallViolations) + " agent-steps; fence crossings " +
           std::to_string(c.fenceCrossings));
    r.line(indent + "step-up: max floor rise in a step " + mm(c.maxRise) + ", rises above MAX_STEP_UP " + std::to_string(c.risesAbove) +
           "; climbs over a vertical face (a discontinuous floor rise onto a floor above the start floor, any height) " +
           std::to_string(c.verticalClimbs) + (c.verticalClimbs ? " (max " + mm(c.maxVerticalRise) + ")" : std::string("")) +
           "; faces crossed upwards in a net descent (information) " + std::to_string(c.descentFaces) + " (max " + mm(c.maxDescentFace) + ")");
}

std::string stepsS(int st) { return st < 0 ? std::string("-") : fmt("%.1f s", venue_s::seconds(st)); }

int runForced(const bench::Args& a) {
    using namespace venue_s;
    const Venue& v = venueByName(a.get("venue", "S"));
    const SeatedLayout& L = v.layout;
    bench::createHiddenContext("venue_probe");
    const std::string throttle = bench::optOutOfPowerThrottling();
    const fs::path shaderDir = resolveAsset("shaders");
    const fs::path variant = driveVariant(shaderDir, "venue_probe_drive");
    const bool isS = v.params.exitLayout == SeatedVenueParams::ExitLayout::DoorPerWing;
    const std::string lower = v.name[0] == 'S' ? "s" : v.name[0] == 'M' ? "m" : "l";
    const fs::path out = fs::path(a.get("out", "out/results/venue_" + lower)) / ("forced_" + bench::localTimestamp("%Y%m%d_%H%M"));
    fs::create_directories(out);
    const std::string only = a.get("only", isS ? "abcdefg" : "abcdf");
    // The rows of (a)-(c) (every row, or a sample in every wing) and step counts scaled by the venue's depth
    std::vector<char> keepRow(size_t(L.rows), 1);
    std::string rowList = "every row";
    if (a.get("rows", isS ? "all" : "sample") == "sample") {
        std::fill(keepRow.begin(), keepRow.end(), 0);
        keepRow[0] = keepRow[size_t(L.rows / 2)] = keepRow[size_t(L.rows - 1)] = 1;
        for (int i = 1; i < L.gangways; ++i) {
            keepRow[size_t(L.gwRow[size_t(i)])] = 1;
            if (L.gwSeated[size_t(i)] < L.rows) keepRow[size_t(L.gwSeated[size_t(i)])] = 1;
        }
        std::mt19937 rng(unsigned(a.getInt("seed", 7)));
        for (int k = 0, extra = a.getInt("sample-rows", 5); k < extra; ++k) keepRow[size_t(std::uniform_int_distribution<int>(0, L.rows - 1)(rng))] = 1;
        rowList.clear();
        for (int k = 0; k < L.rows; ++k)
            if (keepRow[size_t(k)]) rowList += (rowList.empty() ? "rows " : ", ") + std::to_string(k);
        rowList += " (of 0 .. " + std::to_string(L.rows - 1) + ", in all 8 wings: the first, middle and last rows, each straight gangway's first row and first "
                   "seated row, and " + std::to_string(a.getInt("sample-rows", 5)) + " drawn with seed " + std::to_string(a.getInt("seed", 7)) + ")";
    }
    const RowKeep rowKeep = rowList == "every row" ? RowKeep() : RowKeep([&keepRow](int k) { return keepRow[size_t(k)] != 0; });
    const double depthScale = std::stod(a.get("step-scale", std::to_string(std::max(1.0, double(L.rows) / 17.0))));   // --step-scale overrides
    auto scaled = [&](int steps) { return int(std::lround(steps * depthScale)); };
    const scene::Select sel(v);
    Report r;
    r.line("# Venue " + std::string(v.name) + ": forced-motion validation");
    r.line("");
    r.line(header("forced") + " | " + bench::glRenderer() + " | " + bench::glDriver() + " | " + throttle);
    r.line("");
    r.line("The router is bypassed: every agent's desired direction e_goal comes from a table written before every step from the state the");
    r.line("step starts from (physics.comp TEST_DRIVE_TABLE; the CPU reference: setDriveTable), as a field of the agent's cell and plan");
    r.line("(tools/venue_s.hpp). V0 = 1.34 m/s. Checks after every step (venue_s::Checker; (e) also plausibility::runEvacuation).");
    r.line("");
    r.line("Rows of (a)-(c): " + rowList + ". Step limits x " + fmt("%.2f", depthScale) + " (the venue's rows / 17).");
    std::vector<const Checker*> all;
    InvRow inv;
    std::vector<Junction> junctions;
    Gangways gw;
    Passages ps;
    Dense dense;
    const auto t0 = bench::Clock::now();

    if (only.find('a') != std::string::npos) {
        inv = runInvRow(variant, v, 300, rowKeep);
        r.line("");
        r.line("## (a) INV-row: every seat occupied, every agent driven towards the pitch / away from it for 300 steps (52.5 s)");
        for (int k = 0; k < 2; ++k) {
            const RunResult& rr = k == 0 ? inv.runToward : inv.runAway;
            const Setup& su = k == 0 ? inv.toward : inv.away;
            r.line("");
            r.line(std::string("**") + (k == 0 ? "towards the pitch" : "away from the pitch") + "** (" + std::to_string(su.active) + " agents):");
            r.line("  - agent-steps off the agent's own clearway: " + std::to_string(rr.checks.offRowSteps) + "; front-row agents that reached the walkway: " +
                   std::to_string(rr.checks.frontRowOnWalkway));
            checkerLines(r, rr.checks);
            all.push_back(&rr.checks);
        }
    }
    if (only.find('b') != std::string::npos) {
        junctions = runJunctions(variant, v, scaled(2400), rowKeep);
        r.line("");
        r.line("## (b) Junctions: per row, one segment's agents driven along the row towards one adjacent gangway (then down it and out)");
        r.line("");
        r.line("| junction | agents | entered the gangway | first / median / last entry | not entered |");
        r.line("|---|---:|---:|---:|---:|");
        std::ofstream csv(out / "junctions.csv");
        csv << "junction,row,agents,entered,first_s,last_s\n";
        for (const Junction& j : junctions) {
            int agents = 0, entered = 0;
            std::vector<int> st;
            for (const GroupStats& g : j.perRow) {
                agents += g.agents;
                entered += g.arrived;
                st.insert(st.end(), g.steps.begin(), g.steps.end());
            }
            std::sort(st.begin(), st.end());
            r.line("| " + std::string(j.name) + " | " + std::to_string(agents) + " | " + std::to_string(entered) + " | " +
                   (st.empty() ? std::string("-") : stepsS(st.front()) + " / " + stepsS(st[st.size() / 2]) + " / " + stepsS(st.back())) + " | " +
                   std::to_string(agents - entered) + " |");
            for (int k = 0; k < L.rows; ++k) {
                const GroupStats& g = j.perRow[size_t(k)];
                csv << j.name << "," << k << "," << g.agents << "," << g.arrived << "," << venue_s::seconds(g.firstStep) << "," << venue_s::seconds(g.lastStep) << "\n";
            }
        }
        r.line("");
        r.line("Per row (agents / entered / last entry), " + std::string(junctions[0].name) + " | " + junctions[1].name + " | " + junctions[2].name + ":");
        r.line("");
        r.line("| row | dead-end -> straight | segment -> straight | segment -> corner |");
        r.line("|---:|---|---|---|");
        for (int k = 0; k < L.rows; ++k) {
            if (!keepRow[size_t(k)]) continue;
            std::string line = "| " + std::to_string(k) + " |";
            for (const Junction& j : junctions) {
                const GroupStats& g = j.perRow[size_t(k)];
                line += " " + std::to_string(g.agents) + " / " + std::to_string(g.arrived) + " / " + stepsS(g.lastStep) + " |";
            }
            r.line(line);
        }
        {   // the agents still active at the end, where they ended (diagnostics; entered_s < 0: never entered a gangway)
            std::ofstream st(out / "junction_still_active.csv");
            st << "junction,agent,entered_s,row,x_m,y_m,z_m,lat_m,dep_m,place,place_row,speed_m_s\n";
            for (const Junction& j : junctions)
                for (size_t i = 0; i < j.setup.boids.size(); ++i) {
                    if (j.setup.group[i] < 0 || j.run.finalState[i].position.w == 0.0f) continue;   // every agent still active at the end
                    const GpuBoid& b = j.run.finalState[i];
                    const Where w = where(L, b.position);
                    const glm::vec2 f = seated::fold(glm::vec2(b.position));
                    st << j.name << "," << i << "," << venue_s::seconds(j.run.checks.enteredGangway[i]) << "," << j.setup.rows[i] << "," << m(b.position.x) << "," << m(b.position.y) << "," << m(b.position.z) << ","
                       << m(f.x) << "," << m(f.y) << "," << placeName(w.place) << "," << w.row << "," << units::metresPerSecond(glm::length(glm::vec2(b.velocity))) << "\n";
                }
        }
        for (const Junction& j : junctions) {
            r.line("");
            r.line(std::string("Checks, ") + j.name + " (" + std::to_string(j.run.steps) + " steps, everyone out at " + stepsS(j.run.evacStep) + "):");
            checkerLines(r, j.run.checks);
            all.push_back(&j.run.checks);
        }
    }
    if (only.find('c') != std::string::npos) {
        gw = runGangways(variant, v, scaled(1200), rowKeep);
        r.line("");
        r.line("## (c) Gangways: one agent per (sampled) row band on every gangway (a straight gangway from its first row) driven down to the walkway / up to the rear concourse");
        r.line("");
        r.line("| gangway | down: arrived / agents, last | up: arrived / agents, last |");
        r.line("|---|---|---|");
        std::ofstream csv(out / "gangways.csv");
        csv << "gangway,direction,agents,arrived,last_s\n";
        for (int g = 0; g < gangwayGroups(L); ++g) {
            const int sg = 8 * L.gangways;   // groups (q * 2 + wing) * gangways + i, then the 4 corner gangways
            const std::string name = g < sg ? "quadrant " + std::to_string(g / L.gangways / 2) + " wing " + std::to_string(g / L.gangways % 2) + " straight" +
                                                  (L.gangways > 1 ? " " + std::to_string(g % L.gangways) : std::string())
                                            : "quadrant " + std::to_string(g - sg) + " corner";
            const GroupStats& d = gw.statsDown[size_t(g)];
            const GroupStats& u = gw.statsUp[size_t(g)];
            r.line("| " + name + " | " + std::to_string(d.arrived) + " / " + std::to_string(d.agents) + ", " + stepsS(d.lastStep) + " | " +
                   std::to_string(u.arrived) + " / " + std::to_string(u.agents) + ", " + stepsS(u.lastStep) + " |");
            csv << name << ",down," << d.agents << "," << d.arrived << "," << venue_s::seconds(d.lastStep) << "\n";
            csv << name << ",up," << u.agents << "," << u.arrived << "," << venue_s::seconds(u.lastStep) << "\n";
        }
        r.line("");
        r.line("Checks, down:");
        checkerLines(r, gw.runDown.checks);
        r.line("Checks, up:");
        checkerLines(r, gw.runUp.checks);
        all.push_back(&gw.runDown.checks);
        all.push_back(&gw.runUp.checks);
    }
    if (only.find('d') != std::string::npos) {
        ps = runPassages(variant, v, scaled(1500));
        r.line("");
        r.line("## (d) Passages and exits");
        r.line("");
        r.line("| passage | arrived / agents | last arrival |");
        r.line("|---|---:|---:|");
        for (int g = 0; g < 8; ++g) {
            const GroupStats& t = ps.statsRings[size_t(g)];
            r.line("| " + std::string(g < 4 ? "walkway ring, quadrant " : "rear concourse ring, quadrant ") + std::to_string(g % 4) + " | " +
                   std::to_string(t.arrived) + " / " + std::to_string(t.agents) + " | " + stepsS(t.lastStep) + " |");
        }
        static const char* avenues[4] = { "+y", "-x", "-y", "+x" };
        for (int g = 8; g < 12 + 4 * L.doorsPerQuadrant(); ++g) {
            const GroupStats& t = ps.statsExits[size_t(g)];
            const std::string name = g < 12 ? std::string("avenue ") + avenues[g - 8] + " out through its exit"
                                            : "concourse exit: " + seated::exitName(L, 4 + g - 12);
            r.line("| " + name + " | " + std::to_string(t.arrived) + " / " + std::to_string(t.agents) + " | " + stepsS(t.lastStep) + " |");
        }
        r.line("");
        r.line("Checks, rings:");
        checkerLines(r, ps.runRings.checks);
        r.line("Checks, exits:");
        checkerLines(r, ps.runExits.checks);
        all.push_back(&ps.runRings.checks);
        all.push_back(&ps.runExits.checks);
    }
    if (only.find('e') != std::string::npos) {
        dense = runDense(variant, shaderDir, v, 6000, golden::GOLDEN_STEPS);
        r.line("");
        r.line("## (e) Dense: every seat occupied (" + std::to_string(dense.setup.active) + "), along the row to the nearer gangway, down it, along the walkway, out through the nearer avenue");
        r.line("");
        r.line("plausibility::runEvacuation, analytic venue (no exemption: every overlap case held to the crowd limits):");
        r.line("");
        r.line("```");
        r.line("evacuated at step " + std::to_string(dense.plaus.evacStep) + " (" + stepsS(dense.plaus.evacStep) + "); t50 " + stepsS(dense.plaus.s50) + ", t90 " + stepsS(dense.plaus.s90));
        r.line(fmt("all overlaps: %.0f pair-steps", double(dense.plaus.allStats.n)) + fmt(", p99 %.4f", dense.plaus.allStats.p99) + fmt(", max %.4f of BODY_DIAM", dense.plaus.allStats.max));
        r.line(fmt("crowd cases: %.0f pair-steps", double(dense.plaus.crowdStats.n)) + fmt(", p99 %.4f", dense.plaus.crowdStats.p99) + fmt(", max %.4f", dense.plaus.crowdStats.max));
        r.line(fmt("venue-geometry cases (fall, step-down, ramp): %.0f pair-steps", double(dense.plaus.venueStats.n)) + fmt(", p99 %.4f", dense.plaus.venueStats.p99) +
               fmt(", max %.4f", dense.plaus.venueStats.max));
        r.line(std::string("overlap limits (p99 <= 0.05, max <= 0.20, ALL cases): ") + (dense.plaus.overlapOk() ? "PASS" : "FAIL"));
        r.line(fmt("neighbour grid: max displacement %.5f", dense.plaus.maxDisplacement) + fmt(" (bound %.5f)", plausibility::displacementBound()) +
               ", misses " + std::to_string(dense.plaus.gridMisses));
        r.line("floors: centre in solid " + std::to_string(dense.plaus.centreInSolid) + ", below floor + R " + std::to_string(dense.plaus.floorViolations) +
               "; airborne runs " + std::to_string(dense.plaus.airborneRuns) + ", longest " + std::to_string(dense.plaus.longestAirborne) +
               "; step-downs " + std::to_string(dense.plaus.stepDowns));
        r.line("fence: crossings " + std::to_string(dense.plaus.fenceCrossings) + ", band " + std::to_string(dense.plaus.fenceBand) + "; walls: violations " +
               std::to_string(dense.plaus.wallViolations) + fmt(", min clearance %.6f", dense.plaus.minWallClearance < 1e8f ? dense.plaus.minWallClearance : -1.0f));
        r.line(fmt("speed: max %.6f", dense.plaus.maxSpeed) + ", above V_MAX " + std::to_string(dense.plaus.speedViolations) +
               fmt("; density: peak %.2f p/m^2 over fully walkable cells", dense.plaus.peakFull) + fmt(" (ceiling %.2f)", plausibility::DENSITY_CEILING_P_M2));
        r.line(std::string("all plausibility checks: ") + (dense.plaus.allOk() ? "PASS" : "FAIL"));
        r.line("```");
        r.line("");
        r.line("Overlap depth by population and zone (pair-steps, share, p50 / p99 / max, above 2 / 5 / 10 / 20% of BODY_DIAM):");
        r.line("");
        r.line("```");
        auto row = [&](const std::string& what, const plausibility::DepthStats& st) {
            char b[256];
            std::snprintf(b, sizeof b, "%-44s %7zu  p50 %.4f  p99 %.4f  max %.4f  > 2%% %5ld  > 5%% %5ld  > 10%% %4ld  > 20%% %4ld", what.c_str(), st.n, st.p50, st.p99,
                          st.max, st.above2, st.above5, st.above10, st.above20);
            r.line(b);
        };
        row("all", dense.plaus.allStats);
        for (int c = 0; c < plausibility::CASE_COUNT; ++c)
            for (int z = 0; z < plausibility::PZ_COUNT; ++z)
                if (!dense.plaus.caseDepths[c][z].empty()) row(std::string(plausibility::caseName(c)) + ", " + plausibility::pairZoneName(z), dense.plaus.overlapCase(c, z));
        r.line("```");
        r.line("");
        r.line("Checks (venue_s::Checker):");
        checkerLines(r, dense.checks);
        all.push_back(&dense.checks);
    }
    if (only.find('f') != std::string::npos && !all.empty()) {
        long rises = 0, climbs = 0, dips = 0, tunnels = 0, steps = 0;
        float maxRise = 0.0f, maxV = 0.0f, maxD = 0.0f;
        for (const Checker* c : all) {
            rises += c->risesAbove; climbs += c->verticalClimbs; dips += c->descentFaces; tunnels += c->tunnels; steps += c->agentSteps;
            maxRise = std::max(maxRise, c->maxRise); maxV = std::max(maxV, c->maxVerticalRise); maxD = std::max(maxD, c->maxDescentFace);
        }
        r.line("");
        r.line("## (f) The step-up rules over every scenario above (" + std::to_string(steps) + " agent-steps)");
        r.line("");
        r.line("- floor rises above MAX_STEP_UP (0.30 m) in one step: " + std::to_string(rises) + " (max rise " + mm(maxRise) + ")");
        r.line("- climbs over a vertical face (a discontinuous floor rise, any height, along a step's path onto a floor above the start-of-step "
               "floor; checked every 2 mm): " + std::to_string(climbs) + (climbs ? " (max " + mm(maxV) + ")" : std::string("")));
        r.line("- information: faces crossed upwards within a step that ends at or below its start floor (the path dipped onto the incline "
               "first; the step-up rule never blocks level or downward moves): " + std::to_string(dips) + " (max " + mm(maxD) + ")");
        r.line("- paths through a seat block, the barrier or a wall: " + std::to_string(tunnels));
    }
    if (only.find('g') != std::string::npos) {
        r.line("");
        r.line("## (g) CPU/GPU equivalence on venue S (the dense scenario's drive field) and the golden hashes");
        r.line("");
        const Setup su = denseSetup(L);
        const int n = int(su.boids.size());
        // the GPU state after 200 steps
        std::vector<GpuBoid> mid;
        {
            GpuEngine e(variant, n, v);
            mid = run(e, L, su.boids, su.plans, su.rows, 200, false, false).finalState;
        }
        const OneStep o = oneStep(variant, v, mid, su.plans);
        long active = 0;
        for (const GpuBoid& b : mid) active += b.position.w != 0.0f;
        for (int m = 0; m < 2; ++m) {
            bool gridSame = o.cpuCells[m].size() == o.gpuCells.size() &&
                            std::memcmp(o.cpuCells[m].data(), o.gpuCells.data(), o.gpuCells.size() * sizeof(GpuCellData)) == 0;
            long seqDiff = 0, pairDiff = 0, out = 0;
            float maxD = 0.0f;
            for (size_t i = 0; i < o.gpuGrid.size(); ++i) {
                seqDiff += o.cpuGrid[m][i].gridID != o.gpuGrid[i].gridID;
                pairDiff += o.cpuGrid[m][i].boidID != o.gpuGrid[i].boidID;
            }
            for (size_t i = 0; i < mid.size(); ++i) {
                if (mid[i].position.w == 0.0f) continue;
                const float d = glm::length(glm::vec3(o.cpu[m][i].position) - glm::vec3(o.gpu[i].position));
                maxD = std::max(maxD, d);
                out += d > 2e-4f;
            }
            r.line(std::string("- one step from the GPU state after 200 steps (") + std::to_string(active) + " active), CPU " + (m == 0 ? "counting" : "bitonic") +
                   ": cell table " + (gridSame ? "identical" : "DIFFERS") + ", gridID sequence differs at " + std::to_string(seqDiff) + " slots, (gridID, boidID) pairs at " +
                   std::to_string(pairDiff) + (m == 0 ? " (counting: boidID order within a cell)" : "") + "; |dpos| > 2e-4 for " + std::to_string(out) + " agents (" +
                   fmt("%.3f%%", 100.0 * double(out) / double(std::max(active, 1L))) + ", limit < 0.5%), max " + fmt("%.2e", maxD));
        }
        // thread invariance and determinism (100 / 300 steps), golden hashes after GOLDEN_STEPS
        auto cpuRun = [&](int threads, CpuCrowdSim::SortMode mode, int steps, bool stopWhenEmpty = false) {
            CpuEngine c(v, threads, mode);
            return run(c, L, su.boids, su.plans, su.rows, steps, stopWhenEmpty, false);
        };
        const RunResult t1 = cpuRun(1, CpuCrowdSim::SortMode::Counting, 100), tmax = cpuRun(0, CpuCrowdSim::SortMode::Counting, 100);
        r.line(std::string("- CPU thread invariance (counting, 1 thread vs ") + std::to_string(CpuCrowdSim::maxThreads()) + ", 100 steps): trajectory hashes " +
               (t1.trajectoryHash == tmax.trajectoryHash ? "identical" : "DIFFER"));
        const auto gpuGolden = [&]() {
            GpuEngine e(variant, n, v);
            return run(e, L, su.boids, su.plans, su.rows, golden::GOLDEN_STEPS, false, false);
        };
        const RunResult g1 = gpuGolden(), g2 = gpuGolden();
        const RunResult c1 = cpuRun(0, CpuCrowdSim::SortMode::Counting, golden::GOLDEN_STEPS), c2 = cpuRun(0, CpuCrowdSim::SortMode::Counting, golden::GOLDEN_STEPS);
        const RunResult cb = cpuRun(0, CpuCrowdSim::SortMode::GpuBitonic, golden::GOLDEN_STEPS);
        r.line(std::string("- determinism over ") + std::to_string(golden::GOLDEN_STEPS) + " steps: two GPU runs " + (g1.trajectoryHash == g2.trajectoryHash ? "identical" : "DIFFER") +
               ", two CPU runs " + (c1.trajectoryHash == c2.trajectoryHash ? "identical" : "DIFFER") + " (trajectory hashes)");
        long act[3] = {};
        for (const GpuBoid& b : g1.finalState) act[0] += b.position.w != 0.0f;
        for (const GpuBoid& b : c1.finalState) act[1] += b.position.w != 0.0f;
        for (const GpuBoid& b : cb.finalState) act[2] += b.position.w != 0.0f;
        char hb[256];
        std::snprintf(hb, sizeof hb, "- golden (FNV-1a 64 of the state after %d steps of the dense scenario from the full seat spawn): GPU %016llx, CPU counting %016llx, CPU bitonic %016llx (active %ld / %ld / %ld)",
                      golden::GOLDEN_STEPS, (unsigned long long)golden::stateHash(g1.finalState), (unsigned long long)golden::stateHash(c1.finalState),
                      (unsigned long long)golden::stateHash(cb.finalState), act[0], act[1], act[2]);
        r.line(hb);
        // the full dense scenario: CPU (counting) against the GPU
        int gpuEvac = dense.plaus.evacStep;
        if (gpuEvac <= 0) {
            GpuEngine e(variant, n, v);
            gpuEvac = run(e, L, su.boids, su.plans, su.rows, 6000, true, false).evacStep;
        }
        const auto tc = bench::Clock::now();
        const RunResult cfull = cpuRun(0, CpuCrowdSim::SortMode::Counting, 6000, true);
        r.line("- the dense scenario to the last agent out: GPU step " + std::to_string(gpuEvac) + ", CPU counting step " + std::to_string(cfull.evacStep) +
               fmt(" (%+.2f%%; limit +-5%%)", 100.0 * (double(cfull.evacStep) - double(gpuEvac)) / double(std::max(gpuEvac, 1))) +
               fmt("; CPU run %.0f s", bench::msSince(tc) / 1000.0));
    }
    r.line("");
    r.line(fmt("Total time %.0f s.", bench::msSince(t0) / 1000.0));
    r.write(out / "summary.md");
    return 0;
}

} // namespace

// --- gangways: each gangway's floor area (venue_s::gangwayAreasM2), CSV on stdout ---
int runGangways(const bench::Args& a) {
    const Venue& v = venueByName(a.get("venue", "S"));
    const std::vector<double> areas = venue_s::gangwayAreasM2(v.layout, v.domainMin, v.domainSpan);
    std::printf("gangway,area_m2\n");
    for (int g = 0; g < int(areas.size()); ++g) std::printf("%s,%.4f\n", seated::gangwayName(v.layout, g).c_str(), areas[size_t(g)]);
    return 0;
}

// --- catchments ---
// Each row segment of every wing (quadrant, wing, row, segment): its seats and the gangways at its two ends, found geometrically: from the
// segment's end seat along the clearway's centre line outward (0.05 m steps, at most 3 m) to the first gangway cell (seated::gangwayAt, the
// metrics' ids) or a wall (none: a dead end) -> <out>/catchments.csv. The bottleneck analysis' attainable gangway balance reads it.
int runCatchments(const bench::Args& a) {
    const Venue& v = venueByName(a.get("venue", "S"));
    const SeatedLayout& L = v.layout;
    const std::vector<seated::Seat> seats = seated::seats(L);
    struct Group { int n = 0; float lo = 1e9f, hi = -1e9f, dep = 0.0f; };
    std::map<std::array<int, 4>, Group> groups;
    for (const seated::Seat& s : seats) {
        Group& g = groups[{ s.quadrant, s.wing, s.row, s.segment }];
        ++g.n;
        g.lo = std::min(g.lo, s.lat);
        g.hi = std::max(g.hi, s.lat);
        g.dep = seated::fold(glm::vec2(s.pos)).y;
    }
    const float stepU = float(units::modelLength(0.05)), reach = float(units::modelLength(3.0));
    auto endGangway = [&](int q, int wing, float lat, float dep, float dir) {
        for (float d = 0.5f * L.seatWidth; d <= reach; d += stepU) {
            const float l = lat + dir * d;
            if (l < 0.0f || l > dep) return -1;
            const glm::vec2 p = venue_s::unfoldPoint(glm::vec2(l, dep), q, wing);
            const int g = seated::gangwayAt(L, p);
            if (g >= 0) return g;
            const int kind = seated::cellAt(L, p);
            if (kind == seated::WALL || kind == seated::SIDE) return -1;
        }
        return -1;
    };
    std::string vn = v.name;
    std::transform(vn.begin(), vn.end(), vn.begin(), [](unsigned char ch) { return char(std::tolower(ch)); });
    const fs::path out = fs::path(a.get("out", "out/results/venue_" + vn)) / "catchments.csv";
    fs::create_directories(out.parent_path());
    std::ofstream f(out);
    f << "quadrant,wing,row,segment,seats,lat_lo_m,lat_hi_m,gangway_lo,gangway_hi,name_lo,name_hi\n";
    long dead = 0, both = 0;
    for (const auto& [k, g] : groups) {
        const int lo = endGangway(k[0], k[1], g.lo, g.dep, -1.0f), hi = endGangway(k[0], k[1], g.hi, g.dep, +1.0f);
        (lo >= 0 && hi >= 0 ? both : dead) += g.n;
        f << k[0] << "," << k[1] << "," << k[2] << "," << k[3] << "," << g.n << "," << fmt("%.3f", m(g.lo)) << "," << fmt("%.3f", m(g.hi)) << ","
          << lo << "," << hi << "," << (lo >= 0 ? seated::gangwayName(L, lo) : std::string("-")) << "," << (hi >= 0 ? seated::gangwayName(L, hi) : std::string("-")) << "\n";
    }
    std::printf("venue %s: %zu row segments, %zu seats: %ld with a gangway at both ends, %ld at one end only -> %s\n", v.name, groups.size(), seats.size(),
                both, dead, out.string().c_str());
    return 0;
}

int main(int argc, char** argv) {
    try {
        if (argc < 2) {
            std::printf("usage: venue_probe layout|exact|timing|forced|obj [--venue S] [--out DIR] (see the file header)\n");
            return 2;
        }
        const std::string cmd = argv[1];
        const bench::Args a(argc, argv, 2);
        if (cmd == "layout") return runLayout(a);
        if (cmd == "gangways") return runGangways(a);
        if (cmd == "capacity") return runCapacity(a);
        if (cmd == "overcrowd") return runOvercrowd(a);
        if (cmd == "catchments") return runCatchments(a);
        if (cmd == "golden") return runGolden(a);
        if (cmd == "jtrace") {   // diagnostics: junction case (b3) on the GPU to --steps, then the agents near (--x, --y) m; --alone: the
                                 // agent --agent alone from that state (the others parked) for --more steps, on the GPU and the CPU reference
            using namespace venue_s;
            const Venue& v = venueByName(a.get("venue", "L"));
            const SeatedLayout& L = v.layout;
            bench::createHiddenContext("venue_probe");
            const scene::Select sel(v);
            const fs::path variant = driveVariant(resolveAsset("shaders"), "venue_probe_jtrace");
            std::vector<char> keepRow(size_t(L.rows), 0);
            for (const std::string& t : bench::parseList(a.get("rows", "0,7,17,20,21,30,37,39,41,47,56,59,74,76,78,94"))) keepRow[size_t(std::stoi(t))] = 1;
            const int caseIdx = a.getInt("case", 2);
            const float sign = caseIdx == 1 ? -1.0f : 1.0f;
            Setup su = seatSetup(L, [&](const seated::Seat& st) { return (caseIdx == 0 ? st.segment == 0 : st.segment >= 1) && keepRow[size_t(st.row)]; },
                                 [&](const seated::Seat& seat) { Plan pl; pl.mode = M_EGRESS_DOWN; pl.rowSign = caseIdx == 0 ? 1.0f : sign; pl.row = seat.row; return pl; },
                                 [](const seated::Seat& st) { return st.row; });
            const int steps = a.getInt("steps", 13000);
            GpuEngine e(variant, int(su.boids.size()), v);
            RunResult rr = run(e, L, su.boids, su.plans, su.rows, steps, true, false);
            const glm::vec2 c(float(units::modelLength(std::stod(a.get("x", "34.57")))), float(units::modelLength(std::stod(a.get("y", "34.44")))));
            const float rad = float(units::modelLength(std::stod(a.get("r", "1.5"))));
            std::vector<glm::vec2> table;
            driveTable(L, su.plans, rr.finalState, table);
            std::printf("after %d steps (%s): agents within %.1f m of (%.2f, %.2f) m\n", rr.steps, rr.evacStep > 0 ? "all out" : "not all out", units::metres(rad),
                        units::metres(c.x), units::metres(c.y));
            for (size_t i = 0; i < rr.finalState.size(); ++i) {
                const GpuBoid& b = rr.finalState[i];
                if (b.position.w == 0.0f || glm::length(glm::vec2(b.position) - c) > rad) continue;
                const glm::vec2 f = seated::fold(glm::vec2(b.position));
                const Where w = where(L, b.position);
                std::printf("  agent %5zu x %.3f y %.3f z %.3f (lat %.3f dep %.3f, %s) v %.3f %.3f %.3f m/s drive %.3f %.3f floor %.3f\n", i, m(b.position.x),
                            m(b.position.y), m(b.position.z), m(f.x), m(f.y), placeName(w.place), units::metresPerSecond(b.velocity.x),
                            units::metresPerSecond(b.velocity.y), units::metresPerSecond(b.velocity.z), table[i].x, table[i].y, m(seated::floorHeight(L, glm::vec2(b.position))));
            }
            const int agent = a.getInt("agent", -1);
            if (agent >= 0) {
                std::vector<GpuBoid> alone(rr.finalState.size(), parked());
                alone[size_t(agent)] = rr.finalState[size_t(agent)];
                const int more = a.getInt("more", 20);
                for (int eng = 0; eng < 2; ++eng) {
                    std::vector<GpuBoid> st = a.has("alone") ? alone : rr.finalState;
                    std::unique_ptr<GpuEngine> ge;
                    std::unique_ptr<CpuEngine> ce;
                    if (eng == 0) { ge = std::make_unique<GpuEngine>(variant, int(st.size()), v); ge->upload(st); }
                    else { ce = std::make_unique<CpuEngine>(v, 0, CpuCrowdSim::SortMode::Counting); ce->upload(st); }
                    for (int k = 0; k < more; ++k) {
                        driveTable(L, su.plans, st, table);
                        if (eng == 0) { ge->setDrive(table); ge->step(); st = ge->state(); }
                        else { ce->setDrive(table); ce->step(); st = ce->state(); }
                        const GpuBoid& b = st[size_t(agent)];
                        const glm::vec2 f = seated::fold(glm::vec2(b.position));
                        std::printf("  %s step +%d: agent %d lat %.4f dep %.4f z %.4f v %.4f %.4f m/s drive %.3f %.3f\n", eng == 0 ? "GPU" : "CPU", k + 1, agent, m(f.x), m(f.y),
                                    m(b.position.z), units::metresPerSecond(b.velocity.x), units::metresPerSecond(b.velocity.y), table[size_t(agent)].x, table[size_t(agent)].y);
                    }
                }
            }
            fs::remove_all(variant);
            return 0;
        }
        if (cmd == "equiv") return runEquiv(a);
        if (cmd == "exact") return runExact(a);
        if (cmd == "timing") return runTiming(a);
        if (cmd == "obj") return runObj(a);
        if (cmd == "forced") return runForced(a);
        if (cmd == "gdense") {   // diagnostics: the dense scenario on the GPU, plausibility's floor checks per agent-step
            const Venue& v = venueByName(a.get("venue", "S"));
            const SeatedLayout& L = v.layout;
            const scene::Select sel(v);
            const venue_s::Setup su = venue_s::denseSetup(L);
            const bool onCpu = a.has("cpu");   // the CPU reference instead (its contact flags in the neighbourhood dump)
            std::unique_ptr<venue_s::GpuEngine> ge;
            std::unique_ptr<venue_s::CpuEngine> ce;
            if (onCpu) ce = std::make_unique<venue_s::CpuEngine>(v, 0, CpuCrowdSim::SortMode::Counting);
            else {
                bench::createHiddenContext("venue_probe");
                ge = std::make_unique<venue_s::GpuEngine>(venue_s::driveVariant(resolveAsset("shaders"), "venue_probe_drive"), int(su.boids.size()), v);
            }
            if (onCpu) ce->upload(su.boids); else ge->upload(su.boids);
            std::vector<GpuBoid> prev = su.boids;
            std::vector<glm::vec2> table;
            long inSolid = 0, floorBad = 0, air = 0;
            int shown = 0, shownPairs = 0;
            const int steps = a.getInt("steps", 2400), show = a.getInt("show", 30);
            for (int s = 1; s <= steps; ++s) {
                venue_s::driveTable(L, su.plans, prev, table);
                if (onCpu) { ce->setDrive(table); ce->step(); } else { ge->setDrive(table); ge->step(); }
                const std::vector<GpuBoid> cur = onCpu ? ce->state() : ge->state();
                if (a.has("near") && s == a.getInt("at", 1)) {   // the neighbourhood (1 m) of one agent at one step
                    const size_t ni = size_t(a.getInt("near", 0));
                    const glm::vec2 c0(cur[ni].position);
                    {   // the edge margin's queries at its final position
                        const glm::vec3 c(cur[ni].position);
                        const float feet = c.z - BODY_RADIUS, fl = seated::floorHeight(L, glm::vec2(c));
                        const glm::vec3 w1 = seated::wall(L, glm::vec3(glm::vec2(c), feet + STEP_UP_TOL), L.faceMargin);
                        const glm::vec3 w2 = seated::wall(L, glm::vec3(glm::vec2(c), fl + STEP_UP_TOL), L.faceMargin);
                        std::printf("  near %zu: xy (%.9g, %.9g) feet %.9g floor %.9g | wall(feet) (%.4f %.4f) %.3e | wall(floor) (%.4f %.4f) %.3e | margin %.3e\n",
                                    ni, c.x, c.y, feet, fl, w1.x, w1.y, w1.z, w2.x, w2.y, w2.z, L.faceMargin);
                    }
                    for (size_t j = 0; j < cur.size(); ++j) {
                        if (cur[j].position.w == 0.0f || glm::length(glm::vec2(cur[j].position) - c0) > float(units::modelLength(1.0))) continue;
                        const glm::vec2 fj = seated::fold(glm::vec2(cur[j].position)), fp = seated::fold(glm::vec2(prev[j].position));
                        const float d = glm::length(glm::vec2(cur[j].position) - c0);
                        std::printf("  near %zu: agent %zu at (%.4f, %.4f) z %.4f <- (%.4f, %.4f) | d %.3f m | v %.3f m/s (%.3f %.3f) | drive (%.2f %.2f) | contacts 0x%02x | kind %d\n",
                                    ni, j, units::metres(fj.x), units::metres(fj.y), units::metres(cur[j].position.z), units::metres(fp.x), units::metres(fp.y),
                                    units::metres(d), units::metresPerSecond(glm::length(glm::vec2(cur[j].velocity))), cur[j].velocity.x, cur[j].velocity.y,
                                    table[j].x, table[j].y, onCpu ? unsigned(ce->sim.contacts()[j]) : 0u, seated::cellAt(L, glm::vec2(cur[j].position)));
                    }
                }
                for (size_t i = 0; i < cur.size(); ++i) {
                    if (cur[i].position.w == 0.0f) continue;
                    const glm::vec3 c(cur[i].position), p0(prev[i].position);
                    const bool sol = scene::sdf(c) < 0.0f, fb = scene::sdf(c - glm::vec3(0.0f, 0.0f, BODY_RADIUS - plausibility::FLOOR_TOL)) <= 0.0f;
                    const bool ai = scene::sdf(c - glm::vec3(0.0f, 0.0f, BODY_RADIUS + plausibility::FLOOR_TOL)) > 0.0f;
                    inSolid += sol; floorBad += fb; air += ai;
                    if ((sol || fb || (ai && a.has("air"))) && shown < show && !a.has("pairs")) {
                        ++shown;
                        const glm::vec2 f = seated::fold(glm::vec2(c)), f0 = seated::fold(glm::vec2(p0));
                        int row = -1, band = 0;
                        const int kind = seated::cellAt(L, glm::vec2(c), &row, &band);
                        std::printf("  step %d agent %zu: %s%s%s folded (%.6f, %.6f) m z %.5f m <- (%.6f, %.6f) z %.5f | cell kind %d band %d | floor %.5f m, z - floor - R %+.6f m | "
                                    "sdf %.3e m | lat - gHi %+.3e, lat - gLo %+.3e units | v (%.3f %.3f %.3f) drive (%.2f %.2f)\n",
                                    s, i, sol ? "IN-SOLID " : "", fb ? "LOW " : "", ai ? "AIR " : "", units::metres(f.x), units::metres(f.y), units::metres(c.z),
                                    units::metres(f0.x), units::metres(f0.y), units::metres(p0.z), kind, band, units::metres(seated::floorHeight(L, glm::vec2(c))),
                                    units::metres(c.z - seated::floorHeight(L, glm::vec2(c)) - BODY_RADIUS), units::metres(scene::sdf(c)), f.x - L.gangwayHi,
                                    f.x - L.gangwayLo, cur[i].velocity.x, cur[i].velocity.y, cur[i].velocity.z, table[i].x, table[i].y);
                    }
                }
                if (a.has("pairs")) {   // overlapping pairs deeper than --pairs (fraction of BODY_DIAM): where
                    const float thr = std::stof(a.get("pairs", "0.2"));
                    std::map<std::pair<int, int>, std::vector<int>> grid;
                    for (size_t i = 0; i < cur.size(); ++i)
                        if (cur[i].position.w != 0.0f)
                            grid[{ int(std::floor(cur[i].position.x / BODY_DIAM)), int(std::floor(cur[i].position.y / BODY_DIAM)) }].push_back(int(i));
                    for (const auto& kv : grid)
                        for (int dx = -1; dx <= 1; ++dx)
                            for (int dy = -1; dy <= 1; ++dy) {
                                auto it = grid.find({ kv.first.first + dx, kv.first.second + dy });
                                if (it == grid.end()) continue;
                                for (int i : kv.second)
                                    for (int j : it->second) {
                                        if (j <= i) continue;
                                        const glm::vec3 pi(cur[size_t(i)].position), pj(cur[size_t(j)].position);
                                        if (std::abs(pi.z - pj.z) >= BODY_DIAM) continue;
                                        const float d = glm::length(glm::vec2(pi) - glm::vec2(pj));
                                        const float depth = (BODY_DIAM - d) / BODY_DIAM;
                                        if (depth <= thr || shownPairs >= show) continue;
                                        ++shownPairs;
                                        const glm::vec2 fi = seated::fold(glm::vec2(pi)), fj = seated::fold(glm::vec2(pj));
                                        std::printf("  step %d pair %d-%d depth %.3f: i (%.3f, %.3f) z %.3f floor %.3f kind %d | j (%.3f, %.3f) z %.3f floor %.3f kind %d | "
                                                    "speeds %.3f %.3f\n", s, i, j, depth, units::metres(fi.x), units::metres(fi.y), units::metres(pi.z),
                                                    units::metres(seated::floorHeight(L, glm::vec2(pi))), seated::cellAt(L, glm::vec2(pi)), units::metres(fj.x),
                                                    units::metres(fj.y), units::metres(pj.z), units::metres(seated::floorHeight(L, glm::vec2(pj))),
                                                    seated::cellAt(L, glm::vec2(pj)), units::metresPerSecond(glm::length(glm::vec2(cur[size_t(i)].velocity))),
                                                    units::metresPerSecond(glm::length(glm::vec2(cur[size_t(j)].velocity))));
                                    }
                            }
                }
                prev = cur;
            }
            long active = 0;
            for (const GpuBoid& b : prev) active += b.position.w != 0.0f;
            std::printf("gdense: %d steps, in solid %ld, low %ld, airborne %ld agent-steps; active at the end %ld\n", steps, inSolid, floorBad, air, active);
            return 0;
        }
        if (cmd == "debug") {   // diagnostics: junction b1 (or INV-row away) on the CPU reference, the first offending agents traced
            const Venue& v = venueByName(a.get("venue", "S"));
            const SeatedLayout& L = v.layout;
            const scene::Select sel(v);
            const std::string which = a.get("case", "b1");
            venue_s::Setup su;
            if (which == "dense") su = venue_s::denseSetup(L);
            else if (which == "cdown" || which == "cup") su = venue_s::gangwaySetup(L, which == "cdown" ? -1.0f : 1.0f);
            else if (which == "rings" || which == "exits") su = venue_s::passageSetup(L, which == "rings");
            else if (which == "away")
                su = venue_s::seatSetup(L, nullptr, [&](const seated::Seat& s) { venue_s::Plan p; p.mode = venue_s::M_CONST; p.dir = venue_s::depthDir(s, 1.0f); return p; },
                                        [](const seated::Seat& s) { return s.row; });
            else {   // b1: dead-end -> straight; b2: segment -> straight; b3: segment -> corner (one wing, or --all)
                const int seg = which == "b1" ? 0 : 1;
                const float sign = which == "b2" ? -1.0f : 1.0f;
                const bool all = a.has("all");
                su = venue_s::seatSetup(L, [&](const seated::Seat& s) { return s.segment == seg && (all || (s.quadrant == 0 && s.wing == 0)); },
                                        [&](const seated::Seat& st) { venue_s::Plan p; p.mode = venue_s::M_EGRESS_DOWN; p.rowSign = sign; p.row = st.row; return p; },
                                        [](const seated::Seat& s) { return s.row; });
            }
            venue_s::CpuEngine e(v, 0, CpuCrowdSim::SortMode::Counting);
            e.upload(su.boids);
            std::vector<GpuBoid> prev = su.boids;
            std::vector<glm::vec2> table;
            int shown = 0;
            const int steps = a.getInt("steps", 300);
            for (int s = 1; s <= steps; ++s) {
                venue_s::driveTable(L, su.plans, prev, table);
                e.setDrive(table);
                e.step();
                const std::vector<GpuBoid> cur = e.state();
                if (a.has("trace")) {   // one agent, every step from --from
                    const size_t ti = size_t(a.getInt("trace", 0));
                    if (s >= a.getInt("from", 1) && s <= a.getInt("to", 1 << 30)) {
                        const glm::vec3 c0(prev[ti].position), c1(cur[ti].position);
                        const glm::vec2 f0 = seated::fold(glm::vec2(c0)), f1 = seated::fold(glm::vec2(c1));
                        const glm::vec3 wq = seated::wall(L, c1, 0.02f);
                        std::printf("  trace step %d: (%.5f, %.5f, z %.5f) -> (%.5f, %.5f, z %.5f) m | v (%.3f %.3f) | drive (%.2f %.2f) | contacts 0x%02x | wall %.4f m (%.2f %.2f) | floors %.4f -> %.4f m\n",
                                    s, units::metres(f0.x), units::metres(f0.y), units::metres(c0.z), units::metres(f1.x), units::metres(f1.y), units::metres(c1.z),
                                    cur[ti].velocity.x, cur[ti].velocity.y, table[ti].x, table[ti].y, unsigned(e.sim.contacts()[ti]), units::metres(wq.z), wq.x, wq.y,
                                    units::metres(seated::floorHeight(L, glm::vec2(c0))), units::metres(seated::floorHeight(L, glm::vec2(c1))));
                        if (a.has("pathdump")) {   // the checker's path samples whose floor jumps
                            const glm::vec2 pa(c0), pb(c1);
                            float hPrev = seated::floorHeight(L, pa);
                            const int ns = std::max(1, int(std::ceil(glm::length(pb - pa) / (0.002f * float(units::modelLength(1.0))))));
                            for (int k = 1; k <= ns; ++k) {
                                const glm::vec2 q = k == ns ? pb : pa + (pb - pa) * (float(k) / float(ns));
                                const float h = seated::floorHeight(L, q);
                                if (std::abs(h - hPrev) > 1e-3f)
                                    std::printf("    sample %d: (%.9g, %.9g) lat %.9g (gHi %.9g) cell %d floor %.5f -> %.5f m\n", k, q.x, q.y, seated::fold(q).x,
                                                L.gangwayHi, seated::cellAt(L, q), units::metres(hPrev), units::metres(h));
                                hPrev = h;
                            }
                            std::printf("    ends: a (%.9g, %.9g) b (%.9g, %.9g)\n", pa.x, pa.y, pb.x, pb.y);
                        }
                    }
                }
                for (size_t i = 0; i < cur.size(); ++i) {
                    if (cur[i].position.w == 0.0f || su.rows[i] < 0) continue;
                    const venue_s::Where w = venue_s::where(L, cur[i].position);
                    const glm::vec3 c(cur[i].position), p0(prev[i].position);
                    const float sd = seated::sdf(L, c);
                    bool slope = false;
                    const float wc = plausibility::detail::wallClearance(c, slope);
                    venue_s::Checker ck;
                    ck.L = &L;
                    float vr = 0.0f;
                    bool tun = false;
                    if (prev[i].position.w != 0.0f) ck.path(prev[i].position, cur[i].position, vr, tun);
                    const float fl = seated::floorHeight(L, glm::vec2(c));
                    const bool low = c.z < fl + BODY_RADIUS - 1e-4f, air = c.z > fl + BODY_RADIUS + 1e-4f;
                    const float minRise = a.has("minrise") ? float(units::modelLength(std::stod(a.get("minrise", "0.025")))) : STEP_UP_SAMPLE;
                    const bool bad = (!a.has("nostray") && which != "dense" && w.place == venue_s::P_CLEARWAY && w.row != su.rows[i]) || sd < 0.0f ||
                                     wc < BODY_RADIUS - plausibility::WALL_TOL || vr >= minRise || tun || low || (air && a.has("air"));
                    if (bad && shown < a.getInt("show", 6))
                        std::printf("  [vertical rise %.4f m, tunnel %d, low %d (%.4f m), air %d, sdf %.5f m] ", units::metres(vr), int(tun), int(low),
                                    units::metres(c.z - fl - BODY_RADIUS), int(air), units::metres(sd));
                    if (!bad) continue;
                    if (++shown > a.getInt("show", 6)) continue;
                    std::printf("step %d agent %zu (seat row %d): place %s row %d | prev (%.5f %.5f %.5f) -> cur (%.5f %.5f %.5f) | v (%.4f %.4f %.4f) | sdf %.6f wall %.6f floor %.6f | contacts 0x%02x drive (%.3f %.3f)\n",
                                s, i, su.rows[i], venue_s::placeName(w.place), w.row, p0.x, p0.y, p0.z, c.x, c.y, c.z, cur[i].velocity.x, cur[i].velocity.y,
                                cur[i].velocity.z, sd, wc, seated::floorHeight(L, glm::vec2(c)), unsigned(e.sim.contacts()[i]), table[i].x, table[i].y);
                }
                prev = cur;
            }
            std::printf("debug %s: %d offending agent-steps shown\n", which.c_str(), shown);
            // the end state: places, and the agents in gangways or on the walkway that did not move in the last step
            long places[venue_s::P_COUNT] = {};
            int listed = 0;
            const std::vector<GpuBoid> last = e.state();
            for (size_t i = 0; i < last.size(); ++i) {
                if (su.group[i] < 0) continue;
                const venue_s::Where w = venue_s::where(L, last[i].position);
                ++places[w.place];
                const float sp = glm::length(glm::vec2(last[i].velocity));
                if ((w.place != venue_s::P_CLEARWAY || which != "away") && w.place != venue_s::P_LEFT && sp < 1e-3f && listed < 25) {
                    ++listed;
                    const glm::vec3 c(last[i].position);
                    const glm::vec2 f = seated::fold(glm::vec2(c));
                    const glm::vec3 wq = seated::wall(L, c, 0.02f);
                    std::printf("  stopped: agent %zu (seat row %d) %s at folded (%.4f m, %.4f m) z %.4f m floor %.4f m | v %.4f | wall %.4f m dir (%.2f %.2f) | drive (%.2f %.2f) contacts 0x%02x\n",
                                i, su.rows[i], venue_s::placeName(w.place), units::metres(f.x), units::metres(f.y), units::metres(c.z),
                                units::metres(seated::floorHeight(L, glm::vec2(c))), sp, units::metres(wq.z), wq.x, wq.y, table[i].x, table[i].y,
                                unsigned(e.sim.contacts()[i]));
                }
            }
            for (int p = 0; p < venue_s::P_COUNT; ++p) if (places[p]) std::printf("  %s: %ld\n", venue_s::placeName(p), places[p]);
            if (a.has("dump")) {   // the final state: x, y, z (m), speed (m/s), place, seat row
                std::ofstream csv(a.get("dump", "debug.csv"));
                csv << "x,y,z,speed,place,row,agent\n";
                for (size_t i = 0; i < last.size(); ++i)
                    if (last[i].position.w != 0.0f)
                        csv << units::metres(last[i].position.x) << "," << units::metres(last[i].position.y) << "," << units::metres(last[i].position.z) << ","
                            << units::metresPerSecond(glm::length(glm::vec2(last[i].velocity))) << "," << venue_s::placeName(venue_s::where(L, last[i].position).place)
                            << "," << su.rows[i] << "," << i << "\n";
            }
            return 0;
        }
        if (cmd == "still") {   // diagnostics: the full seat spawn without a router on the CPU reference; who moves
            const Venue& v = venueByName(a.get("venue", "S"));
            const int steps = a.getInt("steps", 60);
            const std::vector<seated::Seat> all = seated::seats(v.layout);
            int active = 0;
            const std::vector<GpuBoid> s0 = spawnSeatedCrowd(v, 4096, 1.0, 1337, &active);
            CpuCrowdSim cpu(v, {}, 0);
            cpu.setState(s0);
            for (int i = 0; i < steps; ++i) cpu.step();
            const std::vector<GpuBoid>& s1 = cpu.state();
            int moved = 0;
            for (int i = 0; i < active; ++i) {
                const float d = glm::length(glm::vec3(s1[size_t(i)].position) - glm::vec3(s0[size_t(i)].position));
                if (d > 0.0f) {
                    if (moved < 40) std::printf("  moved %.5f m: q %d wing %d row %d segment %d seat %d (lat %.3f m)\n", units::metres(d), all[size_t(i)].quadrant,
                                                all[size_t(i)].wing, all[size_t(i)].row, all[size_t(i)].segment, all[size_t(i)].index, units::metres(all[size_t(i)].lat));
                    ++moved;
                }
            }
            std::printf("%d of %d seated agents moved in %d steps (CPU reference)\n", moved, active, steps);
            return 0;
        }
        std::printf("unknown command %s\n", cmd.c_str());
        return 2;
    } catch (const std::exception& e) {
        std::fprintf(stderr, "venue_probe: %s\n", e.what());
        return 1;
    }
}
