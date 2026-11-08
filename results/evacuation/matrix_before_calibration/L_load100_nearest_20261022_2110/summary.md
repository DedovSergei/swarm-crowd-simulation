# Experiment `L_load100_nearest`

**Task 5.10 stage 4 (AMD 26.10.1): Task 5.8's model (the level spacing on the gangway inclines, --stair-flow off): venue L, 100% load, nearest exit (incline speed)**

Venue L (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (4000 x 4000), cache key a2f3aaf59c2252b7, content hash 022d17b202313d70). 63424 agents on 100% of the 63424 seats (spawnSeatedCrowd, seed 1337), buffer N = 65536, 8239 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **nearest exit, incline speed**.
Capacity: **within design capacity** (the L venue's design capacity 63424, jam capacity 171923: 23822.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T21:10:28, 798.2 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 2695 | 471.4 |
| t90 | 6222 | 1088.3 |
| t100 | 8239 | 1441.1 |

t_p: the step by which ceil(p x 63424) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| -x | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| +y | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| -y | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| door +x+y (y wall) 0 | 2.30 | 2577 | 2577 | 4.9 | 1423.6 | 47.4 | 57.6 | 14.2-24.1 |
| door +x+y (y wall) 1 | 2.30 | 2142 | 2137 | 4.9 | 1201.3 | 46.7 | 60.2 | 16.4-26.4 |
| door +x+y (y wall) 2 | 2.30 | 1603 | 1594 | 4.9 | 905.3 | 46.4 | 57.6 | 28.5-38.5 |
| door +x+y (y wall) 3 | 2.30 | 1047 | 1045 | 4.9 | 601.3 | 45.8 | 54.9 | 24.3-34.3 |
| door +x+y (y wall) 4 | 2.30 | 513 | 513 | 4.9 | 314.0 | 43.3 | 54.9 | 7.7-17.7 |
| door +x+y (x wall) 0 | 2.30 | 2577 | 2577 | 4.9 | 1436.7 | 46.9 | 60.2 | 18.0-28.0 |
| door +x+y (x wall) 1 | 2.30 | 2132 | 2137 | 4.9 | 1204.4 | 46.4 | 54.9 | 13.3-23.3 |
| door +x+y (x wall) 2 | 2.30 | 1585 | 1594 | 4.9 | 902.2 | 46.1 | 57.6 | 19.6-29.6 |
| door +x+y (x wall) 3 | 2.30 | 1043 | 1045 | 4.9 | 602.7 | 45.5 | 54.9 | 13.3-23.3 |
| door +x+y (x wall) 4 | 2.30 | 513 | 513 | 5.1 | 312.4 | 43.5 | 57.6 | 30.3-40.2 |
| door +x+y (corner) | 2.30 | 124 | 124 | 6.3 | 75.6 | 46.6 | 52.3 | 23.6-33.6 |
| door -x+y (y wall) 0 | 2.30 | 2577 | 2577 | 4.9 | 1441.1 | 46.8 | 60.2 | 11.5-21.5 |
| door -x+y (y wall) 1 | 2.30 | 2129 | 2137 | 4.9 | 1204.8 | 46.3 | 60.2 | 26.8-36.7 |
| door -x+y (y wall) 2 | 2.30 | 1587 | 1594 | 4.9 | 912.3 | 45.6 | 60.2 | 11.5-21.5 |
| door -x+y (y wall) 3 | 2.30 | 1044 | 1045 | 4.9 | 602.2 | 45.6 | 60.2 | 11.5-21.5 |
| door -x+y (y wall) 4 | 2.30 | 506 | 513 | 5.1 | 311.9 | 43.0 | 54.9 | 7.5-17.5 |
| door -x+y (x wall) 0 | 2.30 | 2577 | 2577 | 4.9 | 1430.0 | 47.2 | 57.6 | 14.2-24.1 |
| door -x+y (x wall) 1 | 2.30 | 2145 | 2137 | 4.9 | 1204.6 | 46.6 | 57.6 | 368.4-378.3 |
| door -x+y (x wall) 2 | 2.30 | 1601 | 1594 | 4.9 | 915.1 | 45.9 | 57.6 | 22.2-32.2 |
| door -x+y (x wall) 3 | 2.30 | 1046 | 1045 | 4.9 | 599.8 | 45.9 | 57.6 | 273.6-283.5 |
| door -x+y (x wall) 4 | 2.30 | 520 | 513 | 4.9 | 312.4 | 44.1 | 57.6 | 32.7-42.7 |
| door -x+y (corner) | 2.30 | 124 | 124 | 6.3 | 74.2 | 47.5 | 52.3 | 28.9-38.8 |
| door -x-y (y wall) 0 | 2.30 | 2577 | 2577 | 4.9 | 1427.4 | 47.3 | 57.6 | 26.8-36.7 |
| door -x-y (y wall) 1 | 2.30 | 2139 | 2137 | 4.9 | 1211.2 | 46.2 | 60.2 | 16.6-26.6 |
| door -x-y (y wall) 2 | 2.30 | 1597 | 1594 | 4.9 | 911.6 | 45.9 | 54.9 | 16.4-26.4 |
| door -x-y (y wall) 3 | 2.30 | 1055 | 1045 | 4.9 | 592.9 | 46.8 | 60.2 | 24.1-34.1 |
| door -x-y (y wall) 4 | 2.30 | 518 | 513 | 4.9 | 318.0 | 43.1 | 57.6 | 8.0-18.0 |
| door -x-y (x wall) 0 | 2.30 | 2577 | 2577 | 4.9 | 1437.2 | 46.9 | 60.2 | 11.5-21.5 |
| door -x-y (x wall) 1 | 2.30 | 2135 | 2137 | 4.9 | 1213.0 | 46.1 | 60.2 | 11.5-21.5 |
| door -x-y (x wall) 2 | 2.30 | 1591 | 1594 | 4.9 | 908.5 | 45.9 | 60.2 | 11.7-21.7 |
| door -x-y (x wall) 3 | 2.30 | 1035 | 1045 | 4.9 | 596.3 | 45.6 | 60.2 | 11.5-21.5 |
| door -x-y (x wall) 4 | 2.30 | 508 | 513 | 5.1 | 314.5 | 42.8 | 57.6 | 18.9-28.9 |
| door -x-y (corner) | 2.30 | 124 | 124 | 6.3 | 74.5 | 47.3 | 52.3 | 29.9-39.9 |
| door +x-y (y wall) 0 | 2.30 | 2577 | 2577 | 4.9 | 1439.1 | 46.9 | 60.2 | 11.5-21.5 |
| door +x-y (y wall) 1 | 2.30 | 2144 | 2137 | 4.9 | 1207.4 | 46.5 | 60.2 | 11.5-21.5 |
| door +x-y (y wall) 2 | 2.30 | 1595 | 1594 | 4.9 | 917.9 | 45.6 | 60.2 | 11.7-21.7 |
| door +x-y (y wall) 3 | 2.30 | 1047 | 1045 | 4.9 | 608.7 | 45.2 | 60.2 | 11.5-21.5 |
| door +x-y (y wall) 4 | 2.30 | 517 | 513 | 5.1 | 311.0 | 44.1 | 57.6 | 30.1-40.1 |
| door +x-y (x wall) 0 | 2.30 | 2577 | 2577 | 4.9 | 1437.0 | 46.9 | 54.9 | 10.8-20.8 |
| door +x-y (x wall) 1 | 2.30 | 2130 | 2137 | 4.9 | 1202.8 | 46.4 | 54.9 | 10.8-20.8 |
| door +x-y (x wall) 2 | 2.30 | 1593 | 1594 | 4.9 | 916.9 | 45.6 | 54.9 | 10.8-20.8 |
| door +x-y (x wall) 3 | 2.30 | 1043 | 1045 | 4.9 | 608.5 | 45.1 | 57.6 | 31.5-41.5 |
| door +x-y (x wall) 4 | 2.30 | 509 | 513 | 5.1 | 309.2 | 43.6 | 57.6 | 27.8-37.8 |
| door +x-y (corner) | 2.30 | 124 | 124 | 6.5 | 74.2 | 47.7 | 52.3 | 21.7-31.7 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (2.30 m; a corner door's: the gap between its wall ends, 2.30 m); agents are removed past the outer wall's outer face (92.71 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 0 | 0.0% | 0.0% |
| -x | avenue | 5.66 | 0 | 0.0% | 0.0% |
| +y | avenue | 5.66 | 0 | 0.0% | 0.0% |
| -y | avenue | 5.66 | 0 | 0.0% | 0.0% |
| door +x+y (y wall) 0 | door | 2.30 | 2577 | 4.1% | 55.8% |
| door +x+y (y wall) 1 | door | 2.30 | 2142 | 3.4% | 46.4% |
| door +x+y (y wall) 2 | door | 2.30 | 1603 | 2.5% | 34.7% |
| door +x+y (y wall) 3 | door | 2.30 | 1047 | 1.7% | 22.7% |
| door +x+y (y wall) 4 | door | 2.30 | 513 | 0.8% | 11.1% |
| door +x+y (x wall) 0 | door | 2.30 | 2577 | 4.1% | 55.8% |
| door +x+y (x wall) 1 | door | 2.30 | 2132 | 3.4% | 46.2% |
| door +x+y (x wall) 2 | door | 2.30 | 1585 | 2.5% | 34.3% |
| door +x+y (x wall) 3 | door | 2.30 | 1043 | 1.6% | 22.6% |
| door +x+y (x wall) 4 | door | 2.30 | 513 | 0.8% | 11.1% |
| door +x+y (corner) | door | 2.30 | 124 | 0.2% | 2.7% |
| door -x+y (y wall) 0 | door | 2.30 | 2577 | 4.1% | 55.8% |
| door -x+y (y wall) 1 | door | 2.30 | 2129 | 3.4% | 46.1% |
| door -x+y (y wall) 2 | door | 2.30 | 1587 | 2.5% | 34.4% |
| door -x+y (y wall) 3 | door | 2.30 | 1044 | 1.6% | 22.6% |
| door -x+y (y wall) 4 | door | 2.30 | 506 | 0.8% | 11.0% |
| door -x+y (x wall) 0 | door | 2.30 | 2577 | 4.1% | 55.8% |
| door -x+y (x wall) 1 | door | 2.30 | 2145 | 3.4% | 46.4% |
| door -x+y (x wall) 2 | door | 2.30 | 1601 | 2.5% | 34.7% |
| door -x+y (x wall) 3 | door | 2.30 | 1046 | 1.6% | 22.6% |
| door -x+y (x wall) 4 | door | 2.30 | 520 | 0.8% | 11.3% |
| door -x+y (corner) | door | 2.30 | 124 | 0.2% | 2.7% |
| door -x-y (y wall) 0 | door | 2.30 | 2577 | 4.1% | 55.8% |
| door -x-y (y wall) 1 | door | 2.30 | 2139 | 3.4% | 46.3% |
| door -x-y (y wall) 2 | door | 2.30 | 1597 | 2.5% | 34.6% |
| door -x-y (y wall) 3 | door | 2.30 | 1055 | 1.7% | 22.8% |
| door -x-y (y wall) 4 | door | 2.30 | 518 | 0.8% | 11.2% |
| door -x-y (x wall) 0 | door | 2.30 | 2577 | 4.1% | 55.8% |
| door -x-y (x wall) 1 | door | 2.30 | 2135 | 3.4% | 46.2% |
| door -x-y (x wall) 2 | door | 2.30 | 1591 | 2.5% | 34.5% |
| door -x-y (x wall) 3 | door | 2.30 | 1035 | 1.6% | 22.4% |
| door -x-y (x wall) 4 | door | 2.30 | 508 | 0.8% | 11.0% |
| door -x-y (corner) | door | 2.30 | 124 | 0.2% | 2.7% |
| door +x-y (y wall) 0 | door | 2.30 | 2577 | 4.1% | 55.8% |
| door +x-y (y wall) 1 | door | 2.30 | 2144 | 3.4% | 46.4% |
| door +x-y (y wall) 2 | door | 2.30 | 1595 | 2.5% | 34.5% |
| door +x-y (y wall) 3 | door | 2.30 | 1047 | 1.7% | 22.7% |
| door +x-y (y wall) 4 | door | 2.30 | 517 | 0.8% | 11.2% |
| door +x-y (x wall) 0 | door | 2.30 | 2577 | 4.1% | 55.8% |
| door +x-y (x wall) 1 | door | 2.30 | 2130 | 3.4% | 46.1% |
| door +x-y (x wall) 2 | door | 2.30 | 1593 | 2.5% | 34.5% |
| door +x-y (x wall) 3 | door | 2.30 | 1043 | 1.6% | 22.6% |
| door +x-y (x wall) 4 | door | 2.30 | 509 | 0.8% | 11.0% |
| door +x-y (corner) | door | 2.30 | 124 | 0.2% | 2.7% |
| **doors (44)** | door | 101.20 | 63424 | 100.0% | |
| **avenues (4)** | avenue | 22.64 | 0 | 0.0% | |

**Unused exit width: 22.6 of 123.8 m (18.3%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 1441.1 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 25.5%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 2577 | 4.1% | 2577 | 4.1% |
| straight +x+y (y wing) 1 | straight | yes | 2142 | 3.4% | 2142 | 3.4% |
| straight +x+y (y wing) 2 | straight | yes | 1603 | 2.5% | 1603 | 2.5% |
| straight +x+y (y wing) 3 | straight | yes | 1047 | 1.7% | 1047 | 1.7% |
| straight +x+y (y wing) 4 | straight | yes | 513 | 0.8% | 513 | 0.8% |
| straight +x+y (x wing) 0 | straight | yes | 2577 | 4.1% | 2577 | 4.1% |
| straight +x+y (x wing) 1 | straight | yes | 2132 | 3.4% | 2132 | 3.4% |
| straight +x+y (x wing) 2 | straight | yes | 1585 | 2.5% | 1585 | 2.5% |
| straight +x+y (x wing) 3 | straight | yes | 1043 | 1.6% | 1043 | 1.6% |
| straight +x+y (x wing) 4 | straight | yes | 513 | 0.8% | 513 | 0.8% |
| corner +x+y | corner | yes | 1019 | 1.6% | 124 | 0.2% |
| straight -x+y (y wing) 0 | straight | yes | 2577 | 4.1% | 2577 | 4.1% |
| straight -x+y (y wing) 1 | straight | yes | 2129 | 3.4% | 2129 | 3.4% |
| straight -x+y (y wing) 2 | straight | yes | 1587 | 2.5% | 1587 | 2.5% |
| straight -x+y (y wing) 3 | straight | yes | 1044 | 1.6% | 1044 | 1.6% |
| straight -x+y (y wing) 4 | straight | yes | 506 | 0.8% | 506 | 0.8% |
| straight -x+y (x wing) 0 | straight | yes | 2577 | 4.1% | 2577 | 4.1% |
| straight -x+y (x wing) 1 | straight | yes | 2145 | 3.4% | 2145 | 3.4% |
| straight -x+y (x wing) 2 | straight | yes | 1601 | 2.5% | 1601 | 2.5% |
| straight -x+y (x wing) 3 | straight | yes | 1046 | 1.6% | 1046 | 1.6% |
| straight -x+y (x wing) 4 | straight | yes | 520 | 0.8% | 520 | 0.8% |
| corner -x+y | corner | yes | 1020 | 1.6% | 124 | 0.2% |
| straight -x-y (y wing) 0 | straight | yes | 2577 | 4.1% | 2577 | 4.1% |
| straight -x-y (y wing) 1 | straight | yes | 2139 | 3.4% | 2139 | 3.4% |
| straight -x-y (y wing) 2 | straight | yes | 1597 | 2.5% | 1597 | 2.5% |
| straight -x-y (y wing) 3 | straight | yes | 1055 | 1.7% | 1055 | 1.7% |
| straight -x-y (y wing) 4 | straight | yes | 518 | 0.8% | 518 | 0.8% |
| straight -x-y (x wing) 0 | straight | yes | 2577 | 4.1% | 2577 | 4.1% |
| straight -x-y (x wing) 1 | straight | yes | 2135 | 3.4% | 2135 | 3.4% |
| straight -x-y (x wing) 2 | straight | yes | 1591 | 2.5% | 1591 | 2.5% |
| straight -x-y (x wing) 3 | straight | yes | 1035 | 1.6% | 1035 | 1.6% |
| straight -x-y (x wing) 4 | straight | yes | 508 | 0.8% | 508 | 0.8% |
| corner -x-y | corner | yes | 1020 | 1.6% | 124 | 0.2% |
| straight +x-y (y wing) 0 | straight | yes | 2577 | 4.1% | 2577 | 4.1% |
| straight +x-y (y wing) 1 | straight | yes | 2144 | 3.4% | 2144 | 3.4% |
| straight +x-y (y wing) 2 | straight | yes | 1595 | 2.5% | 1595 | 2.5% |
| straight +x-y (y wing) 3 | straight | yes | 1047 | 1.7% | 1047 | 1.7% |
| straight +x-y (y wing) 4 | straight | yes | 517 | 0.8% | 517 | 0.8% |
| straight +x-y (x wing) 0 | straight | yes | 2577 | 4.1% | 2577 | 4.1% |
| straight +x-y (x wing) 1 | straight | yes | 2130 | 3.4% | 2130 | 3.4% |
| straight +x-y (x wing) 2 | straight | yes | 1593 | 2.5% | 1593 | 2.5% |
| straight +x-y (x wing) 3 | straight | yes | 1043 | 1.6% | 1043 | 1.6% |
| straight +x-y (x wing) 4 | straight | yes | 509 | 0.8% | 509 | 0.8% |
| corner +x-y | corner | yes | 1020 | 1.6% | 124 | 0.2% |
| **straight (40)** | | | 62928 | | 62928 | 99.2% |
| **corner (4)** | | | 4079 | | 496 | 0.8% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| door +x+y (y wall) 0 | 2577 | 4.9 | 1423.6 | 0.57 | 0.69 | 0.0% |
| door +x+y (y wall) 1 | 2142 | 4.9 | 1201.3 | 0.56 | 0.72 | 0.0% |
| door +x+y (y wall) 2 | 1603 | 4.9 | 905.3 | 0.56 | 0.69 | 0.0% |
| door +x+y (y wall) 3 | 1047 | 4.9 | 601.3 | 0.55 | 0.66 | 0.0% |
| door +x+y (y wall) 4 | 513 | 4.9 | 314.0 | 0.52 | 0.66 | 0.0% |
| door +x+y (x wall) 0 | 2577 | 4.9 | 1436.7 | 0.56 | 0.72 | 0.0% |
| door +x+y (x wall) 1 | 2132 | 4.9 | 1204.4 | 0.55 | 0.66 | 0.0% |
| door +x+y (x wall) 2 | 1585 | 4.9 | 902.2 | 0.55 | 0.69 | 0.0% |
| door +x+y (x wall) 3 | 1043 | 4.9 | 602.7 | 0.54 | 0.66 | 0.0% |
| door +x+y (x wall) 4 | 513 | 5.1 | 312.4 | 0.52 | 0.69 | 0.0% |
| door +x+y (corner) | 124 | 6.3 | 75.6 | 0.56 | 0.63 | 0.0% |
| door -x+y (y wall) 0 | 2577 | 4.9 | 1441.1 | 0.56 | 0.72 | 0.0% |
| door -x+y (y wall) 1 | 2129 | 4.9 | 1204.8 | 0.55 | 0.72 | 0.0% |
| door -x+y (y wall) 2 | 1587 | 4.9 | 912.3 | 0.55 | 0.72 | 0.0% |
| door -x+y (y wall) 3 | 1044 | 4.9 | 602.2 | 0.55 | 0.72 | 0.0% |
| door -x+y (y wall) 4 | 506 | 5.1 | 311.9 | 0.51 | 0.66 | 0.0% |
| door -x+y (x wall) 0 | 2577 | 4.9 | 1430.0 | 0.56 | 0.69 | 0.0% |
| door -x+y (x wall) 1 | 2145 | 4.9 | 1204.6 | 0.56 | 0.69 | 0.0% |
| door -x+y (x wall) 2 | 1601 | 4.9 | 915.1 | 0.55 | 0.69 | 0.0% |
| door -x+y (x wall) 3 | 1046 | 4.9 | 599.8 | 0.55 | 0.69 | 0.0% |
| door -x+y (x wall) 4 | 520 | 4.9 | 312.4 | 0.53 | 0.69 | 0.0% |
| door -x+y (corner) | 124 | 6.3 | 74.2 | 0.57 | 0.63 | 0.0% |
| door -x-y (y wall) 0 | 2577 | 4.9 | 1427.4 | 0.57 | 0.69 | 0.0% |
| door -x-y (y wall) 1 | 2139 | 4.9 | 1211.2 | 0.55 | 0.72 | 0.0% |
| door -x-y (y wall) 2 | 1597 | 4.9 | 911.6 | 0.55 | 0.66 | 0.0% |
| door -x-y (y wall) 3 | 1055 | 4.9 | 592.9 | 0.56 | 0.72 | 0.0% |
| door -x-y (y wall) 4 | 518 | 4.9 | 318.0 | 0.52 | 0.69 | 0.0% |
| door -x-y (x wall) 0 | 2577 | 4.9 | 1437.2 | 0.56 | 0.72 | 0.0% |
| door -x-y (x wall) 1 | 2135 | 4.9 | 1213.0 | 0.55 | 0.72 | 0.0% |
| door -x-y (x wall) 2 | 1591 | 4.9 | 908.5 | 0.55 | 0.72 | 0.0% |
| door -x-y (x wall) 3 | 1035 | 4.9 | 596.3 | 0.55 | 0.72 | 0.0% |
| door -x-y (x wall) 4 | 508 | 5.1 | 314.5 | 0.51 | 0.69 | 0.0% |
| door -x-y (corner) | 124 | 6.3 | 74.5 | 0.57 | 0.63 | 0.0% |
| door +x-y (y wall) 0 | 2577 | 4.9 | 1439.1 | 0.56 | 0.72 | 0.0% |
| door +x-y (y wall) 1 | 2144 | 4.9 | 1207.4 | 0.56 | 0.72 | 0.0% |
| door +x-y (y wall) 2 | 1595 | 4.9 | 917.9 | 0.55 | 0.72 | 0.0% |
| door +x-y (y wall) 3 | 1047 | 4.9 | 608.7 | 0.54 | 0.72 | 0.0% |
| door +x-y (y wall) 4 | 517 | 5.1 | 311.0 | 0.53 | 0.69 | 0.0% |
| door +x-y (x wall) 0 | 2577 | 4.9 | 1437.0 | 0.56 | 0.66 | 0.0% |
| door +x-y (x wall) 1 | 2130 | 4.9 | 1202.8 | 0.55 | 0.66 | 0.0% |
| door +x-y (x wall) 2 | 1593 | 4.9 | 916.9 | 0.54 | 0.66 | 0.0% |
| door +x-y (x wall) 3 | 1043 | 4.9 | 608.5 | 0.54 | 0.69 | 0.0% |
| door +x-y (x wall) 4 | 509 | 5.1 | 309.2 | 0.52 | 0.69 | 0.0% |
| door +x-y (corner) | 124 | 6.5 | 74.2 | 0.57 | 0.63 | 0.0% |

Mean flow / w J averaged over the doors 0.55, over the avenues nan.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 103.1 | 2577 | 2577 / 0 / 0 | 0.7 | 1420.6 | 1.81 | 2.11 | 90% | 90% | 0% | 4.36 |
| straight +x+y (y wing) 1 | 1.20 | 81.5 | 2023 | 2142 / 0 / 0 | 0.7 | 1198.3 | 1.79 | 2.11 | 87% | 87% | 0% | 4.33 |
| straight +x+y (y wing) 2 | 1.20 | 61.0 | 1485 | 1603 / 0 / 1 | 0.7 | 902.3 | 1.78 | 2.11 | 85% | 85% | 0% | 4.39 |
| straight +x+y (y wing) 3 | 1.20 | 39.4 | 930 | 1047 / 0 / 0 | 0.7 | 598.4 | 1.75 | 2.01 | 80% | 80% | 0% | 4.27 |
| straight +x+y (y wing) 4 | 1.20 | 18.8 | 404 | 513 / 0 / 0 | 0.7 | 311.0 | 1.65 | 2.01 | 72% | 72% | 0% | 4.29 |
| straight +x+y (x wing) 0 | 1.20 | 103.1 | 2577 | 2577 / 0 / 0 | 0.7 | 1433.7 | 1.80 | 2.21 | 90% | 90% | 0% | 4.12 |
| straight +x+y (x wing) 1 | 1.20 | 81.5 | 2022 | 2132 / 0 / 0 | 0.7 | 1201.4 | 1.78 | 2.11 | 87% | 87% | 0% | 4.10 |
| straight +x+y (x wing) 2 | 1.20 | 61.0 | 1485 | 1585 / 0 / 0 | 0.7 | 899.2 | 1.76 | 2.01 | 85% | 85% | 0% | 4.26 |
| straight +x+y (x wing) 3 | 1.20 | 39.4 | 930 | 1043 / 0 / 0 | 0.7 | 599.8 | 1.74 | 2.01 | 80% | 80% | 0% | 4.19 |
| straight +x+y (x wing) 4 | 1.20 | 18.8 | 404 | 513 / 0 / 0 | 0.7 | 309.4 | 1.66 | 2.11 | 69% | 69% | 0% | 4.15 |
| corner +x+y | 1.20 | 186.0 | 1019 | 124 / 0 / 896 | 0.7 | 1097.5 | 0.93 | 4.01 | 96% | 21% | 76% | 1.45 |
| straight -x+y (y wing) 0 | 1.20 | 103.1 | 2577 | 2577 / 0 / 0 | 0.7 | 1438.1 | 1.79 | 2.21 | 90% | 90% | 0% | 4.20 |
| straight -x+y (y wing) 1 | 1.20 | 81.5 | 2022 | 2129 / 0 / 1 | 0.7 | 1201.8 | 1.77 | 2.11 | 87% | 87% | 0% | 4.16 |
| straight -x+y (y wing) 2 | 1.20 | 61.0 | 1485 | 1587 / 0 / 0 | 0.7 | 909.3 | 1.75 | 2.21 | 85% | 85% | 0% | 4.13 |
| straight -x+y (y wing) 3 | 1.20 | 39.4 | 930 | 1044 / 0 / 0 | 0.7 | 599.2 | 1.74 | 2.21 | 82% | 82% | 0% | 4.11 |
| straight -x+y (y wing) 4 | 1.20 | 18.8 | 404 | 506 / 0 / 0 | 0.7 | 308.9 | 1.64 | 2.11 | 74% | 74% | 0% | 4.10 |
| straight -x+y (x wing) 0 | 1.20 | 103.1 | 2577 | 2577 / 0 / 0 | 0.7 | 1427.1 | 1.81 | 2.01 | 90% | 90% | 0% | 4.31 |
| straight -x+y (x wing) 1 | 1.20 | 81.5 | 2022 | 2145 / 0 / 0 | 0.7 | 1201.6 | 1.79 | 2.11 | 87% | 87% | 0% | 4.37 |
| straight -x+y (x wing) 2 | 1.20 | 61.0 | 1485 | 1601 / 0 / 1 | 0.7 | 912.1 | 1.76 | 2.11 | 86% | 86% | 0% | 4.35 |
| straight -x+y (x wing) 3 | 1.20 | 39.4 | 930 | 1046 / 0 / 0 | 0.7 | 596.8 | 1.75 | 2.11 | 82% | 82% | 0% | 4.30 |
| straight -x+y (x wing) 4 | 1.20 | 18.8 | 404 | 520 / 0 / 1 | 0.7 | 309.4 | 1.69 | 2.21 | 69% | 69% | 0% | 4.31 |
| corner -x+y | 1.20 | 186.0 | 1020 | 124 / 0 / 899 | 0.7 | 1097.9 | 0.93 | 4.01 | 97% | 21% | 77% | 1.43 |
| straight -x-y (y wing) 0 | 1.20 | 103.1 | 2577 | 2577 / 0 / 0 | 0.7 | 1424.4 | 1.81 | 2.01 | 90% | 90% | 0% | 4.30 |
| straight -x-y (y wing) 1 | 1.20 | 81.5 | 2022 | 2139 / 0 / 0 | 0.7 | 1208.3 | 1.77 | 2.01 | 86% | 86% | 0% | 4.37 |
| straight -x-y (y wing) 2 | 1.20 | 61.0 | 1485 | 1597 / 0 / 0 | 0.7 | 908.6 | 1.76 | 2.01 | 84% | 84% | 0% | 4.30 |
| straight -x-y (y wing) 3 | 1.20 | 39.4 | 930 | 1055 / 0 / 0 | 0.7 | 590.0 | 1.79 | 2.11 | 85% | 85% | 0% | 4.33 |
| straight -x-y (y wing) 4 | 1.20 | 18.8 | 404 | 518 / 0 / 0 | 0.7 | 315.0 | 1.65 | 2.11 | 69% | 69% | 0% | 4.34 |
| straight -x-y (x wing) 0 | 1.20 | 103.1 | 2577 | 2577 / 0 / 0 | 0.7 | 1434.2 | 1.80 | 2.21 | 90% | 90% | 0% | 4.21 |
| straight -x-y (x wing) 1 | 1.20 | 81.5 | 2022 | 2135 / 0 / 0 | 0.7 | 1210.0 | 1.77 | 2.21 | 86% | 86% | 0% | 4.20 |
| straight -x-y (x wing) 2 | 1.20 | 61.0 | 1485 | 1591 / 0 / 0 | 0.7 | 905.5 | 1.76 | 2.21 | 86% | 86% | 0% | 4.15 |
| straight -x-y (x wing) 3 | 1.20 | 39.4 | 930 | 1035 / 0 / 0 | 0.7 | 593.3 | 1.75 | 2.21 | 82% | 82% | 0% | 4.17 |
| straight -x-y (x wing) 4 | 1.20 | 18.8 | 404 | 508 / 0 / 1 | 0.7 | 311.5 | 1.64 | 2.01 | 72% | 72% | 0% | 4.07 |
| corner -x-y | 1.20 | 186.0 | 1020 | 124 / 0 / 897 | 0.7 | 1106.1 | 0.92 | 4.21 | 97% | 20% | 77% | 1.41 |
| straight +x-y (y wing) 0 | 1.20 | 103.1 | 2577 | 2577 / 0 / 0 | 0.7 | 1436.2 | 1.80 | 2.21 | 90% | 90% | 0% | 4.22 |
| straight +x-y (y wing) 1 | 1.20 | 81.5 | 2022 | 2144 / 0 / 1 | 0.7 | 1204.4 | 1.78 | 2.21 | 88% | 88% | 0% | 4.20 |
| straight +x-y (y wing) 2 | 1.20 | 61.0 | 1485 | 1595 / 0 / 0 | 0.7 | 914.9 | 1.74 | 2.21 | 85% | 85% | 0% | 4.13 |
| straight +x-y (y wing) 3 | 1.20 | 39.4 | 930 | 1047 / 0 / 0 | 0.7 | 605.7 | 1.73 | 2.21 | 80% | 80% | 0% | 4.14 |
| straight +x-y (y wing) 4 | 1.20 | 18.8 | 404 | 517 / 0 / 0 | 0.7 | 308.0 | 1.68 | 2.01 | 74% | 74% | 0% | 4.09 |
| straight +x-y (x wing) 0 | 1.20 | 103.1 | 2577 | 2577 / 0 / 0 | 0.7 | 1434.1 | 1.80 | 2.01 | 90% | 90% | 0% | 4.10 |
| straight +x-y (x wing) 1 | 1.20 | 81.5 | 2022 | 2130 / 0 / 0 | 0.7 | 1199.9 | 1.78 | 2.01 | 88% | 88% | 0% | 4.15 |
| straight +x-y (x wing) 2 | 1.20 | 61.0 | 1485 | 1593 / 0 / 0 | 0.7 | 913.9 | 1.74 | 2.01 | 85% | 85% | 0% | 4.22 |
| straight +x-y (x wing) 3 | 1.20 | 39.4 | 930 | 1043 / 0 / 1 | 0.7 | 605.5 | 1.73 | 2.11 | 82% | 82% | 0% | 4.20 |
| straight +x-y (x wing) 4 | 1.20 | 18.8 | 404 | 509 / 0 / 0 | 0.7 | 306.3 | 1.66 | 2.11 | 74% | 74% | 0% | 4.13 |
| corner +x-y | 1.20 | 186.0 | 1020 | 124 / 0 / 898 | 0.7 | 1100.5 | 0.93 | 4.21 | 96% | 22% | 75% | 1.50 |

The last agent out (agent 15887, t100 1441.1 s): last gangway straight -x+y (y wing) 0, exit -. The gangway that cleared last: straight -x+y (y wing) 0 at 1438.1 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 8804 | 7800.4 | 6.83 | 1438.3 / 1422.0 / 1271.0 | 1426.4 / 1307.4 / 1252.2 | 7357393.1 | 11748518 | 0.158 |
| gangway | 3792 | 3512.9 | 6.83 | 1436.5 / 1422.0 / 1271.0 | 1426.4 / 1307.4 / 1252.2 | 7357393.1 | 11513544 | 0.140 |
| walkway | 276 | 257.4 | 0.09 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 40 | 0.006 |
| avenue | 1920 | 1801.4 | 0.17 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 28 | 0.142 |
| exit | 4 | 2.0 | 0.00 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 0 | - |
| concourse | 2812 | 2226.8 | 2.79 | 1436.5 / 48.3 / 0.0 | 1357.6 / 20.8 / 0.0 | 0.0 | 234907 | 1.038 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 25392 | 16030.4 | 7.88 | 1306.6 / 1304.3 / 1292.7 | 1306.6 / 1304.3 / 1290.1 | 9154340.0 | 21887849 | 0.018 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 208 x 208 from (-104, -104) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -10.5 | 17.5 | gangway | 0.95 | 5.92 | 1313.7 | 1306.4 | 1251.5 | 6798.4 | 0.010 |
| 2 | 10.5 | 16.5 | gangway | 0.96 | 5.91 | 1294.5 | 1289.4 | 1218.4 | 6794.9 | 0.008 |
| 3 | -10.5 | -18.5 | gangway | 0.94 | 6.18 | 1301.8 | 1282.8 | 1211.9 | 6758.8 | 0.013 |
| 4 | -11.5 | -16.5 | gangway | 0.92 | 5.98 | 1283.1 | 1278.6 | 1230.3 | 6673.8 | 0.006 |
| 5 | 10.5 | 15.5 | gangway | 0.96 | 5.96 | 1288.9 | 1284.0 | 1188.1 | 6656.9 | 0.006 |
| 6 | -11.5 | 17.5 | gangway | 0.89 | 6.20 | 1301.8 | 1296.6 | 1252.2 | 6646.2 | 0.010 |
| 7 | -10.5 | -16.5 | gangway | 0.96 | 5.82 | 1298.3 | 1289.9 | 1226.8 | 6641.3 | 0.009 |
| 8 | -11.5 | -17.5 | gangway | 0.89 | 6.31 | 1287.0 | 1279.3 | 1236.8 | 6618.7 | 0.007 |
| 9 | -16.5 | 10.5 | gangway | 0.96 | 5.80 | 1301.1 | 1296.9 | 1212.5 | 6603.0 | 0.009 |
| 10 | -11.5 | 18.5 | gangway | 0.86 | 6.75 | 1303.6 | 1291.9 | 1239.9 | 6589.3 | 0.010 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -9.5 | -18.5 | seat row | 0.50 | 7.55 | 1266.5 | 1264.2 | 1256.4 | 4617.6 | 0.005 |
| 2 | -18.5 | 9.5 | seat row | 0.50 | 7.50 | 1278.7 | 1276.5 | 1262.7 | 4603.1 | 0.005 |
| 3 | 9.5 | 18.5 | seat row | 0.50 | 7.51 | 1270.2 | 1266.8 | 1252.5 | 4581.3 | 0.005 |
| 4 | 9.5 | -14.5 | seat row | 0.50 | 7.35 | 1300.3 | 1290.1 | 1279.1 | 4527.1 | 0.004 |
| 5 | -9.5 | 18.5 | seat row | 0.50 | 7.32 | 1285.4 | 1281.7 | 1271.2 | 4515.5 | 0.005 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 0; agent-steps of seated agents on another row's clearway: 0.

## Deposit check

Person-seconds deposited: 33642470.2, of them in excluded cells: 6102.661.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 4888817 overlapping pair-steps: p99 0.0029, max 0.0329 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0029 max 0.0329; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00749 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 1 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.748626 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.40 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 0 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
