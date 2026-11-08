#include <swarm/crowd_sim.hpp>

#include <swarm/nav_field.hpp>
#include <swarm/sdf.hpp>
#include <swarm/shader.hpp>

#include <glm/glm.hpp>

#include <algorithm>
#include <cmath>
#include <iterator>
#include <random>
#include <stdexcept>
#include <string>
#include <utility>

namespace fs = std::filesystem;

namespace swarm {

CrowdSim::CrowdSim(const fs::path& shaderDir, int numBoids, GLenum ssboUsage) : CrowdSim(shaderDir, numBoids, terraceVenue(), ssboUsage) {}

CrowdSim::CrowdSim(const fs::path& shaderDir, int numBoids, const Venue& venue, GLenum ssboUsage)
    : CrowdSim(shaderDir, numBoids, venue, defaultModelOptions(venue), ssboUsage) {}

std::vector<ProgramSpec> CrowdSim::programSpecs(const fs::path& shaderDir, const Venue& venue, const ModelOptions& options) {
    // Every program with the venue's preamble (the terrace: empty); physics.comp also with the
    // model options' preamble (empty for the terrace and for the nearest-exit, level-speed model)
    const ModelOptions o = effectiveModelOptions(venue, options);
    const std::string model = modelPreamble(venue, o);
    const Venue* v = &venue;
    std::vector<ProgramSpec> s = {
        { shaderDir / "calc_grid.comp", {}, {}, v },
        { shaderDir / "bitonic_sort.comp", {}, {}, v },
        { shaderDir / "bitonic_sort_shared.comp", {}, {}, v },
        { shaderDir / "reorder.comp", {}, {}, v },
        // physics.comp's three passes: predict, projection iteration, final (projection + static contacts)
        { shaderDir / "physics.comp", {}, "#define PHYSICS_PASS 1\n" + model, v },
        { shaderDir / "physics.comp", {}, "#define PHYSICS_PASS 2\n" + model, v },
        { shaderDir / "physics.comp", {}, "#define PHYSICS_PASS 3\n" + model, v },
    };
    if (o.exitChoice == ExitChoice::QueueAware) s.push_back({ shaderDir / "physics.comp", {}, "#define PHYSICS_PASS 0\n" + model, v });
    return s;
}

std::vector<ProgramBindings> CrowdSim::programBindings(const Venue& venue, const ModelOptions& options) {
    const ModelOptions o = effectiveModelOptions(venue, options);
    // Physics.comp's blocks for every pass, then each pass's own
    std::vector<GLuint> physics = { BIND_GRID, BIND_CELLS, BIND_SLOT_IN };
    if (nav::hasField(venue)) physics.push_back(BIND_NAV);
    if (o.exitChoice == ExitChoice::QueueAware) {
        physics.push_back(BIND_NAV_CHOICE);
        physics.push_back(BIND_NAV_CHOICE_ENTRY);
        physics.push_back(BIND_CHOICE_ASSIGN);
    }
    const auto with = [&](std::initializer_list<GLuint> own) {
        std::vector<GLuint> b = physics;
        b.insert(b.end(), own);
        return b;
    };
    std::vector<ProgramBindings> p = {
        { "calc_grid", true, { BIND_BOIDS_IN, BIND_GRID } },
        { "bitonic_sort", true, { BIND_GRID } },
        { "bitonic_sort_shared", true, { BIND_GRID } },
        { "reorder", true, { BIND_BOIDS_IN, BIND_GRID, BIND_CELLS, BIND_BOIDS_SORTED } },
        { "physics predict", true, with({ BIND_SLOT_OUT, BIND_SLOT_PLANES }) },
        { "physics projection", true, with({ BIND_SLOT_OUT, BIND_SLOT_PLANES }) },
        { "physics final", true, with({ BIND_BOIDS_IN, BIND_BOIDS_OUT, BIND_SLOT_PLANES }) },
    };
    if (o.exitChoice == ExitChoice::QueueAware)
        p.push_back({ "physics choice", true, with({ BIND_BOIDS_IN, BIND_CHOICE_COUNTERS, BIND_CHOICE_WORK, BIND_CHOICE_PENDING }) });
    return p;
}

std::vector<GpuBufferUse> CrowdSim::bufferUses(const Venue& venue, const ModelOptions& options, int numBoids) {
    const int64_t n = numBoids, boidBytes = n * int64_t(sizeof(GpuBoid));
    std::vector<GpuBufferUse> b = {
        { "the agent state", boidBytes },
        { "the sorted grid", n * int64_t(sizeof(GpuGridInfo)) },
        { "the neighbour cells", int64_t(venue.gridRes) * venue.gridRes * int64_t(sizeof(GpuCellData)) },
        { "the wall planes", n * 16 },
    };
    if (nav::hasField(venue)) {
        const int64_t cells = int64_t(nav::venueGrid(venue).cells());
        b.push_back({ "the navigation field", cells * int64_t(sizeof(GpuNavCell)) });   // the nearest exit's predict pass, or the distance overlay
        if (effectiveModelOptions(venue, options).exitChoice == ExitChoice::QueueAware) {
            b.push_back({ "the exit choice index", cells * 4 });
            b.push_back({ "the exit assignments", n * 4 });
            b.push_back({ "the exit choice counters", int64_t(sizeof(GpuChoiceCounters)) });
            b.push_back({ "the exit choice work", int64_t(sizeof(GpuChoiceWork)) });
        }
    }
    return b;
}

CrowdSim::CrowdSim(const fs::path& shaderDir, int numBoids, const Venue& venue, const ModelOptions& options, GLenum ssboUsage)
    : numBoids_(numBoids), venue_(&venue), options_(effectiveModelOptions(venue, options)) {
    // Bitonic sort needs a power of two; the dispatches assume whole 256- and 128-wide groups.
    if (numBoids < 256 || (numBoids & (numBoids - 1)) != 0)
        throw std::invalid_argument("CrowdSim: numBoids must be a power of two >= 256, got " + std::to_string(numBoids));
    const bool queueAware = options_.exitChoice == ExitChoice::QueueAware;

    // Before any table or program (programSpecs' preamble loads or builds the exit choice table): what the GPU must offer
    const GpuLimits limits = readGpuLimits();
    if (const std::string why = gpuShortfall(gpuRequirements(programBindings(venue, options_), bufferUses(venue, options_, numBoids)), limits); !why.empty())
        throw std::runtime_error("CrowdSim: venue " + std::string(venue.name) + " " + why);
    if (queueAware) {   // its exact size is known here, and no program is compiled yet
        const size_t entries = std::max<size_t>(1, nav::choiceForVenue(venue).entries.size());
        if (const std::string why = gpuBlockShortfall("the exit choice table", int64_t(entries * sizeof(GpuNavChoiceCell)), false, limits); !why.empty())
            throw std::runtime_error("CrowdSim: venue " + std::string(venue.name) + " " + why);
    }

    // The programs of programSpecs, in its order
    const std::vector<ProgramSpec> programs = programSpecs(shaderDir, venue, options_);
    hashProg_ = loadProgram(programs[0]);
    sortProg_ = loadProgram(programs[1]);
    sortSharedProg_ = loadProgram(programs[2]);
    cellsProg_ = loadProgram(programs[3]);
    physProg_ = loadProgram(programs[4]);
    projProg_ = loadProgram(programs[5]);
    finalProg_ = loadProgram(programs[6]);
    if (queueAware) {   // the choice pass
        choiceProg_ = loadProgram(programs[7]);
        locChoiceNum_ = glGetUniformLocation(choiceProg_, "numBoids");
        locChoiceStep_ = glGetUniformLocation(choiceProg_, "u_choiceStep");
        locChoiceStage_ = glGetUniformLocation(choiceProg_, "u_choiceStage");
    }

    locHashNum_ = glGetUniformLocation(hashProg_, "num");
    locSortJ_ = glGetUniformLocation(sortProg_, "j");
    locSortK_ = glGetUniformLocation(sortProg_, "k");
    locSharedNum_ = glGetUniformLocation(sortSharedProg_, "num");
    locSharedMode_ = glGetUniformLocation(sortSharedProg_, "mode");
    locSharedK_ = glGetUniformLocation(sortSharedProg_, "k");
    {   // the shared-memory sort's tile is two elements per invocation
        GLint local[3] = {};
        glGetProgramiv(sortSharedProg_, GL_COMPUTE_WORK_GROUP_SIZE, local);
        if (local[0] * 2 != SORT_TILE)
            throw std::runtime_error("CrowdSim: bitonic_sort_shared.comp's local size does not match SORT_TILE / 2");
    }
    locCellsNum_ = glGetUniformLocation(cellsProg_, "num");
    locPhysNum_ = glGetUniformLocation(physProg_, "numBoids");
    locPhysSdfMin_ = glGetUniformLocation(physProg_, "u_sdfMin");
    locPhysSdfInvSpacing_ = glGetUniformLocation(physProg_, "u_sdfInvSpacing");
    locPhysSdfTex_ = glGetUniformLocation(physProg_, "u_sdfTexture");
    locProjNum_ = glGetUniformLocation(projProg_, "numBoids");
    locFinalNum_ = glGetUniformLocation(finalProg_, "numBoids");
    locFinalProject_ = glGetUniformLocation(finalProg_, "u_project");
    locFinalSdfMin_ = glGetUniformLocation(finalProg_, "u_sdfMin");
    locFinalSdfInvSpacing_ = glGetUniformLocation(finalProg_, "u_sdfInvSpacing");
    locFinalSdfTex_ = glGetUniformLocation(finalProg_, "u_sdfTexture");

    const GLsizeiptr boidBytes = GLsizeiptr(numBoids) * sizeof(GpuBoid);
    glGenBuffers(2, boids_);
    for (GLuint b : boids_) {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, b);
        glBufferData(GL_SHADER_STORAGE_BUFFER, boidBytes, nullptr, ssboUsage);
    }
    glGenBuffers(1, &grid_);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, grid_);
    glBufferData(GL_SHADER_STORAGE_BUFFER, GLsizeiptr(numBoids) * sizeof(GpuGridInfo), nullptr, ssboUsage);
    glGenBuffers(1, &cells_);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, cells_);
    glBufferData(GL_SHADER_STORAGE_BUFFER, GLsizeiptr(venue.gridRes) * venue.gridRes * sizeof(GpuCellData), nullptr, ssboUsage);
    glGenBuffers(1, &sorted_);   // the gathered copy: another N x 32 B, written and read by the GL
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, sorted_);
    glBufferData(GL_SHADER_STORAGE_BUFFER, boidBytes, nullptr, ssboUsage);
    glGenBuffers(1, &slots_);    // the projection's second slot buffer: another N x 32 B
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, slots_);
    glBufferData(GL_SHADER_STORAGE_BUFFER, boidBytes, nullptr, ssboUsage);
    glGenBuffers(1, &planes_);   // per slot: wall plane + grounded flag of the predict pass: N x 16 B
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, planes_);
    glBufferData(GL_SHADER_STORAGE_BUFFER, GLsizeiptr(numBoids) * 16, nullptr, ssboUsage);
    if (nav::hasField(venue) && !queueAware) navBuffer();   // the nearest-exit field, read by the predict pass
    if (queueAware) {
        // The candidate table, read-only; the assigned exits (4 B per agent) and the
        // counters, written by the choice pass (GL_DYNAMIC_COPY, as every GPU-written buffer)
        const nav::ChoiceTable& table = nav::choiceForVenue(venue);
        glGenBuffers(1, &choice_);   // the index (4 B per grid cell) and the entries (144 B per cell with candidates)
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, choice_);
        glBufferData(GL_SHADER_STORAGE_BUFFER, GLsizeiptr(table.index.size() * 4), table.index.data(), ssboUsage);
        glGenBuffers(1, &choiceEntries_);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, choiceEntries_);
        glBufferData(GL_SHADER_STORAGE_BUFFER, GLsizeiptr(std::max<size_t>(1, table.entries.size()) * sizeof(GpuNavChoiceCell)), table.entries.data(), ssboUsage);
        glGenBuffers(1, &assign_);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, assign_);
        glBufferData(GL_SHADER_STORAGE_BUFFER, GLsizeiptr(numBoids) * 4, nullptr, ssboUsage);
        glGenBuffers(1, &choiceCounters_);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, choiceCounters_);
        glBufferData(GL_SHADER_STORAGE_BUFFER, GLsizeiptr(sizeof(GpuChoiceCounters)), nullptr, ssboUsage);
        const std::vector<uint8_t> zeros(sizeof(GpuChoiceWork), 0);   // the histograms start (and stay, between evaluations) empty
        glGenBuffers(1, &choiceWork_);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, choiceWork_);
        glBufferData(GL_SHADER_STORAGE_BUFFER, GLsizeiptr(sizeof(GpuChoiceWork)), zeros.data(), ssboUsage);
        glGenBuffers(1, &choicePending_);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, choicePending_);
        glBufferData(GL_SHADER_STORAGE_BUFFER, GLsizeiptr(numBoids) * 4, nullptr, ssboUsage);
    }
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    glGenQueries(5, queries_);
}

