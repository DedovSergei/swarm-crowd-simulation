# Experiment `M_load95_s2`

**Task 5.10 stage 4 (AMD 26.10.1): Task 5.8's model (the level spacing on the gangway inclines, --stair-flow off): venue M, 95% load (seed 2)**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 15040 agents on 95% of the 15832 seats (spawnSeatedCrowd, seed 2), buffer N = 16384, 2530 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 878635 evaluations, 39443 switches, 0 forced choices).
Capacity: **within design capacity** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T20:28:08, 88.1 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 977 | 170.9 |
| t90 | 1836 | 321.1 |
| t100 | 2530 | 442.5 |

t_p: the step by which ceil(p x 15040) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 719 | 0 | 39.5 | 369.2 | 23.1 | 25.5 | 54.2-64.2 |
| -x | 5.66 | 722 | 0 | 39.5 | 366.1 | 23.4 | 26.6 | 170.7-180.7 |
| +y | 5.66 | 729 | 0 | 39.5 | 366.6 | 23.6 | 26.6 | 153.2-163.2 |
| -y | 5.66 | 719 | 0 | 39.5 | 361.5 | 23.7 | 25.5 | 47.4-57.4 |
| door +x+y (y wall) 0 | 1.20 | 594 | 1065 | 4.9 | 383.4 | 78.4 | 105.3 | 20.6-30.6 |
| door +x+y (y wall) 1 | 1.20 | 569 | 646 | 4.9 | 442.5 | 65.0 | 110.3 | 52.6-62.6 |
| door +x+y (y wall) 2 | 1.20 | 273 | 169 | 4.9 | 408.2 | 33.8 | 105.3 | 7.2-17.1 |
| door +x+y (x wall) 0 | 1.20 | 607 | 1071 | 4.9 | 386.9 | 79.4 | 110.3 | 19.1-29.0 |
| door +x+y (x wall) 1 | 1.20 | 568 | 650 | 4.9 | 406.0 | 70.8 | 110.3 | 21.5-31.5 |
| door +x+y (x wall) 2 | 1.20 | 285 | 170 | 4.9 | 410.3 | 35.1 | 105.3 | 7.7-17.7 |
| door +x+y (corner) | 1.20 | 147 | 0 | 31.1 | 393.9 | 20.3 | 110.3 | 208.7-218.6 |
| door -x+y (y wall) 0 | 1.20 | 603 | 1082 | 4.9 | 380.2 | 80.3 | 110.3 | 233.9-243.8 |
| door -x+y (y wall) 1 | 1.20 | 581 | 648 | 4.9 | 388.6 | 75.7 | 105.3 | 9.3-19.2 |
| door -x+y (y wall) 2 | 1.20 | 292 | 167 | 4.9 | 408.1 | 36.2 | 100.3 | 11.2-21.2 |
| door -x+y (x wall) 0 | 1.20 | 600 | 1051 | 4.9 | 404.7 | 75.0 | 105.3 | 27.3-37.3 |
| door -x+y (x wall) 1 | 1.20 | 560 | 643 | 4.9 | 388.6 | 72.9 | 105.3 | 23.3-33.2 |
| door -x+y (x wall) 2 | 1.20 | 274 | 166 | 4.9 | 415.6 | 33.3 | 105.3 | 10.7-20.6 |
| door -x+y (corner) | 1.20 | 119 | 0 | 39.5 | 407.9 | 16.1 | 85.3 | 68.7-78.7 |
| door -x-y (y wall) 0 | 1.20 | 597 | 1060 | 4.9 | 390.7 | 77.3 | 105.3 | 29.9-39.9 |
| door -x-y (y wall) 1 | 1.20 | 574 | 641 | 4.9 | 380.6 | 76.4 | 105.3 | 26.1-36.0 |
| door -x-y (y wall) 2 | 1.20 | 298 | 171 | 4.9 | 429.9 | 35.0 | 105.3 | 7.7-17.7 |
| door -x-y (x wall) 0 | 1.20 | 603 | 1063 | 4.9 | 393.0 | 77.6 | 110.3 | 26.2-36.2 |
| door -x-y (x wall) 1 | 1.20 | 584 | 650 | 4.9 | 404.4 | 73.1 | 115.3 | 33.1-43.0 |
| door -x-y (x wall) 2 | 1.20 | 278 | 170 | 4.9 | 432.0 | 32.5 | 105.3 | 10.1-20.1 |
| door -x-y (corner) | 1.20 | 103 | 0 | 46.5 | 436.0 | 13.2 | 65.2 | 67.5-77.5 |
| door +x-y (y wall) 0 | 1.20 | 602 | 1064 | 4.9 | 386.7 | 78.8 | 110.3 | 14.3-24.3 |
| door +x-y (y wall) 1 | 1.20 | 563 | 639 | 4.9 | 397.2 | 71.7 | 110.3 | 27.6-37.6 |
| door +x-y (y wall) 2 | 1.20 | 278 | 164 | 4.9 | 411.2 | 34.2 | 105.3 | 12.1-22.0 |
| door +x-y (x wall) 0 | 1.20 | 599 | 1071 | 4.9 | 383.7 | 79.0 | 105.3 | 13.1-23.1 |
| door +x-y (x wall) 1 | 1.20 | 578 | 648 | 4.9 | 399.0 | 73.3 | 105.3 | 11.2-21.2 |
| door +x-y (x wall) 2 | 1.20 | 270 | 171 | 4.9 | 421.9 | 32.4 | 105.3 | 10.7-20.6 |
| door +x-y (corner) | 1.20 | 152 | 0 | 30.3 | 418.9 | 19.5 | 90.3 | 307.3-317.3 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 719 | 4.8% | 20.6% |
| -x | avenue | 5.66 | 722 | 4.8% | 20.7% |
| +y | avenue | 5.66 | 729 | 4.8% | 20.9% |
| -y | avenue | 5.66 | 719 | 4.8% | 20.6% |
| door +x+y (y wall) 0 | door | 1.20 | 594 | 3.9% | 80.3% |
| door +x+y (y wall) 1 | door | 1.20 | 569 | 3.8% | 76.9% |
| door +x+y (y wall) 2 | door | 1.20 | 273 | 1.8% | 36.9% |
| door +x+y (x wall) 0 | door | 1.20 | 607 | 4.0% | 82.0% |
| door +x+y (x wall) 1 | door | 1.20 | 568 | 3.8% | 76.8% |
| door +x+y (x wall) 2 | door | 1.20 | 285 | 1.9% | 38.5% |
| door +x+y (corner) | door | 1.20 | 147 | 1.0% | 19.9% |
| door -x+y (y wall) 0 | door | 1.20 | 603 | 4.0% | 81.5% |
| door -x+y (y wall) 1 | door | 1.20 | 581 | 3.9% | 78.5% |
| door -x+y (y wall) 2 | door | 1.20 | 292 | 1.9% | 39.5% |
| door -x+y (x wall) 0 | door | 1.20 | 600 | 4.0% | 81.1% |
| door -x+y (x wall) 1 | door | 1.20 | 560 | 3.7% | 75.7% |
| door -x+y (x wall) 2 | door | 1.20 | 274 | 1.8% | 37.0% |
| door -x+y (corner) | door | 1.20 | 119 | 0.8% | 16.1% |
| door -x-y (y wall) 0 | door | 1.20 | 597 | 4.0% | 80.7% |
| door -x-y (y wall) 1 | door | 1.20 | 574 | 3.8% | 77.6% |
| door -x-y (y wall) 2 | door | 1.20 | 298 | 2.0% | 40.3% |
| door -x-y (x wall) 0 | door | 1.20 | 603 | 4.0% | 81.5% |
| door -x-y (x wall) 1 | door | 1.20 | 584 | 3.9% | 78.9% |
| door -x-y (x wall) 2 | door | 1.20 | 278 | 1.8% | 37.6% |
| door -x-y (corner) | door | 1.20 | 103 | 0.7% | 13.9% |
| door +x-y (y wall) 0 | door | 1.20 | 602 | 4.0% | 81.4% |
| door +x-y (y wall) 1 | door | 1.20 | 563 | 3.7% | 76.1% |
| door +x-y (y wall) 2 | door | 1.20 | 278 | 1.8% | 37.6% |
| door +x-y (x wall) 0 | door | 1.20 | 599 | 4.0% | 81.0% |
| door +x-y (x wall) 1 | door | 1.20 | 578 | 3.8% | 78.1% |
| door +x-y (x wall) 2 | door | 1.20 | 270 | 1.8% | 36.5% |
| door +x-y (corner) | door | 1.20 | 152 | 1.0% | 20.5% |
| **doors (28)** | door | 33.60 | 12151 | 80.8% | |
| **avenues (4)** | avenue | 22.64 | 2889 | 19.2% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 442.5 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 43.4%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 907 | 6.0% | 907 | 6.0% |
| straight +x+y (y wing) 1 | straight | yes | 588 | 3.9% | 578 | 3.8% |
| straight +x+y (y wing) 2 | straight | yes | 263 | 1.7% | 263 | 1.7% |
| straight +x+y (x wing) 0 | straight | yes | 894 | 5.9% | 894 | 5.9% |
| straight +x+y (x wing) 1 | straight | yes | 585 | 3.9% | 577 | 3.8% |
| straight +x+y (x wing) 2 | straight | yes | 274 | 1.8% | 274 | 1.8% |
| corner +x+y | corner | yes | 772 | 5.1% | 278 | 1.8% |
| straight -x+y (y wing) 0 | straight | yes | 902 | 6.0% | 902 | 6.0% |
| straight -x+y (y wing) 1 | straight | yes | 595 | 4.0% | 581 | 3.9% |
| straight -x+y (y wing) 2 | straight | yes | 293 | 1.9% | 293 | 1.9% |
| straight -x+y (x wing) 0 | straight | yes | 895 | 6.0% | 895 | 6.0% |
| straight -x+y (x wing) 1 | straight | yes | 573 | 3.8% | 569 | 3.8% |
| straight -x+y (x wing) 2 | straight | yes | 265 | 1.8% | 265 | 1.8% |
| corner -x+y | corner | yes | 761 | 5.1% | 252 | 1.7% |
| straight -x-y (y wing) 0 | straight | yes | 891 | 5.9% | 891 | 5.9% |
| straight -x-y (y wing) 1 | straight | yes | 591 | 3.9% | 587 | 3.9% |
| straight -x-y (y wing) 2 | straight | yes | 285 | 1.9% | 285 | 1.9% |
| straight -x-y (x wing) 0 | straight | yes | 901 | 6.0% | 901 | 6.0% |
| straight -x-y (x wing) 1 | straight | yes | 590 | 3.9% | 584 | 3.9% |
| straight -x-y (x wing) 2 | straight | yes | 278 | 1.8% | 278 | 1.8% |
| corner -x-y | corner | yes | 752 | 5.0% | 229 | 1.5% |
| straight +x-y (y wing) 0 | straight | yes | 900 | 6.0% | 900 | 6.0% |
| straight +x-y (y wing) 1 | straight | yes | 578 | 3.8% | 571 | 3.8% |
| straight +x-y (y wing) 2 | straight | yes | 277 | 1.8% | 275 | 1.8% |
| straight +x-y (x wing) 0 | straight | yes | 897 | 6.0% | 897 | 6.0% |
| straight +x-y (x wing) 1 | straight | yes | 586 | 3.9% | 580 | 3.9% |
| straight +x-y (x wing) 2 | straight | yes | 266 | 1.8% | 266 | 1.8% |
| corner +x-y | corner | yes | 764 | 5.1% | 268 | 1.8% |
| **straight (24)** | | | 14074 | | 14013 | 93.2% |
| **corner (4)** | | | 3049 | | 1027 | 6.8% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 719 | 39.5 | 369.2 | 0.28 | 0.31 | 0.0% |
| -x | 722 | 39.5 | 366.1 | 0.28 | 0.32 | 0.0% |
| +y | 729 | 39.5 | 366.6 | 0.28 | 0.32 | 0.0% |
| -y | 719 | 39.5 | 361.5 | 0.28 | 0.31 | 0.0% |
| door +x+y (y wall) 0 | 594 | 4.9 | 383.4 | 0.94 | 1.26 | 76.9% |
| door +x+y (y wall) 1 | 569 | 4.9 | 442.5 | 0.78 | 1.32 | 60.0% |
| door +x+y (y wall) 2 | 273 | 4.9 | 408.2 | 0.40 | 1.26 | 14.6% |
| door +x+y (x wall) 0 | 607 | 4.9 | 386.9 | 0.95 | 1.32 | 79.5% |
| door +x+y (x wall) 1 | 568 | 4.9 | 406.0 | 0.85 | 1.32 | 65.9% |
| door +x+y (x wall) 2 | 285 | 4.9 | 410.3 | 0.42 | 1.26 | 9.5% |
| door +x+y (corner) | 147 | 31.1 | 393.9 | 0.24 | 1.32 | 5.4% |
| door -x+y (y wall) 0 | 603 | 4.9 | 380.2 | 0.96 | 1.32 | 79.5% |
| door -x+y (y wall) 1 | 581 | 4.9 | 388.6 | 0.91 | 1.26 | 71.8% |
| door -x+y (y wall) 2 | 292 | 4.9 | 408.1 | 0.43 | 1.20 | 9.8% |
| door -x+y (x wall) 0 | 600 | 4.9 | 404.7 | 0.90 | 1.26 | 75.6% |
| door -x+y (x wall) 1 | 560 | 4.9 | 388.6 | 0.87 | 1.26 | 66.7% |
| door -x+y (x wall) 2 | 274 | 4.9 | 415.6 | 0.40 | 1.26 | 11.9% |
| door -x+y (corner) | 119 | 39.5 | 407.9 | 0.19 | 1.02 | 5.3% |
| door -x-y (y wall) 0 | 597 | 4.9 | 390.7 | 0.92 | 1.26 | 75.0% |
| door -x-y (y wall) 1 | 574 | 4.9 | 380.6 | 0.91 | 1.26 | 66.7% |
| door -x-y (y wall) 2 | 298 | 4.9 | 429.9 | 0.42 | 1.26 | 13.6% |
| door -x-y (x wall) 0 | 603 | 4.9 | 393.0 | 0.93 | 1.32 | 75.0% |
| door -x-y (x wall) 1 | 584 | 4.9 | 404.4 | 0.87 | 1.38 | 63.4% |
| door -x-y (x wall) 2 | 278 | 4.9 | 432.0 | 0.39 | 1.26 | 11.4% |
| door -x-y (corner) | 103 | 46.5 | 436.0 | 0.16 | 0.78 | 0.0% |
| door +x-y (y wall) 0 | 602 | 4.9 | 386.7 | 0.94 | 1.32 | 76.9% |
| door +x-y (y wall) 1 | 563 | 4.9 | 397.2 | 0.86 | 1.32 | 65.0% |
| door +x-y (y wall) 2 | 278 | 4.9 | 411.2 | 0.41 | 1.26 | 9.5% |
| door +x-y (x wall) 0 | 599 | 4.9 | 383.7 | 0.95 | 1.26 | 76.9% |
| door +x-y (x wall) 1 | 578 | 4.9 | 399.0 | 0.88 | 1.26 | 65.9% |
| door +x-y (x wall) 2 | 270 | 4.9 | 421.9 | 0.39 | 1.26 | 11.6% |
| door +x-y (corner) | 152 | 30.3 | 418.9 | 0.23 | 1.08 | 5.0% |

