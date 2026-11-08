# Experiment `M_load100_level`

**Task 5.10 stage 4 (AMD 26.10.1) (model variants): venue M, 100% load, queue-aware exit choice, level walking speed**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 15832 agents on 100% of the 15832 seats (spawnSeatedCrowd, seed 1337), buffer N = 16384, 2171 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, level speed** (exit choice: 766960 evaluations, 38545 switches, 0 forced choices).
Capacity: **within design capacity** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T20:29:46, 261.7 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 814 | 142.4 |
| t90 | 1515 | 265.0 |
| t100 | 2171 | 379.7 |

t_p: the step by which ceil(p x 15832) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 616 | 0 | 39.5 | 314.7 | 23.7 | 25.5 | 47.0-57.0 |
| -x | 5.66 | 620 | 0 | 39.5 | 311.0 | 24.2 | 25.5 | 43.2-53.2 |
| +y | 5.66 | 620 | 0 | 39.5 | 311.5 | 24.1 | 25.5 | 47.2-57.2 |
| -y | 5.66 | 616 | 0 | 39.5 | 310.5 | 24.1 | 25.5 | 47.9-57.9 |
| door +x+y (y wall) 0 | 1.20 | 693 | 1121 | 4.2 | 377.3 | 92.8 | 140.4 | 15.6-25.5 |
| door +x+y (y wall) 1 | 1.20 | 621 | 680 | 4.2 | 369.8 | 84.9 | 150.5 | 176.7-186.6 |
| door +x+y (y wall) 2 | 1.20 | 319 | 178 | 4.2 | 379.7 | 42.5 | 135.4 | 12.1-22.0 |
| door +x+y (x wall) 0 | 1.20 | 694 | 1121 | 4.2 | 354.5 | 99.0 | 145.4 | 150.8-160.7 |
| door +x+y (x wall) 1 | 1.20 | 612 | 680 | 4.2 | 373.3 | 82.9 | 150.5 | 101.6-111.6 |
| door +x+y (x wall) 2 | 1.20 | 290 | 178 | 4.2 | 376.0 | 39.0 | 135.4 | 14.5-24.5 |
| door +x+y (corner) | 1.20 | 107 | 0 | 38.8 | 371.7 | 16.1 | 120.4 | 244.2-254.1 |
| door -x+y (y wall) 0 | 1.20 | 673 | 1121 | 4.2 | 304.5 | 112.0 | 145.4 | 23.1-33.1 |
| door -x+y (y wall) 1 | 1.20 | 627 | 680 | 4.2 | 321.3 | 98.8 | 140.4 | 87.5-97.4 |
| door -x+y (y wall) 2 | 1.20 | 331 | 178 | 4.2 | 317.6 | 52.8 | 135.4 | 12.4-22.4 |
| door -x+y (x wall) 0 | 1.20 | 678 | 1121 | 4.2 | 303.8 | 113.1 | 145.4 | 162.8-172.8 |
| door -x+y (x wall) 1 | 1.20 | 616 | 680 | 4.2 | 323.2 | 96.5 | 145.4 | 35.9-45.8 |
| door -x+y (x wall) 2 | 1.20 | 303 | 178 | 4.2 | 325.3 | 47.2 | 130.4 | 14.0-24.0 |
| door -x+y (corner) | 1.20 | 110 | 0 | 39.2 | 307.3 | 20.5 | 110.3 | 252.9-262.9 |
| door -x-y (y wall) 0 | 1.20 | 678 | 1121 | 4.2 | 308.0 | 111.5 | 145.4 | 98.6-108.6 |
| door -x-y (y wall) 1 | 1.20 | 630 | 680 | 4.2 | 316.6 | 100.8 | 145.4 | 172.8-182.8 |
| door -x-y (y wall) 2 | 1.20 | 253 | 178 | 4.2 | 320.3 | 40.0 | 135.4 | 14.5-24.5 |
| door -x-y (x wall) 0 | 1.20 | 672 | 1121 | 4.2 | 291.7 | 116.8 | 145.4 | 225.3-235.2 |
| door -x-y (x wall) 1 | 1.20 | 630 | 680 | 4.2 | 317.3 | 100.6 | 145.4 | 75.4-85.4 |
| door -x-y (x wall) 2 | 1.20 | 328 | 178 | 4.2 | 315.2 | 52.7 | 140.4 | 27.5-37.4 |
| door -x-y (corner) | 1.20 | 151 | 0 | 39.9 | 312.7 | 27.7 | 130.4 | 194.3-204.3 |
| door +x-y (y wall) 0 | 1.20 | 673 | 1121 | 4.2 | 304.9 | 111.9 | 140.4 | 133.3-143.2 |
| door +x-y (y wall) 1 | 1.20 | 630 | 680 | 4.2 | 329.7 | 96.7 | 145.4 | 115.4-125.4 |
| door +x-y (y wall) 2 | 1.20 | 326 | 178 | 4.2 | 322.9 | 51.1 | 135.4 | 20.5-30.4 |
| door +x-y (x wall) 0 | 1.20 | 685 | 1121 | 4.2 | 305.6 | 113.6 | 145.4 | 78.0-88.0 |
| door +x-y (x wall) 1 | 1.20 | 636 | 680 | 4.2 | 327.6 | 98.3 | 145.4 | 53.9-63.8 |
| door +x-y (x wall) 2 | 1.20 | 258 | 178 | 4.2 | 326.4 | 40.0 | 130.4 | 18.5-28.5 |
| door +x-y (corner) | 1.20 | 136 | 0 | 32.7 | 327.3 | 23.1 | 130.4 | 273.0-283.0 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 616 | 3.9% | 20.6% |
| -x | avenue | 5.66 | 620 | 3.9% | 20.7% |
| +y | avenue | 5.66 | 620 | 3.9% | 20.7% |
| -y | avenue | 5.66 | 616 | 3.9% | 20.6% |
| door +x+y (y wall) 0 | door | 1.20 | 693 | 4.4% | 109.2% |
| door +x+y (y wall) 1 | door | 1.20 | 621 | 3.9% | 97.8% |
| door +x+y (y wall) 2 | door | 1.20 | 319 | 2.0% | 50.2% |
| door +x+y (x wall) 0 | door | 1.20 | 694 | 4.4% | 109.3% |
| door +x+y (x wall) 1 | door | 1.20 | 612 | 3.9% | 96.4% |
| door +x+y (x wall) 2 | door | 1.20 | 290 | 1.8% | 45.7% |
| door +x+y (corner) | door | 1.20 | 107 | 0.7% | 16.9% |
| door -x+y (y wall) 0 | door | 1.20 | 673 | 4.3% | 106.0% |
| door -x+y (y wall) 1 | door | 1.20 | 627 | 4.0% | 98.8% |
| door -x+y (y wall) 2 | door | 1.20 | 331 | 2.1% | 52.1% |
| door -x+y (x wall) 0 | door | 1.20 | 678 | 4.3% | 106.8% |
| door -x+y (x wall) 1 | door | 1.20 | 616 | 3.9% | 97.0% |
| door -x+y (x wall) 2 | door | 1.20 | 303 | 1.9% | 47.7% |
| door -x+y (corner) | door | 1.20 | 110 | 0.7% | 17.3% |
| door -x-y (y wall) 0 | door | 1.20 | 678 | 4.3% | 106.8% |
| door -x-y (y wall) 1 | door | 1.20 | 630 | 4.0% | 99.2% |
| door -x-y (y wall) 2 | door | 1.20 | 253 | 1.6% | 39.8% |
| door -x-y (x wall) 0 | door | 1.20 | 672 | 4.2% | 105.8% |
| door -x-y (x wall) 1 | door | 1.20 | 630 | 4.0% | 99.2% |
| door -x-y (x wall) 2 | door | 1.20 | 328 | 2.1% | 51.7% |
| door -x-y (corner) | door | 1.20 | 151 | 1.0% | 23.8% |
| door +x-y (y wall) 0 | door | 1.20 | 673 | 4.3% | 106.0% |
| door +x-y (y wall) 1 | door | 1.20 | 630 | 4.0% | 99.2% |
| door +x-y (y wall) 2 | door | 1.20 | 326 | 2.1% | 51.3% |
| door +x-y (x wall) 0 | door | 1.20 | 685 | 4.3% | 107.9% |
| door +x-y (x wall) 1 | door | 1.20 | 636 | 4.0% | 100.2% |
| door +x-y (x wall) 2 | door | 1.20 | 258 | 1.6% | 40.6% |
| door +x-y (corner) | door | 1.20 | 136 | 0.9% | 21.4% |
| **doors (28)** | door | 33.60 | 13360 | 84.4% | |
| **avenues (4)** | avenue | 22.64 | 2472 | 15.6% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 379.7 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 53.2%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 946 | 6.0% | 946 | 6.0% |
| straight +x+y (y wing) 1 | straight | yes | 638 | 4.0% | 632 | 4.0% |
| straight +x+y (y wing) 2 | straight | yes | 307 | 1.9% | 307 | 1.9% |
| straight +x+y (x wing) 0 | straight | yes | 948 | 6.0% | 948 | 6.0% |
| straight +x+y (x wing) 1 | straight | yes | 629 | 4.0% | 624 | 3.9% |
| straight +x+y (x wing) 2 | straight | yes | 278 | 1.8% | 278 | 1.8% |
| corner +x+y | corner | yes | 766 | 4.8% | 223 | 1.4% |
| straight -x+y (y wing) 0 | straight | yes | 923 | 5.8% | 923 | 5.8% |
| straight -x+y (y wing) 1 | straight | yes | 637 | 4.0% | 631 | 4.0% |
| straight -x+y (y wing) 2 | straight | yes | 328 | 2.1% | 327 | 2.1% |
| straight -x+y (x wing) 0 | straight | yes | 927 | 5.9% | 927 | 5.9% |
| straight -x+y (x wing) 1 | straight | yes | 646 | 4.1% | 640 | 4.0% |
| straight -x+y (x wing) 2 | straight | yes | 279 | 1.8% | 279 | 1.8% |
| corner -x+y | corner | yes | 810 | 5.1% | 231 | 1.5% |
| straight -x-y (y wing) 0 | straight | yes | 923 | 5.8% | 923 | 5.8% |
| straight -x-y (y wing) 1 | straight | yes | 638 | 4.0% | 634 | 4.0% |
| straight -x-y (y wing) 2 | straight | yes | 249 | 1.6% | 249 | 1.6% |
| straight -x-y (x wing) 0 | straight | yes | 923 | 5.8% | 923 | 5.8% |
| straight -x-y (x wing) 1 | straight | yes | 637 | 4.0% | 632 | 4.0% |
| straight -x-y (x wing) 2 | straight | yes | 326 | 2.1% | 326 | 2.1% |
| corner -x-y | corner | yes | 811 | 5.1% | 271 | 1.7% |
| straight +x-y (y wing) 0 | straight | yes | 926 | 5.8% | 926 | 5.8% |
| straight +x-y (y wing) 1 | straight | yes | 641 | 4.0% | 632 | 4.0% |
| straight +x-y (y wing) 2 | straight | yes | 324 | 2.0% | 324 | 2.0% |
| straight +x-y (x wing) 0 | straight | yes | 928 | 5.9% | 928 | 5.9% |
| straight +x-y (x wing) 1 | straight | yes | 644 | 4.1% | 638 | 4.0% |
| straight +x-y (x wing) 2 | straight | yes | 255 | 1.6% | 255 | 1.6% |
| corner +x-y | corner | yes | 811 | 5.1% | 255 | 1.6% |
| **straight (24)** | | | 14900 | | 14852 | 93.8% |
| **corner (4)** | | | 3198 | | 980 | 6.2% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 616 | 39.5 | 314.7 | 0.28 | 0.31 | 0.0% |
| -x | 620 | 39.5 | 311.0 | 0.29 | 0.31 | 0.0% |
| +y | 620 | 39.5 | 311.5 | 0.29 | 0.31 | 0.0% |
| -y | 616 | 39.5 | 310.5 | 0.29 | 0.31 | 0.0% |
| door +x+y (y wall) 0 | 693 | 4.2 | 377.3 | 1.11 | 1.68 | 73.7% |
| door +x+y (y wall) 1 | 621 | 4.2 | 369.8 | 1.02 | 1.80 | 63.2% |
| door +x+y (y wall) 2 | 319 | 4.2 | 379.7 | 0.51 | 1.62 | 17.9% |
| door +x+y (x wall) 0 | 694 | 4.2 | 354.5 | 1.18 | 1.74 | 77.8% |
| door +x+y (x wall) 1 | 612 | 4.2 | 373.3 | 0.99 | 1.80 | 63.2% |
| door +x+y (x wall) 2 | 290 | 4.2 | 376.0 | 0.47 | 1.62 | 18.4% |
| door +x+y (corner) | 107 | 38.8 | 371.7 | 0.19 | 1.44 | 8.6% |
| door -x+y (y wall) 0 | 673 | 4.2 | 304.5 | 1.34 | 1.74 | 90.3% |
| door -x+y (y wall) 1 | 627 | 4.2 | 321.3 | 1.18 | 1.68 | 84.8% |
| door -x+y (y wall) 2 | 331 | 4.2 | 317.6 | 0.63 | 1.62 | 25.0% |
| door -x+y (x wall) 0 | 678 | 4.2 | 303.8 | 1.35 | 1.74 | 90.3% |
| door -x+y (x wall) 1 | 616 | 4.2 | 323.2 | 1.15 | 1.74 | 75.8% |
| door -x+y (x wall) 2 | 303 | 4.2 | 325.3 | 0.56 | 1.56 | 24.2% |
| door -x+y (corner) | 110 | 39.2 | 307.3 | 0.25 | 1.32 | 7.1% |
| door -x-y (y wall) 0 | 678 | 4.2 | 308.0 | 1.33 | 1.74 | 90.3% |
| door -x-y (y wall) 1 | 630 | 4.2 | 316.6 | 1.21 | 1.74 | 81.2% |
| door -x-y (y wall) 2 | 253 | 4.2 | 320.3 | 0.48 | 1.62 | 15.2% |
| door -x-y (x wall) 0 | 672 | 4.2 | 291.7 | 1.40 | 1.74 | 90.0% |
| door -x-y (x wall) 1 | 630 | 4.2 | 317.3 | 1.20 | 1.74 | 81.2% |
| door -x-y (x wall) 2 | 328 | 4.2 | 315.2 | 0.63 | 1.68 | 21.9% |
| door -x-y (corner) | 151 | 39.9 | 312.7 | 0.33 | 1.56 | 17.2% |
| door +x-y (y wall) 0 | 673 | 4.2 | 304.9 | 1.34 | 1.68 | 87.1% |
| door +x-y (y wall) 1 | 630 | 4.2 | 329.7 | 1.16 | 1.74 | 73.5% |
| door +x-y (y wall) 2 | 326 | 4.2 | 322.9 | 0.61 | 1.62 | 21.2% |
| door +x-y (x wall) 0 | 685 | 4.2 | 305.6 | 1.36 | 1.74 | 90.3% |
| door +x-y (x wall) 1 | 636 | 4.2 | 327.6 | 1.18 | 1.74 | 78.8% |
| door +x-y (x wall) 2 | 258 | 4.2 | 326.4 | 0.48 | 1.56 | 18.2% |
| door +x-y (corner) | 136 | 32.7 | 327.3 | 0.28 | 1.56 | 6.7% |

