// benchmark_crowd: one crowd step on the GPU (CrowdSim) vs the CPU reference
// (CpuCrowdSim, SortMode::Counting, tuned configuration) at 1 thread and at max threads.
//
//   benchmark_crowd run [--quick] [--plan] [--rounds 5] [--clock-note "..."] [--out out/results]
//                       [--snapshots out/bench/snapshots] [--cpu-schedule dynamic64] [--note "..."]
//   benchmark_crowd scaling [--n 65536] [--states spawn,congested] [--threads 1,2,4,6,8,12,14,16,20]
//                           [--rounds 3] [--steps 20] [--clock-note "..."] [--out out/results] [--cpu-schedule ...]
//   benchmark_crowd thesis [--quick] [--plan] [--rounds 5] [--clock-note "..."] [--out out/results/benchmarks/thesis]
//                           [--snapshots out/bench/snapshots_thesis] [--only venue_S,terrace_4096,...] [--no-venues] [--no-terrace]
//              the thesis benchmark (namespace thesis below: the venues S, M, L at 100% load and the terrace sweep, per-pass GPU times with
//              the physics stage split, real-time factors, venue golden pins in the self-check); benchmark_crowd scaling --venue M
//              [--states congested] ...: CPU thread scaling on a venue's thesis snapshot.
// --cpu-schedule selects the physics schedule of the CPU rows (default: CpuCrowdSim::TUNED_SCHEDULE;
// 'static' is the baseline). --note adds a paragraph under the summary's title (e.g. which earlier run
// this one supersedes, and why).
//
// Workloads (run):
//   snapshot mode   'spawn' and 'congested' (GPU state after 250 steps, bench_common.hpp): every timed
//                   step starts from the identical snapshot on both sides; restoring it is outside the
//                   timed region
//   trajectory mode continuous stepping from spawn: 200 warm-up steps, then 300 measured; the active
//                   agent count is recorded per step (evacuation shrinks the work)
// GPU timing: GL_TIMESTAMP per pass (hash, sort, cells, physics) into CrowdSim's query ring, read back
// only after the measured loop; plus wall clock per step including dispatch (glFinish once at the
// end of a batch). CPU timing: steady_clock per stage (CpuCrowdSim::timings).
// Drift control: R rounds, each running every (N, state, impl) in an order rotated between rounds,
// each starting with a fixed reference probe (GPU, N = 4096, spawn, 300 steps) whose coefficient of
// variation across rounds is the measurement-stability figure.
// Self-check before measuring (the run aborts on failure): the golden hashes (test_gpu parity.golden_terrace)
// and CPU-vs-GPU single-step equivalence at N = 4096 congested (the criteria of test_gpu parity.grid and parity.one_step).
// Process QoS: the process opts out of Windows power throttling at start (bench::optOutOfPowerThrottling)
// and records the result in the run metadata.
#include "bench_common.hpp"
#include "../golden_state.hpp"

#include <swarm/assets.hpp>
#include <swarm/cpu_crowd_sim.hpp>
#include <swarm/sdf.hpp>
#include <swarm/venue.hpp>
#include <swarm/venue_capacity.hpp>

#include <omp.h>

#include <array>
#include <cstring>

namespace fs = std::filesystem;
using namespace swarm;
using bench::Args;
using bench::Clock;
using bench::Stats;

namespace {

// --- Configuration ---
constexpr CpuCrowdSim::SortMode CPU_SORT = CpuCrowdSim::SortMode::Counting;
constexpr int GPU_WARMUP_MIN_STEPS = 200;
constexpr double GPU_WARMUP_MIN_MS = 2000.0;
constexpr int CPU_WARMUP_STEPS = 20;
constexpr double CPU_WARMUP_CAP_MS = 2000.0;   // ... or fewer steps once this much sustained load ran
constexpr int CPU_WARMUP_MIN_STEPS = 2;
constexpr int TRAJ_WARMUP = 200, TRAJ_MEASURED = 300;
constexpr int PROBE_N = 4096, PROBE_STEPS = 300;
constexpr double DISK_CAPACITY_PER_CELL = 0.05 * 0.05 / (2.0 * 1.7320508 * double(BODY_RADIUS) * double(BODY_RADIUS));   // hexagonal packing of the hard bodies
constexpr int STRESS_N = 262144;

CpuCrowdSim::Schedule g_cpuSchedule = CpuCrowdSim::TUNED_SCHEDULE;

CpuCrowdSim::Schedule parseSchedule(const std::string& name) {
    for (CpuCrowdSim::Schedule s : { CpuCrowdSim::Schedule::Static, CpuCrowdSim::Schedule::Dynamic64, CpuCrowdSim::Schedule::Dynamic256,
                                     CpuCrowdSim::Schedule::Dynamic1024, CpuCrowdSim::Schedule::Guided })
        if (name == CpuCrowdSim::scheduleName(s)) return s;
    throw std::runtime_error("unknown schedule " + name);
}

struct Meta {
    std::string runId, timestamp, commit, commitFull, dirty, build, flags, clockNote, gpu, driver, cpu, schedule, note, qos;
    unsigned logicalCores = 0;
    int ompMaxThreads = 0;
};

struct Row {
    std::string impl, sortMode, schedule, state, label;
    int threads = 0, n = 0, round = 0, warmup = 0, measured = 0;
    double activeMean = 0, agentsPerCell = 0;
    Stats total;
    double hash = 0, sort = 0, cells = 0, physics = 0, wall = 0;
};

struct StepSample { long active; CrowdSim::PassTimesMs t; };   // trajectory, one per measured step

// The label column of every row: the venue's capacity label for N (within / above the design capacity, or
// physically impossible above the jam capacity), and the stress point
std::string label(int n) {
    return venue::label(n) + (n >= STRESS_N ? "; over-capacity stress point" : "");
}

// --- Output ---
class Writer {
public:
    Writer(const Meta& m, const fs::path& csvPath, const fs::path& trajPath) : m_(m) {
        csv_ = std::fopen(csvPath.string().c_str(), "w");
        if (!csv_) throw std::runtime_error("cannot write " + csvPath.string());
        // Column 3 is "<short>[-dirty]". Appended: git_commit (full SHA-1 of HEAD) and
        // git_dirty (1 / 0 / unknown), both determined at build time
        std::fprintf(csv_, "run_id,timestamp,git_describe,build,clock_note,gpu,driver,cpu,impl,sort_mode,threads,schedule,N,state,active_mean,"
                           "round,warmup_steps,measured_steps,median_ms,p5_ms,p95_ms,mean_ms,cv,hash_ms,sort_ms,cells_ms,physics_ms,"
                           "wall_ms_per_step,logical_cores,omp_max_threads,agents_per_cell,label,build_flags,git_commit,git_dirty\n");
        if (!trajPath.empty()) {
            traj_ = std::fopen(trajPath.string().c_str(), "w");
            if (!traj_) throw std::runtime_error("cannot write " + trajPath.string());
            std::fprintf(traj_, "run_id,round,impl,threads,N,step,active,total_ms,hash_ms,sort_ms,cells_ms,physics_ms,label,git_commit,git_dirty\n");
        }
    }
    ~Writer() { if (csv_) std::fclose(csv_); if (traj_) std::fclose(traj_); }

    void row(const Row& r) {
        using bench::csvField;
        std::fprintf(csv_, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%s,%d,%s,%.1f,%d,%d,%d,%.5f,%.5f,%.5f,%.5f,%.4f,%.5f,%.5f,%.5f,%.5f,%.5f,%u,%d,%.1f,%s,%s,%s,%s\n",
                     m_.runId.c_str(), m_.timestamp.c_str(), m_.commit.c_str(), m_.build.c_str(), csvField(m_.clockNote).c_str(),
                     csvField(m_.gpu).c_str(), csvField(m_.driver).c_str(), csvField(m_.cpu).c_str(), r.impl.c_str(), r.sortMode.c_str(),
                     r.threads, r.schedule.c_str(), r.n, r.state.c_str(), r.activeMean, r.round, r.warmup, r.measured, r.total.median,
                     r.total.p5, r.total.p95, r.total.mean, r.total.cv, r.hash, r.sort, r.cells, r.physics, r.wall, m_.logicalCores,
                     m_.ompMaxThreads, r.agentsPerCell, csvField(r.label).c_str(), csvField(m_.flags).c_str(), m_.commitFull.c_str(),
                     m_.dirty.c_str());
        std::fflush(csv_);
        rows_.push_back(r);
    }
    void trajectory(const Row& r, int firstStep, const std::vector<StepSample>& s) {
        if (!traj_) return;
        const std::string lab = bench::csvField(r.label);
        for (size_t i = 0; i < s.size(); ++i)
            std::fprintf(traj_, "%s,%d,%s,%d,%d,%d,%ld,%.5f,%.5f,%.5f,%.5f,%.5f,%s,%s,%s\n", m_.runId.c_str(), r.round, r.impl.c_str(), r.threads,
                         r.n, firstStep + int(i), s[i].active, s[i].t.total, s[i].t.hash, s[i].t.sort, s[i].t.cells, s[i].t.physics,
                         lab.c_str(), m_.commitFull.c_str(), m_.dirty.c_str());
        std::fflush(traj_);
    }
    const std::vector<Row>& rows() const { return rows_; }

private:
    const Meta& m_;
    std::FILE* csv_ = nullptr;
    std::FILE* traj_ = nullptr;
    std::vector<Row> rows_;
};

void printRow(const Row& r, Clock::time_point start) {
    std::printf("  r%d %-9s t=%2d N=%6d %-10s %4d+%-3d steps  median %10.4f ms (p5 %.4f p95 %.4f, cv %.3f)  wall %.4f  [%5.0f s]\n",
                r.round, r.impl.c_str(), r.threads, r.n, r.state.c_str(), r.warmup, r.measured, r.total.median, r.total.p5, r.total.p95,
                r.total.cv, r.wall, bench::msSince(start) / 1000.0);
    std::fflush(stdout);
}

// --- GPU ---
class GpuBench {
public:
    GpuBench(fs::path shaderDir, GLuint sdfTex) : shaderDir_(std::move(shaderDir)), sdf_(sdfTex) {}

    // Snapshot mode: restore the snapshot (GPU-side copy into both ping-pong halves), step; repeat
    Row snapshot(int n, const std::string& state, const std::vector<GpuBoid>& snap, int measured, double warmMinMs,
                 int warmMinSteps = GPU_WARMUP_MIN_STEPS) {
        CrowdSim sim(shaderDir_, n);
        Pristine p(snap);
        auto restore = [&] { p.copyTo(sim.boidBuffer(0)); p.copyTo(sim.boidBuffer(1)); };
        int warm = 0;
        const auto t0 = Clock::now();
        while (warm < warmMinSteps || bench::msSince(t0) < warmMinMs) {
            restore();
            sim.step(sdf_);
            if (++warm % 50 == 0) glFinish();
        }
        glFinish();
        sim.beginTimingRing(measured);
        const auto t1 = Clock::now();
        for (int i = 0; i < measured; ++i) { restore(); sim.step(sdf_); }
        glFinish();
        const double batchMs = bench::msSince(t1);
        const std::vector<CrowdSim::PassTimesMs> times = sim.readTimingRing();
        const auto t2 = Clock::now();   // the restores alone, to take them out of the wall figure
        for (int i = 0; i < measured; ++i) restore();
        glFinish();
        const double restoreMs = bench::msSince(t2);
        Row r = fromTimes(n, state, times);
        r.warmup = warm;
        r.activeMean = double(bench::countActive(snap));
        r.agentsPerCell = bench::occupancy(snap).meanPerCell;
        r.wall = (batchMs - restoreMs) / measured;
        return r;
    }

    // Trajectory mode: >= warmMinMs of sustained load on the spawn snapshot first, then from spawn
    // TRAJ_WARMUP steps and 'measured' timed steps. activeAfter[s] = active agents after step s + 1.
    Row trajectory(int n, const std::vector<GpuBoid>& spawn, int warmup, int measured, double warmMinMs, const std::vector<long>& activeAfter,
                   std::vector<StepSample>& samples) {
        CrowdSim sim(shaderDir_, n);
        Pristine p(spawn);
        auto restore = [&] { p.copyTo(sim.boidBuffer(0)); p.copyTo(sim.boidBuffer(1)); };
        const auto t0 = Clock::now();
        for (int i = 0; bench::msSince(t0) < warmMinMs; ++i) {
            restore();
            sim.step(sdf_);
            if (i % 50 == 49) glFinish();
        }
        restore();
        for (int i = 0; i < warmup; ++i) sim.step(sdf_);
        glFinish();
        sim.beginTimingRing(measured);
        const auto t1 = Clock::now();
        for (int i = 0; i < measured; ++i) sim.step(sdf_);
        glFinish();
        const double batchMs = bench::msSince(t1);
        const std::vector<CrowdSim::PassTimesMs> times = sim.readTimingRing();
        Row r = fromTimes(n, "trajectory", times);
        r.warmup = warmup;
        r.wall = batchMs / measured;
        samples.clear();
        double activeSum = 0;
        for (int i = 0; i < measured; ++i) {
            const long a = activeAfter[size_t(warmup + i)];
            samples.push_back({ a, times[size_t(i)] });
            activeSum += double(a);
        }
        r.activeMean = activeSum / measured;
        r.agentsPerCell = bench::occupancy(spawn).meanPerCell;
        return r;
    }

    // Active agents after each of 'steps' steps from 'start' (untimed replay with readbacks; the
    // GPU pipeline is deterministic, so every timed trajectory follows the same counts)
    std::vector<long> activeCounts(int n, const std::vector<GpuBoid>& start, int steps) {
        CrowdSim sim(shaderDir_, n);
        sim.upload(start);
        std::vector<long> out;
        for (int i = 0; i < steps; ++i) {
            sim.step(sdf_);
            out.push_back(bench::countActive(bench::readBuffer<GpuBoid>(sim.currentStateBuffer(), size_t(n))));
        }
        return out;
    }

