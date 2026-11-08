#include "viewer/viewer.hpp"

#include "viewer/export.hpp"
#include "viewer/legend.hpp"
#include "viewer/palette.hpp"
#include "viewer/scales.hpp"
#include "viewer/scene.hpp"

#include <swarm/assets.hpp>
#include <swarm/async_counters.hpp>
#include <swarm/build_info.hpp>
#include <swarm/crowd_sim.hpp>
#include <swarm/metrics.hpp>
#include <swarm/sdf.hpp>
#include <swarm/sim_params.hpp>
#include <swarm/venue.hpp>
#include <swarm/nav_field.hpp>
#include <swarm/venue_capacity.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glm/gtc/matrix_transform.hpp>

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <exception>
#include <mutex>
#include <thread>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iterator>
#include <sstream>
#include <stdexcept>

namespace swarm::viewer {

namespace {

const char* const KEY_HELP =
    "Esc quit | F1 panel | P pause/resume | N single step (paused) | V VSync | [ ] playback /2 x2 | "
    "W A S D move the orbit centre | 1 default view, 2 top-down, 3 isometric, 4 exit close-up | M agent colour | H heatmap overlay | F12 screenshot | F9 top-down heatmap export | "
    "mouse: left-drag rotate, right-drag pan, wheel zoom";

// Real-time factor <-> the clock's model time units per wall second
double playbackRateFor(double realTime) { return realTime / double(TIME_SCALE_S_PER_UNIT); }

// The smallest "round" axis end >= t (seconds)
float niceAxisEnd(float t) {
    static const float ends[] = { 30, 60, 90, 120, 150, 180, 240, 300, 450, 600, 900, 1200, 1800, 2400, 3600 };
    for (float e : ends)
        if (t <= e) return e;
    return 1800.0f * std::ceil(t / 1800.0f);
}

std::string hexColour(uint32_t hex) {
    char b[8];
    std::snprintf(b, sizeof(b), "#%06x", hex);
    return b;
}

std::string jsonEscape(const std::string& in) {
    std::string out;
    for (char c : in) {
        if (c == '"' || c == '\\') out += '\\';
        out += c;
    }
    return out;
}

// The venue selector's list, in its order
std::array<const Venue*, 4> selectorVenues() { return { &terraceVenue(), &venueS(), &venueM(), &venueL() }; }
const char* selectorName(const Venue& v) { return v.seated() ? v.name : "terrace"; }

// The loading screen's note (AMD 26.10.1: the driver's shader cache is keyed by the program's source and the executable's path)
const char* const FIRST_START_NOTE = "The first start on this PC compiles the shaders and can take several minutes. Later starts take seconds.";

// The largest N the panel offers (the terrace's buffers grow with it), or a larger --agents
int largestAgents(int agents) { return std::max(agents, *std::max_element(std::begin(N_CHOICES), std::end(N_CHOICES))); }

// The context cannot be created: what the driver does offer, read from a default context
std::string noOpenGlContextMessage() {
    std::string offers = "no OpenGL context at all";
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    if (GLFWwindow* probe = glfwCreateWindow(64, 64, "probe", nullptr, nullptr)) {
        glfwMakeContextCurrent(probe);
        using GetString = const GLubyte*(APIENTRY*)(GLenum);
        if (const GetString get = reinterpret_cast<GetString>(glfwGetProcAddress("glGetString"))) {
            const GLubyte* version = get(GL_VERSION);
            const GLubyte* renderer = get(GL_RENDERER);
            offers = std::string("OpenGL ") + (version ? reinterpret_cast<const char*>(version) : "?") + " on " + (renderer ? reinterpret_cast<const char*>(renderer) : "?");
        }
        glfwMakeContextCurrent(nullptr);
        glfwDestroyWindow(probe);
    }
    return "SWARM needs OpenGL " + std::to_string(GL_REQUIRED_MAJOR) + "." + std::to_string(GL_REQUIRED_MINOR) + " (core profile). This PC offers " + offers +
           ".\n\nA newer graphics driver may help. On a laptop with two GPUs, choose the faster one for SWARM in the Windows graphics settings.";
}

} // namespace

std::string venueFileName(const Venue& v) { return v.seated() ? std::string("venue_") + v.name : std::string("stadium"); }

std::string configureParallelShaderCompile(bool forceOff) {
    bool arb = false, khr = false;
    GLint count = 0;
    glGetIntegerv(GL_NUM_EXTENSIONS, &count);
    for (GLint i = 0; i < count; ++i) {
        const char* e = reinterpret_cast<const char*>(glGetStringi(GL_EXTENSIONS, GLuint(i)));
        arb |= e && std::strcmp(e, "GL_ARB_parallel_shader_compile") == 0;
        khr |= e && std::strcmp(e, "GL_KHR_parallel_shader_compile") == 0;
    }
    using MaxThreads = void(APIENTRY*)(GLuint);
    MaxThreads fn = nullptr;
    if (!forceOff && arb) fn = reinterpret_cast<MaxThreads>(glfwGetProcAddress("glMaxShaderCompilerThreadsARB"));
    if (!forceOff && !fn && khr) fn = reinterpret_cast<MaxThreads>(glfwGetProcAddress("glMaxShaderCompilerThreadsKHR"));
    setParallelShaderCompile(fn);
    if (fn) return std::string("on (") + (arb ? "GL_ARB_parallel_shader_compile" : "GL_KHR_parallel_shader_compile") + ")";
    if (forceOff) return "off (forced: --no-parallel-compile or SWARM_NO_PARALLEL_COMPILE; programs compile one per frame)";
    return "off (the driver has no GL_ARB_ / GL_KHR_parallel_shader_compile; programs compile one per frame)";
}

GpuRequirements venueRequirements(const Venue& v, const ModelOptions& model, int agents) {
    const ModelOptions o = effectiveModelOptions(v, model);
    int n = agents;
    if (v.seated()) {   // as prepareRestart: the smallest power-of-two buffer that holds every seat
        const size_t seats = seated::seats(v.layout).size();
        n = 256;
        while (size_t(n) < seats) n *= 2;
    }
    std::vector<ProgramBindings> programs = CrowdSim::programBindings(v, o);
    for (const ProgramBindings& p : metrics::CrowdMetrics::programBindings(v.seated())) programs.push_back(p);
    for (const ProgramBindings& p : SceneRenderer::programBindings()) programs.push_back(p);
    std::vector<GpuBufferUse> buffers = CrowdSim::bufferUses(v, o, n);
    for (const GpuBufferUse& b : metrics::CrowdMetrics::bufferUses(n, v.metricGridRes)) buffers.push_back(b);
    if (o.exitChoice == ExitChoice::QueueAware) {
        const nav::ChoiceEntryCount count = nav::choiceEntryCountBeforeBuild(v);
        buffers.push_back({ "the exit choice table", int64_t(count.entries * sizeof(GpuNavChoiceCell)), !count.exact });
    }
    return gpuRequirements(programs, buffers);
}

// --- Background loading (Viewer::loading) ---

// What a restart needs, taken on the GL thread when it begins
struct Viewer::RestartInputs {
    const Venue* venue = nullptr;
    int n = 0;                                          // the terrace's N (a seated venue: from its seats)
    double load = 1.0;
    ModelOptions model;
    const std::vector<GpuBoid>* cachedSpawn = nullptr;  // the terrace's spawn of this N, computed before (terraceSpawns_)
    bool needTables = false;                            // the venue's metric table is not computed yet
};

// A restart's CPU results (prepareRestart: no GL call)
struct Viewer::Prepared {
    const Venue* venue = nullptr;
    ModelOptions model;
    int n = 0, population = 0;
    std::vector<GpuBoid> spawn;
    bool newSpawn = false;          // the terrace's spawn, computed here (kept for the next restart)
    bool newTables = false;
    VenueTables tables;             // newTables: the venue's metric table
    std::vector<float> mesh;        // a generated venue's render mesh (venues without an OBJ asset)
};

namespace {
// The loading screen's view of the navigation builds (nav::BuildMonitor): their stage, its fraction, the cancel flag
class LoadMonitor : public nav::BuildMonitor {
public:
    void progress(const std::string& stage, double fraction) override {
        std::lock_guard<std::mutex> lock(m_);
        stage_ = stage;
        fraction_ = fraction;
    }
    bool cancelled() const override { return cancel_.load(); }
    void cancel() { cancel_.store(true); }
    std::pair<std::string, double> current() const {
        std::lock_guard<std::mutex> lock(m_);
        return { stage_, fraction_ };
    }

private:
    mutable std::mutex m_;
    std::string stage_ = "starting";
    double fraction_ = -1.0;
    std::atomic<bool> cancel_{ false };
};
} // namespace

struct Viewer::Loading {
    RestartInputs in;
    bool needScene = false;                // a new venue: its scene too (its programs compiled ahead with the others)
    // Cpu (1), Compile (2: the shaders), Link (3: one more drawn frame, then fenced: nothing drawn), WarmUp (4: fenced: nothing drawn)
    enum class Phase { Cpu, Compile, Link, WarmUp } phase = Phase::Cpu;
    bool linksIssued = false;
    // (1) the worker thread: CPU work only
    std::thread worker;
    std::atomic<bool> cpuDone{ false };
    std::exception_ptr error;
    Prepared prepared;
    LoadMonitor monitor;
    // (2)-(3) this thread
    PrecompileStatus programs;
    GLsync fence = nullptr;
    double t0 = 0.0, phaseStart = 0.0, cpuSeconds = 0.0, compileSeconds = 0.0, linkSeconds = 0.0, lastTitle = -1.0;
};

std::string Viewer::loadingTitle() const {
    const Loading& L = *loading_;
    const Venue& v = *L.in.venue;
    std::string what;
    if (L.phase == Loading::Phase::Cpu) {
        const auto [stage, fraction] = L.monitor.current();
        what = stage;
        if (fraction >= 0.0) what += " (" + std::to_string(int(std::lround(100.0 * fraction))) + " %)";
    } else if (L.phase == Loading::Phase::Compile) {
        what = "shader programs " + std::to_string(L.programs.complete) + " of " + std::to_string(L.programs.total) + " compiled";
    } else if (L.phase == Loading::Phase::Link) {
        what = "linking the shader programs (the picture pauses; a first start on this PC can take several minutes)";
    } else {
        what = "the driver's first dispatch of the compute programs (the picture pauses; a first start on this PC can take several minutes)";
    }
    char t[512];
    std::snprintf(t, sizeof t, "S.W.A.R.M. | loading %s%s | %s | %.0f s", v.seated() ? "venue " : "the terrace", v.seated() ? v.name : "",
                  what.c_str(), glfwGetTime() - L.t0);
    return t;
}

const Viewer::VenueTables* Viewer::tablesOf(const Venue& v) const {
    const auto it = std::find_if(tables_.begin(), tables_.end(), [&](const auto& t) { return t.first == &v; });
    return it == tables_.end() ? nullptr : &it->second;
}

Viewer::RestartInputs Viewer::restartInputs(int n) const {
    RestartInputs in;
    in.venue = selectedVenue_;
    in.n = n;
    in.load = load_;
    in.model = selectedModel_;
    if (!selectedVenue_->seated())
        if (const auto it = terraceSpawns_.find(n); it != terraceSpawns_.end()) in.cachedSpawn = &it->second;
    in.needTables = tablesOf(*selectedVenue_) == nullptr;
    return in;
}

// CPU only (a worker thread runs it while loading in the background): the metric table (once per venue), the navigation field and
// the exit choice table (nav: loaded or built once per process, so the constructors find them in memory), the mesh, the spawn
Viewer::Prepared Viewer::prepareRestart(const RestartInputs& in) {
    const Venue& v = *in.venue;
    Prepared p;
    p.venue = &v;
    p.model = in.model;
    p.n = in.n;
    if (in.needTables) {   // the venue's metric table (on the venue's metric grid)
        nav::reportBuild("metric grid", -1.0);
        const auto t0 = std::chrono::steady_clock::now();
        const metrics::MetricVenue mv = metrics::computeMetricVenue(v);
        p.tables = { mv.cellInfo(), mv.outerWallInnerDepth };
        p.newTables = true;
        std::printf("metric venue %s: %.2f s (once)\n", v.name, std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count());
    }
    if (v.seated()) {   // one agent per occupied seat, in the smallest power-of-two buffer that holds every seat
        const size_t seats = seated::seats(v.layout).size();
        p.n = 256;
        while (size_t(p.n) < seats) p.n *= 2;
        if (nav::hasField(v)) {   // the navigation field; the queue-aware choice's table
            nav::forVenue(v);
            if (effectiveModelOptions(v, in.model).exitChoice == ExitChoice::QueueAware) nav::choiceForVenue(v);
        }
        if (!v.objAsset) {   // venues M and L have no OBJ asset: their render mesh comes from the generator
            nav::reportBuild("render mesh", -1.0);
            p.mesh = seated::mesh(v.layout);
        }
        nav::reportBuild("seat spawn", -1.0);
        p.spawn = spawnSeatedCrowd(v, p.n, in.load, 1337, &p.population);
    } else {
        // The terrace's spawn is deterministic but its overlap relaxation costs ~1.1 s at N = 4096: computed once per N, the same bits
        if (in.cachedSpawn) {
            p.spawn = *in.cachedSpawn;
        } else {
            nav::reportBuild("spawn on the treads", -1.0);
            p.spawn = spawnBleacherCrowd(p.n);
            p.newSpawn = true;
        }
        p.population = p.n;
    }
    return p;
}

std::filesystem::path defaultScreenshotDir() {
    const std::filesystem::path exe = executableDirectory();
    return (exe.empty() ? std::filesystem::current_path() : exe) / "screenshots";
}

namespace {
// The window's size, at most the viewer's own, with its frame inside the primary monitor's work area, centred there
void fitWindowToWorkArea(GLFWwindow* window) {
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    if (!monitor) return;
    int x = 0, y = 0, areaW = 0, areaH = 0;
    glfwGetMonitorWorkarea(monitor, &x, &y, &areaW, &areaH);
    if (areaW <= 0 || areaH <= 0) return;
    int left = 0, top = 0, right = 0, bottom = 0;
    glfwGetWindowFrameSize(window, &left, &top, &right, &bottom);
    const int freeW = areaW - left - right, freeH = areaH - top - bottom;
    if (freeW <= 0 || freeH <= 0) return;
    const int w = std::min(WINDOW_WIDTH, freeW), h = std::min(WINDOW_HEIGHT, freeH);
    glfwSetWindowSize(window, w, h);
    glfwSetWindowPos(window, x + left + (freeW - w) / 2, y + top + (freeH - h) / 2);
}
} // namespace

GLFWwindow* createViewerWindow(bool visible, bool debugContext, bool fitWorkArea) {
    if (!glfwInit()) throw std::runtime_error("glfwInit failed");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, debugContext ? GLFW_TRUE : GLFW_FALSE);
    glfwWindowHint(GLFW_VISIBLE, visible ? GLFW_TRUE : GLFW_FALSE);
    GLFWwindow* window = simulatedGlTooOld() ? nullptr : glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "S.W.A.R.M. viewer", nullptr, nullptr);
    if (!window) throw std::runtime_error(noOpenGlContextMessage());
    if (fitWorkArea) fitWindowToWorkArea(window);
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) throw std::runtime_error("Failed to load OpenGL functions (glad)");
    return window;
}

