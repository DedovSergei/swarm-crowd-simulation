// CPU baseline tuning: workload snapshots, golden-state admissibility check and the
// OpenMP schedule x thread-count sweep of CpuCrowdSim (SortMode::Counting).
//   cpu_tune snapshots <dir> [--n 1024,4096,...]
//       spawn_<n>.bin (spawnBleacherCrowd) and congested_<n>.bin (GPU state after 250 steps), with a
//       spawn validity report (on a tread, in free space, no NaN) and the grid occupancy
//   cpu_tune golden
//       admissibility: both CPU golden hashes (golden::GOLDEN_STEPS steps from spawn, N = 4096) under every schedule
//       and several thread counts; exit code 1 on any mismatch
//   cpu_tune sweep <dir> <out.csv> [--rounds 2] [--n 4096,65536] [--states spawn,congested]
//                  [--threads 1,2,4,6,8,12,14,16,20] [--schedules all] [--steps-small 100] [--steps-large 10]
//       snapshot mode: every timed step starts from the identical snapshot (setState outside the
//       timed region); the schedule order rotates every round
// sweep [--venue S|M|L] times an analytic venue at 100% load with its default model on the thesis benchmark's snapshots
//       (<dir>/venue_<V>_<state>.bin, benchmark_crowd thesis; restoreAgentState before every step: the exit choice runs on);
//       [--proj-schedules list|same] the projection iterations' schedule (CpuCrowdSim::setProjectionSchedule): 'same' (default) = the
//     physics schedule; a list sweeps every (physics, projection) pair, the pairs' order rotated every round. The CSV gains
//       the venue, the projection schedule and the physics stage's parts (exit choice, predict, projection, final).
//       [--choice seq,par|...] the exit choice's threading (CpuCrowdSim::setParallelChoice: seq = sequential, par = the simulation's
//       threads; a label ending in _aa repeats its base mode, the A/A control); default: the tuned configuration's.
//   golden: also every (physics, projection) pair of static / dynamic64 / dynamic256 / guided, and venue S's CPU pins (GOLDEN_S:
//       counting and bitonic, the default model); --venues M,L adds their CPU counting pins at max threads (slow: L ~1 min)
#include "bench_common.hpp"
#include "../golden_state.hpp"

#include <swarm/assets.hpp>
#include <swarm/cpu_crowd_sim.hpp>
#include <swarm/sdf.hpp>
#include <swarm/venue.hpp>
#include <swarm/venue_capacity.hpp>

namespace fs = std::filesystem;
using namespace swarm;
using bench::Args;
using Schedule = CpuCrowdSim::Schedule;

