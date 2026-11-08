# Experiment `L_load95_s2`

**Task 5.8 stage 2: venue L, 95% load (seed 2), default model**

Venue L (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (4000 x 4000), cache key a2f3aaf59c2252b7, content hash 022d17b202313d70). 60253 agents on 95% of the 63424 seats (spawnSeatedCrowd, seed 2), buffer N = 65536, 6700 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 8433122 evaluations, 483648 switches, 0 forced choices).
Capacity: **within design capacity** (the L venue's design capacity 63424, jam capacity 171923: 23822.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `cd8e0bbf3411846ca7aa6719887d122a142a7ca1`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-15T17:02:57, 577.0 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 2254 | 394.2 |
| t90 | 4516 | 789.9 |
| t100 | 6700 | 1171.9 |

t_p: the step by which ceil(p x 60253) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 1757 | 0 | 70.3 | 885.6 | 22.8 | 25.5 | 79.2-89.2 |
| -x | 5.66 | 1766 | 0 | 70.5 | 863.7 | 23.6 | 26.6 | 92.4-102.3 |
| +y | 5.66 | 1754 | 0 | 70.5 | 863.0 | 23.5 | 26.6 | 159.0-169.0 |
| -y | 5.66 | 1776 | 0 | 70.5 | 871.7 | 23.5 | 26.6 | 83.1-93.1 |
| door +x+y (y wall) 0 | 2.30 | 1484 | 2446 | 4.9 | 972.0 | 40.0 | 57.6 | 16.3-26.2 |
| door +x+y (y wall) 1 | 2.30 | 1701 | 2033 | 4.9 | 1124.0 | 39.6 | 57.6 | 15.0-25.0 |
| door +x+y (y wall) 2 | 2.30 | 1463 | 1513 | 4.9 | 1092.6 | 35.1 | 54.9 | 20.6-30.6 |
| door +x+y (y wall) 3 | 2.30 | 1072 | 988 | 4.9 | 1111.5 | 25.3 | 54.9 | 6.8-16.8 |
| door +x+y (y wall) 4 | 2.30 | 700 | 488 | 4.9 | 1027.2 | 17.9 | 54.9 | 7.3-17.3 |
| door +x+y (x wall) 0 | 2.30 | 1485 | 2451 | 5.1 | 949.9 | 41.0 | 54.9 | 12.4-22.4 |
| door +x+y (x wall) 1 | 2.30 | 1687 | 2018 | 4.9 | 1115.4 | 39.6 | 54.9 | 28.0-38.0 |
| door +x+y (x wall) 2 | 2.30 | 1460 | 1527 | 4.9 | 1106.8 | 34.6 | 57.6 | 24.3-34.3 |
| door +x+y (x wall) 3 | 2.30 | 1071 | 997 | 4.7 | 1111.5 | 25.2 | 54.9 | 8.2-18.2 |
| door +x+y (x wall) 4 | 2.30 | 751 | 483 | 5.1 | 1093.9 | 18.0 | 57.6 | 22.9-32.9 |
| door +x+y (corner) | 2.30 | 465 | 120 | 6.3 | 956.0 | 12.8 | 57.6 | 106.7-116.7 |
| door -x+y (y wall) 0 | 2.30 | 1500 | 2456 | 4.9 | 947.8 | 41.5 | 54.9 | 10.5-20.5 |
| door -x+y (y wall) 1 | 2.30 | 1688 | 2023 | 4.9 | 1109.1 | 39.9 | 60.2 | 11.5-21.5 |
| door -x+y (y wall) 2 | 2.30 | 1473 | 1517 | 4.9 | 1085.1 | 35.6 | 54.9 | 22.9-32.9 |
| door -x+y (y wall) 3 | 2.30 | 1082 | 1003 | 4.9 | 1107.7 | 25.6 | 60.2 | 724.6-734.6 |
| door -x+y (y wall) 4 | 2.30 | 694 | 490 | 5.1 | 1111.5 | 16.4 | 57.6 | 7.3-17.3 |
| door -x+y (x wall) 0 | 2.30 | 1493 | 2457 | 4.9 | 961.6 | 40.7 | 57.6 | 14.5-24.5 |
| door -x+y (x wall) 1 | 2.30 | 1687 | 2016 | 4.9 | 1083.5 | 40.8 | 54.9 | 13.3-23.3 |
| door -x+y (x wall) 2 | 2.30 | 1447 | 1499 | 4.9 | 1097.5 | 34.5 | 54.9 | 10.0-19.9 |
| door -x+y (x wall) 3 | 2.30 | 1095 | 995 | 4.9 | 1093.3 | 26.2 | 57.6 | 18.9-28.9 |
| door -x+y (x wall) 4 | 2.30 | 717 | 493 | 4.9 | 1110.7 | 16.9 | 57.6 | 7.3-17.3 |
| door -x+y (corner) | 2.30 | 440 | 119 | 6.3 | 958.5 | 12.1 | 57.6 | 134.3-144.3 |
| door -x-y (y wall) 0 | 2.30 | 1506 | 2459 | 4.9 | 947.6 | 41.7 | 57.6 | 12.8-22.7 |
| door -x-y (y wall) 1 | 2.30 | 1688 | 2034 | 4.9 | 1087.4 | 40.7 | 60.2 | 18.7-28.7 |
| door -x-y (y wall) 2 | 2.30 | 1498 | 1513 | 4.9 | 1171.9 | 33.5 | 57.6 | 643.8-653.8 |
| door -x-y (y wall) 3 | 2.30 | 1179 | 986 | 4.9 | 1171.7 | 26.4 | 54.9 | 11.9-21.9 |
| door -x-y (y wall) 4 | 2.30 | 614 | 485 | 4.9 | 1123.6 | 14.3 | 54.9 | 7.7-17.7 |
| door -x-y (x wall) 0 | 2.30 | 1490 | 2445 | 4.9 | 997.7 | 39.1 | 60.2 | 24.5-34.5 |
| door -x-y (x wall) 1 | 2.30 | 1699 | 2040 | 4.9 | 1100.7 | 40.4 | 57.6 | 431.7-441.6 |
| door -x-y (x wall) 2 | 2.30 | 1520 | 1501 | 4.9 | 1156.8 | 34.4 | 60.2 | 11.5-21.5 |
| door -x-y (x wall) 3 | 2.30 | 1103 | 983 | 4.9 | 1170.1 | 24.7 | 57.6 | 10.7-20.6 |
| door -x-y (x wall) 4 | 2.30 | 605 | 489 | 5.1 | 1139.5 | 13.9 | 57.6 | 7.3-17.3 |
| door -x-y (corner) | 2.30 | 369 | 118 | 6.3 | 850.0 | 11.4 | 57.6 | 92.5-102.5 |
| door +x-y (y wall) 0 | 2.30 | 1486 | 2456 | 5.1 | 944.3 | 41.3 | 57.6 | 5.9-15.9 |
| door +x-y (y wall) 1 | 2.30 | 1689 | 2038 | 4.9 | 1087.6 | 40.7 | 57.6 | 31.0-40.9 |
| door +x-y (y wall) 2 | 2.30 | 1490 | 1522 | 4.9 | 1147.2 | 34.0 | 57.6 | 642.6-652.6 |
| door +x-y (y wall) 3 | 2.30 | 1170 | 984 | 4.9 | 1099.3 | 27.9 | 54.9 | 7.0-17.0 |
| door +x-y (y wall) 4 | 2.30 | 613 | 487 | 5.1 | 1068.2 | 15.0 | 54.9 | 11.5-21.5 |
| door +x-y (x wall) 0 | 2.30 | 1503 | 2443 | 5.1 | 965.8 | 40.8 | 57.6 | 15.9-25.9 |
| door +x-y (x wall) 1 | 2.30 | 1677 | 2040 | 4.9 | 1086.7 | 40.4 | 57.6 | 25.2-35.2 |
| door +x-y (x wall) 2 | 2.30 | 1468 | 1499 | 4.9 | 1115.4 | 34.5 | 57.6 | 30.3-40.2 |
| door +x-y (x wall) 3 | 2.30 | 1121 | 989 | 4.9 | 1132.5 | 25.9 | 60.2 | 18.5-28.5 |
| door +x-y (x wall) 4 | 2.30 | 647 | 494 | 5.1 | 1125.2 | 15.1 | 57.6 | 8.0-18.0 |
| door +x-y (corner) | 2.30 | 410 | 116 | 6.5 | 981.4 | 11.0 | 54.9 | 72.1-82.0 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (2.30 m; a corner door's: the gap between its wall ends, 2.30 m); agents are removed past the outer wall's outer face (92.71 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 1757 | 2.9% | 19.0% |
| -x | avenue | 5.66 | 1766 | 2.9% | 19.1% |
| +y | avenue | 5.66 | 1754 | 2.9% | 19.0% |
| -y | avenue | 5.66 | 1776 | 2.9% | 19.2% |
| door +x+y (y wall) 0 | door | 2.30 | 1484 | 2.5% | 39.5% |
| door +x+y (y wall) 1 | door | 2.30 | 1701 | 2.8% | 45.3% |
| door +x+y (y wall) 2 | door | 2.30 | 1463 | 2.4% | 39.0% |
| door +x+y (y wall) 3 | door | 2.30 | 1072 | 1.8% | 28.5% |
| door +x+y (y wall) 4 | door | 2.30 | 700 | 1.2% | 18.6% |
| door +x+y (x wall) 0 | door | 2.30 | 1485 | 2.5% | 39.5% |
| door +x+y (x wall) 1 | door | 2.30 | 1687 | 2.8% | 44.9% |
| door +x+y (x wall) 2 | door | 2.30 | 1460 | 2.4% | 38.9% |
| door +x+y (x wall) 3 | door | 2.30 | 1071 | 1.8% | 28.5% |
| door +x+y (x wall) 4 | door | 2.30 | 751 | 1.2% | 20.0% |
| door +x+y (corner) | door | 2.30 | 465 | 0.8% | 12.4% |
| door -x+y (y wall) 0 | door | 2.30 | 1500 | 2.5% | 39.9% |
| door -x+y (y wall) 1 | door | 2.30 | 1688 | 2.8% | 44.9% |
| door -x+y (y wall) 2 | door | 2.30 | 1473 | 2.4% | 39.2% |
| door -x+y (y wall) 3 | door | 2.30 | 1082 | 1.8% | 28.8% |
| door -x+y (y wall) 4 | door | 2.30 | 694 | 1.2% | 18.5% |
| door -x+y (x wall) 0 | door | 2.30 | 1493 | 2.5% | 39.8% |
| door -x+y (x wall) 1 | door | 2.30 | 1687 | 2.8% | 44.9% |
| door -x+y (x wall) 2 | door | 2.30 | 1447 | 2.4% | 38.5% |
| door -x+y (x wall) 3 | door | 2.30 | 1095 | 1.8% | 29.2% |
| door -x+y (x wall) 4 | door | 2.30 | 717 | 1.2% | 19.1% |
| door -x+y (corner) | door | 2.30 | 440 | 0.7% | 11.7% |
| door -x-y (y wall) 0 | door | 2.30 | 1506 | 2.5% | 40.1% |
| door -x-y (y wall) 1 | door | 2.30 | 1688 | 2.8% | 44.9% |
| door -x-y (y wall) 2 | door | 2.30 | 1498 | 2.5% | 39.9% |
| door -x-y (y wall) 3 | door | 2.30 | 1179 | 2.0% | 31.4% |
| door -x-y (y wall) 4 | door | 2.30 | 614 | 1.0% | 16.3% |
| door -x-y (x wall) 0 | door | 2.30 | 1490 | 2.5% | 39.7% |
| door -x-y (x wall) 1 | door | 2.30 | 1699 | 2.8% | 45.2% |
| door -x-y (x wall) 2 | door | 2.30 | 1520 | 2.5% | 40.5% |
| door -x-y (x wall) 3 | door | 2.30 | 1103 | 1.8% | 29.4% |
| door -x-y (x wall) 4 | door | 2.30 | 605 | 1.0% | 16.1% |
| door -x-y (corner) | door | 2.30 | 369 | 0.6% | 9.8% |
| door +x-y (y wall) 0 | door | 2.30 | 1486 | 2.5% | 39.6% |
| door +x-y (y wall) 1 | door | 2.30 | 1689 | 2.8% | 45.0% |
| door +x-y (y wall) 2 | door | 2.30 | 1490 | 2.5% | 39.7% |
| door +x-y (y wall) 3 | door | 2.30 | 1170 | 1.9% | 31.2% |
| door +x-y (y wall) 4 | door | 2.30 | 613 | 1.0% | 16.3% |
| door +x-y (x wall) 0 | door | 2.30 | 1503 | 2.5% | 40.0% |
| door +x-y (x wall) 1 | door | 2.30 | 1677 | 2.8% | 44.7% |
| door +x-y (x wall) 2 | door | 2.30 | 1468 | 2.4% | 39.1% |
| door +x-y (x wall) 3 | door | 2.30 | 1121 | 1.9% | 29.8% |
| door +x-y (x wall) 4 | door | 2.30 | 647 | 1.1% | 17.2% |
| door +x-y (corner) | door | 2.30 | 410 | 0.7% | 10.9% |
| **doors (44)** | door | 101.20 | 53200 | 88.3% | |
| **avenues (4)** | avenue | 22.64 | 7053 | 11.7% | |

**Unused exit width: 0.0 of 123.8 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 1171.9 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 29.8%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 2192 | 3.6% | 2192 | 3.6% |
| straight +x+y (y wing) 1 | straight | yes | 1801 | 3.0% | 1717 | 2.8% |
| straight +x+y (y wing) 2 | straight | yes | 1530 | 2.5% | 1507 | 2.5% |
| straight +x+y (y wing) 3 | straight | yes | 1090 | 1.8% | 1073 | 1.8% |
| straight +x+y (y wing) 4 | straight | yes | 669 | 1.1% | 655 | 1.1% |
| straight +x+y (x wing) 0 | straight | yes | 2208 | 3.7% | 2207 | 3.7% |
| straight +x+y (x wing) 1 | straight | yes | 1787 | 3.0% | 1707 | 2.8% |
| straight +x+y (x wing) 2 | straight | yes | 1550 | 2.6% | 1522 | 2.5% |
| straight +x+y (x wing) 3 | straight | yes | 1062 | 1.8% | 1046 | 1.7% |
| straight +x+y (x wing) 4 | straight | yes | 741 | 1.2% | 714 | 1.2% |
| corner +x+y | corner | yes | 2005 | 3.3% | 724 | 1.2% |
| straight -x+y (y wing) 0 | straight | yes | 2210 | 3.7% | 2210 | 3.7% |
| straight -x+y (y wing) 1 | straight | yes | 1786 | 3.0% | 1710 | 2.8% |
| straight -x+y (y wing) 2 | straight | yes | 1535 | 2.5% | 1513 | 2.5% |
| straight -x+y (y wing) 3 | straight | yes | 1108 | 1.8% | 1098 | 1.8% |
| straight -x+y (y wing) 4 | straight | yes | 649 | 1.1% | 638 | 1.1% |
| straight -x+y (x wing) 0 | straight | yes | 2213 | 3.7% | 2213 | 3.7% |
| straight -x+y (x wing) 1 | straight | yes | 1797 | 3.0% | 1705 | 2.8% |
| straight -x+y (x wing) 2 | straight | yes | 1495 | 2.5% | 1481 | 2.5% |
| straight -x+y (x wing) 3 | straight | yes | 1100 | 1.8% | 1091 | 1.8% |
| straight -x+y (x wing) 4 | straight | yes | 707 | 1.2% | 687 | 1.1% |
| corner -x+y | corner | yes | 1982 | 3.3% | 722 | 1.2% |
| straight -x-y (y wing) 0 | straight | yes | 2200 | 3.7% | 2200 | 3.7% |
| straight -x-y (y wing) 1 | straight | yes | 1817 | 3.0% | 1708 | 2.8% |
| straight -x-y (y wing) 2 | straight | yes | 1558 | 2.6% | 1542 | 2.6% |
| straight -x-y (y wing) 3 | straight | yes | 1155 | 1.9% | 1149 | 1.9% |
| straight -x-y (y wing) 4 | straight | yes | 624 | 1.0% | 600 | 1.0% |
| straight -x-y (x wing) 0 | straight | yes | 2214 | 3.7% | 2214 | 3.7% |
| straight -x-y (x wing) 1 | straight | yes | 1812 | 3.0% | 1716 | 2.8% |
| straight -x-y (x wing) 2 | straight | yes | 1557 | 2.6% | 1549 | 2.6% |
| straight -x-y (x wing) 3 | straight | yes | 1096 | 1.8% | 1090 | 1.8% |
| straight -x-y (x wing) 4 | straight | yes | 612 | 1.0% | 589 | 1.0% |
| corner -x-y | corner | yes | 1972 | 3.3% | 696 | 1.2% |
| straight +x-y (y wing) 0 | straight | yes | 2221 | 3.7% | 2221 | 3.7% |
| straight +x-y (y wing) 1 | straight | yes | 1802 | 3.0% | 1705 | 2.8% |
| straight +x-y (y wing) 2 | straight | yes | 1551 | 2.6% | 1533 | 2.5% |
| straight +x-y (y wing) 3 | straight | yes | 1134 | 1.9% | 1131 | 1.9% |
| straight +x-y (y wing) 4 | straight | yes | 618 | 1.0% | 608 | 1.0% |
| straight +x-y (x wing) 0 | straight | yes | 2206 | 3.7% | 2206 | 3.7% |
| straight +x-y (x wing) 1 | straight | yes | 1809 | 3.0% | 1695 | 2.8% |
| straight +x-y (x wing) 2 | straight | yes | 1523 | 2.5% | 1504 | 2.5% |
| straight +x-y (x wing) 3 | straight | yes | 1106 | 1.8% | 1102 | 1.8% |
| straight +x-y (x wing) 4 | straight | yes | 649 | 1.1% | 621 | 1.0% |
| corner +x-y | corner | yes | 1976 | 3.3% | 742 | 1.2% |
| **straight (40)** | | | 58494 | | 57369 | 95.2% |
| **corner (4)** | | | 7935 | | 2884 | 4.8% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 1757 | 70.3 | 885.6 | 0.27 | 0.31 | 0.0% |
| -x | 1766 | 70.5 | 863.7 | 0.28 | 0.32 | 0.0% |
| +y | 1754 | 70.5 | 863.0 | 0.28 | 0.32 | 0.0% |
| -y | 1776 | 70.5 | 871.7 | 0.28 | 0.32 | 0.0% |
| door +x+y (y wall) 0 | 1484 | 4.9 | 972.0 | 0.48 | 0.69 | 0.0% |
| door +x+y (y wall) 1 | 1701 | 4.9 | 1124.0 | 0.47 | 0.69 | 0.0% |
| door +x+y (y wall) 2 | 1463 | 4.9 | 1092.6 | 0.42 | 0.66 | 0.0% |
| door +x+y (y wall) 3 | 1072 | 4.9 | 1111.5 | 0.30 | 0.66 | 0.0% |
| door +x+y (y wall) 4 | 700 | 4.9 | 1027.2 | 0.21 | 0.66 | 0.0% |
| door +x+y (x wall) 0 | 1485 | 5.1 | 949.9 | 0.49 | 0.66 | 0.0% |
| door +x+y (x wall) 1 | 1687 | 4.9 | 1115.4 | 0.47 | 0.66 | 0.0% |
| door +x+y (x wall) 2 | 1460 | 4.9 | 1106.8 | 0.41 | 0.69 | 0.0% |
| door +x+y (x wall) 3 | 1071 | 4.7 | 1111.5 | 0.30 | 0.66 | 0.0% |
| door +x+y (x wall) 4 | 751 | 5.1 | 1093.9 | 0.22 | 0.69 | 0.0% |
| door +x+y (corner) | 465 | 6.3 | 956.0 | 0.15 | 0.69 | 0.0% |
| door -x+y (y wall) 0 | 1500 | 4.9 | 947.8 | 0.50 | 0.66 | 0.0% |
| door -x+y (y wall) 1 | 1688 | 4.9 | 1109.1 | 0.48 | 0.72 | 0.0% |
| door -x+y (y wall) 2 | 1473 | 4.9 | 1085.1 | 0.43 | 0.66 | 0.0% |
| door -x+y (y wall) 3 | 1082 | 4.9 | 1107.7 | 0.31 | 0.72 | 0.0% |
| door -x+y (y wall) 4 | 694 | 5.1 | 1111.5 | 0.20 | 0.69 | 0.0% |
| door -x+y (x wall) 0 | 1493 | 4.9 | 961.6 | 0.49 | 0.69 | 0.0% |
| door -x+y (x wall) 1 | 1687 | 4.9 | 1083.5 | 0.49 | 0.66 | 0.0% |
| door -x+y (x wall) 2 | 1447 | 4.9 | 1097.5 | 0.41 | 0.66 | 0.0% |
| door -x+y (x wall) 3 | 1095 | 4.9 | 1093.3 | 0.31 | 0.69 | 0.0% |
| door -x+y (x wall) 4 | 717 | 4.9 | 1110.7 | 0.20 | 0.69 | 0.0% |
| door -x+y (corner) | 440 | 6.3 | 958.5 | 0.14 | 0.69 | 0.0% |
| door -x-y (y wall) 0 | 1506 | 4.9 | 947.6 | 0.50 | 0.69 | 0.0% |
| door -x-y (y wall) 1 | 1688 | 4.9 | 1087.4 | 0.49 | 0.72 | 0.0% |
| door -x-y (y wall) 2 | 1498 | 4.9 | 1171.9 | 0.40 | 0.69 | 0.0% |
| door -x-y (y wall) 3 | 1179 | 4.9 | 1171.7 | 0.32 | 0.66 | 0.0% |
| door -x-y (y wall) 4 | 614 | 4.9 | 1123.6 | 0.17 | 0.66 | 0.0% |
| door -x-y (x wall) 0 | 1490 | 4.9 | 997.7 | 0.47 | 0.72 | 0.0% |
| door -x-y (x wall) 1 | 1699 | 4.9 | 1100.7 | 0.48 | 0.69 | 0.0% |
| door -x-y (x wall) 2 | 1520 | 4.9 | 1156.8 | 0.41 | 0.72 | 0.0% |
| door -x-y (x wall) 3 | 1103 | 4.9 | 1170.1 | 0.30 | 0.69 | 0.0% |
| door -x-y (x wall) 4 | 605 | 5.1 | 1139.5 | 0.17 | 0.69 | 0.0% |
| door -x-y (corner) | 369 | 6.3 | 850.0 | 0.14 | 0.69 | 0.0% |
| door +x-y (y wall) 0 | 1486 | 5.1 | 944.3 | 0.49 | 0.69 | 0.0% |
| door +x-y (y wall) 1 | 1689 | 4.9 | 1087.6 | 0.49 | 0.69 | 0.0% |
| door +x-y (y wall) 2 | 1490 | 4.9 | 1147.2 | 0.41 | 0.69 | 0.0% |
| door +x-y (y wall) 3 | 1170 | 4.9 | 1099.3 | 0.33 | 0.66 | 0.0% |
| door +x-y (y wall) 4 | 613 | 5.1 | 1068.2 | 0.18 | 0.66 | 0.0% |
| door +x-y (x wall) 0 | 1503 | 5.1 | 965.8 | 0.49 | 0.69 | 0.0% |
| door +x-y (x wall) 1 | 1677 | 4.9 | 1086.7 | 0.48 | 0.69 | 0.0% |
| door +x-y (x wall) 2 | 1468 | 4.9 | 1115.4 | 0.41 | 0.69 | 0.0% |
| door +x-y (x wall) 3 | 1121 | 4.9 | 1132.5 | 0.31 | 0.72 | 0.0% |
| door +x-y (x wall) 4 | 647 | 5.1 | 1125.2 | 0.18 | 0.69 | 0.0% |
| door +x-y (corner) | 410 | 6.5 | 981.4 | 0.13 | 0.66 | 0.0% |

Mean flow / w J averaged over the doors 0.36, over the avenues 0.28.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 103.1 | 2192 | 1468 / 725 / 815 | 0.7 | 827.8 | 3.64 | 5.72 | 88% | 87% | 1% | 4.70 |
| straight +x+y (y wing) 1 | 1.20 | 81.5 | 1785 | 1717 / 0 / 179 | 0.7 | 1121.0 | 1.69 | 3.71 | 84% | 73% | 12% | 3.99 |
| straight +x+y (y wing) 2 | 1.20 | 61.0 | 1433 | 1507 / 0 / 30 | 0.7 | 1089.7 | 1.41 | 2.21 | 73% | 65% | 8% | 3.95 |
| straight +x+y (y wing) 3 | 1.20 | 39.4 | 894 | 1073 / 0 / 22 | 0.7 | 1108.6 | 0.99 | 2.31 | 49% | 38% | 11% | 3.54 |
| straight +x+y (y wing) 4 | 1.20 | 18.8 | 379 | 655 / 0 / 22 | 0.7 | 1024.3 | 0.66 | 2.11 | 19% | 17% | 2% | 4.00 |
| straight +x+y (x wing) 0 | 1.20 | 103.1 | 2208 | 1465 / 742 / 961 | 0.7 | 828.5 | 3.83 | 6.42 | 88% | 85% | 4% | 4.51 |
| straight +x+y (x wing) 1 | 1.20 | 81.5 | 1761 | 1707 / 0 / 163 | 0.7 | 1112.4 | 1.68 | 3.51 | 85% | 72% | 12% | 4.04 |
| straight +x+y (x wing) 2 | 1.20 | 61.0 | 1458 | 1522 / 0 / 33 | 0.7 | 1103.8 | 1.41 | 2.21 | 77% | 65% | 12% | 3.79 |
| straight +x+y (x wing) 3 | 1.20 | 39.4 | 887 | 1046 / 0 / 31 | 0.7 | 1108.6 | 0.97 | 2.21 | 50% | 39% | 11% | 3.51 |
| straight +x+y (x wing) 4 | 1.20 | 18.8 | 368 | 714 / 0 / 28 | 0.7 | 1090.9 | 0.68 | 2.41 | 19% | 16% | 3% | 3.78 |
| corner +x+y | 1.20 | 186.0 | 1699 | 465 / 259 / 1359 | 0.7 | 1066.9 | 1.95 | 4.51 | 91% | 62% | 29% | 2.60 |
| straight -x+y (y wing) 0 | 1.20 | 103.1 | 2210 | 1478 / 732 / 966 | 0.7 | 856.7 | 3.71 | 5.82 | 90% | 85% | 5% | 4.46 |
| straight -x+y (y wing) 1 | 1.20 | 81.5 | 1767 | 1710 / 0 / 177 | 0.7 | 1106.1 | 1.71 | 3.81 | 86% | 74% | 12% | 3.85 |
| straight -x+y (y wing) 2 | 1.20 | 61.0 | 1455 | 1513 / 0 / 153 | 0.7 | 1082.1 | 1.54 | 3.01 | 79% | 67% | 12% | 3.78 |
| straight -x+y (y wing) 3 | 1.20 | 39.4 | 878 | 1098 / 0 / 13 | 0.7 | 1104.7 | 1.01 | 2.21 | 45% | 38% | 7% | 3.86 |
| straight -x+y (y wing) 4 | 1.20 | 18.8 | 388 | 638 / 0 / 17 | 0.7 | 1108.6 | 0.59 | 2.31 | 21% | 16% | 4% | 3.41 |
| straight -x+y (x wing) 0 | 1.20 | 103.1 | 2213 | 1475 / 739 / 856 | 0.7 | 846.2 | 3.63 | 5.92 | 89% | 86% | 4% | 4.63 |
| straight -x+y (x wing) 1 | 1.20 | 81.5 | 1784 | 1705 / 0 / 174 | 0.7 | 1080.6 | 1.74 | 4.41 | 90% | 78% | 12% | 3.94 |
| straight -x+y (x wing) 2 | 1.20 | 61.0 | 1406 | 1481 / 0 / 19 | 0.7 | 1094.6 | 1.37 | 2.21 | 77% | 63% | 15% | 3.67 |
| straight -x+y (x wing) 3 | 1.20 | 39.4 | 881 | 1091 / 0 / 17 | 0.7 | 1090.4 | 1.02 | 2.21 | 45% | 37% | 7% | 3.85 |
| straight -x+y (x wing) 4 | 1.20 | 18.8 | 387 | 687 / 0 / 25 | 0.7 | 1107.7 | 0.64 | 2.31 | 17% | 16% | 1% | 4.08 |
| corner -x+y | 1.20 | 186.0 | 1699 | 440 / 284 / 1457 | 0.7 | 1084.6 | 2.01 | 4.11 | 90% | 64% | 26% | 2.69 |
| straight -x-y (y wing) 0 | 1.20 | 103.1 | 2200 | 1486 / 715 / 825 | 0.7 | 856.7 | 3.53 | 6.12 | 90% | 86% | 3% | 4.55 |
| straight -x-y (y wing) 1 | 1.20 | 81.5 | 1801 | 1708 / 0 / 225 | 0.7 | 1084.4 | 1.78 | 3.51 | 89% | 73% | 16% | 3.81 |
| straight -x-y (y wing) 2 | 1.20 | 61.0 | 1451 | 1542 / 0 / 44 | 0.7 | 1169.1 | 1.36 | 2.51 | 71% | 59% | 12% | 3.86 |
| straight -x-y (y wing) 3 | 1.20 | 39.4 | 888 | 1149 / 0 / 16 | 0.7 | 1168.7 | 1.00 | 2.51 | 39% | 37% | 2% | 4.05 |
| straight -x-y (y wing) 4 | 1.20 | 18.8 | 381 | 600 / 0 / 28 | 0.7 | 1120.6 | 0.56 | 2.51 | 16% | 16% | 0% | 4.14 |
| straight -x-y (x wing) 0 | 1.20 | 103.1 | 2214 | 1473 / 741 / 888 | 0.7 | 890.5 | 3.49 | 6.42 | 83% | 81% | 2% | 4.65 |
| straight -x-y (x wing) 1 | 1.20 | 81.5 | 1786 | 1716 / 0 / 231 | 0.7 | 1097.7 | 1.77 | 4.31 | 89% | 68% | 22% | 3.55 |
| straight -x-y (x wing) 2 | 1.20 | 61.0 | 1442 | 1549 / 0 / 17 | 0.7 | 1153.9 | 1.36 | 2.51 | 68% | 60% | 8% | 3.96 |
| straight -x-y (x wing) 3 | 1.20 | 39.4 | 877 | 1090 / 0 / 16 | 0.7 | 1167.2 | 0.95 | 2.31 | 40% | 36% | 4% | 4.01 |
| straight -x-y (x wing) 4 | 1.20 | 18.8 | 363 | 589 / 0 / 43 | 0.7 | 1136.5 | 0.56 | 2.31 | 18% | 15% | 4% | 3.50 |
| corner -x-y | 1.20 | 186.0 | 1650 | 369 / 327 / 1395 | 0.7 | 1118.5 | 1.87 | 4.41 | 92% | 64% | 28% | 2.71 |
| straight +x-y (y wing) 0 | 1.20 | 103.1 | 2221 | 1471 / 751 / 960 | 0.7 | 844.4 | 3.77 | 7.72 | 89% | 85% | 5% | 4.54 |
| straight +x-y (y wing) 1 | 1.20 | 81.5 | 1781 | 1705 / 0 / 205 | 0.7 | 1084.6 | 1.76 | 3.71 | 89% | 76% | 13% | 3.82 |
| straight +x-y (y wing) 2 | 1.20 | 61.0 | 1442 | 1533 / 0 / 22 | 0.7 | 1144.2 | 1.36 | 2.11 | 72% | 63% | 10% | 3.89 |
| straight +x-y (y wing) 3 | 1.20 | 39.4 | 889 | 1131 / 0 / 10 | 0.7 | 1096.3 | 1.04 | 2.11 | 42% | 38% | 4% | 4.05 |
| straight +x-y (y wing) 4 | 1.20 | 18.8 | 368 | 608 / 0 / 18 | 0.7 | 1065.2 | 0.59 | 2.31 | 37% | 17% | 21% | 2.24 |
| straight +x-y (x wing) 0 | 1.20 | 103.1 | 2206 | 1494 / 712 / 715 | 0.7 | 871.6 | 3.35 | 6.02 | 90% | 85% | 5% | 4.49 |
| straight +x-y (x wing) 1 | 1.20 | 81.5 | 1791 | 1695 / 0 / 199 | 0.7 | 1083.7 | 1.75 | 3.61 | 87% | 72% | 15% | 3.87 |
| straight +x-y (x wing) 2 | 1.20 | 61.0 | 1435 | 1504 / 0 / 40 | 0.7 | 1112.4 | 1.39 | 2.21 | 74% | 63% | 11% | 3.87 |
| straight +x-y (x wing) 3 | 1.20 | 39.4 | 872 | 1102 / 0 / 8 | 0.7 | 1129.5 | 0.98 | 2.31 | 39% | 38% | 2% | 4.10 |
| straight +x-y (x wing) 4 | 1.20 | 18.8 | 381 | 621 / 0 / 29 | 0.7 | 1122.2 | 0.58 | 2.41 | 16% | 16% | 0% | 4.09 |
| corner +x-y | 1.20 | 186.0 | 1682 | 410 / 332 / 1319 | 0.7 | 1098.2 | 1.88 | 4.11 | 90% | 59% | 31% | 2.62 |

The last agent out (agent 31153, t100 1171.9 s): last gangway straight -x-y (y wing) 2, exit door -x-y (y wall) 2. The gangway that cleared last: straight -x-y (y wing) 2 at 1169.1 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 8804 | 7800.4 | 6.99 | 1169.4 / 1091.4 / 1031.4 | 1083.9 / 1075.2 / 1006.1 | 5046684.9 | 10286049 | 0.203 |
| gangway | 3792 | 3512.9 | 6.99 | 1167.2 / 1091.4 / 1031.4 | 1083.9 / 1075.2 / 1006.1 | 5046684.9 | 9585507 | 0.131 |
| walkway | 276 | 257.4 | 4.39 | 569.1 / 386.5 / 0.0 | 409.6 / 233.7 / 0.0 | 0.0 | 72661 | 0.681 |
| avenue | 1920 | 1801.4 | 2.06 | 755.8 / 0.0 / 0.0 | 502.9 / 0.0 / 0.0 | 0.0 | 422696 | 1.334 |
| exit | 4 | 2.0 | 0.00 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 0 | - |
| concourse | 2812 | 2226.8 | 3.12 | 1126.2 / 70.0 / 0.0 | 913.5 / 18.7 / 0.0 | 0.0 | 205184 | 1.046 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 25392 | 16030.4 | 7.72 | 1032.5 / 1020.6 / 993.8 | 1026.2 / 1010.8 / 983.3 | 5727474.6 | 14867764 | 0.031 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 208 x 208 from (-104, -104) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -34.5 | -34.5 | gangway | 1.00 | 6.07 | 1050.7 | 1039.8 | 1006.1 | 5878.2 | 0.009 |
| 2 | -34.5 | 34.5 | gangway | 1.00 | 6.00 | 999.1 | 986.5 | 955.0 | 5483.5 | 0.010 |
| 3 | 34.5 | -34.5 | gangway | 1.00 | 5.81 | 1025.0 | 1012.4 | 978.1 | 5476.7 | 0.010 |
| 4 | -35.5 | -35.5 | gangway | 1.00 | 5.55 | 1054.3 | 1049.1 | 987.2 | 5239.5 | 0.010 |
| 5 | -36.5 | -36.5 | gangway | 1.00 | 5.71 | 1061.7 | 1059.4 | 992.1 | 5198.5 | 0.012 |
| 6 | -33.5 | -33.5 | gangway | 0.99 | 5.73 | 1041.4 | 1032.8 | 968.5 | 5196.5 | 0.008 |
| 7 | -35.5 | 35.5 | gangway | 1.00 | 6.13 | 1002.6 | 995.6 | 887.5 | 5145.4 | 0.011 |
| 8 | 39.5 | -39.5 | gangway | 1.00 | 5.97 | 1052.2 | 1048.9 | 885.6 | 5143.3 | 0.024 |
| 9 | 36.5 | -36.5 | gangway | 1.00 | 5.83 | 1035.3 | 1031.2 | 903.7 | 5113.5 | 0.010 |
| 10 | 35.5 | -35.5 | gangway | 1.00 | 5.64 | 1031.2 | 1026.7 | 944.7 | 5076.7 | 0.010 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -36.5 | -38.5 | seat row | 0.50 | 7.34 | 1019.2 | 1006.6 | 974.1 | 3507.2 | 0.004 |
| 2 | -38.5 | -36.5 | seat row | 0.50 | 7.21 | 1014.5 | 1009.2 | 983.3 | 3487.2 | 0.005 |
| 3 | 36.5 | -38.5 | seat row | 0.50 | 7.22 | 998.0 | 996.6 | 976.9 | 3473.1 | 0.005 |
| 4 | 38.5 | -36.5 | seat row | 0.50 | 7.24 | 996.3 | 991.0 | 971.6 | 3455.6 | 0.007 |
| 5 | 36.5 | 38.5 | seat row | 0.50 | 7.45 | 955.9 | 952.9 | 937.2 | 3349.6 | 0.007 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 7731; agent-steps of seated agents on another row's clearway: 1573165.

## Deposit check

Person-seconds deposited: 25159378.4, of them in excluded cells: 5565.709.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 5125932 overlapping pair-steps: p99 0.0030, max 0.1050 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0030 max 0.1050; venue-geometry 6: p99 0.0008 max 0.0008 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00760 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 38 (longest 2 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.40 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 3762 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
