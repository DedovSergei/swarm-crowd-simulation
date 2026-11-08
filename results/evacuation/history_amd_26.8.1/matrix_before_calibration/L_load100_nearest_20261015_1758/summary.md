# Experiment `L_load100_nearest`

**Task 5.8 stage 2: venue L, 100% load, nearest exit (incline speed): the uninformed-crowd bound**

Venue L (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (4000 x 4000), cache key a2f3aaf59c2252b7, content hash 022d17b202313d70). 63424 agents on 100% of the 63424 seats (spawnSeatedCrowd, seed 1337), buffer N = 65536, 8242 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **nearest exit, incline speed**.
Capacity: **within design capacity** (the L venue's design capacity 63424, jam capacity 171923: 23822.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `cd8e0bbf3411846ca7aa6719887d122a142a7ca1`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-15T17:58:54, 647.9 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 2701 | 472.4 |
| t90 | 6227 | 1089.1 |
| t100 | 8242 | 1441.6 |

t_p: the step by which ceil(p x 63424) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| -x | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| +y | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| -y | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| door +x+y (y wall) 0 | 2.30 | 2577 | 2577 | 4.9 | 1426.7 | 47.3 | 60.2 | 21.5-31.5 |
| door +x+y (y wall) 1 | 2.30 | 2135 | 2137 | 4.9 | 1204.8 | 46.4 | 60.2 | 16.4-26.4 |
| door +x+y (y wall) 2 | 2.30 | 1599 | 1594 | 4.9 | 910.7 | 46.0 | 57.6 | 28.5-38.5 |
| door +x+y (y wall) 3 | 2.30 | 1045 | 1045 | 4.9 | 603.3 | 45.5 | 60.2 | 24.3-34.3 |
| door +x+y (y wall) 4 | 2.30 | 511 | 513 | 4.9 | 315.5 | 42.9 | 57.6 | 22.6-32.5 |
| door +x+y (x wall) 0 | 2.30 | 2577 | 2577 | 4.9 | 1429.7 | 47.2 | 62.8 | 18.2-28.2 |
| door +x+y (x wall) 1 | 2.30 | 2139 | 2137 | 4.9 | 1210.9 | 46.3 | 54.9 | 13.3-23.3 |
| door +x+y (x wall) 2 | 2.30 | 1589 | 1594 | 4.9 | 909.3 | 45.8 | 57.6 | 208.3-218.3 |
| door +x+y (x wall) 3 | 2.30 | 1045 | 1045 | 4.9 | 604.3 | 45.5 | 54.9 | 13.3-23.3 |
| door +x+y (x wall) 4 | 2.30 | 515 | 513 | 5.1 | 316.4 | 43.1 | 54.9 | 5.8-15.7 |
| door +x+y (corner) | 2.30 | 124 | 124 | 6.3 | 75.9 | 46.4 | 54.9 | 51.4-61.4 |
| door -x+y (y wall) 0 | 2.30 | 2577 | 2577 | 4.9 | 1439.1 | 46.9 | 60.2 | 11.5-21.5 |
| door -x+y (y wall) 1 | 2.30 | 2134 | 2137 | 4.9 | 1216.8 | 45.9 | 60.2 | 19.2-29.2 |
| door -x+y (y wall) 2 | 2.30 | 1592 | 1594 | 4.9 | 915.5 | 45.6 | 60.2 | 11.5-21.5 |
| door -x+y (y wall) 3 | 2.30 | 1049 | 1045 | 4.9 | 607.3 | 45.4 | 60.2 | 11.5-21.5 |
| door -x+y (y wall) 4 | 2.30 | 509 | 513 | 5.1 | 312.2 | 43.2 | 57.6 | 19.8-29.7 |
| door -x+y (x wall) 0 | 2.30 | 2577 | 2577 | 4.9 | 1427.9 | 47.2 | 60.2 | 21.2-31.1 |
| door -x+y (x wall) 1 | 2.30 | 2140 | 2137 | 4.9 | 1214.6 | 46.1 | 57.6 | 14.2-24.1 |
| door -x+y (x wall) 2 | 2.30 | 1596 | 1594 | 4.9 | 912.0 | 45.9 | 60.2 | 24.7-34.6 |
| door -x+y (x wall) 3 | 2.30 | 1041 | 1045 | 4.9 | 604.5 | 45.3 | 57.6 | 25.9-35.9 |
| door -x+y (x wall) 4 | 2.30 | 517 | 513 | 4.9 | 314.0 | 43.6 | 57.6 | 10.7-20.6 |
| door -x+y (corner) | 2.30 | 124 | 124 | 6.3 | 75.6 | 46.6 | 52.3 | 47.9-57.9 |
| door -x-y (y wall) 0 | 2.30 | 2577 | 2577 | 4.9 | 1430.9 | 47.1 | 54.9 | 27.1-37.1 |
| door -x-y (y wall) 1 | 2.30 | 2131 | 2137 | 4.9 | 1213.0 | 46.0 | 57.6 | 18.0-28.0 |
| door -x-y (y wall) 2 | 2.30 | 1604 | 1594 | 4.9 | 900.9 | 46.7 | 54.9 | 16.4-26.4 |
| door -x-y (y wall) 3 | 2.30 | 1044 | 1045 | 4.9 | 604.5 | 45.4 | 60.2 | 28.9-38.8 |
| door -x-y (y wall) 4 | 2.30 | 516 | 513 | 4.9 | 314.0 | 43.5 | 60.2 | 19.8-29.7 |
| door -x-y (x wall) 0 | 2.30 | 2577 | 2577 | 4.9 | 1441.6 | 46.8 | 60.2 | 11.5-21.5 |
| door -x-y (x wall) 1 | 2.30 | 2143 | 2137 | 4.9 | 1218.2 | 46.1 | 57.6 | 10.7-20.6 |
| door -x-y (x wall) 2 | 2.30 | 1584 | 1594 | 4.9 | 905.3 | 45.9 | 60.2 | 11.7-21.7 |
| door -x-y (x wall) 3 | 2.30 | 1046 | 1045 | 4.9 | 605.9 | 45.4 | 60.2 | 11.5-21.5 |
| door -x-y (x wall) 4 | 2.30 | 510 | 513 | 5.1 | 310.5 | 43.5 | 57.6 | 18.7-28.7 |
| door -x-y (corner) | 2.30 | 124 | 124 | 6.3 | 74.9 | 47.1 | 52.3 | 28.7-38.7 |
| door +x-y (y wall) 0 | 2.30 | 2577 | 2577 | 4.9 | 1432.7 | 47.1 | 60.2 | 11.5-21.5 |
| door +x-y (y wall) 1 | 2.30 | 2140 | 2137 | 4.9 | 1213.3 | 46.2 | 60.2 | 11.5-21.5 |
| door +x-y (y wall) 2 | 2.30 | 1595 | 1594 | 4.9 | 919.7 | 45.5 | 57.6 | 10.7-20.6 |
| door +x-y (y wall) 3 | 2.30 | 1044 | 1045 | 4.9 | 606.4 | 45.3 | 60.2 | 11.5-21.5 |
| door +x-y (y wall) 4 | 2.30 | 521 | 513 | 5.1 | 315.0 | 43.8 | 57.6 | 18.7-28.7 |
| door +x-y (x wall) 0 | 2.30 | 2577 | 2577 | 4.9 | 1438.1 | 46.9 | 60.2 | 18.2-28.2 |
| door +x-y (x wall) 1 | 2.30 | 2134 | 2137 | 4.9 | 1210.5 | 46.2 | 54.9 | 10.8-20.8 |
| door +x-y (x wall) 2 | 2.30 | 1593 | 1594 | 4.9 | 918.3 | 45.5 | 60.2 | 18.2-28.2 |
| door +x-y (x wall) 3 | 2.30 | 1046 | 1045 | 4.9 | 608.0 | 45.2 | 54.9 | 13.3-23.3 |
| door +x-y (x wall) 4 | 2.30 | 505 | 513 | 5.1 | 312.7 | 42.8 | 60.2 | 28.5-38.5 |
| door +x-y (corner) | 2.30 | 124 | 124 | 6.5 | 72.9 | 48.5 | 57.6 | 63.0-72.9 |
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
| door +x+y (y wall) 1 | door | 2.30 | 2135 | 3.4% | 46.2% |
| door +x+y (y wall) 2 | door | 2.30 | 1599 | 2.5% | 34.6% |
| door +x+y (y wall) 3 | door | 2.30 | 1045 | 1.6% | 22.6% |
| door +x+y (y wall) 4 | door | 2.30 | 511 | 0.8% | 11.1% |
| door +x+y (x wall) 0 | door | 2.30 | 2577 | 4.1% | 55.8% |
| door +x+y (x wall) 1 | door | 2.30 | 2139 | 3.4% | 46.3% |
| door +x+y (x wall) 2 | door | 2.30 | 1589 | 2.5% | 34.4% |
| door +x+y (x wall) 3 | door | 2.30 | 1045 | 1.6% | 22.6% |
| door +x+y (x wall) 4 | door | 2.30 | 515 | 0.8% | 11.1% |
| door +x+y (corner) | door | 2.30 | 124 | 0.2% | 2.7% |
| door -x+y (y wall) 0 | door | 2.30 | 2577 | 4.1% | 55.8% |
| door -x+y (y wall) 1 | door | 2.30 | 2134 | 3.4% | 46.2% |
| door -x+y (y wall) 2 | door | 2.30 | 1592 | 2.5% | 34.5% |
| door -x+y (y wall) 3 | door | 2.30 | 1049 | 1.7% | 22.7% |
| door -x+y (y wall) 4 | door | 2.30 | 509 | 0.8% | 11.0% |
| door -x+y (x wall) 0 | door | 2.30 | 2577 | 4.1% | 55.8% |
| door -x+y (x wall) 1 | door | 2.30 | 2140 | 3.4% | 46.3% |
| door -x+y (x wall) 2 | door | 2.30 | 1596 | 2.5% | 34.5% |
| door -x+y (x wall) 3 | door | 2.30 | 1041 | 1.6% | 22.5% |
| door -x+y (x wall) 4 | door | 2.30 | 517 | 0.8% | 11.2% |
| door -x+y (corner) | door | 2.30 | 124 | 0.2% | 2.7% |
| door -x-y (y wall) 0 | door | 2.30 | 2577 | 4.1% | 55.8% |
| door -x-y (y wall) 1 | door | 2.30 | 2131 | 3.4% | 46.1% |
| door -x-y (y wall) 2 | door | 2.30 | 1604 | 2.5% | 34.7% |
| door -x-y (y wall) 3 | door | 2.30 | 1044 | 1.6% | 22.6% |
| door -x-y (y wall) 4 | door | 2.30 | 516 | 0.8% | 11.2% |
| door -x-y (x wall) 0 | door | 2.30 | 2577 | 4.1% | 55.8% |
| door -x-y (x wall) 1 | door | 2.30 | 2143 | 3.4% | 46.4% |
| door -x-y (x wall) 2 | door | 2.30 | 1584 | 2.5% | 34.3% |
| door -x-y (x wall) 3 | door | 2.30 | 1046 | 1.6% | 22.6% |
| door -x-y (x wall) 4 | door | 2.30 | 510 | 0.8% | 11.0% |
| door -x-y (corner) | door | 2.30 | 124 | 0.2% | 2.7% |
| door +x-y (y wall) 0 | door | 2.30 | 2577 | 4.1% | 55.8% |
| door +x-y (y wall) 1 | door | 2.30 | 2140 | 3.4% | 46.3% |
| door +x-y (y wall) 2 | door | 2.30 | 1595 | 2.5% | 34.5% |
| door +x-y (y wall) 3 | door | 2.30 | 1044 | 1.6% | 22.6% |
| door +x-y (y wall) 4 | door | 2.30 | 521 | 0.8% | 11.3% |
| door +x-y (x wall) 0 | door | 2.30 | 2577 | 4.1% | 55.8% |
| door +x-y (x wall) 1 | door | 2.30 | 2134 | 3.4% | 46.2% |
| door +x-y (x wall) 2 | door | 2.30 | 1593 | 2.5% | 34.5% |
| door +x-y (x wall) 3 | door | 2.30 | 1046 | 1.6% | 22.6% |
| door +x-y (x wall) 4 | door | 2.30 | 505 | 0.8% | 10.9% |
| door +x-y (corner) | door | 2.30 | 124 | 0.2% | 2.7% |
| **doors (44)** | door | 101.20 | 63424 | 100.0% | |
| **avenues (4)** | avenue | 22.64 | 0 | 0.0% | |

**Unused exit width: 22.6 of 123.8 m (18.3%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 1441.6 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 25.5%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 2577 | 4.1% | 2577 | 4.1% |
| straight +x+y (y wing) 1 | straight | yes | 2135 | 3.4% | 2135 | 3.4% |
| straight +x+y (y wing) 2 | straight | yes | 1599 | 2.5% | 1599 | 2.5% |
| straight +x+y (y wing) 3 | straight | yes | 1045 | 1.6% | 1045 | 1.6% |
| straight +x+y (y wing) 4 | straight | yes | 511 | 0.8% | 511 | 0.8% |
| straight +x+y (x wing) 0 | straight | yes | 2577 | 4.1% | 2577 | 4.1% |
| straight +x+y (x wing) 1 | straight | yes | 2139 | 3.4% | 2139 | 3.4% |
| straight +x+y (x wing) 2 | straight | yes | 1589 | 2.5% | 1589 | 2.5% |
| straight +x+y (x wing) 3 | straight | yes | 1045 | 1.6% | 1045 | 1.6% |
| straight +x+y (x wing) 4 | straight | yes | 515 | 0.8% | 515 | 0.8% |
| corner +x+y | corner | yes | 1019 | 1.6% | 124 | 0.2% |
| straight -x+y (y wing) 0 | straight | yes | 2577 | 4.1% | 2577 | 4.1% |
| straight -x+y (y wing) 1 | straight | yes | 2134 | 3.4% | 2134 | 3.4% |
| straight -x+y (y wing) 2 | straight | yes | 1592 | 2.5% | 1592 | 2.5% |
| straight -x+y (y wing) 3 | straight | yes | 1049 | 1.7% | 1049 | 1.7% |
| straight -x+y (y wing) 4 | straight | yes | 509 | 0.8% | 509 | 0.8% |
| straight -x+y (x wing) 0 | straight | yes | 2577 | 4.1% | 2577 | 4.1% |
| straight -x+y (x wing) 1 | straight | yes | 2140 | 3.4% | 2140 | 3.4% |
| straight -x+y (x wing) 2 | straight | yes | 1596 | 2.5% | 1596 | 2.5% |
| straight -x+y (x wing) 3 | straight | yes | 1041 | 1.6% | 1041 | 1.6% |
| straight -x+y (x wing) 4 | straight | yes | 517 | 0.8% | 517 | 0.8% |
| corner -x+y | corner | yes | 1019 | 1.6% | 124 | 0.2% |
| straight -x-y (y wing) 0 | straight | yes | 2577 | 4.1% | 2577 | 4.1% |
| straight -x-y (y wing) 1 | straight | yes | 2131 | 3.4% | 2131 | 3.4% |
| straight -x-y (y wing) 2 | straight | yes | 1604 | 2.5% | 1604 | 2.5% |
| straight -x-y (y wing) 3 | straight | yes | 1044 | 1.6% | 1044 | 1.6% |
| straight -x-y (y wing) 4 | straight | yes | 516 | 0.8% | 516 | 0.8% |
| straight -x-y (x wing) 0 | straight | yes | 2577 | 4.1% | 2577 | 4.1% |
| straight -x-y (x wing) 1 | straight | yes | 2143 | 3.4% | 2143 | 3.4% |
| straight -x-y (x wing) 2 | straight | yes | 1584 | 2.5% | 1584 | 2.5% |
| straight -x-y (x wing) 3 | straight | yes | 1046 | 1.6% | 1046 | 1.6% |
| straight -x-y (x wing) 4 | straight | yes | 510 | 0.8% | 510 | 0.8% |
| corner -x-y | corner | yes | 1018 | 1.6% | 124 | 0.2% |
| straight +x-y (y wing) 0 | straight | yes | 2577 | 4.1% | 2577 | 4.1% |
| straight +x-y (y wing) 1 | straight | yes | 2140 | 3.4% | 2140 | 3.4% |
| straight +x-y (y wing) 2 | straight | yes | 1595 | 2.5% | 1595 | 2.5% |
| straight +x-y (y wing) 3 | straight | yes | 1044 | 1.6% | 1044 | 1.6% |
| straight +x-y (y wing) 4 | straight | yes | 521 | 0.8% | 521 | 0.8% |
| straight +x-y (x wing) 0 | straight | yes | 2577 | 4.1% | 2577 | 4.1% |
| straight +x-y (x wing) 1 | straight | yes | 2134 | 3.4% | 2134 | 3.4% |
| straight +x-y (x wing) 2 | straight | yes | 1593 | 2.5% | 1593 | 2.5% |
| straight +x-y (x wing) 3 | straight | yes | 1046 | 1.6% | 1046 | 1.6% |
| straight +x-y (x wing) 4 | straight | yes | 505 | 0.8% | 505 | 0.8% |
| corner +x-y | corner | yes | 1020 | 1.6% | 124 | 0.2% |
| **straight (40)** | | | 62928 | | 62928 | 99.2% |
| **corner (4)** | | | 4076 | | 496 | 0.8% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| door +x+y (y wall) 0 | 2577 | 4.9 | 1426.7 | 0.57 | 0.72 | 0.0% |
| door +x+y (y wall) 1 | 2135 | 4.9 | 1204.8 | 0.56 | 0.72 | 0.0% |
| door +x+y (y wall) 2 | 1599 | 4.9 | 910.7 | 0.55 | 0.69 | 0.0% |
| door +x+y (y wall) 3 | 1045 | 4.9 | 603.3 | 0.54 | 0.72 | 0.0% |
| door +x+y (y wall) 4 | 511 | 4.9 | 315.5 | 0.51 | 0.69 | 0.0% |
| door +x+y (x wall) 0 | 2577 | 4.9 | 1429.7 | 0.56 | 0.75 | 0.0% |
| door +x+y (x wall) 1 | 2139 | 4.9 | 1210.9 | 0.55 | 0.66 | 0.0% |
| door +x+y (x wall) 2 | 1589 | 4.9 | 909.3 | 0.55 | 0.69 | 0.0% |
| door +x+y (x wall) 3 | 1045 | 4.9 | 604.3 | 0.54 | 0.66 | 0.0% |
| door +x+y (x wall) 4 | 515 | 5.1 | 316.4 | 0.52 | 0.66 | 0.0% |
| door +x+y (corner) | 124 | 6.3 | 75.9 | 0.55 | 0.66 | 0.0% |
| door -x+y (y wall) 0 | 2577 | 4.9 | 1439.1 | 0.56 | 0.72 | 0.0% |
| door -x+y (y wall) 1 | 2134 | 4.9 | 1216.8 | 0.55 | 0.72 | 0.0% |
| door -x+y (y wall) 2 | 1592 | 4.9 | 915.5 | 0.55 | 0.72 | 0.0% |
| door -x+y (y wall) 3 | 1049 | 4.9 | 607.3 | 0.54 | 0.72 | 0.0% |
| door -x+y (y wall) 4 | 509 | 5.1 | 312.2 | 0.52 | 0.69 | 0.0% |
| door -x+y (x wall) 0 | 2577 | 4.9 | 1427.9 | 0.57 | 0.72 | 0.0% |
| door -x+y (x wall) 1 | 2140 | 4.9 | 1214.6 | 0.55 | 0.69 | 0.0% |
| door -x+y (x wall) 2 | 1596 | 4.9 | 912.0 | 0.55 | 0.72 | 0.0% |
| door -x+y (x wall) 3 | 1041 | 4.9 | 604.5 | 0.54 | 0.69 | 0.0% |
| door -x+y (x wall) 4 | 517 | 4.9 | 314.0 | 0.52 | 0.69 | 0.0% |
| door -x+y (corner) | 124 | 6.3 | 75.6 | 0.56 | 0.63 | 0.0% |
| door -x-y (y wall) 0 | 2577 | 4.9 | 1430.9 | 0.56 | 0.66 | 0.0% |
| door -x-y (y wall) 1 | 2131 | 4.9 | 1213.0 | 0.55 | 0.69 | 0.0% |
| door -x-y (y wall) 2 | 1604 | 4.9 | 900.9 | 0.56 | 0.66 | 0.0% |
| door -x-y (y wall) 3 | 1044 | 4.9 | 604.5 | 0.54 | 0.72 | 0.0% |
| door -x-y (y wall) 4 | 516 | 4.9 | 314.0 | 0.52 | 0.72 | 0.0% |
| door -x-y (x wall) 0 | 2577 | 4.9 | 1441.6 | 0.56 | 0.72 | 0.0% |
| door -x-y (x wall) 1 | 2143 | 4.9 | 1218.2 | 0.55 | 0.69 | 0.0% |
| door -x-y (x wall) 2 | 1584 | 4.9 | 905.3 | 0.55 | 0.72 | 0.0% |
| door -x-y (x wall) 3 | 1046 | 4.9 | 605.9 | 0.54 | 0.72 | 0.0% |
| door -x-y (x wall) 4 | 510 | 5.1 | 310.5 | 0.52 | 0.69 | 0.0% |
| door -x-y (corner) | 124 | 6.3 | 74.9 | 0.56 | 0.63 | 0.0% |
| door +x-y (y wall) 0 | 2577 | 4.9 | 1432.7 | 0.56 | 0.72 | 0.0% |
| door +x-y (y wall) 1 | 2140 | 4.9 | 1213.3 | 0.55 | 0.72 | 0.0% |
| door +x-y (y wall) 2 | 1595 | 4.9 | 919.7 | 0.54 | 0.69 | 0.0% |
| door +x-y (y wall) 3 | 1044 | 4.9 | 606.4 | 0.54 | 0.72 | 0.0% |
| door +x-y (y wall) 4 | 521 | 5.1 | 315.0 | 0.52 | 0.69 | 0.0% |
| door +x-y (x wall) 0 | 2577 | 4.9 | 1438.1 | 0.56 | 0.72 | 0.0% |
| door +x-y (x wall) 1 | 2134 | 4.9 | 1210.5 | 0.55 | 0.66 | 0.0% |
| door +x-y (x wall) 2 | 1593 | 4.9 | 918.3 | 0.54 | 0.72 | 0.0% |
| door +x-y (x wall) 3 | 1046 | 4.9 | 608.0 | 0.54 | 0.66 | 0.0% |
| door +x-y (x wall) 4 | 505 | 5.1 | 312.7 | 0.51 | 0.72 | 0.0% |
| door +x-y (corner) | 124 | 6.5 | 72.9 | 0.58 | 0.69 | 0.0% |

Mean flow / w J averaged over the doors 0.55, over the avenues nan.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 103.1 | 2577 | 2577 / 0 / 0 | 0.7 | 1423.7 | 1.81 | 2.11 | 90% | 90% | 0% | 4.28 |
| straight +x+y (y wing) 1 | 1.20 | 81.5 | 2022 | 2135 / 0 / 0 | 0.7 | 1201.8 | 1.78 | 2.11 | 88% | 88% | 0% | 4.27 |
| straight +x+y (y wing) 2 | 1.20 | 61.0 | 1485 | 1599 / 0 / 0 | 0.7 | 907.8 | 1.76 | 2.11 | 84% | 84% | 0% | 4.36 |
| straight +x+y (y wing) 3 | 1.20 | 39.4 | 930 | 1045 / 0 / 1 | 0.7 | 600.3 | 1.74 | 2.11 | 82% | 82% | 0% | 4.27 |
| straight +x+y (y wing) 4 | 1.20 | 18.8 | 404 | 511 / 0 / 1 | 0.7 | 312.6 | 1.64 | 2.01 | 69% | 69% | 0% | 4.34 |
| straight +x+y (x wing) 0 | 1.20 | 103.1 | 2577 | 2577 / 0 / 0 | 0.7 | 1426.7 | 1.81 | 2.31 | 90% | 90% | 0% | 4.25 |
| straight +x+y (x wing) 1 | 1.20 | 81.5 | 2022 | 2139 / 0 / 0 | 0.7 | 1207.9 | 1.77 | 2.11 | 87% | 87% | 0% | 4.30 |
| straight +x+y (x wing) 2 | 1.20 | 61.0 | 1486 | 1589 / 0 / 1 | 0.7 | 906.4 | 1.76 | 2.01 | 87% | 87% | 0% | 4.28 |
| straight +x+y (x wing) 3 | 1.20 | 39.4 | 930 | 1045 / 0 / 0 | 0.7 | 601.3 | 1.74 | 2.11 | 82% | 82% | 0% | 4.13 |
| straight +x+y (x wing) 4 | 1.20 | 18.8 | 404 | 515 / 0 / 0 | 0.7 | 313.4 | 1.65 | 2.01 | 69% | 69% | 0% | 4.12 |
| corner +x+y | 1.20 | 186.0 | 1019 | 124 / 0 / 898 | 0.7 | 1104.2 | 0.93 | 4.01 | 96% | 21% | 76% | 1.46 |
| straight -x+y (y wing) 0 | 1.20 | 103.1 | 2577 | 2577 / 0 / 0 | 0.7 | 1436.2 | 1.80 | 2.21 | 90% | 90% | 0% | 4.03 |
| straight -x+y (y wing) 1 | 1.20 | 81.5 | 2022 | 2134 / 0 / 0 | 0.7 | 1213.9 | 1.76 | 2.21 | 87% | 87% | 0% | 4.01 |
| straight -x+y (y wing) 2 | 1.20 | 61.0 | 1485 | 1592 / 0 / 0 | 0.7 | 912.5 | 1.75 | 2.21 | 85% | 85% | 0% | 4.09 |
| straight -x+y (y wing) 3 | 1.20 | 39.4 | 930 | 1049 / 0 / 0 | 0.7 | 604.3 | 1.74 | 2.21 | 82% | 82% | 0% | 4.11 |
| straight -x+y (y wing) 4 | 1.20 | 18.8 | 404 | 509 / 0 / 0 | 0.7 | 309.2 | 1.65 | 2.11 | 72% | 72% | 0% | 4.00 |
| straight -x+y (x wing) 0 | 1.20 | 103.1 | 2577 | 2577 / 0 / 0 | 0.7 | 1425.0 | 1.81 | 2.11 | 91% | 91% | 0% | 4.22 |
| straight -x+y (x wing) 1 | 1.20 | 81.5 | 2022 | 2140 / 0 / 1 | 0.7 | 1211.6 | 1.77 | 2.11 | 85% | 85% | 0% | 4.32 |
| straight -x+y (x wing) 2 | 1.20 | 61.0 | 1485 | 1596 / 0 / 0 | 0.7 | 909.0 | 1.76 | 2.11 | 84% | 84% | 0% | 4.34 |
| straight -x+y (x wing) 3 | 1.20 | 39.4 | 930 | 1041 / 0 / 0 | 0.7 | 601.5 | 1.73 | 2.01 | 80% | 80% | 0% | 4.24 |
| straight -x+y (x wing) 4 | 1.20 | 18.8 | 405 | 517 / 0 / 0 | 0.7 | 311.0 | 1.67 | 2.11 | 72% | 72% | 0% | 4.19 |
| corner -x+y | 1.20 | 186.0 | 1019 | 124 / 0 / 896 | 0.7 | 1110.1 | 0.92 | 3.91 | 96% | 21% | 76% | 1.45 |
| straight -x-y (y wing) 0 | 1.20 | 103.1 | 2577 | 2577 / 0 / 0 | 0.7 | 1427.9 | 1.81 | 2.01 | 90% | 90% | 0% | 4.20 |
| straight -x-y (y wing) 1 | 1.20 | 81.5 | 2022 | 2131 / 0 / 0 | 0.7 | 1210.0 | 1.76 | 2.01 | 85% | 85% | 0% | 4.31 |
| straight -x-y (y wing) 2 | 1.20 | 61.0 | 1485 | 1604 / 0 / 0 | 0.7 | 898.0 | 1.79 | 2.11 | 87% | 87% | 0% | 4.46 |
| straight -x-y (y wing) 3 | 1.20 | 39.4 | 930 | 1044 / 0 / 1 | 0.7 | 601.5 | 1.74 | 2.11 | 80% | 80% | 0% | 4.28 |
| straight -x-y (y wing) 4 | 1.20 | 18.8 | 405 | 516 / 0 / 0 | 0.7 | 311.0 | 1.66 | 2.21 | 72% | 72% | 0% | 4.25 |
| straight -x-y (x wing) 0 | 1.20 | 103.1 | 2577 | 2577 / 0 / 0 | 0.7 | 1438.6 | 1.79 | 2.21 | 90% | 90% | 0% | 4.09 |
| straight -x-y (x wing) 1 | 1.20 | 81.5 | 2022 | 2143 / 0 / 1 | 0.7 | 1215.3 | 1.77 | 2.01 | 87% | 87% | 0% | 4.03 |
| straight -x-y (x wing) 2 | 1.20 | 61.0 | 1485 | 1584 / 0 / 0 | 0.7 | 902.3 | 1.76 | 2.21 | 85% | 85% | 0% | 4.10 |
| straight -x-y (x wing) 3 | 1.20 | 39.4 | 930 | 1046 / 0 / 0 | 0.7 | 602.9 | 1.74 | 2.21 | 82% | 82% | 0% | 4.08 |
| straight -x-y (x wing) 4 | 1.20 | 18.8 | 405 | 510 / 0 / 0 | 0.7 | 307.5 | 1.66 | 2.01 | 74% | 74% | 0% | 4.18 |
| corner -x-y | 1.20 | 186.0 | 1018 | 124 / 0 / 896 | 0.7 | 1111.5 | 0.92 | 3.91 | 96% | 21% | 76% | 1.43 |
| straight +x-y (y wing) 0 | 1.20 | 103.1 | 2577 | 2577 / 0 / 0 | 0.7 | 1429.7 | 1.80 | 2.21 | 90% | 90% | 0% | 4.07 |
| straight +x-y (y wing) 1 | 1.20 | 81.5 | 2022 | 2140 / 0 / 0 | 0.7 | 1210.4 | 1.77 | 2.11 | 87% | 87% | 0% | 4.04 |
| straight +x-y (y wing) 2 | 1.20 | 61.0 | 1485 | 1595 / 0 / 0 | 0.7 | 916.7 | 1.74 | 2.11 | 86% | 86% | 0% | 4.11 |
| straight +x-y (y wing) 3 | 1.20 | 39.4 | 930 | 1044 / 0 / 0 | 0.7 | 603.4 | 1.73 | 2.21 | 80% | 80% | 0% | 4.09 |
| straight +x-y (y wing) 4 | 1.20 | 18.8 | 404 | 521 / 0 / 0 | 0.7 | 312.2 | 1.67 | 2.01 | 72% | 72% | 0% | 4.07 |
| straight +x-y (x wing) 0 | 1.20 | 103.1 | 2577 | 2577 / 0 / 0 | 0.7 | 1435.3 | 1.80 | 2.01 | 91% | 91% | 0% | 4.31 |
| straight +x-y (x wing) 1 | 1.20 | 81.5 | 2022 | 2134 / 0 / 0 | 0.7 | 1207.6 | 1.77 | 2.11 | 87% | 87% | 0% | 4.25 |
| straight +x-y (x wing) 2 | 1.20 | 61.0 | 1485 | 1593 / 0 / 0 | 0.7 | 915.3 | 1.74 | 2.11 | 85% | 85% | 0% | 4.18 |
| straight +x-y (x wing) 3 | 1.20 | 39.4 | 930 | 1046 / 0 / 0 | 0.7 | 605.0 | 1.73 | 2.11 | 82% | 82% | 0% | 4.17 |
| straight +x-y (x wing) 4 | 1.20 | 18.8 | 404 | 505 / 0 / 0 | 0.7 | 309.8 | 1.63 | 2.11 | 69% | 69% | 0% | 4.13 |
| corner +x-y | 1.20 | 186.0 | 1020 | 124 / 0 / 896 | 0.7 | 1106.5 | 0.92 | 4.31 | 96% | 22% | 75% | 1.49 |

The last agent out (agent 39708, t100 1441.6 s): last gangway straight -x-y (x wing) 0, exit -. The gangway that cleared last: straight -x-y (x wing) 0 at 1438.6 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 8804 | 7800.4 | 6.78 | 1438.6 / 1420.6 / 1272.6 | 1426.5 / 1310.2 / 1261.3 | 7396641.7 | 11752060 | 0.158 |
| gangway | 3792 | 3512.9 | 6.78 | 1437.0 / 1420.6 / 1272.6 | 1426.5 / 1310.2 / 1261.3 | 7396641.7 | 11516889 | 0.140 |
| walkway | 276 | 257.4 | 0.23 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 257 | 0.009 |
| avenue | 1920 | 1801.4 | 0.17 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 28 | 0.142 |
| exit | 4 | 2.0 | 0.00 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 0 | - |
| concourse | 2812 | 2226.8 | 2.83 | 1437.4 / 48.1 / 0.0 | 1343.1 / 20.1 / 0.0 | 0.0 | 234886 | 1.038 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 25392 | 16030.4 | 7.79 | 1310.2 / 1307.8 / 1293.1 | 1310.2 / 1307.8 / 1289.8 | 9124481.3 | 21927255 | 0.018 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 208 x 208 from (-104, -104) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -18.5 | -11.5 | gangway | 0.86 | 6.75 | 1306.4 | 1294.7 | 1259.5 | 7077.7 | 0.011 |
| 2 | -18.5 | 11.5 | gangway | 0.86 | 6.69 | 1292.0 | 1270.7 | 1230.8 | 6899.7 | 0.010 |
| 3 | 17.5 | 10.5 | gangway | 0.95 | 6.06 | 1302.2 | 1293.3 | 1231.9 | 6830.9 | 0.010 |
| 4 | -10.5 | -15.5 | gangway | 0.96 | 5.83 | 1300.1 | 1295.4 | 1238.5 | 6823.0 | 0.006 |
| 5 | 10.5 | -18.5 | gangway | 0.94 | 6.12 | 1306.9 | 1289.9 | 1228.2 | 6780.2 | 0.014 |
| 6 | 10.5 | 16.5 | gangway | 0.96 | 5.82 | 1297.6 | 1286.6 | 1224.7 | 6737.6 | 0.009 |
| 7 | -16.5 | 10.5 | gangway | 0.96 | 6.00 | 1298.9 | 1295.0 | 1223.6 | 6731.9 | 0.008 |
| 8 | -10.5 | -17.5 | gangway | 0.95 | 5.93 | 1303.4 | 1285.7 | 1213.2 | 6694.2 | 0.010 |
| 9 | -19.5 | -10.5 | gangway | 0.96 | 5.96 | 1317.6 | 1300.3 | 1224.5 | 6665.9 | 0.016 |
| 10 | -18.5 | -10.5 | gangway | 0.94 | 6.17 | 1316.0 | 1309.2 | 1249.9 | 6661.6 | 0.014 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -18.5 | -9.5 | seat row | 0.50 | 7.38 | 1303.1 | 1301.7 | 1289.8 | 4682.4 | 0.006 |
| 2 | 9.5 | -18.5 | seat row | 0.50 | 7.42 | 1278.4 | 1277.0 | 1267.0 | 4623.6 | 0.005 |
| 3 | -18.5 | 9.5 | seat row | 0.50 | 7.61 | 1273.5 | 1271.0 | 1260.9 | 4596.0 | 0.004 |
| 4 | -9.5 | 18.5 | seat row | 0.50 | 7.34 | 1280.8 | 1278.0 | 1269.1 | 4564.1 | 0.005 |
| 5 | -9.5 | 14.5 | seat row | 0.50 | 7.23 | 1298.5 | 1291.7 | 1281.9 | 4532.1 | 0.004 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 0; agent-steps of seated agents on another row's clearway: 0.

## Deposit check

Person-seconds deposited: 33685417.2, of them in excluded cells: 6102.499.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 5494561 overlapping pair-steps: p99 0.0028, max 0.0530 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0028 max 0.0530; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00749 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 0 (longest 0 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.748623 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.37 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 0 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
