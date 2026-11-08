# Experiment `M_load92_s6`

**Task 5.11 stage 1 (gridlock robustness, default model, AMD 26.10.1): venue M, 92% load (seed 6)**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 14565 agents on 92% of the 15832 seats (spawnSeatedCrowd, seed 6), buffer N = 16384, 2952 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 1049458 evaluations, 44125 switches, 0 forced choices).
Capacity: **within design capacity** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `15aa31e8667e4a9417fde7884d907d1832c5e2d6`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-23T18:09:50, 107.8 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1183 | 206.9 |
| t90 | 2289 | 400.4 |
| t100 | 2952 | 516.3 |

t_p: the step by which ceil(p x 14565) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 769 | 0 | 39.5 | 452.0 | 19.8 | 25.5 | 49.1-59.1 |
| -x | 5.66 | 765 | 0 | 39.5 | 453.4 | 19.6 | 25.5 | 49.0-58.9 |
| +y | 5.66 | 758 | 0 | 39.5 | 451.8 | 19.5 | 26.6 | 70.3-80.3 |
| -y | 5.66 | 748 | 0 | 39.7 | 446.7 | 19.5 | 25.5 | 82.7-92.7 |
| door +x+y (y wall) 0 | 1.20 | 564 | 1034 | 4.9 | 470.7 | 60.5 | 80.2 | 25.0-35.0 |
| door +x+y (y wall) 1 | 1.20 | 552 | 622 | 4.9 | 476.6 | 58.5 | 85.3 | 19.2-29.2 |
| door +x+y (y wall) 2 | 1.20 | 281 | 160 | 4.9 | 506.9 | 28.0 | 80.2 | 7.3-17.3 |
| door +x+y (x wall) 0 | 1.20 | 568 | 1050 | 4.9 | 469.4 | 61.1 | 85.3 | 35.0-45.0 |
| door +x+y (x wall) 1 | 1.20 | 561 | 619 | 4.9 | 482.6 | 58.7 | 85.3 | 21.5-31.5 |
| door +x+y (x wall) 2 | 1.20 | 251 | 165 | 4.9 | 512.1 | 24.7 | 85.3 | 8.6-18.5 |
| door +x+y (corner) | 1.20 | 115 | 0 | 49.7 | 516.3 | 12.3 | 75.2 | 403.3-413.3 |
| door -x+y (y wall) 0 | 1.20 | 559 | 1026 | 4.9 | 452.5 | 62.4 | 85.3 | 4.7-14.7 |
| door -x+y (y wall) 1 | 1.20 | 559 | 629 | 4.9 | 491.7 | 57.4 | 85.3 | 9.8-19.8 |
| door -x+y (y wall) 2 | 1.20 | 271 | 170 | 5.2 | 502.7 | 27.2 | 85.3 | 6.1-16.1 |
| door -x+y (x wall) 0 | 1.20 | 563 | 1028 | 4.9 | 475.4 | 59.8 | 90.3 | 25.7-35.7 |
| door -x+y (x wall) 1 | 1.20 | 556 | 627 | 4.9 | 479.8 | 58.5 | 85.3 | 5.6-15.6 |
| door -x+y (x wall) 2 | 1.20 | 258 | 165 | 4.9 | 495.3 | 26.3 | 80.2 | 4.7-14.7 |
| door -x+y (corner) | 1.20 | 118 | 0 | 74.9 | 489.2 | 14.2 | 85.3 | 81.0-91.0 |
| door -x-y (y wall) 0 | 1.20 | 559 | 1027 | 4.9 | 476.6 | 59.2 | 85.3 | 11.4-21.3 |
| door -x-y (y wall) 1 | 1.20 | 560 | 629 | 4.9 | 471.0 | 60.0 | 85.3 | 15.4-25.4 |
| door -x-y (y wall) 2 | 1.20 | 272 | 164 | 4.9 | 491.0 | 28.0 | 80.2 | 4.7-14.7 |
| door -x-y (x wall) 0 | 1.20 | 557 | 1028 | 4.9 | 476.1 | 59.1 | 80.2 | 16.4-26.4 |
| door -x-y (x wall) 1 | 1.20 | 555 | 628 | 4.9 | 476.6 | 58.8 | 85.3 | 9.4-19.4 |
| door -x-y (x wall) 2 | 1.20 | 264 | 162 | 4.9 | 494.3 | 27.0 | 80.2 | 9.6-19.6 |
| door -x-y (corner) | 1.20 | 107 | 0 | 53.3 | 498.7 | 12.0 | 80.2 | 78.7-88.7 |
| door +x-y (y wall) 0 | 1.20 | 561 | 1025 | 4.9 | 470.3 | 60.2 | 90.3 | 13.1-23.1 |
| door +x-y (y wall) 1 | 1.20 | 560 | 619 | 4.9 | 488.2 | 57.9 | 90.3 | 21.3-31.3 |
| door +x-y (y wall) 2 | 1.20 | 262 | 169 | 4.9 | 513.9 | 25.7 | 85.3 | 17.1-27.1 |
| door +x-y (x wall) 0 | 1.20 | 563 | 1037 | 4.9 | 465.4 | 61.1 | 80.2 | 10.0-19.9 |
| door +x-y (x wall) 1 | 1.20 | 557 | 617 | 4.9 | 486.6 | 57.8 | 85.3 | 10.1-20.1 |
| door +x-y (x wall) 2 | 1.20 | 274 | 165 | 4.9 | 512.7 | 27.0 | 80.2 | 9.8-19.8 |
| door +x-y (corner) | 1.20 | 98 | 0 | 68.9 | 493.9 | 11.5 | 85.3 | 296.1-306.1 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 769 | 5.3% | 18.9% |
| -x | avenue | 5.66 | 765 | 5.3% | 18.8% |
| +y | avenue | 5.66 | 758 | 5.2% | 18.6% |
| -y | avenue | 5.66 | 748 | 5.1% | 18.4% |
| door +x+y (y wall) 0 | door | 1.20 | 564 | 3.9% | 65.3% |
| door +x+y (y wall) 1 | door | 1.20 | 552 | 3.8% | 63.9% |
| door +x+y (y wall) 2 | door | 1.20 | 281 | 1.9% | 32.5% |
| door +x+y (x wall) 0 | door | 1.20 | 568 | 3.9% | 65.8% |
| door +x+y (x wall) 1 | door | 1.20 | 561 | 3.9% | 65.0% |
| door +x+y (x wall) 2 | door | 1.20 | 251 | 1.7% | 29.1% |
| door +x+y (corner) | door | 1.20 | 115 | 0.8% | 13.3% |
| door -x+y (y wall) 0 | door | 1.20 | 559 | 3.8% | 64.8% |
| door -x+y (y wall) 1 | door | 1.20 | 559 | 3.8% | 64.8% |
| door -x+y (y wall) 2 | door | 1.20 | 271 | 1.9% | 31.4% |
| door -x+y (x wall) 0 | door | 1.20 | 563 | 3.9% | 65.2% |
| door -x+y (x wall) 1 | door | 1.20 | 556 | 3.8% | 64.4% |
| door -x+y (x wall) 2 | door | 1.20 | 258 | 1.8% | 29.9% |
| door -x+y (corner) | door | 1.20 | 118 | 0.8% | 13.7% |
| door -x-y (y wall) 0 | door | 1.20 | 559 | 3.8% | 64.8% |
| door -x-y (y wall) 1 | door | 1.20 | 560 | 3.8% | 64.9% |
| door -x-y (y wall) 2 | door | 1.20 | 272 | 1.9% | 31.5% |
| door -x-y (x wall) 0 | door | 1.20 | 557 | 3.8% | 64.5% |
| door -x-y (x wall) 1 | door | 1.20 | 555 | 3.8% | 64.3% |
| door -x-y (x wall) 2 | door | 1.20 | 264 | 1.8% | 30.6% |
| door -x-y (corner) | door | 1.20 | 107 | 0.7% | 12.4% |
| door +x-y (y wall) 0 | door | 1.20 | 561 | 3.9% | 65.0% |
| door +x-y (y wall) 1 | door | 1.20 | 560 | 3.8% | 64.9% |
| door +x-y (y wall) 2 | door | 1.20 | 262 | 1.8% | 30.3% |
| door +x-y (x wall) 0 | door | 1.20 | 563 | 3.9% | 65.2% |
| door +x-y (x wall) 1 | door | 1.20 | 557 | 3.8% | 64.5% |
| door +x-y (x wall) 2 | door | 1.20 | 274 | 1.9% | 31.7% |
| door +x-y (corner) | door | 1.20 | 98 | 0.7% | 11.4% |
| **doors (28)** | door | 33.60 | 11525 | 79.1% | |
| **avenues (4)** | avenue | 22.64 | 3040 | 20.9% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 516.3 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 36.0%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 871 | 6.0% | 871 | 6.0% |
| straight +x+y (y wing) 1 | straight | yes | 559 | 3.8% | 553 | 3.8% |
| straight +x+y (y wing) 2 | straight | yes | 280 | 1.9% | 280 | 1.9% |
| straight +x+y (x wing) 0 | straight | yes | 882 | 6.1% | 882 | 6.1% |
| straight +x+y (x wing) 1 | straight | yes | 565 | 3.9% | 561 | 3.9% |
| straight +x+y (x wing) 2 | straight | yes | 251 | 1.7% | 251 | 1.7% |
| corner +x+y | corner | yes | 735 | 5.0% | 252 | 1.7% |
| straight -x+y (y wing) 0 | straight | yes | 876 | 6.0% | 876 | 6.0% |
| straight -x+y (y wing) 1 | straight | yes | 568 | 3.9% | 559 | 3.8% |
| straight -x+y (y wing) 2 | straight | yes | 269 | 1.8% | 269 | 1.8% |
| straight -x+y (x wing) 0 | straight | yes | 874 | 6.0% | 874 | 6.0% |
| straight -x+y (x wing) 1 | straight | yes | 568 | 3.9% | 561 | 3.9% |
| straight -x+y (x wing) 2 | straight | yes | 253 | 1.7% | 253 | 1.7% |
| corner -x+y | corner | yes | 738 | 5.1% | 253 | 1.7% |
| straight -x-y (y wing) 0 | straight | yes | 865 | 5.9% | 865 | 5.9% |
| straight -x-y (y wing) 1 | straight | yes | 564 | 3.9% | 560 | 3.8% |
| straight -x-y (y wing) 2 | straight | yes | 272 | 1.9% | 272 | 1.9% |
| straight -x-y (x wing) 0 | straight | yes | 874 | 6.0% | 874 | 6.0% |
| straight -x-y (x wing) 1 | straight | yes | 564 | 3.9% | 560 | 3.8% |
| straight -x-y (x wing) 2 | straight | yes | 259 | 1.8% | 259 | 1.8% |
| corner -x-y | corner | yes | 739 | 5.1% | 248 | 1.7% |
| straight +x-y (y wing) 0 | straight | yes | 866 | 5.9% | 866 | 5.9% |
| straight +x-y (y wing) 1 | straight | yes | 567 | 3.9% | 561 | 3.9% |
| straight +x-y (y wing) 2 | straight | yes | 261 | 1.8% | 261 | 1.8% |
| straight +x-y (x wing) 0 | straight | yes | 877 | 6.0% | 877 | 6.0% |
| straight +x-y (x wing) 1 | straight | yes | 569 | 3.9% | 565 | 3.9% |
| straight +x-y (x wing) 2 | straight | yes | 266 | 1.8% | 266 | 1.8% |
| corner +x-y | corner | yes | 744 | 5.1% | 236 | 1.6% |
| **straight (24)** | | | 13620 | | 13576 | 93.2% |
| **corner (4)** | | | 2956 | | 989 | 6.8% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 769 | 39.5 | 452.0 | 0.24 | 0.31 | 0.0% |
| -x | 765 | 39.5 | 453.4 | 0.23 | 0.31 | 0.0% |
| +y | 758 | 39.5 | 451.8 | 0.23 | 0.32 | 0.0% |
| -y | 748 | 39.7 | 446.7 | 0.23 | 0.31 | 0.0% |
| door +x+y (y wall) 0 | 564 | 4.9 | 470.7 | 0.72 | 0.96 | 37.5% |
| door +x+y (y wall) 1 | 552 | 4.9 | 476.6 | 0.70 | 1.02 | 33.3% |
| door +x+y (y wall) 2 | 281 | 4.9 | 506.9 | 0.33 | 0.96 | 3.9% |
| door +x+y (x wall) 0 | 568 | 4.9 | 469.4 | 0.73 | 1.02 | 41.7% |
| door +x+y (x wall) 1 | 561 | 4.9 | 482.6 | 0.70 | 1.02 | 30.6% |
| door +x+y (x wall) 2 | 251 | 4.9 | 512.1 | 0.30 | 1.02 | 5.8% |
| door +x+y (corner) | 115 | 49.7 | 516.3 | 0.15 | 0.90 | 0.0% |
| door -x+y (y wall) 0 | 559 | 4.9 | 452.5 | 0.75 | 1.02 | 34.8% |
| door -x+y (y wall) 1 | 559 | 4.9 | 491.7 | 0.69 | 1.02 | 32.0% |
| door -x+y (y wall) 2 | 271 | 5.2 | 502.7 | 0.33 | 1.02 | 5.9% |
| door -x+y (x wall) 0 | 563 | 4.9 | 475.4 | 0.72 | 1.08 | 43.8% |
| door -x+y (x wall) 1 | 556 | 4.9 | 479.8 | 0.70 | 1.02 | 24.5% |
| door -x+y (x wall) 2 | 258 | 4.9 | 495.3 | 0.31 | 0.96 | 2.0% |
| door -x+y (corner) | 118 | 74.9 | 489.2 | 0.17 | 1.02 | 4.7% |
| door -x-y (y wall) 0 | 559 | 4.9 | 476.6 | 0.71 | 1.02 | 29.2% |
| door -x-y (y wall) 1 | 560 | 4.9 | 471.0 | 0.72 | 1.02 | 27.1% |
| door -x-y (y wall) 2 | 272 | 4.9 | 491.0 | 0.33 | 0.96 | 6.0% |
| door -x-y (x wall) 0 | 557 | 4.9 | 476.1 | 0.71 | 0.96 | 31.2% |
| door -x-y (x wall) 1 | 555 | 4.9 | 476.6 | 0.70 | 1.02 | 29.2% |
| door -x-y (x wall) 2 | 264 | 4.9 | 494.3 | 0.32 | 0.96 | 4.0% |
| door -x-y (corner) | 107 | 53.3 | 498.7 | 0.14 | 0.96 | 2.2% |
| door +x-y (y wall) 0 | 561 | 4.9 | 470.3 | 0.72 | 1.08 | 31.2% |
| door +x-y (y wall) 1 | 560 | 4.9 | 488.2 | 0.69 | 1.08 | 30.6% |
| door +x-y (y wall) 2 | 262 | 4.9 | 513.9 | 0.31 | 1.02 | 3.8% |
| door +x-y (x wall) 0 | 563 | 4.9 | 465.4 | 0.73 | 0.96 | 31.9% |
| door +x-y (x wall) 1 | 557 | 4.9 | 486.6 | 0.69 | 1.02 | 24.5% |
| door +x-y (x wall) 2 | 274 | 4.9 | 512.7 | 0.32 | 0.96 | 1.9% |
| door +x-y (corner) | 98 | 68.9 | 493.9 | 0.14 | 1.02 | 4.5% |

