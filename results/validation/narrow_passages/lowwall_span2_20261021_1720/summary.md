# Stair harness `lowwall_span2`

commit `ea80c1f9b6a86467e339c0e00f43701a12bf3f20`, dirty 0, Release; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; 2026-10-21T17:20:47.

Inclined periodic corridor (tools/fd/fd_harness.cpp `stair`, physics.comp FD_INCLINE): the agents' centres span 2 m (walls 2.4 m apart), period 50 m with a screw boundary, rake 0.5 (26.57 deg); goal +x: up = ascending, down = descending, level = rake 0. Warm-up 300 s, measured 300 s (DT 0.1749 s), seeds 7,8,9 (means; overlap: max). Model: the venues' incline speed (stair speeds 0.58 / 0.655 m/s), stair spacing (empirical: T_stair up 0.625 s, down 0.65 s; T_HEADWAY 0.3 s on the level). Density per m^2 of plan area of the clear width; J = specific flow per metre of the clear width (the ring's mean flow).

| dir | rho [p/m^2] | agents | v [m/s] | v halves [m/s] | J [p/(m s)] | J [p/(m min)] | area density | mean gap [m] | max overlap |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|
| level | 0.50 | 50 | 1.340 | 1.342 / 1.338 | 0.670 | 40.2 | 0.50 | 2.943 | 0.000 |
| level | 1.00 | 100 | 1.340 | 1.342 / 1.338 | 1.340 | 80.4 | 1.00 | 1.488 | 0.000 |
| level | 1.25 | 125 | 1.340 | 1.342 / 1.338 | 1.675 | 100.5 | 1.25 | 1.226 | 0.000 |
| level | 1.50 | 150 | 1.340 | 1.342 / 1.338 | 2.010 | 120.6 | 1.50 | 1.010 | 0.000 |
| level | 1.60 | 160 | 1.340 | 1.342 / 1.338 | 2.144 | 128.6 | 1.60 | 0.938 | 0.000 |
| level | 1.70 | 170 | 1.333 | 1.327 / 1.338 | 2.266 | 135.9 | 1.70 | 0.837 | 0.000 |
| level | 1.80 | 180 | 1.168 | 1.167 / 1.168 | 2.102 | 126.1 | 1.79 | 0.799 | 0.000 |
| level | 1.90 | 190 | 1.066 | 1.066 / 1.065 | 2.025 | 121.5 | 1.90 | 0.769 | 0.000 |
| level | 2.00 | 200 | 0.987 | 0.987 / 0.987 | 1.974 | 118.4 | 2.00 | 0.737 | 0.000 |
| level | 2.05 | 205 | 0.944 | 0.946 / 0.943 | 1.936 | 116.2 | 2.05 | 0.724 | 0.000 |
| level | 2.10 | 210 | 0.924 | 0.926 / 0.923 | 1.941 | 116.5 | 2.10 | 0.722 | 0.000 |
| level | 2.15 | 215 | 0.906 | 0.905 / 0.906 | 1.947 | 116.8 | 2.14 | 0.719 | 0.000 |
| level | 2.20 | 220 | 0.868 | 0.868 / 0.868 | 1.909 | 114.5 | 2.18 | 0.706 | 0.000 |
| level | 2.25 | 225 | 0.839 | 0.838 / 0.839 | 1.887 | 113.2 | 2.23 | 0.694 | 0.000 |
| level | 2.30 | 230 | 0.813 | 0.814 / 0.813 | 1.871 | 112.2 | 2.28 | 0.682 | 0.000 |
| level | 2.40 | 240 | 0.778 | 0.781 / 0.775 | 1.867 | 112.0 | 2.35 | 0.666 | 0.000 |
| level | 2.50 | 250 | 0.754 | 0.755 / 0.753 | 1.884 | 113.0 | 2.49 | 0.661 | 0.000 |
| level | 2.75 | 275 | 0.619 | 0.620 / 0.617 | 1.701 | 102.1 | 2.76 | 0.611 | 0.000 |
| level | 3.00 | 300 | 0.572 | 0.574 / 0.571 | 1.717 | 103.0 | 3.03 | 0.592 | 0.000 |
| level | 3.25 | 325 | 0.514 | 0.515 / 0.514 | 1.672 | 100.3 | 3.25 | 0.571 | 0.000 |
| level | 3.50 | 350 | 0.484 | 0.486 / 0.483 | 1.695 | 101.7 | 3.49 | 0.558 | 0.000 |
| level | 3.75 | 375 | 0.424 | 0.425 / 0.423 | 1.590 | 95.4 | 3.77 | 0.536 | 0.000 |
| level | 4.00 | 400 | 0.400 | 0.400 / 0.400 | 1.600 | 96.0 | 4.00 | 0.526 | 0.000 |
| level | 4.50 | 450 | 0.359 | 0.360 / 0.359 | 1.616 | 97.0 | 4.50 | 0.510 | 0.000 |
| level | 5.00 | 500 | 0.319 | 0.320 / 0.317 | 1.593 | 95.6 | 5.01 | 0.498 | 0.000 |

| dir | max J [p/(m s)] | [p/(m min)] | at rho | EMPIRICAL target | J / EMPIRICAL | CONSERVATIVE target | J / CONSERVATIVE |
|---|---:|---:|---:|---:|---:|---:|---:|
| level | 2.266 | 135.9 | 1.70 | - | - | - | - |

Targets (results/task_5.9.md stage 1; verify against the cited sources): EMPIRICAL = Burghardt, Seyfried & Klingsch (2013), maximum specific flows 1.22 (up) / 1.25 (down) persons/(m s); CONSERVATIVE = the Green Guide (6th ed., 2018), 66 persons/(m min) on stepped surfaces.
