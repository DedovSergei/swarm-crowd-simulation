# Experiment `L_load150_s3`

**Task 5.8 stage 2: venue L, 150% requested (seed 3): every seat + standing on the walkway and concourse (M, L: the achievable maximum, also the 125% request)**

Venue L (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (4000 x 4000), cache key a2f3aaf59c2252b7, content hash 022d17b202313d70). 69311 agents (load 109.3%, requested 150%): every one of the 63424 seats and 5887 standing (spawnOvercrowdedCrowd, seed 3; below), buffer N = 131072, 7079 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 9646083 evaluations, 549650 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.09)** (the L venue's design capacity 63424, jam capacity 171923: 23822.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `cd8e0bbf3411846ca7aa6719887d122a142a7ca1`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-15T17:47:16, 660.0 s wall.

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
| t50 | 2187 | 382.5 |
| t90 | 4776 | 835.4 |
| t100 | 7079 | 1238.2 |

t_p: the step by which ceil(p x 69311) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 1962 | 88 | 60.2 | 926.0 | 24.0 | 62.7 | 60.0-70.0 |
| -x | 5.66 | 1957 | 86 | 60.2 | 923.3 | 24.0 | 59.5 | 59.6-69.6 |
| +y | 5.66 | 1967 | 90 | 60.2 | 935.2 | 23.8 | 60.6 | 59.8-69.8 |
| -y | 5.66 | 1954 | 85 | 60.2 | 925.8 | 23.9 | 58.5 | 59.6-69.6 |
| door +x+y (y wall) 0 | 2.30 | 1715 | 2734 | 0.9 | 1010.3 | 44.3 | 115.1 | 39.7-49.7 |
| door +x+y (y wall) 1 | 2.30 | 1916 | 2257 | 0.9 | 1159.3 | 43.1 | 107.3 | 18.0-28.0 |
| door +x+y (y wall) 2 | 2.30 | 1700 | 1712 | 0.7 | 1191.1 | 37.2 | 117.7 | 24.0-33.9 |
| door +x+y (y wall) 3 | 2.30 | 1211 | 1160 | 0.9 | 1185.9 | 26.7 | 109.9 | 9.8-19.8 |
| door +x+y (y wall) 4 | 2.30 | 859 | 641 | 0.9 | 1168.7 | 19.2 | 107.3 | 35.0-45.0 |
| door +x+y (x wall) 0 | 2.30 | 1742 | 2724 | 0.9 | 1042.1 | 43.6 | 112.5 | 7.3-17.3 |
| door +x+y (x wall) 1 | 2.30 | 1891 | 2246 | 0.7 | 1181.5 | 41.8 | 104.7 | 2.1-12.1 |
| door +x+y (x wall) 2 | 2.30 | 1705 | 1717 | 0.7 | 1189.4 | 37.4 | 107.3 | 19.4-29.4 |
| door +x+y (x wall) 3 | 2.30 | 1223 | 1162 | 0.9 | 1154.4 | 27.7 | 112.5 | 18.2-28.2 |
| door +x+y (x wall) 4 | 2.30 | 801 | 638 | 1.0 | 1154.2 | 18.1 | 115.1 | 23.1-33.1 |
| door +x+y (corner) | 2.30 | 607 | 248 | 0.9 | 1007.8 | 15.7 | 73.3 | 75.2-85.2 |
| door -x+y (y wall) 0 | 2.30 | 1700 | 2731 | 0.7 | 1001.2 | 44.3 | 109.9 | 1.4-11.4 |
| door -x+y (y wall) 1 | 2.30 | 1890 | 2259 | 0.9 | 1156.0 | 42.7 | 117.7 | 7.5-17.5 |
| door -x+y (y wall) 2 | 2.30 | 1730 | 1718 | 0.9 | 1161.0 | 38.9 | 112.5 | 27.6-37.6 |
| door -x+y (y wall) 3 | 2.30 | 1371 | 1162 | 0.7 | 1151.1 | 31.1 | 107.3 | 22.7-32.7 |
| door -x+y (y wall) 4 | 2.30 | 758 | 638 | 0.9 | 1160.0 | 17.1 | 107.3 | 24.3-34.3 |
| door -x+y (x wall) 0 | 2.30 | 1710 | 2725 | 0.9 | 1015.7 | 44.0 | 109.9 | 14.2-24.1 |
| door -x+y (x wall) 1 | 2.30 | 1889 | 2261 | 0.7 | 1130.9 | 43.6 | 112.5 | 1.4-11.4 |
| door -x+y (x wall) 2 | 2.30 | 1766 | 1706 | 0.9 | 1152.3 | 40.0 | 109.9 | 1.4-11.4 |
| door -x+y (x wall) 3 | 2.30 | 1358 | 1167 | 0.7 | 1164.7 | 30.4 | 115.1 | 37.1-47.0 |
| door -x+y (x wall) 4 | 2.30 | 709 | 642 | 0.9 | 1114.3 | 16.6 | 107.3 | 15.7-25.7 |
| door -x+y (corner) | 2.30 | 482 | 242 | 0.9 | 928.2 | 13.6 | 73.3 | 73.3-83.3 |
| door -x-y (y wall) 0 | 2.30 | 1703 | 2729 | 0.7 | 1007.1 | 44.1 | 115.1 | 26.1-36.0 |
| door -x-y (y wall) 1 | 2.30 | 1906 | 2254 | 0.9 | 1209.1 | 41.1 | 109.9 | 3.1-13.1 |
| door -x-y (y wall) 2 | 2.30 | 1712 | 1710 | 0.9 | 1212.8 | 36.8 | 104.7 | 22.6-32.5 |
| door -x-y (y wall) 3 | 2.30 | 1353 | 1163 | 0.9 | 1216.5 | 29.0 | 109.9 | 18.2-28.2 |
| door -x-y (y wall) 4 | 2.30 | 768 | 645 | 1.0 | 1160.9 | 17.3 | 107.3 | 0.9-10.8 |
| door -x-y (x wall) 0 | 2.30 | 1714 | 2720 | 0.7 | 1022.0 | 43.8 | 115.1 | 18.7-28.7 |
| door -x-y (x wall) 1 | 2.30 | 1919 | 2259 | 0.7 | 1137.8 | 44.0 | 109.9 | 1.2-11.2 |
| door -x-y (x wall) 2 | 2.30 | 1633 | 1704 | 0.9 | 1210.5 | 35.2 | 109.9 | 10.5-20.5 |
| door -x-y (x wall) 3 | 2.30 | 1323 | 1160 | 0.7 | 1217.5 | 28.4 | 115.1 | 16.8-26.8 |
| door -x-y (x wall) 4 | 2.30 | 832 | 643 | 0.9 | 1216.1 | 17.9 | 112.5 | 1.6-11.5 |
| door -x-y (corner) | 2.30 | 508 | 245 | 1.0 | 995.7 | 13.3 | 70.6 | 0.9-10.8 |
| door +x-y (y wall) 0 | 2.30 | 1730 | 2725 | 0.9 | 1027.1 | 44.0 | 112.5 | 19.4-29.4 |
| door +x-y (y wall) 1 | 2.30 | 1909 | 2259 | 1.0 | 1238.2 | 40.2 | 104.7 | 1.9-11.9 |
| door +x-y (y wall) 2 | 2.30 | 1667 | 1708 | 0.7 | 1224.9 | 35.5 | 112.5 | 0.9-10.8 |
| door +x-y (y wall) 3 | 2.30 | 1295 | 1165 | 0.9 | 1231.0 | 27.5 | 109.9 | 40.9-50.9 |
| door +x-y (y wall) 4 | 2.30 | 901 | 639 | 0.9 | 1214.2 | 19.4 | 109.9 | 26.9-36.9 |
| door +x-y (x wall) 0 | 2.30 | 1702 | 2726 | 0.7 | 1017.8 | 43.6 | 112.5 | 15.6-25.5 |
| door +x-y (x wall) 1 | 2.30 | 1909 | 2257 | 0.9 | 1188.8 | 41.9 | 112.5 | 33.6-43.6 |
| door +x-y (x wall) 2 | 2.30 | 1669 | 1719 | 0.9 | 1233.3 | 35.3 | 109.9 | 4.5-14.5 |
| door +x-y (x wall) 3 | 2.30 | 1263 | 1159 | 0.9 | 1223.3 | 26.9 | 117.7 | 5.2-15.2 |
| door +x-y (x wall) 4 | 2.30 | 834 | 638 | 0.9 | 1200.7 | 18.1 | 117.7 | 23.1-33.1 |
| door +x-y (corner) | 2.30 | 488 | 245 | 0.9 | 940.3 | 13.5 | 73.3 | 0.5-10.5 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (2.30 m; a corner door's: the gap between its wall ends, 2.30 m); agents are removed past the outer wall's outer face (92.71 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 1962 | 2.8% | 20.1% |
| -x | avenue | 5.66 | 1957 | 2.8% | 20.0% |
| +y | avenue | 5.66 | 1967 | 2.8% | 20.1% |
| -y | avenue | 5.66 | 1954 | 2.8% | 20.0% |
| door +x+y (y wall) 0 | door | 2.30 | 1715 | 2.5% | 43.2% |
| door +x+y (y wall) 1 | door | 2.30 | 1916 | 2.8% | 48.3% |
| door +x+y (y wall) 2 | door | 2.30 | 1700 | 2.5% | 42.8% |
| door +x+y (y wall) 3 | door | 2.30 | 1211 | 1.7% | 30.5% |
| door +x+y (y wall) 4 | door | 2.30 | 859 | 1.2% | 21.6% |
| door +x+y (x wall) 0 | door | 2.30 | 1742 | 2.5% | 43.9% |
| door +x+y (x wall) 1 | door | 2.30 | 1891 | 2.7% | 47.7% |
| door +x+y (x wall) 2 | door | 2.30 | 1705 | 2.5% | 43.0% |
| door +x+y (x wall) 3 | door | 2.30 | 1223 | 1.8% | 30.8% |
| door +x+y (x wall) 4 | door | 2.30 | 801 | 1.2% | 20.2% |
| door +x+y (corner) | door | 2.30 | 607 | 0.9% | 15.3% |
| door -x+y (y wall) 0 | door | 2.30 | 1700 | 2.5% | 42.8% |
| door -x+y (y wall) 1 | door | 2.30 | 1890 | 2.7% | 47.6% |
| door -x+y (y wall) 2 | door | 2.30 | 1730 | 2.5% | 43.6% |
| door -x+y (y wall) 3 | door | 2.30 | 1371 | 2.0% | 34.6% |
| door -x+y (y wall) 4 | door | 2.30 | 758 | 1.1% | 19.1% |
| door -x+y (x wall) 0 | door | 2.30 | 1710 | 2.5% | 43.1% |
| door -x+y (x wall) 1 | door | 2.30 | 1889 | 2.7% | 47.6% |
| door -x+y (x wall) 2 | door | 2.30 | 1766 | 2.5% | 44.5% |
| door -x+y (x wall) 3 | door | 2.30 | 1358 | 2.0% | 34.2% |
| door -x+y (x wall) 4 | door | 2.30 | 709 | 1.0% | 17.9% |
| door -x+y (corner) | door | 2.30 | 482 | 0.7% | 12.1% |
| door -x-y (y wall) 0 | door | 2.30 | 1703 | 2.5% | 42.9% |
| door -x-y (y wall) 1 | door | 2.30 | 1906 | 2.7% | 48.0% |
| door -x-y (y wall) 2 | door | 2.30 | 1712 | 2.5% | 43.1% |
| door -x-y (y wall) 3 | door | 2.30 | 1353 | 2.0% | 34.1% |
| door -x-y (y wall) 4 | door | 2.30 | 768 | 1.1% | 19.4% |
| door -x-y (x wall) 0 | door | 2.30 | 1714 | 2.5% | 43.2% |
| door -x-y (x wall) 1 | door | 2.30 | 1919 | 2.8% | 48.4% |
| door -x-y (x wall) 2 | door | 2.30 | 1633 | 2.4% | 41.2% |
| door -x-y (x wall) 3 | door | 2.30 | 1323 | 1.9% | 33.3% |
| door -x-y (x wall) 4 | door | 2.30 | 832 | 1.2% | 21.0% |
| door -x-y (corner) | door | 2.30 | 508 | 0.7% | 12.8% |
| door +x-y (y wall) 0 | door | 2.30 | 1730 | 2.5% | 43.6% |
| door +x-y (y wall) 1 | door | 2.30 | 1909 | 2.8% | 48.1% |
| door +x-y (y wall) 2 | door | 2.30 | 1667 | 2.4% | 42.0% |
| door +x-y (y wall) 3 | door | 2.30 | 1295 | 1.9% | 32.6% |
| door +x-y (y wall) 4 | door | 2.30 | 901 | 1.3% | 22.7% |
| door +x-y (x wall) 0 | door | 2.30 | 1702 | 2.5% | 42.9% |
| door +x-y (x wall) 1 | door | 2.30 | 1909 | 2.8% | 48.1% |
| door +x-y (x wall) 2 | door | 2.30 | 1669 | 2.4% | 42.1% |
| door +x-y (x wall) 3 | door | 2.30 | 1263 | 1.8% | 31.8% |
| door +x-y (x wall) 4 | door | 2.30 | 834 | 1.2% | 21.0% |
| door +x-y (corner) | door | 2.30 | 488 | 0.7% | 12.3% |
| **doors (44)** | door | 101.20 | 61471 | 88.7% | |
| **avenues (4)** | avenue | 22.64 | 7840 | 11.3% | |

**Unused exit width: 0.0 of 123.8 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 1238.2 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 32.4%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 2324 | 3.4% | 2324 | 3.4% |
| straight +x+y (y wing) 1 | straight | yes | 1898 | 2.7% | 1815 | 2.6% |
| straight +x+y (y wing) 2 | straight | yes | 1643 | 2.4% | 1625 | 2.3% |
| straight +x+y (y wing) 3 | straight | yes | 1113 | 1.6% | 1094 | 1.6% |
| straight +x+y (y wing) 4 | straight | yes | 702 | 1.0% | 690 | 1.0% |
| straight +x+y (x wing) 0 | straight | yes | 2350 | 3.4% | 2350 | 3.4% |
| straight +x+y (x wing) 1 | straight | yes | 1916 | 2.8% | 1811 | 2.6% |
| straight +x+y (x wing) 2 | straight | yes | 1638 | 2.4% | 1630 | 2.4% |
| straight +x+y (x wing) 3 | straight | yes | 1118 | 1.6% | 1108 | 1.6% |
| straight +x+y (x wing) 4 | straight | yes | 633 | 0.9% | 626 | 0.9% |
| corner +x+y | corner | yes | 2009 | 2.9% | 793 | 1.1% |
| straight -x+y (y wing) 0 | straight | yes | 2374 | 3.4% | 2374 | 3.4% |
| straight -x+y (y wing) 1 | straight | yes | 1866 | 2.7% | 1775 | 2.6% |
| straight -x+y (y wing) 2 | straight | yes | 1621 | 2.3% | 1609 | 2.3% |
| straight -x+y (y wing) 3 | straight | yes | 1292 | 1.9% | 1290 | 1.9% |
| straight -x+y (y wing) 4 | straight | yes | 613 | 0.9% | 594 | 0.9% |
| straight -x+y (x wing) 0 | straight | yes | 2310 | 3.3% | 2310 | 3.3% |
| straight -x+y (x wing) 1 | straight | yes | 1866 | 2.7% | 1787 | 2.6% |
| straight -x+y (x wing) 2 | straight | yes | 1679 | 2.4% | 1669 | 2.4% |
| straight -x+y (x wing) 3 | straight | yes | 1254 | 1.8% | 1252 | 1.8% |
| straight -x+y (x wing) 4 | straight | yes | 557 | 0.8% | 549 | 0.8% |
| corner -x+y | corner | yes | 2021 | 2.9% | 658 | 0.9% |
| straight -x-y (y wing) 0 | straight | yes | 2312 | 3.3% | 2312 | 3.3% |
| straight -x-y (y wing) 1 | straight | yes | 1891 | 2.7% | 1807 | 2.6% |
| straight -x-y (y wing) 2 | straight | yes | 1649 | 2.4% | 1623 | 2.3% |
| straight -x-y (y wing) 3 | straight | yes | 1223 | 1.8% | 1220 | 1.8% |
| straight -x-y (y wing) 4 | straight | yes | 643 | 0.9% | 624 | 0.9% |
| straight -x-y (x wing) 0 | straight | yes | 2357 | 3.4% | 2357 | 3.4% |
| straight -x-y (x wing) 1 | straight | yes | 1909 | 2.8% | 1812 | 2.6% |
| straight -x-y (x wing) 2 | straight | yes | 1560 | 2.3% | 1537 | 2.2% |
| straight -x-y (x wing) 3 | straight | yes | 1223 | 1.8% | 1220 | 1.8% |
| straight -x-y (x wing) 4 | straight | yes | 696 | 1.0% | 676 | 1.0% |
| corner -x-y | corner | yes | 2010 | 2.9% | 678 | 1.0% |
| straight +x-y (y wing) 0 | straight | yes | 2348 | 3.4% | 2348 | 3.4% |
| straight +x-y (y wing) 1 | straight | yes | 1893 | 2.7% | 1820 | 2.6% |
| straight +x-y (y wing) 2 | straight | yes | 1602 | 2.3% | 1584 | 2.3% |
| straight +x-y (y wing) 3 | straight | yes | 1176 | 1.7% | 1162 | 1.7% |
| straight +x-y (y wing) 4 | straight | yes | 765 | 1.1% | 754 | 1.1% |
| straight +x-y (x wing) 0 | straight | yes | 2346 | 3.4% | 2346 | 3.4% |
| straight +x-y (x wing) 1 | straight | yes | 1888 | 2.7% | 1810 | 2.6% |
| straight +x-y (x wing) 2 | straight | yes | 1590 | 2.3% | 1562 | 2.3% |
| straight +x-y (x wing) 3 | straight | yes | 1155 | 1.7% | 1147 | 1.7% |
| straight +x-y (x wing) 4 | straight | yes | 699 | 1.0% | 692 | 1.0% |
| corner +x-y | corner | yes | 2030 | 2.9% | 643 | 0.9% |
| **straight (40)** | | | 61692 | | 60695 | 87.6% |
| **corner (4)** | | | 8070 | | 2772 | 4.0% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 5844, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 1962 | 60.2 | 926.0 | 0.29 | 0.75 | 0.0% |
| -x | 1957 | 60.2 | 923.3 | 0.29 | 0.71 | 0.0% |
| +y | 1967 | 60.2 | 935.2 | 0.28 | 0.72 | 0.0% |
| -y | 1954 | 60.2 | 925.8 | 0.29 | 0.70 | 0.0% |
| door +x+y (y wall) 0 | 1715 | 0.9 | 1010.3 | 0.53 | 1.38 | 4.9% |
| door +x+y (y wall) 1 | 1916 | 0.9 | 1159.3 | 0.52 | 1.28 | 5.1% |
| door +x+y (y wall) 2 | 1700 | 0.7 | 1191.1 | 0.45 | 1.41 | 4.2% |
| door +x+y (y wall) 3 | 1211 | 0.9 | 1185.9 | 0.32 | 1.31 | 5.0% |
| door +x+y (y wall) 4 | 859 | 0.9 | 1168.7 | 0.23 | 1.28 | 5.9% |
| door +x+y (x wall) 0 | 1742 | 0.9 | 1042.1 | 0.52 | 1.35 | 4.8% |
| door +x+y (x wall) 1 | 1891 | 0.7 | 1181.5 | 0.50 | 1.25 | 4.2% |
| door +x+y (x wall) 2 | 1705 | 0.7 | 1189.4 | 0.45 | 1.28 | 5.0% |
| door +x+y (x wall) 3 | 1223 | 0.9 | 1154.4 | 0.33 | 1.35 | 4.3% |
| door +x+y (x wall) 4 | 801 | 1.0 | 1154.2 | 0.22 | 1.38 | 5.2% |
| door +x+y (corner) | 607 | 0.9 | 1007.8 | 0.19 | 0.88 | 0.0% |
| door -x+y (y wall) 0 | 1700 | 0.7 | 1001.2 | 0.53 | 1.31 | 5.0% |
| door -x+y (y wall) 1 | 1890 | 0.9 | 1156.0 | 0.51 | 1.41 | 4.3% |
| door -x+y (y wall) 2 | 1730 | 0.9 | 1161.0 | 0.47 | 1.35 | 5.1% |
| door -x+y (y wall) 3 | 1371 | 0.7 | 1151.1 | 0.37 | 1.28 | 5.2% |
| door -x+y (y wall) 4 | 758 | 0.9 | 1160.0 | 0.20 | 1.28 | 5.1% |
| door -x+y (x wall) 0 | 1710 | 0.9 | 1015.7 | 0.53 | 1.31 | 4.9% |
| door -x+y (x wall) 1 | 1889 | 0.7 | 1130.9 | 0.52 | 1.35 | 5.3% |
| door -x+y (x wall) 2 | 1766 | 0.9 | 1152.3 | 0.48 | 1.31 | 4.3% |
| door -x+y (x wall) 3 | 1358 | 0.7 | 1164.7 | 0.36 | 1.38 | 5.1% |
| door -x+y (x wall) 4 | 709 | 0.9 | 1114.3 | 0.20 | 1.28 | 5.4% |
| door -x+y (corner) | 482 | 0.9 | 928.2 | 0.16 | 0.88 | 2.1% |
| door -x-y (y wall) 0 | 1703 | 0.7 | 1007.1 | 0.53 | 1.38 | 4.9% |
| door -x-y (y wall) 1 | 1906 | 0.9 | 1209.1 | 0.49 | 1.31 | 4.1% |
| door -x-y (y wall) 2 | 1712 | 0.9 | 1212.8 | 0.44 | 1.25 | 4.1% |
| door -x-y (y wall) 3 | 1353 | 0.9 | 1216.5 | 0.35 | 1.31 | 4.1% |
| door -x-y (y wall) 4 | 768 | 1.0 | 1160.9 | 0.21 | 1.28 | 6.0% |
| door -x-y (x wall) 0 | 1714 | 0.7 | 1022.0 | 0.52 | 1.38 | 5.8% |
| door -x-y (x wall) 1 | 1919 | 0.7 | 1137.8 | 0.53 | 1.31 | 4.3% |
| door -x-y (x wall) 2 | 1633 | 0.9 | 1210.5 | 0.42 | 1.31 | 4.1% |
| door -x-y (x wall) 3 | 1323 | 0.7 | 1217.5 | 0.34 | 1.38 | 4.1% |
| door -x-y (x wall) 4 | 832 | 0.9 | 1216.1 | 0.21 | 1.35 | 4.9% |
| door -x-y (corner) | 508 | 1.0 | 995.7 | 0.16 | 0.85 | 1.0% |
| door +x-y (y wall) 0 | 1730 | 0.9 | 1027.1 | 0.53 | 1.35 | 4.8% |
| door +x-y (y wall) 1 | 1909 | 1.0 | 1238.2 | 0.48 | 1.25 | 4.8% |
| door +x-y (y wall) 2 | 1667 | 0.7 | 1224.9 | 0.42 | 1.35 | 4.1% |
| door +x-y (y wall) 3 | 1295 | 0.9 | 1231.0 | 0.33 | 1.31 | 4.0% |
| door +x-y (y wall) 4 | 901 | 0.9 | 1214.2 | 0.23 | 1.31 | 4.9% |
| door +x-y (x wall) 0 | 1702 | 0.7 | 1017.8 | 0.52 | 1.35 | 4.9% |
| door +x-y (x wall) 1 | 1909 | 0.9 | 1188.8 | 0.50 | 1.35 | 4.2% |
| door +x-y (x wall) 2 | 1669 | 0.9 | 1233.3 | 0.42 | 1.31 | 4.8% |
| door +x-y (x wall) 3 | 1263 | 0.9 | 1223.3 | 0.32 | 1.41 | 4.1% |
| door +x-y (x wall) 4 | 834 | 0.9 | 1200.7 | 0.22 | 1.41 | 5.0% |
| door +x-y (corner) | 488 | 0.9 | 940.3 | 0.16 | 0.88 | 2.1% |

Mean flow / w J averaged over the doors 0.38, over the avenues 0.29.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 103.1 | 2324 | 1578 / 747 / 874 | 0.3 | 911.8 | 3.51 | 6.22 | 90% | 85% | 5% | 4.56 |
| straight +x+y (y wing) 1 | 1.20 | 81.5 | 1853 | 1815 / 0 / 190 | 0.7 | 1156.3 | 1.73 | 3.11 | 91% | 73% | 17% | 3.90 |
| straight +x+y (y wing) 2 | 1.20 | 61.0 | 1560 | 1625 / 0 / 34 | 0.7 | 1188.1 | 1.40 | 2.51 | 76% | 65% | 11% | 3.99 |
| straight +x+y (y wing) 3 | 1.20 | 39.4 | 936 | 1094 / 0 / 24 | 0.7 | 1182.9 | 0.95 | 2.11 | 48% | 39% | 9% | 3.57 |
| straight +x+y (y wing) 4 | 1.20 | 18.8 | 399 | 690 / 0 / 13 | 0.7 | 1165.8 | 0.60 | 2.21 | 18% | 17% | 1% | 4.15 |
| straight +x+y (x wing) 0 | 1.20 | 103.1 | 2350 | 1601 / 751 / 909 | 0.3 | 923.7 | 3.53 | 5.72 | 90% | 86% | 4% | 4.50 |
| straight +x+y (x wing) 1 | 1.20 | 81.5 | 1902 | 1811 / 0 / 190 | 0.7 | 1178.5 | 1.70 | 3.21 | 89% | 73% | 16% | 3.88 |
| straight +x+y (x wing) 2 | 1.20 | 61.0 | 1470 | 1630 / 0 / 13 | 0.7 | 1186.4 | 1.39 | 2.11 | 68% | 62% | 6% | 4.08 |
| straight +x+y (x wing) 3 | 1.20 | 39.4 | 952 | 1108 / 0 / 84 | 0.7 | 1151.4 | 1.04 | 2.21 | 53% | 41% | 13% | 3.47 |
| straight +x+y (x wing) 4 | 1.20 | 18.8 | 402 | 626 / 0 / 27 | 0.7 | 1151.2 | 0.57 | 2.21 | 18% | 16% | 2% | 4.05 |
| corner +x+y | 1.20 | 186.0 | 1718 | 483 / 310 / 1360 | 0.7 | 1141.8 | 1.89 | 4.81 | 92% | 70% | 23% | 2.75 |
| straight -x+y (y wing) 0 | 1.20 | 103.1 | 2374 | 1573 / 802 / 1069 | 0.2 | 909.2 | 3.79 | 6.62 | 89% | 87% | 2% | 4.50 |
| straight -x+y (y wing) 1 | 1.20 | 81.5 | 1859 | 1775 / 0 / 169 | 0.7 | 1153.0 | 1.69 | 3.31 | 88% | 74% | 14% | 3.87 |
| straight -x+y (y wing) 2 | 1.20 | 61.0 | 1466 | 1609 / 0 / 18 | 0.7 | 1158.2 | 1.41 | 2.01 | 67% | 61% | 6% | 3.97 |
| straight -x+y (y wing) 3 | 1.20 | 39.4 | 955 | 1290 / 0 / 12 | 0.7 | 1148.1 | 1.13 | 2.01 | 66% | 42% | 24% | 3.02 |
| straight -x+y (y wing) 4 | 1.20 | 18.8 | 405 | 594 / 0 / 28 | 0.7 | 1157.0 | 0.54 | 2.21 | 19% | 18% | 1% | 3.93 |
| straight -x+y (x wing) 0 | 1.20 | 103.1 | 2310 | 1576 / 734 / 809 | 0.2 | 897.6 | 3.47 | 5.92 | 89% | 87% | 2% | 4.64 |
| straight -x+y (x wing) 1 | 1.20 | 81.5 | 1845 | 1787 / 0 / 174 | 0.7 | 1128.0 | 1.74 | 3.61 | 91% | 74% | 18% | 3.90 |
| straight -x+y (x wing) 2 | 1.20 | 61.0 | 1556 | 1669 / 0 / 19 | 0.7 | 1149.3 | 1.47 | 2.21 | 73% | 66% | 8% | 4.10 |
| straight -x+y (x wing) 3 | 1.20 | 39.4 | 939 | 1252 / 0 / 6 | 0.7 | 1161.7 | 1.08 | 2.01 | 62% | 39% | 22% | 3.12 |
| straight -x+y (x wing) 4 | 1.20 | 18.8 | 401 | 549 / 0 / 47 | 0.7 | 1111.4 | 0.54 | 2.11 | 20% | 18% | 2% | 3.98 |
| corner -x+y | 1.20 | 186.0 | 1757 | 364 / 294 / 1470 | 0.7 | 1133.0 | 1.88 | 5.12 | 92% | 73% | 19% | 3.01 |
| straight -x-y (y wing) 0 | 1.20 | 103.1 | 2312 | 1569 / 744 / 696 | 0.7 | 892.7 | 3.37 | 5.82 | 90% | 87% | 3% | 4.71 |
| straight -x-y (y wing) 1 | 1.20 | 81.5 | 1852 | 1807 / 0 / 197 | 0.7 | 1206.2 | 1.66 | 3.01 | 88% | 72% | 16% | 3.88 |
| straight -x-y (y wing) 2 | 1.20 | 61.0 | 1553 | 1623 / 0 / 48 | 0.7 | 1209.8 | 1.38 | 2.71 | 74% | 63% | 11% | 3.94 |
| straight -x-y (y wing) 3 | 1.20 | 39.4 | 949 | 1220 / 0 / 9 | 0.7 | 1213.5 | 1.01 | 2.01 | 45% | 39% | 6% | 3.79 |
| straight -x-y (y wing) 4 | 1.20 | 18.8 | 399 | 624 / 0 / 33 | 0.7 | 1157.9 | 0.57 | 2.51 | 18% | 17% | 1% | 4.10 |
| straight -x-y (x wing) 0 | 1.20 | 103.1 | 2357 | 1587 / 772 / 968 | 0.3 | 910.6 | 3.65 | 6.22 | 90% | 86% | 4% | 4.44 |
| straight -x-y (x wing) 1 | 1.20 | 81.5 | 1897 | 1812 / 0 / 183 | 0.7 | 1134.8 | 1.76 | 3.41 | 91% | 77% | 14% | 3.79 |
| straight -x-y (x wing) 2 | 1.20 | 61.0 | 1461 | 1537 / 0 / 25 | 0.7 | 1207.6 | 1.29 | 2.11 | 73% | 59% | 14% | 3.47 |
| straight -x-y (x wing) 3 | 1.20 | 39.4 | 960 | 1220 / 0 / 6 | 0.7 | 1214.6 | 1.01 | 2.01 | 46% | 39% | 7% | 3.74 |
| straight -x-y (x wing) 4 | 1.20 | 18.8 | 413 | 676 / 0 / 25 | 0.7 | 1213.2 | 0.58 | 2.11 | 18% | 17% | 1% | 4.15 |
| corner -x-y | 1.20 | 186.0 | 1713 | 387 / 291 / 1415 | 0.7 | 1189.2 | 1.76 | 4.11 | 90% | 62% | 28% | 2.81 |
| straight +x-y (y wing) 0 | 1.20 | 103.1 | 2348 | 1583 / 765 / 912 | 0.5 | 931.4 | 3.50 | 5.72 | 89% | 85% | 4% | 4.43 |
| straight +x-y (y wing) 1 | 1.20 | 81.5 | 1880 | 1820 / 0 / 164 | 0.7 | 1235.2 | 1.61 | 3.31 | 85% | 73% | 11% | 3.86 |
| straight +x-y (y wing) 2 | 1.20 | 61.0 | 1485 | 1584 / 0 / 31 | 0.7 | 1221.9 | 1.32 | 2.41 | 71% | 59% | 12% | 3.61 |
| straight +x-y (y wing) 3 | 1.20 | 39.4 | 943 | 1162 / 0 / 26 | 0.7 | 1228.0 | 0.97 | 2.21 | 41% | 37% | 4% | 3.99 |
| straight +x-y (y wing) 4 | 1.20 | 18.8 | 414 | 754 / 0 / 15 | 0.7 | 1211.2 | 0.64 | 2.11 | 18% | 17% | 1% | 3.97 |
| straight +x-y (x wing) 0 | 1.20 | 103.1 | 2346 | 1568 / 778 / 844 | 0.2 | 929.3 | 3.43 | 6.12 | 89% | 84% | 5% | 4.47 |
| straight +x-y (x wing) 1 | 1.20 | 81.5 | 1874 | 1810 / 0 / 149 | 0.7 | 1185.9 | 1.65 | 3.71 | 92% | 76% | 15% | 3.82 |
| straight +x-y (x wing) 2 | 1.20 | 61.0 | 1488 | 1562 / 0 / 35 | 0.7 | 1230.3 | 1.30 | 2.41 | 73% | 60% | 13% | 3.66 |
| straight +x-y (x wing) 3 | 1.20 | 39.4 | 935 | 1147 / 0 / 15 | 0.7 | 1220.3 | 0.95 | 2.01 | 46% | 36% | 11% | 3.55 |
| straight +x-y (x wing) 4 | 1.20 | 18.8 | 401 | 692 / 0 / 20 | 0.7 | 1197.8 | 0.59 | 2.21 | 21% | 16% | 5% | 3.31 |
| corner +x-y | 1.20 | 186.0 | 1754 | 367 / 276 / 1463 | 0.7 | 1187.3 | 1.77 | 4.41 | 92% | 60% | 32% | 2.66 |

The last agent out (agent 48438, t100 1238.2 s): last gangway straight +x-y (y wing) 1, exit door +x-y (y wall) 1. The gangway that cleared last: straight +x-y (y wing) 1 at 1235.2 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 8804 | 7800.4 | 7.03 | 1229.1 / 1142.7 / 1106.8 | 1145.6 / 1125.0 / 1061.7 | 5597355.8 | 11405482 | 0.198 |
| gangway | 3792 | 3512.9 | 7.03 | 1227.5 / 1142.5 / 1105.1 | 1145.6 / 1125.0 / 1061.7 | 5568518.7 | 10457471 | 0.127 |
| walkway | 276 | 257.4 | 5.33 | 607.3 / 437.1 / 140.6 | 438.3 / 361.0 / 52.1 | 1015.5 | 119795 | 0.456 |
| avenue | 1920 | 1801.4 | 3.04 | 819.6 / 27.1 / 0.0 | 567.4 / 2.1 / 0.0 | 0.0 | 469929 | 1.333 |
| exit | 4 | 2.0 | 0.00 | 0.7 / 0.0 / 0.0 | 0.7 / 0.0 / 0.0 | 0.0 | 3 | 0.884 |
| concourse | 2812 | 2226.8 | 6.15 | 1191.3 / 92.2 / 51.2 | 987.3 / 76.8 / 46.0 | 27821.6 | 358284 | 0.694 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 25392 | 16030.4 | 7.73 | 1108.7 / 1098.2 / 1073.2 | 1100.5 / 1092.3 / 1067.6 | 6933337.5 | 17367042 | 0.029 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 208 x 208 from (-104, -104) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -34.5 | -34.5 | gangway | 1.00 | 5.94 | 1105.6 | 1096.0 | 1052.6 | 5984.4 | 0.008 |
| 2 | 32.5 | -32.5 | gangway | 1.00 | 5.87 | 1107.3 | 1101.2 | 1043.0 | 5905.6 | 0.005 |
| 3 | -36.5 | -36.5 | gangway | 1.00 | 5.80 | 1112.2 | 1109.8 | 1023.7 | 5722.4 | 0.011 |
| 4 | 35.5 | 35.5 | gangway | 1.00 | 5.74 | 1084.2 | 1081.8 | 1016.2 | 5696.5 | 0.009 |
| 5 | 33.5 | -33.5 | gangway | 0.99 | 5.58 | 1112.6 | 1108.0 | 1061.7 | 5682.1 | 0.007 |
| 6 | -38.5 | -38.5 | gangway | 1.00 | 6.07 | 1121.0 | 1117.8 | 956.2 | 5675.1 | 0.018 |
| 7 | 34.5 | -34.5 | gangway | 1.00 | 5.87 | 1125.7 | 1114.3 | 1041.2 | 5666.7 | 0.010 |
| 8 | -34.5 | 34.5 | gangway | 1.00 | 5.77 | 1050.5 | 1039.1 | 1001.7 | 5592.1 | 0.010 |
| 9 | 35.5 | -35.5 | gangway | 1.00 | 5.74 | 1128.3 | 1119.9 | 1032.5 | 5526.8 | 0.010 |
| 10 | 38.5 | -38.5 | gangway | 1.00 | 5.73 | 1138.3 | 1114.9 | 992.2 | 5497.4 | 0.026 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -36.5 | -38.5 | seat row | 0.50 | 7.20 | 1072.4 | 1071.3 | 1054.7 | 3743.4 | 0.005 |
| 2 | 36.5 | -38.5 | seat row | 0.50 | 7.30 | 1082.7 | 1080.2 | 1067.6 | 3697.5 | 0.006 |
| 3 | 38.5 | -35.5 | seat row | 0.50 | 7.18 | 1066.9 | 1059.9 | 1045.4 | 3696.4 | 0.006 |
| 4 | 38.5 | 36.5 | seat row | 0.50 | 7.36 | 1058.2 | 1055.9 | 1042.1 | 3680.6 | 0.006 |
| 5 | 34.5 | -38.5 | seat row | 0.50 | 7.23 | 1065.4 | 1059.8 | 1039.8 | 3673.1 | 0.005 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 7696; agent-steps of seated agents on another row's clearway: 1519290.

## Deposit check

Person-seconds deposited: 28778790.8, of them in excluded cells: 6266.549.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 6211022 overlapping pair-steps: p99 0.0029, max 0.0875 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0029 max 0.0875; venue-geometry 16: p99 0.0023 max 0.0023 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00770 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 68 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.40 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 3740 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
