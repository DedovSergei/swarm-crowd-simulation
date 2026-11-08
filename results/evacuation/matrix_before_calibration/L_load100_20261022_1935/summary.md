# Experiment `L_load100`

**Task 5.10 stage 4 (AMD 26.10.1): Task 5.8's model (the level spacing on the gangway inclines, --stair-flow off): venue L, 100% load**

Venue L (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (4000 x 4000), cache key a2f3aaf59c2252b7, content hash 022d17b202313d70). 63424 agents on 100% of the 63424 seats (spawnSeatedCrowd, seed 1337), buffer N = 65536, 6867 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 9281301 evaluations, 522205 switches, 0 forced choices).
Capacity: **within design capacity** (the L venue's design capacity 63424, jam capacity 171923: 23822.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T19:35:13, 929.7 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 2343 | 409.8 |
| t90 | 4761 | 832.7 |
| t100 | 6867 | 1201.1 |

t_p: the step by which ceil(p x 63424) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 1862 | 0 | 70.3 | 917.9 | 23.3 | 26.6 | 347.9-357.9 |
| -x | 5.66 | 1854 | 0 | 70.5 | 899.9 | 23.7 | 26.6 | 260.1-270.1 |
| +y | 5.66 | 1839 | 0 | 70.5 | 900.8 | 23.5 | 25.5 | 79.1-89.0 |
| -y | 5.66 | 1872 | 0 | 70.5 | 904.4 | 23.8 | 25.5 | 80.1-90.1 |
| door +x+y (y wall) 0 | 2.30 | 1568 | 2577 | 4.9 | 979.5 | 42.0 | 60.2 | 16.4-26.4 |
| door +x+y (y wall) 1 | 2.30 | 1765 | 2137 | 4.9 | 1155.8 | 40.0 | 54.9 | 14.9-24.8 |
| door +x+y (y wall) 2 | 2.30 | 1528 | 1594 | 4.9 | 1149.1 | 34.8 | 57.6 | 19.1-29.0 |
| door +x+y (y wall) 3 | 2.30 | 1143 | 1045 | 4.9 | 1132.9 | 26.4 | 65.4 | 581.0-591.0 |
| door +x+y (y wall) 4 | 2.30 | 750 | 513 | 4.9 | 1132.0 | 17.4 | 57.6 | 19.1-29.0 |
| door +x+y (x wall) 0 | 2.30 | 1563 | 2577 | 4.9 | 990.1 | 41.4 | 54.9 | 13.3-23.3 |
| door +x+y (x wall) 1 | 2.30 | 1757 | 2137 | 4.9 | 1117.5 | 41.2 | 57.6 | 428.7-438.7 |
| door +x+y (x wall) 2 | 2.30 | 1525 | 1594 | 4.9 | 1152.1 | 34.7 | 60.2 | 18.0-28.0 |
| door +x+y (x wall) 3 | 2.30 | 1153 | 1045 | 4.9 | 1144.1 | 26.4 | 57.6 | 342.8-352.8 |
| door +x+y (x wall) 4 | 2.30 | 792 | 513 | 5.1 | 1143.5 | 18.1 | 57.6 | 27.3-37.3 |
| door +x+y (corner) | 2.30 | 472 | 124 | 6.3 | 852.8 | 14.5 | 57.6 | 75.9-85.9 |
| door -x+y (y wall) 0 | 2.30 | 1567 | 2577 | 4.9 | 988.4 | 41.6 | 57.6 | 11.7-21.7 |
| door -x+y (y wall) 1 | 2.30 | 1746 | 2137 | 4.9 | 1127.8 | 40.6 | 60.2 | 11.5-21.5 |
| door -x+y (y wall) 2 | 2.30 | 1499 | 1594 | 4.9 | 1115.2 | 35.2 | 60.2 | 11.5-21.5 |
| door -x+y (y wall) 3 | 2.30 | 1146 | 1045 | 4.9 | 1137.6 | 26.4 | 60.2 | 11.5-21.5 |
| door -x+y (y wall) 4 | 2.30 | 856 | 513 | 5.1 | 1058.4 | 21.2 | 60.2 | 504.3-514.2 |
| door -x+y (x wall) 0 | 2.30 | 1580 | 2577 | 4.9 | 997.7 | 41.5 | 57.6 | 14.2-24.1 |
| door -x+y (x wall) 1 | 2.30 | 1744 | 2137 | 4.9 | 1136.0 | 40.2 | 60.2 | 19.1-29.0 |
| door -x+y (x wall) 2 | 2.30 | 1465 | 1594 | 4.9 | 1079.5 | 35.6 | 57.6 | 24.0-33.9 |
| door -x+y (x wall) 3 | 2.30 | 1132 | 1045 | 4.9 | 1137.1 | 26.1 | 57.6 | 24.0-33.9 |
| door -x+y (x wall) 4 | 2.30 | 797 | 513 | 4.9 | 1134.6 | 18.4 | 60.2 | 25.2-35.2 |
| door -x+y (corner) | 2.30 | 486 | 124 | 6.3 | 994.3 | 12.8 | 60.2 | 184.0-194.0 |
| door -x-y (y wall) 0 | 2.30 | 1592 | 2577 | 4.9 | 1045.1 | 39.9 | 54.9 | 12.1-22.0 |
| door -x-y (y wall) 1 | 2.30 | 1784 | 2137 | 4.9 | 1123.8 | 41.6 | 60.2 | 16.6-26.6 |
| door -x-y (y wall) 2 | 2.30 | 1616 | 1594 | 4.9 | 1164.4 | 36.4 | 54.9 | 16.8-26.8 |
| door -x-y (y wall) 3 | 2.30 | 1079 | 1045 | 4.9 | 1172.2 | 24.1 | 60.2 | 16.6-26.6 |
| door -x-y (y wall) 4 | 2.30 | 744 | 513 | 4.9 | 1166.8 | 16.7 | 54.9 | 7.9-17.8 |
| door -x-y (x wall) 0 | 2.30 | 1575 | 2577 | 4.9 | 1046.1 | 39.5 | 60.2 | 11.5-21.5 |
| door -x-y (x wall) 1 | 2.30 | 1794 | 2137 | 4.9 | 1130.1 | 41.6 | 57.6 | 10.7-20.6 |
| door -x-y (x wall) 2 | 2.30 | 1534 | 1594 | 4.9 | 1170.8 | 34.3 | 57.6 | 10.7-20.6 |
| door -x-y (x wall) 3 | 2.30 | 1073 | 1045 | 4.9 | 1173.4 | 24.0 | 60.2 | 11.7-21.7 |
| door -x-y (x wall) 4 | 2.30 | 719 | 513 | 5.1 | 1115.7 | 16.9 | 57.6 | 16.8-26.8 |
| door -x-y (corner) | 2.30 | 483 | 124 | 6.3 | 1044.9 | 12.1 | 54.9 | 55.1-65.1 |
| door +x-y (y wall) 0 | 2.30 | 1581 | 2577 | 4.9 | 1009.6 | 41.0 | 57.6 | 10.7-20.6 |
| door +x-y (y wall) 1 | 2.30 | 1772 | 2137 | 4.9 | 1120.8 | 41.4 | 60.2 | 11.7-21.7 |
| door +x-y (y wall) 2 | 2.30 | 1612 | 1594 | 4.9 | 1189.9 | 35.5 | 57.6 | 20.3-30.3 |
| door +x-y (y wall) 3 | 2.30 | 1148 | 1045 | 4.9 | 1201.1 | 25.0 | 60.2 | 11.7-21.7 |
| door +x-y (y wall) 4 | 2.30 | 730 | 513 | 5.1 | 1171.2 | 16.3 | 60.2 | 18.0-28.0 |
| door +x-y (x wall) 0 | 2.30 | 1580 | 2577 | 4.9 | 989.6 | 41.8 | 60.2 | 17.8-27.8 |
| door +x-y (x wall) 1 | 2.30 | 1781 | 2137 | 4.9 | 1126.0 | 41.4 | 60.2 | 18.0-28.0 |
| door +x-y (x wall) 2 | 2.30 | 1564 | 1594 | 4.9 | 1193.2 | 34.3 | 57.6 | 452.5-462.5 |
| door +x-y (x wall) 3 | 2.30 | 1188 | 1045 | 4.9 | 1185.9 | 26.2 | 54.9 | 11.0-21.0 |
| door +x-y (x wall) 4 | 2.30 | 601 | 513 | 5.1 | 1198.6 | 13.1 | 54.9 | 5.8-15.7 |
| door +x-y (corner) | 2.30 | 413 | 124 | 6.5 | 1059.2 | 10.2 | 54.9 | 76.4-86.4 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (2.30 m; a corner door's: the gap between its wall ends, 2.30 m); agents are removed past the outer wall's outer face (92.71 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 1862 | 2.9% | 19.7% |
| -x | avenue | 5.66 | 1854 | 2.9% | 19.6% |
| +y | avenue | 5.66 | 1839 | 2.9% | 19.4% |
| -y | avenue | 5.66 | 1872 | 3.0% | 19.8% |
| door +x+y (y wall) 0 | door | 2.30 | 1568 | 2.5% | 40.7% |
| door +x+y (y wall) 1 | door | 2.30 | 1765 | 2.8% | 45.9% |
| door +x+y (y wall) 2 | door | 2.30 | 1528 | 2.4% | 39.7% |
| door +x+y (y wall) 3 | door | 2.30 | 1143 | 1.8% | 29.7% |
| door +x+y (y wall) 4 | door | 2.30 | 750 | 1.2% | 19.5% |
| door +x+y (x wall) 0 | door | 2.30 | 1563 | 2.5% | 40.6% |
| door +x+y (x wall) 1 | door | 2.30 | 1757 | 2.8% | 45.6% |
| door +x+y (x wall) 2 | door | 2.30 | 1525 | 2.4% | 39.6% |
| door +x+y (x wall) 3 | door | 2.30 | 1153 | 1.8% | 30.0% |
| door +x+y (x wall) 4 | door | 2.30 | 792 | 1.2% | 20.6% |
| door +x+y (corner) | door | 2.30 | 472 | 0.7% | 12.3% |
| door -x+y (y wall) 0 | door | 2.30 | 1567 | 2.5% | 40.7% |
| door -x+y (y wall) 1 | door | 2.30 | 1746 | 2.8% | 45.4% |
| door -x+y (y wall) 2 | door | 2.30 | 1499 | 2.4% | 38.9% |
| door -x+y (y wall) 3 | door | 2.30 | 1146 | 1.8% | 29.8% |
| door -x+y (y wall) 4 | door | 2.30 | 856 | 1.3% | 22.2% |
| door -x+y (x wall) 0 | door | 2.30 | 1580 | 2.5% | 41.0% |
| door -x+y (x wall) 1 | door | 2.30 | 1744 | 2.7% | 45.3% |
| door -x+y (x wall) 2 | door | 2.30 | 1465 | 2.3% | 38.1% |
| door -x+y (x wall) 3 | door | 2.30 | 1132 | 1.8% | 29.4% |
| door -x+y (x wall) 4 | door | 2.30 | 797 | 1.3% | 20.7% |
| door -x+y (corner) | door | 2.30 | 486 | 0.8% | 12.6% |
| door -x-y (y wall) 0 | door | 2.30 | 1592 | 2.5% | 41.4% |
| door -x-y (y wall) 1 | door | 2.30 | 1784 | 2.8% | 46.3% |
| door -x-y (y wall) 2 | door | 2.30 | 1616 | 2.5% | 42.0% |
| door -x-y (y wall) 3 | door | 2.30 | 1079 | 1.7% | 28.0% |
| door -x-y (y wall) 4 | door | 2.30 | 744 | 1.2% | 19.3% |
| door -x-y (x wall) 0 | door | 2.30 | 1575 | 2.5% | 40.9% |
| door -x-y (x wall) 1 | door | 2.30 | 1794 | 2.8% | 46.6% |
| door -x-y (x wall) 2 | door | 2.30 | 1534 | 2.4% | 39.9% |
| door -x-y (x wall) 3 | door | 2.30 | 1073 | 1.7% | 27.9% |
| door -x-y (x wall) 4 | door | 2.30 | 719 | 1.1% | 18.7% |
| door -x-y (corner) | door | 2.30 | 483 | 0.8% | 12.5% |
| door +x-y (y wall) 0 | door | 2.30 | 1581 | 2.5% | 41.1% |
| door +x-y (y wall) 1 | door | 2.30 | 1772 | 2.8% | 46.0% |
| door +x-y (y wall) 2 | door | 2.30 | 1612 | 2.5% | 41.9% |
| door +x-y (y wall) 3 | door | 2.30 | 1148 | 1.8% | 29.8% |
| door +x-y (y wall) 4 | door | 2.30 | 730 | 1.2% | 19.0% |
| door +x-y (x wall) 0 | door | 2.30 | 1580 | 2.5% | 41.0% |
| door +x-y (x wall) 1 | door | 2.30 | 1781 | 2.8% | 46.3% |
| door +x-y (x wall) 2 | door | 2.30 | 1564 | 2.5% | 40.6% |
| door +x-y (x wall) 3 | door | 2.30 | 1188 | 1.9% | 30.9% |
| door +x-y (x wall) 4 | door | 2.30 | 601 | 0.9% | 15.6% |
| door +x-y (corner) | door | 2.30 | 413 | 0.7% | 10.7% |
| **doors (44)** | door | 101.20 | 55997 | 88.3% | |
| **avenues (4)** | avenue | 22.64 | 7427 | 11.7% | |

**Unused exit width: 0.0 of 123.8 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 1201.1 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 30.6%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 2296 | 3.6% | 2296 | 3.6% |
| straight +x+y (y wing) 1 | straight | yes | 1888 | 3.0% | 1780 | 2.8% |
| straight +x+y (y wing) 2 | straight | yes | 1621 | 2.6% | 1594 | 2.5% |
| straight +x+y (y wing) 3 | straight | yes | 1127 | 1.8% | 1123 | 1.8% |
| straight +x+y (y wing) 4 | straight | yes | 719 | 1.1% | 704 | 1.1% |
| straight +x+y (x wing) 0 | straight | yes | 2307 | 3.6% | 2306 | 3.6% |
| straight +x+y (x wing) 1 | straight | yes | 1885 | 3.0% | 1774 | 2.8% |
| straight +x+y (x wing) 2 | straight | yes | 1609 | 2.5% | 1585 | 2.5% |
| straight +x+y (x wing) 3 | straight | yes | 1121 | 1.8% | 1110 | 1.8% |
| straight +x+y (x wing) 4 | straight | yes | 800 | 1.3% | 775 | 1.2% |
| corner +x+y | corner | yes | 2163 | 3.4% | 809 | 1.3% |
| straight -x+y (y wing) 0 | straight | yes | 2315 | 3.7% | 2315 | 3.7% |
| straight -x+y (y wing) 1 | straight | yes | 1868 | 2.9% | 1757 | 2.8% |
| straight -x+y (y wing) 2 | straight | yes | 1612 | 2.5% | 1576 | 2.5% |
| straight -x+y (y wing) 3 | straight | yes | 1154 | 1.8% | 1143 | 1.8% |
| straight -x+y (y wing) 4 | straight | yes | 807 | 1.3% | 782 | 1.2% |
| straight -x+y (x wing) 0 | straight | yes | 2312 | 3.6% | 2312 | 3.6% |
| straight -x+y (x wing) 1 | straight | yes | 1869 | 2.9% | 1771 | 2.8% |
| straight -x+y (x wing) 2 | straight | yes | 1580 | 2.5% | 1558 | 2.5% |
| straight -x+y (x wing) 3 | straight | yes | 1129 | 1.8% | 1109 | 1.7% |
| straight -x+y (x wing) 4 | straight | yes | 745 | 1.2% | 727 | 1.1% |
| corner -x+y | corner | yes | 2169 | 3.4% | 806 | 1.3% |
| straight -x-y (y wing) 0 | straight | yes | 2311 | 3.6% | 2311 | 3.6% |
| straight -x-y (y wing) 1 | straight | yes | 1923 | 3.0% | 1818 | 2.9% |
| straight -x-y (y wing) 2 | straight | yes | 1691 | 2.7% | 1686 | 2.7% |
| straight -x-y (y wing) 3 | straight | yes | 1084 | 1.7% | 1066 | 1.7% |
| straight -x-y (y wing) 4 | straight | yes | 703 | 1.1% | 687 | 1.1% |
| straight -x-y (x wing) 0 | straight | yes | 2318 | 3.7% | 2318 | 3.7% |
| straight -x-y (x wing) 1 | straight | yes | 1929 | 3.0% | 1818 | 2.9% |
| straight -x-y (x wing) 2 | straight | yes | 1634 | 2.6% | 1625 | 2.6% |
| straight -x-y (x wing) 3 | straight | yes | 1087 | 1.7% | 1061 | 1.7% |
| straight -x-y (x wing) 4 | straight | yes | 658 | 1.0% | 640 | 1.0% |
| corner -x-y | corner | yes | 2068 | 3.3% | 826 | 1.3% |
| straight +x-y (y wing) 0 | straight | yes | 2336 | 3.7% | 2335 | 3.7% |
| straight +x-y (y wing) 1 | straight | yes | 1899 | 3.0% | 1796 | 2.8% |
| straight +x-y (y wing) 2 | straight | yes | 1650 | 2.6% | 1643 | 2.6% |
| straight +x-y (y wing) 3 | straight | yes | 1152 | 1.8% | 1149 | 1.8% |
| straight +x-y (y wing) 4 | straight | yes | 716 | 1.1% | 698 | 1.1% |
| straight +x-y (x wing) 0 | straight | yes | 2325 | 3.7% | 2325 | 3.7% |
| straight +x-y (x wing) 1 | straight | yes | 1911 | 3.0% | 1803 | 2.8% |
| straight +x-y (x wing) 2 | straight | yes | 1640 | 2.6% | 1629 | 2.6% |
| straight +x-y (x wing) 3 | straight | yes | 1138 | 1.8% | 1131 | 1.8% |
| straight +x-y (x wing) 4 | straight | yes | 608 | 1.0% | 593 | 0.9% |
| corner +x-y | corner | yes | 2049 | 3.2% | 754 | 1.2% |
| **straight (40)** | | | 61477 | | 60229 | 95.0% |
| **corner (4)** | | | 8449 | | 3195 | 5.0% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 1862 | 70.3 | 917.9 | 0.28 | 0.32 | 0.0% |
| -x | 1854 | 70.5 | 899.9 | 0.28 | 0.32 | 0.0% |
| +y | 1839 | 70.5 | 900.8 | 0.28 | 0.31 | 0.0% |
| -y | 1872 | 70.5 | 904.4 | 0.28 | 0.31 | 0.0% |
| door +x+y (y wall) 0 | 1568 | 4.9 | 979.5 | 0.50 | 0.72 | 0.0% |
| door +x+y (y wall) 1 | 1765 | 4.9 | 1155.8 | 0.48 | 0.66 | 0.0% |
| door +x+y (y wall) 2 | 1528 | 4.9 | 1149.1 | 0.42 | 0.69 | 0.0% |
| door +x+y (y wall) 3 | 1143 | 4.9 | 1132.9 | 0.32 | 0.78 | 0.0% |
| door +x+y (y wall) 4 | 750 | 4.9 | 1132.0 | 0.21 | 0.69 | 0.0% |
| door +x+y (x wall) 0 | 1563 | 4.9 | 990.1 | 0.49 | 0.66 | 0.0% |
| door +x+y (x wall) 1 | 1757 | 4.9 | 1117.5 | 0.49 | 0.69 | 0.0% |
| door +x+y (x wall) 2 | 1525 | 4.9 | 1152.1 | 0.41 | 0.72 | 0.0% |
| door +x+y (x wall) 3 | 1153 | 4.9 | 1144.1 | 0.32 | 0.69 | 0.0% |
| door +x+y (x wall) 4 | 792 | 5.1 | 1143.5 | 0.22 | 0.69 | 0.0% |
| door +x+y (corner) | 472 | 6.3 | 852.8 | 0.17 | 0.69 | 0.0% |
| door -x+y (y wall) 0 | 1567 | 4.9 | 988.4 | 0.50 | 0.69 | 0.0% |
| door -x+y (y wall) 1 | 1746 | 4.9 | 1127.8 | 0.49 | 0.72 | 0.0% |
| door -x+y (y wall) 2 | 1499 | 4.9 | 1115.2 | 0.42 | 0.72 | 0.0% |
| door -x+y (y wall) 3 | 1146 | 4.9 | 1137.6 | 0.32 | 0.72 | 0.0% |
| door -x+y (y wall) 4 | 856 | 5.1 | 1058.4 | 0.25 | 0.72 | 0.0% |
| door -x+y (x wall) 0 | 1580 | 4.9 | 997.7 | 0.50 | 0.69 | 0.0% |
| door -x+y (x wall) 1 | 1744 | 4.9 | 1136.0 | 0.48 | 0.72 | 0.0% |
| door -x+y (x wall) 2 | 1465 | 4.9 | 1079.5 | 0.43 | 0.69 | 0.0% |
| door -x+y (x wall) 3 | 1132 | 4.9 | 1137.1 | 0.31 | 0.69 | 0.0% |
| door -x+y (x wall) 4 | 797 | 4.9 | 1134.6 | 0.22 | 0.72 | 0.0% |
| door -x+y (corner) | 486 | 6.3 | 994.3 | 0.15 | 0.72 | 0.0% |
| door -x-y (y wall) 0 | 1592 | 4.9 | 1045.1 | 0.48 | 0.66 | 0.0% |
| door -x-y (y wall) 1 | 1784 | 4.9 | 1123.8 | 0.50 | 0.72 | 0.0% |
| door -x-y (y wall) 2 | 1616 | 4.9 | 1164.4 | 0.43 | 0.66 | 0.0% |
| door -x-y (y wall) 3 | 1079 | 4.9 | 1172.2 | 0.29 | 0.72 | 0.0% |
| door -x-y (y wall) 4 | 744 | 4.9 | 1166.8 | 0.20 | 0.66 | 0.0% |
| door -x-y (x wall) 0 | 1575 | 4.9 | 1046.1 | 0.47 | 0.72 | 0.0% |
| door -x-y (x wall) 1 | 1794 | 4.9 | 1130.1 | 0.50 | 0.69 | 0.0% |
| door -x-y (x wall) 2 | 1534 | 4.9 | 1170.8 | 0.41 | 0.69 | 0.0% |
| door -x-y (x wall) 3 | 1073 | 4.9 | 1173.4 | 0.29 | 0.72 | 0.0% |
| door -x-y (x wall) 4 | 719 | 5.1 | 1115.7 | 0.20 | 0.69 | 0.0% |
| door -x-y (corner) | 483 | 6.3 | 1044.9 | 0.15 | 0.66 | 0.0% |
| door +x-y (y wall) 0 | 1581 | 4.9 | 1009.6 | 0.49 | 0.69 | 0.0% |
| door +x-y (y wall) 1 | 1772 | 4.9 | 1120.8 | 0.50 | 0.72 | 0.0% |
| door +x-y (y wall) 2 | 1612 | 4.9 | 1189.9 | 0.42 | 0.69 | 0.0% |
| door +x-y (y wall) 3 | 1148 | 4.9 | 1201.1 | 0.30 | 0.72 | 0.0% |
| door +x-y (y wall) 4 | 730 | 5.1 | 1171.2 | 0.20 | 0.72 | 0.0% |
| door +x-y (x wall) 0 | 1580 | 4.9 | 989.6 | 0.50 | 0.72 | 0.0% |
| door +x-y (x wall) 1 | 1781 | 4.9 | 1126.0 | 0.50 | 0.72 | 0.0% |
| door +x-y (x wall) 2 | 1564 | 4.9 | 1193.2 | 0.41 | 0.69 | 0.0% |
| door +x-y (x wall) 3 | 1188 | 4.9 | 1185.9 | 0.31 | 0.66 | 0.0% |
| door +x-y (x wall) 4 | 601 | 5.1 | 1198.6 | 0.16 | 0.66 | 0.0% |
| door +x-y (corner) | 413 | 6.5 | 1059.2 | 0.12 | 0.66 | 0.0% |

Mean flow / w J averaged over the doors 0.36, over the avenues 0.28.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 103.1 | 2296 | 1553 / 744 / 734 | 0.7 | 884.2 | 3.43 | 5.42 | 90% | 87% | 3% | 4.65 |
| straight +x+y (y wing) 1 | 1.20 | 81.5 | 1871 | 1780 / 0 / 238 | 0.7 | 1152.8 | 1.75 | 3.81 | 87% | 73% | 14% | 3.82 |
| straight +x+y (y wing) 2 | 1.20 | 61.0 | 1530 | 1594 / 0 / 48 | 0.7 | 1146.2 | 1.43 | 2.91 | 77% | 64% | 12% | 3.84 |
| straight +x+y (y wing) 3 | 1.20 | 39.4 | 925 | 1123 / 0 / 9 | 0.7 | 1129.9 | 1.00 | 2.21 | 50% | 41% | 9% | 3.58 |
| straight +x+y (y wing) 4 | 1.20 | 18.8 | 392 | 704 / 0 / 21 | 0.7 | 1129.0 | 0.64 | 2.11 | 17% | 16% | 1% | 4.10 |
| straight +x+y (x wing) 0 | 1.20 | 103.1 | 2307 | 1546 / 760 / 932 | 0.7 | 891.7 | 3.63 | 6.02 | 90% | 84% | 6% | 4.50 |
| straight +x+y (x wing) 1 | 1.20 | 81.5 | 1869 | 1774 / 0 / 234 | 0.7 | 1114.5 | 1.80 | 3.51 | 90% | 77% | 13% | 3.84 |
| straight +x+y (x wing) 2 | 1.20 | 61.0 | 1526 | 1585 / 0 / 30 | 0.7 | 1149.1 | 1.41 | 2.41 | 75% | 66% | 9% | 3.89 |
| straight +x+y (x wing) 3 | 1.20 | 39.4 | 929 | 1110 / 0 / 17 | 0.7 | 1141.1 | 0.99 | 2.11 | 50% | 38% | 11% | 3.56 |
| straight +x+y (x wing) 4 | 1.20 | 18.8 | 402 | 775 / 0 / 28 | 0.7 | 1140.6 | 0.70 | 2.31 | 17% | 16% | 1% | 4.03 |
| corner +x+y | 1.20 | 186.0 | 1809 | 472 / 337 / 1439 | 0.7 | 1116.6 | 2.01 | 4.41 | 92% | 64% | 28% | 2.65 |
| straight -x+y (y wing) 0 | 1.20 | 103.1 | 2315 | 1556 / 760 / 981 | 0.7 | 893.8 | 3.69 | 6.32 | 90% | 86% | 4% | 4.45 |
| straight -x+y (y wing) 1 | 1.20 | 81.5 | 1855 | 1757 / 0 / 255 | 0.7 | 1124.8 | 1.79 | 4.01 | 88% | 75% | 12% | 3.90 |
| straight -x+y (y wing) 2 | 1.20 | 61.0 | 1517 | 1576 / 0 / 44 | 0.7 | 1112.2 | 1.46 | 2.41 | 77% | 67% | 10% | 3.70 |
| straight -x+y (y wing) 3 | 1.20 | 39.4 | 944 | 1143 / 0 / 13 | 0.7 | 1134.6 | 1.02 | 2.41 | 47% | 40% | 7% | 3.78 |
| straight -x+y (y wing) 4 | 1.20 | 18.8 | 404 | 782 / 0 / 26 | 0.7 | 1055.4 | 0.77 | 2.31 | 19% | 18% | 1% | 3.93 |
| straight -x+y (x wing) 0 | 1.20 | 103.1 | 2312 | 1553 / 759 / 772 | 0.7 | 871.7 | 3.54 | 5.42 | 90% | 86% | 3% | 4.60 |
| straight -x+y (x wing) 1 | 1.20 | 81.5 | 1850 | 1771 / 0 / 212 | 0.7 | 1133.0 | 1.75 | 3.81 | 90% | 74% | 17% | 3.90 |
| straight -x+y (x wing) 2 | 1.20 | 61.0 | 1528 | 1558 / 0 / 28 | 0.7 | 1076.6 | 1.47 | 2.21 | 82% | 72% | 10% | 3.96 |
| straight -x+y (x wing) 3 | 1.20 | 39.4 | 932 | 1109 / 0 / 20 | 0.7 | 1134.1 | 1.00 | 2.21 | 46% | 41% | 5% | 3.92 |
| straight -x+y (x wing) 4 | 1.20 | 18.8 | 391 | 727 / 0 / 18 | 0.7 | 1131.6 | 0.66 | 2.21 | 17% | 16% | 1% | 4.06 |
| corner -x+y | 1.20 | 186.0 | 1808 | 486 / 320 / 1482 | 0.7 | 1107.9 | 2.07 | 4.31 | 88% | 60% | 29% | 2.66 |
| straight -x-y (y wing) 0 | 1.20 | 103.1 | 2310 | 1558 / 754 / 858 | 0.7 | 856.3 | 3.70 | 5.72 | 90% | 90% | 0% | 4.72 |
| straight -x-y (y wing) 1 | 1.20 | 81.5 | 1894 | 1818 / 0 / 241 | 0.7 | 1120.8 | 1.84 | 3.81 | 91% | 78% | 13% | 3.70 |
| straight -x-y (y wing) 2 | 1.20 | 61.0 | 1532 | 1686 / 0 / 12 | 0.7 | 1161.4 | 1.46 | 2.11 | 74% | 68% | 7% | 4.00 |
| straight -x-y (y wing) 3 | 1.20 | 39.4 | 930 | 1066 / 0 / 23 | 0.7 | 1169.3 | 0.93 | 2.41 | 58% | 38% | 20% | 3.00 |
| straight -x-y (y wing) 4 | 1.20 | 18.8 | 382 | 687 / 0 / 18 | 0.7 | 1163.8 | 0.61 | 2.11 | 17% | 16% | 1% | 3.95 |
| straight -x-y (x wing) 0 | 1.20 | 103.1 | 2318 | 1551 / 767 / 881 | 0.7 | 868.6 | 3.69 | 6.02 | 89% | 88% | 1% | 4.56 |
| straight -x-y (x wing) 1 | 1.20 | 81.5 | 1899 | 1818 / 0 / 232 | 0.7 | 1127.1 | 1.82 | 3.41 | 89% | 75% | 14% | 3.81 |
| straight -x-y (x wing) 2 | 1.20 | 61.0 | 1506 | 1625 / 0 / 17 | 0.7 | 1167.9 | 1.41 | 2.31 | 74% | 67% | 7% | 3.82 |
| straight -x-y (x wing) 3 | 1.20 | 39.4 | 954 | 1061 / 0 / 49 | 0.7 | 1170.5 | 0.95 | 2.31 | 49% | 42% | 7% | 3.65 |
| straight -x-y (x wing) 4 | 1.20 | 18.8 | 402 | 640 / 0 / 19 | 0.7 | 1112.8 | 0.59 | 2.11 | 19% | 18% | 1% | 3.81 |
| corner -x-y | 1.20 | 186.0 | 1729 | 483 / 346 / 1336 | 0.7 | 1140.0 | 1.90 | 4.41 | 90% | 72% | 18% | 2.79 |
| straight +x-y (y wing) 0 | 1.20 | 103.1 | 2336 | 1557 / 780 / 1034 | 0.7 | 878.9 | 3.84 | 6.32 | 89% | 88% | 1% | 4.51 |
| straight +x-y (y wing) 1 | 1.20 | 81.5 | 1877 | 1796 / 0 / 216 | 0.7 | 1117.8 | 1.80 | 3.81 | 90% | 73% | 18% | 3.68 |
| straight +x-y (y wing) 2 | 1.20 | 61.0 | 1525 | 1643 / 0 / 14 | 0.7 | 1186.9 | 1.40 | 2.21 | 70% | 64% | 6% | 3.87 |
| straight +x-y (y wing) 3 | 1.20 | 39.4 | 937 | 1149 / 0 / 15 | 0.7 | 1198.1 | 0.97 | 2.31 | 45% | 38% | 7% | 3.75 |
| straight +x-y (y wing) 4 | 1.20 | 18.8 | 389 | 698 / 0 / 20 | 0.7 | 1168.2 | 0.61 | 2.31 | 17% | 14% | 3% | 3.70 |
| straight +x-y (x wing) 0 | 1.20 | 103.1 | 2325 | 1558 / 767 / 834 | 0.7 | 892.7 | 3.54 | 6.12 | 90% | 87% | 3% | 4.52 |
| straight +x-y (x wing) 1 | 1.20 | 81.5 | 1886 | 1803 / 0 / 226 | 0.7 | 1123.1 | 1.81 | 3.61 | 91% | 73% | 18% | 3.78 |
| straight +x-y (x wing) 2 | 1.20 | 61.0 | 1517 | 1629 / 0 / 22 | 0.7 | 1190.2 | 1.39 | 2.21 | 70% | 64% | 6% | 4.06 |
| straight +x-y (x wing) 3 | 1.20 | 39.4 | 934 | 1131 / 0 / 11 | 0.7 | 1182.9 | 0.97 | 2.11 | 42% | 37% | 5% | 3.89 |
| straight +x-y (x wing) 4 | 1.20 | 18.8 | 395 | 593 / 0 / 24 | 0.7 | 1195.7 | 0.52 | 2.21 | 26% | 15% | 11% | 2.63 |
| corner +x-y | 1.20 | 186.0 | 1735 | 413 / 341 / 1358 | 0.7 | 1171.7 | 1.80 | 4.71 | 91% | 67% | 24% | 2.76 |

The last agent out (agent 48440, t100 1201.1 s): last gangway straight +x-y (y wing) 3, exit door +x-y (y wall) 3. The gangway that cleared last: straight +x-y (y wing) 3 at 1198.1 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 8804 | 7800.4 | 7.10 | 1197.9 / 1130.6 / 1070.6 | 1104.9 / 1094.7 / 1048.6 | 5222975.1 | 10843981 | 0.203 |
| gangway | 3792 | 3512.9 | 7.10 | 1196.5 / 1130.6 / 1070.6 | 1104.9 / 1094.7 / 1048.6 | 5222975.1 | 10100685 | 0.131 |
| walkway | 276 | 257.4 | 4.04 | 580.0 / 368.4 / 0.0 | 420.1 / 205.9 / 0.0 | 0.0 | 78360 | 0.667 |
| avenue | 1920 | 1801.4 | 2.11 | 783.4 / 0.0 / 0.0 | 584.7 / 0.0 / 0.0 | 0.0 | 445134 | 1.334 |
| exit | 4 | 2.0 | 0.00 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 0 | - |
| concourse | 2812 | 2226.8 | 3.06 | 1180.1 / 104.4 / 0.0 | 974.2 / 20.8 / 0.0 | 0.0 | 219803 | 1.048 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 25392 | 16030.4 | 7.67 | 1066.1 / 1050.5 / 1014.5 | 1059.8 / 1050.5 / 1005.0 | 6709117.0 | 16836018 | 0.029 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 208 x 208 from (-104, -104) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -34.5 | -34.5 | gangway | 1.00 | 5.99 | 1046.5 | 1038.8 | 998.5 | 5778.1 | 0.007 |
| 2 | 34.5 | 34.5 | gangway | 1.00 | 5.86 | 1040.0 | 1031.4 | 1009.4 | 5749.0 | 0.011 |
| 3 | 34.5 | -34.5 | gangway | 1.00 | 5.65 | 1081.3 | 1073.2 | 1031.2 | 5660.3 | 0.007 |
| 4 | 38.5 | -38.5 | gangway | 1.00 | 5.99 | 1100.3 | 1094.7 | 975.6 | 5653.5 | 0.014 |
| 5 | -46.5 | -46.5 | gangway | 1.00 | 6.02 | 1025.7 | 1015.7 | 960.8 | 5553.0 | 0.012 |
| 6 | 35.5 | -35.5 | gangway | 1.00 | 5.79 | 1090.0 | 1084.9 | 992.4 | 5534.5 | 0.008 |
| 7 | 39.5 | -39.5 | gangway | 1.00 | 5.83 | 1102.4 | 1094.2 | 968.6 | 5460.8 | 0.018 |
| 8 | -38.5 | -38.5 | gangway | 1.00 | 5.90 | 1075.5 | 1073.4 | 969.3 | 5434.9 | 0.013 |
| 9 | -39.5 | -39.5 | gangway | 1.00 | 5.75 | 1079.0 | 1077.1 | 954.5 | 5377.4 | 0.018 |
| 10 | -47.5 | -47.5 | gangway | 1.00 | 5.76 | 1031.9 | 1022.2 | 969.2 | 5353.7 | 0.016 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 36.5 | 38.5 | seat row | 0.50 | 7.29 | 1008.2 | 1000.6 | 983.7 | 3522.1 | 0.006 |
| 2 | 38.5 | -36.5 | seat row | 0.50 | 7.18 | 1059.8 | 1050.5 | 1005.0 | 3518.9 | 0.003 |
| 3 | -38.5 | -36.5 | seat row | 0.50 | 7.20 | 1021.8 | 1002.4 | 976.3 | 3453.0 | 0.004 |
| 4 | -36.5 | -38.5 | seat row | 0.50 | 7.01 | 1013.6 | 1006.2 | 992.4 | 3408.3 | 0.005 |
| 5 | 38.5 | 36.5 | seat row | 0.50 | 7.23 | 1006.9 | 998.7 | 977.9 | 3404.5 | 0.006 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 7872; agent-steps of seated agents on another row's clearway: 1826203.

## Deposit check

Person-seconds deposited: 27685850.9, of them in excluded cells: 5851.975.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 6308690 overlapping pair-steps: p99 0.0031, max 0.1323 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0031 max 0.1323; venue-geometry 11: p99 0.0012 max 0.0012 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00757 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 61 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.42 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 3774 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
