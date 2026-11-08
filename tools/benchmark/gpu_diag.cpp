// gpu_diag: GPU diagnostics: correctness at every N, sort and physics scaling, buffer placement, the sort's byte-identity check.
//
//   gpu_diag correctness [--n 1024,4096,16384,65536,131072,262144] [--snapshots out/bench/snapshots] [--out out/results/diag]
//     For every N and state (spawn, congested), one CrowdSim::step with glGetError after every
//       dispatch (CrowdSim's dispatch hook), the dispatch geometry against GL_MAX_COMPUTE_WORK_GROUP_COUNT,
//       the sorted pairs (non-decreasing gridID, boidIDs a permutation of 0..N-1, every pair's gridID the
//       hash of its agent), the cell table and gridID sequence against CpuCrowdSim (counting; plus the
//       (gridID, boidID) sequence against the bitonic replay) and the single-step equivalence criteria of
//     test_gpu parity.one_step (|dpos| > 2e-4 for < 0.5% of active agents) for both CPU sort modes.
//
//   gpu_diag sort [--min 10] [--max 20] [--reps 10] [--warm 3] [--alloc dynamic_draw,...] [--no-variants]
//     bitonic_sort.comp alone on synthetic keys, N = 2^min .. 2^max, per-dispatch GL_TIMESTAMPs,
//       split into local (j < 256) and global (j >= 256) passes; ends-only, wall-clock and barrier variants.
//   gpu_diag bandwidth [--min 12] [--max 24] [--reps 20] [--alloc ...]
//     Reference kernels: streaming copy GB/s and one sort-like exchange pass vs buffer size and
//       allocation; empty-dispatch cost vs group count.
//   gpu_diag placement [--usage dynamic_draw,dynamic_copy,static_draw,stream_draw] [--sizes-mb ...]
//     Read/write GB/s of single buffers per usage hint and size (also after a CPU readback and an
//       upload), and of CrowdSim's own buffers at every N: where the driver places each buffer.
//   gpu_diag physics [--n ...] [--usage dynamic_draw,dynamic_copy] [--steps 100] [--warm-ms 1000]
//     Per-pass GPU ms in snapshot mode and physics ns per neighbour candidate vs N, per usage hint,
//       for the original agent order and for the agents relabelled in sorted order (memory locality).
//   gpu_diag timing [--n 65536,262144] [--usage ...] [--steps 100]
//     Snapshot restore and timer-query interference (ring / no restore / wall / per-dispatch stamps).
//   gpu_diag clock [--n 262144] [--seconds 30] [--iters 20000]
//     An ALU-bound probe kernel after every step, light load vs sustained long steps.
//   gpu_diag ab [--n ...] [--rounds 12] [--warm-ms 500] [--labels base:dynamic_draw,base_aa:dynamic_draw,new:dynamic_copy]
//     GL_DYNAMIC_DRAW (base, base_aa = A/A control) vs GL_DYNAMIC_COPY (new),
//       rotated order, median over rounds.
//   gpu_diag same [--n ...] [--steps 100]
//     FNV-1a of the state after 'steps' steps from spawn under GL_DYNAMIC_DRAW and GL_DYNAMIC_COPY, every N.
//   gpu_diag sortcheck [--min 10] [--max 20] [--no-cpu] [--out out/results/perf]
//     The proof: CrowdSim::sortGrid (shared-memory stages) against the same network as one global dispatch per
//       pass, byte for byte, synthetic and real keys, N = 2^min .. 2^max; real keys also against the step's grid and the
//       CPU bitonic replay.
//   gpu_diag sortlocal [--min 10] [--max 20] [--reps 20]
//     Prototype (CrowdSim does not use it): the same bitonic network with its j < 512 passes in
//       shared memory; output compared byte for byte with bitonic_sort.comp, synthetic keys and real hash output.
//
// Snapshots: <snapshots>/<state>_<n>.bin as benchmark_crowd writes them (spawn = spawnBleacherCrowd(n),
// congested = the GPU state after 250 steps); missing ones are generated the same way.
#include "bench_common.hpp"
#include "../golden_state.hpp"

#include <swarm/assets.hpp>
#include <swarm/cpu_crowd_sim.hpp>
#include <swarm/sdf.hpp>
#include <swarm/shader.hpp>
#include <swarm/venue_capacity.hpp>

#include <omp.h>

#include <cstdarg>
#include <functional>
#include <random>
#include <tuple>

namespace fs = std::filesystem;
using namespace swarm;
using bench::Args;
using bench::Clock;

