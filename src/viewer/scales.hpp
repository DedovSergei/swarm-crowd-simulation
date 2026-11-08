#pragma once

// Fixed colour scales of the viewer: agent colours and the heatmap overlay. Each maps a value to t in [0, 1]
// on the sequential ramp (palette::RAMP) piecewise-linearly between fixed stops placed at equal t: stops s_0 .. s_k
// sit at t = 0, 1/k, .., 1 (log10 of the value first for a log scale). Values beyond the last stop take t = 1, below
// the first t = 0. The shaders receive the stops as uniforms and evaluate the same mapping (boid.vert,
// stadium.frag: scaleT); the panel legends and docs/VIEWER.md show them. Nothing here depends on the run.

#include <swarm/metrics.hpp>
#include <swarm/sim_params.hpp>

#include <algorithm>
#include <cmath>

namespace swarm::viewer {

constexpr int MAX_SCALE_STOPS = 6;
constexpr int MAX_SCALE_TICKS = 6;

struct ScaleTick {
    float value;
    const char* label;   // printed under the legend bar
    const char* note;    // second line (threshold name), or nullptr
};

struct ColourScale {
    const char* title;
    const char* unit;
    bool log10;
    int stopCount;
    float stops[MAX_SCALE_STOPS];   // log10 values for a log scale
    int tickCount;
    ScaleTick ticks[MAX_SCALE_TICKS];
    const char* rangeNote;          // how the range was chosen (legend tooltip, docs)

    // The shaders' scaleT: t of a value (CPU mirror for the legend ticks)
    float t(float v) const {
        const float x = log10 ? std::log10(std::max(v, 1e-6f)) : v;
        if (x <= stops[0]) return 0.0f;
        for (int k = 0; k + 1 < stopCount; ++k)
            if (x <= stops[k + 1]) return (float(k) + (x - stops[k]) / (stops[k + 1] - stops[k])) / float(stopCount - 1);
        return 1.0f;
    }
};

// Speed of an agent or mean speed of a cell: horizontal, m/s, 0 to the free walking speed (V_MAX = V_FREE_M_S)
inline const ColourScale SPEED_SCALE{
    "Horizontal speed", "m/s", false, 2, { 0.0f, V_FREE_M_S }, 4,
    { { 0.0f, "0", nullptr }, { 0.5f, "0.5", nullptr }, { 1.0f, "1.0", nullptr }, { V_FREE_M_S, "1.34", "free" } },
    "linear, 0 to the free walking speed 1.34 m/s (= V_MAX, the clamp: no agent is faster)" };

// Density, persons/m^2: equal legend space per band, the metric thresholds as stops (metrics.hpp), then 10 and 20
inline const ColourScale DENSITY_SCALE{
    "Density", "persons/m^2", false, 6,
    { 0.0f, float(metrics::LOS_E_P_M2), float(metrics::LOS_F_P_M2), float(metrics::CRUSH_P_M2), 10.0f, 20.0f }, 6,
    { { 0.0f, "0", nullptr }, { float(metrics::LOS_E_P_M2), "1.08", "LoS E" }, { float(metrics::LOS_F_P_M2), "2.17", "LoS F" },
      { float(metrics::CRUSH_P_M2), "5", "crush" }, { 10.0f, "10", nullptr }, { 20.0f, "20+", nullptr } },
    "piecewise linear, equal space per band: 0 | LoS E 1.08 | LoS F 2.17 | crush 5 | 10 | 20 and above (Fruin 1971; "
    "Fruin 1993, Still 2000). The bodies are hard (0.40 m): at most 7.2 persons/m^2 fit (hexagonal packing); the 1 m cells' "
    "cloud-in-cell deposit can read a little above that, and cells with little walkable floor higher" };

// Time at or above a threshold, s: 0 to 120 s, fixed (the terrace's evacuation at N = 4096 takes ~474 s, so long waits saturate at 120+)
inline const ColourScale TIME_SCALE{
    "Time at or above the threshold", "s", false, 2, { 0.0f, 120.0f }, 5,
    { { 0.0f, "0", nullptr }, { 30.0f, "30", nullptr }, { 60.0f, "60", nullptr }, { 90.0f, "90", nullptr }, { 120.0f, "120+", nullptr } },
    "linear, 0 to 120 s and above (a fixed range: longer times take the darkest colour, 120+)" };

// Crush exposure, person-seconds at or above 5 persons/m^2: log10, 1 to 1000, fixed (the waiting crowds exceed 1000 on the terrace's treads)
inline const ColourScale EXPOSURE_SCALE{
    "Crush exposure", "person-s", true, 2, { 0.0f, 3.0f }, 4,
    { { 1.0f, "1", nullptr }, { 10.0f, "10", nullptr }, { 100.0f, "100", nullptr }, { 1000.0f, "1000+", nullptr } },
    "log10, 1 to 1000 person-s and above (a fixed range: values in (0, 1) take the lightest colour, values above 1000 the darkest, 1000+)" };

// Navigation field: the walking distance to the nearest exit, metres, linear 0 to 30 m (venue S's farthest floor:
// 28.4 m, the corner of the walkway; its farthest seat 23 m)
inline const ColourScale NAV_DISTANCE_SCALE{
    "Walking distance to the nearest exit", "m", false, 2, { 0.0f, 30.0f }, 4,
    { { 0.0f, "0", nullptr }, { 10.0f, "10", nullptr }, { 20.0f, "20", nullptr }, { 30.0f, "30+", nullptr } },
    "linear, 0 to 30 m and above (venue S's farthest floor: 28.4 m); the navigation field's shortest legal path" };

} // namespace swarm::viewer
