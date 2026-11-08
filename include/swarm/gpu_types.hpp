#pragma once

// Shared CPU/GPU SSBO layouts. Every struct here must match its GLSL
// counterpart under std430 rules byte-for-byte; the static_asserts below
// fail the build if the C++ side drifts.

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <glm/glm.hpp>

namespace swarm {

#pragma pack(push, 16)

// GLSL: struct Boid { vec4 position; vec4 velocity; };
struct alignas(16) GpuBoid {
    glm::vec4 position; // xyz = position, w = active/evacuated state flag
    glm::vec4 velocity; // xyz = velocity, w = speed
};

// GLSL: struct GridInfo { uint gridID; uint boidID; uint padding0; uint padding1; };
struct alignas(16) GpuGridInfo {
    uint32_t gridID;
    uint32_t boidID;
    uint32_t padding0;
    uint32_t padding1;
};

// GLSL: struct CellData { uint startIndex; uint agentCount; uint padding0; uint padding1; };
struct alignas(16) GpuCellData {
    uint32_t startIndex;
    uint32_t agentCount;
    uint32_t padding0;
    uint32_t padding1;
};

// GLSL (physics.comp, VENUE_NAV_FIELD): struct NavCell { vec2 anchor; float dist; uint info; };
// The navigation field of an analytic venue (swarm/nav_field.hpp), one per grid cell, read-only: the anchor (the
// first vertex of the cell's shortest path to an exit), the distance to the exit (model units, horizontal; +infinity: none),
// info = the exit id (bits 0-7) | nav::NAV_FIT | nav::NAV_REACHABLE.
struct alignas(16) GpuNavCell {
    float anchorX, anchorY;
    float dist;
    uint32_t info;
};

// GLSL (physics.comp, VENUE_EXIT_CHOICE): struct NavChoiceCell { uint slot[24]; uint dist[12]; };
// The exit choice's candidate table (swarm/exit_choice.hpp; stored only for
// the cells whose lookup can return them: nav::ChoiceTable::index), read-only: the nav::CHOICE_K = 24 candidates, ascending walking distance (ties: the lower exit id): the 2 nearest
// avenues and the nearest door (nav::CHOICE_TYPE_MIN), then the nearest other exits. slot[k] = the anchor's
// cell index (bits 0-24) | the exit id (bits 25-30; nav::CHOICE_EMPTY = 63: no candidate) | nav::CHOICE_FIT (bit 31, the cell's class,
// in every slot); dist[k / 2] bits 16 (k & 1) .. + 15 = the walking distance from the cell's centre to that exit in quanta of
// nav::CHOICE_DIST_QUANTUM = 2^-12 model units (7.6 mm; 0xFFFF: empty slot): nav::slotDist.
struct alignas(16) GpuNavChoiceCell {
    uint32_t slot[24];
    uint32_t dist[12];
};

// GLSL (physics.comp PHYSICS_PASS 0): buffer ChoiceCounters { uint queue[128]; uint switches; uint forced; uint evaluations;
// uint eligible; }. The exit choice's counters: queue[h * 64 + e], the agents assigned to exit e, counted by integer
// atomics in the choice pass of the steps with parity h (the next step reads them: Q_e); totals since the last upload: switches
// (re-evaluations that changed the exit), forced (choices forced because the assigned exit was no candidate of the agent's cell),
// evaluations (agents re-evaluated), eligible (of them, gains above the hysteresis margins: candidates for the switch cap).
struct alignas(16) GpuChoiceCounters {
    uint32_t queue[128];
    uint32_t switches;
    uint32_t forced;
    uint32_t evaluations;
    uint32_t eligible;
};

// GLSL (physics.comp PHYSICS_PASS 0): buffer ChoiceWork { uint threshold[64]; uint hist[64 * 256]; uint ahead[]; }. The switch cap's
// working storage: per exit the eligible agents' gain histogram (CHOICE_GAIN_BINS bins of 1 s) of the current evaluation, and
// the lowest gain bin that switches. The threshold stage clears each histogram after reading it. The QUEUE
// AHEAD: ahead[h * 64 * 1024 + e * 1024 + b], per parity h, exit e and distance bin b (nav::aheadBin: 64 distance quanta = 0.49 m) the
// agents assigned to e by the apply stage of the steps of parity h, counted at their own distance to e; the next step's prefix stage
// turns parity h into exclusive prefix sums (the agents assigned to e in nearer bins) and clears the other parity.
struct alignas(16) GpuChoiceWork {
    uint32_t threshold[64];
    uint32_t hist[64 * 256];
    uint32_t ahead[2 * 64 * 1024];
};

// --- Safety metrics (swarm/metrics.hpp): write-only side outputs of the step ---

// GLSL (metrics_deposit.comp, metrics_finalize.comp): buffer Counters { uint step; uint active;
// uint evacuated; uint activeAccum; uint exits[61]; uint pad[3]; uint gangwayVisits[64]; uint gangwayLast[64]; }. The small
// counters a UI reads (AsyncCounterReader): 61 exit slots (5 + up to 56 doors: venue L has 44) and the per-gangway
// utilisation of a seated venue (seated::gangwayAt
// ids, up to 64): the agents that stood on each gangway (each agent counted once per gangway), and the evacuated agents whose last
// gangway it was.
struct alignas(16) GpuMetricCounters {
    uint32_t step;          // metric steps recorded: the stepIndex of the last finalize pass (1 = first step)
    uint32_t active;        // active agents after that step
    uint32_t evacuated;     // agents evacuated since the last reset (= the sum of exits[])
    uint32_t activeAccum;   // the deposit pass's count for the step in flight (0 between steps)
    uint32_t exits[61];     // per exit (metrics::Exit): +x, -x, +y, -y, other, then a seated venue's concourse doors
    uint32_t pad[3];
    uint32_t gangwayVisits[64];   // per gangway, the agents that stood on it
    uint32_t gangwayLast[64];     // per gangway, the evacuated agents whose last gangway it was
};

// GLSL: struct CellMass { uint mass; uint speedMass; uint pad0; uint pad1; }. One step's cloud-in-cell
// deposit per floor cell, in fixed point (metrics::MASS_ONE units per person); cleared by the finalize pass.
struct alignas(16) GpuMetricCellMass {
    uint32_t mass;        // persons x MASS_ONE
    uint32_t speedMass;   // persons x (horizontal speed in m/s) x MASS_ONE
    uint32_t padding0;
    uint32_t padding1;
};

// GLSL: struct CellInfo { uvec4 thresholdMass; float walkableM2; uint zone; uint pad0; uint pad1; }.
// Static per venue (computeMetricVenue): the density thresholds as cell masses, so the finalize pass
// compares integers: density >= threshold <=> mass >= ceil(threshold * walkableM2 * MASS_ONE).
struct alignas(16) GpuMetricCellInfo {
    uint32_t thresholdMass[4];   // LoS E, LoS F, crush, unused (0xFFFFFFFF); all 0xFFFFFFFF for excluded cells
    float walkableM2;            // walkable floor area of the cell (0: excluded)
    uint32_t zone;               // metrics::Zone
    uint32_t padding0;
    uint32_t padding1;
};

// GLSL: struct MetricCell { uint lastMass; uint lastSpeedMass; uint peakMass; uint occupiedSteps;
// uvec4 stepsAbove; uvec2 massSteps; uvec2 speedMassSteps; uvec2 exposureMassSteps; uvec2 pad; }.
// Per-cell accumulators since the last reset; uvec2 = 64-bit (lo, hi).
struct alignas(16) GpuMetricCell {
    uint32_t lastMass;               // mass of the most recent step
    uint32_t lastSpeedMass;          // speed mass of the most recent step
    uint32_t peakMass;               // max over steps of mass
    uint32_t occupiedSteps;          // steps with mass > 0
    uint32_t stepsAbove[4];          // steps with mass >= thresholdMass[k]
    uint32_t massSteps[2];           // sum over steps of mass (person-steps x MASS_ONE)
    uint32_t speedMassSteps[2];      // sum over steps of speedMass
    uint32_t exposureMassSteps[2];   // sum over steps with mass >= the crush threshold of mass
    uint32_t padding[2];
};

#pragma pack(pop)

// --- std430 parity checks ---
static_assert(sizeof(glm::vec4) == 16, "glm::vec4 must be 16 bytes (check GLM_FORCE_* defines)");

static_assert(std::is_standard_layout_v<GpuBoid> && std::is_trivially_copyable_v<GpuBoid>, "GpuBoid must be POD-like");
static_assert(sizeof(GpuBoid) == 32, "GpuBoid must be 32 bytes");
static_assert(alignof(GpuBoid) == 16, "GpuBoid must be 16-byte aligned");
static_assert(offsetof(GpuBoid, position) == 0, "GpuBoid::position offset");
static_assert(offsetof(GpuBoid, velocity) == 16, "GpuBoid::velocity offset");

static_assert(std::is_standard_layout_v<GpuGridInfo> && std::is_trivially_copyable_v<GpuGridInfo>, "GpuGridInfo must be POD-like");
static_assert(sizeof(GpuGridInfo) == 16, "GpuGridInfo must be 16 bytes");
static_assert(alignof(GpuGridInfo) == 16, "GpuGridInfo must be 16-byte aligned");
static_assert(offsetof(GpuGridInfo, gridID) == 0, "GpuGridInfo::gridID offset");
static_assert(offsetof(GpuGridInfo, boidID) == 4, "GpuGridInfo::boidID offset");
static_assert(offsetof(GpuGridInfo, padding0) == 8, "GpuGridInfo::padding0 offset");
static_assert(offsetof(GpuGridInfo, padding1) == 12, "GpuGridInfo::padding1 offset");

static_assert(std::is_standard_layout_v<GpuCellData> && std::is_trivially_copyable_v<GpuCellData>, "GpuCellData must be POD-like");
static_assert(sizeof(GpuCellData) == 16, "GpuCellData must be 16 bytes");
static_assert(alignof(GpuCellData) == 16, "GpuCellData must be 16-byte aligned");
static_assert(offsetof(GpuCellData, startIndex) == 0, "GpuCellData::startIndex offset");
static_assert(offsetof(GpuCellData, agentCount) == 4, "GpuCellData::agentCount offset");
static_assert(offsetof(GpuCellData, padding0) == 8, "GpuCellData::padding0 offset");
static_assert(offsetof(GpuCellData, padding1) == 12, "GpuCellData::padding1 offset");

static_assert(std::is_standard_layout_v<GpuNavCell> && std::is_trivially_copyable_v<GpuNavCell>, "GpuNavCell must be POD-like");
static_assert(sizeof(GpuNavCell) == 16, "GpuNavCell must be 16 bytes");
static_assert(alignof(GpuNavCell) == 16, "GpuNavCell must be 16-byte aligned");
static_assert(offsetof(GpuNavCell, anchorX) == 0, "GpuNavCell::anchor offset (vec2)");
static_assert(offsetof(GpuNavCell, anchorY) == 4, "GpuNavCell::anchor.y offset");
static_assert(offsetof(GpuNavCell, dist) == 8, "GpuNavCell::dist offset");
static_assert(offsetof(GpuNavCell, info) == 12, "GpuNavCell::info offset");

static_assert(std::is_standard_layout_v<GpuNavChoiceCell> && std::is_trivially_copyable_v<GpuNavChoiceCell>, "GpuNavChoiceCell must be POD-like");
static_assert(sizeof(GpuNavChoiceCell) == 144, "GpuNavChoiceCell must be 144 bytes");
static_assert(alignof(GpuNavChoiceCell) == 16, "GpuNavChoiceCell must be 16-byte aligned");
static_assert(offsetof(GpuNavChoiceCell, slot) == 0, "GpuNavChoiceCell::slot offset (uint[24])");
static_assert(offsetof(GpuNavChoiceCell, dist) == 96, "GpuNavChoiceCell::dist offset (uint[12])");

static_assert(std::is_standard_layout_v<GpuChoiceCounters> && std::is_trivially_copyable_v<GpuChoiceCounters>, "GpuChoiceCounters must be POD-like");
static_assert(sizeof(GpuChoiceCounters) == 528, "GpuChoiceCounters must be 528 bytes");
static_assert(alignof(GpuChoiceCounters) == 16, "GpuChoiceCounters must be 16-byte aligned");
static_assert(offsetof(GpuChoiceCounters, queue) == 0, "GpuChoiceCounters::queue offset");
static_assert(offsetof(GpuChoiceCounters, switches) == 512, "GpuChoiceCounters::switches offset");
static_assert(offsetof(GpuChoiceCounters, forced) == 516, "GpuChoiceCounters::forced offset");
static_assert(offsetof(GpuChoiceCounters, evaluations) == 520, "GpuChoiceCounters::evaluations offset");
static_assert(offsetof(GpuChoiceCounters, eligible) == 524, "GpuChoiceCounters::eligible offset");

static_assert(std::is_standard_layout_v<GpuChoiceWork> && std::is_trivially_copyable_v<GpuChoiceWork>, "GpuChoiceWork must be POD-like");
static_assert(sizeof(GpuChoiceWork) == 590080, "GpuChoiceWork must be 590080 bytes");
static_assert(offsetof(GpuChoiceWork, ahead) == 65792, "GpuChoiceWork::ahead offset");
static_assert(alignof(GpuChoiceWork) == 16, "GpuChoiceWork must be 16-byte aligned");
static_assert(offsetof(GpuChoiceWork, hist) == 256, "GpuChoiceWork::hist offset");

static_assert(std::is_standard_layout_v<GpuMetricCounters> && std::is_trivially_copyable_v<GpuMetricCounters>, "GpuMetricCounters must be POD-like");
static_assert(sizeof(GpuMetricCounters) == 784, "GpuMetricCounters must be 784 bytes");
static_assert(alignof(GpuMetricCounters) == 16, "GpuMetricCounters must be 16-byte aligned");
static_assert(offsetof(GpuMetricCounters, step) == 0, "GpuMetricCounters::step offset");
static_assert(offsetof(GpuMetricCounters, active) == 4, "GpuMetricCounters::active offset");
static_assert(offsetof(GpuMetricCounters, evacuated) == 8, "GpuMetricCounters::evacuated offset");
static_assert(offsetof(GpuMetricCounters, activeAccum) == 12, "GpuMetricCounters::activeAccum offset");
static_assert(offsetof(GpuMetricCounters, exits) == 16, "GpuMetricCounters::exits offset");
static_assert(offsetof(GpuMetricCounters, pad) == 260, "GpuMetricCounters::pad offset");
static_assert(offsetof(GpuMetricCounters, gangwayVisits) == 272, "GpuMetricCounters::gangwayVisits offset");
static_assert(offsetof(GpuMetricCounters, gangwayLast) == 528, "GpuMetricCounters::gangwayLast offset");

static_assert(std::is_standard_layout_v<GpuMetricCellMass> && std::is_trivially_copyable_v<GpuMetricCellMass>, "GpuMetricCellMass must be POD-like");
static_assert(sizeof(GpuMetricCellMass) == 16, "GpuMetricCellMass must be 16 bytes");
static_assert(alignof(GpuMetricCellMass) == 16, "GpuMetricCellMass must be 16-byte aligned");
static_assert(offsetof(GpuMetricCellMass, mass) == 0, "GpuMetricCellMass::mass offset");
static_assert(offsetof(GpuMetricCellMass, speedMass) == 4, "GpuMetricCellMass::speedMass offset");
static_assert(offsetof(GpuMetricCellMass, padding0) == 8, "GpuMetricCellMass::padding0 offset");
static_assert(offsetof(GpuMetricCellMass, padding1) == 12, "GpuMetricCellMass::padding1 offset");

static_assert(std::is_standard_layout_v<GpuMetricCellInfo> && std::is_trivially_copyable_v<GpuMetricCellInfo>, "GpuMetricCellInfo must be POD-like");
static_assert(sizeof(GpuMetricCellInfo) == 32, "GpuMetricCellInfo must be 32 bytes");
static_assert(alignof(GpuMetricCellInfo) == 16, "GpuMetricCellInfo must be 16-byte aligned");
static_assert(offsetof(GpuMetricCellInfo, thresholdMass) == 0, "GpuMetricCellInfo::thresholdMass offset (uvec4)");
static_assert(offsetof(GpuMetricCellInfo, walkableM2) == 16, "GpuMetricCellInfo::walkableM2 offset");
static_assert(offsetof(GpuMetricCellInfo, zone) == 20, "GpuMetricCellInfo::zone offset");
static_assert(offsetof(GpuMetricCellInfo, padding0) == 24, "GpuMetricCellInfo::padding0 offset");
static_assert(offsetof(GpuMetricCellInfo, padding1) == 28, "GpuMetricCellInfo::padding1 offset");

static_assert(std::is_standard_layout_v<GpuMetricCell> && std::is_trivially_copyable_v<GpuMetricCell>, "GpuMetricCell must be POD-like");
static_assert(sizeof(GpuMetricCell) == 64, "GpuMetricCell must be 64 bytes");
static_assert(alignof(GpuMetricCell) == 16, "GpuMetricCell must be 16-byte aligned");
static_assert(offsetof(GpuMetricCell, lastMass) == 0, "GpuMetricCell::lastMass offset");
static_assert(offsetof(GpuMetricCell, lastSpeedMass) == 4, "GpuMetricCell::lastSpeedMass offset");
static_assert(offsetof(GpuMetricCell, peakMass) == 8, "GpuMetricCell::peakMass offset");
static_assert(offsetof(GpuMetricCell, occupiedSteps) == 12, "GpuMetricCell::occupiedSteps offset");
static_assert(offsetof(GpuMetricCell, stepsAbove) == 16, "GpuMetricCell::stepsAbove offset (uvec4)");
static_assert(offsetof(GpuMetricCell, massSteps) == 32, "GpuMetricCell::massSteps offset (uvec2)");
static_assert(offsetof(GpuMetricCell, speedMassSteps) == 40, "GpuMetricCell::speedMassSteps offset (uvec2)");
static_assert(offsetof(GpuMetricCell, exposureMassSteps) == 48, "GpuMetricCell::exposureMassSteps offset (uvec2)");
static_assert(offsetof(GpuMetricCell, padding) == 56, "GpuMetricCell::padding offset (uvec2)");

} // namespace swarm
