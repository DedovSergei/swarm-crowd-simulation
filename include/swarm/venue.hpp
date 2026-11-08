#pragma once

// Venues: the venue a simulation runs in, selected per simulation (CrowdSim, CpuCrowdSim, the viewer).
// - the baked TERRACE reference venue: stadium.obj / stadium.sdf, the 3D texture;
//   - analytic SEATED venues from a parametric generator (SeatedVenueParams, real units): a heightfield of boxes and
// inclines, evaluated as an exact signed distance in closed form (no texture): venues S, M and L.
// Every venue carries the neighbour grid it is simulated on (domain extent and GRID_RES; the cell size stays
// DOMAIN_SPAN / GRID_RES = 0.05 > R_PERC) and its exit test (EXIT_DEPTH, EXIT_MAX_Z).
// The per-venue shader preamble (shader.cpp shaderPreamble(venue)) emits them; for a seated venue it adds the layout
// (SeatedLayout, model units, as float literals) and the analytic distance code (shaders/venue_seated.glsl), which
// src/venue.cpp mirrors on the CPU line by line (CpuCrowdSim, tests, tools).
//
// SEATED VENUE GEOMETRY (all four quadrants alike, mirror-symmetric about both axes and both diagonals). Plan coordinates
// in the FOLDED frame: lat = min(|x|, |y|) (distance from the nearer avenue centreline), dep = max(|x|, |y|) (Chebyshev
// depth from the pitch centre: rows are square rings). Outward along dep:
//   pitch + analytic fence (sim_params.hpp, as in the terrace) | walkway (ground, z 0) | front barrier (a solid upstand
//   with gaps at the gangway feet) | rows k = 0 .. rows-1 | rear concourse | outer wall (with exits) | exterior landings |
//   ground. Across lat: avenue (ground, through the whole stand to the domain edge) | side wall (beside the barrier and the rows
//   a parapet at the barrier's / the row's seat-block top; beside the concourse a full wall) | stand.
//   Row k: front at d_k = row0 + k rowDepth; its tread at z_k = firstRow + k rowRise. The front `clearway` of the tread
//   (where people stand) and behind it the solid SEAT BLOCK, (rowDepth - clearway) deep, top seatTop above z_k. A seat
//   block's top is seatTop - rowRise above the next row's tread: no row can be crossed (INV-row) under MAX_STEP_UP.
//   Gangways: walking surface a continuous incline z = rake (dep - row0), rake = rowRise / rowDepth, through the back edge
//   of every clearway (firstRow = rake x clearway puts its foot at walkway level at row 0's front). Beside a clearway the
//   incline lies 0 .. rake x clearway below the tread: a row enters a gangway by stepping DOWN, never up a face.
//   One straight gangway per wing (lat in [gangwayLo, gangwayHi]) and one corner gangway per quadrant around the diagonal
//   (lat >= dep_front - cornerInset for the clearway of a row, dep_front its front; the seat block in front of it, row 0's
//   barrier, from seatInset earlier): a staircase band whose narrowest clear width is the gangway width. Seat blocks and the
//   barrier end seatInset (a body radius) short of every gangway's edge, so no wall face crosses a gangway's flow along its
// edge; the seats sit in front of the seat blocks only, so every seat keeps a seat block (row 0: the barrier) in front.
//   Between the side wall and the straight gangway: a dead-end segment; between the straight and the corner gangway: a
//   segment with a gangway at both ends.
// Generated venues (M, L): MORE STRAIGHT GANGWAYS where the rows grow long. Straight gangway i + 1 lies exactly
//   maxSeatsBetweenGangways seats beyond gangway i (its seat blocks' ends seatInset short of both); it starts at the first row
//   whose front reaches it (gangwayLo_i < row front - cornerInset: below that row its footprint lies in the corner gangway, so its
//   foot opens onto the corner gangway over its whole width) and runs up to the concourse. A row's last segment (from its last
//   straight gangway to the corner gangway) thus holds at most maxSeatsBetweenGangways seats; while it is too short for one seat
//   (the first rows after a gangway starts) the straight gangway and the corner gangway MERGE (one incline from the straight
// gangway's low edge to the diagonal). Venue S (rows up to 26 seats) has a single straight gangway.
// Exits (ExitLayout::DoorPerGangwayHead): a concourse door centred on every gangway head, the straight gangways' and the
//   corner gangway's (a door through the outer wall's corner, straddling the diagonal); all doors of a venue share one width, set
// by the capacity rule (buildSeatedLayout). Venue S has ExitLayout::DoorPerWing (one door per wing, centred on its
//   straight gangway; the corner gangways lead to concourse corners without doors).

