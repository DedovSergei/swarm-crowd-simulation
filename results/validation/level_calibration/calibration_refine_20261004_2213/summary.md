# Calibration grid `calibration_5.3b_refine`

commit `1e185832cf10623f40dc8f6241fc712cd9fa0069`, dirty 1, Release; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; 2026-10-04T22:21:42.

Corridor 3 x 50 m, warm-up 300 s, measured 300 s per density (seeds 7,8,9); projection iterations 32. Objective: RMS of the model's speed minus Weidmann's over rho in [0.5, 4] (target <= 0.15 m/s). Hard constraints (feasible): the N = 4096 terrace evacuation completes and passes every plausibility check (tools/plausibility.hpp, the limits of test_gpu section 31); its t100 changes by at most 5% from DT to DT/2; the maximum flow is within +-25% of Weidmann's 73.5 p/(m min) (at rho 1.751). Fruin ~82 p/(m min). Raw rows: grid.csv.

| K_SEP | relax | T [s] | RMS [m/s] | v(0.1) | v(0.5) | v(1) | v(1.5) | v(2) | v(2.5) | v(3) | v(3.5) | v(4) | v(5) | v(6) | max J [p/(m min)] at rho | evac step (s) | t100 / t50 / t90 DT -> DT/2 | overlap p50 / p99 / max | peak density | misses |
|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---|---|---|---|---:|---|
| 60.00 | 1.00 | 0.28 | 0.1380 | 1.340 | 1.340 | 1.340 | 0.936 | 0.573 | 0.400 | 0.306 | 0.066 | 0.010 | 0.000 | 0.000 | 84.2 at 1.5 | 2728 (477.1) | +0.57% / +0.69% / +0.82% | 0.0014 / 0.0721 / 0.3748 | 6.71 | overlap |
| 60.00 | 1.00 | 0.30 | 0.1394 | 1.340 | 1.340 | 1.340 | 0.900 | 0.537 | 0.373 | 0.278 | 0.063 | 0.006 | 0.000 | 0.000 | 81.0 at 1.5 | 2827 (494.5) | +0.90% / +0.89% / +1.32% | 0.0013 / 0.0761 / 0.3912 | 6.64 | overlap |
| 60.00 | 1.00 | 0.33 | 0.1438 | 1.340 | 1.340 | 1.340 | 0.832 | 0.507 | 0.335 | 0.255 | 0.053 | 0.010 | 0.000 | 0.000 | 80.4 at 1.0 | 2896 (506.5) | +1.00% / +0.87% / +0.81% | 0.0013 / 0.0714 / 0.3666 | 6.61 | overlap |
| 80.00 | 1.00 | 0.28 | 0.1297 **(compromise)** | 1.340 | 1.340 | 1.340 | 0.905 | 0.580 | 0.400 | 0.314 | 0.087 | 0.021 | 0.000 | 0.000 | 81.4 at 1.5 | 2662 (465.6) | +0.62% / +0.63% / +1.18% | 0.0013 / 0.0690 / 0.3910 | 6.86 | overlap |
| 80.00 | 1.00 | 0.30 | 0.1339 | 1.340 | 1.340 | 1.340 | 0.870 | 0.559 | 0.363 | 0.284 | 0.075 | 0.013 | 0.000 | -0.000 | 80.4 at 1.0 | 2763 (483.3) | +1.95% / +1.49% / +1.11% | 0.0012 / 0.0662 / 0.4382 | 6.92 | overlap |
| 80.00 | 1.00 | 0.33 | 0.1399 | 1.340 | 1.340 | 1.340 | 0.814 | 0.505 | 0.330 | 0.263 | 0.076 | 0.014 | 0.000 | 0.000 | 80.4 at 1.0 | 2862 (500.6) | -0.40% / +0.99% / +0.84% | 0.0013 / 0.0729 / 0.3915 | 6.87 | overlap |

**No row meets every constraint.** Best compromise (plausible first, then the fewest missed criteria, then RMS): K_SEP 80, PROJ_RELAX 1, T_HEADWAY 0.275 s: RMS 0.129661 m/s, max flow 81.4177 p/(m min), t100 DT -> DT/2 0.619835%; misses: overlap.
