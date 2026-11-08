#pragma once

#include <glad/glad.h>

#include <cstdint>
#include <filesystem>
#include <functional>
#include <vector>

#include <swarm/exit_choice.hpp>
#include <swarm/gpu_caps.hpp>
#include <swarm/gpu_types.hpp>
#include <swarm/shader.hpp>
#include <swarm/sim_params.hpp>
#include <swarm/venue.hpp>

// CrowdSim::setProjectionIterations exists
#define SWARM_CROWDSIM_HAS_PROJECTION 1

namespace swarm {

// SSBO binding points shared by the compute and render shaders
constexpr GLuint BIND_BOIDS_IN = 0;   // agent state read by the pass
constexpr GLuint BIND_GRID = 1;       // (gridID, boidID) pairs, sorted by gridID
constexpr GLuint BIND_CELLS = 2;      // per-cell start/count into the sorted pairs
constexpr GLuint BIND_BOIDS_OUT = 3;  // agent state written by physics
constexpr GLuint BIND_BOIDS_SORTED = 4;  // agent state gathered in slot order (cells pass -> physics)
// The physics passes' slot-order state: read at BIND_SLOT_IN (the gathered start-of-step copy for
// the predict pass, the previous iteration for the projection), written at BIND_SLOT_OUT
constexpr GLuint BIND_SLOT_IN = BIND_BOIDS_SORTED;
constexpr GLuint BIND_SLOT_OUT = 5;
constexpr GLuint BIND_SLOT_PLANES = 6;   // per slot: the predict pass's wall plane and grounded flag
constexpr GLuint BIND_DRIVE = 11;        // forced motion (TEST_DRIVE_TABLE shader variants only): e_goal per agent
constexpr GLuint BIND_NAV = 12;          // an analytic venue's navigation field (VENUE_NAV_FIELD): GpuNavCell per grid cell
// The queue-aware exit choice (VENUE_EXIT_CHOICE; swarm/exit_choice.hpp)
constexpr GLuint BIND_NAV_CHOICE = 13;       // the candidate table's index: uint per navigation grid cell (read-only)
constexpr GLuint BIND_NAV_CHOICE_ENTRY = 19; // the candidate table's entries, GpuNavChoiceCell (read-only)
constexpr GLuint BIND_CHOICE_ASSIGN = 14;    // per agent (by id): the assigned exit (uint; nav::CHOICE_NONE before the first choice)
constexpr GLuint BIND_CHOICE_COUNTERS = 15;  // GpuChoiceCounters: the per-exit counts of both parities, the totals
constexpr GLuint BIND_CHOICE_WORK = 16;      // GpuChoiceWork: the switch cap's gain histograms and thresholds (choice pass only)
constexpr GLuint BIND_CHOICE_PENDING = 17;   // per agent: the pending switch of an evaluation step (choice pass only)

// Four-pass GPU crowd step (hash -> bitonic sort -> cell ranges -> physics) with the agent
// state double-buffered: physics reads boids[readIdx] and writes boids[writeIdx], then the
// indices swap, so no invocation ever reads a value another invocation is writing.
// Agent i always lives at index i in both buffers. The cells pass also copies every
// active agent's state into a third buffer in sorted-slot order (sorted[slot] = boids[read][boidID]),
// and physics reads its own and its neighbours' state from there: consecutive memory in the
// neighbour loop, the same values bit for bit. Physics is three programs (physics.comp
// PHYSICS_PASS 1-3): predict (steering + integration) into a fourth buffer, also in slot order; the
// hard-body projection's Jacobi iterations ping-pong between that buffer and the gathered copy; the final
// pass (last iteration + static contacts) writes boids[write] at the agent's index.
class CrowdSim {
public:
    // ssboUsage: the glBufferData usage hint of the agent, grid and cell buffers. It decides where the
    // driver places them, never what the passes compute. GL_DYNAMIC_COPY (written and read by the GL,
    // every step) keeps them in VRAM at every size. GL_DYNAMIC_DRAW puts buffers
    // of >= 4 MB in host memory on AMD 26.8.1 (agents from N = 131072, the grid at 262144: 10-50x slower
    // passes; results/benchmarks/optimisation_chain); gpu_diag passes it to reproduce that.
    static constexpr GLenum SSBO_USAGE = GL_DYNAMIC_COPY;
    // The terrace reference venue (step() needs stadium.sdf's texture)
    CrowdSim(const std::filesystem::path& shaderDir, int numBoids, GLenum ssboUsage = SSBO_USAGE);
    // Any venue: its programs are compiled with the venue's preamble (shader.cpp shaderPreamble(venue): its
    // neighbour grid and exit test; a seated venue's analytic distance code), the cell table has its GRID_RES^2 cells.
    // A seated venue samples no texture: step(0). A seated venue's navigation field (nav::forVenue: built or loaded
    // on first use) is uploaded once into a read-only SSBO, bound at BIND_NAV for the predict pass.
    CrowdSim(const std::filesystem::path& shaderDir, int numBoids, const Venue& venue, GLenum ssboUsage = SSBO_USAGE);
    // An analytic venue's model options (the exit choice, the incline speed; swarm/exit_choice.hpp ModelOptions). The
    // constructors above use defaultModelOptions(venue); the terrace ignores them. Queue-aware: the candidate table
    // (nav::choiceForVenue: built or loaded on first use) in a read-only SSBO, the per-agent assigned exits and the counters, and a
    // fourth program, physics.comp PHYSICS_PASS 0 (the choice pass: prefix / evaluate / thresholds / apply), first in the physics
    // stage of every step (the GPU timestamps count it in the physics interval).
    CrowdSim(const std::filesystem::path& shaderDir, int numBoids, const Venue& venue, const ModelOptions& options, GLenum ssboUsage = SSBO_USAGE);
    // The compute programs the constructor builds, in its order (the viewer compiles them ahead: swarm/shader.hpp precompileProgram).
    // A queue-aware venue's preamble needs its choice table (nav::choiceForVenue: loaded or built here if not yet).
    static std::vector<ProgramSpec> programSpecs(const std::filesystem::path& shaderDir, const Venue& venue, const ModelOptions& options);
    // What the constructor needs from the GPU (swarm/gpu_caps.hpp), known without the navigation tables: each program's SSBO bindings,
    // in programSpecs' order, and every buffer but the exit choice table's entries (their count comes with the table, or before it from
    // nav::choiceEntryCountBeforeBuild). The constructor checks both first and throws std::runtime_error with the reason, before it loads
    // or builds a table or compiles a program; then the entries' exact size, before it compiles.
    static std::vector<ProgramBindings> programBindings(const Venue& venue, const ModelOptions& options);
    static std::vector<GpuBufferUse> bufferUses(const Venue& venue, const ModelOptions& options, int numBoids);
    ~CrowdSim();
    CrowdSim(const CrowdSim&) = delete;
    CrowdSim& operator=(const CrowdSim&) = delete;

