#pragma once

#include <filesystem>
#include <string>

namespace swarm {

// Resolves a path relative to the asset root (shaders/, stadium.obj, stadium.sdf).
// Search order:
//   1. the executable's directory (CMake copies assets next to SWARM.exe)
//   2. the current working directory
//   3. the source tree (SWARM_SOURCE_DIR, baked in at build time)
// Throws std::runtime_error listing every candidate if none exists.
std::filesystem::path resolveAsset(const std::filesystem::path& relative);

// The directory of the running executable (empty if it cannot be determined)
std::filesystem::path executableDirectory();

// A path in the system temp directory private to this process: <temp>/<name>_<process id>, so that two tool processes
// running at once never overwrite or delete each other's shader variants
std::filesystem::path processTempPath(const std::string& name);

} // namespace swarm