#include <swarm/sim_params.hpp>

#include <glm/glm.hpp>

#include <array>
#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

namespace swarm {

// --- The generator's parameters, real units (metres) ---
struct SeatedVenueParams {
    const char* name;
    // Plan
    double walkwayWidthM;            // the fence's outer face -> the front barrier's front face
    double barrierThicknessM;        // the front barrier (solid from the walkway up)
    double avenueWidthM;             // clear width between the side walls
    double sideWallThicknessM;
    int rows;
    double rowDepthM;                // tread depth, riser to riser
    double clearwayM;                // the standing strip at the front of each tread
    double seatWidthM;               // seat pitch along the row
    double gangwayWidthM;
    double seatBlockInsetM;          // seat blocks and the barrier end this far short of a gangway's edge
    int maxSeatsBetweenGangways;     // a row segment with a gangway at both ends (as reported in the Guide to Safety at Sports Grounds; not yet checked against the original)
    int maxSeatsDeadEnd;             // a row segment with a gangway at one end only (same source, same caveat)
    double concourseWidthM;
    double outerWallThicknessM;
    double landingDepthM;            // exterior landing beyond each concourse exit
    // Heights
    double rowRiseM;
    double seatBlockTopM;            // above its own tread
    double barrierTopM;              // above the walkway
    double wallTopAboveConcourseM;   // side walls and outer wall
    // Concourse exits: per quadrant, sized to clear the quadrant's seats on their own (design rule, venue.cpp)
    int exitsPerQuadrant;
    double exitRatePerMMin;          // rate of passage, persons per metre width per minute (as reported in the same source; not yet checked against the original)
    double egressTimeMin;            // egress time the exits are sized for (same source, same caveat)
    double minExitWidthM;
    // Generated venues. Defaults: venue S's values (S's initializer leaves these out)
    enum class ExitLayout { DoorPerWing, DoorPerGangwayHead };
    ExitLayout exitLayout = ExitLayout::DoorPerWing;
    // The neighbour grid: gridRes cells per axis of DOMAIN_SPAN / GRID_RES (0.05 model units), the domain symmetric about 0
    // (half-width gridRes x 0.025); 0: the terrace's grid (DOMAIN_MIN, DOMAIN_SPAN, GRID_RES)
    int gridRes = 0;
    // The metric floor grid (swarm/metrics.hpp): cells of 1 m per axis, centred on 0, a multiple of 16; 0: the terrace's 64
    int metricGridRes = 0;
};

// --- The layout in model units: what the per-venue preamble emits (VS_* float literals) and the CPU mirror uses ---
// dep breakpoints: standFront (barrier front) < row0 (row 0 front = barrier back) < d_k = row0 + k rowDepth ... <
// concFront = d_rows (concourse) < concBack (outer wall inner face) < outerFace (outer wall outer face) < landingEnd.
// lat breakpoints: avenueHalf < lat0 (side wall's stand face) < gangwayLo < gangwayHi (straight gangway); exits
// [exitLo, exitHi]; corner gangway from dep_front - cornerInset.
constexpr int SEATED_MAX_GANGWAYS = 8;   // straight gangways per wing (the shader's arrays)
constexpr int SEATED_MAX_DOORS = 8;      // straight-gangway doors per wing
struct SeatedLayout {
    float standFront, row0, rowDepth, clearway;
    int rows;
    float concFront, concBack, outerFace, landingEnd;
    float avenueHalf, lat0, gangwayLo, gangwayHi, exitLo, exitHi, cornerInset;
    float seatInset;   // seat bands and the barrier: their segments end seatInset short of the gangways' edges
    float faceMargin;  // contacts: every centre ends its step this far off the side face of a column higher than its feet
    float wallAbove;   // contacts: walls are the faces reaching this far above the centre: the body's top, BODY_RADIUS
    float wallClear;   // contacts: the clearance a centre keeps from walls, BODY_RADIUS + faceMargin
    float firstRow, rowRise, seatTop, barrierTop, concourseZ, wallTop, rake;
    int maxBandSteps;  // the distance search visits at most this many bands on either side of the query's own band
    float seatWidth;   // spawn only (not in the preamble)
    // Straight gangways per wing: gwLo / gwHi their clearway edges (gangway 0 = gangwayLo / gangwayHi); gwRow: the first
    // row-front index r (0 .. rows; r = rows is the concourse front) where the gangway exists (row0 + r rowDepth - cornerInset >
    // gwLo); gwSeated: the first row-front index from which the segment after it holds a seat while it is the last straight gangway
    // (before it the gangway merges with the corner gangway). A band follows row-front r = (band - 1) / 2: the barrier r = 0, the
    // clearway of row k r = k, the seat block of row k r = k + 1 (the front of the row behind it).
    float domainHalf = 1.0f;   // the venue's domain half-width (the render mesh's ground ends there; not in the preamble)
    int gangways = 1;
    std::array<float, SEATED_MAX_GANGWAYS> gwLo{}, gwHi{};
    std::array<int, SEATED_MAX_GANGWAYS> gwRow{}, gwSeated{};
    // Concourse doors per wing (folded lat, the outer wall's band): door i centred on straight gangway i (door 0 = exitLo / exitHi);
    // cornerDoorLo: the corner gangway's door, lat >= cornerDoorLo up to the diagonal (no corner door: >= 1e9)
    int doors = 1;
    std::array<float, SEATED_MAX_DOORS> doorLo{}, doorHi{};
    float cornerDoorLo = 1e9f;
    // The exit sizing rule's figures (metres; reports): the clear width of each straight door and of the corner door, the total
    // exit width (doors + avenues) and the width the rule requires
    double doorWidthM = 0.0, cornerDoorWidthM = 0.0, totalExitWidthM = 0.0, requiredExitWidthM = 0.0;
    int seatTotal = 0;
    // Row-front index r: straight gangways present, and whether the last one merges with the corner gangway (no seat after it)
    int activeGangways(int r) const;
    bool mergedCorner(int r) const;
    int doorsPerQuadrant() const { return 2 * doors + (cornerDoorLo < 1e8f ? 1 : 0); }
    int gangwaysPerQuadrant() const { return 2 * gangways + 1; }
};

enum class VenueKind { BakedTerrace, AnalyticSeated };

struct Venue {
    VenueKind kind;
    const char* name;          // "terrace", "S"
    const char* objAsset;      // the render mesh: stadium.obj, venue_s.obj; nullptr (M and L): seated::mesh() of the layout
    // The neighbour grid (the terrace keeps sim_params.hpp's values)
    float domainMin, domainSpan;
    int gridRes;
    // The exit test of the predict pass: max(|x|, |y|) > exitDepth below exitMaxZ, or outside the domain
    float exitDepth, exitMaxZ;
    // The metric floor grid: metricGridRes 1 m cells per axis, centred on 0 (the terrace and S: 64)
    int metricGridRes = 64;
    // Seated venues only
    SeatedVenueParams params{};
    SeatedLayout layout{};
    bool seated() const { return kind == VenueKind::AnalyticSeated; }
    float domainMax() const { return domainMin + domainSpan; }
    float cellSize() const { return domainSpan / float(gridRes); }
};

const Venue& terraceVenue();   // the baked reference venue (sim_params.hpp values)
const Venue& venueS();         // seated venue S
const Venue& venueM();         // generated seated venue M (about 16k seats)
const Venue& venueL();         // generated seated venue L (about 64k seats)
const Venue& venueByName(const std::string& name);   // "terrace" | "S" | "M" | "L"; throws otherwise
const std::vector<const Venue*>& seatedVenues();     // S, M, L
// The parameters of a generated venue with the given row count (venue_probe's capacity search; M and L use it)
SeatedVenueParams generatedVenueParams(const char* name, int rows, int gridRes, int metricGridRes);

// The venue-specific part of the shader preamble (inserted after the simulation preamble). Terrace: empty. Seated:
// "#define VENUE_ANALYTIC 1", the navigation field's grid (nav::preambleDefines: VENUE_NAV_FIELD, NAV_*) and the VS_* layout literals, then shaders/venue_seated.glsl (read from shaderDir).
std::string venuePreamble(const Venue& v, const std::filesystem::path& shaderDir);
// The VS_* #defines alone (test_gpu parity.constants reads each back from the GPU)
std::string seatedDefines(const SeatedLayout& L);
// VS_GANGWAYS, VS_DOORS, VS_CORNER_DOOR_LO and the const arrays VS_GW_LO / HI / ROW / SEATED, VS_DOOR_LO / HI
std::string seatedArrays(const SeatedLayout& L);
struct SeatedConstant { const char* name; float value; bool isInt; };
std::vector<SeatedConstant> seatedConstants(const SeatedLayout& L);

// Builds the layout from the parameters (model units), checking the design rules (throws std::runtime_error on a
// violation): segments within the seat limits, the straight gangway reaching the walkway, rows not climbable
// (seatTop - rowRise > MAX_STEP_UP), a walkable rake, a clearway and seat at least a body wide, the venue inside the domain.
SeatedLayout buildSeatedLayout(const SeatedVenueParams& p, float domainHalf = DOMAIN_MAX);

namespace seated {

// --- Cells of the folded frame (shaders/venue_seated.glsl mirrors every function here) ---
// SIDE: the side wall beside the barrier and the rows, a parapet whose top follows the stand (the barrier's
// top, a row's seat-block top): a full-height wall there would put the seats beside it within the torso-height obstacle avoidance's
// range, which pushes them along the row
enum CellKind : int { GROUND = 0, TREAD = 1, SEAT = 2, INCLINE = 3, BARRIER = 4, WALL = 5, CONC = 6, SIDE = 7 };
const char* cellKindName(int kind);
// Bands along dep: 0 walkway (and pitch), 1 barrier, 2 + 2k clearway of row k, 3 + 2k seat block of row k,
// 2 + 2 rows concourse, +1 outer wall, +2 landing, +3 outside
int bandCount(const SeatedLayout& L);
void band(const SeatedLayout& L, int j, float& lo, float& hi);
int bandOf(const SeatedLayout& L, float dep);
// Cell c (0, 1, ...) of band j, ascending in lat: [l0, l1) and its kind (row: the tread row of TREAD / SEAT). The last
// cell of a band reaches to the band's upper dep bound (the diagonal fold: see venue.cpp). False past the last cell.
bool cell(const SeatedLayout& L, int j, int c, float& l0, float& l1, int& kind, int& row);
// Top height of a cell at depth dep
float cellTop(const SeatedLayout& L, int kind, int row, float dep);

// Folded coordinates (lat, dep) of a plan point, and back for a direction / gradient
glm::vec2 fold(glm::vec2 xy);
glm::vec2 unfoldDir(glm::vec2 xy, glm::vec2 foldedDir);   // (d_lat, d_dep) at plan point xy -> (d_x, d_y)

// The heightfield: the venue is solid exactly where z <= floorHeight(xy) (the fence is separate: sdFence)
float floorHeight(const SeatedLayout& L, glm::vec2 xy);
// The cell kind (and row) under xy
int cellAt(const SeatedLayout& L, glm::vec2 xy, int* row = nullptr, int* band = nullptr);
// The cell under xy as a key (its band, its lateral start; GLSL venueCellKey); the floor is continuous within a cell
glm::vec2 cellKey(const SeatedLayout& L, glm::vec2 xy);
// The incline speed (physics.comp venueFloorSlope): the floor's rise per unit of horizontal travel along the plan direction e
// at xy (e a unit vector or 0): on a gangway incline its gradient (rake along dep) projected on e, 0 on every level floor
float floorSlope(const SeatedLayout& L, glm::vec2 xy, glm::vec2 e);
// physics.comp inclineFreeSpeed: the free walking speed for the slope g along the travel direction (sim_params.hpp "Incline
// speed": V_MAX on the level, V_STAIR_UP ascending / V_STAIR_DOWN descending from INCLINE_REF_SLOPE on, smoothstep in between)
float inclineFreeSpeed(float g);
// physics.comp inclineHeadwayTime: the headway rule's time gap for the slope g (sim_params.hpp "Stair spacing": T_HEADWAY on the
// level, tUp ascending / tDown descending from INCLINE_REF_SLOPE on, the incline speed's smoothstep in between; model time)
float inclineHeadwayTime(float g, float tUp, float tDown);
// physics.comp venueStepUpScan: at most SCAN_CROSSINGS cell boundaries per path sample, each found by SCAN_BISECTIONS
constexpr int SCAN_CROSSINGS = 4, SCAN_BISECTIONS = 12;
// physics.comp venueStepUpScan, its CPU port (CpuCrowdSim's step-up limit and the navigation field's edges): the
// fraction of the horizontal move p0 -> p1 that an agent whose start-of-step floor is f0 may take (1: not blocked; a climb over a
// vertical face onto a floor above f0 is blocked at the face), n: the face's horizontal normal away from it
float stepUpScan(const SeatedLayout& L, glm::vec2 p0, glm::vec2 p1, float f0, glm::vec2& n);

// Exits and gangways. Exit ids (the navigation field's, metrics::Exit's from EXIT_DOOR0 on): 0-3 the avenues (+x, -x, +y,
// -y), then per quadrant (0 +x+y, 1 -x+y, 2 -x-y, 3 +x-y) its doorsPerQuadrant() doors: wing 0's (the y wall) doors 0 .. doors-1,
// wing 1's, then the corner door; venue S: 4 + 2 quadrant + wing. exitByLat: the exit whose opening contains xy's folded lateral
// position (the metrics' rule for the last active position), -1: none
int exitByLat(const SeatedLayout& L, glm::vec2 xy);
int exitCount(const SeatedLayout& L);              // 4 + 4 doorsPerQuadrant
std::string exitName(const SeatedLayout& L, int e);
double exitWidthM(const SeatedLayout& L, int e);   // clear width, metres (an avenue: 2 avenueHalf; a door: its lat extent; the corner door: cornerDoorWidthM)
// Gangway ids (per-gangway utilisation): per quadrant gangwaysPerQuadrant(): wing 0's straight gangways, wing 1's, the corner gangway.
// The gangway an agent at xy stands on (an incline cell, or a barrier gap at a gangway's foot; a straight gangway merged with the corner
// gangway counts as the corner gangway), -1: none
int gangwayAt(const SeatedLayout& L, glm::vec2 xy);
int gangwayCount(const SeatedLayout& L);           // 4 gangwaysPerQuadrant
std::string gangwayName(const SeatedLayout& L, int g);

// Exact signed distance (physics.comp map() for a seated venue) and its gradient: vec4(gradient, value)
float sdf(const SeatedLayout& L, glm::vec3 p);
glm::vec4 sdfGrad(const SeatedLayout& L, glm::vec3 p);
// The nearest wall in the horizontal plane z = c.z (physics.comp clearWalls / wallPlaneProbe on VENUE_ANALYTIC; the GLSL
// venueWall): walls are the vertical faces of the cells whose top lies above the plane (inclines are walkable slopes).
// vec3(unit direction away from the wall, clearance); clearance < 0: c is inside a wall; WALL_NONE: none within reach.
constexpr float WALL_NONE = 1e9f;
glm::vec3 wall(const SeatedLayout& L, glm::vec3 c, float reach);
// Diagnostics of one evaluation: bands and cells visited
struct EvalStats { int bands = 0, cells = 0; };
glm::vec4 sdfGradStats(const SeatedLayout& L, glm::vec3 p, EvalStats& stats);

// --- Brute-force reference: the explicit list of solid primitives in the plane frame, unfolded ---
// A primitive is a box [lo, hi] (z from -inf) or an incline prism over a rectangle whose top rises along one plan axis.
struct Primitive {
    glm::dvec2 lo, hi;     // plan rectangle
    double top0;           // top height (box), or at the low end of the rise axis (incline)
    double slope;          // 0: box; else the top rises by slope per unit along axis 'axis' (towards +|coordinate|)
    int axis;              // 0: x, 1: y
    double axisLo;         // the coordinate where the incline top is top0
    int kind;              // CellKind
};
std::vector<Primitive> primitives(const SeatedLayout& L);
// Exact distance from p (outside every primitive) to the union: min over all primitives; double precision
double bruteForceDistance(const std::vector<Primitive>& prims, glm::dvec3 p);
// Whether p lies in the solid of the primitive list (z below some primitive's top inside its rectangle, or z <= 0)
bool bruteForceInside(const std::vector<Primitive>& prims, glm::dvec3 p);
// The wall query by brute force (the check of seated::wall): in the plane z = p.z, the 2D distance to the nearest footprint
// of a box primitive taller than the plane (inclines are not walls); inside: whether p's xy lies in such a footprint
double bruteForceWall(const std::vector<Primitive>& prims, glm::dvec3 p, bool& inside);

// --- Seats ---
struct Seat {
    glm::vec3 pos;      // the agent's spawn: clearway centre, rest height (tread + BODY_RADIUS)
    int quadrant;       // 0 (+x +y), 1 (-x +y), 2 (-x -y), 3 (+x -y)
    int wing;           // 0: rows along x (depth |y|), 1: rows along y (depth |x|)
    int row;            // 0 = front row
    int segment;        // 0: dead-end segment (side wall - straight gangway 0), i: after straight gangway i - 1 (S: 1, to the corner)
    int index;          // seat number within the segment, from its low-lat end
    float lat;          // folded lateral coordinate of the seat centre
};
// Every seat of the venue, in the order quadrant, wing, row, segment, index
std::vector<Seat> seats(const SeatedLayout& L);
// Seats per row in one wing (the same in all 8 wings), per segment. A row has the dead-end segment and one segment after
// each straight gangway (the last up to the corner gangway, absent while it merges with it); between: the largest of those
struct RowSeats { int deadEnd, between, total, segments; };
std::vector<RowSeats> seatsPerRow(const SeatedLayout& L);
int segmentCount(const SeatedLayout& L, int row);           // seat segments of a row
int seatCountIn(float a, float b, float seatWidth);         // seats of pitch seatWidth fitting in [a, b] (the layout's count rule)

// --- Areas (m^2), exact from the layout ---
// Occupiable floor (the agents' reachable floor up to the outer wall's outer face, where they have left): the walkway
// (from the fence's outer face), avenues (to the outer face), clearways, gangways (with the barrier's gaps at their feet),
// the concourse and its exits through the outer wall. Not occupiable: seat blocks, barrier, walls, the fenced pitch, and
// the exterior landings beyond the exit test.
struct Areas {
    double walkway, avenues, clearways, gangways, concourse, exits;
    double landings, seatBlocks, barrier, walls, pitch;
    double occupiable() const { return walkway + avenues + clearways + gangways + concourse + exits; }
};
Areas areas(const SeatedLayout& L);

// --- Render mesh: triangles (position + outward normal, 6 floats per vertex, counter-clockwise from outside) ---
std::vector<float> mesh(const SeatedLayout& L);
std::string meshOBJ(const SeatedLayout& L, const char* comment);   // the same triangles as an OBJ file (venue_s.obj)

} // namespace seated
} // namespace swarm
