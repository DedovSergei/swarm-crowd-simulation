#pragma once

// What the GPU offers and what a run needs from it. Every requirement comes from the programs' and buffers' own lists
// (CrowdSim, CrowdMetrics, the viewer's SceneRenderer: programBindings, bufferUses). SWARM --selftest-ui compares the binding lists
// with the compiled programs (glGetProgramResourceiv), test_gpu engine.gpu_capabilities the buffer lists with the real buffers. Nothing here builds a
// navigation table or compiles a program, so the viewer can refuse a venue before its user waits for either.

#include <glad/glad.h>

#include <cstdint>
#include <string>
#include <vector>

namespace swarm {

constexpr int GL_REQUIRED_MAJOR = 4, GL_REQUIRED_MINOR = 3;

// The current context's limits (a GL call; needs the context current).
// SWARM_GPU_LIMITS (a test aid, as SWARM_NO_PARALLEL_COMPILE): overrides any of them,
// "gl=4.1,bindings=16,blocks=16,vertexblocks=4,fragmentblocks=8,blocksize=134217728"
struct GpuLimits {
    int glMajor = 0, glMinor = 0;
    int ssboBindings = 0;         // GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS
    int computeSsboBlocks = 0;    // GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS
    int vertexSsboBlocks = 0;     // GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS (OpenGL 4.3 allows a driver 0)
    int fragmentSsboBlocks = 0;   // GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS
    int64_t ssboBlockBytes = 0;   // GL_MAX_SHADER_STORAGE_BLOCK_SIZE
    std::string renderer, version;
    bool simulated = false;       // SWARM_GPU_LIMITS changed them
};
GpuLimits readGpuLimits();
// The override's text applied to l; throws std::invalid_argument on anything else
GpuLimits applyGpuLimitsOverride(GpuLimits l, const std::string& text);
// SWARM_GPU_LIMITS's OpenGL version below the required one, so that creating the window fails as on such a driver (no context needed)
bool simulatedGlTooOld();

// A program's SSBO binding points (every block its source declares for this venue and model), per stage
struct ProgramBindings {
    std::string name;
    bool compute = true;
    std::vector<GLuint> ssbo;           // a compute program's, or a render program's vertex stage's
    std::vector<GLuint> fragmentSsbo;   // a render program's fragment stage's
};
// A buffer bound as an SSBO. estimated: an upper bound, the exact size is known only once the table is loaded or built
struct GpuBufferUse {
    std::string name;
    int64_t bytes = 0;
    bool estimated = false;
};

struct GpuRequirements {
    int ssboBindings = 0;         // the highest binding of any program + 1
    int computeSsboBlocks = 0;    // the most blocks of one compute program
    int vertexSsboBlocks = 0;     // the most blocks of one vertex stage
    int fragmentSsboBlocks = 0;   // the most blocks of one fragment stage
    int64_t ssboBlockBytes = 0;   // the largest buffer
    std::string largestBuffer;
    bool blockBytesEstimated = false;
};
GpuRequirements gpuRequirements(const std::vector<ProgramBindings>& programs, const std::vector<GpuBufferUse>& buffers);

// "" if the limits meet the requirements, else why not, for a person: "needs 20 SSBO bindings, this GPU has 16"
std::string gpuShortfall(const GpuRequirements& need, const GpuLimits& limits);
// The largest buffer alone: "" or "needs a 884 MB buffer (the exit choice table), this GPU allows 134 MB"
std::string gpuBlockShortfall(const std::string& buffer, int64_t bytes, bool estimated, const GpuLimits& limits);
std::string formatBytes(int64_t bytes);   // "884 MB", "2.15 GB"

} // namespace swarm
