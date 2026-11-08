# Experiment `M_load95_s3`

**Task 5.10 stage 4 (AMD 26.10.1): Task 5.8's model (the level spacing on the gangway inclines, --stair-flow off): venue M, 95% load (seed 3)**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 15040 agents on 95% of the 15832 seats (spawnSeatedCrowd, seed 3), buffer N = 16384, 2456 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 879167 evaluations, 39674 switches, 0 forced choices).
Capacity: **within design capacity** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T20:30:00, 62.6 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 972 | 170.0 |
| t90 | 1849 | 323.4 |
| t100 | 2456 | 429.6 |

t_p: the step by which ceil(p x 15040) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 726 | 0 | 39.5 | 367.0 | 23.5 | 26.6 | 127.9-137.8 |
| -x | 5.66 | 728 | 0 | 39.5 | 367.3 | 23.5 | 25.5 | 64.0-74.0 |
| +y | 5.66 | 718 | 0 | 39.7 | 366.1 | 23.3 | 25.5 | 49.8-59.8 |
| -y | 5.66 | 727 | 0 | 39.5 | 367.7 | 23.5 | 25.5 | 45.3-55.3 |
| door +x+y (y wall) 0 | 1.20 | 596 | 1068 | 4.9 | 388.5 | 77.7 | 110.3 | 24.5-34.5 |
| door +x+y (y wall) 1 | 1.20 | 581 | 651 | 4.9 | 398.1 | 73.8 | 110.3 | 76.6-86.6 |
| door +x+y (y wall) 2 | 1.20 | 317 | 168 | 4.9 | 424.7 | 37.7 | 110.3 | 12.4-22.4 |
| door +x+y (x wall) 0 | 1.20 | 589 | 1058 | 4.9 | 370.3 | 80.6 | 110.3 | 28.7-38.7 |
| door +x+y (x wall) 1 | 1.20 | 577 | 650 | 4.9 | 390.6 | 74.8 | 105.3 | 20.6-30.6 |
| door +x+y (x wall) 2 | 1.20 | 269 | 169 | 4.9 | 421.4 | 32.3 | 110.3 | 9.1-19.1 |
| door +x+y (corner) | 1.20 | 111 | 0 | 42.9 | 420.5 | 14.7 | 80.2 | 307.7-317.6 |
| door -x+y (y wall) 0 | 1.20 | 591 | 1050 | 4.9 | 398.1 | 75.1 | 110.3 | 33.1-43.0 |
| door -x+y (y wall) 1 | 1.20 | 576 | 640 | 4.9 | 397.7 | 73.3 | 105.3 | 79.4-89.4 |
| door -x+y (y wall) 2 | 1.20 | 273 | 174 | 4.9 | 429.6 | 32.1 | 105.3 | 7.9-17.8 |
| door -x+y (x wall) 0 | 1.20 | 592 | 1048 | 4.9 | 392.5 | 76.3 | 105.3 | 33.2-43.2 |
| door -x+y (x wall) 1 | 1.20 | 569 | 645 | 4.9 | 395.3 | 72.8 | 110.3 | 24.7-34.6 |
| door -x+y (x wall) 2 | 1.20 | 287 | 175 | 4.9 | 422.4 | 34.4 | 110.3 | 14.3-24.3 |
| door -x+y (corner) | 1.20 | 127 | 0 | 35.3 | 413.8 | 16.8 | 105.3 | 280.0-290.0 |
| door -x-y (y wall) 0 | 1.20 | 605 | 1075 | 4.9 | 379.4 | 80.7 | 105.3 | 30.1-40.1 |
| door -x-y (y wall) 1 | 1.20 | 574 | 654 | 4.9 | 398.3 | 72.9 | 110.3 | 25.0-35.0 |
| door -x-y (y wall) 2 | 1.20 | 264 | 173 | 4.9 | 423.3 | 31.5 | 110.3 | 29.7-39.7 |
| door -x-y (x wall) 0 | 1.20 | 601 | 1071 | 4.9 | 387.9 | 78.4 | 110.3 | 25.5-35.5 |
| door -x-y (x wall) 1 | 1.20 | 590 | 642 | 4.9 | 398.3 | 75.0 | 110.3 | 25.9-35.9 |
| door -x-y (x wall) 2 | 1.20 | 285 | 172 | 4.9 | 417.2 | 34.6 | 110.3 | 14.2-24.1 |
| door -x-y (corner) | 1.20 | 138 | 0 | 32.4 | 424.3 | 17.6 | 85.3 | 376.4-386.4 |
| door +x-y (y wall) 0 | 1.20 | 600 | 1056 | 4.9 | 374.5 | 81.1 | 115.3 | 20.1-30.1 |
| door +x-y (y wall) 1 | 1.20 | 588 | 652 | 4.9 | 394.2 | 75.5 | 105.3 | 51.2-61.2 |
| door +x-y (y wall) 2 | 1.20 | 283 | 170 | 4.9 | 408.8 | 35.0 | 110.3 | 10.1-20.1 |
| door +x-y (x wall) 0 | 1.20 | 598 | 1071 | 4.9 | 383.4 | 79.0 | 110.3 | 20.6-30.6 |
| door +x-y (x wall) 1 | 1.20 | 585 | 639 | 4.9 | 388.3 | 76.3 | 105.3 | 25.0-35.0 |
| door +x-y (x wall) 2 | 1.20 | 288 | 169 | 4.9 | 396.9 | 36.7 | 105.3 | 9.8-19.8 |
| door +x-y (corner) | 1.20 | 87 | 0 | 41.1 | 405.4 | 11.9 | 65.2 | 49.7-59.6 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 726 | 4.8% | 21.4% |
| -x | avenue | 5.66 | 728 | 4.8% | 21.5% |
| +y | avenue | 5.66 | 718 | 4.8% | 21.2% |
| -y | avenue | 5.66 | 727 | 4.8% | 21.5% |
| door +x+y (y wall) 0 | door | 1.20 | 596 | 4.0% | 83.0% |
| door +x+y (y wall) 1 | door | 1.20 | 581 | 3.9% | 80.9% |
| door +x+y (y wall) 2 | door | 1.20 | 317 | 2.1% | 44.1% |
| door +x+y (x wall) 0 | door | 1.20 | 589 | 3.9% | 82.0% |
| door +x+y (x wall) 1 | door | 1.20 | 577 | 3.8% | 80.3% |
| door +x+y (x wall) 2 | door | 1.20 | 269 | 1.8% | 37.5% |
| door +x+y (corner) | door | 1.20 | 111 | 0.7% | 15.5% |
| door -x+y (y wall) 0 | door | 1.20 | 591 | 3.9% | 82.3% |
| door -x+y (y wall) 1 | door | 1.20 | 576 | 3.8% | 80.2% |
| door -x+y (y wall) 2 | door | 1.20 | 273 | 1.8% | 38.0% |
| door -x+y (x wall) 0 | door | 1.20 | 592 | 3.9% | 82.4% |
| door -x+y (x wall) 1 | door | 1.20 | 569 | 3.8% | 79.2% |
| door -x+y (x wall) 2 | door | 1.20 | 287 | 1.9% | 40.0% |
| door -x+y (corner) | door | 1.20 | 127 | 0.8% | 17.7% |
| door -x-y (y wall) 0 | door | 1.20 | 605 | 4.0% | 84.2% |
| door -x-y (y wall) 1 | door | 1.20 | 574 | 3.8% | 79.9% |
| door -x-y (y wall) 2 | door | 1.20 | 264 | 1.8% | 36.8% |
| door -x-y (x wall) 0 | door | 1.20 | 601 | 4.0% | 83.7% |
| door -x-y (x wall) 1 | door | 1.20 | 590 | 3.9% | 82.1% |
| door -x-y (x wall) 2 | door | 1.20 | 285 | 1.9% | 39.7% |
| door -x-y (corner) | door | 1.20 | 138 | 0.9% | 19.2% |
| door +x-y (y wall) 0 | door | 1.20 | 600 | 4.0% | 83.5% |
| door +x-y (y wall) 1 | door | 1.20 | 588 | 3.9% | 81.9% |
| door +x-y (y wall) 2 | door | 1.20 | 283 | 1.9% | 39.4% |
| door +x-y (x wall) 0 | door | 1.20 | 598 | 4.0% | 83.3% |
| door +x-y (x wall) 1 | door | 1.20 | 585 | 3.9% | 81.4% |
| door +x-y (x wall) 2 | door | 1.20 | 288 | 1.9% | 40.1% |
| door +x-y (corner) | door | 1.20 | 87 | 0.6% | 12.1% |
| **doors (28)** | door | 33.60 | 12141 | 80.7% | |
| **avenues (4)** | avenue | 22.64 | 2899 | 19.3% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 429.6 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 44.7%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 887 | 5.9% | 887 | 5.9% |
| straight +x+y (y wing) 1 | straight | yes | 594 | 3.9% | 587 | 3.9% |
| straight +x+y (y wing) 2 | straight | yes | 311 | 2.1% | 311 | 2.1% |
| straight +x+y (x wing) 0 | straight | yes | 887 | 5.9% | 887 | 5.9% |
| straight +x+y (x wing) 1 | straight | yes | 583 | 3.9% | 577 | 3.8% |
| straight +x+y (x wing) 2 | straight | yes | 268 | 1.8% | 268 | 1.8% |
| corner +x+y | corner | yes | 779 | 5.2% | 247 | 1.6% |
| straight -x+y (y wing) 0 | straight | yes | 880 | 5.9% | 880 | 5.9% |
| straight -x+y (y wing) 1 | straight | yes | 582 | 3.9% | 577 | 3.8% |
| straight -x+y (y wing) 2 | straight | yes | 272 | 1.8% | 272 | 1.8% |
| straight -x+y (x wing) 0 | straight | yes | 891 | 5.9% | 891 | 5.9% |
| straight -x+y (x wing) 1 | straight | yes | 581 | 3.9% | 576 | 3.8% |
| straight -x+y (x wing) 2 | straight | yes | 280 | 1.9% | 280 | 1.9% |
| corner -x+y | corner | yes | 758 | 5.0% | 256 | 1.7% |
| straight -x-y (y wing) 0 | straight | yes | 907 | 6.0% | 907 | 6.0% |
| straight -x-y (y wing) 1 | straight | yes | 592 | 3.9% | 587 | 3.9% |
| straight -x-y (y wing) 2 | straight | yes | 251 | 1.7% | 251 | 1.7% |
| straight -x-y (x wing) 0 | straight | yes | 902 | 6.0% | 902 | 6.0% |
| straight -x-y (x wing) 1 | straight | yes | 597 | 4.0% | 592 | 3.9% |
| straight -x-y (x wing) 2 | straight | yes | 286 | 1.9% | 285 | 1.9% |
| corner -x-y | corner | yes | 761 | 5.1% | 263 | 1.7% |
| straight +x-y (y wing) 0 | straight | yes | 905 | 6.0% | 905 | 6.0% |
| straight +x-y (y wing) 1 | straight | yes | 593 | 3.9% | 589 | 3.9% |
| straight +x-y (y wing) 2 | straight | yes | 282 | 1.9% | 282 | 1.9% |
| straight +x-y (x wing) 0 | straight | yes | 894 | 5.9% | 894 | 5.9% |
| straight +x-y (x wing) 1 | straight | yes | 603 | 4.0% | 597 | 4.0% |
| straight +x-y (x wing) 2 | straight | yes | 276 | 1.8% | 276 | 1.8% |
| corner +x-y | corner | yes | 743 | 4.9% | 214 | 1.4% |
| **straight (24)** | | | 14104 | | 14060 | 93.5% |
| **corner (4)** | | | 3041 | | 980 | 6.5% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 726 | 39.5 | 367.0 | 0.28 | 0.32 | 0.0% |
| -x | 728 | 39.5 | 367.3 | 0.28 | 0.31 | 0.0% |
| +y | 718 | 39.7 | 366.1 | 0.28 | 0.31 | 0.0% |
| -y | 727 | 39.5 | 367.7 | 0.28 | 0.31 | 0.0% |
| door +x+y (y wall) 0 | 596 | 4.9 | 388.5 | 0.93 | 1.32 | 76.9% |
| door +x+y (y wall) 1 | 581 | 4.9 | 398.1 | 0.88 | 1.32 | 67.5% |
| door +x+y (y wall) 2 | 317 | 4.9 | 424.7 | 0.45 | 1.32 | 14.0% |
| door +x+y (x wall) 0 | 589 | 4.9 | 370.3 | 0.96 | 1.32 | 78.9% |
| door +x+y (x wall) 1 | 577 | 4.9 | 390.6 | 0.89 | 1.26 | 67.5% |
| door +x+y (x wall) 2 | 269 | 4.9 | 421.4 | 0.39 | 1.32 | 11.6% |
| door +x+y (corner) | 111 | 42.9 | 420.5 | 0.18 | 0.96 | 5.1% |
| door -x+y (y wall) 0 | 591 | 4.9 | 398.1 | 0.90 | 1.32 | 75.0% |
| door -x+y (y wall) 1 | 576 | 4.9 | 397.7 | 0.88 | 1.26 | 62.5% |
| door -x+y (y wall) 2 | 273 | 4.9 | 429.6 | 0.38 | 1.26 | 9.1% |
| door -x+y (x wall) 0 | 592 | 4.9 | 392.5 | 0.91 | 1.26 | 77.5% |
| door -x+y (x wall) 1 | 569 | 4.9 | 395.3 | 0.87 | 1.32 | 70.0% |
| door -x+y (x wall) 2 | 287 | 4.9 | 422.4 | 0.41 | 1.32 | 11.6% |
| door -x+y (corner) | 127 | 35.3 | 413.8 | 0.20 | 1.26 | 5.1% |
| door -x-y (y wall) 0 | 605 | 4.9 | 379.4 | 0.97 | 1.26 | 79.5% |
| door -x-y (y wall) 1 | 574 | 4.9 | 398.3 | 0.87 | 1.32 | 62.5% |
| door -x-y (y wall) 2 | 264 | 4.9 | 423.3 | 0.38 | 1.32 | 11.6% |
| door -x-y (x wall) 0 | 601 | 4.9 | 387.9 | 0.94 | 1.32 | 76.9% |
| door -x-y (x wall) 1 | 590 | 4.9 | 398.3 | 0.90 | 1.32 | 65.0% |
| door -x-y (x wall) 2 | 285 | 4.9 | 417.2 | 0.41 | 1.32 | 7.1% |
| door -x-y (corner) | 138 | 32.4 | 424.3 | 0.21 | 1.02 | 5.0% |
| door +x-y (y wall) 0 | 600 | 4.9 | 374.5 | 0.97 | 1.38 | 78.9% |
| door +x-y (y wall) 1 | 588 | 4.9 | 394.2 | 0.90 | 1.26 | 65.0% |
| door +x-y (y wall) 2 | 283 | 4.9 | 408.8 | 0.42 | 1.32 | 14.6% |
| door +x-y (x wall) 0 | 598 | 4.9 | 383.4 | 0.94 | 1.32 | 76.9% |
| door +x-y (x wall) 1 | 585 | 4.9 | 388.3 | 0.91 | 1.26 | 66.7% |
| door +x-y (x wall) 2 | 288 | 4.9 | 396.9 | 0.44 | 1.26 | 10.0% |
| door +x-y (corner) | 87 | 41.1 | 405.4 | 0.14 | 0.78 | 0.0% |

