# Stair harness `lowwall_span0.8`

commit `ea80c1f9b6a86467e339c0e00f43701a12bf3f20`, dirty 0, Release; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; 2026-10-21T17:18:18.

Inclined periodic corridor (tools/fd/fd_harness.cpp `stair`, physics.comp FD_INCLINE): the agents' centres span 0.8 m (walls 1.2 m apart), period 50 m with a screw boundary, rake 0.5 (26.57 deg); goal +x: up = ascending, down = descending, level = rake 0. Warm-up 300 s, measured 300 s (DT 0.1749 s), seeds 7,8,9 (means; overlap: max). Model: the venues' incline speed (stair speeds 0.58 / 0.655 m/s), stair spacing (empirical: T_stair up 0.625 s, down 0.65 s; T_HEADWAY 0.3 s on the level). Density per m^2 of plan area of the clear width; J = specific flow per metre of the clear width (the ring's mean flow).

| dir | rho [p/m^2] | agents | v [m/s] | v halves [m/s] | J [p/(m s)] | J [p/(m min)] | area density | mean gap [m] | max overlap |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|
| level | 0.50 | 20 | 1.340 | 1.342 / 1.338 | 0.670 | 40.2 | 0.50 | 3.484 | 0.000 |
| level | 1.00 | 40 | 1.340 | 1.342 / 1.338 | 1.340 | 80.4 | 1.00 | 1.782 | 0.000 |
| level | 1.25 | 50 | 1.340 | 1.342 / 1.338 | 1.675 | 100.5 | 1.25 | 1.439 | 0.000 |
| level | 1.50 | 60 | 1.340 | 1.342 / 1.338 | 2.010 | 120.6 | 1.50 | 1.175 | 0.000 |
| level | 1.60 | 64 | 1.340 | 1.342 / 1.338 | 2.144 | 128.6 | 1.60 | 1.098 | 0.000 |
| level | 1.70 | 68 | 1.340 | 1.342 / 1.338 | 2.278 | 136.7 | 1.70 | 1.052 | 0.000 |
| level | 1.80 | 72 | 1.340 | 1.342 / 1.338 | 2.412 | 144.7 | 1.80 | 1.004 | 0.000 |
| level | 1.90 | 76 | 1.340 | 1.342 / 1.338 | 2.546 | 152.8 | 1.90 | 0.981 | 0.000 |
| level | 2.00 | 80 | 1.340 | 1.342 / 1.338 | 2.680 | 160.8 | 2.00 | 0.946 | 0.000 |
| level | 2.05 | 82 | 1.340 | 1.342 / 1.338 | 2.747 | 164.8 | 2.05 | 0.932 | 0.000 |
| level | 2.10 | 84 | 1.340 | 1.342 / 1.338 | 2.814 | 168.8 | 2.10 | 0.926 | 0.000 |
| level | 2.15 | 86 | 1.340 | 1.342 / 1.338 | 2.881 | 172.9 | 2.15 | 0.881 | 0.000 |
| level | 2.20 | 88 | 1.340 | 1.342 / 1.338 | 2.948 | 176.9 | 2.20 | 0.849 | 0.000 |
| level | 2.25 | 90 | 1.272 | 1.264 / 1.280 | 2.863 | 171.8 | 2.25 | 0.833 | 0.000 |
| level | 2.30 | 92 | 1.253 | 1.245 / 1.261 | 2.881 | 172.9 | 2.32 | 0.825 | 0.000 |
| level | 2.40 | 96 | 1.175 | 1.177 / 1.174 | 2.821 | 169.3 | 2.40 | 0.801 | 0.000 |
| level | 2.50 | 100 | 1.092 | 1.093 / 1.091 | 2.730 | 163.8 | 2.50 | 0.780 | 0.000 |
| level | 2.75 | 110 | 0.918 | 0.919 / 0.916 | 2.523 | 151.4 | 2.73 | 0.720 | 0.000 |
| level | 3.00 | 120 | 0.800 | 0.798 / 0.801 | 2.400 | 144.0 | 3.01 | 0.677 | 0.000 |
| level | 3.25 | 130 | 0.706 | 0.707 / 0.704 | 2.294 | 137.6 | 3.22 | 0.646 | 0.000 |
| level | 3.50 | 140 | 0.642 | 0.643 / 0.641 | 2.247 | 134.8 | 3.50 | 0.621 | 0.000 |
| level | 3.75 | 150 | 0.577 | 0.578 / 0.576 | 2.163 | 129.8 | 3.73 | 0.596 | 0.000 |
| level | 4.00 | 160 | 0.530 | 0.531 / 0.530 | 2.122 | 127.3 | 4.00 | 0.578 | 0.000 |
| level | 4.50 | 180 | 0.457 | 0.457 / 0.456 | 2.056 | 123.3 | 4.49 | 0.549 | 0.000 |
| level | 5.00 | 200 | 0.394 | 0.395 / 0.394 | 1.972 | 118.3 | 5.00 | 0.524 | 0.000 |

| dir | max J [p/(m s)] | [p/(m min)] | at rho | EMPIRICAL target | J / EMPIRICAL | CONSERVATIVE target | J / CONSERVATIVE |
|---|---:|---:|---:|---:|---:|---:|---:|
| level | 2.948 | 176.9 | 2.20 | - | - | - | - |

Targets (results/task_5.9.md stage 1; verify against the cited sources): EMPIRICAL = Burghardt, Seyfried & Klingsch (2013), maximum specific flows 1.22 (up) / 1.25 (down) persons/(m s); CONSERVATIVE = the Green Guide (6th ed., 2018), 66 persons/(m min) on stepped surfaces.
