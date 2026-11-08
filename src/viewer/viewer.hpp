#pragma once

// The SWARM viewer: window loop around the simulation step, with a Dear ImGui control
// panel (F1). Viewer code only: it calls CrowdSim::step() and CrowdMetrics::afterStep() and
// only reads their buffers (rendering, fence-gated counters).

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <cstdint>
#include <filesystem>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <swarm/fixed_step_clock.hpp>

#include "viewer/orbit_camera.hpp"
#include "viewer/scene.hpp"
#include <swarm/exit_choice.hpp>
#include <swarm/gpu_caps.hpp>
#include <swarm/gpu_types.hpp>

namespace swarm {
class CrowdSim;
class AsyncCounterReader;
struct Venue;
namespace metrics {
class CrowdMetrics;
}
} // namespace swarm

namespace swarm::viewer {

// Playback in REAL time: simulated seconds per wall-clock second (1 = real time). The clock's playbackRate is in
// model time units per wall second: realTime / TIME_SCALE_S_PER_UNIT.
constexpr double MIN_REAL_TIME = 0.1;
constexpr double MAX_REAL_TIME = 20.0;
// Agent counts offered by the N selector (CrowdSim needs a power of two >= 256)
constexpr int N_CHOICES[] = { 1024, 2048, 4096, 8192, 16384, 32768, 65536 };

struct ViewerOptions {
    std::string venue = "terrace";   // "terrace" | "S" | "M" | "L" (swarm::venueByName)
    double load = 1.0;               // a seated venue: the share of its seats occupied (a seeded random subset)
    std::string exitChoice;          // an analytic venue's exit choice, "nearest" | "queue-aware" ("": the venue's default)
    int inclineSpeed = -1;           // an analytic venue's incline speed, 0 | 1 (-1: the venue's default)
    std::string stairFlow;           // the stair spacing, "off" | "empirical" | "conservative" ("": the venue's default)
    int agents = 4096;
    int maxStepsPerFrame = 8;
    double realTime = 1.0;     // initial playback speed, x real time
    bool ui = true;            // Dear ImGui panel available (F1 toggles it); false: no ImGui at all
    bool panelVisible = true;
    std::filesystem::path screenshotDir;   // empty: defaultScreenshotDir()
    int exportPx = 4096;                   // top-down heatmap export, pixels per side (>= 3000)
    // The interactive SWARM: the start and every restart load in the background behind a loading screen (Viewer::frame; the window
    // keeps responding). false (the self-test, the timing cell): every restart completes within its frame.
    bool asyncLoading = false;
};

// A screenshots folder beside the executable (the current folder if its location is unknown).
std::filesystem::path defaultScreenshotDir();

// glfwInit (if needed), an OpenGL 4.3 core window of the viewer's size (2560 x 1440), its context current, glad
// loaded. Hidden windows render normally (all exports go through offscreen framebuffers). Throws on failure.
// fitWorkArea: the interactive viewer's window, at most that size, its frame inside the primary monitor's work area and centred
// there; the self-test and the timing cell keep the fixed size.
constexpr int WINDOW_WIDTH = 2560, WINDOW_HEIGHT = 1440;
GLFWwindow* createViewerWindow(bool visible, bool debugContext, bool fitWorkArea = false);
// Export file names: the terrace keeps its asset name (stadium), a seated venue "venue_<name>"
std::string venueFileName(const Venue& v);
// GL_ARB_parallel_shader_compile (or the KHR form) for the programs the background loading compiles ahead (swarm/shader.hpp): on if
// the driver has it, unless forceOff (SWARM --no-parallel-compile, SWARM_NO_PARALLEL_COMPILE). Needs the window's context current.
// Returns the state as one line for the console.
std::string configureParallelShaderCompile(bool forceOff);
// What a run of the venue needs from the GPU (swarm/gpu_caps.hpp): every program of the scene, the simulation and the metrics, every
// buffer. Loads and builds no table. agents: the terrace's N (a seated venue: from its seats).
GpuRequirements venueRequirements(const Venue& v, const ModelOptions& model, int agents);

class Viewer {
public:
    Viewer(GLFWwindow* window, const ViewerOptions& opts);
    ~Viewer();
    Viewer(const Viewer&) = delete;
    Viewer& operator=(const Viewer&) = delete;

    // One interactive frame: input, the clock's steps, panel, render, swap. wallDelta in wall seconds.
    void frame(double wallDelta);
    // The same frame with exactly 'steps' steps instead of the clock's (self-test, timing cell); beforeSteps runs
    // after the input and before the steps. Single steps requested with N still add one.
    void frameFixed(int steps, const std::function<void()>& beforeSteps = {});

