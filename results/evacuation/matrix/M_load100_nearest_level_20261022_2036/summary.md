# Experiment `M_load100_nearest_level`

**Task 5.10 stage 4 (AMD 26.10.1) (model variants): venue M, 100% load, nearest exit, level walking speed**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 15832 agents on 100% of the 15832 seats (spawnSeatedCrowd, seed 1337), buffer N = 16384, 2690 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **nearest exit, level speed**.
Capacity: **within design capacity** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T20:36:34, 235.6 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 973 | 170.2 |
| t90 | 2186 | 382.3 |
| t100 | 2690 | 470.5 |

t_p: the step by which ceil(p x 15832) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| -x | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| +y | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| -y | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| door +x+y (y wall) 0 | 1.20 | 1121 | 1121 | 4.2 | 467.2 | 121.0 | 145.4 | 411.9-421.9 |
| door +x+y (y wall) 1 | 1.20 | 677 | 680 | 4.2 | 306.8 | 111.8 | 140.4 | 50.2-60.2 |
| door +x+y (y wall) 2 | 1.20 | 176 | 178 | 4.2 | 107.0 | 85.4 | 125.4 | 8.4-18.4 |
| door +x+y (x wall) 0 | 1.20 | 1121 | 1121 | 4.2 | 468.4 | 120.7 | 140.4 | 120.2-130.1 |
| door +x+y (x wall) 1 | 1.20 | 683 | 680 | 4.2 | 307.0 | 112.7 | 145.4 | 206.6-216.5 |
| door +x+y (x wall) 2 | 1.20 | 180 | 178 | 4.2 | 107.4 | 87.1 | 125.4 | 8.4-18.4 |
| door +x+y (corner) | 1.20 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| door -x+y (y wall) 0 | 1.20 | 1121 | 1121 | 4.2 | 467.2 | 121.0 | 145.4 | 330.7-340.7 |
| door -x+y (y wall) 1 | 1.20 | 679 | 680 | 4.2 | 300.0 | 114.7 | 145.4 | 218.5-228.4 |
| door -x+y (y wall) 2 | 1.20 | 176 | 178 | 4.2 | 109.0 | 83.9 | 135.4 | 14.7-24.7 |
| door -x+y (x wall) 0 | 1.20 | 1121 | 1121 | 4.2 | 461.4 | 122.5 | 145.4 | 33.9-43.9 |
| door -x+y (x wall) 1 | 1.20 | 681 | 680 | 4.2 | 300.0 | 115.1 | 140.4 | 21.0-31.0 |
| door -x+y (x wall) 2 | 1.20 | 180 | 178 | 4.2 | 109.1 | 85.6 | 130.4 | 9.4-19.4 |
| door -x+y (corner) | 1.20 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| door -x-y (y wall) 0 | 1.20 | 1121 | 1121 | 4.2 | 469.1 | 120.5 | 145.4 | 139.6-149.5 |
| door -x-y (y wall) 1 | 1.20 | 682 | 680 | 4.2 | 303.3 | 113.9 | 140.4 | 30.6-40.6 |
| door -x-y (y wall) 2 | 1.20 | 180 | 178 | 4.2 | 109.8 | 85.1 | 130.4 | 8.4-18.4 |
| door -x-y (x wall) 0 | 1.20 | 1121 | 1121 | 4.2 | 470.5 | 120.2 | 145.4 | 424.3-434.3 |
| door -x-y (x wall) 1 | 1.20 | 678 | 680 | 4.2 | 302.6 | 113.5 | 145.4 | 191.7-201.7 |
| door -x-y (x wall) 2 | 1.20 | 176 | 178 | 4.2 | 108.8 | 84.0 | 125.4 | 21.2-31.1 |
| door -x-y (corner) | 1.20 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| door +x-y (y wall) 0 | 1.20 | 1121 | 1121 | 4.2 | 463.2 | 122.1 | 145.4 | 264.3-274.3 |
| door +x-y (y wall) 1 | 1.20 | 683 | 680 | 4.2 | 305.4 | 113.3 | 140.4 | 37.4-47.4 |
| door +x-y (y wall) 2 | 1.20 | 177 | 178 | 4.2 | 106.7 | 86.2 | 135.4 | 31.3-41.3 |
| door +x-y (x wall) 0 | 1.20 | 1121 | 1121 | 4.2 | 466.5 | 121.2 | 150.5 | 147.8-157.8 |
| door +x-y (x wall) 1 | 1.20 | 677 | 680 | 4.2 | 305.4 | 112.3 | 145.4 | 63.8-73.8 |
| door +x-y (x wall) 2 | 1.20 | 179 | 178 | 4.2 | 106.7 | 87.2 | 140.4 | 27.1-37.1 |
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
| door +x+y (y wall) 0 | door | 1.20 | 1121 | 7.1% | 142.5% |
| door +x+y (y wall) 1 | door | 1.20 | 677 | 4.3% | 86.1% |
| door +x+y (y wall) 2 | door | 1.20 | 176 | 1.1% | 22.4% |
| door +x+y (x wall) 0 | door | 1.20 | 1121 | 7.1% | 142.5% |
| door +x+y (x wall) 1 | door | 1.20 | 683 | 4.3% | 86.8% |
| door +x+y (x wall) 2 | door | 1.20 | 180 | 1.1% | 22.9% |
| door +x+y (corner) | door | 1.20 | 0 | 0.0% | 0.0% |
| door -x+y (y wall) 0 | door | 1.20 | 1121 | 7.1% | 142.5% |
| door -x+y (y wall) 1 | door | 1.20 | 679 | 4.3% | 86.3% |
| door -x+y (y wall) 2 | door | 1.20 | 176 | 1.1% | 22.4% |
| door -x+y (x wall) 0 | door | 1.20 | 1121 | 7.1% | 142.5% |
| door -x+y (x wall) 1 | door | 1.20 | 681 | 4.3% | 86.6% |
| door -x+y (x wall) 2 | door | 1.20 | 180 | 1.1% | 22.9% |
| door -x+y (corner) | door | 1.20 | 0 | 0.0% | 0.0% |
| door -x-y (y wall) 0 | door | 1.20 | 1121 | 7.1% | 142.5% |
| door -x-y (y wall) 1 | door | 1.20 | 682 | 4.3% | 86.7% |
| door -x-y (y wall) 2 | door | 1.20 | 180 | 1.1% | 22.9% |
| door -x-y (x wall) 0 | door | 1.20 | 1121 | 7.1% | 142.5% |
| door -x-y (x wall) 1 | door | 1.20 | 678 | 4.3% | 86.2% |
| door -x-y (x wall) 2 | door | 1.20 | 176 | 1.1% | 22.4% |
| door -x-y (corner) | door | 1.20 | 0 | 0.0% | 0.0% |
| door +x-y (y wall) 0 | door | 1.20 | 1121 | 7.1% | 142.5% |
| door +x-y (y wall) 1 | door | 1.20 | 683 | 4.3% | 86.8% |
| door +x-y (y wall) 2 | door | 1.20 | 177 | 1.1% | 22.5% |
| door +x-y (x wall) 0 | door | 1.20 | 1121 | 7.1% | 142.5% |
| door +x-y (x wall) 1 | door | 1.20 | 677 | 4.3% | 86.1% |
| door +x-y (x wall) 2 | door | 1.20 | 179 | 1.1% | 22.8% |
| door +x-y (corner) | door | 1.20 | 0 | 0.0% | 0.0% |
| **doors (28)** | door | 33.60 | 15832 | 100.0% | |
| **avenues (4)** | avenue | 22.64 | 0 | 0.0% | |

