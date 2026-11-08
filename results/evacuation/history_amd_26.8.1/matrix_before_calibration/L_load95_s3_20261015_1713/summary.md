# Experiment `L_load95_s3`

**Task 5.8 stage 2: venue L, 95% load (seed 3), default model**

Venue L (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (4000 x 4000), cache key a2f3aaf59c2252b7, content hash 022d17b202313d70). 60253 agents on 95% of the 63424 seats (spawnSeatedCrowd, seed 3), buffer N = 65536, 6520 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 8435301 evaluations, 479869 switches, 0 forced choices).
Capacity: **within design capacity** (the L venue's design capacity 63424, jam capacity 171923: 23822.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `cd8e0bbf3411846ca7aa6719887d122a142a7ca1`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-15T17:13:12, 602.2 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 2232 | 390.4 |
| t90 | 4563 | 798.1 |
| t100 | 6520 | 1140.4 |

t_p: the step by which ceil(p x 60253) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 1761 | 0 | 70.3 | 861.1 | 23.6 | 26.6 | 79.6-89.6 |
| -x | 5.66 | 1751 | 0 | 70.5 | 866.7 | 23.3 | 26.6 | 82.0-92.0 |
| +y | 5.66 | 1768 | 0 | 70.5 | 874.5 | 23.3 | 25.5 | 79.6-89.6 |
| -y | 5.66 | 1769 | 0 | 70.5 | 860.0 | 23.7 | 26.6 | 209.2-219.2 |
| door +x+y (y wall) 0 | 2.30 | 1507 | 2455 | 4.9 | 932.8 | 42.4 | 57.6 | 22.7-32.7 |
| door +x+y (y wall) 1 | 2.30 | 1692 | 2043 | 4.9 | 1076.6 | 41.2 | 54.9 | 5.2-15.2 |
| door +x+y (y wall) 2 | 2.30 | 1474 | 1511 | 4.9 | 1137.9 | 33.9 | 57.6 | 15.2-25.2 |
| door +x+y (y wall) 3 | 2.30 | 1079 | 983 | 4.9 | 1124.3 | 25.1 | 57.6 | 7.9-17.8 |
| door +x+y (y wall) 4 | 2.30 | 711 | 480 | 5.1 | 1125.3 | 16.6 | 57.6 | 23.4-33.4 |
| door +x+y (x wall) 0 | 2.30 | 1493 | 2431 | 4.9 | 953.2 | 41.1 | 54.9 | 13.5-23.4 |
| door +x+y (x wall) 1 | 2.30 | 1681 | 2045 | 4.9 | 1100.2 | 40.0 | 54.9 | 13.3-23.3 |
| door +x+y (x wall) 2 | 2.30 | 1475 | 1502 | 4.9 | 1113.5 | 34.7 | 57.6 | 736.9-746.9 |
| door +x+y (x wall) 3 | 2.30 | 1043 | 1000 | 4.9 | 1140.4 | 24.0 | 57.6 | 11.2-21.2 |
| door +x+y (x wall) 4 | 2.30 | 718 | 486 | 5.1 | 1085.6 | 17.3 | 57.6 | 10.8-20.8 |
| door +x+y (corner) | 2.30 | 417 | 118 | 6.3 | 935.4 | 11.7 | 54.9 | 46.2-56.1 |
| door -x+y (y wall) 0 | 2.30 | 1517 | 2467 | 4.9 | 959.4 | 41.5 | 60.2 | 25.7-35.7 |
| door -x+y (y wall) 1 | 2.30 | 1664 | 2035 | 4.9 | 1025.1 | 42.5 | 57.6 | 8.0-18.0 |
| door -x+y (y wall) 2 | 2.30 | 1525 | 1508 | 4.9 | 1098.2 | 36.4 | 57.6 | 9.3-19.2 |
| door -x+y (y wall) 3 | 2.30 | 1101 | 1001 | 4.9 | 1111.4 | 26.0 | 54.9 | 11.4-21.3 |
| door -x+y (y wall) 4 | 2.30 | 659 | 481 | 5.1 | 1007.8 | 17.1 | 54.9 | 17.1-27.1 |
| door -x+y (x wall) 0 | 2.30 | 1494 | 2460 | 4.9 | 952.7 | 41.1 | 57.6 | 15.2-25.2 |
| door -x+y (x wall) 1 | 2.30 | 1684 | 2022 | 4.9 | 1120.8 | 39.4 | 60.2 | 24.0-33.9 |
| door -x+y (x wall) 2 | 2.30 | 1513 | 1499 | 4.9 | 1110.5 | 35.7 | 57.6 | 40.4-50.4 |
| door -x+y (x wall) 3 | 2.30 | 1115 | 1001 | 4.9 | 1119.1 | 26.1 | 60.2 | 19.2-29.2 |
| door -x+y (x wall) 4 | 2.30 | 662 | 479 | 4.9 | 1033.3 | 16.8 | 57.6 | 20.6-30.6 |
| door -x+y (corner) | 2.30 | 374 | 119 | 6.3 | 912.0 | 10.8 | 54.9 | 60.0-70.0 |
| door -x-y (y wall) 0 | 2.30 | 1509 | 2461 | 4.9 | 961.8 | 41.1 | 54.9 | 16.6-26.6 |
| door -x-y (y wall) 1 | 2.30 | 1701 | 2005 | 4.9 | 1117.5 | 39.9 | 57.6 | 13.5-23.4 |
| door -x-y (y wall) 2 | 2.30 | 1435 | 1528 | 4.7 | 1125.3 | 33.4 | 57.6 | 26.4-36.4 |
| door -x-y (y wall) 3 | 2.30 | 1038 | 982 | 4.9 | 1135.0 | 24.0 | 57.6 | 27.1-37.1 |
| door -x-y (y wall) 4 | 2.30 | 685 | 489 | 4.9 | 1134.4 | 15.8 | 57.6 | 12.9-22.9 |
| door -x-y (x wall) 0 | 2.30 | 1497 | 2455 | 4.9 | 952.4 | 41.2 | 57.6 | 192.2-202.2 |
| door -x-y (x wall) 1 | 2.30 | 1683 | 2027 | 5.1 | 1088.6 | 40.5 | 57.6 | 7.0-17.0 |
| door -x-y (x wall) 2 | 2.30 | 1510 | 1514 | 4.9 | 1126.9 | 35.1 | 60.2 | 29.7-39.7 |
| door -x-y (x wall) 3 | 2.30 | 1046 | 998 | 4.9 | 1135.7 | 24.1 | 54.9 | 20.6-30.6 |
| door -x-y (x wall) 4 | 2.30 | 675 | 487 | 5.1 | 1124.3 | 15.7 | 54.9 | 33.2-43.2 |
| door -x-y (corner) | 2.30 | 533 | 118 | 6.3 | 937.7 | 14.9 | 54.9 | 147.1-157.1 |
| door +x-y (y wall) 0 | 2.30 | 1501 | 2439 | 4.9 | 948.7 | 41.5 | 54.9 | 131.2-141.1 |
| door +x-y (y wall) 1 | 2.30 | 1703 | 2026 | 4.9 | 1098.2 | 40.6 | 54.9 | 9.6-19.6 |
| door +x-y (y wall) 2 | 2.30 | 1523 | 1517 | 4.9 | 1124.8 | 35.5 | 60.2 | 14.2-24.1 |
| door +x-y (y wall) 3 | 2.30 | 992 | 998 | 4.9 | 1124.0 | 23.1 | 60.2 | 11.7-21.7 |
| door +x-y (y wall) 4 | 2.30 | 677 | 488 | 5.1 | 1114.9 | 15.9 | 57.6 | 10.3-20.3 |
| door +x-y (x wall) 0 | 2.30 | 1501 | 2440 | 4.9 | 944.1 | 41.7 | 54.9 | 11.0-21.0 |
| door +x-y (x wall) 1 | 2.30 | 1698 | 2030 | 4.9 | 1132.7 | 39.3 | 60.2 | 10.3-20.3 |
| door +x-y (x wall) 2 | 2.30 | 1484 | 1519 | 4.9 | 1119.2 | 34.7 | 60.2 | 28.0-38.0 |
| door +x-y (x wall) 3 | 2.30 | 1084 | 993 | 4.9 | 1121.0 | 25.3 | 57.6 | 17.7-27.6 |
| door +x-y (x wall) 4 | 2.30 | 703 | 490 | 5.1 | 1104.5 | 16.7 | 60.2 | 24.8-34.8 |
| door +x-y (corner) | 2.30 | 428 | 123 | 6.5 | 1029.3 | 10.9 | 57.6 | 97.8-107.7 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (2.30 m; a corner door's: the gap between its wall ends, 2.30 m); agents are removed past the outer wall's outer face (92.71 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 1761 | 2.9% | 19.6% |
| -x | avenue | 5.66 | 1751 | 2.9% | 19.5% |
| +y | avenue | 5.66 | 1768 | 2.9% | 19.7% |
| -y | avenue | 5.66 | 1769 | 2.9% | 19.7% |
| door +x+y (y wall) 0 | door | 2.30 | 1507 | 2.5% | 41.2% |
| door +x+y (y wall) 1 | door | 2.30 | 1692 | 2.8% | 46.3% |
| door +x+y (y wall) 2 | door | 2.30 | 1474 | 2.4% | 40.3% |
| door +x+y (y wall) 3 | door | 2.30 | 1079 | 1.8% | 29.5% |
| door +x+y (y wall) 4 | door | 2.30 | 711 | 1.2% | 19.5% |
| door +x+y (x wall) 0 | door | 2.30 | 1493 | 2.5% | 40.9% |
| door +x+y (x wall) 1 | door | 2.30 | 1681 | 2.8% | 46.0% |
| door +x+y (x wall) 2 | door | 2.30 | 1475 | 2.4% | 40.4% |
| door +x+y (x wall) 3 | door | 2.30 | 1043 | 1.7% | 28.5% |
| door +x+y (x wall) 4 | door | 2.30 | 718 | 1.2% | 19.6% |
| door +x+y (corner) | door | 2.30 | 417 | 0.7% | 11.4% |
| door -x+y (y wall) 0 | door | 2.30 | 1517 | 2.5% | 41.5% |
| door -x+y (y wall) 1 | door | 2.30 | 1664 | 2.8% | 45.5% |
| door -x+y (y wall) 2 | door | 2.30 | 1525 | 2.5% | 41.7% |
| door -x+y (y wall) 3 | door | 2.30 | 1101 | 1.8% | 30.1% |
| door -x+y (y wall) 4 | door | 2.30 | 659 | 1.1% | 18.0% |
| door -x+y (x wall) 0 | door | 2.30 | 1494 | 2.5% | 40.9% |
| door -x+y (x wall) 1 | door | 2.30 | 1684 | 2.8% | 46.1% |
| door -x+y (x wall) 2 | door | 2.30 | 1513 | 2.5% | 41.4% |
| door -x+y (x wall) 3 | door | 2.30 | 1115 | 1.9% | 30.5% |
| door -x+y (x wall) 4 | door | 2.30 | 662 | 1.1% | 18.1% |
| door -x+y (corner) | door | 2.30 | 374 | 0.6% | 10.2% |
| door -x-y (y wall) 0 | door | 2.30 | 1509 | 2.5% | 41.3% |
| door -x-y (y wall) 1 | door | 2.30 | 1701 | 2.8% | 46.5% |
| door -x-y (y wall) 2 | door | 2.30 | 1435 | 2.4% | 39.3% |
| door -x-y (y wall) 3 | door | 2.30 | 1038 | 1.7% | 28.4% |
| door -x-y (y wall) 4 | door | 2.30 | 685 | 1.1% | 18.7% |
| door -x-y (x wall) 0 | door | 2.30 | 1497 | 2.5% | 41.0% |
| door -x-y (x wall) 1 | door | 2.30 | 1683 | 2.8% | 46.1% |
| door -x-y (x wall) 2 | door | 2.30 | 1510 | 2.5% | 41.3% |
| door -x-y (x wall) 3 | door | 2.30 | 1046 | 1.7% | 28.6% |
| door -x-y (x wall) 4 | door | 2.30 | 675 | 1.1% | 18.5% |
| door -x-y (corner) | door | 2.30 | 533 | 0.9% | 14.6% |
| door +x-y (y wall) 0 | door | 2.30 | 1501 | 2.5% | 41.1% |
| door +x-y (y wall) 1 | door | 2.30 | 1703 | 2.8% | 46.6% |
| door +x-y (y wall) 2 | door | 2.30 | 1523 | 2.5% | 41.7% |
| door +x-y (y wall) 3 | door | 2.30 | 992 | 1.6% | 27.1% |
| door +x-y (y wall) 4 | door | 2.30 | 677 | 1.1% | 18.5% |
| door +x-y (x wall) 0 | door | 2.30 | 1501 | 2.5% | 41.1% |
| door +x-y (x wall) 1 | door | 2.30 | 1698 | 2.8% | 46.5% |
| door +x-y (x wall) 2 | door | 2.30 | 1484 | 2.5% | 40.6% |
| door +x-y (x wall) 3 | door | 2.30 | 1084 | 1.8% | 29.7% |
| door +x-y (x wall) 4 | door | 2.30 | 703 | 1.2% | 19.2% |
| door +x-y (corner) | door | 2.30 | 428 | 0.7% | 11.7% |
| **doors (44)** | door | 101.20 | 53204 | 88.3% | |
| **avenues (4)** | avenue | 22.64 | 7049 | 11.7% | |

**Unused exit width: 0.0 of 123.8 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 1140.4 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 30.6%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 2186 | 3.6% | 2186 | 3.6% |
| straight +x+y (y wing) 1 | straight | yes | 1821 | 3.0% | 1713 | 2.8% |
| straight +x+y (y wing) 2 | straight | yes | 1553 | 2.6% | 1535 | 2.5% |
| straight +x+y (y wing) 3 | straight | yes | 1096 | 1.8% | 1082 | 1.8% |
| straight +x+y (y wing) 4 | straight | yes | 661 | 1.1% | 647 | 1.1% |
| straight +x+y (x wing) 0 | straight | yes | 2200 | 3.7% | 2200 | 3.7% |
| straight +x+y (x wing) 1 | straight | yes | 1810 | 3.0% | 1699 | 2.8% |
| straight +x+y (x wing) 2 | straight | yes | 1533 | 2.5% | 1517 | 2.5% |
| straight +x+y (x wing) 3 | straight | yes | 1060 | 1.8% | 1047 | 1.7% |
| straight +x+y (x wing) 4 | straight | yes | 686 | 1.1% | 672 | 1.1% |
| corner +x+y | corner | yes | 2001 | 3.3% | 756 | 1.3% |
| straight -x+y (y wing) 0 | straight | yes | 2248 | 3.7% | 2248 | 3.7% |
| straight -x+y (y wing) 1 | straight | yes | 1765 | 2.9% | 1688 | 2.8% |
| straight -x+y (y wing) 2 | straight | yes | 1551 | 2.6% | 1541 | 2.6% |
| straight -x+y (y wing) 3 | straight | yes | 1105 | 1.8% | 1103 | 1.8% |
| straight -x+y (y wing) 4 | straight | yes | 667 | 1.1% | 641 | 1.1% |
| straight -x+y (x wing) 0 | straight | yes | 2210 | 3.7% | 2210 | 3.7% |
| straight -x+y (x wing) 1 | straight | yes | 1780 | 3.0% | 1701 | 2.8% |
| straight -x+y (x wing) 2 | straight | yes | 1550 | 2.6% | 1538 | 2.6% |
| straight -x+y (x wing) 3 | straight | yes | 1124 | 1.9% | 1120 | 1.9% |
| straight -x+y (x wing) 4 | straight | yes | 647 | 1.1% | 632 | 1.0% |
| corner -x+y | corner | yes | 1962 | 3.3% | 650 | 1.1% |
| straight -x-y (y wing) 0 | straight | yes | 2198 | 3.6% | 2198 | 3.6% |
| straight -x-y (y wing) 1 | straight | yes | 1832 | 3.0% | 1729 | 2.9% |
| straight -x-y (y wing) 2 | straight | yes | 1534 | 2.5% | 1513 | 2.5% |
| straight -x-y (y wing) 3 | straight | yes | 1034 | 1.7% | 1010 | 1.7% |
| straight -x-y (y wing) 4 | straight | yes | 652 | 1.1% | 635 | 1.1% |
| straight -x-y (x wing) 0 | straight | yes | 2182 | 3.6% | 2182 | 3.6% |
| straight -x-y (x wing) 1 | straight | yes | 1824 | 3.0% | 1715 | 2.8% |
| straight -x-y (x wing) 2 | straight | yes | 1546 | 2.6% | 1536 | 2.5% |
| straight -x-y (x wing) 3 | straight | yes | 1087 | 1.8% | 1066 | 1.8% |
| straight -x-y (x wing) 4 | straight | yes | 655 | 1.1% | 629 | 1.0% |
| corner -x-y | corner | yes | 2014 | 3.3% | 851 | 1.4% |
| straight +x-y (y wing) 0 | straight | yes | 2218 | 3.7% | 2218 | 3.7% |
| straight +x-y (y wing) 1 | straight | yes | 1819 | 3.0% | 1728 | 2.9% |
| straight +x-y (y wing) 2 | straight | yes | 1573 | 2.6% | 1567 | 2.6% |
| straight +x-y (y wing) 3 | straight | yes | 1041 | 1.7% | 1028 | 1.7% |
| straight +x-y (y wing) 4 | straight | yes | 623 | 1.0% | 597 | 1.0% |
| straight +x-y (x wing) 0 | straight | yes | 2208 | 3.7% | 2208 | 3.7% |
| straight +x-y (x wing) 1 | straight | yes | 1803 | 3.0% | 1719 | 2.9% |
| straight +x-y (x wing) 2 | straight | yes | 1564 | 2.6% | 1555 | 2.6% |
| straight +x-y (x wing) 3 | straight | yes | 1060 | 1.8% | 1050 | 1.7% |
| straight +x-y (x wing) 4 | straight | yes | 682 | 1.1% | 666 | 1.1% |
| corner +x-y | corner | yes | 1938 | 3.2% | 727 | 1.2% |
| **straight (40)** | | | 58388 | | 57269 | 95.0% |
| **corner (4)** | | | 7915 | | 2984 | 5.0% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 1761 | 70.3 | 861.1 | 0.28 | 0.32 | 0.0% |
| -x | 1751 | 70.5 | 866.7 | 0.28 | 0.32 | 0.0% |
| +y | 1768 | 70.5 | 874.5 | 0.28 | 0.31 | 0.0% |
| -y | 1769 | 70.5 | 860.0 | 0.28 | 0.32 | 0.0% |
| door +x+y (y wall) 0 | 1507 | 4.9 | 932.8 | 0.51 | 0.69 | 0.0% |
| door +x+y (y wall) 1 | 1692 | 4.9 | 1076.6 | 0.49 | 0.66 | 0.0% |
| door +x+y (y wall) 2 | 1474 | 4.9 | 1137.9 | 0.41 | 0.69 | 0.0% |
| door +x+y (y wall) 3 | 1079 | 4.9 | 1124.3 | 0.30 | 0.69 | 0.0% |
| door +x+y (y wall) 4 | 711 | 5.1 | 1125.3 | 0.20 | 0.69 | 0.0% |
| door +x+y (x wall) 0 | 1493 | 4.9 | 953.2 | 0.49 | 0.66 | 0.0% |
| door +x+y (x wall) 1 | 1681 | 4.9 | 1100.2 | 0.48 | 0.66 | 0.0% |
| door +x+y (x wall) 2 | 1475 | 4.9 | 1113.5 | 0.42 | 0.69 | 0.0% |
| door +x+y (x wall) 3 | 1043 | 4.9 | 1140.4 | 0.29 | 0.69 | 0.0% |
| door +x+y (x wall) 4 | 718 | 5.1 | 1085.6 | 0.21 | 0.69 | 0.0% |
| door +x+y (corner) | 417 | 6.3 | 935.4 | 0.14 | 0.66 | 0.0% |
| door -x+y (y wall) 0 | 1517 | 4.9 | 959.4 | 0.50 | 0.72 | 0.0% |
| door -x+y (y wall) 1 | 1664 | 4.9 | 1025.1 | 0.51 | 0.69 | 0.0% |
| door -x+y (y wall) 2 | 1525 | 4.9 | 1098.2 | 0.44 | 0.69 | 0.0% |
| door -x+y (y wall) 3 | 1101 | 4.9 | 1111.4 | 0.31 | 0.66 | 0.0% |
| door -x+y (y wall) 4 | 659 | 5.1 | 1007.8 | 0.21 | 0.66 | 0.0% |
| door -x+y (x wall) 0 | 1494 | 4.9 | 952.7 | 0.49 | 0.69 | 0.0% |
| door -x+y (x wall) 1 | 1684 | 4.9 | 1120.8 | 0.47 | 0.72 | 0.0% |
| door -x+y (x wall) 2 | 1513 | 4.9 | 1110.5 | 0.43 | 0.69 | 0.0% |
| door -x+y (x wall) 3 | 1115 | 4.9 | 1119.1 | 0.31 | 0.72 | 0.0% |
| door -x+y (x wall) 4 | 662 | 4.9 | 1033.3 | 0.20 | 0.69 | 0.0% |
| door -x+y (corner) | 374 | 6.3 | 912.0 | 0.13 | 0.66 | 0.0% |
| door -x-y (y wall) 0 | 1509 | 4.9 | 961.8 | 0.49 | 0.66 | 0.0% |
| door -x-y (y wall) 1 | 1701 | 4.9 | 1117.5 | 0.48 | 0.69 | 0.0% |
| door -x-y (y wall) 2 | 1435 | 4.7 | 1125.3 | 0.40 | 0.69 | 0.0% |
| door -x-y (y wall) 3 | 1038 | 4.9 | 1135.0 | 0.29 | 0.69 | 0.0% |
| door -x-y (y wall) 4 | 685 | 4.9 | 1134.4 | 0.19 | 0.69 | 0.0% |
| door -x-y (x wall) 0 | 1497 | 4.9 | 952.4 | 0.49 | 0.69 | 0.0% |
| door -x-y (x wall) 1 | 1683 | 5.1 | 1088.6 | 0.48 | 0.69 | 0.0% |
| door -x-y (x wall) 2 | 1510 | 4.9 | 1126.9 | 0.42 | 0.72 | 0.0% |
| door -x-y (x wall) 3 | 1046 | 4.9 | 1135.7 | 0.29 | 0.66 | 0.0% |
| door -x-y (x wall) 4 | 675 | 5.1 | 1124.3 | 0.19 | 0.66 | 0.0% |
| door -x-y (corner) | 533 | 6.3 | 937.7 | 0.18 | 0.66 | 0.0% |
| door +x-y (y wall) 0 | 1501 | 4.9 | 948.7 | 0.50 | 0.66 | 0.0% |
| door +x-y (y wall) 1 | 1703 | 4.9 | 1098.2 | 0.49 | 0.66 | 0.0% |
| door +x-y (y wall) 2 | 1523 | 4.9 | 1124.8 | 0.42 | 0.72 | 0.0% |
| door +x-y (y wall) 3 | 992 | 4.9 | 1124.0 | 0.28 | 0.72 | 0.0% |
| door +x-y (y wall) 4 | 677 | 5.1 | 1114.9 | 0.19 | 0.69 | 0.0% |
| door +x-y (x wall) 0 | 1501 | 4.9 | 944.1 | 0.50 | 0.66 | 0.0% |
| door +x-y (x wall) 1 | 1698 | 4.9 | 1132.7 | 0.47 | 0.72 | 0.0% |
| door +x-y (x wall) 2 | 1484 | 4.9 | 1119.2 | 0.42 | 0.72 | 0.0% |
| door +x-y (x wall) 3 | 1084 | 4.9 | 1121.0 | 0.30 | 0.69 | 0.0% |
| door +x-y (x wall) 4 | 703 | 5.1 | 1104.5 | 0.20 | 0.72 | 0.0% |
| door +x-y (corner) | 428 | 6.5 | 1029.3 | 0.13 | 0.69 | 0.0% |

Mean flow / w J averaged over the doors 0.36, over the avenues 0.28.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 103.1 | 2186 | 1486 / 700 / 797 | 0.7 | 866.1 | 3.45 | 6.02 | 87% | 84% | 3% | 4.59 |
| straight +x+y (y wing) 1 | 1.20 | 81.5 | 1808 | 1713 / 0 / 235 | 0.7 | 1073.6 | 1.82 | 3.41 | 90% | 75% | 15% | 3.77 |
| straight +x+y (y wing) 2 | 1.20 | 61.0 | 1448 | 1535 / 0 / 116 | 0.7 | 1135.0 | 1.46 | 4.21 | 73% | 61% | 11% | 3.86 |
| straight +x+y (y wing) 3 | 1.20 | 39.4 | 879 | 1082 / 0 / 19 | 0.7 | 1121.3 | 0.98 | 2.31 | 45% | 39% | 6% | 3.74 |
| straight +x+y (y wing) 4 | 1.20 | 18.8 | 387 | 647 / 0 / 15 | 0.7 | 1122.4 | 0.59 | 2.11 | 18% | 17% | 1% | 4.03 |
| straight +x+y (x wing) 0 | 1.20 | 103.1 | 2200 | 1475 / 725 / 924 | 0.7 | 836.9 | 3.74 | 6.32 | 89% | 87% | 2% | 4.55 |
| straight +x+y (x wing) 1 | 1.20 | 81.5 | 1793 | 1699 / 0 / 260 | 0.7 | 1097.2 | 1.79 | 3.61 | 89% | 75% | 14% | 3.69 |
| straight +x+y (x wing) 2 | 1.20 | 61.0 | 1439 | 1517 / 0 / 22 | 0.7 | 1110.5 | 1.39 | 2.11 | 79% | 65% | 13% | 3.75 |
| straight +x+y (x wing) 3 | 1.20 | 39.4 | 875 | 1047 / 0 / 28 | 0.7 | 1137.4 | 0.95 | 2.41 | 43% | 37% | 6% | 3.80 |
| straight +x+y (x wing) 4 | 1.20 | 18.8 | 377 | 672 / 0 / 18 | 0.7 | 1082.8 | 0.64 | 2.21 | 21% | 16% | 6% | 3.45 |
| corner +x+y | 1.20 | 186.0 | 1662 | 417 / 339 / 1427 | 0.7 | 1098.6 | 1.99 | 4.81 | 89% | 66% | 23% | 2.64 |
| straight -x+y (y wing) 0 | 1.20 | 103.1 | 2248 | 1493 / 755 / 1070 | 0.7 | 843.2 | 3.94 | 6.32 | 89% | 87% | 2% | 4.62 |
| straight -x+y (y wing) 1 | 1.20 | 81.5 | 1746 | 1688 / 0 / 165 | 0.7 | 1022.2 | 1.81 | 3.21 | 90% | 79% | 12% | 3.98 |
| straight -x+y (y wing) 2 | 1.20 | 61.0 | 1449 | 1541 / 0 / 14 | 0.7 | 1095.3 | 1.42 | 2.41 | 70% | 65% | 5% | 4.01 |
| straight -x+y (y wing) 3 | 1.20 | 39.4 | 878 | 1103 / 0 / 7 | 0.7 | 1108.4 | 1.00 | 2.21 | 49% | 38% | 12% | 3.46 |
| straight -x+y (y wing) 4 | 1.20 | 18.8 | 387 | 641 / 0 / 35 | 0.7 | 1004.8 | 0.67 | 2.21 | 18% | 17% | 1% | 3.96 |
| straight -x+y (x wing) 0 | 1.20 | 103.1 | 2210 | 1477 / 733 / 783 | 0.7 | 840.4 | 3.56 | 5.82 | 88% | 86% | 2% | 4.62 |
| straight -x+y (x wing) 1 | 1.20 | 81.5 | 1767 | 1701 / 0 / 166 | 0.7 | 1117.8 | 1.67 | 3.31 | 81% | 72% | 9% | 4.18 |
| straight -x+y (x wing) 2 | 1.20 | 61.0 | 1449 | 1538 / 0 / 21 | 0.7 | 1107.5 | 1.41 | 2.31 | 71% | 62% | 9% | 4.01 |
| straight -x+y (x wing) 3 | 1.20 | 39.4 | 869 | 1120 / 0 / 8 | 0.7 | 1116.1 | 1.01 | 2.41 | 46% | 38% | 7% | 3.74 |
| straight -x+y (x wing) 4 | 1.20 | 18.8 | 365 | 632 / 0 / 32 | 0.7 | 1030.4 | 0.64 | 2.11 | 18% | 18% | 0% | 4.04 |
| corner -x+y | 1.20 | 186.0 | 1704 | 374 / 276 / 1388 | 0.7 | 1066.1 | 1.91 | 4.21 | 92% | 69% | 22% | 2.77 |
| straight -x-y (y wing) 0 | 1.20 | 103.1 | 2198 | 1481 / 717 / 820 | 0.7 | 856.5 | 3.53 | 6.22 | 90% | 85% | 5% | 4.58 |
| straight -x-y (y wing) 1 | 1.20 | 81.5 | 1802 | 1729 / 0 / 225 | 0.7 | 1114.5 | 1.75 | 3.71 | 84% | 71% | 12% | 3.91 |
| straight -x-y (y wing) 2 | 1.20 | 61.0 | 1438 | 1513 / 0 / 24 | 0.7 | 1122.4 | 1.37 | 2.21 | 74% | 63% | 12% | 3.82 |
| straight -x-y (y wing) 3 | 1.20 | 39.4 | 870 | 1010 / 0 / 38 | 0.7 | 1132.0 | 0.93 | 2.21 | 46% | 39% | 7% | 3.63 |
| straight -x-y (y wing) 4 | 1.20 | 18.8 | 379 | 635 / 0 / 20 | 0.7 | 1131.5 | 0.58 | 2.21 | 20% | 15% | 5% | 3.46 |
| straight -x-y (x wing) 0 | 1.20 | 103.1 | 2182 | 1465 / 717 / 796 | 0.7 | 852.5 | 3.50 | 5.62 | 90% | 84% | 6% | 4.54 |
| straight -x-y (x wing) 1 | 1.20 | 81.5 | 1812 | 1715 / 0 / 230 | 0.7 | 1085.6 | 1.79 | 3.81 | 90% | 76% | 14% | 3.77 |
| straight -x-y (x wing) 2 | 1.20 | 61.0 | 1458 | 1536 / 0 / 114 | 0.7 | 1124.0 | 1.47 | 2.81 | 76% | 63% | 13% | 3.82 |
| straight -x-y (x wing) 3 | 1.20 | 39.4 | 891 | 1066 / 0 / 23 | 0.7 | 1132.7 | 0.96 | 2.21 | 43% | 38% | 5% | 3.93 |
| straight -x-y (x wing) 4 | 1.20 | 18.8 | 380 | 629 / 0 / 28 | 0.7 | 1121.3 | 0.59 | 2.31 | 16% | 16% | 0% | 4.08 |
| corner -x-y | 1.20 | 186.0 | 1654 | 533 / 318 / 1331 | 0.7 | 1107.5 | 1.97 | 4.31 | 89% | 65% | 24% | 2.62 |
| straight +x-y (y wing) 0 | 1.20 | 103.1 | 2218 | 1476 / 742 / 900 | 0.7 | 843.2 | 3.70 | 5.82 | 89% | 86% | 4% | 4.56 |
| straight +x-y (y wing) 1 | 1.20 | 81.5 | 1802 | 1728 / 0 / 205 | 0.7 | 1095.3 | 1.77 | 3.81 | 88% | 73% | 15% | 3.92 |
| straight +x-y (y wing) 2 | 1.20 | 61.0 | 1414 | 1567 / 0 / 15 | 0.7 | 1121.9 | 1.41 | 2.61 | 68% | 65% | 4% | 4.11 |
| straight +x-y (y wing) 3 | 1.20 | 39.4 | 889 | 1028 / 0 / 19 | 0.7 | 1121.0 | 0.93 | 2.31 | 50% | 42% | 8% | 3.57 |
| straight +x-y (y wing) 4 | 1.20 | 18.8 | 380 | 597 / 0 / 60 | 0.7 | 1111.9 | 0.59 | 2.31 | 20% | 17% | 3% | 3.58 |
| straight +x-y (x wing) 0 | 1.20 | 103.1 | 2208 | 1480 / 728 / 770 | 0.7 | 834.0 | 3.57 | 5.72 | 89% | 87% | 2% | 4.58 |
| straight +x-y (x wing) 1 | 1.20 | 81.5 | 1780 | 1719 / 0 / 206 | 0.7 | 1129.7 | 1.70 | 3.31 | 84% | 68% | 16% | 3.77 |
| straight +x-y (x wing) 2 | 1.20 | 61.0 | 1464 | 1555 / 0 / 13 | 0.7 | 1116.3 | 1.41 | 2.21 | 74% | 67% | 7% | 3.97 |
| straight +x-y (x wing) 3 | 1.20 | 39.4 | 863 | 1050 / 0 / 11 | 0.7 | 1118.0 | 0.95 | 2.11 | 42% | 38% | 4% | 3.86 |
| straight +x-y (x wing) 4 | 1.20 | 18.8 | 388 | 666 / 0 / 16 | 0.7 | 1101.6 | 0.62 | 2.21 | 17% | 16% | 1% | 4.01 |
| corner +x-y | 1.20 | 186.0 | 1657 | 428 / 299 / 1302 | 0.7 | 1087.9 | 1.87 | 4.71 | 90% | 70% | 20% | 2.67 |

The last agent out (agent 826, t100 1140.4 s): last gangway straight +x+y (x wing) 3, exit door +x+y (x wall) 3. The gangway that cleared last: straight +x+y (x wing) 3 at 1137.4 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 8804 | 7800.4 | 6.93 | 1134.8 / 1061.9 / 1007.8 | 1050.5 / 1038.2 / 978.6 | 5017818.6 | 10288108 | 0.203 |
| gangway | 3792 | 3512.9 | 6.93 | 1132.9 / 1061.9 / 1007.8 | 1050.5 / 1038.2 / 978.6 | 5017818.6 | 9584219 | 0.131 |
| walkway | 276 | 257.4 | 4.04 | 562.3 / 346.7 / 0.0 | 412.1 / 233.3 / 0.0 | 0.0 | 74425 | 0.666 |
| avenue | 1920 | 1801.4 | 1.89 | 747.0 / 0.0 / 0.0 | 557.3 / 0.0 / 0.0 | 0.0 | 422465 | 1.334 |
| exit | 4 | 2.0 | 0.00 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 0 | - |
| concourse | 2812 | 2226.8 | 2.89 | 1118.2 / 72.6 / 0.0 | 931.7 / 18.5 / 0.0 | 0.0 | 206999 | 1.049 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 25392 | 16030.4 | 7.76 | 1002.9 / 994.3 / 983.5 | 996.4 / 994.3 / 977.9 | 5718556.4 | 14872066 | 0.032 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 208 x 208 from (-104, -104) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 36.5 | -36.5 | gangway | 1.00 | 6.03 | 1023.9 | 1021.5 | 954.1 | 5670.1 | 0.008 |
| 2 | 36.5 | 36.5 | gangway | 1.00 | 5.83 | 1031.4 | 1029.0 | 961.6 | 5485.2 | 0.012 |
| 3 | 35.5 | 35.5 | gangway | 1.00 | 5.80 | 1026.4 | 1021.6 | 954.6 | 5424.1 | 0.009 |
| 4 | 34.5 | 34.5 | gangway | 1.00 | 5.98 | 1021.3 | 1012.9 | 938.9 | 5410.6 | 0.009 |
| 5 | -35.5 | 35.5 | gangway | 1.00 | 6.01 | 1008.3 | 1003.1 | 928.2 | 5410.6 | 0.012 |
| 6 | 34.5 | -34.5 | gangway | 1.00 | 5.76 | 1015.2 | 1002.9 | 950.8 | 5389.2 | 0.008 |
| 7 | -34.5 | 34.5 | gangway | 1.00 | 5.80 | 1004.0 | 991.5 | 944.5 | 5310.2 | 0.010 |
| 8 | 35.5 | -35.5 | gangway | 1.00 | 5.63 | 1019.4 | 1013.6 | 961.6 | 5297.4 | 0.009 |
| 9 | -35.5 | -35.5 | gangway | 1.00 | 5.88 | 1028.6 | 1023.6 | 968.3 | 5253.0 | 0.012 |
| 10 | 33.5 | 33.5 | gangway | 0.99 | 5.62 | 1008.0 | 998.7 | 952.0 | 5118.3 | 0.008 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -38.5 | -36.5 | seat row | 0.50 | 7.40 | 992.1 | 988.0 | 968.6 | 3468.2 | 0.005 |
| 2 | 38.5 | 36.5 | seat row | 0.50 | 7.33 | 988.7 | 985.9 | 969.2 | 3446.9 | 0.007 |
| 3 | -36.5 | -38.5 | seat row | 0.50 | 7.36 | 996.4 | 994.3 | 977.9 | 3340.5 | 0.006 |
| 4 | 36.5 | 38.5 | seat row | 0.50 | 7.12 | 966.9 | 959.2 | 950.8 | 3317.4 | 0.006 |
| 5 | -38.5 | -35.5 | seat row | 0.50 | 7.19 | 971.4 | 960.6 | 944.3 | 3303.7 | 0.005 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 7645; agent-steps of seated agents on another row's clearway: 1677998.

## Deposit check

Person-seconds deposited: 25165739.1, of them in excluded cells: 5565.311.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 5139900 overlapping pair-steps: p99 0.0030, max 0.1028 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0030 max 0.1028; venue-geometry 13: p99 0.0008 max 0.0008 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00756 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 51 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.45 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 3766 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