    std::vector<GpuBoid> run(int n, const std::vector<GpuBoid>& start, int steps) {
        CrowdSim sim(shaderDir_, n);
        sim.upload(start);
        for (int i = 0; i < steps; ++i) sim.step(sdf_);
        return bench::readBuffer<GpuBoid>(sim.currentStateBuffer(), size_t(n));
    }

    struct OneStep { std::vector<GpuBoid> out; std::vector<GpuGridInfo> grid; std::vector<GpuCellData> cells; };
    OneStep oneStep(const std::vector<GpuBoid>& in) {
        const int n = int(in.size());
        CrowdSim sim(shaderDir_, n);
        sim.upload(in);
        sim.step(sdf_);
        return { bench::readBuffer<GpuBoid>(sim.currentStateBuffer(), size_t(n)), bench::readBuffer<GpuGridInfo>(sim.gridBuffer(), size_t(n)),
                 bench::readBuffer<GpuCellData>(sim.cellBuffer(), size_t(GRID_RES) * GRID_RES) };
    }

private:
    // The snapshot resident on the GPU, copied into the ping-pong buffers without a CPU transfer
    struct Pristine {
        GLuint buf = 0;
        GLsizeiptr bytes = 0;
        explicit Pristine(const std::vector<GpuBoid>& s) : bytes(GLsizeiptr(s.size() * sizeof(GpuBoid))) {
            glGenBuffers(1, &buf);
            glBindBuffer(GL_COPY_READ_BUFFER, buf);
            glBufferData(GL_COPY_READ_BUFFER, bytes, s.data(), GL_STATIC_DRAW);
        }
        ~Pristine() { glDeleteBuffers(1, &buf); }
        void copyTo(GLuint dst) const {
            glMemoryBarrier(GL_BUFFER_UPDATE_BARRIER_BIT);   // after the previous step's shader writes
            glBindBuffer(GL_COPY_READ_BUFFER, buf);
            glBindBuffer(GL_COPY_WRITE_BUFFER, dst);
            glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, bytes);
        }
    };

    static Row fromTimes(int n, const std::string& state, const std::vector<CrowdSim::PassTimesMs>& times) {
        std::vector<double> total, hash, sort, cells, physics;
        for (const CrowdSim::PassTimesMs& t : times) {
            total.push_back(t.total); hash.push_back(t.hash); sort.push_back(t.sort); cells.push_back(t.cells); physics.push_back(t.physics);
        }
        Row r;
        r.impl = "gpu";
        r.sortMode = "bitonic";
        r.schedule = "-";
        r.n = n;
        r.state = state;
        r.measured = int(times.size());
        r.total = bench::stats(total);
        r.hash = bench::median(hash); r.sort = bench::median(sort); r.cells = bench::median(cells); r.physics = bench::median(physics);
        r.label = label(n);
        return r;
    }

    fs::path shaderDir_;
    GLuint sdf_;
};

// --- CPU ---
struct CpuTimes { std::vector<double> total, hash, sort, cells, physics; };

void addTimes(CpuTimes& c, const CpuCrowdSim::StageTimesMs& t) {
    c.total.push_back(t.total); c.hash.push_back(t.hash); c.sort.push_back(t.sort); c.cells.push_back(t.cells); c.physics.push_back(t.physics);
}

Row cpuRow(int n, int threads, const std::string& state, const CpuTimes& c) {
    Row r;
    r.impl = "cpu";
    r.sortMode = "counting";
    r.schedule = CpuCrowdSim::scheduleName(g_cpuSchedule);
    r.threads = threads;
    r.n = n;
    r.state = state;
    r.measured = int(c.total.size());
    r.total = bench::stats(c.total);
    r.hash = bench::median(c.hash); r.sort = bench::median(c.sort); r.cells = bench::median(c.cells); r.physics = bench::median(c.physics);
    r.wall = r.total.mean;   // synchronous: a step's wall time is its stage sum
    r.label = label(n);
    return r;
}

// CPU warm-up: CPU_WARMUP_STEPS steps, or fewer (at least CPU_WARMUP_MIN_STEPS) once CPU_WARMUP_CAP_MS
// of sustained load ran
template <class StepFn>
int cpuWarmup(StepFn step) {
    const auto t0 = Clock::now();
    int w = 0;
    while (w < CPU_WARMUP_STEPS && (w < CPU_WARMUP_MIN_STEPS || bench::msSince(t0) < CPU_WARMUP_CAP_MS)) { step(); ++w; }
    return w;
}

Row cpuSnapshot(const std::vector<float>& sdf, int n, int threads, const std::string& state, const std::vector<GpuBoid>& snap, int measured) {
    CpuCrowdSim cpu(sdf, threads, CPU_SORT);
    cpu.setSchedule(g_cpuSchedule);
    const int warm = cpuWarmup([&] { cpu.setState(snap); cpu.step(); });
    CpuTimes c;
    for (int i = 0; i < measured; ++i) {
        cpu.setState(snap);
        cpu.step();
        addTimes(c, cpu.timings());
    }
    Row r = cpuRow(n, cpu.numThreads(), state, c);
    r.warmup = warm;
    r.activeMean = double(bench::countActive(snap));
    r.agentsPerCell = bench::occupancy(snap).meanPerCell;
    return r;
}

// The warm-up steps of a 1-thread trajectory run at max threads when 'fastWarmup': the state is
// bit-identical for any thread count (test_gpu parity.thread_invariance, cpu_tune golden), so only the measured
// steps need the measured thread count
Row cpuTrajectory(const std::vector<float>& sdf, int n, int threads, const std::vector<GpuBoid>& spawn, int warmup, int measured,
                  bool fastWarmup, std::vector<StepSample>& samples) {
    CpuCrowdSim cpu(sdf, fastWarmup ? 0 : threads, CPU_SORT);
    cpu.setSchedule(g_cpuSchedule);
    cpu.setState(spawn);
    for (int i = 0; i < warmup; ++i) cpu.step();
    cpu.setNumThreads(threads);
    CpuTimes c;
    samples.clear();
    double activeSum = 0;
    for (int i = 0; i < measured; ++i) {
        cpu.step();
        const CpuCrowdSim::StageTimesMs& t = cpu.timings();
        addTimes(c, t);
        const long a = bench::countActive(cpu.state());
        samples.push_back({ a, { t.hash, t.sort, t.cells, t.physics, t.total } });
        activeSum += double(a);
    }
    Row r = cpuRow(n, threads, "trajectory", c);
    r.warmup = warmup;
    r.activeMean = activeSum / measured;
    r.agentsPerCell = bench::occupancy(spawn).meanPerCell;
    return r;
}

// --- Self-check ---
bool selfCheck(GpuBench& gpu, const std::vector<float>& sdf, const fs::path& snapDir, const Meta& meta, std::string& report) {
    bool ok = true;
    char line[512];
    auto log = [&](const std::string& s) { std::printf("%s\n", s.c_str()); report += s + "\n"; };
    log("self-check (abort on failure):");
    // 1. Golden hashes (test_gpu parity.golden_terrace)
    const std::vector<GpuBoid> spawn4096 = spawnBleacherCrowd(4096), spawn65536 = spawnBleacherCrowd(65536);
    const bool sameDriver = meta.gpu + " | " + meta.driver == golden::GOLDEN_DRIVER;
    struct Check { const golden::Golden& g; uint64_t h; bool gpu; };
    std::vector<Check> checks;
    checks.push_back({ golden::GOLDEN[golden::GOLDEN_GPU_4096], golden::stateHash(gpu.run(4096, spawn4096, golden::GOLDEN_STEPS)), true });
    checks.push_back({ golden::GOLDEN[golden::GOLDEN_GPU_65536], golden::stateHash(gpu.run(65536, spawn65536, golden::GOLDEN_STEPS)), true });
    for (int threads : { 0, 1 }) {
        for (CpuCrowdSim::SortMode mode : { CpuCrowdSim::SortMode::Counting, CpuCrowdSim::SortMode::GpuBitonic }) {
            if (threads == 1 && mode == CpuCrowdSim::SortMode::GpuBitonic) continue;
            CpuCrowdSim cpu(sdf, threads, mode);
            cpu.setSchedule(g_cpuSchedule);
            cpu.setState(spawn4096);
            for (int i = 0; i < golden::GOLDEN_STEPS; ++i) cpu.step();
            const golden::Golden& g = golden::GOLDEN[mode == CpuCrowdSim::SortMode::Counting ? golden::GOLDEN_CPU_COUNTING_4096 : golden::GOLDEN_CPU_BITONIC_4096];
            checks.push_back({ g, golden::stateHash(cpu.state()), false });
            std::snprintf(line, sizeof line, "  (%s at %d thread(s), schedule %s)", g.name, cpu.numThreads(), CpuCrowdSim::scheduleName(cpu.schedule()));
            log(line);
        }
    }
    for (const Check& c : checks) {
        const bool match = c.h == c.g.hash;
        const bool enforced = !c.gpu || sameDriver;
        std::snprintf(line, sizeof line, "  golden %-22s %016llx pinned %016llx: %s", c.g.name, (unsigned long long)c.h,
                      (unsigned long long)c.g.hash, match ? "match" : enforced ? "MISMATCH" : "differs (different driver: not enforced)");
        log(line);
        ok &= match || !enforced;
    }
    // 2. Single-step equivalence at N = 4096 congested: grid exact, |dpos| > 2e-4 for < 0.5% of active
    const std::vector<GpuBoid> in = bench::loadSnapshot(snapDir, "congested", 4096);
    const GpuBench::OneStep g = gpu.oneStep(in);
    CpuCrowdSim cpuMax(sdf, 0, CPU_SORT), cpuOne(sdf, 1, CPU_SORT);
    cpuMax.setSchedule(g_cpuSchedule);
    cpuOne.setSchedule(g_cpuSchedule);
    cpuMax.setState(in); cpuMax.step();
    cpuOne.setState(in); cpuOne.step();
    long gridDiff = 0, cellDiff = 0, outliers = 0, active = 0;
    for (size_t s = 0; s < in.size(); ++s) gridDiff += cpuMax.grid()[s].gridID != g.grid[s].gridID;
    for (size_t k = 0; k < g.cells.size(); ++k)
        cellDiff += cpuMax.cells()[k].startIndex != g.cells[k].startIndex || cpuMax.cells()[k].agentCount != g.cells[k].agentCount;
    for (size_t i = 0; i < in.size(); ++i) {
        if (in[i].position.w == 0.0f) continue;
        ++active;
        outliers += glm::length(glm::vec3(cpuMax.state()[i].position) - glm::vec3(g.out[i].position)) > 2e-4f;
    }
    const bool threadsSame = std::memcmp(cpuMax.state().data(), cpuOne.state().data(), in.size() * sizeof(GpuBoid)) == 0;
    const bool equivOk = gridDiff == 0 && cellDiff == 0 && outliers * 1000 < active * 5 && threadsSame;
    std::snprintf(line, sizeof line,
                  "  equivalence N = 4096 congested, one step, CPU counting (%s): gridID slots != GPU %ld, cells != GPU %ld, "
                  "|dpos| > 2e-4: %ld of %ld active (%.3f%%, limit 0.5%%), 1 thread == %d threads: %s -> %s",
                  CpuCrowdSim::scheduleName(cpuMax.schedule()), gridDiff, cellDiff, outliers, active, 100.0 * double(outliers) / double(active),
                  cpuMax.numThreads(), threadsSame ? "bit-identical" : "DIFFERENT", equivOk ? "pass" : "FAIL");
    log(line);
    ok &= equivOk;
    log(ok ? "self-check passed" : "SELF-CHECK FAILED: run aborted");
    return ok;
}

// --- Plan ---
struct Cell {
    std::string impl;   // gpu | cpu
    int threads = 0;    // cpu only
    int n = 0;
    std::string state;  // spawn | congested | trajectory
    int measured = 0;
    std::vector<int> rounds;   // rounds that run this cell
};

struct RunConfig {
    bool quick = false;
    int rounds = 5;
    std::vector<int> ns, trajNs;
    double gpuWarmMs = GPU_WARMUP_MIN_MS;
    int trajWarmup = TRAJ_WARMUP, trajMeasured = TRAJ_MEASURED, probeSteps = PROBE_STEPS;
};

std::vector<int> allRounds(int r) { std::vector<int> v(static_cast<size_t>(r)); std::iota(v.begin(), v.end(), 0); return v; }

// Reduced rounds for the 1-thread CPU at N >= 65536, spread over the run (5 rounds: 3 -> {0, 2, 4}, 2 -> {1, 3})
std::vector<int> reducedRounds(int r, int k) {
    if (r <= k) return allRounds(r);
    std::vector<int> v;
    for (int i = 0; i < k; ++i) v.push_back(int((2 * i + 1) * r / (2 * k)));
    return v;
}