Viewer::Viewer(GLFWwindow* window, const ViewerOptions& opts) : window_(window), opts_(opts), panelVisible_(opts.panelVisible) {
    shaderDir_ = resolveAsset("shaders");
    screenshotDir_ = opts.screenshotDir.empty() ? defaultScreenshotDir() : opts.screenshotDir;
    exportPx_ = opts.exportPx;
    selectedVenue_ = &venueByName(opts.venue);
    load_ = std::clamp(opts.load, 0.0, 1.0);
    selectedModel_ = defaultModelOptions(venueS());   // the analytic venues' defaults, unless given
    if (!opts.exitChoice.empty()) selectedModel_.exitChoice = exitChoiceByName(opts.exitChoice);
    if (opts.inclineSpeed >= 0) selectedModel_.inclineSpeed = opts.inclineSpeed != 0;
    if (!opts.stairFlow.empty()) selectedModel_.stairFlow = stairFlowByName(opts.stairFlow);

    // The capability check, before any table is built: every venue's requirements against this GPU's limits
    gpuLimits_ = readGpuLimits();
    std::printf("GPU: %s | OpenGL %d.%d | %d SSBO bindings, SSBOs per compute program %d, vertex shader %d, fragment shader %d, an SSBO of up to %s%s\n", gpuLimits_.renderer.c_str(),
                gpuLimits_.glMajor, gpuLimits_.glMinor, gpuLimits_.ssboBindings, gpuLimits_.computeSsboBlocks, gpuLimits_.vertexSsboBlocks, gpuLimits_.fragmentSsboBlocks,
                formatBytes(gpuLimits_.ssboBlockBytes).c_str(), gpuLimits_.simulated ? " (simulated: SWARM_GPU_LIMITS)" : "");
    std::string runnable;
    for (const Venue* v : selectorVenues()) {
        const GpuRequirements need = venueRequirements(*v, selectedModel_, largestAgents(opts.agents));
        const std::string& why = venueShortfall(*v);
        std::printf("  %-8s needs %d SSBO bindings, SSBOs per compute program %d, vertex shader %d, fragment shader %d, an SSBO of %s%s (%s): %s\n", selectorName(*v), need.ssboBindings,
                    need.computeSsboBlocks, need.vertexSsboBlocks, need.fragmentSsboBlocks, need.blockBytesEstimated ? "up to " : "", formatBytes(need.ssboBlockBytes).c_str(),
                    need.largestBuffer.c_str(), why.empty() ? "ok" : why.c_str());
        if (why.empty()) runnable += (runnable.empty() ? "" : ", ") + std::string(selectorName(*v));
    }
    std::fflush(stdout);
    if (const std::string& why = venueShortfall(*selectedVenue_); !why.empty())
        throw std::runtime_error("Venue " + std::string(selectorName(*selectedVenue_)) + " cannot run on this GPU (" + gpuLimits_.renderer + "): " + why + ".\n\n" +
                                 (runnable.empty() ? std::string("No venue can run on it.") : "Venues this GPU can run: " + runnable + ".") +
                                 "\n\nA newer graphics driver may help. On a laptop with two GPUs, choose the faster one for SWARM in the Windows graphics settings.");

    sdfTexture_ = loadSDFTexture3D(resolveAsset("stadium.sdf"));   // the terrace's (a seated venue samples no texture)
    if (!sdfTexture_) throw std::runtime_error("Failed to load stadium.sdf");

    // Fixed-step clock: model time advances at playbackRate x wall time, in steps of DT
    clock_.maxStepsPerFrame = opts.maxStepsPerFrame;
    setRealTime(opts.realTime);
    selectedN_ = opts.agents;
    asyncLoading_ = opts.asyncLoading;
    if (!asyncLoading_) restart(opts.agents);

    // Input: our key callback first, so the ImGui backend (installed next) chains to it
    glfwSetWindowUserPointer(window_, this);
    glfwSetKeyCallback(window_, onKey);
    glfwSetScrollCallback(window_, onScroll);
    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);   // never captured

    if (opts.ui) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.IniFilename = nullptr;   // no imgui.ini in the working directory (an untracked file marks builds dirty)
        ImGui::StyleColorsDark();
        const float scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());
        ImGuiStyle& style = ImGui::GetStyle();
        style.ScaleAllSizes(scale);
        style.FontScaleDpi = scale;
        style.FontSizeBase = 16.0f;
        io.Fonts->AddFontDefaultVector();
        if (!ImGui_ImplGlfw_InitForOpenGL(window_, true)) throw std::runtime_error("ImGui GLFW backend init failed");
        if (!ImGui_ImplOpenGL3_Init("#version 430 core")) throw std::runtime_error("ImGui OpenGL3 backend init failed");
        uiActive_ = true;
    }
    windowStart_ = glfwGetTime();
    if (asyncLoading_) beginLoading(opts.agents);   // last: nothing above may throw with the worker running. The first frames draw the loading screen
}

const std::string& Viewer::venueShortfall(const Venue& v) const {
    const std::pair<const Venue*, bool> key(&v, effectiveModelOptions(v, selectedModel_).exitChoice == ExitChoice::QueueAware);
    auto it = shortfalls_.find(key);
    if (it == shortfalls_.end()) it = shortfalls_.emplace(key, gpuShortfall(venueRequirements(v, selectedModel_, largestAgents(opts_.agents)), gpuLimits_)).first;
    return it->second;
}

void Viewer::setGpuLimits(const GpuLimits& l) {
    gpuLimits_ = l;
    shortfalls_.clear();
}

