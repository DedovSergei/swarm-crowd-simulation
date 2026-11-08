// fd_harness: fundamental diagram of the crowd model in a periodic corridor, and the
// calibration of its parameters against it. A test scenario only: it builds the simulation shaders with scenario
// defines (physics.comp FD_CORRIDOR, FD_PERIODIC_X, TEST_DRIVE_DIR); without them the shaders are the production ones.
//
//   fd_harness run       [--densities 0.1,0.5,1,...] [--width-m 3] [--length-m 50] [--warmup-s 300] [--measure-s 300]
//                        [--seeds 7,8,9] [--ksep X] [--relax X] [--theadway S] [--iters K] [--name fd] [--out out/results/fd]
//   fd_harness calibrate [--ksep-grid a,b,...] [--relax-grid a,b,...] [--theadway-grid a,b,...] [--densities ...]
//                        [--warmup-s ..] [--measure-s ..] [--seeds 7,8,9] [--name calibration] [--out out/results/fd]
//   fd_harness dtcheck   [--ksep-grid a,b,...] [--relax-grid a,b,...] [--theadway-grid a,b,...]
//                        (DT convergence of the N = 4096 evacuation per variant: DT, DT/2, DT/4)
//   fd_harness ksweep    [--iters-list 0,1,2,4,8,16,32] [--ref 32] [--densities 0.5,...,4] [--rms-densities 1,2,3,4]
//                        [--seeds 7,8,9] [--warmup-s ..] [--measure-s ..] [--name ksweep] [--out out/results/fd]
//                        (the projection iteration sweep, see cmdKSweep)
//   fd_harness tiebreak  [--max-steps 12000] [--name tiebreak] [--out out/results/fd]
//                        (mutual-standoff tie-break activations per step of the N = 4096 evacuation)
//   fd_harness stair     [--mode ring|reservoir] [--dirs up,down,level] [--densities ...] [--width-m 1.2] [--length-m 50 (reservoir: 28)]
//                        [--rake 0.5] [--seeds 7,8,9 (reservoir: 7,...,11)] [--warmup-s 300 --measure-s 300 (ring)] [--name stair] [--out out/results/stair]
//                        [--stair-flow off|empirical|conservative (default: the venues' default)] [--t-up S --t-down S (the calibration's grid)]
//                        (the stair harness at a gangway's width: an inclined periodic corridor, the stair fundamental diagram and
//                        the calibration's measure (cmdStair), or a reservoir discharging up / down the incline (the cross-check, cmdStairReservoir))
//
// Parameter overrides (--ksep, --relax, --theadway in real seconds) are #undef / #define pairs after the preamble with
// the literal the preamble itself would emit (glslFloatLiteral of the value sim_params.hpp would compute), so a grid row
// and the production build with the same constants compile to the same program.
//
// Scenario: a straight corridor (analytic box: floor z = 0, walls at |y| = width / 2), periodic in x with period
// --length-m (positions wrap; the neighbour search wraps its cells and uses minimum-image offsets), the goal direction
// constant +x (the router bypassed). Global density rho = N / (width x length). After the warm-up, every step the
// mean x-velocity of the agents in the central measurement area (|x| <= 5 m, wall to wall) is recorded; the speed is
// its mean over the measured steps, the flow J = rho v. With several --seeds (independent random placements) every
// figure of a density is the mean over the seeds (the max overlap: the max). Reference: Weidmann (1993) v(rho) = v0 (1 - exp(-gamma (1/rho -
// 1/rho_max))), v0 1.34 m/s, gamma 1.913 m^-2, rho_max 5.4 persons/m^2 (as reported there; not yet checked against the original).
// 'run' writes <out>/<name>_<yyyymmdd_hhmm>/fd.csv and summary.md (plot: tools/fd/fd_plot.py <folder>).
// 'calibrate' runs the FD (rho in [0.5, 4] for the RMS objective, all densities for the flow) for every grid point, then
// the N = 4096 stadium evacuation with the plausibility checks (tools/plausibility.hpp) and the same evacuation at DT / 2,
// into grid.csv and summary.md. The hard constraints of a row (feasible) are the plausibility checks (which
// include a complete evacuation), the DT -> DT/2 change of the evacuation time t100 within DT_CHANGE_LIMIT and the
// maximum flow within FLOW_TOLERANCE of Weidmann's; the objective is the RMS speed error, target RMS_TARGET.
#include "../benchmark/bench_common.hpp"
#include "../plausibility.hpp"
#include "../tiebreak.hpp"

#include <swarm/assets.hpp>
#include <swarm/crowd_sim.hpp>
#include <swarm/exit_choice.hpp>
#include <swarm/metrics.hpp>
#include <swarm/sdf.hpp>
#include <swarm/shader.hpp>
#include <swarm/venue.hpp>

#include <array>
#include <cstdlib>
#include <iomanip>
#include <random>
#include <tuple>

namespace fs = std::filesystem;
using namespace swarm;