std::vector<Cell> makePlan(const RunConfig& cfg, int maxThreads) {
    std::vector<Cell> plan;
    const std::vector<int> all = allRounds(cfg.rounds);
    for (int n : cfg.ns) {
        for (const char* state : { "spawn", "congested" }) {
            if (cfg.quick) {
                plan.push_back({ "gpu", 0, n, state, 50, all });
                plan.push_back({ "cpu", maxThreads, n, state, 20, all });
                plan.push_back({ "cpu", 1, n, state, 10, all });
                continue;
            }
            plan.push_back({ "gpu", 0, n, state, n >= STRESS_N ? 100 : 300, all });
            plan.push_back({ "cpu", maxThreads, n, state, n >= STRESS_N ? 20 : 100, all });
            // 1 thread at N >= 65536 (0.6-12 s per step): fewer measured steps and rounds (spec minimum 10 / 2)
            if (n < 65536) plan.push_back({ "cpu", 1, n, state, 100, all });
            else if (n < STRESS_N) plan.push_back({ "cpu", 1, n, state, 20, reducedRounds(cfg.rounds, 3) });
            else plan.push_back({ "cpu", 1, n, state, 10, reducedRounds(cfg.rounds, 2) });
        }
    }
    for (int n : cfg.trajNs) {
        plan.push_back({ "gpu", 0, n, "trajectory", cfg.trajMeasured, all });
        plan.push_back({ "cpu", maxThreads, n, "trajectory", cfg.trajMeasured, all });
        if (n < 65536 || cfg.quick) plan.push_back({ "cpu", 1, n, "trajectory", cfg.trajMeasured, all });
        else plan.push_back({ "cpu", 1, n, "trajectory", 60, reducedRounds(cfg.rounds, 3) });
    }
    return plan;
}

std::string cellKey(const Cell& c) { return c.impl + (c.impl == "cpu" ? "-" + std::to_string(c.threads) : "") + " N=" + std::to_string(c.n) + " " + c.state; }

// Seconds per step for each (impl, threads, n, state) from one short timed pass, for the estimate
double estimateSeconds(const std::vector<Cell>& plan, const RunConfig& cfg, GpuBench& gpu, const std::vector<float>& sdf, const fs::path& snapDir,
                       int maxThreads, std::string& report) {
    std::map<std::string, double> perStep;   // ms per step
    for (int n : cfg.ns) {
        for (const char* state : { "spawn", "congested" }) {
            const std::vector<GpuBoid> snap = bench::loadSnapshot(snapDir, state, n);
            perStep["gpu " + std::to_string(n) + state] = gpu.snapshot(n, state, snap, 10, 0.0, 5).total.median;
            CpuCrowdSim cpu(sdf, maxThreads, CPU_SORT);
            cpu.setSchedule(g_cpuSchedule);
            cpu.setState(snap); cpu.step();
            cpu.setState(snap); cpu.step();
            const double t20 = cpu.timings().total;
            perStep["cpu-" + std::to_string(maxThreads) + " " + std::to_string(n) + state] = t20;
            double t1;
            if (n <= 65536) {
                CpuCrowdSim one(sdf, 1, CPU_SORT);
                one.setState(snap); one.step();
                t1 = one.timings().total;
            } else {   // extrapolated with the 1-thread / max-thread ratio at 65536
                t1 = t20 * perStep["cpu-1 65536" + std::string(state)] / perStep["cpu-" + std::to_string(maxThreads) + " 65536" + state];
            }
            perStep["cpu-1 " + std::to_string(n) + state] = t1;
        }
    }
    double totalS = 0;
    char line[256];
    report += "time estimate (s per cell over its rounds):\n";
    for (const Cell& c : plan) {
        const std::string st = c.state == "trajectory" ? "spawn" : c.state;
        const std::string key = (c.impl == "gpu" ? "gpu " : "cpu-" + std::to_string(c.threads) + " ") + std::to_string(c.n) + st;
        if (!perStep.count(key)) continue;
        const double ms = perStep[key];
        double s;
        if (c.impl == "gpu") {
            const double warm = std::max(GPU_WARMUP_MIN_STEPS * ms, cfg.gpuWarmMs);
            s = c.state == "trajectory" ? (cfg.gpuWarmMs + (cfg.trajWarmup + c.measured) * ms) : (warm + c.measured * ms * 1.05);
        } else if (c.state == "trajectory") {
            const double warmMs = (c.threads == 1 && c.n >= 65536) ? cfg.trajWarmup * perStep["cpu-" + std::to_string(maxThreads) + " " + std::to_string(c.n) + "spawn"]
                                                                    : cfg.trajWarmup * ms;
            s = warmMs + c.measured * ms;
        } else {
            const int warm = std::max(CPU_WARMUP_MIN_STEPS, std::min(CPU_WARMUP_STEPS, int(std::ceil(CPU_WARMUP_CAP_MS / ms))));
            s = (warm + c.measured) * ms;
        }
        s = s * double(c.rounds.size()) / 1000.0;
        totalS += s;
        std::snprintf(line, sizeof line, "  %-32s %8.2f ms/step x %3d steps x %zu rounds: %7.1f s\n", cellKey(c).c_str(), ms, c.measured, c.rounds.size(), s);
        report += line;
    }
    const double probeS = cfg.rounds * (cfg.gpuWarmMs + cfg.probeSteps * perStep["gpu 4096spawn"]) / 1000.0;
    totalS += probeS;
    std::snprintf(line, sizeof line, "  probes: %.1f s\n  TOTAL estimate: %.1f min\n", probeS, totalS / 60.0);
    report += line;
    return totalS;
}

// --- Summary ---
struct Agg { double med = 0, lo = 0, hi = 0; int rounds = 0; double hash = 0, sort = 0, cells = 0, physics = 0, wall = 0, active = 0; int measured = 0, warmup = 0; };

Agg aggregate(const std::vector<Row>& rows) {
    Agg a;
    if (rows.empty()) return a;
    std::vector<double> m, h, s, c, p, w, act;
    for (const Row& r : rows) {
        m.push_back(r.total.median); h.push_back(r.hash); s.push_back(r.sort); c.push_back(r.cells); p.push_back(r.physics); w.push_back(r.wall);
        act.push_back(r.activeMean);
    }
    a.med = bench::median(m);
    a.lo = *std::min_element(m.begin(), m.end());
    a.hi = *std::max_element(m.begin(), m.end());
    a.rounds = int(rows.size());
    a.hash = bench::median(h); a.sort = bench::median(s); a.cells = bench::median(c); a.physics = bench::median(p); a.wall = bench::median(w);
    a.active = bench::median(act);
    a.measured = rows.front().measured;
    a.warmup = rows.front().warmup;
    return a;
}

std::string fmtMs(double v) {
    char b[32];
    if (v >= 100) std::snprintf(b, sizeof b, "%.1f", v);
    else if (v >= 10) std::snprintf(b, sizeof b, "%.2f", v);
    else if (v >= 1) std::snprintf(b, sizeof b, "%.3f", v);
    else std::snprintf(b, sizeof b, "%.4f", v);
    return b;
}

void writeSummary(const fs::path& path, const Meta& meta, const RunConfig& cfg, const std::vector<Row>& rows, int maxThreads,
                  const std::string& selfCheckReport, const std::string& estimateReport, const std::string& snapshotReport, double elapsedS) {
    std::ofstream md(path);
    auto select = [&](const std::string& impl, int threads, int n, const std::string& state) {
        std::vector<Row> out;
        for (const Row& r : rows)
            if (r.impl == impl && (impl != "cpu" || r.threads == threads) && r.n == n && r.state == state) out.push_back(r);
        return out;
    };
    auto cellStr = [](const Agg& a) {
        if (a.rounds == 0) return std::string("-");
        return fmtMs(a.med) + " (" + fmtMs(a.lo) + "-" + fmtMs(a.hi) + ")";
    };
    const std::string cpuMax = "CPU-" + std::to_string(maxThreads);
    md << "# benchmark_crowd " << meta.runId << (cfg.quick ? " (QUICK smoke run, not a measurement)" : "") << "\n\n";
    if (!meta.note.empty()) md << "> " << meta.note << "\n\n";
    md << "One simulation step (hash, sort, cells, physics) of the GPU pipeline (CrowdSim) and of the CPU reference (CpuCrowdSim, "
          "SortMode::Counting, schedule " << meta.schedule << ") at " << maxThreads << " threads and at 1 thread.\n\n";
    md << "**GPU times are GPU-execution times**: GL_TIMESTAMP queries around the four passes of each step, read back after the "
          "measured loop. They exclude the CPU-side dispatch. The end-to-end wall-clock time per step (dispatch included, glFinish "
          "once at the end of each batch) is in the `GPU wall` column. CPU times are steady_clock wall time per step (all stages).\n\n";
    md << "Cell format: median over rounds of the per-round median ms/step, with the min-max of the round medians in brackets. "
          "Speedups are ratios of those medians.\n\n";

    md << "## Headline: snapshot mode (every step from the identical snapshot)\n\n";
    md << "| N | state | GPU ms | " << cpuMax << " ms | CPU-1 ms | GPU vs " << cpuMax << " | " << cpuMax << " vs CPU-1 | GPU wall ms | note |\n";
    md << "|---:|---|---:|---:|---:|---:|---:|---:|---|\n";
    for (int n : cfg.ns)
        for (const char* state : { "spawn", "congested" }) {
            const Agg g = aggregate(select("gpu", 0, n, state)), c = aggregate(select("cpu", maxThreads, n, state)), c1 = aggregate(select("cpu", 1, n, state));
            char sp1[32] = "-", sp2[32] = "-";
            if (g.rounds && c.rounds) std::snprintf(sp1, sizeof sp1, "%.1fx", c.med / g.med);
            if (c.rounds && c1.rounds) std::snprintf(sp2, sizeof sp2, "%.1fx", c1.med / c.med);
            md << "| " << n << " | " << state << " | " << cellStr(g) << " | " << cellStr(c) << " | " << cellStr(c1) << " | " << sp1 << " | " << sp2
               << " | " << (g.rounds ? fmtMs(g.wall) : "-") << " | " << label(n) << " |\n";
        }
    md << "\nRounds and steps per cell (warm-up + measured):\n\n| N | state | GPU | " << cpuMax << " | CPU-1 |\n|---:|---|---|---|---|\n";
    for (int n : cfg.ns)
        for (const char* state : { "spawn", "congested" }) {
            auto rs = [](const Agg& a) {
                return a.rounds ? std::to_string(a.rounds) + " rounds, " + std::to_string(a.warmup) + "+" + std::to_string(a.measured) : std::string("-");
            };
            md << "| " << n << " | " << state << " | " << rs(aggregate(select("gpu", 0, n, state))) << " | "
               << rs(aggregate(select("cpu", maxThreads, n, state))) << " | " << rs(aggregate(select("cpu", 1, n, state))) << " |\n";
        }

    md << "\n## GPU per-pass breakdown (snapshot mode, GPU-execution ms, median over rounds)\n\n";
    md << "| N | state | hash | sort | cells | physics | total | physics share | wall/step |\n|---:|---|---:|---:|---:|---:|---:|---:|---:|\n";
    for (int n : cfg.ns)
        for (const char* state : { "spawn", "congested" }) {
            const Agg g = aggregate(select("gpu", 0, n, state));
            if (!g.rounds) continue;
            char share[16];
            std::snprintf(share, sizeof share, "%.0f%%", 100.0 * g.physics / g.med);
            md << "| " << n << " | " << state << " | " << fmtMs(g.hash) << " | " << fmtMs(g.sort) << " | " << fmtMs(g.cells) << " | " << fmtMs(g.physics)
               << " | " << fmtMs(g.med) << " | " << share << " | " << fmtMs(g.wall) << " |\n";
        }

    if (!cfg.trajNs.empty()) {
        md << "\n## Trajectory mode (from spawn: " << cfg.trajWarmup << " warm-up steps, then the measured steps)\n\n";
        md << "| N | GPU ms | " << cpuMax << " ms | CPU-1 ms | GPU vs " << cpuMax << " | active (mean, GPU / CPU) | GPU wall ms |\n|---:|---:|---:|---:|---:|---|---:|\n";
        for (int n : cfg.trajNs) {
            const Agg g = aggregate(select("gpu", 0, n, "trajectory")), c = aggregate(select("cpu", maxThreads, n, "trajectory")),
                      c1 = aggregate(select("cpu", 1, n, "trajectory"));
            char sp[32] = "-", act[64];
            if (g.rounds && c.rounds) std::snprintf(sp, sizeof sp, "%.1fx", c.med / g.med);
            std::snprintf(act, sizeof act, "%.0f / %.0f", g.active, c.active);
            md << "| " << n << " | " << cellStr(g) << " | " << cellStr(c) << " | " << cellStr(c1) << " | " << sp << " | " << act << " | "
               << (g.rounds ? fmtMs(g.wall) : "-") << " |\n";
        }
        md << "\nMeasured steps: GPU and " << cpuMax << " " << cfg.trajMeasured << " (steps " << cfg.trajWarmup + 1 << "-" << cfg.trajWarmup + cfg.trajMeasured
           << "); CPU-1 at N >= 65536 a shorter window from step " << cfg.trajWarmup + 1 << " in fewer rounds (see the CSV), its warm-up steps run "
              "at max threads (bit-identical state for any thread count). Per-step data: `*_trajectory.csv`.\n";
    }

    md << "\n## Measurement stability: reference probe (GPU, N = " << PROBE_N << ", spawn snapshot, " << cfg.probeSteps << " steps, start of every round)\n\n";
    std::vector<double> probe;
    for (const Row& r : rows) if (r.impl == "gpu_probe") probe.push_back(r.total.median);
    if (!probe.empty()) {
        const Stats ps = bench::stats(probe);
        md << "| round | median ms |\n|---:|---:|\n";
        for (size_t i = 0; i < probe.size(); ++i) md << "| " << i << " | " << fmtMs(probe[i]) << " |\n";
        char b[160];
        std::snprintf(b, sizeof b, "\n**Probe coefficient of variation across rounds: %.2f%%** (mean %.4f ms, min %.4f, max %.4f)\n", 100.0 * ps.cv, ps.mean, ps.min, ps.max);
        md << b;
    }

    md << "\n## Workload\n\n" << snapshotReport;
    md << "\nDisk-packing reference: agents' hard bodies are disks of radius " << BODY_RADIUS << ", so one layer holds about " << int(DISK_CAPACITY_PER_CELL)
       << " agents per fully covered 0.05 x 0.05 cell (hexagonal packing). N = 1024 and 4096 spawn within it; 16384 and 65536 already "
          "spawn stacked (as in every earlier 65536-agent test); N = " << STRESS_N << " spawns validly (on a tread, in free space, no NaN) at "
          "about 50x the single-layer capacity and is reported as an **over-capacity stress point**.\n";

    md << "\n## Protocol\n\n";
    md << "- Rounds: " << cfg.rounds << ". Each round runs the probe first, then every (N, state, impl) cell in an order rotated between rounds.\n";
    md << "- GPU warm-up: >= " << GPU_WARMUP_MIN_STEPS << " steps and >= " << cfg.gpuWarmMs / 1000.0 << " s of sustained load per cell "
          "(trajectory: the load on the spawn snapshot, then " << cfg.trajWarmup << " trajectory steps). Snapshot restore: GPU-side copy from a "
          "resident buffer, outside the timestamps; the wall figure subtracts a restore-only batch.\n";
    md << "- CPU warm-up: " << CPU_WARMUP_STEPS << " steps, or fewer (>= " << CPU_WARMUP_MIN_STEPS << ") once " << CPU_WARMUP_CAP_MS / 1000.0
       << " s of sustained load ran (long steps). CPU-1 at N >= 65536: fewer measured steps and rounds (CSV columns).\n";
    md << "- Elapsed: " << std::lround(elapsedS / 60.0) << " min.\n\n";
    md << "```\n" << selfCheckReport << estimateReport << "```\n";

    md << "\n## Metadata\n\n";
    md << "| key | value |\n|---|---|\n";
    md << "| run_id | " << meta.runId << " |\n| timestamp | " << meta.timestamp << " |\n| git commit | " << meta.commitFull << " |\n";
    md << "| git dirty | " << meta.dirty << " (at build time) |\n";
    md << "| build | " << meta.build << " |\n| simulation core flags | `" << meta.flags << "` |\n| clock note | " << meta.clockNote << " |\n";
    md << "| GPU (GL_RENDERER) | " << meta.gpu << " |\n| driver (GL_VERSION) | " << meta.driver << " |\n| CPU | " << meta.cpu << " |\n";
    md << "| logical cores | " << meta.logicalCores << " |\n| OpenMP max threads | " << meta.ompMaxThreads << " |\n| CPU schedule | " << meta.schedule << " |\n";
    md << "| CPU sort mode | counting |\n| process QoS | " << meta.qos << " |\n";
}

