#pragma once

// Exit choice checks (test_gpu nav.exit_choice, nav_probe choice): a GPU harness that runs physics.comp's real choice
// pass (PHYSICS_PASS 0) on any candidate table, the CPU mirror on the same data (nav::choiceStep), and the
// known-answer world: a 20 m x 10 m room with two 1.2 m doors in its left and right walls at equal distance from the room's centre.

#include "nav_check.hpp"

#include <swarm/exit_choice.hpp>
#include <swarm/shader.hpp>
#include <swarm/venue.hpp>

#include <glad/glad.h>

#include <cstring>
#include <filesystem>
#include <string>
#include <vector>

namespace choice_check {

using namespace swarm;

// The two-door room: interior [0, 20] x [0, 10] m, 0.3 m walls, doors (1.20 m) at y 4.4 .. 5.6 in the left (exit 0) and right
// (exit 1) walls, the exit regions beyond the walls' outer faces; point agents (body 0). Grid: 0.1 m cells from -1 m, symmetric
// about x = 10 (cell centres at 9.95 and 10.05).
struct Room {
    nav::RectGeometry geo;
    nav::Field grid;
    nav::ChoiceTable table;
    Room()
        : geo(nav_check::roomWalls(0.0f, 0.0f, 20.0f, 10.0f, 0.3f, { { 3, 4.4f, 5.6f }, { 1, 4.4f, 5.6f } }),
              { { { -1.0f, 4.4f }, { -0.3f, 5.6f } }, { { 20.3f, 4.4f }, { 21.0f, 5.6f } } }) {
        geo.setExitWidths({ 1.2f, 1.2f });
        grid = nav::buildGrid(geo, nav_check::testGrid(-1.0f, 22.0f, 0.1));
        table = nav::buildChoiceTable(geo, grid);
    }
};

// An agent at (x, y) metres in the room (the choice reads xy only)
inline GpuBoid agentAt(float x, float y, bool active = true) {
    GpuBoid b{};
    b.position = glm::vec4(x, y, 0.0f, active ? 1.0f : 0.0f);
    return b;
}

// physics.comp PHYSICS_PASS 0 on a table of its own: compiled with venue S's preamble (the venue code it references) and the table's
// grid and exits in place of S's (#undef / #define after the venue preamble); the buffers of CrowdSim's choice pass
struct GpuHarness {
    GLuint prog = 0, boids = 0, table = 0, entries = 0, assign = 0, counters = 0, work = 0, pending = 0;
    int n = 0;
    uint32_t step = 0;
    GLint locNum = -1, locStep = -1, locStage = -1;

