# Experiment `L_load150_s8`

**Task 5.11 stage 1 (gridlock robustness, default model, AMD 26.10.1): venue L, the achievable maximum 109.28% (150% requested, seed 8)**

Venue L (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (4000 x 4000), cache key a2f3aaf59c2252b7, content hash 022d17b202313d70). 69311 agents (load 109.3%, requested 150%): every one of the 63424 seats and 5887 standing (spawnOvercrowdedCrowd, seed 8; below), buffer N = 131072, 8613 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 12253997 evaluations, 669588 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.09)** (the L venue's design capacity 63424, jam capacity 171923: 23822.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `15aa31e8667e4a9417fde7884d907d1832c5e2d6`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-23T18:43:35, 1261.0 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Spawn (overcrowding)

| | |
|---|---|
| seated | 63424 (every seat) |
| standing | **5887** (requested round((1.50 - 1) x 63424) = 31712; at most 5887 = floor(2.5 p/m^2 x 2355.0 m^2)) |
| standing floor | walkway + rear concourse, 2355.0 m^2 |
| standing on the walkway / concourse / gangways | 639 / 5248 / 0 |
| **load** | **109.28%** of the seats (requested 150%; the floor takes no more: the achievable maximum) |
| standing crowd's mean density | 2.500 p/m^2 |
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 4.06, all circulation cells 4.06 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 8, 347505 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 2779 | 486.1 |
| t90 | 6163 | 1078.0 |
| t100 | 8613 | 1506.5 |

t_p: the step by which ceil(p x 69311) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 2220 | 92 | 60.2 | 1192.0 | 20.8 | 64.9 | 60.0-70.0 |
| -x | 5.66 | 2200 | 91 | 60.2 | 1228.4 | 20.0 | 61.7 | 59.6-69.6 |
| +y | 5.66 | 2169 | 92 | 60.2 | 1209.0 | 20.0 | 65.9 | 59.6-69.6 |
| -y | 5.66 | 2113 | 80 | 60.2 | 1190.4 | 19.8 | 57.4 | 60.0-70.0 |
| door +x+y (y wall) 0 | 2.30 | 1659 | 2723 | 0.9 | 1176.1 | 36.8 | 109.9 | 34.1-44.1 |
| door +x+y (y wall) 1 | 2.30 | 1818 | 2253 | 0.9 | 1434.9 | 33.1 | 112.5 | 34.8-44.8 |
| door +x+y (y wall) 2 | 2.30 | 1683 | 1707 | 0.9 | 1451.9 | 30.3 | 109.9 | 16.6-26.6 |
| door +x+y (y wall) 3 | 2.30 | 1296 | 1161 | 0.9 | 1473.4 | 23.0 | 117.7 | 22.7-32.7 |
| door +x+y (y wall) 4 | 2.30 | 777 | 638 | 0.7 | 1456.3 | 13.9 | 104.7 | 24.0-33.9 |
| door +x+y (x wall) 0 | 2.30 | 1651 | 2731 | 0.9 | 1161.4 | 37.1 | 112.5 | 17.7-27.6 |
| door +x+y (x wall) 1 | 2.30 | 1817 | 2255 | 0.9 | 1427.8 | 33.2 | 104.7 | 9.8-19.8 |
| door +x+y (x wall) 2 | 2.30 | 1695 | 1710 | 1.0 | 1449.6 | 30.5 | 112.5 | 22.4-32.4 |
| door +x+y (x wall) 3 | 2.30 | 1360 | 1160 | 0.7 | 1471.5 | 24.1 | 115.1 | 34.3-44.3 |
| door +x+y (x wall) 4 | 2.30 | 755 | 643 | 0.7 | 1392.1 | 14.2 | 112.5 | 11.5-21.5 |
| door +x+y (corner) | 2.30 | 514 | 244 | 0.7 | 944.1 | 14.2 | 70.6 | 51.4-61.4 |
| door -x+y (y wall) 0 | 2.30 | 1660 | 2727 | 0.7 | 1247.4 | 34.7 | 107.3 | 11.5-21.5 |
| door -x+y (y wall) 1 | 2.30 | 1836 | 2255 | 0.9 | 1485.0 | 32.3 | 109.9 | 11.9-21.9 |
| door -x+y (y wall) 2 | 2.30 | 1710 | 1708 | 0.7 | 1504.9 | 29.7 | 115.1 | 20.5-30.4 |
| door -x+y (y wall) 3 | 2.30 | 1207 | 1158 | 1.0 | 1506.5 | 20.9 | 117.7 | 14.7-24.7 |
| door -x+y (y wall) 4 | 2.30 | 856 | 647 | 0.9 | 1436.9 | 15.5 | 117.7 | 12.2-22.2 |
| door -x+y (x wall) 0 | 2.30 | 1696 | 2728 | 0.9 | 1239.9 | 35.7 | 107.3 | 13.8-23.8 |
| door -x+y (x wall) 1 | 2.30 | 1817 | 2256 | 0.7 | 1461.2 | 32.5 | 104.7 | 18.0-28.0 |
| door -x+y (x wall) 2 | 2.30 | 1680 | 1709 | 1.0 | 1484.6 | 29.5 | 109.9 | 12.6-22.6 |
| door -x+y (x wall) 3 | 2.30 | 1298 | 1156 | 0.9 | 1450.7 | 23.4 | 109.9 | 10.5-20.5 |
| door -x+y (x wall) 4 | 2.30 | 829 | 644 | 0.9 | 1417.6 | 15.3 | 112.5 | 22.6-32.5 |
| door -x+y (corner) | 2.30 | 560 | 253 | 0.7 | 1025.7 | 14.3 | 73.3 | 35.9-45.8 |
| door -x-y (y wall) 0 | 2.30 | 1658 | 2738 | 0.7 | 1283.3 | 33.7 | 107.3 | 28.0-38.0 |
| door -x-y (y wall) 1 | 2.30 | 1856 | 2252 | 0.7 | 1490.9 | 32.5 | 117.7 | 3.1-13.1 |
| door -x-y (y wall) 2 | 2.30 | 1654 | 1711 | 0.7 | 1479.9 | 29.2 | 104.7 | 37.3-47.2 |
| door -x-y (y wall) 3 | 2.30 | 1293 | 1160 | 0.7 | 1478.5 | 22.8 | 107.3 | 28.5-38.5 |
| door -x-y (y wall) 4 | 2.30 | 905 | 641 | 0.7 | 1471.5 | 16.0 | 115.1 | 7.2-17.1 |
| door -x-y (x wall) 0 | 2.30 | 1682 | 2737 | 0.7 | 1283.5 | 34.2 | 112.5 | 5.6-15.6 |
| door -x-y (x wall) 1 | 2.30 | 1826 | 2255 | 0.9 | 1461.3 | 32.6 | 107.3 | 21.3-31.3 |
| door -x-y (x wall) 2 | 2.30 | 1655 | 1705 | 0.9 | 1470.1 | 29.4 | 109.9 | 27.8-37.8 |
| door -x-y (x wall) 3 | 2.30 | 1226 | 1159 | 0.9 | 1462.2 | 21.9 | 109.9 | 10.3-20.3 |
| door -x-y (x wall) 4 | 2.30 | 891 | 638 | 0.7 | 1423.0 | 16.3 | 107.3 | 35.2-45.1 |
| door -x-y (corner) | 2.30 | 585 | 248 | 0.9 | 1163.0 | 13.1 | 70.6 | 34.3-44.3 |
| door +x-y (y wall) 0 | 2.30 | 1663 | 2728 | 0.9 | 1263.2 | 34.4 | 115.1 | 13.8-23.8 |
| door +x-y (y wall) 1 | 2.30 | 1838 | 2259 | 1.0 | 1459.9 | 32.9 | 115.1 | 0.9-10.8 |
| door +x-y (y wall) 2 | 2.30 | 1629 | 1714 | 0.7 | 1445.8 | 29.4 | 117.7 | 8.9-18.9 |
| door +x-y (y wall) 3 | 2.30 | 1257 | 1161 | 0.7 | 1473.9 | 22.3 | 112.5 | 27.8-37.8 |
| door +x-y (y wall) 4 | 2.30 | 896 | 642 | 0.9 | 1393.0 | 16.8 | 112.5 | 11.7-21.7 |
| door +x-y (x wall) 0 | 2.30 | 1686 | 2725 | 0.7 | 1267.9 | 34.7 | 109.9 | 4.9-14.9 |
| door +x-y (x wall) 1 | 2.30 | 1818 | 2251 | 1.2 | 1441.4 | 32.9 | 109.9 | 11.7-21.7 |
| door +x-y (x wall) 2 | 2.30 | 1644 | 1710 | 0.9 | 1460.1 | 29.4 | 115.1 | 1.4-11.4 |
| door +x-y (x wall) 3 | 2.30 | 1264 | 1166 | 0.9 | 1471.5 | 22.4 | 115.1 | 28.2-38.1 |
| door +x-y (x wall) 4 | 2.30 | 887 | 634 | 1.0 | 1345.2 | 17.2 | 112.5 | 27.6-37.6 |
| door +x-y (corner) | 2.30 | 622 | 256 | 0.9 | 1230.8 | 13.2 | 70.6 | 0.7-10.7 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (2.30 m; a corner door's: the gap between its wall ends, 2.30 m); agents are removed past the outer wall's outer face (92.71 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 2220 | 3.2% | 18.7% |
| -x | avenue | 5.66 | 2200 | 3.2% | 18.5% |
| +y | avenue | 5.66 | 2169 | 3.1% | 18.3% |
| -y | avenue | 5.66 | 2113 | 3.0% | 17.8% |
| door +x+y (y wall) 0 | door | 2.30 | 1659 | 2.4% | 34.4% |
| door +x+y (y wall) 1 | door | 2.30 | 1818 | 2.6% | 37.7% |
| door +x+y (y wall) 2 | door | 2.30 | 1683 | 2.4% | 34.9% |
| door +x+y (y wall) 3 | door | 2.30 | 1296 | 1.9% | 26.8% |
| door +x+y (y wall) 4 | door | 2.30 | 777 | 1.1% | 16.1% |
| door +x+y (x wall) 0 | door | 2.30 | 1651 | 2.4% | 34.2% |
| door +x+y (x wall) 1 | door | 2.30 | 1817 | 2.6% | 37.6% |
| door +x+y (x wall) 2 | door | 2.30 | 1695 | 2.4% | 35.1% |
| door +x+y (x wall) 3 | door | 2.30 | 1360 | 2.0% | 28.2% |
| door +x+y (x wall) 4 | door | 2.30 | 755 | 1.1% | 15.6% |
| door +x+y (corner) | door | 2.30 | 514 | 0.7% | 10.6% |
| door -x+y (y wall) 0 | door | 2.30 | 1660 | 2.4% | 34.4% |
| door -x+y (y wall) 1 | door | 2.30 | 1836 | 2.6% | 38.0% |
| door -x+y (y wall) 2 | door | 2.30 | 1710 | 2.5% | 35.4% |
| door -x+y (y wall) 3 | door | 2.30 | 1207 | 1.7% | 25.0% |
| door -x+y (y wall) 4 | door | 2.30 | 856 | 1.2% | 17.7% |
| door -x+y (x wall) 0 | door | 2.30 | 1696 | 2.4% | 35.1% |
| door -x+y (x wall) 1 | door | 2.30 | 1817 | 2.6% | 37.6% |
| door -x+y (x wall) 2 | door | 2.30 | 1680 | 2.4% | 34.8% |
| door -x+y (x wall) 3 | door | 2.30 | 1298 | 1.9% | 26.9% |
| door -x+y (x wall) 4 | door | 2.30 | 829 | 1.2% | 17.2% |
| door -x+y (corner) | door | 2.30 | 560 | 0.8% | 11.6% |
| door -x-y (y wall) 0 | door | 2.30 | 1658 | 2.4% | 34.3% |
| door -x-y (y wall) 1 | door | 2.30 | 1856 | 2.7% | 38.4% |
| door -x-y (y wall) 2 | door | 2.30 | 1654 | 2.4% | 34.3% |
| door -x-y (y wall) 3 | door | 2.30 | 1293 | 1.9% | 26.8% |
| door -x-y (y wall) 4 | door | 2.30 | 905 | 1.3% | 18.7% |
| door -x-y (x wall) 0 | door | 2.30 | 1682 | 2.4% | 34.8% |
| door -x-y (x wall) 1 | door | 2.30 | 1826 | 2.6% | 37.8% |
| door -x-y (x wall) 2 | door | 2.30 | 1655 | 2.4% | 34.3% |
| door -x-y (x wall) 3 | door | 2.30 | 1226 | 1.8% | 25.4% |
| door -x-y (x wall) 4 | door | 2.30 | 891 | 1.3% | 18.5% |
| door -x-y (corner) | door | 2.30 | 585 | 0.8% | 12.1% |
| door +x-y (y wall) 0 | door | 2.30 | 1663 | 2.4% | 34.4% |
| door +x-y (y wall) 1 | door | 2.30 | 1838 | 2.7% | 38.1% |
| door +x-y (y wall) 2 | door | 2.30 | 1629 | 2.4% | 33.7% |
| door +x-y (y wall) 3 | door | 2.30 | 1257 | 1.8% | 26.0% |
| door +x-y (y wall) 4 | door | 2.30 | 896 | 1.3% | 18.6% |
| door +x-y (x wall) 0 | door | 2.30 | 1686 | 2.4% | 34.9% |
| door +x-y (x wall) 1 | door | 2.30 | 1818 | 2.6% | 37.7% |
| door +x-y (x wall) 2 | door | 2.30 | 1644 | 2.4% | 34.1% |
| door +x-y (x wall) 3 | door | 2.30 | 1264 | 1.8% | 26.2% |
| door +x-y (x wall) 4 | door | 2.30 | 887 | 1.3% | 18.4% |
| door +x-y (corner) | door | 2.30 | 622 | 0.9% | 12.9% |
| **doors (44)** | door | 101.20 | 60609 | 87.4% | |
| **avenues (4)** | avenue | 22.64 | 8702 | 12.6% | |

**Unused exit width: 0.0 of 123.8 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 1506.5 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 26.7%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 2338 | 3.4% | 2338 | 3.4% |
| straight +x+y (y wing) 1 | straight | yes | 1927 | 2.8% | 1702 | 2.5% |
| straight +x+y (y wing) 2 | straight | yes | 1585 | 2.3% | 1575 | 2.3% |
| straight +x+y (y wing) 3 | straight | yes | 1215 | 1.8% | 1213 | 1.8% |
| straight +x+y (y wing) 4 | straight | yes | 629 | 0.9% | 614 | 0.9% |
| straight +x+y (x wing) 0 | straight | yes | 2323 | 3.4% | 2323 | 3.4% |
| straight +x+y (x wing) 1 | straight | yes | 1901 | 2.7% | 1699 | 2.5% |
| straight +x+y (x wing) 2 | straight | yes | 1604 | 2.3% | 1594 | 2.3% |
| straight +x+y (x wing) 3 | straight | yes | 1239 | 1.8% | 1235 | 1.8% |
| straight +x+y (x wing) 4 | straight | yes | 636 | 0.9% | 620 | 0.9% |
| corner +x+y | corner | yes | 2259 | 3.3% | 952 | 1.4% |
| straight -x+y (y wing) 0 | straight | yes | 2361 | 3.4% | 2361 | 3.4% |
| straight -x+y (y wing) 1 | straight | yes | 1858 | 2.7% | 1725 | 2.5% |
| straight -x+y (y wing) 2 | straight | yes | 1635 | 2.4% | 1611 | 2.3% |
| straight -x+y (y wing) 3 | straight | yes | 1144 | 1.7% | 1134 | 1.6% |
| straight -x+y (y wing) 4 | straight | yes | 682 | 1.0% | 667 | 1.0% |
| straight -x+y (x wing) 0 | straight | yes | 2379 | 3.4% | 2379 | 3.4% |
| straight -x+y (x wing) 1 | straight | yes | 1855 | 2.7% | 1705 | 2.5% |
| straight -x+y (x wing) 2 | straight | yes | 1590 | 2.3% | 1578 | 2.3% |
| straight -x+y (x wing) 3 | straight | yes | 1186 | 1.7% | 1178 | 1.7% |
| straight -x+y (x wing) 4 | straight | yes | 709 | 1.0% | 694 | 1.0% |
| corner -x+y | corner | yes | 2151 | 3.1% | 834 | 1.2% |
| straight -x-y (y wing) 0 | straight | yes | 2320 | 3.3% | 2320 | 3.3% |
| straight -x-y (y wing) 1 | straight | yes | 1846 | 2.7% | 1744 | 2.5% |
| straight -x-y (y wing) 2 | straight | yes | 1617 | 2.3% | 1581 | 2.3% |
| straight -x-y (y wing) 3 | straight | yes | 1182 | 1.7% | 1168 | 1.7% |
| straight -x-y (y wing) 4 | straight | yes | 759 | 1.1% | 743 | 1.1% |
| straight -x-y (x wing) 0 | straight | yes | 2375 | 3.4% | 2375 | 3.4% |
| straight -x-y (x wing) 1 | straight | yes | 1820 | 2.6% | 1715 | 2.5% |
| straight -x-y (x wing) 2 | straight | yes | 1597 | 2.3% | 1572 | 2.3% |
| straight -x-y (x wing) 3 | straight | yes | 1139 | 1.6% | 1120 | 1.6% |
| straight -x-y (x wing) 4 | straight | yes | 744 | 1.1% | 730 | 1.1% |
| corner -x-y | corner | yes | 2162 | 3.1% | 797 | 1.1% |
| straight +x-y (y wing) 0 | straight | yes | 2352 | 3.4% | 2352 | 3.4% |
| straight +x-y (y wing) 1 | straight | yes | 1832 | 2.6% | 1719 | 2.5% |
| straight +x-y (y wing) 2 | straight | yes | 1611 | 2.3% | 1576 | 2.3% |
| straight +x-y (y wing) 3 | straight | yes | 1124 | 1.6% | 1110 | 1.6% |
| straight +x-y (y wing) 4 | straight | yes | 752 | 1.1% | 731 | 1.1% |
| straight +x-y (x wing) 0 | straight | yes | 2378 | 3.4% | 2378 | 3.4% |
| straight +x-y (x wing) 1 | straight | yes | 1836 | 2.6% | 1711 | 2.5% |
| straight +x-y (x wing) 2 | straight | yes | 1580 | 2.3% | 1560 | 2.3% |
| straight +x-y (x wing) 3 | straight | yes | 1181 | 1.7% | 1164 | 1.7% |
| straight +x-y (x wing) 4 | straight | yes | 732 | 1.1% | 713 | 1.0% |
| corner +x-y | corner | yes | 2195 | 3.2% | 853 | 1.2% |
| **straight (40)** | | | 61573 | | 60027 | 86.6% |
| **corner (4)** | | | 8767 | | 3436 | 5.0% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 5848, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 2220 | 60.2 | 1192.0 | 0.25 | 0.78 | 0.0% |
| -x | 2200 | 60.2 | 1228.4 | 0.24 | 0.74 | 0.0% |
| +y | 2169 | 60.2 | 1209.0 | 0.24 | 0.79 | 0.0% |
| -y | 2113 | 60.2 | 1190.4 | 0.24 | 0.69 | 0.0% |
| door +x+y (y wall) 0 | 1659 | 0.9 | 1176.1 | 0.44 | 1.31 | 4.2% |
| door +x+y (y wall) 1 | 1818 | 0.9 | 1434.9 | 0.40 | 1.35 | 3.5% |
| door +x+y (y wall) 2 | 1683 | 0.9 | 1451.9 | 0.36 | 1.31 | 3.4% |
| door +x+y (y wall) 3 | 1296 | 0.9 | 1473.4 | 0.27 | 1.41 | 3.4% |
| door +x+y (y wall) 4 | 777 | 0.7 | 1456.3 | 0.17 | 1.25 | 3.4% |
| door +x+y (x wall) 0 | 1651 | 0.9 | 1161.4 | 0.44 | 1.35 | 4.3% |
| door +x+y (x wall) 1 | 1817 | 0.9 | 1427.8 | 0.40 | 1.25 | 3.5% |
| door +x+y (x wall) 2 | 1695 | 1.0 | 1449.6 | 0.37 | 1.35 | 3.4% |
| door +x+y (x wall) 3 | 1360 | 0.7 | 1471.5 | 0.29 | 1.38 | 3.4% |
| door +x+y (x wall) 4 | 755 | 0.7 | 1392.1 | 0.17 | 1.35 | 3.6% |
| door +x+y (corner) | 514 | 0.7 | 944.1 | 0.17 | 0.85 | 0.0% |
| door -x+y (y wall) 0 | 1660 | 0.7 | 1247.4 | 0.42 | 1.28 | 4.0% |
| door -x+y (y wall) 1 | 1836 | 0.9 | 1485.0 | 0.39 | 1.31 | 3.4% |
| door -x+y (y wall) 2 | 1710 | 0.7 | 1504.9 | 0.35 | 1.38 | 2.6% |
| door -x+y (y wall) 3 | 1207 | 1.0 | 1506.5 | 0.25 | 1.41 | 3.3% |
| door -x+y (y wall) 4 | 856 | 0.9 | 1436.9 | 0.19 | 1.41 | 3.4% |
| door -x+y (x wall) 0 | 1696 | 0.9 | 1239.9 | 0.43 | 1.28 | 4.0% |
| door -x+y (x wall) 1 | 1817 | 0.7 | 1461.2 | 0.39 | 1.25 | 3.4% |
| door -x+y (x wall) 2 | 1680 | 1.0 | 1484.6 | 0.35 | 1.31 | 3.4% |
| door -x+y (x wall) 3 | 1298 | 0.9 | 1450.7 | 0.28 | 1.31 | 3.4% |
| door -x+y (x wall) 4 | 829 | 0.9 | 1417.6 | 0.18 | 1.35 | 3.5% |
| door -x+y (corner) | 560 | 0.7 | 1025.7 | 0.17 | 0.88 | 2.9% |
| door -x-y (y wall) 0 | 1658 | 0.7 | 1283.3 | 0.40 | 1.28 | 3.9% |
| door -x-y (y wall) 1 | 1856 | 0.7 | 1490.9 | 0.39 | 1.41 | 3.3% |
| door -x-y (y wall) 2 | 1654 | 0.7 | 1479.9 | 0.35 | 1.25 | 3.4% |
| door -x-y (y wall) 3 | 1293 | 0.7 | 1478.5 | 0.27 | 1.28 | 3.4% |
| door -x-y (y wall) 4 | 905 | 0.7 | 1471.5 | 0.19 | 1.38 | 4.1% |
| door -x-y (x wall) 0 | 1682 | 0.7 | 1283.5 | 0.41 | 1.35 | 3.9% |
| door -x-y (x wall) 1 | 1826 | 0.9 | 1461.3 | 0.39 | 1.28 | 3.4% |
| door -x-y (x wall) 2 | 1655 | 0.9 | 1470.1 | 0.35 | 1.31 | 2.7% |
| door -x-y (x wall) 3 | 1226 | 0.9 | 1462.2 | 0.26 | 1.31 | 2.7% |
| door -x-y (x wall) 4 | 891 | 0.7 | 1423.0 | 0.20 | 1.28 | 4.2% |
| door -x-y (corner) | 585 | 0.9 | 1163.0 | 0.16 | 0.85 | 0.9% |
| door +x-y (y wall) 0 | 1663 | 0.9 | 1263.2 | 0.41 | 1.38 | 3.9% |
| door +x-y (y wall) 1 | 1838 | 1.0 | 1459.9 | 0.39 | 1.38 | 3.4% |
| door +x-y (y wall) 2 | 1629 | 0.7 | 1445.8 | 0.35 | 1.41 | 3.4% |
| door +x-y (y wall) 3 | 1257 | 0.7 | 1473.9 | 0.27 | 1.35 | 3.4% |
| door +x-y (y wall) 4 | 896 | 0.9 | 1393.0 | 0.20 | 1.35 | 3.6% |
| door +x-y (x wall) 0 | 1686 | 0.7 | 1267.9 | 0.42 | 1.31 | 3.9% |
| door +x-y (x wall) 1 | 1818 | 1.2 | 1441.4 | 0.39 | 1.31 | 3.4% |
| door +x-y (x wall) 2 | 1644 | 0.9 | 1460.1 | 0.35 | 1.38 | 3.4% |
| door +x-y (x wall) 3 | 1264 | 0.9 | 1471.5 | 0.27 | 1.38 | 3.4% |
| door +x-y (x wall) 4 | 887 | 1.0 | 1345.2 | 0.21 | 1.35 | 3.7% |
| door +x-y (corner) | 622 | 0.9 | 1230.8 | 0.16 | 0.85 | 1.6% |

Mean flow / w J averaged over the doors 0.31, over the avenues 0.24.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 103.1 | 2338 | 1544 / 796 / 920 | 0.2 | 1173.1 | 2.78 | 4.71 | 92% | 88% | 4% | 4.47 |
| straight +x+y (y wing) 1 | 1.20 | 81.5 | 1909 | 1702 / 0 / 296 | 0.7 | 1432.0 | 1.40 | 2.61 | 92% | 65% | 27% | 3.39 |
| straight +x+y (y wing) 2 | 1.20 | 61.0 | 1470 | 1575 / 0 / 14 | 0.7 | 1448.9 | 1.10 | 1.71 | 77% | 64% | 13% | 3.81 |
| straight +x+y (y wing) 3 | 1.20 | 39.4 | 945 | 1213 / 0 / 72 | 0.7 | 1470.4 | 0.87 | 2.41 | 53% | 41% | 12% | 3.60 |
| straight +x+y (y wing) 4 | 1.20 | 18.8 | 396 | 614 / 0 / 33 | 0.7 | 1453.3 | 0.45 | 1.60 | 18% | 16% | 1% | 3.86 |
| straight +x+y (x wing) 0 | 1.20 | 103.1 | 2323 | 1531 / 794 / 1047 | 0.5 | 1158.4 | 2.91 | 4.91 | 91% | 88% | 3% | 4.43 |
| straight +x+y (x wing) 1 | 1.20 | 81.5 | 1870 | 1699 / 0 / 283 | 0.7 | 1424.8 | 1.39 | 2.81 | 92% | 64% | 29% | 3.31 |
| straight +x+y (x wing) 2 | 1.20 | 61.0 | 1532 | 1594 / 0 / 13 | 0.7 | 1446.7 | 1.11 | 1.60 | 81% | 66% | 14% | 3.71 |
| straight +x+y (x wing) 3 | 1.20 | 39.4 | 935 | 1235 / 0 / 7 | 0.7 | 1468.5 | 0.85 | 1.71 | 46% | 39% | 7% | 3.66 |
| straight +x+y (x wing) 4 | 1.20 | 18.8 | 396 | 620 / 0 / 21 | 0.7 | 1389.1 | 0.46 | 1.71 | 19% | 16% | 3% | 3.78 |
| corner +x+y | 1.20 | 186.0 | 1751 | 394 / 558 / 1445 | 0.7 | 1429.3 | 1.68 | 3.91 | 92% | 63% | 28% | 2.74 |
| straight -x+y (y wing) 0 | 1.20 | 103.1 | 2361 | 1536 / 825 / 1129 | 0.2 | 1167.2 | 2.99 | 5.22 | 92% | 85% | 7% | 4.18 |
| straight -x+y (y wing) 1 | 1.20 | 81.5 | 1821 | 1725 / 0 / 191 | 0.7 | 1482.0 | 1.29 | 2.31 | 91% | 72% | 19% | 3.64 |
| straight -x+y (y wing) 2 | 1.20 | 61.0 | 1540 | 1611 / 0 / 31 | 0.7 | 1501.9 | 1.09 | 1.71 | 77% | 68% | 9% | 3.76 |
| straight -x+y (y wing) 3 | 1.20 | 39.4 | 928 | 1134 / 0 / 14 | 0.7 | 1503.5 | 0.76 | 1.71 | 48% | 39% | 9% | 3.53 |
| straight -x+y (y wing) 4 | 1.20 | 18.8 | 399 | 667 / 0 / 30 | 0.7 | 1433.9 | 0.49 | 1.91 | 19% | 17% | 2% | 3.94 |
| straight -x+y (x wing) 0 | 1.20 | 103.1 | 2379 | 1576 / 805 / 978 | 0.2 | 1189.7 | 2.82 | 5.02 | 92% | 89% | 2% | 4.43 |
| straight -x+y (x wing) 1 | 1.20 | 81.5 | 1840 | 1705 / 0 / 194 | 0.7 | 1458.2 | 1.30 | 2.31 | 93% | 70% | 22% | 3.61 |
| straight -x+y (x wing) 2 | 1.20 | 61.0 | 1487 | 1578 / 0 / 15 | 0.7 | 1481.6 | 1.08 | 1.71 | 77% | 64% | 12% | 3.75 |
| straight -x+y (x wing) 3 | 1.20 | 39.4 | 936 | 1178 / 0 / 9 | 0.7 | 1447.7 | 0.82 | 1.71 | 50% | 40% | 10% | 3.68 |
| straight -x+y (x wing) 4 | 1.20 | 18.8 | 406 | 694 / 0 / 31 | 0.7 | 1414.6 | 0.51 | 2.01 | 20% | 18% | 2% | 3.71 |
| corner -x+y | 1.20 | 186.0 | 1769 | 432 / 403 / 1396 | 0.7 | 1453.3 | 1.54 | 3.21 | 95% | 61% | 34% | 2.64 |
| straight -x-y (y wing) 0 | 1.20 | 103.1 | 2320 | 1532 / 789 / 987 | 0.3 | 1180.8 | 2.80 | 5.32 | 92% | 86% | 7% | 4.40 |
| straight -x-y (y wing) 1 | 1.20 | 81.5 | 1819 | 1744 / 0 / 146 | 0.7 | 1487.9 | 1.27 | 2.31 | 89% | 75% | 15% | 3.92 |
| straight -x-y (y wing) 2 | 1.20 | 61.0 | 1538 | 1581 / 0 / 39 | 0.7 | 1476.9 | 1.10 | 1.60 | 79% | 68% | 10% | 3.80 |
| straight -x-y (y wing) 3 | 1.20 | 39.4 | 946 | 1168 / 0 / 17 | 0.7 | 1475.5 | 0.80 | 1.71 | 46% | 41% | 5% | 3.97 |
| straight -x-y (y wing) 4 | 1.20 | 18.8 | 402 | 743 / 0 / 16 | 0.7 | 1468.5 | 0.52 | 1.71 | 21% | 16% | 5% | 3.39 |
| straight -x-y (x wing) 0 | 1.20 | 103.1 | 2375 | 1555 / 820 / 993 | 0.3 | 1206.2 | 2.79 | 5.12 | 93% | 83% | 10% | 4.13 |
| straight -x-y (x wing) 1 | 1.20 | 81.5 | 1807 | 1715 / 0 / 139 | 0.7 | 1458.4 | 1.27 | 2.31 | 89% | 78% | 12% | 3.98 |
| straight -x-y (x wing) 2 | 1.20 | 61.0 | 1491 | 1572 / 0 / 31 | 0.7 | 1467.1 | 1.09 | 1.91 | 76% | 66% | 9% | 3.77 |
| straight -x-y (x wing) 3 | 1.20 | 39.4 | 950 | 1120 / 0 / 28 | 0.7 | 1459.2 | 0.79 | 1.71 | 50% | 41% | 9% | 3.65 |
| straight -x-y (x wing) 4 | 1.20 | 18.8 | 413 | 730 / 0 / 17 | 0.7 | 1420.1 | 0.53 | 1.91 | 20% | 19% | 1% | 3.89 |
| corner -x-y | 1.20 | 186.0 | 1804 | 461 / 336 / 1405 | 0.7 | 1444.6 | 1.52 | 3.81 | 93% | 60% | 33% | 2.54 |
| straight +x-y (y wing) 0 | 1.20 | 103.1 | 2352 | 1544 / 808 / 1136 | 0.5 | 1187.8 | 2.94 | 5.02 | 92% | 86% | 6% | 4.18 |
| straight +x-y (y wing) 1 | 1.20 | 81.5 | 1808 | 1719 / 0 / 182 | 0.7 | 1457.0 | 1.31 | 2.71 | 89% | 73% | 16% | 3.77 |
| straight +x-y (y wing) 2 | 1.20 | 61.0 | 1547 | 1576 / 0 / 40 | 0.7 | 1442.8 | 1.12 | 1.71 | 83% | 71% | 12% | 3.81 |
| straight +x-y (y wing) 3 | 1.20 | 39.4 | 927 | 1110 / 0 / 20 | 0.7 | 1471.0 | 0.77 | 1.71 | 47% | 37% | 10% | 3.66 |
| straight +x-y (y wing) 4 | 1.20 | 18.8 | 406 | 731 / 0 / 37 | 0.7 | 1390.0 | 0.55 | 2.11 | 23% | 19% | 4% | 3.46 |
| straight +x-y (x wing) 0 | 1.20 | 103.1 | 2378 | 1566 / 813 / 940 | 0.5 | 1203.4 | 2.76 | 4.71 | 93% | 83% | 9% | 4.14 |
| straight +x-y (x wing) 1 | 1.20 | 81.5 | 1821 | 1711 / 0 / 169 | 0.7 | 1438.4 | 1.31 | 2.41 | 90% | 77% | 13% | 3.97 |
| straight +x-y (x wing) 2 | 1.20 | 61.0 | 1470 | 1560 / 0 / 153 | 0.7 | 1457.1 | 1.18 | 2.51 | 75% | 64% | 11% | 3.77 |
| straight +x-y (x wing) 3 | 1.20 | 39.4 | 941 | 1164 / 0 / 22 | 0.7 | 1468.5 | 0.81 | 1.71 | 47% | 43% | 3% | 3.83 |
| straight +x-y (x wing) 4 | 1.20 | 18.8 | 402 | 713 / 0 / 22 | 0.7 | 1342.2 | 0.55 | 1.71 | 20% | 18% | 2% | 3.93 |
| corner +x-y | 1.20 | 186.0 | 1815 | 490 / 363 / 1551 | 0.7 | 1420.9 | 1.69 | 4.31 | 93% | 59% | 34% | 2.59 |

The last agent out (agent 16679, t100 1506.5 s): last gangway straight -x+y (y wing) 3, exit door -x+y (y wall) 3. The gangway that cleared last: straight -x+y (y wing) 3 at 1503.5 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 8804 | 7800.4 | 6.98 | 1503.3 / 1408.9 / 1355.0 | 1412.0 / 1392.4 / 1328.9 | 7204841.5 | 13792334 | 0.168 |
| gangway | 3792 | 3512.9 | 6.98 | 1501.9 / 1408.7 / 1353.4 | 1412.0 / 1392.4 / 1328.9 | 7177597.6 | 12836530 | 0.102 |
| walkway | 276 | 257.4 | 5.45 | 810.2 / 464.9 / 31.0 | 477.1 / 221.8 / 11.5 | 244.7 | 92525 | 0.657 |
| avenue | 1920 | 1801.4 | 3.27 | 837.8 / 62.8 / 0.0 | 602.9 / 2.3 / 0.0 | 0.0 | 521545 | 1.334 |
| exit | 4 | 2.0 | 0.00 | 0.7 / 0.0 / 0.0 | 0.7 / 0.0 / 0.0 | 0.0 | 3 | 0.869 |
| concourse | 2812 | 2226.8 | 5.89 | 1437.9 / 76.1 / 48.8 | 1082.0 / 74.0 / 43.7 | 26999.2 | 341731 | 0.715 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 25392 | 16030.4 | 7.86 | 1375.6 / 1364.4 / 1334.2 | 1375.6 / 1364.4 / 1329.8 | 9237642.7 | 22734453 | 0.022 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 208 x 208 from (-104, -104) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -34.5 | 34.5 | gangway | 1.00 | 5.85 | 1382.3 | 1373.7 | 1309.7 | 7488.0 | 0.006 |
| 2 | -35.5 | 35.5 | gangway | 1.00 | 5.78 | 1393.5 | 1390.9 | 1303.4 | 7363.1 | 0.006 |
| 3 | -35.5 | -35.5 | gangway | 1.00 | 5.96 | 1371.6 | 1355.4 | 1281.5 | 7301.1 | 0.009 |
| 4 | -38.5 | 38.5 | gangway | 1.00 | 5.92 | 1406.9 | 1381.1 | 1253.9 | 7259.1 | 0.014 |
| 5 | 34.5 | 34.5 | gangway | 1.00 | 5.81 | 1343.5 | 1334.9 | 1277.7 | 7101.2 | 0.005 |
| 6 | 34.5 | -34.5 | gangway | 1.00 | 5.85 | 1358.0 | 1343.6 | 1267.7 | 6994.3 | 0.008 |
| 7 | -34.5 | -34.5 | gangway | 1.00 | 5.70 | 1366.9 | 1352.7 | 1253.0 | 6987.9 | 0.007 |
| 8 | -33.5 | 33.5 | gangway | 0.99 | 5.60 | 1371.3 | 1363.4 | 1310.2 | 6957.9 | 0.005 |
| 9 | 35.5 | -35.5 | gangway | 1.00 | 5.81 | 1365.1 | 1358.7 | 1229.4 | 6860.3 | 0.008 |
| 10 | -33.5 | -33.5 | gangway | 0.99 | 5.72 | 1360.8 | 1349.2 | 1261.1 | 6847.4 | 0.005 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -36.5 | 38.5 | seat row | 0.50 | 7.19 | 1346.1 | 1344.5 | 1329.8 | 4691.1 | 0.004 |
| 2 | 36.5 | 38.5 | seat row | 0.50 | 7.40 | 1313.2 | 1305.7 | 1286.4 | 4680.3 | 0.003 |
| 3 | -42.5 | 25.5 | seat row | 0.64 | 6.86 | 1142.3 | 1140.0 | 1128.3 | 4655.4 | 0.011 |
| 4 | 42.5 | -25.5 | seat row | 0.64 | 6.79 | 1138.3 | 1130.4 | 1121.2 | 4579.5 | 0.010 |
| 5 | -35.5 | 38.5 | seat row | 0.50 | 7.08 | 1334.2 | 1324.6 | 1316.2 | 4564.6 | 0.003 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 8462; agent-steps of seated agents on another row's clearway: 851376.

## Deposit check

Person-seconds deposited: 36533077.8, of them in excluded cells: 6290.415.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 8966776 overlapping pair-steps: p99 0.0020, max 0.0933 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0020 max 0.0933; venue-geometry 14: p99 0.0013 max 0.0013 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00763 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 64 (longest 2 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.49 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 3768 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
