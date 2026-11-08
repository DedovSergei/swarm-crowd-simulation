#include "viewer/orbit_camera.hpp"

#include <swarm/sim_params.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <algorithm>
#include <cmath>

namespace swarm::viewer {

namespace {
constexpr float ROTATE_DEG_PER_PX = 0.25f;
constexpr float ZOOM_PER_NOTCH = 0.88f;           // distance factor per wheel notch towards the target
constexpr float GROUND_SPEED_DISTANCES = 0.6f;    // W A S D: target speed in distances per second (caller scales)
} // namespace

glm::vec3 OrbitCamera::offsetDir() const {
    const float y = glm::radians(yawDeg), p = glm::radians(pitchDeg);
    return { std::cos(p) * std::cos(y), std::cos(p) * std::sin(y), std::sin(p) };
}

glm::vec3 OrbitCamera::upVector() const {   // d(offsetDir)/d(pitch): perpendicular to the view, z-positive
    const float y = glm::radians(yawDeg), p = glm::radians(pitchDeg);
    return { -std::sin(p) * std::cos(y), -std::sin(p) * std::sin(y), std::cos(p) };
}

glm::vec3 OrbitCamera::rightVector() const {   // forward x up, forward = -offsetDir
    return glm::normalize(glm::cross(-offsetDir(), upVector()));
}

float OrbitCamera::halfHeightAtTarget() const { return distance * std::tan(glm::radians(0.5f * fovyDeg)); }

glm::mat4 OrbitCamera::view() const { return glm::lookAt(eye(), target, upVector()); }

glm::mat4 OrbitCamera::projection(float aspect) const {
    if (orthographic) {
        const float h = halfHeightAtTarget();
        // Depth range around the target, wide enough for the whole venue at any distance (ortho near may be < 0)
        return glm::ortho(-h * aspect, h * aspect, -h, h, distance - depthRange, distance + depthRange);
    }
    return glm::perspective(glm::radians(fovyDeg), aspect, std::max(0.002f, 0.01f * distance), distance + 10.0f * depthRange / 6.0f);
}

void OrbitCamera::rotate(float dxPx, float dyPx) {
    yawDeg = std::fmod(yawDeg - dxPx * ROTATE_DEG_PER_PX, 360.0f);
    pitchDeg = std::clamp(pitchDeg + dyPx * ROTATE_DEG_PER_PX, MIN_PITCH, MAX_PITCH);
}

void OrbitCamera::pan(float dxPx, float dyPx, float viewportHeightPx) {
    if (viewportHeightPx <= 0.0f) return;
    const float unitsPerPx = 2.0f * halfHeightAtTarget() / viewportHeightPx;   // at the target's depth
    target += (-dxPx * rightVector() + dyPx * upVector()) * unitsPerPx;
}

void OrbitCamera::zoom(float wheelNotches) {
    distance = std::clamp(distance * std::pow(ZOOM_PER_NOTCH, wheelNotches), MIN_DISTANCE, MAX_DISTANCE);
}

void OrbitCamera::moveOnGround(float forward, float right) {
    const float y = glm::radians(yawDeg);
    const glm::vec3 f(-std::cos(y), -std::sin(y), 0.0f);   // horizontal, eye -> target
    const glm::vec3 r(-std::sin(y), std::cos(y), 0.0f);
    target += (forward * f + right * r) * (GROUND_SPEED_DISTANCES * distance);
}

OrbitCamera OrbitCamera::preset(CameraPreset p, int exitIndex, float scale, float exitDepth) {
    OrbitCamera c;
    c.depthRange = 6.0f * std::max(1.0f, scale);
    c.distance *= scale;
    switch (p) {
    case CameraPreset::Default:   // the start view: from the -y side, ~35 degrees down onto the venue
        break;
    case CameraPreset::TopDown:   // straight down, north (+y) up, the whole venue (span 1.9) in view
        c.pitchDeg = 90.0f;
        c.orthographic = true;
        c.distance = 1.05f * scale / std::tan(glm::radians(0.5f * c.fovyDeg));
        break;
    case CameraPreset::Isometric:   // true isometric: orthographic, azimuth 45 degrees, elevation atan(1/sqrt 2)
        c.yawDeg = -45.0f;
        c.pitchDeg = glm::degrees(std::atan(1.0f / std::sqrt(2.0f)));
        c.orthographic = true;
        c.distance = 1.12f * scale / std::tan(glm::radians(0.5f * c.fovyDeg));
        break;
    case CameraPreset::ExitCloseUp: {   // from inside the venue onto one wall gap (metrics::Exit order)
        static const glm::vec2 out[4] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
        const glm::vec2 o = out[std::clamp(exitIndex, 0, 3)];
        c.target = glm::vec3(o * ((exitDepth > 0.0f ? exitDepth : EXIT_DEPTH) - 0.05f), 0.02f);   // in the avenue, just before the gap
        c.yawDeg = glm::degrees(std::atan2(-o.y, -o.x));         // eye on the venue side, looking outward
        c.pitchDeg = 35.0f;
        c.distance = 0.55f;   // 17 m: the queue in the avenue and the gap in the outer wall
        break;
    }
    }
    return c;
}

} // namespace swarm::viewer
