#pragma once

#include <array>
#include <cmath>
#include <cstdint>

// Simulation parameters shared by C++ and GLSL: the single source of truth for every model
// constant of the simulation step (the compute shaders and their CPU port, CpuCrowdSim).
// Every shader receives them as #defines through the preamble that shader.cpp inserts
// right after its #version line, so none of these values may be repeated in a shader.
// All lengths in this file are model units (the stadium spans [-0.95, 0.95] in x and y), except the
// physical-units block near the end, which converts them to metres and seconds for reports.
// The model in prose: docs/MODEL.md.
namespace swarm {

struct Float2 { float x, y; };
struct Float3 { float x, y, z; };

// --- How the GLSL compiler folds constant expressions (CPU/GPU constant parity) ---
// The preamble emits every float constant as its shortest round-trip decimal. The GLSL compiler
// folds a constant expression over those decimal literals in double precision and rounds the
// result to float once. C++ float arithmetic rounds each factor to float first and can land one
// float step away (1.25f * 0.008f = 0x3c23d70b; GLSL 1.25 * 0.008 = 0x3c23d70a), and so can
// double arithmetic on the float factors, since 0.008f is not 0.008. glsl_fold::decimal(f) is
// the double of f's preamble literal, so mul / add / div fold exactly as the GPU does.
// test_gpu parity.constants checks decimal() against the preamble text and every folded value against
// the GPU bit pattern.
namespace glsl_fold {
constexpr double pow10(int k) {   // exact for 0 <= k <= 22
    double p = 1.0;
    for (int i = 0; i < k; ++i) p *= 10.0;
    return p;
}
// f's shortest round-trip decimal (std::to_chars: fewest significant digits, then nearest) as a
// double: n / 10^k with n and 10^k exact, so the division rounds the decimal value correctly
constexpr double decimal(float f) {
    if (f == 0.0f) return 0.0;
    const float m = f < 0.0f ? -f : f;
    const double a = double(m);
    int e = 0;   // 10^e <= a < 10^(e + 1)
    if (a >= 1.0) { while (a >= pow10(e + 1)) ++e; }
    else          { while (a * pow10(-e) < 1.0) --e; }
    for (int digits = 1; digits <= 9; ++digits) {
        const int k = digits - 1 - e;   // a * 10^k has 'digits' integer digits
        const double n = double((long long)((k >= 0 ? a * pow10(k) : a / pow10(-k)) + 0.5));
        const double d = k >= 0 ? n / pow10(k) : n * pow10(-k);
        if (float(d) == m) return f < 0.0f ? -d : d;
    }
    return double(f);   // unreachable: 9 significant digits always round-trip a float
}
constexpr float mul(float a, float b) { return float(decimal(a) * decimal(b)); }
constexpr float add(float a, float b) { return float(decimal(a) + decimal(b)); }
constexpr float div(float a, float b) { return float(decimal(a) / decimal(b)); }
} // namespace glsl_fold

// --- Spatial hash: 2D column grid over [DOMAIN_MIN, DOMAIN_MIN + DOMAIN_SPAN]^2, z ignored ---
constexpr int GRID_RES = 40;
constexpr float DOMAIN_MIN = -1.0f;
constexpr float DOMAIN_SPAN = 2.0f;
constexpr float DOMAIN_MAX = DOMAIN_MIN + DOMAIN_SPAN;
// physics.comp parks any agent with max(|x|, |y|) > DOMAIN_MAX, which needs a symmetric domain
static_assert(-DOMAIN_MIN == DOMAIN_MAX, "the out-of-domain exit test assumes a domain symmetric about 0");

// --- Baked stadium SDF (stadium.sdf, loaded by sdf.hpp) ---
// SDF_RES samples per axis: 128 + a 1-voxel pad each side. Sample index i (0..SDF_RES-1) sits at
// SDF_ORIGIN + (i - 1) * SDF_SPACING. physics.comp gets SDF_RES as a #define and the origin and
// spacing as uniforms (u_sdfMin, u_sdfInvSpacing).
constexpr int SDF_RES = 130;
constexpr float SDF_SPACING = 1.9f / 127.0f;
constexpr Float3 SDF_ORIGIN{ -0.95f, -0.95f, -0.8092595f };

// --- Model scales ---
// Metres per model length unit and seconds per model time unit: 31.25 m (a 0.25 m personal radius is 0.008 units)
// and 17.490671 s = V_MAX * WORLD_SCALE_M_PER_UNIT / V_FREE_M_S. The physical-units block at the end states what they are calibrated to.
// They reach the simulation through three constants only: GRAVITY (real gravity in model units), TAU_RELAX and
// T_HEADWAY (the driving term's relaxation time and the headway time gap, real seconds in model time; below).
constexpr float WORLD_SCALE_M_PER_UNIT = 31.25f;
constexpr float TIME_SCALE_S_PER_UNIT = 17.490671f;

// --- Agent body model: two radii ---
// PERSONAL_RADIUS (0.25 m): the soft personal-space preference. The separation kernel's support is
// R_SEP = 2 * PERSONAL_RADIUS (two personal spaces touch where it starts); it steers, it never forbids.
// BODY_RADIUS (0.20 m): the hard physical body, a disk/cylinder. Every hard contact uses it: agent-agent
// non-overlap (the projection below), wall clearance, the fence collision band and the floor rest height
// (the centre rests BODY_RADIUS above any floor and keeps BODY_RADIUS horizontal clearance from any wall).
constexpr float PERSONAL_RADIUS = 0.008f;
constexpr float BODY_RADIUS = 0.0064f;
// Derived constants reach the shaders as expressions of their factors, which the GLSL compiler folds;
// the values here are that fold (glsl_fold above). Doubling is exact, so 2 * 0.008f is 0.016f either way.
constexpr float R_SEP = glsl_fold::mul(2.0f, PERSONAL_RADIUS);   // separation support (3D distance): 2.0 * PERSONAL_RADIUS
constexpr float BODY_DIAM = glsl_fold::mul(2.0f, BODY_RADIUS);   // hard contact distance (3D): 2.0 * BODY_RADIUS
static_assert(R_SEP == 0.016f && BODY_DIAM == 0.0128f, "doubling a float is exact");
static_assert(BODY_RADIUS < PERSONAL_RADIUS, "the hard body lies inside the personal space");

// Personal-space repulsion (the soft personal space): r = K_SEP * (1 - d / R_SEP)^2 per neighbour closer than R_SEP,
// along the offset from it. It deflects the desired direction, e_dir = normalize(e_goal + sum r), the
// direction model of the collision-free speed model (Tordeux et al. 2016, below); at body contact (d = BODY_DIAM) one
// neighbour gives r = 0.04 K_SEP against the unit e_goal. A moderate value, calibrated in [10, 100] together with
// T_HEADWAY (results/validation/level_calibration: the smallest RMS speed error against Weidmann's fundamental diagram,
// rho 0.5-4, under the hard constraints; 100 is the range's upper bound). It steers agents around each other and spreads a
// dense corridor into lanes; the headway rule sets the speed.
constexpr float K_SEP = 100.0f;

// --- Fixed simulation step (model time units per physics dispatch) ---
constexpr float DT = 0.01f;

// --- Agent kinematics ---
// The free walking speed V0 (= V_FREE_M_S, 1.34 m/s, below) and the horizontal speed clamp, applied to the
// integrated velocity every step. The driving term relaxes the velocity towards v_des * e_dir with
// v_des <= V_MAX, so an unobstructed agent walks at exactly V_MAX.
constexpr float V_MAX = 0.75f;
// Gravity: real gravity GRAVITY_M_S2 in model units, length / time^2: x TIME_SCALE^2 /
// WORLD_SCALE = 96.03553. nv.z -= GRAVITY * DT. Folded in double
// from the decimal literals and rounded once; the preamble carries the value (its factors are host-side).
constexpr float GRAVITY_M_S2 = 9.81f;
constexpr float GRAVITY = float(glsl_fold::decimal(GRAVITY_M_S2) * glsl_fold::decimal(TIME_SCALE_S_PER_UNIT) *
                                glsl_fold::decimal(TIME_SCALE_S_PER_UNIT) / glsl_fold::decimal(WORLD_SCALE_M_PER_UNIT));
static_assert(GRAVITY > 96.0f && GRAVITY < 96.1f, "9.81 m/s^2 = 96.04 model units at 31.25 m and 17.49 s per unit");

// --- Driving term and headway speed rule (physics.comp predict pass, CpuCrowdSim) ---
// Velocity relaxation (the driving term of the social force model, Helbing & Molnar 1995, Phys. Rev. E 51, 4282;
// citation not yet checked against the original): dv/dt = (v_des * e_dir - v) / TAU_RELAX + a_obs, e_dir the desired direction (the router's unit
// direction e_goal deflected by the personal-space repulsion, K_SEP above) and a_obs the obstacle avoidance. Integrated
// exactly over a step for constant inputs: v(DT) = v_eq + (v - v_eq) * exp(-DT / TAU_RELAX), v_eq = v_des * e_dir +
// TAU_RELAX * a_obs (DT-consistent). Without neighbours or walls e_dir = e_goal and v -> v_des * e_goal = V_MAX * e_goal: the
// free speed is V0 by construction. TAU_RELAX_S is the real relaxation time; TAU_RELAX is it in model time, folded in
// double from the decimal literals and rounded once (the preamble carries the value; its factors are host-side).
constexpr float TAU_RELAX_S = 0.5f;
constexpr float TAU_RELAX = float(glsl_fold::decimal(TAU_RELAX_S) / glsl_fold::decimal(TIME_SCALE_S_PER_UNIT));
// Headway speed rule (the collision-free speed model, Tordeux, Chraibi & Seyfried 2016, "Collision-free speed model
// for pedestrian dynamics", Traffic and Granular Flow '15, Springer; citation not yet checked against the original): v_des = clamp((s - 2 *
// BODY_RADIUS) / T_HEADWAY, 0, V_MAX), s the horizontal centre distance to the nearest agent AHEAD: a neighbour counts if
// its offset projects positively onto e_goal and lies less than BODY_DIAM from the agent's path (lateral offset). No
// agent ahead within R_PERC: v_des = V_MAX. Two additions to the published rule: v_des also bounds the
// velocity's component along e_goal after the relaxation (the speed model is collision-free because it sets the speed;
// relaxing over TAU_RELAX an agent could not brake within a short time gap), and a mutual standoff (each agent ahead in
// the other's lane, along the other's own e_goal: merges, crossings) is broken by letting only the agent that has the
// other more directly ahead yield. T_HEADWAY_S (the time gap, real seconds) is the calibration parameter: 0.3 s
// (with K_SEP; RMS 0.126 m/s against Weidmann, max flow 80.4 persons/(m min): results/validation/level_calibration).
constexpr float T_HEADWAY_S = 0.3f;
constexpr float T_HEADWAY = float(glsl_fold::decimal(T_HEADWAY_S) / glsl_fold::decimal(TIME_SCALE_S_PER_UNIT));
// The neighbour search radius of the predict pass (horizontal distance): the separation partners (R_SEP <= R_PERC) and
// the headway look-ahead. A leader farther than BODY_DIAM + V_MAX * T_HEADWAY does not slow its follower (v_des = V_MAX),
// so R_PERC at least that makes the look-ahead's cutoff invisible (static_assert below): the headway rule is exactly the
// formula above for every gap. The predict pass searches PERC_RING grid cells to each side (a (2 PERC_RING + 1)^2 ring).
// 0.045 (1.41 m; the 3x3 ring) covers T_HEADWAY up to 0.75 s. Any covering R_PERC gives bit-identical results (the repulsion
// partners lie within R_SEP, in the inner cells, summed in the same order), verified on the golden states.
constexpr float R_PERC = 0.045f;

// --- Hard-body projection (physics.comp PHYSICS_PASS 2 and 3, CpuCrowdSim) ---
// After the integration and before the final static contacts, PROJ_ITERATIONS Jacobi iterations in
// sorted-slot space: every pair closer than BODY_DIAM (3D) is moved apart along its XY offset (the pair's
// hash direction when stacked) to the XY distance at which its 3D distance is BODY_DIAM, each member
// taking half; an agent's correction is the mean over its contacts, scaled by PROJ_RELAX and capped at
// PROJ_MAX_SHIFT per iteration. The velocity is not changed (adding correction / DT to it would carry every push of a jam
// into the next steps). PROJ_ITERATIONS is host-side (the number of dispatches); 0
// switches the projection off (CrowdSim::setProjectionIterations, diagnostics only).
// PROJ_RELAX within (0, 1] (no over-relaxation), PROJ_ITERATIONS chosen for the overlap limits
// (test_gpu validation.plausibility_terrace: p99 <= 5%, max <= 20% of BODY_DIAM).
constexpr int PROJ_ITERATIONS = 32;
constexpr float PROJ_RELAX = 1.0f;
constexpr float PROJ_MAX_SHIFT_RADII = 0.05f;
constexpr float PROJ_MAX_SHIFT = glsl_fold::mul(PROJ_MAX_SHIFT_RADII, BODY_RADIUS);   // PROJ_MAX_SHIFT_RADII * BODY_RADIUS

// --- Steering weights ---
// The personal-space repulsion (K_SEP above) acts in the desired direction, not as an added acceleration
// (as an acceleration it keeps pushing agents that the headway rule has stopped: a standing queue drifts towards its
// free side, off the tread fronts, about 2.5 times as many falls between rows). The obstacle avoidance is an
// acceleration a_obs (W_OBS below): a repulsion from walls and the fence at torso height that keeps agents off walls
// before the hard contact acts. The velocity stays clamped to V_MAX.
constexpr float W_OBS = 10.0f;     // obstacle avoidance
constexpr float GOAL_DEADZONE = 1e-4f;  // e_goal = 0 closer than this to the waypoint
// Obstacle avoidance: the scene distance d is sampled TORSO_HEIGHT above the centre (above the
// treads); within OBSTACLE_RANGE it pushes along the scene normal by
// (OBSTACLE_RANGE - d) * W_OBS * OBSTACLE_GAIN, unless that normal is shorter than
// OBSTACLE_MIN_NORMAL. The baked term's normal uses tetrahedral differences with step OBSTACLE_GRAD_H.
constexpr float TORSO_HEIGHT = 0.05f;
constexpr float OBSTACLE_RANGE = 0.025f;
constexpr float OBSTACLE_GAIN = 20.0f;
constexpr float OBSTACLE_MIN_NORMAL = 0.01f;
constexpr float OBSTACLE_GRAD_H = 0.0015f;
// Numerical guards: safeNormalize returns 0 for a vector no longer than SAFE_NORMALIZE_EPS; a pair
// with |xy offset|^2 <= SEP_STACKED_XY2 (|xy| <= 1e-6) is stacked and separates along its hash direction
constexpr float SAFE_NORMALIZE_EPS = 1e-8f;
constexpr float SEP_STACKED_XY2 = 1e-12f;

// --- Static contact with the baked stadium (physics.comp restOnFloor / clearWalls), hard: BODY_RADIUS ---
// After every step the agent centre rests BODY_RADIUS above any floor (vertical clearance: treads,
// aisles, walkway, avenues and the CSG ground plane alike) and keeps BODY_RADIUS horizontal clearance
// from any wall or fence.
// Floor: the zero crossing on the vertical under the centre, searched down to BODY_RADIUS below it, or,
// with the centre in solid, up to BODY_RADIUS above the start-of-step centre height (one step of real
// gravity, GRAVITY * DT^2 = 9.6e-3, sinks a resting centre below its floor and a falling one by up to
// ~2.9e-2), through at most FLOOR_SEARCH_CELLS voxel levels.
constexpr int FLOOR_SEARCH_CELLS = 4;
// A grounded agent that a wall push moved sideways settles onto the floor of its new column, searched down to
// FLOOR_SETTLE_REACH below its centre (lower or higher; deeper than that it falls)
constexpr float FLOOR_SETTLE_RADII = 1.5f;
constexpr float FLOOR_SETTLE_REACH = glsl_fold::mul(FLOOR_SETTLE_RADII, BODY_RADIUS);   // FLOOR_SETTLE_RADII * BODY_RADIUS
// Walls: FEELER_COUNT feelers (every 22.5 degrees) reach FEELER_REACH out in the centre's
// plane; 1.25 cos(11.25 deg) > 1, so any flat wall within BODY_RADIUS puts one in solid, and a convex corner (the
// end of a tread block, an aisle mouth), which a 6.4 mm body could pass between feelers 45 degrees apart, is seen.
// Derived constants (FEELER_REACH, WALL_RECAST_TOL) reach the shaders as expressions of their
// factors, which the GLSL compiler folds; the values here are that fold (glsl_fold above).
constexpr float FEELER_REACH_RADII = 1.25f;
constexpr float FEELER_REACH = glsl_fold::mul(FEELER_REACH_RADII, BODY_RADIUS);
constexpr int FEELER_COUNT = 16;
constexpr std::array<Float2, FEELER_COUNT> FEELER_DIRS{ {
    { 1.0f, 0.0f }, { 0.92387953f, 0.38268343f }, { 0.70710678f, 0.70710678f }, { 0.38268343f, 0.92387953f }, { 0.0f, 1.0f }, { -0.38268343f, 0.92387953f }, { -0.70710678f, 0.70710678f }, { -0.92387953f, 0.38268343f },
    { -1.0f, 0.0f }, { -0.92387953f, -0.38268343f }, { -0.70710678f, -0.70710678f }, { -0.38268343f, -0.92387953f }, { 0.0f, -1.0f }, { 0.38268343f, -0.92387953f }, { 0.70710678f, -0.70710678f }, { 0.92387953f, -0.38268343f } } };
// From a feeler in solid: WALL_ROOT_STEPS safeguarded Newton steps to the surface point q1, then
// WALL_RECAST_STEPS Newton steps along the normal there; the recast is accepted as the foot point
// if its last step moved less than WALL_RECAST_TOL.
constexpr int WALL_ROOT_STEPS = 3;
constexpr int WALL_RECAST_STEPS = 2;
constexpr float WALL_RECAST_TOL_RADII = 0.02f;
constexpr float WALL_RECAST_TOL = glsl_fold::mul(WALL_RECAST_TOL_RADII, BODY_RADIUS);
constexpr float WALL_MAX_NZ = 0.6f;       // contact normal n_z <= this: wall; above: walkable slope
constexpr int WALL_PASSES = 3;            // clearWalls passes (later ones resolve corners)
constexpr float CENTRE_GRAD_MIN = 1e-3f;  // |grad xy| floor when the centre itself is in solid
// Static sweep: a centre left in solid without a floor in reach goes back along its step to the
// obstacle's face (bisection on the horizontal segment at the start-of-step height)
constexpr int STATIC_SWEEP_BISECTIONS = 8;
// Wall plane probe: where the feelers (FEELER_REACH) find no wall, the projection's wall plane comes
// from the same feelers reaching PLANE_PROBE_REACH (walls the projection could push an agent into in a step)
constexpr float PLANE_PROBE_RADII = 2.5f;
constexpr float PLANE_PROBE_REACH = glsl_fold::mul(PLANE_PROBE_RADII, BODY_RADIUS);   // PLANE_PROBE_RADII * BODY_RADIUS
// Feeler offsets FEELER_DIRS[i] * reach as float products, computed here once and emitted as preamble arrays:
// with 16 feelers the GLSL compiler's folding of FEELER_DIRS[i] * FEELER_REACH differs from the float product
// by one ulp for the 22.5-degree directions; arrays of literals hold the same bits on both sides by construction
constexpr std::array<Float2, FEELER_COUNT> feelerOffsets(float reach) {
    std::array<Float2, FEELER_COUNT> o{};
    for (size_t i = 0; i < size_t(FEELER_COUNT); ++i) o[i] = { FEELER_DIRS[i].x * reach, FEELER_DIRS[i].y * reach };
    return o;
}
constexpr std::array<Float2, FEELER_COUNT> FEELER_OFFSETS = feelerOffsets(FEELER_REACH);       // clearWalls' feelers
constexpr std::array<Float2, FEELER_COUNT> PROBE_OFFSETS = feelerOffsets(PLANE_PROBE_REACH);   // wallPlaneProbe's

// --- Step-up limit (physics.comp limitStepUp, CpuCrowdSim): the last operation of every step ---
// A pedestrian steps up at most MAX_STEP_UP_M in one step and cannot climb a surface too steep to walk on. Checked for every
// active agent after the projection and the final static contacts (so no pass can bypass it), on the horizontal segment of
// its move from its start-of-step centre, against f0, the floor under that centre (the floor contact's zero crossing
// searched down to STEP_UP_FLOOR_REACH; none in reach: f0 = the end of that search). The move is blocked if
//   (a) the floor under its end lies higher than f0 + MAX_STEP_UP (that column is solid at that height), or
//   (b) at a point of the segment (sampled every STEP_UP_SAMPLE, the end included) the floor lies higher than f0 +
//       STEP_UP_TOL on a wall-steep surface (normal n_z <= WALL_MAX_NZ, the contact model's own wall threshold) that the
//       move climbs (any ascent along the move).
// (b) is needed in the baked terrace: its 0.55 m risers are ramps whose middle is a
// wall-steep band (n_z 0.18-0.54) between walkable fillets, so a pressed crowd climbs a row in moves far below any height
// limit: creeping a few millimetres per step up the band, or crossing
// the band in one move of 0.14-0.27 m from the bottom fillet onto the top one. Outside the
// aisles the bands separate every pair of rows (no walkable route over a riser, at any threshold n_z 0.6-0.85); a band is
// 1.7-12 mm (model) wide and STEP_UP_SAMPLE is half the narrowest, so every crossing puts a sample on it. In an exact venue
// a vertical riser has no band (the floors on both sides are level): (a) decides there.
// A blocked move is resolved like a wall: back along the segment to the last point the agent may stand on
// (STEP_UP_BISECTIONS bisections between the last allowed sample and the next), then the rest of the move along the face
// (its component along the tangent of the face at the blocking point, the field's horizontal gradient giving the normal),
// veering away from the face by the angles of STEP_UP_SLIDE_DIRS until one such slide is allowed too; then the velocity
// into the face is removed and the centre settles from its start-of-step height on the floor there (FLOOR_SETTLE_REACH;
// none in reach: it keeps falling). The veer is needed because the bake's faces undulate along their length (lateral slope
// on the bands: median 0.05, p90 0.15 of rise over run, more at the wing corners): along the tangent a slide can climb a
// little further on, and an agent that fell onto a ramp would be pinned there, with every queue behind it. Downhill (away
// from the face) a slide does not
// climb. Floors at or below f0 + STEP_UP_TOL are never blocked: level and downward moves are unchanged.
// MAX_STEP_UP_M = 0.30 m: midway between the largest step a crowd must climb, 0.14 m (the
// terrace aisle's sub-steps; stadium aisle stairs are typically at most ~0.20 m per riser, not yet checked against the applicable
// code) and the smallest it must not, 0.40 m (the seated venues' row risers; their seat blocks are 0.45 m, the terrace's
// risers 0.55 m), a 0.10 m margin on either side for the bake's blur of steps into ramps. In model units: folded in double
// from the decimal literals and rounded once (the preamble carries the value; its factors are host-side).
constexpr float MAX_STEP_UP_M = 0.30f;
constexpr float MAX_STEP_UP = float(glsl_fold::decimal(MAX_STEP_UP_M) / glsl_fold::decimal(WORLD_SCALE_M_PER_UNIT));
static_assert(MAX_STEP_UP > 0.0095f && MAX_STEP_UP < 0.0097f, "0.30 m = 0.0096 model units at 31.25 m per unit");
// Rounding level (0.03 mm): a floor this little above f0 is level ground (floor heights are exact texel arithmetic on
// both sides, equal up to rounding)
constexpr float STEP_UP_TOL = 1e-6f;
constexpr float STEP_UP_FLOOR_REACH_RADII = 6.0f;   // f0 searched down to 6 BODY_RADIUS (1.2 m) below the centre
constexpr float STEP_UP_FLOOR_REACH = glsl_fold::mul(STEP_UP_FLOOR_REACH_RADII, BODY_RADIUS);   // STEP_UP_FLOOR_REACH_RADII * BODY_RADIUS
constexpr int STEP_UP_BISECTIONS = 8;
// Path samples: every STEP_UP_SAMPLE_RADII * BODY_RADIUS (0.8 mm model, 2.5 cm), at most STEP_UP_MAX_SAMPLES per move
// (beyond 32 x 0.8 mm the spacing grows; a step moves at most the neighbour grid's bound, 18.6 mm: 24 samples)
constexpr float STEP_UP_SAMPLE_RADII = 0.125f;
constexpr float STEP_UP_SAMPLE = glsl_fold::mul(STEP_UP_SAMPLE_RADII, BODY_RADIUS);   // STEP_UP_SAMPLE_RADII * BODY_RADIUS
constexpr int STEP_UP_MAX_SAMPLES = 32;
static_assert(STEP_UP_MAX_SAMPLES * STEP_UP_SAMPLE >= 0.5f * (DOMAIN_SPAN / GRID_RES - BODY_DIAM),
              "a move within the neighbour grid's bound is sampled at the full density");
// The slides tried after a block, in order: (cos, sin) of the veer away from the face, 0, 30 and 60 degrees (a slide is
// tangent * cos + normal * |tangent| * sin); preamble array literals, the same bits on both sides
constexpr int STEP_UP_SLIDE_TRIES = 3;
constexpr std::array<Float2, STEP_UP_SLIDE_TRIES> STEP_UP_SLIDE_DIRS{ { { 1.0f, 0.0f }, { 0.86602540f, 0.5f }, { 0.5f, 0.86602540f } } };
// The window (f0 + STEP_UP_TOL, f0 + MAX_STEP_UP] is shorter than a voxel, so the floor search in it visits at most two
// voxel cells (physics.comp stepUpWindow)
static_assert(MAX_STEP_UP < SDF_SPACING, "the step-up window must be shorter than one SDF voxel");
// f0's search stays within floorUnderReach's FLOOR_SEARCH_CELLS voxel levels below the centre
static_assert(STEP_UP_FLOOR_REACH <= (FLOOR_SEARCH_CELLS - 1) * SDF_SPACING, "the start floor's search must fit in FLOOR_SEARCH_CELLS");

// --- Pitch fence: analytic CSG collision (physics.comp sdFence) ---
// stadium.obj pitch fence (tools/measure_fence.py)
//   components: 441 (by OBJ vertex index); pitch floor x[-0.328395,+0.328395] y[-0.328395,+0.328395]
//   fence pieces: 4 axis-aligned boxes
//     x[-0.335432,+0.335432] y[+0.328395,+0.335432] z[0.000000,0.025802]
//     x[-0.335432,+0.335432] y[-0.335432,-0.328395] z[0.000000,0.025802]
//     x[-0.335432,-0.328395] y[-0.328395,+0.328395] z[0.000000,0.025802]
//     x[+0.328395,+0.335432] y[-0.328395,+0.328395] z[0.000000,0.025802]
//   center             (+0.000000, +0.000000)
//   outer half-extents (0.335432, 0.335432)
//   inner half-extents (0.328395, 0.328395)
//   midline half-ext.  (0.331913, 0.331913)
//   thickness          +x 0.007037, -x 0.007037, +y 0.007037, -y 0.007037
//   z_min, z_max       0.000000, 0.025802
//   gates              0 (midline perimeter 2.655308 sampled every 0.0002)
// The fence is 7 mm thick, thinner than one stadium.sdf voxel (15 mm), so the baked field does
// not contain it; the collision fence is analytic instead.
struct FenceGate { Float2 center, halfSize; };  // opening cut through the fence (box footprint)

constexpr float FENCE_HALF_INNER = 0.328395f;   // measured inner face
constexpr float FENCE_HALF_OUTER = 0.335432f;   // measured outer face
constexpr Float2 FENCE_CENTER{ 0.0f, 0.0f };
constexpr Float2 FENCE_HALF_MID{ 0.5f * (FENCE_HALF_INNER + FENCE_HALF_OUTER), 0.5f * (FENCE_HALF_INNER + FENCE_HALF_OUTER) };
constexpr float FENCE_HALF_THK_VISUAL = 0.5f * (FENCE_HALF_OUTER - FENCE_HALF_INNER);
constexpr std::array<FenceGate, 0> FENCE_GATES{};  // measured: none, the ring is closed

// Collision half-thickness = visual half-thickness + BODY_RADIUS: the collision faces are where a
// disk agent's centre stops, BODY_RADIUS clear of the rendered fence. This inflation is the body
// radius, not an anti-tunneling margin: tunneling is prevented by exact continuous collision
// (physics.comp fenceCCD clamps any step whose segment crosses the fence midline to the face it
// came from), which holds for any step length.
constexpr float FENCE_HALF_THK_COLL = FENCE_HALF_THK_VISUAL + BODY_RADIUS;
constexpr int FENCE_CCD_BISECTIONS = 8;  // fenceCCD: bisection steps towards the old-side face

// --- Router: stadium layout (measured from stadium.obj) ---
// Four L-shaped stands around the pitch, separated by two floor-level avenues along the axes that
// run out through gaps in the outer wall: the only exits. Distances are per stand wing: 'lat' =
// distance from the avenue centreline, 'dep' = Chebyshev depth max(|x|, |y|) from the pitch
// centre. Each stand is walled off from its avenue (lat 0.094..0.104, from dep 0.4225 outward) and
// drained by an aisle beside that wall that steps down in 4.4 mm increments from the platform to
// the floor-level walkway (dep WALKWAY_MIN..WALKWAY_MAX), which is open to the avenue. The pitch
// fence (dep 0.328..0.335) is collided analytically and has no gates, so the pitch is closed off.
// The walkway starts at the measured outer fence face (the fence is square and centred on the origin).
constexpr float WALKWAY_MIN = FENCE_HALF_OUTER;
constexpr float WALKWAY_MAX = 0.422f;
constexpr float WALKWAY_CENTRE = 0.380f;
constexpr float AVENUE_HALF = 0.090f;
constexpr float AISLE_MAX = 0.152f;
constexpr float AISLE_CENTRE = 0.128f;
constexpr float AVENUE_TARGET_DEPTH = 1.2f;     // avenue waypoint: out past the wall gap
constexpr float PITCH_RECOVERY_MARGIN = 0.02f;  // pitch-recovery waypoint depth: WALKWAY_MIN + this
// Exit: an agent past EXIT_DEPTH below EXIT_MAX_Z (a wall gap at ground level), or outside the
// domain, is parked at (PARK_COORD, PARK_COORD, PARK_COORD) with position.w = 0 (inactive)
constexpr float EXIT_DEPTH = 0.930f;
constexpr float EXIT_MAX_Z = 0.050f;
constexpr float PARK_COORD = 1000.0f;

// --- Physical units ---
// What the model scales WORLD_SCALE_M_PER_UNIT and TIME_SCALE_S_PER_UNIT (top of this file) stand for.
// Apart from GRAVITY, TAU_RELAX and T_HEADWAY (real values in model units), every constant above stays in model units
// and these real values are host-side, for reports.
//   length: the personal-space radius PERSONAL_RADIUS is PERSONAL_RADIUS_M, and the hard body radius
// BODY_RADIUS is BODY_RADIUS_M (31.25 m per model unit);
//   time:   the desired (clamped) speed V_MAX is the free walking speed V_FREE_M_S.
// PERSONAL_RADIUS_M: Fruin's body ellipse (Fruin 1971, "Pedestrian Planning and Design"; 0.25 m is a common
// circle equivalent of it, as reported in that source; not yet checked against the original): the personal
// space. BODY_RADIUS_M: 0.20 m, the hard body (hexagonal packing of 0.40 m disks: 7.2 persons/m^2).
// V_FREE_M_S: mean free walking speed, as reported in Weidmann 1993 ("Transporttechnik der Fussgaenger", ETH
// Zuerich, Schriftenreihe IVT Nr. 90); not yet checked against the original.
constexpr float PERSONAL_RADIUS_M = 0.25f;
constexpr float BODY_RADIUS_M = 0.20f;
constexpr float V_FREE_M_S = 1.34f;
// The scales are explicit; these state what they stand for (folded in double from the decimal literals)
static_assert(float(glsl_fold::decimal(PERSONAL_RADIUS) * glsl_fold::decimal(WORLD_SCALE_M_PER_UNIT)) == PERSONAL_RADIUS_M,
              "PERSONAL_RADIUS is PERSONAL_RADIUS_M: 0.008 x 31.25 m = 0.25 m");
static_assert(float(glsl_fold::decimal(BODY_RADIUS) * glsl_fold::decimal(WORLD_SCALE_M_PER_UNIT)) == BODY_RADIUS_M,
              "BODY_RADIUS is BODY_RADIUS_M: 0.0064 x 31.25 m = 0.20 m");
static_assert(TIME_SCALE_S_PER_UNIT == float(glsl_fold::decimal(V_MAX) * glsl_fold::decimal(WORLD_SCALE_M_PER_UNIT) /
                                             glsl_fold::decimal(V_FREE_M_S)),
              "V_MAX is V_FREE_M_S: 0.75 x 31.25 m / 17.490671 s = 1.34 m/s");

// Model -> real conversions (double, for reports; the float scale factors above are the definition)
namespace units {
constexpr double M_PER_UNIT = double(WORLD_SCALE_M_PER_UNIT);
constexpr double S_PER_UNIT = double(TIME_SCALE_S_PER_UNIT);
constexpr double metres(double modelLength) { return modelLength * M_PER_UNIT; }
constexpr double seconds(double modelTime) { return modelTime * S_PER_UNIT; }
constexpr double metresPerSecond(double modelSpeed) { return modelSpeed * M_PER_UNIT / S_PER_UNIT; }
// and back
constexpr double modelLength(double m) { return m / M_PER_UNIT; }
} // namespace units

// One fixed step DT in real seconds (~0.175 s)
constexpr double DT_REAL_S = units::seconds(double(DT));
static_assert(DT_REAL_S >= 0.01 && DT_REAL_S <= 0.25, "DT must be 0.01-0.25 s in real time");

// gridID of evacuated agents (position.w == 0): sorts after every real cell
constexpr uint32_t INACTIVE_CELL = 0xFFFFFFFFu;

// --- Exit choice on analytic venues (physics.comp PHYSICS_PASS 0, CpuCrowdSim; swarm/exit_choice.hpp) ---
// The queue-aware mode ("queue-aware"; the nearest-exit field stays selectable as "nearest"). Every agent holds an
// assigned exit e and estimates its time to leave through each candidate exit of its cell (the K nearest by walking distance):
// E_e(x) = d_e(x) / V0 + A_e(x) / (w_e J),
// d_e the walking distance to e (per-exit distance fields), A_e the queue ahead (active agents assigned to e in nearer distance bins, integer atomics of
// the previous step's choice pass: deterministic), w_e the exit's clear width and J = EXIT_FLOW_P_M_MIN, a specific-flow
// capacity. In seconds: d_e x CHOICE_S_PER_UNIT + A_e x (60 / (w_e[m] J)) (the per-exit factors are venue data, emitted with
// the choice preamble). V0 = V_FREE_M_S (the level free speed). Every T_CHOICE of simulated time (CHOICE_STEPS steps) all agents
// re-evaluate on the same counts; an agent is eligible to switch to its best candidate only if that gains more than
// max(CHOICE_REL_MARGIN x E_current, CHOICE_ABS_MARGIN_S) (hysteresis), and of the eligible agents assigned to an exit at most
// max(CHOICE_MIN_SWITCHES, CHOICE_SWITCH_SHARE x Q_e) switch per evaluation, the largest gains first (whole gain bins of
// CHOICE_GAIN_BIN_S = 1 s, an integer histogram per exit: deterministic). Rules and their reasons: swarm/exit_choice.hpp.
// J: the model's own measured door flow under the default model, a fixed point: venue S's 100% GPU
// evacuation with the queue-aware exit choice and the incline speed, the mean over its 8 concourse doors (1.20 m) of their mean specific
// flows: with J = 83.6 the doors give 82.8 persons/(m min) (-1.0%: consistent).
// A door fed by an up-stair gangway at 0.58 m/s discharges ~30% less than with level walking (119.8), a value that would
// understate every door queue's wait.
constexpr float T_CHOICE_S = 3.0f;              // re-evaluation interval, real seconds
constexpr float T_CHOICE = float(glsl_fold::decimal(T_CHOICE_S) / glsl_fold::decimal(TIME_SCALE_S_PER_UNIT));   // model time
// Steps per re-evaluation interval: GLSL int(T_CHOICE / DT + 0.5) in physics.comp (an expression of DT, so a DT / k shader
// variant re-evaluates every T_CHOICE of simulated time too); 17 at DT (2.97 s)
constexpr int choiceSteps(float dt) { return int(glsl_fold::decimal(T_CHOICE) / glsl_fold::decimal(dt) + 0.5); }
constexpr int CHOICE_STEPS = choiceSteps(DT);
static_assert(CHOICE_STEPS == 17, "T_CHOICE = 3 s is 17 steps of DT");
constexpr float CHOICE_REL_MARGIN = 0.10f;      // hysteresis: the gain must exceed this share of E_current ...
constexpr float CHOICE_ABS_MARGIN_S = 5.0f;     // ... and this many seconds
constexpr float CHOICE_SWITCH_SHARE = 0.10f;    // per evaluation at most this share of an exit's assigned agents switch away ...
constexpr int CHOICE_MIN_SWITCHES = 1;          // ... but at least this many (an exit with few agents still releases them)
constexpr int CHOICE_GAIN_BINS = 256;           // the gain histogram: bins of 1 s (CHOICE_GAIN_BIN_S), gains >= 255 s in the last
constexpr float CHOICE_GAIN_BIN_S = 1.0f;       // bin width, seconds: the bin is uint(gain) (no division)
constexpr float EXIT_FLOW_P_M_MIN = 83.6f;      // J, persons per metre of clear width per minute
// Seconds per model unit of walking distance at V0 (31.25 m / 1.34 m/s), folded in double from the decimal literals
constexpr float CHOICE_S_PER_UNIT = float(glsl_fold::decimal(WORLD_SCALE_M_PER_UNIT) / glsl_fold::decimal(V_FREE_M_S));

// --- Incline speed on analytic venues (physics.comp predict pass, VENUE_INCLINE_SPEED; CpuCrowdSim) ---
// The free walking speed on a walkable incline depends on the direction of travel. An analytic venue's gangway inclines stand for
// stepped gangways (venue S: a 26.57 deg incline, rendered without steps), so stair-walking speeds apply. Horizontal speeds:
//   V_STAIR_UP_M_S   = 0.58 m/s:  Fruin (1971), "Pedestrian Planning and Design", ascending a 27 deg (outdoor) stair: the mean of his four
//                                 groups as Fujiyama & Tyler (2004) tabulate them (Table 6, horizontal speeds): male / female aged over 50
//                                 0.41 / 0.45, aged 30-50 0.81 / 0.65 m/s;
//   V_STAIR_DOWN_M_S = 0.655 m/s: the same source and table, descending: 0.60 / 0.56, 0.81 / 0.65 m/s.
// Values as reported in the cited sources; not yet checked against the originals (Fruin's own tables; the groups weighted equally: a choice). For comparison, Fujiyama & Tyler's own
// laboratory measurements (T. Fujiyama, N. Tyler, "An explicit study on walking speeds of pedestrians on stairs", 10th TRANSED conference,
// Hamamatsu, 2004; Table 3, unimpeded individuals, horizontal): at 24.6 deg ascending 0.73 (mean age 71) / 0.76 m/s (mean age 35),
// descending 0.80 / 0.87 m/s; at 30.5 deg 0.59 / 0.63 and 0.64 / 0.74 m/s (as reported there; not yet checked against the original). Field observations (Fruin)
// are chosen: they are slower than the laboratory's, which Fujiyama & Tyler attribute to the surrounding people in real facilities.
// The free speed by the slope along the travel direction, inclineFreeSpeed(g) (physics.comp, seated::inclineFreeSpeed): g = the floor's
// rise per unit of horizontal travel along e_goal (> 0 ascending, < 0 descending; venue S's gangway walked straight up: +0.5),
//   v0(g) = V_MAX + (v_stair - V_MAX) s(|g| / INCLINE_REF_SLOPE),  s(u) = u^2 (3 - 2u) for u in [0, 1] (smoothstep), 1 beyond,
// v_stair = V_STAIR_UP for g > 0, V_STAIR_DOWN for g < 0; INCLINE_REF_SLOPE = tan(27 deg), the source stair's gradient. Continuous with
// a continuous first derivative in g (zero slope at g = 0: level floors keep exactly V_MAX); across a gangway (g = 0) the level speed.
// v0 replaces V_MAX as the headway rule's upper bound (v_des); |v_xy| <= V_MAX stays the clamp.
constexpr float V_STAIR_UP_M_S = 0.58f;
constexpr float V_STAIR_DOWN_M_S = 0.655f;
constexpr float INCLINE_REF_SLOPE = 0.50952545f;   // tan(27 deg)
constexpr float V_STAIR_UP = float(glsl_fold::decimal(V_STAIR_UP_M_S) * glsl_fold::decimal(TIME_SCALE_S_PER_UNIT) /
                                   glsl_fold::decimal(WORLD_SCALE_M_PER_UNIT));      // model units
constexpr float V_STAIR_DOWN = float(glsl_fold::decimal(V_STAIR_DOWN_M_S) * glsl_fold::decimal(TIME_SCALE_S_PER_UNIT) /
                                     glsl_fold::decimal(WORLD_SCALE_M_PER_UNIT));
constexpr float INCLINE_INV_REF_SLOPE = float(1.0 / glsl_fold::decimal(INCLINE_REF_SLOPE));
static_assert(V_STAIR_UP < V_STAIR_DOWN && V_STAIR_DOWN < V_MAX, "stairs are slower than the level, ascending slower than descending");

// --- Stair spacing on analytic venues (physics.comp predict pass, VENUE_STAIR_HEADWAY; CpuCrowdSim) ---
// The incline speed alone leaves the crowd's spacing at its level-ground value (the headway rule, calibrated on level ground),
// so a gangway carries about 1.8x the stair planning flows. On a gangway incline the headway rule's time gap is a function of the
// slope g along the travel direction, blended exactly like the free speed (the same smoothstep s, the same reference slope):
//   T(g) = T_HEADWAY + (T_stair - T_HEADWAY) s(min(|g| / INCLINE_REF_SLOPE, 1)),  T_stair = T_HEADWAY_STAIR_UP (g > 0) | _DOWN (g < 0),
// and v_des = clamp((s - BODY_DIAM) / T(g), 0, v0(g)). On level floors (g = 0) the rule is the level one bit for bit. Two parameter sets,
// each calibrated with the stair harness (fd_harness stair: an inclined periodic corridor at a gangway's width, its maximum sustained
// specific flow; results/validation/stair_flow) to a target (values as reported in the cited sources; not yet checked against the originals):
//   EMPIRICAL (the default): Burghardt, Seyfried & Klingsch (2013), the measured maximum specific flows on stairs, 1.22 persons/(m s)
//     ascending and 1.25 descending;
//   CONSERVATIVE: the Green Guide's planning rate for stepped surfaces (6th ed., 2018), 66 persons/(m min) = 1.10 persons/(m s) both ways.
// ModelOptions::stairFlow (swarm/exit_choice.hpp) selects the set (off: the level spacing on the inclines too).
constexpr float T_HEADWAY_STAIR_UP_S = 0.625f;                // EMPIRICAL, ascending (harness maximum 1.220 persons/(m s))
constexpr float T_HEADWAY_STAIR_DOWN_S = 0.65f;               // EMPIRICAL, descending (1.260)
constexpr float T_HEADWAY_STAIR_UP_CONSERVATIVE_S = 0.75f;    // CONSERVATIVE, ascending (1.093)
constexpr float T_HEADWAY_STAIR_DOWN_CONSERVATIVE_S = 0.78f;  // CONSERVATIVE, descending (about 1.10)
// In model time, as T_HEADWAY (folded in double from the decimal literals, rounded once)
constexpr float stairHeadwayModel(float seconds) {
    return float(glsl_fold::decimal(seconds) / glsl_fold::decimal(TIME_SCALE_S_PER_UNIT));
}
constexpr float T_HEADWAY_STAIR_UP = stairHeadwayModel(T_HEADWAY_STAIR_UP_S);
constexpr float T_HEADWAY_STAIR_DOWN = stairHeadwayModel(T_HEADWAY_STAIR_DOWN_S);
constexpr float T_HEADWAY_STAIR_UP_CONSERVATIVE = stairHeadwayModel(T_HEADWAY_STAIR_UP_CONSERVATIVE_S);
constexpr float T_HEADWAY_STAIR_DOWN_CONSERVATIVE = stairHeadwayModel(T_HEADWAY_STAIR_DOWN_CONSERVATIVE_S);
// The headway look-ahead on an incline, BODY_DIAM + v0(g) T(g): both factors blend with the same s in [0, 1], so it is a quadratic in s,
// (V_MAX + (v_stair - V_MAX) s) (T_HEADWAY + (T_stair - T_HEADWAY) s); its largest value on [0, 1] (the ends or the vertex)
constexpr double stairLookAhead(float vStair, float tStair) {
    const double a = V_MAX, b = double(vStair) - V_MAX, c = T_HEADWAY, d = double(tStair) - T_HEADWAY;
    const double f0 = a * c, f1 = (a + b) * (c + d);
    double best = f0 > f1 ? f0 : f1;
    if (b * d != 0.0) {
        const double s = -(a * d + b * c) / (2.0 * b * d);
        if (s > 0.0 && s < 1.0) {
            const double fs = (a + b * s) * (c + d * s);
            best = fs > best ? fs : best;
        }
    }
    return double(BODY_DIAM) + best;
}
static_assert(T_HEADWAY_STAIR_UP >= T_HEADWAY && T_HEADWAY_STAIR_DOWN >= T_HEADWAY && T_HEADWAY_STAIR_UP_CONSERVATIVE >= T_HEADWAY_STAIR_UP &&
              T_HEADWAY_STAIR_DOWN_CONSERVATIVE >= T_HEADWAY_STAIR_DOWN, "stairs keep a larger spacing; the conservative set the largest");

// --- Constant expressions in physics.comp, as the GLSL compiler folds them ---
// The shader writes each of these as the expression in its comment; CpuCrowdSim uses the folded
// value, so both sides hold the same bits (test_gpu parity.constants reads every one back from the GPU).
constexpr float R_SEP2 = glsl_fold::mul(R_SEP, R_SEP);                          // R_SEP * R_SEP
constexpr float R_PERC2 = glsl_fold::mul(R_PERC, R_PERC);                       // R_PERC * R_PERC
constexpr float GRAVITY_DT = glsl_fold::mul(GRAVITY, DT);                       // GRAVITY * DT
constexpr float OBSTACLE_GRAD_SCALE = glsl_fold::div(0.25f, OBSTACLE_GRAD_H);   // 0.25 / OBSTACLE_GRAD_H (tetrahedral mean)
constexpr float PITCH_RECOVERY_DEPTH = glsl_fold::add(WALKWAY_MIN, PITCH_RECOVERY_MARGIN);  // WALKWAY_MIN + PITCH_RECOVERY_MARGIN
constexpr float HASH_TO_RADIANS = float(6.28318530718 / 4294967296.0);         // 6.28318530718 / 4294967296.0 (2 pi / 2^32)
// exp(-DT / TAU_RELAX): the driving term's decay over one step, folded in double as well (std::exp is not constexpr
// before C++26)
inline const float RELAX_STEP = float(std::exp(-glsl_fold::decimal(DT) / glsl_fold::decimal(TAU_RELAX)));
constexpr float HEADWAY_RATE = glsl_fold::div(1.0f, T_HEADWAY);                 // 1.0 / T_HEADWAY
constexpr float BODY_DIAM2 = glsl_fold::mul(BODY_DIAM, BODY_DIAM);              // BODY_DIAM * BODY_DIAM

// The predict pass searches PERC_RING cells to each side: every agent within R_PERC (horizontal) of a point in the
// centre cell lies in that ring
constexpr int PERC_RING = int(R_PERC / (DOMAIN_SPAN / GRID_RES)) + 1;
static_assert(PERC_RING * (DOMAIN_SPAN / GRID_RES) > R_PERC && (PERC_RING - 1) * (DOMAIN_SPAN / GRID_RES) <= R_PERC,
              "PERC_RING: the fewest cells that cover R_PERC");
// The headway look-ahead covers the rule's whole range: beyond BODY_DIAM + V_MAX * T_HEADWAY, v_des = V_MAX anyway
static_assert(R_PERC >= BODY_DIAM + V_MAX * T_HEADWAY, "R_PERC must cover the headway rule's look-ahead");
// And on the gangway inclines, for both stair-spacing sets and both directions
static_assert(R_PERC >= stairLookAhead(V_STAIR_UP, T_HEADWAY_STAIR_UP) && R_PERC >= stairLookAhead(V_STAIR_DOWN, T_HEADWAY_STAIR_DOWN) &&
              R_PERC >= stairLookAhead(V_STAIR_UP, T_HEADWAY_STAIR_UP_CONSERVATIVE) &&
              R_PERC >= stairLookAhead(V_STAIR_DOWN, T_HEADWAY_STAIR_DOWN_CONSERVATIVE),
              "R_PERC must cover the headway rule's look-ahead on the inclines");
// Separation partners are found by the perception search
static_assert(R_SEP <= R_PERC, "R_SEP must not exceed R_PERC");
// The projection and the final static contacts search the step's start-of-step grid (3x3 ring). A pair
// in non-adjacent cells starts more than a cell apart; it can come within BODY_DIAM only if its members
// move (DOMAIN_SPAN / GRID_RES - BODY_DIAM) / 2 = 0.0186 each. Integration moves an agent at most
// V_MAX * DT and the projection at most PROJ_ITERATIONS * PROJ_MAX_SHIFT; the static contacts push it back
// towards free space (test_gpu validation.plausibility_terrace measures the whole step's displacement at run time).
static_assert(V_MAX * DT + PROJ_ITERATIONS * PROJ_MAX_SHIFT <= 0.5f * (DOMAIN_SPAN / GRID_RES - BODY_DIAM),
              "the start-of-step neighbour grid must stay valid for the projection");
static_assert(PROJ_ITERATIONS >= 0 && PROJ_RELAX > 0.0f && PROJ_MAX_SHIFT > 0.0f, "projection parameters");

} // namespace swarm