std::string g_qos = "not set";

Meta makeMeta(const std::string& prefix, const std::string& clockNote) {
    Meta m;
    m.runId = prefix + "_" + bench::localTimestamp("%Y%m%d_%H%M");
    m.timestamp = bench::localTimestamp("%Y-%m-%dT%H:%M:%S");
    m.commit = bench::gitDescribe();   // build time (swarm_build_info)
    m.commitFull = bench::gitCommit();
    m.dirty = bench::gitDirty();
    m.build = SWARM_BUILD_TYPE;
    m.flags = SWARM_CORE_FLAGS;
    m.clockNote = clockNote;
    m.qos = g_qos;
    m.gpu = bench::glRenderer();
    m.driver = bench::glDriver();
    m.cpu = bench::cpuBrand();
    m.schedule = std::string(CpuCrowdSim::scheduleName(g_cpuSchedule)) + " (physics), " + CpuCrowdSim::scheduleName(CpuCrowdSim::TUNED_PROJECTION_SCHEDULE) +
                 " (projection), static (hash), exit choice " + (CpuCrowdSim::TUNED_PARALLEL_CHOICE ? "parallel" : "sequential") +
                 (g_cpuSchedule == CpuCrowdSim::TUNED_SCHEDULE ? "" : " [NOT the tuned default]");
    m.logicalCores = bench::logicalCores();
    m.ompMaxThreads = omp_get_max_threads();
    return m;
}

// Generates the snapshots that are missing; reports occupancy and validity of every N
std::string ensureSnapshots(const fs::path& dir, const std::vector<int>& ns, GpuBench& gpu) {
    fs::create_directories(dir);
    std::string report = "| N | state | active | occupied cells | agents / occupied cell | max / cell | candidates / agent | spawn check |\n"
                         "|---:|---|---:|---:|---:|---:|---:|---|\n";
    for (int n : ns) {
        if (!fs::exists(bench::snapshotPath(dir, "spawn", n)) || !fs::exists(bench::snapshotPath(dir, "congested", n))) {
            std::printf("generating snapshots for N = %d\n", n);
            const std::vector<GpuBoid> spawn = spawnBleacherCrowd(n);
            bench::saveSnapshot(bench::snapshotPath(dir, "spawn", n), spawn);
            bench::saveSnapshot(bench::snapshotPath(dir, "congested", n), gpu.run(n, spawn, bench::CONGESTED_STEPS));
        }
        for (const char* state : { "spawn", "congested" }) {
            const std::vector<GpuBoid> s = bench::loadSnapshot(dir, state, n);
            long nan = 0, notFree = 0, noTread = 0;
            for (const GpuBoid& b : s) {
                const glm::vec3 p(b.position);
                nan += std::isnan(p.x) || std::isnan(p.y) || std::isnan(p.z);
                if (std::string(state) == "spawn") {
                    notFree += !(sampleSDF_CPU(p) > 0.0f);
                    noTread += !(sampleSDF_CPU(p - glm::vec3(0.0f, 0.0f, 0.02f)) < 0.0f);
                }
            }
            const bench::Occupancy o = bench::occupancy(s);
            char line[320];
            std::snprintf(line, sizeof line, "| %d | %s | %ld | %d | %.1f | %d | %.0f | %s |\n", n, state, o.active, o.occupiedCells, o.meanPerCell,
                          o.maxPerCell, o.meanCandidates,
                          std::string(state) == "spawn" ? (nan || notFree || noTread ? "INVALID" : "valid: on a tread, free space, no NaN")
                                                        : (nan ? "NaN" : "no NaN"));
            report += line;
            if (nan || notFree || noTread) throw std::runtime_error("invalid snapshot " + bench::snapshotPath(dir, state, n).string());
        }
    }
    report += "\nCongested: the GPU state after " + std::to_string(bench::CONGESTED_STEPS) + " steps from spawn.\n";
    return report;
}

int cmdRun(const Args& a) {
    RunConfig cfg;
    cfg.quick = a.has("quick");
    if (cfg.quick) {
        cfg.rounds = a.getInt("rounds", 1);
        cfg.ns = { 1024, 4096 };
        cfg.trajNs = { 1024, 4096 };
        cfg.gpuWarmMs = 200.0;
        cfg.trajWarmup = 20;
        cfg.trajMeasured = 30;
        cfg.probeSteps = 50;
    } else {
        cfg.rounds = a.getInt("rounds", 5);
        cfg.ns = { 1024, 4096, 16384, 65536, 262144 };
        cfg.trajNs = { 1024, 4096, 16384, 65536 };
    }
    if (a.has("n")) cfg.ns = bench::parseIntList(a.get("n", ""));
    if (a.has("traj-n")) cfg.trajNs = bench::parseIntList(a.get("traj-n", ""));
    for (int n : cfg.ns)   // N above the venue's design capacity is measured, with a warning (and its label on every row)
        if (const std::string w = venue::warning(n); !w.empty()) std::fprintf(stderr, "%s\n", w.c_str());
    const fs::path outDir = a.get("out", "out/results");
    const fs::path snapDir = a.get("snapshots", "out/bench/snapshots");

    bench::createHiddenContext("benchmark_crowd");
    const GLuint sdfTex = loadSDFTexture3D(resolveAsset("stadium.sdf"));
    const std::vector<float>& sdf = sdfVolumeCPU();
    if (!sdfTex || sdf.empty()) throw std::runtime_error("cannot load stadium.sdf");
    GpuBench gpu(resolveAsset("shaders"), sdfTex);
    const int maxThreads = CpuCrowdSim::maxThreads();
    Meta meta = makeMeta(cfg.quick ? "benchmark_quick" : "benchmark", a.get("clock-note", ""));
    meta.note = a.get("note", "");
    std::printf("benchmark_crowd %s | commit %s | %s | GPU %s | %s | CPU %s (%u logical, OpenMP %d) | schedule %s | clock note '%s' | %s\n",
                meta.runId.c_str(), meta.commit.c_str(), meta.build.c_str(), meta.gpu.c_str(), meta.driver.c_str(), meta.cpu.c_str(),
                meta.logicalCores, meta.ompMaxThreads, meta.schedule.c_str(), meta.clockNote.c_str(), meta.qos.c_str());
#ifndef NDEBUG
    std::printf("WARNING: not a Release build; timings are not representative\n");
#endif

    std::vector<int> snapNs = cfg.ns;
    for (int n : cfg.trajNs) if (std::find(snapNs.begin(), snapNs.end(), n) == snapNs.end()) snapNs.push_back(n);
    if (std::find(snapNs.begin(), snapNs.end(), 4096) == snapNs.end()) snapNs.push_back(4096);   // self-check, probe
    const std::string snapshotReport = ensureSnapshots(snapDir, snapNs, gpu);

    std::string selfCheckReport;
    if (!selfCheck(gpu, sdf, snapDir, meta, selfCheckReport)) return 3;

    const std::vector<Cell> plan = makePlan(cfg, maxThreads);
    std::string estimateReport;
    const double estS = estimateSeconds(plan, cfg, gpu, sdf, snapDir, maxThreads, estimateReport);
    std::printf("%s", estimateReport.c_str());
    if (a.has("plan")) return 0;
    if (estS > 50 * 60 && !a.has("force")) {
        std::printf("estimate exceeds the 45-minute budget (with margin); rerun with --force to measure anyway\n");
        return 4;
    }

    // Untimed: active agents per trajectory step (GPU); the CPU counts its own
    std::map<int, std::vector<long>> gpuActive;
    for (int n : cfg.trajNs) gpuActive[n] = gpu.activeCounts(n, bench::loadSnapshot(snapDir, "spawn", n), cfg.trajWarmup + cfg.trajMeasured);

    fs::create_directories(outDir);
    const fs::path csvPath = outDir / (meta.runId + ".csv"), trajPath = outDir / (meta.runId + "_trajectory.csv"),
                   mdPath = outDir / (meta.runId + "_summary.md");
    Writer out(meta, csvPath, cfg.trajNs.empty() ? fs::path() : trajPath);
    std::map<std::string, std::vector<GpuBoid>> snaps;
    auto snapshot = [&](const std::string& state, int n) -> const std::vector<GpuBoid>& {
        const std::string key = state + std::to_string(n);
        if (!snaps.count(key)) snaps[key] = bench::loadSnapshot(snapDir, state, n);
        return snaps[key];
    };

    const auto start = Clock::now();
    for (int r = 0; r < cfg.rounds; ++r) {
        std::printf("round %d/%d\n", r + 1, cfg.rounds);
        Row probe = gpu.snapshot(PROBE_N, "spawn", snapshot("spawn", PROBE_N), cfg.probeSteps, cfg.gpuWarmMs);
        probe.impl = "gpu_probe";
        probe.round = r;
        out.row(probe);
        printRow(probe, start);
        std::vector<const Cell*> cells;
        for (const Cell& c : plan)
            if (std::find(c.rounds.begin(), c.rounds.end(), r) != c.rounds.end()) cells.push_back(&c);
        const size_t shift = cells.empty() ? 0 : (size_t(r) * ((cells.size() + size_t(cfg.rounds) - 1) / size_t(cfg.rounds))) % cells.size();
        std::rotate(cells.begin(), cells.begin() + std::ptrdiff_t(shift), cells.end());
        for (const Cell* c : cells) {
            Row row;
            std::vector<StepSample> samples;
            if (c->state == "trajectory") {
                const std::vector<GpuBoid>& spawn = snapshot("spawn", c->n);
                if (c->impl == "gpu") row = gpu.trajectory(c->n, spawn, cfg.trajWarmup, c->measured, cfg.gpuWarmMs, gpuActive[c->n], samples);
                else row = cpuTrajectory(sdf, c->n, c->threads, spawn, cfg.trajWarmup, c->measured, c->threads == 1 && c->n >= 65536, samples);
            } else if (c->impl == "gpu") {
                row = gpu.snapshot(c->n, c->state, snapshot(c->state, c->n), c->measured, cfg.gpuWarmMs);
            } else {
                row = cpuSnapshot(sdf, c->n, c->threads, c->state, snapshot(c->state, c->n), c->measured);
            }
            row.round = r;
            out.row(row);
            if (!samples.empty()) out.trajectory(row, cfg.trajWarmup + 1, samples);
            printRow(row, start);
        }
    }
    const double elapsedS = bench::msSince(start) / 1000.0;
    writeSummary(mdPath, meta, cfg, out.rows(), maxThreads, selfCheckReport, estimateReport, snapshotReport, elapsedS);
    std::printf("done in %.1f min: %s, %s, %s\n", elapsedS / 60.0, csvPath.string().c_str(), trajPath.string().c_str(), mdPath.string().c_str());
    return 0;
}

