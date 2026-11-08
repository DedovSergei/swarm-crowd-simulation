// A/B perf harness (see README.md): times CrowdSim::step on fixed inputs, so two builds of the
// pipeline process exactly the same work.
//   bench cell --n <N> --state <spawn|congested> [--label L] [--snapshots out/bench/snapshots]
//              [--warm-ms 2000] [--steps S] [--shaders dir] [--continuous] [--trace] [--metrics]
//     Protocol (ab.py drives it): one (N, state) cell in snapshot mode. The snapshot is restored
//       into both ping-pong halves by a GPU-side copy before every step, outside the timestamps (as
//       benchmark_crowd and gpu_diag). Warm-up >= warm-ms and >= 10 steps, then S timed steps on CrowdSim's
//       query ring (default 300 / 200 / 100 / 50 at N <= 16384 / 65536 / 131072 / larger). Prints one
//       "CELL key=value ..." line: per-pass medians (GPU execution ms), the build-time commit and dirty
//       flag of the engine build it links, and the FNV-1a 64 of the state one step after the snapshot
//       (so an A/B also compares the results of both builds).
//     --metrics (or SWARM_BENCH_METRICS=1): the safety metrics' two passes after every step,
//       timed by two timestamps around them; total_ms then includes them, metrics_ms is their median.
//     For ab.py labels: SWARM_BENCH_SNAPSHOTS=<dir> replaces --snapshots (each model on the snapshots
//       its own build wrote), SWARM_BENCH_PROJ_ITERS=K sets CrowdSim::setProjectionIterations (0: projection
//     off; an error on engine builds without it).
//     SWARM_BENCH_VENUE=S (or --venue S) runs venue S (routed by its navigation field) on its own snapshots
//     (SWARM_BENCH_SNAPSHOTS: a directory 'bench snapshots ... --venue S' wrote); engine builds without it: an error.
//     The restore copies the agent state only, so an analytic venue's exit choice (assignments, counts,
//       the choice step) runs on through the warm-up, whose length is a time; the hashed step (and --continuous's first)
//       therefore starts from CrowdSim::upload, which also resets the choice: the hash is the same in every process.
//   bench snapshots <dir> <n,n,...> [--venue S]   write the 'cell' inputs of THIS build's model:
//                                                 spawn_<n>.bin (spawnBleacherCrowd; venue S: every seat occupied,
//                                                 spawnSeatedCrowd) and congested_<n>.bin (the GPU state after
//                                                 bench::CONGESTED_STEPS steps), as benchmark_crowd
//   bench snapshot <dir>                          (older protocol) write spawn_<n>.bin and snap_<n>.bin
//                                                 (mid-evacuation) for n = 4096, 65536
//   bench time <dir> <label> [shaderDir] [onlyN] [onlyKind]
//                                                 (older protocol) time both inputs for both sizes
// Builds against any version with CrowdSim::beginTimingRing() ('cell') or currentStateBuffer() ('snapshot', 'time').
// The commit comes from that version's swarm_build_info ("unknown" without it). Assets (stadium.sdf, shaders) resolve
// next to the executable unless a shader directory is given.
#include "../benchmark/bench_common.hpp"
#include "../golden_state.hpp"

#include <swarm/assets.hpp>
#include <swarm/crowd_sim.hpp>
#include <swarm/sdf.hpp>

// Safety metrics: 'cell --metrics' (or SWARM_BENCH_METRICS=1 in the environment, for ab.py labels)
// runs CrowdMetrics::afterStep after every step and times it with timestamps of its own. Engine builds
// without metrics: the option is an error.
#if __has_include(<swarm/metrics.hpp>)
#include <swarm/metrics.hpp>
#define SWARM_BENCH_HAS_METRICS 1
#endif
// The venue's capacity label on the CELL line; "unknown" in engine builds without it
#if __has_include(<swarm/venue_capacity.hpp>)
#include <swarm/venue_capacity.hpp>
#define SWARM_BENCH_CAPACITY(n) swarm::venue::label(n)
#else
#define SWARM_BENCH_CAPACITY(n) std::string("unknown")
#endif