Viewer::~Viewer() {
    if (loading_) cancelLoading();   // a window closed while loading: the builders stop, nothing partial is saved
    if (uiActive_) {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
    glfwSetWindowUserPointer(window_, nullptr);
}

// The venue's render mesh and metric table (computed once per venue: the terrace on the CPU sampler, a seated venue from its
// cells; prepareRestart computes it, finishRestart keeps it). mesh: a generated venue's triangles (prepareRestart), else empty.
void Viewer::useVenue(const Venue& v, const std::vector<float>& mesh) {
    if (venue_ == &v) return;
    const VenueTables& t = *tablesOf(v);
    cellInfo_ = t.cellInfo;
    outerWallInnerDepth_ = t.outerWallInnerDepth;
    scene_.reset();
    glm::vec3 navGrid(0.0f);   // the navigation grid for the distance overlay (res, origin, 1 / cell)
    if (nav::hasField(v)) {
        const nav::Grid g = nav::venueGrid(v);
        navGrid = glm::vec3(float(g.res), g.origin, g.invCell);
    }
    // Venues M and L have no OBJ asset: their render mesh comes from the generator (seated::mesh, the same triangles)
    const bool first = !venue_, rescale = !venue_ || venue_->domainMax() != v.domainMax();
    scene_ = std::make_unique<SceneRenderer>(shaderDir_, cellInfo_, outerWallInnerDepth_, v.objAsset ? v.objAsset : "", v.seated(),
                                             v.seated() ? v.layout.wallTop : 0.0f, nav::hasField(v) ? &navGrid : nullptr, &mesh);
    venue_ = &v;
    // a venue of another size: its default view (the first venue: the preset chosen before it was ready, --camera, if any)
    if (rescale) applyPreset(first && cameraPresetSet_ ? cameraPreset_ : CameraPreset::Default);
}

void Viewer::setLoad(double load) { load_ = std::clamp(load, 0.0, 1.0); }

void Viewer::restart(int n) { finishRestart(prepareRestart(restartInputs(n))); }

// The GL half of a restart (this thread): the scene, the simulation, the metrics and the readouts, from prepareRestart's results
void Viewer::finishRestart(Prepared&& p) {
    // Free the old run's GPU buffers first (65536 agents: ~10 MB)
    assignReader_.reset();
    counters_.reset();
    metrics_.reset();
    sim_.reset();
    if (p.newTables) tables_.push_back({ p.venue, std::move(p.tables) });
    shortfalls_.clear();   // a table built by this restart: its exact size replaces the bound
    if (p.newSpawn) terraceSpawns_.emplace(p.n, p.spawn);
    useVenue(*p.venue, p.mesh);
    const int n = p.n;
    // Compute pipeline (hash -> sort -> cell ranges -> ping-pong physics), exactly as a fresh process starts it
    if (venue_->seated())   // one agent per occupied seat; routed by the venue's navigation field
        sim_ = std::make_unique<CrowdSim>(shaderDir_, n, *venue_, p.model);   // the selected exit choice and incline speed
    else
        sim_ = std::make_unique<CrowdSim>(shaderDir_, n);
    sim_->upload(p.spawn);
    population_ = p.population;
    if (const std::string w = venue::warning(population_, venue::capacityOf(*venue_)); !w.empty()) std::fprintf(stderr, "%s\n", w.c_str());
    // Safety metrics: write-only passes after every step; the small counters reach the panel through a
    // fence-gated ring that never waits
    metrics_ = std::make_unique<metrics::CrowdMetrics>(shaderDir_, n, cellInfo_, venue_->seated() ? venue_ : nullptr);   // a seated venue's doors
    counters_ = std::make_unique<AsyncCounterReader>(GLsizeiptr(sizeof(GpuMetricCounters)));
    // The exit choice's per-exit counts (the half the latest choice pass wrote, 64 uints), captured with the counters
    assignReader_ = sim_->choiceCounterBuffer() ? std::make_unique<AsyncCounterReader>(GLsizeiptr(64 * sizeof(uint32_t))) : nullptr;
    haveAssign_ = false;

    FixedStepClock fresh;
    fresh.maxStepsPerFrame = clock_.maxStepsPerFrame;
    fresh.playbackRate = clock_.playbackRate;
    if (clock_.paused) fresh.pause();
    clock_ = fresh;

    haveCounters_ = false;
    latest_ = GpuMetricCounters{};
    latestSeq_ = 0;
    evacCurve_.assign(1, EvacPoint{ 0.0f, 0.0f });
    evacComplete_ = false;
    evacCompleteStep_ = 0;
    if (!venue_->seated()) selectedN_ = n;

    // The playback readouts start a fresh window with the fresh clock, whose dropped time starts at 0 (keeping the old
    // clock's would make the window across a restart read a negative "dropped"). The restart's own duration is not playback: the next
    // frame's wall delta is counted from here (frameBody), so the clock does not drop it and the readout does not report it.
    restartEnd_ = glfwGetTime();
    windowStart_ = restartEnd_;
    windowFrames_ = windowSteps_ = 0;
    windowDroppedStart_ = clock_.droppedTime;
    windowLongest_ = windowWall_ = 0.0;
    droppedRealTime_ = longestFrameS_ = 0.0;
}

void Viewer::beginLoading(int n) {
    // The running simulation goes first: the loading frames draw only the loading screen (venue L's buffers: ~1.3 GB)
    assignReader_.reset();
    counters_.reset();
    metrics_.reset();
    sim_.reset();
    auto loading = std::make_unique<Loading>();
    Loading* L = loading.get();
    L->in = restartInputs(n);
    L->needScene = venue_ != selectedVenue_;
    L->t0 = L->phaseStart = glfwGetTime();
    nav::setBuildMonitor(&L->monitor);
    L->worker = std::thread([L] {   // CPU work only: no GL call on this thread
        try {
            L->prepared = prepareRestart(L->in);
        } catch (...) {
            L->error = std::current_exception();
        }
        L->cpuDone.store(true);
    });
    loading_ = std::move(loading);
    std::printf("loading %s%s in the background (parallel shader compile: %s)\n", selectedVenue_->seated() ? "venue " : "the terrace",
                selectedVenue_->seated() ? selectedVenue_->name : "", parallelShaderCompile() ? "on" : "off");
    std::fflush(stdout);
}

// One frame of the background loading: its next step, then the loading screen (or, while the warm-up runs, the window's events alone)
void Viewer::loadingFrame() {
    Loading& L = *loading_;
    if (L.phase == Loading::Phase::Cpu && L.cpuDone.load()) {
        L.worker.join();
        nav::setBuildMonitor(nullptr);
        if (L.error) {   // as a synchronous restart would have thrown
            const std::exception_ptr e = L.error;
            loading_.reset();
            std::rethrow_exception(e);
        }
        L.cpuSeconds = glfwGetTime() - L.t0;
        // (2) every program of the scene (a new venue), the simulation and the metrics, compiled ahead from the sources their
        // constructors will build
        const Prepared& p = L.prepared;
        const VenueTables& t = p.newTables ? p.tables : *tablesOf(*p.venue);
        std::vector<ProgramSpec> specs;
        if (L.needScene) specs = SceneRenderer::programSpecs(shaderDir_);
        for (const ProgramSpec& s : CrowdSim::programSpecs(shaderDir_, *p.venue, p.model)) specs.push_back(s);
        for (const ProgramSpec& s : metrics::CrowdMetrics::programSpecs(shaderDir_, metrics::gridResOf(t.cellInfo.size()), p.venue->seated() ? p.venue : nullptr))
            specs.push_back(s);
        for (const ProgramSpec& s : specs) precompileProgram(s);
        L.phase = Loading::Phase::Compile;
        L.phaseStart = glfwGetTime();
    }
    if (L.phase == Loading::Phase::Compile) {
        L.programs = precompileStep();
        if (L.programs.complete >= L.programs.total) {   // (3) the links: this frame is still drawn (the screen says the picture pauses)
            L.compileSeconds = glfwGetTime() - L.phaseStart;
            L.phase = Loading::Phase::Link;
            L.phaseStart = glfwGetTime();
        }
    } else if (L.phase == Loading::Phase::Link && !L.linksIssued) {
        L.fence = linkPrecompiled();
        L.linksIssued = true;
    }
    if ((L.phase == Loading::Phase::Link && L.linksIssued) || L.phase == Loading::Phase::WarmUp) {
        const GLenum r = L.fence ? glClientWaitSync(L.fence, 0, 0) : GL_ALREADY_SIGNALED;
        if (r == GL_TIMEOUT_EXPIRED) {
            // No drawing meanwhile: a swap would wait behind the driver's links or its compile of a first dispatch (AMD 26.10.1, a
            // cold shader cache: 16 s and 31 s for venue S). The window's events keep it responding; the title shows the step.
            const double now = glfwGetTime();
            if (now - L.lastTitle >= 0.25) {
                glfwSetWindowTitle(window_, loadingTitle().c_str());
                L.lastTitle = now;
            }
            glfwPollEvents();
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            return;
        }
        if (r == GL_WAIT_FAILED) std::fprintf(stderr, "loading: glClientWaitSync failed on a loading fence; continuing\n");
        if (L.fence) glDeleteSync(L.fence);
        L.fence = nullptr;
        if (L.phase == Loading::Phase::Link) {   // (4) every program is linked: the first dispatches, fenced
            L.linkSeconds = glfwGetTime() - L.phaseStart;
            L.fence = warmUpPrecompiled(sdfTexture_);
            L.phase = Loading::Phase::WarmUp;
            L.phaseStart = glfwGetTime();
            glfwPollEvents();
            return;
        }
        const double warmUp = glfwGetTime() - L.phaseStart, t4 = glfwGetTime();
        // (4) the GL objects; their constructors take the programs compiled ahead
        const Venue& v = *L.in.venue;
        const double cpu = L.cpuSeconds, compile = L.compileSeconds, link = L.linkSeconds, t0 = L.t0;
        const int programs = L.programs.total;
        finishRestart(std::move(L.prepared));
        lastUnusedPrograms_ = discardPrecompiled();
        loading_.reset();
        const double now = glfwGetTime();
        std::printf("loaded %s%s in %.2f s: CPU %.2f s (navigation tables, metric grid, mesh, spawn), %d programs: compile %.2f s, link %.2f s, "
                    "first dispatch %.2f s; GPU objects %.2f s\n", v.seated() ? "venue " : "the terrace", v.seated() ? v.name : "", now - t0, cpu,
                    programs, compile, link, warmUp, now - t4);
        if (lastUnusedPrograms_ > 0)
            std::fprintf(stderr, "loading: %d program(s) compiled ahead were not used (a constructor's program list changed?)\n", lastUnusedPrograms_);
        std::fflush(stdout);
        glfwSetWindowTitle(window_, windowTitle().c_str());
        glfwPollEvents();
        return;
    }
    // (1)-(2): the loading screen
    int fbw = 0, fbh = 0;
    glfwGetFramebufferSize(window_, &fbw, &fbh);
    glViewport(0, 0, std::max(fbw, 1), std::max(fbh, 1));
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (uiActive_) {
        beginUiFrame();
        drawLoadingWindow();
        endUiFrame();
    }
    const double now = glfwGetTime();
    if (now - L.lastTitle >= 0.25) {
        glfwSetWindowTitle(window_, loadingTitle().c_str());
        L.lastTitle = now;
    }
    glfwSwapBuffers(window_);
    glfwPollEvents();
    if (!vsync_) std::this_thread::sleep_for(std::chrono::milliseconds(10));   // no need for thousands of loading frames a second
}

void Viewer::drawLoadingWindow() {
    const Loading& L = *loading_;
    const Venue& v = *L.in.venue;
    const float s = ImGui::GetStyle().FontScaleDpi;
    const ImVec2 display = ImGui::GetIO().DisplaySize;
    ImGui::SetNextWindowPos(ImVec2(0.5f * display.x, 0.45f * display.y), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(ImVec2(720.0f * s, 0.0f), ImGuiCond_Always);
    ImGui::Begin("Loading###loading", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                                                   ImGuiWindowFlags_NoSavedSettings);
    if (v.seated())
        ImGui::Text("Loading venue %s: %d seats, %.0f %% occupied", v.name, int(seated::seats(v.layout).size()), 100.0 * L.in.load);
    else
        ImGui::Text("Loading the terrace: %d agents", L.in.n);
    ImGui::SameLine();
    ImGui::TextDisabled("%.1f s", glfwGetTime() - L.t0);
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.85f, 0.4f, 1.0f));
    ImGui::TextWrapped("%s", FIRST_START_NOTE);
    ImGui::PopStyleColor();
    ImGui::Separator();
    const float barW = -1.0f;
    const auto indeterminate = [] { return -1.0f * float(ImGui::GetTime()); };   // a negative fraction: ImGui's moving bar
    // (1)
    ImGui::TextUnformatted("1. Navigation tables, metric grid, mesh and spawn (a background thread)");
    if (L.phase == Loading::Phase::Cpu) {
        const auto [stage, fraction] = L.monitor.current();
        ImGui::ProgressBar(fraction >= 0.0 ? float(fraction) : indeterminate(), ImVec2(barW, 0.0f), stage.c_str());
    } else {
        ImGui::TextDisabled("   done in %.1f s", L.cpuSeconds);
    }
    // (2)
    ImGui::TextUnformatted(parallelShaderCompile() ? "2. Shader programs: compile (in parallel on the driver's threads)"
                                                   : "2. Shader programs: compile and link, one at a time (no parallel shader compile)");
    if (L.phase == Loading::Phase::Compile) {
        char overlay[64];
        std::snprintf(overlay, sizeof overlay, "%d of %d", L.programs.complete, L.programs.total);
        ImGui::ProgressBar(L.programs.total > 0 ? float(L.programs.complete) / float(L.programs.total) : 0.0f, ImVec2(barW, 0.0f), overlay);
    } else if (L.phase == Loading::Phase::Cpu) {
        ImGui::TextDisabled("   waiting");
    } else {
        ImGui::TextDisabled("   done in %.1f s", L.compileSeconds);
    }
    // (3), (4): the picture is not redrawn while the driver links and compiles the first dispatches (a redraw would wait for them)
    ImGui::TextUnformatted("3. Shader programs: link");
    ImGui::TextUnformatted("4. First dispatch of each compute program, then the GPU buffers");
    // In every phase: the window's height must not change in the last frame drawn before the picture pauses (the auto-fit lags a frame)
    ImGui::Indent();
    ImGui::PushStyleColor(ImGuiCol_Text, palette::rgb(palette::MUTED));
    ImGui::TextWrapped("The picture pauses during steps 3 and 4; the window keeps responding and its title shows the progress.");
    ImGui::PopStyleColor();
    ImGui::Unindent();
    ImGui::Separator();
    ImGui::PushStyleColor(ImGuiCol_Text, palette::rgb(palette::MUTED));
    ImGui::TextWrapped("Restart and the venue selector return when the venue is ready. Closing the window cancels the loading: a "
                       "navigation table is written to its cache file only when its build is complete.");
    ImGui::PopStyleColor();
    ImGui::End();
}