namespace {

const std::vector<int> DEFAULT_NS = { 1024, 4096, 16384, 65536, 131072, 262144 };

// --- Output: everything printed also goes to the report file ---
class Report {
public:
    explicit Report(const fs::path& path) {
        fs::create_directories(path.parent_path());
        f_ = std::fopen(path.string().c_str(), "w");
        if (!f_) throw std::runtime_error("cannot write " + path.string());
    }
    ~Report() { if (f_) std::fclose(f_); }
    void operator()(const char* fmt, ...) {
        char buf[4096];
        va_list ap;
        va_start(ap, fmt);
        std::vsnprintf(buf, sizeof buf, fmt, ap);
        va_end(ap);
        std::fputs(buf, stdout);
        std::fputs(buf, f_);
        std::fflush(stdout);
        std::fflush(f_);
    }

private:
    std::FILE* f_ = nullptr;
};

std::string g_qos = "not set";

std::string header(const char* what) {
    char b[1024];
    std::snprintf(b, sizeof b, "gpu_diag %s | commit %s (dirty %s) | %s | GPU %s | %s | CPU %s | %s | %s\n", what,
                  bench::gitCommit().c_str(), bench::gitDirty().c_str(), SWARM_BUILD_TYPE,
                  bench::glRenderer().c_str(), bench::glDriver().c_str(), bench::cpuBrand().c_str(),
                  bench::localTimestamp("%Y-%m-%dT%H:%M:%S").c_str(), g_qos.c_str());
    return b;
}

// Snapshot as benchmark_crowd writes it; generated (and saved) when missing
std::vector<GpuBoid> snapshot(const fs::path& dir, const std::string& state, int n, const fs::path& shaderDir, GLuint sdfTex) {
    const fs::path path = bench::snapshotPath(dir, state, n);
    if (!fs::exists(path)) {
        fs::create_directories(dir);
        const std::vector<GpuBoid> spawn = spawnBleacherCrowd(n);
        if (!fs::exists(bench::snapshotPath(dir, "spawn", n))) bench::saveSnapshot(bench::snapshotPath(dir, "spawn", n), spawn);
        if (state == "congested") {
            std::printf("  generating %s (GPU, %d steps from spawn)\n", path.string().c_str(), bench::CONGESTED_STEPS);
            CrowdSim sim(shaderDir, n);
            sim.upload(spawn);
            for (int i = 0; i < bench::CONGESTED_STEPS; ++i) sim.step(sdfTex);
            bench::saveSnapshot(path, bench::readBuffer<GpuBoid>(sim.currentStateBuffer(), size_t(n)));
        }
    }
    return bench::loadSnapshot(dir, state, n);
}

const char* glErrorName(GLenum e) {
    switch (e) {
    case GL_NO_ERROR: return "GL_NO_ERROR";
    case GL_INVALID_ENUM: return "GL_INVALID_ENUM";
    case GL_INVALID_VALUE: return "GL_INVALID_VALUE";
    case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
    case GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY";
    case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
    default: return "GL error";
    }
}

// calc_grid.comp's cellID on the CPU (same float expression; the counting sort's gridIDs are compared too)
uint32_t hashCell(const GpuBoid& b) {
    if (b.position.w == 0.0f) return INACTIVE_CELL;
    const int x = std::clamp(int((b.position.x - DOMAIN_MIN) / DOMAIN_SPAN * float(GRID_RES)), 0, GRID_RES - 1);
    const int y = std::clamp(int((b.position.y - DOMAIN_MIN) / DOMAIN_SPAN * float(GRID_RES)), 0, GRID_RES - 1);
    return uint32_t(x + y * GRID_RES);
}

// Correctness at every size

struct DispatchRecord { std::string pass; GLuint groups = 0; int k = 0, j = 0, elems = 1; GLenum error = GL_NO_ERROR; GLint local[3] = {}; };

// Sort dispatches per step: one shared-memory tile sort, then per stage k > SORT_TILE its global
// passes j >= SORT_TILE and one shared-memory merge (without the shared stages: log2N (log2N + 1) / 2 global passes)
int expectedSortDispatches(int n) {
    int d = 1;
    for (int k = 2 * CrowdSim::SORT_TILE; k <= n; k <<= 1) {
        for (int j = k >> 1; j >= CrowdSim::SORT_TILE; j >>= 1) ++d;
        ++d;
    }
    return d;
}

struct EquivStats { long outliers = 0, flagDiff = 0; float p50 = 0, p99 = 0, max = 0; };

EquivStats equivalence(const std::vector<GpuBoid>& in, const std::vector<GpuBoid>& gpuOut, const std::vector<GpuBoid>& cpuOut) {
    EquivStats s;
    std::vector<float> d;
    for (size_t i = 0; i < in.size(); ++i) {
        if (in[i].position.w == 0.0f) continue;
        const float dp = glm::length(glm::vec3(cpuOut[i].position) - glm::vec3(gpuOut[i].position));
        d.push_back(dp);
        s.outliers += dp > 2e-4f;
        s.flagDiff += cpuOut[i].position.w != gpuOut[i].position.w;
    }
    std::sort(d.begin(), d.end());
    if (!d.empty()) {
        s.p50 = d[d.size() / 2];
        s.p99 = d[std::min(d.size() - 1, size_t(double(d.size()) * 0.99))];
        s.max = d.back();
    }
    return s;
}

int cmdCorrectness(const Args& a) {
    const std::vector<int> ns = a.has("n") ? bench::parseIntList(a.get("n", "")) : DEFAULT_NS;
    const fs::path snapDir = a.get("snapshots", "out/bench/snapshots");
    const fs::path outDir = a.get("out", "out/results/diag");

    bench::createHiddenContext("gpu_diag");
    const GLuint sdfTex = loadSDFTexture3D(resolveAsset("stadium.sdf"));
    const std::vector<float>& sdf = sdfVolumeCPU();
    if (!sdfTex || sdf.empty()) throw std::runtime_error("cannot load stadium.sdf");
    const fs::path shaderDir = resolveAsset("shaders");

    Report out(outDir / ("stage1_correctness_" + bench::localTimestamp("%Y%m%d_%H%M") + ".txt"));
    out("%s", header("correctness").c_str());
    GLint maxCount[3] = {}, maxSize[3] = {}, maxInvocations = 0;
    for (GLuint i = 0; i < 3; ++i) {
        glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, i, &maxCount[i]);
        glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, i, &maxSize[i]);
    }
    glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &maxInvocations);
    out("GL_MAX_COMPUTE_WORK_GROUP_COUNT = (%d, %d, %d), GL_MAX_COMPUTE_WORK_GROUP_SIZE = (%d, %d, %d), "
        "GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS = %d\n",
        maxCount[0], maxCount[1], maxCount[2], maxSize[0], maxSize[1], maxSize[2], maxInvocations);
    GLint maxSsboSize = 0;
    glGetIntegerv(GL_MAX_SHADER_STORAGE_BLOCK_SIZE, &maxSsboSize);
    out("GL_MAX_SHADER_STORAGE_BLOCK_SIZE = %d bytes; CPU reference at %d threads (OpenMP)\n\n", maxSsboSize, CpuCrowdSim::maxThreads());
    while (glGetError() != GL_NO_ERROR) {}

    bool allOk = true;
    std::vector<std::string> summary;
    for (int n : ns) {
        for (const char* state : { "spawn", "congested" }) {
            const std::vector<GpuBoid> in = snapshot(snapDir, state, n, shaderDir, sdfTex);
            const long active = bench::countActive(in);

            // --- GPU: one step with glGetError after every dispatch ---
            CrowdSim sim(shaderDir, n);
            sim.upload(in);
            const GLenum before = glGetError();
            std::vector<DispatchRecord> rec;
            sim.setDispatchHook([&](const CrowdSim::DispatchInfo& d) {
                DispatchRecord r;
                r.pass = d.pass;
                r.groups = d.groupsX;
                r.k = d.k;
                r.j = d.j;
                r.elems = d.elementsPerInvocation;
                r.error = glGetError();
                glGetProgramiv(d.program, GL_COMPUTE_WORK_GROUP_SIZE, r.local);
                rec.push_back(r);
            });
            sim.step(sdfTex);
            sim.setDispatchHook(nullptr);
            const std::vector<GpuBoid> gpuOut = bench::readBuffer<GpuBoid>(sim.currentStateBuffer(), size_t(n));
            const std::vector<GpuGridInfo> grid = bench::readBuffer<GpuGridInfo>(sim.gridBuffer(), size_t(n));
            const std::vector<GpuCellData> cells = bench::readBuffer<GpuCellData>(sim.cellBuffer(), size_t(GRID_RES) * GRID_RES);
            const GLenum after = glGetError();

            // Dispatch report (once per N)
            int log2n = 0;
            while ((1 << log2n) < n) ++log2n;
            const int expectSort = expectedSortDispatches(n);
            std::map<std::string, int> count;
            long errors = 0;
            bool geometryOk = true;
            for (const DispatchRecord& r : rec) {
                ++count[r.pass];
                errors += r.error != GL_NO_ERROR;
                if (r.error != GL_NO_ERROR) out("  ERROR after %s dispatch (k %d, j %d): %s\n", r.pass.c_str(), r.k, r.j, glErrorName(r.error));
                geometryOk &= r.groups >= 1 && GLint(r.groups) <= maxCount[0] && long(r.groups) * r.local[0] * r.elems == n && r.local[1] == 1 &&
                              r.local[2] == 1;
            }
            geometryOk &= count["hash"] == 1 && count["sort"] == expectSort && count["cells"] == 1 && count["physics"] == 1;
            if (std::string(state) == "spawn") {
                out("N = %d: dispatches per step (local size, groups x 1 x 1, invocations, GL_MAX_COMPUTE_WORK_GROUP_COUNT.x %d)\n", n, maxCount[0]);
                std::map<std::string, const DispatchRecord*> first;
                for (const DispatchRecord& r : rec) if (!first.count(r.pass)) first[r.pass] = &r;
                for (const char* p : { "hash", "sort", "cells", "physics" }) {
                    const DispatchRecord& r = *first[p];
                    out("    %-8s x%3d  local (%d, %d, %d)  groups %6u (%.3f%% of the limit)  invocations %8ld\n", p, count[p], r.local[0], r.local[1],
                        r.local[2], r.groups, 100.0 * double(r.groups) / double(maxCount[0]), long(r.groups) * r.local[0]);
                }
                out("    sort dispatches: %d expected (log2 N = %d; shared-memory stages; without them log2N (log2N + 1) / 2 = %d)\n",
                    expectSort, log2n, log2n * (log2n + 1) / 2);
            }

            // --- Sorted pairs ---
            long decreasing = 0, badBoidId = 0, dupBoidId = 0, wrongCell = 0;
            std::vector<char> seen(size_t(n), 0);
            for (int s = 0; s < n; ++s) {
                if (s > 0 && grid[s].gridID < grid[s - 1].gridID) ++decreasing;
                const uint32_t b = grid[s].boidID;
                if (b >= uint32_t(n)) { ++badBoidId; continue; }
                if (seen[b]++) ++dupBoidId;
                if (grid[s].gridID != hashCell(in[b])) ++wrongCell;
            }
            const long missing = long(std::count(seen.begin(), seen.end(), 0));
            const bool sortOk = decreasing == 0 && badBoidId == 0 && dupBoidId == 0 && missing == 0 && wrongCell == 0;

            // --- CPU reference: counting (gridID sequence, cell table) and bitonic replay (exact pairs) ---
            CpuCrowdSim counting(sdf, 0, CpuCrowdSim::SortMode::Counting), bitonic(sdf, 0, CpuCrowdSim::SortMode::GpuBitonic);
            counting.setState(in);
            counting.step();
            bitonic.setState(in);
            bitonic.step();
            long gridIdDiff = 0, cellDiff = 0, pairDiff = 0, bitonicCellDiff = 0;
            for (int s = 0; s < n; ++s) {
                gridIdDiff += counting.grid()[s].gridID != grid[s].gridID;
                pairDiff += bitonic.grid()[s].gridID != grid[s].gridID || bitonic.grid()[s].boidID != grid[s].boidID;
            }
            for (size_t c = 0; c < cells.size(); ++c) {
                cellDiff += counting.cells()[c].startIndex != cells[c].startIndex || counting.cells()[c].agentCount != cells[c].agentCount;
                bitonicCellDiff += bitonic.cells()[c].startIndex != cells[c].startIndex || bitonic.cells()[c].agentCount != cells[c].agentCount;
            }
            // Independent cell-table check: every non-empty cell's run in the sorted GPU array
            long cellRunDiff = 0;
            {
                std::vector<GpuCellData> own(cells.size(), GpuCellData{});
                for (int s = 0; s < n; ++s) {
                    const uint32_t g = grid[s].gridID;
                    if (g == INACTIVE_CELL || g >= own.size()) continue;
                    if (own[g].agentCount == 0) own[g].startIndex = uint32_t(s);
                    ++own[g].agentCount;
                }
                for (size_t c = 0; c < cells.size(); ++c)
                    cellRunDiff += own[c].agentCount != cells[c].agentCount || (own[c].agentCount && own[c].startIndex != cells[c].startIndex);
            }
            const bool tableOk = gridIdDiff == 0 && cellDiff == 0 && pairDiff == 0 && bitonicCellDiff == 0 && cellRunDiff == 0;

            const EquivStats ec = equivalence(in, gpuOut, counting.state()), eb = equivalence(in, gpuOut, bitonic.state());
            const bool equivOk = ec.outliers * 1000 < active * 5 && eb.outliers * 1000 < active * 5;
            const bool errOk = errors == 0 && before == GL_NO_ERROR && after == GL_NO_ERROR;
            const bool ok = errOk && geometryOk && sortOk && tableOk && equivOk;
            allOk &= ok;

            out("  N = %6d %-9s active %6ld | GL errors: %ld of %zu dispatches (before step %s, after readback %s) | geometry %s\n", n, state, active,
                errors, rec.size(), glErrorName(before), glErrorName(after), geometryOk ? "ok" : "BAD");
            out("    sorted pairs: gridID decreases %ld | boidID out of range %ld, duplicated %ld, missing %ld | pair gridID != hash(agent) %ld -> %s\n",
                decreasing, badBoidId, dupBoidId, missing, wrongCell, sortOk ? "ok" : "FAIL");
            out("    vs CPU counting: gridID slots != %ld, cells != %ld of %zu | vs CPU bitonic: (gridID, boidID) slots != %ld, cells != %ld | "
                "cell runs != own scan %ld -> %s\n",
                gridIdDiff, cellDiff, cells.size(), pairDiff, bitonicCellDiff, cellRunDiff, tableOk ? "ok" : "FAIL");
            out("    one step vs CPU: counting |dpos| p50 %.2e p99 %.2e max %.2e, > 2e-4: %ld (%.3f%%), w != %ld | bitonic > 2e-4: %ld (%.3f%%), "
                "w != %ld (limit < 0.5%%) -> %s\n",
                ec.p50, ec.p99, ec.max, ec.outliers, 100.0 * double(ec.outliers) / double(active), ec.flagDiff, eb.outliers,
                100.0 * double(eb.outliers) / double(active), eb.flagDiff, equivOk ? "ok" : "FAIL");
            out("    => %s\n", ok ? "PASS" : "FAIL");

            char line[512];
            std::snprintf(line, sizeof line, "| %d | %s | %ld | %ld / %zu | %s | %s | %s | %s | %ld (%.3f%%) | %ld (%.3f%%) | %ld / %ld | %s |", n, state,
                          active, errors, rec.size(), geometryOk ? "ok" : "BAD", sortOk ? "ok" : "FAIL",
                          (gridIdDiff == 0 && cellDiff == 0 && cellRunDiff == 0) ? "exact" : "DIFF", pairDiff == 0 && bitonicCellDiff == 0 ? "exact" : "DIFF",
                          ec.outliers, 100.0 * double(ec.outliers) / double(active), eb.outliers, 100.0 * double(eb.outliers) / double(active),
                          ec.flagDiff, eb.flagDiff, ok ? "PASS" : "FAIL");
            summary.push_back(line);
        }
        out("\n");
    }
    out("| N | state | active | GL errors / dispatches | geometry | sorted + permutation + hash | gridIDs + cells vs CPU counting | pairs + cells vs CPU bitonic "
        "| outliers counting | outliers bitonic | w != (c / b) | verdict |\n|---:|---|---:|---:|---|---|---|---|---:|---:|---:|---|\n");
    for (const std::string& s : summary) out("%s\n", s.c_str());
    out("\n%s\n", allOk ? "STAGE 1: ALL PASSED" : "STAGE 1: FAILURES (see above)");
    return allOk ? 0 : 1;
}

// Helpers: buffer allocation variants, inline compute programs, timestamp rings

// Buffer allocation variants. CrowdSim allocates every SSBO with glBufferData(nullptr, CrowdSim::SSBO_USAGE).
// 'storage' is glBufferStorage with no flags (immutable, GL 4.4 / ARB_buffer_storage; diagnosis only,
// the engine targets GL 4.3).
const std::vector<std::string> ALLOCS = { "dynamic_draw", "static_draw", "dynamic_copy", "stream_draw", "storage" };

PFNGLBUFFERSTORAGEPROC bufferStorageFn() {
    static PFNGLBUFFERSTORAGEPROC fn = glBufferStorage ? glBufferStorage : (PFNGLBUFFERSTORAGEPROC)glfwGetProcAddress("glBufferStorage");
    return fn;
}

GLuint makeBuffer(const std::string& alloc, GLsizeiptr bytes, const void* data = nullptr) {
    GLuint b = 0;
    glGenBuffers(1, &b);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, b);
    if (alloc == "storage") {
        PFNGLBUFFERSTORAGEPROC fn = bufferStorageFn();
        if (!fn) throw std::runtime_error("glBufferStorage unavailable");
        fn(GL_SHADER_STORAGE_BUFFER, bytes, data, 0);
    } else {
        const GLenum usage = alloc == "dynamic_draw" ? GL_DYNAMIC_DRAW : alloc == "static_draw" ? GL_STATIC_DRAW : alloc == "dynamic_copy" ? GL_DYNAMIC_COPY
                           : alloc == "stream_draw" ? GL_STREAM_DRAW : alloc == "static_copy" ? GL_STATIC_COPY : 0;
        if (!usage) throw std::runtime_error("unknown allocation " + alloc);
        glBufferData(GL_SHADER_STORAGE_BUFFER, bytes, data, usage);
    }
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    return b;
}

void copyBuffer(GLuint src, GLuint dst, GLsizeiptr bytes) {
    glMemoryBarrier(GL_BUFFER_UPDATE_BARRIER_BIT);
    glBindBuffer(GL_COPY_READ_BUFFER, src);
    glBindBuffer(GL_COPY_WRITE_BUFFER, dst);
    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, bytes);
    glMemoryBarrier(GL_ALL_BARRIER_BITS);
}

GLuint inlineProgram(const char* name, const std::string& body) {
    const std::string src = "#version 430 core\n" + body;
    const GLuint sh = glCreateShader(GL_COMPUTE_SHADER);
    const char* p = src.c_str();
    glShaderSource(sh, 1, &p, nullptr);
    glCompileShader(sh);
    GLint ok = 0;
    glGetShaderiv(sh, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[4096] = {};
        glGetShaderInfoLog(sh, sizeof log, nullptr, log);
        throw std::runtime_error(std::string(name) + ": " + log);
    }
    const GLuint prog = glCreateProgram();
    glAttachShader(prog, sh);
    glLinkProgram(prog);
    glDeleteShader(sh);
    glGetProgramiv(prog, GL_LINK_STATUS, &ok);
    if (!ok) throw std::runtime_error(std::string(name) + ": link failed");
    return prog;
}

// GL_TIMESTAMP ring, read back once after the measured loop
class Stamps {
public:
    explicit Stamps(size_t capacity) : q_(capacity) { glGenQueries(GLsizei(capacity), q_.data()); }
    ~Stamps() { glDeleteQueries(GLsizei(q_.size()), q_.data()); }
    Stamps(const Stamps&) = delete;
    Stamps& operator=(const Stamps&) = delete;
    void reset() { pos_ = 0; }
    void stamp() {
        if (pos_ >= q_.size()) throw std::runtime_error("Stamps: ring full");
        glQueryCounter(q_[pos_++], GL_TIMESTAMP);
    }
    size_t size() const { return pos_; }
    std::vector<double> readMs() const {   // ms since the first stamp
        std::vector<double> out(pos_);
        GLuint64 t0 = 0;
        for (size_t i = 0; i < pos_; ++i) {
            GLuint64 t = 0;
            glGetQueryObjectui64v(q_[i], GL_QUERY_RESULT, &t);
            if (i == 0) t0 = t;
            out[i] = double(t - t0) * 1e-6;
        }
        return out;
    }

private:
    std::vector<GLuint> q_;
    size_t pos_ = 0;
};

