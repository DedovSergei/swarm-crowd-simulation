# Experiment `M_load95_s1`

**Task 5.8 stage 2: venue M, 95% load (seed 1), default model**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 15040 agents on 95% of the 15832 seats (spawnSeatedCrowd, seed 1), buffer N = 16384, 2511 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 878788 evaluations, 39831 switches, 0 forced choices).
Capacity: **within design capacity** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `cd8e0bbf3411846ca7aa6719887d122a142a7ca1`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-15T16:26:39, 60.4 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 971 | 169.8 |
| t90 | 1845 | 322.7 |
| t100 | 2511 | 439.2 |

t_p: the step by which ceil(p x 15040) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 725 | 0 | 39.7 | 368.5 | 23.4 | 25.5 | 56.7-66.6 |
| -x | 5.66 | 721 | 0 | 39.5 | 367.5 | 23.3 | 25.5 | 55.3-65.2 |
| +y | 5.66 | 722 | 0 | 39.7 | 367.1 | 23.4 | 25.5 | 45.8-55.8 |
| -y | 5.66 | 729 | 0 | 39.7 | 366.8 | 23.6 | 25.5 | 64.0-74.0 |
| door +x+y (y wall) 0 | 1.20 | 604 | 1057 | 4.9 | 387.4 | 78.9 | 105.3 | 28.5-38.5 |
| door +x+y (y wall) 1 | 1.20 | 575 | 649 | 4.9 | 393.2 | 74.0 | 105.3 | 79.9-89.9 |
| door +x+y (y wall) 2 | 1.20 | 266 | 167 | 4.9 | 437.6 | 30.7 | 105.3 | 9.1-19.1 |
| door +x+y (x wall) 0 | 1.20 | 598 | 1061 | 4.9 | 397.4 | 76.1 | 110.3 | 24.8-34.8 |
| door +x+y (x wall) 1 | 1.20 | 575 | 649 | 4.9 | 391.1 | 74.4 | 105.3 | 25.0-35.0 |
| door +x+y (x wall) 2 | 1.20 | 329 | 170 | 4.9 | 434.5 | 38.3 | 105.3 | 13.3-23.3 |
| door +x+y (corner) | 1.20 | 83 | 0 | 65.2 | 439.2 | 11.1 | 75.2 | 69.1-79.1 |
| door -x+y (y wall) 0 | 1.20 | 596 | 1061 | 4.9 | 387.8 | 77.8 | 105.3 | 5.8-15.7 |
| door -x+y (y wall) 1 | 1.20 | 573 | 653 | 4.9 | 390.4 | 74.3 | 105.3 | 47.2-57.2 |
| door -x+y (y wall) 2 | 1.20 | 293 | 168 | 4.9 | 418.0 | 35.4 | 110.3 | 14.0-24.0 |
| door -x+y (x wall) 0 | 1.20 | 606 | 1068 | 4.9 | 387.2 | 79.2 | 105.3 | 7.0-17.0 |
| door -x+y (x wall) 1 | 1.20 | 579 | 643 | 4.9 | 389.7 | 75.2 | 110.3 | 9.1-19.1 |
| door -x+y (x wall) 2 | 1.20 | 274 | 169 | 4.9 | 421.0 | 32.9 | 105.3 | 10.5-20.5 |
| door -x+y (corner) | 1.20 | 120 | 0 | 43.2 | 416.1 | 16.1 | 80.2 | 59.1-69.1 |
| door -x-y (y wall) 0 | 1.20 | 604 | 1058 | 4.9 | 383.9 | 79.6 | 105.3 | 23.1-33.1 |
| door -x-y (y wall) 1 | 1.20 | 586 | 656 | 4.9 | 393.5 | 75.4 | 110.3 | 27.6-37.6 |
| door -x-y (y wall) 2 | 1.20 | 286 | 168 | 4.9 | 409.1 | 35.4 | 105.3 | 12.8-22.7 |
| door -x-y (x wall) 0 | 1.20 | 603 | 1070 | 4.9 | 379.4 | 80.5 | 105.3 | 25.2-35.2 |
| door -x-y (x wall) 1 | 1.20 | 567 | 645 | 4.9 | 394.2 | 72.8 | 110.3 | 12.4-22.4 |
| door -x-y (x wall) 2 | 1.20 | 280 | 174 | 4.9 | 408.1 | 34.7 | 110.3 | 29.6-39.5 |
| door -x-y (corner) | 1.20 | 121 | 0 | 46.0 | 411.9 | 16.5 | 70.2 | 232.5-242.4 |
| door +x-y (y wall) 0 | 1.20 | 595 | 1063 | 4.9 | 376.4 | 80.0 | 110.3 | 39.5-49.5 |
| door +x-y (y wall) 1 | 1.20 | 595 | 642 | 4.9 | 391.8 | 76.9 | 115.3 | 26.9-36.9 |
| door +x-y (y wall) 2 | 1.20 | 273 | 169 | 5.2 | 428.3 | 32.2 | 105.3 | 42.2-52.1 |
| door +x-y (x wall) 0 | 1.20 | 590 | 1062 | 4.9 | 370.1 | 80.7 | 105.3 | 173.9-183.8 |
| door +x-y (x wall) 1 | 1.20 | 587 | 649 | 4.9 | 385.1 | 77.2 | 105.3 | 24.3-34.3 |
| door +x-y (x wall) 2 | 1.20 | 293 | 169 | 4.9 | 426.6 | 34.7 | 105.3 | 12.8-22.7 |
| door +x-y (corner) | 1.20 | 92 | 0 | 38.8 | 427.1 | 11.8 | 65.2 | 63.0-72.9 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 725 | 4.8% | 20.9% |
| -x | avenue | 5.66 | 721 | 4.8% | 20.8% |
| +y | avenue | 5.66 | 722 | 4.8% | 20.8% |
| -y | avenue | 5.66 | 729 | 4.8% | 21.0% |
| door +x+y (y wall) 0 | door | 1.20 | 604 | 4.0% | 82.3% |
| door +x+y (y wall) 1 | door | 1.20 | 575 | 3.8% | 78.3% |
| door +x+y (y wall) 2 | door | 1.20 | 266 | 1.8% | 36.2% |
| door +x+y (x wall) 0 | door | 1.20 | 598 | 4.0% | 81.4% |
| door +x+y (x wall) 1 | door | 1.20 | 575 | 3.8% | 78.3% |
| door +x+y (x wall) 2 | door | 1.20 | 329 | 2.2% | 44.8% |
| door +x+y (corner) | door | 1.20 | 83 | 0.6% | 11.3% |
| door -x+y (y wall) 0 | door | 1.20 | 596 | 4.0% | 81.2% |
| door -x+y (y wall) 1 | door | 1.20 | 573 | 3.8% | 78.0% |
| door -x+y (y wall) 2 | door | 1.20 | 293 | 1.9% | 39.9% |
| door -x+y (x wall) 0 | door | 1.20 | 606 | 4.0% | 82.5% |
| door -x+y (x wall) 1 | door | 1.20 | 579 | 3.8% | 78.8% |
| door -x+y (x wall) 2 | door | 1.20 | 274 | 1.8% | 37.3% |
| door -x+y (corner) | door | 1.20 | 120 | 0.8% | 16.3% |
| door -x-y (y wall) 0 | door | 1.20 | 604 | 4.0% | 82.3% |
| door -x-y (y wall) 1 | door | 1.20 | 586 | 3.9% | 79.8% |
| door -x-y (y wall) 2 | door | 1.20 | 286 | 1.9% | 38.9% |
| door -x-y (x wall) 0 | door | 1.20 | 603 | 4.0% | 82.1% |
| door -x-y (x wall) 1 | door | 1.20 | 567 | 3.8% | 77.2% |
| door -x-y (x wall) 2 | door | 1.20 | 280 | 1.9% | 38.1% |
| door -x-y (corner) | door | 1.20 | 121 | 0.8% | 16.5% |
| door +x-y (y wall) 0 | door | 1.20 | 595 | 4.0% | 81.0% |
| door +x-y (y wall) 1 | door | 1.20 | 595 | 4.0% | 81.0% |
| door +x-y (y wall) 2 | door | 1.20 | 273 | 1.8% | 37.2% |
| door +x-y (x wall) 0 | door | 1.20 | 590 | 3.9% | 80.3% |
| door +x-y (x wall) 1 | door | 1.20 | 587 | 3.9% | 79.9% |
| door +x-y (x wall) 2 | door | 1.20 | 293 | 1.9% | 39.9% |
| door +x-y (corner) | door | 1.20 | 92 | 0.6% | 12.5% |
| **doors (28)** | door | 33.60 | 12143 | 80.7% | |
| **avenues (4)** | avenue | 22.64 | 2897 | 19.3% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 439.2 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 43.7%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 905 | 6.0% | 905 | 6.0% |
| straight +x+y (y wing) 1 | straight | yes | 587 | 3.9% | 576 | 3.8% |
| straight +x+y (y wing) 2 | straight | yes | 265 | 1.8% | 265 | 1.8% |
| straight +x+y (x wing) 0 | straight | yes | 890 | 5.9% | 890 | 5.9% |
| straight +x+y (x wing) 1 | straight | yes | 593 | 3.9% | 587 | 3.9% |
| straight +x+y (x wing) 2 | straight | yes | 318 | 2.1% | 318 | 2.1% |
| corner +x+y | corner | yes | 757 | 5.0% | 212 | 1.4% |
| straight -x+y (y wing) 0 | straight | yes | 901 | 6.0% | 901 | 6.0% |
| straight -x+y (y wing) 1 | straight | yes | 588 | 3.9% | 579 | 3.8% |
| straight -x+y (y wing) 2 | straight | yes | 287 | 1.9% | 287 | 1.9% |
| straight -x+y (x wing) 0 | straight | yes | 899 | 6.0% | 899 | 6.0% |
| straight -x+y (x wing) 1 | straight | yes | 586 | 3.9% | 579 | 3.8% |
| straight -x+y (x wing) 2 | straight | yes | 273 | 1.8% | 273 | 1.8% |
| corner -x+y | corner | yes | 770 | 5.1% | 244 | 1.6% |
| straight -x-y (y wing) 0 | straight | yes | 900 | 6.0% | 900 | 6.0% |
| straight -x-y (y wing) 1 | straight | yes | 593 | 3.9% | 588 | 3.9% |
| straight -x-y (y wing) 2 | straight | yes | 284 | 1.9% | 284 | 1.9% |
| straight -x-y (x wing) 0 | straight | yes | 903 | 6.0% | 903 | 6.0% |
| straight -x-y (x wing) 1 | straight | yes | 596 | 4.0% | 587 | 3.9% |
| straight -x-y (x wing) 2 | straight | yes | 260 | 1.7% | 260 | 1.7% |
| corner -x-y | corner | yes | 763 | 5.1% | 249 | 1.7% |
| straight +x-y (y wing) 0 | straight | yes | 900 | 6.0% | 900 | 6.0% |
| straight +x-y (y wing) 1 | straight | yes | 599 | 4.0% | 595 | 4.0% |
| straight +x-y (y wing) 2 | straight | yes | 273 | 1.8% | 273 | 1.8% |
| straight +x-y (x wing) 0 | straight | yes | 892 | 5.9% | 892 | 5.9% |
| straight +x-y (x wing) 1 | straight | yes | 596 | 4.0% | 590 | 3.9% |
| straight +x-y (x wing) 2 | straight | yes | 290 | 1.9% | 290 | 1.9% |
| corner +x-y | corner | yes | 757 | 5.0% | 214 | 1.4% |
| **straight (24)** | | | 14178 | | 14121 | 93.9% |
| **corner (4)** | | | 3047 | | 919 | 6.1% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 725 | 39.7 | 368.5 | 0.28 | 0.31 | 0.0% |
| -x | 721 | 39.5 | 367.5 | 0.28 | 0.31 | 0.0% |
| +y | 722 | 39.7 | 367.1 | 0.28 | 0.31 | 0.0% |
| -y | 729 | 39.7 | 366.8 | 0.28 | 0.31 | 0.0% |
| door +x+y (y wall) 0 | 604 | 4.9 | 387.4 | 0.94 | 1.26 | 79.5% |
| door +x+y (y wall) 1 | 575 | 4.9 | 393.2 | 0.89 | 1.26 | 67.5% |
| door +x+y (y wall) 2 | 266 | 4.9 | 437.6 | 0.37 | 1.26 | 13.6% |
| door +x+y (x wall) 0 | 598 | 4.9 | 397.4 | 0.91 | 1.32 | 77.5% |
| door +x+y (x wall) 1 | 575 | 4.9 | 391.1 | 0.89 | 1.26 | 62.5% |
| door +x+y (x wall) 2 | 329 | 4.9 | 434.5 | 0.46 | 1.26 | 15.9% |
| door +x+y (corner) | 83 | 65.2 | 439.2 | 0.13 | 0.90 | 2.6% |
| door -x+y (y wall) 0 | 596 | 4.9 | 387.8 | 0.93 | 1.26 | 76.9% |
| door -x+y (y wall) 1 | 573 | 4.9 | 390.4 | 0.89 | 1.26 | 67.5% |
| door -x+y (y wall) 2 | 293 | 4.9 | 418.0 | 0.42 | 1.32 | 11.9% |
| door -x+y (x wall) 0 | 606 | 4.9 | 387.2 | 0.95 | 1.26 | 76.9% |
| door -x+y (x wall) 1 | 579 | 4.9 | 389.7 | 0.90 | 1.32 | 65.0% |
| door -x+y (x wall) 2 | 274 | 4.9 | 421.0 | 0.39 | 1.26 | 11.6% |
| door -x+y (corner) | 120 | 43.2 | 416.1 | 0.19 | 0.96 | 5.3% |
| door -x-y (y wall) 0 | 604 | 4.9 | 383.9 | 0.95 | 1.26 | 76.9% |
| door -x-y (y wall) 1 | 586 | 4.9 | 393.5 | 0.90 | 1.32 | 67.5% |
| door -x-y (y wall) 2 | 286 | 4.9 | 409.1 | 0.42 | 1.26 | 9.5% |
| door -x-y (x wall) 0 | 603 | 4.9 | 379.4 | 0.96 | 1.26 | 76.9% |
| door -x-y (x wall) 1 | 567 | 4.9 | 394.2 | 0.87 | 1.32 | 65.0% |
| door -x-y (x wall) 2 | 280 | 4.9 | 408.1 | 0.42 | 1.32 | 12.2% |
| door -x-y (corner) | 121 | 46.0 | 411.9 | 0.20 | 0.84 | 0.0% |
| door +x-y (y wall) 0 | 595 | 4.9 | 376.4 | 0.96 | 1.32 | 78.9% |
| door +x-y (y wall) 1 | 595 | 4.9 | 391.8 | 0.92 | 1.38 | 67.5% |
| door +x-y (y wall) 2 | 273 | 5.2 | 428.3 | 0.39 | 1.26 | 14.0% |
| door +x-y (x wall) 0 | 590 | 4.9 | 370.1 | 0.97 | 1.26 | 78.9% |
| door +x-y (x wall) 1 | 587 | 4.9 | 385.1 | 0.92 | 1.26 | 69.2% |
| door +x-y (x wall) 2 | 293 | 4.9 | 426.6 | 0.42 | 1.26 | 9.3% |
| door +x-y (corner) | 92 | 38.8 | 427.1 | 0.14 | 0.78 | 0.0% |

