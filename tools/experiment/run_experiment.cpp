// run_experiment: headless evacuation experiment with the safety metrics, in real units.
//
//   run_experiment --n N [--seed S] [--spawn bleacher] [--max-steps M] [--every K] [--name NAME]
//                  [--note "text"] [--out out/results/experiments] [--peak-window-s 10]
//
// Spawns N agents (spawnBleacherCrowd(N, seed), N a power of two >= 256), steps the GPU pipeline with
// CrowdMetrics after every step until every agent has left or M steps, and reads back every K steps (a
// headless tool: readbacks are allowed; the application never does this). Writes
// <out>/<name>_<yyyymmdd_hhmm>/:
//   timeseries.csv  per readback: step, t_model, t_real_s, active, cumulative evacuated per exit, max density
//                   per zone (persons/m^2 over the zone's included cells, that step);
//   heatmap.csv     per included floor cell: x_m, y_m (centre), zone, walkable_m2, peak density, time at or above
//                   each threshold [s], occupied time [s], mean speed when occupied [m/s], exposure [person-s],
//                   person-seconds spent in the cell;
//   summary.md / summary.json: t50 / t90 / t100 [s]; per exit its clear width [m] (measured from the SDF) and the
//                   mean and peak specific flow [persons per metre per minute]; per zone peak density, time at or
//                   above each threshold, exposure; the top 10 hotspot cells; tread-row changes that bypass the
//                   aisles (INV-row); N, venue, commit and dirty flag;
//   crossings.csv   the first 2000 row changes counted (only if there are any).
// Every output row (timeseries.csv, heatmap.csv, crossings.csv) and the summaries carry the venue's capacity
// label for N (swarm/venue_capacity.hpp: within / above the design capacity, or physically impossible above the jam
// capacity); above the design capacity the run prints a warning. No N is refused.
// Seated venues and the CPU reference.
//   --venue S [--load L] [--seed S]: venue S, round(L x seats) seats occupied (spawnSeatedCrowd, seeded), the agents routed by the
//       navigation field; N = the smallest power of two >= the seated agents; exits: the 4 avenue ends and the 8 concourse
//       doors; the zone 'walkway' is split into the walkway and the rear concourse in the report.
//   --engine gpu|cpu [--threads T] [--sort counting|bitonic]: the GPU pipeline (default) or the CPU reference (CpuCrowdSim with
//       the metrics' CPU reference, MetricsReference: the same integer arithmetic).
// --dt-div k (GPU): the step DT / k (a shader variant, as test_gpu validation.dt_convergence_terrace); times in real seconds of the shorter step.
// --exit-choice nearest|queue-aware and --incline-speed 0|1 (an analytic venue's model options, swarm/exit_choice.hpp;
//       default defaultModelOptions(venue)); the summaries name the options and count the exit choice's switches.
// --stair-flow off|empirical|conservative (the stair spacing on the gangway inclines, with the incline speed; default the venue's,
// EMPIRICAL).
// Seated venues: the headline density metrics (peak density, time above the thresholds, crush exposure, hotspots)
//       cover the CIRCULATION zones only (gangways, walkway, concourse, avenues, exits); the seat rows' clearways (zone 'tread') are
//       reported apart, labelled "single-file seat-row queue; area-normalised density not comparable with Fruin thresholds"; exit
//       utilisation: each exit's and each exit type's (door / avenue) share of the evacuated, the share of its nominal capacity used
//       (evacuated / (width x J x t100), J = EXIT_FLOW_P_M_MIN) and the unused exit width (the exits nobody used, share of the total
//       width). heatmap.csv gets a column 'scope' (circulation | seat_row | other).
//   --checks 0|1 (default 1 on a seated venue): after every step the plausibility checks (tools/plausibility.hpp Monitor; an
//       analytic venue with NO exemption) and the venue's per-step checks (tools/venue_s.hpp Checker: INV-row row changes, wall
//       tops, tunnelling, the step-up rules, fence crossings); summary.md / .json get a Checks section with PASS / FAIL.
// --venue M | L (generated venues: their metric grids, doors at every gangway head); per-gangway utilisation (seated
//       venues, from the metric counters: the agents that stood on each gangway, and the evacuated agents whose last gangway it was).
// --load L > 1 (seated venues): OVERCROWDING, every seat filled plus round((L - 1) x seats) people standing on the walkway
//       and the rear concourse (spawnOvercrowdedCrowd: seeded uniform placement without overlap, at most OVERCROWD_STANDING_MAX_P_M2
//       initially; a load the floor cannot take is reduced to the achievable maximum, reported); --standing gangways: also on the
//       gangways (the blocked-aisles variant). The summaries report the spawn (seated, standing per area, the achievable load) and the
//       initial densities (the metric's own cloud-in-cell deposit of the spawn).
// --stall-dump-s T (seated venues; default 0, off): stall snapshots stall_<step>.csv, the active agents' place, row, gangway,
//       velocity, e_goal and assigned exit whenever no agent has left for T, 2T, 4T, ... s (counted from the last evacuation, after the
//       first one). Diagnostics only: the state is read, never written.
// Definitions are in summary.md and in swarm/metrics.hpp. Run it from the repository root.
#include "../benchmark/bench_common.hpp"
#include "../plausibility.hpp"
#include "../venue_s.hpp"

#include <swarm/assets.hpp>
#include <swarm/cpu_crowd_sim.hpp>
#include <swarm/crowd_sim.hpp>
#include <swarm/exit_choice.hpp>
#include <swarm/metrics.hpp>
#include <swarm/nav_field.hpp>
#include <swarm/sdf.hpp>
#include <swarm/venue.hpp>
#include <swarm/venue_capacity.hpp>

#include <memory>

#include <cstdlib>
#include <iomanip>
#include <limits>

namespace fs = std::filesystem;
using namespace swarm;
namespace mt = swarm::metrics;

