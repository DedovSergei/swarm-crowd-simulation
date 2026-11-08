# Experiment `L_load150_s1`

**Task 5.10 stage 4 (AMD 26.10.1): Task 5.8's model (the level spacing on the gangway inclines, --stair-flow off): venue L, 150% requested (seed 1)**

Venue L (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (4000 x 4000), cache key a2f3aaf59c2252b7, content hash 022d17b202313d70). 69311 agents (load 109.3%, requested 150%): every one of the 63424 seats and 5887 standing (spawnOvercrowdedCrowd, seed 1; below), buffer N = 131072, 7268 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 9650701 evaluations, 543762 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.09)** (the L venue's design capacity 63424, jam capacity 171923: 23822.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T20:30:45, 810.4 s wall.

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
| t50 | 2193 | 383.6 |
| t90 | 4779 | 835.9 |
| t100 | 7268 | 1271.2 |

t_p: the step by which ceil(p x 69311) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 1954 | 82 | 60.2 | 946.1 | 23.4 | 55.3 | 59.6-69.6 |
| -x | 5.66 | 1951 | 86 | 60.2 | 946.8 | 23.3 | 59.5 | 59.5-69.4 |
| +y | 5.66 | 1944 | 81 | 60.2 | 958.5 | 22.9 | 60.6 | 60.0-70.0 |
| -y | 5.66 | 1941 | 85 | 60.2 | 965.7 | 22.7 | 63.8 | 59.8-69.8 |
| door +x+y (y wall) 0 | 2.30 | 1734 | 2726 | 0.9 | 977.2 | 46.3 | 112.5 | 42.2-52.1 |
| door +x+y (y wall) 1 | 2.30 | 1888 | 2254 | 0.9 | 1131.8 | 43.5 | 104.7 | 0.7-10.7 |
| door +x+y (y wall) 2 | 2.30 | 1750 | 1712 | 1.0 | 1119.6 | 40.8 | 107.3 | 18.0-28.0 |
| door +x+y (y wall) 3 | 2.30 | 1421 | 1157 | 0.9 | 1112.1 | 33.4 | 107.3 | 13.1-23.1 |
| door +x+y (y wall) 4 | 2.30 | 687 | 639 | 0.9 | 1138.6 | 15.7 | 109.9 | 45.8-55.8 |
| door +x+y (x wall) 0 | 2.30 | 1697 | 2732 | 0.9 | 1009.4 | 43.9 | 109.9 | 9.1-19.1 |
| door +x+y (x wall) 1 | 2.30 | 1864 | 2251 | 0.9 | 1084.9 | 44.8 | 112.5 | 6.6-16.6 |
| door +x+y (x wall) 2 | 2.30 | 1765 | 1711 | 0.9 | 1142.0 | 40.3 | 107.3 | 14.5-24.5 |
| door +x+y (x wall) 3 | 2.30 | 1399 | 1158 | 0.9 | 1139.0 | 32.1 | 109.9 | 2.3-12.2 |
| door +x+y (x wall) 4 | 2.30 | 688 | 641 | 0.9 | 1057.0 | 17.0 | 104.7 | 8.6-18.5 |
| door +x+y (corner) | 2.30 | 472 | 260 | 0.7 | 1083.0 | 11.4 | 70.6 | 23.1-33.1 |
| door -x+y (y wall) 0 | 2.30 | 1694 | 2734 | 0.9 | 1013.1 | 43.7 | 115.1 | 13.8-23.8 |
| door -x+y (y wall) 1 | 2.30 | 1872 | 2259 | 1.0 | 1135.7 | 43.0 | 109.9 | 3.0-12.9 |
| door -x+y (y wall) 2 | 2.30 | 1725 | 1709 | 0.9 | 1162.6 | 38.7 | 117.7 | 17.3-27.3 |
| door -x+y (y wall) 3 | 2.30 | 1421 | 1164 | 0.9 | 1148.4 | 32.3 | 115.1 | 31.1-41.1 |
| door -x+y (y wall) 4 | 2.30 | 704 | 648 | 1.0 | 1119.4 | 16.4 | 107.3 | 6.6-16.6 |
| door -x+y (x wall) 0 | 2.30 | 1728 | 2724 | 0.9 | 963.0 | 46.8 | 109.9 | 33.6-43.6 |
| door -x+y (x wall) 1 | 2.30 | 1901 | 2254 | 0.9 | 1146.0 | 43.3 | 109.9 | 0.7-10.7 |
| door -x+y (x wall) 2 | 2.30 | 1745 | 1716 | 0.9 | 1149.0 | 39.6 | 109.9 | 1.4-11.4 |
| door -x+y (x wall) 3 | 2.30 | 1437 | 1163 | 0.9 | 1160.9 | 32.3 | 107.3 | 18.5-28.5 |
| door -x+y (x wall) 4 | 2.30 | 686 | 639 | 1.0 | 1165.6 | 15.4 | 107.3 | 7.3-17.3 |
| door -x+y (corner) | 2.30 | 489 | 245 | 0.9 | 987.2 | 12.9 | 73.3 | 0.7-10.7 |
| door -x-y (y wall) 0 | 2.30 | 1739 | 2736 | 0.9 | 1030.9 | 44.0 | 115.1 | 10.7-20.6 |
| door -x-y (y wall) 1 | 2.30 | 1936 | 2259 | 1.0 | 1149.7 | 44.0 | 104.7 | 42.0-51.9 |
| door -x-y (y wall) 2 | 2.30 | 1776 | 1715 | 1.0 | 1195.8 | 38.8 | 109.9 | 31.7-41.6 |
| door -x-y (y wall) 3 | 2.30 | 1199 | 1163 | 0.7 | 1265.1 | 24.7 | 115.1 | 35.5-45.5 |
| door -x-y (y wall) 4 | 2.30 | 848 | 641 | 0.9 | 1262.7 | 17.5 | 109.9 | 43.0-53.0 |
| door -x-y (x wall) 0 | 2.30 | 1701 | 2721 | 0.9 | 1027.2 | 43.2 | 112.5 | 0.5-10.5 |
| door -x-y (x wall) 1 | 2.30 | 1913 | 2249 | 0.9 | 1117.3 | 44.7 | 112.5 | 27.3-37.3 |
| door -x-y (x wall) 2 | 2.30 | 1745 | 1711 | 0.9 | 1196.4 | 38.1 | 112.5 | 36.9-46.9 |
| door -x-y (x wall) 3 | 2.30 | 1233 | 1165 | 0.9 | 1259.0 | 25.6 | 112.5 | 0.5-10.5 |
| door -x-y (x wall) 4 | 2.30 | 793 | 641 | 0.7 | 1271.2 | 16.3 | 109.9 | 28.9-38.8 |
| door -x-y (corner) | 2.30 | 470 | 247 | 0.9 | 1096.7 | 11.2 | 73.3 | 73.5-83.4 |
| door +x-y (y wall) 0 | 2.30 | 1685 | 2722 | 0.9 | 1016.2 | 43.3 | 115.1 | 31.8-41.8 |
| door +x-y (y wall) 1 | 2.30 | 1862 | 2251 | 0.9 | 1157.9 | 42.0 | 104.7 | 7.5-17.5 |
| door +x-y (y wall) 2 | 2.30 | 1658 | 1714 | 0.7 | 1178.5 | 36.7 | 112.5 | 4.2-14.2 |
| door +x-y (y wall) 3 | 2.30 | 1249 | 1165 | 0.7 | 1179.7 | 27.6 | 107.3 | 1.6-11.5 |
| door +x-y (y wall) 4 | 2.30 | 918 | 638 | 0.7 | 1147.0 | 20.9 | 115.1 | 19.4-29.4 |
| door +x-y (x wall) 0 | 2.30 | 1736 | 2729 | 0.9 | 1021.6 | 44.4 | 107.3 | 25.4-35.3 |
| door +x-y (x wall) 1 | 2.30 | 1893 | 2254 | 0.7 | 1144.2 | 43.2 | 115.1 | 19.6-29.6 |
| door +x-y (x wall) 2 | 2.30 | 1615 | 1714 | 0.9 | 1162.8 | 36.3 | 104.7 | 19.4-29.4 |
| door +x-y (x wall) 3 | 2.30 | 1251 | 1156 | 0.9 | 1167.2 | 28.0 | 115.1 | 11.0-21.0 |
| door +x-y (x wall) 4 | 2.30 | 902 | 636 | 0.9 | 1181.7 | 19.9 | 107.3 | 0.7-10.7 |
| door +x-y (corner) | 2.30 | 632 | 254 | 0.7 | 956.7 | 17.2 | 73.3 | 0.5-10.5 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (2.30 m; a corner door's: the gap between its wall ends, 2.30 m); agents are removed past the outer wall's outer face (92.71 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 1954 | 2.8% | 19.5% |
| -x | avenue | 5.66 | 1951 | 2.8% | 19.5% |
| +y | avenue | 5.66 | 1944 | 2.8% | 19.4% |
| -y | avenue | 5.66 | 1941 | 2.8% | 19.4% |
| door +x+y (y wall) 0 | door | 2.30 | 1734 | 2.5% | 42.6% |
| door +x+y (y wall) 1 | door | 2.30 | 1888 | 2.7% | 46.3% |
| door +x+y (y wall) 2 | door | 2.30 | 1750 | 2.5% | 43.0% |
| door +x+y (y wall) 3 | door | 2.30 | 1421 | 2.1% | 34.9% |
| door +x+y (y wall) 4 | door | 2.30 | 687 | 1.0% | 16.9% |
| door +x+y (x wall) 0 | door | 2.30 | 1697 | 2.4% | 41.7% |
| door +x+y (x wall) 1 | door | 2.30 | 1864 | 2.7% | 45.8% |
| door +x+y (x wall) 2 | door | 2.30 | 1765 | 2.5% | 43.3% |
| door +x+y (x wall) 3 | door | 2.30 | 1399 | 2.0% | 34.3% |
| door +x+y (x wall) 4 | door | 2.30 | 688 | 1.0% | 16.9% |
| door +x+y (corner) | door | 2.30 | 472 | 0.7% | 11.6% |
| door -x+y (y wall) 0 | door | 2.30 | 1694 | 2.4% | 41.6% |
| door -x+y (y wall) 1 | door | 2.30 | 1872 | 2.7% | 46.0% |
| door -x+y (y wall) 2 | door | 2.30 | 1725 | 2.5% | 42.3% |
| door -x+y (y wall) 3 | door | 2.30 | 1421 | 2.1% | 34.9% |
| door -x+y (y wall) 4 | door | 2.30 | 704 | 1.0% | 17.3% |
| door -x+y (x wall) 0 | door | 2.30 | 1728 | 2.5% | 42.4% |
| door -x+y (x wall) 1 | door | 2.30 | 1901 | 2.7% | 46.7% |
| door -x+y (x wall) 2 | door | 2.30 | 1745 | 2.5% | 42.8% |
| door -x+y (x wall) 3 | door | 2.30 | 1437 | 2.1% | 35.3% |
| door -x+y (x wall) 4 | door | 2.30 | 686 | 1.0% | 16.8% |
| door -x+y (corner) | door | 2.30 | 489 | 0.7% | 12.0% |
| door -x-y (y wall) 0 | door | 2.30 | 1739 | 2.5% | 42.7% |
| door -x-y (y wall) 1 | door | 2.30 | 1936 | 2.8% | 47.5% |
| door -x-y (y wall) 2 | door | 2.30 | 1776 | 2.6% | 43.6% |
| door -x-y (y wall) 3 | door | 2.30 | 1199 | 1.7% | 29.4% |
| door -x-y (y wall) 4 | door | 2.30 | 848 | 1.2% | 20.8% |
| door -x-y (x wall) 0 | door | 2.30 | 1701 | 2.5% | 41.8% |
| door -x-y (x wall) 1 | door | 2.30 | 1913 | 2.8% | 47.0% |
| door -x-y (x wall) 2 | door | 2.30 | 1745 | 2.5% | 42.8% |
| door -x-y (x wall) 3 | door | 2.30 | 1233 | 1.8% | 30.3% |
| door -x-y (x wall) 4 | door | 2.30 | 793 | 1.1% | 19.5% |
| door -x-y (corner) | door | 2.30 | 470 | 0.7% | 11.5% |
| door +x-y (y wall) 0 | door | 2.30 | 1685 | 2.4% | 41.4% |
| door +x-y (y wall) 1 | door | 2.30 | 1862 | 2.7% | 45.7% |
| door +x-y (y wall) 2 | door | 2.30 | 1658 | 2.4% | 40.7% |
| door +x-y (y wall) 3 | door | 2.30 | 1249 | 1.8% | 30.7% |
| door +x-y (y wall) 4 | door | 2.30 | 918 | 1.3% | 22.5% |
| door +x-y (x wall) 0 | door | 2.30 | 1736 | 2.5% | 42.6% |
| door +x-y (x wall) 1 | door | 2.30 | 1893 | 2.7% | 46.5% |
| door +x-y (x wall) 2 | door | 2.30 | 1615 | 2.3% | 39.6% |
| door +x-y (x wall) 3 | door | 2.30 | 1251 | 1.8% | 30.7% |
| door +x-y (x wall) 4 | door | 2.30 | 902 | 1.3% | 22.1% |
| door +x-y (corner) | door | 2.30 | 632 | 0.9% | 15.5% |
| **doors (44)** | door | 101.20 | 61521 | 88.8% | |
| **avenues (4)** | avenue | 22.64 | 7790 | 11.2% | |

**Unused exit width: 0.0 of 123.8 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 1271.2 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 31.6%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 2333 | 3.4% | 2333 | 3.4% |
| straight +x+y (y wing) 1 | straight | yes | 1891 | 2.7% | 1775 | 2.6% |
| straight +x+y (y wing) 2 | straight | yes | 1649 | 2.4% | 1634 | 2.4% |
| straight +x+y (y wing) 3 | straight | yes | 1322 | 1.9% | 1321 | 1.9% |
| straight +x+y (y wing) 4 | straight | yes | 563 | 0.8% | 547 | 0.8% |
| straight +x+y (x wing) 0 | straight | yes | 2339 | 3.4% | 2339 | 3.4% |
| straight +x+y (x wing) 1 | straight | yes | 1881 | 2.7% | 1779 | 2.6% |
| straight +x+y (x wing) 2 | straight | yes | 1667 | 2.4% | 1653 | 2.4% |
| straight +x+y (x wing) 3 | straight | yes | 1302 | 1.9% | 1300 | 1.9% |
| straight +x+y (x wing) 4 | straight | yes | 548 | 0.8% | 541 | 0.8% |
| corner +x+y | corner | yes | 2007 | 2.9% | 647 | 0.9% |
| straight -x+y (y wing) 0 | straight | yes | 2343 | 3.4% | 2343 | 3.4% |
| straight -x+y (y wing) 1 | straight | yes | 1845 | 2.7% | 1772 | 2.6% |
| straight -x+y (y wing) 2 | straight | yes | 1654 | 2.4% | 1628 | 2.3% |
| straight -x+y (y wing) 3 | straight | yes | 1321 | 1.9% | 1321 | 1.9% |
| straight -x+y (y wing) 4 | straight | yes | 540 | 0.8% | 532 | 0.8% |
| straight -x+y (x wing) 0 | straight | yes | 2332 | 3.4% | 2332 | 3.4% |
| straight -x+y (x wing) 1 | straight | yes | 1875 | 2.7% | 1792 | 2.6% |
| straight -x+y (x wing) 2 | straight | yes | 1635 | 2.4% | 1624 | 2.3% |
| straight -x+y (x wing) 3 | straight | yes | 1339 | 1.9% | 1335 | 1.9% |
| straight -x+y (x wing) 4 | straight | yes | 555 | 0.8% | 543 | 0.8% |
| corner -x+y | corner | yes | 1987 | 2.9% | 644 | 0.9% |
| straight -x-y (y wing) 0 | straight | yes | 2321 | 3.3% | 2321 | 3.3% |
| straight -x-y (y wing) 1 | straight | yes | 1938 | 2.8% | 1837 | 2.7% |
| straight -x-y (y wing) 2 | straight | yes | 1696 | 2.4% | 1690 | 2.4% |
| straight -x-y (y wing) 3 | straight | yes | 1097 | 1.6% | 1089 | 1.6% |
| straight -x-y (y wing) 4 | straight | yes | 684 | 1.0% | 677 | 1.0% |
| straight -x-y (x wing) 0 | straight | yes | 2366 | 3.4% | 2366 | 3.4% |
| straight -x-y (x wing) 1 | straight | yes | 1916 | 2.8% | 1819 | 2.6% |
| straight -x-y (x wing) 2 | straight | yes | 1690 | 2.4% | 1684 | 2.4% |
| straight -x-y (x wing) 3 | straight | yes | 1139 | 1.6% | 1129 | 1.6% |
| straight -x-y (x wing) 4 | straight | yes | 616 | 0.9% | 593 | 0.9% |
| corner -x-y | corner | yes | 1979 | 2.9% | 660 | 1.0% |
| straight +x-y (y wing) 0 | straight | yes | 2329 | 3.4% | 2329 | 3.4% |
| straight +x-y (y wing) 1 | straight | yes | 1848 | 2.7% | 1776 | 2.6% |
| straight +x-y (y wing) 2 | straight | yes | 1649 | 2.4% | 1615 | 2.3% |
| straight +x-y (y wing) 3 | straight | yes | 1161 | 1.7% | 1138 | 1.6% |
| straight +x-y (y wing) 4 | straight | yes | 723 | 1.0% | 707 | 1.0% |
| straight +x-y (x wing) 0 | straight | yes | 2322 | 3.4% | 2322 | 3.4% |
| straight +x-y (x wing) 1 | straight | yes | 1906 | 2.7% | 1795 | 2.6% |
| straight +x-y (x wing) 2 | straight | yes | 1580 | 2.3% | 1548 | 2.2% |
| straight +x-y (x wing) 3 | straight | yes | 1187 | 1.7% | 1161 | 1.7% |
| straight +x-y (x wing) 4 | straight | yes | 718 | 1.0% | 705 | 1.0% |
| corner +x-y | corner | yes | 2091 | 3.0% | 771 | 1.1% |
| **straight (40)** | | | 61820 | | 60745 | 87.6% |
| **corner (4)** | | | 8064 | | 2722 | 3.9% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 5844, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 1954 | 60.2 | 946.1 | 0.28 | 0.66 | 0.0% |
| -x | 1951 | 60.2 | 946.8 | 0.28 | 0.71 | 0.0% |
| +y | 1944 | 60.2 | 958.5 | 0.27 | 0.72 | 0.0% |
| -y | 1941 | 60.2 | 965.7 | 0.27 | 0.76 | 0.0% |
| door +x+y (y wall) 0 | 1734 | 0.9 | 977.2 | 0.55 | 1.35 | 5.1% |
| door +x+y (y wall) 1 | 1888 | 0.9 | 1131.8 | 0.52 | 1.25 | 5.3% |
| door +x+y (y wall) 2 | 1750 | 1.0 | 1119.6 | 0.49 | 1.28 | 4.4% |
| door +x+y (y wall) 3 | 1421 | 0.9 | 1112.1 | 0.40 | 1.28 | 4.5% |
| door +x+y (y wall) 4 | 687 | 0.9 | 1138.6 | 0.19 | 1.31 | 5.2% |
| door +x+y (x wall) 0 | 1697 | 0.9 | 1009.4 | 0.52 | 1.31 | 5.9% |
| door +x+y (x wall) 1 | 1864 | 0.9 | 1084.9 | 0.54 | 1.35 | 5.5% |
| door +x+y (x wall) 2 | 1765 | 0.9 | 1142.0 | 0.48 | 1.28 | 5.2% |
| door +x+y (x wall) 3 | 1399 | 0.9 | 1139.0 | 0.38 | 1.31 | 4.3% |
| door +x+y (x wall) 4 | 688 | 0.9 | 1057.0 | 0.20 | 1.25 | 5.6% |
| door +x+y (corner) | 472 | 0.7 | 1083.0 | 0.14 | 0.85 | 1.8% |
| door -x+y (y wall) 0 | 1694 | 0.9 | 1013.1 | 0.52 | 1.38 | 4.9% |
| door -x+y (y wall) 1 | 1872 | 1.0 | 1135.7 | 0.51 | 1.31 | 5.3% |
| door -x+y (y wall) 2 | 1725 | 0.9 | 1162.6 | 0.46 | 1.41 | 4.3% |
| door -x+y (y wall) 3 | 1421 | 0.9 | 1148.4 | 0.39 | 1.38 | 4.3% |
| door -x+y (y wall) 4 | 704 | 1.0 | 1119.4 | 0.20 | 1.28 | 5.3% |
| door -x+y (x wall) 0 | 1728 | 0.9 | 963.0 | 0.56 | 1.31 | 5.2% |
| door -x+y (x wall) 1 | 1901 | 0.9 | 1146.0 | 0.52 | 1.31 | 4.3% |
| door -x+y (x wall) 2 | 1745 | 0.9 | 1149.0 | 0.47 | 1.31 | 5.2% |
| door -x+y (x wall) 3 | 1437 | 0.9 | 1160.9 | 0.39 | 1.28 | 5.1% |
| door -x+y (x wall) 4 | 686 | 1.0 | 1165.6 | 0.18 | 1.28 | 5.1% |
| door -x+y (corner) | 489 | 0.9 | 987.2 | 0.15 | 0.88 | 2.0% |
| door -x-y (y wall) 0 | 1739 | 0.9 | 1030.9 | 0.53 | 1.38 | 4.8% |
| door -x-y (y wall) 1 | 1936 | 1.0 | 1149.7 | 0.53 | 1.25 | 5.2% |
| door -x-y (y wall) 2 | 1776 | 1.0 | 1195.8 | 0.46 | 1.31 | 5.0% |
| door -x-y (y wall) 3 | 1199 | 0.7 | 1265.1 | 0.30 | 1.38 | 3.9% |
| door -x-y (y wall) 4 | 848 | 0.9 | 1262.7 | 0.21 | 1.31 | 4.7% |
| door -x-y (x wall) 0 | 1701 | 0.9 | 1027.2 | 0.52 | 1.35 | 4.8% |
| door -x-y (x wall) 1 | 1913 | 0.9 | 1117.3 | 0.53 | 1.35 | 4.4% |
| door -x-y (x wall) 2 | 1745 | 0.9 | 1196.4 | 0.46 | 1.35 | 4.2% |
| door -x-y (x wall) 3 | 1233 | 0.9 | 1259.0 | 0.31 | 1.35 | 3.9% |
| door -x-y (x wall) 4 | 793 | 0.7 | 1271.2 | 0.19 | 1.31 | 4.7% |
| door -x-y (corner) | 470 | 0.9 | 1096.7 | 0.13 | 0.88 | 0.9% |
| door +x-y (y wall) 0 | 1685 | 0.9 | 1016.2 | 0.52 | 1.38 | 4.9% |
| door +x-y (y wall) 1 | 1862 | 0.9 | 1157.9 | 0.50 | 1.25 | 4.3% |
| door +x-y (y wall) 2 | 1658 | 0.7 | 1178.5 | 0.44 | 1.35 | 5.0% |
| door +x-y (y wall) 3 | 1249 | 0.7 | 1179.7 | 0.33 | 1.28 | 5.0% |
| door +x-y (y wall) 4 | 918 | 0.7 | 1147.0 | 0.25 | 1.38 | 5.2% |
| door +x-y (x wall) 0 | 1736 | 0.9 | 1021.6 | 0.53 | 1.28 | 4.9% |
| door +x-y (x wall) 1 | 1893 | 0.7 | 1144.2 | 0.52 | 1.38 | 4.3% |
| door +x-y (x wall) 2 | 1615 | 0.9 | 1162.8 | 0.43 | 1.25 | 5.1% |
| door +x-y (x wall) 3 | 1251 | 0.9 | 1167.2 | 0.33 | 1.38 | 4.2% |
| door +x-y (x wall) 4 | 902 | 0.9 | 1181.7 | 0.24 | 1.28 | 5.0% |
| door +x-y (corner) | 632 | 0.7 | 956.7 | 0.21 | 0.88 | 2.1% |

Mean flow / w J averaged over the doors 0.39, over the avenues 0.28.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 103.1 | 2333 | 1610 / 725 / 757 | 0.3 | 920.7 | 3.36 | 6.12 | 88% | 87% | 1% | 4.72 |
| straight +x+y (y wing) 1 | 1.20 | 81.5 | 1869 | 1775 / 0 / 179 | 0.7 | 1128.8 | 1.73 | 3.11 | 85% | 75% | 11% | 4.12 |
| straight +x+y (y wing) 2 | 1.20 | 61.0 | 1496 | 1634 / 0 / 34 | 0.7 | 1116.6 | 1.49 | 2.81 | 72% | 64% | 8% | 4.19 |
| straight +x+y (y wing) 3 | 1.20 | 39.4 | 971 | 1321 / 0 / 8 | 0.7 | 1109.1 | 1.20 | 2.11 | 68% | 42% | 26% | 3.09 |
| straight +x+y (y wing) 4 | 1.20 | 18.8 | 408 | 547 / 0 / 24 | 0.7 | 1135.7 | 0.50 | 2.31 | 18% | 18% | 1% | 4.23 |
| straight +x+y (x wing) 0 | 1.20 | 103.1 | 2339 | 1544 / 795 / 913 | 0.2 | 894.1 | 3.64 | 6.02 | 90% | 86% | 4% | 4.47 |
| straight +x+y (x wing) 1 | 1.20 | 81.5 | 1846 | 1779 / 0 / 215 | 0.7 | 1082.0 | 1.84 | 3.11 | 91% | 79% | 12% | 3.85 |
| straight +x+y (x wing) 2 | 1.20 | 61.0 | 1548 | 1653 / 0 / 26 | 0.7 | 1139.0 | 1.47 | 2.41 | 73% | 67% | 6% | 4.09 |
| straight +x+y (x wing) 3 | 1.20 | 39.4 | 957 | 1300 / 0 / 18 | 0.7 | 1136.0 | 1.16 | 2.11 | 69% | 42% | 27% | 2.97 |
| straight +x+y (x wing) 4 | 1.20 | 18.8 | 396 | 541 / 0 / 21 | 0.7 | 1054.0 | 0.53 | 2.11 | 25% | 19% | 7% | 3.30 |
| corner +x+y | 1.20 | 186.0 | 1706 | 336 / 311 / 1443 | 0.7 | 1111.7 | 1.88 | 5.62 | 89% | 76% | 13% | 3.18 |
| straight -x+y (y wing) 0 | 1.20 | 103.1 | 2343 | 1554 / 789 / 1060 | 0.2 | 883.3 | 3.85 | 7.12 | 90% | 87% | 3% | 4.44 |
| straight -x+y (y wing) 1 | 1.20 | 81.5 | 1823 | 1772 / 0 / 148 | 0.7 | 1132.7 | 1.70 | 3.61 | 88% | 75% | 13% | 4.01 |
| straight -x+y (y wing) 2 | 1.20 | 61.0 | 1555 | 1628 / 0 / 30 | 0.7 | 1159.6 | 1.43 | 2.21 | 74% | 66% | 9% | 3.85 |
| straight -x+y (y wing) 3 | 1.20 | 39.4 | 959 | 1321 / 0 / 14 | 0.7 | 1145.5 | 1.17 | 2.41 | 70% | 40% | 30% | 2.92 |
| straight -x+y (y wing) 4 | 1.20 | 18.8 | 399 | 532 / 0 / 13 | 0.7 | 1116.4 | 0.49 | 2.11 | 18% | 18% | 0% | 4.18 |
| straight -x+y (x wing) 0 | 1.20 | 103.1 | 2331 | 1606 / 730 / 774 | 0.3 | 927.2 | 3.35 | 5.32 | 89% | 87% | 2% | 4.64 |
| straight -x+y (x wing) 1 | 1.20 | 81.5 | 1863 | 1792 / 0 / 168 | 0.7 | 1143.0 | 1.72 | 3.01 | 90% | 75% | 15% | 3.98 |
| straight -x+y (x wing) 2 | 1.20 | 61.0 | 1493 | 1624 / 0 / 13 | 0.7 | 1146.0 | 1.43 | 2.41 | 69% | 63% | 5% | 4.18 |
| straight -x+y (x wing) 3 | 1.20 | 39.4 | 970 | 1335 / 0 / 12 | 0.7 | 1157.9 | 1.16 | 2.01 | 63% | 39% | 24% | 3.15 |
| straight -x+y (x wing) 4 | 1.20 | 18.8 | 406 | 543 / 0 / 14 | 0.7 | 1162.6 | 0.48 | 2.11 | 18% | 18% | 0% | 4.15 |
| corner -x+y | 1.20 | 186.0 | 1724 | 368 / 277 / 1396 | 0.7 | 1138.6 | 1.79 | 5.12 | 90% | 70% | 19% | 3.01 |
| straight -x-y (y wing) 0 | 1.20 | 103.1 | 2321 | 1595 / 727 / 746 | 0.2 | 899.0 | 3.41 | 5.52 | 89% | 89% | 0% | 4.80 |
| straight -x-y (y wing) 1 | 1.20 | 81.5 | 1913 | 1837 / 0 / 277 | 0.7 | 1146.7 | 1.84 | 3.71 | 89% | 74% | 15% | 4.06 |
| straight -x-y (y wing) 2 | 1.20 | 61.0 | 1503 | 1690 / 0 / 21 | 0.7 | 1192.9 | 1.43 | 2.11 | 68% | 62% | 7% | 4.06 |
| straight -x-y (y wing) 3 | 1.20 | 39.4 | 945 | 1089 / 0 / 18 | 0.7 | 1262.1 | 0.88 | 2.21 | 43% | 38% | 6% | 3.79 |
| straight -x-y (y wing) 4 | 1.20 | 18.8 | 395 | 677 / 0 / 27 | 0.7 | 1259.7 | 0.56 | 2.11 | 17% | 15% | 2% | 4.03 |
| straight -x-y (x wing) 0 | 1.20 | 103.1 | 2366 | 1572 / 794 / 928 | 0.5 | 891.5 | 3.70 | 6.22 | 90% | 86% | 4% | 4.42 |
| straight -x-y (x wing) 1 | 1.20 | 81.5 | 1887 | 1819 / 0 / 232 | 0.7 | 1114.3 | 1.84 | 3.41 | 91% | 82% | 9% | 3.93 |
| straight -x-y (x wing) 2 | 1.20 | 61.0 | 1501 | 1684 / 0 / 9 | 0.7 | 1193.4 | 1.42 | 2.11 | 84% | 63% | 21% | 3.41 |
| straight -x-y (x wing) 3 | 1.20 | 39.4 | 935 | 1129 / 0 / 21 | 0.7 | 1256.0 | 0.92 | 2.21 | 42% | 37% | 5% | 3.90 |
| straight -x-y (x wing) 4 | 1.20 | 18.8 | 415 | 593 / 0 / 25 | 0.7 | 1268.2 | 0.49 | 2.21 | 17% | 16% | 1% | 4.04 |
| corner -x-y | 1.20 | 186.0 | 1684 | 347 / 313 / 1465 | 0.7 | 1244.3 | 1.71 | 4.21 | 88% | 67% | 21% | 2.86 |
| straight +x-y (y wing) 0 | 1.20 | 103.1 | 2329 | 1547 / 782 / 1061 | 0.5 | 881.5 | 3.85 | 6.22 | 90% | 83% | 7% | 4.34 |
| straight +x-y (y wing) 1 | 1.20 | 81.5 | 1827 | 1776 / 0 / 129 | 0.7 | 1154.9 | 1.65 | 3.31 | 74% | 74% | 0% | 4.44 |
| straight +x-y (y wing) 2 | 1.20 | 61.0 | 1552 | 1615 / 0 / 36 | 0.7 | 1175.5 | 1.41 | 2.61 | 75% | 66% | 8% | 3.81 |
| straight +x-y (y wing) 3 | 1.20 | 39.4 | 938 | 1138 / 0 / 31 | 0.7 | 1176.8 | 0.99 | 2.21 | 46% | 39% | 7% | 3.75 |
| straight +x-y (y wing) 4 | 1.20 | 18.8 | 403 | 707 / 0 / 20 | 0.7 | 1144.1 | 0.64 | 2.21 | 17% | 17% | 0% | 4.12 |
| straight +x-y (x wing) 0 | 1.20 | 103.1 | 2321 | 1601 / 721 / 694 | 0.2 | 929.1 | 3.25 | 5.82 | 89% | 86% | 3% | 4.51 |
| straight +x-y (x wing) 1 | 1.20 | 81.5 | 1896 | 1795 / 0 / 164 | 0.7 | 1141.3 | 1.72 | 3.41 | 76% | 76% | 0% | 4.50 |
| straight +x-y (x wing) 2 | 1.20 | 61.0 | 1477 | 1548 / 0 / 35 | 0.7 | 1159.8 | 1.37 | 2.21 | 73% | 62% | 10% | 3.91 |
| straight +x-y (x wing) 3 | 1.20 | 39.4 | 968 | 1161 / 0 / 30 | 0.7 | 1164.2 | 1.02 | 2.31 | 47% | 41% | 6% | 3.85 |
| straight +x-y (x wing) 4 | 1.20 | 18.8 | 408 | 705 / 0 / 14 | 0.7 | 1178.7 | 0.61 | 2.41 | 18% | 18% | 1% | 4.01 |
| corner +x-y | 1.20 | 186.0 | 1748 | 502 / 270 / 1375 | 0.7 | 1154.7 | 1.86 | 4.21 | 90% | 58% | 32% | 2.64 |

The last agent out (agent 34425, t100 1271.2 s): last gangway straight -x-y (x wing) 4, exit door -x-y (x wall) 4. The gangway that cleared last: straight -x-y (x wing) 4 at 1268.2 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 8804 | 7800.4 | 6.97 | 1261.1 / 1210.2 / 1119.6 | 1206.5 / 1190.8 / 1076.7 | 5607604.5 | 11436074 | 0.197 |
| gangway | 3792 | 3512.9 | 6.97 | 1260.0 / 1210.0 / 1118.2 | 1206.5 / 1190.8 / 1076.7 | 5576981.9 | 10483134 | 0.126 |
| walkway | 276 | 257.4 | 5.52 | 632.3 / 456.5 / 225.3 | 506.2 / 429.7 / 130.7 | 2036.1 | 124474 | 0.440 |
| avenue | 1920 | 1801.4 | 3.20 | 834.8 / 60.5 / 0.0 | 594.9 / 1.9 / 0.0 | 0.0 | 466924 | 1.333 |
| exit | 4 | 2.0 | 0.00 | 0.7 / 0.0 / 0.0 | 0.7 / 0.0 / 0.0 | 0.0 | 3 | 0.838 |
| concourse | 2812 | 2226.8 | 6.02 | 1197.4 / 107.2 / 51.1 | 992.9 / 82.2 / 45.7 | 28586.6 | 361540 | 0.693 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 25392 | 16030.4 | 7.89 | 1118.2 / 1097.5 / 1079.3 | 1092.8 / 1090.2 / 1068.3 | 6918276.0 | 17349964 | 0.029 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 208 x 208 from (-104, -104) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -50.5 | -50.5 | gangway | 1.00 | 5.92 | 1148.8 | 1144.8 | 1054.0 | 5966.1 | 0.012 |
| 2 | -58.5 | -59.5 | gangway | 1.00 | 6.13 | 1197.6 | 1187.6 | 1022.3 | 5793.1 | 0.016 |
| 3 | 34.5 | 34.5 | gangway | 1.00 | 6.30 | 1027.2 | 1018.3 | 963.7 | 5770.5 | 0.009 |
| 4 | -48.5 | -48.5 | gangway | 1.00 | 5.64 | 1128.5 | 1126.0 | 1060.1 | 5705.9 | 0.008 |
| 5 | 34.5 | -34.5 | gangway | 1.00 | 6.00 | 1064.7 | 1052.8 | 1002.0 | 5658.2 | 0.012 |
| 6 | -34.5 | 34.5 | gangway | 1.00 | 5.72 | 1052.2 | 1042.8 | 1002.9 | 5642.6 | 0.008 |
| 7 | -35.5 | 35.5 | gangway | 1.00 | 5.96 | 1056.1 | 1054.2 | 992.6 | 5640.3 | 0.011 |
| 8 | -51.5 | -51.5 | gangway | 1.00 | 5.79 | 1161.9 | 1159.3 | 997.5 | 5424.8 | 0.018 |
| 9 | -49.5 | -49.5 | gangway | 0.99 | 5.64 | 1141.4 | 1133.6 | 1023.6 | 5357.7 | 0.012 |
| 10 | -34.5 | -34.5 | gangway | 1.00 | 5.81 | 1030.7 | 1022.9 | 957.3 | 5341.8 | 0.007 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -36.5 | -38.5 | seat row | 0.50 | 7.40 | 1010.8 | 1009.2 | 993.6 | 3593.7 | 0.005 |
| 2 | -36.5 | 38.5 | seat row | 0.50 | 7.54 | 999.4 | 996.8 | 984.7 | 3565.6 | 0.007 |
| 3 | -54.5 | -52.5 | seat row | 0.50 | 7.39 | 1022.5 | 1012.7 | 986.8 | 3521.4 | 0.007 |
| 4 | -52.5 | -54.5 | seat row | 0.50 | 7.31 | 1026.2 | 1020.6 | 996.1 | 3514.0 | 0.008 |
| 5 | -38.5 | -36.5 | seat row | 0.50 | 7.33 | 1006.4 | 1006.1 | 993.3 | 3500.9 | 0.005 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 7589; agent-steps of seated agents on another row's clearway: 1611197.

## Deposit check

Person-seconds deposited: 28792305.5, of them in excluded cells: 6267.679.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 6435141 overlapping pair-steps: p99 0.0031, max 0.0736 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0031 max 0.0736; venue-geometry 19: p99 0.0013 max 0.0013 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00762 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 50 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.43 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 3694 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
