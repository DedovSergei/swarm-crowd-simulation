#pragma once

// Shared by the benchmark tools in tools/benchmark (benchmark_crowd, cpu_tune, cpu_profile, gpu_diag):
// hidden GL context, workload snapshots, run metadata, order statistics, process QoS.

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>   // SetProcessInformation; before glad, which then keeps windows.h's APIENTRY
#endif
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <swarm/crowd_sim.hpp>
#include <swarm/gpu_types.hpp>
#include <swarm/sim_params.hpp>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

#ifdef _MSC_VER
#include <intrin.h>
#endif

// Build-time commit metadata. __has_include: tools/perf_ab/bench.cpp includes this
// header and also builds against older engine versions, which have no build_info.
#if __has_include(<swarm/build_info.hpp>)
#include <swarm/build_info.hpp>
#define SWARM_HAS_BUILD_INFO 1
#endif

// Configure-time build facts (CMakeLists.txt, benchmark targets)
#ifndef SWARM_BUILD_TYPE
#define SWARM_BUILD_TYPE "unknown"
#endif
#ifndef SWARM_CORE_FLAGS
#define SWARM_CORE_FLAGS "unknown"
#endif

namespace bench {

namespace fs = std::filesystem;
using swarm::GpuBoid;

// --- Hidden OpenGL 4.3 core context ---
inline GLFWwindow* createHiddenContext(const char* title) {
    if (!glfwInit()) throw std::runtime_error("glfwInit failed");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    GLFWwindow* w = glfwCreateWindow(64, 64, title, nullptr, nullptr);
    if (!w) throw std::runtime_error("no OpenGL 4.3 core context");
    glfwMakeContextCurrent(w);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) throw std::runtime_error("glad failed");
    return w;
}

// The commit the binary was built from, determined at build time (swarm_build_info)
inline std::string gitCommit() {      // full SHA-1, or "unknown"
#ifdef SWARM_HAS_BUILD_INFO
    return swarm::buildinfo::gitCommit();
#else
    return "unknown";
#endif
}
inline std::string gitDirty() {       // "1", "0" or "unknown" (a CSV field)
#ifdef SWARM_HAS_BUILD_INFO
    return swarm::buildinfo::gitDirtyField();
#else
    return "unknown";
#endif
}
inline std::string gitDescribe() {    // "<short>" or "<short>-dirty", or "unknown"
#ifdef SWARM_HAS_BUILD_INFO
    return swarm::buildinfo::gitDescribe();
#else
    return "unknown";
#endif
}

inline std::string glRenderer() { return (const char*)glGetString(GL_RENDERER); }
inline std::string glDriver() { return (const char*)glGetString(GL_VERSION); }

template <class T>
std::vector<T> readBuffer(GLuint buf, size_t count) {
    glMemoryBarrier(GL_BUFFER_UPDATE_BARRIER_BIT);
    std::vector<T> out(count);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, buf);
    glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, GLsizeiptr(count * sizeof(T)), out.data());
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    return out;
}

// --- Workload snapshots: <dir>/<state>_<n>.bin, raw GpuBoid arrays ---
// spawn:     spawnBleacherCrowd(n)
// congested: the GPU state after CONGESTED_STEPS steps from spawn (the build that wrote it)
constexpr int CONGESTED_STEPS = 250;

inline fs::path snapshotPath(const fs::path& dir, const std::string& state, int n) {
    return dir / (state + "_" + std::to_string(n) + ".bin");
}

inline void saveSnapshot(const fs::path& path, const std::vector<GpuBoid>& s) {
    std::ofstream out(path, std::ios::binary);
    out.write(reinterpret_cast<const char*>(s.data()), std::streamsize(s.size() * sizeof(GpuBoid)));
    if (!out) throw std::runtime_error("cannot write " + path.string());
}

inline std::vector<GpuBoid> loadSnapshot(const fs::path& dir, const std::string& state, int n) {
    const fs::path path = snapshotPath(dir, state, n);
    std::vector<GpuBoid> s(static_cast<size_t>(n));
    std::ifstream in(path, std::ios::binary | std::ios::ate);
    if (!in || in.tellg() != std::streamoff(n * sizeof(GpuBoid)))
        throw std::runtime_error("missing or wrong-size snapshot " + path.string() + " (run the 'snapshots' command first)");
    in.seekg(0);
    in.read(reinterpret_cast<char*>(s.data()), std::streamsize(s.size() * sizeof(GpuBoid)));
    return s;
}

