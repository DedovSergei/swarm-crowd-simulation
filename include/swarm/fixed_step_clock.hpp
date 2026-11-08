#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>

#include <swarm/sim_params.hpp>

namespace swarm {

// Fixed-timestep simulation clock with render interpolation. Header-only, no GL; unit-tested by
// tools/test_clock.cpp.
//
// The accumulator runs in MODEL time. Each frame's wall-clock delta is clamped to maxFrameTime
// (wall seconds; covers stalls, window drags, minimize/restore), multiplied by playbackRate
// (model time units per wall second) and accumulated; advance() returns how many fixed steps of
// dt to run, at most maxStepsPerFrame. Model time discarded by either clamp goes to droppedTime,
// so between pauses:
//   totalSteps * dt + accumulator + droppedTime == sum(frameDelta * playbackRate)
// (single steps taken while paused add dt to the left side only).
struct FixedStepClock {
    double dt = double(DT);        // model time per step (sim_params DT)
    double maxFrameTime = 0.1;     // wall seconds: clamp for a single frame delta
    int maxStepsPerFrame = 8;      // spiral-of-death cap
    double playbackRate = 1.0;     // model time units per wall-clock second
    double accumulator = 0;        // model time not yet stepped, in [0, dt)
    uint64_t totalSteps = 0;
    double droppedTime = 0;        // model time discarded by either clamp

    bool paused = false;
    double frozenAlpha = 0;        // alpha shown while paused

    // Returns the number of steps to run this frame (0 while paused).
    int advance(double frameDelta) {
        if (paused) return 0;
        const double wall = std::max(frameDelta, 0.0);
        const double clamped = std::min(wall, maxFrameTime);
        droppedTime += (wall - clamped) * playbackRate;
        accumulator += clamped * playbackRate;

        int n = int(std::min(std::floor(accumulator / dt), double(maxStepsPerFrame)));
        n = std::max(n, 0);
        accumulator -= n * dt;
        while (accumulator >= dt && n < maxStepsPerFrame) {  // floor() of a rounded ratio
            accumulator -= dt;
            ++n;
        }
        if (accumulator >= dt) {  // capped: keep the partial step, drop the whole steps
            const double kept = std::fmod(accumulator, dt);
            droppedTime += accumulator - kept;
            accumulator = kept;
        }
        if (accumulator < 0.0) accumulator = 0.0;  // ratio rounded up to an integer (~1e-18)
        totalSteps += uint64_t(n);
        return n;
    }

    // Interpolation factor between the previous and current state, in [0, 1)
    double alpha() const { return accumulator / dt; }

    // Pause semantics: alpha is frozen at its value when paused (no visual snap); after a single
    // step it is 1 (the new state in full) until resume; on resume the accumulator restarts at 0.
    double renderAlpha() const { return paused ? frozenAlpha : alpha(); }
    void pause() {
        if (paused) return;
        paused = true;
        frozenAlpha = alpha();
    }
    void resume() {
        if (!paused) return;
        paused = false;
        accumulator = 0.0;
    }
    // Records a step the caller ran while paused
    void singleStep() {
        ++totalSteps;
        frozenAlpha = 1.0;
    }
};

} // namespace swarm
