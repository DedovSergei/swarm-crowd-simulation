#include <swarm/exit_choice.hpp>

#include <swarm/shader.hpp>
#include <swarm/venue.hpp>

#include <omp.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <limits>
#include <map>
#include <memory>
#include <mutex>
#include <sstream>
#include <stdexcept>

namespace swarm {

const char* exitChoiceName(ExitChoice c) { return c == ExitChoice::QueueAware ? "queue-aware" : "nearest"; }

ExitChoice exitChoiceByName(const std::string& name) {
    if (name == "nearest") return ExitChoice::Nearest;
    if (name == "queue-aware" || name == "queue") return ExitChoice::QueueAware;
    throw std::invalid_argument("exit choice '" + name + "': expected nearest | queue-aware");
}

const char* stairFlowName(StairFlow s) {
    return s == StairFlow::Empirical ? "empirical" : s == StairFlow::Conservative ? "conservative" : "off";
}

StairFlow stairFlowByName(const std::string& name) {
    if (name == "off" || name == "0") return StairFlow::Off;
    if (name == "empirical") return StairFlow::Empirical;
    if (name == "conservative") return StairFlow::Conservative;
    throw std::invalid_argument("stair flow '" + name + "': expected off | empirical | conservative");
}

glm::vec2 stairHeadwayTimes(StairFlow s) {
    switch (s) {
    case StairFlow::Empirical: return { T_HEADWAY_STAIR_UP, T_HEADWAY_STAIR_DOWN };
    case StairFlow::Conservative: return { T_HEADWAY_STAIR_UP_CONSERVATIVE, T_HEADWAY_STAIR_DOWN_CONSERVATIVE };
    default: return { T_HEADWAY, T_HEADWAY };
    }
}

ModelOptions defaultModelOptions(const Venue& v) {
    if (!v.seated()) return {};
    // The queue-aware exit choice and the incline speed: on venue S every exit is used and t100 is far shorter than with the nearest exit at the
    // same stair speeds, every per-step check passes; the stair speeds replace a level speed on 26.6 deg gangways. The stair spacing, EMPIRICAL:
    // the gangways' maximum sustained flow at the measured stair flows instead of about 1.8x the planning rate. Simpler models stay
    // selectable: {Nearest, false}, {QueueAware, true, Off}.
    return { ExitChoice::QueueAware, true, StairFlow::Empirical };
}

ModelOptions effectiveModelOptions(const Venue& v, const ModelOptions& o) {
    if (!v.seated()) return ModelOptions{};
    ModelOptions e = o;
    if (!e.inclineSpeed) e.stairFlow = StairFlow::Off;
    return e;
}

std::string modelOptionsLabel(const Venue& v, const ModelOptions& o) {
    if (!v.seated()) return "hand router, level speed";
    const ModelOptions e = effectiveModelOptions(v, o);
    return std::string(e.exitChoice == ExitChoice::QueueAware ? "queue-aware exit choice" : "nearest exit") +
           (e.inclineSpeed ? ", incline speed" : ", level speed") +
           (e.stairFlow != StairFlow::Off ? std::string(", stair spacing (") + stairFlowName(e.stairFlow) + ")" : std::string());
}

std::string modelPreamble(const Venue& v, const ModelOptions& opts) {
    const ModelOptions o = effectiveModelOptions(v, opts);
    std::string s;
    if (o.exitChoice == ExitChoice::QueueAware) s += nav::choicePreambleDefines(nav::choiceForVenue(v));
    if (o.inclineSpeed) {   // the stair speeds in model units, host-folded (sim_params.hpp)
        s += "// ---- incline speed (swarm/sim_params.hpp) ----\n#define VENUE_INCLINE_SPEED 1\n";
        s += "#define V_STAIR_UP " + glslFloatLiteral(V_STAIR_UP) + "\n#define V_STAIR_DOWN " + glslFloatLiteral(V_STAIR_DOWN) + "\n";
        s += "#define INCLINE_INV_REF_SLOPE " + glslFloatLiteral(INCLINE_INV_REF_SLOPE) + "\n";
    }
    if (o.stairFlow != StairFlow::Off) {   // the stair spacing's time gaps in model units, host-folded (sim_params.hpp)
        const glm::vec2 t = stairHeadwayTimes(o.stairFlow);
        s += std::string("// ---- stair spacing (swarm/sim_params.hpp): ") + stairFlowName(o.stairFlow) + " ----\n#define VENUE_STAIR_HEADWAY 1\n";
        s += "#define T_HEADWAY_STAIR_UP " + glslFloatLiteral(t.x) + "\n#define T_HEADWAY_STAIR_DOWN " + glslFloatLiteral(t.y) + "\n";
    }
    return s;
}

namespace nav {

const GpuNavChoiceCell& ChoiceTable::at(size_t i) const {
    static const GpuNavChoiceCell empty = [] {
        GpuNavChoiceCell c{};
        for (int k = 0; k < CHOICE_K; ++k) c.slot[k] = CHOICE_EMPTY << CHOICE_EXIT_SHIFT;
        for (int w = 0; w < CHOICE_DIST_WORDS; ++w) c.dist[w] = 0xFFFFFFFFu;
        return c;
    }();
    const uint32_t e = index[i] & CHOICE_INDEX_MASK;
    return e ? entries[e - 1] : empty;
}

int ChoiceTable::candidates(size_t i) const {
    int k = 0;
    while (k < CHOICE_K && slotExit(at(i).slot[k]) != CHOICE_EMPTY) ++k;
    return k;
}

ExitField buildExitField(const Field& grid, int exit) {
    std::vector<double> g;
    std::vector<int32_t> par;
    std::vector<uint8_t> closed;
    lazyThetaStar(grid, exit, g, par, closed);
    ExitField e;
    const size_t n = grid.grid.cells();
    e.dist.resize(n);
    e.anchor.resize(n);
    for (size_t i = 0; i < n; ++i) {
        const bool reach = closed[i] && std::isfinite(g[i]);   // Field::dist's conversion (nav::build)
        e.dist[i] = reach ? float(g[i]) : std::numeric_limits<float>::infinity();
        e.anchor[i] = reach ? par[i] : -1;
    }
    return e;
}

void setChoiceCapacities(ChoiceTable& t, double metresPerUnit) {
    t.invCapS.assign(size_t(t.exitCount), 0.0f);
    for (int e = 0; e < t.exitCount; ++e) {
        const double w = t.exitWidthM[size_t(e)];
        // seconds per queued person: 60 / (w J), J in persons/(m min); rounded once from double
        t.invCapS[size_t(e)] = w > 0.0 ? float(60.0 / (w * glsl_fold::decimal(EXIT_FLOW_P_M_MIN))) : 0.0f;
    }
    // A venue walks at V0 = V_FREE_M_S over model units: CHOICE_S_PER_UNIT (sim_params.hpp); other geometries in their units
    t.secondsPerUnit = metresPerUnit == units::M_PER_UNIT ? CHOICE_S_PER_UNIT
                                                          : float(metresPerUnit / glsl_fold::decimal(V_FREE_M_S));
    // 2^-k with 2^-k x metresPerUnit the largest at or below 7.6 mm (a venue: 2^-12 model units; metres: 2^-8 m = 3.9 mm)
    t.distQuantum = metresPerUnit == units::M_PER_UNIT ? CHOICE_DIST_QUANTUM
                                                       : std::ldexp(1.0f, -int(std::ceil(std::log2(metresPerUnit / (double(CHOICE_DIST_QUANTUM) * units::M_PER_UNIT)))));
}

ChoiceTable buildChoiceTable(const Geometry& geo, const Field& grid, std::vector<ExitField>* allFields) {
    const auto t0 = std::chrono::steady_clock::now();
    const size_t n = grid.grid.cells();
    if (n > size_t(CHOICE_ANCHOR_MASK) + 1) throw std::invalid_argument("buildChoiceTable: more cells than the 25-bit anchor index holds");
    if (grid.exitCount > CHOICE_MAX_EXITS) throw std::invalid_argument("buildChoiceTable: more than 63 exits");
    ChoiceTable t;
    t.grid = grid.grid;
    t.exitCount = grid.exitCount;
    t.exitNames = grid.exitNames;
    for (int e = 0; e < t.exitCount; ++e) t.exitWidthM.push_back(geo.exitWidthM(e));
    setChoiceCapacities(t, geo.metresPerUnit());
    // The cells with an entry: the reachable FIT cells (the lookup, choiceCell, returns no other: a NOFIT cell takes a FIT
    // neighbour of its 3 x 3 or 5 x 5 ring). The index holds every cell's class and its entry + 1.
    // (a grid without its distance field, buildGrid alone: every FIT cell; the entries left without a candidate are removed below)
    auto reach = [&](size_t i) { return grid.dist.empty() || std::isfinite(grid.dist[i]); };
    t.index.assign(n, 0u);
    std::vector<size_t> cellOf;
    for (size_t i = 0; i < n; ++i) {
        const bool fit = grid.cls[i] == FIT;
        const bool entry = reach(i) && fit;
        t.index[i] = (fit ? CHOICE_INDEX_FIT : 0u) | (entry ? uint32_t(cellOf.size() + 1) : 0u);
        if (entry) cellOf.push_back(i);
    }
    const size_t ne = cellOf.size();
    if (ne >= size_t(CHOICE_INDEX_MASK)) throw std::invalid_argument("buildChoiceTable: too many entries");
    // Empty slots; the class bit in every slot. The distances are merged in float (dist, CHOICE_K per entry) and quantized at the end.
    t.entries.resize(ne);
    std::vector<float> dist(ne * size_t(CHOICE_K), std::numeric_limits<float>::infinity());
    for (size_t k = 0; k < ne; ++k) {
        GpuNavChoiceCell& c = t.entries[k];
        const uint32_t fit = grid.cls[cellOf[k]] == FIT ? CHOICE_FIT : 0u;
        for (int m = 0; m < CHOICE_K; ++m) c.slot[m] = fit | (CHOICE_EMPTY << CHOICE_EXIT_SHIFT);
    }
    if (allFields) allFields->assign(size_t(t.exitCount), ExitField{});
    // The type rule: per entry and exit type the CHOICE_TYPE_MIN[type] nearest exits of that type (distance, slot word,
    // ascending); two types at most
    std::vector<int> exitType(size_t(t.exitCount), 0);
    int types = 1;
    for (int e = 0; e < t.exitCount; ++e) { exitType[size_t(e)] = geo.exitType(e); types = std::max(types, exitType[size_t(e)] + 1); }
    if (types > 2) throw std::invalid_argument("buildChoiceTable: at most two exit types");
    constexpr int TM = CHOICE_TYPE_MIN_MAX;
    std::vector<float> typeDist;
    std::vector<uint32_t> typeSlot;
    if (types == 2) {
        typeDist.assign(ne * 2 * TM, std::numeric_limits<float>::infinity());
        typeSlot.assign(ne * 2 * TM, 0u);
    }
    // Each exit's own search (sequential and deterministic), in parallel batches; merged in exit order. The merge's order is total
    // (distance, then exit id), so the table does not depend on the batch size or the thread count.
    // At most 4 GB of searches in flight (each: the ExitField and lazyThetaStar's arrays, about 24 bytes per cell, plus its
    // open list): venue L's 16 M cells take ~0.4 GB per exit, 8 at a time on a 16 GB machine
    const size_t perExit = n * 32, budget = size_t(4) << 30;
    const int memBatch = int(std::max<size_t>(1, budget / std::max<size_t>(perExit, 1)));
    const int batch = std::max(1, std::min(std::min(omp_get_max_threads(), memBatch), t.exitCount));
    // Progress: the per-exit fields done (BuildMonitor); a cancelled build returns from each search early and throws after the batch
    std::atomic<int> fieldsDone{ 0 };
    auto reportFields = [&](int done) {
        reportBuild("exit choice table: per-exit fields " + std::to_string(done) + " of " + std::to_string(t.exitCount),
                    double(done) / double(std::max(1, t.exitCount)));
    };
    reportFields(0);
    for (int e0 = 0; e0 < t.exitCount; e0 += batch) {
        const int e1 = std::min(t.exitCount, e0 + batch);
        std::vector<ExitField> fields(size_t(e1 - e0));
#pragma omp parallel for schedule(dynamic, 1)
        for (int e = e0; e < e1; ++e) {
            if (buildCancelRequested()) continue;
            fields[size_t(e - e0)] = buildExitField(grid, e);
            reportFields(++fieldsDone);
        }
        throwIfBuildCancelled();
        for (int e = e0; e < e1; ++e) {
            const ExitField& f = fields[size_t(e - e0)];
#pragma omp parallel for schedule(static)
            for (long long kk = 0; kk < (long long)ne; ++kk) {
                const size_t k = size_t(kk), i = cellOf[k];
                const float d = f.dist[i];
                if (!std::isfinite(d)) continue;
                GpuNavChoiceCell& c = t.entries[k];
                float* cd = &dist[k * size_t(CHOICE_K)];
                const uint32_t fit = c.slot[0] & CHOICE_FIT;
                int m = CHOICE_K;   // insertion position: before the first slot it beats (exits arrive in increasing id)
                while (m > 0 && d < cd[m - 1]) --m;
                if (m >= CHOICE_K) continue;
                for (int r = CHOICE_K - 1; r > m; --r) { c.slot[r] = c.slot[r - 1]; cd[r] = cd[r - 1]; }
                c.slot[m] = fit | (uint32_t(e) << CHOICE_EXIT_SHIFT) | uint32_t(f.anchor[i]);
                cd[m] = d;
            }
            if (types == 2) {   // the nearest of this exit's type (exits arrive in increasing id: ties keep the lower one)
                const int ty = exitType[size_t(e)], mt = CHOICE_TYPE_MIN[ty];
#pragma omp parallel for schedule(static)
                for (long long kk = 0; kk < (long long)ne; ++kk) {
                    const size_t k = size_t(kk), i = cellOf[k], j = (k * 2 + size_t(ty)) * TM;
                    const float d = f.dist[i];
                    if (!std::isfinite(d)) continue;
                    int m = mt;
                    while (m > 0 && d < typeDist[j + size_t(m - 1)]) --m;
                    if (m >= mt) continue;
                    for (int r = mt - 1; r > m; --r) { typeDist[j + size_t(r)] = typeDist[j + size_t(r - 1)]; typeSlot[j + size_t(r)] = typeSlot[j + size_t(r - 1)]; }
                    typeDist[j + size_t(m)] = d;
                    typeSlot[j + size_t(m)] = (t.entries[k].slot[0] & CHOICE_FIT) | (uint32_t(e) << CHOICE_EXIT_SHIFT) | uint32_t(f.anchor[i]);
                }
            }
            if (allFields) (*allFields)[size_t(e)] = std::move(fields[size_t(e - e0)]);
        }
    }
    long long swaps = 0;
    if (types == 2) {   // the type rule: the guaranteed nearest of each type first, then the nearest others, in ascending distance
#pragma omp parallel for schedule(static) reduction(+ : swaps)
        for (long long kk = 0; kk < (long long)ne; ++kk) {
            const size_t k = size_t(kk);
            GpuNavChoiceCell& c = t.entries[k];
            float* cd = &dist[k * size_t(CHOICE_K)];
            if (slotExit(c.slot[CHOICE_K - 1]) == CHOICE_EMPTY) continue;   // fewer reachable exits than slots: every one is there
            struct Cand { float d; uint32_t s; };
            Cand resl[CHOICE_K];
            int nres = 0;
            auto has = [&](uint32_t e) { for (int m = 0; m < nres; ++m) if (slotExit(resl[m].s) == e) return true; return false; };
            for (int ty = 0; ty < 2; ++ty)
                for (int m = 0; m < CHOICE_TYPE_MIN[ty] && nres < CHOICE_K; ++m) {
                    const size_t j = (k * 2 + size_t(ty)) * TM + size_t(m);
                    if (std::isfinite(typeDist[j])) resl[nres++] = { typeDist[j], typeSlot[j] };
                }
            for (int m = 0; m < CHOICE_K && nres < CHOICE_K; ++m)
                if (!has(slotExit(c.slot[m]))) resl[nres++] = { cd[m], c.slot[m] };
            std::sort(resl, resl + nres, [](const Cand& a, const Cand& b) { return a.d < b.d || (a.d == b.d && slotExit(a.s) < slotExit(b.s)); });
            bool changed = false;
            for (int m = 0; m < nres; ++m) {
                changed |= c.slot[m] != resl[m].s;
                c.slot[m] = resl[m].s;
                cd[m] = resl[m].d;
            }
            swaps += changed;
        }
    }
    t.typeSwaps = swaps;
    {   // entries without any candidate (no exit reaches the cell) are removed: the index's entry 0 means "no candidates"
        size_t w = 0;
        for (size_t k = 0; k < ne; ++k) {
            const size_t i = cellOf[k];
            if (slotExit(t.entries[k].slot[0]) == CHOICE_EMPTY) { t.index[i] &= CHOICE_INDEX_FIT; continue; }
            if (w != k) {
                t.entries[w] = t.entries[k];
                std::copy(dist.begin() + std::ptrdiff_t(k * size_t(CHOICE_K)), dist.begin() + std::ptrdiff_t((k + 1) * size_t(CHOICE_K)),
                          dist.begin() + std::ptrdiff_t(w * size_t(CHOICE_K)));
                cellOf[w] = i;
            }
            t.index[i] = (t.index[i] & CHOICE_INDEX_FIT) | uint32_t(w + 1);
            ++w;
        }
        t.entries.resize(w);
        cellOf.resize(w);
    }
    const size_t nk = t.entries.size();
    // The distances in 16 bits: the nearest multiple of the table's distQuantum (empty slots 0xFFFF)
    float maxD = 0.0f;
    for (size_t k = 0; k < nk; ++k) {
        GpuNavChoiceCell& c = t.entries[k];
        for (int w = 0; w < CHOICE_DIST_WORDS; ++w) c.dist[w] = 0u;
        for (int m = 0; m < CHOICE_K; ++m) {
            const float d = dist[k * size_t(CHOICE_K) + size_t(m)];
            uint32_t q = CHOICE_DIST_EMPTY;
            if (std::isfinite(d)) {
                const double qd = std::nearbyint(double(d) / double(t.distQuantum));
                if (qd >= double(CHOICE_DIST_EMPTY)) throw std::invalid_argument("buildChoiceTable: a candidate distance beyond the 16-bit range");
                q = uint32_t(qd);
                maxD = std::max(maxD, d);
            }
            c.dist[m >> 1] |= q << ((m & 1) * 16);
        }
    }
    t.maxDist = maxD;
    t.buildSeconds = std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count();
    return t;
}

// --- The cache ---

namespace {

struct Fnv {
    uint64_t h = 0xcbf29ce484222325ull;
    void bytes(const void* p, size_t n) {
        const unsigned char* b = static_cast<const unsigned char*>(p);
        for (size_t i = 0; i < n; ++i) { h ^= b[i]; h *= 0x100000001b3ull; }
    }
};

constexpr char MAGIC[8] = { 'S', 'W', 'C', 'H', 'O', 'I', '0', '1' };

} // namespace

uint64_t choiceCacheKey(const Venue& v) {
    std::ostringstream s;
    s << "swarm-choice|" << CHOICE_VERSION << "|" << CHOICE_K << "|" << std::hex << cacheKey(v);
    const std::string text = s.str();
    Fnv h;
    h.bytes(text.data(), text.size());
    return h.h;
}

std::filesystem::path choiceCacheFile(const Venue& v) {
    char b[96];
    std::snprintf(b, sizeof b, "nav_%s_choice_%016llx.bin", v.name, (unsigned long long)choiceCacheKey(v));
    return cacheDir() / b;
}

uint64_t choiceContentHash(const ChoiceTable& t) {
    Fnv h;
    h.bytes(&t.grid.res, sizeof t.grid.res);
    h.bytes(t.index.data(), t.index.size() * 4);
    h.bytes(t.entries.data(), t.entries.size() * sizeof(GpuNavChoiceCell));
    return h.h;
}

bool saveChoice(const ChoiceTable& t, const std::filesystem::path& file) {
    std::error_code ec;
    std::filesystem::create_directories(file.parent_path(), ec);
    std::ostringstream body(std::ios::binary);
    auto put = [&](const void* p, size_t n) { body.write(static_cast<const char*>(p), std::streamsize(n)); };
    const uint32_t version = CHOICE_VERSION, k = CHOICE_K, res = uint32_t(t.grid.res), exits = uint32_t(t.exitCount);
    put(&version, 4);
    put(&k, 4);
    put(&res, 4);
    put(&t.grid.origin, 4);
    put(&t.grid.cell, 4);
    put(&t.grid.invCell, 4);
    put(&exits, 4);
    put(&t.key, 8);
    const uint64_t ne = t.entries.size();
    put(&ne, 8);
    put(t.index.data(), t.index.size() * 4);
    put(t.entries.data(), t.entries.size() * sizeof(GpuNavChoiceCell));
    for (int e = 0; e < t.exitCount; ++e) {
        put(&t.exitWidthM[size_t(e)], 8);
        const uint32_t len = uint32_t(t.exitNames[size_t(e)].size());
        put(&len, 4);
        put(t.exitNames[size_t(e)].data(), len);
    }
    const std::string payload = body.str();
    Fnv h;
    h.bytes(payload.data(), payload.size());
    const std::filesystem::path tmp = file.string() + ".tmp" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count());
    {
        std::ofstream o(tmp, std::ios::binary | std::ios::trunc);
        if (!o) return false;
        o.write(MAGIC, 8);
        o.write(payload.data(), std::streamsize(payload.size()));
        o.write(reinterpret_cast<const char*>(&h.h), 8);
        if (!o) return false;
    }
    std::filesystem::rename(tmp, file, ec);
    if (ec) { std::filesystem::remove(tmp, ec); return false; }
    return true;
}

bool loadChoice(ChoiceTable& t, const std::filesystem::path& file, uint64_t expectedKey, double metresPerUnit) {
    CacheFileReader in;   // straight into the vectors (nav_field.hpp)
    if (!in.open(file, MAGIC)) return false;
    uint32_t version = 0, k = 0, res = 0, exits = 0;
    ChoiceTable r;
    if (!in.read(&version, 4) || !in.read(&k, 4) || !in.read(&res, 4) || !in.read(&r.grid.origin, 4) || !in.read(&r.grid.cell, 4) || !in.read(&r.grid.invCell, 4) ||
        !in.read(&exits, 4) || !in.read(&r.key, 8))
        return false;
    if (version != CHOICE_VERSION || k != uint32_t(CHOICE_K) || r.key != expectedKey || res == 0 || res > 100000 || exits > uint32_t(CHOICE_MAX_EXITS))
        return false;
    r.grid.res = int(res);
    r.exitCount = int(exits);
    uint64_t ne = 0;
    if (!in.read(&ne, 8) || ne > r.grid.cells()) return false;
    if (!in.readVector(r.index, r.grid.cells()) || !in.readVector(r.entries, size_t(ne))) return false;
    for (uint32_t e = 0; e < exits; ++e) {
        double w = 0.0;
        uint32_t len = 0;
        if (!in.read(&w, 8) || !in.read(&len, 4) || len > 1000) return false;
        std::string name(len, '\0');
        if (!in.read(name.data(), len)) return false;
        r.exitWidthM.push_back(w);
        r.exitNames.push_back(name);
    }
    if (!in.finish()) return false;
    setChoiceCapacities(r, metresPerUnit);
    t = std::move(r);
    return true;
}

ChoiceEntryCount choiceEntryCountBeforeBuild(const Venue& v) {
    if (!hasField(v)) return {};
    std::ifstream in(choiceCacheFile(v), std::ios::binary);
    char magic[8] = {};
    uint32_t version = 0, k = 0, res = 0, exits = 0;
    float origin = 0.0f, cell = 0.0f, invCell = 0.0f;
    uint64_t key = 0, entries = 0;
    const auto get = [&](void* p, size_t n) { return bool(in.read(static_cast<char*>(p), std::streamsize(n))); };
    if (in && get(magic, 8) && get(&version, 4) && get(&k, 4) && get(&res, 4) && get(&origin, 4) && get(&cell, 4) && get(&invCell, 4) && get(&exits, 4) &&
        get(&key, 8) && get(&entries, 8) && std::memcmp(magic, MAGIC, 8) == 0 && version == CHOICE_VERSION && k == uint32_t(CHOICE_K) && key == choiceCacheKey(v))
        return { entries, true };
    return { choiceEntryUpperBound(v), false };
}

uint64_t choiceEntryUpperBound(const Venue& v) { return uint64_t(std::ceil(seated::areas(v.layout).occupiable() / (CELL_M * CELL_M))); }

const ChoiceTable& choiceForVenue(const Venue& v) {
    if (!hasField(v)) throw std::invalid_argument(std::string("nav::choiceForVenue: venue ") + v.name + " has no navigation field");
    static std::mutex mutex;
    static std::map<const Venue*, std::unique_ptr<ChoiceTable>> tables;
    const Field& grid = forVenue(v);   // outside the lock: forVenue locks its own
    std::lock_guard<std::mutex> lock(mutex);
    std::unique_ptr<ChoiceTable>& slot = tables[&v];
    if (slot) return *slot;
    const auto t0 = std::chrono::steady_clock::now();
    const uint64_t key = choiceCacheKey(v);
    const std::filesystem::path file = choiceCacheFile(v);
    auto t = std::make_unique<ChoiceTable>();
    reportBuild("exit choice table: reading the cache file", -1.0);
    if (loadChoice(*t, file, key, units::M_PER_UNIT)) {
        t->fromCache = true;
        t->buildSeconds = std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count();
        std::printf("exit choice table of venue %s: loaded from %s (%.2f s)\n", v.name, file.string().c_str(), t->buildSeconds);
    } else {
        *t = buildChoiceTable(SeatedGeometry(v.layout), grid);   // BuildCancelled leaves the slot empty and writes nothing
        t->key = key;
        reportBuild("exit choice table: saving the cache file", -1.0);
        const bool saved = saveChoice(*t, file);   // a temporary file renamed when complete
        std::printf("exit choice table of venue %s: built in %.2f s (%d per-exit fields, %d candidates per cell, %.1f MB), %s %s\n", v.name,
                    t->buildSeconds, t->exitCount, CHOICE_K, double(t->bytes()) / 1048576.0, saved ? "saved to" : "NOT saved to", file.string().c_str());
    }
    std::fflush(stdout);
    t->surface = &v.layout;   // the surface rule (choiceCell)
    slot = std::move(t);
    return *slot;
}

std::string choicePreambleDefines(const ChoiceTable& t) {
    std::ostringstream s;
    auto f = [&s](const char* name, float v) { s << "#define " << name << " " << glslFloatLiteral(v) << "\n"; };
    s << "// ---- exit choice: queue-aware (swarm/exit_choice.hpp) ----\n"
      << "#define VENUE_EXIT_CHOICE 1\n";
    f("NAV_CELL", t.grid.cell);
    s << "#define NAV_EXITS " << t.exitCount << "\n"
      << "#define NAV_CHOICE_EXIT_SHIFT " << CHOICE_EXIT_SHIFT << "\n"
      << "#define NAV_CHOICE_ANCHOR_MASK " << CHOICE_ANCHOR_MASK << "u\n"
      << "#define NAV_CHOICE_EMPTY " << CHOICE_EMPTY << "u\n"
      << "#define NAV_CHOICE_FIT " << CHOICE_FIT << "u\n"
      << "#define NAV_CHOICE_NONE " << CHOICE_NONE << "u\n"
      << "#define NAV_CHOICE_QUEUE_STRIDE " << CHOICE_QUEUE_STRIDE << "u\n"
      << "#define NAV_CHOICE_AHEAD_BINS " << CHOICE_AHEAD_BINS << "u\n"
      << "#define NAV_CHOICE_AHEAD_SHIFT " << CHOICE_AHEAD_SHIFT << "u\n"
      << "#define NAV_CHOICE_K " << CHOICE_K << "\n"
      << "#define NAV_CHOICE_DIST_WORDS " << CHOICE_DIST_WORDS << "\n"
      << "#define NAV_CHOICE_INDEX_MASK " << CHOICE_INDEX_MASK << "u\n"
      << "#define NAV_CHOICE_DIST_EMPTY " << CHOICE_DIST_EMPTY << "u\n";
    f("NAV_CHOICE_DIST_QUANTUM", t.distQuantum);

    f("NAV_CHOICE_S_PER_UNIT", t.secondsPerUnit);
    f("T_CHOICE", T_CHOICE);
    f("CHOICE_REL_MARGIN", CHOICE_REL_MARGIN);
    f("CHOICE_ABS_MARGIN_S", CHOICE_ABS_MARGIN_S);
    f("CHOICE_SWITCH_SHARE", CHOICE_SWITCH_SHARE);
    s << "#define CHOICE_MIN_SWITCHES " << CHOICE_MIN_SWITCHES << "\n"
      << "#define CHOICE_GAIN_BINS " << CHOICE_GAIN_BINS << "\n";
    s << "const float NAV_EXIT_INV_CAP[NAV_EXITS] = float[](";
    for (int e = 0; e < t.exitCount; ++e) s << (e ? ", " : "") << glslFloatLiteral(t.invCapS[size_t(e)]);
    s << ");\n";
    return s.str();
}

// --- The CPU mirror ---

int choiceCell(const ChoiceTable& t, glm::vec2 x) {   // physics.comp navChoiceCell
    const Grid& gr = t.grid;
    const glm::vec2 g = (x - glm::vec2(gr.origin)) * gr.invCell;
    const glm::ivec2 c = gr.cellOf(x);
    int i = gr.index(c.x, c.y);
    if (!t.fit(size_t(i))) {   // a NOFIT cell: the FIT neighbour with candidates whose centre is nearest to x; none in the 3 x 3
        float best = 1e9f;     // ring: the nearest of the 5 x 5 ring's outer cells (none: its own, without candidates: no path)
        for (int r = 1; r <= 2 && best == 1e9f; r++)
            for (int dy = -r; dy <= r; dy++)
                for (int dx = -r; dx <= r; dx++) {
                    if (std::max(std::abs(dx), std::abs(dy)) != r) continue;
                    const glm::ivec2 m = c + glm::ivec2(dx, dy);
                    if (m.x < 0 || m.y < 0 || m.x >= gr.res || m.y >= gr.res) continue;
                    const int j = gr.index(m.x, m.y);
                    if (!t.fit(size_t(j)) || !t.reachable(size_t(j))) continue;
                    const glm::vec2 q = g - (glm::vec2(m) + 0.5f);
                    const float d2 = q.x * q.x + q.y * q.y;
                    if (d2 < best) { best = d2; i = j; }
                }
    }
    if (t.surface && !surfaceReaches(*t.surface, x, surfaceCellCentre(gr, i))) {   // the surface rule (physics.comp navChoiceCell)
        float best = 1e9f;
        int pick = i;
        for (int dy = -1; dy <= 1; dy++)
            for (int dx = -1; dx <= 1; dx++) {
                const glm::ivec2 m = c + glm::ivec2(dx, dy);
                if (m.x < 0 || m.y < 0 || m.x >= gr.res || m.y >= gr.res) continue;
                const int j = gr.index(m.x, m.y);
                if (j == i || !t.fit(size_t(j)) || !t.reachable(size_t(j))) continue;
                const glm::vec2 q = g - (glm::vec2(m) + 0.5f);
                const float d2 = q.x * q.x + q.y * q.y;
                if (d2 < best && surfaceReaches(*t.surface, x, surfaceCellCentre(gr, j))) { best = d2; pick = j; }
            }
        i = pick;
    }
    return i;
}

glm::vec2 anchorCentre(const ChoiceTable& t, uint32_t a) {   // physics.comp navAnchorCentre
    const uint32_t res = uint32_t(t.grid.res);
    const float cx = float(a % res) + 0.5f, cy = float(a / res) + 0.5f;
    const float px = cx * t.grid.cell, py = cy * t.grid.cell;
    return glm::vec2(t.grid.origin + px, t.grid.origin + py);
}

glm::vec2 choiceDirection(const ChoiceTable& t, glm::vec2 x, uint32_t exit) {   // physics.comp navChoiceDirection
    const GpuNavChoiceCell& c = t.at(size_t(choiceCell(t, x)));
    for (int k = 0; k < CHOICE_K; ++k) {
        if (slotExit(c.slot[k]) != exit) continue;   // (the exit appears at most once)
        const glm::vec2 d = anchorCentre(t, slotAnchor(c.slot[k])) - x;
        const float l = glm::length(d);
        return l > GOAL_DEADZONE ? d / l : glm::vec2(0.0f);
    }
    return glm::vec2(0.0f);
}

glm::vec2 choiceGoal(const ChoiceTable& t, const SeatedLayout& L, glm::vec3 p, uint32_t exit) {   // physics.comp navChoiceGoal
    glm::vec2 e = choiceDirection(t, glm::vec2(p), exit);
    const glm::vec3 w = seated::wall(L, p, FEELER_REACH);
    const float into = glm::dot(e, glm::vec2(w));
    if (w.z < FEELER_REACH && into < 0.0f) {
        e -= glm::vec2(w) * into;
        const float l = glm::length(e);
        e = l > SAFE_NORMALIZE_EPS ? e / l : glm::vec2(0.0f);
    }
    return e;
}

float estimatedTime(const ChoiceTable& t, float dist, uint32_t exit, uint32_t queued) {   // physics.comp navEstimate
    const float walk = dist * t.secondsPerUnit;
    const float wait = float(queued) * t.invCapS[size_t(exit)];
    return walk + wait;
}

int slotOf(const GpuNavChoiceCell& c, uint32_t exit) {   // physics.comp navSlotOf
    int k = -1;
    for (int i = 0; i < CHOICE_K; ++i)
        if (slotExit(c.slot[i]) == exit) k = i;
    return k;
}

int bestCandidate(const ChoiceTable& t, const GpuNavChoiceCell& c, const uint32_t* ahead, float& eBest) {   // physics.comp navBest
    int best = -1;
    eBest = 0.0f;
    for (int k = 0; k < CHOICE_K; ++k) {
        const uint32_t ex = slotExit(c.slot[k]);
        if (ex == CHOICE_EMPTY) break;
        const float e = estimatedTime(t, slotDist(t, c, k), ex, aheadOf(ahead, ex, slotDistQ(c, k)));
        if (best < 0 || e < eBest) { best = k; eBest = e; }
    }
    return best;
}

Evaluation evaluate(const ChoiceTable& t, glm::vec3 p, uint32_t current, const uint32_t* ahead) {   // physics.comp stage 1
    Evaluation r;
    const GpuNavChoiceCell& c = t.at(size_t(choiceCell(t, glm::vec2(p))));
    if (slotExit(c.slot[0]) == CHOICE_EMPTY) return r;
    const int curK = slotOf(c, current);
    if (curK < 0) return r;
    r.evaluated = true;
    float eBest;
    const int best = bestCandidate(t, c, ahead, eBest);
    const float eCur = estimatedTime(t, slotDist(t, c, curK), current, aheadOf(ahead, current, slotDistQ(c, curK)));
    const float gain = eCur - eBest;
    r.gain = gain;
    if (best != curK && gain > std::max(CHOICE_REL_MARGIN * eCur, CHOICE_ABS_MARGIN_S)) {
        r.eligible = true;
        r.best = slotExit(c.slot[best]);
        r.bin = std::min(uint32_t(gain), uint32_t(CHOICE_GAIN_BINS - 1));
    }
    return r;
}

uint32_t switchThreshold(const uint32_t* hist, uint32_t queued) {   // physics.comp stage 2
    const uint32_t cap = std::max(uint32_t(CHOICE_MIN_SWITCHES), uint32_t(float(queued) * CHOICE_SWITCH_SHARE));
    uint32_t cum = 0, thr = uint32_t(CHOICE_GAIN_BINS);
    for (int b = CHOICE_GAIN_BINS - 1; b >= 0; --b) {
        const uint32_t c = hist[b];
        if (c == 0) continue;
        if (cum + c > cap) {
            if (cum == 0) thr = uint32_t(b);   // the highest bin alone exceeds the cap: it switches anyway
            break;
        }
        cum += c;
        thr = uint32_t(b);
    }
    return thr;
}

Applied apply(const ChoiceTable& t, glm::vec3 p, uint32_t current, const uint32_t* ahead, const Evaluation* pending, const uint32_t* threshold) {
    Applied r;
    r.exit = current;
    const GpuNavChoiceCell& c = t.at(size_t(choiceCell(t, glm::vec2(p))));
    const bool hasPath = slotExit(c.slot[0]) != CHOICE_EMPTY;
    const int curK = hasPath ? slotOf(c, current) : -1;
    if (hasPath && curK < 0) {   // forced (or the first choice)
        float eBest;
        r.exit = slotExit(c.slot[bestCandidate(t, c, ahead, eBest)]);
        r.forced = current != CHOICE_NONE;
    } else if (pending && curK >= 0 && pending->eligible && pending->bin >= threshold[current]) {
        r.exit = pending->best;
        r.switched = true;
    }
    return r;
}

std::vector<uint32_t> aheadPrefixOf(const uint32_t* raw) {
    std::vector<uint32_t> p(size_t(CHOICE_QUEUE_STRIDE) * CHOICE_AHEAD_BINS);
    for (int e = 0; e < CHOICE_QUEUE_STRIDE; ++e) {
        uint32_t run = 0;
        for (int b = 0; b < CHOICE_AHEAD_BINS; ++b) {
            const size_t i = size_t(e) * CHOICE_AHEAD_BINS + size_t(b);
            p[i] = run;
            run += raw[i];
        }
    }
    return p;
}

void ChoiceState::reset(size_t agents) {
    assign.assign(agents, CHOICE_NONE);
    counters = GpuChoiceCounters{};
    step = 0;
    pending.assign(agents, Evaluation{});
    hist.assign(size_t(CHOICE_MAX_EXITS) * CHOICE_GAIN_BINS, 0u);
    threshold.assign(size_t(CHOICE_MAX_EXITS), uint32_t(CHOICE_GAIN_BINS));
    ahead.assign(size_t(2) * CHOICE_QUEUE_STRIDE * CHOICE_AHEAD_BINS, 0u);
}

// physics.comp PHYSICS_PASS 0's four stages in order, sequential in agent order: the stages read only the previous step's counts and
// integer sums, so the GPU's atomics give the same result
void choiceStep(const ChoiceTable& t, const std::vector<GpuBoid>& state, ChoiceState& s, int choiceSteps, int threads) {
    const uint32_t qRead = (s.step & 1u) * uint32_t(CHOICE_QUEUE_STRIDE), qWrite = uint32_t(CHOICE_QUEUE_STRIDE) - qRead;
    const uint32_t* queue = s.counters.queue + qRead;
    const bool evalStep = evaluationStep(s.step, choiceSteps);
    const size_t n = state.size();
    // The prefix stage (3): the read parity's histograms to exclusive prefix sums (the queue ahead), the write parity's cleared
    const size_t perParity = size_t(CHOICE_QUEUE_STRIDE) * CHOICE_AHEAD_BINS;
    uint32_t* aRead = s.ahead.data() + (s.step & 1u) * perParity;
    uint32_t* aWrite = s.ahead.data() + (1u - (s.step & 1u)) * perParity;
    for (int e = 0; e < t.exitCount; ++e) {
        uint32_t run = 0;
        for (int b = 0; b < CHOICE_AHEAD_BINS; ++b) {
            const size_t i = size_t(e) * CHOICE_AHEAD_BINS + size_t(b);
            const uint32_t h = aRead[i];
            aRead[i] = run;
            run += h;
            aWrite[i] = 0u;
        }
    }
    const int ni = int(n);
    if (evalStep) {
        if (threads <= 1) {
            for (size_t i = 0; i < n; ++i) {
                s.pending[i] = Evaluation{};
                const glm::vec4 p = state[i].position;
                if (p.w == 0.0f) continue;
                s.pending[i] = evaluate(t, glm::vec3(p), s.assign[i], aRead);
                s.counters.evaluations += s.pending[i].evaluated;
                if (s.pending[i].eligible) {
                    ++s.hist[size_t(s.assign[i]) * CHOICE_GAIN_BINS + s.pending[i].bin];
                    ++s.counters.eligible;
                }
            }
        } else {   // the same evaluations and integer counts, in parallel
            long long evaluations = 0, eligible = 0;
            Evaluation* pending = s.pending.data();
            uint32_t* hist = s.hist.data();
            const uint32_t* assign = s.assign.data();
#pragma omp parallel for schedule(dynamic, 64) num_threads(threads) reduction(+ : evaluations, eligible)
            for (int i = 0; i < ni; ++i) {
                pending[i] = Evaluation{};
                const glm::vec4 p = state[size_t(i)].position;
                if (p.w == 0.0f) continue;
                pending[i] = evaluate(t, glm::vec3(p), assign[i], aRead);
                evaluations += pending[i].evaluated ? 1 : 0;
                if (pending[i].eligible) {
                    uint32_t& h = hist[size_t(assign[i]) * CHOICE_GAIN_BINS + pending[i].bin];
#pragma omp atomic
                    ++h;
                    ++eligible;
                }
            }
            s.counters.evaluations += uint32_t(evaluations);
            s.counters.eligible += uint32_t(eligible);
        }
        for (int e = 0; e < t.exitCount; ++e) {
            uint32_t* h = s.hist.data() + size_t(e) * CHOICE_GAIN_BINS;
            s.threshold[size_t(e)] = switchThreshold(h, queue[e]);
            std::fill(h, h + CHOICE_GAIN_BINS, 0u);
        }
    }
    std::fill(s.counters.queue + qWrite, s.counters.queue + qWrite + CHOICE_QUEUE_STRIDE, 0u);
    if (threads <= 1) {
        for (size_t i = 0; i < n; ++i) {
            const glm::vec4 p = state[i].position;
            if (p.w == 0.0f) continue;
            const Applied a = apply(t, glm::vec3(p), s.assign[i], aRead, evalStep ? &s.pending[i] : nullptr, s.threshold.data());
            s.assign[i] = a.exit;
            if (a.exit != CHOICE_NONE) ++s.counters.queue[qWrite + a.exit];
            {   // the queue ahead, at the agent's own distance to its exit (none without a path: no candidate)
                const GpuNavChoiceCell& c = t.at(size_t(choiceCell(t, glm::vec2(p))));
                const int k = slotOf(c, a.exit);
                if (k >= 0) ++aWrite[size_t(a.exit) * CHOICE_AHEAD_BINS + aheadBin(slotDistQ(c, k))];
            }
            s.counters.switches += a.switched;
            s.counters.forced += a.forced;
        }
    } else {   // the same applied exits and integer counts, in parallel
        long long switches = 0, forced = 0;
        uint32_t* assign = s.assign.data();
        uint32_t* queueW = s.counters.queue + qWrite;
        const Evaluation* pending = s.pending.data();
        const uint32_t* threshold = s.threshold.data();
#pragma omp parallel for schedule(dynamic, 64) num_threads(threads) reduction(+ : switches, forced)
        for (int i = 0; i < ni; ++i) {
            const glm::vec4 p = state[size_t(i)].position;
            if (p.w == 0.0f) continue;
            const Applied a = apply(t, glm::vec3(p), assign[i], aRead, evalStep ? &pending[i] : nullptr, threshold);
            assign[i] = a.exit;
            if (a.exit != CHOICE_NONE) {
                uint32_t& q = queueW[a.exit];
#pragma omp atomic
                ++q;
            }
            const GpuNavChoiceCell& c = t.at(size_t(choiceCell(t, glm::vec2(p))));
            const int k = slotOf(c, a.exit);
            if (k >= 0) {
                uint32_t& h = aWrite[size_t(a.exit) * CHOICE_AHEAD_BINS + aheadBin(slotDistQ(c, k))];
#pragma omp atomic
                ++h;
            }
            switches += a.switched ? 1 : 0;
            forced += a.forced ? 1 : 0;
        }
        s.counters.switches += uint32_t(switches);
        s.counters.forced += uint32_t(forced);
    }
    ++s.step;
}

} // namespace nav
} // namespace swarm