// Venue S: builds with the navigation field (venue S routed); otherwise the terrace only
#if __has_include(<swarm/nav_field.hpp>)
#include <swarm/venue.hpp>
#define SWARM_BENCH_HAS_VENUES 1
#endif

#include <cstdlib>
#include <memory>
using namespace swarm;

// The venue of 'cell' and 'snapshots': SWARM_BENCH_VENUE (ab.py labels) or --venue; "terrace" by default
static std::string benchVenueName(const bench::Args& a) {
    const char* env = std::getenv("SWARM_BENCH_VENUE");
    return env && *env ? std::string(env) : a.get("venue", "terrace");
}
#ifdef SWARM_BENCH_HAS_VENUES
static const Venue& benchVenue(const bench::Args& a) { return venueByName(benchVenueName(a)); }
#endif

static std::vector<GpuBoid> readState(GLuint buf, int n) {
    glMemoryBarrier(GL_BUFFER_UPDATE_BARRIER_BIT);
    std::vector<GpuBoid> s(n);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, buf);
    glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, n * sizeof(GpuBoid), s.data());
    return s;
}
static void save(const std::string& path, const std::vector<GpuBoid>& s) {
    std::ofstream(path, std::ios::binary).write(reinterpret_cast<const char*>(s.data()), s.size() * sizeof(GpuBoid));
}
static bool load(const std::string& path, int n, std::vector<GpuBoid>& s) {
    s.assign(n, GpuBoid{});
    std::ifstream in(path, std::ios::binary);
    in.read(reinterpret_cast<char*>(s.data()), n * sizeof(GpuBoid));
    return bool(in);
}

// The snapshot, resident on the GPU; restore() copies it into both ping-pong halves
struct Pristine {
    GLuint buf = 0;
    GLsizeiptr bytes = 0;
    explicit Pristine(const std::vector<GpuBoid>& s) : bytes(GLsizeiptr(s.size() * sizeof(GpuBoid))) {
        glGenBuffers(1, &buf);
        glBindBuffer(GL_COPY_READ_BUFFER, buf);
        glBufferData(GL_COPY_READ_BUFFER, bytes, s.data(), GL_STATIC_DRAW);
    }
    ~Pristine() { glDeleteBuffers(1, &buf); }
    void restore(const CrowdSim& sim) const {
        for (int i = 0; i < 2; ++i) {
            glMemoryBarrier(GL_BUFFER_UPDATE_BARRIER_BIT);
            glBindBuffer(GL_COPY_READ_BUFFER, buf);
            glBindBuffer(GL_COPY_WRITE_BUFFER, sim.boidBuffer(i));
            glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, bytes);
        }
    }
};

// The 'cell' inputs of this build's model (each model of an A/B across a model change on its own snapshots)
static int cmdSnapshots(int argc, char** argv) {
    if (argc < 4) throw std::runtime_error("usage: bench snapshots <dir> <n,n,...>");
    const std::filesystem::path dir = argv[2];
    std::filesystem::create_directories(dir);
    const bench::Args a(argc, argv, 4);
    bench::createHiddenContext("bench");
    const GLuint sdf = loadSDFTexture3D(resolveAsset("stadium.sdf"));
    if (!sdf) throw std::runtime_error("cannot load stadium.sdf");
    for (const std::string& t : bench::parseList(argv[3])) {
        const int n = std::stoi(t);
#ifdef SWARM_BENCH_HAS_VENUES
        const Venue& v = benchVenue(a);
        const std::vector<GpuBoid> spawn = v.seated() ? spawnSeatedCrowd(v, n, 1.0) : spawnBleacherCrowd(n);
        bench::saveSnapshot(bench::snapshotPath(dir, "spawn", n), spawn);
        CrowdSim sim(resolveAsset("shaders"), n, v);
#else
        if (benchVenueName(a) != "terrace") throw std::runtime_error("--venue: this engine build has no navigation field");
        const std::vector<GpuBoid> spawn = spawnBleacherCrowd(n);
        bench::saveSnapshot(bench::snapshotPath(dir, "spawn", n), spawn);
        CrowdSim sim(resolveAsset("shaders"), n);
#endif
        sim.upload(spawn);
        for (int i = 0; i < bench::CONGESTED_STEPS; ++i) sim.step(sdf);
        const std::vector<GpuBoid> s = readState(sim.currentStateBuffer(), n);
        bench::saveSnapshot(bench::snapshotPath(dir, "congested", n), s);
        const long active = long(std::count_if(s.begin(), s.end(), [](const GpuBoid& b) { return b.position.w != 0.0f; }));
        std::printf("snapshots n=%d: spawn, congested after %d steps (%ld active), commit %s dirty %s\n", n, bench::CONGESTED_STEPS, active,
                    bench::gitCommit().c_str(), bench::gitDirty().c_str());
    }
    return 0;
}

