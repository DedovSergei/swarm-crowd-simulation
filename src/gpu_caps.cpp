#include <swarm/gpu_caps.hpp>

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>

namespace swarm {

GpuLimits applyGpuLimitsOverride(GpuLimits l, const std::string& text) {
    std::istringstream items(text);
    std::string item;
    while (std::getline(items, item, ',')) {
        const size_t eq = item.find('=');
        if (eq == std::string::npos) throw std::invalid_argument("SWARM_GPU_LIMITS: expected key=value, got \"" + item + "\"");
        const std::string key = item.substr(0, eq), value = item.substr(eq + 1);
        if (key == "gl") {
            const size_t dot = value.find('.');
            if (dot == std::string::npos) throw std::invalid_argument("SWARM_GPU_LIMITS: gl=<major>.<minor>, got \"" + value + "\"");
            l.glMajor = std::stoi(value.substr(0, dot));
            l.glMinor = std::stoi(value.substr(dot + 1));
        } else if (key == "bindings") {
            l.ssboBindings = std::stoi(value);
        } else if (key == "blocks") {
            l.computeSsboBlocks = std::stoi(value);
        } else if (key == "vertexblocks") {
            l.vertexSsboBlocks = std::stoi(value);
        } else if (key == "fragmentblocks") {
            l.fragmentSsboBlocks = std::stoi(value);
        } else if (key == "blocksize") {
            l.ssboBlockBytes = std::stoll(value);
        } else {
            throw std::invalid_argument("SWARM_GPU_LIMITS: unknown limit \"" + key + "\" (gl, bindings, blocks, vertexblocks, fragmentblocks, blocksize)");
        }
        l.simulated = true;
    }
    return l;
}

GpuLimits readGpuLimits() {
    GpuLimits l;
    glGetIntegerv(GL_MAJOR_VERSION, &l.glMajor);
    glGetIntegerv(GL_MINOR_VERSION, &l.glMinor);
    glGetIntegerv(GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS, &l.ssboBindings);
    glGetIntegerv(GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS, &l.computeSsboBlocks);
    glGetIntegerv(GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS, &l.vertexSsboBlocks);
    glGetIntegerv(GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS, &l.fragmentSsboBlocks);
    GLint64 blockBytes = 0;
    glGetInteger64v(GL_MAX_SHADER_STORAGE_BLOCK_SIZE, &blockBytes);
    l.ssboBlockBytes = int64_t(blockBytes);
    if (const GLubyte* s = glGetString(GL_RENDERER)) l.renderer = reinterpret_cast<const char*>(s);
    if (const GLubyte* s = glGetString(GL_VERSION)) l.version = reinterpret_cast<const char*>(s);
    if (const char* env = std::getenv("SWARM_GPU_LIMITS"); env && *env) l = applyGpuLimitsOverride(l, env);
    return l;
}

bool simulatedGlTooOld() {
    const char* env = std::getenv("SWARM_GPU_LIMITS");
    if (!env || !*env) return false;
    GpuLimits l;
    l.glMajor = GL_REQUIRED_MAJOR;
    l.glMinor = GL_REQUIRED_MINOR;
    l = applyGpuLimitsOverride(l, env);
    return l.glMajor < GL_REQUIRED_MAJOR || (l.glMajor == GL_REQUIRED_MAJOR && l.glMinor < GL_REQUIRED_MINOR);
}

GpuRequirements gpuRequirements(const std::vector<ProgramBindings>& programs, const std::vector<GpuBufferUse>& buffers) {
    GpuRequirements r;
    for (const ProgramBindings& p : programs) {
        for (GLuint b : p.ssbo) r.ssboBindings = std::max(r.ssboBindings, int(b) + 1);
        for (GLuint b : p.fragmentSsbo) r.ssboBindings = std::max(r.ssboBindings, int(b) + 1);
        if (p.compute) {
            r.computeSsboBlocks = std::max(r.computeSsboBlocks, int(p.ssbo.size()));
        } else {
            r.vertexSsboBlocks = std::max(r.vertexSsboBlocks, int(p.ssbo.size()));
            r.fragmentSsboBlocks = std::max(r.fragmentSsboBlocks, int(p.fragmentSsbo.size()));
        }
    }
    for (const GpuBufferUse& b : buffers)
        if (b.bytes > r.ssboBlockBytes) {
            r.ssboBlockBytes = b.bytes;
            r.largestBuffer = b.name;
            r.blockBytesEstimated = b.estimated;
        }
    return r;
}

std::string formatBytes(int64_t bytes) {
    char b[32];
    if (bytes >= 1000000000) std::snprintf(b, sizeof b, "%.2f GB", double(bytes) / 1e9);
    else std::snprintf(b, sizeof b, "%.0f MB", double(bytes) / 1e6);
    return b;
}

std::string gpuBlockShortfall(const std::string& buffer, int64_t bytes, bool estimated, const GpuLimits& limits) {
    if (bytes <= limits.ssboBlockBytes) return "";
    return std::string("needs a buffer of ") + (estimated ? "up to " : "") + formatBytes(bytes) + " (" + buffer + "), this GPU allows " + formatBytes(limits.ssboBlockBytes);
}

std::string gpuShortfall(const GpuRequirements& need, const GpuLimits& limits) {
    std::string why;
    const auto add = [&](const std::string& s) {
        if (!s.empty()) why += (why.empty() ? "" : "; ") + s;
    };
    if (limits.glMajor < GL_REQUIRED_MAJOR || (limits.glMajor == GL_REQUIRED_MAJOR && limits.glMinor < GL_REQUIRED_MINOR))
        add("needs OpenGL " + std::to_string(GL_REQUIRED_MAJOR) + "." + std::to_string(GL_REQUIRED_MINOR) + ", this GPU has " + std::to_string(limits.glMajor) + "." +
            std::to_string(limits.glMinor));
    if (need.ssboBindings > limits.ssboBindings)
        add("needs " + std::to_string(need.ssboBindings) + " SSBO bindings, this GPU has " + std::to_string(limits.ssboBindings));
    if (need.computeSsboBlocks > limits.computeSsboBlocks)
        add("needs " + std::to_string(need.computeSsboBlocks) + " SSBOs per compute program, this GPU has " + std::to_string(limits.computeSsboBlocks));
    if (need.vertexSsboBlocks > limits.vertexSsboBlocks)
        add("needs " + std::to_string(need.vertexSsboBlocks) + " SSBOs per vertex shader, this GPU has " + std::to_string(limits.vertexSsboBlocks));
    if (need.fragmentSsboBlocks > limits.fragmentSsboBlocks)
        add("needs " + std::to_string(need.fragmentSsboBlocks) + " SSBOs per fragment shader, this GPU has " + std::to_string(limits.fragmentSsboBlocks));
    add(gpuBlockShortfall(need.largestBuffer, need.ssboBlockBytes, need.blockBytesEstimated, limits));
    return why;
}

} // namespace swarm
