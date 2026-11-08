#include <swarm/shader.hpp>

#include <swarm/sim_params.hpp>
#include <swarm/venue.hpp>

#include <swarm/assets.hpp>

#include <algorithm>
#include <chrono>
#include <charconv>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <mutex>
#include <sstream>
#include <vector>

namespace fs = std::filesystem;

namespace swarm {

std::string glslFloatLiteral(float v) {
    char buf[64];
    std::to_chars_result r = std::to_chars(buf, buf + sizeof(buf), v);
    std::string s(buf, r.ptr);
    if (s.find_first_of(".e") == std::string::npos) s += ".0";
    return v < 0.0f ? "(" + s + ")" : s;
}

namespace {

std::string glslFloat(float v) { return glslFloatLiteral(v); }

std::string glslVec2(Float2 v) { return "vec2(" + glslFloat(v.x) + ", " + glslFloat(v.y) + ")"; }

// #version must stay the first directive, so the preamble goes right after that line and a
// #line directive restores the file's own numbering for driver error messages. The venue's preamble (empty for the terrace)
// and then 'extra' follow the generated simulation preamble (extra is empty for the simulation shaders).
std::string insertPreamble(const std::string& source, const fs::path& path, const std::string& extra, const Venue& venue) {
    size_t lineStart = 0;
    int lineNo = 1;
    while (lineStart < source.size()) {
        size_t lineEnd = source.find('\n', lineStart);
        if (lineEnd == std::string::npos) lineEnd = source.size();
        size_t first = source.find_first_not_of(" \t", lineStart);
        if (first < lineEnd && source.compare(first, 8, "#version") == 0) {
            std::string head = source.substr(0, lineEnd);
            std::string tail = lineEnd < source.size() ? source.substr(lineEnd + 1) : std::string();
            return head + "\n" + shaderPreamble(venue) + venuePreamble(venue, path.parent_path()) + extra + "#line " +
                   std::to_string(lineNo + 1) + "\n" + tail;
        }
        lineStart = lineEnd + 1;
        ++lineNo;
    }
    throw ShaderError("Shader has no #version directive: " + path.string());
}

const char* stageName(GLenum stage) {
    switch (stage) {
    case GL_VERTEX_SHADER:   return "vertex";
    case GL_FRAGMENT_SHADER: return "fragment";
    case GL_COMPUTE_SHADER:  return "compute";
    default:                 return "unknown-stage";
    }
}

std::string readTextFile(const fs::path& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) throw ShaderError("Cannot open shader file: " + path.string());
    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

std::string trimNulls(std::string s) {
    while (!s.empty() && (s.back() == '\0' || s.back() == '\n' || s.back() == '\r')) s.pop_back();
    return s;
}

std::string shaderInfoLog(GLuint shader) {
    GLint len = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
    if (len <= 0) return {};
    std::string log(static_cast<size_t>(len), '\0');
    glGetShaderInfoLog(shader, len, nullptr, log.data());
    return trimNulls(std::move(log));
}

std::string programInfoLog(GLuint program) {
    GLint len = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
    if (len <= 0) return {};
    std::string log(static_cast<size_t>(len), '\0');
    glGetProgramInfoLog(program, len, nullptr, log.data());
    return trimNulls(std::move(log));
}

} // namespace

std::string shaderPreamble() { return shaderPreamble(terraceVenue()); }

std::string shaderPreamble(const Venue& venue) {
    std::ostringstream s;
    auto f = [&s](const char* name, float v) { s << "#define " << name << " " << glslFloat(v) << "\n"; };
    auto i = [&s](const char* name, long long v) { s << "#define " << name << " " << v << "\n"; };
    s << "// ---- generated from swarm/sim_params.hpp ----\n";
    // The venue's neighbour grid (the terrace: sim_params.hpp's GRID_RES, DOMAIN_*)
    i("GRID_RES", venue.gridRes);
    f("DOMAIN_MIN", venue.domainMin);
    f("DOMAIN_SPAN", venue.domainSpan);
    f("DOMAIN_MAX", venue.domainMax());
    i("SDF_RES", SDF_RES);
    // The predict pass's neighbour search radius (separation partners, headway look-ahead) and its ring
    f("R_PERC", R_PERC);
    i("PERC_RING", PERC_RING);
    // Two radii; R_SEP and BODY_DIAM are derived (exact doublings), emitted as expressions
    f("PERSONAL_RADIUS", PERSONAL_RADIUS);
    f("BODY_RADIUS", BODY_RADIUS);
    s << "#define R_SEP (2.0 * PERSONAL_RADIUS)\n";
    s << "#define BODY_DIAM (2.0 * BODY_RADIUS)\n";
    f("K_SEP", K_SEP);
    f("DT", DT);
    f("V_MAX", V_MAX);
    f("GRAVITY", GRAVITY);
    // The driving term's relaxation time and the headway time gap, in model time
    f("TAU_RELAX", TAU_RELAX);
    f("T_HEADWAY", T_HEADWAY);
    f("PROJ_RELAX", PROJ_RELAX);
    f("PROJ_MAX_SHIFT_RADII", PROJ_MAX_SHIFT_RADII);
    s << "#define PROJ_MAX_SHIFT (PROJ_MAX_SHIFT_RADII * BODY_RADIUS)\n";
    f("W_OBS", W_OBS);
    f("GOAL_DEADZONE", GOAL_DEADZONE);
    f("TORSO_HEIGHT", TORSO_HEIGHT);
    f("OBSTACLE_RANGE", OBSTACLE_RANGE);
    f("OBSTACLE_GAIN", OBSTACLE_GAIN);
    f("OBSTACLE_MIN_NORMAL", OBSTACLE_MIN_NORMAL);
    f("OBSTACLE_GRAD_H", OBSTACLE_GRAD_H);
    f("SAFE_NORMALIZE_EPS", SAFE_NORMALIZE_EPS);
    f("SEP_STACKED_XY2", SEP_STACKED_XY2);
    i("FLOOR_SEARCH_CELLS", FLOOR_SEARCH_CELLS);
    f("FLOOR_SETTLE_RADII", FLOOR_SETTLE_RADII);
    s << "#define FLOOR_SETTLE_REACH (FLOOR_SETTLE_RADII * BODY_RADIUS)\n";
    // Derived constants as expressions, folded by the GLSL compiler (see sim_params.hpp)
    f("FEELER_REACH_RADII", FEELER_REACH_RADII);
    s << "#define FEELER_REACH (FEELER_REACH_RADII * BODY_RADIUS)\n";
    i("FEELER_COUNT", FEELER_COUNT);
    s << "const vec2 FEELER_DIRS[FEELER_COUNT] = vec2[](";
    for (size_t k = 0; k < FEELER_DIRS.size(); ++k) s << (k ? ", " : "") << glslVec2(FEELER_DIRS[k]);
    s << ");\n";
    i("WALL_ROOT_STEPS", WALL_ROOT_STEPS);
    i("WALL_RECAST_STEPS", WALL_RECAST_STEPS);
    f("WALL_RECAST_TOL_RADII", WALL_RECAST_TOL_RADII);
    s << "#define WALL_RECAST_TOL (WALL_RECAST_TOL_RADII * BODY_RADIUS)\n";
    f("WALL_MAX_NZ", WALL_MAX_NZ);
    i("WALL_PASSES", WALL_PASSES);
    f("CENTRE_GRAD_MIN", CENTRE_GRAD_MIN);
    i("STATIC_SWEEP_BISECTIONS", STATIC_SWEEP_BISECTIONS);
    f("PLANE_PROBE_RADII", PLANE_PROBE_RADII);
    s << "#define PLANE_PROBE_REACH (PLANE_PROBE_RADII * BODY_RADIUS)\n";
    // The step-up limit (MAX_STEP_UP folded host-side from metres, as TAU_RELAX)
    f("MAX_STEP_UP", MAX_STEP_UP);
    f("STEP_UP_TOL", STEP_UP_TOL);
    f("STEP_UP_FLOOR_REACH_RADII", STEP_UP_FLOOR_REACH_RADII);
    s << "#define STEP_UP_FLOOR_REACH (STEP_UP_FLOOR_REACH_RADII * BODY_RADIUS)\n";
    i("STEP_UP_BISECTIONS", STEP_UP_BISECTIONS);
    f("STEP_UP_SAMPLE_RADII", STEP_UP_SAMPLE_RADII);
    s << "#define STEP_UP_SAMPLE (STEP_UP_SAMPLE_RADII * BODY_RADIUS)\n";
    i("STEP_UP_MAX_SAMPLES", STEP_UP_MAX_SAMPLES);
    i("STEP_UP_SLIDE_TRIES", STEP_UP_SLIDE_TRIES);
    s << "const vec2 STEP_UP_SLIDE_DIRS[STEP_UP_SLIDE_TRIES] = vec2[](";
    for (size_t k = 0; k < STEP_UP_SLIDE_DIRS.size(); ++k) s << (k ? ", " : "") << glslVec2(STEP_UP_SLIDE_DIRS[k]);
    s << ");\n";
    for (const auto& [name, arr] : { std::pair{ "FEELER_OFFSETS", FEELER_OFFSETS }, std::pair{ "PROBE_OFFSETS", PROBE_OFFSETS } }) {
        s << "const vec2 " << name << "[FEELER_COUNT] = vec2[](";
        for (size_t k = 0; k < arr.size(); ++k) s << (k ? ", " : "") << glslVec2(arr[k]);
        s << ");\n";
    }
    s << "#define FENCE_CENTER " << glslVec2(FENCE_CENTER) << "\n"
      << "#define FENCE_HALF_MID " << glslVec2(FENCE_HALF_MID) << "\n";
    f("FENCE_HALF_THK_VISUAL", FENCE_HALF_THK_VISUAL);
    f("FENCE_HALF_THK_COLL", FENCE_HALF_THK_COLL);
    i("FENCE_CCD_BISECTIONS", FENCE_CCD_BISECTIONS);
    f("WALKWAY_MIN", WALKWAY_MIN);
    f("WALKWAY_MAX", WALKWAY_MAX);
    f("WALKWAY_CENTRE", WALKWAY_CENTRE);
    f("AVENUE_HALF", AVENUE_HALF);
    f("AISLE_MAX", AISLE_MAX);
    f("AISLE_CENTRE", AISLE_CENTRE);
    f("AVENUE_TARGET_DEPTH", AVENUE_TARGET_DEPTH);
    f("PITCH_RECOVERY_MARGIN", PITCH_RECOVERY_MARGIN);
    f("EXIT_DEPTH", venue.exitDepth);   // the venue's exit test (the terrace: sim_params.hpp's)
    f("EXIT_MAX_Z", venue.exitMaxZ);
    f("PARK_COORD", PARK_COORD);
    i("FENCE_GATE_COUNT", (long long)FENCE_GATES.size());
    if (!FENCE_GATES.empty()) {  // GLSL has no zero-length arrays
        s << "const vec2 FENCE_GATE_CENTER[FENCE_GATE_COUNT] = vec2[](";
        for (size_t i = 0; i < FENCE_GATES.size(); ++i) s << (i ? ", " : "") << glslVec2(FENCE_GATES[i].center);
        s << ");\nconst vec2 FENCE_GATE_HALF[FENCE_GATE_COUNT] = vec2[](";
        for (size_t i = 0; i < FENCE_GATES.size(); ++i) s << (i ? ", " : "") << glslVec2(FENCE_GATES[i].halfSize);
        s << ");\n";
    }
    s << "#define INACTIVE_CELL 0x" << std::hex << std::uppercase << INACTIVE_CELL << "u\n"
      << "// ---- end generated ----\n";
    return s.str();
}

namespace {

// A compiled shader's status and log: throws ShaderError (deleting the shader) on failure, prints a non-empty log as a warning
void checkCompiled(GLuint shader, GLenum stage, const fs::path& path);

GLuint compileShaderSource(GLenum stage, const std::string& source, const fs::path& path) {
    const char* src = source.c_str();

    GLuint shader = glCreateShader(stage);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    checkCompiled(shader, stage, path);
    return shader;
}

void checkCompiled(GLuint shader, GLenum stage, const fs::path& path) {
    GLint ok = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
    const std::string log = shaderInfoLog(shader);
    if (!ok) {
        std::cerr << "[shader] " << stageName(stage) << " compile FAILED: " << path.string() << "\n"
                  << (log.empty() ? "(driver returned no info log)" : log) << std::endl;
        glDeleteShader(shader);
        throw ShaderError(std::string("Failed to compile ") + stageName(stage) + " shader " + path.string());
    }
    if (!log.empty())
        std::cerr << "[shader] " << stageName(stage) << " compile warnings: " << path.string() << "\n" << log << std::endl;
}

// --- The program binary cache (see shader.hpp) ---
struct ProgramCache {
    std::mutex m;
    fs::path dir;   // empty: off
    ProgramCacheStats stats;
};
ProgramCache& programCache() {
    static ProgramCache c;
    return c;
}

uint64_t fnv1a(uint64_t h, const void* data, size_t n) {
    const unsigned char* b = static_cast<const unsigned char*>(data);
    for (size_t i = 0; i < n; ++i) { h ^= b[i]; h *= 0x100000001b3ull; }
    return h;
}

std::string driverString() {
    const char* r = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
    const char* v = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    return std::string(r ? r : "?") + " | " + (v ? v : "?");
}

// One stage of a program: its GL stage, its complete source (the generated preambles included), its file (messages)
struct StageSource { GLenum stage; std::string source; fs::path path; };

// The cache key: FNV-1a 64 of the format version, the driver string and every stage (its GL stage and complete source)
uint64_t programKey(const std::string& driver, const std::vector<StageSource>& stages) {
    uint64_t h = 0xcbf29ce484222325ull;
    const char version[] = "swarm program binary cache 1";
    h = fnv1a(h, version, sizeof version);
    h = fnv1a(h, driver.data(), driver.size() + 1);
    for (const StageSource& s : stages) {
        h = fnv1a(h, &s.stage, sizeof s.stage);
        h = fnv1a(h, s.source.data(), s.source.size() + 1);
    }
    return h;
}

// The file: magic, key, binary format, binary length, FNV-1a 64 of the binary, the driver string's length and the string, the binary
constexpr char CACHE_MAGIC[8] = { 'S', 'W', 'P', 'R', 'O', 'G', '0', '1' };
struct CacheHeader {
    char magic[8];
    uint64_t key;
    uint32_t format;
    uint32_t length;
    uint64_t checksum;
    uint32_t driverLength;
    uint32_t reserved;
};

fs::path cacheFile(const fs::path& dir, uint64_t key) {
    char name[40];
    std::snprintf(name, sizeof name, "%016llx.bin", static_cast<unsigned long long>(key));
    return dir / name;
}

// The cached binary of 'key' as a linked program, or 0 (no file, a damaged or foreign file, or a binary the driver rejects)
GLuint loadCachedProgram(const fs::path& file, uint64_t key, const std::string& driver, bool& rejected) {
    rejected = false;
    std::ifstream in(file, std::ios::binary);
    if (!in) return 0;
    CacheHeader hd{};
    if (!in.read(reinterpret_cast<char*>(&hd), sizeof hd) || std::memcmp(hd.magic, CACHE_MAGIC, 8) != 0 || hd.key != key ||
        hd.driverLength != driver.size() || hd.length == 0) { rejected = true; return 0; }
    std::string d(hd.driverLength, '\0');
    std::vector<char> bin(hd.length);
    if (!in.read(d.data(), std::streamsize(d.size())) || d != driver || !in.read(bin.data(), std::streamsize(bin.size())) ||
        fnv1a(0xcbf29ce484222325ull, bin.data(), bin.size()) != hd.checksum) { rejected = true; return 0; }
    GLuint program = glCreateProgram();
    glProgramBinary(program, hd.format, bin.data(), GLsizei(bin.size()));
    GLint ok = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &ok);
    if (!ok) {
        glDeleteProgram(program);
        rejected = true;
        return 0;
    }
    return program;
}

// Stores a linked program's binary (written to a temporary file, then renamed: processes sharing the cache never read a partial file)
bool storeProgram(const fs::path& dir, uint64_t key, const std::string& driver, GLuint program) {
    GLint length = 0;
    glGetProgramiv(program, GL_PROGRAM_BINARY_LENGTH, &length);
    if (length <= 0) return false;
    std::vector<char> bin(static_cast<size_t>(length));
    GLenum format = 0;
    GLsizei written = 0;
    glGetProgramBinary(program, length, &written, &format, bin.data());
    if (written <= 0) return false;
    bin.resize(static_cast<size_t>(written));
    CacheHeader hd{};
    std::memcpy(hd.magic, CACHE_MAGIC, 8);
    hd.key = key;
    hd.format = format;
    hd.length = uint32_t(bin.size());
    hd.checksum = fnv1a(0xcbf29ce484222325ull, bin.data(), bin.size());
    hd.driverLength = uint32_t(driver.size());
    std::error_code ec;
    fs::create_directories(dir, ec);
    const fs::path file = cacheFile(dir, key), tmp = dir / (processTempPath(file.filename().string()).filename().string() + ".tmp");
    {
        std::ofstream out(tmp, std::ios::binary);
        out.write(reinterpret_cast<const char*>(&hd), sizeof hd);
        out.write(driver.data(), std::streamsize(driver.size()));
        out.write(bin.data(), std::streamsize(bin.size()));
        if (!out) { out.close(); fs::remove(tmp, ec); return false; }
    }
    fs::rename(tmp, file, ec);
    if (ec) { fs::remove(tmp, ec); return false; }
    return true;
}

GLuint linkShaders(std::initializer_list<GLuint> shaders, const std::string& label, bool retrievable);
void checkLinked(GLuint program, const std::string& label);
GLuint takePrecompiled(const std::vector<StageSource>& stages, const std::string& label);

// SWARM_SHADER_NONCE=<text> (diagnostics): a trailing comment "// nonce <text>" on every stage's source. The code is
// unchanged, but every source-keyed cache (this one and the driver's own) misses: a cold compile can be timed without deleting a cache.
std::string withNonce(std::string source) {
    if (const char* env = std::getenv("SWARM_SHADER_NONCE"); env && *env) source += std::string("\n// nonce ") + env + "\n";
    return source;
}

// Builds a program from its stages: from the cache when it is on and holds the program, else compiled and linked (and stored)
GLuint buildProgram(std::vector<StageSource> stages, const std::string& label) {
    for (StageSource& s : stages) s.source = withNonce(std::move(s.source));
    ProgramCache& pc = programCache();
    fs::path dir;
    {
        std::lock_guard<std::mutex> lock(pc.m);
        dir = pc.dir;
    }
    const auto t0 = std::chrono::steady_clock::now();
    auto seconds = [&] { return std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count(); };
    std::string driver;
    uint64_t key = 0;
    if (!dir.empty()) {
        driver = driverString();
        key = programKey(driver, stages);
        bool rejected = false;
        if (GLuint program = loadCachedProgram(cacheFile(dir, key), key, driver, rejected)) {
            std::lock_guard<std::mutex> lock(pc.m);
            ++pc.stats.loaded;
            pc.stats.loadSeconds += seconds();
            return program;
        }
        if (rejected) {
            std::lock_guard<std::mutex> lock(pc.m);
            ++pc.stats.rejected;
        }
    } else if (GLuint program = takePrecompiled(stages, label)) {   // compiled ahead from this very source (precompileProgram)
        std::lock_guard<std::mutex> lock(pc.m);
        ++pc.stats.compiled;
        ++pc.stats.ahead;
        pc.stats.compileSeconds += seconds();
        return program;
    }
    std::vector<GLuint> shaders;
    try {
        for (const StageSource& s : stages) shaders.push_back(compileShaderSource(s.stage, s.source, s.path));
    } catch (...) {
        for (GLuint s : shaders) glDeleteShader(s);
        throw;
    }
    GLuint program = 0;
    if (shaders.size() == 1) program = linkShaders({ shaders[0] }, label, !dir.empty());
    else program = linkShaders({ shaders[0], shaders[1] }, label, !dir.empty());
    const bool stored = !dir.empty() && storeProgram(dir, key, driver, program);
    std::lock_guard<std::mutex> lock(pc.m);
    ++pc.stats.compiled;
    pc.stats.stored += stored;
    pc.stats.compileSeconds += seconds();
    return program;
}

GLuint linkShaders(std::initializer_list<GLuint> shaders, const std::string& label, bool retrievable) {
    GLuint program = glCreateProgram();
    // the cache's binaries: requested before the link (the hint does not change the program: test_gpu engine.program_cache compares the states)
    if (retrievable) glProgramParameteri(program, GL_PROGRAM_BINARY_RETRIEVABLE_HINT, GL_TRUE);
    for (GLuint s : shaders) glAttachShader(program, s);
    glLinkProgram(program);
    for (GLuint s : shaders) {
        glDetachShader(program, s);
        glDeleteShader(s);
    }
    checkLinked(program, label);
    return program;
}

void checkLinked(GLuint program, const std::string& label) {
    GLint ok = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &ok);
    const std::string log = programInfoLog(program);
    if (!ok) {
        std::cerr << "[shader] link FAILED: " << label << "\n"
                  << (log.empty() ? "(driver returned no info log)" : log) << std::endl;
        glDeleteProgram(program);
        throw ShaderError("Failed to link program " + label);
    }
    if (!log.empty())
        std::cerr << "[shader] link warnings: " << label << "\n" << log << std::endl;
}