enum class BarrierMode { Ssbo, All, None };
void barrier(BarrierMode b) {
    if (b == BarrierMode::Ssbo) glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    else if (b == BarrierMode::All) glMemoryBarrier(GL_ALL_BARRIER_BITS);
}

// CrowdSim::step's sort loop (same shader, uniforms, 256-wide groups, SSBO barrier after every
// dispatch) on any buffer bound at BIND_GRID
struct SortRunner {
    GLuint prog = 0;
    GLint locJ = -1, locK = -1;
    explicit SortRunner(const fs::path& shaderDir) : prog(loadComputeProgram(shaderDir / "bitonic_sort.comp")) {
        locJ = glGetUniformLocation(prog, "j");
        locK = glGetUniformLocation(prog, "k");
    }
    ~SortRunner() { glDeleteProgram(prog); }
    void run(GLuint buf, int n, BarrierMode bm, Stamps* perDispatch) const {
        glUseProgram(prog);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_GRID, buf);
        for (int k = 2; k <= n; k <<= 1)
            for (int j = k >> 1; j > 0; j >>= 1) {
                glUniform1i(locJ, j);
                glUniform1i(locK, k);
                glDispatchCompute(GLuint(n / 256), 1, 1);
                barrier(bm);
                if (perDispatch) perDispatch->stamp();
            }
    }
};

std::vector<GpuGridInfo> randomKeys(int n, unsigned seed) {
    std::mt19937 gen(seed);
    std::uniform_int_distribution<uint32_t> cell(0, uint32_t(GRID_RES * GRID_RES - 1));
    std::vector<GpuGridInfo> keys(static_cast<size_t>(n));
    for (int i = 0; i < n; ++i) keys[size_t(i)] = { cell(gen), uint32_t(i), 0u, 0u };
    return keys;
}

bool sortedPermutation(const std::vector<GpuGridInfo>& g) {
    std::vector<char> seen(g.size(), 0);
    for (size_t s = 0; s < g.size(); ++s) {
        if (s > 0 && g[s].gridID < g[s - 1].gridID) return false;
        if (g[s].boidID >= g.size() || seen[g[s].boidID]++) return false;
    }
    return true;
}

double medianOf(std::vector<double> v) { return bench::median(std::move(v)); }

// The sort alone, synthetic random keys (uniform over the 1600 cells), N = 2^min .. 2^max
int cmdSort(const Args& a) {
    const int lo = a.getInt("min", 10), hi = a.getInt("max", 20), reps = a.getInt("reps", 10), warm = a.getInt("warm", 3);
    const std::vector<std::string> allocs = a.has("alloc") ? bench::parseList(a.get("alloc", "")) : ALLOCS;
    const fs::path outDir = a.get("out", "out/results/diag");
    const bool variants = !a.has("no-variants");

    bench::createHiddenContext("gpu_diag");
    const fs::path shaderDir = resolveAsset("shaders");
    const std::string stamp = bench::localTimestamp("%Y%m%d_%H%M");
    Report out(outDir / ("stage2a_sort_" + stamp + ".txt"));
    std::FILE* csv = std::fopen((outDir / ("stage2a_sort_" + stamp + ".csv")).string().c_str(), "w");
    if (!csv) throw std::runtime_error("cannot write the sort CSV");
    std::fprintf(csv, "alloc,N,dispatch,k,j,class,median_us,capacity_label\n");
    out("%s", header("sort").c_str());
    out("bitonic_sort.comp alone on synthetic keys (gridID uniform over the %d cells, boidID = index), the dispatch loop of CrowdSim::step.\n"
        "No pass of this sort uses shared memory: every (k, j) pass is one global-memory dispatch. 'local' = j < 256 (the partner lies\n"
        "in the same 256-wide work group), 'global' = j >= 256 (the partner lies in another group). Per-dispatch GL_TIMESTAMP after\n"
        "each dispatch + barrier; median over %d reps (after %d warm-up sorts), each rep from the same unsorted keys (GPU copy, untimed).\n"
        "ends = stamps only around the whole sort; wall = steady_clock over %d sorts with one glFinish, minus a copy-only batch;\n"
        "all/none = ends-only total with glMemoryBarrier(GL_ALL_BARRIER_BITS) / no barrier between passes (none: timing only).\n\n",
        GRID_RES * GRID_RES, reps, warm, reps);
    SortRunner sorter(shaderDir);
    for (const std::string& alloc : allocs) {
        out("allocation: %s\n", alloc.c_str());
        out("  %8s %5s %10s | %8s %8s %8s | %4s %9s %8s | %4s %9s %8s | %9s | %8s %8s | %s\n", "N", "MB", "dispatches", "total", "ends", "wall", "loc",
            "loc ms", "us/disp", "glob", "glob ms", "us/disp", "ns/elem", "all", "none", "sorted");
        for (int l = lo; l <= hi; ++l) {
            const int n = 1 << l;
            const GLsizeiptr bytes = GLsizeiptr(n) * GLsizeiptr(sizeof(GpuGridInfo));
            const std::vector<GpuGridInfo> keys = randomKeys(n, 4242u + unsigned(l));
            const GLuint pristine = makeBuffer("static_draw", bytes, keys.data());
            const GLuint buf = makeBuffer(alloc, bytes);
            const int d = l * (l + 1) / 2;
            for (int w = 0; w < warm; ++w) { copyBuffer(pristine, buf, bytes); sorter.run(buf, n, BarrierMode::Ssbo, nullptr); }
            glFinish();

            // Per-dispatch stamps
            Stamps st(size_t(reps) * size_t(d + 1));
            for (int r = 0; r < reps; ++r) {
                copyBuffer(pristine, buf, bytes);
                st.stamp();
                sorter.run(buf, n, BarrierMode::Ssbo, &st);
            }
            const std::vector<double> t = st.readMs();
            const bool sorted = sortedPermutation(bench::readBuffer<GpuGridInfo>(buf, size_t(n)));
            std::vector<std::vector<double>> per(static_cast<size_t>(d));
            std::vector<double> totals, locSums, globSums;
            std::vector<int> ks, js;
            for (int k = 2; k <= n; k <<= 1)
                for (int j = k >> 1; j > 0; j >>= 1) { ks.push_back(k); js.push_back(j); }
            for (int r = 0; r < reps; ++r) {
                const size_t base = size_t(r) * size_t(d + 1);
                totals.push_back(t[base + size_t(d)] - t[base]);
                double ls = 0, gs = 0;
                for (int i = 0; i < d; ++i) {
                    const double dt = t[base + size_t(i) + 1] - t[base + size_t(i)];
                    per[size_t(i)].push_back(dt);
                    (js[size_t(i)] < 256 ? ls : gs) += dt;
                }
                locSums.push_back(ls);
                globSums.push_back(gs);
            }
            int nLoc = 0, nGlob = 0;
            for (int i = 0; i < d; ++i) {
                const bool local = js[size_t(i)] < 256;
                (local ? nLoc : nGlob)++;
                std::fprintf(csv, "%s,%d,%d,%d,%d,%s,%.3f,%s\n", alloc.c_str(), n, i, ks[size_t(i)], js[size_t(i)], local ? "local" : "global",
                             1000.0 * medianOf(per[size_t(i)]), venue::label(n).c_str());
            }
            std::fflush(csv);

            // Ends-only stamps, barrier variants
            auto endsOnly = [&](BarrierMode bm) {
                Stamps e(size_t(reps) * 2);
                for (int r = 0; r < reps; ++r) {
                    copyBuffer(pristine, buf, bytes);
                    e.stamp();
                    sorter.run(buf, n, bm, nullptr);
                    e.stamp();
                }
                const std::vector<double> te = e.readMs();
                std::vector<double> v;
                for (int r = 0; r < reps; ++r) v.push_back(te[size_t(2 * r + 1)] - te[size_t(2 * r)]);
                return medianOf(v);
            };
            const double ends = endsOnly(BarrierMode::Ssbo);
            const double all = variants ? endsOnly(BarrierMode::All) : 0.0;
            const double none = variants ? endsOnly(BarrierMode::None) : 0.0;

            // Wall clock: copies + sorts, minus copies only
            glFinish();
            auto t0 = Clock::now();
            for (int r = 0; r < reps; ++r) { copyBuffer(pristine, buf, bytes); sorter.run(buf, n, BarrierMode::Ssbo, nullptr); }
            glFinish();
            const double withSort = bench::msSince(t0);
            t0 = Clock::now();
            for (int r = 0; r < reps; ++r) copyBuffer(pristine, buf, bytes);
            glFinish();
            const double wall = (withSort - bench::msSince(t0)) / reps;

            const double total = medianOf(totals), locMs = medianOf(locSums), globMs = medianOf(globSums);
            out("  %8d %5.2f %4d=%2d+%-3d | %8.4f %8.4f %8.4f | %4d %9.4f %8.3f | %4d %9.4f %8.3f | %9.4f | %8.4f %8.4f | %s\n", n,
                double(bytes) / 1048576.0, d, nLoc, nGlob, total, ends, wall, nLoc, locMs, 1000.0 * locMs / nLoc, nGlob, globMs,
                nGlob ? 1000.0 * globMs / nGlob : 0.0, 1e6 * total / double(d) / double(n), all, none, sorted ? "ok" : "NOT SORTED");
            glDeleteBuffers(1, &buf);
            glDeleteBuffers(1, &pristine);
        }
        out("\n");
    }
    std::fclose(csv);
    return 0;
}

