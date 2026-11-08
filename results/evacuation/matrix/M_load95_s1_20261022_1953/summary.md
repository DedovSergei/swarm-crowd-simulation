# Experiment `M_load95_s1`

**Task 5.10 stage 4 (AMD 26.10.1): venue M, 95% load (seed 1), default model**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 15040 agents on 95% of the 15832 seats (spawnSeatedCrowd, seed 1), buffer N = 16384, 3068 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 1119479 evaluations, 46259 switches, 0 forced choices).
Capacity: **within design capacity** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T19:53:47, 106.2 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1224 | 214.1 |
| t90 | 2352 | 411.4 |
| t100 | 3068 | 536.6 |

t_p: the step by which ceil(p x 15040) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 779 | 0 | 39.7 | 467.4 | 19.3 | 25.5 | 72.8-82.7 |
| -x | 5.66 | 783 | 0 | 39.4 | 467.9 | 19.4 | 25.5 | 73.8-83.8 |
| +y | 5.66 | 782 | 0 | 39.7 | 463.9 | 19.5 | 25.5 | 49.0-58.9 |
| -y | 5.66 | 776 | 0 | 39.7 | 467.0 | 19.2 | 25.5 | 72.8-82.7 |
| door +x+y (y wall) 0 | 1.20 | 576 | 1057 | 4.9 | 475.7 | 61.1 | 85.3 | 26.6-36.6 |
| door +x+y (y wall) 1 | 1.20 | 577 | 649 | 4.9 | 496.9 | 58.6 | 85.3 | 24.5-34.5 |
| door +x+y (y wall) 2 | 1.20 | 246 | 167 | 4.9 | 534.5 | 23.2 | 85.3 | 10.0-19.9 |
| door +x+y (x wall) 0 | 1.20 | 582 | 1061 | 4.9 | 471.5 | 62.3 | 80.2 | 16.4-26.4 |
| door +x+y (x wall) 1 | 1.20 | 563 | 649 | 4.9 | 487.8 | 58.3 | 85.3 | 32.0-42.0 |
| door +x+y (x wall) 2 | 1.20 | 303 | 170 | 4.9 | 530.8 | 28.8 | 80.2 | 6.1-16.1 |
| door +x+y (corner) | 1.20 | 130 | 0 | 57.9 | 536.6 | 13.6 | 85.3 | 85.2-95.1 |
| door -x+y (y wall) 0 | 1.20 | 580 | 1061 | 4.9 | 491.8 | 59.5 | 85.3 | 18.2-28.2 |
| door -x+y (y wall) 1 | 1.20 | 564 | 653 | 4.9 | 497.3 | 57.3 | 90.3 | 19.1-29.0 |
| door -x+y (y wall) 2 | 1.20 | 287 | 168 | 4.9 | 516.5 | 28.0 | 80.2 | 7.9-17.8 |
| door -x+y (x wall) 0 | 1.20 | 577 | 1068 | 4.9 | 483.8 | 60.2 | 85.3 | 8.6-18.5 |
| door -x+y (x wall) 1 | 1.20 | 576 | 643 | 4.9 | 495.7 | 58.7 | 90.3 | 25.0-35.0 |
| door -x+y (x wall) 2 | 1.20 | 274 | 169 | 4.9 | 527.2 | 26.2 | 80.2 | 7.9-17.8 |
| door -x+y (corner) | 1.20 | 123 | 0 | 72.2 | 505.0 | 14.2 | 80.2 | 415.1-425.0 |
| door -x-y (y wall) 0 | 1.20 | 579 | 1058 | 4.9 | 489.2 | 59.8 | 85.3 | 15.7-25.7 |
| door -x-y (y wall) 1 | 1.20 | 574 | 656 | 4.9 | 502.9 | 57.6 | 80.2 | 13.1-23.1 |
| door -x-y (y wall) 2 | 1.20 | 253 | 168 | 4.9 | 519.1 | 24.6 | 85.3 | 10.5-20.5 |
| door -x-y (x wall) 0 | 1.20 | 581 | 1070 | 4.9 | 492.4 | 59.6 | 85.3 | 17.3-27.3 |
| door -x-y (x wall) 1 | 1.20 | 565 | 645 | 4.9 | 497.3 | 57.4 | 85.3 | 15.2-25.2 |
| door -x-y (x wall) 2 | 1.20 | 327 | 174 | 4.9 | 522.8 | 31.6 | 80.2 | 4.7-14.7 |
| door -x-y (corner) | 1.20 | 104 | 0 | 82.7 | 512.7 | 12.1 | 80.2 | 98.5-108.4 |
| door +x-y (y wall) 0 | 1.20 | 581 | 1063 | 4.9 | 470.3 | 62.4 | 85.3 | 10.0-19.9 |
| door +x-y (y wall) 1 | 1.20 | 582 | 642 | 4.9 | 500.1 | 58.7 | 85.3 | 17.3-27.3 |
| door +x-y (y wall) 2 | 1.20 | 268 | 169 | 5.2 | 519.5 | 26.0 | 80.2 | 6.3-16.3 |
| door +x-y (x wall) 0 | 1.20 | 583 | 1062 | 4.9 | 490.8 | 60.0 | 90.3 | 16.8-26.8 |
| door +x-y (x wall) 1 | 1.20 | 571 | 649 | 4.9 | 501.3 | 57.5 | 85.3 | 18.7-28.7 |
| door +x-y (x wall) 2 | 1.20 | 289 | 169 | 4.9 | 516.8 | 28.2 | 80.2 | 4.7-14.7 |
| door +x-y (corner) | 1.20 | 105 | 0 | 71.5 | 505.7 | 12.1 | 70.2 | 449.2-459.1 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 779 | 5.2% | 18.4% |
| -x | avenue | 5.66 | 783 | 5.2% | 18.5% |
| +y | avenue | 5.66 | 782 | 5.2% | 18.5% |
| -y | avenue | 5.66 | 776 | 5.2% | 18.3% |
| door +x+y (y wall) 0 | door | 1.20 | 576 | 3.8% | 64.2% |
| door +x+y (y wall) 1 | door | 1.20 | 577 | 3.8% | 64.3% |
| door +x+y (y wall) 2 | door | 1.20 | 246 | 1.6% | 27.4% |
| door +x+y (x wall) 0 | door | 1.20 | 582 | 3.9% | 64.9% |
| door +x+y (x wall) 1 | door | 1.20 | 563 | 3.7% | 62.7% |
| door +x+y (x wall) 2 | door | 1.20 | 303 | 2.0% | 33.8% |
| door +x+y (corner) | door | 1.20 | 130 | 0.9% | 14.5% |
| door -x+y (y wall) 0 | door | 1.20 | 580 | 3.9% | 64.6% |
| door -x+y (y wall) 1 | door | 1.20 | 564 | 3.8% | 62.9% |
| door -x+y (y wall) 2 | door | 1.20 | 287 | 1.9% | 32.0% |
| door -x+y (x wall) 0 | door | 1.20 | 577 | 3.8% | 64.3% |
| door -x+y (x wall) 1 | door | 1.20 | 576 | 3.8% | 64.2% |
| door -x+y (x wall) 2 | door | 1.20 | 274 | 1.8% | 30.5% |
| door -x+y (corner) | door | 1.20 | 123 | 0.8% | 13.7% |
| door -x-y (y wall) 0 | door | 1.20 | 579 | 3.8% | 64.5% |
| door -x-y (y wall) 1 | door | 1.20 | 574 | 3.8% | 64.0% |
| door -x-y (y wall) 2 | door | 1.20 | 253 | 1.7% | 28.2% |
| door -x-y (x wall) 0 | door | 1.20 | 581 | 3.9% | 64.8% |
| door -x-y (x wall) 1 | door | 1.20 | 565 | 3.8% | 63.0% |
| door -x-y (x wall) 2 | door | 1.20 | 327 | 2.2% | 36.4% |
| door -x-y (corner) | door | 1.20 | 104 | 0.7% | 11.6% |
| door +x-y (y wall) 0 | door | 1.20 | 581 | 3.9% | 64.8% |
| door +x-y (y wall) 1 | door | 1.20 | 582 | 3.9% | 64.9% |
| door +x-y (y wall) 2 | door | 1.20 | 268 | 1.8% | 29.9% |
| door +x-y (x wall) 0 | door | 1.20 | 583 | 3.9% | 65.0% |
| door +x-y (x wall) 1 | door | 1.20 | 571 | 3.8% | 63.6% |
| door +x-y (x wall) 2 | door | 1.20 | 289 | 1.9% | 32.2% |
| door +x-y (corner) | door | 1.20 | 105 | 0.7% | 11.7% |
| **doors (28)** | door | 33.60 | 11920 | 79.3% | |
| **avenues (4)** | avenue | 22.64 | 3120 | 20.7% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 536.6 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 35.8%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 905 | 6.0% | 905 | 6.0% |
| straight +x+y (y wing) 1 | straight | yes | 583 | 3.9% | 577 | 3.8% |
| straight +x+y (y wing) 2 | straight | yes | 246 | 1.6% | 246 | 1.6% |
| straight +x+y (x wing) 0 | straight | yes | 895 | 6.0% | 895 | 6.0% |
| straight +x+y (x wing) 1 | straight | yes | 571 | 3.8% | 565 | 3.8% |
| straight +x+y (x wing) 2 | straight | yes | 301 | 2.0% | 301 | 2.0% |
| corner +x+y | corner | yes | 764 | 5.1% | 264 | 1.8% |
| straight -x+y (y wing) 0 | straight | yes | 902 | 6.0% | 902 | 6.0% |
| straight -x+y (y wing) 1 | straight | yes | 572 | 3.8% | 566 | 3.8% |
| straight -x+y (y wing) 2 | straight | yes | 285 | 1.9% | 285 | 1.9% |
| straight -x+y (x wing) 0 | straight | yes | 900 | 6.0% | 900 | 6.0% |
| straight -x+y (x wing) 1 | straight | yes | 581 | 3.9% | 576 | 3.8% |
| straight -x+y (x wing) 2 | straight | yes | 274 | 1.8% | 274 | 1.8% |
| corner -x+y | corner | yes | 754 | 5.0% | 259 | 1.7% |
| straight -x-y (y wing) 0 | straight | yes | 901 | 6.0% | 901 | 6.0% |
| straight -x-y (y wing) 1 | straight | yes | 581 | 3.9% | 574 | 3.8% |
| straight -x-y (y wing) 2 | straight | yes | 253 | 1.7% | 253 | 1.7% |
| straight -x-y (x wing) 0 | straight | yes | 904 | 6.0% | 904 | 6.0% |
| straight -x-y (x wing) 1 | straight | yes | 575 | 3.8% | 566 | 3.8% |
| straight -x-y (x wing) 2 | straight | yes | 326 | 2.2% | 326 | 2.2% |
| corner -x-y | corner | yes | 781 | 5.2% | 247 | 1.6% |
| straight +x-y (y wing) 0 | straight | yes | 899 | 6.0% | 899 | 6.0% |
| straight +x-y (y wing) 1 | straight | yes | 587 | 3.9% | 582 | 3.9% |
| straight +x-y (y wing) 2 | straight | yes | 268 | 1.8% | 268 | 1.8% |
| straight +x-y (x wing) 0 | straight | yes | 908 | 6.0% | 908 | 6.0% |
| straight +x-y (x wing) 1 | straight | yes | 575 | 3.8% | 571 | 3.8% |
| straight +x-y (x wing) 2 | straight | yes | 289 | 1.9% | 289 | 1.9% |
| corner +x-y | corner | yes | 761 | 5.1% | 237 | 1.6% |
| **straight (24)** | | | 14081 | | 14033 | 93.3% |
| **corner (4)** | | | 3060 | | 1007 | 6.7% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 779 | 39.7 | 467.4 | 0.23 | 0.31 | 0.0% |
| -x | 783 | 39.4 | 467.9 | 0.23 | 0.31 | 0.0% |
| +y | 782 | 39.7 | 463.9 | 0.23 | 0.31 | 0.0% |
| -y | 776 | 39.7 | 467.0 | 0.23 | 0.31 | 0.0% |
| door +x+y (y wall) 0 | 576 | 4.9 | 475.7 | 0.73 | 1.02 | 39.6% |
| door +x+y (y wall) 1 | 577 | 4.9 | 496.9 | 0.70 | 1.02 | 34.0% |
| door +x+y (y wall) 2 | 246 | 4.9 | 534.5 | 0.28 | 1.02 | 1.9% |
| door +x+y (x wall) 0 | 582 | 4.9 | 471.5 | 0.75 | 0.96 | 39.6% |
| door +x+y (x wall) 1 | 563 | 4.9 | 487.8 | 0.70 | 1.02 | 24.5% |
| door +x+y (x wall) 2 | 303 | 4.9 | 530.8 | 0.34 | 0.96 | 3.7% |
| door +x+y (corner) | 130 | 57.9 | 536.6 | 0.16 | 1.02 | 2.0% |
| door -x+y (y wall) 0 | 580 | 4.9 | 491.8 | 0.71 | 1.02 | 36.0% |
| door -x+y (y wall) 1 | 564 | 4.9 | 497.3 | 0.68 | 1.08 | 26.0% |
| door -x+y (y wall) 2 | 287 | 4.9 | 516.5 | 0.34 | 0.96 | 5.8% |
| door -x+y (x wall) 0 | 577 | 4.9 | 483.8 | 0.72 | 1.02 | 30.6% |
| door -x+y (x wall) 1 | 576 | 4.9 | 495.7 | 0.70 | 1.08 | 24.0% |
| door -x+y (x wall) 2 | 274 | 4.9 | 527.2 | 0.31 | 0.96 | 7.5% |
| door -x+y (corner) | 123 | 72.2 | 505.0 | 0.17 | 0.96 | 0.0% |
| door -x-y (y wall) 0 | 579 | 4.9 | 489.2 | 0.71 | 1.02 | 22.0% |
| door -x-y (y wall) 1 | 574 | 4.9 | 502.9 | 0.69 | 0.96 | 31.4% |
| door -x-y (y wall) 2 | 253 | 4.9 | 519.1 | 0.29 | 1.02 | 3.8% |
| door -x-y (x wall) 0 | 581 | 4.9 | 492.4 | 0.71 | 1.02 | 34.0% |
| door -x-y (x wall) 1 | 565 | 4.9 | 497.3 | 0.69 | 1.02 | 24.0% |
| door -x-y (x wall) 2 | 327 | 4.9 | 522.8 | 0.38 | 0.96 | 3.8% |
| door -x-y (corner) | 104 | 82.7 | 512.7 | 0.14 | 0.96 | 2.3% |
| door +x-y (y wall) 0 | 581 | 4.9 | 470.3 | 0.75 | 1.02 | 39.6% |
| door +x-y (y wall) 1 | 582 | 4.9 | 500.1 | 0.70 | 1.02 | 21.6% |
| door +x-y (y wall) 2 | 268 | 5.2 | 519.5 | 0.31 | 0.96 | 5.7% |
| door +x-y (x wall) 0 | 583 | 4.9 | 490.8 | 0.72 | 1.08 | 32.0% |
| door +x-y (x wall) 1 | 571 | 4.9 | 501.3 | 0.69 | 1.02 | 27.5% |
| door +x-y (x wall) 2 | 289 | 4.9 | 516.8 | 0.34 | 0.96 | 1.9% |
| door +x-y (corner) | 105 | 71.5 | 505.7 | 0.14 | 0.84 | 0.0% |

