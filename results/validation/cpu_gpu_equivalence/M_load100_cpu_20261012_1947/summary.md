# Experiment `venue_M_load100_cpu_c1`

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 15832 agents on 100% of the 15832 seats (spawnSeatedCrowd, seed 1337), buffer N = 16384, 2576 steps (everyone left), readback every 1 step(s). Engine: CPU reference (CpuCrowdSim, counting sort, all threads).
Model: **queue-aware exit choice, incline speed** (exit choice: 967334 evaluations, 43955 switches, 0 forced choices).
Capacity: **within design capacity** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `372a5c19c97779f851bd5737b102b7136c2f09ce`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-12T19:47:36, 565.7 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1014 | 177.4 |
| t90 | 1932 | 337.9 |
| t100 | 2576 | 450.6 |

t_p: the step by which ceil(p x 15832) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 763 | 0 | 39.7 | 385.8 | 23.4 | 25.5 | 50.4-60.3 |
| -x | 5.66 | 755 | 0 | 39.7 | 383.4 | 23.3 | 25.5 | 50.0-60.0 |
| +y | 5.66 | 756 | 0 | 39.7 | 383.0 | 23.3 | 25.5 | 49.1-59.1 |
| -y | 5.66 | 763 | 0 | 39.7 | 386.5 | 23.3 | 25.5 | 50.2-60.2 |
| door +x+y (y wall) 0 | 1.20 | 625 | 1121 | 4.9 | 387.8 | 81.6 | 105.3 | 94.1-104.1 |
| door +x+y (y wall) 1 | 1.20 | 569 | 680 | 4.9 | 422.9 | 68.0 | 105.3 | 121.7-131.7 |
| door +x+y (y wall) 2 | 1.20 | 326 | 178 | 4.9 | 435.2 | 37.9 | 105.3 | 13.3-23.3 |
| door +x+y (x wall) 0 | 1.20 | 627 | 1121 | 4.9 | 404.0 | 78.5 | 100.3 | 4.7-14.7 |
| door +x+y (x wall) 1 | 1.20 | 604 | 680 | 4.9 | 403.7 | 75.7 | 105.3 | 254.1-264.1 |
| door +x+y (x wall) 2 | 1.20 | 321 | 178 | 4.9 | 434.5 | 37.3 | 105.3 | 13.3-23.3 |
| door +x+y (corner) | 1.20 | 123 | 0 | 55.8 | 428.0 | 16.5 | 95.3 | 65.2-75.2 |
| door -x+y (y wall) 0 | 1.20 | 634 | 1121 | 4.9 | 416.3 | 77.0 | 115.3 | 26.8-36.7 |
| door -x+y (y wall) 1 | 1.20 | 601 | 680 | 4.9 | 411.4 | 73.9 | 105.3 | 27.6-37.6 |
| door -x+y (y wall) 2 | 1.20 | 298 | 178 | 4.9 | 445.1 | 33.8 | 105.3 | 13.3-23.3 |
| door -x+y (x wall) 0 | 1.20 | 629 | 1121 | 4.9 | 398.8 | 79.8 | 105.3 | 17.8-27.8 |
| door -x+y (x wall) 1 | 1.20 | 588 | 680 | 4.9 | 438.5 | 67.8 | 110.3 | 27.8-37.8 |
| door -x+y (x wall) 2 | 1.20 | 350 | 178 | 4.9 | 440.9 | 40.1 | 105.3 | 13.3-23.3 |
| door -x+y (corner) | 1.20 | 102 | 0 | 53.7 | 450.6 | 12.8 | 95.3 | 58.8-68.7 |
| door -x-y (y wall) 0 | 1.20 | 629 | 1121 | 4.9 | 402.5 | 79.1 | 105.3 | 41.3-51.2 |
| door -x-y (y wall) 1 | 1.20 | 610 | 680 | 4.9 | 403.3 | 76.5 | 110.3 | 25.0-35.0 |
| door -x-y (y wall) 2 | 1.20 | 272 | 178 | 4.9 | 429.7 | 32.0 | 105.3 | 12.9-22.9 |
| door -x-y (x wall) 0 | 1.20 | 638 | 1121 | 4.9 | 395.8 | 81.6 | 105.3 | 45.3-55.3 |
| door -x-y (x wall) 1 | 1.20 | 619 | 680 | 4.9 | 403.3 | 77.6 | 110.3 | 25.0-35.0 |
| door -x-y (x wall) 2 | 1.20 | 316 | 178 | 4.9 | 433.6 | 36.8 | 105.3 | 12.9-22.9 |
| door -x-y (corner) | 1.20 | 111 | 0 | 53.5 | 438.0 | 14.4 | 100.3 | 63.7-73.6 |
| door +x-y (y wall) 0 | 1.20 | 630 | 1121 | 4.9 | 408.4 | 78.0 | 105.3 | 17.8-27.8 |
| door +x-y (y wall) 1 | 1.20 | 592 | 680 | 4.9 | 404.4 | 74.1 | 110.3 | 27.8-37.8 |
| door +x-y (y wall) 2 | 1.20 | 320 | 178 | 4.9 | 430.4 | 37.6 | 105.3 | 13.3-23.3 |
| door +x-y (x wall) 0 | 1.20 | 629 | 1121 | 4.9 | 408.4 | 77.9 | 110.3 | 25.0-35.0 |
| door +x-y (x wall) 1 | 1.20 | 610 | 680 | 4.9 | 409.8 | 75.3 | 105.3 | 27.6-37.6 |
| door +x-y (x wall) 2 | 1.20 | 282 | 178 | 4.9 | 426.4 | 33.4 | 105.3 | 13.3-23.3 |
| door +x-y (corner) | 1.20 | 140 | 0 | 53.7 | 430.3 | 18.6 | 110.3 | 342.6-352.6 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 763 | 4.8% | 21.5% |
| -x | avenue | 5.66 | 755 | 4.8% | 21.2% |
| +y | avenue | 5.66 | 756 | 4.8% | 21.3% |
| -y | avenue | 5.66 | 763 | 4.8% | 21.5% |
| door +x+y (y wall) 0 | door | 1.20 | 625 | 3.9% | 83.0% |
| door +x+y (y wall) 1 | door | 1.20 | 569 | 3.6% | 75.5% |
| door +x+y (y wall) 2 | door | 1.20 | 326 | 2.1% | 43.3% |
| door +x+y (x wall) 0 | door | 1.20 | 627 | 4.0% | 83.2% |
| door +x+y (x wall) 1 | door | 1.20 | 604 | 3.8% | 80.2% |
| door +x+y (x wall) 2 | door | 1.20 | 321 | 2.0% | 42.6% |
| door +x+y (corner) | door | 1.20 | 123 | 0.8% | 16.3% |
| door -x+y (y wall) 0 | door | 1.20 | 634 | 4.0% | 84.2% |
| door -x+y (y wall) 1 | door | 1.20 | 601 | 3.8% | 79.8% |
| door -x+y (y wall) 2 | door | 1.20 | 298 | 1.9% | 39.6% |
| door -x+y (x wall) 0 | door | 1.20 | 629 | 4.0% | 83.5% |
| door -x+y (x wall) 1 | door | 1.20 | 588 | 3.7% | 78.1% |
| door -x+y (x wall) 2 | door | 1.20 | 350 | 2.2% | 46.5% |
| door -x+y (corner) | door | 1.20 | 102 | 0.6% | 13.5% |
| door -x-y (y wall) 0 | door | 1.20 | 629 | 4.0% | 83.5% |
| door -x-y (y wall) 1 | door | 1.20 | 610 | 3.9% | 81.0% |
| door -x-y (y wall) 2 | door | 1.20 | 272 | 1.7% | 36.1% |
| door -x-y (x wall) 0 | door | 1.20 | 638 | 4.0% | 84.7% |
| door -x-y (x wall) 1 | door | 1.20 | 619 | 3.9% | 82.2% |
| door -x-y (x wall) 2 | door | 1.20 | 316 | 2.0% | 41.9% |
| door -x-y (corner) | door | 1.20 | 111 | 0.7% | 14.7% |
| door +x-y (y wall) 0 | door | 1.20 | 630 | 4.0% | 83.6% |
| door +x-y (y wall) 1 | door | 1.20 | 592 | 3.7% | 78.6% |
| door +x-y (y wall) 2 | door | 1.20 | 320 | 2.0% | 42.5% |
| door +x-y (x wall) 0 | door | 1.20 | 629 | 4.0% | 83.5% |
| door +x-y (x wall) 1 | door | 1.20 | 610 | 3.9% | 81.0% |
| door +x-y (x wall) 2 | door | 1.20 | 282 | 1.8% | 37.4% |
| door +x-y (corner) | door | 1.20 | 140 | 0.9% | 18.6% |
| **doors (28)** | door | 33.60 | 12795 | 80.8% | |
| **avenues (4)** | avenue | 22.64 | 3037 | 19.2% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 450.6 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 44.8%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 942 | 5.9% | 942 | 5.9% |
| straight +x+y (y wing) 1 | straight | yes | 609 | 3.8% | 604 | 3.8% |
| straight +x+y (y wing) 2 | straight | yes | 291 | 1.8% | 291 | 1.8% |
| straight +x+y (x wing) 0 | straight | yes | 946 | 6.0% | 946 | 6.0% |
| straight +x+y (x wing) 1 | straight | yes | 623 | 3.9% | 618 | 3.9% |
| straight +x+y (x wing) 2 | straight | yes | 307 | 1.9% | 307 | 1.9% |
| corner +x+y | corner | yes | 800 | 5.1% | 250 | 1.6% |
| straight -x+y (y wing) 0 | straight | yes | 944 | 6.0% | 944 | 6.0% |
| straight -x+y (y wing) 1 | straight | yes | 627 | 4.0% | 618 | 3.9% |
| straight -x+y (y wing) 2 | straight | yes | 282 | 1.8% | 282 | 1.8% |
| straight -x+y (x wing) 0 | straight | yes | 945 | 6.0% | 945 | 6.0% |
| straight -x+y (x wing) 1 | straight | yes | 613 | 3.9% | 605 | 3.8% |
| straight -x+y (x wing) 2 | straight | yes | 333 | 2.1% | 333 | 2.1% |
| corner -x+y | corner | yes | 806 | 5.1% | 231 | 1.5% |
| straight -x-y (y wing) 0 | straight | yes | 950 | 6.0% | 950 | 6.0% |
| straight -x-y (y wing) 1 | straight | yes | 621 | 3.9% | 615 | 3.9% |
| straight -x-y (y wing) 2 | straight | yes | 267 | 1.7% | 267 | 1.7% |
| straight -x-y (x wing) 0 | straight | yes | 950 | 6.0% | 950 | 6.0% |
| straight -x-y (x wing) 1 | straight | yes | 624 | 3.9% | 619 | 3.9% |
| straight -x-y (x wing) 2 | straight | yes | 316 | 2.0% | 316 | 2.0% |
| corner -x-y | corner | yes | 782 | 4.9% | 241 | 1.5% |
| straight +x-y (y wing) 0 | straight | yes | 943 | 6.0% | 943 | 6.0% |
| straight +x-y (y wing) 1 | straight | yes | 613 | 3.9% | 600 | 3.8% |
| straight +x-y (y wing) 2 | straight | yes | 312 | 2.0% | 312 | 2.0% |
| straight +x-y (x wing) 0 | straight | yes | 947 | 6.0% | 947 | 6.0% |
| straight +x-y (x wing) 1 | straight | yes | 619 | 3.9% | 611 | 3.9% |
| straight +x-y (x wing) 2 | straight | yes | 280 | 1.8% | 280 | 1.8% |
| corner +x-y | corner | yes | 812 | 5.1% | 265 | 1.7% |
| **straight (24)** | | | 14904 | | 14845 | 93.8% |
| **corner (4)** | | | 3200 | | 987 | 6.2% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 763 | 39.7 | 385.8 | 0.28 | 0.31 | 0.0% |
| -x | 755 | 39.7 | 383.4 | 0.28 | 0.31 | 0.0% |
| +y | 756 | 39.7 | 383.0 | 0.28 | 0.31 | 0.0% |
| -y | 763 | 39.7 | 386.5 | 0.28 | 0.31 | 0.0% |
| door +x+y (y wall) 0 | 625 | 4.9 | 387.8 | 0.98 | 1.26 | 84.6% |
| door +x+y (y wall) 1 | 569 | 4.9 | 422.9 | 0.81 | 1.26 | 58.1% |
| door +x+y (y wall) 2 | 326 | 4.9 | 435.2 | 0.45 | 1.26 | 11.4% |
| door +x+y (x wall) 0 | 627 | 4.9 | 404.0 | 0.94 | 1.20 | 80.5% |
| door +x+y (x wall) 1 | 604 | 4.9 | 403.7 | 0.91 | 1.26 | 68.3% |
| door +x+y (x wall) 2 | 321 | 4.9 | 434.5 | 0.45 | 1.26 | 11.4% |
| door +x+y (corner) | 123 | 55.8 | 428.0 | 0.20 | 1.14 | 2.6% |
| door -x+y (y wall) 0 | 634 | 4.9 | 416.3 | 0.92 | 1.38 | 78.6% |
| door -x+y (y wall) 1 | 601 | 4.9 | 411.4 | 0.88 | 1.26 | 61.9% |
| door -x+y (y wall) 2 | 298 | 4.9 | 445.1 | 0.40 | 1.26 | 11.1% |
| door -x+y (x wall) 0 | 629 | 4.9 | 398.8 | 0.95 | 1.26 | 80.0% |
| door -x+y (x wall) 1 | 588 | 4.9 | 438.5 | 0.81 | 1.32 | 59.1% |
| door -x+y (x wall) 2 | 350 | 4.9 | 440.9 | 0.48 | 1.26 | 13.3% |
| door -x+y (corner) | 102 | 53.7 | 450.6 | 0.15 | 1.14 | 4.9% |
| door -x-y (y wall) 0 | 629 | 4.9 | 402.5 | 0.95 | 1.26 | 80.5% |
| door -x-y (y wall) 1 | 610 | 4.9 | 403.3 | 0.92 | 1.32 | 68.3% |
| door -x-y (y wall) 2 | 272 | 4.9 | 429.7 | 0.38 | 1.26 | 11.4% |
| door -x-y (x wall) 0 | 638 | 4.9 | 395.8 | 0.98 | 1.26 | 82.5% |
| door -x-y (x wall) 1 | 619 | 4.9 | 403.3 | 0.93 | 1.32 | 65.9% |
| door -x-y (x wall) 2 | 316 | 4.9 | 433.6 | 0.44 | 1.26 | 11.4% |
| door -x-y (corner) | 111 | 53.5 | 438.0 | 0.17 | 1.20 | 5.1% |
| door +x-y (y wall) 0 | 630 | 4.9 | 408.4 | 0.93 | 1.26 | 78.0% |
| door +x-y (y wall) 1 | 592 | 4.9 | 404.4 | 0.89 | 1.32 | 68.3% |
| door +x-y (y wall) 2 | 320 | 4.9 | 430.4 | 0.45 | 1.26 | 11.4% |
| door +x-y (x wall) 0 | 629 | 4.9 | 408.4 | 0.93 | 1.32 | 78.0% |
| door +x-y (x wall) 1 | 610 | 4.9 | 409.8 | 0.90 | 1.26 | 66.7% |
| door +x-y (x wall) 2 | 282 | 4.9 | 426.4 | 0.40 | 1.26 | 11.6% |
| door +x-y (corner) | 140 | 53.7 | 430.3 | 0.22 | 1.32 | 5.1% |