// Reference kernels: streaming copy bandwidth vs buffer size, empty-dispatch cost vs group count
int cmdBandwidth(const Args& a) {
    const int lo = a.getInt("min", 12), hi = a.getInt("max", 24), reps = a.getInt("reps", 20);
    const std::vector<std::string> allocs = a.has("alloc") ? bench::parseList(a.get("alloc", "")) : ALLOCS;
    const fs::path outDir = a.get("out", "out/results/diag");
    bench::createHiddenContext("gpu_diag");
    Report out(outDir / ("stage2c_bandwidth_" + bench::localTimestamp("%Y%m%d_%H%M") + ".txt"));
    out("%s", header("bandwidth (reference kernels)").c_str());
    const GLuint copyProg = inlineProgram("copy", R"GLSL(
layout(local_size_x = 256) in;
layout(std430, binding = 0) readonly buffer A { uvec4 a[]; };
layout(std430, binding = 1) writeonly buffer B { uvec4 b[]; };
uniform uint n;
void main() { uint i = gl_GlobalInvocationID.x; if (i < n) b[i] = a[i]; }
)GLSL");
    // The sort's access pattern without its data dependence: element i and i ^ j, both read and written
    const GLuint pairProg = inlineProgram("pair", R"GLSL(
layout(local_size_x = 256) in;
layout(std430, binding = 1) buffer G { uvec4 g[]; };
uniform uint j;
void main() { uint id = gl_GlobalInvocationID.x; uint p = id ^ j; if (p > id) { uvec4 x = g[id]; g[id] = g[p] + 1u; g[p] = x; } }
)GLSL");
    const GLuint nullProg = inlineProgram("null", R"GLSL(
layout(local_size_x = 256) in;
layout(std430, binding = 0) buffer A { uint a[]; };
void main() { if (gl_GlobalInvocationID.x == 0xFFFFFFFFu) a[0] = 1u; }
)GLSL");
    out("copy: out[i] = in[i] (uvec4), GB/s = 2 x bytes / GPU time (median of %d); pair: one sort-like exchange pass (i <-> i ^ j,\n"
        "j = N/2 and j = 1, read + write both), us per pass\n", reps);
    for (const std::string& alloc : allocs) {
        out("allocation: %s\n  %10s %9s | %9s %8s | %10s %10s\n", alloc.c_str(), "elements", "MB", "copy ms", "GB/s", "pair j=N/2", "pair j=1");
        for (int l = lo; l <= hi; ++l) {
            const int n = 1 << l;
            const GLsizeiptr bytes = GLsizeiptr(n) * 16;
            const GLuint src = makeBuffer(alloc, bytes), dst = makeBuffer(alloc, bytes);
            const GLuint zero = 0;
            for (GLuint b : { src, dst }) {
                glBindBuffer(GL_SHADER_STORAGE_BUFFER, b);
                glClearBufferData(GL_SHADER_STORAGE_BUFFER, GL_R32UI, GL_RED_INTEGER, GL_UNSIGNED_INT, &zero);
            }
            glMemoryBarrier(GL_ALL_BARRIER_BITS);
            auto timeIt = [&](auto&& dispatch) {
                for (int w = 0; w < 3; ++w) dispatch();
                Stamps s(size_t(reps) * 2);
                for (int r = 0; r < reps; ++r) { s.stamp(); dispatch(); s.stamp(); }
                const std::vector<double> t = s.readMs();
                std::vector<double> v;
                for (int r = 0; r < reps; ++r) v.push_back(t[size_t(2 * r + 1)] - t[size_t(2 * r)]);
                return medianOf(v);
            };
            const double copyMs = timeIt([&] {
                glUseProgram(copyProg);
                glUniform1ui(glGetUniformLocation(copyProg, "n"), GLuint(n));
                glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, src);
                glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, dst);
                glDispatchCompute(GLuint((n + 255) / 256), 1, 1);
                glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
            });
            auto pair = [&](int j) {
                return timeIt([&] {
                    glUseProgram(pairProg);
                    glUniform1ui(glGetUniformLocation(pairProg, "j"), GLuint(j));
                    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, dst);
                    glDispatchCompute(GLuint((n + 255) / 256), 1, 1);
                    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
                });
            };
            const double pairHi = pair(n / 2), pairLo = pair(1);
            out("  %10d %9.3f | %9.4f %8.1f | %10.2f %10.2f\n", n, double(bytes) / 1048576.0, copyMs, 2.0 * double(bytes) / (copyMs * 1e6), 1000.0 * pairHi,
                1000.0 * pairLo);
            glDeleteBuffers(1, &src);
            glDeleteBuffers(1, &dst);
        }
    }
    // Empty dispatches: cost vs group count (dispatch + SSBO barrier, 100 per sample)
    out("\nempty dispatch + SSBO barrier, us per dispatch (median of %d samples of 100 dispatches)\n  %8s %10s\n", reps, "groups", "us");
    const GLuint dummy = makeBuffer("dynamic_draw", 16);
    for (int groups : { 1, 4, 16, 64, 256, 512, 1024, 2048, 4096, 16384, 65536 }) {
        glUseProgram(nullProg);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, dummy);
        Stamps s(size_t(reps) * 2);
        for (int r = 0; r < reps; ++r) {
            s.stamp();
            for (int i = 0; i < 100; ++i) { glDispatchCompute(GLuint(groups), 1, 1); glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT); }
            s.stamp();
        }
        const std::vector<double> t = s.readMs();
        std::vector<double> v;
        for (int r = 0; r < reps; ++r) v.push_back((t[size_t(2 * r + 1)] - t[size_t(2 * r)]) * 10.0);   // us per dispatch
        out("  %8d %10.3f\n", groups, medianOf(v));
    }
    return 0;
}

// Buffer placement: read / write bandwidth of single buffers and of CrowdSim's own buffers

GLenum usageOf(const std::string& name) {
    if (name == "dynamic_draw") return GL_DYNAMIC_DRAW;
    if (name == "dynamic_copy") return GL_DYNAMIC_COPY;
    if (name == "static_draw") return GL_STATIC_DRAW;
    if (name == "stream_draw") return GL_STREAM_DRAW;
    throw std::runtime_error("unknown usage " + name);
}

// Bandwidth probes: every uvec4 of a buffer read once (no write unless a sentinel matches), or written once
struct Probes {
    GLuint readProg = 0, writeProg = 0, sink = 0;
    Probes() {
        readProg = inlineProgram("read", R"GLSL(
layout(local_size_x = 256) in;
layout(std430, binding = 0) readonly buffer A { uvec4 a[]; };
layout(std430, binding = 1) buffer O { uint o[]; };
uniform uint n;
void main() { uint i = gl_GlobalInvocationID.x; if (i < n) { uvec4 v = a[i]; if ((v.x ^ v.y ^ v.z ^ v.w) == 0x7FBADA55u) o[0] = i; } }
)GLSL");
        writeProg = inlineProgram("write", R"GLSL(
layout(local_size_x = 256) in;
layout(std430, binding = 0) writeonly buffer A { uvec4 a[]; };
uniform uint n;
void main() { uint i = gl_GlobalInvocationID.x; if (i < n) a[i] = uvec4(i); }
)GLSL");
        sink = makeBuffer("dynamic_copy", 16);
    }
    ~Probes() { glDeleteProgram(readProg); glDeleteProgram(writeProg); glDeleteBuffers(1, &sink); }
    // Median GPU ms of one pass over 'bytes' (a multiple of 16) of 'buf'
    double time(GLuint buf, GLsizeiptr bytes, bool write, int reps = 15) const {
        const GLuint prog = write ? writeProg : readProg;
        const GLuint n = GLuint(bytes / 16);
        auto pass = [&] {
            glUseProgram(prog);
            glUniform1ui(glGetUniformLocation(prog, "n"), n);
            glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, buf);
            glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, sink);
            glDispatchCompute((n + 255) / 256, 1, 1);
            glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
        };
        for (int w = 0; w < 3; ++w) pass();
        Stamps s(size_t(reps) * 2);
        for (int r = 0; r < reps; ++r) { s.stamp(); pass(); s.stamp(); }
        const std::vector<double> t = s.readMs();
        std::vector<double> v;
        for (int r = 0; r < reps; ++r) v.push_back(t[size_t(2 * r + 1)] - t[size_t(2 * r)]);
        return medianOf(v);
    }
    double readGBs(GLuint buf, GLsizeiptr bytes) const { return double(bytes) / (time(buf, bytes, false) * 1e6); }
};

int cmdPlacement(const Args& a) {
    const fs::path outDir = a.get("out", "out/results/diag");
    const std::vector<std::string> usages = bench::parseList(a.get("usage", "dynamic_draw,dynamic_copy,static_draw,stream_draw"));
    std::vector<double> sizesMb;
    for (const std::string& s : bench::parseList(a.get("sizes-mb", "0.5,1,1.5,1.75,1.9375,2,2.0625,2.25,2.5,3,4,8,16,24,32,48,64")))
        sizesMb.push_back(std::stod(s));

    bench::createHiddenContext("gpu_diag");
    const GLuint sdfTex = loadSDFTexture3D(resolveAsset("stadium.sdf"));
    if (!sdfTex) throw std::runtime_error("cannot load stadium.sdf");
    const fs::path shaderDir = resolveAsset("shaders");
    Report out(outDir / ("stage2c_placement_" + bench::localTimestamp("%Y%m%d_%H%M") + ".txt"));
    out("%s", header("placement (where the driver puts each buffer)").c_str());
    const Probes probes;

    out("A. One buffer at a time, glBufferData(nullptr, usage), cleared on the GPU. GB/s of one compute pass that reads (or writes)\n"
        "   every 16 bytes once (median of 15). 'after readback' = after glGetBufferSubData of the whole buffer; 'after upload' = after\n"
        "   glBufferSubData of the whole buffer (what CrowdSim::upload does). VRAM / Infinity Cache reads run at 500-1500 GB/s at these\n"
        "   sizes, host memory over PCIe 4.0 x16 at ~17-25 GB/s.\n");
    for (const std::string& u : usages) {
        out("  usage %s\n    %9s | %9s %9s | %14s %13s\n", u.c_str(), "MB", "read GB/s", "write GB/s", "after readback", "after upload");
        for (double mb : sizesMb) {
            const GLsizeiptr bytes = GLsizeiptr(mb * 1048576.0) / 16 * 16;
            GLuint b = 0;
            glGenBuffers(1, &b);
            glBindBuffer(GL_SHADER_STORAGE_BUFFER, b);
            glBufferData(GL_SHADER_STORAGE_BUFFER, bytes, nullptr, usageOf(u));
            const GLuint zero = 0;
            glClearBufferData(GL_SHADER_STORAGE_BUFFER, GL_R32UI, GL_RED_INTEGER, GL_UNSIGNED_INT, &zero);
            glMemoryBarrier(GL_ALL_BARRIER_BITS);
            const double rd = probes.readGBs(b, bytes);
            const double wr = double(bytes) / (probes.time(b, bytes, true) * 1e6);
            std::vector<char> host(static_cast<size_t>(bytes));
            glMemoryBarrier(GL_BUFFER_UPDATE_BARRIER_BIT);
            glBindBuffer(GL_SHADER_STORAGE_BUFFER, b);
            glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, bytes, host.data());
            const double rdAfterRead = probes.readGBs(b, bytes);
            glBindBuffer(GL_SHADER_STORAGE_BUFFER, b);
            glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, bytes, host.data());
            const double rdAfterUpload = probes.readGBs(b, bytes);
            out("    %9.4f | %9.1f %9.1f | %14.1f %13.1f\n", mb, rd, wr, rdAfterRead, rdAfterUpload);
            glDeleteBuffers(1, &b);
        }
    }

    // C. Access types: the hash pass writes 8 of every 16 bytes, the cells pass does atomics on a 25 KB buffer
    {
        const GLuint partialProg = inlineProgram("partial", R"GLSL(
layout(local_size_x = 256) in;
layout(std430, binding = 0) buffer A { uvec4 a[]; };
uniform uint n;
void main() { uint i = gl_GlobalInvocationID.x; if (i < n) a[i].xy = uvec2(i, i + 1u); }
)GLSL");
        const GLuint atomicProg = inlineProgram("atomic", R"GLSL(
layout(local_size_x = 256) in;
layout(std430, binding = 0) buffer A { uvec4 a[]; };
uniform uint n;
void main() { atomicAdd(a[gl_GlobalInvocationID.x % n].y, 1u); }
)GLSL");
        auto timeProg = [&](GLuint prog, GLuint buf, GLuint n, GLuint groups) {
            auto pass = [&] {
                glUseProgram(prog);
                glUniform1ui(glGetUniformLocation(prog, "n"), n);
                glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, buf);
                glDispatchCompute(groups, 1, 1);
                glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
            };
            for (int w = 0; w < 3; ++w) pass();
            Stamps st(30);
            for (int r = 0; r < 15; ++r) { st.stamp(); pass(); st.stamp(); }
            const std::vector<double> t = st.readMs();
            std::vector<double> v;
            for (int r = 0; r < 15; ++r) v.push_back(t[size_t(2 * r + 1)] - t[size_t(2 * r)]);
            return 1000.0 * medianOf(v);
        };
        out("\nC. Access types per usage and size, us per pass (median of 15): read, full write (16 of 16 bytes), partial write\n"
            "   (8 of 16 bytes, as calc_grid.comp writes the grid), and 65536 atomicAdds over the buffer's first min(1600, size/16)\n"
            "   uvec4 (as reorder.comp counts into the 1600-cell table)\n");
        out("  %-13s %9s | %9s %9s %9s %9s\n", "usage", "MB", "read", "write", "partial", "atomic");
        for (const std::string& u : usages) {
            for (double mb : { 0.0244140625, 0.25, 1.0, 2.0, 3.0, 4.0, 8.0 }) {
                const GLsizeiptr bytes = GLsizeiptr(mb * 1048576.0) / 16 * 16;
                const GLuint n = GLuint(bytes / 16);
                GLuint b = 0;
                glGenBuffers(1, &b);
                glBindBuffer(GL_SHADER_STORAGE_BUFFER, b);
                glBufferData(GL_SHADER_STORAGE_BUFFER, bytes, nullptr, usageOf(u));
                const GLuint zero = 0;
                glClearBufferData(GL_SHADER_STORAGE_BUFFER, GL_R32UI, GL_RED_INTEGER, GL_UNSIGNED_INT, &zero);
                glMemoryBarrier(GL_ALL_BARRIER_BITS);
                out("  %-13s %9.4f | %9.2f %9.2f %9.2f %9.2f\n", u.c_str(), mb, 1000.0 * probes.time(b, bytes, false), 1000.0 * probes.time(b, bytes, true),
                    timeProg(partialProg, b, n, (n + 255) / 256), timeProg(atomicProg, b, std::min<GLuint>(n, 1600), 65536 / 256));
                glDeleteBuffers(1, &b);
            }
        }
        glDeleteProgram(partialProg);
        glDeleteProgram(atomicProg);
    }

    out("\nB. CrowdSim's own buffers (upload of the spawn state, one step): read GB/s of each\n");
    out("  %-13s %7s | %9s %9s | %9s %9s | %9s %9s | %9s %9s\n", "usage", "N", "boids[0]", "MB", "boids[1]", "MB", "grid", "MB", "cells", "KB");
    for (const std::string& u : { std::string("dynamic_draw"), std::string("dynamic_copy") }) {
        for (int n : DEFAULT_NS) {
            CrowdSim sim(shaderDir, n, usageOf(u));
            sim.upload(spawnBleacherCrowd(n));
            sim.step(sdfTex);
            glFinish();
            const GLsizeiptr boidBytes = GLsizeiptr(n) * GLsizeiptr(sizeof(GpuBoid)), gridBytes = GLsizeiptr(n) * GLsizeiptr(sizeof(GpuGridInfo)),
                             cellBytes = GLsizeiptr(GRID_RES * GRID_RES) * GLsizeiptr(sizeof(GpuCellData));
            out("  %-13s %7d | %9.1f %9.2f | %9.1f %9.2f | %9.1f %9.2f | %9.1f %9.1f\n", u.c_str(), n, probes.readGBs(sim.boidBuffer(0), boidBytes),
                double(boidBytes) / 1048576.0, probes.readGBs(sim.boidBuffer(1), boidBytes), double(boidBytes) / 1048576.0,
                probes.readGBs(sim.gridBuffer(), gridBytes), double(gridBytes) / 1048576.0, probes.readGBs(sim.cellBuffer(), cellBytes),
                double(cellBytes) / 1024.0);
        }
    }
    return 0;
}