Mean flow / w J averaged over the doors 0.67, over the avenues 0.28.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 887 | 596 / 291 / 163 | 0.7 | 385.5 | 2.73 | 4.21 | 87% | 74% | 13% | 4.06 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 546 | 587 / 0 / 7 | 0.7 | 395.1 | 1.51 | 2.21 | 75% | 62% | 12% | 3.66 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 69 | 311 / 0 / 0 | 0.7 | 421.7 | 0.74 | 2.01 | 12% | 12% | 0% | 2.91 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 887 | 589 / 298 / 172 | 0.7 | 367.3 | 2.89 | 4.61 | 89% | 78% | 11% | 4.02 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 536 | 577 / 0 / 10 | 0.7 | 387.6 | 1.52 | 2.11 | 77% | 64% | 13% | 3.65 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 69 | 268 / 0 / 0 | 0.7 | 418.4 | 0.64 | 2.01 | 12% | 12% | 0% | 2.91 |
| corner +x+y | 1.20 | 85.6 | 770 | 112 / 135 / 540 | 0.7 | 416.6 | 1.89 | 4.71 | 81% | 52% | 29% | 2.56 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 880 | 590 / 291 / 162 | 0.7 | 387.9 | 2.69 | 4.31 | 90% | 74% | 15% | 3.72 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 535 | 577 / 0 / 9 | 0.7 | 394.8 | 1.49 | 2.01 | 78% | 60% | 18% | 3.51 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 70 | 272 / 0 / 0 | 0.7 | 426.6 | 0.64 | 2.11 | 12% | 9% | 2% | 2.83 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 891 | 592 / 299 / 168 | 0.7 | 389.5 | 2.72 | 4.61 | 88% | 72% | 15% | 3.81 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 541 | 576 / 0 / 8 | 0.7 | 392.3 | 1.49 | 2.21 | 78% | 65% | 12% | 3.53 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 67 | 280 / 0 / 0 | 0.7 | 419.4 | 0.67 | 2.01 | 12% | 12% | 0% | 2.98 |
| corner -x+y | 1.20 | 85.6 | 748 | 128 / 128 / 509 | 0.7 | 420.7 | 1.82 | 3.91 | 81% | 56% | 26% | 2.57 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 907 | 605 / 302 / 169 | 0.7 | 376.4 | 2.86 | 4.61 | 87% | 79% | 8% | 4.13 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 551 | 587 / 0 / 5 | 0.7 | 395.3 | 1.50 | 2.11 | 80% | 62% | 18% | 3.48 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 68 | 251 / 0 / 0 | 0.7 | 420.3 | 0.60 | 2.01 | 12% | 12% | 0% | 2.94 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 902 | 601 / 301 / 160 | 0.7 | 385.0 | 2.76 | 4.51 | 87% | 74% | 13% | 4.05 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 541 | 592 / 0 / 10 | 0.7 | 395.3 | 1.52 | 2.11 | 75% | 65% | 10% | 3.68 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 66 | 285 / 0 / 1 | 0.7 | 414.2 | 0.69 | 2.11 | 10% | 7% | 2% | 2.81 |
| corner -x-y | 1.20 | 85.6 | 752 | 136 / 127 / 505 | 0.7 | 420.5 | 1.83 | 4.31 | 79% | 60% | 19% | 2.65 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 905 | 600 / 305 / 216 | 0.7 | 371.5 | 3.02 | 4.81 | 87% | 76% | 11% | 3.96 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 544 | 589 / 0 / 10 | 0.7 | 391.3 | 1.53 | 2.11 | 78% | 65% | 12% | 3.52 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 63 | 282 / 0 / 0 | 0.7 | 405.8 | 0.70 | 1.91 | 10% | 10% | 0% | 3.01 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 894 | 598 / 296 / 169 | 0.7 | 380.4 | 2.80 | 4.61 | 87% | 74% | 13% | 3.94 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 551 | 597 / 0 / 11 | 0.7 | 385.3 | 1.58 | 2.11 | 74% | 67% | 8% | 3.69 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 68 | 276 / 0 / 0 | 0.7 | 393.9 | 0.70 | 2.01 | 12% | 12% | 0% | 2.92 |
| corner +x-y | 1.20 | 85.6 | 732 | 87 / 127 / 539 | 0.7 | 401.6 | 1.88 | 4.31 | 83% | 61% | 22% | 2.54 |