void Viewer::cancelLoading() {
    Loading& L = *loading_;
    L.monitor.cancel();
    if (L.worker.joinable()) L.worker.join();   // the builders stop within milliseconds; a cache file being written is completed first
    nav::setBuildMonitor(nullptr);
    if (L.fence) glDeleteSync(L.fence);
    discardPrecompiled();
    bool cancelledBuild = false;
    if (L.error) {
        try {
            std::rethrow_exception(L.error);
        } catch (const nav::BuildCancelled&) {
            cancelledBuild = true;
        } catch (...) {
        }
    }
    std::printf("loading %s%s cancelled after %.1f s%s\n", L.in.venue->seated() ? "venue " : "the terrace", L.in.venue->seated() ? L.in.venue->name : "",
                glfwGetTime() - L.t0, cancelledBuild ? ": a navigation build stopped; nothing of it was saved" : "");
    std::fflush(stdout);
    loading_.reset();
}

void Viewer::setRealTime(double x) {
    realTime_ = std::clamp(x, MIN_REAL_TIME, MAX_REAL_TIME);
    clock_.playbackRate = playbackRateFor(realTime_);
}

bool Viewer::uiWantsMouse() const { return uiActive_ && panelVisible_ && ImGui::GetIO().WantCaptureMouse; }
bool Viewer::uiWantsKeyboard() const { return uiActive_ && panelVisible_ && ImGui::GetIO().WantCaptureKeyboard; }

// --- Input ---
void Viewer::onKey(GLFWwindow* w, int key, int, int action, int) {
    if (action != GLFW_PRESS) return;
    if (Viewer* v = static_cast<Viewer*>(glfwGetWindowUserPointer(w))) v->handleKey(key);
}

void Viewer::onScroll(GLFWwindow* w, double, double yoffset) {
    if (Viewer* v = static_cast<Viewer*>(glfwGetWindowUserPointer(w))) v->scrollY_ += yoffset;
}

// The venue's domain half-width in model units (the terrace and S: 1)
float Viewer::venueScale() const { return venue_ ? std::max(1.0f, venue_->domainMax()) : 1.0f; }

void Viewer::applyPreset(CameraPreset p) {
    if (!venue_) {   // before the first venue is ready (background loading): kept for it
        cameraPresetSet_ = true;
        cameraPreset_ = p;
    }
    const float scale = venueScale();
    camera_ = OrbitCamera::preset(p, exitIndex_, scale, scale > 1.0f ? venue_->exitDepth : -1.0f);   // the terrace and S: the unscaled presets
}

