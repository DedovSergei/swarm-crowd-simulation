# Experiment `M_load100_level`

**Task 5.9 stage 4 (model variants): venue M, 100% load, queue-aware exit choice, level walking speed**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 15832 agents on 100% of the 15832 seats (spawnSeatedCrowd, seed 1337), buffer N = 16384, 2161 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, level speed** (exit choice: 767135 evaluations, 38835 switches, 0 forced choices).
Capacity: **within design capacity** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-20T23:55:54, 82.5 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 807 | 141.1 |
| t90 | 1525 | 266.7 |
| t100 | 2161 | 378.0 |

t_p: the step by which ceil(p x 15832) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 621 | 0 | 39.5 | 313.8 | 24.0 | 25.5 | 43.2-53.2 |
| -x | 5.66 | 620 | 0 | 39.5 | 311.7 | 24.1 | 25.5 | 43.4-53.3 |
| +y | 5.66 | 620 | 0 | 39.5 | 310.8 | 24.2 | 25.5 | 43.2-53.2 |
| -y | 5.66 | 623 | 0 | 39.5 | 311.2 | 24.3 | 27.6 | 127.9-137.8 |
| door +x+y (y wall) 0 | 1.20 | 678 | 1121 | 4.2 | 323.2 | 106.2 | 140.4 | 82.6-92.5 |
| door +x+y (y wall) 1 | 1.20 | 632 | 680 | 4.2 | 334.9 | 95.5 | 140.4 | 108.8-118.8 |
| door +x+y (y wall) 2 | 1.20 | 304 | 178 | 4.2 | 333.9 | 46.1 | 120.4 | 4.0-14.0 |
| door +x+y (x wall) 0 | 1.20 | 675 | 1121 | 4.2 | 326.7 | 104.6 | 145.4 | 153.6-163.5 |
| door +x+y (x wall) 1 | 1.20 | 621 | 680 | 4.2 | 333.9 | 94.1 | 150.5 | 99.2-109.1 |
| door +x+y (x wall) 2 | 1.20 | 321 | 178 | 4.2 | 326.0 | 49.8 | 125.4 | 31.0-40.9 |
| door +x+y (corner) | 1.20 | 104 | 0 | 50.0 | 340.9 | 17.9 | 105.3 | 53.3-63.3 |
| door -x+y (y wall) 0 | 1.20 | 677 | 1121 | 4.2 | 304.0 | 112.8 | 145.4 | 223.9-233.9 |
| door -x+y (y wall) 1 | 1.20 | 631 | 680 | 4.2 | 318.7 | 100.3 | 145.4 | 61.2-71.2 |
| door -x+y (y wall) 2 | 1.20 | 308 | 178 | 4.2 | 324.1 | 48.1 | 130.4 | 38.7-48.6 |
| door -x+y (x wall) 0 | 1.20 | 684 | 1121 | 4.2 | 302.9 | 114.4 | 150.5 | 188.4-198.3 |
| door -x+y (x wall) 1 | 1.20 | 625 | 680 | 4.2 | 322.7 | 98.1 | 140.4 | 102.1-112.1 |
| door -x+y (x wall) 2 | 1.20 | 326 | 178 | 4.2 | 330.0 | 50.0 | 130.4 | 10.5-20.5 |
| door -x+y (corner) | 1.20 | 89 | 0 | 45.8 | 330.7 | 15.6 | 115.3 | 49.0-58.9 |
| door -x-y (y wall) 0 | 1.20 | 680 | 1121 | 4.2 | 329.0 | 104.6 | 145.4 | 107.2-117.2 |
| door -x-y (y wall) 1 | 1.20 | 625 | 680 | 4.2 | 372.4 | 84.8 | 140.4 | 61.2-71.2 |
| door -x-y (y wall) 2 | 1.20 | 298 | 178 | 4.2 | 378.0 | 39.8 | 120.4 | 4.0-14.0 |
| door -x-y (x wall) 0 | 1.20 | 678 | 1121 | 4.2 | 376.6 | 91.0 | 145.4 | 220.0-230.0 |
| door -x-y (x wall) 1 | 1.20 | 606 | 680 | 4.2 | 367.8 | 83.3 | 145.4 | 126.3-136.3 |
| door -x-y (x wall) 2 | 1.20 | 328 | 178 | 4.2 | 376.7 | 44.0 | 135.4 | 19.8-29.7 |
| door -x-y (corner) | 1.20 | 118 | 0 | 46.2 | 363.1 | 18.6 | 125.4 | 56.0-65.9 |
| door +x-y (y wall) 0 | 1.20 | 672 | 1121 | 4.2 | 310.6 | 109.6 | 140.4 | 24.7-34.6 |
| door +x-y (y wall) 1 | 1.20 | 605 | 680 | 4.2 | 316.1 | 96.9 | 150.5 | 173.7-183.7 |
| door +x-y (y wall) 2 | 1.20 | 301 | 178 | 4.2 | 321.7 | 47.4 | 125.4 | 4.7-14.7 |
| door +x-y (x wall) 0 | 1.20 | 684 | 1121 | 4.2 | 311.2 | 111.4 | 145.4 | 180.3-190.3 |
| door +x-y (x wall) 1 | 1.20 | 623 | 680 | 4.2 | 316.1 | 99.8 | 140.4 | 25.4-35.3 |
| door +x-y (x wall) 2 | 1.20 | 334 | 178 | 4.2 | 314.7 | 53.8 | 130.4 | 25.5-35.5 |
| door +x-y (corner) | 1.20 | 121 | 0 | 35.7 | 322.2 | 21.1 | 100.3 | 229.7-239.6 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 621 | 3.9% | 20.8% |
| -x | avenue | 5.66 | 620 | 3.9% | 20.8% |
| +y | avenue | 5.66 | 620 | 3.9% | 20.8% |
| -y | avenue | 5.66 | 623 | 3.9% | 20.9% |
| door +x+y (y wall) 0 | door | 1.20 | 678 | 4.3% | 107.3% |
| door +x+y (y wall) 1 | door | 1.20 | 632 | 4.0% | 100.0% |
| door +x+y (y wall) 2 | door | 1.20 | 304 | 1.9% | 48.1% |
| door +x+y (x wall) 0 | door | 1.20 | 675 | 4.3% | 106.8% |
| door +x+y (x wall) 1 | door | 1.20 | 621 | 3.9% | 98.3% |
| door +x+y (x wall) 2 | door | 1.20 | 321 | 2.0% | 50.8% |
| door +x+y (corner) | door | 1.20 | 104 | 0.7% | 16.5% |
| door -x+y (y wall) 0 | door | 1.20 | 677 | 4.3% | 107.1% |
| door -x+y (y wall) 1 | door | 1.20 | 631 | 4.0% | 99.8% |
| door -x+y (y wall) 2 | door | 1.20 | 308 | 1.9% | 48.7% |
| door -x+y (x wall) 0 | door | 1.20 | 684 | 4.3% | 108.2% |
| door -x+y (x wall) 1 | door | 1.20 | 625 | 3.9% | 98.9% |
| door -x+y (x wall) 2 | door | 1.20 | 326 | 2.1% | 51.6% |
| door -x+y (corner) | door | 1.20 | 89 | 0.6% | 14.1% |
| door -x-y (y wall) 0 | door | 1.20 | 680 | 4.3% | 107.6% |
| door -x-y (y wall) 1 | door | 1.20 | 625 | 3.9% | 98.9% |
| door -x-y (y wall) 2 | door | 1.20 | 298 | 1.9% | 47.2% |
| door -x-y (x wall) 0 | door | 1.20 | 678 | 4.3% | 107.3% |
| door -x-y (x wall) 1 | door | 1.20 | 606 | 3.8% | 95.9% |
| door -x-y (x wall) 2 | door | 1.20 | 328 | 2.1% | 51.9% |
| door -x-y (corner) | door | 1.20 | 118 | 0.7% | 18.7% |
| door +x-y (y wall) 0 | door | 1.20 | 672 | 4.2% | 106.3% |
| door +x-y (y wall) 1 | door | 1.20 | 605 | 3.8% | 95.7% |
| door +x-y (y wall) 2 | door | 1.20 | 301 | 1.9% | 47.6% |
| door +x-y (x wall) 0 | door | 1.20 | 684 | 4.3% | 108.2% |
| door +x-y (x wall) 1 | door | 1.20 | 623 | 3.9% | 98.6% |
| door +x-y (x wall) 2 | door | 1.20 | 334 | 2.1% | 52.9% |
| door +x-y (corner) | door | 1.20 | 121 | 0.8% | 19.1% |
| **doors (28)** | door | 33.60 | 13348 | 84.3% | |
| **avenues (4)** | avenue | 22.64 | 2484 | 15.7% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 378.0 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 53.5%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 928 | 5.9% | 928 | 5.9% |
| straight +x+y (y wing) 1 | straight | yes | 639 | 4.0% | 632 | 4.0% |
| straight +x+y (y wing) 2 | straight | yes | 305 | 1.9% | 305 | 1.9% |
| straight +x+y (x wing) 0 | straight | yes | 929 | 5.9% | 929 | 5.9% |
| straight +x+y (x wing) 1 | straight | yes | 644 | 4.1% | 640 | 4.0% |
| straight +x+y (x wing) 2 | straight | yes | 303 | 1.9% | 303 | 1.9% |
| corner +x+y | corner | yes | 807 | 5.1% | 221 | 1.4% |
| straight -x+y (y wing) 0 | straight | yes | 931 | 5.9% | 931 | 5.9% |
| straight -x+y (y wing) 1 | straight | yes | 646 | 4.1% | 641 | 4.0% |
| straight -x+y (y wing) 2 | straight | yes | 299 | 1.9% | 299 | 1.9% |
| straight -x+y (x wing) 0 | straight | yes | 930 | 5.9% | 930 | 5.9% |
| straight -x+y (x wing) 1 | straight | yes | 643 | 4.1% | 637 | 4.0% |
| straight -x+y (x wing) 2 | straight | yes | 316 | 2.0% | 315 | 2.0% |
| corner -x+y | corner | yes | 808 | 5.1% | 205 | 1.3% |
| straight -x-y (y wing) 0 | straight | yes | 929 | 5.9% | 929 | 5.9% |
| straight -x-y (y wing) 1 | straight | yes | 642 | 4.1% | 633 | 4.0% |
| straight -x-y (y wing) 2 | straight | yes | 291 | 1.8% | 291 | 1.8% |
| straight -x-y (x wing) 0 | straight | yes | 931 | 5.9% | 931 | 5.9% |
| straight -x-y (x wing) 1 | straight | yes | 627 | 4.0% | 622 | 3.9% |
| straight -x-y (x wing) 2 | straight | yes | 313 | 2.0% | 313 | 2.0% |
| corner -x-y | corner | yes | 810 | 5.1% | 239 | 1.5% |
| straight +x-y (y wing) 0 | straight | yes | 925 | 5.8% | 925 | 5.8% |
| straight +x-y (y wing) 1 | straight | yes | 638 | 4.0% | 628 | 4.0% |
| straight +x-y (y wing) 2 | straight | yes | 279 | 1.8% | 279 | 1.8% |
| straight +x-y (x wing) 0 | straight | yes | 927 | 5.9% | 927 | 5.9% |
| straight +x-y (x wing) 1 | straight | yes | 640 | 4.0% | 630 | 4.0% |
| straight +x-y (x wing) 2 | straight | yes | 328 | 2.1% | 328 | 2.1% |
| corner +x-y | corner | yes | 813 | 5.1% | 241 | 1.5% |
| **straight (24)** | | | 14983 | | 14926 | 94.3% |
| **corner (4)** | | | 3238 | | 906 | 5.7% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 621 | 39.5 | 313.8 | 0.29 | 0.31 | 0.0% |
| -x | 620 | 39.5 | 311.7 | 0.29 | 0.31 | 0.0% |
| +y | 620 | 39.5 | 310.8 | 0.29 | 0.31 | 0.0% |
| -y | 623 | 39.5 | 311.2 | 0.29 | 0.33 | 0.0% |
| door +x+y (y wall) 0 | 678 | 4.2 | 323.2 | 1.27 | 1.68 | 84.8% |
| door +x+y (y wall) 1 | 632 | 4.2 | 334.9 | 1.14 | 1.68 | 73.5% |
| door +x+y (y wall) 2 | 304 | 4.2 | 333.9 | 0.55 | 1.44 | 20.6% |
| door +x+y (x wall) 0 | 675 | 4.2 | 326.7 | 1.25 | 1.74 | 84.8% |
| door +x+y (x wall) 1 | 621 | 4.2 | 333.9 | 1.13 | 1.80 | 70.6% |
| door +x+y (x wall) 2 | 321 | 4.2 | 326.0 | 0.60 | 1.50 | 27.3% |
| door +x+y (corner) | 104 | 50.0 | 340.9 | 0.21 | 1.26 | 6.7% |
| door -x+y (y wall) 0 | 677 | 4.2 | 304.0 | 1.35 | 1.74 | 90.3% |
| door -x+y (y wall) 1 | 631 | 4.2 | 318.7 | 1.20 | 1.74 | 78.1% |
| door -x+y (y wall) 2 | 308 | 4.2 | 324.1 | 0.58 | 1.56 | 21.2% |
| door -x+y (x wall) 0 | 684 | 4.2 | 302.9 | 1.37 | 1.80 | 90.3% |
| door -x+y (x wall) 1 | 625 | 4.2 | 322.7 | 1.17 | 1.68 | 78.8% |
| door -x+y (x wall) 2 | 326 | 4.2 | 330.0 | 0.60 | 1.56 | 23.5% |
| door -x+y (corner) | 89 | 45.8 | 330.7 | 0.19 | 1.38 | 3.3% |
| door -x-y (y wall) 0 | 680 | 4.2 | 329.0 | 1.25 | 1.74 | 84.8% |
| door -x-y (y wall) 1 | 625 | 4.2 | 372.4 | 1.01 | 1.68 | 63.2% |
| door -x-y (y wall) 2 | 298 | 4.2 | 378.0 | 0.48 | 1.44 | 15.8% |
| door -x-y (x wall) 0 | 678 | 4.2 | 376.6 | 1.09 | 1.74 | 73.7% |
| door -x-y (x wall) 1 | 606 | 4.2 | 367.8 | 1.00 | 1.74 | 62.2% |
| door -x-y (x wall) 2 | 328 | 4.2 | 376.7 | 0.53 | 1.62 | 18.4% |
| door -x-y (corner) | 118 | 46.2 | 363.1 | 0.22 | 1.50 | 9.1% |
| door +x-y (y wall) 0 | 672 | 4.2 | 310.6 | 1.31 | 1.68 | 84.4% |
| door +x-y (y wall) 1 | 605 | 4.2 | 316.1 | 1.16 | 1.80 | 78.1% |
| door +x-y (y wall) 2 | 301 | 4.2 | 321.7 | 0.57 | 1.50 | 18.2% |
| door +x-y (x wall) 0 | 684 | 4.2 | 311.2 | 1.33 | 1.74 | 87.5% |
| door +x-y (x wall) 1 | 623 | 4.2 | 316.1 | 1.19 | 1.68 | 81.2% |
| door +x-y (x wall) 2 | 334 | 4.2 | 314.7 | 0.64 | 1.56 | 28.1% |
| door +x-y (corner) | 121 | 35.7 | 322.2 | 0.25 | 1.20 | 10.0% |

