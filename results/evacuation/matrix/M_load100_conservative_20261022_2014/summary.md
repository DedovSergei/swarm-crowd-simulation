# Experiment `M_load100_conservative`

**Task 5.10 stage 4 (AMD 26.10.1): venue M, 100% load, the CONSERVATIVE stair spacing (the Green Guide's planning rate)**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 15832 agents on 100% of the 15832 seats (spawnSeatedCrowd, seed 1337), buffer N = 16384, 3379 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (conservative)** (exit choice: 1330755 evaluations, 53311 switches, 0 forced choices).
Capacity: **within design capacity** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T20:14:06, 240.1 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1380 | 241.4 |
| t90 | 2678 | 468.4 |
| t100 | 3379 | 591.0 |

t_p: the step by which ceil(p x 15832) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 840 | 0 | 39.7 | 528.6 | 18.2 | 25.5 | 49.7-59.6 |
| -x | 5.66 | 843 | 0 | 39.7 | 525.9 | 18.4 | 25.5 | 49.5-59.5 |
| +y | 5.66 | 836 | 0 | 39.7 | 530.7 | 18.0 | 26.6 | 49.7-59.6 |
| -y | 5.66 | 835 | 0 | 39.7 | 531.5 | 18.0 | 25.5 | 49.5-59.5 |
| door +x+y (y wall) 0 | 1.20 | 614 | 1121 | 4.9 | 530.0 | 58.4 | 85.3 | 25.9-35.9 |
| door +x+y (y wall) 1 | 1.20 | 590 | 680 | 4.9 | 541.7 | 54.9 | 85.3 | 25.9-35.9 |
| door +x+y (y wall) 2 | 1.20 | 291 | 178 | 4.9 | 573.2 | 25.6 | 80.2 | 10.1-20.1 |
| door +x+y (x wall) 0 | 1.20 | 608 | 1121 | 4.9 | 527.2 | 58.2 | 80.2 | 23.8-33.8 |
| door +x+y (x wall) 1 | 1.20 | 595 | 680 | 4.9 | 546.8 | 54.9 | 75.2 | 19.2-29.2 |
| door +x+y (x wall) 2 | 1.20 | 295 | 178 | 4.9 | 578.6 | 25.7 | 80.2 | 10.1-20.1 |
| door +x+y (corner) | 1.20 | 130 | 0 | 63.7 | 567.2 | 12.9 | 85.3 | 354.7-364.7 |
| door -x+y (y wall) 0 | 1.20 | 605 | 1121 | 4.9 | 546.4 | 55.8 | 80.2 | 25.7-35.7 |
| door -x+y (y wall) 1 | 1.20 | 605 | 680 | 4.9 | 562.0 | 54.3 | 80.2 | 25.7-35.7 |
| door -x+y (y wall) 2 | 1.20 | 305 | 178 | 4.9 | 590.8 | 26.0 | 80.2 | 10.1-20.1 |
| door -x+y (x wall) 0 | 1.20 | 608 | 1121 | 4.9 | 547.6 | 56.0 | 85.3 | 27.3-37.3 |
| door -x+y (x wall) 1 | 1.20 | 599 | 680 | 4.9 | 562.8 | 53.7 | 80.2 | 27.1-37.1 |
| door -x+y (x wall) 2 | 1.20 | 281 | 178 | 4.9 | 577.7 | 24.5 | 80.2 | 10.1-20.1 |
| door -x+y (corner) | 1.20 | 112 | 0 | 87.3 | 587.0 | 11.2 | 90.3 | 407.5-417.5 |
| door -x-y (y wall) 0 | 1.20 | 612 | 1121 | 4.9 | 544.8 | 56.7 | 80.2 | 25.4-35.3 |
| door -x-y (y wall) 1 | 1.20 | 605 | 680 | 4.9 | 568.1 | 53.7 | 85.3 | 23.8-33.8 |
| door -x-y (y wall) 2 | 1.20 | 309 | 178 | 4.9 | 580.9 | 26.8 | 80.2 | 10.1-20.1 |
| door -x-y (x wall) 0 | 1.20 | 611 | 1121 | 4.9 | 530.0 | 58.2 | 85.3 | 27.3-37.3 |
| door -x-y (x wall) 1 | 1.20 | 608 | 680 | 4.9 | 570.0 | 53.8 | 85.3 | 23.8-33.8 |
| door -x-y (x wall) 2 | 1.20 | 301 | 178 | 4.9 | 591.0 | 25.7 | 80.2 | 10.1-20.1 |
| door -x-y (corner) | 1.20 | 77 | 0 | 84.1 | 571.4 | 7.9 | 60.2 | 91.5-101.4 |
| door +x-y (y wall) 0 | 1.20 | 609 | 1121 | 4.9 | 547.5 | 56.1 | 85.3 | 27.3-37.3 |
| door +x-y (y wall) 1 | 1.20 | 609 | 680 | 4.9 | 553.2 | 55.5 | 80.2 | 25.5-35.5 |
| door +x-y (y wall) 2 | 1.20 | 309 | 178 | 4.9 | 583.3 | 26.7 | 80.2 | 10.1-20.1 |
| door +x-y (x wall) 0 | 1.20 | 608 | 1121 | 4.9 | 553.6 | 55.4 | 85.3 | 27.3-37.3 |
| door +x-y (x wall) 1 | 1.20 | 599 | 680 | 4.9 | 552.4 | 54.7 | 75.2 | 25.7-35.7 |
| door +x-y (x wall) 2 | 1.20 | 285 | 178 | 4.9 | 581.7 | 24.7 | 80.2 | 10.1-20.1 |
| door +x-y (corner) | 1.20 | 98 | 0 | 90.1 | 570.7 | 10.2 | 65.2 | 101.8-111.8 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 840 | 5.3% | 18.0% |
| -x | avenue | 5.66 | 843 | 5.3% | 18.1% |
| +y | avenue | 5.66 | 836 | 5.3% | 17.9% |
| -y | avenue | 5.66 | 835 | 5.3% | 17.9% |
| door +x+y (y wall) 0 | door | 1.20 | 614 | 3.9% | 62.1% |
| door +x+y (y wall) 1 | door | 1.20 | 590 | 3.7% | 59.7% |
| door +x+y (y wall) 2 | door | 1.20 | 291 | 1.8% | 29.4% |
| door +x+y (x wall) 0 | door | 1.20 | 608 | 3.8% | 61.5% |
| door +x+y (x wall) 1 | door | 1.20 | 595 | 3.8% | 60.2% |
| door +x+y (x wall) 2 | door | 1.20 | 295 | 1.9% | 29.9% |
| door +x+y (corner) | door | 1.20 | 130 | 0.8% | 13.2% |
| door -x+y (y wall) 0 | door | 1.20 | 605 | 3.8% | 61.2% |
| door -x+y (y wall) 1 | door | 1.20 | 605 | 3.8% | 61.2% |
| door -x+y (y wall) 2 | door | 1.20 | 305 | 1.9% | 30.9% |
| door -x+y (x wall) 0 | door | 1.20 | 608 | 3.8% | 61.5% |
| door -x+y (x wall) 1 | door | 1.20 | 599 | 3.8% | 60.6% |
| door -x+y (x wall) 2 | door | 1.20 | 281 | 1.8% | 28.4% |
| door -x+y (corner) | door | 1.20 | 112 | 0.7% | 11.3% |
| door -x-y (y wall) 0 | door | 1.20 | 612 | 3.9% | 61.9% |
| door -x-y (y wall) 1 | door | 1.20 | 605 | 3.8% | 61.2% |
| door -x-y (y wall) 2 | door | 1.20 | 309 | 2.0% | 31.3% |
| door -x-y (x wall) 0 | door | 1.20 | 611 | 3.9% | 61.8% |
| door -x-y (x wall) 1 | door | 1.20 | 608 | 3.8% | 61.5% |
| door -x-y (x wall) 2 | door | 1.20 | 301 | 1.9% | 30.5% |
| door -x-y (corner) | door | 1.20 | 77 | 0.5% | 7.8% |
| door +x-y (y wall) 0 | door | 1.20 | 609 | 3.8% | 61.6% |
| door +x-y (y wall) 1 | door | 1.20 | 609 | 3.8% | 61.6% |
| door +x-y (y wall) 2 | door | 1.20 | 309 | 2.0% | 31.3% |
| door +x-y (x wall) 0 | door | 1.20 | 608 | 3.8% | 61.5% |
| door +x-y (x wall) 1 | door | 1.20 | 599 | 3.8% | 60.6% |
| door +x-y (x wall) 2 | door | 1.20 | 285 | 1.8% | 28.8% |
| door +x-y (corner) | door | 1.20 | 98 | 0.6% | 9.9% |
| **doors (28)** | door | 33.60 | 12478 | 78.8% | |
| **avenues (4)** | avenue | 22.64 | 3354 | 21.2% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 591.0 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 34.2%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 958 | 6.1% | 958 | 6.1% |
| straight +x+y (y wing) 1 | straight | yes | 595 | 3.8% | 590 | 3.7% |
| straight +x+y (y wing) 2 | straight | yes | 292 | 1.8% | 291 | 1.8% |
| straight +x+y (x wing) 0 | straight | yes | 959 | 6.1% | 959 | 6.1% |
| straight +x+y (x wing) 1 | straight | yes | 597 | 3.8% | 595 | 3.8% |
| straight +x+y (x wing) 2 | straight | yes | 296 | 1.9% | 296 | 1.9% |
| corner +x+y | corner | yes | 787 | 5.0% | 269 | 1.7% |
| straight -x+y (y wing) 0 | straight | yes | 952 | 6.0% | 952 | 6.0% |
| straight -x+y (y wing) 1 | straight | yes | 608 | 3.8% | 605 | 3.8% |
| straight -x+y (y wing) 2 | straight | yes | 305 | 1.9% | 305 | 1.9% |
| straight -x+y (x wing) 0 | straight | yes | 961 | 6.1% | 961 | 6.1% |
| straight -x+y (x wing) 1 | straight | yes | 600 | 3.8% | 599 | 3.8% |
| straight -x+y (x wing) 2 | straight | yes | 281 | 1.8% | 281 | 1.8% |
| corner -x+y | corner | yes | 781 | 4.9% | 255 | 1.6% |
| straight -x-y (y wing) 0 | straight | yes | 959 | 6.1% | 959 | 6.1% |
| straight -x-y (y wing) 1 | straight | yes | 606 | 3.8% | 605 | 3.8% |
| straight -x-y (y wing) 2 | straight | yes | 309 | 2.0% | 309 | 2.0% |
| straight -x-y (x wing) 0 | straight | yes | 965 | 6.1% | 965 | 6.1% |
| straight -x-y (x wing) 1 | straight | yes | 612 | 3.9% | 611 | 3.9% |
| straight -x-y (x wing) 2 | straight | yes | 298 | 1.9% | 298 | 1.9% |
| corner -x-y | corner | yes | 767 | 4.8% | 211 | 1.3% |
| straight +x-y (y wing) 0 | straight | yes | 954 | 6.0% | 954 | 6.0% |
| straight +x-y (y wing) 1 | straight | yes | 611 | 3.9% | 609 | 3.8% |
| straight +x-y (y wing) 2 | straight | yes | 309 | 2.0% | 309 | 2.0% |
| straight +x-y (x wing) 0 | straight | yes | 961 | 6.1% | 961 | 6.1% |
| straight +x-y (x wing) 1 | straight | yes | 603 | 3.8% | 599 | 3.8% |
| straight +x-y (x wing) 2 | straight | yes | 285 | 1.8% | 285 | 1.8% |
| corner +x-y | corner | yes | 783 | 4.9% | 241 | 1.5% |
| **straight (24)** | | | 14876 | | 14856 | 93.8% |
| **corner (4)** | | | 3118 | | 976 | 6.2% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 840 | 39.7 | 528.6 | 0.22 | 0.31 | 0.0% |
| -x | 843 | 39.7 | 525.9 | 0.22 | 0.31 | 0.0% |
| +y | 836 | 39.7 | 530.7 | 0.22 | 0.32 | 0.0% |
| -y | 835 | 39.7 | 531.5 | 0.22 | 0.31 | 0.0% |
| door +x+y (y wall) 0 | 614 | 4.9 | 530.0 | 0.70 | 1.02 | 13.0% |
| door +x+y (y wall) 1 | 590 | 4.9 | 541.7 | 0.66 | 1.02 | 7.3% |
| door +x+y (y wall) 2 | 291 | 4.9 | 573.2 | 0.31 | 0.96 | 1.7% |
| door +x+y (x wall) 0 | 608 | 4.9 | 527.2 | 0.70 | 0.96 | 7.5% |
| door +x+y (x wall) 1 | 595 | 4.9 | 546.8 | 0.66 | 0.90 | 5.5% |
| door +x+y (x wall) 2 | 295 | 4.9 | 578.6 | 0.31 | 0.96 | 1.7% |
| door +x+y (corner) | 130 | 63.7 | 567.2 | 0.15 | 1.02 | 0.0% |
| door -x+y (y wall) 0 | 605 | 4.9 | 546.4 | 0.67 | 0.96 | 1.8% |
| door -x+y (y wall) 1 | 605 | 4.9 | 562.0 | 0.65 | 0.96 | 3.5% |
| door -x+y (y wall) 2 | 305 | 4.9 | 590.8 | 0.31 | 0.96 | 1.7% |
| door -x+y (x wall) 0 | 608 | 4.9 | 547.6 | 0.67 | 1.02 | 5.5% |
| door -x+y (x wall) 1 | 599 | 4.9 | 562.8 | 0.64 | 0.96 | 3.5% |
| door -x+y (x wall) 2 | 281 | 4.9 | 577.7 | 0.29 | 0.96 | 1.7% |
| door -x+y (corner) | 112 | 87.3 | 587.0 | 0.13 | 1.08 | 2.0% |
| door -x-y (y wall) 0 | 612 | 4.9 | 544.8 | 0.68 | 0.96 | 9.1% |
| door -x-y (y wall) 1 | 605 | 4.9 | 568.1 | 0.64 | 1.02 | 5.3% |
| door -x-y (y wall) 2 | 309 | 4.9 | 580.9 | 0.32 | 0.96 | 1.7% |
| door -x-y (x wall) 0 | 611 | 4.9 | 530.0 | 0.70 | 1.02 | 13.0% |
| door -x-y (x wall) 1 | 608 | 4.9 | 570.0 | 0.64 | 1.02 | 1.7% |
| door -x-y (x wall) 2 | 301 | 4.9 | 591.0 | 0.31 | 0.96 | 1.7% |
| door -x-y (corner) | 77 | 84.1 | 571.4 | 0.09 | 0.72 | 0.0% |
| door +x-y (y wall) 0 | 609 | 4.9 | 547.5 | 0.67 | 1.02 | 5.5% |
| door +x-y (y wall) 1 | 609 | 4.9 | 553.2 | 0.66 | 0.96 | 7.1% |
| door +x-y (y wall) 2 | 309 | 4.9 | 583.3 | 0.32 | 0.96 | 1.7% |
| door +x-y (x wall) 0 | 608 | 4.9 | 553.6 | 0.66 | 1.02 | 7.1% |
| door +x-y (x wall) 1 | 599 | 4.9 | 552.4 | 0.65 | 0.90 | 5.4% |
| door +x-y (x wall) 2 | 285 | 4.9 | 581.7 | 0.30 | 0.96 | 1.7% |
| door +x-y (corner) | 98 | 90.1 | 570.7 | 0.12 | 0.78 | 0.0% |

Mean flow / w J averaged over the doors 0.49, over the avenues 0.22.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 958 | 614 / 344 / 213 | 0.7 | 527.0 | 2.22 | 3.41 | 85% | 83% | 2% | 4.12 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 562 | 590 / 0 / 28 | 0.7 | 538.7 | 1.15 | 2.31 | 82% | 65% | 16% | 3.46 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 69 | 291 / 0 / 1 | 0.7 | 570.2 | 0.51 | 1.40 | 12% | 10% | 2% | 2.58 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 959 | 608 / 351 / 245 | 0.7 | 524.2 | 2.30 | 3.81 | 85% | 83% | 2% | 4.01 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 557 | 595 / 0 / 3 | 0.7 | 543.8 | 1.10 | 1.40 | 84% | 67% | 16% | 3.40 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 70 | 296 / 0 / 0 | 0.7 | 575.6 | 0.51 | 1.40 | 12% | 10% | 2% | 2.54 |
| corner +x+y | 1.20 | 85.6 | 783 | 129 / 140 / 546 | 0.7 | 569.5 | 1.43 | 3.31 | 86% | 55% | 31% | 2.32 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 952 | 605 / 347 / 261 | 0.7 | 543.4 | 2.23 | 3.41 | 91% | 80% | 11% | 3.75 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 568 | 605 / 0 / 4 | 0.7 | 559.0 | 1.09 | 1.50 | 84% | 67% | 18% | 3.45 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 70 | 305 / 0 / 0 | 0.7 | 587.9 | 0.52 | 1.40 | 12% | 10% | 2% | 2.55 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 961 | 608 / 353 / 260 | 0.7 | 544.7 | 2.24 | 3.41 | 87% | 78% | 9% | 3.85 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 559 | 599 / 0 / 2 | 0.7 | 559.9 | 1.07 | 1.40 | 79% | 65% | 14% | 3.53 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 70 | 281 / 0 / 0 | 0.7 | 574.7 | 0.49 | 1.40 | 12% | 10% | 2% | 2.52 |
| corner -x+y | 1.20 | 85.6 | 778 | 112 / 143 / 529 | 0.7 | 583.1 | 1.35 | 4.01 | 86% | 54% | 32% | 2.32 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 959 | 612 / 347 / 223 | 0.7 | 541.9 | 2.18 | 3.31 | 91% | 78% | 13% | 3.73 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 565 | 605 / 0 / 1 | 0.7 | 565.1 | 1.07 | 1.50 | 82% | 63% | 19% | 3.33 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 70 | 309 / 0 / 0 | 0.7 | 577.9 | 0.54 | 1.40 | 12% | 10% | 2% | 2.52 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 965 | 611 / 354 / 238 | 0.7 | 527.2 | 2.28 | 3.31 | 91% | 81% | 9% | 3.89 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 563 | 611 / 0 / 3 | 0.7 | 567.0 | 1.08 | 1.50 | 81% | 67% | 14% | 3.51 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 70 | 298 / 0 / 0 | 0.7 | 588.0 | 0.51 | 1.40 | 12% | 10% | 2% | 2.51 |
| corner -x-y | 1.20 | 85.6 | 766 | 77 / 134 / 559 | 0.7 | 582.1 | 1.32 | 3.51 | 86% | 63% | 24% | 2.44 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 954 | 609 / 345 / 248 | 0.7 | 544.5 | 2.21 | 3.41 | 87% | 80% | 7% | 3.89 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 567 | 609 / 0 / 7 | 0.7 | 550.3 | 1.12 | 1.60 | 84% | 66% | 18% | 3.37 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 69 | 309 / 0 / 0 | 0.7 | 580.3 | 0.53 | 1.40 | 12% | 10% | 2% | 2.54 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 961 | 608 / 353 / 259 | 0.7 | 550.6 | 2.22 | 3.71 | 91% | 79% | 12% | 3.69 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 562 | 599 / 0 / 9 | 0.7 | 549.4 | 1.11 | 1.40 | 80% | 64% | 16% | 3.40 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 69 | 285 / 0 / 0 | 0.7 | 578.8 | 0.49 | 1.40 | 12% | 10% | 2% | 2.58 |
| corner +x-y | 1.20 | 85.6 | 776 | 98 / 143 / 551 | 0.7 | 574.2 | 1.38 | 3.81 | 86% | 53% | 33% | 2.33 |

The last agent out (agent 10385, t100 591.0 s): last gangway straight -x-y (x wing) 2, exit door -x-y (x wall) 2. The gangway that cleared last: straight -x-y (x wing) 2 at 588.0 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.76 | 584.9 / 572.8 / 546.6 | 569.0 / 534.2 / 471.4 | 748770.4 | 1692932 | 0.205 |
| gangway | 1212 | 1112.9 | 6.76 | 581.6 / 566.5 / 493.9 | 569.0 / 534.2 / 471.4 | 747901.9 | 1537430 | 0.102 |
| walkway | 276 | 257.4 | 3.24 | 172.5 / 101.4 / 0.0 | 130.1 / 34.1 / 0.0 | 0.0 | 26350 | 0.896 |
| avenue | 912 | 858.9 | 2.14 | 185.6 / 0.0 / 0.0 | 160.7 / 0.0 / 0.0 | 0.0 | 96280 | 1.328 |
| exit | 32 | 3.2 | 0.00 | 556.2 / 553.6 / 493.2 | 256.8 / 230.5 / 135.6 | 868.4 | 1651 | 1.327 |
| concourse | 1116 | 1043.8 | 1.97 | 529.8 / 0.0 / 0.0 | 104.4 / 0.0 / 0.0 | 0.0 | 31220 | 1.196 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.55 | 527.2 / 505.8 / 492.7 | 508.5 / 505.5 / 489.0 | 847793.9 | 2282958 | 0.038 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -26.5 | -27.5 | gangway | 1.00 | 6.14 | 512.0 | 506.4 | 443.2 | 2539.9 | 0.015 |
| 2 | -27.5 | -26.5 | gangway | 1.00 | 6.01 | 527.5 | 507.9 | 443.4 | 2530.3 | 0.017 |
| 3 | -27.5 | -27.5 | gangway | 1.00 | 5.83 | 514.9 | 509.9 | 458.3 | 2516.0 | 0.013 |
| 4 | -28.5 | -27.5 | gangway | 1.00 | 5.98 | 523.1 | 517.9 | 440.9 | 2475.6 | 0.017 |
| 5 | 27.5 | -27.5 | gangway | 1.00 | 5.98 | 497.1 | 492.4 | 432.5 | 2450.8 | 0.014 |
| 6 | -27.5 | 28.5 | gangway | 1.00 | 6.05 | 518.1 | 513.9 | 424.3 | 2443.4 | 0.019 |
| 7 | -26.5 | 29.5 | gangway | 1.00 | 6.23 | 505.3 | 463.2 | 416.1 | 2431.7 | 0.018 |
| 8 | -27.5 | 27.5 | gangway | 1.00 | 5.98 | 508.3 | 504.8 | 418.0 | 2405.6 | 0.016 |
| 9 | 26.5 | 28.5 | gangway | 1.00 | 6.08 | 483.3 | 469.6 | 406.7 | 2385.5 | 0.017 |
| 10 | -28.5 | -26.5 | gangway | 1.00 | 5.95 | 508.5 | 485.4 | 432.5 | 2375.4 | 0.020 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -24.5 | -26.5 | seat row | 0.50 | 7.42 | 502.7 | 497.1 | 484.3 | 1710.9 | 0.010 |
| 2 | 26.5 | -24.5 | seat row | 0.50 | 7.15 | 501.6 | 501.1 | 489.0 | 1676.0 | 0.014 |
| 3 | -26.5 | 24.5 | seat row | 0.50 | 7.29 | 495.2 | 490.3 | 480.1 | 1669.4 | 0.012 |
| 4 | 24.5 | -26.5 | seat row | 0.50 | 7.14 | 506.9 | 505.5 | 489.0 | 1661.7 | 0.013 |
| 5 | -26.5 | -24.5 | seat row | 0.50 | 7.27 | 499.5 | 496.6 | 482.2 | 1652.0 | 0.012 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1947; agent-steps of seated agents on another row's clearway: 15396.

## Deposit check

Person-seconds deposited: 3978976.5, of them in excluded cells: 3086.090.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 415667 overlapping pair-steps: p99 0.0021, max 0.0196 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0021 max 0.0196; venue-geometry 2: p99 0.0005 max 0.0005 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00754 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 24 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.34 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 589 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