The last agent out (agent 6019, t100 429.6 s): last gangway straight -x+y (y wing) 2, exit door -x+y (y wall) 2. The gangway that cleared last: straight -x+y (y wing) 2 at 426.6 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.81 | 424.8 / 417.7 / 387.1 | 413.3 / 391.3 / 321.0 | 475066.3 | 1255185 | 0.257 |
| gangway | 1212 | 1112.9 | 6.81 | 424.8 / 410.0 / 335.1 | 413.3 / 391.3 / 321.0 | 474223.3 | 1112408 | 0.138 |
| walkway | 276 | 257.4 | 3.60 | 265.5 / 137.8 / 0.0 | 173.3 / 63.7 / 0.0 | 0.0 | 26887 | 0.745 |
| avenue | 912 | 858.9 | 2.01 | 315.0 / 0.0 / 0.0 | 253.3 / 0.0 / 0.0 | 0.0 | 83280 | 1.326 |
| exit | 32 | 3.2 | 0.00 | 407.7 / 403.5 / 373.8 | 248.0 / 224.6 / 132.2 | 843.0 | 1549 | 1.319 |
| concourse | 1116 | 1043.8 | 2.75 | 390.2 / 14.2 / 0.0 | 237.2 / 10.3 / 0.0 | 0.0 | 31062 | 1.188 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.57 | 356.5 / 345.4 / 336.0 | 348.1 / 345.4 / 332.7 | 460307.1 | 1377016 | 0.062 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -27.5 | 27.5 | gangway | 1.00 | 5.78 | 346.8 | 345.1 | 289.5 | 1639.9 | 0.025 |
| 2 | -26.5 | -28.5 | gangway | 1.00 | 6.08 | 342.8 | 331.8 | 274.1 | 1614.3 | 0.026 |
| 3 | -27.5 | -28.5 | gangway | 1.00 | 5.99 | 346.0 | 341.2 | 269.7 | 1566.7 | 0.026 |
| 4 | -28.5 | 26.5 | gangway | 1.00 | 5.90 | 345.1 | 342.3 | 271.1 | 1540.7 | 0.026 |
| 5 | 26.5 | 27.5 | gangway | 1.00 | 6.03 | 359.3 | 347.7 | 271.3 | 1537.9 | 0.030 |
| 6 | -26.5 | 28.5 | gangway | 1.00 | 6.01 | 354.2 | 341.6 | 264.3 | 1528.2 | 0.031 |
| 7 | -29.5 | -26.5 | gangway | 1.00 | 6.18 | 338.1 | 309.9 | 250.3 | 1512.4 | 0.039 |
| 8 | -28.5 | 27.5 | gangway | 1.00 | 5.86 | 345.3 | 342.1 | 270.4 | 1511.7 | 0.027 |
| 9 | -26.5 | 27.5 | gangway | 1.00 | 5.77 | 354.0 | 344.6 | 267.1 | 1505.0 | 0.030 |
| 10 | -26.5 | -29.5 | gangway | 1.00 | 6.01 | 338.3 | 310.1 | 256.9 | 1501.0 | 0.029 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -26.5 | -24.5 | seat row | 0.50 | 7.11 | 347.5 | 343.3 | 332.7 | 1135.6 | 0.018 |
| 2 | -26.5 | 24.5 | seat row | 0.50 | 7.15 | 343.0 | 342.6 | 332.7 | 1134.3 | 0.019 |
| 3 | 26.5 | -24.5 | seat row | 0.50 | 7.32 | 333.9 | 333.4 | 323.8 | 1132.2 | 0.020 |
| 4 | -24.5 | 26.5 | seat row | 0.50 | 7.21 | 346.5 | 342.6 | 326.6 | 1128.5 | 0.019 |
| 5 | 24.5 | 26.5 | seat row | 0.50 | 7.28 | 348.1 | 345.4 | 328.3 | 1119.2 | 0.022 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1380; agent-steps of seated agents on another row's clearway: 23312.

## Deposit check

Person-seconds deposited: 2635164.7, of them in excluded cells: 2963.458.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 226790 overlapping pair-steps: p99 0.0044, max 0.0403 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0044 max 0.0403; venue-geometry 2: p99 0.0004 max 0.0004 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00757 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 11 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.29 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 570 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