Mean flow / w J averaged over the doors 0.67, over the avenues 0.28.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 942 | 625 / 317 / 175 | 0.7 | 384.8 | 2.91 | 4.11 | 87% | 79% | 8% | 4.14 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 571 | 604 / 0 / 9 | 0.7 | 420.0 | 1.46 | 2.21 | 79% | 67% | 12% | 3.70 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 70 | 291 / 0 / 0 | 0.7 | 432.2 | 0.67 | 2.11 | 11% | 11% | 0% | 3.01 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 946 | 627 / 319 / 188 | 0.7 | 401.1 | 2.83 | 4.41 | 88% | 76% | 12% | 3.96 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 566 | 618 / 0 / 9 | 0.7 | 400.7 | 1.57 | 2.11 | 78% | 66% | 12% | 3.71 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 70 | 307 / 0 / 0 | 0.7 | 431.5 | 0.71 | 2.11 | 11% | 11% | 0% | 3.01 |
| corner +x+y | 1.20 | 85.6 | 793 | 123 / 127 / 561 | 0.7 | 426.2 | 1.90 | 4.61 | 81% | 56% | 26% | 2.48 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 944 | 633 / 311 / 185 | 0.7 | 402.1 | 2.81 | 4.31 | 88% | 76% | 12% | 4.01 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 570 | 618 / 0 / 11 | 0.7 | 407.9 | 1.54 | 2.11 | 78% | 66% | 12% | 3.59 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 69 | 282 / 0 / 0 | 0.7 | 442.2 | 0.64 | 1.91 | 11% | 11% | 0% | 2.99 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 945 | 629 / 316 / 194 | 0.7 | 395.8 | 2.88 | 4.21 | 88% | 78% | 10% | 4.04 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 569 | 605 / 0 / 11 | 0.7 | 435.5 | 1.42 | 2.11 | 73% | 61% | 11% | 3.65 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 68 | 333 / 0 / 0 | 0.7 | 438.0 | 0.76 | 1.91 | 11% | 11% | 0% | 2.95 |
| corner -x+y | 1.20 | 85.6 | 793 | 102 / 129 / 584 | 0.7 | 446.7 | 1.83 | 4.91 | 78% | 58% | 20% | 2.54 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 950 | 629 / 321 / 185 | 0.7 | 399.5 | 2.84 | 4.51 | 88% | 76% | 12% | 4.02 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 575 | 615 / 0 / 8 | 0.7 | 400.4 | 1.56 | 2.21 | 76% | 66% | 10% | 3.73 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 69 | 267 / 0 / 0 | 0.7 | 426.8 | 0.63 | 2.01 | 12% | 12% | 0% | 2.95 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 950 | 638 / 312 / 192 | 0.7 | 392.8 | 2.91 | 4.61 | 85% | 78% | 8% | 4.21 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 571 | 619 / 0 / 10 | 0.7 | 400.5 | 1.57 | 2.11 | 78% | 66% | 12% | 3.66 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 70 | 316 / 0 / 0 | 0.7 | 430.6 | 0.73 | 2.01 | 11% | 11% | 0% | 2.95 |
| corner -x-y | 1.20 | 85.6 | 773 | 111 / 130 / 550 | 0.7 | 434.1 | 1.82 | 5.02 | 80% | 61% | 18% | 2.54 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 943 | 630 / 314 / 189 | 0.7 | 405.4 | 2.80 | 5.52 | 88% | 76% | 12% | 3.89 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 567 | 600 / 0 / 20 | 0.7 | 401.4 | 1.55 | 2.01 | 76% | 66% | 10% | 3.72 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 69 | 312 / 0 / 0 | 0.7 | 427.5 | 0.73 | 1.91 | 12% | 12% | 0% | 2.95 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 947 | 629 / 318 / 194 | 0.7 | 405.4 | 2.82 | 4.41 | 88% | 76% | 12% | 3.91 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 566 | 611 / 0 / 9 | 0.7 | 406.8 | 1.53 | 2.21 | 73% | 66% | 7% | 3.78 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 69 | 280 / 0 / 0 | 0.7 | 423.4 | 0.66 | 1.91 | 12% | 12% | 0% | 2.99 |
| corner +x-y | 1.20 | 85.6 | 797 | 141 / 124 / 561 | 0.7 | 426.4 | 1.94 | 4.81 | 81% | 60% | 21% | 2.53 |