// Discrete keys: F1 panel, P pause/resume, N single step while paused, V VSync, [ and ] playback speed,
// 1-4 camera presets
void Viewer::handleKey(int key) {
    if (loading_) {   // while loading: Esc quits (it cancels the load), nothing else
        if (key == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(window_, true);
        return;
    }
    if (key == GLFW_KEY_F1) { panelVisible_ = !panelVisible_; return; }
    if (uiWantsKeyboard()) return;   // typing into a panel widget
    switch (key) {
    case GLFW_KEY_P: if (clock_.paused) clock_.resume(); else clock_.pause(); break;
    case GLFW_KEY_N: if (clock_.paused) stepRequested_ = true; break;
    case GLFW_KEY_V: vsync_ = !vsync_; glfwSwapInterval(vsync_ ? 1 : 0); break;
    case GLFW_KEY_LEFT_BRACKET: setRealTime(realTime_ * 0.5); break;
    case GLFW_KEY_RIGHT_BRACKET: setRealTime(realTime_ * 2.0); break;
    case GLFW_KEY_1: applyPreset(CameraPreset::Default); break;
    case GLFW_KEY_2: applyPreset(CameraPreset::TopDown); break;
    case GLFW_KEY_3: applyPreset(CameraPreset::Isometric); break;
    case GLFW_KEY_4: applyPreset(CameraPreset::ExitCloseUp); break;
    case GLFW_KEY_M: agentColour_ = AgentColour((int(agentColour_) + 1) % 3); break;
    case GLFW_KEY_H: overlay_ = !overlay_; break;
    case GLFW_KEY_F12: screenshotRequested_ = true; break;
    case GLFW_KEY_F9: heatmapRequested_ = true; break;
    default: break;
    }
}

void Viewer::processHeldKeys(double wallDelta) {
    if (glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window_, true);
    if (uiWantsKeyboard()) return;
    const float dt = float(std::min(wallDelta, 0.1));
    auto held = [&](int key) { return glfwGetKey(window_, key) == GLFW_PRESS ? dt : 0.0f; };
    const float forward = held(GLFW_KEY_W) - held(GLFW_KEY_S), right = held(GLFW_KEY_D) - held(GLFW_KEY_A);
    if (forward != 0.0f || right != 0.0f) camera_.moveOnGround(forward, right);
}

// Left-drag rotates, right-drag pans, the wheel zooms. A drag starts only over the scene (not over the panel) and then
// keeps the mouse until the button is released, also across the panel.
void Viewer::processMouse() {
    double x, y;
    glfwGetCursorPos(window_, &x, &y);
    const bool left = glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
    const bool right = glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
    if ((drag_ == Drag::Rotate && !left) || (drag_ == Drag::Pan && !right)) drag_ = Drag::None;
    if (drag_ == Drag::None && (left || right) && !uiWantsMouse()) {
        drag_ = left ? Drag::Rotate : Drag::Pan;
        lastX_ = x;
        lastY_ = y;
    }
    const float dx = float(x - lastX_), dy = float(y - lastY_);
    lastX_ = x;
    lastY_ = y;
    if (drag_ == Drag::Rotate) camera_.rotate(dx, dy);
    if (drag_ == Drag::Pan) {
        int ww = 0, wh = 0;
        glfwGetWindowSize(window_, &ww, &wh);   // cursor positions are in window coordinates
        camera_.pan(dx, dy, float(wh));
    }
    if (scrollY_ != 0.0 && !uiWantsMouse()) camera_.zoom(float(scrollY_));
    scrollY_ = 0.0;
}

// --- Frame ---
int Viewer::runSteps(int steps) {
    // --- COMPUTE STEPS (hash -> sort -> cell ranges -> ping-pong physics), fixed DT each, then the metric passes ---
    for (int i = 0; i < steps; ++i) {
        sim_->step(sdfTexture_);
        metrics_->afterStep(*sim_);
    }
    return steps;
}

// Fence-gated: reads only captures whose fence has signalled (AsyncCounterReader::poll never waits)
void Viewer::readCounters() {
    if (assignReader_ && assignReader_->poll() && assignReader_->hasData()) {   // fence-gated as the counters
        std::memcpy(assign_, assignReader_->latest().data(), sizeof(assign_));
        haveAssign_ = true;
    }
    counters_->poll();
    if (!counters_->hasData() || counters_->latestSequence() == latestSeq_) return;
    latestSeq_ = counters_->latestSequence();
    latest_ = counters_->latestAs<GpuMetricCounters>();
    haveCounters_ = true;
    const float t = float(double(latest_.step) * DT_REAL_S);
    if (t > evacCurve_.back().tS) evacCurve_.push_back({ t, float(100.0 * latest_.evacuated / double(std::max(population_, 1))) });
    if (!evacComplete_ && population_ > 0 && latest_.step > 0 && latest_.active == 0) {   // (an empty venue never completes)
        evacComplete_ = true;
        evacCompleteStep_ = latest_.step;
        if (pauseWhenEvacuated_) clock_.pause();
        overlay_ = true;   // the heatmap switches on when everyone has left (once per run; H or the panel turns it off)
    }
}

void Viewer::frame(double wallDelta) { frameBody(wallDelta, -1, {}); }

void Viewer::frameFixed(int steps, const std::function<void()>& beforeSteps) { frameBody(0.0, steps, beforeSteps); }

void Viewer::frameBody(double wallDelta, int fixedSteps, const std::function<void()>& beforeSteps) {
    if (restartEnd_ >= 0.0) {   // the first frame after a restart: its delta counts from the restart's end, not across it
        wallDelta = std::min(wallDelta, std::max(0.0, glfwGetTime() - restartEnd_));
        restartEnd_ = -1.0;
    }
    // Background loading (interactive frames: frameFixed restarts within its frame); a restart requested meanwhile waits for it
    if (!loading_ && restartRequested_ > 0 && asyncLoading_ && fixedSteps < 0) {
        beginLoading(restartRequested_);
        restartRequested_ = 0;
    }
    if (loading_) {
        loadingFrame();
        return;
    }
    beginUiFrame();
    if (restartRequested_ > 0) {
        restart(restartRequested_);
        restartRequested_ = 0;
    }
    processHeldKeys(wallDelta);
    processMouse();

    if (beforeSteps) beforeSteps();
    int steps = 0;
    if (fixedSteps < 0) {
        steps = runSteps(clock_.advance(wallDelta));   // 0 while paused
    } else {
        steps = runSteps(fixedSteps);                  // the caller's count; the clock only counts them
        clock_.totalSteps += uint64_t(fixedSteps);
    }
    if (stepRequested_) {                                // N while paused
        stepRequested_ = false;
        runSteps(1);
        clock_.singleStep();
        ++steps;
    }
    if (steps > 0) {
        counters_->capture(metrics_->countersBuffer());
        if (assignReader_) assignReader_->capture(sim_->choiceCounterBuffer(), GLintptr((sim_->choiceStep() & 1u) * 64u * sizeof(uint32_t)));
    }
    readCounters();
    windowLongest_ = std::max(windowLongest_, wallDelta);
    windowWall_ += wallDelta;
    updateStats(glfwGetTime(), steps);

    render();
    buildPanel();
    endUiFrame();
    runExports();
    glfwSwapBuffers(window_);
    glfwPollEvents();
}

void Viewer::updateStats(double now, int steps) {
    ++windowFrames_; ++framesTotal_;
    windowSteps_ += uint64_t(steps); stepsTotal_ += uint64_t(steps);
    if (now - windowStart_ < 1.0) return;
    const double elapsed = now - windowStart_;
    fps_ = windowFrames_ / elapsed;
    stepsPerFrame_ = double(windowSteps_) / double(windowFrames_);
    // Over the frame time the window's frames consumed (the clock's wall deltas), not the wall clock between the window's
    // ends: a stalled frame's time is consumed by the frame after it, so the wall clock would put the stall in one window and its steps (and
    // dropped time) in the next: one window reads low and the next high. The self-test's fixed
    // frames carry no deltas: the wall clock then.
    const double consumed = windowWall_ > 0.0 ? windowWall_ : elapsed;
    achievedRealTime_ = double(windowSteps_) * DT_REAL_S / consumed;
    // The model time the clock dropped in this window (a frame longer than maxFrameTime, or the steps-per-frame cap), as
    // a real-time factor: achieved + dropped = requested (to a step) while playing; and the window's longest frame
    droppedRealTime_ = (clock_.droppedTime - windowDroppedStart_) * double(TIME_SCALE_S_PER_UNIT) / consumed;
    longestFrameS_ = windowLongest_;
    glfwSetWindowTitle(window_, windowTitle().c_str());
    windowStart_ = now;
    windowFrames_ = windowSteps_ = 0;
    windowDroppedStart_ = clock_.droppedTime;
    windowLongest_ = 0.0;
    windowWall_ = 0.0;
}

std::string Viewer::capacityLabel() const { return venue::label(population_, venue::capacityOf(*venue_)); }

ModelOptions Viewer::runningModel() const { return sim_ ? sim_->options() : ModelOptions{}; }

std::string Viewer::windowTitle() const {
    if (loading_) return loadingTitle();
    char metricText[200] = "";
    uint32_t doors = 0;   // a seated venue's concourse doors
    for (int e = metrics::EXIT_DOOR0; e < metrics::EXIT_SLOTS; ++e) doors += latest_.exits[e];   // (unused slots are 0)
    if (haveCounters_ && venue_->seated())
        std::snprintf(metricText, sizeof(metricText), " | active %u | evacuated %u (avenues +x %u -x %u +y %u -y %u, doors %u) at %.1f s",
                      latest_.active, latest_.evacuated, latest_.exits[0], latest_.exits[1], latest_.exits[2], latest_.exits[3], doors,
                      double(latest_.step) * DT_REAL_S);
    else if (haveCounters_)
        std::snprintf(metricText, sizeof(metricText), " | active %u | evacuated %u (+x %u -x %u +y %u -y %u) at %.1f s",
                      latest_.active, latest_.evacuated, latest_.exits[0], latest_.exits[1], latest_.exits[2], latest_.exits[3],
                      double(latest_.step) * DT_REAL_S);
    // Above the venue's design capacity the title carries the capacity label (physically impossible above the
    // jam capacity)
    std::string capacity = venue::load(population_, venue::capacityOf(*venue_)) == venue::Load::WithinDesign ? "" : " | " + capacityLabel();
    if (venue_->seated())   // the venue and the model options
        capacity = std::string(" | venue ") + venue_->name + " (navigation field, " + modelOptionsLabel(*venue_, sim_->options()) + ")" + capacity;
    char title[512];
    std::snprintf(title, sizeof(title),
        "S.W.A.R.M. | %d agents%s | FPS %.0f | steps/frame %.2f | playback %.3gx requested / %.3gx achieved real time%s%s%s",
        population_, capacity.c_str(), fps_, stepsPerFrame_, realTime_, achievedRealTime_, clock_.paused ? " | PAUSED" : "",
        vsync_ ? " | VSync" : "", metricText);
    return title;
}

void Viewer::render() {
    int fbw = 0, fbh = 0;
    glfwGetFramebufferSize(window_, &fbw, &fbh);
    if (fbw <= 0 || fbh <= 0) return;   // minimized
    glViewport(0, 0, fbw, fbh);
    drawScene(camera_.view(), camera_.projection(float(fbw) / float(fbh)), float(clock_.renderAlpha()), overlay_, agentsVisible_);
}

void Viewer::drawScene(const glm::mat4& view, const glm::mat4& projection, float alpha, bool overlay, bool agents) {
    SceneFrame f;
    f.projection = projection;
    f.view = view;
    f.alpha = alpha;
    f.agentsVisible = agents;
    f.agentColour = agentColour_;
    f.metricCells = metrics_->cellBuffer();
    // 0: the terrace. Built the first time the distance overlay is drawn (L: 244 MB): the queue-aware default never
    // needs it otherwise, and the stadium shader reads it only for that overlay
    f.navCells = overlay && overlayMetric_ == OverlayMetric::NavDistance ? sim_->navBuffer() : 0;
    f.overlay = overlay;
    f.overlayMetric = overlayMetric_;
    f.circulationOnly = overlayCirculationOnly_;
    scene_->draw(f, *sim_);
}

double Viewer::simTimeS() const { return double(clock_.totalSteps) * DT_REAL_S; }

// --- Export ---
void Viewer::runExports() {
    if (!screenshotRequested_ && !heatmapRequested_) return;
    try {
        if (screenshotRequested_) lastExport_ = takeScreenshot(includePanel_).string();
        if (heatmapRequested_) lastExport_ = takeHeatmapExport().string();
    } catch (const std::exception& e) {
        lastExport_ = std::string("export FAILED: ") + e.what();
        std::fprintf(stderr, "%s\n", lastExport_.c_str());
    }
    screenshotRequested_ = heatmapRequested_ = false;
}

std::filesystem::path Viewer::takeScreenshot(bool includePanel) {
    int fbw = 0, fbh = 0;
    glfwGetFramebufferSize(window_, &fbw, &fbh);
    if (fbw <= 0 || fbh <= 0) throw std::runtime_error("screenshot: the window has no framebuffer (minimized)");
    OffscreenTarget target(fbw, fbh);
    target.bind();
    // alpha 1: the current state exactly, so the image is the state at the time in its name
    drawScene(camera_.view(), camera_.projection(float(fbw) / float(fbh)), 1.0f, overlay_, agentsVisible_);
    if (includePanel && uiActive_ && panelVisible_) ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    const std::vector<uint8_t> px = target.readRGB();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, fbw, fbh);
    const std::filesystem::path path =
        uniquePath(screenshotDir_, exportStem(venueFileName(*venue_), population_, simTimeS(), buildinfo::gitDescribe()), ".png");
    writePngRGB(path, fbw, fbh, px);
    std::printf("screenshot: %s (%d x %d)\n", path.string().c_str(), fbw, fbh);
    return path;
}

