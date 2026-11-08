# Experiment `L_load150_s5`

**Task 5.11 stage 1 (gridlock robustness, default model, AMD 26.10.1): venue L, the achievable maximum 109.28% (150% requested, seed 5)**

Venue L (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (4000 x 4000), cache key a2f3aaf59c2252b7, content hash 022d17b202313d70). 69311 agents (load 109.3%, requested 150%): every one of the 63424 seats and 5887 standing (spawnOvercrowdedCrowd, seed 5; below), buffer N = 131072, 8652 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 12307550 evaluations, 670627 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.09)** (the L venue's design capacity 63424, jam capacity 171923: 23822.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `15aa31e8667e4a9417fde7884d907d1832c5e2d6`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-23T18:21:16, 1287.9 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Spawn (overcrowding)

| | |
|---|---|
| seated | 63424 (every seat) |
| standing | **5887** (requested round((1.50 - 1) x 63424) = 31712; at most 5887 = floor(2.5 p/m^2 x 2355.0 m^2)) |
| standing floor | walkway + rear concourse, 2355.0 m^2 |
| standing on the walkway / concourse / gangways | 629 / 5258 / 0 |
| **load** | **109.28%** of the seats (requested 150%; the floor takes no more: the achievable maximum) |
| standing crowd's mean density | 2.500 p/m^2 |
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 4.21, all circulation cells 4.21 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 5, 363970 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 2798 | 489.4 |
| t90 | 6173 | 1079.7 |
| t100 | 8652 | 1513.3 |

t_p: the step by which ceil(p x 69311) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 2168 | 85 | 60.2 | 1213.7 | 19.9 | 59.5 | 60.0-70.0 |
| -x | 5.66 | 2239 | 90 | 60.2 | 1198.1 | 20.9 | 62.7 | 60.0-70.0 |
| +y | 5.66 | 2168 | 82 | 60.2 | 1207.2 | 20.0 | 58.5 | 59.5-69.4 |
| -y | 5.66 | 2176 | 90 | 60.2 | 1196.9 | 20.3 | 61.7 | 60.0-70.0 |
| door +x+y (y wall) 0 | 2.30 | 1673 | 2726 | 0.9 | 1318.1 | 33.1 | 112.5 | 20.5-30.4 |
| door +x+y (y wall) 1 | 2.30 | 1841 | 2255 | 0.9 | 1450.5 | 33.1 | 107.3 | 15.6-25.5 |
| door +x+y (y wall) 2 | 2.30 | 1677 | 1712 | 0.9 | 1448.8 | 30.2 | 115.1 | 0.7-10.7 |
| door +x+y (y wall) 3 | 2.30 | 1240 | 1161 | 0.9 | 1469.0 | 22.0 | 107.3 | 6.5-16.4 |
| door +x+y (y wall) 4 | 2.30 | 915 | 647 | 0.9 | 1475.9 | 16.2 | 107.3 | 22.0-32.0 |
| door +x+y (x wall) 0 | 2.30 | 1680 | 2727 | 0.9 | 1299.4 | 33.7 | 104.7 | 26.2-36.2 |
| door +x+y (x wall) 1 | 2.30 | 1823 | 2258 | 0.7 | 1434.9 | 33.2 | 115.1 | 0.5-10.5 |
| door +x+y (x wall) 2 | 2.30 | 1668 | 1712 | 0.9 | 1482.0 | 29.4 | 107.3 | 0.7-10.7 |
| door +x+y (x wall) 3 | 2.30 | 1263 | 1166 | 0.9 | 1478.3 | 22.3 | 112.5 | 18.2-28.2 |
| door +x+y (x wall) 4 | 2.30 | 890 | 647 | 0.9 | 1486.2 | 15.6 | 107.3 | 18.4-28.3 |
| door +x+y (corner) | 2.30 | 573 | 252 | 0.9 | 1309.2 | 11.4 | 73.3 | 0.7-10.7 |
| door -x+y (y wall) 0 | 2.30 | 1659 | 2727 | 0.7 | 1197.2 | 36.2 | 109.9 | 14.0-24.0 |
| door -x+y (y wall) 1 | 2.30 | 1822 | 2252 | 0.7 | 1413.9 | 33.6 | 112.5 | 32.9-42.9 |
| door -x+y (y wall) 2 | 2.30 | 1700 | 1715 | 0.9 | 1489.7 | 29.8 | 115.1 | 8.7-18.7 |
| door -x+y (y wall) 3 | 2.30 | 1403 | 1166 | 0.7 | 1489.9 | 24.6 | 112.5 | 2.4-12.4 |
| door -x+y (y wall) 4 | 2.30 | 746 | 636 | 1.0 | 1480.8 | 13.2 | 109.9 | 0.3-10.3 |
| door -x+y (x wall) 0 | 2.30 | 1647 | 2723 | 0.9 | 1154.2 | 37.2 | 109.9 | 28.3-38.3 |
| door -x+y (x wall) 1 | 2.30 | 1806 | 2250 | 0.9 | 1411.3 | 33.4 | 109.9 | 22.0-32.0 |
| door -x+y (x wall) 2 | 2.30 | 1744 | 1711 | 0.9 | 1480.9 | 30.7 | 107.3 | 8.7-18.7 |
| door -x+y (x wall) 3 | 2.30 | 1368 | 1163 | 0.9 | 1484.6 | 24.0 | 112.5 | 6.6-16.6 |
| door -x+y (x wall) 4 | 2.30 | 670 | 638 | 0.9 | 1358.9 | 12.9 | 109.9 | 26.1-36.0 |
| door -x+y (corner) | 2.30 | 475 | 244 | 0.9 | 1156.5 | 10.7 | 75.9 | 0.5-10.5 |
| door -x-y (y wall) 0 | 2.30 | 1660 | 2732 | 0.9 | 1250.9 | 34.6 | 115.1 | 36.9-46.9 |
| door -x-y (y wall) 1 | 2.30 | 1812 | 2247 | 0.9 | 1420.6 | 33.3 | 107.3 | 2.3-12.2 |
| door -x-y (y wall) 2 | 2.30 | 1664 | 1717 | 0.9 | 1438.8 | 30.2 | 112.5 | 24.0-33.9 |
| door -x-y (y wall) 3 | 2.30 | 1278 | 1154 | 0.7 | 1473.6 | 22.6 | 112.5 | 23.4-33.4 |
| door -x-y (y wall) 4 | 2.30 | 870 | 648 | 0.9 | 1385.1 | 16.4 | 115.1 | 33.8-43.7 |
| door -x-y (x wall) 0 | 2.30 | 1665 | 2725 | 0.9 | 1168.9 | 37.2 | 115.1 | 22.0-32.0 |
| door -x-y (x wall) 1 | 2.30 | 1810 | 2255 | 1.0 | 1385.8 | 34.1 | 112.5 | 22.0-32.0 |
| door -x-y (x wall) 2 | 2.30 | 1651 | 1700 | 0.7 | 1455.9 | 29.6 | 112.5 | 21.0-31.0 |
| door -x-y (x wall) 3 | 2.30 | 1285 | 1156 | 0.9 | 1473.4 | 22.8 | 109.9 | 0.7-10.7 |
| door -x-y (x wall) 4 | 2.30 | 835 | 641 | 0.9 | 1448.8 | 15.0 | 109.9 | 4.4-14.3 |
| door -x-y (corner) | 2.30 | 557 | 246 | 0.7 | 1126.7 | 12.9 | 70.6 | 0.5-10.5 |
| door +x-y (y wall) 0 | 2.30 | 1675 | 2726 | 0.9 | 1226.6 | 35.6 | 109.9 | 5.8-15.7 |
| door +x-y (y wall) 1 | 2.30 | 1841 | 2256 | 0.9 | 1484.4 | 32.4 | 104.7 | 0.7-10.7 |
| door +x-y (y wall) 2 | 2.30 | 1691 | 1713 | 0.9 | 1513.3 | 29.2 | 112.5 | 34.3-44.3 |
| door +x-y (y wall) 3 | 2.30 | 1306 | 1157 | 0.9 | 1479.9 | 23.0 | 115.1 | 17.7-27.6 |
| door +x-y (y wall) 4 | 2.30 | 825 | 643 | 0.9 | 1410.1 | 15.3 | 112.5 | 3.7-13.6 |
| door +x-y (x wall) 0 | 2.30 | 1678 | 2729 | 0.9 | 1275.6 | 34.3 | 112.5 | 2.4-12.4 |
| door +x-y (x wall) 1 | 2.30 | 1843 | 2257 | 0.7 | 1492.1 | 32.2 | 107.3 | 36.2-46.2 |
| door +x-y (x wall) 2 | 2.30 | 1735 | 1714 | 0.7 | 1493.2 | 30.3 | 104.7 | 13.3-23.3 |
| door +x-y (x wall) 3 | 2.30 | 1337 | 1168 | 0.9 | 1490.7 | 23.4 | 107.3 | 4.9-14.9 |
| door +x-y (x wall) 4 | 2.30 | 749 | 646 | 1.0 | 1471.0 | 13.3 | 115.1 | 26.9-36.9 |
| door +x-y (corner) | 2.30 | 510 | 246 | 0.7 | 1112.4 | 12.0 | 70.6 | 0.7-10.7 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (2.30 m; a corner door's: the gap between its wall ends, 2.30 m); agents are removed past the outer wall's outer face (92.71 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 2168 | 3.1% | 18.2% |
| -x | avenue | 5.66 | 2239 | 3.2% | 18.8% |
| +y | avenue | 5.66 | 2168 | 3.1% | 18.2% |
| -y | avenue | 5.66 | 2176 | 3.1% | 18.2% |
| door +x+y (y wall) 0 | door | 2.30 | 1673 | 2.4% | 34.5% |
| door +x+y (y wall) 1 | door | 2.30 | 1841 | 2.7% | 38.0% |
| door +x+y (y wall) 2 | door | 2.30 | 1677 | 2.4% | 34.6% |
| door +x+y (y wall) 3 | door | 2.30 | 1240 | 1.8% | 25.6% |
| door +x+y (y wall) 4 | door | 2.30 | 915 | 1.3% | 18.9% |
| door +x+y (x wall) 0 | door | 2.30 | 1680 | 2.4% | 34.6% |
| door +x+y (x wall) 1 | door | 2.30 | 1823 | 2.6% | 37.6% |
| door +x+y (x wall) 2 | door | 2.30 | 1668 | 2.4% | 34.4% |
| door +x+y (x wall) 3 | door | 2.30 | 1263 | 1.8% | 26.0% |
| door +x+y (x wall) 4 | door | 2.30 | 890 | 1.3% | 18.4% |
| door +x+y (corner) | door | 2.30 | 573 | 0.8% | 11.8% |
| door -x+y (y wall) 0 | door | 2.30 | 1659 | 2.4% | 34.2% |
| door -x+y (y wall) 1 | door | 2.30 | 1822 | 2.6% | 37.6% |
| door -x+y (y wall) 2 | door | 2.30 | 1700 | 2.5% | 35.1% |
| door -x+y (y wall) 3 | door | 2.30 | 1403 | 2.0% | 28.9% |
| door -x+y (y wall) 4 | door | 2.30 | 746 | 1.1% | 15.4% |
| door -x+y (x wall) 0 | door | 2.30 | 1647 | 2.4% | 34.0% |
| door -x+y (x wall) 1 | door | 2.30 | 1806 | 2.6% | 37.2% |
| door -x+y (x wall) 2 | door | 2.30 | 1744 | 2.5% | 36.0% |
| door -x+y (x wall) 3 | door | 2.30 | 1368 | 2.0% | 28.2% |
| door -x+y (x wall) 4 | door | 2.30 | 670 | 1.0% | 13.8% |
| door -x+y (corner) | door | 2.30 | 475 | 0.7% | 9.8% |
| door -x-y (y wall) 0 | door | 2.30 | 1660 | 2.4% | 34.2% |
| door -x-y (y wall) 1 | door | 2.30 | 1812 | 2.6% | 37.4% |
| door -x-y (y wall) 2 | door | 2.30 | 1664 | 2.4% | 34.3% |
| door -x-y (y wall) 3 | door | 2.30 | 1278 | 1.8% | 26.4% |
| door -x-y (y wall) 4 | door | 2.30 | 870 | 1.3% | 17.9% |
| door -x-y (x wall) 0 | door | 2.30 | 1665 | 2.4% | 34.3% |
| door -x-y (x wall) 1 | door | 2.30 | 1810 | 2.6% | 37.3% |
| door -x-y (x wall) 2 | door | 2.30 | 1651 | 2.4% | 34.0% |
| door -x-y (x wall) 3 | door | 2.30 | 1285 | 1.9% | 26.5% |
| door -x-y (x wall) 4 | door | 2.30 | 835 | 1.2% | 17.2% |
| door -x-y (corner) | door | 2.30 | 557 | 0.8% | 11.5% |
| door +x-y (y wall) 0 | door | 2.30 | 1675 | 2.4% | 34.5% |
| door +x-y (y wall) 1 | door | 2.30 | 1841 | 2.7% | 38.0% |
| door +x-y (y wall) 2 | door | 2.30 | 1691 | 2.4% | 34.9% |
| door +x-y (y wall) 3 | door | 2.30 | 1306 | 1.9% | 26.9% |
| door +x-y (y wall) 4 | door | 2.30 | 825 | 1.2% | 17.0% |
| door +x-y (x wall) 0 | door | 2.30 | 1678 | 2.4% | 34.6% |
| door +x-y (x wall) 1 | door | 2.30 | 1843 | 2.7% | 38.0% |
| door +x-y (x wall) 2 | door | 2.30 | 1735 | 2.5% | 35.8% |
| door +x-y (x wall) 3 | door | 2.30 | 1337 | 1.9% | 27.6% |
| door +x-y (x wall) 4 | door | 2.30 | 749 | 1.1% | 15.4% |
| door +x-y (corner) | door | 2.30 | 510 | 0.7% | 10.5% |
| **doors (44)** | door | 101.20 | 60560 | 87.4% | |
| **avenues (4)** | avenue | 22.64 | 8751 | 12.6% | |

**Unused exit width: 0.0 of 123.8 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 1513.3 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 26.5%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 2342 | 3.4% | 2342 | 3.4% |
| straight +x+y (y wing) 1 | straight | yes | 1829 | 2.6% | 1731 | 2.5% |
| straight +x+y (y wing) 2 | straight | yes | 1618 | 2.3% | 1590 | 2.3% |
| straight +x+y (y wing) 3 | straight | yes | 1149 | 1.7% | 1137 | 1.6% |
| straight +x+y (y wing) 4 | straight | yes | 748 | 1.1% | 737 | 1.1% |
| straight +x+y (x wing) 0 | straight | yes | 2393 | 3.5% | 2393 | 3.5% |
| straight +x+y (x wing) 1 | straight | yes | 1815 | 2.6% | 1711 | 2.5% |
| straight +x+y (x wing) 2 | straight | yes | 1604 | 2.3% | 1584 | 2.3% |
| straight +x+y (x wing) 3 | straight | yes | 1168 | 1.7% | 1154 | 1.7% |
| straight +x+y (x wing) 4 | straight | yes | 727 | 1.0% | 710 | 1.0% |
| corner +x+y | corner | yes | 2158 | 3.1% | 777 | 1.1% |
| straight -x+y (y wing) 0 | straight | yes | 2364 | 3.4% | 2364 | 3.4% |
| straight -x+y (y wing) 1 | straight | yes | 1905 | 2.7% | 1707 | 2.5% |
| straight -x+y (y wing) 2 | straight | yes | 1591 | 2.3% | 1582 | 2.3% |
| straight -x+y (y wing) 3 | straight | yes | 1294 | 1.9% | 1292 | 1.9% |
| straight -x+y (y wing) 4 | straight | yes | 627 | 0.9% | 610 | 0.9% |
| straight -x+y (x wing) 0 | straight | yes | 2329 | 3.4% | 2329 | 3.4% |
| straight -x+y (x wing) 1 | straight | yes | 1876 | 2.7% | 1693 | 2.4% |
| straight -x+y (x wing) 2 | straight | yes | 1642 | 2.4% | 1630 | 2.4% |
| straight -x+y (x wing) 3 | straight | yes | 1279 | 1.8% | 1279 | 1.8% |
| straight -x+y (x wing) 4 | straight | yes | 525 | 0.8% | 513 | 0.7% |
| corner -x+y | corner | yes | 2188 | 3.2% | 867 | 1.3% |
| straight -x-y (y wing) 0 | straight | yes | 2303 | 3.3% | 2303 | 3.3% |
| straight -x-y (y wing) 1 | straight | yes | 1886 | 2.7% | 1704 | 2.5% |
| straight -x-y (y wing) 2 | straight | yes | 1616 | 2.3% | 1586 | 2.3% |
| straight -x-y (y wing) 3 | straight | yes | 1142 | 1.6% | 1132 | 1.6% |
| straight -x-y (y wing) 4 | straight | yes | 745 | 1.1% | 727 | 1.0% |
| straight -x-y (x wing) 0 | straight | yes | 2363 | 3.4% | 2363 | 3.4% |
| straight -x-y (x wing) 1 | straight | yes | 1881 | 2.7% | 1692 | 2.4% |
| straight -x-y (x wing) 2 | straight | yes | 1587 | 2.3% | 1575 | 2.3% |
| straight -x-y (x wing) 3 | straight | yes | 1178 | 1.7% | 1168 | 1.7% |
| straight -x-y (x wing) 4 | straight | yes | 697 | 1.0% | 683 | 1.0% |
| corner -x-y | corner | yes | 2269 | 3.3% | 932 | 1.3% |
| straight +x-y (y wing) 0 | straight | yes | 2406 | 3.5% | 2406 | 3.5% |
| straight +x-y (y wing) 1 | straight | yes | 1827 | 2.6% | 1723 | 2.5% |
| straight +x-y (y wing) 2 | straight | yes | 1608 | 2.3% | 1602 | 2.3% |
| straight +x-y (y wing) 3 | straight | yes | 1180 | 1.7% | 1178 | 1.7% |
| straight +x-y (y wing) 4 | straight | yes | 703 | 1.0% | 681 | 1.0% |
| straight +x-y (x wing) 0 | straight | yes | 2350 | 3.4% | 2350 | 3.4% |
| straight +x-y (x wing) 1 | straight | yes | 1841 | 2.7% | 1726 | 2.5% |
| straight +x-y (x wing) 2 | straight | yes | 1638 | 2.4% | 1628 | 2.3% |
| straight +x-y (x wing) 3 | straight | yes | 1206 | 1.7% | 1202 | 1.7% |
| straight +x-y (x wing) 4 | straight | yes | 632 | 0.9% | 615 | 0.9% |
| corner +x-y | corner | yes | 2086 | 3.0% | 754 | 1.1% |
| **straight (40)** | | | 61614 | | 60132 | 86.8% |
| **corner (4)** | | | 8701 | | 3330 | 4.8% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 5849, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 2168 | 60.2 | 1213.7 | 0.24 | 0.71 | 0.0% |
| -x | 2239 | 60.2 | 1198.1 | 0.25 | 0.75 | 0.0% |
| +y | 2168 | 60.2 | 1207.2 | 0.24 | 0.70 | 0.0% |
| -y | 2176 | 60.2 | 1196.9 | 0.24 | 0.74 | 0.0% |
| door +x+y (y wall) 0 | 1673 | 0.9 | 1318.1 | 0.40 | 1.35 | 3.8% |
| door +x+y (y wall) 1 | 1841 | 0.9 | 1450.5 | 0.40 | 1.28 | 3.4% |
| door +x+y (y wall) 2 | 1677 | 0.9 | 1448.8 | 0.36 | 1.38 | 2.7% |
| door +x+y (y wall) 3 | 1240 | 0.9 | 1469.0 | 0.26 | 1.28 | 3.4% |
| door +x+y (y wall) 4 | 915 | 0.9 | 1475.9 | 0.19 | 1.28 | 4.0% |
| door +x+y (x wall) 0 | 1680 | 0.9 | 1299.4 | 0.40 | 1.25 | 3.8% |
| door +x+y (x wall) 1 | 1823 | 0.7 | 1434.9 | 0.40 | 1.38 | 3.5% |
| door +x+y (x wall) 2 | 1668 | 0.9 | 1482.0 | 0.35 | 1.28 | 3.4% |
| door +x+y (x wall) 3 | 1263 | 0.9 | 1478.3 | 0.27 | 1.35 | 3.4% |
| door +x+y (x wall) 4 | 890 | 0.9 | 1486.2 | 0.19 | 1.28 | 4.0% |
| door +x+y (corner) | 573 | 0.9 | 1309.2 | 0.14 | 0.88 | 1.5% |
| door -x+y (y wall) 0 | 1659 | 0.7 | 1197.2 | 0.43 | 1.31 | 4.1% |
| door -x+y (y wall) 1 | 1822 | 0.7 | 1413.9 | 0.40 | 1.35 | 3.5% |
| door -x+y (y wall) 2 | 1700 | 0.9 | 1489.7 | 0.36 | 1.38 | 3.3% |
| door -x+y (y wall) 3 | 1403 | 0.7 | 1489.9 | 0.29 | 1.35 | 3.3% |
| door -x+y (y wall) 4 | 746 | 1.0 | 1480.8 | 0.16 | 1.31 | 3.4% |
| door -x+y (x wall) 0 | 1647 | 0.9 | 1154.2 | 0.45 | 1.31 | 4.3% |
| door -x+y (x wall) 1 | 1806 | 0.9 | 1411.3 | 0.40 | 1.31 | 3.5% |
| door -x+y (x wall) 2 | 1744 | 0.9 | 1480.9 | 0.37 | 1.28 | 3.4% |
| door -x+y (x wall) 3 | 1368 | 0.9 | 1484.6 | 0.29 | 1.35 | 3.4% |
| door -x+y (x wall) 4 | 670 | 0.9 | 1358.9 | 0.15 | 1.31 | 3.6% |
| door -x+y (corner) | 475 | 0.9 | 1156.5 | 0.13 | 0.91 | 0.9% |
| door -x-y (y wall) 0 | 1660 | 0.9 | 1250.9 | 0.41 | 1.38 | 4.0% |
| door -x-y (y wall) 1 | 1812 | 0.9 | 1420.6 | 0.40 | 1.28 | 3.5% |
| door -x-y (y wall) 2 | 1664 | 0.9 | 1438.8 | 0.36 | 1.35 | 3.4% |
| door -x-y (y wall) 3 | 1278 | 0.7 | 1473.6 | 0.27 | 1.35 | 2.7% |
| door -x-y (y wall) 4 | 870 | 0.9 | 1385.1 | 0.20 | 1.38 | 4.3% |
| door -x-y (x wall) 0 | 1665 | 0.9 | 1168.9 | 0.44 | 1.38 | 4.2% |
| door -x-y (x wall) 1 | 1810 | 1.0 | 1385.8 | 0.41 | 1.35 | 3.6% |
| door -x-y (x wall) 2 | 1651 | 0.7 | 1455.9 | 0.35 | 1.35 | 2.7% |
| door -x-y (x wall) 3 | 1285 | 0.9 | 1473.4 | 0.27 | 1.31 | 3.4% |
| door -x-y (x wall) 4 | 835 | 0.9 | 1448.8 | 0.18 | 1.31 | 3.4% |
| door -x-y (corner) | 557 | 0.7 | 1126.7 | 0.15 | 0.85 | 0.9% |
| door +x-y (y wall) 0 | 1675 | 0.9 | 1226.6 | 0.43 | 1.31 | 4.0% |
| door +x-y (y wall) 1 | 1841 | 0.9 | 1484.4 | 0.39 | 1.25 | 3.4% |
| door +x-y (y wall) 2 | 1691 | 0.9 | 1513.3 | 0.35 | 1.35 | 3.3% |
| door +x-y (y wall) 3 | 1306 | 0.9 | 1479.9 | 0.28 | 1.38 | 2.7% |
| door +x-y (y wall) 4 | 825 | 0.9 | 1410.1 | 0.18 | 1.35 | 3.5% |
| door +x-y (x wall) 0 | 1678 | 0.9 | 1275.6 | 0.41 | 1.35 | 3.9% |
| door +x-y (x wall) 1 | 1843 | 0.7 | 1492.1 | 0.39 | 1.28 | 3.3% |
| door +x-y (x wall) 2 | 1735 | 0.7 | 1493.2 | 0.36 | 1.25 | 3.3% |
| door +x-y (x wall) 3 | 1337 | 0.9 | 1490.7 | 0.28 | 1.28 | 3.3% |
| door +x-y (x wall) 4 | 749 | 1.0 | 1471.0 | 0.16 | 1.38 | 3.4% |
| door +x-y (corner) | 510 | 0.7 | 1112.4 | 0.14 | 0.85 | 1.8% |

Mean flow / w J averaged over the doors 0.31, over the avenues 0.24.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 103.1 | 2342 | 1550 / 793 / 943 | 0.2 | 1177.5 | 2.79 | 4.61 | 92% | 87% | 5% | 4.47 |
| straight +x+y (y wing) 1 | 1.20 | 81.5 | 1805 | 1731 / 0 / 152 | 0.7 | 1447.5 | 1.30 | 2.11 | 91% | 75% | 16% | 3.88 |
| straight +x+y (y wing) 2 | 1.20 | 61.0 | 1551 | 1590 / 0 / 43 | 0.7 | 1445.8 | 1.13 | 1.81 | 82% | 71% | 11% | 3.77 |
| straight +x+y (y wing) 3 | 1.20 | 39.4 | 923 | 1137 / 0 / 46 | 0.7 | 1466.1 | 0.81 | 2.51 | 47% | 38% | 9% | 3.85 |
| straight +x+y (y wing) 4 | 1.20 | 18.8 | 404 | 737 / 0 / 12 | 0.7 | 1472.9 | 0.51 | 1.91 | 18% | 17% | 1% | 3.85 |
| straight +x+y (x wing) 0 | 1.20 | 103.1 | 2393 | 1560 / 833 / 1152 | 0.5 | 1197.1 | 2.96 | 5.02 | 93% | 83% | 10% | 4.13 |
| straight +x+y (x wing) 1 | 1.20 | 81.5 | 1804 | 1711 / 0 / 154 | 0.7 | 1432.0 | 1.30 | 2.01 | 93% | 78% | 15% | 3.84 |
| straight +x+y (x wing) 2 | 1.20 | 61.0 | 1484 | 1584 / 0 / 21 | 0.7 | 1479.0 | 1.09 | 1.71 | 74% | 66% | 9% | 3.78 |
| straight +x+y (x wing) 3 | 1.20 | 39.4 | 937 | 1154 / 0 / 16 | 0.7 | 1475.3 | 0.79 | 1.71 | 49% | 41% | 8% | 3.61 |
| straight +x+y (x wing) 4 | 1.20 | 18.8 | 397 | 710 / 0 / 21 | 0.7 | 1483.2 | 0.49 | 1.60 | 19% | 16% | 3% | 3.81 |
| corner +x+y | 1.20 | 186.0 | 1826 | 445 / 332 / 1460 | 0.7 | 1459.2 | 1.53 | 3.31 | 92% | 56% | 36% | 2.60 |
| straight -x+y (y wing) 0 | 1.20 | 103.1 | 2364 | 1547 / 817 / 1172 | 0.2 | 1194.3 | 2.96 | 5.42 | 92% | 87% | 6% | 4.18 |
| straight -x+y (y wing) 1 | 1.20 | 81.5 | 1893 | 1707 / 0 / 262 | 0.7 | 1411.0 | 1.40 | 2.71 | 93% | 68% | 25% | 3.44 |
| straight -x+y (y wing) 2 | 1.20 | 61.0 | 1474 | 1582 / 0 / 13 | 0.7 | 1486.7 | 1.07 | 1.91 | 75% | 61% | 13% | 3.72 |
| straight -x+y (y wing) 3 | 1.20 | 39.4 | 953 | 1292 / 0 / 8 | 0.7 | 1486.9 | 0.87 | 1.60 | 58% | 39% | 19% | 3.26 |
| straight -x+y (y wing) 4 | 1.20 | 18.8 | 409 | 610 / 0 / 23 | 0.7 | 1477.8 | 0.43 | 1.81 | 19% | 17% | 2% | 3.88 |
| straight -x+y (x wing) 0 | 1.20 | 103.1 | 2329 | 1531 / 799 / 891 | 0.5 | 1151.2 | 2.80 | 4.81 | 92% | 88% | 4% | 4.46 |
| straight -x+y (x wing) 1 | 1.20 | 81.5 | 1838 | 1693 / 0 / 275 | 0.7 | 1408.3 | 1.40 | 2.61 | 92% | 65% | 26% | 3.59 |
| straight -x+y (x wing) 2 | 1.20 | 61.0 | 1544 | 1630 / 0 / 16 | 0.7 | 1478.0 | 1.11 | 1.71 | 79% | 66% | 12% | 3.77 |
| straight -x+y (x wing) 3 | 1.20 | 39.4 | 942 | 1279 / 0 / 3 | 0.7 | 1481.6 | 0.87 | 1.91 | 56% | 40% | 16% | 3.47 |
| straight -x+y (x wing) 4 | 1.20 | 18.8 | 398 | 513 / 0 / 27 | 0.7 | 1355.9 | 0.40 | 1.60 | 41% | 18% | 24% | 1.98 |
| corner -x+y | 1.20 | 186.0 | 1722 | 355 / 512 / 1413 | 0.7 | 1453.8 | 1.57 | 3.51 | 92% | 70% | 23% | 2.84 |
| straight -x-y (y wing) 0 | 1.20 | 103.1 | 2303 | 1539 / 766 / 893 | 0.7 | 1188.3 | 2.69 | 5.32 | 92% | 87% | 6% | 4.47 |
| straight -x-y (y wing) 1 | 1.20 | 81.5 | 1861 | 1704 / 0 / 257 | 0.7 | 1417.6 | 1.38 | 2.81 | 93% | 71% | 22% | 3.55 |
| straight -x-y (y wing) 2 | 1.20 | 61.0 | 1546 | 1586 / 0 / 36 | 0.7 | 1435.8 | 1.13 | 1.91 | 82% | 70% | 12% | 3.80 |
| straight -x-y (y wing) 3 | 1.20 | 39.4 | 933 | 1132 / 0 / 11 | 0.7 | 1470.6 | 0.78 | 1.71 | 48% | 38% | 10% | 3.69 |
| straight -x-y (y wing) 4 | 1.20 | 18.8 | 401 | 727 / 0 / 29 | 0.7 | 1382.1 | 0.55 | 2.11 | 19% | 17% | 2% | 3.89 |
| straight -x-y (x wing) 0 | 1.20 | 103.1 | 2363 | 1549 / 815 / 979 | 0.3 | 1165.9 | 2.87 | 5.12 | 92% | 88% | 4% | 4.32 |
| straight -x-y (x wing) 1 | 1.20 | 81.5 | 1868 | 1692 / 0 / 288 | 0.7 | 1382.8 | 1.43 | 2.71 | 93% | 71% | 22% | 3.47 |
| straight -x-y (x wing) 2 | 1.20 | 61.0 | 1484 | 1575 / 0 / 19 | 0.7 | 1453.0 | 1.10 | 1.71 | 77% | 66% | 10% | 3.80 |
| straight -x-y (x wing) 3 | 1.20 | 39.4 | 941 | 1168 / 0 / 10 | 0.7 | 1470.4 | 0.80 | 1.71 | 48% | 41% | 7% | 3.61 |
| straight -x-y (x wing) 4 | 1.20 | 18.8 | 397 | 683 / 0 / 22 | 0.7 | 1445.8 | 0.49 | 1.60 | 19% | 17% | 2% | 3.75 |
| corner -x-y | 1.20 | 186.0 | 1768 | 436 / 497 / 1424 | 0.7 | 1421.8 | 1.66 | 4.11 | 93% | 66% | 27% | 2.65 |
| straight +x-y (y wing) 0 | 1.20 | 103.1 | 2406 | 1561 / 845 / 1164 | 0.5 | 1222.4 | 2.92 | 4.71 | 93% | 81% | 11% | 4.00 |
| straight +x-y (y wing) 1 | 1.20 | 81.5 | 1813 | 1723 / 0 / 149 | 0.7 | 1481.5 | 1.26 | 2.11 | 88% | 73% | 15% | 3.84 |
| straight +x-y (y wing) 2 | 1.20 | 61.0 | 1480 | 1602 / 0 / 12 | 0.7 | 1510.3 | 1.07 | 1.81 | 73% | 63% | 10% | 3.85 |
| straight +x-y (y wing) 3 | 1.20 | 39.4 | 944 | 1178 / 0 / 6 | 0.7 | 1476.9 | 0.80 | 1.71 | 46% | 38% | 8% | 3.71 |
| straight +x-y (y wing) 4 | 1.20 | 18.8 | 401 | 681 / 0 / 25 | 0.7 | 1407.1 | 0.50 | 1.81 | 19% | 17% | 2% | 3.76 |
| straight +x-y (x wing) 0 | 1.20 | 103.1 | 2350 | 1560 / 791 / 906 | 0.3 | 1199.3 | 2.72 | 5.22 | 92% | 87% | 5% | 4.22 |
| straight +x-y (x wing) 1 | 1.20 | 81.5 | 1824 | 1726 / 0 / 176 | 0.7 | 1489.2 | 1.28 | 2.11 | 90% | 72% | 18% | 3.74 |
| straight +x-y (x wing) 2 | 1.20 | 61.0 | 1541 | 1628 / 0 / 13 | 0.7 | 1490.2 | 1.10 | 1.81 | 78% | 67% | 11% | 3.69 |
| straight +x-y (x wing) 3 | 1.20 | 39.4 | 928 | 1202 / 0 / 6 | 0.7 | 1487.8 | 0.81 | 1.71 | 46% | 39% | 7% | 3.71 |
| straight +x-y (x wing) 4 | 1.20 | 18.8 | 411 | 615 / 0 / 23 | 0.7 | 1468.0 | 0.43 | 1.81 | 23% | 17% | 6% | 3.27 |
| corner +x-y | 1.20 | 186.0 | 1767 | 388 / 366 / 1385 | 0.7 | 1444.0 | 1.48 | 3.51 | 94% | 66% | 29% | 2.73 |

The last agent out (agent 56270, t100 1513.3 s): last gangway straight +x-y (y wing) 2, exit door +x-y (y wall) 2. The gangway that cleared last: straight +x-y (y wing) 2 at 1510.3 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 8804 | 7800.4 | 7.08 | 1488.6 / 1416.6 / 1365.3 | 1420.6 / 1397.9 / 1334.7 | 7283571.6 | 13883593 | 0.166 |
| gangway | 3792 | 3512.9 | 7.08 | 1487.2 / 1416.4 / 1363.4 | 1420.6 / 1397.9 / 1334.7 | 7255950.1 | 12924810 | 0.101 |
| walkway | 276 | 257.4 | 5.30 | 835.7 / 510.2 / 19.6 | 507.9 / 249.8 / 11.0 | 186.6 | 92368 | 0.662 |
| avenue | 1920 | 1801.4 | 2.98 | 867.7 / 25.7 / 0.0 | 676.4 / 1.7 / 0.0 | 0.0 | 524480 | 1.334 |
| exit | 4 | 2.0 | 0.00 | 0.9 / 0.5 / 0.0 | 0.7 / 0.5 / 0.0 | 0.0 | 4 | 0.869 |
| concourse | 2812 | 2226.8 | 6.02 | 1437.7 / 74.5 / 50.2 | 1065.5 / 72.8 / 42.7 | 27435.0 | 341931 | 0.710 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 25392 | 16030.4 | 7.86 | 1364.6 / 1363.4 / 1330.0 | 1364.6 / 1363.4 / 1321.8 | 9291401.1 | 22802459 | 0.022 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 208 x 208 from (-104, -104) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 35.5 | -35.5 | gangway | 1.00 | 5.83 | 1401.4 | 1397.9 | 1321.1 | 7601.4 | 0.006 |
| 2 | 34.5 | -34.5 | gangway | 1.00 | 6.01 | 1392.6 | 1382.3 | 1334.7 | 7562.9 | 0.006 |
| 3 | -36.5 | 36.5 | gangway | 1.00 | 5.76 | 1386.1 | 1383.3 | 1312.5 | 7325.5 | 0.007 |
| 4 | -34.5 | -34.5 | gangway | 1.00 | 5.87 | 1346.1 | 1335.4 | 1259.9 | 7269.6 | 0.006 |
| 5 | -35.5 | -35.5 | gangway | 1.00 | 5.88 | 1357.8 | 1348.2 | 1298.9 | 7267.9 | 0.009 |
| 6 | 34.5 | 34.5 | gangway | 1.00 | 5.63 | 1366.0 | 1352.0 | 1313.9 | 7129.6 | 0.008 |
| 7 | 36.5 | -36.5 | gangway | 1.00 | 5.60 | 1403.8 | 1397.0 | 1308.7 | 7109.6 | 0.007 |
| 8 | 36.5 | 36.5 | gangway | 1.00 | 5.71 | 1377.6 | 1367.6 | 1256.5 | 7046.2 | 0.011 |
| 9 | 33.5 | 33.5 | gangway | 0.99 | 5.60 | 1356.1 | 1350.3 | 1300.8 | 6968.5 | 0.005 |
| 10 | 38.5 | -38.5 | gangway | 1.00 | 5.81 | 1412.2 | 1387.2 | 1213.5 | 6897.7 | 0.015 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 36.5 | -38.5 | seat row | 0.50 | 7.31 | 1364.6 | 1363.4 | 1321.1 | 4674.6 | 0.006 |
| 2 | 38.5 | -36.5 | seat row | 0.50 | 7.23 | 1347.3 | 1343.1 | 1321.8 | 4665.6 | 0.004 |
| 3 | -36.5 | -38.5 | seat row | 0.50 | 7.32 | 1316.5 | 1313.5 | 1296.4 | 4645.6 | 0.004 |
| 4 | 25.5 | -42.5 | seat row | 0.64 | 6.98 | 1140.0 | 1135.3 | 1120.6 | 4643.9 | 0.010 |
| 5 | 42.5 | 25.5 | seat row | 0.64 | 6.89 | 1126.0 | 1119.1 | 1100.2 | 4606.0 | 0.009 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 8422; agent-steps of seated agents on another row's clearway: 775428.

## Deposit check

Person-seconds deposited: 36692332.6, of them in excluded cells: 6280.258.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 9161028 overlapping pair-steps: p99 0.0020, max 0.0834 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0020 max 0.0834; venue-geometry 14: p99 0.0042 max 0.0042 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00764 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 65 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.60 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 3820 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
