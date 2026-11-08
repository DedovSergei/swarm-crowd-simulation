# Stair harness, reservoir mode `reservoir_conservative`

commit `ba86b3ae21b252be1c83e995381b467da49ad033`, dirty 1, Release; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; 2026-10-20T23:04:33.

A gangway fed from a reservoir (tools/fd/fd_harness.cpp `stair --mode reservoir`, physics.comp FD_INCLINE without FD_PERIODIC_X): the incline z = rake x, rake 0.5 (26.57 deg), walls 1.6 m apart (the agents' centres span 1.2 m, the gangway's clear width); a queue of agents at rest, uniform at density rho0 over the 28 m below x = 0, all driven +x (up: ascending, down: the incline reversed, descending, level: rake 0). Specific flow J = crossings of a line in its steady window (the 10-th to the 80-th percentile of the agents' crossing times) / (window x clear width); lines at 0, 5 and 10 m. Seeds 7,8,9,10,11 (means; the 5 m line's range over the seeds). Model: the venues' incline speed (stair speeds 0.58 / 0.655 m/s), stair spacing (conservative: T_stair up 0.75 s, down 0.78 s; T_HEADWAY 0.3 s on the level). The local diagram (local_fd.csv): the measurement area x in [2.5, 7.5] m in 10 s windows.

| dir | rho0 [p/m^2] | agents | J at 0 m | J at 5 m [p/(m s)] | J at 10 m | J at 5 m [p/(m min)] | 5 m, seeds | window [s] | max overlap |
|---|---:|---:|---:|---:|---:|---:|---|---|---:|
| up | 1.00 | 34 | 0.568 | 0.568 | 0.568 | 34.1 | 0.525-0.615 | 15-50 | 0.000 |
| up | 2.00 | 67 | 1.075 | 1.075 | 1.075 | 64.5 | 1.042-1.125 | 15-52 | 0.000 |
| up | 3.00 | 101 | 1.193 | 1.193 | 1.191 | 71.6 | 1.138-1.254 | 16-65 | 0.000 |
| up | 4.00 | 134 | 1.370 | 1.369 | 1.368 | 82.2 | 1.321-1.413 | 17-74 | 0.000 |
| up | 5.00 | 168 | 1.527 | 1.527 | 1.527 | 91.6 | 1.491-1.575 | 18-83 | 0.000 |
| up | 5.50 | 185 | 1.589 | 1.588 | 1.587 | 95.3 | 1.548-1.648 | 19-87 | 0.000 |
| up | 6.00 | 202 | 1.606 | 1.605 | 1.605 | 96.3 | 1.570-1.631 | 20-93 | 0.000 |
| down | 1.00 | 34 | 0.643 | 0.642 | 0.643 | 38.5 | 0.589-0.697 | 13-44 | 0.000 |
| down | 2.00 | 67 | 1.142 | 1.142 | 1.141 | 68.5 | 1.066-1.191 | 14-48 | 0.000 |
| down | 3.00 | 101 | 1.227 | 1.228 | 1.226 | 73.7 | 1.170-1.288 | 15-62 | 0.000 |
| down | 4.00 | 134 | 1.410 | 1.409 | 1.411 | 84.5 | 1.357-1.454 | 16-72 | 0.000 |
| down | 5.00 | 168 | 1.575 | 1.574 | 1.573 | 94.4 | 1.536-1.630 | 17-80 | 0.000 |
| down | 5.50 | 185 | 1.640 | 1.640 | 1.640 | 98.4 | 1.601-1.703 | 18-84 | 0.000 |
| down | 6.00 | 202 | 1.657 | 1.658 | 1.655 | 99.5 | 1.619-1.709 | 19-90 | 0.000 |

The maximum sustained flow (the capacity): the largest J at the 5 m line over rho0.

| dir | capacity [p/(m s)] | [p/(m min)] | at rho0 | EMPIRICAL target | J / EMPIRICAL | CONSERVATIVE target | J / CONSERVATIVE |
|---|---:|---:|---:|---:|---:|---:|---:|
| up | 1.605 | 96.3 | 6.00 | 1.22 | 1.316 | 1.10 | 1.459 |
| down | 1.658 | 99.5 | 6.00 | 1.25 | 1.326 | 1.10 | 1.507 |

Targets (results/task_5.9.md stage 1; verify against the cited sources): EMPIRICAL = Burghardt, Seyfried & Klingsch (2013), maximum specific flows 1.22 (up) / 1.25 (down) persons/(m s); CONSERVATIVE = the Green Guide (6th ed., 2018), 66 persons/(m min) on stepped surfaces.