static int cmdCell(int argc, char** argv) {
    const bench::Args a(argc, argv, 2);
    const int n = a.getInt("n", 0);
    const std::string state = a.get("state", "");
    if (n <= 0 || state.empty()) throw std::runtime_error("cell: --n and --state are required");
    const std::string label = a.get("label", "?");
    const double warmMs = a.getInt("warm-ms", 2000);
    const int steps = a.getInt("steps", n <= 16384 ? 300 : n <= 65536 ? 200 : n <= 131072 ? 100 : 50);
    // --continuous: the timed steps run back to back from ONE restore of the snapshot (a trajectory of 'steps' steps,
    // as the application steps), instead of a restore before every step. Both modes do identical work in every build
    // whose results are bit-identical.
    const bool continuous = a.has("continuous");
    const bool trace = a.has("trace");   // also print every timed step's hash / physics / total (TRACE lines)
    const char* envMetrics = std::getenv("SWARM_BENCH_METRICS");
    const bool useMetrics = a.has("metrics") || (envMetrics && std::string(envMetrics) == "1");
    const char* envSnapshots = std::getenv("SWARM_BENCH_SNAPSHOTS");
    const std::string snapshots = envSnapshots && *envSnapshots ? std::string(envSnapshots) : a.get("snapshots", "out/bench/snapshots");
    const char* envIters = std::getenv("SWARM_BENCH_PROJ_ITERS");
    const bool setIters = envIters && *envIters;
    const std::string qos = bench::optOutOfPowerThrottling();

    bench::createHiddenContext("bench");
    const GLuint sdf = loadSDFTexture3D(resolveAsset("stadium.sdf"));
    if (!sdf) throw std::runtime_error("cannot load stadium.sdf");
    const std::filesystem::path shaderDir = a.has("shaders") ? std::filesystem::path(a.get("shaders", "")) : resolveAsset("shaders");
    const std::vector<GpuBoid> in = bench::loadSnapshot(snapshots, state, n);

#ifdef SWARM_BENCH_HAS_VENUES
    const Venue& venue = benchVenue(a);
    CrowdSim sim(shaderDir, n, venue);
#else
    if (benchVenueName(a) != "terrace") throw std::runtime_error("SWARM_BENCH_VENUE: this engine build has no navigation field");
    CrowdSim sim(shaderDir, n);
#endif
    std::string projIters = "-";
#ifdef SWARM_CROWDSIM_HAS_PROJECTION
    if (setIters) sim.setProjectionIterations(std::atoi(envIters));
    projIters = std::to_string(sim.projectionIterations());
#else
    if (setIters) throw std::runtime_error("SWARM_BENCH_PROJ_ITERS: this engine build has no projection");
#endif
#ifdef SWARM_BENCH_HAS_METRICS
    std::unique_ptr<metrics::CrowdMetrics> met;
#ifdef SWARM_BENCH_HAS_VENUES
    if (useMetrics)
        met = venue.seated() ? std::make_unique<metrics::CrowdMetrics>(shaderDir, n, metrics::computeMetricVenueSeated(venue.layout).cellInfo(), &venue)
                             : std::make_unique<metrics::CrowdMetrics>(shaderDir, n, metrics::computeMetricVenue(sdfVolumeCPU()).cellInfo());
#else
    if (useMetrics) met = std::make_unique<metrics::CrowdMetrics>(shaderDir, n, metrics::computeMetricVenue(sdfVolumeCPU()).cellInfo());
#endif
#else
    if (useMetrics) throw std::runtime_error("cell --metrics: this engine build has no safety metrics");
#endif
    // Metrics ON: afterStep after every step; the timed steps stamp two timestamps around it (outside CrowdSim's
    // ring, which ends after physics). Metrics OFF issues none of these commands.
    std::vector<GLuint> mq(useMetrics ? size_t(steps) * 2 : 0);
    if (!mq.empty()) glGenQueries(GLsizei(mq.size()), mq.data());
    auto metricsStep = [&](int timedIndex) {
#ifdef SWARM_BENCH_HAS_METRICS
        if (!met) return;
        if (timedIndex >= 0) glQueryCounter(mq[size_t(timedIndex) * 2], GL_TIMESTAMP);
        met->afterStep(sim);
        if (timedIndex >= 0) glQueryCounter(mq[size_t(timedIndex) * 2 + 1], GL_TIMESTAMP);
#else
        (void)timedIndex;
#endif
    };
    const Pristine p(in);
    const auto t0 = bench::Clock::now();
    for (int i = 0; i < 10 || bench::msSince(t0) < warmMs; ++i) {
        p.restore(sim);
        sim.step(sdf);
        metricsStep(-1);
        if (i % 20 == 19) glFinish();
    }
    glFinish();
    sim.beginTimingRing(steps);
    for (int i = 0; i < steps; ++i) {
        if (continuous && i == 0) sim.upload(in);   // a fresh run (upload resets the exit choice)
        else if (!continuous) p.restore(sim);
        sim.step(sdf);
        metricsStep(i);
    }
    const std::vector<CrowdSim::PassTimesMs> t = sim.readTimingRing();
    std::vector<double> h, s, c, ph, tot, mt;
    for (size_t i = 0; i < t.size(); ++i) {
        const CrowdSim::PassTimesMs& x = t[i];
        double m = 0.0;
        if (!mq.empty()) {
            GLuint64 a0 = 0, a1 = 0;
            glGetQueryObjectui64v(mq[i * 2], GL_QUERY_RESULT, &a0);
            glGetQueryObjectui64v(mq[i * 2 + 1], GL_QUERY_RESULT, &a1);
            m = double(a1 - a0) * 1e-6;
        }
        h.push_back(x.hash); s.push_back(x.sort); c.push_back(x.cells); ph.push_back(x.physics); tot.push_back(x.total + m); mt.push_back(m);
    }
    if (!mq.empty()) glDeleteQueries(GLsizei(mq.size()), mq.data());
    // Untimed: the state one step after the snapshot (every timed step started from the snapshot), or 'steps' steps
    // after it (--continuous)
    // The snapshot mode's hashed step is a fresh run's first step (upload resets the exit choice; the terrace: the same
    // step as a restore)
    if (!continuous) {
        sim.upload(in);
        sim.step(sdf);
    }
    const uint64_t stateHash = golden::stateHash(readState(sim.currentStateBuffer(), n));

    if (trace)
        for (size_t i = 0; i < t.size(); ++i)
            std::printf("TRACE step=%zu hash_ms=%.5f sort_ms=%.5f physics_ms=%.5f total_ms=%.5f metrics_ms=%.5f\n", i, t[i].hash, t[i].sort,
                        t[i].physics, tot[i], mt[i]);
    std::printf("META label=%s gpu=\"%s\" driver=\"%s\" qos=\"%s\" shaders=\"%s\" snapshots=\"%s\" proj_iters=%s venue=%s\n", label.c_str(),
                bench::glRenderer().c_str(), bench::glDriver().c_str(), qos.c_str(), shaderDir.string().c_str(), snapshots.c_str(), projIters.c_str(),
                benchVenueName(a).c_str());
    std::printf("CELL label=%s n=%d state=%s mode=%s steps=%d commit=%s dirty=%s hash_ms=%.5f sort_ms=%.5f cells_ms=%.5f physics_ms=%.5f total_ms=%.5f "
                "state_fnv=%016llx metrics=%s metrics_ms=%.5f capacity=\"%s\"\n",
                label.c_str(), n, state.c_str(), continuous ? "continuous" : "snapshot", int(t.size()), bench::gitCommit().c_str(),
                bench::gitDirty().c_str(), bench::median(h), bench::median(s), bench::median(c), bench::median(ph), bench::median(tot),
                (unsigned long long)stateHash, useMetrics ? "on" : "off", bench::median(mt),
#ifdef SWARM_BENCH_HAS_VENUES
                (venue.seated() ? swarm::venue::label(int(bench::countActive(in)), swarm::venue::capacityOf(venue)) : SWARM_BENCH_CAPACITY(n)).c_str());
#else
                SWARM_BENCH_CAPACITY(n).c_str());
