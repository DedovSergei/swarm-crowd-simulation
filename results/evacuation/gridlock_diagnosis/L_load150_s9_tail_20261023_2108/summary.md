# Experiment `L_load150_s9_tail`

**Task 5.11 stage 1b (diagnosis): L 109.28% seed 9 (the slow tail of stage 1) with stall snapshots after 10, 20, 40 ... s**

Venue L (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (4000 x 4000), cache key a2f3aaf59c2252b7, content hash 022d17b202313d70). 69311 agents (load 109.3%, requested 150%): every one of the 63424 seats and 5887 standing (spawnOvercrowdedCrowd, seed 9; below), buffer N = 131072, 10205 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 12286598 evaluations, 670147 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.09)** (the L venue's design capacity 63424, jam capacity 171923: 23822.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `2460e1c59e38aaecfb32bf43be1679eb3fbcf232`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-23T21:08:41, 1009.0 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Spawn (overcrowding)

| | |
|---|---|
| seated | 63424 (every seat) |
| standing | **5887** (requested round((1.50 - 1) x 63424) = 31712; at most 5887 = floor(2.5 p/m^2 x 2355.0 m^2)) |
| standing floor | walkway + rear concourse, 2355.0 m^2 |
| standing on the walkway / concourse / gangways | 628 / 5259 / 0 |
| **load** | **109.28%** of the seats (requested 150%; the floor takes no more: the achievable maximum) |
| standing crowd's mean density | 2.500 p/m^2 |
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 4.13, all circulation cells 4.13 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 9, 361826 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 2756 | 482.0 |
| t90 | 6196 | 1083.7 |
| t100 | 10205 | 1784.9 |

t_p: the step by which ceil(p x 69311) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 2179 | 90 | 60.2 | 1189.2 | 20.5 | 60.6 | 59.6-69.6 |
| -x | 5.66 | 2125 | 81 | 60.2 | 1192.0 | 19.9 | 58.5 | 60.0-70.0 |
| +y | 5.66 | 2184 | 84 | 60.2 | 1192.3 | 20.4 | 57.4 | 59.8-69.8 |
| -y | 5.66 | 2143 | 84 | 60.2 | 1202.0 | 19.9 | 60.6 | 60.0-70.0 |
| door +x+y (y wall) 0 | 2.30 | 1642 | 2731 | 0.9 | 1298.7 | 33.0 | 107.3 | 22.6-32.5 |
| door +x+y (y wall) 1 | 2.30 | 1843 | 2256 | 0.9 | 1437.7 | 33.5 | 112.5 | 17.8-27.8 |
| door +x+y (y wall) 2 | 2.30 | 1695 | 1714 | 0.7 | 1470.4 | 30.1 | 112.5 | 1.7-11.7 |
| door +x+y (y wall) 3 | 2.30 | 1196 | 1165 | 0.7 | 1462.2 | 21.3 | 109.9 | 22.4-32.4 |
| door +x+y (y wall) 4 | 2.30 | 869 | 643 | 0.9 | 1475.5 | 15.4 | 109.9 | 29.9-39.9 |
| door +x+y (x wall) 0 | 2.30 | 1681 | 2732 | 0.9 | 1319.3 | 33.3 | 109.9 | 1.4-11.4 |
| door +x+y (x wall) 1 | 2.30 | 1856 | 2261 | 0.7 | 1462.6 | 33.1 | 107.3 | 5.9-15.9 |
| door +x+y (x wall) 2 | 2.30 | 1668 | 1712 | 0.9 | 1481.1 | 29.4 | 109.9 | 23.4-33.4 |
| door +x+y (x wall) 3 | 2.30 | 1303 | 1162 | 0.9 | 1478.3 | 23.0 | 107.3 | 25.4-35.3 |
| door +x+y (x wall) 4 | 2.30 | 847 | 634 | 0.7 | 1491.1 | 14.8 | 112.5 | 21.5-31.5 |
| door +x+y (corner) | 2.30 | 611 | 252 | 0.7 | 1157.0 | 13.8 | 70.6 | 0.2-10.1 |
| door -x+y (y wall) 0 | 2.30 | 1647 | 2724 | 0.7 | 1247.6 | 34.5 | 112.5 | 34.1-44.1 |
| door -x+y (y wall) 1 | 2.30 | 1823 | 2249 | 0.9 | 1443.9 | 33.0 | 109.9 | 15.2-25.2 |
| door -x+y (y wall) 2 | 2.30 | 1706 | 1708 | 0.7 | 1500.9 | 29.7 | 109.9 | 22.7-32.7 |
| door -x+y (y wall) 3 | 2.30 | 1280 | 1159 | 0.7 | 1489.0 | 22.4 | 112.5 | 17.3-27.3 |
| door -x+y (y wall) 4 | 2.30 | 781 | 643 | 0.9 | 1415.7 | 14.4 | 109.9 | 11.9-21.9 |
| door -x+y (x wall) 0 | 2.30 | 1657 | 2721 | 0.9 | 1173.6 | 36.9 | 109.9 | 16.3-26.2 |
| door -x+y (x wall) 1 | 2.30 | 1836 | 2255 | 0.9 | 1416.9 | 33.8 | 112.5 | 16.6-26.6 |
| door -x+y (x wall) 2 | 2.30 | 1696 | 1710 | 1.0 | 1485.8 | 29.8 | 112.5 | 20.5-30.4 |
| door -x+y (x wall) 3 | 2.30 | 1284 | 1163 | 0.7 | 1500.3 | 22.3 | 112.5 | 1.9-11.9 |
| door -x+y (x wall) 4 | 2.30 | 834 | 640 | 0.9 | 1457.7 | 14.9 | 109.9 | 32.9-42.9 |
| door -x+y (corner) | 2.30 | 528 | 246 | 0.9 | 1117.7 | 12.3 | 70.6 | 61.7-71.7 |
| door -x-y (y wall) 0 | 2.30 | 1685 | 2739 | 0.7 | 1312.8 | 33.5 | 117.7 | 13.6-23.6 |
| door -x-y (y wall) 1 | 2.30 | 1848 | 2247 | 0.7 | 1478.3 | 32.6 | 109.9 | 31.5-41.5 |
| door -x-y (y wall) 2 | 2.30 | 1719 | 1715 | 0.9 | 1519.6 | 29.5 | 112.5 | 29.9-39.9 |
| door -x-y (y wall) 3 | 2.30 | 1204 | 1164 | 0.9 | 1484.6 | 21.2 | 109.9 | 17.1-27.1 |
| door -x-y (y wall) 4 | 2.30 | 840 | 637 | 0.9 | 1460.5 | 15.0 | 112.5 | 0.9-10.8 |
| door -x-y (x wall) 0 | 2.30 | 1673 | 2733 | 0.9 | 1327.2 | 32.9 | 117.7 | 18.7-28.7 |
| door -x-y (x wall) 1 | 2.30 | 1860 | 2259 | 0.9 | 1466.2 | 33.1 | 109.9 | 21.5-31.5 |
| door -x-y (x wall) 2 | 2.30 | 1711 | 1708 | 0.9 | 1505.9 | 29.7 | 107.3 | 14.3-24.3 |
| door -x-y (x wall) 3 | 2.30 | 1241 | 1163 | 0.9 | 1466.6 | 22.1 | 112.5 | 14.2-24.1 |
| door -x-y (x wall) 4 | 2.30 | 813 | 643 | 0.7 | 1491.4 | 14.2 | 115.1 | 28.2-38.1 |
| door -x-y (corner) | 2.30 | 620 | 249 | 1.0 | 1059.2 | 15.3 | 68.0 | 0.9-10.8 |
| door +x-y (y wall) 0 | 2.30 | 1686 | 2723 | 0.9 | 1323.9 | 33.2 | 112.5 | 19.6-29.6 |
| door +x-y (y wall) 1 | 2.30 | 1867 | 2251 | 0.9 | 1662.7 | 29.3 | 107.3 | 8.2-18.2 |
| door +x-y (y wall) 2 | 2.30 | 1726 | 1711 | 0.9 | 1714.6 | 26.3 | 107.3 | 18.5-28.5 |
| door +x-y (y wall) 3 | 2.30 | 1227 | 1163 | 0.9 | 1784.0 | 17.9 | 109.9 | 31.3-41.3 |
| door +x-y (y wall) 4 | 2.30 | 839 | 639 | 0.9 | 1566.6 | 14.0 | 112.5 | 10.0-19.9 |
| door +x-y (x wall) 0 | 2.30 | 1658 | 2727 | 0.9 | 1298.2 | 33.3 | 112.5 | 7.3-17.3 |
| door +x-y (x wall) 1 | 2.30 | 1867 | 2251 | 0.9 | 1510.8 | 32.3 | 112.5 | 0.7-10.7 |
| door +x-y (x wall) 2 | 2.30 | 1719 | 1711 | 0.7 | 1780.0 | 25.2 | 112.5 | 32.5-42.5 |
| door +x-y (x wall) 3 | 2.30 | 1181 | 1169 | 0.7 | 1784.9 | 17.3 | 104.7 | 11.7-21.7 |
| door +x-y (x wall) 4 | 2.30 | 803 | 638 | 0.9 | 1714.4 | 12.2 | 112.5 | 18.2-28.2 |
| door +x-y (corner) | 2.30 | 610 | 252 | 1.0 | 1278.0 | 12.5 | 73.3 | 71.5-81.5 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (2.30 m; a corner door's: the gap between its wall ends, 2.30 m); agents are removed past the outer wall's outer face (92.71 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 2179 | 3.1% | 15.5% |
| -x | avenue | 5.66 | 2125 | 3.1% | 15.1% |
| +y | avenue | 5.66 | 2184 | 3.2% | 15.5% |
| -y | avenue | 5.66 | 2143 | 3.1% | 15.2% |
| door +x+y (y wall) 0 | door | 2.30 | 1642 | 2.4% | 28.7% |
| door +x+y (y wall) 1 | door | 2.30 | 1843 | 2.7% | 32.2% |
| door +x+y (y wall) 2 | door | 2.30 | 1695 | 2.4% | 29.6% |
| door +x+y (y wall) 3 | door | 2.30 | 1196 | 1.7% | 20.9% |
| door +x+y (y wall) 4 | door | 2.30 | 869 | 1.3% | 15.2% |
| door +x+y (x wall) 0 | door | 2.30 | 1681 | 2.4% | 29.4% |
| door +x+y (x wall) 1 | door | 2.30 | 1856 | 2.7% | 32.4% |
| door +x+y (x wall) 2 | door | 2.30 | 1668 | 2.4% | 29.2% |
| door +x+y (x wall) 3 | door | 2.30 | 1303 | 1.9% | 22.8% |
| door +x+y (x wall) 4 | door | 2.30 | 847 | 1.2% | 14.8% |
| door +x+y (corner) | door | 2.30 | 611 | 0.9% | 10.7% |
| door -x+y (y wall) 0 | door | 2.30 | 1647 | 2.4% | 28.8% |
| door -x+y (y wall) 1 | door | 2.30 | 1823 | 2.6% | 31.9% |
| door -x+y (y wall) 2 | door | 2.30 | 1706 | 2.5% | 29.8% |
| door -x+y (y wall) 3 | door | 2.30 | 1280 | 1.8% | 22.4% |
| door -x+y (y wall) 4 | door | 2.30 | 781 | 1.1% | 13.7% |
| door -x+y (x wall) 0 | door | 2.30 | 1657 | 2.4% | 29.0% |
| door -x+y (x wall) 1 | door | 2.30 | 1836 | 2.6% | 32.1% |
| door -x+y (x wall) 2 | door | 2.30 | 1696 | 2.4% | 29.6% |
| door -x+y (x wall) 3 | door | 2.30 | 1284 | 1.9% | 22.4% |
| door -x+y (x wall) 4 | door | 2.30 | 834 | 1.2% | 14.6% |
| door -x+y (corner) | door | 2.30 | 528 | 0.8% | 9.2% |
| door -x-y (y wall) 0 | door | 2.30 | 1685 | 2.4% | 29.5% |
| door -x-y (y wall) 1 | door | 2.30 | 1848 | 2.7% | 32.3% |
| door -x-y (y wall) 2 | door | 2.30 | 1719 | 2.5% | 30.1% |
| door -x-y (y wall) 3 | door | 2.30 | 1204 | 1.7% | 21.0% |
| door -x-y (y wall) 4 | door | 2.30 | 840 | 1.2% | 14.7% |
| door -x-y (x wall) 0 | door | 2.30 | 1673 | 2.4% | 29.2% |
| door -x-y (x wall) 1 | door | 2.30 | 1860 | 2.7% | 32.5% |
| door -x-y (x wall) 2 | door | 2.30 | 1711 | 2.5% | 29.9% |
| door -x-y (x wall) 3 | door | 2.30 | 1241 | 1.8% | 21.7% |
| door -x-y (x wall) 4 | door | 2.30 | 813 | 1.2% | 14.2% |
| door -x-y (corner) | door | 2.30 | 620 | 0.9% | 10.8% |
| door +x-y (y wall) 0 | door | 2.30 | 1686 | 2.4% | 29.5% |
| door +x-y (y wall) 1 | door | 2.30 | 1867 | 2.7% | 32.6% |
| door +x-y (y wall) 2 | door | 2.30 | 1726 | 2.5% | 30.2% |
| door +x-y (y wall) 3 | door | 2.30 | 1227 | 1.8% | 21.5% |
| door +x-y (y wall) 4 | door | 2.30 | 839 | 1.2% | 14.7% |
| door +x-y (x wall) 0 | door | 2.30 | 1658 | 2.4% | 29.0% |
| door +x-y (x wall) 1 | door | 2.30 | 1867 | 2.7% | 32.6% |
| door +x-y (x wall) 2 | door | 2.30 | 1719 | 2.5% | 30.1% |
| door +x-y (x wall) 3 | door | 2.30 | 1181 | 1.7% | 20.6% |
| door +x-y (x wall) 4 | door | 2.30 | 803 | 1.2% | 14.0% |
| door +x-y (corner) | door | 2.30 | 610 | 0.9% | 10.7% |
| **doors (44)** | door | 101.20 | 60680 | 87.5% | |
| **avenues (4)** | avenue | 22.64 | 8631 | 12.5% | |

**Unused exit width: 0.0 of 123.8 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 1784.9 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 22.5%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 2313 | 3.3% | 2313 | 3.3% |
| straight +x+y (y wing) 1 | straight | yes | 1853 | 2.7% | 1731 | 2.5% |
| straight +x+y (y wing) 2 | straight | yes | 1628 | 2.3% | 1612 | 2.3% |
| straight +x+y (y wing) 3 | straight | yes | 1120 | 1.6% | 1112 | 1.6% |
| straight +x+y (y wing) 4 | straight | yes | 681 | 1.0% | 666 | 1.0% |
| straight +x+y (x wing) 0 | straight | yes | 2383 | 3.4% | 2383 | 3.4% |
| straight +x+y (x wing) 1 | straight | yes | 1842 | 2.7% | 1740 | 2.5% |
| straight +x+y (x wing) 2 | straight | yes | 1592 | 2.3% | 1581 | 2.3% |
| straight +x+y (x wing) 3 | straight | yes | 1184 | 1.7% | 1169 | 1.7% |
| straight +x+y (x wing) 4 | straight | yes | 720 | 1.0% | 712 | 1.0% |
| corner +x+y | corner | yes | 2124 | 3.1% | 846 | 1.2% |
| straight -x+y (y wing) 0 | straight | yes | 2335 | 3.4% | 2335 | 3.4% |
| straight -x+y (y wing) 1 | straight | yes | 1885 | 2.7% | 1713 | 2.5% |
| straight -x+y (y wing) 2 | straight | yes | 1609 | 2.3% | 1600 | 2.3% |
| straight -x+y (y wing) 3 | straight | yes | 1192 | 1.7% | 1189 | 1.7% |
| straight -x+y (y wing) 4 | straight | yes | 639 | 0.9% | 620 | 0.9% |
| straight -x+y (x wing) 0 | straight | yes | 2353 | 3.4% | 2353 | 3.4% |
| straight -x+y (x wing) 1 | straight | yes | 1890 | 2.7% | 1718 | 2.5% |
| straight -x+y (x wing) 2 | straight | yes | 1600 | 2.3% | 1590 | 2.3% |
| straight -x+y (x wing) 3 | straight | yes | 1207 | 1.7% | 1205 | 1.7% |
| straight -x+y (x wing) 4 | straight | yes | 674 | 1.0% | 658 | 0.9% |
| corner -x+y | corner | yes | 2189 | 3.2% | 884 | 1.3% |
| straight -x-y (y wing) 0 | straight | yes | 2377 | 3.4% | 2377 | 3.4% |
| straight -x-y (y wing) 1 | straight | yes | 1862 | 2.7% | 1747 | 2.5% |
| straight -x-y (y wing) 2 | straight | yes | 1616 | 2.3% | 1611 | 2.3% |
| straight -x-y (y wing) 3 | straight | yes | 1135 | 1.6% | 1123 | 1.6% |
| straight -x-y (y wing) 4 | straight | yes | 678 | 1.0% | 665 | 1.0% |
| straight -x-y (x wing) 0 | straight | yes | 2348 | 3.4% | 2348 | 3.4% |
| straight -x-y (x wing) 1 | straight | yes | 1850 | 2.7% | 1751 | 2.5% |
| straight -x-y (x wing) 2 | straight | yes | 1634 | 2.4% | 1624 | 2.3% |
| straight -x-y (x wing) 3 | straight | yes | 1142 | 1.6% | 1119 | 1.6% |
| straight -x-y (x wing) 4 | straight | yes | 679 | 1.0% | 660 | 1.0% |
| corner -x-y | corner | yes | 2082 | 3.0% | 841 | 1.2% |
| straight +x-y (y wing) 0 | straight | yes | 2382 | 3.4% | 2382 | 3.4% |
| straight +x-y (y wing) 1 | straight | yes | 1887 | 2.7% | 1758 | 2.5% |
| straight +x-y (y wing) 2 | straight | yes | 1648 | 2.4% | 1638 | 2.4% |
| straight +x-y (y wing) 3 | straight | yes | 1139 | 1.6% | 1124 | 1.6% |
| straight +x-y (y wing) 4 | straight | yes | 684 | 1.0% | 669 | 1.0% |
| straight +x-y (x wing) 0 | straight | yes | 2349 | 3.4% | 2349 | 3.4% |
| straight +x-y (x wing) 1 | straight | yes | 1876 | 2.7% | 1759 | 2.5% |
| straight +x-y (x wing) 2 | straight | yes | 1649 | 2.4% | 1642 | 2.4% |
| straight +x-y (x wing) 3 | straight | yes | 1082 | 1.6% | 1067 | 1.5% |
| straight +x-y (x wing) 4 | straight | yes | 644 | 0.9% | 628 | 0.9% |
| corner +x-y | corner | yes | 2086 | 3.0% | 849 | 1.2% |
| **straight (40)** | | | 61361 | | 60041 | 86.6% |
| **corner (4)** | | | 8481 | | 3420 | 4.9% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 5850, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 2179 | 60.2 | 1189.2 | 0.24 | 0.72 | 0.0% |
| -x | 2125 | 60.2 | 1192.0 | 0.24 | 0.70 | 0.0% |
| +y | 2184 | 60.2 | 1192.3 | 0.24 | 0.69 | 0.0% |
| -y | 2143 | 60.2 | 1202.0 | 0.24 | 0.72 | 0.0% |
| door +x+y (y wall) 0 | 1642 | 0.9 | 1298.7 | 0.39 | 1.28 | 3.8% |
| door +x+y (y wall) 1 | 1843 | 0.9 | 1437.7 | 0.40 | 1.35 | 3.4% |
| door +x+y (y wall) 2 | 1695 | 0.7 | 1470.4 | 0.36 | 1.35 | 3.4% |
| door +x+y (y wall) 3 | 1196 | 0.7 | 1462.2 | 0.26 | 1.31 | 3.4% |
| door +x+y (y wall) 4 | 869 | 0.9 | 1475.5 | 0.18 | 1.31 | 3.4% |
| door +x+y (x wall) 0 | 1681 | 0.9 | 1319.3 | 0.40 | 1.31 | 3.8% |
| door +x+y (x wall) 1 | 1856 | 0.7 | 1462.6 | 0.40 | 1.28 | 3.4% |
| door +x+y (x wall) 2 | 1668 | 0.9 | 1481.1 | 0.35 | 1.31 | 3.4% |
| door +x+y (x wall) 3 | 1303 | 0.9 | 1478.3 | 0.28 | 1.28 | 3.4% |
| door +x+y (x wall) 4 | 847 | 0.7 | 1491.1 | 0.18 | 1.35 | 3.3% |
| door +x+y (corner) | 611 | 0.7 | 1157.0 | 0.16 | 0.85 | 0.9% |
| door -x+y (y wall) 0 | 1647 | 0.7 | 1247.6 | 0.41 | 1.35 | 4.0% |
| door -x+y (y wall) 1 | 1823 | 0.9 | 1443.9 | 0.39 | 1.31 | 2.8% |
| door -x+y (y wall) 2 | 1706 | 0.7 | 1500.9 | 0.35 | 1.31 | 3.3% |
| door -x+y (y wall) 3 | 1280 | 0.7 | 1489.0 | 0.27 | 1.35 | 3.3% |
| door -x+y (y wall) 4 | 781 | 0.9 | 1415.7 | 0.17 | 1.31 | 3.5% |
| door -x+y (x wall) 0 | 1657 | 0.9 | 1173.6 | 0.44 | 1.31 | 3.4% |
| door -x+y (x wall) 1 | 1836 | 0.9 | 1416.9 | 0.40 | 1.35 | 3.5% |
| door -x+y (x wall) 2 | 1696 | 1.0 | 1485.8 | 0.36 | 1.35 | 3.3% |
| door -x+y (x wall) 3 | 1284 | 0.7 | 1500.3 | 0.27 | 1.35 | 3.3% |
| door -x+y (x wall) 4 | 834 | 0.9 | 1457.7 | 0.18 | 1.31 | 3.4% |
| door -x+y (corner) | 528 | 0.9 | 1117.7 | 0.15 | 0.85 | 0.0% |
| door -x-y (y wall) 0 | 1685 | 0.7 | 1312.8 | 0.40 | 1.41 | 3.8% |
| door -x-y (y wall) 1 | 1848 | 0.7 | 1478.3 | 0.39 | 1.31 | 3.4% |
| door -x-y (y wall) 2 | 1719 | 0.9 | 1519.6 | 0.35 | 1.35 | 3.3% |
| door -x-y (y wall) 3 | 1204 | 0.9 | 1484.6 | 0.25 | 1.31 | 3.4% |
| door -x-y (y wall) 4 | 840 | 0.9 | 1460.5 | 0.18 | 1.35 | 3.4% |
| door -x-y (x wall) 0 | 1673 | 0.9 | 1327.2 | 0.39 | 1.41 | 3.7% |
| door -x-y (x wall) 1 | 1860 | 0.9 | 1466.2 | 0.40 | 1.31 | 3.4% |
| door -x-y (x wall) 2 | 1711 | 0.9 | 1505.9 | 0.35 | 1.28 | 3.3% |
| door -x-y (x wall) 3 | 1241 | 0.9 | 1466.6 | 0.26 | 1.35 | 3.4% |
| door -x-y (x wall) 4 | 813 | 0.7 | 1491.4 | 0.17 | 1.38 | 4.0% |
| door -x-y (corner) | 620 | 1.0 | 1059.2 | 0.18 | 0.81 | 0.0% |
| door +x-y (y wall) 0 | 1686 | 0.9 | 1323.9 | 0.40 | 1.35 | 3.0% |
| door +x-y (y wall) 1 | 1867 | 0.9 | 1662.7 | 0.35 | 1.28 | 3.0% |
| door +x-y (y wall) 2 | 1726 | 0.9 | 1714.6 | 0.31 | 1.28 | 2.9% |
| door +x-y (y wall) 3 | 1227 | 0.9 | 1784.0 | 0.21 | 1.31 | 2.8% |
| door +x-y (y wall) 4 | 839 | 0.9 | 1566.6 | 0.17 | 1.35 | 3.2% |
| door +x-y (x wall) 0 | 1658 | 0.9 | 1298.2 | 0.40 | 1.35 | 3.8% |
| door +x-y (x wall) 1 | 1867 | 0.9 | 1510.8 | 0.39 | 1.35 | 2.6% |
| door +x-y (x wall) 2 | 1719 | 0.7 | 1780.0 | 0.30 | 1.35 | 2.8% |
| door +x-y (x wall) 3 | 1181 | 0.7 | 1784.9 | 0.21 | 1.25 | 2.8% |
| door +x-y (x wall) 4 | 803 | 0.9 | 1714.4 | 0.15 | 1.35 | 2.9% |
| door +x-y (corner) | 610 | 1.0 | 1278.0 | 0.15 | 0.88 | 0.8% |

Mean flow / w J averaged over the doors 0.30, over the avenues 0.24.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 103.1 | 2313 | 1515 / 798 / 959 | 0.3 | 1200.4 | 2.73 | 4.71 | 93% | 85% | 7% | 4.44 |
| straight +x+y (y wing) 1 | 1.20 | 81.5 | 1838 | 1731 / 0 / 171 | 0.7 | 1434.8 | 1.33 | 2.31 | 92% | 78% | 15% | 3.91 |
| straight +x+y (y wing) 2 | 1.20 | 61.0 | 1555 | 1612 / 0 / 17 | 0.7 | 1467.5 | 1.11 | 1.91 | 82% | 69% | 13% | 3.74 |
| straight +x+y (y wing) 3 | 1.20 | 39.4 | 935 | 1112 / 0 / 23 | 0.7 | 1459.2 | 0.78 | 1.91 | 48% | 39% | 9% | 3.89 |
| straight +x+y (y wing) 4 | 1.20 | 18.8 | 403 | 666 / 0 / 21 | 0.7 | 1472.5 | 0.47 | 1.81 | 19% | 17% | 2% | 3.80 |
| straight +x+y (x wing) 0 | 1.20 | 103.1 | 2383 | 1556 / 827 / 1083 | 0.3 | 1195.7 | 2.90 | 5.32 | 92% | 85% | 8% | 4.25 |
| straight +x+y (x wing) 1 | 1.20 | 81.5 | 1825 | 1740 / 0 / 157 | 0.7 | 1459.6 | 1.30 | 2.51 | 93% | 74% | 19% | 3.68 |
| straight +x+y (x wing) 2 | 1.20 | 61.0 | 1477 | 1581 / 0 / 20 | 0.7 | 1478.1 | 1.08 | 1.71 | 75% | 66% | 9% | 3.67 |
| straight +x+y (x wing) 3 | 1.20 | 39.4 | 936 | 1169 / 0 / 17 | 0.7 | 1475.3 | 0.80 | 1.60 | 51% | 40% | 11% | 3.47 |
| straight +x+y (x wing) 4 | 1.20 | 18.8 | 401 | 712 / 0 / 13 | 0.7 | 1488.1 | 0.49 | 1.81 | 19% | 17% | 2% | 3.82 |
| corner +x+y | 1.20 | 186.0 | 1799 | 484 / 363 / 1339 | 0.7 | 1464.1 | 1.49 | 4.11 | 93% | 57% | 35% | 2.53 |
| straight -x+y (y wing) 0 | 1.20 | 103.1 | 2335 | 1532 / 803 / 1012 | 0.7 | 1156.0 | 2.90 | 5.22 | 92% | 87% | 5% | 4.24 |
| straight -x+y (y wing) 1 | 1.20 | 81.5 | 1853 | 1713 / 0 / 246 | 0.7 | 1440.9 | 1.36 | 2.51 | 91% | 68% | 23% | 3.51 |
| straight -x+y (y wing) 2 | 1.20 | 61.0 | 1530 | 1600 / 0 / 15 | 0.7 | 1497.9 | 1.08 | 1.91 | 78% | 66% | 12% | 3.64 |
| straight -x+y (y wing) 3 | 1.20 | 39.4 | 928 | 1189 / 0 / 17 | 0.7 | 1486.0 | 0.81 | 2.01 | 47% | 41% | 6% | 3.64 |
| straight -x+y (y wing) 4 | 1.20 | 18.8 | 401 | 620 / 0 / 52 | 0.7 | 1412.7 | 0.48 | 2.11 | 20% | 18% | 1% | 3.83 |
| straight -x+y (x wing) 0 | 1.20 | 103.1 | 2353 | 1548 / 808 / 1024 | 0.2 | 1170.7 | 2.89 | 5.02 | 92% | 88% | 4% | 4.43 |
| straight -x+y (x wing) 1 | 1.20 | 81.5 | 1876 | 1718 / 0 / 233 | 0.7 | 1413.9 | 1.38 | 2.41 | 92% | 68% | 24% | 3.63 |
| straight -x+y (x wing) 2 | 1.20 | 61.0 | 1490 | 1590 / 0 / 10 | 0.7 | 1482.9 | 1.08 | 1.81 | 77% | 64% | 13% | 3.72 |
| straight -x+y (x wing) 3 | 1.20 | 39.4 | 942 | 1205 / 0 / 8 | 0.7 | 1497.4 | 0.81 | 1.60 | 47% | 40% | 7% | 3.83 |
| straight -x+y (x wing) 4 | 1.20 | 18.8 | 402 | 658 / 0 / 20 | 0.7 | 1454.7 | 0.47 | 1.60 | 19% | 15% | 4% | 3.68 |
| corner -x+y | 1.20 | 186.0 | 1755 | 406 / 478 / 1396 | 0.7 | 1447.2 | 1.58 | 3.61 | 94% | 60% | 34% | 2.67 |
| straight -x-y (y wing) 0 | 1.20 | 103.1 | 2377 | 1554 / 824 / 919 | 0.5 | 1185.7 | 2.78 | 5.22 | 92% | 87% | 6% | 4.38 |
| straight -x-y (y wing) 1 | 1.20 | 81.5 | 1844 | 1747 / 0 / 169 | 0.7 | 1475.3 | 1.30 | 2.31 | 91% | 75% | 16% | 3.89 |
| straight -x-y (y wing) 2 | 1.20 | 61.0 | 1478 | 1611 / 0 / 10 | 0.7 | 1516.6 | 1.07 | 1.71 | 73% | 62% | 10% | 3.78 |
| straight -x-y (y wing) 3 | 1.20 | 39.4 | 954 | 1123 / 0 / 16 | 0.7 | 1481.6 | 0.77 | 1.71 | 48% | 41% | 7% | 3.70 |
| straight -x-y (y wing) 4 | 1.20 | 18.8 | 396 | 665 / 0 / 17 | 0.7 | 1457.5 | 0.47 | 1.60 | 18% | 17% | 1% | 3.99 |
| straight -x-y (x wing) 0 | 1.20 | 103.1 | 2348 | 1543 / 809 / 946 | 0.2 | 1170.0 | 2.82 | 5.52 | 92% | 86% | 6% | 4.26 |
| straight -x-y (x wing) 1 | 1.20 | 81.5 | 1827 | 1751 / 0 / 155 | 0.7 | 1463.3 | 1.30 | 2.31 | 92% | 76% | 16% | 3.77 |
| straight -x-y (x wing) 2 | 1.20 | 61.0 | 1543 | 1624 / 0 / 15 | 0.7 | 1503.0 | 1.09 | 1.60 | 79% | 68% | 11% | 3.78 |
| straight -x-y (x wing) 3 | 1.20 | 39.4 | 941 | 1119 / 0 / 26 | 0.7 | 1463.6 | 0.78 | 1.71 | 49% | 41% | 8% | 3.66 |
| straight -x-y (x wing) 4 | 1.20 | 18.8 | 404 | 660 / 0 / 21 | 0.7 | 1488.5 | 0.46 | 1.60 | 19% | 17% | 2% | 3.77 |
| corner -x-y | 1.20 | 186.0 | 1754 | 495 / 346 / 1287 | 0.7 | 1464.5 | 1.45 | 3.31 | 95% | 65% | 31% | 2.54 |
| straight +x-y (y wing) 0 | 1.20 | 103.1 | 2382 | 1570 / 812 / 1113 | 0.3 | 1202.1 | 2.91 | 5.32 | 93% | 86% | 7% | 4.14 |
| straight +x-y (y wing) 1 | 1.20 | 81.5 | 1862 | 1758 / 0 / 176 | 0.7 | 1659.7 | 1.17 | 2.51 | 83% | 67% | 16% | 3.73 |
| straight +x-y (y wing) 2 | 1.20 | 61.0 | 1492 | 1638 / 0 / 97 | 0.7 | 1711.6 | 1.01 | 2.71 | 65% | 58% | 7% | 3.88 |
| straight +x-y (y wing) 3 | 1.20 | 39.4 | 943 | 1124 / 0 / 23 | 0.7 | 1781.1 | 0.64 | 1.60 | 43% | 36% | 7% | 3.54 |
| straight +x-y (y wing) 4 | 1.20 | 18.8 | 399 | 669 / 0 / 28 | 0.7 | 1563.7 | 0.45 | 2.01 | 18% | 15% | 3% | 3.80 |
| straight +x-y (x wing) 0 | 1.20 | 103.1 | 2349 | 1536 / 813 / 936 | 0.3 | 1175.7 | 2.79 | 5.12 | 92% | 86% | 6% | 4.22 |
| straight +x-y (x wing) 1 | 1.20 | 81.5 | 1834 | 1759 / 0 / 173 | 0.7 | 1507.9 | 1.28 | 2.31 | 90% | 70% | 20% | 3.66 |
| straight +x-y (x wing) 2 | 1.20 | 61.0 | 1541 | 1642 / 0 / 51 | 0.7 | 1777.1 | 0.95 | 2.11 | 66% | 57% | 9% | 3.69 |
| straight +x-y (x wing) 3 | 1.20 | 39.4 | 925 | 1067 / 0 / 22 | 0.7 | 1781.9 | 0.61 | 1.71 | 39% | 36% | 3% | 3.75 |
| straight +x-y (x wing) 4 | 1.20 | 18.8 | 403 | 628 / 0 / 18 | 0.7 | 1711.5 | 0.38 | 1.71 | 16% | 13% | 3% | 3.71 |
| corner +x-y | 1.20 | 186.0 | 1735 | 482 / 367 / 1424 | 0.7 | 1731.9 | 1.31 | 3.71 | 87% | 63% | 24% | 2.46 |

The last agent out (agent 56763, t100 1784.9 s): last gangway straight +x-y (x wing) 3, exit door +x-y (x wall) 3. The gangway that cleared last: straight +x-y (x wing) 3 at 1781.9 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 8804 | 7800.4 | 7.10 | 1710.8 / 1679.6 / 1523.4 | 1694.3 / 1668.4 / 1500.2 | 7237941.3 | 13872351 | 0.166 |
| gangway | 3792 | 3512.9 | 7.10 | 1707.8 / 1679.5 / 1521.7 | 1694.3 / 1668.4 / 1500.2 | 7210812.4 | 12923473 | 0.101 |
| walkway | 276 | 257.4 | 5.27 | 767.0 / 506.0 / 18.9 | 381.8 / 233.7 / 6.3 | 169.2 | 88154 | 0.682 |
| avenue | 1920 | 1801.4 | 3.26 | 802.1 / 61.6 / 0.0 | 546.2 / 2.1 / 0.0 | 0.0 | 517271 | 1.334 |
| exit | 4 | 2.0 | 0.00 | 0.7 / 0.5 / 0.0 | 0.7 / 0.5 / 0.0 | 0.0 | 3 | 0.878 |
| concourse | 2812 | 2226.8 | 5.99 | 1458.4 / 77.3 / 52.3 | 1080.2 / 75.2 / 42.5 | 26959.7 | 343449 | 0.715 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 25392 | 16030.4 | 7.80 | 1507.9 / 1497.0 / 1403.5 | 1507.9 / 1495.1 / 1396.5 | 9239200.3 | 22751120 | 0.022 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 208 x 208 from (-104, -104) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 38.5 | -38.5 | gangway | 1.00 | 6.10 | 1597.2 | 1593.2 | 1446.0 | 8377.1 | 0.009 |
| 2 | 34.5 | -34.5 | gangway | 1.00 | 5.83 | 1547.6 | 1531.0 | 1455.4 | 8251.1 | 0.005 |
| 3 | 36.5 | -36.5 | gangway | 1.00 | 5.58 | 1576.4 | 1564.9 | 1476.2 | 8044.2 | 0.006 |
| 4 | 35.5 | -35.5 | gangway | 1.00 | 5.67 | 1562.6 | 1553.2 | 1430.9 | 7716.0 | 0.006 |
| 5 | 34.5 | 34.5 | gangway | 1.00 | 6.01 | 1373.0 | 1357.1 | 1317.6 | 7691.7 | 0.006 |
| 6 | -34.5 | -34.5 | gangway | 1.00 | 6.04 | 1400.1 | 1389.8 | 1356.6 | 7533.5 | 0.006 |
| 7 | -34.5 | 34.5 | gangway | 1.00 | 5.89 | 1384.4 | 1374.1 | 1345.2 | 7471.7 | 0.005 |
| 8 | -36.5 | -36.5 | gangway | 1.00 | 5.82 | 1414.6 | 1399.1 | 1317.0 | 7365.5 | 0.008 |
| 9 | 39.5 | -39.5 | gangway | 1.00 | 5.87 | 1606.3 | 1602.7 | 1368.3 | 7324.4 | 0.012 |
| 10 | 37.5 | -37.5 | gangway | 0.99 | 5.48 | 1588.3 | 1577.5 | 1420.2 | 7321.9 | 0.008 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 38.5 | -36.5 | seat row | 0.50 | 7.19 | 1502.6 | 1492.3 | 1396.5 | 4945.2 | 0.005 |
| 2 | 36.5 | -38.5 | seat row | 0.50 | 7.26 | 1490.0 | 1481.3 | 1360.9 | 4815.1 | 0.003 |
| 3 | -36.5 | -38.5 | seat row | 0.50 | 7.32 | 1351.2 | 1347.1 | 1331.4 | 4690.4 | 0.003 |
| 4 | -38.5 | -36.5 | seat row | 0.50 | 7.26 | 1388.2 | 1384.7 | 1336.1 | 4686.2 | 0.006 |
| 5 | -36.5 | 38.5 | seat row | 0.50 | 7.32 | 1347.0 | 1343.1 | 1328.4 | 4683.0 | 0.003 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 8271; agent-steps of seated agents on another row's clearway: 691641.

## Deposit check

Person-seconds deposited: 36629746.1, of them in excluded cells: 6274.729.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 9240038 overlapping pair-steps: p99 0.0020, max 0.0900 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0020 max 0.0900; venue-geometry 18: p99 0.0017 max 0.0017 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00765 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 79 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.46 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 3715 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
