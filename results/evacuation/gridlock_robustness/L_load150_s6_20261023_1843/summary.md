# Experiment `L_load150_s6`

**Task 5.11 stage 1 (gridlock robustness, default model, AMD 26.10.1): venue L, the achievable maximum 109.28% (150% requested, seed 6)**

Venue L (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (4000 x 4000), cache key a2f3aaf59c2252b7, content hash 022d17b202313d70). 69311 agents (load 109.3%, requested 150%): every one of the 63424 seats and 5887 standing (spawnOvercrowdedCrowd, seed 6; below), buffer N = 131072, 8658 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 12268490 evaluations, 678427 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.09)** (the L venue's design capacity 63424, jam capacity 171923: 23822.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `15aa31e8667e4a9417fde7884d907d1832c5e2d6`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-23T18:43:27, 1272.4 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Spawn (overcrowding)

| | |
|---|---|
| seated | 63424 (every seat) |
| standing | **5887** (requested round((1.50 - 1) x 63424) = 31712; at most 5887 = floor(2.5 p/m^2 x 2355.0 m^2)) |
| standing floor | walkway + rear concourse, 2355.0 m^2 |
| standing on the walkway / concourse / gangways | 623 / 5264 / 0 |
| **load** | **109.28%** of the seats (requested 150%; the floor takes no more: the achievable maximum) |
| standing crowd's mean density | 2.500 p/m^2 |
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 4.46, all circulation cells 4.46 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 6, 366788 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 2772 | 484.8 |
| t90 | 6183 | 1081.4 |
| t100 | 8658 | 1514.3 |

t_p: the step by which ceil(p x 69311) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 2152 | 88 | 60.2 | 1197.2 | 20.1 | 56.4 | 59.5-69.4 |
| -x | 5.66 | 2146 | 86 | 60.2 | 1190.2 | 20.1 | 58.5 | 60.0-70.0 |
| +y | 5.66 | 2212 | 89 | 60.2 | 1193.0 | 20.7 | 59.5 | 60.0-70.0 |
| -y | 5.66 | 2109 | 82 | 60.2 | 1197.6 | 19.7 | 58.5 | 59.8-69.8 |
| door +x+y (y wall) 0 | 2.30 | 1654 | 2722 | 1.0 | 1172.6 | 36.8 | 104.7 | 0.5-10.5 |
| door +x+y (y wall) 1 | 2.30 | 1832 | 2252 | 0.9 | 1446.1 | 33.1 | 109.9 | 18.4-28.3 |
| door +x+y (y wall) 2 | 2.30 | 1723 | 1707 | 0.9 | 1483.7 | 30.3 | 109.9 | 13.3-23.3 |
| door +x+y (y wall) 3 | 2.30 | 1236 | 1162 | 1.0 | 1474.3 | 21.9 | 109.9 | 20.1-30.1 |
| door +x+y (y wall) 4 | 2.30 | 800 | 641 | 0.7 | 1505.9 | 13.9 | 112.5 | 13.5-23.4 |
| door +x+y (x wall) 0 | 2.30 | 1667 | 2727 | 0.7 | 1218.2 | 35.7 | 112.5 | 10.7-20.6 |
| door +x+y (x wall) 1 | 2.30 | 1832 | 2256 | 0.9 | 1398.2 | 34.2 | 109.9 | 15.6-25.5 |
| door +x+y (x wall) 2 | 2.30 | 1727 | 1716 | 0.9 | 1505.1 | 29.9 | 107.3 | 13.5-23.4 |
| door +x+y (x wall) 3 | 2.30 | 1225 | 1156 | 0.9 | 1455.2 | 22.0 | 112.5 | 0.7-10.7 |
| door +x+y (x wall) 4 | 2.30 | 859 | 647 | 0.9 | 1475.7 | 15.2 | 112.5 | 15.9-25.9 |
| door +x+y (corner) | 2.30 | 573 | 248 | 0.9 | 1371.1 | 10.9 | 70.6 | 0.3-10.3 |
| door -x+y (y wall) 0 | 2.30 | 1685 | 2736 | 0.9 | 1287.0 | 34.2 | 109.9 | 11.7-21.7 |
| door -x+y (y wall) 1 | 2.30 | 1839 | 2255 | 0.9 | 1475.7 | 32.5 | 115.1 | 30.4-40.4 |
| door -x+y (y wall) 2 | 2.30 | 1689 | 1711 | 0.9 | 1510.8 | 29.2 | 112.5 | 21.9-31.8 |
| door -x+y (y wall) 3 | 2.30 | 1252 | 1161 | 1.0 | 1511.4 | 21.6 | 109.9 | 20.1-30.1 |
| door -x+y (y wall) 4 | 2.30 | 870 | 644 | 0.9 | 1487.6 | 15.3 | 115.1 | 23.8-33.8 |
| door -x+y (x wall) 0 | 2.30 | 1671 | 2736 | 0.9 | 1272.8 | 34.3 | 112.5 | 11.4-21.3 |
| door -x+y (x wall) 1 | 2.30 | 1838 | 2251 | 0.7 | 1470.8 | 32.6 | 109.9 | 1.0-11.0 |
| door -x+y (x wall) 2 | 2.30 | 1730 | 1715 | 0.7 | 1502.1 | 30.1 | 112.5 | 34.1-44.1 |
| door -x+y (x wall) 3 | 2.30 | 1223 | 1155 | 0.9 | 1514.3 | 21.1 | 112.5 | 6.8-16.8 |
| door -x+y (x wall) 4 | 2.30 | 859 | 644 | 0.9 | 1481.3 | 15.1 | 112.5 | 6.5-16.4 |
| door -x+y (corner) | 2.30 | 510 | 252 | 0.9 | 956.7 | 13.9 | 70.6 | 0.7-10.7 |
| door -x-y (y wall) 0 | 2.30 | 1692 | 2727 | 0.9 | 1274.4 | 34.7 | 112.5 | 14.3-24.3 |
| door -x-y (y wall) 1 | 2.30 | 1838 | 2257 | 0.7 | 1400.0 | 34.3 | 117.7 | 9.3-19.2 |
| door -x-y (y wall) 2 | 2.30 | 1665 | 1715 | 0.7 | 1445.1 | 30.1 | 104.7 | 18.5-28.5 |
| door -x-y (y wall) 3 | 2.30 | 1229 | 1164 | 0.9 | 1481.6 | 21.6 | 112.5 | 27.3-37.3 |
| door -x-y (y wall) 4 | 2.30 | 830 | 643 | 0.7 | 1482.0 | 14.6 | 115.1 | 39.9-49.8 |
| door -x-y (x wall) 0 | 2.30 | 1670 | 2727 | 0.9 | 1262.7 | 34.5 | 112.5 | 9.4-19.4 |
| door -x-y (x wall) 1 | 2.30 | 1841 | 2255 | 1.0 | 1429.2 | 33.6 | 115.1 | 15.6-25.5 |
| door -x-y (x wall) 2 | 2.30 | 1698 | 1707 | 0.9 | 1484.1 | 29.9 | 112.5 | 15.9-25.9 |
| door -x-y (x wall) 3 | 2.30 | 1221 | 1163 | 0.7 | 1482.9 | 21.5 | 109.9 | 11.0-21.0 |
| door -x-y (x wall) 4 | 2.30 | 895 | 644 | 0.9 | 1474.8 | 15.8 | 109.9 | 22.0-32.0 |
| door -x-y (corner) | 2.30 | 631 | 249 | 0.9 | 1235.7 | 13.3 | 70.6 | 0.5-10.5 |
| door +x-y (y wall) 0 | 2.30 | 1665 | 2726 | 0.9 | 1246.9 | 34.9 | 107.3 | 15.2-25.2 |
| door +x-y (y wall) 1 | 2.30 | 1818 | 2247 | 0.9 | 1413.8 | 33.6 | 109.9 | 28.0-38.0 |
| door +x-y (y wall) 2 | 2.30 | 1646 | 1707 | 0.9 | 1441.4 | 29.8 | 109.9 | 34.5-44.4 |
| door +x-y (y wall) 3 | 2.30 | 1231 | 1166 | 0.9 | 1482.0 | 21.7 | 109.9 | 28.0-38.0 |
| door +x-y (y wall) 4 | 2.30 | 924 | 645 | 0.9 | 1425.0 | 16.9 | 115.1 | 9.6-19.6 |
| door +x-y (x wall) 0 | 2.30 | 1692 | 2723 | 0.7 | 1278.0 | 34.6 | 109.9 | 14.0-24.0 |
| door +x-y (x wall) 1 | 2.30 | 1816 | 2256 | 0.7 | 1416.0 | 33.5 | 112.5 | 30.8-40.8 |
| door +x-y (x wall) 2 | 2.30 | 1614 | 1707 | 0.7 | 1480.8 | 28.4 | 112.5 | 18.4-28.3 |
| door +x-y (x wall) 3 | 2.30 | 1288 | 1163 | 0.7 | 1485.1 | 22.6 | 112.5 | 15.6-25.5 |
| door +x-y (x wall) 4 | 2.30 | 877 | 637 | 1.0 | 1455.4 | 15.7 | 115.1 | 19.6-29.6 |
| door +x-y (corner) | 2.30 | 617 | 244 | 0.9 | 1201.6 | 13.4 | 73.3 | 66.1-76.1 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (2.30 m; a corner door's: the gap between its wall ends, 2.30 m); agents are removed past the outer wall's outer face (92.71 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 2152 | 3.1% | 18.0% |
| -x | avenue | 5.66 | 2146 | 3.1% | 18.0% |
| +y | avenue | 5.66 | 2212 | 3.2% | 18.5% |
| -y | avenue | 5.66 | 2109 | 3.0% | 17.7% |
| door +x+y (y wall) 0 | door | 2.30 | 1654 | 2.4% | 34.1% |
| door +x+y (y wall) 1 | door | 2.30 | 1832 | 2.6% | 37.8% |
| door +x+y (y wall) 2 | door | 2.30 | 1723 | 2.5% | 35.5% |
| door +x+y (y wall) 3 | door | 2.30 | 1236 | 1.8% | 25.5% |
| door +x+y (y wall) 4 | door | 2.30 | 800 | 1.2% | 16.5% |
| door +x+y (x wall) 0 | door | 2.30 | 1667 | 2.4% | 34.4% |
| door +x+y (x wall) 1 | door | 2.30 | 1832 | 2.6% | 37.8% |
| door +x+y (x wall) 2 | door | 2.30 | 1727 | 2.5% | 35.6% |
| door +x+y (x wall) 3 | door | 2.30 | 1225 | 1.8% | 25.2% |
| door +x+y (x wall) 4 | door | 2.30 | 859 | 1.2% | 17.7% |
| door +x+y (corner) | door | 2.30 | 573 | 0.8% | 11.8% |
| door -x+y (y wall) 0 | door | 2.30 | 1685 | 2.4% | 34.7% |
| door -x+y (y wall) 1 | door | 2.30 | 1839 | 2.7% | 37.9% |
| door -x+y (y wall) 2 | door | 2.30 | 1689 | 2.4% | 34.8% |
| door -x+y (y wall) 3 | door | 2.30 | 1252 | 1.8% | 25.8% |
| door -x+y (y wall) 4 | door | 2.30 | 870 | 1.3% | 17.9% |
| door -x+y (x wall) 0 | door | 2.30 | 1671 | 2.4% | 34.4% |
| door -x+y (x wall) 1 | door | 2.30 | 1838 | 2.7% | 37.9% |
| door -x+y (x wall) 2 | door | 2.30 | 1730 | 2.5% | 35.6% |
| door -x+y (x wall) 3 | door | 2.30 | 1223 | 1.8% | 25.2% |
| door -x+y (x wall) 4 | door | 2.30 | 859 | 1.2% | 17.7% |
| door -x+y (corner) | door | 2.30 | 510 | 0.7% | 10.5% |
| door -x-y (y wall) 0 | door | 2.30 | 1692 | 2.4% | 34.9% |
| door -x-y (y wall) 1 | door | 2.30 | 1838 | 2.7% | 37.9% |
| door -x-y (y wall) 2 | door | 2.30 | 1665 | 2.4% | 34.3% |
| door -x-y (y wall) 3 | door | 2.30 | 1229 | 1.8% | 25.3% |
| door -x-y (y wall) 4 | door | 2.30 | 830 | 1.2% | 17.1% |
| door -x-y (x wall) 0 | door | 2.30 | 1670 | 2.4% | 34.4% |
| door -x-y (x wall) 1 | door | 2.30 | 1841 | 2.7% | 37.9% |
| door -x-y (x wall) 2 | door | 2.30 | 1698 | 2.4% | 35.0% |
| door -x-y (x wall) 3 | door | 2.30 | 1221 | 1.8% | 25.2% |
| door -x-y (x wall) 4 | door | 2.30 | 895 | 1.3% | 18.4% |
| door -x-y (corner) | door | 2.30 | 631 | 0.9% | 13.0% |
| door +x-y (y wall) 0 | door | 2.30 | 1665 | 2.4% | 34.3% |
| door +x-y (y wall) 1 | door | 2.30 | 1818 | 2.6% | 37.5% |
| door +x-y (y wall) 2 | door | 2.30 | 1646 | 2.4% | 33.9% |
| door +x-y (y wall) 3 | door | 2.30 | 1231 | 1.8% | 25.4% |
| door +x-y (y wall) 4 | door | 2.30 | 924 | 1.3% | 19.0% |
| door +x-y (x wall) 0 | door | 2.30 | 1692 | 2.4% | 34.9% |
| door +x-y (x wall) 1 | door | 2.30 | 1816 | 2.6% | 37.4% |
| door +x-y (x wall) 2 | door | 2.30 | 1614 | 2.3% | 33.3% |
| door +x-y (x wall) 3 | door | 2.30 | 1288 | 1.9% | 26.5% |
| door +x-y (x wall) 4 | door | 2.30 | 877 | 1.3% | 18.1% |
| door +x-y (corner) | door | 2.30 | 617 | 0.9% | 12.7% |
| **doors (44)** | door | 101.20 | 60692 | 87.6% | |
| **avenues (4)** | avenue | 22.64 | 8619 | 12.4% | |

**Unused exit width: 0.0 of 123.8 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 1514.3 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 26.5%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 2376 | 3.4% | 2376 | 3.4% |
| straight +x+y (y wing) 1 | straight | yes | 1861 | 2.7% | 1717 | 2.5% |
| straight +x+y (y wing) 2 | straight | yes | 1618 | 2.3% | 1613 | 2.3% |
| straight +x+y (y wing) 3 | straight | yes | 1163 | 1.7% | 1158 | 1.7% |
| straight +x+y (y wing) 4 | straight | yes | 650 | 0.9% | 630 | 0.9% |
| straight +x+y (x wing) 0 | straight | yes | 2354 | 3.4% | 2354 | 3.4% |
| straight +x+y (x wing) 1 | straight | yes | 1849 | 2.7% | 1716 | 2.5% |
| straight +x+y (x wing) 2 | straight | yes | 1630 | 2.4% | 1624 | 2.3% |
| straight +x+y (x wing) 3 | straight | yes | 1144 | 1.7% | 1140 | 1.6% |
| straight +x+y (x wing) 4 | straight | yes | 699 | 1.0% | 680 | 1.0% |
| corner +x+y | corner | yes | 2112 | 3.0% | 858 | 1.2% |
| straight -x+y (y wing) 0 | straight | yes | 2380 | 3.4% | 2380 | 3.4% |
| straight -x+y (y wing) 1 | straight | yes | 1860 | 2.7% | 1726 | 2.5% |
| straight -x+y (y wing) 2 | straight | yes | 1594 | 2.3% | 1586 | 2.3% |
| straight -x+y (y wing) 3 | straight | yes | 1170 | 1.7% | 1161 | 1.7% |
| straight -x+y (y wing) 4 | straight | yes | 715 | 1.0% | 700 | 1.0% |
| straight -x+y (x wing) 0 | straight | yes | 2338 | 3.4% | 2338 | 3.4% |
| straight -x+y (x wing) 1 | straight | yes | 1861 | 2.7% | 1731 | 2.5% |
| straight -x+y (x wing) 2 | straight | yes | 1637 | 2.4% | 1630 | 2.4% |
| straight -x+y (x wing) 3 | straight | yes | 1126 | 1.6% | 1110 | 1.6% |
| straight -x+y (x wing) 4 | straight | yes | 719 | 1.0% | 710 | 1.0% |
| corner -x+y | corner | yes | 2119 | 3.1% | 793 | 1.1% |
| straight -x-y (y wing) 0 | straight | yes | 2380 | 3.4% | 2380 | 3.4% |
| straight -x-y (y wing) 1 | straight | yes | 1834 | 2.6% | 1722 | 2.5% |
| straight -x-y (y wing) 2 | straight | yes | 1587 | 2.3% | 1564 | 2.3% |
| straight -x-y (y wing) 3 | straight | yes | 1151 | 1.7% | 1132 | 1.6% |
| straight -x-y (y wing) 4 | straight | yes | 680 | 1.0% | 658 | 0.9% |
| straight -x-y (x wing) 0 | straight | yes | 2377 | 3.4% | 2377 | 3.4% |
| straight -x-y (x wing) 1 | straight | yes | 1833 | 2.6% | 1728 | 2.5% |
| straight -x-y (x wing) 2 | straight | yes | 1629 | 2.4% | 1607 | 2.3% |
| straight -x-y (x wing) 3 | straight | yes | 1124 | 1.6% | 1111 | 1.6% |
| straight -x-y (x wing) 4 | straight | yes | 749 | 1.1% | 734 | 1.1% |
| corner -x-y | corner | yes | 2146 | 3.1% | 851 | 1.2% |
| straight +x-y (y wing) 0 | straight | yes | 2345 | 3.4% | 2345 | 3.4% |
| straight +x-y (y wing) 1 | straight | yes | 1826 | 2.6% | 1711 | 2.5% |
| straight +x-y (y wing) 2 | straight | yes | 1605 | 2.3% | 1567 | 2.3% |
| straight +x-y (y wing) 3 | straight | yes | 1135 | 1.6% | 1119 | 1.6% |
| straight +x-y (y wing) 4 | straight | yes | 768 | 1.1% | 749 | 1.1% |
| straight +x-y (x wing) 0 | straight | yes | 2395 | 3.5% | 2395 | 3.5% |
| straight +x-y (x wing) 1 | straight | yes | 1819 | 2.6% | 1705 | 2.5% |
| straight +x-y (x wing) 2 | straight | yes | 1581 | 2.3% | 1562 | 2.3% |
| straight +x-y (x wing) 3 | straight | yes | 1149 | 1.7% | 1134 | 1.6% |
| straight +x-y (x wing) 4 | straight | yes | 747 | 1.1% | 728 | 1.1% |
| corner +x-y | corner | yes | 2181 | 3.1% | 849 | 1.2% |
| **straight (40)** | | | 61458 | | 60108 | 86.7% |
| **corner (4)** | | | 8558 | | 3351 | 4.8% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 5852, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 2152 | 60.2 | 1197.2 | 0.24 | 0.67 | 0.0% |
| -x | 2146 | 60.2 | 1190.2 | 0.24 | 0.70 | 0.0% |
| +y | 2212 | 60.2 | 1193.0 | 0.25 | 0.71 | 0.0% |
| -y | 2109 | 60.2 | 1197.6 | 0.24 | 0.70 | 0.0% |
| door +x+y (y wall) 0 | 1654 | 1.0 | 1172.6 | 0.44 | 1.25 | 4.2% |
| door +x+y (y wall) 1 | 1832 | 0.9 | 1446.1 | 0.40 | 1.31 | 3.4% |
| door +x+y (y wall) 2 | 1723 | 0.9 | 1483.7 | 0.36 | 1.31 | 3.4% |
| door +x+y (y wall) 3 | 1236 | 1.0 | 1474.3 | 0.26 | 1.31 | 3.4% |
| door +x+y (y wall) 4 | 800 | 0.7 | 1505.9 | 0.17 | 1.35 | 3.3% |
| door +x+y (x wall) 0 | 1667 | 0.7 | 1218.2 | 0.43 | 1.35 | 4.1% |
| door +x+y (x wall) 1 | 1832 | 0.9 | 1398.2 | 0.41 | 1.31 | 3.5% |
| door +x+y (x wall) 2 | 1727 | 0.9 | 1505.1 | 0.36 | 1.28 | 3.3% |
| door +x+y (x wall) 3 | 1225 | 0.9 | 1455.2 | 0.26 | 1.35 | 3.4% |
| door +x+y (x wall) 4 | 859 | 0.9 | 1475.7 | 0.18 | 1.35 | 4.0% |
| door +x+y (corner) | 573 | 0.9 | 1371.1 | 0.13 | 0.85 | 1.4% |
| door -x+y (y wall) 0 | 1685 | 0.9 | 1287.0 | 0.41 | 1.31 | 3.8% |
| door -x+y (y wall) 1 | 1839 | 0.9 | 1475.7 | 0.39 | 1.38 | 3.4% |
| door -x+y (y wall) 2 | 1689 | 0.9 | 1510.8 | 0.35 | 1.35 | 3.3% |
| door -x+y (y wall) 3 | 1252 | 1.0 | 1511.4 | 0.26 | 1.31 | 3.3% |
| door -x+y (y wall) 4 | 870 | 0.9 | 1487.6 | 0.18 | 1.38 | 3.3% |
| door -x+y (x wall) 0 | 1671 | 0.9 | 1272.8 | 0.41 | 1.35 | 3.9% |
| door -x+y (x wall) 1 | 1838 | 0.7 | 1470.8 | 0.39 | 1.31 | 3.4% |
| door -x+y (x wall) 2 | 1730 | 0.7 | 1502.1 | 0.36 | 1.35 | 3.3% |
| door -x+y (x wall) 3 | 1223 | 0.9 | 1514.3 | 0.25 | 1.35 | 3.3% |
| door -x+y (x wall) 4 | 859 | 0.9 | 1481.3 | 0.18 | 1.35 | 3.4% |
| door -x+y (corner) | 510 | 0.9 | 956.7 | 0.17 | 0.85 | 2.1% |
| door -x-y (y wall) 0 | 1692 | 0.9 | 1274.4 | 0.41 | 1.35 | 3.9% |
| door -x-y (y wall) 1 | 1838 | 0.7 | 1400.0 | 0.41 | 1.41 | 3.5% |
| door -x-y (y wall) 2 | 1665 | 0.7 | 1445.1 | 0.36 | 1.25 | 3.4% |
| door -x-y (y wall) 3 | 1229 | 0.9 | 1481.6 | 0.26 | 1.35 | 3.4% |
| door -x-y (y wall) 4 | 830 | 0.7 | 1482.0 | 0.17 | 1.38 | 3.4% |
| door -x-y (x wall) 0 | 1670 | 0.9 | 1262.7 | 0.41 | 1.35 | 3.9% |
| door -x-y (x wall) 1 | 1841 | 1.0 | 1429.2 | 0.40 | 1.38 | 3.5% |
| door -x-y (x wall) 2 | 1698 | 0.9 | 1484.1 | 0.36 | 1.35 | 2.7% |
| door -x-y (x wall) 3 | 1221 | 0.7 | 1482.9 | 0.26 | 1.31 | 3.4% |
| door -x-y (x wall) 4 | 895 | 0.9 | 1474.8 | 0.19 | 1.31 | 4.1% |
| door -x-y (corner) | 631 | 0.9 | 1235.7 | 0.16 | 0.85 | 0.8% |
| door +x-y (y wall) 0 | 1665 | 0.9 | 1246.9 | 0.42 | 1.28 | 4.0% |
| door +x-y (y wall) 1 | 1818 | 0.9 | 1413.8 | 0.40 | 1.31 | 3.5% |
| door +x-y (y wall) 2 | 1646 | 0.9 | 1441.4 | 0.36 | 1.31 | 3.4% |
| door +x-y (y wall) 3 | 1231 | 0.9 | 1482.0 | 0.26 | 1.31 | 3.4% |
| door +x-y (y wall) 4 | 924 | 0.9 | 1425.0 | 0.20 | 1.38 | 3.5% |
| door +x-y (x wall) 0 | 1692 | 0.7 | 1278.0 | 0.41 | 1.31 | 3.9% |
| door +x-y (x wall) 1 | 1816 | 0.7 | 1416.0 | 0.40 | 1.35 | 3.5% |
| door +x-y (x wall) 2 | 1614 | 0.7 | 1480.8 | 0.34 | 1.35 | 3.4% |
| door +x-y (x wall) 3 | 1288 | 0.7 | 1485.1 | 0.27 | 1.35 | 3.4% |
| door +x-y (x wall) 4 | 877 | 1.0 | 1455.4 | 0.19 | 1.38 | 3.4% |
| door +x-y (corner) | 617 | 0.9 | 1201.6 | 0.16 | 0.88 | 1.7% |

Mean flow / w J averaged over the doors 0.31, over the avenues 0.24.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 103.1 | 2376 | 1544 / 832 / 987 | 0.2 | 1169.6 | 2.88 | 5.02 | 91% | 88% | 3% | 4.40 |
| straight +x+y (y wing) 1 | 1.20 | 81.5 | 1845 | 1717 / 0 / 204 | 0.7 | 1443.2 | 1.33 | 2.31 | 93% | 72% | 21% | 3.65 |
| straight +x+y (y wing) 2 | 1.20 | 61.0 | 1499 | 1613 / 0 / 11 | 0.7 | 1480.8 | 1.10 | 1.91 | 74% | 64% | 11% | 3.83 |
| straight +x+y (y wing) 3 | 1.20 | 39.4 | 938 | 1158 / 0 / 15 | 0.7 | 1471.3 | 0.80 | 1.60 | 51% | 43% | 9% | 3.64 |
| straight +x+y (y wing) 4 | 1.20 | 18.8 | 405 | 630 / 0 / 22 | 0.7 | 1503.0 | 0.43 | 1.71 | 19% | 16% | 3% | 3.67 |
| straight +x+y (x wing) 0 | 1.20 | 103.1 | 2354 | 1549 / 805 / 1121 | 0.3 | 1171.7 | 2.97 | 5.02 | 92% | 88% | 3% | 4.41 |
| straight +x+y (x wing) 1 | 1.20 | 81.5 | 1824 | 1716 / 0 / 181 | 0.7 | 1395.2 | 1.36 | 2.21 | 91% | 76% | 15% | 3.85 |
| straight +x+y (x wing) 2 | 1.20 | 61.0 | 1547 | 1624 / 0 / 11 | 0.7 | 1502.1 | 1.09 | 1.60 | 80% | 68% | 13% | 3.62 |
| straight +x+y (x wing) 3 | 1.20 | 39.4 | 930 | 1140 / 0 / 6 | 0.7 | 1452.3 | 0.79 | 1.60 | 52% | 40% | 12% | 3.51 |
| straight +x+y (x wing) 4 | 1.20 | 18.8 | 400 | 680 / 0 / 24 | 0.7 | 1472.7 | 0.48 | 1.81 | 20% | 16% | 3% | 3.67 |
| corner +x+y | 1.20 | 186.0 | 1748 | 449 / 409 / 1309 | 0.7 | 1479.0 | 1.47 | 3.61 | 91% | 66% | 26% | 2.64 |
| straight -x+y (y wing) 0 | 1.20 | 103.1 | 2380 | 1560 / 820 / 1118 | 0.2 | 1182.7 | 2.96 | 4.71 | 92% | 86% | 7% | 4.20 |
| straight -x+y (y wing) 1 | 1.20 | 81.5 | 1846 | 1726 / 0 / 192 | 0.7 | 1472.9 | 1.30 | 2.01 | 87% | 73% | 14% | 3.78 |
| straight -x+y (y wing) 2 | 1.20 | 61.0 | 1485 | 1586 / 0 / 10 | 0.7 | 1507.9 | 1.06 | 1.60 | 76% | 63% | 12% | 3.68 |
| straight -x+y (y wing) 3 | 1.20 | 39.4 | 944 | 1161 / 0 / 12 | 0.7 | 1508.4 | 0.78 | 1.81 | 48% | 39% | 9% | 3.66 |
| straight -x+y (y wing) 4 | 1.20 | 18.8 | 398 | 700 / 0 / 24 | 0.7 | 1484.6 | 0.49 | 1.81 | 18% | 15% | 3% | 3.82 |
| straight -x+y (x wing) 0 | 1.20 | 103.1 | 2338 | 1543 / 795 / 916 | 0.3 | 1172.6 | 2.78 | 5.02 | 92% | 88% | 4% | 4.49 |
| straight -x+y (x wing) 1 | 1.20 | 81.5 | 1842 | 1731 / 0 / 167 | 0.7 | 1467.8 | 1.29 | 2.11 | 89% | 73% | 16% | 3.89 |
| straight -x+y (x wing) 2 | 1.20 | 61.0 | 1545 | 1630 / 0 / 20 | 0.7 | 1499.1 | 1.10 | 1.81 | 79% | 67% | 12% | 3.79 |
| straight -x+y (x wing) 3 | 1.20 | 39.4 | 930 | 1110 / 0 / 19 | 0.7 | 1511.4 | 0.75 | 1.81 | 56% | 41% | 15% | 3.20 |
| straight -x+y (x wing) 4 | 1.20 | 18.8 | 403 | 710 / 0 / 12 | 0.7 | 1478.3 | 0.49 | 1.71 | 19% | 15% | 3% | 3.69 |
| corner -x+y | 1.20 | 186.0 | 1754 | 382 / 411 / 1389 | 0.7 | 1461.2 | 1.49 | 3.51 | 93% | 61% | 31% | 2.61 |
| straight -x-y (y wing) 0 | 1.20 | 103.1 | 2380 | 1572 / 811 / 994 | 0.3 | 1198.6 | 2.82 | 4.71 | 92% | 86% | 6% | 4.36 |
| straight -x-y (y wing) 1 | 1.20 | 81.5 | 1823 | 1722 / 0 / 152 | 0.7 | 1397.0 | 1.34 | 2.41 | 92% | 80% | 12% | 4.03 |
| straight -x-y (y wing) 2 | 1.20 | 61.0 | 1496 | 1564 / 0 / 25 | 0.7 | 1442.1 | 1.10 | 1.71 | 79% | 68% | 11% | 3.80 |
| straight -x-y (y wing) 3 | 1.20 | 39.4 | 928 | 1132 / 0 / 21 | 0.7 | 1478.7 | 0.78 | 1.71 | 47% | 40% | 7% | 3.80 |
| straight -x-y (y wing) 4 | 1.20 | 18.8 | 415 | 658 / 0 / 27 | 0.7 | 1479.2 | 0.46 | 1.81 | 19% | 17% | 3% | 3.75 |
| straight -x-y (x wing) 0 | 1.20 | 103.1 | 2377 | 1549 / 828 / 971 | 0.5 | 1198.8 | 2.79 | 5.32 | 92% | 84% | 7% | 4.09 |
| straight -x-y (x wing) 1 | 1.20 | 81.5 | 1817 | 1728 / 0 / 165 | 0.7 | 1426.2 | 1.33 | 2.31 | 92% | 76% | 16% | 3.79 |
| straight -x-y (x wing) 2 | 1.20 | 61.0 | 1508 | 1607 / 0 / 29 | 0.7 | 1481.1 | 1.10 | 1.91 | 75% | 68% | 7% | 3.83 |
| straight -x-y (x wing) 3 | 1.20 | 39.4 | 924 | 1111 / 0 / 22 | 0.7 | 1479.9 | 0.77 | 1.60 | 48% | 39% | 9% | 3.61 |
| straight -x-y (x wing) 4 | 1.20 | 18.8 | 399 | 734 / 0 / 15 | 0.7 | 1471.8 | 0.51 | 1.71 | 19% | 17% | 2% | 3.78 |
| corner -x-y | 1.20 | 186.0 | 1797 | 506 / 345 / 1353 | 0.7 | 1455.2 | 1.52 | 4.01 | 92% | 58% | 34% | 2.57 |
| straight +x-y (y wing) 0 | 1.20 | 103.1 | 2345 | 1547 / 798 / 1097 | 0.5 | 1205.8 | 2.86 | 5.22 | 93% | 84% | 9% | 4.09 |
| straight +x-y (y wing) 1 | 1.20 | 81.5 | 1813 | 1711 / 0 / 146 | 0.7 | 1410.8 | 1.32 | 2.11 | 93% | 80% | 13% | 3.92 |
| straight +x-y (y wing) 2 | 1.20 | 61.0 | 1543 | 1567 / 0 / 47 | 0.7 | 1438.4 | 1.12 | 1.71 | 82% | 72% | 10% | 3.75 |
| straight +x-y (y wing) 3 | 1.20 | 39.4 | 934 | 1119 / 0 / 22 | 0.7 | 1479.0 | 0.77 | 1.71 | 48% | 42% | 7% | 3.66 |
| straight +x-y (y wing) 4 | 1.20 | 18.8 | 415 | 749 / 0 / 24 | 0.7 | 1422.0 | 0.54 | 1.91 | 20% | 17% | 3% | 3.75 |
| straight +x-y (x wing) 0 | 1.20 | 103.1 | 2395 | 1567 / 828 / 1021 | 0.5 | 1207.6 | 2.83 | 5.22 | 92% | 84% | 8% | 4.23 |
| straight +x-y (x wing) 1 | 1.20 | 81.5 | 1802 | 1705 / 0 / 149 | 0.7 | 1413.1 | 1.31 | 2.11 | 92% | 76% | 15% | 3.85 |
| straight +x-y (x wing) 2 | 1.20 | 61.0 | 1482 | 1562 / 0 / 24 | 0.7 | 1478.0 | 1.07 | 1.71 | 77% | 67% | 9% | 3.79 |
| straight +x-y (x wing) 3 | 1.20 | 39.4 | 945 | 1134 / 0 / 18 | 0.7 | 1482.2 | 0.78 | 1.60 | 49% | 41% | 8% | 3.58 |
| straight +x-y (x wing) 4 | 1.20 | 18.8 | 395 | 728 / 0 / 20 | 0.7 | 1452.6 | 0.52 | 1.81 | 18% | 16% | 3% | 3.83 |
| corner +x-y | 1.20 | 186.0 | 1795 | 497 / 352 / 1379 | 0.7 | 1432.0 | 1.56 | 4.31 | 94% | 56% | 38% | 2.49 |

The last agent out (agent 24462, t100 1514.3 s): last gangway straight -x+y (x wing) 3, exit door -x+y (x wall) 3. The gangway that cleared last: straight -x+y (x wing) 3 at 1511.4 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 8804 | 7800.4 | 6.93 | 1507.9 / 1417.8 / 1370.2 | 1418.7 / 1395.2 / 1339.3 | 7270016.1 | 13807721 | 0.167 |
| gangway | 3792 | 3512.9 | 6.93 | 1506.6 / 1417.6 / 1368.5 | 1418.7 / 1395.2 / 1339.3 | 7242260.9 | 12860674 | 0.102 |
| walkway | 276 | 257.4 | 5.35 | 738.6 / 467.7 / 26.6 | 384.6 / 202.0 / 11.7 | 207.3 | 87267 | 0.688 |
| avenue | 1920 | 1801.4 | 3.10 | 779.9 / 57.7 / 0.0 | 533.1 / 1.7 / 0.0 | 0.0 | 516533 | 1.334 |
| exit | 4 | 2.0 | 0.00 | 0.7 / 0.0 / 0.0 | 0.7 / 0.0 / 0.0 | 0.0 | 3 | 0.926 |
| concourse | 2812 | 2226.8 | 6.11 | 1424.1 / 75.6 / 50.0 | 1062.9 / 72.8 / 42.3 | 27547.9 | 343244 | 0.713 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 25392 | 16030.4 | 7.89 | 1359.9 / 1357.3 / 1344.5 | 1359.9 / 1357.3 / 1337.5 | 9255030.2 | 22762258 | 0.022 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 208 x 208 from (-104, -104) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 34.5 | -34.5 | gangway | 1.00 | 6.00 | 1364.1 | 1345.4 | 1309.2 | 7626.8 | 0.007 |
| 2 | -35.5 | 35.5 | gangway | 1.00 | 5.84 | 1399.1 | 1393.5 | 1331.2 | 7547.7 | 0.008 |
| 3 | 34.5 | 34.5 | gangway | 1.00 | 5.76 | 1387.7 | 1375.5 | 1335.8 | 7503.8 | 0.007 |
| 4 | -36.5 | 36.5 | gangway | 1.00 | 5.76 | 1403.5 | 1395.2 | 1295.9 | 7357.0 | 0.007 |
| 5 | 35.5 | 35.5 | gangway | 1.00 | 5.65 | 1396.1 | 1386.7 | 1305.9 | 7203.7 | 0.008 |
| 6 | 32.5 | -32.5 | gangway | 1.00 | 6.07 | 1350.1 | 1344.2 | 1302.7 | 7163.7 | 0.005 |
| 7 | -38.5 | 38.5 | gangway | 1.00 | 5.94 | 1413.4 | 1388.8 | 1237.8 | 7141.8 | 0.013 |
| 8 | -34.5 | -34.5 | gangway | 1.00 | 5.87 | 1363.0 | 1352.0 | 1258.1 | 7026.1 | 0.008 |
| 9 | -39.5 | 39.5 | gangway | 1.00 | 5.76 | 1418.7 | 1356.6 | 1241.5 | 7018.7 | 0.017 |
| 10 | 39.5 | 39.5 | gangway | 1.00 | 5.72 | 1407.6 | 1349.9 | 1249.9 | 6977.4 | 0.016 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 36.5 | 38.5 | seat row | 0.50 | 7.47 | 1354.1 | 1351.5 | 1331.6 | 4833.1 | 0.003 |
| 2 | -36.5 | 38.5 | seat row | 0.50 | 7.34 | 1357.5 | 1344.7 | 1327.9 | 4802.5 | 0.003 |
| 3 | 38.5 | 36.5 | seat row | 0.50 | 7.27 | 1346.3 | 1339.4 | 1320.5 | 4710.7 | 0.003 |
| 4 | -38.5 | 36.5 | seat row | 0.50 | 7.18 | 1359.9 | 1357.3 | 1337.5 | 4662.0 | 0.003 |
| 5 | 42.5 | -25.5 | seat row | 0.64 | 6.83 | 1141.1 | 1135.8 | 1122.9 | 4578.9 | 0.011 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 8424; agent-steps of seated agents on another row's clearway: 482605.

## Deposit check

Person-seconds deposited: 36576239.2, of them in excluded cells: 6259.930.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 9719188 overlapping pair-steps: p99 0.0020, max 0.0566 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0020 max 0.0566; venue-geometry 19: p99 0.0033 max 0.0033 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00772 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 67 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.54 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 3716 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
