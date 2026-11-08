#pragma once

// Safety metrics: write-only side outputs of the simulation step, in real units.
//
// After a step, CrowdMetrics::afterStep(sim) runs two compute passes that only READ the agent state
// (the step's input and output buffers) and write buffers of their own:
//   metrics_deposit.comp  (one invocation per agent)
//     - evacuation events: an agent active in the input and inactive in the output left through the
//       exit at its last active position; the exit's counter is incremented atomically and the step is
//       written to the agent's slot of the evacuation-step buffer;
//     - density: every active agent deposits one person bilinearly (cloud-in-cell) onto the 4 floor
//       cells whose centres surround it, in fixed point with uint atomics (GL 4.3 core has no float
//       atomics), together with its horizontal speed times that weight;
//   metrics_finalize.comp (one invocation per floor cell)
//     - density = mass / walkable area, compared with the thresholds as integer masses; peak, steps at
//       or above each threshold, occupied steps, the person-step and speed sums (mean speed when
//       occupied), exposure (person-steps while density >= the crush threshold); then it clears the
//       step's mass.
// Nothing here writes agent state, and CrowdSim::step() does not depend on it: with metrics disabled (no
// CrowdMetrics, or afterStep not called) the GL command stream has none of these passes.
//
// The floor grid is in metres: METRIC_CELL_M x METRIC_CELL_M cells over the whole simulation domain.
// Each cell's walkable floor area and zone are precomputed once per venue on the CPU sampler
// (computeMetricVenue). Times are counted in steps; one step is DT_REAL_S seconds (sim_params.hpp).
//
// Fixed point and its round-off: a position is quantized to 1/SUBCELL of a cell (3.9 mm at 1 m cells)
// before the cloud-in-cell weights are formed, and the weights are the exact integer products
// (SUBCELL - qx)(SUBCELL - qy), qx(SUBCELL - qy), ... which sum to MASS_ONE = SUBCELL^2 for every agent.
// So the deposited mass is exactly (active agents) x MASS_ONE every step (no round-off in the total),
// and each cell's share of an agent differs from the exact-position bilinear weight by at most
// 1/SUBCELL (0.39% of a person). The speed mass rounds each weight x speed product to the nearest
// unit: at most 0.5 / MASS_ONE person m/s per deposit. Capacity: one cell holds up to 65535 persons
// per step (uint32 mass), the speed mass up to 48900 persons at V_FREE_M_S; the per-cell sums over
// steps are 64-bit.

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <array>
#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

#include <swarm/gpu_caps.hpp>
#include <swarm/gpu_types.hpp>
#include <swarm/shader.hpp>
#include <swarm/sim_params.hpp>

