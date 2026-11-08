# Experiment `L_load100`

**Task 5.9 stage 4: venue L, 100% load, default model**

Venue L (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (4000 x 4000), cache key a2f3aaf59c2252b7, content hash 022d17b202313d70). 63424 agents on 100% of the 63424 seats (spawnSeatedCrowd, seed 1337), buffer N = 65536, 8447 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 12030277 evaluations, 636799 switches, 0 forced choices).
Capacity: **within design capacity** (the L venue's design capacity 63424, jam capacity 171923: 23822.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-21T20:56:21, 807.7 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 3044 | 532.4 |
| t90 | 6189 | 1082.5 |
| t100 | 8447 | 1477.4 |

t_p: the step by which ceil(p x 63424) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 2163 | 0 | 70.8 | 1172.4 | 20.8 | 25.5 | 78.9-88.9 |
| -x | 5.66 | 2179 | 0 | 70.5 | 1176.2 | 20.9 | 25.5 | 80.5-90.4 |
| +y | 5.66 | 2126 | 0 | 70.5 | 1179.7 | 20.3 | 26.6 | 82.9-92.9 |
| -y | 5.66 | 2168 | 0 | 70.5 | 1178.3 | 20.7 | 26.6 | 82.9-92.9 |
| door +x+y (y wall) 0 | 2.30 | 1527 | 2577 | 4.9 | 1261.6 | 31.7 | 47.1 | 27.6-37.6 |
| door +x+y (y wall) 1 | 2.30 | 1678 | 2137 | 4.9 | 1418.3 | 31.0 | 44.5 | 22.6-32.5 |
| door +x+y (y wall) 2 | 2.30 | 1576 | 1594 | 4.9 | 1463.6 | 28.2 | 41.9 | 5.9-15.9 |
| door +x+y (y wall) 3 | 2.30 | 1207 | 1045 | 4.9 | 1467.5 | 21.5 | 47.1 | 16.3-26.2 |
| door +x+y (y wall) 4 | 2.30 | 660 | 513 | 4.9 | 1369.7 | 12.6 | 49.7 | 24.1-34.1 |
| door +x+y (x wall) 0 | 2.30 | 1525 | 2577 | 4.9 | 1158.2 | 34.5 | 47.1 | 12.6-22.6 |
| door +x+y (x wall) 1 | 2.30 | 1678 | 2137 | 4.9 | 1380.4 | 31.8 | 47.1 | 12.6-22.6 |
| door +x+y (x wall) 2 | 2.30 | 1596 | 1594 | 4.9 | 1450.2 | 28.8 | 47.1 | 25.7-35.7 |
| door +x+y (x wall) 3 | 2.30 | 1199 | 1045 | 4.9 | 1412.7 | 22.2 | 47.1 | 12.6-22.6 |
| door +x+y (x wall) 4 | 2.30 | 601 | 513 | 5.1 | 1432.3 | 11.0 | 44.5 | 16.3-26.2 |
| door +x+y (corner) | 2.30 | 457 | 124 | 6.3 | 1108.9 | 10.8 | 47.1 | 67.3-77.3 |
| door -x+y (y wall) 0 | 2.30 | 1530 | 2577 | 4.9 | 1155.3 | 34.7 | 47.1 | 27.1-37.1 |
| door -x+y (y wall) 1 | 2.30 | 1716 | 2137 | 4.9 | 1428.8 | 31.4 | 47.1 | 27.1-37.1 |
| door -x+y (y wall) 2 | 2.30 | 1614 | 1594 | 4.9 | 1469.7 | 28.7 | 44.5 | 11.4-21.3 |
| door -x+y (y wall) 3 | 2.30 | 1126 | 1045 | 4.9 | 1474.3 | 20.0 | 47.1 | 21.0-31.0 |
| door -x+y (y wall) 4 | 2.30 | 683 | 513 | 5.1 | 1410.4 | 12.7 | 44.5 | 13.3-23.3 |
| door -x+y (x wall) 0 | 2.30 | 1521 | 2577 | 4.9 | 1147.7 | 34.7 | 44.5 | 28.2-38.1 |
| door -x+y (x wall) 1 | 2.30 | 1718 | 2137 | 4.9 | 1430.7 | 31.4 | 44.5 | 31.0-40.9 |
| door -x+y (x wall) 2 | 2.30 | 1608 | 1594 | 4.9 | 1467.6 | 28.7 | 44.5 | 29.4-39.4 |
| door -x+y (x wall) 3 | 2.30 | 1094 | 1045 | 4.9 | 1477.4 | 19.4 | 44.5 | 27.6-37.6 |
| door -x+y (x wall) 4 | 2.30 | 668 | 513 | 4.9 | 1469.6 | 11.9 | 47.1 | 8.7-18.7 |
| door -x+y (corner) | 2.30 | 456 | 124 | 6.3 | 864.2 | 13.9 | 44.5 | 69.8-79.8 |
| door -x-y (y wall) 0 | 2.30 | 1529 | 2577 | 4.9 | 1261.8 | 31.7 | 44.5 | 31.1-41.1 |
| door -x-y (y wall) 1 | 2.30 | 1694 | 2137 | 4.9 | 1424.4 | 31.1 | 44.5 | 27.1-37.1 |
| door -x-y (y wall) 2 | 2.30 | 1631 | 1594 | 4.9 | 1462.4 | 29.2 | 44.5 | 27.1-37.1 |
| door -x-y (y wall) 3 | 2.30 | 1134 | 1045 | 4.9 | 1453.3 | 20.4 | 44.5 | 27.1-37.1 |
| door -x-y (y wall) 4 | 2.30 | 672 | 513 | 4.9 | 1407.8 | 12.5 | 47.1 | 14.3-24.3 |
| door -x-y (x wall) 0 | 2.30 | 1528 | 2577 | 4.9 | 1252.2 | 32.0 | 47.1 | 27.3-37.3 |
| door -x-y (x wall) 1 | 2.30 | 1686 | 2137 | 4.9 | 1395.4 | 31.6 | 47.1 | 26.9-36.9 |
| door -x-y (x wall) 2 | 2.30 | 1628 | 1594 | 4.9 | 1460.8 | 29.2 | 47.1 | 26.1-36.0 |
| door -x-y (x wall) 3 | 2.30 | 1156 | 1045 | 4.9 | 1412.0 | 21.4 | 47.1 | 26.8-36.7 |
| door -x-y (x wall) 4 | 2.30 | 644 | 513 | 5.1 | 1422.2 | 11.9 | 44.5 | 13.3-23.3 |
| door -x-y (corner) | 2.30 | 370 | 124 | 6.3 | 1065.5 | 9.1 | 47.1 | 67.5-77.5 |
| door +x-y (y wall) 0 | 2.30 | 1534 | 2577 | 4.9 | 1256.4 | 32.0 | 44.5 | 30.6-40.6 |
| door +x-y (y wall) 1 | 2.30 | 1672 | 2137 | 4.9 | 1423.6 | 30.7 | 44.5 | 26.8-36.7 |
| door +x-y (y wall) 2 | 2.30 | 1565 | 1594 | 4.9 | 1466.9 | 27.9 | 47.1 | 22.7-32.7 |
| door +x-y (y wall) 3 | 2.30 | 1224 | 1045 | 4.9 | 1460.5 | 21.9 | 44.5 | 11.4-21.3 |
| door +x-y (y wall) 4 | 2.30 | 718 | 513 | 5.1 | 1459.6 | 12.9 | 44.5 | 13.3-23.3 |
| door +x-y (x wall) 0 | 2.30 | 1515 | 2577 | 4.9 | 1298.7 | 30.5 | 44.5 | 8.6-18.5 |
| door +x-y (x wall) 1 | 2.30 | 1688 | 2137 | 4.9 | 1427.4 | 31.0 | 47.1 | 22.6-32.5 |
| door +x-y (x wall) 2 | 2.30 | 1580 | 1594 | 4.9 | 1466.4 | 28.2 | 47.1 | 12.6-22.6 |
| door +x-y (x wall) 3 | 2.30 | 1180 | 1045 | 4.9 | 1419.7 | 21.8 | 47.1 | 12.6-22.6 |
| door +x-y (x wall) 4 | 2.30 | 604 | 513 | 5.1 | 1466.9 | 10.8 | 47.1 | 20.5-30.4 |
| door +x-y (corner) | 2.30 | 398 | 124 | 6.5 | 1100.0 | 9.5 | 47.1 | 76.4-86.4 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (2.30 m; a corner door's: the gap between its wall ends, 2.30 m); agents are removed past the outer wall's outer face (92.71 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 2163 | 3.4% | 18.6% |
| -x | avenue | 5.66 | 2179 | 3.4% | 18.7% |
| +y | avenue | 5.66 | 2126 | 3.4% | 18.2% |
| -y | avenue | 5.66 | 2168 | 3.4% | 18.6% |
| door +x+y (y wall) 0 | door | 2.30 | 1527 | 2.4% | 32.3% |
| door +x+y (y wall) 1 | door | 2.30 | 1678 | 2.6% | 35.4% |
| door +x+y (y wall) 2 | door | 2.30 | 1576 | 2.5% | 33.3% |
| door +x+y (y wall) 3 | door | 2.30 | 1207 | 1.9% | 25.5% |
| door +x+y (y wall) 4 | door | 2.30 | 660 | 1.0% | 13.9% |
| door +x+y (x wall) 0 | door | 2.30 | 1525 | 2.4% | 32.2% |
| door +x+y (x wall) 1 | door | 2.30 | 1678 | 2.6% | 35.4% |
| door +x+y (x wall) 2 | door | 2.30 | 1596 | 2.5% | 33.7% |
| door +x+y (x wall) 3 | door | 2.30 | 1199 | 1.9% | 25.3% |
| door +x+y (x wall) 4 | door | 2.30 | 601 | 0.9% | 12.7% |
| door +x+y (corner) | door | 2.30 | 457 | 0.7% | 9.7% |
| door -x+y (y wall) 0 | door | 2.30 | 1530 | 2.4% | 32.3% |
| door -x+y (y wall) 1 | door | 2.30 | 1716 | 2.7% | 36.2% |
| door -x+y (y wall) 2 | door | 2.30 | 1614 | 2.5% | 34.1% |
| door -x+y (y wall) 3 | door | 2.30 | 1126 | 1.8% | 23.8% |
| door -x+y (y wall) 4 | door | 2.30 | 683 | 1.1% | 14.4% |
| door -x+y (x wall) 0 | door | 2.30 | 1521 | 2.4% | 32.1% |
| door -x+y (x wall) 1 | door | 2.30 | 1718 | 2.7% | 36.3% |
| door -x+y (x wall) 2 | door | 2.30 | 1608 | 2.5% | 34.0% |
| door -x+y (x wall) 3 | door | 2.30 | 1094 | 1.7% | 23.1% |
| door -x+y (x wall) 4 | door | 2.30 | 668 | 1.1% | 14.1% |
| door -x+y (corner) | door | 2.30 | 456 | 0.7% | 9.6% |
| door -x-y (y wall) 0 | door | 2.30 | 1529 | 2.4% | 32.3% |
| door -x-y (y wall) 1 | door | 2.30 | 1694 | 2.7% | 35.8% |
| door -x-y (y wall) 2 | door | 2.30 | 1631 | 2.6% | 34.4% |
| door -x-y (y wall) 3 | door | 2.30 | 1134 | 1.8% | 24.0% |
| door -x-y (y wall) 4 | door | 2.30 | 672 | 1.1% | 14.2% |
| door -x-y (x wall) 0 | door | 2.30 | 1528 | 2.4% | 32.3% |
| door -x-y (x wall) 1 | door | 2.30 | 1686 | 2.7% | 35.6% |
| door -x-y (x wall) 2 | door | 2.30 | 1628 | 2.6% | 34.4% |
| door -x-y (x wall) 3 | door | 2.30 | 1156 | 1.8% | 24.4% |
| door -x-y (x wall) 4 | door | 2.30 | 644 | 1.0% | 13.6% |
| door -x-y (corner) | door | 2.30 | 370 | 0.6% | 7.8% |
| door +x-y (y wall) 0 | door | 2.30 | 1534 | 2.4% | 32.4% |
| door +x-y (y wall) 1 | door | 2.30 | 1672 | 2.6% | 35.3% |
| door +x-y (y wall) 2 | door | 2.30 | 1565 | 2.5% | 33.1% |
| door +x-y (y wall) 3 | door | 2.30 | 1224 | 1.9% | 25.9% |
| door +x-y (y wall) 4 | door | 2.30 | 718 | 1.1% | 15.2% |
| door +x-y (x wall) 0 | door | 2.30 | 1515 | 2.4% | 32.0% |
| door +x-y (x wall) 1 | door | 2.30 | 1688 | 2.7% | 35.7% |
| door +x-y (x wall) 2 | door | 2.30 | 1580 | 2.5% | 33.4% |
| door +x-y (x wall) 3 | door | 2.30 | 1180 | 1.9% | 24.9% |
| door +x-y (x wall) 4 | door | 2.30 | 604 | 1.0% | 12.8% |
| door +x-y (corner) | door | 2.30 | 398 | 0.6% | 8.4% |
| **doors (44)** | door | 101.20 | 54788 | 86.4% | |
| **avenues (4)** | avenue | 22.64 | 8636 | 13.6% | |

**Unused exit width: 0.0 of 123.8 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 1477.4 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 24.9%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 2312 | 3.6% | 2312 | 3.6% |
| straight +x+y (y wing) 1 | straight | yes | 1893 | 3.0% | 1680 | 2.6% |
| straight +x+y (y wing) 2 | straight | yes | 1613 | 2.5% | 1597 | 2.5% |
| straight +x+y (y wing) 3 | straight | yes | 1198 | 1.9% | 1194 | 1.9% |
| straight +x+y (y wing) 4 | straight | yes | 678 | 1.1% | 652 | 1.0% |
| straight +x+y (x wing) 0 | straight | yes | 2323 | 3.7% | 2323 | 3.7% |
| straight +x+y (x wing) 1 | straight | yes | 1892 | 3.0% | 1678 | 2.6% |
| straight +x+y (x wing) 2 | straight | yes | 1617 | 2.5% | 1603 | 2.5% |
| straight +x+y (x wing) 3 | straight | yes | 1198 | 1.9% | 1196 | 1.9% |
| straight +x+y (x wing) 4 | straight | yes | 626 | 1.0% | 597 | 0.9% |
| corner +x+y | corner | yes | 2300 | 3.6% | 1024 | 1.6% |
| straight -x+y (y wing) 0 | straight | yes | 2350 | 3.7% | 2350 | 3.7% |
| straight -x+y (y wing) 1 | straight | yes | 1885 | 3.0% | 1716 | 2.7% |
| straight -x+y (y wing) 2 | straight | yes | 1638 | 2.6% | 1629 | 2.6% |
| straight -x+y (y wing) 3 | straight | yes | 1164 | 1.8% | 1151 | 1.8% |
| straight -x+y (y wing) 4 | straight | yes | 675 | 1.1% | 643 | 1.0% |
| straight -x+y (x wing) 0 | straight | yes | 2323 | 3.7% | 2322 | 3.7% |
| straight -x+y (x wing) 1 | straight | yes | 1909 | 3.0% | 1718 | 2.7% |
| straight -x+y (x wing) 2 | straight | yes | 1634 | 2.6% | 1628 | 2.6% |
| straight -x+y (x wing) 3 | straight | yes | 1123 | 1.8% | 1116 | 1.8% |
| straight -x+y (x wing) 4 | straight | yes | 647 | 1.0% | 626 | 1.0% |
| corner -x+y | corner | yes | 2188 | 3.4% | 957 | 1.5% |
| straight -x-y (y wing) 0 | straight | yes | 2332 | 3.7% | 2332 | 3.7% |
| straight -x-y (y wing) 1 | straight | yes | 1904 | 3.0% | 1698 | 2.7% |
| straight -x-y (y wing) 2 | straight | yes | 1645 | 2.6% | 1637 | 2.6% |
| straight -x-y (y wing) 3 | straight | yes | 1148 | 1.8% | 1146 | 1.8% |
| straight -x-y (y wing) 4 | straight | yes | 676 | 1.1% | 654 | 1.0% |
| straight -x-y (x wing) 0 | straight | yes | 2329 | 3.7% | 2329 | 3.7% |
| straight -x-y (x wing) 1 | straight | yes | 1915 | 3.0% | 1687 | 2.7% |
| straight -x-y (x wing) 2 | straight | yes | 1656 | 2.6% | 1651 | 2.6% |
| straight -x-y (x wing) 3 | straight | yes | 1144 | 1.8% | 1142 | 1.8% |
| straight -x-y (x wing) 4 | straight | yes | 653 | 1.0% | 635 | 1.0% |
| corner -x-y | corner | yes | 2219 | 3.5% | 945 | 1.5% |
| straight +x-y (y wing) 0 | straight | yes | 2325 | 3.7% | 2325 | 3.7% |
| straight +x-y (y wing) 1 | straight | yes | 1899 | 3.0% | 1681 | 2.7% |
| straight +x-y (y wing) 2 | straight | yes | 1601 | 2.5% | 1589 | 2.5% |
| straight +x-y (y wing) 3 | straight | yes | 1216 | 1.9% | 1212 | 1.9% |
| straight +x-y (y wing) 4 | straight | yes | 730 | 1.2% | 706 | 1.1% |
| straight +x-y (x wing) 0 | straight | yes | 2317 | 3.7% | 2317 | 3.7% |
| straight +x-y (x wing) 1 | straight | yes | 1902 | 3.0% | 1693 | 2.7% |
| straight +x-y (x wing) 2 | straight | yes | 1599 | 2.5% | 1589 | 2.5% |
| straight +x-y (x wing) 3 | straight | yes | 1207 | 1.9% | 1204 | 1.9% |
| straight +x-y (x wing) 4 | straight | yes | 587 | 0.9% | 571 | 0.9% |
| corner +x-y | corner | yes | 2314 | 3.6% | 969 | 1.5% |
| **straight (40)** | | | 61483 | | 59529 | 93.9% |
| **corner (4)** | | | 9021 | | 3895 | 6.1% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 2163 | 70.8 | 1172.4 | 0.25 | 0.31 | 0.0% |
| -x | 2179 | 70.5 | 1176.2 | 0.25 | 0.31 | 0.0% |
| +y | 2126 | 70.5 | 1179.7 | 0.24 | 0.32 | 0.0% |
| -y | 2168 | 70.5 | 1178.3 | 0.25 | 0.32 | 0.0% |
| door +x+y (y wall) 0 | 1527 | 4.9 | 1261.6 | 0.38 | 0.56 | 0.0% |
| door +x+y (y wall) 1 | 1678 | 4.9 | 1418.3 | 0.37 | 0.53 | 0.0% |
| door +x+y (y wall) 2 | 1576 | 4.9 | 1463.6 | 0.34 | 0.50 | 0.0% |
| door +x+y (y wall) 3 | 1207 | 4.9 | 1467.5 | 0.26 | 0.56 | 0.0% |
| door +x+y (y wall) 4 | 660 | 4.9 | 1369.7 | 0.15 | 0.59 | 0.0% |
| door +x+y (x wall) 0 | 1525 | 4.9 | 1158.2 | 0.41 | 0.56 | 0.0% |
| door +x+y (x wall) 1 | 1678 | 4.9 | 1380.4 | 0.38 | 0.56 | 0.0% |
| door +x+y (x wall) 2 | 1596 | 4.9 | 1450.2 | 0.34 | 0.56 | 0.0% |
| door +x+y (x wall) 3 | 1199 | 4.9 | 1412.7 | 0.27 | 0.56 | 0.0% |
| door +x+y (x wall) 4 | 601 | 5.1 | 1432.3 | 0.13 | 0.53 | 0.0% |
| door +x+y (corner) | 457 | 6.3 | 1108.9 | 0.13 | 0.56 | 0.0% |
| door -x+y (y wall) 0 | 1530 | 4.9 | 1155.3 | 0.41 | 0.56 | 0.0% |
| door -x+y (y wall) 1 | 1716 | 4.9 | 1428.8 | 0.38 | 0.56 | 0.0% |
| door -x+y (y wall) 2 | 1614 | 4.9 | 1469.7 | 0.34 | 0.53 | 0.0% |
| door -x+y (y wall) 3 | 1126 | 4.9 | 1474.3 | 0.24 | 0.56 | 0.0% |
| door -x+y (y wall) 4 | 683 | 5.1 | 1410.4 | 0.15 | 0.53 | 0.0% |
| door -x+y (x wall) 0 | 1521 | 4.9 | 1147.7 | 0.42 | 0.53 | 0.0% |
| door -x+y (x wall) 1 | 1718 | 4.9 | 1430.7 | 0.38 | 0.53 | 0.0% |
| door -x+y (x wall) 2 | 1608 | 4.9 | 1467.6 | 0.34 | 0.53 | 0.0% |
| door -x+y (x wall) 3 | 1094 | 4.9 | 1477.4 | 0.23 | 0.53 | 0.0% |
| door -x+y (x wall) 4 | 668 | 4.9 | 1469.6 | 0.14 | 0.56 | 0.0% |
| door -x+y (corner) | 456 | 6.3 | 864.2 | 0.17 | 0.53 | 0.0% |
| door -x-y (y wall) 0 | 1529 | 4.9 | 1261.8 | 0.38 | 0.53 | 0.0% |
| door -x-y (y wall) 1 | 1694 | 4.9 | 1424.4 | 0.37 | 0.53 | 0.0% |
| door -x-y (y wall) 2 | 1631 | 4.9 | 1462.4 | 0.35 | 0.53 | 0.0% |
| door -x-y (y wall) 3 | 1134 | 4.9 | 1453.3 | 0.24 | 0.53 | 0.0% |
| door -x-y (y wall) 4 | 672 | 4.9 | 1407.8 | 0.15 | 0.56 | 0.0% |
| door -x-y (x wall) 0 | 1528 | 4.9 | 1252.2 | 0.38 | 0.56 | 0.0% |
| door -x-y (x wall) 1 | 1686 | 4.9 | 1395.4 | 0.38 | 0.56 | 0.0% |
| door -x-y (x wall) 2 | 1628 | 4.9 | 1460.8 | 0.35 | 0.56 | 0.0% |
| door -x-y (x wall) 3 | 1156 | 4.9 | 1412.0 | 0.26 | 0.56 | 0.0% |
| door -x-y (x wall) 4 | 644 | 5.1 | 1422.2 | 0.14 | 0.53 | 0.0% |
| door -x-y (corner) | 370 | 6.3 | 1065.5 | 0.11 | 0.56 | 0.0% |
| door +x-y (y wall) 0 | 1534 | 4.9 | 1256.4 | 0.38 | 0.53 | 0.0% |
| door +x-y (y wall) 1 | 1672 | 4.9 | 1423.6 | 0.37 | 0.53 | 0.0% |
| door +x-y (y wall) 2 | 1565 | 4.9 | 1466.9 | 0.33 | 0.56 | 0.0% |
| door +x-y (y wall) 3 | 1224 | 4.9 | 1460.5 | 0.26 | 0.53 | 0.0% |
| door +x-y (y wall) 4 | 718 | 5.1 | 1459.6 | 0.15 | 0.53 | 0.0% |
| door +x-y (x wall) 0 | 1515 | 4.9 | 1298.7 | 0.37 | 0.53 | 0.0% |
| door +x-y (x wall) 1 | 1688 | 4.9 | 1427.4 | 0.37 | 0.56 | 0.0% |
| door +x-y (x wall) 2 | 1580 | 4.9 | 1466.4 | 0.34 | 0.56 | 0.0% |
| door +x-y (x wall) 3 | 1180 | 4.9 | 1419.7 | 0.26 | 0.56 | 0.0% |
| door +x-y (x wall) 4 | 604 | 5.1 | 1466.9 | 0.13 | 0.56 | 0.0% |
| door +x-y (corner) | 398 | 6.5 | 1100.0 | 0.11 | 0.56 | 0.0% |

Mean flow / w J averaged over the doors 0.29, over the avenues 0.25.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 103.1 | 2312 | 1525 / 787 / 913 | 0.7 | 1173.1 | 2.75 | 5.22 | 92% | 86% | 6% | 4.44 |
| straight +x+y (y wing) 1 | 1.20 | 81.5 | 1874 | 1680 / 0 / 298 | 0.7 | 1415.3 | 1.40 | 2.91 | 91% | 64% | 27% | 3.33 |
| straight +x+y (y wing) 2 | 1.20 | 61.0 | 1533 | 1597 / 0 / 47 | 0.7 | 1460.6 | 1.13 | 2.31 | 80% | 69% | 11% | 3.80 |
| straight +x+y (y wing) 3 | 1.20 | 39.4 | 933 | 1194 / 0 / 6 | 0.7 | 1464.5 | 0.82 | 1.71 | 46% | 39% | 7% | 3.90 |
| straight +x+y (y wing) 4 | 1.20 | 18.8 | 396 | 652 / 0 / 27 | 0.7 | 1366.7 | 0.50 | 1.81 | 19% | 17% | 2% | 3.74 |
| straight +x+y (x wing) 0 | 1.20 | 103.1 | 2323 | 1525 / 798 / 1009 | 0.7 | 1155.3 | 2.89 | 5.12 | 92% | 87% | 5% | 4.26 |
| straight +x+y (x wing) 1 | 1.20 | 81.5 | 1867 | 1678 / 0 / 328 | 0.7 | 1377.4 | 1.46 | 2.81 | 91% | 63% | 29% | 3.20 |
| straight +x+y (x wing) 2 | 1.20 | 61.0 | 1523 | 1603 / 0 / 18 | 0.7 | 1447.2 | 1.12 | 1.81 | 80% | 68% | 12% | 3.70 |
| straight +x+y (x wing) 3 | 1.20 | 39.4 | 938 | 1196 / 0 / 4 | 0.7 | 1409.7 | 0.85 | 1.60 | 47% | 41% | 6% | 3.74 |
| straight +x+y (x wing) 4 | 1.20 | 18.8 | 403 | 597 / 0 / 43 | 0.7 | 1429.3 | 0.45 | 1.71 | 27% | 16% | 11% | 2.67 |
| corner +x+y | 1.20 | 186.0 | 1754 | 457 / 567 / 1391 | 0.7 | 1414.5 | 1.71 | 3.61 | 93% | 63% | 30% | 2.68 |
| straight -x+y (y wing) 0 | 1.20 | 103.1 | 2350 | 1530 / 820 / 1136 | 0.7 | 1152.3 | 3.03 | 5.22 | 92% | 88% | 4% | 4.29 |
| straight -x+y (y wing) 1 | 1.20 | 81.5 | 1862 | 1716 / 0 / 267 | 0.7 | 1425.8 | 1.39 | 2.51 | 93% | 67% | 26% | 3.34 |
| straight -x+y (y wing) 2 | 1.20 | 61.0 | 1525 | 1629 / 0 / 14 | 0.7 | 1466.8 | 1.12 | 1.91 | 77% | 68% | 9% | 3.77 |
| straight -x+y (y wing) 3 | 1.20 | 39.4 | 943 | 1151 / 0 / 20 | 0.7 | 1471.3 | 0.80 | 1.71 | 51% | 41% | 10% | 3.50 |
| straight -x+y (y wing) 4 | 1.20 | 18.8 | 401 | 643 / 0 / 33 | 0.7 | 1407.5 | 0.48 | 2.11 | 18% | 17% | 1% | 3.87 |
| straight -x+y (x wing) 0 | 1.20 | 103.1 | 2323 | 1521 / 802 / 985 | 0.7 | 1144.8 | 2.89 | 5.12 | 90% | 88% | 3% | 4.51 |
| straight -x+y (x wing) 1 | 1.20 | 81.5 | 1880 | 1718 / 0 / 282 | 0.7 | 1427.8 | 1.40 | 2.71 | 92% | 63% | 29% | 3.35 |
| straight -x+y (x wing) 2 | 1.20 | 61.0 | 1518 | 1628 / 0 / 36 | 0.7 | 1464.7 | 1.14 | 2.41 | 78% | 68% | 10% | 3.87 |
| straight -x+y (x wing) 3 | 1.20 | 39.4 | 949 | 1116 / 0 / 24 | 0.7 | 1474.5 | 0.77 | 1.81 | 51% | 41% | 10% | 3.69 |
| straight -x+y (x wing) 4 | 1.20 | 18.8 | 398 | 626 / 0 / 33 | 0.7 | 1466.6 | 0.45 | 1.71 | 19% | 16% | 3% | 3.63 |
| corner -x+y | 1.20 | 186.0 | 1707 | 456 / 501 / 1338 | 0.7 | 1442.8 | 1.59 | 3.51 | 92% | 65% | 28% | 2.65 |
| straight -x-y (y wing) 0 | 1.20 | 103.1 | 2332 | 1525 / 807 / 924 | 0.7 | 1139.3 | 2.86 | 5.22 | 90% | 89% | 2% | 4.45 |
| straight -x-y (y wing) 1 | 1.20 | 81.5 | 1880 | 1698 / 0 / 283 | 0.7 | 1421.5 | 1.39 | 2.91 | 91% | 62% | 29% | 3.31 |
| straight -x-y (y wing) 2 | 1.20 | 61.0 | 1532 | 1637 / 0 / 13 | 0.7 | 1459.4 | 1.13 | 1.60 | 78% | 66% | 12% | 3.88 |
| straight -x-y (y wing) 3 | 1.20 | 39.4 | 935 | 1146 / 0 / 4 | 0.7 | 1450.3 | 0.79 | 1.71 | 49% | 39% | 10% | 3.71 |
| straight -x-y (y wing) 4 | 1.20 | 18.8 | 400 | 654 / 0 / 27 | 0.7 | 1404.9 | 0.48 | 1.71 | 19% | 16% | 3% | 3.69 |
| straight -x-y (x wing) 0 | 1.20 | 103.1 | 2329 | 1527 / 803 / 944 | 0.7 | 1146.2 | 2.86 | 5.62 | 91% | 88% | 3% | 4.28 |
| straight -x-y (x wing) 1 | 1.20 | 81.5 | 1892 | 1687 / 0 / 309 | 0.7 | 1392.4 | 1.43 | 2.81 | 93% | 64% | 29% | 3.32 |
| straight -x-y (x wing) 2 | 1.20 | 61.0 | 1530 | 1651 / 0 / 7 | 0.7 | 1457.8 | 1.14 | 1.81 | 78% | 67% | 11% | 3.82 |
| straight -x-y (x wing) 3 | 1.20 | 39.4 | 937 | 1142 / 0 / 7 | 0.7 | 1409.0 | 0.82 | 1.71 | 49% | 41% | 8% | 3.65 |
| straight -x-y (x wing) 4 | 1.20 | 18.8 | 399 | 635 / 0 / 21 | 0.7 | 1419.2 | 0.46 | 1.71 | 20% | 16% | 4% | 3.45 |
| corner -x-y | 1.20 | 186.0 | 1690 | 370 / 575 / 1332 | 0.7 | 1400.1 | 1.63 | 3.31 | 93% | 72% | 21% | 2.78 |
| straight +x-y (y wing) 0 | 1.20 | 103.1 | 2325 | 1525 / 800 / 1094 | 0.7 | 1146.2 | 2.98 | 5.32 | 92% | 89% | 3% | 4.36 |
| straight +x-y (y wing) 1 | 1.20 | 81.5 | 1884 | 1681 / 0 / 313 | 0.7 | 1420.8 | 1.40 | 3.01 | 92% | 62% | 30% | 3.22 |
| straight +x-y (y wing) 2 | 1.20 | 61.0 | 1522 | 1589 / 0 / 29 | 0.7 | 1464.0 | 1.11 | 2.01 | 81% | 68% | 13% | 3.68 |
| straight +x-y (y wing) 3 | 1.20 | 39.4 | 927 | 1212 / 0 / 7 | 0.7 | 1457.5 | 0.84 | 1.71 | 47% | 38% | 9% | 3.70 |
| straight +x-y (y wing) 4 | 1.20 | 18.8 | 391 | 706 / 0 / 26 | 0.7 | 1456.6 | 0.50 | 1.81 | 18% | 16% | 3% | 3.63 |
| straight +x-y (x wing) 0 | 1.20 | 103.1 | 2317 | 1510 / 807 / 969 | 0.7 | 1142.0 | 2.88 | 5.22 | 91% | 88% | 3% | 4.31 |
| straight +x-y (x wing) 1 | 1.20 | 81.5 | 1881 | 1693 / 0 / 308 | 0.7 | 1424.4 | 1.41 | 3.01 | 92% | 63% | 29% | 3.27 |
| straight +x-y (x wing) 2 | 1.20 | 61.0 | 1511 | 1589 / 0 / 16 | 0.7 | 1463.4 | 1.10 | 1.91 | 80% | 67% | 13% | 3.62 |
| straight +x-y (x wing) 3 | 1.20 | 39.4 | 939 | 1204 / 0 / 8 | 0.7 | 1416.7 | 0.86 | 1.71 | 50% | 41% | 9% | 3.63 |
| straight +x-y (x wing) 4 | 1.20 | 18.8 | 378 | 571 / 0 / 56 | 0.7 | 1464.0 | 0.43 | 2.11 | 22% | 16% | 6% | 3.12 |
| corner +x-y | 1.20 | 186.0 | 1781 | 398 / 571 / 1465 | 0.7 | 1440.0 | 1.69 | 4.11 | 92% | 60% | 32% | 2.70 |

The last agent out (agent 24657, t100 1477.4 s): last gangway straight -x+y (x wing) 3, exit door -x+y (x wall) 3. The gangway that cleared last: straight -x+y (x wing) 3 at 1474.5 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 8804 | 7800.4 | 7.16 | 1474.5 / 1393.1 / 1348.7 | 1378.8 / 1358.9 / 1329.3 | 7040192.2 | 13396377 | 0.169 |
| gangway | 3792 | 3512.9 | 7.16 | 1472.7 / 1393.1 / 1348.7 | 1378.8 / 1358.9 / 1329.3 | 7040192.2 | 12594563 | 0.103 |
| walkway | 276 | 257.4 | 3.21 | 852.1 / 425.5 / 0.0 | 430.4 / 101.6 / 0.0 | 0.0 | 76477 | 0.814 |
| avenue | 1920 | 1801.4 | 1.88 | 871.0 / 0.0 / 0.0 | 587.2 / 0.0 / 0.0 | 0.0 | 517623 | 1.334 |
| exit | 4 | 2.0 | 0.00 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 0 | - |
| concourse | 2812 | 2226.8 | 2.60 | 1432.3 / 20.6 / 0.0 | 1056.3 / 2.6 / 0.0 | 0.0 | 207714 | 1.039 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 25392 | 16030.4 | 7.87 | 1339.6 / 1337.3 / 1299.7 | 1339.6 / 1337.3 / 1292.4 | 9176452.7 | 22457365 | 0.022 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 208 x 208 from (-104, -104) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -38.5 | 38.5 | gangway | 1.00 | 6.09 | 1375.3 | 1346.1 | 1265.6 | 7417.3 | 0.010 |
| 2 | 35.5 | -35.5 | gangway | 1.00 | 5.90 | 1365.5 | 1354.5 | 1319.7 | 7335.2 | 0.005 |
| 3 | -36.5 | 36.5 | gangway | 1.00 | 5.71 | 1371.1 | 1358.7 | 1329.3 | 7279.9 | 0.007 |
| 4 | 34.5 | -34.5 | gangway | 1.00 | 5.67 | 1357.3 | 1349.2 | 1289.6 | 7215.2 | 0.004 |
| 5 | -43.5 | -43.5 | gangway | 1.00 | 6.10 | 1302.4 | 1290.8 | 1195.1 | 7172.8 | 0.011 |
| 6 | -35.5 | -35.5 | gangway | 1.00 | 5.81 | 1354.1 | 1347.8 | 1249.4 | 7140.2 | 0.005 |
| 7 | -43.5 | -42.5 | gangway | 1.00 | 6.20 | 1293.6 | 1263.9 | 1171.2 | 7129.0 | 0.012 |
| 8 | -36.5 | -36.5 | gangway | 1.00 | 5.66 | 1359.0 | 1356.8 | 1274.2 | 7039.4 | 0.005 |
| 9 | -43.5 | 42.5 | gangway | 1.00 | 6.19 | 1341.4 | 1320.2 | 1158.2 | 6981.5 | 0.013 |
| 10 | -40.5 | 40.5 | gangway | 1.00 | 5.87 | 1378.8 | 1325.4 | 1198.8 | 6950.9 | 0.015 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 38.5 | -36.5 | seat row | 0.50 | 7.45 | 1328.6 | 1323.2 | 1292.4 | 4754.3 | 0.003 |
| 2 | 38.5 | 36.5 | seat row | 0.50 | 7.42 | 1317.9 | 1315.3 | 1289.6 | 4635.9 | 0.004 |
| 3 | -36.5 | 38.5 | seat row | 0.50 | 7.52 | 1331.2 | 1316.0 | 1253.9 | 4612.0 | 0.003 |
| 4 | 36.5 | 38.5 | seat row | 0.50 | 7.38 | 1313.0 | 1303.6 | 1277.2 | 4521.9 | 0.003 |
| 5 | -38.5 | 36.5 | seat row | 0.50 | 7.48 | 1313.2 | 1289.2 | 1245.2 | 4445.5 | 0.003 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 8630; agent-steps of seated agents on another row's clearway: 1588669.

## Deposit check

Person-seconds deposited: 35859624.7, of them in excluded cells: 5883.054.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 9247456 overlapping pair-steps: p99 0.0020, max 0.0872 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0020 max 0.0872; venue-geometry 17: p99 0.0009 max 0.0009 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00762 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 61 (longest 2 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.40 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 3818 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