CrowdSim::~CrowdSim() {
    glDeleteQueries(5, queries_);
    if (!ring_.empty()) glDeleteQueries(GLsizei(ring_.size()), ring_.data());
    glDeleteBuffers(2, boids_);
    glDeleteBuffers(1, &grid_);
    glDeleteBuffers(1, &cells_);
    glDeleteBuffers(1, &sorted_);
    glDeleteBuffers(1, &slots_);
    glDeleteBuffers(1, &planes_);
    if (nav_) glDeleteBuffers(1, &nav_);
    for (GLuint b : { choice_, choiceEntries_, assign_, choiceCounters_, choiceWork_, choicePending_ })
        if (b) glDeleteBuffers(1, &b);
    for (GLuint p : { hashProg_, sortProg_, sortSharedProg_, cellsProg_, physProg_, projProg_, finalProg_ }) glDeleteProgram(p);
    if (choiceProg_) glDeleteProgram(choiceProg_);
}

GLuint CrowdSim::navBuffer() const {
    if (!nav_ && nav::hasField(*venue_)) {   // GpuNavCell per cell: 16 B, 25 MB for venue S
        const std::vector<GpuNavCell> cells = nav::gpuCells(nav::forVenue(*venue_));
        glGenBuffers(1, &nav_);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, nav_);
        glBufferData(GL_SHADER_STORAGE_BUFFER, GLsizeiptr(cells.size() * sizeof(GpuNavCell)), cells.data(), SSBO_USAGE);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }
    return nav_;
}

