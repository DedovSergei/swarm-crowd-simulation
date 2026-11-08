# Experiment `M_load100`

**Task 5.10 stage 4 (AMD 26.10.1): Task 5.8's model (the level spacing on the gangway inclines, --stair-flow off): venue M, 100% load**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 15832 agents on 100% of the 15832 seats (spawnSeatedCrowd, seed 1337), buffer N = 16384, 2636 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 966885 evaluations, 43636 switches, 0 forced choices).
Capacity: **within design capacity** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T20:18:50, 260.1 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1016 | 177.7 |
| t90 | 1942 | 339.7 |
| t100 | 2636 | 461.1 |

t_p: the step by which ceil(p x 15832) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 758 | 0 | 39.5 | 382.0 | 23.5 | 25.5 | 43.4-53.3 |
| -x | 5.66 | 762 | 0 | 39.5 | 384.4 | 23.4 | 25.5 | 45.3-55.3 |
| +y | 5.66 | 767 | 0 | 39.5 | 381.8 | 23.7 | 26.6 | 142.9-152.9 |
| -y | 5.66 | 763 | 0 | 39.5 | 382.5 | 23.6 | 25.5 | 45.5-55.4 |
| door +x+y (y wall) 0 | 1.20 | 630 | 1121 | 4.9 | 394.1 | 80.9 | 105.3 | 22.9-32.9 |
| door +x+y (y wall) 1 | 1.20 | 614 | 680 | 4.9 | 396.9 | 78.3 | 105.3 | 29.7-39.7 |
| door +x+y (y wall) 2 | 1.20 | 287 | 178 | 4.9 | 423.4 | 34.3 | 110.3 | 9.1-19.1 |
| door +x+y (x wall) 0 | 1.20 | 637 | 1121 | 4.9 | 393.7 | 81.9 | 110.3 | 24.1-34.1 |
| door +x+y (x wall) 1 | 1.20 | 607 | 680 | 4.9 | 398.1 | 77.2 | 105.3 | 31.8-41.8 |
| door +x+y (x wall) 2 | 1.20 | 313 | 178 | 4.9 | 422.0 | 37.5 | 110.3 | 9.1-19.1 |
| door +x+y (corner) | 1.20 | 108 | 0 | 56.8 | 417.9 | 15.0 | 85.3 | 58.4-68.4 |
| door -x+y (y wall) 0 | 1.20 | 634 | 1121 | 4.9 | 401.8 | 79.8 | 105.3 | 35.7-45.7 |
| door -x+y (y wall) 1 | 1.20 | 580 | 680 | 4.9 | 428.2 | 68.5 | 105.3 | 26.1-36.0 |
| door -x+y (y wall) 2 | 1.20 | 325 | 178 | 4.9 | 448.1 | 36.6 | 105.3 | 7.9-17.8 |
| door -x+y (x wall) 0 | 1.20 | 633 | 1121 | 4.9 | 433.1 | 73.9 | 120.4 | 29.2-39.2 |
| door -x+y (x wall) 1 | 1.20 | 599 | 680 | 4.9 | 426.4 | 71.0 | 105.3 | 25.2-35.2 |
| door -x+y (x wall) 2 | 1.20 | 301 | 178 | 4.9 | 458.1 | 33.2 | 110.3 | 14.3-24.3 |
| door -x+y (corner) | 1.20 | 124 | 0 | 53.0 | 461.1 | 15.2 | 110.3 | 263.4-273.4 |
| door -x-y (y wall) 0 | 1.20 | 627 | 1121 | 4.9 | 415.9 | 76.2 | 105.3 | 231.4-241.4 |
| door -x-y (y wall) 1 | 1.20 | 612 | 680 | 4.9 | 407.5 | 76.0 | 115.3 | 26.1-36.0 |
| door -x-y (y wall) 2 | 1.20 | 299 | 178 | 4.9 | 431.1 | 35.1 | 105.3 | 7.7-17.7 |
| door -x-y (x wall) 0 | 1.20 | 627 | 1121 | 4.9 | 390.2 | 81.3 | 105.3 | 26.2-36.2 |
| door -x-y (x wall) 1 | 1.20 | 599 | 680 | 4.9 | 420.3 | 72.1 | 105.3 | 18.0-28.0 |
| door -x-y (x wall) 2 | 1.20 | 300 | 178 | 4.9 | 430.8 | 35.2 | 105.3 | 7.7-17.7 |
| door -x-y (corner) | 1.20 | 130 | 0 | 50.5 | 428.7 | 17.2 | 90.3 | 327.3-337.2 |
| door +x-y (y wall) 0 | 1.20 | 642 | 1121 | 4.9 | 397.6 | 81.7 | 110.3 | 252.9-262.9 |
| door +x-y (y wall) 1 | 1.20 | 608 | 680 | 4.9 | 413.1 | 74.4 | 105.3 | 18.2-28.2 |
| door +x-y (y wall) 2 | 1.20 | 341 | 178 | 4.9 | 418.9 | 41.2 | 110.3 | 13.1-23.1 |
| door +x-y (x wall) 0 | 1.20 | 634 | 1121 | 4.9 | 388.5 | 82.6 | 110.3 | 206.9-216.9 |
| door +x-y (x wall) 1 | 1.20 | 633 | 680 | 4.9 | 413.7 | 77.4 | 105.3 | 21.3-31.3 |
| door +x-y (x wall) 2 | 1.20 | 270 | 178 | 4.9 | 424.3 | 32.2 | 105.3 | 7.9-17.8 |
| door +x-y (corner) | 1.20 | 68 | 0 | 57.0 | 424.8 | 9.2 | 90.3 | 60.0-70.0 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 758 | 4.8% | 20.8% |
| -x | avenue | 5.66 | 762 | 4.8% | 21.0% |
| +y | avenue | 5.66 | 767 | 4.8% | 21.1% |
| -y | avenue | 5.66 | 763 | 4.8% | 21.0% |
| door +x+y (y wall) 0 | door | 1.20 | 630 | 4.0% | 81.7% |
| door +x+y (y wall) 1 | door | 1.20 | 614 | 3.9% | 79.6% |
| door +x+y (y wall) 2 | door | 1.20 | 287 | 1.8% | 37.2% |
| door +x+y (x wall) 0 | door | 1.20 | 637 | 4.0% | 82.6% |
| door +x+y (x wall) 1 | door | 1.20 | 607 | 3.8% | 78.7% |
| door +x+y (x wall) 2 | door | 1.20 | 313 | 2.0% | 40.6% |
| door +x+y (corner) | door | 1.20 | 108 | 0.7% | 14.0% |
| door -x+y (y wall) 0 | door | 1.20 | 634 | 4.0% | 82.2% |
| door -x+y (y wall) 1 | door | 1.20 | 580 | 3.7% | 75.2% |
| door -x+y (y wall) 2 | door | 1.20 | 325 | 2.1% | 42.2% |
| door -x+y (x wall) 0 | door | 1.20 | 633 | 4.0% | 82.1% |
| door -x+y (x wall) 1 | door | 1.20 | 599 | 3.8% | 77.7% |
| door -x+y (x wall) 2 | door | 1.20 | 301 | 1.9% | 39.0% |
| door -x+y (corner) | door | 1.20 | 124 | 0.8% | 16.1% |
| door -x-y (y wall) 0 | door | 1.20 | 627 | 4.0% | 81.3% |
| door -x-y (y wall) 1 | door | 1.20 | 612 | 3.9% | 79.4% |
| door -x-y (y wall) 2 | door | 1.20 | 299 | 1.9% | 38.8% |
| door -x-y (x wall) 0 | door | 1.20 | 627 | 4.0% | 81.3% |
| door -x-y (x wall) 1 | door | 1.20 | 599 | 3.8% | 77.7% |
| door -x-y (x wall) 2 | door | 1.20 | 300 | 1.9% | 38.9% |
| door -x-y (corner) | door | 1.20 | 130 | 0.8% | 16.9% |
| door +x-y (y wall) 0 | door | 1.20 | 642 | 4.1% | 83.3% |
| door +x-y (y wall) 1 | door | 1.20 | 608 | 3.8% | 78.9% |
| door +x-y (y wall) 2 | door | 1.20 | 341 | 2.2% | 44.2% |
| door +x-y (x wall) 0 | door | 1.20 | 634 | 4.0% | 82.2% |
| door +x-y (x wall) 1 | door | 1.20 | 633 | 4.0% | 82.1% |
| door +x-y (x wall) 2 | door | 1.20 | 270 | 1.7% | 35.0% |
| door +x-y (corner) | door | 1.20 | 68 | 0.4% | 8.8% |
| **doors (28)** | door | 33.60 | 12782 | 80.7% | |
| **avenues (4)** | avenue | 22.64 | 3050 | 19.3% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 461.1 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 43.8%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 947 | 6.0% | 947 | 6.0% |
| straight +x+y (y wing) 1 | straight | yes | 624 | 3.9% | 618 | 3.9% |
| straight +x+y (y wing) 2 | straight | yes | 279 | 1.8% | 279 | 1.8% |
| straight +x+y (x wing) 0 | straight | yes | 951 | 6.0% | 951 | 6.0% |
| straight +x+y (x wing) 1 | straight | yes | 611 | 3.9% | 609 | 3.8% |
| straight +x+y (x wing) 2 | straight | yes | 311 | 2.0% | 311 | 2.0% |
| corner +x+y | corner | yes | 782 | 4.9% | 243 | 1.5% |
| straight -x+y (y wing) 0 | straight | yes | 953 | 6.0% | 953 | 6.0% |
| straight -x+y (y wing) 1 | straight | yes | 603 | 3.8% | 597 | 3.8% |
| straight -x+y (y wing) 2 | straight | yes | 308 | 1.9% | 308 | 1.9% |
| straight -x+y (x wing) 0 | straight | yes | 949 | 6.0% | 949 | 6.0% |
| straight -x+y (x wing) 1 | straight | yes | 620 | 3.9% | 615 | 3.9% |
| straight -x+y (x wing) 2 | straight | yes | 286 | 1.8% | 286 | 1.8% |
| corner -x+y | corner | yes | 780 | 4.9% | 250 | 1.6% |
| straight -x-y (y wing) 0 | straight | yes | 945 | 6.0% | 945 | 6.0% |
| straight -x-y (y wing) 1 | straight | yes | 621 | 3.9% | 615 | 3.9% |
| straight -x-y (y wing) 2 | straight | yes | 296 | 1.9% | 296 | 1.9% |
| straight -x-y (x wing) 0 | straight | yes | 949 | 6.0% | 949 | 6.0% |
| straight -x-y (x wing) 1 | straight | yes | 611 | 3.9% | 605 | 3.8% |
| straight -x-y (x wing) 2 | straight | yes | 294 | 1.9% | 294 | 1.9% |
| corner -x-y | corner | yes | 790 | 5.0% | 254 | 1.6% |
| straight +x-y (y wing) 0 | straight | yes | 959 | 6.1% | 959 | 6.1% |
| straight +x-y (y wing) 1 | straight | yes | 625 | 3.9% | 621 | 3.9% |
| straight +x-y (y wing) 2 | straight | yes | 328 | 2.1% | 328 | 2.1% |
| straight +x-y (x wing) 0 | straight | yes | 953 | 6.0% | 953 | 6.0% |
| straight +x-y (x wing) 1 | straight | yes | 636 | 4.0% | 634 | 4.0% |
| straight +x-y (x wing) 2 | straight | yes | 269 | 1.7% | 269 | 1.7% |
| corner +x-y | corner | yes | 779 | 4.9% | 194 | 1.2% |
| **straight (24)** | | | 14928 | | 14891 | 94.1% |
| **corner (4)** | | | 3131 | | 941 | 5.9% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 758 | 39.5 | 382.0 | 0.28 | 0.31 | 0.0% |
| -x | 762 | 39.5 | 384.4 | 0.28 | 0.31 | 0.0% |
| +y | 767 | 39.5 | 381.8 | 0.28 | 0.32 | 0.0% |
| -y | 763 | 39.5 | 382.5 | 0.28 | 0.31 | 0.0% |
| door +x+y (y wall) 0 | 630 | 4.9 | 394.1 | 0.97 | 1.26 | 80.0% |
| door +x+y (y wall) 1 | 614 | 4.9 | 396.9 | 0.94 | 1.26 | 75.0% |
| door +x+y (y wall) 2 | 287 | 4.9 | 423.4 | 0.41 | 1.32 | 11.6% |
| door +x+y (x wall) 0 | 637 | 4.9 | 393.7 | 0.98 | 1.32 | 80.0% |
| door +x+y (x wall) 1 | 607 | 4.9 | 398.1 | 0.92 | 1.26 | 72.5% |
| door +x+y (x wall) 2 | 313 | 4.9 | 422.0 | 0.45 | 1.32 | 16.3% |
| door +x+y (corner) | 108 | 56.8 | 417.9 | 0.18 | 1.02 | 5.4% |
| door -x+y (y wall) 0 | 634 | 4.9 | 401.8 | 0.96 | 1.26 | 78.0% |
| door -x+y (y wall) 1 | 580 | 4.9 | 428.2 | 0.82 | 1.26 | 60.5% |
| door -x+y (y wall) 2 | 325 | 4.9 | 448.1 | 0.44 | 1.26 | 15.6% |
| door -x+y (x wall) 0 | 633 | 4.9 | 433.1 | 0.88 | 1.44 | 72.7% |
| door -x+y (x wall) 1 | 599 | 4.9 | 426.4 | 0.85 | 1.26 | 62.8% |
| door -x+y (x wall) 2 | 301 | 4.9 | 458.1 | 0.40 | 1.32 | 15.2% |
| door -x+y (corner) | 124 | 53.0 | 461.1 | 0.18 | 1.32 | 4.8% |
| door -x-y (y wall) 0 | 627 | 4.9 | 415.9 | 0.91 | 1.26 | 76.2% |
| door -x-y (y wall) 1 | 612 | 4.9 | 407.5 | 0.91 | 1.38 | 70.7% |
| door -x-y (y wall) 2 | 299 | 4.9 | 431.1 | 0.42 | 1.26 | 11.4% |
| door -x-y (x wall) 0 | 627 | 4.9 | 390.2 | 0.97 | 1.26 | 80.0% |
| door -x-y (x wall) 1 | 599 | 4.9 | 420.3 | 0.86 | 1.26 | 69.8% |
| door -x-y (x wall) 2 | 300 | 4.9 | 430.8 | 0.42 | 1.26 | 13.6% |
| door -x-y (corner) | 130 | 50.5 | 428.7 | 0.21 | 1.08 | 7.9% |
| door +x-y (y wall) 0 | 642 | 4.9 | 397.6 | 0.98 | 1.32 | 80.0% |
| door +x-y (y wall) 1 | 608 | 4.9 | 413.1 | 0.89 | 1.26 | 61.9% |
| door +x-y (y wall) 2 | 341 | 4.9 | 418.9 | 0.49 | 1.32 | 16.3% |
| door +x-y (x wall) 0 | 634 | 4.9 | 388.5 | 0.99 | 1.32 | 82.1% |
| door +x-y (x wall) 1 | 633 | 4.9 | 413.7 | 0.93 | 1.26 | 71.4% |
| door +x-y (x wall) 2 | 270 | 4.9 | 424.3 | 0.38 | 1.26 | 14.0% |
| door +x-y (corner) | 68 | 57.0 | 424.8 | 0.11 | 1.08 | 2.6% |

