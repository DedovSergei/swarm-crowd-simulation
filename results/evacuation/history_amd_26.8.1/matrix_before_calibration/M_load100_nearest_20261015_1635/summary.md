# Experiment `M_load100_nearest`

**Task 5.8 stage 2: venue M, 100% load, nearest exit (incline speed): the uninformed-crowd bound**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 15832 agents on 100% of the 15832 seats (spawnSeatedCrowd, seed 1337), buffer N = 16384, 3617 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **nearest exit, incline speed**.
Capacity: **within design capacity** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `cd8e0bbf3411846ca7aa6719887d122a142a7ca1`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-15T16:35:48, 81.0 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1305 | 228.3 |
| t90 | 2948 | 515.6 |
| t100 | 3617 | 632.6 |

t_p: the step by which ceil(p x 15832) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| -x | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| +y | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| -y | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| door +x+y (y wall) 0 | 1.20 | 1121 | 1121 | 4.9 | 631.2 | 89.5 | 105.3 | 19.9-29.9 |
| door +x+y (y wall) 1 | 1.20 | 680 | 680 | 4.9 | 409.8 | 83.9 | 105.3 | 19.9-29.9 |
| door +x+y (y wall) 2 | 1.20 | 180 | 178 | 4.9 | 142.4 | 65.4 | 105.3 | 13.3-23.3 |
| door +x+y (x wall) 0 | 1.20 | 1121 | 1121 | 4.9 | 628.1 | 89.9 | 105.3 | 27.5-37.4 |
| door +x+y (x wall) 1 | 1.20 | 680 | 680 | 4.9 | 408.9 | 84.1 | 105.3 | 19.9-29.9 |
| door +x+y (x wall) 2 | 1.20 | 176 | 178 | 4.9 | 140.1 | 65.0 | 105.3 | 13.3-23.3 |
| door +x+y (corner) | 1.20 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| door -x+y (y wall) 0 | 1.20 | 1121 | 1121 | 4.9 | 630.7 | 89.5 | 105.3 | 19.9-29.9 |
| door -x+y (y wall) 1 | 1.20 | 676 | 680 | 4.9 | 405.6 | 84.3 | 105.3 | 17.8-27.8 |
| door -x+y (y wall) 2 | 1.20 | 172 | 178 | 4.9 | 137.3 | 64.9 | 105.3 | 12.9-22.9 |
| door -x+y (x wall) 0 | 1.20 | 1121 | 1121 | 4.9 | 629.1 | 89.8 | 105.3 | 18.9-28.9 |
| door -x+y (x wall) 1 | 1.20 | 684 | 680 | 4.9 | 404.6 | 85.5 | 110.3 | 29.4-39.4 |
| door -x+y (x wall) 2 | 1.20 | 184 | 178 | 4.9 | 143.1 | 66.5 | 105.3 | 13.3-23.3 |
| door -x+y (corner) | 1.20 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| door -x-y (y wall) 0 | 1.20 | 1121 | 1121 | 4.9 | 632.6 | 89.3 | 105.3 | 154.6-164.6 |
| door -x-y (y wall) 1 | 1.20 | 680 | 680 | 4.9 | 410.9 | 83.7 | 100.3 | 4.7-14.7 |
| door -x-y (y wall) 2 | 1.20 | 179 | 178 | 4.9 | 139.8 | 66.3 | 105.3 | 12.9-22.9 |
| door -x-y (x wall) 0 | 1.20 | 1121 | 1121 | 4.9 | 627.4 | 90.0 | 105.3 | 46.2-56.1 |
| door -x-y (x wall) 1 | 1.20 | 680 | 680 | 4.9 | 411.4 | 83.6 | 105.3 | 30.6-40.6 |
| door -x-y (x wall) 2 | 1.20 | 177 | 178 | 4.9 | 139.6 | 65.6 | 105.3 | 12.9-22.9 |
| door -x-y (corner) | 1.20 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| door +x-y (y wall) 0 | 1.20 | 1121 | 1121 | 4.9 | 625.8 | 90.2 | 110.3 | 25.0-35.0 |
| door +x-y (y wall) 1 | 1.20 | 681 | 680 | 4.9 | 403.7 | 85.3 | 105.3 | 25.2-35.2 |
| door +x-y (y wall) 2 | 1.20 | 179 | 178 | 4.9 | 138.4 | 67.0 | 105.3 | 13.3-23.3 |
| door +x-y (x wall) 0 | 1.20 | 1121 | 1121 | 4.9 | 630.9 | 89.5 | 105.3 | 26.9-36.9 |
| door +x-y (x wall) 1 | 1.20 | 679 | 680 | 4.9 | 403.7 | 85.1 | 110.3 | 25.0-35.0 |
| door +x-y (x wall) 2 | 1.20 | 177 | 178 | 4.9 | 138.4 | 66.2 | 105.3 | 12.9-22.9 |
| door +x-y (corner) | 1.20 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 0 | 0.0% | 0.0% |
| -x | avenue | 5.66 | 0 | 0.0% | 0.0% |
| +y | avenue | 5.66 | 0 | 0.0% | 0.0% |
| -y | avenue | 5.66 | 0 | 0.0% | 0.0% |
| door +x+y (y wall) 0 | door | 1.20 | 1121 | 7.1% | 106.0% |
| door +x+y (y wall) 1 | door | 1.20 | 680 | 4.3% | 64.3% |
| door +x+y (y wall) 2 | door | 1.20 | 180 | 1.1% | 17.0% |
| door +x+y (x wall) 0 | door | 1.20 | 1121 | 7.1% | 106.0% |
| door +x+y (x wall) 1 | door | 1.20 | 680 | 4.3% | 64.3% |
| door +x+y (x wall) 2 | door | 1.20 | 176 | 1.1% | 16.6% |
| door +x+y (corner) | door | 1.20 | 0 | 0.0% | 0.0% |
| door -x+y (y wall) 0 | door | 1.20 | 1121 | 7.1% | 106.0% |
| door -x+y (y wall) 1 | door | 1.20 | 676 | 4.3% | 63.9% |
| door -x+y (y wall) 2 | door | 1.20 | 172 | 1.1% | 16.3% |
| door -x+y (x wall) 0 | door | 1.20 | 1121 | 7.1% | 106.0% |
| door -x+y (x wall) 1 | door | 1.20 | 684 | 4.3% | 64.7% |
| door -x+y (x wall) 2 | door | 1.20 | 184 | 1.2% | 17.4% |
| door -x+y (corner) | door | 1.20 | 0 | 0.0% | 0.0% |
| door -x-y (y wall) 0 | door | 1.20 | 1121 | 7.1% | 106.0% |
| door -x-y (y wall) 1 | door | 1.20 | 680 | 4.3% | 64.3% |
| door -x-y (y wall) 2 | door | 1.20 | 179 | 1.1% | 16.9% |
| door -x-y (x wall) 0 | door | 1.20 | 1121 | 7.1% | 106.0% |
| door -x-y (x wall) 1 | door | 1.20 | 680 | 4.3% | 64.3% |
| door -x-y (x wall) 2 | door | 1.20 | 177 | 1.1% | 16.7% |
| door -x-y (corner) | door | 1.20 | 0 | 0.0% | 0.0% |
| door +x-y (y wall) 0 | door | 1.20 | 1121 | 7.1% | 106.0% |
| door +x-y (y wall) 1 | door | 1.20 | 681 | 4.3% | 64.4% |
| door +x-y (y wall) 2 | door | 1.20 | 179 | 1.1% | 16.9% |
| door +x-y (x wall) 0 | door | 1.20 | 1121 | 7.1% | 106.0% |
| door +x-y (x wall) 1 | door | 1.20 | 679 | 4.3% | 64.2% |
| door +x-y (x wall) 2 | door | 1.20 | 177 | 1.1% | 16.7% |
| door +x-y (corner) | door | 1.20 | 0 | 0.0% | 0.0% |
| **doors (28)** | door | 33.60 | 15832 | 100.0% | |
| **avenues (4)** | avenue | 22.64 | 0 | 0.0% | |

