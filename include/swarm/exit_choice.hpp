#pragma once

// Exit choice on analytic venues. Two modes:
// NEAREST ("nearest"): e_goal follows the nearest-exit field (swarm/nav_field.hpp).
//   QUEUE-AWARE ("queue-aware"): every agent holds an assigned exit and steers towards it on that exit's own field, with the same
// anchor-based direction and wall handling as the nearest-exit field (physics.comp navChoiceGoal / choiceGoal below). It estimates its time
//     to leave through each candidate exit e of its cell,
//         E_e(x) = d_e(x) / V0 + A_e(x) / (w_e J)        (seconds; sim_params.hpp "Exit choice"),
// d_e the walking distance to e (the per-exit field's value at the cell's centre), A_e(x) the QUEUE AHEAD:
// the active agents assigned to e by the previous step's choice pass whose own distance to e lies in a nearer distance bin
// (CHOICE_AHEAD_SHIFT: 0.49 m) than d_e(x) (integer histograms and prefix sums), w_e the clear width and J = EXIT_FLOW_P_M_MIN.
// Counting every agent assigned to e instead would show an agent walking out through an avenue the whole avenue's
// queue behind it: `nav_probe excluded` found agents in venue M's avenues for whom a door 50 m back looked 20 s faster.
// Q_e (every assigned agent) still sets the switch cap.
//
// THE CHOICE PASS (physics.comp PHYSICS_PASS 0, at the start of a step's physics; CpuCrowdSim::chooseExits), per active
// agent from the start-of-step position, on the counts of the previous step:
// its CELL: the navigation grid cell containing it, or for a NOFIT cell its nearest FIT neighbour; a cell
// without any path keeps the assignment (e_goal 0 there);
//   EVALUATE (evaluation steps: every CHOICE_STEPS steps = T_CHOICE of simulated time, all agents on the same counts): an agent whose
//     assigned exit is a candidate of its cell is ELIGIBLE to switch to its best candidate if that gains more than both hysteresis
//     margins, max(CHOICE_REL_MARGIN E_current, CHOICE_ABS_MARGIN_S); its gain goes into its exit's histogram (1 s bins);
//   THRESHOLDS: per exit e, the lowest gain bin such that the eligible agents in it and above number at most the SWITCH CAP
//     max(CHOICE_MIN_SWITCHES, CHOICE_SWITCH_SHARE Q_e) (if the highest bin alone exceeds it, that bin);
//   APPLY (every step): a FORCED choice if the assigned exit is not a candidate of the agent's cell (or it has none yet: the first step)
//     -- the candidate with the least E, no margins, no cap: every agent always holds an exit it can steer to; else on an evaluation
//     step the agent's pending switch if its gain bin reaches its exit's threshold; then its count for the next step.
// Why simultaneous evaluation with a cap of the largest gains: the gain is monotonic along a row and
// along a gangway (moving one row up the gangway shortens the walk to the door above and lengthens the walk to the avenue below by the
// same amount), so the agents that switch are the ones at the current split between two exits' catchments, and two exits' flows do
// not cross in a single-file row or a 1.2 m gangway. All agents switching at once on one count vector would swing the crowd between
// the doors and the avenues (at t = 3 s every door queue looks 194 s long against empty avenues); staggered per-agent decisions
// interleave door- and avenue-bound agents in the rows and gangways, whose counterflows gridlock.
//
// CANDIDATES AND MEMORY (the per-exit fields). A field per exit at the navigation grid's full resolution costs cells x exits x 8
// bytes: venue S 1.56 M cells x 12 = 150 MB, venue L 16.0 M cells x 48 exits = 6.1 GB. The table keeps, per cell,
// CHOICE_K = 24 CANDIDATES: the 2 nearest avenues and the nearest concourse door (the TYPE RULE, CHOICE_TYPE_MIN;
// Geometry::exitType), then the nearest other exits by walking distance, in ascending distance. COMPACT: candidates are stored only for
// the reachable FIT cells (choiceCell returns no other: a NOFIT cell takes the nearest FIT cell with candidates of its 3 x 3 ring, else of
// the 5 x 5 ring's outer cells); ChoiceTable::index maps every grid cell to its entry (and holds its class). Each candidate: the anchor of its own exact field and its distance in 16 bits
// (CHOICE_DIST_QUANTUM = 2^-12 model units = 7.6 mm, dequantized exactly: q x 2^-12): 144 bytes per entry plus 4 bytes per grid cell (the
// index): venue S 101 MB, M 418 MB, L 904 MB (MB = 2^20 bytes; budget 1 GB = 1024 MB). Why the type rule: the 4 nearest exits hold no avenue in any seat's cell of venue M (7 doors
// per quadrant lie nearer), so the avenues would never be evaluated or used; `nav_probe excluded` measures, during an evacuation,
// the agents for whom an exit outside their candidates has a lower E than every candidate (results/validation/navigation). An agent chooses
// among its cell's candidates.
// Anchors are cell indices (25 bits: at most 2^25 = 33.5 M cells, a 5792^2 grid), exit ids 6 bits (at most 63 exits).
// Built on the CPU when the venue is first used in queue-aware mode (each exit's Lazy Theta* search, nav::lazyThetaStar from that
// exit's region alone, in parallel over exits; merged in exit order: deterministic) and cached beside the navigation field
// (`nav_<venue>_choice_<key>.bin`, keyed by the navigation field's key, CHOICE_VERSION and CHOICE_K; checksummed).