GpuChoiceCounters CrowdSim::readChoiceCounters() const {
    GpuChoiceCounters c{};
    if (!choiceCounters_) return c;
    glMemoryBarrier(GL_BUFFER_UPDATE_BARRIER_BIT);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, choiceCounters_);
    glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, GLsizeiptr(sizeof c), &c);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    return c;
}

// The choice pass (physics.comp PHYSICS_PASS 0) on the current state: stage 3 (the queue ahead's prefix sums, one invocation
// per exit), stage 1 (evaluate, one invocation per agent), stage 2 (the
// per-exit thresholds, one group), then the counts of this step's parity cleared and stage 0 (apply, one invocation per agent). Stages 1
// and 2 return at once on the steps between evaluations (physics.comp decides: its CHOICE_STEPS is an expression of DT). The choice
// step advances.
void CrowdSim::dispatchChoice() {
    if (!choiceProg_) return;
    const GLuint groups128 = GLuint(numBoids_ / 128);
    glUseProgram(choiceProg_);
    glUniform1i(locChoiceNum_, numBoids_);
    glUniform1ui(locChoiceStep_, choiceStep_);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_BOIDS_IN, boids_[readIdx_]);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_NAV_CHOICE, choice_);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_NAV_CHOICE_ENTRY, choiceEntries_);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_CHOICE_ASSIGN, assign_);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_CHOICE_COUNTERS, choiceCounters_);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_CHOICE_WORK, choiceWork_);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_CHOICE_PENDING, choicePending_);
    glUniform1i(locChoiceStage_, 3);   // the queue ahead's prefix sums (one invocation per exit)
    glDispatchCompute(1, 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    if (hook_) hook_({ "choice", choiceProg_, 1, 3, 0 });
    glUniform1i(locChoiceStage_, 1);
    glDispatchCompute(groups128, 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    if (hook_) hook_({ "choice", choiceProg_, groups128, 1, 0 });
    glUniform1i(locChoiceStage_, 2);
    glDispatchCompute(1, 1, 1);   // one invocation per exit (at most 63 < 128)
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    if (hook_) hook_({ "choice", choiceProg_, 1, 2, 0 });
    const GLuint zero = 0;
    const GLintptr qWrite = (choiceStep_ & 1u) ? 0 : nav::CHOICE_QUEUE_STRIDE;   // the shader's qWrite = 64 - qRead
    glMemoryBarrier(GL_BUFFER_UPDATE_BARRIER_BIT);   // the earlier stages' atomics before the clear
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, choiceCounters_);
    glClearBufferSubData(GL_SHADER_STORAGE_BUFFER, GL_R32UI, qWrite * 4, nav::CHOICE_QUEUE_STRIDE * 4, GL_RED_INTEGER, GL_UNSIGNED_INT, &zero);
    glUniform1i(locChoiceStage_, 0);
    glDispatchCompute(groups128, 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    if (hook_) hook_({ "choice", choiceProg_, groups128, 0, 0 });
    ++choiceStep_;
}

void CrowdSim::stepExitChoice() { dispatchChoice(); }

void CrowdSim::upload(const std::vector<GpuBoid>& boids) {
    if (boids.size() != size_t(numBoids_))
        throw std::invalid_argument("CrowdSim::upload: expected " + std::to_string(numBoids_) + " agents, got " + std::to_string(boids.size()));
    // Both halves start identical so neither ever holds uninitialised agents
    for (GLuint b : boids_) {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, b);
        glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, GLsizeiptr(boids.size() * sizeof(GpuBoid)), boids.data());
    }
    if (assign_) {   // a fresh exit choice
        const GLuint none = nav::CHOICE_NONE, zero = 0;
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, assign_);
        glClearBufferData(GL_SHADER_STORAGE_BUFFER, GL_R32UI, GL_RED_INTEGER, GL_UNSIGNED_INT, &none);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, choiceCounters_);
        glClearBufferData(GL_SHADER_STORAGE_BUFFER, GL_R32UI, GL_RED_INTEGER, GL_UNSIGNED_INT, &zero);
        // The work buffer (the queue-ahead histograms of both parities, the gain histograms, the thresholds) and the
        // pending switches too, as a fresh CrowdSim holds them (nav::ChoiceState::reset on the CPU): otherwise an upload onto a CrowdSim that has
        // stepped reads the previous run's queue ahead in its first choice
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, choiceWork_);
        glClearBufferData(GL_SHADER_STORAGE_BUFFER, GL_R32UI, GL_RED_INTEGER, GL_UNSIGNED_INT, &zero);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, choicePending_);
        glClearBufferData(GL_SHADER_STORAGE_BUFFER, GL_R32UI, GL_RED_INTEGER, GL_UNSIGNED_INT, &zero);
        choiceStep_ = 0;
    }
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void CrowdSim::stamp(int slot) const {
    if (ringPos_ < ringSteps_) glQueryCounter(ring_[size_t(ringPos_) * 5 + size_t(slot)], GL_TIMESTAMP);
    else if (timing_) glQueryCounter(queries_[slot], GL_TIMESTAMP);
}