    // Respawns n agents (spawnBleacherCrowd) in a fresh simulation with fresh metrics and counters; the clock
    // restarts at step 0 (playback speed and pause state kept). In a seated venue n is ignored: one agent per
    // occupied seat (spawnSeatedCrowd, load()), in the smallest power-of-two buffer that holds every seat. Synchronous: complete
    // when it returns.
    void restart(int n);
    // Background loading (ViewerOptions::asyncLoading; frame() only, frameFixed() always restarts synchronously). A requested restart
    // first frees the running simulation, then: (1) a worker thread does the CPU work (the venue's metric table, navigation field and
    // exit choice table, loaded or built, the generated mesh, the spawn; no GL call); (2) this thread compiles the venue's programs
    // ahead (swarm/shader.hpp precompileProgram: in parallel with GL_ARB_parallel_shader_compile, else one per frame); (3) it dispatches
    // each compute program once without work and polls a fence, drawing nothing meanwhile (a swap would wait behind the driver's
    // first-dispatch compile) but handling the window's events; (4) in one frame it builds the scene, the simulation and the metrics,
    // whose constructors take the compiled programs: the same programs, so the same results as restart(). Frames (1)-(2) draw the
    // loading screen instead of the panel: Restart and the venue selector are unavailable until the venue is ready; a restart
    // requested meanwhile waits for it. Destroying the viewer cancels the load (the navigation builders stop, nothing partial is saved).
    bool loading() const { return loading_ != nullptr; }
    void setAsyncLoading(bool on) { asyncLoading_ = on; }
    int lastLoadUnusedPrograms() const { return lastUnusedPrograms_; }   // programs compiled ahead that no constructor took (0 expected)
    // The venue selector. The next restart (requestRestart, or at once with restart) uses this venue.
    void selectVenue(const Venue& v) { selectedVenue_ = &v; }
    const Venue& selectedVenue() const { return *selectedVenue_; }
    // The capability check, from the limits read at the start (before any table is built): why the venue cannot run on this GPU with
    // the selected model, "" if it can. The constructor refuses a start venue that cannot run; the selector disables such a venue and
    // the panel shows the reason. setGpuLimits, the self-test's way to another GPU's limits.
    const std::string& venueShortfall(const Venue& v) const;
    const GpuLimits& gpuLimits() const { return gpuLimits_; }
    void setGpuLimits(const GpuLimits& l);
    // Self-test: where the selector and its items were drawn (index: the selector's order), for its mouse clicks
    glm::vec2 venueComboCentre() const { return venueComboCentre_; }
    glm::vec2 venueItemCentre(int i) const { return venueItemCentre_[i]; }
    void requestVenue(const Venue& v) { selectedVenue_ = &v; restartRequested_ = selectedN_; }
    void setLoad(double load);
    double load() const { return load_; }
    // An analytic venue's model options for the next restart (the panel's exit choice and incline speed controls) and the
    // running simulation's
    void selectModel(const ModelOptions& m) { selectedModel_ = m; }
    const ModelOptions& selectedModel() const { return selectedModel_; }
    ModelOptions runningModel() const;
    const Venue& currentVenue() const { return *venue_; }
    int population() const { return population_; }   // agents active at the restart (seated: the occupied seats)

    CrowdSim& sim() { return *sim_; }
    const FixedStepClock& clock() const { return clock_; }
    double realTime() const { return realTime_; }
    void setRealTime(double x);
    bool vsync() const { return vsync_; }
    uint64_t framesRendered() const { return framesTotal_; }
    uint64_t stepsTaken() const { return stepsTotal_; }
    void printRunMetrics() const;   // --run-seconds summary of the latest counters

    // Exports (one-off framebuffer reads; they wait for the GPU once). Both return the PNG written.
    // Screenshot: the current view at the window's framebuffer size, without the panel unless includePanel and the
    // panel is drawn this frame. Heatmap: top-down orthographic view of the venue's whole metric grid at exportPx
    // with the overlay of the selected metric, without the UI, plus a JSON sidecar describing the colour scale.
    std::filesystem::path takeScreenshot(bool includePanel);
    std::filesystem::path takeHeatmapExport();
    // The heatmap export's image (RGB rows, bottom row first) without writing it (self-test)
    std::vector<uint8_t> renderHeatmapPixels(int px);
    GLuint sdfTexture() const { return sdfTexture_; }
    double simTimeS() const;   // exact: steps taken since the restart x DT_REAL_S