Mean flow / w J averaged over the doors 0.52, over the avenues 0.23.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 871 | 564 / 307 / 169 | 0.7 | 467.7 | 2.23 | 3.31 | 91% | 79% | 13% | 3.71 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 518 | 553 / 0 / 17 | 0.7 | 473.6 | 1.20 | 1.91 | 79% | 67% | 12% | 3.46 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 66 | 280 / 0 / 0 | 0.7 | 503.9 | 0.56 | 1.50 | 12% | 10% | 2% | 2.49 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 882 | 568 / 314 / 210 | 0.7 | 466.5 | 2.34 | 3.71 | 91% | 77% | 15% | 3.71 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 520 | 561 / 0 / 17 | 0.7 | 479.6 | 1.21 | 2.11 | 78% | 65% | 12% | 3.42 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 65 | 251 / 0 / 0 | 0.7 | 509.2 | 0.49 | 1.50 | 12% | 12% | 0% | 2.71 |
| corner +x+y | 1.20 | 85.6 | 728 | 115 / 137 / 510 | 0.7 | 512.5 | 1.49 | 4.01 | 83% | 54% | 29% | 2.44 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 876 | 559 / 317 / 211 | 0.7 | 449.5 | 2.42 | 4.21 | 89% | 78% | 11% | 3.78 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 523 | 559 / 0 / 10 | 0.7 | 488.7 | 1.17 | 1.91 | 74% | 60% | 14% | 3.62 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 65 | 269 / 0 / 0 | 0.7 | 499.7 | 0.54 | 1.50 | 12% | 10% | 2% | 2.57 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 874 | 563 / 311 / 205 | 0.7 | 472.4 | 2.29 | 4.51 | 90% | 75% | 15% | 3.70 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 520 | 561 / 0 / 8 | 0.7 | 476.8 | 1.19 | 1.81 | 81% | 65% | 17% | 3.42 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 61 | 253 / 0 / 0 | 0.7 | 492.4 | 0.51 | 1.50 | 12% | 10% | 2% | 2.51 |
| corner -x+y | 1.20 | 85.6 | 726 | 120 / 133 / 491 | 0.7 | 493.6 | 1.51 | 3.21 | 86% | 54% | 32% | 2.41 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 865 | 559 / 306 / 165 | 0.7 | 473.6 | 2.18 | 3.31 | 90% | 77% | 12% | 3.68 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 521 | 560 / 0 / 8 | 0.7 | 468.1 | 1.21 | 1.81 | 81% | 70% | 11% | 3.59 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 62 | 272 / 0 / 0 | 0.7 | 488.0 | 0.56 | 1.60 | 10% | 8% | 2% | 2.73 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 874 | 557 / 317 / 212 | 0.7 | 473.1 | 2.30 | 3.81 | 90% | 75% | 15% | 3.72 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 519 | 560 / 0 / 7 | 0.7 | 473.6 | 1.20 | 1.71 | 79% | 67% | 12% | 3.56 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 65 | 259 / 0 / 0 | 0.7 | 491.3 | 0.53 | 1.40 | 12% | 10% | 2% | 2.69 |
| corner -x-y | 1.20 | 85.6 | 732 | 107 / 141 / 499 | 0.7 | 494.8 | 1.51 | 3.61 | 84% | 50% | 34% | 2.39 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 866 | 561 / 305 / 199 | 0.7 | 467.4 | 2.28 | 4.01 | 91% | 77% | 15% | 3.61 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 511 | 561 / 0 / 11 | 0.7 | 485.2 | 1.18 | 1.71 | 73% | 63% | 10% | 3.49 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 64 | 261 / 0 / 0 | 0.7 | 510.9 | 0.51 | 1.60 | 10% | 8% | 2% | 2.75 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 877 | 563 / 314 / 205 | 0.7 | 462.5 | 2.34 | 3.71 | 89% | 77% | 13% | 3.73 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 513 | 565 / 0 / 6 | 0.7 | 483.6 | 1.18 | 1.81 | 82% | 63% | 18% | 3.40 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 66 | 266 / 0 / 0 | 0.7 | 509.7 | 0.52 | 1.40 | 12% | 10% | 2% | 2.62 |
| corner +x-y | 1.20 | 85.6 | 735 | 98 / 138 / 516 | 0.7 | 505.0 | 1.49 | 3.51 | 82% | 59% | 24% | 2.50 |

