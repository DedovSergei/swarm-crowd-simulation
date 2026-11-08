# Experiment `L_load150_s3`

**Task 5.9 stage 4: venue L, 150% requested (seed 3): every seat + standing on the walkway and concourse (M, L: the achievable maximum, also the 125% request)**

Venue L (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (4000 x 4000), cache key a2f3aaf59c2252b7, content hash 022d17b202313d70). 69311 agents (load 109.3%, requested 150%): every one of the 63424 seats and 5887 standing (spawnOvercrowdedCrowd, seed 3; below), buffer N = 131072, 8645 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 12315101 evaluations, 678874 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.09)** (the L venue's design capacity 63424, jam capacity 171923: 23822.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-21T18:19:07, 1121.1 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Spawn (overcrowding)

| | |
|---|---|
| seated | 63424 (every seat) |
| standing | **5887** (requested round((1.50 - 1) x 63424) = 31712; at most 5887 = floor(2.5 p/m^2 x 2355.0 m^2)) |
| standing floor | walkway + rear concourse, 2355.0 m^2 |
| standing on the walkway / concourse / gangways | 626 / 5261 / 0 |
| **load** | **109.28%** of the seats (requested 150%; the floor takes no more: the achievable maximum) |
| standing crowd's mean density | 2.500 p/m^2 |
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 4.11, all circulation cells 4.11 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 3, 355962 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 2793 | 488.5 |
| t90 | 6203 | 1084.9 |
| t100 | 8645 | 1512.1 |

t_p: the step by which ceil(p x 69311) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 2164 | 88 | 60.2 | 1212.3 | 19.9 | 62.7 | 60.0-70.0 |
| -x | 5.66 | 2164 | 86 | 60.2 | 1191.1 | 20.3 | 59.5 | 59.6-69.6 |
| +y | 5.66 | 2242 | 90 | 60.2 | 1178.9 | 21.2 | 60.6 | 59.8-69.8 |
| -y | 5.66 | 2141 | 85 | 60.2 | 1195.0 | 20.0 | 58.5 | 59.6-69.6 |
| door +x+y (y wall) 0 | 2.30 | 1645 | 2734 | 0.9 | 1202.7 | 35.7 | 112.5 | 30.8-40.8 |
| door +x+y (y wall) 1 | 2.30 | 1831 | 2257 | 0.9 | 1441.4 | 33.2 | 107.3 | 39.9-49.8 |
| door +x+y (y wall) 2 | 2.30 | 1711 | 1712 | 0.7 | 1450.2 | 30.8 | 112.5 | 12.1-22.0 |
| door +x+y (y wall) 3 | 2.30 | 1261 | 1160 | 0.9 | 1476.0 | 22.3 | 112.5 | 1.2-11.2 |
| door +x+y (y wall) 4 | 2.30 | 836 | 641 | 0.9 | 1488.8 | 14.7 | 104.7 | 2.1-12.1 |
| door +x+y (x wall) 0 | 2.30 | 1688 | 2724 | 0.9 | 1216.7 | 36.2 | 109.9 | 0.9-10.8 |
| door +x+y (x wall) 1 | 2.30 | 1817 | 2246 | 0.7 | 1461.0 | 32.5 | 107.3 | 3.8-13.8 |
| door +x+y (x wall) 2 | 2.30 | 1692 | 1717 | 0.7 | 1492.8 | 29.6 | 112.5 | 17.3-27.3 |
| door +x+y (x wall) 3 | 2.30 | 1311 | 1162 | 0.9 | 1455.9 | 23.5 | 109.9 | 20.6-30.6 |
| door +x+y (x wall) 4 | 2.30 | 787 | 638 | 1.0 | 1470.1 | 14.0 | 115.1 | 15.9-25.9 |
| door +x+y (corner) | 2.30 | 542 | 248 | 0.9 | 1028.6 | 13.8 | 70.6 | 67.9-77.8 |
| door -x+y (y wall) 0 | 2.30 | 1687 | 2731 | 0.7 | 1325.4 | 33.2 | 107.3 | 23.8-33.8 |
| door -x+y (y wall) 1 | 2.30 | 1867 | 2259 | 0.9 | 1381.6 | 35.3 | 107.3 | 1.6-11.5 |
| door -x+y (y wall) 2 | 2.30 | 1794 | 1718 | 0.9 | 1457.7 | 32.1 | 104.7 | 21.0-31.0 |
| door -x+y (y wall) 3 | 2.30 | 1223 | 1162 | 0.7 | 1461.3 | 21.8 | 112.5 | 20.6-30.6 |
| door -x+y (y wall) 4 | 2.30 | 783 | 638 | 0.9 | 1504.5 | 13.6 | 115.1 | 34.3-44.3 |
| door -x+y (x wall) 0 | 2.30 | 1672 | 2725 | 0.9 | 1310.8 | 33.3 | 115.1 | 23.8-33.8 |
| door -x+y (x wall) 1 | 2.30 | 1862 | 2261 | 0.7 | 1455.2 | 33.4 | 112.5 | 5.9-15.9 |
| door -x+y (x wall) 2 | 2.30 | 1796 | 1706 | 0.9 | 1453.8 | 32.2 | 112.5 | 18.2-28.2 |
| door -x+y (x wall) 3 | 2.30 | 1221 | 1167 | 0.7 | 1500.5 | 21.2 | 109.9 | 7.2-17.1 |
| door -x+y (x wall) 4 | 2.30 | 736 | 642 | 0.9 | 1495.8 | 12.8 | 109.9 | 17.0-26.9 |
| door -x+y (corner) | 2.30 | 545 | 242 | 0.9 | 1359.4 | 10.5 | 70.6 | 0.3-10.3 |
| door -x-y (y wall) 0 | 2.30 | 1667 | 2729 | 0.7 | 1197.1 | 36.3 | 112.5 | 22.4-32.4 |
| door -x-y (y wall) 1 | 2.30 | 1808 | 2254 | 0.9 | 1448.8 | 32.6 | 115.1 | 3.1-13.1 |
| door -x-y (y wall) 2 | 2.30 | 1692 | 1710 | 0.9 | 1466.6 | 30.1 | 115.1 | 30.3-40.2 |
| door -x-y (y wall) 3 | 2.30 | 1259 | 1163 | 0.9 | 1408.3 | 23.3 | 109.9 | 21.7-31.7 |
| door -x-y (y wall) 4 | 2.30 | 814 | 645 | 1.0 | 1347.1 | 15.8 | 107.3 | 0.9-10.8 |
| door -x-y (x wall) 0 | 2.30 | 1676 | 2720 | 0.7 | 1199.9 | 36.5 | 112.5 | 28.2-38.1 |
| door -x-y (x wall) 1 | 2.30 | 1816 | 2259 | 0.7 | 1434.9 | 33.0 | 115.1 | 24.7-34.6 |
| door -x-y (x wall) 2 | 2.30 | 1664 | 1704 | 0.9 | 1467.5 | 29.6 | 117.7 | 20.5-30.4 |
| door -x-y (x wall) 3 | 2.30 | 1323 | 1160 | 0.7 | 1456.3 | 23.7 | 109.9 | 18.0-28.0 |
| door -x-y (x wall) 4 | 2.30 | 846 | 643 | 0.9 | 1432.7 | 15.4 | 109.9 | 0.7-10.7 |
| door -x-y (corner) | 2.30 | 537 | 245 | 1.0 | 1132.0 | 12.4 | 70.6 | 0.9-10.8 |
| door +x-y (y wall) 0 | 2.30 | 1686 | 2725 | 0.9 | 1271.0 | 34.6 | 115.1 | 22.9-32.9 |
| door +x-y (y wall) 1 | 2.30 | 1861 | 2259 | 1.0 | 1442.8 | 33.7 | 109.9 | 38.1-48.1 |
| door +x-y (y wall) 2 | 2.30 | 1645 | 1708 | 0.7 | 1492.3 | 28.8 | 109.9 | 0.9-10.8 |
| door +x-y (y wall) 3 | 2.30 | 1224 | 1165 | 0.9 | 1463.1 | 21.8 | 107.3 | 11.7-21.7 |
| door +x-y (y wall) 4 | 2.30 | 868 | 639 | 0.9 | 1501.6 | 15.1 | 112.5 | 17.7-27.6 |
| door +x-y (x wall) 0 | 2.30 | 1673 | 2726 | 0.7 | 1274.7 | 34.3 | 109.9 | 21.5-31.5 |
| door +x-y (x wall) 1 | 2.30 | 1847 | 2257 | 0.9 | 1476.0 | 32.7 | 112.5 | 22.0-32.0 |
| door +x-y (x wall) 2 | 2.30 | 1694 | 1719 | 0.9 | 1490.0 | 29.7 | 112.5 | 10.7-20.6 |
| door +x-y (x wall) 3 | 2.30 | 1287 | 1159 | 0.9 | 1512.1 | 22.2 | 115.1 | 15.7-25.7 |
| door +x-y (x wall) 4 | 2.30 | 800 | 638 | 0.9 | 1498.6 | 13.9 | 109.9 | 0.7-10.7 |
| door +x-y (corner) | 2.30 | 606 | 245 | 0.9 | 1142.7 | 13.8 | 73.3 | 0.5-10.5 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (2.30 m; a corner door's: the gap between its wall ends, 2.30 m); agents are removed past the outer wall's outer face (92.71 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 2164 | 3.1% | 18.1% |
| -x | avenue | 5.66 | 2164 | 3.1% | 18.1% |
| +y | avenue | 5.66 | 2242 | 3.2% | 18.8% |
| -y | avenue | 5.66 | 2141 | 3.1% | 18.0% |
| door +x+y (y wall) 0 | door | 2.30 | 1645 | 2.4% | 33.9% |
| door +x+y (y wall) 1 | door | 2.30 | 1831 | 2.6% | 37.8% |
| door +x+y (y wall) 2 | door | 2.30 | 1711 | 2.5% | 35.3% |
| door +x+y (y wall) 3 | door | 2.30 | 1261 | 1.8% | 26.0% |
| door +x+y (y wall) 4 | door | 2.30 | 836 | 1.2% | 17.3% |
| door +x+y (x wall) 0 | door | 2.30 | 1688 | 2.4% | 34.8% |
| door +x+y (x wall) 1 | door | 2.30 | 1817 | 2.6% | 37.5% |
| door +x+y (x wall) 2 | door | 2.30 | 1692 | 2.4% | 34.9% |
| door +x+y (x wall) 3 | door | 2.30 | 1311 | 1.9% | 27.1% |
| door +x+y (x wall) 4 | door | 2.30 | 787 | 1.1% | 16.2% |
| door +x+y (corner) | door | 2.30 | 542 | 0.8% | 11.2% |
| door -x+y (y wall) 0 | door | 2.30 | 1687 | 2.4% | 34.8% |
| door -x+y (y wall) 1 | door | 2.30 | 1867 | 2.7% | 38.5% |
| door -x+y (y wall) 2 | door | 2.30 | 1794 | 2.6% | 37.0% |
| door -x+y (y wall) 3 | door | 2.30 | 1223 | 1.8% | 25.2% |
| door -x+y (y wall) 4 | door | 2.30 | 783 | 1.1% | 16.2% |
| door -x+y (x wall) 0 | door | 2.30 | 1672 | 2.4% | 34.5% |
| door -x+y (x wall) 1 | door | 2.30 | 1862 | 2.7% | 38.4% |
| door -x+y (x wall) 2 | door | 2.30 | 1796 | 2.6% | 37.1% |
| door -x+y (x wall) 3 | door | 2.30 | 1221 | 1.8% | 25.2% |
| door -x+y (x wall) 4 | door | 2.30 | 736 | 1.1% | 15.2% |
| door -x+y (corner) | door | 2.30 | 545 | 0.8% | 11.2% |
| door -x-y (y wall) 0 | door | 2.30 | 1667 | 2.4% | 34.4% |
| door -x-y (y wall) 1 | door | 2.30 | 1808 | 2.6% | 37.3% |
| door -x-y (y wall) 2 | door | 2.30 | 1692 | 2.4% | 34.9% |
| door -x-y (y wall) 3 | door | 2.30 | 1259 | 1.8% | 26.0% |
| door -x-y (y wall) 4 | door | 2.30 | 814 | 1.2% | 16.8% |
| door -x-y (x wall) 0 | door | 2.30 | 1676 | 2.4% | 34.6% |
| door -x-y (x wall) 1 | door | 2.30 | 1816 | 2.6% | 37.5% |
| door -x-y (x wall) 2 | door | 2.30 | 1664 | 2.4% | 34.3% |
| door -x-y (x wall) 3 | door | 2.30 | 1323 | 1.9% | 27.3% |
| door -x-y (x wall) 4 | door | 2.30 | 846 | 1.2% | 17.5% |
| door -x-y (corner) | door | 2.30 | 537 | 0.8% | 11.1% |
| door +x-y (y wall) 0 | door | 2.30 | 1686 | 2.4% | 34.8% |
| door +x-y (y wall) 1 | door | 2.30 | 1861 | 2.7% | 38.4% |
| door +x-y (y wall) 2 | door | 2.30 | 1645 | 2.4% | 33.9% |
| door +x-y (y wall) 3 | door | 2.30 | 1224 | 1.8% | 25.3% |
| door +x-y (y wall) 4 | door | 2.30 | 868 | 1.3% | 17.9% |
| door +x-y (x wall) 0 | door | 2.30 | 1673 | 2.4% | 34.5% |
| door +x-y (x wall) 1 | door | 2.30 | 1847 | 2.7% | 38.1% |
| door +x-y (x wall) 2 | door | 2.30 | 1694 | 2.4% | 35.0% |
| door +x-y (x wall) 3 | door | 2.30 | 1287 | 1.9% | 26.6% |
| door +x-y (x wall) 4 | door | 2.30 | 800 | 1.2% | 16.5% |
| door +x-y (corner) | door | 2.30 | 606 | 0.9% | 12.5% |
| **doors (44)** | door | 101.20 | 60600 | 87.4% | |
| **avenues (4)** | avenue | 22.64 | 8711 | 12.6% | |

**Unused exit width: 0.0 of 123.8 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 1512.1 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 26.6%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 2337 | 3.4% | 2337 | 3.4% |
| straight +x+y (y wing) 1 | straight | yes | 1865 | 2.7% | 1712 | 2.5% |
| straight +x+y (y wing) 2 | straight | yes | 1626 | 2.3% | 1614 | 2.3% |
| straight +x+y (y wing) 3 | straight | yes | 1164 | 1.7% | 1156 | 1.7% |
| straight +x+y (y wing) 4 | straight | yes | 688 | 1.0% | 677 | 1.0% |
| straight +x+y (x wing) 0 | straight | yes | 2393 | 3.5% | 2393 | 3.5% |
| straight +x+y (x wing) 1 | straight | yes | 1859 | 2.7% | 1708 | 2.5% |
| straight +x+y (x wing) 2 | straight | yes | 1601 | 2.3% | 1589 | 2.3% |
| straight +x+y (x wing) 3 | straight | yes | 1198 | 1.7% | 1192 | 1.7% |
| straight +x+y (x wing) 4 | straight | yes | 667 | 1.0% | 644 | 0.9% |
| corner +x+y | corner | yes | 2162 | 3.1% | 844 | 1.2% |
| straight -x+y (y wing) 0 | straight | yes | 2386 | 3.4% | 2386 | 3.4% |
| straight -x+y (y wing) 1 | straight | yes | 1895 | 2.7% | 1755 | 2.5% |
| straight -x+y (y wing) 2 | straight | yes | 1677 | 2.4% | 1675 | 2.4% |
| straight -x+y (y wing) 3 | straight | yes | 1131 | 1.6% | 1124 | 1.6% |
| straight -x+y (y wing) 4 | straight | yes | 647 | 0.9% | 635 | 0.9% |
| straight -x+y (x wing) 0 | straight | yes | 2350 | 3.4% | 2350 | 3.4% |
| straight -x+y (x wing) 1 | straight | yes | 1860 | 2.7% | 1750 | 2.5% |
| straight -x+y (x wing) 2 | straight | yes | 1695 | 2.4% | 1693 | 2.4% |
| straight -x+y (x wing) 3 | straight | yes | 1123 | 1.6% | 1117 | 1.6% |
| straight -x+y (x wing) 4 | straight | yes | 592 | 0.9% | 580 | 0.8% |
| corner -x+y | corner | yes | 2055 | 3.0% | 800 | 1.2% |
| straight -x-y (y wing) 0 | straight | yes | 2331 | 3.4% | 2331 | 3.4% |
| straight -x-y (y wing) 1 | straight | yes | 1861 | 2.7% | 1692 | 2.4% |
| straight -x-y (y wing) 2 | straight | yes | 1623 | 2.3% | 1598 | 2.3% |
| straight -x-y (y wing) 3 | straight | yes | 1143 | 1.6% | 1138 | 1.6% |
| straight -x-y (y wing) 4 | straight | yes | 674 | 1.0% | 663 | 1.0% |
| straight -x-y (x wing) 0 | straight | yes | 2394 | 3.5% | 2394 | 3.5% |
| straight -x-y (x wing) 1 | straight | yes | 1868 | 2.7% | 1694 | 2.4% |
| straight -x-y (x wing) 2 | straight | yes | 1576 | 2.3% | 1563 | 2.3% |
| straight -x-y (x wing) 3 | straight | yes | 1228 | 1.8% | 1224 | 1.8% |
| straight -x-y (x wing) 4 | straight | yes | 708 | 1.0% | 691 | 1.0% |
| corner -x-y | corner | yes | 2215 | 3.2% | 876 | 1.3% |
| straight +x-y (y wing) 0 | straight | yes | 2374 | 3.4% | 2374 | 3.4% |
| straight +x-y (y wing) 1 | straight | yes | 1861 | 2.7% | 1746 | 2.5% |
| straight +x-y (y wing) 2 | straight | yes | 1593 | 2.3% | 1573 | 2.3% |
| straight +x-y (y wing) 3 | straight | yes | 1126 | 1.6% | 1115 | 1.6% |
| straight +x-y (y wing) 4 | straight | yes | 704 | 1.0% | 689 | 1.0% |
| straight +x-y (x wing) 0 | straight | yes | 2376 | 3.4% | 2376 | 3.4% |
| straight +x-y (x wing) 1 | straight | yes | 1854 | 2.7% | 1739 | 2.5% |
| straight +x-y (x wing) 2 | straight | yes | 1598 | 2.3% | 1590 | 2.3% |
| straight +x-y (x wing) 3 | straight | yes | 1170 | 1.7% | 1164 | 1.7% |
| straight +x-y (x wing) 4 | straight | yes | 679 | 1.0% | 661 | 1.0% |
| corner +x-y | corner | yes | 2100 | 3.0% | 838 | 1.2% |
| **straight (40)** | | | 61495 | | 60102 | 86.7% |
| **corner (4)** | | | 8532 | | 3358 | 4.8% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 5851, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 2164 | 60.2 | 1212.3 | 0.24 | 0.75 | 0.0% |
| -x | 2164 | 60.2 | 1191.1 | 0.24 | 0.71 | 0.0% |
| +y | 2242 | 60.2 | 1178.9 | 0.25 | 0.72 | 0.0% |
| -y | 2141 | 60.2 | 1195.0 | 0.24 | 0.70 | 0.0% |
| door +x+y (y wall) 0 | 1645 | 0.9 | 1202.7 | 0.43 | 1.35 | 4.1% |
| door +x+y (y wall) 1 | 1831 | 0.9 | 1441.4 | 0.40 | 1.28 | 3.4% |
| door +x+y (y wall) 2 | 1711 | 0.7 | 1450.2 | 0.37 | 1.35 | 3.4% |
| door +x+y (y wall) 3 | 1261 | 0.9 | 1476.0 | 0.27 | 1.35 | 3.4% |
| door +x+y (y wall) 4 | 836 | 0.9 | 1488.8 | 0.18 | 1.25 | 4.0% |
| door +x+y (x wall) 0 | 1688 | 0.9 | 1216.7 | 0.43 | 1.31 | 4.1% |
| door +x+y (x wall) 1 | 1817 | 0.7 | 1461.0 | 0.39 | 1.28 | 2.7% |
| door +x+y (x wall) 2 | 1692 | 0.7 | 1492.8 | 0.35 | 1.35 | 3.3% |
| door +x+y (x wall) 3 | 1311 | 0.9 | 1455.9 | 0.28 | 1.31 | 3.4% |
| door +x+y (x wall) 4 | 787 | 1.0 | 1470.1 | 0.17 | 1.38 | 3.4% |
| door +x+y (corner) | 542 | 0.9 | 1028.6 | 0.16 | 0.85 | 1.0% |
| door -x+y (y wall) 0 | 1687 | 0.7 | 1325.4 | 0.40 | 1.28 | 3.8% |
| door -x+y (y wall) 1 | 1867 | 0.9 | 1381.6 | 0.42 | 1.28 | 3.6% |
| door -x+y (y wall) 2 | 1794 | 0.9 | 1457.7 | 0.38 | 1.25 | 3.4% |
| door -x+y (y wall) 3 | 1223 | 0.7 | 1461.3 | 0.26 | 1.35 | 3.4% |
| door -x+y (y wall) 4 | 783 | 0.9 | 1504.5 | 0.16 | 1.38 | 3.3% |
| door -x+y (x wall) 0 | 1672 | 0.9 | 1310.8 | 0.40 | 1.38 | 3.0% |
| door -x+y (x wall) 1 | 1862 | 0.7 | 1455.2 | 0.40 | 1.35 | 3.4% |
| door -x+y (x wall) 2 | 1796 | 0.9 | 1453.8 | 0.39 | 1.35 | 2.7% |
| door -x+y (x wall) 3 | 1221 | 0.7 | 1500.5 | 0.25 | 1.31 | 3.3% |
| door -x+y (x wall) 4 | 736 | 0.9 | 1495.8 | 0.15 | 1.31 | 3.3% |
| door -x+y (corner) | 545 | 0.9 | 1359.4 | 0.13 | 0.85 | 0.7% |
| door -x-y (y wall) 0 | 1667 | 0.7 | 1197.1 | 0.43 | 1.35 | 4.1% |
| door -x-y (y wall) 1 | 1808 | 0.9 | 1448.8 | 0.39 | 1.38 | 3.4% |
| door -x-y (y wall) 2 | 1692 | 0.9 | 1466.6 | 0.36 | 1.38 | 3.4% |
| door -x-y (y wall) 3 | 1259 | 0.9 | 1408.3 | 0.28 | 1.31 | 3.5% |
| door -x-y (y wall) 4 | 814 | 1.0 | 1347.1 | 0.19 | 1.28 | 3.7% |
| door -x-y (x wall) 0 | 1676 | 0.7 | 1199.9 | 0.44 | 1.35 | 4.1% |
| door -x-y (x wall) 1 | 1816 | 0.7 | 1434.9 | 0.40 | 1.38 | 3.5% |
| door -x-y (x wall) 2 | 1664 | 0.9 | 1467.5 | 0.35 | 1.41 | 3.4% |
| door -x-y (x wall) 3 | 1323 | 0.7 | 1456.3 | 0.28 | 1.31 | 3.4% |
| door -x-y (x wall) 4 | 846 | 0.9 | 1432.7 | 0.18 | 1.31 | 3.5% |
| door -x-y (corner) | 537 | 1.0 | 1132.0 | 0.15 | 0.85 | 0.0% |
| door +x-y (y wall) 0 | 1686 | 0.9 | 1271.0 | 0.41 | 1.38 | 3.1% |
| door +x-y (y wall) 1 | 1861 | 1.0 | 1442.8 | 0.40 | 1.31 | 3.4% |
| door +x-y (y wall) 2 | 1645 | 0.7 | 1492.3 | 0.34 | 1.31 | 3.3% |
| door +x-y (y wall) 3 | 1224 | 0.9 | 1463.1 | 0.26 | 1.28 | 3.4% |
| door +x-y (y wall) 4 | 868 | 0.9 | 1501.6 | 0.18 | 1.35 | 3.3% |
| door +x-y (x wall) 0 | 1673 | 0.7 | 1274.7 | 0.41 | 1.31 | 3.9% |
| door +x-y (x wall) 1 | 1847 | 0.9 | 1476.0 | 0.39 | 1.35 | 3.4% |
| door +x-y (x wall) 2 | 1694 | 0.9 | 1490.0 | 0.35 | 1.35 | 3.3% |
| door +x-y (x wall) 3 | 1287 | 0.9 | 1512.1 | 0.27 | 1.38 | 3.3% |
| door +x-y (x wall) 4 | 800 | 0.9 | 1498.6 | 0.17 | 1.31 | 3.3% |
| door +x-y (corner) | 606 | 0.9 | 1142.7 | 0.17 | 0.88 | 1.7% |

Mean flow / w J averaged over the doors 0.31, over the avenues 0.24.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 103.1 | 2337 | 1526 / 811 / 913 | 0.3 | 1156.1 | 2.81 | 4.81 | 91% | 88% | 3% | 4.48 |
| straight +x+y (y wing) 1 | 1.20 | 81.5 | 1825 | 1712 / 0 / 211 | 0.7 | 1438.4 | 1.34 | 2.21 | 92% | 70% | 23% | 3.58 |
| straight +x+y (y wing) 2 | 1.20 | 61.0 | 1544 | 1614 / 0 / 14 | 0.7 | 1447.2 | 1.13 | 1.81 | 79% | 69% | 10% | 3.84 |
| straight +x+y (y wing) 3 | 1.20 | 39.4 | 940 | 1156 / 0 / 9 | 0.7 | 1473.1 | 0.79 | 1.81 | 50% | 40% | 10% | 3.69 |
| straight +x+y (y wing) 4 | 1.20 | 18.8 | 395 | 677 / 0 / 27 | 0.7 | 1485.8 | 0.47 | 1.60 | 18% | 16% | 2% | 3.85 |
| straight +x+y (x wing) 0 | 1.20 | 103.1 | 2393 | 1576 / 819 / 1181 | 0.3 | 1213.7 | 2.95 | 5.92 | 93% | 87% | 6% | 4.26 |
| straight +x+y (x wing) 1 | 1.20 | 81.5 | 1845 | 1708 / 0 / 188 | 0.7 | 1458.0 | 1.30 | 2.31 | 92% | 75% | 17% | 3.68 |
| straight +x+y (x wing) 2 | 1.20 | 61.0 | 1471 | 1589 / 0 / 19 | 0.7 | 1489.9 | 1.08 | 1.91 | 73% | 65% | 7% | 3.77 |
| straight +x+y (x wing) 3 | 1.20 | 39.4 | 947 | 1192 / 0 / 7 | 0.7 | 1453.0 | 0.83 | 1.71 | 51% | 39% | 12% | 3.43 |
| straight +x+y (x wing) 4 | 1.20 | 18.8 | 407 | 644 / 0 / 25 | 0.7 | 1467.1 | 0.46 | 1.81 | 18% | 17% | 1% | 3.85 |
| corner +x+y | 1.20 | 186.0 | 1762 | 418 / 426 / 1367 | 0.7 | 1461.9 | 1.51 | 3.81 | 92% | 57% | 35% | 2.61 |
| straight -x+y (y wing) 0 | 1.20 | 103.1 | 2386 | 1557 / 830 / 1051 | 0.2 | 1180.4 | 2.91 | 5.32 | 92% | 86% | 7% | 4.21 |
| straight -x+y (y wing) 1 | 1.20 | 81.5 | 1865 | 1755 / 0 / 181 | 0.7 | 1378.8 | 1.40 | 2.21 | 90% | 79% | 11% | 4.04 |
| straight -x+y (y wing) 2 | 1.20 | 61.0 | 1473 | 1675 / 0 / 10 | 0.7 | 1454.7 | 1.16 | 1.71 | 87% | 64% | 23% | 3.49 |
| straight -x+y (y wing) 3 | 1.20 | 39.4 | 942 | 1124 / 0 / 37 | 0.7 | 1458.4 | 0.80 | 1.60 | 52% | 39% | 13% | 3.29 |
| straight -x+y (y wing) 4 | 1.20 | 18.8 | 401 | 635 / 0 / 17 | 0.7 | 1501.6 | 0.43 | 1.71 | 18% | 17% | 1% | 3.93 |
| straight -x+y (x wing) 0 | 1.20 | 103.1 | 2350 | 1548 / 804 / 948 | 0.2 | 1161.4 | 2.84 | 4.91 | 91% | 88% | 3% | 4.47 |
| straight -x+y (x wing) 1 | 1.20 | 81.5 | 1827 | 1750 / 0 / 164 | 0.7 | 1452.3 | 1.32 | 2.41 | 90% | 73% | 16% | 3.92 |
| straight -x+y (x wing) 2 | 1.20 | 61.0 | 1543 | 1693 / 0 / 7 | 0.7 | 1451.0 | 1.17 | 1.81 | 88% | 68% | 21% | 3.58 |
| straight -x+y (x wing) 3 | 1.20 | 39.4 | 943 | 1117 / 0 / 12 | 0.7 | 1497.6 | 0.75 | 1.71 | 48% | 39% | 9% | 3.74 |
| straight -x+y (x wing) 4 | 1.20 | 18.8 | 397 | 580 / 0 / 15 | 0.7 | 1492.8 | 0.40 | 1.60 | 19% | 17% | 2% | 3.80 |
| corner -x+y | 1.20 | 186.0 | 1738 | 427 / 373 / 1339 | 0.7 | 1477.6 | 1.45 | 3.71 | 92% | 75% | 17% | 2.74 |
| straight -x-y (y wing) 0 | 1.20 | 103.1 | 2331 | 1550 / 783 / 920 | 0.7 | 1176.8 | 2.77 | 5.02 | 92% | 86% | 6% | 4.45 |
| straight -x-y (y wing) 1 | 1.20 | 81.5 | 1830 | 1692 / 0 / 245 | 0.7 | 1445.8 | 1.34 | 2.51 | 87% | 69% | 18% | 3.74 |
| straight -x-y (y wing) 2 | 1.20 | 61.0 | 1548 | 1598 / 0 / 26 | 0.7 | 1463.6 | 1.11 | 1.81 | 81% | 71% | 10% | 3.86 |
| straight -x-y (y wing) 3 | 1.20 | 39.4 | 935 | 1138 / 0 / 5 | 0.7 | 1405.4 | 0.81 | 1.60 | 55% | 43% | 11% | 3.51 |
| straight -x-y (y wing) 4 | 1.20 | 18.8 | 400 | 663 / 0 / 26 | 0.7 | 1344.2 | 0.51 | 1.81 | 22% | 19% | 4% | 3.49 |
| straight -x-y (x wing) 0 | 1.20 | 103.1 | 2394 | 1564 / 830 / 1006 | 0.3 | 1196.9 | 2.84 | 4.91 | 92% | 85% | 7% | 4.24 |
| straight -x-y (x wing) 1 | 1.20 | 81.5 | 1846 | 1694 / 0 / 223 | 0.7 | 1432.0 | 1.34 | 2.41 | 90% | 69% | 21% | 3.64 |
| straight -x-y (x wing) 2 | 1.20 | 61.0 | 1475 | 1563 / 0 / 15 | 0.7 | 1464.5 | 1.08 | 1.71 | 77% | 65% | 12% | 3.71 |
| straight -x-y (x wing) 3 | 1.20 | 39.4 | 940 | 1224 / 0 / 12 | 0.7 | 1453.3 | 0.85 | 2.01 | 48% | 40% | 8% | 3.68 |
| straight -x-y (x wing) 4 | 1.20 | 18.8 | 394 | 691 / 0 / 18 | 0.7 | 1429.7 | 0.50 | 1.81 | 19% | 15% | 3% | 3.78 |
| corner -x-y | 1.20 | 186.0 | 1771 | 416 / 460 / 1401 | 0.7 | 1405.7 | 1.62 | 3.91 | 94% | 62% | 33% | 2.73 |
| straight +x-y (y wing) 0 | 1.20 | 103.1 | 2374 | 1562 / 814 / 1090 | 0.5 | 1200.0 | 2.89 | 4.91 | 92% | 85% | 7% | 4.23 |
| straight +x-y (y wing) 1 | 1.20 | 81.5 | 1846 | 1746 / 0 / 157 | 0.7 | 1439.8 | 1.32 | 2.11 | 91% | 77% | 14% | 3.89 |
| straight +x-y (y wing) 2 | 1.20 | 61.0 | 1497 | 1573 / 0 / 22 | 0.7 | 1489.3 | 1.07 | 1.71 | 77% | 65% | 11% | 3.70 |
| straight +x-y (y wing) 3 | 1.20 | 39.4 | 932 | 1115 / 0 / 41 | 0.7 | 1460.1 | 0.79 | 2.81 | 50% | 43% | 7% | 3.57 |
| straight +x-y (y wing) 4 | 1.20 | 18.8 | 394 | 689 / 0 / 69 | 0.7 | 1498.6 | 0.51 | 2.01 | 18% | 16% | 2% | 3.78 |
| straight +x-y (x wing) 0 | 1.20 | 103.1 | 2376 | 1549 / 828 / 1071 | 0.2 | 1192.5 | 2.89 | 5.42 | 92% | 85% | 8% | 4.13 |
| straight +x-y (x wing) 1 | 1.20 | 81.5 | 1830 | 1739 / 0 / 161 | 0.7 | 1473.1 | 1.29 | 2.31 | 92% | 74% | 18% | 3.68 |
| straight +x-y (x wing) 2 | 1.20 | 61.0 | 1492 | 1590 / 0 / 16 | 0.7 | 1487.1 | 1.08 | 1.71 | 77% | 65% | 13% | 3.68 |
| straight +x-y (x wing) 3 | 1.20 | 39.4 | 931 | 1164 / 0 / 9 | 0.7 | 1509.1 | 0.78 | 1.71 | 48% | 38% | 10% | 3.58 |
| straight +x-y (x wing) 4 | 1.20 | 18.8 | 416 | 661 / 0 / 25 | 0.7 | 1495.6 | 0.46 | 1.71 | 19% | 17% | 2% | 3.74 |
| corner +x-y | 1.20 | 186.0 | 1777 | 485 / 353 / 1402 | 0.7 | 1474.6 | 1.52 | 3.41 | 92% | 57% | 34% | 2.58 |

The last agent out (agent 48386, t100 1512.1 s): last gangway straight +x-y (x wing) 3, exit door +x-y (x wall) 3. The gangway that cleared last: straight +x-y (x wing) 3 at 1509.1 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 8804 | 7800.4 | 7.13 | 1508.7 / 1433.4 / 1384.6 | 1436.7 / 1408.9 / 1339.1 | 7337101.3 | 13889630 | 0.166 |
| gangway | 3792 | 3512.9 | 7.13 | 1507.3 / 1433.2 / 1382.6 | 1436.7 / 1408.9 / 1339.1 | 7310187.2 | 12939672 | 0.101 |
| walkway | 276 | 257.4 | 5.25 | 791.8 / 505.7 / 24.5 | 442.2 / 207.8 / 12.4 | 160.9 | 86877 | 0.698 |
| avenue | 1920 | 1801.4 | 3.04 | 817.3 / 27.3 / 0.0 | 599.8 / 2.1 / 0.0 | 0.0 | 522067 | 1.334 |
| exit | 4 | 2.0 | 0.00 | 0.7 / 0.0 / 0.0 | 0.7 / 0.0 / 0.0 | 0.0 | 3 | 0.886 |
| concourse | 2812 | 2226.8 | 6.20 | 1459.8 / 73.3 / 49.7 | 1086.5 / 69.6 / 41.6 | 26753.2 | 341012 | 0.712 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 25392 | 16030.4 | 7.82 | 1365.8 / 1362.9 / 1348.4 | 1359.0 / 1355.5 / 1337.7 | 9258251.6 | 22818962 | 0.022 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 208 x 208 from (-104, -104) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 35.5 | 35.5 | gangway | 1.00 | 5.94 | 1382.1 | 1371.8 | 1320.0 | 7699.9 | 0.007 |
| 2 | -48.5 | 48.5 | gangway | 1.00 | 5.83 | 1402.4 | 1400.3 | 1327.7 | 7598.3 | 0.006 |
| 3 | 35.5 | -35.5 | gangway | 1.00 | 5.87 | 1396.1 | 1393.3 | 1297.5 | 7388.4 | 0.007 |
| 4 | -47.5 | 47.5 | gangway | 1.00 | 5.71 | 1396.8 | 1394.5 | 1324.6 | 7322.8 | 0.005 |
| 5 | -35.5 | -35.5 | gangway | 1.00 | 5.91 | 1354.1 | 1342.8 | 1264.1 | 7290.8 | 0.007 |
| 6 | 34.5 | -34.5 | gangway | 1.00 | 5.75 | 1386.5 | 1379.5 | 1323.2 | 7235.6 | 0.006 |
| 7 | 36.5 | -36.5 | gangway | 1.00 | 5.73 | 1401.4 | 1397.7 | 1284.5 | 7232.4 | 0.011 |
| 8 | 38.5 | 38.5 | gangway | 1.00 | 5.96 | 1393.3 | 1369.2 | 1232.7 | 7180.3 | 0.013 |
| 9 | 34.5 | 34.5 | gangway | 1.00 | 5.80 | 1373.4 | 1362.5 | 1325.6 | 7148.3 | 0.007 |
| 10 | -35.5 | 35.5 | gangway | 1.00 | 5.74 | 1347.1 | 1342.4 | 1253.6 | 7090.4 | 0.005 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 38.5 | -36.5 | seat row | 0.50 | 7.40 | 1334.0 | 1331.4 | 1313.5 | 4712.3 | 0.005 |
| 2 | 36.5 | -38.5 | seat row | 0.50 | 7.29 | 1330.2 | 1326.0 | 1313.0 | 4706.0 | 0.004 |
| 3 | -48.5 | 50.5 | seat row | 0.50 | 7.00 | 1359.0 | 1355.5 | 1337.7 | 4620.0 | 0.003 |
| 4 | 38.5 | 36.5 | seat row | 0.50 | 7.11 | 1331.9 | 1325.4 | 1314.9 | 4612.5 | 0.004 |
| 5 | -38.5 | -36.5 | seat row | 0.50 | 7.26 | 1314.9 | 1313.2 | 1294.1 | 4598.8 | 0.004 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 8439; agent-steps of seated agents on another row's clearway: 592548.

## Deposit check

Person-seconds deposited: 36714864.5, of them in excluded cells: 6271.872.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 9260208 overlapping pair-steps: p99 0.0019, max 0.0646 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0019 max 0.0646; venue-geometry 17: p99 0.0012 max 0.0012 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00763 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 64 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.46 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 3789 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
