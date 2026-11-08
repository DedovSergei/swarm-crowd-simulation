#pragma once

#include <cstdint>
#include <vector>

#include <swarm/exit_choice.hpp>
#include <swarm/gpu_types.hpp>
#include <swarm/sim_params.hpp>
#include <swarm/venue.hpp>

namespace swarm {

namespace nav { struct Field; }

// CPU reference of CrowdSim::step (OpenMP): the same four stages on the same data layout.
//   hash    calc_grid.comp: 2D column cell per agent, INACTIVE_CELL for evacuated agents
//   sort    by gridID (SortMode), inactive agents at the tail
//   cells   reorder.comp: startIndex / agentCount per cell over the sorted pairs
//   physics physics.comp, ported 1:1 (see cpu_crowd_sim.cpp): reads boids[readIdx], writes
// boids[writeIdx] at the agent's own index, then the indices swap. Its three
//           passes (predict, PROJ_ITERATIONS - 1 projection iterations, final), one parallel loop each,
//           with the projection's slot-order state in two buffers like the GPU's
// One layout difference, no value difference: the GPU's cells pass also copies the
// active agents' state into slot order and physics reads that copy (consecutive memory); the copy
// holds the same bits, so this port keeps reading boids[readIdx] by boidID (the CPU neighbour loop is not
// memory-bound, so a cell-sorted gather gains nothing here).
// Hash and physics run as OpenMP parallel loops over agents: hash under schedule(static), physics
// under the Schedule (default TUNED_SCHEDULE). Every agent's result depends only on the step's input,
// never on scheduling, so the state is bit-identical for any thread count and schedule.
class CpuCrowdSim {
public:
    enum class SortMode {
        // Counting sort by gridID, stable over the hash output (which is in boidID order), so boidID
        // breaks ties. O(N). Same gridID sequence and cell table as the GPU; within a cell the order
        // is ascending boidID, which the GPU's is not, so neighbour sums run in a different order.
        Counting,
        // bitonic_sort.comp's network (same k/j passes, compare-exchange on gridID only), one OpenMP
        // loop per pass. That network is not stable: within a cell it leaves its own deterministic
        // permutation of boidIDs, which this reproduces. Identical (gridID, boidID) sequence to the GPU.
        // O(N log^2 N); needs a power-of-two agent count, like the GPU. The GPU runs
        // the passes with j < 512 in shared memory (bitonic_sort_shared.comp): the same network, so
        // the same sequence; this replay keeps one loop per pass.
        GpuBitonic,
    };

    // Contact branches the physics pass took for an agent in the last step (diagnostics only)
    enum ContactBits : uint8_t {
        CONTACT_EXIT = 1,       // left through a wall gap this step: parked and flagged inactive
        CONTACT_FENCE_CCD = 2,  // fenceCCD clamped a step that crossed the fence midline
        CONTACT_FENCE = 4,      // projected out of the analytic fence (sdFence < 0)
        CONTACT_FLOOR = 8,      // restOnFloor lifted the centre to floor + BODY_RADIUS
        CONTACT_WALL = 16,      // clearWalls pushed the centre away from a wall
        CONTACT_AGENT = 32,     // the hard-body projection moved it
        CONTACT_SWEEP = 64,     // the static sweep took a centre left in solid back along its step
        CONTACT_STEP_UP = 128,  // the step-up limit blocked its move
    };

    // OpenMP loop schedule of the physics pass. Speed only: every agent's result depends only on the
    // step's input, so the state is bit-identical under every schedule.
    enum class Schedule { Static, Dynamic64, Dynamic256, Dynamic1024, Guided };
    // The schedule sweep (static / dynamic 64, 256, 1024 / guided, 1-20 threads, i5-13600KF): at 20
    // threads dynamic,64 is fastest where the CPU spends its time: the sorted slots of dense cells cost far more than
    // sparse ones, and 8 of the 20 threads are E-cores. The hash pass stays static (fastest for its uniform per-agent work).
    static constexpr Schedule TUNED_SCHEDULE = Schedule::Dynamic64;
    static constexpr Schedule BASELINE_SCHEDULE = Schedule::Static;  // the static baseline, selectable for comparison
    // The projection iterations' schedule and the exit choice's threading of the tuned configuration (results/benchmarks/cpu_tuning/sweep.md).
    // configuration. Sweep at 20 threads on S and M (spawn, congested; every (physics, projection) pair of static / dynamic64 / dynamic256 /
    // guided, the exit choice sequential and parallel, 6 rounds, A/A <= 0.2%): no schedule pair beats dynamic64 / dynamic64; the parallel exit
    // choice is faster in every cell (-24% S congested, -29% S spawn, -33% M congested, -35% M spawn; 6 / 6 rounds): the sequential choice was
    // 35% of M's congested step at 20 threads. Bit-identical (cpu_tune golden, test_gpu).
    static constexpr Schedule TUNED_PROJECTION_SCHEDULE = TUNED_SCHEDULE;
    static constexpr bool TUNED_PARALLEL_CHOICE = true;