void CrowdSim::step(GLuint sdfTexture) {
    const GLuint groups256 = GLuint(numBoids_ / 256);
    stamp(0);

    // 1. Hash the current state into (gridID, boidID); evacuated agents get INACTIVE_CELL
    glUseProgram(hashProg_);
    glUniform1i(locHashNum_, numBoids_);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_BOIDS_IN, boids_[readIdx_]);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_GRID, grid_);
    glDispatchCompute(groups256, 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    if (hook_) hook_({ "hash", hashProg_, groups256, 0, 0 });
    stamp(1);

    // 2. Bitonic sort by gridID (unsigned, so INACTIVE_CELL runs to the tail)
    sortGrid();
    stamp(2);

    // 3. Cell ranges over the sorted pairs, and the gather of the active agents' state into slot
    // order for physics. The barrier orders the previous step's atomic writes to the
    //    cell buffer before the clear.
    glMemoryBarrier(GL_BUFFER_UPDATE_BARRIER_BIT);
    const GLuint zero = 0;
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, cells_);
    glClearBufferData(GL_SHADER_STORAGE_BUFFER, GL_R32UI, GL_RED_INTEGER, GL_UNSIGNED_INT, &zero);
    glUseProgram(cellsProg_);
    glUniform1i(locCellsNum_, numBoids_);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_BOIDS_IN, boids_[readIdx_]);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_GRID, grid_);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_CELLS, cells_);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_BOIDS_SORTED, sorted_);
    glDispatchCompute(groups256, 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    if (hook_) hook_({ "cells", cellsProg_, groups256, 0, 0 });
    stamp(3);

    // 4. Physics (three programs from physics.comp). Predict: steering + integration + static
    //    contacts from the gathered state (sorted_) into slots_, each agent's wall plane into planes_.
    //    Projection: PROJ_ITERATIONS - 1 Jacobi iterations, the two slot buffers ping-pong (the gathered
    //    start-of-step copy is no longer needed after the predict pass). Final: the last iteration + the
    //    final static contacts, boids[read] -> boids[write] at the agent's index. Then swap so the new
    //    state is current. planes_ stays bound at BIND_SLOT_PLANES for all three.
    // Queue-aware: first the choice pass (each agent's exit for this step; agent order, from boids[read]).
    dispatchChoice();
    const GLuint groups128 = GLuint(numBoids_ / 128);
    GLuint slotIn = sorted_, slotOut = slots_;
    glUseProgram(physProg_);
    glUniform1i(locPhysNum_, numBoids_);
    glUniform3fv(locPhysSdfMin_, 1, &SDF_MIN[0]);
    glUniform1f(locPhysSdfInvSpacing_, 1.0f / SDF_SPACING);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_3D, sdfTexture);
    glUniform1i(locPhysSdfTex_, 0);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_GRID, grid_);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_CELLS, cells_);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_SLOT_IN, slotIn);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_SLOT_OUT, slotOut);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_SLOT_PLANES, planes_);
    if (drive_) glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_DRIVE, drive_);   // forced motion (tools only)
    if (nav_) glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_NAV, nav_);         // the navigation field
    if (choice_) {                                                                  // the exit choice
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_NAV_CHOICE, choice_);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_NAV_CHOICE_ENTRY, choiceEntries_);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_CHOICE_ASSIGN, assign_);
    }
    glDispatchCompute(groups128, 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    if (hook_) hook_({ "physics", physProg_, groups128, 0, 0 });
    std::swap(slotIn, slotOut);
    if (projIterations_ > 1) {
        glUseProgram(projProg_);
        glUniform1i(locProjNum_, numBoids_);
        for (int it = 1; it < projIterations_; ++it) {
            glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_SLOT_IN, slotIn);
            glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_SLOT_OUT, slotOut);
            glDispatchCompute(groups128, 1, 1);
            glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
            if (hook_) hook_({ "project", projProg_, groups128, 0, it });
            std::swap(slotIn, slotOut);
        }
    }
    glUseProgram(finalProg_);
    glUniform1i(locFinalNum_, numBoids_);
    glUniform1i(locFinalProject_, projIterations_ > 0 ? 1 : 0);
    glUniform3fv(locFinalSdfMin_, 1, &SDF_MIN[0]);
    glUniform1f(locFinalSdfInvSpacing_, 1.0f / SDF_SPACING);
    glUniform1i(locFinalSdfTex_, 0);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_BOIDS_IN, boids_[readIdx_]);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_BOIDS_OUT, boids_[writeIdx_]);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_SLOT_IN, slotIn);
    glDispatchCompute(groups128, 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);  // next hash and the boid vertex shader read it
    if (hook_) hook_({ "project_final", finalProg_, groups128, 0, projIterations_ });
    std::swap(readIdx_, writeIdx_);
    stamp(4);
    if (ringPos_ < ringSteps_) ++ringPos_;
}

