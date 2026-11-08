// Physics sub-phase profile of CpuCrowdSim. Built by the cpu_profile target, which
// compiles cpu_crowd_sim.cpp with SWARM_CPU_PROFILE: rdtsc marks per agent split the physics pass
// into phases (cpu_profile::Phase) and count candidates, neighbours, separation pairs and SDF reads.
// Separation runs inside the neighbour loop, so its cost is measured by ablation: the same snapshot
// once with and once without separationForce (neighbour-phase difference).
//   cpu_profile <snapshotDir> [--n 65536] [--state congested] [--threads 1,20] [--steps 5] [--schedule static]
// [--venue S|M|L] profiles an analytic venue at 100% load with its default model on the thesis benchmark's snapshots
// (<snapshotDir>/venue_<V>_<state>.bin, benchmark_crowd thesis; N = the venue's buffer); [--proj-schedule s] the projection's schedule;
// [--parallel-choice 0|1] the exit choice's threading (default: the tuned configuration's).
// Every timed step restores the agent state only (CpuCrowdSim::restoreAgentState: the exit choice runs on, as in the benchmark). The
// step's stages by wall clock: hash, sort, cells, and physics split into the exit choice, predict, the projection
// iterations and the final pass.
#include "bench_common.hpp"

#include <swarm/assets.hpp>
#include <swarm/cpu_crowd_sim.hpp>
#include <swarm/sdf.hpp>
#include <swarm/venue.hpp>

#include <intrin.h>

namespace fs = std::filesystem;
using namespace swarm;
namespace prof = swarm::cpu_profile;

namespace {

const char* PHASE_NAMES[prof::PHASE_COUNT] = { "other (setup, e_goal, inactive, exit)", "neighbour loop (incl. separation)",
                                               "obstacle SDF sampling (torso)", "steering + integration", "fence + CCD",
                                               "floor contact", "walls: feelers + contact", "hard-body projection" };

double tscPerMs() {   // invariant TSC rate against steady_clock
    const auto t0 = bench::Clock::now();
    const uint64_t c0 = __rdtsc();
    while (bench::msSince(t0) < 250.0) {}
    return double(__rdtsc() - c0) / bench::msSince(t0);
}

struct Result {
    double cycles[prof::PHASE_COUNT] = {};
    double counts[prof::COUNT_COUNT] = {};
    double busyMax = 0, busyMean = 0;   // per-thread summed phase cycles, per step
    double physicsWallMs = 0, totalWallMs = 0, hashMs = 0, sortMs = 0, cellsMs = 0, choiceMs = 0, predictMs = 0, projectMs = 0, finalMs = 0;
};

Result profile(const Venue& venue, const std::vector<float>& sdf, const std::vector<GpuBoid>& snap, int threads, CpuCrowdSim::Schedule sched,
               CpuCrowdSim::Schedule projSched, bool parChoice, int steps, bool skipSep) {
    CpuCrowdSim cpu(venue, defaultModelOptions(venue), venue.seated() ? std::vector<float>() : sdf, threads, CpuCrowdSim::SortMode::Counting);
    cpu.setSchedule(sched);
    cpu.setProjectionSchedule(projSched);
    cpu.setParallelChoice(parChoice);
    prof::skipSeparation = skipSep;
    cpu.setState(snap);
    for (int i = 0; i < 2; ++i) { cpu.restoreAgentState(snap); cpu.step(); }   // warm-up
    prof::reset();
    std::vector<double> phys, total, hash, sort, cells, choice, predict, project, fin;
    for (int i = 0; i < steps; ++i) {
        cpu.restoreAgentState(snap);
        cpu.step();
        const CpuCrowdSim::StageTimesMs& t = cpu.timings();
        phys.push_back(t.physics); total.push_back(t.total); hash.push_back(t.hash); sort.push_back(t.sort); cells.push_back(t.cells);
        choice.push_back(t.choice); predict.push_back(t.predict); project.push_back(t.project); fin.push_back(t.final);
    }
    prof::skipSeparation = false;
    Result r;
    std::vector<double> busy;
    for (int t = 0; t < prof::MAX_THREADS; ++t) {
        double b = 0;
        for (int p = 0; p < prof::PHASE_COUNT; ++p) { r.cycles[p] += double(prof::slots[t].cycles[p]) / steps; b += double(prof::slots[t].cycles[p]); }
        for (int c = 0; c < prof::COUNT_COUNT; ++c) r.counts[c] += double(prof::slots[t].counts[c]) / steps;
        if (t < threads) busy.push_back(b / steps);
    }
    r.busyMax = *std::max_element(busy.begin(), busy.end());
    r.busyMean = std::accumulate(busy.begin(), busy.end(), 0.0) / double(busy.size());
    r.physicsWallMs = bench::median(phys);
    r.totalWallMs = bench::median(total);
    r.hashMs = bench::median(hash); r.sortMs = bench::median(sort); r.cellsMs = bench::median(cells);
    r.choiceMs = bench::median(choice); r.predictMs = bench::median(predict); r.projectMs = bench::median(project); r.finalMs = bench::median(fin);
    return r;
}

CpuCrowdSim::Schedule scheduleByName(const std::string& name) {
    for (CpuCrowdSim::Schedule s : { CpuCrowdSim::Schedule::Static, CpuCrowdSim::Schedule::Dynamic64, CpuCrowdSim::Schedule::Dynamic256,
                                     CpuCrowdSim::Schedule::Dynamic1024, CpuCrowdSim::Schedule::Guided })
        if (name == CpuCrowdSim::scheduleName(s)) return s;
    throw std::runtime_error("unknown schedule " + name);
}

} // namespace

