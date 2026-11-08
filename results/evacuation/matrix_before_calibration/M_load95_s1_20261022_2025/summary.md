# Experiment `M_load95_s1`

**Task 5.10 stage 4 (AMD 26.10.1): Task 5.8's model (the level spacing on the gangway inclines, --stair-flow off): venue M, 95% load (seed 1)**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 15040 agents on 95% of the 15832 seats (spawnSeatedCrowd, seed 1), buffer N = 16384, 2466 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 880562 evaluations, 39610 switches, 0 forced choices).
Capacity: **within design capacity** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T20:25:40, 123.1 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 980 | 171.4 |
| t90 | 1838 | 321.5 |
| t100 | 2466 | 431.3 |

t_p: the step by which ceil(p x 15040) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 723 | 0 | 39.7 | 367.3 | 23.4 | 25.5 | 65.8-75.7 |
| -x | 5.66 | 724 | 0 | 39.5 | 370.8 | 23.2 | 25.5 | 68.6-78.5 |
| +y | 5.66 | 723 | 0 | 39.5 | 364.5 | 23.6 | 26.6 | 164.6-174.6 |
| -y | 5.66 | 731 | 0 | 39.5 | 370.3 | 23.4 | 26.6 | 122.1-132.1 |
| door +x+y (y wall) 0 | 1.20 | 603 | 1057 | 4.9 | 388.8 | 78.5 | 115.3 | 22.6-32.5 |
| door +x+y (y wall) 1 | 1.20 | 556 | 649 | 4.9 | 384.6 | 73.2 | 110.3 | 20.1-30.1 |
| door +x+y (y wall) 2 | 1.20 | 261 | 167 | 4.9 | 404.4 | 32.7 | 105.3 | 10.7-20.6 |
| door +x+y (x wall) 0 | 1.20 | 596 | 1061 | 4.9 | 374.5 | 80.6 | 110.3 | 146.9-156.9 |
| door +x+y (x wall) 1 | 1.20 | 579 | 649 | 4.9 | 383.6 | 76.4 | 105.3 | 23.8-33.8 |
| door +x+y (x wall) 2 | 1.20 | 295 | 170 | 4.9 | 398.1 | 37.5 | 110.3 | 13.3-23.3 |
| door +x+y (corner) | 1.20 | 143 | 0 | 58.9 | 386.4 | 21.8 | 105.3 | 284.7-294.7 |
| door -x+y (y wall) 0 | 1.20 | 598 | 1061 | 4.9 | 390.7 | 77.5 | 110.3 | 27.5-37.4 |
| door -x+y (y wall) 1 | 1.20 | 590 | 653 | 4.9 | 387.8 | 77.0 | 105.3 | 21.3-31.3 |
| door -x+y (y wall) 2 | 1.20 | 333 | 168 | 4.9 | 424.3 | 39.7 | 105.3 | 7.7-17.7 |
| door -x+y (x wall) 0 | 1.20 | 607 | 1068 | 4.9 | 390.4 | 78.7 | 105.3 | 23.1-33.1 |
| door -x+y (x wall) 1 | 1.20 | 583 | 643 | 4.9 | 384.3 | 76.8 | 105.3 | 17.8-27.8 |
| door -x+y (x wall) 2 | 1.20 | 244 | 169 | 4.9 | 422.6 | 29.2 | 105.3 | 8.2-18.2 |
| door -x+y (corner) | 1.20 | 83 | 0 | 54.7 | 411.7 | 11.6 | 85.3 | 63.5-73.5 |
| door -x-y (y wall) 0 | 1.20 | 605 | 1058 | 4.9 | 390.7 | 78.4 | 105.3 | 8.2-18.2 |
| door -x-y (y wall) 1 | 1.20 | 575 | 656 | 4.9 | 398.3 | 73.1 | 105.3 | 18.0-28.0 |
| door -x-y (y wall) 2 | 1.20 | 269 | 168 | 4.9 | 419.4 | 32.4 | 105.3 | 8.2-18.2 |
| door -x-y (x wall) 0 | 1.20 | 602 | 1070 | 4.9 | 375.5 | 81.2 | 105.3 | 18.2-28.2 |
| door -x-y (x wall) 1 | 1.20 | 581 | 645 | 4.9 | 392.3 | 74.9 | 110.3 | 21.3-31.3 |
| door -x-y (x wall) 2 | 1.20 | 312 | 174 | 4.9 | 428.5 | 36.8 | 105.3 | 7.7-17.7 |
| door -x-y (corner) | 1.20 | 97 | 0 | 42.3 | 431.3 | 12.5 | 80.2 | 177.2-187.2 |
| door +x-y (y wall) 0 | 1.20 | 595 | 1063 | 4.9 | 385.5 | 78.1 | 105.3 | 38.1-48.1 |
| door +x-y (y wall) 1 | 1.20 | 589 | 642 | 4.9 | 390.9 | 76.3 | 105.3 | 21.2-31.1 |
| door +x-y (y wall) 2 | 1.20 | 267 | 169 | 5.2 | 427.3 | 31.6 | 105.3 | 19.2-29.2 |
| door +x-y (x wall) 0 | 1.20 | 603 | 1062 | 4.9 | 375.2 | 81.4 | 110.3 | 237.5-247.5 |
| door +x-y (x wall) 1 | 1.20 | 569 | 649 | 4.9 | 387.4 | 74.3 | 105.3 | 13.3-23.3 |
| door +x-y (x wall) 2 | 1.20 | 287 | 169 | 4.9 | 426.1 | 34.1 | 105.3 | 7.9-17.8 |
| door +x-y (corner) | 1.20 | 117 | 0 | 36.4 | 419.3 | 15.3 | 70.2 | 283.9-293.8 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 723 | 4.8% | 21.3% |
| -x | avenue | 5.66 | 724 | 4.8% | 21.3% |
| +y | avenue | 5.66 | 723 | 4.8% | 21.3% |
| -y | avenue | 5.66 | 731 | 4.9% | 21.5% |
| door +x+y (y wall) 0 | door | 1.20 | 603 | 4.0% | 83.6% |
| door +x+y (y wall) 1 | door | 1.20 | 556 | 3.7% | 77.1% |
| door +x+y (y wall) 2 | door | 1.20 | 261 | 1.7% | 36.2% |
| door +x+y (x wall) 0 | door | 1.20 | 596 | 4.0% | 82.6% |
| door +x+y (x wall) 1 | door | 1.20 | 579 | 3.8% | 80.3% |
| door +x+y (x wall) 2 | door | 1.20 | 295 | 2.0% | 40.9% |
| door +x+y (corner) | door | 1.20 | 143 | 1.0% | 19.8% |
| door -x+y (y wall) 0 | door | 1.20 | 598 | 4.0% | 82.9% |
| door -x+y (y wall) 1 | door | 1.20 | 590 | 3.9% | 81.8% |
| door -x+y (y wall) 2 | door | 1.20 | 333 | 2.2% | 46.2% |
| door -x+y (x wall) 0 | door | 1.20 | 607 | 4.0% | 84.2% |
| door -x+y (x wall) 1 | door | 1.20 | 583 | 3.9% | 80.8% |
| door -x+y (x wall) 2 | door | 1.20 | 244 | 1.6% | 33.8% |
| door -x+y (corner) | door | 1.20 | 83 | 0.6% | 11.5% |
| door -x-y (y wall) 0 | door | 1.20 | 605 | 4.0% | 83.9% |
| door -x-y (y wall) 1 | door | 1.20 | 575 | 3.8% | 79.7% |
| door -x-y (y wall) 2 | door | 1.20 | 269 | 1.8% | 37.3% |
| door -x-y (x wall) 0 | door | 1.20 | 602 | 4.0% | 83.5% |
| door -x-y (x wall) 1 | door | 1.20 | 581 | 3.9% | 80.6% |
| door -x-y (x wall) 2 | door | 1.20 | 312 | 2.1% | 43.3% |
| door -x-y (corner) | door | 1.20 | 97 | 0.6% | 13.5% |
| door +x-y (y wall) 0 | door | 1.20 | 595 | 4.0% | 82.5% |
| door +x-y (y wall) 1 | door | 1.20 | 589 | 3.9% | 81.7% |
| door +x-y (y wall) 2 | door | 1.20 | 267 | 1.8% | 37.0% |
| door +x-y (x wall) 0 | door | 1.20 | 603 | 4.0% | 83.6% |
| door +x-y (x wall) 1 | door | 1.20 | 569 | 3.8% | 78.9% |
| door +x-y (x wall) 2 | door | 1.20 | 287 | 1.9% | 39.8% |
| door +x-y (corner) | door | 1.20 | 117 | 0.8% | 16.2% |
| **doors (28)** | door | 33.60 | 12139 | 80.7% | |
| **avenues (4)** | avenue | 22.64 | 2901 | 19.3% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 431.3 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 44.5%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 902 | 6.0% | 902 | 6.0% |
| straight +x+y (y wing) 1 | straight | yes | 570 | 3.8% | 563 | 3.7% |
| straight +x+y (y wing) 2 | straight | yes | 254 | 1.7% | 254 | 1.7% |
| straight +x+y (x wing) 0 | straight | yes | 887 | 5.9% | 887 | 5.9% |
| straight +x+y (x wing) 1 | straight | yes | 586 | 3.9% | 580 | 3.9% |
| straight +x+y (x wing) 2 | straight | yes | 294 | 2.0% | 294 | 2.0% |
| corner +x+y | corner | yes | 764 | 5.1% | 273 | 1.8% |
| straight -x+y (y wing) 0 | straight | yes | 900 | 6.0% | 900 | 6.0% |
| straight -x+y (y wing) 1 | straight | yes | 598 | 4.0% | 595 | 4.0% |
| straight -x+y (y wing) 2 | straight | yes | 329 | 2.2% | 328 | 2.2% |
| straight -x+y (x wing) 0 | straight | yes | 895 | 6.0% | 895 | 6.0% |
| straight -x+y (x wing) 1 | straight | yes | 590 | 3.9% | 584 | 3.9% |
| straight -x+y (x wing) 2 | straight | yes | 243 | 1.6% | 243 | 1.6% |
| corner -x+y | corner | yes | 759 | 5.0% | 217 | 1.4% |
| straight -x-y (y wing) 0 | straight | yes | 904 | 6.0% | 904 | 6.0% |
| straight -x-y (y wing) 1 | straight | yes | 594 | 3.9% | 587 | 3.9% |
| straight -x-y (y wing) 2 | straight | yes | 257 | 1.7% | 257 | 1.7% |
| straight -x-y (x wing) 0 | straight | yes | 907 | 6.0% | 907 | 6.0% |
| straight -x-y (x wing) 1 | straight | yes | 593 | 3.9% | 587 | 3.9% |
| straight -x-y (x wing) 2 | straight | yes | 306 | 2.0% | 306 | 2.0% |
| corner -x-y | corner | yes | 759 | 5.0% | 223 | 1.5% |
| straight +x-y (y wing) 0 | straight | yes | 901 | 6.0% | 901 | 6.0% |
| straight +x-y (y wing) 1 | straight | yes | 593 | 3.9% | 589 | 3.9% |
| straight +x-y (y wing) 2 | straight | yes | 267 | 1.8% | 267 | 1.8% |
| straight +x-y (x wing) 0 | straight | yes | 901 | 6.0% | 901 | 6.0% |
| straight +x-y (x wing) 1 | straight | yes | 580 | 3.9% | 576 | 3.8% |
| straight +x-y (x wing) 2 | straight | yes | 281 | 1.9% | 280 | 1.9% |
| corner +x-y | corner | yes | 749 | 5.0% | 240 | 1.6% |
| **straight (24)** | | | 14132 | | 14087 | 93.7% |
| **corner (4)** | | | 3031 | | 953 | 6.3% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 723 | 39.7 | 367.3 | 0.28 | 0.31 | 0.0% |
| -x | 724 | 39.5 | 370.8 | 0.28 | 0.31 | 0.0% |
| +y | 723 | 39.5 | 364.5 | 0.28 | 0.32 | 0.0% |
| -y | 731 | 39.5 | 370.3 | 0.28 | 0.32 | 0.0% |
| door +x+y (y wall) 0 | 603 | 4.9 | 388.8 | 0.94 | 1.38 | 76.9% |
| door +x+y (y wall) 1 | 556 | 4.9 | 384.6 | 0.88 | 1.32 | 74.4% |
| door +x+y (y wall) 2 | 261 | 4.9 | 404.4 | 0.39 | 1.26 | 12.2% |
| door +x+y (x wall) 0 | 596 | 4.9 | 374.5 | 0.96 | 1.32 | 78.9% |
| door +x+y (x wall) 1 | 579 | 4.9 | 383.6 | 0.91 | 1.26 | 71.8% |
| door +x+y (x wall) 2 | 295 | 4.9 | 398.1 | 0.45 | 1.32 | 12.5% |
| door +x+y (corner) | 143 | 58.9 | 386.4 | 0.26 | 1.26 | 2.9% |
| door -x+y (y wall) 0 | 598 | 4.9 | 390.7 | 0.93 | 1.32 | 75.0% |
| door -x+y (y wall) 1 | 590 | 4.9 | 387.8 | 0.92 | 1.26 | 69.2% |
| door -x+y (y wall) 2 | 333 | 4.9 | 424.3 | 0.47 | 1.26 | 9.3% |
| door -x+y (x wall) 0 | 607 | 4.9 | 390.4 | 0.94 | 1.26 | 77.5% |
| door -x+y (x wall) 1 | 583 | 4.9 | 384.3 | 0.92 | 1.26 | 74.4% |
| door -x+y (x wall) 2 | 244 | 4.9 | 422.6 | 0.35 | 1.26 | 11.6% |
| door -x+y (corner) | 83 | 54.7 | 411.7 | 0.14 | 1.02 | 0.0% |
| door -x-y (y wall) 0 | 605 | 4.9 | 390.7 | 0.94 | 1.26 | 77.5% |
| door -x-y (y wall) 1 | 575 | 4.9 | 398.3 | 0.87 | 1.26 | 60.0% |
| door -x-y (y wall) 2 | 269 | 4.9 | 419.4 | 0.39 | 1.26 | 9.3% |
| door -x-y (x wall) 0 | 602 | 4.9 | 375.5 | 0.97 | 1.26 | 78.9% |
| door -x-y (x wall) 1 | 581 | 4.9 | 392.3 | 0.90 | 1.32 | 67.5% |
| door -x-y (x wall) 2 | 312 | 4.9 | 428.5 | 0.44 | 1.26 | 14.0% |
| door -x-y (corner) | 97 | 42.3 | 431.3 | 0.15 | 0.96 | 0.0% |
| door +x-y (y wall) 0 | 595 | 4.9 | 385.5 | 0.93 | 1.26 | 76.9% |
| door +x-y (y wall) 1 | 589 | 4.9 | 390.9 | 0.91 | 1.26 | 67.5% |
| door +x-y (y wall) 2 | 267 | 5.2 | 427.3 | 0.38 | 1.26 | 11.6% |
| door +x-y (x wall) 0 | 603 | 4.9 | 375.2 | 0.97 | 1.32 | 81.6% |
| door +x-y (x wall) 1 | 569 | 4.9 | 387.4 | 0.89 | 1.26 | 66.7% |
| door +x-y (x wall) 2 | 287 | 4.9 | 426.1 | 0.41 | 1.26 | 9.3% |
| door +x-y (corner) | 117 | 36.4 | 419.3 | 0.18 | 0.84 | 0.0% |

