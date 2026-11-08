#pragma once

// Golden state: the pinned hashes of test_gpu parity.golden_terrace and the venues' checks, shared with benchmark_crowd's self-check
// and the CPU tuning tool (tools/benchmark), which must reproduce them before they measure anything.

#include <cstddef>
#include <cstdint>
#include <iterator>
#include <vector>

#include <swarm/gpu_types.hpp>

namespace swarm::golden {

// 64-bit FNV-1a of the raw agent state bytes after GOLDEN_STEPS steps from spawnBleacherCrowd(n).
// A change that alters any of these must be intentional, explained in its commit message and re-pinned here after
// re-running the checks that name them. GPU results are only reproducible bit for bit on the same driver. GOLDEN_STEPS is 250 so
// that no golden state is close to a full evacuation (test_gpu parity.golden_terrace checks that agents remain active).
constexpr int GOLDEN_STEPS = 250;
// The reference evacuation of the golden spawn (GPU, N = 4096): the step at which every agent has left (test_gpu
// engine.pipeline_invariants measures it; SWARM --selftest-ui checks that its completion behaviour fires there).
constexpr int REFERENCE_EVACUATION_STEP = 2712;
// Venue S routed: the step at which every one of the 3728 agents of the full seat spawn has left (GPU, default model; test_gpu
// validation.s_evacuation and run_experiment measure it; SWARM --selftest-ui viewer.venue_s checks its completion there): 238.2 s
// (results/evacuation/matrix).
constexpr int REFERENCE_EVACUATION_STEP_S = 1362;
// The same with the nearest exit and the level speed: 201.7 s (run_experiment --exit-choice nearest --incline-speed 0).
constexpr int REFERENCE_EVACUATION_STEP_S_NEAREST = 1153;
// The driver every GPU pin below belongs to (GL_RENDERER | GL_VERSION). On another driver test_gpu, SWARM --selftest-ui and
// benchmark_crowd warn and compare the CPU pins only.
constexpr char GOLDEN_DRIVER[] = "AMD  Radeon RX 7800 XT | 4.3.0 Core Profile Context 26.10.1.261008";
struct Golden { const char* name; uint64_t hash; };
constexpr Golden GOLDEN[] = {
    { "GPU N = 4096", 0xc78d743496d02748ull },
    { "GPU N = 65536", 0xe4e589d428d02a31ull },
    { "CPU counting N = 4096", 0xf6acc34947d51106ull },
    { "CPU bitonic N = 4096", 0x0fe0246dbd6703feull },
};
constexpr int GOLDEN_COUNT = int(std::size(GOLDEN));
// Venue S, forced (test_gpu parity.s_forced): the state after GOLDEN_STEPS steps of the dense forced scenario (every
// seat occupied, N = 4096, along the row to the nearer gangway, down it and out; tools/venue_s.hpp denseSetup and its drive field,
// physics.comp TEST_DRIVE_TABLE). The drive table bypasses the router, so routing leaves these unchanged: they pin S's contact model.
constexpr Golden GOLDEN_S_FORCED[] = {
    { "GPU venue S dense", 0x08cce2bdb3a7d911ull },
    { "CPU counting venue S dense", 0xa2abaea7c0139b09ull },
    { "CPU bitonic venue S dense", 0x988ff92de7169640ull },
};
// Venue S, routed (test_gpu validation.s_evacuation): the production program with the default model (queue-aware exit choice,
// incline speed, stair spacing EMPIRICAL), e_goal from the navigation field: the state after GOLDEN_STEPS steps of the full seat
// spawn (spawnSeatedCrowd(venueS(), 4096, 1.0, 1337): 3728 agents). Validated with this program: the exit choice's known answers and
// GPU = CPU checks (nav.exit_choice), the incline speed's targets and the stair spacing's function (physics.incline_speed), the
// one-step equivalence and the full evacuations with every per-step check (validation.s_evacuation; results/evacuation/matrix).
constexpr Golden GOLDEN_S[] = {
    { "GPU venue S routed", 0x706f97c4846bc167ull },
    { "CPU counting venue S routed", 0x434356ac8d65471dull },
    { "CPU bitonic venue S routed", 0x5e72f98915ca108full },
};
// The same spawn and steps with ModelOptions{} (nearest exit, level speed): test_gpu validation.s_evacuation checks that the
// model stays selectable.
constexpr Golden GOLDEN_S_NEAREST[] = {
    { "GPU venue S nearest exit, level speed", 0x8c3381ecc5b29b40ull },
    { "CPU counting venue S nearest exit, level speed", 0xb1d6dac42f5dcd09ull },
    { "CPU bitonic venue S nearest exit, level speed", 0x4b591d2bcece4279ull },
};
// The same spawn and steps with ModelOptions{QueueAware, true, StairFlow::Off} (the level spacing on the
// gangway inclines): test_gpu validation.s_evacuation checks that it stays selectable bit for bit
constexpr Golden GOLDEN_S_LEVEL_SPACING[] = {
    { "GPU venue S routed, level spacing", 0xf9df5600c46679d6ull },
    { "CPU counting venue S routed, level spacing", 0x22ad15f59ee18632ull },
    { "CPU bitonic venue S routed, level spacing", 0x94095993d96de587ull },
};
// The generated venues M and L, routed with the default model: the state after
// GOLDEN_STEPS steps of the full seat spawn (spawnSeatedCrowd(venue, N, 1.0, 1337); M 15 832 agents in N = 16384, L 63 424 in N =
// 65536). Checked by venue_probe equiv: grid exact, one step 0 agents beyond 2e-4 with both sorts, CPU thread invariance,
// GPU and CPU determinism (results/validation/venues/M, results/validation/venues/L).
constexpr Golden GOLDEN_M[] = {
    { "GPU venue M routed", 0x0fa616143c51c4c9ull },
    { "CPU counting venue M routed", 0xdfbb0cd26213add2ull },
    { "CPU bitonic venue M routed", 0x06ded25a7094b105ull },
};
constexpr Golden GOLDEN_L[] = {
    { "GPU venue L routed", 0x56ca268d9dfb4bedull },
    { "CPU counting venue L routed", 0x107e45d468070142ull },
    { "CPU bitonic venue L routed", 0xa0ac9c69b02f5ce6ull },
};
// M and L with the level spacing on the inclines: test_gpu venue.generated_m_l (long tier) checks the GPU's state, so the
// model stays selectable bit for bit
constexpr Golden GOLDEN_M_LEVEL_SPACING[] = {
    { "GPU venue M routed, level spacing", 0x96d54e95d2e05a40ull },
    { "CPU counting venue M routed, level spacing", 0xc7d9dce76083ce21ull },
    { "CPU bitonic venue M routed, level spacing", 0x518d0c2aa349a17cull },
};
constexpr Golden GOLDEN_L_LEVEL_SPACING[] = {
    { "GPU venue L routed, level spacing", 0x259b7f6b211ade72ull },
    { "CPU counting venue L routed, level spacing", 0x45a6ee6803ca22eeull },
    { "CPU bitonic venue L routed, level spacing", 0x4b52c37b362a96f3ull },
};
// The GPU pins and reference evacuation steps of AMD 26.8.1.260810, the driver of results/evacuation/history_amd_26.8.1 (the same
// programs; a driver changes GPU results bit for bit like a different rounding). Not compared by any check; the CPU pins are driver-independent.
namespace driver_26_8_1 {
constexpr char DRIVER[] = "AMD  Radeon RX 7800 XT | 4.3.0 Core Profile Context 26.8.1.260810";
constexpr Golden GPU[] = {
    { "GPU N = 4096", 0x82f434e117f245d6ull },
    { "GPU N = 65536", 0x83ab9101857d00aaull },
    { "GPU venue S dense", 0x27f4f0e74ebb6b72ull },
    { "GPU venue S routed", 0x892b235e7f021644ull },
    { "GPU venue S nearest exit, level speed", 0x6305dcc7a430279eull },
    { "GPU venue S routed, level spacing", 0x840e648e51c78ad7ull },
    { "GPU venue M routed", 0xf01cbab87d50bce0ull },
    { "GPU venue L routed", 0x16ead091df60d13bull },
    { "GPU venue M routed, level spacing", 0xc3682e4998ef9673ull },
    { "GPU venue L routed, level spacing", 0x31d01dac1780ffc1ull },
};
constexpr int REFERENCE_EVACUATION_STEP = 2704;
constexpr int REFERENCE_EVACUATION_STEP_S = 1351;
constexpr int REFERENCE_EVACUATION_STEP_S_NEAREST = 1150;
} // namespace driver_26_8_1

enum GoldenIndex { GOLDEN_GPU_4096, GOLDEN_GPU_65536, GOLDEN_CPU_COUNTING_4096, GOLDEN_CPU_BITONIC_4096 };

inline uint64_t stateHash(const std::vector<GpuBoid>& state) {
    uint64_t h = 0xcbf29ce484222325ull;
    const unsigned char* b = reinterpret_cast<const unsigned char*>(state.data());
    for (size_t i = 0; i < state.size() * sizeof(GpuBoid); ++i) { h ^= b[i]; h *= 0x100000001b3ull; }
    return h;
}

} // namespace swarm::golden
