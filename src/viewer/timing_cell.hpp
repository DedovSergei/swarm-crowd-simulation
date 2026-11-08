#pragma once

// SWARM cell (the UI on / off check): the viewer's real frame loop, timed like tools/perf_ab/bench.cpp's
// 'bench cell', with the same arguments and the same META / CELL output, so tools/perf_ab/ab.py drives it unchanged:
//   SWARM cell --n N --state spawn|congested [--label L] [--snapshots out/bench/snapshots] [--warm-ms 2000]
//              [--steps S] [--continuous] [--trace] [--ui on|off] [--overlay]
// Every frame takes exactly one step (with the metric passes, as the viewer always runs them), renders the scene,
// and draws the panel when the UI is on; CrowdSim's timestamp ring times the four simulation passes. UI on / off
// also from the environment (ab.py labels): SWARM_VIEWER_UI=1 / 0 (default 0); SWARM_VIEWER_OVERLAY=1 adds density
// colouring and the heatmap overlay. A visible window (as in use), VSync off.

namespace swarm::viewer {

int runTimingCell(int argc, char** argv);

} // namespace swarm::viewer