Mean flow / w J averaged over the doors 0.88, over the avenues 0.29.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 928 | 678 / 250 / 107 | 0.7 | 320.6 | 3.23 | 4.71 | 91% | 73% | 18% | 3.52 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 578 | 632 / 0 / 9 | 0.7 | 332.3 | 1.93 | 2.61 | 76% | 50% | 26% | 3.10 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 70 | 305 / 0 / 0 | 0.7 | 331.3 | 0.92 | 2.21 | 12% | 9% | 3% | 2.60 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 929 | 675 / 254 / 106 | 0.7 | 324.1 | 3.20 | 5.12 | 91% | 73% | 18% | 3.47 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 582 | 640 / 0 / 9 | 0.7 | 331.3 | 1.96 | 2.71 | 76% | 53% | 24% | 3.21 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 68 | 303 / 0 / 0 | 0.7 | 323.4 | 0.94 | 2.31 | 12% | 9% | 3% | 2.62 |
| corner +x+y | 1.20 | 85.6 | 803 | 102 / 119 / 600 | 0.7 | 337.2 | 2.44 | 5.82 | 91% | 50% | 41% | 2.31 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 931 | 677 / 254 / 139 | 0.7 | 301.4 | 3.56 | 5.42 | 90% | 77% | 13% | 3.71 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 580 | 641 / 0 / 10 | 0.7 | 316.1 | 2.06 | 2.71 | 78% | 56% | 22% | 3.23 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 69 | 299 / 0 / 0 | 0.7 | 321.5 | 0.93 | 2.41 | 12% | 9% | 3% | 2.66 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 930 | 684 / 246 / 114 | 0.7 | 300.3 | 3.48 | 4.91 | 87% | 77% | 10% | 3.87 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 579 | 637 / 0 / 11 | 0.7 | 320.1 | 2.03 | 2.71 | 76% | 55% | 21% | 3.27 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 68 | 315 / 0 / 1 | 0.7 | 327.4 | 0.97 | 2.71 | 12% | 9% | 3% | 2.54 |
| corner -x+y | 1.20 | 85.6 | 801 | 87 / 118 / 618 | 0.7 | 327.3 | 2.52 | 5.72 | 91% | 58% | 33% | 2.36 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 929 | 680 / 249 / 103 | 0.7 | 326.4 | 3.17 | 4.81 | 94% | 73% | 21% | 3.45 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 581 | 633 / 0 / 10 | 0.7 | 369.8 | 1.74 | 2.71 | 68% | 50% | 18% | 3.22 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 68 | 291 / 0 / 0 | 0.7 | 375.3 | 0.78 | 2.21 | 11% | 8% | 3% | 2.56 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 931 | 678 / 255 / 105 | 0.7 | 374.0 | 2.78 | 5.22 | 92% | 63% | 29% | 3.03 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 578 | 622 / 0 / 14 | 0.7 | 365.2 | 1.74 | 2.71 | 68% | 49% | 19% | 3.24 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 69 | 313 / 0 / 0 | 0.7 | 374.1 | 0.84 | 2.51 | 11% | 11% | 0% | 2.60 |
| corner -x-y | 1.20 | 85.6 | 802 | 116 / 123 / 587 | 0.7 | 372.7 | 2.22 | 4.41 | 92% | 47% | 45% | 2.10 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 925 | 672 / 253 / 117 | 0.7 | 308.0 | 3.39 | 5.02 | 94% | 77% | 16% | 3.61 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 585 | 628 / 0 / 12 | 0.7 | 313.4 | 2.05 | 2.91 | 75% | 56% | 19% | 3.40 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 69 | 279 / 0 / 0 | 0.7 | 319.0 | 0.88 | 2.51 | 12% | 12% | 0% | 2.60 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 927 | 684 / 243 / 100 | 0.7 | 308.5 | 3.33 | 4.81 | 94% | 77% | 16% | 3.60 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 581 | 630 / 0 / 13 | 0.7 | 313.4 | 2.05 | 2.61 | 78% | 59% | 19% | 3.34 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 69 | 328 / 0 / 0 | 0.7 | 312.0 | 1.05 | 2.41 | 12% | 12% | 0% | 2.70 |
| corner +x-y | 1.20 | 85.6 | 802 | 119 / 122 / 586 | 0.7 | 318.5 | 2.60 | 5.42 | 91% | 56% | 34% | 2.34 |

