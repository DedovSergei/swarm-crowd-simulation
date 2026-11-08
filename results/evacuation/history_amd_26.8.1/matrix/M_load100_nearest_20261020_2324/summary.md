# Experiment `M_load100_nearest`

**Task 5.9 stage 4: venue M, 100% load, nearest exit (incline speed, stair spacing): the uninformed-crowd bound**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 15832 agents on 100% of the 15832 seats (spawnSeatedCrowd, seed 1337), buffer N = 16384, 4932 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **nearest exit, incline speed, stair spacing (empirical)**.
Capacity: **within design capacity** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-20T23:24:37, 97.3 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1757 | 307.3 |
| t90 | 4000 | 699.6 |
| t100 | 4932 | 862.6 |

t_p: the step by which ceil(p x 15832) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| -x | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| +y | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| -y | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| door +x+y (y wall) 0 | 1.20 | 1121 | 1121 | 4.9 | 862.6 | 65.3 | 85.3 | 12.8-22.7 |
| door +x+y (y wall) 1 | 1.20 | 676 | 680 | 4.9 | 545.5 | 62.5 | 85.3 | 12.8-22.7 |
| door +x+y (y wall) 2 | 1.20 | 174 | 178 | 4.9 | 183.5 | 48.7 | 80.2 | 4.7-14.7 |
| door +x+y (x wall) 0 | 1.20 | 1121 | 1121 | 4.9 | 848.5 | 66.4 | 85.3 | 12.8-22.7 |
| door +x+y (x wall) 1 | 1.20 | 684 | 680 | 4.9 | 549.9 | 62.7 | 85.3 | 12.8-22.7 |
| door +x+y (x wall) 2 | 1.20 | 182 | 178 | 4.9 | 187.8 | 49.7 | 80.2 | 4.7-14.7 |
| door +x+y (corner) | 1.20 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| door -x+y (y wall) 0 | 1.20 | 1121 | 1121 | 4.9 | 856.2 | 65.8 | 85.3 | 12.8-22.7 |
| door -x+y (y wall) 1 | 1.20 | 678 | 680 | 4.9 | 552.9 | 61.8 | 85.3 | 12.8-22.7 |
| door -x+y (y wall) 2 | 1.20 | 176 | 178 | 4.9 | 183.1 | 49.3 | 80.2 | 4.7-14.7 |
| door -x+y (x wall) 0 | 1.20 | 1121 | 1121 | 4.9 | 844.4 | 66.7 | 85.3 | 12.6-22.6 |
| door -x+y (x wall) 1 | 1.20 | 682 | 680 | 4.9 | 553.1 | 62.2 | 90.3 | 15.9-25.9 |
| door -x+y (x wall) 2 | 1.20 | 180 | 178 | 4.9 | 184.9 | 50.0 | 80.2 | 4.7-14.7 |
| door -x+y (corner) | 1.20 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| door -x-y (y wall) 0 | 1.20 | 1121 | 1121 | 4.9 | 852.1 | 66.1 | 85.3 | 12.6-22.6 |
| door -x-y (y wall) 1 | 1.20 | 684 | 680 | 4.9 | 555.9 | 62.1 | 85.3 | 12.6-22.6 |
| door -x-y (y wall) 2 | 1.20 | 179 | 178 | 4.9 | 182.3 | 50.4 | 80.2 | 4.7-14.7 |
| door -x-y (x wall) 0 | 1.20 | 1121 | 1121 | 4.9 | 862.5 | 65.3 | 90.3 | 16.3-26.2 |
| door -x-y (x wall) 1 | 1.20 | 676 | 680 | 4.9 | 550.6 | 61.9 | 90.3 | 15.9-25.9 |
| door -x-y (x wall) 2 | 1.20 | 177 | 178 | 4.9 | 181.7 | 50.0 | 80.2 | 4.7-14.7 |
| door -x-y (corner) | 1.20 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| door +x-y (y wall) 0 | 1.20 | 1121 | 1121 | 4.9 | 856.3 | 65.8 | 85.3 | 12.6-22.6 |
| door +x-y (y wall) 1 | 1.20 | 686 | 680 | 4.9 | 549.9 | 62.9 | 90.3 | 15.9-25.9 |
| door +x-y (y wall) 2 | 1.20 | 177 | 178 | 4.9 | 180.7 | 50.3 | 80.2 | 4.7-14.7 |
| door +x-y (x wall) 0 | 1.20 | 1121 | 1121 | 4.9 | 851.1 | 66.2 | 85.3 | 12.8-22.7 |
| door +x-y (x wall) 1 | 1.20 | 674 | 680 | 4.9 | 548.3 | 62.0 | 85.3 | 12.8-22.7 |
| door +x-y (x wall) 2 | 1.20 | 179 | 178 | 4.9 | 182.1 | 50.5 | 80.2 | 4.7-14.7 |
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
| door +x+y (y wall) 0 | door | 1.20 | 1121 | 7.1% | 77.7% |
| door +x+y (y wall) 1 | door | 1.20 | 676 | 4.3% | 46.9% |
| door +x+y (y wall) 2 | door | 1.20 | 174 | 1.1% | 12.1% |
| door +x+y (x wall) 0 | door | 1.20 | 1121 | 7.1% | 77.7% |
| door +x+y (x wall) 1 | door | 1.20 | 684 | 4.3% | 47.4% |
| door +x+y (x wall) 2 | door | 1.20 | 182 | 1.1% | 12.6% |
| door +x+y (corner) | door | 1.20 | 0 | 0.0% | 0.0% |
| door -x+y (y wall) 0 | door | 1.20 | 1121 | 7.1% | 77.7% |
| door -x+y (y wall) 1 | door | 1.20 | 678 | 4.3% | 47.0% |
| door -x+y (y wall) 2 | door | 1.20 | 176 | 1.1% | 12.2% |
| door -x+y (x wall) 0 | door | 1.20 | 1121 | 7.1% | 77.7% |
| door -x+y (x wall) 1 | door | 1.20 | 682 | 4.3% | 47.3% |
| door -x+y (x wall) 2 | door | 1.20 | 180 | 1.1% | 12.5% |
| door -x+y (corner) | door | 1.20 | 0 | 0.0% | 0.0% |
| door -x-y (y wall) 0 | door | 1.20 | 1121 | 7.1% | 77.7% |
| door -x-y (y wall) 1 | door | 1.20 | 684 | 4.3% | 47.4% |
| door -x-y (y wall) 2 | door | 1.20 | 179 | 1.1% | 12.4% |
| door -x-y (x wall) 0 | door | 1.20 | 1121 | 7.1% | 77.7% |
| door -x-y (x wall) 1 | door | 1.20 | 676 | 4.3% | 46.9% |
| door -x-y (x wall) 2 | door | 1.20 | 177 | 1.1% | 12.3% |
| door -x-y (corner) | door | 1.20 | 0 | 0.0% | 0.0% |
| door +x-y (y wall) 0 | door | 1.20 | 1121 | 7.1% | 77.7% |
| door +x-y (y wall) 1 | door | 1.20 | 686 | 4.3% | 47.6% |
| door +x-y (y wall) 2 | door | 1.20 | 177 | 1.1% | 12.3% |
| door +x-y (x wall) 0 | door | 1.20 | 1121 | 7.1% | 77.7% |
| door +x-y (x wall) 1 | door | 1.20 | 674 | 4.3% | 46.7% |
| door +x-y (x wall) 2 | door | 1.20 | 179 | 1.1% | 12.4% |
| door +x-y (corner) | door | 1.20 | 0 | 0.0% | 0.0% |
| **doors (28)** | door | 33.60 | 15832 | 100.0% | |
| **avenues (4)** | avenue | 22.64 | 0 | 0.0% | |

