# Experiment `L_load150_s2`

**Task 5.9 stage 4: venue L, 150% requested (seed 2): every seat + standing on the walkway and concourse (M, L: the achievable maximum, also the 125% request)**

Venue L (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (4000 x 4000), cache key a2f3aaf59c2252b7, content hash 022d17b202313d70). 69311 agents (load 109.3%, requested 150%): every one of the 63424 seats and 5887 standing (spawnOvercrowdedCrowd, seed 2; below), buffer N = 131072, 8725 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 12373415 evaluations, 671049 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.09)** (the L venue's design capacity 63424, jam capacity 171923: 23822.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-21T18:29:18, 1005.0 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Spawn (overcrowding)

| | |
|---|---|
| seated | 63424 (every seat) |
| standing | **5887** (requested round((1.50 - 1) x 63424) = 31712; at most 5887 = floor(2.5 p/m^2 x 2355.0 m^2)) |
| standing floor | walkway + rear concourse, 2355.0 m^2 |
| standing on the walkway / concourse / gangways | 615 / 5272 / 0 |
| **load** | **109.28%** of the seats (requested 150%; the floor takes no more: the achievable maximum) |
| standing crowd's mean density | 2.500 p/m^2 |
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 4.20, all circulation cells 4.20 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 2, 355876 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 2815 | 492.4 |
| t90 | 6234 | 1090.4 |
| t100 | 8725 | 1526.1 |

t_p: the step by which ceil(p x 69311) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 2183 | 89 | 60.2 | 1193.2 | 20.4 | 61.7 | 59.6-69.6 |
| -x | 5.66 | 2154 | 85 | 60.2 | 1202.0 | 20.0 | 60.6 | 59.6-69.6 |
| +y | 5.66 | 2153 | 84 | 60.2 | 1204.9 | 19.9 | 55.3 | 59.6-69.6 |
| -y | 5.66 | 2241 | 90 | 60.2 | 1203.4 | 20.8 | 59.5 | 59.8-69.8 |
| door +x+y (y wall) 0 | 2.30 | 1668 | 2724 | 0.9 | 1182.7 | 36.8 | 109.9 | 20.8-30.8 |
| door +x+y (y wall) 1 | 2.30 | 1848 | 2257 | 1.0 | 1457.8 | 33.1 | 112.5 | 5.6-15.6 |
| door +x+y (y wall) 2 | 2.30 | 1722 | 1713 | 0.7 | 1526.1 | 29.4 | 107.3 | 39.5-49.5 |
| door +x+y (y wall) 3 | 2.30 | 1251 | 1159 | 1.0 | 1513.3 | 21.6 | 109.9 | 22.4-32.4 |
| door +x+y (y wall) 4 | 2.30 | 779 | 640 | 0.9 | 1424.3 | 14.3 | 109.9 | 18.2-28.2 |
| door +x+y (x wall) 0 | 2.30 | 1667 | 2728 | 0.7 | 1169.4 | 37.2 | 112.5 | 8.2-18.2 |
| door +x+y (x wall) 1 | 2.30 | 1860 | 2255 | 0.9 | 1424.4 | 34.1 | 117.7 | 18.9-28.9 |
| door +x+y (x wall) 2 | 2.30 | 1739 | 1717 | 0.7 | 1510.8 | 30.0 | 117.7 | 9.4-19.4 |
| door +x+y (x wall) 3 | 2.30 | 1268 | 1163 | 0.9 | 1489.0 | 22.2 | 115.1 | 34.6-44.6 |
| door +x+y (x wall) 4 | 2.30 | 743 | 638 | 0.9 | 1464.8 | 13.2 | 107.3 | 7.2-17.1 |
| door +x+y (corner) | 2.30 | 572 | 245 | 0.9 | 1110.1 | 13.4 | 73.3 | 65.6-75.6 |
| door -x+y (y wall) 0 | 2.30 | 1689 | 2722 | 0.9 | 1278.4 | 34.5 | 112.5 | 0.7-10.7 |
| door -x+y (y wall) 1 | 2.30 | 1839 | 2252 | 0.7 | 1448.1 | 33.1 | 107.3 | 17.0-26.9 |
| door -x+y (y wall) 2 | 2.30 | 1681 | 1708 | 1.0 | 1511.4 | 29.0 | 109.9 | 24.0-33.9 |
| door -x+y (y wall) 3 | 2.30 | 1303 | 1168 | 1.0 | 1507.7 | 22.6 | 109.9 | 10.0-19.9 |
| door -x+y (y wall) 4 | 2.30 | 786 | 639 | 0.9 | 1494.6 | 13.7 | 109.9 | 0.5-10.5 |
| door -x+y (x wall) 0 | 2.30 | 1643 | 2723 | 0.7 | 1292.0 | 33.2 | 112.5 | 27.6-37.6 |
| door -x+y (x wall) 1 | 2.30 | 1861 | 2257 | 0.9 | 1480.6 | 32.8 | 112.5 | 17.8-27.8 |
| door -x+y (x wall) 2 | 2.30 | 1715 | 1710 | 0.7 | 1485.3 | 30.1 | 109.9 | 12.9-22.9 |
| door -x+y (x wall) 3 | 2.30 | 1251 | 1165 | 0.7 | 1510.3 | 21.6 | 109.9 | 4.0-14.0 |
| door -x+y (x wall) 4 | 2.30 | 898 | 640 | 0.7 | 1513.5 | 15.5 | 109.9 | 20.6-30.6 |
| door -x+y (corner) | 2.30 | 550 | 250 | 0.9 | 1147.4 | 12.5 | 70.6 | 40.6-50.5 |
| door -x-y (y wall) 0 | 2.30 | 1703 | 2729 | 1.0 | 1302.9 | 34.1 | 104.7 | 0.5-10.5 |
| door -x-y (y wall) 1 | 2.30 | 1835 | 2250 | 0.7 | 1452.3 | 33.0 | 104.7 | 17.7-27.6 |
| door -x-y (y wall) 2 | 2.30 | 1760 | 1711 | 0.7 | 1446.1 | 31.8 | 109.9 | 38.5-48.4 |
| door -x-y (y wall) 3 | 2.30 | 1271 | 1156 | 0.9 | 1461.2 | 22.7 | 112.5 | 16.1-26.1 |
| door -x-y (y wall) 4 | 2.30 | 750 | 639 | 0.7 | 1447.2 | 13.5 | 104.7 | 6.3-16.3 |
| door -x-y (x wall) 0 | 2.30 | 1661 | 2721 | 0.9 | 1301.7 | 33.3 | 112.5 | 24.1-34.1 |
| door -x-y (x wall) 1 | 2.30 | 1862 | 2252 | 0.9 | 1452.4 | 33.5 | 112.5 | 25.0-35.0 |
| door -x-y (x wall) 2 | 2.30 | 1774 | 1711 | 0.7 | 1462.0 | 31.7 | 112.5 | 0.9-10.8 |
| door -x-y (x wall) 3 | 2.30 | 1241 | 1165 | 0.7 | 1465.4 | 22.1 | 109.9 | 11.4-21.3 |
| door -x-y (x wall) 4 | 2.30 | 720 | 640 | 0.9 | 1391.0 | 13.5 | 107.3 | 18.2-28.2 |
| door -x-y (corner) | 2.30 | 557 | 259 | 0.7 | 948.9 | 15.3 | 73.3 | 26.9-36.9 |
| door +x-y (y wall) 0 | 2.30 | 1675 | 2724 | 0.9 | 1316.0 | 33.2 | 115.1 | 4.0-14.0 |
| door +x-y (y wall) 1 | 2.30 | 1833 | 2253 | 0.9 | 1438.3 | 33.3 | 109.9 | 15.7-25.7 |
| door +x-y (y wall) 2 | 2.30 | 1704 | 1714 | 0.9 | 1486.4 | 29.9 | 104.7 | 9.3-19.2 |
| door +x-y (y wall) 3 | 2.30 | 1269 | 1159 | 1.0 | 1485.1 | 22.3 | 112.5 | 11.9-21.9 |
| door +x-y (y wall) 4 | 2.30 | 766 | 640 | 0.9 | 1441.2 | 13.9 | 109.9 | 0.7-10.7 |
| door +x-y (x wall) 0 | 2.30 | 1666 | 2728 | 0.9 | 1212.3 | 35.9 | 115.1 | 21.0-31.0 |
| door +x-y (x wall) 1 | 2.30 | 1846 | 2258 | 0.9 | 1444.0 | 33.4 | 115.1 | 18.9-28.9 |
| door +x-y (x wall) 2 | 2.30 | 1715 | 1714 | 0.7 | 1487.6 | 30.1 | 109.9 | 34.6-44.6 |
| door +x-y (x wall) 3 | 2.30 | 1341 | 1157 | 0.7 | 1474.5 | 23.7 | 117.7 | 14.9-24.8 |
| door +x-y (x wall) 4 | 2.30 | 761 | 646 | 0.9 | 1494.4 | 13.3 | 115.1 | 30.3-40.2 |
| door +x-y (corner) | 2.30 | 537 | 264 | 0.9 | 1362.9 | 10.3 | 75.9 | 0.7-10.7 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (2.30 m; a corner door's: the gap between its wall ends, 2.30 m); agents are removed past the outer wall's outer face (92.71 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 2183 | 3.1% | 18.1% |
| -x | avenue | 5.66 | 2154 | 3.1% | 17.9% |
| +y | avenue | 5.66 | 2153 | 3.1% | 17.9% |
| -y | avenue | 5.66 | 2241 | 3.2% | 18.6% |
| door +x+y (y wall) 0 | door | 2.30 | 1668 | 2.4% | 34.1% |
| door +x+y (y wall) 1 | door | 2.30 | 1848 | 2.7% | 37.8% |
| door +x+y (y wall) 2 | door | 2.30 | 1722 | 2.5% | 35.2% |
| door +x+y (y wall) 3 | door | 2.30 | 1251 | 1.8% | 25.6% |
| door +x+y (y wall) 4 | door | 2.30 | 779 | 1.1% | 15.9% |
| door +x+y (x wall) 0 | door | 2.30 | 1667 | 2.4% | 34.1% |
| door +x+y (x wall) 1 | door | 2.30 | 1860 | 2.7% | 38.0% |
| door +x+y (x wall) 2 | door | 2.30 | 1739 | 2.5% | 35.6% |
| door +x+y (x wall) 3 | door | 2.30 | 1268 | 1.8% | 25.9% |
| door +x+y (x wall) 4 | door | 2.30 | 743 | 1.1% | 15.2% |
| door +x+y (corner) | door | 2.30 | 572 | 0.8% | 11.7% |
| door -x+y (y wall) 0 | door | 2.30 | 1689 | 2.4% | 34.5% |
| door -x+y (y wall) 1 | door | 2.30 | 1839 | 2.7% | 37.6% |
| door -x+y (y wall) 2 | door | 2.30 | 1681 | 2.4% | 34.4% |
| door -x+y (y wall) 3 | door | 2.30 | 1303 | 1.9% | 26.6% |
| door -x+y (y wall) 4 | door | 2.30 | 786 | 1.1% | 16.1% |
| door -x+y (x wall) 0 | door | 2.30 | 1643 | 2.4% | 33.6% |
| door -x+y (x wall) 1 | door | 2.30 | 1861 | 2.7% | 38.1% |
| door -x+y (x wall) 2 | door | 2.30 | 1715 | 2.5% | 35.1% |
| door -x+y (x wall) 3 | door | 2.30 | 1251 | 1.8% | 25.6% |
| door -x+y (x wall) 4 | door | 2.30 | 898 | 1.3% | 18.4% |
| door -x+y (corner) | door | 2.30 | 550 | 0.8% | 11.2% |
| door -x-y (y wall) 0 | door | 2.30 | 1703 | 2.5% | 34.8% |
| door -x-y (y wall) 1 | door | 2.30 | 1835 | 2.6% | 37.5% |
| door -x-y (y wall) 2 | door | 2.30 | 1760 | 2.5% | 36.0% |
| door -x-y (y wall) 3 | door | 2.30 | 1271 | 1.8% | 26.0% |
| door -x-y (y wall) 4 | door | 2.30 | 750 | 1.1% | 15.3% |
| door -x-y (x wall) 0 | door | 2.30 | 1661 | 2.4% | 34.0% |
| door -x-y (x wall) 1 | door | 2.30 | 1862 | 2.7% | 38.1% |
| door -x-y (x wall) 2 | door | 2.30 | 1774 | 2.6% | 36.3% |
| door -x-y (x wall) 3 | door | 2.30 | 1241 | 1.8% | 25.4% |
| door -x-y (x wall) 4 | door | 2.30 | 720 | 1.0% | 14.7% |
| door -x-y (corner) | door | 2.30 | 557 | 0.8% | 11.4% |
| door +x-y (y wall) 0 | door | 2.30 | 1675 | 2.4% | 34.2% |
| door +x-y (y wall) 1 | door | 2.30 | 1833 | 2.6% | 37.5% |
| door +x-y (y wall) 2 | door | 2.30 | 1704 | 2.5% | 34.8% |
| door +x-y (y wall) 3 | door | 2.30 | 1269 | 1.8% | 25.9% |
| door +x-y (y wall) 4 | door | 2.30 | 766 | 1.1% | 15.7% |
| door +x-y (x wall) 0 | door | 2.30 | 1666 | 2.4% | 34.1% |
| door +x-y (x wall) 1 | door | 2.30 | 1846 | 2.7% | 37.7% |
| door +x-y (x wall) 2 | door | 2.30 | 1715 | 2.5% | 35.1% |
| door +x-y (x wall) 3 | door | 2.30 | 1341 | 1.9% | 27.4% |
| door +x-y (x wall) 4 | door | 2.30 | 761 | 1.1% | 15.6% |
| door +x-y (corner) | door | 2.30 | 537 | 0.8% | 11.0% |
| **doors (44)** | door | 101.20 | 60580 | 87.4% | |
| **avenues (4)** | avenue | 22.64 | 8731 | 12.6% | |

**Unused exit width: 0.0 of 123.8 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 1526.1 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 26.3%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 2356 | 3.4% | 2356 | 3.4% |
| straight +x+y (y wing) 1 | straight | yes | 1891 | 2.7% | 1728 | 2.5% |
| straight +x+y (y wing) 2 | straight | yes | 1619 | 2.3% | 1613 | 2.3% |
| straight +x+y (y wing) 3 | straight | yes | 1140 | 1.6% | 1137 | 1.6% |
| straight +x+y (y wing) 4 | straight | yes | 658 | 0.9% | 642 | 0.9% |
| straight +x+y (x wing) 0 | straight | yes | 2369 | 3.4% | 2369 | 3.4% |
| straight +x+y (x wing) 1 | straight | yes | 1887 | 2.7% | 1742 | 2.5% |
| straight +x+y (x wing) 2 | straight | yes | 1627 | 2.3% | 1619 | 2.3% |
| straight +x+y (x wing) 3 | straight | yes | 1162 | 1.7% | 1158 | 1.7% |
| straight +x+y (x wing) 4 | straight | yes | 618 | 0.9% | 607 | 0.9% |
| corner +x+y | corner | yes | 2150 | 3.1% | 895 | 1.3% |
| straight -x+y (y wing) 0 | straight | yes | 2388 | 3.4% | 2388 | 3.4% |
| straight -x+y (y wing) 1 | straight | yes | 1849 | 2.7% | 1735 | 2.5% |
| straight -x+y (y wing) 2 | straight | yes | 1603 | 2.3% | 1590 | 2.3% |
| straight -x+y (y wing) 3 | straight | yes | 1177 | 1.7% | 1169 | 1.7% |
| straight -x+y (y wing) 4 | straight | yes | 662 | 1.0% | 646 | 0.9% |
| straight -x+y (x wing) 0 | straight | yes | 2337 | 3.4% | 2337 | 3.4% |
| straight -x+y (x wing) 1 | straight | yes | 1865 | 2.7% | 1743 | 2.5% |
| straight -x+y (x wing) 2 | straight | yes | 1647 | 2.4% | 1623 | 2.3% |
| straight -x+y (x wing) 3 | straight | yes | 1154 | 1.7% | 1145 | 1.7% |
| straight -x+y (x wing) 4 | straight | yes | 741 | 1.1% | 733 | 1.1% |
| corner -x+y | corner | yes | 2114 | 3.1% | 757 | 1.1% |
| straight -x-y (y wing) 0 | straight | yes | 2394 | 3.5% | 2394 | 3.5% |
| straight -x-y (y wing) 1 | straight | yes | 1871 | 2.7% | 1737 | 2.5% |
| straight -x-y (y wing) 2 | straight | yes | 1653 | 2.4% | 1649 | 2.4% |
| straight -x-y (y wing) 3 | straight | yes | 1165 | 1.7% | 1163 | 1.7% |
| straight -x-y (y wing) 4 | straight | yes | 630 | 0.9% | 615 | 0.9% |
| straight -x-y (x wing) 0 | straight | yes | 2349 | 3.4% | 2349 | 3.4% |
| straight -x-y (x wing) 1 | straight | yes | 1885 | 2.7% | 1751 | 2.5% |
| straight -x-y (x wing) 2 | straight | yes | 1682 | 2.4% | 1677 | 2.4% |
| straight -x-y (x wing) 3 | straight | yes | 1112 | 1.6% | 1109 | 1.6% |
| straight -x-y (x wing) 4 | straight | yes | 600 | 0.9% | 585 | 0.8% |
| corner -x-y | corner | yes | 2082 | 3.0% | 836 | 1.2% |
| straight +x-y (y wing) 0 | straight | yes | 2379 | 3.4% | 2379 | 3.4% |
| straight +x-y (y wing) 1 | straight | yes | 1900 | 2.7% | 1718 | 2.5% |
| straight +x-y (y wing) 2 | straight | yes | 1606 | 2.3% | 1600 | 2.3% |
| straight +x-y (y wing) 3 | straight | yes | 1173 | 1.7% | 1167 | 1.7% |
| straight +x-y (y wing) 4 | straight | yes | 627 | 0.9% | 611 | 0.9% |
| straight +x-y (x wing) 0 | straight | yes | 2352 | 3.4% | 2352 | 3.4% |
| straight +x-y (x wing) 1 | straight | yes | 1889 | 2.7% | 1728 | 2.5% |
| straight +x-y (x wing) 2 | straight | yes | 1635 | 2.4% | 1624 | 2.3% |
| straight +x-y (x wing) 3 | straight | yes | 1203 | 1.7% | 1201 | 1.7% |
| straight +x-y (x wing) 4 | straight | yes | 640 | 0.9% | 627 | 0.9% |
| corner +x-y | corner | yes | 2129 | 3.1% | 858 | 1.2% |
| **straight (40)** | | | 61495 | | 60116 | 86.7% |
| **corner (4)** | | | 8475 | | 3346 | 4.8% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 5849, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 2183 | 60.2 | 1193.2 | 0.24 | 0.74 | 0.0% |
| -x | 2154 | 60.2 | 1202.0 | 0.24 | 0.72 | 0.0% |
| +y | 2153 | 60.2 | 1204.9 | 0.24 | 0.66 | 0.0% |
| -y | 2241 | 60.2 | 1203.4 | 0.25 | 0.71 | 0.0% |
| door +x+y (y wall) 0 | 1668 | 0.9 | 1182.7 | 0.44 | 1.31 | 4.2% |
| door +x+y (y wall) 1 | 1848 | 1.0 | 1457.8 | 0.40 | 1.35 | 3.4% |
| door +x+y (y wall) 2 | 1722 | 0.7 | 1526.1 | 0.35 | 1.28 | 3.2% |
| door +x+y (y wall) 3 | 1251 | 1.0 | 1513.3 | 0.26 | 1.31 | 3.3% |
| door +x+y (y wall) 4 | 779 | 0.9 | 1424.3 | 0.17 | 1.31 | 3.5% |
| door +x+y (x wall) 0 | 1667 | 0.7 | 1169.4 | 0.45 | 1.35 | 4.2% |
| door +x+y (x wall) 1 | 1860 | 0.9 | 1424.4 | 0.41 | 1.41 | 3.5% |
| door +x+y (x wall) 2 | 1739 | 0.7 | 1510.8 | 0.36 | 1.41 | 3.3% |
| door +x+y (x wall) 3 | 1268 | 0.9 | 1489.0 | 0.27 | 1.38 | 3.3% |
| door +x+y (x wall) 4 | 743 | 0.9 | 1464.8 | 0.16 | 1.28 | 3.4% |
| door +x+y (corner) | 572 | 0.9 | 1110.1 | 0.16 | 0.88 | 1.8% |
| door -x+y (y wall) 0 | 1689 | 0.9 | 1278.4 | 0.41 | 1.35 | 3.1% |
| door -x+y (y wall) 1 | 1839 | 0.7 | 1448.1 | 0.40 | 1.28 | 3.4% |
| door -x+y (y wall) 2 | 1681 | 1.0 | 1511.4 | 0.35 | 1.31 | 3.3% |
| door -x+y (y wall) 3 | 1303 | 1.0 | 1507.7 | 0.27 | 1.31 | 3.3% |
| door -x+y (y wall) 4 | 786 | 0.9 | 1494.6 | 0.16 | 1.31 | 3.3% |
| door -x+y (x wall) 0 | 1643 | 0.7 | 1292.0 | 0.40 | 1.35 | 3.8% |
| door -x+y (x wall) 1 | 1861 | 0.9 | 1480.6 | 0.39 | 1.35 | 3.4% |
| door -x+y (x wall) 2 | 1715 | 0.7 | 1485.3 | 0.36 | 1.31 | 3.4% |
| door -x+y (x wall) 3 | 1251 | 0.7 | 1510.3 | 0.26 | 1.31 | 3.3% |
| door -x+y (x wall) 4 | 898 | 0.7 | 1513.5 | 0.19 | 1.31 | 3.9% |
| door -x+y (corner) | 550 | 0.9 | 1147.4 | 0.15 | 0.85 | 0.9% |
| door -x-y (y wall) 0 | 1703 | 1.0 | 1302.9 | 0.41 | 1.25 | 3.8% |
| door -x-y (y wall) 1 | 1835 | 0.7 | 1452.3 | 0.39 | 1.25 | 3.4% |
| door -x-y (y wall) 2 | 1760 | 0.7 | 1446.1 | 0.38 | 1.31 | 3.4% |
| door -x-y (y wall) 3 | 1271 | 0.9 | 1461.2 | 0.27 | 1.35 | 3.4% |
| door -x-y (y wall) 4 | 750 | 0.7 | 1447.2 | 0.16 | 1.25 | 3.4% |
| door -x-y (x wall) 0 | 1661 | 0.9 | 1301.7 | 0.40 | 1.35 | 3.8% |
| door -x-y (x wall) 1 | 1862 | 0.9 | 1452.4 | 0.40 | 1.35 | 3.4% |
| door -x-y (x wall) 2 | 1774 | 0.7 | 1462.0 | 0.38 | 1.35 | 3.4% |
| door -x-y (x wall) 3 | 1241 | 0.7 | 1465.4 | 0.26 | 1.31 | 3.4% |
| door -x-y (x wall) 4 | 720 | 0.9 | 1391.0 | 0.16 | 1.28 | 3.6% |
| door -x-y (corner) | 557 | 0.7 | 948.9 | 0.18 | 0.88 | 2.1% |
| door +x-y (y wall) 0 | 1675 | 0.9 | 1316.0 | 0.40 | 1.38 | 3.8% |
| door +x-y (y wall) 1 | 1833 | 0.9 | 1438.3 | 0.40 | 1.31 | 3.4% |
| door +x-y (y wall) 2 | 1704 | 0.9 | 1486.4 | 0.36 | 1.25 | 3.3% |
| door +x-y (y wall) 3 | 1269 | 1.0 | 1485.1 | 0.27 | 1.35 | 3.4% |
| door +x-y (y wall) 4 | 766 | 0.9 | 1441.2 | 0.17 | 1.31 | 3.4% |
| door +x-y (x wall) 0 | 1666 | 0.9 | 1212.3 | 0.43 | 1.38 | 4.1% |
| door +x-y (x wall) 1 | 1846 | 0.9 | 1444.0 | 0.40 | 1.38 | 3.4% |
| door +x-y (x wall) 2 | 1715 | 0.7 | 1487.6 | 0.36 | 1.31 | 3.3% |
| door +x-y (x wall) 3 | 1341 | 0.7 | 1474.5 | 0.28 | 1.41 | 3.4% |
| door +x-y (x wall) 4 | 761 | 0.9 | 1494.4 | 0.16 | 1.38 | 3.3% |
| door +x-y (corner) | 537 | 0.9 | 1362.9 | 0.12 | 0.91 | 2.2% |

Mean flow / w J averaged over the doors 0.31, over the avenues 0.24.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 103.1 | 2356 | 1554 / 803 / 999 | 0.7 | 1179.7 | 2.85 | 5.12 | 92% | 87% | 4% | 4.41 |
| straight +x+y (y wing) 1 | 1.20 | 81.5 | 1876 | 1728 / 0 / 206 | 0.7 | 1454.9 | 1.33 | 2.31 | 91% | 70% | 21% | 3.61 |
| straight +x+y (y wing) 2 | 1.20 | 61.0 | 1498 | 1613 / 0 / 10 | 0.7 | 1523.1 | 1.07 | 1.60 | 73% | 63% | 10% | 3.80 |
| straight +x+y (y wing) 3 | 1.20 | 39.4 | 934 | 1137 / 0 / 14 | 0.7 | 1510.3 | 0.76 | 1.91 | 57% | 39% | 18% | 3.24 |
| straight +x+y (y wing) 4 | 1.20 | 18.8 | 400 | 642 / 0 / 18 | 0.7 | 1421.3 | 0.46 | 1.81 | 20% | 16% | 3% | 3.67 |
| straight +x+y (x wing) 0 | 1.20 | 103.1 | 2369 | 1551 / 818 / 1062 | 0.2 | 1166.5 | 2.94 | 5.12 | 92% | 87% | 5% | 4.33 |
| straight +x+y (x wing) 1 | 1.20 | 81.5 | 1862 | 1742 / 0 / 204 | 0.7 | 1421.5 | 1.37 | 2.31 | 93% | 71% | 22% | 3.59 |
| straight +x+y (x wing) 2 | 1.20 | 61.0 | 1497 | 1619 / 0 / 13 | 0.7 | 1507.9 | 1.08 | 1.71 | 73% | 62% | 11% | 3.73 |
| straight +x+y (x wing) 3 | 1.20 | 39.4 | 932 | 1158 / 0 / 20 | 0.7 | 1486.0 | 0.79 | 1.60 | 47% | 39% | 7% | 3.70 |
| straight +x+y (x wing) 4 | 1.20 | 18.8 | 393 | 607 / 0 / 14 | 0.7 | 1461.9 | 0.42 | 1.60 | 31% | 16% | 14% | 2.40 |
| corner +x+y | 1.20 | 186.0 | 1749 | 451 / 444 / 1306 | 0.7 | 1460.3 | 1.51 | 3.01 | 93% | 69% | 24% | 2.78 |
| straight -x+y (y wing) 0 | 1.20 | 103.1 | 2388 | 1570 / 818 / 1178 | 0.2 | 1206.2 | 2.96 | 6.22 | 93% | 85% | 7% | 4.19 |
| straight -x+y (y wing) 1 | 1.20 | 81.5 | 1827 | 1735 / 0 / 133 | 0.7 | 1445.1 | 1.29 | 2.31 | 93% | 79% | 14% | 3.89 |
| straight -x+y (y wing) 2 | 1.20 | 61.0 | 1491 | 1590 / 0 / 23 | 0.7 | 1508.4 | 1.07 | 1.71 | 74% | 62% | 12% | 3.76 |
| straight -x+y (y wing) 3 | 1.20 | 39.4 | 935 | 1169 / 0 / 15 | 0.7 | 1504.9 | 0.79 | 1.71 | 48% | 39% | 9% | 3.55 |
| straight -x+y (y wing) 4 | 1.20 | 18.8 | 399 | 646 / 0 / 17 | 0.7 | 1491.6 | 0.44 | 1.71 | 18% | 17% | 1% | 3.98 |
| straight -x+y (x wing) 0 | 1.20 | 103.1 | 2337 | 1527 / 810 / 982 | 0.2 | 1177.8 | 2.82 | 5.32 | 92% | 85% | 7% | 4.33 |
| straight -x+y (x wing) 1 | 1.20 | 81.5 | 1817 | 1743 / 0 / 182 | 0.7 | 1477.6 | 1.30 | 2.61 | 90% | 70% | 20% | 3.68 |
| straight -x+y (x wing) 2 | 1.20 | 61.0 | 1558 | 1623 / 0 / 48 | 0.7 | 1482.3 | 1.13 | 2.41 | 80% | 70% | 10% | 3.77 |
| straight -x+y (x wing) 3 | 1.20 | 39.4 | 933 | 1145 / 0 / 13 | 0.7 | 1507.3 | 0.77 | 1.71 | 48% | 39% | 9% | 3.70 |
| straight -x+y (x wing) 4 | 1.20 | 18.8 | 400 | 733 / 0 / 10 | 0.7 | 1510.7 | 0.49 | 1.81 | 18% | 16% | 3% | 3.72 |
| corner -x+y | 1.20 | 186.0 | 1781 | 424 / 333 / 1424 | 0.7 | 1486.7 | 1.47 | 4.01 | 91% | 57% | 35% | 2.60 |
| straight -x-y (y wing) 0 | 1.20 | 103.1 | 2394 | 1568 / 827 / 961 | 0.3 | 1173.6 | 2.86 | 5.32 | 92% | 86% | 6% | 4.36 |
| straight -x-y (y wing) 1 | 1.20 | 81.5 | 1848 | 1737 / 0 / 179 | 0.7 | 1449.3 | 1.32 | 2.01 | 87% | 75% | 12% | 4.02 |
| straight -x-y (y wing) 2 | 1.20 | 61.0 | 1475 | 1649 / 0 / 11 | 0.7 | 1443.2 | 1.15 | 1.71 | 73% | 63% | 10% | 3.90 |
| straight -x-y (y wing) 3 | 1.20 | 39.4 | 937 | 1163 / 0 / 5 | 0.7 | 1458.2 | 0.80 | 1.60 | 49% | 39% | 10% | 3.73 |
| straight -x-y (y wing) 4 | 1.20 | 18.8 | 404 | 615 / 0 / 18 | 0.7 | 1444.2 | 0.44 | 1.71 | 19% | 17% | 2% | 3.77 |
| straight -x-y (x wing) 0 | 1.20 | 103.1 | 2349 | 1545 / 804 / 943 | 0.7 | 1170.1 | 2.81 | 5.32 | 92% | 88% | 3% | 4.28 |
| straight -x-y (x wing) 1 | 1.20 | 81.5 | 1863 | 1751 / 0 / 215 | 0.7 | 1449.5 | 1.36 | 2.61 | 90% | 71% | 19% | 3.70 |
| straight -x-y (x wing) 2 | 1.20 | 61.0 | 1547 | 1677 / 0 / 15 | 0.7 | 1459.1 | 1.16 | 1.81 | 78% | 69% | 10% | 3.77 |
| straight -x-y (x wing) 3 | 1.20 | 39.4 | 918 | 1109 / 0 / 12 | 0.7 | 1462.4 | 0.77 | 1.71 | 48% | 39% | 9% | 3.60 |
| straight -x-y (x wing) 4 | 1.20 | 18.8 | 400 | 585 / 0 / 24 | 0.7 | 1388.1 | 0.44 | 1.71 | 33% | 17% | 16% | 2.48 |
| corner -x-y | 1.20 | 186.0 | 1730 | 422 / 414 / 1305 | 0.7 | 1420.2 | 1.51 | 3.81 | 92% | 77% | 15% | 2.86 |
| straight +x-y (y wing) 0 | 1.20 | 103.1 | 2379 | 1560 / 819 / 1043 | 0.3 | 1174.5 | 2.91 | 5.12 | 92% | 89% | 3% | 4.31 |
| straight +x-y (y wing) 1 | 1.20 | 81.5 | 1880 | 1718 / 0 / 230 | 0.7 | 1435.3 | 1.36 | 2.41 | 90% | 72% | 18% | 3.68 |
| straight +x-y (y wing) 2 | 1.20 | 61.0 | 1479 | 1600 / 0 / 9 | 0.7 | 1483.4 | 1.09 | 1.60 | 74% | 66% | 8% | 3.92 |
| straight +x-y (y wing) 3 | 1.20 | 39.4 | 950 | 1167 / 0 / 39 | 0.7 | 1482.2 | 0.81 | 1.91 | 49% | 40% | 9% | 3.70 |
| straight +x-y (y wing) 4 | 1.20 | 18.8 | 395 | 611 / 0 / 22 | 0.7 | 1438.3 | 0.44 | 1.91 | 19% | 17% | 2% | 3.86 |
| straight +x-y (x wing) 0 | 1.20 | 103.1 | 2352 | 1547 / 806 / 979 | 0.5 | 1166.3 | 2.86 | 6.52 | 91% | 89% | 2% | 4.36 |
| straight +x-y (x wing) 1 | 1.20 | 81.5 | 1847 | 1728 / 0 / 223 | 0.7 | 1441.1 | 1.35 | 2.51 | 92% | 67% | 25% | 3.50 |
| straight +x-y (x wing) 2 | 1.20 | 61.0 | 1545 | 1624 / 0 / 11 | 0.7 | 1484.6 | 1.10 | 1.81 | 80% | 69% | 11% | 3.74 |
| straight +x-y (x wing) 3 | 1.20 | 39.4 | 922 | 1201 / 0 / 8 | 0.7 | 1471.5 | 0.82 | 1.60 | 45% | 38% | 7% | 3.76 |
| straight +x-y (x wing) 4 | 1.20 | 18.8 | 404 | 627 / 0 / 27 | 0.7 | 1491.4 | 0.44 | 1.71 | 21% | 16% | 5% | 3.36 |
| corner +x-y | 1.20 | 186.0 | 1712 | 397 / 461 / 1367 | 0.7 | 1467.5 | 1.52 | 3.81 | 92% | 70% | 22% | 2.75 |

The last agent out (agent 8749, t100 1526.1 s): last gangway straight +x+y (y wing) 2, exit door +x+y (y wall) 2. The gangway that cleared last: straight +x+y (y wing) 2 at 1523.1 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 8804 | 7800.4 | 7.07 | 1513.6 / 1429.0 / 1381.2 | 1433.9 / 1414.5 / 1348.2 | 7380211.4 | 13962793 | 0.165 |
| gangway | 3792 | 3512.9 | 7.07 | 1513.5 / 1428.8 / 1379.5 | 1433.9 / 1414.5 / 1348.2 | 7353172.6 | 13008831 | 0.100 |
| walkway | 276 | 257.4 | 5.21 | 783.4 / 550.4 / 15.6 | 402.6 / 211.5 / 9.1 | 117.1 | 88481 | 0.687 |
| avenue | 1920 | 1801.4 | 3.05 | 810.0 / 38.8 / 0.0 | 533.8 / 1.9 / 0.0 | 0.0 | 523261 | 1.334 |
| exit | 4 | 2.0 | 0.00 | 0.7 / 0.0 / 0.0 | 0.7 / 0.0 / 0.0 | 0.0 | 3 | 0.910 |
| concourse | 2812 | 2226.8 | 5.93 | 1453.5 / 78.9 / 54.4 | 1087.7 / 77.7 / 45.7 | 26921.7 | 342216 | 0.706 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 25392 | 16030.4 | 7.87 | 1378.8 / 1355.0 / 1327.4 | 1361.6 / 1355.0 / 1323.0 | 9297473.1 | 22919222 | 0.022 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 208 x 208 from (-104, -104) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 35.5 | -35.5 | gangway | 1.00 | 5.79 | 1383.7 | 1378.3 | 1330.3 | 7518.6 | 0.006 |
| 2 | -33.5 | 33.5 | gangway | 0.99 | 5.72 | 1385.8 | 1379.7 | 1321.9 | 7376.3 | 0.003 |
| 3 | -34.5 | 34.5 | gangway | 1.00 | 5.72 | 1399.8 | 1389.8 | 1335.6 | 7338.7 | 0.007 |
| 4 | 38.5 | 38.5 | gangway | 1.00 | 5.83 | 1427.4 | 1413.4 | 1289.4 | 7323.2 | 0.012 |
| 5 | -32.5 | 32.5 | gangway | 1.00 | 5.64 | 1366.4 | 1347.3 | 1304.6 | 7318.5 | 0.003 |
| 6 | -38.5 | -38.5 | gangway | 1.00 | 5.96 | 1367.8 | 1354.0 | 1234.8 | 7155.8 | 0.012 |
| 7 | -35.5 | -35.5 | gangway | 1.00 | 5.76 | 1355.4 | 1350.5 | 1279.8 | 7132.1 | 0.006 |
| 8 | 33.5 | 33.5 | gangway | 0.99 | 5.64 | 1388.6 | 1382.3 | 1308.3 | 7116.5 | 0.003 |
| 9 | -36.5 | -36.5 | gangway | 1.00 | 5.81 | 1359.4 | 1353.3 | 1257.9 | 7076.9 | 0.006 |
| 10 | 36.5 | -36.5 | gangway | 1.00 | 5.71 | 1384.0 | 1373.0 | 1281.2 | 7060.9 | 0.007 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 36.5 | 38.5 | seat row | 0.50 | 7.28 | 1357.6 | 1353.8 | 1317.7 | 4639.0 | 0.003 |
| 2 | 38.5 | -36.5 | seat row | 0.50 | 7.21 | 1342.2 | 1327.2 | 1307.8 | 4638.1 | 0.003 |
| 3 | 38.5 | 36.5 | seat row | 0.50 | 7.27 | 1360.8 | 1355.0 | 1323.0 | 4622.4 | 0.003 |
| 4 | -36.5 | 38.5 | seat row | 0.50 | 7.21 | 1347.0 | 1344.2 | 1312.5 | 4621.8 | 0.004 |
| 5 | -25.5 | 42.5 | seat row | 0.64 | 6.93 | 1133.0 | 1128.7 | 1118.2 | 4614.8 | 0.010 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 8417; agent-steps of seated agents on another row's clearway: 694063.

## Deposit check

Person-seconds deposited: 36888291.1, of them in excluded cells: 6276.188.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 9393739 overlapping pair-steps: p99 0.0021, max 0.1017 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0021 max 0.1017; venue-geometry 20: p99 0.0009 max 0.0009 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00771 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 76 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.42 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 3927 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