The last agent out (agent 6354, t100 450.6 s): last gangway corner -x+y, exit door -x+y (corner). The gangway that cleared last: corner -x+y at 446.7 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.86 | 450.2 / 439.4 / 402.1 | 431.7 / 419.1 / 330.0 | 496137.7 | 1315706 | 0.258 |
| gangway | 1212 | 1112.9 | 6.86 | 446.0 / 434.5 / 347.9 | 431.7 / 419.1 / 330.0 | 495268.1 | 1166513 | 0.139 |
| walkway | 276 | 257.4 | 3.33 | 279.3 / 130.5 / 0.0 | 174.2 / 59.1 / 0.0 | 0.0 | 27023 | 0.774 |
| avenue | 912 | 858.9 | 1.78 | 332.5 / 0.0 / 0.0 | 268.0 / 0.0 / 0.0 | 0.0 | 87229 | 1.326 |
| exit | 32 | 3.2 | 0.00 | 417.0 / 412.4 / 376.9 | 256.2 / 231.6 / 137.8 | 869.6 | 1604 | 1.318 |
| concourse | 1116 | 1043.8 | 2.75 | 410.3 / 27.8 / 0.0 | 246.1 / 14.5 / 0.0 | 0.0 | 33337 | 1.186 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.61 | 369.6 / 354.7 / 348.2 | 357.0 / 354.5 / 345.1 | 554154.6 | 1579424 | 0.057 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 29.5 | -26.5 | gangway | 1.00 | 6.42 | 351.2 | 311.2 | 268.5 | 1660.8 | 0.032 |
| 2 | -26.5 | -28.5 | gangway | 1.00 | 5.92 | 349.5 | 341.9 | 290.3 | 1647.1 | 0.027 |
| 3 | -29.5 | 26.5 | gangway | 1.00 | 6.24 | 355.6 | 327.1 | 279.7 | 1633.0 | 0.032 |
| 4 | 28.5 | -26.5 | gangway | 1.00 | 6.08 | 365.2 | 336.9 | 277.9 | 1608.9 | 0.030 |
| 5 | 29.5 | 26.5 | gangway | 1.00 | 6.12 | 359.1 | 322.4 | 270.4 | 1599.9 | 0.033 |
| 6 | -28.5 | 26.5 | gangway | 1.00 | 6.02 | 358.9 | 352.8 | 285.1 | 1575.3 | 0.028 |
| 7 | -27.5 | -28.5 | gangway | 1.00 | 6.01 | 349.1 | 343.7 | 275.8 | 1564.9 | 0.026 |
| 8 | -29.5 | -26.5 | gangway | 1.00 | 6.19 | 354.0 | 321.1 | 270.9 | 1563.6 | 0.037 |
| 9 | 26.5 | 28.5 | gangway | 1.00 | 6.04 | 354.4 | 347.4 | 279.2 | 1563.2 | 0.028 |
| 10 | 27.5 | 28.5 | gangway | 1.00 | 5.90 | 357.9 | 354.4 | 278.5 | 1551.9 | 0.031 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 26.5 | -24.5 | seat row | 0.50 | 7.35 | 352.1 | 347.2 | 341.8 | 1196.5 | 0.018 |
| 2 | -26.5 | 24.5 | seat row | 0.50 | 7.30 | 352.6 | 350.3 | 345.1 | 1171.6 | 0.020 |
| 3 | -24.5 | -26.5 | seat row | 0.50 | 7.30 | 351.6 | 350.5 | 335.5 | 1167.7 | 0.017 |
| 4 | 26.5 | 24.5 | seat row | 0.50 | 7.21 | 354.9 | 354.5 | 341.9 | 1165.7 | 0.020 |
| 5 | 24.5 | -26.5 | seat row | 0.50 | 7.14 | 351.7 | 348.9 | 337.9 | 1159.5 | 0.020 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1507; agent-steps of seated agents on another row's clearway: 24815.

## Deposit check

Person-seconds deposited: 2898279.7, of them in excluded cells: 3149.497.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 283822 overlapping pair-steps: p99 0.0036, max 0.0763 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0036 max 0.0763; venue-geometry 3: p99 0.0008 max 0.0008 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 12 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.42 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 645 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
