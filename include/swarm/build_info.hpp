#pragma once

// Build facts of the binary. The commit and the dirty flag are determined at BUILD
// time: cmake/build_info.cmake runs on every build and rewrites the generated header behind
// src/build_info.cpp only when HEAD or the working-tree state changed. A commit followed by a plain
// rebuild (no reconfigure) reports the new commit; nothing depends on the reflog.
// Library: swarm_build_info (linked by swarm_core and by every executable).

namespace swarm::buildinfo {

const char* gitCommit();       // full SHA-1 of HEAD, or "unknown" (no git, or not a git checkout)
int gitDirty();                // 1: 'git status --porcelain' listed changes (untracked included); 0: clean; -1: unknown
const char* gitDirtyField();   // the same as a CSV field: "1", "0" or "unknown"
const char* gitDescribe();     // "<short>" or "<short>-dirty", or "unknown"
const char* buildConfig();     // the CMake configuration (Release, Debug, ...)

} // namespace swarm::buildinfo
