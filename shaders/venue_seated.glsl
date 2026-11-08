// Analytic seated venue: the exact signed distance of a heightfield of boxes and inclines (no texture).
// Not a shader of its own: the per-venue preamble (swarm/venue.hpp venuePreamble) appends this file after the VS_*
// layout literals, so every program of a seated venue has it. src/venue.cpp (namespace swarm::seated) mirrors every
// function line by line; the geometry is described in venue.hpp, the method in venue.cpp (sdfGradStats).
// Folded frame: lat = min(|x|, |y|), dep = max(|x|, |y|). Bands along dep: 0 walkway (and pitch), 1 barrier, 2 + 2k the
// clearway of row k, 3 + 2k its seat block, then concourse, outer wall, landing, outside. Cells per band along lat.
// Arithmetic that classifies (band and cell bounds, floor heights) is 'precise', so the GPU computes the same bits as the
// CPU mirror (no fused multiply-add).
// Generated venues (M, L; swarm/venue.hpp): several straight gangways per wing (VS_GW_LO / HI [VS_GANGWAYS], from row front
// VS_GW_ROW, merging with the corner gangway before row front VS_GW_SEATED), a door at every gangway head (VS_DOOR_LO / HI [VS_DOORS],
// the corner door from VS_CORNER_DOOR_LO); the arrays come with the layout's literals (venue.cpp seatedArrays). VS_GENERATED 0 (venue
// S: one straight gangway and one door per wing) compiles its own cell table and band search, VS_GENERATED 1 the general
// ones. Both describe S's cells with the same values (the CPU mirror, src/venue.cpp, has the general code only and keeps S's CPU pins);
// S keeps its own code because the GPU compiler turned the general one into different bits (fused operations) for S's golden runs.
const int VS_GROUND = 0, VS_TREAD = 1, VS_SEAT = 2, VS_INCLINE = 3, VS_BARRIER = 4, VS_WALL = 5, VS_CONC = 6, VS_SIDE = 7;
const int VS_BANDS = 6 + 2 * VS_ROWS;
#if VS_GENERATED
const int VS_MAX_CELLS = 4 + 2 * max(VS_GANGWAYS, VS_DOORS);   // cells per band (the table below)
#else
const int VS_MAX_CELLS = 6;      // cells per band (the table below)
#endif
const float VS_BIG = 1e9;        // sentinel: unbounded / no point

float vsRowFront(int k) { precise float d = VS_ROW0 + float(k) * VS_ROW_DEPTH; return d; }
float vsRowTread(int k) { precise float z = VS_FIRST_ROW + float(k) * VS_ROW_RISE; return z; }

void vsBand(int j, out float lo, out float hi) {
    if (j <= 0) { lo = 0.0; hi = VS_STAND_FRONT; return; }
    if (j == 1) { lo = VS_STAND_FRONT; hi = VS_ROW0; return; }
    if (j < VS_BANDS - 4) {
        int k = (j - 2) >> 1;
        float d = vsRowFront(k);
        if (((j - 2) & 1) == 0) { lo = d; hi = d + VS_CLEARWAY; }
        else { lo = d + VS_CLEARWAY; hi = vsRowFront(k + 1); }
        return;
    }
    if (j == VS_BANDS - 4) { lo = VS_CONC_FRONT; hi = VS_CONC_BACK; return; }
    if (j == VS_BANDS - 3) { lo = VS_CONC_BACK; hi = VS_OUTER_FACE; return; }
    if (j == VS_BANDS - 2) { lo = VS_OUTER_FACE; hi = VS_LANDING_END; return; }
    lo = VS_LANDING_END;
    hi = VS_BIG;
}