// CPU thread scaling study: snapshot mode, tuned schedule, thread order rotated between rounds
int cmdScaling(const Args& a) {
    const std::vector<int> ns = bench::parseIntList(a.get("n", "65536"));
    const std::vector<std::string> states = bench::parseList(a.get("states", "spawn,congested"));
    const std::vector<int> threadList = bench::parseIntList(a.get("threads", "1,2,4,6,8,12,14,16,20"));
    const int rounds = a.getInt("rounds", 3), steps = a.getInt("steps", 20);
    const fs::path outDir = a.get("out", "out/results");
    const fs::path snapDir = a.get("snapshots", "out/bench/snapshots");
    bench::createHiddenContext("benchmark_crowd");
    loadSDFTexture3D(resolveAsset("stadium.sdf"));
    const std::vector<float>& sdf = sdfVolumeCPU();
    Meta meta = makeMeta("cpu_scaling", a.get("clock-note", ""));
    fs::create_directories(outDir);
    const fs::path csvPath = outDir / (meta.runId + ".csv");
    Writer out(meta, csvPath, fs::path());
    std::printf("CPU scaling %s | %s | schedule %s | %d rounds x %d steps | %s\n", meta.runId.c_str(), meta.cpu.c_str(), meta.schedule.c_str(), rounds,
                steps, meta.qos.c_str());
    const auto start = Clock::now();
    for (int r = 0; r < rounds; ++r) {
        for (int n : ns) {
            for (const std::string& state : states) {
                const std::vector<GpuBoid> snap = bench::loadSnapshot(snapDir, state, n);
                for (size_t j = 0; j < threadList.size(); ++j) {
                    const int threads = threadList[(j + size_t(r) * 3) % threadList.size()];
                    Row row = cpuSnapshot(sdf, n, threads, state, snap, steps);
                    row.round = r;
                    out.row(row);
                    printRow(row, start);
                }
            }
        }
    }
    // Summary table: median over rounds, speedup vs 1 thread
    std::ofstream md(outDir / (meta.runId + "_summary.md"));
    md << "# CPU thread scaling " << meta.runId << "\n\nCpuCrowdSim, SortMode::Counting, schedule " << meta.schedule
       << ", snapshot mode, steady_clock ms per step: median over " << rounds << " rounds of the per-round median (" << steps
       << " measured steps per round). CPU: " << meta.cpu << " (" << meta.logicalCores << " logical cores: 6 P-cores with 2 threads each = 12, plus 8 E-cores). "
       << "Commit " << meta.commit << ", " << meta.build << ", flags `" << meta.flags << "`, clock note: " << meta.clockNote << ", process QoS: "
       << meta.qos << ".\n\n";
    md << "| N | state | threads | ms/step (min-max) | physics ms | speedup vs 1 | efficiency |\n|---:|---|---:|---:|---:|---:|---:|\n";
    for (int n : ns)
        for (const std::string& state : states) {
            double base = 0;
            for (int threads : threadList) {
                std::vector<Row> sel;
                for (const Row& row : out.rows()) if (row.n == n && row.state == state && row.threads == threads) sel.push_back(row);
                const Agg g = aggregate(sel);
                if (threads == 1) base = g.med;
                char b[256];
                std::snprintf(b, sizeof b, "| %d | %s | %d | %s (%s-%s) | %s | %.2fx | %.0f%% |\n", n, state.c_str(), threads, fmtMs(g.med).c_str(),
                              fmtMs(g.lo).c_str(), fmtMs(g.hi).c_str(), fmtMs(g.physics).c_str(), base > 0 ? base / g.med : 0.0,
                              base > 0 ? 100.0 * base / g.med / threads : 0.0);
                md << b;
            }
        }
    std::printf("done in %.1f min: %s\n", bench::msSince(start) / 60000.0, csvPath.string().c_str());
    return 0;
}

// --- The thesis benchmark ---
// (A) constant density: venues S, M, L at 100% load (every seat: 3 728 / 15 832 / 63 424 agents in buffers of 4 096 / 16 384 / 65 536), the
// default model (queue-aware exit choice, incline speed, stair spacing EMPIRICAL); (B) the fixed-venue stress sweep: the terrace at N = 1 024
// .. 262 144 (capacity labels on every row). States: 'spawn' and 'congested': a venue's GPU state at t50 of its 100% run (the step by which
// ceil(N0 / 2) agents have left, found by stepping from the spawn: the run of results/evacuation/matrix/<V>_load100, bit for bit, since the
// safety metrics only read the state); the terrace's after CONGESTED_STEPS steps. The safety metrics are OFF (CrowdSim
// alone, as in production benchmarking). Snapshot mode: before every step the agent state is restored (a GPU-side copy into both ping-pong
// halves, outside the timestamps; the CPU's restoreAgentState); an analytic venue's exit choice (assignments, counts, the 3 s evaluation rhythm)
// runs on, as in the perf protocol's bench cell. GPU per-pass times: the timestamp ring (hash, sort, cells / gather, physics) and the
// physics stage split by CrowdSim's dispatch hook (exit choice, predict, projection iterations 1 .. K - 1, final pass = the last iteration + the
// final static contacts + the step-up limit). CPU: the same parts by steady_clock (CpuCrowdSim::timings).
namespace thesis {

struct Workload {
    std::string venue;   // "terrace" | "S" | "M" | "L"
    int n = 0;           // the buffer (a power of two); a venue's seated agents are its active ones, the rest parked
    std::string key() const { return bench::workloadKey(venue, n); }
    bool seated() const { return venue != "terrace"; }
};

const std::vector<Workload> VENUES = { { "S", 4096 }, { "M", 16384 }, { "L", 65536 } };
const std::vector<Workload> TERRACE = { { "terrace", 1024 }, { "terrace", 4096 }, { "terrace", 16384 }, { "terrace", 65536 }, { "terrace", 262144 } };

fs::path snapPath(const fs::path& dir, const Workload& w, const std::string& state) { return bench::workloadSnapshotPath(dir, w.venue, w.n, state); }
std::vector<GpuBoid> loadSnap(const fs::path& dir, const Workload& w, const std::string& state) { return bench::loadWorkloadSnapshot(dir, w.venue, w.n, state); }

std::string rowLabel(const Workload& w, long active) {
    if (!w.seated()) return label(w.n);
    return venue::label(int(active), venue::capacityOf(venueByName(w.venue)));
}

// The physics stage split on the GPU: timestamps from the dispatch hook after the cells pass (tag 0), the exit choice's last dispatch (1),
// the predict pass (2), the projection's last iteration (3) and the final pass (4); read once after the measured loop
class PhysicsStamps {
public:
    PhysicsStamps() = default;
    PhysicsStamps(const PhysicsStamps&) = delete;
    PhysicsStamps& operator=(const PhysicsStamps&) = delete;
    ~PhysicsStamps() { if (!q_.empty()) glDeleteQueries(GLsizei(q_.size()), q_.data()); }
    void attach(CrowdSim& sim, int steps) {
        if (q_.size() < size_t(steps) * 5) {
            if (!q_.empty()) glDeleteQueries(GLsizei(q_.size()), q_.data());
            q_.assign(size_t(steps) * 5, 0);
            glGenQueries(GLsizei(q_.size()), q_.data());
        }
        used_ = 0;
        step_ = 0;
        tags_.clear();
        const int lastIt = sim.projectionIterations() - 1;
        sim.setDispatchHook([this, lastIt](const CrowdSim::DispatchInfo& d) {
            int tag = -1;
            if (std::strcmp(d.pass, "cells") == 0) tag = 0;
            else if (std::strcmp(d.pass, "choice") == 0 && d.k == 0) tag = 1;
            else if (std::strcmp(d.pass, "physics") == 0) tag = 2;
            else if (std::strcmp(d.pass, "project") == 0 && d.j == lastIt) tag = 3;
            else if (std::strcmp(d.pass, "project_final") == 0) tag = 4;
            if (tag < 0 || used_ >= q_.size()) return;
            glQueryCounter(q_[used_++], GL_TIMESTAMP);
            tags_.push_back({ step_, tag });
            if (tag == 4) ++step_;
        });
    }
    struct Split { double choice = 0, predict = 0, project = 0, final = 0; };
    std::vector<Split> read(CrowdSim& sim) {
        sim.setDispatchHook(nullptr);
        std::vector<GLuint64> t(used_, 0);
        for (size_t i = 0; i < used_; ++i) glGetQueryObjectui64v(q_[i], GL_QUERY_RESULT, &t[i]);
        std::vector<Split> out(static_cast<size_t>(step_));
        std::vector<std::array<GLuint64, 5>> at(static_cast<size_t>(step_), std::array<GLuint64, 5>{});
        std::vector<std::array<bool, 5>> has(static_cast<size_t>(step_), std::array<bool, 5>{});
        for (size_t i = 0; i < used_; ++i) {
            if (tags_[i].first >= step_) continue;
            at[size_t(tags_[i].first)][size_t(tags_[i].second)] = t[i];
            has[size_t(tags_[i].first)][size_t(tags_[i].second)] = true;
        }
        for (size_t s = 0; s < out.size(); ++s) {
            auto& a = at[s];
            if (!has[s][1]) a[1] = a[0];   // no exit choice (the terrace, the nearest exit)
            if (!has[s][3]) a[3] = a[2];   // K <= 1: no separate projection iterations
            auto ms = [&](int x, int y) { return double(a[size_t(y)] - a[size_t(x)]) * 1e-6; };
            out[s] = { ms(0, 1), ms(1, 2), ms(2, 3), ms(3, 4) };
        }
        return out;
    }

private:
    std::vector<GLuint> q_;
    size_t used_ = 0;
    int step_ = 0;
    std::vector<std::pair<int, int>> tags_;
};

struct Cell {
    Workload w;
    std::string impl;   // gpu | cpu
    int threads = 0;
    std::string state;
    int measured = 0;
    std::vector<int> rounds;
};

struct Result {   // one cell in one round
    Cell c;
    int round = 0, warmup = 0;
    long active = 0;
    std::vector<double> total;   // per measured step [ms]
    double hash = 0, sort = 0, cells = 0, physics = 0, choice = 0, predict = 0, project = 0, final = 0, wall = 0;   // medians [ms]
    std::string label;
};

double med(std::vector<double> v) { return v.empty() ? 0.0 : bench::median(std::move(v)); }

Result gpuCell(const fs::path& shaderDir, GLuint sdfTex, const Cell& c, const std::vector<GpuBoid>& snap, double warmMinMs) {
    const Venue& v = venueByName(c.w.venue);
    CrowdSim sim(shaderDir, c.w.n, v, defaultModelOptions(v));
    const GLuint tex = v.seated() ? 0 : sdfTex;
    GLuint pristine = 0;
    const GLsizeiptr bytes = GLsizeiptr(snap.size() * sizeof(GpuBoid));
    glGenBuffers(1, &pristine);
    glBindBuffer(GL_COPY_READ_BUFFER, pristine);
    glBufferData(GL_COPY_READ_BUFFER, bytes, snap.data(), GL_STATIC_DRAW);
    auto restore = [&] {
        glMemoryBarrier(GL_BUFFER_UPDATE_BARRIER_BIT);
        for (int h = 0; h < 2; ++h) {
            glBindBuffer(GL_COPY_READ_BUFFER, pristine);
            glBindBuffer(GL_COPY_WRITE_BUFFER, sim.boidBuffer(h));
            glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, bytes);
        }
    };
    sim.upload(snap);   // a fresh exit choice; the restores below keep it running
    int warm = 0;
    const auto t0 = Clock::now();
    while (warm < GPU_WARMUP_MIN_STEPS || bench::msSince(t0) < warmMinMs) {
        restore();
        sim.step(tex);
        if (++warm % 50 == 0) glFinish();
    }
    glFinish();
    PhysicsStamps split;
    split.attach(sim, c.measured);
    sim.beginTimingRing(c.measured);
    const auto t1 = Clock::now();
    for (int i = 0; i < c.measured; ++i) { restore(); sim.step(tex); }
    glFinish();
    const double batchMs = bench::msSince(t1);
    const std::vector<CrowdSim::PassTimesMs> times = sim.readTimingRing();
    const std::vector<PhysicsStamps::Split> parts = split.read(sim);
    const auto t2 = Clock::now();
    for (int i = 0; i < c.measured; ++i) restore();
    glFinish();
    const double restoreMs = bench::msSince(t2);
    glDeleteBuffers(1, &pristine);
    Result r;
    r.c = c;
    r.warmup = warm;
    r.active = bench::countActive(snap);
    std::vector<double> h, s, ce, p, ch, pr, pj, fi;
    for (const CrowdSim::PassTimesMs& t : times) { r.total.push_back(t.total); h.push_back(t.hash); s.push_back(t.sort); ce.push_back(t.cells); p.push_back(t.physics); }
    for (const PhysicsStamps::Split& x : parts) { ch.push_back(x.choice); pr.push_back(x.predict); pj.push_back(x.project); fi.push_back(x.final); }
    r.hash = med(h); r.sort = med(s); r.cells = med(ce); r.physics = med(p);
    r.choice = med(ch); r.predict = med(pr); r.project = med(pj); r.final = med(fi);
    r.wall = (batchMs - restoreMs) / c.measured;
    r.label = rowLabel(c.w, r.active);
    return r;
}