namespace {

constexpr Schedule ALL_SCHEDULES[] = { Schedule::Static, Schedule::Dynamic64, Schedule::Dynamic256, Schedule::Dynamic1024, Schedule::Guided };

std::vector<Schedule> parseSchedules(const std::string& s) {
    if (s == "all") return std::vector<Schedule>(std::begin(ALL_SCHEDULES), std::end(ALL_SCHEDULES));
    std::vector<Schedule> out;
    for (const std::string& name : bench::parseList(s)) {
        bool found = false;
        for (Schedule k : ALL_SCHEDULES)
            if (name == CpuCrowdSim::scheduleName(k)) { out.push_back(k); found = true; }
        if (!found) throw std::runtime_error("unknown schedule " + name);
    }
    return out;
}

int cmdSnapshots(const Args& a) {
    if (a.positional.empty()) throw std::runtime_error("usage: cpu_tune snapshots <dir> [--n list]");
    const fs::path dir = a.positional[0];
    fs::create_directories(dir);
    bench::createHiddenContext("cpu_tune");
    const GLuint sdf = loadSDFTexture3D(resolveAsset("stadium.sdf"));
    const fs::path shaderDir = resolveAsset("shaders");
    std::printf("GL: %s | %s\n", bench::glRenderer().c_str(), bench::glDriver().c_str());
    for (int n : bench::parseIntList(a.get("n", "1024,4096,16384,65536,262144"))) {
        const auto t0 = bench::Clock::now();
        const std::vector<GpuBoid> spawn = spawnBleacherCrowd(n);
        long nan = 0, notFree = 0, noTread = 0;
        for (const GpuBoid& b : spawn) {
            const glm::vec3 p(b.position);
            nan += std::isnan(p.x) || std::isnan(p.y) || std::isnan(p.z);
            notFree += !(sampleSDF_CPU(p) > 0.0f);
            noTread += !(sampleSDF_CPU(p - glm::vec3(0.0f, 0.0f, 0.02f)) < 0.0f);
        }
        bench::saveSnapshot(bench::snapshotPath(dir, "spawn", n), spawn);
        CrowdSim sim(shaderDir, n);
        sim.upload(spawn);
        for (int i = 0; i < bench::CONGESTED_STEPS; ++i) sim.step(sdf);
        const std::vector<GpuBoid> congested = bench::readBuffer<GpuBoid>(sim.currentStateBuffer(), size_t(n));
        long congestedNan = 0;
        for (const GpuBoid& b : congested) congestedNan += std::isnan(b.position.x) || std::isnan(b.position.y) || std::isnan(b.position.z);
        bench::saveSnapshot(bench::snapshotPath(dir, "congested", n), congested);
        const bench::Occupancy os = bench::occupancy(spawn), oc = bench::occupancy(congested);
        std::printf("n=%6d spawn: NaN %ld, not in free space %ld, no tread below %ld | %d occupied cells, %.1f agents/cell (max %d), "
                    "%.0f candidates/agent\n", n, nan, notFree, noTread, os.occupiedCells, os.meanPerCell, os.maxPerCell, os.meanCandidates);
        std::printf("         congested (GPU step %d): %ld active, NaN %ld | %d occupied cells, %.1f agents/cell (max %d), "
                    "%.0f candidates/agent  [%.1f s]\n", bench::CONGESTED_STEPS, oc.active, congestedNan, oc.occupiedCells, oc.meanPerCell,
                    oc.maxPerCell, oc.meanCandidates, bench::msSince(t0) / 1000.0);
    }
    return 0;
}

int cmdGolden(const Args& a) {
    bench::createHiddenContext("cpu_tune");
    loadSDFTexture3D(resolveAsset("stadium.sdf"));
    const std::vector<GpuBoid> spawn = spawnBleacherCrowd(4096);
    int failures = 0, runs = 0;
    auto run = [&](const Venue& v, const std::vector<GpuBoid>& sp, CpuCrowdSim::SortMode mode, Schedule s, Schedule ps, int threads, uint64_t pinned,
                   const char* name, bool parChoice = CpuCrowdSim::TUNED_PARALLEL_CHOICE) {
        CpuCrowdSim cpu(v, defaultModelOptions(v), v.seated() ? std::vector<float>() : sdfVolumeCPU(), threads, mode);
        cpu.setSchedule(s);
        cpu.setProjectionSchedule(ps);
        cpu.setParallelChoice(parChoice);
        cpu.setState(sp);
        for (int i = 0; i < golden::GOLDEN_STEPS; ++i) cpu.step();
        const uint64_t h = golden::stateHash(cpu.state());
        failures += h != pinned;
        ++runs;
        std::printf("  %-30s %-11s / %-11s %2d threads, choice %s: %016llx %s\n", name, CpuCrowdSim::scheduleName(s), CpuCrowdSim::scheduleName(ps),
                    cpu.numThreads(), v.seated() ? (parChoice ? "par" : "seq") : "-", (unsigned long long)h, h == pinned ? "match" : "MISMATCH");
        std::fflush(stdout);
    };
    const Venue& terrace = terraceVenue();
    const golden::Golden& counting = golden::GOLDEN[golden::GOLDEN_CPU_COUNTING_4096];
    const golden::Golden& bitonic = golden::GOLDEN[golden::GOLDEN_CPU_BITONIC_4096];
    std::printf("terrace, one schedule for every physics loop (physics / projection):\n");
    for (Schedule s : ALL_SCHEDULES)
        for (int threads : { CpuCrowdSim::maxThreads(), 7 }) {
            run(terrace, spawn, CpuCrowdSim::SortMode::Counting, s, s, threads, counting.hash, counting.name);
            run(terrace, spawn, CpuCrowdSim::SortMode::GpuBitonic, s, s, threads, bitonic.hash, bitonic.name);
        }
    run(terrace, spawn, CpuCrowdSim::SortMode::Counting, Schedule::Static, Schedule::Static, 1, counting.hash, counting.name);
    // The projection's own schedule, and venue S (the default model: the exit choice, the incline speed, the stair spacing)
    const Venue& s = venueS();
    const std::vector<GpuBoid> spawnS = spawnSeatedCrowd(s, 4096, 1.0, 1337);
    const Schedule pairSet[] = { Schedule::Static, Schedule::Dynamic64, Schedule::Dynamic256, Schedule::Guided };
    std::printf("every (physics, projection) pair at max threads: the terrace (counting) and venue S (counting; bitonic at 7 threads):\n");
    for (Schedule ph : pairSet)
        for (Schedule pj : pairSet) {
            run(terrace, spawn, CpuCrowdSim::SortMode::Counting, ph, pj, CpuCrowdSim::maxThreads(), counting.hash, counting.name);
            for (bool par : { false, true }) {   // the exit choice sequential and in parallel
                run(s, spawnS, CpuCrowdSim::SortMode::Counting, ph, pj, CpuCrowdSim::maxThreads(), golden::GOLDEN_S[1].hash, golden::GOLDEN_S[1].name, par);
                run(s, spawnS, CpuCrowdSim::SortMode::GpuBitonic, ph, pj, 7, golden::GOLDEN_S[2].hash, golden::GOLDEN_S[2].name, par);
            }
        }
    run(s, spawnS, CpuCrowdSim::SortMode::Counting, Schedule::Static, Schedule::Static, 1, golden::GOLDEN_S[1].hash, golden::GOLDEN_S[1].name, false);
    run(s, spawnS, CpuCrowdSim::SortMode::Counting, Schedule::Static, Schedule::Static, 1, golden::GOLDEN_S[1].hash, golden::GOLDEN_S[1].name, true);
    // The nearest-exit and level-spacing models (GOLDEN_S_NEAREST: no exit choice; GOLDEN_S_LEVEL_SPACING: the exit choice) with the parallel choice
    for (bool par : { false, true }) {
        auto runModel = [&](const ModelOptions& mo, const golden::Golden& g) {
            CpuCrowdSim cpu(s, mo, std::vector<float>(), CpuCrowdSim::maxThreads(), CpuCrowdSim::SortMode::Counting);
            cpu.setParallelChoice(par);
            cpu.setState(spawnS);
            for (int i = 0; i < golden::GOLDEN_STEPS; ++i) cpu.step();
            const uint64_t h = golden::stateHash(cpu.state());
            failures += h != g.hash;
            ++runs;
            std::printf("  %-48s %2d threads, choice %s: %016llx %s\n", g.name, cpu.numThreads(), par ? "par" : "seq", (unsigned long long)h,
                        h == g.hash ? "match" : "MISMATCH");
        };
        runModel(ModelOptions{}, golden::GOLDEN_S_NEAREST[1]);
        runModel(ModelOptions{ ExitChoice::QueueAware, true, StairFlow::Off }, golden::GOLDEN_S_LEVEL_SPACING[1]);
    }
    for (const std::string& vn : bench::parseList(a.get("venues", ""))) {
        const Venue& v = venueByName(vn);
        const golden::Golden* g = vn == "M" ? golden::GOLDEN_M : vn == "L" ? golden::GOLDEN_L : nullptr;
        if (!g) throw std::runtime_error("--venues: M and / or L");
        const Schedule ph = a.has("schedule") ? parseSchedules(a.get("schedule", ""))[0] : CpuCrowdSim::TUNED_SCHEDULE;
        const Schedule pj = a.has("proj-schedule") ? parseSchedules(a.get("proj-schedule", ""))[0] : CpuCrowdSim::TUNED_SCHEDULE;
        for (bool par : { false, true })
            run(v, spawnSeatedCrowd(v, bench::venueBufferN(vn), 1.0, 1337), CpuCrowdSim::SortMode::Counting, ph, pj, CpuCrowdSim::maxThreads(), g[1].hash, g[1].name,
                par);
    }
    std::printf("%s: %d mismatch(es) in %d runs\n", failures ? "FAILED" : "ALL MATCH", failures, runs);
    return failures ? 1 : 0;
}

int cmdSweep(const Args& a) {
    if (a.positional.size() < 2) throw std::runtime_error("usage: cpu_tune sweep <snapshotDir> <out.csv> [options]");
    const fs::path dir = a.positional[0];
    const std::string csvPath = a.positional[1];
    const int rounds = a.getInt("rounds", 2);
    const std::string venueName = a.get("venue", "terrace");
    const Venue& venue = venueByName(venueName);
    const std::vector<int> ns = venue.seated() ? std::vector<int>{ bench::venueBufferN(venueName) } : bench::parseIntList(a.get("n", "4096,65536"));
    const std::vector<std::string> states = bench::parseList(a.get("states", "spawn,congested"));
    const std::vector<int> threadList = bench::parseIntList(a.get("threads", "1,2,4,6,8,12,14,16,20"));
    const std::vector<Schedule> schedules = parseSchedules(a.get("schedules", "all"));
    const std::string projArg = a.get("proj-schedules", "same");
    // The (physics, projection) pairs: 'same' = one schedule for both, else every pair
    struct Config { Schedule s, ps; std::string choice; };
    std::vector<std::pair<Schedule, Schedule>> pairs;
    if (projArg == "same") for (Schedule s : schedules) pairs.push_back({ s, s });
    else for (Schedule s : schedules) for (Schedule ps : parseSchedules(projArg)) pairs.push_back({ s, ps });
    const std::vector<std::string> choices = bench::parseList(a.get("choice", CpuCrowdSim::TUNED_PARALLEL_CHOICE ? "par" : "seq"));
    std::vector<Config> configs;
    for (const auto& [s, ps] : pairs) for (const std::string& c : choices) configs.push_back({ s, ps, c });
    // A/A control (--aa): the tuned configuration once more, labelled <choice>_aa
    if (a.has("aa")) configs.push_back({ CpuCrowdSim::TUNED_SCHEDULE, CpuCrowdSim::TUNED_PROJECTION_SCHEDULE, (CpuCrowdSim::TUNED_PARALLEL_CHOICE ? "par" : "seq") + std::string("_aa") });
    for (const Config& c : configs)
        if (c.choice.rfind("seq", 0) != 0 && c.choice.rfind("par", 0) != 0) throw std::runtime_error("--choice: seq | par (a label ending in _aa: the A/A control)");
    const int stepsSmall = a.getInt("steps-small", 100), stepsLarge = a.getInt("steps-large", 10);
    const int warmSmall = a.getInt("warmup-small", 20), warmLarge = a.getInt("warmup-large", 3);
    const std::string qos = bench::optOutOfPowerThrottling();   // as benchmark_crowd (E-core placement otherwise)

    std::vector<float> sdf = venue.seated() ? std::vector<float>() : loadSDFVolume(resolveAsset("stadium.sdf"));
    if (!venue.seated() && sdf.empty()) throw std::runtime_error("cannot load stadium.sdf");
    std::FILE* csv = std::fopen(csvPath.c_str(), "w");
    if (!csv) throw std::runtime_error("cannot write " + csvPath);
    std::fprintf(csv, "# cpu_tune sweep | commit %s (dirty %s) | build %s | flags %s | cpu %s | logical cores %u | %s | venue %s\n", bench::gitCommit().c_str(),
                 bench::gitDirty().c_str(), SWARM_BUILD_TYPE, SWARM_CORE_FLAGS, bench::cpuBrand().c_str(), bench::logicalCores(), qos.c_str(), venueName.c_str());
    std::fprintf(csv, "round,venue,N,state,schedule,proj_schedule,choice,threads,warmup_steps,measured_steps,hash_ms,sort_ms,cells_ms,physics_ms,choice_ms,predict_ms,"
                      "project_ms,final_ms,total_ms,total_p5_ms,total_p95_ms,total_cv,capacity_label\n");
    std::printf("cpu_tune sweep: %s | %u logical cores | commit %s | flags %s | %s | venue %s | %zu configurations\n", bench::cpuBrand().c_str(),
                bench::logicalCores(), bench::gitDescribe().c_str(), SWARM_CORE_FLAGS, qos.c_str(), venueName.c_str(), configs.size());
    const auto tStart = bench::Clock::now();
    for (int r = 0; r < rounds; ++r) {
        for (int n : ns) {
            for (const std::string& state : states) {
                const std::vector<GpuBoid> snap = venue.seated() ? bench::loadWorkloadSnapshot(dir, venueName, n, state) : bench::loadSnapshot(dir, state, n);
                const long active = bench::countActive(snap);
                const std::string label = venue.seated() ? venue::label(int(active), venue::capacityOf(venue)) : venue::label(n);
                const bool large = n >= 65536;
                const int warm = large ? warmLarge : warmSmall, steps = large ? stepsLarge : stepsSmall;
                for (int threads : threadList) {
                    for (size_t j = 0; j < configs.size(); ++j) {
                        const Config& cf = configs[(j + size_t(r) * 7) % configs.size()];   // rotated every round (by 7: coprime with typical sizes)
                        const Schedule s = cf.s, ps = cf.ps;
                        CpuCrowdSim cpu(venue, defaultModelOptions(venue), sdf, threads, CpuCrowdSim::SortMode::Counting);
                        cpu.setSchedule(s);
                        cpu.setProjectionSchedule(ps);
                        cpu.setParallelChoice(cf.choice.rfind("par", 0) == 0);
                        cpu.setState(snap);   // a fresh exit choice; restoreAgentState keeps it running (the terrace: the same as setState)
                        std::vector<double> hash, sort, cells, physics, choice, predict, project, fin, total;
                        for (int i = 0; i < warm + steps; ++i) {
                            cpu.restoreAgentState(snap);
                            cpu.step();
                            if (i < warm) continue;
                            const CpuCrowdSim::StageTimesMs& t = cpu.timings();
                            hash.push_back(t.hash); sort.push_back(t.sort); cells.push_back(t.cells); physics.push_back(t.physics);
                            choice.push_back(t.choice); predict.push_back(t.predict); project.push_back(t.project); fin.push_back(t.final);
                            total.push_back(t.total);
                        }
                        const bench::Stats st = bench::stats(total);
                        std::fprintf(csv, "%d,%s,%d,%s,%s,%s,%s,%d,%d,%d,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f,%.4f,%s\n", r, venueName.c_str(), n,
                                     state.c_str(), CpuCrowdSim::scheduleName(s), CpuCrowdSim::scheduleName(ps), cf.choice.c_str(), threads, warm, steps, bench::median(hash),
                                     bench::median(sort), bench::median(cells), bench::median(physics), bench::median(choice), bench::median(predict),
                                     bench::median(project), bench::median(fin), st.median, st.p5, st.p95, st.cv, bench::csvField(label).c_str());
                        std::fflush(csv);
                        std::printf("r%d %s n=%6d %-9s %-11s / %-11s %-6s t=%2d  hash %.4f choice %.3f predict %.3f project %.3f final %.3f total %9.3f ms (cv %.3f)  [%.0f s]\n",
                                    r, venueName.c_str(), n, state.c_str(), CpuCrowdSim::scheduleName(s), CpuCrowdSim::scheduleName(ps), cf.choice.c_str(), threads,
                                    bench::median(hash), bench::median(choice), bench::median(predict), bench::median(project), bench::median(fin), st.median,
                                    st.cv, bench::msSince(tStart) / 1000.0);
                        std::fflush(stdout);
                    }
                }
            }
        }
    }
    std::fclose(csv);
    return 0;
}

} // namespace

int main(int argc, char** argv) {
    if (argc < 2) {
        std::fprintf(stderr, "usage: cpu_tune snapshots|golden|sweep ...\n");
        return 2;
    }
    try {
        const std::string cmd = argv[1];
        const Args a(argc, argv, 2);
        if (cmd == "snapshots") return cmdSnapshots(a);
        if (cmd == "golden") return cmdGolden(a);
        if (cmd == "sweep") return cmdSweep(a);
        std::fprintf(stderr, "unknown command %s\n", cmd.c_str());
        return 2;
    } catch (const std::exception& e) {
        std::fprintf(stderr, "FATAL: %s\n", e.what());
        return 1;
    }
}