std::vector<uint8_t> Viewer::renderHeatmapPixels(int px) {
    // The whole metric grid (the terrace and S: 64 m x 64 m; others: the venue's), centred on the origin, straight down, +y up
    const int res = metrics::gridResOf(cellInfo_.size());
    const float halfExtent = float(0.5 * res * metrics::CELL_M / units::M_PER_UNIT);
    const glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    const glm::mat4 projection = glm::ortho(-halfExtent, halfExtent, -halfExtent, halfExtent, 0.1f, 10.0f);   // z 4.9 .. -5: above L's walls
    std::vector<uint8_t> rgb;
    {
        OffscreenTarget target(px, px);
        target.bind();
        drawScene(view, projection, 1.0f, true, agentsInHeatmap_);
        rgb = target.readRGB();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    int fbw = 0, fbh = 0;
    glfwGetFramebufferSize(window_, &fbw, &fbh);
    glViewport(0, 0, fbw, fbh);
    return rgb;
}

std::filesystem::path Viewer::takeHeatmapExport() {
    const int px = exportPx_;
    const std::vector<uint8_t> rgb = renderHeatmapPixels(px);

    const OverlayInfo& info = overlayInfo(overlayMetric_);
    const std::string stem = exportStem(venueFileName(*venue_), population_, simTimeS(), buildinfo::gitDescribe(),
                                        std::string("heatmap-") + info.fileTag);
    const std::filesystem::path path = uniquePath(screenshotDir_, stem, ".png");
    writePngRGB(path, px, px, rgb);

    // Sidecar: what the colours mean, and where the pixels are
    const ColourScale& sc = *info.scale;
    const bool nav = overlayMetric_ == OverlayMetric::NavDistance;   // the navigation field (static, 0.05 m cells)
    const int res = metrics::gridResOf(cellInfo_.size());
    const double minM = metrics::gridMinM(res), maxM = minM + res * metrics::CELL_M;
    const bool scoped = overlayCirculationOnly_ && overlayScoped(overlayMetric_);
    std::ostringstream j;
    j << "{\n  \"image\": \"" << jsonEscape(path.filename().string()) << "\",\n"
      << "  \"venue\": \"" << venueFileName(*venue_) << "\", \"n\": " << population_ << ", \"step\": " << clock_.totalSteps
      << ", \"sim_time_s\": " << simTimeS() << ",\n"
      << "  \"commit\": \"" << buildinfo::gitCommit() << "\", \"dirty\": \"" << buildinfo::gitDirtyField() << "\", \"build\": \""
      << buildinfo::buildConfig() << "\",\n"
      << "  \"gpu\": \"" << jsonEscape((const char*)glGetString(GL_RENDERER)) << "\", \"driver\": \""
      << jsonEscape((const char*)glGetString(GL_VERSION)) << "\",\n"
      << "  \"metric\": \"" << info.fileTag << "\", \"metric_name\": \"" << jsonEscape(info.legendTitle) << "\", \"unit\": \""
      << sc.unit << "\",\n  \"definition\": \"" << jsonEscape(info.definition) << "\",\n"
      << "  \"scale\": {\"type\": \"" << (sc.log10 ? "log10 piecewise-linear" : "piecewise-linear") << "\", \"stops\": [";
    for (int i = 0; i < sc.stopCount; ++i) j << (i ? ", " : "") << sc.stops[i];
    j << "], \"stops_at_t\": \"equally spaced from 0 to 1\", \"ticks\": [";
    for (int i = 0; i < sc.tickCount; ++i)
        j << (i ? ", " : "") << "{\"value\": " << sc.ticks[i].value << ", \"label\": \"" << sc.ticks[i].label
          << (sc.ticks[i].note ? std::string(" ") + sc.ticks[i].note : std::string()) << "\", \"t\": " << sc.t(sc.ticks[i].value) << "}";
    j << "],\n            \"note\": \"" << jsonEscape(sc.rangeNote) << "\"},\n  \"ramp\": [";
    for (int i = 0; i < palette::RAMP_STEPS; ++i) j << (i ? ", " : "") << "\"" << hexColour(palette::RAMP[i]) << "\"";
    j << "], \"ramp_at_t\": \"i / " << (palette::RAMP_STEPS - 1) << ", linear between steps\",\n"
      << "  \"zero_colour\": \"" << hexColour(palette::ZERO) << "\", \"zero_meaning\": \""
      << (nav ? "an exit region (distance 0)" : "walkable floor, value 0 (mean speed: never occupied)") << "\",\n"
      << "  \"no_data\": \""
      << (nav ? "normal stadium shading: no path to an exit (seat-block and wall tops, the fenced pitch) or not floor-like (n_z <= 0.5)"
              : "normal stadium shading: no counted floor (excluded below 0.1 m^2, outside the grid) or not floor-like (n_z <= 0.5)")
      << "\",\n"
      << "  \"shading\": \"overlay colour x (0.75 + 0.25 x diffuse); flat floors x ~0.96\",\n"
      << "  \"zones\": \"" << (scoped ? "circulation zones only: seat rows / treads (metric zone 'tread') keep the normal shading" : "every zone") << "\",\n"
      << "  \"extent_m\": {\"x\": [" << minM << ", " << maxM << "], \"y\": [" << minM << ", " << maxM << "]}, \"pixels\": " << px
      << ", \"px_per_m\": " << double(px) / (res * metrics::CELL_M) << ", \"orientation\": \"top-down orthographic, +x right, +y up\",\n"
      << "  \"agents_drawn\": " << (agentsInHeatmap_ ? "true" : "false") << "\n}\n";
    std::filesystem::path side = path;
    side.replace_extension(".json");
    std::ofstream(side) << j.str();
    std::printf("heatmap export: %s (%d x %d, %s) + %s\n", path.string().c_str(), px, px, info.fileTag, side.filename().string().c_str());
    return path;
}

// --- Panel (Dear ImGui) ---
void Viewer::beginUiFrame() {
    if (!uiActive_) return;
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Viewer::buildPanel() {
    if (!uiActive_ || !panelVisible_) return;
    const float s = ImGui::GetStyle().FontScaleDpi;
    ImGui::SetNextWindowPos(ImVec2(12.0f * s, 12.0f * s), ImGuiCond_FirstUseEver);
    // Full window height (scrolls if the sections do not fit), wide enough for the legends' labels
    ImGui::SetNextWindowSize(ImVec2(560.0f * s, ImGui::GetIO().DisplaySize.y - 24.0f * s), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("S.W.A.R.M. viewer (F1 hides)", &panelVisible_)) {
        ImGui::TextColored(ImGui::ColorConvertU32ToFloat4(palette::rgb(palette::TEXT_SECONDARY_DARK)), "%s | N = %d | %s | %s",
                           venue_->seated() ? (std::string("venue ") + venue_->name).c_str() : "stadium (terrace)", population_,
                           buildinfo::gitDescribe(), buildinfo::buildConfig());
        // A seated venue's agents follow its navigation field: to the nearest exit or a queue-aware choice
        if (venue_->seated())
            ImGui::TextDisabled("Routing: navigation field, %s", sim_->options().exitChoice == ExitChoice::QueueAware
                                    ? "queue-aware exit choice (re-evaluated every 3 s)" : "each agent to its nearest exit (static)");
        if (venue_->seated()) ImGui::TextDisabled("Walking speed: %s", sim_->options().inclineSpeed ? "stair speeds on the gangway inclines" : "level speed everywhere");
        if (venue_->seated() && sim_->options().stairFlow != StairFlow::Off)
            ImGui::TextDisabled("Stair spacing: %s (calibrated to %s)", stairFlowName(sim_->options().stairFlow),
                                sim_->options().stairFlow == StairFlow::Empirical ? "measured stair flows, 73-75 p/(m min)" : "the planning rate, 66 p/(m min)");
        // The venue's capacity (design capacity, jam capacity of the occupiable floor at hexagonal packing)
        const venue::Capacity cap = venue::capacityOf(*venue_);
        const venue::Load load = venue::load(population_, cap);
        if (load == venue::Load::WithinDesign) {
            ImGui::TextDisabled("%s (design capacity %d, jam capacity %d)", capacityLabel().c_str(), cap.design, cap.jam);
        } else {
            const ImVec4 colour = load == venue::Load::PhysicallyImpossible ? ImVec4(1.0f, 0.35f, 0.30f, 1.0f) : ImVec4(1.0f, 0.75f, 0.25f, 1.0f);
            ImGui::TextColored(colour, "%s%s", load == venue::Load::PhysicallyImpossible ? "PHYSICALLY IMPOSSIBLE: " : "", capacityLabel().c_str());
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("Design capacity %d agents; jam capacity %d: the venue's occupiable floor (%.1f m^2) at hexagonal packing of\n"
                                  "0.40 m bodies (%.2f persons/m^2). Above it the bodies do not fit on the floor at once: densities and\n"
                                  "overlaps of this run are not physical (a performance stress test).",
                                  cap.design, cap.jam, cap.occupiableM2, venue::HEX_PACKING_P_M2);
        }
        panelSimulation();
        panelReadouts();
        panelCamera();
        panelAgents();
        panelOverlay();
        panelExport();
        ImGui::Separator();
        ImGui::PushStyleColor(ImGuiCol_Text, palette::rgb(palette::MUTED));
        ImGui::TextWrapped("Keys: %s", KEY_HELP);
        ImGui::PopStyleColor();
        if (panelExtra_) panelExtra_();
    }
    ImGui::End();
}

void Viewer::panelSimulation() {
    if (!ImGui::CollapsingHeader("Simulation", ImGuiTreeNodeFlags_DefaultOpen)) return;
    // Widget IDs are unique in the panel ("##"/"###" suffixes; SWARM --selftest-ui fails on any ID conflict)
    if (ImGui::Button(clock_.paused ? "Play (P)###playpause" : "Pause (P)###playpause", ImVec2(ImGui::GetFontSize() * 6.0f, 0.0f))) {
        if (clock_.paused) clock_.resume(); else clock_.pause();
    }
    ImGui::SameLine();
    if (ImGui::Button("Step (N)")) {   // a single step; pauses a running simulation first
        clock_.pause();
        stepRequested_ = true;
    }
    ImGui::SameLine();
    ImGui::BeginDisabled(!venueShortfall(*selectedVenue_).empty());   // the selected venue cannot run on this GPU with the selected model
    if (ImGui::Button("Restart")) restartRequested_ = selectedN_;
    ImGui::EndDisabled();
    // The venue selector (applies at the restart); a venue this GPU cannot run is disabled, with the reason
    ImGui::SameLine();
    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 6.0f);
    const auto itemCentre = [] { return 0.5f * (glm::vec2(ImGui::GetItemRectMin().x, ImGui::GetItemRectMin().y) + glm::vec2(ImGui::GetItemRectMax().x, ImGui::GetItemRectMax().y)); };
    const bool venueListOpen = ImGui::BeginCombo("venue##restart", selectorName(*selectedVenue_));
    if (!venueListOpen) venueComboCentre_ = itemCentre();
    if (venueListOpen) {
        int item = 0;
        for (const Venue* v : selectorVenues()) {
            const std::string& why = venueShortfall(*v);
            const std::string label = std::string(selectorName(*v)) + (why.empty() ? "" : "  (" + why + ")") + "###venue" + selectorName(*v);
            if (ImGui::Selectable(label.c_str(), v == selectedVenue_, why.empty() ? ImGuiSelectableFlags_None : ImGuiSelectableFlags_Disabled)) selectedVenue_ = v;
            venueItemCentre_[item++] = itemCentre();
        }
        ImGui::EndCombo();
    }
    ImGui::SameLine();
    if (selectedVenue_->seated()) {   // a seated venue: one agent per occupied seat
        float pct = float(load_ * 100.0);
        ImGui::SetNextItemWidth(ImGui::GetFontSize() * 7.0f);
        if (ImGui::SliderFloat("load##restart", &pct, 0.0f, 100.0f, "%.0f%% of seats")) setLoad(double(pct) / 100.0);
    } else {
        ImGui::SetNextItemWidth(ImGui::GetFontSize() * 6.0f);
        char preview[32];
        std::snprintf(preview, sizeof(preview), "%d", selectedN_);
        if (ImGui::BeginCombo("N##restart", preview)) {
            for (int n : N_CHOICES) {
                char label[128];
                if (venue::load(n) == venue::Load::WithinDesign) std::snprintf(label, sizeof(label), "%d", n);
                else std::snprintf(label, sizeof(label), "%d  (%s)", n, venue::label(n).c_str());
                if (ImGui::Selectable(label, n == selectedN_)) selectedN_ = n;
            }
            ImGui::EndCombo();
        }
    }
    for (const Venue* v : selectorVenues())   // the reasons stay in view with the list closed
        if (const std::string& why = venueShortfall(*v); !why.empty()) {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.75f, 0.35f, 1.0f));
            ImGui::TextWrapped("%s: %s", selectorName(*v), why.c_str());
            ImGui::PopStyleColor();
        }
    if (selectedVenue_->seated()) {   // the model options of the next restart
        int mode = selectedModel_.exitChoice == ExitChoice::QueueAware ? 1 : 0;
        static const char* modes[] = { "nearest", "queue-aware" };
        ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8.0f);
        if (ImGui::Combo("exit choice##restart", &mode, modes, 2)) selectedModel_.exitChoice = mode ? ExitChoice::QueueAware : ExitChoice::Nearest;
        if (ImGui::IsItemHovered())   // the choice's constants (sim_params.hpp): T_CHOICE_S, V_FREE_M_S, EXIT_FLOW_P_M_MIN
            ImGui::SetTooltip("nearest: every agent walks to its nearest exit.\nqueue-aware: every %.0f s agents compare walk + queue time per "
                              "exit\n(E = d / %.2f m/s + queued ahead / (width x %.1f p/(m min)); queued ahead: the agents assigned to the exit\n"
                              "and nearer to it) and switch with hysteresis. Applies at the restart.",
                              double(T_CHOICE_S), double(V_FREE_M_S), double(EXIT_FLOW_P_M_MIN));
        ImGui::SameLine();
        ImGui::Checkbox("incline speed##restart", &selectedModel_.inclineSpeed);
        if (ImGui::IsItemHovered()) ImGui::SetTooltip("Stair walking speeds on the gangway inclines (0.58 m/s up, 0.655 m/s down; Fruin 1971). Applies at the restart.");
        if (selectedModel_.inclineSpeed) {   // the stair spacing (with the incline speed only)
            int sf = int(selectedModel_.stairFlow);
            static const char* sets[] = { "off", "empirical", "conservative" };
            ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8.0f);
            if (ImGui::Combo("stair spacing##restart", &sf, sets, 3)) selectedModel_.stairFlow = StairFlow(sf);
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("The headway time gap on the gangway inclines: empirical = the gangways' maximum flow at the measured stair\n"
                                  "flows (Burghardt et al. 2013, 73-75 p/(m min)), conservative = the Green Guide's 66 p/(m min), off = the level\n"
                                  "spacing. Applies at the restart.");
        }
    }
    if (selectedVenue_ != venue_ || (!venue_->seated() && selectedN_ != sim_->numBoids()) ||
        (venue_->seated() && selectedVenue_ == venue_ && effectiveModelOptions(*venue_, selectedModel_) != sim_->options())) {
        ImGui::SameLine();
        ImGui::TextDisabled("(Restart applies%s)", !selectedVenue_->seated() && venue::load(selectedN_) == venue::Load::PhysicallyImpossible
                                                       ? ": physically impossible" : "");
    }

    float rt = float(realTime_);
    ImGui::SetNextItemWidth(-ImGui::GetFontSize() * 6.0f);
    if (ImGui::SliderFloat("speed##playback", &rt, float(MIN_REAL_TIME), float(MAX_REAL_TIME), "%.2fx real time", ImGuiSliderFlags_Logarithmic))
        setRealTime(rt);
    ImGui::SameLine();
    if (ImGui::SmallButton("1x##playback")) setRealTime(1.0);
    if (!clock_.paused && droppedRealTime_ > 0.005)   // a dip is time the clock dropped, not an averaging artefact
        ImGui::Text("requested %.2fx | achieved %.2fx real time (%.2fx dropped: longest frame %.0f ms)", realTime_, achievedRealTime_,
                    droppedRealTime_, 1000.0 * longestFrameS_);
    else
        ImGui::Text("requested %.2fx | achieved %.2fx real time", realTime_, clock_.paused ? 0.0 : achievedRealTime_);
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("1x real time = 1 simulated second per wall second (DT = %.4f s per step, %.2f steps/s at 1x).\n"
                          "Achieved: steps taken in the last wall second x DT. At most %d steps per frame.\n"
                          "Dropped: a frame longer than %.0f ms (a stall: window drag, a busy GPU or CPU) or the steps-per-frame cap skips its\n"
                          "excess simulated time instead of catching up; achieved + dropped = requested within a step.",
                          DT_REAL_S, 1.0 / DT_REAL_S, clock_.maxStepsPerFrame, 1000.0 * clock_.maxFrameTime);
    ImGui::Checkbox("Pause when everyone has left", &pauseWhenEvacuated_);
}

