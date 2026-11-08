#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <cstddef>
#include <filesystem>
#include <vector>

#include <swarm/sim_params.hpp>

namespace swarm {

// stadium.sdf: mesh-to-sdf bake (voxel_resolution=128, pad=True) repaired by tools/repair_sdf.py.
// NumPy C-order [x][y][z] (z fastest), world-unit distances, d < 0 inside solid.
// Grid (sim_params.hpp): sample index i (0..129, 0 and 129 = pad) sits at SDF_MIN + (i - 1) * SDF_SPACING.
inline const glm::vec3 SDF_MIN(SDF_ORIGIN.x, SDF_ORIGIN.y, SDF_ORIGIN.z);
constexpr size_t SDF_VOXELS = static_cast<size_t>(SDF_RES) * SDF_RES * SDF_RES;
static_assert(SDF_VOXELS * sizeof(float) == 8788000, "stadium.sdf is a 130^3 float32 grid");

// Reads stadium.sdf into memory (no GL). Returns an empty vector (after logging) if the file is
// missing or has the wrong size.
std::vector<float> loadSDFVolume(const std::filesystem::path& filename);

// Loads the SDF (loadSDFVolume) into a GL_R32F 3D texture and keeps the CPU copy for
// sampleSDF_CPU and sdfVolumeCPU. Returns 0 (after logging) if the file is missing or has the
// wrong size.
GLuint loadSDFTexture3D(const std::filesystem::path& filename);

// The CPU copy kept by loadSDFTexture3D (empty before it has succeeded)
const std::vector<float>& sdfVolumeCPU();

// Mirrors GPU map() on the GL_LINEAR / CLAMP_TO_EDGE 3D texture (texel-centre convention), with
// exact float weights (the hardware quantizes them). Returns 1.0 outside the volume or for an
// empty volume.
float sampleSDF(const std::vector<float>& volume, glm::vec3 pos);

// sampleSDF on the copy kept by loadSDFTexture3D (1.0 before it has succeeded)
float sampleSDF_CPU(glm::vec3 pos);

// CPU mirrors of the analytic pitch fence in physics.comp (@fence block): signed distance to
// the collision fence (an infinite vertical extrusion, parameters in sim_params.hpp) and the
// gradient of its active term, which is horizontal (z = 0).
float sdBox2(glm::vec2 p, glm::vec2 halfSize);
glm::vec2 sdBox2Grad(glm::vec2 p, glm::vec2 halfSize);
float sdFence(glm::vec3 p);
glm::vec3 sdFenceGradient(glm::vec3 p);

} // namespace swarm
