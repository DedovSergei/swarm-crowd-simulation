# Calibration grid `calibration_5.3b_refine100`

commit `1e185832cf10623f40dc8f6241fc712cd9fa0069`, dirty 1, Release; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; 2026-10-04T22:24:32.

Corridor 3 x 50 m, warm-up 300 s, measured 300 s per density (seeds 7,8,9); projection iterations 32. Objective: RMS of the model's speed minus Weidmann's over rho in [0.5, 4] (target <= 0.15 m/s). Hard constraints (feasible): the N = 4096 terrace evacuation completes and passes every plausibility check (tools/plausibility.hpp, the limits of test_gpu section 31); its t100 changes by at most 5% from DT to DT/2; the maximum flow is within +-25% of Weidmann's 73.5 p/(m min) (at rho 1.751). Fruin ~82 p/(m min). Raw rows: grid.csv.

| K_SEP | relax | T [s] | RMS [m/s] | v(0.1) | v(0.5) | v(1) | v(1.5) | v(2) | v(2.5) | v(3) | v(3.5) | v(4) | v(5) | v(6) | max J [p/(m min)] at rho | evac step (s) | t100 / t50 / t90 DT -> DT/2 | overlap p50 / p99 / max | peak density | misses |
|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---|---|---|---|---:|---|
| 100.00 | 1.00 | 0.28 | 0.1274 | 1.340 | 1.340 | 1.340 | 0.940 | 0.581 | 0.404 | 0.322 | 0.113 | 0.042 | -0.000 | 0.000 | 84.6 at 1.5 | 2620 (458.3) | +0.00% / -0.87% / -0.02% | 0.0013 / 0.0659 / 0.3867 | 6.85 | overlap |
| 100.00 | 1.00 | 0.33 | 0.1270 **(compromise)** | 1.340 | 1.340 | 1.340 | 0.805 | 0.503 | 0.333 | 0.265 | 0.185 | 0.028 | -0.000 | 0.000 | 80.4 at 1.0 | 2790 (488.0) | +0.88% / +1.69% / +1.51% | 0.0013 / 0.0711 / 0.3906 | 6.77 | overlap |

**No row meets every constraint.** Best compromise (plausible first, then the fewest missed criteria, then RMS): K_SEP 100, PROJ_RELAX 1, T_HEADWAY 0.325 s: RMS 0.127048 m/s, max flow 80.4 p/(m min), t100 DT -> DT/2 0.878136%; misses: overlap.