// The network of bitonic_sort.comp (stages k = 2 .. N, passes j = k/2 .. 1).
// Its passes with j < SORT_TILE run in shared memory: one dispatch sorts every tile
// (all stages k <= SORT_TILE), then each stage k > SORT_TILE runs its passes j >= SORT_TILE as global
// dispatches and its passes j < SORT_TILE as one shared-memory dispatch. The same compare-exchanges in
// the same order per element pair, on data-independent pairs: byte-identical output
// (gpu_diag sortcheck). Dispatches: 10 instead of 78 at N = 4096, 55 instead of 171 at
// N = 262144.
void CrowdSim::sortGrid() {
    const GLuint groups256 = GLuint(numBoids_ / 256);
    const GLuint tiles = GLuint(std::max(1, numBoids_ / SORT_TILE));   // N = 256: one half-filled tile
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_GRID, grid_);
    glUseProgram(sortSharedProg_);
    glUniform1i(locSharedNum_, numBoids_);
    glUniform1i(locSharedMode_, 0);
    glDispatchCompute(tiles, 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    if (hook_) hook_({ "sort", sortSharedProg_, tiles, std::min(numBoids_, SORT_TILE), 0, 2 });
    for (int k = 2 * SORT_TILE; k <= numBoids_; k <<= 1) {
        glUseProgram(sortProg_);
        for (int j = k >> 1; j >= SORT_TILE; j >>= 1) {
            glUniform1i(locSortJ_, j);
            glUniform1i(locSortK_, k);
            glDispatchCompute(groups256, 1, 1);
            glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
            if (hook_) hook_({ "sort", sortProg_, groups256, k, j });
        }
        glUseProgram(sortSharedProg_);
        glUniform1i(locSharedMode_, 1);
        glUniform1i(locSharedK_, k);
        glDispatchCompute(tiles, 1, 1);
        glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
        if (hook_) hook_({ "sort", sortSharedProg_, tiles, k, SORT_TILE / 2, 2 });
    }
}

CrowdSim::PassTimesMs CrowdSim::readTimings() const {
    if (!timing_) return {};
    GLuint64 t[5] = {};
    for (int i = 0; i < 5; ++i) glGetQueryObjectui64v(queries_[i], GL_QUERY_RESULT, &t[i]);
    auto ms = [&](int a, int b) { return double(t[b] - t[a]) * 1e-6; };
    return { ms(0, 1), ms(1, 2), ms(2, 3), ms(3, 4), ms(0, 4) };
}

void CrowdSim::beginTimingRing(int steps) {
    if (steps <= 0) throw std::invalid_argument("CrowdSim::beginTimingRing: steps must be positive");
    if (ring_.size() < size_t(steps) * 5) {
        if (!ring_.empty()) glDeleteQueries(GLsizei(ring_.size()), ring_.data());
        ring_.assign(size_t(steps) * 5, 0);
        glGenQueries(GLsizei(ring_.size()), ring_.data());
    }
    ringSteps_ = steps;
    ringPos_ = 0;
}

std::vector<CrowdSim::PassTimesMs> CrowdSim::readTimingRing() {
    std::vector<PassTimesMs> out;
    for (int s = 0; s < ringPos_; ++s) {
        GLuint64 t[5] = {};
        for (int i = 0; i < 5; ++i) glGetQueryObjectui64v(ring_[size_t(s) * 5 + size_t(i)], GL_QUERY_RESULT, &t[i]);
        auto ms = [&](int a, int b) { return double(t[b] - t[a]) * 1e-6; };
        out.push_back({ ms(0, 1), ms(1, 2), ms(2, 3), ms(3, 4), ms(0, 4) });
    }
    ringSteps_ = ringPos_ = 0;
    return out;
}

void CrowdSim::setProjectionIterations(int iterations) {
    if (iterations < 0) throw std::invalid_argument("CrowdSim::setProjectionIterations: iterations must be >= 0");
    projIterations_ = iterations;
}