Mean flow / w J averaged over the doors 0.67, over the avenues 0.28.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 947 | 630 / 317 / 188 | 0.7 | 391.1 | 2.91 | 4.31 | 88% | 78% | 10% | 4.11 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 576 | 618 / 0 / 14 | 0.7 | 393.4 | 1.61 | 2.21 | 78% | 68% | 10% | 3.72 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 70 | 279 / 0 / 0 | 0.7 | 420.5 | 0.66 | 2.01 | 12% | 12% | 0% | 3.07 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 951 | 637 / 314 / 187 | 0.7 | 390.7 | 2.92 | 4.61 | 88% | 78% | 10% | 4.06 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 571 | 609 / 0 / 7 | 0.7 | 395.1 | 1.56 | 2.11 | 85% | 68% | 18% | 3.53 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 69 | 311 / 0 / 0 | 0.7 | 419.1 | 0.74 | 2.01 | 12% | 12% | 0% | 3.05 |
| corner +x+y | 1.20 | 85.6 | 774 | 112 / 131 / 552 | 0.7 | 414.5 | 1.92 | 4.41 | 81% | 62% | 19% | 2.57 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 953 | 634 / 319 / 185 | 0.7 | 398.8 | 2.86 | 4.81 | 90% | 78% | 12% | 3.94 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 570 | 597 / 0 / 8 | 0.7 | 425.2 | 1.42 | 2.11 | 79% | 65% | 14% | 3.52 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 71 | 308 / 0 / 1 | 0.7 | 445.1 | 0.69 | 2.11 | 11% | 11% | 0% | 2.99 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 949 | 632 / 318 / 172 | 0.7 | 417.3 | 2.69 | 4.21 | 90% | 74% | 17% | 3.71 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 570 | 615 / 0 / 8 | 0.7 | 423.4 | 1.47 | 2.01 | 79% | 65% | 14% | 3.45 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 71 | 286 / 0 / 0 | 0.7 | 455.1 | 0.63 | 2.01 | 11% | 11% | 0% | 2.98 |
| corner -x+y | 1.20 | 85.6 | 774 | 124 / 126 / 541 | 0.7 | 457.2 | 1.73 | 5.12 | 80% | 57% | 24% | 2.56 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 945 | 626 / 320 / 217 | 0.7 | 385.0 | 3.03 | 4.81 | 87% | 79% | 8% | 4.12 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 572 | 615 / 0 / 11 | 0.7 | 404.6 | 1.55 | 2.11 | 78% | 66% | 12% | 3.66 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 71 | 296 / 0 / 0 | 0.7 | 428.2 | 0.69 | 2.01 | 12% | 12% | 0% | 3.00 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 949 | 627 / 322 / 174 | 0.7 | 387.2 | 2.90 | 4.11 | 87% | 79% | 8% | 4.20 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 570 | 605 / 0 / 14 | 0.7 | 417.3 | 1.49 | 2.11 | 81% | 67% | 14% | 3.56 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 70 | 294 / 0 / 0 | 0.7 | 427.8 | 0.69 | 2.11 | 12% | 12% | 0% | 2.95 |
| corner -x-y | 1.20 | 85.6 | 781 | 131 / 123 / 552 | 0.7 | 424.8 | 1.90 | 5.12 | 81% | 63% | 19% | 2.58 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 959 | 642 / 317 / 207 | 0.7 | 394.6 | 2.96 | 4.91 | 88% | 78% | 10% | 4.08 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 562 | 621 / 0 / 5 | 0.7 | 410.2 | 1.53 | 2.11 | 71% | 64% | 7% | 3.73 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 70 | 328 / 0 / 0 | 0.7 | 415.9 | 0.79 | 2.01 | 12% | 12% | 0% | 3.00 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 953 | 634 / 319 / 192 | 0.7 | 385.5 | 2.97 | 4.41 | 87% | 79% | 8% | 4.08 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 570 | 634 / 0 / 4 | 0.7 | 410.7 | 1.56 | 2.11 | 76% | 64% | 12% | 3.57 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 70 | 269 / 0 / 0 | 0.7 | 421.4 | 0.64 | 2.11 | 12% | 12% | 0% | 2.90 |
| corner +x-y | 1.20 | 85.6 | 774 | 68 / 126 / 589 | 0.7 | 421.0 | 1.86 | 4.71 | 81% | 70% | 12% | 2.67 |