int vsBandOf(float dep) {
    if (dep < VS_STAND_FRONT) return 0;
    if (dep < VS_ROW0) return 1;
    if (dep < VS_CONC_FRONT) {
        int k = clamp(int(floor((dep - VS_ROW0) / VS_ROW_DEPTH)), 0, VS_ROWS - 1);
        if (dep < vsRowFront(k)) --k;   // the division rounded across a row front
        else if (k + 1 < VS_ROWS && dep >= vsRowFront(k + 1)) ++k;
        return 2 + 2 * k + (dep >= vsRowFront(k) + VS_CLEARWAY ? 1 : 0);
    }
    if (dep < VS_CONC_BACK) return VS_BANDS - 4;
    if (dep < VS_OUTER_FACE) return VS_BANDS - 3;
    if (dep < VS_LANDING_END) return VS_BANDS - 2;
    return VS_BANDS - 1;
}

// The straight gangways of row front r (a band follows r = (j - 1) / 2) and whether the last one merges with the corner
// gangway (SeatedLayout::activeGangways / mergedCorner); the loop unrolls over the constant arrays
void vsFront(int r, out int n, out bool merged) {
    n = 0;
    merged = false;
    for (int i = 0; i < VS_GANGWAYS; ++i)
        if (VS_GW_ROW[i] <= r) { n = i + 1; merged = r < VS_GW_SEATED[i]; }
}
int vsActiveGangways(int r) { int n; bool m; vsFront(r, n, m); return n; }
bool vsMergedCorner(int r) { int n; bool m; vsFront(r, n, m); return m; }