// Timed CrowdSim steps in snapshot mode (as benchmark_crowd: GPU-side restore of the snapshot into both
// ping-pong halves before every step, outside the timestamps)

struct Pristine {
    GLuint buf = 0;
    GLsizeiptr bytes = 0;
    explicit Pristine(const std::vector<GpuBoid>& s) : bytes(GLsizeiptr(s.size() * sizeof(GpuBoid))) {
        glGenBuffers(1, &buf);
        glBindBuffer(GL_COPY_READ_BUFFER, buf);
        glBufferData(GL_COPY_READ_BUFFER, bytes, s.data(), GL_STATIC_DRAW);
    }
    ~Pristine() { glDeleteBuffers(1, &buf); }
    void restore(const CrowdSim& sim) const {
        for (int i = 0; i < 2; ++i) {
            glMemoryBarrier(GL_BUFFER_UPDATE_BARRIER_BIT);
            glBindBuffer(GL_COPY_READ_BUFFER, buf);
            glBindBuffer(GL_COPY_WRITE_BUFFER, sim.boidBuffer(i));
            glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, bytes);
        }
    }
};

struct PassMedians { double hash = 0, sort = 0, cells = 0, physics = 0, total = 0; int steps = 0; };

PassMedians medians(const std::vector<CrowdSim::PassTimesMs>& t) {
    std::vector<double> h, s, c, p, tot;
    for (const CrowdSim::PassTimesMs& x : t) { h.push_back(x.hash); s.push_back(x.sort); c.push_back(x.cells); p.push_back(x.physics); tot.push_back(x.total); }
    return { medianOf(h), medianOf(s), medianOf(c), medianOf(p), medianOf(tot), int(t.size()) };
}

// Warm-up (>= warmMs and >= 10 steps), then 'steps' timed steps, each from the restored snapshot
PassMedians timedSnapshotSteps(CrowdSim& sim, const Pristine& p, GLuint sdfTex, int steps, double warmMs) {
    const auto t0 = Clock::now();
    for (int i = 0; i < 10 || bench::msSince(t0) < warmMs; ++i) {
        p.restore(sim);
        sim.step(sdfTex);
        if (i % 20 == 19) glFinish();
    }
    glFinish();
    sim.beginTimingRing(steps);
    for (int i = 0; i < steps; ++i) { p.restore(sim); sim.step(sdfTex); }
    return medians(sim.readTimingRing());
}

int stepsFor(int n, int base) { return n >= 262144 ? std::max(10, base / 5) : n >= 131072 ? std::max(10, base / 2) : base; }

// Physics GPU time per neighbour candidate vs N
struct Workload { long active = 0, looping = 0; double candidates = 0, neighbours = 0; };

// The physics loop's trip counts from the sorted pairs and cell table of the input state: every slot
// that reaches the 3x3 ring (active, not exiting this step) visits all agents of the ring's cells but
// itself ('candidates'); 'neighbours' passes the 3D R_PERC test
Workload workload(const std::vector<GpuBoid>& in, const std::vector<GpuGridInfo>& grid, const std::vector<GpuCellData>& cells) {
    Workload w;
    const int n = int(grid.size());
    double cand = 0, nb = 0;
    long active = 0, looping = 0;
#pragma omp parallel for schedule(dynamic, 256) reduction(+ : cand, nb, active, looping)
    for (int s = 0; s < n; ++s) {
        const uint32_t cid = grid[size_t(s)].gridID;
        if (cid == INACTIVE_CELL) continue;
        ++active;
        const GpuBoid& self = in[grid[size_t(s)].boidID];
        const float ax = std::fabs(self.position.x), ay = std::fabs(self.position.y);
        if ((std::max(ax, ay) > EXIT_DEPTH && self.position.z < EXIT_MAX_Z) || std::max(ax, ay) > DOMAIN_MAX) continue;
        ++looping;
        const int cx = int(cid % uint32_t(GRID_RES)), cy = int(cid / uint32_t(GRID_RES));
        for (int y = -1; y <= 1; ++y)
            for (int x = -1; x <= 1; ++x) {
                const int nx = cx + x, ny = cy + y;
                if (nx < 0 || nx >= GRID_RES || ny < 0 || ny >= GRID_RES) continue;
                const GpuCellData& c = cells[size_t(nx + ny * GRID_RES)];
                for (uint32_t k = c.startIndex; k < c.startIndex + c.agentCount; ++k) {
                    if (k == uint32_t(s)) continue;
                    cand += 1;
                    const glm::vec3 d = glm::vec3(self.position) - glm::vec3(in[grid[k].boidID].position);
                    nb += glm::dot(d, d) < R_PERC * R_PERC;
                }
            }
    }
    w.active = active;
    w.looping = looping;
    w.candidates = cand;
    w.neighbours = nb;
    return w;
}

int cmdPhysics(const Args& a) {
    const std::vector<int> ns = a.has("n") ? bench::parseIntList(a.get("n", "")) : DEFAULT_NS;
    const std::vector<std::string> usages = bench::parseList(a.get("usage", "dynamic_draw,dynamic_copy"));
    const int baseSteps = a.getInt("steps", 100);
    const double warmMs = a.getInt("warm-ms", 1000);
    const fs::path snapDir = a.get("snapshots", "out/bench/snapshots");
    const fs::path outDir = a.get("out", "out/results/diag");

    bench::createHiddenContext("gpu_diag");
    const GLuint sdfTex = loadSDFTexture3D(resolveAsset("stadium.sdf"));
    if (!sdfTex) throw std::runtime_error("cannot load stadium.sdf");
    const fs::path shaderDir = resolveAsset("shaders");
    const std::string stamp = bench::localTimestamp("%Y%m%d_%H%M");
    Report out(outDir / ("stage2b_physics_" + stamp + ".txt"));
    std::FILE* csv = std::fopen((outDir / ("stage2b_physics_" + stamp + ".csv")).string().c_str(), "w");
    if (!csv) throw std::runtime_error("cannot write the physics CSV");
    std::fprintf(csv, "usage,layout,N,state,active,looping,candidates,neighbours,steps,hash_ms,sort_ms,cells_ms,physics_ms,total_ms,ns_per_candidate,capacity_label\n");
    out("%s", header("physics").c_str());
    out("Snapshot mode as benchmark_crowd (restore before every step, outside the timestamps); GPU-execution ms, median over the\n"
        "measured steps (%d; N = 131072: %d, N = 262144: %d) after >= %.0f ms of warm-up. candidates = the physics loop's trip count\n"
        "(agents in the 3x3 ring but itself, summed over the slots that reach the loop), from the GPU's sorted pairs and cell table.\n"
        "layout 'sorted' = the same agents relabelled in the sorted-pair order (agent i = slot i), so the neighbour gathers read\n"
        "nearly contiguous memory: same positions, same trip counts, different memory locality (timing only, not the golden state).\n\n",
        baseSteps, stepsFor(131072, baseSteps), stepsFor(262144, baseSteps), warmMs);
    out("  %-12s %-8s %7s %-9s %7s %10s %8s | %8s %8s %8s %9s %9s | %8s\n", "usage", "layout", "N", "state", "active", "cand (M)", "cand/ag", "hash",
        "sort", "cells", "physics", "total", "ns/cand");
    for (int n : ns) {
        for (const char* state : { "spawn", "congested" }) {
            const std::vector<GpuBoid> in = snapshot(snapDir, state, n, shaderDir, sdfTex);
            // Sorted pairs and cell table of this input (identical for every usage), and the relabelled layout
            std::vector<GpuGridInfo> grid;
            std::vector<GpuCellData> cells;
            {
                CrowdSim sim(shaderDir, n, GL_DYNAMIC_COPY);
                sim.upload(in);
                sim.step(sdfTex);
                grid = bench::readBuffer<GpuGridInfo>(sim.gridBuffer(), size_t(n));
                cells = bench::readBuffer<GpuCellData>(sim.cellBuffer(), size_t(GRID_RES) * GRID_RES);
            }
            const Workload w = workload(in, grid, cells);
            std::vector<GpuBoid> sorted(in.size());
            for (int s = 0; s < n; ++s) sorted[size_t(s)] = in[grid[size_t(s)].boidID];
            for (const std::string& u : usages) {
                for (const char* layout : { "original", "sorted" }) {
                    CrowdSim sim(shaderDir, n, usageOf(u));
                    const Pristine p(std::string(layout) == "original" ? in : sorted);
                    const PassMedians m = timedSnapshotSteps(sim, p, sdfTex, stepsFor(n, baseSteps), warmMs);
                    const double nsPerCand = w.candidates > 0 ? m.physics * 1e6 / w.candidates : 0.0;
                    out("  %-12s %-8s %7d %-9s %7ld %10.2f %8.1f | %8.4f %8.4f %8.4f %9.4f %9.4f | %8.4f\n", u.c_str(), layout, n, state, w.active,
                        w.candidates / 1e6, w.candidates / double(std::max(1L, w.looping)), m.hash, m.sort, m.cells, m.physics, m.total, nsPerCand);
                    std::fprintf(csv, "%s,%s,%d,%s,%ld,%ld,%.0f,%.0f,%d,%.5f,%.5f,%.5f,%.5f,%.5f,%.6f,%s\n", u.c_str(), layout, n, state, w.active, w.looping,
                                 w.candidates, w.neighbours, m.steps, m.hash, m.sort, m.cells, m.physics, m.total, nsPerCand, venue::label(n).c_str());
                    std::fflush(csv);
                }
            }
        }
    }
    std::fclose(csv);
    return 0;
}