#endif
    std::fflush(stdout);
    return 0;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::fprintf(stderr, "usage: bench cell --n N --state S [...] | bench snapshots <dir> <n,...> | bench snapshot <dir> | bench time <dir> <label> "
                             "[shaderDir] [onlyN] [onlyKind]\n");
        return 2;
    }
    std::string mode = argv[1];
    try {
        if (mode == "cell") return cmdCell(argc, argv);
        if (mode == "snapshots") return cmdSnapshots(argc, argv);
    } catch (const std::exception& e) {
        std::fprintf(stderr, "FATAL: %s\n", e.what());
        return 1;
    }
    if (argc < 3) {
        std::fprintf(stderr, "usage: bench snapshot <dir> | bench time <dir> <label> [shaderDir] [onlyN] [onlyKind]\n");
        return 2;
    }
    std::string dir = argv[2];
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    GLFWwindow* w = glfwCreateWindow(64, 64, "bench", nullptr, nullptr);
    glfwMakeContextCurrent(w);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    GLuint sdf = loadSDFTexture3D(resolveAsset("stadium.sdf"));
    std::filesystem::path shaderDir = argc > 4 && argv[4][0] ? std::filesystem::path(argv[4]) : resolveAsset("shaders");
    const int onlyN = argc > 5 ? std::atoi(argv[5]) : 0;
    const std::string onlyKind = argc > 6 ? argv[6] : "";

    if (mode == "snapshot") {
        std::filesystem::create_directories(dir);
        for (auto [n, steps] : { std::pair<int, int>{ 4096, 250 }, { 65536, 150 } }) {
            auto spawn = spawnBleacherCrowd(n);
            save(dir + "/spawn_" + std::to_string(n) + ".bin", spawn);
            CrowdSim sim(shaderDir, n);
            sim.upload(spawn);
            for (int i = 0; i < steps; ++i) sim.step(sdf);
            auto s = readState(sim.currentStateBuffer(), n);
            int active = int(std::count_if(s.begin(), s.end(), [](const GpuBoid& b) { return b.position.w != 0.0f; }));
            save(dir + "/snap_" + std::to_string(n) + ".bin", s);
            std::printf("snapshot n=%d after %d steps: %d active\n", n, steps, active);
        }
        return 0;
    }

    const char* label = argc > 3 ? argv[3] : "?";
    for (int n : { 4096, 65536 }) {
        for (const char* kind : { "spawn", "snap" }) {
            if ((onlyN && n != onlyN) || (!onlyKind.empty() && onlyKind != kind)) continue;
            std::vector<GpuBoid> state;
            const std::string file = dir + "/" + kind + "_" + std::to_string(n) + ".bin";
            if (!load(file, n, state)) { std::fprintf(stderr, "cannot read %s (run 'bench snapshot' first)\n", file.c_str()); return 1; }
            CrowdSim sim(shaderDir, n);
            sim.setTimingEnabled(true);
            for (int i = 0; i < 100; ++i) { sim.upload(state); sim.step(sdf); sim.readTimings(); }
            const int runs = 500;
            std::vector<double> totals, physics;
            for (int i = 0; i < runs; ++i) {
                sim.upload(state);
                sim.step(sdf);
                auto t = sim.readTimings();
                totals.push_back(t.total);
                physics.push_back(t.physics);
            }
            std::sort(totals.begin(), totals.end());
            std::sort(physics.begin(), physics.end());
            std::printf("%-8s n=%5d %-5s physics min %.4f med %.4f | total min %.4f med %.4f\n", label, n, kind,
                        physics[0], physics[runs / 2], totals[0], totals[runs / 2]);
        }
    }
    return 0;
}