    // Writes the current (read) buffer. Queue-aware: also resets the exit choice (every agent unassigned, the counters 0,
    // the choice step 0, the work buffer's queue-ahead and gain histograms and the pending switches 0, as created), so an
    // uploaded state starts as a fresh run: its first step assigns every agent the candidate with the least E.
    void upload(const std::vector<GpuBoid>& boids);
    void step(GLuint sdfTexture);

    // The sort stage of step() alone: sorts the grid buffer's (gridID, boidID, padding) entries by
    // gridID with the bitonic network, in place. step() calls it after the hash pass; tools call it
    // on keys of their own (gpu_diag sortcheck). Passes with partner distance j <
    // SORT_TILE run in shared memory (bitonic_sort_shared.comp: one dispatch for all stages k <=
    // SORT_TILE, then one per stage after its global passes j >= SORT_TILE in bitonic_sort.comp).
    static constexpr int SORT_TILE = 512;   // = 2 x local_size_x of bitonic_sort_shared.comp
    void sortGrid();

    int numBoids() const { return numBoids_; }
    const Venue& venue() const { return *venue_; }
    const ModelOptions& options() const { return options_; }   // the effective options (the terrace: {Nearest, false})

    // The queue-aware exit choice (0 / no-ops otherwise). assignBuffer: uint per agent, the exit each agent steers to in
    // the next step (read back by tests and tools); choiceCounterBuffer: GpuChoiceCounters (queue[(choiceStep() & 1) * 64 + e]: the
    // counts the next step's choice reads); choiceStep: steps since the upload. readChoiceCounters waits on the GPU (tests, tools).
    // stepExitChoice: the choice pass alone, as step() runs it (tests: decisions without motion).
    GLuint assignBuffer() const { return assign_; }
    GLuint choiceCounterBuffer() const { return choiceCounters_; }
    GLuint choiceWorkBuffer() const { return choiceWork_; }   // GpuChoiceWork (the queue ahead's histograms; tools)
    GLuint choiceTableBuffer() const { return choice_; }
    GLuint choiceEntryBuffer() const { return choiceEntries_; }
    uint32_t choiceStep() const { return choiceStep_; }
    GpuChoiceCounters readChoiceCounters() const;
    void stepExitChoice();

    // Forced motion (tools only): a buffer of one vec2 per agent (std430, by boidID) bound at BIND_DRIVE for the
    // predict pass. Read only by programs compiled with TEST_DRIVE_TABLE (tools/venue_s.hpp's shader variant); 0: none.
    void setDriveBuffer(GLuint buffer) { drive_ = buffer; }