// Snapshot restore and timer-query interference
int cmdTiming(const Args& a) {
    const std::vector<int> ns = a.has("n") ? bench::parseIntList(a.get("n", "")) : std::vector<int>{ 65536, 262144 };
    const std::vector<std::string> usages = bench::parseList(a.get("usage", "dynamic_draw,dynamic_copy"));
    const int baseSteps = a.getInt("steps", 100);
    const fs::path snapDir = a.get("snapshots", "out/bench/snapshots");
    const fs::path outDir = a.get("out", "out/results/diag");

    bench::createHiddenContext("gpu_diag");
    const GLuint sdfTex = loadSDFTexture3D(resolveAsset("stadium.sdf"));
    if (!sdfTex) throw std::runtime_error("cannot load stadium.sdf");
    const fs::path shaderDir = resolveAsset("shaders");
    Report out(outDir / ("stage2c_timing_" + bench::localTimestamp("%Y%m%d_%H%M") + ".txt"));
    out("%s", header("timing (snapshot restore and timer-query interference)").c_str());
    out("Congested snapshot. ms per step, median (stamps) or mean (wall) over the measured steps after >= 1 s of warm-up:\n"
        "  A ring:      restore + step, 5 GL_TIMESTAMPs per step (benchmark_crowd's configuration), GPU total\n"
        "  B ring, no restore: continuous stepping from the snapshot, 5 stamps per step, GPU total\n"
        "  C wall:      restore + step, no queries; steady_clock over the batch (one glFinish) minus a restore-only batch\n"
        "  D wall, no restore: continuous stepping, no queries, steady_clock over the batch\n"
        "  E per-dispatch: restore + step, a GL_TIMESTAMP after every dispatch (dispatch hook), GPU total and per-pass sums;\n"
        "                  sort us/dispatch = median sort dispatch\n\n");
    out("  %-12s %7s %6s | %9s %9s %9s %9s %9s | %9s %9s %9s %9s %10s\n", "usage", "N", "steps", "A ring", "B norest", "C wall", "D wall nr", "E perdisp",
        "E hash", "E sort", "E cells", "E phys", "sort us/d");
    for (int n : ns) {
        const std::vector<GpuBoid> in = snapshot(snapDir, "congested", n, shaderDir, sdfTex);
        const int steps = stepsFor(n, baseSteps);
        for (const std::string& u : usages) {
            CrowdSim sim(shaderDir, n, usageOf(u));
            const Pristine p(in);
            // A
            const PassMedians ring = timedSnapshotSteps(sim, p, sdfTex, steps, 1000.0);
            // B
            p.restore(sim);
            sim.beginTimingRing(steps);
            for (int i = 0; i < steps; ++i) sim.step(sdfTex);
            const PassMedians noRestore = medians(sim.readTimingRing());
            // C
            glFinish();
            auto t0 = Clock::now();
            for (int i = 0; i < steps; ++i) { p.restore(sim); sim.step(sdfTex); }
            glFinish();
            const double withSteps = bench::msSince(t0);
            t0 = Clock::now();
            for (int i = 0; i < steps; ++i) p.restore(sim);
            glFinish();
            const double wall = (withSteps - bench::msSince(t0)) / steps;
            // D
            p.restore(sim);
            glFinish();
            t0 = Clock::now();
            for (int i = 0; i < steps; ++i) sim.step(sdfTex);
            glFinish();
            const double wallNoRestore = bench::msSince(t0) / steps;
            // E
            int log2n = 0;
            while ((1 << log2n) < n) ++log2n;
            const size_t perStep = size_t(log2n * (log2n + 1) / 2 + 3) + 1;
            Stamps st(perStep * size_t(steps));
            std::vector<std::string> passOf;
            sim.setDispatchHook([&](const CrowdSim::DispatchInfo& d) { st.stamp(); passOf.push_back(d.pass); });
            for (int i = 0; i < steps; ++i) {
                p.restore(sim);
                st.stamp();
                passOf.push_back("start");
                sim.step(sdfTex);
            }
            sim.setDispatchHook(nullptr);
            const std::vector<double> t = st.readMs();
            std::vector<double> tot, h, s, c, ph, sortDisp;
            for (size_t i = 0; i < t.size();) {   // one step: "start" then its dispatches
                const size_t b = i;
                double hs = 0, ss = 0, cs = 0, ps = 0;
                for (++i; i < t.size() && passOf[i] != "start"; ++i) {
                    const double dt = t[i] - t[i - 1];
                    if (passOf[i] == "hash") hs += dt;
                    else if (passOf[i] == "sort") { ss += dt; sortDisp.push_back(dt); }
                    else if (passOf[i] == "cells") cs += dt;
                    else ps += dt;
                }
                tot.push_back(t[i - 1] - t[b]);
                h.push_back(hs); s.push_back(ss); c.push_back(cs); ph.push_back(ps);
            }
            out("  %-12s %7d %6d | %9.4f %9.4f %9.4f %9.4f %9.4f | %9.4f %9.4f %9.4f %9.4f %10.3f\n", u.c_str(), n, steps, ring.total, noRestore.total, wall,
                wallNoRestore, medianOf(tot), medianOf(h), medianOf(s), medianOf(c), medianOf(ph), 1000.0 * medianOf(sortDisp));
            out("  %-12s %7s %6s   A passes: hash %.4f sort %.4f cells %.4f physics %.4f | B passes: hash %.4f sort %.4f cells %.4f physics %.4f\n", "", "",
                "", ring.hash, ring.sort, ring.cells, ring.physics, noRestore.hash, noRestore.sort, noRestore.cells, noRestore.physics);
        }
    }
    return 0;
}

// GPU clock during sustained long steps (ALU-bound probe kernel between steps)
int cmdClock(const Args& a) {
    const int n = a.getInt("n", 262144);
    const double phaseS = a.getInt("seconds", 30);
    const fs::path snapDir = a.get("snapshots", "out/bench/snapshots");
    const fs::path outDir = a.get("out", "out/results/diag");

    bench::createHiddenContext("gpu_diag");
    const GLuint sdfTex = loadSDFTexture3D(resolveAsset("stadium.sdf"));
    if (!sdfTex) throw std::runtime_error("cannot load stadium.sdf");
    const fs::path shaderDir = resolveAsset("shaders");
    Report out(outDir / ("stage2c_clock_" + bench::localTimestamp("%Y%m%d_%H%M") + ".txt"));
    out("%s", header("clock (GPU clock during sustained long steps)").c_str());
    // A dependent FMA chain, no memory traffic: its GPU time is inversely proportional to the shader clock
    // (GL_TIMESTAMP counts a fixed-frequency reference)
    const GLuint alu = inlineProgram("alu", R"GLSL(
layout(local_size_x = 64) in;
layout(std430, binding = 0) buffer O { float o[]; };
uniform int iters;
void main() {
    float x = float(gl_GlobalInvocationID.x) * 1e-6, y = 1.0;
    for (int i = 0; i < iters; ++i) { x = fma(x, 0.9999999, 1e-7); y = fma(y, 1.0000001, -x); }
    if (y == 12345.678) o[0] = x;
}
)GLSL");
    const GLuint sink = makeBuffer("dynamic_copy", 16);
    const int iters = a.getInt("iters", 20000);
    auto probe = [&](Stamps& s) {
        glUseProgram(alu);
        glUniform1i(glGetUniformLocation(alu, "iters"), iters);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, sink);
        s.stamp();
        glDispatchCompute(240, 1, 1);
        glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
        s.stamp();
    };
    out("probe: %d iterations of a dependent FMA chain, 240 groups x 64; one probe after every step. Phases of ~%.0f s each.\n"
        "step ms = GPU total (5-stamp ring), restore before every step (snapshot mode), congested snapshot.\n\n", iters, phaseS);
    out("  %-34s %6s | %9s %9s %9s %9s %9s | %9s %9s %9s\n", "phase", "steps", "probe med", "min", "max", "first 10%", "last 10%", "step med", "first 10%",
        "last 10%");
    struct Phase { std::string name; int n; GLenum usage; };
    const std::vector<Phase> phases = { { "idle-light: N = 4096 steps", 4096, GL_DYNAMIC_DRAW },
                                        { "sustained: N = " + std::to_string(n) + ", dynamic_draw", n, GL_DYNAMIC_DRAW },
                                        { "sustained: N = " + std::to_string(n) + ", dynamic_copy", n, GL_DYNAMIC_COPY },
                                        { "idle-light again: N = 4096 steps", 4096, GL_DYNAMIC_DRAW } };
    for (const Phase& ph : phases) {
        const std::vector<GpuBoid> in = snapshot(snapDir, "congested", ph.n, shaderDir, sdfTex);
        CrowdSim sim(shaderDir, ph.n, ph.usage);
        const Pristine p(in);
        std::vector<double> probeMs, stepMs;
        const auto t0 = Clock::now();
        while (bench::msSince(t0) < phaseS * 1000.0) {   // batches of 10 steps, read back after each batch
            Stamps s(20);
            sim.beginTimingRing(10);
            for (int i = 0; i < 10; ++i) { p.restore(sim); sim.step(sdfTex); probe(s); }
            const std::vector<double> t = s.readMs();
            for (int i = 0; i < 10; ++i) probeMs.push_back(t[size_t(2 * i + 1)] - t[size_t(2 * i)]);
            for (const CrowdSim::PassTimesMs& x : sim.readTimingRing()) stepMs.push_back(x.total);
        }
        auto part = [](const std::vector<double>& v, bool first) {
            const size_t k = std::max<size_t>(1, v.size() / 10);
            return medianOf(first ? std::vector<double>(v.begin(), v.begin() + std::ptrdiff_t(k)) : std::vector<double>(v.end() - std::ptrdiff_t(k), v.end()));
        };
        const bench::Stats ps = bench::stats(probeMs);
        out("  %-34s %6zu | %9.4f %9.4f %9.4f %9.4f %9.4f | %9.4f %9.4f %9.4f\n", ph.name.c_str(), stepMs.size(), ps.median, ps.min, ps.max,
            part(probeMs, true), part(probeMs, false), medianOf(stepMs), part(stepMs, true), part(stepMs, false));
    }
    glDeleteBuffers(1, &sink);
    glDeleteProgram(alu);
    return 0;
}

