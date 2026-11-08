# Experiment `M_load95_s3`

**Task 5.8 stage 2: venue M, 95% load (seed 3), default model**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 15040 agents on 95% of the 15832 seats (spawnSeatedCrowd, seed 3), buffer N = 16384, 2472 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 877224 evaluations, 39851 switches, 0 forced choices).
Capacity: **within design capacity** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `cd8e0bbf3411846ca7aa6719887d122a142a7ca1`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-15T16:29:07, 59.0 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 971 | 169.8 |
| t90 | 1847 | 323.1 |
| t100 | 2472 | 432.4 |

t_p: the step by which ceil(p x 15040) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 716 | 0 | 39.5 | 363.8 | 23.4 | 25.5 | 50.7-60.7 |
| -x | 5.66 | 724 | 0 | 39.7 | 365.9 | 23.5 | 26.6 | 118.6-128.6 |
| +y | 5.66 | 722 | 0 | 39.7 | 367.8 | 23.3 | 25.5 | 45.7-55.6 |
| -y | 5.66 | 734 | 0 | 39.7 | 371.3 | 23.5 | 25.5 | 46.0-56.0 |
| door +x+y (y wall) 0 | 1.20 | 610 | 1068 | 4.9 | 384.6 | 80.3 | 110.3 | 12.4-22.4 |
| door +x+y (y wall) 1 | 1.20 | 571 | 651 | 4.9 | 397.9 | 72.6 | 105.3 | 25.4-35.3 |
| door +x+y (y wall) 2 | 1.20 | 278 | 168 | 4.9 | 414.9 | 33.9 | 105.3 | 15.6-25.5 |
| door +x+y (x wall) 0 | 1.20 | 593 | 1058 | 4.9 | 383.2 | 78.3 | 105.3 | 20.1-30.1 |
| door +x+y (x wall) 1 | 1.20 | 577 | 650 | 4.9 | 397.0 | 73.5 | 110.3 | 12.1-22.0 |
| door +x+y (x wall) 2 | 1.20 | 278 | 169 | 4.9 | 407.2 | 34.5 | 110.3 | 12.9-22.9 |
| door +x+y (corner) | 1.20 | 132 | 0 | 43.6 | 401.9 | 18.4 | 110.3 | 272.9-282.8 |
| door -x+y (y wall) 0 | 1.20 | 589 | 1050 | 4.9 | 365.6 | 81.6 | 110.3 | 14.2-24.1 |
| door -x+y (y wall) 1 | 1.20 | 566 | 640 | 4.9 | 396.7 | 72.2 | 110.3 | 21.3-31.3 |
| door -x+y (y wall) 2 | 1.20 | 303 | 174 | 4.9 | 429.6 | 35.7 | 110.3 | 21.0-31.0 |
| door -x+y (x wall) 0 | 1.20 | 599 | 1048 | 4.9 | 368.9 | 82.2 | 115.3 | 12.4-22.4 |
| door -x+y (x wall) 1 | 1.20 | 566 | 645 | 4.9 | 391.1 | 73.2 | 110.3 | 158.5-168.4 |
| door -x+y (x wall) 2 | 1.20 | 276 | 175 | 4.9 | 421.5 | 33.1 | 105.3 | 13.3-23.3 |
| door -x+y (corner) | 1.20 | 118 | 0 | 37.3 | 432.4 | 14.9 | 65.2 | 57.9-67.9 |
| door -x-y (y wall) 0 | 1.20 | 593 | 1075 | 4.9 | 389.9 | 77.0 | 100.3 | 4.7-14.7 |
| door -x-y (y wall) 1 | 1.20 | 569 | 654 | 4.9 | 408.4 | 70.5 | 110.3 | 27.5-37.4 |
| door -x-y (y wall) 2 | 1.20 | 332 | 173 | 4.9 | 429.2 | 39.1 | 110.3 | 26.2-36.2 |
| door -x-y (x wall) 0 | 1.20 | 610 | 1071 | 4.9 | 385.7 | 80.1 | 110.3 | 20.6-30.6 |
| door -x-y (x wall) 1 | 1.20 | 587 | 642 | 4.9 | 397.7 | 74.7 | 110.3 | 25.9-35.9 |
| door -x-y (x wall) 2 | 1.20 | 256 | 172 | 4.9 | 420.0 | 30.8 | 110.3 | 28.7-38.7 |
| door -x-y (corner) | 1.20 | 107 | 0 | 34.1 | 423.6 | 13.7 | 80.2 | 379.7-389.7 |
| door +x-y (y wall) 0 | 1.20 | 593 | 1056 | 4.9 | 380.1 | 79.0 | 105.3 | 47.4-57.4 |
| door +x-y (y wall) 1 | 1.20 | 576 | 652 | 4.9 | 391.6 | 74.4 | 110.3 | 12.2-22.2 |
| door +x-y (y wall) 2 | 1.20 | 284 | 170 | 4.9 | 402.6 | 35.7 | 105.3 | 10.0-19.9 |
| door +x-y (x wall) 0 | 1.20 | 596 | 1071 | 4.9 | 377.4 | 80.0 | 105.3 | 17.5-27.5 |
| door +x-y (x wall) 1 | 1.20 | 564 | 639 | 4.9 | 392.7 | 72.7 | 105.3 | 86.1-96.0 |
| door +x-y (x wall) 2 | 1.20 | 264 | 169 | 4.9 | 399.7 | 33.4 | 110.3 | 25.0-35.0 |
| door +x-y (corner) | 1.20 | 157 | 0 | 45.7 | 398.1 | 22.3 | 110.3 | 226.7-236.6 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 716 | 4.8% | 21.0% |
| -x | avenue | 5.66 | 724 | 4.8% | 21.2% |
| +y | avenue | 5.66 | 722 | 4.8% | 21.2% |
| -y | avenue | 5.66 | 734 | 4.9% | 21.5% |
| door +x+y (y wall) 0 | door | 1.20 | 610 | 4.1% | 84.4% |
| door +x+y (y wall) 1 | door | 1.20 | 571 | 3.8% | 79.0% |
| door +x+y (y wall) 2 | door | 1.20 | 278 | 1.8% | 38.5% |
| door +x+y (x wall) 0 | door | 1.20 | 593 | 3.9% | 82.0% |
| door +x+y (x wall) 1 | door | 1.20 | 577 | 3.8% | 79.8% |
| door +x+y (x wall) 2 | door | 1.20 | 278 | 1.8% | 38.5% |
| door +x+y (corner) | door | 1.20 | 132 | 0.9% | 18.3% |
| door -x+y (y wall) 0 | door | 1.20 | 589 | 3.9% | 81.5% |
| door -x+y (y wall) 1 | door | 1.20 | 566 | 3.8% | 78.3% |
| door -x+y (y wall) 2 | door | 1.20 | 303 | 2.0% | 41.9% |
| door -x+y (x wall) 0 | door | 1.20 | 599 | 4.0% | 82.9% |
| door -x+y (x wall) 1 | door | 1.20 | 566 | 3.8% | 78.3% |
| door -x+y (x wall) 2 | door | 1.20 | 276 | 1.8% | 38.2% |
| door -x+y (corner) | door | 1.20 | 118 | 0.8% | 16.3% |
| door -x-y (y wall) 0 | door | 1.20 | 593 | 3.9% | 82.0% |
| door -x-y (y wall) 1 | door | 1.20 | 569 | 3.8% | 78.7% |
| door -x-y (y wall) 2 | door | 1.20 | 332 | 2.2% | 45.9% |
| door -x-y (x wall) 0 | door | 1.20 | 610 | 4.1% | 84.4% |
| door -x-y (x wall) 1 | door | 1.20 | 587 | 3.9% | 81.2% |
| door -x-y (x wall) 2 | door | 1.20 | 256 | 1.7% | 35.4% |
| door -x-y (corner) | door | 1.20 | 107 | 0.7% | 14.8% |
| door +x-y (y wall) 0 | door | 1.20 | 593 | 3.9% | 82.0% |
| door +x-y (y wall) 1 | door | 1.20 | 576 | 3.8% | 79.7% |
| door +x-y (y wall) 2 | door | 1.20 | 284 | 1.9% | 39.3% |
| door +x-y (x wall) 0 | door | 1.20 | 596 | 4.0% | 82.4% |
| door +x-y (x wall) 1 | door | 1.20 | 564 | 3.8% | 78.0% |
| door +x-y (x wall) 2 | door | 1.20 | 264 | 1.8% | 36.5% |
| door +x-y (corner) | door | 1.20 | 157 | 1.0% | 21.7% |
| **doors (28)** | door | 33.60 | 12144 | 80.7% | |
| **avenues (4)** | avenue | 22.64 | 2896 | 19.3% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 432.4 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 44.4%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 899 | 6.0% | 899 | 6.0% |
| straight +x+y (y wing) 1 | straight | yes | 576 | 3.8% | 572 | 3.8% |
| straight +x+y (y wing) 2 | straight | yes | 277 | 1.8% | 277 | 1.8% |
| straight +x+y (x wing) 0 | straight | yes | 892 | 5.9% | 892 | 5.9% |
| straight +x+y (x wing) 1 | straight | yes | 586 | 3.9% | 577 | 3.8% |
| straight +x+y (x wing) 2 | straight | yes | 279 | 1.9% | 279 | 1.9% |
| corner +x+y | corner | yes | 774 | 5.1% | 268 | 1.8% |
| straight -x+y (y wing) 0 | straight | yes | 885 | 5.9% | 885 | 5.9% |
| straight -x+y (y wing) 1 | straight | yes | 575 | 3.8% | 570 | 3.8% |
| straight -x+y (y wing) 2 | straight | yes | 302 | 2.0% | 300 | 2.0% |
| straight -x+y (x wing) 0 | straight | yes | 895 | 6.0% | 895 | 6.0% |
| straight -x+y (x wing) 1 | straight | yes | 580 | 3.9% | 573 | 3.8% |
| straight -x+y (x wing) 2 | straight | yes | 269 | 1.8% | 269 | 1.8% |
| corner -x+y | corner | yes | 744 | 4.9% | 240 | 1.6% |
| straight -x-y (y wing) 0 | straight | yes | 904 | 6.0% | 904 | 6.0% |
| straight -x-y (y wing) 1 | straight | yes | 597 | 4.0% | 586 | 3.9% |
| straight -x-y (y wing) 2 | straight | yes | 315 | 2.1% | 315 | 2.1% |
| straight -x-y (x wing) 0 | straight | yes | 909 | 6.0% | 909 | 6.0% |
| straight -x-y (x wing) 1 | straight | yes | 593 | 3.9% | 587 | 3.9% |
| straight -x-y (x wing) 2 | straight | yes | 256 | 1.7% | 256 | 1.7% |
| corner -x-y | corner | yes | 769 | 5.1% | 230 | 1.5% |
| straight +x-y (y wing) 0 | straight | yes | 894 | 5.9% | 894 | 5.9% |
| straight +x-y (y wing) 1 | straight | yes | 589 | 3.9% | 581 | 3.9% |
| straight +x-y (y wing) 2 | straight | yes | 277 | 1.8% | 277 | 1.8% |
| straight +x-y (x wing) 0 | straight | yes | 891 | 5.9% | 891 | 5.9% |
| straight +x-y (x wing) 1 | straight | yes | 593 | 3.9% | 578 | 3.8% |
| straight +x-y (x wing) 2 | straight | yes | 245 | 1.6% | 244 | 1.6% |
| corner +x-y | corner | yes | 768 | 5.1% | 292 | 1.9% |
| **straight (24)** | | | 14078 | | 14010 | 93.2% |
| **corner (4)** | | | 3055 | | 1030 | 6.8% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 716 | 39.5 | 363.8 | 0.28 | 0.31 | 0.0% |
| -x | 724 | 39.7 | 365.9 | 0.28 | 0.32 | 0.0% |
| +y | 722 | 39.7 | 367.8 | 0.28 | 0.31 | 0.0% |
| -y | 734 | 39.7 | 371.3 | 0.28 | 0.31 | 0.0% |
| door +x+y (y wall) 0 | 610 | 4.9 | 384.6 | 0.96 | 1.32 | 79.5% |
| door +x+y (y wall) 1 | 571 | 4.9 | 397.9 | 0.87 | 1.26 | 67.5% |
| door +x+y (y wall) 2 | 278 | 4.9 | 414.9 | 0.41 | 1.26 | 11.9% |
| door +x+y (x wall) 0 | 593 | 4.9 | 383.2 | 0.94 | 1.26 | 76.9% |
| door +x+y (x wall) 1 | 577 | 4.9 | 397.0 | 0.88 | 1.32 | 65.0% |
| door +x+y (x wall) 2 | 278 | 4.9 | 407.2 | 0.41 | 1.32 | 12.2% |
| door +x+y (corner) | 132 | 43.6 | 401.9 | 0.22 | 1.32 | 5.4% |
| door -x+y (y wall) 0 | 589 | 4.9 | 365.6 | 0.98 | 1.32 | 78.4% |
| door -x+y (y wall) 1 | 566 | 4.9 | 396.7 | 0.86 | 1.32 | 65.0% |
| door -x+y (y wall) 2 | 303 | 4.9 | 429.6 | 0.43 | 1.32 | 9.1% |
| door -x+y (x wall) 0 | 599 | 4.9 | 368.9 | 0.98 | 1.38 | 81.1% |
| door -x+y (x wall) 1 | 566 | 4.9 | 391.1 | 0.88 | 1.32 | 70.0% |
| door -x+y (x wall) 2 | 276 | 4.9 | 421.5 | 0.40 | 1.26 | 14.0% |
| door -x+y (corner) | 118 | 37.3 | 432.4 | 0.18 | 0.78 | 0.0% |
| door -x-y (y wall) 0 | 593 | 4.9 | 389.9 | 0.92 | 1.20 | 77.5% |
| door -x-y (y wall) 1 | 569 | 4.9 | 408.4 | 0.84 | 1.32 | 58.5% |
| door -x-y (y wall) 2 | 332 | 4.9 | 429.2 | 0.47 | 1.32 | 11.4% |
| door -x-y (x wall) 0 | 610 | 4.9 | 385.7 | 0.96 | 1.32 | 79.5% |
| door -x-y (x wall) 1 | 587 | 4.9 | 397.7 | 0.89 | 1.32 | 72.5% |
| door -x-y (x wall) 2 | 256 | 4.9 | 420.0 | 0.37 | 1.32 | 11.6% |
| door -x-y (corner) | 107 | 34.1 | 423.6 | 0.16 | 0.96 | 0.0% |
| door +x-y (y wall) 0 | 593 | 4.9 | 380.1 | 0.94 | 1.26 | 79.5% |
| door +x-y (y wall) 1 | 576 | 4.9 | 391.6 | 0.89 | 1.32 | 67.5% |
| door +x-y (y wall) 2 | 284 | 4.9 | 402.6 | 0.43 | 1.26 | 17.1% |
| door +x-y (x wall) 0 | 596 | 4.9 | 377.4 | 0.96 | 1.26 | 78.9% |
| door +x-y (x wall) 1 | 564 | 4.9 | 392.7 | 0.87 | 1.26 | 65.0% |
| door +x-y (x wall) 2 | 264 | 4.9 | 399.7 | 0.40 | 1.32 | 9.8% |
| door +x-y (corner) | 157 | 45.7 | 398.1 | 0.27 | 1.32 | 5.6% |