// --- Compiling ahead (see shader.hpp) ---

constexpr GLenum COMPLETION_STATUS = 0x91B1;   // GL_COMPLETION_STATUS_ARB = _KHR (this glad is generated for the core 4.3 profile alone)
constexpr GLsizeiptr WARMUP_SCRATCH_BYTES = GLsizeiptr(4) << 20;   // > any index a 1-group dispatch reaches (finalize: 256 cells)

struct Precompiled {
    std::vector<StageSource> stages;   // complete sources, the nonce applied (buildProgram compares them)
    std::vector<GLuint> shaders;
    GLuint program = 0;
    bool compileStarted = false;   // the shaders' compiles issued
    bool compiled = false;         // the shaders' compiles complete (without the extension: compiled and linked)
    bool started = false;          // the program's link issued
};

struct PrecompilePool {
    std::vector<Precompiled> entries;
    int taken = 0;                                 // entries a loader took since the last discard
    void (APIENTRY* maxThreads)(GLuint) = nullptr; // GL_ARB / KHR_parallel_shader_compile; nullptr: one program at a time
};

// The pool is the GL thread's (every GL call is made there): no lock
PrecompilePool& pool() {
    static PrecompilePool p;
    return p;
}

// The two halves of a program's build: its shaders' compiles, then (their compiles complete, or at once without the extension) the link
void startCompile(Precompiled& e) {
    for (const StageSource& s : e.stages) {
        const char* src = s.source.c_str();
        const GLuint shader = glCreateShader(s.stage);
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);
        e.shaders.push_back(shader);
    }
    e.compileStarted = true;
}

