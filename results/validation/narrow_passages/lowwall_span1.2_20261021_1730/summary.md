# Stair harness `lowwall_span1.2`

commit `ea80c1f9b6a86467e339c0e00f43701a12bf3f20`, dirty 0, Release; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; 2026-10-21T17:30:57.

Inclined periodic corridor (tools/fd/fd_harness.cpp `stair`, physics.comp FD_INCLINE): the agents' centres span 1.2 m (walls 1.6 m apart), period 50 m with a screw boundary, rake 0.5 (26.57 deg); goal +x: up = ascending, down = descending, level = rake 0. Warm-up 300 s, measured 300 s (DT 0.1749 s), seeds 7,8,9 (means; overlap: max). Model: the venues' incline speed (stair speeds 0.58 / 0.655 m/s), stair spacing (empirical: T_stair up 0.625 s, down 0.65 s; T_HEADWAY 0.3 s on the level). Density per m^2 of plan area of the clear width; J = specific flow per metre of the clear width (the ring's mean flow).

| dir | rho [p/m^2] | agents | v [m/s] | v halves [m/s] | J [p/(m s)] | J [p/(m min)] | area density | mean gap [m] | max overlap |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|
| level | 0.50 | 30 | 1.340 | 1.342 / 1.338 | 0.670 | 40.2 | 0.50 | 3.620 | 0.000 |
| level | 1.00 | 60 | 1.340 | 1.342 / 1.338 | 1.340 | 80.4 | 1.00 | 1.583 | 0.000 |
| level | 1.25 | 75 | 1.340 | 1.342 / 1.338 | 1.675 | 100.5 | 1.25 | 1.270 | 0.000 |
| level | 1.50 | 90 | 1.340 | 1.342 / 1.338 | 2.010 | 120.6 | 1.50 | 1.127 | 0.000 |
| level | 1.60 | 96 | 1.340 | 1.342 / 1.338 | 2.144 | 128.6 | 1.60 | 1.049 | 0.000 |
| level | 1.70 | 102 | 1.340 | 1.342 / 1.338 | 2.278 | 136.7 | 1.70 | 1.006 | 0.000 |
| level | 1.80 | 108 | 1.340 | 1.342 / 1.338 | 2.412 | 144.7 | 1.80 | 0.932 | 0.000 |
| level | 1.90 | 114 | 1.275 | 1.276 / 1.274 | 2.423 | 145.4 | 1.90 | 0.833 | 0.000 |
| level | 2.00 | 120 | 1.263 | 1.263 / 1.264 | 2.527 | 151.6 | 2.00 | 0.826 | 0.000 |
| level | 2.05 | 123 | 1.239 | 1.240 / 1.238 | 2.539 | 152.4 | 2.06 | 0.814 | 0.000 |
| level | 2.10 | 126 | 1.138 | 1.140 / 1.137 | 2.391 | 143.4 | 2.10 | 0.793 | 0.000 |
| level | 2.15 | 129 | 1.075 | 1.076 / 1.075 | 2.312 | 138.7 | 2.15 | 0.774 | 0.000 |
| level | 2.20 | 132 | 1.049 | 1.050 / 1.048 | 2.308 | 138.5 | 2.20 | 0.764 | 0.000 |
| level | 2.25 | 135 | 1.000 | 1.001 / 0.999 | 2.250 | 135.0 | 2.23 | 0.756 | 0.000 |
| level | 2.30 | 138 | 0.972 | 0.973 / 0.971 | 2.235 | 134.1 | 2.29 | 0.743 | 0.000 |
| level | 2.40 | 144 | 0.939 | 0.940 / 0.938 | 2.254 | 135.2 | 2.41 | 0.728 | 0.000 |
| level | 2.50 | 150 | 0.901 | 0.903 / 0.900 | 2.254 | 135.2 | 2.53 | 0.715 | 0.000 |
| level | 2.75 | 165 | 0.786 | 0.787 / 0.785 | 2.161 | 129.7 | 2.74 | 0.671 | 0.000 |
| level | 3.00 | 180 | 0.678 | 0.677 / 0.678 | 2.033 | 122.0 | 2.95 | 0.635 | 0.000 |
| level | 3.25 | 195 | 0.621 | 0.620 / 0.621 | 2.017 | 121.0 | 3.22 | 0.611 | 0.000 |
| level | 3.50 | 210 | 0.563 | 0.564 / 0.562 | 1.971 | 118.2 | 3.51 | 0.589 | 0.000 |
| level | 3.75 | 225 | 0.508 | 0.508 / 0.507 | 1.903 | 114.2 | 3.74 | 0.568 | 0.000 |
| level | 4.00 | 240 | 0.469 | 0.470 / 0.468 | 1.876 | 112.6 | 4.00 | 0.553 | 0.000 |
| level | 4.50 | 270 | 0.410 | 0.410 / 0.410 | 1.845 | 110.7 | 4.51 | 0.530 | 0.000 |
| level | 5.00 | 300 | 0.349 | 0.350 / 0.349 | 1.746 | 104.8 | 5.01 | 0.506 | 0.000 |

| dir | max J [p/(m s)] | [p/(m min)] | at rho | EMPIRICAL target | J / EMPIRICAL | CONSERVATIVE target | J / CONSERVATIVE |
|---|---:|---:|---:|---:|---:|---:|---:|
| level | 2.539 | 152.4 | 2.05 | - | - | - | - |

Targets (results/task_5.9.md stage 1; verify against the cited sources): EMPIRICAL = Burghardt, Seyfried & Klingsch (2013), maximum specific flows 1.22 (up) / 1.25 (down) persons/(m s); CONSERVATIVE = the Green Guide (6th ed., 2018), 66 persons/(m min) on stepped surfaces.