Mean flow / w J averaged over the doors 0.67, over the avenues 0.28.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 902 | 603 / 299 / 172 | 0.7 | 385.8 | 2.79 | 4.51 | 74% | 74% | 0% | 4.38 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 532 | 563 / 0 / 16 | 0.7 | 381.6 | 1.52 | 2.31 | 79% | 67% | 13% | 3.57 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 64 | 254 / 0 / 0 | 0.7 | 401.4 | 0.63 | 2.01 | 10% | 10% | 0% | 3.03 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 887 | 596 / 291 / 173 | 0.7 | 371.5 | 2.86 | 4.61 | 82% | 76% | 5% | 4.20 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 549 | 580 / 0 / 10 | 0.7 | 380.6 | 1.55 | 2.21 | 79% | 67% | 13% | 3.66 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 66 | 294 / 0 / 0 | 0.7 | 395.1 | 0.75 | 2.11 | 12% | 12% | 0% | 3.05 |
| corner +x+y | 1.20 | 85.6 | 753 | 143 / 130 / 506 | 0.7 | 395.5 | 1.97 | 4.31 | 80% | 57% | 22% | 2.59 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 900 | 598 / 302 / 200 | 0.7 | 387.9 | 2.84 | 4.61 | 90% | 74% | 15% | 3.81 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 535 | 595 / 0 / 9 | 0.7 | 384.8 | 1.57 | 2.21 | 72% | 64% | 8% | 3.82 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 64 | 328 / 0 / 1 | 0.7 | 421.4 | 0.78 | 2.01 | 9% | 9% | 0% | 2.98 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 895 | 607 / 288 / 167 | 0.7 | 387.4 | 2.74 | 4.61 | 87% | 77% | 10% | 4.01 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 548 | 584 / 0 / 7 | 0.7 | 381.3 | 1.55 | 2.11 | 74% | 67% | 8% | 3.70 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 68 | 243 / 0 / 0 | 0.7 | 419.6 | 0.58 | 2.01 | 12% | 12% | 0% | 2.95 |
| corner -x+y | 1.20 | 85.6 | 752 | 83 / 135 / 552 | 0.7 | 415.4 | 1.86 | 4.51 | 81% | 64% | 17% | 2.65 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 904 | 605 / 299 / 159 | 0.7 | 387.8 | 2.75 | 4.11 | 87% | 77% | 10% | 3.97 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 539 | 587 / 0 / 12 | 0.7 | 395.3 | 1.52 | 2.31 | 70% | 62% | 8% | 3.85 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 62 | 257 / 0 / 0 | 0.7 | 416.5 | 0.62 | 2.11 | 10% | 10% | 0% | 2.94 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 907 | 602 / 305 / 177 | 0.7 | 372.6 | 2.91 | 4.51 | 87% | 76% | 11% | 4.08 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 544 | 587 / 0 / 11 | 0.7 | 389.3 | 1.54 | 2.21 | 72% | 62% | 10% | 3.76 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 68 | 306 / 0 / 0 | 0.7 | 425.5 | 0.72 | 2.11 | 12% | 12% | 0% | 2.96 |
| corner -x-y | 1.20 | 85.6 | 747 | 97 / 126 / 547 | 0.7 | 427.5 | 1.80 | 3.91 | 79% | 56% | 23% | 2.54 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 901 | 595 / 306 / 185 | 0.7 | 382.5 | 2.84 | 4.71 | 87% | 74% | 13% | 3.99 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 541 | 589 / 0 / 7 | 0.7 | 387.9 | 1.54 | 2.11 | 74% | 64% | 10% | 3.74 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 66 | 267 / 0 / 0 | 0.7 | 424.3 | 0.63 | 1.81 | 12% | 12% | 0% | 3.00 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 901 | 603 / 298 / 176 | 0.7 | 372.2 | 2.90 | 4.61 | 84% | 79% | 5% | 4.25 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 537 | 576 / 0 / 10 | 0.7 | 384.4 | 1.53 | 2.21 | 77% | 67% | 10% | 3.59 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 65 | 280 / 0 / 1 | 0.7 | 423.1 | 0.66 | 2.01 | 9% | 9% | 0% | 3.05 |
| corner +x-y | 1.20 | 85.6 | 743 | 117 / 123 / 521 | 0.7 | 418.2 | 1.82 | 4.01 | 81% | 64% | 17% | 2.65 |