namespace {

// Stand treads measured from stadium.obj. Each quadrant's stand is an L of square rings
// around the pitch: tread k covers Chebyshev depth max(|x|, |y|) in [depthMin, depthMax]
// at height z. Laterally the benches start past the aisle beside each avenue wall.
struct Tread { float z, depthMin, depthMax; };
constexpr Tread TREADS[] = {
    { 0.0176f, 0.427f, 0.470f }, { 0.0352f, 0.473f, 0.517f }, { 0.0528f, 0.520f, 0.565f },
    { 0.0704f, 0.568f, 0.610f }, { 0.0880f, 0.615f, 0.657f }, { 0.1056f, 0.662f, 0.705f },
    { 0.1231f, 0.708f, 0.753f },
};
constexpr int TREAD_COUNT = int(std::size(TREADS));
constexpr float BENCH_START = 0.152f;   // outer edge of the aisle
constexpr float EDGE_MARGIN = 0.006f;   // keep clear of risers, lips and the aisle edge
constexpr float SPAWN_HOVER = BODY_RADIUS;  // the centre at the rest height above the tread (the hard body)

// Bodies are hard, so a spawn that fits is made overlap-free. The random placement is relaxed by Gauss-Seidel
// sweeps over every overlapping pair (vertical disks, as in the physics
// projection: |dz| < BODY_DIAM and XY distance < BODY_DIAM), in agent order: the pair moves apart along its XY
// offset to the XY distance BODY_DIAM, half each (a stacked pair along a hash direction), and each agent is kept
// on its own tread's spawn band. It stops after a sweep in which no pair overlapped by more than
// SPAWN_RELAX_TOL, or after SPAWN_RELAX_SWEEPS. Loads beyond the bands' capacity at random close
// packing (SPAWN_RCP_FRACTION of the area covered by bodies) are left as placed: such crowds start
// stacked (N = 8192 and up).
constexpr int SPAWN_RELAX_SWEEPS = 2000;
constexpr float SPAWN_RELAX_TOL = 1e-6f;
constexpr double SPAWN_RCP_FRACTION = 0.82;
constexpr float SPAWN_GRID_CELL = 2.0f * BODY_DIAM;

// The spawn band of a tread: Chebyshev depth in [lo, hi], lateral (the smaller of |x|, |y|) >= lat0
struct Band { float lo, hi, lat0; };
Band bandOf(const Tread& t) { return { t.depthMin + EDGE_MARGIN, t.depthMax - EDGE_MARGIN, BENCH_START + EDGE_MARGIN }; }

// Total area of the spawn bands (4 quadrants, each an L: per depth d two runs of length d - lat0)
double spawnBandArea() {
    double a = 0.0;
    for (const Tread& t : TREADS) {
        const Band b = bandOf(t);
        a += 4.0 * double(b.hi - b.lo) * (double(b.lo) + double(b.hi) - 2.0 * double(b.lat0));
    }
    return a;
}

glm::vec2 clampToBand(glm::vec2 p, const Band& b) {
    const glm::vec2 s(p.x < 0.0f ? -1.0f : 1.0f, p.y < 0.0f ? -1.0f : 1.0f);
    glm::vec2 a = glm::min(glm::abs(p), glm::vec2(b.hi));
    if (std::max(a.x, a.y) < b.lo) (a.x >= a.y ? a.x : a.y) = b.lo;
    if (std::min(a.x, a.y) < b.lat0) (a.x <= a.y ? a.x : a.y) = b.lat0;
    return s * a;
}

uint32_t spawnHash(uint32_t x) {   // lowbias32
    x ^= x >> 16; x *= 0x7feb352du;
    x ^= x >> 15; x *= 0x846ca68bu;
    x ^= x >> 16;
    return x;
}

// Returns the number of sweeps run; maxOverlap: the largest overlap of the last sweep
int relaxSpawn(std::vector<GpuBoid>& boids, const std::vector<int>& tread, float& maxOverlap) {
    const int n = int(boids.size());
    const int res = int(std::ceil(DOMAIN_SPAN / SPAWN_GRID_CELL));
    auto cellOf = [&](glm::vec2 p) {
        const int x = std::clamp(int((p.x - DOMAIN_MIN) / SPAWN_GRID_CELL), 0, res - 1);
        const int y = std::clamp(int((p.y - DOMAIN_MIN) / SPAWN_GRID_CELL), 0, res - 1);
        return x + y * res;
    };
    std::vector<int> start(size_t(res) * res + 1), order(static_cast<size_t>(n)), cellIdx(static_cast<size_t>(n));
    int sweep = 0;
    for (; sweep < SPAWN_RELAX_SWEEPS; ++sweep) {
        // Counting sort of the agents by grid cell (agent order within a cell)
        std::fill(start.begin(), start.end(), 0);
        for (int i = 0; i < n; ++i) { cellIdx[size_t(i)] = cellOf(glm::vec2(boids[size_t(i)].position)); ++start[size_t(cellIdx[size_t(i)]) + 1]; }
        for (size_t c = 1; c < start.size(); ++c) start[c] += start[c - 1];
        std::vector<int> fill(start.begin(), start.end() - 1);
        for (int i = 0; i < n; ++i) order[size_t(fill[size_t(cellIdx[size_t(i)])]++)] = i;

        maxOverlap = 0.0f;
        for (int i = 0; i < n; ++i) {
            const int ci = cellIdx[size_t(i)], cx = ci % res, cy = ci / res;
            for (int y = std::max(cy - 1, 0); y <= std::min(cy + 1, res - 1); ++y)
                for (int x = std::max(cx - 1, 0); x <= std::min(cx + 1, res - 1); ++x)
                    for (int s = start[size_t(x + y * res)]; s < start[size_t(x + y * res) + 1]; ++s) {
                        const int j = order[size_t(s)];
                        if (j <= i) continue;   // each pair once per sweep
                        glm::vec4& pi = boids[size_t(i)].position;
                        glm::vec4& pj = boids[size_t(j)].position;
                        const glm::vec3 off = glm::vec3(pi) - glm::vec3(pj);
                        const float dxy = glm::length(glm::vec2(off));   // vertical disks, as the projection's contacts
                        if (std::abs(off.z) >= BODY_DIAM || dxy >= BODY_DIAM) continue;
                        maxOverlap = std::max(maxOverlap, BODY_DIAM - dxy);
                        const float shift = 0.5f * (BODY_DIAM - dxy);
                        glm::vec2 dir;
                        if (dxy > 1e-6f) dir = glm::vec2(off) / dxy;
                        else {
                            const float angle = float(spawnHash(spawnHash(uint32_t(i)) ^ uint32_t(j))) * HASH_TO_RADIANS;
                            dir = glm::vec2(std::cos(angle), std::sin(angle));
                        }
                        // Each member moves to its corrected position unless that leaves its band's valid floor
                        // (the placement's own test: free at the centre, solid tread 2 cm below; the riser fillets
                        // fail it near a band's edge); then it stays and the next sweeps move its partner
                        for (int m = 0; m < 2; ++m) {
                            glm::vec4& pm = m == 0 ? pi : pj;
                            const glm::vec2 c = clampToBand(glm::vec2(pm) + (m == 0 ? shift : -shift) * dir, bandOf(TREADS[tread[size_t(m == 0 ? i : j)]]));
                            const glm::vec3 q(c, pm.z);
                            if (sampleSDF_CPU(q) > 0.0f && sampleSDF_CPU(q - glm::vec3(0.0f, 0.0f, 0.02f)) < 0.0f) { pm.x = c.x; pm.y = c.y; }
                        }
                    }
        }
        if (maxOverlap <= SPAWN_RELAX_TOL) return sweep + 1;
    }
    return sweep;
}

} // namespace

