#include "viewer/scene.hpp"

#include "viewer/palette.hpp"
#include "viewer/scales.hpp"

#include <swarm/assets.hpp>
#include <swarm/crowd_sim.hpp>
#include <swarm/metrics.hpp>
#include <swarm/nav_field.hpp>
#include <swarm/shader.hpp>

#include <glm/gtc/type_ptr.hpp>

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace swarm::viewer {

namespace {

// SSBO bindings read by boid.vert (and stadium.frag: the metric pair)
constexpr GLuint BIND_RENDER_CURR = 0;
constexpr GLuint BIND_RENDER_PREV = 1;
constexpr GLuint BIND_RENDER_CELL_INFO = BIND_METRIC_CELL_INFO;   // 8, as in the metric passes
constexpr GLuint BIND_RENDER_CELLS = BIND_METRIC_CELLS;           // 9
constexpr GLuint BIND_RENDER_NAV = BIND_NAV;                      // 12, as in the predict pass

// Agent mesh: unit cone (base radius 1 on z = 0, apex on +z), scaled by BODY_RADIUS in boid.vert
constexpr int CONE_SEGMENTS = 12;
constexpr float CONE_HEIGHT = 3.0f;   // in base radii: 19.2 mm (0.6 m) tall at BODY_RADIUS = 6.4 mm

// Side triangles of the unit agent cone (no base cap: it rests on the ground)
std::vector<float> makeConeMesh() {
    std::vector<float> v;
    for (int i = 0; i < CONE_SEGMENTS; ++i) {
        float a0 = 6.28318530718f * float(i) / CONE_SEGMENTS, a1 = 6.28318530718f * float(i + 1) / CONE_SEGMENTS;
        v.insert(v.end(), { std::cos(a0), std::sin(a0), 0.0f, std::cos(a1), std::sin(a1), 0.0f, 0.0f, 0.0f, CONE_HEIGHT });
    }
    return v;
}

// The overlay colours surfaces whose normal has n_z above this (floors, treads, aisle steps, wall tops): walls and
// risers keep the normal shading
constexpr float OVERLAY_MIN_NZ = 0.5f;

// Uniforms that never change: the palette and the metric grid's constants (the venue's metric grid, res cells per axis)
void setStaticColourUniforms(GLuint prog, float outerWallInnerDepth, int res) {
    glUseProgram(prog);
    glm::vec3 ramp[palette::RAMP_STEPS];
    for (int i = 0; i < palette::RAMP_STEPS; ++i) ramp[i] = palette::vec3(palette::RAMP[i]);
    glUniform3fv(glGetUniformLocation(prog, "rampColors"), palette::RAMP_STEPS, &ramp[0].x);
    glm::vec3 zones[palette::ZONE_COLOURS];
    for (int i = 0; i < palette::ZONE_COLOURS; ++i) zones[i] = palette::vec3(palette::ZONE[i]);
    const glm::vec3 noData = palette::vec3(palette::NO_DATA), zero = palette::vec3(palette::ZERO);
    if (GLint loc = glGetUniformLocation(prog, "zoneColors"); loc >= 0) glUniform3fv(loc, palette::ZONE_COLOURS, &zones[0].x);
    if (GLint loc = glGetUniformLocation(prog, "noDataColor"); loc >= 0) glUniform3fv(loc, 1, &noData.x);
    if (GLint loc = glGetUniformLocation(prog, "zeroColor"); loc >= 0) glUniform3fv(loc, 1, &zero.x);
    if (GLint loc = glGetUniformLocation(prog, "speedMpsPerUnit"); loc >= 0) glUniform1f(loc, metrics::SPEED_M_S_PER_UNIT);
    glUniform1f(glGetUniformLocation(prog, "cellsPerUnit"), metrics::CELLS_PER_UNIT);
    glUniform1f(glGetUniformLocation(prog, "gridOffset"), metrics::gridOffset(res));
    glUniform1i(glGetUniformLocation(prog, "gridRes"), res);
    glUniform1f(glGetUniformLocation(prog, "massOne"), float(metrics::MASS_ONE));
    if (GLint loc = glGetUniformLocation(prog, "peakMinWalkableM2"); loc >= 0) glUniform1f(loc, float(metrics::PEAK_MIN_WALKABLE_M2));
    if (GLint loc = glGetUniformLocation(prog, "outerWallInnerDepth"); loc >= 0) glUniform1f(loc, outerWallInnerDepth);
    if (GLint loc = glGetUniformLocation(prog, "dtRealS"); loc >= 0) glUniform1f(loc, float(DT_REAL_S));
    glUseProgram(0);
}

} // namespace

bool overlayScoped(OverlayMetric m) {
    return m == OverlayMetric::PeakDensity || m == OverlayMetric::TimeLosE || m == OverlayMetric::TimeLosF || m == OverlayMetric::TimeCrush ||
           m == OverlayMetric::Exposure;
}

const char* agentColourName(AgentColour c) {
    switch (c) {
    case AgentColour::Speed: return "speed";
    case AgentColour::Density: return "density";
    case AgentColour::Zone: return "zone";
    }
    return "?";
}

const ColourScale& agentColourScale(AgentColour c) { return c == AgentColour::Density ? DENSITY_SCALE : SPEED_SCALE; }

const OverlayInfo& overlayInfo(OverlayMetric m) {
    static const OverlayInfo infos[int(OverlayMetric::Count)] = {
        { "Peak density", "peak-density", &DENSITY_SCALE, "Peak density",
          "highest density of the cell in any step since the restart (cloud-in-cell deposit / walkable area)" },
        { "Density (last step)", "density-now", &DENSITY_SCALE, "Density, last step", "density of the cell in the most recent step" },
        { "Time >= LoS E (1.08)", "time-los-e", &TIME_SCALE, "Time at or above LoS E (1.08 persons/m^2)",
          "steps with density >= 1.08 persons/m^2 (Fruin 1971 LoS E) x DT, since the restart" },
        { "Time >= LoS F (2.17)", "time-los-f", &TIME_SCALE, "Time at or above LoS F (2.17 persons/m^2)",
          "steps with density >= 2.17 persons/m^2 (Fruin 1971 LoS F) x DT, since the restart" },
        { "Time >= crush (5)", "time-crush", &TIME_SCALE, "Time at or above the crush threshold (5 persons/m^2)",
          "steps with density >= 5 persons/m^2 (Fruin 1993; Still 2000) x DT, since the restart" },
        { "Mean speed when occupied", "mean-speed", &SPEED_SCALE, "Mean speed when occupied",
          "person-weighted mean horizontal speed over the steps the cell was occupied (never occupied: 0)" },
        { "Crush exposure", "exposure", &EXPOSURE_SCALE, "Crush exposure",
          "person-seconds spent in the cell while its density was >= 5 persons/m^2, since the restart" },
        { "Distance to the nearest exit", "nav-distance", &NAV_DISTANCE_SCALE, "Walking distance to the nearest exit (navigation field)",
          "the navigation field's shortest legal walking distance from the point to the nearest exit (static); no colour: no path "
          "(seat-block and wall tops, the pitch); venues without a field (the terrace): no colour" },
    };
    return infos[std::clamp(int(m), 0, int(OverlayMetric::Count) - 1)];
}

// --- LIGHTWEIGHT OBJ LOADER ---
std::vector<float> loadOBJ(const std::filesystem::path& path) {
    std::ifstream file(path);
    if (!file.is_open()) throw std::runtime_error("Failed to open OBJ file at: " + path.string());

    std::vector<float> outData;
    std::vector<glm::vec3> temp_pos;
    std::vector<glm::vec3> temp_norm;
    std::string line;

    struct VertIdx { int v = 0, vt = 0, vn = 0; };
    auto parseToken = [](const std::string& token) -> VertIdx {
        VertIdx idx;
        size_t s1 = token.find('/');
        if (s1 == std::string::npos) { idx.v = std::stoi(token); return idx; }
        idx.v = std::stoi(token.substr(0, s1));
        size_t s2 = token.find('/', s1 + 1);
        if (s2 != std::string::npos) {
            std::string vnStr = token.substr(s2 + 1);
            if (!vnStr.empty()) idx.vn = std::stoi(vnStr);
        }
        return idx;
        };

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {
            glm::vec3 p; iss >> p.x >> p.y >> p.z;
            temp_pos.push_back(p);
        }
        else if (prefix == "vn") {
            glm::vec3 n; iss >> n.x >> n.y >> n.z;
            temp_norm.push_back(n);
        }
        else if (prefix == "f") {
            std::vector<VertIdx> fVerts;
            std::string token;
            while (iss >> token) fVerts.push_back(parseToken(token));
            if (fVerts.size() < 3) continue;

            for (size_t i = 1; i + 1 < fVerts.size(); ++i) {
                VertIdx idxs[3] = { fVerts[0], fVerts[i], fVerts[i + 1] };
                glm::vec3 p0 = temp_pos[idxs[0].v - 1];
                glm::vec3 p1 = temp_pos[idxs[1].v - 1];
                glm::vec3 p2 = temp_pos[idxs[2].v - 1];
                glm::vec3 faceNorm = glm::normalize(glm::cross(p1 - p0, p2 - p0));

                for (int j = 0; j < 3; ++j) {
                    glm::vec3 p = temp_pos[idxs[j].v - 1];
                    glm::vec3 n = (idxs[j].vn > 0 && idxs[j].vn <= (int)temp_norm.size())
                        ? temp_norm[idxs[j].vn - 1] : faceNorm;
                    outData.insert(outData.end(), { p.x, p.y, p.z, n.x, n.y, n.z });
                }
            }
        }
    }
    std::cout << "Successfully loaded OBJ: " << path.string() << " (" << outData.size() / 6 << " vertices)\n";
    return outData;
}

