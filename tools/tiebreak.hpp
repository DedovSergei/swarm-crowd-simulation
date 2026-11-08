#pragma once

// Mutual-standoff tie-break activations: how often the predict pass's tie-break of the headway rule acts
// (physics.comp: two agents each ahead in the other's lane; only the one that has the other more directly
// ahead yields, ties by boidID). The predict pass built with DIAG_TIEBREAK (a shader variant; never in production)
// accumulates the counters below per dispatch into a buffer at BINDING; run() zeroes and reads it after every step.
// Test and tool code only (readbacks every step): test_gpu validation.plausibility_terrace and fd_harness tiebreak.

#include <glad/glad.h>

#include <swarm/crowd_sim.hpp>
#include <swarm/gpu_types.hpp>

#include "plausibility.hpp"

#include <array>
#include <cstdint>
#include <filesystem>
#include <vector>

namespace swarm::tiebreak {

constexpr GLuint BINDING = 10;   // physics.comp's TieBreakCounters
constexpr const char* DEFINE = "#define DIAG_TIEBREAK\n";
// physics.comp's counters, per step
enum Counter {
    CANDIDATES,   // in-lane candidates in a mutual standoff (each standoff pair is seen from both agents)
    STANDOFFS,    // of them discarded as the leader by the tie-break: one per standoff pair, the activations
    TIES,         // of them exact ties (equal projections) decided by boidID (two per tied pair)
    LEADER,       // agents whose leader the tie-break changed (s differs from the literal rule's)
    SPEED,        // agents whose v_des it changed
    RELEASED,     // agents it released from a standstill (literal v_des = 0, v_des > 0)
    COUNTERS
};
inline const char* counterName(int c) {
    static const char* names[COUNTERS] = { "mutual candidates", "standoffs resolved (activations)", "exact ties (by boidID)",
                                           "agents: leader changed", "agents: v_des changed", "agents: released from v_des 0" };
    return names[c];
}
using Counters = std::array<uint32_t, COUNTERS>;

struct Run {
    int steps = 0, evacStep = -1;
    std::vector<Counters> perStep;   // after step k + 1
    std::vector<int> active;         // active agents after step k + 1
    // plausibility::chainHash over every step's agent state: equal to plausibility::Result::trajectoryHash of a production
    // run from the same spawn when the instrumented shaders compute bit-identical states
    uint64_t trajectoryHash = 0xcbf29ce484222325ull;

    uint64_t total(int c) const {
        uint64_t t = 0;
        for (const Counters& s : perStep) t += s[size_t(c)];
        return t;
    }
    uint32_t maxPerStep(int c, int* at = nullptr) const {
        uint32_t m = 0;
        for (size_t k = 0; k < perStep.size(); ++k)
            if (perStep[k][size_t(c)] > m) { m = perStep[k][size_t(c)]; if (at) *at = int(k) + 1; }
        return m;
    }
    int stepsWith(int c) const {
        int n = 0;
        for (const Counters& s : perStep) n += s[size_t(c)] > 0;
        return n;
    }
};

// Steps a CrowdSim built from 'variantShaders' (the shader folder with DEFINE after physics.comp's #version line) from
// 'spawn' until every agent has left or maxSteps
inline Run run(const std::filesystem::path& variantShaders, GLuint sdfTex, const std::vector<GpuBoid>& spawn, int maxSteps) {
    Run r;
    const int n = int(spawn.size());
    CrowdSim sim(variantShaders, n);
    sim.upload(spawn);
    GLuint buf = 0;
    glGenBuffers(1, &buf);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, buf);
    const Counters zero{};
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(Counters), zero.data(), CrowdSim::SSBO_USAGE);
    std::vector<GpuBoid> st(static_cast<size_t>(n));
    for (int step = 1; step <= maxSteps; ++step) {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, buf);
        glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(Counters), zero.data());
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BINDING, buf);
        sim.step(sdfTex);
        glMemoryBarrier(GL_BUFFER_UPDATE_BARRIER_BIT);
        Counters c{};
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, buf);
        glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(Counters), c.data());
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, sim.currentStateBuffer());
        glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, GLsizeiptr(st.size() * sizeof(GpuBoid)), st.data());
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
        plausibility::chainHash(r.trajectoryHash, st);
        int active = 0;
        for (const GpuBoid& b : st) active += b.position.w != 0.0f;
        r.perStep.push_back(c);
        r.active.push_back(active);
        r.steps = step;
        if (active == 0) { r.evacStep = step; break; }
    }
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BINDING, 0);
    glDeleteBuffers(1, &buf);
    return r;
}

} // namespace swarm::tiebreak