#if VS_GENERATED
// Cell c of band j, ascending in lat: [l0, l1), its kind and tread row; the last cell reaches the band's outer depth
// (across the diagonal fold). False past the last cell. (seated::cell)
bool vsCell(int j, int c, out float l0, out float l1, out int kind, out int row) {
    float lo, hi;
    vsBand(j, lo, hi);
    row = -1;
    l0 = 0.0;
    l1 = 0.0;
    kind = VS_GROUND;
    if (j == 0 || j == VS_BANDS - 1) {   // walkway (and the pitch under the fence); outside
        if (c > 0) return false;
        l1 = hi;
        return true;
    }
    bool cornerDoor = VS_CORNER_DOOR_LO < 1e8;
    if (j == VS_BANDS - 2) {   // landings beyond the concourse exits: every door's, the corner door's
        int i = c >> 1;
        if (i < VS_DOORS) {
            if ((c & 1) == 0) { l0 = i == 0 ? 0.0 : VS_DOOR_HI[max(i - 1, 0)]; l1 = VS_DOOR_LO[i]; }
            else { l0 = VS_DOOR_LO[i]; l1 = VS_DOOR_HI[i]; kind = VS_CONC; }
            return true;
        }
        if (c == 2 * VS_DOORS) { l0 = VS_DOOR_HI[VS_DOORS - 1]; l1 = cornerDoor ? VS_CORNER_DOOR_LO : hi; return true; }
        if (c == 2 * VS_DOORS + 1 && cornerDoor) { l0 = VS_CORNER_DOOR_LO; l1 = hi; kind = VS_CONC; return true; }
        return false;
    }
    if (c == 0) { l1 = VS_AVENUE_HALF; return true; }   // the avenue
    if (j == VS_BANDS - 3) {   // outer wall (the side wall runs into it) with the concourse doors and the corner door
        int i = (c - 1) >> 1;
        if (i < VS_DOORS) {
            if ((c & 1) == 1) { l0 = i == 0 ? VS_AVENUE_HALF : VS_DOOR_HI[max(i - 1, 0)]; l1 = VS_DOOR_LO[i]; kind = VS_WALL; }
            else { l0 = VS_DOOR_LO[i]; l1 = VS_DOOR_HI[i]; kind = VS_CONC; }
            return true;
        }
        if (c == 2 * VS_DOORS + 1) { l0 = VS_DOOR_HI[VS_DOORS - 1]; l1 = cornerDoor ? VS_CORNER_DOOR_LO : hi; kind = VS_WALL; return true; }
        if (c == 2 * VS_DOORS + 2 && cornerDoor) { l0 = VS_CORNER_DOOR_LO; l1 = hi; kind = VS_CONC; return true; }
        return false;
    }
    if (j == VS_BANDS - 4) {   // concourse (the side wall: a full wall)
        if (c == 1) { l0 = VS_AVENUE_HALF; l1 = VS_LAT0; kind = VS_WALL; return true; }
        if (c > 2) return false;
        l0 = VS_LAT0;
        l1 = hi;
        kind = VS_CONC;
        return true;
    }
    // Barrier band and row bands: dead-end segment, straight gangway 0, segment, [straight gangway i, segment,] corner gangway (from
    // cornerInset before the diagonal at the front of the row the band belongs to: a clearway band's own front, a seat band's next
    // row); seat blocks and the barrier end VS_SEAT_INSET short of the gangways; the clearways reach the gangways' edges; the
    // last straight gangway merges with the corner gangway while no seat follows it
    int segKind = VS_BARRIER, gapKind = VS_GROUND;
    bool seatBand = true;
    float corner = hi - VS_CORNER_INSET - VS_SEAT_INSET;
    if (j >= 2) {
        row = (j - 2) >> 1;
        seatBand = ((j - 2) & 1) != 0;
        segKind = seatBand ? VS_SEAT : VS_TREAD;
        gapKind = VS_INCLINE;
        if (!seatBand) corner = lo - VS_CORNER_INSET;
    }
    if (c == 1) { l0 = VS_AVENUE_HALF; l1 = VS_LAT0; kind = VS_SIDE; return true; }   // the side wall: a parapet at the row's seat-block top
    int n;
    bool merged;
    vsFront((j - 1) >> 1, n, merged);
    float inset = seatBand ? VS_SEAT_INSET : 0.0;
    int i = (c - 2) >> 1;   // c even: the segment before straight gangway i; odd: gangway i
    if (i < n) {
        if ((c & 1) == 0) {
            if (i == 0) l0 = VS_LAT0;
            else { float h = VS_GW_HI[max(i - 1, 0)]; l0 = seatBand ? h + VS_SEAT_INSET : h; }
            float g = VS_GW_LO[i];
            l1 = seatBand ? g - VS_SEAT_INSET : g;
            kind = segKind;
        } else {
            float g = VS_GW_LO[i];
            l0 = seatBand ? g - VS_SEAT_INSET : g;
            float h = VS_GW_HI[i];
            l1 = merged && i == n - 1 ? hi : (seatBand ? h + VS_SEAT_INSET : h);
            kind = gapKind;
        }
        return true;
    }
    if (merged) return false;
    float h = VS_GW_HI[max(n - 1, 0)];
    if (c == 2 + 2 * n) { l0 = seatBand ? h + VS_SEAT_INSET : h; l1 = corner; kind = segKind; return true; }
    if (c == 3 + 2 * n) { l0 = corner; l1 = hi; kind = gapKind; return true; }
    return false;
}
#else
// Cell c of band j, ascending in lat: [l0, l1), its kind and tread row; the last cell reaches the band's outer depth
// (across the diagonal fold). False past the last cell.
bool vsCell(int j, int c, out float l0, out float l1, out int kind, out int row) {
    float lo, hi;
    vsBand(j, lo, hi);
    row = -1;
    l0 = 0.0;
    l1 = 0.0;
    kind = VS_GROUND;
    if (j == 0 || j == VS_BANDS - 1) {   // walkway (and the pitch under the fence); outside
        if (c > 0) return false;
        l1 = hi;
        return true;
    }
    if (j == VS_BANDS - 2) {   // landings beyond the concourse exits
        if (c == 0) { l1 = VS_EXIT_LO; return true; }
        if (c == 1) { l0 = VS_EXIT_LO; l1 = VS_EXIT_HI; kind = VS_CONC; return true; }
        if (c == 2) { l0 = VS_EXIT_HI; l1 = hi; return true; }
        return false;
    }
    if (c == 0) { l1 = VS_AVENUE_HALF; return true; }   // the avenue
    if (j == VS_BANDS - 3) {   // outer wall (the side wall runs into it) with the concourse exit
        if (c == 1) { l0 = VS_AVENUE_HALF; l1 = VS_EXIT_LO; kind = VS_WALL; return true; }
        if (c == 2) { l0 = VS_EXIT_LO; l1 = VS_EXIT_HI; kind = VS_CONC; return true; }
        if (c == 3) { l0 = VS_EXIT_HI; l1 = hi; kind = VS_WALL; return true; }
        return false;
    }
    if (j == VS_BANDS - 4) {   // concourse (the side wall: a full wall)
        if (c == 1) { l0 = VS_AVENUE_HALF; l1 = VS_LAT0; kind = VS_WALL; return true; }
        if (c > 2) return false;
        l0 = VS_LAT0;
        l1 = hi;
        kind = VS_CONC;
        return true;
    }
    // Barrier band and row bands: dead-end segment, straight gangway, segment, corner gangway (from cornerInset before the
    // diagonal at the front of the row the band belongs to: a clearway band's own front, a seat band's next row)
    // seat blocks and the barrier end VS_SEAT_INSET short of both gangways; the clearways reach the gangways' edges
    int segKind = VS_BARRIER, gapKind = VS_GROUND;
    float corner = hi - VS_CORNER_INSET - VS_SEAT_INSET, gLo = VS_GANGWAY_LO - VS_SEAT_INSET, gHi = VS_GANGWAY_HI + VS_SEAT_INSET;
    if (j >= 2) {
        row = (j - 2) >> 1;
        bool seatBand = ((j - 2) & 1) != 0;
        segKind = seatBand ? VS_SEAT : VS_TREAD;
        gapKind = VS_INCLINE;
        if (!seatBand) { corner = lo - VS_CORNER_INSET; gLo = VS_GANGWAY_LO; gHi = VS_GANGWAY_HI; }
    }
    if (c == 1) { l0 = VS_AVENUE_HALF; l1 = VS_LAT0; kind = VS_SIDE; return true; }   // the side wall: a parapet at the row's seat-block top
    if (c == 2) { l0 = VS_LAT0; l1 = gLo; kind = segKind; return true; }
    if (c == 3) { l0 = gLo; l1 = gHi; kind = gapKind; return true; }
    if (c == 4) { l0 = gHi; l1 = corner; kind = segKind; return true; }
    if (c == 5) { l0 = corner; l1 = hi; kind = gapKind; return true; }
    return false;
}
#endif