Mean flow / w J averaged over the doors 0.67, over the avenues 0.28.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 905 | 604 / 301 / 174 | 0.7 | 384.4 | 2.81 | 4.61 | 87% | 77% | 10% | 3.98 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 532 | 576 / 0 / 14 | 0.7 | 390.2 | 1.51 | 2.11 | 70% | 62% | 8% | 3.71 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 64 | 265 / 0 / 0 | 0.7 | 434.6 | 0.61 | 2.01 | 9% | 9% | 0% | 3.01 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 890 | 597 / 293 / 179 | 0.7 | 375.3 | 2.85 | 4.21 | 87% | 76% | 11% | 4.04 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 548 | 587 / 0 / 7 | 0.7 | 388.1 | 1.53 | 2.11 | 79% | 67% | 13% | 3.73 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 66 | 318 / 0 / 0 | 0.7 | 431.5 | 0.74 | 2.01 | 9% | 9% | 0% | 3.01 |
| corner +x+y | 1.20 | 85.6 | 748 | 83 / 129 / 557 | 0.7 | 435.3 | 1.77 | 4.31 | 75% | 52% | 23% | 2.59 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 901 | 596 / 305 / 245 | 0.7 | 384.8 | 2.98 | 5.02 | 87% | 74% | 13% | 3.83 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 533 | 579 / 0 / 10 | 0.7 | 387.4 | 1.52 | 2.11 | 77% | 64% | 13% | 3.62 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 64 | 287 / 0 / 0 | 0.7 | 415.1 | 0.69 | 2.01 | 10% | 10% | 0% | 3.04 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 899 | 606 / 293 / 162 | 0.7 | 384.3 | 2.76 | 4.71 | 87% | 77% | 10% | 4.00 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 539 | 579 / 0 / 12 | 0.7 | 386.7 | 1.53 | 2.11 | 74% | 62% | 13% | 3.64 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 66 | 273 / 0 / 0 | 0.7 | 418.0 | 0.65 | 2.01 | 10% | 10% | 0% | 3.17 |
| corner -x+y | 1.20 | 85.6 | 760 | 121 / 123 / 538 | 0.7 | 412.3 | 1.90 | 4.51 | 81% | 57% | 24% | 2.59 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 900 | 604 / 296 / 167 | 0.7 | 380.9 | 2.80 | 4.61 | 85% | 77% | 8% | 4.06 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 532 | 588 / 0 / 7 | 0.7 | 390.6 | 1.53 | 2.11 | 72% | 60% | 12% | 3.64 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 62 | 284 / 0 / 0 | 0.7 | 406.1 | 0.70 | 2.01 | 10% | 10% | 0% | 2.96 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 903 | 603 / 300 / 170 | 0.7 | 376.4 | 2.85 | 4.41 | 89% | 76% | 13% | 3.93 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 554 | 587 / 0 / 9 | 0.7 | 391.3 | 1.53 | 2.11 | 75% | 65% | 10% | 3.80 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 67 | 260 / 0 / 0 | 0.7 | 405.1 | 0.64 | 1.91 | 10% | 10% | 0% | 3.16 |
| corner -x-y | 1.20 | 85.6 | 753 | 121 / 129 / 520 | 0.7 | 408.2 | 1.89 | 4.11 | 83% | 59% | 24% | 2.56 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 900 | 595 / 305 / 206 | 0.7 | 373.4 | 2.97 | 4.91 | 87% | 76% | 11% | 4.01 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 542 | 595 / 0 / 9 | 0.7 | 388.8 | 1.56 | 2.11 | 79% | 64% | 15% | 3.51 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 65 | 273 / 0 / 0 | 0.7 | 425.4 | 0.64 | 1.91 | 12% | 12% | 0% | 3.11 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 892 | 590 / 302 / 184 | 0.7 | 367.1 | 2.94 | 4.61 | 86% | 78% | 8% | 4.13 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 544 | 590 / 0 / 11 | 0.7 | 382.2 | 1.57 | 2.31 | 79% | 64% | 15% | 3.55 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 66 | 290 / 0 / 0 | 0.7 | 423.6 | 0.69 | 2.01 | 9% | 9% | 0% | 3.05 |
| corner +x-y | 1.20 | 85.6 | 745 | 92 / 122 / 551 | 0.7 | 423.3 | 1.81 | 4.11 | 77% | 56% | 21% | 2.64 |

