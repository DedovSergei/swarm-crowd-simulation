# Experiment `M_load95_s2`

**Task 5.8 stage 2: venue M, 95% load (seed 2), default model**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 15040 agents on 95% of the 15832 seats (spawnSeatedCrowd, seed 2), buffer N = 16384, 2427 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 880032 evaluations, 39438 switches, 0 forced choices).
Capacity: **within design capacity** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `cd8e0bbf3411846ca7aa6719887d122a142a7ca1`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-15T16:27:53, 58.9 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 976 | 170.7 |
| t90 | 1845 | 322.7 |
| t100 | 2427 | 424.5 |

t_p: the step by which ceil(p x 15040) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 728 | 0 | 39.7 | 373.4 | 23.1 | 25.5 | 51.9-61.9 |
| -x | 5.66 | 730 | 0 | 39.7 | 367.5 | 23.6 | 26.6 | 111.1-121.0 |
| +y | 5.66 | 729 | 0 | 39.7 | 368.2 | 23.5 | 25.5 | 49.1-59.1 |
| -y | 5.66 | 727 | 0 | 39.5 | 367.1 | 23.5 | 26.6 | 166.7-176.7 |
| door +x+y (y wall) 0 | 1.20 | 598 | 1065 | 4.9 | 374.0 | 81.0 | 105.3 | 24.5-34.5 |
| door +x+y (y wall) 1 | 1.20 | 579 | 646 | 4.9 | 393.9 | 74.4 | 110.3 | 26.9-36.9 |
| door +x+y (y wall) 2 | 1.20 | 282 | 169 | 4.9 | 412.1 | 34.6 | 105.3 | 7.2-17.1 |
| door +x+y (x wall) 0 | 1.20 | 596 | 1071 | 4.9 | 385.8 | 78.2 | 105.3 | 262.4-272.3 |
| door +x+y (x wall) 1 | 1.20 | 588 | 650 | 4.9 | 388.8 | 76.5 | 110.3 | 13.3-23.3 |
| door +x+y (x wall) 2 | 1.20 | 284 | 170 | 4.9 | 420.5 | 34.2 | 105.3 | 21.7-31.7 |
| door +x+y (corner) | 1.20 | 112 | 0 | 37.6 | 420.5 | 14.6 | 95.3 | 324.3-334.2 |
| door -x+y (y wall) 0 | 1.20 | 600 | 1082 | 4.9 | 387.6 | 78.4 | 105.3 | 7.9-17.8 |
| door -x+y (y wall) 1 | 1.20 | 582 | 648 | 4.9 | 417.0 | 70.6 | 115.3 | 240.3-250.3 |
| door -x+y (y wall) 2 | 1.20 | 283 | 167 | 4.9 | 423.6 | 33.8 | 100.3 | 11.2-21.2 |
| door -x+y (x wall) 0 | 1.20 | 599 | 1051 | 4.9 | 376.2 | 80.6 | 110.3 | 14.5-24.5 |
| door -x+y (x wall) 1 | 1.20 | 573 | 643 | 4.9 | 393.7 | 73.7 | 100.3 | 4.7-14.7 |
| door -x+y (x wall) 2 | 1.20 | 275 | 166 | 4.9 | 414.9 | 33.5 | 110.3 | 15.6-25.5 |
| door -x+y (corner) | 1.20 | 112 | 0 | 58.2 | 424.5 | 15.3 | 80.2 | 265.2-275.1 |
| door -x-y (y wall) 0 | 1.20 | 594 | 1060 | 4.9 | 373.4 | 80.6 | 105.3 | 5.8-15.7 |
| door -x-y (y wall) 1 | 1.20 | 564 | 641 | 4.9 | 387.9 | 73.6 | 105.3 | 31.1-41.1 |
| door -x-y (y wall) 2 | 1.20 | 273 | 171 | 4.9 | 405.4 | 34.1 | 100.3 | 7.9-17.8 |
| door -x-y (x wall) 0 | 1.20 | 592 | 1063 | 4.9 | 381.3 | 78.6 | 105.3 | 82.4-92.4 |
| door -x-y (x wall) 1 | 1.20 | 583 | 650 | 4.9 | 384.6 | 76.7 | 105.3 | 11.4-21.3 |
| door -x-y (x wall) 2 | 1.20 | 282 | 170 | 4.9 | 398.8 | 35.8 | 105.3 | 20.5-30.4 |
| door -x-y (corner) | 1.20 | 143 | 0 | 54.6 | 408.9 | 20.2 | 95.3 | 313.3-323.2 |
| door +x-y (y wall) 0 | 1.20 | 595 | 1064 | 4.9 | 373.6 | 80.6 | 105.3 | 7.9-17.8 |
| door +x-y (y wall) 1 | 1.20 | 576 | 639 | 4.9 | 386.5 | 75.4 | 110.3 | 22.9-32.9 |
| door +x-y (y wall) 2 | 1.20 | 283 | 164 | 4.9 | 408.4 | 35.1 | 100.3 | 10.5-20.5 |
| door +x-y (x wall) 0 | 1.20 | 596 | 1071 | 4.9 | 373.8 | 80.7 | 105.3 | 8.4-18.4 |
| door +x-y (x wall) 1 | 1.20 | 587 | 648 | 4.9 | 389.2 | 76.3 | 105.3 | 9.3-19.2 |
| door +x-y (x wall) 2 | 1.20 | 264 | 171 | 4.9 | 396.0 | 33.7 | 100.3 | 7.7-17.7 |
| door +x-y (corner) | 1.20 | 131 | 0 | 29.4 | 408.2 | 17.3 | 75.2 | 46.9-56.8 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 728 | 4.8% | 21.7% |
| -x | avenue | 5.66 | 730 | 4.9% | 21.8% |
| +y | avenue | 5.66 | 729 | 4.8% | 21.8% |
| -y | avenue | 5.66 | 727 | 4.8% | 21.7% |
| door +x+y (y wall) 0 | door | 1.20 | 598 | 4.0% | 84.3% |
| door +x+y (y wall) 1 | door | 1.20 | 579 | 3.8% | 81.6% |
| door +x+y (y wall) 2 | door | 1.20 | 282 | 1.9% | 39.7% |
| door +x+y (x wall) 0 | door | 1.20 | 596 | 4.0% | 84.0% |
| door +x+y (x wall) 1 | door | 1.20 | 588 | 3.9% | 82.8% |
| door +x+y (x wall) 2 | door | 1.20 | 284 | 1.9% | 40.0% |
| door +x+y (corner) | door | 1.20 | 112 | 0.7% | 15.8% |
| door -x+y (y wall) 0 | door | 1.20 | 600 | 4.0% | 84.5% |
| door -x+y (y wall) 1 | door | 1.20 | 582 | 3.9% | 82.0% |
| door -x+y (y wall) 2 | door | 1.20 | 283 | 1.9% | 39.9% |
| door -x+y (x wall) 0 | door | 1.20 | 599 | 4.0% | 84.4% |
| door -x+y (x wall) 1 | door | 1.20 | 573 | 3.8% | 80.7% |
| door -x+y (x wall) 2 | door | 1.20 | 275 | 1.8% | 38.7% |
| door -x+y (corner) | door | 1.20 | 112 | 0.7% | 15.8% |
| door -x-y (y wall) 0 | door | 1.20 | 594 | 3.9% | 83.7% |
| door -x-y (y wall) 1 | door | 1.20 | 564 | 3.8% | 79.5% |
| door -x-y (y wall) 2 | door | 1.20 | 273 | 1.8% | 38.5% |
| door -x-y (x wall) 0 | door | 1.20 | 592 | 3.9% | 83.4% |
| door -x-y (x wall) 1 | door | 1.20 | 583 | 3.9% | 82.1% |
| door -x-y (x wall) 2 | door | 1.20 | 282 | 1.9% | 39.7% |
| door -x-y (corner) | door | 1.20 | 143 | 1.0% | 20.1% |
| door +x-y (y wall) 0 | door | 1.20 | 595 | 4.0% | 83.8% |
| door +x-y (y wall) 1 | door | 1.20 | 576 | 3.8% | 81.2% |
| door +x-y (y wall) 2 | door | 1.20 | 283 | 1.9% | 39.9% |
| door +x-y (x wall) 0 | door | 1.20 | 596 | 4.0% | 84.0% |
| door +x-y (x wall) 1 | door | 1.20 | 587 | 3.9% | 82.7% |
| door +x-y (x wall) 2 | door | 1.20 | 264 | 1.8% | 37.2% |
| door +x-y (corner) | door | 1.20 | 131 | 0.9% | 18.5% |
| **doors (28)** | door | 33.60 | 12126 | 80.6% | |
| **avenues (4)** | avenue | 22.64 | 2914 | 19.4% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 424.5 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 45.2%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 904 | 6.0% | 904 | 6.0% |
| straight +x+y (y wing) 1 | straight | yes | 593 | 3.9% | 588 | 3.9% |
| straight +x+y (y wing) 2 | straight | yes | 273 | 1.8% | 273 | 1.8% |
| straight +x+y (x wing) 0 | straight | yes | 896 | 6.0% | 896 | 6.0% |
| straight +x+y (x wing) 1 | straight | yes | 594 | 3.9% | 588 | 3.9% |
| straight +x+y (x wing) 2 | straight | yes | 284 | 1.9% | 284 | 1.9% |
| corner +x+y | corner | yes | 762 | 5.1% | 238 | 1.6% |
| straight -x+y (y wing) 0 | straight | yes | 908 | 6.0% | 908 | 6.0% |
| straight -x+y (y wing) 1 | straight | yes | 589 | 3.9% | 586 | 3.9% |
| straight -x+y (y wing) 2 | straight | yes | 279 | 1.9% | 279 | 1.9% |
| straight -x+y (x wing) 0 | straight | yes | 888 | 5.9% | 888 | 5.9% |
| straight -x+y (x wing) 1 | straight | yes | 585 | 3.9% | 580 | 3.9% |
| straight -x+y (x wing) 2 | straight | yes | 268 | 1.8% | 268 | 1.8% |
| corner -x+y | corner | yes | 756 | 5.0% | 248 | 1.6% |
| straight -x-y (y wing) 0 | straight | yes | 886 | 5.9% | 886 | 5.9% |
| straight -x-y (y wing) 1 | straight | yes | 588 | 3.9% | 579 | 3.8% |
| straight -x-y (y wing) 2 | straight | yes | 254 | 1.7% | 254 | 1.7% |
| straight -x-y (x wing) 0 | straight | yes | 896 | 6.0% | 896 | 6.0% |
| straight -x-y (x wing) 1 | straight | yes | 591 | 3.9% | 584 | 3.9% |
| straight -x-y (x wing) 2 | straight | yes | 282 | 1.9% | 282 | 1.9% |
| corner -x-y | corner | yes | 751 | 5.0% | 274 | 1.8% |
| straight +x-y (y wing) 0 | straight | yes | 892 | 5.9% | 892 | 5.9% |
| straight +x-y (y wing) 1 | straight | yes | 591 | 3.9% | 584 | 3.9% |
| straight +x-y (y wing) 2 | straight | yes | 280 | 1.9% | 278 | 1.8% |
| straight +x-y (x wing) 0 | straight | yes | 901 | 6.0% | 901 | 6.0% |
| straight +x-y (x wing) 1 | straight | yes | 594 | 3.9% | 587 | 3.9% |
| straight +x-y (x wing) 2 | straight | yes | 264 | 1.8% | 264 | 1.8% |
| corner +x-y | corner | yes | 762 | 5.1% | 251 | 1.7% |
| **straight (24)** | | | 14080 | | 14029 | 93.3% |
| **corner (4)** | | | 3031 | | 1011 | 6.7% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 728 | 39.7 | 373.4 | 0.28 | 0.31 | 0.0% |
| -x | 730 | 39.7 | 367.5 | 0.28 | 0.32 | 0.0% |
| +y | 729 | 39.7 | 368.2 | 0.28 | 0.31 | 0.0% |
| -y | 727 | 39.5 | 367.1 | 0.28 | 0.32 | 0.0% |
| door +x+y (y wall) 0 | 598 | 4.9 | 374.0 | 0.97 | 1.26 | 78.9% |
| door +x+y (y wall) 1 | 579 | 4.9 | 393.9 | 0.89 | 1.32 | 62.5% |
| door +x+y (y wall) 2 | 282 | 4.9 | 412.1 | 0.41 | 1.26 | 11.9% |
| door +x+y (x wall) 0 | 596 | 4.9 | 385.8 | 0.94 | 1.26 | 79.5% |
| door +x+y (x wall) 1 | 588 | 4.9 | 388.8 | 0.92 | 1.32 | 74.4% |
| door +x+y (x wall) 2 | 284 | 4.9 | 420.5 | 0.41 | 1.26 | 9.3% |
| door +x+y (corner) | 112 | 37.6 | 420.5 | 0.17 | 1.14 | 0.0% |
| door -x+y (y wall) 0 | 600 | 4.9 | 387.6 | 0.94 | 1.26 | 79.5% |
| door -x+y (y wall) 1 | 582 | 4.9 | 417.0 | 0.84 | 1.38 | 64.3% |
| door -x+y (y wall) 2 | 283 | 4.9 | 423.6 | 0.40 | 1.20 | 11.6% |
| door -x+y (x wall) 0 | 599 | 4.9 | 376.2 | 0.96 | 1.32 | 81.6% |
| door -x+y (x wall) 1 | 573 | 4.9 | 393.7 | 0.88 | 1.20 | 62.5% |
| door -x+y (x wall) 2 | 275 | 4.9 | 414.9 | 0.40 | 1.32 | 11.9% |
| door -x+y (corner) | 112 | 58.2 | 424.5 | 0.18 | 0.96 | 0.0% |
| door -x-y (y wall) 0 | 594 | 4.9 | 373.4 | 0.96 | 1.26 | 78.9% |
| door -x-y (y wall) 1 | 564 | 4.9 | 387.9 | 0.88 | 1.26 | 64.1% |
| door -x-y (y wall) 2 | 273 | 4.9 | 405.4 | 0.41 | 1.20 | 12.2% |
| door -x-y (x wall) 0 | 592 | 4.9 | 381.3 | 0.94 | 1.26 | 76.9% |
| door -x-y (x wall) 1 | 583 | 4.9 | 384.6 | 0.92 | 1.26 | 69.2% |
| door -x-y (x wall) 2 | 282 | 4.9 | 398.8 | 0.43 | 1.26 | 10.0% |
| door -x-y (corner) | 143 | 54.6 | 408.9 | 0.24 | 1.14 | 5.4% |
| door +x-y (y wall) 0 | 595 | 4.9 | 373.6 | 0.96 | 1.26 | 78.9% |
| door +x-y (y wall) 1 | 576 | 4.9 | 386.5 | 0.90 | 1.32 | 71.8% |
| door +x-y (y wall) 2 | 283 | 4.9 | 408.4 | 0.42 | 1.20 | 7.3% |
| door +x-y (x wall) 0 | 596 | 4.9 | 373.8 | 0.97 | 1.26 | 78.9% |
| door +x-y (x wall) 1 | 587 | 4.9 | 389.2 | 0.91 | 1.26 | 65.0% |
| door +x-y (x wall) 2 | 264 | 4.9 | 396.0 | 0.40 | 1.20 | 12.5% |
| door +x-y (corner) | 131 | 29.4 | 408.2 | 0.21 | 0.90 | 2.6% |