    static std::string gridOverride(const nav::Grid& g) {
        return "#undef NAV_SURFACE_RULE\n#undef NAV_RES\n#undef NAV_ORIGIN\n#undef NAV_INV_CELL\n#define NAV_RES " + std::to_string(g.res) + "\n#define NAV_ORIGIN " +
               glslFloatLiteral(g.origin) + "\n#define NAV_INV_CELL " + glslFloatLiteral(g.invCell) + "\n";
    }
    template <class T> static GLuint buffer(const T* data, size_t bytes) {
        GLuint b = 0;
        glGenBuffers(1, &b);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, b);
        glBufferData(GL_SHADER_STORAGE_BUFFER, GLsizeiptr(bytes), data, GL_DYNAMIC_COPY);
        return b;
    }
    GpuHarness(const std::filesystem::path& shaderDir, const nav::ChoiceTable& t, const std::vector<GpuBoid>& state) : n(int(state.size())) {
        prog = loadComputeProgram(shaderDir / "physics.comp", "#define PHYSICS_PASS 0\n" + gridOverride(t.grid) + nav::choicePreambleDefines(t), &venueS());
        locNum = glGetUniformLocation(prog, "numBoids");
        locStep = glGetUniformLocation(prog, "u_choiceStep");
        locStage = glGetUniformLocation(prog, "u_choiceStage");
        const size_t padded = (state.size() + 127) / 128 * 128;
        std::vector<GpuBoid> b(state);
        b.resize(padded, agentAt(0.0f, 0.0f, false));
        boids = buffer(b.data(), b.size() * sizeof(GpuBoid));
        table = buffer(t.index.data(), t.index.size() * 4);   // the compact table's index and entries
        entries = buffer(t.entries.data(), std::max<size_t>(1, t.entries.size()) * sizeof(GpuNavChoiceCell));
        const std::vector<uint32_t> none(padded, nav::CHOICE_NONE);
        assign = buffer(none.data(), none.size() * 4);
        pending = buffer(none.data(), none.size() * 4);
        const GpuChoiceCounters c{};
        counters = buffer(&c, sizeof c);
        const std::vector<uint8_t> zeros(sizeof(GpuChoiceWork), 0);
        work = buffer(zeros.data(), zeros.size());
    }
    ~GpuHarness() {
        for (GLuint b : { boids, table, entries, assign, counters, work, pending }) glDeleteBuffers(1, &b);
        glDeleteProgram(prog);
    }
    void setState(const std::vector<GpuBoid>& state) {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, boids);
        glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, GLsizeiptr(state.size() * sizeof(GpuBoid)), state.data());
    }
    void setAssign(const std::vector<uint32_t>& a) {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, assign);
        glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, GLsizeiptr(a.size() * 4), a.data());
    }
    void setCounters(const GpuChoiceCounters& c) {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, counters);
        glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, GLsizeiptr(sizeof c), &c);
    }
    void setAhead(const std::vector<uint32_t>& a) {   // GpuChoiceWork::ahead (nav::ChoiceState::ahead's layout)
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, work);
        glBufferSubData(GL_SHADER_STORAGE_BUFFER, GLintptr(offsetof(GpuChoiceWork, ahead)), GLsizeiptr(a.size() * 4), a.data());
    }
    // One choice step: CrowdSim::dispatchChoice's sequence
    void run() {
        glUseProgram(prog);
        glUniform1i(locNum, n);
        glUniform1ui(locStep, step);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, boids);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 13, table);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 19, entries);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 14, assign);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 15, counters);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 16, work);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 17, pending);
        const GLuint groups = GLuint((n + 127) / 128);
        glUniform1i(locStage, 3);   // the queue ahead's prefix sums
        glDispatchCompute(1, 1, 1);
        glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
        glUniform1i(locStage, 1);
        glDispatchCompute(groups, 1, 1);
        glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
        glUniform1i(locStage, 2);
        glDispatchCompute(1, 1, 1);
        glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_BUFFER_UPDATE_BARRIER_BIT);
        const GLuint zero = 0;
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, counters);
        glClearBufferSubData(GL_SHADER_STORAGE_BUFFER, GL_R32UI, GLintptr((step & 1u) ? 0 : nav::CHOICE_QUEUE_STRIDE) * 4, nav::CHOICE_QUEUE_STRIDE * 4,
                             GL_RED_INTEGER, GL_UNSIGNED_INT, &zero);
        glUniform1i(locStage, 0);
        glDispatchCompute(groups, 1, 1);
        glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_BUFFER_UPDATE_BARRIER_BIT);
        ++step;
    }
    std::vector<uint32_t> readAssign() const {
        std::vector<uint32_t> a(static_cast<size_t>(n));
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, assign);
        glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, GLsizeiptr(a.size() * 4), a.data());
        return a;
    }
    GpuChoiceCounters readCounters() const {
        GpuChoiceCounters c{};
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, counters);
        glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, GLsizeiptr(sizeof c), &c);
        return c;
    }
};

// The counts the next step reads (qRead of choice step 'step')
inline const uint32_t* nextQueue(const GpuChoiceCounters& c, uint32_t step) { return c.queue + (step & 1u) * uint32_t(nav::CHOICE_QUEUE_STRIDE); }

} // namespace choice_check
