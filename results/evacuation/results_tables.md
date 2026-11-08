<!-- results_tables.py: MATRIX_DIR results/evacuation/matrix, MATRIX_DIR_BEFORE results/evacuation/matrix_before_calibration, stair results/validation/stair_flow/harness -->

## matrix

| venue | case | agents | t50 [s] | t90 [s] | **t100 [s]** | t100 CONSERVATIVE [s] | t100 / t_lb | doors / avenues | exposure to critical density in circulation areas [person-s] |
|---|---|---:|---:|---:|---:|---:|---:|---|---:|
| terrace | N = 4 096 | 4 096 | 225.3 | 404.0 | **474.3** |  | - | (4 gaps) | 275 005 (all zones) |
| S | 95% | 3 542 | 109.7 (109.0-110.7) | 192.2 (191.2-193.4) | **229.7 (225.5-232.1)** |  | 1.47 (1.44-1.49) | 63 / 37% | 37 786 (37 248-38 476) |
| S | **100%** | 3 728 | 114.9 | 202.0 | **238.2** | **253.6** | **1.45** | 62 / 38% | 41 880 |
| S | 125% | 4 660 | 103.0 (102.5-103.4) | 210.6 (210.2-210.9) | **254.0 (251.3-256.2)** |  | 1.55 (1.53-1.56) | 62 / 38% | 52 102 (50 985-53 767) |
| S | 150% | 5 592 | 119.3 (119.1-119.5) | 233.8 (233.5-234.0) | **291.0 (282.1-296.6)** |  | 1.77 (1.72-1.80) | 61 / 39% | 96 981 (95 773-98 624) |
| S | 150%, standing also on the gangways | 5 592 | 120.2 (119.5-121.0) | 238.3 (237.0-239.1) | **299.1 (295.1-301.4)** |  | 1.82 (1.79-1.83) | 61 / 39% | 80 870 (78 547-83 230) |
| S | 100%, nearest exit | 3 728 | 175.3 | 316.6 | **362.1** |  | 2.20 | 100 / 0% | 124 831 |
| M | 95% | 15 040 | 213.8 (213.0-214.3) | 411.8 (411.4-412.1) | **534.2 (531.5-536.6)** |  | 1.88 (1.87-1.89) | 79 / 21% | 631 643 (617 150-644 037) |
| M | **100%** | 15 832 | 224.6 | 434.6 | **563.4** | **591.0** | **1.88** | 79 / 21% | 711 286 |
| M | 125% and 150% requested = 121.4% (the floor's maximum) | 19 223 | 206.7 (206.4-206.9) | 455.9 (455.3-456.3) | **590.0 (585.8-592.4)** |  | 1.97 (1.96-1.98) | 80 / 20% | 837 879 (831 825-847 103) |
| M | 100%, nearest exit | 15 832 | 306.1 | 697.4 | **857.2** |  | 2.87 | 100 / 0% | 1 218 600 |
| L | 95% | 60 253 | 506.9 (504.8-508.5) | 1 027.1 (1 022.3-1 032.0) | **1 453.9 (1 423.9-1 507.9)** |  | 2.01 (1.97-2.08) | 87 / 13% | 6 515 650 (6 480 340-6 538 090) |
| L | **100%** | 63 424 | 532.4 | 1 082.5 | **1 477.4** | **1 588.5** | **1.94** | 86 / 14% | 7 040 190 |
| L | 125% and 150% requested = 109.3% (the floor's maximum) | 69 311 | 488.0 (483.3-492.4) | 1 088.7 (1 085.0-1 090.9) | **1 523.4 (1 512.1-1 532.0)** |  | 2.00 (1.98-2.01) | 88 / 12% | 7 337 243 (7 294 420-7 380 210) |
| L | 100%, nearest exit | 63 424 | 640.0 | 1 482.2 | **1 958.3** |  | 2.57 | 100 / 0% | 10 449 700 |

## before / after

| venue | case | t100 before [s] | **t100 after [s]** | change | t50 change | exposure to critical density before / after [person-s] |
|---|---|---:|---:|---:|---:|---|
| terrace | N = 4 096 | 474.3 | **474.3** | +0.0% | +0.0% | 275 005 / 275 005 |
| S | 95% | 180.9 (178.9-182.3) | **229.7 (225.5-232.1)** | +26.9% | +26.2% | 24 868 / 37 786 |
| S | 100% | 191.2 | **238.2** | +24.6% | +26.1% | 27 084 / 41 880 |
| S | 125% | 215.5 (214.1-217.1) | **254.0 (251.3-256.2)** | +17.9% | +2.2% | 44 509 / 52 102 |
| S | 150% | 258.3 (251.2-263.4) | **291.0 (282.1-296.6)** | +12.6% | -0.5% | 95 300 / 96 981 |
| S | 150%, standing also on the gangways | 261.8 (261.0-262.4) | **299.1 (295.1-301.4)** | +14.3% | -0.7% | 84 204 / 80 870 |
| S | 100%, nearest exit | 268.1 | **362.1** | +35.0% | +32.5% | 88 653 / 124 831 |
| M | 95% | 434.5 (429.6-442.5) | **534.2 (531.5-536.6)** | +22.9% | +25.2% | 478 170 / 631 643 |
| M | 100% | 461.1 | **563.4** | +22.2% | +26.4% | 512 676 / 711 286 |
| M | 125% and 150% requested = 121.4% (the floor's maximum) (seed 2 before: did not complete; the mean over the others) | 484.8 (483.8-485.7) | **590.0 (585.8-592.4)** | +21.7% | +11.0% | 811 181 / 837 879 |
| M | 100%, nearest exit | 636.1 | **857.2** | +34.8% | +34.1% | 889 583 / 1 218 600 |
| L | 95% | 1 215.6 (1 134.3-1 301.7) | **1 453.9 (1 423.9-1 507.9)** | +19.6% | +28.3% | 5 059 890 / 6 515 650 |
| L | 100% | 1 201.1 | **1 477.4** | +23.0% | +29.9% | 5 222 980 / 7 040 190 |
| L | 125% and 150% requested = 109.3% (the floor's maximum) | 1 237.8 (1 213.3-1 271.2) | **1 523.4 (1 512.1-1 532.0)** | +23.1% | +27.7% | 5 596 893 / 7 337 243 |
| L | 100%, nearest exit | 1 441.1 | **1 958.3** | +35.9% | +35.8% | 7 357 390 / 10 449 700 |

## bottleneck

| venue | (a) exits | (b) gangways | (c) travel | t_lb | t100 | **efficiency t100 / t_lb** (before the calibration) | people per straight gangway: max / mean | t100 if each row segment split its seats between its two end gangways to balance them |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| S | 83 s | **164 s** | 27 s | 164 s | 238.2 s | **1.45** (1.49) | 1.00 | 187.5 s (-21%) |
| M | 203 s | **299 s** | 52 s | 299 s | 563.4 s | **1.88** (1.98) | 1.82 | 457.1 s (-19%) |
| L | 369 s | **763 s** | 103 s | 763 s | 1 477.4 s | **1.94** (2.02) | 1.66 | 1 135.0 s (-23%) |

## flows

| in-situ gangway flow [persons/(m min)] | before the calibration | **EMPIRICAL** |
|---|---:|---:|
| single-outlet straight gangways (M, L), saturated 10 s windows | 94.0 | **71.6** |
| all straight gangways pooled (the gangway bound's flow) | 121.1 | **94.5** |
| corner gangways | 95.8 | **84.0** |
| door capacity J_door (S's doors at 100% before the calibration, where they run at capacity) | | 83.3 |
| doors' mean flow S / M / L | | 63.8 / 43.3 / 23.8 |

## stair harness

| stair harness, maximum sustained specific flow [persons/(m s)] (at rho) | ascending | descending | level (rake 0) |
|---|---:|---:|---:|
| the level spacing (before the calibration): results/validation/stair_flow/harness/stair_baseline_20261022_1946 | 1.902 (4.50) | 1.952 (4.50) | 2.539 (2.05) |
| **EMPIRICAL**: results/validation/stair_flow/harness/stair_empirical_20261022_1956 | 1.220 (2.10) | 1.260 (2.05) | 2.539 (2.05) |
| CONSERVATIVE: results/validation/stair_flow/harness/stair_conservative_20261022_2007 | 1.093 (2.00) | 1.094 (1.70) | 2.539 (2.05) |

## walking-model variants (t100 at 100%)

| venue | level walking, queue-aware | level walking, nearest | incline speed, level spacing (before the calibration) | **stairs (default)** | stairs, nearest |
|---|---:|---:|---:|---:|---:|
| S | 154.8 | 201.7 | 191.2 | **238.2** | 362.1 |
| M | 379.7 | 470.5 | 461.1 | **563.4** | 857.2 |
| L | 988.4 | 1 065.9 | 1 201.1 | **1 477.4** | 1 958.3 |

## facts

- runs 41: every check PASS; seated row changes 0; overlap p99 <= 0.0056, max <= 0.158
- drivers: 4.3.0 Core Profile Context 26.10.1.261008; commits: 49b5a27, b6a7874
- S: 95% spread 2.9%; overcrowded spread 5.0%; CONSERVATIVE / EMPIRICAL 1.065; circulation time >= crush 188 s; peak circulation density 6.45; t99 227.2
- M: 95% spread 0.9%; overcrowded spread 1.1%; CONSERVATIVE / EMPIRICAL 1.049; circulation time >= crush 514 s; peak circulation density 6.81; t99 521.7
- L: 95% spread 5.8%; overcrowded spread 1.3%; CONSERVATIVE / EMPIRICAL 1.075; circulation time >= crush 1349 s; peak circulation density 7.16; t99 1362.9
- longest pause: 8.8 s (L_load95_s1)
- M DT / 2: t100 563.4 -> 555.5 (-1.40%), t50 -0.74%, t90 -0.70%