Mean flow / w J averaged over the doors 0.66, over the avenues 0.28.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 907 | 594 / 313 / 179 | 0.7 | 380.4 | 2.86 | 4.51 | 87% | 74% | 13% | 3.98 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 536 | 578 / 0 / 14 | 0.7 | 439.5 | 1.35 | 2.11 | 64% | 56% | 9% | 3.61 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 64 | 263 / 0 / 0 | 0.7 | 405.3 | 0.65 | 1.91 | 12% | 12% | 0% | 2.96 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 894 | 607 / 287 / 154 | 0.7 | 383.9 | 2.73 | 4.31 | 87% | 77% | 10% | 3.91 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 546 | 577 / 0 / 14 | 0.7 | 403.0 | 1.47 | 2.31 | 71% | 63% | 7% | 3.81 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 68 | 274 / 0 / 0 | 0.7 | 407.4 | 0.67 | 2.01 | 12% | 10% | 2% | 2.79 |
| corner +x+y | 1.20 | 85.6 | 756 | 150 / 128 / 506 | 0.7 | 407.4 | 1.93 | 4.01 | 98% | 59% | 39% | 2.27 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 902 | 603 / 299 / 187 | 0.7 | 377.3 | 2.89 | 4.51 | 89% | 76% | 13% | 3.99 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 546 | 581 / 0 / 19 | 0.7 | 385.7 | 1.56 | 2.21 | 79% | 64% | 15% | 3.47 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 64 | 293 / 0 / 0 | 0.7 | 405.1 | 0.72 | 1.91 | 15% | 12% | 2% | 2.54 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 895 | 600 / 295 / 161 | 0.7 | 401.8 | 2.63 | 4.31 | 88% | 71% | 17% | 3.73 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 537 | 569 / 0 / 8 | 0.7 | 385.7 | 1.50 | 2.31 | 85% | 67% | 18% | 3.41 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 67 | 265 / 0 / 0 | 0.7 | 412.6 | 0.64 | 2.01 | 10% | 10% | 0% | 3.15 |
| corner -x+y | 1.20 | 85.6 | 746 | 118 / 134 / 521 | 0.7 | 406.5 | 1.90 | 4.11 | 83% | 59% | 24% | 2.56 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 891 | 597 / 294 / 170 | 0.7 | 387.8 | 2.74 | 4.31 | 90% | 74% | 15% | 3.81 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 550 | 587 / 0 / 6 | 0.7 | 377.6 | 1.57 | 2.11 | 76% | 68% | 8% | 3.89 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 65 | 285 / 0 / 0 | 0.7 | 426.9 | 0.67 | 1.91 | 9% | 9% | 0% | 3.10 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 901 | 603 / 298 / 176 | 0.7 | 390.0 | 2.76 | 4.61 | 88% | 72% | 15% | 3.81 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 536 | 584 / 0 / 8 | 0.7 | 401.4 | 1.48 | 2.21 | 71% | 61% | 10% | 3.72 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 66 | 278 / 0 / 0 | 0.7 | 429.0 | 0.65 | 1.91 | 11% | 11% | 0% | 3.04 |
| corner -x-y | 1.20 | 85.6 | 746 | 103 / 126 / 531 | 0.7 | 432.2 | 1.76 | 4.41 | 77% | 59% | 18% | 2.59 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 900 | 602 / 298 / 189 | 0.7 | 383.7 | 2.84 | 5.42 | 87% | 74% | 13% | 3.98 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 532 | 571 / 0 / 8 | 0.7 | 394.2 | 1.47 | 2.21 | 72% | 60% | 12% | 3.65 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 63 | 275 / 0 / 4 | 0.7 | 408.2 | 0.68 | 1.91 | 10% | 7% | 2% | 2.61 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 897 | 599 / 298 / 178 | 0.7 | 380.8 | 2.83 | 4.71 | 85% | 74% | 10% | 3.98 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 546 | 580 / 0 / 8 | 0.7 | 396.0 | 1.49 | 2.21 | 72% | 62% | 10% | 3.77 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 64 | 266 / 0 / 0 | 0.7 | 418.9 | 0.64 | 2.01 | 9% | 9% | 0% | 2.99 |
| corner +x-y | 1.20 | 85.6 | 755 | 149 / 119 / 507 | 0.7 | 415.1 | 1.87 | 4.01 | 83% | 60% | 24% | 2.54 |

