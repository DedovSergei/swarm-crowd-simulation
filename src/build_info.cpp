#include <swarm/build_info.hpp>

// Generated on every build by cmake/build_info.cmake (in the build tree); this is its only includer,
// so a new commit recompiles this file alone and relinks.
#include "swarm_git_info.h"

#ifndef SWARM_BUILD_CONFIG
#define SWARM_BUILD_CONFIG "unknown"
#endif

namespace swarm::buildinfo {

const char* gitCommit() { return SWARM_GIT_COMMIT; }
int gitDirty() { return SWARM_GIT_DIRTY; }
const char* gitDirtyField() { return SWARM_GIT_DIRTY == 1 ? "1" : SWARM_GIT_DIRTY == 0 ? "0" : "unknown"; }
const char* gitDescribe() { return SWARM_GIT_DESCRIBE; }
const char* buildConfig() { return SWARM_BUILD_CONFIG; }

} // namespace swarm::buildinfo