Mean flow / w J averaged over the doors 0.67, over the avenues 0.28.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 899 | 610 / 289 / 177 | 0.7 | 381.6 | 2.82 | 4.61 | 87% | 74% | 13% | 3.97 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 536 | 572 / 0 / 9 | 0.7 | 394.9 | 1.47 | 2.01 | 78% | 65% | 12% | 3.50 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 68 | 277 / 0 / 0 | 0.7 | 411.9 | 0.67 | 1.91 | 10% | 10% | 0% | 3.08 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 892 | 593 / 299 / 202 | 0.7 | 380.2 | 2.88 | 4.91 | 87% | 74% | 13% | 3.91 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 536 | 577 / 0 / 11 | 0.7 | 394.1 | 1.49 | 2.11 | 72% | 62% | 10% | 3.72 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 68 | 279 / 0 / 0 | 0.7 | 404.2 | 0.69 | 2.11 | 12% | 12% | 0% | 2.84 |
| corner +x+y | 1.20 | 85.6 | 765 | 131 / 137 / 517 | 0.7 | 406.0 | 1.94 | 3.91 | 85% | 56% | 29% | 2.52 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 885 | 589 / 296 / 188 | 0.7 | 362.6 | 2.96 | 4.71 | 86% | 76% | 11% | 3.96 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 539 | 570 / 0 / 13 | 0.7 | 393.7 | 1.48 | 2.11 | 78% | 62% | 15% | 3.42 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 68 | 300 / 0 / 3 | 0.7 | 426.6 | 0.71 | 2.11 | 9% | 9% | 0% | 3.06 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 895 | 599 / 297 / 159 | 0.7 | 365.9 | 2.89 | 4.51 | 86% | 78% | 8% | 4.05 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 543 | 573 / 0 / 9 | 0.7 | 388.1 | 1.50 | 2.21 | 82% | 67% | 15% | 3.52 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 66 | 269 / 0 / 0 | 0.7 | 418.6 | 0.64 | 1.91 | 10% | 10% | 0% | 3.05 |
| corner -x+y | 1.20 | 85.6 | 736 | 117 / 123 / 521 | 0.7 | 428.5 | 1.78 | 3.91 | 79% | 56% | 23% | 2.59 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 904 | 593 / 311 / 195 | 0.7 | 386.9 | 2.84 | 4.41 | 90% | 77% | 13% | 3.89 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 547 | 586 / 0 / 22 | 0.7 | 405.4 | 1.50 | 2.61 | 78% | 63% | 15% | 3.51 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 67 | 315 / 0 / 0 | 0.7 | 426.2 | 0.74 | 2.11 | 9% | 9% | 0% | 3.02 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 909 | 610 / 299 / 152 | 0.7 | 382.7 | 2.78 | 4.31 | 85% | 77% | 8% | 4.13 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 538 | 587 / 0 / 19 | 0.7 | 394.8 | 1.54 | 2.21 | 78% | 65% | 12% | 3.50 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 66 | 256 / 0 / 0 | 0.7 | 417.0 | 0.61 | 2.01 | 10% | 10% | 0% | 3.05 |
| corner -x-y | 1.20 | 85.6 | 756 | 107 / 123 / 567 | 0.7 | 420.1 | 1.90 | 5.02 | 81% | 63% | 19% | 2.66 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 894 | 593 / 301 / 186 | 0.7 | 377.1 | 2.87 | 4.51 | 89% | 76% | 13% | 3.95 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 545 | 581 / 0 / 24 | 0.7 | 388.6 | 1.56 | 2.51 | 77% | 64% | 13% | 3.66 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 63 | 277 / 0 / 0 | 0.7 | 399.7 | 0.69 | 1.91 | 10% | 10% | 0% | 3.12 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 891 | 596 / 295 / 164 | 0.7 | 374.5 | 2.82 | 4.31 | 87% | 76% | 11% | 4.00 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 550 | 578 / 0 / 16 | 0.7 | 389.7 | 1.53 | 2.11 | 78% | 65% | 12% | 3.69 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 67 | 244 / 0 / 1 | 0.7 | 396.7 | 0.62 | 2.01 | 10% | 10% | 0% | 2.95 |
| corner +x-y | 1.20 | 85.6 | 747 | 165 / 127 / 496 | 0.7 | 394.2 | 2.00 | 4.01 | 82% | 55% | 28% | 2.55 |

