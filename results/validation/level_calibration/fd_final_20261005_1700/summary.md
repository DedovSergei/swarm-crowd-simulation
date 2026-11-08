# Fundamental diagram `fd_5.3b_final`

commit `df51e50f47006ce148f3b972b7b0e7520d4f1a57`, dirty 1, Release; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; 2026-10-05T17:00:00.

Corridor 3 m x 50 m, periodic in x, goal +x; warm-up 300 s, measured 300 s (DT 0.174907 s), seeds 7,8,9 (mean over seeds); measurement area |x| <= 5 m, wall to wall. K_SEP 100, PROJ_RELAX 1, T_HEADWAY 0.3 s, projection iterations 32.

| rho [p/m^2] | agents | v [m/s] | v halves [m/s] | area density | J [p/(m s)] | J [p/(m min)] | Weidmann v | Weidmann J [p/(m min)] | max overlap |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|
| 0.100 | 15 | 1.340 | 1.340 / 1.340 | 0.100 | 0.134 | 8.0 | 1.340 | 8.0 | 0.000 |
| 0.500 | 75 | 1.340 | 1.340 / 1.340 | 0.500 | 0.670 | 40.2 | 1.298 | 39.0 | 0.000 |
| 1.000 | 150 | 1.340 | 1.340 / 1.340 | 1.000 | 1.340 | 80.4 | 1.058 | 63.5 | 0.000 |
| 1.500 | 225 | 0.867 | 0.832 / 0.904 | 1.501 | 1.300 | 78.0 | 0.807 | 72.6 | 0.000 |
| 2.000 | 300 | 0.558 | 0.560 / 0.557 | 1.998 | 1.117 | 67.0 | 0.606 | 72.7 | 0.000 |
| 2.500 | 375 | 0.368 | 0.365 / 0.370 | 2.499 | 0.919 | 55.2 | 0.452 | 67.7 | 0.000 |
| 3.000 | 450 | 0.292 | 0.292 / 0.292 | 3.000 | 0.875 | 52.5 | 0.331 | 59.5 | 0.000 |
| 3.500 | 525 | 0.110 | 0.105 / 0.116 | 3.404 | 0.386 | 23.2 | 0.234 | 49.2 | 0.005 |
| 4.000 | 600 | 0.033 | 0.037 / 0.029 | 3.994 | 0.131 | 7.9 | 0.156 | 37.5 | 0.006 |
| 5.000 | 750 | -0.000 | -0.000 / 0.000 | 5.031 | -0.000 | -0.0 | 0.037 | 11.2 | 0.014 |
| 6.000 | 900 | 0.000 | 0.000 / 0.000 | 6.057 | 0.000 | 0.0 | 0.000 | 0.0 | 0.042 |

RMS speed error vs Weidmann over rho in [0.5, 4] (8 points): **0.1257 m/s**. Max flow: model **80.4 p/(m min)** at rho 1; Weidmann 73.5 p/(m min) at rho 1.751; Fruin ~82 p/(m min).

Weidmann (1993): v(rho) = 1.34 (1 - exp(-1.913 (1/rho - 1/5.4))) m/s (verify against the cited source).
