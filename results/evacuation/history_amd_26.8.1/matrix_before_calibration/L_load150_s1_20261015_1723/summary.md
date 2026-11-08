# Experiment `L_load150_s1`

**Task 5.8 stage 2: venue L, 150% requested (seed 1): every seat + standing on the walkway and concourse (M, L: the achievable maximum, also the 125% request)**

Venue L (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (4000 x 4000), cache key a2f3aaf59c2252b7, content hash 022d17b202313d70). 69311 agents (load 109.3%, requested 150%): every one of the 63424 seats and 5887 standing (spawnOvercrowdedCrowd, seed 1; below), buffer N = 131072, 7189 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 9584778 evaluations, 538013 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.09)** (the L venue's design capacity 63424, jam capacity 171923: 23822.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `cd8e0bbf3411846ca7aa6719887d122a142a7ca1`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-15T17:23:51, 671.7 s wall.

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
| t50 | 2174 | 380.2 |
| t90 | 4740 | 829.1 |
| t100 | 7189 | 1257.4 |

t_p: the step by which ceil(p x 69311) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 1915 | 82 | 60.2 | 954.1 | 22.7 | 55.3 | 59.6-69.6 |
| -x | 5.66 | 1934 | 86 | 60.2 | 962.3 | 22.7 | 59.5 | 59.5-69.4 |
| +y | 5.66 | 1938 | 81 | 60.2 | 947.8 | 23.1 | 60.6 | 60.0-70.0 |
| -y | 5.66 | 1936 | 85 | 60.2 | 961.5 | 22.8 | 63.8 | 59.8-69.8 |
| door +x+y (y wall) 0 | 2.30 | 1736 | 2726 | 0.9 | 1024.4 | 44.2 | 104.7 | 23.1-33.1 |
| door +x+y (y wall) 1 | 2.30 | 1895 | 2254 | 0.9 | 1184.6 | 41.8 | 109.9 | 23.6-33.6 |
| door +x+y (y wall) 2 | 2.30 | 1654 | 1712 | 1.0 | 1142.8 | 37.8 | 107.3 | 3.8-13.8 |
| door +x+y (y wall) 3 | 2.30 | 1232 | 1157 | 0.9 | 1173.6 | 27.4 | 115.1 | 26.1-36.0 |
| door +x+y (y wall) 4 | 2.30 | 932 | 639 | 0.9 | 1165.2 | 20.9 | 107.3 | 12.1-22.0 |
| door +x+y (x wall) 0 | 2.30 | 1692 | 2732 | 0.9 | 998.0 | 44.3 | 115.1 | 15.7-25.7 |
| door +x+y (x wall) 1 | 2.30 | 1882 | 2251 | 0.9 | 1132.5 | 43.4 | 117.7 | 10.7-20.6 |
| door +x+y (x wall) 2 | 2.30 | 1680 | 1711 | 0.9 | 1172.0 | 37.4 | 104.7 | 0.3-10.3 |
| door +x+y (x wall) 3 | 2.30 | 1294 | 1158 | 0.9 | 1161.0 | 29.1 | 109.9 | 2.3-12.2 |
| door +x+y (x wall) 4 | 2.30 | 896 | 641 | 0.9 | 1170.1 | 20.0 | 104.7 | 8.6-18.5 |
| door +x+y (corner) | 2.30 | 519 | 260 | 0.7 | 1030.2 | 13.1 | 73.3 | 81.2-91.1 |
| door -x+y (y wall) 0 | 2.30 | 1691 | 2734 | 0.9 | 1045.1 | 42.2 | 117.7 | 10.8-20.8 |
| door -x+y (y wall) 1 | 2.30 | 1897 | 2259 | 1.0 | 1150.4 | 43.1 | 109.9 | 3.0-12.9 |
| door -x+y (y wall) 2 | 2.30 | 1752 | 1709 | 0.9 | 1230.6 | 37.2 | 107.3 | 2.3-12.2 |
| door -x+y (y wall) 3 | 2.30 | 1281 | 1164 | 0.9 | 1198.6 | 27.9 | 115.1 | 24.8-34.8 |
| door -x+y (y wall) 4 | 2.30 | 800 | 648 | 1.0 | 1240.1 | 16.8 | 107.3 | 6.1-16.1 |
| door -x+y (x wall) 0 | 2.30 | 1734 | 2724 | 0.9 | 1008.9 | 44.9 | 104.7 | 0.3-10.3 |
| door -x+y (x wall) 1 | 2.30 | 1928 | 2254 | 0.9 | 1151.9 | 43.7 | 109.9 | 0.7-10.7 |
| door -x+y (x wall) 2 | 2.30 | 1720 | 1716 | 0.9 | 1257.4 | 35.7 | 109.9 | 1.4-11.4 |
| door -x+y (x wall) 3 | 2.30 | 1294 | 1163 | 0.9 | 1243.9 | 27.2 | 104.7 | 0.7-10.7 |
| door -x+y (x wall) 4 | 2.30 | 768 | 639 | 1.0 | 1230.3 | 16.3 | 104.7 | 33.2-43.2 |
| door -x+y (corner) | 2.30 | 513 | 245 | 0.9 | 1014.3 | 13.2 | 73.3 | 0.7-10.7 |
| door -x-y (y wall) 0 | 2.30 | 1735 | 2736 | 0.9 | 1014.6 | 44.6 | 109.9 | 11.2-21.2 |
| door -x-y (y wall) 1 | 2.30 | 1954 | 2259 | 1.0 | 1154.2 | 44.2 | 109.9 | 17.0-26.9 |
| door -x-y (y wall) 2 | 2.30 | 1649 | 1715 | 1.0 | 1157.7 | 37.2 | 104.7 | 33.1-43.0 |
| door -x-y (y wall) 3 | 2.30 | 1312 | 1163 | 0.7 | 1167.3 | 29.3 | 107.3 | 11.2-21.2 |
| door -x-y (y wall) 4 | 2.30 | 889 | 641 | 0.9 | 1165.1 | 19.9 | 109.9 | 17.3-27.3 |
| door -x-y (x wall) 0 | 2.30 | 1698 | 2721 | 0.9 | 1024.6 | 43.3 | 115.1 | 7.9-17.8 |
| door -x-y (x wall) 1 | 2.30 | 1901 | 2249 | 0.9 | 1139.2 | 43.6 | 109.9 | 1.4-11.4 |
| door -x-y (x wall) 2 | 2.30 | 1690 | 1711 | 0.9 | 1153.2 | 38.3 | 107.3 | 12.4-22.4 |
| door -x-y (x wall) 3 | 2.30 | 1261 | 1165 | 0.9 | 1172.9 | 28.1 | 112.5 | 0.5-10.5 |
| door -x-y (x wall) 4 | 2.30 | 790 | 641 | 0.7 | 1144.2 | 18.0 | 107.3 | 11.4-21.3 |
| door -x-y (corner) | 2.30 | 517 | 247 | 0.9 | 992.6 | 13.6 | 70.6 | 0.5-10.5 |
| door +x-y (y wall) 0 | 2.30 | 1661 | 2722 | 0.9 | 988.0 | 43.9 | 112.5 | 37.3-47.2 |
| door +x-y (y wall) 1 | 2.30 | 1870 | 2251 | 0.9 | 1136.4 | 43.0 | 104.7 | 7.5-17.5 |
| door +x-y (y wall) 2 | 2.30 | 1610 | 1714 | 0.7 | 1135.1 | 37.0 | 112.5 | 4.2-14.2 |
| door +x-y (y wall) 3 | 2.30 | 1181 | 1165 | 0.7 | 1147.2 | 26.9 | 107.3 | 1.6-11.5 |
| door +x-y (y wall) 4 | 2.30 | 912 | 638 | 0.7 | 1103.7 | 21.6 | 112.5 | 10.0-19.9 |
| door +x-y (x wall) 0 | 2.30 | 1722 | 2729 | 0.9 | 1022.7 | 44.0 | 104.7 | 32.2-42.2 |
| door +x-y (x wall) 1 | 2.30 | 1894 | 2254 | 0.7 | 1147.9 | 43.1 | 115.1 | 6.6-16.6 |
| door +x-y (x wall) 2 | 2.30 | 1587 | 1714 | 0.9 | 1151.1 | 36.0 | 115.1 | 35.3-45.3 |
| door +x-y (x wall) 3 | 2.30 | 1268 | 1156 | 0.9 | 1102.4 | 30.0 | 115.1 | 12.1-22.0 |
| door +x-y (x wall) 4 | 2.30 | 957 | 636 | 0.9 | 1132.9 | 22.1 | 107.3 | 0.7-10.7 |
| door +x-y (corner) | 2.30 | 740 | 254 | 0.7 | 902.2 | 21.4 | 73.3 | 0.5-10.5 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (2.30 m; a corner door's: the gap between its wall ends, 2.30 m); agents are removed past the outer wall's outer face (92.71 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 1915 | 2.8% | 19.3% |
| -x | avenue | 5.66 | 1934 | 2.8% | 19.5% |
| +y | avenue | 5.66 | 1938 | 2.8% | 19.5% |
| -y | avenue | 5.66 | 1936 | 2.8% | 19.5% |
| door +x+y (y wall) 0 | door | 2.30 | 1736 | 2.5% | 43.1% |
| door +x+y (y wall) 1 | door | 2.30 | 1895 | 2.7% | 47.0% |
| door +x+y (y wall) 2 | door | 2.30 | 1654 | 2.4% | 41.0% |
| door +x+y (y wall) 3 | door | 2.30 | 1232 | 1.8% | 30.6% |
| door +x+y (y wall) 4 | door | 2.30 | 932 | 1.3% | 23.1% |
| door +x+y (x wall) 0 | door | 2.30 | 1692 | 2.4% | 42.0% |
| door +x+y (x wall) 1 | door | 2.30 | 1882 | 2.7% | 46.7% |
| door +x+y (x wall) 2 | door | 2.30 | 1680 | 2.4% | 41.7% |
| door +x+y (x wall) 3 | door | 2.30 | 1294 | 1.9% | 32.1% |
| door +x+y (x wall) 4 | door | 2.30 | 896 | 1.3% | 22.2% |
| door +x+y (corner) | door | 2.30 | 519 | 0.7% | 12.9% |
| door -x+y (y wall) 0 | door | 2.30 | 1691 | 2.4% | 42.0% |
| door -x+y (y wall) 1 | door | 2.30 | 1897 | 2.7% | 47.1% |
| door -x+y (y wall) 2 | door | 2.30 | 1752 | 2.5% | 43.5% |
| door -x+y (y wall) 3 | door | 2.30 | 1281 | 1.8% | 31.8% |
| door -x+y (y wall) 4 | door | 2.30 | 800 | 1.2% | 19.9% |
| door -x+y (x wall) 0 | door | 2.30 | 1734 | 2.5% | 43.0% |
| door -x+y (x wall) 1 | door | 2.30 | 1928 | 2.8% | 47.8% |
| door -x+y (x wall) 2 | door | 2.30 | 1720 | 2.5% | 42.7% |
| door -x+y (x wall) 3 | door | 2.30 | 1294 | 1.9% | 32.1% |
| door -x+y (x wall) 4 | door | 2.30 | 768 | 1.1% | 19.1% |
| door -x+y (corner) | door | 2.30 | 513 | 0.7% | 12.7% |
| door -x-y (y wall) 0 | door | 2.30 | 1735 | 2.5% | 43.1% |
| door -x-y (y wall) 1 | door | 2.30 | 1954 | 2.8% | 48.5% |
| door -x-y (y wall) 2 | door | 2.30 | 1649 | 2.4% | 40.9% |
| door -x-y (y wall) 3 | door | 2.30 | 1312 | 1.9% | 32.6% |
| door -x-y (y wall) 4 | door | 2.30 | 889 | 1.3% | 22.1% |
| door -x-y (x wall) 0 | door | 2.30 | 1698 | 2.4% | 42.1% |
| door -x-y (x wall) 1 | door | 2.30 | 1901 | 2.7% | 47.2% |
| door -x-y (x wall) 2 | door | 2.30 | 1690 | 2.4% | 41.9% |
| door -x-y (x wall) 3 | door | 2.30 | 1261 | 1.8% | 31.3% |
| door -x-y (x wall) 4 | door | 2.30 | 790 | 1.1% | 19.6% |
| door -x-y (corner) | door | 2.30 | 517 | 0.7% | 12.8% |
| door +x-y (y wall) 0 | door | 2.30 | 1661 | 2.4% | 41.2% |
| door +x-y (y wall) 1 | door | 2.30 | 1870 | 2.7% | 46.4% |
| door +x-y (y wall) 2 | door | 2.30 | 1610 | 2.3% | 40.0% |
| door +x-y (y wall) 3 | door | 2.30 | 1181 | 1.7% | 29.3% |
| door +x-y (y wall) 4 | door | 2.30 | 912 | 1.3% | 22.6% |
| door +x-y (x wall) 0 | door | 2.30 | 1722 | 2.5% | 42.7% |
| door +x-y (x wall) 1 | door | 2.30 | 1894 | 2.7% | 47.0% |
| door +x-y (x wall) 2 | door | 2.30 | 1587 | 2.3% | 39.4% |
| door +x-y (x wall) 3 | door | 2.30 | 1268 | 1.8% | 31.5% |
| door +x-y (x wall) 4 | door | 2.30 | 957 | 1.4% | 23.7% |
| door +x-y (corner) | door | 2.30 | 740 | 1.1% | 18.4% |
| **doors (44)** | door | 101.20 | 61588 | 88.9% | |
| **avenues (4)** | avenue | 22.64 | 7723 | 11.1% | |

**Unused exit width: 0.0 of 123.8 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 1257.4 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 31.9%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 2327 | 3.4% | 2327 | 3.4% |
| straight +x+y (y wing) 1 | straight | yes | 1889 | 2.7% | 1797 | 2.6% |
| straight +x+y (y wing) 2 | straight | yes | 1595 | 2.3% | 1572 | 2.3% |
| straight +x+y (y wing) 3 | straight | yes | 1163 | 1.7% | 1149 | 1.7% |
| straight +x+y (y wing) 4 | straight | yes | 748 | 1.1% | 737 | 1.1% |
| straight +x+y (x wing) 0 | straight | yes | 2334 | 3.4% | 2334 | 3.4% |
| straight +x+y (x wing) 1 | straight | yes | 1866 | 2.7% | 1796 | 2.6% |
| straight +x+y (x wing) 2 | straight | yes | 1636 | 2.4% | 1610 | 2.3% |
| straight +x+y (x wing) 3 | straight | yes | 1161 | 1.7% | 1150 | 1.7% |
| straight +x+y (x wing) 4 | straight | yes | 763 | 1.1% | 752 | 1.1% |
| corner +x+y | corner | yes | 2020 | 2.9% | 645 | 0.9% |
| straight -x+y (y wing) 0 | straight | yes | 2330 | 3.4% | 2330 | 3.4% |
| straight -x+y (y wing) 1 | straight | yes | 1901 | 2.7% | 1805 | 2.6% |
| straight -x+y (y wing) 2 | straight | yes | 1654 | 2.4% | 1639 | 2.4% |
| straight -x+y (y wing) 3 | straight | yes | 1179 | 1.7% | 1176 | 1.7% |
| straight -x+y (y wing) 4 | straight | yes | 666 | 1.0% | 647 | 0.9% |
| straight -x+y (x wing) 0 | straight | yes | 2306 | 3.3% | 2306 | 3.3% |
| straight -x+y (x wing) 1 | straight | yes | 1945 | 2.8% | 1827 | 2.6% |
| straight -x+y (x wing) 2 | straight | yes | 1616 | 2.3% | 1607 | 2.3% |
| straight -x+y (x wing) 3 | straight | yes | 1199 | 1.7% | 1196 | 1.7% |
| straight -x+y (x wing) 4 | straight | yes | 625 | 0.9% | 611 | 0.9% |
| corner -x+y | corner | yes | 1995 | 2.9% | 722 | 1.0% |
| straight -x-y (y wing) 0 | straight | yes | 2326 | 3.4% | 2325 | 3.4% |
| straight -x-y (y wing) 1 | straight | yes | 1919 | 2.8% | 1846 | 2.7% |
| straight -x-y (y wing) 2 | straight | yes | 1581 | 2.3% | 1565 | 2.3% |
| straight -x-y (y wing) 3 | straight | yes | 1186 | 1.7% | 1182 | 1.7% |
| straight -x-y (y wing) 4 | straight | yes | 751 | 1.1% | 734 | 1.1% |
| straight -x-y (x wing) 0 | straight | yes | 2364 | 3.4% | 2364 | 3.4% |
| straight -x-y (x wing) 1 | straight | yes | 1881 | 2.7% | 1809 | 2.6% |
| straight -x-y (x wing) 2 | straight | yes | 1599 | 2.3% | 1585 | 2.3% |
| straight -x-y (x wing) 3 | straight | yes | 1177 | 1.7% | 1169 | 1.7% |
| straight -x-y (x wing) 4 | straight | yes | 631 | 0.9% | 621 | 0.9% |
| corner -x-y | corner | yes | 1982 | 2.9% | 665 | 1.0% |
| straight +x-y (y wing) 0 | straight | yes | 2305 | 3.3% | 2305 | 3.3% |
| straight +x-y (y wing) 1 | straight | yes | 1877 | 2.7% | 1773 | 2.6% |
| straight +x-y (y wing) 2 | straight | yes | 1644 | 2.4% | 1590 | 2.3% |
| straight +x-y (y wing) 3 | straight | yes | 1069 | 1.5% | 1044 | 1.5% |
| straight +x-y (y wing) 4 | straight | yes | 714 | 1.0% | 704 | 1.0% |
| straight +x-y (x wing) 0 | straight | yes | 2301 | 3.3% | 2301 | 3.3% |
| straight +x-y (x wing) 1 | straight | yes | 1924 | 2.8% | 1788 | 2.6% |
| straight +x-y (x wing) 2 | straight | yes | 1567 | 2.3% | 1528 | 2.2% |
| straight +x-y (x wing) 3 | straight | yes | 1188 | 1.7% | 1153 | 1.7% |
| straight +x-y (x wing) 4 | straight | yes | 793 | 1.1% | 777 | 1.1% |
| corner +x-y | corner | yes | 2184 | 3.2% | 904 | 1.3% |
| **straight (40)** | | | 61700 | | 60531 | 87.3% |
| **corner (4)** | | | 8181 | | 2936 | 4.2% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 5844, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 1915 | 60.2 | 954.1 | 0.27 | 0.66 | 0.0% |
| -x | 1934 | 60.2 | 962.3 | 0.27 | 0.71 | 0.0% |
| +y | 1938 | 60.2 | 947.8 | 0.28 | 0.72 | 0.0% |
| -y | 1936 | 60.2 | 961.5 | 0.27 | 0.76 | 0.0% |
| door +x+y (y wall) 0 | 1736 | 0.9 | 1024.4 | 0.53 | 1.25 | 5.8% |
| door +x+y (y wall) 1 | 1895 | 0.9 | 1184.6 | 0.50 | 1.31 | 5.0% |
| door +x+y (y wall) 2 | 1654 | 1.0 | 1142.8 | 0.45 | 1.28 | 5.2% |
| door +x+y (y wall) 3 | 1232 | 0.9 | 1173.6 | 0.33 | 1.38 | 4.2% |
| door +x+y (y wall) 4 | 932 | 0.9 | 1165.2 | 0.25 | 1.28 | 5.1% |
| door +x+y (x wall) 0 | 1692 | 0.9 | 998.0 | 0.53 | 1.38 | 5.0% |
| door +x+y (x wall) 1 | 1882 | 0.9 | 1132.5 | 0.52 | 1.41 | 4.4% |
| door +x+y (x wall) 2 | 1680 | 0.9 | 1172.0 | 0.45 | 1.25 | 4.2% |
| door +x+y (x wall) 3 | 1294 | 0.9 | 1161.0 | 0.35 | 1.31 | 4.3% |
| door +x+y (x wall) 4 | 896 | 0.9 | 1170.1 | 0.24 | 1.25 | 5.1% |
| door +x+y (corner) | 519 | 0.7 | 1030.2 | 0.16 | 0.88 | 1.0% |
| door -x+y (y wall) 0 | 1691 | 0.9 | 1045.1 | 0.51 | 1.41 | 4.8% |
| door -x+y (y wall) 1 | 1897 | 1.0 | 1150.4 | 0.51 | 1.31 | 4.3% |
| door -x+y (y wall) 2 | 1752 | 0.9 | 1230.6 | 0.44 | 1.28 | 4.0% |
| door -x+y (y wall) 3 | 1281 | 0.9 | 1198.6 | 0.33 | 1.38 | 5.0% |
| door -x+y (y wall) 4 | 800 | 1.0 | 1240.1 | 0.20 | 1.28 | 5.6% |
| door -x+y (x wall) 0 | 1734 | 0.9 | 1008.9 | 0.54 | 1.25 | 4.9% |
| door -x+y (x wall) 1 | 1928 | 0.9 | 1151.9 | 0.52 | 1.31 | 4.3% |
| door -x+y (x wall) 2 | 1720 | 0.9 | 1257.4 | 0.43 | 1.31 | 4.7% |
| door -x+y (x wall) 3 | 1294 | 0.9 | 1243.9 | 0.32 | 1.25 | 4.8% |
| door -x+y (x wall) 4 | 768 | 1.0 | 1230.3 | 0.19 | 1.25 | 4.8% |
| door -x+y (corner) | 513 | 0.9 | 1014.3 | 0.16 | 0.88 | 2.0% |
| door -x-y (y wall) 0 | 1735 | 0.9 | 1014.6 | 0.53 | 1.31 | 4.9% |
| door -x-y (y wall) 1 | 1954 | 1.0 | 1154.2 | 0.53 | 1.31 | 5.2% |
| door -x-y (y wall) 2 | 1649 | 1.0 | 1157.7 | 0.44 | 1.25 | 5.1% |
| door -x-y (y wall) 3 | 1312 | 0.7 | 1167.3 | 0.35 | 1.28 | 5.1% |
| door -x-y (y wall) 4 | 889 | 0.9 | 1165.1 | 0.24 | 1.31 | 5.1% |
| door -x-y (x wall) 0 | 1698 | 0.9 | 1024.6 | 0.52 | 1.38 | 4.9% |
| door -x-y (x wall) 1 | 1901 | 0.9 | 1139.2 | 0.52 | 1.31 | 4.3% |
| door -x-y (x wall) 2 | 1690 | 0.9 | 1153.2 | 0.46 | 1.28 | 4.3% |
| door -x-y (x wall) 3 | 1261 | 0.9 | 1172.9 | 0.34 | 1.35 | 5.1% |
| door -x-y (x wall) 4 | 790 | 0.7 | 1144.2 | 0.22 | 1.28 | 5.2% |
| door -x-y (corner) | 517 | 0.9 | 992.6 | 0.16 | 0.85 | 0.0% |
| door +x-y (y wall) 0 | 1661 | 0.9 | 988.0 | 0.52 | 1.35 | 5.0% |
| door +x-y (y wall) 1 | 1870 | 0.9 | 1136.4 | 0.51 | 1.25 | 5.3% |
| door +x-y (y wall) 2 | 1610 | 0.7 | 1135.1 | 0.44 | 1.35 | 4.4% |
| door +x-y (y wall) 3 | 1181 | 0.7 | 1147.2 | 0.32 | 1.28 | 5.2% |
| door +x-y (y wall) 4 | 912 | 0.7 | 1103.7 | 0.26 | 1.35 | 5.4% |
| door +x-y (x wall) 0 | 1722 | 0.9 | 1022.7 | 0.53 | 1.25 | 5.8% |
| door +x-y (x wall) 1 | 1894 | 0.7 | 1147.9 | 0.52 | 1.38 | 4.3% |
| door +x-y (x wall) 2 | 1587 | 0.9 | 1151.1 | 0.43 | 1.38 | 4.3% |
| door +x-y (x wall) 3 | 1268 | 0.9 | 1102.4 | 0.36 | 1.38 | 4.5% |
| door +x-y (x wall) 4 | 957 | 0.9 | 1132.9 | 0.26 | 1.28 | 5.3% |
| door +x-y (corner) | 740 | 0.7 | 902.2 | 0.26 | 0.88 | 3.3% |

Mean flow / w J averaged over the doors 0.39, over the avenues 0.27.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 103.1 | 2327 | 1601 / 727 / 737 | 0.3 | 931.0 | 3.29 | 5.32 | 90% | 86% | 4% | 4.53 |
| straight +x+y (y wing) 1 | 1.20 | 81.5 | 1875 | 1797 / 0 / 175 | 0.7 | 1181.7 | 1.67 | 3.11 | 87% | 73% | 13% | 4.10 |
| straight +x+y (y wing) 2 | 1.20 | 61.0 | 1491 | 1572 / 0 / 30 | 0.7 | 1139.9 | 1.41 | 2.11 | 75% | 64% | 10% | 3.88 |
| straight +x+y (y wing) 3 | 1.20 | 39.4 | 960 | 1149 / 0 / 18 | 0.7 | 1170.7 | 1.00 | 2.21 | 51% | 40% | 11% | 3.58 |
| straight +x+y (y wing) 4 | 1.20 | 18.8 | 411 | 737 / 0 / 18 | 0.7 | 1162.3 | 0.65 | 2.51 | 21% | 17% | 3% | 3.92 |
| straight +x+y (x wing) 0 | 1.20 | 103.1 | 2334 | 1540 / 794 / 923 | 0.2 | 868.2 | 3.75 | 5.82 | 90% | 84% | 6% | 4.43 |
| straight +x+y (x wing) 1 | 1.20 | 81.5 | 1840 | 1796 / 0 / 151 | 0.7 | 1129.5 | 1.72 | 3.31 | 89% | 77% | 12% | 3.98 |
| straight +x+y (x wing) 2 | 1.20 | 61.0 | 1549 | 1610 / 0 / 29 | 0.7 | 1169.1 | 1.40 | 2.11 | 74% | 66% | 8% | 3.99 |
| straight +x+y (x wing) 3 | 1.20 | 39.4 | 933 | 1150 / 0 / 12 | 0.7 | 1158.1 | 1.00 | 2.11 | 47% | 38% | 9% | 3.61 |
| straight +x+y (x wing) 4 | 1.20 | 18.8 | 407 | 752 / 0 / 18 | 0.7 | 1167.2 | 0.66 | 2.11 | 24% | 17% | 7% | 3.15 |
| corner +x+y | 1.20 | 186.0 | 1742 | 384 / 262 / 1440 | 0.7 | 1143.2 | 1.83 | 3.81 | 90% | 64% | 26% | 2.76 |
| straight -x+y (y wing) 0 | 1.20 | 103.1 | 2330 | 1545 / 787 / 1053 | 0.2 | 896.7 | 3.77 | 6.72 | 90% | 86% | 4% | 4.42 |
| straight -x+y (y wing) 1 | 1.20 | 81.5 | 1867 | 1805 / 0 / 192 | 0.7 | 1147.6 | 1.74 | 3.91 | 91% | 76% | 15% | 3.62 |
| straight -x+y (y wing) 2 | 1.20 | 61.0 | 1553 | 1639 / 0 / 22 | 0.7 | 1227.7 | 1.35 | 2.41 | 72% | 61% | 10% | 3.70 |
| straight -x+y (y wing) 3 | 1.20 | 39.4 | 944 | 1176 / 0 / 15 | 0.7 | 1195.7 | 1.00 | 2.41 | 45% | 38% | 7% | 3.75 |
| straight -x+y (y wing) 4 | 1.20 | 18.8 | 398 | 647 / 0 / 22 | 0.7 | 1237.1 | 0.54 | 2.21 | 17% | 16% | 1% | 4.02 |
| straight -x+y (x wing) 0 | 1.20 | 103.1 | 2306 | 1606 / 700 / 776 | 0.3 | 928.1 | 3.32 | 6.52 | 89% | 86% | 3% | 4.63 |
| straight -x+y (x wing) 1 | 1.20 | 81.5 | 1924 | 1827 / 0 / 212 | 0.7 | 1149.0 | 1.78 | 3.61 | 90% | 74% | 16% | 3.87 |
| straight -x+y (x wing) 2 | 1.20 | 61.0 | 1481 | 1607 / 0 / 15 | 0.7 | 1254.4 | 1.29 | 2.01 | 65% | 58% | 7% | 4.00 |
| straight -x+y (x wing) 3 | 1.20 | 39.4 | 951 | 1196 / 0 / 19 | 0.7 | 1241.0 | 0.98 | 2.11 | 45% | 38% | 7% | 3.79 |
| straight -x+y (x wing) 4 | 1.20 | 18.8 | 414 | 611 / 0 / 29 | 0.7 | 1227.3 | 0.52 | 2.11 | 34% | 17% | 17% | 2.50 |
| corner -x+y | 1.20 | 186.0 | 1698 | 392 / 330 / 1357 | 0.7 | 1213.3 | 1.71 | 3.91 | 93% | 64% | 29% | 2.77 |
| straight -x-y (y wing) 0 | 1.20 | 103.1 | 2326 | 1602 / 723 / 782 | 0.2 | 924.7 | 3.36 | 5.22 | 90% | 87% | 3% | 4.67 |
| straight -x-y (y wing) 1 | 1.20 | 81.5 | 1896 | 1846 / 0 / 151 | 0.7 | 1151.2 | 1.74 | 3.41 | 86% | 75% | 11% | 4.28 |
| straight -x-y (y wing) 2 | 1.20 | 61.0 | 1489 | 1565 / 0 / 20 | 0.7 | 1154.7 | 1.37 | 2.01 | 78% | 64% | 15% | 3.77 |
| straight -x-y (y wing) 3 | 1.20 | 39.4 | 941 | 1182 / 0 / 7 | 0.7 | 1164.4 | 1.02 | 2.21 | 47% | 39% | 8% | 3.74 |
| straight -x-y (y wing) 4 | 1.20 | 18.8 | 401 | 734 / 0 / 18 | 0.7 | 1162.1 | 0.65 | 2.21 | 17% | 17% | 0% | 4.25 |
| straight -x-y (x wing) 0 | 1.20 | 103.1 | 2364 | 1568 / 796 / 863 | 0.5 | 909.3 | 3.55 | 5.32 | 90% | 82% | 9% | 4.28 |
| straight -x-y (x wing) 1 | 1.20 | 81.5 | 1863 | 1809 / 0 / 173 | 0.7 | 1136.2 | 1.75 | 3.01 | 91% | 78% | 13% | 3.87 |
| straight -x-y (x wing) 2 | 1.20 | 61.0 | 1498 | 1585 / 0 / 17 | 0.7 | 1150.2 | 1.39 | 2.11 | 77% | 64% | 13% | 3.63 |
| straight -x-y (x wing) 3 | 1.20 | 39.4 | 947 | 1169 / 0 / 11 | 0.7 | 1170.0 | 1.01 | 2.01 | 50% | 39% | 11% | 3.57 |
| straight -x-y (x wing) 4 | 1.20 | 18.8 | 411 | 621 / 0 / 35 | 0.7 | 1141.3 | 0.58 | 2.21 | 18% | 18% | 0% | 4.15 |
| corner -x-y | 1.20 | 186.0 | 1729 | 394 / 271 / 1415 | 0.7 | 1138.1 | 1.83 | 4.91 | 90% | 70% | 20% | 2.88 |
| straight +x-y (y wing) 0 | 1.20 | 103.1 | 2305 | 1534 / 771 / 971 | 0.5 | 897.3 | 3.65 | 5.72 | 91% | 82% | 9% | 4.28 |
| straight +x-y (y wing) 1 | 1.20 | 81.5 | 1850 | 1773 / 0 / 217 | 0.7 | 1133.4 | 1.76 | 3.81 | 75% | 75% | 0% | 4.35 |
| straight +x-y (y wing) 2 | 1.20 | 61.0 | 1558 | 1590 / 0 / 58 | 0.7 | 1132.2 | 1.46 | 2.71 | 78% | 72% | 6% | 3.88 |
| straight +x-y (y wing) 3 | 1.20 | 39.4 | 941 | 1044 / 0 / 29 | 0.7 | 1144.2 | 0.94 | 2.21 | 44% | 43% | 2% | 4.03 |
| straight +x-y (y wing) 4 | 1.20 | 18.8 | 414 | 704 / 0 / 11 | 0.7 | 1100.7 | 0.65 | 2.11 | 21% | 20% | 1% | 3.92 |
| straight +x-y (x wing) 0 | 1.20 | 103.1 | 2301 | 1595 / 706 / 610 | 0.2 | 945.5 | 3.08 | 5.42 | 88% | 85% | 3% | 4.65 |
| straight +x-y (x wing) 1 | 1.20 | 81.5 | 1920 | 1788 / 0 / 203 | 0.7 | 1144.9 | 1.74 | 3.41 | 80% | 77% | 3% | 4.27 |
| straight +x-y (x wing) 2 | 1.20 | 61.0 | 1470 | 1528 / 0 / 41 | 0.7 | 1148.1 | 1.37 | 2.21 | 72% | 66% | 6% | 3.97 |
| straight +x-y (x wing) 3 | 1.20 | 39.4 | 954 | 1153 / 0 / 39 | 0.7 | 1099.5 | 1.08 | 2.21 | 48% | 42% | 5% | 3.90 |
| straight +x-y (x wing) 4 | 1.20 | 18.8 | 403 | 777 / 0 / 18 | 0.7 | 1129.9 | 0.70 | 2.21 | 18% | 18% | 1% | 4.16 |
| corner +x-y | 1.20 | 186.0 | 1751 | 610 / 294 / 1385 | 0.7 | 1105.9 | 2.07 | 5.02 | 90% | 52% | 38% | 2.63 |

The last agent out (agent 16727, t100 1257.4 s): last gangway straight -x+y (x wing) 2, exit door -x+y (x wall) 2. The gangway that cleared last: straight -x+y (x wing) 2 at 1254.4 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 8804 | 7800.4 | 7.09 | 1250.9 / 1185.3 / 1119.8 | 1169.4 / 1154.2 / 1093.2 | 5468795.2 | 11286123 | 0.200 |
| gangway | 3792 | 3512.9 | 7.09 | 1250.9 / 1185.2 / 1118.2 | 1169.4 / 1154.2 / 1093.2 | 5437742.7 | 10335805 | 0.129 |
| walkway | 276 | 257.4 | 5.35 | 683.2 / 530.7 / 261.8 | 571.6 / 451.4 / 126.6 | 2043.4 | 124913 | 0.435 |
| avenue | 1920 | 1801.4 | 3.20 | 843.4 / 60.7 / 0.0 | 630.0 / 1.9 / 0.0 | 0.0 | 462900 | 1.333 |
| exit | 4 | 2.0 | 0.00 | 0.7 / 0.0 / 0.0 | 0.7 / 0.0 / 0.0 | 0.0 | 3 | 0.844 |
| concourse | 2812 | 2226.8 | 6.11 | 1197.1 / 111.4 / 54.9 | 990.1 / 82.4 / 50.4 | 29009.0 | 362502 | 0.694 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 25392 | 16030.4 | 7.67 | 1137.4 / 1130.2 / 1094.7 | 1132.5 / 1130.2 / 1089.5 | 6908861.1 | 17303986 | 0.029 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 208 x 208 from (-104, -104) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -35.5 | 35.5 | gangway | 1.00 | 5.74 | 1147.4 | 1145.3 | 1093.2 | 6144.2 | 0.008 |
| 2 | -34.5 | 34.5 | gangway | 1.00 | 5.69 | 1142.1 | 1132.5 | 1045.1 | 5709.9 | 0.007 |
| 3 | -32.5 | 32.5 | gangway | 1.00 | 5.84 | 1086.3 | 1065.7 | 993.8 | 5626.3 | 0.008 |
| 4 | -39.5 | 39.5 | gangway | 1.00 | 5.89 | 1160.7 | 1152.8 | 985.6 | 5626.2 | 0.021 |
| 5 | -35.5 | -35.5 | gangway | 1.00 | 5.95 | 1062.7 | 1059.6 | 951.3 | 5459.1 | 0.010 |
| 6 | -34.5 | -34.5 | gangway | 1.00 | 5.73 | 1053.8 | 1047.2 | 980.9 | 5445.4 | 0.009 |
| 7 | 33.5 | 33.5 | gangway | 0.99 | 5.63 | 1055.7 | 1050.7 | 996.6 | 5382.3 | 0.008 |
| 8 | -43.5 | 42.5 | gangway | 1.00 | 6.06 | 1097.0 | 1076.9 | 926.1 | 5338.8 | 0.021 |
| 9 | 32.5 | 32.5 | gangway | 1.00 | 5.61 | 1048.4 | 1041.7 | 967.1 | 5329.6 | 0.008 |
| 10 | 32.5 | -32.5 | gangway | 1.00 | 5.73 | 1024.4 | 1014.6 | 959.4 | 5294.7 | 0.009 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -36.5 | 38.5 | seat row | 0.50 | 7.21 | 1132.5 | 1130.2 | 1089.5 | 3698.3 | 0.007 |
| 2 | -38.5 | 36.5 | seat row | 0.50 | 7.24 | 1107.5 | 1105.1 | 1068.2 | 3621.9 | 0.005 |
| 3 | -35.5 | 38.5 | seat row | 0.50 | 7.08 | 1110.8 | 1097.5 | 1037.4 | 3613.0 | 0.006 |
| 4 | -38.5 | -36.5 | seat row | 0.50 | 7.35 | 1023.4 | 1021.5 | 996.6 | 3560.0 | 0.007 |
| 5 | -38.5 | 35.5 | seat row | 0.50 | 7.04 | 1056.6 | 1032.8 | 1019.2 | 3540.2 | 0.004 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 7299; agent-steps of seated agents on another row's clearway: 1468750.

## Deposit check

Person-seconds deposited: 28596372.2, of them in excluded cells: 6263.516.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 6199621 overlapping pair-steps: p99 0.0031, max 0.0943 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0031 max 0.0943; venue-geometry 12: p99 0.0010 max 0.0010 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00770 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 47 (longest 2 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.43 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 3507 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