std::vector<GpuBoid> spawnBleacherCrowd(int numBoids, unsigned seed) {
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> quadDist(0, 3);
    std::uniform_int_distribution<int> wingDist(0, 1);
    std::uniform_real_distribution<float> unit(0.0f, 1.0f);

    // Weight treads by bench area so density stays uniform as the rings widen outward
    std::vector<float> weights;
    for (const Tread& t : TREADS)
        weights.push_back((0.5f * (t.depthMin + t.depthMax) - BENCH_START) * (t.depthMax - t.depthMin));
    std::discrete_distribution<int> treadDist(weights.begin(), weights.end());

    std::vector<GpuBoid> boids(numBoids);
    std::vector<int> tread(size_t(numBoids), 0);
    for (int i = 0; i < numBoids; ++i) {
        GpuBoid& b = boids[size_t(i)];
        glm::vec3 pos(0.0f);
        bool placed = false;
        for (int attempt = 0; attempt < 200 && !placed; ++attempt) {
            const int k = treadDist(gen);
            const Tread& t = TREADS[k];
            float depth = glm::mix(t.depthMin + EDGE_MARGIN, t.depthMax - EDGE_MARGIN, unit(gen));
            float lateral = glm::mix(BENCH_START + EDGE_MARGIN, depth, unit(gen));
            // Wing 0: benches run along x at depth |y|; wing 1: along y at depth |x|
            pos = wingDist(gen) == 0 ? glm::vec3(lateral, depth, t.z + SPAWN_HOVER)
                                     : glm::vec3(depth, lateral, t.z + SPAWN_HOVER);
            int quad = quadDist(gen);
            if (quad == 1 || quad == 2) pos.x = -pos.x;
            if (quad == 2 || quad == 3) pos.y = -pos.y;
            // Free space here, solid tread just below
            placed = sampleSDF_CPU(pos) > 0.0f && sampleSDF_CPU(pos - glm::vec3(0.0f, 0.0f, 0.02f)) < 0.0f;
            tread[size_t(i)] = k;
        }
        if (!placed)
            throw std::runtime_error("spawnBleacherCrowd: no valid tread position found "
                                     "(SDF not loaded, or tread table out of sync with stadium.sdf)");
        b.position = glm::vec4(pos, 1.0f);  // w = 1: active
        b.velocity = glm::vec4(0.0f);       // w = speed
    }
    if (double(numBoids) <= spawnCapacity()) {
        float maxOverlap = 0.0f;
        relaxSpawn(boids, tread, maxOverlap);
    }
    return boids;
}

double spawnCapacity() {
    const double bodyArea = 3.14159265358979 * double(BODY_RADIUS) * double(BODY_RADIUS);
    return spawnBandArea() * SPAWN_RCP_FRACTION / bodyArea;
}

std::vector<int> seatedSpawnSeats(const Venue& venue, int numBoids, double load, unsigned seed) {
    if (!venue.seated()) throw std::invalid_argument("seatedSpawnSeats: venue " + std::string(venue.name) + " has no seats");
    const int seatCount = int(seated::seats(venue.layout).size());
    const int m = int(std::lround(std::clamp(load, 0.0, 1.0) * seatCount));
    if (m > numBoids)
        throw std::invalid_argument("spawnSeatedCrowd: " + std::to_string(m) + " seats chosen for " + std::to_string(numBoids) + " agents");
    // Partial Fisher-Yates over the seat indices (mt19937's raw output, specified by the standard: the same subset on every
    // platform), then the chosen seats in seat order
    std::vector<int> idx(static_cast<size_t>(seatCount));
    for (int i = 0; i < seatCount; ++i) idx[size_t(i)] = i;
    std::mt19937 gen(seed);
    for (int i = 0; i < m && m < seatCount; ++i) {
        const int j = i + int(uint32_t(gen()) % uint32_t(seatCount - i));
        std::swap(idx[size_t(i)], idx[size_t(j)]);
    }
    std::vector<int> chosen(idx.begin(), idx.begin() + m);
    std::sort(chosen.begin(), chosen.end());
    chosen.resize(size_t(numBoids), -1);
    return chosen;
}

std::vector<GpuBoid> spawnSeatedCrowd(const Venue& venue, int numBoids, double load, unsigned seed, int* activeOut) {
    const std::vector<int> chosen = seatedSpawnSeats(venue, numBoids, load, seed);
    const std::vector<seated::Seat> all = seated::seats(venue.layout);
    std::vector<GpuBoid> boids(static_cast<size_t>(numBoids));
    int active = 0;
    for (int i = 0; i < numBoids; ++i) {
        GpuBoid& b = boids[size_t(i)];
        if (chosen[size_t(i)] >= 0) {
            b.position = glm::vec4(all[size_t(chosen[size_t(i)])].pos, 1.0f);   // w = 1: active
            ++active;
        } else {
            b.position = glm::vec4(PARK_COORD, PARK_COORD, PARK_COORD, 0.0f);   // parked: never simulated
        }
        b.velocity = glm::vec4(0.0f);
    }
    if (activeOut) *activeOut = active;
    return boids;
}

// --- Overcrowding ---
namespace {

enum StandZone { SZ_NONE = 0, SZ_WALKWAY, SZ_CONCOURSE, SZ_GANGWAY };

// The standing floor's zone of a plan point, by seated::areas' own partition: the walkway is band 0 from the fence's outer face, the
// concourse the CONC cells of band 2 + 2 rows (the door passages through the outer wall are the next band), a gangway seated::gangwayAt
// (an incline, or a barrier gap at a gangway's foot)
int standZone(const SeatedLayout& L, glm::vec2 xy, bool gangways) {
    const glm::vec2 f = seated::fold(xy);
    int row = -1, band = -1;
    const int kind = seated::cellAt(L, xy, &row, &band);
    if (band == 0) return f.y >= FENCE_HALF_OUTER ? SZ_WALKWAY : SZ_NONE;
    if (band == seated::bandCount(L) - 4) return kind == seated::CONC ? SZ_CONCOURSE : SZ_NONE;
    if (gangways && seated::gangwayAt(L, xy) >= 0) return SZ_GANGWAY;
    return SZ_NONE;
}

// A standing body fits at xy (centre at floorZ + BODY_RADIUS): the navigation grid's FIT rule (outside the fence's collision band, no
// wall within BODY_RADIUS of the plane at the body's top) with STANDING_CLEARANCE_MARGIN on both, the walls' clearance the contact
// rules keep (wallClear), and no step face rising within the body's radius (the floor on a circle of 16 points at most the incline's
// own rise above floorZ: a body stands on its own floor, not against a row's step)
bool standingFits(const SeatedLayout& L, glm::vec2 xy, float floorZ) {
    if (sdFence(glm::vec3(xy, 0.0f)) < STANDING_CLEARANCE_MARGIN) return false;
    const glm::vec3 w = seated::wall(L, glm::vec3(xy, floorZ + BODY_RADIUS + L.wallAbove), 2.0f * BODY_RADIUS);
    if (w.z < L.wallClear + STANDING_CLEARANCE_MARGIN) return false;
    const float r = BODY_RADIUS + STANDING_CLEARANCE_MARGIN;
    for (int k = 0; k < 16; ++k) {
        const double a = 6.283185307179586 * k / 16.0;
        const glm::vec2 q = xy + r * glm::vec2(float(std::cos(a)), float(std::sin(a)));
        if (seated::floorHeight(L, q) > floorZ + L.rake * r + 1e-6f) return false;
    }
    return true;
}

} // namespace