std::vector<ProgramSpec> SceneRenderer::programSpecs(const std::filesystem::path& shaderDir) {
    return { { shaderDir / "boid.vert", shaderDir / "boid.frag", {}, nullptr }, { shaderDir / "stadium.vert", shaderDir / "stadium.frag", {}, nullptr } };
}

std::vector<ProgramBindings> SceneRenderer::programBindings() {
    return { { "agents", false, { BIND_RENDER_CURR, BIND_RENDER_PREV, BIND_RENDER_CELL_INFO, BIND_RENDER_CELLS }, {} },   // boid.vert
             { "stadium", false, {}, { BIND_RENDER_CELL_INFO, BIND_RENDER_CELLS, BIND_RENDER_NAV } } };                   // stadium.frag
}

SceneRenderer::SceneRenderer(const std::filesystem::path& shaderDir, const std::vector<GpuMetricCellInfo>& cellInfo,
                             float outerWallInnerDepth, const std::string& objAsset, bool zoneFromTable, float heightShadeTop,
                             const glm::vec3* navGrid, const std::vector<float>* meshData) {
    const int res = metrics::gridResOf(cellInfo.size());   // the venue's metric grid
    // Programs (compile/link failures print the driver log and throw)
    const std::vector<ProgramSpec> programs = programSpecs(shaderDir);
    agentProg_ = loadProgram(programs[0]);
    stadiumProg_ = loadProgram(programs[1]);
    locStadiumModel_ = glGetUniformLocation(stadiumProg_, "model");
    locStadiumView_ = glGetUniformLocation(stadiumProg_, "view");
    locStadiumProj_ = glGetUniformLocation(stadiumProg_, "projection");
    locStadiumOverlay_ = glGetUniformLocation(stadiumProg_, "overlayMetric");
    locStadiumScaleLog_ = glGetUniformLocation(stadiumProg_, "scaleLog");
    locStadiumScaleCount_ = glGetUniformLocation(stadiumProg_, "scaleStopCount");
    locStadiumScaleStops_ = glGetUniformLocation(stadiumProg_, "scaleStops");
    locStadiumScope_ = glGetUniformLocation(stadiumProg_, "overlayCirculationOnly");
    setStaticColourUniforms(stadiumProg_, 0.0f, res);
    glUseProgram(stadiumProg_);
    glUniform1f(glGetUniformLocation(stadiumProg_, "overlayMinNz"), OVERLAY_MIN_NZ);
    glUniform1f(glGetUniformLocation(stadiumProg_, "heightShadeTop"), heightShadeTop);
    // The navigation grid (navGrid = (res, origin, 1 / cell)); res 0: no field
    glUniform1i(glGetUniformLocation(stadiumProg_, "navRes"), navGrid ? int(navGrid->x) : 0);
    glUniform1f(glGetUniformLocation(stadiumProg_, "navOrigin"), navGrid ? navGrid->y : 0.0f);
    glUniform1f(glGetUniformLocation(stadiumProg_, "navInvCell"), navGrid ? navGrid->z : 0.0f);
    glUniform1f(glGetUniformLocation(stadiumProg_, "navMetresPerUnit"), WORLD_SCALE_M_PER_UNIT);
    glUniform1ui(glGetUniformLocation(stadiumProg_, "navReachableFlag"), nav::NAV_REACHABLE);
    navGrid_ = navGrid != nullptr;
    glUseProgram(0);
    locAgentView_ = glGetUniformLocation(agentProg_, "view");
    locAgentProj_ = glGetUniformLocation(agentProg_, "projection");
    locAgentAlpha_ = glGetUniformLocation(agentProg_, "alpha");
    locAgentMode_ = glGetUniformLocation(agentProg_, "colorMode");
    locAgentScaleLog_ = glGetUniformLocation(agentProg_, "scaleLog");
    locAgentScaleCount_ = glGetUniformLocation(agentProg_, "scaleStopCount");
    locAgentScaleStops_ = glGetUniformLocation(agentProg_, "scaleStops");
    setStaticColourUniforms(agentProg_, outerWallInnerDepth, res);
    glUseProgram(agentProg_);
    glUniform1i(glGetUniformLocation(agentProg_, "zoneFromTable"), zoneFromTable ? 1 : 0);
    glUseProgram(0);

    // The venue's metric table, read by the shaders (written once here, never by the GL)
    glGenBuffers(1, &cellInfo_);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, cellInfo_);
    glBufferData(GL_SHADER_STORAGE_BUFFER, GLsizeiptr(cellInfo.size() * sizeof(GpuMetricCellInfo)), cellInfo.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    // Agent mesh (unit cone, scaled to BODY_RADIUS in boid.vert)
    const std::vector<float> cone = makeConeMesh();
    coneVertices_ = GLsizei(cone.size() / 3);
    glGenVertexArrays(1, &coneVAO_);
    glGenBuffers(1, &coneVBO_);
    glBindVertexArray(coneVAO_);
    glBindBuffer(GL_ARRAY_BUFFER, coneVBO_);
    glBufferData(GL_ARRAY_BUFFER, GLsizeiptr(cone.size() * sizeof(float)), cone.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // Stadium mesh: position (layout 0), normal (layout 1) and the riser flag (layout 2): a vertical triangle (|n_z| <
    // 0.1) at most RISER_MAX_HEIGHT tall, a step's riser, which the overlay paints like the floor beside it
    const std::vector<float> stadium = objAsset.empty() && meshData ? *meshData : loadOBJ(resolveAsset(objAsset));
    std::vector<float> verts;
    verts.reserve(stadium.size() / 6 * 7);
    for (size_t t = 0; t + 17 < stadium.size(); t += 18) {
        float zLo = 1e30f, zHi = -1e30f;
        for (int k = 0; k < 3; ++k) { zLo = std::min(zLo, stadium[t + 6 * k + 2]); zHi = std::max(zHi, stadium[t + 6 * k + 2]); }
        const bool riser = std::abs(stadium[t + 5]) < 0.1f && zHi - zLo <= RISER_MAX_HEIGHT;
        for (int k = 0; k < 3; ++k) {
            verts.insert(verts.end(), stadium.begin() + std::ptrdiff_t(t + 6 * k), stadium.begin() + std::ptrdiff_t(t + 6 * k + 6));
            verts.push_back(riser ? 1.0f : 0.0f);
        }
    }
    stadiumVertices_ = GLsizei(verts.size() / 7);
    glGenVertexArrays(1, &stadiumVAO_);
    glGenBuffers(1, &stadiumVBO_);
    glBindVertexArray(stadiumVAO_);
    glBindBuffer(GL_ARRAY_BUFFER, stadiumVBO_);
    glBufferData(GL_ARRAY_BUFFER, GLsizeiptr(verts.size() * sizeof(float)), verts.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

SceneRenderer::~SceneRenderer() {
    glDeleteVertexArrays(1, &stadiumVAO_);
    glDeleteVertexArrays(1, &coneVAO_);
    glDeleteBuffers(1, &stadiumVBO_);
    glDeleteBuffers(1, &coneVBO_);
    glDeleteBuffers(1, &cellInfo_);
    glDeleteProgram(stadiumProg_);
    glDeleteProgram(agentProg_);
}

void SceneRenderer::setScale(const ColourScale& s, GLint locLog, GLint locCount, GLint locStops) {
    glUniform1i(locLog, s.log10 ? 1 : 0);
    glUniform1i(locCount, s.stopCount);
    glUniform1fv(locStops, s.stopCount, s.stops);
}

void SceneRenderer::draw(const SceneFrame& f, const CrowdSim& sim) const {
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // 1. Stadium
    glUseProgram(stadiumProg_);
    const glm::mat4 model(1.0f);
    glUniformMatrix4fv(locStadiumModel_, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(locStadiumView_, 1, GL_FALSE, glm::value_ptr(f.view));
    glUniformMatrix4fv(locStadiumProj_, 1, GL_FALSE, glm::value_ptr(f.projection));
    glUniform1i(locStadiumOverlay_, f.overlay ? int(f.overlayMetric) : -1);
    glUniform1i(locStadiumScope_, f.circulationOnly && overlayScoped(f.overlayMetric) ? 1 : 0);
    setScale(*overlayInfo(f.overlayMetric).scale, locStadiumScaleLog_, locStadiumScaleCount_, locStadiumScaleStops_);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_RENDER_CELL_INFO, cellInfo_);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_RENDER_CELLS, f.metricCells);
    // the navigation field (read-only); without one a dummy keeps binding 12 valid (the shader reads it only if navRes > 0)
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_RENDER_NAV, navGrid_ && f.navCells ? f.navCells : cellInfo_);
    glBindVertexArray(stadiumVAO_);
    glDrawArrays(GL_TRIANGLES, 0, stadiumVertices_);

    // 2. Agents, interpolated between the previous and current states
    if (f.agentsVisible) {
        glUseProgram(agentProg_);
        glUniformMatrix4fv(locAgentView_, 1, GL_FALSE, glm::value_ptr(f.view));
        glUniformMatrix4fv(locAgentProj_, 1, GL_FALSE, glm::value_ptr(f.projection));
        glUniform1f(locAgentAlpha_, f.alpha);
        glUniform1i(locAgentMode_, int(f.agentColour));
        setScale(agentColourScale(f.agentColour), locAgentScaleLog_, locAgentScaleCount_, locAgentScaleStops_);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_RENDER_CURR, sim.currentStateBuffer());
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BIND_RENDER_PREV, sim.previousStateBuffer());
        glBindVertexArray(coneVAO_);
        glDrawArraysInstanced(GL_TRIANGLES, 0, coneVertices_, sim.numBoids());
    }
    glBindVertexArray(0);
}

} // namespace swarm::viewer
