# Experiment `M_load100_conservative`

**Task 5.9 stage 4: venue M, 100% load, the CONSERVATIVE stair spacing (the Green Guide's planning rate)**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 15832 agents on 100% of the 15832 seats (spawnSeatedCrowd, seed 1337), buffer N = 16384, 3414 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (conservative)** (exit choice: 1328890 evaluations, 53677 switches, 0 forced choices).
Capacity: **within design capacity** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-20T23:26:38, 80.3 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1377 | 240.8 |
| t90 | 2678 | 468.4 |
| t100 | 3414 | 597.1 |

t_p: the step by which ceil(p x 15832) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 829 | 0 | 39.7 | 530.1 | 17.9 | 25.5 | 49.5-59.5 |
| -x | 5.66 | 827 | 0 | 39.7 | 525.8 | 18.0 | 25.5 | 49.5-59.5 |
| +y | 5.66 | 847 | 0 | 39.7 | 529.8 | 18.3 | 26.6 | 143.6-153.6 |
| -y | 5.66 | 838 | 0 | 39.7 | 527.2 | 18.2 | 25.5 | 49.1-59.1 |
| door +x+y (y wall) 0 | 1.20 | 606 | 1121 | 4.9 | 556.6 | 54.9 | 75.2 | 21.5-31.5 |
| door +x+y (y wall) 1 | 1.20 | 603 | 680 | 4.9 | 572.1 | 53.1 | 70.2 | 3.8-13.8 |
| door +x+y (y wall) 2 | 1.20 | 295 | 178 | 4.9 | 587.7 | 25.3 | 80.2 | 10.5-20.5 |
| door +x+y (x wall) 0 | 1.20 | 609 | 1121 | 4.9 | 544.0 | 56.5 | 75.2 | 23.1-33.1 |
| door +x+y (x wall) 1 | 1.20 | 609 | 680 | 4.9 | 568.3 | 54.0 | 75.2 | 17.8-27.8 |
| door +x+y (x wall) 2 | 1.20 | 293 | 178 | 4.9 | 588.2 | 25.1 | 80.2 | 10.5-20.5 |
| door +x+y (corner) | 1.20 | 102 | 0 | 86.9 | 573.9 | 10.5 | 65.2 | 100.7-110.7 |
| door -x+y (y wall) 0 | 1.20 | 600 | 1121 | 4.9 | 547.6 | 55.3 | 75.2 | 21.3-31.3 |
| door -x+y (y wall) 1 | 1.20 | 603 | 680 | 4.9 | 555.5 | 54.7 | 80.2 | 23.4-33.4 |
| door -x+y (y wall) 2 | 1.20 | 288 | 178 | 4.9 | 584.0 | 24.9 | 80.2 | 10.5-20.5 |
| door -x+y (x wall) 0 | 1.20 | 608 | 1121 | 4.9 | 542.4 | 56.5 | 80.2 | 27.6-37.6 |
| door -x+y (x wall) 1 | 1.20 | 594 | 680 | 4.9 | 557.6 | 53.7 | 80.2 | 24.1-34.1 |
| door -x+y (x wall) 2 | 1.20 | 309 | 178 | 4.9 | 594.2 | 26.2 | 80.2 | 10.5-20.5 |
| door -x+y (corner) | 1.20 | 124 | 0 | 84.3 | 570.5 | 12.7 | 80.2 | 498.3-508.3 |
| door -x-y (y wall) 0 | 1.20 | 601 | 1121 | 4.9 | 544.0 | 55.7 | 80.2 | 27.1-37.1 |
| door -x-y (y wall) 1 | 1.20 | 594 | 680 | 4.9 | 562.0 | 53.3 | 75.2 | 27.5-37.4 |
| door -x-y (y wall) 2 | 1.20 | 283 | 178 | 4.9 | 591.9 | 24.1 | 80.2 | 10.5-20.5 |
| door -x-y (x wall) 0 | 1.20 | 604 | 1121 | 4.9 | 547.6 | 55.6 | 80.2 | 27.8-37.8 |
| door -x-y (x wall) 1 | 1.20 | 598 | 680 | 4.9 | 558.5 | 54.0 | 75.2 | 27.5-37.4 |
| door -x-y (x wall) 2 | 1.20 | 292 | 178 | 4.9 | 597.1 | 24.6 | 80.2 | 10.5-20.5 |
| door -x-y (corner) | 1.20 | 148 | 0 | 78.2 | 591.0 | 14.4 | 80.2 | 102.5-112.5 |
| door +x-y (y wall) 0 | 1.20 | 605 | 1121 | 4.9 | 532.2 | 57.3 | 80.2 | 29.7-39.7 |
| door +x-y (y wall) 1 | 1.20 | 597 | 680 | 4.9 | 554.5 | 54.3 | 80.2 | 23.6-33.6 |
| door +x-y (y wall) 2 | 1.20 | 289 | 178 | 4.9 | 571.4 | 25.5 | 80.2 | 10.5-20.5 |
| door +x-y (x wall) 0 | 1.20 | 605 | 1121 | 4.9 | 544.5 | 56.0 | 80.2 | 28.5-38.5 |
| door +x-y (x wall) 1 | 1.20 | 587 | 680 | 4.9 | 542.6 | 54.6 | 80.2 | 23.3-33.2 |
| door +x-y (x wall) 2 | 1.20 | 321 | 178 | 4.9 | 584.0 | 27.7 | 80.2 | 10.5-20.5 |
| door +x-y (corner) | 1.20 | 124 | 0 | 86.1 | 578.2 | 12.6 | 70.2 | 355.2-365.2 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 829 | 5.2% | 17.6% |
| -x | avenue | 5.66 | 827 | 5.2% | 17.6% |
| +y | avenue | 5.66 | 847 | 5.3% | 18.0% |
| -y | avenue | 5.66 | 838 | 5.3% | 17.8% |
| door +x+y (y wall) 0 | door | 1.20 | 606 | 3.8% | 60.7% |
| door +x+y (y wall) 1 | door | 1.20 | 603 | 3.8% | 60.4% |
| door +x+y (y wall) 2 | door | 1.20 | 295 | 1.9% | 29.5% |
| door +x+y (x wall) 0 | door | 1.20 | 609 | 3.8% | 61.0% |
| door +x+y (x wall) 1 | door | 1.20 | 609 | 3.8% | 61.0% |
| door +x+y (x wall) 2 | door | 1.20 | 293 | 1.9% | 29.3% |
| door +x+y (corner) | door | 1.20 | 102 | 0.6% | 10.2% |
| door -x+y (y wall) 0 | door | 1.20 | 600 | 3.8% | 60.1% |
| door -x+y (y wall) 1 | door | 1.20 | 603 | 3.8% | 60.4% |
| door -x+y (y wall) 2 | door | 1.20 | 288 | 1.8% | 28.8% |
| door -x+y (x wall) 0 | door | 1.20 | 608 | 3.8% | 60.9% |
| door -x+y (x wall) 1 | door | 1.20 | 594 | 3.8% | 59.5% |
| door -x+y (x wall) 2 | door | 1.20 | 309 | 2.0% | 30.9% |
| door -x+y (corner) | door | 1.20 | 124 | 0.8% | 12.4% |
| door -x-y (y wall) 0 | door | 1.20 | 601 | 3.8% | 60.2% |
| door -x-y (y wall) 1 | door | 1.20 | 594 | 3.8% | 59.5% |
| door -x-y (y wall) 2 | door | 1.20 | 283 | 1.8% | 28.3% |
| door -x-y (x wall) 0 | door | 1.20 | 604 | 3.8% | 60.5% |
| door -x-y (x wall) 1 | door | 1.20 | 598 | 3.8% | 59.9% |
| door -x-y (x wall) 2 | door | 1.20 | 292 | 1.8% | 29.2% |
| door -x-y (corner) | door | 1.20 | 148 | 0.9% | 14.8% |
| door +x-y (y wall) 0 | door | 1.20 | 605 | 3.8% | 60.6% |
| door +x-y (y wall) 1 | door | 1.20 | 597 | 3.8% | 59.8% |
| door +x-y (y wall) 2 | door | 1.20 | 289 | 1.8% | 28.9% |
| door +x-y (x wall) 0 | door | 1.20 | 605 | 3.8% | 60.6% |
| door +x-y (x wall) 1 | door | 1.20 | 587 | 3.7% | 58.8% |
| door +x-y (x wall) 2 | door | 1.20 | 321 | 2.0% | 32.2% |
| door +x-y (corner) | door | 1.20 | 124 | 0.8% | 12.4% |
| **doors (28)** | door | 33.60 | 12491 | 78.9% | |
| **avenues (4)** | avenue | 22.64 | 3341 | 21.1% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 597.1 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 33.8%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 963 | 6.1% | 963 | 6.1% |
| straight +x+y (y wing) 1 | straight | yes | 606 | 3.8% | 603 | 3.8% |
| straight +x+y (y wing) 2 | straight | yes | 296 | 1.9% | 296 | 1.9% |
| straight +x+y (x wing) 0 | straight | yes | 952 | 6.0% | 952 | 6.0% |
| straight +x+y (x wing) 1 | straight | yes | 612 | 3.9% | 609 | 3.8% |
| straight +x+y (x wing) 2 | straight | yes | 293 | 1.9% | 293 | 1.9% |
| corner +x+y | corner | yes | 785 | 5.0% | 242 | 1.5% |
| straight -x+y (y wing) 0 | straight | yes | 951 | 6.0% | 951 | 6.0% |
| straight -x+y (y wing) 1 | straight | yes | 611 | 3.9% | 605 | 3.8% |
| straight -x+y (y wing) 2 | straight | yes | 286 | 1.8% | 286 | 1.8% |
| straight -x+y (x wing) 0 | straight | yes | 954 | 6.0% | 954 | 6.0% |
| straight -x+y (x wing) 1 | straight | yes | 602 | 3.8% | 597 | 3.8% |
| straight -x+y (x wing) 2 | straight | yes | 306 | 1.9% | 306 | 1.9% |
| corner -x+y | corner | yes | 777 | 4.9% | 259 | 1.6% |
| straight -x-y (y wing) 0 | straight | yes | 952 | 6.0% | 952 | 6.0% |
| straight -x-y (y wing) 1 | straight | yes | 601 | 3.8% | 594 | 3.8% |
| straight -x-y (y wing) 2 | straight | yes | 282 | 1.8% | 282 | 1.8% |
| straight -x-y (x wing) 0 | straight | yes | 951 | 6.0% | 951 | 6.0% |
| straight -x-y (x wing) 1 | straight | yes | 605 | 3.8% | 598 | 3.8% |
| straight -x-y (x wing) 2 | straight | yes | 292 | 1.8% | 292 | 1.8% |
| corner -x-y | corner | yes | 789 | 5.0% | 289 | 1.8% |
| straight +x-y (y wing) 0 | straight | yes | 953 | 6.0% | 953 | 6.0% |
| straight +x-y (y wing) 1 | straight | yes | 605 | 3.8% | 597 | 3.8% |
| straight +x-y (y wing) 2 | straight | yes | 288 | 1.8% | 288 | 1.8% |
| straight +x-y (x wing) 0 | straight | yes | 947 | 6.0% | 947 | 6.0% |
| straight +x-y (x wing) 1 | straight | yes | 597 | 3.8% | 587 | 3.7% |
| straight +x-y (x wing) 2 | straight | yes | 321 | 2.0% | 321 | 2.0% |
| corner +x-y | corner | yes | 814 | 5.1% | 265 | 1.7% |
| **straight (24)** | | | 14826 | | 14777 | 93.3% |
| **corner (4)** | | | 3165 | | 1055 | 6.7% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 829 | 39.7 | 530.1 | 0.21 | 0.31 | 0.0% |
| -x | 827 | 39.7 | 525.8 | 0.22 | 0.31 | 0.0% |
| +y | 847 | 39.7 | 529.8 | 0.22 | 0.32 | 0.0% |
| -y | 838 | 39.7 | 527.2 | 0.22 | 0.31 | 0.0% |
| door +x+y (y wall) 0 | 606 | 4.9 | 556.6 | 0.66 | 0.90 | 7.1% |
| door +x+y (y wall) 1 | 603 | 4.9 | 572.1 | 0.64 | 0.84 | 5.2% |
| door +x+y (y wall) 2 | 295 | 4.9 | 587.7 | 0.30 | 0.96 | 3.4% |
| door +x+y (x wall) 0 | 609 | 4.9 | 544.0 | 0.68 | 0.90 | 7.3% |
| door +x+y (x wall) 1 | 609 | 4.9 | 568.3 | 0.65 | 0.90 | 3.5% |
| door +x+y (x wall) 2 | 293 | 4.9 | 588.2 | 0.30 | 0.96 | 3.4% |
| door +x+y (corner) | 102 | 86.9 | 573.9 | 0.13 | 0.78 | 0.0% |
| door -x+y (y wall) 0 | 600 | 4.9 | 547.6 | 0.66 | 0.90 | 3.6% |
| door -x+y (y wall) 1 | 603 | 4.9 | 555.5 | 0.65 | 0.96 | 8.9% |
| door -x+y (y wall) 2 | 288 | 4.9 | 584.0 | 0.30 | 0.96 | 3.4% |
| door -x+y (x wall) 0 | 608 | 4.9 | 542.4 | 0.68 | 0.96 | 7.3% |
| door -x+y (x wall) 1 | 594 | 4.9 | 557.6 | 0.64 | 0.96 | 3.6% |
| door -x+y (x wall) 2 | 309 | 4.9 | 594.2 | 0.31 | 0.96 | 3.3% |
| door -x+y (corner) | 124 | 84.3 | 570.5 | 0.15 | 0.96 | 2.0% |
| door -x-y (y wall) 0 | 601 | 4.9 | 544.0 | 0.67 | 0.96 | 5.5% |
| door -x-y (y wall) 1 | 594 | 4.9 | 562.0 | 0.64 | 0.90 | 5.3% |
| door -x-y (y wall) 2 | 283 | 4.9 | 591.9 | 0.29 | 0.96 | 3.3% |
| door -x-y (x wall) 0 | 604 | 4.9 | 547.6 | 0.67 | 0.96 | 9.1% |
| door -x-y (x wall) 1 | 598 | 4.9 | 558.5 | 0.65 | 0.90 | 3.5% |
| door -x-y (x wall) 2 | 292 | 4.9 | 597.1 | 0.29 | 0.96 | 3.3% |
| door -x-y (corner) | 148 | 78.2 | 591.0 | 0.17 | 0.96 | 3.8% |
| door +x-y (y wall) 0 | 605 | 4.9 | 532.2 | 0.69 | 0.96 | 7.4% |
| door +x-y (y wall) 1 | 597 | 4.9 | 554.5 | 0.65 | 0.96 | 7.1% |
| door +x-y (y wall) 2 | 289 | 4.9 | 571.4 | 0.31 | 0.96 | 3.4% |
| door +x-y (x wall) 0 | 605 | 4.9 | 544.5 | 0.67 | 0.96 | 9.1% |
| door +x-y (x wall) 1 | 587 | 4.9 | 542.6 | 0.65 | 0.96 | 7.3% |
| door +x-y (x wall) 2 | 321 | 4.9 | 584.0 | 0.33 | 0.96 | 3.4% |
| door +x-y (corner) | 124 | 86.1 | 578.2 | 0.15 | 0.84 | 2.0% |

Mean flow / w J averaged over the doors 0.48, over the avenues 0.22.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 963 | 606 / 358 / 260 | 0.7 | 553.6 | 2.21 | 3.81 | 89% | 79% | 11% | 3.70 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 553 | 603 / 0 / 4 | 0.7 | 569.1 | 1.07 | 1.40 | 78% | 62% | 16% | 3.48 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 71 | 296 / 0 / 0 | 0.7 | 584.7 | 0.51 | 1.40 | 12% | 8% | 3% | 2.61 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 952 | 609 / 343 / 250 | 0.7 | 541.0 | 2.22 | 4.01 | 89% | 80% | 9% | 3.84 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 569 | 609 / 0 / 5 | 0.7 | 565.3 | 1.09 | 1.50 | 79% | 61% | 18% | 3.45 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 70 | 293 / 0 / 0 | 0.7 | 585.2 | 0.50 | 1.40 | 12% | 8% | 3% | 2.56 |
| corner +x+y | 1.20 | 85.6 | 780 | 101 / 141 / 547 | 0.7 | 579.3 | 1.36 | 4.01 | 86% | 58% | 29% | 2.38 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 951 | 600 / 351 / 276 | 0.7 | 544.7 | 2.25 | 4.11 | 91% | 80% | 11% | 3.69 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 572 | 605 / 0 / 9 | 0.7 | 552.5 | 1.11 | 1.40 | 82% | 66% | 16% | 3.49 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 70 | 286 / 0 / 0 | 0.7 | 581.0 | 0.49 | 1.40 | 12% | 10% | 2% | 2.61 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 954 | 608 / 346 / 248 | 0.7 | 539.4 | 2.23 | 3.31 | 91% | 80% | 11% | 3.70 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 574 | 597 / 0 / 7 | 0.7 | 554.6 | 1.09 | 1.50 | 88% | 70% | 18% | 3.31 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 70 | 306 / 0 / 0 | 0.7 | 591.2 | 0.52 | 1.40 | 12% | 10% | 2% | 2.63 |
| corner -x+y | 1.20 | 85.6 | 767 | 124 / 135 / 524 | 0.7 | 585.1 | 1.34 | 3.51 | 85% | 56% | 29% | 2.37 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 952 | 601 / 351 / 222 | 0.7 | 541.0 | 2.17 | 3.81 | 89% | 78% | 11% | 3.81 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 567 | 594 / 0 / 9 | 0.7 | 559.0 | 1.08 | 1.40 | 84% | 67% | 18% | 3.47 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 70 | 282 / 0 / 0 | 0.7 | 588.9 | 0.48 | 1.40 | 12% | 8% | 3% | 2.57 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 951 | 604 / 347 / 228 | 0.7 | 544.7 | 2.17 | 3.21 | 91% | 80% | 11% | 3.72 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 571 | 598 / 0 / 7 | 0.7 | 555.5 | 1.09 | 1.40 | 86% | 71% | 14% | 3.51 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 70 | 292 / 0 / 0 | 0.7 | 594.2 | 0.49 | 1.40 | 12% | 8% | 3% | 2.60 |
| corner -x-y | 1.20 | 85.6 | 777 | 149 / 140 / 504 | 0.7 | 588.2 | 1.35 | 4.61 | 86% | 58% | 29% | 2.36 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 953 | 605 / 348 / 239 | 0.7 | 529.3 | 2.25 | 3.61 | 91% | 80% | 11% | 3.70 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 560 | 597 / 0 / 9 | 0.7 | 551.5 | 1.10 | 1.50 | 82% | 66% | 16% | 3.42 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 70 | 288 / 0 / 0 | 0.7 | 568.4 | 0.51 | 1.50 | 10% | 9% | 2% | 2.74 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 947 | 605 / 342 / 226 | 0.7 | 541.5 | 2.17 | 3.41 | 82% | 80% | 2% | 4.03 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 559 | 587 / 0 / 52 | 0.7 | 539.6 | 1.19 | 2.41 | 82% | 65% | 16% | 3.42 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 70 | 321 / 0 / 0 | 0.7 | 581.0 | 0.55 | 1.40 | 12% | 10% | 2% | 2.60 |
| corner +x-y | 1.20 | 85.6 | 799 | 125 / 140 / 595 | 0.7 | 574.9 | 1.50 | 3.41 | 86% | 59% | 28% | 2.38 |

The last agent out (agent 8333, t100 597.1 s): last gangway straight -x-y (x wing) 2, exit door -x-y (x wall) 2. The gangway that cleared last: straight -x-y (x wing) 2 at 594.2 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.95 | 589.4 / 577.0 / 546.6 | 570.9 / 526.3 / 459.3 | 769019.3 | 1694092 | 0.206 |
| gangway | 1212 | 1112.9 | 6.95 | 586.8 / 567.6 / 489.9 | 570.9 / 526.3 / 459.3 | 768151.5 | 1538733 | 0.103 |
| walkway | 276 | 257.4 | 3.16 | 169.8 / 102.3 / 0.0 | 124.0 / 36.4 / 0.0 | 0.0 | 26446 | 0.888 |
| avenue | 912 | 858.9 | 1.85 | 180.3 / 0.0 / 0.0 | 153.7 / 0.0 / 0.0 | 0.0 | 95908 | 1.328 |
| exit | 32 | 3.2 | 0.00 | 556.9 / 553.8 / 489.9 | 255.4 / 230.0 / 134.7 | 867.8 | 1665 | 1.326 |
| concourse | 1116 | 1043.8 | 1.96 | 512.8 / 0.0 / 0.0 | 102.1 / 0.0 / 0.0 | 0.0 | 31341 | 1.197 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.57 | 512.3 / 506.2 / 496.9 | 508.5 / 506.2 / 491.3 | 845175.9 | 2276105 | 0.039 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 26.5 | 27.5 | gangway | 1.00 | 6.14 | 510.2 | 492.4 | 439.7 | 2530.6 | 0.017 |
| 2 | -29.5 | -26.5 | gangway | 1.00 | 6.19 | 500.2 | 477.7 | 428.3 | 2475.1 | 0.019 |
| 3 | 26.5 | 28.5 | gangway | 1.00 | 5.91 | 500.9 | 482.6 | 421.9 | 2427.4 | 0.021 |
| 4 | 27.5 | -27.5 | gangway | 1.00 | 5.92 | 498.1 | 493.9 | 429.4 | 2402.2 | 0.017 |
| 5 | 26.5 | 29.5 | gangway | 1.00 | 6.06 | 488.7 | 448.5 | 405.3 | 2380.8 | 0.022 |
| 6 | 26.5 | -28.5 | gangway | 1.00 | 6.02 | 498.5 | 481.2 | 409.6 | 2372.7 | 0.023 |
| 7 | -26.5 | 28.5 | gangway | 1.00 | 6.09 | 510.2 | 490.8 | 404.2 | 2369.9 | 0.019 |
| 8 | -26.5 | 29.5 | gangway | 1.00 | 5.89 | 512.7 | 480.1 | 411.7 | 2356.3 | 0.019 |
| 9 | 26.5 | -27.5 | gangway | 1.00 | 6.02 | 505.8 | 493.4 | 412.1 | 2355.5 | 0.021 |
| 10 | 27.5 | 26.5 | gangway | 1.00 | 5.59 | 506.0 | 498.1 | 430.6 | 2350.4 | 0.017 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -26.5 | -24.5 | seat row | 0.50 | 7.39 | 503.7 | 501.8 | 488.9 | 1732.2 | 0.012 |
| 2 | 24.5 | 26.5 | seat row | 0.50 | 7.29 | 506.2 | 502.9 | 488.5 | 1713.5 | 0.012 |
| 3 | -24.5 | -26.5 | seat row | 0.50 | 7.30 | 508.5 | 503.7 | 491.3 | 1700.4 | 0.013 |
| 4 | 26.5 | -24.5 | seat row | 0.50 | 7.28 | 507.4 | 506.2 | 487.3 | 1693.7 | 0.014 |
| 5 | 24.5 | -26.5 | seat row | 0.50 | 7.21 | 488.7 | 487.3 | 479.1 | 1658.7 | 0.014 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1953; agent-steps of seated agents on another row's clearway: 18876.

## Deposit check

Person-seconds deposited: 3973273.8, of them in excluded cells: 3076.954.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 419368 overlapping pair-steps: p99 0.0022, max 0.0282 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0022 max 0.0282; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 21 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.26 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 610 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
