#pragma once

// Navigation field: the shortest walking distance from every point of an analytic
// venue to its nearest exit, and the desired direction e_goal derived from it, for the agents of a seated venue (the terrace
// keeps its hand router, physics.comp egressTarget).
//
// TRAVERSABILITY GRID (single-tier venues: one floor per xy). A square grid of CELL_M (0.05 m) cells over the venue's domain.
// Per cell, at its centre: the floor height (the heightfield's top, the physics' floor), and its class: FIT if a standing body
// fits there by the physics' own contact rules (the centre at floor + BODY_RADIUS clears every wall by BODY_RADIUS, a wall being
// a face that reaches the body's top: seated::wall; and it lies outside the fence's collision band), NOFIT if not
// (a centre can still lie in such a cell: the cell's centre is up to 3.5 cm from the agent's). Directed edges to the 8
// neighbours: legal if the move between the two centres is one the physics allows: the step-up limit's own scan of the path
// (S: seated::stepUpScan, physics.comp venueStepUpScan: no climb over any vertical face onto a floor above the start floor, the
// incline walkable), no climb above MAX_STEP_UP, no fence crossing, a drop of at most MAX_STEP_UP (deeper is a fall, not a
// step), and a diagonal never cuts the corner of a cell a body does not fit. Down is not always up: a clearway steps down onto
// the incline beside it, never up from it. No edge leads into a seat row's clearway from outside that row
// (rows are exits only: SeatedGeometry::moveVerdict 5).
//
// DISTANCE FIELD. The exits are the cells of the venue's exit regions (S: the four avenue ends and the eight concourse door
// landings beyond the outer wall's outer face, where the physics' exit test parks an agent). From them a Lazy Theta* search
// (Nash, Koenig & Tovey 2010, "Lazy Theta*: any-angle path planning and path length analysis in 3D", AAAI; citation not yet checked against the original), an
// any-angle Dijkstra, runs over the REVERSED edges: every cell gets the length of a shortest polyline of cell centres to an exit
// whose straight segments are legal on the grid (lineLegal: every cell transition along the segment a legal edge), and that
// polyline's first vertex, its ANCHOR. Plain 8-neighbour Dijkstra measures octile lengths (up to 8% long); the any-angle search
// measures straight segments, within a cell of the Euclidean geodesic (results/validation/navigation/S/validation.md). Lengths are
// horizontal (the physics bounds the horizontal speed). FIT cells route over FIT cells only; NOFIT cells may route over NOFIT
// cells into FIT cells, never back. Cells without a legal path (the fenced pitch, the tops of seat blocks, barrier and walls)
// are unreachable (dist = infinity, no anchor).
//
// DESIRED DIRECTION. Within the cell that contains the agent's position x the field is D(x) = D(anchor) + |x - anchor| (exact
// at the cell's centre), so e_goal = -grad D(x) = (anchor - x) / |anchor - x|: the unit vector from the agent to its cell's
// anchor (0 within GOAL_DEADZONE of it, or in an unreachable cell). No interpolation between cells: the segment from a cell's
// centre to its anchor is legal by construction, so the direction never points into a wall or up a step it may not climb
// (from x, up to 3.5 cm off the centre, the segment can graze an inflated corner by that much; the contacts slide it). The
// GPU (physics.comp navDirection, @nav block) and the CPU (direction() below) evaluate it with the same float operations.
//
// GPU: an SSBO of GpuNavCell (binding BIND_NAV = 12, the predict pass), the grid as preamble #defines (VENUE_NAV_FIELD,
// NAV_RES, NAV_ORIGIN, NAV_INV_CELL). The field is computed on the CPU when a venue is first used and cached in a file keyed by
// the hash of everything it depends on (cacheKey: the venue's parameters and layout, the contact constants, VERSION).

#include <swarm/gpu_types.hpp>
#include <swarm/sim_params.hpp>

#include <glm/glm.hpp>

#include <cmath>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace swarm {

struct Venue;
struct SeatedLayout;