**Unused exit width: 27.4 of 56.2 m (48.8%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 862.6 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 23.4%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight +x+y (y wing) 1 | straight | yes | 676 | 4.3% | 676 | 4.3% |
| straight +x+y (y wing) 2 | straight | yes | 174 | 1.1% | 174 | 1.1% |
| straight +x+y (x wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight +x+y (x wing) 1 | straight | yes | 684 | 4.3% | 684 | 4.3% |
| straight +x+y (x wing) 2 | straight | yes | 182 | 1.1% | 182 | 1.1% |
| corner +x+y | corner | yes | 450 | 2.8% | 0 | 0.0% |
| straight -x+y (y wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight -x+y (y wing) 1 | straight | yes | 678 | 4.3% | 678 | 4.3% |
| straight -x+y (y wing) 2 | straight | yes | 176 | 1.1% | 176 | 1.1% |
| straight -x+y (x wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight -x+y (x wing) 1 | straight | yes | 682 | 4.3% | 682 | 4.3% |
| straight -x+y (x wing) 2 | straight | yes | 180 | 1.1% | 180 | 1.1% |
| corner -x+y | corner | yes | 449 | 2.8% | 0 | 0.0% |
| straight -x-y (y wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight -x-y (y wing) 1 | straight | yes | 684 | 4.3% | 684 | 4.3% |
| straight -x-y (y wing) 2 | straight | yes | 179 | 1.1% | 179 | 1.1% |
| straight -x-y (x wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight -x-y (x wing) 1 | straight | yes | 676 | 4.3% | 676 | 4.3% |
| straight -x-y (x wing) 2 | straight | yes | 177 | 1.1% | 177 | 1.1% |
| corner -x-y | corner | yes | 450 | 2.8% | 0 | 0.0% |
| straight +x-y (y wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight +x-y (y wing) 1 | straight | yes | 686 | 4.3% | 686 | 4.3% |
| straight +x-y (y wing) 2 | straight | yes | 177 | 1.1% | 177 | 1.1% |
| straight +x-y (x wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight +x-y (x wing) 1 | straight | yes | 674 | 4.3% | 674 | 4.3% |
| straight +x-y (x wing) 2 | straight | yes | 179 | 1.1% | 179 | 1.1% |
| corner +x-y | corner | yes | 450 | 2.8% | 0 | 0.0% |
| **straight (24)** | | | 15832 | | 15832 | 100.0% |
| **corner (4)** | | | 1799 | | 0 | 0.0% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| door +x+y (y wall) 0 | 1121 | 4.9 | 862.6 | 0.78 | 1.02 | 31.0% |
| door +x+y (y wall) 1 | 676 | 4.9 | 545.5 | 0.75 | 1.02 | 30.9% |
| door +x+y (y wall) 2 | 174 | 4.9 | 183.5 | 0.58 | 0.96 | 15.8% |
| door +x+y (x wall) 0 | 1121 | 4.9 | 848.5 | 0.79 | 1.02 | 40.7% |
| door +x+y (x wall) 1 | 684 | 4.9 | 549.9 | 0.75 | 1.02 | 33.9% |
| door +x+y (x wall) 2 | 182 | 4.9 | 187.8 | 0.59 | 0.96 | 15.8% |
| door -x+y (y wall) 0 | 1121 | 4.9 | 856.2 | 0.79 | 1.02 | 38.4% |
| door -x+y (y wall) 1 | 678 | 4.9 | 552.9 | 0.74 | 1.02 | 26.8% |
| door -x+y (y wall) 2 | 176 | 4.9 | 183.1 | 0.59 | 0.96 | 15.8% |
| door -x+y (x wall) 0 | 1121 | 4.9 | 844.4 | 0.80 | 1.02 | 42.4% |
| door -x+y (x wall) 1 | 682 | 4.9 | 553.1 | 0.74 | 1.08 | 26.8% |
| door -x+y (x wall) 2 | 180 | 4.9 | 184.9 | 0.60 | 0.96 | 10.5% |
| door -x-y (y wall) 0 | 1121 | 4.9 | 852.1 | 0.79 | 1.02 | 34.9% |
| door -x-y (y wall) 1 | 684 | 4.9 | 555.9 | 0.74 | 1.02 | 39.3% |
| door -x-y (y wall) 2 | 179 | 4.9 | 182.3 | 0.60 | 0.96 | 10.5% |
| door -x-y (x wall) 0 | 1121 | 4.9 | 862.5 | 0.78 | 1.08 | 32.2% |
| door -x-y (x wall) 1 | 676 | 4.9 | 550.6 | 0.74 | 1.08 | 26.8% |
| door -x-y (x wall) 2 | 177 | 4.9 | 181.7 | 0.60 | 0.96 | 15.8% |
| door +x-y (y wall) 0 | 1121 | 4.9 | 856.3 | 0.79 | 1.02 | 40.7% |
| door +x-y (y wall) 1 | 686 | 4.9 | 549.9 | 0.75 | 1.08 | 39.3% |
| door +x-y (y wall) 2 | 177 | 4.9 | 180.7 | 0.60 | 0.96 | 15.8% |
| door +x-y (x wall) 0 | 1121 | 4.9 | 851.1 | 0.79 | 1.02 | 37.2% |
| door +x-y (x wall) 1 | 674 | 4.9 | 548.3 | 0.74 | 1.02 | 36.4% |
| door +x-y (x wall) 2 | 179 | 4.9 | 182.1 | 0.60 | 0.96 | 21.1% |

Mean flow / w J averaged over the doors 0.71, over the avenues nan.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 859.7 | 1.30 | 1.71 | 92% | 83% | 9% | 3.97 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 565 | 676 / 0 / 0 | 0.7 | 542.6 | 1.25 | 1.71 | 75% | 69% | 5% | 3.97 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 68 | 174 / 0 / 0 | 0.7 | 180.5 | 0.97 | 1.50 | 32% | 32% | 0% | 2.67 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 845.5 | 1.33 | 1.71 | 93% | 85% | 8% | 4.00 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 565 | 684 / 0 / 0 | 0.7 | 546.9 | 1.25 | 1.71 | 75% | 73% | 2% | 4.07 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 68 | 182 / 0 / 0 | 0.7 | 184.9 | 0.99 | 1.50 | 32% | 26% | 5% | 2.64 |
| corner +x+y | 1.20 | 85.6 | 450 | 0 / 0 / 450 | 0.7 | 514.8 | 0.88 | 2.11 | 92% | 19% | 73% | 1.56 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 853.2 | 1.31 | 1.71 | 92% | 85% | 7% | 4.01 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 565 | 678 / 0 / 0 | 0.7 | 549.9 | 1.23 | 1.71 | 75% | 70% | 5% | 3.97 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 68 | 176 / 0 / 0 | 0.7 | 180.2 | 0.98 | 1.50 | 32% | 26% | 5% | 2.67 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 841.5 | 1.33 | 1.71 | 92% | 84% | 8% | 4.06 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 565 | 682 / 0 / 0 | 0.7 | 550.1 | 1.24 | 1.71 | 75% | 70% | 5% | 3.95 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 69 | 180 / 0 / 0 | 0.7 | 181.9 | 0.99 | 1.50 | 37% | 26% | 11% | 2.53 |
| corner -x+y | 1.20 | 85.6 | 449 | 0 / 0 / 449 | 0.7 | 517.9 | 0.87 | 2.01 | 94% | 19% | 75% | 1.55 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 849.2 | 1.32 | 1.71 | 92% | 85% | 7% | 4.04 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 565 | 684 / 0 / 0 | 0.7 | 552.9 | 1.24 | 1.71 | 73% | 68% | 5% | 3.99 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 68 | 179 / 0 / 0 | 0.7 | 179.3 | 1.00 | 1.50 | 33% | 33% | 0% | 2.68 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 859.5 | 1.31 | 1.71 | 92% | 83% | 9% | 4.02 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 565 | 676 / 0 / 1 | 0.7 | 547.6 | 1.24 | 1.71 | 76% | 69% | 7% | 3.88 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 68 | 177 / 0 / 0 | 0.7 | 178.8 | 0.99 | 1.50 | 33% | 28% | 6% | 2.67 |
| corner -x-y | 1.20 | 85.6 | 450 | 0 / 0 / 451 | 0.7 | 520.7 | 0.87 | 2.31 | 92% | 19% | 74% | 1.55 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 853.4 | 1.31 | 1.71 | 92% | 84% | 8% | 4.02 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 565 | 686 / 0 / 0 | 0.7 | 546.9 | 1.26 | 1.71 | 76% | 69% | 7% | 3.93 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 68 | 177 / 0 / 0 | 0.7 | 177.7 | 1.00 | 1.50 | 33% | 33% | 0% | 2.68 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 848.1 | 1.32 | 1.71 | 92% | 84% | 8% | 4.04 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 565 | 674 / 0 / 0 | 0.7 | 545.4 | 1.24 | 1.71 | 75% | 69% | 5% | 3.96 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 68 | 179 / 0 / 0 | 0.7 | 179.1 | 1.00 | 1.50 | 33% | 28% | 6% | 2.67 |
| corner +x-y | 1.20 | 85.6 | 450 | 0 / 0 / 450 | 0.7 | 514.8 | 0.88 | 2.11 | 92% | 17% | 75% | 1.53 |

The last agent out (agent 31, t100 862.6 s): last gangway straight +x+y (y wing) 0, exit -. The gangway that cleared last: straight +x+y (y wing) 0 at 859.7 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.82 | 857.6 / 798.1 / 755.6 | 808.2 / 798.1 / 739.0 | 1215332.5 | 2008647 | 0.130 |
| gangway | 1212 | 1112.9 | 6.82 | 857.6 / 798.1 / 755.6 | 808.2 / 798.1 / 739.0 | 1214425.6 | 1968220 | 0.108 |
| walkway | 276 | 257.4 | 0.12 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 9 | 0.019 |
| avenue | 912 | 858.9 | 0.17 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 13 | 0.142 |
| exit | 32 | 3.2 | 0.00 | 539.4 / 537.1 / 483.4 | 281.8 / 253.4 / 152.7 | 906.9 | 1262 | 1.326 |
| concourse | 1116 | 1043.8 | 1.98 | 769.1 / 0.0 / 0.0 | 142.2 / 0.0 / 0.0 | 0.0 | 39144 | 1.193 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.53 | 801.4 / 796.9 / 784.6 | 801.4 / 796.9 / 782.0 | 1287499.2 | 3315617 | 0.021 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 18.5 | 11.5 | gangway | 0.86 | 6.75 | 776.9 | 753.5 | 712.0 | 3948.9 | 0.017 |
| 2 | -16.5 | -11.5 | gangway | 0.92 | 6.13 | 786.0 | 782.2 | 739.0 | 3939.5 | 0.010 |
| 3 | 17.5 | 11.5 | gangway | 0.89 | 6.34 | 777.3 | 767.8 | 734.6 | 3935.7 | 0.014 |
| 4 | -17.5 | -11.5 | gangway | 0.89 | 6.37 | 790.4 | 778.2 | 737.9 | 3927.5 | 0.014 |
| 5 | -18.5 | -11.5 | gangway | 0.86 | 6.73 | 790.6 | 757.7 | 708.5 | 3914.3 | 0.017 |
| 6 | 11.5 | -17.5 | gangway | 0.89 | 6.33 | 775.2 | 760.7 | 725.7 | 3907.6 | 0.013 |
| 7 | 11.5 | 18.5 | gangway | 0.86 | 6.75 | 784.3 | 753.0 | 698.8 | 3877.9 | 0.016 |
| 8 | -11.5 | -18.5 | gangway | 0.86 | 6.82 | 777.5 | 749.3 | 699.8 | 3870.3 | 0.016 |
| 9 | -11.5 | -17.5 | gangway | 0.89 | 6.31 | 778.3 | 768.5 | 728.8 | 3850.6 | 0.014 |
| 10 | 11.5 | -18.5 | gangway | 0.86 | 6.73 | 777.1 | 736.0 | 699.8 | 3846.6 | 0.016 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -18.5 | -9.5 | seat row | 0.50 | 7.39 | 768.4 | 765.4 | 755.2 | 2687.3 | 0.008 |
| 2 | 18.5 | 9.5 | seat row | 0.50 | 7.43 | 766.3 | 763.5 | 751.9 | 2668.7 | 0.008 |
| 3 | 9.5 | 18.5 | seat row | 0.50 | 7.45 | 758.7 | 755.8 | 747.7 | 2666.9 | 0.008 |
| 4 | 18.5 | -9.5 | seat row | 0.50 | 7.53 | 753.5 | 751.9 | 744.4 | 2655.0 | 0.008 |
| 5 | -9.5 | -18.5 | seat row | 0.50 | 7.41 | 753.8 | 750.0 | 740.6 | 2654.2 | 0.008 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 0; agent-steps of seated agents on another row's clearway: 0.

## Deposit check

Person-seconds deposited: 5327892.2, of them in excluded cells: 3627.475.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 939035 overlapping pair-steps: p99 0.0020, max 0.0086 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0020 max 0.0086; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00758 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 0 (longest 0 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.748545 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.23 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 0 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
