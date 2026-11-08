#pragma once

// Colours of the viewer: the same values the figures use
// (tools/experiment/plot_heatmap.py), so a viewer screenshot and a map read alike. Panel chrome uses the
// palette's dark-mode steps (dark ImGui panel); data colours in the 3D scene use the figure values.

#include <imgui.h>
#include <glm/glm.hpp>

#include <cstdint>

namespace swarm::viewer::palette {

constexpr ImU32 rgb(uint32_t hex, uint8_t alpha = 255) {   // 0xRRGGBB -> ImGui's ABGR
    return (uint32_t(alpha) << 24) | ((hex & 0xFFu) << 16) | (hex & 0xFF00u) | ((hex >> 16) & 0xFFu);
}
// 0xRRGGBB -> the sRGB components as floats (the framebuffer is not sRGB-encoded: shaders write these values as is)
inline glm::vec3 vec3(uint32_t hex) {
    return glm::vec3(float((hex >> 16) & 0xFFu), float((hex >> 8) & 0xFFu), float(hex & 0xFFu)) / 255.0f;
}

// Dark-mode chart chrome
constexpr uint32_t SURFACE_DARK = 0x1a1a19;
constexpr uint32_t TEXT_PRIMARY_DARK = 0xffffff;
constexpr uint32_t TEXT_SECONDARY_DARK = 0xc3c2b7;
constexpr uint32_t MUTED = 0x898781;
constexpr uint32_t GRID_DARK = 0x2c2c2a;
constexpr uint32_t AXIS_DARK = 0x383835;
constexpr uint32_t SERIES1_DARK = 0x3987e5;   // categorical slot 1 (blue), dark step

// Sequential (magnitude): one hue, light -> dark = low -> high. plot_heatmap.py's BLUE_RAMP (the sequential blue,
// steps 150 to 700), evenly spaced over the scale: t = i / 11.
constexpr int RAMP_STEPS = 12;
constexpr uint32_t RAMP[RAMP_STEPS] = { 0xb7d3f6, 0x9ec5f4, 0x86b6ef, 0x6da7ec, 0x5598e7, 0x3987e5,
                                        0x2a78d6, 0x256abf, 0x1c5cab, 0x184f95, 0x104281, 0x0d366b };
// A walkable cell whose value is 0 (plot_heatmap.py ZERO): distinct from "no data" (the scene's normal shading)
constexpr uint32_t ZERO = 0xe1e0d9;
// An agent with no density value (its 1 m cell has no counted floor)
constexpr uint32_t NO_DATA = 0x898781;

// Categorical (identity), fixed order, in metrics::Zone order: tread, aisle, walkway, avenue, pitch, exit
// (plot_heatmap.py CATEGORICAL[:6], so the colours follow the zone as in map_zone.png)
constexpr int ZONE_COLOURS = 6;
constexpr uint32_t ZONE[ZONE_COLOURS] = { 0x2a78d6, 0xeb6834, 0x1baf7a, 0xeda100, 0xe87ba4, 0x008300 };

} // namespace swarm::viewer::palette