    // Jacobi iterations of the hard-body projection per step (default PROJ_ITERATIONS, the model
    // constant). Experiments and diagnostics only (tools/fd, perf A/B): 0 switches the projection off.
    // SWARM_CROWDSIM_HAS_PROJECTION (top of this file) lets tools built against several engine versions test for it.
    void setProjectionIterations(int iterations);
    int projectionIterations() const { return projIterations_; }
    int readIndex() const { return readIdx_; }
    GLuint boidBuffer(int idx) const { return boids_[idx]; }
    // Both derived from the ping-pong indices after the last step (not from frame parity: the
    // number of steps per frame varies). The previous state is the last physics input, which
    // nothing overwrites until the next step. Before the first step both hold the uploaded state.
    GLuint currentStateBuffer() const { return boids_[readIdx_]; }    // latest integrated state
    GLuint previousStateBuffer() const { return boids_[writeIdx_]; }  // state one step earlier
    GLuint gridBuffer() const { return grid_; }
    GLuint cellBuffer() const { return cells_; }
    // The nearest-exit navigation field (GpuNavCell per cell; 0: the terrace, none). Queue-aware simulations do not read it: it is
    // uploaded on the first call (the viewer's distance overlay), not by the constructor.
    GLuint navBuffer() const;

    // GPU timestamps around each pass. Profiling/tests only: readTimings() waits on the GPU.
    struct PassTimesMs { double hash = 0, sort = 0, cells = 0, physics = 0, total = 0; };
    void setTimingEnabled(bool enabled) { timing_ = enabled; }
    PassTimesMs readTimings() const;

    // Benchmark timing without stalls (tools/benchmark): the next 'steps' steps stamp a query ring
    // of their own, and readTimingRing() reads the whole ring back once, after the measured loop
    // (it waits on the GPU). Takes precedence over setTimingEnabled while the ring is open.
    void beginTimingRing(int steps);
    std::vector<PassTimesMs> readTimingRing();

    // Diagnostics only (tools/benchmark/gpu_diag.cpp): when set, step() calls it after every
    // dispatch and the memory barrier that follows it, with the pass name, its program, the group
    // count (x; y = z = 1) and, for a sort pass, its k and j. The application never sets it.
    // Physics: "physics" (predict), "project" (j = iteration 1 .. PROJ_ITERATIONS - 1) and
    // "project_final" (j = the number of iterations).
    // elementsPerInvocation: 2 for the shared-memory sort dispatches (a 512-element tile per 256-wide
    // group), else 1. For those, k is the stage (mode 0: min(N, SORT_TILE), all its stages) and j the
    // first pass (mode 0: 0, all passes; mode 1: SORT_TILE / 2).
    struct DispatchInfo { const char* pass; GLuint program; GLuint groupsX; int k, j; int elementsPerInvocation = 1; };
    void setDispatchHook(std::function<void(const DispatchInfo&)> hook) { hook_ = std::move(hook); }

private:
    void stamp(int slot) const;
    void dispatchChoice();

    int numBoids_;
    const Venue* venue_;
    ModelOptions options_;
    GLuint drive_ = 0;
    GLuint hashProg_ = 0, sortProg_ = 0, sortSharedProg_ = 0, cellsProg_ = 0, physProg_ = 0, projProg_ = 0, finalProg_ = 0;
    GLuint boids_[2] = { 0, 0 };
    GLuint grid_ = 0, cells_ = 0, sorted_ = 0, slots_ = 0, planes_ = 0;
    mutable GLuint nav_ = 0;
    GLuint choiceProg_ = 0, choice_ = 0, choiceEntries_ = 0, assign_ = 0, choiceCounters_ = 0, choiceWork_ = 0, choicePending_ = 0;
    uint32_t choiceStep_ = 0;
    GLint locChoiceNum_ = -1, locChoiceStep_ = -1, locChoiceStage_ = -1;
    int projIterations_ = PROJ_ITERATIONS;
    int readIdx_ = 0, writeIdx_ = 1;

    GLint locHashNum_ = -1;
    GLint locSortJ_ = -1, locSortK_ = -1;
    GLint locSharedNum_ = -1, locSharedMode_ = -1, locSharedK_ = -1;
    GLint locCellsNum_ = -1;
    GLint locPhysNum_ = -1;
    GLint locPhysSdfMin_ = -1, locPhysSdfInvSpacing_ = -1, locPhysSdfTex_ = -1;
    GLint locProjNum_ = -1;
    GLint locFinalNum_ = -1, locFinalProject_ = -1, locFinalSdfMin_ = -1, locFinalSdfInvSpacing_ = -1, locFinalSdfTex_ = -1;

