# Experiment `L_load95_s3`

**Task 5.9 stage 4: venue L, 95% load (seed 3), default model**

Venue L (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (4000 x 4000), cache key a2f3aaf59c2252b7, content hash 022d17b202313d70). 60253 agents on 95% of the 63424 seats (spawnSeatedCrowd, seed 3), buffer N = 65536, 8176 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 10866977 evaluations, 593550 switches, 0 forced choices).
Capacity: **within design capacity** (the L venue's design capacity 63424, jam capacity 171923: 23822.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-21T17:53:26, 914.2 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 2886 | 504.8 |
| t90 | 5900 | 1031.9 |
| t100 | 8176 | 1430.0 |

t_p: the step by which ceil(p x 60253) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 1992 | 0 | 70.8 | 1123.1 | 20.1 | 25.5 | 79.1-89.0 |
| -x | 5.66 | 2008 | 0 | 70.5 | 1123.1 | 20.2 | 26.6 | 80.8-90.8 |
| +y | 5.66 | 1989 | 0 | 70.8 | 1118.5 | 20.1 | 26.6 | 376.4-386.4 |
| -y | 5.66 | 2033 | 0 | 70.5 | 1118.9 | 20.6 | 26.6 | 366.4-376.4 |
| door +x+y (y wall) 0 | 2.30 | 1454 | 2455 | 4.9 | 1193.9 | 31.9 | 44.5 | 4.7-14.7 |
| door +x+y (y wall) 1 | 2.30 | 1609 | 2043 | 4.9 | 1398.4 | 30.1 | 44.5 | 4.5-14.5 |
| door +x+y (y wall) 2 | 2.30 | 1470 | 1511 | 4.9 | 1378.4 | 27.9 | 44.5 | 9.4-19.4 |
| door +x+y (y wall) 3 | 2.30 | 1044 | 983 | 4.9 | 1412.5 | 19.3 | 47.1 | 23.6-33.6 |
| door +x+y (y wall) 4 | 2.30 | 713 | 480 | 5.1 | 1325.3 | 14.1 | 44.5 | 7.5-17.5 |
| door +x+y (x wall) 0 | 2.30 | 1463 | 2431 | 4.9 | 1182.0 | 32.4 | 44.5 | 8.6-18.5 |
| door +x+y (x wall) 1 | 2.30 | 1604 | 2045 | 4.9 | 1390.2 | 30.2 | 47.1 | 25.4-35.3 |
| door +x+y (x wall) 2 | 2.30 | 1493 | 1502 | 4.9 | 1413.8 | 27.6 | 44.5 | 5.9-15.9 |
| door +x+y (x wall) 3 | 2.30 | 1058 | 1000 | 4.9 | 1389.3 | 19.9 | 41.9 | 4.2-14.2 |
| door +x+y (x wall) 4 | 2.30 | 723 | 486 | 5.1 | 1396.1 | 13.6 | 49.7 | 19.1-29.0 |
| door +x+y (corner) | 2.30 | 416 | 118 | 6.3 | 1127.3 | 9.7 | 44.5 | 43.6-53.5 |
| door -x+y (y wall) 0 | 2.30 | 1454 | 2467 | 4.9 | 1131.6 | 33.7 | 44.5 | 21.9-31.8 |
| door -x+y (y wall) 1 | 2.30 | 1612 | 2035 | 4.9 | 1426.7 | 29.6 | 44.5 | 12.8-22.7 |
| door -x+y (y wall) 2 | 2.30 | 1497 | 1508 | 4.9 | 1424.4 | 27.5 | 47.1 | 19.6-29.6 |
| door -x+y (y wall) 3 | 2.30 | 1116 | 1001 | 4.9 | 1370.7 | 21.3 | 47.1 | 14.5-24.5 |
| door -x+y (y wall) 4 | 2.30 | 657 | 481 | 5.1 | 1422.5 | 12.1 | 44.5 | 20.8-30.8 |
| door -x+y (x wall) 0 | 2.30 | 1452 | 2460 | 4.9 | 1122.4 | 33.9 | 44.5 | 14.2-24.1 |
| door -x+y (x wall) 1 | 2.30 | 1609 | 2022 | 4.9 | 1326.0 | 31.8 | 47.1 | 20.6-30.6 |
| door -x+y (x wall) 2 | 2.30 | 1523 | 1499 | 4.9 | 1418.5 | 28.1 | 47.1 | 28.2-38.1 |
| door -x+y (x wall) 3 | 2.30 | 1037 | 1001 | 4.9 | 1426.0 | 19.0 | 47.1 | 22.0-32.0 |
| door -x+y (x wall) 4 | 2.30 | 682 | 479 | 4.9 | 1430.0 | 12.5 | 47.1 | 24.8-34.8 |
| door -x+y (corner) | 2.30 | 420 | 119 | 6.3 | 1083.4 | 10.2 | 47.1 | 195.7-205.7 |
| door -x-y (y wall) 0 | 2.30 | 1448 | 2461 | 4.9 | 1093.7 | 34.7 | 44.5 | 28.0-38.0 |
| door -x-y (y wall) 1 | 2.30 | 1641 | 2005 | 4.9 | 1360.2 | 31.6 | 44.5 | 14.2-24.1 |
| door -x-y (y wall) 2 | 2.30 | 1511 | 1528 | 4.7 | 1409.6 | 28.1 | 47.1 | 14.5-24.5 |
| door -x-y (y wall) 3 | 2.30 | 1109 | 982 | 4.9 | 1413.6 | 20.5 | 44.5 | 9.6-19.6 |
| door -x-y (y wall) 4 | 2.30 | 554 | 489 | 4.9 | 1402.8 | 10.3 | 47.1 | 20.6-30.6 |
| door -x-y (x wall) 0 | 2.30 | 1469 | 2455 | 4.9 | 1202.7 | 32.0 | 44.5 | 18.2-28.2 |
| door -x-y (x wall) 1 | 2.30 | 1609 | 2027 | 5.1 | 1352.6 | 31.1 | 44.5 | 9.3-19.2 |
| door -x-y (x wall) 2 | 2.30 | 1521 | 1514 | 4.9 | 1409.6 | 28.2 | 47.1 | 30.6-40.6 |
| door -x-y (x wall) 3 | 2.30 | 1114 | 998 | 4.9 | 1409.4 | 20.7 | 44.5 | 8.7-18.7 |
| door -x-y (x wall) 4 | 2.30 | 671 | 487 | 5.1 | 1388.4 | 12.7 | 44.5 | 13.3-23.3 |
| door -x-y (corner) | 2.30 | 407 | 118 | 6.3 | 1302.0 | 8.2 | 47.1 | 67.3-77.3 |
| door +x-y (y wall) 0 | 2.30 | 1460 | 2439 | 4.9 | 1102.3 | 34.7 | 44.5 | 8.7-18.7 |
| door +x-y (y wall) 1 | 2.30 | 1623 | 2026 | 4.9 | 1407.1 | 30.2 | 47.1 | 11.5-21.5 |
| door +x-y (y wall) 2 | 2.30 | 1458 | 1517 | 4.9 | 1390.7 | 27.4 | 44.5 | 26.9-36.9 |
| door +x-y (y wall) 3 | 2.30 | 1130 | 998 | 4.9 | 1401.0 | 21.1 | 44.5 | 11.5-21.5 |
| door +x-y (y wall) 4 | 2.30 | 651 | 488 | 5.1 | 1367.1 | 12.5 | 44.5 | 19.9-29.9 |
| door +x-y (x wall) 0 | 2.30 | 1448 | 2440 | 4.9 | 1140.9 | 33.2 | 44.5 | 8.6-18.5 |
| door +x-y (x wall) 1 | 2.30 | 1605 | 2030 | 4.9 | 1358.5 | 30.9 | 44.5 | 28.2-38.1 |
| door +x-y (x wall) 2 | 2.30 | 1505 | 1519 | 4.9 | 1406.1 | 28.0 | 49.7 | 9.6-19.6 |
| door +x-y (x wall) 3 | 2.30 | 1077 | 993 | 4.9 | 1373.9 | 20.5 | 44.5 | 9.4-19.4 |
| door +x-y (x wall) 4 | 2.30 | 673 | 490 | 5.1 | 1405.9 | 12.5 | 49.7 | 24.8-34.8 |
| door +x-y (corner) | 2.30 | 441 | 123 | 6.5 | 1065.4 | 10.9 | 47.1 | 65.4-75.4 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (2.30 m; a corner door's: the gap between its wall ends, 2.30 m); agents are removed past the outer wall's outer face (92.71 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 1992 | 3.3% | 17.7% |
| -x | avenue | 5.66 | 2008 | 3.3% | 17.8% |
| +y | avenue | 5.66 | 1989 | 3.3% | 17.6% |
| -y | avenue | 5.66 | 2033 | 3.4% | 18.0% |
| door +x+y (y wall) 0 | door | 2.30 | 1454 | 2.4% | 31.7% |
| door +x+y (y wall) 1 | door | 2.30 | 1609 | 2.7% | 35.1% |
| door +x+y (y wall) 2 | door | 2.30 | 1470 | 2.4% | 32.1% |
| door +x+y (y wall) 3 | door | 2.30 | 1044 | 1.7% | 22.8% |
| door +x+y (y wall) 4 | door | 2.30 | 713 | 1.2% | 15.6% |
| door +x+y (x wall) 0 | door | 2.30 | 1463 | 2.4% | 31.9% |
| door +x+y (x wall) 1 | door | 2.30 | 1604 | 2.7% | 35.0% |
| door +x+y (x wall) 2 | door | 2.30 | 1493 | 2.5% | 32.6% |
| door +x+y (x wall) 3 | door | 2.30 | 1058 | 1.8% | 23.1% |
| door +x+y (x wall) 4 | door | 2.30 | 723 | 1.2% | 15.8% |
| door +x+y (corner) | door | 2.30 | 416 | 0.7% | 9.1% |
| door -x+y (y wall) 0 | door | 2.30 | 1454 | 2.4% | 31.7% |
| door -x+y (y wall) 1 | door | 2.30 | 1612 | 2.7% | 35.2% |
| door -x+y (y wall) 2 | door | 2.30 | 1497 | 2.5% | 32.7% |
| door -x+y (y wall) 3 | door | 2.30 | 1116 | 1.9% | 24.4% |
| door -x+y (y wall) 4 | door | 2.30 | 657 | 1.1% | 14.3% |
| door -x+y (x wall) 0 | door | 2.30 | 1452 | 2.4% | 31.7% |
| door -x+y (x wall) 1 | door | 2.30 | 1609 | 2.7% | 35.1% |
| door -x+y (x wall) 2 | door | 2.30 | 1523 | 2.5% | 33.2% |
| door -x+y (x wall) 3 | door | 2.30 | 1037 | 1.7% | 22.6% |
| door -x+y (x wall) 4 | door | 2.30 | 682 | 1.1% | 14.9% |
| door -x+y (corner) | door | 2.30 | 420 | 0.7% | 9.2% |
| door -x-y (y wall) 0 | door | 2.30 | 1448 | 2.4% | 31.6% |
| door -x-y (y wall) 1 | door | 2.30 | 1641 | 2.7% | 35.8% |
| door -x-y (y wall) 2 | door | 2.30 | 1511 | 2.5% | 33.0% |
| door -x-y (y wall) 3 | door | 2.30 | 1109 | 1.8% | 24.2% |
| door -x-y (y wall) 4 | door | 2.30 | 554 | 0.9% | 12.1% |
| door -x-y (x wall) 0 | door | 2.30 | 1469 | 2.4% | 32.1% |
| door -x-y (x wall) 1 | door | 2.30 | 1609 | 2.7% | 35.1% |
| door -x-y (x wall) 2 | door | 2.30 | 1521 | 2.5% | 33.2% |
| door -x-y (x wall) 3 | door | 2.30 | 1114 | 1.8% | 24.3% |
| door -x-y (x wall) 4 | door | 2.30 | 671 | 1.1% | 14.6% |
| door -x-y (corner) | door | 2.30 | 407 | 0.7% | 8.9% |
| door +x-y (y wall) 0 | door | 2.30 | 1460 | 2.4% | 31.9% |
| door +x-y (y wall) 1 | door | 2.30 | 1623 | 2.7% | 35.4% |
| door +x-y (y wall) 2 | door | 2.30 | 1458 | 2.4% | 31.8% |
| door +x-y (y wall) 3 | door | 2.30 | 1130 | 1.9% | 24.7% |
| door +x-y (y wall) 4 | door | 2.30 | 651 | 1.1% | 14.2% |
| door +x-y (x wall) 0 | door | 2.30 | 1448 | 2.4% | 31.6% |
| door +x-y (x wall) 1 | door | 2.30 | 1605 | 2.7% | 35.0% |
| door +x-y (x wall) 2 | door | 2.30 | 1505 | 2.5% | 32.8% |
| door +x-y (x wall) 3 | door | 2.30 | 1077 | 1.8% | 23.5% |
| door +x-y (x wall) 4 | door | 2.30 | 673 | 1.1% | 14.7% |
| door +x-y (corner) | door | 2.30 | 441 | 0.7% | 9.6% |
| **doors (44)** | door | 101.20 | 52231 | 86.7% | |
| **avenues (4)** | avenue | 22.64 | 8022 | 13.3% | |

**Unused exit width: 0.0 of 123.8 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 1430.0 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 24.4%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 2216 | 3.7% | 2216 | 3.7% |
| straight +x+y (y wing) 1 | straight | yes | 1784 | 3.0% | 1613 | 2.7% |
| straight +x+y (y wing) 2 | straight | yes | 1528 | 2.5% | 1509 | 2.5% |
| straight +x+y (y wing) 3 | straight | yes | 1064 | 1.8% | 1050 | 1.7% |
| straight +x+y (y wing) 4 | straight | yes | 687 | 1.1% | 668 | 1.1% |
| straight +x+y (x wing) 0 | straight | yes | 2221 | 3.7% | 2221 | 3.7% |
| straight +x+y (x wing) 1 | straight | yes | 1787 | 3.0% | 1606 | 2.7% |
| straight +x+y (x wing) 2 | straight | yes | 1542 | 2.6% | 1530 | 2.5% |
| straight +x+y (x wing) 3 | straight | yes | 1082 | 1.8% | 1066 | 1.8% |
| straight +x+y (x wing) 4 | straight | yes | 701 | 1.2% | 678 | 1.1% |
| corner +x+y | corner | yes | 2183 | 3.6% | 897 | 1.5% |
| straight -x+y (y wing) 0 | straight | yes | 2233 | 3.7% | 2233 | 3.7% |
| straight -x+y (y wing) 1 | straight | yes | 1780 | 3.0% | 1613 | 2.7% |
| straight -x+y (y wing) 2 | straight | yes | 1530 | 2.5% | 1518 | 2.5% |
| straight -x+y (y wing) 3 | straight | yes | 1121 | 1.9% | 1115 | 1.9% |
| straight -x+y (y wing) 4 | straight | yes | 653 | 1.1% | 637 | 1.1% |
| straight -x+y (x wing) 0 | straight | yes | 2213 | 3.7% | 2213 | 3.7% |
| straight -x+y (x wing) 1 | straight | yes | 1774 | 2.9% | 1609 | 2.7% |
| straight -x+y (x wing) 2 | straight | yes | 1550 | 2.6% | 1540 | 2.6% |
| straight -x+y (x wing) 3 | straight | yes | 1074 | 1.8% | 1063 | 1.8% |
| straight -x+y (x wing) 4 | straight | yes | 652 | 1.1% | 639 | 1.1% |
| corner -x+y | corner | yes | 2138 | 3.5% | 892 | 1.5% |
| straight -x-y (y wing) 0 | straight | yes | 2227 | 3.7% | 2227 | 3.7% |
| straight -x-y (y wing) 1 | straight | yes | 1808 | 3.0% | 1641 | 2.7% |
| straight -x-y (y wing) 2 | straight | yes | 1526 | 2.5% | 1523 | 2.5% |
| straight -x-y (y wing) 3 | straight | yes | 1103 | 1.8% | 1099 | 1.8% |
| straight -x-y (y wing) 4 | straight | yes | 585 | 1.0% | 552 | 0.9% |
| straight -x-y (x wing) 0 | straight | yes | 2236 | 3.7% | 2236 | 3.7% |
| straight -x-y (x wing) 1 | straight | yes | 1788 | 3.0% | 1617 | 2.7% |
| straight -x-y (x wing) 2 | straight | yes | 1548 | 2.6% | 1536 | 2.5% |
| straight -x-y (x wing) 3 | straight | yes | 1127 | 1.9% | 1121 | 1.9% |
| straight -x-y (x wing) 4 | straight | yes | 664 | 1.1% | 649 | 1.1% |
| corner -x-y | corner | yes | 2073 | 3.4% | 863 | 1.4% |
| straight +x-y (y wing) 0 | straight | yes | 2221 | 3.7% | 2221 | 3.7% |
| straight +x-y (y wing) 1 | straight | yes | 1789 | 3.0% | 1623 | 2.7% |
| straight +x-y (y wing) 2 | straight | yes | 1512 | 2.5% | 1496 | 2.5% |
| straight +x-y (y wing) 3 | straight | yes | 1098 | 1.8% | 1092 | 1.8% |
| straight +x-y (y wing) 4 | straight | yes | 676 | 1.1% | 651 | 1.1% |
| straight +x-y (x wing) 0 | straight | yes | 2221 | 3.7% | 2221 | 3.7% |
| straight +x-y (x wing) 1 | straight | yes | 1770 | 2.9% | 1607 | 2.7% |
| straight +x-y (x wing) 2 | straight | yes | 1544 | 2.6% | 1528 | 2.5% |
| straight +x-y (x wing) 3 | straight | yes | 1102 | 1.8% | 1094 | 1.8% |
| straight +x-y (x wing) 4 | straight | yes | 649 | 1.1% | 633 | 1.1% |
| corner +x-y | corner | yes | 2173 | 3.6% | 897 | 1.5% |
| **straight (40)** | | | 58386 | | 56704 | 94.1% |
| **corner (4)** | | | 8567 | | 3549 | 5.9% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 1992 | 70.8 | 1123.1 | 0.24 | 0.31 | 0.0% |
| -x | 2008 | 70.5 | 1123.1 | 0.24 | 0.32 | 0.0% |
| +y | 1989 | 70.8 | 1118.5 | 0.24 | 0.32 | 0.0% |
| -y | 2033 | 70.5 | 1118.9 | 0.25 | 0.32 | 0.0% |
| door +x+y (y wall) 0 | 1454 | 4.9 | 1193.9 | 0.38 | 0.53 | 0.0% |
| door +x+y (y wall) 1 | 1609 | 4.9 | 1398.4 | 0.36 | 0.53 | 0.0% |
| door +x+y (y wall) 2 | 1470 | 4.9 | 1378.4 | 0.33 | 0.53 | 0.0% |
| door +x+y (y wall) 3 | 1044 | 4.9 | 1412.5 | 0.23 | 0.56 | 0.0% |
| door +x+y (y wall) 4 | 713 | 5.1 | 1325.3 | 0.17 | 0.53 | 0.0% |
| door +x+y (x wall) 0 | 1463 | 4.9 | 1182.0 | 0.39 | 0.53 | 0.0% |
| door +x+y (x wall) 1 | 1604 | 4.9 | 1390.2 | 0.36 | 0.56 | 0.0% |
| door +x+y (x wall) 2 | 1493 | 4.9 | 1413.8 | 0.33 | 0.53 | 0.0% |
| door +x+y (x wall) 3 | 1058 | 4.9 | 1389.3 | 0.24 | 0.50 | 0.0% |
| door +x+y (x wall) 4 | 723 | 5.1 | 1396.1 | 0.16 | 0.59 | 0.0% |
| door +x+y (corner) | 416 | 6.3 | 1127.3 | 0.12 | 0.53 | 0.0% |
| door -x+y (y wall) 0 | 1454 | 4.9 | 1131.6 | 0.40 | 0.53 | 0.0% |
| door -x+y (y wall) 1 | 1612 | 4.9 | 1426.7 | 0.35 | 0.53 | 0.0% |
| door -x+y (y wall) 2 | 1497 | 4.9 | 1424.4 | 0.33 | 0.56 | 0.0% |
| door -x+y (y wall) 3 | 1116 | 4.9 | 1370.7 | 0.25 | 0.56 | 0.0% |
| door -x+y (y wall) 4 | 657 | 5.1 | 1422.5 | 0.14 | 0.53 | 0.0% |
| door -x+y (x wall) 0 | 1452 | 4.9 | 1122.4 | 0.41 | 0.53 | 0.0% |
| door -x+y (x wall) 1 | 1609 | 4.9 | 1326.0 | 0.38 | 0.56 | 0.0% |
| door -x+y (x wall) 2 | 1523 | 4.9 | 1418.5 | 0.34 | 0.56 | 0.0% |
| door -x+y (x wall) 3 | 1037 | 4.9 | 1426.0 | 0.23 | 0.56 | 0.0% |
| door -x+y (x wall) 4 | 682 | 4.9 | 1430.0 | 0.15 | 0.56 | 0.0% |
| door -x+y (corner) | 420 | 6.3 | 1083.4 | 0.12 | 0.56 | 0.0% |
| door -x-y (y wall) 0 | 1448 | 4.9 | 1093.7 | 0.41 | 0.53 | 0.0% |
| door -x-y (y wall) 1 | 1641 | 4.9 | 1360.2 | 0.38 | 0.53 | 0.0% |
| door -x-y (y wall) 2 | 1511 | 4.7 | 1409.6 | 0.34 | 0.56 | 0.0% |
| door -x-y (y wall) 3 | 1109 | 4.9 | 1413.6 | 0.25 | 0.53 | 0.0% |
| door -x-y (y wall) 4 | 554 | 4.9 | 1402.8 | 0.12 | 0.56 | 0.0% |
| door -x-y (x wall) 0 | 1469 | 4.9 | 1202.7 | 0.38 | 0.53 | 0.0% |
| door -x-y (x wall) 1 | 1609 | 5.1 | 1352.6 | 0.37 | 0.53 | 0.0% |
| door -x-y (x wall) 2 | 1521 | 4.9 | 1409.6 | 0.34 | 0.56 | 0.0% |
| door -x-y (x wall) 3 | 1114 | 4.9 | 1409.4 | 0.25 | 0.53 | 0.0% |
| door -x-y (x wall) 4 | 671 | 5.1 | 1388.4 | 0.15 | 0.53 | 0.0% |
| door -x-y (corner) | 407 | 6.3 | 1302.0 | 0.10 | 0.56 | 0.0% |
| door +x-y (y wall) 0 | 1460 | 4.9 | 1102.3 | 0.42 | 0.53 | 0.0% |
| door +x-y (y wall) 1 | 1623 | 4.9 | 1407.1 | 0.36 | 0.56 | 0.0% |
| door +x-y (y wall) 2 | 1458 | 4.9 | 1390.7 | 0.33 | 0.53 | 0.0% |
| door +x-y (y wall) 3 | 1130 | 4.9 | 1401.0 | 0.25 | 0.53 | 0.0% |
| door +x-y (y wall) 4 | 651 | 5.1 | 1367.1 | 0.15 | 0.53 | 0.0% |
| door +x-y (x wall) 0 | 1448 | 4.9 | 1140.9 | 0.40 | 0.53 | 0.0% |
| door +x-y (x wall) 1 | 1605 | 4.9 | 1358.5 | 0.37 | 0.53 | 0.0% |
| door +x-y (x wall) 2 | 1505 | 4.9 | 1406.1 | 0.34 | 0.59 | 0.0% |
| door +x-y (x wall) 3 | 1077 | 4.9 | 1373.9 | 0.25 | 0.53 | 0.0% |
| door +x-y (x wall) 4 | 673 | 5.1 | 1405.9 | 0.15 | 0.59 | 0.0% |
| door +x-y (corner) | 441 | 6.5 | 1065.4 | 0.13 | 0.56 | 0.0% |

Mean flow / w J averaged over the doors 0.28, over the avenues 0.24.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 103.1 | 2216 | 1450 / 767 / 859 | 0.7 | 1098.8 | 2.80 | 4.51 | 92% | 86% | 5% | 4.42 |
| straight +x+y (y wing) 1 | 1.20 | 81.5 | 1765 | 1613 / 0 / 277 | 0.7 | 1395.4 | 1.35 | 2.51 | 90% | 64% | 26% | 3.34 |
| straight +x+y (y wing) 2 | 1.20 | 61.0 | 1456 | 1509 / 0 / 21 | 0.7 | 1375.5 | 1.11 | 1.71 | 80% | 70% | 11% | 3.86 |
| straight +x+y (y wing) 3 | 1.20 | 39.4 | 869 | 1050 / 0 / 18 | 0.7 | 1409.6 | 0.76 | 1.71 | 48% | 37% | 11% | 3.59 |
| straight +x+y (y wing) 4 | 1.20 | 18.8 | 382 | 668 / 0 / 22 | 0.7 | 1322.3 | 0.52 | 1.81 | 19% | 17% | 2% | 3.78 |
| straight +x+y (x wing) 0 | 1.20 | 103.1 | 2221 | 1461 / 760 / 969 | 0.7 | 1124.5 | 2.84 | 5.52 | 92% | 85% | 7% | 4.22 |
| straight +x+y (x wing) 1 | 1.20 | 81.5 | 1769 | 1606 / 0 / 265 | 0.7 | 1387.2 | 1.35 | 2.81 | 91% | 66% | 26% | 3.32 |
| straight +x+y (x wing) 2 | 1.20 | 61.0 | 1440 | 1530 / 0 / 14 | 0.7 | 1410.8 | 1.09 | 1.81 | 79% | 65% | 13% | 3.55 |
| straight +x+y (x wing) 3 | 1.20 | 39.4 | 871 | 1066 / 0 / 20 | 0.7 | 1386.3 | 0.78 | 1.60 | 48% | 41% | 7% | 3.62 |
| straight +x+y (x wing) 4 | 1.20 | 18.8 | 372 | 678 / 0 / 23 | 0.7 | 1393.1 | 0.50 | 1.81 | 19% | 16% | 3% | 3.55 |
| corner +x+y | 1.20 | 186.0 | 1693 | 416 / 481 / 1357 | 0.7 | 1369.2 | 1.65 | 3.41 | 92% | 56% | 36% | 2.48 |
| straight -x+y (y wing) 0 | 1.20 | 103.1 | 2233 | 1453 / 783 / 1144 | 0.7 | 1101.6 | 3.07 | 4.91 | 92% | 86% | 5% | 4.25 |
| straight -x+y (y wing) 1 | 1.20 | 81.5 | 1762 | 1613 / 0 / 259 | 0.7 | 1423.9 | 1.32 | 2.71 | 88% | 65% | 23% | 3.27 |
| straight -x+y (y wing) 2 | 1.20 | 61.0 | 1442 | 1518 / 0 / 14 | 0.7 | 1421.5 | 1.08 | 1.91 | 75% | 64% | 10% | 3.76 |
| straight -x+y (y wing) 3 | 1.20 | 39.4 | 892 | 1115 / 0 / 10 | 0.7 | 1367.8 | 0.82 | 1.60 | 49% | 38% | 11% | 3.58 |
| straight -x+y (y wing) 4 | 1.20 | 18.8 | 373 | 637 / 0 / 20 | 0.7 | 1419.5 | 0.46 | 1.81 | 17% | 16% | 1% | 3.76 |
| straight -x+y (x wing) 0 | 1.20 | 103.1 | 2213 | 1452 / 763 / 917 | 0.7 | 1119.4 | 2.80 | 5.22 | 92% | 85% | 7% | 4.39 |
| straight -x+y (x wing) 1 | 1.20 | 81.5 | 1764 | 1609 / 0 / 253 | 0.7 | 1323.0 | 1.41 | 2.51 | 92% | 69% | 23% | 3.40 |
| straight -x+y (x wing) 2 | 1.20 | 61.0 | 1451 | 1540 / 0 / 12 | 0.7 | 1415.5 | 1.10 | 1.81 | 78% | 66% | 12% | 3.69 |
| straight -x+y (x wing) 3 | 1.20 | 39.4 | 885 | 1063 / 0 / 21 | 0.7 | 1423.0 | 0.76 | 1.81 | 48% | 42% | 6% | 3.70 |
| straight -x+y (x wing) 4 | 1.20 | 18.8 | 360 | 639 / 0 / 14 | 0.7 | 1427.1 | 0.46 | 1.60 | 16% | 15% | 1% | 3.80 |
| corner -x+y | 1.20 | 186.0 | 1697 | 420 / 472 / 1317 | 0.7 | 1403.1 | 1.57 | 3.71 | 91% | 61% | 30% | 2.53 |
| straight -x-y (y wing) 0 | 1.20 | 103.1 | 2227 | 1448 / 779 / 943 | 0.7 | 1090.7 | 2.91 | 5.72 | 91% | 87% | 4% | 4.44 |
| straight -x-y (y wing) 1 | 1.20 | 81.5 | 1778 | 1641 / 0 / 258 | 0.7 | 1357.3 | 1.40 | 2.71 | 93% | 67% | 26% | 3.40 |
| straight -x-y (y wing) 2 | 1.20 | 61.0 | 1440 | 1523 / 0 / 11 | 0.7 | 1406.6 | 1.09 | 1.81 | 78% | 65% | 13% | 3.67 |
| straight -x-y (y wing) 3 | 1.20 | 39.4 | 870 | 1099 / 0 / 9 | 0.7 | 1410.6 | 0.79 | 1.71 | 46% | 37% | 9% | 3.55 |
| straight -x-y (y wing) 4 | 1.20 | 18.8 | 377 | 552 / 0 / 40 | 0.7 | 1399.8 | 0.42 | 1.71 | 17% | 16% | 1% | 3.68 |
| straight -x-y (x wing) 0 | 1.20 | 103.1 | 2236 | 1461 / 775 / 935 | 0.7 | 1100.0 | 2.88 | 5.12 | 91% | 86% | 5% | 4.23 |
| straight -x-y (x wing) 1 | 1.20 | 81.5 | 1768 | 1617 / 0 / 227 | 0.7 | 1349.6 | 1.37 | 2.91 | 90% | 71% | 19% | 3.62 |
| straight -x-y (x wing) 2 | 1.20 | 61.0 | 1454 | 1536 / 0 / 15 | 0.7 | 1406.6 | 1.10 | 1.81 | 77% | 65% | 12% | 3.68 |
| straight -x-y (x wing) 3 | 1.20 | 39.4 | 892 | 1121 / 0 / 14 | 0.7 | 1406.4 | 0.81 | 1.60 | 51% | 39% | 12% | 3.39 |
| straight -x-y (x wing) 4 | 1.20 | 18.8 | 389 | 649 / 0 / 16 | 0.7 | 1385.4 | 0.48 | 1.71 | 19% | 17% | 2% | 3.79 |
| corner -x-y | 1.20 | 186.0 | 1633 | 407 / 456 / 1278 | 0.7 | 1376.0 | 1.56 | 3.51 | 92% | 65% | 27% | 2.61 |
| straight +x-y (y wing) 0 | 1.20 | 103.1 | 2221 | 1460 / 761 / 1025 | 0.7 | 1099.3 | 2.95 | 5.32 | 91% | 86% | 5% | 4.29 |
| straight +x-y (y wing) 1 | 1.20 | 81.5 | 1779 | 1623 / 0 / 269 | 0.7 | 1404.2 | 1.35 | 2.91 | 87% | 65% | 22% | 3.39 |
| straight +x-y (y wing) 2 | 1.20 | 61.0 | 1417 | 1496 / 0 / 17 | 0.7 | 1387.7 | 1.09 | 1.81 | 77% | 66% | 11% | 3.69 |
| straight +x-y (y wing) 3 | 1.20 | 39.4 | 878 | 1092 / 0 / 68 | 0.7 | 1398.0 | 0.83 | 2.51 | 48% | 38% | 11% | 3.54 |
| straight +x-y (y wing) 4 | 1.20 | 18.8 | 377 | 651 / 0 / 25 | 0.7 | 1364.1 | 0.50 | 1.81 | 18% | 16% | 1% | 3.85 |
| straight +x-y (x wing) 0 | 1.20 | 103.1 | 2221 | 1446 / 775 / 920 | 0.7 | 1097.0 | 2.86 | 5.32 | 92% | 86% | 6% | 4.26 |
| straight +x-y (x wing) 1 | 1.20 | 81.5 | 1752 | 1607 / 0 / 246 | 0.7 | 1355.5 | 1.37 | 2.81 | 93% | 68% | 25% | 3.24 |
| straight +x-y (x wing) 2 | 1.20 | 61.0 | 1460 | 1528 / 0 / 20 | 0.7 | 1403.1 | 1.10 | 2.01 | 79% | 69% | 10% | 3.71 |
| straight +x-y (x wing) 3 | 1.20 | 39.4 | 879 | 1094 / 0 / 10 | 0.7 | 1370.9 | 0.81 | 1.71 | 48% | 41% | 7% | 3.67 |
| straight +x-y (x wing) 4 | 1.20 | 18.8 | 363 | 633 / 0 / 21 | 0.7 | 1402.9 | 0.47 | 1.81 | 19% | 15% | 4% | 3.37 |
| corner +x-y | 1.20 | 186.0 | 1716 | 441 / 456 / 1395 | 0.7 | 1379.0 | 1.66 | 3.61 | 91% | 55% | 37% | 2.52 |

The last agent out (agent 23438, t100 1430.0 s): last gangway straight -x+y (x wing) 4, exit door -x+y (x wall) 4. The gangway that cleared last: straight -x+y (x wing) 4 at 1427.1 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 8804 | 7800.4 | 7.03 | 1420.6 / 1328.6 / 1287.3 | 1330.9 / 1314.1 / 1266.8 | 6480337.3 | 12559732 | 0.171 |
| gangway | 3792 | 3512.9 | 7.03 | 1419.0 / 1328.6 / 1287.3 | 1330.9 / 1314.1 / 1266.8 | 6480337.3 | 11809468 | 0.105 |
| walkway | 276 | 257.4 | 3.35 | 696.0 / 327.8 / 0.0 | 395.5 / 106.9 / 0.0 | 0.0 | 70533 | 0.819 |
| avenue | 1920 | 1801.4 | 1.98 | 731.8 / 0.0 / 0.0 | 492.0 / 0.0 / 0.0 | 0.0 | 480782 | 1.334 |
| exit | 4 | 2.0 | 0.00 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 0 | - |
| concourse | 2812 | 2226.8 | 2.62 | 1351.9 / 29.2 / 0.0 | 1009.4 / 3.7 / 0.0 | 0.0 | 198949 | 1.043 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 25392 | 16030.4 | 7.86 | 1279.8 / 1274.0 / 1258.3 | 1279.8 / 1274.0 / 1254.4 | 7819191.4 | 19830838 | 0.023 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 208 x 208 from (-104, -104) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 34.5 | -34.5 | gangway | 1.00 | 6.01 | 1295.9 | 1280.3 | 1242.9 | 7026.2 | 0.006 |
| 2 | -36.5 | -36.5 | gangway | 1.00 | 5.72 | 1312.7 | 1299.0 | 1228.5 | 6915.8 | 0.008 |
| 3 | -35.5 | -35.5 | gangway | 1.00 | 5.63 | 1310.6 | 1301.1 | 1266.8 | 6842.6 | 0.008 |
| 4 | 33.5 | -33.5 | gangway | 0.99 | 5.74 | 1286.8 | 1278.4 | 1233.6 | 6739.4 | 0.005 |
| 5 | 36.5 | -36.5 | gangway | 1.00 | 5.66 | 1303.9 | 1285.2 | 1210.2 | 6667.6 | 0.008 |
| 6 | 36.5 | 36.5 | gangway | 1.00 | 5.74 | 1302.7 | 1280.5 | 1200.7 | 6589.0 | 0.008 |
| 7 | -42.5 | 43.5 | gangway | 1.00 | 6.38 | 1140.7 | 1129.4 | 1043.8 | 6540.3 | 0.014 |
| 8 | -34.5 | -34.5 | gangway | 1.00 | 5.63 | 1306.9 | 1296.1 | 1245.2 | 6517.7 | 0.005 |
| 9 | 37.5 | 37.5 | gangway | 0.99 | 5.76 | 1307.6 | 1281.2 | 1180.4 | 6475.9 | 0.012 |
| 10 | -38.5 | -38.5 | gangway | 1.00 | 5.75 | 1317.2 | 1278.6 | 1176.6 | 6454.8 | 0.012 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 38.5 | 36.5 | seat row | 0.50 | 7.42 | 1260.2 | 1258.3 | 1244.8 | 4492.7 | 0.004 |
| 2 | -36.5 | -38.5 | seat row | 0.50 | 7.29 | 1269.1 | 1262.5 | 1254.4 | 4485.4 | 0.003 |
| 3 | 36.5 | 38.5 | seat row | 0.50 | 7.22 | 1264.2 | 1260.0 | 1249.4 | 4417.3 | 0.004 |
| 4 | -36.5 | 38.5 | seat row | 0.50 | 7.23 | 1261.4 | 1256.4 | 1238.7 | 4408.2 | 0.004 |
| 5 | -38.5 | 36.5 | seat row | 0.50 | 7.28 | 1271.9 | 1268.1 | 1239.6 | 4402.3 | 0.005 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 8277; agent-steps of seated agents on another row's clearway: 1244832.

## Deposit check

Person-seconds deposited: 32396148.9, of them in excluded cells: 5578.274.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 6916520 overlapping pair-steps: p99 0.0021, max 0.0534 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0021 max 0.0534; venue-geometry 6: p99 0.0004 max 0.0004 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00765 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 52 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.62 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 3741 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