namespace {

constexpr double WEIDMANN_V0 = 1.34, WEIDMANN_GAMMA = 1.913, WEIDMANN_RHO_MAX = 5.4;   // m/s, m^-2, persons/m^2
constexpr double FRUIN_FLOW_P_M_MIN = 82.0;   // the commonly cited Fruin maximum flow (not yet checked against the source)
constexpr double MEASURE_HALF_M = 5.0;        // central measurement area: |x| <= 5 m, wall to wall
// Calibration: hard constraints and the objective's target
constexpr double DT_CHANGE_LIMIT = 0.05;      // |t100(DT/2) - t100(DT)| / t100(DT)
constexpr double FLOW_TOLERANCE = 0.25;       // max flow within +-25% of Weidmann's
constexpr double RMS_TARGET = 0.15;           // m/s

double weidmannSpeed(double rho) {
    if (rho >= WEIDMANN_RHO_MAX) return 0.0;
    return WEIDMANN_V0 * (1.0 - std::exp(-WEIDMANN_GAMMA * (1.0 / rho - 1.0 / WEIDMANN_RHO_MAX)));
}

struct Params {
    double ksep = K_SEP, relax = PROJ_RELAX, theadway = T_HEADWAY_S;   // theadway: the time gap in real seconds
    int iters = PROJ_ITERATIONS;
};

struct Scenario {
    double widthM = 3.0, lengthM = 50.0, warmupS = 300.0, measureS = 300.0;
    std::vector<unsigned> seeds{ 7 };
};

struct FdPoint {
    double rho = 0;          // global density, persons/m^2
    int agents = 0;
    double speed = 0;        // mean x-velocity in the measurement area, m/s
    double speedAbs = 0;     // mean horizontal speed |v_xy| there, m/s
    double speedFirstHalf = 0, speedSecondHalf = 0;   // stationarity check
    double rhoArea = 0;      // mean density in the measurement area, persons/m^2
    double flow = 0;         // rho * speed, persons per metre per second
    double weidmann = 0;     // Weidmann speed at rho
    double overlapMax = 0;   // max overlap depth / BODY_DIAM over the measured steps
};

// Shader directory with the scenario defines inserted into physics.comp after its #version line (after the generated
// preamble, so #undef/#define pairs override preamble values)
fs::path shaderVariant(const fs::path& shaderDir, const std::string& name, const std::string& defines) {
    fs::path dir = processTempPath("swarm_fd_" + name);
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
    src.insert(src.find('\n') + 1, defines);
    std::ofstream(dir / "physics.comp", std::ios::binary | std::ios::trunc) << src;
    return dir;
}

std::string fmtNum(double v) { std::ostringstream o; o << std::setprecision(9) << v; return o.str(); }
std::string fmtShort(double v) { std::ostringstream o; o << v; return o.str(); }

// T_HEADWAY in model time as sim_params.hpp computes it from T_HEADWAY_S
float headwayModel(double seconds) {
    return float(glsl_fold::decimal(float(seconds)) / glsl_fold::decimal(TIME_SCALE_S_PER_UNIT));
}

std::string paramDefines(const Params& p) {
    return "#undef K_SEP\n#define K_SEP " + glslFloatLiteral(float(p.ksep)) + "\n#undef PROJ_RELAX\n#define PROJ_RELAX " +
           glslFloatLiteral(float(p.relax)) + "\n#undef T_HEADWAY\n#define T_HEADWAY " + glslFloatLiteral(headwayModel(p.theadway)) + "\n";
}

std::string corridorDefines(const Scenario& sc) {
    const double halfW = units::modelLength(0.5 * sc.widthM), period = units::modelLength(sc.lengthM);
    const double cell = double(DOMAIN_SPAN) / GRID_RES;
    const double c0 = (-0.5 * period - double(DOMAIN_MIN)) / cell, cells = period / cell;
    if (std::abs(c0 - std::round(c0)) > 1e-6 || std::abs(cells - std::round(cells)) > 1e-6 || period > 1.8)
        throw std::runtime_error("--length-m must be a multiple of 2 grid cells (3.125 m) and at most 56 m");
    std::ostringstream d;
    d << "#define FD_CORRIDOR\n#define FD_HALF_WIDTH " << fmtNum(halfW) << "\n#define FD_PERIODIC_X\n#define FD_PERIOD " << fmtNum(period)
      << "\n#define FD_CELL0 " << int(std::lround(c0)) << "\n#define FD_CELLS " << int(std::lround(cells))
      << "\n#define TEST_DRIVE_DIR vec2(1.0, 0.0)\n";
    return d.str();
}

// Uniform random placement in the corridor's centre band, hard-disk rejection (up to 200 attempts each; the
// densest points place the rest overlapping, the warm-up resolves them)
std::vector<GpuBoid> placeCorridor(const Scenario& sc, int active, unsigned seed) {
    const float halfL = float(units::modelLength(0.5 * sc.lengthM));
    const float yMax = float(units::modelLength(0.5 * sc.widthM)) - BODY_RADIUS;
    std::mt19937 rng(seed);
    std::uniform_real_distribution<float> ux(-halfL, halfL), uy(-yMax, yMax);
    int n = 256;
    while (n < active) n *= 2;
    std::vector<GpuBoid> b(size_t(n), GpuBoid{ glm::vec4(PARK_COORD, PARK_COORD, PARK_COORD, 0.0f), glm::vec4(0.0f) });
    const float period = 2.0f * halfL;
    for (int i = 0; i < active; ++i) {
        glm::vec2 p(0.0f);
        for (int a = 0; a < 200; ++a) {
            p = glm::vec2(ux(rng), uy(rng));
            bool free = true;
            for (int j = 0; j < i && free; ++j) {
                glm::vec2 d = p - glm::vec2(b[size_t(j)].position);
                d.x -= period * std::round(d.x / period);
                free = glm::dot(d, d) >= BODY_DIAM2;
            }
            if (free) break;
        }
        b[size_t(i)].position = glm::vec4(p, BODY_RADIUS, 1.0f);
        b[size_t(i)].velocity = glm::vec4(0.0f);
    }
    return b;
}

FdPoint measureSeed(const fs::path& shaderDir, GLuint sdfTex, const Scenario& sc, const Params& prm, double rho, unsigned seed) {
    const int active = int(std::lround(rho * sc.widthM * sc.lengthM));
    std::vector<GpuBoid> start = placeCorridor(sc, active, seed);
    const int n = int(start.size());
    CrowdSim sim(shaderDir, n);
    sim.setProjectionIterations(prm.iters);
    sim.upload(start);
    const int warm = int(std::lround(sc.warmupS / DT_REAL_S)), meas = int(std::lround(sc.measureS / DT_REAL_S));
    for (int s = 0; s < warm; ++s) sim.step(sdfTex);
    const double halfArea = units::modelLength(MEASURE_HALF_M), areaM2 = 2.0 * MEASURE_HALF_M * sc.widthM;
    const double toMs = units::metresPerSecond(1.0);
    double sumV = 0, sumAbs = 0, sumHalf[2] = {}, countHalf[2] = {}, count = 0, sumRhoArea = 0, maxOverlap = 0;
    for (int s = 0; s < meas; ++s) {
        sim.step(sdfTex);
        const std::vector<GpuBoid> st = bench::readBuffer<GpuBoid>(sim.currentStateBuffer(), size_t(n));
        int inArea = 0;
        for (int i = 0; i < active; ++i) {
            const GpuBoid& a = st[size_t(i)];
            if (std::abs(a.position.x) > halfArea) continue;
            ++inArea;
            const double vx = double(a.velocity.x) * toMs;
            sumV += vx;
            sumAbs += double(glm::length(glm::vec2(a.velocity))) * toMs;
            sumHalf[s * 2 / meas] += vx;
            countHalf[s * 2 / meas] += 1;
        }
        count += inArea;
        sumRhoArea += double(inArea) / areaM2;
        if (s % 50 == 0) {   // overlap spot check (all pairs; periodic minimum image)
            const float period = float(units::modelLength(sc.lengthM));
            for (int i = 0; i < active; ++i)
                for (int j = i + 1; j < active; ++j) {
                    glm::vec3 d = glm::vec3(st[size_t(i)].position) - glm::vec3(st[size_t(j)].position);
                    d.x -= period * std::round(d.x / period);
                    const float l = glm::length(d);
                    if (l < BODY_DIAM) maxOverlap = std::max(maxOverlap, double((BODY_DIAM - l) / BODY_DIAM));
                }
        }
    }
    FdPoint p;
    p.rho = rho;
    p.agents = active;
    p.speed = count > 0 ? sumV / count : 0.0;
    p.speedAbs = count > 0 ? sumAbs / count : 0.0;
    p.speedFirstHalf = countHalf[0] > 0 ? sumHalf[0] / countHalf[0] : 0.0;
    p.speedSecondHalf = countHalf[1] > 0 ? sumHalf[1] / countHalf[1] : 0.0;
    p.rhoArea = sumRhoArea / meas;
    p.flow = rho * p.speed;
    p.weidmann = weidmannSpeed(rho);
    p.overlapMax = maxOverlap;
    return p;
}

FdPoint measurePoint(const fs::path& shaderDir, GLuint sdfTex, const Scenario& sc, const Params& prm, double rho, bool verbose) {
    FdPoint p;
    const double k = 1.0 / double(sc.seeds.size());
    for (unsigned seed : sc.seeds) {
        const FdPoint q = measureSeed(shaderDir, sdfTex, sc, prm, rho, seed);
        p.rho = q.rho;
        p.agents = q.agents;
        p.weidmann = q.weidmann;
        p.speed += k * q.speed;
        p.speedAbs += k * q.speedAbs;
        p.speedFirstHalf += k * q.speedFirstHalf;
        p.speedSecondHalf += k * q.speedSecondHalf;
        p.rhoArea += k * q.rhoArea;
        p.flow += k * q.flow;
        p.overlapMax = std::max(p.overlapMax, q.overlapMax);
    }
    if (verbose)
        std::printf("  rho %4.2f: %4d agents, v %.3f m/s (halves %.3f / %.3f, |v| %.3f), area density %.2f, J %.3f p/(m s) = %.1f p/(m min), "
                    "Weidmann v %.3f, max overlap %.3f\n", rho, p.agents, p.speed, p.speedFirstHalf, p.speedSecondHalf, p.speedAbs, p.rhoArea,
                    p.flow, 60.0 * p.flow, p.weidmann, p.overlapMax);
    return p;
}

struct FdSummary { double rms = 0, maxFlow = 0, maxFlowRho = 0; int rmsPoints = 0; };
FdSummary summarize(const std::vector<FdPoint>& pts) {
    FdSummary s;
    double se = 0;
    for (const FdPoint& p : pts) {
        if (p.rho >= 0.5 - 1e-9 && p.rho <= 4.0 + 1e-9) { se += (p.speed - p.weidmann) * (p.speed - p.weidmann); ++s.rmsPoints; }
        if (p.flow > s.maxFlow) { s.maxFlow = p.flow; s.maxFlowRho = p.rho; }
    }
    s.rms = s.rmsPoints ? std::sqrt(se / s.rmsPoints) : 0.0;
    return s;
}

// Weidmann's maximum flow (dense scan)
std::pair<double, double> weidmannMaxFlow() {
    double best = 0, at = 0;
    for (double r = 0.05; r < WEIDMANN_RHO_MAX; r += 0.001) {
        const double j = r * weidmannSpeed(r);
        if (j > best) { best = j; at = r; }
    }
    return { best, at };
}

std::string runFolder(const fs::path& out, const std::string& name) {
    const fs::path dir = out / (name + "_" + bench::localTimestamp("%Y%m%d_%H%M"));
    fs::create_directories(dir);
    return dir.generic_string();
}

void writeFdCsv(const fs::path& file, const std::vector<FdPoint>& pts) {
    std::ofstream f(file);
    f << "rho_p_m2,agents,speed_m_s,speed_first_half_m_s,speed_second_half_m_s,abs_speed_m_s,area_density_p_m2,flow_p_m_s,flow_p_m_min,"
         "weidmann_speed_m_s,weidmann_flow_p_m_s,max_overlap_body_diam\n";
    for (const FdPoint& p : pts)
        f << p.rho << ',' << p.agents << ',' << p.speed << ',' << p.speedFirstHalf << ',' << p.speedSecondHalf << ',' << p.speedAbs << ','
          << p.rhoArea << ',' << p.flow << ',' << 60.0 * p.flow << ',' << p.weidmann << ',' << p.rho * p.weidmann << ',' << p.overlapMax << '\n';
}

std::string metaLine() {
    return "commit `" + bench::gitCommit() + "`, dirty " + bench::gitDirty() + ", " + std::string(buildinfo::buildConfig()) + "; " + bench::glRenderer() +
           ", " + bench::glDriver() + "; " + bench::localTimestamp("%Y-%m-%dT%H:%M:%S");
}

Scenario parseScenario(const bench::Args& a) {
    Scenario sc;
    sc.widthM = std::stod(a.get("width-m", "3"));
    sc.lengthM = std::stod(a.get("length-m", "50"));
    sc.warmupS = std::stod(a.get("warmup-s", "300"));
    sc.measureS = std::stod(a.get("measure-s", "300"));
    sc.seeds.clear();
    for (const std::string& t : bench::parseList(a.get("seeds", "7"))) sc.seeds.push_back(unsigned(std::stoul(t)));
    return sc;
}

std::string seedList(const Scenario& sc) {
    std::string r;
    for (unsigned v : sc.seeds) r += (r.empty() ? "" : ",") + std::to_string(v);
    return r;
}

std::vector<double> parseDoubles(const std::string& s) {
    std::vector<double> v;
    for (const std::string& t : bench::parseList(s)) v.push_back(std::stod(t));
    return v;
}

// rho 0.1 (15 agents): the free walking speed (V0 by construction)
const char* DEFAULT_DENSITIES = "0.1,0.5,1,1.5,2,2.5,3,3.5,4,5,6";

int cmdRun(const bench::Args& a) {
    Scenario sc = parseScenario(a);
    // The reference protocol's seeds by default (every stored FD reference uses 7, 8, 9: comparing a seed-7 run with them
    // mistakes the seed set's difference for a change of the model)
    if (!a.has("seeds")) sc.seeds = { 7, 8, 9 };
    Params prm;
    prm.ksep = std::stod(a.get("ksep", fmtNum(K_SEP)));
    prm.relax = std::stod(a.get("relax", fmtNum(PROJ_RELAX)));
    prm.theadway = std::stod(a.get("theadway", fmtNum(T_HEADWAY_S)));
    prm.iters = a.getInt("iters", PROJ_ITERATIONS);
    if (headwayModel(prm.theadway) * V_MAX + BODY_DIAM > R_PERC)
        std::printf("WARNING: R_PERC %.4f does not cover the look-ahead BODY_DIAM + V_MAX T_HEADWAY = %.4f\n", R_PERC,
                    BODY_DIAM + V_MAX * headwayModel(prm.theadway));
    const std::vector<double> dens = parseDoubles(a.get("densities", DEFAULT_DENSITIES));
    const fs::path out = a.get("out", "out/results/fd");
    const std::string name = a.get("name", "fd");
    bench::createHiddenContext("fd_harness");
    const GLuint sdf = loadSDFTexture3D(resolveAsset("stadium.sdf"));   // unused by the corridor; the pipeline binds it
    const fs::path shaders = shaderVariant(resolveAsset("shaders"), "run", corridorDefines(sc) + paramDefines(prm));
    std::printf("fd_harness run | %s\n  corridor %.2f x %.2f m (periodic in x), warm-up %.0f s, measured %.0f s, seeds %s, K_SEP %g, PROJ_RELAX %g, "
                "T_HEADWAY %g s, iterations %d\n", metaLine().c_str(), sc.widthM, sc.lengthM, sc.warmupS, sc.measureS, seedList(sc).c_str(), prm.ksep,
                prm.relax, prm.theadway, prm.iters);
    std::vector<FdPoint> pts;
    for (double rho : dens) pts.push_back(measurePoint(shaders, sdf, sc, prm, rho, true));
    fs::remove_all(shaders);
    const FdSummary s = summarize(pts);
    const auto [wJ, wRho] = weidmannMaxFlow();
    const std::string dir = runFolder(out, name);
    writeFdCsv(fs::path(dir) / "fd.csv", pts);
    std::ofstream md(fs::path(dir) / "summary.md");
    md << "# Fundamental diagram `" << name << "`\n\n" << metaLine() << ".\n\n";
    md << "Corridor " << sc.widthM << " m x " << sc.lengthM << " m, periodic in x, goal +x; warm-up " << sc.warmupS << " s, measured " << sc.measureS
       << " s (DT " << DT_REAL_S << " s), seeds " << seedList(sc) << " (mean over seeds); measurement area |x| <= " << MEASURE_HALF_M << " m, wall to wall. K_SEP " << prm.ksep << ", PROJ_RELAX "
       << prm.relax << ", T_HEADWAY " << prm.theadway << " s, projection iterations " << prm.iters << ".\n\n";
    md << "| rho [p/m^2] | agents | v [m/s] | v halves [m/s] | area density | J [p/(m s)] | J [p/(m min)] | Weidmann v | Weidmann J [p/(m min)] | max overlap |\n";
    md << "|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|\n";
    for (const FdPoint& p : pts)
        md << std::fixed << std::setprecision(3) << "| " << p.rho << " | " << p.agents << " | " << p.speed << " | " << p.speedFirstHalf << " / " << p.speedSecondHalf
           << " | " << p.rhoArea << " | " << p.flow << " | " << std::setprecision(1) << 60.0 * p.flow << " | " << std::setprecision(3) << p.weidmann << " | "
           << std::setprecision(1) << 60.0 * p.rho * p.weidmann << " | " << std::setprecision(3) << p.overlapMax << " |\n";
    md << std::defaultfloat << "\nRMS speed error vs Weidmann over rho in [0.5, 4] (" << s.rmsPoints << " points): **" << std::setprecision(4) << s.rms
       << " m/s**. Max flow: model **" << std::setprecision(4) << 60.0 * s.maxFlow << " p/(m min)** at rho " << s.maxFlowRho << "; Weidmann " << 60.0 * wJ
       << " p/(m min) at rho " << wRho << "; Fruin ~" << FRUIN_FLOW_P_M_MIN << " p/(m min).\n\n"
       << "Weidmann (1993): v(rho) = 1.34 (1 - exp(-1.913 (1/rho - 1/5.4))) m/s (as reported there; not yet checked against the original).\n";
    std::printf("  RMS speed error (rho 0.5-4): %.4f m/s; max flow %.1f p/(m min) at rho %.2f (Weidmann %.1f at %.2f, Fruin ~%.0f)\n  -> %s\n", s.rms,
                60.0 * s.maxFlow, s.maxFlowRho, 60.0 * wJ, wRho, FRUIN_FLOW_P_M_MIN, dir.c_str());
    return 0;
}

// Evacuation steps of the N = 4096 terrace evacuation from 'spawn' (50%, 90%, 100% evacuated; 0: not reached)
struct EvacSteps { int s50 = 0, s90 = 0, s100 = 0; };
EvacSteps evacuate(const fs::path& shaders, GLuint sdf, const std::vector<GpuBoid>& spawn, int iters, int maxSteps) {
    const int n = int(spawn.size());
    CrowdSim sim(shaders, n);
    sim.setProjectionIterations(iters);
    sim.upload(spawn);
    EvacSteps e;
    for (int s = 1; s <= maxSteps; ++s) {
        sim.step(sdf);
        const std::vector<GpuBoid> st = bench::readBuffer<GpuBoid>(sim.currentStateBuffer(), size_t(n));
        int active = 0;
        for (const GpuBoid& b : st) active += b.position.w != 0.0f;
        if (!e.s50 && active <= n / 2) e.s50 = s;
        if (!e.s90 && active <= n / 10) e.s90 = s;
        if (active == 0) { e.s100 = s; break; }
    }
    return e;
}

std::string dtDefines(int div) { return div > 1 ? "#undef DT\n#define DT " + glslFloatLiteral(DT / float(div)) + "\n" : std::string(); }

// Relative change of an evacuation time from DT (steps a) to DT/2 (steps b): (b DT/2 - a DT) / (a DT)
double dtChange(int a, int b) { return a > 0 && b > 0 ? (0.5 * b - a) / double(a) : 1e9; }

struct GridRow {
    Params prm;
    FdSummary fd;
    std::vector<FdPoint> pts;
    plausibility::Result ev;
    EvacSteps half;   // the evacuation at DT / 2
    double wallS = 0;
    double dt100() const { return dtChange(ev.evacStep, half.s100); }
    double dt50() const { return dtChange(ev.s50, half.s50); }
    double dt90() const { return dtChange(ev.s90, half.s90); }
    bool dtOk() const { return std::abs(dt100()) <= DT_CHANGE_LIMIT; }
    bool flowOk(double weidmannMax) const { return std::abs(fd.maxFlow / weidmannMax - 1.0) <= FLOW_TOLERANCE; }
    bool rmsOk() const { return fd.rms <= RMS_TARGET; }
    // Every plausibility check except the overlap targets, with a complete evacuation
    bool hardOk() const { return ev.evacStep > 0 && !ev.nan && ev.gridOk() && ev.floorOk() && ev.fenceOk() && ev.wallOk() && ev.speedOk() && ev.densityOk(); }
    bool feasible(double weidmannMax) const { return ev.allOk() && dtOk() && flowOk(weidmannMax); }
    // Compromise rank when no row is feasible: the plausibility checks other than the overlap targets first (a complete,
    // physically valid evacuation), then the number of missed criteria (overlap targets, DT, flow, RMS target), then the
    // RMS
    std::tuple<int, int, double> rank(double weidmannMax) const {
        return { hardOk() ? 0 : 1, int(!ev.overlapOk()) + int(!dtOk()) + int(!flowOk(weidmannMax)) + int(!rmsOk()), fd.rms };
    }
    std::string misses(double weidmannMax) const {
        std::string m;
        auto add = [&](bool ok, const char* what) { if (!ok) m += (m.empty() ? "" : ", ") + std::string(what); };
        add(ev.evacStep > 0, "evacuation");
        add(!ev.nan, "NaN");
        add(ev.overlapOk(), "overlap");
        add(ev.gridOk(), "grid");
        add(ev.floorOk(), "floor");
        add(ev.fenceOk(), "fence");
        add(ev.wallOk(), "wall");
        add(ev.speedOk(), "speed");
        add(ev.densityOk(), "density");
        add(dtOk(), "DT");
        add(flowOk(weidmannMax), "flow");
        add(rmsOk(), "RMS target");
        return m.empty() ? "-" : m;
    }
};

int cmdCalibrate(const bench::Args& a) {
    const Scenario sc = parseScenario(a);
    const std::vector<double> ksepGrid = parseDoubles(a.get("ksep-grid", fmtNum(K_SEP)));
    const std::vector<double> relaxGrid = parseDoubles(a.get("relax-grid", fmtNum(PROJ_RELAX)));
    const std::vector<double> headwayGrid = parseDoubles(a.get("theadway-grid", fmtNum(T_HEADWAY_S)));
    const std::vector<double> dens = parseDoubles(a.get("densities", DEFAULT_DENSITIES));
    const int iters = a.getInt("iters", PROJ_ITERATIONS);
    const fs::path out = a.get("out", "out/results/fd");
    const std::string name = a.get("name", "calibration");
    for (double th : headwayGrid)
        if (headwayModel(th) * V_MAX + BODY_DIAM > R_PERC)
            throw std::runtime_error("R_PERC does not cover the headway look-ahead at T_HEADWAY " + fmtShort(th) + " s");
    bench::createHiddenContext("fd_harness");
    const GLuint sdf = loadSDFTexture3D(resolveAsset("stadium.sdf"));
    const metrics::MetricVenue venue = metrics::computeMetricVenue(sdfVolumeCPU());
    const std::vector<GpuMetricCellInfo> info = venue.cellInfo();
    const std::vector<GpuBoid> spawn = spawnBleacherCrowd(4096);
    const std::string dir = runFolder(out, name);
    const auto [wJ, wRho] = weidmannMaxFlow();
    std::ofstream grid(fs::path(dir) / "grid.csv");
    grid << "k_sep,proj_relax,t_headway_s,iterations,rms_m_s,max_flow_p_m_min,max_flow_rho";
    for (double r : dens) grid << ",v_" << r;
    grid << ",evac_step,evac_s,s50,s90,dt2_s50,dt2_s90,dt2_s100,dt_change_t50,dt_change_t90,dt_change_t100,overlap_p50,overlap_p99,overlap_max,"
            "peak_density,overlap_ok,grid_ok,floor_ok,fence_ok,wall_ok,speed_ok,density_ok,plausible,dt_ok,flow_ok,rms_ok,feasible,wall_s\n";
    std::printf("fd_harness calibrate | %s\n", metaLine().c_str());
    std::vector<GridRow> rows;
    for (double ks : ksepGrid)
        for (double rl : relaxGrid)
            for (double th : headwayGrid) {
                const auto t0 = bench::Clock::now();
                GridRow row;
                row.prm.ksep = ks;
                row.prm.relax = rl;
                row.prm.theadway = th;
                row.prm.iters = iters;
                const fs::path fdShaders = shaderVariant(resolveAsset("shaders"), "cal_fd", corridorDefines(sc) + paramDefines(row.prm));
                for (double rho : dens) row.pts.push_back(measurePoint(fdShaders, sdf, sc, row.prm, rho, false));
                fs::remove_all(fdShaders);
                row.fd = summarize(row.pts);
                const fs::path stShaders = shaderVariant(resolveAsset("shaders"), "cal_stadium", paramDefines(row.prm));
                {
                    CrowdSim sim(stShaders, 4096);
                    sim.setProjectionIterations(iters);
                    sim.upload(spawn);
                    metrics::CrowdMetrics gm(stShaders, 4096, info);
                    row.ev = plausibility::runEvacuation(sim, sdf, spawn, gm, info, 6000);
                }
                fs::remove_all(stShaders);
                const fs::path halfShaders = shaderVariant(resolveAsset("shaders"), "cal_dt2", paramDefines(row.prm) + dtDefines(2));
                row.half = evacuate(halfShaders, sdf, spawn, iters, 12000);
                fs::remove_all(halfShaders);
                row.ev.depths.clear();
                row.ev.depths.shrink_to_fit();
                row.wallS = bench::msSince(t0) / 1000.0;
                const plausibility::Result& r = row.ev;
                grid << ks << ',' << rl << ',' << th << ',' << iters << ',' << row.fd.rms << ',' << 60.0 * row.fd.maxFlow << ',' << row.fd.maxFlowRho;
                for (const FdPoint& p : row.pts) grid << ',' << p.speed;
                grid << ',' << r.evacStep << ',' << (r.evacStep > 0 ? r.evacStep * DT_REAL_S : -1.0) << ',' << r.s50 << ',' << r.s90 << ',' << row.half.s50
                     << ',' << row.half.s90 << ',' << row.half.s100 << ',' << row.dt50() << ',' << row.dt90() << ',' << row.dt100() << ',' << r.p50 << ','
                     << r.p99 << ',' << r.maxDepth << ',' << r.peakFull << ',' << r.overlapOk() << ',' << r.gridOk() << ',' << r.floorOk() << ','
                     << r.fenceOk() << ',' << r.wallOk() << ',' << r.speedOk() << ',' << r.densityOk() << ',' << r.allOk() << ',' << row.dtOk() << ','
                     << row.flowOk(wJ) << ',' << row.rmsOk() << ',' << row.feasible(wJ) << ',' << row.wallS << '\n';
                grid.flush();
                std::printf("  K_SEP %6.2f relax %.2f T %.2f s: RMS %.4f m/s, max flow %.1f p/(m min) at %.1f | evac %d (%.1f s), DT/2 %+.2f%%, overlap p99 "
                            "%.4f max %.3f, peak %.2f | %s (%.0f s)\n", ks, rl, th, row.fd.rms, 60.0 * row.fd.maxFlow, row.fd.maxFlowRho, r.evacStep,
                            r.evacStep * DT_REAL_S, 100.0 * row.dt100(), r.p99, r.maxDepth, r.peakFull,
                            row.feasible(wJ) ? "feasible" : ("misses: " + row.misses(wJ)).c_str(), row.wallS);
                std::fflush(stdout);
                rows.push_back(std::move(row));
            }
    // Selection: the smallest RMS among the feasible rows; if there is none, the best compromise (GridRow::rank)
    int best = -1, compromise = 0;
    for (int i = 0; i < int(rows.size()); ++i) {
        if (rows[size_t(i)].feasible(wJ) && (best < 0 || rows[size_t(i)].fd.rms < rows[size_t(best)].fd.rms)) best = i;
        if (rows[size_t(i)].rank(wJ) < rows[size_t(compromise)].rank(wJ)) compromise = i;
    }
    const int chosen = best >= 0 ? best : compromise;
    std::ofstream md(fs::path(dir) / "summary.md");
    md << "# Calibration grid `" << name << "`\n\n" << metaLine() << ".\n\nCorridor " << sc.widthM << " x " << sc.lengthM << " m, warm-up " << sc.warmupS
       << " s, measured " << sc.measureS << " s per density (seeds " << seedList(sc) << "); projection iterations " << iters << ". Objective: RMS of the model's "
       << "speed minus Weidmann's over rho in [0.5, 4] (target <= " << RMS_TARGET << " m/s). Hard constraints (feasible): the N = 4096 terrace evacuation "
       << "completes and passes every plausibility check (tools/plausibility.hpp, the limits of test_gpu validation.plausibility_terrace); its t100 changes by at most "
       << 100.0 * DT_CHANGE_LIMIT << "% from DT to DT/2; the maximum flow is within +-" << 100.0 * FLOW_TOLERANCE << "% of Weidmann's " << std::setprecision(4)
       << 60.0 * wJ << " p/(m min) (at rho " << wRho << "). Fruin ~" << FRUIN_FLOW_P_M_MIN << " p/(m min). Raw rows: grid.csv.\n\n";
    md << "| K_SEP | relax | T [s] | RMS [m/s] |";
    for (double r : dens) md << " v(" << r << ") |";
    md << " max J [p/(m min)] at rho | evac step (s) | t100 / t50 / t90 DT -> DT/2 | overlap p50 / p99 / max | peak density | misses |\n|---:|---:|---:|---:|";
    for (size_t i = 0; i < dens.size(); ++i) md << "---:|";
    md << "---|---|---|---|---:|---|\n";
    for (int i = 0; i < int(rows.size()); ++i) {
        const GridRow& g = rows[size_t(i)];
        const plausibility::Result& r = g.ev;
        md << std::fixed << "| " << std::setprecision(2) << g.prm.ksep << " | " << g.prm.relax << " | " << g.prm.theadway << " | " << std::setprecision(4)
           << g.fd.rms << (i == chosen ? (best >= 0 ? " **(chosen)**" : " **(compromise)**") : "") << " |";
        for (const FdPoint& p : g.pts) md << ' ' << std::setprecision(3) << p.speed << " |";
        md << ' ' << std::setprecision(1) << 60.0 * g.fd.maxFlow << " at " << g.fd.maxFlowRho << " | " << r.evacStep << " (" << r.evacStep * DT_REAL_S << ") | "
           << std::setprecision(2) << std::showpos << 100.0 * g.dt100() << "% / " << 100.0 * g.dt50() << "% / " << 100.0 * g.dt90() << "%" << std::noshowpos
           << " | " << std::setprecision(4) << r.p50 << " / " << r.p99 << " / " << r.maxDepth << " | " << std::setprecision(2) << r.peakFull << " | "
           << g.misses(wJ) << " |\n";
    }
    md << std::defaultfloat << std::setprecision(6) << "\n";
    const GridRow& c = rows[size_t(chosen)];
    if (best >= 0)
        md << "Chosen (smallest RMS among the feasible rows): ";
    else
        md << "**No row meets every constraint.** Best compromise (every plausibility check but the overlap targets first, then the fewest "
              "missed criteria among overlap targets, DT, flow and RMS target, then RMS): ";
    md << "K_SEP " << c.prm.ksep << ", PROJ_RELAX " << c.prm.relax << ", T_HEADWAY " << c.prm.theadway << " s: RMS " << c.fd.rms << " m/s, max flow "
       << 60.0 * c.fd.maxFlow << " p/(m min), t100 DT -> DT/2 " << 100.0 * c.dt100() << "%; misses: " << c.misses(wJ) << ".\n";
    std::printf("  %s: K_SEP %g, PROJ_RELAX %g, T_HEADWAY %g s (misses: %s)\n  -> %s\n", best >= 0 ? "chosen" : "NO FEASIBLE ROW, compromise",
                c.prm.ksep, c.prm.relax, c.prm.theadway, c.misses(wJ).c_str(), dir.c_str());
    return 0;
}

// DT convergence of the N = 4096 terrace evacuation for parameter variants (the method of test_gpu validation.dt_convergence_terrace:
// DT, DT/2, DT/4 by a preamble override; the evacuation times in model units at each)
int cmdDtCheck(const bench::Args& a) {
    const std::vector<double> ksepGrid = parseDoubles(a.get("ksep-grid", fmtNum(K_SEP)));
    const std::vector<double> relaxGrid = parseDoubles(a.get("relax-grid", fmtNum(PROJ_RELAX)));
    const std::vector<double> headwayGrid = parseDoubles(a.get("theadway-grid", fmtNum(T_HEADWAY_S)));
    const int iters = a.getInt("iters", PROJ_ITERATIONS);
    bench::createHiddenContext("fd_harness");
    const GLuint sdf = loadSDFTexture3D(resolveAsset("stadium.sdf"));
    const std::vector<GpuBoid> spawn = spawnBleacherCrowd(4096);
    std::printf("fd_harness dtcheck | %s\n", metaLine().c_str());
    for (double ks : ksepGrid)
        for (double rl : relaxGrid)
            for (double th : headwayGrid) {
                Params prm;
                prm.ksep = ks;
                prm.relax = rl;
                prm.theadway = th;
                prm.iters = iters;
                EvacSteps e[3];
                for (int v = 0; v < 3; ++v) {
                    const int div = 1 << v;
                    const fs::path dir = shaderVariant(resolveAsset("shaders"), "dtcheck", paramDefines(prm) + dtDefines(div));
                    e[v] = evacuate(dir, sdf, spawn, iters, 6000 * div);
                    fs::remove_all(dir);
                }
                std::printf("  K_SEP %g relax %g T_HEADWAY %g s (iterations %d):\n", ks, rl, th, iters);
                for (int q = 0; q < 3; ++q) {
                    auto steps = [&](int v) { return q == 0 ? e[v].s50 : q == 1 ? e[v].s90 : e[v].s100; };
                    const double t0 = steps(0) * double(DT), t1 = steps(1) * double(DT) / 2.0, t2 = steps(2) * double(DT) / 4.0;
                    std::printf("    t%-3d steps %d / %d / %d at DT, DT/2, DT/4 = t %.3f / %.3f / %.3f (%.1f / %.1f / %.1f s): DT -> DT/2 %+.2f%%, "
                                "DT/2 -> DT/4 %+.2f%%\n", q == 0 ? 50 : q == 1 ? 90 : 100, steps(0), steps(1), steps(2), t0, t1, t2, units::seconds(t0),
                                units::seconds(t1), units::seconds(t2), 100.0 * (t1 - t0) / t0, 100.0 * (t2 - t1) / t1);
                }
                std::fflush(stdout);
            }
    return 0;
}

// Projection iteration sweep. Per K in --iters-list: the N = 4096 terrace evacuation from spawn with
// every plausibility check (tools/plausibility.hpp; overlap depths split into crowd and venue-geometry cases), t50 / t90
// / t100 and the peak density per zone; the FD at --densities with --seeds (the RMS criterion over --rms-densities).
// Selection rule (fixed before the run): the smallest K with crowd-case overlap p99 <= KSWEEP_CROWD_P99 and max <=
// KSWEEP_CROWD_MAX of BODY_DIAM, t100 and the FD RMS each within KSWEEP_REL_TOL of the reference K (--ref, the
// production PROJ_ITERATIONS), and every other plausibility check passing (complete evacuation, no NaN, grid, floors,
// fence, walls, speed, density). The GPU cost per K is measured separately on a quiet GPU (tools/perf_ab, bench cell
// with SWARM_BENCH_PROJ_ITERS), never here.
constexpr double KSWEEP_CROWD_P99 = 0.05, KSWEEP_CROWD_MAX = 0.20, KSWEEP_REL_TOL = 0.02;

int cmdKSweep(const bench::Args& a) {
    Scenario sc = parseScenario(a);
    if (!a.has("seeds")) sc.seeds = { 7, 8, 9 };
    std::vector<int> itersList;
    for (const std::string& t : bench::parseList(a.get("iters-list", "0,1,2,4,8,16,32"))) itersList.push_back(std::stoi(t));
    const int ref = a.getInt("ref", PROJ_ITERATIONS);
    if (std::find(itersList.begin(), itersList.end(), ref) == itersList.end()) throw std::runtime_error("--iters-list must contain --ref");
    const std::vector<double> dens = parseDoubles(a.get("densities", "0.5,1,1.5,2,2.5,3,3.5,4"));
    const std::vector<double> rmsDens = parseDoubles(a.get("rms-densities", "1,2,3,4"));
    const int maxSteps = a.getInt("max-steps", 12000);
    const fs::path out = a.get("out", "out/results/fd");
    const std::string name = a.get("name", "ksweep");
    bench::createHiddenContext("fd_harness");
    const GLuint sdf = loadSDFTexture3D(resolveAsset("stadium.sdf"));
    const metrics::MetricVenue venue = metrics::computeMetricVenue(sdfVolumeCPU());
    const std::vector<GpuMetricCellInfo> info = venue.cellInfo();
    const std::vector<GpuBoid> spawn = spawnBleacherCrowd(4096);
    const std::string dir = runFolder(out, name);
    std::printf("fd_harness ksweep | %s\n  K %s, reference K %d; FD: densities %s, RMS over %s, seeds %s, warm-up %.0f s, measured %.0f s\n",
                metaLine().c_str(), a.get("iters-list", "0,1,2,4,8,16,32").c_str(), ref, a.get("densities", "0.5,...,4").c_str(),
                a.get("rms-densities", "1,2,3,4").c_str(), seedList(sc).c_str(), sc.warmupS, sc.measureS);
    namespace pl = plausibility;
    struct Row {
        int k = 0;
        pl::Result ev;
        pl::DepthStats all, crowd, venueCases, fall, ramp;
        std::vector<FdPoint> pts;
        double rms = 0, rmsAll = 0;   // over rmsDens, over 0.5-4 (the production objective)
        double wallS = 0;
        bool hardOk() const {
            return ev.evacStep > 0 && !ev.nan && ev.gridOk() && ev.floorOk() && ev.fenceOk() && ev.wallOk() && ev.speedOk() && ev.densityOk();
        }
        bool crowdOk() const { return crowd.p99 <= KSWEEP_CROWD_P99 && crowd.max <= KSWEEP_CROWD_MAX; }
    };
    std::vector<Row> rows;
    for (int k : itersList) {
        const auto t0 = bench::Clock::now();
        Row row;
        row.k = k;
        {
            CrowdSim sim(resolveAsset("shaders"), 4096);
            sim.setProjectionIterations(k);
            sim.upload(spawn);
            metrics::CrowdMetrics gm(resolveAsset("shaders"), 4096, info);
            row.ev = pl::runEvacuation(sim, sdf, spawn, gm, info, maxSteps);
        }
        row.all = pl::depthStats(row.ev.depths);
        row.crowd = row.ev.overlapCase(pl::CASE_CROWD);
        row.venueCases = row.ev.overlapVenue();
        row.fall = row.ev.overlapCase(pl::CASE_FALL);
        row.ramp = row.ev.overlapCase(pl::CASE_RAMP);
        std::printf("\n  K = %d:\n", k);
        pl::print(row.ev, "    ");
        pl::printOverlapCases(row.ev, "    ");
        Params prm;
        prm.iters = k;
        const fs::path fdShaders = shaderVariant(resolveAsset("shaders"), "ksweep_fd", corridorDefines(sc) + paramDefines(prm));
        for (double rho : dens) row.pts.push_back(measurePoint(fdShaders, sdf, sc, prm, rho, true));
        fs::remove_all(fdShaders);
        double se = 0, seAll = 0;
        int nr = 0, nAll = 0;
        for (const FdPoint& p : row.pts) {
            const double e2 = (p.speed - p.weidmann) * (p.speed - p.weidmann);
            for (double r : rmsDens)
                if (std::abs(p.rho - r) < 1e-9) { se += e2; ++nr; }
            if (p.rho >= 0.5 - 1e-9 && p.rho <= 4.0 + 1e-9) { seAll += e2; ++nAll; }
        }
        if (nr != int(rmsDens.size())) throw std::runtime_error("--rms-densities must be a subset of --densities");
        row.rms = std::sqrt(se / nr);
        row.rmsAll = nAll ? std::sqrt(seAll / nAll) : 0.0;
        row.wallS = bench::msSince(t0) / 1000.0;
        row.ev.depths.clear();
        row.ev.depths.shrink_to_fit();
        for (auto& c : row.ev.caseDepths)
            for (auto& z : c) { z.clear(); z.shrink_to_fit(); }
        std::printf("    t50 / t90 / t100 = %.1f / %.1f / %.1f s; FD RMS (rho %s) %.4f m/s, (0.5-4) %.4f m/s; crowd p99 %.4f max %.4f; plausibility "
                    "(except overlap) %s (%.0f s)\n", row.ev.s50 * DT_REAL_S, row.ev.s90 * DT_REAL_S, row.ev.evacStep * DT_REAL_S,
                    a.get("rms-densities", "1,2,3,4").c_str(), row.rms, row.rmsAll, row.crowd.p99, row.crowd.max, row.hardOk() ? "pass" : "FAIL", row.wallS);
        std::fflush(stdout);
        rows.push_back(std::move(row));
    }
    const Row* refRow = nullptr;
    for (const Row& r : rows)
        if (r.k == ref) refRow = &r;
    auto rel = [](double v, double r) { return r != 0.0 ? v / r - 1.0 : 1e9; };
    auto t100Ok = [&](const Row& r) { return r.ev.evacStep > 0 && std::abs(rel(r.ev.evacStep, refRow->ev.evacStep)) <= KSWEEP_REL_TOL; };
    auto rmsOk = [&](const Row& r) { return std::abs(rel(r.rms, refRow->rms)) <= KSWEEP_REL_TOL; };
    auto meets = [&](const Row& r) { return r.crowdOk() && t100Ok(r) && rmsOk(r) && r.hardOk(); };
    const Row* chosen = nullptr;
    for (const Row& r : rows)
        if (meets(r) && (!chosen || r.k < chosen->k)) chosen = &r;

    namespace mt = metrics;
    std::ofstream csv(fs::path(dir) / "ksweep.csv");
    csv << "iterations,evac_step,t50_s,t90_s,t100_s,t100_rel_ref,overlap_pairs,all_p50,all_p99,all_max,crowd_pairs,crowd_p50,crowd_p99,crowd_max,"
           "crowd_above5,crowd_above20,venue_pairs,venue_p99,venue_max,fall_pairs,fall_p99,fall_max,ramp_pairs,ramp_p99,ramp_max,mean_overlapping_agents";
    for (int z = 0; z < mt::ZONE_COUNT; ++z) csv << ",peak_" << mt::zoneName(uint32_t(z));
    csv << ",peak_full_cells,max_displacement,grid_misses,floor_violations,in_solid,fence_crossings,fence_band,wall_violations,speed_violations,airborne_runs";
    for (double r : dens) csv << ",v_" << r;
    csv << ",fd_rms,fd_rms_rel_ref,fd_rms_0p5_4,crowd_ok,t100_ok,rms_ok,plausible_except_overlap,meets_all,wall_s\n";
    for (const Row& r : rows) {
        const pl::Result& e = r.ev;
        csv << r.k << ',' << e.evacStep << ',' << e.s50 * DT_REAL_S << ',' << e.s90 * DT_REAL_S << ',' << e.evacStep * DT_REAL_S << ','
            << rel(e.evacStep, refRow->ev.evacStep) << ',' << r.all.n << ',' << r.all.p50 << ',' << r.all.p99 << ',' << r.all.max << ',' << r.crowd.n
            << ',' << r.crowd.p50 << ',' << r.crowd.p99 << ',' << r.crowd.max << ',' << r.crowd.above5 << ',' << r.crowd.above20 << ','
            << r.venueCases.n << ',' << r.venueCases.p99 << ',' << r.venueCases.max << ',' << r.fall.n << ',' << r.fall.p99 << ',' << r.fall.max << ','
            << r.ramp.n << ',' << r.ramp.p99 << ',' << r.ramp.max << ',' << e.meanOverlappingAgents;
        for (int z = 0; z < mt::ZONE_COUNT; ++z) csv << ',' << e.peakZone[z];
        csv << ',' << e.peakFull << ',' << e.maxDisplacement << ',' << e.gridMisses << ',' << e.floorViolations << ',' << e.centreInSolid << ','
            << e.fenceCrossings << ',' << e.fenceBand << ',' << e.wallViolations << ',' << e.speedViolations << ',' << e.airborneRuns;
        for (const FdPoint& p : r.pts) csv << ',' << p.speed;
        csv << ',' << r.rms << ',' << rel(r.rms, refRow->rms) << ',' << r.rmsAll << ',' << r.crowdOk() << ',' << t100Ok(r) << ',' << rmsOk(r) << ','
            << r.hardOk() << ',' << meets(r) << ',' << r.wallS << '\n';
    }
    std::ofstream md(fs::path(dir) / "summary.md");
    md << "# Projection iteration sweep `" << name << "`\n\n" << metaLine() << ".\n\nN = 4096 terrace evacuation from spawn per K (production "
       << "shaders, CrowdSim::setProjectionIterations), every plausibility check of tools/plausibility.hpp after every step; overlap depth / "
       << "BODY_DIAM over the pair-steps above " << pl::OVERLAP_NOISE << ", split into crowd (both agents steadily grounded on walkable floor) and "
       << "venue-geometry cases (fall: airborne within " << pl::AIRBORNE_MEMORY << " steps; ramp: floor n_z < " << pl::RAMP_NZ << "). FD: corridor "
       << sc.widthM << " x " << sc.lengthM << " m, seeds " << seedList(sc) << ", warm-up " << sc.warmupS << " s, measured " << sc.measureS
       << " s; RMS vs Weidmann over rho " << a.get("rms-densities", "1,2,3,4") << " (and over 0.5-4, the calibration's objective). Reference K = " << ref
       << ". Rule: the smallest K with crowd p99 <= " << KSWEEP_CROWD_P99 << ", crowd max <= " << KSWEEP_CROWD_MAX << ", t100 and FD RMS within "
       << 100.0 * KSWEEP_REL_TOL << "% of the reference, every other plausibility check passing. Raw: ksweep.csv.\n\n";
    md << std::fixed;
    md << "| K | t50 / t90 / t100 [s] | t100 vs ref | overlap all p99 / max | crowd pairs, p99 / max | venue pairs, p99 / max | fall p99 / max | "
          "ramp p99 / max | peak tread / aisle / walkway / avenue / exit [p/m^2] |";
    for (double r : dens) md << " v(" << std::setprecision(1) << r << ") |";
    md << " RMS (" << a.get("rms-densities", "1,2,3,4") << ") | vs ref | RMS (0.5-4) | other checks | meets |\n|---:|---|---:|---|---|---|---|---|---|";
    for (size_t i = 0; i < dens.size(); ++i) md << "---:|";
    md << "---:|---:|---:|---|---|\n";
    for (const Row& r : rows) {
        const pl::Result& e = r.ev;
        md << "| " << r.k << (chosen == &r ? " **(chosen)**" : "") << " | " << std::setprecision(1) << e.s50 * DT_REAL_S << " / " << e.s90 * DT_REAL_S
           << " / " << e.evacStep * DT_REAL_S << " | " << std::showpos << std::setprecision(2) << 100.0 * rel(e.evacStep, refRow->ev.evacStep) << "%"
           << std::noshowpos << std::setprecision(4) << " | " << r.all.p99 << " / " << r.all.max << " | " << r.crowd.n << ", " << r.crowd.p99 << " / "
           << r.crowd.max << " | " << r.venueCases.n << ", " << r.venueCases.p99 << " / " << r.venueCases.max << " | " << r.fall.p99 << " / " << r.fall.max
           << " | " << r.ramp.p99 << " / " << r.ramp.max << " | " << std::setprecision(2) << e.peakZone[mt::ZONE_TREAD] << " / "
           << e.peakZone[mt::ZONE_AISLE] << " / " << e.peakZone[mt::ZONE_WALKWAY] << " / " << e.peakZone[mt::ZONE_AVENUE] << " / "
           << e.peakZone[mt::ZONE_EXIT] << " |";
        for (const FdPoint& p : r.pts) md << ' ' << std::setprecision(3) << p.speed << " |";
        md << ' ' << std::setprecision(4) << r.rms << " | " << std::showpos << std::setprecision(2) << 100.0 * rel(r.rms, refRow->rms) << "%"
           << std::noshowpos << " | " << std::setprecision(4) << r.rmsAll << " | " << (r.hardOk() ? "pass" : "FAIL") << " | "
           << (meets(r) ? "yes" : "no") << " |\n";
    }
    md << std::defaultfloat << "\n";
    if (chosen)
        md << "Chosen: **K = " << chosen->k << "** (the smallest K meeting every criterion).\n";
    else
        md << "**No K meets every criterion.**\n";
    std::printf("\n  %s\n  -> %s\n", chosen ? ("chosen K = " + std::to_string(chosen->k)).c_str() : "NO K MEETS EVERY CRITERION", dir.c_str());
    return 0;
}

// Mutual-standoff tie-break activations over the N = 4096 terrace evacuation: per step the counters of
// tools/tiebreak.hpp (the predict pass built with DIAG_TIEBREAK) and the active agents, into tiebreak.csv and summary.md.
// A production run from the same spawn proves that the instrumented run is the
// production run bit for bit (plausibility::chainHash over every step's state).
int cmdTieBreak(const bench::Args& a) {
    namespace tb = tiebreak;
    const int maxSteps = a.getInt("max-steps", 12000);
    const fs::path out = a.get("out", "out/results/fd");
    const std::string name = a.get("name", "tiebreak");
    bench::createHiddenContext("fd_harness");
    const GLuint sdf = loadSDFTexture3D(resolveAsset("stadium.sdf"));
    const std::vector<GpuBoid> spawn = spawnBleacherCrowd(4096);
    const int n = int(spawn.size());
    std::printf("fd_harness tiebreak | %s\n", metaLine().c_str());
    const fs::path diag = shaderVariant(resolveAsset("shaders"), "tiebreak", tb::DEFINE);
    const tb::Run t = tb::run(diag, sdf, spawn, maxSteps);
    fs::remove_all(diag);
    uint64_t prodHash = 0xcbf29ce484222325ull;
    int prodEvac = -1;
    {
        CrowdSim sim(resolveAsset("shaders"), n);
        sim.upload(spawn);
        for (int s = 1; s <= maxSteps; ++s) {
            sim.step(sdf);
            const std::vector<GpuBoid> st = bench::readBuffer<GpuBoid>(sim.currentStateBuffer(), size_t(n));
            plausibility::chainHash(prodHash, st);
            int active = 0;
            for (const GpuBoid& b : st) active += b.position.w != 0.0f;
            if (active == 0) { prodEvac = s; break; }
        }
    }
    const bool identical = prodHash == t.trajectoryHash && prodEvac == t.evacStep;
    int s50 = 0, s90 = 0;
    for (size_t k = 0; k < t.active.size(); ++k) {
        if (!s50 && t.active[k] <= n / 2) s50 = int(k) + 1;
        if (!s90 && t.active[k] <= n / 10) s90 = int(k) + 1;
    }
    uint64_t agentSteps = 0;
    for (int v : t.active) agentSteps += uint64_t(v);
    const std::string dir = runFolder(out, name);
    std::ofstream csv(fs::path(dir) / "tiebreak.csv");
    csv << "step,time_s,active,mutual_candidates,standoffs,ties,leader_changed,vdes_changed,released\n";
    for (size_t k = 0; k < t.perStep.size(); ++k) {
        csv << k + 1 << ',' << double(k + 1) * DT_REAL_S << ',' << t.active[k];
        for (uint32_t c : t.perStep[k]) csv << ',' << c;
        csv << '\n';
    }
    // Totals per evacuation phase: up to t50, t50-t90, t90-t100
    auto phaseTotal = [&](int c, int from, int to) {
        uint64_t s = 0;
        for (int k = from; k < to && k < int(t.perStep.size()); ++k) s += t.perStep[size_t(k)][size_t(c)];
        return s;
    };
    std::ofstream md(fs::path(dir) / "summary.md");
    md << "# Mutual-standoff tie-break activations `" << name << "`\n\n" << metaLine() << ".\n\nN = 4096 terrace evacuation from spawn, the "
       << "predict pass built with DIAG_TIEBREAK (tools/tiebreak.hpp; counters per step, raw: tiebreak.csv). Evacuated at step " << t.evacStep
       << " (" << std::fixed << std::setprecision(1) << t.evacStep * DT_REAL_S << " s); t50 / t90 at steps " << s50 << " / " << s90 << "; "
       << agentSteps << " agent-steps. The instrumented run is the production run bit for bit (chained state hash of every step, "
       << "evacuation step): **" << (identical ? "yes" : "NO") << "**.\n\n";
    md << "A standoff: two agents each ahead in the other's lane (along the other's own e_goal); the tie-break lets only the one that "
          "has the other more directly ahead count it as its leader (ties: the larger boidID). 'Standoffs resolved' counts one "
          "activation per standoff pair and step; the agent counts compare the headway with the literal rule's (without the "
          "tie-break) for the same state.\n\n";
    md << "| counter | total | per agent-step | max per step (step) | steps with any | mean per step | up to t50 | t50-t90 | t90-t100 |\n"
          "|---|---:|---:|---|---:|---:|---:|---:|---:|\n";
    for (int c = 0; c < tb::COUNTERS; ++c) {
        int at = 0;
        const uint32_t mx = t.maxPerStep(c, &at);
        md << "| " << tb::counterName(c) << " | " << t.total(c) << " | " << std::setprecision(5) << double(t.total(c)) / double(agentSteps) << " | "
           << mx << " (" << at << ") | " << t.stepsWith(c) << " | " << std::setprecision(2) << double(t.total(c)) / double(t.steps) << " | "
           << phaseTotal(c, 0, s50) << " | " << phaseTotal(c, s50, s90) << " | " << phaseTotal(c, s90, t.steps) << " |\n";
    }
    md << std::defaultfloat;
    std::printf("  evacuated at step %d (production %d), instrumented run identical to production: %s\n", t.evacStep, prodEvac, identical ? "yes" : "NO");
    for (int c = 0; c < tb::COUNTERS; ++c) {
        int at = 0;
        const uint32_t mx = t.maxPerStep(c, &at);
        std::printf("  %-34s total %9llu, max %5u per step (step %d), %d steps with any\n", tb::counterName(c), (unsigned long long)t.total(c), mx,
                    at, t.stepsWith(c));
    }
    std::printf("  -> %s\n", dir.c_str());
    return identical ? 0 : 1;
}

// The stair harness (cmdStair, `fd_harness stair`, --mode ring: the default and the calibration's measure, the maximum
// sustained flow = the largest J of the stationary diagram). The model's specific flow on a gangway incline against density,
// ascending and descending, in an inclined periodic corridor: floor z = rake x (physics.comp FD_INCLINE; default venue S's gangway
// rake 0.5, 26.57 deg), periodic in x with period --length-m and a screw boundary (one period also shifts z by rake x period: the
// image of the incline is the incline), walls at |y| = width / 2 + BODY_RADIUS, so that the agents' centres span --width-m (the
// gangway's clear width, 1.20 m: on S the seat blocks end a body radius beyond a gangway's edge and a body at the edge overhangs the
// row's floor beside it), ending STAIR_WALL_TOP_M above the incline (seat-block ends: below the torso-height obstacle
// avoidance's reach, as on the venues' gangways). Goal direction +x: ascending on rake > 0 ("up"), descending on the reversed incline ("down"),
// level on rake 0 ("level", the control at the gangway's width). The venues' incline speed (VENUE_INCLINE_SPEED: the @incline block
// with the corridor's slope, the same stair speeds) and the stair spacing of --stair-flow (off: the level spacing).
// Density rho = N / (width x length), persons per m^2 of plan area. After the warm-up, every step: the ring's specific flow J =
// sum_i v_x,i / (length x width) [persons/(m s)] (the ring's time-mean flow through any cross-section, per metre of the clear width)
// and mean x-velocity, the central area's (|x| <= 5 m) density; every 10th step the mean in-lane gap (horizontal centre distance to
// the nearest agent ahead within BODY_DIAM of the path, the headway rule's s); overlap spot checks every 50 steps. Several seeds: the
// mean (the overlap: the max). Writes <out>/<name>_<yyyymmdd_hhmm>/stair.csv and summary.md (plot: tools/fd/stair_plot.py <folder>).
// Calibration targets (values as reported in the cited sources; not yet checked against the originals): EMPIRICAL = Burghardt, Seyfried & Klingsch
// (2013) maximum specific flows 1.22 (up) / 1.25 (down) persons/(m s); CONSERVATIVE = the Green Guide's 66 persons/(m min).
constexpr double EMPIRICAL_UP_P_M_S = 1.22, EMPIRICAL_DOWN_P_M_S = 1.25;
constexpr double CONSERVATIVE_P_M_S = 66.0 / 60.0;
// The corridor's side walls end STAIR_WALL_TOP_M above the incline: venue S's seat-block top above its tread (a gangway's sides are
// seat-block ends), below the obstacle avoidance's torso sample (TORSO_HEIGHT above the centre, range OBSTACLE_RANGE), as on the venues'
// gangways; full-height walls push every agent within 0.78 m of them towards the middle
constexpr double STAIR_WALL_TOP_M = 0.85;
// 0.05-0.1 steps through the stair spacing's critical densities (the calibrated maxima lie at 1.7-2.2), 0.25-0.5 beyond
// (the level spacing peaks at 3-4.5): the sharp peak where the free branch meets the headway branch, sampled every 0.05 persons/m^2
const char* DEFAULT_STAIR_DENSITIES = "0.5,1,1.25,1.5,1.6,1.7,1.8,1.9,2,2.05,2.1,2.15,2.2,2.25,2.3,2.4,2.5,2.75,3,3.25,3.5,3.75,4,4.5,5";

struct StairPoint {
    std::string dir;
    double rho = 0;          // persons per m^2 of plan area (the clear width)
    int agents = 0;
    double speed = 0;        // the ring's mean x-velocity, m/s (horizontal)
    double speedHalf[2] = {};
    double flow = 0;         // specific flow, persons/(m s)
    double rhoArea = 0;      // the central area's mean density
    double gap = 0;          // mean in-lane gap s, m
    double overlapMax = 0;
};

double stairRake(const std::string& dir, double rake) { return dir == "up" ? rake : dir == "down" ? -rake : 0.0; }

// The reservoir corridor (--mode reservoir): the same incline, not periodic (the grid's domain, |x| <= 31.25 m)
std::string reservoirDefines(const Scenario& sc, double rake) {
    const double halfW = units::modelLength(0.5 * sc.widthM) + double(BODY_RADIUS);
    const double inv = 1.0 / std::sqrt(1.0 + rake * rake);
    std::ostringstream d;
    d << "#define FD_CORRIDOR\n#define FD_INCLINE\n#define FD_RAKE " << glslFloatLiteral(float(rake)) << "\n#define FD_INCLINE_N vec3("
      << glslFloatLiteral(float(-rake * inv)) << ", 0.0, " << glslFloatLiteral(float(inv)) << ")\n#define FD_WALL_TOP_N "
      << glslFloatLiteral(float(units::modelLength(STAIR_WALL_TOP_M) * inv)) << "\n#define FD_HALF_WIDTH " << fmtNum(halfW)
      << "\n#define TEST_DRIVE_DIR vec2(1.0, 0.0)\n";
    return d.str();
}

std::string stairDefines(const Scenario& sc, double rake) {
    const double halfW = units::modelLength(0.5 * sc.widthM) + double(BODY_RADIUS), period = units::modelLength(sc.lengthM);
    const double cell = double(DOMAIN_SPAN) / GRID_RES;
    const double c0 = (-0.5 * period - double(DOMAIN_MIN)) / cell, cells = period / cell;
    if (std::abs(c0 - std::round(c0)) > 1e-6 || std::abs(cells - std::round(cells)) > 1e-6 || period > 1.8)
        throw std::runtime_error("--length-m must be a multiple of 2 grid cells (3.125 m) and at most 56 m");
    const double inv = 1.0 / std::sqrt(1.0 + rake * rake);
    std::ostringstream d;
    d << "#define FD_CORRIDOR\n#define FD_INCLINE\n#define FD_RAKE " << glslFloatLiteral(float(rake)) << "\n#define FD_INCLINE_N vec3("
      << glslFloatLiteral(float(-rake * inv)) << ", 0.0, " << glslFloatLiteral(float(inv)) << ")\n#define FD_WALL_TOP_N "
      << glslFloatLiteral(float(units::modelLength(STAIR_WALL_TOP_M) * inv)) << "\n#define FD_HALF_WIDTH " << fmtNum(halfW)
      << "\n#define FD_PERIODIC_X\n#define FD_PERIOD " << fmtNum(period) << "\n#define FD_CELL0 " << int(std::lround(c0)) << "\n#define FD_CELLS "
      << int(std::lround(cells)) << "\n#define TEST_DRIVE_DIR vec2(1.0, 0.0)\n";
    return d.str();
}

// Uniform random placement over the centres' band, hard-disk rejection in the plan (minimum image; up to 200 attempts each), at rest
// height above the incline
std::vector<GpuBoid> placeStair(const Scenario& sc, double rake, int active, unsigned seed) {
    const float halfL = float(units::modelLength(0.5 * sc.lengthM));
    const float yMax = float(units::modelLength(0.5 * sc.widthM));
    std::mt19937 rng(seed);
    std::uniform_real_distribution<float> ux(-halfL, halfL), uy(-yMax, yMax);
    int n = 256;
    while (n < active) n *= 2;
    std::vector<GpuBoid> b(size_t(n), GpuBoid{ glm::vec4(PARK_COORD, PARK_COORD, PARK_COORD, 0.0f), glm::vec4(0.0f) });
    const float period = 2.0f * halfL;
    for (int i = 0; i < active; ++i) {
        glm::vec2 p(0.0f);
        for (int a = 0; a < 200; ++a) {
            p = glm::vec2(ux(rng), uy(rng));
            bool free = true;
            for (int j = 0; j < i && free; ++j) {
                glm::vec2 d = p - glm::vec2(b[size_t(j)].position);
                d.x -= period * std::round(d.x / period);
                free = glm::dot(d, d) >= BODY_DIAM2;
            }
            if (free) break;
        }
        b[size_t(i)].position = glm::vec4(p, float(rake) * p.x + BODY_RADIUS, 1.0f);
        b[size_t(i)].velocity = glm::vec4(0.0f);
    }
    return b;
}

StairPoint measureStairSeed(const fs::path& shaderDir, GLuint sdfTex, const Scenario& sc, double rake, double rho, unsigned seed) {
    const int active = int(std::lround(rho * sc.widthM * sc.lengthM));
    const std::vector<GpuBoid> start = placeStair(sc, rake, active, seed);
    const int n = int(start.size());
    CrowdSim sim(shaderDir, n);
    sim.upload(start);
    const int warm = int(std::lround(sc.warmupS / DT_REAL_S)), meas = int(std::lround(sc.measureS / DT_REAL_S));
    for (int s = 0; s < warm; ++s) sim.step(sdfTex);
    const float period = float(units::modelLength(sc.lengthM));
    const double halfArea = units::modelLength(MEASURE_HALF_M), areaM2 = 2.0 * MEASURE_HALF_M * sc.widthM;
    const double toMs = units::metresPerSecond(1.0);
    double sumV = 0, sumHalf[2] = {}, sumRhoArea = 0, sumGap = 0, maxOverlap = 0;
    long gapCount = 0;
    for (int s = 0; s < meas; ++s) {
        sim.step(sdfTex);
        const std::vector<GpuBoid> st = bench::readBuffer<GpuBoid>(sim.currentStateBuffer(), size_t(n));
        double v = 0;
        int inArea = 0;
        for (int i = 0; i < active; ++i) {
            v += double(st[size_t(i)].velocity.x) * toMs;
            inArea += std::abs(st[size_t(i)].position.x) <= halfArea;
        }
        sumV += v;
        sumHalf[s * 2 / meas] += v;
        sumRhoArea += double(inArea) / areaM2;
        auto offset = [&](int i, int j) {   // from i to j, the screw minimum image
            glm::vec3 d = glm::vec3(st[size_t(j)].position) - glm::vec3(st[size_t(i)].position);
            const float k = std::round(d.x / period);
            d.x -= period * k;
            d.z -= float(rake) * period * k;
            return d;
        };
        if (s % 10 == 0) {
            for (int i = 0; i < active; ++i) {
                float best = 1e9f;
                for (int j = 0; j < active; ++j) {
                    if (j == i) continue;
                    const glm::vec3 d = offset(i, j);
                    if (d.x > 0.0f && std::abs(d.y) < BODY_DIAM) best = std::min(best, glm::length(glm::vec2(d)));
                }
                if (best < 1e8f) { sumGap += units::metres(best); ++gapCount; }
            }
        }
        if (s % 50 == 0)
            for (int i = 0; i < active; ++i)
                for (int j = i + 1; j < active; ++j) {
                    const float l = glm::length(offset(i, j));
                    if (l < BODY_DIAM) maxOverlap = std::max(maxOverlap, double((BODY_DIAM - l) / BODY_DIAM));
                }
    }
    StairPoint p;
    p.rho = rho;
    p.agents = active;
    p.speed = sumV / (double(meas) * active);
    p.speedHalf[0] = sumHalf[0] / (double(meas / 2) * active);
    p.speedHalf[1] = sumHalf[1] / (double(meas - meas / 2) * active);
    p.flow = sumV / double(meas) / (sc.lengthM * sc.widthM);
    p.rhoArea = sumRhoArea / meas;
    p.gap = gapCount ? sumGap / double(gapCount) : 0.0;
    p.overlapMax = maxOverlap;
    return p;
}

// --mode reservoir: a dense queue (the reservoir: agents at rest, uniform hard-disk placement at density rho0 over x in [-length, 0] m
// of the gangway band) discharging up (or down) the non-periodic incline; every step each agent's first crossing of the lines x = 0,
// 5, 10 m is timed. The steady-state window at a line: from the crossing of the RES_FRAC_LO-th to the RES_FRAC_HI-th share of the agents
// (the front's arrival and the reservoir's tail excluded); J = crossings in the window / (window x width). With a reservoir denser
// than the critical state the discharge is the gangway's capacity (its maximum sustained flow), whatever rho0; below it the reservoir
// moves off at its own flow, so J(rho0) rises and saturates. The local diagram: density and flow (density x mean x-velocity) of the
// measurement area x in [2.5, 7.5] m in 10 s windows. The reservoir keeps |x| <= 28 m (the exit test removes agents past 29.06 m
// below EXIT_MAX_Z: the descending corridor's far end).
constexpr double RES_LINES_M[3] = { 0.0, 5.0, 10.0 };
constexpr double RES_FRAC_LO = 0.10, RES_FRAC_HI = 0.80;
constexpr double RES_AREA_LO_M = 2.5, RES_AREA_HI_M = 7.5, RES_WINDOW_S = 10.0;

struct ReservoirRun {
    int agents = 0;
    double flow[3] = {};      // the steady window's specific flow at each line, persons/(m s)
    double window[2] = {};    // the 5 m line's window, s
    double overlapMax = 0;
    int crossed = 0;          // agents that crossed the 10 m line
    std::vector<std::array<double, 3>> local;   // (rho, v, J) of the measurement area per 10 s window with someone in it
};

ReservoirRun measureReservoirSeed(const fs::path& shaderDir, GLuint sdfTex, const Scenario& sc, double rake, double rho0, unsigned seed) {
    const int active = int(std::lround(rho0 * sc.widthM * sc.lengthM));
    const float halfL = float(units::modelLength(0.5 * sc.lengthM));
    const float yMax = float(units::modelLength(0.5 * sc.widthM));
    std::mt19937 rng(seed);
    std::uniform_real_distribution<float> ux(-2.0f * halfL, 0.0f), uy(-yMax, yMax);
    int n = 256;
    while (n < active) n *= 2;
    std::vector<GpuBoid> start(size_t(n), GpuBoid{ glm::vec4(PARK_COORD, PARK_COORD, PARK_COORD, 0.0f), glm::vec4(0.0f) });
    for (int i = 0; i < active; ++i) {
        glm::vec2 p(0.0f);
        for (int t = 0; t < 200; ++t) {
            p = glm::vec2(ux(rng), uy(rng));
            bool free = true;
            for (int j = 0; j < i && free; ++j) {
                const glm::vec2 d = p - glm::vec2(start[size_t(j)].position);
                free = glm::dot(d, d) >= BODY_DIAM2;
            }
            if (free) break;
        }
        start[size_t(i)].position = glm::vec4(p, float(rake) * p.x + BODY_RADIUS, 1.0f);
    }
    CrowdSim sim(shaderDir, n);
    sim.upload(start);
    const double toMs = units::metresPerSecond(1.0);
    float line[3];
    for (int k = 0; k < 3; ++k) line[k] = float(units::modelLength(RES_LINES_M[k]));
    const float areaLo = float(units::modelLength(RES_AREA_LO_M)), areaHi = float(units::modelLength(RES_AREA_HI_M));
    const double areaM2 = (RES_AREA_HI_M - RES_AREA_LO_M) * sc.widthM;
    const int windowSteps = int(std::lround(RES_WINDOW_S / DT_REAL_S));
    const int maxSteps = int(std::lround(1800.0 / DT_REAL_S));
    std::vector<float> prevX(static_cast<size_t>(active));
    for (int i = 0; i < active; ++i) prevX[size_t(i)] = start[size_t(i)].position.x;
    std::vector<std::vector<double>> times(3);
    std::vector<std::array<bool, 3>> crossed(size_t(active), { false, false, false });
    ReservoirRun r;
    r.agents = active;
    double wN = 0, wV = 0;
    int wSteps = 0;
    for (int s = 1; s <= maxSteps && int(times[2].size()) < active; ++s) {
        sim.step(sdfTex);
        const std::vector<GpuBoid> st = bench::readBuffer<GpuBoid>(sim.currentStateBuffer(), size_t(n));
        for (int i = 0; i < active; ++i) {
            const GpuBoid& b = st[size_t(i)];
            if (b.position.w == 0.0f) continue;
            const float x = b.position.x;
            for (int k = 0; k < 3; ++k)
                if (!crossed[size_t(i)][size_t(k)] && prevX[size_t(i)] < line[k] && x >= line[k]) {
                    crossed[size_t(i)][size_t(k)] = true;
                    times[size_t(k)].push_back(s * DT_REAL_S);
                }
            prevX[size_t(i)] = x;
            if (x >= areaLo && x < areaHi) { wN += 1.0; wV += double(b.velocity.x) * toMs; }
        }
        if (++wSteps == windowSteps) {
            if (wN > 0) {
                const double rho = wN / windowSteps / areaM2, v = wV / wN;
                r.local.push_back({ rho, v, rho * v });
            }
            wN = wV = 0;
            wSteps = 0;
        }
        if (s % 50 == 0)
            for (int i = 0; i < active; ++i)
                for (int j = i + 1; j < active; ++j) {
                    if (st[size_t(i)].position.w == 0.0f || st[size_t(j)].position.w == 0.0f) continue;
                    const float l = glm::length(glm::vec3(st[size_t(i)].position) - glm::vec3(st[size_t(j)].position));
                    if (l < BODY_DIAM) r.overlapMax = std::max(r.overlapMax, double((BODY_DIAM - l) / BODY_DIAM));
                }
    }
    r.crossed = int(times[2].size());
    for (int k = 0; k < 3; ++k) {
        std::vector<double>& t = times[size_t(k)];
        std::sort(t.begin(), t.end());
        const int lo = int(std::floor(RES_FRAC_LO * active)), hi = int(std::ceil(RES_FRAC_HI * active)) - 1;
        if (hi < int(t.size()) && hi > lo && t[size_t(hi)] > t[size_t(lo)]) {
            r.flow[k] = double(hi - lo) / (t[size_t(hi)] - t[size_t(lo)]) / sc.widthM;
            if (k == 1) { r.window[0] = t[size_t(lo)]; r.window[1] = t[size_t(hi)]; }
        }
    }
    return r;
}

const char* DEFAULT_RESERVOIR_DENSITIES = "1,2,3,4,5,5.5,6";

int cmdStairReservoir(const bench::Args& a, const Scenario& sc, double rake, const std::vector<std::string>& dirs, const std::string& modelDefs,
                      const std::string& modelText, const fs::path& out, const std::string& name) {
    const std::vector<double> dens = parseDoubles(a.get("densities", DEFAULT_RESERVOIR_DENSITIES));
    bench::createHiddenContext("fd_harness");
    const GLuint sdf = loadSDFTexture3D(resolveAsset("stadium.sdf"));   // unused by the corridor; the pipeline binds it
    std::printf("fd_harness stair --mode reservoir | %s\n  non-periodic incline, centres span %.2f m (walls %.2f m apart), rake %.4f (%.2f deg); reservoir %.1f m "
                "below x = 0 at rho0, lines at 0 / 5 / 10 m, steady window %.0f-%.0f%% of the agents; seeds %s; model: %s\n", metaLine().c_str(), sc.widthM,
                sc.widthM + 2.0 * units::metres(BODY_RADIUS), rake, std::atan(rake) * 57.29577951308232, sc.lengthM, 100.0 * RES_FRAC_LO, 100.0 * RES_FRAC_HI,
                seedList(sc).c_str(), modelText.c_str());
    struct Row { std::string dir; double rho0; int agents; double flow[3]; double flowMin, flowMax, w0, w1, overlap; int crossed; };
    std::vector<Row> rows;
    std::ofstream loc;
    const std::string dirOut = runFolder(out, name);
    loc.open(fs::path(dirOut) / "local_fd.csv");
    loc << "dir,rho0_p_m2,seed,window,rho_p_m2,speed_m_s,flow_p_m_s\n";
    for (const std::string& dir : dirs) {
        const double r = stairRake(dir, rake);
        const fs::path shaders = shaderVariant(resolveAsset("shaders"), "reservoir_" + dir, reservoirDefines(sc, r) + modelDefs);
        for (double rho0 : dens) {
            Row row{ dir, rho0, 0, { 0, 0, 0 }, 1e9, 0, 0, 0, 0, 0 };
            const double k = 1.0 / double(sc.seeds.size());
            for (unsigned seed : sc.seeds) {
                const ReservoirRun q = measureReservoirSeed(shaders, sdf, sc, r, rho0, seed);
                row.agents = q.agents;
                for (int l = 0; l < 3; ++l) row.flow[l] += k * q.flow[l];
                row.flowMin = std::min(row.flowMin, q.flow[1]);
                row.flowMax = std::max(row.flowMax, q.flow[1]);
                row.w0 += k * q.window[0];
                row.w1 += k * q.window[1];
                row.overlap = std::max(row.overlap, q.overlapMax);
                row.crossed += q.crossed;
                for (size_t w = 0; w < q.local.size(); ++w)
                    loc << dir << ',' << rho0 << ',' << seed << ',' << w << ',' << q.local[w][0] << ',' << q.local[w][1] << ',' << q.local[w][2] << '\n';
            }
            std::printf("  %-5s rho0 %4.2f: %3d agents, J at 0 / 5 / 10 m %.3f / %.3f / %.3f p/(m s) (5 m: %.1f p/(m min), seeds %.3f-%.3f; window %.0f-%.0f s), "
                        "crossed %d of %d, max overlap %.3f\n", dir.c_str(), rho0, row.agents, row.flow[0], row.flow[1], row.flow[2], 60.0 * row.flow[1], row.flowMin,
                        row.flowMax, row.w0, row.w1, row.crossed, row.agents * int(sc.seeds.size()), row.overlap);
            rows.push_back(row);
        }
        fs::remove_all(shaders);
    }
    {
        std::ofstream f(fs::path(dirOut) / "reservoir.csv");
        f << "dir,rho0_p_m2,agents,flow_0m_p_m_s,flow_5m_p_m_s,flow_10m_p_m_s,flow_5m_p_m_min,flow_5m_seed_min,flow_5m_seed_max,window_start_s,window_end_s,"
             "crossed_all,max_overlap_body_diam\n";
        for (const Row& w : rows)
            f << w.dir << ',' << w.rho0 << ',' << w.agents << ',' << w.flow[0] << ',' << w.flow[1] << ',' << w.flow[2] << ',' << 60.0 * w.flow[1] << ',' << w.flowMin
              << ',' << w.flowMax << ',' << w.w0 << ',' << w.w1 << ',' << w.crossed << ',' << w.overlap << '\n';
    }
    std::ofstream md(fs::path(dirOut) / "summary.md");
    md << "# Stair harness, reservoir mode `" << name << "`\n\n" << metaLine() << ".\n\n";
    md << "A gangway fed from a reservoir (tools/fd/fd_harness.cpp `stair --mode reservoir`, physics.comp FD_INCLINE without FD_PERIODIC_X): the incline z = "
       << "rake x, rake " << rake << " (" << std::setprecision(4) << std::atan(rake) * 57.29577951308232 << " deg), walls " << sc.widthM + 2.0 * units::metres(BODY_RADIUS)
       << " m apart (the agents' centres span " << sc.widthM << " m, the gangway's clear width); a queue of agents at rest, uniform at density rho0 over the "
       << sc.lengthM << " m below x = 0, all driven +x (up: ascending, down: the incline reversed, descending, level: rake 0). Specific flow J = crossings of a "
       << "line in its steady window (the " << 100.0 * RES_FRAC_LO << "-th to the " << 100.0 * RES_FRAC_HI << "-th percentile of the agents' crossing times) / "
       << "(window x clear width); lines at 0, 5 and 10 m. Seeds " << seedList(sc) << " (means; the 5 m line's range over the seeds). Model: " << modelText
       << ". The local diagram (local_fd.csv): the measurement area x in [" << RES_AREA_LO_M << ", " << RES_AREA_HI_M << "] m in " << RES_WINDOW_S << " s windows.\n\n";
    md << "| dir | rho0 [p/m^2] | agents | J at 0 m | J at 5 m [p/(m s)] | J at 10 m | J at 5 m [p/(m min)] | 5 m, seeds | window [s] | max overlap |\n";
    md << "|---|---:|---:|---:|---:|---:|---:|---|---|---:|\n";
    for (const Row& w : rows)
        md << std::fixed << "| " << w.dir << " | " << std::setprecision(2) << w.rho0 << " | " << w.agents << " | " << std::setprecision(3) << w.flow[0] << " | " << w.flow[1]
           << " | " << w.flow[2] << " | " << std::setprecision(1) << 60.0 * w.flow[1] << " | " << std::setprecision(3) << w.flowMin << "-" << w.flowMax << " | "
           << std::setprecision(0) << w.w0 << "-" << w.w1 << " | " << std::setprecision(3) << w.overlap << " |\n";
    md << std::defaultfloat << "\nThe maximum sustained flow (the capacity): the largest J at the 5 m line over rho0.\n\n"
       << "| dir | capacity [p/(m s)] | [p/(m min)] | at rho0 | EMPIRICAL target | J / EMPIRICAL | CONSERVATIVE target | J / CONSERVATIVE |\n"
       << "|---|---:|---:|---:|---:|---:|---:|---:|\n";
    for (const std::string& dir : dirs) {
        double best = 0, at = 0;
        for (const Row& w : rows)
            if (w.dir == dir && w.flow[1] > best) { best = w.flow[1]; at = w.rho0; }
        const double emp = dir == "down" ? EMPIRICAL_DOWN_P_M_S : EMPIRICAL_UP_P_M_S;
        md << std::fixed << "| " << dir << " | " << std::setprecision(3) << best << " | " << std::setprecision(1) << 60.0 * best << " | " << std::setprecision(2) << at;
        if (dir == "level") md << " | - | - | - | - |\n";
        else md << " | " << std::setprecision(2) << emp << " | " << std::setprecision(3) << best / emp << " | " << std::setprecision(2) << CONSERVATIVE_P_M_S << " | "
                << std::setprecision(3) << best / CONSERVATIVE_P_M_S << " |\n";
        std::printf("  %-5s capacity %.3f p/(m s) = %.1f p/(m min) at rho0 %.2f", dir.c_str(), best, 60.0 * best, at);
        if (dir != "level") std::printf(": %.3f x EMPIRICAL (%.2f), %.3f x CONSERVATIVE (%.2f)", best / emp, emp, best / CONSERVATIVE_P_M_S, CONSERVATIVE_P_M_S);
        std::printf("\n");
    }
    md << std::defaultfloat << "\nTargets (as reported in the cited sources; not yet checked against the originals): EMPIRICAL = Burghardt, Seyfried & Klingsch (2013), "
       << "maximum specific flows 1.22 (up) / 1.25 (down) persons/(m s); CONSERVATIVE = the Green Guide (6th ed., 2018), 66 persons/(m min) on stepped surfaces.\n";
    std::printf("  -> %s\n", dirOut.c_str());
    return 0;
}

int cmdStair(const bench::Args& a) {
    const std::string mode = a.get("mode", "ring");
    if (mode != "reservoir" && mode != "ring") throw std::runtime_error("--mode reservoir | ring");
    const bool ring = mode == "ring";
    Scenario sc;
    sc.widthM = std::stod(a.get("width-m", "1.2"));
    sc.lengthM = std::stod(a.get("length-m", ring ? "50" : "28"));   // ring: the period; reservoir: the queue's length below x = 0
    sc.warmupS = std::stod(a.get("warmup-s", "300"));
    sc.measureS = std::stod(a.get("measure-s", "300"));
    sc.seeds.clear();
    for (const std::string& t : bench::parseList(a.get("seeds", ring ? "7,8,9" : "7,8,9,10,11"))) sc.seeds.push_back(unsigned(std::stoul(t)));
    const double rake = std::stod(a.get("rake", fmtNum(venueS().layout.rake)));
    const std::vector<std::string> dirs = bench::parseList(a.get("dirs", "up,down,level"));
    // The analytic venues' stair model (their preamble: the same literals): the incline speed and the stair spacing of --stair-flow (default
    // the venues' default, EMPIRICAL; off: the level spacing). --t-up / --t-down (real seconds; the calibration's grid) override the set's time
    // gaps with the literals sim_params.hpp would compute for them (stairHeadwayModel): a grid point and the build with the same constants are
    // the same program
    ModelOptions mo;
    mo.inclineSpeed = true;
    mo.stairFlow = stairFlowByName(a.get("stair-flow", stairFlowName(defaultModelOptions(venueS()).stairFlow)));
    const bool overrideT = a.has("t-up") || a.has("t-down");
    if (overrideT && mo.stairFlow == StairFlow::Off) mo.stairFlow = StairFlow::Empirical;
    std::string modelDefs = modelPreamble(venueS(), mo);
    const glm::vec2 tSet = stairHeadwayTimes(mo.stairFlow);
    const double tUpS = std::stod(a.get("t-up", fmtNum(double(tSet.x) * double(TIME_SCALE_S_PER_UNIT)))),
                 tDownS = std::stod(a.get("t-down", fmtNum(double(tSet.y) * double(TIME_SCALE_S_PER_UNIT))));
    if (overrideT)
        modelDefs += "#undef T_HEADWAY_STAIR_UP\n#define T_HEADWAY_STAIR_UP " + glslFloatLiteral(stairHeadwayModel(float(tUpS))) +
                     "\n#undef T_HEADWAY_STAIR_DOWN\n#define T_HEADWAY_STAIR_DOWN " + glslFloatLiteral(stairHeadwayModel(float(tDownS))) + "\n";
    const float tUp = overrideT ? stairHeadwayModel(float(tUpS)) : tSet.x, tDown = overrideT ? stairHeadwayModel(float(tDownS)) : tSet.y;
    for (const auto& [v, t] : { std::pair<float, float>{ V_STAIR_UP, tUp }, std::pair<float, float>{ V_STAIR_DOWN, tDown } })
        if (stairLookAhead(v, t) > double(R_PERC))
            std::printf("WARNING: R_PERC %.4f does not cover the incline's look-ahead %.4f (T_stair %.3f s)\n", double(R_PERC), stairLookAhead(v, t),
                        double(t) * double(TIME_SCALE_S_PER_UNIT));
    const std::string modelText = "the venues' incline speed (stair speeds " + fmtShort(V_STAIR_UP_M_S) + " / " + fmtShort(V_STAIR_DOWN_M_S) +
                                  " m/s), " + (mo.stairFlow == StairFlow::Off
                                      ? "level spacing (T_HEADWAY " + fmtShort(T_HEADWAY_S) + " s)"
                                      : std::string("stair spacing ") + (overrideT ? "(grid point" : "(" + std::string(stairFlowName(mo.stairFlow))) +
                                            ": T_stair up " + fmtShort(double(tUp) * double(TIME_SCALE_S_PER_UNIT)) + " s, down " +
                                            fmtShort(double(tDown) * double(TIME_SCALE_S_PER_UNIT)) + " s; T_HEADWAY " + fmtShort(T_HEADWAY_S) + " s on the level)");
    const fs::path out = a.get("out", "out/results/stair");
    const std::string name = a.get("name", ring ? "stair_ring" : "stair");
    if (!ring) {
        if (sc.lengthM > 28.0 + 1e-9) throw std::runtime_error("--length-m: the reservoir lies within 28 m below x = 0");
        return cmdStairReservoir(a, sc, rake, dirs, modelDefs, modelText, out, name);
    }
    const std::vector<double> dens = parseDoubles(a.get("densities", DEFAULT_STAIR_DENSITIES));
    bench::createHiddenContext("fd_harness");
    const GLuint sdf = loadSDFTexture3D(resolveAsset("stadium.sdf"));   // unused by the corridor; the pipeline binds it
    std::printf("fd_harness stair | %s\n  inclined periodic corridor: centres span %.2f m (walls %.2f m apart), period %.2f m, rake %.4f (%.2f deg); warm-up %.0f s, "
                "measured %.0f s, seeds %s; model: %s\n", metaLine().c_str(), sc.widthM, sc.widthM + 2.0 * units::metres(BODY_RADIUS), sc.lengthM, rake,
                std::atan(rake) * 57.29577951308232, sc.warmupS, sc.measureS, seedList(sc).c_str(), modelText.c_str());
    std::vector<StairPoint> pts;
    for (const std::string& dir : dirs) {
        const double r = stairRake(dir, rake);
        const fs::path shaders = shaderVariant(resolveAsset("shaders"), "stair_" + dir, stairDefines(sc, r) + modelDefs);
        for (double rho : dens) {
            StairPoint p;
            p.dir = dir;
            const double k = 1.0 / double(sc.seeds.size());
            for (unsigned seed : sc.seeds) {
                const StairPoint q = measureStairSeed(shaders, sdf, sc, r, rho, seed);
                p.rho = q.rho;
                p.agents = q.agents;
                p.speed += k * q.speed;
                p.speedHalf[0] += k * q.speedHalf[0];
                p.speedHalf[1] += k * q.speedHalf[1];
                p.flow += k * q.flow;
                p.rhoArea += k * q.rhoArea;
                p.gap += k * q.gap;
                p.overlapMax = std::max(p.overlapMax, q.overlapMax);
            }
            std::printf("  %-5s rho %4.2f: %3d agents, v %.3f m/s (halves %.3f / %.3f), J %.3f p/(m s) = %5.1f p/(m min), area density %.2f, gap %.3f m, "
                        "max overlap %.3f\n", dir.c_str(), rho, p.agents, p.speed, p.speedHalf[0], p.speedHalf[1], p.flow, 60.0 * p.flow, p.rhoArea, p.gap,
                        p.overlapMax);
            pts.push_back(p);
        }
        fs::remove_all(shaders);
    }
    const std::string dirOut = runFolder(out, name);
    {
        std::ofstream f(fs::path(dirOut) / "stair.csv");
        f << "dir,rho_p_m2,agents,speed_m_s,speed_first_half_m_s,speed_second_half_m_s,flow_p_m_s,flow_p_m_min,area_density_p_m2,gap_m,max_overlap_body_diam\n";
        for (const StairPoint& p : pts)
            f << p.dir << ',' << p.rho << ',' << p.agents << ',' << p.speed << ',' << p.speedHalf[0] << ',' << p.speedHalf[1] << ',' << p.flow << ','
              << 60.0 * p.flow << ',' << p.rhoArea << ',' << p.gap << ',' << p.overlapMax << '\n';
    }
    std::ofstream md(fs::path(dirOut) / "summary.md");
    md << "# Stair harness `" << name << "`\n\n" << metaLine() << ".\n\n";
    md << "Inclined periodic corridor (tools/fd/fd_harness.cpp `stair`, physics.comp FD_INCLINE): the agents' centres span " << sc.widthM
       << " m (walls " << sc.widthM + 2.0 * units::metres(BODY_RADIUS) << " m apart), period " << sc.lengthM << " m with a screw boundary, rake " << rake
       << " (" << std::setprecision(4) << std::atan(rake) * 57.29577951308232 << " deg); goal +x: up = ascending, down = descending, level = rake 0. Warm-up "
       << sc.warmupS << " s, measured " << sc.measureS << " s (DT " << DT_REAL_S << " s), seeds " << seedList(sc) << " (means; overlap: max). Model: "
       << modelText << ". Density per m^2 of plan area of the clear width; J = specific flow per metre of the clear width (the ring's mean flow).\n\n";
    md << "| dir | rho [p/m^2] | agents | v [m/s] | v halves [m/s] | J [p/(m s)] | J [p/(m min)] | area density | mean gap [m] | max overlap |\n";
    md << "|---|---:|---:|---:|---|---:|---:|---:|---:|---:|\n";
    for (const StairPoint& p : pts)
        md << std::fixed << std::setprecision(3) << "| " << p.dir << " | " << std::setprecision(2) << p.rho << " | " << p.agents << " | " << std::setprecision(3)
           << p.speed << " | " << p.speedHalf[0] << " / " << p.speedHalf[1] << " | " << p.flow << " | " << std::setprecision(1) << 60.0 * p.flow << " | "
           << std::setprecision(2) << p.rhoArea << " | " << std::setprecision(3) << p.gap << " | " << p.overlapMax << " |\n";
    md << std::defaultfloat << "\n| dir | max J [p/(m s)] | [p/(m min)] | at rho | EMPIRICAL target | J / EMPIRICAL | CONSERVATIVE target | J / CONSERVATIVE |\n"
       << "|---|---:|---:|---:|---:|---:|---:|---:|\n";
    for (const std::string& dir : dirs) {
        double best = 0, at = 0;
        for (const StairPoint& p : pts)
            if (p.dir == dir && p.flow > best) { best = p.flow; at = p.rho; }
        const double emp = dir == "down" ? EMPIRICAL_DOWN_P_M_S : EMPIRICAL_UP_P_M_S;
        md << std::fixed << "| " << dir << " | " << std::setprecision(3) << best << " | " << std::setprecision(1) << 60.0 * best << " | " << std::setprecision(2) << at;
        if (dir == "level") md << " | - | - | - | - |\n";
        else md << " | " << std::setprecision(2) << emp << " | " << std::setprecision(3) << best / emp << " | " << std::setprecision(2) << CONSERVATIVE_P_M_S << " | "
                << std::setprecision(3) << best / CONSERVATIVE_P_M_S << " |\n";
        std::printf("  %-5s max J %.3f p/(m s) = %.1f p/(m min) at rho %.2f", dir.c_str(), best, 60.0 * best, at);
        if (dir != "level") std::printf(": %.3f x EMPIRICAL (%.2f), %.3f x CONSERVATIVE (%.2f)", best / emp, emp, best / CONSERVATIVE_P_M_S, CONSERVATIVE_P_M_S);
        std::printf("\n");
    }
    md << std::defaultfloat << "\nTargets (as reported in the cited sources; not yet checked against the originals): EMPIRICAL = Burghardt, Seyfried & Klingsch (2013), "
       << "maximum specific flows 1.22 (up) / 1.25 (down) persons/(m s); CONSERVATIVE = the Green Guide (6th ed., 2018), 66 persons/(m min) on stepped surfaces.\n";
    std::printf("  -> %s\n", dirOut.c_str());
    return 0;
}

} // namespace

int main(int argc, char** argv) {
    try {
        if (argc < 2) {
            std::fprintf(stderr, "usage: fd_harness run | calibrate | dtcheck | ksweep | tiebreak | stair [...] (see the header of tools/fd/fd_harness.cpp)\n");
            return 2;
        }
        const std::string cmd = argv[1];
        const bench::Args a(argc, argv, 2);
        if (cmd == "run") return cmdRun(a);
        if (cmd == "calibrate") return cmdCalibrate(a);
        if (cmd == "dtcheck") return cmdDtCheck(a);
        if (cmd == "ksweep") return cmdKSweep(a);
        if (cmd == "tiebreak") return cmdTieBreak(a);
        if (cmd == "stair") return cmdStair(a);
        std::fprintf(stderr, "unknown command %s\n", cmd.c_str());
        return 2;
    } catch (const std::exception& e) {
        std::fprintf(stderr, "fd_harness: %s\n", e.what());
        return 1;
    }
}
