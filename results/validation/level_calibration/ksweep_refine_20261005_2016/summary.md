# Projection iteration sweep `ksweep_5.3c_refine`

commit `ed56a3c442bc2413b8427632b0b59e71ca4f3168`, dirty 1, Release; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; 2026-10-05T20:20:03.

N = 4096 terrace evacuation from spawn per K (production shaders, CrowdSim::setProjectionIterations), every plausibility check of tools/plausibility.hpp after every step; overlap depth / BODY_DIAM over the pair-steps above 0.0001, split into crowd (both agents steadily grounded on walkable floor) and venue-geometry cases (fall: airborne within 5 steps; ramp: floor n_z < 0.8). FD: corridor 3 x 50 m, seeds 7,8,9, warm-up 300 s, measured 300 s; RMS vs Weidmann over rho 1,2,3,4 (and over 0.5-4, the Task 5.3b objective). Reference K = 32. Rule: the smallest K with crowd p99 <= 0.05, crowd max <= 0.2, t100 and FD RMS within 2% of the reference, every other plausibility check passing. Raw: ksweep.csv.

| K | t50 / t90 / t100 [s] | t100 vs ref | overlap all p99 / max | crowd pairs, p99 / max | venue pairs, p99 / max | fall p99 / max | ramp p99 / max | peak tread / aisle / walkway / avenue / exit [p/m^2] | v(0.5) | v(1.0) | v(1.5) | v(2.0) | v(2.5) | v(3.0) | v(3.5) | v(4.0) | RMS (1,2,3,4) | vs ref | RMS (0.5-4) | other checks | meets |
|---:|---|---:|---|---|---|---|---|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---|---|
| 20 | 228.6 / 405.4 / 480.5 | +0.44% | 0.0712 / 0.3933 | 127401, 0.0452 / 0.2388 | 13903, 0.2286 / 0.3933 | 0.2360 / 0.3933 | 0.0277 / 0.0786 | 6.81 / 6.35 / 3.93 / 2.71 / 1.64 | 1.340 | 1.340 | 0.867 | 0.558 | 0.368 | 0.292 | 0.111 | 0.034 | 0.1568 | -0.10% | 0.1255 | pass | no |
| 24 | 227.0 / 404.4 / 472.1 | -1.32% | 0.0676 / 0.3925 | 116071, 0.0401 / 0.3489 | 13235, 0.2293 / 0.3925 | 0.2406 / 0.3925 | 0.0266 / 0.0984 | 6.80 / 6.38 / 4.22 / 3.09 / 1.67 | 1.340 | 1.340 | 0.867 | 0.558 | 0.368 | 0.292 | 0.108 | 0.035 | 0.1566 | -0.24% | 0.1257 | pass | no |
| 28 | 227.7 / 405.3 / 475.2 | -0.66% | 0.0622 / 0.3872 | 140562, 0.0358 / 0.2681 | 13397, 0.2446 / 0.3872 | 0.2551 / 0.3872 | 0.0291 / 0.0859 | 6.84 / 6.37 / 3.93 / 2.81 / 1.65 | 1.340 | 1.340 | 0.867 | 0.558 | 0.368 | 0.292 | 0.106 | 0.034 | 0.1566 | -0.20% | 0.1260 | pass | no |
| 32 **(chosen)** | 226.7 / 403.9 / 478.4 | +0.00% | 0.0650 / 0.3818 | 113139, 0.0350 / 0.1602 | 12588, 0.2471 / 0.3818 | 0.2494 / 0.3818 | 0.0376 / 0.0652 | 6.84 / 6.31 / 4.00 / 2.78 / 1.62 | 1.340 | 1.340 | 0.867 | 0.558 | 0.368 | 0.292 | 0.110 | 0.033 | 0.1569 | +0.00% | 0.1257 | pass | yes |

Chosen: **K = 32** (the smallest K meeting every criterion).