// --- The thesis benchmark's workloads (benchmark_crowd thesis, cpu_tune, cpu_profile): <dir>/<key>_<state>.bin, key = venue_<V>
// (S, M, L at 100% load, every seat, in buffers of 4 096 / 16 384 / 65 536) or terrace_<N>; written by 'benchmark_crowd thesis' ---
inline int venueBufferN(const std::string& venue) { return venue == "S" ? 4096 : venue == "M" ? 16384 : venue == "L" ? 65536 : 0; }
inline std::string workloadKey(const std::string& venue, int n) { return venue == "terrace" ? "terrace_" + std::to_string(n) : "venue_" + venue; }
inline fs::path workloadSnapshotPath(const fs::path& dir, const std::string& venue, int n, const std::string& state) {
    return dir / (workloadKey(venue, n) + "_" + state + ".bin");
}
inline std::vector<GpuBoid> loadWorkloadSnapshot(const fs::path& dir, const std::string& venue, int n, const std::string& state) {
    const fs::path path = workloadSnapshotPath(dir, venue, n, state);
    std::vector<GpuBoid> s(static_cast<size_t>(n));
    std::ifstream in(path, std::ios::binary | std::ios::ate);
    if (!in || in.tellg() != std::streamoff(size_t(n) * sizeof(GpuBoid)))
        throw std::runtime_error("missing or wrong-size snapshot " + path.string() + " (run 'benchmark_crowd thesis --plan' first)");
    in.seekg(0);
    in.read(reinterpret_cast<char*>(s.data()), std::streamsize(s.size() * sizeof(GpuBoid)));
    return s;
}

inline long countActive(const std::vector<GpuBoid>& s) {
    return long(std::count_if(s.begin(), s.end(), [](const GpuBoid& b) { return b.position.w != 0.0f; }));
}

// Occupancy of the 2D hash grid: agents per occupied cell over the active agents
struct Occupancy { long active = 0; int occupiedCells = 0; double meanPerCell = 0; int maxPerCell = 0; double meanCandidates = 0; };
inline Occupancy occupancy(const std::vector<GpuBoid>& s) {
    std::vector<int> cells(size_t(swarm::GRID_RES) * swarm::GRID_RES, 0);
    Occupancy o;
    std::vector<int> cellOf;
    for (const GpuBoid& b : s) {
        if (b.position.w == 0.0f) continue;
        int x = std::clamp(int((b.position.x - swarm::DOMAIN_MIN) / swarm::DOMAIN_SPAN * float(swarm::GRID_RES)), 0, swarm::GRID_RES - 1);
        int y = std::clamp(int((b.position.y - swarm::DOMAIN_MIN) / swarm::DOMAIN_SPAN * float(swarm::GRID_RES)), 0, swarm::GRID_RES - 1);
        ++cells[size_t(x + y * swarm::GRID_RES)];
        cellOf.push_back(x + y * swarm::GRID_RES);
        ++o.active;
    }
    for (int c : cells) { o.occupiedCells += c > 0; o.maxPerCell = std::max(o.maxPerCell, c); }
    o.meanPerCell = o.occupiedCells ? double(o.active) / o.occupiedCells : 0.0;
    double cand = 0;   // agents in the 3x3 ring, averaged over agents (the neighbour loop's trip count)
    for (int c : cellOf) {
        const int cx = c % swarm::GRID_RES, cy = c / swarm::GRID_RES;
        for (int dy = -1; dy <= 1; ++dy)
            for (int dx = -1; dx <= 1; ++dx) {
                const int nx = cx + dx, ny = cy + dy;
                if (nx >= 0 && nx < swarm::GRID_RES && ny >= 0 && ny < swarm::GRID_RES) cand += cells[size_t(nx + ny * swarm::GRID_RES)];
            }
    }
    o.meanCandidates = cellOf.empty() ? 0.0 : cand / double(cellOf.size());
    return o;
}

// --- Metadata ---
inline std::string cpuBrand() {
#ifdef _MSC_VER
    int regs[4] = {};
    __cpuid(regs, int(0x80000000u));
    if (unsigned(regs[0]) < 0x80000004u) return "unknown";
    char brand[49] = {};
    for (int i = 0; i < 3; ++i) {
        __cpuid(regs, int(0x80000002u + i));
        std::memcpy(brand + 16 * i, regs, 16);
    }
    std::string s(brand);
    s.erase(0, s.find_first_not_of(' '));
    s.erase(s.find_last_not_of(' ') + 1);
    return s;
#else
    return "unknown";
#endif
}

inline unsigned logicalCores() { return std::thread::hardware_concurrency(); }

