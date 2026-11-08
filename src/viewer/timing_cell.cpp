#include "benchmark/bench_common.hpp"   // first: windows.h before glad (power throttling opt-out)
#include "golden_state.hpp"

#include "viewer/timing_cell.hpp"
#include "viewer/viewer.hpp"

#include <swarm/crowd_sim.hpp>

#include <cstdlib>

namespace swarm::viewer {

namespace {

// The snapshot, resident on the GPU; restore() copies it into both ping-pong halves (as bench.cpp's Pristine)
struct Pristine {
    GLuint buf = 0;
    GLsizeiptr bytes = 0;
    explicit Pristine(const std::vector<GpuBoid>& s) : bytes(GLsizeiptr(s.size() * sizeof(GpuBoid))) {
        glGenBuffers(1, &buf);
        glBindBuffer(GL_COPY_READ_BUFFER, buf);
        glBufferData(GL_COPY_READ_BUFFER, bytes, s.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_COPY_READ_BUFFER, 0);
    }
    ~Pristine() { glDeleteBuffers(1, &buf); }
    void restore(const CrowdSim& sim) const {
        for (int i = 0; i < 2; ++i) {
            glMemoryBarrier(GL_BUFFER_UPDATE_BARRIER_BIT);
            glBindBuffer(GL_COPY_READ_BUFFER, buf);
            glBindBuffer(GL_COPY_WRITE_BUFFER, sim.boidBuffer(i));
            glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, bytes);
        }
        glBindBuffer(GL_COPY_READ_BUFFER, 0);
        glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
    }
};

bool envOn(const char* name) {
    const char* v = std::getenv(name);
    return v && std::string(v) == "1";
}

} // namespace

int runTimingCell(int argc, char** argv) {
    const bench::Args a(argc, argv, 2);
    const int n = a.getInt("n", 0);
    const std::string state = a.get("state", "");
    if (n <= 0 || state.empty()) throw std::runtime_error("cell: --n and --state are required");
    const std::string label = a.get("label", "?");
    const double warmMs = a.getInt("warm-ms", 2000);
    const int steps = a.getInt("steps", n <= 16384 ? 300 : n <= 65536 ? 200 : n <= 131072 ? 100 : 50);
    const bool continuous = a.has("continuous");
    const bool trace = a.has("trace");
    const bool ui = a.has("ui") ? a.get("ui", "off") == "on" : envOn("SWARM_VIEWER_UI");
    const bool overlay = a.has("overlay") || envOn("SWARM_VIEWER_OVERLAY");
    const std::string qos = bench::optOutOfPowerThrottling();

    GLFWwindow* window = createViewerWindow(true, false);
    glfwSwapInterval(0);
    const std::vector<GpuBoid> in = bench::loadSnapshot(a.get("snapshots", "out/bench/snapshots"), state, n);
    int frames = 0;
    std::vector<CrowdSim::PassTimesMs> t;
    uint64_t stateHash = 0;
    {
        ViewerOptions vo;
        vo.agents = n;
        vo.ui = ui;
        vo.panelVisible = ui;
        Viewer v(window, vo);
        if (overlay) {
            v.setAgentColour(AgentColour::Density);
            v.setOverlay(true, OverlayMetric::PeakDensity);
        }
        const Pristine p(in);
        auto restore = [&]() { p.restore(v.sim()); };
        const auto t0 = bench::Clock::now();
        for (int i = 0; i < 10 || bench::msSince(t0) < warmMs; ++i) {
            v.frameFixed(1, restore);
            ++frames;
            if (i % 20 == 19) glFinish();
        }
        glFinish();
        v.sim().beginTimingRing(steps);
        for (int i = 0; i < steps; ++i) {
            if (i == 0 || !continuous) v.frameFixed(1, restore);
            else v.frameFixed(1);
            ++frames;
        }
        t = v.sim().readTimingRing();
        // Untimed: the state one step after the snapshot, or 'steps' steps after it (--continuous)
        stateHash = golden::stateHash(bench::readBuffer<GpuBoid>(v.sim().currentStateBuffer(), size_t(n)));
    }
    std::vector<double> h, s, c, ph, tot;
    for (const CrowdSim::PassTimesMs& x : t) {
        h.push_back(x.hash); s.push_back(x.sort); c.push_back(x.cells); ph.push_back(x.physics); tot.push_back(x.total);
    }
    if (trace)
        for (size_t i = 0; i < t.size(); ++i)
            std::printf("TRACE step=%zu hash_ms=%.5f sort_ms=%.5f physics_ms=%.5f total_ms=%.5f\n", i, t[i].hash, t[i].sort, t[i].physics,
                        t[i].total);
    std::printf("META label=%s gpu=\"%s\" driver=\"%s\" qos=\"%s\" harness=\"SWARM cell (viewer frame loop)\"\n", label.c_str(),
                bench::glRenderer().c_str(), bench::glDriver().c_str(), qos.c_str());
    std::printf("CELL label=%s n=%d state=%s mode=%s steps=%d commit=%s dirty=%s hash_ms=%.5f sort_ms=%.5f cells_ms=%.5f physics_ms=%.5f "
                "total_ms=%.5f state_fnv=%016llx ui=%s overlay=%s frames=%d\n",
                label.c_str(), n, state.c_str(), continuous ? "continuous" : "snapshot", int(t.size()), bench::gitCommit().c_str(),
                bench::gitDirty().c_str(), bench::median(h), bench::median(s), bench::median(c), bench::median(ph), bench::median(tot),
                (unsigned long long)stateHash, ui ? "on" : "off", overlay ? "on" : "off", frames);
    std::fflush(stdout);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

} // namespace swarm::viewer