Mean flow / w J averaged over the doors 0.89, over the avenues 0.29.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 946 | 692 / 254 / 127 | 0.7 | 357.0 | 3.01 | 5.22 | 94% | 67% | 28% | 3.08 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 583 | 632 / 0 / 13 | 0.7 | 367.1 | 1.76 | 2.81 | 73% | 51% | 22% | 3.09 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 68 | 307 / 0 / 0 | 0.7 | 377.1 | 0.82 | 2.51 | 11% | 8% | 3% | 2.62 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 948 | 694 / 255 / 117 | 0.7 | 351.7 | 3.04 | 5.02 | 92% | 67% | 25% | 3.19 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 588 | 624 / 0 / 18 | 0.7 | 370.6 | 1.73 | 2.91 | 71% | 50% | 21% | 3.12 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 69 | 278 / 0 / 0 | 0.7 | 373.4 | 0.75 | 2.41 | 11% | 11% | 0% | 2.72 |
| corner +x+y | 1.20 | 85.6 | 756 | 109 / 114 / 564 | 0.7 | 374.5 | 2.10 | 4.51 | 89% | 50% | 39% | 2.18 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 923 | 673 / 250 / 126 | 0.7 | 301.9 | 3.48 | 5.02 | 90% | 77% | 13% | 3.73 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 585 | 631 / 0 / 8 | 0.7 | 318.7 | 2.01 | 2.71 | 81% | 59% | 22% | 3.33 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 69 | 327 / 0 / 1 | 0.7 | 315.0 | 1.04 | 2.31 | 12% | 9% | 3% | 2.63 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 927 | 678 / 249 / 136 | 0.7 | 301.2 | 3.54 | 4.91 | 81% | 77% | 3% | 4.01 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 582 | 640 / 0 / 9 | 0.7 | 320.6 | 2.03 | 2.71 | 73% | 55% | 18% | 3.42 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 69 | 279 / 0 / 0 | 0.7 | 322.7 | 0.87 | 2.51 | 12% | 12% | 0% | 2.67 |
| corner -x+y | 1.20 | 85.6 | 803 | 110 / 121 / 590 | 0.7 | 320.1 | 2.57 | 5.42 | 88% | 52% | 36% | 2.33 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 923 | 678 / 245 / 123 | 0.7 | 305.4 | 3.43 | 5.22 | 90% | 77% | 13% | 3.70 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 588 | 634 / 0 / 11 | 0.7 | 313.8 | 2.06 | 2.81 | 78% | 59% | 19% | 3.43 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 70 | 249 / 0 / 0 | 0.7 | 317.6 | 0.79 | 2.51 | 12% | 9% | 3% | 2.64 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 923 | 672 / 251 / 117 | 0.7 | 289.1 | 3.60 | 5.02 | 93% | 83% | 10% | 3.79 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 578 | 632 / 0 / 6 | 0.7 | 314.7 | 2.03 | 2.71 | 78% | 53% | 25% | 3.25 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 70 | 326 / 0 / 0 | 0.7 | 312.6 | 1.04 | 2.51 | 12% | 9% | 3% | 2.71 |
| corner -x-y | 1.20 | 85.6 | 806 | 151 / 120 / 552 | 0.7 | 315.0 | 2.62 | 6.02 | 91% | 59% | 31% | 2.35 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 926 | 673 / 253 / 126 | 0.7 | 302.2 | 3.49 | 5.22 | 90% | 77% | 13% | 3.69 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 576 | 632 / 0 / 11 | 0.7 | 327.1 | 1.97 | 2.71 | 73% | 55% | 18% | 3.38 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 69 | 324 / 0 / 0 | 0.7 | 320.3 | 1.01 | 2.41 | 12% | 9% | 3% | 2.71 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 928 | 685 / 243 / 114 | 0.7 | 302.9 | 3.45 | 4.91 | 90% | 77% | 13% | 3.78 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 586 | 638 / 0 / 9 | 0.7 | 325.0 | 1.99 | 2.71 | 76% | 58% | 18% | 3.40 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 69 | 255 / 0 / 0 | 0.7 | 323.8 | 0.79 | 2.31 | 12% | 12% | 0% | 2.69 |
| corner +x-y | 1.20 | 85.6 | 804 | 137 / 118 / 569 | 0.7 | 323.6 | 2.55 | 5.02 | 91% | 58% | 33% | 2.38 |