Mean flow / w J averaged over the doors 0.52, over the avenues 0.23.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 905 | 576 / 329 / 215 | 0.7 | 472.8 | 2.37 | 4.11 | 90% | 79% | 10% | 3.71 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 529 | 577 / 0 / 17 | 0.7 | 493.9 | 1.20 | 1.60 | 74% | 64% | 10% | 3.73 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 64 | 246 / 0 / 0 | 0.7 | 531.5 | 0.46 | 1.60 | 11% | 9% | 2% | 2.59 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 895 | 582 / 313 / 212 | 0.7 | 468.6 | 2.37 | 3.61 | 89% | 81% | 9% | 3.90 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 537 | 565 / 0 / 8 | 0.7 | 484.8 | 1.18 | 1.60 | 82% | 67% | 14% | 3.53 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 68 | 301 / 0 / 0 | 0.7 | 527.9 | 0.57 | 1.40 | 11% | 11% | 0% | 2.70 |
| corner +x+y | 1.20 | 85.6 | 755 | 130 / 134 / 515 | 0.7 | 532.8 | 1.46 | 4.11 | 83% | 56% | 28% | 2.42 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 902 | 580 / 322 / 232 | 0.7 | 488.9 | 2.32 | 3.81 | 90% | 76% | 14% | 3.53 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 537 | 566 / 0 / 8 | 0.7 | 494.3 | 1.16 | 1.71 | 78% | 64% | 14% | 3.49 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 64 | 285 / 0 / 0 | 0.7 | 513.5 | 0.56 | 1.50 | 12% | 8% | 4% | 2.54 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 900 | 577 / 323 / 213 | 0.7 | 480.8 | 2.32 | 3.61 | 90% | 78% | 12% | 3.68 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 546 | 576 / 0 / 8 | 0.7 | 492.7 | 1.19 | 1.60 | 78% | 64% | 14% | 3.55 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 68 | 274 / 0 / 0 | 0.7 | 524.2 | 0.52 | 1.50 | 11% | 9% | 2% | 2.61 |
| corner -x+y | 1.20 | 85.6 | 745 | 123 / 136 / 502 | 0.7 | 518.1 | 1.47 | 3.41 | 87% | 56% | 31% | 2.40 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 901 | 579 / 322 / 225 | 0.7 | 486.2 | 2.32 | 4.31 | 90% | 78% | 12% | 3.71 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 534 | 574 / 0 / 8 | 0.7 | 499.9 | 1.17 | 1.71 | 75% | 63% | 12% | 3.66 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 62 | 253 / 0 / 0 | 0.7 | 516.1 | 0.49 | 1.50 | 10% | 10% | 0% | 2.78 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 904 | 581 / 323 / 189 | 0.7 | 489.4 | 2.24 | 3.41 | 78% | 76% | 2% | 4.19 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 531 | 566 / 0 / 12 | 0.7 | 494.3 | 1.17 | 1.71 | 78% | 62% | 16% | 3.56 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 69 | 326 / 0 / 0 | 0.7 | 519.8 | 0.63 | 1.50 | 13% | 9% | 4% | 2.46 |
| corner -x-y | 1.20 | 85.6 | 770 | 104 / 143 / 543 | 0.7 | 513.7 | 1.54 | 3.51 | 85% | 48% | 37% | 2.34 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 899 | 581 / 318 / 182 | 0.7 | 467.4 | 2.32 | 3.81 | 91% | 81% | 11% | 3.77 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 533 | 582 / 0 / 6 | 0.7 | 497.1 | 1.18 | 1.71 | 80% | 66% | 14% | 3.49 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 67 | 268 / 0 / 0 | 0.7 | 516.5 | 0.52 | 1.40 | 12% | 10% | 2% | 2.63 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 908 | 583 / 325 / 205 | 0.7 | 487.8 | 2.28 | 3.51 | 90% | 78% | 12% | 3.78 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 527 | 571 / 0 / 4 | 0.7 | 498.3 | 1.16 | 1.81 | 78% | 66% | 12% | 3.43 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 65 | 289 / 0 / 0 | 0.7 | 513.9 | 0.56 | 1.60 | 12% | 12% | 0% | 2.71 |
| corner +x-y | 1.20 | 85.6 | 755 | 105 / 132 / 528 | 0.7 | 510.6 | 1.50 | 4.21 | 87% | 60% | 27% | 2.44 |