void startLink(Precompiled& e) {
    e.program = glCreateProgram();
    for (GLuint s : e.shaders) glAttachShader(e.program, s);
    glLinkProgram(e.program);
    e.started = true;
}

void startPrecompiled(Precompiled& e) {
    if (!e.compileStarted) startCompile(e);
    if (!e.started) startLink(e);
}

void deletePrecompiled(Precompiled& e) {
    for (GLuint s : e.shaders) {
        if (e.program) glDetachShader(e.program, s);
        glDeleteShader(s);
    }
    if (e.program) glDeleteProgram(e.program);
    e = Precompiled{};
}

// The pool's program of exactly these stages, its statuses and logs checked as compileShaderSource and linkShaders check them
// (ShaderError on a failure); 0 if the pool has none
GLuint takePrecompiled(const std::vector<StageSource>& stages, const std::string& label) {
    std::vector<Precompiled>& entries = pool().entries;
    auto same = [&](const Precompiled& e) {
        if (e.stages.size() != stages.size()) return false;
        for (size_t k = 0; k < stages.size(); ++k)
            if (e.stages[k].stage != stages[k].stage || e.stages[k].source != stages[k].source) return false;
        return true;
    };
    const auto it = std::find_if(entries.begin(), entries.end(), same);
    if (it == entries.end()) return 0;
    Precompiled e = std::move(*it);
    entries.erase(it);
    ++pool().taken;
    if (!e.started) startPrecompiled(e);   // queued, not started yet (one program at a time)
    size_t k = 0;
    try {
        for (; k < e.shaders.size(); ++k) {
            checkCompiled(e.shaders[k], e.stages[k].stage, e.stages[k].path);   // deletes that shader on a failure
            glDetachShader(e.program, e.shaders[k]);
            glDeleteShader(e.shaders[k]);
        }
    } catch (...) {
        for (size_t r = k + 1; r < e.shaders.size(); ++r) glDeleteShader(e.shaders[r]);   // (shaders before k: deleted; k: by checkCompiled)
        glDeleteProgram(e.program);
        throw;
    }
    checkLinked(e.program, label);   // deletes the program on a failure
    return e.program;
}

} // namespace

