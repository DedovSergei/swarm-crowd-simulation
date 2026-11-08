#pragma once

// Orbit camera of the viewer: it circles a target point (the venue centre by default) at a distance,
// with an azimuth (yaw, about +z) and an elevation (pitch). Perspective or orthographic; in orthographic mode the
// view height at the target is the perspective one, so switching keeps the scale. Model units (z up).

#include <glm/glm.hpp>

namespace swarm::viewer {

enum class CameraPreset { Default, TopDown, Isometric, ExitCloseUp };

struct OrbitCamera {
    glm::vec3 target{ 0.0f };
    float yawDeg = -90.0f;      // azimuth of the eye around the target: -90 = eye on the -y side, looking +y
    float pitchDeg = 35.0f;     // elevation of the eye above the target's horizontal plane; 90 = straight down
    float distance = 2.4f;      // eye to target, model units
    float fovyDeg = 45.0f;
    bool orthographic = false;

    static constexpr float MIN_PITCH = -10.0f, MAX_PITCH = 90.0f;
    static constexpr float MIN_DISTANCE = 0.03f, MAX_DISTANCE = 30.0f;   // venue L spans 6.4 units
    float depthRange = 6.0f;    // the orthographic depth range either side of the target (scales with the venue)

    glm::vec3 offsetDir() const;   // unit vector target -> eye
    glm::vec3 eye() const { return target + distance * offsetDir(); }
    glm::vec3 upVector() const;    // screen up (well defined at pitch 90)
    glm::vec3 rightVector() const; // screen right
    float halfHeightAtTarget() const;   // half the view height at the target distance (= the ortho half height)
    glm::mat4 view() const;
    glm::mat4 projection(float aspect) const;

    // Mouse: drag in pixels, the viewport height in pixels; wheel in notches (+ = zoom in)
    void rotate(float dxPx, float dyPx);
    void pan(float dxPx, float dyPx, float viewportHeightPx);
    void zoom(float wheelNotches);
    // Keys (W A S D): move the target on the ground plane, along the view's horizontal forward and right
    void moveOnGround(float forward, float right);

    // exitIndex: metrics::Exit order (0 +x, 1 -x, 2 +y, 3 -y), used by ExitCloseUp only. scale = the venue's domain
    // half-width in model units (the terrace and S: 1; M 1.9, L 3.2): the overview presets' distances scale with it; exitDepth: the
    // venue's exit test depth (the close-up's target)
    static OrbitCamera preset(CameraPreset p, int exitIndex = 2, float scale = 1.0f, float exitDepth = -1.0f);
};

} // namespace swarm::viewer