The last agent out (agent 2332, t100 536.6 s): last gangway corner +x+y, exit door +x+y (corner). The gangway that cleared last: corner +x+y at 532.8 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.99 | 524.0 / 513.0 / 481.5 | 510.2 / 463.0 / 408.4 | 633741.7 | 1505747 | 0.219 |
| gangway | 1212 | 1112.9 | 6.99 | 522.8 / 510.6 / 428.0 | 510.2 / 463.0 / 408.4 | 632903.2 | 1361098 | 0.111 |
| walkway | 276 | 257.4 | 2.98 | 186.6 / 110.4 / 0.0 | 119.3 / 22.9 / 0.0 | 0.0 | 23558 | 0.925 |
| avenue | 912 | 858.9 | 1.79 | 201.1 / 0.0 / 0.0 | 158.6 / 0.0 / 0.0 | 0.0 | 89570 | 1.327 |
| exit | 32 | 3.2 | 0.00 | 498.7 / 496.4 / 448.8 | 246.1 / 223.0 / 133.6 | 838.6 | 1580 | 1.324 |
| concourse | 1116 | 1043.8 | 2.00 | 469.6 / 0.0 / 0.0 | 118.1 / 0.0 / 0.0 | 0.0 | 29941 | 1.195 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.59 | 450.0 / 445.5 / 441.5 | 446.4 / 445.5 / 437.6 | 640806.9 | 1841088 | 0.046 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 27.5 | -26.5 | gangway | 1.00 | 5.80 | 443.9 | 433.4 | 391.4 | 2207.9 | 0.017 |
| 2 | 28.5 | -26.5 | gangway | 1.00 | 6.04 | 436.2 | 426.2 | 368.2 | 2153.0 | 0.022 |
| 3 | -28.5 | 27.5 | gangway | 1.00 | 5.75 | 437.8 | 427.8 | 378.7 | 2134.5 | 0.021 |
| 4 | -27.5 | 26.5 | gangway | 1.00 | 5.83 | 445.1 | 424.7 | 375.5 | 2123.5 | 0.019 |
| 5 | -26.5 | -28.5 | gangway | 1.00 | 6.15 | 428.7 | 418.6 | 365.0 | 2114.2 | 0.021 |
| 6 | -28.5 | 26.5 | gangway | 1.00 | 6.00 | 441.8 | 423.8 | 364.7 | 2109.6 | 0.019 |
| 7 | 26.5 | -28.5 | gangway | 1.00 | 6.36 | 445.1 | 426.2 | 355.2 | 2078.7 | 0.024 |
| 8 | 26.5 | 29.5 | gangway | 1.00 | 6.06 | 425.5 | 398.6 | 350.7 | 2060.2 | 0.027 |
| 9 | 27.5 | -27.5 | gangway | 1.00 | 6.08 | 437.8 | 422.9 | 355.9 | 2040.4 | 0.016 |
| 10 | 28.5 | -27.5 | gangway | 1.00 | 5.97 | 429.0 | 419.3 | 354.2 | 2040.3 | 0.017 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -24.5 | -26.5 | seat row | 0.50 | 7.25 | 439.7 | 436.9 | 426.1 | 1502.6 | 0.014 |
| 2 | 26.5 | -24.5 | seat row | 0.50 | 7.15 | 446.2 | 445.5 | 437.6 | 1479.5 | 0.015 |
| 3 | -24.5 | 26.5 | seat row | 0.50 | 6.95 | 441.3 | 438.7 | 424.8 | 1451.2 | 0.016 |
| 4 | 26.5 | -23.5 | seat row | 0.50 | 7.00 | 442.3 | 440.1 | 425.2 | 1438.3 | 0.013 |
| 5 | 26.5 | 24.5 | seat row | 0.50 | 7.21 | 444.4 | 438.7 | 417.9 | 1421.3 | 0.016 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1676; agent-steps of seated agents on another row's clearway: 15987.

## Deposit check

Person-seconds deposited: 3349759.4, of them in excluded cells: 2923.928.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 284565 overlapping pair-steps: p99 0.0027, max 0.0746 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0027 max 0.0746; venue-geometry 2: p99 0.0001 max 0.0001 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00762 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 14 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.41 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 570 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