float vsCellTop(int kind, int row, float dep) {
    if (kind == VS_TREAD) return vsRowTread(row);
    if (kind == VS_SEAT) { precise float t = vsRowTread(row) + VS_SEAT_TOP; return t; }
    if (kind == VS_INCLINE) { precise float t = VS_RAKE * (dep - VS_ROW0); return t; }
    if (kind == VS_BARRIER) return VS_BARRIER_TOP;
    if (kind == VS_WALL) return VS_WALL_TOP;
    if (kind == VS_CONC) return VS_CONC_Z;
    if (kind == VS_SIDE) {   // the side wall beside the barrier and the rows: the barrier's top, a row's seat-block top
        if (row < 0) return VS_BARRIER_TOP;
        precise float t = vsRowTread(row) + VS_SEAT_TOP;
        return t;
    }
    return 0.0;
}

vec2 vsFold(vec2 xy) { vec2 a = abs(xy); return vec2(min(a.x, a.y), max(a.x, a.y)); }

vec2 vsUnfoldDir(vec2 xy, vec2 d) {
    vec2 s = vec2(xy.x < 0.0 ? -1.0 : 1.0, xy.y < 0.0 ? -1.0 : 1.0);
    vec2 a = abs(xy);
    return a.y >= a.x ? vec2(s.x * d.x, s.y * d.y) : vec2(s.x * d.y, s.y * d.x);
}

// The cell of band j containing lat
void vsOwnCell(int j, float lat, out float l0, out float l1, out int kind, out int row) {
    l0 = 0.0;
    l1 = 0.0;
    kind = VS_GROUND;
    row = -1;
    for (int c = 0; c < VS_MAX_CELLS; ++c) {
        float a, b;
        int k, r;
        if (!vsCell(j, c, a, b, k, r)) break;
        l0 = a; l1 = b; kind = k; row = r;
        if (lat < b) break;
    }
}

