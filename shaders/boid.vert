#version 430 core

// Agent render: an upright cone with base radius BODY_RADIUS (the hard body), drawn at
// the position interpolated between the previous and current physics states.
// Colour (src/viewer/scene.cpp sets the uniforms): by horizontal speed, by the density of the 1 m metric
// cell that contains the agent (last step), or by zone (the metric zones' rule, per position).
// Read-only: every buffer here is readonly.
layout (location = 0) in vec3 aPos;   // unit cone: base radius 1 on z = 0, apex on +z

struct Boid { vec4 position; vec4 velocity; };   // swarm::GpuBoid (boidID-indexed in both buffers)
struct CellInfo { uvec4 thresholdMass; float walkableM2; uint zone; uint padding0; uint padding1; };   // swarm::GpuMetricCellInfo
struct MetricCell {                                                                                  // swarm::GpuMetricCell
    uint lastMass; uint lastSpeedMass; uint peakMass; uint occupiedSteps;
    uvec4 stepsAbove;
    uvec2 massSteps; uvec2 speedMassSteps; uvec2 exposureMassSteps; uvec2 padding;
};

layout(std430, binding = 0) readonly buffer CurrBuffer { Boid curr[]; };   // state after the last step
layout(std430, binding = 1) readonly buffer PrevBuffer { Boid prev[]; };   // state one step earlier
layout(std430, binding = 8) readonly buffer Info { CellInfo cellInfo[]; };     // the venue's metric table
layout(std430, binding = 9) readonly buffer Cells { MetricCell cells[]; };     // metric accumulators

uniform mat4 view;
uniform mat4 projection;
uniform float alpha;   // FixedStepClock::renderAlpha(), in [0, 1]

// Colour (viewer/scales.hpp, viewer/palette.hpp)
uniform int colorMode;              // 0 speed, 1 density, 2 zone
uniform vec3 rampColors[12];        // sequential ramp, t = i / 11
uniform int scaleLog;               // 1: the stops are log10 values
uniform int scaleStopCount;
uniform float scaleStops[6];
uniform vec3 zoneColors[6];         // metrics::Zone order
uniform vec3 noDataColor;
uniform float speedMpsPerUnit;      // metrics::SPEED_M_S_PER_UNIT
// Metric grid (metrics.hpp): g = xy * cellsPerUnit + gridOffset is the position in cells from the centre of cell 0
uniform float cellsPerUnit;
uniform float gridOffset;
uniform int gridRes;
uniform float massOne;              // metrics::MASS_ONE: mass units per person
uniform float outerWallInnerDepth;  // metrics::MetricVenue: start of the exit zone
uniform int zoneFromTable;          // 1 = the zone of the agent's 1 m metric cell from the venue table (seated venues)

out vec3 Color;
out vec3 Normal;

float scaleT(float v) {
    float x = scaleLog != 0 ? log(max(v, 1e-6)) / log(10.0) : v;
    if (x <= scaleStops[0]) return 0.0;
    for (int k = 0; k + 1 < scaleStopCount; ++k)
        if (x <= scaleStops[k + 1]) return (float(k) + (x - scaleStops[k]) / (scaleStops[k + 1] - scaleStops[k])) / float(scaleStopCount - 1);
    return 1.0;
}

vec3 ramp(float t) {
    float x = clamp(t, 0.0, 1.0) * 11.0;
    int i = min(int(x), 10);
    return mix(rampColors[i], rampColors[i + 1], x - float(i));
}

// metrics::sampleZone: pitch inside the fence midline; avenue (exit beyond the outer wall's inner face) where
// lat < AVENUE_HALF; walkway up to dep WALKWAY_MAX; aisle where lat < AISLE_MAX; else tread
int zoneAt(vec2 p) {
    if (all(lessThan(abs(p - FENCE_CENTER), FENCE_HALF_MID))) return 4;
    vec2 a = abs(p);
    bool alongX = a.y >= a.x;
    float lat = alongX ? a.x : a.y;
    float dep = alongX ? a.y : a.x;
    if (lat < AVENUE_HALF) return dep >= outerWallInnerDepth ? 5 : 3;
    if (dep < WALKWAY_MAX) return 2;
    if (lat < AISLE_MAX) return 1;
    return 0;
}

vec3 densityColor(vec2 p) {
    ivec2 c = ivec2(floor(p * cellsPerUnit + gridOffset + 0.5));   // the cell whose square contains p
    if (any(lessThan(c, ivec2(0))) || any(greaterThanEqual(c, ivec2(gridRes)))) return noDataColor;
    int i = c.x + c.y * gridRes;
    if (cellInfo[i].thresholdMass.x == 0xFFFFFFFFu) return noDataColor;   // excluded cell (< 0.1 m^2 of floor)
    float density = float(cells[i].lastMass) / massOne / cellInfo[i].walkableM2;
    return ramp(scaleT(density));
}

void main() {
    Boid c = curr[gl_InstanceID];
    Boid p = prev[gl_InstanceID];

    // Evacuated (position.w == 0) in either state: the agent is parked off-screen, so
    // interpolating would sweep it across the scene. Emit a point outside the clip volume.
    if (c.position.w == 0.0 || p.position.w == 0.0) {
        Color = vec3(0.0);
        Normal = vec3(0.0, 0.0, 1.0);
        gl_Position = vec4(0.0, 0.0, 2.0, 1.0);
        return;
    }

    vec3 worldPos = mix(p.position.xyz, c.position.xyz, alpha);

    // Lighting Prep
    Normal = normalize(aPos);

    // --- COLOR (current state) ---
    if (colorMode == 1) Color = densityColor(c.position.xy);
    else if (colorMode == 2) {
        if (zoneFromTable != 0) {   // the venue table's zone of the cell containing the agent (seated venues)
            ivec2 cc = clamp(ivec2(floor(c.position.xy * cellsPerUnit + gridOffset + 0.5)), ivec2(0), ivec2(gridRes - 1));
            uint z = cellInfo[cc.x + cc.y * gridRes].zone;
            Color = z < 6u ? zoneColors[z] : noDataColor;
        } else {
            Color = zoneColors[zoneAt(c.position.xy)];
        }
    }
    else Color = ramp(scaleT(length(c.velocity.xy) * speedMpsPerUnit));

    // Final Position: the centre rests BODY_RADIUS above the floor, so the cone base (local
    // z = 0) goes BODY_RADIUS below it to stand on the floor
    gl_Position = projection * view * vec4(worldPos + aPos * BODY_RADIUS - vec3(0.0, 0.0, BODY_RADIUS), 1.0);
}
