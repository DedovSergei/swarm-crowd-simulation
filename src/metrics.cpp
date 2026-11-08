#include <swarm/metrics.hpp>

#include <swarm/crowd_sim.hpp>
#include <swarm/sdf.hpp>
#include <swarm/shader.hpp>
#include <swarm/venue.hpp>

#include <algorithm>
#include <cmath>
#include <sstream>
#include <stdexcept>

namespace fs = std::filesystem;

namespace swarm::metrics {

std::string exitName(int exit, const SeatedLayout* L) {
    static const char* names[13] = { "+x", "-x", "+y", "-y", "other", "door +x+y y", "door +x+y x", "door -x+y y", "door -x+y x",
                                     "door -x-y y", "door -x-y x", "door +x-y y", "door +x-y x" };
    if (exit < 0 || exit >= EXIT_SLOTS) return "?";
    // venue S (one door per wing) keeps its short names; a venue with more doors names them by the layout (seated::exitName)
    if (L && L->doorsPerQuadrant() != 2 && exit >= EXIT_DOOR0) return seated::exitName(*L, 4 + exit - EXIT_DOOR0);
    if (exit < 13) return names[exit];
    return "door " + std::to_string(exit - EXIT_DOOR0);
}

int exitSlotsUsed(const SeatedLayout* L) { return L ? EXIT_DOOR0 + 4 * L->doorsPerQuadrant() : EXIT_OTHER + 1; }

int gridResOf(size_t cells) {
    const int res = int(std::lround(std::sqrt(double(cells))));
    if (size_t(res) * size_t(res) != cells || res % 16 != 0) throw std::invalid_argument("metrics: the cell table is not a square grid of a multiple of 16");
    return res;
}

const char* zoneName(uint32_t zone) {
    static const char* names[ZONE_COUNT] = { "tread", "aisle", "walkway", "avenue", "pitch", "exit" };
    return zone < ZONE_COUNT ? names[zone] : "none";
}

int exitSlot(glm::vec4 p, const SeatedLayout* L) {   // metrics_deposit.comp exitSlot()
    const glm::vec2 a = glm::abs(glm::vec2(p));
    const bool alongY = a.y >= a.x;
    const float lat = alongY ? a.x : a.y;
    if (L) {   // VENUE_ANALYTIC: the venue's avenues, else its concourse doors (seated::exitByLat)
        const int e = seated::exitByLat(*L, glm::vec2(p));
        if (e < 0) return EXIT_OTHER;
        return e < 4 ? e : EXIT_DOOR0 + e - 4;
    }
    if (lat >= AVENUE_HALF) return EXIT_OTHER;
    return alongY ? (p.y > 0.0f ? EXIT_POS_Y : EXIT_NEG_Y) : (p.x > 0.0f ? EXIT_POS_X : EXIT_NEG_X);
}

int cellIndex(int ix, int iy, int res) { return ix + iy * res; }

glm::vec2 cellCentreM(int cell, int res) {
    const int ix = cell % res, iy = cell / res;
    return glm::vec2(float(gridMinM(res) + (ix + 0.5) * CELL_M), float(gridMinM(res) + (iy + 0.5) * CELL_M));
}

uint32_t sampleZone(glm::vec2 p, float outerWallInnerDepth) {
    if (sdBox2(p - glm::vec2(FENCE_CENTER.x, FENCE_CENTER.y), glm::vec2(FENCE_HALF_MID.x, FENCE_HALF_MID.y)) < 0.0f) return ZONE_PITCH;
    const glm::vec2 a = glm::abs(p);
    const bool alongX = a.y >= a.x;   // treads run along x; this wing drains into the x = 0 avenue
    const float lat = alongX ? a.x : a.y, dep = alongX ? a.y : a.x;
    if (lat < AVENUE_HALF) return dep >= outerWallInnerDepth ? ZONE_EXIT : ZONE_AVENUE;
    if (dep < WALKWAY_MAX) return ZONE_WALKWAY;
    if (lat < AISLE_MAX) return ZONE_AISLE;
    return ZONE_TREAD;
}

namespace {

// --- Venue geometry on the exact CPU sampler (the conventions of the probes of test_gpu venue.terrace_passage_widths) ---
// Visible geometry: baked field union the fence's visual faces; inside the fence's collision band the
// analytic fence stands for the baked one (as in physics)
float sceneDist(const std::vector<float>& vol, glm::vec3 p) {
    const float fence = sdFence(p) + BODY_RADIUS;   // the visual faces: the collision band is inflated by BODY_RADIUS
    return fence < BODY_RADIUS ? fence : std::min(sampleSDF(vol, p), fence);
}

// Height of the stadium surface under xy: first crossing going down from zTop, bisected to 1e-7
float floorHeight(const std::vector<float>& vol, glm::vec2 xy, float zTop) {
    float hi = zTop, lo = zTop;
    while (lo > -0.05f && sampleSDF(vol, glm::vec3(xy, lo)) > 0.0f) { hi = lo; lo -= 0.0005f; }
    for (int i = 0; i < 40 && hi - lo > 1e-7f; ++i) {
        const float mid = 0.5f * (lo + hi);
        (sampleSDF(vol, glm::vec3(xy, mid)) > 0.0f ? hi : lo) = mid;
    }
    return 0.5f * (lo + hi);
}

// Free distance from c along the unit u until the visible geometry is reached
float freeRun(const std::vector<float>& vol, glm::vec3 c, glm::vec3 u, float maxDist = 0.4f) {
    const float step = 0.0002f;
    float prev = sceneDist(vol, c);
    for (float t = step; t <= maxDist; t += step) {
        const float d = sceneDist(vol, c + u * t);
        if (d <= 0.0f) return t - step + step * prev / (prev - d);
        prev = d;
    }
    return maxDist;
}

// The baked mesh's footprint: SDF samples 1 .. SDF_RES - 2 (the outer faces of the outer wall, x and y in
// [-0.95, 0.95]). The pad voxels beyond it carry the bake's ground plane, which is not venue floor.
constexpr float FOOTPRINT_MIN_X = SDF_ORIGIN.x, FOOTPRINT_MIN_Y = SDF_ORIGIN.y;
constexpr float FOOTPRINT_SPAN = float(SDF_RES - 3) * SDF_SPACING;

bool walkableSample(const std::vector<float>& vol, glm::vec2 p) {
    const bool inFootprint = p.x >= FOOTPRINT_MIN_X && p.x <= FOOTPRINT_MIN_X + FOOTPRINT_SPAN && p.y >= FOOTPRINT_MIN_Y &&
                             p.y <= FOOTPRINT_MIN_Y + FOOTPRINT_SPAN;
    return inFootprint && sampleSDF(vol, glm::vec3(p, FLOOR_PROBE_TOP_Z)) > 0.0f && sampleSDF(vol, glm::vec3(p, FLOOR_PROBE_BOTTOM_Z)) <= 0.0f &&
           sdFence(glm::vec3(p, 0.0f)) + BODY_RADIUS > 0.0f;
}

// Exit axes in the order of metrics::Exit: outward direction and lateral direction
const glm::vec2 EXIT_OUT[EXIT_GAPS] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
const glm::vec2 EXIT_LAT[EXIT_GAPS] = { { 0, 1 }, { 0, 1 }, { 1, 0 }, { 1, 0 } };

} // namespace

MetricVenue computeMetricVenue(const std::vector<float>& vol) {
    if (vol.empty()) throw std::runtime_error("computeMetricVenue: no SDF volume (loadSDFTexture3D first)");
    MetricVenue v;

    // The outer wall's inner face: where the column at FLOOR_PROBE_TOP_Z turns solid on a radial line at
    // lat 0.3 (across the back platform) between dep 0.90 (platform) and 0.94 (wall); the nearest of the
    // 8 stand wings. The EXIT zone (the wall gap in each avenue) starts there.
    v.outerWallInnerDepth = 1.0f;
    for (int e = 0; e < EXIT_GAPS; ++e)
        for (float sgn : { -1.0f, 1.0f }) {
            auto at = [&](float dep) { return EXIT_LAT[e] * (sgn * 0.3f) + EXIT_OUT[e] * dep; };
            float lo = 0.90f, hi = 0.94f;
            if (sampleSDF(vol, glm::vec3(at(lo), FLOOR_PROBE_TOP_Z)) <= 0.0f || sampleSDF(vol, glm::vec3(at(hi), FLOOR_PROBE_TOP_Z)) > 0.0f)
                throw std::runtime_error("computeMetricVenue: no outer wall between dep 0.90 and 0.94 (venue changed?)");
            for (int i = 0; i < 30; ++i) {
                const float mid = 0.5f * (lo + hi);
                (sampleSDF(vol, glm::vec3(at(mid), FLOOR_PROBE_TOP_Z)) > 0.0f ? lo : hi) = mid;
            }
            v.outerWallInnerDepth = std::min(v.outerWallInnerDepth, lo);
        }

    // Walkable area and zone per cell: SUBSAMPLES^2 sample points at the centres of a regular subgrid
    v.walkableM2.assign(CELLS, 0.0f);
    v.zone.assign(CELLS, ZONE_COUNT);
    v.included.assign(CELLS, 0);
    const double sampleM = CELL_M / SUBSAMPLES;
#pragma omp parallel for schedule(dynamic, 1)
    for (int cell = 0; cell < CELLS; ++cell) {
        const int ix = cell % GRID_RES, iy = cell / GRID_RES;
        int count = 0;
        int byZone[ZONE_COUNT] = {};
        for (int sy = 0; sy < SUBSAMPLES; ++sy)
            for (int sx = 0; sx < SUBSAMPLES; ++sx) {
                const double xm = GRID_MIN_M + ix * CELL_M + (sx + 0.5) * sampleM;
                const double ym = GRID_MIN_M + iy * CELL_M + (sy + 0.5) * sampleM;
                const glm::vec2 p(float(units::modelLength(xm)), float(units::modelLength(ym)));
                if (!walkableSample(vol, p)) continue;
                ++count;
                ++byZone[sampleZone(p, v.outerWallInnerDepth)];
            }
        v.walkableM2[size_t(cell)] = float(count * sampleM * sampleM);
        if (count > 0) v.zone[size_t(cell)] = uint32_t(std::max_element(byZone, byZone + ZONE_COUNT) - byZone);
        v.included[size_t(cell)] = v.walkableM2[size_t(cell)] >= MIN_WALKABLE_M2;
    }

    // Clear width of each exit gap: lateral section through the avenue axis at dep EXIT_DEPTH (where
    // physics removes agents), at the rest height above the floor there
    for (int e = 0; e < EXIT_GAPS; ++e) {
        const glm::vec2 c = EXIT_OUT[e] * EXIT_DEPTH;
        const glm::vec3 p(c, floorHeight(vol, c, 0.2f) + BODY_RADIUS), u(EXIT_LAT[e], 0.0f);
        v.exitWidthM[size_t(e)] = float(units::metres(freeRun(vol, p, u) + freeRun(vol, p, -u)));
    }
    return v;
}

MetricVenue computeMetricVenue(const Venue& venue) {
    if (venue.seated()) return computeMetricVenueSeated(venue.layout, venue.metricGridRes);
    return computeMetricVenue(sdfVolumeCPU());
}

MetricVenue computeMetricVenueSeated(const SeatedLayout& L, int res) {
    MetricVenue v;
    v.res = res;
    const int cells = res * res;
    const double minM = gridMinM(res);
    v.outerWallInnerDepth = L.concBack;
    const glm::vec2 fc(FENCE_CENTER.x, FENCE_CENTER.y), fm(FENCE_HALF_MID.x, FENCE_HALF_MID.y);
    // zone of a sample point, or ZONE_COUNT if it is not walkable floor
    auto sample = [&](glm::vec2 p) -> uint32_t {
        if (sdFence(glm::vec3(p, 0.0f)) + BODY_RADIUS <= 0.0f) return ZONE_COUNT;   // the fence's visual band
        if (sdBox2(p - fc, fm) < 0.0f) return ZONE_PITCH;
        const glm::vec2 f = seated::fold(p);
        if (f.y > L.outerFace) return ZONE_COUNT;   // beyond the exit test
        int row = 0, band = 0;
        const int kind = seated::cellAt(L, p, &row, &band);
        if (kind == seated::SEAT || kind == seated::BARRIER || kind == seated::WALL || kind == seated::SIDE) return ZONE_COUNT;
        if (f.y < L.standFront) return ZONE_WALKWAY;
        if (f.x < L.avenueHalf) return f.y >= L.concBack ? ZONE_EXIT : ZONE_AVENUE;
        if (kind == seated::TREAD) return ZONE_TREAD;
        if (kind == seated::INCLINE || kind == seated::GROUND) return ZONE_AISLE;
        return f.y >= L.concBack ? ZONE_EXIT : ZONE_WALKWAY;   // CONC: a concourse exit, or the concourse
    };
    v.walkableM2.assign(size_t(cells), 0.0f);
    v.zone.assign(size_t(cells), ZONE_COUNT);
    v.included.assign(size_t(cells), 0);
    const double sampleM = CELL_M / SUBSAMPLES;
#pragma omp parallel for schedule(dynamic, 1)
    for (int cell = 0; cell < cells; ++cell) {
        const int ix = cell % res, iy = cell / res;
        int count = 0;
        int byZone[ZONE_COUNT] = {};
        for (int sy = 0; sy < SUBSAMPLES; ++sy)
            for (int sx = 0; sx < SUBSAMPLES; ++sx) {
                const double xm = minM + ix * CELL_M + (sx + 0.5) * sampleM;
                const double ym = minM + iy * CELL_M + (sy + 0.5) * sampleM;
                const uint32_t z = sample(glm::vec2(float(units::modelLength(xm)), float(units::modelLength(ym))));
                if (z >= ZONE_COUNT) continue;
                ++count;
                ++byZone[z];
            }
        v.walkableM2[size_t(cell)] = float(count * sampleM * sampleM);
        if (count > 0) v.zone[size_t(cell)] = uint32_t(std::max_element(byZone, byZone + ZONE_COUNT) - byZone);
        v.included[size_t(cell)] = v.walkableM2[size_t(cell)] >= MIN_WALKABLE_M2;
    }
    // Exit widths: the avenues, and every door slot the layout has (seated::exitWidthM); the rest 0
    for (int e = 0; e < EXIT_GAPS; ++e) v.exitWidthM[size_t(e)] = float(units::metres(2.0 * double(L.avenueHalf)));
    for (int e = EXIT_DOOR0; e < exitSlotsUsed(&L); ++e) v.exitWidthM[size_t(e)] = float(seated::exitWidthM(L, 4 + e - EXIT_DOOR0));
    return v;
}

std::vector<GpuMetricCellInfo> MetricVenue::cellInfo() const {
    const int cells = res * res;
    std::vector<GpuMetricCellInfo> info(static_cast<size_t>(cells));
    for (int c = 0; c < cells; ++c) {
        GpuMetricCellInfo& i = info[size_t(c)];
        i.walkableM2 = walkableM2[size_t(c)];
        i.zone = zone[size_t(c)];
        for (uint32_t& t : i.thresholdMass) t = NEVER;
        if (!included[size_t(c)]) continue;
        for (int k = 0; k < THRESHOLD_COUNT; ++k) {
            const double m = std::ceil(THRESHOLD_P_M2[size_t(k)] * double(i.walkableM2) * double(MASS_ONE));
            i.thresholdMass[k] = uint32_t(std::clamp(m, 1.0, double(NEVER)));
        }
    }
    return info;
}

// --- Cloud-in-cell, exactly as metrics_deposit.comp ---
CicDeposit cicDeposit(glm::vec2 xy, int res) {
    // float arithmetic in the shader's order: multiply, round, add, round (the shader's 'precise')
    const float off = gridOffset(res);
    const float gx = xy.x * CELLS_PER_UNIT + off, gy = xy.y * CELLS_PER_UNIT + off;
    const float fx = std::floor(gx), fy = std::floor(gy);
    const float tx = gx - fx, ty = gy - fy;
    const uint32_t qx = uint32_t(std::floor(tx * float(SUBCELL) + 0.5f)), qy = uint32_t(std::floor(ty * float(SUBCELL) + 0.5f));
    const uint32_t rx = SUBCELL - qx, ry = SUBCELL - qy;
    const int ix = int(fx), iy = int(fy);
    auto idx = [res](int x, int y) { return std::clamp(x, 0, res - 1) + std::clamp(y, 0, res - 1) * res; };
    return { { idx(ix, iy), idx(ix + 1, iy), idx(ix, iy + 1), idx(ix + 1, iy + 1) }, { rx * ry, qx * ry, rx * qy, qx * qy } };
}

uint32_t speedMass(uint32_t weight, float speedMps) {
    const float sm = float(weight) * speedMps + 0.5f;
    return uint32_t(std::floor(sm));
}

float horizontalSpeedMps(const glm::vec4& v) { return std::sqrt(v.x * v.x + v.y * v.y) * SPEED_M_S_PER_UNIT; }

std::string metricsPreamble(int res) {
    std::ostringstream s;
    s << "// ---- generated from swarm/metrics.hpp ----\n"
      << "#define METRIC_GRID_RES " << res << "\n"
      << "#define METRIC_CELLS " << res * res << "\n"
      << "#define METRIC_CELLS_PER_UNIT " << glslFloatLiteral(CELLS_PER_UNIT) << "\n"
      << "#define METRIC_GRID_OFFSET " << glslFloatLiteral(gridOffset(res)) << "\n"
      << "#define METRIC_SUBCELL " << SUBCELL << "u\n"
      << "#define METRIC_SPEED_M_S_PER_UNIT " << glslFloatLiteral(SPEED_M_S_PER_UNIT) << "\n"
      << "#define METRIC_CRUSH_INDEX " << CRUSH_INDEX << "\n"
      << "#define METRIC_EXIT_SLOTS " << EXIT_SLOTS << "\n"
      << "#define METRIC_EXIT_POS_X " << EXIT_POS_X << "\n"
      << "#define METRIC_EXIT_NEG_X " << EXIT_NEG_X << "\n"
      << "#define METRIC_EXIT_POS_Y " << EXIT_POS_Y << "\n"
      << "#define METRIC_EXIT_NEG_Y " << EXIT_NEG_Y << "\n"
      << "#define METRIC_EXIT_OTHER " << EXIT_OTHER << "\n"
      << "#define METRIC_EXIT_DOOR0 " << EXIT_DOOR0 << "\n"
      << "#define METRIC_GANGWAY_SLOTS " << GANGWAY_SLOTS << "\n"
      << "// ---- end generated ----\n";
    return s.str();
}

// --- GPU ---
std::vector<ProgramSpec> CrowdMetrics::programSpecs(const fs::path& shaderDir, int res, const Venue* venue) {
    const std::string pre = metricsPreamble(res);
    return { { shaderDir / "metrics_deposit.comp", {}, pre, venue }, { shaderDir / "metrics_finalize.comp", {}, pre, venue } };
}

std::vector<ProgramBindings> CrowdMetrics::programBindings(bool seated) {
    std::vector<GLuint> deposit = { BIND_BOIDS_IN, BIND_BOIDS_OUT, BIND_METRIC_COUNTERS, BIND_METRIC_EVAC_STEP, BIND_METRIC_MASS };
    if (seated) deposit.push_back(BIND_METRIC_GANGWAY);
    return { { "metrics_deposit", true, deposit }, { "metrics_finalize", true, { BIND_METRIC_COUNTERS, BIND_METRIC_MASS, BIND_METRIC_CELL_INFO, BIND_METRIC_CELLS } } };
}

std::vector<GpuBufferUse> CrowdMetrics::bufferUses(int numBoids, int res) {
    const int64_t n = numBoids, cells = int64_t(res) * res;
    return {
        { "the metric counters", int64_t(sizeof(GpuMetricCounters)) },
        { "the evacuation steps", n * int64_t(sizeof(uint32_t)) },
        { "the metric mass", cells * int64_t(sizeof(GpuMetricCellMass)) },
        { "the metric cells", cells * int64_t(sizeof(GpuMetricCell)) },
        { "the metric table", cells * int64_t(sizeof(GpuMetricCellInfo)) },
        { "the gangway state", n * 16 },
    };
}

CrowdMetrics::CrowdMetrics(const fs::path& shaderDir, int numBoids, const std::vector<GpuMetricCellInfo>& cellInfo, const Venue* venue)
    : numBoids_(numBoids) {
    if (numBoids <= 0) throw std::invalid_argument("CrowdMetrics: numBoids must be positive");
    res_ = gridResOf(cellInfo.size());   // the venue's metric grid (the terrace and S: 64)
    if (venue && venue->metricGridRes != res_) throw std::invalid_argument("CrowdMetrics: cellInfo is not the venue's metric grid");
    if (venue && venue->seated() && seated::gangwayCount(venue->layout) > GANGWAY_SLOTS) throw std::invalid_argument("CrowdMetrics: too many gangways");
    bindGangway_ = venue && venue->seated();
    if (const std::string why = gpuShortfall(gpuRequirements(programBindings(bindGangway_), bufferUses(numBoids, res_)), readGpuLimits()); !why.empty())
        throw std::runtime_error("CrowdMetrics: " + why);
    const std::vector<ProgramSpec> programs = programSpecs(shaderDir, res_, venue);
    depositProg_ = loadProgram(programs[0]);
    finalizeProg_ = loadProgram(programs[1]);
    locDepositNum_ = glGetUniformLocation(depositProg_, "numBoids");
    locDepositStep_ = glGetUniformLocation(depositProg_, "stepIndex");
    locFinalizeStep_ = glGetUniformLocation(finalizeProg_, "stepIndex");

    auto make = [](GLuint& b, GLsizeiptr bytes, const void* data, GLenum usage) {
        glGenBuffers(1, &b);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, b);
        glBufferData(GL_SHADER_STORAGE_BUFFER, bytes, data, usage);
    };
    // Written by the GL: CrowdSim's usage hint (VRAM at every size). The venue table is
    // written once by the CPU and only read by the GL.
    make(counters_, sizeof(GpuMetricCounters), nullptr, CrowdSim::SSBO_USAGE);
    make(evacStep_, GLsizeiptr(numBoids) * sizeof(uint32_t), nullptr, CrowdSim::SSBO_USAGE);
    const GLsizeiptr cells = GLsizeiptr(res_) * res_;
    make(mass_, cells * GLsizeiptr(sizeof(GpuMetricCellMass)), nullptr, CrowdSim::SSBO_USAGE);
    make(cells_, cells * GLsizeiptr(sizeof(GpuMetricCell)), nullptr, CrowdSim::SSBO_USAGE);
    make(info_, cells * GLsizeiptr(sizeof(GpuMetricCellInfo)), cellInfo.data(), GL_STATIC_DRAW);
    make(gangway_, GLsizeiptr(numBoids) * 16, nullptr, CrowdSim::SSBO_USAGE);   // read by seated venues' programs only
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    reset();
}