The last agent out (agent 4307, t100 461.1 s): last gangway corner -x+y, exit door -x+y (corner). The gangway that cleared last: corner -x+y at 457.2 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.86 | 453.7 / 439.2 / 407.7 | 442.2 / 422.7 / 317.5 | 512675.6 | 1323330 | 0.257 |
| gangway | 1212 | 1112.9 | 6.86 | 453.0 / 437.8 / 362.6 | 442.2 / 422.7 / 317.5 | 511800.3 | 1173589 | 0.137 |
| walkway | 276 | 257.4 | 3.48 | 280.6 / 133.5 / 0.0 | 171.6 / 55.4 / 0.0 | 0.0 | 27718 | 0.759 |
| avenue | 912 | 858.9 | 1.88 | 325.3 / 0.0 / 0.0 | 245.9 / 0.0 / 0.0 | 0.0 | 87611 | 1.326 |
| exit | 32 | 3.2 | 0.00 | 422.9 / 418.6 / 379.4 | 264.1 / 243.3 / 141.0 | 875.3 | 1607 | 1.316 |
| concourse | 1116 | 1043.8 | 2.67 | 412.4 / 11.2 / 0.0 | 254.1 / 5.1 / 0.0 | 0.0 | 32805 | 1.189 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.56 | 377.8 / 368.0 / 352.3 | 372.7 / 368.0 / 348.9 | 556305.4 | 1570462 | 0.057 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 29.5 | 26.5 | gangway | 1.00 | 6.38 | 349.1 | 334.1 | 300.1 | 1824.4 | 0.025 |
| 2 | -26.5 | 29.5 | gangway | 1.00 | 6.12 | 368.7 | 347.9 | 298.0 | 1747.1 | 0.026 |
| 3 | 28.5 | -27.5 | gangway | 1.00 | 5.85 | 368.2 | 363.8 | 307.0 | 1723.9 | 0.021 |
| 4 | -29.5 | 26.5 | gangway | 1.00 | 6.06 | 377.4 | 331.8 | 300.5 | 1710.8 | 0.033 |
| 5 | -26.5 | 28.5 | gangway | 1.00 | 5.85 | 364.9 | 361.7 | 301.4 | 1677.4 | 0.023 |
| 6 | -27.5 | 28.5 | gangway | 1.00 | 6.08 | 365.2 | 360.7 | 290.0 | 1664.6 | 0.029 |
| 7 | -29.5 | -26.5 | gangway | 1.00 | 6.04 | 349.6 | 326.9 | 287.7 | 1657.9 | 0.030 |
| 8 | 26.5 | 28.5 | gangway | 1.00 | 6.04 | 355.4 | 340.0 | 288.6 | 1651.1 | 0.031 |
| 9 | 28.5 | 26.5 | gangway | 1.00 | 5.93 | 353.8 | 339.7 | 293.5 | 1639.6 | 0.025 |
| 10 | 26.5 | -26.5 | gangway | 1.00 | 6.09 | 362.8 | 352.8 | 293.1 | 1636.1 | 0.027 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -24.5 | 26.5 | seat row | 0.50 | 7.25 | 372.7 | 368.0 | 348.9 | 1204.6 | 0.017 |
| 2 | -24.5 | -26.5 | seat row | 0.50 | 7.44 | 353.0 | 348.1 | 335.6 | 1158.4 | 0.020 |
| 3 | -26.5 | -24.5 | seat row | 0.50 | 7.17 | 354.0 | 348.6 | 334.6 | 1132.5 | 0.019 |
| 4 | -25.5 | 30.5 | seat row | 0.64 | 6.83 | 333.5 | 321.0 | 273.6 | 1125.6 | 0.034 |
| 5 | 24.5 | -26.5 | seat row | 0.50 | 7.27 | 345.8 | 345.4 | 337.0 | 1125.5 | 0.018 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1524; agent-steps of seated agents on another row's clearway: 21034.

## Deposit check

Person-seconds deposited: 2896930.0, of them in excluded cells: 3137.172.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 237414 overlapping pair-steps: p99 0.0045, max 0.0283 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0045 max 0.0283; venue-geometry 2: p99 0.0002 max 0.0002 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00751 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 14 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.38 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 623 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
