# Experiment `M_load100_nearest_level`

**Task 5.9 stage 4 (model variants): venue M, 100% load, nearest exit, level walking speed**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 15832 agents on 100% of the 15832 seats (spawnSeatedCrowd, seed 1337), buffer N = 16384, 2715 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **nearest exit, level speed**.
Capacity: **within design capacity** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-20T23:58:06, 96.3 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 974 | 170.4 |
| t90 | 2189 | 382.9 |
| t100 | 2715 | 474.9 |

t_p: the step by which ceil(p x 15832) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| -x | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| +y | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| -y | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| door +x+y (y wall) 0 | 1.20 | 1121 | 1121 | 4.2 | 473.3 | 119.4 | 140.4 | 91.1-101.1 |
| door +x+y (y wall) 1 | 1.20 | 674 | 680 | 4.2 | 309.4 | 110.4 | 145.4 | 115.1-125.1 |
| door +x+y (y wall) 2 | 1.20 | 175 | 178 | 4.2 | 113.2 | 80.2 | 125.4 | 27.6-37.6 |
| door +x+y (x wall) 0 | 1.20 | 1121 | 1121 | 4.2 | 465.4 | 121.5 | 145.4 | 133.8-143.8 |
| door +x+y (x wall) 1 | 1.20 | 686 | 680 | 4.2 | 309.9 | 112.1 | 145.4 | 155.1-165.1 |
| door +x+y (x wall) 2 | 1.20 | 181 | 178 | 4.2 | 113.9 | 82.4 | 120.4 | 4.0-14.0 |
| door +x+y (corner) | 1.20 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| door -x+y (y wall) 0 | 1.20 | 1121 | 1121 | 4.2 | 464.0 | 121.8 | 145.4 | 203.6-213.6 |
| door -x+y (y wall) 1 | 1.20 | 675 | 680 | 4.2 | 304.7 | 112.3 | 140.4 | 31.3-41.3 |
| door -x+y (y wall) 2 | 1.20 | 181 | 178 | 4.2 | 109.0 | 86.2 | 130.4 | 24.7-34.6 |
| door -x+y (x wall) 0 | 1.20 | 1121 | 1121 | 4.2 | 465.6 | 121.4 | 140.4 | 117.0-127.0 |
| door -x+y (x wall) 1 | 1.20 | 685 | 680 | 4.2 | 304.2 | 114.1 | 145.4 | 25.0-35.0 |
| door -x+y (x wall) 2 | 1.20 | 175 | 178 | 4.2 | 109.1 | 83.2 | 125.4 | 4.7-14.7 |
| door -x+y (corner) | 1.20 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| door -x-y (y wall) 0 | 1.20 | 1121 | 1121 | 4.2 | 469.1 | 120.5 | 145.4 | 49.8-59.8 |
| door -x-y (y wall) 1 | 1.20 | 685 | 680 | 4.2 | 302.4 | 114.8 | 145.4 | 167.4-177.4 |
| door -x-y (y wall) 2 | 1.20 | 179 | 178 | 4.2 | 108.3 | 85.9 | 130.4 | 10.5-20.5 |
| door -x-y (x wall) 0 | 1.20 | 1121 | 1121 | 4.2 | 463.0 | 122.1 | 145.4 | 378.5-388.5 |
| door -x-y (x wall) 1 | 1.20 | 675 | 680 | 4.2 | 301.9 | 113.3 | 140.4 | 146.9-156.9 |
| door -x-y (x wall) 2 | 1.20 | 177 | 178 | 4.2 | 108.1 | 85.0 | 135.4 | 19.9-29.9 |
| door -x-y (corner) | 1.20 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| door +x-y (y wall) 0 | 1.20 | 1121 | 1121 | 4.2 | 467.4 | 121.0 | 145.4 | 152.3-162.3 |
| door +x-y (y wall) 1 | 1.20 | 683 | 680 | 4.2 | 300.3 | 115.3 | 140.4 | 75.2-85.2 |
| door +x-y (y wall) 2 | 1.20 | 179 | 178 | 4.2 | 109.1 | 85.1 | 125.4 | 4.7-14.7 |
| door +x-y (x wall) 0 | 1.20 | 1121 | 1121 | 4.2 | 474.9 | 119.0 | 140.4 | 278.1-288.1 |
| door +x-y (x wall) 1 | 1.20 | 677 | 680 | 4.2 | 300.8 | 114.0 | 150.5 | 210.6-220.6 |
| door +x-y (x wall) 2 | 1.20 | 177 | 178 | 4.2 | 109.3 | 84.1 | 135.4 | 17.3-27.3 |
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
| door +x+y (y wall) 0 | door | 1.20 | 1121 | 7.1% | 141.2% |
| door +x+y (y wall) 1 | door | 1.20 | 674 | 4.3% | 84.9% |
| door +x+y (y wall) 2 | door | 1.20 | 175 | 1.1% | 22.0% |
| door +x+y (x wall) 0 | door | 1.20 | 1121 | 7.1% | 141.2% |
| door +x+y (x wall) 1 | door | 1.20 | 686 | 4.3% | 86.4% |
| door +x+y (x wall) 2 | door | 1.20 | 181 | 1.1% | 22.8% |
| door +x+y (corner) | door | 1.20 | 0 | 0.0% | 0.0% |
| door -x+y (y wall) 0 | door | 1.20 | 1121 | 7.1% | 141.2% |
| door -x+y (y wall) 1 | door | 1.20 | 675 | 4.3% | 85.0% |
| door -x+y (y wall) 2 | door | 1.20 | 181 | 1.1% | 22.8% |
| door -x+y (x wall) 0 | door | 1.20 | 1121 | 7.1% | 141.2% |
| door -x+y (x wall) 1 | door | 1.20 | 685 | 4.3% | 86.3% |
| door -x+y (x wall) 2 | door | 1.20 | 175 | 1.1% | 22.0% |
| door -x+y (corner) | door | 1.20 | 0 | 0.0% | 0.0% |
| door -x-y (y wall) 0 | door | 1.20 | 1121 | 7.1% | 141.2% |
| door -x-y (y wall) 1 | door | 1.20 | 685 | 4.3% | 86.3% |
| door -x-y (y wall) 2 | door | 1.20 | 179 | 1.1% | 22.5% |
| door -x-y (x wall) 0 | door | 1.20 | 1121 | 7.1% | 141.2% |
| door -x-y (x wall) 1 | door | 1.20 | 675 | 4.3% | 85.0% |
| door -x-y (x wall) 2 | door | 1.20 | 177 | 1.1% | 22.3% |
| door -x-y (corner) | door | 1.20 | 0 | 0.0% | 0.0% |
| door +x-y (y wall) 0 | door | 1.20 | 1121 | 7.1% | 141.2% |
| door +x-y (y wall) 1 | door | 1.20 | 683 | 4.3% | 86.0% |
| door +x-y (y wall) 2 | door | 1.20 | 179 | 1.1% | 22.5% |
| door +x-y (x wall) 0 | door | 1.20 | 1121 | 7.1% | 141.2% |
| door +x-y (x wall) 1 | door | 1.20 | 677 | 4.3% | 85.3% |
| door +x-y (x wall) 2 | door | 1.20 | 177 | 1.1% | 22.3% |
| door +x-y (corner) | door | 1.20 | 0 | 0.0% | 0.0% |
| **doors (28)** | door | 33.60 | 15832 | 100.0% | |
| **avenues (4)** | avenue | 22.64 | 0 | 0.0% | |

