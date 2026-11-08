// Unit tests for swarm::FixedStepClock (header-only, no GL). Exits non-zero if any check fails.
#include <swarm/build_info.hpp>
#include <swarm/fixed_step_clock.hpp>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <random>
#include <string>
#include <vector>

using swarm::FixedStepClock;

namespace {

int g_failures = 0;

void check(bool ok, const std::string& what) {
    std::printf("  [%s] %s\n", ok ? "PASS" : "FAIL", what.c_str());
    if (!ok) ++g_failures;
}

void section(const char* title) { std::printf("\n== %s\n", title); }

std::string fmt(const char* f, double v) {
    char b[256];
    std::snprintf(b, sizeof(b), f, v);
    return b;
}

// |totalSteps*dt + accumulator + droppedTime - model time fed|
double conservationError(const FixedStepClock& c, double modelIn) {
    return std::abs(double(c.totalSteps) * c.dt + c.accumulator + c.droppedTime - modelIn);
}

// Random frame times: mostly 1/240..1/20 s, some zero-length frames, 1% two-second stalls
std::vector<double> randomFrames(std::mt19937& rng, int count) {
    std::uniform_real_distribution<double> typical(1.0 / 240.0, 1.0 / 20.0), u(0.0, 1.0);
    std::vector<double> f(count);
    for (double& d : f) {
        double r = u(rng);
        d = r < 0.01 ? 2.0 : r < 0.02 ? 0.0 : typical(rng);
    }
    return f;
}

} // namespace