    // Physics split into its parts (wall clock): the exit choice (queue-aware only), the predict pass, the projection's
    // PROJ_ITERATIONS - 1 Jacobi iterations, the final pass (the last iteration, the final static contacts, the step-up limit)
    struct StageTimesMs { double hash = 0, sort = 0, cells = 0, physics = 0, total = 0, choice = 0, predict = 0, project = 0, final = 0; };

    // The terrace reference venue. sdfVolume: stadium.sdf as loadSDFVolume / sdfVolumeCPU return it (SDF_VOXELS floats).
    // numThreads <= 0 means maxThreads().
    explicit CpuCrowdSim(std::vector<float> sdfVolume, int numThreads = 0, SortMode sortMode = SortMode::Counting);
    // Any venue: its neighbour grid and exit test; a seated venue's analytic distance (swarm::seated, the
    // mirror of shaders/venue_seated.glsl) in place of the baked field (sdfVolume unused, may be empty), and e_goal
    // from its navigation field (swarm::nav::forVenue: built or loaded on first use; physics.comp VENUE_NAV_FIELD)
    CpuCrowdSim(const Venue& venue, std::vector<float> sdfVolume, int numThreads = 0, SortMode sortMode = SortMode::Counting);
    // An analytic venue's model options (swarm/exit_choice.hpp; the constructors above use defaultModelOptions(venue), the
    // terrace ignores them). Queue-aware: the candidate table (nav::choiceForVenue), the assigned exits and the counters, and the
    // choice pass (physics.comp PHYSICS_PASS 0) at the start of the physics stage
    CpuCrowdSim(const Venue& venue, const ModelOptions& options, std::vector<float> sdfVolume, int numThreads = 0, SortMode sortMode = SortMode::Counting);

    // Writes both halves, like CrowdSim::upload, so neither holds a stale state; queue-aware: resets the exit choice (CrowdSim::upload)
    void setState(const std::vector<GpuBoid>& boids);
    // For benchmarks: writes both halves of the agent state only, as the GPU benchmarks' buffer copy does: the exit choice (assignments,
    // counts, the choice step) runs on. Needs a state of the same size set before (setState).
    void restoreAgentState(const std::vector<GpuBoid>& boids);
    void step();

    // The queue-aware exit choice (empty otherwise), as CrowdSim's: the assigned exit per agent, the counters, the choice
    // step; stepExitChoice runs the choice pass alone
    const ModelOptions& options() const { return options_; }
    const std::vector<uint32_t>& assignedExits() const { return choiceState_.assign; }
    const GpuChoiceCounters& choiceCounters() const { return choiceState_.counters; }
    const nav::ChoiceState& choiceState() const { return choiceState_; }   // tools: the queue ahead
    uint32_t choiceStep() const { return choiceState_.step; }
    void stepExitChoice() { chooseExits(); }

    void setNumThreads(int numThreads);   // <= 0: maxThreads(); takes effect from the next step
    void setSchedule(Schedule s) { schedule_ = s; }   // physics pass; BASELINE_SCHEDULE = static
    // The projection iterations' own schedule (default TUNED_SCHEDULE); the predict
    // and final passes keep setSchedule's. Speed only (every agent's result depends only on the iteration's input)
    void setProjectionSchedule(Schedule s) { projSchedule_ = s; }
    // The exit choice's evaluate and apply stages over the agents on the simulation's threads (nav::choiceStep with threads;
    // bit-identical to the sequential pass; the default, TUNED_PARALLEL_CHOICE) or sequentially, in agent order (false)
    void setParallelChoice(bool on) { parallelChoice_ = on; }
    // Jacobi iterations of the hard-body projection (default PROJ_ITERATIONS), as
    // CrowdSim::setProjectionIterations: experiments and diagnostics only, 0 switches it off
    void setProjectionIterations(int iterations);
    int projectionIterations() const { return projIterations_; }

    // Forced motion (tools only, the port of physics.comp's TEST_DRIVE_TABLE): e_goal of agent i is (*table)[i]
    // instead of the router's; nullptr: the router. The table must hold numBoids() entries and outlive the steps.
    void setDriveTable(const std::vector<glm::vec2>* table) { drive_ = table; }