namespace nav {

constexpr double CELL_M = 0.05;      // cell edge, metres (the clearway's standing strip is 0.10 m deep: 2 cell centres)
constexpr uint32_t VERSION = 2;      // the field's algorithm version (part of the cache key)
constexpr uint8_t NO_EXIT = 0xFF;

// The 8 neighbour directions, counter-clockwise from +x; bit k of a cell's edge mask: the edge towards DIR k
constexpr int DIR_COUNT = 8;
constexpr int DIR_X[DIR_COUNT] = { 1, 1, 0, -1, -1, -1, 0, 1 };
constexpr int DIR_Y[DIR_COUNT] = { 0, 1, 1, 1, 0, -1, -1, -1 };
constexpr int opposite(int k) { return (k + 4) & 7; }
int dirIndex(int dx, int dy);   // -1 for (0, 0) or a non-neighbour

// A square grid; model units (the test geometries use their own units)
struct Grid {
    int res = 0;            // cells per axis
    float origin = 0.0f;    // lower-left corner (x and y)
    float cell = 0.0f;      // edge
    float invCell = 0.0f;   // 1 / cell, rounded once
    size_t cells() const { return size_t(res) * size_t(res); }
    int index(int ix, int iy) const { return ix + iy * res; }
    glm::vec2 centre(int ix, int iy) const;   // origin + (i + 0.5) cell, in double, rounded once
    glm::vec2 centre(int i) const { return centre(i % res, i / res); }
    glm::ivec2 cellOf(glm::vec2 p) const;     // the cell containing p, clamped
};
Grid venueGrid(const Venue& v);   // CELL_M cells over the venue's domain (venue S: 1250 x 1250 of 0.0016 model units)

enum Class : uint8_t { FIT = 0, NOFIT = 1 };

// What the builder asks of a venue. Units: the grid's.
class Geometry {
public:
    virtual ~Geometry() = default;
    virtual float floor(glm::vec2 xy) const = 0;                    // the floor height under xy
    virtual bool fits(glm::vec2 xy, float floorZ) const = 0;        // a standing body fits with its centre over xy
    // The move between two cell centres (from 'from' on floor fromZ to 'to' on floor toZ) is one the physics allows
    virtual bool moveLegal(glm::vec2 from, float fromZ, glm::vec2 to, float toZ) const = 0;
    virtual int exitAt(glm::vec2 xy) const = 0;                     // the exit region containing xy, -1: none
    virtual int exitCount() const = 0;
    virtual std::string exitName(int e) const = 0;
    // The exit choice's capacity term: an exit's clear width in metres, and metres per grid unit
    virtual double exitWidthM(int e) const = 0;
    virtual double metresPerUnit() const = 0;
    // The exit's type for the choice table's candidate diversity (swarm/exit_choice.hpp): exits of different types (a seated
    // venue: 0 avenues, 1 concourse doors) are both kept among a cell's candidates; one type (the default): no diversity rule
    virtual int exitType(int e) const { (void)e; return 0; }
};

// A seated venue (VenueKind::AnalyticSeated): the physics' own contact rules on its exact heightfield. Exits: the four avenue
// ends (folded lat < avenueHalf beyond the outer wall's outer face: 0 +x, 1 -x, 2 +y, 3 -y, metrics::Exit's order) and the eight
// concourse door landings (lat in [exitLo, exitHi] between the outer face and the landing's end: 4 + 2 quadrant + wing, the
// quadrant and wing of seated::Seat). The physics parks an agent past the outer face (its exit test), i.e. on entering one.
class SeatedGeometry : public Geometry {
public:
    explicit SeatedGeometry(const SeatedLayout& L) : L_(L) {}
    float floor(glm::vec2 xy) const override;
    bool fits(glm::vec2 xy, float floorZ) const override;
    bool moveLegal(glm::vec2 from, float fromZ, glm::vec2 to, float toZ) const override;
    int exitAt(glm::vec2 xy) const override;
    int exitCount() const override;   // seated::exitCount (venue S: 12)
    std::string exitName(int e) const override;
    double exitWidthM(int e) const override;   // an avenue: 2 avenueHalf; a door: exitHi - exitLo (metrics::computeMetricVenueSeated's)
    double metresPerUnit() const override { return units::M_PER_UNIT; }
    int exitType(int e) const override { return e < 4 ? 0 : 1; }   // 0 avenue, 1 door
    // Why a move is not legal (the order moveLegal tests): 0 legal, 1 fence crossing, 2 drop deeper than MAX_STEP_UP,
    // 3 rise above MAX_STEP_UP, 4 the step-up scan (a climb over a vertical face), 5 into a seat row's clearway from outside it
    // (rows are exits only)
    int moveVerdict(glm::vec2 from, float fromZ, glm::vec2 to, float toZ) const;
private:
    const SeatedLayout& L_;
};

// Known-answer geometries: a flat floor (z 0) with axis-aligned wall rectangles, optional raised ledges
// (one-way: stepping down off a ledge is allowed, up onto it not), exit rectangles; a body of radius 'body' fits where its
// centre is at least 'body' from every wall rectangle (0: point agents). Units: metres.
struct Rect {
    glm::vec2 lo, hi;
    bool contains(glm::vec2 p) const { return p.x >= lo.x && p.x <= hi.x && p.y >= lo.y && p.y <= hi.y; }
};
class RectGeometry : public Geometry {
public:
    RectGeometry(std::vector<Rect> walls, std::vector<Rect> exits, float body = 0.0f, std::vector<Rect> ledges = {}, float ledgeHeight = 0.3f)
        : walls_(std::move(walls)), exits_(std::move(exits)), ledges_(std::move(ledges)), body_(body), ledgeH_(ledgeHeight) {}
    float floor(glm::vec2 xy) const override;
    bool fits(glm::vec2 xy, float floorZ) const override;
    bool moveLegal(glm::vec2 from, float fromZ, glm::vec2 to, float toZ) const override;
    int exitAt(glm::vec2 xy) const override;
    int exitCount() const override { return int(exits_.size()); }
    std::string exitName(int e) const override { return "exit " + std::to_string(e); }
    // The exit rectangle's longer side unless set (setExitWidths); metres
    double exitWidthM(int e) const override;
    double metresPerUnit() const override { return 1.0; }
    void setExitWidths(std::vector<float> w) { exitWidths_ = std::move(w); }
    const std::vector<Rect>& walls() const { return walls_; }
    const std::vector<Rect>& exits() const { return exits_; }
    const std::vector<Rect>& ledges() const { return ledges_; }
private:
    std::vector<Rect> walls_, exits_, ledges_;
    float body_, ledgeH_;
    std::vector<float> exitWidths_;
};

// The traversability grid and the distance field
struct Field {
    Grid grid;
    std::vector<float> floorZ;          // per cell
    std::vector<uint8_t> cls;           // Class
    std::vector<uint8_t> out;           // legal out-edges: bit k = the edge towards DIR k
    std::vector<int8_t> exitRegion;     // the exit region the cell's centre lies in (-1: none)
    int exitCount = 0;
    std::vector<std::string> exitNames;
    // The distance field (build; empty after buildGrid alone)
    std::vector<float> dist;            // to the nearest exit, horizontal, grid units; INFINITY: no path
    std::vector<int32_t> anchor;        // the first vertex of the cell's shortest polyline (an exit cell: itself); -1: none
    std::vector<glm::vec2> anchorXY;    // its centre (grid.centre(anchor)); the cell's own centre if unreachable
    std::vector<uint8_t> exitId;        // the exit the shortest path leads to (NO_EXIT: none)
    uint64_t key = 0;                   // the cache key (0: not a venue field)
    const SeatedLayout* surface = nullptr;   // a venue's field (forVenue): directionCell's surface rule (surfaceReaches)
    // How it was obtained
    bool fromCache = false;
    double buildSeconds = 0.0;          // the grid (and, for build, the search), or loading it from the cache
    double searchSeconds = 0.0;
    long long losChecks = 0, losFallbacks = 0, losCellSteps = 0;
    bool reachable(size_t i) const { return std::isfinite(dist[i]); }
    // The local field D(x) = D(anchor) + |x - anchor| of the cell containing x (INFINITY: unreachable)
    float value(glm::vec2 x) const;
};

// The traversability grid of a geometry (deterministic: the result does not depend on the thread count)
Field buildGrid(const Geometry& g, const Grid& grid);
// The grid and its distance field (the search is sequential: deterministic)
Field build(const Geometry& g, const Grid& grid);
// The search behind build(): Lazy Theta* over the reversed edges of f's grid (cls, out, exitRegion) from the FIT cells of every
// exit region (exitFilter -1) or of region exitFilter alone (a per-exit field, swarm/exit_choice.hpp). Per cell: g
// the path length (grid units; INFINITY: no path), par the anchor (-1: none), closed (expanded); exitId (optional): the exit the
// path leads to. Line-of-sight statistics are added to the counters given.
void lazyThetaStar(const Field& f, int exitFilter, std::vector<double>& g, std::vector<int32_t>& par, std::vector<uint8_t>& closed,
                   std::vector<uint8_t>* exitId = nullptr, long long* losChecks = nullptr, long long* losFallbacks = nullptr,
                   long long* losCellSteps = nullptr);
// Whether the straight segment between the centres of cells a and b is legal on the field's grid: every cell transition along
// it (the supercover of the segment; a diagonal step where it passes exactly through a cell corner) is a legal edge, and none
// leads from a FIT cell into a NOFIT one. cellSteps: transitions examined (added).
bool lineLegal(const Field& f, int a, int b, long long* cellSteps = nullptr);
// The cell whose anchor gives the direction at x (physics.comp navDirection): the cell containing x, or if that cell is NOFIT, the
// FIT neighbour (of 8, reachable) whose centre is nearest to x (none: its own)
int directionCell(const Field& f, glm::vec2 x);

// Progress and cancellation of the slow work behind forVenue and choiceForVenue (swarm/exit_choice.hpp): the cache loads and the
// builds. The viewer sets a monitor while a worker thread loads a venue; the builders report their stage to it and, when it asks,
// stop and throw BuildCancelled (nothing is cached or saved: a build is saved only once it is complete). Process-wide; none by
// default (tests and tools): no reports, no checks. A monitor never changes a result.
class BuildMonitor {
public:
    virtual ~BuildMonitor() = default;
    // fraction in [0, 1], or < 0: no estimate. Called from the building threads (OpenMP workers included).
    virtual void progress(const std::string& stage, double fraction) = 0;
    virtual bool cancelled() const = 0;
};
void setBuildMonitor(BuildMonitor* m);   // nullptr: none
struct BuildCancelled : std::runtime_error {
    BuildCancelled() : std::runtime_error("navigation build cancelled") {}
};
void reportBuild(const std::string& stage, double fraction);   // to the monitor, if one is set
bool buildCancelRequested();                                     // the monitor asks to stop
void throwIfBuildCancelled();                                    // BuildCancelled if it does

// The venue's field: computed once per process (thread-safe), from the cache file if one matches, else built and saved.
// Throws std::invalid_argument for a venue without a field (the terrace).
const Field& forVenue(const Venue& v);
bool hasField(const Venue& v);   // seated venues
uint64_t cacheKey(const Venue& v);
// The cache directory: SWARM_NAV_CACHE if set, else <the executable's directory>/navcache
std::filesystem::path cacheDir();
std::filesystem::path cacheFile(const Venue& v);
// File I/O (the cache's format: header, arrays, FNV-1a checksum); load returns false on any mismatch (key, size, checksum)
bool save(const Field& f, const std::filesystem::path& file);
bool load(Field& f, const std::filesystem::path& file, uint64_t expectedKey);
uint64_t contentHash(const Field& f);   // FNV-1a over the arrays (cached and fresh fields are compared by it)
// A cache file read straight into its destinations, one sized read per array: the files are up to ~1 GB, reading them through
// std::istreambuf_iterator runs at ~50 MB/s, and reading them whole first holds a second copy of the table (venue L: 0.95 GB). The checksum
// (FNV-1a over everything between the 8-byte magic and the last 8 bytes) runs over the pieces as they arrive, so a destination may hold
// damaged bytes until finish() returns true: the loaders fill a local table and keep it only then.
class CacheFileReader {
public:
    bool open(const std::filesystem::path& file, const char* magic8);   // false: missing, shorter than the magic + the checksum, another magic
    size_t remaining() const { return left_; }                          // of the payload
    bool read(void* dst, size_t bytes);                                 // false: past the payload's end, or a short read
    // resizes v only if the rest of the file can hold count elements (a damaged header must not allocate gigabytes)
    template <class V> bool readVector(V& v, size_t count) {
        if (count > left_ / sizeof(typename V::value_type)) return false;
        v.resize(count);
        return read(v.data(), count * sizeof(typename V::value_type));
    }
    bool finish();   // every payload byte was read and the checksum matches

private:
    std::ifstream in_;
    size_t left_ = 0;
    uint64_t hash_ = 0xcbf29ce484222325ull;
};

// The field's direction at x: physics.comp navDirection, the same float operations
glm::vec2 direction(const Field& f, glm::vec2 x);
// e_goal of an agent centred at p in a seated venue (physics.comp navGoal; CpuCrowdSim's goalDirection): direction() with its
// component into a wall or a step face beside the agent removed (the faces of the columns reaching above the centre within
// FEELER_REACH, seated::wall at the centre's plane), renormalized
glm::vec2 goal(const Field& f, const SeatedLayout& L, glm::vec3 p);

// The GPU table (GpuNavCell per cell; GpuNavCell::info: the exit id in bits 0-7, NAV_FIT, NAV_REACHABLE) and the preamble's
// grid #defines
constexpr uint32_t NAV_FIT = 0x100u, NAV_REACHABLE = 0x200u;
std::vector<GpuNavCell> gpuCells(const Field& f);
std::string preambleDefines(const Grid& g);
// The SURFACE RULE of directionCell / choiceCell (physics.comp navCell / navChoiceCell, NAV_SURFACE_RULE): the
// centre of grid cell i (physics.comp navCellCentre), and whether an agent at x may walk straight to c (the step-up limit's scan;
// always within one heightfield cell: physics.comp navReaches)
glm::vec2 surfaceCellCentre(const Grid& gr, int i);
bool surfaceReaches(const SeatedLayout& L, glm::vec2 x, glm::vec2 c);

} // namespace nav
} // namespace swarm
