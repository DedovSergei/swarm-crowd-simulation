// step_probe: step-ups and unreachable floors in the terrace evacuation, and the venue's floor capacity.
//
//   step_probe measure --n N [--steps S] [--seed 1337] [--name NAME] [--out out/results/stepup] [--events-cap 20000]
//   step_probe venue   [--out out/results/stepup]
//
// measure: spawnBleacherCrowd(N, seed), the GPU pipeline from spawn until every agent has left or S steps (default
// 6000), reading the state back after every step (a tool: readbacks are allowed). Per active agent and step:
//   - the floor under its centre before and after the step (tools/stepup.hpp floorUnder, exact CPU sampler) and the rise
//     F_end - F_start; rises above RISE_LIMIT_M (0.30 m) are events;
//   - which pass made the rise: a dispatch hook reads the predict pass's output (slot order, binding 5), its grounded
//     flags (binding 6) and the slot -> agent map (binding 1), and the projection's state after its next-to-last
//     iteration (binding 5 of that dispatch, with the displacement so far in velocity.w). The rise splits into the
//     predict pass's part (integration + static contacts: F_pred - F_start) and the final pass's (the projection's last
//     iteration + the final static contacts, settleOnFloor for a grounded agent, else the lift-only restOnFloor:
//     F_end - F_pred); the horizontal move into integration (start -> predicted) and projection (predicted -> end);
//   - its floor class (stepup::classify): the agents off the egress route (the rear platform, wall tops) every step, and
//     how each reached the platform (from the tread zone over the riser, or from the aisle zone);
//   - riser climbs (stepup::ClimbTracker): arrivals on a higher tread row other than through the aisle, with the steps the
//     climb took and its largest single-step rise;
//   - the walkway: agents on it at spawn and every step, and how each arrived (from the treads, i.e. off a tread front,
//     or from the aisle).
// Writes <out>/<name>_<yyyymmdd_hhmm>/: steps.csv (one row per step), rises.csv (the rise events, first --events-cap),
// climbs.csv (the riser climbs, first --events-cap), summary.md.
// venue: the metric grid's walkable floor area (metrics::computeMetricVenue: the sum of the cells' walkable area), per
// zone, the tread zone split into the treads and the rear platform, and the hard-body jam capacity (area x hexagonal
// packing of BODY_RADIUS disks, plausibility::HEX_PACKING_P_M2) -> <out>/venue_capacity.md. Run from the repository root.
#include "../benchmark/bench_common.hpp"
#include "../plausibility.hpp"
#include "../stepup.hpp"

#include <swarm/assets.hpp>
#include <swarm/crowd_sim.hpp>
#include <swarm/metrics.hpp>
#include <swarm/sdf.hpp>

#include <array>
#include <cstdlib>
#include <map>

namespace fs = std::filesystem;
using namespace swarm;
namespace mt = swarm::metrics;