const char* standingAreasName(StandingAreas a) { return a == StandingAreas::WithGangways ? "gangways" : "circulation"; }

OvercrowdSpawn spawnOvercrowdedCrowd(const Venue& venue, double requestedLoad, unsigned seed, StandingAreas areas, int numBoids) {
    if (!venue.seated()) throw std::invalid_argument("spawnOvercrowdedCrowd: venue " + std::string(venue.name) + " has no seats");
    const SeatedLayout& L = venue.layout;
    OvercrowdSpawn o;
    o.requestedLoad = requestedLoad;
    const int seatCount = int(seated::seats(L).size());
    const bool withGangways = areas == StandingAreas::WithGangways;
    const seated::Areas A = seated::areas(L);
    o.standingAreaM2 = A.walkway + A.concourse + (withGangways ? A.gangways : 0.0);
    o.standingMax = int(std::floor(OVERCROWD_STANDING_MAX_P_M2 * o.standingAreaM2));
    o.standingRequested = requestedLoad > 1.0 ? int(std::lround((requestedLoad - 1.0) * double(seatCount))) : 0;
    const int target = std::min(o.standingRequested, o.standingMax);
    const double seatLoad = std::min(requestedLoad, 1.0);
    const int seatedWanted = int(std::lround(std::clamp(seatLoad, 0.0, 1.0) * seatCount));
    if (numBoids == 0) {
        numBoids = 256;
        while (numBoids < seatedWanted + target) numBoids *= 2;
    }
    if (numBoids < seatedWanted + target)
        throw std::invalid_argument("spawnOvercrowdedCrowd: " + std::to_string(seatedWanted + target) + " agents for a buffer of " + std::to_string(numBoids));
    // The seats: spawnSeatedCrowd unchanged (at 100% every seat, the seed unused: the same agents 0 .. seats - 1 for every seed)
    o.boids = spawnSeatedCrowd(venue, numBoids, seatLoad, seed, &o.seats);
    o.seat = seatedSpawnSeats(venue, numBoids, seatLoad, seed);
    o.load = double(o.seats) / double(seatCount);
    if (target <= 0) return o;

    // The standing crowd: uniform draws over the square within the outer wall's inner face, kept on the standing floor where a body
    // fits and touches nobody. A hash grid of (BODY_DIAM + margin) cells holds every agent placed so far (the seated ones included)
    std::mt19937 gen(seed);
    auto u01 = [&gen]() { return double(gen() >> 8) * (1.0 / 16777216.0); };   // 24 bits of mt19937's raw output: portable
    const double R = double(L.concBack);
    const float minDist = BODY_DIAM + STANDING_CLEARANCE_MARGIN;
    const int res = int(std::ceil(2.0 * R / double(minDist))) + 1;
    std::vector<std::vector<int>> grid(size_t(res) * size_t(res));
    auto cellOf = [&](glm::vec2 p) {
        const int ix = std::clamp(int(std::floor((double(p.x) + R) / double(minDist))), 0, res - 1);
        const int iy = std::clamp(int(std::floor((double(p.y) + R) / double(minDist))), 0, res - 1);
        return glm::ivec2(ix, iy);
    };
    for (int i = 0; i < numBoids; ++i)
        if (o.boids[size_t(i)].position.w != 0.0f) {
            const glm::ivec2 c = cellOf(glm::vec2(o.boids[size_t(i)].position));
            grid[size_t(c.y) * size_t(res) + size_t(c.x)].push_back(i);
        }
    const long maxDraws = 100000L + 4000L * long(target);
    int next = o.seats;
    while (o.standing < target && o.draws < maxDraws) {
        ++o.draws;
        const double ux = u01(), uy = u01();
        const glm::vec2 xy(float(-R + 2.0 * R * ux), float(-R + 2.0 * R * uy));
        const int zone = standZone(L, xy, withGangways);
        if (zone == SZ_NONE) continue;
        const float floorZ = seated::floorHeight(L, xy);
        if (!standingFits(L, xy, floorZ)) continue;
        const glm::vec3 c(xy, floorZ + BODY_RADIUS);
        const glm::ivec2 cc = cellOf(xy);
        bool free = true;
        for (int dy = -1; dy <= 1 && free; ++dy)
            for (int dx = -1; dx <= 1 && free; ++dx) {
                const int gx = cc.x + dx, gy = cc.y + dy;
                if (gx < 0 || gy < 0 || gx >= res || gy >= res) continue;
                for (int j : grid[size_t(gy) * size_t(res) + size_t(gx)])
                    if (glm::length(c - glm::vec3(o.boids[size_t(j)].position)) < minDist) { free = false; break; }
            }
        if (!free) continue;
        GpuBoid& b = o.boids[size_t(next)];
        b.position = glm::vec4(c, 1.0f);   // w = 1: active, at rest
        b.velocity = glm::vec4(0.0f);
        o.seat[size_t(next)] = -1;
        grid[size_t(cc.y) * size_t(res) + size_t(cc.x)].push_back(next);
        ++next;
        ++o.standing;
        (zone == SZ_WALKWAY ? o.standingWalkway : zone == SZ_CONCOURSE ? o.standingConcourse : o.standingGangways)++;
    }
    o.placementExhausted = o.standing < target;
    o.load = double(o.seats + o.standing) / double(seatCount);
    return o;
}

} // namespace swarm
