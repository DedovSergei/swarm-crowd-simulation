#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>

#include <swarm/build_info.hpp>
#include <swarm/crowd_sim.hpp>
#include <swarm/shader.hpp>
#include <swarm/sim_params.hpp>

#include "viewer/message_box.hpp"
#include "viewer/selftest.hpp"
#include "viewer/timing_cell.hpp"
#include "viewer/viewer.hpp"

// CONFIGURATION
const int DEFAULT_NUM_BOIDS = 4096; // 8192 16384 32768 65536 131072 262144 (--agents N)
static_assert(DEFAULT_NUM_BOIDS >= 256 && (DEFAULT_NUM_BOIDS & (DEFAULT_NUM_BOIDS - 1)) == 0, "agent count must be a power of two >= 256");

struct Options {
    swarm::viewer::ViewerOptions viewer;
    double runSeconds = 0.0;   // > 0: close after this much wall time and print run statistics
    bool exportOnExit = false; // screenshot + top-down heatmap export of the final state
    bool screenshotOnExit = false;   // the screenshot alone
    bool includePanel = false; // --export-on-exit's screenshot includes the panel
    int colour = -1;           // AgentColour, -1: default
    int overlay = -1;          // OverlayMetric, -1: off
    int camera = -1;           // CameraPreset, -1: default
    bool selfTest = false;     // --selftest-ui
    bool noParallelCompile = false;   // --no-parallel-compile (or SWARM_NO_PARALLEL_COMPILE): the fallback of drivers without the extension
    int selfTestSteps = swarm::golden::GOLDEN_STEPS;   // K: the golden state's step count, so the self-test compares it
};

const char* const HELP =
    "SWARM: GPU crowd evacuation simulation and viewer\n"
    "\n"
    "Usage: SWARM [options]\n"
    "\n"
    "Venue and crowd\n"
    "  --venue terrace|S|M|L    the venue (default terrace)\n"
    "  --load X                 seated venue: share of the seats occupied, 0-1 (default 1)\n"
    "  --agents N               terrace: agents, a power of two >= 256 (default 4096)\n"
    "\n"
    "Model of the seated venues (default: the venue's)\n"
    "  --exit-choice nearest|queue-aware\n"
    "  --incline-speed 0|1\n"
    "  --stair-flow off|empirical|conservative\n"
    "\n"
    "Playback and display\n"
    "  --playback X             x real time, 0.1-20 (default 1)\n"
    "  --max-steps-per-frame K  (default 8)\n"
    "  --no-ui                  no control panel\n"
    "  --panel-hidden           start with the panel hidden (F1 shows it)\n"
    "  --colour speed|density|zone\n"
    "  --overlay METRIC         peak-density, density-now, time-los-e, time-los-f, time-crush, mean-speed, exposure, nav-distance\n"
    "  --camera default|top-down|isometric|exit\n"
    "\n"
    "Runs and exports\n"
    "  --run-seconds S          close after S seconds and print run statistics\n"
    "  --screenshot-dir DIR     where exports go (default: a screenshots folder beside the program)\n"
    "  --export-px N            heatmap export, pixels per side, >= 3000 (default 4096)\n"
    "  --export-on-exit         screenshot and heatmap of the final state\n"
    "  --screenshot-on-exit     screenshot of the final state\n"
    "  --include-panel          those screenshots include the panel\n"
    "\n"
    "Checks and diagnostics\n"
    "  --selftest-ui [--selftest-steps K]   hidden window; exit code 0 when all checks pass\n"
    "  --no-parallel-compile    compile one program per frame, as without GL_ARB_parallel_shader_compile\n"
    "  SWARM cell --n N --state S ...       UI timing cell (tools/perf_ab/ab.py)\n"
    "\n"
    "  --help                   this text\n";