**Unused exit width: 27.4 of 56.2 m (48.8%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 470.5 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 42.9%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight +x+y (y wing) 1 | straight | yes | 677 | 4.3% | 677 | 4.3% |
| straight +x+y (y wing) 2 | straight | yes | 176 | 1.1% | 176 | 1.1% |
| straight +x+y (x wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight +x+y (x wing) 1 | straight | yes | 683 | 4.3% | 683 | 4.3% |
| straight +x+y (x wing) 2 | straight | yes | 180 | 1.1% | 180 | 1.1% |
| corner +x+y | corner | yes | 450 | 2.8% | 0 | 0.0% |
| straight -x+y (y wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight -x+y (y wing) 1 | straight | yes | 679 | 4.3% | 679 | 4.3% |
| straight -x+y (y wing) 2 | straight | yes | 176 | 1.1% | 176 | 1.1% |
| straight -x+y (x wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight -x+y (x wing) 1 | straight | yes | 681 | 4.3% | 681 | 4.3% |
| straight -x+y (x wing) 2 | straight | yes | 180 | 1.1% | 180 | 1.1% |
| corner -x+y | corner | yes | 450 | 2.8% | 0 | 0.0% |
| straight -x-y (y wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight -x-y (y wing) 1 | straight | yes | 682 | 4.3% | 682 | 4.3% |
| straight -x-y (y wing) 2 | straight | yes | 180 | 1.1% | 180 | 1.1% |
| straight -x-y (x wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight -x-y (x wing) 1 | straight | yes | 678 | 4.3% | 678 | 4.3% |
| straight -x-y (x wing) 2 | straight | yes | 176 | 1.1% | 176 | 1.1% |
| corner -x-y | corner | yes | 450 | 2.8% | 0 | 0.0% |
| straight +x-y (y wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight +x-y (y wing) 1 | straight | yes | 683 | 4.3% | 683 | 4.3% |
| straight +x-y (y wing) 2 | straight | yes | 177 | 1.1% | 177 | 1.1% |
| straight +x-y (x wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight +x-y (x wing) 1 | straight | yes | 677 | 4.3% | 677 | 4.3% |
| straight +x-y (x wing) 2 | straight | yes | 179 | 1.1% | 179 | 1.1% |
| corner +x-y | corner | yes | 449 | 2.8% | 0 | 0.0% |
| **straight (24)** | | | 15832 | | 15832 | 100.0% |
| **corner (4)** | | | 1799 | | 0 | 0.0% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| door +x+y (y wall) 0 | 1121 | 4.2 | 467.2 | 1.45 | 1.74 | 100.0% |
| door +x+y (y wall) 1 | 677 | 4.2 | 306.8 | 1.34 | 1.68 | 87.1% |
| door +x+y (y wall) 2 | 176 | 4.2 | 107.0 | 1.02 | 1.50 | 45.5% |
| door +x+y (x wall) 0 | 1121 | 4.2 | 468.4 | 1.44 | 1.68 | 100.0% |
| door +x+y (x wall) 1 | 683 | 4.2 | 307.0 | 1.35 | 1.74 | 87.1% |
| door +x+y (x wall) 2 | 180 | 4.2 | 107.4 | 1.04 | 1.50 | 45.5% |
| door -x+y (y wall) 0 | 1121 | 4.2 | 467.2 | 1.45 | 1.74 | 97.9% |
| door -x+y (y wall) 1 | 679 | 4.2 | 300.0 | 1.37 | 1.74 | 83.9% |
| door -x+y (y wall) 2 | 176 | 4.2 | 109.0 | 1.00 | 1.62 | 45.5% |
| door -x+y (x wall) 0 | 1121 | 4.2 | 461.4 | 1.47 | 1.74 | 97.9% |
| door -x+y (x wall) 1 | 681 | 4.2 | 300.0 | 1.38 | 1.68 | 87.1% |
| door -x+y (x wall) 2 | 180 | 4.2 | 109.1 | 1.02 | 1.56 | 45.5% |
| door -x-y (y wall) 0 | 1121 | 4.2 | 469.1 | 1.44 | 1.74 | 97.9% |
| door -x-y (y wall) 1 | 682 | 4.2 | 303.3 | 1.36 | 1.68 | 87.1% |
| door -x-y (y wall) 2 | 180 | 4.2 | 109.8 | 1.02 | 1.56 | 50.0% |
| door -x-y (x wall) 0 | 1121 | 4.2 | 470.5 | 1.44 | 1.74 | 97.9% |
| door -x-y (x wall) 1 | 678 | 4.2 | 302.6 | 1.36 | 1.74 | 87.1% |
| door -x-y (x wall) 2 | 176 | 4.2 | 108.8 | 1.00 | 1.50 | 45.5% |
| door +x-y (y wall) 0 | 1121 | 4.2 | 463.2 | 1.46 | 1.74 | 97.9% |
| door +x-y (y wall) 1 | 683 | 4.2 | 305.4 | 1.36 | 1.68 | 87.1% |
| door +x-y (y wall) 2 | 177 | 4.2 | 106.7 | 1.03 | 1.62 | 45.5% |
| door +x-y (x wall) 0 | 1121 | 4.2 | 466.5 | 1.45 | 1.80 | 97.9% |
| door +x-y (x wall) 1 | 677 | 4.2 | 305.4 | 1.34 | 1.74 | 87.1% |
| door +x-y (x wall) 2 | 179 | 4.2 | 106.7 | 1.04 | 1.68 | 45.5% |

Mean flow / w J averaged over the doors 1.28, over the avenues nan.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 464.6 | 2.42 | 2.81 | 94% | 81% | 13% | 3.74 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 565 | 677 / 0 / 0 | 0.7 | 304.2 | 2.23 | 2.71 | 74% | 65% | 10% | 3.86 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 68 | 176 / 0 / 0 | 0.7 | 104.4 | 1.69 | 2.41 | 36% | 36% | 0% | 2.74 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 465.8 | 2.41 | 2.71 | 94% | 81% | 13% | 3.69 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 565 | 683 / 0 / 0 | 0.7 | 304.3 | 2.25 | 2.71 | 77% | 65% | 13% | 3.81 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 68 | 180 / 0 / 0 | 0.7 | 104.8 | 1.73 | 2.41 | 36% | 36% | 0% | 2.76 |
| corner +x+y | 1.20 | 85.6 | 450 | 0 / 0 / 450 | 0.7 | 290.3 | 1.55 | 3.21 | 90% | 10% | 80% | 1.43 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 464.6 | 2.42 | 2.71 | 91% | 81% | 11% | 3.72 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 565 | 679 / 0 / 0 | 0.7 | 297.3 | 2.29 | 2.71 | 77% | 67% | 10% | 3.85 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 68 | 176 / 0 / 0 | 0.7 | 106.3 | 1.66 | 2.21 | 36% | 36% | 0% | 2.65 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 458.8 | 2.45 | 2.71 | 91% | 81% | 11% | 3.73 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 565 | 681 / 0 / 0 | 0.7 | 297.3 | 2.29 | 2.61 | 80% | 67% | 13% | 3.81 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 68 | 180 / 0 / 0 | 0.7 | 106.5 | 1.70 | 2.41 | 36% | 27% | 9% | 2.69 |
| corner -x+y | 1.20 | 85.6 | 450 | 0 / 0 / 450 | 0.7 | 283.3 | 1.59 | 3.21 | 90% | 14% | 76% | 1.46 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 466.5 | 2.41 | 2.81 | 94% | 81% | 13% | 3.72 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 565 | 682 / 0 / 0 | 0.7 | 300.7 | 2.27 | 2.71 | 74% | 65% | 10% | 3.95 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 68 | 180 / 0 / 0 | 0.7 | 107.2 | 1.69 | 2.41 | 36% | 27% | 9% | 2.69 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 467.9 | 2.40 | 2.71 | 94% | 81% | 13% | 3.77 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 565 | 678 / 0 / 0 | 0.7 | 300.0 | 2.26 | 2.71 | 77% | 65% | 13% | 3.94 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 68 | 176 / 0 / 0 | 0.7 | 106.2 | 1.67 | 2.41 | 36% | 36% | 0% | 2.73 |
| corner -x-y | 1.20 | 85.6 | 450 | 0 / 0 / 450 | 0.7 | 286.7 | 1.57 | 3.21 | 93% | 14% | 79% | 1.46 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 460.5 | 2.44 | 2.71 | 91% | 81% | 11% | 3.75 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 565 | 683 / 0 / 0 | 0.7 | 302.8 | 2.26 | 2.71 | 77% | 65% | 13% | 3.81 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 68 | 177 / 0 / 0 | 0.7 | 104.1 | 1.71 | 2.41 | 36% | 27% | 9% | 2.67 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 463.9 | 2.42 | 2.81 | 94% | 81% | 13% | 3.63 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 566 | 677 / 0 / 0 | 0.7 | 302.8 | 2.24 | 2.71 | 74% | 65% | 10% | 3.83 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 68 | 179 / 0 / 0 | 0.7 | 103.9 | 1.73 | 2.51 | 36% | 27% | 9% | 2.63 |
| corner +x-y | 1.20 | 85.6 | 449 | 0 / 0 / 449 | 0.7 | 288.8 | 1.56 | 3.21 | 93% | 14% | 79% | 1.41 |

The last agent out (agent 9926, t100 470.5 s): last gangway straight -x-y (x wing) 0, exit -. The gangway that cleared last: straight -x-y (x wing) 0 at 467.9 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.75 | 466.8 / 438.8 / 410.3 | 442.2 / 438.7 / 397.2 | 655737.2 | 1076765 | 0.242 |
| gangway | 1212 | 1112.9 | 6.75 | 465.1 / 438.8 / 410.3 | 442.2 / 438.7 / 397.2 | 654919.5 | 1039053 | 0.204 |
| walkway | 276 | 257.4 | 0.10 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 4 | 0.021 |
| avenue | 912 | 858.9 | 0.17 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 13 | 0.142 |
| exit | 32 | 3.2 | 0.00 | 301.7 / 300.8 / 293.0 | 259.7 / 231.9 / 142.9 | 817.7 | 1129 | 1.306 |
| concourse | 1116 | 1043.8 | 3.26 | 463.7 / 36.7 / 0.0 | 280.6 / 13.5 / 0.0 | 0.0 | 36566 | 1.293 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.56 | 441.6 / 439.5 / 432.9 | 441.6 / 439.5 / 430.1 | 702609.8 | 1865660 | 0.036 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -10.5 | -16.5 | gangway | 0.96 | 5.84 | 442.2 | 435.7 | 394.6 | 2154.1 | 0.021 |
| 2 | 10.5 | 15.5 | gangway | 0.96 | 5.86 | 439.5 | 435.9 | 395.8 | 2153.7 | 0.017 |
| 3 | 16.5 | -10.5 | gangway | 0.96 | 5.83 | 434.1 | 431.5 | 386.7 | 2135.3 | 0.022 |
| 4 | -16.5 | -10.5 | gangway | 0.96 | 5.85 | 438.7 | 434.3 | 389.9 | 2132.6 | 0.022 |
| 5 | 16.5 | 10.5 | gangway | 0.96 | 5.86 | 437.6 | 433.6 | 393.5 | 2107.4 | 0.025 |
| 6 | -16.5 | 10.5 | gangway | 0.96 | 5.87 | 433.9 | 430.1 | 381.6 | 2103.6 | 0.023 |
| 7 | -10.5 | 16.5 | gangway | 0.96 | 5.84 | 434.1 | 427.8 | 379.9 | 2094.4 | 0.022 |
| 8 | -10.5 | -18.5 | gangway | 0.94 | 6.08 | 434.5 | 422.2 | 383.9 | 2074.7 | 0.037 |
| 9 | 15.5 | 10.5 | gangway | 0.96 | 5.92 | 440.8 | 435.7 | 393.7 | 2068.7 | 0.018 |
| 10 | -15.5 | 10.5 | gangway | 0.96 | 5.78 | 433.4 | 430.8 | 383.0 | 2067.1 | 0.017 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -14.5 | -9.5 | seat row | 0.50 | 7.35 | 439.2 | 437.4 | 430.1 | 1516.8 | 0.012 |
| 2 | -9.5 | 14.5 | seat row | 0.50 | 7.26 | 437.6 | 436.6 | 428.9 | 1505.9 | 0.012 |
| 3 | 14.5 | -9.5 | seat row | 0.50 | 7.30 | 435.5 | 432.5 | 424.1 | 1498.5 | 0.012 |
| 4 | 9.5 | 14.5 | seat row | 0.50 | 7.35 | 436.2 | 435.2 | 427.6 | 1488.1 | 0.013 |
| 5 | -9.5 | -14.5 | seat row | 0.50 | 7.29 | 434.5 | 431.3 | 421.9 | 1480.8 | 0.012 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 0; agent-steps of seated agents on another row's clearway: 0.

## Deposit check

Person-seconds deposited: 2945600.9, of them in excluded cells: 3176.494.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 566554 overlapping pair-steps: p99 0.0031, max 0.0318 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0031 max 0.0318; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 0 (longest 0 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.31 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 0 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