Result cpuCell(const std::vector<float>& sdf, const Cell& c, const std::vector<GpuBoid>& snap) {
    const Venue& v = venueByName(c.w.venue);
    CpuCrowdSim cpu(v, defaultModelOptions(v), v.seated() ? std::vector<float>() : sdf, c.threads, CPU_SORT);
    cpu.setSchedule(g_cpuSchedule);
    cpu.setState(snap);   // a fresh exit choice; restoreAgentState keeps it running
    // Warm-up: CPU_WARMUP_STEPS steps, or fewer once CPU_WARMUP_CAP_MS of load ran (at least CPU_WARMUP_MIN_STEPS; one step if that step
    // alone ran CPU_WARMUP_CAP_MS: the 262 144 stress point's steps take minutes at 1 thread)
    int warm = 0;
    const auto tw = Clock::now();
    while (warm < CPU_WARMUP_STEPS) {
        const double el = bench::msSince(tw);
        if (warm >= CPU_WARMUP_MIN_STEPS && el >= CPU_WARMUP_CAP_MS) break;
        if (warm >= 1 && el / warm >= CPU_WARMUP_CAP_MS) break;
        cpu.restoreAgentState(snap);
        cpu.step();
        ++warm;
    }
    Result r;
    r.c = c;
    r.warmup = warm;
    r.active = bench::countActive(snap);
    std::vector<double> h, s, ce, p, ch, pr, pj, fi;
    for (int i = 0; i < c.measured; ++i) {
        cpu.restoreAgentState(snap);
        cpu.step();
        const CpuCrowdSim::StageTimesMs& t = cpu.timings();
        r.total.push_back(t.total); h.push_back(t.hash); s.push_back(t.sort); ce.push_back(t.cells); p.push_back(t.physics);
        ch.push_back(t.choice); pr.push_back(t.predict); pj.push_back(t.project); fi.push_back(t.final);
    }
    r.hash = med(h); r.sort = med(s); r.cells = med(ce); r.physics = med(p);
    r.choice = med(ch); r.predict = med(pr); r.project = med(pj); r.final = med(fi);
    r.wall = bench::stats(r.total).mean;
    r.label = rowLabel(c.w, r.active);
    return r;
}

// Snapshots: the spawn and the congested state of every workload (generated when missing, by this build's GPU pipeline)
std::string ensureWorkloadSnapshots(const fs::path& dir, const std::vector<Workload>& ws, const fs::path& shaderDir, GLuint sdfTex) {
    fs::create_directories(dir);
    std::string report = "| workload | N (buffer) | state | active | definition |\n|---|---:|---|---:|---|\n";
    for (const Workload& w : ws) {
        const Venue& v = venueByName(w.venue);
        std::string congestedDef;
        if (!fs::exists(snapPath(dir, w, "spawn")) || !fs::exists(snapPath(dir, w, "congested")) || !fs::exists(dir / (w.key() + "_congested.txt"))) {
            std::printf("generating snapshots for %s\n", w.key().c_str());
            const std::vector<GpuBoid> spawn = w.seated() ? spawnSeatedCrowd(v, w.n, 1.0, 1337) : spawnBleacherCrowd(w.n);
            bench::saveSnapshot(snapPath(dir, w, "spawn"), spawn);
            CrowdSim sim(shaderDir, w.n, v, defaultModelOptions(v));
            sim.upload(spawn);
            const GLuint tex = v.seated() ? 0 : sdfTex;
            std::vector<GpuBoid> st;
            if (w.seated()) {   // t50: the step by which ceil(N0 / 2) agents have left
                const long n0 = bench::countActive(spawn), need = (n0 + 1) / 2;
                int step = 0;
                for (;;) {
                    sim.step(tex);
                    ++step;
                    st = bench::readBuffer<GpuBoid>(sim.currentStateBuffer(), size_t(w.n));
                    if (n0 - bench::countActive(st) >= need) break;
                    if (step > 100000) throw std::runtime_error("no t50 within 100000 steps");
                }
                char b[256];
                std::snprintf(b, sizeof b, "GPU state at t50 of the 100%% run: step %d (%.1f s), %ld of %ld agents left", step, step * DT_REAL_S, n0 - bench::countActive(st), n0);
                congestedDef = b;
            } else {
                for (int i = 0; i < bench::CONGESTED_STEPS; ++i) sim.step(tex);
                st = bench::readBuffer<GpuBoid>(sim.currentStateBuffer(), size_t(w.n));
                congestedDef = "GPU state after " + std::to_string(bench::CONGESTED_STEPS) + " steps from spawn";
            }
            bench::saveSnapshot(snapPath(dir, w, "congested"), st);
            std::ofstream(dir / (w.key() + "_congested.txt")) << congestedDef << "\n";
        }
        {
            std::ifstream f(dir / (w.key() + "_congested.txt"));
            std::getline(f, congestedDef);
        }
        for (const char* state : { "spawn", "congested" }) {
            const std::vector<GpuBoid> s = loadSnap(dir, w, state);
            long nan = 0;
            for (const GpuBoid& b : s) nan += std::isnan(b.position.x) || std::isnan(b.position.y) || std::isnan(b.position.z);
            if (nan) throw std::runtime_error("NaN in snapshot " + snapPath(dir, w, state).string());
            const std::string def = std::string(state) == "spawn" ? (w.seated() ? "spawnSeatedCrowd(venue, N, 100%, seed 1337): every seat" : "spawnBleacherCrowd(N)") : congestedDef;
            report += "| " + w.key() + " | " + std::to_string(w.n) + " | " + state + " | " + std::to_string(bench::countActive(s)) + " | " + def + " |\n";
        }
    }
    return report;
}

// Self-check before measuring: the terrace's (selfCheck above) plus every venue's golden pins: GPU, CPU counting (and S's CPU bitonic) after
// GOLDEN_STEPS steps of the full seat spawn
bool venueSelfCheck(const fs::path& shaderDir, const Meta& meta, std::string& report) {
    bool ok = true;
    char line[512];
    auto log = [&](const std::string& s) { std::printf("%s\n", s.c_str()); report += s + "\n"; };
    const bool sameDriver = meta.gpu + " | " + meta.driver == golden::GOLDEN_DRIVER;
    struct Pin { const char* venue; int n; const golden::Golden* g; bool bitonic; };
    for (const Pin& p : { Pin{ "S", 4096, golden::GOLDEN_S, true }, Pin{ "M", 16384, golden::GOLDEN_M, false }, Pin{ "L", 65536, golden::GOLDEN_L, false } }) {
        const Venue& v = venueByName(p.venue);
        const std::vector<GpuBoid> spawn = spawnSeatedCrowd(v, p.n, 1.0, 1337);
        CrowdSim sim(shaderDir, p.n, v, defaultModelOptions(v));
        sim.upload(spawn);
        for (int i = 0; i < golden::GOLDEN_STEPS; ++i) sim.step(0);
        const uint64_t hg = golden::stateHash(bench::readBuffer<GpuBoid>(sim.currentStateBuffer(), size_t(p.n)));
        std::vector<std::pair<const golden::Golden*, uint64_t>> got = { { &p.g[0], hg } };
        for (int k = 1; k <= (p.bitonic ? 2 : 1); ++k) {
            CpuCrowdSim cpu(v, defaultModelOptions(v), std::vector<float>(), 0, k == 1 ? CpuCrowdSim::SortMode::Counting : CpuCrowdSim::SortMode::GpuBitonic);
            cpu.setSchedule(g_cpuSchedule);
            cpu.setState(spawn);
            for (int i = 0; i < golden::GOLDEN_STEPS; ++i) cpu.step();
            got.push_back({ &p.g[k], golden::stateHash(cpu.state()) });
        }
        for (size_t k = 0; k < got.size(); ++k) {
            const bool match = got[k].second == got[k].first->hash, enforced = k > 0 || sameDriver;
            std::snprintf(line, sizeof line, "  golden %-30s %016llx pinned %016llx: %s", got[k].first->name, (unsigned long long)got[k].second,
                          (unsigned long long)got[k].first->hash, match ? "match" : enforced ? "MISMATCH" : "differs (different driver: not enforced)");
            log(line);
            ok &= match || !enforced;
        }
    }
    log(ok ? "venue self-check passed" : "VENUE SELF-CHECK FAILED: run aborted");
    return ok;
}

struct Agg {   // a cell over its rounds
    int rounds = 0, measured = 0, warmup = 0;
    long active = 0;
    double roundMed = 0, roundLo = 0, roundHi = 0;   // median, min, max of the per-round medians
    double med = 0, p5 = 0, p95 = 0;                 // over every measured step of every round
    double hash = 0, sort = 0, cells = 0, physics = 0, choice = 0, predict = 0, project = 0, final = 0, wall = 0;
    std::string label;
};

Agg aggregate(const std::vector<const Result*>& rs) {
    Agg a;
    if (rs.empty()) return a;
    std::vector<double> m, all, h, s, c, p, ch, pr, pj, fi, w;
    for (const Result* r : rs) {
        m.push_back(med(r->total));
        all.insert(all.end(), r->total.begin(), r->total.end());
        h.push_back(r->hash); s.push_back(r->sort); c.push_back(r->cells); p.push_back(r->physics);
        ch.push_back(r->choice); pr.push_back(r->predict); pj.push_back(r->project); fi.push_back(r->final); w.push_back(r->wall);
    }
    a.rounds = int(rs.size());
    a.measured = rs.front()->c.measured;
    a.warmup = rs.front()->warmup;
    a.active = rs.front()->active;
    a.label = rs.front()->label;
    a.roundMed = med(m);
    a.roundLo = *std::min_element(m.begin(), m.end());
    a.roundHi = *std::max_element(m.begin(), m.end());
    const Stats st = bench::stats(all);
    a.med = st.median; a.p5 = st.p5; a.p95 = st.p95;
    a.hash = med(h); a.sort = med(s); a.cells = med(c); a.physics = med(p);
    a.choice = med(ch); a.predict = med(pr); a.project = med(pj); a.final = med(fi); a.wall = med(w);
    return a;
}

std::string cellName(const Cell& c) { return c.w.key() + " " + c.state + " " + c.impl + (c.impl == "cpu" ? "-" + std::to_string(c.threads) : ""); }

