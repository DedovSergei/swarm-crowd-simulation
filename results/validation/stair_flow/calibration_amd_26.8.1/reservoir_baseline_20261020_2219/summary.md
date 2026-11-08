# Stair harness, reservoir mode `reservoir_baseline`

commit `b63ea545ea2d9abd446c890a4266c4b736cff364`, dirty 0, Release; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; 2026-10-20T22:19:53.

A gangway fed from a reservoir (tools/fd/fd_harness.cpp `stair --mode reservoir`, physics.comp FD_INCLINE without FD_PERIODIC_X): the incline z = rake x, rake 0.5 (26.57 deg), walls 1.6 m apart (the agents' centres span 1.2 m, the gangway's clear width); a queue of agents at rest, uniform at density rho0 over the 28 m below x = 0, all driven +x (up: ascending, down: the incline reversed, descending, level: rake 0). Specific flow J = crossings of a line in its steady window (the 10-th to the 80-th percentile of the agents' crossing times) / (window x clear width); lines at 0, 5 and 10 m. Seeds 7,8,9,10,11 (means; the 5 m line's range over the seeds). Model: the venues' incline speed (stair speeds 0.58 / 0.655 m/s), level spacing (T_HEADWAY 0.3 s). The local diagram (local_fd.csv): the measurement area x in [2.5, 7.5] m in 10 s windows.

| dir | rho0 [p/m^2] | agents | J at 0 m | J at 5 m [p/(m s)] | J at 10 m | J at 5 m [p/(m min)] | 5 m, seeds | window [s] | max overlap |
|---|---:|---:|---:|---:|---:|---:|---|---|---:|
| up | 1.00 | 34 | 0.564 | 0.564 | 0.565 | 33.8 | 0.525-0.605 | 14-50 | 0.000 |
| up | 2.00 | 67 | 1.189 | 1.187 | 1.186 | 71.2 | 1.027-1.317 | 15-48 | 0.000 |
| up | 3.00 | 101 | 1.670 | 1.672 | 1.676 | 100.3 | 1.596-1.719 | 15-49 | 0.000 |
| up | 4.00 | 134 | 2.042 | 2.038 | 2.038 | 122.3 | 1.956-2.143 | 15-53 | 0.000 |
| up | 5.00 | 168 | 2.254 | 2.253 | 2.251 | 135.2 | 2.231-2.285 | 16-59 | 0.000 |
| up | 5.50 | 185 | 2.296 | 2.294 | 2.298 | 137.6 | 2.235-2.337 | 16-63 | 0.000 |
| up | 6.00 | 202 | 2.275 | 2.273 | 2.275 | 136.4 | 2.224-2.309 | 17-69 | 0.000 |
| down | 1.00 | 34 | 0.638 | 0.638 | 0.638 | 38.3 | 0.592-0.685 | 13-44 | 0.000 |
| down | 2.00 | 67 | 1.338 | 1.341 | 1.343 | 80.5 | 1.154-1.493 | 13-43 | 0.000 |
| down | 3.00 | 101 | 1.819 | 1.817 | 1.815 | 109.0 | 1.783-1.832 | 13-45 | 0.000 |
| down | 4.00 | 134 | 2.178 | 2.180 | 2.178 | 130.8 | 2.103-2.285 | 13-49 | 0.000 |
| down | 5.00 | 168 | 2.407 | 2.409 | 2.407 | 144.5 | 2.382-2.423 | 14-55 | 0.000 |
| down | 5.50 | 185 | 2.465 | 2.463 | 2.465 | 147.8 | 2.410-2.529 | 15-59 | 0.000 |
| down | 6.00 | 202 | 2.453 | 2.449 | 2.447 | 146.9 | 2.382-2.516 | 16-64 | 0.000 |
| level | 1.00 | 34 | 1.306 | 1.315 | 1.312 | 78.9 | 1.204-1.412 | 7-22 | 0.000 |
| level | 2.00 | 67 | 2.456 | 2.445 | 2.455 | 146.7 | 2.309-2.634 | 7-23 | 0.000 |
| level | 3.00 | 101 | 2.759 | 2.758 | 2.764 | 165.5 | 2.508-2.875 | 7-29 | 0.000 |
| level | 4.00 | 134 | 3.090 | 3.099 | 3.095 | 185.9 | 2.908-3.269 | 8-33 | 0.000 |
| level | 5.00 | 168 | 3.303 | 3.311 | 3.307 | 198.7 | 3.288-3.327 | 9-38 | 0.000 |
| level | 5.50 | 185 | 3.371 | 3.375 | 3.367 | 202.5 | 3.287-3.512 | 9-41 | 0.000 |
| level | 6.00 | 202 | 3.239 | 3.236 | 3.239 | 194.1 | 3.096-3.342 | 10-46 | 0.000 |

The maximum sustained flow (the capacity): the largest J at the 5 m line over rho0.

| dir | capacity [p/(m s)] | [p/(m min)] | at rho0 | EMPIRICAL target | J / EMPIRICAL | CONSERVATIVE target | J / CONSERVATIVE |
|---|---:|---:|---:|---:|---:|---:|---:|
| up | 2.294 | 137.6 | 5.50 | 1.22 | 1.880 | 1.10 | 2.085 |
| down | 2.463 | 147.8 | 5.50 | 1.25 | 1.971 | 1.10 | 2.239 |
| level | 3.375 | 202.5 | 5.50 | - | - | - | - |

Targets (results/task_5.9.md stage 1; verify against the cited sources): EMPIRICAL = Burghardt, Seyfried & Klingsch (2013), maximum specific flows 1.22 (up) / 1.25 (down) persons/(m s); CONSERVATIVE = the Green Guide (6th ed., 2018), 66 persons/(m min) on stepped surfaces.