    const Venue& venue() const { return *venue_; }
    int numBoids() const { return int(boids_[0].size()); }
    int numThreads() const { return threads_; }
    SortMode sortMode() const { return sortMode_; }
    Schedule schedule() const { return schedule_; }
    static const char* scheduleName(Schedule s);
    const std::vector<GpuBoid>& state() const { return boids_[readIdx_]; }           // latest state
    // Sorted pairs and cell table of the last step's input (the GPU grid and cell buffers after step())
    const std::vector<GpuGridInfo>& grid() const { return grid_; }
    const std::vector<GpuCellData>& cells() const { return cells_; }
    const std::vector<uint8_t>& contacts() const { return contacts_; }  // ContactBits per agent
    const StageTimesMs& timings() const { return times_; }                 // wall clock, last step

    static int maxThreads();  // omp_get_max_threads()

private:
    void hash();
    void sortCounting();
    void sortBitonic();
    void buildCells();
    void physics();
    void chooseExits();

    const Venue* venue_;
    ModelOptions options_;
    const nav::ChoiceTable* choice_ = nullptr;
    nav::ChoiceState choiceState_;
    std::vector<float> sdf_;
    const std::vector<glm::vec2>* drive_ = nullptr;
    const nav::Field* navField_ = nullptr;
    int threads_;
    SortMode sortMode_;
    Schedule schedule_ = TUNED_SCHEDULE;
    Schedule projSchedule_ = TUNED_PROJECTION_SCHEDULE;
    bool parallelChoice_ = TUNED_PARALLEL_CHOICE;
    double choiceMs_ = 0, predictMs_ = 0, projectMs_ = 0, finalMs_ = 0;   // the last step's physics parts
    std::vector<GpuBoid> boids_[2];
    int readIdx_ = 0, writeIdx_ = 1;
    std::vector<GpuGridInfo> grid_, gridScratch_;
    std::vector<GpuBoid> slotA_, slotB_;   // the physics passes' slot-order state
    std::vector<glm::vec4> planes_;        // per slot: the predict pass's wall plane and grounded flag
    int projIterations_ = PROJ_ITERATIONS;
    std::vector<GpuCellData> cells_;
    std::vector<uint32_t> bucketStart_;
    std::vector<uint8_t> contacts_;
    StageTimesMs times_;
};

// The shaders and this port share every model constant through sim_params.hpp, but the port
// repeats the shaders' logic. To make a logic change impossible to miss, this pins the compute
// shaders it ports: the 64-bit FNV-1a hash of calc_grid.comp, bitonic_sort.comp,
// bitonic_sort_shared.comp, reorder.comp, physics.comp and venue_seated.glsl, concatenated in that order with
// carriage returns removed (comments count). test_gpu fails when the shaders no longer hash to it: port a logic change
// to cpu_crowd_sim.cpp and its mirrors (src/venue.cpp, src/nav_field.cpp, src/exit_choice.cpp), re-run the parity
// checks, then update the value.
constexpr uint64_t PORTED_SHADERS_FNV1A = 0xc7459fcaf9b908a2ull;

#ifdef SWARM_CPU_PROFILE
// Physics sub-phase profile, compiled in only by the cpu_profile target (tools/benchmark): rdtsc
// cycles per phase of physics.comp main() and event counts, summed per OpenMP thread.
namespace cpu_profile {
enum Phase {
    OTHER,       // slot setup, inactive and exiting agents, the egress target (e_goal)
    NEIGHBOUR,   // the PERC_RING ring: cell table, candidate gather, distance test, separation sum, headway
    OBSTACLE,    // torso-height obstacle avoidance: sceneDist + sceneNormal (5 SDF samples, fence)
    STEER,       // the driving term (velocity relaxation), integration
    FENCE,       // fenceCCD and the static fence projection
    FLOOR,       // restOnFloor (both calls)
    WALLS,       // clearWalls: 8 feelers, wallContact root finding and recast
    PROJECT,     // the hard-body projection iterations
    PHASE_COUNT
};
enum Count { AGENTS, CANDIDATES, NEIGHBOURS, SEP_PAIRS, MAP_CALLS, EXACT_GRAD_CALLS, COUNT_COUNT };
struct alignas(64) ThreadSlot { uint64_t cycles[PHASE_COUNT]; uint64_t counts[COUNT_COUNT]; };
constexpr int MAX_THREADS = 64;
extern ThreadSlot slots[MAX_THREADS];
extern bool skipSeparation;   // ablation: the neighbour loop without separationForce
void reset();
} // namespace cpu_profile
#endif

} // namespace swarm