namespace swarm {

class CrowdSim;
struct SeatedLayout;
struct Venue;

namespace metrics {

// --- Floor grid (real units) ---
// The grid's size is the venue's (Venue::metricGridRes, centred on 0, a multiple of 16): GRID_RES, GRID_MIN_M and CELLS
// below are the terrace's and venue S's grid (the defaults of the functions taking a resolution); venues M and L have larger ones.
constexpr double CELL_M = 1.0;          // cell edge, metres
constexpr int GRID_RES = 64;            // cells per axis
constexpr double GRID_MIN_M = -32.0;    // lower-left corner, metres (x and y); integer metres, symmetric about 0
constexpr int CELLS = GRID_RES * GRID_RES;
inline double gridMinM(int res) { return -0.5 * res * CELL_M; }
inline float gridOffset(int res) { return float(0.5 * res - 0.5); }   // GRID_OFFSET of a grid of res cells (exact in float)
int gridResOf(size_t cells);   // the resolution of a centred grid with this many cells (throws unless a square of a multiple of 16)
static_assert(GRID_MIN_M <= units::metres(DOMAIN_MIN) && GRID_MIN_M + GRID_RES * CELL_M >= units::metres(DOMAIN_MAX),
              "the metric grid must cover the simulation domain");
static_assert(GRID_MIN_M + 0.5 * GRID_RES * CELL_M == 0.0, "the metric grid is centred on the origin");
// Shader: g = xy * CELLS_PER_UNIT + GRID_OFFSET is the position in cells relative to the centre of cell 0
constexpr float CELLS_PER_UNIT = float(units::M_PER_UNIT / CELL_M);   // 31.25 at 1 m cells
constexpr float GRID_OFFSET = float(-GRID_MIN_M / CELL_M - 0.5);      // 31.5
static_assert(CELLS_PER_UNIT == 31.25f && GRID_OFFSET == 31.5f, "both are exact in float (the CPU reference relies on it)");

// --- Fixed point ---
constexpr uint32_t SUBCELL = 256;                  // cloud-in-cell position quantum: 1/256 of a cell
constexpr uint32_t MASS_ONE = SUBCELL * SUBCELL;   // one person = 65536 mass units
// Horizontal speed in m/s per model speed unit: WORLD_SCALE_M_PER_UNIT / TIME_SCALE_S_PER_UNIT
constexpr float SPEED_M_S_PER_UNIT = float(units::metresPerSecond(1.0));

// --- Density thresholds, persons per m^2 (>= counts as above) ---
// Fruin, J. J. (1971), "Pedestrian Planning and Design", walkway Level of Service: LoS E from about
// 1.08 persons/m^2 (10 ft^2 = 0.93 m^2 per person), LoS F from about 2.17 persons/m^2 (5 ft^2 =
// 0.46 m^2 per person). Verify against the cited source.
constexpr double LOS_E_P_M2 = 1.08;
constexpr double LOS_F_P_M2 = 2.17;
// Crush risk from about 5 persons/m^2: Fruin, J. J. (1993), "The causes and prevention of crowd
// disasters" (Engineering for Crowd Safety, Elsevier); Still, G. K. (2000), "Crowd Dynamics", PhD
// thesis, University of Warwick. Verify against the cited source.
constexpr double CRUSH_P_M2 = 5.0;
constexpr int THRESHOLD_COUNT = 3;   // GpuMetricCellInfo::thresholdMass / GpuMetricCell::stepsAbove [0..2]; [3] unused
constexpr std::array<double, THRESHOLD_COUNT> THRESHOLD_P_M2{ LOS_E_P_M2, LOS_F_P_M2, CRUSH_P_M2 };
constexpr std::array<const char*, THRESHOLD_COUNT> THRESHOLD_NAMES{ "los_e", "los_f", "crush" };
constexpr int CRUSH_INDEX = 2;
constexpr uint32_t NEVER = 0xFFFFFFFFu;   // threshold mass that is never reached (unused slot, excluded cell)

// --- Exits: the terrace's four avenue gaps in the outer wall (its only exits) ---
// An evacuated agent is assigned by its last active position (the one the physics exit test saw):
// the avenue axis it is on (|y| >= |x|: y), the sign, and lat < AVENUE_HALF (inside the avenue);
// anything else is EXIT_OTHER, which the terrace never produces (test_gpu metrics.safety).
// A seated venue (exitSlot with its layout; the shader compiled with the venue's preamble): the avenue slots where
// lat < its avenueHalf, else its 8 concourse doors (lat within [exitLo, exitHi]): EXIT_DOOR0 + 2 quadrant + wing (quadrant 0
// (+x +y), 1 (-x +y), 2 (-x -y), 3 (+x -y); wing 0: the door in the outer wall facing y, |y| >= |x|), else EXIT_OTHER.
// Up to 56 door slots (seated::exitByLat's door order: EXIT_DOOR0 + exit id - 4); venue S uses 8, M 28, L 44.
enum Exit : int { EXIT_POS_X, EXIT_NEG_X, EXIT_POS_Y, EXIT_NEG_Y, EXIT_OTHER, EXIT_DOOR0, EXIT_SLOTS = EXIT_DOOR0 + 56 };
constexpr int EXIT_GAPS = 4;
constexpr int EXIT_DOORS = 56;
static_assert(EXIT_SLOTS == int(sizeof(GpuMetricCounters::exits) / sizeof(uint32_t)), "GpuMetricCounters::exits has one slot per exit");
// "+x", "-x", "+y", "-y", "other", "door +x+y y" .. (venue S's eight; seated: the layout's door names, seated::exitName)
std::string exitName(int exit, const SeatedLayout* seated = nullptr);
int exitSlot(glm::vec4 lastActivePosition, const SeatedLayout* seated = nullptr);   // the shader's exitSlot() (metrics_deposit.comp)
// The slots a venue's agents can leave through: the terrace 0 .. EXIT_OTHER, a seated venue EXIT_DOOR0 + its doors
int exitSlotsUsed(const SeatedLayout* seated);
// Per-gangway utilisation (GpuMetricCounters::gangwayVisits / gangwayLast; seated::gangwayAt ids)
constexpr int GANGWAY_SLOTS = 64;
static_assert(GANGWAY_SLOTS == int(sizeof(GpuMetricCounters::gangwayVisits) / sizeof(uint32_t)), "one slot per gangway");

// --- Zones (router layout of the current stadium, sim_params.hpp) ---
// Per sample point: PITCH inside the fence midline; AVENUE where lat < AVENUE_HALF (EXIT from the outer
// wall's inner face outward); WALKWAY up to dep WALKWAY_MAX; AISLE where lat < AISLE_MAX; else TREAD
// (the treads and the back platform). A cell's zone is the zone of most of its walkable samples.
enum Zone : uint32_t { ZONE_TREAD, ZONE_AISLE, ZONE_WALKWAY, ZONE_AVENUE, ZONE_PITCH, ZONE_EXIT, ZONE_COUNT };
const char* zoneName(uint32_t zone);   // "tread", "aisle", "walkway", "avenue", "pitch", "exit"

// --- Venue precompute (CPU sampler; once per venue) ---
// A sample point (x, y) is walkable floor if it lies inside the baked mesh's footprint (x, y in
// [-0.95, 0.95]: the SDF's pad voxels beyond it carry the bake's ground plane, outside the outer
// wall), the stadium is free at FLOOR_PROBE_TOP_Z and solid at FLOOR_PROBE_BOTTOM_Z above it (a floor
// lies between: treads, aisles, walkway, avenues, platform, pitch), and it is outside the pitch
// fence's visual band (the baked field does not contain the fence). FLOOR_PROBE_TOP_Z lies between the highest floor (the back platform, z 0.141) and the
// lowest wall top (the avenue side walls, z 0.164): wall footprints are not walkable.
constexpr float FLOOR_PROBE_TOP_Z = 0.150f;     // model units
constexpr float FLOOR_PROBE_BOTTOM_Z = -0.010f; // below the ground plane (solid everywhere inside the SDF volume)
constexpr int SUBSAMPLES = 40;                  // per cell axis: 2.5 cm sample spacing at 1 m cells
// Cells with less walkable area than this are excluded (no density, no thresholds): a sliver of floor
// would turn the cloud-in-cell tail of a neighbour into a large density.
constexpr double MIN_WALKABLE_M2 = 0.10;
// PEAK-density reporting (run_experiment's zone and circulation peaks, its per-step zone maxima and hotspot lists, the viewer's
// peak-density overlay) counts only cells with at least this much floor. A partial cell turns the cloud-in-cell share of the agents
// passing it into a density over a small area: venue M's 0.1 m^2 door-passage cells read 12.72 persons/m^2. The
// time above the thresholds and the crush exposure keep MIN_WALKABLE_M2 (they weigh such cells by their persons, not their area).
constexpr double PEAK_MIN_WALKABLE_M2 = 0.5;

struct MetricVenue {
    int res = GRID_RES;                  // cells per axis (the venue's metric grid)
    std::vector<float> walkableM2;       // per cell (row-major, cell = ix + iy * res)
    std::vector<uint32_t> zone;          // per cell (the majority zone of its walkable samples; ZONE_COUNT if none)
    std::vector<uint8_t> included;       // walkableM2 >= MIN_WALKABLE_M2
    float outerWallInnerDepth = 0.0f;    // model units: the outer wall's inner face (start of the EXIT zone)
    std::array<float, EXIT_SLOTS> exitWidthM{};   // geometric clear width of each exit at dep EXIT_DEPTH, rest height (m); 0: none
    std::vector<GpuMetricCellInfo> cellInfo() const;   // the GPU table (thresholds as cell masses)
};
MetricVenue computeMetricVenue(const std::vector<float>& sdfVolume);
// The same table for a seated venue, from its analytic cells (swarm::seated), the same sample grid. Walkable: the
// floor cells (ground, clearways, gangways, concourse and its exits) up to the outer wall's outer face (beyond it agents have
// left), the pitch included, the fence's visual band excluded; not walkable: seat blocks, barrier, walls. Zones: pitch,
// walkway (and the rear concourse: no zone of its own), avenue (EXIT from the outer wall's inner face outward), aisle (the
// gangways and the barrier's gaps at their feet), tread (the clearways), exit (the concourse exits through the outer wall).
// Exit widths: the four avenue exits and the concourse doors (exitHi - exitLo).
MetricVenue computeMetricVenueSeated(const SeatedLayout& layout, int res = GRID_RES);
MetricVenue computeMetricVenue(const Venue& venue);                  // either, on the venue's metric grid
uint32_t sampleZone(glm::vec2 xyModel, float outerWallInnerDepth);   // zone of one sample point
glm::vec2 cellCentreM(int cell, int res = GRID_RES);                 // metres
int cellIndex(int ix, int iy, int res = GRID_RES);

// --- Cloud-in-cell deposit, exactly as metrics_deposit.comp computes it (CPU reference) ---
struct CicDeposit { int cell[4]; uint32_t weight[4]; };   // cells (ix, iy), (ix+1, iy), (ix, iy+1), (ix+1, iy+1), clamped
CicDeposit cicDeposit(glm::vec2 xyModel, int res = GRID_RES);
uint32_t speedMass(uint32_t weight, float speedMps);      // floor(float(weight) * speed + 0.5)
float horizontalSpeedMps(const glm::vec4& velocity);      // |v_xy| * SPEED_M_S_PER_UNIT (the GPU's length() may differ in the last bit)

// 64-bit accumulator of a GpuMetricCell (lo, hi)
inline uint64_t sum64(const uint32_t v[2]) { return uint64_t(v[0]) | (uint64_t(v[1]) << 32); }

// #defines for the metric shaders (inserted after the simulation preamble; test_gpu metrics.safety checks
// every value against the GPU); res: the metric grid's resolution
std::string metricsPreamble(int res = GRID_RES);

// --- GPU metrics ---
class CrowdMetrics {
public:
    // cellInfo: MetricVenue::cellInfo() of the venue (its metric grid's cells). venue: the metric shaders are
    // compiled with its preamble (a seated venue's doors and gangways); nullptr: the terrace
    CrowdMetrics(const std::filesystem::path& shaderDir, int numBoids, const std::vector<GpuMetricCellInfo>& cellInfo, const Venue* venue = nullptr);
    // The programs the constructor builds, in its order (metric grid res = gridResOf(cellInfo.size()); the viewer compiles them ahead)
    static std::vector<ProgramSpec> programSpecs(const std::filesystem::path& shaderDir, int res, const Venue* venue);
    // What the constructor needs from the GPU (swarm/gpu_caps.hpp; res as above; seated: the programs compiled with a seated venue's preamble)
    static std::vector<ProgramBindings> programBindings(bool seated);
    static std::vector<GpuBufferUse> bufferUses(int numBoids, int res);
    ~CrowdMetrics();
    CrowdMetrics(const CrowdMetrics&) = delete;
    CrowdMetrics& operator=(const CrowdMetrics&) = delete;