CrowdMetrics::~CrowdMetrics() {
    for (GLuint b : { counters_, evacStep_, mass_, info_, cells_, gangway_ }) glDeleteBuffers(1, &b);
    glDeleteProgram(depositProg_);
    glDeleteProgram(finalizeProg_);
}

void CrowdMetrics::reset() {
    const GLuint zero = 0;
    glMemoryBarrier(GL_BUFFER_UPDATE_BARRIER_BIT);   // after any pass that wrote them
    for (GLuint b : { counters_, evacStep_, mass_, cells_, gangway_ }) {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, b);
        glClearBufferData(GL_SHADER_STORAGE_BUFFER, GL_R32UI, GL_RED_INTEGER, GL_UNSIGNED_INT, &zero);
    }
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    steps_ = 0;
}

void CrowdMetrics::afterStep(const CrowdSim& sim) {
    if (sim.numBoids() != numBoids_) throw std::invalid_argument("CrowdMetrics::afterStep: agent count differs from the simulation's");
    record(sim.previousStateBuffer(), sim.currentStateBuffer());
}

void CrowdMetrics::record(GLuint prevState, GLuint curState) {
    ++steps_;
    glUseProgram(depositProg_);
    glUniform1i(locDepositNum_, numBoids_);
    glUniform1ui(locDepositStep_, steps_);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_BOIDS_IN, prevState);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_BOIDS_OUT, curState);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_METRIC_COUNTERS, counters_);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_METRIC_EVAC_STEP, evacStep_);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_METRIC_MASS, mass_);
    if (bindGangway_) glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_METRIC_GANGWAY, gangway_);
    glDispatchCompute(GLuint((numBoids_ + 255) / 256), 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

    glUseProgram(finalizeProg_);
    glUniform1ui(locFinalizeStep_, steps_);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_METRIC_CELL_INFO, info_);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_METRIC_CELLS, cells_);
    glDispatchCompute(GLuint(res_ * res_ / 256), 1, 1);
    // The next step's passes, and copies or readbacks of the counters (AsyncCounterReader), see the results
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_BUFFER_UPDATE_BARRIER_BIT);
}

