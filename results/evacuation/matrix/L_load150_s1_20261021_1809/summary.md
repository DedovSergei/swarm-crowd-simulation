# Experiment `L_load150_s1`

**Task 5.9 stage 4: venue L, 150% requested (seed 1): every seat + standing on the walkway and concourse (M, L: the achievable maximum, also the 125% request)**

Venue L (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (4000 x 4000), cache key a2f3aaf59c2252b7, content hash 022d17b202313d70). 69311 agents (load 109.3%, requested 150%): every one of the 63424 seats and 5887 standing (spawnOvercrowdedCrowd, seed 1; below), buffer N = 131072, 8759 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 12307192 evaluations, 692663 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.09)** (the L venue's design capacity 63424, jam capacity 171923: 23822.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-21T18:09:25, 1137.3 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Spawn (overcrowding)

| | |
|---|---|
| seated | 63424 (every seat) |
| standing | **5887** (requested round((1.50 - 1) x 63424) = 31712; at most 5887 = floor(2.5 p/m^2 x 2355.0 m^2)) |
| standing floor | walkway + rear concourse, 2355.0 m^2 |
| standing on the walkway / concourse / gangways | 608 / 5279 / 0 |
| **load** | **109.28%** of the seats (requested 150%; the floor takes no more: the achievable maximum) |
| standing crowd's mean density | 2.500 p/m^2 |
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 4.06, all circulation cells 4.06 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 1, 349703 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 2763 | 483.3 |
| t90 | 6237 | 1090.9 |
| t100 | 8759 | 1532.0 |

t_p: the step by which ceil(p x 69311) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 2145 | 82 | 60.2 | 1226.8 | 19.5 | 55.3 | 59.6-69.6 |
| -x | 5.66 | 2155 | 86 | 60.2 | 1210.2 | 19.9 | 59.5 | 59.5-69.4 |
| +y | 5.66 | 2117 | 81 | 60.2 | 1224.7 | 19.3 | 60.6 | 60.0-70.0 |
| -y | 5.66 | 2144 | 85 | 60.2 | 1237.6 | 19.3 | 63.8 | 59.8-69.8 |
| door +x+y (y wall) 0 | 2.30 | 1686 | 2726 | 0.9 | 1203.4 | 36.6 | 109.9 | 32.5-42.5 |
| door +x+y (y wall) 1 | 2.30 | 1823 | 2254 | 0.9 | 1409.0 | 33.8 | 107.3 | 37.3-47.2 |
| door +x+y (y wall) 2 | 2.30 | 1666 | 1712 | 1.0 | 1482.5 | 29.3 | 104.7 | 0.9-10.8 |
| door +x+y (y wall) 3 | 2.30 | 1139 | 1157 | 0.9 | 1446.1 | 20.6 | 109.9 | 20.3-30.3 |
| door +x+y (y wall) 4 | 2.30 | 911 | 639 | 0.9 | 1353.6 | 17.6 | 112.5 | 12.1-22.0 |
| door +x+y (x wall) 0 | 2.30 | 1654 | 2732 | 0.9 | 1303.4 | 33.1 | 107.3 | 22.6-32.5 |
| door +x+y (x wall) 1 | 2.30 | 1821 | 2251 | 0.9 | 1427.8 | 33.3 | 112.5 | 23.4-33.4 |
| door +x+y (x wall) 2 | 2.30 | 1682 | 1711 | 0.9 | 1446.5 | 30.3 | 112.5 | 11.4-21.3 |
| door +x+y (x wall) 3 | 2.30 | 1234 | 1158 | 0.9 | 1463.6 | 22.0 | 109.9 | 0.5-10.5 |
| door +x+y (x wall) 4 | 2.30 | 877 | 641 | 0.9 | 1481.3 | 15.5 | 109.9 | 32.9-42.9 |
| door +x+y (corner) | 2.30 | 680 | 260 | 0.7 | 1003.3 | 17.7 | 70.6 | 34.5-44.4 |
| door -x+y (y wall) 0 | 2.30 | 1654 | 2734 | 0.9 | 1295.4 | 33.3 | 109.9 | 11.0-21.0 |
| door -x+y (y wall) 1 | 2.30 | 1828 | 2259 | 1.0 | 1441.1 | 33.1 | 115.1 | 31.7-41.6 |
| door -x+y (y wall) 2 | 2.30 | 1655 | 1709 | 0.9 | 1441.8 | 30.0 | 107.3 | 6.3-16.3 |
| door -x+y (y wall) 3 | 2.30 | 1236 | 1164 | 0.9 | 1480.8 | 21.8 | 115.1 | 4.7-14.7 |
| door -x+y (y wall) 4 | 2.30 | 886 | 648 | 1.0 | 1478.8 | 15.6 | 104.7 | 26.9-36.9 |
| door -x+y (x wall) 0 | 2.30 | 1690 | 2724 | 0.9 | 1204.6 | 36.6 | 109.9 | 16.8-26.8 |
| door -x+y (x wall) 1 | 2.30 | 1823 | 2254 | 0.9 | 1480.1 | 32.1 | 107.3 | 0.5-10.5 |
| door -x+y (x wall) 2 | 2.30 | 1667 | 1716 | 0.9 | 1487.2 | 29.3 | 115.1 | 8.6-18.5 |
| door -x+y (x wall) 3 | 2.30 | 1190 | 1163 | 0.9 | 1490.6 | 20.8 | 115.1 | 18.7-28.7 |
| door -x+y (x wall) 4 | 2.30 | 882 | 639 | 1.0 | 1468.0 | 15.7 | 102.0 | 23.1-33.1 |
| door -x+y (corner) | 2.30 | 692 | 245 | 0.9 | 1215.3 | 14.9 | 73.3 | 0.7-10.7 |
| door -x-y (y wall) 0 | 2.30 | 1694 | 2736 | 0.9 | 1295.9 | 34.1 | 104.7 | 34.1-44.1 |
| door -x-y (y wall) 1 | 2.30 | 1859 | 2259 | 1.0 | 1481.1 | 32.8 | 109.9 | 35.7-45.7 |
| door -x-y (y wall) 2 | 2.30 | 1755 | 1715 | 1.0 | 1485.3 | 30.8 | 107.3 | 20.1-30.1 |
| door -x-y (y wall) 3 | 2.30 | 1173 | 1163 | 0.7 | 1489.3 | 20.6 | 109.9 | 36.9-46.9 |
| door -x-y (y wall) 4 | 2.30 | 811 | 641 | 0.9 | 1460.3 | 14.5 | 112.5 | 8.6-18.5 |
| door -x-y (x wall) 0 | 2.30 | 1669 | 2721 | 0.9 | 1327.5 | 32.8 | 109.9 | 0.5-10.5 |
| door -x-y (x wall) 1 | 2.30 | 1870 | 2249 | 0.9 | 1476.0 | 33.1 | 109.9 | 16.4-26.4 |
| door -x-y (x wall) 2 | 2.30 | 1740 | 1711 | 0.9 | 1475.3 | 30.8 | 109.9 | 30.1-40.1 |
| door -x-y (x wall) 3 | 2.30 | 1233 | 1165 | 0.9 | 1494.4 | 21.5 | 109.9 | 20.1-30.1 |
| door -x-y (x wall) 4 | 2.30 | 845 | 641 | 0.7 | 1501.6 | 14.7 | 107.3 | 4.9-14.9 |
| door -x-y (corner) | 2.30 | 547 | 247 | 0.9 | 1292.2 | 11.0 | 70.6 | 0.3-10.3 |
| door +x-y (y wall) 0 | 2.30 | 1638 | 2722 | 0.9 | 1158.4 | 36.9 | 112.5 | 26.2-36.2 |
| door +x-y (y wall) 1 | 2.30 | 1866 | 2251 | 0.9 | 1478.0 | 33.0 | 104.7 | 23.4-33.4 |
| door +x-y (y wall) 2 | 2.30 | 1732 | 1714 | 0.7 | 1527.5 | 29.6 | 115.1 | 15.0-25.0 |
| door +x-y (y wall) 3 | 2.30 | 1156 | 1165 | 0.7 | 1495.5 | 20.2 | 112.5 | 29.0-39.0 |
| door +x-y (y wall) 4 | 2.30 | 877 | 638 | 0.7 | 1502.3 | 15.2 | 112.5 | 24.5-34.5 |
| door +x-y (x wall) 0 | 2.30 | 1701 | 2729 | 0.9 | 1277.7 | 34.7 | 115.1 | 11.2-21.2 |
| door +x-y (x wall) 1 | 2.30 | 1860 | 2254 | 0.7 | 1472.7 | 33.0 | 109.9 | 27.1-37.1 |
| door +x-y (x wall) 2 | 2.30 | 1698 | 1714 | 0.9 | 1522.9 | 29.1 | 112.5 | 33.2-43.2 |
| door +x-y (x wall) 3 | 2.30 | 1160 | 1156 | 0.9 | 1501.7 | 20.2 | 109.9 | 2.4-12.4 |
| door +x-y (x wall) 4 | 2.30 | 872 | 636 | 0.9 | 1532.0 | 14.9 | 107.3 | 0.9-10.8 |
| door +x-y (corner) | 2.30 | 618 | 254 | 0.7 | 1140.2 | 14.1 | 73.3 | 0.5-10.5 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (2.30 m; a corner door's: the gap between its wall ends, 2.30 m); agents are removed past the outer wall's outer face (92.71 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 2145 | 3.1% | 17.8% |
| -x | avenue | 5.66 | 2155 | 3.1% | 17.8% |
| +y | avenue | 5.66 | 2117 | 3.1% | 17.5% |
| -y | avenue | 5.66 | 2144 | 3.1% | 17.7% |
| door +x+y (y wall) 0 | door | 2.30 | 1686 | 2.4% | 34.3% |
| door +x+y (y wall) 1 | door | 2.30 | 1823 | 2.6% | 37.1% |
| door +x+y (y wall) 2 | door | 2.30 | 1666 | 2.4% | 33.9% |
| door +x+y (y wall) 3 | door | 2.30 | 1139 | 1.6% | 23.2% |
| door +x+y (y wall) 4 | door | 2.30 | 911 | 1.3% | 18.6% |
| door +x+y (x wall) 0 | door | 2.30 | 1654 | 2.4% | 33.7% |
| door +x+y (x wall) 1 | door | 2.30 | 1821 | 2.6% | 37.1% |
| door +x+y (x wall) 2 | door | 2.30 | 1682 | 2.4% | 34.3% |
| door +x+y (x wall) 3 | door | 2.30 | 1234 | 1.8% | 25.1% |
| door +x+y (x wall) 4 | door | 2.30 | 877 | 1.3% | 17.9% |
| door +x+y (corner) | door | 2.30 | 680 | 1.0% | 13.9% |
| door -x+y (y wall) 0 | door | 2.30 | 1654 | 2.4% | 33.7% |
| door -x+y (y wall) 1 | door | 2.30 | 1828 | 2.6% | 37.2% |
| door -x+y (y wall) 2 | door | 2.30 | 1655 | 2.4% | 33.7% |
| door -x+y (y wall) 3 | door | 2.30 | 1236 | 1.8% | 25.2% |
| door -x+y (y wall) 4 | door | 2.30 | 886 | 1.3% | 18.0% |
| door -x+y (x wall) 0 | door | 2.30 | 1690 | 2.4% | 34.4% |
| door -x+y (x wall) 1 | door | 2.30 | 1823 | 2.6% | 37.1% |
| door -x+y (x wall) 2 | door | 2.30 | 1667 | 2.4% | 34.0% |
| door -x+y (x wall) 3 | door | 2.30 | 1190 | 1.7% | 24.2% |
| door -x+y (x wall) 4 | door | 2.30 | 882 | 1.3% | 18.0% |
| door -x+y (corner) | door | 2.30 | 692 | 1.0% | 14.1% |
| door -x-y (y wall) 0 | door | 2.30 | 1694 | 2.4% | 34.5% |
| door -x-y (y wall) 1 | door | 2.30 | 1859 | 2.7% | 37.9% |
| door -x-y (y wall) 2 | door | 2.30 | 1755 | 2.5% | 35.7% |
| door -x-y (y wall) 3 | door | 2.30 | 1173 | 1.7% | 23.9% |
| door -x-y (y wall) 4 | door | 2.30 | 811 | 1.2% | 16.5% |
| door -x-y (x wall) 0 | door | 2.30 | 1669 | 2.4% | 34.0% |
| door -x-y (x wall) 1 | door | 2.30 | 1870 | 2.7% | 38.1% |
| door -x-y (x wall) 2 | door | 2.30 | 1740 | 2.5% | 35.4% |
| door -x-y (x wall) 3 | door | 2.30 | 1233 | 1.8% | 25.1% |
| door -x-y (x wall) 4 | door | 2.30 | 845 | 1.2% | 17.2% |
| door -x-y (corner) | door | 2.30 | 547 | 0.8% | 11.1% |
| door +x-y (y wall) 0 | door | 2.30 | 1638 | 2.4% | 33.4% |
| door +x-y (y wall) 1 | door | 2.30 | 1866 | 2.7% | 38.0% |
| door +x-y (y wall) 2 | door | 2.30 | 1732 | 2.5% | 35.3% |
| door +x-y (y wall) 3 | door | 2.30 | 1156 | 1.7% | 23.5% |
| door +x-y (y wall) 4 | door | 2.30 | 877 | 1.3% | 17.9% |
| door +x-y (x wall) 0 | door | 2.30 | 1701 | 2.5% | 34.6% |
| door +x-y (x wall) 1 | door | 2.30 | 1860 | 2.7% | 37.9% |
| door +x-y (x wall) 2 | door | 2.30 | 1698 | 2.4% | 34.6% |
| door +x-y (x wall) 3 | door | 2.30 | 1160 | 1.7% | 23.6% |
| door +x-y (x wall) 4 | door | 2.30 | 872 | 1.3% | 17.8% |
| door +x-y (corner) | door | 2.30 | 618 | 0.9% | 12.6% |
| **doors (44)** | door | 101.20 | 60750 | 87.6% | |
| **avenues (4)** | avenue | 22.64 | 8561 | 12.4% | |

**Unused exit width: 0.0 of 123.8 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 1532.0 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 26.2%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 2365 | 3.4% | 2365 | 3.4% |
| straight +x+y (y wing) 1 | straight | yes | 1854 | 2.7% | 1706 | 2.5% |
| straight +x+y (y wing) 2 | straight | yes | 1602 | 2.3% | 1585 | 2.3% |
| straight +x+y (y wing) 3 | straight | yes | 1111 | 1.6% | 1097 | 1.6% |
| straight +x+y (y wing) 4 | straight | yes | 695 | 1.0% | 678 | 1.0% |
| straight +x+y (x wing) 0 | straight | yes | 2348 | 3.4% | 2348 | 3.4% |
| straight +x+y (x wing) 1 | straight | yes | 1838 | 2.7% | 1715 | 2.5% |
| straight +x+y (x wing) 2 | straight | yes | 1619 | 2.3% | 1600 | 2.3% |
| straight +x+y (x wing) 3 | straight | yes | 1147 | 1.7% | 1130 | 1.6% |
| straight +x+y (x wing) 4 | straight | yes | 718 | 1.0% | 705 | 1.0% |
| corner +x+y | corner | yes | 2187 | 3.2% | 938 | 1.4% |
| straight -x+y (y wing) 0 | straight | yes | 2339 | 3.4% | 2339 | 3.4% |
| straight -x+y (y wing) 1 | straight | yes | 1847 | 2.7% | 1716 | 2.5% |
| straight -x+y (y wing) 2 | straight | yes | 1612 | 2.3% | 1565 | 2.3% |
| straight -x+y (y wing) 3 | straight | yes | 1151 | 1.7% | 1129 | 1.6% |
| straight -x+y (y wing) 4 | straight | yes | 730 | 1.1% | 714 | 1.0% |
| straight -x+y (x wing) 0 | straight | yes | 2362 | 3.4% | 2361 | 3.4% |
| straight -x+y (x wing) 1 | straight | yes | 1851 | 2.7% | 1706 | 2.5% |
| straight -x+y (x wing) 2 | straight | yes | 1575 | 2.3% | 1565 | 2.3% |
| straight -x+y (x wing) 3 | straight | yes | 1155 | 1.7% | 1129 | 1.6% |
| straight -x+y (x wing) 4 | straight | yes | 695 | 1.0% | 679 | 1.0% |
| corner -x+y | corner | yes | 2243 | 3.2% | 962 | 1.4% |
| straight -x-y (y wing) 0 | straight | yes | 2360 | 3.4% | 2360 | 3.4% |
| straight -x-y (y wing) 1 | straight | yes | 1862 | 2.7% | 1746 | 2.5% |
| straight -x-y (y wing) 2 | straight | yes | 1660 | 2.4% | 1656 | 2.4% |
| straight -x-y (y wing) 3 | straight | yes | 1133 | 1.6% | 1108 | 1.6% |
| straight -x-y (y wing) 4 | straight | yes | 623 | 0.9% | 608 | 0.9% |
| straight -x-y (x wing) 0 | straight | yes | 2401 | 3.5% | 2401 | 3.5% |
| straight -x-y (x wing) 1 | straight | yes | 1852 | 2.7% | 1764 | 2.5% |
| straight -x-y (x wing) 2 | straight | yes | 1664 | 2.4% | 1660 | 2.4% |
| straight -x-y (x wing) 3 | straight | yes | 1105 | 1.6% | 1096 | 1.6% |
| straight -x-y (x wing) 4 | straight | yes | 716 | 1.0% | 697 | 1.0% |
| corner -x-y | corner | yes | 2087 | 3.0% | 769 | 1.1% |
| straight +x-y (y wing) 0 | straight | yes | 2350 | 3.4% | 2350 | 3.4% |
| straight +x-y (y wing) 1 | straight | yes | 1866 | 2.7% | 1752 | 2.5% |
| straight +x-y (y wing) 2 | straight | yes | 1645 | 2.4% | 1636 | 2.4% |
| straight +x-y (y wing) 3 | straight | yes | 1098 | 1.6% | 1082 | 1.6% |
| straight +x-y (y wing) 4 | straight | yes | 699 | 1.0% | 682 | 1.0% |
| straight +x-y (x wing) 0 | straight | yes | 2377 | 3.4% | 2377 | 3.4% |
| straight +x-y (x wing) 1 | straight | yes | 1886 | 2.7% | 1749 | 2.5% |
| straight +x-y (x wing) 2 | straight | yes | 1627 | 2.3% | 1622 | 2.3% |
| straight +x-y (x wing) 3 | straight | yes | 1105 | 1.6% | 1093 | 1.6% |
| straight +x-y (x wing) 4 | straight | yes | 680 | 1.0% | 661 | 1.0% |
| corner +x-y | corner | yes | 2061 | 3.0% | 863 | 1.2% |
| **straight (40)** | | | 61323 | | 59932 | 86.5% |
| **corner (4)** | | | 8578 | | 3532 | 5.1% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 5847, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 2145 | 60.2 | 1226.8 | 0.23 | 0.66 | 0.0% |
| -x | 2155 | 60.2 | 1210.2 | 0.24 | 0.71 | 0.0% |
| +y | 2117 | 60.2 | 1224.7 | 0.23 | 0.72 | 0.0% |
| -y | 2144 | 60.2 | 1237.6 | 0.23 | 0.76 | 0.0% |
| door +x+y (y wall) 0 | 1686 | 0.9 | 1203.4 | 0.44 | 1.31 | 4.1% |
| door +x+y (y wall) 1 | 1823 | 0.9 | 1409.0 | 0.40 | 1.28 | 3.5% |
| door +x+y (y wall) 2 | 1666 | 1.0 | 1482.5 | 0.35 | 1.25 | 3.4% |
| door +x+y (y wall) 3 | 1139 | 0.9 | 1446.1 | 0.25 | 1.31 | 3.4% |
| door +x+y (y wall) 4 | 911 | 0.9 | 1353.6 | 0.21 | 1.35 | 3.7% |
| door +x+y (x wall) 0 | 1654 | 0.9 | 1303.4 | 0.40 | 1.28 | 3.8% |
| door +x+y (x wall) 1 | 1821 | 0.9 | 1427.8 | 0.40 | 1.35 | 3.5% |
| door +x+y (x wall) 2 | 1682 | 0.9 | 1446.5 | 0.36 | 1.35 | 3.4% |
| door +x+y (x wall) 3 | 1234 | 0.9 | 1463.6 | 0.26 | 1.31 | 3.4% |
| door +x+y (x wall) 4 | 877 | 0.9 | 1481.3 | 0.18 | 1.31 | 3.4% |
| door +x+y (corner) | 680 | 0.7 | 1003.3 | 0.21 | 0.85 | 3.0% |
| door -x+y (y wall) 0 | 1654 | 0.9 | 1295.4 | 0.40 | 1.31 | 3.8% |
| door -x+y (y wall) 1 | 1828 | 1.0 | 1441.1 | 0.40 | 1.38 | 3.4% |
| door -x+y (y wall) 2 | 1655 | 0.9 | 1441.8 | 0.36 | 1.28 | 3.4% |
| door -x+y (y wall) 3 | 1236 | 0.9 | 1480.8 | 0.26 | 1.38 | 3.4% |
| door -x+y (y wall) 4 | 886 | 1.0 | 1478.8 | 0.19 | 1.25 | 4.0% |
| door -x+y (x wall) 0 | 1690 | 0.9 | 1204.6 | 0.44 | 1.31 | 4.1% |
| door -x+y (x wall) 1 | 1823 | 0.9 | 1480.1 | 0.38 | 1.28 | 3.4% |
| door -x+y (x wall) 2 | 1667 | 0.9 | 1487.2 | 0.35 | 1.38 | 3.3% |
| door -x+y (x wall) 3 | 1190 | 0.9 | 1490.6 | 0.25 | 1.38 | 3.3% |
| door -x+y (x wall) 4 | 882 | 1.0 | 1468.0 | 0.19 | 1.22 | 4.1% |
| door -x+y (corner) | 692 | 0.9 | 1215.3 | 0.18 | 0.88 | 0.8% |
| door -x-y (y wall) 0 | 1694 | 0.9 | 1295.9 | 0.41 | 1.25 | 3.8% |
| door -x-y (y wall) 1 | 1859 | 1.0 | 1481.1 | 0.39 | 1.31 | 3.4% |
| door -x-y (y wall) 2 | 1755 | 1.0 | 1485.3 | 0.37 | 1.28 | 3.4% |
| door -x-y (y wall) 3 | 1173 | 0.7 | 1489.3 | 0.25 | 1.31 | 3.3% |
| door -x-y (y wall) 4 | 811 | 0.9 | 1460.3 | 0.17 | 1.35 | 3.4% |
| door -x-y (x wall) 0 | 1669 | 0.9 | 1327.5 | 0.39 | 1.31 | 3.0% |
| door -x-y (x wall) 1 | 1870 | 0.9 | 1476.0 | 0.40 | 1.31 | 3.4% |
| door -x-y (x wall) 2 | 1740 | 0.9 | 1475.3 | 0.37 | 1.31 | 3.4% |
| door -x-y (x wall) 3 | 1233 | 0.9 | 1494.4 | 0.26 | 1.31 | 3.3% |
| door -x-y (x wall) 4 | 845 | 0.7 | 1501.6 | 0.18 | 1.28 | 3.3% |
| door -x-y (corner) | 547 | 0.9 | 1292.2 | 0.13 | 0.85 | 0.0% |
| door +x-y (y wall) 0 | 1638 | 0.9 | 1158.4 | 0.44 | 1.35 | 3.4% |
| door +x-y (y wall) 1 | 1866 | 0.9 | 1478.0 | 0.39 | 1.25 | 3.4% |
| door +x-y (y wall) 2 | 1732 | 0.7 | 1527.5 | 0.35 | 1.38 | 3.2% |
| door +x-y (y wall) 3 | 1156 | 0.7 | 1495.5 | 0.24 | 1.35 | 3.3% |
| door +x-y (y wall) 4 | 877 | 0.7 | 1502.3 | 0.18 | 1.35 | 3.3% |
| door +x-y (x wall) 0 | 1701 | 0.9 | 1277.7 | 0.42 | 1.38 | 3.9% |
| door +x-y (x wall) 1 | 1860 | 0.7 | 1472.7 | 0.39 | 1.31 | 3.4% |
| door +x-y (x wall) 2 | 1698 | 0.9 | 1522.9 | 0.35 | 1.35 | 3.3% |
| door +x-y (x wall) 3 | 1160 | 0.9 | 1501.7 | 0.24 | 1.31 | 3.3% |
| door +x-y (x wall) 4 | 872 | 0.9 | 1532.0 | 0.18 | 1.28 | 3.2% |
| door +x-y (corner) | 618 | 0.7 | 1140.2 | 0.17 | 0.88 | 2.6% |

Mean flow / w J averaged over the doors 0.31, over the avenues 0.23.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 103.1 | 2365 | 1566 / 800 / 924 | 0.3 | 1200.4 | 2.74 | 4.91 | 93% | 88% | 5% | 4.41 |
| straight +x+y (y wing) 1 | 1.20 | 81.5 | 1840 | 1706 / 0 / 209 | 0.7 | 1406.1 | 1.36 | 2.31 | 92% | 73% | 19% | 3.77 |
| straight +x+y (y wing) 2 | 1.20 | 61.0 | 1486 | 1585 / 0 / 22 | 0.7 | 1479.5 | 1.09 | 1.71 | 74% | 65% | 9% | 3.87 |
| straight +x+y (y wing) 3 | 1.20 | 39.4 | 946 | 1097 / 0 / 16 | 0.7 | 1443.2 | 0.77 | 1.60 | 57% | 44% | 12% | 3.50 |
| straight +x+y (y wing) 4 | 1.20 | 18.8 | 408 | 678 / 0 / 23 | 0.7 | 1350.6 | 0.52 | 2.01 | 22% | 18% | 4% | 3.64 |
| straight +x+y (x wing) 0 | 1.20 | 103.1 | 2348 | 1522 / 826 / 1156 | 0.2 | 1156.7 | 3.03 | 4.81 | 91% | 84% | 8% | 4.29 |
| straight +x+y (x wing) 1 | 1.20 | 81.5 | 1809 | 1715 / 0 / 173 | 0.7 | 1424.8 | 1.33 | 2.41 | 92% | 76% | 16% | 3.84 |
| straight +x+y (x wing) 2 | 1.20 | 61.0 | 1543 | 1600 / 0 / 23 | 0.7 | 1443.5 | 1.12 | 1.91 | 83% | 71% | 12% | 3.64 |
| straight +x+y (x wing) 3 | 1.20 | 39.4 | 933 | 1130 / 0 / 18 | 0.7 | 1460.6 | 0.79 | 1.71 | 48% | 41% | 7% | 3.68 |
| straight +x+y (x wing) 4 | 1.20 | 18.8 | 393 | 705 / 0 / 17 | 0.7 | 1478.3 | 0.49 | 1.81 | 18% | 17% | 1% | 3.76 |
| corner +x+y | 1.20 | 186.0 | 1796 | 544 / 394 / 1300 | 0.7 | 1454.3 | 1.54 | 3.71 | 91% | 58% | 34% | 2.61 |
| straight -x+y (y wing) 0 | 1.20 | 103.1 | 2339 | 1526 / 813 / 1178 | 0.2 | 1178.0 | 2.99 | 5.32 | 92% | 83% | 9% | 4.04 |
| straight -x+y (y wing) 1 | 1.20 | 81.5 | 1820 | 1716 / 0 / 182 | 0.7 | 1438.1 | 1.32 | 2.61 | 92% | 76% | 17% | 3.73 |
| straight -x+y (y wing) 2 | 1.20 | 61.0 | 1533 | 1565 / 0 / 48 | 0.7 | 1438.8 | 1.12 | 1.71 | 79% | 70% | 10% | 3.89 |
| straight -x+y (y wing) 3 | 1.20 | 39.4 | 943 | 1129 / 0 / 25 | 0.7 | 1477.8 | 0.78 | 1.71 | 50% | 42% | 8% | 3.63 |
| straight -x+y (y wing) 4 | 1.20 | 18.8 | 391 | 714 / 0 / 16 | 0.7 | 1475.9 | 0.49 | 1.71 | 19% | 17% | 2% | 3.82 |
| straight -x+y (x wing) 0 | 1.20 | 103.1 | 2362 | 1576 / 787 / 846 | 0.3 | 1201.6 | 2.67 | 5.72 | 93% | 87% | 6% | 4.33 |
| straight -x+y (x wing) 1 | 1.20 | 81.5 | 1829 | 1706 / 0 / 201 | 0.7 | 1477.1 | 1.29 | 2.31 | 91% | 71% | 19% | 3.71 |
| straight -x+y (x wing) 2 | 1.20 | 61.0 | 1492 | 1565 / 0 / 21 | 0.7 | 1484.3 | 1.07 | 1.91 | 79% | 66% | 13% | 3.68 |
| straight -x+y (x wing) 3 | 1.20 | 39.4 | 946 | 1129 / 0 / 30 | 0.7 | 1487.6 | 0.78 | 1.71 | 51% | 42% | 9% | 3.59 |
| straight -x+y (x wing) 4 | 1.20 | 18.8 | 398 | 679 / 0 / 18 | 0.7 | 1465.0 | 0.48 | 1.71 | 19% | 18% | 1% | 3.86 |
| corner -x+y | 1.20 | 186.0 | 1812 | 571 / 392 / 1333 | 0.7 | 1451.9 | 1.58 | 3.11 | 92% | 57% | 35% | 2.54 |
| straight -x-y (y wing) 0 | 1.20 | 103.1 | 2360 | 1564 / 798 / 945 | 0.2 | 1184.1 | 2.79 | 4.71 | 92% | 90% | 2% | 4.54 |
| straight -x-y (y wing) 1 | 1.20 | 81.5 | 1847 | 1746 / 0 / 198 | 0.7 | 1478.1 | 1.32 | 2.31 | 92% | 72% | 20% | 3.73 |
| straight -x-y (y wing) 2 | 1.20 | 61.0 | 1499 | 1656 / 0 / 8 | 0.7 | 1482.3 | 1.12 | 1.71 | 75% | 64% | 11% | 3.80 |
| straight -x-y (y wing) 3 | 1.20 | 39.4 | 939 | 1108 / 0 / 37 | 0.7 | 1486.4 | 0.77 | 2.21 | 49% | 43% | 6% | 3.82 |
| straight -x-y (y wing) 4 | 1.20 | 18.8 | 402 | 608 / 0 / 23 | 0.7 | 1457.3 | 0.43 | 2.01 | 20% | 17% | 3% | 3.59 |
| straight -x-y (x wing) 0 | 1.20 | 103.1 | 2401 | 1552 / 850 / 1069 | 0.5 | 1170.5 | 2.97 | 4.91 | 92% | 86% | 6% | 4.23 |
| straight -x-y (x wing) 1 | 1.20 | 81.5 | 1832 | 1764 / 0 / 162 | 0.7 | 1473.1 | 1.31 | 2.61 | 91% | 76% | 15% | 3.88 |
| straight -x-y (x wing) 2 | 1.20 | 61.0 | 1513 | 1660 / 0 / 13 | 0.7 | 1472.4 | 1.14 | 1.71 | 78% | 68% | 9% | 3.80 |
| straight -x-y (x wing) 3 | 1.20 | 39.4 | 929 | 1096 / 0 / 20 | 0.7 | 1491.4 | 0.75 | 1.71 | 51% | 40% | 11% | 3.42 |
| straight -x-y (x wing) 4 | 1.20 | 18.8 | 391 | 697 / 0 / 22 | 0.7 | 1498.6 | 0.48 | 1.71 | 17% | 15% | 2% | 3.83 |
| corner -x-y | 1.20 | 186.0 | 1752 | 424 / 345 / 1390 | 0.7 | 1474.6 | 1.46 | 4.21 | 92% | 75% | 17% | 2.79 |
| straight +x-y (y wing) 0 | 1.20 | 103.1 | 2350 | 1528 / 822 / 1101 | 0.5 | 1155.4 | 2.99 | 5.12 | 92% | 85% | 7% | 4.30 |
| straight +x-y (y wing) 1 | 1.20 | 81.5 | 1833 | 1752 / 0 / 155 | 0.7 | 1475.0 | 1.29 | 2.11 | 93% | 75% | 18% | 3.77 |
| straight +x-y (y wing) 2 | 1.20 | 61.0 | 1549 | 1636 / 0 / 12 | 0.7 | 1524.5 | 1.08 | 1.81 | 77% | 67% | 10% | 3.76 |
| straight +x-y (y wing) 3 | 1.20 | 39.4 | 929 | 1082 / 0 / 23 | 0.7 | 1492.5 | 0.74 | 1.71 | 48% | 43% | 5% | 3.72 |
| straight +x-y (y wing) 4 | 1.20 | 18.8 | 411 | 682 / 0 / 18 | 0.7 | 1499.3 | 0.47 | 1.71 | 19% | 17% | 1% | 3.85 |
| straight +x-y (x wing) 0 | 1.20 | 103.1 | 2377 | 1579 / 798 / 930 | 0.2 | 1185.3 | 2.79 | 4.81 | 92% | 89% | 3% | 4.33 |
| straight +x-y (x wing) 1 | 1.20 | 81.5 | 1863 | 1749 / 0 / 179 | 0.7 | 1469.7 | 1.31 | 2.31 | 93% | 74% | 19% | 3.75 |
| straight +x-y (x wing) 2 | 1.20 | 61.0 | 1485 | 1622 / 0 / 8 | 0.7 | 1519.9 | 1.07 | 1.71 | 73% | 65% | 7% | 3.86 |
| straight +x-y (x wing) 3 | 1.20 | 39.4 | 960 | 1093 / 0 / 21 | 0.7 | 1498.8 | 0.74 | 1.71 | 60% | 43% | 17% | 3.21 |
| straight +x-y (x wing) 4 | 1.20 | 18.8 | 400 | 661 / 0 / 20 | 0.7 | 1529.0 | 0.45 | 1.81 | 18% | 16% | 2% | 3.87 |
| corner +x-y | 1.20 | 186.0 | 1710 | 488 / 375 / 1244 | 0.7 | 1505.2 | 1.40 | 3.41 | 92% | 66% | 26% | 2.59 |

The last agent out (agent 48440, t100 1532.0 s): last gangway straight +x-y (x wing) 4, exit door +x-y (x wall) 4. The gangway that cleared last: straight +x-y (x wing) 4 at 1529.0 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 8804 | 7800.4 | 6.91 | 1500.0 / 1433.0 / 1380.7 | 1437.9 / 1430.2 / 1354.8 | 7294420.0 | 13897840 | 0.166 |
| gangway | 3792 | 3512.9 | 6.91 | 1498.8 / 1432.8 / 1379.0 | 1437.9 / 1430.2 / 1354.8 | 7266928.2 | 12950034 | 0.102 |
| walkway | 276 | 257.4 | 5.21 | 717.6 / 520.0 / 16.6 | 488.0 / 270.8 / 6.3 | 85.0 | 87419 | 0.683 |
| avenue | 1920 | 1801.4 | 3.20 | 762.6 / 60.5 / 0.0 | 611.1 / 1.9 / 0.0 | 0.0 | 513056 | 1.334 |
| exit | 4 | 2.0 | 0.00 | 0.7 / 0.0 / 0.0 | 0.7 / 0.0 / 0.0 | 0.0 | 3 | 0.836 |
| concourse | 2812 | 2226.8 | 5.99 | 1446.0 / 76.8 / 50.4 | 1086.3 / 75.0 / 44.3 | 27406.8 | 347327 | 0.715 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 25392 | 16030.4 | 7.78 | 1387.4 / 1378.4 / 1341.0 | 1386.0 / 1377.6 / 1325.6 | 9258746.3 | 22787099 | 0.022 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 208 x 208 from (-104, -104) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -34.5 | -34.5 | gangway | 1.00 | 5.93 | 1380.9 | 1372.8 | 1335.4 | 7800.0 | 0.005 |
| 2 | 35.5 | -35.5 | gangway | 1.00 | 6.02 | 1412.5 | 1405.2 | 1327.4 | 7669.7 | 0.005 |
| 3 | 34.5 | -34.5 | gangway | 1.00 | 5.86 | 1405.2 | 1395.1 | 1354.8 | 7419.9 | 0.006 |
| 4 | -34.5 | 34.5 | gangway | 1.00 | 5.67 | 1373.0 | 1364.4 | 1284.7 | 7133.2 | 0.005 |
| 5 | 36.5 | -36.5 | gangway | 1.00 | 5.58 | 1417.4 | 1410.6 | 1323.9 | 7128.0 | 0.007 |
| 6 | 32.5 | 32.5 | gangway | 1.00 | 5.84 | 1330.5 | 1321.6 | 1257.8 | 7059.8 | 0.005 |
| 7 | -35.5 | -35.5 | gangway | 1.00 | 5.67 | 1389.1 | 1382.5 | 1264.9 | 6996.3 | 0.006 |
| 8 | 39.5 | -39.5 | gangway | 1.00 | 5.96 | 1435.5 | 1423.6 | 1237.6 | 6982.7 | 0.015 |
| 9 | -36.5 | -36.5 | gangway | 1.00 | 5.63 | 1391.9 | 1381.8 | 1266.5 | 6905.4 | 0.007 |
| 10 | -33.5 | -33.5 | gangway | 0.99 | 5.51 | 1371.1 | 1362.0 | 1294.0 | 6896.5 | 0.005 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 38.5 | -36.5 | seat row | 0.50 | 7.39 | 1354.3 | 1337.3 | 1309.0 | 4745.8 | 0.003 |
| 2 | 36.5 | -38.5 | seat row | 0.50 | 7.33 | 1359.2 | 1349.8 | 1314.9 | 4713.4 | 0.003 |
| 3 | 42.5 | -25.5 | seat row | 0.64 | 6.99 | 1135.8 | 1131.3 | 1120.3 | 4692.2 | 0.011 |
| 4 | -38.5 | -36.5 | seat row | 0.50 | 7.26 | 1347.1 | 1341.7 | 1314.9 | 4667.8 | 0.004 |
| 5 | -42.5 | -25.5 | seat row | 0.64 | 6.97 | 1120.3 | 1115.6 | 1103.8 | 4624.3 | 0.011 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 8428; agent-steps of seated agents on another row's clearway: 713094.

## Deposit check

Person-seconds deposited: 36691196.3, of them in excluded cells: 6257.433.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 9772263 overlapping pair-steps: p99 0.0020, max 0.0830 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0020 max 0.0830; venue-geometry 14: p99 0.0032 max 0.0032 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00768 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 59 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.40 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 3770 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