    // Display settings (panel, keys, command line)
    void applyPreset(CameraPreset p);
    void setAgentColour(AgentColour c) { agentColour_ = c; }
    void setAgentsVisible(bool v) { agentsVisible_ = v; }
    void setOverlay(bool on, OverlayMetric m) { overlay_ = on; overlayMetric_ = m; }
    // The density metrics over the circulation zones only (the default) or every zone
    void setOverlayCirculationOnly(bool on) { overlayCirculationOnly_ = on; }
    bool overlayCirculationOnly() const { return overlayCirculationOnly_; }
    void setPanelVisible(bool v) { panelVisible_ = v; }
    void setIncludePanel(bool v) { includePanel_ = v; }   // screenshots include the panel
    bool panelVisible() const { return panelVisible_; }
    bool overlay() const { return overlay_; }
    bool uiActive() const { return uiActive_; }
    void pressKey(int key) { handleKey(key); }   // a discrete key press, as from the keyboard (self-test)
    void selectN(int n) { selectedN_ = n; }
    void requestRestart() { restartRequested_ = selectedN_; }   // the panel's Restart button
    // The venue's capacity label for the running N (venue::label: within design capacity, above it, or
    // physically impossible), shown in the panel and the window title, and the title the stats window sets
    std::string capacityLabel() const;
    std::string windowTitle() const;
    // Self-test only: widgets submitted at the end of the panel window every frame (empty: none)
    void setPanelExtra(std::function<void()> f) { panelExtra_ = std::move(f); }

    // Fence-gated counters as the panel shows them
    bool haveCounters() const { return haveCounters_; }
    const GpuMetricCounters& latestCounters() const { return latest_; }
    bool evacuationComplete() const { return evacComplete_; }
    uint32_t evacuationCompleteStep() const { return evacCompleteStep_; }
    size_t evacuationCurvePoints() const { return evacCurve_.size(); }
    float evacuationCurveLastPercent() const { return evacCurve_.back().percent; }
    // The playback statistics of the last full 1 s window: the simulated time the clock dropped (frames longer than maxFrameTime, or
    // the steps-per-frame cap) as a real-time factor, the window's longest frame
    double droppedRealTime() const { return droppedRealTime_; }
    double longestFrameS() const { return longestFrameS_; }
    // The exit choice's latest per-exit assignment counts (queue-aware; fence-gated, false: none yet)
    bool haveAssignment() const { return haveAssign_; }

private:
    static void onKey(GLFWwindow* w, int key, int scancode, int action, int mods);
    static void onScroll(GLFWwindow* w, double xoffset, double yoffset);
    void handleKey(int key);
    void processHeldKeys(double wallDelta);
    void processMouse();
    void beginUiFrame();
    void buildPanel();
    void panelSimulation();
    void panelReadouts();
    void panelCamera();
    void panelAgents();
    void panelOverlay();
    void panelExport();
    void runExports();
    void drawScene(const glm::mat4& view, const glm::mat4& projection, float alpha, bool overlay, bool agents);
    void drawEvacuationCurve();
    void endUiFrame();
    int runSteps(int steps);
    void frameBody(double wallDelta, int fixedSteps, const std::function<void()>& beforeSteps);
    void readCounters();
    void updateStats(double now, int steps);
    void render();
    bool uiWantsMouse() const;
    bool uiWantsKeyboard() const;

