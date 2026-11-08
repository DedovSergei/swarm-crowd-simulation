#include "viewer/selftest.hpp"

#include "viewer/imgui_id_check.hpp"
#include "viewer/viewer.hpp"

#include "golden_state.hpp"   // tools/: the pinned golden hashes (test_gpu parity.golden_terrace)

#include <swarm/assets.hpp>
#include <swarm/build_info.hpp>
#include <swarm/crowd_sim.hpp>
#include <swarm/exit_choice.hpp>
#include <swarm/gpu_caps.hpp>
#include <swarm/gpu_types.hpp>
#include <swarm/metrics.hpp>
#include <swarm/nav_field.hpp>
#include <swarm/sim_params.hpp>
#include <swarm/venue.hpp>
#include <swarm/venue_capacity.hpp>

#include <glad/glad.h>
#include <imgui.h>

#include <algorithm>
#include <cfloat>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

namespace swarm::viewer {

namespace {

int g_failures = 0;
void check(bool ok, const std::string& what) {
    std::printf("  [%s] %s\n", ok ? "PASS" : "FAIL", what.c_str());
    if (!ok) ++g_failures;
}

// GL debug output: errors and warnings (notifications ignored)
struct DebugLog {
    int errors = 0, warnings = 0;
    std::vector<std::string> samples;
} g_debug;

void APIENTRY onDebugMessage(GLenum, GLenum type, GLuint, GLenum severity, GLsizei, const GLchar* msg, const void*) {
    if (severity == GL_DEBUG_SEVERITY_NOTIFICATION) return;
    if (type == GL_DEBUG_TYPE_ERROR) ++g_debug.errors; else ++g_debug.warnings;
    if (g_debug.samples.size() < 8) g_debug.samples.emplace_back(msg);
}

// glGetError after a frame: every pending error
int g_glErrors = 0;
std::string g_firstGlError;
void drainGlErrors(const char* where) {
    for (GLenum e = glGetError(); e != GL_NO_ERROR; e = glGetError()) {
        if (g_glErrors++ == 0) {
            char b[96];
            std::snprintf(b, sizeof(b), "0x%04x after %s", unsigned(e), where);
            g_firstGlError = b;
        }
    }
}

std::vector<GpuBoid> readState(GLuint buffer, int n) {   // test readback (waits for the GPU)
    glMemoryBarrier(GL_BUFFER_UPDATE_BARRIER_BIT);
    std::vector<GpuBoid> s(static_cast<size_t>(n));
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer);
    glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, GLsizeiptr(s.size() * sizeof(GpuBoid)), s.data());
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    return s;
}

// The SSBO bindings the program's active blocks really have. stage (GL_REFERENCED_BY_VERTEX_SHADER, _FRAGMENT_SHADER: a render program): only
// that stage's; GL_NONE: all of them (a compute program: AMD 26.10.1 lists every declared block as active, referenced or not)
std::vector<GLuint> activeBindings(GLuint program, GLenum stage) {
    GLint blocks = 0;
    glGetProgramInterfaceiv(program, GL_SHADER_STORAGE_BLOCK, GL_ACTIVE_RESOURCES, &blocks);
    std::vector<GLuint> b;
    for (GLint i = 0; i < blocks; ++i) {
        const GLenum props[2] = { GL_BUFFER_BINDING, stage };
        GLint values[2] = { -1, 1 };
        glGetProgramResourceiv(program, GL_SHADER_STORAGE_BLOCK, GLuint(i), stage == GL_NONE ? 1 : 2, props, 2, nullptr, values);
        if (values[1]) b.push_back(GLuint(values[0]));
    }
    std::sort(b.begin(), b.end());
    return b;
}

std::string hex64(uint64_t v) {
    char b[24];
    std::snprintf(b, sizeof(b), "%016llx", (unsigned long long)v);
    return b;
}

// Counters as the panel shows them: one consistent snapshot (active + evacuated = N, exits sum to evacuated)
int g_counterReadings = 0, g_counterViolations = 0;
uint64_t g_lastSeq = 0;
void checkCounters(const Viewer& v, int n) {
    if (!v.haveCounters()) return;
    const GpuMetricCounters& c = v.latestCounters();
    const uint64_t key = (uint64_t(c.step) << 32) | c.evacuated;
    if (key == g_lastSeq) return;
    g_lastSeq = key;
    ++g_counterReadings;
    uint32_t exits = 0;
    for (uint32_t e : c.exits) exits += e;
    if (c.active + c.evacuated != uint32_t(n) || exits != c.evacuated) ++g_counterViolations;
}

} // namespace