**Unused exit width: 27.4 of 56.2 m (48.8%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 474.9 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 42.5%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight +x+y (y wing) 1 | straight | yes | 674 | 4.3% | 674 | 4.3% |
| straight +x+y (y wing) 2 | straight | yes | 175 | 1.1% | 175 | 1.1% |
| straight +x+y (x wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight +x+y (x wing) 1 | straight | yes | 686 | 4.3% | 686 | 4.3% |
| straight +x+y (x wing) 2 | straight | yes | 181 | 1.1% | 181 | 1.1% |
| corner +x+y | corner | yes | 450 | 2.8% | 0 | 0.0% |
| straight -x+y (y wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight -x+y (y wing) 1 | straight | yes | 675 | 4.3% | 675 | 4.3% |
| straight -x+y (y wing) 2 | straight | yes | 181 | 1.1% | 181 | 1.1% |
| straight -x+y (x wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight -x+y (x wing) 1 | straight | yes | 685 | 4.3% | 685 | 4.3% |
| straight -x+y (x wing) 2 | straight | yes | 175 | 1.1% | 175 | 1.1% |
| corner -x+y | corner | yes | 449 | 2.8% | 0 | 0.0% |
| straight -x-y (y wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight -x-y (y wing) 1 | straight | yes | 685 | 4.3% | 685 | 4.3% |
| straight -x-y (y wing) 2 | straight | yes | 179 | 1.1% | 179 | 1.1% |
| straight -x-y (x wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight -x-y (x wing) 1 | straight | yes | 675 | 4.3% | 675 | 4.3% |
| straight -x-y (x wing) 2 | straight | yes | 177 | 1.1% | 177 | 1.1% |
| corner -x-y | corner | yes | 450 | 2.8% | 0 | 0.0% |
| straight +x-y (y wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight +x-y (y wing) 1 | straight | yes | 683 | 4.3% | 683 | 4.3% |
| straight +x-y (y wing) 2 | straight | yes | 179 | 1.1% | 179 | 1.1% |
| straight +x-y (x wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight +x-y (x wing) 1 | straight | yes | 677 | 4.3% | 677 | 4.3% |
| straight +x-y (x wing) 2 | straight | yes | 177 | 1.1% | 177 | 1.1% |
| corner +x-y | corner | yes | 450 | 2.8% | 0 | 0.0% |
| **straight (24)** | | | 15832 | | 15832 | 100.0% |
| **corner (4)** | | | 1799 | | 0 | 0.0% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| door +x+y (y wall) 0 | 1121 | 4.2 | 473.3 | 1.43 | 1.68 | 97.9% |
| door +x+y (y wall) 1 | 674 | 4.2 | 309.4 | 1.32 | 1.74 | 84.4% |
| door +x+y (y wall) 2 | 175 | 4.2 | 113.2 | 0.96 | 1.50 | 50.0% |
| door +x+y (x wall) 0 | 1121 | 4.2 | 465.4 | 1.45 | 1.74 | 97.9% |
| door +x+y (x wall) 1 | 686 | 4.2 | 309.9 | 1.34 | 1.74 | 87.5% |
| door +x+y (x wall) 2 | 181 | 4.2 | 113.9 | 0.99 | 1.44 | 50.0% |
| door -x+y (y wall) 0 | 1121 | 4.2 | 464.0 | 1.46 | 1.74 | 97.9% |
| door -x+y (y wall) 1 | 675 | 4.2 | 304.7 | 1.34 | 1.68 | 87.1% |
| door -x+y (y wall) 2 | 181 | 4.2 | 109.0 | 1.03 | 1.56 | 54.5% |
| door -x+y (x wall) 0 | 1121 | 4.2 | 465.6 | 1.45 | 1.68 | 97.9% |
| door -x+y (x wall) 1 | 685 | 4.2 | 304.2 | 1.36 | 1.74 | 87.1% |
| door -x+y (x wall) 2 | 175 | 4.2 | 109.1 | 1.00 | 1.50 | 54.5% |
| door -x-y (y wall) 0 | 1121 | 4.2 | 469.1 | 1.44 | 1.74 | 97.9% |
| door -x-y (y wall) 1 | 685 | 4.2 | 302.4 | 1.37 | 1.74 | 87.1% |
| door -x-y (y wall) 2 | 179 | 4.2 | 108.3 | 1.03 | 1.56 | 54.5% |
| door -x-y (x wall) 0 | 1121 | 4.2 | 463.0 | 1.46 | 1.74 | 97.9% |
| door -x-y (x wall) 1 | 675 | 4.2 | 301.9 | 1.36 | 1.68 | 87.1% |
| door -x-y (x wall) 2 | 177 | 4.2 | 108.1 | 1.02 | 1.62 | 54.5% |
| door +x-y (y wall) 0 | 1121 | 4.2 | 467.4 | 1.45 | 1.74 | 100.0% |
| door +x-y (y wall) 1 | 683 | 4.2 | 300.3 | 1.38 | 1.68 | 87.1% |
| door +x-y (y wall) 2 | 179 | 4.2 | 109.1 | 1.02 | 1.50 | 54.5% |
| door +x-y (x wall) 0 | 1121 | 4.2 | 474.9 | 1.42 | 1.68 | 97.9% |
| door +x-y (x wall) 1 | 677 | 4.2 | 300.8 | 1.36 | 1.80 | 87.1% |
| door +x-y (x wall) 2 | 177 | 4.2 | 109.3 | 1.01 | 1.62 | 54.5% |

Mean flow / w J averaged over the doors 1.27, over the avenues nan.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 470.7 | 2.38 | 2.71 | 92% | 81% | 10% | 3.81 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 565 | 674 / 0 / 0 | 0.7 | 306.8 | 2.20 | 2.71 | 74% | 68% | 6% | 3.97 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 68 | 175 / 0 / 0 | 0.7 | 110.5 | 1.59 | 2.21 | 33% | 25% | 8% | 2.56 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 462.8 | 2.42 | 2.81 | 91% | 81% | 11% | 3.84 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 565 | 686 / 0 / 0 | 0.7 | 307.3 | 2.24 | 2.71 | 77% | 68% | 10% | 3.88 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 68 | 181 / 0 / 0 | 0.7 | 111.2 | 1.63 | 2.31 | 33% | 25% | 8% | 2.58 |
| corner +x+y | 1.20 | 85.6 | 450 | 0 / 0 / 450 | 0.7 | 293.3 | 1.54 | 3.21 | 90% | 13% | 77% | 1.51 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 461.4 | 2.43 | 2.91 | 91% | 81% | 11% | 3.85 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 565 | 675 / 0 / 0 | 0.7 | 302.1 | 2.24 | 2.61 | 77% | 68% | 10% | 3.82 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 68 | 181 / 0 / 0 | 0.7 | 106.3 | 1.71 | 2.61 | 36% | 27% | 9% | 2.47 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 463.0 | 2.42 | 2.71 | 91% | 81% | 11% | 3.85 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 566 | 685 / 0 / 1 | 0.7 | 301.5 | 2.28 | 2.81 | 77% | 68% | 10% | 3.75 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 68 | 175 / 0 / 0 | 0.7 | 106.5 | 1.65 | 2.51 | 36% | 27% | 9% | 2.55 |
| corner -x+y | 1.20 | 85.6 | 449 | 0 / 0 / 450 | 0.7 | 288.1 | 1.56 | 3.21 | 93% | 14% | 79% | 1.48 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 466.5 | 2.41 | 2.81 | 94% | 81% | 13% | 3.84 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 565 | 685 / 0 / 2 | 0.7 | 299.8 | 2.30 | 2.81 | 74% | 65% | 10% | 3.87 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 68 | 179 / 0 / 0 | 0.7 | 105.6 | 1.70 | 2.61 | 36% | 27% | 9% | 2.45 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 460.4 | 2.44 | 2.81 | 91% | 81% | 11% | 3.89 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 565 | 675 / 0 / 1 | 0.7 | 299.3 | 2.26 | 2.61 | 77% | 68% | 10% | 3.83 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 68 | 177 / 0 / 0 | 0.7 | 105.5 | 1.69 | 2.41 | 36% | 36% | 0% | 2.62 |
| corner -x-y | 1.20 | 85.6 | 450 | 0 / 0 / 453 | 0.7 | 285.8 | 1.59 | 3.21 | 93% | 14% | 79% | 1.50 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 464.7 | 2.41 | 2.81 | 94% | 81% | 13% | 3.84 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 565 | 683 / 0 / 2 | 0.7 | 297.5 | 2.31 | 2.61 | 80% | 70% | 10% | 3.80 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 68 | 179 / 0 / 0 | 0.7 | 106.5 | 1.69 | 2.51 | 36% | 27% | 9% | 2.54 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 472.2 | 2.38 | 2.61 | 92% | 79% | 12% | 3.81 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 565 | 677 / 0 / 1 | 0.7 | 298.2 | 2.28 | 2.91 | 80% | 70% | 10% | 3.79 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 68 | 177 / 0 / 0 | 0.7 | 106.7 | 1.67 | 2.61 | 36% | 27% | 9% | 2.53 |
| corner +x-y | 1.20 | 85.6 | 450 | 0 / 0 / 453 | 0.7 | 284.4 | 1.60 | 3.41 | 93% | 14% | 79% | 1.48 |

The last agent out (agent 13884, t100 474.9 s): last gangway straight +x-y (x wing) 0, exit -. The gangway that cleared last: straight +x-y (x wing) 0 at 472.2 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.79 | 469.1 / 444.4 / 419.1 | 447.6 / 444.3 / 393.4 | 654110.9 | 1091599 | 0.239 |
| gangway | 1212 | 1112.9 | 6.79 | 467.0 / 444.4 / 419.1 | 447.6 / 444.3 / 393.4 | 653293.6 | 1054253 | 0.201 |
| walkway | 276 | 257.4 | 0.11 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 17 | 0.013 |
| avenue | 912 | 858.9 | 0.17 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 13 | 0.142 |
| exit | 32 | 3.2 | 0.00 | 302.4 / 300.5 / 290.9 | 259.4 / 231.1 / 139.2 | 817.4 | 1124 | 1.313 |
| concourse | 1116 | 1043.8 | 2.85 | 467.4 / 22.0 / 0.0 | 275.3 / 3.8 / 0.0 | 0.0 | 36192 | 1.307 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.64 | 444.4 / 442.7 / 432.7 | 444.4 / 442.7 / 429.9 | 709444.0 | 1853956 | 0.037 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 11.5 | 18.5 | gangway | 0.86 | 6.64 | 428.3 | 414.4 | 388.5 | 2116.6 | 0.028 |
| 2 | 18.5 | -11.5 | gangway | 0.86 | 6.68 | 436.7 | 418.0 | 389.9 | 2111.6 | 0.030 |
| 3 | 11.5 | -18.5 | gangway | 0.86 | 6.68 | 428.9 | 407.7 | 386.4 | 2078.9 | 0.029 |
| 4 | 18.5 | -10.5 | gangway | 0.94 | 6.15 | 440.8 | 426.9 | 384.1 | 2073.3 | 0.036 |
| 5 | 11.5 | 17.5 | gangway | 0.89 | 6.24 | 430.4 | 423.6 | 392.1 | 2072.5 | 0.023 |
| 6 | 17.5 | -11.5 | gangway | 0.89 | 6.27 | 436.7 | 429.4 | 393.4 | 2062.3 | 0.024 |
| 7 | 10.5 | -18.5 | gangway | 0.94 | 6.12 | 436.2 | 419.8 | 381.8 | 2060.3 | 0.037 |
| 8 | 17.5 | 11.5 | gangway | 0.89 | 6.24 | 424.5 | 416.1 | 382.0 | 2054.3 | 0.023 |
| 9 | 18.5 | 11.5 | gangway | 0.86 | 6.57 | 422.4 | 404.7 | 378.3 | 2050.5 | 0.030 |
| 10 | -17.5 | -11.5 | gangway | 0.89 | 6.36 | 421.2 | 411.7 | 379.7 | 2050.4 | 0.022 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 18.5 | -9.5 | seat row | 0.50 | 7.49 | 426.4 | 424.1 | 417.9 | 1508.0 | 0.014 |
| 2 | 9.5 | 18.5 | seat row | 0.50 | 7.45 | 417.3 | 414.7 | 409.8 | 1487.6 | 0.013 |
| 3 | 9.5 | -18.5 | seat row | 0.50 | 7.49 | 418.6 | 416.8 | 408.6 | 1481.2 | 0.014 |
| 4 | -18.5 | 9.5 | seat row | 0.50 | 7.50 | 411.4 | 410.0 | 402.8 | 1471.5 | 0.014 |
| 5 | 9.5 | 14.5 | seat row | 0.50 | 7.17 | 440.1 | 438.5 | 429.9 | 1470.0 | 0.013 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 0; agent-steps of seated agents on another row's clearway: 0.

## Deposit check

Person-seconds deposited: 2948724.5, of them in excluded cells: 3168.838.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 619544 overlapping pair-steps: p99 0.0031, max 0.0253 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0031 max 0.0253; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 0 (longest 0 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.37 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 0 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