The last agent out (agent 10267, t100 378.0 s): last gangway straight -x-y (y wing) 2, exit door -x-y (y wall) 2. The gangway that cleared last: straight -x-y (y wing) 2 at 375.3 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.72 | 370.6 / 363.5 / 341.9 | 352.6 / 349.8 / 315.5 | 402005.6 | 999282 | 0.325 |
| gangway | 1212 | 1112.9 | 6.72 | 366.8 / 350.5 / 332.5 | 352.6 / 349.8 / 315.5 | 401224.7 | 868431 | 0.195 |
| walkway | 276 | 257.4 | 3.37 | 274.1 / 126.3 / 0.0 | 239.4 / 48.6 / 0.0 | 0.0 | 25629 | 0.672 |
| avenue | 912 | 858.9 | 1.93 | 270.8 / 0.0 / 0.0 | 266.7 / 0.0 / 0.0 | 0.0 | 71410 | 1.324 |
| exit | 32 | 3.2 | 0.00 | 346.3 / 341.2 / 310.5 | 248.4 / 216.4 / 127.3 | 780.9 | 1411 | 1.309 |
| concourse | 1116 | 1043.8 | 2.90 | 326.6 / 70.3 / 0.0 | 193.3 / 15.7 / 0.0 | 0.0 | 32401 | 1.283 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.62 | 355.6 / 346.7 / 332.7 | 349.1 / 345.6 / 328.8 | 455472.5 | 1301067 | 0.068 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -28.5 | -26.5 | gangway | 1.00 | 5.97 | 347.7 | 341.9 | 258.0 | 1420.5 | 0.029 |
| 2 | -26.5 | -25.5 | gangway | 0.77 | 6.44 | 351.0 | 348.1 | 315.5 | 1402.4 | 0.030 |
| 3 | -26.5 | -29.5 | gangway | 1.00 | 5.89 | 288.1 | 267.1 | 234.7 | 1331.6 | 0.044 |
| 4 | -29.5 | -26.5 | gangway | 1.00 | 6.23 | 323.4 | 304.5 | 225.1 | 1321.5 | 0.037 |
| 5 | 29.5 | 26.5 | gangway | 1.00 | 6.27 | 268.5 | 244.0 | 224.9 | 1317.9 | 0.047 |
| 6 | -28.5 | 26.5 | gangway | 1.00 | 5.97 | 272.7 | 267.4 | 222.8 | 1274.1 | 0.042 |
| 7 | 26.5 | 29.5 | gangway | 1.00 | 5.86 | 266.0 | 249.1 | 220.4 | 1256.6 | 0.046 |
| 8 | 28.5 | -26.5 | gangway | 1.00 | 6.19 | 276.4 | 268.1 | 216.4 | 1255.9 | 0.044 |
| 9 | -26.5 | -28.5 | gangway | 1.00 | 5.89 | 314.0 | 298.2 | 221.8 | 1247.1 | 0.044 |
| 10 | -26.5 | 28.5 | gangway | 1.00 | 6.04 | 270.1 | 261.7 | 219.2 | 1242.2 | 0.048 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -26.5 | -24.5 | seat row | 0.50 | 7.17 | 347.0 | 337.4 | 328.8 | 1126.4 | 0.023 |
| 2 | -24.5 | -26.5 | seat row | 0.50 | 7.25 | 309.4 | 304.3 | 292.1 | 998.7 | 0.028 |
| 3 | -26.5 | -23.5 | seat row | 0.50 | 6.97 | 330.6 | 324.6 | 310.1 | 992.0 | 0.024 |
| 4 | 24.5 | 26.5 | seat row | 0.50 | 7.29 | 300.0 | 297.3 | 285.4 | 959.6 | 0.030 |
| 5 | 24.5 | -26.5 | seat row | 0.50 | 7.28 | 287.2 | 286.0 | 278.3 | 952.2 | 0.028 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 894; agent-steps of seated agents on another row's clearway: 13509.

## Deposit check

Person-seconds deposited: 2303178.0, of them in excluded cells: 2828.755.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 258572 overlapping pair-steps: p99 0.0047, max 0.0641 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0047 max 0.0641; venue-geometry 4: p99 0.0003 max 0.0003 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00752 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 17 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.29 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 366 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