namespace {

struct Options {
    int n = 4096;
    unsigned seed = 1337;          // spawnBleacherCrowd's default
    std::string spawn = "bleacher";
    int maxSteps = 6000;
    int every = 1;                 // readback interval K (steps)
    std::string name;
    std::string note;
    fs::path out = "out/results/experiments";
    double peakWindowS = 10.0;     // sliding window of the peak flow
    std::string venue = "terrace"; // terrace | S | M | L
    double load = 1.0;             // seated venues: the share of seats occupied
    std::string engine = "gpu";    // gpu | cpu (the CPU reference)
    int threads = 0;               // cpu: OpenMP threads (0: all)
    std::string sort = "counting"; // cpu: counting | bitonic
    int dtDiv = 1;                 // gpu: DT / dtDiv
    int checks = -1;               // per-step checks: -1 auto (on for a seated venue), 0 off, 1 on
    std::string exitChoice;        // nearest | queue-aware ("": the venue's default)
    int inclineSpeed = -1;         // 0 | 1 (-1: the venue's default)
    std::string stairFlow;         // off | empirical | conservative ("": the venue's default)
    std::string standing = "circulation";   // circulation | gangways (overcrowding: where the extra people stand)
    double stallDumpS = 0.0;       // stall snapshots after T, 2T, 4T, ... s without an evacuation (0: off)
};

StandingAreas standingAreasByName(const std::string& s) {
    if (s == "circulation") return StandingAreas::Circulation;
    if (s == "gangways") return StandingAreas::WithGangways;
    throw std::runtime_error("--standing circulation | gangways");
}

// Tread rows (INV-row check): rows are the stand's treads, ROW_RISE apart (crowd_sim.cpp TREADS: 0.0176 per
// row, the back platform is row 8). An agent in the TREAD zone whose centre is within ROW_TOLERANCE rises of a
// row's rest height (row k: k * ROW_RISE + BODY_RADIUS) is on that row; between rows it is airborne or
// stepping and keeps its last row. Outside the TREAD zone (aisle, walkway, ...) it has left its row properly.
constexpr float ROW_RISE = 0.0176f;
constexpr float ROW_TOLERANCE = 0.3f;
constexpr int OFF_ROWS = -2, BETWEEN_ROWS = -1;
constexpr size_t MAX_CROSSING_EVENTS = 2000;

int rowOf(const GpuBoid& b, float outerWallInnerDepth) {
    if (mt::sampleZone(glm::vec2(b.position), outerWallInnerDepth) != mt::ZONE_TREAD) return OFF_ROWS;
    const float r = (b.position.z - BODY_RADIUS) / ROW_RISE;
    const int k = int(std::lround(r));
    return std::abs(r - float(k)) <= ROW_TOLERANCE ? k : BETWEEN_ROWS;
}

// --- minimal JSON ---
std::string jstr(const std::string& s) {
    std::string o = "\"";
    for (char c : s) {
        if (c == '"' || c == '\\') { o += '\\'; o += c; }
        else if (c == '\n') o += "\\n";
        else if ((unsigned char)c < 0x20) { char b[8]; std::snprintf(b, sizeof b, "\\u%04x", c); o += b; }
        else o += c;
    }
    return o + "\"";
}
std::string jnum(double v, int prec = 6) {
    if (!std::isfinite(v)) return "null";
    std::ostringstream o;
    o << std::setprecision(prec) << v;
    return o.str();
}
std::string jint(long long v) { return std::to_string(v); }
using Fields = std::vector<std::pair<std::string, std::string>>;
std::string pad(int n) { return std::string(size_t(n), ' '); }
std::string jobj(const Fields& f, int ind) {
    if (f.empty()) return "{}";
    std::string s = "{\n";
    for (size_t i = 0; i < f.size(); ++i) s += pad(ind + 2) + jstr(f[i].first) + ": " + f[i].second + (i + 1 < f.size() ? ",\n" : "\n");
    return s + pad(ind) + "}";
}
std::string jarr(const std::vector<std::string>& v, int ind) {
    if (v.empty()) return "[]";
    std::string s = "[\n";
    for (size_t i = 0; i < v.size(); ++i) s += pad(ind + 2) + v[i] + (i + 1 < v.size() ? ",\n" : "\n");
    return s + pad(ind) + "]";
}

std::string fmt(const char* f, double v) { char b[64]; std::snprintf(b, sizeof b, f, v); return b; }

Options parse(int argc, char** argv) {
    const bench::Args a(argc, argv, 1);
    Options o;
    o.n = a.getInt("n", o.n);
    o.seed = unsigned(std::stoul(a.get("seed", std::to_string(o.seed))));
    o.spawn = a.get("spawn", o.spawn);
    o.maxSteps = a.getInt("max-steps", o.maxSteps);
    o.every = a.getInt("every", o.every);
    o.name = a.get("name", "stadium_n" + std::to_string(o.n));
    o.note = a.get("note", "");
    o.out = a.get("out", o.out.string());
    o.peakWindowS = std::stod(a.get("peak-window-s", "10"));
    o.venue = a.get("venue", o.venue);
    o.load = std::stod(a.get("load", "1"));
    o.engine = a.get("engine", o.engine);
    o.threads = a.getInt("threads", 0);
    o.sort = a.get("sort", o.sort);
    o.dtDiv = a.getInt("dt-div", 1);
    o.checks = a.getInt("checks", -1);
    o.exitChoice = a.get("exit-choice", "");
    o.inclineSpeed = a.getInt("incline-speed", -1);
    o.stairFlow = a.get("stair-flow", "");
    if (!o.stairFlow.empty()) stairFlowByName(o.stairFlow);   // validates
    o.standing = a.get("standing", o.standing);
    standingAreasByName(o.standing);   // validates
    o.stallDumpS = std::stod(a.get("stall-dump-s", "0"));
    if (!o.exitChoice.empty()) exitChoiceByName(o.exitChoice);   // validates
    const bool seated = venueByName(o.venue).seated();
    if (seated) {   // the spawn: the seats; N = the smallest power of two that holds them
        if (a.has("spawn") && a.get("spawn", "") != "seats") throw std::runtime_error("--spawn: a seated venue spawns on its seats");
        o.spawn = "seats";
        const int seats = int(seated::seats(venueByName(o.venue).layout).size());
        int m = int(std::lround(std::clamp(o.load, 0.0, 1.0) * seats));
        if (o.load > 1.0) {   // the seats and the standing crowd the floor takes
            const OvercrowdSpawn sp = spawnOvercrowdedCrowd(venueByName(o.venue), o.load, o.seed, standingAreasByName(o.standing));
            m = sp.seats + sp.standing;
        }
        if (!a.has("n")) { o.n = 256; while (o.n < m) o.n *= 2; }
        if (!a.has("name"))
            o.name = std::string("venue_") + venueByName(o.venue).name + "_load" + std::to_string(int(std::lround(o.load * 100.0))) +
                     (o.load > 1.0 && o.standing != "circulation" ? "_standing-" + o.standing : std::string()) + "_" + o.engine;
    } else if (o.spawn != "bleacher") {
        throw std::runtime_error("--spawn: only 'bleacher' (spawnBleacherCrowd) exists");
    }
    if (o.every < 1 || o.maxSteps < 1) throw std::runtime_error("--every and --max-steps must be >= 1");
    if (o.engine != "gpu" && o.engine != "cpu") throw std::runtime_error("--engine gpu | cpu");
    if (o.sort != "counting" && o.sort != "bitonic") throw std::runtime_error("--sort counting | bitonic");
    if (o.dtDiv < 1 || (o.dtDiv != 1 && o.engine != "gpu")) throw std::runtime_error("--dt-div k >= 1, GPU engine only");
    if (o.checks < 0) o.checks = seated ? 1 : 0;
    if (o.checks && o.every != 1) throw std::runtime_error("--checks needs a readback every step (--every 1)");
    if (a.has("standing") && !(seated && o.load > 1.0)) throw std::runtime_error("--standing: overcrowding only (a seated venue, --load > 1)");
    if (o.stallDumpS < 0.0 || (o.stallDumpS > 0.0 && !seated)) throw std::runtime_error("--stall-dump-s T >= 0, seated venues only");
    for (const auto& kv : a.opts)
        if (kv.first != "n" && kv.first != "seed" && kv.first != "spawn" && kv.first != "max-steps" && kv.first != "every" && kv.first != "name" &&
            kv.first != "note" && kv.first != "out" && kv.first != "peak-window-s" && kv.first != "venue" && kv.first != "load" && kv.first != "engine" &&
            kv.first != "threads" && kv.first != "sort" && kv.first != "dt-div" && kv.first != "checks" && kv.first != "exit-choice" &&
            kv.first != "incline-speed" && kv.first != "standing" && kv.first != "stair-flow" && kv.first != "stall-dump-s")
            throw std::runtime_error("unknown option --" + kv.first);
    return o;
}

// The simulation and its metrics: the GPU pipeline (CrowdSim + CrowdMetrics) or the CPU reference (CpuCrowdSim +
// MetricsReference, the same integer arithmetic as the metric shaders)
struct Engine {
    virtual ~Engine() = default;
    virtual void step() = 0;
    virtual GpuMetricCounters counters() = 0;
    virtual std::vector<GpuMetricCell> cells() = 0;
    virtual std::vector<uint32_t> evacSteps() = 0;
    virtual std::vector<GpuBoid> state() = 0;
    virtual GpuChoiceCounters choice() = 0;   // the exit choice's counters (zero unless queue-aware)
    virtual std::vector<uint32_t> assigned() = 0;   // the assigned exit per agent (empty unless queue-aware)
};

struct GpuEngine : Engine {
    CrowdSim sim;
    mt::CrowdMetrics gm;
    GLuint sdf;
    GpuEngine(const fs::path& shaderDir, int n, const Venue& v, const ModelOptions& mo, const std::vector<GpuMetricCellInfo>& info, const std::vector<GpuBoid>& spawn, GLuint sdfTex)
        : sim(shaderDir, n, v, mo), gm(shaderDir, n, info, v.seated() ? &v : nullptr), sdf(sdfTex) {
        sim.upload(spawn);
    }
    void step() override { sim.step(sdf); gm.afterStep(sim); }
    GpuMetricCounters counters() override { return gm.readCounters(); }
    std::vector<GpuMetricCell> cells() override { return gm.readCells(); }
    std::vector<uint32_t> evacSteps() override { return gm.readEvacSteps(); }
    std::vector<GpuBoid> state() override { return bench::readBuffer<GpuBoid>(sim.currentStateBuffer(), size_t(sim.numBoids())); }
    GpuChoiceCounters choice() override { return sim.readChoiceCounters(); }
    std::vector<uint32_t> assigned() override {
        return sim.assignBuffer() ? bench::readBuffer<uint32_t>(sim.assignBuffer(), size_t(sim.numBoids())) : std::vector<uint32_t>{};
    }
};

struct CpuEngine : Engine {
    CpuCrowdSim sim;
    mt::MetricsReference ref;
    CpuEngine(const Venue& v, const ModelOptions& mo, int threads, CpuCrowdSim::SortMode mode, int n, const std::vector<GpuMetricCellInfo>& info, const std::vector<GpuBoid>& spawn)
        : sim(v, mo, v.seated() ? std::vector<float>{} : sdfVolumeCPU(), threads, mode), ref(n, info, v.seated() ? &v.layout : nullptr) {
        sim.setState(spawn);
    }
    void step() override {
        const std::vector<GpuBoid> prev = sim.state();
        sim.step();
        ref.record(prev, sim.state());
    }
    GpuMetricCounters counters() override { return ref.counters; }
    std::vector<GpuMetricCell> cells() override { return ref.cells; }
    std::vector<uint32_t> evacSteps() override { return ref.evacStep; }
    std::vector<GpuBoid> state() override { return sim.state(); }
    GpuChoiceCounters choice() override { return sim.choiceCounters(); }
    std::vector<uint32_t> assigned() override { return sim.assignedExits(); }
};

// A copy of the shader directory with DT / k in physics.comp (after the preamble: the variant line follows #version, the loader
// inserts the preamble before it; test_gpu validation.dt_convergence_terrace's override)
fs::path dtVariant(const fs::path& shaderDir, int k) {
    const fs::path dir = processTempPath("swarm_shaders_runexp_dt" + std::to_string(k));
    fs::remove_all(dir);
    fs::create_directories(dir);
    for (const auto& e : fs::directory_iterator(shaderDir)) fs::copy_file(e.path(), dir / e.path().filename());
    std::string src;
    {
        std::ifstream in(dir / "physics.comp", std::ios::binary);
        std::stringstream ss;
        ss << in.rdbuf();
        src = ss.str();
    }
    char b[96];
    std::snprintf(b, sizeof b, "#undef DT\n#define DT %.9g\n", double(DT / float(k)));
    src.insert(src.find('\n') + 1, b);
    std::ofstream(dir / "physics.comp", std::ios::binary | std::ios::trunc) << src;
    return dir;
}

std::string exitColumn(int e, const SeatedLayout* L) {
    if (e < mt::EXIT_OTHER) return std::string(e % 2 ? "neg_" : "pos_") + (e < 2 ? "x" : "y");
    if (e == mt::EXIT_OTHER) return "other";
    static const char* q[4] = { "pxpy", "nxpy", "nxny", "pxny" };
    const int d = e - mt::EXIT_DOOR0;
    if (!L || L->doorsPerQuadrant() == 2) return std::string("door_") + q[d / 2] + (d % 2 ? "_xwall" : "_ywall");   // venue S's short names
    // door_<quadrant>_<ywall|xwall>_<i> | door_<quadrant>_corner
    const int dq = d % L->doorsPerQuadrant();
    if (dq == 2 * L->doors) return std::string("door_") + q[d / L->doorsPerQuadrant()] + "_corner";
    return std::string("door_") + q[d / L->doorsPerQuadrant()] + (dq < L->doors ? "_ywall_" : "_xwall_") + std::to_string(dq % L->doors);
}

// Report zones: metrics::Zone, and (seated venues) the rear concourse split off the walkway zone
constexpr int Z_CONC = mt::ZONE_COUNT, ZONES = mt::ZONE_COUNT + 1;
// Seated venues: the zones' report names and scopes. Circulation: the gangways (metric zone 'aisle'), the walkway,
// the concourse, the avenues and the exits; the seat rows' clearways (zone 'tread') are single-file queues, reported apart; the pitch
// (fenced, no floor an agent reaches) is neither
const char* SEAT_ROW_LABEL = "single-file seat-row queue; area-normalised density not comparable with Fruin thresholds";
bool circulationZone(int z) { return z == mt::ZONE_AISLE || z == mt::ZONE_WALKWAY || z == mt::ZONE_AVENUE || z == mt::ZONE_EXIT || z == Z_CONC; }
std::string seatedZoneName(int z) {
    if (z == mt::ZONE_TREAD) return "seat row";
    if (z == mt::ZONE_AISLE) return "gangway";
    if (z == Z_CONC) return "concourse";
    return mt::zoneName(uint32_t(z));
}

struct Sample {
    int step = 0;
    uint32_t active = 0;
    std::array<uint32_t, mt::EXIT_SLOTS> exits{};
    std::array<double, ZONES> zoneMax{};   // persons/m^2 (0 if no included cell in the zone has mass)
    double circulationMax = 0.0;           // over the circulation zones' cells (seated venues)
};

// Per-gangway flows of a seated venue, from the state at every readback. Each active agent's gangway
// (seated::gangwayAt, the metric counters' rule); a departure from a gangway is classified by where the agent stands next: the HEAD (the
// concourse or a door's passage), the FOOT (the walkway or an avenue) or other (another gangway: a straight gangway's flow into the corner
// gangway where they merge; a clearway: a stray); each agent's first gangway and the step it entered it (its catchment: the seats whose
// occupants walked their row to it)
struct GangwayFlow {
    const SeatedLayout* L = nullptr;
    int G = 0;
    std::vector<int16_t> cur, first, lastG;
    std::vector<int> firstStep;
    std::vector<int> steps;                                   // the readback steps
    std::vector<uint16_t> occ, outHead, outFoot, outOther;    // per readback x gangway
    void init(const SeatedLayout& l, size_t n) {
        L = &l;
        G = seated::gangwayCount(l);
        cur.assign(n, -1);
        first.assign(n, -1);
        lastG.assign(n, -1);
        firstStep.assign(n, -1);
    }
    void step(int s, const std::vector<GpuBoid>& st) {
        const size_t base = occ.size();
        for (auto* v : { &occ, &outHead, &outFoot, &outOther }) v->resize(base + size_t(G), 0);
        steps.push_back(s);
        for (size_t i = 0; i < st.size(); ++i) {
            const glm::vec4 p = st[i].position;
            const int g = p.w != 0.0f ? seated::gangwayAt(*L, glm::vec2(p)) : -1;
            const int was = cur[i];
            if (was >= 0 && g != was) {
                const venue_s::Place pl = p.w == 0.0f ? venue_s::P_LEFT : venue_s::where(*L, p).place;
                if (pl == venue_s::P_CONCOURSE || pl == venue_s::P_EXIT) ++outHead[base + size_t(was)];
                else if (pl == venue_s::P_WALKWAY || pl == venue_s::P_AVENUE) ++outFoot[base + size_t(was)];
                else ++outOther[base + size_t(was)];
            }
            if (g >= 0) {
                ++occ[base + size_t(g)];
                if (first[i] < 0) { first[i] = int16_t(g); firstStep[i] = s; }
                lastG[i] = int16_t(g);
            }
            cur[i] = int16_t(g);
        }
    }
};

int run(const Options& o) {
    const std::string started = bench::localTimestamp("%Y-%m-%dT%H:%M:%S");
    const fs::path dir = o.out / (o.name + "_" + bench::localTimestamp("%Y%m%d_%H%M"));
    bench::createHiddenContext("run_experiment");
    const Venue& sv = venueByName(o.venue);   // the simulated venue
    const bool seatedV = sv.seated();
    const GLuint sdf = seatedV ? 0 : loadSDFTexture3D(resolveAsset("stadium.sdf"));
    if (!seatedV && !sdf) throw std::runtime_error("cannot load stadium.sdf");
    const fs::path shaderBase = resolveAsset("shaders");
    const fs::path shaderDir = o.dtDiv == 1 ? shaderBase : dtVariant(shaderBase, o.dtDiv);
    std::printf("run_experiment | %s | commit %s (dirty %s) | %s | %s\n", o.name.c_str(), bench::gitCommit().c_str(), bench::gitDirty().c_str(),
                buildinfo::buildConfig(), bench::glRenderer().c_str());
    const swarm::venue::Capacity cap = swarm::venue::capacityOf(sv);

    const mt::MetricVenue venue = mt::computeMetricVenue(sv);   // on the venue's metric grid
    const int metricCells = venue.res * venue.res;
    const SeatedLayout* seatL = seatedV ? &sv.layout : nullptr;
    auto cellCentre = [&venue](int c) { return mt::cellCentreM(c, venue.res); };
    const std::vector<GpuMetricCellInfo> info = venue.cellInfo();
    // spawnOvercrowdedCrowd is spawnSeatedCrowd for a load up to 100% (the same agents and seats)
    const OvercrowdSpawn sp = seatedV ? spawnOvercrowdedCrowd(sv, o.load, o.seed, standingAreasByName(o.standing), o.n) : OvercrowdSpawn{};
    const std::vector<GpuBoid> spawn = seatedV ? sp.boids : spawnBleacherCrowd(o.n, o.seed);
    const bool overcrowded = seatedV && o.load > 1.0;
    if (overcrowded)
        std::printf("  overcrowding: %d seated + %d standing (requested %d, at most %d = %.1f p/m^2 x %.1f m^2; walkway %d, concourse %d, gangways %d)%s: load %.2f%% "
                    "(requested %.2f%%)\n", sp.seats, sp.standing, sp.standingRequested, sp.standingMax, OVERCROWD_STANDING_MAX_P_M2, sp.standingAreaM2,
                    sp.standingWalkway, sp.standingConcourse, sp.standingGangways, sp.placementExhausted ? " PLACEMENT EXHAUSTED" : "", 100.0 * sp.load,
                    100.0 * sp.requestedLoad);
    const long n0 = bench::countActive(spawn);
    // On every output row; a seated venue's label counts its seated agents (the buffer is padded with parked ones)
    const std::string capacityLabel = swarm::venue::label(seatedV ? int(n0) : o.n, cap);
    if (const std::string w = swarm::venue::warning(seatedV ? int(n0) : o.n, cap); !w.empty()) std::fprintf(stderr, "%s\n", w.c_str());
    // The model options (the venue's defaults unless given)
    ModelOptions mo = defaultModelOptions(sv);
    if (!o.exitChoice.empty()) mo.exitChoice = exitChoiceByName(o.exitChoice);
    if (o.inclineSpeed >= 0) mo.inclineSpeed = o.inclineSpeed != 0;
    if (!o.stairFlow.empty()) mo.stairFlow = stairFlowByName(o.stairFlow);
    mo = effectiveModelOptions(sv, mo);
    const std::string modelLabel = modelOptionsLabel(sv, mo);
    std::printf("  model: %s\n", modelLabel.c_str());
    std::unique_ptr<Engine> engine;
    if (o.engine == "gpu") engine = std::make_unique<GpuEngine>(shaderDir, o.n, sv, mo, info, spawn, sdf);
    else engine = std::make_unique<CpuEngine>(sv, mo, o.threads, o.sort == "bitonic" ? CpuCrowdSim::SortMode::GpuBitonic : CpuCrowdSim::SortMode::Counting, o.n, info, spawn);
    const int exitSlots = mt::exitSlotsUsed(seatL);
    const double dt = DT_REAL_S / double(o.dtDiv);
    // Per-step checks: plausibility (no exemption on an analytic venue) and the seated venue's checks
    const scene::Select sceneSel(sv);
    plausibility::Monitor monitor(spawn, seatedV ? plausibility::VenueKind::Analytic : plausibility::VenueKind::BakedTerrace);
    venue_s::Checker checker;
    std::vector<int> seatIdx;
    if (seatedV) {
        seatIdx = sp.seat;   // -1 for the standing (and parked) agents
        checker.init(sv.layout, spawn, venue_s::seatRows(sv, seatIdx));
        // The venue checker's own wall clearance (its ring test, the costliest check) duplicates the plausibility monitor's,
        // which the summaries report
        checker.wallCheck = false;
    }
    std::vector<GpuBoid> prevState = spawn;
    GangwayFlow gflow;
    if (seatedV) gflow.init(sv.layout, size_t(o.n));
    // The concourse: the report splits a seated venue's 'walkway' zone into the walkway and the rear concourse (by the cell centre)
    auto isConcourse = [&](int c) {
        if (!seatedV || venue.zone[size_t(c)] != mt::ZONE_WALKWAY) return false;
        const glm::vec2 cm = cellCentre(c);
        return seated::fold(glm::vec2(float(units::modelLength(cm.x)), float(units::modelLength(cm.y)))).y > 0.5f * (sv.layout.standFront + sv.layout.concFront);
    };
    auto zoneLabel = [&](int c) -> std::string { return isConcourse(c) ? "concourse" : mt::zoneName(venue.zone[size_t(c)]); };
    // The initial densities, the metric's own cloud-in-cell deposit of the spawn (seated venues), over cells of at least
    // PEAK_MIN_WALKABLE_M2 (the peak densities' rule): the standing zones' cells (walkway, concourse; the gangways too in the
    // gangway-standing variant) and every circulation cell
    struct InitialDensity { double standingMax = 0.0, circulationMax = 0.0, standingMean = NAN; int standingCells = 0; } init;
    if (seatedV) {
        std::vector<uint64_t> mass(size_t(metricCells), 0);
        for (const GpuBoid& b : spawn) {
            if (b.position.w == 0.0f) continue;
            const mt::CicDeposit d = mt::cicDeposit(glm::vec2(b.position), venue.res);
            for (int k = 0; k < 4; ++k) mass[size_t(d.cell[k])] += d.weight[k];
        }
        const bool gwStand = overcrowded && o.standing == "gangways";
        for (int c = 0; c < metricCells; ++c) {
            if (!venue.included[size_t(c)] || venue.walkableM2[size_t(c)] < mt::PEAK_MIN_WALKABLE_M2) continue;
            const uint32_t zc = venue.zone[size_t(c)];
            const double dens = double(mass[size_t(c)]) / mt::MASS_ONE / double(venue.walkableM2[size_t(c)]);
            const bool standingCell = zc == mt::ZONE_WALKWAY || (gwStand && zc == mt::ZONE_AISLE);   // the walkway zone holds the concourse
            if (standingCell) { init.standingMax = std::max(init.standingMax, dens); ++init.standingCells; }
            if (zc == mt::ZONE_AISLE || zc == mt::ZONE_WALKWAY || zc == mt::ZONE_AVENUE || zc == mt::ZONE_EXIT) init.circulationMax = std::max(init.circulationMax, dens);
        }
        if (overcrowded) init.standingMean = sp.standingAreaM2 > 0.0 ? double(sp.standing) / sp.standingAreaM2 : NAN;
        std::printf("  initial density (cloud-in-cell, cells >= %.1f m^2): standing zones' cells max %.2f p/m^2, circulation max %.2f p/m^2%s\n",
                    mt::PEAK_MIN_WALKABLE_M2, init.standingMax, init.circulationMax,
                    overcrowded ? (", standing crowd mean " + fmt("%.3f", init.standingMean) + " p/m^2").c_str() : "");
    }

    std::vector<Sample> samples;
    long zoneAboveSamples[ZONES][mt::THRESHOLD_COUNT] = {};
    long circAboveSamples[mt::THRESHOLD_COUNT] = {};   // samples at which any circulation cell was at or above the threshold
    std::vector<int> lastRow(size_t(o.n), BETWEEN_ROWS);
    if (!seatedV)
        for (int i = 0; i < o.n; ++i) lastRow[size_t(i)] = std::max(rowOf(spawn[size_t(i)], venue.outerWallInnerDepth), BETWEEN_ROWS);
    long rowCrossings = 0, rowDown = 0, rowMulti = 0;
    long rowByPhase[3] = {};   // steps 1-50, 51-200, after 200
    std::vector<char> crossed(size_t(o.n), 0);
    struct Crossing { int step; int agent; int from, to; glm::vec4 p; };
    std::vector<Crossing> events;

    // Stall snapshots (--stall-dump-s T, seated venues): when no agent has left for T, 2T, 4T, ... s since the last evacuation
    // (counted from the first one) while agents remain, the active agents' state is kept for stall_<step>.csv: place, row, gangway,
    // velocity, e_goal on the assigned exit's field (the nearest-exit field without a choice) and the assigned exit. Reads the state only; the
    // files are written with the others at the end (the run's folder appears when the run ends).
    int lastEvacStep = -1;
    long lastActive = n0;
    double nextDumpS = o.stallDumpS;
    std::vector<std::pair<std::string, std::string>> stallFiles;
    auto dumpStall = [&](int step, double gapS, const std::vector<GpuBoid>& st) {
        const SeatedLayout& L = sv.layout;
        const std::vector<uint32_t> asg = engine->assigned();
        const nav::ChoiceTable* ct = asg.empty() ? nullptr : &nav::choiceForVenue(sv);
        const nav::Field& nf = nav::forVenue(sv);
        std::ostringstream f;
        f << "step,t_s,gap_s,agent,x_m,y_m,z_m,lat_m,dep_m,place,row,gangway,vx_m_s,vy_m_s,speed_m_s,e_goal_x,e_goal_y,assigned_exit,assigned_exit_name\n"
          << std::setprecision(7);
        long active = 0;
        for (size_t i = 0; i < st.size(); ++i) {
            const glm::vec4 p = st[i].position;
            if (p.w == 0.0f) continue;
            ++active;
            const venue_s::Where w = venue_s::where(L, p);
            const glm::vec2 v(st[i].velocity);
            const glm::vec2 e = ct ? nav::choiceGoal(*ct, L, glm::vec3(p), asg[i]) : nav::goal(nf, L, glm::vec3(p));
            const std::string en = ct && asg[i] < ct->exitNames.size() ? ct->exitNames[asg[i]] : std::string("-");
            f << step << "," << step * dt << "," << gapS << "," << i << "," << units::metres(p.x) << "," << units::metres(p.y) << "," << units::metres(p.z) << ","
              << units::metres(w.f.x) << "," << units::metres(w.f.y) << "," << venue_s::placeName(w.place) << "," << w.row << ","
              << seated::gangwayAt(L, glm::vec2(p)) << "," << units::metresPerSecond(v.x) << "," << units::metresPerSecond(v.y) << ","
              << units::metresPerSecond(glm::length(v)) << "," << e.x << "," << e.y << "," << (ct ? std::to_string(int(asg[i])) : std::string("-")) << ","
              << en << "\n";
        }
        const std::string name = "stall_" + std::to_string(step) + ".csv";
        std::printf("  stall: step %d (%.1f s), no evacuation for %.1f s, %ld active -> %s\n", step, step * dt, gapS, active, name.c_str());
        stallFiles.emplace_back(name, f.str());
    };

    const auto t0 = bench::Clock::now();
    int stepsRun = 0;
    double msStep = 0.0, msRead = 0.0, msFlows = 0.0, msMonitor = 0.0, msChecker = 0.0;   // where the wall time goes
    for (int step = 1; step <= o.maxSteps; ++step) {
        auto tp = bench::Clock::now();
        engine->step();
        stepsRun = step;
        if (step % o.every != 0 && step != o.maxSteps) { msStep += bench::msSince(tp); continue; }
        const GpuMetricCounters ctr = engine->counters();
        msStep += bench::msSince(tp);
        tp = bench::Clock::now();
        const std::vector<GpuMetricCell> cells = engine->cells();
        const std::vector<GpuBoid> st = engine->state();
        msRead += bench::msSince(tp);
        tp = bench::Clock::now();
        if (seatedV) gflow.step(step, st);
        msFlows += bench::msSince(tp);
        if (o.checks) {
            tp = bench::Clock::now();
            monitor.step(step, st);
            msMonitor += bench::msSince(tp);
            tp = bench::Clock::now();
            if (seatedV) checker.step(step, prevState, st);
            msChecker += bench::msSince(tp);
            prevState = st;
        }
        Sample s;
        s.step = step;
        s.active = ctr.active;
        std::copy(std::begin(ctr.exits), std::end(ctr.exits), s.exits.begin());
        bool above[ZONES][mt::THRESHOLD_COUNT] = {};
        for (int c = 0; c < metricCells; ++c) {
            if (!venue.included[size_t(c)]) continue;
            const uint32_t z = isConcourse(c) ? uint32_t(Z_CONC) : venue.zone[size_t(c)];
            const uint32_t m = cells[size_t(c)].lastMass;
            if (venue.walkableM2[size_t(c)] >= mt::PEAK_MIN_WALKABLE_M2)   // peaks over cells of at least 0.5 m^2
                s.zoneMax[z] = std::max(s.zoneMax[z], double(m) / mt::MASS_ONE / double(venue.walkableM2[size_t(c)]));
            for (int k = 0; k < mt::THRESHOLD_COUNT; ++k) above[z][k] |= m >= info[size_t(c)].thresholdMass[k];
        }
        for (int z = 0; z < ZONES; ++z)
            for (int k = 0; k < mt::THRESHOLD_COUNT; ++k) zoneAboveSamples[z][k] += above[z][k];
        if (seatedV) {
            for (int k = 0; k < mt::THRESHOLD_COUNT; ++k) {
                bool any = false;
                for (int z = 0; z < ZONES; ++z) any |= circulationZone(z) && above[z][k];
                circAboveSamples[k] += any;
            }
            for (int z = 0; z < ZONES; ++z)
                if (circulationZone(z)) s.circulationMax = std::max(s.circulationMax, s.zoneMax[size_t(z)]);
        }
        for (int i = 0; i < o.n && !seatedV; ++i) {   // INV-row (the terrace): row changes that do not pass through a non-tread zone
            if (st[size_t(i)].position.w == 0.0f) continue;
            const int r = rowOf(st[size_t(i)], venue.outerWallInnerDepth);
            int& last = lastRow[size_t(i)];
            if (r == OFF_ROWS) { last = BETWEEN_ROWS; continue; }
            if (r == BETWEEN_ROWS) continue;
            if (last >= 0 && r != last) {
                ++rowCrossings;
                rowDown += r < last;
                rowMulti += std::abs(r - last) > 1;
                ++rowByPhase[step <= 50 ? 0 : step <= 200 ? 1 : 2];
                crossed[size_t(i)] = 1;
                if (events.size() < MAX_CROSSING_EVENTS) events.push_back({ step, i, last, r, st[size_t(i)].position });
            }
            last = r;
        }
        samples.push_back(s);
        if (o.stallDumpS > 0.0) {
            if (long(ctr.active) < lastActive) { lastEvacStep = step; nextDumpS = o.stallDumpS; }
            lastActive = long(ctr.active);
            const double gapS = (step - lastEvacStep) * dt;
            if (lastEvacStep >= 0 && ctr.active > 0 && gapS >= nextDumpS) { dumpStall(step, gapS, st); nextDumpS *= 2.0; }
        }
        if (ctr.active == 0) break;
    }
    const double wallS = bench::msSince(t0) / 1000.0;
    std::printf("  wall time per step: simulation + counters %.2f ms, readback %.2f ms, gangway flows %.2f ms, plausibility %.2f ms, venue checks %.2f ms\n",
                msStep / stepsRun, msRead / stepsRun, msFlows / stepsRun, msMonitor / stepsRun, msChecker / stepsRun);

    const GpuMetricCounters ctr = engine->counters();
    const std::vector<uint32_t> evac = engine->evacSteps();
    const std::vector<GpuMetricCell> cells = engine->cells();
    if (seatedV) rowCrossings = checker.rowChanges;   // INV-row on a seated venue: the venue checker's row changes
    std::printf("  %d steps in %.1f s wall; %u of %ld evacuated; %ld %s\n", stepsRun, wallS, ctr.evacuated, n0, rowCrossings,
                seatedV ? "row changes (INV-row)" : "tread-row changes bypassing the aisles");
    const plausibility::Result plaus = o.checks ? monitor.finish(cells, info) : plausibility::Result{};
    // Diagnostics of a seated venue: where the wall-clearance violations happened, where the agents still active
    // at the end stand (both by the venue checker's place)
    std::map<std::string, long> wallWhere, leftWhere;
    if (seatedV) {
        const SeatedLayout& L = sv.layout;
        auto placeOf = [&](const glm::vec4& p) {
            const venue_s::Where w = venue_s::where(L, p);
            std::string s = venue_s::placeName(w.place);
            if (w.place == venue_s::P_CLEARWAY) s += " (row " + std::to_string(w.row) + ")";
            return s;
        };
        fs::create_directories(dir);
        std::ofstream wf(dir / "wall_violations.csv");
        wf << "step,agent,x_m,y_m,z_m,clearance_m,lat_m,dep_m,place\n" << std::setprecision(7);
        for (const plausibility::Result::Sample& v : plaus.wallViolationSamples) {
            const std::string place = placeOf(glm::vec4(glm::vec3(v.p), 1.0f));
            ++wallWhere[place];
            const glm::vec2 f = seated::fold(glm::vec2(v.p));
            wf << v.step << "," << v.agent << "," << units::metres(v.p.x) << "," << units::metres(v.p.y) << "," << units::metres(v.p.z) << ","
               << units::metres(v.p.w) << "," << units::metres(f.x) << "," << units::metres(f.y) << "," << place << "\n";
        }
        const std::vector<GpuBoid> last = engine->state();
        std::ofstream rf(dir / "remaining.csv");
        rf << "agent,x_m,y_m,z_m,lat_m,dep_m,place,e_goal_x,e_goal_y,assigned_exit\n" << std::setprecision(7);
        const nav::Field& nf = nav::forVenue(sv);
        const std::vector<uint32_t> asg = engine->assigned();   // queue-aware: e_goal on the assigned exit's field
        const nav::ChoiceTable* ct = asg.empty() ? nullptr : &nav::choiceForVenue(sv);
        for (size_t i = 0; i < last.size(); ++i) {
            if (last[i].position.w == 0.0f) continue;
            const std::string place = placeOf(last[i].position);
            ++leftWhere[place];
            const glm::vec2 f = seated::fold(glm::vec2(last[i].position));
            const glm::vec2 e = ct ? nav::choiceGoal(*ct, L, glm::vec3(last[i].position), asg[i]) : nav::goal(nf, L, glm::vec3(last[i].position));
            rf << i << "," << units::metres(last[i].position.x) << "," << units::metres(last[i].position.y) << "," << units::metres(last[i].position.z) << ","
               << units::metres(f.x) << "," << units::metres(f.y) << "," << place << "," << e.x << "," << e.y << ","
               << (ct ? std::to_string(int(asg[i])) : std::string("-")) << "\n";
        }
        for (const auto& [name, text] : stallFiles) std::ofstream(dir / name) << text;
        std::ofstream vf(dir / "venue_overlaps.csv");
        vf << "step,i,j,depth,case,place_i,place_j,xi_m,yi_m,zi_m,xj_m,yj_m,zj_m,lat_i_m,dep_i_m\n" << std::setprecision(7);
        for (const plausibility::Result::PairSample& q : plaus.venuePairSamples) {
            const glm::vec2 f = seated::fold(glm::vec2(q.pi));
            vf << q.step << "," << q.i << "," << q.j << "," << q.depth << "," << plausibility::caseName(q.kind) << "," << placeOf(q.pi) << "," << placeOf(q.pj) << ","
               << units::metres(q.pi.x) << "," << units::metres(q.pi.y) << "," << units::metres(q.pi.z) << "," << units::metres(q.pj.x) << ","
               << units::metres(q.pj.y) << "," << units::metres(q.pj.z) << "," << units::metres(f.x) << "," << units::metres(f.y) << "\n";
        }
        {   // The floor check's violations (centre below floor + BODY_RADIUS - 1e-4)
            std::ofstream ff(dir / "floor_violations.csv");
            ff << "step,agent,x_m,y_m,z_m,floor_m,centre_above_floor_m,lat_m,dep_m,place\n" << std::setprecision(7);
            for (const plausibility::Result::Sample& v : plaus.floorViolationSamples) {
                const glm::vec2 f = seated::fold(glm::vec2(v.p));
                ff << v.step << "," << v.agent << "," << units::metres(v.p.x) << "," << units::metres(v.p.y) << "," << units::metres(v.p.z) << ","
                   << units::metres(v.p.w) << "," << units::metres(v.p.z - v.p.w) << "," << units::metres(f.x) << "," << units::metres(f.y) << ","
                   << placeOf(glm::vec4(glm::vec3(v.p), 1.0f)) << "\n";
            }
        }
        for (const auto& [k, v] : wallWhere) std::printf("  wall violations (first %zu samples) at %s: %ld\n", plaus.wallViolationSamples.size(), k.c_str(), v);
        for (const auto& [k, v] : leftWhere) std::printf("  still active at the end at %s: %ld\n", k.c_str(), v);
    }

    // --- Evacuation times: t_p = the step by which ceil(p * N0) agents have left ---
    std::vector<uint32_t> left;
    for (uint32_t e : evac) if (e) left.push_back(e);
    std::sort(left.begin(), left.end());
    auto tPct = [&](double p) -> int {
        const size_t k = size_t(std::ceil(p * double(n0)));
        return k >= 1 && k <= left.size() ? int(left[k - 1]) : -1;
    };
    const int s50 = tPct(0.5), s90 = tPct(0.9), s100 = tPct(1.0);
    auto secs = [&](int s) { return s < 0 ? std::numeric_limits<double>::quiet_NaN() : s * dt; };

    // --- Exits: flows from the cumulative counters at the readbacks ---
    const int windowSteps = std::max(o.every, int(std::lround(o.peakWindowS / dt / o.every)) * o.every);
    struct ExitStat { uint32_t count = 0; int first = -1, last = -1; double meanFlow = NAN, peakFlow = NAN; int peakFrom = -1; };
    std::array<ExitStat, mt::EXIT_SLOTS> ex{};
    auto hasWidth = [&](int e) { return e < exitSlots && e != mt::EXIT_OTHER && venue.exitWidthM[size_t(e)] > 0.0f; };
    for (int e = 0; e < mt::EXIT_SLOTS; ++e) {
        ExitStat& x = ex[size_t(e)];
        x.count = ctr.exits[e];
        for (const Sample& s : samples) {
            if (x.first < 0 && s.exits[size_t(e)] > 0) x.first = s.step - o.every + 1;   // left within (previous readback, this one]
            if (x.last < 0 && x.count > 0 && s.exits[size_t(e)] == x.count) x.last = s.step;
        }
        if (!hasWidth(e) || x.count == 0) continue;
        const double widthM = venue.exitWidthM[size_t(e)];
        x.meanFlow = double(x.count) / (double(x.last - x.first + 1) * dt / 60.0) / widthM;
        // Peak: the most agents through the exit in any window of windowSteps consecutive steps (readback-aligned)
        uint32_t best = 0;
        for (size_t j = 0; j < samples.size(); ++j) {
            const int from = samples[j].step - windowSteps;   // count in (from, step]
            uint32_t before = 0;
            for (size_t q = 0; q < j && samples[q].step <= from; ++q) before = samples[q].exits[size_t(e)];
            const uint32_t inWindow = samples[j].exits[size_t(e)] - before;
            if (inWindow > best) { best = inWindow; x.peakFrom = from + 1; }
        }
        x.peakFlow = double(best) / (windowSteps * dt / 60.0) / widthM;
    }

    // --- Per-cell and per-zone aggregates ---
    struct CellOut { int c; double peak, timeAbove[3], occupied, meanSpeed, exposure, personS; };
    std::vector<CellOut> cellOut;
    struct ZoneOut { int cells = 0; double area = 0, peak = 0; int peakCell = -1; double maxCellAbove[3] = {}; double exposure = 0, personS = 0;
                     uint64_t massSteps = 0, speedSteps = 0; };
    std::array<ZoneOut, ZONES> zo{};
    double excludedPersonS = 0.0, totalPersonS = 0.0;
    for (int c = 0; c < metricCells; ++c) {
        const GpuMetricCell& g = cells[size_t(c)];
        const double personS = double(mt::sum64(g.massSteps)) / mt::MASS_ONE * dt;
        totalPersonS += personS;
        if (!venue.included[size_t(c)]) { excludedPersonS += personS; continue; }
        const double area = venue.walkableM2[size_t(c)];
        CellOut co{ c, double(g.peakMass) / mt::MASS_ONE / area, {}, g.occupiedSteps * dt,
                    mt::sum64(g.massSteps) ? double(mt::sum64(g.speedMassSteps)) / double(mt::sum64(g.massSteps)) : NAN,
                    double(mt::sum64(g.exposureMassSteps)) / mt::MASS_ONE * dt, personS };
        for (int k = 0; k < mt::THRESHOLD_COUNT; ++k) co.timeAbove[k] = g.stepsAbove[k] * dt;
        cellOut.push_back(co);
        ZoneOut& z = zo[isConcourse(c) ? size_t(Z_CONC) : size_t(venue.zone[size_t(c)])];
        ++z.cells;
        z.area += area;
        if (co.peak > z.peak && area >= mt::PEAK_MIN_WALKABLE_M2) { z.peak = co.peak; z.peakCell = c; }   // no peak from a sliver
        for (int k = 0; k < mt::THRESHOLD_COUNT; ++k) z.maxCellAbove[k] = std::max(z.maxCellAbove[k], co.timeAbove[k]);
        z.exposure += co.exposure;
        z.personS += personS;
        z.massSteps += mt::sum64(g.massSteps);
        z.speedSteps += mt::sum64(g.speedMassSteps);
    }
    auto zoneOfCell = [&](int c) { return isConcourse(c) ? int(Z_CONC) : int(venue.zone[size_t(c)]); };
    // Seated venues: the circulation zones together
    ZoneOut circ;
    if (seatedV)
        for (int z = 0; z < ZONES; ++z) {
            if (!circulationZone(z)) continue;
            const ZoneOut& q = zo[size_t(z)];
            circ.cells += q.cells;
            circ.area += q.area;
            if (q.peak > circ.peak) { circ.peak = q.peak; circ.peakCell = q.peakCell; }
            for (int k = 0; k < 3; ++k) circ.maxCellAbove[k] = std::max(circ.maxCellAbove[k], q.maxCellAbove[k]);
            circ.exposure += q.exposure;
            circ.personS += q.personS;
            circ.massSteps += q.massSteps;
            circ.speedSteps += q.speedSteps;
        }
    double circAnyAbove[3];
    for (int k = 0; k < 3; ++k) circAnyAbove[k] = circAboveSamples[k] * o.every * dt;
    auto hotOrder = [](const CellOut& a, const CellOut& b) {   // ranking: exposure, then time above LoS F, then LoS E, then peak density
        if (a.exposure != b.exposure) return a.exposure > b.exposure;
        if (a.timeAbove[1] != b.timeAbove[1]) return a.timeAbove[1] > b.timeAbove[1];
        if (a.timeAbove[0] != b.timeAbove[0]) return a.timeAbove[0] > b.timeAbove[0];
        if (a.peak != b.peak) return a.peak > b.peak;
        return a.c < b.c;
    };
    // The headline hotspots: on a seated venue the circulation cells only; its seat-row cells ranked apart
    std::vector<CellOut> hot, hotRows;
    for (const CellOut& co : cellOut) {
        if (venue.walkableM2[size_t(co.c)] < mt::PEAK_MIN_WALKABLE_M2) continue;   // hotspot lists over cells of at least 0.5 m^2
        if (!seatedV || circulationZone(zoneOfCell(co.c))) hot.push_back(co);
        else if (zoneOfCell(co.c) == mt::ZONE_TREAD) hotRows.push_back(co);
    }
    std::sort(hot.begin(), hot.end(), hotOrder);
    std::sort(hotRows.begin(), hotRows.end(), hotOrder);
    hot.resize(std::min<size_t>(10, hot.size()));
    hotRows.resize(std::min<size_t>(5, hotRows.size()));
    // Exit utilisation: shares of the evacuated, capacity used, unused width
    const double t100s = secs(s100);
    struct ExitUse { double share = NAN, capacityUsed = NAN; bool avenue = false; };
    std::array<ExitUse, mt::EXIT_SLOTS> use{};
    double typeCount[2] = {}, typeWidth[2] = {}, unusedWidth = 0.0, totalWidth = 0.0;   // [0] doors, [1] avenues (the terrace: its 4 gaps)
    for (int e = 0; e < exitSlots; ++e) {
        if (!hasWidth(e)) continue;
        ExitUse& u = use[size_t(e)];
        u.avenue = e < mt::EXIT_GAPS;
        const double w = venue.exitWidthM[size_t(e)];
        u.share = ctr.evacuated ? double(ex[size_t(e)].count) / double(ctr.evacuated) : NAN;
        u.capacityUsed = std::isfinite(t100s) ? double(ex[size_t(e)].count) / (w * double(EXIT_FLOW_P_M_MIN) / 60.0 * t100s) : NAN;
        typeCount[u.avenue] += ex[size_t(e)].count;
        typeWidth[u.avenue] += w;
        totalWidth += w;
        if (ex[size_t(e)].count == 0) unusedWidth += w;
    }
    double zoneAnyAbove[ZONES][3];
    for (int z = 0; z < ZONES; ++z)
        for (int k = 0; k < 3; ++k) zoneAnyAbove[z][k] = zoneAboveSamples[z][k] * o.every * dt;
    // Per-gangway utilisation (seated venues): from the metric counters (seated::gangwayAt ids)
    struct GangwayUse { std::string name; bool corner = false, headDoor = false; long visits = 0, last = 0; double visitShare = NAN, lastShare = NAN; };
    std::vector<GangwayUse> gangwayUse;
    long gwTypeVisits[2] = {}, gwTypeLast[2] = {};   // [0] straight, [1] corner
    if (seatedV) {
        const SeatedLayout& L = sv.layout;
        for (int g = 0; g < seated::gangwayCount(L); ++g) {
            GangwayUse u;
            u.name = seated::gangwayName(L, g);
            u.corner = g % L.gangwaysPerQuadrant() == 2 * L.gangways;
            // the head leads to a door: every head of a DoorPerGangwayHead venue; venue S: its straight gangways (its doors are centred on them)
            u.headDoor = !u.corner || L.cornerDoorLo < 1e8f;
            u.visits = long(ctr.gangwayVisits[g]);
            u.last = long(ctr.gangwayLast[g]);
            u.visitShare = n0 ? double(u.visits) / double(n0) : NAN;
            u.lastShare = ctr.evacuated ? double(u.last) / double(ctr.evacuated) : NAN;
            gwTypeVisits[u.corner] += u.visits;
            gwTypeLast[u.corner] += u.last;
            gangwayUse.push_back(u);
        }
    }


    // Flows and limits (seated venues), in windows of windowSteps steps (the peak window, 10 s)
    // from step 0. EXITS: flow per window against the exit's capacity at the exit choice's J (w J / 60 persons/s); at capacity: a window
    // at >= 80% of it. GANGWAYS: the people whose first gangway it was (its catchment), its departures (head / foot / other), the step its
    // first agent entered it and the step its last agent left it (clear); per window its outflow, its mean occupancy and its DEMAND (its
    // catchment's agents still to enter it at the window's end); LOADED: demand > 0. Its density: the mean occupancy over its floor area
    // (venue_s::gangwayAreasM2). SATURATED: loaded and its density at or above LoS F (2.17 persons/m^2): a queue waits to enter a gangway
    // that is itself full, so its own discharge limits; ENTRY-LIMITED: loaded while its density is below LoS F: the agents wait in their rows
    // although it has room, so the row merges (the clearways' single-file entries) limit. Shares of the windows of its active period (first
    // entry .. clear). Peak outflow: its largest 10 s window.
    struct GangwayFlowOut { int people = 0; long head = 0, foot = 0, other = 0; int firstIn = -1, clear = -1; double widthM = 0.0, areaM2 = 0.0,
                            meanFlowPS = NAN, peakFlowPS = NAN, loadedShare = NAN, saturatedShare = NAN, entryShare = NAN, meanDensityLoaded = NAN; };
    std::vector<GangwayFlowOut> gfo;
    struct ExitFlowOut { double capPS = NAN, meanOfCap = NAN, peakOfCap = NAN, atCapShare = NAN; };
    std::array<ExitFlowOut, mt::EXIT_SLOTS> efo{};
    int lastAgent = -1, lastAgentGangway = -1, lastAgentExit = -1, lastClearGangway = -1;
    const int flowW = windowSteps;
    if (seatedV && !gflow.steps.empty()) {
        const SeatedLayout& L = sv.layout;
        const int G = gflow.G, gpq = L.gangwaysPerQuadrant();
        const int endStep = gflow.steps.back(), nWin = (endStep + flowW - 1) / flowW;
        std::vector<std::vector<int>> entries(static_cast<size_t>(G));
        for (size_t i = 0; i < gflow.first.size(); ++i)
            if (gflow.first[i] >= 0) entries[size_t(gflow.first[i])].push_back(gflow.firstStep[i]);
        for (auto& v : entries) std::sort(v.begin(), v.end());
        // per window and gangway: departures, occupancy sum, readbacks
        std::vector<long> wOut(size_t(nWin) * size_t(G), 0), wOcc(size_t(nWin) * size_t(G), 0);
        std::vector<int> wReads(size_t(nWin), 0);
        for (size_t r = 0; r < gflow.steps.size(); ++r) {
            const int w = std::min(nWin - 1, (gflow.steps[r] - 1) / flowW);
            ++wReads[size_t(w)];
            for (int g = 0; g < G; ++g) {
                const size_t k = r * size_t(G) + size_t(g);
                wOut[size_t(w) * size_t(G) + size_t(g)] += long(gflow.outHead[k]) + gflow.outFoot[k] + gflow.outOther[k];
                wOcc[size_t(w) * size_t(G) + size_t(g)] += gflow.occ[k];
            }
        }
        fs::create_directories(dir);
        std::ofstream gcsv(dir / "gangway_flows.csv");
        gcsv << "window_start_s,window_end_s,gangway,outflow_p_s,mean_occupancy,demand,density_p_m2\n";
        gfo.assign(size_t(G), {});
        const std::vector<double> areas = venue_s::gangwayAreasM2(L, sv.domainMin, sv.domainSpan);
        double clearMax = -1.0;
        for (int g = 0; g < G; ++g) {
            GangwayFlowOut& f = gfo[size_t(g)];
            const int d = g % gpq;
            f.widthM = d == 2 * L.gangways ? sv.params.gangwayWidthM : units::metres(double(L.gwHi[size_t(d % L.gangways)]) - double(L.gwLo[size_t(d % L.gangways)]));
            f.people = int(entries[size_t(g)].size());
            f.areaM2 = areas[size_t(g)];
            for (size_t r = 0; r < gflow.steps.size(); ++r) {
                const size_t k = r * size_t(G) + size_t(g);
                f.head += gflow.outHead[k];
                f.foot += gflow.outFoot[k];
                f.other += gflow.outOther[k];
                const long out = long(gflow.outHead[k]) + gflow.outFoot[k] + gflow.outOther[k];
                if (gflow.occ[k] > 0 && f.firstIn < 0) f.firstIn = gflow.steps[r];
                if (out > 0) f.clear = gflow.steps[r];
            }
            if (f.firstIn < 0 || f.clear < 0) continue;
            const long outAll = f.head + f.foot + f.other;
            f.meanFlowPS = double(outAll) / (double(f.clear - f.firstIn + 1) * dt);
            const int w0 = (f.firstIn - 1) / flowW, w1 = std::min(nWin - 1, (f.clear - 1) / flowW);
            int windows = 0, loaded = 0, saturated = 0, entry = 0;
            double densLoaded = 0.0, peak = 0.0;
            for (int w = w0; w <= w1; ++w) {
                const double flow = double(wOut[size_t(w) * size_t(G) + size_t(g)]) / (double(flowW) * dt);
                const int wEnd = (w + 1) * flowW;
                const long demand = long(entries[size_t(g)].end() - std::upper_bound(entries[size_t(g)].begin(), entries[size_t(g)].end(), wEnd));
                const double occM = wReads[size_t(w)] ? double(wOcc[size_t(w) * size_t(G) + size_t(g)]) / wReads[size_t(w)] : 0.0;
                const double dens = f.areaM2 > 0.0 ? occM / f.areaM2 : 0.0;
                gcsv << fmt("%.2f", w * flowW * dt) << "," << fmt("%.2f", wEnd * dt) << "," << seated::gangwayName(L, g) << "," << fmt("%.4f", flow) << ","
                     << fmt("%.2f", occM) << "," << demand << "," << fmt("%.3f", dens) << "\n";
                ++windows;
                peak = std::max(peak, flow);
                if (demand > 0) {
                    ++loaded;
                    densLoaded += dens;
                    (dens >= mt::LOS_F_P_M2 ? saturated : entry)++;
                }
            }
            f.peakFlowPS = peak;
            f.meanDensityLoaded = loaded ? densLoaded / loaded : NAN;
            f.loadedShare = windows ? double(loaded) / windows : NAN;
            f.saturatedShare = windows ? double(saturated) / windows : NAN;
            f.entryShare = windows ? double(entry) / windows : NAN;
            if (f.clear * dt > clearMax) { clearMax = f.clear * dt; lastClearGangway = g; }
        }
        // the last agent out: its last gangway and its (last) assigned exit
        uint32_t lastEvac = 0;
        for (size_t i = 0; i < evac.size(); ++i)
            if (evac[i] > lastEvac) { lastEvac = evac[i]; lastAgent = int(i); }
        if (lastAgent >= 0) {
            lastAgentGangway = gflow.lastG[size_t(lastAgent)];
            const std::vector<uint32_t> asgEnd = engine->assigned();
            if (!asgEnd.empty() && asgEnd[size_t(lastAgent)] < uint32_t(seated::exitCount(L))) lastAgentExit = int(asgEnd[size_t(lastAgent)]);
        }
        // exits: per window from the cumulative counters at the readbacks
        for (int e = 0; e < exitSlots; ++e) {
            if (!hasWidth(e) || ex[size_t(e)].count == 0) continue;
            ExitFlowOut& f = efo[size_t(e)];
            f.capPS = venue.exitWidthM[size_t(e)] * double(EXIT_FLOW_P_M_MIN) / 60.0;
            const ExitStat& x = ex[size_t(e)];
            f.meanOfCap = double(x.count) / (double(x.last - x.first + 1) * dt) / f.capPS;
            f.peakOfCap = x.peakFlow * venue.exitWidthM[size_t(e)] / 60.0 / f.capPS;
            std::vector<uint32_t> cumAt(size_t(nWin) + 1, 0);
            size_t si = 0;
            uint32_t cum = 0;
            for (int w = 0; w <= nWin; ++w) {
                while (si < samples.size() && samples[si].step <= w * flowW) cum = samples[si++].exits[size_t(e)];
                cumAt[size_t(w)] = cum;
            }
            const int w0 = (x.first - 1) / flowW, w1 = std::min(nWin - 1, (x.last - 1) / flowW);
            int windows = 0, atCap = 0;
            for (int w = w0; w <= w1; ++w) {
                const double flow = double(cumAt[size_t(w) + 1] - cumAt[size_t(w)]) / (double(flowW) * dt);
                ++windows;
                atCap += flow >= 0.8 * f.capPS;
            }
            f.atCapShare = windows ? double(atCap) / windows : NAN;
        }
    }

    // --- Files ---
    fs::create_directories(dir);
    {
        std::ofstream f(dir / "timeseries.csv");
        f << "step,t_model,t_real_s,active";
        for (int e = 0; e < exitSlots; ++e) f << ",cum_evacuated_" << exitColumn(e, seatL);
        for (uint32_t z = 0; z < mt::ZONE_COUNT; ++z) f << ",max_density_" << mt::zoneName(z) << "_p_m2";
        if (seatedV) f << ",max_density_concourse_p_m2,max_density_circulation_p_m2";
        f << ",capacity_label\n" << std::setprecision(6);
        for (const Sample& s : samples) {
            f << s.step << "," << s.step * double(DT) / o.dtDiv << "," << s.step * dt << "," << s.active;
            for (int e = 0; e < exitSlots; ++e) f << "," << s.exits[size_t(e)];
            for (int z = 0; z < (seatedV ? ZONES : mt::ZONE_COUNT); ++z) f << "," << s.zoneMax[size_t(z)];
            if (seatedV) f << "," << s.circulationMax;
            f << "," << capacityLabel << "\n";
        }
    }
    {
        std::ofstream f(dir / "heatmap.csv");
        f << "ix,iy,x_m,y_m,zone,walkable_m2,peak_density_p_m2";
        for (const char* t : mt::THRESHOLD_NAMES) f << ",time_above_" << t << "_s";
        f << ",occupied_s,mean_speed_occupied_m_s,exposure_person_s,person_s" << (seatedV ? ",scope" : "") << ",capacity_label\n" << std::setprecision(6);
        for (const CellOut& co : cellOut) {
            const glm::vec2 cm = cellCentre(co.c);
            f << co.c % venue.res << "," << co.c / venue.res << "," << cm.x << "," << cm.y << "," << zoneLabel(co.c) << ","
              << venue.walkableM2[size_t(co.c)] << "," << co.peak;
            for (double t : co.timeAbove) f << "," << t;
            f << "," << co.occupied << ",";
            if (std::isfinite(co.meanSpeed)) f << co.meanSpeed;
            f << "," << co.exposure << "," << co.personS;
            if (seatedV) {
                const int z = zoneOfCell(co.c);
                f << "," << (circulationZone(z) ? "circulation" : z == mt::ZONE_TREAD ? "seat_row" : "other");
            }
            f << "," << capacityLabel << "\n";
        }
    }
    if (!events.empty()) {
        std::ofstream f(dir / "crossings.csv");
        f << "step,agent,from_row,to_row,x,y,z,x_m,y_m,capacity_label\n" << std::setprecision(7);
        for (const Crossing& c : events)
            f << c.step << "," << c.agent << "," << c.from << "," << c.to << "," << c.p.x << "," << c.p.y << "," << c.p.z << ","
              << units::metres(c.p.x) << "," << units::metres(c.p.y) << "," << capacityLabel << "\n";
    }

    const std::string commit = bench::gitCommit(), dirty = bench::gitDirty();
    const long crossingAgents = seatedV ? 0 : long(std::count(crossed.begin(), crossed.end(), 1));
    auto zoneName = [&](int z) -> std::string { return seatedV ? seatedZoneName(z) : z == Z_CONC ? "concourse" : mt::zoneName(uint32_t(z)); };
    const int zoneRows = seatedV ? ZONES : mt::ZONE_COUNT;
    // Checks: the run's verdicts
    const bool overlapOk = plaus.overlapOk() && (!seatedV || plausibility::Result::withinCrowdLimits(plaus.allStats));
    const bool plausOk = o.checks && overlapOk && plaus.gridOk() && plaus.floorOk() && plaus.fenceOk() && plaus.wallOk() && plaus.speedOk() &&
                         plaus.densityOk() && !plaus.nan;
    // INV-row binds seated venues; the baked terrace is exempt (bare treads, agents drop to the row below):
    // the verdict says so instead of failing the run
    const bool invRowOk = !seatedV || rowCrossings == 0;
    const bool stepOk = !seatedV || (checker.risesAbove == 0 && checker.verticalClimbs == 0);
    const bool topsOk = !seatedV || (checker.solidSteps == 0 && checker.tunnels == 0 && checker.fenceCrossings == 0);
    // Exit choice predicted by the navigation field (the seat's cell's exit) against the counted exits
    std::vector<long> predicted(size_t(mt::EXIT_SLOTS), 0);
    std::string navInfo;
    if (seatedV) {
        const nav::Field& nf = nav::forVenue(sv);
        for (size_t i = 0; i < spawn.size(); ++i) {
            if (spawn[i].position.w == 0.0f) continue;
            const glm::ivec2 c = nf.grid.cellOf(glm::vec2(spawn[i].position));
            const uint8_t e = nf.exitId[size_t(nf.grid.index(c.x, c.y))];
            if (e != nav::NO_EXIT) ++predicted[size_t(e < 4 ? e : e + 1)];
        }
        char b[160];
        std::snprintf(b, sizeof b, "navigation field: %.3f m cells (%d x %d), cache key %016llx, content hash %016llx", nav::CELL_M, nf.grid.res, nf.grid.res,
                      (unsigned long long)nf.key, (unsigned long long)nav::contentHash(nf));
        navInfo = b;
    }
    const bool complete = ctr.active == 0;
    const GpuChoiceCounters choiceCtr = engine->choice();

    // summary.json
    {
        Fields meta = { { "name", jstr(o.name) }, { "note", jstr(o.note) },
                        { "venue", jstr(seatedV ? std::string("venue ") + sv.name + " (analytic seated venue, navigation field)" : std::string("current stadium (stadium.sdf, stadium.obj)")) },
                        { "n", jint(o.n) }, { "capacity_label", jstr(capacityLabel) }, { "design_capacity", jint(cap.design) },
                        { "jam_capacity", jint(cap.jam) }, { "initially_active", jint(n0) }, { "spawn", jstr(o.spawn) }, { "seed", jint(o.seed) },
                        { "load", jnum(seatedV ? (overcrowded ? sp.load : o.load) : 1.0) }, { "requested_load", jnum(seatedV ? o.load : 1.0) },
                        { "engine", jstr(o.engine == "gpu" ? "gpu" : "cpu " + o.sort) },
                        { "dt_div", jint(o.dtDiv) }, { "checks", o.checks ? "true" : "false" }, { "navigation_field", jstr(navInfo) },
                        { "model", jstr(modelLabel) }, { "exit_choice", jstr(exitChoiceName(mo.exitChoice)) },
                        { "incline_speed", mo.inclineSpeed ? "true" : "false" }, { "stair_flow", jstr(stairFlowName(mo.stairFlow)) },
                        { "choice_evaluations", jint(choiceCtr.evaluations) },
                        { "choice_switches", jint(choiceCtr.switches) }, { "choice_forced", jint(choiceCtr.forced) },
                        { "max_steps", jint(o.maxSteps) }, { "readback_every_steps", jint(o.every) }, { "steps_run", jint(stepsRun) },
                        { "complete", complete ? "true" : "false" }, { "git_commit", jstr(commit) }, { "git_dirty", jstr(dirty) },
                        { "git_describe", jstr(bench::gitDescribe()) }, { "build", jstr(buildinfo::buildConfig()) },
                        { "gpu", jstr(bench::glRenderer()) }, { "driver", jstr(bench::glDriver()) }, { "started", jstr(started) },
                        { "wall_s", jnum(wallS, 4) } };
        Fields unitsF = { { "m_per_model_unit", jnum(WORLD_SCALE_M_PER_UNIT, 8) }, { "s_per_model_time_unit", jnum(TIME_SCALE_S_PER_UNIT, 8) },
                          { "dt_model", jnum(DT / float(o.dtDiv), 6) }, { "dt_real_s", jnum(dt, 8) }, { "body_radius_m", jnum(BODY_RADIUS_M) }, { "personal_radius_m", jnum(PERSONAL_RADIUS_M) }, { "gravity_m_s2", jnum(GRAVITY_M_S2) },
                          { "v_free_m_s", jnum(V_FREE_M_S) }, { "grid_cell_m", jnum(mt::CELL_M) }, { "grid_res", jint(venue.res) },
                          { "grid_min_m", jnum(mt::gridMinM(venue.res)) }, { "min_walkable_m2", jnum(mt::MIN_WALKABLE_M2) }, { "peak_min_walkable_m2", jnum(mt::PEAK_MIN_WALKABLE_M2) },
                          { "thresholds_p_m2", jobj({ { "los_e", jnum(mt::LOS_E_P_M2) }, { "los_f", jnum(mt::LOS_F_P_M2) }, { "crush", jnum(mt::CRUSH_P_M2) } }, 4) } };
        Fields evacF = { { "evacuated", jint(ctr.evacuated) }, { "remaining", jint(ctr.active) },
                         { "t50_s", jnum(secs(s50)) }, { "t90_s", jnum(secs(s90)) }, { "t100_s", jnum(secs(s100)) },
                         { "t50_step", jint(s50) }, { "t90_step", jint(s90) }, { "t100_step", jint(s100) } };
        std::vector<std::string> exits;
        for (int e = 0; e < exitSlots; ++e) {
            const ExitStat& x = ex[size_t(e)];
            Fields f = { { "exit", jstr(mt::exitName(e, seatL)) }, { "evacuated", jint(x.count) } };
            if (seatedV) f.push_back({ "nearest_exit_of_seats", jint(predicted[size_t(e)]) });
            if (hasWidth(e)) {
                f.push_back({ "width_m", jnum(venue.exitWidthM[size_t(e)], 5) });
                f.push_back({ "first_s", jnum(secs(x.first)) });
                f.push_back({ "last_s", jnum(secs(x.last)) });
                f.push_back({ "mean_flow_p_per_m_min", jnum(x.meanFlow, 5) });
                f.push_back({ "peak_flow_p_per_m_min", jnum(x.peakFlow, 5) });
                f.push_back({ "peak_window_start_s", jnum(secs(x.peakFrom - 1)) });
            }
            exits.push_back(jobj(f, 4));
        }
        std::vector<std::string> zones;
        for (int z = 0; z < zoneRows; ++z) {
            const ZoneOut& q = zo[size_t(z)];
            Fields anyAbove, maxCell;
            for (int k = 0; k < 3; ++k) {
                anyAbove.push_back({ mt::THRESHOLD_NAMES[size_t(k)], jnum(zoneAnyAbove[z][k]) });
                maxCell.push_back({ mt::THRESHOLD_NAMES[size_t(k)], jnum(q.maxCellAbove[k]) });
            }
            const glm::vec2 pc = q.peakCell >= 0 ? cellCentre(q.peakCell) : glm::vec2(NAN);
            zones.push_back(jobj({ { "zone", jstr(zoneName(z)) }, { "scope", jstr(!seatedV ? "zone" : circulationZone(z) ? "circulation" : z == mt::ZONE_TREAD ? "seat_row" : "other") },
                                   { "cells", jint(q.cells) }, { "walkable_m2", jnum(q.area, 6) },
                                   { "peak_density_p_m2", jnum(q.peak) }, { "peak_cell_x_m", jnum(pc.x) }, { "peak_cell_y_m", jnum(pc.y) },
                                   { "time_any_cell_above_s", jobj(anyAbove, 6) }, { "max_cell_time_above_s", jobj(maxCell, 6) },
                                   { "exposure_person_s", jnum(q.exposure) }, { "person_s", jnum(q.personS) },
                                   { "mean_speed_occupied_m_s", jnum(q.massSteps ? double(q.speedSteps) / double(q.massSteps) : NAN) } }, 4));
        }
        auto zoneJson = [&](const ZoneOut& q, const double* anyAboveS, const char* name, const char* label) {
            Fields anyAbove, maxCell;
            for (int k = 0; k < 3; ++k) {
                anyAbove.push_back({ mt::THRESHOLD_NAMES[size_t(k)], jnum(anyAboveS[k]) });
                maxCell.push_back({ mt::THRESHOLD_NAMES[size_t(k)], jnum(q.maxCellAbove[k]) });
            }
            const glm::vec2 pc = q.peakCell >= 0 ? cellCentre(q.peakCell) : glm::vec2(NAN);
            Fields f = { { "zones", jstr(name) }, { "cells", jint(q.cells) }, { "walkable_m2", jnum(q.area, 6) }, { "peak_density_p_m2", jnum(q.peak) },
                         { "peak_cell_x_m", jnum(pc.x) }, { "peak_cell_y_m", jnum(pc.y) }, { "time_any_cell_above_s", jobj(anyAbove, 6) },
                         { "max_cell_time_above_s", jobj(maxCell, 6) }, { "exposure_person_s", jnum(q.exposure) }, { "person_s", jnum(q.personS) },
                         { "mean_speed_occupied_m_s", jnum(q.massSteps ? double(q.speedSteps) / double(q.massSteps) : NAN) } };
            if (label) f.push_back({ "label", jstr(label) });
            return jobj(f, 2);
        };
        auto hotJson = [&](const std::vector<CellOut>& cellsIn) {
            std::vector<std::string> out;
            for (const CellOut& h : cellsIn) {
                const glm::vec2 cm = cellCentre(h.c);
                out.push_back(jobj({ { "ix", jint(h.c % venue.res) }, { "iy", jint(h.c / venue.res) }, { "x_m", jnum(cm.x) }, { "y_m", jnum(cm.y) },
                                     { "zone", jstr(zoneName(zoneOfCell(h.c))) }, { "walkable_m2", jnum(venue.walkableM2[size_t(h.c)]) },
                                     { "peak_density_p_m2", jnum(h.peak) }, { "time_above_los_e_s", jnum(h.timeAbove[0]) },
                                     { "time_above_los_f_s", jnum(h.timeAbove[1]) }, { "time_above_crush_s", jnum(h.timeAbove[2]) },
                                     { "exposure_person_s", jnum(h.exposure) }, { "mean_speed_occupied_m_s", jnum(h.meanSpeed) } }, 4));
            }
            return out;
        };
        std::vector<std::string> utilisation;
        for (int e = 0; e < exitSlots; ++e) {
            if (!hasWidth(e)) continue;
            utilisation.push_back(jobj({ { "exit", jstr(mt::exitName(e, seatL)) }, { "type", jstr(use[size_t(e)].avenue ? (seatedV ? "avenue" : "gap") : "door") },
                                         { "width_m", jnum(venue.exitWidthM[size_t(e)], 5) }, { "evacuated", jint(ex[size_t(e)].count) },
                                         { "share_of_evacuated", jnum(use[size_t(e)].share, 5) }, { "capacity_used", jnum(use[size_t(e)].capacityUsed, 5) } }, 4));
        }
        Fields utilF = { { "j_p_per_m_min", jnum(EXIT_FLOW_P_M_MIN) }, { "t100_s", jnum(t100s) }, { "exits", jarr(utilisation, 2) },
                         { "doors_evacuated", jint(long(typeCount[0])) }, { "doors_share", jnum(ctr.evacuated ? typeCount[0] / ctr.evacuated : NAN, 5) },
                         { "doors_width_m", jnum(typeWidth[0], 5) }, { "avenues_evacuated", jint(long(typeCount[1])) },
                         { "avenues_share", jnum(ctr.evacuated ? typeCount[1] / ctr.evacuated : NAN, 5) }, { "avenues_width_m", jnum(typeWidth[1], 5) },
                         { "total_width_m", jnum(totalWidth, 5) }, { "unused_exit_width_m", jnum(unusedWidth, 5) },
                         { "unused_exit_width_fraction", jnum(totalWidth > 0 ? unusedWidth / totalWidth : NAN, 5) },
                         { "capacity_used_all_exits", jnum(std::isfinite(t100s) ? double(ctr.evacuated) / (totalWidth * double(EXIT_FLOW_P_M_MIN) / 60.0 * t100s) : NAN, 5) } };
        std::vector<std::string> hotspots;
        for (const CellOut& h : hot) {
            const glm::vec2 cm = cellCentre(h.c);
            hotspots.push_back(jobj({ { "ix", jint(h.c % venue.res) }, { "iy", jint(h.c / venue.res) }, { "x_m", jnum(cm.x) }, { "y_m", jnum(cm.y) },
                                      { "zone", jstr(zoneName(zoneOfCell(h.c))) }, { "walkable_m2", jnum(venue.walkableM2[size_t(h.c)]) },
                                      { "peak_density_p_m2", jnum(h.peak) }, { "time_above_los_e_s", jnum(h.timeAbove[0]) },
                                      { "time_above_los_f_s", jnum(h.timeAbove[1]) }, { "time_above_crush_s", jnum(h.timeAbove[2]) },
                                      { "exposure_person_s", jnum(h.exposure) }, { "mean_speed_occupied_m_s", jnum(h.meanSpeed) } }, 4));
        }
        Fields rows = { { "row_changes_bypassing_aisles", jint(rowCrossings) }, { "agents", jint(crossingAgents) },
                        { "down", jint(rowDown) }, { "up", jint(rowCrossings - rowDown) }, { "more_than_one_row", jint(rowMulti) },
                        { "steps_1_50", jint(rowByPhase[0]) }, { "steps_51_200", jint(rowByPhase[1]) }, { "steps_after_200", jint(rowByPhase[2]) },
                        { "sampled_every_steps", jint(o.every) } };
        if (seatedV) rows = { { "row_changes", jint(checker.rowChanges) }, { "rows_entered_from_an_aisle", jint(checker.rowEntries) },
                              { "agent_steps_on_another_rows_clearway", jint(checker.strayRowSteps) }, { "sampled_every_steps", jint(o.every) } };
        Fields diag = { { "person_s_total", jnum(totalPersonS) }, { "person_s_in_excluded_cells", jnum(excludedPersonS) } };
        Fields checks;
        if (o.checks) {
            checks = { { "plausibility_pass", plausOk ? "true" : "false" }, { "overlap_all_pair_steps", jint(long(plaus.allStats.n)) },
                       { "overlap_all_p99", jnum(plaus.allStats.p99) }, { "overlap_all_max", jnum(plaus.allStats.max) },
                       { "overlap_crowd_p99", jnum(plaus.crowdStats.p99) }, { "overlap_crowd_max", jnum(plaus.crowdStats.max) },
                       { "overlap_venue_p99", jnum(plaus.venueStats.p99) }, { "overlap_venue_max", jnum(plaus.venueStats.max) },
                       { "grid_misses", jint(plaus.gridMisses) }, { "max_displacement", jnum(plaus.maxDisplacement) },
                       { "floor_violations", jint(plaus.floorViolations) }, { "centre_in_solid", jint(plaus.centreInSolid) },
                       { "fence_crossings", jint(plaus.fenceCrossings) }, { "fence_band", jint(plaus.fenceBand) },
                       { "wall_violations", jint(plaus.wallViolations) }, { "min_wall_clearance", jnum(plaus.minWallClearance < 1e8f ? plaus.minWallClearance : NAN) },
                       { "speed_violations", jint(plaus.speedViolations) }, { "peak_density_full_cells_p_m2", jnum(plaus.peakFull) },
                       { "density_ceiling_p_m2", jnum(plausibility::DENSITY_CEILING_P_M2) }, { "inv_row_pass", invRowOk ? "true" : "false" },
                       { "inv_row_exempt", seatedV ? "false" : "true" } };
            if (seatedV)
                for (auto kv : Fields{ { "rises_above_max_step_up", jint(checker.risesAbove) }, { "vertical_face_climbs", jint(checker.verticalClimbs) },
                                       { "max_vertical_rise_m", jnum(units::metres(checker.maxVerticalRise)) }, { "step_up_pass", stepOk ? "true" : "false" },
                                       { "agent_steps_in_a_solid_column", jint(checker.solidSteps) }, { "tunnels", jint(checker.tunnels) },
                                       { "checker_fence_crossings", jint(checker.fenceCrossings) }, { "wall_tops_pass", topsOk ? "true" : "false" } })
                    checks.push_back(kv);
        }
        // The flows and limits (summary.md's tables) for the analysis scripts
        std::vector<std::string> gangwayFlowsJ, exitFlowsJ;
        if (seatedV && !gfo.empty()) {
            const SeatedLayout& L = sv.layout;
            for (int g = 0; g < int(gfo.size()); ++g) {
                const GangwayFlowOut& f = gfo[size_t(g)];
                gangwayFlowsJ.push_back(jobj({ { "gangway", jstr(seated::gangwayName(L, g)) },
                                               { "type", jstr(g % L.gangwaysPerQuadrant() == 2 * L.gangways ? "corner" : "straight") },
                                               { "index", jint(g % L.gangwaysPerQuadrant() == 2 * L.gangways ? -1 : (g % L.gangwaysPerQuadrant()) % L.gangways) },
                                               { "width_m", jnum(f.widthM, 5) }, { "area_m2", jnum(f.areaM2, 6) }, { "people", jint(f.people) },
                                               { "out_head", jint(f.head) }, { "out_foot", jint(f.foot) }, { "out_other", jint(f.other) },
                                               { "first_in_s", jnum(f.firstIn >= 0 ? f.firstIn * dt : NAN) }, { "clear_s", jnum(f.clear >= 0 ? f.clear * dt : NAN) },
                                               { "mean_outflow_p_s", jnum(f.meanFlowPS) }, { "peak_outflow_p_s", jnum(f.peakFlowPS) },
                                               { "loaded_share", jnum(f.loadedShare) }, { "saturated_share", jnum(f.saturatedShare) },
                                               { "entry_limited_share", jnum(f.entryShare) }, { "mean_density_loaded_p_m2", jnum(f.meanDensityLoaded) } }, 4));
            }
            for (int e = 0; e < exitSlots; ++e) {
                if (!hasWidth(e) || ex[size_t(e)].count == 0) continue;
                const ExitFlowOut& f = efo[size_t(e)];
                exitFlowsJ.push_back(jobj({ { "exit", jstr(mt::exitName(e, seatL)) }, { "type", jstr(e < mt::EXIT_GAPS ? "avenue" : "door") },
                                            { "capacity_p_s", jnum(f.capPS) }, { "mean_flow_of_capacity", jnum(f.meanOfCap) },
                                            { "peak_flow_of_capacity", jnum(f.peakOfCap) }, { "at_capacity_share", jnum(f.atCapShare) } }, 4));
            }
        }
        const std::string flowsJson = seatedV && !gfo.empty()
            ? jobj({ { "window_s", jnum(flowW * dt) }, { "gangways", jarr(gangwayFlowsJ, 4) }, { "exits", jarr(exitFlowsJ, 4) },
                     { "last_agent", jint(lastAgent) },
                     { "last_agent_gangway", jstr(lastAgentGangway >= 0 ? seated::gangwayName(sv.layout, lastAgentGangway) : std::string("none")) },
                     { "last_agent_exit", jstr(lastAgentExit >= 0 ? seated::exitName(sv.layout, lastAgentExit) : std::string("-")) },
                     { "last_clear_gangway", jstr(lastClearGangway >= 0 ? seated::gangwayName(sv.layout, lastClearGangway) : std::string("-")) } }, 2)
            : std::string("null");
        std::vector<std::string> gangwaysJ;
        for (const GangwayUse& g : gangwayUse)
            gangwaysJ.push_back(jobj({ { "gangway", jstr(g.name) }, { "type", jstr(g.corner ? "corner" : "straight") },
                                       { "head_leads_to_door", g.headDoor ? "true" : "false" }, { "agents_on_it", jint(g.visits) },
                                       { "share_of_agents", jnum(g.visitShare, 5) }, { "last_gangway_of", jint(g.last) },
                                       { "share_of_evacuated_last", jnum(g.lastShare, 5) } }, 4));
        Fields spawnF;   // the spawn (seated venues)
        if (seatedV)
            spawnF = { { "seated", jint(sp.seats) }, { "standing", jint(sp.standing) }, { "standing_requested", jint(sp.standingRequested) },
                       { "standing_max", jint(sp.standingMax) }, { "standing_max_p_m2", jnum(OVERCROWD_STANDING_MAX_P_M2) },
                       { "standing_areas", jstr(overcrowded ? o.standing : std::string("none")) }, { "standing_area_m2", jnum(sp.standingAreaM2, 6) },
                       { "standing_walkway", jint(sp.standingWalkway) }, { "standing_concourse", jint(sp.standingConcourse) },
                       { "standing_gangways", jint(sp.standingGangways) }, { "placement_exhausted", sp.placementExhausted ? "true" : "false" },
                       { "placement_draws", jint(sp.draws) }, { "requested_load", jnum(o.load) }, { "load", jnum(overcrowded ? sp.load : o.load) },
                       { "standing_mean_p_m2", jnum(init.standingMean) }, { "initial_standing_cell_max_p_m2", jnum(init.standingMax) },
                       { "initial_circulation_cell_max_p_m2", jnum(init.circulationMax) } };
        const std::string json = jobj({ { "meta", jobj(meta, 2) }, { "spawn", seatedV ? jobj(spawnF, 2) : "null" }, { "units", jobj(unitsF, 2) },
                                        { "evacuation", jobj(evacF, 2) },
                                        { "exits", jarr(exits, 2) }, { "exit_utilisation", jobj(utilF, 2) },
                                        { "gangway_utilisation", seatedV ? jobj({ { "gangways", jarr(gangwaysJ, 4) },
                                              { "straight_agents", jint(gwTypeVisits[0]) }, { "corner_agents", jint(gwTypeVisits[1]) },
                                              { "straight_last", jint(gwTypeLast[0]) }, { "corner_last", jint(gwTypeLast[1]) },
                                              { "evacuated_without_gangway", jint(long(ctr.evacuated) - gwTypeLast[0] - gwTypeLast[1]) } }, 2) : "null" },
                                        { "zones", jarr(zones, 2) },
                                        { "circulation", seatedV ? zoneJson(circ, circAnyAbove, "gangway, walkway, concourse, avenue, exit", nullptr) : "null" },
                                        { "seat_rows", seatedV ? zoneJson(zo[mt::ZONE_TREAD], zoneAnyAbove[mt::ZONE_TREAD], "seat row (zone tread)", SEAT_ROW_LABEL) : "null" },
                                        { "hotspots", jarr(hotspots, 2) }, { "seat_row_hotspots", jarr(hotJson(hotRows), 2) },
                                        { "flows", flowsJson },
                                        { "inv_row", jobj(rows, 2) }, { "deposit", jobj(diag, 2) }, { "checks", jobj(checks, 2) } }, 0);
        std::ofstream(dir / "summary.json") << json << "\n";
    }

    // summary.md
    {
        std::ostringstream m;
        m << "# Experiment `" << o.name << "`\n\n";
        if (!o.note.empty()) m << "**" << o.note << "**\n\n";
        if (seatedV)
            m << "Venue " << sv.name << " (analytic seated venue; e_goal from the navigation field: " << navInfo << "). " << n0 << " agents "
              << (overcrowded ? "(load " + fmt("%.1f", 100.0 * sp.load) + "%, requested " + fmt("%.0f", 100.0 * o.load) + "%): every one of the " +
                                    std::to_string(cap.design) + " seats and " + std::to_string(sp.standing) + " standing (spawnOvercrowdedCrowd, seed " +
                                    std::to_string(o.seed) + "; below)"
                              : "on " + fmt("%.0f", 100.0 * o.load) + "% of the " + std::to_string(cap.design) + " seats (spawnSeatedCrowd, seed " +
                                    std::to_string(o.seed) + ")")
              << ", buffer N = " << o.n << ", "
              << stepsRun << " steps" << (complete ? " (everyone left)" : " (max steps reached)") << ", readback every " << o.every << " step(s). Engine: "
              << (o.engine == "gpu" ? std::string("GPU (CrowdSim)") : "CPU reference (CpuCrowdSim, " + o.sort + " sort, " +
                  (o.threads > 0 ? std::to_string(o.threads) : std::string("all")) + " threads)")
              << (o.dtDiv > 1 ? ", DT / " + std::to_string(o.dtDiv) : std::string()) << ".\n"
              << "Model: **" << modelLabel << "**"
              << (mo.exitChoice == ExitChoice::QueueAware ? " (exit choice: " + std::to_string(choiceCtr.evaluations) + " evaluations, " +
                  std::to_string(choiceCtr.switches) + " switches, " + std::to_string(choiceCtr.forced) + " forced choices)" : std::string()) << ".\n";
        else
            m << "Venue: the current stadium (`stadium.sdf`, `stadium.obj`). N = " << o.n << " (" << n0 << " active), spawn `" << o.spawn
              << "` (spawnBleacherCrowd, seed " << o.seed << "), " << stepsRun << " steps" << (complete ? " (everyone left)" : " (max steps reached)")
              << ", readback every " << o.every << " step(s)." << (o.engine == "cpu" ? " Engine: CPU reference (" + o.sort + " sort)." : std::string())
              << (o.dtDiv > 1 ? " DT / " + std::to_string(o.dtDiv) + "." : std::string()) << "\n";
        m << "Capacity: **" << capacityLabel << "** (the " << cap.venue << " venue's design capacity " << cap.design
          << ", jam capacity " << cap.jam << ": " << fmt("%.1f", cap.occupiableM2) << " m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).\n";
        m << "Commit `" << commit << "`, dirty " << dirty << ", " << buildinfo::buildConfig() << " build; " << bench::glRenderer() << ", "
          << bench::glDriver() << "; started " << started << ", " << fmt("%.1f", wallS) << " s wall.\n\n";
        m << "Units: 1 model unit = " << WORLD_SCALE_M_PER_UNIT << " m (hard body radius " << BODY_RADIUS_M << " m, personal space " << PERSONAL_RADIUS_M << " m), 1 model time unit = "
          << fmt("%.4f", TIME_SCALE_S_PER_UNIT) << " s (V_MAX = " << V_FREE_M_S << " m/s), one step DT = " << fmt("%.4f", dt) << " s.\n\n";

        if (overcrowded) {
            m << "## Spawn (overcrowding)\n\n| | |\n|---|---|\n"
              << "| seated | " << sp.seats << " (every seat) |\n"
              << "| standing | **" << sp.standing << "** (requested round((" << fmt("%.2f", o.load) << " - 1) x " << cap.design << ") = " << sp.standingRequested
              << "; at most " << sp.standingMax << " = floor(" << OVERCROWD_STANDING_MAX_P_M2 << " p/m^2 x " << fmt("%.1f", sp.standingAreaM2) << " m^2))"
              << (sp.placementExhausted ? " **placement exhausted**" : "") << " |\n"
              << "| standing floor | " << (o.standing == "gangways" ? "walkway + rear concourse + gangways (the gangway-standing variant)" : "walkway + rear concourse")
              << ", " << fmt("%.1f", sp.standingAreaM2) << " m^2 |\n"
              << "| standing on the walkway / concourse / gangways | " << sp.standingWalkway << " / " << sp.standingConcourse << " / " << sp.standingGangways << " |\n"
              << "| **load** | **" << fmt("%.2f", 100.0 * sp.load) << "%** of the seats (requested " << fmt("%.0f", 100.0 * o.load) << "%"
              << (sp.standing < sp.standingRequested ? "; the floor takes no more: the achievable maximum" : "") << ") |\n"
              << "| standing crowd's mean density | " << fmt("%.3f", init.standingMean) << " p/m^2 |\n"
              << "| initial density, max over 1 m cells >= " << mt::PEAK_MIN_WALKABLE_M2 << " m^2 (cloud-in-cell of the spawn) | standing zones' cells "
              << fmt("%.2f", init.standingMax) << ", all circulation cells " << fmt("%.2f", init.circulationMax) << " p/m^2 |\n\n"
              << "Placement: seeded uniform random over the standing floor (mt19937, seed " << o.seed << ", " << sp.draws << " draws), a draw kept if a body fits "
                 "there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.\n\n";
        }
        m << "## Evacuation\n\n| | step | t [s] |\n|---|---:|---:|\n";
        for (auto [label, s] : { std::pair<const char*, int>{ "t50", s50 }, { "t90", s90 }, { "t100", s100 } })
            m << "| " << label << " | " << (s < 0 ? std::string("-") : std::to_string(s)) << " | " << (s < 0 ? std::string("-") : fmt("%.1f", secs(s))) << " |\n";
        m << "\nt_p: the step by which ceil(p x " << n0 << ") agents had left (per-agent evacuation steps from the metrics), x DT.\n\n";

        m << "## Exits\n\n| exit | clear width [m] | evacuated |" << (seatedV ? " nearest exit of [seats] |" : "")
          << " first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |\n"
          << (seatedV ? "|---|---:|---:|---:|---:|---:|---:|---:|---|\n" : "|---|---:|---:|---:|---:|---:|---:|---|\n");
        for (int e = 0; e < exitSlots; ++e) {
            if (e == mt::EXIT_OTHER) continue;
            const ExitStat& x = ex[size_t(e)];
            m << "| " << mt::exitName(e, seatL) << " | " << fmt("%.2f", venue.exitWidthM[size_t(e)]) << " | " << x.count << " | "
              << (seatedV ? std::to_string(predicted[size_t(e)]) + " | " : std::string()) << fmt("%.1f", secs(x.first))
              << " | " << fmt("%.1f", secs(x.last)) << " | " << fmt("%.1f", x.meanFlow) << " | " << fmt("%.1f", x.peakFlow) << " | "
              << fmt("%.1f", secs(x.peakFrom - 1)) << "-" << fmt("%.1f", secs(x.peakFrom - 1 + windowSteps)) << " |\n";
        }
        m << "| other | | " << ex[mt::EXIT_OTHER].count << (seatedV ? " | |" : " |") << " | | | | |\n\n";
        if (seatedV)
            m << "Clear width: an avenue's width between its side walls (" << fmt("%.2f", units::metres(2.0 * double(sv.layout.avenueHalf)))
              << " m), a concourse door's width through the outer wall (" << fmt("%.2f", sv.layout.doorWidthM)
              << (sv.layout.cornerDoorLo < 1e8f ? " m; a corner door's: the gap between its wall ends, " + fmt("%.2f", sv.layout.cornerDoorWidthM) : std::string())
              << " m); agents are removed past the outer wall's outer face (" << fmt("%.2f", units::metres(sv.layout.outerFace))
              << " m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no "
                 "congestion-aware rerouting). Mean flow: agents through the exit / "
                 "its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents "
                 "in any window of " << windowSteps << " consecutive steps (" << fmt("%.2f", windowSteps * dt) << " s; `--peak-window-s` "
              << o.peakWindowS << "), / window / width. Both from the exit counters read every " << o.every << " step(s).\n\n";
        else
        m << "Clear width: geometric width of the gap in the outer wall, lateral section at dep " << EXIT_DEPTH << " (" << fmt("%.2f", units::metres(EXIT_DEPTH))
          << " m, where agents are removed) at the agent rest height, measured on the SDF (CPU sampler). Mean flow: agents through the exit / "
             "its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents "
             "in any window of " << windowSteps << " consecutive steps (" << fmt("%.2f", windowSteps * dt) << " s; `--peak-window-s` "
          << o.peakWindowS << "), / window / width. Both from the exit counters read every " << o.every << " step(s).\n\n";

        // Exit utilisation
        m << "## Exit utilisation\n\n| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |\n|---|---|---:|---:|---:|---:|\n";
        for (int e = 0; e < exitSlots; ++e) {
            if (!hasWidth(e)) continue;
            m << "| " << mt::exitName(e, seatL) << " | " << (use[size_t(e)].avenue ? (seatedV ? "avenue" : "gap") : "door") << " | " << fmt("%.2f", venue.exitWidthM[size_t(e)])
              << " | " << ex[size_t(e)].count << " | " << fmt("%.1f%%", 100.0 * use[size_t(e)].share) << " | " << fmt("%.1f%%", 100.0 * use[size_t(e)].capacityUsed) << " |\n";
        }
        if (seatedV)
            m << "| **doors (" << 4 * sv.layout.doorsPerQuadrant() << ")** | door | " << fmt("%.2f", typeWidth[0]) << " | " << long(typeCount[0]) << " | "
              << fmt("%.1f%%", 100.0 * typeCount[0] / std::max(1u, ctr.evacuated)) << " | |\n"
              << "| **avenues (4)** | avenue | " << fmt("%.2f", typeWidth[1]) << " | " << long(typeCount[1]) << " | "
              << fmt("%.1f%%", 100.0 * typeCount[1] / std::max(1u, ctr.evacuated)) << " | |\n";
        m << "\n**Unused exit width: " << fmt("%.1f", unusedWidth) << " of " << fmt("%.1f", totalWidth) << " m (" << fmt("%.1f%%", totalWidth > 0 ? 100.0 * unusedWidth / totalWidth : 0.0)
          << ")** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = " << EXIT_FLOW_P_M_MIN
          << " persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = " << fmt("%.1f", t100s)
          << " s: the share of the exit's nominal throughput over the whole evacuation used; all exits together "
          << fmt("%.1f%%", std::isfinite(t100s) && totalWidth > 0 ? 100.0 * double(ctr.evacuated) / (totalWidth * double(EXIT_FLOW_P_M_MIN) / 60.0 * t100s) : NAN) << ".\n\n";

        if (seatedV) {   // per-gangway utilisation
            m << "## Gangway utilisation\n\n| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |\n"
                 "|---|---|---|---:|---:|---:|---:|\n";
            for (const GangwayUse& g : gangwayUse)
                m << "| " << g.name << " | " << (g.corner ? "corner" : "straight") << " | " << (g.headDoor ? "yes" : "**no**") << " | " << g.visits << " | "
                  << fmt("%.1f%%", 100.0 * g.visitShare) << " | " << g.last << " | " << fmt("%.1f%%", 100.0 * g.lastShare) << " |\n";
            m << "| **straight (" << 8 * sv.layout.gangways << ")** | | | " << gwTypeVisits[0] << " | | " << gwTypeLast[0] << " | "
              << fmt("%.1f%%", ctr.evacuated ? 100.0 * gwTypeLast[0] / ctr.evacuated : 0.0) << " |\n"
              << "| **corner (4)** | | | " << gwTypeVisits[1] << " | | " << gwTypeLast[1] << " | " << fmt("%.1f%%", ctr.evacuated ? 100.0 * gwTypeLast[1] / ctr.evacuated : 0.0)
              << " |\n\nAgents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one "
                 "step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the "
                 "evacuated agents whose last gangway it was (a partition of those that used any; the rest, " << long(ctr.evacuated) - gwTypeLast[0] - gwTypeLast[1]
              << ", left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows "
                 "after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).\n\n";
        }

        if (seatedV && !gfo.empty()) {   // flows and limits
            const SeatedLayout& L = sv.layout;
            m << "## Flows and limits\n\nWindows of " << flowW << " steps (" << fmt("%.2f", flowW * dt) << " s). Exits: the exit choice's capacity w J (J = "
              << EXIT_FLOW_P_M_MIN << " persons/(m min)); at capacity: a window at >= 80% of it.\n\n"
                 "| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |\n|---|---:|---:|---:|---:|---:|---:|\n";
            double dSum[2] = {}, dN[2] = {};
            for (int e = 0; e < exitSlots; ++e) {
                if (!hasWidth(e) || ex[size_t(e)].count == 0) continue;
                const ExitFlowOut& f = efo[size_t(e)];
                m << "| " << mt::exitName(e, seatL) << " | " << ex[size_t(e)].count << " | " << fmt("%.1f", ex[size_t(e)].first * dt) << " | "
                  << fmt("%.1f", ex[size_t(e)].last * dt) << " | " << fmt("%.2f", f.meanOfCap) << " | " << fmt("%.2f", f.peakOfCap) << " | "
                  << fmt("%.1f%%", 100.0 * f.atCapShare) << " |\n";
                const int ty = e < mt::EXIT_GAPS ? 1 : 0;
                dSum[ty] += f.meanOfCap;
                dN[ty] += 1.0;
            }
            m << "\nMean flow / w J averaged over the doors " << fmt("%.2f", dN[0] ? dSum[0] / dN[0] : NAN) << ", over the avenues "
              << fmt("%.2f", dN[1] ? dSum[1] / dN[1] : NAN) << ".\n\n"
                 "Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, "
                 "avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor "
                 "(seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and "
                 "its density (occupancy / area) at or above LoS F (" << mt::LOS_F_P_M2 << " persons/m^2): the gangway itself is full; entry-limited: "
                 "loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per "
                 "window: gangway_flows.csv.\n\n"
                 "| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | "
                 "loaded | saturated | entry-limited | mean density while loaded [p/m^2] |\n|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|\n";
            for (int g = 0; g < int(gfo.size()); ++g) {
                const GangwayFlowOut& f = gfo[size_t(g)];
                m << "| " << seated::gangwayName(L, g) << " | " << fmt("%.2f", f.widthM) << " | " << fmt("%.1f", f.areaM2) << " | " << f.people << " | " << f.head
                  << " / " << f.foot << " / " << f.other << " | " << (f.firstIn >= 0 ? fmt("%.1f", f.firstIn * dt) : "-") << " | "
                  << (f.clear >= 0 ? fmt("%.1f", f.clear * dt) : "-") << " | " << fmt("%.2f", f.meanFlowPS) << " | " << fmt("%.2f", f.peakFlowPS) << " | "
                  << fmt("%.0f%%", 100.0 * f.loadedShare) << " | " << fmt("%.0f%%", 100.0 * f.saturatedShare) << " | " << fmt("%.0f%%", 100.0 * f.entryShare)
                  << " | " << fmt("%.2f", f.meanDensityLoaded) << " |\n";
            }
            m << "\nThe last agent out (agent " << lastAgent << ", t100 " << fmt("%.1f", t100s) << " s): last gangway "
              << (lastAgentGangway >= 0 ? seated::gangwayName(L, lastAgentGangway) : std::string("none")) << ", exit "
              << (lastAgentExit >= 0 ? seated::exitName(L, lastAgentExit) : std::string("-"))
              << ". The gangway that cleared last: " << (lastClearGangway >= 0 ? seated::gangwayName(L, lastClearGangway) + " at " + fmt("%.1f", gfo[size_t(lastClearGangway)].clear * dt) + " s" : std::string("-"))
              << ".\n\n";
        }
        m << "## Zones\n\nDensity thresholds (persons/m^2, at or above): LoS E " << mt::LOS_E_P_M2 << ", LoS F " << mt::LOS_F_P_M2 << " (Fruin 1971), crush "
          << mt::CRUSH_P_M2 << " (as reported in the cited sources, not yet checked against the originals; swarm/metrics.hpp).";
        if (seatedV)
            m << " **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the "
                 "seat rows' clearways are reported apart (" << SEAT_ROW_LABEL << ").";
        m << "\n\n";
        auto zoneRow = [&](const std::string& name, const ZoneOut& q, const double* any) {
            m << "| " << name << " | " << q.cells << " | " << fmt("%.1f", q.area) << " | " << fmt("%.2f", q.peak) << " | "
              << fmt("%.1f", any[0]) << " / " << fmt("%.1f", any[1]) << " / " << fmt("%.1f", any[2]) << " | "
              << fmt("%.1f", q.maxCellAbove[0]) << " / " << fmt("%.1f", q.maxCellAbove[1]) << " / " << fmt("%.1f", q.maxCellAbove[2]) << " | "
              << fmt("%.1f", q.exposure) << " | " << fmt("%.0f", q.personS) << " | "
              << (q.massSteps ? fmt("%.3f", double(q.speedSteps) / double(q.massSteps)) : std::string("-")) << " |\n";
        };
        const char* zoneHeader = "| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | "
                                 "exposure [person-s] | person-s | mean speed occupied [m/s] |\n|---|---:|---:|---:|---|---|---:|---:|---:|\n";
        if (seatedV) {
            m << "### Circulation zones (headline)\n\n" << zoneHeader;
            zoneRow("**all circulation**", circ, circAnyAbove);
            for (int z = 0; z < zoneRows; ++z)
                if (circulationZone(z)) zoneRow(zoneName(z), zo[size_t(z)], zoneAnyAbove[z]);
            m << "\n### Seat rows (reported apart: " << SEAT_ROW_LABEL << ")\n\n" << zoneHeader;
            zoneRow("seat row", zo[mt::ZONE_TREAD], zoneAnyAbove[mt::ZONE_TREAD]);
            m << "\nA seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m "
                 "cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)\n";
        } else {
            m << zoneHeader;
            for (int z = 0; z < zoneRows; ++z) zoneRow(zoneName(z), zo[size_t(z)], zoneAnyAbove[z]);
        }
        m << "\nPer floor cell (1 m x 1 m, " << venue.res << " x " << venue.res << " from (" << mt::gridMinM(venue.res) << ", " << mt::gridMinM(venue.res)
          << ") m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below " << mt::MIN_WALKABLE_M2
          << " m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least " << mt::PEAK_MIN_WALKABLE_M2
          << " m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it "
             "(readbacks every " << o.every << " step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: "
             "person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal "
             "speed weighted by the persons present (person-time weighted).\n\n";

        auto hotTable = [&](const std::vector<CellOut>& list) {
            m << "| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |\n"
                 "|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|\n";
            for (size_t i = 0; i < list.size(); ++i) {
                const CellOut& h = list[i];
                const glm::vec2 cm = cellCentre(h.c);
                m << "| " << i + 1 << " | " << fmt("%.1f", cm.x) << " | " << fmt("%.1f", cm.y) << " | " << zoneName(zoneOfCell(h.c)) << " | "
                  << fmt("%.2f", venue.walkableM2[size_t(h.c)]) << " | " << fmt("%.2f", h.peak) << " | " << fmt("%.1f", h.timeAbove[0]) << " | "
                  << fmt("%.1f", h.timeAbove[1]) << " | " << fmt("%.1f", h.timeAbove[2]) << " | " << fmt("%.1f", h.exposure) << " | "
                  << (std::isfinite(h.meanSpeed) ? fmt("%.3f", h.meanSpeed) : std::string("-")) << " |\n";
            }
        };
        m << "## Top 10 hotspot cells" << (seatedV ? " (circulation zones)" : "") << "\n\nRanked by exposure, then time >= LoS F, then time >= LoS E, then peak density.\n\n";
        hotTable(hot);
        if (seatedV) {
            m << "\nThe top 5 seat-row cells, apart (" << SEAT_ROW_LABEL << "):\n\n";
            hotTable(hotRows);
        }
        if (seatedV)
            m << "\n## Rows (INV-row)\n\n" << checker.rowChanges << " row changes (a move from one row's clearway onto another's without a gangway, "
                 "the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every "
                 "step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): " << checker.rowEntries
              << "; agent-steps of seated agents on another row's clearway: " << checker.strayRowSteps << ".\n\n";
        else
        m << "\n## Tread rows (INV-row)\n\n" << rowCrossings << " row changes by " << crossingAgents
          << " agents that did not pass through a non-tread zone (aisle, walkway, ...): an agent in the tread zone resting within "
          << ROW_TOLERANCE << " rises of row k (centre at k x " << ROW_RISE << " + BODY_RADIUS) is on row k; a change of row without leaving "
             "the tread zone in between counts (sampled every " << o.every << " step(s)). Down (towards the pitch) " << rowDown << ", up "
          << rowCrossings - rowDown << "; more than one row at once " << rowMulti << "; in steps 1-50 / 51-200 / after 200: " << rowByPhase[0]
          << " / " << rowByPhase[1] << " / " << rowByPhase[2] << "." << (events.empty() ? "" : " The first events are in `crossings.csv`.")
          << "\n\n";
        m << "## Deposit check\n\nPerson-seconds deposited: " << fmt("%.1f", totalPersonS) << ", of them in excluded cells: " << fmt("%.3f", excludedPersonS)
          << ".\n";
        if (o.checks) {
            auto pf = [](bool ok) { return ok ? "PASS" : "**FAIL**"; };
            char b[400];
            m << "\n## Checks (after every step)\n\n| check | result | values |\n|---|---|---|\n";
            std::snprintf(b, sizeof b, "all %zu overlapping pair-steps: p99 %.4f, max %.4f of BODY_DIAM (limits 0.05 / 0.20%s); crowd p99 %.4f max %.4f; "
                          "venue-geometry %zu: p99 %.4f max %.4f", plaus.allStats.n, plaus.allStats.p99, plaus.allStats.max,
                          seatedV ? ", every case: analytic venue, no exemption" : ", crowd cases; venue-geometry cases exempt in the baked terrace",
                          plaus.crowdStats.p99, plaus.crowdStats.max, plaus.venueStats.n, plaus.venueStats.p99, plaus.venueStats.max);
            m << "| overlap | " << pf(overlapOk) << " | " << b << " |\n";
            std::snprintf(b, sizeof b, "pairs from non-adjacent start cells %ld, max displacement %.5f (bound %.5f)", plaus.gridMisses, plaus.maxDisplacement,
                          plausibility::displacementBound());
            m << "| neighbour grid | " << pf(plaus.gridOk()) << " | " << b << " |\n";
            std::snprintf(b, sizeof b, "centre in solid %ld, below floor + BODY_RADIUS - 1e-4 %ld agent-steps; airborne runs %ld (longest %d steps)",
                          plaus.centreInSolid, plaus.floorViolations, plaus.airborneRuns, plaus.longestAirborne);
            m << "| floors | " << pf(plaus.floorOk()) << " | " << b << " |\n";
            std::snprintf(b, sizeof b, "midline crossings %ld, in the collision band %ld agent-steps", plaus.fenceCrossings, plaus.fenceBand);
            m << "| fence | " << pf(plaus.fenceOk()) << " | " << b << " |\n";
            if (plaus.minWallClearance < 1e8f)
                std::snprintf(b, sizeof b, "clearance < BODY_RADIUS - 3e-4: %ld agent-steps; min %.5f", plaus.wallViolations,
                              double(plaus.minWallClearance));
            else   // wallClearance searches only within BODY_RADIUS - 3e-4
                std::snprintf(b, sizeof b, "clearance < BODY_RADIUS - 3e-4: %ld agent-steps (no wall that close)", plaus.wallViolations);
            m << "| walls | " << pf(plaus.wallOk()) << " | " << b << " |\n";
            std::snprintf(b, sizeof b, "max |v_xy| %.6f (V_MAX %.2f), %ld above", plaus.maxSpeed, V_MAX, plaus.speedViolations);
            m << "| speed | " << pf(plaus.speedOk()) << " | " << b << " |\n";
            std::snprintf(b, sizeof b, "peak %.2f p/m^2 over fully walkable 1 m cells (ceiling %.2f)", plaus.peakFull, plausibility::DENSITY_CEILING_P_M2);
            m << "| density ceiling | " << pf(plaus.densityOk()) << " | " << b << " |\n";
            m << "| INV-row | " << (seatedV ? pf(invRowOk) : "exempt") << " | " << rowCrossings << " row changes"
              << (seatedV ? "" : " (the baked terrace is exempt: bare treads without seat backs)") << " |\n";
            if (seatedV) {
                std::snprintf(b, sizeof b, "floor rises above MAX_STEP_UP %ld; climbs over a vertical face (any height, onto a floor above the start floor) %ld "
                              "(max rise %.3f m); faces crossed in a net descent %ld (information)", checker.risesAbove, checker.verticalClimbs,
                              units::metres(checker.maxVerticalRise), checker.descentFaces);
                m << "| step-up rules | " << pf(stepOk) << " | " << b << " |\n";
                std::snprintf(b, sizeof b, "agent-steps over a seat block / barrier / wall column %ld; steps through one %ld; fence-side changes %ld",
                              checker.solidSteps, checker.tunnels, checker.fenceCrossings);
                m << "| no wall tops, no tunnelling | " << pf(topsOk) << " | " << b << " |\n";
            }
            m << "\nPlausibility: tools/plausibility.hpp (test_gpu validation.plausibility_terrace's checks, the " << plausibility::venueKindName(plaus.venue)
              << "); the venue checks: tools/venue_s.hpp Checker (test_gpu venue.s_forced_*).\n";
        }
        std::ofstream(dir / "summary.md") << m.str();
    }
    std::printf("  t50 %.1f s, t90 %.1f s, t100 %.1f s -> %s\n", secs(s50), secs(s90), secs(s100), dir.string().c_str());
    if (o.checks)
        std::printf("  checks: plausibility %s, INV-row %s (%ld), step-up %s, wall tops %s\n", plausOk ? "PASS" : "FAIL", !seatedV ? "exempt" : invRowOk ? "PASS" : "FAIL",
                    rowCrossings, stepOk ? "PASS" : "FAIL", topsOk ? "PASS" : "FAIL");
    if (o.dtDiv > 1) fs::remove_all(shaderDir);
    return !o.checks || (complete && plausOk && invRowOk && stepOk && topsOk) ? 0 : 3;
}

} // namespace

int main(int argc, char** argv) {
    try {
        return run(parse(argc, argv));
    } catch (const std::exception& e) {
        std::fprintf(stderr, "FATAL: %s\n", e.what());
        return 1;
    }
}