int main(int argc, char** argv) {
    try {
        const bench::Args a(argc, argv, 1);
        if (a.positional.empty())
            throw std::runtime_error("usage: cpu_profile <snapshotDir> [--venue terrace|S|M|L] [--n N] [--state S] [--threads list] [--steps K] [--schedule s] [--proj-schedule s]");
        const std::string qos = bench::optOutOfPowerThrottling();   // as benchmark_crowd (E-core placement otherwise)
        const fs::path dir = a.positional[0];
        const std::string venueName = a.get("venue", "terrace");
        const Venue& venue = venueByName(venueName);
        const int n = venue.seated() ? bench::venueBufferN(venueName) : a.getInt("n", 65536);
        const std::string state = a.get("state", "congested");
        const int steps = a.getInt("steps", 5);
        const CpuCrowdSim::Schedule sched = scheduleByName(a.get("schedule", "static"));
        const CpuCrowdSim::Schedule projSched = scheduleByName(a.get("proj-schedule", a.get("schedule", "static")));
        const bool parChoice = a.getInt("parallel-choice", CpuCrowdSim::TUNED_PARALLEL_CHOICE ? 1 : 0) != 0;
        const std::vector<float> sdf = venue.seated() ? std::vector<float>() : loadSDFVolume(resolveAsset("stadium.sdf"));
        const std::vector<GpuBoid> snap = venue.seated() ? bench::loadWorkloadSnapshot(dir, venueName, n, state) : bench::loadSnapshot(dir, state, n);
        const double tsc = tscPerMs();
        long active = bench::countActive(snap);
        std::printf("cpu_profile: commit %s (dirty %s) | %s | %s | %s | venue %s, N = %d %s (%ld active) | schedule %s, projection %s, exit choice %s | %d steps | TSC %.0f MHz\n",
                    bench::gitCommit().c_str(), bench::gitDirty().c_str(), SWARM_BUILD_TYPE, bench::cpuBrand().c_str(), qos.c_str(), venueName.c_str(), n,
                    state.c_str(), active, CpuCrowdSim::scheduleName(sched), CpuCrowdSim::scheduleName(projSched), parChoice ? "parallel" : "sequential", steps, tsc / 1000.0);
        if (!venue.seated()) {
            const bench::Occupancy occ = bench::occupancy(snap);
            std::printf("  terrace grid: %d occupied cells, %.1f agents/cell\n", occ.occupiedCells, occ.meanPerCell);
        }
        for (int threads : bench::parseIntList(a.get("threads", "1,20"))) {
            const Result full = profile(venue, sdf, snap, threads, sched, projSched, parChoice, steps, false);
            const Result noSep = profile(venue, sdf, snap, threads, sched, projSched, parChoice, steps, true);
            double sum = 0;
            for (double c : full.cycles) sum += c;
            std::printf("\n%d thread(s): wall per step (median): hash %.3f, sort %.3f, cells %.3f, physics %.2f (exit choice %.3f, predict %.2f, projection %.2f, "
                        "final %.2f), total %.2f ms\n", threads, full.hashMs, full.sortMs, full.cellsMs, full.physicsWallMs, full.choiceMs, full.predictMs,
                        full.projectMs, full.finalMs, full.totalWallMs);
            std::printf("  stage shares of the step: hash %.1f%%, sort %.1f%%, cells %.1f%%, exit choice %.1f%%, predict %.1f%%, projection %.1f%%, final %.1f%%\n",
                        100 * full.hashMs / full.totalWallMs, 100 * full.sortMs / full.totalWallMs, 100 * full.cellsMs / full.totalWallMs,
                        100 * full.choiceMs / full.totalWallMs, 100 * full.predictMs / full.totalWallMs, 100 * full.projectMs / full.totalWallMs,
                        100 * full.finalMs / full.totalWallMs);
            std::printf("  physics CPU time (sum over threads) per step: %.2f ms; per-thread busy max/mean %.3f (wall/busy-max %.3f)\n",
                        sum / tsc, full.busyMax / full.busyMean, full.physicsWallMs / (full.busyMax / tsc));
            std::printf("  %-38s %10s %7s\n", "phase (per-agent marks; the exit choice outside)", "CPU ms", "share");
            for (int p = 0; p < prof::PHASE_COUNT; ++p) {
                std::printf("  %-38s %10.2f %6.1f%%\n", PHASE_NAMES[p], full.cycles[p] / tsc, 100.0 * full.cycles[p] / sum);
                if (p == prof::NEIGHBOUR) {
                    const double sep = full.cycles[p] - noSep.cycles[p];
                    std::printf("    %-36s %10.2f %6.1f%%   (ablation: neighbour phase with - without separationForce)\n",
                                "of which separation", sep / tsc, 100.0 * sep / sum);
                    std::printf("    %-36s %10.2f %6.1f%%\n", "of which gather + distance + headway", noSep.cycles[p] / tsc,
                                100.0 * noSep.cycles[p] / sum);
                }
            }
            const double agents = full.counts[prof::AGENTS];
            std::printf("  per agent slot: %.0f candidates (3x3 ring, incl. self), %.1f perception neighbours, %.1f separation pairs,\n"
                        "                  %.1f map() samples, %.1f mapExactGrad; %.2f ns per candidate (neighbour phase, CPU time)\n",
                        full.counts[prof::CANDIDATES] / agents, full.counts[prof::NEIGHBOURS] / agents, full.counts[prof::SEP_PAIRS] / agents,
                        full.counts[prof::MAP_CALLS] / agents, full.counts[prof::EXACT_GRAD_CALLS] / agents,
                        1e6 * (full.cycles[prof::NEIGHBOUR] / tsc) / full.counts[prof::CANDIDATES]);
        }
        return 0;
    } catch (const std::exception& e) {
        std::fprintf(stderr, "FATAL: %s\n", e.what());
        return 1;
    }
}