// The metrics' per-gangway utilisation (seated::gangwayAt): the gangway an agent at xy stands on (an incline cell, or a
// barrier gap at a gangway's foot; a straight gangway merged with the corner gangway counts as the corner gangway), -1: none. Ids per
// quadrant (0 +x+y, 1 -x+y, 2 -x-y, 3 +x-y): wing 0's straight gangways (|y| >= |x|), wing 1's, the corner gangway.
int venueGangwayAt(vec2 xy) {
    vec2 f = vsFold(xy);
    int j = vsBandOf(f.y);
    if (j < 1 || j >= VS_BANDS - 4) return -1;
    int idx = 0, kind = VS_GROUND;
    for (int c = 0; c < VS_MAX_CELLS; ++c) {
        float a, b;
        int k, r;
        if (!vsCell(j, c, a, b, k, r)) break;
        idx = c; kind = k;
        if (f.x < b) break;
    }
    if (!(kind == VS_INCLINE || (j == 1 && kind == VS_GROUND && idx >= 2))) return -1;
    int n;
    bool merged;
    vsFront((j - 1) >> 1, n, merged);
    int i = (idx - 3) >> 1;
    bool straight = (idx & 1) == 1 && i < n && !(merged && i == n - 1);
    vec2 a = abs(xy);
    int q = xy.x >= 0.0 ? (xy.y >= 0.0 ? 0 : 3) : (xy.y >= 0.0 ? 1 : 2);
    int base = q * (2 * VS_GANGWAYS + 1);
    return straight ? base + (a.y >= a.x ? 0 : VS_GANGWAYS) + i : base + 2 * VS_GANGWAYS;
}

// The cell under xy as a key (its band, its lateral start): the floor is continuous within a cell (venueStepUpScan)
vec2 venueCellKey(vec2 xy) {
    vec2 f = vsFold(xy);
    int j = vsBandOf(f.y);
    float l0, l1;
    int kind, row;
    vsOwnCell(j, f.x, l0, l1, kind, row);
    return vec2(float(j), l0);
}

// The heightfield: the venue is solid exactly where z <= venueFloor(xy) (the fence is separate: sdFence)
float venueFloor(vec2 xy) {
    vec2 f = vsFold(xy);
    float l0, l1;
    int kind, row;
    vsOwnCell(vsBandOf(f.y), f.x, l0, l1, kind, row);
    return vsCellTop(kind, row, f.y);
}

// Nearest point (u, z) of the 2D region {u in [u0, u1]} x (below ? z <= t(u) : z >= t(u)), t(u) = s (u - uRef)
vec2 vsNearestRegion2(float u, float z, float u0, float u1, float s, float uRef, bool below) {
    float uc = clamp(u, u0, u1);
    float tc = s * (uc - uRef);
    if (below ? z <= tc : z >= tc) return vec2(uc, z);
    float t0 = s * (u0 - uRef), t1 = s * (u1 - uRef);
    float du = u1 - u0, dz = t1 - t0;
    float len2 = du * du + dz * dz;
    float t = len2 > 0.0 ? clamp(((u - u0) * du + (z - t0) * dz) / len2, 0.0, 1.0) : 0.0;
    vec2 best = vec2(u0 + t * du, t0 + t * dz);
    float bd = (u - best.x) * (u - best.x) + (z - best.y) * (z - best.y);
    vec2 r0 = vec2(u0, below ? min(z, t0) : max(z, t0)), r1 = vec2(u1, below ? min(z, t1) : max(z, t1));
    float d0 = (u - r0.x) * (u - r0.x) + (z - r0.y) * (z - r0.y), d1 = (u - r1.x) * (u - r1.x) + (z - r1.y) * (z - r1.y);
    if (d0 < bd) { bd = d0; best = r0; }
    if (d1 < bd) best = r1;
    return best;
}

