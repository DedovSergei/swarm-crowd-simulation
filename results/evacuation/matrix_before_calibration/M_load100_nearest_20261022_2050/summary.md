# Experiment `M_load100_nearest`

**Task 5.10 stage 4 (AMD 26.10.1): Task 5.8's model (the level spacing on the gangway inclines, --stair-flow off): venue M, 100% load, nearest exit (incline speed)**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 15832 agents on 100% of the 15832 seats (spawnSeatedCrowd, seed 1337), buffer N = 16384, 3637 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **nearest exit, incline speed**.
Capacity: **within design capacity** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T20:50:34, 259.1 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1305 | 228.3 |
| t90 | 2947 | 515.5 |
| t100 | 3637 | 636.1 |

t_p: the step by which ceil(p x 15832) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| -x | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| +y | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| -y | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| door +x+y (y wall) 0 | 1.20 | 1121 | 1121 | 4.9 | 636.1 | 88.8 | 110.3 | 24.7-34.6 |
| door +x+y (y wall) 1 | 1.20 | 678 | 680 | 4.9 | 406.7 | 84.3 | 110.3 | 28.5-38.5 |
| door +x+y (y wall) 2 | 1.20 | 177 | 178 | 4.9 | 139.2 | 65.8 | 110.3 | 14.5-24.5 |
| door +x+y (x wall) 0 | 1.20 | 1121 | 1121 | 4.9 | 630.2 | 89.6 | 105.3 | 18.2-28.2 |
| door +x+y (x wall) 1 | 1.20 | 682 | 680 | 4.9 | 408.2 | 84.5 | 105.3 | 27.5-37.4 |
| door +x+y (x wall) 2 | 1.20 | 179 | 178 | 4.9 | 139.2 | 66.5 | 110.3 | 14.5-24.5 |
| door +x+y (corner) | 1.20 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| door -x+y (y wall) 0 | 1.20 | 1121 | 1121 | 4.9 | 627.9 | 89.9 | 105.3 | 148.3-158.3 |
| door -x+y (y wall) 1 | 1.20 | 675 | 680 | 4.9 | 403.3 | 84.7 | 105.3 | 23.4-33.4 |
| door -x+y (y wall) 2 | 1.20 | 176 | 178 | 4.9 | 140.6 | 64.8 | 105.3 | 7.7-17.7 |
| door -x+y (x wall) 0 | 1.20 | 1121 | 1121 | 4.9 | 629.3 | 89.7 | 105.3 | 104.4-114.4 |
| door -x+y (x wall) 1 | 1.20 | 685 | 680 | 4.9 | 407.0 | 85.1 | 105.3 | 22.0-32.0 |
| door -x+y (x wall) 2 | 1.20 | 180 | 178 | 4.9 | 142.2 | 65.5 | 105.3 | 9.6-19.6 |
| door -x+y (corner) | 1.20 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| door -x-y (y wall) 0 | 1.20 | 1121 | 1121 | 4.9 | 626.7 | 90.1 | 115.3 | 25.4-35.3 |
| door -x-y (y wall) 1 | 1.20 | 680 | 680 | 4.9 | 408.4 | 84.2 | 110.3 | 25.7-35.7 |
| door -x-y (y wall) 2 | 1.20 | 178 | 178 | 4.9 | 139.9 | 65.8 | 110.3 | 11.9-21.9 |
| door -x-y (x wall) 0 | 1.20 | 1121 | 1121 | 4.9 | 631.4 | 89.4 | 105.3 | 27.3-37.3 |
| door -x-y (x wall) 1 | 1.20 | 680 | 680 | 4.9 | 407.2 | 84.5 | 105.3 | 41.3-51.2 |
| door -x-y (x wall) 2 | 1.20 | 178 | 178 | 4.9 | 140.5 | 65.6 | 105.3 | 8.7-18.7 |
| door -x-y (corner) | 1.20 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| door +x-y (y wall) 0 | 1.20 | 1121 | 1121 | 4.9 | 626.7 | 90.1 | 105.3 | 203.1-213.0 |
| door +x-y (y wall) 1 | 1.20 | 680 | 680 | 4.9 | 405.6 | 84.8 | 105.3 | 34.1-44.1 |
| door +x-y (y wall) 2 | 1.20 | 181 | 178 | 4.9 | 137.8 | 68.0 | 110.3 | 13.1-23.1 |
| door +x-y (x wall) 0 | 1.20 | 1121 | 1121 | 4.9 | 629.8 | 89.7 | 110.3 | 27.1-37.1 |
| door +x-y (x wall) 1 | 1.20 | 680 | 680 | 4.9 | 406.1 | 84.7 | 105.3 | 25.2-35.2 |
| door +x-y (x wall) 2 | 1.20 | 175 | 178 | 4.9 | 136.4 | 66.4 | 105.3 | 7.7-17.7 |
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
| door +x+y (y wall) 0 | door | 1.20 | 1121 | 7.1% | 105.4% |
| door +x+y (y wall) 1 | door | 1.20 | 678 | 4.3% | 63.7% |
| door +x+y (y wall) 2 | door | 1.20 | 177 | 1.1% | 16.6% |
| door +x+y (x wall) 0 | door | 1.20 | 1121 | 7.1% | 105.4% |
| door +x+y (x wall) 1 | door | 1.20 | 682 | 4.3% | 64.1% |
| door +x+y (x wall) 2 | door | 1.20 | 179 | 1.1% | 16.8% |
| door +x+y (corner) | door | 1.20 | 0 | 0.0% | 0.0% |
| door -x+y (y wall) 0 | door | 1.20 | 1121 | 7.1% | 105.4% |
| door -x+y (y wall) 1 | door | 1.20 | 675 | 4.3% | 63.5% |
| door -x+y (y wall) 2 | door | 1.20 | 176 | 1.1% | 16.5% |
| door -x+y (x wall) 0 | door | 1.20 | 1121 | 7.1% | 105.4% |
| door -x+y (x wall) 1 | door | 1.20 | 685 | 4.3% | 64.4% |
| door -x+y (x wall) 2 | door | 1.20 | 180 | 1.1% | 16.9% |
| door -x+y (corner) | door | 1.20 | 0 | 0.0% | 0.0% |
| door -x-y (y wall) 0 | door | 1.20 | 1121 | 7.1% | 105.4% |
| door -x-y (y wall) 1 | door | 1.20 | 680 | 4.3% | 63.9% |
| door -x-y (y wall) 2 | door | 1.20 | 178 | 1.1% | 16.7% |
| door -x-y (x wall) 0 | door | 1.20 | 1121 | 7.1% | 105.4% |
| door -x-y (x wall) 1 | door | 1.20 | 680 | 4.3% | 63.9% |
| door -x-y (x wall) 2 | door | 1.20 | 178 | 1.1% | 16.7% |
| door -x-y (corner) | door | 1.20 | 0 | 0.0% | 0.0% |
| door +x-y (y wall) 0 | door | 1.20 | 1121 | 7.1% | 105.4% |
| door +x-y (y wall) 1 | door | 1.20 | 680 | 4.3% | 63.9% |
| door +x-y (y wall) 2 | door | 1.20 | 181 | 1.1% | 17.0% |
| door +x-y (x wall) 0 | door | 1.20 | 1121 | 7.1% | 105.4% |
| door +x-y (x wall) 1 | door | 1.20 | 680 | 4.3% | 63.9% |
| door +x-y (x wall) 2 | door | 1.20 | 175 | 1.1% | 16.5% |
| door +x-y (corner) | door | 1.20 | 0 | 0.0% | 0.0% |
| **doors (28)** | door | 33.60 | 15832 | 100.0% | |
| **avenues (4)** | avenue | 22.64 | 0 | 0.0% | |

