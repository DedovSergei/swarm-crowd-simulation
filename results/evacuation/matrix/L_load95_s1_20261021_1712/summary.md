# Experiment `L_load95_s1`

**Task 5.9 stage 4: venue L, 95% load (seed 1), default model**

Venue L (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (4000 x 4000), cache key a2f3aaf59c2252b7, content hash 022d17b202313d70). 60253 agents on 95% of the 63424 seats (spawnSeatedCrowd, seed 1), buffer N = 65536, 8621 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 10864632 evaluations, 580720 switches, 0 forced choices).
Capacity: **within design capacity** (the L venue's design capacity 63424, jam capacity 171923: 23822.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-21T17:12:30, 1203.3 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 2902 | 507.6 |
| t90 | 5872 | 1027.1 |
| t100 | 8621 | 1507.9 |

t_p: the step by which ceil(p x 60253) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 2039 | 0 | 70.8 | 1132.5 | 20.4 | 26.6 | 336.9-346.8 |
| -x | 5.66 | 2044 | 0 | 70.8 | 1118.7 | 20.7 | 26.6 | 87.5-97.4 |
| +y | 5.66 | 2054 | 0 | 70.5 | 1122.9 | 20.7 | 26.6 | 182.4-192.4 |
| -y | 5.66 | 1976 | 0 | 70.8 | 1116.8 | 20.0 | 26.6 | 138.5-148.5 |
| door +x+y (y wall) 0 | 2.30 | 1427 | 2445 | 4.9 | 1232.6 | 30.3 | 44.5 | 9.6-19.6 |
| door +x+y (y wall) 1 | 2.30 | 1618 | 2029 | 4.9 | 1356.9 | 31.2 | 47.1 | 12.8-22.7 |
| door +x+y (y wall) 2 | 2.30 | 1516 | 1513 | 4.9 | 1437.0 | 27.6 | 47.1 | 24.1-34.1 |
| door +x+y (y wall) 3 | 2.30 | 1098 | 999 | 4.9 | 1502.4 | 19.1 | 47.1 | 14.9-24.8 |
| door +x+y (y wall) 4 | 2.30 | 624 | 485 | 4.9 | 1507.9 | 10.8 | 44.5 | 11.9-21.9 |
| door +x+y (x wall) 0 | 2.30 | 1449 | 2443 | 5.1 | 1124.7 | 33.8 | 47.1 | 15.9-25.9 |
| door +x+y (x wall) 1 | 2.30 | 1625 | 2019 | 4.9 | 1354.1 | 31.4 | 49.7 | 22.7-32.7 |
| door +x+y (x wall) 2 | 2.30 | 1511 | 1499 | 4.9 | 1506.8 | 26.2 | 44.5 | 30.3-40.2 |
| door +x+y (x wall) 3 | 2.30 | 1059 | 990 | 4.9 | 1503.8 | 18.4 | 49.7 | 25.7-35.7 |
| door +x+y (x wall) 4 | 2.30 | 616 | 487 | 5.1 | 1400.7 | 11.5 | 47.1 | 17.7-27.6 |
| door +x+y (corner) | 2.30 | 460 | 116 | 6.3 | 1062.7 | 11.4 | 47.1 | 95.8-105.8 |
| door -x+y (y wall) 0 | 2.30 | 1445 | 2445 | 4.9 | 1134.6 | 33.4 | 47.1 | 27.1-37.1 |
| door -x+y (y wall) 1 | 2.30 | 1583 | 2024 | 4.9 | 1348.9 | 30.7 | 47.1 | 10.7-20.6 |
| door -x+y (y wall) 2 | 2.30 | 1492 | 1511 | 4.9 | 1390.0 | 28.1 | 44.5 | 14.5-24.5 |
| door -x+y (y wall) 3 | 2.30 | 1205 | 1004 | 4.9 | 1371.8 | 23.0 | 47.1 | 22.2-32.2 |
| door -x+y (y wall) 4 | 2.30 | 583 | 494 | 5.1 | 1390.7 | 11.0 | 47.1 | 29.0-39.0 |
| door -x+y (x wall) 0 | 2.30 | 1447 | 2451 | 4.9 | 1093.0 | 34.7 | 44.5 | 9.6-19.6 |
| door -x+y (x wall) 1 | 2.30 | 1582 | 2036 | 4.9 | 1320.0 | 31.4 | 47.1 | 26.4-36.4 |
| door -x+y (x wall) 2 | 2.30 | 1490 | 1521 | 4.9 | 1388.6 | 28.1 | 47.1 | 26.1-36.0 |
| door -x+y (x wall) 3 | 2.30 | 1222 | 998 | 4.9 | 1394.2 | 22.9 | 44.5 | 15.2-25.2 |
| door -x+y (x wall) 4 | 2.30 | 570 | 482 | 4.9 | 1374.8 | 10.9 | 47.1 | 17.1-27.1 |
| door -x+y (corner) | 2.30 | 369 | 115 | 6.3 | 999.1 | 9.7 | 47.1 | 173.0-183.0 |
| door -x-y (y wall) 0 | 2.30 | 1450 | 2430 | 4.9 | 1226.8 | 31.0 | 44.5 | 4.4-14.3 |
| door -x-y (y wall) 1 | 2.30 | 1622 | 2027 | 4.9 | 1336.6 | 31.8 | 47.1 | 4.5-14.5 |
| door -x-y (y wall) 2 | 2.30 | 1527 | 1522 | 4.9 | 1423.4 | 28.1 | 49.7 | 15.7-25.7 |
| door -x-y (y wall) 3 | 2.30 | 1102 | 989 | 4.9 | 1422.7 | 20.3 | 44.5 | 21.5-31.5 |
| door -x-y (y wall) 4 | 2.30 | 615 | 490 | 4.9 | 1360.9 | 11.8 | 47.1 | 7.2-17.1 |
| door -x-y (x wall) 0 | 2.30 | 1443 | 2430 | 4.9 | 1090.5 | 34.7 | 44.5 | 8.7-18.7 |
| door -x-y (x wall) 1 | 2.30 | 1608 | 2025 | 4.9 | 1336.5 | 31.5 | 41.9 | 4.7-14.7 |
| door -x-y (x wall) 2 | 2.30 | 1507 | 1515 | 4.9 | 1423.9 | 27.7 | 44.5 | 9.4-19.4 |
| door -x-y (x wall) 3 | 2.30 | 1102 | 998 | 4.9 | 1427.8 | 20.2 | 47.1 | 15.4-25.4 |
| door -x-y (x wall) 4 | 2.30 | 658 | 493 | 5.1 | 1332.6 | 12.9 | 49.7 | 23.1-33.1 |
| door -x-y (corner) | 2.30 | 415 | 120 | 6.3 | 831.2 | 13.1 | 47.1 | 97.8-107.7 |
| door +x-y (y wall) 0 | 2.30 | 1449 | 2435 | 4.9 | 1096.0 | 34.6 | 44.5 | 9.8-19.8 |
| door +x-y (y wall) 1 | 2.30 | 1629 | 2029 | 4.9 | 1389.3 | 30.7 | 47.1 | 15.4-25.4 |
| door +x-y (y wall) 2 | 2.30 | 1484 | 1531 | 4.9 | 1394.7 | 27.9 | 44.5 | 12.6-22.6 |
| door +x-y (y wall) 3 | 2.30 | 1109 | 992 | 4.9 | 1404.9 | 20.7 | 44.5 | 15.6-25.5 |
| door +x-y (y wall) 4 | 2.30 | 637 | 479 | 5.1 | 1412.0 | 11.8 | 44.5 | 4.9-14.9 |
| door +x-y (x wall) 0 | 2.30 | 1465 | 2464 | 4.9 | 1138.1 | 33.7 | 47.1 | 26.1-36.0 |
| door +x-y (x wall) 1 | 2.30 | 1614 | 2061 | 4.9 | 1388.2 | 30.4 | 44.5 | 8.6-18.5 |
| door +x-y (x wall) 2 | 2.30 | 1486 | 1517 | 4.9 | 1394.5 | 27.9 | 47.1 | 9.6-19.6 |
| door +x-y (x wall) 3 | 2.30 | 1114 | 997 | 4.9 | 1377.7 | 21.2 | 44.5 | 8.6-18.5 |
| door +x-y (x wall) 4 | 2.30 | 689 | 482 | 5.1 | 1307.6 | 13.8 | 44.5 | 29.9-39.9 |
| door +x-y (corner) | 2.30 | 424 | 121 | 6.5 | 1006.8 | 11.1 | 47.1 | 156.9-166.9 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (2.30 m; a corner door's: the gap between its wall ends, 2.30 m); agents are removed past the outer wall's outer face (92.71 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 2039 | 3.4% | 17.1% |
| -x | avenue | 5.66 | 2044 | 3.4% | 17.2% |
| +y | avenue | 5.66 | 2054 | 3.4% | 17.3% |
| -y | avenue | 5.66 | 1976 | 3.3% | 16.6% |
| door +x+y (y wall) 0 | door | 2.30 | 1427 | 2.4% | 29.5% |
| door +x+y (y wall) 1 | door | 2.30 | 1618 | 2.7% | 33.5% |
| door +x+y (y wall) 2 | door | 2.30 | 1516 | 2.5% | 31.4% |
| door +x+y (y wall) 3 | door | 2.30 | 1098 | 1.8% | 22.7% |
| door +x+y (y wall) 4 | door | 2.30 | 624 | 1.0% | 12.9% |
| door +x+y (x wall) 0 | door | 2.30 | 1449 | 2.4% | 30.0% |
| door +x+y (x wall) 1 | door | 2.30 | 1625 | 2.7% | 33.6% |
| door +x+y (x wall) 2 | door | 2.30 | 1511 | 2.5% | 31.3% |
| door +x+y (x wall) 3 | door | 2.30 | 1059 | 1.8% | 21.9% |
| door +x+y (x wall) 4 | door | 2.30 | 616 | 1.0% | 12.7% |
| door +x+y (corner) | door | 2.30 | 460 | 0.8% | 9.5% |
| door -x+y (y wall) 0 | door | 2.30 | 1445 | 2.4% | 29.9% |
| door -x+y (y wall) 1 | door | 2.30 | 1583 | 2.6% | 32.8% |
| door -x+y (y wall) 2 | door | 2.30 | 1492 | 2.5% | 30.9% |
| door -x+y (y wall) 3 | door | 2.30 | 1205 | 2.0% | 24.9% |
| door -x+y (y wall) 4 | door | 2.30 | 583 | 1.0% | 12.1% |
| door -x+y (x wall) 0 | door | 2.30 | 1447 | 2.4% | 29.9% |
| door -x+y (x wall) 1 | door | 2.30 | 1582 | 2.6% | 32.7% |
| door -x+y (x wall) 2 | door | 2.30 | 1490 | 2.5% | 30.8% |
| door -x+y (x wall) 3 | door | 2.30 | 1222 | 2.0% | 25.3% |
| door -x+y (x wall) 4 | door | 2.30 | 570 | 0.9% | 11.8% |
| door -x+y (corner) | door | 2.30 | 369 | 0.6% | 7.6% |
| door -x-y (y wall) 0 | door | 2.30 | 1450 | 2.4% | 30.0% |
| door -x-y (y wall) 1 | door | 2.30 | 1622 | 2.7% | 33.6% |
| door -x-y (y wall) 2 | door | 2.30 | 1527 | 2.5% | 31.6% |
| door -x-y (y wall) 3 | door | 2.30 | 1102 | 1.8% | 22.8% |
| door -x-y (y wall) 4 | door | 2.30 | 615 | 1.0% | 12.7% |
| door -x-y (x wall) 0 | door | 2.30 | 1443 | 2.4% | 29.9% |
| door -x-y (x wall) 1 | door | 2.30 | 1608 | 2.7% | 33.3% |
| door -x-y (x wall) 2 | door | 2.30 | 1507 | 2.5% | 31.2% |
| door -x-y (x wall) 3 | door | 2.30 | 1102 | 1.8% | 22.8% |
| door -x-y (x wall) 4 | door | 2.30 | 658 | 1.1% | 13.6% |
| door -x-y (corner) | door | 2.30 | 415 | 0.7% | 8.6% |
| door +x-y (y wall) 0 | door | 2.30 | 1449 | 2.4% | 30.0% |
| door +x-y (y wall) 1 | door | 2.30 | 1629 | 2.7% | 33.7% |
| door +x-y (y wall) 2 | door | 2.30 | 1484 | 2.5% | 30.7% |
| door +x-y (y wall) 3 | door | 2.30 | 1109 | 1.8% | 23.0% |
| door +x-y (y wall) 4 | door | 2.30 | 637 | 1.1% | 13.2% |
| door +x-y (x wall) 0 | door | 2.30 | 1465 | 2.4% | 30.3% |
| door +x-y (x wall) 1 | door | 2.30 | 1614 | 2.7% | 33.4% |
| door +x-y (x wall) 2 | door | 2.30 | 1486 | 2.5% | 30.8% |
| door +x-y (x wall) 3 | door | 2.30 | 1114 | 1.8% | 23.1% |
| door +x-y (x wall) 4 | door | 2.30 | 689 | 1.1% | 14.3% |
| door +x-y (corner) | door | 2.30 | 424 | 0.7% | 8.8% |
| **doors (44)** | door | 101.20 | 52140 | 86.5% | |
| **avenues (4)** | avenue | 22.64 | 8113 | 13.5% | |

**Unused exit width: 0.0 of 123.8 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 1507.9 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 23.2%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 2197 | 3.6% | 2197 | 3.6% |
| straight +x+y (y wing) 1 | straight | yes | 1801 | 3.0% | 1621 | 2.7% |
| straight +x+y (y wing) 2 | straight | yes | 1550 | 2.6% | 1537 | 2.6% |
| straight +x+y (y wing) 3 | straight | yes | 1102 | 1.8% | 1096 | 1.8% |
| straight +x+y (y wing) 4 | straight | yes | 618 | 1.0% | 605 | 1.0% |
| straight +x+y (x wing) 0 | straight | yes | 2203 | 3.7% | 2203 | 3.7% |
| straight +x+y (x wing) 1 | straight | yes | 1810 | 3.0% | 1626 | 2.7% |
| straight +x+y (x wing) 2 | straight | yes | 1527 | 2.5% | 1521 | 2.5% |
| straight +x+y (x wing) 3 | straight | yes | 1067 | 1.8% | 1063 | 1.8% |
| straight +x+y (x wing) 4 | straight | yes | 627 | 1.0% | 602 | 1.0% |
| corner +x+y | corner | yes | 2166 | 3.6% | 954 | 1.6% |
| straight -x+y (y wing) 0 | straight | yes | 2210 | 3.7% | 2210 | 3.7% |
| straight -x+y (y wing) 1 | straight | yes | 1804 | 3.0% | 1586 | 2.6% |
| straight -x+y (y wing) 2 | straight | yes | 1522 | 2.5% | 1509 | 2.5% |
| straight -x+y (y wing) 3 | straight | yes | 1204 | 2.0% | 1203 | 2.0% |
| straight -x+y (y wing) 4 | straight | yes | 582 | 1.0% | 568 | 0.9% |
| straight -x+y (x wing) 0 | straight | yes | 2224 | 3.7% | 2224 | 3.7% |
| straight -x+y (x wing) 1 | straight | yes | 1787 | 3.0% | 1582 | 2.6% |
| straight -x+y (x wing) 2 | straight | yes | 1535 | 2.5% | 1511 | 2.5% |
| straight -x+y (x wing) 3 | straight | yes | 1205 | 2.0% | 1202 | 2.0% |
| straight -x+y (x wing) 4 | straight | yes | 596 | 1.0% | 569 | 0.9% |
| corner -x+y | corner | yes | 2222 | 3.7% | 917 | 1.5% |
| straight -x-y (y wing) 0 | straight | yes | 2208 | 3.7% | 2208 | 3.7% |
| straight -x-y (y wing) 1 | straight | yes | 1797 | 3.0% | 1623 | 2.7% |
| straight -x-y (y wing) 2 | straight | yes | 1556 | 2.6% | 1544 | 2.6% |
| straight -x-y (y wing) 3 | straight | yes | 1093 | 1.8% | 1090 | 1.8% |
| straight -x-y (y wing) 4 | straight | yes | 621 | 1.0% | 610 | 1.0% |
| straight -x-y (x wing) 0 | straight | yes | 2198 | 3.6% | 2198 | 3.6% |
| straight -x-y (x wing) 1 | straight | yes | 1777 | 2.9% | 1608 | 2.7% |
| straight -x-y (x wing) 2 | straight | yes | 1531 | 2.5% | 1517 | 2.5% |
| straight -x-y (x wing) 3 | straight | yes | 1110 | 1.8% | 1106 | 1.8% |
| straight -x-y (x wing) 4 | straight | yes | 665 | 1.1% | 644 | 1.1% |
| corner -x-y | corner | yes | 2151 | 3.6% | 891 | 1.5% |
| straight +x-y (y wing) 0 | straight | yes | 2218 | 3.7% | 2218 | 3.7% |
| straight +x-y (y wing) 1 | straight | yes | 1791 | 3.0% | 1629 | 2.7% |
| straight +x-y (y wing) 2 | straight | yes | 1524 | 2.5% | 1509 | 2.5% |
| straight +x-y (y wing) 3 | straight | yes | 1096 | 1.8% | 1091 | 1.8% |
| straight +x-y (y wing) 4 | straight | yes | 639 | 1.1% | 630 | 1.0% |
| straight +x-y (x wing) 0 | straight | yes | 2247 | 3.7% | 2247 | 3.7% |
| straight +x-y (x wing) 1 | straight | yes | 1792 | 3.0% | 1614 | 2.7% |
| straight +x-y (x wing) 2 | straight | yes | 1535 | 2.5% | 1517 | 2.5% |
| straight +x-y (x wing) 3 | straight | yes | 1113 | 1.8% | 1104 | 1.8% |
| straight +x-y (x wing) 4 | straight | yes | 690 | 1.1% | 668 | 1.1% |
| corner +x-y | corner | yes | 2188 | 3.6% | 881 | 1.5% |
| **straight (40)** | | | 58372 | | 56610 | 94.0% |
| **corner (4)** | | | 8727 | | 3643 | 6.0% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 2039 | 70.8 | 1132.5 | 0.24 | 0.32 | 0.0% |
| -x | 2044 | 70.8 | 1118.7 | 0.25 | 0.32 | 0.0% |
| +y | 2054 | 70.5 | 1122.9 | 0.25 | 0.32 | 0.0% |
| -y | 1976 | 70.8 | 1116.8 | 0.24 | 0.32 | 0.0% |
| door +x+y (y wall) 0 | 1427 | 4.9 | 1232.6 | 0.36 | 0.53 | 0.0% |
| door +x+y (y wall) 1 | 1618 | 4.9 | 1356.9 | 0.37 | 0.56 | 0.0% |
| door +x+y (y wall) 2 | 1516 | 4.9 | 1437.0 | 0.33 | 0.56 | 0.0% |
| door +x+y (y wall) 3 | 1098 | 4.9 | 1502.4 | 0.23 | 0.56 | 0.0% |
| door +x+y (y wall) 4 | 624 | 4.9 | 1507.9 | 0.13 | 0.53 | 0.0% |
| door +x+y (x wall) 0 | 1449 | 5.1 | 1124.7 | 0.40 | 0.56 | 0.0% |
| door +x+y (x wall) 1 | 1625 | 4.9 | 1354.1 | 0.38 | 0.59 | 0.0% |
| door +x+y (x wall) 2 | 1511 | 4.9 | 1506.8 | 0.31 | 0.53 | 0.0% |
| door +x+y (x wall) 3 | 1059 | 4.9 | 1503.8 | 0.22 | 0.59 | 0.0% |
| door +x+y (x wall) 4 | 616 | 5.1 | 1400.7 | 0.14 | 0.56 | 0.0% |
| door +x+y (corner) | 460 | 6.3 | 1062.7 | 0.14 | 0.56 | 0.0% |
| door -x+y (y wall) 0 | 1445 | 4.9 | 1134.6 | 0.40 | 0.56 | 0.0% |
| door -x+y (y wall) 1 | 1583 | 4.9 | 1348.9 | 0.37 | 0.56 | 0.0% |
| door -x+y (y wall) 2 | 1492 | 4.9 | 1390.0 | 0.34 | 0.53 | 0.0% |
| door -x+y (y wall) 3 | 1205 | 4.9 | 1371.8 | 0.28 | 0.56 | 0.0% |
| door -x+y (y wall) 4 | 583 | 5.1 | 1390.7 | 0.13 | 0.56 | 0.0% |
| door -x+y (x wall) 0 | 1447 | 4.9 | 1093.0 | 0.41 | 0.53 | 0.0% |
| door -x+y (x wall) 1 | 1582 | 4.9 | 1320.0 | 0.38 | 0.56 | 0.0% |
| door -x+y (x wall) 2 | 1490 | 4.9 | 1388.6 | 0.34 | 0.56 | 0.0% |
| door -x+y (x wall) 3 | 1222 | 4.9 | 1394.2 | 0.27 | 0.53 | 0.0% |
| door -x+y (x wall) 4 | 570 | 4.9 | 1374.8 | 0.13 | 0.56 | 0.0% |
| door -x+y (corner) | 369 | 6.3 | 999.1 | 0.12 | 0.56 | 0.0% |
| door -x-y (y wall) 0 | 1450 | 4.9 | 1226.8 | 0.37 | 0.53 | 0.0% |
| door -x-y (y wall) 1 | 1622 | 4.9 | 1336.6 | 0.38 | 0.56 | 0.0% |
| door -x-y (y wall) 2 | 1527 | 4.9 | 1423.4 | 0.34 | 0.59 | 0.0% |
| door -x-y (y wall) 3 | 1102 | 4.9 | 1422.7 | 0.24 | 0.53 | 0.0% |
| door -x-y (y wall) 4 | 615 | 4.9 | 1360.9 | 0.14 | 0.56 | 0.0% |
| door -x-y (x wall) 0 | 1443 | 4.9 | 1090.5 | 0.41 | 0.53 | 0.0% |
| door -x-y (x wall) 1 | 1608 | 4.9 | 1336.5 | 0.38 | 0.50 | 0.0% |
| door -x-y (x wall) 2 | 1507 | 4.9 | 1423.9 | 0.33 | 0.53 | 0.0% |
| door -x-y (x wall) 3 | 1102 | 4.9 | 1427.8 | 0.24 | 0.56 | 0.0% |
| door -x-y (x wall) 4 | 658 | 5.1 | 1332.6 | 0.15 | 0.59 | 0.0% |
| door -x-y (corner) | 415 | 6.3 | 831.2 | 0.16 | 0.56 | 0.0% |
| door +x-y (y wall) 0 | 1449 | 4.9 | 1096.0 | 0.41 | 0.53 | 0.0% |
| door +x-y (y wall) 1 | 1629 | 4.9 | 1389.3 | 0.37 | 0.56 | 0.0% |
| door +x-y (y wall) 2 | 1484 | 4.9 | 1394.7 | 0.33 | 0.53 | 0.0% |
| door +x-y (y wall) 3 | 1109 | 4.9 | 1404.9 | 0.25 | 0.53 | 0.0% |
| door +x-y (y wall) 4 | 637 | 5.1 | 1412.0 | 0.14 | 0.53 | 0.0% |
| door +x-y (x wall) 0 | 1465 | 4.9 | 1138.1 | 0.40 | 0.56 | 0.0% |
| door +x-y (x wall) 1 | 1614 | 4.9 | 1388.2 | 0.36 | 0.53 | 0.0% |
| door +x-y (x wall) 2 | 1486 | 4.9 | 1394.5 | 0.33 | 0.56 | 0.0% |
| door +x-y (x wall) 3 | 1114 | 4.9 | 1377.7 | 0.25 | 0.53 | 0.0% |
| door +x-y (x wall) 4 | 689 | 5.1 | 1307.6 | 0.17 | 0.53 | 0.0% |
| door +x-y (corner) | 424 | 6.5 | 1006.8 | 0.13 | 0.56 | 0.0% |

Mean flow / w J averaged over the doors 0.28, over the avenues 0.24.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 103.1 | 2197 | 1424 / 773 / 1017 | 0.7 | 1085.6 | 2.96 | 5.32 | 92% | 87% | 5% | 4.44 |
| straight +x+y (y wing) 1 | 1.20 | 81.5 | 1783 | 1621 / 0 / 272 | 0.7 | 1354.0 | 1.40 | 2.81 | 93% | 67% | 26% | 3.39 |
| straight +x+y (y wing) 2 | 1.20 | 61.0 | 1449 | 1537 / 0 / 17 | 0.7 | 1434.1 | 1.08 | 1.71 | 76% | 65% | 11% | 3.74 |
| straight +x+y (y wing) 3 | 1.20 | 39.4 | 883 | 1096 / 0 / 9 | 0.7 | 1499.5 | 0.74 | 1.81 | 45% | 37% | 8% | 3.64 |
| straight +x+y (y wing) 4 | 1.20 | 18.8 | 360 | 605 / 0 / 20 | 0.7 | 1504.9 | 0.42 | 1.81 | 16% | 13% | 3% | 3.70 |
| straight +x+y (x wing) 0 | 1.20 | 103.1 | 2203 | 1448 / 755 / 1056 | 0.7 | 1093.0 | 2.98 | 4.91 | 91% | 87% | 4% | 4.33 |
| straight +x+y (x wing) 1 | 1.20 | 81.5 | 1793 | 1626 / 0 / 271 | 0.7 | 1351.2 | 1.40 | 3.11 | 93% | 68% | 25% | 3.34 |
| straight +x+y (x wing) 2 | 1.20 | 61.0 | 1419 | 1521 / 0 / 11 | 0.7 | 1503.8 | 1.02 | 1.71 | 72% | 62% | 9% | 3.70 |
| straight +x+y (x wing) 3 | 1.20 | 39.4 | 871 | 1063 / 0 / 9 | 0.7 | 1500.9 | 0.71 | 2.01 | 45% | 34% | 11% | 3.42 |
| straight +x+y (x wing) 4 | 1.20 | 18.8 | 373 | 602 / 0 / 25 | 0.7 | 1397.7 | 0.45 | 1.71 | 17% | 16% | 1% | 3.79 |
| corner +x+y | 1.20 | 186.0 | 1694 | 460 / 494 / 1259 | 0.7 | 1481.1 | 1.49 | 3.81 | 88% | 59% | 29% | 2.51 |
| straight -x+y (y wing) 0 | 1.20 | 103.1 | 2210 | 1442 / 770 / 1095 | 0.7 | 1086.5 | 3.05 | 4.81 | 91% | 88% | 3% | 4.25 |
| straight -x+y (y wing) 1 | 1.20 | 81.5 | 1783 | 1586 / 0 / 311 | 0.7 | 1345.9 | 1.41 | 2.61 | 91% | 61% | 30% | 3.20 |
| straight -x+y (y wing) 2 | 1.20 | 61.0 | 1440 | 1509 / 0 / 15 | 0.7 | 1387.0 | 1.10 | 1.60 | 79% | 66% | 12% | 3.66 |
| straight -x+y (y wing) 3 | 1.20 | 39.4 | 891 | 1203 / 0 / 3 | 0.7 | 1368.8 | 0.88 | 1.60 | 48% | 40% | 8% | 3.74 |
| straight -x+y (y wing) 4 | 1.20 | 18.8 | 357 | 568 / 0 / 25 | 0.7 | 1387.7 | 0.43 | 1.81 | 19% | 16% | 3% | 3.57 |
| straight -x+y (x wing) 0 | 1.20 | 103.1 | 2224 | 1447 / 778 / 933 | 0.7 | 1090.0 | 2.90 | 5.12 | 90% | 87% | 3% | 4.38 |
| straight -x+y (x wing) 1 | 1.20 | 81.5 | 1774 | 1582 / 0 / 291 | 0.7 | 1317.0 | 1.42 | 3.21 | 92% | 62% | 30% | 3.23 |
| straight -x+y (x wing) 2 | 1.20 | 61.0 | 1451 | 1511 / 0 / 27 | 0.7 | 1385.6 | 1.11 | 1.60 | 79% | 68% | 12% | 3.73 |
| straight -x+y (x wing) 3 | 1.20 | 39.4 | 876 | 1202 / 0 / 5 | 0.7 | 1391.2 | 0.87 | 1.71 | 46% | 39% | 8% | 3.86 |
| straight -x+y (x wing) 4 | 1.20 | 18.8 | 386 | 569 / 0 / 27 | 0.7 | 1371.8 | 0.43 | 2.01 | 17% | 17% | 0% | 3.80 |
| corner -x+y | 1.20 | 186.0 | 1689 | 369 / 548 / 1368 | 0.7 | 1363.7 | 1.68 | 3.51 | 92% | 66% | 26% | 2.72 |
| straight -x-y (y wing) 0 | 1.20 | 103.1 | 2208 | 1449 / 759 / 935 | 0.7 | 1089.3 | 2.89 | 5.02 | 90% | 86% | 4% | 4.46 |
| straight -x-y (y wing) 1 | 1.20 | 81.5 | 1781 | 1623 / 0 / 263 | 0.7 | 1333.7 | 1.41 | 2.91 | 93% | 66% | 26% | 3.32 |
| straight -x-y (y wing) 2 | 1.20 | 61.0 | 1442 | 1544 / 0 / 16 | 0.7 | 1420.6 | 1.10 | 2.11 | 76% | 65% | 10% | 3.82 |
| straight -x-y (y wing) 3 | 1.20 | 39.4 | 867 | 1090 / 0 / 7 | 0.7 | 1419.7 | 0.77 | 1.60 | 45% | 36% | 9% | 3.75 |
| straight -x-y (y wing) 4 | 1.20 | 18.8 | 365 | 610 / 0 / 95 | 0.7 | 1358.0 | 0.52 | 1.71 | 18% | 16% | 1% | 3.83 |
| straight -x-y (x wing) 0 | 1.20 | 103.1 | 2198 | 1443 / 755 / 900 | 0.7 | 1087.6 | 2.85 | 5.42 | 91% | 86% | 5% | 4.27 |
| straight -x-y (x wing) 1 | 1.20 | 81.5 | 1762 | 1608 / 0 / 297 | 0.7 | 1333.5 | 1.43 | 3.01 | 92% | 68% | 24% | 3.40 |
| straight -x-y (x wing) 2 | 1.20 | 61.0 | 1445 | 1517 / 0 / 18 | 0.7 | 1420.9 | 1.08 | 1.81 | 76% | 65% | 10% | 3.64 |
| straight -x-y (x wing) 3 | 1.20 | 39.4 | 881 | 1106 / 0 / 8 | 0.7 | 1424.8 | 0.78 | 1.71 | 49% | 36% | 13% | 3.37 |
| straight -x-y (x wing) 4 | 1.20 | 18.8 | 393 | 644 / 0 / 22 | 0.7 | 1329.6 | 0.50 | 1.91 | 19% | 18% | 1% | 3.68 |
| corner -x-y | 1.20 | 186.0 | 1697 | 415 / 476 / 1432 | 0.7 | 1374.6 | 1.69 | 3.81 | 93% | 59% | 33% | 2.59 |
| straight +x-y (y wing) 0 | 1.20 | 103.1 | 2218 | 1449 / 770 / 994 | 0.7 | 1093.0 | 2.94 | 5.22 | 91% | 87% | 4% | 4.26 |
| straight +x-y (y wing) 1 | 1.20 | 81.5 | 1764 | 1629 / 0 / 260 | 0.7 | 1386.3 | 1.36 | 2.51 | 89% | 66% | 23% | 3.46 |
| straight +x-y (y wing) 2 | 1.20 | 61.0 | 1451 | 1509 / 0 / 26 | 0.7 | 1391.7 | 1.10 | 1.81 | 81% | 69% | 12% | 3.65 |
| straight +x-y (y wing) 3 | 1.20 | 39.4 | 872 | 1091 / 0 / 8 | 0.7 | 1401.9 | 0.78 | 1.71 | 49% | 38% | 11% | 3.39 |
| straight +x-y (y wing) 4 | 1.20 | 18.8 | 352 | 630 / 0 / 12 | 0.7 | 1409.0 | 0.46 | 1.71 | 20% | 15% | 5% | 3.22 |
| straight +x-y (x wing) 0 | 1.20 | 103.1 | 2247 | 1465 / 782 / 966 | 0.7 | 1135.1 | 2.83 | 5.02 | 92% | 85% | 7% | 4.18 |
| straight +x-y (x wing) 1 | 1.20 | 81.5 | 1781 | 1614 / 0 / 225 | 0.7 | 1385.3 | 1.33 | 3.01 | 90% | 68% | 22% | 3.44 |
| straight +x-y (x wing) 2 | 1.20 | 61.0 | 1437 | 1517 / 0 / 24 | 0.7 | 1391.6 | 1.11 | 1.91 | 77% | 66% | 11% | 3.70 |
| straight +x-y (x wing) 3 | 1.20 | 39.4 | 878 | 1104 / 0 / 14 | 0.7 | 1374.8 | 0.81 | 1.60 | 49% | 41% | 8% | 3.53 |
| straight +x-y (x wing) 4 | 1.20 | 18.8 | 367 | 668 / 0 / 25 | 0.7 | 1304.6 | 0.53 | 1.91 | 19% | 16% | 3% | 3.70 |
| corner +x-y | 1.20 | 186.0 | 1741 | 424 / 457 / 1391 | 0.7 | 1385.1 | 1.64 | 3.61 | 91% | 59% | 32% | 2.59 |

The last agent out (agent 892, t100 1507.9 s): last gangway straight +x+y (y wing) 4, exit door +x+y (y wall) 4. The gangway that cleared last: straight +x+y (y wing) 4 at 1504.9 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 8804 | 7800.4 | 7.02 | 1503.1 / 1418.0 / 1316.5 | 1413.4 / 1402.1 / 1290.3 | 6538090.8 | 12576956 | 0.171 |
| gangway | 3792 | 3512.9 | 7.02 | 1501.7 / 1418.0 / 1316.5 | 1413.4 / 1402.1 / 1290.3 | 6538090.8 | 11823383 | 0.105 |
| walkway | 276 | 257.4 | 3.27 | 792.7 / 399.1 / 0.0 | 397.0 / 81.0 / 0.0 | 0.0 | 70240 | 0.830 |
| avenue | 1920 | 1801.4 | 1.96 | 808.9 / 0.0 / 0.0 | 573.2 / 0.0 / 0.0 | 0.0 | 486260 | 1.334 |
| exit | 4 | 2.0 | 0.00 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 0 | - |
| concourse | 2812 | 2226.8 | 2.61 | 1363.9 / 27.8 / 0.0 | 998.2 / 3.8 / 0.0 | 0.0 | 197073 | 1.040 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 25392 | 16030.4 | 7.80 | 1305.2 / 1300.8 / 1276.1 | 1305.2 / 1300.8 / 1272.3 | 7859969.9 | 19806726 | 0.023 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 208 x 208 from (-104, -104) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 35.5 | 35.5 | gangway | 1.00 | 5.84 | 1348.4 | 1344.3 | 1281.0 | 7219.8 | 0.007 |
| 2 | -34.5 | -34.5 | gangway | 1.00 | 5.79 | 1307.6 | 1297.1 | 1247.4 | 7010.2 | 0.007 |
| 3 | -33.5 | -33.5 | gangway | 0.99 | 5.73 | 1294.0 | 1285.7 | 1250.2 | 6957.7 | 0.004 |
| 4 | 34.5 | -34.5 | gangway | 1.00 | 5.89 | 1288.9 | 1277.9 | 1244.5 | 6951.8 | 0.006 |
| 5 | 38.5 | 38.5 | gangway | 1.00 | 5.81 | 1358.9 | 1332.8 | 1210.2 | 6913.6 | 0.011 |
| 6 | 36.5 | -36.5 | gangway | 1.00 | 5.85 | 1296.6 | 1292.0 | 1214.4 | 6745.0 | 0.009 |
| 7 | -35.5 | -35.5 | gangway | 1.00 | 5.46 | 1311.6 | 1308.5 | 1243.1 | 6699.7 | 0.008 |
| 8 | 37.5 | 37.5 | gangway | 0.99 | 5.59 | 1356.2 | 1345.7 | 1223.3 | 6665.6 | 0.008 |
| 9 | 36.5 | 36.5 | gangway | 1.00 | 5.53 | 1353.6 | 1350.3 | 1235.9 | 6605.3 | 0.007 |
| 10 | 33.5 | -33.5 | gangway | 0.99 | 5.65 | 1278.6 | 1268.6 | 1197.8 | 6481.1 | 0.004 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 38.5 | 36.5 | seat row | 0.50 | 7.20 | 1305.2 | 1300.8 | 1272.3 | 4496.7 | 0.003 |
| 2 | 36.5 | 38.5 | seat row | 0.50 | 7.22 | 1304.3 | 1296.4 | 1265.6 | 4394.9 | 0.003 |
| 3 | -38.5 | -36.5 | seat row | 0.50 | 7.30 | 1276.1 | 1273.7 | 1244.1 | 4377.9 | 0.005 |
| 4 | 42.5 | -25.5 | seat row | 0.64 | 6.89 | 1074.3 | 1071.3 | 1048.2 | 4356.0 | 0.008 |
| 5 | -36.5 | -38.5 | seat row | 0.50 | 7.32 | 1245.2 | 1239.7 | 1213.9 | 4330.7 | 0.003 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 8514; agent-steps of seated agents on another row's clearway: 1405331.

## Deposit check

Person-seconds deposited: 32389262.6, of them in excluded cells: 5580.140.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 7167339 overlapping pair-steps: p99 0.0021, max 0.0773 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0021 max 0.0773; venue-geometry 9: p99 0.0011 max 0.0011 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00751 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 64 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.62 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 3750 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