Options parseOptions(int argc, char** argv) {
    using namespace swarm::viewer;
    Options o;
    o.viewer.agents = DEFAULT_NUM_BOIDS;
    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i];
        auto value = [&]() -> std::string {
            if (i + 1 >= argc) throw std::runtime_error(arg + " needs a value");
            return argv[++i];
        };
        if (arg == "--agents") o.viewer.agents = std::stoi(value());
        else if (arg == "--venue") o.viewer.venue = value();   // terrace | S | M | L
        else if (arg == "--load") o.viewer.load = std::stod(value());   // a seated venue: the share of seats occupied, 0-1
        else if (arg == "--exit-choice") o.viewer.exitChoice = value();   // nearest | queue-aware (analytic venues)
        else if (arg == "--incline-speed") o.viewer.inclineSpeed = std::stoi(value());   // 0 | 1 (analytic venues)
        else if (arg == "--stair-flow") o.viewer.stairFlow = value();   // off | empirical | conservative (analytic venues)
        else if (arg == "--max-steps-per-frame") o.viewer.maxStepsPerFrame = std::stoi(value());
        else if (arg == "--run-seconds") o.runSeconds = std::stod(value());
        else if (arg == "--playback") o.viewer.realTime = std::stod(value());
        else if (arg == "--no-ui") o.viewer.ui = false;
        else if (arg == "--panel-hidden") o.viewer.panelVisible = false;
        else if (arg == "--screenshot-dir") o.viewer.screenshotDir = value();
        else if (arg == "--export-px") o.viewer.exportPx = std::stoi(value());
        else if (arg == "--export-on-exit") o.exportOnExit = true;
        else if (arg == "--screenshot-on-exit") o.screenshotOnExit = true;
        else if (arg == "--include-panel") o.includePanel = true;
        else if (arg == "--selftest-ui") o.selfTest = true;
        else if (arg == "--selftest-steps") o.selfTestSteps = std::stoi(value());
        else if (arg == "--no-parallel-compile") o.noParallelCompile = true;
        else if (arg == "--colour") {
            const std::string v = value();
            for (int c = 0; c < 3; ++c)
                if (v == agentColourName(AgentColour(c))) o.colour = c;
            if (o.colour < 0) throw std::runtime_error("--colour: speed, density or zone");
        } else if (arg == "--overlay") {
            const std::string v = value();
            for (int m = 0; m < int(OverlayMetric::Count); ++m)
                if (v == overlayInfo(OverlayMetric(m)).fileTag) o.overlay = m;
            if (o.overlay < 0) throw std::runtime_error("--overlay: unknown metric " + v);
        } else if (arg == "--camera") {
            const std::string v = value();
            const char* names[] = { "default", "top-down", "isometric", "exit" };
            for (int c = 0; c < 4; ++c)
                if (v == names[c]) o.camera = c;
            if (o.camera < 0) throw std::runtime_error("--camera: default, top-down, isometric or exit");
        } else throw std::runtime_error("unknown option " + arg + " (SWARM --help lists the options)");
    }
    if (o.viewer.maxStepsPerFrame < 1) throw std::runtime_error("--max-steps-per-frame must be >= 1");
    if (o.viewer.exportPx < 3000) throw std::runtime_error("--export-px must be >= 3000");
    return o;
}

// The process's start (main's first line), for the startup report
static std::chrono::steady_clock::time_point g_processStart;
static double secondsSinceStart() { return std::chrono::duration<double>(std::chrono::steady_clock::now() - g_processStart).count(); }

// The program binary cache (swarm/shader.hpp): off unless SWARM_SHADER_CACHE=<dir> (on AMD 26.10.1 a binary loads no faster than
// it compiles; the driver's own cache makes warm starts fast)
static void enableProgramCache() {
    const std::filesystem::path dir = swarm::programCacheDirFromEnv();
    swarm::setProgramCache(dir);
    std::printf("program binary cache: %s%s\n", dir.empty() ? "off (the default; SWARM_SHADER_CACHE=<dir> turns it on)" : dir.string().c_str(),
                std::getenv("SWARM_SHADER_NONCE") ? " | SWARM_SHADER_NONCE set (every source-keyed cache misses)" : "");
}