Mean flow / w J averaged over the doors 0.67, over the avenues 0.28.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 904 | 598 / 306 / 187 | 0.7 | 371.0 | 2.95 | 4.71 | 84% | 76% | 8% | 4.17 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 538 | 588 / 0 / 16 | 0.7 | 390.9 | 1.55 | 2.71 | 75% | 65% | 10% | 3.66 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 63 | 273 / 0 / 0 | 0.7 | 409.1 | 0.67 | 1.91 | 10% | 10% | 0% | 3.07 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 896 | 596 / 300 / 203 | 0.7 | 383.0 | 2.87 | 4.41 | 74% | 74% | 0% | 4.43 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 550 | 588 / 0 / 8 | 0.7 | 385.8 | 1.55 | 2.01 | 77% | 67% | 10% | 3.74 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 66 | 284 / 0 / 0 | 0.7 | 417.5 | 0.68 | 1.91 | 12% | 12% | 0% | 2.93 |
| corner +x+y | 1.20 | 85.6 | 754 | 112 / 126 / 539 | 0.7 | 416.6 | 1.87 | 4.91 | 81% | 60% | 21% | 2.60 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 908 | 600 / 308 / 184 | 0.7 | 384.6 | 2.84 | 4.01 | 85% | 74% | 10% | 4.05 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 549 | 586 / 0 / 8 | 0.7 | 414.0 | 1.44 | 2.11 | 71% | 62% | 10% | 3.70 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 63 | 279 / 0 / 0 | 0.7 | 420.7 | 0.66 | 1.91 | 9% | 9% | 0% | 3.06 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 888 | 599 / 289 / 175 | 0.7 | 373.3 | 2.85 | 4.81 | 87% | 76% | 11% | 4.06 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 535 | 580 / 0 / 6 | 0.7 | 390.7 | 1.50 | 2.01 | 70% | 62% | 8% | 3.90 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 66 | 268 / 0 / 0 | 0.7 | 411.9 | 0.65 | 2.11 | 10% | 10% | 0% | 3.18 |
| corner -x+y | 1.20 | 85.6 | 748 | 112 / 136 / 514 | 0.7 | 420.7 | 1.81 | 4.81 | 77% | 60% | 16% | 2.67 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 886 | 594 / 292 / 149 | 0.7 | 370.5 | 2.80 | 4.51 | 82% | 76% | 5% | 4.27 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 555 | 579 / 0 / 13 | 0.7 | 385.0 | 1.54 | 2.11 | 79% | 69% | 10% | 3.52 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 65 | 254 / 0 / 0 | 0.7 | 402.5 | 0.63 | 1.91 | 10% | 10% | 0% | 3.12 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 896 | 592 / 304 / 183 | 0.7 | 378.3 | 2.86 | 4.51 | 84% | 76% | 8% | 4.22 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 547 | 584 / 0 / 8 | 0.7 | 381.6 | 1.55 | 2.11 | 74% | 67% | 8% | 3.79 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 66 | 282 / 0 / 0 | 0.7 | 395.8 | 0.71 | 1.91 | 12% | 12% | 0% | 2.87 |
| corner -x-y | 1.20 | 85.6 | 740 | 146 / 128 / 487 | 0.7 | 405.1 | 1.88 | 4.21 | 83% | 56% | 27% | 2.53 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 892 | 595 / 297 / 184 | 0.7 | 370.6 | 2.91 | 4.51 | 74% | 74% | 0% | 4.56 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 537 | 584 / 0 / 11 | 0.7 | 383.6 | 1.55 | 2.21 | 79% | 67% | 13% | 3.63 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 62 | 278 / 0 / 2 | 0.7 | 405.4 | 0.69 | 1.91 | 10% | 7% | 2% | 2.52 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 901 | 596 / 305 / 190 | 0.7 | 370.8 | 2.95 | 4.51 | 87% | 76% | 11% | 3.99 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 549 | 587 / 0 / 13 | 0.7 | 386.2 | 1.56 | 2.11 | 77% | 67% | 10% | 3.67 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 64 | 264 / 0 / 0 | 0.7 | 393.0 | 0.67 | 1.91 | 10% | 10% | 0% | 3.14 |
| corner +x-y | 1.20 | 85.6 | 752 | 128 / 123 / 527 | 0.7 | 404.4 | 1.93 | 4.21 | 80% | 61% | 20% | 2.57 |

