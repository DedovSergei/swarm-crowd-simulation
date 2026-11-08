# The exit choice's GPU cost (Task 5.6)

nav_probe choice-timing | commit c94a60cf0c2213aa8c69fb77a3f7f58122042999 (dirty 0) | Release | 2026-10-10 19:33 | AMD  Radeon RX 7800 XT

The choice pass (physics.comp PHYSICS_PASS 0: evaluate, thresholds, apply) alone (CrowdSim::stepExitChoice, agents at rest), GPU timestamps around it, venue S, N = 4096 buffers (3728 agents at spawn), the default model (queue-aware, incline speed); median of 15 repetitions of 40 evaluation intervals (17 steps each); the whole step of the default model for scale (GPU timestamps, mean of 34 steps, median of the repetitions). No other GPU work was started beside it; the gpuwatch quiet-GPU check was not run for this measurement.

| state | active | choice pass, between evaluations [ms] | choice pass, an evaluation step [ms] | mean per step [ms] | whole step [ms] | share |
|---|---:|---:|---:|---:|---:|---:|
| spawn | 3728 | 0.0083 (spread 0.0001) | 0.0368 (spread 0.0011) | 0.0100 | 0.756 | 1.3% |
| after 250 steps | 2978 | 0.0122 (spread 0.0001) | 0.0441 (spread 0.0009) | 0.0140 | 1.035 | 1.4% |
