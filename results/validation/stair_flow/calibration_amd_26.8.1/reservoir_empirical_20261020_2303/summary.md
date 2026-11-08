# Stair harness, reservoir mode `reservoir_empirical`

commit `ba86b3ae21b252be1c83e995381b467da49ad033`, dirty 1, Release; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; 2026-10-20T23:04:14.

A gangway fed from a reservoir (tools/fd/fd_harness.cpp `stair --mode reservoir`, physics.comp FD_INCLINE without FD_PERIODIC_X): the incline z = rake x, rake 0.5 (26.57 deg), walls 1.6 m apart (the agents' centres span 1.2 m, the gangway's clear width); a queue of agents at rest, uniform at density rho0 over the 28 m below x = 0, all driven +x (up: ascending, down: the incline reversed, descending, level: rake 0). Specific flow J = crossings of a line in its steady window (the 10-th to the 80-th percentile of the agents' crossing times) / (window x clear width); lines at 0, 5 and 10 m. Seeds 7,8,9,10,11 (means; the 5 m line's range over the seeds). Model: the venues' incline speed (stair speeds 0.58 / 0.655 m/s), stair spacing (empirical: T_stair up 0.625 s, down 0.65 s; T_HEADWAY 0.3 s on the level). The local diagram (local_fd.csv): the measurement area x in [2.5, 7.5] m in 10 s windows.

| dir | rho0 [p/m^2] | agents | J at 0 m | J at 5 m [p/(m s)] | J at 10 m | J at 5 m [p/(m min)] | 5 m, seeds | window [s] | max overlap |
|---|---:|---:|---:|---:|---:|---:|---|---|---:|
| up | 1.00 | 34 | 0.567 | 0.567 | 0.566 | 34.0 | 0.525-0.611 | 15-50 | 0.000 |
| up | 2.00 | 67 | 1.126 | 1.128 | 1.127 | 67.7 | 1.037-1.204 | 15-50 | 0.000 |
| up | 3.00 | 101 | 1.308 | 1.307 | 1.308 | 78.4 | 1.249-1.378 | 15-60 | 0.000 |
| up | 4.00 | 134 | 1.500 | 1.500 | 1.499 | 90.0 | 1.431-1.544 | 16-69 | 0.000 |
| up | 5.00 | 168 | 1.661 | 1.661 | 1.662 | 99.7 | 1.620-1.709 | 18-77 | 0.000 |
| up | 5.50 | 185 | 1.723 | 1.723 | 1.724 | 103.4 | 1.684-1.781 | 18-81 | 0.000 |
| up | 6.00 | 202 | 1.744 | 1.746 | 1.745 | 104.8 | 1.705-1.768 | 19-87 | 0.000 |
| down | 1.00 | 34 | 0.642 | 0.641 | 0.641 | 38.5 | 0.592-0.693 | 13-44 | 0.000 |
| down | 2.00 | 67 | 1.217 | 1.218 | 1.218 | 73.1 | 1.179-1.287 | 13-46 | 0.000 |
| down | 3.00 | 101 | 1.351 | 1.350 | 1.350 | 81.0 | 1.288-1.419 | 14-57 | 0.000 |
| down | 4.00 | 134 | 1.553 | 1.554 | 1.553 | 93.2 | 1.488-1.599 | 15-66 | 0.000 |
| down | 5.00 | 168 | 1.717 | 1.718 | 1.717 | 103.1 | 1.678-1.774 | 16-74 | 0.000 |
| down | 5.50 | 185 | 1.789 | 1.789 | 1.788 | 107.3 | 1.741-1.857 | 17-77 | 0.000 |
| down | 6.00 | 202 | 1.801 | 1.800 | 1.803 | 108.0 | 1.763-1.830 | 18-83 | 0.000 |

The maximum sustained flow (the capacity): the largest J at the 5 m line over rho0.

| dir | capacity [p/(m s)] | [p/(m min)] | at rho0 | EMPIRICAL target | J / EMPIRICAL | CONSERVATIVE target | J / CONSERVATIVE |
|---|---:|---:|---:|---:|---:|---:|---:|
| up | 1.746 | 104.8 | 6.00 | 1.22 | 1.431 | 1.10 | 1.587 |
| down | 1.800 | 108.0 | 6.00 | 1.25 | 1.440 | 1.10 | 1.637 |

Targets (results/task_5.9.md stage 1; verify against the cited sources): EMPIRICAL = Burghardt, Seyfried & Klingsch (2013), maximum specific flows 1.22 (up) / 1.25 (down) persons/(m s); CONSERVATIVE = the Green Guide (6th ed., 2018), 66 persons/(m min) on stepped surfaces.