GLuint compileShaderFile(GLenum stage, const fs::path& path, const std::string& extraPreamble, const Venue* venue) {
    return compileShaderSource(stage, insertPreamble(readTextFile(path), path, extraPreamble, venue ? *venue : terraceVenue()), path);
}

namespace {

// A spec's stages with their complete sources (the preambles inserted; the nonce is buildProgram's) and its label
std::vector<StageSource> specStages(const ProgramSpec& s) {
    if (s.frag.empty())
        return { { GL_COMPUTE_SHADER, insertPreamble(readTextFile(s.path), s.path, s.extraPreamble, s.venue ? *s.venue : terraceVenue()), s.path } };
    const Venue& terrace = terraceVenue();
    return { { GL_VERTEX_SHADER, insertPreamble(readTextFile(s.path), s.path, {}, terrace), s.path },
             { GL_FRAGMENT_SHADER, insertPreamble(readTextFile(s.frag), s.frag, {}, terrace), s.frag } };
}

std::string specLabel(const ProgramSpec& s) {
    if (!s.frag.empty()) return s.path.filename().string() + " + " + s.frag.filename().string();
    return s.path.filename().string() + (s.venue && s.venue->seated() ? std::string(" (venue ") + s.venue->name + ")" : std::string());
}

} // namespace