void Viewer::panelReadouts() {
    if (!ImGui::CollapsingHeader("Readouts", ImGuiTreeNodeFlags_DefaultOpen)) return;
    const int n = population_;
    if (ImGui::BeginTable("readouts", 2, ImGuiTableFlags_SizingStretchProp)) {
        auto row = [](const char* name, const char* fmt, auto... args) {
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::TextUnformatted(name);
            ImGui::TableNextColumn();
            ImGui::Text(fmt, args...);
        };
        if (haveCounters_) {
            row("Simulated time", "%.1f s (step %u)", double(latest_.step) * DT_REAL_S, latest_.step);
            row("Active agents", "%u of %d", latest_.active, n);
            row("Evacuated", "%.1f %% (%u)", 100.0 * latest_.evacuated / std::max(n, 1), latest_.evacuated);
            row("Exits", "+x %u | -x %u | +y %u | -y %u", latest_.exits[0], latest_.exits[1], latest_.exits[2], latest_.exits[3]);
            if (venue_->seated()) {   // the concourse doors, per quadrant (y wall + x wall)
                const SeatedLayout& VL = venue_->layout;
                const int dpq = VL.doorsPerQuadrant();   // the doors per quadrant (S: 2)
                uint32_t q[4] = {};
                for (int k = 0; k < 4; ++k)
                    for (int d = 0; d < dpq; ++d) q[k] += latest_.exits[metrics::EXIT_DOOR0 + dpq * k + d];
                row("Concourse doors", "+x+y %u | -x+y %u | -x-y %u | +x-y %u", q[0], q[1], q[2], q[3]);
                // Exit utilisation, from the same counters: the doors' and the avenues' shares of the evacuated, the exit width
                // nobody has used yet
                const uint32_t av = latest_.exits[0] + latest_.exits[1] + latest_.exits[2] + latest_.exits[3];
                const uint32_t dr = q[0] + q[1] + q[2] + q[3];
                double unused = 0.0, total = 0.0;
                for (int e = 0; e < metrics::exitSlotsUsed(&VL); ++e) {
                    if (e == metrics::EXIT_OTHER) continue;
                    const double w = seated::exitWidthM(VL, e < metrics::EXIT_GAPS ? e : 4 + e - metrics::EXIT_DOOR0);
                    total += w;
                    if (latest_.exits[e] == 0) unused += w;
                }
                const double ev = std::max(1u, latest_.evacuated);
                // These count the agents that have left so far; the assignment line below is the active agents' exits now
                row("Exit utilisation (so far)", "doors %.0f %% | avenues %.0f %% of the evacuated", 100.0 * dr / ev, 100.0 * av / ev);
                row("Unused exit width (so far)", "%.1f of %.1f m (%.0f %%): no one left there yet", unused, total, 100.0 * unused / total);
                if (sim_->options().exitChoice == ExitChoice::QueueAware && haveAssign_) {
                    // the exit choice's latest counts: every active agent's assigned exit (nav exit ids: 0-3 avenues, 4.. doors)
                    uint64_t toDoors = 0, toAvenues = 0;
                    double idle = 0.0;
                    for (int e = 0; e < seated::exitCount(VL); ++e) {
                        (e < 4 ? toAvenues : toDoors) += assign_[e];
                        if (assign_[e] == 0) idle += seated::exitWidthM(VL, e);
                    }
                    const double act = double(std::max<uint64_t>(1, toDoors + toAvenues));
                    row("Assigned now", "doors %.0f %% | avenues %.0f %% of the active", 100.0 * double(toDoors) / act, 100.0 * double(toAvenues) / act);
                    row("Unused width now", "%.1f of %.1f m (%.0f %%): exits with no agent assigned", idle, total, 100.0 * idle / total);
                }
                // Per-gangway utilisation (the metric counters; seated::gangwayAt): the agents that stood on each gangway, and
                // the evacuated agents whose last gangway it was, straight against corner
                uint64_t visS = 0, visC = 0, lastS = 0, lastC = 0;
                int unusedGw = 0;
                for (int g = 0; g < seated::gangwayCount(VL); ++g) {
                    const bool corner = g % VL.gangwaysPerQuadrant() == 2 * VL.gangways;
                    (corner ? visC : visS) += latest_.gangwayVisits[g];
                    (corner ? lastC : lastS) += latest_.gangwayLast[g];
                    unusedGw += latest_.gangwayVisits[g] == 0;
                }
                const double lastAll = double(std::max<uint64_t>(1, lastS + lastC));
                row("Gangways (last used)", "straight (%d) %.0f %% | corner (4) %.0f %%", 8 * VL.gangways, 100.0 * double(lastS) / lastAll, 100.0 * double(lastC) / lastAll);
                if (ImGui::IsItemHovered()) {
                    std::string tip = "Per gangway: agents that stood on it / evacuated agents whose last gangway it was\n";
                    for (int g = 0; g < seated::gangwayCount(VL); ++g)
                        tip += seated::gangwayName(VL, g) + ": " + std::to_string(latest_.gangwayVisits[g]) + " / " + std::to_string(latest_.gangwayLast[g]) + "\n";
                    ImGui::SetTooltip("%s", tip.c_str());
                }
                row("Gangways (agents on them)", "straight %llu | corner %llu | unused %d of %d", (unsigned long long)visS, (unsigned long long)visC,
                    unusedGw, seated::gangwayCount(VL));
            }
        } else {
            row("Simulated time", "%.1f s (no step yet)", 0.0);
            row("Active agents", "%d of %d", n, n);
            row("Evacuated", "%.1f %%", 0.0);
        }
        row("FPS", "%.0f", fps_);
        row("Steps/frame", "%.2f", stepsPerFrame_);
        ImGui::EndTable();
    }
    if (evacComplete_)
        ImGui::Text("Everyone has left: first reading with 0 active at t = %.1f s (step %u)", double(evacCompleteStep_) * DT_REAL_S,
                    evacCompleteStep_);
    drawEvacuationCurve();
    ImGui::PushStyleColor(ImGuiCol_Text, palette::rgb(palette::MUTED));
    ImGui::TextWrapped("Readouts: fence-gated GPU counters (never waited for), at most a few frames old.");
    ImGui::PopStyleColor();
}