// Perf verdict, rotated A/B with an A/A control (tools/perf_ab protocol) in one
// process: the two versions differ only in CrowdSim's ssboUsage, so one build runs both
int cmdAb(const Args& a) {
    const std::vector<int> ns = a.has("n") ? bench::parseIntList(a.get("n", "")) : DEFAULT_NS;
    const int rounds = a.getInt("rounds", 12);
    const double warmMs = a.getInt("warm-ms", 500);
    const fs::path snapDir = a.get("snapshots", "out/bench/snapshots");
    const fs::path outDir = a.get("out", "out/results/diag");
    struct Label { std::string name; GLenum usage; };
    // --labels name:usage,... replaces the default set; the first label is the reference, the second its A/A control
    std::vector<Label> labels = { { "base", GL_DYNAMIC_DRAW }, { "base_aa", GL_DYNAMIC_DRAW }, { "new", GL_DYNAMIC_COPY } };
    if (a.has("labels")) {
        labels.clear();
        for (const std::string& l : bench::parseList(a.get("labels", ""))) {
            const size_t c = l.find(':');
            if (c == std::string::npos) throw std::runtime_error("--labels: expected name:usage, got " + l);
            labels.push_back({ l.substr(0, c), usageOf(l.substr(c + 1)) });
        }
        if (labels.size() < 3) throw std::runtime_error("--labels: need a reference, its A/A control and at least one variant");
    }
    auto usageName = [](GLenum u) {
        return u == GL_DYNAMIC_DRAW ? "dynamic_draw" : u == GL_DYNAMIC_COPY ? "dynamic_copy" : u == GL_STATIC_DRAW ? "static_draw" : "stream_draw";
    };
    auto stepsAt = [](int n) { return n <= 16384 ? 300 : n <= 65536 ? 200 : n <= 131072 ? 50 : 20; };

    bench::createHiddenContext("gpu_diag");
    const GLuint sdfTex = loadSDFTexture3D(resolveAsset("stadium.sdf"));
    if (!sdfTex) throw std::runtime_error("cannot load stadium.sdf");
    const fs::path shaderDir = resolveAsset("shaders");
    const std::string stamp = bench::localTimestamp("%Y%m%d_%H%M");
    Report out(outDir / ("stage3_ab_" + stamp + ".md"));
    std::FILE* csv = std::fopen((outDir / ("stage3_ab_" + stamp + ".csv")).string().c_str(), "w");
    if (!csv) throw std::runtime_error("cannot write the A/B CSV");
    std::fprintf(csv, "round,position,label,usage,N,state,steps,hash_ms,sort_ms,cells_ms,physics_ms,total_ms,capacity_label\n");
    out("# A/B: CrowdSim SSBO usage GL_DYNAMIC_DRAW (base) vs GL_DYNAMIC_COPY (new)\n\n```\n%s```\n\n", header("ab").c_str());
    out("Protocol (tools/perf_ab): one build; both versions differ only in CrowdSim's ssboUsage. Snapshot mode (restore before every\n"
        "step, outside the timestamps), >= %.1f s warm-up per cell, then N-dependent measured steps (300 / 200 / 50 / 20 at N <= 16384 /\n"
        "65536 / 131072 / 262144). %d rounds; in each round every (N, state) runs base, base_aa (A/A control: base again) and new in an\n"
        "order rotated by one position per round (Latin square: each label takes each position equally often over 3k rounds).\n"
        "Verdict per case: median over rounds of the per-round median step time (GPU-execution, all four passes); A/A delta = noise floor.\n\n",
        warmMs / 1000.0, rounds);

    std::map<std::string, std::vector<GpuBoid>> snaps;
    for (int n : ns)
        for (const char* state : { "spawn", "congested" }) snaps[std::string(state) + std::to_string(n)] = snapshot(snapDir, state, n, shaderDir, sdfTex);
    // results[(n, state, label)] -> per-round PassMedians
    std::map<std::tuple<int, std::string, std::string>, std::vector<PassMedians>> res;
    const auto start = Clock::now();
    for (int r = 0; r < rounds; ++r) {
        for (int n : ns) {
            for (const char* state : { "spawn", "congested" }) {
                const std::vector<GpuBoid>& in = snaps[std::string(state) + std::to_string(n)];
                for (size_t pos = 0; pos < labels.size(); ++pos) {
                    const Label& l = labels[(pos + size_t(r)) % labels.size()];
                    CrowdSim sim(shaderDir, n, l.usage);
                    const Pristine p(in);
                    const PassMedians m = timedSnapshotSteps(sim, p, sdfTex, stepsAt(n), warmMs);
                    res[{ n, state, l.name }].push_back(m);
                    std::fprintf(csv, "%d,%zu,%s,%s,%d,%s,%d,%.5f,%.5f,%.5f,%.5f,%.5f,%s\n", r, pos, l.name.c_str(),
                                 usageName(l.usage), n, state, m.steps, m.hash, m.sort, m.cells, m.physics,
                                 m.total, venue::label(n).c_str());
                    std::fflush(csv);
                }
            }
        }
        std::printf("  round %d/%d done [%.0f s]\n", r + 1, rounds, bench::msSince(start) / 1000.0);
        std::fflush(stdout);
    }
    std::fclose(csv);

    auto agg = [](const std::vector<PassMedians>& v, double PassMedians::*f) {
        std::vector<double> x;
        for (const PassMedians& m : v) x.push_back(m.*f);
        return medianOf(x);
    };
    auto range = [](const std::vector<PassMedians>& v) {
        double lo = 1e30, hi = 0;
        for (const PassMedians& m : v) { lo = std::min(lo, m.total); hi = std::max(hi, m.total); }
        return std::make_pair(lo, hi);
    };
    const std::string& ref = labels[0].name;
    out("| N | state |");
    for (const Label& l : labels) out(" %s (%s) ms (min-max) |%s", l.name.c_str(), usageName(l.usage), &l == &labels[0] ? "" : " vs ref |");
    out("\n|---:|---|");
    for (const Label& l : labels) out("---:|%s", &l == &labels[0] ? "" : "---:|");
    out("\n");
    for (int n : ns)
        for (const char* state : { "spawn", "congested" }) {
            const double mr = agg(res[{ n, state, ref }], &PassMedians::total);
            out("| %d | %s |", n, state);
            for (const Label& l : labels) {
                const auto& v = res[{ n, state, l.name }];
                const double m = agg(v, &PassMedians::total);
                const auto rg = range(v);
                out(" %.4f (%.4f-%.4f) |", m, rg.first, rg.second);
                if (&l != &labels[0]) out(" %+.1f%% |", 100.0 * (m / mr - 1.0));
            }
            out("\n");
        }
    out("\nThe second label repeats the reference (A/A control): its delta is the noise floor.\n");
    out("\nPer pass (median over rounds of the per-round medians, ms), per label: hash / sort / cells / physics\n\n| N | state |");
    for (const Label& l : labels) out(" %s |", l.name.c_str());
    out("\n|---:|---|");
    for (size_t k = 0; k < labels.size(); ++k) out("---|");
    out("\n");
    for (int n : ns)
        for (const char* state : { "spawn", "congested" }) {
            out("| %d | %s |", n, state);
            for (const Label& l : labels) {
                const auto& v = res[{ n, state, l.name }];
                out(" %.4f / %.4f / %.4f / %.4f |", agg(v, &PassMedians::hash), agg(v, &PassMedians::sort), agg(v, &PassMedians::cells),
                    agg(v, &PassMedians::physics));
            }
            out("\n");
        }
    out("\nElapsed: %.1f min.\n", bench::msSince(start) / 60000.0);
    return 0;
}

// Admissibility beyond the golden sizes: the state after 'steps' steps from spawn under
// GL_DYNAMIC_DRAW and GL_DYNAMIC_COPY, FNV-1a 64 (golden::stateHash), at every N
int cmdSame(const Args& a) {
    const std::vector<int> ns = a.has("n") ? bench::parseIntList(a.get("n", "")) : DEFAULT_NS;
    const int steps = a.getInt("steps", 100);
    const fs::path outDir = a.get("out", "out/results/diag");
    bench::createHiddenContext("gpu_diag");
    const GLuint sdfTex = loadSDFTexture3D(resolveAsset("stadium.sdf"));
    if (!sdfTex) throw std::runtime_error("cannot load stadium.sdf");
    const fs::path shaderDir = resolveAsset("shaders");
    Report out(outDir / ("stage3_same_" + bench::localTimestamp("%Y%m%d_%H%M") + ".txt"));
    out("%s", header("same (state bit-identical under both usage hints)").c_str());
    out("FNV-1a 64 of the raw agent state after %d steps from spawnBleacherCrowd(N), continuous stepping\n", steps);
    out("  %7s | %-18s %-18s | %s\n", "N", "GL_DYNAMIC_DRAW", "GL_DYNAMIC_COPY", "result");
    bool all = true;
    for (int n : ns) {
        const std::vector<GpuBoid> spawn = spawnBleacherCrowd(n);
        uint64_t h[2] = {};
        const GLenum usages[2] = { GL_DYNAMIC_DRAW, GL_DYNAMIC_COPY };
        for (int u = 0; u < 2; ++u) {
            CrowdSim sim(shaderDir, n, usages[u]);
            sim.upload(spawn);
            for (int i = 0; i < steps; ++i) sim.step(sdfTex);
            h[u] = golden::stateHash(bench::readBuffer<GpuBoid>(sim.currentStateBuffer(), size_t(n)));
        }
        all &= h[0] == h[1];
        out("  %7d | %016llx   %016llx   | %s\n", n, (unsigned long long)h[0], (unsigned long long)h[1], h[0] == h[1] ? "bit-identical" : "DIFFERENT");
    }
    out("%s\n", all ? "ALL BIT-IDENTICAL" : "DIFFERENCES FOUND");
    return all ? 0 : 1;
}

// Proposal prototype (not used by CrowdSim): the same bitonic network with its j < 512 passes run in
// shared memory, 512-element tiles, two elements per invocation. Every compare-exchange is the one
// bitonic_sort.comp performs (same pairs, same direction (id & k) == 0, same strict gridID test, whole
// 16-byte entries moved), and the network is data-oblivious, so the output must be bit-identical.
// Dispatches: one tile sort (k = 2..512), then per k >= 1024 the global passes j = k/2 .. 512
// (bitonic_sort.comp) and one shared-memory merge (j = 256 .. 1).
struct LocalSortRunner {
    GLuint prog = 0;
    GLint locK = -1, locJStart = -1, locMode = -1;
    const SortRunner& global;
    explicit LocalSortRunner(const SortRunner& g) : global(g) {
        prog = inlineProgram("sort_local", R"GLSL(
layout(local_size_x = 256) in;
struct Info { uint g; uint b; uint p1; uint p2; };
layout(std430, binding = 1) buffer G { Info i[]; };
uniform int k;        // mode 1: the k of the merge
uniform int jStart;   // mode 1: first j (256)
uniform int mode;     // 0: tile sort, k = 2..512; 1: merge passes j = jStart..1 of k
shared Info s[512];
void cmpx(uint base, uint t, uint kk, uint jj) {
    uint lo = ((t & ~(jj - 1u)) << 1u) | (t & (jj - 1u));   // t with a 0 inserted at bit log2(jj)
    uint hi = lo | jj;
    bool asc = ((base + lo) & kk) == 0u;
    uint gl = s[lo].g, gh = s[hi].g;
    if ((asc && gl > gh) || (!asc && gl < gh)) { Info x = s[lo]; s[lo] = s[hi]; s[hi] = x; }
}
void main() {
    uint t = gl_LocalInvocationID.x;
    uint base = gl_WorkGroupID.x * 512u;
    s[t] = i[base + t];
    s[t + 256u] = i[base + t + 256u];
    barrier();
    if (mode == 0) {
        for (uint kk = 2u; kk <= 512u; kk <<= 1u)
            for (uint jj = kk >> 1u; jj > 0u; jj >>= 1u) { cmpx(base, t, kk, jj); barrier(); }
    } else {
        for (uint jj = uint(jStart); jj > 0u; jj >>= 1u) { cmpx(base, t, uint(k), jj); barrier(); }
    }
    i[base + t] = s[t];
    i[base + t + 256u] = s[t + 256u];
}
)GLSL");
        locK = glGetUniformLocation(prog, "k");
        locJStart = glGetUniformLocation(prog, "jStart");
        locMode = glGetUniformLocation(prog, "mode");
    }
    ~LocalSortRunner() { glDeleteProgram(prog); }
    static int dispatches(int n) {
        int d = 1;
        for (int k = 1024; k <= n; k <<= 1) for (int j = k >> 1; j >= 512; j >>= 1) ++d;
        for (int k = 1024; k <= n; k <<= 1) ++d;
        return d;
    }
    void run(GLuint buf, int n) const {   // n >= 512, a power of two
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_GRID, buf);
        glUseProgram(prog);
        glUniform1i(locMode, 0);
        glDispatchCompute(GLuint(n / 512), 1, 1);
        glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
        for (int k = 1024; k <= n; k <<= 1) {
            glUseProgram(global.prog);
            for (int j = k >> 1; j >= 512; j >>= 1) {
                glUniform1i(global.locJ, j);
                glUniform1i(global.locK, k);
                glDispatchCompute(GLuint(n / 256), 1, 1);
                glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
            }
            glUseProgram(prog);
            glUniform1i(locMode, 1);
            glUniform1i(locK, k);
            glUniform1i(locJStart, 256);
            glDispatchCompute(GLuint(n / 512), 1, 1);
            glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
        }
    }
};