**Unused exit width: 27.4 of 56.2 m (48.8%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 632.6 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 31.9%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight +x+y (y wing) 1 | straight | yes | 680 | 4.3% | 680 | 4.3% |
| straight +x+y (y wing) 2 | straight | yes | 180 | 1.1% | 180 | 1.1% |
| straight +x+y (x wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight +x+y (x wing) 1 | straight | yes | 680 | 4.3% | 680 | 4.3% |
| straight +x+y (x wing) 2 | straight | yes | 176 | 1.1% | 176 | 1.1% |
| corner +x+y | corner | yes | 450 | 2.8% | 0 | 0.0% |
| straight -x+y (y wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight -x+y (y wing) 1 | straight | yes | 676 | 4.3% | 676 | 4.3% |
| straight -x+y (y wing) 2 | straight | yes | 172 | 1.1% | 172 | 1.1% |
| straight -x+y (x wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight -x+y (x wing) 1 | straight | yes | 684 | 4.3% | 684 | 4.3% |
| straight -x+y (x wing) 2 | straight | yes | 184 | 1.2% | 184 | 1.2% |
| corner -x+y | corner | yes | 449 | 2.8% | 0 | 0.0% |
| straight -x-y (y wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight -x-y (y wing) 1 | straight | yes | 680 | 4.3% | 680 | 4.3% |
| straight -x-y (y wing) 2 | straight | yes | 179 | 1.1% | 179 | 1.1% |
| straight -x-y (x wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight -x-y (x wing) 1 | straight | yes | 680 | 4.3% | 680 | 4.3% |
| straight -x-y (x wing) 2 | straight | yes | 177 | 1.1% | 177 | 1.1% |
| corner -x-y | corner | yes | 450 | 2.8% | 0 | 0.0% |
| straight +x-y (y wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight +x-y (y wing) 1 | straight | yes | 681 | 4.3% | 681 | 4.3% |
| straight +x-y (y wing) 2 | straight | yes | 179 | 1.1% | 179 | 1.1% |
| straight +x-y (x wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight +x-y (x wing) 1 | straight | yes | 679 | 4.3% | 679 | 4.3% |
| straight +x-y (x wing) 2 | straight | yes | 177 | 1.1% | 177 | 1.1% |
| corner +x-y | corner | yes | 450 | 2.8% | 0 | 0.0% |
| **straight (24)** | | | 15832 | | 15832 | 100.0% |
| **corner (4)** | | | 1799 | | 0 | 0.0% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| door +x+y (y wall) 0 | 1121 | 4.9 | 631.2 | 1.07 | 1.26 | 96.9% |
| door +x+y (y wall) 1 | 680 | 4.9 | 409.8 | 1.00 | 1.26 | 83.3% |
| door +x+y (y wall) 2 | 180 | 4.9 | 142.4 | 0.78 | 1.26 | 40.0% |
| door +x+y (x wall) 0 | 1121 | 4.9 | 628.1 | 1.08 | 1.26 | 96.8% |
| door +x+y (x wall) 1 | 680 | 4.9 | 408.9 | 1.01 | 1.26 | 83.3% |
| door +x+y (x wall) 2 | 176 | 4.9 | 140.1 | 0.78 | 1.26 | 40.0% |
| door -x+y (y wall) 0 | 1121 | 4.9 | 630.7 | 1.07 | 1.26 | 95.3% |
| door -x+y (y wall) 1 | 676 | 4.9 | 405.6 | 1.01 | 1.26 | 82.9% |
| door -x+y (y wall) 2 | 172 | 4.9 | 137.3 | 0.78 | 1.26 | 35.7% |
| door -x+y (x wall) 0 | 1121 | 4.9 | 629.1 | 1.07 | 1.26 | 96.9% |
| door -x+y (x wall) 1 | 684 | 4.9 | 404.6 | 1.02 | 1.32 | 82.9% |
| door -x+y (x wall) 2 | 184 | 4.9 | 143.1 | 0.80 | 1.26 | 33.3% |
| door -x-y (y wall) 0 | 1121 | 4.9 | 632.6 | 1.07 | 1.26 | 95.3% |
| door -x-y (y wall) 1 | 680 | 4.9 | 410.9 | 1.00 | 1.20 | 83.3% |
| door -x-y (y wall) 2 | 179 | 4.9 | 139.8 | 0.79 | 1.26 | 40.0% |
| door -x-y (x wall) 0 | 1121 | 4.9 | 627.4 | 1.08 | 1.26 | 96.8% |
| door -x-y (x wall) 1 | 680 | 4.9 | 411.4 | 1.00 | 1.26 | 81.0% |
| door -x-y (x wall) 2 | 177 | 4.9 | 139.6 | 0.79 | 1.26 | 35.7% |
| door +x-y (y wall) 0 | 1121 | 4.9 | 625.8 | 1.08 | 1.32 | 96.8% |
| door +x-y (y wall) 1 | 681 | 4.9 | 403.7 | 1.02 | 1.26 | 85.4% |
| door +x-y (y wall) 2 | 179 | 4.9 | 138.4 | 0.80 | 1.26 | 42.9% |
| door +x-y (x wall) 0 | 1121 | 4.9 | 630.9 | 1.07 | 1.26 | 95.3% |
| door +x-y (x wall) 1 | 679 | 4.9 | 403.7 | 1.02 | 1.32 | 82.9% |
| door +x-y (x wall) 2 | 177 | 4.9 | 138.4 | 0.79 | 1.26 | 42.9% |

Mean flow / w J averaged over the doors 0.96, over the avenues nan.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 628.3 | 1.79 | 2.01 | 89% | 88% | 2% | 4.20 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 565 | 680 / 0 / 1 | 0.7 | 406.8 | 1.68 | 2.01 | 76% | 76% | 0% | 4.15 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 68 | 180 / 0 / 0 | 0.7 | 139.4 | 1.30 | 1.91 | 29% | 29% | 0% | 3.07 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 625.1 | 1.79 | 2.01 | 90% | 89% | 2% | 4.28 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 565 | 680 / 0 / 0 | 0.7 | 406.0 | 1.68 | 2.01 | 76% | 76% | 0% | 4.14 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 68 | 176 / 0 / 0 | 0.7 | 137.1 | 1.29 | 1.91 | 36% | 36% | 0% | 3.04 |
| corner +x+y | 1.20 | 85.6 | 450 | 0 / 0 / 451 | 0.7 | 374.7 | 1.21 | 2.81 | 92% | 11% | 82% | 1.48 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 627.7 | 1.79 | 2.01 | 90% | 89% | 2% | 4.26 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 566 | 676 / 0 / 0 | 0.7 | 402.6 | 1.68 | 2.11 | 73% | 73% | 0% | 4.15 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 68 | 172 / 0 / 0 | 0.7 | 134.3 | 1.29 | 2.01 | 29% | 29% | 0% | 3.03 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 626.2 | 1.79 | 2.11 | 90% | 89% | 2% | 4.29 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 565 | 684 / 0 / 0 | 0.7 | 401.6 | 1.71 | 2.01 | 76% | 76% | 0% | 4.19 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 68 | 184 / 0 / 0 | 0.7 | 140.1 | 1.32 | 1.91 | 33% | 33% | 0% | 2.96 |
| corner -x+y | 1.20 | 85.6 | 449 | 0 / 0 / 449 | 0.7 | 370.3 | 1.21 | 2.61 | 92% | 11% | 82% | 1.44 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 629.7 | 1.78 | 2.11 | 89% | 88% | 2% | 4.25 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 565 | 680 / 0 / 0 | 0.7 | 407.9 | 1.67 | 2.01 | 76% | 76% | 0% | 4.12 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 68 | 179 / 0 / 0 | 0.7 | 136.8 | 1.31 | 2.01 | 36% | 36% | 0% | 3.04 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 624.4 | 1.80 | 2.01 | 89% | 89% | 0% | 4.29 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 565 | 680 / 0 / 0 | 0.7 | 408.4 | 1.67 | 2.11 | 73% | 73% | 0% | 4.15 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 68 | 177 / 0 / 0 | 0.7 | 136.6 | 1.30 | 2.01 | 29% | 29% | 0% | 3.09 |
| corner -x-y | 1.20 | 85.6 | 450 | 0 / 0 / 450 | 0.7 | 376.2 | 1.20 | 2.51 | 92% | 11% | 82% | 1.45 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 622.8 | 1.80 | 2.11 | 89% | 89% | 0% | 4.35 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 565 | 681 / 0 / 0 | 0.7 | 400.7 | 1.70 | 2.01 | 76% | 76% | 0% | 4.18 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 68 | 179 / 0 / 0 | 0.7 | 135.4 | 1.33 | 1.91 | 36% | 36% | 0% | 3.00 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 627.9 | 1.79 | 2.01 | 90% | 90% | 0% | 4.23 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 565 | 679 / 0 / 0 | 0.7 | 400.7 | 1.70 | 2.11 | 73% | 73% | 0% | 4.22 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 68 | 177 / 0 / 0 | 0.7 | 135.4 | 1.31 | 2.01 | 29% | 29% | 0% | 3.04 |
| corner +x-y | 1.20 | 85.6 | 450 | 0 / 0 / 450 | 0.7 | 368.5 | 1.22 | 2.51 | 95% | 11% | 84% | 1.44 |

The last agent out (agent 7947, t100 632.6 s): last gangway straight -x-y (y wing) 0, exit -. The gangway that cleared last: straight -x-y (y wing) 0 at 629.7 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.82 | 628.8 / 611.8 / 537.1 | 625.5 / 570.5 / 527.2 | 872827.4 | 1538775 | 0.169 |
| gangway | 1212 | 1112.9 | 6.82 | 628.8 / 611.8 / 537.1 | 625.5 / 570.5 / 527.2 | 871911.8 | 1498289 | 0.142 |
| walkway | 276 | 257.4 | 0.20 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 10 | 0.018 |
| avenue | 912 | 858.9 | 0.17 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 13 | 0.142 |
| exit | 32 | 3.2 | 0.00 | 401.8 / 400.2 / 374.1 | 282.6 / 259.4 / 153.9 | 915.6 | 1254 | 1.324 |
| concourse | 1116 | 1043.8 | 2.18 | 619.7 / 0.2 / 0.0 | 294.7 / 0.2 / 0.0 | 0.0 | 39209 | 1.192 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.65 | 569.7 / 566.9 / 547.1 | 569.7 / 566.9 / 541.0 | 912773.5 | 2409159 | 0.029 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 17.5 | 10.5 | gangway | 0.95 | 6.05 | 572.5 | 566.9 | 510.6 | 2820.4 | 0.021 |
| 2 | -10.5 | -17.5 | gangway | 0.95 | 6.11 | 576.8 | 567.9 | 508.3 | 2809.6 | 0.021 |
| 3 | 18.5 | 10.5 | gangway | 0.94 | 6.21 | 574.0 | 566.9 | 496.6 | 2778.4 | 0.027 |
| 4 | -17.5 | -10.5 | gangway | 0.95 | 6.05 | 571.8 | 567.4 | 505.8 | 2778.2 | 0.022 |
| 5 | -10.5 | 17.5 | gangway | 0.95 | 6.04 | 575.1 | 564.9 | 509.7 | 2765.5 | 0.022 |
| 6 | 10.5 | 18.5 | gangway | 0.94 | 6.15 | 577.2 | 566.2 | 503.7 | 2764.9 | 0.028 |
| 7 | -11.5 | 16.5 | gangway | 0.92 | 6.18 | 557.3 | 551.1 | 520.2 | 2757.8 | 0.014 |
| 8 | -10.5 | -18.5 | gangway | 0.94 | 6.17 | 578.6 | 559.9 | 497.4 | 2755.0 | 0.028 |
| 9 | 10.5 | 17.5 | gangway | 0.95 | 6.03 | 575.4 | 569.7 | 504.1 | 2754.0 | 0.022 |
| 10 | 17.5 | -10.5 | gangway | 0.95 | 5.99 | 575.1 | 569.1 | 506.4 | 2751.9 | 0.022 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 18.5 | 9.5 | seat row | 0.50 | 7.60 | 552.0 | 549.0 | 540.1 | 1980.3 | 0.011 |
| 2 | 9.5 | 18.5 | seat row | 0.50 | 7.51 | 551.5 | 548.9 | 541.0 | 1969.0 | 0.011 |
| 3 | -18.5 | -9.5 | seat row | 0.50 | 7.56 | 549.0 | 546.4 | 535.0 | 1961.7 | 0.011 |
| 4 | -9.5 | -18.5 | seat row | 0.50 | 7.56 | 547.5 | 544.7 | 534.0 | 1949.4 | 0.011 |
| 5 | 18.5 | -9.5 | seat row | 0.50 | 7.56 | 543.6 | 540.8 | 532.2 | 1946.8 | 0.011 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 0; agent-steps of seated agents on another row's clearway: 0.

## Deposit check

Person-seconds deposited: 3951573.1, of them in excluded cells: 3638.820.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 717405 overlapping pair-steps: p99 0.0029, max 0.0158 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0029 max 0.0158; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00754 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 0 (longest 0 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.748557 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.36 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 0 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
