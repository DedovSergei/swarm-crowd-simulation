#pragma once

// Panel legends: the fixed colour scales (viewer/scales.hpp) as gradient bars with their ticks, and the
// categorical zone swatches. They draw the same palette values the shaders receive.

namespace swarm::viewer {

struct ColourScale;

// Gradient bar over the scale's ramp with labelled ticks (threshold names on a second line). zeroSwatch: also show
// the "walkable, 0" colour; noDataText: what normal / grey shading means for this view.
void drawScaleLegend(const ColourScale& scale, const char* title, bool zeroSwatch, const char* noDataText);
// Swatches of the six metric zones (metrics::Zone order)
void drawZoneLegend();

} // namespace swarm::viewer