The last agent out (agent 393, t100 442.5 s): last gangway straight +x+y (y wing) 1, exit door +x+y (y wall) 1. The gangway that cleared last: straight +x+y (y wing) 1 at 439.5 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.86 | 432.9 / 417.9 / 386.7 | 418.0 / 404.7 / 321.8 | 482475.5 | 1251292 | 0.259 |
| gangway | 1212 | 1112.9 | 6.86 | 429.9 / 411.9 / 342.8 | 418.0 / 404.7 / 321.8 | 481629.0 | 1109177 | 0.140 |
| walkway | 276 | 257.4 | 3.41 | 265.3 / 133.8 / 0.0 | 170.4 / 62.6 / 0.0 | 0.0 | 26351 | 0.757 |
| avenue | 912 | 858.9 | 1.94 | 312.6 / 0.0 / 0.0 | 253.1 / 0.0 / 0.0 | 0.0 | 82991 | 1.326 |
| exit | 32 | 3.2 | 0.00 | 407.4 / 403.7 / 368.9 | 246.3 / 224.4 / 132.1 | 846.4 | 1548 | 1.314 |
| concourse | 1116 | 1043.8 | 2.80 | 385.0 / 15.6 / 0.0 | 229.5 / 8.2 / 0.0 | 0.0 | 31226 | 1.190 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.59 | 399.1 / 380.8 / 341.9 | 395.8 / 374.5 / 337.7 | 465656.6 | 1379231 | 0.062 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 28.5 | 26.5 | gangway | 1.00 | 6.14 | 356.8 | 339.5 | 273.0 | 1599.3 | 0.025 |
| 2 | -26.5 | 29.5 | gangway | 1.00 | 6.08 | 336.5 | 324.8 | 263.6 | 1553.1 | 0.035 |
| 3 | -28.5 | -26.5 | gangway | 1.00 | 6.07 | 341.9 | 321.7 | 256.6 | 1504.6 | 0.032 |
| 4 | -28.5 | 26.5 | gangway | 1.00 | 5.83 | 333.0 | 323.9 | 279.9 | 1504.4 | 0.029 |
| 5 | 27.5 | -28.5 | gangway | 1.00 | 5.76 | 349.1 | 340.0 | 276.5 | 1501.5 | 0.032 |
| 6 | 26.5 | -28.5 | gangway | 1.00 | 5.98 | 342.6 | 337.4 | 279.2 | 1491.6 | 0.029 |
| 7 | 26.5 | -27.5 | gangway | 1.00 | 5.62 | 352.4 | 337.9 | 276.0 | 1489.1 | 0.029 |
| 8 | -28.5 | 27.5 | gangway | 1.00 | 6.03 | 339.8 | 332.8 | 260.3 | 1487.2 | 0.031 |
| 9 | 25.5 | -26.5 | gangway | 0.77 | 6.32 | 354.2 | 351.9 | 320.6 | 1479.5 | 0.025 |
| 10 | -26.5 | 28.5 | gangway | 1.00 | 5.71 | 342.8 | 340.7 | 264.3 | 1472.6 | 0.033 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 26.5 | 24.5 | seat row | 0.50 | 7.41 | 350.9 | 348.9 | 330.7 | 1153.4 | 0.021 |
| 2 | 24.5 | -26.5 | seat row | 0.50 | 7.31 | 350.2 | 348.1 | 337.7 | 1146.9 | 0.019 |
| 3 | 26.5 | -24.5 | seat row | 0.50 | 7.35 | 345.4 | 343.9 | 336.0 | 1144.9 | 0.020 |
| 4 | 24.5 | 26.5 | seat row | 0.50 | 7.36 | 335.8 | 334.6 | 324.8 | 1126.8 | 0.018 |
| 5 | -24.5 | 26.5 | seat row | 0.50 | 7.21 | 341.1 | 337.9 | 323.8 | 1109.2 | 0.019 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1403; agent-steps of seated agents on another row's clearway: 29626.

## Deposit check

Person-seconds deposited: 2633482.7, of them in excluded cells: 2959.063.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 232896 overlapping pair-steps: p99 0.0040, max 0.0706 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0040 max 0.0706; venue-geometry 2: p99 0.0005 max 0.0005 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00754 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 9 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.31 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 590 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
