#pragma once

// SWARM --selftest-ui: the viewer in a hidden window, scripted. It runs frames with the panel drawn,
// cycling every agent display mode, every overlay metric (on and off), every camera preset and the key bindings,
// exports a screenshot (F12) and a top-down heatmap, checks glGetError after every frame and the GL debug output,
// and checks that the agent state after K steps equals the state of a bare CrowdSim stepped K times without any UI
// (bit-identical; at N = 4096, K = golden::GOLDEN_STEPS also the pinned golden hash). Then it runs
// on to the end of the evacuation and checks the completion behaviour (overlay on, playback paused, counters; at N = 4096
// at golden::REFERENCE_EVACUATION_STEP). Returns the process exit code.

#include <glad/glad.h>   // before GLFW (GLFW would include the system GL header)
#include <GLFW/glfw3.h>

#include <filesystem>

#include "golden_state.hpp"   // tools/: GOLDEN_STEPS, the default K

namespace swarm::viewer {

struct SelfTestOptions {
    int agents = 4096;
    int steps = golden::GOLDEN_STEPS;   // K
    std::filesystem::path outDir;       // exports; empty: <source tree>/out/selftest
};

int runSelfTestUi(GLFWwindow* hiddenWindow, const SelfTestOptions& opts);

} // namespace swarm::viewer
