# Experiment `M_load100_nearest`

**Task 5.10 stage 4 (AMD 26.10.1): venue M, 100% load, nearest exit (incline speed, stair spacing): the uninformed-crowd bound**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 15832 agents on 100% of the 15832 seats (spawnSeatedCrowd, seed 1337), buffer N = 16384, 4901 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **nearest exit, incline speed, stair spacing (empirical)**.
Capacity: **within design capacity** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T20:07:40, 271.7 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1750 | 306.1 |
| t90 | 3987 | 697.4 |
| t100 | 4901 | 857.2 |

t_p: the step by which ceil(p x 15832) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| -x | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| +y | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| -y | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| door +x+y (y wall) 0 | 1.20 | 1121 | 1121 | 4.9 | 847.6 | 66.5 | 90.3 | 32.0-42.0 |
| door +x+y (y wall) 1 | 1.20 | 672 | 680 | 4.9 | 551.7 | 61.4 | 85.3 | 17.5-27.5 |
| door +x+y (y wall) 2 | 1.20 | 177 | 178 | 4.9 | 185.2 | 49.0 | 80.2 | 4.7-14.7 |
| door +x+y (x wall) 0 | 1.20 | 1121 | 1121 | 4.9 | 850.6 | 66.3 | 85.3 | 15.6-25.5 |
| door +x+y (x wall) 1 | 1.20 | 688 | 680 | 4.9 | 555.2 | 62.5 | 85.3 | 15.6-25.5 |
| door +x+y (x wall) 2 | 1.20 | 179 | 178 | 4.9 | 184.7 | 49.7 | 80.2 | 4.7-14.7 |
| door +x+y (corner) | 1.20 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| door -x+y (y wall) 0 | 1.20 | 1121 | 1121 | 4.9 | 857.2 | 65.7 | 80.2 | 13.3-23.3 |
| door -x+y (y wall) 1 | 1.20 | 678 | 680 | 4.9 | 541.7 | 63.1 | 85.3 | 15.7-25.7 |
| door -x+y (y wall) 2 | 1.20 | 173 | 178 | 4.9 | 184.5 | 48.1 | 80.2 | 4.7-14.7 |
| door -x+y (x wall) 0 | 1.20 | 1121 | 1121 | 4.9 | 848.8 | 66.4 | 85.3 | 28.0-38.0 |
| door -x+y (x wall) 1 | 1.20 | 682 | 680 | 4.9 | 543.8 | 63.3 | 85.3 | 17.5-27.5 |
| door -x+y (x wall) 2 | 1.20 | 183 | 178 | 4.9 | 187.3 | 50.1 | 80.2 | 4.7-14.7 |
| door -x+y (corner) | 1.20 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| door -x-y (y wall) 0 | 1.20 | 1121 | 1121 | 4.9 | 856.9 | 65.8 | 85.3 | 18.7-28.7 |
| door -x-y (y wall) 1 | 1.20 | 681 | 680 | 4.9 | 543.1 | 63.2 | 90.3 | 17.5-27.5 |
| door -x-y (y wall) 2 | 1.20 | 181 | 178 | 4.9 | 185.4 | 50.1 | 80.2 | 4.7-14.7 |
| door -x-y (x wall) 0 | 1.20 | 1121 | 1121 | 4.9 | 848.6 | 66.4 | 85.3 | 32.7-42.7 |
| door -x-y (x wall) 1 | 1.20 | 679 | 680 | 4.9 | 543.6 | 63.0 | 90.3 | 18.7-28.7 |
| door -x-y (x wall) 2 | 1.20 | 175 | 178 | 4.9 | 184.0 | 48.8 | 80.2 | 4.7-14.7 |
| door -x-y (corner) | 1.20 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| door +x-y (y wall) 0 | 1.20 | 1121 | 1121 | 4.9 | 854.1 | 66.0 | 85.3 | 13.8-23.8 |
| door +x-y (y wall) 1 | 1.20 | 682 | 680 | 4.9 | 545.9 | 63.0 | 85.3 | 18.7-28.7 |
| door +x-y (y wall) 2 | 1.20 | 179 | 178 | 4.9 | 184.4 | 49.8 | 80.2 | 4.7-14.7 |
| door +x-y (x wall) 0 | 1.20 | 1121 | 1121 | 4.9 | 851.1 | 66.2 | 85.3 | 32.2-42.2 |
| door +x-y (x wall) 1 | 1.20 | 678 | 680 | 4.9 | 544.7 | 62.8 | 85.3 | 15.7-25.7 |
| door +x-y (x wall) 2 | 1.20 | 177 | 178 | 4.9 | 179.8 | 50.5 | 80.2 | 4.7-14.7 |
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
| door +x+y (y wall) 0 | door | 1.20 | 1121 | 7.1% | 78.2% |
| door +x+y (y wall) 1 | door | 1.20 | 672 | 4.2% | 46.9% |
| door +x+y (y wall) 2 | door | 1.20 | 177 | 1.1% | 12.3% |
| door +x+y (x wall) 0 | door | 1.20 | 1121 | 7.1% | 78.2% |
| door +x+y (x wall) 1 | door | 1.20 | 688 | 4.3% | 48.0% |
| door +x+y (x wall) 2 | door | 1.20 | 179 | 1.1% | 12.5% |
| door +x+y (corner) | door | 1.20 | 0 | 0.0% | 0.0% |
| door -x+y (y wall) 0 | door | 1.20 | 1121 | 7.1% | 78.2% |
| door -x+y (y wall) 1 | door | 1.20 | 678 | 4.3% | 47.3% |
| door -x+y (y wall) 2 | door | 1.20 | 173 | 1.1% | 12.1% |
| door -x+y (x wall) 0 | door | 1.20 | 1121 | 7.1% | 78.2% |
| door -x+y (x wall) 1 | door | 1.20 | 682 | 4.3% | 47.6% |
| door -x+y (x wall) 2 | door | 1.20 | 183 | 1.2% | 12.8% |
| door -x+y (corner) | door | 1.20 | 0 | 0.0% | 0.0% |
| door -x-y (y wall) 0 | door | 1.20 | 1121 | 7.1% | 78.2% |
| door -x-y (y wall) 1 | door | 1.20 | 681 | 4.3% | 47.5% |
| door -x-y (y wall) 2 | door | 1.20 | 181 | 1.1% | 12.6% |
| door -x-y (x wall) 0 | door | 1.20 | 1121 | 7.1% | 78.2% |
| door -x-y (x wall) 1 | door | 1.20 | 679 | 4.3% | 47.4% |
| door -x-y (x wall) 2 | door | 1.20 | 175 | 1.1% | 12.2% |
| door -x-y (corner) | door | 1.20 | 0 | 0.0% | 0.0% |
| door +x-y (y wall) 0 | door | 1.20 | 1121 | 7.1% | 78.2% |
| door +x-y (y wall) 1 | door | 1.20 | 682 | 4.3% | 47.6% |
| door +x-y (y wall) 2 | door | 1.20 | 179 | 1.1% | 12.5% |
| door +x-y (x wall) 0 | door | 1.20 | 1121 | 7.1% | 78.2% |
| door +x-y (x wall) 1 | door | 1.20 | 678 | 4.3% | 47.3% |
| door +x-y (x wall) 2 | door | 1.20 | 177 | 1.1% | 12.3% |
| door +x-y (corner) | door | 1.20 | 0 | 0.0% | 0.0% |
| **doors (28)** | door | 33.60 | 15832 | 100.0% | |
| **avenues (4)** | avenue | 22.64 | 0 | 0.0% | |