namespace {
template <class T>
std::vector<T> readSsbo(GLuint buffer, size_t count) {
    glMemoryBarrier(GL_BUFFER_UPDATE_BARRIER_BIT);
    std::vector<T> out(count);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer);
    glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, GLsizeiptr(count * sizeof(T)), out.data());
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    return out;
}
} // namespace

GpuMetricCounters CrowdMetrics::readCounters() const { return readSsbo<GpuMetricCounters>(counters_, 1)[0]; }
std::vector<uint32_t> CrowdMetrics::readEvacSteps() const { return readSsbo<uint32_t>(evacStep_, size_t(numBoids_)); }
std::vector<GpuMetricCell> CrowdMetrics::readCells() const { return readSsbo<GpuMetricCell>(cells_, size_t(res_) * size_t(res_)); }

static_assert(CELLS % 256 == 0, "the finalize pass dispatches whole 256-wide groups");   // and every grid of a multiple of 16

// --- CPU reference ---
MetricsReference::MetricsReference(int numBoids, std::vector<GpuMetricCellInfo> cellInfo, const SeatedLayout* seated)
    : evacStep(size_t(numBoids), 0u), info_(std::move(cellInfo)), seated_(seated) {
    res_ = gridResOf(info_.size());
    cells.assign(info_.size(), GpuMetricCell{});
    gangway_.assign(size_t(numBoids), std::array<uint32_t, 3>{ 0u, 0u, 0u });
}