// Nearest point to pf (folded) of a cell's solid column (below its top) or air column (above it), squared distance in .w;
// the corner gangway's air is clipped to the fold (lat <= dep)
vec4 vsNearestInCell(float lo, float hi, float l0, float l1, int kind, int row, vec3 pf, bool airColumn) {
    float latC = clamp(pf.x, l0, l1);
    vec3 q;
    if (kind == VS_INCLINE) {
        vec2 n2 = vsNearestRegion2(pf.y, pf.z, lo, hi, VS_RAKE, VS_ROW0, !airColumn);
        q = vec3(latC, n2.x, n2.y);
        if (airColumn && q.x > q.y) {
            float s0 = max(l0, lo), s1 = min(l1, hi);
            if (s0 > s1) return vec4(q, VS_BIG);
            const float r2 = 1.41421356;   // sqrt(2): coordinates along the diagonal
            float m = 0.5 * (pf.x + pf.y);
            vec2 w = vsNearestRegion2(m * r2, pf.z, s0 * r2, s1 * r2, VS_RAKE / r2, VS_ROW0 * r2, false);
            float s = w.x / r2;
            q = vec3(s, s, w.y);
        }
    } else {
        float top = vsCellTop(kind, row, 0.0);
        q = vec3(latC, clamp(pf.y, lo, hi), airColumn ? max(pf.z, top) : min(pf.z, top));
    }
    vec3 d = pf - q;
    return vec4(q, dot(d, d));
}

// Exact signed distance to the venue and its gradient: vec4(gradient, value). From a point in air the minimum over the
// solid columns, from a point in solid over the air columns; bands visited outward from the point's own band until the
// depth gap exceeds the best distance, at most VS_MAX_BAND_STEPS on either side.
vec4 venueMapGrad(vec3 p) {
    vec2 f = vsFold(p.xy);
    vec3 pf = vec3(f, p.z);
    int jp = vsBandOf(pf.y);
    float l0, l1;
    int kind, row;
    vsOwnCell(jp, pf.x, l0, l1, kind, row);
    bool inAir = pf.z > vsCellTop(kind, row, pf.y);
    float best = VS_BIG;
    vec3 bestQ = pf;
    vec4 bestRect = vec4(0.0);   // the nearest cell's (l0, l1, lo, hi)
    int bestKind = kind;
    bool down = true, up = true;
    for (int s = 0; s <= VS_MAX_BAND_STEPS; ++s) {
        for (int side = 0; side < 2; ++side) {
            if (s == 0 && side == 1) break;
            int j = side == 0 ? jp - s : jp + s;
            if (s > 0) {
                if (side == 0 ? !down : !up) continue;
                if (j < 0 || j >= VS_BANDS) { if (side == 0) down = false; else up = false; continue; }
            }
            float lo, hi;
            vsBand(j, lo, hi);
            float g = max(max(lo - pf.y, pf.y - hi), 0.0);
            if (s > 0 && g * g >= best) { if (side == 0) down = false; else up = false; continue; }
            for (int c = 0; c < VS_MAX_CELLS; ++c) {
                float a, b;
                int k, r;
                if (!vsCell(j, c, a, b, k, r)) break;
                float lg = max(max(a - pf.x, pf.x - b), 0.0);
#if VS_GENERATED
                if (g * g + lg * lg >= best) {
                    if (a > pf.x) break;   // every later cell lies farther right (the skipped ones would be skipped: same result)
                    continue;
                }
#else
                if (g * g + lg * lg >= best) continue;
#endif
                vec4 n = vsNearestInCell(lo, hi, a, b, k, r, pf, !inAir);
                if (n.w < best) { best = n.w; bestQ = n.xyz; bestRect = vec4(a, b, lo, hi); bestKind = k; }
            }
        }
        if (!down && !up) break;
    }
    float d = sqrt(best);
    vec3 gf;
    if (d > 0.0) {
        gf = inAir ? (pf - bestQ) / d : (bestQ - pf) / d;
    } else {
        // Exactly on the surface (root finding lands there): the normal of the face the point lies on. On a side of the
        // nearest cell's footprint it is a vertical face (towards that cell's air column from solid, away from its solid
        // column from air); inside the footprint it is that cell's top
        float sgn = inAir ? -1.0 : 1.0;
        vec2 h = vec2(pf.x <= bestRect.x ? sgn : pf.x >= bestRect.y ? -sgn : 0.0, pf.y <= bestRect.z ? sgn : pf.y >= bestRect.w ? -sgn : 0.0);
        gf = h != vec2(0.0) ? vec3(normalize(h), 0.0) : (bestKind == VS_INCLINE ? normalize(vec3(0.0, -VS_RAKE, 1.0)) : vec3(0.0, 0.0, 1.0));
    }
    return vec4(vsUnfoldDir(p.xy, gf.xy), gf.z, inAir ? d : -d);
}