int runSelfTestUi(GLFWwindow* window, const SelfTestOptions& o) {
    using clock = std::chrono::steady_clock;
    const auto t0 = clock::now();
    const std::string driver = std::string((const char*)glGetString(GL_RENDERER)) + " | " + (const char*)glGetString(GL_VERSION);
    std::printf("SWARM --selftest-ui | commit %s (dirty %s) | %s\nGL %s\n", buildinfo::gitCommit(), buildinfo::gitDirtyField(),
                buildinfo::buildConfig(), driver.c_str());
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(onDebugMessage, nullptr);

    std::filesystem::path outDir = o.outDir;
    if (outDir.empty()) {
#ifdef SWARM_SOURCE_DIR
        outDir = std::filesystem::path(SWARM_SOURCE_DIR) / "out" / "selftest";
#else
        outDir = std::filesystem::current_path() / "selftest_out";
#endif
    }
    const int n = o.agents, K = o.steps;

    ViewerOptions vo;
    vo.agents = n;
    vo.ui = true;
    vo.panelVisible = true;
    vo.screenshotDir = outDir;
    Viewer v(window, vo);
    drainGlErrors("startup");
    check(v.uiActive() && v.panelVisible(), "Dear ImGui panel active in a hidden " + std::to_string(n) + "-agent window");

    int frames = 0;
    auto frame = [&](int steps, const char* where) {
        v.frameFixed(steps);
        ++frames;
        drainGlErrors(where);
        checkCounters(v, v.population());
    };

    // --- Widget IDs: any two panel widgets with the same ID fail the self-test. ImGui's own report
    //     (io.ConfigDebugHighlightIdConflicts, on) needs a mouse over the item; idcheck counts every frame's items ---
    std::printf("\n== viewer.widget_ids: Dear ImGui widget IDs\n");
    ImGui::GetIO().ConfigDebugHighlightIdConflicts = true;
    idcheck::setEnabled(true);
    v.setPanelExtra([] {   // known answer: two buttons with one ID in the panel for one frame
        ImGui::Button("conflict##idcheck");
        ImGui::Button("conflict##idcheck");
    });
    frame(0, "id conflict known answer");
    const int planted = idcheck::conflicts();
    check(planted >= 1, "the ID check sees a planted conflict (two buttons \"conflict##idcheck\" in one frame: " + std::to_string(planted) + ")");
    v.setPanelExtra({});
    idcheck::setEnabled(true);   // from zero: every later frame counts

    // --- Restart through the panel's path (N selector + Restart), at another N and back ---
    std::printf("\n== viewer.restart: Restart with another N and back (panel path)\n");
    v.selectN(1024);
    v.requestRestart();
    frame(0, "restart 1024");
    check(v.sim().numBoids() == 1024 && v.clock().totalSteps == 0, "restart with N = 1024: fresh simulation at step 0");
    for (int i = 0; i < 20; ++i) frame(2, "N = 1024 frames");
    check(v.clock().totalSteps == 40, "40 steps at N = 1024");
    v.selectN(n);
    v.requestRestart();
    frame(0, "restart back");
    check(v.sim().numBoids() == n && v.clock().totalSteps == 0 && !v.haveCounters(), "restart with N = " + std::to_string(n) +
          ": step 0, counters reset");

    // --- Capacity labels: above the design capacity the panel and the title say so; above the jam capacity
    //     they say "physically impossible (N / jam capacity = x)" ---
    std::printf("\n== viewer.capacity_labels: Capacity labels (design capacity %d, jam capacity %d)\n", venue::TERRACE.design, venue::TERRACE.jam);
    for (int big : { 16384, 65536 }) {
        v.selectN(big);
        v.requestRestart();
        frame(0, "capacity restart");
        const std::string label = v.capacityLabel(), title = v.windowTitle();
        const std::string expect = big > venue::TERRACE.jam ? "physically impossible (N / jam capacity = " : "above design capacity (N / design capacity = ";
        std::printf("  N = %d: %s\n  title: %s\n", big, label.c_str(), title.c_str());
        check(label.rfind(expect, 0) == 0 && label == venue::label(big) && title.find(label) != std::string::npos,
              "N = " + std::to_string(big) + ": panel and window title carry \"" + label + "\"");
    }
    v.selectN(n);
    v.requestRestart();
    frame(0, "restart back after the capacity labels");
    check(v.sim().numBoids() == n && v.clock().totalSteps == 0 && (n > venue::TERRACE.design || v.windowTitle().find("capacity") == std::string::npos),
          "back at N = " + std::to_string(n) + " (" + v.capacityLabel() + "): no capacity label in the title");

    // --- K steps, cycling every display mode, overlay metric, camera preset and key binding ---
    std::printf("\n== viewer.display_modes: %d steps with the panel, every display mode, overlay metric, camera preset and key\n", K);
    const int schedule[] = { 1, 3, 0, 2, 8, 1, 5, 0, 4, 7 };
    std::filesystem::path screenshot;
    int modesSeen[3] = {}, overlaysSeen[int(OverlayMetric::Count)] = {}, presetsSeen[4] = {}, panelHiddenFrames = 0;
    for (int f = 0; int(v.clock().totalSteps) < K; ++f) {
        const int remaining = K - int(v.clock().totalSteps);
        int steps = std::min(schedule[f % 10], remaining);
        v.setAgentColour(AgentColour(f % 3));
        v.setAgentsVisible(f % 11 != 10);
        v.setOverlay(f % 2 == 0, OverlayMetric((f / 2) % int(OverlayMetric::Count)));
        if (f % 5 == 0) v.applyPreset(CameraPreset((f / 5) % 4));
        ++modesSeen[f % 3];
        if (f % 2 == 0) ++overlaysSeen[(f / 2) % int(OverlayMetric::Count)];
        ++presetsSeen[(f / 5) % 4];
        // Keys (the same handler as the keyboard)
        if (f == 20) v.pressKey(GLFW_KEY_F1);   // hide the panel for one frame
        if (f == 21) v.pressKey(GLFW_KEY_F1);
        if (!v.panelVisible()) ++panelHiddenFrames;
        if (f == 30) { v.pressKey(GLFW_KEY_P); steps = 0; }                 // pause
        if (f == 31) { steps = 0; if (remaining >= 1) v.pressKey(GLFW_KEY_N); }   // single step (+1)
        if (f == 32) { v.pressKey(GLFW_KEY_P); steps = 0; }                 // resume
        if (f == 40) {
            const double rt = v.realTime();
            for (int key : { GLFW_KEY_LEFT_BRACKET, GLFW_KEY_RIGHT_BRACKET, GLFW_KEY_V, GLFW_KEY_V, GLFW_KEY_M, GLFW_KEY_M, GLFW_KEY_M,
                             GLFW_KEY_H, GLFW_KEY_H, GLFW_KEY_1, GLFW_KEY_2, GLFW_KEY_3, GLFW_KEY_4 })
                v.pressKey(key);
            check(v.realTime() == rt && !v.vsync(), "[ ] restore the playback speed; V twice restores VSync off");
        }
        if (f == 45) {   // screenshot at the end of this frame, the panel included
            v.setIncludePanel(true);
            v.pressKey(GLFW_KEY_F12);
        }
        frame(steps, "display modes frame");
        if (f == 31) check(v.clock().paused && v.clock().totalSteps == uint64_t(K - remaining + 1), "P pauses, N single-steps once");
        if (f == 45) {
            for (const auto& e : std::filesystem::directory_iterator(outDir))
                if (e.path().extension() == ".png" && e.path().filename().string().find("heatmap") == std::string::npos &&
                    std::filesystem::last_write_time(e.path()) >= std::filesystem::file_time_type::clock::now() - std::chrono::minutes(5))
                    screenshot = e.path();
        }
    }
    std::printf("  %d frames so far (%d steps), panel drawn in all but %d\n", frames, int(v.clock().totalSteps), panelHiddenFrames);
    check(v.clock().totalSteps == uint64_t(K), "exactly K = " + std::to_string(K) + " steps taken");
    check(*std::min_element(modesSeen, modesSeen + 3) > 0 && *std::min_element(overlaysSeen, overlaysSeen + int(OverlayMetric::Count)) > 0 &&
              *std::min_element(presetsSeen, presetsSeen + 4) > 0,
          "every agent display mode (speed, density, zone, hidden), overlay metric (8; the navigation field's draws no colour on the terrace) and "
          "camera preset (4) rendered");
    check(!screenshot.empty() && std::filesystem::file_size(screenshot) > 10000,
          "F12 screenshot written: " + (screenshot.empty() ? std::string("none") : screenshot.filename().string()));

    // --- The agent state after K steps vs a bare CrowdSim without UI, metrics or rendering ---
    std::printf("\n== viewer.state_unchanged: Agent state after %d steps: viewer (UI, metrics, rendering) vs a bare CrowdSim\n", K);
    const std::vector<GpuBoid> withUi = readState(v.sim().currentStateBuffer(), n);
    std::vector<GpuBoid> bare;
    {
        CrowdSim ref(resolveAsset("shaders"), n);
        ref.upload(spawnBleacherCrowd(n));
        for (int i = 0; i < K; ++i) ref.step(v.sdfTexture());
        bare = readState(ref.currentStateBuffer(), n);
    }
    drainGlErrors("reference run");
    const uint64_t hUi = golden::stateHash(withUi), hBare = golden::stateHash(bare);
    std::printf("  viewer %s | bare %s\n", hex64(hUi).c_str(), hex64(hBare).c_str());
    check(std::memcmp(withUi.data(), bare.data(), withUi.size() * sizeof(GpuBoid)) == 0, "bit-identical (" + std::to_string(n) + " x 32 bytes)");
    if (n == 4096 && K == golden::GOLDEN_STEPS) {
        const uint64_t pin = golden::GOLDEN[golden::GOLDEN_GPU_4096].hash;
        if (driver == golden::GOLDEN_DRIVER) check(hUi == pin, "equals the pinned golden hash GPU N = 4096 (" + hex64(pin) + ")");
        else std::printf("  [WARN] driver differs from the golden pin's; golden %s not compared\n", hex64(pin).c_str());
    } else {
        std::printf("  [INFO] golden hash not compared: it is pinned for N = 4096 after K = %d steps (this run: N = %d, K = %d)\n",
                    golden::GOLDEN_STEPS, n, K);
    }

    // --- On to the end of the evacuation: overlay switches on, playback pauses ---
    std::printf("\n== viewer.evacuation_end: On to the end of the evacuation\n");
    v.setOverlay(false, OverlayMetric::PeakDensity);
    v.setAgentColour(AgentColour::Density);
    v.applyPreset(CameraPreset::Isometric);
    while (!v.evacuationComplete() && v.clock().totalSteps < 6000) frame(8, "evacuation end frame");
    for (int i = 0; i < 4; ++i) frame(0, "evacuation end settle");   // let the last captures signal
    const GpuMetricCounters& c = v.latestCounters();
    std::printf("  completion seen at step %u (t = %.1f s); latest counters: step %u, active %u, evacuated %u (+x %u -x %u +y %u -y %u other %u)\n",
                v.evacuationCompleteStep(), v.evacuationCompleteStep() * DT_REAL_S, c.step, c.active, c.evacuated, c.exits[0], c.exits[1],
                c.exits[2], c.exits[3], c.exits[4]);
    check(v.evacuationComplete() && c.active == 0 && c.evacuated == uint32_t(n), "everyone has left (fence-gated counters)");
    check(v.overlay(), "the heatmap overlay switched on by itself");
    check(v.clock().paused, "the playback paused by itself");
    check(v.evacuationCurvePoints() > 10 && v.evacuationCurveLastPercent() == 100.0f,
          "evacuation curve: " + std::to_string(v.evacuationCurvePoints()) + " points, ends at 100%");
    if (n == 4096)
        check(v.evacuationCompleteStep() >= uint32_t(golden::REFERENCE_EVACUATION_STEP) &&
                  v.evacuationCompleteStep() <= uint32_t(golden::REFERENCE_EVACUATION_STEP + 8 * 5),
              "completion seen within 5 frames after step " + std::to_string(golden::REFERENCE_EVACUATION_STEP) +
              " (the reference evacuation, test_gpu engine.pipeline_invariants)");
    check(g_counterReadings > 50 && g_counterViolations == 0,
          std::to_string(g_counterReadings) + " counter readings, each consistent (active + evacuated = N, exits sum to evacuated)");

    // --- Top-down heatmap export ---
    std::printf("\n== viewer.heatmap_export: Top-down heatmap export\n");
    // Every zone first (the check below), then the default circulation-only scope
    v.setOverlayCirculationOnly(false);
    const std::vector<uint8_t> px = v.renderHeatmapPixels(4096);
    size_t ramp = 0;
    for (size_t i = 0; i + 2 < px.size(); i += 3)
        if (int(px[i + 2]) - int(px[i]) > 40 && px[i + 2] > 100) ++ramp;   // the blue ramp; grey, background and zero grey are not
    const double rampShare = double(ramp) / double(px.size() / 3);
    std::printf("  %zu of %zu pixels on the colour ramp (%.1f%%)\n", ramp, px.size() / 3, 100.0 * rampShare);
    check(rampShare > 0.10, "the overlay colours the floor (peak density, every zone: more than 10% of the image)");
    v.setOverlayCirculationOnly(true);
    {
        const std::vector<uint8_t> pc = v.renderHeatmapPixels(4096);
        size_t rampC = 0;
        for (size_t i = 0; i + 2 < pc.size(); i += 3)
            if (int(pc[i + 2]) - int(pc[i]) > 40 && pc[i + 2] > 100) ++rampC;
        const double shareC = double(rampC) / double(pc.size() / 3);
        std::printf("  circulation zones only: %zu pixels on the colour ramp (%.1f%%)\n", rampC, 100.0 * shareC);
        check(shareC > 0.01 && shareC < rampShare, "circulation zones only (the default): the aisles, walkway and avenues coloured, the "
              "treads neutral (fewer ramp pixels than every zone)");
    }
    const std::filesystem::path heat = v.takeHeatmapExport();
    std::filesystem::path side = heat;
    side.replace_extension(".json");
    check(std::filesystem::file_size(heat) > 10000 && std::filesystem::exists(side), "heatmap PNG (4096 x 4096) and JSON sidecar written: " +
          heat.filename().string());
    drainGlErrors("exports");

    // --- Venue S: the selector's path, the seat spawn, the agents following the navigation
    //     field, the state against a bare CrowdSim, the field's overlay, the completion at the reference step, the capacity ---
    std::printf("\n== viewer.venue_s: Venue S: venue selector, seat spawn, routed evacuation, navigation-field overlay, capacity label, screenshot\n");
    uint64_t phaseSHash = 0;   // the state after GOLDEN_STEPS steps (viewer.background_loading compares the background loading's with it)
    {
        const Venue& vs = venueS();
        const int seats = int(seated::seats(vs.layout).size());
        v.setLoad(1.0);
        v.requestVenue(vs);
        frame(0, "restart venue S");
        check(&v.currentVenue() == &vs && v.population() == seats && v.sim().numBoids() == 4096 && v.clock().totalSteps == 0,
              "venue S through the selector: " + std::to_string(v.population()) + " agents, one per seat (" + std::to_string(seats) +
              " seats), in a 4096-agent buffer, step 0");
        const std::vector<GpuBoid> s0 = readState(v.sim().currentStateBuffer(), v.sim().numBoids());
        v.setAgentColour(AgentColour::Zone);
        v.applyPreset(CameraPreset::Isometric);
        for (int i = 0; i < 30; ++i) frame(2, "venue S frames");
        const std::vector<GpuBoid> s1 = readState(v.sim().currentStateBuffer(), v.sim().numBoids());
        int moved = 0, active = 0;
        for (size_t i = 0; i < s0.size(); ++i) {
            if (s0[i].position.w == 0.0f) continue;
            ++active;
            moved += glm::length(glm::vec3(s1[i].position) - glm::vec3(s0[i].position)) > 0.0f;
        }
        check(active == seats && moved > seats / 2, "routed by the navigation field: after 60 steps " + std::to_string(moved) + " of the " +
              std::to_string(active) + " seated agents have moved");
        const std::string label = v.capacityLabel(), title = v.windowTitle();
        std::printf("  %s\n  title: %s\n", label.c_str(), title.c_str());
        // The title names the model options too (the venue's defaults: the self-test starts S with them)
        const std::string want = "venue S (navigation field, " + modelOptionsLabel(vs, defaultModelOptions(vs)) + ")";
        check(label == "within design capacity" && title.find(want) != std::string::npos && title.find("no routing") == std::string::npos &&
                  v.runningModel() == defaultModelOptions(vs),
              "capacity label (design capacity = the seat count), the title's \"" + want + "\", the venue's default model options");
        // The state after GOLDEN_STEPS steps with the UI, metrics and rendering against a bare CrowdSim on venue S
        for (int f = 0; int(v.clock().totalSteps) < golden::GOLDEN_STEPS; ++f) {
            v.setOverlay(f % 2 == 0, OverlayMetric(f % int(OverlayMetric::Count)));
            frame(std::min(8, golden::GOLDEN_STEPS - int(v.clock().totalSteps)), "venue S to the golden step");
        }
        const std::vector<GpuBoid> withUiS = readState(v.sim().currentStateBuffer(), v.sim().numBoids());
        std::vector<GpuBoid> bareS;
        {
            CrowdSim ref(resolveAsset("shaders"), 4096, vs);
            ref.upload(spawnSeatedCrowd(vs, 4096, 1.0, 1337));
            for (int i = 0; i < golden::GOLDEN_STEPS; ++i) ref.step(0);
            bareS = readState(ref.currentStateBuffer(), 4096);
        }
        drainGlErrors("venue S reference run");
        const uint64_t hS = golden::stateHash(withUiS);
        phaseSHash = hS;
        std::printf("  viewer %s | bare %s\n", hex64(hS).c_str(), hex64(golden::stateHash(bareS)).c_str());
        check(withUiS.size() == bareS.size() && std::memcmp(withUiS.data(), bareS.data(), withUiS.size() * sizeof(GpuBoid)) == 0,
              "venue S after " + std::to_string(golden::GOLDEN_STEPS) + " steps: bit-identical to a bare CrowdSim (4096 x 32 bytes)");
        if (driver == golden::GOLDEN_DRIVER)
            check(hS == golden::GOLDEN_S[0].hash, "equals the pinned golden hash " + std::string(golden::GOLDEN_S[0].name) + " (" +
                  hex64(golden::GOLDEN_S[0].hash) + ")");
        else std::printf("  [WARN] driver differs from the golden pin's; GOLDEN_S not compared\n");
        // The navigation field's overlay: the walking distance over the floor (top-down export image, no file)
        v.setOverlay(true, OverlayMetric::NavDistance);
        frame(0, "venue S navigation-field overlay");
        const std::vector<uint8_t> pxS = v.renderHeatmapPixels(3000);
        size_t rampS = 0;
        for (size_t i = 0; i + 2 < pxS.size(); i += 3)
            if (int(pxS[i + 2]) - int(pxS[i]) > 40 && pxS[i + 2] > 100) ++rampS;
        std::printf("  navigation-field overlay: %zu of %zu pixels on the colour ramp (%.1f%%)\n", rampS, pxS.size() / 3,
                    100.0 * double(rampS) / double(pxS.size() / 3));
        check(double(rampS) / double(pxS.size() / 3) > 0.10, "the navigation-field overlay colours the floor (more than 10% of the image)");
        v.setIncludePanel(true);
        const std::filesystem::path shot = v.takeScreenshot(true);
        check(std::filesystem::file_size(shot) > 10000 && shot.filename().string().rfind("venue_S_N" + std::to_string(seats), 0) == 0,
              "venue S screenshot (navigation-field overlay, panel) written: " + shot.filename().string());
        // On to the end: completion at the reference evacuation of S, every agent through a door
        v.setOverlay(false, OverlayMetric::PeakDensity);
        while (!v.evacuationComplete() && v.clock().totalSteps < 6000) frame(8, "venue S evacuation frame");
        for (int i = 0; i < 4; ++i) frame(0, "venue S settle");
        const GpuMetricCounters& cs = v.latestCounters();
        uint32_t doors = 0;
        for (int e = metrics::EXIT_DOOR0; e < metrics::EXIT_SLOTS; ++e) doors += cs.exits[e];
        std::printf("  completion seen at step %u (t = %.1f s); latest counters: active %u, evacuated %u (avenues %u, doors %u)\n",
                    v.evacuationCompleteStep(), v.evacuationCompleteStep() * DT_REAL_S, cs.active, cs.evacuated,
                    cs.exits[0] + cs.exits[1] + cs.exits[2] + cs.exits[3], doors);
        // The default queue-aware exit choice sends agents through the avenues too
        const uint32_t avenuesS = cs.exits[0] + cs.exits[1] + cs.exits[2] + cs.exits[3];
        const bool exitsOk = v.runningModel().exitChoice == ExitChoice::QueueAware ? avenuesS > 0 && doors > 0 && avenuesS + doors == uint32_t(seats)
                                                                                   : doors == uint32_t(seats);
        check(v.evacuationComplete() && cs.active == 0 && cs.evacuated == uint32_t(seats) && exitsOk && v.overlay() && v.clock().paused,
              "everyone has left (" + std::string(v.runningModel().exitChoice == ExitChoice::QueueAware ? "through the doors and the avenues"
                                                                                                         : "through the concourse doors") +
              "); the overlay switched on and the playback paused by themselves");
        check(v.evacuationCompleteStep() >= uint32_t(golden::REFERENCE_EVACUATION_STEP_S) &&
                  v.evacuationCompleteStep() <= uint32_t(golden::REFERENCE_EVACUATION_STEP_S + 8 * 5),
              "completion seen within 5 frames after step " + std::to_string(golden::REFERENCE_EVACUATION_STEP_S) +
              " (venue S's reference evacuation with the default model)");
        v.setLoad(0.5);
        v.requestRestart();
        frame(1, "venue S at 50% load");
        check(v.population() == int(std::lround(0.5 * seats)), "load 50%: " + std::to_string(v.population()) + " seated agents (a seeded subset)");
        drainGlErrors("venue S");
    }

    // --- Venues M and L: the selector, the generated render mesh, the seat spawn, routed agents moving, the overlay ---
    std::printf("\n== viewer.venues_m_l: Venues M and L: selector, generated mesh, seat spawn, routed agents, overlay\n");
    for (const Venue* vg : { &venueM(), &venueL() }) {
        const int seats = int(seated::seats(vg->layout).size());
        v.setLoad(1.0);
        v.requestVenue(*vg);
        frame(0, (std::string("restart venue ") + vg->name).c_str());
        int buf = 256;
        while (buf < seats) buf *= 2;
        check(&v.currentVenue() == vg && v.population() == seats && v.sim().numBoids() == buf && v.clock().totalSteps == 0,
              std::string("venue ") + vg->name + " through the selector: " + std::to_string(v.population()) + " agents, one per seat, in a " +
              std::to_string(buf) + "-agent buffer");
        const std::vector<GpuBoid> m0 = readState(v.sim().currentStateBuffer(), v.sim().numBoids());
        v.setOverlay(true, OverlayMetric::PeakDensity);
        v.applyPreset(CameraPreset::Isometric);
        for (int i = 0; i < 20; ++i) frame(3, (std::string("venue ") + vg->name + " frames").c_str());
        const std::vector<GpuBoid> m1 = readState(v.sim().currentStateBuffer(), v.sim().numBoids());
        int moved = 0;
        for (size_t i = 0; i < m0.size(); ++i) moved += m0[i].position.w != 0.0f && glm::length(glm::vec3(m1[i].position) - glm::vec3(m0[i].position)) > 0.0f;
        check(moved > seats / 2, std::string("venue ") + vg->name + ": after 60 steps " + std::to_string(moved) + " of " + std::to_string(seats) +
              " seated agents have moved");
        const std::vector<uint8_t> pm = v.renderHeatmapPixels(3000);
        size_t rampM = 0;
        for (size_t i = 0; i + 2 < pm.size(); i += 3)
            if (int(pm[i + 2]) - int(pm[i]) > 40 && pm[i + 2] > 100) ++rampM;
        std::printf("  venue %s: peak-density overlay (circulation zones) %.1f%% of the 3000 px image on the colour ramp\n", vg->name,
                    100.0 * double(rampM) / double(pm.size() / 3));
        check(rampM > 0, std::string("venue ") + vg->name + ": the overlay colours its circulation floor (the whole metric grid in the export)");
        drainGlErrors((std::string("venue ") + vg->name).c_str());
    }

    // --- Background loading (the interactive SWARM's start and restarts; the phases above restart within the frame): venue S through
    //     the loading screen, from venue L. Its programs are compiled ahead (in parallel, or one per frame without parallel shader
    //     compile: --no-parallel-compile) and every one is used, and the state after GOLDEN_STEPS steps is the synchronous restart's ---
    std::printf("\n== viewer.background_loading: Background loading: venue S through the loading screen (parallel shader compile %s)\n", parallelShaderCompile() ? "on" : "off");
    {
        const Venue& vs = venueS();
        const ProgramCacheStats before = programCacheStats();
        v.setAsyncLoading(true);
        v.setLoad(1.0);
        v.selectModel(defaultModelOptions(vs));
        v.requestVenue(vs);
        int loadingFrames = 0;
        const auto tl = clock::now();
        do {
            v.frame(1.0 / 60.0);   // the interactive frame: the loading screen, then the venue
            ++frames;
            ++loadingFrames;
            drainGlErrors("background loading");
        } while (v.loading() && std::chrono::duration<double>(clock::now() - tl).count() < 900.0);
        v.setAsyncLoading(false);
        const ProgramCacheStats after = programCacheStats();
        const int seats = int(seated::seats(vs.layout).size());
        check(!v.loading() && &v.currentVenue() == &vs && v.population() == seats && v.clock().totalSteps == 0,
              "venue S loaded in the background in " + std::to_string(loadingFrames) + " frames (" +
                  std::to_string(std::chrono::duration<double>(clock::now() - tl).count()) + " s): " + std::to_string(v.population()) +
                  " agents, step 0");
        check(after.ahead - before.ahead == 12 && v.lastLoadUnusedPrograms() == 0,
              "its 12 programs (scene 2, simulation 8, metrics 2) compiled ahead and all of them used (" + std::to_string(after.ahead - before.ahead) +
                  " taken, " + std::to_string(v.lastLoadUnusedPrograms()) + " unused)");
        while (int(v.clock().totalSteps) < golden::GOLDEN_STEPS)
            frame(std::min(8, golden::GOLDEN_STEPS - int(v.clock().totalSteps)), "background-loaded venue S to the golden step");
        const uint64_t h = golden::stateHash(readState(v.sim().currentStateBuffer(), v.sim().numBoids()));
        std::printf("  background-loaded %s | synchronous restart (viewer.venue_s) %s\n", hex64(h).c_str(), hex64(phaseSHash).c_str());
        check(h == phaseSHash, "after " + std::to_string(golden::GOLDEN_STEPS) + " steps: bit-identical to the synchronous restart's state (viewer.venue_s)");
        if (driver == golden::GOLDEN_DRIVER)
            check(h == golden::GOLDEN_S[0].hash, "equals the pinned golden hash " + std::string(golden::GOLDEN_S[0].name) + " (" +
                  hex64(golden::GOLDEN_S[0].hash) + ")");
        drainGlErrors("background loading, golden step");
    }

    // --- The capability check: the binding lists against the compiled programs, known answers, the selector clicked with another GPU's limits ---
    std::printf("\n== viewer.gpu_capabilities: GPU capability check: requirements against the compiled programs, a GPU with fewer bindings, the selector\n");
    {
        const std::filesystem::path shaders = resolveAsset("shaders");
        const auto listsMatch = [&](const Venue& venue, const ModelOptions& model) {
            std::vector<ProgramSpec> specs = CrowdSim::programSpecs(shaders, venue, model);
            std::vector<ProgramBindings> lists = CrowdSim::programBindings(venue, model);
            for (const ProgramSpec& s : metrics::CrowdMetrics::programSpecs(shaders, venue.metricGridRes, venue.seated() ? &venue : nullptr)) specs.push_back(s);
            for (const ProgramBindings& b : metrics::CrowdMetrics::programBindings(venue.seated())) lists.push_back(b);
            for (const ProgramSpec& s : SceneRenderer::programSpecs(shaders)) specs.push_back(s);
            for (const ProgramBindings& b : SceneRenderer::programBindings()) lists.push_back(b);
            std::string differs;
            bool sameCount = specs.size() == lists.size();
            for (size_t i = 0; sameCount && i < specs.size(); ++i) {
                const GLuint program = loadProgram(specs[i]);
                // Every driver may drop a block its compiler removed; the pinned driver keeps every declared one
                const auto stageMatches = [&](std::vector<GLuint> listed, GLenum stage) {
                    const std::vector<GLuint> active = activeBindings(program, stage);
                    std::sort(listed.begin(), listed.end());
                    return driver == golden::GOLDEN_DRIVER ? active == listed : std::includes(listed.begin(), listed.end(), active.begin(), active.end());
                };
                const bool ok = lists[i].compute ? stageMatches(lists[i].ssbo, GL_NONE)
                                                 : stageMatches(lists[i].ssbo, GL_REFERENCED_BY_VERTEX_SHADER) &&
                                                       stageMatches(lists[i].fragmentSsbo, GL_REFERENCED_BY_FRAGMENT_SHADER);
                glDeleteProgram(program);
                if (!ok) differs += (differs.empty() ? "" : ", ") + lists[i].name;
            }
            check(sameCount && differs.empty(), std::string("venue ") + venue.name + " (" + modelOptionsLabel(venue, model) + "): every program's SSBO bindings are its list's (" +
                  std::to_string(specs.size()) + " programs)" + (differs.empty() ? "" : "; differ: " + differs));
        };
        for (const Venue* vc : { &terraceVenue(), &venueS(), &venueM(), &venueL() }) listsMatch(*vc, defaultModelOptions(*vc));
        listsMatch(venueS(), ModelOptions{});   // the nearest exit: no choice pass, other bindings

        const GpuLimits real = v.gpuLimits();
        // The render programs' stages, the same for every venue: one block short in either stops the terrace too
        const GpuRequirements needS = venueRequirements(venueS(), v.selectedModel(), 4096);
        GpuLimits stage = real;
        stage.vertexSsboBlocks = needS.vertexSsboBlocks - 1;
        v.setGpuLimits(stage);
        const std::string whyVertex = v.venueShortfall(terraceVenue());
        stage = real;
        stage.fragmentSsboBlocks = needS.fragmentSsboBlocks - 1;
        v.setGpuLimits(stage);
        const std::string whyFragment = v.venueShortfall(terraceVenue());
        std::printf("  render stages need %d / %d SSBOs (vertex / fragment); one short: %s | %s\n", needS.vertexSsboBlocks, needS.fragmentSsboBlocks, whyVertex.c_str(), whyFragment.c_str());
        check(needS.vertexSsboBlocks == int(SceneRenderer::programBindings()[0].ssbo.size()) && needS.fragmentSsboBlocks == int(SceneRenderer::programBindings()[1].fragmentSsbo.size()) &&
                  whyVertex.find("SSBOs per vertex shader") != std::string::npos && whyFragment.find("SSBOs per fragment shader") != std::string::npos,
              "one SSBO short in the vertex or the fragment stage: every venue is refused, the terrace too, and the reason names the stage");
        GpuLimits few = real;
        few.ssboBindings = 16;
        few.simulated = true;
        v.setGpuLimits(few);
        const std::string whyS = v.venueShortfall(venueS());
        std::printf("  with 16 bindings: S: %s\n", whyS.c_str());
        check(v.venueShortfall(terraceVenue()).empty() && whyS.find("needs 20 SSBO bindings, this GPU has 16") != std::string::npos && !v.venueShortfall(venueL()).empty(),
              "a GPU with 16 SSBO bindings: the terrace can run, S and L cannot, the reason names both numbers");
        // Real clicks on the panel's selector: a disabled venue cannot be chosen, an enabled one can
        v.setPanelVisible(true);
        v.selectVenue(venueS());
        ImGuiIO& io = ImGui::GetIO();
        const auto click = [&](glm::vec2 p, const char* what) {
            io.AddMousePosEvent(p.x, p.y);
            frame(0, what);
            io.AddMouseButtonEvent(ImGuiMouseButton_Left, true);
            frame(0, what);
            io.AddMouseButtonEvent(ImGuiMouseButton_Left, false);
            frame(0, what);
        };
        frame(0, "selector: panel drawn");
        click(v.venueComboCentre(), "selector: open");
        frame(0, "selector: open");
        const std::filesystem::path shot = v.takeScreenshot(true);
        std::printf("  selector open: %s\n", shot.filename().string().c_str());
        click(v.venueItemCentre(3), "selector: the disabled venue L");
        check(&v.selectedVenue() == &venueS(), "clicking the disabled venue L does not select it");
        frame(0, "selector: still open");
        click(v.venueItemCentre(0), "selector: the terrace");
        check(&v.selectedVenue() == &terraceVenue(), "clicking the enabled terrace selects it");
        io.AddMousePosEvent(-FLT_MAX, -FLT_MAX);
        frame(0, "selector: done");
        v.selectVenue(v.currentVenue());
        v.setGpuLimits(real);
        drainGlErrors("capability check");
    }

    // --- Widget IDs over the whole run ---
    std::printf("\n== viewer.widget_ids_all_frames: Dear ImGui widget IDs over every frame since the known answer\n");
    std::string conflictNames;
    for (const std::string& c : idcheck::samples()) conflictNames += (conflictNames.empty() ? "" : ", ") + c;
    check(idcheck::conflicts() == 0, "no widget ID conflict in " + std::to_string(frames - 1) + " frames with the panel" +
          (conflictNames.empty() ? std::string() : " (" + std::to_string(idcheck::conflicts()) + ": " + conflictNames + ")"));
    idcheck::setEnabled(false);

    // --- GL errors ---
    std::printf("\n== viewer.gl_errors: OpenGL errors\n");
    check(g_glErrors == 0, "glGetError clean after every one of " + std::to_string(frames) + " frames" +
          (g_glErrors ? " (" + std::to_string(g_glErrors) + ", first " + g_firstGlError + ")" : std::string()));
    for (const std::string& m : g_debug.samples) std::printf("    debug: %s\n", m.c_str());
    check(g_debug.errors == 0, "no GL debug errors (" + std::to_string(g_debug.errors) + " errors, " + std::to_string(g_debug.warnings) +
          " warnings)");

    std::printf("\n%d frames, %.1f s | %s: %d check(s) failed\n", frames, std::chrono::duration<double>(clock::now() - t0).count(),
                g_failures == 0 ? "SELFTEST ALL PASSED" : "SELFTEST FAILED", g_failures);
    return g_failures == 0 ? 0 : 1;
}

} // namespace swarm::viewer