static void printProgramStats(const char* when) {
    const swarm::ProgramCacheStats s = swarm::programCacheStats();
    std::printf("startup: %s after %.2f s; programs compiled %d (%.2f s), loaded from the cache %d (%.2f s), stored %d, rejected %d | %s | %s\n", when,
                secondsSinceStart(), s.compiled, s.compileSeconds, s.loaded, s.loadSeconds, s.stored, s.rejected,
                reinterpret_cast<const char*>(glGetString(GL_RENDERER)), reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    std::fflush(stdout);
}

static int run(const Options& opts) {
    enableProgramCache();
    const char* noParallel = std::getenv("SWARM_NO_PARALLEL_COMPILE");
    const bool forceSerialCompile = opts.noParallelCompile || (noParallel && *noParallel && std::string(noParallel) != "0");
    if (opts.selfTest) {   // prints its own header
        GLFWwindow* hidden = swarm::viewer::createViewerWindow(false, true);
        glfwSwapInterval(0);
        std::printf("parallel shader compile: %s\n", swarm::viewer::configureParallelShaderCompile(forceSerialCompile).c_str());
        swarm::viewer::SelfTestOptions st;
        st.agents = opts.viewer.agents;
        st.steps = opts.selfTestSteps;
        st.outDir = opts.viewer.screenshotDir;
        const int rc = swarm::viewer::runSelfTestUi(hidden, st);
        glfwTerminate();
        return rc;
    }
    std::printf("SWARM | commit %s (dirty %s) | %s\n", swarm::buildinfo::gitCommit(), swarm::buildinfo::gitDirtyField(),
                swarm::buildinfo::buildConfig());
    GLFWwindow* window = swarm::viewer::createViewerWindow(false, false, true);   // shown once the Viewer's capability check has passed
    glfwSwapInterval(0);
    std::printf("parallel shader compile: %s\n", swarm::viewer::configureParallelShaderCompile(forceSerialCompile).c_str());

    {
        swarm::viewer::ViewerOptions vo = opts.viewer;
        vo.asyncLoading = true;   // the start and every restart load behind a loading screen: the window keeps responding
        swarm::viewer::Viewer viewer(window, vo);
        glfwShowWindow(window);
        if (opts.colour >= 0) viewer.setAgentColour(swarm::viewer::AgentColour(opts.colour));
        if (opts.overlay >= 0) viewer.setOverlay(true, swarm::viewer::OverlayMetric(opts.overlay));
        if (opts.camera >= 0) viewer.applyPreset(swarm::viewer::CameraPreset(opts.camera));

        // Run statistics (--run-seconds) over the whole run, from the first frame with the venue ready
        double lastTime = glfwGetTime();
        double runStart = -1.0;
        bool firstStepReported = false;
        while (!glfwWindowShouldClose(window)) {
            const double now = glfwGetTime();
            const double wallDelta = now - lastTime;   // stalls, drags, minimize: clamped by the clock
            lastTime = now;
            if (runStart < 0.0 && !viewer.loading()) {
                runStart = now;
                printProgramStats("viewer ready (venue, programs, navigation caches)");
            }
            if (opts.runSeconds > 0.0 && runStart >= 0.0 && now - runStart >= opts.runSeconds) glfwSetWindowShouldClose(window, true);
            viewer.frame(wallDelta);
            if (!firstStepReported && viewer.stepsTaken() > 0) {   // the first frame that advanced the simulation
                firstStepReported = true;
                printProgramStats("first simulated frame");
            }
        }

        if (viewer.loading() || runStart < 0.0) {   // closed while loading: there is no run to report or export
            if (opts.runSeconds > 0.0 || opts.exportOnExit || opts.screenshotOnExit)
                std::printf("closed while loading: no run statistics, no exports\n");
        } else if (opts.runSeconds > 0.0) {
            const double wall = lastTime - runStart;
            const swarm::FixedStepClock& clock = viewer.clock();
            const uint64_t frames = viewer.framesRendered(), steps = viewer.stepsTaken();
            std::printf("run: %d agents | %.2f s wall | %llu frames | mean FPS %.1f | mean steps/frame %.3f | sim/real %.4f model units/s "
                        "= %.4gx real time (requested %.4gx = playback %.4g) | droppedTime %.6f model units | maxStepsPerFrame %d | VSync %s\n",
                        viewer.sim().numBoids(), wall, (unsigned long long)frames, frames / wall, double(steps) / double(frames),
                        double(steps) * clock.dt / wall, double(steps) * swarm::DT_REAL_S / wall, viewer.realTime(), clock.playbackRate,
                        clock.droppedTime, clock.maxStepsPerFrame, viewer.vsync() ? "on" : "off");
            viewer.printRunMetrics();
        }
        if (!viewer.loading() && runStart >= 0.0) {
            if (opts.screenshotOnExit && !opts.exportOnExit) viewer.takeScreenshot(opts.includePanel);
            if (opts.exportOnExit) {
                viewer.takeScreenshot(opts.includePanel);
                viewer.takeHeatmapExport();
            }
        }
    }
    glfwTerminate();
    return 0;
}

int main(int argc, char** argv) {
    g_processStart = std::chrono::steady_clock::now();
    // A person started it: a fatal error also shows a message box (a double-clicked console closes with the process). Scripts drive the
    // self-test and the timing cell: they must never wait for a click.
    bool automated = argc >= 2 && std::string(argv[1]) == "cell";
    for (int i = 1; i < argc; ++i) automated |= std::string(argv[i]) == "--selftest-ui";
    const auto fatal = [&](const std::string& what) {
        std::cerr << "Fatal: " << what << std::endl;
        glfwTerminate();   // the window goes first: the box must not sit on a frozen window
        if (!automated) swarm::viewer::showFatalMessage(what);
        return EXIT_FAILURE;
    };
    try {
        if (argc >= 2 && std::string(argv[1]) == "cell") return swarm::viewer::runTimingCell(argc, argv);
        for (int i = 1; i < argc; ++i)
            if (std::string(argv[i]) == "--help" || std::string(argv[i]) == "-h") {
                std::fputs(HELP, stdout);
                return EXIT_SUCCESS;
            }
        return run(parseOptions(argc, argv));
    } catch (const std::exception& e) {
        return fatal(e.what());
    } catch (...) {
        return fatal("an unknown error");
    }
}