float venueMap(vec3 p) { return venueMapGrad(p).w; }

// The nearest wall in the horizontal plane z = c.z (the contact model's wall rule, evaluated exactly: physics.comp clearWalls
// and wallPlaneProbe on VENUE_ANALYTIC). Walls: the vertical faces of the cells whose top lies above the plane (an incline is
// a walkable slope, never a wall). From a point outside every wall: the 2D distance to the nearest wall footprint (searched
// within 'reach'); from a point inside one: minus the distance to the nearest footprint that is not a wall there. The same
// folded band search as venueMapGrad. Returns (unit direction away from the wall, clearance); VS_BIG: no wall within reach.
vec3 venueWall(vec3 c, float reach) {
    vec2 f = vsFold(c.xy);
    int jp = vsBandOf(f.y);
    float l0, l1;
    int kind, row;
    vsOwnCell(jp, f.x, l0, l1, kind, row);
    bool inWall = kind != VS_INCLINE && vsCellTop(kind, row, f.y) > c.z;
    float best = inWall ? VS_BIG : reach * reach;
    vec2 bestQ = f;
    vec4 bestRect = vec4(0.0);
    bool found = false, down = true, up = true;
    for (int s = 0; s <= VS_MAX_BAND_STEPS; ++s) {
        for (int side = 0; side < 2; ++side) {
            if (s == 0 && side == 1) break;
            int j = side == 0 ? jp - s : jp + s;
            if (s > 0) {
                if (side == 0 ? !down : !up) continue;
                if (j < 0 || j >= VS_BANDS) { if (side == 0) down = false; else up = false; continue; }
            }
            float lo, hi;
            vsBand(j, lo, hi);
            float g = max(max(lo - f.y, f.y - hi), 0.0);
            if (s > 0 && g * g >= best) { if (side == 0) down = false; else up = false; continue; }
            for (int cc = 0; cc < VS_MAX_CELLS; ++cc) {
                float a, b;
                int k, r;
                if (!vsCell(j, cc, a, b, k, r)) break;
                bool wall = k != VS_INCLINE && vsCellTop(k, r, lo) > c.z;
                if (wall == inWall) continue;   // the nearest cell of the other kind
                vec2 q = clamp(f, vec2(a, lo), vec2(b, hi));
                vec2 dd = f - q;
                float d2 = dot(dd, dd);
                if (d2 < best) { best = d2; bestQ = q; bestRect = vec4(a, b, lo, hi); found = true; }
            }
        }
        if (!down && !up) break;
    }
    if (!found) return vec3(0.0, 0.0, VS_BIG);
    float d = sqrt(best);
    vec2 dir;
    if (d > 0.0) {
        dir = inWall ? (bestQ - f) / d : (f - bestQ) / d;
    } else {   // on a wall's face: the face's normal, out of the wall
        float sgn = inWall ? 1.0 : -1.0;
        dir = normalize(vec2(f.x <= bestRect.x ? sgn : f.x >= bestRect.y ? -sgn : 0.0, f.y <= bestRect.z ? sgn : f.y >= bestRect.w ? -sgn : 0.0));
    }
    return vec3(vsUnfoldDir(c.xy, dir), inWall ? -d : d);
}