namespace {

constexpr double RISE_LIMIT_M = 0.30;   // the probe's threshold for a step-up event
const float RISE_LIMIT = float(units::modelLength(RISE_LIMIT_M));
// Rise histogram bins (metres, upper bounds; the last bin is open) of the rises above RISE_HIST_MIN_M
constexpr double RISE_HIST_MIN_M = 0.05;
// An upward step onto a wall-steep floor: a rise above STEEP_RISE_MIN (3 mm) ending on n_z <= WALL_MAX_NZ
constexpr float STEEP_RISE_MIN = 1e-4f;
constexpr std::array<double, 6> RISE_BINS_M{ 0.10, 0.20, 0.30, 0.35, 0.40, 1e9 };

std::string m(double modelLength, int prec = 3) { char b[32]; std::snprintf(b, sizeof b, "%.*f", prec, units::metres(modelLength)); return b; }

GLuint boundSsbo(GLuint index) {
    GLint b = 0;
    glGetIntegeri_v(GL_SHADER_STORAGE_BUFFER_BINDING, index, &b);
    return GLuint(b);
}

int runVenue(const bench::Args& a) {
    const fs::path out = a.get("out", "out/results/stepup");
    bench::createHiddenContext("step_probe");
    if (!loadSDFTexture3D(resolveAsset("stadium.sdf"))) throw std::runtime_error("cannot load stadium.sdf");
    const std::vector<float>& vol = sdfVolumeCPU();
    const mt::MetricVenue v = mt::computeMetricVenue(vol);

    double all = 0, included = 0, byZone[mt::ZONE_COUNT] = {};
    for (int c = 0; c < mt::CELLS; ++c) {
        all += v.walkableM2[size_t(c)];
        if (v.included[size_t(c)]) included += v.walkableM2[size_t(c)];
        if (v.zone[size_t(c)] < mt::ZONE_COUNT) byZone[v.zone[size_t(c)]] += v.walkableM2[size_t(c)];
    }
    // The tread zone split by the floor under each walkable sample point of the metric grid (its own sampling, the same
    // walkable test): rows 1-7, the platform (row 8), between rows (riser ramps, lips); per sample zone, not per cell
    const int S = mt::SUBSAMPLES;
    const double sampleM = mt::CELL_M / S;
    std::array<double, mt::ZONE_COUNT> sampleZoneArea{};
    double treadRows = 0, platform = 0, between = 0;
    for (int cell = 0; cell < mt::CELLS; ++cell) {
        const int ix = cell % mt::GRID_RES, iy = cell / mt::GRID_RES;
        for (int sy = 0; sy < S; ++sy)
            for (int sx = 0; sx < S; ++sx) {
                const double xm = mt::GRID_MIN_M + ix * mt::CELL_M + (sx + 0.5) * sampleM;
                const double ym = mt::GRID_MIN_M + iy * mt::CELL_M + (sy + 0.5) * sampleM;
                const glm::vec2 p(float(units::modelLength(xm)), float(units::modelLength(ym)));
                const bool inFootprint = std::max(std::abs(p.x), std::abs(p.y)) <= SDF_ORIGIN.x * -1.0f;
                if (!inFootprint || sampleSDF(vol, glm::vec3(p, mt::FLOOR_PROBE_TOP_Z)) <= 0.0f ||
                    sampleSDF(vol, glm::vec3(p, mt::FLOOR_PROBE_BOTTOM_Z)) > 0.0f || sdFence(glm::vec3(p, 0.0f)) + BODY_RADIUS <= 0.0f)
                    continue;
                const uint32_t z = mt::sampleZone(p, v.outerWallInnerDepth);
                sampleZoneArea[z] += sampleM * sampleM;
                if (z != mt::ZONE_TREAD) continue;
                const float f = stepup::floorUnder(glm::vec3(p, mt::FLOOR_PROBE_TOP_Z));
                const stepup::FloorClass fc = stepup::classify(p, f, v.outerWallInnerDepth);
                (fc.row == stepup::PLATFORM_ROW ? platform : fc.row >= 1 ? treadRows : between) += sampleM * sampleM;
            }
    }
    const double hex = plausibility::HEX_PACKING_P_M2;
    const double occupiable = all - byZone[mt::ZONE_PITCH];
    fs::create_directories(out);
    const fs::path file = out / "venue_capacity.md";
    FILE* f = std::fopen(file.string().c_str(), "w");
    if (!f) throw std::runtime_error("cannot write " + file.string());
    auto both = [&](const char* fmt, auto... args) { std::printf(fmt, args...); std::fprintf(f, fmt, args...); };
    both("# Venue floor area and jam capacity (step_probe venue)\n\n");
    both("commit %s (dirty %s), %s\n\n", bench::gitCommit().c_str(), bench::gitDirty().c_str(), buildinfo::buildConfig());
    both("Metric grid: %d x %d cells of %.0f m, %d x %d walkable samples per cell (metrics::computeMetricVenue). Hexagonal packing "
         "of %.2f m bodies (BODY_RADIUS_M %.2f): %.4f persons/m^2.\n\n", mt::GRID_RES, mt::GRID_RES, mt::CELL_M, S, S, 2.0 * BODY_RADIUS_M,
         double(BODY_RADIUS_M), hex);
    both("| floor | area m^2 | jam capacity (x %.2f) |\n|---|---:|---:|\n", hex);
    both("| all walkable (sum of the cells' walkable area) | %.1f | %.0f |\n", all, all * hex);
    both("| included cells only (>= %.2f m^2) | %.1f | %.0f |\n", mt::MIN_WALKABLE_M2, included, included * hex);
    for (int z = 0; z < mt::ZONE_COUNT; ++z) both("| . zone %s (cells by majority) | %.1f | %.0f |\n", mt::zoneName(uint32_t(z)), byZone[z], byZone[z] * hex);
    both("| occupiable: all walkable minus the pitch (fenced, no gates) | %.1f | **%.0f** |\n", occupiable, occupiable * hex);
    both("\nTread zone by sample point (%.1f m^2): tread rows 1-7 %.1f m^2, rear platform (row 8) %.1f m^2, between rows (riser ramps, "
         "lips) %.1f m^2.\n", sampleZoneArea[mt::ZONE_TREAD], treadRows, platform, between);
    both("Sample-point zones: ");
    for (int z = 0; z < mt::ZONE_COUNT; ++z) both("%s %.1f%s", mt::zoneName(uint32_t(z)), sampleZoneArea[size_t(z)], z + 1 < mt::ZONE_COUNT ? ", " : " m^2\n");
    both("Occupiable without the rear platform: %.1f m^2, jam capacity %.0f.\n", occupiable - platform, (occupiable - platform) * hex);
    std::fclose(f);
    std::printf("wrote %s\n", file.string().c_str());
    return 0;
}

struct RiseEvent {
    int step, agent;
    glm::vec3 start, pred, end;
    float f0, fp, f2, projDisp;
    bool groundedFlag;
    stepup::FloorClass c0, c2;
    float nzEnd;   // floor normal n_z under the end position
};

int runMeasure(const bench::Args& a) {
    const int n = a.getInt("n", 4096);
    const unsigned seed = unsigned(std::stoul(a.get("seed", "1337")));
    const int maxSteps = a.getInt("steps", 6000);
    const size_t cap = size_t(a.getInt("events-cap", 20000));
    const std::string name = a.get("name", "stepup_n" + std::to_string(n));
    const fs::path dir = fs::path(a.get("out", "out/results/stepup")) / (name + "_" + bench::localTimestamp("%Y%m%d_%H%M"));

    bench::createHiddenContext("step_probe");
    const GLuint sdf = loadSDFTexture3D(resolveAsset("stadium.sdf"));
    if (!sdf) throw std::runtime_error("cannot load stadium.sdf");
    const fs::path shaderDir = resolveAsset("shaders");
    const mt::MetricVenue venue = mt::computeMetricVenue(sdfVolumeCPU());
    const float wallDep = venue.outerWallInnerDepth;
    std::printf("step_probe measure | N %d, seed %u, up to %d steps | commit %s (dirty %s) | %s | %s\n", n, seed, maxSteps, bench::gitCommit().c_str(),
                bench::gitDirty().c_str(), buildinfo::buildConfig(), bench::glRenderer().c_str());

    const std::vector<GpuBoid> spawn = spawnBleacherCrowd(n, seed);
    CrowdSim sim(shaderDir, n);
    sim.upload(spawn);
    const int K = sim.projectionIterations();
    std::vector<GpuGridInfo> grid;
    std::vector<GpuBoid> predSlots, projSlots;
    std::vector<glm::vec4> planes;
    sim.setDispatchHook([&](const CrowdSim::DispatchInfo& d) {
        const std::string pass = d.pass;
        if (pass == "physics") {
            grid = bench::readBuffer<GpuGridInfo>(boundSsbo(BIND_GRID), size_t(n));
            predSlots = bench::readBuffer<GpuBoid>(boundSsbo(BIND_SLOT_OUT), size_t(n));
            planes = bench::readBuffer<glm::vec4>(boundSsbo(BIND_SLOT_PLANES), size_t(n));
        } else if (pass == "project" && d.j == K - 1) {
            projSlots = bench::readBuffer<GpuBoid>(boundSsbo(BIND_SLOT_OUT), size_t(n));
        }
    });

    // Spawn: floors and classes
    std::vector<float> floorPrev(static_cast<size_t>(n));
    std::vector<stepup::FloorClass> classPrev(static_cast<size_t>(n));
    std::array<long, 10> spawnRows{};
    long spawnWalkway = 0, spawnUnreachable = 0;
    stepup::ClimbTracker climbs(static_cast<size_t>(n));
    for (int i = 0; i < n; ++i) {
        const glm::vec3 c(spawn[size_t(i)].position);
        floorPrev[size_t(i)] = stepup::floorUnder(c);
        classPrev[size_t(i)] = stepup::classify(glm::vec2(c), floorPrev[size_t(i)], wallDep);
        const stepup::FloorClass& fc = classPrev[size_t(i)];
        if (fc.row >= 0 && fc.row < 10) ++spawnRows[size_t(fc.row)];
        spawnWalkway += fc.zone == mt::ZONE_WALKWAY;
        spawnUnreachable += fc.offRoute();
        stepup::ClimbEvent e;
        climbs.update(i, 0, fc, 0.0f, false, e);
    }
    const double capacity = spawnCapacity();
    std::printf("spawn: %ld on the walkway zone, %ld on the platform or wall tops; rows 0-8: ", spawnWalkway, spawnUnreachable);
    for (int r = 0; r <= stepup::PLATFORM_ROW; ++r) std::printf("%ld ", spawnRows[size_t(r)]);
    std::printf("(spawn capacity %.0f: %s)\n", capacity, double(n) <= capacity ? "relaxed overlap-free" : "over capacity, starts stacked as placed");

    fs::create_directories(dir);
    FILE* fs_ = std::fopen((dir / "steps.csv").string().c_str(), "w");
    std::fprintf(fs_, "step,active,rises_gt_limit,max_rise_m,rise_pred_part,rise_final_settle,rise_final_rest,steep_up_steps,riser_climbs,platform,platform_from_tread,"
                      "platform_from_aisle,wall_top,walkway,walkway_from_tread,walkway_from_aisle,airborne\n");
    std::vector<RiseEvent> rises;
    std::vector<std::pair<int, stepup::ClimbEvent>> climbEvents;
    std::array<long, RISE_BINS_M.size()> riseHist{};
    long totalRises = 0, riseByPred = 0, riseByFinalSettle = 0, riseByFinalRest = 0, totalClimbs = 0, totalPlatformEntriesTread = 0,
         totalPlatformEntriesAisle = 0, totalWalkwayFromTread = 0, totalWalkwayFromAisle = 0, maxPlatform = 0, maxWallTop = 0, agentStepsUnreachable = 0;
    long climbsByDuration[4] = {}, climbsWithBigStep = 0, climbsWithSteepUp = 0, climbsCaught = 0;   // 1, 2-3, 4-10, > 10 steps
    long totalSteepUp = 0;   // agent-steps whose floor rose (> STEEP_RISE_MIN) onto a wall-steep floor (n_z <= WALL_MAX_NZ)
    std::map<std::pair<int, int>, long> climbRows;
    std::map<std::string, long> riseWhere;
    double maxRise = 0;
    int evacStep = -1, lastStep = 0;
    std::vector<GpuBoid> prev = spawn;
    std::vector<char> everUnreachable(static_cast<size_t>(n), 0);

    for (int step = 1; step <= maxSteps; ++step) {
        sim.step(sdf);
        const std::vector<GpuBoid> cur = bench::readBuffer<GpuBoid>(sim.currentStateBuffer(), size_t(n));
        lastStep = step;
        // Agent order of the predict / projection states
        std::vector<int> slotOf(static_cast<size_t>(n), -1);
        for (int s = 0; s < n; ++s)
            if (grid[size_t(s)].gridID != INACTIVE_CELL) slotOf[grid[size_t(s)].boidID] = s;

        std::vector<float> floorCur(static_cast<size_t>(n), std::numeric_limits<float>::quiet_NaN()), floorPred(static_cast<size_t>(n), std::numeric_limits<float>::quiet_NaN());
        std::vector<char> airborne(static_cast<size_t>(n), 0), steepUp(static_cast<size_t>(n), 0);
        std::vector<float> nzEnd(static_cast<size_t>(n), 1.0f);
        std::vector<stepup::FloorClass> classCur(static_cast<size_t>(n));
#pragma omp parallel for schedule(dynamic, 256)
        for (int i = 0; i < n; ++i) {
            if (cur[size_t(i)].position.w == 0.0f) continue;
            bool g = false;
            const glm::vec3 c(cur[size_t(i)].position);
            floorCur[size_t(i)] = stepup::floorUnder(c, &g);
            airborne[size_t(i)] = !g;
            classCur[size_t(i)] = stepup::classify(glm::vec2(c), floorCur[size_t(i)], wallDep);
            if (floorCur[size_t(i)] - floorPrev[size_t(i)] > STEEP_RISE_MIN) {   // NaN compares false
                nzEnd[size_t(i)] = stepup::floorNormalZ(glm::vec2(c), floorCur[size_t(i)]);
                steepUp[size_t(i)] = nzEnd[size_t(i)] <= WALL_MAX_NZ;
            }
            const int s = slotOf[size_t(i)];
            if (s >= 0 && predSlots[size_t(s)].position.w != 0.0f) floorPred[size_t(i)] = stepup::floorUnder(glm::vec3(predSlots[size_t(s)].position));
        }

        long active = 0, stepRises = 0, stepPred = 0, stepSettle = 0, stepRest = 0, stepClimbs = 0, stepSteepUp = 0, platform = 0, platformTread = 0, platformAisle = 0,
             wallTop = 0, walkway = 0, walkwayTread = 0, walkwayAisle = 0, air = 0;
        double stepMax = 0;
        for (int i = 0; i < n; ++i) {
            const GpuBoid& b = cur[size_t(i)];
            if (b.position.w == 0.0f) continue;
            ++active;
            air += airborne[size_t(i)];
            stepSteepUp += steepUp[size_t(i)];
            const stepup::FloorClass& c2 = classCur[size_t(i)];
            const stepup::FloorClass& c0 = classPrev[size_t(i)];
            const float rise = floorCur[size_t(i)] - floorPrev[size_t(i)];
            if (!std::isnan(rise)) {
                stepMax = std::max(stepMax, double(rise));
                const double rm = units::metres(rise);
                if (rm > RISE_HIST_MIN_M)
                    for (size_t k = 0; k < RISE_BINS_M.size(); ++k)
                        if (rm <= RISE_BINS_M[k]) { ++riseHist[k]; break; }
            }
            if (!std::isnan(rise) && rise > RISE_LIMIT) {
                ++stepRises;
                const int s = slotOf[size_t(i)];
                RiseEvent e{ step, i, glm::vec3(prev[size_t(i)].position), s >= 0 ? glm::vec3(predSlots[size_t(s)].position) : glm::vec3(NAN),
                             glm::vec3(b.position), floorPrev[size_t(i)], floorPred[size_t(i)], floorCur[size_t(i)],
                             s >= 0 && !projSlots.empty() ? projSlots[size_t(s)].velocity.w : NAN, s >= 0 && planes[size_t(s)].w >= 2.0f, c0, c2, nzEnd[size_t(i)] };
                const float predPart = e.fp - e.f0, finalPart = e.f2 - e.fp;
                if (!std::isnan(predPart) && predPart > finalPart) ++stepPred;
                else if (e.groundedFlag) ++stepSettle;
                else ++stepRest;
                char where[96];
                std::snprintf(where, sizeof where, "%s row %d -> %s row %d", mt::zoneName(c0.zone), c0.row, mt::zoneName(c2.zone), c2.row);
                ++riseWhere[where];
                if (rises.size() < cap) rises.push_back(e);
            }
            stepup::ClimbEvent ce;
            if (climbs.update(i, step, c2, rise, steepUp[size_t(i)] != 0, ce)) {
                ++stepClimbs;
                ++climbRows[{ ce.fromRow, ce.toRow }];
                ++climbsByDuration[ce.steps <= 1 ? 0 : ce.steps <= 3 ? 1 : ce.steps <= 10 ? 2 : 3];
                climbsWithBigStep += ce.maxStepRise > RISE_LIMIT;
                climbsWithSteepUp += ce.steepUpSteps > 0;
                climbsCaught += ce.maxStepRise > RISE_LIMIT || ce.steepUpSteps > 0;
                if (climbEvents.size() < cap) climbEvents.push_back({ step, ce });
            }
            if (c2.platform()) {
                ++platform;
                if (!c0.platform()) (c0.zone == mt::ZONE_AISLE ? platformAisle : platformTread)++;
            }
            wallTop += c2.wallTop;
            if (c2.offRoute()) { ++agentStepsUnreachable; everUnreachable[size_t(i)] = 1; }
            if (c2.zone == mt::ZONE_WALKWAY) {
                ++walkway;
                if (c0.zone == mt::ZONE_TREAD) ++walkwayTread;
                else if (c0.zone == mt::ZONE_AISLE) ++walkwayAisle;
            }
        }
        totalRises += stepRises;
        totalSteepUp += stepSteepUp;
        riseByPred += stepPred;
        riseByFinalSettle += stepSettle;
        riseByFinalRest += stepRest;
        totalClimbs += stepClimbs;
        totalPlatformEntriesTread += platformTread;
        totalPlatformEntriesAisle += platformAisle;
        totalWalkwayFromTread += walkwayTread;
        totalWalkwayFromAisle += walkwayAisle;
        maxPlatform = std::max(maxPlatform, platform);
        maxWallTop = std::max(maxWallTop, wallTop);
        maxRise = std::max(maxRise, stepMax);
        std::fprintf(fs_, "%d,%ld,%ld,%.4f,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld\n", step, active, stepRises, units::metres(stepMax), stepPred,
                     stepSettle, stepRest, stepSteepUp, stepClimbs, platform, platformTread, platformAisle, wallTop, walkway, walkwayTread, walkwayAisle, air);
        if (step % 250 == 0 || active == 0)
            std::printf("  step %5d: active %6ld, rises > %.2f m this step %4ld (total %ld), riser climbs total %ld, platform %ld, wall tops %ld, walkway %ld\n",
                        step, active, RISE_LIMIT_M, stepRises, totalRises, totalClimbs, platform, wallTop, walkway);
        floorPrev.swap(floorCur);
        classPrev.swap(classCur);
        prev = cur;
        if (active == 0) { evacStep = step; break; }
    }
    std::fclose(fs_);
    bench::saveSnapshot(dir / "final_state.bin", prev);   // the last state (raw GpuBoid array)
    long agentsEverUnreachable = 0;
    for (char c : everUnreachable) agentsEverUnreachable += c;

    FILE* fr = std::fopen((dir / "rises.csv").string().c_str(), "w");
    std::fprintf(fr, "step,agent,x0,y0,z0,xp,yp,zp,x2,y2,z2,floor0_m,floor_pred_m,floor2_m,rise_m,rise_pred_part_m,rise_final_part_m,move_integration_m,"
                     "move_projection_m,proj_disp_m,grounded_flag,zone0,row0,zone2,row2,nz_end\n");
    for (const RiseEvent& e : rises)
        std::fprintf(fr, "%d,%d,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%d,%s,%d,%s,%d,%.3f\n", e.step, e.agent,
                     e.start.x, e.start.y, e.start.z, e.pred.x, e.pred.y, e.pred.z, e.end.x, e.end.y, e.end.z, units::metres(e.f0), units::metres(e.fp),
                     units::metres(e.f2), units::metres(e.f2 - e.f0), units::metres(e.fp - e.f0), units::metres(e.f2 - e.fp),
                     units::metres(glm::length(glm::vec2(e.pred) - glm::vec2(e.start))), units::metres(glm::length(glm::vec2(e.end) - glm::vec2(e.pred))),
                     units::metres(e.projDisp), int(e.groundedFlag), mt::zoneName(e.c0.zone), e.c0.row, mt::zoneName(e.c2.zone), e.c2.row, e.nzEnd);
    std::fclose(fr);
    FILE* fc = std::fopen((dir / "climbs.csv").string().c_str(), "w");
    std::fprintf(fc, "step,agent,from_row,to_row,steps,max_step_rise_m,steep_up_steps\n");
    for (const auto& [s, e] : climbEvents)
        std::fprintf(fc, "%d,%d,%d,%d,%d,%.4f,%d\n", s, e.agent, e.fromRow, e.toRow, e.steps, units::metres(e.maxStepRise), e.steepUpSteps);
    std::fclose(fc);

    // Mechanism statistics over the recorded rise events
    long evGrounded = 0, evProjMoved = 0, evProjDominant = 0;
    std::vector<double> moveInt, moveProj;
    for (const RiseEvent& e : rises) {
        evGrounded += e.groundedFlag;
        const double mi = glm::length(glm::vec2(e.pred) - glm::vec2(e.start)), mp = glm::length(glm::vec2(e.end) - glm::vec2(e.pred));
        moveInt.push_back(units::metres(mi));
        moveProj.push_back(units::metres(mp));
        evProjMoved += e.projDisp > 0.0f;
        evProjDominant += mp > mi;
    }
    const bench::Stats si = bench::stats(moveInt), sp = bench::stats(moveProj);

    FILE* f = std::fopen((dir / "summary.md").string().c_str(), "w");
    auto both = [&](const char* fmt, auto... args) { std::printf(fmt, args...); std::fprintf(f, fmt, args...); };
    both("# step_probe measure: N = %d (seed %u)\n\n", n, seed);
    both("commit %s (dirty %s), %s, %s\n\n", bench::gitCommit().c_str(), bench::gitDirty().c_str(), buildinfo::buildConfig(), bench::glRenderer().c_str());
    both("- steps: %d (%s)\n", lastStep, evacStep > 0 ? ("full evacuation at step " + std::to_string(evacStep)).c_str() : "step limit, not evacuated");
    both("- spawn: %s (capacity %.0f); on the walkway zone at spawn: %ld; on the platform or wall tops at spawn: %ld\n",
         double(n) <= capacity ? "relaxed overlap-free" : "over the spawn capacity, stacked as placed", capacity, spawnWalkway, spawnUnreachable);
    both("- floor rises > %.2f m in one step: **%ld** agent-steps; max rise %s m\n", RISE_LIMIT_M, totalRises, m(maxRise).c_str());
    both("  - histogram of single-step floor rises (agent-steps): 0.05-0.10 m %ld, 0.10-0.20 %ld, 0.20-0.30 %ld, 0.30-0.35 %ld, 0.35-0.40 %ld, > 0.40 %ld\n",
         riseHist[0], riseHist[1], riseHist[2], riseHist[3], riseHist[4], riseHist[5]);
    both("  - which pass made the rise: predict (integration + static contacts) %ld, final pass of a grounded agent (projection + settleOnFloor) %ld, "
         "final pass of an airborne agent (projection + lift-only restOnFloor) %ld\n", riseByPred, riseByFinalSettle, riseByFinalRest);
    both("  - of the %zu recorded events: predict-pass grounded flag %ld; moved by the projection (displacement > 0) %ld; horizontal move "
         "integration median %.3f m (max %.3f), projection + final contacts median %.3f m (max %.3f); projection move larger: %ld\n", rises.size(),
         evGrounded, evProjMoved, si.median, si.max, sp.median, sp.max, evProjDominant);
    both("  - where (start zone/row -> end zone/row):\n");
    std::vector<std::pair<long, std::string>> w;
    for (const auto& [k, c] : riseWhere) w.push_back({ c, k });
    std::sort(w.rbegin(), w.rend());
    for (size_t i = 0; i < std::min<size_t>(w.size(), 12); ++i) both("    - %s: %ld\n", w[i].second.c_str(), w[i].first);
    both("- riser climbs (arrival on a higher tread row other than through the aisle): **%ld**; took 1 step %ld, 2-3 %ld, 4-10 %ld, > 10 %ld; "
         "with a single-step rise > %.2f m: %ld\n", totalClimbs, climbsByDuration[0], climbsByDuration[1], climbsByDuration[2], climbsByDuration[3],
         RISE_LIMIT_M, climbsWithBigStep);
    both("  - with a step that rose onto a wall-steep floor (n_z <= %.1f): %ld; with either (caught by a height limit of %.2f m plus a no-rise-onto-"
         "wall-steep-floor rule): %ld of %ld\n", WALL_MAX_NZ, climbsWithSteepUp, RISE_LIMIT_M, climbsCaught, totalClimbs);
    both("- agent-steps whose floor rose (> %.1f mm model) onto a wall-steep floor (n_z <= %.1f): %ld\n", STEEP_RISE_MIN * 1000.0f, WALL_MAX_NZ, totalSteepUp);
    both("  - rows (from -> to): ");
    for (const auto& [k, c] : climbRows) both("%d->%d %ld; ", k.first, k.second, c);
    both("\n- off the egress route (the platform is reached legally up the aisle): "
         "rear platform or wall tops: agent-steps %ld, agents ever %ld; max per step: rear platform %ld, wall tops %ld\n", agentStepsUnreachable,
         agentsEverUnreachable, maxPlatform, maxWallTop);
    both("  - arrivals on the platform: from the tread zone (over the riser) %ld, from the aisle zone %ld\n", totalPlatformEntriesTread,
         totalPlatformEntriesAisle);
    both("- walkway: arrivals from the tread zone (off a tread front) %ld, from the aisle %ld\n", totalWalkwayFromTread, totalWalkwayFromAisle);
    std::fclose(f);
    std::printf("wrote %s\n", dir.string().c_str());
    return 0;
}

} // namespace

int main(int argc, char** argv) {
    try {
        if (argc < 2) {
            std::printf("usage: step_probe measure --n N [--steps S] [--seed 1337] [--name NAME] [--out out/results/stepup] [--events-cap 20000]\n"
                        "       step_probe venue [--out out/results/stepup]\n");
            return 2;
        }
        const std::string cmd = argv[1];
        const bench::Args a(argc, argv, 2);
        if (cmd == "measure") return runMeasure(a);
        if (cmd == "venue") return runVenue(a);
        std::printf("unknown command %s\n", cmd.c_str());
        return 2;
    } catch (const std::exception& e) {
        std::fprintf(stderr, "step_probe: %s\n", e.what());
        return 1;
    }
}
