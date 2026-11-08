# Experiment `L_load95_s1`

**Task 5.8 stage 2: venue L, 95% load (seed 1), default model**

Venue L (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (4000 x 4000), cache key a2f3aaf59c2252b7, content hash 022d17b202313d70). 60253 agents on 95% of the 63424 seats (spawnSeatedCrowd, seed 1), buffer N = 65536, 6439 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 8440358 evaluations, 466140 switches, 0 forced choices).
Capacity: **within design capacity** (the L venue's design capacity 63424, jam capacity 171923: 23822.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `cd8e0bbf3411846ca7aa6719887d122a142a7ca1`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-15T16:52:00, 605.2 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 2259 | 395.1 |
| t90 | 4515 | 789.7 |
| t100 | 6439 | 1126.2 |

t_p: the step by which ceil(p x 60253) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 1771 | 0 | 70.5 | 870.5 | 23.5 | 25.5 | 80.5-90.4 |
| -x | 5.66 | 1762 | 0 | 70.5 | 862.3 | 23.6 | 26.6 | 154.3-164.2 |
| +y | 5.66 | 1776 | 0 | 70.5 | 875.1 | 23.4 | 26.6 | 82.0-92.0 |
| -y | 5.66 | 1761 | 0 | 70.5 | 866.0 | 23.5 | 26.6 | 300.3-310.3 |
| door +x+y (y wall) 0 | 2.30 | 1509 | 2445 | 4.9 | 960.1 | 41.2 | 57.6 | 19.1-29.0 |
| door +x+y (y wall) 1 | 2.30 | 1687 | 2029 | 4.9 | 1094.0 | 40.4 | 54.9 | 11.4-21.3 |
| door +x+y (y wall) 2 | 2.30 | 1502 | 1513 | 4.9 | 1123.6 | 35.0 | 57.6 | 11.0-21.0 |
| door +x+y (y wall) 3 | 2.30 | 1129 | 999 | 4.9 | 1126.2 | 26.3 | 54.9 | 15.0-25.0 |
| door +x+y (y wall) 4 | 2.30 | 584 | 485 | 4.9 | 1122.6 | 13.6 | 54.9 | 15.6-25.5 |
| door +x+y (x wall) 0 | 2.30 | 1506 | 2443 | 5.1 | 952.2 | 41.5 | 57.6 | 30.6-40.6 |
| door +x+y (x wall) 1 | 2.30 | 1684 | 2019 | 4.9 | 1078.1 | 40.9 | 57.6 | 24.5-34.5 |
| door +x+y (x wall) 2 | 2.30 | 1499 | 1499 | 4.9 | 1096.0 | 35.8 | 57.6 | 18.2-28.2 |
| door +x+y (x wall) 3 | 2.30 | 1161 | 990 | 4.9 | 1126.0 | 27.0 | 60.2 | 24.7-34.6 |
| door +x+y (x wall) 4 | 2.30 | 622 | 487 | 5.1 | 1105.9 | 14.7 | 57.6 | 8.2-18.2 |
| door +x+y (corner) | 2.30 | 380 | 116 | 6.3 | 956.0 | 10.4 | 54.9 | 47.7-57.7 |
| door -x+y (y wall) 0 | 2.30 | 1512 | 2445 | 4.9 | 926.0 | 42.8 | 60.2 | 11.7-21.7 |
| door -x+y (y wall) 1 | 2.30 | 1655 | 2024 | 4.9 | 1102.3 | 39.3 | 57.6 | 7.9-17.8 |
| door -x+y (y wall) 2 | 2.30 | 1527 | 1511 | 4.9 | 1099.1 | 36.4 | 54.9 | 10.8-20.8 |
| door -x+y (y wall) 3 | 2.30 | 1223 | 1004 | 4.9 | 1102.3 | 29.1 | 57.6 | 28.5-38.5 |
| door -x+y (y wall) 4 | 2.30 | 522 | 494 | 5.1 | 1034.2 | 13.2 | 57.6 | 8.6-18.5 |
| door -x+y (x wall) 0 | 2.30 | 1501 | 2451 | 4.9 | 948.0 | 41.5 | 60.2 | 14.5-24.5 |
| door -x+y (x wall) 1 | 2.30 | 1672 | 2036 | 4.9 | 1083.2 | 40.4 | 54.9 | 76.4-86.4 |
| door -x+y (x wall) 2 | 2.30 | 1527 | 1521 | 4.9 | 1099.8 | 36.4 | 60.2 | 19.8-29.7 |
| door -x+y (x wall) 3 | 2.30 | 1249 | 998 | 4.9 | 1096.3 | 29.8 | 57.6 | 21.0-31.0 |
| door -x+y (x wall) 4 | 2.30 | 591 | 482 | 4.9 | 1046.6 | 14.8 | 54.9 | 10.7-20.6 |
| door -x+y (corner) | 2.30 | 325 | 115 | 6.3 | 807.0 | 10.6 | 54.9 | 26.9-36.9 |
| door -x-y (y wall) 0 | 2.30 | 1487 | 2430 | 4.9 | 974.1 | 40.0 | 60.2 | 21.0-31.0 |
| door -x-y (y wall) 1 | 2.30 | 1688 | 2027 | 4.9 | 1072.7 | 41.2 | 57.6 | 10.1-20.1 |
| door -x-y (y wall) 2 | 2.30 | 1481 | 1522 | 4.9 | 1108.4 | 35.0 | 60.2 | 24.7-34.6 |
| door -x-y (y wall) 3 | 2.30 | 1073 | 989 | 4.9 | 1066.9 | 26.4 | 60.2 | 16.4-26.4 |
| door -x-y (y wall) 4 | 2.30 | 691 | 490 | 4.9 | 1077.6 | 16.8 | 60.2 | 17.0-26.9 |
| door -x-y (x wall) 0 | 2.30 | 1480 | 2430 | 4.9 | 968.6 | 40.1 | 54.9 | 15.2-25.2 |
| door -x-y (x wall) 1 | 2.30 | 1683 | 2025 | 4.9 | 1092.3 | 40.4 | 57.6 | 10.7-20.6 |
| door -x-y (x wall) 2 | 2.30 | 1439 | 1515 | 4.9 | 1104.2 | 34.1 | 54.9 | 32.7-42.7 |
| door -x-y (x wall) 3 | 2.30 | 1084 | 998 | 4.9 | 1091.2 | 26.0 | 54.9 | 7.0-17.0 |
| door -x-y (x wall) 4 | 2.30 | 710 | 493 | 5.1 | 1089.7 | 17.1 | 57.6 | 25.0-35.0 |
| door -x-y (corner) | 2.30 | 454 | 120 | 6.3 | 1039.6 | 11.5 | 57.6 | 144.1-154.1 |
| door +x-y (y wall) 0 | 2.30 | 1484 | 2435 | 4.9 | 941.7 | 41.3 | 60.2 | 11.5-21.5 |
| door +x-y (y wall) 1 | 2.30 | 1686 | 2029 | 4.9 | 1073.1 | 41.2 | 57.6 | 28.0-38.0 |
| door +x-y (y wall) 2 | 2.30 | 1476 | 1531 | 4.9 | 1104.7 | 35.0 | 57.6 | 25.4-35.3 |
| door +x-y (y wall) 3 | 2.30 | 1081 | 992 | 4.9 | 1109.8 | 25.5 | 57.6 | 23.8-33.8 |
| door +x-y (y wall) 4 | 2.30 | 719 | 479 | 5.1 | 1104.9 | 17.1 | 54.9 | 10.8-20.8 |
| door +x-y (x wall) 0 | 2.30 | 1503 | 2464 | 4.9 | 946.8 | 41.6 | 57.6 | 11.0-21.0 |
| door +x-y (x wall) 1 | 2.30 | 1697 | 2061 | 4.9 | 1114.0 | 39.9 | 60.2 | 18.2-28.2 |
| door +x-y (x wall) 2 | 2.30 | 1467 | 1517 | 4.9 | 1078.5 | 35.6 | 54.9 | 11.5-21.5 |
| door +x-y (x wall) 3 | 2.30 | 1121 | 997 | 4.9 | 1110.0 | 26.5 | 57.6 | 18.0-28.0 |
| door +x-y (x wall) 4 | 2.30 | 659 | 482 | 5.1 | 1082.3 | 16.0 | 60.2 | 8.0-18.0 |
| door +x-y (corner) | 2.30 | 453 | 121 | 6.5 | 784.5 | 15.2 | 57.6 | 48.3-58.2 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (2.30 m; a corner door's: the gap between its wall ends, 2.30 m); agents are removed past the outer wall's outer face (92.71 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 1771 | 2.9% | 19.9% |
| -x | avenue | 5.66 | 1762 | 2.9% | 19.8% |
| +y | avenue | 5.66 | 1776 | 2.9% | 20.0% |
| -y | avenue | 5.66 | 1761 | 2.9% | 19.8% |
| door +x+y (y wall) 0 | door | 2.30 | 1509 | 2.5% | 41.8% |
| door +x+y (y wall) 1 | door | 2.30 | 1687 | 2.8% | 46.7% |
| door +x+y (y wall) 2 | door | 2.30 | 1502 | 2.5% | 41.6% |
| door +x+y (y wall) 3 | door | 2.30 | 1129 | 1.9% | 31.3% |
| door +x+y (y wall) 4 | door | 2.30 | 584 | 1.0% | 16.2% |
| door +x+y (x wall) 0 | door | 2.30 | 1506 | 2.5% | 41.7% |
| door +x+y (x wall) 1 | door | 2.30 | 1684 | 2.8% | 46.7% |
| door +x+y (x wall) 2 | door | 2.30 | 1499 | 2.5% | 41.5% |
| door +x+y (x wall) 3 | door | 2.30 | 1161 | 1.9% | 32.2% |
| door +x+y (x wall) 4 | door | 2.30 | 622 | 1.0% | 17.2% |
| door +x+y (corner) | door | 2.30 | 380 | 0.6% | 10.5% |
| door -x+y (y wall) 0 | door | 2.30 | 1512 | 2.5% | 41.9% |
| door -x+y (y wall) 1 | door | 2.30 | 1655 | 2.7% | 45.9% |
| door -x+y (y wall) 2 | door | 2.30 | 1527 | 2.5% | 42.3% |
| door -x+y (y wall) 3 | door | 2.30 | 1223 | 2.0% | 33.9% |
| door -x+y (y wall) 4 | door | 2.30 | 522 | 0.9% | 14.5% |
| door -x+y (x wall) 0 | door | 2.30 | 1501 | 2.5% | 41.6% |
| door -x+y (x wall) 1 | door | 2.30 | 1672 | 2.8% | 46.3% |
| door -x+y (x wall) 2 | door | 2.30 | 1527 | 2.5% | 42.3% |
| door -x+y (x wall) 3 | door | 2.30 | 1249 | 2.1% | 34.6% |
| door -x+y (x wall) 4 | door | 2.30 | 591 | 1.0% | 16.4% |
| door -x+y (corner) | door | 2.30 | 325 | 0.5% | 9.0% |
| door -x-y (y wall) 0 | door | 2.30 | 1487 | 2.5% | 41.2% |
| door -x-y (y wall) 1 | door | 2.30 | 1688 | 2.8% | 46.8% |
| door -x-y (y wall) 2 | door | 2.30 | 1481 | 2.5% | 41.0% |
| door -x-y (y wall) 3 | door | 2.30 | 1073 | 1.8% | 29.7% |
| door -x-y (y wall) 4 | door | 2.30 | 691 | 1.1% | 19.1% |
| door -x-y (x wall) 0 | door | 2.30 | 1480 | 2.5% | 41.0% |
| door -x-y (x wall) 1 | door | 2.30 | 1683 | 2.8% | 46.6% |
| door -x-y (x wall) 2 | door | 2.30 | 1439 | 2.4% | 39.9% |
| door -x-y (x wall) 3 | door | 2.30 | 1084 | 1.8% | 30.0% |
| door -x-y (x wall) 4 | door | 2.30 | 710 | 1.2% | 19.7% |
| door -x-y (corner) | door | 2.30 | 454 | 0.8% | 12.6% |
| door +x-y (y wall) 0 | door | 2.30 | 1484 | 2.5% | 41.1% |
| door +x-y (y wall) 1 | door | 2.30 | 1686 | 2.8% | 46.7% |
| door +x-y (y wall) 2 | door | 2.30 | 1476 | 2.4% | 40.9% |
| door +x-y (y wall) 3 | door | 2.30 | 1081 | 1.8% | 30.0% |
| door +x-y (y wall) 4 | door | 2.30 | 719 | 1.2% | 19.9% |
| door +x-y (x wall) 0 | door | 2.30 | 1503 | 2.5% | 41.6% |
| door +x-y (x wall) 1 | door | 2.30 | 1697 | 2.8% | 47.0% |
| door +x-y (x wall) 2 | door | 2.30 | 1467 | 2.4% | 40.6% |
| door +x-y (x wall) 3 | door | 2.30 | 1121 | 1.9% | 31.1% |
| door +x-y (x wall) 4 | door | 2.30 | 659 | 1.1% | 18.3% |
| door +x-y (corner) | door | 2.30 | 453 | 0.8% | 12.6% |
| **doors (44)** | door | 101.20 | 53183 | 88.3% | |
| **avenues (4)** | avenue | 22.64 | 7070 | 11.7% | |

**Unused exit width: 0.0 of 123.8 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 1126.2 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 31.0%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 2205 | 3.7% | 2204 | 3.7% |
| straight +x+y (y wing) 1 | straight | yes | 1814 | 3.0% | 1713 | 2.8% |
| straight +x+y (y wing) 2 | straight | yes | 1539 | 2.6% | 1526 | 2.5% |
| straight +x+y (y wing) 3 | straight | yes | 1157 | 1.9% | 1151 | 1.9% |
| straight +x+y (y wing) 4 | straight | yes | 551 | 0.9% | 538 | 0.9% |
| straight +x+y (x wing) 0 | straight | yes | 2215 | 3.7% | 2215 | 3.7% |
| straight +x+y (x wing) 1 | straight | yes | 1804 | 3.0% | 1699 | 2.8% |
| straight +x+y (x wing) 2 | straight | yes | 1538 | 2.6% | 1526 | 2.5% |
| straight +x+y (x wing) 3 | straight | yes | 1152 | 1.9% | 1149 | 1.9% |
| straight +x+y (x wing) 4 | straight | yes | 630 | 1.0% | 607 | 1.0% |
| corner +x+y | corner | yes | 1975 | 3.3% | 697 | 1.2% |
| straight -x+y (y wing) 0 | straight | yes | 2223 | 3.7% | 2223 | 3.7% |
| straight -x+y (y wing) 1 | straight | yes | 1789 | 3.0% | 1676 | 2.8% |
| straight -x+y (y wing) 2 | straight | yes | 1538 | 2.6% | 1523 | 2.5% |
| straight -x+y (y wing) 3 | straight | yes | 1248 | 2.1% | 1246 | 2.1% |
| straight -x+y (y wing) 4 | straight | yes | 503 | 0.8% | 499 | 0.8% |
| straight -x+y (x wing) 0 | straight | yes | 2217 | 3.7% | 2217 | 3.7% |
| straight -x+y (x wing) 1 | straight | yes | 1785 | 3.0% | 1691 | 2.8% |
| straight -x+y (x wing) 2 | straight | yes | 1557 | 2.6% | 1530 | 2.5% |
| straight -x+y (x wing) 3 | straight | yes | 1249 | 2.1% | 1246 | 2.1% |
| straight -x+y (x wing) 4 | straight | yes | 618 | 1.0% | 591 | 1.0% |
| corner -x+y | corner | yes | 2013 | 3.3% | 639 | 1.1% |
| straight -x-y (y wing) 0 | straight | yes | 2168 | 3.6% | 2168 | 3.6% |
| straight -x-y (y wing) 1 | straight | yes | 1824 | 3.0% | 1701 | 2.8% |
| straight -x-y (y wing) 2 | straight | yes | 1550 | 2.6% | 1527 | 2.5% |
| straight -x-y (y wing) 3 | straight | yes | 1065 | 1.8% | 1045 | 1.7% |
| straight -x-y (y wing) 4 | straight | yes | 698 | 1.2% | 673 | 1.1% |
| straight -x-y (x wing) 0 | straight | yes | 2180 | 3.6% | 2180 | 3.6% |
| straight -x-y (x wing) 1 | straight | yes | 1814 | 3.0% | 1698 | 2.8% |
| straight -x-y (x wing) 2 | straight | yes | 1534 | 2.5% | 1506 | 2.5% |
| straight -x-y (x wing) 3 | straight | yes | 1067 | 1.8% | 1054 | 1.7% |
| straight -x-y (x wing) 4 | straight | yes | 689 | 1.1% | 672 | 1.1% |
| corner -x-y | corner | yes | 2063 | 3.4% | 815 | 1.4% |
| straight +x-y (y wing) 0 | straight | yes | 2217 | 3.7% | 2217 | 3.7% |
| straight +x-y (y wing) 1 | straight | yes | 1783 | 3.0% | 1697 | 2.8% |
| straight +x-y (y wing) 2 | straight | yes | 1524 | 2.5% | 1508 | 2.5% |
| straight +x-y (y wing) 3 | straight | yes | 1115 | 1.9% | 1109 | 1.8% |
| straight +x-y (y wing) 4 | straight | yes | 681 | 1.1% | 659 | 1.1% |
| straight +x-y (x wing) 0 | straight | yes | 2222 | 3.7% | 2222 | 3.7% |
| straight +x-y (x wing) 1 | straight | yes | 1819 | 3.0% | 1711 | 2.8% |
| straight +x-y (x wing) 2 | straight | yes | 1530 | 2.5% | 1513 | 2.5% |
| straight +x-y (x wing) 3 | straight | yes | 1133 | 1.9% | 1126 | 1.9% |
| straight +x-y (x wing) 4 | straight | yes | 624 | 1.0% | 607 | 1.0% |
| corner +x-y | corner | yes | 2047 | 3.4% | 739 | 1.2% |
| **straight (40)** | | | 58569 | | 57363 | 95.2% |
| **corner (4)** | | | 8098 | | 2890 | 4.8% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 1771 | 70.5 | 870.5 | 0.28 | 0.31 | 0.0% |
| -x | 1762 | 70.5 | 862.3 | 0.28 | 0.32 | 0.0% |
| +y | 1776 | 70.5 | 875.1 | 0.28 | 0.32 | 0.0% |
| -y | 1761 | 70.5 | 866.0 | 0.28 | 0.32 | 0.0% |
| door +x+y (y wall) 0 | 1509 | 4.9 | 960.1 | 0.49 | 0.69 | 0.0% |
| door +x+y (y wall) 1 | 1687 | 4.9 | 1094.0 | 0.48 | 0.66 | 0.0% |
| door +x+y (y wall) 2 | 1502 | 4.9 | 1123.6 | 0.42 | 0.69 | 0.0% |
| door +x+y (y wall) 3 | 1129 | 4.9 | 1126.2 | 0.31 | 0.66 | 0.0% |
| door +x+y (y wall) 4 | 584 | 4.9 | 1122.6 | 0.16 | 0.66 | 0.0% |
| door +x+y (x wall) 0 | 1506 | 5.1 | 952.2 | 0.50 | 0.69 | 0.0% |
| door +x+y (x wall) 1 | 1684 | 4.9 | 1078.1 | 0.49 | 0.69 | 0.0% |
| door +x+y (x wall) 2 | 1499 | 4.9 | 1096.0 | 0.43 | 0.69 | 0.0% |
| door +x+y (x wall) 3 | 1161 | 4.9 | 1126.0 | 0.32 | 0.72 | 0.0% |
| door +x+y (x wall) 4 | 622 | 5.1 | 1105.9 | 0.18 | 0.69 | 0.0% |
| door +x+y (corner) | 380 | 6.3 | 956.0 | 0.12 | 0.66 | 0.0% |
| door -x+y (y wall) 0 | 1512 | 4.9 | 926.0 | 0.51 | 0.72 | 0.0% |
| door -x+y (y wall) 1 | 1655 | 4.9 | 1102.3 | 0.47 | 0.69 | 0.0% |
| door -x+y (y wall) 2 | 1527 | 4.9 | 1099.1 | 0.44 | 0.66 | 0.0% |
| door -x+y (y wall) 3 | 1223 | 4.9 | 1102.3 | 0.35 | 0.69 | 0.0% |
| door -x+y (y wall) 4 | 522 | 5.1 | 1034.2 | 0.16 | 0.69 | 0.0% |
| door -x+y (x wall) 0 | 1501 | 4.9 | 948.0 | 0.50 | 0.72 | 0.0% |
| door -x+y (x wall) 1 | 1672 | 4.9 | 1083.2 | 0.48 | 0.66 | 0.0% |
| door -x+y (x wall) 2 | 1527 | 4.9 | 1099.8 | 0.44 | 0.72 | 0.0% |
| door -x+y (x wall) 3 | 1249 | 4.9 | 1096.3 | 0.36 | 0.69 | 0.0% |
| door -x+y (x wall) 4 | 591 | 4.9 | 1046.6 | 0.18 | 0.66 | 0.0% |
| door -x+y (corner) | 325 | 6.3 | 807.0 | 0.13 | 0.66 | 0.0% |
| door -x-y (y wall) 0 | 1487 | 4.9 | 974.1 | 0.48 | 0.72 | 0.0% |
| door -x-y (y wall) 1 | 1688 | 4.9 | 1072.7 | 0.49 | 0.69 | 0.0% |
| door -x-y (y wall) 2 | 1481 | 4.9 | 1108.4 | 0.42 | 0.72 | 0.0% |
| door -x-y (y wall) 3 | 1073 | 4.9 | 1066.9 | 0.32 | 0.72 | 0.0% |
| door -x-y (y wall) 4 | 691 | 4.9 | 1077.6 | 0.20 | 0.72 | 0.0% |
| door -x-y (x wall) 0 | 1480 | 4.9 | 968.6 | 0.48 | 0.66 | 0.0% |
| door -x-y (x wall) 1 | 1683 | 4.9 | 1092.3 | 0.48 | 0.69 | 0.0% |
| door -x-y (x wall) 2 | 1439 | 4.9 | 1104.2 | 0.41 | 0.66 | 0.0% |
| door -x-y (x wall) 3 | 1084 | 4.9 | 1091.2 | 0.31 | 0.66 | 0.0% |
| door -x-y (x wall) 4 | 710 | 5.1 | 1089.7 | 0.20 | 0.69 | 0.0% |
| door -x-y (corner) | 454 | 6.3 | 1039.6 | 0.14 | 0.69 | 0.0% |
| door +x-y (y wall) 0 | 1484 | 4.9 | 941.7 | 0.49 | 0.72 | 0.0% |
| door +x-y (y wall) 1 | 1686 | 4.9 | 1073.1 | 0.49 | 0.69 | 0.0% |
| door +x-y (y wall) 2 | 1476 | 4.9 | 1104.7 | 0.42 | 0.69 | 0.0% |
| door +x-y (y wall) 3 | 1081 | 4.9 | 1109.8 | 0.31 | 0.69 | 0.0% |
| door +x-y (y wall) 4 | 719 | 5.1 | 1104.9 | 0.20 | 0.66 | 0.0% |
| door +x-y (x wall) 0 | 1503 | 4.9 | 946.8 | 0.50 | 0.69 | 0.0% |
| door +x-y (x wall) 1 | 1697 | 4.9 | 1114.0 | 0.48 | 0.72 | 0.0% |
| door +x-y (x wall) 2 | 1467 | 4.9 | 1078.5 | 0.43 | 0.66 | 0.0% |
| door +x-y (x wall) 3 | 1121 | 4.9 | 1110.0 | 0.32 | 0.69 | 0.0% |
| door +x-y (x wall) 4 | 659 | 5.1 | 1082.3 | 0.19 | 0.72 | 0.0% |
| door +x-y (corner) | 453 | 6.5 | 784.5 | 0.18 | 0.69 | 0.0% |

Mean flow / w J averaged over the doors 0.36, over the avenues 0.28.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 103.1 | 2205 | 1483 / 721 / 816 | 0.7 | 837.8 | 3.61 | 6.02 | 88% | 86% | 2% | 4.51 |
| straight +x+y (y wing) 1 | 1.20 | 81.5 | 1774 | 1713 / 0 / 237 | 0.7 | 1091.1 | 1.79 | 4.11 | 89% | 69% | 20% | 3.62 |
| straight +x+y (y wing) 2 | 1.20 | 61.0 | 1444 | 1526 / 0 / 17 | 0.7 | 1120.6 | 1.38 | 2.21 | 75% | 62% | 13% | 3.79 |
| straight +x+y (y wing) 3 | 1.20 | 39.4 | 890 | 1151 / 0 / 18 | 0.7 | 1123.3 | 1.04 | 2.51 | 49% | 38% | 11% | 3.66 |
| straight +x+y (y wing) 4 | 1.20 | 18.8 | 377 | 538 / 0 / 13 | 0.7 | 1119.6 | 0.49 | 2.21 | 19% | 15% | 4% | 3.57 |
| straight +x+y (x wing) 0 | 1.20 | 103.1 | 2215 | 1491 / 725 / 875 | 0.7 | 862.6 | 3.59 | 5.82 | 90% | 85% | 5% | 4.50 |
| straight +x+y (x wing) 1 | 1.20 | 81.5 | 1785 | 1699 / 0 / 221 | 0.7 | 1075.2 | 1.79 | 3.61 | 91% | 73% | 18% | 3.75 |
| straight +x+y (x wing) 2 | 1.20 | 61.0 | 1426 | 1526 / 0 / 12 | 0.7 | 1093.0 | 1.41 | 2.31 | 75% | 64% | 11% | 3.88 |
| straight +x+y (x wing) 3 | 1.20 | 39.4 | 874 | 1149 / 0 / 11 | 0.7 | 1123.1 | 1.03 | 2.31 | 50% | 36% | 14% | 3.43 |
| straight +x+y (x wing) 4 | 1.20 | 18.8 | 359 | 607 / 0 / 31 | 0.7 | 1103.0 | 0.58 | 2.31 | 18% | 15% | 3% | 3.74 |
| corner +x+y | 1.20 | 186.0 | 1676 | 380 / 317 / 1362 | 0.7 | 1095.6 | 1.88 | 4.01 | 93% | 66% | 26% | 2.72 |
| straight -x+y (y wing) 0 | 1.20 | 103.1 | 2223 | 1495 / 728 / 1009 | 0.7 | 866.7 | 3.73 | 6.32 | 89% | 85% | 3% | 4.56 |
| straight -x+y (y wing) 1 | 1.20 | 81.5 | 1775 | 1676 / 0 / 225 | 0.7 | 1099.3 | 1.73 | 3.61 | 86% | 70% | 16% | 3.66 |
| straight -x+y (y wing) 2 | 1.20 | 61.0 | 1423 | 1523 / 0 / 24 | 0.7 | 1096.1 | 1.41 | 2.21 | 69% | 62% | 7% | 4.02 |
| straight -x+y (y wing) 3 | 1.20 | 39.4 | 902 | 1246 / 0 / 7 | 0.7 | 1099.3 | 1.14 | 2.21 | 64% | 40% | 24% | 3.10 |
| straight -x+y (y wing) 4 | 1.20 | 18.8 | 361 | 499 / 0 / 16 | 0.7 | 1031.2 | 0.50 | 2.11 | 39% | 16% | 23% | 2.08 |
| straight -x+y (x wing) 0 | 1.20 | 103.1 | 2217 | 1482 / 735 / 870 | 0.7 | 858.6 | 3.60 | 6.22 | 89% | 84% | 5% | 4.63 |
| straight -x+y (x wing) 1 | 1.20 | 81.5 | 1762 | 1691 / 0 / 199 | 0.7 | 1080.2 | 1.75 | 3.51 | 87% | 72% | 16% | 3.85 |
| straight -x+y (x wing) 2 | 1.20 | 61.0 | 1463 | 1530 / 0 / 30 | 0.7 | 1096.8 | 1.42 | 2.21 | 71% | 62% | 9% | 3.97 |
| straight -x+y (x wing) 3 | 1.20 | 39.4 | 888 | 1246 / 0 / 8 | 0.7 | 1093.3 | 1.15 | 2.51 | 55% | 39% | 16% | 3.40 |
| straight -x+y (x wing) 4 | 1.20 | 18.8 | 389 | 591 / 0 / 33 | 0.7 | 1043.7 | 0.60 | 2.51 | 17% | 17% | 0% | 4.14 |
| corner -x+y | 1.20 | 186.0 | 1678 | 325 / 314 / 1442 | 0.7 | 1049.1 | 1.98 | 5.22 | 92% | 70% | 22% | 2.90 |
| straight -x-y (y wing) 0 | 1.20 | 103.1 | 2168 | 1474 / 694 / 800 | 0.7 | 851.1 | 3.49 | 5.72 | 90% | 85% | 5% | 4.57 |
| straight -x-y (y wing) 1 | 1.20 | 81.5 | 1810 | 1701 / 0 / 252 | 0.7 | 1069.7 | 1.83 | 3.51 | 89% | 73% | 16% | 3.63 |
| straight -x-y (y wing) 2 | 1.20 | 61.0 | 1432 | 1527 / 0 / 28 | 0.7 | 1105.4 | 1.41 | 2.21 | 75% | 65% | 10% | 3.82 |
| straight -x-y (y wing) 3 | 1.20 | 39.4 | 883 | 1045 / 0 / 32 | 0.7 | 1064.0 | 1.01 | 2.21 | 48% | 42% | 6% | 3.74 |
| straight -x-y (y wing) 4 | 1.20 | 18.8 | 376 | 673 / 0 / 29 | 0.7 | 1074.6 | 0.65 | 2.21 | 19% | 16% | 3% | 3.77 |
| straight -x-y (x wing) 0 | 1.20 | 103.1 | 2180 | 1466 / 714 / 900 | 0.7 | 844.6 | 3.65 | 6.72 | 89% | 86% | 4% | 4.56 |
| straight -x-y (x wing) 1 | 1.20 | 81.5 | 1788 | 1698 / 0 / 365 | 0.7 | 1089.3 | 1.89 | 3.61 | 87% | 70% | 17% | 3.60 |
| straight -x-y (x wing) 2 | 1.20 | 61.0 | 1456 | 1506 / 0 / 34 | 0.7 | 1101.2 | 1.40 | 2.51 | 77% | 67% | 10% | 3.86 |
| straight -x-y (x wing) 3 | 1.20 | 39.4 | 876 | 1054 / 0 / 23 | 0.7 | 1088.3 | 0.99 | 2.21 | 43% | 38% | 5% | 4.04 |
| straight -x-y (x wing) 4 | 1.20 | 18.8 | 387 | 672 / 0 / 21 | 0.7 | 1086.7 | 0.64 | 2.11 | 17% | 17% | 0% | 4.09 |
| corner -x-y | 1.20 | 186.0 | 1683 | 454 / 361 / 1427 | 0.7 | 1062.7 | 2.11 | 4.41 | 93% | 62% | 32% | 2.63 |
| straight +x-y (y wing) 0 | 1.20 | 103.1 | 2217 | 1473 / 744 / 929 | 0.7 | 849.5 | 3.71 | 5.82 | 90% | 84% | 6% | 4.54 |
| straight +x-y (y wing) 1 | 1.20 | 81.5 | 1752 | 1697 / 0 / 185 | 0.7 | 1070.1 | 1.76 | 3.71 | 89% | 74% | 15% | 3.87 |
| straight +x-y (y wing) 2 | 1.20 | 61.0 | 1442 | 1508 / 0 / 23 | 0.7 | 1101.7 | 1.39 | 2.41 | 76% | 64% | 12% | 3.77 |
| straight +x-y (y wing) 3 | 1.20 | 39.4 | 882 | 1109 / 0 / 12 | 0.7 | 1106.8 | 1.01 | 2.21 | 46% | 39% | 7% | 3.68 |
| straight +x-y (y wing) 4 | 1.20 | 18.8 | 358 | 659 / 0 / 25 | 0.7 | 1101.9 | 0.62 | 2.31 | 15% | 15% | 0% | 4.18 |
| straight +x-y (x wing) 0 | 1.20 | 103.1 | 2222 | 1490 / 733 / 776 | 0.7 | 857.0 | 3.50 | 5.52 | 90% | 86% | 3% | 4.54 |
| straight +x-y (x wing) 1 | 1.20 | 81.5 | 1801 | 1711 / 0 / 201 | 0.7 | 1111.0 | 1.72 | 3.71 | 86% | 72% | 13% | 3.98 |
| straight +x-y (x wing) 2 | 1.20 | 61.0 | 1428 | 1513 / 0 / 17 | 0.7 | 1075.5 | 1.42 | 2.21 | 75% | 64% | 11% | 3.91 |
| straight +x-y (x wing) 3 | 1.20 | 39.4 | 887 | 1126 / 0 / 11 | 0.7 | 1107.0 | 1.03 | 2.31 | 47% | 41% | 6% | 3.71 |
| straight +x-y (x wing) 4 | 1.20 | 18.8 | 362 | 607 / 0 / 18 | 0.7 | 1079.3 | 0.58 | 2.21 | 17% | 17% | 0% | 3.91 |
| corner +x-y | 1.20 | 186.0 | 1757 | 453 / 286 / 1375 | 0.7 | 1078.0 | 1.96 | 4.71 | 90% | 64% | 26% | 2.73 |

The last agent out (agent 8309, t100 1126.2 s): last gangway straight +x+y (y wing) 3, exit door +x+y (y wall) 3. The gangway that cleared last: straight +x+y (y wing) 3 at 1123.3 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 8804 | 7800.4 | 6.93 | 1124.0 / 1061.2 / 986.5 | 1037.2 / 1025.1 / 962.5 | 5008599.5 | 10300663 | 0.202 |
| gangway | 3792 | 3512.9 | 6.93 | 1121.9 / 1061.2 / 986.5 | 1037.2 / 1025.1 / 962.5 | 5008599.5 | 9598220 | 0.131 |
| walkway | 276 | 257.4 | 3.90 | 570.7 / 371.9 / 0.0 | 390.4 / 195.5 / 0.0 | 0.0 | 74286 | 0.670 |
| avenue | 1920 | 1801.4 | 2.04 | 752.6 / 0.0 / 0.0 | 531.7 / 0.0 / 0.0 | 0.0 | 423736 | 1.334 |
| exit | 4 | 2.0 | 0.00 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 0 | - |
| concourse | 2812 | 2226.8 | 3.08 | 1114.5 / 72.6 / 0.0 | 932.6 / 20.1 / 0.0 | 0.0 | 204421 | 1.044 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 25392 | 16030.4 | 7.71 | 1024.4 / 1019.0 / 969.3 | 1021.1 / 1011.8 / 965.5 | 5727470.9 | 14875010 | 0.032 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 208 x 208 from (-104, -104) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 34.5 | -34.5 | gangway | 1.00 | 5.87 | 1002.9 | 990.5 | 926.1 | 5240.0 | 0.011 |
| 2 | -35.5 | -35.5 | gangway | 1.00 | 5.80 | 997.8 | 996.3 | 948.2 | 5223.8 | 0.010 |
| 3 | 35.5 | -35.5 | gangway | 1.00 | 5.81 | 1005.2 | 995.2 | 918.1 | 5152.4 | 0.012 |
| 4 | 34.5 | 34.5 | gangway | 1.00 | 5.56 | 1006.8 | 998.7 | 947.1 | 5151.7 | 0.009 |
| 5 | 38.5 | 38.5 | gangway | 1.00 | 5.91 | 1029.2 | 1024.4 | 907.8 | 5104.2 | 0.017 |
| 6 | 33.5 | -33.5 | gangway | 0.99 | 5.84 | 992.6 | 985.8 | 935.6 | 5063.2 | 0.007 |
| 7 | -36.5 | -36.5 | gangway | 1.00 | 5.82 | 1003.4 | 1001.5 | 945.2 | 5037.0 | 0.012 |
| 8 | 36.5 | -36.5 | gangway | 1.00 | 5.58 | 1009.0 | 1004.5 | 934.7 | 5022.0 | 0.014 |
| 9 | 35.5 | 35.5 | gangway | 1.00 | 5.57 | 1013.9 | 1011.0 | 949.9 | 4989.2 | 0.010 |
| 10 | -34.5 | -34.5 | gangway | 1.00 | 5.81 | 994.0 | 980.5 | 909.9 | 4977.5 | 0.009 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 38.5 | 36.5 | seat row | 0.50 | 7.43 | 973.9 | 973.2 | 961.8 | 3452.5 | 0.005 |
| 2 | 36.5 | 38.5 | seat row | 0.50 | 7.25 | 1021.1 | 1011.8 | 965.5 | 3360.3 | 0.008 |
| 3 | -36.5 | 38.5 | seat row | 0.50 | 7.35 | 956.2 | 951.1 | 934.5 | 3310.3 | 0.007 |
| 4 | -38.5 | -36.5 | seat row | 0.50 | 7.22 | 968.3 | 966.0 | 946.8 | 3306.4 | 0.006 |
| 5 | 35.5 | 38.5 | seat row | 0.50 | 7.11 | 991.0 | 982.6 | 954.5 | 3301.1 | 0.007 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 7818; agent-steps of seated agents on another row's clearway: 1852936.

## Deposit check

Person-seconds deposited: 25181246.8, of them in excluded cells: 5573.645.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 5183829 overlapping pair-steps: p99 0.0028, max 0.0992 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0028 max 0.0992; venue-geometry 14: p99 0.0018 max 0.0018 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00766 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 50 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.47 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 3690 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