namespace {
void add64(uint32_t v[2], uint32_t b) {
    const uint64_t s = sum64(v) + b;
    v[0] = uint32_t(s);
    v[1] = uint32_t(s >> 32);
}
} // namespace

void MetricsReference::record(const std::vector<GpuBoid>& prev, const std::vector<GpuBoid>& cur) {
    if (prev.size() != evacStep.size() || cur.size() != evacStep.size()) throw std::invalid_argument("MetricsReference::record: state size");
    ++steps;
    std::vector<GpuMetricCellMass> mass(cells.size(), GpuMetricCellMass{});
    uint32_t active = 0;
    for (size_t i = 0; i < cur.size(); ++i) {
        const glm::vec4 p0 = prev[i].position, p1 = cur[i].position;
        if (p0.w != 0.0f && p1.w == 0.0f) {
            ++counters.exits[exitSlot(p0, seated_)];
            ++counters.evacuated;
            evacStep[i] = steps;
            if (seated_ && gangway_[i][2] != 0u) ++counters.gangwayLast[gangway_[i][2] - 1u];
        }
        if (p1.w != 0.0f) {
            ++active;
            if (seated_) {   // the gangway it stands on (metrics_deposit.comp)
                const int g = seated::gangwayAt(*seated_, glm::vec2(p1));
                if (g >= 0) {
                    const uint32_t bit = 1u << uint32_t(g & 31);
                    uint32_t& bits = gangway_[i][g < 32 ? 0 : 1];
                    if ((bits & bit) == 0u) ++counters.gangwayVisits[g];
                    bits |= bit;
                    gangway_[i][2] = uint32_t(g) + 1u;
                }
            }
            const CicDeposit d = cicDeposit(glm::vec2(p1), res_);
            const float s = horizontalSpeedMps(cur[i].velocity);
            for (int k = 0; k < 4; ++k) {
                if (d.weight[k] == 0) continue;
                mass[size_t(d.cell[k])].mass += d.weight[k];
                mass[size_t(d.cell[k])].speedMass += speedMass(d.weight[k], s);
            }
        }
    }
    counters.active = active;
    counters.activeAccum = 0;
    counters.step = steps;
    for (int c = 0; c < int(cells.size()); ++c) {
        const uint32_t m = mass[size_t(c)].mass, sm = mass[size_t(c)].speedMass;
        const GpuMetricCellInfo& in = info_[size_t(c)];
        GpuMetricCell& s = cells[size_t(c)];
        s.lastMass = m;
        s.lastSpeedMass = sm;
        s.peakMass = std::max(s.peakMass, m);
        s.occupiedSteps += m != 0;
        for (int k = 0; k < 4; ++k) s.stepsAbove[k] += m >= in.thresholdMass[k];
        add64(s.massSteps, m);
        add64(s.speedMassSteps, sm);
        if (m >= in.thresholdMass[CRUSH_INDEX]) add64(s.exposureMassSteps, m);
    }
}

} // namespace swarm::metrics
