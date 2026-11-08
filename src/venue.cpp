#include <swarm/venue.hpp>

#include <swarm/assets.hpp>
#include <swarm/nav_field.hpp>
#include <swarm/sdf.hpp>
#include <swarm/shader.hpp>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <tuple>

namespace fs = std::filesystem;

namespace swarm {

namespace {

constexpr double SQRT2 = 1.4142135623730951;

// --- Venue S ---
// Real units. The walkway and avenue widths are the terrace's measured clear widths (test_gpu venue.terrace_passage_widths: walkway 2.63 m,
// median of 8 radial sections; avenue mouths 5.66 m, median of 4). Row geometry:
// tread 0.80 m, rise 0.40 m, clearway 0.50 m, seat block 0.30 m deep with its top 0.85 m above its tread.
// Gangways 1.20 m; at most 28 seats between two gangways and 14 in a row with a gangway at one end only (Guide to Safety
// at Sports Grounds, "Green Guide", seated accommodation; as reported there, not yet checked against the cited edition). Seat pitch 0.50 m (the same
// guide's recommended seat width; same caveat). Concourse 3.0 m. 17 rows: the count nearest 4000 seats that fits the domain.
// Barrier, side and outer walls 0.30 m thick (a thinner wall could be crossed in one step of the
// projection); barrier top 1.10 m above the walkway (0.85 m above row 0's tread, as a seat block); wall tops 1.10 m
// above the concourse. Concourse exits: Green Guide rate of passage for stairways, 66 persons per metre width per minute,
// and an egress time of 8 minutes (both as reported there; not yet checked against the cited edition), each quadrant's concourse able to clear all of
// its seats on its own, two exits per quadrant (one per wing, centred on the wing's straight gangway), at least 1.20 m each.
// Venues M and L (generatedVenueParams): rows for the target capacities (venue_probe capacity: the row counts whose seat
// totals lie nearest 16 000 and 64 000), the grids sized to them
constexpr int VENUE_M_ROWS = 43, VENUE_M_GRID_RES = 76, VENUE_M_METRIC_RES = 128;   // 15 832 seats
constexpr int VENUE_L_ROWS = 95, VENUE_L_GRID_RES = 128, VENUE_L_METRIC_RES = 208;  // 63 424 seats

const SeatedVenueParams VENUE_S_PARAMS = {
    "S",
    2.63,   // walkwayWidthM
    0.30,   // barrierThicknessM
    5.66,   // avenueWidthM
    0.30,   // sideWallThicknessM
    17,     // rows
    0.80,   // rowDepthM
    0.50,   // clearwayM
    0.50,   // seatWidthM
    1.20,   // gangwayWidthM
    0.20,   // seatBlockInsetM: a body radius
    28,     // maxSeatsBetweenGangways
    14,     // maxSeatsDeadEnd
    3.00,   // concourseWidthM
    0.30,   // outerWallThicknessM
    0.50,   // landingDepthM
    0.40,   // rowRiseM
    0.85,   // seatBlockTopM
    1.10,   // barrierTopM
    1.10,   // wallTopAboveConcourseM
    2,      // exitsPerQuadrant
    66.0,   // exitRatePerMMin
    8.0,    // egressTimeMin
    1.20,   // minExitWidthM
};

// The pitch fence's visual top (stadium.obj, tools/measure_fence.py; sim_params.hpp quotes the measurement): the
// render mesh carries the fence (collision is the analytic sdFence, unchanged)
constexpr float FENCE_VISUAL_TOP = 0.025802f;

Venue makeTerrace() {
    Venue v{};
    v.kind = VenueKind::BakedTerrace;
    v.name = "terrace";
    v.objAsset = "stadium.obj";
    v.domainMin = DOMAIN_MIN;
    v.domainSpan = DOMAIN_SPAN;
    v.gridRes = GRID_RES;
    v.exitDepth = EXIT_DEPTH;
    v.exitMaxZ = EXIT_MAX_Z;
    return v;
}

Venue makeSeated(const SeatedVenueParams& p, const char* objAsset) {
    Venue v{};
    v.kind = VenueKind::AnalyticSeated;
    v.name = p.name;
    v.objAsset = objAsset;
    // The neighbour grid: the terrace's domain and resolution (S fits it: its landings end inside DOMAIN_MAX); gridRes cells
    // of DOMAIN_SPAN / GRID_RES (0.05 model units) per axis, symmetric about 0
    v.gridRes = p.gridRes > 0 ? p.gridRes : GRID_RES;
    if (p.gridRes > 0) {
        v.domainSpan = float(double(p.gridRes) * (double(DOMAIN_SPAN) / double(GRID_RES)));
        v.domainMin = -0.5f * v.domainSpan;
    } else {
        v.domainMin = DOMAIN_MIN;
        v.domainSpan = DOMAIN_SPAN;
    }
    v.metricGridRes = p.metricGridRes > 0 ? p.metricGridRes : 64;
    v.params = p;
    v.layout = buildSeatedLayout(p, v.domainMax());
    // Exit test: every agent past the outer wall's outer face has left (through an avenue at ground level or a concourse
    // exit at the concourse level: no other way leads there); no height limit
    v.exitDepth = v.layout.outerFace;
    // model units (31 m): above every floor and wall top. A taller venue (wall tops above 0.5 units = 15.6 m) gets the next
    // whole unit above its wall tops plus one
    v.exitMaxZ = v.layout.wallTop < 0.5f ? 1.0f : float(std::ceil(double(v.layout.wallTop)) + 1.0);
    if (v.cellSize() != DOMAIN_SPAN / float(GRID_RES))
        throw std::logic_error("venue: the neighbour grid's cell size must stay DOMAIN_SPAN / GRID_RES (R_PERC, PERC_RING)");
    if (-v.domainMin != v.domainMax()) throw std::logic_error("venue: the out-of-domain exit test assumes a domain symmetric about 0");
    if (v.metricGridRes % 16 != 0 || 0.5 * v.metricGridRes < units::metres(double(v.domainMax())))
        throw std::logic_error("venue: the metric grid (1 m cells, a multiple of 16) must cover the domain");
    return v;
}

} // namespace

const Venue& terraceVenue() {
    static const Venue v = makeTerrace();
    return v;
}

const Venue& venueS() {
    static const Venue v = makeSeated(VENUE_S_PARAMS, "venue_s.obj");
    return v;
}

// --- Venues M and L ---
// Venue S's plan and row geometry, more rows (the counts nearest 16 000 and 64 000 seats: venue_probe capacity), the gangway rule's
// straight gangways (venue.hpp), a door at every gangway head, the doors sized by the capacity rule (buildSeatedLayout), the grids
// sized to the venue (the smallest neighbour grid, a multiple of 4 cells, holding the landings with a cell to spare; the 1 m
// metric grid, a multiple of 16, covering the domain).
SeatedVenueParams generatedVenueParams(const char* name, int rows, int gridRes, int metricGridRes) {
    SeatedVenueParams p = VENUE_S_PARAMS;
    p.name = name;
    p.rows = rows;
    p.exitsPerQuadrant = 0;   // DoorPerGangwayHead: the gangway heads set the door count
    p.exitLayout = SeatedVenueParams::ExitLayout::DoorPerGangwayHead;
    p.gridRes = gridRes;
    p.metricGridRes = metricGridRes;
    return p;
}

const Venue& venueM() {
    static const Venue v = makeSeated(generatedVenueParams("M", VENUE_M_ROWS, VENUE_M_GRID_RES, VENUE_M_METRIC_RES), nullptr);
    return v;
}

const Venue& venueL() {
    static const Venue v = makeSeated(generatedVenueParams("L", VENUE_L_ROWS, VENUE_L_GRID_RES, VENUE_L_METRIC_RES), nullptr);
    return v;
}

const std::vector<const Venue*>& seatedVenues() {
    static const std::vector<const Venue*> v = { &venueS(), &venueM(), &venueL() };
    return v;
}

const Venue& venueByName(const std::string& name) {
    if (name == "terrace") return terraceVenue();
    if (name == "S" || name == "s") return venueS();
    if (name == "M" || name == "m") return venueM();
    if (name == "L" || name == "l") return venueL();
    throw std::runtime_error("unknown venue '" + name + "' (terrace | S | M | L)");
}

SeatedLayout buildSeatedLayout(const SeatedVenueParams& p, float domainHalf) {
    auto mu = [](double m) { return m / double(WORLD_SCALE_M_PER_UNIT); };   // metres -> model units (double, rounded once below)
    auto fail = [&p](const std::string& what) { throw std::runtime_error(std::string("seated venue ") + p.name + ": " + what); };
    SeatedLayout L{};
    // dep breakpoints. Row fronts and the concourse front in float as the shader computes them (row0 + float(k) * rowDepth)
    L.standFront = float(glsl_fold::decimal(FENCE_HALF_OUTER) + mu(p.walkwayWidthM));
    L.row0 = float(double(L.standFront) + mu(p.barrierThicknessM));
    L.rowDepth = float(mu(p.rowDepthM));
    L.clearway = float(mu(p.clearwayM));
    L.rows = p.rows;
    L.concFront = L.row0 + float(L.rows) * L.rowDepth;
    L.concBack = float(double(L.concFront) + mu(p.concourseWidthM));
    L.outerFace = float(double(L.concBack) + mu(p.outerWallThicknessM));
    L.landingEnd = float(double(L.outerFace) + mu(p.landingDepthM));
    // lat breakpoints. The straight gangway follows a dead-end segment of exactly maxSeatsDeadEnd seats. The corner gangway
    // starts cornerInset before the diagonal at each row front: its narrowest clear width (between the front corners of
    // two mirrored seat blocks, sqrt(2) (cornerInset - seat block depth)) is the gangway width.
    L.avenueHalf = float(mu(0.5 * p.avenueWidthM));
    L.lat0 = float(double(L.avenueHalf) + mu(p.sideWallThicknessM));
    // The dead-end segment's seats end seatInset short of the straight gangway (its seat blocks' end): exactly maxSeatsDeadEnd
    // of them. The corner gangway: the seat blocks end cornerInset + seatInset before the diagonal at the front of the row
    // behind, so its narrowest clear width (between the front corners of two mirrored seat blocks) is the gangway width
    L.seatInset = float(mu(p.seatBlockInsetM));
    // 0.3 mm, ~80 ulps of a position near the domain's edge (1 unit), a tenth of plausibility's floor tolerance
    L.faceMargin = float(mu(0.3e-3));
    // A wall reaches the body's top, a body diameter above the floor (the centre BODY_RADIUS above it)
    L.wallAbove = BODY_RADIUS;
    // Centres keep faceMargin more than BODY_RADIUS from walls. The seat blocks and the barrier end exactly a body radius
    // short of the gangways, so a centre held at BODY_RADIUS from such an end would lie exactly on the next tread's side line, where
    // one ulp decides between the incline and the tread: moving up the gangway it would be refused as a climb for good
    L.wallClear = glsl_fold::add(BODY_RADIUS, L.faceMargin);
    const double gangwayCentre = double(L.lat0) + mu(p.maxSeatsDeadEnd * p.seatWidthM + p.seatBlockInsetM + 0.5 * p.gangwayWidthM);
    L.gangwayLo = float(gangwayCentre - mu(0.5 * p.gangwayWidthM));
    L.gangwayHi = float(gangwayCentre + mu(0.5 * p.gangwayWidthM));
    L.cornerInset = float(mu(p.rowDepthM - p.clearwayM + p.gangwayWidthM / SQRT2 - p.seatBlockInsetM));
    // Heights. firstRow = rake x clearway: the incline through every clearway's back edge meets the walkway at row 0's front.
    L.rowRise = float(mu(p.rowRiseM));
    L.rake = float(p.rowRiseM / p.rowDepthM);
    L.firstRow = float(mu(p.rowRiseM / p.rowDepthM * p.clearwayM));
    L.seatTop = float(mu(p.seatBlockTopM));
    L.barrierTop = float(mu(p.barrierTopM));
    L.concourseZ = L.rake * (L.concFront - L.row0);   // the incline's height at the concourse front, as the shader computes it
    L.wallTop = float(double(L.concourseZ) + mu(p.wallTopAboveConcourseM));
    L.seatWidth = float(mu(p.seatWidthM));
    // The distance search (seated::sdfGradStats): 4 bands on either side reach >= 2 clearways + 2 seat blocks (1.6 m)
    L.maxBandSteps = 4;

    L.domainHalf = domainHalf;

    // Straight gangways (venue.hpp): gangway i + 1 exactly maxSeatsBetweenGangways seats beyond gangway i, from the first
    // row front it lies before the corner gangway of (gwRow), up to the concourse; a gangway no seat row needs (its first row front
    // the concourse's) is not built. Gangway 0 is S's straight gangway.
    const double gangwayPitch = mu(p.maxSeatsBetweenGangways * p.seatWidthM + 2.0 * p.seatBlockInsetM + p.gangwayWidthM);
    auto frontCorner = [&L](int r) { const float d = L.row0 + float(r) * L.rowDepth; return d - L.cornerInset; };   // vsRowFront(r) - VS_CORNER_INSET
    L.gangways = 0;
    for (int i = 0; i < SEATED_MAX_GANGWAYS; ++i) {
        const double c = gangwayCentre + double(i) * gangwayPitch;
        const float lo = i == 0 ? L.gangwayLo : float(c - mu(0.5 * p.gangwayWidthM)), hi = i == 0 ? L.gangwayHi : float(c + mu(0.5 * p.gangwayWidthM));
        int r = 0;
        while (r <= L.rows && !(lo < frontCorner(r))) ++r;
        if (r >= L.rows) break;   // no seat row reaches it
        L.gwLo[size_t(i)] = lo;
        L.gwHi[size_t(i)] = hi;
        L.gwRow[size_t(i)] = r;
        ++L.gangways;
    }
    if (L.gangways == 0 || L.gwRow[0] != 0) fail("the first straight gangway must cross every row (reach the walkway)");
    if (L.gangways == SEATED_MAX_GANGWAYS) {
        const double c = gangwayCentre + double(SEATED_MAX_GANGWAYS) * gangwayPitch;
        if (float(c - mu(0.5 * p.gangwayWidthM)) < frontCorner(L.rows - 1)) fail("more straight gangways than SEATED_MAX_GANGWAYS");
    }
    // gwSeated: while gangway i is the last one of a row front, the first row front whose segment after it holds a seat (a row's
    // seats sit in front of the seat blocks of the band before it: the segment [gwHi + seatInset, front - cornerInset - seatInset])
    for (int i = 0; i < L.gangways; ++i) {
        const int rEnd = i + 1 < L.gangways ? L.gwRow[size_t(i + 1)] : L.rows + 1;
        int r = L.gwRow[size_t(i)];
        while (r < rEnd && seated::seatCountIn(L.gwHi[size_t(i)] + L.seatInset, frontCorner(r) - L.seatInset, L.seatWidth) < 1) ++r;
        L.gwSeated[size_t(i)] = r;
    }

    // Concourse exits
    long total = 0;
    for (const seated::RowSeats& r : seated::seatsPerRow(L)) total += 8L * r.total;
    L.seatTotal = int(total);
    const double avenuesM = 4.0 * p.avenueWidthM;
    // The capacity rule (the source of both figures: VENUE_S_PARAMS's comment, not yet checked against the cited edition): the
    // total exit width, concourse doors and avenues, clears every seat within the egress time at the planning rate of passage
    L.requiredExitWidthM = double(total) / (p.exitRatePerMMin * p.egressTimeMin);
    if (p.exitLayout == SeatedVenueParams::ExitLayout::DoorPerWing) {
        // Venue S: per quadrant the doors alone clear the quadrant's seats (width >= seats / (rate x time)), split over
        // the exits, rounded up to 0.1 m, at least minExitWidthM each; one per wing, centred on the straight gangway
        if (p.exitsPerQuadrant != 2) fail("one concourse exit per wing (exitsPerQuadrant = 2) is the only DoorPerWing layout implemented");
        const double perQuadrant = double(total) / 4.0;
        const double needM = perQuadrant / (p.exitRatePerMMin * p.egressTimeMin) / p.exitsPerQuadrant;
        const double exitM = std::max(p.minExitWidthM, std::ceil(needM * 10.0 - 1e-9) / 10.0);
        L.exitLo = float(gangwayCentre - mu(0.5 * exitM));
        L.exitHi = float(gangwayCentre + mu(0.5 * exitM));
        L.doors = 1;
        L.doorLo[0] = L.exitLo;
        L.doorHi[0] = L.exitHi;
        L.cornerDoorLo = 1e9f;
        L.doorWidthM = exitM;
        L.cornerDoorWidthM = 0.0;
        L.totalExitWidthM = 8.0 * exitM + avenuesM;
    } else {
        // A door at every gangway head (the straight gangways' and the corner gangway's), all of one width: the doors carry
        // the required width the avenues leave, split evenly, rounded up to 0.1 m, at least minExitWidthM (the gangway's width);
        // wider doors rather than more doors (the door count is the gangway heads')
        if (L.gangways > SEATED_MAX_DOORS) fail("more straight gangways than SEATED_MAX_DOORS doors per wing");
        const int doorCount = 4 * (2 * L.gangways + 1);
        const double needM = std::max(0.0, L.requiredExitWidthM - avenuesM) / doorCount;
        const double w = std::max(std::max(p.minExitWidthM, p.gangwayWidthM), std::ceil(needM * 10.0 - 1e-9) / 10.0);
        L.doors = L.gangways;
        for (int i = 0; i < L.doors; ++i) {
            const double c = gangwayCentre + double(i) * gangwayPitch;
            L.doorLo[size_t(i)] = float(c - mu(0.5 * w));
            L.doorHi[size_t(i)] = float(c + mu(0.5 * w));
        }
        L.exitLo = L.doorLo[0];
        L.exitHi = L.doorHi[0];
        // The corner door: through the outer wall's corner, lat from cornerDoorLo up to the diagonal on both wings; its clear width is
        // the gap between the two wall ends at the wall's inner face, sqrt(2) (concBack - cornerDoorLo)
        L.cornerDoorLo = float(double(L.concBack) - mu(w) / SQRT2);
        L.doorWidthM = w;
        L.cornerDoorWidthM = SQRT2 * units::metres(double(L.concBack) - double(L.cornerDoorLo));
        L.totalExitWidthM = 8.0 * L.doors * w + 4.0 * L.cornerDoorWidthM + avenuesM;
        if (L.doorLo[0] <= L.lat0) fail("the first door must lie beside the stand (past the side wall)");
        if (L.doorHi[size_t(L.doors - 1)] >= L.cornerDoorLo) fail("the last straight door overlaps the corner door");
    }

    // Design rules
    const double clearM = p.maxSeatsDeadEnd * p.seatWidthM;
    if (p.rows < 1 || p.rowDepthM <= p.clearwayM) fail("rows and a seat block behind the clearway are required");
    if (p.clearwayM < 2.0 * BODY_RADIUS_M || p.seatWidthM < 2.0 * BODY_RADIUS_M) fail("clearway and seat pitch must be at least a body wide");
    if (p.seatBlockTopM - p.rowRiseM <= MAX_STEP_UP_M) fail("a seat block must stand more than MAX_STEP_UP above the next row's tread (INV-row)");
    if (p.barrierTopM - p.rowRiseM / p.rowDepthM * p.clearwayM <= MAX_STEP_UP_M) fail("the front barrier must stand more than MAX_STEP_UP above row 0");
    // The walls (seat blocks, barrier, side and outer walls) reach a body diameter above every floor beside them, the
    // tread faces stay below it (steps for the step-up limit)
    if (p.seatBlockTopM - p.rowRiseM <= 2.0 * BODY_RADIUS_M || p.barrierTopM <= 2.0 * BODY_RADIUS_M + p.rowRiseM / p.rowDepthM * p.clearwayM)
        fail("seat blocks and the barrier must reach a body diameter above every floor beside them");
    // a tread face (at most rake x clearway above the incline beside the clearway) reaches a body diameter
    // above a descending agent's floor only a body radius or more beyond its corner: never a wall within reach at once
    if (p.rowRiseM / p.rowDepthM * (p.clearwayM + BODY_RADIUS_M) > 2.0 * BODY_RADIUS_M)
        fail("a tread face must not reach a body diameter within a body radius of its corner");
    if (1.0 / std::sqrt(1.0 + double(L.rake) * L.rake) <= WALL_MAX_NZ) fail("the gangway rake must be walkable (n_z > WALL_MAX_NZ)");
    if (L.gangwayHi + 2.0f * L.seatInset > L.row0 - L.cornerInset) fail("the straight gangway must cross every row (reach the walkway)");
    if (float(p.seatBlockInsetM) < BODY_RADIUS_M) fail("seat blocks must end at least a body radius short of the gangways");
    if (clearM < p.seatWidthM) fail("empty dead-end segment");
    for (const seated::RowSeats& r : seated::seatsPerRow(L)) {
        if (r.deadEnd > p.maxSeatsDeadEnd) fail("a dead-end segment exceeds maxSeatsDeadEnd");
        if (r.between > p.maxSeatsBetweenGangways) fail("a segment between gangways exceeds maxSeatsBetweenGangways");
        if (r.between < 1) fail("a row without seats between its gangways");
    }
    for (int i = 1; i < L.gangways; ++i)
        if (L.gwSeated[size_t(i - 1)] > L.gwRow[size_t(i)]) fail("a straight gangway starts before the previous one's last segment holds a seat");
    if (L.landingEnd >= domainHalf) fail("the venue does not fit the domain");
    return L;
}

int SeatedLayout::activeGangways(int r) const {
    int n = 0;
    for (int i = 0; i < gangways; ++i) n += gwRow[size_t(i)] <= r ? 1 : 0;
    return n;
}

bool SeatedLayout::mergedCorner(int r) const {
    const int n = activeGangways(r);
    return n > 0 && r < gwSeated[size_t(n - 1)];
}

std::vector<SeatedConstant> seatedConstants(const SeatedLayout& L) {
    return {
        { "VS_STAND_FRONT", L.standFront, false }, { "VS_ROW0", L.row0, false }, { "VS_ROW_DEPTH", L.rowDepth, false },
        { "VS_CLEARWAY", L.clearway, false }, { "VS_ROWS", float(L.rows), true }, { "VS_CONC_FRONT", L.concFront, false },
        { "VS_CONC_BACK", L.concBack, false }, { "VS_OUTER_FACE", L.outerFace, false }, { "VS_LANDING_END", L.landingEnd, false },
        { "VS_AVENUE_HALF", L.avenueHalf, false }, { "VS_LAT0", L.lat0, false }, { "VS_GANGWAY_LO", L.gangwayLo, false },
        { "VS_GANGWAY_HI", L.gangwayHi, false }, { "VS_EXIT_LO", L.exitLo, false }, { "VS_EXIT_HI", L.exitHi, false },
        { "VS_CORNER_INSET", L.cornerInset, false }, { "VS_SEAT_INSET", L.seatInset, false }, { "VS_FACE_MARGIN", L.faceMargin, false }, { "VS_WALL_ABOVE", L.wallAbove, false }, { "VS_WALL_CLEAR", L.wallClear, false }, { "VS_FIRST_ROW", L.firstRow, false }, { "VS_ROW_RISE", L.rowRise, false },
        { "VS_SEAT_TOP", L.seatTop, false }, { "VS_BARRIER_TOP", L.barrierTop, false }, { "VS_CONC_Z", L.concourseZ, false },
        { "VS_WALL_TOP", L.wallTop, false }, { "VS_RAKE", L.rake, false }, { "VS_MAX_BAND_STEPS", float(L.maxBandSteps), true }, { "VS_SCAN_CROSSINGS", float(seated::SCAN_CROSSINGS), true },
        { "VS_SCAN_BISECTIONS", float(seated::SCAN_BISECTIONS), true },
    };
}

std::string seatedDefines(const SeatedLayout& L) {
    std::ostringstream s;
    for (const SeatedConstant& c : seatedConstants(L)) {
        s << "#define " << c.name << " ";
        if (c.isInt) s << int(c.value);
        else s << glslFloatLiteral(c.value);
        s << "\n";
    }
    return s.str();
}

std::string seatedArrays(const SeatedLayout& L) {
    std::ostringstream s;
    // VS_GENERATED: venue_seated.glsl's general cell table (several straight gangways or doors, a corner door); 0: venue S's own code
    const bool generated = L.gangways != 1 || L.doors != 1 || L.cornerDoorLo < 1e8f;
    s << "#define VS_GENERATED " << (generated ? 1 : 0) << "\n";
    s << "#define VS_GANGWAYS " << L.gangways << "\n#define VS_DOORS " << L.doors << "\n#define VS_CORNER_DOOR_LO " << glslFloatLiteral(L.cornerDoorLo) << "\n";
    auto floats = [&s](const char* name, const char* count, const float* v, int n) {
        s << "const float " << name << "[" << count << "] = float[](";
        for (int i = 0; i < n; ++i) s << (i ? ", " : "") << glslFloatLiteral(v[i]);
        s << ");\n";
    };
    auto ints = [&s](const char* name, const char* count, const int* v, int n) {
        s << "const int " << name << "[" << count << "] = int[](";
        for (int i = 0; i < n; ++i) s << (i ? ", " : "") << v[i];
        s << ");\n";
    };
    floats("VS_GW_LO", "VS_GANGWAYS", L.gwLo.data(), L.gangways);
    floats("VS_GW_HI", "VS_GANGWAYS", L.gwHi.data(), L.gangways);
    ints("VS_GW_ROW", "VS_GANGWAYS", L.gwRow.data(), L.gangways);
    ints("VS_GW_SEATED", "VS_GANGWAYS", L.gwSeated.data(), L.gangways);
    floats("VS_DOOR_LO", "VS_DOORS", L.doorLo.data(), L.doors);
    floats("VS_DOOR_HI", "VS_DOORS", L.doorHi.data(), L.doors);
    return s.str();
}

std::string venuePreamble(const Venue& v, const fs::path& shaderDir) {
    if (!v.seated()) return {};
    std::ostringstream s;
    s << "// ---- venue " << v.name << " (swarm/venue.hpp): analytic seated venue ----\n"
      << "#define VENUE_ANALYTIC 1\n"
      << nav::preambleDefines(nav::venueGrid(v))   // e_goal from the navigation field (swarm/nav_field.hpp)
      << seatedDefines(v.layout)
      << seatedArrays(v.layout);   // the straight gangways and the doors
    // Next to the shader being compiled (tool variants copy the shader directory), else the asset directory (probes
    // compiled from a temporary file)
    fs::path code = shaderDir / "venue_seated.glsl";
    std::error_code ec;
    if (!fs::exists(code, ec)) code = resolveAsset("shaders") / "venue_seated.glsl";
    std::ifstream in(code, std::ios::binary);
    if (!in) throw ShaderError("Cannot open the venue shader code " + code.string());
    std::ostringstream body;
    body << in.rdbuf();
    s << body.str() << "\n// ---- end venue ----\n";
    return s.str();
}

namespace seated {

namespace {

constexpr float BIG = 1e9f;

float rowFront(const SeatedLayout& L, int k) { return L.row0 + float(k) * L.rowDepth; }
float rowTread(const SeatedLayout& L, int k) { return L.firstRow + float(k) * L.rowRise; }

// The cell of band j containing lat (the last cell for lat past every l1: cannot happen for lat <= dep)
int ownCell(const SeatedLayout& L, int j, float lat, float& l0, float& l1, int& kind, int& row) {
    int c = 0;
    float a, b;
    int k, r;
    for (; cell(L, j, c, a, b, k, r); ++c) {
        l0 = a; l1 = b; kind = k; row = r;
        if (lat < b) return c;
    }
    return c - 1;
}

// Nearest point (u, z) of the 2D region {u in [u0, u1]} x (below ? z <= t(u) : z >= t(u)), t(u) = s (u - uRef): the point
// itself inside, else the nearest of the top segment and the two vertical rays bounding the region
glm::vec2 nearestRegion2(float u, float z, float u0, float u1, float s, float uRef, bool below) {
    const float uc = std::clamp(u, u0, u1);
    const float tc = s * (uc - uRef);
    if (below ? z <= tc : z >= tc) return glm::vec2(uc, z);
    const float t0 = s * (u0 - uRef), t1 = s * (u1 - uRef);
    const float du = u1 - u0, dz = t1 - t0;
    const float len2 = du * du + dz * dz;
    const float t = len2 > 0.0f ? std::clamp(((u - u0) * du + (z - t0) * dz) / len2, 0.0f, 1.0f) : 0.0f;
    glm::vec2 best(u0 + t * du, t0 + t * dz);
    float bd = (u - best.x) * (u - best.x) + (z - best.y) * (z - best.y);
    const glm::vec2 r0(u0, below ? std::min(z, t0) : std::max(z, t0)), r1(u1, below ? std::min(z, t1) : std::max(z, t1));
    const float d0 = (u - r0.x) * (u - r0.x) + (z - r0.y) * (z - r0.y), d1 = (u - r1.x) * (u - r1.x) + (z - r1.y) * (z - r1.y);
    if (d0 < bd) { bd = d0; best = r0; }
    if (d1 < bd) { best = r1; }
    return best;
}

// Nearest point to pf (folded) of a cell's solid column (below its top) or air column (above it); squared distance in .w.
// Constant tops: a clamp. Incline tops: the lateral clamp times the 2D region in (dep, z). The air above the corner
// gangway's incline is clipped to the fold (lat <= dep): beyond the diagonal the true surface is the mirrored incline,
// higher, so the extended cell's air there is not air; its nearest point is then the one on the fold plane (the
// intersection of a convex set with a half-space).
glm::vec4 nearestInCell(const SeatedLayout& L, float lo, float hi, float l0, float l1, int kind, int row, glm::vec3 pf, bool airColumn) {
    const float latC = std::clamp(pf.x, l0, l1);
    glm::vec3 q;
    if (kind == INCLINE) {
        const glm::vec2 n2 = nearestRegion2(pf.y, pf.z, lo, hi, L.rake, L.row0, !airColumn);
        q = glm::vec3(latC, n2.x, n2.y);
        if (airColumn && q.x > q.y) {
            const float s0 = std::max(l0, lo), s1 = std::min(l1, hi);
            if (s0 > s1) return glm::vec4(q, BIG);
            const float r2 = 1.41421356f;
            const float m = 0.5f * (pf.x + pf.y);
            const glm::vec2 w = nearestRegion2(m * r2, pf.z, s0 * r2, s1 * r2, L.rake / r2, L.row0 * r2, false);
            const float s = w.x / r2;
            q = glm::vec3(s, s, w.y);
        }
    } else {
        const float top = cellTop(L, kind, row, 0.0f);
        q = glm::vec3(latC, std::clamp(pf.y, lo, hi), airColumn ? std::max(pf.z, top) : std::min(pf.z, top));
    }
    const glm::vec3 d = pf - q;
    return glm::vec4(q, glm::dot(d, d));
}

} // namespace

const char* cellKindName(int kind) {
    static const char* names[] = { "ground", "tread", "seat", "incline", "barrier", "wall", "concourse", "side wall" };
    return kind >= 0 && kind <= SIDE ? names[kind] : "?";
}

int bandCount(const SeatedLayout& L) { return 6 + 2 * L.rows; }

void band(const SeatedLayout& L, int j, float& lo, float& hi) {
    const int nb = bandCount(L);
    if (j <= 0) { lo = 0.0f; hi = L.standFront; return; }
    if (j == 1) { lo = L.standFront; hi = L.row0; return; }
    if (j < nb - 4) {
        const int k = (j - 2) >> 1;
        const float d = rowFront(L, k);
        if (((j - 2) & 1) == 0) { lo = d; hi = d + L.clearway; }
        else { lo = d + L.clearway; hi = rowFront(L, k + 1); }
        return;
    }
    if (j == nb - 4) { lo = L.concFront; hi = L.concBack; return; }
    if (j == nb - 3) { lo = L.concBack; hi = L.outerFace; return; }
    if (j == nb - 2) { lo = L.outerFace; hi = L.landingEnd; return; }
    lo = L.landingEnd;
    hi = BIG;
}

int bandOf(const SeatedLayout& L, float dep) {
    const int nb = bandCount(L);
    if (dep < L.standFront) return 0;
    if (dep < L.row0) return 1;
    if (dep < L.concFront) {
        int k = std::clamp(int(std::floor((dep - L.row0) / L.rowDepth)), 0, L.rows - 1);
        if (dep < rowFront(L, k)) --k;   // the division rounded across a row front
        else if (k + 1 < L.rows && dep >= rowFront(L, k + 1)) ++k;
        return 2 + 2 * k + (dep >= rowFront(L, k) + L.clearway ? 1 : 0);
    }
    if (dep < L.concBack) return nb - 4;
    if (dep < L.outerFace) return nb - 3;
    if (dep < L.landingEnd) return nb - 2;
    return nb - 1;
}

bool cell(const SeatedLayout& L, int j, int c, float& l0, float& l1, int& kind, int& row) {
    const int nb = bandCount(L);
    float lo, hi;
    band(L, j, lo, hi);
    row = -1;
    if (j == 0 || j == nb - 1) {   // walkway (and the pitch under the fence); outside
        if (c > 0) return false;
        l0 = 0.0f; l1 = hi; kind = GROUND;
        return true;
    }
    const bool cornerDoor = L.cornerDoorLo < 1e8f;
    if (j == nb - 2) {   // landings beyond the concourse exits: ground, the doors' landings (every door's, the corner door's)
        const int i = c >> 1;
        if (i < L.doors) {
            if ((c & 1) == 0) { l0 = i == 0 ? 0.0f : L.doorHi[size_t(i - 1)]; l1 = L.doorLo[size_t(i)]; kind = GROUND; }
            else { l0 = L.doorLo[size_t(i)]; l1 = L.doorHi[size_t(i)]; kind = CONC; }
            return true;
        }
        if (c == 2 * L.doors) { l0 = L.doorHi[size_t(L.doors - 1)]; l1 = cornerDoor ? L.cornerDoorLo : hi; kind = GROUND; return true; }
        if (c == 2 * L.doors + 1 && cornerDoor) { l0 = L.cornerDoorLo; l1 = hi; kind = CONC; return true; }
        return false;
    }
    if (c == 0) { l0 = 0.0f; l1 = L.avenueHalf; kind = GROUND; return true; }   // the avenue
    if (j == nb - 3) {   // outer wall (the side wall runs into it) with the concourse exits (the doors, the corner door)
        const int i = (c - 1) >> 1;
        if (i < L.doors) {
            if ((c & 1) == 1) { l0 = i == 0 ? L.avenueHalf : L.doorHi[size_t(i - 1)]; l1 = L.doorLo[size_t(i)]; kind = WALL; }
            else { l0 = L.doorLo[size_t(i)]; l1 = L.doorHi[size_t(i)]; kind = CONC; }
            return true;
        }
        if (c == 2 * L.doors + 1) { l0 = L.doorHi[size_t(L.doors - 1)]; l1 = cornerDoor ? L.cornerDoorLo : hi; kind = WALL; return true; }
        if (c == 2 * L.doors + 2 && cornerDoor) { l0 = L.cornerDoorLo; l1 = hi; kind = CONC; return true; }
        return false;
    }
    if (j == nb - 4) {   // concourse (the side wall: a full wall)
        if (c == 1) { l0 = L.avenueHalf; l1 = L.lat0; kind = WALL; return true; }
        if (c > 2) return false;
        l0 = L.lat0; l1 = hi; kind = CONC;
        return true;
    }
    // Barrier band and row bands: dead-end segment, straight gangway 0, segment, [straight gangway i, segment,] corner gangway. The
    // corner gangway starts cornerInset before the diagonal at the front of the row a band belongs to: a clearway band at its own
    // front (lo), a seat band (and the barrier) at the front of the row behind it (hi). Seat blocks and the barrier end seatInset
    // short of the gangways; the clearways reach the gangways' edges. The straight gangways of row front
    // r = (j - 1) / 2 (SeatedLayout::activeGangways); while the segment after the last one holds no seat it merges with the corner
    // gangway (one incline to the band's outer depth).
    int segKind = BARRIER, gapKind = GROUND;
    bool seatBand = true;
    float corner = hi - L.cornerInset - L.seatInset;
    if (j >= 2) {
        row = (j - 2) >> 1;
        seatBand = ((j - 2) & 1) != 0;
        segKind = seatBand ? SEAT : TREAD;
        gapKind = INCLINE;
        if (!seatBand) corner = lo - L.cornerInset;
    }
    if (c == 1) { l0 = L.avenueHalf; l1 = L.lat0; kind = SIDE; return true; }   // the side wall: a parapet at the row's seat-block top
    const int r = (j - 1) >> 1;
    const int n = L.activeGangways(r);
    const bool merged = L.mergedCorner(r);
    auto gLo = [&](int i) { return seatBand ? L.gwLo[size_t(i)] - L.seatInset : L.gwLo[size_t(i)]; };
    auto gHi = [&](int i) { return seatBand ? L.gwHi[size_t(i)] + L.seatInset : L.gwHi[size_t(i)]; };
    const int i = (c - 2) >> 1;   // c even: the segment before straight gangway i; odd: gangway i
    if (i < n) {
        if ((c & 1) == 0) { l0 = i == 0 ? L.lat0 : gHi(i - 1); l1 = gLo(i); kind = segKind; }
        else { l0 = gLo(i); l1 = merged && i == n - 1 ? hi : gHi(i); kind = gapKind; }
        return true;
    }
    if (merged) return false;
    if (c == 2 + 2 * n) { l0 = gHi(n - 1); l1 = corner; kind = segKind; return true; }
    if (c == 3 + 2 * n) { l0 = corner; l1 = hi; kind = gapKind; return true; }
    return false;
}

float cellTop(const SeatedLayout& L, int kind, int row, float dep) {
    switch (kind) {
    case TREAD: return rowTread(L, row);
    case SEAT: return rowTread(L, row) + L.seatTop;
    case INCLINE: return L.rake * (dep - L.row0);
    case BARRIER: return L.barrierTop;
    case WALL: return L.wallTop;
    case CONC: return L.concourseZ;
    case SIDE: return row < 0 ? L.barrierTop : rowTread(L, row) + L.seatTop;
    default: return 0.0f;
    }
}

glm::vec2 fold(glm::vec2 xy) {
    const glm::vec2 a = glm::abs(xy);
    return glm::vec2(std::min(a.x, a.y), std::max(a.x, a.y));
}

glm::vec2 unfoldDir(glm::vec2 xy, glm::vec2 d) {
    const glm::vec2 s(xy.x < 0.0f ? -1.0f : 1.0f, xy.y < 0.0f ? -1.0f : 1.0f);
    const glm::vec2 a = glm::abs(xy);
    return a.y >= a.x ? glm::vec2(s.x * d.x, s.y * d.y) : glm::vec2(s.x * d.y, s.y * d.x);
}

int cellAt(const SeatedLayout& L, glm::vec2 xy, int* row, int* bandIndex) {
    const glm::vec2 f = fold(xy);
    const int j = bandOf(L, f.y);
    float l0, l1;
    int kind, r;
    ownCell(L, j, f.x, l0, l1, kind, r);
    if (row) *row = r;
    if (bandIndex) *bandIndex = j;
    return kind;
}

glm::vec2 cellKey(const SeatedLayout& L, glm::vec2 xy) {
    const glm::vec2 f = fold(xy);
    const int j = bandOf(L, f.y);
    float l0, l1;
    int kind, row;
    ownCell(L, j, f.x, l0, l1, kind, row);
    return glm::vec2(float(j), l0);
}

float floorSlope(const SeatedLayout& L, glm::vec2 xy, glm::vec2 e) {   // physics.comp venueFloorSlope
    const glm::vec2 f = fold(xy);
    const int j = bandOf(L, f.y);
    float l0, l1;
    int kind, row;
    ownCell(L, j, f.x, l0, l1, kind, row);
    if (kind != INCLINE) return 0.0f;
    const glm::vec2 g = unfoldDir(xy, glm::vec2(0.0f, L.rake));   // the incline's gradient: rake along dep
    const float a = g.x * e.x, b = g.y * e.y;
    return a + b;
}

float inclineFreeSpeed(float g) {   // physics.comp inclineFreeSpeed
    const float u = std::clamp(std::abs(g) * INCLINE_INV_REF_SLOPE, 0.0f, 1.0f);
    const float uu = u * u, w = 3.0f - 2.0f * u;
    const float t = uu * w;
    const float vStair = g > 0.0f ? V_STAIR_UP : V_STAIR_DOWN;
    const float dv = vStair - V_MAX;
    const float k = dv * t;
    return V_MAX + k;
}

float inclineHeadwayTime(float g, float tUp, float tDown) {   // physics.comp inclineHeadwayTime
    const float u = std::clamp(std::abs(g) * INCLINE_INV_REF_SLOPE, 0.0f, 1.0f);
    const float uu = u * u, w = 3.0f - 2.0f * u;
    const float t = uu * w;
    const float tStair = g > 0.0f ? tUp : tDown;
    const float dt = tStair - T_HEADWAY;
    const float k = dt * t;
    return T_HEADWAY + k;
}

float floorHeight(const SeatedLayout& L, glm::vec2 xy) {
    const glm::vec2 f = fold(xy);
    const int j = bandOf(L, f.y);
    float l0, l1;
    int kind, row;
    ownCell(L, j, f.x, l0, l1, kind, row);
    return cellTop(L, kind, row, f.y);
}

// Exact signed distance to the heightfield {z <= floorHeight(xy)} (the venue without the fence). In the folded frame the
// venue is a set of columns (cells) per dep band; its distance from a point in air is the minimum over the solid columns
// (below their tops), from a point in solid the minimum over the air columns (above them), both exact: the columns of a
// band tile the fundamental domain lat <= dep (the mirror images of the folded-away copies are never nearer), and a cell
// that crosses the diagonal is extended to its band's outer depth, which stays inside the true solid (constant tops: the
// same ring band; the corner incline: the mirrored incline is higher) and, for constant tops, inside the true air; the
// corner incline's air is clipped to the fold (nearestInCell). Bands are visited outward from the point's own band until
// the band's depth gap exceeds the best distance, at most maxBandSteps on either side: exact for every point closer to
// the surface than maxBandSteps consecutive bands (>= 1.6 m), an upper bound beyond.
glm::vec4 sdfGradStats(const SeatedLayout& L, glm::vec3 p, EvalStats& st) {
    const glm::vec2 f = fold(glm::vec2(p));
    const glm::vec3 pf(f.x, f.y, p.z);
    const int nb = bandCount(L);
    const int jp = bandOf(L, pf.y);
    float l0, l1;
    int kind, row;
    ownCell(L, jp, pf.x, l0, l1, kind, row);
    const bool inAir = pf.z > cellTop(L, kind, row, pf.y);
    float best = BIG;
    glm::vec3 bestQ = pf;
    glm::vec4 bestRect(0.0f);   // the nearest cell's (l0, l1, lo, hi)
    int bestKind = kind;
    auto visit = [&](int j, float g2) {
        float lo, hi;
        band(L, j, lo, hi);
        ++st.bands;
        float a, b;
        int k, r;
        for (int c = 0; cell(L, j, c, a, b, k, r); ++c) {
            const float lg = std::max(std::max(a - pf.x, pf.x - b), 0.0f);
            if (g2 + lg * lg >= best) {
                if (a > pf.x) break;   // every later cell lies farther right (the GLSL's early exit)
                continue;
            }
            ++st.cells;
            const glm::vec4 n = nearestInCell(L, lo, hi, a, b, k, r, pf, !inAir);
            if (n.w < best) { best = n.w; bestQ = glm::vec3(n); bestRect = glm::vec4(a, b, lo, hi); bestKind = k; }
        }
    };
    visit(jp, 0.0f);
    bool down = true, up = true;
    for (int s = 1; s <= L.maxBandSteps && (down || up); ++s) {
        for (int side = 0; side < 2; ++side) {
            bool& open = side == 0 ? down : up;
            if (!open) continue;
            const int j = side == 0 ? jp - s : jp + s;
            if (j < 0 || j >= nb) { open = false; continue; }
            float lo, hi;
            band(L, j, lo, hi);
            const float g = std::max(std::max(lo - pf.y, pf.y - hi), 0.0f);
            if (g * g >= best) { open = false; continue; }
            visit(j, g * g);
        }
    }
    const float d = std::sqrt(best);
    glm::vec3 gf;
    if (d > 0.0f) {
        gf = inAir ? (pf - bestQ) / d : (bestQ - pf) / d;
    } else {
        // Exactly on the surface (root finding lands there): the normal of the face the point lies on. On a side of the
        // nearest cell's footprint it is a vertical face (towards that cell's air column from solid, away from its solid
        // column from air); inside the footprint it is that cell's top. (The top's normal for every
        // point on the surface would make the wall contact classify the vertical faces it has just found as walkable.)
        const float sgn = inAir ? -1.0f : 1.0f;
        const glm::vec2 h(pf.x <= bestRect.x ? sgn : pf.x >= bestRect.y ? -sgn : 0.0f, pf.y <= bestRect.z ? sgn : pf.y >= bestRect.w ? -sgn : 0.0f);
        gf = h != glm::vec2(0.0f) ? glm::vec3(glm::normalize(h), 0.0f)
                                  : (bestKind == INCLINE ? glm::normalize(glm::vec3(0.0f, -L.rake, 1.0f)) : glm::vec3(0.0f, 0.0f, 1.0f));
    }
    const glm::vec2 g = unfoldDir(glm::vec2(p), glm::vec2(gf));
    return glm::vec4(g, gf.z, inAir ? d : -d);
}

glm::vec3 wall(const SeatedLayout& L, glm::vec3 c, float reach) {
    const glm::vec2 f = fold(glm::vec2(c));
    const int nb = bandCount(L);
    const int jp = bandOf(L, f.y);
    float l0, l1;
    int kind, row;
    ownCell(L, jp, f.x, l0, l1, kind, row);
    const bool inWall = kind != INCLINE && cellTop(L, kind, row, f.y) > c.z;
    float best = inWall ? BIG : reach * reach;
    glm::vec2 bestQ = f;
    glm::vec4 bestRect(0.0f);
    bool found = false;
    auto visit = [&](int j) {
        float lo, hi;
        band(L, j, lo, hi);
        float a, b;
        int k, r;
        for (int cc = 0; cell(L, j, cc, a, b, k, r); ++cc) {
            const bool isWall = k != INCLINE && cellTop(L, k, r, lo) > c.z;
            if (isWall == inWall) continue;
            const glm::vec2 q = glm::clamp(f, glm::vec2(a, lo), glm::vec2(b, hi));
            const glm::vec2 dd = f - q;
            const float d2 = glm::dot(dd, dd);
            if (d2 < best) { best = d2; bestQ = q; bestRect = glm::vec4(a, b, lo, hi); found = true; }
        }
    };
    visit(jp);
    bool down = true, up = true;
    for (int s = 1; s <= L.maxBandSteps && (down || up); ++s) {
        for (int side = 0; side < 2; ++side) {
            bool& open = side == 0 ? down : up;
            if (!open) continue;
            const int j = side == 0 ? jp - s : jp + s;
            if (j < 0 || j >= nb) { open = false; continue; }
            float lo, hi;
            band(L, j, lo, hi);
            const float g = std::max(std::max(lo - f.y, f.y - hi), 0.0f);
            if (g * g >= best) { open = false; continue; }
            visit(j);
        }
    }
    if (!found) return glm::vec3(0.0f, 0.0f, WALL_NONE);
    const float d = std::sqrt(best);
    glm::vec2 dir;
    if (d > 0.0f) {
        dir = inWall ? (bestQ - f) / d : (f - bestQ) / d;
    } else {
        const float sgn = inWall ? 1.0f : -1.0f;
        dir = glm::normalize(glm::vec2(f.x <= bestRect.x ? sgn : f.x >= bestRect.y ? -sgn : 0.0f, f.y <= bestRect.z ? sgn : f.y >= bestRect.w ? -sgn : 0.0f));
    }
    return glm::vec3(unfoldDir(glm::vec2(c), dir), inWall ? -d : d);
}

// physics.comp venueStepUpScan, ported line by line (here for the navigation field's edges too)
float stepUpScan(const SeatedLayout& L, glm::vec2 p0, glm::vec2 p1, float f0, glm::vec2& n) {
    n = glm::vec2(0.0f);
    float len = glm::length(p1 - p0);
    int ns = std::clamp(int(std::ceil(len / STEP_UP_SAMPLE)), 1, STEP_UP_MAX_SAMPLES);
    float lo = 0.0f;
    glm::vec2 key = cellKey(L, p0);
    for (int i = 1; i <= ns; ++i) {
        float t = float(i) / float(ns);
        for (int k = 0; k < SCAN_CROSSINGS; ++k) {
            if (cellKey(L, glm::mix(p0, p1, t)) == key) break;
            float a = lo, b = t;
            for (int m = 0; m < SCAN_BISECTIONS; ++m) {
                float tm = 0.5f * (a + b);
                if (cellKey(L, glm::mix(p0, p1, tm)) == key) a = tm;
                else b = tm;
            }
            float ha = floorHeight(L, glm::mix(p0, p1, a)), hb = floorHeight(L, glm::mix(p0, p1, b));
            if (hb > f0 + STEP_UP_TOL && hb - ha > L.rake * len * (b - a) + STEP_UP_TOL) {
                const glm::vec3 w = wall(L, glm::vec3(glm::mix(p0, p1, a), ha + STEP_UP_TOL), STEP_UP_SAMPLE);
                n = w.z < WALL_NONE ? glm::vec2(w) : (p0 - p1) / std::max(len, 1e-30f);
                return a;
            }
            lo = b;
            key = cellKey(L, glm::mix(p0, p1, b));
        }
        lo = t;
    }
    return 1.0f;
}

namespace {
int quadrantOf(glm::vec2 xy) { return xy.x >= 0.0f ? (xy.y >= 0.0f ? 0 : 3) : (xy.y >= 0.0f ? 1 : 2); }
const char* QUADRANT_NAMES[4] = { "+x+y", "-x+y", "-x-y", "+x-y" };
} // namespace

int exitByLat(const SeatedLayout& L, glm::vec2 xy) {   // metrics_deposit.comp exitSlot (VENUE_ANALYTIC)
    const glm::vec2 a = glm::abs(xy);
    const bool alongY = a.y >= a.x;
    const float lat = alongY ? a.x : a.y;
    if (lat < L.avenueHalf) return alongY ? (xy.y > 0.0f ? 2 : 3) : (xy.x > 0.0f ? 0 : 1);
    const int base = 4 + quadrantOf(xy) * L.doorsPerQuadrant();
    for (int i = 0; i < L.doors; ++i)
        if (lat >= L.doorLo[size_t(i)] && lat <= L.doorHi[size_t(i)]) return base + (alongY ? 0 : L.doors) + i;
    if (L.cornerDoorLo < 1e8f && lat >= L.cornerDoorLo) return base + 2 * L.doors;
    return -1;
}

int exitCount(const SeatedLayout& L) { return 4 + 4 * L.doorsPerQuadrant(); }

std::string exitName(const SeatedLayout& L, int e) {
    static const char* avenues[4] = { "avenue +x", "avenue -x", "avenue +y", "avenue -y" };
    if (e >= 0 && e < 4) return avenues[e];
    if (e < 4 || e >= exitCount(L)) return "?";
    const int q = (e - 4) / L.doorsPerQuadrant(), d = (e - 4) % L.doorsPerQuadrant();
    if (d == 2 * L.doors) return std::string("door ") + QUADRANT_NAMES[q] + " (corner)";
    const int wing = d / L.doors, i = d % L.doors;
    // venue S (one door per wing): its names
    return std::string("door ") + QUADRANT_NAMES[q] + (wing == 0 ? " (y wall)" : " (x wall)") + (L.doors > 1 ? " " + std::to_string(i) : std::string());
}

double exitWidthM(const SeatedLayout& L, int e) {
    if (e >= 0 && e < 4) return units::metres(2.0 * double(L.avenueHalf));
    if (e < 4 || e >= exitCount(L)) return 0.0;
    const int d = (e - 4) % L.doorsPerQuadrant();
    if (d == 2 * L.doors) return L.cornerDoorWidthM;
    const int i = d % L.doors;
    return units::metres(double(L.doorHi[size_t(i)]) - double(L.doorLo[size_t(i)]));
}

int gangwayAt(const SeatedLayout& L, glm::vec2 xy) {   // metrics_deposit.comp gangwayAt (VENUE_ANALYTIC)
    const glm::vec2 f = fold(xy);
    const int j = bandOf(L, f.y);
    if (j < 1 || j >= bandCount(L) - 4) return -1;   // the barrier band and the row bands
    float l0, l1;
    int kind, row;
    const int c = ownCell(L, j, f.x, l0, l1, kind, row);
    if (!(kind == INCLINE || (j == 1 && kind == GROUND && c >= 2))) return -1;
    const int r = (j - 1) >> 1;
    const int n = L.activeGangways(r);
    const bool merged = L.mergedCorner(r);
    const int i = (c - 3) >> 1;   // odd c = 3 + 2i: straight gangway i
    const bool straight = (c & 1) == 1 && i < n && !(merged && i == n - 1);
    const glm::vec2 a = glm::abs(xy);
    const int base = quadrantOf(xy) * L.gangwaysPerQuadrant();
    return straight ? base + (a.y >= a.x ? 0 : L.gangways) + i : base + 2 * L.gangways;
}

int gangwayCount(const SeatedLayout& L) { return 4 * L.gangwaysPerQuadrant(); }

std::string gangwayName(const SeatedLayout& L, int g) {
    if (g < 0 || g >= gangwayCount(L)) return "?";
    const int q = g / L.gangwaysPerQuadrant(), d = g % L.gangwaysPerQuadrant();
    if (d == 2 * L.gangways) return std::string("corner ") + QUADRANT_NAMES[q];
    return std::string("straight ") + QUADRANT_NAMES[q] + (d < L.gangways ? " (y wing) " : " (x wing) ") + std::to_string(d % L.gangways);
}

glm::vec4 sdfGrad(const SeatedLayout& L, glm::vec3 p) {
    EvalStats st;
    return sdfGradStats(L, p, st);
}

float sdf(const SeatedLayout& L, glm::vec3 p) { return sdfGrad(L, p).w; }

// --- Brute force ---
namespace {

glm::dvec2 nearestRegion2d(double u, double z, double u0, double u1, double s, double uRef) {   // below the line
    const double uc = std::clamp(u, u0, u1);
    const double tc = s * (uc - uRef);
    if (z <= tc) return glm::dvec2(uc, z);
    const double t0 = s * (u0 - uRef), t1 = s * (u1 - uRef);
    const double du = u1 - u0, dz = t1 - t0, len2 = du * du + dz * dz;
    const double t = len2 > 0.0 ? std::clamp(((u - u0) * du + (z - t0) * dz) / len2, 0.0, 1.0) : 0.0;
    glm::dvec2 best(u0 + t * du, t0 + t * dz);
    double bd = (u - best.x) * (u - best.x) + (z - best.y) * (z - best.y);
    for (const glm::dvec2 r : { glm::dvec2(u0, std::min(z, t0)), glm::dvec2(u1, std::min(z, t1)) }) {
        const double d = (u - r.x) * (u - r.x) + (z - r.y) * (z - r.y);
        if (d < bd) { bd = d; best = r; }
    }
    return best;
}

double primitiveTop(const Primitive& pr, glm::dvec3 p) {
    if (pr.slope == 0.0) return pr.top0;
    const double u = std::abs(pr.axis == 0 ? p.x : p.y);
    return pr.top0 + pr.slope * (u - pr.axisLo);
}

} // namespace

std::vector<Primitive> primitives(const SeatedLayout& L) {
    std::vector<Primitive> out;
    const int nb = bandCount(L);
    for (int q = 0; q < 4; ++q) {
        const double sx = (q == 1 || q == 2) ? -1.0 : 1.0, sy = (q >= 2) ? -1.0 : 1.0;
        for (int wing = 0; wing < 2; ++wing)
            for (int j = 0; j < nb; ++j) {
                float lo, hi;
                band(L, j, lo, hi);
                float l0, l1;
                int kind, row;
                for (int c = 0; cell(L, j, c, l0, l1, kind, row); ++c) {
                    if (kind == GROUND) continue;   // the ground half-space z <= 0
                    // folded (lat, dep) rectangle -> plane rectangle; wing 0: lat = |x|, dep = |y|; wing 1: lat = |y|, dep = |x|
                    const glm::dvec2 a = wing == 0 ? glm::dvec2(sx * l0, sy * lo) : glm::dvec2(sx * lo, sy * l0);
                    const glm::dvec2 b = wing == 0 ? glm::dvec2(sx * l1, sy * hi) : glm::dvec2(sx * hi, sy * l1);
                    Primitive pr{};
                    pr.lo = glm::min(a, b);
                    pr.hi = glm::max(a, b);
                    pr.kind = kind;
                    if (kind == INCLINE) {
                        pr.axis = wing == 0 ? 1 : 0;   // rises along the depth axis
                        pr.axisLo = double(L.row0);
                        pr.top0 = 0.0;
                        pr.slope = double(L.rake);
                    } else {
                        pr.top0 = double(cellTop(L, kind, row, 0.0f));
                    }
                    out.push_back(pr);
                }
            }
    }
    return out;
}

double bruteForceDistance(const std::vector<Primitive>& prims, glm::dvec3 p) {
    double best = std::max(p.z, 0.0);   // the ground half-space z <= 0
    double best2 = best * best;
    for (const Primitive& pr : prims) {
        if (pr.slope == 0.0) {
            const glm::dvec3 q(std::clamp(p.x, pr.lo.x, pr.hi.x), std::clamp(p.y, pr.lo.y, pr.hi.y), std::min(p.z, pr.top0));
            const glm::dvec3 d = p - q;
            best2 = std::min(best2, glm::dot(d, d));
        } else {
            const int la = 1 - pr.axis;
            const double lat = la == 0 ? p.x : p.y;
            const double dl = lat - std::clamp(lat, la == 0 ? pr.lo.x : pr.lo.y, la == 0 ? pr.hi.x : pr.hi.y);
            const double v = pr.axis == 0 ? p.x : p.y;
            const double sgn = (pr.axis == 0 ? pr.lo.x + pr.hi.x : pr.lo.y + pr.hi.y) < 0.0 ? -1.0 : 1.0;   // the quadrant's side
            const double u = sgn * v;
            const double u0 = std::min(sgn * (pr.axis == 0 ? pr.lo.x : pr.lo.y), sgn * (pr.axis == 0 ? pr.hi.x : pr.hi.y));
            const double u1 = std::max(sgn * (pr.axis == 0 ? pr.lo.x : pr.lo.y), sgn * (pr.axis == 0 ? pr.hi.x : pr.hi.y));
            const glm::dvec2 n = nearestRegion2d(u, p.z, u0, u1, pr.slope, pr.axisLo);
            const double d2 = dl * dl + (u - n.x) * (u - n.x) + (p.z - n.y) * (p.z - n.y);
            best2 = std::min(best2, d2);
        }
    }
    return std::sqrt(best2);
}

bool bruteForceInside(const std::vector<Primitive>& prims, glm::dvec3 p) {
    if (p.z <= 0.0) return true;
    for (const Primitive& pr : prims)
        if (p.x >= pr.lo.x && p.x <= pr.hi.x && p.y >= pr.lo.y && p.y <= pr.hi.y && p.z <= primitiveTop(pr, p)) return true;
    return false;
}

double bruteForceWall(const std::vector<Primitive>& prims, glm::dvec3 p, bool& inside) {
    inside = false;
    double best2 = 1e300;
    for (const Primitive& pr : prims) {
        if (pr.slope != 0.0 || pr.top0 <= p.z) continue;
        const glm::dvec2 q(std::clamp(p.x, pr.lo.x, pr.hi.x), std::clamp(p.y, pr.lo.y, pr.hi.y));
        const glm::dvec2 d = glm::dvec2(p) - q;
        const double d2 = glm::dot(d, d);
        if (d2 == 0.0 && p.x > pr.lo.x && p.x < pr.hi.x && p.y > pr.lo.y && p.y < pr.hi.y) inside = true;
        best2 = std::min(best2, d2);
    }
    return std::sqrt(best2);
}

// --- Seats ---
int seatCountIn(float a, float b, float w) { return b > a ? int(std::floor(double(b - a) / double(w) + 1e-4)) : 0; }
namespace {
int seatCount(float a, float b, float w) { return seatCountIn(a, b, w); }
} // namespace

// A row's seat segments: in front of the seat blocks (or the barrier) of the band before it (row front r = k), which end seatInset
// short of the gangways: [lat0, gangwayLo - seatInset], then after straight gangway i - 1 up to gangway i
// [gwHi_(i-1) + seatInset, gwLo_i - seatInset], the last up to the corner gangway [gwHi + seatInset, front - cornerInset - seatInset]
// (absent while the last straight gangway merges with the corner gangway; venue S: segments 0 and 1)
int segmentCount(const SeatedLayout& L, int k) { return L.activeGangways(k) + (L.mergedCorner(k) ? 0 : 1); }

static void segmentBounds(const SeatedLayout& L, int k, int seg, float& a, float& b) {
    const int n = L.activeGangways(k);
    if (seg == 0) { a = L.lat0; b = L.gangwayLo - L.seatInset; }
    else if (seg < n) { a = L.gwHi[size_t(seg - 1)] + L.seatInset; b = L.gwLo[size_t(seg)] - L.seatInset; }
    else { a = L.gwHi[size_t(n - 1)] + L.seatInset; b = rowFront(L, k) - L.cornerInset - L.seatInset; }
}

std::vector<RowSeats> seatsPerRow(const SeatedLayout& L) {
    std::vector<RowSeats> r;
    for (int k = 0; k < L.rows; ++k) {
        RowSeats rs{ 0, 0, 0, segmentCount(L, k) };
        for (int seg = 0; seg < rs.segments; ++seg) {
            float a, b;
            segmentBounds(L, k, seg, a, b);
            const int n = seatCount(a, b, L.seatWidth);
            if (seg == 0) rs.deadEnd = n;
            else rs.between = std::max(rs.between, n);
            rs.total += n;
        }
        r.push_back(rs);
    }
    return r;
}

std::vector<Seat> seats(const SeatedLayout& L) {
    std::vector<Seat> out;
    for (int q = 0; q < 4; ++q) {
        const float sx = (q == 1 || q == 2) ? -1.0f : 1.0f, sy = (q >= 2) ? -1.0f : 1.0f;
        for (int wing = 0; wing < 2; ++wing)
            for (int k = 0; k < L.rows; ++k)
                for (int seg = 0; seg < segmentCount(L, k); ++seg) {
                    float a, b;
                    segmentBounds(L, k, seg, a, b);
                    const int n = seatCount(a, b, L.seatWidth);
                    const double off = 0.5 * (double(b - a) - n * double(L.seatWidth));   // the seats centred in the segment
                    const float dep = rowFront(L, k) + 0.5f * L.clearway;
                    const float z = rowTread(L, k) + BODY_RADIUS;
                    for (int i = 0; i < n; ++i) {
                        const float lat = float(double(a) + off + (i + 0.5) * double(L.seatWidth));
                        Seat s;
                        s.pos = wing == 0 ? glm::vec3(sx * lat, sy * dep, z) : glm::vec3(sx * dep, sy * lat, z);
                        s.quadrant = q;
                        s.wing = wing;
                        s.row = k;
                        s.segment = seg;
                        s.index = i;
                        s.lat = lat;
                        out.push_back(s);
                    }
                }
    }
    return out;
}

// --- Areas ---
namespace {
// Area of [a, b] x [c, d] (lat x dep) within the fold lat <= dep, double
double foldedArea(double a, double b, double c, double d) {
    if (b <= a || d <= c) return 0.0;
    double area = 0.0;
    const double y0 = std::max(c, a), y1 = std::min(d, b);   // there the lat extent is y - a
    if (y1 > y0) area += 0.5 * ((y1 - a) * (y1 - a) - (y0 - a) * (y0 - a));
    const double y2 = std::max(c, b);                        // above b the full width b - a
    if (d > y2) area += (d - y2) * (b - a);
    return area;
}
} // namespace

Areas areas(const SeatedLayout& L) {
    Areas A{};
    const double m2 = 8.0 * units::M_PER_UNIT * units::M_PER_UNIT;   // 8 folded copies, model units^2 -> m^2
    const int nb = bandCount(L);
    for (int j = 0; j < nb - 2; ++j) {   // up to the outer wall's outer face (beyond it agents have left)
        float lo, hi;
        band(L, j, lo, hi);
        float l0, l1;
        int kind, row;
        for (int c = 0; cell(L, j, c, l0, l1, kind, row); ++c) {
            if (j == 0) {   // walkway: from the fence's outer face; inside it the fence band and the pitch
                A.walkway += m2 * foldedArea(l0, l1, glsl_fold::decimal(FENCE_HALF_OUTER), hi);
                A.pitch += m2 * foldedArea(l0, l1, 0.0, glsl_fold::decimal(FENCE_HALF_INNER));
                continue;
            }
            const double a = m2 * foldedArea(l0, l1, lo, hi);
            switch (kind) {
            case GROUND: (c == 0 ? A.avenues : A.gangways) += a; break;   // avenues; the barrier's gaps at the gangway feet
            case TREAD: A.clearways += a; break;
            case INCLINE: A.gangways += a; break;
            case SEAT: A.seatBlocks += a; break;
            case BARRIER: A.barrier += a; break;
            case WALL: case SIDE: A.walls += a; break;
            case CONC: (j == nb - 4 ? A.concourse : A.exits) += a; break;
            default: break;
            }
        }
    }
    // Landings beyond the concourse exits: reported, not occupiable (an agent past the outer face has left)
    float lo, hi;
    band(L, nb - 2, lo, hi);
    for (int i = 0; i < L.doors; ++i) A.landings += m2 * foldedArea(L.doorLo[size_t(i)], L.doorHi[size_t(i)], lo, hi);
    if (L.cornerDoorLo < 1e8f) A.landings += m2 * foldedArea(L.cornerDoorLo, hi, lo, hi);
    return A;
}

// --- Render mesh ---
namespace {

struct Tri { glm::vec3 v[3]; glm::vec3 n; };

// Fan triangulation of a convex polygon, each triangle wound counter-clockwise around n (seen from the side n points to)
void addPoly(std::vector<Tri>& out, const std::vector<glm::vec3>& poly, glm::vec3 n) {
    for (size_t i = 1; i + 1 < poly.size(); ++i) {
        Tri t{ { poly[0], poly[i], poly[i + 1] }, n };
        const glm::vec3 c = glm::cross(t.v[1] - t.v[0], t.v[2] - t.v[0]);
        const float area = glm::length(c);
        if (area < 2e-9f) continue;   // degenerate: a face tapering to an edge, or a float-step sliver (< ~1 mm^2; real faces >= 3e-4)
        if (glm::dot(c, n) < 0.0f) std::swap(t.v[1], t.v[2]);
        out.push_back(t);
    }
}

// Clips the lat x dep rectangle to the fold lat <= dep (and lat >= 0): convex polygon (lat, dep)
std::vector<glm::vec2> clipRect(float a, float b, float c, float d) {
    std::vector<glm::vec2> in = { { a, c }, { b, c }, { b, d }, { a, d } }, out;
    for (size_t i = 0; i < in.size(); ++i) {   // Sutherland-Hodgman against lat - dep <= 0
        const glm::vec2 p = in[i], q = in[(i + 1) % in.size()];
        const float fp = p.x - p.y, fq = q.x - q.y;
        if (fp <= 0.0f) out.push_back(p);
        if ((fp < 0.0f && fq > 0.0f) || (fp > 0.0f && fq < 0.0f)) {
            const float t = fp / (fp - fq);
            out.push_back(p + t * (q - p));
        }
    }
    return out;
}

} // namespace

std::vector<float> mesh(const SeatedLayout& L) {
    std::vector<Tri> folded;   // in (lat, dep, z), the fundamental domain lat <= dep
    const int nb = bandCount(L);
    const float edge = L.domainHalf;   // the ground ends at the domain edge
    const glm::vec3 up(0.0f, 0.0f, 1.0f), inclineN = glm::normalize(glm::vec3(0.0f, -L.rake, 1.0f));
    auto topAt = [&](int kind, int row, float dep) { return cellTop(L, kind, row, dep); };
    for (int j = 0; j < nb; ++j) {
        float lo, hi;
        band(L, j, lo, hi);
        hi = std::min(hi, edge);
        if (lo >= hi) continue;
        std::vector<std::tuple<float, float, int, int>> cells;
        float l0, l1;
        int kind, row;
        for (int c = 0; cell(L, j, c, l0, l1, kind, row); ++c) cells.emplace_back(l0, std::min(l1, hi), kind, row);
        // tops
        for (const auto& [a, b, k, r] : cells) {
            std::vector<glm::vec3> poly;
            for (const glm::vec2 v : clipRect(a, b, lo, hi)) poly.emplace_back(v.x, v.y, topAt(k, r, v.y));
            if (poly.size() >= 3) addPoly(folded, poly, k == INCLINE ? inclineN : up);
        }
        // lateral faces between neighbouring cells of the band (at lat = x, over dep >= x)
        for (size_t c = 0; c + 1 < cells.size(); ++c) {
            const auto& [a0, b0, k0, r0] = cells[c];
            const auto& [a1, b1, k1, r1] = cells[c + 1];
            (void)a0; (void)b1;
            const float x = b0, d0 = std::max(lo, x), d1 = hi;
            if (d1 <= d0 || x != a1) continue;
            const float hA0 = topAt(k0, r0, d0), hA1 = topAt(k0, r0, d1), hB0 = topAt(k1, r1, d0), hB1 = topAt(k1, r1, d1);
            // Tops that meet at an end (an incline at a clearway's back edge) may differ there by a float step: equal
            const float tol = 1e-6f;
            const float lo0 = std::min(hA0, hB0), hi0 = std::max(hA0, hB0), lo1 = std::min(hA1, hB1), hi1 = std::max(hA1, hB1);
            if (hA0 >= hB0 - tol && hA1 >= hB1 - tol) {   // the face belongs to cell c, facing +lat
                if (hA0 > hB0 + tol || hA1 > hB1 + tol)
                    addPoly(folded, { { x, d0, lo0 }, { x, d1, lo1 }, { x, d1, hi1 }, { x, d0, hi0 } }, glm::vec3(1.0f, 0.0f, 0.0f));
            } else if (hB0 >= hA0 - tol && hB1 >= hA1 - tol) {
                addPoly(folded, { { x, d0, lo0 }, { x, d1, lo1 }, { x, d1, hi1 }, { x, d0, hi0 } }, glm::vec3(-1.0f, 0.0f, 0.0f));
            } else {
                throw std::logic_error("seated::mesh: crossing cell tops (layout invariant violated)");
            }
        }
        // faces between this band and the next (at dep = hi), per lat overlap
        if (j + 1 < nb && hi < edge) {
            float nlo, nhi;
            band(L, j + 1, nlo, nhi);
            float m0, m1;
            int nk, nr;
            for (const auto& [a, b, k, r] : cells)
                for (int c2 = 0; cell(L, j + 1, c2, m0, m1, nk, nr); ++c2) {
                    const float s0 = std::max(a, m0), s1 = std::min(std::min(b, m1), hi);   // lat <= dep = hi
                    if (s1 <= s0) continue;
                    const float h = topAt(k, r, hi), h2 = topAt(nk, nr, hi);
                    if (h > h2) addPoly(folded, { { s0, hi, h2 }, { s1, hi, h2 }, { s1, hi, h }, { s0, hi, h } }, glm::vec3(0.0f, 1.0f, 0.0f));
                    else if (h2 > h) addPoly(folded, { { s0, hi, h }, { s1, hi, h }, { s1, hi, h2 }, { s0, hi, h2 } }, glm::vec3(0.0f, -1.0f, 0.0f));
                }
        }
    }
    // The pitch fence (visual: the measured ring, sim_params.hpp), on the ground
    {
        const float fi = FENCE_HALF_INNER, fo = FENCE_HALF_OUTER, t = FENCE_VISUAL_TOP;
        std::vector<glm::vec3> top;
        for (const glm::vec2 v : clipRect(0.0f, fo, fi, fo)) top.emplace_back(v.x, v.y, t);
        addPoly(folded, top, up);
        addPoly(folded, { { 0.0f, fo, 0.0f }, { fo, fo, 0.0f }, { fo, fo, t }, { 0.0f, fo, t } }, glm::vec3(0.0f, 1.0f, 0.0f));
        addPoly(folded, { { 0.0f, fi, 0.0f }, { fi, fi, 0.0f }, { fi, fi, t }, { 0.0f, fi, t } }, glm::vec3(0.0f, -1.0f, 0.0f));
    }
    // Unfold: the 8 images (x, y) = (sx lat, sy dep) and (sx dep, sy lat); each triangle re-wound around its image normal
    std::vector<float> out;
    out.reserve(folded.size() * 8 * 18);
    for (int q = 0; q < 4; ++q) {
        const float sx = (q == 1 || q == 2) ? -1.0f : 1.0f, sy = (q >= 2) ? -1.0f : 1.0f;
        for (int wing = 0; wing < 2; ++wing) {
            auto map = [&](glm::vec3 v) { return wing == 0 ? glm::vec3(sx * v.x, sy * v.y, v.z) : glm::vec3(sx * v.y, sy * v.x, v.z); };
            for (const Tri& t : folded) {
                glm::vec3 v[3] = { map(t.v[0]), map(t.v[1]), map(t.v[2]) };
                const glm::vec3 n = map(t.n);
                if (glm::dot(glm::cross(v[1] - v[0], v[2] - v[0]), n) < 0.0f) std::swap(v[1], v[2]);
                for (const glm::vec3& p : v) out.insert(out.end(), { p.x, p.y, p.z, n.x, n.y, n.z });
            }
        }
    }
    return out;
}

std::string meshOBJ(const SeatedLayout& L, const char* comment) {
    const std::vector<float> m = mesh(L);
    std::map<std::tuple<float, float, float>, int> vIndex, nIndex;
    std::vector<glm::vec3> vs, ns;
    std::vector<std::pair<int, int>> corners;
    auto index = [](std::map<std::tuple<float, float, float>, int>& map, std::vector<glm::vec3>& list, glm::vec3 v) {
        const auto key = std::make_tuple(v.x == 0.0f ? 0.0f : v.x, v.y == 0.0f ? 0.0f : v.y, v.z == 0.0f ? 0.0f : v.z);   // -0 == +0
        const auto it = map.find(key);
        if (it != map.end()) return it->second;
        list.push_back(v);
        return map[key] = int(list.size());
    };
    for (size_t i = 0; i + 5 < m.size(); i += 6)
        corners.emplace_back(index(vIndex, vs, glm::vec3(m[i], m[i + 1], m[i + 2])), index(nIndex, ns, glm::vec3(m[i + 3], m[i + 4], m[i + 5])));
    std::ostringstream s;
    s << "# " << comment << "\n# " << corners.size() / 3 << " triangles, outward normals, counter-clockwise from outside\n";
    char b[96];
    for (const glm::vec3& v : vs) { std::snprintf(b, sizeof b, "v %.9g %.9g %.9g\n", v.x, v.y, v.z); s << b; }
    for (const glm::vec3& n : ns) { std::snprintf(b, sizeof b, "vn %.9g %.9g %.9g\n", n.x, n.y, n.z); s << b; }
    for (size_t i = 0; i + 2 < corners.size(); i += 3) {
        std::snprintf(b, sizeof b, "f %d//%d %d//%d %d//%d\n", corners[i].first, corners[i].second, corners[i + 1].first,
                      corners[i + 1].second, corners[i + 2].first, corners[i + 2].second);
        s << b;
    }
    return s.str();
}

} // namespace seated
} // namespace swarm