**Unused exit width: 27.4 of 56.2 m (48.8%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 636.1 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 31.8%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight +x+y (y wing) 1 | straight | yes | 678 | 4.3% | 678 | 4.3% |
| straight +x+y (y wing) 2 | straight | yes | 177 | 1.1% | 177 | 1.1% |
| straight +x+y (x wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight +x+y (x wing) 1 | straight | yes | 682 | 4.3% | 682 | 4.3% |
| straight +x+y (x wing) 2 | straight | yes | 179 | 1.1% | 179 | 1.1% |
| corner +x+y | corner | yes | 450 | 2.8% | 0 | 0.0% |
| straight -x+y (y wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight -x+y (y wing) 1 | straight | yes | 675 | 4.3% | 675 | 4.3% |
| straight -x+y (y wing) 2 | straight | yes | 176 | 1.1% | 176 | 1.1% |
| straight -x+y (x wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight -x+y (x wing) 1 | straight | yes | 685 | 4.3% | 685 | 4.3% |
| straight -x+y (x wing) 2 | straight | yes | 180 | 1.1% | 180 | 1.1% |
| corner -x+y | corner | yes | 450 | 2.8% | 0 | 0.0% |
| straight -x-y (y wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight -x-y (y wing) 1 | straight | yes | 680 | 4.3% | 680 | 4.3% |
| straight -x-y (y wing) 2 | straight | yes | 178 | 1.1% | 178 | 1.1% |
| straight -x-y (x wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight -x-y (x wing) 1 | straight | yes | 680 | 4.3% | 680 | 4.3% |
| straight -x-y (x wing) 2 | straight | yes | 178 | 1.1% | 178 | 1.1% |
| corner -x-y | corner | yes | 450 | 2.8% | 0 | 0.0% |
| straight +x-y (y wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight +x-y (y wing) 1 | straight | yes | 680 | 4.3% | 680 | 4.3% |
| straight +x-y (y wing) 2 | straight | yes | 181 | 1.1% | 181 | 1.1% |
| straight +x-y (x wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight +x-y (x wing) 1 | straight | yes | 680 | 4.3% | 680 | 4.3% |
| straight +x-y (x wing) 2 | straight | yes | 175 | 1.1% | 175 | 1.1% |
| corner +x-y | corner | yes | 448 | 2.8% | 0 | 0.0% |
| **straight (24)** | | | 15832 | | 15832 | 100.0% |
| **corner (4)** | | | 1798 | | 0 | 0.0% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| door +x+y (y wall) 0 | 1121 | 4.9 | 636.1 | 1.06 | 1.32 | 96.9% |
| door +x+y (y wall) 1 | 678 | 4.9 | 406.7 | 1.01 | 1.32 | 82.9% |
| door +x+y (y wall) 2 | 177 | 4.9 | 139.2 | 0.79 | 1.32 | 42.9% |
| door +x+y (x wall) 0 | 1121 | 4.9 | 630.2 | 1.07 | 1.26 | 95.3% |
| door +x+y (x wall) 1 | 682 | 4.9 | 408.2 | 1.01 | 1.26 | 82.9% |
| door +x+y (x wall) 2 | 179 | 4.9 | 139.2 | 0.80 | 1.32 | 35.7% |
| door -x+y (y wall) 0 | 1121 | 4.9 | 627.9 | 1.08 | 1.26 | 96.8% |
| door -x+y (y wall) 1 | 675 | 4.9 | 403.3 | 1.01 | 1.26 | 82.9% |
| door -x+y (y wall) 2 | 176 | 4.9 | 140.6 | 0.77 | 1.26 | 40.0% |
| door -x+y (x wall) 0 | 1121 | 4.9 | 629.3 | 1.07 | 1.26 | 95.3% |
| door -x+y (x wall) 1 | 685 | 4.9 | 407.0 | 1.02 | 1.26 | 82.9% |
| door -x+y (x wall) 2 | 180 | 4.9 | 142.2 | 0.78 | 1.26 | 40.0% |
| door -x-y (y wall) 0 | 1121 | 4.9 | 626.7 | 1.08 | 1.38 | 96.8% |
| door -x-y (y wall) 1 | 680 | 4.9 | 408.4 | 1.01 | 1.32 | 82.9% |
| door -x-y (y wall) 2 | 178 | 4.9 | 139.9 | 0.79 | 1.32 | 40.0% |
| door -x-y (x wall) 0 | 1121 | 4.9 | 631.4 | 1.07 | 1.26 | 96.9% |
| door -x-y (x wall) 1 | 680 | 4.9 | 407.2 | 1.01 | 1.26 | 85.4% |
| door -x-y (x wall) 2 | 178 | 4.9 | 140.5 | 0.78 | 1.26 | 40.0% |
| door +x-y (y wall) 0 | 1121 | 4.9 | 626.7 | 1.08 | 1.26 | 96.8% |
| door +x-y (y wall) 1 | 680 | 4.9 | 405.6 | 1.01 | 1.26 | 82.9% |
| door +x-y (y wall) 2 | 181 | 4.9 | 137.8 | 0.81 | 1.32 | 35.7% |
| door +x-y (x wall) 0 | 1121 | 4.9 | 629.8 | 1.07 | 1.32 | 95.3% |
| door +x-y (x wall) 1 | 680 | 4.9 | 406.1 | 1.01 | 1.26 | 82.9% |
| door +x-y (x wall) 2 | 175 | 4.9 | 136.4 | 0.79 | 1.26 | 42.9% |

Mean flow / w J averaged over the doors 0.96, over the avenues nan.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 633.3 | 1.77 | 2.11 | 89% | 89% | 0% | 4.30 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 565 | 678 / 0 / 0 | 0.7 | 403.7 | 1.68 | 2.01 | 73% | 73% | 0% | 4.24 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 68 | 177 / 0 / 0 | 0.7 | 136.3 | 1.30 | 2.01 | 36% | 36% | 0% | 2.93 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 627.2 | 1.79 | 2.11 | 90% | 89% | 2% | 4.31 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 565 | 682 / 0 / 1 | 0.7 | 405.3 | 1.69 | 2.01 | 76% | 76% | 0% | 4.26 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 68 | 179 / 0 / 0 | 0.7 | 136.3 | 1.32 | 2.01 | 29% | 29% | 0% | 3.15 |
| corner +x+y | 1.20 | 85.6 | 450 | 0 / 0 / 451 | 0.7 | 373.1 | 1.21 | 2.61 | 92% | 13% | 79% | 1.48 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 624.9 | 1.80 | 2.01 | 90% | 90% | 0% | 4.28 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 565 | 675 / 0 / 0 | 0.7 | 400.4 | 1.69 | 2.11 | 76% | 76% | 0% | 4.14 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 68 | 176 / 0 / 0 | 0.7 | 137.7 | 1.28 | 1.91 | 29% | 29% | 0% | 3.13 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 626.3 | 1.79 | 2.01 | 90% | 89% | 2% | 4.32 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 565 | 685 / 0 / 0 | 0.7 | 404.0 | 1.70 | 2.01 | 73% | 73% | 0% | 4.19 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 68 | 180 / 0 / 0 | 0.7 | 139.2 | 1.30 | 2.01 | 36% | 36% | 0% | 2.85 |
| corner -x+y | 1.20 | 85.6 | 450 | 0 / 0 / 450 | 0.7 | 371.9 | 1.21 | 2.71 | 89% | 16% | 74% | 1.52 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 623.7 | 1.80 | 2.21 | 90% | 89% | 2% | 4.26 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 565 | 680 / 0 / 0 | 0.7 | 405.4 | 1.68 | 2.11 | 73% | 73% | 0% | 4.23 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 68 | 178 / 0 / 0 | 0.7 | 137.0 | 1.30 | 2.11 | 29% | 29% | 0% | 3.08 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 628.4 | 1.79 | 2.01 | 89% | 88% | 2% | 4.26 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 565 | 680 / 0 / 1 | 0.7 | 404.2 | 1.69 | 2.01 | 76% | 76% | 0% | 4.26 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 68 | 178 / 0 / 0 | 0.7 | 137.5 | 1.30 | 2.11 | 29% | 29% | 0% | 3.08 |
| corner -x-y | 1.20 | 85.6 | 450 | 0 / 0 / 451 | 0.7 | 373.3 | 1.21 | 2.61 | 92% | 18% | 74% | 1.50 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 623.7 | 1.80 | 2.01 | 90% | 89% | 2% | 4.34 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 566 | 680 / 0 / 0 | 0.7 | 402.6 | 1.69 | 2.01 | 73% | 73% | 0% | 4.21 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 68 | 181 / 0 / 0 | 0.7 | 134.9 | 1.35 | 2.01 | 29% | 29% | 0% | 3.05 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 626.9 | 1.79 | 2.01 | 90% | 89% | 2% | 4.28 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 566 | 680 / 0 / 1 | 0.7 | 403.2 | 1.69 | 2.01 | 73% | 73% | 0% | 4.24 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 68 | 175 / 0 / 0 | 0.7 | 133.5 | 1.32 | 2.11 | 29% | 29% | 0% | 3.14 |
| corner +x-y | 1.20 | 85.6 | 448 | 0 / 0 / 449 | 0.7 | 371.0 | 1.21 | 2.91 | 92% | 16% | 76% | 1.47 |

The last agent out (agent 15, t100 636.1 s): last gangway straight +x+y (y wing) 0, exit -. The gangway that cleared last: straight +x+y (y wing) 0 at 633.3 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.80 | 632.5 / 613.2 / 539.4 | 627.7 / 572.6 / 528.7 | 889582.7 | 1553411 | 0.168 |
| gangway | 1212 | 1112.9 | 6.80 | 632.5 / 613.2 / 539.4 | 627.7 / 572.6 / 528.7 | 888669.4 | 1512823 | 0.140 |
| walkway | 276 | 257.4 | 0.27 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 46 | 0.017 |
| avenue | 912 | 858.9 | 0.17 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 13 | 0.142 |
| exit | 32 | 3.2 | 0.00 | 399.8 / 398.3 / 374.8 | 282.3 / 257.8 / 155.3 | 913.3 | 1261 | 1.320 |
| concourse | 1116 | 1043.8 | 2.30 | 617.8 / 1.0 / 0.0 | 293.7 / 0.7 / 0.0 | 0.0 | 39269 | 1.190 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.55 | 573.7 / 572.5 / 568.3 | 573.7 / 572.5 / 565.6 | 888337.2 | 2391360 | 0.029 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -11.5 | -18.5 | gangway | 0.86 | 6.76 | 562.5 | 545.5 | 515.1 | 2832.3 | 0.023 |
| 2 | -18.5 | -11.5 | gangway | 0.86 | 6.80 | 567.2 | 537.1 | 494.3 | 2798.9 | 0.022 |
| 3 | -10.5 | -17.5 | gangway | 0.95 | 6.03 | 570.7 | 567.6 | 516.3 | 2780.3 | 0.022 |
| 4 | -10.5 | -18.5 | gangway | 0.94 | 6.17 | 572.6 | 559.5 | 505.5 | 2779.8 | 0.028 |
| 5 | -10.5 | 18.5 | gangway | 0.94 | 6.13 | 573.9 | 565.3 | 513.7 | 2741.7 | 0.029 |
| 6 | -11.5 | -17.5 | gangway | 0.89 | 6.48 | 558.8 | 555.9 | 528.7 | 2708.9 | 0.020 |
| 7 | -11.5 | 18.5 | gangway | 0.86 | 6.70 | 566.0 | 558.3 | 510.4 | 2707.2 | 0.024 |
| 8 | -18.5 | -10.5 | gangway | 0.94 | 6.13 | 577.4 | 553.8 | 486.8 | 2705.4 | 0.028 |
| 9 | 11.5 | -18.5 | gangway | 0.86 | 6.58 | 558.5 | 544.0 | 497.1 | 2704.6 | 0.023 |
| 10 | 18.5 | -11.5 | gangway | 0.86 | 6.74 | 556.2 | 543.4 | 499.0 | 2685.7 | 0.024 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -9.5 | -18.5 | seat row | 0.50 | 7.44 | 553.6 | 551.5 | 542.9 | 1962.1 | 0.011 |
| 2 | 9.5 | 14.5 | seat row | 0.50 | 7.16 | 573.7 | 572.5 | 565.6 | 1926.2 | 0.010 |
| 3 | -18.5 | -9.5 | seat row | 0.50 | 7.45 | 541.5 | 539.2 | 527.9 | 1922.2 | 0.010 |
| 4 | -9.5 | 18.5 | seat row | 0.50 | 7.40 | 545.5 | 542.2 | 534.5 | 1910.6 | 0.011 |
| 5 | 18.5 | -9.5 | seat row | 0.50 | 7.45 | 542.9 | 539.6 | 528.4 | 1895.1 | 0.011 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 0; agent-steps of seated agents on another row's clearway: 0.

## Deposit check

Person-seconds deposited: 3948412.4, of them in excluded cells: 3640.566.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 712608 overlapping pair-steps: p99 0.0034, max 0.0112 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0034 max 0.0112; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00751 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 0 (longest 0 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.748555 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.28 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 0 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
