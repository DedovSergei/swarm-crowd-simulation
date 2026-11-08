# Experiment `L_load150_s2`

**Task 5.8 stage 2: venue L, 150% requested (seed 2): every seat + standing on the walkway and concourse (M, L: the achievable maximum, also the 125% request)**

Venue L (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (4000 x 4000), cache key a2f3aaf59c2252b7, content hash 022d17b202313d70). 69311 agents (load 109.3%, requested 150%): every one of the 63424 seats and 5887 standing (spawnOvercrowdedCrowd, seed 2; below), buffer N = 131072, 6913 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 9616939 evaluations, 557085 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.09)** (the L venue's design capacity 63424, jam capacity 171923: 23822.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `cd8e0bbf3411846ca7aa6719887d122a142a7ca1`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-15T17:35:44, 654.5 s wall.

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
| t50 | 2183 | 381.8 |
| t90 | 4759 | 832.4 |
| t100 | 6913 | 1209.1 |

t_p: the step by which ceil(p x 69311) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 1940 | 89 | 60.2 | 930.7 | 23.6 | 61.7 | 59.6-69.6 |
| -x | 5.66 | 1944 | 85 | 60.2 | 931.0 | 23.7 | 60.6 | 59.6-69.6 |
| +y | 5.66 | 1936 | 84 | 60.2 | 924.2 | 23.7 | 55.3 | 59.6-69.6 |
| -y | 5.66 | 1960 | 90 | 60.2 | 923.0 | 24.1 | 59.5 | 59.8-69.8 |
| door +x+y (y wall) 0 | 2.30 | 1731 | 2724 | 0.9 | 1068.2 | 42.3 | 107.3 | 34.8-44.8 |
| door +x+y (y wall) 1 | 2.30 | 1965 | 2257 | 1.0 | 1185.3 | 43.3 | 112.5 | 4.9-14.9 |
| door +x+y (y wall) 2 | 2.30 | 1669 | 1713 | 0.7 | 1207.9 | 36.1 | 104.7 | 32.9-42.9 |
| door +x+y (y wall) 3 | 2.30 | 1224 | 1159 | 1.0 | 1209.1 | 26.4 | 109.9 | 23.4-33.4 |
| door +x+y (y wall) 4 | 2.30 | 819 | 640 | 0.9 | 1189.7 | 18.0 | 112.5 | 14.2-24.1 |
| door +x+y (x wall) 0 | 2.30 | 1732 | 2728 | 0.7 | 1061.2 | 42.6 | 107.3 | 8.7-18.7 |
| door +x+y (x wall) 1 | 2.30 | 1935 | 2255 | 0.9 | 1154.6 | 43.7 | 109.9 | 3.1-13.1 |
| door +x+y (x wall) 2 | 2.30 | 1704 | 1717 | 0.7 | 1200.4 | 37.0 | 109.9 | 22.6-32.5 |
| door +x+y (x wall) 3 | 2.30 | 1205 | 1163 | 0.9 | 1207.9 | 26.0 | 107.3 | 38.0-47.9 |
| door +x+y (x wall) 4 | 2.30 | 853 | 638 | 0.9 | 1162.3 | 19.2 | 112.5 | 7.2-17.1 |
| door +x+y (corner) | 2.30 | 561 | 245 | 0.9 | 1092.5 | 13.4 | 73.3 | 74.5-84.5 |
| door -x+y (y wall) 0 | 2.30 | 1729 | 2722 | 0.9 | 1017.4 | 44.4 | 109.9 | 0.7-10.7 |
| door -x+y (y wall) 1 | 2.30 | 1892 | 2252 | 0.7 | 1169.1 | 42.2 | 107.3 | 13.1-23.1 |
| door -x+y (y wall) 2 | 2.30 | 1674 | 1708 | 1.0 | 1194.1 | 36.6 | 107.3 | 25.2-35.2 |
| door -x+y (y wall) 3 | 2.30 | 1339 | 1168 | 1.0 | 1179.0 | 29.6 | 109.9 | 10.1-20.1 |
| door -x+y (y wall) 4 | 2.30 | 776 | 639 | 0.9 | 1181.8 | 17.1 | 115.1 | 10.7-20.6 |
| door -x+y (x wall) 0 | 2.30 | 1700 | 2723 | 0.7 | 1007.3 | 44.0 | 112.5 | 16.8-26.8 |
| door -x+y (x wall) 1 | 2.30 | 1906 | 2257 | 0.9 | 1140.9 | 43.6 | 104.7 | 14.7-24.7 |
| door -x+y (x wall) 2 | 2.30 | 1718 | 1710 | 0.7 | 1196.2 | 37.5 | 104.7 | 18.0-28.0 |
| door -x+y (x wall) 3 | 2.30 | 1341 | 1165 | 0.7 | 1190.9 | 29.4 | 107.3 | 30.3-40.2 |
| door -x+y (x wall) 4 | 2.30 | 820 | 640 | 0.7 | 1162.8 | 18.4 | 107.3 | 1.4-11.4 |
| door -x+y (corner) | 2.30 | 501 | 250 | 0.9 | 874.4 | 15.0 | 70.6 | 46.0-56.0 |
| door -x-y (y wall) 0 | 2.30 | 1720 | 2729 | 1.0 | 1007.6 | 44.6 | 112.5 | 0.9-10.8 |
| door -x-y (y wall) 1 | 2.30 | 1893 | 2250 | 0.7 | 1188.5 | 41.6 | 109.9 | 14.7-24.7 |
| door -x-y (y wall) 2 | 2.30 | 1682 | 1711 | 0.7 | 1174.8 | 37.4 | 107.3 | 0.5-10.5 |
| door -x-y (y wall) 3 | 2.30 | 1362 | 1156 | 0.9 | 1190.4 | 29.9 | 112.5 | 30.8-40.8 |
| door -x-y (y wall) 4 | 2.30 | 773 | 639 | 0.7 | 1163.0 | 17.3 | 107.3 | 12.2-22.2 |
| door -x-y (x wall) 0 | 2.30 | 1700 | 2721 | 0.9 | 1003.4 | 44.2 | 107.3 | 2.4-12.4 |
| door -x-y (x wall) 1 | 2.30 | 1895 | 2252 | 0.9 | 1137.8 | 43.5 | 117.7 | 1.0-11.0 |
| door -x-y (x wall) 2 | 2.30 | 1709 | 1711 | 0.7 | 1189.0 | 37.5 | 117.7 | 13.6-23.6 |
| door -x-y (x wall) 3 | 2.30 | 1386 | 1165 | 0.7 | 1194.6 | 30.3 | 115.1 | 1.0-11.0 |
| door -x-y (x wall) 4 | 2.30 | 741 | 640 | 0.9 | 1190.9 | 16.2 | 104.7 | 0.7-10.7 |
| door -x-y (corner) | 2.30 | 488 | 259 | 0.7 | 1037.4 | 12.3 | 70.6 | 36.6-46.5 |
| door +x-y (y wall) 0 | 2.30 | 1701 | 2724 | 0.9 | 1009.9 | 44.0 | 109.9 | 12.9-22.9 |
| door +x-y (y wall) 1 | 2.30 | 1883 | 2253 | 0.9 | 1091.9 | 45.0 | 112.5 | 16.8-26.8 |
| door +x-y (y wall) 2 | 2.30 | 1649 | 1714 | 0.9 | 1157.0 | 37.2 | 107.3 | 37.4-47.4 |
| door +x-y (y wall) 3 | 2.30 | 1191 | 1159 | 1.0 | 1150.2 | 27.0 | 109.9 | 0.5-10.5 |
| door +x-y (y wall) 4 | 2.30 | 973 | 640 | 0.9 | 1109.8 | 22.9 | 117.7 | 12.9-22.9 |
| door +x-y (x wall) 0 | 2.30 | 1699 | 2728 | 0.9 | 1006.8 | 44.1 | 102.0 | 4.5-14.5 |
| door +x-y (x wall) 1 | 2.30 | 1892 | 2258 | 0.9 | 1158.2 | 42.6 | 112.5 | 31.5-41.5 |
| door +x-y (x wall) 2 | 2.30 | 1637 | 1714 | 0.7 | 1144.4 | 37.3 | 109.9 | 5.4-15.4 |
| door +x-y (x wall) 3 | 2.30 | 1181 | 1157 | 0.7 | 1148.8 | 26.8 | 120.4 | 33.4-43.4 |
| door +x-y (x wall) 4 | 2.30 | 913 | 646 | 0.9 | 1158.8 | 20.6 | 115.1 | 2.8-12.8 |
| door +x-y (corner) | 2.30 | 669 | 264 | 0.9 | 993.1 | 17.6 | 75.9 | 0.7-10.7 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (2.30 m; a corner door's: the gap between its wall ends, 2.30 m); agents are removed past the outer wall's outer face (92.71 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 1940 | 2.8% | 20.3% |
| -x | avenue | 5.66 | 1944 | 2.8% | 20.4% |
| +y | avenue | 5.66 | 1936 | 2.8% | 20.3% |
| -y | avenue | 5.66 | 1960 | 2.8% | 20.6% |
| door +x+y (y wall) 0 | door | 2.30 | 1731 | 2.5% | 44.7% |
| door +x+y (y wall) 1 | door | 2.30 | 1965 | 2.8% | 50.7% |
| door +x+y (y wall) 2 | door | 2.30 | 1669 | 2.4% | 43.1% |
| door +x+y (y wall) 3 | door | 2.30 | 1224 | 1.8% | 31.6% |
| door +x+y (y wall) 4 | door | 2.30 | 819 | 1.2% | 21.1% |
| door +x+y (x wall) 0 | door | 2.30 | 1732 | 2.5% | 44.7% |
| door +x+y (x wall) 1 | door | 2.30 | 1935 | 2.8% | 49.9% |
| door +x+y (x wall) 2 | door | 2.30 | 1704 | 2.5% | 44.0% |
| door +x+y (x wall) 3 | door | 2.30 | 1205 | 1.7% | 31.1% |
| door +x+y (x wall) 4 | door | 2.30 | 853 | 1.2% | 22.0% |
| door +x+y (corner) | door | 2.30 | 561 | 0.8% | 14.5% |
| door -x+y (y wall) 0 | door | 2.30 | 1729 | 2.5% | 44.6% |
| door -x+y (y wall) 1 | door | 2.30 | 1892 | 2.7% | 48.8% |
| door -x+y (y wall) 2 | door | 2.30 | 1674 | 2.4% | 43.2% |
| door -x+y (y wall) 3 | door | 2.30 | 1339 | 1.9% | 34.6% |
| door -x+y (y wall) 4 | door | 2.30 | 776 | 1.1% | 20.0% |
| door -x+y (x wall) 0 | door | 2.30 | 1700 | 2.5% | 43.9% |
| door -x+y (x wall) 1 | door | 2.30 | 1906 | 2.7% | 49.2% |
| door -x+y (x wall) 2 | door | 2.30 | 1718 | 2.5% | 44.3% |
| door -x+y (x wall) 3 | door | 2.30 | 1341 | 1.9% | 34.6% |
| door -x+y (x wall) 4 | door | 2.30 | 820 | 1.2% | 21.2% |
| door -x+y (corner) | door | 2.30 | 501 | 0.7% | 12.9% |
| door -x-y (y wall) 0 | door | 2.30 | 1720 | 2.5% | 44.4% |
| door -x-y (y wall) 1 | door | 2.30 | 1893 | 2.7% | 48.9% |
| door -x-y (y wall) 2 | door | 2.30 | 1682 | 2.4% | 43.4% |
| door -x-y (y wall) 3 | door | 2.30 | 1362 | 2.0% | 35.1% |
| door -x-y (y wall) 4 | door | 2.30 | 773 | 1.1% | 19.9% |
| door -x-y (x wall) 0 | door | 2.30 | 1700 | 2.5% | 43.9% |
| door -x-y (x wall) 1 | door | 2.30 | 1895 | 2.7% | 48.9% |
| door -x-y (x wall) 2 | door | 2.30 | 1709 | 2.5% | 44.1% |
| door -x-y (x wall) 3 | door | 2.30 | 1386 | 2.0% | 35.8% |
| door -x-y (x wall) 4 | door | 2.30 | 741 | 1.1% | 19.1% |
| door -x-y (corner) | door | 2.30 | 488 | 0.7% | 12.6% |
| door +x-y (y wall) 0 | door | 2.30 | 1701 | 2.5% | 43.9% |
| door +x-y (y wall) 1 | door | 2.30 | 1883 | 2.7% | 48.6% |
| door +x-y (y wall) 2 | door | 2.30 | 1649 | 2.4% | 42.6% |
| door +x-y (y wall) 3 | door | 2.30 | 1191 | 1.7% | 30.7% |
| door +x-y (y wall) 4 | door | 2.30 | 973 | 1.4% | 25.1% |
| door +x-y (x wall) 0 | door | 2.30 | 1699 | 2.5% | 43.8% |
| door +x-y (x wall) 1 | door | 2.30 | 1892 | 2.7% | 48.8% |
| door +x-y (x wall) 2 | door | 2.30 | 1637 | 2.4% | 42.2% |
| door +x-y (x wall) 3 | door | 2.30 | 1181 | 1.7% | 30.5% |
| door +x-y (x wall) 4 | door | 2.30 | 913 | 1.3% | 23.6% |
| door +x-y (corner) | door | 2.30 | 669 | 1.0% | 17.3% |
| **doors (44)** | door | 101.20 | 61531 | 88.8% | |
| **avenues (4)** | avenue | 22.64 | 7780 | 11.2% | |

**Unused exit width: 0.0 of 123.8 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 1209.1 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 33.2%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 2324 | 3.4% | 2324 | 3.4% |
| straight +x+y (y wing) 1 | straight | yes | 1949 | 2.8% | 1865 | 2.7% |
| straight +x+y (y wing) 2 | straight | yes | 1617 | 2.3% | 1604 | 2.3% |
| straight +x+y (y wing) 3 | straight | yes | 1117 | 1.6% | 1103 | 1.6% |
| straight +x+y (y wing) 4 | straight | yes | 660 | 1.0% | 645 | 0.9% |
| straight +x+y (x wing) 0 | straight | yes | 2371 | 3.4% | 2371 | 3.4% |
| straight +x+y (x wing) 1 | straight | yes | 1909 | 2.8% | 1845 | 2.7% |
| straight +x+y (x wing) 2 | straight | yes | 1629 | 2.4% | 1622 | 2.3% |
| straight +x+y (x wing) 3 | straight | yes | 1110 | 1.6% | 1098 | 1.6% |
| straight +x+y (x wing) 4 | straight | yes | 685 | 1.0% | 676 | 1.0% |
| corner +x+y | corner | yes | 1963 | 2.8% | 713 | 1.0% |
| straight -x+y (y wing) 0 | straight | yes | 2362 | 3.4% | 2362 | 3.4% |
| straight -x+y (y wing) 1 | straight | yes | 1890 | 2.7% | 1804 | 2.6% |
| straight -x+y (y wing) 2 | straight | yes | 1587 | 2.3% | 1574 | 2.3% |
| straight -x+y (y wing) 3 | straight | yes | 1244 | 1.8% | 1242 | 1.8% |
| straight -x+y (y wing) 4 | straight | yes | 612 | 0.9% | 604 | 0.9% |
| straight -x+y (x wing) 0 | straight | yes | 2324 | 3.4% | 2324 | 3.4% |
| straight -x+y (x wing) 1 | straight | yes | 1867 | 2.7% | 1807 | 2.6% |
| straight -x+y (x wing) 2 | straight | yes | 1643 | 2.4% | 1626 | 2.3% |
| straight -x+y (x wing) 3 | straight | yes | 1212 | 1.7% | 1209 | 1.7% |
| straight -x+y (x wing) 4 | straight | yes | 695 | 1.0% | 681 | 1.0% |
| corner -x+y | corner | yes | 1952 | 2.8% | 633 | 0.9% |
| straight -x-y (y wing) 0 | straight | yes | 2343 | 3.4% | 2343 | 3.4% |
| straight -x-y (y wing) 1 | straight | yes | 1891 | 2.7% | 1809 | 2.6% |
| straight -x-y (y wing) 2 | straight | yes | 1605 | 2.3% | 1593 | 2.3% |
| straight -x-y (y wing) 3 | straight | yes | 1237 | 1.8% | 1235 | 1.8% |
| straight -x-y (y wing) 4 | straight | yes | 650 | 0.9% | 634 | 0.9% |
| straight -x-y (x wing) 0 | straight | yes | 2322 | 3.4% | 2322 | 3.4% |
| straight -x-y (x wing) 1 | straight | yes | 1881 | 2.7% | 1798 | 2.6% |
| straight -x-y (x wing) 2 | straight | yes | 1632 | 2.4% | 1610 | 2.3% |
| straight -x-y (x wing) 3 | straight | yes | 1263 | 1.8% | 1259 | 1.8% |
| straight -x-y (x wing) 4 | straight | yes | 614 | 0.9% | 603 | 0.9% |
| corner -x-y | corner | yes | 1984 | 2.9% | 660 | 1.0% |
| straight +x-y (y wing) 0 | straight | yes | 2352 | 3.4% | 2352 | 3.4% |
| straight +x-y (y wing) 1 | straight | yes | 1878 | 2.7% | 1780 | 2.6% |
| straight +x-y (y wing) 2 | straight | yes | 1579 | 2.3% | 1550 | 2.2% |
| straight +x-y (y wing) 3 | straight | yes | 1139 | 1.6% | 1118 | 1.6% |
| straight +x-y (y wing) 4 | straight | yes | 800 | 1.2% | 783 | 1.1% |
| straight +x-y (x wing) 0 | straight | yes | 2303 | 3.3% | 2303 | 3.3% |
| straight +x-y (x wing) 1 | straight | yes | 1878 | 2.7% | 1793 | 2.6% |
| straight +x-y (x wing) 2 | straight | yes | 1632 | 2.4% | 1592 | 2.3% |
| straight +x-y (x wing) 3 | straight | yes | 1106 | 1.6% | 1083 | 1.6% |
| straight +x-y (x wing) 4 | straight | yes | 704 | 1.0% | 691 | 1.0% |
| corner +x-y | corner | yes | 2095 | 3.0% | 822 | 1.2% |
| **straight (40)** | | | 61616 | | 60637 | 87.5% |
| **corner (4)** | | | 7994 | | 2828 | 4.1% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 5846, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 1940 | 60.2 | 930.7 | 0.28 | 0.74 | 0.0% |
| -x | 1944 | 60.2 | 931.0 | 0.28 | 0.72 | 0.0% |
| +y | 1936 | 60.2 | 924.2 | 0.28 | 0.66 | 0.0% |
| -y | 1960 | 60.2 | 923.0 | 0.29 | 0.71 | 0.0% |
| door +x+y (y wall) 0 | 1731 | 0.9 | 1068.2 | 0.51 | 1.28 | 4.6% |
| door +x+y (y wall) 1 | 1965 | 1.0 | 1185.3 | 0.52 | 1.35 | 5.0% |
| door +x+y (y wall) 2 | 1669 | 0.7 | 1207.9 | 0.43 | 1.25 | 4.1% |
| door +x+y (y wall) 3 | 1224 | 1.0 | 1209.1 | 0.32 | 1.31 | 4.1% |
| door +x+y (y wall) 4 | 819 | 0.9 | 1189.7 | 0.21 | 1.35 | 5.0% |
| door +x+y (x wall) 0 | 1732 | 0.7 | 1061.2 | 0.51 | 1.28 | 4.7% |
| door +x+y (x wall) 1 | 1935 | 0.9 | 1154.6 | 0.52 | 1.31 | 4.3% |
| door +x+y (x wall) 2 | 1704 | 0.7 | 1200.4 | 0.44 | 1.31 | 4.1% |
| door +x+y (x wall) 3 | 1205 | 0.9 | 1207.9 | 0.31 | 1.28 | 4.1% |
| door +x+y (x wall) 4 | 853 | 0.9 | 1162.3 | 0.23 | 1.35 | 5.1% |
| door +x+y (corner) | 561 | 0.9 | 1092.5 | 0.16 | 0.88 | 0.9% |
| door -x+y (y wall) 0 | 1729 | 0.9 | 1017.4 | 0.53 | 1.31 | 4.9% |
| door -x+y (y wall) 1 | 1892 | 0.7 | 1169.1 | 0.51 | 1.28 | 5.1% |
| door -x+y (y wall) 2 | 1674 | 1.0 | 1194.1 | 0.44 | 1.28 | 4.2% |
| door -x+y (y wall) 3 | 1339 | 1.0 | 1179.0 | 0.35 | 1.31 | 5.0% |
| door -x+y (y wall) 4 | 776 | 0.9 | 1181.8 | 0.21 | 1.38 | 5.0% |
| door -x+y (x wall) 0 | 1700 | 0.7 | 1007.3 | 0.53 | 1.35 | 4.9% |
| door -x+y (x wall) 1 | 1906 | 0.9 | 1140.9 | 0.52 | 1.25 | 5.2% |
| door -x+y (x wall) 2 | 1718 | 0.7 | 1196.2 | 0.45 | 1.25 | 4.2% |
| door -x+y (x wall) 3 | 1341 | 0.7 | 1190.9 | 0.35 | 1.28 | 5.0% |
| door -x+y (x wall) 4 | 820 | 0.7 | 1162.8 | 0.22 | 1.28 | 5.1% |
| door -x+y (corner) | 501 | 0.9 | 874.4 | 0.18 | 0.85 | 0.0% |
| door -x-y (y wall) 0 | 1720 | 1.0 | 1007.6 | 0.53 | 1.35 | 4.9% |
| door -x-y (y wall) 1 | 1893 | 0.7 | 1188.5 | 0.50 | 1.31 | 5.0% |
| door -x-y (y wall) 2 | 1682 | 0.7 | 1174.8 | 0.45 | 1.28 | 5.1% |
| door -x-y (y wall) 3 | 1362 | 0.9 | 1190.4 | 0.36 | 1.35 | 4.2% |
| door -x-y (y wall) 4 | 773 | 0.7 | 1163.0 | 0.21 | 1.28 | 5.1% |
| door -x-y (x wall) 0 | 1700 | 0.9 | 1003.4 | 0.53 | 1.28 | 5.0% |
| door -x-y (x wall) 1 | 1895 | 0.9 | 1137.8 | 0.52 | 1.41 | 4.3% |
| door -x-y (x wall) 2 | 1709 | 0.7 | 1189.0 | 0.45 | 1.41 | 4.2% |
| door -x-y (x wall) 3 | 1386 | 0.7 | 1194.6 | 0.36 | 1.38 | 5.0% |
| door -x-y (x wall) 4 | 741 | 0.9 | 1190.9 | 0.19 | 1.25 | 5.0% |
| door -x-y (corner) | 488 | 0.7 | 1037.4 | 0.15 | 0.85 | 1.0% |
| door +x-y (y wall) 0 | 1701 | 0.9 | 1009.9 | 0.53 | 1.31 | 5.9% |
| door +x-y (y wall) 1 | 1883 | 0.9 | 1091.9 | 0.54 | 1.35 | 4.5% |
| door +x-y (y wall) 2 | 1649 | 0.9 | 1157.0 | 0.45 | 1.28 | 5.1% |
| door +x-y (y wall) 3 | 1191 | 1.0 | 1150.2 | 0.32 | 1.31 | 5.2% |
| door +x-y (y wall) 4 | 973 | 0.9 | 1109.8 | 0.27 | 1.41 | 5.4% |
| door +x-y (x wall) 0 | 1699 | 0.9 | 1006.8 | 0.53 | 1.22 | 5.9% |
| door +x-y (x wall) 1 | 1892 | 0.9 | 1158.2 | 0.51 | 1.35 | 4.3% |
| door +x-y (x wall) 2 | 1637 | 0.7 | 1144.4 | 0.45 | 1.31 | 5.2% |
| door +x-y (x wall) 3 | 1181 | 0.7 | 1148.8 | 0.32 | 1.44 | 4.3% |
| door +x-y (x wall) 4 | 913 | 0.9 | 1158.8 | 0.25 | 1.38 | 5.1% |
| door +x-y (corner) | 669 | 0.9 | 993.1 | 0.21 | 0.91 | 2.0% |

Mean flow / w J averaged over the doors 0.39, over the avenues 0.28.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 103.1 | 2324 | 1597 / 727 / 773 | 0.7 | 883.3 | 3.51 | 5.52 | 90% | 90% | 0% | 4.69 |
| straight +x+y (y wing) 1 | 1.20 | 81.5 | 1929 | 1865 / 0 / 187 | 0.7 | 1182.4 | 1.74 | 3.61 | 92% | 76% | 15% | 3.95 |
| straight +x+y (y wing) 2 | 1.20 | 61.0 | 1480 | 1604 / 0 / 29 | 0.7 | 1204.9 | 1.36 | 2.21 | 75% | 62% | 13% | 3.70 |
| straight +x+y (y wing) 3 | 1.20 | 39.4 | 943 | 1103 / 0 / 34 | 0.7 | 1206.2 | 0.94 | 2.41 | 45% | 40% | 5% | 3.82 |
| straight +x+y (y wing) 4 | 1.20 | 18.8 | 406 | 645 / 0 / 20 | 0.7 | 1186.7 | 0.56 | 2.21 | 18% | 18% | 1% | 4.02 |
| straight +x+y (x wing) 0 | 1.20 | 103.1 | 2371 | 1588 / 784 / 1091 | 0.2 | 907.4 | 3.82 | 6.92 | 89% | 85% | 4% | 4.53 |
| straight +x+y (x wing) 1 | 1.20 | 81.5 | 1874 | 1845 / 0 / 110 | 0.7 | 1151.6 | 1.70 | 2.71 | 90% | 79% | 10% | 4.09 |
| straight +x+y (x wing) 2 | 1.20 | 61.0 | 1481 | 1622 / 0 / 20 | 0.7 | 1197.4 | 1.37 | 2.11 | 70% | 62% | 8% | 3.92 |
| straight +x+y (x wing) 3 | 1.20 | 39.4 | 941 | 1098 / 0 / 32 | 0.7 | 1204.9 | 0.94 | 2.21 | 48% | 40% | 8% | 3.71 |
| straight +x+y (x wing) 4 | 1.20 | 18.8 | 397 | 676 / 0 / 17 | 0.7 | 1159.3 | 0.60 | 2.21 | 18% | 17% | 1% | 4.06 |
| corner +x+y | 1.20 | 186.0 | 1720 | 440 / 273 / 1348 | 0.7 | 1162.8 | 1.77 | 4.11 | 92% | 74% | 19% | 2.75 |
| straight -x+y (y wing) 0 | 1.20 | 103.1 | 2362 | 1598 / 764 / 976 | 0.2 | 899.5 | 3.71 | 5.42 | 89% | 87% | 2% | 4.53 |
| straight -x+y (y wing) 1 | 1.20 | 81.5 | 1875 | 1804 / 0 / 150 | 0.7 | 1166.1 | 1.68 | 3.01 | 90% | 74% | 15% | 3.75 |
| straight -x+y (y wing) 2 | 1.20 | 61.0 | 1482 | 1574 / 0 / 15 | 0.7 | 1191.1 | 1.33 | 2.41 | 68% | 61% | 8% | 3.87 |
| straight -x+y (y wing) 3 | 1.20 | 39.4 | 953 | 1242 / 0 / 5 | 0.7 | 1176.1 | 1.06 | 2.11 | 46% | 42% | 4% | 3.88 |
| straight -x+y (y wing) 4 | 1.20 | 18.8 | 405 | 604 / 0 / 28 | 0.7 | 1178.9 | 0.54 | 2.01 | 18% | 17% | 1% | 4.03 |
| straight -x+y (x wing) 0 | 1.20 | 103.1 | 2324 | 1565 / 760 / 787 | 0.2 | 872.6 | 3.57 | 5.52 | 89% | 88% | 1% | 4.72 |
| straight -x+y (x wing) 1 | 1.20 | 81.5 | 1832 | 1807 / 0 / 123 | 0.7 | 1137.9 | 1.70 | 3.01 | 90% | 76% | 14% | 3.99 |
| straight -x+y (x wing) 2 | 1.20 | 61.0 | 1550 | 1626 / 0 / 85 | 0.7 | 1193.2 | 1.43 | 2.61 | 76% | 65% | 11% | 3.89 |
| straight -x+y (x wing) 3 | 1.20 | 39.4 | 948 | 1209 / 0 / 6 | 0.7 | 1188.0 | 1.02 | 2.01 | 45% | 39% | 6% | 3.87 |
| straight -x+y (x wing) 4 | 1.20 | 18.8 | 401 | 681 / 0 / 14 | 0.7 | 1159.8 | 0.60 | 2.21 | 17% | 17% | 0% | 4.30 |
| corner -x+y | 1.20 | 186.0 | 1734 | 375 / 258 / 1439 | 0.7 | 1154.9 | 1.79 | 4.81 | 92% | 68% | 24% | 2.81 |
| straight -x-y (y wing) 0 | 1.20 | 103.1 | 2343 | 1572 / 771 / 866 | 0.3 | 893.4 | 3.59 | 6.22 | 90% | 88% | 2% | 4.65 |
| straight -x-y (y wing) 1 | 1.20 | 81.5 | 1875 | 1809 / 0 / 176 | 0.7 | 1185.5 | 1.68 | 3.41 | 87% | 72% | 14% | 3.94 |
| straight -x-y (y wing) 2 | 1.20 | 61.0 | 1489 | 1593 / 0 / 19 | 0.7 | 1171.9 | 1.38 | 2.21 | 73% | 61% | 12% | 3.83 |
| straight -x-y (y wing) 3 | 1.20 | 39.4 | 961 | 1235 / 0 / 9 | 0.7 | 1187.4 | 1.05 | 2.11 | 50% | 40% | 10% | 3.58 |
| straight -x-y (y wing) 4 | 1.20 | 18.8 | 406 | 634 / 0 / 19 | 0.7 | 1160.0 | 0.56 | 2.21 | 17% | 17% | 0% | 4.32 |
| straight -x-y (x wing) 0 | 1.20 | 103.1 | 2322 | 1570 / 752 / 770 | 0.7 | 887.5 | 3.49 | 5.72 | 89% | 88% | 1% | 4.58 |
| straight -x-y (x wing) 1 | 1.20 | 81.5 | 1867 | 1798 / 0 / 190 | 0.7 | 1134.8 | 1.75 | 3.81 | 91% | 75% | 17% | 3.75 |
| straight -x-y (x wing) 2 | 1.20 | 61.0 | 1540 | 1610 / 0 / 28 | 0.7 | 1186.0 | 1.38 | 2.31 | 76% | 65% | 11% | 3.64 |
| straight -x-y (x wing) 3 | 1.20 | 39.4 | 954 | 1259 / 0 / 9 | 0.7 | 1191.6 | 1.06 | 2.21 | 43% | 40% | 3% | 3.91 |
| straight -x-y (x wing) 4 | 1.20 | 18.8 | 399 | 603 / 0 / 25 | 0.7 | 1188.0 | 0.53 | 2.11 | 33% | 17% | 17% | 2.42 |
| corner -x-y | 1.20 | 186.0 | 1710 | 353 / 307 / 1385 | 0.7 | 1164.0 | 1.76 | 5.12 | 91% | 68% | 23% | 2.89 |
| straight +x-y (y wing) 0 | 1.20 | 103.1 | 2352 | 1575 / 780 / 998 | 0.3 | 903.4 | 3.71 | 6.02 | 90% | 86% | 4% | 4.52 |
| straight +x-y (y wing) 1 | 1.20 | 81.5 | 1871 | 1780 / 0 / 180 | 0.7 | 1089.0 | 1.80 | 3.11 | 90% | 78% | 12% | 3.93 |
| straight +x-y (y wing) 2 | 1.20 | 61.0 | 1476 | 1550 / 0 / 36 | 0.7 | 1154.0 | 1.37 | 2.31 | 73% | 65% | 9% | 3.69 |
| straight +x-y (y wing) 3 | 1.20 | 39.4 | 965 | 1118 / 0 / 38 | 0.7 | 1147.2 | 1.01 | 2.61 | 49% | 43% | 6% | 3.70 |
| straight +x-y (y wing) 4 | 1.20 | 18.8 | 415 | 783 / 0 / 20 | 0.7 | 1106.8 | 0.73 | 2.31 | 20% | 18% | 2% | 3.93 |
| straight +x-y (x wing) 0 | 1.20 | 103.1 | 2303 | 1561 / 743 / 832 | 0.5 | 904.3 | 3.47 | 6.32 | 90% | 88% | 2% | 4.61 |
| straight +x-y (x wing) 1 | 1.20 | 81.5 | 1856 | 1793 / 0 / 192 | 0.7 | 1155.3 | 1.72 | 3.41 | 86% | 74% | 12% | 4.00 |
| straight +x-y (x wing) 2 | 1.20 | 61.0 | 1558 | 1592 / 0 / 45 | 0.7 | 1141.4 | 1.43 | 2.31 | 80% | 69% | 11% | 3.89 |
| straight +x-y (x wing) 3 | 1.20 | 39.4 | 934 | 1083 / 0 / 26 | 0.7 | 1145.8 | 0.97 | 2.01 | 50% | 41% | 9% | 3.64 |
| straight +x-y (x wing) 4 | 1.20 | 18.8 | 406 | 691 / 0 / 18 | 0.7 | 1155.8 | 0.61 | 2.11 | 18% | 17% | 1% | 4.04 |
| corner +x-y | 1.20 | 186.0 | 1731 | 529 / 294 / 1361 | 0.7 | 1131.8 | 1.93 | 5.02 | 89% | 62% | 27% | 2.76 |

The last agent out (agent 8751, t100 1209.1 s): last gangway straight +x+y (y wing) 3, exit door +x+y (y wall) 3. The gangway that cleared last: straight +x+y (y wing) 3 at 1206.2 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 8804 | 7800.4 | 6.90 | 1203.5 / 1124.3 / 1078.5 | 1120.1 / 1103.3 / 1052.2 | 5505457.2 | 11352002 | 0.198 |
| gangway | 3792 | 3512.9 | 6.90 | 1202.7 / 1124.1 / 1076.7 | 1120.1 / 1103.3 / 1052.2 | 5476033.3 | 10404380 | 0.127 |
| walkway | 276 | 257.4 | 5.38 | 646.1 / 416.5 / 133.1 | 473.6 / 365.6 / 66.3 | 1029.8 | 118599 | 0.457 |
| avenue | 1920 | 1801.4 | 3.05 | 826.4 / 39.0 / 0.0 | 612.9 / 1.9 / 0.0 | 0.0 | 466339 | 1.333 |
| exit | 4 | 2.0 | 0.00 | 0.7 / 0.0 / 0.0 | 0.7 / 0.0 / 0.0 | 0.0 | 3 | 0.906 |
| concourse | 2812 | 2226.8 | 6.10 | 1183.9 / 126.8 / 55.1 | 998.9 / 82.0 / 51.1 | 28394.1 | 362680 | 0.693 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 25392 | 16030.4 | 7.67 | 1094.4 / 1086.0 / 1051.4 | 1084.1 / 1071.1 / 1043.1 | 6890082.7 | 17334147 | 0.029 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 208 x 208 from (-104, -104) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 34.5 | 34.5 | gangway | 1.00 | 6.02 | 1093.7 | 1083.5 | 1041.2 | 6160.6 | 0.006 |
| 2 | -34.5 | 34.5 | gangway | 1.00 | 6.08 | 1087.6 | 1078.0 | 1035.3 | 5896.6 | 0.007 |
| 3 | -35.5 | 35.5 | gangway | 1.00 | 5.98 | 1091.2 | 1089.0 | 1019.4 | 5877.4 | 0.009 |
| 4 | 38.5 | 38.5 | gangway | 1.00 | 5.88 | 1110.8 | 1103.3 | 987.7 | 5655.3 | 0.016 |
| 5 | -35.5 | -35.5 | gangway | 1.00 | 5.59 | 1088.4 | 1080.7 | 1015.3 | 5504.4 | 0.010 |
| 6 | -38.5 | 38.5 | gangway | 1.00 | 5.88 | 1101.4 | 1098.1 | 945.7 | 5453.8 | 0.019 |
| 7 | -34.5 | -34.5 | gangway | 1.00 | 5.61 | 1080.0 | 1070.8 | 1033.7 | 5447.8 | 0.009 |
| 8 | -38.5 | -38.5 | gangway | 1.00 | 5.98 | 1095.4 | 1088.8 | 948.3 | 5317.0 | 0.021 |
| 9 | 35.5 | 35.5 | gangway | 1.00 | 5.90 | 1098.6 | 1096.7 | 1022.5 | 5291.3 | 0.007 |
| 10 | 33.5 | 33.5 | gangway | 0.99 | 5.69 | 1073.4 | 1051.0 | 954.8 | 5278.0 | 0.006 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -36.5 | -38.5 | seat row | 0.50 | 7.18 | 1056.1 | 1050.3 | 1028.1 | 3637.2 | 0.005 |
| 2 | -38.5 | 36.5 | seat row | 0.50 | 7.18 | 1060.1 | 1056.4 | 1041.6 | 3627.4 | 0.006 |
| 3 | 36.5 | 38.5 | seat row | 0.50 | 7.08 | 1062.0 | 1057.8 | 1041.4 | 3625.0 | 0.004 |
| 4 | 35.5 | 38.5 | seat row | 0.50 | 7.11 | 1046.5 | 1040.0 | 1021.5 | 3597.8 | 0.008 |
| 5 | -38.5 | -36.5 | seat row | 0.50 | 7.09 | 1053.8 | 1051.0 | 1035.3 | 3574.6 | 0.005 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 7632; agent-steps of seated agents on another row's clearway: 1406598.

## Deposit check

Person-seconds deposited: 28692415.7, of them in excluded cells: 6266.853.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 6011466 overlapping pair-steps: p99 0.0032, max 0.0935 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0032 max 0.0935; venue-geometry 8: p99 0.0013 max 0.0013 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00754 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 48 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.38 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 3765 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
