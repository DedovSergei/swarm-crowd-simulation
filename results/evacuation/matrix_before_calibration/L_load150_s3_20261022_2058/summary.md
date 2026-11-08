# Experiment `L_load150_s3`

**Task 5.10 stage 4 (AMD 26.10.1): Task 5.8's model (the level spacing on the gangway inclines, --stair-flow off): venue L, 150% requested (seed 3)**

Venue L (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (4000 x 4000), cache key a2f3aaf59c2252b7, content hash 022d17b202313d70). 69311 agents (load 109.3%, requested 150%): every one of the 63424 seats and 5887 standing (spawnOvercrowdedCrowd, seed 3; below), buffer N = 131072, 7026 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 9641597 evaluations, 554509 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.09)** (the L venue's design capacity 63424, jam capacity 171923: 23822.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T20:58:35, 675.7 s wall.

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
| t50 | 2177 | 380.8 |
| t90 | 4813 | 841.8 |
| t100 | 7026 | 1228.9 |

t_p: the step by which ceil(p x 69311) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 1976 | 88 | 60.2 | 935.6 | 23.9 | 62.7 | 60.0-70.0 |
| -x | 5.66 | 1951 | 86 | 60.2 | 921.6 | 24.0 | 59.5 | 59.6-69.6 |
| +y | 5.66 | 1943 | 90 | 60.2 | 916.3 | 24.1 | 60.6 | 59.8-69.8 |
| -y | 5.66 | 1947 | 85 | 60.2 | 924.7 | 23.9 | 58.5 | 59.6-69.6 |
| door +x+y (y wall) 0 | 2.30 | 1711 | 2734 | 0.9 | 1029.5 | 43.4 | 115.1 | 20.1-30.1 |
| door +x+y (y wall) 1 | 2.30 | 1919 | 2257 | 0.9 | 1120.8 | 44.7 | 107.3 | 42.5-52.5 |
| door +x+y (y wall) 2 | 2.30 | 1742 | 1712 | 0.7 | 1186.6 | 38.3 | 109.9 | 2.1-12.1 |
| door +x+y (y wall) 3 | 2.30 | 1198 | 1160 | 0.9 | 1170.5 | 26.7 | 109.9 | 10.7-20.6 |
| door +x+y (y wall) 4 | 2.30 | 839 | 641 | 0.9 | 1159.5 | 18.9 | 104.7 | 0.5-10.5 |
| door +x+y (x wall) 0 | 2.30 | 1733 | 2724 | 0.9 | 1033.0 | 43.8 | 120.4 | 18.7-28.7 |
| door +x+y (x wall) 1 | 2.30 | 1897 | 2246 | 0.7 | 1171.9 | 42.2 | 104.7 | 2.1-12.1 |
| door +x+y (x wall) 2 | 2.30 | 1697 | 1717 | 0.7 | 1187.6 | 37.3 | 109.9 | 37.3-47.2 |
| door +x+y (x wall) 3 | 2.30 | 1243 | 1162 | 0.9 | 1185.7 | 27.4 | 107.3 | 11.2-21.2 |
| door +x+y (x wall) 4 | 2.30 | 846 | 638 | 1.0 | 1158.9 | 19.1 | 112.5 | 38.0-47.9 |
| door +x+y (corner) | 2.30 | 529 | 248 | 0.9 | 1115.6 | 12.4 | 70.6 | 79.4-89.4 |
| door -x+y (y wall) 0 | 2.30 | 1713 | 2731 | 0.7 | 1023.9 | 43.7 | 112.5 | 10.7-20.6 |
| door -x+y (y wall) 1 | 2.30 | 1907 | 2259 | 0.9 | 1113.1 | 44.7 | 115.1 | 8.4-18.4 |
| door -x+y (y wall) 2 | 2.30 | 1628 | 1718 | 0.9 | 1138.1 | 37.3 | 104.7 | 40.1-50.0 |
| door -x+y (y wall) 3 | 2.30 | 1233 | 1162 | 0.7 | 1144.2 | 28.1 | 107.3 | 35.7-45.7 |
| door -x+y (y wall) 4 | 2.30 | 885 | 638 | 0.9 | 1144.4 | 20.2 | 104.7 | 1.6-11.5 |
| door -x+y (x wall) 0 | 2.30 | 1705 | 2725 | 0.9 | 974.9 | 45.7 | 115.1 | 22.9-32.9 |
| door -x+y (x wall) 1 | 2.30 | 1892 | 2261 | 0.7 | 1083.9 | 45.6 | 112.5 | 1.4-11.4 |
| door -x+y (x wall) 2 | 2.30 | 1620 | 1706 | 0.9 | 1121.0 | 37.7 | 109.9 | 1.4-11.4 |
| door -x+y (x wall) 3 | 2.30 | 1257 | 1167 | 0.7 | 1146.3 | 28.6 | 112.5 | 18.2-28.2 |
| door -x+y (x wall) 4 | 2.30 | 976 | 642 | 0.9 | 1078.8 | 23.6 | 112.5 | 11.5-21.5 |
| door -x+y (corner) | 2.30 | 585 | 242 | 0.9 | 1027.2 | 14.9 | 73.3 | 72.1-82.0 |
| door -x-y (y wall) 0 | 2.30 | 1710 | 2729 | 0.7 | 1049.3 | 42.5 | 115.1 | 20.8-30.8 |
| door -x-y (y wall) 1 | 2.30 | 1924 | 2254 | 0.9 | 1083.0 | 46.4 | 109.9 | 3.1-13.1 |
| door -x-y (y wall) 2 | 2.30 | 1732 | 1710 | 0.9 | 1154.0 | 39.2 | 112.5 | 19.4-29.4 |
| door -x-y (y wall) 3 | 2.30 | 1291 | 1163 | 0.9 | 1182.7 | 28.5 | 115.1 | 11.9-21.9 |
| door -x-y (y wall) 4 | 2.30 | 747 | 645 | 1.0 | 1166.8 | 16.7 | 115.1 | 35.9-45.8 |
| door -x-y (x wall) 0 | 2.30 | 1721 | 2720 | 0.7 | 1059.9 | 42.4 | 104.7 | 18.0-28.0 |
| door -x-y (x wall) 1 | 2.30 | 1930 | 2259 | 0.7 | 1073.6 | 46.9 | 109.9 | 1.2-11.2 |
| door -x-y (x wall) 2 | 2.30 | 1742 | 1704 | 0.9 | 1172.9 | 38.8 | 109.9 | 19.4-29.4 |
| door -x-y (x wall) 3 | 2.30 | 1199 | 1160 | 0.7 | 1181.7 | 26.5 | 109.9 | 36.4-46.4 |
| door -x-y (x wall) 4 | 2.30 | 835 | 643 | 0.9 | 1199.2 | 18.2 | 112.5 | 1.6-11.5 |
| door -x-y (corner) | 2.30 | 538 | 245 | 1.0 | 1153.2 | 12.2 | 70.6 | 0.9-10.8 |
| door +x-y (y wall) 0 | 2.30 | 1725 | 2725 | 0.9 | 1025.5 | 43.9 | 112.5 | 28.9-38.8 |
| door +x-y (y wall) 1 | 2.30 | 1924 | 2259 | 1.0 | 1148.3 | 43.7 | 112.5 | 43.2-53.2 |
| door +x-y (y wall) 2 | 2.30 | 1685 | 1708 | 0.7 | 1191.6 | 36.9 | 112.5 | 0.9-10.8 |
| door +x-y (y wall) 3 | 2.30 | 1315 | 1165 | 0.9 | 1176.2 | 29.2 | 104.7 | 0.5-10.5 |
| door +x-y (y wall) 4 | 2.30 | 754 | 639 | 0.9 | 1118.9 | 17.6 | 109.9 | 8.7-18.7 |
| door +x-y (x wall) 0 | 2.30 | 1725 | 2726 | 0.7 | 1025.3 | 43.9 | 109.9 | 22.2-32.2 |
| door +x-y (x wall) 1 | 2.30 | 1897 | 2257 | 0.9 | 1216.7 | 40.7 | 107.3 | 30.1-40.1 |
| door +x-y (x wall) 2 | 2.30 | 1700 | 1719 | 0.9 | 1218.4 | 36.4 | 109.9 | 4.5-14.5 |
| door +x-y (x wall) 3 | 2.30 | 1310 | 1159 | 0.9 | 1206.0 | 28.4 | 117.7 | 5.1-15.0 |
| door +x-y (x wall) 4 | 2.30 | 783 | 638 | 0.9 | 1228.9 | 16.6 | 115.1 | 11.9-21.9 |
| door +x-y (corner) | 2.30 | 552 | 245 | 0.9 | 857.7 | 16.8 | 73.3 | 0.5-10.5 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (2.30 m; a corner door's: the gap between its wall ends, 2.30 m); agents are removed past the outer wall's outer face (92.71 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 1976 | 2.9% | 20.4% |
| -x | avenue | 5.66 | 1951 | 2.8% | 20.1% |
| +y | avenue | 5.66 | 1943 | 2.8% | 20.0% |
| -y | avenue | 5.66 | 1947 | 2.8% | 20.1% |
| door +x+y (y wall) 0 | door | 2.30 | 1711 | 2.5% | 43.4% |
| door +x+y (y wall) 1 | door | 2.30 | 1919 | 2.8% | 48.7% |
| door +x+y (y wall) 2 | door | 2.30 | 1742 | 2.5% | 44.2% |
| door +x+y (y wall) 3 | door | 2.30 | 1198 | 1.7% | 30.4% |
| door +x+y (y wall) 4 | door | 2.30 | 839 | 1.2% | 21.3% |
| door +x+y (x wall) 0 | door | 2.30 | 1733 | 2.5% | 44.0% |
| door +x+y (x wall) 1 | door | 2.30 | 1897 | 2.7% | 48.2% |
| door +x+y (x wall) 2 | door | 2.30 | 1697 | 2.4% | 43.1% |
| door +x+y (x wall) 3 | door | 2.30 | 1243 | 1.8% | 31.6% |
| door +x+y (x wall) 4 | door | 2.30 | 846 | 1.2% | 21.5% |
| door +x+y (corner) | door | 2.30 | 529 | 0.8% | 13.4% |
| door -x+y (y wall) 0 | door | 2.30 | 1713 | 2.5% | 43.5% |
| door -x+y (y wall) 1 | door | 2.30 | 1907 | 2.8% | 48.4% |
| door -x+y (y wall) 2 | door | 2.30 | 1628 | 2.3% | 41.3% |
| door -x+y (y wall) 3 | door | 2.30 | 1233 | 1.8% | 31.3% |
| door -x+y (y wall) 4 | door | 2.30 | 885 | 1.3% | 22.5% |
| door -x+y (x wall) 0 | door | 2.30 | 1705 | 2.5% | 43.3% |
| door -x+y (x wall) 1 | door | 2.30 | 1892 | 2.7% | 48.0% |
| door -x+y (x wall) 2 | door | 2.30 | 1620 | 2.3% | 41.1% |
| door -x+y (x wall) 3 | door | 2.30 | 1257 | 1.8% | 31.9% |
| door -x+y (x wall) 4 | door | 2.30 | 976 | 1.4% | 24.8% |
| door -x+y (corner) | door | 2.30 | 585 | 0.8% | 14.9% |
| door -x-y (y wall) 0 | door | 2.30 | 1710 | 2.5% | 43.4% |
| door -x-y (y wall) 1 | door | 2.30 | 1924 | 2.8% | 48.9% |
| door -x-y (y wall) 2 | door | 2.30 | 1732 | 2.5% | 44.0% |
| door -x-y (y wall) 3 | door | 2.30 | 1291 | 1.9% | 32.8% |
| door -x-y (y wall) 4 | door | 2.30 | 747 | 1.1% | 19.0% |
| door -x-y (x wall) 0 | door | 2.30 | 1721 | 2.5% | 43.7% |
| door -x-y (x wall) 1 | door | 2.30 | 1930 | 2.8% | 49.0% |
| door -x-y (x wall) 2 | door | 2.30 | 1742 | 2.5% | 44.2% |
| door -x-y (x wall) 3 | door | 2.30 | 1199 | 1.7% | 30.4% |
| door -x-y (x wall) 4 | door | 2.30 | 835 | 1.2% | 21.2% |
| door -x-y (corner) | door | 2.30 | 538 | 0.8% | 13.7% |
| door +x-y (y wall) 0 | door | 2.30 | 1725 | 2.5% | 43.8% |
| door +x-y (y wall) 1 | door | 2.30 | 1924 | 2.8% | 48.9% |
| door +x-y (y wall) 2 | door | 2.30 | 1685 | 2.4% | 42.8% |
| door +x-y (y wall) 3 | door | 2.30 | 1315 | 1.9% | 33.4% |
| door +x-y (y wall) 4 | door | 2.30 | 754 | 1.1% | 19.1% |
| door +x-y (x wall) 0 | door | 2.30 | 1725 | 2.5% | 43.8% |
| door +x-y (x wall) 1 | door | 2.30 | 1897 | 2.7% | 48.2% |
| door +x-y (x wall) 2 | door | 2.30 | 1700 | 2.5% | 43.2% |
| door +x-y (x wall) 3 | door | 2.30 | 1310 | 1.9% | 33.3% |
| door +x-y (x wall) 4 | door | 2.30 | 783 | 1.1% | 19.9% |
| door +x-y (corner) | door | 2.30 | 552 | 0.8% | 14.0% |
| **doors (44)** | door | 101.20 | 61494 | 88.7% | |
| **avenues (4)** | avenue | 22.64 | 7817 | 11.3% | |

**Unused exit width: 0.0 of 123.8 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 1228.9 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 32.7%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 2325 | 3.4% | 2325 | 3.4% |
| straight +x+y (y wing) 1 | straight | yes | 1896 | 2.7% | 1822 | 2.6% |
| straight +x+y (y wing) 2 | straight | yes | 1710 | 2.5% | 1701 | 2.5% |
| straight +x+y (y wing) 3 | straight | yes | 1080 | 1.6% | 1072 | 1.5% |
| straight +x+y (y wing) 4 | straight | yes | 662 | 1.0% | 645 | 0.9% |
| straight +x+y (x wing) 0 | straight | yes | 2358 | 3.4% | 2358 | 3.4% |
| straight +x+y (x wing) 1 | straight | yes | 1920 | 2.8% | 1810 | 2.6% |
| straight +x+y (x wing) 2 | straight | yes | 1647 | 2.4% | 1635 | 2.4% |
| straight +x+y (x wing) 3 | straight | yes | 1129 | 1.6% | 1107 | 1.6% |
| straight +x+y (x wing) 4 | straight | yes | 693 | 1.0% | 679 | 1.0% |
| corner +x+y | corner | yes | 1995 | 2.9% | 712 | 1.0% |
| straight -x+y (y wing) 0 | straight | yes | 2355 | 3.4% | 2355 | 3.4% |
| straight -x+y (y wing) 1 | straight | yes | 1891 | 2.7% | 1797 | 2.6% |
| straight -x+y (y wing) 2 | straight | yes | 1557 | 2.2% | 1533 | 2.2% |
| straight -x+y (y wing) 3 | straight | yes | 1158 | 1.7% | 1135 | 1.6% |
| straight -x+y (y wing) 4 | straight | yes | 729 | 1.1% | 712 | 1.0% |
| straight -x+y (x wing) 0 | straight | yes | 2306 | 3.3% | 2306 | 3.3% |
| straight -x+y (x wing) 1 | straight | yes | 1863 | 2.7% | 1785 | 2.6% |
| straight -x+y (x wing) 2 | straight | yes | 1611 | 2.3% | 1571 | 2.3% |
| straight -x+y (x wing) 3 | straight | yes | 1143 | 1.6% | 1122 | 1.6% |
| straight -x+y (x wing) 4 | straight | yes | 809 | 1.2% | 797 | 1.1% |
| corner -x+y | corner | yes | 2106 | 3.0% | 754 | 1.1% |
| straight -x-y (y wing) 0 | straight | yes | 2306 | 3.3% | 2306 | 3.3% |
| straight -x-y (y wing) 1 | straight | yes | 1910 | 2.8% | 1839 | 2.7% |
| straight -x-y (y wing) 2 | straight | yes | 1703 | 2.5% | 1694 | 2.4% |
| straight -x-y (y wing) 3 | straight | yes | 1134 | 1.6% | 1125 | 1.6% |
| straight -x-y (y wing) 4 | straight | yes | 597 | 0.9% | 585 | 0.8% |
| straight -x-y (x wing) 0 | straight | yes | 2372 | 3.4% | 2372 | 3.4% |
| straight -x-y (x wing) 1 | straight | yes | 1914 | 2.8% | 1826 | 2.6% |
| straight -x-y (x wing) 2 | straight | yes | 1697 | 2.4% | 1693 | 2.4% |
| straight -x-y (x wing) 3 | straight | yes | 1096 | 1.6% | 1088 | 1.6% |
| straight -x-y (x wing) 4 | straight | yes | 657 | 0.9% | 640 | 0.9% |
| corner -x-y | corner | yes | 1931 | 2.8% | 698 | 1.0% |
| straight +x-y (y wing) 0 | straight | yes | 2367 | 3.4% | 2367 | 3.4% |
| straight +x-y (y wing) 1 | straight | yes | 1886 | 2.7% | 1818 | 2.6% |
| straight +x-y (y wing) 2 | straight | yes | 1611 | 2.3% | 1598 | 2.3% |
| straight +x-y (y wing) 3 | straight | yes | 1191 | 1.7% | 1186 | 1.7% |
| straight +x-y (y wing) 4 | straight | yes | 623 | 0.9% | 606 | 0.9% |
| straight +x-y (x wing) 0 | straight | yes | 2368 | 3.4% | 2368 | 3.4% |
| straight +x-y (x wing) 1 | straight | yes | 1879 | 2.7% | 1809 | 2.6% |
| straight +x-y (x wing) 2 | straight | yes | 1606 | 2.3% | 1589 | 2.3% |
| straight +x-y (x wing) 3 | straight | yes | 1221 | 1.8% | 1219 | 1.8% |
| straight +x-y (x wing) 4 | straight | yes | 632 | 0.9% | 617 | 0.9% |
| corner +x-y | corner | yes | 1969 | 2.8% | 691 | 1.0% |
| **straight (40)** | | | 61612 | | 60612 | 87.4% |
| **corner (4)** | | | 8001 | | 2855 | 4.1% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 5844, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 1976 | 60.2 | 935.6 | 0.29 | 0.75 | 0.0% |
| -x | 1951 | 60.2 | 921.6 | 0.29 | 0.71 | 0.0% |
| +y | 1943 | 60.2 | 916.3 | 0.29 | 0.72 | 0.0% |
| -y | 1947 | 60.2 | 924.7 | 0.29 | 0.70 | 0.0% |
| door +x+y (y wall) 0 | 1711 | 0.9 | 1029.5 | 0.52 | 1.38 | 4.8% |
| door +x+y (y wall) 1 | 1919 | 0.9 | 1120.8 | 0.53 | 1.28 | 5.3% |
| door +x+y (y wall) 2 | 1742 | 0.7 | 1186.6 | 0.46 | 1.31 | 4.2% |
| door +x+y (y wall) 3 | 1198 | 0.9 | 1170.5 | 0.32 | 1.31 | 4.2% |
| door +x+y (y wall) 4 | 839 | 0.9 | 1159.5 | 0.23 | 1.25 | 5.1% |
| door +x+y (x wall) 0 | 1733 | 0.9 | 1033.0 | 0.52 | 1.44 | 4.8% |
| door +x+y (x wall) 1 | 1897 | 0.7 | 1171.9 | 0.51 | 1.25 | 4.2% |
| door +x+y (x wall) 2 | 1697 | 0.7 | 1187.6 | 0.45 | 1.31 | 5.0% |
| door +x+y (x wall) 3 | 1243 | 0.9 | 1185.7 | 0.33 | 1.28 | 4.2% |
| door +x+y (x wall) 4 | 846 | 1.0 | 1158.9 | 0.23 | 1.35 | 5.1% |
| door +x+y (corner) | 529 | 0.9 | 1115.6 | 0.15 | 0.85 | 0.0% |
| door -x+y (y wall) 0 | 1713 | 0.7 | 1023.9 | 0.52 | 1.35 | 4.9% |
| door -x+y (y wall) 1 | 1907 | 0.9 | 1113.1 | 0.53 | 1.38 | 4.5% |
| door -x+y (y wall) 2 | 1628 | 0.9 | 1138.1 | 0.45 | 1.25 | 5.2% |
| door -x+y (y wall) 3 | 1233 | 0.7 | 1144.2 | 0.34 | 1.28 | 4.3% |
| door -x+y (y wall) 4 | 885 | 0.9 | 1144.4 | 0.24 | 1.25 | 5.2% |
| door -x+y (x wall) 0 | 1705 | 0.9 | 974.9 | 0.55 | 1.38 | 5.1% |
| door -x+y (x wall) 1 | 1892 | 0.7 | 1083.9 | 0.54 | 1.35 | 5.5% |
| door -x+y (x wall) 2 | 1620 | 0.9 | 1121.0 | 0.45 | 1.31 | 4.4% |
| door -x+y (x wall) 3 | 1257 | 0.7 | 1146.3 | 0.34 | 1.35 | 5.2% |
| door -x+y (x wall) 4 | 976 | 0.9 | 1078.8 | 0.28 | 1.35 | 5.5% |
| door -x+y (corner) | 585 | 0.9 | 1027.2 | 0.18 | 0.88 | 1.9% |
| door -x-y (y wall) 0 | 1710 | 0.7 | 1049.3 | 0.51 | 1.38 | 4.7% |
| door -x-y (y wall) 1 | 1924 | 0.9 | 1083.0 | 0.55 | 1.31 | 4.6% |
| door -x-y (y wall) 2 | 1732 | 0.9 | 1154.0 | 0.47 | 1.35 | 4.3% |
| door -x-y (y wall) 3 | 1291 | 0.9 | 1182.7 | 0.34 | 1.38 | 5.0% |
| door -x-y (y wall) 4 | 747 | 1.0 | 1166.8 | 0.20 | 1.38 | 5.9% |
| door -x-y (x wall) 0 | 1721 | 0.7 | 1059.9 | 0.51 | 1.25 | 5.6% |
| door -x-y (x wall) 1 | 1930 | 0.7 | 1073.6 | 0.56 | 1.31 | 5.6% |
| door -x-y (x wall) 2 | 1742 | 0.9 | 1172.9 | 0.46 | 1.31 | 4.2% |
| door -x-y (x wall) 3 | 1199 | 0.7 | 1181.7 | 0.32 | 1.31 | 4.2% |
| door -x-y (x wall) 4 | 835 | 0.9 | 1199.2 | 0.22 | 1.35 | 5.0% |
| door -x-y (corner) | 538 | 1.0 | 1153.2 | 0.15 | 0.85 | 0.0% |
| door +x-y (y wall) 0 | 1725 | 0.9 | 1025.5 | 0.53 | 1.35 | 4.9% |
| door +x-y (y wall) 1 | 1924 | 1.0 | 1148.3 | 0.52 | 1.35 | 5.2% |
| door +x-y (y wall) 2 | 1685 | 0.7 | 1191.6 | 0.44 | 1.35 | 5.0% |
| door +x-y (y wall) 3 | 1315 | 0.9 | 1176.2 | 0.35 | 1.25 | 4.2% |
| door +x-y (y wall) 4 | 754 | 0.9 | 1118.9 | 0.21 | 1.31 | 5.3% |
| door +x-y (x wall) 0 | 1725 | 0.7 | 1025.3 | 0.53 | 1.31 | 4.9% |
| door +x-y (x wall) 1 | 1897 | 0.9 | 1216.7 | 0.49 | 1.28 | 4.9% |
| door +x-y (x wall) 2 | 1700 | 0.9 | 1218.4 | 0.44 | 1.31 | 4.9% |
| door +x-y (x wall) 3 | 1310 | 0.9 | 1206.0 | 0.34 | 1.41 | 4.1% |
| door +x-y (x wall) 4 | 783 | 0.9 | 1228.9 | 0.20 | 1.38 | 4.8% |
| door +x-y (corner) | 552 | 0.9 | 857.7 | 0.20 | 0.88 | 3.4% |

Mean flow / w J averaged over the doors 0.39, over the avenues 0.29.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 103.1 | 2325 | 1570 / 757 / 890 | 0.3 | 868.9 | 3.70 | 6.32 | 89% | 89% | 0% | 4.77 |
| straight +x+y (y wing) 1 | 1.20 | 81.5 | 1855 | 1822 / 0 / 166 | 0.7 | 1117.8 | 1.78 | 3.01 | 90% | 81% | 10% | 4.09 |
| straight +x+y (y wing) 2 | 1.20 | 61.0 | 1564 | 1701 / 0 / 28 | 0.7 | 1183.6 | 1.46 | 2.81 | 75% | 67% | 8% | 4.07 |
| straight +x+y (y wing) 3 | 1.20 | 39.4 | 935 | 1072 / 0 / 23 | 0.7 | 1167.5 | 0.94 | 2.11 | 47% | 41% | 6% | 3.78 |
| straight +x+y (y wing) 4 | 1.20 | 18.8 | 397 | 645 / 0 / 18 | 0.7 | 1156.5 | 0.57 | 2.11 | 20% | 17% | 3% | 3.85 |
| straight +x+y (x wing) 0 | 1.20 | 103.1 | 2358 | 1599 / 760 / 912 | 0.3 | 923.5 | 3.54 | 6.02 | 90% | 86% | 4% | 4.45 |
| straight +x+y (x wing) 1 | 1.20 | 81.5 | 1899 | 1810 / 0 / 233 | 0.7 | 1168.9 | 1.75 | 3.21 | 87% | 71% | 16% | 3.78 |
| straight +x+y (x wing) 2 | 1.20 | 61.0 | 1471 | 1635 / 0 / 159 | 0.7 | 1184.6 | 1.52 | 3.61 | 68% | 62% | 6% | 4.09 |
| straight +x+y (x wing) 3 | 1.20 | 39.4 | 966 | 1107 / 0 / 33 | 0.7 | 1182.7 | 0.96 | 2.31 | 49% | 40% | 8% | 3.66 |
| straight +x+y (x wing) 4 | 1.20 | 18.8 | 400 | 679 / 0 / 16 | 0.7 | 1156.0 | 0.60 | 2.41 | 17% | 17% | 0% | 4.16 |
| corner +x+y | 1.20 | 186.0 | 1696 | 405 / 307 / 1493 | 0.7 | 1132.7 | 1.95 | 5.02 | 92% | 75% | 18% | 2.82 |
| straight -x+y (y wing) 0 | 1.20 | 103.1 | 2355 | 1581 / 775 / 1083 | 0.2 | 922.1 | 3.73 | 6.22 | 90% | 85% | 5% | 4.42 |
| straight -x+y (y wing) 1 | 1.20 | 81.5 | 1881 | 1797 / 0 / 159 | 0.7 | 1110.1 | 1.76 | 3.31 | 90% | 79% | 11% | 4.00 |
| straight -x+y (y wing) 2 | 1.20 | 61.0 | 1457 | 1533 / 0 / 32 | 0.7 | 1135.1 | 1.38 | 2.61 | 75% | 63% | 12% | 3.64 |
| straight -x+y (y wing) 3 | 1.20 | 39.4 | 954 | 1135 / 0 / 25 | 0.7 | 1141.3 | 1.02 | 2.11 | 49% | 41% | 8% | 3.72 |
| straight -x+y (y wing) 4 | 1.20 | 18.8 | 404 | 712 / 0 / 17 | 0.7 | 1141.4 | 0.64 | 2.31 | 18% | 18% | 0% | 4.13 |
| straight -x+y (x wing) 0 | 1.20 | 103.1 | 2306 | 1576 / 730 / 804 | 0.2 | 903.4 | 3.44 | 6.62 | 90% | 86% | 4% | 4.64 |
| straight -x+y (x wing) 1 | 1.20 | 81.5 | 1845 | 1785 / 0 / 160 | 0.7 | 1080.9 | 1.80 | 3.01 | 76% | 76% | 0% | 4.70 |
| straight -x+y (x wing) 2 | 1.20 | 61.0 | 1548 | 1571 / 0 / 43 | 0.7 | 1118.0 | 1.44 | 2.51 | 81% | 68% | 12% | 3.89 |
| straight -x+y (x wing) 3 | 1.20 | 39.4 | 941 | 1122 / 0 / 24 | 0.7 | 1143.4 | 1.00 | 2.31 | 50% | 41% | 9% | 3.69 |
| straight -x+y (x wing) 4 | 1.20 | 18.8 | 395 | 797 / 0 / 15 | 0.7 | 1075.9 | 0.76 | 2.21 | 19% | 19% | 0% | 4.21 |
| corner -x+y | 1.20 | 186.0 | 1781 | 467 / 287 / 1398 | 0.7 | 1117.5 | 1.93 | 4.51 | 89% | 65% | 25% | 2.75 |
| straight -x-y (y wing) 0 | 1.20 | 103.1 | 2306 | 1562 / 744 / 753 | 0.7 | 881.2 | 3.47 | 6.22 | 89% | 88% | 1% | 4.70 |
| straight -x-y (y wing) 1 | 1.20 | 81.5 | 1874 | 1839 / 0 / 155 | 0.7 | 1080.2 | 1.85 | 2.91 | 91% | 84% | 6% | 4.26 |
| straight -x-y (y wing) 2 | 1.20 | 61.0 | 1545 | 1694 / 0 / 22 | 0.7 | 1151.1 | 1.49 | 2.01 | 74% | 67% | 7% | 4.08 |
| straight -x-y (y wing) 3 | 1.20 | 39.4 | 953 | 1125 / 0 / 11 | 0.7 | 1179.7 | 0.96 | 2.41 | 43% | 39% | 3% | 3.99 |
| straight -x-y (y wing) 4 | 1.20 | 18.8 | 395 | 585 / 0 / 18 | 0.7 | 1163.8 | 0.52 | 2.21 | 20% | 17% | 3% | 3.86 |
| straight -x-y (x wing) 0 | 1.20 | 103.1 | 2372 | 1591 / 781 / 856 | 0.3 | 896.4 | 3.60 | 6.22 | 91% | 88% | 3% | 4.43 |
| straight -x-y (x wing) 1 | 1.20 | 81.5 | 1901 | 1826 / 0 / 181 | 0.7 | 1070.6 | 1.88 | 3.61 | 87% | 81% | 6% | 4.27 |
| straight -x-y (x wing) 2 | 1.20 | 61.0 | 1469 | 1693 / 0 / 19 | 0.7 | 1170.0 | 1.46 | 2.21 | 69% | 62% | 8% | 3.83 |
| straight -x-y (x wing) 3 | 1.20 | 39.4 | 955 | 1088 / 0 / 61 | 0.7 | 1178.7 | 0.98 | 2.71 | 50% | 42% | 8% | 3.64 |
| straight -x-y (x wing) 4 | 1.20 | 18.8 | 417 | 640 / 0 / 18 | 0.7 | 1196.2 | 0.55 | 2.21 | 21% | 18% | 3% | 3.74 |
| corner -x-y | 1.20 | 186.0 | 1679 | 417 / 281 / 1372 | 0.7 | 1172.4 | 1.77 | 4.51 | 92% | 72% | 19% | 2.85 |
| straight +x-y (y wing) 0 | 1.20 | 103.1 | 2367 | 1596 / 771 / 955 | 0.5 | 923.3 | 3.60 | 5.82 | 90% | 86% | 4% | 4.51 |
| straight +x-y (y wing) 1 | 1.20 | 81.5 | 1859 | 1818 / 0 / 154 | 0.7 | 1145.3 | 1.72 | 3.31 | 91% | 77% | 14% | 3.92 |
| straight +x-y (y wing) 2 | 1.20 | 61.0 | 1498 | 1598 / 0 / 18 | 0.7 | 1188.7 | 1.36 | 2.11 | 73% | 61% | 12% | 3.58 |
| straight +x-y (y wing) 3 | 1.20 | 39.4 | 949 | 1186 / 0 / 14 | 0.7 | 1173.3 | 1.02 | 2.21 | 47% | 39% | 8% | 3.80 |
| straight +x-y (y wing) 4 | 1.20 | 18.8 | 407 | 606 / 0 / 21 | 0.7 | 1115.9 | 0.56 | 2.41 | 18% | 18% | 0% | 4.11 |
| straight +x-y (x wing) 0 | 1.20 | 103.1 | 2368 | 1583 / 785 / 871 | 0.2 | 912.7 | 3.55 | 6.12 | 90% | 86% | 4% | 4.51 |
| straight +x-y (x wing) 1 | 1.20 | 81.5 | 1865 | 1809 / 0 / 136 | 0.7 | 1213.7 | 1.60 | 3.91 | 86% | 73% | 13% | 3.98 |
| straight +x-y (x wing) 2 | 1.20 | 61.0 | 1485 | 1589 / 0 / 25 | 0.7 | 1215.4 | 1.33 | 2.31 | 73% | 58% | 15% | 3.69 |
| straight +x-y (x wing) 3 | 1.20 | 39.4 | 935 | 1219 / 0 / 8 | 0.7 | 1203.0 | 1.02 | 2.01 | 42% | 38% | 4% | 3.98 |
| straight +x-y (x wing) 4 | 1.20 | 18.8 | 401 | 617 / 0 / 65 | 0.7 | 1225.9 | 0.56 | 2.11 | 17% | 15% | 2% | 3.79 |
| corner +x-y | 1.20 | 186.0 | 1734 | 431 / 260 / 1387 | 0.7 | 1202.0 | 1.73 | 4.81 | 90% | 65% | 25% | 2.77 |

The last agent out (agent 48650, t100 1228.9 s): last gangway straight +x-y (x wing) 4, exit door +x-y (x wall) 4. The gangway that cleared last: straight +x-y (x wing) 4 at 1225.9 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 8804 | 7800.4 | 6.97 | 1214.4 / 1157.4 / 1076.0 | 1132.9 / 1121.2 / 1049.3 | 5569796.8 | 11394192 | 0.198 |
| gangway | 3792 | 3512.9 | 6.97 | 1214.4 / 1157.2 / 1074.5 | 1132.9 / 1121.2 / 1049.3 | 5540660.1 | 10444533 | 0.127 |
| walkway | 276 | 257.4 | 5.43 | 616.9 / 413.3 / 160.9 | 446.5 / 365.0 / 85.2 | 1288.5 | 118257 | 0.460 |
| avenue | 1920 | 1801.4 | 3.04 | 814.9 / 27.1 / 0.0 | 592.6 / 2.1 / 0.0 | 0.0 | 468543 | 1.333 |
| exit | 4 | 2.0 | 0.00 | 0.7 / 0.0 / 0.0 | 0.7 / 0.0 / 0.0 | 0.0 | 3 | 0.899 |
| concourse | 2812 | 2226.8 | 6.14 | 1196.0 / 116.7 / 54.2 | 987.7 / 81.5 / 41.1 | 27848.2 | 362856 | 0.697 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 25392 | 16030.4 | 7.74 | 1087.2 / 1072.4 / 1047.9 | 1079.2 / 1072.4 / 1041.4 | 6933347.7 | 17364637 | 0.029 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 208 x 208 from (-104, -104) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -48.5 | -48.5 | gangway | 1.00 | 5.69 | 1093.3 | 1091.4 | 1049.3 | 5879.7 | 0.008 |
| 2 | 34.5 | 34.5 | gangway | 1.00 | 5.91 | 1058.4 | 1046.8 | 1025.5 | 5877.1 | 0.006 |
| 3 | -50.5 | -50.5 | gangway | 1.00 | 5.89 | 1104.4 | 1100.7 | 1020.8 | 5861.1 | 0.013 |
| 4 | -49.5 | -49.5 | gangway | 0.99 | 5.91 | 1101.4 | 1094.4 | 1034.7 | 5758.1 | 0.013 |
| 5 | 38.5 | 38.5 | gangway | 1.00 | 6.08 | 1089.8 | 1087.9 | 981.8 | 5750.0 | 0.014 |
| 6 | -34.5 | -34.5 | gangway | 1.00 | 6.09 | 1022.7 | 1013.1 | 979.1 | 5730.5 | 0.009 |
| 7 | -46.5 | -46.5 | gangway | 1.00 | 5.56 | 1082.7 | 1076.7 | 1034.0 | 5688.9 | 0.005 |
| 8 | 35.5 | 35.5 | gangway | 1.00 | 5.75 | 1071.8 | 1069.9 | 1002.0 | 5593.6 | 0.009 |
| 9 | -47.5 | -47.5 | gangway | 1.00 | 5.74 | 1088.4 | 1085.8 | 990.8 | 5551.7 | 0.007 |
| 10 | -51.5 | -51.5 | gangway | 1.00 | 5.87 | 1113.1 | 1106.1 | 1019.9 | 5509.1 | 0.017 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 38.5 | -36.5 | seat row | 0.50 | 7.40 | 1065.2 | 1059.4 | 1038.1 | 3669.0 | 0.006 |
| 2 | 36.5 | -38.5 | seat row | 0.50 | 7.31 | 1066.9 | 1062.9 | 1041.4 | 3637.4 | 0.006 |
| 3 | 36.5 | 38.5 | seat row | 0.50 | 7.32 | 1051.4 | 1047.5 | 1029.2 | 3606.1 | 0.005 |
| 4 | -52.5 | -54.5 | seat row | 0.50 | 7.38 | 1007.6 | 1006.4 | 992.4 | 3568.6 | 0.007 |
| 5 | 38.5 | 36.5 | seat row | 0.50 | 7.48 | 1038.9 | 1025.5 | 1000.1 | 3534.4 | 0.005 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 7680; agent-steps of seated agents on another row's clearway: 1396665.

## Deposit check

Person-seconds deposited: 28765081.8, of them in excluded cells: 6253.044.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 6723698 overlapping pair-steps: p99 0.0029, max 0.1245 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0029 max 0.1245; venue-geometry 23: p99 0.0017 max 0.0017 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00769 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 62 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.61 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 3701 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