    GLFWwindow* window_;
    ViewerOptions opts_;
    std::filesystem::path shaderDir_;
    GLuint sdfTexture_ = 0;
    std::vector<GpuMetricCellInfo> cellInfo_;   // the venue's metric table (computeMetricVenue, once per venue)
    float outerWallInnerDepth_ = 0.0f;
    // The running venue, the one the next restart uses, the seated load, the active agents at the restart, and
    // each venue's metric table (computed on first use)
    const Venue* venue_ = nullptr;
    const Venue* selectedVenue_ = nullptr;
    double load_ = 1.0;
    ModelOptions selectedModel_;   // applies to analytic venues at the restart (the terrace ignores it)
    int population_ = 0;
    struct VenueTables { std::vector<GpuMetricCellInfo> cellInfo; float outerWallInnerDepth = 0.0f; };
    std::vector<std::pair<const Venue*, VenueTables>> tables_;
    std::map<int, std::vector<GpuBoid>> terraceSpawns_;   // spawnBleacherCrowd(n), once per n (deterministic)
    GpuLimits gpuLimits_;
    mutable std::map<std::pair<const Venue*, bool>, std::string> shortfalls_;   // by venue and queue-aware; cleared when a table may have appeared
    glm::vec2 venueComboCentre_{ 0.0f }, venueItemCentre_[4] = { glm::vec2(0.0f), glm::vec2(0.0f), glm::vec2(0.0f), glm::vec2(0.0f) };
    const VenueTables* tablesOf(const Venue& v) const;    // nullptr: not computed yet
    // A restart in two halves: the CPU work (static: a worker thread runs it in the background loading) and the GL objects
    struct Prepared;
    struct RestartInputs;
    static Prepared prepareRestart(const RestartInputs& in);
    RestartInputs restartInputs(int n) const;
    void finishRestart(Prepared&& p);
    void useVenue(const Venue& v, const std::vector<float>& mesh);
    // Background loading (loading())
    struct Loading;
    std::unique_ptr<Loading> loading_;
    bool asyncLoading_ = false;
    int lastUnusedPrograms_ = 0;
    void beginLoading(int n);
    void loadingFrame();
    void drawLoadingWindow();
    std::string loadingTitle() const;
    void cancelLoading();
    bool cameraPresetSet_ = false;   // a preset applied before the first venue was ready (--camera): kept when it is
    CameraPreset cameraPreset_ = CameraPreset::Default;
    std::unique_ptr<CrowdSim> sim_;
    std::unique_ptr<metrics::CrowdMetrics> metrics_;
    std::unique_ptr<AsyncCounterReader> counters_;
    std::unique_ptr<SceneRenderer> scene_;
    FixedStepClock clock_;
    double realTime_ = 1.0;

    // Controls
    bool stepRequested_ = false;
    int restartRequested_ = 0;    // > 0: restart with this N at the start of the next frame
    int selectedN_ = 4096;
    bool vsync_ = false;
    bool uiActive_ = false;       // ImGui context created
    bool panelVisible_ = true;
    bool pauseWhenEvacuated_ = true;

    // Display
    AgentColour agentColour_ = AgentColour::Speed;
    bool agentsVisible_ = true;
    bool overlay_ = false;
    OverlayMetric overlayMetric_ = OverlayMetric::PeakDensity;

    // Export
    std::filesystem::path screenshotDir_;
    int exportPx_ = 4096;
    bool screenshotRequested_ = false, heatmapRequested_ = false;
    bool includePanel_ = false;      // screenshots include the panel
    bool agentsInHeatmap_ = false;   // the heatmap export draws the agents
    std::string lastExport_;

    // Fence-gated counters (never waited for): the latest reading, the evacuation curve, completion
    bool haveCounters_ = false;
    GpuMetricCounters latest_{};
    uint64_t latestSeq_ = 0;
    struct EvacPoint { float tS, percent; };
    std::vector<EvacPoint> evacCurve_;
    bool evacComplete_ = false;
    uint32_t evacCompleteStep_ = 0;   // the first reading with no active agent

    // Orbit camera: left-drag rotates, right-drag pans, the wheel zooms (never over the panel); W A S D move the
    // orbit centre on the ground. A drag belongs to where it started (scene or panel).
    OrbitCamera camera_ = OrbitCamera::preset(CameraPreset::Default);
    int exitIndex_ = 2;                 // exit of the close-up preset (metrics::Exit order; +y)
    enum class Drag { None, Rotate, Pan } drag_ = Drag::None;
    double lastX_ = 0.0, lastY_ = 0.0;
    double scrollY_ = 0.0;              // wheel notches since the last frame

    // Statistics over a 1 s wall-clock window (title and panel)
    double windowStart_ = 0.0;
    uint64_t windowFrames_ = 0, windowSteps_ = 0;
    uint64_t framesTotal_ = 0, stepsTotal_ = 0;
    double fps_ = 0.0, stepsPerFrame_ = 0.0, achievedRealTime_ = 0.0;
    // The clock's dropped time at the window start, the window's dropped real-time share and longest frame
    double windowDroppedStart_ = 0.0, droppedRealTime_ = 0.0, windowLongest_ = 0.0, longestFrameS_ = 0.0, windowWall_ = 0.0;
    double restartEnd_ = -1.0;   // glfwGetTime() at the end of the latest restart, until the next frame has used it (-1: none)
    // The overlay scope; the exit choice's per-exit counts (an async reader of the latest written half)
    bool overlayCirculationOnly_ = true;
    std::unique_ptr<AsyncCounterReader> assignReader_;
    bool haveAssign_ = false;
    uint32_t assign_[64] = {};
    float venueScale() const;
    std::function<void()> panelExtra_;
};

} // namespace swarm::viewer