#include <swarm/gpu_types.hpp>
#include <swarm/nav_field.hpp>
#include <swarm/sim_params.hpp>

#include <glm/glm.hpp>

#include <cstdint>
#include <filesystem>
#include <limits>
#include <string>
#include <vector>

namespace swarm {

struct Venue;
struct SeatedLayout;

enum class ExitChoice { Nearest, QueueAware };
const char* exitChoiceName(ExitChoice c);              // "nearest" | "queue-aware"
ExitChoice exitChoiceByName(const std::string& name);  // throws std::invalid_argument otherwise
// The stair spacing on the gangway inclines (sim_params.hpp "Stair spacing"): off (the level headway time gap
// on the inclines too), EMPIRICAL (the default: calibrated to Burghardt et al. 2013's measured stair flows) or CONSERVATIVE (the Green
// Guide's planning rate)
enum class StairFlow { Off, Empirical, Conservative };
const char* stairFlowName(StairFlow s);               // "off" | "empirical" | "conservative"
StairFlow stairFlowByName(const std::string& name);   // throws std::invalid_argument otherwise
// The set's headway time gaps on a full-slope incline, model time: {ascending, descending} (Off: T_HEADWAY both)
glm::vec2 stairHeadwayTimes(StairFlow s);

// The model options of an analytic venue. The terrace ignores them: its programs (hand router, level speed) are
// unchanged whatever is set.
struct ModelOptions {
    ExitChoice exitChoice = ExitChoice::Nearest;
    bool inclineSpeed = false;   // the free speed on the gangway inclines by the slope along the travel direction
    StairFlow stairFlow = StairFlow::Off;   // the headway time gap on the gangway inclines (only with inclineSpeed: the stair model)
    bool operator==(const ModelOptions& o) const {
        return exitChoice == o.exitChoice && inclineSpeed == o.inclineSpeed && stairFlow == o.stairFlow;
    }
    bool operator!=(const ModelOptions& o) const { return !(*this == o); }
};
// The defaults: an analytic venue's (see the definition for the stage that set them); the terrace: {Nearest, false, Off}
ModelOptions defaultModelOptions(const Venue& v);
// The options in effect: the terrace's are always {Nearest, false, Off}; without the incline speed the stair spacing is off (the
// stair model is the two together; its slope is the incline speed's)
ModelOptions effectiveModelOptions(const Venue& v, const ModelOptions& o);
// "nearest exit, level speed" style label (reports, the viewer)
std::string modelOptionsLabel(const Venue& v, const ModelOptions& o);
// The extra preamble of a venue's compute programs for these options (empty for the terrace and for an analytic venue's
// {Nearest, false}). Queue-aware: the candidate table's grid and the exits' capacities (choicePreambleDefines).
std::string modelPreamble(const Venue& v, const ModelOptions& o);

namespace nav {

constexpr int CHOICE_K = 24;                       // candidates per cell (GpuNavChoiceCell::slot)
constexpr int CHOICE_DIST_WORDS = 12;              // GpuNavChoiceCell::dist: CHOICE_K 16-bit distances
constexpr uint32_t CHOICE_INDEX_FIT = 0x80000000u; // ChoiceTable::index: the cell's class (FIT)
constexpr uint32_t CHOICE_INDEX_MASK = 0x7FFFFFFFu;   // ChoiceTable::index: the cell's entry + 1 (0: the cell has no candidates)
constexpr float CHOICE_DIST_QUANTUM = 1.0f / 4096.0f;   // a venue's candidate distance quantum, model units (2^-12 = 7.6 mm: q x quantum is exact);
                                                         // other geometries: the power of two nearest below 7.6 mm in their unit (ChoiceTable::distQuantum)
// THE TYPE RULE: per exit type (Geometry::exitType: a seated venue's 0 avenues, 1 concourse doors) the nearest
// CHOICE_TYPE_MIN[type] exits of that type are always candidates, the other slots go to the nearest exits. Two avenues: a quadrant's
// rows lie between two avenues, both reached along the walkway; with one, `nav_probe excluded` finds M's agents for whom the other
// avenue beats all candidates
constexpr int CHOICE_TYPE_MIN[2] = { 2, 1 };
constexpr int CHOICE_TYPE_MIN_MAX = 2;
constexpr uint32_t CHOICE_DIST_EMPTY = 0xFFFFu;    // the distance of an empty slot (+infinity)
constexpr int CHOICE_EXIT_SHIFT = 25;
constexpr uint32_t CHOICE_ANCHOR_MASK = (1u << CHOICE_EXIT_SHIFT) - 1u;
constexpr uint32_t CHOICE_EMPTY = 63u;             // the exit id of an empty slot
constexpr uint32_t CHOICE_FIT = 0x80000000u;       // the cell's class (FIT), in every slot
constexpr int CHOICE_MAX_EXITS = 63;               // exit ids 0 .. 62
constexpr int CHOICE_QUEUE_STRIDE = 64;            // GpuChoiceCounters::queue[parity * 64 + exit]
constexpr uint32_t CHOICE_NONE = 0xFFFFFFFFu;      // an agent's assigned exit before its first choice
constexpr uint32_t CHOICE_VERSION = 6;             // the table's algorithm version (part of the cache key)
constexpr int CHOICE_AHEAD_BINS = 1024;            // the queue ahead's distance bins per exit (GpuChoiceWork::ahead)
constexpr int CHOICE_AHEAD_SHIFT = 6;              // bin = distance quanta >> 6: 64 x 2^-12 = 2^-6 model units = 0.49 m (the last bin: 500 m on)
static_assert(CHOICE_AHEAD_BINS * CHOICE_QUEUE_STRIDE * 2 == int(sizeof(GpuChoiceWork::ahead) / 4), "ahead layout");
static_assert(CHOICE_MAX_EXITS < CHOICE_QUEUE_STRIDE && 2 * CHOICE_QUEUE_STRIDE == int(sizeof(GpuChoiceCounters::queue) / 4), "counter layout");

inline uint32_t slotExit(uint32_t slot) { return (slot >> CHOICE_EXIT_SHIFT) & 63u; }
inline uint32_t slotAnchor(uint32_t slot) { return slot & CHOICE_ANCHOR_MASK; }
// Candidate k's distance in quanta (16 bits; slotDist below: in the table's units)
inline uint32_t slotDistQ(const GpuNavChoiceCell& c, int k) { return (c.dist[k >> 1] >> ((k & 1) * 16)) & 0xFFFFu; }
// The queue ahead's bin of a distance of q quanta (physics.comp navAheadBin), and the queue ahead of an exit at that distance from the
// prefix sums of the read parity (ahead + exit x CHOICE_AHEAD_BINS + bin)
inline uint32_t aheadBin(uint32_t q) { return std::min(q >> CHOICE_AHEAD_SHIFT, uint32_t(CHOICE_AHEAD_BINS - 1)); }
inline uint32_t aheadOf(const uint32_t* ahead, uint32_t exit, uint32_t q) { return ahead[size_t(exit) * CHOICE_AHEAD_BINS + aheadBin(q)]; }

// One exit's own field: the search from its region alone (dist in grid units, float; INFINITY: no path; anchor -1: none)
struct ExitField {
    std::vector<float> dist;
    std::vector<int32_t> anchor;
};
ExitField buildExitField(const Field& grid, int exit);

struct ChoiceTable {
    Grid grid;
    int exitCount = 0;
    std::vector<std::string> exitNames;
    std::vector<double> exitWidthM;     // clear widths (Geometry::exitWidthM)
    std::vector<float> invCapS;         // 60 / (w_e J): seconds per queued person (float, emitted as NAV_EXIT_INV_CAP)
    float secondsPerUnit = 0.0f;        // seconds per grid unit of walking at V0 (a venue: CHOICE_S_PER_UNIT)
    std::vector<uint32_t> index;             // per grid cell CHOICE_INDEX_FIT (its class) | its entry + 1 (0: no candidates)
    std::vector<GpuNavChoiceCell> entries;   // the candidates of the cells that have them (compact, in grid order)
    uint64_t key = 0;                   // the cache key (0: not a venue table)
    bool fromCache = false;
    double buildSeconds = 0.0;          // the build (the searches), or loading it from the cache
    long long typeSwaps = 0;            // cells whose candidates the type rule changed (a fresh build)
    float maxDist = 0.0f;               // the largest candidate distance stored (model units; a fresh build)
    const SeatedLayout* surface = nullptr;   // a venue's table (choiceForVenue): choiceCell's surface rule (nav::surfaceReaches)
    float distQuantum = CHOICE_DIST_QUANTUM;   // the distances' quantum in the table's units (setChoiceCapacities; a power of two)
    size_t cellCount() const { return index.size(); }
    bool fit(size_t i) const { return (index[i] & CHOICE_INDEX_FIT) != 0u; }
    bool reachable(size_t i) const { return (index[i] & CHOICE_INDEX_MASK) != 0u; }   // the cell has candidates
    const GpuNavChoiceCell& at(size_t i) const;   // grid cell i's candidates (a cell of empty slots without)
    int candidates(size_t i) const;     // non-empty slots
    size_t bytes() const { return index.size() * 4 + entries.size() * sizeof(GpuNavChoiceCell); }
};

// The table of a geometry from its navigation grid (buildGrid or build: cls, out, exitRegion): every exit's own field, merged into
// each cell's CHOICE_K nearest (ascending distance, ties: the lower exit id); then the TYPE RULE (geometries
// with two exit types, Geometry::exitType: a seated venue's avenues and doors): the CHOICE_TYPE_MIN[type] nearest exits of each type
// first, then the nearest others, in ascending distance (ties: the lower exit id). Distances are rounded
// to the nearest CHOICE_DIST_QUANTUM (throws if one exceeds the 16-bit range, 16 model units). allFields (optional): every exit's
// field (diagnostics).
ChoiceTable buildChoiceTable(const Geometry& g, const Field& grid, std::vector<ExitField>* allFields = nullptr);
// Candidate k's distance in the table's units (physics.comp navSlotDist): its quantum count times the table's distQuantum (exact in float);
// +infinity for an empty slot
inline float slotDist(const ChoiceTable& t, const GpuNavChoiceCell& c, int k) {
    const uint32_t q = slotDistQ(c, k);
    return q == CHOICE_DIST_EMPTY ? std::numeric_limits<float>::infinity() : float(q) * t.distQuantum;
}
// The capacity terms of a table's exits from its widths: invCapS and secondsPerUnit (buildChoiceTable and load call it); the
// distance quantum (CHOICE_DIST_QUANTUM for a venue; the power of two nearest below 7.6 mm in another geometry's unit)
void setChoiceCapacities(ChoiceTable& t, double metresPerUnit);

// The venue's table: computed once per process (thread-safe), from the cache file if one matches, else built and saved
const ChoiceTable& choiceForVenue(const Venue& v);
uint64_t choiceCacheKey(const Venue& v);
std::filesystem::path choiceCacheFile(const Venue& v);
bool saveChoice(const ChoiceTable& t, const std::filesystem::path& file);
bool loadChoice(ChoiceTable& t, const std::filesystem::path& file, uint64_t expectedKey, double metresPerUnit);
// How many entries the venue's table has, without loading or building it (the GPU capability check): the count in the header of its
// cache file if one matches (exact), else an upper bound (the occupiable floor's cells: entries exist for reachable FIT cells only;
// test_gpu checks the bound on every venue)
struct ChoiceEntryCount {
    uint64_t entries = 0;
    bool exact = false;
};
ChoiceEntryCount choiceEntryCountBeforeBuild(const Venue& v);
uint64_t choiceEntryUpperBound(const Venue& v);
uint64_t choiceContentHash(const ChoiceTable& t);   // FNV-1a over the cells (cached and fresh tables are compared by it)

// The queue-aware preamble's defines: VENUE_EXIT_CHOICE, NAV_CELL, NAV_EXITS, the slot layout, NAV_CHOICE_S_PER_UNIT, T_CHOICE,
// the margins and NAV_EXIT_INV_CAP[NAV_EXITS]
std::string choicePreambleDefines(const ChoiceTable& t);

// --- The CPU mirror of physics.comp's queue-aware functions (the same float operations) ---
// The cell whose candidates apply at x (physics.comp navChoiceCell): nav::directionCell's rule on the table's FIT bits
int choiceCell(const ChoiceTable& t, glm::vec2 x);
// The centre of anchor cell a: NAV_ORIGIN + (index + 0.5) NAV_CELL in float (physics.comp navAnchorCentre)
glm::vec2 anchorCentre(const ChoiceTable& t, uint32_t a);
// The unit vector from x towards the anchor of exit 'exit' in x's choice cell (0 within GOAL_DEADZONE, or if exit is no candidate
// there; physics.comp navChoiceDirection)
glm::vec2 choiceDirection(const ChoiceTable& t, glm::vec2 x, uint32_t exit);
// e_goal of an agent centred at p assigned to 'exit' (physics.comp navChoiceGoal): choiceDirection without its component into a
// wall or step face beside the agent, renormalized (nav::goal's rule)
glm::vec2 choiceGoal(const ChoiceTable& t, const SeatedLayout& L, glm::vec3 p, uint32_t exit);
// E in seconds (physics.comp navEstimate): dist x secondsPerUnit + queued x invCapS[exit], each product rounded, then the sum
float estimatedTime(const ChoiceTable& t, float dist, uint32_t exit, uint32_t queued);
// Whether choice step 'step' is an evaluation step (physics.comp: step > 0 and step mod CHOICE_STEPS == 0)
inline bool evaluationStep(uint32_t step, int choiceSteps) { return step > 0u && step % uint32_t(choiceSteps) == 0u; }
// The slot of 'exit' among cell c's candidates (-1: none; physics.comp navSlotOf)
int slotOf(const GpuNavChoiceCell& c, uint32_t exit);
// The exclusive prefix sums of one parity's queue-ahead histograms (CHOICE_QUEUE_STRIDE x CHOICE_AHEAD_BINS; the prefix stage's result)
std::vector<uint32_t> aheadPrefixOf(const uint32_t* raw);
// The candidate with the least E on the queues ahead (ahead: the read parity's prefix sums, exit x CHOICE_AHEAD_BINS + bin; the first
// of equal ones: the nearer): its slot (physics.comp navBest)
int bestCandidate(const ChoiceTable& t, const GpuNavChoiceCell& c, const uint32_t* ahead, float& eBest);
// The evaluate stage (physics.comp u_choiceStage 1) of one agent at p assigned to 'current', on an evaluation step (ahead: as above)
struct Evaluation {
    bool evaluated = false;   // its exit is a candidate of its cell: its candidates' E were compared
    bool eligible = false;    // the best candidate gains more than both margins: a pending switch
    uint32_t best = CHOICE_NONE, bin = 0;   // the pending switch's exit and gain bin (uint(gain s), at most CHOICE_GAIN_BINS - 1)
    float gain = 0.0f;        // E_current - E_best, seconds (diagnostics)
};
Evaluation evaluate(const ChoiceTable& t, glm::vec3 p, uint32_t current, const uint32_t* ahead);
// The thresholds stage (physics.comp u_choiceStage 2), one exit's threshold: from its histogram (CHOICE_GAIN_BINS counts) and its count Q_e,
// the lowest bin that switches (CHOICE_GAIN_BINS: none)
uint32_t switchThreshold(const uint32_t* hist, uint32_t queued);
// The apply stage (physics.comp u_choiceStage 0) of one agent: its exit for this step; pending: its evaluate result on an evaluation step
// (nullptr otherwise), threshold: the per-exit thresholds of that step
struct Applied {
    uint32_t exit = CHOICE_NONE;
    bool switched = false;    // its pending switch was applied
    bool forced = false;      // the assigned exit was no candidate of its cell (not counted for the first choice)
};
Applied apply(const ChoiceTable& t, glm::vec3 p, uint32_t current, const uint32_t* ahead, const Evaluation* pending, const uint32_t* threshold);
// The whole choice pass over a state (CpuCrowdSim::chooseExits; tests): assigned exits, counters (both parities) and the step
// counter, as CrowdSim keeps them; work: the histograms (CHOICE_MAX_EXITS x CHOICE_GAIN_BINS) and the thresholds; ahead, the
// queue ahead's histograms (GpuChoiceWork::ahead's layout: the prefix stage at the start of a step turns the read parity into prefix sums)
struct ChoiceState {
    std::vector<uint32_t> assign;
    GpuChoiceCounters counters{};
    uint32_t step = 0;
    std::vector<Evaluation> pending;
    std::vector<uint32_t> hist, threshold;
    std::vector<uint32_t> ahead;
    void reset(size_t agents);
    const uint32_t* aheadRead() const { return ahead.data() + size_t(step & 1u) * CHOICE_QUEUE_STRIDE * CHOICE_AHEAD_BINS; }
    // Before a step: the prefix sums its choice pass will read (the read parity's histograms, prefixed; tools and tests)
    std::vector<uint32_t> aheadPrefix() const { return aheadPrefixOf(aheadRead()); }
};
// threads > 1 runs the evaluate and apply stages over the agents in parallel (OpenMP): every agent's evaluation and applied
// exit depend only on the step's input, and the shared counts are integer sums (atomic increments, reductions), so the result is the
// sequential one bit for bit (the GPU's atomics give the same integers too). threads <= 1: sequential, in agent order.
void choiceStep(const ChoiceTable& t, const std::vector<GpuBoid>& state, ChoiceState& s, int choiceSteps, int threads = 1);

} // namespace nav
} // namespace swarm