GLuint loadComputeProgram(const fs::path& comp, const std::string& extraPreamble, const Venue* venue) {
    return loadProgram({ comp, {}, extraPreamble, venue });
}

GLuint loadRenderProgram(const fs::path& vert, const fs::path& frag) { return loadProgram({ vert, frag, {}, nullptr }); }

GLuint loadProgram(const ProgramSpec& spec) { return buildProgram(specStages(spec), specLabel(spec)); }

void setParallelShaderCompile(void (APIENTRY* maxShaderCompilerThreads)(GLuint)) {
    pool().maxThreads = maxShaderCompilerThreads;
    if (maxShaderCompilerThreads) maxShaderCompilerThreads(0xFFFFFFFFu);   // the implementation's own choice of threads
}

bool parallelShaderCompile() { return pool().maxThreads != nullptr; }

void precompileProgram(const ProgramSpec& spec) {
    if (!programCacheDir().empty()) return;   // the binary cache builds its own programs
    Precompiled e;
    e.stages = specStages(spec);
    for (StageSource& s : e.stages) s.source = withNonce(std::move(s.source));   // as buildProgram, so the sources compare equal
    pool().entries.push_back(std::move(e));
}

PrecompileStatus precompileStep() {
    PrecompilePool& p = pool();
    if (p.maxThreads) {
        // The driver's threads compile; this thread only issues and polls: every shader's compile at once, then their completion
        // (a shader's status query returns at once). No link here: linkPrecompiled issues them all.
        for (Precompiled& e : p.entries)
            if (!e.compileStarted) startCompile(e);
        for (Precompiled& e : p.entries) {
            if (e.compiled) continue;
            bool compiled = true;
            for (GLuint s : e.shaders) {
                GLint done = GL_FALSE;
                glGetShaderiv(s, COMPLETION_STATUS, &done);
                compiled = compiled && done != GL_FALSE;
            }
            e.compiled = compiled;
        }
    } else {   // without the extension: one program per call, compiled, linked and waited for (its link status)
        for (Precompiled& e : p.entries)
            if (!e.compiled) {
                startPrecompiled(e);
                GLint ok = GL_FALSE;
                glGetProgramiv(e.program, GL_LINK_STATUS, &ok);
                e.compiled = true;
                break;
            }
    }
    PrecompileStatus st;
    st.total = int(p.entries.size()) + p.taken;
    st.complete = p.taken;
    for (const Precompiled& e : p.entries) st.complete += e.compiled;
    return st;
}