The last agent out (agent 2301, t100 439.2 s): last gangway corner +x+y, exit door +x+y (corner). The gangway that cleared last: corner +x+y at 435.3 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.85 | 431.3 / 422.4 / 383.9 | 421.9 / 402.5 / 307.3 | 474328.8 | 1254682 | 0.257 |
| gangway | 1212 | 1112.9 | 6.85 | 429.9 / 418.0 / 325.5 | 421.9 / 402.5 / 307.3 | 473489.8 | 1111990 | 0.138 |
| walkway | 276 | 257.4 | 3.86 | 265.0 / 146.9 / 0.0 | 162.8 / 60.7 / 0.0 | 0.0 | 27000 | 0.741 |
| avenue | 912 | 858.9 | 1.86 | 312.0 / 0.0 / 0.0 | 246.3 / 0.0 / 0.0 | 0.0 | 83221 | 1.326 |
| exit | 32 | 3.2 | 0.00 | 401.1 / 397.9 / 367.0 | 249.9 / 228.6 / 135.2 | 838.9 | 1530 | 1.318 |
| concourse | 1116 | 1043.8 | 2.44 | 383.7 / 3.1 / 0.0 | 241.7 / 1.9 / 0.0 | 0.0 | 30941 | 1.192 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.55 | 347.9 / 336.9 / 322.9 | 340.2 / 336.9 / 319.7 | 461033.3 | 1376422 | 0.062 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -29.5 | -26.5 | gangway | 1.00 | 6.17 | 339.8 | 306.8 | 286.7 | 1693.9 | 0.029 |
| 2 | -27.5 | -28.5 | gangway | 1.00 | 6.05 | 328.5 | 325.3 | 281.9 | 1613.5 | 0.027 |
| 3 | -28.5 | -26.5 | gangway | 1.00 | 5.98 | 346.5 | 332.3 | 275.3 | 1582.5 | 0.026 |
| 4 | 26.5 | -29.5 | gangway | 1.00 | 6.42 | 350.7 | 313.4 | 263.1 | 1581.1 | 0.037 |
| 5 | 28.5 | -26.5 | gangway | 1.00 | 6.00 | 341.2 | 327.8 | 271.8 | 1574.5 | 0.030 |
| 6 | 29.5 | -26.5 | gangway | 1.00 | 6.27 | 337.6 | 309.6 | 271.5 | 1573.6 | 0.036 |
| 7 | -26.5 | 29.5 | gangway | 1.00 | 6.18 | 329.2 | 305.7 | 264.5 | 1554.0 | 0.036 |
| 8 | 29.5 | 26.5 | gangway | 1.00 | 5.85 | 343.5 | 319.6 | 272.7 | 1513.3 | 0.031 |
| 9 | -27.5 | -27.5 | gangway | 1.00 | 5.80 | 338.1 | 336.9 | 264.6 | 1487.5 | 0.026 |
| 10 | 27.5 | 27.5 | gangway | 1.00 | 5.86 | 345.8 | 340.0 | 262.0 | 1453.0 | 0.031 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 26.5 | 24.5 | seat row | 0.50 | 7.30 | 326.9 | 324.1 | 317.5 | 1112.5 | 0.020 |
| 2 | -26.5 | -24.5 | seat row | 0.50 | 7.23 | 332.1 | 330.7 | 319.7 | 1104.6 | 0.019 |
| 3 | 26.5 | -24.5 | seat row | 0.50 | 7.29 | 332.1 | 330.9 | 316.4 | 1103.2 | 0.021 |
| 4 | -24.5 | 26.5 | seat row | 0.50 | 7.25 | 334.8 | 329.2 | 316.9 | 1091.1 | 0.021 |
| 5 | 24.5 | 26.5 | seat row | 0.50 | 7.24 | 334.1 | 330.4 | 313.6 | 1072.0 | 0.021 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1494; agent-steps of seated agents on another row's clearway: 27881.

## Deposit check

Person-seconds deposited: 2634070.0, of them in excluded cells: 2966.491.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 225000 overlapping pair-steps: p99 0.0032, max 0.0450 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0032 max 0.0450; venue-geometry 1: p99 0.0005 max 0.0005 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00756 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 13 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.42 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 609 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