The last agent out (agent 4165, t100 424.5 s): last gangway corner -x+y, exit door -x+y (corner). The gangway that cleared last: straight -x+y (y wing) 2 at 420.7 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.93 | 421.7 / 413.0 / 382.7 | 406.8 / 399.3 / 305.4 | 483944.4 | 1253978 | 0.258 |
| gangway | 1212 | 1112.9 | 6.93 | 419.4 / 406.5 / 322.4 | 406.8 / 399.3 / 305.4 | 483088.4 | 1111160 | 0.138 |
| walkway | 276 | 257.4 | 3.57 | 272.7 / 129.3 / 0.0 | 168.3 / 53.0 / 0.0 | 0.0 | 26559 | 0.757 |
| avenue | 912 | 858.9 | 2.05 | 319.9 / 0.0 / 0.0 | 256.8 / 0.0 / 0.0 | 0.0 | 83715 | 1.326 |
| exit | 32 | 3.2 | 0.00 | 403.9 / 399.8 / 368.0 | 245.9 / 223.7 / 131.4 | 855.9 | 1549 | 1.318 |
| concourse | 1116 | 1043.8 | 2.38 | 390.4 / 0.7 / 0.0 | 240.8 / 0.7 / 0.0 | 0.0 | 30995 | 1.192 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.62 | 354.5 / 338.6 / 325.0 | 342.6 / 338.6 / 321.5 | 469235.6 | 1380840 | 0.062 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -26.5 | 28.5 | gangway | 1.00 | 6.08 | 333.7 | 326.2 | 278.3 | 1632.0 | 0.026 |
| 2 | 26.5 | -29.5 | gangway | 1.00 | 6.17 | 348.4 | 313.3 | 271.3 | 1617.5 | 0.036 |
| 3 | -27.5 | 27.5 | gangway | 1.00 | 6.02 | 346.7 | 344.0 | 277.1 | 1587.1 | 0.030 |
| 4 | -26.5 | 29.5 | gangway | 1.00 | 6.22 | 333.4 | 323.1 | 262.4 | 1564.2 | 0.030 |
| 5 | -27.5 | -26.5 | gangway | 1.00 | 6.10 | 341.2 | 327.6 | 260.4 | 1551.2 | 0.025 |
| 6 | -27.5 | -27.5 | gangway | 1.00 | 6.21 | 341.9 | 339.1 | 256.9 | 1543.3 | 0.027 |
| 7 | -27.5 | 28.5 | gangway | 1.00 | 5.83 | 348.2 | 336.9 | 268.7 | 1530.1 | 0.030 |
| 8 | -26.5 | -27.5 | gangway | 1.00 | 5.99 | 347.4 | 338.1 | 270.2 | 1528.5 | 0.028 |
| 9 | 29.5 | 26.5 | gangway | 1.00 | 6.29 | 337.7 | 301.4 | 256.8 | 1523.7 | 0.032 |
| 10 | -26.5 | 27.5 | gangway | 1.00 | 6.04 | 347.0 | 337.0 | 259.2 | 1519.3 | 0.027 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 26.5 | -24.5 | seat row | 0.50 | 7.26 | 330.7 | 329.2 | 320.8 | 1106.8 | 0.019 |
| 2 | -24.5 | -26.5 | seat row | 0.50 | 7.31 | 340.0 | 338.6 | 313.4 | 1101.6 | 0.023 |
| 3 | -24.5 | 26.5 | seat row | 0.50 | 7.25 | 332.8 | 330.6 | 321.5 | 1096.9 | 0.021 |
| 4 | -26.5 | -24.5 | seat row | 0.50 | 7.23 | 338.8 | 337.4 | 319.2 | 1088.5 | 0.019 |
| 5 | -26.5 | 24.5 | seat row | 0.50 | 7.12 | 334.1 | 331.6 | 319.7 | 1083.0 | 0.018 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1459; agent-steps of seated agents on another row's clearway: 22157.

## Deposit check

Person-seconds deposited: 2637760.4, of them in excluded cells: 2942.136.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 206170 overlapping pair-steps: p99 0.0039, max 0.0225 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0039 max 0.0225; venue-geometry 2: p99 0.0002 max 0.0002 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00751 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 9 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.32 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 597 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