inline std::string localTimestamp(const char* fmt) {
    const std::time_t t = std::time(nullptr);
    std::tm tm{};
#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    char buf[64];
    std::strftime(buf, sizeof buf, fmt, &tm);
    return buf;
}

// CSV field: quoted when it contains a separator or a quote
inline std::string csvField(const std::string& s) {
    if (s.find_first_of(",\"\n") == std::string::npos) return s;
    std::string q = "\"";
    for (char c : s) q += c == '"' ? std::string("\"\"") : std::string(1, c);
    return q + "\"";
}

// --- Order statistics over per-step times ---
struct Stats { double median = 0, p5 = 0, p95 = 0, mean = 0, cv = 0, min = 0, max = 0; size_t n = 0; };

inline double percentile(const std::vector<double>& sorted, double p) {   // linear interpolation
    if (sorted.empty()) return 0.0;
    const double r = p * double(sorted.size() - 1);
    const size_t i = size_t(r);
    const double f = r - double(i);
    return i + 1 < sorted.size() ? sorted[i] * (1.0 - f) + sorted[i + 1] * f : sorted[i];
}

inline Stats stats(std::vector<double> v) {
    Stats s;
    s.n = v.size();
    if (v.empty()) return s;
    std::sort(v.begin(), v.end());
    s.median = percentile(v, 0.5);
    s.p5 = percentile(v, 0.05);
    s.p95 = percentile(v, 0.95);
    s.min = v.front();
    s.max = v.back();
    s.mean = std::accumulate(v.begin(), v.end(), 0.0) / double(v.size());
    double var = 0.0;
    for (double x : v) var += (x - s.mean) * (x - s.mean);
    s.cv = v.size() > 1 && s.mean > 0 ? std::sqrt(var / double(v.size() - 1)) / s.mean : 0.0;
    return s;
}

inline double median(std::vector<double> v) { std::sort(v.begin(), v.end()); return percentile(v, 0.5); }

// Process QoS: opts the process out of Windows power throttling (EcoQoS). Without it
// Windows 11 may run a background process's threads on E-cores at reduced speed (a 1-thread CPU step at N = 65536 then
// takes 982 ms instead of ~580 ms). Returns the state for the run metadata.
inline std::string optOutOfPowerThrottling() {
#ifdef _WIN32
    PROCESS_POWER_THROTTLING_STATE state{};
    state.Version = PROCESS_POWER_THROTTLING_CURRENT_VERSION;
    state.ControlMask = PROCESS_POWER_THROTTLING_EXECUTION_SPEED;
    state.StateMask = 0;   // controlled, and off: always full speed
    return SetProcessInformation(GetCurrentProcess(), ProcessPowerThrottling, &state, sizeof state)
               ? "power throttling off (SetProcessInformation, EXECUTION_SPEED)"
               : "power throttling opt-out FAILED (error " + std::to_string(GetLastError()) + ")";
#else
    return "default (not Windows)";
#endif
}

using Clock = std::chrono::steady_clock;
inline double msSince(Clock::time_point t0) { return std::chrono::duration<double, std::milli>(Clock::now() - t0).count(); }

// "1,2,4" -> {1, 2, 4}
inline std::vector<int> parseIntList(const std::string& s) {
    std::vector<int> out;
    std::stringstream ss(s);
    for (std::string tok; std::getline(ss, tok, ',');)
        if (!tok.empty()) out.push_back(std::stoi(tok));
    return out;
}
inline std::vector<std::string> parseList(const std::string& s) {
    std::vector<std::string> out;
    std::stringstream ss(s);
    for (std::string tok; std::getline(ss, tok, ',');)
        if (!tok.empty()) out.push_back(tok);
    return out;
}

// Minimal "--key value" / "--flag" argument map; positional arguments in order
struct Args {
    std::vector<std::string> positional;
    std::map<std::string, std::string> opts;
    Args(int argc, char** argv, int first) {
        for (int i = first; i < argc; ++i) {
            std::string a = argv[i];
            if (a.rfind("--", 0) == 0) {
                const std::string key = a.substr(2);
                if (i + 1 < argc && std::string(argv[i + 1]).rfind("--", 0) != 0) opts[key] = argv[++i];
                else opts[key] = "1";
            } else {
                positional.push_back(a);
            }
        }
    }
    bool has(const std::string& k) const { return opts.count(k) != 0; }
    std::string get(const std::string& k, const std::string& def) const { auto it = opts.find(k); return it == opts.end() ? def : it->second; }
    int getInt(const std::string& k, int def) const { return has(k) ? std::stoi(opts.at(k)) : def; }
};

} // namespace bench
