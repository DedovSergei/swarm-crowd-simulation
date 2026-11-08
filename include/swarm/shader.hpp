#pragma once

#include <glad/glad.h>

#include <filesystem>
#include <initializer_list>
#include <stdexcept>
#include <string>

namespace swarm {

struct Venue;

struct ShaderError : std::runtime_error {
    using std::runtime_error::runtime_error;
};

// #defines generated from swarm/sim_params.hpp. compileShaderFile inserts them right after
// the #version line of every shader, followed by a #line directive that keeps the file's
// own line numbers in driver messages. The neighbour grid (GRID_RES, DOMAIN_*) and the exit test
// (EXIT_DEPTH, EXIT_MAX_Z) are the venue's; without a venue, the terrace reference venue's.
std::string shaderPreamble();
std::string shaderPreamble(const Venue& venue);

// Shortest decimal that round-trips to v, as a GLSL float literal (negative values parenthesized):
// the form every float of the generated preambles takes
std::string glslFloatLiteral(float v);

// Compiles one GLSL stage from a file (with the preamble above, then the venue's preamble (swarm/venue.hpp
// venuePreamble: empty for the terrace), then extraPreamble, e.g. the metric shaders' metrics::metricsPreamble()).
// venue nullptr: the terrace. On failure the complete driver info log is printed to std::cerr and ShaderError is thrown.
// A non-empty log on success is printed as a warning.
GLuint compileShaderFile(GLenum stage, const std::filesystem::path& path, const std::string& extraPreamble = {},
                         const Venue* venue = nullptr);

GLuint loadComputeProgram(const std::filesystem::path& comp, const std::string& extraPreamble = {}, const Venue* venue = nullptr);
GLuint loadRenderProgram(const std::filesystem::path& vert, const std::filesystem::path& frag);

// A program as the two loaders above build it: a compute shader with its extra preamble and venue, or (frag not empty) a vertex +
// fragment pair. CrowdSim, CrowdMetrics and the viewer's SceneRenderer list theirs (programSpecs) and build them from the list.
struct ProgramSpec {
    std::filesystem::path path;   // the compute shader, or the vertex shader
    std::filesystem::path frag;   // the fragment shader of a render program; empty: a compute program
    std::string extraPreamble;    // compute programs
    const Venue* venue = nullptr; // compute programs (nullptr: the terrace)
};
GLuint loadProgram(const ProgramSpec& spec);   // loadComputeProgram or loadRenderProgram

// Compiling ahead (the viewer's loading screen; nothing else uses it). precompileProgram queues a program; precompileStep() starts and
// polls the compiles; the next loadComputeProgram / loadRenderProgram of the identical source (every stage, the generated preambles
// and SWARM_SHADER_NONCE included) takes that program instead of compiling it again: the same source, the same program, so the
// results cannot change. Its compile and link status and logs are checked when it is taken, exactly as for a program compiled there.
// With GL_ARB_parallel_shader_compile (or the KHR form; setParallelShaderCompile) every queued program's shaders start compiling at
// once on the driver's threads and precompileStep() polls the SHADERS' completion (GL_COMPLETION_STATUS_ARB, which returns at once).
// Without it, each precompileStep() compiles and links one program and waits for it (on the GL thread: the best a driver without the
// extension allows). Off while the program binary cache is on (setProgramCache): precompileProgram does nothing then.
void setParallelShaderCompile(void (APIENTRY* maxShaderCompilerThreads)(GLuint));   // the extension's entry point; nullptr: off (the default)
bool parallelShaderCompile();
void precompileProgram(const ProgramSpec& spec);
struct PrecompileStatus {
    int total = 0;      // queued since the last discardPrecompiled
    int complete = 0;   // with the extension: compiled; without: compiled and linked (a failure is reported when the program is taken)
};
PrecompileStatus precompileStep();
// linkPrecompiled() issues every link not issued yet and returns a fence after them, for the caller to poll (glClientWaitSync,
// timeout 0) WITHOUT drawing: once it signals, every program is linked. Measured on AMD 26.10.1 (cold shader cache, venue S): the
// links run on the driver's threads, but GL_COMPLETION_STATUS_ARB on a program still linking, glUseProgram of it and a swap all wait
// for the links on this thread, while glClientWaitSync on a fence after them returns at once. So precompileStep never
// queries or uses a program, and nothing is drawn until the fence signals.
GLsync linkPrecompiled();
// The driver may compile a program again on its first dispatch (AMD 26.10.1 with a cold shader cache: about twice as long as the link):
// warmUpPrecompiled() dispatches every complete compute program of the pool once, 1 work group, its
// uniforms at their link-time defaults (0: every pass of this project returns before touching memory, the sort exchanges nothing), with
// a zeroed scratch buffer bound to every storage binding and sdfTexture on unit 0, so no real buffer is read or written; then a fence
// for the caller to poll with glClientWaitSync(timeout 0), again without drawing. Call it once linkPrecompiled's fence has signalled
// (every program linked: nothing here waits). Nullptr if the pool has no compute program.
GLsync warmUpPrecompiled(GLuint sdfTexture);
int discardPrecompiled();   // deletes the programs nobody took and empties the pool; returns how many it deleted

// The program binary cache of loadComputeProgram / loadRenderProgram. Off by default (every program compiled from source);
// setProgramCache(dir) turns it on for this process (SWARM: SWARM_SHADER_CACHE=<dir>). A linked program is stored as the driver's
// binary (glGetProgramBinary) in dir/<key>.bin, key = FNV-1a 64 of the driver string (GL_RENDERER | GL_VERSION) and every stage's complete
// source, the generated preambles included (any change of the code, a constant, a venue or a model option is another key), and loaded with
// glProgramBinary. A missing, damaged or foreign file, or a binary the driver rejects, falls back to compiling (and replaces the file). The
// binary is the compiled program itself: the same results bit for bit (test_gpu engine.program_cache compares the states with and without the cache).
void setProgramCache(const std::filesystem::path& dir);   // empty: off
std::filesystem::path programCacheDir();                  // empty: off
// Measured on AMD 26.10.1: glProgramBinary costs as much as compiling and the driver keeps its own source-keyed cache (warm starts are fast),
// so the cache is OFF by default
// everywhere: opt-in for a driver whose binaries load fast. SWARM_SHADER_CACHE=<dir>: that directory; unset or "off": none (an empty path)
std::filesystem::path programCacheDirFromEnv();
struct ProgramCacheStats {
    int loaded = 0;              // programs loaded from the cache
    int compiled = 0;            // programs compiled from source (the cache on or off)
    int ahead = 0;               // of these, compiled ahead (precompileProgram): compileSeconds holds only the wait when they were taken
    int stored = 0;              // binaries written to the cache
    int rejected = 0;            // cache files not used (damaged, foreign, or the driver refused the binary)
    double loadSeconds = 0.0;    // wall time of the loads
    double compileSeconds = 0.0; // wall time of the compiles and links
};
ProgramCacheStats programCacheStats();

} // namespace swarm