The last agent out (agent 2265, t100 516.3 s): last gangway corner +x+y, exit door +x+y (corner). The gangway that cleared last: corner +x+y at 512.5 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.77 | 510.2 / 498.8 / 469.1 | 491.1 / 456.2 / 386.9 | 604327.5 | 1450337 | 0.221 |
| gangway | 1212 | 1112.9 | 6.77 | 507.6 / 495.7 / 414.4 | 491.1 / 456.2 / 386.9 | 603511.9 | 1308827 | 0.112 |
| walkway | 276 | 257.4 | 3.14 | 193.1 / 115.8 / 0.0 | 127.5 / 28.2 / 0.0 | 0.0 | 23603 | 0.904 |
| avenue | 912 | 858.9 | 1.77 | 202.5 / 0.0 / 0.0 | 175.3 / 0.0 / 0.0 | 0.0 | 87279 | 1.327 |
| exit | 32 | 3.2 | 0.00 | 487.6 / 485.0 / 437.6 | 237.5 / 212.9 / 127.3 | 815.7 | 1537 | 1.322 |
| concourse | 1116 | 1043.8 | 1.96 | 458.8 / 0.0 / 0.0 | 113.7 / 0.0 / 0.0 | 0.0 | 29093 | 1.195 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.59 | 443.4 / 426.2 / 414.9 | 429.9 / 426.2 / 411.0 | 575654.7 | 1687649 | 0.049 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 26.5 | 28.5 | gangway | 1.00 | 6.15 | 422.7 | 413.8 | 352.6 | 2083.5 | 0.019 |
| 2 | -26.5 | 29.5 | gangway | 1.00 | 6.30 | 418.7 | 395.8 | 334.1 | 2024.2 | 0.023 |
| 3 | -26.5 | -29.5 | gangway | 1.00 | 6.33 | 430.1 | 381.5 | 342.1 | 2018.0 | 0.024 |
| 4 | 28.5 | -26.5 | gangway | 1.00 | 5.89 | 443.0 | 415.6 | 354.4 | 2015.1 | 0.025 |
| 5 | 26.5 | 29.5 | gangway | 1.00 | 6.31 | 420.0 | 389.5 | 330.4 | 2014.3 | 0.023 |
| 6 | 27.5 | -27.5 | gangway | 1.00 | 5.86 | 434.8 | 430.4 | 363.6 | 1998.6 | 0.016 |
| 7 | -28.5 | 27.5 | gangway | 1.00 | 5.92 | 428.5 | 421.9 | 346.8 | 1991.8 | 0.022 |
| 8 | 27.5 | -28.5 | gangway | 1.00 | 5.95 | 418.9 | 408.6 | 355.1 | 1983.7 | 0.019 |
| 9 | -26.5 | 28.5 | gangway | 1.00 | 5.95 | 421.2 | 406.7 | 343.5 | 1972.5 | 0.021 |
| 10 | -29.5 | 26.5 | gangway | 1.00 | 5.92 | 425.0 | 388.6 | 337.7 | 1957.3 | 0.025 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -26.5 | 24.5 | seat row | 0.50 | 7.34 | 429.9 | 426.1 | 411.0 | 1435.4 | 0.016 |
| 2 | -24.5 | -26.5 | seat row | 0.50 | 7.29 | 426.6 | 426.2 | 410.2 | 1423.0 | 0.016 |
| 3 | -24.5 | 26.5 | seat row | 0.50 | 7.34 | 419.4 | 416.1 | 400.7 | 1422.6 | 0.014 |
| 4 | 26.5 | -24.5 | seat row | 0.50 | 7.33 | 424.1 | 420.0 | 409.8 | 1418.6 | 0.015 |
| 5 | 24.5 | -26.5 | seat row | 0.50 | 7.14 | 419.4 | 415.2 | 407.2 | 1410.2 | 0.014 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1577; agent-steps of seated agents on another row's clearway: 15228.

## Deposit check

Person-seconds deposited: 3140812.9, of them in excluded cells: 2826.788.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 257187 overlapping pair-steps: p99 0.0026, max 0.0170 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0026 max 0.0170; venue-geometry 2: p99 0.0028 max 0.0028 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00751 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 11 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.33 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 510 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