int cmdSortLocal(const Args& a) {
    const int lo = a.getInt("min", 10), hi = a.getInt("max", 20), reps = a.getInt("reps", 20);
    const fs::path snapDir = a.get("snapshots", "out/bench/snapshots");
    const fs::path outDir = a.get("out", "out/results/diag");
    bench::createHiddenContext("gpu_diag");
    const GLuint sdfTex = loadSDFTexture3D(resolveAsset("stadium.sdf"));
    if (!sdfTex) throw std::runtime_error("cannot load stadium.sdf");
    const fs::path shaderDir = resolveAsset("shaders");
    Report out(outDir / ("stage3_sortlocal_" + bench::localTimestamp("%Y%m%d_%H%M") + ".txt"));
    out("%s", header("sortlocal (prototype: the same network, j < 512 passes in shared memory)").c_str());
    const SortRunner global(shaderDir);
    const LocalSortRunner local(global);
    auto timeSort = [&](GLuint pristine, GLuint buf, GLsizeiptr bytes, int n, bool useLocal) {
        for (int w = 0; w < 3; ++w) { copyBuffer(pristine, buf, bytes); useLocal ? local.run(buf, n) : global.run(buf, n, BarrierMode::Ssbo, nullptr); }
        Stamps s(size_t(reps) * 2);
        for (int r = 0; r < reps; ++r) {
            copyBuffer(pristine, buf, bytes);
            s.stamp();
            useLocal ? local.run(buf, n) : global.run(buf, n, BarrierMode::Ssbo, nullptr);
            s.stamp();
        }
        const std::vector<double> t = s.readMs();
        std::vector<double> v;
        for (int r = 0; r < reps; ++r) v.push_back(t[size_t(2 * r + 1)] - t[size_t(2 * r)]);
        return medianOf(v);
    };
    auto sortBoth = [&](const std::vector<GpuGridInfo>& keys, double& msGlobal, double& msLocal) {
        const int n = int(keys.size());
        const GLsizeiptr bytes = GLsizeiptr(n) * GLsizeiptr(sizeof(GpuGridInfo));
        const GLuint pristine = makeBuffer("static_draw", bytes, keys.data());
        const GLuint bufG = makeBuffer("dynamic_copy", bytes), bufL = makeBuffer("dynamic_copy", bytes);
        copyBuffer(pristine, bufG, bytes);
        global.run(bufG, n, BarrierMode::Ssbo, nullptr);
        copyBuffer(pristine, bufL, bytes);
        local.run(bufL, n);
        const std::vector<GpuGridInfo> g = bench::readBuffer<GpuGridInfo>(bufG, size_t(n)), l = bench::readBuffer<GpuGridInfo>(bufL, size_t(n));
        const bool same = std::memcmp(g.data(), l.data(), size_t(bytes)) == 0;
        msGlobal = timeSort(pristine, bufG, bytes, n, false);
        msLocal = timeSort(pristine, bufL, bytes, n, true);
        glDeleteBuffers(1, &pristine);
        glDeleteBuffers(1, &bufG);
        glDeleteBuffers(1, &bufL);
        return same;
    };
    out("GPU ms per sort (median of %d, GL_DYNAMIC_COPY buffers), output compared byte for byte with bitonic_sort.comp's\n\n", reps);
    out("A. synthetic keys (gridID uniform over the 1600 cells, padding = index)\n  %8s | %10s %10s | %9s %9s | %7s | %s\n", "N", "dispatches", "proposed",
        "global ms", "local ms", "speedup", "output");
    bool all = true;
    for (int l = std::max(lo, 9); l <= hi; ++l) {
        const int n = 1 << l;
        std::vector<GpuGridInfo> keys = randomKeys(n, 777u + unsigned(l));
        for (int i = 0; i < n; ++i) keys[size_t(i)].padding0 = keys[size_t(i)].padding1 = uint32_t(i);   // entries move whole
        double mg = 0, ml = 0;
        const bool same = sortBoth(keys, mg, ml);
        all &= same;
        out("  %8d | %10d %10d | %9.4f %9.4f | %6.2fx | %s\n", n, l * (l + 1) / 2, LocalSortRunner::dispatches(n), mg, ml, mg / ml,
            same ? "bit-identical" : "DIFFERENT");
    }
    out("\nB. real hash output: CrowdSim's grid buffer after the hash pass (the sort's input), benchmark snapshots\n  %8s %-9s | %9s %9s | %7s | %s\n", "N", "state",
        "global ms", "local ms", "speedup", "output");
    for (int n : DEFAULT_NS) {
        for (const char* state : { "spawn", "congested" }) {
            const std::vector<GpuBoid> in = snapshot(snapDir, state, n, shaderDir, sdfTex);
            CrowdSim sim(shaderDir, n);
            sim.upload(in);
            std::vector<GpuGridInfo> hashed;
            sim.setDispatchHook([&](const CrowdSim::DispatchInfo& d) {
                if (std::string(d.pass) == "hash") hashed = bench::readBuffer<GpuGridInfo>(sim.gridBuffer(), size_t(n));
            });
            sim.step(sdfTex);
            sim.setDispatchHook(nullptr);
            const std::vector<GpuGridInfo> gpuSorted = bench::readBuffer<GpuGridInfo>(sim.gridBuffer(), size_t(n));
            double mg = 0, ml = 0;
            bool same = sortBoth(hashed, mg, ml);
            // ... and equal to the sorted array of the real step (the sort input is the hash output)
            {
                const GLsizeiptr bytes = GLsizeiptr(n) * GLsizeiptr(sizeof(GpuGridInfo));
                const GLuint buf = makeBuffer("dynamic_copy", bytes, hashed.data());
                local.run(buf, n);
                same &= std::memcmp(bench::readBuffer<GpuGridInfo>(buf, size_t(n)).data(), gpuSorted.data(), size_t(bytes)) == 0;
                glDeleteBuffers(1, &buf);
            }
            all &= same;
            out("  %8d %-9s | %9.4f %9.4f | %6.2fx | %s\n", n, state, mg, ml, mg / ml, same ? "bit-identical (also to the step's sorted grid)" : "DIFFERENT");
        }
    }
    out("\n%s\n", all ? "ALL BIT-IDENTICAL" : "DIFFERENCES FOUND");
    return all ? 0 : 1;
}

// The proof: CrowdSim's sort (shared-memory stages, CrowdSim::sortGrid) against the same network as one global
// dispatch per pass (SortRunner: bitonic_sort.comp). Whole 16-byte entries compared byte for byte, every N from 2^min to 2^max.
//   synthetic keys: several distributions, boidID = index and padding words derived from the index, so every
//                   entry is unique and any difference in the permutation shows
//   real keys:      the hash pass output of the benchmark snapshots (spawn, congested; generated when missing),
//                   also compared with the step's own sorted grid and with CpuCrowdSim's bitonic replay
int cmdSortCheck(const Args& a) {
    const int lo = a.getInt("min", 10), hi = a.getInt("max", 20);
    const bool cpu = !a.has("no-cpu");
    const fs::path snapDir = a.get("snapshots", "out/bench/snapshots");
    const fs::path outDir = a.get("out", "out/results/perf");
    bench::createHiddenContext("gpu_diag");
    const GLuint sdfTex = loadSDFTexture3D(resolveAsset("stadium.sdf"));
    const std::vector<float>& sdf = sdfVolumeCPU();
    if (!sdfTex || sdf.empty()) throw std::runtime_error("cannot load stadium.sdf");
    const fs::path shaderDir = resolveAsset("shaders");
    Report out(outDir / ("sort_identity_" + bench::localTimestamp("%Y%m%d_%H%M") + ".txt"));
    out("%s", header("sortcheck (shared-memory bitonic stages vs one global dispatch per pass)").c_str());
    out("new = CrowdSim::sortGrid (passes j < %d in shared memory, bitonic_sort_shared.comp); old = the same network as one\n"
        "global dispatch per pass (bitonic_sort.comp). Whole 16-byte entries, byte for byte.\n\n",
        CrowdSim::SORT_TILE);

    const SortRunner global(shaderDir);
    // Sorts 'keys' both ways; returns the new output, sets 'same'
    auto sortBoth = [&](CrowdSim& sim, const std::vector<GpuGridInfo>& keys, bool& same) {
        const int n = int(keys.size());
        const GLsizeiptr bytes = GLsizeiptr(n) * GLsizeiptr(sizeof(GpuGridInfo));
        const GLuint ref = makeBuffer("dynamic_copy", bytes, keys.data());
        global.run(ref, n, BarrierMode::Ssbo, nullptr);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, sim.gridBuffer());
        glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, bytes, keys.data());
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
        sim.sortGrid();
        const std::vector<GpuGridInfo> oldOut = bench::readBuffer<GpuGridInfo>(ref, size_t(n));
        std::vector<GpuGridInfo> newOut = bench::readBuffer<GpuGridInfo>(sim.gridBuffer(), size_t(n));
        same = std::memcmp(oldOut.data(), newOut.data(), size_t(bytes)) == 0 && sortedPermutation(newOut);
        glDeleteBuffers(1, &ref);
        return newOut;
    };

    struct Dist { const char* name; std::function<uint32_t(int, int, std::mt19937&)> key; };
    const std::vector<Dist> dists = {
        { "cells+10%inactive", [](int, int, std::mt19937& g) { return g() % 10 == 0 ? INACTIVE_CELL : uint32_t(g() % uint32_t(GRID_RES * GRID_RES)); } },
        { "random32", [](int, int, std::mt19937& g) { return uint32_t(g()); } },
        { "fewkeys", [](int, int, std::mt19937& g) { const uint32_t k[3] = { 0u, 1u, INACTIVE_CELL }; return k[g() % 3]; } },
        { "all-equal", [](int, int, std::mt19937&) { return 777u; } },
        { "ascending", [](int i, int, std::mt19937&) { return uint32_t(i); } },
        { "descending", [](int i, int n, std::mt19937&) { return uint32_t(n - 1 - i); } },
    };
    out("A. synthetic keys (boidID = index, padding0 = index ^ 0xA5A5A5A5, padding1 = random)\n  %8s | %5s %5s |", "N", "old", "new");
    for (const Dist& d : dists) out(" %-17s |", d.name);
    out("\n");
    bool all = true;
    for (int l = lo; l <= hi; ++l) {
        const int n = 1 << l;
        CrowdSim sim(shaderDir, n);
        int newDispatches = 0;
        sim.setDispatchHook([&](const CrowdSim::DispatchInfo& d) { newDispatches += std::string(d.pass) == "sort"; });
        out("  %8d | %5d ", n, l * (l + 1) / 2);
        std::string row;
        for (size_t di = 0; di < dists.size(); ++di) {
            std::mt19937 gen(4404u + unsigned(l) * 16u + unsigned(di));
            std::vector<GpuGridInfo> keys(static_cast<size_t>(n));
            for (int i = 0; i < n; ++i)
                keys[size_t(i)] = { dists[di].key(i, n, gen), uint32_t(i), uint32_t(i) ^ 0xA5A5A5A5u, uint32_t(gen()) };
            newDispatches = 0;
            bool same = false;
            sortBoth(sim, keys, same);
            all &= same;
            row += same ? " bit-identical     |" : " DIFFERENT         |";
        }
        out("%5d |%s\n", newDispatches, row.c_str());
    }

    out("\nB. real keys: the hash pass output of the snapshots (the sort's input in CrowdSim::step)\n"
        "  %8s %-9s %7s | %-16s | %-22s | %s\n", "N", "state", "active", "new vs old", "new vs the step's grid",
        cpu ? "(gridID, boidID) vs CPU bitonic replay" : "(CPU replay skipped)");
    for (int l = lo; l <= hi; ++l) {
        const int n = 1 << l;
        for (const char* state : { "spawn", "congested" }) {
            const std::vector<GpuBoid> in = snapshot(snapDir, state, n, shaderDir, sdfTex);
            CrowdSim sim(shaderDir, n);
            sim.upload(in);
            std::vector<GpuGridInfo> hashed;
            sim.setDispatchHook([&](const CrowdSim::DispatchInfo& d) {
                if (std::string(d.pass) == "hash") hashed = bench::readBuffer<GpuGridInfo>(sim.gridBuffer(), size_t(n));
            });
            sim.step(sdfTex);
            sim.setDispatchHook(nullptr);
            const std::vector<GpuGridInfo> stepGrid = bench::readBuffer<GpuGridInfo>(sim.gridBuffer(), size_t(n));
            bool same = false;
            const std::vector<GpuGridInfo> newOut = sortBoth(sim, hashed, same);
            const bool sameStep = std::memcmp(newOut.data(), stepGrid.data(), newOut.size() * sizeof(GpuGridInfo)) == 0;
            long cpuDiff = -1;
            if (cpu) {
                CpuCrowdSim replay(sdf, 0, CpuCrowdSim::SortMode::GpuBitonic);
                replay.setState(in);
                replay.step();
                cpuDiff = 0;
                for (int s = 0; s < n; ++s)
                    cpuDiff += replay.grid()[size_t(s)].gridID != stepGrid[size_t(s)].gridID || replay.grid()[size_t(s)].boidID != stepGrid[size_t(s)].boidID;
            }
            all &= same && sameStep && cpuDiff <= 0;
            char cpuCol[64];
            if (cpu) std::snprintf(cpuCol, sizeof cpuCol, "%s (%ld slots differ)", cpuDiff == 0 ? "exact" : "DIFFERENT", cpuDiff);
            else std::snprintf(cpuCol, sizeof cpuCol, "-");
            out("  %8d %-9s %7ld | %-16s | %-22s | %s\n", n, state, bench::countActive(in), same ? "bit-identical" : "DIFFERENT",
                sameStep ? "bit-identical" : "DIFFERENT", cpuCol);
        }
    }
    out("\n%s\n", all ? "ALL BIT-IDENTICAL" : "DIFFERENCES FOUND");
    return all ? 0 : 1;
}

} // namespace

int main(int argc, char** argv) {
    if (argc < 2) {
        std::fprintf(stderr, "usage: gpu_diag correctness [...]\n");
        return 2;
    }
    g_qos = bench::optOutOfPowerThrottling();
    try {
        const std::string cmd = argv[1];
        const Args a(argc, argv, 2);
        if (cmd == "correctness") return cmdCorrectness(a);
        if (cmd == "sort") return cmdSort(a);
        if (cmd == "bandwidth") return cmdBandwidth(a);
        if (cmd == "placement") return cmdPlacement(a);
        if (cmd == "physics") return cmdPhysics(a);
        if (cmd == "timing") return cmdTiming(a);
        if (cmd == "clock") return cmdClock(a);
        if (cmd == "ab") return cmdAb(a);
        if (cmd == "same") return cmdSame(a);
        if (cmd == "sortlocal") return cmdSortLocal(a);
        if (cmd == "sortcheck") return cmdSortCheck(a);
        std::fprintf(stderr, "unknown command %s\n", cmd.c_str());
        return 2;
    } catch (const std::exception& e) {
        std::fprintf(stderr, "FATAL: %s\n", e.what());
        return 1;
    }
}
