# Experiment `L_load95_s2`

**Task 5.10 stage 4 (AMD 26.10.1): Task 5.8's model (the level spacing on the gangway inclines, --stair-flow off): venue L, 95% load (seed 2)**

Venue L (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (4000 x 4000), cache key a2f3aaf59c2252b7, content hash 022d17b202313d70). 60253 agents on 95% of the 63424 seats (spawnSeatedCrowd, seed 2), buffer N = 65536, 6485 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 8451030 evaluations, 474462 switches, 0 forced choices).
Capacity: **within design capacity** (the L venue's design capacity 63424, jam capacity 171923: 23822.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T20:07:31, 600.5 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 2265 | 396.2 |
| t90 | 4524 | 791.3 |
| t100 | 6485 | 1134.3 |

t_p: the step by which ceil(p x 60253) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 1765 | 0 | 70.3 | 862.1 | 23.6 | 25.5 | 79.6-89.6 |
| -x | 5.66 | 1772 | 0 | 70.5 | 866.0 | 23.6 | 26.6 | 392.8-402.8 |
| +y | 5.66 | 1771 | 0 | 70.5 | 871.4 | 23.4 | 26.6 | 131.9-141.8 |
| -y | 5.66 | 1771 | 0 | 70.5 | 878.7 | 23.2 | 25.5 | 79.1-89.0 |
| door +x+y (y wall) 0 | 2.30 | 1510 | 2446 | 4.9 | 967.9 | 40.9 | 57.6 | 16.3-26.2 |
| door +x+y (y wall) 1 | 2.30 | 1674 | 2033 | 4.9 | 1071.3 | 40.9 | 57.6 | 14.9-24.8 |
| door +x+y (y wall) 2 | 2.30 | 1445 | 1513 | 4.9 | 1110.0 | 34.1 | 57.6 | 29.0-39.0 |
| door +x+y (y wall) 3 | 2.30 | 1186 | 988 | 4.9 | 1122.7 | 27.7 | 57.6 | 58.6-68.6 |
| door +x+y (y wall) 4 | 2.30 | 664 | 488 | 4.9 | 1126.4 | 15.4 | 54.9 | 7.3-17.3 |
| door +x+y (x wall) 0 | 2.30 | 1488 | 2451 | 5.1 | 962.0 | 40.6 | 54.9 | 12.4-22.4 |
| door +x+y (x wall) 1 | 2.30 | 1673 | 2018 | 4.9 | 1055.6 | 41.5 | 54.9 | 75.9-85.9 |
| door +x+y (x wall) 2 | 2.30 | 1500 | 1527 | 4.9 | 1102.4 | 35.6 | 57.6 | 27.1-37.1 |
| door +x+y (x wall) 3 | 2.30 | 1123 | 997 | 4.7 | 1104.9 | 26.6 | 57.6 | 16.6-26.6 |
| door +x+y (x wall) 4 | 2.30 | 595 | 483 | 5.1 | 1072.5 | 14.5 | 54.9 | 5.8-15.7 |
| door +x+y (corner) | 2.30 | 421 | 120 | 6.3 | 981.4 | 11.3 | 54.9 | 57.0-67.0 |
| door -x+y (y wall) 0 | 2.30 | 1496 | 2456 | 4.9 | 949.6 | 41.3 | 57.6 | 15.0-25.0 |
| door -x+y (y wall) 1 | 2.30 | 1698 | 2023 | 4.9 | 1134.3 | 39.2 | 60.2 | 11.5-21.5 |
| door -x+y (y wall) 2 | 2.30 | 1496 | 1517 | 4.9 | 1119.4 | 35.0 | 57.6 | 25.5-35.5 |
| door -x+y (y wall) 3 | 2.30 | 1179 | 1003 | 4.9 | 1109.6 | 27.8 | 57.6 | 10.7-20.6 |
| door -x+y (y wall) 4 | 2.30 | 646 | 490 | 5.1 | 1074.8 | 15.8 | 57.6 | 7.3-17.3 |
| door -x+y (x wall) 0 | 2.30 | 1508 | 2457 | 4.9 | 952.0 | 41.5 | 60.2 | 19.2-29.2 |
| door -x+y (x wall) 1 | 2.30 | 1682 | 2016 | 4.9 | 1076.7 | 40.9 | 54.9 | 57.5-67.5 |
| door -x+y (x wall) 2 | 2.30 | 1484 | 1499 | 4.9 | 1118.5 | 34.8 | 54.9 | 10.0-19.9 |
| door -x+y (x wall) 3 | 2.30 | 1140 | 995 | 4.9 | 1104.0 | 27.1 | 57.6 | 16.4-26.4 |
| door -x+y (x wall) 4 | 2.30 | 576 | 493 | 4.9 | 1028.6 | 14.7 | 57.6 | 7.3-17.3 |
| door -x+y (corner) | 2.30 | 403 | 119 | 6.3 | 962.2 | 11.0 | 54.9 | 45.8-55.8 |
| door -x-y (y wall) 0 | 2.30 | 1506 | 2459 | 4.9 | 898.1 | 44.0 | 57.6 | 18.0-28.0 |
| door -x-y (y wall) 1 | 2.30 | 1673 | 2034 | 4.9 | 1041.0 | 42.1 | 57.6 | 16.4-26.4 |
| door -x-y (y wall) 2 | 2.30 | 1530 | 1513 | 4.9 | 1094.6 | 36.6 | 57.6 | 191.3-201.3 |
| door -x-y (y wall) 3 | 2.30 | 1157 | 986 | 4.9 | 1094.7 | 27.7 | 57.6 | 48.8-58.8 |
| door -x-y (y wall) 4 | 2.30 | 615 | 485 | 4.9 | 1054.9 | 15.3 | 57.6 | 17.3-27.3 |
| door -x-y (x wall) 0 | 2.30 | 1503 | 2445 | 4.9 | 918.6 | 42.9 | 57.6 | 13.5-23.4 |
| door -x-y (x wall) 1 | 2.30 | 1660 | 2040 | 4.9 | 1065.7 | 40.8 | 57.6 | 25.7-35.7 |
| door -x-y (x wall) 2 | 2.30 | 1496 | 1501 | 4.9 | 1081.1 | 36.3 | 60.2 | 11.5-21.5 |
| door -x-y (x wall) 3 | 2.30 | 1177 | 983 | 4.9 | 1100.0 | 28.0 | 57.6 | 10.7-20.6 |
| door -x-y (x wall) 4 | 2.30 | 601 | 489 | 5.1 | 1014.1 | 15.5 | 57.6 | 7.3-17.3 |
| door -x-y (corner) | 2.30 | 340 | 118 | 6.3 | 968.6 | 9.2 | 52.3 | 46.4-56.3 |
| door +x-y (y wall) 0 | 2.30 | 1505 | 2456 | 5.1 | 950.6 | 41.5 | 57.6 | 5.9-15.9 |
| door +x-y (y wall) 1 | 2.30 | 1690 | 2038 | 4.9 | 1106.3 | 40.0 | 57.6 | 29.0-39.0 |
| door +x-y (y wall) 2 | 2.30 | 1487 | 1522 | 4.9 | 1105.8 | 35.2 | 54.9 | 23.4-33.4 |
| door +x-y (y wall) 3 | 2.30 | 1024 | 984 | 4.9 | 1092.8 | 24.6 | 57.6 | 436.9-446.9 |
| door +x-y (y wall) 4 | 2.30 | 767 | 487 | 5.1 | 1114.3 | 18.0 | 54.9 | 18.0-28.0 |
| door +x-y (x wall) 0 | 2.30 | 1503 | 2443 | 5.1 | 955.5 | 41.2 | 57.6 | 29.4-39.4 |
| door +x-y (x wall) 1 | 2.30 | 1700 | 2040 | 4.9 | 1104.5 | 40.3 | 57.6 | 770.5-780.4 |
| door +x-y (x wall) 2 | 2.30 | 1439 | 1499 | 4.9 | 1105.2 | 34.1 | 57.6 | 20.5-30.4 |
| door +x-y (x wall) 3 | 2.30 | 1107 | 989 | 4.9 | 1110.0 | 26.1 | 60.2 | 18.5-28.5 |
| door +x-y (x wall) 4 | 2.30 | 653 | 494 | 5.1 | 1082.7 | 15.8 | 60.2 | 14.7-24.7 |
| door +x-y (corner) | 2.30 | 454 | 116 | 6.5 | 947.8 | 12.6 | 60.2 | 128.0-138.0 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (2.30 m; a corner door's: the gap between its wall ends, 2.30 m); agents are removed past the outer wall's outer face (92.71 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 1765 | 2.9% | 19.7% |
| -x | avenue | 5.66 | 1772 | 2.9% | 19.8% |
| +y | avenue | 5.66 | 1771 | 2.9% | 19.8% |
| -y | avenue | 5.66 | 1771 | 2.9% | 19.8% |
| door +x+y (y wall) 0 | door | 2.30 | 1510 | 2.5% | 41.5% |
| door +x+y (y wall) 1 | door | 2.30 | 1674 | 2.8% | 46.1% |
| door +x+y (y wall) 2 | door | 2.30 | 1445 | 2.4% | 39.8% |
| door +x+y (y wall) 3 | door | 2.30 | 1186 | 2.0% | 32.6% |
| door +x+y (y wall) 4 | door | 2.30 | 664 | 1.1% | 18.3% |
| door +x+y (x wall) 0 | door | 2.30 | 1488 | 2.5% | 40.9% |
| door +x+y (x wall) 1 | door | 2.30 | 1673 | 2.8% | 46.0% |
| door +x+y (x wall) 2 | door | 2.30 | 1500 | 2.5% | 41.3% |
| door +x+y (x wall) 3 | door | 2.30 | 1123 | 1.9% | 30.9% |
| door +x+y (x wall) 4 | door | 2.30 | 595 | 1.0% | 16.4% |
| door +x+y (corner) | door | 2.30 | 421 | 0.7% | 11.6% |
| door -x+y (y wall) 0 | door | 2.30 | 1496 | 2.5% | 41.2% |
| door -x+y (y wall) 1 | door | 2.30 | 1698 | 2.8% | 46.7% |
| door -x+y (y wall) 2 | door | 2.30 | 1496 | 2.5% | 41.2% |
| door -x+y (y wall) 3 | door | 2.30 | 1179 | 2.0% | 32.4% |
| door -x+y (y wall) 4 | door | 2.30 | 646 | 1.1% | 17.8% |
| door -x+y (x wall) 0 | door | 2.30 | 1508 | 2.5% | 41.5% |
| door -x+y (x wall) 1 | door | 2.30 | 1682 | 2.8% | 46.3% |
| door -x+y (x wall) 2 | door | 2.30 | 1484 | 2.5% | 40.8% |
| door -x+y (x wall) 3 | door | 2.30 | 1140 | 1.9% | 31.4% |
| door -x+y (x wall) 4 | door | 2.30 | 576 | 1.0% | 15.8% |
| door -x+y (corner) | door | 2.30 | 403 | 0.7% | 11.1% |
| door -x-y (y wall) 0 | door | 2.30 | 1506 | 2.5% | 41.4% |
| door -x-y (y wall) 1 | door | 2.30 | 1673 | 2.8% | 46.0% |
| door -x-y (y wall) 2 | door | 2.30 | 1530 | 2.5% | 42.1% |
| door -x-y (y wall) 3 | door | 2.30 | 1157 | 1.9% | 31.8% |
| door -x-y (y wall) 4 | door | 2.30 | 615 | 1.0% | 16.9% |
| door -x-y (x wall) 0 | door | 2.30 | 1503 | 2.5% | 41.3% |
| door -x-y (x wall) 1 | door | 2.30 | 1660 | 2.8% | 45.7% |
| door -x-y (x wall) 2 | door | 2.30 | 1496 | 2.5% | 41.2% |
| door -x-y (x wall) 3 | door | 2.30 | 1177 | 2.0% | 32.4% |
| door -x-y (x wall) 4 | door | 2.30 | 601 | 1.0% | 16.5% |
| door -x-y (corner) | door | 2.30 | 340 | 0.6% | 9.4% |
| door +x-y (y wall) 0 | door | 2.30 | 1505 | 2.5% | 41.4% |
| door +x-y (y wall) 1 | door | 2.30 | 1690 | 2.8% | 46.5% |
| door +x-y (y wall) 2 | door | 2.30 | 1487 | 2.5% | 40.9% |
| door +x-y (y wall) 3 | door | 2.30 | 1024 | 1.7% | 28.2% |
| door +x-y (y wall) 4 | door | 2.30 | 767 | 1.3% | 21.1% |
| door +x-y (x wall) 0 | door | 2.30 | 1503 | 2.5% | 41.3% |
| door +x-y (x wall) 1 | door | 2.30 | 1700 | 2.8% | 46.8% |
| door +x-y (x wall) 2 | door | 2.30 | 1439 | 2.4% | 39.6% |
| door +x-y (x wall) 3 | door | 2.30 | 1107 | 1.8% | 30.5% |
| door +x-y (x wall) 4 | door | 2.30 | 653 | 1.1% | 18.0% |
| door +x-y (corner) | door | 2.30 | 454 | 0.8% | 12.5% |
| **doors (44)** | door | 101.20 | 53174 | 88.3% | |
| **avenues (4)** | avenue | 22.64 | 7079 | 11.7% | |

**Unused exit width: 0.0 of 123.8 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 1134.3 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 30.8%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 2211 | 3.7% | 2211 | 3.7% |
| straight +x+y (y wing) 1 | straight | yes | 1799 | 3.0% | 1701 | 2.8% |
| straight +x+y (y wing) 2 | straight | yes | 1514 | 2.5% | 1502 | 2.5% |
| straight +x+y (y wing) 3 | straight | yes | 1164 | 1.9% | 1160 | 1.9% |
| straight +x+y (y wing) 4 | straight | yes | 653 | 1.1% | 633 | 1.1% |
| straight +x+y (x wing) 0 | straight | yes | 2204 | 3.7% | 2204 | 3.7% |
| straight +x+y (x wing) 1 | straight | yes | 1796 | 3.0% | 1689 | 2.8% |
| straight +x+y (x wing) 2 | straight | yes | 1539 | 2.6% | 1515 | 2.5% |
| straight +x+y (x wing) 3 | straight | yes | 1132 | 1.9% | 1132 | 1.9% |
| straight +x+y (x wing) 4 | straight | yes | 584 | 1.0% | 571 | 0.9% |
| corner +x+y | corner | yes | 1969 | 3.3% | 746 | 1.2% |
| straight -x+y (y wing) 0 | straight | yes | 2205 | 3.7% | 2205 | 3.7% |
| straight -x+y (y wing) 1 | straight | yes | 1805 | 3.0% | 1718 | 2.9% |
| straight -x+y (y wing) 2 | straight | yes | 1534 | 2.5% | 1523 | 2.5% |
| straight -x+y (y wing) 3 | straight | yes | 1177 | 2.0% | 1171 | 1.9% |
| straight -x+y (y wing) 4 | straight | yes | 643 | 1.1% | 627 | 1.0% |
| straight -x+y (x wing) 0 | straight | yes | 2226 | 3.7% | 2226 | 3.7% |
| straight -x+y (x wing) 1 | straight | yes | 1795 | 3.0% | 1702 | 2.8% |
| straight -x+y (x wing) 2 | straight | yes | 1504 | 2.5% | 1495 | 2.5% |
| straight -x+y (x wing) 3 | straight | yes | 1145 | 1.9% | 1139 | 1.9% |
| straight -x+y (x wing) 4 | straight | yes | 584 | 1.0% | 566 | 0.9% |
| corner -x+y | corner | yes | 1960 | 3.3% | 696 | 1.2% |
| straight -x-y (y wing) 0 | straight | yes | 2212 | 3.7% | 2212 | 3.7% |
| straight -x-y (y wing) 1 | straight | yes | 1789 | 3.0% | 1682 | 2.8% |
| straight -x-y (y wing) 2 | straight | yes | 1559 | 2.6% | 1542 | 2.6% |
| straight -x-y (y wing) 3 | straight | yes | 1185 | 2.0% | 1182 | 2.0% |
| straight -x-y (y wing) 4 | straight | yes | 595 | 1.0% | 578 | 1.0% |
| straight -x-y (x wing) 0 | straight | yes | 2226 | 3.7% | 2226 | 3.7% |
| straight -x-y (x wing) 1 | straight | yes | 1784 | 3.0% | 1674 | 2.8% |
| straight -x-y (x wing) 2 | straight | yes | 1536 | 2.5% | 1522 | 2.5% |
| straight -x-y (x wing) 3 | straight | yes | 1181 | 2.0% | 1180 | 2.0% |
| straight -x-y (x wing) 4 | straight | yes | 585 | 1.0% | 572 | 0.9% |
| corner -x-y | corner | yes | 2011 | 3.3% | 683 | 1.1% |
| straight +x-y (y wing) 0 | straight | yes | 2224 | 3.7% | 2224 | 3.7% |
| straight +x-y (y wing) 1 | straight | yes | 1792 | 3.0% | 1708 | 2.8% |
| straight +x-y (y wing) 2 | straight | yes | 1531 | 2.5% | 1509 | 2.5% |
| straight +x-y (y wing) 3 | straight | yes | 1082 | 1.8% | 1074 | 1.8% |
| straight +x-y (y wing) 4 | straight | yes | 718 | 1.2% | 695 | 1.2% |
| straight +x-y (x wing) 0 | straight | yes | 2221 | 3.7% | 2221 | 3.7% |
| straight +x-y (x wing) 1 | straight | yes | 1796 | 3.0% | 1712 | 2.8% |
| straight +x-y (x wing) 2 | straight | yes | 1526 | 2.5% | 1506 | 2.5% |
| straight +x-y (x wing) 3 | straight | yes | 1083 | 1.8% | 1077 | 1.8% |
| straight +x-y (x wing) 4 | straight | yes | 634 | 1.1% | 615 | 1.0% |
| corner +x-y | corner | yes | 1985 | 3.3% | 727 | 1.2% |
| **straight (40)** | | | 58473 | | 57401 | 95.3% |
| **corner (4)** | | | 7925 | | 2852 | 4.7% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 1765 | 70.3 | 862.1 | 0.28 | 0.31 | 0.0% |
| -x | 1772 | 70.5 | 866.0 | 0.28 | 0.32 | 0.0% |
| +y | 1771 | 70.5 | 871.4 | 0.28 | 0.32 | 0.0% |
| -y | 1771 | 70.5 | 878.7 | 0.28 | 0.31 | 0.0% |
| door +x+y (y wall) 0 | 1510 | 4.9 | 967.9 | 0.49 | 0.69 | 0.0% |
| door +x+y (y wall) 1 | 1674 | 4.9 | 1071.3 | 0.49 | 0.69 | 0.0% |
| door +x+y (y wall) 2 | 1445 | 4.9 | 1110.0 | 0.41 | 0.69 | 0.0% |
| door +x+y (y wall) 3 | 1186 | 4.9 | 1122.7 | 0.33 | 0.69 | 0.0% |
| door +x+y (y wall) 4 | 664 | 4.9 | 1126.4 | 0.18 | 0.66 | 0.0% |
| door +x+y (x wall) 0 | 1488 | 5.1 | 962.0 | 0.49 | 0.66 | 0.0% |
| door +x+y (x wall) 1 | 1673 | 4.9 | 1055.6 | 0.50 | 0.66 | 0.0% |
| door +x+y (x wall) 2 | 1500 | 4.9 | 1102.4 | 0.43 | 0.69 | 0.0% |
| door +x+y (x wall) 3 | 1123 | 4.7 | 1104.9 | 0.32 | 0.69 | 0.0% |
| door +x+y (x wall) 4 | 595 | 5.1 | 1072.5 | 0.17 | 0.66 | 0.0% |
| door +x+y (corner) | 421 | 6.3 | 981.4 | 0.13 | 0.66 | 0.0% |
| door -x+y (y wall) 0 | 1496 | 4.9 | 949.6 | 0.49 | 0.69 | 0.0% |
| door -x+y (y wall) 1 | 1698 | 4.9 | 1134.3 | 0.47 | 0.72 | 0.0% |
| door -x+y (y wall) 2 | 1496 | 4.9 | 1119.4 | 0.42 | 0.69 | 0.0% |
| door -x+y (y wall) 3 | 1179 | 4.9 | 1109.6 | 0.33 | 0.69 | 0.0% |
| door -x+y (y wall) 4 | 646 | 5.1 | 1074.8 | 0.19 | 0.69 | 0.0% |
| door -x+y (x wall) 0 | 1508 | 4.9 | 952.0 | 0.50 | 0.72 | 0.0% |
| door -x+y (x wall) 1 | 1682 | 4.9 | 1076.7 | 0.49 | 0.66 | 0.0% |
| door -x+y (x wall) 2 | 1484 | 4.9 | 1118.5 | 0.42 | 0.66 | 0.0% |
| door -x+y (x wall) 3 | 1140 | 4.9 | 1104.0 | 0.32 | 0.69 | 0.0% |
| door -x+y (x wall) 4 | 576 | 4.9 | 1028.6 | 0.18 | 0.69 | 0.0% |
| door -x+y (corner) | 403 | 6.3 | 962.2 | 0.13 | 0.66 | 0.0% |
| door -x-y (y wall) 0 | 1506 | 4.9 | 898.1 | 0.53 | 0.69 | 0.0% |
| door -x-y (y wall) 1 | 1673 | 4.9 | 1041.0 | 0.50 | 0.69 | 0.0% |
| door -x-y (y wall) 2 | 1530 | 4.9 | 1094.6 | 0.44 | 0.69 | 0.0% |
| door -x-y (y wall) 3 | 1157 | 4.9 | 1094.7 | 0.33 | 0.69 | 0.0% |
| door -x-y (y wall) 4 | 615 | 4.9 | 1054.9 | 0.18 | 0.69 | 0.0% |
| door -x-y (x wall) 0 | 1503 | 4.9 | 918.6 | 0.51 | 0.69 | 0.0% |
| door -x-y (x wall) 1 | 1660 | 4.9 | 1065.7 | 0.49 | 0.69 | 0.0% |
| door -x-y (x wall) 2 | 1496 | 4.9 | 1081.1 | 0.43 | 0.72 | 0.0% |
| door -x-y (x wall) 3 | 1177 | 4.9 | 1100.0 | 0.34 | 0.69 | 0.0% |
| door -x-y (x wall) 4 | 601 | 5.1 | 1014.1 | 0.19 | 0.69 | 0.0% |
| door -x-y (corner) | 340 | 6.3 | 968.6 | 0.11 | 0.63 | 0.0% |
| door +x-y (y wall) 0 | 1505 | 5.1 | 950.6 | 0.50 | 0.69 | 0.0% |
| door +x-y (y wall) 1 | 1690 | 4.9 | 1106.3 | 0.48 | 0.69 | 0.0% |
| door +x-y (y wall) 2 | 1487 | 4.9 | 1105.8 | 0.42 | 0.66 | 0.0% |
| door +x-y (y wall) 3 | 1024 | 4.9 | 1092.8 | 0.29 | 0.69 | 0.0% |
| door +x-y (y wall) 4 | 767 | 5.1 | 1114.3 | 0.22 | 0.66 | 0.0% |
| door +x-y (x wall) 0 | 1503 | 5.1 | 955.5 | 0.49 | 0.69 | 0.0% |
| door +x-y (x wall) 1 | 1700 | 4.9 | 1104.5 | 0.48 | 0.69 | 0.0% |
| door +x-y (x wall) 2 | 1439 | 4.9 | 1105.2 | 0.41 | 0.69 | 0.0% |
| door +x-y (x wall) 3 | 1107 | 4.9 | 1110.0 | 0.31 | 0.72 | 0.0% |
| door +x-y (x wall) 4 | 653 | 5.1 | 1082.7 | 0.19 | 0.72 | 0.0% |
| door +x-y (corner) | 454 | 6.5 | 947.8 | 0.15 | 0.72 | 0.0% |

Mean flow / w J averaged over the doors 0.36, over the avenues 0.28.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 103.1 | 2211 | 1483 / 728 / 760 | 0.7 | 862.6 | 3.45 | 5.52 | 86% | 85% | 1% | 4.61 |
| straight +x+y (y wing) 1 | 1.20 | 81.5 | 1783 | 1701 / 0 / 228 | 0.7 | 1068.3 | 1.81 | 3.61 | 87% | 73% | 14% | 3.88 |
| straight +x+y (y wing) 2 | 1.20 | 61.0 | 1434 | 1502 / 0 / 396 | 0.7 | 1107.0 | 1.72 | 3.41 | 74% | 62% | 12% | 3.81 |
| straight +x+y (y wing) 3 | 1.20 | 39.4 | 892 | 1160 / 0 / 11 | 0.7 | 1119.8 | 1.05 | 2.31 | 41% | 38% | 3% | 4.06 |
| straight +x+y (y wing) 4 | 1.20 | 18.8 | 394 | 633 / 0 / 21 | 0.7 | 1123.4 | 0.58 | 2.31 | 18% | 16% | 2% | 4.05 |
| straight +x+y (x wing) 0 | 1.20 | 103.1 | 2204 | 1472 / 732 / 963 | 0.7 | 854.6 | 3.71 | 5.82 | 90% | 86% | 3% | 4.52 |
| straight +x+y (x wing) 1 | 1.20 | 81.5 | 1784 | 1689 / 0 / 240 | 0.7 | 1052.6 | 1.83 | 3.71 | 88% | 71% | 17% | 3.68 |
| straight +x+y (x wing) 2 | 1.20 | 61.0 | 1458 | 1515 / 0 / 30 | 0.7 | 1099.5 | 1.41 | 2.21 | 76% | 64% | 12% | 3.80 |
| straight +x+y (x wing) 3 | 1.20 | 39.4 | 877 | 1132 / 0 / 10 | 0.7 | 1101.9 | 1.04 | 2.21 | 41% | 38% | 4% | 3.98 |
| straight +x+y (x wing) 4 | 1.20 | 18.8 | 382 | 571 / 0 / 17 | 0.7 | 1069.6 | 0.55 | 2.21 | 41% | 16% | 25% | 2.08 |
| corner +x+y | 1.20 | 186.0 | 1645 | 421 / 326 / 1663 | 0.7 | 1099.5 | 2.19 | 6.02 | 88% | 65% | 23% | 2.73 |
| straight -x+y (y wing) 0 | 1.20 | 103.1 | 2205 | 1476 / 729 / 1065 | 0.7 | 847.2 | 3.86 | 6.52 | 89% | 86% | 4% | 4.54 |
| straight -x+y (y wing) 1 | 1.20 | 81.5 | 1778 | 1718 / 0 / 205 | 0.7 | 1131.3 | 1.70 | 4.11 | 87% | 70% | 17% | 3.73 |
| straight -x+y (y wing) 2 | 1.20 | 61.0 | 1441 | 1523 / 0 / 16 | 0.7 | 1116.4 | 1.38 | 2.11 | 73% | 63% | 10% | 3.79 |
| straight -x+y (y wing) 3 | 1.20 | 39.4 | 893 | 1171 / 0 / 8 | 0.7 | 1106.6 | 1.07 | 2.31 | 47% | 40% | 7% | 3.79 |
| straight -x+y (y wing) 4 | 1.20 | 18.8 | 378 | 627 / 0 / 19 | 0.7 | 1071.8 | 0.60 | 2.31 | 21% | 16% | 6% | 3.23 |
| straight -x+y (x wing) 0 | 1.20 | 103.1 | 2226 | 1488 / 739 / 788 | 0.7 | 865.6 | 3.49 | 5.52 | 90% | 84% | 6% | 4.55 |
| straight -x+y (x wing) 1 | 1.20 | 81.5 | 1780 | 1702 / 0 / 196 | 0.7 | 1073.8 | 1.77 | 4.01 | 91% | 73% | 18% | 3.77 |
| straight -x+y (x wing) 2 | 1.20 | 61.0 | 1400 | 1495 / 0 / 14 | 0.7 | 1115.6 | 1.35 | 2.21 | 73% | 60% | 13% | 3.76 |
| straight -x+y (x wing) 3 | 1.20 | 39.4 | 892 | 1139 / 0 / 8 | 0.7 | 1101.0 | 1.04 | 2.21 | 44% | 38% | 6% | 3.80 |
| straight -x+y (x wing) 4 | 1.20 | 18.8 | 384 | 566 / 0 / 44 | 0.7 | 1025.7 | 0.60 | 2.11 | 33% | 17% | 16% | 2.55 |
| corner -x+y | 1.20 | 186.0 | 1691 | 403 / 293 / 1345 | 0.7 | 1056.4 | 1.93 | 4.51 | 92% | 66% | 26% | 2.79 |
| straight -x-y (y wing) 0 | 1.20 | 103.1 | 2212 | 1497 / 716 / 830 | 0.7 | 846.9 | 3.60 | 6.42 | 89% | 87% | 2% | 4.65 |
| straight -x-y (y wing) 1 | 1.20 | 81.5 | 1774 | 1682 / 0 / 215 | 0.7 | 1038.1 | 1.83 | 3.61 | 88% | 73% | 14% | 3.78 |
| straight -x-y (y wing) 2 | 1.20 | 61.0 | 1467 | 1542 / 0 / 19 | 0.7 | 1091.6 | 1.43 | 2.11 | 76% | 65% | 12% | 3.84 |
| straight -x-y (y wing) 3 | 1.20 | 39.4 | 881 | 1182 / 0 / 13 | 0.7 | 1091.8 | 1.10 | 2.31 | 51% | 39% | 12% | 3.56 |
| straight -x-y (y wing) 4 | 1.20 | 18.8 | 367 | 578 / 0 / 30 | 0.7 | 1051.9 | 0.58 | 2.21 | 18% | 16% | 2% | 3.91 |
| straight -x-y (x wing) 0 | 1.20 | 103.1 | 2226 | 1489 / 737 / 794 | 0.7 | 851.6 | 3.55 | 6.32 | 90% | 86% | 3% | 4.57 |
| straight -x-y (x wing) 1 | 1.20 | 81.5 | 1771 | 1674 / 0 / 220 | 0.7 | 1062.7 | 1.78 | 3.61 | 89% | 74% | 15% | 3.71 |
| straight -x-y (x wing) 2 | 1.20 | 61.0 | 1447 | 1522 / 0 / 19 | 0.7 | 1078.1 | 1.43 | 2.41 | 76% | 65% | 11% | 3.86 |
| straight -x-y (x wing) 3 | 1.20 | 39.4 | 858 | 1180 / 0 / 4 | 0.7 | 1097.0 | 1.08 | 2.11 | 54% | 37% | 17% | 3.38 |
| straight -x-y (x wing) 4 | 1.20 | 18.8 | 367 | 572 / 0 / 21 | 0.7 | 1011.1 | 0.59 | 2.21 | 21% | 17% | 4% | 3.64 |
| corner -x-y | 1.20 | 186.0 | 1683 | 340 / 343 / 1390 | 0.7 | 1046.8 | 1.98 | 5.82 | 92% | 69% | 24% | 2.86 |
| straight +x-y (y wing) 0 | 1.20 | 103.1 | 2224 | 1487 / 739 / 885 | 0.7 | 858.3 | 3.63 | 5.72 | 89% | 83% | 6% | 4.54 |
| straight +x-y (y wing) 1 | 1.20 | 81.5 | 1771 | 1708 / 0 / 182 | 0.7 | 1103.3 | 1.71 | 4.31 | 88% | 72% | 16% | 3.76 |
| straight +x-y (y wing) 2 | 1.20 | 61.0 | 1449 | 1509 / 0 / 32 | 0.7 | 1102.8 | 1.40 | 2.21 | 77% | 65% | 12% | 3.76 |
| straight +x-y (y wing) 3 | 1.20 | 39.4 | 876 | 1074 / 0 / 11 | 0.7 | 1089.8 | 1.00 | 2.21 | 49% | 39% | 10% | 3.62 |
| straight +x-y (y wing) 4 | 1.20 | 18.8 | 367 | 695 / 0 / 31 | 0.7 | 1111.4 | 0.65 | 2.41 | 19% | 18% | 1% | 3.74 |
| straight +x-y (x wing) 0 | 1.20 | 103.1 | 2221 | 1492 / 730 / 830 | 0.7 | 846.9 | 3.61 | 5.82 | 91% | 86% | 5% | 4.46 |
| straight +x-y (x wing) 1 | 1.20 | 81.5 | 1772 | 1712 / 0 / 167 | 0.7 | 1101.6 | 1.71 | 3.71 | 88% | 73% | 15% | 3.97 |
| straight +x-y (x wing) 2 | 1.20 | 61.0 | 1435 | 1506 / 0 / 24 | 0.7 | 1102.3 | 1.39 | 2.31 | 76% | 64% | 12% | 3.85 |
| straight +x-y (x wing) 3 | 1.20 | 39.4 | 872 | 1077 / 0 / 11 | 0.7 | 1107.0 | 0.98 | 2.21 | 47% | 38% | 9% | 3.50 |
| straight +x-y (x wing) 4 | 1.20 | 18.8 | 378 | 615 / 0 / 28 | 0.7 | 1079.7 | 0.60 | 2.31 | 17% | 17% | 1% | 4.02 |
| corner +x-y | 1.20 | 186.0 | 1703 | 454 / 273 / 1339 | 0.7 | 1087.4 | 1.90 | 4.71 | 88% | 65% | 24% | 2.69 |

The last agent out (agent 15841, t100 1134.3 s): last gangway straight -x+y (y wing) 1, exit door -x+y (y wall) 1. The gangway that cleared last: straight -x+y (y wing) 1 at 1131.3 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 8804 | 7800.4 | 7.05 | 1120.5 / 1041.2 / 986.5 | 1027.4 / 1015.5 / 955.0 | 4998928.9 | 10291198 | 0.203 |
| gangway | 3792 | 3512.9 | 7.05 | 1118.5 / 1041.2 / 986.5 | 1027.4 / 1015.5 / 955.0 | 4998928.9 | 9588778 | 0.131 |
| walkway | 276 | 257.4 | 3.92 | 624.6 / 341.4 / 0.0 | 481.2 / 244.2 / 0.0 | 0.0 | 73937 | 0.672 |
| avenue | 1920 | 1801.4 | 2.02 | 763.8 / 0.0 / 0.0 | 609.9 / 0.0 / 0.0 | 0.0 | 424292 | 1.334 |
| exit | 4 | 2.0 | 0.00 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 0 | - |
| concourse | 2812 | 2226.8 | 3.18 | 1096.1 / 71.7 / 0.0 | 924.2 / 19.6 / 0.0 | 0.0 | 204191 | 1.045 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 25392 | 16030.4 | 7.89 | 985.6 / 979.8 / 967.2 | 981.8 / 975.3 / 958.8 | 5768873.1 | 14916121 | 0.031 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 208 x 208 from (-104, -104) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -33.5 | 33.5 | gangway | 0.99 | 5.80 | 1009.2 | 993.5 | 935.8 | 5210.8 | 0.008 |
| 2 | -34.5 | 34.5 | gangway | 1.00 | 5.90 | 1000.6 | 986.6 | 920.7 | 5208.1 | 0.010 |
| 3 | -35.5 | 35.5 | gangway | 1.00 | 5.65 | 1003.1 | 990.8 | 939.8 | 5206.5 | 0.010 |
| 4 | 36.5 | -36.5 | gangway | 1.00 | 5.84 | 1008.5 | 1000.3 | 936.6 | 5186.3 | 0.014 |
| 5 | 35.5 | -35.5 | gangway | 1.00 | 5.79 | 1006.4 | 997.1 | 924.0 | 5161.8 | 0.012 |
| 6 | -35.5 | -35.5 | gangway | 1.00 | 5.86 | 990.8 | 985.6 | 908.6 | 5151.8 | 0.012 |
| 7 | 34.5 | -34.5 | gangway | 1.00 | 5.91 | 1002.6 | 986.1 | 882.9 | 5016.5 | 0.010 |
| 8 | 33.5 | 33.5 | gangway | 0.99 | 5.57 | 999.2 | 990.3 | 925.8 | 5014.4 | 0.006 |
| 9 | -32.5 | 32.5 | gangway | 1.00 | 5.67 | 1002.7 | 986.8 | 894.6 | 5013.0 | 0.005 |
| 10 | 36.5 | 36.5 | gangway | 1.00 | 5.93 | 1016.7 | 1012.9 | 944.3 | 4981.4 | 0.013 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 36.5 | 38.5 | seat row | 0.50 | 7.34 | 977.4 | 975.3 | 958.8 | 3414.1 | 0.007 |
| 2 | -36.5 | 38.5 | seat row | 0.50 | 7.23 | 976.2 | 969.0 | 949.2 | 3347.5 | 0.006 |
| 3 | -38.5 | 36.5 | seat row | 0.50 | 7.28 | 969.5 | 964.6 | 943.6 | 3344.8 | 0.006 |
| 4 | -36.5 | -38.5 | seat row | 0.50 | 7.35 | 950.8 | 946.9 | 925.3 | 3313.4 | 0.006 |
| 5 | 38.5 | -36.5 | seat row | 0.50 | 7.33 | 956.2 | 951.7 | 935.1 | 3301.4 | 0.007 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 7665; agent-steps of seated agents on another row's clearway: 1643788.

## Deposit check

Person-seconds deposited: 25212901.8, of them in excluded cells: 5583.228.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 5081756 overlapping pair-steps: p99 0.0031, max 0.0762 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0031 max 0.0762; venue-geometry 15: p99 0.0010 max 0.0010 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00752 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 56 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.44 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 3654 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