The last agent out (agent 338, t100 379.7 s): last gangway straight +x+y (y wing) 2, exit door +x+y (y wall) 2. The gangway that cleared last: straight +x+y (y wing) 2 at 377.1 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.70 | 372.4 / 364.0 / 345.1 | 353.3 / 350.3 / 316.6 | 403278.1 | 995634 | 0.325 |
| gangway | 1212 | 1112.9 | 6.70 | 369.9 / 351.0 / 335.3 | 353.3 / 350.3 / 316.6 | 402476.5 | 865645 | 0.196 |
| walkway | 276 | 257.4 | 3.30 | 275.0 / 119.1 / 0.0 | 241.5 / 51.4 / 0.0 | 0.0 | 25126 | 0.681 |
| avenue | 912 | 858.9 | 1.80 | 271.5 / 0.0 / 0.0 | 264.3 / 0.0 / 0.0 | 0.0 | 71060 | 1.324 |
| exit | 32 | 3.2 | 0.00 | 353.1 / 347.2 / 314.7 | 252.0 / 222.7 / 130.5 | 801.6 | 1445 | 1.308 |
| concourse | 1116 | 1043.8 | 3.27 | 325.5 / 77.3 / 0.0 | 201.1 / 21.9 / 0.0 | 0.0 | 32359 | 1.275 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.59 | 345.4 / 343.7 / 330.0 | 345.4 / 343.7 / 326.4 | 449344.4 | 1304313 | 0.068 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 28.5 | 26.5 | gangway | 1.00 | 6.12 | 345.1 | 343.2 | 282.1 | 1615.4 | 0.026 |
| 2 | 27.5 | 26.5 | gangway | 1.00 | 5.91 | 344.9 | 340.2 | 275.3 | 1529.0 | 0.028 |
| 3 | 26.5 | 25.5 | gangway | 0.77 | 6.18 | 349.6 | 343.7 | 316.6 | 1387.0 | 0.029 |
| 4 | 24.5 | 24.5 | gangway | 1.00 | 5.57 | 350.9 | 347.4 | 257.6 | 1382.5 | 0.020 |
| 5 | 26.5 | 28.5 | gangway | 1.00 | 6.05 | 328.0 | 321.5 | 245.7 | 1346.1 | 0.037 |
| 6 | -26.5 | 29.5 | gangway | 1.00 | 6.28 | 280.0 | 255.4 | 221.8 | 1292.2 | 0.042 |
| 7 | 26.5 | 27.5 | gangway | 1.00 | 5.75 | 334.2 | 316.8 | 230.4 | 1259.2 | 0.038 |
| 8 | 29.5 | -26.5 | gangway | 1.00 | 6.07 | 281.4 | 259.0 | 220.9 | 1243.8 | 0.046 |
| 9 | 29.5 | 26.5 | gangway | 1.00 | 6.06 | 333.7 | 315.9 | 215.0 | 1239.1 | 0.035 |
| 10 | -26.5 | -29.5 | gangway | 1.00 | 6.10 | 261.1 | 243.6 | 217.1 | 1237.9 | 0.046 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 24.5 | 26.5 | seat row | 0.50 | 7.40 | 345.4 | 343.7 | 326.4 | 1088.6 | 0.020 |
| 2 | 26.5 | 24.5 | seat row | 0.50 | 7.19 | 342.8 | 329.0 | 295.1 | 1004.2 | 0.021 |
| 3 | 26.5 | -24.5 | seat row | 0.50 | 7.21 | 292.3 | 290.0 | 279.0 | 949.5 | 0.027 |
| 4 | -26.5 | 24.5 | seat row | 0.50 | 7.45 | 282.3 | 279.9 | 271.6 | 940.4 | 0.028 |
| 5 | 24.5 | -26.5 | seat row | 0.50 | 7.13 | 290.9 | 289.1 | 275.8 | 933.0 | 0.027 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 983; agent-steps of seated agents on another row's clearway: 13902.

## Deposit check

Person-seconds deposited: 2302767.3, of them in excluded cells: 2820.183.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 297701 overlapping pair-steps: p99 0.0041, max 0.0691 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0041 max 0.0691; venue-geometry 3: p99 0.0002 max 0.0002 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 9 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.36 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 379 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
