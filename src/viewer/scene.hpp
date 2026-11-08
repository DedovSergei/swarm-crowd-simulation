#pragma once

// Scene rendering of the viewer: the stadium mesh and the agents, drawn into the currently bound
// framebuffer. Read-only on the simulation: the agent shader reads the current and previous state buffers
// (and the metric buffers), and nothing here writes a buffer the simulation or the metrics use.

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <filesystem>
#include <string>
#include <vector>

#include <swarm/gpu_caps.hpp>
#include <swarm/gpu_types.hpp>
#include <swarm/shader.hpp>

namespace swarm {
class CrowdSim;
}

namespace swarm::viewer {

// An OBJ (stadium.obj, venue_s.obj) as interleaved position + normal triangles (6 floats per vertex). Throws if it cannot be read.
std::vector<float> loadOBJ(const std::filesystem::path& path);

struct ColourScale;

// Agent colouring (display modes)
enum class AgentColour : int { Speed = 0, Density = 1, Zone = 2 };
const char* agentColourName(AgentColour c);
const ColourScale& agentColourScale(AgentColour c);   // Speed, Density (Zone: categorical, no scale)

// Heatmap overlay metrics (stadium.frag overlayMetric), all from the metric cells since the last restart; NavDistance
// (a venue with a navigation field): the field's walking distance to the nearest exit, static
enum class OverlayMetric : int { PeakDensity = 0, DensityNow, TimeLosE, TimeLosF, TimeCrush, MeanSpeed, Exposure, NavDistance, Count };
struct OverlayInfo {
    const char* name;          // panel
    const char* fileTag;       // export file names
    const ColourScale* scale;
    const char* legendTitle;
    const char* definition;    // tooltip, export sidecar
};
const OverlayInfo& overlayInfo(OverlayMetric m);

struct SceneFrame {
    glm::mat4 view{ 1.0f };
    glm::mat4 projection{ 1.0f };
    float alpha = 0.0f;           // FixedStepClock::renderAlpha(): previous -> current state
    bool agentsVisible = true;
    AgentColour agentColour = AgentColour::Speed;
    GLuint metricCells = 0;       // CrowdMetrics::cellBuffer() (GpuMetricCell per 1 m floor cell)
    GLuint navCells = 0;          // CrowdSim::navBuffer() (GpuNavCell per navigation grid cell; 0: none, the terrace)
    bool overlay = false;         // heatmap overlay on the stadium's floor-like surfaces
    OverlayMetric overlayMetric = OverlayMetric::PeakDensity;
    // The density metrics (peak density, time above the thresholds, crush exposure) over the circulation zones only: the
    // seat rows / treads (metric zone 'tread') keep the normal shading; false: every zone
    bool circulationOnly = true;
};
// Whether the overlay metric is one that the circulation-only scope applies to
bool overlayScoped(OverlayMetric m);

class SceneRenderer {
public:
    // cellInfo: the venue's metric table (MetricVenue::cellInfo()); outerWallInnerDepth: MetricVenue's. objAsset: the venue's
    // render mesh (stadium.obj, venue_s.obj). zoneFromTable: agents coloured by zone take the zone of their 1 m
    // metric cell from the venue table (a seated venue: its zones are not the terrace router's, which boid.vert computes).
    // heightShadeTop > 0: the stadium's normal shading is tinted by height up to that z (a seated venue; 0: none). navGrid:
    // the venue's navigation grid (res, origin, 1 / cell) for the NavDistance overlay; nullptr: none
    // cellInfo of the venue's metric grid (its resolution from the size: venues M and L have larger grids); objAsset empty:
    // the triangles in meshData (seated::mesh, 6 floats per vertex: venues M and L have no OBJ asset)
    SceneRenderer(const std::filesystem::path& shaderDir, const std::vector<GpuMetricCellInfo>& cellInfo, float outerWallInnerDepth,
                  const std::string& objAsset = "stadium.obj", bool zoneFromTable = false, float heightShadeTop = 0.0f,
                  const glm::vec3* navGrid = nullptr, const std::vector<float>* meshData = nullptr);
    // The programs the constructor builds, in its order (the viewer's loading screen compiles them ahead)
    static std::vector<ProgramSpec> programSpecs(const std::filesystem::path& shaderDir);
    static std::vector<ProgramBindings> programBindings();   // what they need from the GPU (swarm/gpu_caps.hpp)
    // The triangles the overlay paints although they are not floor-like: step risers, vertical faces at most
    // RISER_MAX_HEIGHT tall (the terrace's aisle sub-steps, 0.14 m), not walls (from MAX_STEP_UP up: not climbable)
    static constexpr float RISER_MAX_HEIGHT = 0.0096f;   // model units: MAX_STEP_UP (0.30 m)
    ~SceneRenderer();
    SceneRenderer(const SceneRenderer&) = delete;
    SceneRenderer& operator=(const SceneRenderer&) = delete;

    // Clears the bound framebuffer and draws the stadium, then the agents of sim
    void draw(const SceneFrame& f, const CrowdSim& sim) const;

private:
    static void setScale(const ColourScale& s, GLint locLog, GLint locCount, GLint locStops);

    GLuint stadiumProg_ = 0, agentProg_ = 0;
    GLuint cellInfo_ = 0;   // the viewer's own read-only copy of the venue table (binding 8)
    GLuint stadiumVAO_ = 0, stadiumVBO_ = 0, coneVAO_ = 0, coneVBO_ = 0;
    GLsizei stadiumVertices_ = 0, coneVertices_ = 0;
    bool navGrid_ = false;   // the venue has a navigation field (the NavDistance overlay)
    GLint locStadiumModel_ = -1, locStadiumView_ = -1, locStadiumProj_ = -1;
    GLint locStadiumOverlay_ = -1, locStadiumScaleLog_ = -1, locStadiumScaleCount_ = -1, locStadiumScaleStops_ = -1;
    GLint locStadiumScope_ = -1;
    GLint locAgentView_ = -1, locAgentProj_ = -1, locAgentAlpha_ = -1;
    GLint locAgentMode_ = -1, locAgentScaleLog_ = -1, locAgentScaleCount_ = -1, locAgentScaleStops_ = -1;
};

} // namespace swarm::viewer
