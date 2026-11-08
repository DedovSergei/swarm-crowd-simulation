#version 430 core
in vec3 Normal;
in vec3 WorldPos;
in float Riser;   // 1 on a step riser (a vertical face at most MAX_STEP_UP tall): painted like the floor beside it
out vec4 FragColor;

// Heatmap overlay: floor-like surfaces (n_z > overlayMinNz) take the colour of the selected
// metric of the 1 m metric cell under them, looked up by world xy in the metric buffers (read on the GPU, read-only).
// Cells without counted floor (excluded in the venue table) keep the normal shading; a counted cell whose value is 0
// takes zeroColor. Scales and colours: src/viewer/scales.hpp, src/viewer/palette.hpp (set by src/viewer/scene.cpp).
struct CellInfo { uvec4 thresholdMass; float walkableM2; uint zone; uint padding0; uint padding1; };   // swarm::GpuMetricCellInfo
struct MetricCell {                                                                                  // swarm::GpuMetricCell
    uint lastMass; uint lastSpeedMass; uint peakMass; uint occupiedSteps;
    uvec4 stepsAbove;
    uvec2 massSteps; uvec2 speedMassSteps; uvec2 exposureMassSteps; uvec2 padding;
};
layout(std430, binding = 8) readonly buffer Info { CellInfo cellInfo[]; };   // the venue's metric table
layout(std430, binding = 9) readonly buffer Cells { MetricCell cells[]; };   // metric accumulators since the restart
// An analytic venue's navigation field (read-only), the overlay 'walking distance to the nearest exit'
struct NavCell { vec2 anchor; float dist; uint info; };                     // swarm::GpuNavCell
layout(std430, binding = 12) readonly buffer Nav { NavCell navCells[]; };

// 0 peak density, 1 density (last step), 2 / 3 / 4 time at or above LoS E / LoS F / crush, 5 mean speed when occupied,
// 6 crush exposure, 7 the navigation field's distance to the nearest exit; < 0: off
uniform int overlayMetric;
uniform float overlayMinNz;
uniform int overlayCirculationOnly;   // 1: the seat rows / treads (metric zone 'tread', 0) keep the normal shading
uniform vec3 rampColors[12];
uniform vec3 zeroColor;
uniform int scaleLog;
uniform int scaleStopCount;
uniform float scaleStops[6];
uniform float cellsPerUnit;   // metric grid: g = xy * cellsPerUnit + gridOffset, in cells from the centre of cell 0
uniform float gridOffset;
uniform int gridRes;
uniform float massOne;        // mass units per person
uniform float peakMinWalkableM2;   // the peak-density overlay shows cells with at least this much floor (metrics::PEAK_MIN_WALKABLE_M2)
uniform float dtRealS;        // seconds per step
uniform float heightShadeTop; // > 0 tints the normal shading by height (x 0.75 at z 0 .. x 1.2 at this z): rows, seat
                              // blocks and gangways tell apart from straight above (seated venues); 0: off (the terrace)
uniform int navRes;           // the navigation grid (cells per axis; 0: no field bound, the terrace), its origin,
uniform float navOrigin;      // 1 / cell (model units), and metres per model unit for the distance
uniform float navInvCell;
uniform float navMetresPerUnit;
uniform uint navReachableFlag;  // nav::NAV_REACHABLE (a uniform: the render shaders compile with the simulation preamble alone)

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

float u64(uvec2 v) { return float(v.x) + float(v.y) * 4294967296.0; }   // (lo, hi) as float

// 0: no data (normal shading), 1: value 0, 2: value in v
int overlayValue(vec2 p, out float v) {
    v = 0.0;
    if (overlayMetric == 7) {   // the navigation field: its cell under p; no path (seat-block tops, the pitch): no data
        if (navRes <= 0) return 0;
        ivec2 n = clamp(ivec2(floor((p - vec2(navOrigin)) * navInvCell)), ivec2(0), ivec2(navRes - 1));
        NavCell c = navCells[n.x + n.y * navRes];
        if ((c.info & navReachableFlag) == 0u) return 0;
        v = c.dist * navMetresPerUnit;
        return v > 0.0 ? 2 : 1;
    }
    ivec2 c = ivec2(floor(p * cellsPerUnit + gridOffset + 0.5));   // the cell whose square contains p
    if (any(lessThan(c, ivec2(0))) || any(greaterThanEqual(c, ivec2(gridRes)))) return 0;
    int i = c.x + c.y * gridRes;
    CellInfo info = cellInfo[i];
    if (info.thresholdMass.x == 0xFFFFFFFFu) return 0;   // excluded: no counted floor
    if (overlayCirculationOnly != 0 && info.zone == 0u) return 0;   // a seat row / tread: neutral (circulation zones only)
    if (overlayMetric == 0 && info.walkableM2 < peakMinWalkableM2) return 0;   // no peak density from a sliver of floor
    MetricCell m = cells[i];
    if (overlayMetric == 0) v = float(m.peakMass) / massOne / info.walkableM2;
    else if (overlayMetric == 1) v = float(m.lastMass) / massOne / info.walkableM2;
    else if (overlayMetric <= 4) v = float(m.stepsAbove[overlayMetric - 2]) * dtRealS;
    else if (overlayMetric == 5) v = m.massSteps == uvec2(0u) ? 0.0 : u64(m.speedMassSteps) / u64(m.massSteps);   // never occupied: 0
    else v = u64(m.exposureMassSteps) / massOne * dtRealS;
    return v > 0.0 ? 2 : 1;
}

void main() {
    // Two-sided lighting: stadium.obj's stand solids are inside-out (their tread tops carry -z normals and clockwise
    // winding; winding and normals agree on every face), so a face seen from its back gets its normal flipped. Without
    // this the stands render ambient-only and the overlay's n_z test skips the treads.
    vec3 n = normalize(gl_FrontFacing ? Normal : -Normal);
    vec3 lightDir = normalize(vec3(0.3, -0.6, 1.0)); // Directional sunlight
    float diff = max(dot(n, lightDir), 0.0);
    vec3 ambient = vec3(0.22, 0.24, 0.28);
    vec3 diffuse = diff * vec3(0.65, 0.65, 0.62);
    vec3 concrete = vec3(0.52, 0.54, 0.56); // Architectural concrete grey
    vec3 color = (ambient + diffuse) * concrete;
    if (heightShadeTop > 0.0) color *= mix(0.75, 1.2, clamp(WorldPos.z / heightShadeTop, 0.0, 1.0));
    if (overlayMetric >= 0 && (n.z > overlayMinNz || Riser > 0.5)) {
        float v;
        // a riser: the cell a hair in front of its face (the lower step's side, where the floor it rises from lies)
        int state = overlayValue(n.z > overlayMinNz ? WorldPos.xy : WorldPos.xy + n.xy * 1e-4, v);
        // Mild shading (x 0.75 - 1.0) keeps the legend's colours readable
        if (state != 0) color = (state == 1 ? zeroColor : ramp(scaleT(v))) * mix(0.75, 1.0, diff);
    }
    FragColor = vec4(color, 1.0);
}
