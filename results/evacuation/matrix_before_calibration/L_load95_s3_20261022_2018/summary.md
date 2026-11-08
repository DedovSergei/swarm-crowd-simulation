# Experiment `L_load95_s3`

**Task 5.10 stage 4 (AMD 26.10.1): Task 5.8's model (the level spacing on the gangway inclines, --stair-flow off): venue L, 95% load (seed 3)**

Venue L (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (4000 x 4000), cache key a2f3aaf59c2252b7, content hash 022d17b202313d70). 60253 agents on 95% of the 63424 seats (spawnSeatedCrowd, seed 3), buffer N = 65536, 6923 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 8475383 evaluations, 481177 switches, 0 forced choices).
Capacity: **within design capacity** (the L venue's design capacity 63424, jam capacity 171923: 23822.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T20:18:10, 706.5 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 2238 | 391.4 |
| t90 | 4581 | 801.2 |
| t100 | 6923 | 1210.9 |

t_p: the step by which ceil(p x 60253) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 1748 | 0 | 70.3 | 873.8 | 23.1 | 25.5 | 75.7-85.7 |
| -x | 5.66 | 1753 | 0 | 70.5 | 861.2 | 23.5 | 26.6 | 78.0-88.0 |
| +y | 5.66 | 1768 | 0 | 70.5 | 870.2 | 23.4 | 25.5 | 76.3-86.2 |
| -y | 5.66 | 1755 | 0 | 70.5 | 861.1 | 23.5 | 26.6 | 83.8-93.7 |
| door +x+y (y wall) 0 | 2.30 | 1536 | 2455 | 4.9 | 1012.0 | 39.8 | 57.6 | 22.7-32.7 |
| door +x+y (y wall) 1 | 2.30 | 1715 | 2043 | 4.9 | 1032.6 | 43.5 | 54.9 | 4.5-14.5 |
| door +x+y (y wall) 2 | 2.30 | 1569 | 1511 | 4.9 | 1160.2 | 35.4 | 54.9 | 8.0-18.0 |
| door +x+y (y wall) 3 | 2.30 | 1048 | 983 | 4.9 | 1206.7 | 22.7 | 57.6 | 7.9-17.8 |
| door +x+y (y wall) 4 | 2.30 | 615 | 480 | 5.1 | 1201.1 | 13.4 | 60.2 | 279.9-289.8 |
| door +x+y (x wall) 0 | 2.30 | 1510 | 2431 | 4.9 | 1004.7 | 39.4 | 57.6 | 29.4-39.4 |
| door +x+y (x wall) 1 | 2.30 | 1706 | 2045 | 4.9 | 1049.1 | 42.6 | 57.6 | 22.7-32.7 |
| door +x+y (x wall) 2 | 2.30 | 1582 | 1502 | 4.9 | 1161.2 | 35.7 | 57.6 | 566.2-576.1 |
| door +x+y (x wall) 3 | 2.30 | 1002 | 1000 | 4.9 | 1210.9 | 21.7 | 57.6 | 11.2-21.2 |
| door +x+y (x wall) 4 | 2.30 | 644 | 486 | 5.1 | 1203.4 | 14.0 | 57.6 | 10.8-20.8 |
| door +x+y (corner) | 2.30 | 391 | 118 | 6.3 | 1210.0 | 8.5 | 54.9 | 67.0-77.0 |
| door -x+y (y wall) 0 | 2.30 | 1492 | 2467 | 4.9 | 959.7 | 40.8 | 57.6 | 19.8-29.7 |
| door -x+y (y wall) 1 | 2.30 | 1709 | 2035 | 4.9 | 1101.2 | 40.7 | 57.6 | 8.0-18.0 |
| door -x+y (y wall) 2 | 2.30 | 1514 | 1508 | 4.9 | 1124.8 | 35.3 | 57.6 | 9.3-19.2 |
| door -x+y (y wall) 3 | 2.30 | 1103 | 1001 | 4.9 | 1079.5 | 26.8 | 54.9 | 11.4-21.3 |
| door -x+y (y wall) 4 | 2.30 | 653 | 481 | 5.1 | 1094.9 | 15.6 | 57.6 | 7.3-17.3 |
| door -x+y (x wall) 0 | 2.30 | 1512 | 2460 | 4.9 | 950.1 | 41.7 | 57.6 | 15.2-25.2 |
| door -x+y (x wall) 1 | 2.30 | 1704 | 2022 | 4.9 | 1098.8 | 40.6 | 57.6 | 22.2-32.2 |
| door -x+y (x wall) 2 | 2.30 | 1499 | 1499 | 4.9 | 1126.4 | 34.9 | 54.9 | 25.7-35.7 |
| door -x+y (x wall) 3 | 2.30 | 1135 | 1001 | 4.9 | 1098.4 | 27.1 | 60.2 | 16.4-26.4 |
| door -x+y (x wall) 4 | 2.30 | 626 | 479 | 4.9 | 1098.8 | 14.9 | 54.9 | 7.2-17.1 |
| door -x+y (corner) | 2.30 | 356 | 119 | 6.3 | 891.8 | 10.5 | 52.3 | 21.3-31.3 |
| door -x-y (y wall) 0 | 2.30 | 1507 | 2461 | 4.9 | 956.2 | 41.3 | 54.9 | 16.8-26.8 |
| door -x-y (y wall) 1 | 2.30 | 1677 | 2005 | 4.9 | 1047.5 | 42.0 | 54.9 | 10.8-20.8 |
| door -x-y (y wall) 2 | 2.30 | 1438 | 1528 | 4.7 | 1120.6 | 33.6 | 57.6 | 25.0-35.0 |
| door -x-y (y wall) 3 | 2.30 | 1128 | 982 | 4.9 | 1129.2 | 26.2 | 57.6 | 20.8-30.8 |
| door -x-y (y wall) 4 | 2.30 | 661 | 489 | 4.9 | 1092.6 | 15.8 | 57.6 | 12.9-22.9 |
| door -x-y (x wall) 0 | 2.30 | 1486 | 2455 | 4.9 | 948.0 | 41.1 | 57.6 | 20.5-30.4 |
| door -x-y (x wall) 1 | 2.30 | 1667 | 2027 | 5.1 | 1069.0 | 40.9 | 57.6 | 7.0-17.0 |
| door -x-y (x wall) 2 | 2.30 | 1461 | 1514 | 4.9 | 1111.0 | 34.5 | 57.6 | 20.5-30.4 |
| door -x-y (x wall) 3 | 2.30 | 1015 | 998 | 4.9 | 1086.2 | 24.5 | 57.6 | 26.4-36.4 |
| door -x-y (x wall) 4 | 2.30 | 792 | 487 | 5.1 | 1129.4 | 18.4 | 54.9 | 24.8-34.8 |
| door -x-y (corner) | 2.30 | 501 | 118 | 6.3 | 893.9 | 14.7 | 54.9 | 82.4-92.4 |
| door +x-y (y wall) 0 | 2.30 | 1504 | 2439 | 4.9 | 956.7 | 41.2 | 54.9 | 19.6-29.6 |
| door +x-y (y wall) 1 | 2.30 | 1676 | 2026 | 4.9 | 1079.2 | 40.7 | 57.6 | 23.3-33.2 |
| door +x-y (y wall) 2 | 2.30 | 1493 | 1517 | 4.9 | 1113.1 | 35.1 | 60.2 | 14.2-24.1 |
| door +x-y (y wall) 3 | 2.30 | 1089 | 998 | 4.9 | 1094.2 | 26.1 | 60.2 | 11.7-21.7 |
| door +x-y (y wall) 4 | 2.30 | 723 | 488 | 5.1 | 1073.4 | 17.7 | 57.6 | 10.3-20.3 |
| door +x-y (x wall) 0 | 2.30 | 1516 | 2440 | 4.9 | 964.8 | 41.2 | 54.9 | 11.0-21.0 |
| door +x-y (x wall) 1 | 2.30 | 1691 | 2030 | 4.9 | 1080.7 | 41.0 | 60.2 | 10.3-20.3 |
| door +x-y (x wall) 2 | 2.30 | 1493 | 1519 | 4.9 | 1107.2 | 35.3 | 54.9 | 11.4-21.3 |
| door +x-y (x wall) 3 | 2.30 | 1045 | 993 | 4.9 | 1110.3 | 24.7 | 57.6 | 17.7-27.6 |
| door +x-y (x wall) 4 | 2.30 | 626 | 490 | 5.1 | 1036.3 | 15.8 | 57.6 | 16.1-26.1 |
| door +x-y (corner) | 2.30 | 419 | 123 | 6.5 | 922.3 | 11.9 | 54.9 | 88.0-97.9 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (2.30 m; a corner door's: the gap between its wall ends, 2.30 m); agents are removed past the outer wall's outer face (92.71 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 1748 | 2.9% | 18.3% |
| -x | avenue | 5.66 | 1753 | 2.9% | 18.4% |
| +y | avenue | 5.66 | 1768 | 2.9% | 18.5% |
| -y | avenue | 5.66 | 1755 | 2.9% | 18.4% |
| door +x+y (y wall) 0 | door | 2.30 | 1536 | 2.5% | 39.6% |
| door +x+y (y wall) 1 | door | 2.30 | 1715 | 2.8% | 44.2% |
| door +x+y (y wall) 2 | door | 2.30 | 1569 | 2.6% | 40.4% |
| door +x+y (y wall) 3 | door | 2.30 | 1048 | 1.7% | 27.0% |
| door +x+y (y wall) 4 | door | 2.30 | 615 | 1.0% | 15.8% |
| door +x+y (x wall) 0 | door | 2.30 | 1510 | 2.5% | 38.9% |
| door +x+y (x wall) 1 | door | 2.30 | 1706 | 2.8% | 44.0% |
| door +x+y (x wall) 2 | door | 2.30 | 1582 | 2.6% | 40.8% |
| door +x+y (x wall) 3 | door | 2.30 | 1002 | 1.7% | 25.8% |
| door +x+y (x wall) 4 | door | 2.30 | 644 | 1.1% | 16.6% |
| door +x+y (corner) | door | 2.30 | 391 | 0.6% | 10.1% |
| door -x+y (y wall) 0 | door | 2.30 | 1492 | 2.5% | 38.4% |
| door -x+y (y wall) 1 | door | 2.30 | 1709 | 2.8% | 44.0% |
| door -x+y (y wall) 2 | door | 2.30 | 1514 | 2.5% | 39.0% |
| door -x+y (y wall) 3 | door | 2.30 | 1103 | 1.8% | 28.4% |
| door -x+y (y wall) 4 | door | 2.30 | 653 | 1.1% | 16.8% |
| door -x+y (x wall) 0 | door | 2.30 | 1512 | 2.5% | 39.0% |
| door -x+y (x wall) 1 | door | 2.30 | 1704 | 2.8% | 43.9% |
| door -x+y (x wall) 2 | door | 2.30 | 1499 | 2.5% | 38.6% |
| door -x+y (x wall) 3 | door | 2.30 | 1135 | 1.9% | 29.2% |
| door -x+y (x wall) 4 | door | 2.30 | 626 | 1.0% | 16.1% |
| door -x+y (corner) | door | 2.30 | 356 | 0.6% | 9.2% |
| door -x-y (y wall) 0 | door | 2.30 | 1507 | 2.5% | 38.8% |
| door -x-y (y wall) 1 | door | 2.30 | 1677 | 2.8% | 43.2% |
| door -x-y (y wall) 2 | door | 2.30 | 1438 | 2.4% | 37.1% |
| door -x-y (y wall) 3 | door | 2.30 | 1128 | 1.9% | 29.1% |
| door -x-y (y wall) 4 | door | 2.30 | 661 | 1.1% | 17.0% |
| door -x-y (x wall) 0 | door | 2.30 | 1486 | 2.5% | 38.3% |
| door -x-y (x wall) 1 | door | 2.30 | 1667 | 2.8% | 43.0% |
| door -x-y (x wall) 2 | door | 2.30 | 1461 | 2.4% | 37.7% |
| door -x-y (x wall) 3 | door | 2.30 | 1015 | 1.7% | 26.2% |
| door -x-y (x wall) 4 | door | 2.30 | 792 | 1.3% | 20.4% |
| door -x-y (corner) | door | 2.30 | 501 | 0.8% | 12.9% |
| door +x-y (y wall) 0 | door | 2.30 | 1504 | 2.5% | 38.8% |
| door +x-y (y wall) 1 | door | 2.30 | 1676 | 2.8% | 43.2% |
| door +x-y (y wall) 2 | door | 2.30 | 1493 | 2.5% | 38.5% |
| door +x-y (y wall) 3 | door | 2.30 | 1089 | 1.8% | 28.1% |
| door +x-y (y wall) 4 | door | 2.30 | 723 | 1.2% | 18.6% |
| door +x-y (x wall) 0 | door | 2.30 | 1516 | 2.5% | 39.1% |
| door +x-y (x wall) 1 | door | 2.30 | 1691 | 2.8% | 43.6% |
| door +x-y (x wall) 2 | door | 2.30 | 1493 | 2.5% | 38.5% |
| door +x-y (x wall) 3 | door | 2.30 | 1045 | 1.7% | 26.9% |
| door +x-y (x wall) 4 | door | 2.30 | 626 | 1.0% | 16.1% |
| door +x-y (corner) | door | 2.30 | 419 | 0.7% | 10.8% |
| **doors (44)** | door | 101.20 | 53229 | 88.3% | |
| **avenues (4)** | avenue | 22.64 | 7024 | 11.7% | |

**Unused exit width: 0.0 of 123.8 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 1210.9 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 28.8%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 2221 | 3.7% | 2221 | 3.7% |
| straight +x+y (y wing) 1 | straight | yes | 1819 | 3.0% | 1755 | 2.9% |
| straight +x+y (y wing) 2 | straight | yes | 1644 | 2.7% | 1642 | 2.7% |
| straight +x+y (y wing) 3 | straight | yes | 1008 | 1.7% | 1000 | 1.7% |
| straight +x+y (y wing) 4 | straight | yes | 602 | 1.0% | 590 | 1.0% |
| straight +x+y (x wing) 0 | straight | yes | 2222 | 3.7% | 2222 | 3.7% |
| straight +x+y (x wing) 1 | straight | yes | 1811 | 3.0% | 1741 | 2.9% |
| straight +x+y (x wing) 2 | straight | yes | 1647 | 2.7% | 1644 | 2.7% |
| straight +x+y (x wing) 3 | straight | yes | 1018 | 1.7% | 1012 | 1.7% |
| straight +x+y (x wing) 4 | straight | yes | 599 | 1.0% | 572 | 0.9% |
| corner +x+y | corner | yes | 1855 | 3.1% | 655 | 1.1% |
| straight -x+y (y wing) 0 | straight | yes | 2221 | 3.7% | 2221 | 3.7% |
| straight -x+y (y wing) 1 | straight | yes | 1811 | 3.0% | 1721 | 2.9% |
| straight -x+y (y wing) 2 | straight | yes | 1550 | 2.6% | 1544 | 2.6% |
| straight -x+y (y wing) 3 | straight | yes | 1116 | 1.9% | 1113 | 1.8% |
| straight -x+y (y wing) 4 | straight | yes | 630 | 1.0% | 613 | 1.0% |
| straight -x+y (x wing) 0 | straight | yes | 2231 | 3.7% | 2231 | 3.7% |
| straight -x+y (x wing) 1 | straight | yes | 1801 | 3.0% | 1728 | 2.9% |
| straight -x+y (x wing) 2 | straight | yes | 1563 | 2.6% | 1556 | 2.6% |
| straight -x+y (x wing) 3 | straight | yes | 1124 | 1.9% | 1117 | 1.9% |
| straight -x+y (x wing) 4 | straight | yes | 602 | 1.0% | 587 | 1.0% |
| corner -x+y | corner | yes | 1910 | 3.2% | 641 | 1.1% |
| straight -x-y (y wing) 0 | straight | yes | 2206 | 3.7% | 2206 | 3.7% |
| straight -x-y (y wing) 1 | straight | yes | 1791 | 3.0% | 1702 | 2.8% |
| straight -x-y (y wing) 2 | straight | yes | 1523 | 2.5% | 1497 | 2.5% |
| straight -x-y (y wing) 3 | straight | yes | 1094 | 1.8% | 1074 | 1.8% |
| straight -x-y (y wing) 4 | straight | yes | 682 | 1.1% | 656 | 1.1% |
| straight -x-y (x wing) 0 | straight | yes | 2203 | 3.7% | 2203 | 3.7% |
| straight -x-y (x wing) 1 | straight | yes | 1787 | 3.0% | 1683 | 2.8% |
| straight -x-y (x wing) 2 | straight | yes | 1530 | 2.5% | 1504 | 2.5% |
| straight -x-y (x wing) 3 | straight | yes | 1087 | 1.8% | 1061 | 1.8% |
| straight -x-y (x wing) 4 | straight | yes | 726 | 1.2% | 703 | 1.2% |
| corner -x-y | corner | yes | 2047 | 3.4% | 775 | 1.3% |
| straight +x-y (y wing) 0 | straight | yes | 2222 | 3.7% | 2222 | 3.7% |
| straight +x-y (y wing) 1 | straight | yes | 1807 | 3.0% | 1695 | 2.8% |
| straight +x-y (y wing) 2 | straight | yes | 1547 | 2.6% | 1538 | 2.6% |
| straight +x-y (y wing) 3 | straight | yes | 1108 | 1.8% | 1093 | 1.8% |
| straight +x-y (y wing) 4 | straight | yes | 688 | 1.1% | 671 | 1.1% |
| straight +x-y (x wing) 0 | straight | yes | 2200 | 3.7% | 2199 | 3.6% |
| straight +x-y (x wing) 1 | straight | yes | 1820 | 3.0% | 1719 | 2.9% |
| straight +x-y (x wing) 2 | straight | yes | 1556 | 2.6% | 1548 | 2.6% |
| straight +x-y (x wing) 3 | straight | yes | 1030 | 1.7% | 1022 | 1.7% |
| straight +x-y (x wing) 4 | straight | yes | 607 | 1.0% | 594 | 1.0% |
| corner +x-y | corner | yes | 1951 | 3.2% | 762 | 1.3% |
| **straight (40)** | | | 58454 | | 57420 | 95.3% |
| **corner (4)** | | | 7763 | | 2833 | 4.7% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 1748 | 70.3 | 873.8 | 0.28 | 0.31 | 0.0% |
| -x | 1753 | 70.5 | 861.2 | 0.28 | 0.32 | 0.0% |
| +y | 1768 | 70.5 | 870.2 | 0.28 | 0.31 | 0.0% |
| -y | 1755 | 70.5 | 861.1 | 0.28 | 0.32 | 0.0% |
| door +x+y (y wall) 0 | 1536 | 4.9 | 1012.0 | 0.48 | 0.69 | 0.0% |
| door +x+y (y wall) 1 | 1715 | 4.9 | 1032.6 | 0.52 | 0.66 | 0.0% |
| door +x+y (y wall) 2 | 1569 | 4.9 | 1160.2 | 0.42 | 0.66 | 0.0% |
| door +x+y (y wall) 3 | 1048 | 4.9 | 1206.7 | 0.27 | 0.69 | 0.0% |
| door +x+y (y wall) 4 | 615 | 5.1 | 1201.1 | 0.16 | 0.72 | 0.0% |
| door +x+y (x wall) 0 | 1510 | 4.9 | 1004.7 | 0.47 | 0.69 | 0.0% |
| door +x+y (x wall) 1 | 1706 | 4.9 | 1049.1 | 0.51 | 0.69 | 0.0% |
| door +x+y (x wall) 2 | 1582 | 4.9 | 1161.2 | 0.43 | 0.69 | 0.0% |
| door +x+y (x wall) 3 | 1002 | 4.9 | 1210.9 | 0.26 | 0.69 | 0.0% |
| door +x+y (x wall) 4 | 644 | 5.1 | 1203.4 | 0.17 | 0.69 | 0.0% |
| door +x+y (corner) | 391 | 6.3 | 1210.0 | 0.10 | 0.66 | 0.0% |
| door -x+y (y wall) 0 | 1492 | 4.9 | 959.7 | 0.49 | 0.69 | 0.0% |
| door -x+y (y wall) 1 | 1709 | 4.9 | 1101.2 | 0.49 | 0.69 | 0.0% |
| door -x+y (y wall) 2 | 1514 | 4.9 | 1124.8 | 0.42 | 0.69 | 0.0% |
| door -x+y (y wall) 3 | 1103 | 4.9 | 1079.5 | 0.32 | 0.66 | 0.0% |
| door -x+y (y wall) 4 | 653 | 5.1 | 1094.9 | 0.19 | 0.69 | 0.0% |
| door -x+y (x wall) 0 | 1512 | 4.9 | 950.1 | 0.50 | 0.69 | 0.0% |
| door -x+y (x wall) 1 | 1704 | 4.9 | 1098.8 | 0.49 | 0.69 | 0.0% |
| door -x+y (x wall) 2 | 1499 | 4.9 | 1126.4 | 0.42 | 0.66 | 0.0% |
| door -x+y (x wall) 3 | 1135 | 4.9 | 1098.4 | 0.32 | 0.72 | 0.0% |
| door -x+y (x wall) 4 | 626 | 4.9 | 1098.8 | 0.18 | 0.66 | 0.0% |
| door -x+y (corner) | 356 | 6.3 | 891.8 | 0.13 | 0.63 | 0.0% |
| door -x-y (y wall) 0 | 1507 | 4.9 | 956.2 | 0.49 | 0.66 | 0.0% |
| door -x-y (y wall) 1 | 1677 | 4.9 | 1047.5 | 0.50 | 0.66 | 0.0% |
| door -x-y (y wall) 2 | 1438 | 4.7 | 1120.6 | 0.40 | 0.69 | 0.0% |
| door -x-y (y wall) 3 | 1128 | 4.9 | 1129.2 | 0.31 | 0.69 | 0.0% |
| door -x-y (y wall) 4 | 661 | 4.9 | 1092.6 | 0.19 | 0.69 | 0.0% |
| door -x-y (x wall) 0 | 1486 | 4.9 | 948.0 | 0.49 | 0.69 | 0.0% |
| door -x-y (x wall) 1 | 1667 | 5.1 | 1069.0 | 0.49 | 0.69 | 0.0% |
| door -x-y (x wall) 2 | 1461 | 4.9 | 1111.0 | 0.41 | 0.69 | 0.0% |
| door -x-y (x wall) 3 | 1015 | 4.9 | 1086.2 | 0.29 | 0.69 | 0.0% |
| door -x-y (x wall) 4 | 792 | 5.1 | 1129.4 | 0.22 | 0.66 | 0.0% |
| door -x-y (corner) | 501 | 6.3 | 893.9 | 0.18 | 0.66 | 0.0% |
| door +x-y (y wall) 0 | 1504 | 4.9 | 956.7 | 0.49 | 0.66 | 0.0% |
| door +x-y (y wall) 1 | 1676 | 4.9 | 1079.2 | 0.49 | 0.69 | 0.0% |
| door +x-y (y wall) 2 | 1493 | 4.9 | 1113.1 | 0.42 | 0.72 | 0.0% |
| door +x-y (y wall) 3 | 1089 | 4.9 | 1094.2 | 0.31 | 0.72 | 0.0% |
| door +x-y (y wall) 4 | 723 | 5.1 | 1073.4 | 0.21 | 0.69 | 0.0% |
| door +x-y (x wall) 0 | 1516 | 4.9 | 964.8 | 0.49 | 0.66 | 0.0% |
| door +x-y (x wall) 1 | 1691 | 4.9 | 1080.7 | 0.49 | 0.72 | 0.0% |
| door +x-y (x wall) 2 | 1493 | 4.9 | 1107.2 | 0.42 | 0.66 | 0.0% |
| door +x-y (x wall) 3 | 1045 | 4.9 | 1110.3 | 0.29 | 0.69 | 0.0% |
| door +x-y (x wall) 4 | 626 | 5.1 | 1036.3 | 0.19 | 0.69 | 0.0% |
| door +x-y (corner) | 419 | 6.5 | 922.3 | 0.14 | 0.66 | 0.0% |

Mean flow / w J averaged over the doors 0.36, over the avenues 0.28.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 103.1 | 2221 | 1496 / 725 / 693 | 0.7 | 843.4 | 3.46 | 5.22 | 89% | 87% | 2% | 4.57 |
| straight +x+y (y wing) 1 | 1.20 | 81.5 | 1792 | 1755 / 0 / 173 | 0.7 | 1029.7 | 1.87 | 3.21 | 90% | 80% | 11% | 4.14 |
| straight +x+y (y wing) 2 | 1.20 | 61.0 | 1472 | 1642 / 0 / 9 | 0.7 | 1157.2 | 1.43 | 2.21 | 92% | 62% | 30% | 3.30 |
| straight +x+y (y wing) 3 | 1.20 | 39.4 | 852 | 1000 / 0 / 15 | 0.7 | 1203.7 | 0.84 | 2.31 | 40% | 32% | 7% | 3.74 |
| straight +x+y (y wing) 4 | 1.20 | 18.8 | 375 | 590 / 0 / 16 | 0.7 | 1198.1 | 0.51 | 2.21 | 15% | 15% | 0% | 3.93 |
| straight +x+y (x wing) 0 | 1.20 | 103.1 | 2222 | 1475 / 747 / 940 | 0.7 | 839.2 | 3.77 | 6.62 | 89% | 84% | 6% | 4.46 |
| straight +x+y (x wing) 1 | 1.20 | 81.5 | 1791 | 1741 / 0 / 158 | 0.7 | 1046.1 | 1.82 | 3.81 | 87% | 83% | 4% | 4.20 |
| straight +x+y (x wing) 2 | 1.20 | 61.0 | 1445 | 1644 / 0 / 13 | 0.7 | 1158.2 | 1.43 | 2.21 | 92% | 62% | 31% | 3.19 |
| straight +x+y (x wing) 3 | 1.20 | 39.4 | 881 | 1012 / 0 / 21 | 0.7 | 1207.9 | 0.86 | 2.21 | 43% | 36% | 7% | 3.71 |
| straight +x+y (x wing) 4 | 1.20 | 18.8 | 378 | 572 / 0 / 33 | 0.7 | 1200.4 | 0.50 | 2.21 | 16% | 15% | 1% | 3.81 |
| corner +x+y | 1.20 | 186.0 | 1625 | 391 / 264 / 1266 | 0.7 | 1206.5 | 1.59 | 3.81 | 89% | 66% | 24% | 2.56 |
| straight -x+y (y wing) 0 | 1.20 | 103.1 | 2221 | 1480 / 741 / 989 | 0.7 | 845.0 | 3.80 | 6.32 | 89% | 86% | 4% | 4.71 |
| straight -x+y (y wing) 1 | 1.20 | 81.5 | 1789 | 1721 / 0 / 186 | 0.7 | 1098.2 | 1.74 | 3.61 | 89% | 76% | 14% | 3.97 |
| straight -x+y (y wing) 2 | 1.20 | 61.0 | 1446 | 1544 / 0 / 12 | 0.7 | 1121.9 | 1.39 | 2.31 | 73% | 63% | 11% | 3.88 |
| straight -x+y (y wing) 3 | 1.20 | 39.4 | 887 | 1113 / 0 / 12 | 0.7 | 1076.6 | 1.05 | 2.21 | 44% | 41% | 4% | 3.93 |
| straight -x+y (y wing) 4 | 1.20 | 18.8 | 375 | 613 / 0 / 18 | 0.7 | 1091.9 | 0.58 | 2.21 | 17% | 16% | 1% | 3.90 |
| straight -x+y (x wing) 0 | 1.20 | 103.1 | 2231 | 1488 / 743 / 873 | 0.7 | 856.9 | 3.62 | 6.42 | 90% | 85% | 5% | 4.62 |
| straight -x+y (x wing) 1 | 1.20 | 81.5 | 1773 | 1728 / 0 / 187 | 0.7 | 1095.8 | 1.75 | 3.51 | 91% | 75% | 16% | 3.80 |
| straight -x+y (x wing) 2 | 1.20 | 61.0 | 1439 | 1556 / 0 / 15 | 0.7 | 1123.4 | 1.40 | 2.31 | 73% | 63% | 10% | 3.97 |
| straight -x+y (x wing) 3 | 1.20 | 39.4 | 883 | 1117 / 0 / 11 | 0.7 | 1095.4 | 1.03 | 2.21 | 47% | 39% | 8% | 3.77 |
| straight -x+y (x wing) 4 | 1.20 | 18.8 | 361 | 587 / 0 / 21 | 0.7 | 1095.8 | 0.56 | 2.31 | 17% | 15% | 2% | 3.89 |
| corner -x+y | 1.20 | 186.0 | 1667 | 356 / 285 / 1334 | 0.7 | 1071.8 | 1.84 | 4.21 | 92% | 69% | 22% | 2.81 |
| straight -x-y (y wing) 0 | 1.20 | 103.1 | 2206 | 1482 / 725 / 763 | 0.7 | 849.0 | 3.50 | 5.72 | 87% | 84% | 3% | 4.65 |
| straight -x-y (y wing) 1 | 1.20 | 81.5 | 1779 | 1702 / 0 / 190 | 0.7 | 1044.5 | 1.81 | 4.11 | 89% | 77% | 11% | 4.02 |
| straight -x-y (y wing) 2 | 1.20 | 61.0 | 1426 | 1497 / 0 / 27 | 0.7 | 1117.7 | 1.36 | 2.31 | 71% | 60% | 11% | 3.99 |
| straight -x-y (y wing) 3 | 1.20 | 39.4 | 874 | 1074 / 0 / 20 | 0.7 | 1126.2 | 0.97 | 2.11 | 42% | 37% | 5% | 3.84 |
| straight -x-y (y wing) 4 | 1.20 | 18.8 | 381 | 656 / 0 / 29 | 0.7 | 1089.7 | 0.63 | 2.21 | 20% | 16% | 4% | 3.63 |
| straight -x-y (x wing) 0 | 1.20 | 103.1 | 2203 | 1470 / 733 / 816 | 0.7 | 835.2 | 3.62 | 5.82 | 89% | 86% | 4% | 4.66 |
| straight -x-y (x wing) 1 | 1.20 | 81.5 | 1777 | 1683 / 0 / 194 | 0.7 | 1066.1 | 1.76 | 3.91 | 91% | 76% | 15% | 3.90 |
| straight -x-y (x wing) 2 | 1.20 | 61.0 | 1434 | 1504 / 0 / 30 | 0.7 | 1108.0 | 1.39 | 2.21 | 72% | 64% | 8% | 3.98 |
| straight -x-y (x wing) 3 | 1.20 | 39.4 | 909 | 1061 / 0 / 39 | 0.7 | 1083.2 | 1.02 | 2.31 | 46% | 42% | 4% | 4.01 |
| straight -x-y (x wing) 4 | 1.20 | 18.8 | 392 | 703 / 0 / 23 | 0.7 | 1126.4 | 0.64 | 2.41 | 18% | 16% | 2% | 3.84 |
| corner -x-y | 1.20 | 186.0 | 1683 | 501 / 274 / 1334 | 0.7 | 1102.4 | 1.91 | 4.81 | 89% | 55% | 34% | 2.53 |
| straight +x-y (y wing) 0 | 1.20 | 103.1 | 2222 | 1488 / 734 / 961 | 0.7 | 853.0 | 3.73 | 6.62 | 90% | 85% | 5% | 4.52 |
| straight +x-y (y wing) 1 | 1.20 | 81.5 | 1795 | 1695 / 0 / 228 | 0.7 | 1076.2 | 1.79 | 3.71 | 91% | 75% | 16% | 3.71 |
| straight +x-y (y wing) 2 | 1.20 | 61.0 | 1420 | 1538 / 0 / 17 | 0.7 | 1110.1 | 1.40 | 2.41 | 72% | 62% | 10% | 3.89 |
| straight +x-y (y wing) 3 | 1.20 | 39.4 | 901 | 1093 / 0 / 23 | 0.7 | 1091.2 | 1.02 | 2.31 | 46% | 43% | 4% | 3.85 |
| straight +x-y (y wing) 4 | 1.20 | 18.8 | 382 | 671 / 0 / 24 | 0.7 | 1070.4 | 0.65 | 2.41 | 20% | 17% | 4% | 3.61 |
| straight +x-y (x wing) 0 | 1.20 | 103.1 | 2200 | 1488 / 712 / 786 | 0.7 | 829.2 | 3.60 | 6.02 | 88% | 87% | 1% | 4.63 |
| straight +x-y (x wing) 1 | 1.20 | 81.5 | 1790 | 1719 / 0 / 227 | 0.7 | 1077.8 | 1.81 | 3.81 | 86% | 72% | 15% | 3.79 |
| straight +x-y (x wing) 2 | 1.20 | 61.0 | 1467 | 1548 / 0 / 16 | 0.7 | 1104.2 | 1.42 | 2.31 | 77% | 67% | 11% | 3.92 |
| straight +x-y (x wing) 3 | 1.20 | 39.4 | 863 | 1022 / 0 / 19 | 0.7 | 1107.3 | 0.94 | 2.21 | 45% | 37% | 8% | 3.72 |
| straight +x-y (x wing) 4 | 1.20 | 18.8 | 389 | 594 / 0 / 13 | 0.7 | 1033.3 | 0.59 | 2.21 | 19% | 17% | 2% | 3.90 |
| corner +x-y | 1.20 | 186.0 | 1634 | 419 / 343 / 1261 | 0.7 | 1057.1 | 1.91 | 4.51 | 92% | 70% | 21% | 2.68 |

The last agent out (agent 9477, t100 1210.9 s): last gangway straight +x+y (x wing) 3, exit door +x+y (x wall) 3. The gangway that cleared last: straight +x+y (x wing) 3 at 1207.9 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 8804 | 7800.4 | 7.01 | 1208.4 / 1145.8 / 1080.9 | 1148.8 / 1142.1 / 1066.6 | 5067293.9 | 10367137 | 0.201 |
| gangway | 3792 | 3512.9 | 7.01 | 1206.5 / 1145.8 / 1080.9 | 1148.8 / 1142.1 / 1066.6 | 5067293.9 | 9666812 | 0.130 |
| walkway | 276 | 257.4 | 3.97 | 550.6 / 354.9 / 0.0 | 364.7 / 222.7 / 0.0 | 0.0 | 71752 | 0.687 |
| avenue | 1920 | 1801.4 | 1.85 | 745.6 / 0.0 / 0.0 | 506.7 / 0.0 / 0.0 | 0.0 | 420959 | 1.334 |
| exit | 4 | 2.0 | 0.00 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 0 | - |
| concourse | 2812 | 2226.8 | 2.95 | 1170.3 / 75.9 / 0.0 | 927.4 / 18.0 / 0.0 | 0.0 | 207614 | 1.050 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 25392 | 16030.4 | 7.91 | 1093.5 / 1075.7 / 1055.2 | 1083.5 / 1069.2 / 1048.0 | 5760069.0 | 14912448 | 0.032 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 208 x 208 from (-104, -104) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 48.5 | 48.5 | gangway | 1.00 | 5.67 | 1104.4 | 1102.1 | 1053.6 | 5808.6 | 0.004 |
| 2 | 47.5 | 47.5 | gangway | 1.00 | 5.57 | 1066.6 | 1060.6 | 1028.8 | 5540.1 | 0.004 |
| 3 | 35.5 | -35.5 | gangway | 1.00 | 5.92 | 1005.0 | 999.6 | 937.2 | 5410.6 | 0.007 |
| 4 | -36.5 | 36.5 | gangway | 1.00 | 5.75 | 1023.0 | 1019.7 | 971.3 | 5351.6 | 0.009 |
| 5 | 50.5 | 50.5 | gangway | 1.00 | 5.91 | 1121.0 | 1118.0 | 974.6 | 5338.8 | 0.008 |
| 6 | -34.5 | 34.5 | gangway | 1.00 | 5.66 | 1011.0 | 999.8 | 957.8 | 5312.1 | 0.007 |
| 7 | 49.5 | 49.5 | gangway | 0.99 | 5.50 | 1111.0 | 1107.2 | 1028.5 | 5307.2 | 0.008 |
| 8 | 36.5 | -36.5 | gangway | 1.00 | 5.74 | 1007.8 | 1004.8 | 926.8 | 5177.8 | 0.010 |
| 9 | 39.5 | -39.5 | gangway | 1.00 | 5.89 | 1020.6 | 1004.3 | 899.2 | 5172.9 | 0.021 |
| 10 | 46.5 | 46.5 | gangway | 1.00 | 5.40 | 1058.4 | 1013.4 | 978.1 | 5162.1 | 0.005 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 52.5 | 54.5 | seat row | 0.50 | 7.38 | 1038.8 | 1030.7 | 1017.1 | 3597.8 | 0.007 |
| 2 | 50.5 | 48.5 | seat row | 0.50 | 6.97 | 1075.0 | 1060.1 | 1048.0 | 3507.3 | 0.008 |
| 3 | 54.5 | 52.5 | seat row | 0.50 | 7.38 | 1020.9 | 1017.8 | 1003.4 | 3496.7 | 0.007 |
| 4 | 51.5 | 54.5 | seat row | 0.50 | 7.17 | 1027.6 | 1025.5 | 1013.4 | 3483.4 | 0.006 |
| 5 | -36.5 | 38.5 | seat row | 0.50 | 7.30 | 983.3 | 982.5 | 965.3 | 3418.7 | 0.005 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 7550; agent-steps of seated agents on another row's clearway: 1602014.

## Deposit check

Person-seconds deposited: 25285141.1, of them in excluded cells: 5556.719.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 5575972 overlapping pair-steps: p99 0.0030, max 0.1094 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0030 max 0.1094; venue-geometry 17: p99 0.0027 max 0.0027 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00758 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 52 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.38 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 3642 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