int cmdThesis(const Args& a) {
    const bool quick = a.has("quick");
    const int rounds = a.getInt("rounds", quick ? 1 : 5);
    const fs::path outDir = a.get("out", "out/results/benchmarks/thesis");
    const fs::path snapDir = a.get("snapshots", "out/bench/snapshots_thesis");
    std::vector<Workload> ws;
    if (!a.has("no-venues")) ws.insert(ws.end(), VENUES.begin(), VENUES.end());
    if (!a.has("no-terrace")) for (const Workload& w : TERRACE) if (!quick || w.n <= 4096) ws.push_back(w);
    if (a.has("only")) {   // a subset of workload keys (venue_S, terrace_4096, ...)
        const std::vector<std::string> keep = bench::parseList(a.get("only", ""));
        std::vector<Workload> sel;
        for (const Workload& w : ws) if (std::find(keep.begin(), keep.end(), w.key()) != keep.end()) sel.push_back(w);
        ws = sel;
    }
    bench::createHiddenContext("benchmark_crowd");
    const GLuint sdfTex = loadSDFTexture3D(resolveAsset("stadium.sdf"));
    const std::vector<float>& sdf = sdfVolumeCPU();
    if (!sdfTex || sdf.empty()) throw std::runtime_error("cannot load stadium.sdf");
    const fs::path shaderDir = resolveAsset("shaders");
    GpuBench gpu(shaderDir, sdfTex);
    const int maxThreads = CpuCrowdSim::maxThreads();
    Meta meta = makeMeta(quick ? "thesis_quick" : "thesis", a.get("clock-note", ""));
    meta.note = a.get("note", "");
    std::printf("benchmark_crowd thesis %s | commit %s (dirty %s) | %s | GPU %s | %s | CPU %s (%u logical, OpenMP %d) | schedule %s | clock note '%s' | %s\n",
                meta.runId.c_str(), meta.commit.c_str(), meta.dirty.c_str(), meta.build.c_str(), meta.gpu.c_str(), meta.driver.c_str(), meta.cpu.c_str(),
                meta.logicalCores, meta.ompMaxThreads, meta.schedule.c_str(), meta.clockNote.c_str(), meta.qos.c_str());
#ifndef NDEBUG
    std::printf("WARNING: not a Release build; timings are not representative\n");
#endif
    // The terrace's own snapshots for the base self-check (N = 4096 congested) and the probe (N = 4096 spawn)
    const fs::path baseSnapDir = snapDir / "terrace_base";
    const std::string baseReport = ensureSnapshots(baseSnapDir, { 4096 }, gpu);
    (void)baseReport;
    const std::string snapshotReport = ensureWorkloadSnapshots(snapDir, ws, shaderDir, sdfTex);
    std::string selfCheckReport;
    if (!a.has("skip-self-check")) {
        if (!selfCheck(gpu, sdf, baseSnapDir, meta, selfCheckReport)) return 3;
        if (!venueSelfCheck(shaderDir, meta, selfCheckReport)) return 3;
    } else {
        selfCheckReport = "self-check SKIPPED (--skip-self-check: not a measurement)\n";
    }

    // The plan (by the step's cost; `thesis --plan` measures it): GPU 300 measured steps (262 144: 100); CPU at max threads 100 (N <= 16 384),
    // 30 (L), 10 (the terrace at 65 536), 3 (262 144); CPU-1 100 (N <= 4 096), 20 (M), 10 (the terrace at 16 384), 5 in 3 rounds (L), 3 in 2
    // rounds (the terrace at 65 536), 1 in 1 round (262 144: ~5 min per step); every row records its rounds and steps
    std::vector<Cell> plan;
    const std::vector<int> all = allRounds(rounds);
    for (const Workload& w : ws)
        for (const char* state : { "spawn", "congested" }) {
            if (quick) {
                plan.push_back({ w, "gpu", 0, state, 50, all });
                plan.push_back({ w, "cpu", maxThreads, state, 5, all });
                plan.push_back({ w, "cpu", 1, state, 2, all });
                continue;
            }
            plan.push_back({ w, "gpu", 0, state, w.n >= STRESS_N ? 100 : 300, all });
            plan.push_back({ w, "cpu", maxThreads, state, w.n >= STRESS_N ? 3 : w.n <= 16384 ? 100 : w.seated() ? 30 : 10, all });
            if (w.n <= 4096) plan.push_back({ w, "cpu", 1, state, 100, all });
            else if (w.n <= 16384) plan.push_back({ w, "cpu", 1, state, w.seated() ? 20 : 10, all });
            else if (w.n < STRESS_N) plan.push_back(w.seated() ? Cell{ w, "cpu", 1, state, 5, reducedRounds(rounds, 3) } : Cell{ w, "cpu", 1, state, 3, reducedRounds(rounds, 2) });
            else plan.push_back({ w, "cpu", 1, state, 1, reducedRounds(rounds, 1) });
        }
    if (a.has("plan")) {
        // The time estimate: per (workload, state) a short GPU timing (10 steps after 0.2 s) and one CPU step at max threads and at 1 thread
        // after one warm-up step (CPU-1 at the stress point: extrapolated with the 1 / max-thread ratio at 65 536)
        std::map<std::string, double> ms;
        double total = 0;
        for (const Workload& w : ws)
            for (const char* state : { "spawn", "congested" }) {
                const std::vector<GpuBoid> snap = loadSnap(snapDir, w, state);
                const std::string k = w.key() + state;
                ms["gpu" + k] = med(gpuCell(shaderDir, sdfTex, { w, "gpu", 0, state, 10, {} }, snap, 200.0).total);
                for (int t : { maxThreads, 1 }) {
                    if (t == 1 && w.n >= STRESS_N) {
                        const std::string r = "terrace_65536" + std::string(state);
                        ms["cpu1" + k] = ms.count("cpu1" + r) && ms.count("cpu" + std::to_string(maxThreads) + r)
                                             ? ms["cpu" + std::to_string(maxThreads) + k] * ms["cpu1" + r] / ms["cpu" + std::to_string(maxThreads) + r]
                                             : 0.0;
                        continue;
                    }
                    const Venue& v = venueByName(w.venue);
                    CpuCrowdSim cpu(v, defaultModelOptions(v), v.seated() ? std::vector<float>() : sdf, t, CPU_SORT);
                    cpu.setSchedule(g_cpuSchedule);
                    cpu.setState(snap);
                    cpu.step();
                    cpu.restoreAgentState(snap);
                    cpu.step();
                    ms["cpu" + std::to_string(t) + k] = cpu.timings().total;
                }
                std::printf("  estimate %-14s %-9s GPU %9.4f ms, CPU-%d %10.2f ms, CPU-1 %11.2f ms%s\n", w.key().c_str(), state, ms["gpu" + k], maxThreads,
                            ms["cpu" + std::to_string(maxThreads) + k], ms["cpu1" + k], w.n >= STRESS_N ? " (CPU-1 extrapolated)" : "");
                std::fflush(stdout);
            }
        for (const Cell& c : plan) {
            const std::string k = c.w.key() + c.state;
            const double m = c.impl == "gpu" ? ms["gpu" + k] : ms["cpu" + std::to_string(c.threads) + k];
            const double warmMs = c.impl == "gpu" ? std::max(GPU_WARMUP_MIN_STEPS * m, GPU_WARMUP_MIN_MS)
                                                  : (m >= CPU_WARMUP_CAP_MS ? m : std::min(CPU_WARMUP_STEPS * m, std::max(CPU_WARMUP_MIN_STEPS * m, CPU_WARMUP_CAP_MS)));
            const double s = (warmMs + c.measured * m) * double(c.rounds.size()) / 1000.0;
            total += s;
            std::printf("  %-34s %3d steps x %zu rounds: %10.2f ms/step -> %7.0f s\n", cellName(c).c_str(), c.measured, c.rounds.size(), m, s);
        }
        std::printf("  TOTAL estimate: %.0f min (plus the probes and the CrowdSim set-ups)\n", total / 60.0);
        return 0;
    }

    fs::create_directories(outDir);
    const fs::path csvPath = outDir / (meta.runId + ".csv"), cellsPath = outDir / (meta.runId + "_cells.csv"), mdPath = outDir / (meta.runId + "_summary.md");
    std::FILE* csv = std::fopen(csvPath.string().c_str(), "w");
    if (!csv) throw std::runtime_error("cannot write " + csvPath.string());
    std::fprintf(csv, "run_id,timestamp,git_describe,git_commit,git_dirty,build,clock_note,gpu,driver,cpu,qos,schedule,workload,venue,N,agents,state,impl,threads,round,"
                      "warmup_steps,measured_steps,median_ms,p5_ms,p95_ms,mean_ms,cv,hash_ms,sort_ms,cells_ms,physics_ms,choice_ms,predict_ms,project_ms,final_ms,"
                      "wall_ms_per_step,metrics,label\n");
    std::map<std::string, std::vector<GpuBoid>> snaps;
    auto snapshot = [&](const Workload& w, const std::string& state) -> const std::vector<GpuBoid>& {
        const std::string key = w.key() + state;
        if (!snaps.count(key)) snaps[key] = loadSnap(snapDir, w, state);
        return snaps[key];
    };
    std::vector<Result> results;
    std::vector<double> probes;
    const auto start = Clock::now();
    const std::vector<GpuBoid> probeSnap = bench::loadSnapshot(baseSnapDir, "spawn", PROBE_N);
    for (int r = 0; r < rounds; ++r) {
        std::printf("round %d/%d\n", r + 1, rounds);
        const Row probe = gpu.snapshot(PROBE_N, "spawn", probeSnap, PROBE_STEPS, GPU_WARMUP_MIN_MS);
        probes.push_back(probe.total.median);
        std::printf("  r%d probe (GPU terrace N = %d spawn, %d steps): median %.4f ms  [%5.0f s]\n", r, PROBE_N, PROBE_STEPS, probe.total.median, bench::msSince(start) / 1000.0);
        std::fprintf(csv, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,probe,terrace,%d,%ld,spawn,gpu_probe,0,%d,%d,%d,%.5f,%.5f,%.5f,%.5f,%.4f,%.5f,%.5f,%.5f,%.5f,0,0,0,0,%.5f,off,%s\n",
                     meta.runId.c_str(), meta.timestamp.c_str(), meta.commit.c_str(), meta.commitFull.c_str(), meta.dirty.c_str(), meta.build.c_str(),
                     bench::csvField(meta.clockNote).c_str(), bench::csvField(meta.gpu).c_str(), bench::csvField(meta.driver).c_str(), bench::csvField(meta.cpu).c_str(),
                     bench::csvField(meta.qos).c_str(), bench::csvField(meta.schedule).c_str(), PROBE_N, bench::countActive(probeSnap), r, probe.warmup, probe.measured,
                     probe.total.median, probe.total.p5, probe.total.p95, probe.total.mean, probe.total.cv, probe.hash, probe.sort, probe.cells, probe.physics,
                     probe.wall, bench::csvField(label(PROBE_N)).c_str());
        std::fflush(csv);
        std::vector<const Cell*> cells;
        for (const Cell& c : plan)
            if (std::find(c.rounds.begin(), c.rounds.end(), r) != c.rounds.end()) cells.push_back(&c);
        const size_t shift = cells.empty() ? 0 : (size_t(r) * ((cells.size() + size_t(rounds) - 1) / size_t(rounds))) % cells.size();
        std::rotate(cells.begin(), cells.begin() + std::ptrdiff_t(shift), cells.end());
        for (const Cell* c : cells) {
            Result res = c->impl == "gpu" ? gpuCell(shaderDir, sdfTex, *c, snapshot(c->w, c->state), GPU_WARMUP_MIN_MS) : cpuCell(sdf, *c, snapshot(c->w, c->state));
            res.round = r;
            const Stats st = bench::stats(res.total);
            std::fprintf(csv, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%ld,%s,%s,%d,%d,%d,%d,%.5f,%.5f,%.5f,%.5f,%.4f,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f,off,%s\n",
                         meta.runId.c_str(), meta.timestamp.c_str(), meta.commit.c_str(), meta.commitFull.c_str(), meta.dirty.c_str(), meta.build.c_str(),
                         bench::csvField(meta.clockNote).c_str(), bench::csvField(meta.gpu).c_str(), bench::csvField(meta.driver).c_str(), bench::csvField(meta.cpu).c_str(),
                         bench::csvField(meta.qos).c_str(), bench::csvField(meta.schedule).c_str(), c->w.key().c_str(), c->w.venue.c_str(), c->w.n, res.active,
                         c->state.c_str(), c->impl.c_str(), c->impl == "cpu" ? c->threads : 0, r, res.warmup, c->measured, st.median, st.p5, st.p95, st.mean, st.cv,
                         res.hash, res.sort, res.cells, res.physics, res.choice, res.predict, res.project, res.final, res.wall, bench::csvField(res.label).c_str());
            std::fflush(csv);
            std::printf("  r%d %-34s %4d+%-3d steps  median %10.4f ms (p5 %.4f p95 %.4f)  choice %.4f predict %.4f project %.4f final %.4f  [%5.0f s]\n", r,
                        cellName(*c).c_str(), res.warmup, c->measured, st.median, st.p5, st.p95, res.choice, res.predict, res.project, res.final,
                        bench::msSince(start) / 1000.0);
            std::fflush(stdout);
            results.push_back(std::move(res));
        }
    }
    std::fclose(csv);
    const double elapsedS = bench::msSince(start) / 1000.0;

    // Aggregates per cell
    auto pick = [&](const Workload& w, const std::string& impl, int threads, const std::string& state) {
        std::vector<const Result*> out;
        for (const Result& r : results)
            if (r.c.w.key() == w.key() && r.c.impl == impl && (impl != "cpu" || r.c.threads == threads) && r.c.state == state) out.push_back(&r);
        return aggregate(out);
    };
    std::FILE* cc = std::fopen(cellsPath.string().c_str(), "w");
    std::fprintf(cc, "run_id,git_commit,git_dirty,driver,clock_note,workload,venue,N,agents,state,impl,threads,rounds,warmup_steps,measured_steps,round_median_ms,"
                     "round_min_ms,round_max_ms,median_ms,p5_ms,p95_ms,hash_ms,sort_ms,cells_ms,physics_ms,choice_ms,predict_ms,project_ms,final_ms,wall_ms_per_step,"
                     "realtime_factor,metrics,label\n");
    const std::string cpuMax = "CPU-" + std::to_string(maxThreads);
    std::ofstream md(mdPath);
    md << "# benchmark_crowd thesis " << meta.runId << (quick ? " (QUICK smoke run, not a measurement)" : "") << "\n\n";
    if (!meta.note.empty()) md << "> " << meta.note << "\n\n";
    md << "The benchmark: one simulation step of the GPU pipeline (CrowdSim) and of the CPU reference (CpuCrowdSim, SortMode::Counting, schedule "
       << meta.schedule << ") at " << maxThreads << " threads and at 1 thread. (A) constant density: venues S, M, L at 100% load, the default model "
          "(queue-aware exit choice, incline speed, stair spacing EMPIRICAL); (B) the terrace at N = 1 024 .. 262 144 (the fixed-venue stress sweep, "
          "capacity labels). **The safety metrics are off** (CrowdSim alone, as in production benchmarking). Snapshot mode: every timed step starts from "
          "the identical agent state (restored outside the timed region); an analytic venue's exit choice runs on with its own 3 s rhythm.\n\n";
    md << "Cell format: the median over rounds of the per-round median ms per step, the min-max of the round medians in brackets; p5 / p95: over every "
          "measured step of every round. GPU: GPU-execution time (GL_TIMESTAMP). CPU: steady_clock. Real-time factor = DT_real (" << DT_REAL_S * 1000.0
       << " ms of simulated time per step) / ms per step.\n\n";
    auto cellStr = [](const Agg& g) { return g.rounds ? fmtMs(g.roundMed) + " (" + fmtMs(g.roundLo) + "-" + fmtMs(g.roundHi) + ")" : std::string("-"); };
    auto writeCells = [&](const Workload& w, const std::string& state) {
        for (const auto& [impl, threads] : std::vector<std::pair<std::string, int>>{ { "gpu", 0 }, { "cpu", maxThreads }, { "cpu", 1 } }) {
            const Agg g = pick(w, impl, threads, state);
            if (!g.rounds) continue;
            std::fprintf(cc, "%s,%s,%s,%s,%s,%s,%s,%d,%ld,%s,%s,%d,%d,%d,%d,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f,%.4f,off,%s\n",
                         meta.runId.c_str(), meta.commitFull.c_str(), meta.dirty.c_str(), bench::csvField(meta.driver).c_str(), bench::csvField(meta.clockNote).c_str(),
                         w.key().c_str(), w.venue.c_str(), w.n, g.active, state.c_str(), impl.c_str(), threads, g.rounds, g.warmup, g.measured, g.roundMed,
                         g.roundLo, g.roundHi, g.med, g.p5, g.p95, g.hash, g.sort, g.cells, g.physics, g.choice, g.predict, g.project, g.final, g.wall,
                         DT_REAL_S * 1000.0 / g.roundMed, bench::csvField(g.label).c_str());
        }
    };
    for (const auto& [title, group] : std::vector<std::pair<std::string, std::vector<Workload>>>{ { "(A) Constant density: venues S, M, L at 100% load", VENUES },
                                                                                                   { "(B) Fixed-venue stress sweep: the terrace", TERRACE } }) {
        std::vector<Workload> sel;
        for (const Workload& w : group) if (std::find_if(ws.begin(), ws.end(), [&](const Workload& x) { return x.key() == w.key(); }) != ws.end()) sel.push_back(w);
        if (sel.empty()) continue;
        md << "## " << title << "\n\n";
        md << "| workload | agents (N) | state | GPU ms | p5-p95 | " << cpuMax << " ms | CPU-1 ms | GPU vs " << cpuMax << " | " << cpuMax
           << " vs CPU-1 | real-time factor GPU / " << cpuMax << " / CPU-1 | label |\n|---|---:|---|---:|---|---:|---:|---:|---:|---|---|\n";
        for (const Workload& w : sel)
            for (const char* state : { "spawn", "congested" }) {
                writeCells(w, state);
                const Agg g = pick(w, "gpu", 0, state), c = pick(w, "cpu", maxThreads, state), c1 = pick(w, "cpu", 1, state);
                char sp1[32] = "-", sp2[32] = "-", rt[96] = "-", pp[64] = "-";
                if (g.rounds && c.rounds) std::snprintf(sp1, sizeof sp1, "%.1fx", c.roundMed / g.roundMed);
                if (c.rounds && c1.rounds) std::snprintf(sp2, sizeof sp2, "%.1fx", c1.roundMed / c.roundMed);
                if (g.rounds) std::snprintf(pp, sizeof pp, "%s-%s", fmtMs(g.p5).c_str(), fmtMs(g.p95).c_str());
                std::snprintf(rt, sizeof rt, "%.0f / %.1f / %.2f", g.rounds ? DT_REAL_S * 1000.0 / g.roundMed : 0.0, c.rounds ? DT_REAL_S * 1000.0 / c.roundMed : 0.0,
                              c1.rounds ? DT_REAL_S * 1000.0 / c1.roundMed : 0.0);
                md << "| " << w.key() << " | " << g.active << " (" << w.n << ") | " << state << " | " << cellStr(g) << " | " << pp << " | " << cellStr(c) << " | "
                   << cellStr(c1) << " | " << sp1 << " | " << sp2 << " | " << rt << " | " << (g.rounds ? g.label : c.label) << " |\n";
            }
        md << "\n### GPU per pass (GPU-execution ms, median over rounds)\n\n| workload | state | hash | sort | cells / gather | exit choice | predict | projection "
              "(K - 1 iterations) | final pass | total | projection share | projection + final share |\n|---|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|\n";
        for (const Workload& w : sel)
            for (const char* state : { "spawn", "congested" }) {
                const Agg g = pick(w, "gpu", 0, state);
                if (!g.rounds) continue;
                char s1[16], s2[16];
                std::snprintf(s1, sizeof s1, "%.0f%%", 100.0 * g.project / g.roundMed);
                std::snprintf(s2, sizeof s2, "%.0f%%", 100.0 * (g.project + g.final) / g.roundMed);
                md << "| " << w.key() << " | " << state << " | " << fmtMs(g.hash) << " | " << fmtMs(g.sort) << " | " << fmtMs(g.cells) << " | " << fmtMs(g.choice)
                   << " | " << fmtMs(g.predict) << " | " << fmtMs(g.project) << " | " << fmtMs(g.final) << " | " << fmtMs(g.roundMed) << " | " << s1 << " | " << s2 << " |\n";
            }
        md << "\n### CPU per stage (" << cpuMax << " / CPU-1, ms, median over rounds)\n\n| workload | state | threads | hash | sort | cells | exit choice | predict | "
              "projection | final | total |\n|---|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|\n";
        for (const Workload& w : sel)
            for (const char* state : { "spawn", "congested" })
                for (int t : { maxThreads, 1 }) {
                    const Agg g = pick(w, "cpu", t, state);
                    if (!g.rounds) continue;
                    md << "| " << w.key() << " | " << state << " | " << t << " | " << fmtMs(g.hash) << " | " << fmtMs(g.sort) << " | " << fmtMs(g.cells) << " | "
                       << fmtMs(g.choice) << " | " << fmtMs(g.predict) << " | " << fmtMs(g.project) << " | " << fmtMs(g.final) << " | " << fmtMs(g.roundMed) << " |\n";
                }
        md << "\n";
    }
    std::fclose(cc);
    md << "## Measurement stability: reference probe (GPU, terrace N = " << PROBE_N << ", spawn snapshot, " << PROBE_STEPS << " steps, start of every round)\n\n";
    if (!probes.empty()) {
        const Stats ps = bench::stats(probes);
        md << "| round | median ms |\n|---:|---:|\n";
        for (size_t i = 0; i < probes.size(); ++i) md << "| " << i << " | " << fmtMs(probes[i]) << " |\n";
        char b[200];
        std::snprintf(b, sizeof b, "\n**Probe coefficient of variation across rounds: %.2f%%** (mean %.4f ms, min %.4f, max %.4f)\n", 100.0 * ps.cv, ps.mean, ps.min, ps.max);
        md << b;
    }
    md << "\n## Workloads\n\n" << snapshotReport;
    md << "\n## Protocol\n\n- Rounds: " << rounds << "; each starts with the probe, then every (workload, state, implementation) cell in an order rotated "
          "between rounds.\n- Steps per cell (warm-up + measured) and rounds: `" << cellsPath.filename().string() << "` (CPU-1 at 65 536 and above: fewer steps "
          "and rounds).\n- GPU warm-up: >= " << GPU_WARMUP_MIN_STEPS << " steps and >= " << GPU_WARMUP_MIN_MS / 1000.0 << " s of sustained load per cell. CPU warm-up: "
       << CPU_WARMUP_STEPS << " steps, or fewer (>= " << CPU_WARMUP_MIN_STEPS << ") once " << CPU_WARMUP_CAP_MS / 1000.0 << " s ran.\n- The GPU's physics split: "
          "timestamps in CrowdSim's dispatch hook (after the cells pass, the exit choice's last dispatch, the predict pass, the projection's last iteration, "
          "the final pass); the ring's physics interval = their sum.\n- Elapsed: " << std::lround(elapsedS / 60.0) << " min.\n\n```\n" << selfCheckReport << "```\n";
    md << "\n## Metadata\n\n| key | value |\n|---|---|\n";
    md << "| run_id | " << meta.runId << " |\n| timestamp | " << meta.timestamp << " |\n| git commit | " << meta.commitFull << " |\n| git dirty | " << meta.dirty
       << " (at build time) |\n| build | " << meta.build << " |\n| simulation core flags | `" << meta.flags << "` |\n| clock note | " << meta.clockNote << " |\n"
       << "| GPU (GL_RENDERER) | " << meta.gpu << " |\n| driver (GL_VERSION) | " << meta.driver << " |\n| CPU | " << meta.cpu << " |\n| logical cores | "
       << meta.logicalCores << " |\n| OpenMP max threads | " << meta.ompMaxThreads << " |\n| CPU schedule | " << meta.schedule << " |\n| CPU sort mode | counting |\n"
       << "| safety metrics | off |\n| process QoS | " << meta.qos << " |\n";
    std::printf("done in %.1f min: %s, %s, %s\n", elapsedS / 60.0, csvPath.string().c_str(), cellsPath.string().c_str(), mdPath.string().c_str());
    return 0;
}