GLsync linkPrecompiled() {
    for (Precompiled& e : pool().entries)
        if (!e.started) startPrecompiled(e);   // (the compile, if a program was never polled)
    GLsync fence = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
    glFlush();
    return fence;
}

GLsync warmUpPrecompiled(GLuint sdfTexture) {
    std::vector<GLuint> programs;
    for (const Precompiled& e : pool().entries) {
        if (!e.started || e.stages.size() != 1 || e.stages[0].stage != GL_COMPUTE_SHADER) continue;
        GLint ok = GL_FALSE;
        glGetProgramiv(e.program, GL_LINK_STATUS, &ok);   // linked by now (linkPrecompiled's fence); a failure is reported when it is taken
        if (ok) programs.push_back(e.program);
    }
    if (programs.empty()) return nullptr;
    GLint maxBindings = 0;
    glGetIntegerv(GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS, &maxBindings);
    const GLuint bindings = GLuint(std::min(maxBindings, 32));
    GLuint scratch = 0;
    glGenBuffers(1, &scratch);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, scratch);
    glBufferData(GL_SHADER_STORAGE_BUFFER, WARMUP_SCRATCH_BYTES, nullptr, GL_DYNAMIC_COPY);
    const GLuint zero = 0;
    glClearBufferData(GL_SHADER_STORAGE_BUFFER, GL_R32UI, GL_RED_INTEGER, GL_UNSIGNED_INT, &zero);
    for (GLuint b = 0; b < bindings; ++b) glBindBufferBase(GL_SHADER_STORAGE_BUFFER, b, scratch);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_3D, sdfTexture);
    for (GLuint program : programs) {   // the uniforms are never set here: they keep their link-time defaults
        glUseProgram(program);
        glDispatchCompute(1, 1, 1);
    }
    glMemoryBarrier(GL_ALL_BARRIER_BITS);
    glUseProgram(0);
    for (GLuint b = 0; b < bindings; ++b) glBindBufferBase(GL_SHADER_STORAGE_BUFFER, b, 0);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    glDeleteBuffers(1, &scratch);   // the GL frees it once the dispatches are done
    GLsync fence = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
    glFlush();
    return fence;
}

int discardPrecompiled() {
    PrecompilePool& p = pool();
    const int n = int(p.entries.size());
    for (Precompiled& e : p.entries) deletePrecompiled(e);
    p.entries.clear();
    p.taken = 0;
    return n;
}

void setProgramCache(const fs::path& dir) {
    ProgramCache& pc = programCache();
    std::lock_guard<std::mutex> lock(pc.m);
    pc.dir = dir;
}

fs::path programCacheDir() {
    ProgramCache& pc = programCache();
    std::lock_guard<std::mutex> lock(pc.m);
    return pc.dir;
}

ProgramCacheStats programCacheStats() {
    ProgramCache& pc = programCache();
    std::lock_guard<std::mutex> lock(pc.m);
    return pc.stats;
}

fs::path programCacheDirFromEnv() {
    if (const char* env = std::getenv("SWARM_SHADER_CACHE"); env && *env && std::string(env) != "off") return fs::path(env);
    return {};
}

} // namespace swarm
