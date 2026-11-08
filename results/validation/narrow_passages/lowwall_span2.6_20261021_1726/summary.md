# Stair harness `lowwall_span2.6`

commit `ea80c1f9b6a86467e339c0e00f43701a12bf3f20`, dirty 0, Release; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; 2026-10-21T17:26:45.

Inclined periodic corridor (tools/fd/fd_harness.cpp `stair`, physics.comp FD_INCLINE): the agents' centres span 2.6 m (walls 3 m apart), period 50 m with a screw boundary, rake 0.5 (26.57 deg); goal +x: up = ascending, down = descending, level = rake 0. Warm-up 300 s, measured 300 s (DT 0.1749 s), seeds 7,8,9 (means; overlap: max). Model: the venues' incline speed (stair speeds 0.58 / 0.655 m/s), stair spacing (empirical: T_stair up 0.625 s, down 0.65 s; T_HEADWAY 0.3 s on the level). Density per m^2 of plan area of the clear width; J = specific flow per metre of the clear width (the ring's mean flow).

| dir | rho [p/m^2] | agents | v [m/s] | v halves [m/s] | J [p/(m s)] | J [p/(m min)] | area density | mean gap [m] | max overlap |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|
| level | 0.50 | 65 | 1.340 | 1.342 / 1.338 | 0.670 | 40.2 | 0.50 | 3.059 | 0.000 |
| level | 1.00 | 130 | 1.340 | 1.342 / 1.338 | 1.340 | 80.4 | 1.00 | 1.475 | 0.000 |
| level | 1.25 | 163 | 1.340 | 1.342 / 1.338 | 1.680 | 100.8 | 1.25 | 1.198 | 0.000 |
| level | 1.50 | 195 | 1.340 | 1.342 / 1.338 | 2.010 | 120.6 | 1.50 | 0.913 | 0.000 |
| level | 1.60 | 208 | 1.287 | 1.288 / 1.285 | 2.058 | 123.5 | 1.60 | 0.871 | 0.000 |
| level | 1.70 | 221 | 1.235 | 1.232 / 1.237 | 2.099 | 125.9 | 1.70 | 0.816 | 0.000 |
| level | 1.80 | 234 | 1.028 | 1.030 / 1.027 | 1.851 | 111.1 | 1.80 | 0.766 | 0.000 |
| level | 1.90 | 247 | 0.988 | 0.989 / 0.986 | 1.877 | 112.6 | 1.89 | 0.751 | 0.000 |
| level | 2.00 | 260 | 0.908 | 0.910 / 0.906 | 1.816 | 109.0 | 2.02 | 0.725 | 0.000 |
| level | 2.05 | 267 | 0.867 | 0.866 / 0.869 | 1.782 | 106.9 | 2.04 | 0.707 | 0.000 |
| level | 2.10 | 273 | 0.842 | 0.843 / 0.841 | 1.768 | 106.1 | 2.10 | 0.700 | 0.000 |
| level | 2.15 | 280 | 0.798 | 0.799 / 0.796 | 1.718 | 103.1 | 2.15 | 0.682 | 0.000 |
| level | 2.20 | 286 | 0.782 | 0.783 / 0.782 | 1.721 | 103.3 | 2.19 | 0.674 | 0.000 |
| level | 2.25 | 293 | 0.768 | 0.771 / 0.765 | 1.730 | 103.8 | 2.23 | 0.667 | 0.000 |
| level | 2.30 | 299 | 0.749 | 0.750 / 0.748 | 1.722 | 103.3 | 2.28 | 0.661 | 0.000 |
| level | 2.40 | 312 | 0.699 | 0.700 / 0.698 | 1.677 | 100.6 | 2.40 | 0.641 | 0.000 |
| level | 2.50 | 325 | 0.659 | 0.660 / 0.658 | 1.647 | 98.8 | 2.49 | 0.624 | 0.000 |
| level | 2.75 | 358 | 0.565 | 0.565 / 0.565 | 1.555 | 93.3 | 2.75 | 0.590 | 0.000 |
| level | 3.00 | 390 | 0.512 | 0.514 / 0.511 | 1.537 | 92.2 | 3.01 | 0.570 | 0.000 |
| level | 3.25 | 423 | 0.488 | 0.488 / 0.488 | 1.586 | 95.2 | 3.26 | 0.561 | 0.000 |
| level | 3.50 | 455 | 0.443 | 0.444 / 0.442 | 1.550 | 93.0 | 3.50 | 0.543 | 0.000 |
| level | 3.75 | 488 | 0.405 | 0.405 / 0.405 | 1.520 | 91.2 | 3.75 | 0.528 | 0.000 |
| level | 4.00 | 520 | 0.380 | 0.381 / 0.380 | 1.521 | 91.2 | 3.99 | 0.518 | 0.000 |
| level | 4.50 | 585 | 0.336 | 0.336 / 0.337 | 1.513 | 90.8 | 4.50 | 0.501 | 0.000 |
| level | 5.00 | 650 | 0.277 | 0.279 / 0.275 | 1.386 | 83.2 | 5.01 | 0.487 | 0.000 |

| dir | max J [p/(m s)] | [p/(m min)] | at rho | EMPIRICAL target | J / EMPIRICAL | CONSERVATIVE target | J / CONSERVATIVE |
|---|---:|---:|---:|---:|---:|---:|---:|
| level | 2.099 | 125.9 | 1.70 | - | - | - | - |

Targets (results/task_5.9.md stage 1; verify against the cited sources): EMPIRICAL = Burghardt, Seyfried & Klingsch (2013), maximum specific flows 1.22 (up) / 1.25 (down) persons/(m s); CONSERVATIVE = the Green Guide (6th ed., 2018), 66 persons/(m min) on stepped surfaces.