    bool timing_ = false;
    GLuint queries_[5] = {};
    std::vector<GLuint> ring_;   // 5 timestamps per step
    int ringSteps_ = 0, ringPos_ = 0;
    std::function<void(const DispatchInfo&)> hook_;
};

// Spawns agents on the seven stand treads measured from stadium.obj, rejection-sampled so
// every agent starts in free space directly above solid tread (checked with sampleSDF_CPU,
// which requires loadSDFTexture3D to have run).
// The centre spawns at the rest height (BODY_RADIUS above the tread), and a load up to
// spawnCapacity() is relaxed (deterministic Gauss-Seidel projection, each agent kept on its tread band)
// until no two bodies overlap; a larger load starts stacked, as placed.
std::vector<GpuBoid> spawnBleacherCrowd(int numBoids, unsigned seed = 1337);

// The most agents spawnBleacherCrowd relaxes free of overlap: the spawn bands' area at random close
// packing of BODY_RADIUS disks (82% covered)
double spawnCapacity();

// Seat spawn of a seated venue: one agent per seat (seated::seats: the clearway centre in front of the seat, at
// the rest height BODY_RADIUS above the tread), at rest. load in [0, 1]: round(load x seats) seats, a seeded random subset
// (seed: a partial Fisher-Yates shuffle on mt19937's raw output, portable), taken in seat order; agents beyond them are
// parked (inactive, w = 0). numBoids must hold every chosen seat (a power of two >= 256 for CrowdSim). activeOut: the
// number of seated agents.
std::vector<GpuBoid> spawnSeatedCrowd(const Venue& venue, int numBoids, double load = 1.0, unsigned seed = 1337, int* activeOut = nullptr);
// The seat index of each spawned agent (-1 for parked ones), for the same arguments
std::vector<int> seatedSpawnSeats(const Venue& venue, int numBoids, double load = 1.0, unsigned seed = 1337);

// Overcrowding of a seated venue. A load above 100%
// fills every seat (the 100% seat spawn, in seat order: agents 0 .. seats - 1 are bit for bit spawnSeatedCrowd(venue, n, 1.0)'s)
// and adds round((load - 1) x seats) people STANDING at rest (floor + BODY_RADIUS) on the circulation floor: the front walkway (from
// the fence's outer face to the barrier) and the rear concourse; StandingAreas::WithGangways also the gangways (inclines and the
// barrier's gaps at their feet: blocked aisles). Never on the avenues, the seat rows or the door passages. Placement: seeded
// uniform random over that floor (mt19937's raw output, portable), a draw kept only if the body fits there (the navigation grid's
// FIT rule plus STANDING_CLEARANCE_MARGIN: outside the fence's collision band, clear of every wall, no step face rising within the
// body's radius) and overlaps no agent placed before it (3D centre distance >= BODY_DIAM + STANDING_CLEARANCE_MARGIN). The standing
// crowd's initial density is at most OVERCROWD_STANDING_MAX_P_M2 over the standing floor's exact area (seated::areas): if the
// requested load needs more, the spawn places that maximum and reports the achievable load (the caller uses it).
constexpr double OVERCROWD_STANDING_MAX_P_M2 = 2.5;      // persons per m^2 of standing floor, initially
constexpr float STANDING_CLEARANCE_MARGIN = 0.000320f;   // 1 cm in model units, beyond the contact rules' own clearances
enum class StandingAreas { Circulation, WithGangways };
struct OvercrowdSpawn {
    std::vector<GpuBoid> boids;     // numBoids: the seated agents (seat order), the standing agents (placement order), parked ones
    std::vector<int> seat;          // per agent its seat index (-1: standing or parked)
    int seats = 0;                  // seated agents: every seat
    int standingRequested = 0;      // round((requestedLoad - 1) x seats)
    int standingMax = 0;            // floor(OVERCROWD_STANDING_MAX_P_M2 x standingAreaM2)
    int standing = 0;               // placed: min(requested, max), unless no free position was found (placementExhausted)
    int standingWalkway = 0, standingConcourse = 0, standingGangways = 0;
    bool placementExhausted = false;
    long draws = 0;                 // random positions drawn
    double standingAreaM2 = 0.0;    // the standing floor (walkway + concourse [+ gangways]), exact
    double requestedLoad = 0.0, load = 0.0;   // load: (seats + standing) / seats, the achievable load used
};
// numBoids 0: the smallest power of two >= 256 that holds everyone. requestedLoad <= 1: the plain seat spawn (spawnSeatedCrowd).
OvercrowdSpawn spawnOvercrowdedCrowd(const Venue& venue, double requestedLoad, unsigned seed = 1337,
                                     StandingAreas areas = StandingAreas::Circulation, int numBoids = 0);
const char* standingAreasName(StandingAreas a);   // "circulation" | "gangways"

} // namespace swarm