// CPU thread scaling on a venue ('scaling --venue V'): snapshot mode on the thesis snapshots, the thread order rotated between rounds
int cmdScalingVenue(const Args& a) {
    const std::string vn = a.get("venue", "M");
    const Workload w{ vn, bench::venueBufferN(vn) };
    if (!w.n) throw std::runtime_error("scaling --venue: S, M or L");
    const std::vector<std::string> states = bench::parseList(a.get("states", "congested"));
    const std::vector<int> threadList = bench::parseIntList(a.get("threads", "1,2,4,6,8,12,14,16,20"));
    const int rounds = a.getInt("rounds", 3), steps = a.getInt("steps", 20);
    const fs::path outDir = a.get("out", "out/results/benchmarks/thesis");
    const fs::path snapDir = a.get("snapshots", "out/bench/snapshots_thesis");
    bench::createHiddenContext("benchmark_crowd");
    loadSDFTexture3D(resolveAsset("stadium.sdf"));
    const std::vector<float>& sdf = sdfVolumeCPU();
    Meta meta = makeMeta("cpu_scaling_" + vn, a.get("clock-note", ""));
    fs::create_directories(outDir);
    const fs::path csvPath = outDir / (meta.runId + ".csv");
    std::FILE* csv = std::fopen(csvPath.string().c_str(), "w");
    if (!csv) throw std::runtime_error("cannot write " + csvPath.string());
    std::fprintf(csv, "run_id,timestamp,git_commit,git_dirty,build,cpu,qos,schedule,workload,venue,N,agents,state,threads,round,warmup_steps,measured_steps,"
                      "median_ms,p5_ms,p95_ms,hash_ms,sort_ms,cells_ms,physics_ms,choice_ms,predict_ms,project_ms,final_ms,label\n");
    std::printf("CPU scaling %s | %s | schedule %s | %d rounds x %d steps | %s\n", meta.runId.c_str(), meta.cpu.c_str(), meta.schedule.c_str(), rounds, steps,
                meta.qos.c_str());
    std::vector<Result> results;
    const auto start = Clock::now();
    for (int r = 0; r < rounds; ++r)
        for (const std::string& state : states) {
            const std::vector<GpuBoid> snap = loadSnap(snapDir, w, state);
            for (size_t j = 0; j < threadList.size(); ++j) {
                const int threads = threadList[(j + size_t(r) * 3) % threadList.size()];
                Cell c{ w, "cpu", threads, state, steps, {} };
                Result res = cpuCell(sdf, c, snap);
                res.round = r;
                const Stats st = bench::stats(res.total);
                std::fprintf(csv, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%ld,%s,%d,%d,%d,%d,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f,%s\n", meta.runId.c_str(),
                             meta.timestamp.c_str(), meta.commitFull.c_str(), meta.dirty.c_str(), meta.build.c_str(), bench::csvField(meta.cpu).c_str(),
                             bench::csvField(meta.qos).c_str(), bench::csvField(meta.schedule).c_str(), w.key().c_str(), vn.c_str(), w.n, res.active, state.c_str(),
                             threads, r, res.warmup, steps, st.median, st.p5, st.p95, res.hash, res.sort, res.cells, res.physics, res.choice, res.predict,
                             res.project, res.final, bench::csvField(res.label).c_str());
                std::fflush(csv);
                std::printf("  r%d %s %-9s t=%2d  median %10.3f ms (choice %.3f predict %.3f project %.3f final %.3f)  [%5.0f s]\n", r, w.key().c_str(),
                            state.c_str(), threads, st.median, res.choice, res.predict, res.project, res.final, bench::msSince(start) / 1000.0);
                std::fflush(stdout);
                results.push_back(std::move(res));
            }
        }
    std::fclose(csv);
    std::ofstream md(outDir / (meta.runId + "_summary.md"));
    md << "# CPU thread scaling " << meta.runId << "\n\nCpuCrowdSim on venue " << vn << " at 100% load (" << results.front().active << " agents in N = " << w.n
       << "), the default model, SortMode::Counting, schedule " << meta.schedule << ", snapshot mode (restoreAgentState: the exit choice runs on), steady_clock "
          "ms per step: the median over " << rounds << " rounds of the per-round median (" << steps << " measured steps per round). CPU: " << meta.cpu << " ("
       << meta.logicalCores << " logical cores: 6 P-cores with 2 threads each = 12, plus 8 E-cores). Commit " << meta.commitFull << " (dirty " << meta.dirty << "), "
       << meta.build << ", flags `" << meta.flags << "`, process QoS: " << meta.qos << ". Safety metrics off.\n\n";
    md << "| state | threads | ms/step (min-max of the rounds) | exit choice | predict | projection | final | speedup vs 1 | efficiency |\n"
          "|---|---:|---:|---:|---:|---:|---:|---:|---:|\n";
    for (const std::string& state : states) {
        double base = 0;
        for (int threads : threadList) {
            std::vector<const Result*> sel;
            for (const Result& r : results) if (r.c.state == state && r.c.threads == threads) sel.push_back(&r);
            const Agg g = aggregate(sel);
            if (threads == 1) base = g.roundMed;
            char b[320];
            std::snprintf(b, sizeof b, "| %s | %d | %s (%s-%s) | %s | %s | %s | %s | %.2fx | %.0f%% |\n", state.c_str(), threads, fmtMs(g.roundMed).c_str(),
                          fmtMs(g.roundLo).c_str(), fmtMs(g.roundHi).c_str(), fmtMs(g.choice).c_str(), fmtMs(g.predict).c_str(), fmtMs(g.project).c_str(),
                          fmtMs(g.final).c_str(), base > 0 ? base / g.roundMed : 0.0, base > 0 ? 100.0 * base / g.roundMed / threads : 0.0);
            md << b;
        }
    }
    std::printf("done in %.1f min: %s\n", bench::msSince(start) / 60000.0, csvPath.string().c_str());
    return 0;
}

} // namespace thesis


} // namespace

int main(int argc, char** argv) {
    if (argc < 2) {
        std::fprintf(stderr, "usage: benchmark_crowd run [--quick] [--plan] ... | scaling [--venue S|M|L] ... | thesis [--quick] [--plan] ...\n");
        return 2;
    }
    g_qos = bench::optOutOfPowerThrottling();
    try {
        const std::string cmd = argv[1];
        const Args a(argc, argv, 2);
        g_cpuSchedule = parseSchedule(a.get("cpu-schedule", CpuCrowdSim::scheduleName(CpuCrowdSim::TUNED_SCHEDULE)));
        if (cmd == "run") return cmdRun(a);
        if (cmd == "scaling") return a.has("venue") ? thesis::cmdScalingVenue(a) : cmdScaling(a);
        if (cmd == "thesis") return thesis::cmdThesis(a);
        std::fprintf(stderr, "unknown command %s\n", cmd.c_str());
        return 2;
    } catch (const std::exception& e) {
        std::fprintf(stderr, "FATAL: %s\n", e.what());
        return 1;
    }
}