**Unused exit width: 27.4 of 56.2 m (48.8%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 857.2 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 23.6%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight +x+y (y wing) 1 | straight | yes | 672 | 4.2% | 672 | 4.2% |
| straight +x+y (y wing) 2 | straight | yes | 177 | 1.1% | 177 | 1.1% |
| straight +x+y (x wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight +x+y (x wing) 1 | straight | yes | 688 | 4.3% | 688 | 4.3% |
| straight +x+y (x wing) 2 | straight | yes | 179 | 1.1% | 179 | 1.1% |
| corner +x+y | corner | yes | 450 | 2.8% | 0 | 0.0% |
| straight -x+y (y wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight -x+y (y wing) 1 | straight | yes | 678 | 4.3% | 678 | 4.3% |
| straight -x+y (y wing) 2 | straight | yes | 173 | 1.1% | 173 | 1.1% |
| straight -x+y (x wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight -x+y (x wing) 1 | straight | yes | 682 | 4.3% | 682 | 4.3% |
| straight -x+y (x wing) 2 | straight | yes | 183 | 1.2% | 183 | 1.2% |
| corner -x+y | corner | yes | 450 | 2.8% | 0 | 0.0% |
| straight -x-y (y wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight -x-y (y wing) 1 | straight | yes | 681 | 4.3% | 681 | 4.3% |
| straight -x-y (y wing) 2 | straight | yes | 181 | 1.1% | 181 | 1.1% |
| straight -x-y (x wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight -x-y (x wing) 1 | straight | yes | 679 | 4.3% | 679 | 4.3% |
| straight -x-y (x wing) 2 | straight | yes | 175 | 1.1% | 175 | 1.1% |
| corner -x-y | corner | yes | 449 | 2.8% | 0 | 0.0% |
| straight +x-y (y wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight +x-y (y wing) 1 | straight | yes | 682 | 4.3% | 682 | 4.3% |
| straight +x-y (y wing) 2 | straight | yes | 179 | 1.1% | 179 | 1.1% |
| straight +x-y (x wing) 0 | straight | yes | 1121 | 7.1% | 1121 | 7.1% |
| straight +x-y (x wing) 1 | straight | yes | 678 | 4.3% | 678 | 4.3% |
| straight +x-y (x wing) 2 | straight | yes | 177 | 1.1% | 177 | 1.1% |
| corner +x-y | corner | yes | 448 | 2.8% | 0 | 0.0% |
| **straight (24)** | | | 15832 | | 15832 | 100.0% |
| **corner (4)** | | | 1797 | | 0 | 0.0% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| door +x+y (y wall) 0 | 1121 | 4.9 | 847.6 | 0.80 | 1.08 | 40.7% |
| door +x+y (y wall) 1 | 672 | 4.9 | 551.7 | 0.73 | 1.02 | 28.6% |
| door +x+y (y wall) 2 | 177 | 4.9 | 185.2 | 0.59 | 0.96 | 15.8% |
| door +x+y (x wall) 0 | 1121 | 4.9 | 850.6 | 0.79 | 1.02 | 43.0% |
| door +x+y (x wall) 1 | 688 | 4.9 | 555.2 | 0.75 | 1.02 | 35.7% |
| door +x+y (x wall) 2 | 179 | 4.9 | 184.7 | 0.59 | 0.96 | 10.5% |
| door -x+y (y wall) 0 | 1121 | 4.9 | 857.2 | 0.79 | 0.96 | 37.2% |
| door -x+y (y wall) 1 | 678 | 4.9 | 541.7 | 0.76 | 1.02 | 32.7% |
| door -x+y (y wall) 2 | 173 | 4.9 | 184.5 | 0.58 | 0.96 | 15.8% |
| door -x+y (x wall) 0 | 1121 | 4.9 | 848.8 | 0.79 | 1.02 | 48.8% |
| door -x+y (x wall) 1 | 682 | 4.9 | 543.8 | 0.76 | 1.02 | 30.9% |
| door -x+y (x wall) 2 | 183 | 4.9 | 187.3 | 0.60 | 0.96 | 21.1% |
| door -x-y (y wall) 0 | 1121 | 4.9 | 856.9 | 0.79 | 1.02 | 39.5% |
| door -x-y (y wall) 1 | 681 | 4.9 | 543.1 | 0.76 | 1.08 | 34.5% |
| door -x-y (y wall) 2 | 181 | 4.9 | 185.4 | 0.60 | 0.96 | 10.5% |
| door -x-y (x wall) 0 | 1121 | 4.9 | 848.6 | 0.79 | 1.02 | 39.5% |
| door -x-y (x wall) 1 | 679 | 4.9 | 543.6 | 0.75 | 1.08 | 36.4% |
| door -x-y (x wall) 2 | 175 | 4.9 | 184.0 | 0.58 | 0.96 | 15.8% |
| door +x-y (y wall) 0 | 1121 | 4.9 | 854.1 | 0.79 | 1.02 | 37.2% |
| door +x-y (y wall) 1 | 682 | 4.9 | 545.9 | 0.75 | 1.02 | 38.2% |
| door +x-y (y wall) 2 | 179 | 4.9 | 184.4 | 0.60 | 0.96 | 15.8% |
| door +x-y (x wall) 0 | 1121 | 4.9 | 851.1 | 0.79 | 1.02 | 39.5% |
| door +x-y (x wall) 1 | 678 | 4.9 | 544.7 | 0.75 | 1.02 | 30.9% |
| door +x-y (x wall) 2 | 177 | 4.9 | 179.8 | 0.60 | 0.96 | 10.5% |

Mean flow / w J averaged over the doors 0.71, over the avenues nan.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 844.6 | 1.33 | 1.60 | 93% | 82% | 11% | 3.96 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 565 | 672 / 0 / 0 | 0.7 | 548.7 | 1.23 | 1.60 | 75% | 70% | 5% | 3.93 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 68 | 177 / 0 / 0 | 0.7 | 182.3 | 0.97 | 1.50 | 32% | 26% | 5% | 2.66 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 847.6 | 1.32 | 1.60 | 92% | 83% | 9% | 4.00 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 565 | 688 / 0 / 0 | 0.7 | 552.2 | 1.25 | 1.50 | 75% | 70% | 5% | 3.95 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 68 | 179 / 0 / 0 | 0.7 | 181.7 | 0.99 | 1.50 | 32% | 26% | 5% | 2.66 |
| corner +x+y | 1.20 | 85.6 | 450 | 0 / 0 / 450 | 0.7 | 520.0 | 0.87 | 2.31 | 92% | 15% | 77% | 1.50 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 854.2 | 1.31 | 1.60 | 93% | 85% | 8% | 3.97 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 565 | 678 / 0 / 0 | 0.7 | 538.7 | 1.26 | 1.60 | 75% | 69% | 5% | 3.90 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 68 | 173 / 0 / 0 | 0.7 | 181.6 | 0.96 | 1.50 | 32% | 26% | 5% | 2.66 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 845.8 | 1.33 | 1.60 | 93% | 85% | 8% | 4.00 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 565 | 682 / 0 / 0 | 0.7 | 540.8 | 1.26 | 1.60 | 76% | 71% | 5% | 3.99 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 68 | 183 / 0 / 0 | 0.7 | 184.4 | 1.00 | 1.50 | 32% | 26% | 5% | 2.64 |
| corner -x+y | 1.20 | 85.6 | 450 | 0 / 0 / 450 | 0.7 | 508.6 | 0.89 | 2.11 | 92% | 15% | 77% | 1.52 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 853.9 | 1.31 | 1.50 | 92% | 84% | 8% | 4.03 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 566 | 681 / 0 / 0 | 0.7 | 540.1 | 1.26 | 1.60 | 78% | 71% | 7% | 3.91 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 68 | 181 / 0 / 0 | 0.7 | 182.4 | 1.00 | 1.50 | 32% | 26% | 5% | 2.58 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 845.7 | 1.33 | 1.60 | 93% | 86% | 7% | 3.94 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 565 | 679 / 0 / 0 | 0.7 | 540.6 | 1.26 | 1.60 | 76% | 69% | 7% | 3.95 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 68 | 175 / 0 / 0 | 0.7 | 181.0 | 0.97 | 1.50 | 32% | 26% | 5% | 2.65 |
| corner -x-y | 1.20 | 85.6 | 449 | 0 / 0 / 449 | 0.7 | 508.5 | 0.88 | 2.11 | 94% | 18% | 76% | 1.52 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 851.1 | 1.32 | 1.60 | 92% | 84% | 8% | 3.97 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 565 | 682 / 0 / 0 | 0.7 | 542.9 | 1.26 | 1.60 | 76% | 71% | 5% | 3.92 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 68 | 179 / 0 / 0 | 0.7 | 181.4 | 0.99 | 1.50 | 32% | 26% | 5% | 2.64 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 1121 | 1121 / 0 / 0 | 0.7 | 848.1 | 1.32 | 1.50 | 92% | 84% | 8% | 3.97 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 566 | 678 / 0 / 1 | 0.7 | 541.7 | 1.25 | 1.50 | 78% | 71% | 7% | 3.98 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 69 | 177 / 0 / 0 | 0.7 | 176.8 | 1.00 | 1.50 | 39% | 28% | 11% | 2.54 |
| corner +x-y | 1.20 | 85.6 | 448 | 0 / 0 / 449 | 0.7 | 510.7 | 0.88 | 2.11 | 90% | 17% | 73% | 1.55 |

The last agent out (agent 3989, t100 857.2 s): last gangway straight -x+y (y wing) 0, exit -. The gangway that cleared last: straight -x+y (y wing) 0 at 854.2 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.76 | 852.1 / 796.0 / 755.9 | 800.9 / 795.7 / 730.9 | 1218603.8 | 1996914 | 0.130 |
| gangway | 1212 | 1112.9 | 6.76 | 852.1 / 796.0 / 755.9 | 800.9 / 795.7 / 730.9 | 1217689.1 | 1956422 | 0.108 |
| walkway | 276 | 257.4 | 0.12 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 54 | 0.006 |
| avenue | 912 | 858.9 | 0.17 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 13 | 0.142 |
| exit | 32 | 3.2 | 0.00 | 537.3 / 534.3 / 478.9 | 284.6 / 256.6 / 154.6 | 914.7 | 1261 | 1.325 |
| concourse | 1116 | 1043.8 | 1.97 | 775.4 / 0.0 / 0.0 | 143.1 / 0.0 / 0.0 | 0.0 | 39165 | 1.193 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.54 | 795.7 / 792.9 / 755.4 | 795.7 / 792.9 / 752.3 | 1287144.3 | 3313714 | 0.021 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -11.5 | -17.5 | gangway | 0.89 | 6.28 | 778.9 | 772.0 | 730.9 | 3946.6 | 0.014 |
| 2 | 11.5 | -18.5 | gangway | 0.86 | 6.68 | 778.2 | 749.0 | 710.1 | 3937.8 | 0.017 |
| 3 | -10.5 | -16.5 | gangway | 0.96 | 5.86 | 799.0 | 795.7 | 713.3 | 3921.1 | 0.012 |
| 4 | 17.5 | -11.5 | gangway | 0.89 | 6.31 | 780.3 | 770.1 | 730.2 | 3911.2 | 0.014 |
| 5 | 11.5 | -17.5 | gangway | 0.89 | 6.28 | 778.0 | 767.1 | 726.6 | 3911.2 | 0.014 |
| 6 | -11.5 | -18.5 | gangway | 0.86 | 6.66 | 779.6 | 748.4 | 710.8 | 3899.8 | 0.016 |
| 7 | 18.5 | 11.5 | gangway | 0.86 | 6.68 | 769.4 | 741.6 | 712.0 | 3895.9 | 0.017 |
| 8 | 18.5 | -11.5 | gangway | 0.86 | 6.61 | 781.0 | 750.2 | 712.4 | 3863.2 | 0.017 |
| 9 | -11.5 | 17.5 | gangway | 0.89 | 6.28 | 778.9 | 759.8 | 724.1 | 3851.2 | 0.014 |
| 10 | 16.5 | 10.5 | gangway | 0.96 | 5.87 | 793.0 | 789.0 | 703.1 | 3849.9 | 0.012 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -9.5 | -18.5 | seat row | 0.50 | 7.54 | 758.0 | 755.2 | 744.6 | 2680.5 | 0.008 |
| 2 | 18.5 | -9.5 | seat row | 0.50 | 7.51 | 753.1 | 750.2 | 740.6 | 2668.8 | 0.008 |
| 3 | 9.5 | -18.5 | seat row | 0.50 | 7.38 | 757.0 | 753.8 | 742.5 | 2665.9 | 0.008 |
| 4 | 18.5 | 9.5 | seat row | 0.50 | 7.50 | 750.9 | 748.4 | 736.7 | 2657.8 | 0.008 |
| 5 | -18.5 | -9.5 | seat row | 0.50 | 7.41 | 742.0 | 739.9 | 729.9 | 2621.1 | 0.007 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 0; agent-steps of seated agents on another row's clearway: 0.

## Deposit check

Person-seconds deposited: 5314264.1, of them in excluded cells: 3635.983.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 793330 overlapping pair-steps: p99 0.0021, max 0.0084 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0021 max 0.0084; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00765 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 0 (longest 0 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.748553 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.25 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 0 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