int main() {
    std::printf("test_clock | commit %s (dirty %s) | %s\n", swarm::buildinfo::gitCommit(), swarm::buildinfo::gitDirtyField(),
                swarm::buildinfo::buildConfig());
    const FixedStepClock defaults;
    std::printf("FixedStepClock: dt %.17g (sim_params DT), maxFrameTime %g s, maxStepsPerFrame %d\n",
                defaults.dt, defaults.maxFrameTime, defaults.maxStepsPerFrame);

    section("engine.clock_constant_frames: Constant 1/60, 1/144, 1/30 s frames for 10 s");
    const double expectedSteps = std::floor(10.0 / defaults.dt);
    for (double hz : { 60.0, 144.0, 30.0 }) {
        FixedStepClock c;
        const int frames = int(std::lround(10.0 * hz));
        double minA = 1.0, maxA = 0.0;
        int maxSteps = 0;
        for (int i = 0; i < frames; ++i) {
            maxSteps = std::max(maxSteps, c.advance(1.0 / hz));
            minA = std::min(minA, c.alpha());
            maxA = std::max(maxA, c.alpha());
        }
        std::printf("  %5.0f Hz: %d frames, %llu steps (floor(10/dt) = %.0f), steps/frame <= %d, alpha in [%.6f, %.6f], droppedTime %g\n",
                    hz, frames, (unsigned long long)c.totalSteps, expectedSteps, maxSteps, minA, maxA, c.droppedTime);
        check(std::abs(double(c.totalSteps) - expectedSteps) <= 1.0 && c.droppedTime == 0.0 && minA >= 0.0 && maxA < 1.0,
              fmt("%.0f Hz: step count within +/-1, no dropped time, alpha always in [0, 1)", hz));
    }

    section("engine.clock_conservation: Conservation: totalSteps*dt + accumulator + droppedTime == sum(frameDelta * playbackRate)");
    // rate > 0: fixed playback rate; rate == 0: a random power of two in [1/16, 16] every frame
    // (as [ and ] would change it). Returns the worst absolute error and the model time fed.
    std::mt19937 rng(12345);
    struct Run { double worst = 0.0, modelIn = 0.0, minA = 1.0, maxA = 0.0; FixedStepClock c; };
    auto conserve = [&](double rate, int frames) {
        Run r;
        std::uniform_int_distribution<int> pow2(-4, 4);
        for (double d : randomFrames(rng, frames)) {
            r.c.playbackRate = rate > 0.0 ? rate : std::ldexp(1.0, pow2(rng));
            r.c.advance(d);
            r.modelIn += d * r.c.playbackRate;
            r.worst = std::max(r.worst, conservationError(r.c, r.modelIn));
            r.minA = std::min(r.minA, r.c.alpha());
            r.maxA = std::max(r.maxA, r.c.alpha());
        }
        return r;
    };
    auto rateName = [](double rate) { return rate > 0.0 ? fmt("rate %g", rate) : std::string("rate random/frame"); };
    std::printf("  10000 random frames each (1/240..1/20 s, 1%% zero, 1%% 2 s stalls); absolute bound 1e-9 after every frame\n");
    for (double rate : { 1.0 / 16.0, 1.0, 16.0, 0.0 }) {
        Run r = conserve(rate, 10000);
        std::printf("    %-18s %7llu steps, droppedTime %10.4f, model time fed %10.4f, max |error| %.3e, alpha in [%.6f, %.6f]\n",
                    rateName(rate).c_str(), (unsigned long long)r.c.totalSteps, r.c.droppedTime, r.modelIn, r.worst, r.minA, r.maxA);
        check(r.worst < 1e-9 && r.minA >= 0.0 && r.maxA < 1.0, rateName(rate) + ": conserved to 1e-9 after every frame, alpha in [0, 1)");
    }
    std::printf("  long haul, 100000 frames each: the sums reach ~1e5 model units, where one double ulp is ~1.5e-11,\n"
                "  so the bound is relative: max |error| / model time fed < 1e-13\n");
    for (double rate : { 1.0 / 16.0, 1.0, 16.0, 0.0 }) {
        Run r = conserve(rate, 100000);
        const double rel = r.worst / r.modelIn;
        std::printf("    %-18s %7llu steps, droppedTime %10.4f, model time fed %10.4f, max |error| %.3e (relative %.2e)\n",
                    rateName(rate).c_str(), (unsigned long long)r.c.totalSteps, r.c.droppedTime, r.modelIn, r.worst, rel);
        check(rel < 1e-13 && r.minA >= 0.0 && r.maxA < 1.0, rateName(rate) + ": long-haul conservation within 1e-13 relative, alpha in [0, 1)");
    }
    {
        FixedStepClock c;
        c.playbackRate = 16.0;
        int cappedFrames = 0;
        for (int i = 0; i < 600; ++i) cappedFrames += c.advance(1.0 / 60.0) == c.maxStepsPerFrame;
        const double achieved = double(c.totalSteps) * c.dt / 10.0;
        std::printf("  rate 16 at 60 Hz for 10 s: %d/600 frames capped at %d steps, droppedTime %.4f, achieved rate %.3f vs requested 16\n",
                    cappedFrames, c.maxStepsPerFrame, c.droppedTime, achieved);
        check(cappedFrames == 600 && c.droppedTime > 0.0 && achieved < 16.0, "rate 16 at 60 Hz: every frame capped, time dropped, achieved < requested");
    }

    section("engine.clock_stall: A 2 s stall yields exactly maxStepsPerFrame steps, then the nominal rate");
    {
        FixedStepClock c;
        for (int i = 0; i < 60; ++i) c.advance(1.0 / 60.0);
        const uint64_t before = c.totalSteps;
        const int stallSteps = c.advance(2.0);
        std::printf("  stall: %d steps, droppedTime %.4f (1.9 s over the clamp + capped whole steps)\n", stallSteps, c.droppedTime);
        check(stallSteps == c.maxStepsPerFrame && c.totalSteps == before + uint64_t(stallSteps), "2 s stall -> exactly maxStepsPerFrame steps");
        const double droppedAfterStall = c.droppedTime;
        const uint64_t s0 = c.totalSteps;
        int maxAfter = 0;
        for (int i = 0; i < 60; ++i) maxAfter = std::max(maxAfter, c.advance(1.0 / 60.0));
        const double nominal = 1.0 / c.dt;
        std::printf("  next 1 s at 60 Hz: %llu steps (nominal %.1f), at most %d per frame, no further drops: %s\n",
                    (unsigned long long)(c.totalSteps - s0), nominal, maxAfter, c.droppedTime == droppedAfterStall ? "yes" : "no");
        check(std::abs(double(c.totalSteps - s0) - nominal) <= 1.0 && maxAfter <= 2 && c.droppedTime == droppedAfterStall,
              "recovers to the nominal rate immediately (100 +/- 1 steps in the next second, no cap)");
    }

    section("engine.clock_pause: Pause semantics: frozen alpha, single step shows alpha = 1, resume restarts the accumulator");
    {
        FixedStepClock c;
        for (int i = 0; i < 7; ++i) c.advance(1.0 / 144.0);
        const double alphaAtPause = c.alpha();
        const double accAtPause = c.accumulator;
        const uint64_t stepsAtPause = c.totalSteps;
        c.pause();
        const int whilePaused = c.advance(0.5);
        check(whilePaused == 0 && c.accumulator == accAtPause && c.totalSteps == stepsAtPause,
              "advance() while paused runs no steps and leaves the accumulator alone");
        check(c.renderAlpha() == alphaAtPause, "render alpha frozen at its value when paused (" + fmt("%.6f", alphaAtPause) + ")");
        c.singleStep();
        check(c.totalSteps == stepsAtPause + 1 && c.renderAlpha() == 1.0, "after a single step: one more step, render alpha 1");
        c.singleStep();
        check(c.totalSteps == stepsAtPause + 2 && c.renderAlpha() == 1.0, "render alpha stays 1 until resume");
        c.resume();
        check(!c.paused && c.accumulator == 0.0 && c.renderAlpha() == 0.0, "resume: accumulator restarts at 0");
        check(c.advance(1.0 / 60.0) == 1, "clock runs normally after resume");
    }

    std::printf("\n%s: %d check(s) failed\n", g_failures ? "FAILED" : "ALL PASSED", g_failures);
    return g_failures ? 1 : 0;
}
