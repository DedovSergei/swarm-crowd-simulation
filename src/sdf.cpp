#include <swarm/sdf.hpp>

#include <swarm/sim_params.hpp>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

namespace swarm {

namespace {
// CPU copy of the volume for spawn validation
std::vector<float> g_sdfCPU;
} // namespace

const std::vector<float>& sdfVolumeCPU() { return g_sdfCPU; }

float sampleSDF_CPU(glm::vec3 pos) { return sampleSDF(g_sdfCPU, pos); }

float sampleSDF(const std::vector<float>& volume, glm::vec3 pos) {
    if (volume.empty()) return 1.0f;
    glm::vec3 uvw = (1.5f + (pos - SDF_MIN) / SDF_SPACING) / float(SDF_RES);
    if (glm::any(glm::lessThan(uvw, glm::vec3(0.0f))) || glm::any(glm::greaterThan(uvw, glm::vec3(1.0f)))) {
        return 1.0f;
    }
    glm::vec3 t = uvw * float(SDF_RES) - 0.5f;
    glm::vec3 base = glm::floor(t);
    glm::vec3 f = t - base;
    const float* samples = volume.data();   // raw reads: unchecked in Debug builds too (hot path)
    auto at = [samples](int x, int y, int z) {
        x = std::clamp(x, 0, SDF_RES - 1);
        y = std::clamp(y, 0, SDF_RES - 1);
        z = std::clamp(z, 0, SDF_RES - 1);
        return samples[(static_cast<size_t>(x) * SDF_RES + y) * SDF_RES + z];
    };
    int x0 = int(base.x), y0 = int(base.y), z0 = int(base.z);
    float c00 = glm::mix(at(x0, y0, z0),         at(x0 + 1, y0, z0),         f.x);
    float c10 = glm::mix(at(x0, y0 + 1, z0),     at(x0 + 1, y0 + 1, z0),     f.x);
    float c01 = glm::mix(at(x0, y0, z0 + 1),     at(x0 + 1, y0, z0 + 1),     f.x);
    float c11 = glm::mix(at(x0, y0 + 1, z0 + 1), at(x0 + 1, y0 + 1, z0 + 1), f.x);
    return glm::mix(glm::mix(c00, c10, f.y), glm::mix(c01, c11, f.y), f.z);
}

float sdBox2(glm::vec2 p, glm::vec2 halfSize) {
    glm::vec2 q = glm::abs(p) - halfSize;
    return glm::length(glm::max(q, 0.0f)) + std::min(std::max(q.x, q.y), 0.0f);
}

glm::vec2 sdBox2Grad(glm::vec2 p, glm::vec2 halfSize) {
    glm::vec2 q = glm::abs(p) - halfSize;
    glm::vec2 s(p.x < 0.0f ? -1.0f : 1.0f, p.y < 0.0f ? -1.0f : 1.0f);
    glm::vec2 g = std::max(q.x, q.y) > 0.0f ? glm::max(q, 0.0f) / glm::length(glm::max(q, 0.0f))
                                            : (q.x > q.y ? glm::vec2(1.0f, 0.0f) : glm::vec2(0.0f, 1.0f));
    return s * g;
}

namespace {
const glm::vec2 kFenceCenter(FENCE_CENTER.x, FENCE_CENTER.y);
const glm::vec2 kFenceHalfMid(FENCE_HALF_MID.x, FENCE_HALF_MID.y);
glm::vec2 toGlm(Float2 v) { return glm::vec2(v.x, v.y); }
} // namespace

float sdFence(glm::vec3 p) {
    float d = std::abs(sdBox2(glm::vec2(p) - kFenceCenter, kFenceHalfMid)) - FENCE_HALF_THK_COLL;
    for (const FenceGate& gate : FENCE_GATES)
        d = std::max(d, -sdBox2(glm::vec2(p) - toGlm(gate.center), toGlm(gate.halfSize)));
    return d;
}

glm::vec3 sdFenceGradient(glm::vec3 p) {
    glm::vec2 rel = glm::vec2(p) - kFenceCenter;
    float box = sdBox2(rel, kFenceHalfMid);
    float d = std::abs(box) - FENCE_HALF_THK_COLL;
    glm::vec2 g = (box < 0.0f ? -1.0f : 1.0f) * sdBox2Grad(rel, kFenceHalfMid);
    for (const FenceGate& gate : FENCE_GATES) {
        glm::vec2 gp = glm::vec2(p) - toGlm(gate.center);
        float dGate = -sdBox2(gp, toGlm(gate.halfSize));
        if (dGate > d) { d = dGate; g = -sdBox2Grad(gp, toGlm(gate.halfSize)); }
    }
    return glm::vec3(g, 0.0f);
}

std::vector<float> loadSDFVolume(const std::filesystem::path& filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open SDF file at: " << filename.string() << std::endl;
        return {};
    }

    const std::streamsize expectedBytes = static_cast<std::streamsize>(SDF_VOXELS * sizeof(float));
    const std::streamsize fileBytes = file.tellg();
    if (fileBytes != expectedBytes) {
        std::cerr << "Error: SDF file " << filename.string() << " is " << fileBytes << " bytes, expected "
                  << expectedBytes << " (" << SDF_RES << "^3 float32)." << std::endl;
        return {};
    }
    file.seekg(0);

    std::vector<float> volume(SDF_VOXELS);
    file.read(reinterpret_cast<char*>(volume.data()), expectedBytes);
    if (file.gcount() != expectedBytes) {
        std::cerr << "Error: Short read on SDF file " << filename.string() << " (" << file.gcount() << " bytes)." << std::endl;
        return {};
    }
    return volume;
}

GLuint loadSDFTexture3D(const std::filesystem::path& filename) {
    const int res = SDF_RES;
    g_sdfCPU = loadSDFVolume(filename);
    if (g_sdfCPU.empty()) return 0;

    GLuint texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_3D, texID);

    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // Uploaded as-is: GL's fastest axis (s) is the file's z, so samplers look up with .zyx
    glTexImage3D(GL_TEXTURE_3D, 0, GL_R32F, res, res, res, 0, GL_RED, GL_FLOAT, g_sdfCPU.data());
    glBindTexture(GL_TEXTURE_3D, 0);

    std::cout << "Successfully loaded 3D SDF Texture (" << res << "^3 voxels).\n";
    return texID;
}

} // namespace swarm