The last agent out (agent 9822, t100 431.3 s): last gangway corner -x-y, exit door -x-y (corner). The gangway that cleared last: corner -x-y at 427.5 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.83 | 425.0 / 413.3 / 382.0 | 411.2 / 397.2 / 311.0 | 476968.5 | 1257975 | 0.257 |
| gangway | 1212 | 1112.9 | 6.83 | 423.8 / 410.5 / 328.3 | 411.2 / 397.2 / 311.0 | 476133.0 | 1115063 | 0.138 |
| walkway | 276 | 257.4 | 3.44 | 273.0 / 137.1 / 0.0 | 181.7 / 58.8 / 0.0 | 0.0 | 27083 | 0.739 |
| avenue | 912 | 858.9 | 2.15 | 315.4 / 0.0 / 0.0 | 249.1 / 0.0 / 0.0 | 0.0 | 83333 | 1.326 |
| exit | 32 | 3.2 | 0.00 | 397.9 / 395.5 / 366.6 | 248.2 / 225.3 / 133.8 | 835.5 | 1532 | 1.318 |
| concourse | 1116 | 1043.8 | 2.64 | 384.8 / 14.5 / 0.0 | 234.2 / 7.2 / 0.0 | 0.0 | 30964 | 1.189 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.60 | 350.3 / 340.5 / 335.3 | 343.9 / 340.0 / 331.1 | 463516.4 | 1378442 | 0.061 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -27.5 | -28.5 | gangway | 1.00 | 6.25 | 331.4 | 329.7 | 270.9 | 1627.1 | 0.025 |
| 2 | -26.5 | 27.5 | gangway | 1.00 | 6.10 | 345.8 | 318.0 | 284.0 | 1556.1 | 0.032 |
| 3 | -27.5 | 27.5 | gangway | 1.00 | 5.68 | 339.0 | 337.4 | 279.9 | 1553.9 | 0.024 |
| 4 | 27.5 | -26.5 | gangway | 1.00 | 5.85 | 347.2 | 338.6 | 277.8 | 1541.2 | 0.031 |
| 5 | 28.5 | -27.5 | gangway | 1.00 | 6.10 | 343.3 | 338.4 | 268.7 | 1533.1 | 0.029 |
| 6 | 28.5 | -26.5 | gangway | 1.00 | 6.07 | 345.4 | 329.2 | 264.5 | 1531.3 | 0.029 |
| 7 | -28.5 | 27.5 | gangway | 1.00 | 5.83 | 338.8 | 332.0 | 277.1 | 1521.0 | 0.025 |
| 8 | -29.5 | -26.5 | gangway | 1.00 | 6.35 | 336.5 | 304.5 | 254.1 | 1519.7 | 0.033 |
| 9 | 27.5 | -28.5 | gangway | 1.00 | 5.84 | 346.0 | 330.9 | 265.3 | 1518.6 | 0.029 |
| 10 | -26.5 | -28.5 | gangway | 1.00 | 5.85 | 339.1 | 325.7 | 261.8 | 1501.9 | 0.028 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -24.5 | -26.5 | seat row | 0.50 | 7.30 | 340.7 | 337.6 | 322.5 | 1125.9 | 0.018 |
| 2 | -26.5 | -24.5 | seat row | 0.50 | 7.13 | 334.4 | 333.2 | 319.4 | 1101.5 | 0.019 |
| 3 | 24.5 | -26.5 | seat row | 0.50 | 7.28 | 337.0 | 334.8 | 317.6 | 1089.6 | 0.021 |
| 4 | 26.5 | -24.5 | seat row | 0.50 | 7.26 | 340.4 | 336.7 | 314.7 | 1086.8 | 0.021 |
| 5 | -26.5 | 24.5 | seat row | 0.50 | 6.84 | 340.9 | 340.0 | 331.1 | 1069.8 | 0.020 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1409; agent-steps of seated agents on another row's clearway: 23269.

## Deposit check

Person-seconds deposited: 2639375.3, of them in excluded cells: 2958.037.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 236338 overlapping pair-steps: p99 0.0044, max 0.0356 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0044 max 0.0356; venue-geometry 5: p99 0.0006 max 0.0006 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00758 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 11 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.35 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 606 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