    // Zeroes every counter and accumulator and the step index (no step recorded yet)
    void reset();
    // Records the step sim just took: its input (previousStateBuffer) and output (currentStateBuffer).
    // Call once after every CrowdSim::step().
    void afterStep(const CrowdSim& sim);
    // The same for any pair of agent-state buffers (tests: synthetic states)
    void record(GLuint prevState, GLuint curState);

    int numBoids() const { return numBoids_; }
    uint32_t steps() const { return steps_; }   // steps recorded since the last reset
    GLuint countersBuffer() const { return counters_; }   // GpuMetricCounters
    GLuint evacStepBuffer() const { return evacStep_; }   // uint per agent: the step it left (0: not evacuated)
    GLuint cellBuffer() const { return cells_; }          // GpuMetricCell per floor cell
    GLuint massBuffer() const { return mass_; }           // GpuMetricCellMass per floor cell (zero between steps)
    int gridRes() const { return res_; }                  // the metric grid's cells per axis

    // Synchronous readbacks for tests and the headless experiment runner (they wait on the GPU)
    GpuMetricCounters readCounters() const;
    std::vector<uint32_t> readEvacSteps() const;
    std::vector<GpuMetricCell> readCells() const;

private:
    int numBoids_;
    int res_ = GRID_RES;
    uint32_t steps_ = 0;
    GLuint depositProg_ = 0, finalizeProg_ = 0;
    GLuint counters_ = 0, evacStep_ = 0, mass_ = 0, info_ = 0, cells_ = 0;
    GLuint gangway_ = 0;   // uvec4 per agent (seated venues): gangways visited (bits 0-31, 32-63), the last one + 1
    bool bindGangway_ = false;   // a seated venue's program reads it; the terrace's does not, and a GPU may not have its binding point
    GLint locDepositNum_ = -1, locDepositStep_ = -1, locFinalizeStep_ = -1;
};

// --- CPU reference of the two passes (tests): the same integer arithmetic on CPU-side states ---
class MetricsReference {
public:
    // seated: a seated venue's layout (its exits), nullptr: the terrace
    MetricsReference(int numBoids, std::vector<GpuMetricCellInfo> cellInfo, const SeatedLayout* seated = nullptr);
    void record(const std::vector<GpuBoid>& prev, const std::vector<GpuBoid>& cur);
    uint32_t steps = 0;
    GpuMetricCounters counters{};
    std::vector<uint32_t> evacStep;
    std::vector<GpuMetricCell> cells;
private:
    std::vector<GpuMetricCellInfo> info_;
    const SeatedLayout* seated_ = nullptr;
    int res_ = GRID_RES;
    std::vector<std::array<uint32_t, 3>> gangway_;   // the deposit pass's per-agent gangway state
};

} // namespace metrics

// SSBO binding points of the metric passes (the agent-state buffers keep CrowdSim's 0 and 3)
constexpr GLuint BIND_METRIC_COUNTERS = 5;
constexpr GLuint BIND_METRIC_EVAC_STEP = 6;
constexpr GLuint BIND_METRIC_MASS = 7;
constexpr GLuint BIND_METRIC_CELL_INFO = 8;
constexpr GLuint BIND_METRIC_CELLS = 9;
constexpr GLuint BIND_METRIC_GANGWAY = 18;   // the per-agent gangway state (seated venues)

} // namespace swarm