void Viewer::panelCamera() {
    if (!ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen)) return;
    if (ImGui::Button("Default (1)")) applyPreset(CameraPreset::Default);
    ImGui::SameLine();
    if (ImGui::Button("Top-down (2)")) applyPreset(CameraPreset::TopDown);
    ImGui::SameLine();
    if (ImGui::Button("Isometric (3)")) applyPreset(CameraPreset::Isometric);
    if (ImGui::Button("Exit close-up (4)")) applyPreset(CameraPreset::ExitCloseUp);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 4.5f);
    static const char* exits[] = { "+x", "-x", "+y", "-y" };
    if (ImGui::Combo("exit##camera", &exitIndex_, exits, 4)) applyPreset(CameraPreset::ExitCloseUp);
    ImGui::Checkbox("Orthographic", &camera_.orthographic);
    ImGui::TextDisabled("yaw %.0f, pitch %.0f, distance %.2f (%.1f m)", camera_.yawDeg, camera_.pitchDeg, camera_.distance,
                        camera_.distance * WORLD_SCALE_M_PER_UNIT);
}

void Viewer::panelAgents() {
    if (!ImGui::CollapsingHeader("Agents", ImGuiTreeNodeFlags_DefaultOpen)) return;
    int mode = int(agentColour_);
    ImGui::TextUnformatted("Colour by (M):");
    ImGui::SameLine();
    ImGui::RadioButton("speed##colour", &mode, int(AgentColour::Speed));
    ImGui::SameLine();
    ImGui::RadioButton("density##colour", &mode, int(AgentColour::Density));
    ImGui::SameLine();
    ImGui::RadioButton("zone##colour", &mode, int(AgentColour::Zone));
    agentColour_ = AgentColour(mode);
    ImGui::SameLine();
    ImGui::Checkbox("show##agents", &agentsVisible_);
    switch (agentColour_) {
    case AgentColour::Speed:
        drawScaleLegend(SPEED_SCALE, "Horizontal speed", false, "Each agent's speed in the current step.");
        break;
    case AgentColour::Density:
        drawScaleLegend(DENSITY_SCALE, "Local density", false,
                        "Density of the 1 m metric cell containing the agent, last step (cloud-in-cell). "
                        "Grey: a cell without counted floor.");
        break;
    case AgentColour::Zone:
        drawZoneLegend();
        break;
    }
}

void Viewer::panelOverlay() {
    if (!ImGui::CollapsingHeader("Heatmap overlay", ImGuiTreeNodeFlags_DefaultOpen)) return;
    ImGui::Checkbox("show on the stadium (H)", &overlay_);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(-1.0f);
    if (ImGui::BeginCombo("##metric", overlayInfo(overlayMetric_).name)) {
        for (int m = 0; m < int(OverlayMetric::Count); ++m) {
            if (OverlayMetric(m) == OverlayMetric::NavDistance && !nav::hasField(*venue_)) continue;   // venues with a field
            const OverlayInfo& info = overlayInfo(OverlayMetric(m));
            if (ImGui::Selectable(info.name, OverlayMetric(m) == overlayMetric_)) overlayMetric_ = OverlayMetric(m);
            if (ImGui::IsItemHovered()) ImGui::SetTooltip("%s", info.definition);
        }
        ImGui::EndCombo();
    }
    // Circulation zones only (the default for peak density, the time above the thresholds and crush exposure)
    ImGui::Checkbox("circulation zones only##overlay", &overlayCirculationOnly_);
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("Peak density, time above the thresholds and crush exposure over the circulation zones (gangways / aisles,\n"
                          "walkway, concourse, avenues, exits); the seat rows and treads (metric zone 'tread') keep the normal\n"
                          "shading. Off: every zone. The other metrics always show every zone.");
    if (!overlayScoped(overlayMetric_)) {
        ImGui::SameLine();
        ImGui::TextDisabled("(this metric: every zone)");
    }
    const OverlayInfo& info = overlayInfo(overlayMetric_);
    const bool nav = overlayMetric_ == OverlayMetric::NavDistance;   // the navigation field, static
    drawScaleLegend(*info.scale, info.legendTitle, !nav, nav ? "Normal shading: no path to an exit (seat-block and wall tops, the pitch)."
                                                             : "Normal shading: no counted floor (or not floor-like).");
    ImGui::PushStyleColor(ImGuiCol_Text, palette::rgb(palette::MUTED));
    if (nav)
        ImGui::TextWrapped("The navigation field's 0.05 m cells: the shortest legal walk to the nearest exit (static; value 0: an exit "
                           "region), read on the GPU.");
    else
        ImGui::TextWrapped("1 m cells of the metric grid since the last restart, read on the GPU. Switches on by itself when "
                           "everyone has left.");
    ImGui::PopStyleColor();
}

void Viewer::panelExport() {
    if (!ImGui::CollapsingHeader("Export", ImGuiTreeNodeFlags_DefaultOpen)) return;
    if (ImGui::Button("Screenshot (F12)")) screenshotRequested_ = true;
    ImGui::SameLine();
    ImGui::Checkbox("include the panel", &includePanel_);
    if (ImGui::Button("Top-down heatmap export (F9)")) heatmapRequested_ = true;
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("Orthographic top-down view of the venue's metric grid (%d m x %d m) with the selected overlay metric,\n"
                          "%d x %d px (%.0f px per 1 m cell), no UI; a .json sidecar describes the colour scale.", metrics::gridResOf(cellInfo_.size()),
                          metrics::gridResOf(cellInfo_.size()), exportPx_, exportPx_, exportPx_ / (metrics::gridResOf(cellInfo_.size()) * metrics::CELL_M));
    ImGui::SameLine();
    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 6.5f);
    static const int sizes[] = { 4096, 8192 };
    char preview[16];
    std::snprintf(preview, sizeof(preview), "%d px", exportPx_);
    if (ImGui::BeginCombo("##px", preview)) {
        for (int sz : sizes) {
            char label[16];
            std::snprintf(label, sizeof(label), "%d px", sz);
            if (ImGui::Selectable(label, sz == exportPx_)) exportPx_ = sz;
        }
        ImGui::EndCombo();
    }
    ImGui::SameLine();
    ImGui::Checkbox("agents##heatmap", &agentsInHeatmap_);
    ImGui::PushStyleColor(ImGuiCol_Text, palette::rgb(palette::MUTED));
    ImGui::TextWrapped("Folder: %s", screenshotDir_.string().c_str());
    if (!lastExport_.empty()) ImGui::TextWrapped("Last: %s", lastExport_.c_str());
    ImGui::PopStyleColor();
}

// Evacuated [%] over simulated time [s]: one series, so no legend box (the title names it); hover for values
void Viewer::drawEvacuationCurve() {
    using namespace palette;
    const float s = ImGui::GetStyle().FontScaleDpi;
    ImGui::TextUnformatted("Evacuated [%] over simulated time [s]");
    const float w = ImGui::GetContentRegionAvail().x, h = 140.0f * s;
    const ImVec2 p0 = ImGui::GetCursorScreenPos();
    ImGui::InvisibleButton("evac_curve", ImVec2(w, h));
    const bool hovered = ImGui::IsItemHovered();
    ImDrawList* dl = ImGui::GetWindowDrawList();
    const float lineH = ImGui::GetTextLineHeight();
    const ImVec2 a(p0.x + ImGui::CalcTextSize("100").x + 8.0f * s, p0.y + 0.5f * lineH);   // plot area top-left
    const ImVec2 b(p0.x + w - 6.0f * s, p0.y + h - lineH - 6.0f * s);                       // bottom-right
    dl->AddRectFilled(p0, ImVec2(p0.x + w, p0.y + h), rgb(SURFACE_DARK), 4.0f * s);
    const float tEnd = niceAxisEnd(evacCurve_.back().tS);
    auto px = [&](float t) { return a.x + (b.x - a.x) * t / tEnd; };
    auto py = [&](float pct) { return b.y - (b.y - a.y) * pct / 100.0f; };
    for (int pct : { 25, 50, 75, 100 }) dl->AddLine(ImVec2(a.x, py(float(pct))), ImVec2(b.x, py(float(pct))), rgb(GRID_DARK), 1.0f);
    dl->AddLine(ImVec2(a.x, b.y), ImVec2(b.x, b.y), rgb(AXIS_DARK), 1.0f);
    for (int pct : { 0, 50, 100 }) {
        char lab[8];
        std::snprintf(lab, sizeof(lab), "%d", pct);
        dl->AddText(ImVec2(a.x - ImGui::CalcTextSize(lab).x - 4.0f * s, py(float(pct)) - 0.5f * lineH), rgb(MUTED), lab);
    }
    for (float t : { 0.0f, 0.5f * tEnd, tEnd }) {
        char lab[16];
        std::snprintf(lab, sizeof(lab), t == tEnd ? "%.0f s" : "%.0f", t);
        const float tw = ImGui::CalcTextSize(lab).x;
        const float x = std::clamp(px(t) - 0.5f * tw, a.x - 0.5f * tw, b.x - tw);
        dl->AddText(ImVec2(x, b.y + 3.0f * s), rgb(MUTED), lab);
    }
    std::vector<ImVec2> pts;
    pts.reserve(evacCurve_.size());
    for (const EvacPoint& e : evacCurve_) pts.emplace_back(px(e.tS), py(e.percent));
    if (pts.size() >= 2) dl->AddPolyline(pts.data(), int(pts.size()), rgb(SERIES1_DARK), ImDrawFlags_None, 2.0f * s);
    if (hovered && evacCurve_.size() >= 2) {
        const float t = std::clamp((ImGui::GetIO().MousePos.x - a.x) / (b.x - a.x) * tEnd, 0.0f, evacCurve_.back().tS);
        auto it = std::lower_bound(evacCurve_.begin(), evacCurve_.end(), t, [](const EvacPoint& e, float v) { return e.tS < v; });
        if (it == evacCurve_.end()) --it;
        if (it != evacCurve_.begin() && t - std::prev(it)->tS < it->tS - t) --it;
        const ImVec2 m(px(it->tS), py(it->percent));
        dl->AddLine(ImVec2(m.x, a.y), ImVec2(m.x, b.y), rgb(AXIS_DARK), 1.0f);
        dl->AddCircleFilled(m, 4.0f * s, rgb(SERIES1_DARK));
        dl->AddCircle(m, 4.0f * s, rgb(SURFACE_DARK), 0, 2.0f * s);
        ImGui::SetTooltip("t = %.1f s\n%.1f %% evacuated", it->tS, it->percent);
    }
}

void Viewer::endUiFrame() {
    if (!uiActive_) return;
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Viewer::printRunMetrics() const {
    if (!counters_ || !counters_->hasData()) return;
    const GpuMetricCounters c = counters_->latestAs<GpuMetricCounters>();
    std::printf("metrics (latest fence-signalled counters, %llu of %llu captures read, %llu skipped): step %u, active %u, evacuated %u "
                "(+x %u, -x %u, +y %u, -y %u, other %u)\n", (unsigned long long)counters_->latestSequence(),
                (unsigned long long)counters_->capturedSequence(), (unsigned long long)counters_->skipped(), c.step, c.active, c.evacuated,
                c.exits[0], c.exits[1], c.exits[2], c.exits[3], c.exits[4]);
}

} // namespace swarm::viewer