The last agent out (agent 4117, t100 432.4 s): last gangway corner -x+y, exit door -x+y (corner). The gangway that cleared last: corner -x+y at 428.5 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.80 | 425.7 / 415.6 / 384.6 | 413.3 / 396.0 / 308.7 | 474797.0 | 1250628 | 0.259 |
| gangway | 1212 | 1112.9 | 6.80 | 425.0 / 411.0 / 332.0 | 413.3 / 396.0 / 308.7 | 473955.5 | 1108181 | 0.139 |
| walkway | 276 | 257.4 | 3.38 | 268.1 / 145.3 / 0.0 | 168.1 / 45.7 / 0.0 | 0.0 | 26522 | 0.753 |
| avenue | 912 | 858.9 | 1.83 | 316.6 / 0.0 / 0.0 | 251.5 / 0.0 / 0.0 | 0.0 | 83191 | 1.326 |
| exit | 32 | 3.2 | 0.00 | 405.3 / 402.1 / 370.3 | 244.2 / 222.1 / 131.2 | 841.5 | 1540 | 1.317 |
| concourse | 1116 | 1043.8 | 2.70 | 387.9 / 14.5 / 0.0 | 235.2 / 11.5 / 0.0 | 0.0 | 31195 | 1.188 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.55 | 361.5 / 348.2 / 333.2 | 356.5 / 346.5 / 330.0 | 464092.5 | 1375760 | 0.062 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -26.5 | 29.5 | gangway | 1.00 | 6.24 | 332.5 | 311.7 | 283.3 | 1655.5 | 0.028 |
| 2 | -26.5 | -28.5 | gangway | 1.00 | 6.16 | 351.9 | 339.0 | 273.6 | 1641.2 | 0.030 |
| 3 | -29.5 | -26.5 | gangway | 1.00 | 6.02 | 354.7 | 317.5 | 277.6 | 1621.7 | 0.038 |
| 4 | 29.5 | -26.5 | gangway | 1.00 | 6.05 | 337.4 | 315.4 | 275.7 | 1619.4 | 0.031 |
| 5 | -26.5 | -29.5 | gangway | 1.00 | 6.02 | 342.1 | 316.8 | 275.0 | 1589.4 | 0.035 |
| 6 | -26.5 | -27.5 | gangway | 1.00 | 5.87 | 354.5 | 338.6 | 274.4 | 1573.5 | 0.028 |
| 7 | -29.5 | 26.5 | gangway | 1.00 | 6.13 | 346.1 | 309.2 | 264.8 | 1548.0 | 0.029 |
| 8 | -27.5 | -28.5 | gangway | 1.00 | 6.03 | 361.2 | 346.1 | 263.2 | 1534.7 | 0.026 |
| 9 | 26.5 | 29.5 | gangway | 1.00 | 5.95 | 356.3 | 332.3 | 262.2 | 1510.7 | 0.032 |
| 10 | -28.5 | -26.5 | gangway | 1.00 | 5.92 | 354.4 | 347.2 | 260.3 | 1502.7 | 0.032 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 24.5 | 26.5 | seat row | 0.50 | 7.25 | 342.5 | 339.7 | 330.0 | 1110.7 | 0.020 |
| 2 | 24.5 | -26.5 | seat row | 0.50 | 7.27 | 335.8 | 332.1 | 327.3 | 1103.4 | 0.020 |
| 3 | 26.5 | -24.5 | seat row | 0.50 | 7.30 | 333.5 | 331.6 | 323.1 | 1098.2 | 0.021 |
| 4 | -26.5 | -24.5 | seat row | 0.50 | 7.12 | 341.1 | 336.2 | 318.7 | 1091.5 | 0.017 |
| 5 | -24.5 | -26.5 | seat row | 0.50 | 7.38 | 334.9 | 327.4 | 315.4 | 1090.2 | 0.016 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1426; agent-steps of seated agents on another row's clearway: 27352.

## Deposit check

Person-seconds deposited: 2629343.2, of them in excluded cells: 2954.954.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 207481 overlapping pair-steps: p99 0.0040, max 0.0406 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0040 max 0.0406; venue-geometry 3: p99 0.0003 max 0.0003 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00754 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 10 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.28 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 646 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
