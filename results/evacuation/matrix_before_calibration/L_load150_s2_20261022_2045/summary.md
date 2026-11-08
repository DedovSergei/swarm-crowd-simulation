# Experiment `L_load150_s2`

**Task 5.10 stage 4 (AMD 26.10.1): Task 5.8's model (the level spacing on the gangway inclines, --stair-flow off): venue L, 150% requested (seed 2)**

Venue L (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (4000 x 4000), cache key a2f3aaf59c2252b7, content hash 022d17b202313d70). 69311 agents (load 109.3%, requested 150%): every one of the 63424 seats and 5887 standing (spawnOvercrowdedCrowd, seed 2; below), buffer N = 131072, 6937 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 9627121 evaluations, 556155 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.09)** (the L venue's design capacity 63424, jam capacity 171923: 23822.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T20:45:06, 767.1 s wall.

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
| t90 | 4789 | 837.6 |
| t100 | 6937 | 1213.3 |

t_p: the step by which ceil(p x 69311) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 1939 | 89 | 60.2 | 925.6 | 23.7 | 61.7 | 59.6-69.6 |
| -x | 5.66 | 1937 | 85 | 60.2 | 928.1 | 23.7 | 60.6 | 59.6-69.6 |
| +y | 5.66 | 1953 | 84 | 60.2 | 939.6 | 23.5 | 55.3 | 59.6-69.6 |
| -y | 5.66 | 1964 | 90 | 60.2 | 923.5 | 24.1 | 59.5 | 59.8-69.8 |
| door +x+y (y wall) 0 | 2.30 | 1725 | 2724 | 0.9 | 1057.3 | 42.6 | 102.0 | 2.6-12.6 |
| door +x+y (y wall) 1 | 2.30 | 1965 | 2257 | 1.0 | 1213.3 | 42.3 | 112.5 | 4.2-14.2 |
| door +x+y (y wall) 2 | 2.30 | 1652 | 1713 | 0.7 | 1187.8 | 36.3 | 104.7 | 18.4-28.3 |
| door +x+y (y wall) 3 | 2.30 | 1223 | 1159 | 1.0 | 1181.1 | 27.0 | 104.7 | 6.8-16.8 |
| door +x+y (y wall) 4 | 2.30 | 841 | 640 | 0.9 | 1207.4 | 18.2 | 115.1 | 15.7-25.7 |
| door +x+y (x wall) 0 | 2.30 | 1717 | 2728 | 0.7 | 1054.0 | 42.5 | 115.1 | 17.1-27.1 |
| door +x+y (x wall) 1 | 2.30 | 1922 | 2255 | 0.9 | 1190.9 | 42.1 | 109.9 | 3.1-13.1 |
| door +x+y (x wall) 2 | 2.30 | 1692 | 1717 | 0.7 | 1199.5 | 36.8 | 107.3 | 4.2-14.2 |
| door +x+y (x wall) 3 | 2.30 | 1226 | 1163 | 0.9 | 1199.3 | 26.7 | 104.7 | 9.3-19.2 |
| door +x+y (x wall) 4 | 2.30 | 897 | 638 | 0.9 | 1154.7 | 20.3 | 115.1 | 16.3-26.2 |
| door +x+y (corner) | 2.30 | 523 | 245 | 0.9 | 1067.3 | 12.8 | 70.6 | 0.5-10.5 |
| door -x+y (y wall) 0 | 2.30 | 1714 | 2722 | 0.9 | 1030.6 | 43.4 | 112.5 | 28.7-38.7 |
| door -x+y (y wall) 1 | 2.30 | 1931 | 2252 | 0.7 | 1169.8 | 43.1 | 112.5 | 16.8-26.8 |
| door -x+y (y wall) 2 | 2.30 | 1698 | 1708 | 1.0 | 1199.2 | 37.0 | 104.7 | 3.0-12.9 |
| door -x+y (y wall) 3 | 2.30 | 1275 | 1168 | 1.0 | 1185.7 | 28.1 | 115.1 | 19.8-29.7 |
| door -x+y (y wall) 4 | 2.30 | 800 | 639 | 0.9 | 1124.8 | 18.6 | 115.1 | 11.4-21.3 |
| door -x+y (x wall) 0 | 2.30 | 1700 | 2723 | 0.7 | 1022.0 | 43.4 | 112.5 | 29.4-39.4 |
| door -x+y (x wall) 1 | 2.30 | 1931 | 2257 | 0.9 | 1159.3 | 43.5 | 104.7 | 24.5-34.5 |
| door -x+y (x wall) 2 | 2.30 | 1751 | 1710 | 0.7 | 1188.1 | 38.5 | 109.9 | 27.3-37.3 |
| door -x+y (x wall) 3 | 2.30 | 1218 | 1165 | 0.7 | 1188.5 | 26.7 | 104.7 | 0.5-10.5 |
| door -x+y (x wall) 4 | 2.30 | 824 | 640 | 0.7 | 1194.3 | 18.0 | 109.9 | 8.7-18.7 |
| door -x+y (corner) | 2.30 | 538 | 250 | 0.9 | 1083.9 | 13.0 | 73.3 | 73.1-83.1 |
| door -x-y (y wall) 0 | 2.30 | 1717 | 2729 | 1.0 | 1014.5 | 44.2 | 112.5 | 0.9-10.8 |
| door -x-y (y wall) 1 | 2.30 | 1917 | 2250 | 0.7 | 1130.2 | 44.3 | 120.4 | 18.0-28.0 |
| door -x-y (y wall) 2 | 2.30 | 1630 | 1711 | 0.7 | 1141.3 | 37.3 | 107.3 | 0.5-10.5 |
| door -x-y (y wall) 3 | 2.30 | 1329 | 1156 | 0.9 | 1167.3 | 29.7 | 107.3 | 0.7-10.7 |
| door -x-y (y wall) 4 | 2.30 | 832 | 639 | 0.7 | 1068.0 | 20.3 | 112.5 | 30.3-40.2 |
| door -x-y (x wall) 0 | 2.30 | 1704 | 2721 | 0.9 | 1012.2 | 43.9 | 107.3 | 2.4-12.4 |
| door -x-y (x wall) 1 | 2.30 | 1890 | 2252 | 0.9 | 1133.2 | 43.5 | 117.7 | 1.0-11.0 |
| door -x-y (x wall) 2 | 2.30 | 1675 | 1711 | 0.7 | 1164.9 | 37.5 | 112.5 | 1.6-11.5 |
| door -x-y (x wall) 3 | 2.30 | 1318 | 1165 | 0.7 | 1147.4 | 30.0 | 115.1 | 1.2-11.2 |
| door -x-y (x wall) 4 | 2.30 | 829 | 640 | 0.9 | 1090.4 | 19.8 | 104.7 | 0.7-10.7 |
| door -x-y (corner) | 2.30 | 524 | 259 | 0.7 | 1019.2 | 13.4 | 70.6 | 77.7-87.6 |
| door +x-y (y wall) 0 | 2.30 | 1716 | 2724 | 0.9 | 1011.1 | 44.3 | 112.5 | 9.3-19.2 |
| door +x-y (y wall) 1 | 2.30 | 1877 | 2253 | 0.9 | 1177.3 | 41.6 | 107.3 | 26.8-36.7 |
| door +x-y (y wall) 2 | 2.30 | 1636 | 1714 | 0.9 | 1142.0 | 37.4 | 104.7 | 43.2-53.2 |
| door +x-y (y wall) 3 | 2.30 | 1233 | 1159 | 1.0 | 1178.0 | 27.3 | 109.9 | 0.5-10.5 |
| door +x-y (y wall) 4 | 2.30 | 901 | 640 | 0.9 | 1183.9 | 19.9 | 107.3 | 1.4-11.4 |
| door +x-y (x wall) 0 | 2.30 | 1694 | 2728 | 0.9 | 1001.0 | 44.2 | 109.9 | 25.4-35.3 |
| door +x-y (x wall) 1 | 2.30 | 1900 | 2258 | 0.9 | 1171.0 | 42.4 | 109.9 | 6.8-16.8 |
| door +x-y (x wall) 2 | 2.30 | 1676 | 1714 | 0.7 | 1174.1 | 37.3 | 115.1 | 39.5-49.5 |
| door +x-y (x wall) 3 | 2.30 | 1262 | 1157 | 0.7 | 1156.0 | 28.5 | 109.9 | 22.0-32.0 |
| door +x-y (x wall) 4 | 2.30 | 864 | 646 | 0.9 | 1145.1 | 19.7 | 112.5 | 3.1-13.1 |
| door +x-y (corner) | 2.30 | 631 | 264 | 0.9 | 895.0 | 18.4 | 75.9 | 0.7-10.7 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (2.30 m; a corner door's: the gap between its wall ends, 2.30 m); agents are removed past the outer wall's outer face (92.71 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 1939 | 2.8% | 20.3% |
| -x | avenue | 5.66 | 1937 | 2.8% | 20.2% |
| +y | avenue | 5.66 | 1953 | 2.8% | 20.4% |
| -y | avenue | 5.66 | 1964 | 2.8% | 20.5% |
| door +x+y (y wall) 0 | door | 2.30 | 1725 | 2.5% | 44.4% |
| door +x+y (y wall) 1 | door | 2.30 | 1965 | 2.8% | 50.5% |
| door +x+y (y wall) 2 | door | 2.30 | 1652 | 2.4% | 42.5% |
| door +x+y (y wall) 3 | door | 2.30 | 1223 | 1.8% | 31.5% |
| door +x+y (y wall) 4 | door | 2.30 | 841 | 1.2% | 21.6% |
| door +x+y (x wall) 0 | door | 2.30 | 1717 | 2.5% | 44.2% |
| door +x+y (x wall) 1 | door | 2.30 | 1922 | 2.8% | 49.4% |
| door +x+y (x wall) 2 | door | 2.30 | 1692 | 2.4% | 43.5% |
| door +x+y (x wall) 3 | door | 2.30 | 1226 | 1.8% | 31.5% |
| door +x+y (x wall) 4 | door | 2.30 | 897 | 1.3% | 23.1% |
| door +x+y (corner) | door | 2.30 | 523 | 0.8% | 13.5% |
| door -x+y (y wall) 0 | door | 2.30 | 1714 | 2.5% | 44.1% |
| door -x+y (y wall) 1 | door | 2.30 | 1931 | 2.8% | 49.7% |
| door -x+y (y wall) 2 | door | 2.30 | 1698 | 2.4% | 43.7% |
| door -x+y (y wall) 3 | door | 2.30 | 1275 | 1.8% | 32.8% |
| door -x+y (y wall) 4 | door | 2.30 | 800 | 1.2% | 20.6% |
| door -x+y (x wall) 0 | door | 2.30 | 1700 | 2.5% | 43.7% |
| door -x+y (x wall) 1 | door | 2.30 | 1931 | 2.8% | 49.7% |
| door -x+y (x wall) 2 | door | 2.30 | 1751 | 2.5% | 45.0% |
| door -x+y (x wall) 3 | door | 2.30 | 1218 | 1.8% | 31.3% |
| door -x+y (x wall) 4 | door | 2.30 | 824 | 1.2% | 21.2% |
| door -x+y (corner) | door | 2.30 | 538 | 0.8% | 13.8% |
| door -x-y (y wall) 0 | door | 2.30 | 1717 | 2.5% | 44.2% |
| door -x-y (y wall) 1 | door | 2.30 | 1917 | 2.8% | 49.3% |
| door -x-y (y wall) 2 | door | 2.30 | 1630 | 2.4% | 41.9% |
| door -x-y (y wall) 3 | door | 2.30 | 1329 | 1.9% | 34.2% |
| door -x-y (y wall) 4 | door | 2.30 | 832 | 1.2% | 21.4% |
| door -x-y (x wall) 0 | door | 2.30 | 1704 | 2.5% | 43.8% |
| door -x-y (x wall) 1 | door | 2.30 | 1890 | 2.7% | 48.6% |
| door -x-y (x wall) 2 | door | 2.30 | 1675 | 2.4% | 43.1% |
| door -x-y (x wall) 3 | door | 2.30 | 1318 | 1.9% | 33.9% |
| door -x-y (x wall) 4 | door | 2.30 | 829 | 1.2% | 21.3% |
| door -x-y (corner) | door | 2.30 | 524 | 0.8% | 13.5% |
| door +x-y (y wall) 0 | door | 2.30 | 1716 | 2.5% | 44.1% |
| door +x-y (y wall) 1 | door | 2.30 | 1877 | 2.7% | 48.3% |
| door +x-y (y wall) 2 | door | 2.30 | 1636 | 2.4% | 42.1% |
| door +x-y (y wall) 3 | door | 2.30 | 1233 | 1.8% | 31.7% |
| door +x-y (y wall) 4 | door | 2.30 | 901 | 1.3% | 23.2% |
| door +x-y (x wall) 0 | door | 2.30 | 1694 | 2.4% | 43.6% |
| door +x-y (x wall) 1 | door | 2.30 | 1900 | 2.7% | 48.9% |
| door +x-y (x wall) 2 | door | 2.30 | 1676 | 2.4% | 43.1% |
| door +x-y (x wall) 3 | door | 2.30 | 1262 | 1.8% | 32.5% |
| door +x-y (x wall) 4 | door | 2.30 | 864 | 1.2% | 22.2% |
| door +x-y (corner) | door | 2.30 | 631 | 0.9% | 16.2% |
| **doors (44)** | door | 101.20 | 61518 | 88.8% | |
| **avenues (4)** | avenue | 22.64 | 7793 | 11.2% | |

**Unused exit width: 0.0 of 123.8 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 1213.3 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 33.1%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 2331 | 3.4% | 2331 | 3.4% |
| straight +x+y (y wing) 1 | straight | yes | 1935 | 2.8% | 1866 | 2.7% |
| straight +x+y (y wing) 2 | straight | yes | 1614 | 2.3% | 1603 | 2.3% |
| straight +x+y (y wing) 3 | straight | yes | 1079 | 1.6% | 1067 | 1.5% |
| straight +x+y (y wing) 4 | straight | yes | 698 | 1.0% | 686 | 1.0% |
| straight +x+y (x wing) 0 | straight | yes | 2359 | 3.4% | 2359 | 3.4% |
| straight +x+y (x wing) 1 | straight | yes | 1895 | 2.7% | 1823 | 2.6% |
| straight +x+y (x wing) 2 | straight | yes | 1618 | 2.3% | 1604 | 2.3% |
| straight +x+y (x wing) 3 | straight | yes | 1151 | 1.7% | 1135 | 1.6% |
| straight +x+y (x wing) 4 | straight | yes | 721 | 1.0% | 710 | 1.0% |
| corner +x+y | corner | yes | 1970 | 2.8% | 682 | 1.0% |
| straight -x+y (y wing) 0 | straight | yes | 2352 | 3.4% | 2352 | 3.4% |
| straight -x+y (y wing) 1 | straight | yes | 1927 | 2.8% | 1841 | 2.7% |
| straight -x+y (y wing) 2 | straight | yes | 1653 | 2.4% | 1642 | 2.4% |
| straight -x+y (y wing) 3 | straight | yes | 1134 | 1.6% | 1121 | 1.6% |
| straight -x+y (y wing) 4 | straight | yes | 662 | 1.0% | 647 | 0.9% |
| straight -x+y (x wing) 0 | straight | yes | 2311 | 3.3% | 2311 | 3.3% |
| straight -x+y (x wing) 1 | straight | yes | 1905 | 2.7% | 1833 | 2.6% |
| straight -x+y (x wing) 2 | straight | yes | 1683 | 2.4% | 1671 | 2.4% |
| straight -x+y (x wing) 3 | straight | yes | 1129 | 1.6% | 1115 | 1.6% |
| straight -x+y (x wing) 4 | straight | yes | 668 | 1.0% | 644 | 0.9% |
| corner -x+y | corner | yes | 1969 | 2.8% | 689 | 1.0% |
| straight -x-y (y wing) 0 | straight | yes | 2355 | 3.4% | 2355 | 3.4% |
| straight -x-y (y wing) 1 | straight | yes | 1895 | 2.7% | 1819 | 2.6% |
| straight -x-y (y wing) 2 | straight | yes | 1583 | 2.3% | 1564 | 2.3% |
| straight -x-y (y wing) 3 | straight | yes | 1194 | 1.7% | 1187 | 1.7% |
| straight -x-y (y wing) 4 | straight | yes | 705 | 1.0% | 686 | 1.0% |
| straight -x-y (x wing) 0 | straight | yes | 2323 | 3.4% | 2323 | 3.4% |
| straight -x-y (x wing) 1 | straight | yes | 1879 | 2.7% | 1794 | 2.6% |
| straight -x-y (x wing) 2 | straight | yes | 1638 | 2.4% | 1612 | 2.3% |
| straight -x-y (x wing) 3 | straight | yes | 1163 | 1.7% | 1161 | 1.7% |
| straight -x-y (x wing) 4 | straight | yes | 691 | 1.0% | 682 | 1.0% |
| corner -x-y | corner | yes | 1986 | 2.9% | 683 | 1.0% |
| straight +x-y (y wing) 0 | straight | yes | 2362 | 3.4% | 2362 | 3.4% |
| straight +x-y (y wing) 1 | straight | yes | 1870 | 2.7% | 1772 | 2.6% |
| straight +x-y (y wing) 2 | straight | yes | 1584 | 2.3% | 1557 | 2.2% |
| straight +x-y (y wing) 3 | straight | yes | 1157 | 1.7% | 1141 | 1.6% |
| straight +x-y (y wing) 4 | straight | yes | 730 | 1.1% | 711 | 1.0% |
| straight +x-y (x wing) 0 | straight | yes | 2315 | 3.3% | 2314 | 3.3% |
| straight +x-y (x wing) 1 | straight | yes | 1881 | 2.7% | 1794 | 2.6% |
| straight +x-y (x wing) 2 | straight | yes | 1642 | 2.4% | 1611 | 2.3% |
| straight +x-y (x wing) 3 | straight | yes | 1132 | 1.6% | 1121 | 1.6% |
| straight +x-y (x wing) 4 | straight | yes | 725 | 1.0% | 703 | 1.0% |
| corner +x-y | corner | yes | 2067 | 3.0% | 781 | 1.1% |
| **straight (40)** | | | 61649 | | 60630 | 87.5% |
| **corner (4)** | | | 7992 | | 2835 | 4.1% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 5846, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 1939 | 60.2 | 925.6 | 0.28 | 0.74 | 0.0% |
| -x | 1937 | 60.2 | 928.1 | 0.28 | 0.72 | 0.0% |
| +y | 1953 | 60.2 | 939.6 | 0.28 | 0.66 | 0.0% |
| -y | 1964 | 60.2 | 923.5 | 0.29 | 0.71 | 0.0% |
| door +x+y (y wall) 0 | 1725 | 0.9 | 1057.3 | 0.51 | 1.22 | 4.7% |
| door +x+y (y wall) 1 | 1965 | 1.0 | 1213.3 | 0.51 | 1.35 | 4.1% |
| door +x+y (y wall) 2 | 1652 | 0.7 | 1187.8 | 0.43 | 1.25 | 5.0% |
| door +x+y (y wall) 3 | 1223 | 1.0 | 1181.1 | 0.32 | 1.25 | 5.0% |
| door +x+y (y wall) 4 | 841 | 0.9 | 1207.4 | 0.22 | 1.38 | 4.9% |
| door +x+y (x wall) 0 | 1717 | 0.7 | 1054.0 | 0.51 | 1.38 | 4.7% |
| door +x+y (x wall) 1 | 1922 | 0.9 | 1190.9 | 0.50 | 1.31 | 4.2% |
| door +x+y (x wall) 2 | 1692 | 0.7 | 1199.5 | 0.44 | 1.28 | 5.0% |
| door +x+y (x wall) 3 | 1226 | 0.9 | 1199.3 | 0.32 | 1.25 | 5.0% |
| door +x+y (x wall) 4 | 897 | 0.9 | 1154.7 | 0.24 | 1.38 | 5.2% |
| door +x+y (corner) | 523 | 0.9 | 1067.3 | 0.15 | 0.85 | 0.9% |
| door -x+y (y wall) 0 | 1714 | 0.9 | 1030.6 | 0.52 | 1.35 | 4.8% |
| door -x+y (y wall) 1 | 1931 | 0.7 | 1169.8 | 0.52 | 1.35 | 4.2% |
| door -x+y (y wall) 2 | 1698 | 1.0 | 1199.2 | 0.44 | 1.25 | 5.0% |
| door -x+y (y wall) 3 | 1275 | 1.0 | 1185.7 | 0.34 | 1.38 | 4.2% |
| door -x+y (y wall) 4 | 800 | 0.9 | 1124.8 | 0.22 | 1.38 | 5.3% |
| door -x+y (x wall) 0 | 1700 | 0.7 | 1022.0 | 0.52 | 1.35 | 4.9% |
| door -x+y (x wall) 1 | 1931 | 0.9 | 1159.3 | 0.52 | 1.25 | 5.1% |
| door -x+y (x wall) 2 | 1751 | 0.7 | 1188.1 | 0.46 | 1.31 | 4.2% |
| door -x+y (x wall) 3 | 1218 | 0.7 | 1188.5 | 0.32 | 1.25 | 5.0% |
| door -x+y (x wall) 4 | 824 | 0.7 | 1194.3 | 0.22 | 1.31 | 5.0% |
| door -x+y (corner) | 538 | 0.9 | 1083.9 | 0.15 | 0.88 | 0.9% |
| door -x-y (y wall) 0 | 1717 | 1.0 | 1014.5 | 0.53 | 1.35 | 4.9% |
| door -x-y (y wall) 1 | 1917 | 0.7 | 1130.2 | 0.53 | 1.44 | 4.4% |
| door -x-y (y wall) 2 | 1630 | 0.7 | 1141.3 | 0.45 | 1.28 | 4.3% |
| door -x-y (y wall) 3 | 1329 | 0.9 | 1167.3 | 0.36 | 1.28 | 4.2% |
| door -x-y (y wall) 4 | 832 | 0.7 | 1068.0 | 0.24 | 1.35 | 5.6% |
| door -x-y (x wall) 0 | 1704 | 0.9 | 1012.2 | 0.53 | 1.28 | 4.9% |
| door -x-y (x wall) 1 | 1890 | 0.9 | 1133.2 | 0.52 | 1.41 | 5.3% |
| door -x-y (x wall) 2 | 1675 | 0.7 | 1164.9 | 0.45 | 1.35 | 4.3% |
| door -x-y (x wall) 3 | 1318 | 0.7 | 1147.4 | 0.36 | 1.38 | 5.2% |
| door -x-y (x wall) 4 | 829 | 0.9 | 1090.4 | 0.24 | 1.25 | 5.5% |
| door -x-y (corner) | 524 | 0.7 | 1019.2 | 0.16 | 0.85 | 1.0% |
| door +x-y (y wall) 0 | 1716 | 0.9 | 1011.1 | 0.53 | 1.35 | 4.9% |
| door +x-y (y wall) 1 | 1877 | 0.9 | 1177.3 | 0.50 | 1.28 | 4.2% |
| door +x-y (y wall) 2 | 1636 | 0.9 | 1142.0 | 0.45 | 1.25 | 5.2% |
| door +x-y (y wall) 3 | 1233 | 1.0 | 1178.0 | 0.33 | 1.31 | 4.2% |
| door +x-y (y wall) 4 | 901 | 0.9 | 1183.9 | 0.24 | 1.28 | 5.0% |
| door +x-y (x wall) 0 | 1694 | 0.9 | 1001.0 | 0.53 | 1.31 | 5.0% |
| door +x-y (x wall) 1 | 1900 | 0.9 | 1171.0 | 0.51 | 1.31 | 5.1% |
| door +x-y (x wall) 2 | 1676 | 0.7 | 1174.1 | 0.45 | 1.38 | 4.2% |
| door +x-y (x wall) 3 | 1262 | 0.7 | 1156.0 | 0.34 | 1.31 | 4.3% |
| door +x-y (x wall) 4 | 864 | 0.9 | 1145.1 | 0.24 | 1.35 | 5.2% |
| door +x-y (corner) | 631 | 0.9 | 895.0 | 0.22 | 0.91 | 2.2% |

Mean flow / w J averaged over the doors 0.39, over the avenues 0.28.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 103.1 | 2331 | 1590 / 741 / 785 | 0.7 | 912.0 | 3.42 | 5.92 | 90% | 86% | 4% | 4.57 |
| straight +x+y (y wing) 1 | 1.20 | 81.5 | 1913 | 1866 / 0 / 150 | 0.7 | 1210.4 | 1.67 | 3.51 | 84% | 74% | 11% | 4.15 |
| straight +x+y (y wing) 2 | 1.20 | 61.0 | 1482 | 1603 / 0 / 14 | 0.7 | 1184.8 | 1.37 | 2.11 | 73% | 63% | 10% | 3.90 |
| straight +x+y (y wing) 3 | 1.20 | 39.4 | 938 | 1067 / 0 / 81 | 0.7 | 1178.2 | 0.97 | 3.11 | 53% | 39% | 14% | 3.35 |
| straight +x+y (y wing) 4 | 1.20 | 18.8 | 418 | 686 / 0 / 16 | 0.7 | 1204.4 | 0.58 | 2.21 | 17% | 17% | 0% | 4.24 |
| straight +x+y (x wing) 0 | 1.20 | 103.1 | 2359 | 1582 / 777 / 1068 | 0.2 | 920.5 | 3.72 | 6.32 | 89% | 84% | 5% | 4.44 |
| straight +x+y (x wing) 1 | 1.20 | 81.5 | 1879 | 1823 / 0 / 134 | 0.7 | 1188.0 | 1.65 | 3.11 | 89% | 75% | 14% | 4.00 |
| straight +x+y (x wing) 2 | 1.20 | 61.0 | 1492 | 1604 / 0 / 24 | 0.7 | 1196.5 | 1.36 | 2.11 | 74% | 62% | 12% | 3.84 |
| straight +x+y (x wing) 3 | 1.20 | 39.4 | 939 | 1135 / 0 / 17 | 0.7 | 1196.4 | 0.96 | 2.11 | 48% | 38% | 9% | 3.79 |
| straight +x+y (x wing) 4 | 1.20 | 18.8 | 397 | 710 / 0 / 15 | 0.7 | 1151.8 | 0.63 | 2.11 | 19% | 16% | 3% | 3.78 |
| corner +x+y | 1.20 | 186.0 | 1718 | 402 / 280 / 1406 | 0.7 | 1180.6 | 1.77 | 4.91 | 90% | 72% | 18% | 2.78 |
| straight -x+y (y wing) 0 | 1.20 | 103.1 | 2352 | 1579 / 773 / 991 | 0.2 | 888.7 | 3.76 | 5.72 | 89% | 89% | 0% | 4.54 |
| straight -x+y (y wing) 1 | 1.20 | 81.5 | 1903 | 1841 / 0 / 158 | 0.7 | 1166.8 | 1.71 | 3.01 | 92% | 74% | 18% | 3.88 |
| straight -x+y (y wing) 2 | 1.20 | 61.0 | 1474 | 1642 / 0 / 86 | 0.7 | 1196.2 | 1.45 | 3.21 | 70% | 65% | 5% | 3.84 |
| straight -x+y (y wing) 3 | 1.20 | 39.4 | 959 | 1121 / 0 / 19 | 0.7 | 1182.7 | 0.96 | 2.01 | 49% | 39% | 9% | 3.51 |
| straight -x+y (y wing) 4 | 1.20 | 18.8 | 407 | 647 / 0 / 40 | 0.7 | 1121.9 | 0.61 | 2.21 | 19% | 18% | 1% | 3.96 |
| straight -x+y (x wing) 0 | 1.20 | 103.1 | 2311 | 1564 / 747 / 834 | 0.2 | 884.5 | 3.56 | 5.82 | 90% | 88% | 2% | 4.70 |
| straight -x+y (x wing) 1 | 1.20 | 81.5 | 1872 | 1833 / 0 / 192 | 0.7 | 1156.3 | 1.75 | 3.71 | 91% | 78% | 13% | 3.96 |
| straight -x+y (x wing) 2 | 1.20 | 61.0 | 1551 | 1671 / 0 / 18 | 0.7 | 1185.2 | 1.43 | 2.21 | 73% | 64% | 9% | 4.09 |
| straight -x+y (x wing) 3 | 1.20 | 39.4 | 932 | 1115 / 0 / 18 | 0.7 | 1185.5 | 0.96 | 2.01 | 47% | 39% | 8% | 3.69 |
| straight -x+y (x wing) 4 | 1.20 | 18.8 | 420 | 644 / 0 / 25 | 0.7 | 1191.3 | 0.56 | 2.31 | 18% | 18% | 0% | 4.21 |
| corner -x+y | 1.20 | 186.0 | 1685 | 412 / 277 / 1426 | 0.7 | 1167.3 | 1.81 | 5.42 | 90% | 69% | 20% | 2.92 |
| straight -x-y (y wing) 0 | 1.20 | 103.1 | 2355 | 1582 / 774 / 873 | 0.3 | 900.8 | 3.59 | 5.92 | 89% | 87% | 2% | 4.56 |
| straight -x-y (y wing) 1 | 1.20 | 81.5 | 1868 | 1819 / 0 / 166 | 0.7 | 1127.3 | 1.76 | 3.11 | 89% | 76% | 13% | 3.97 |
| straight -x-y (y wing) 2 | 1.20 | 61.0 | 1476 | 1564 / 0 / 27 | 0.7 | 1138.3 | 1.40 | 2.51 | 76% | 63% | 12% | 3.89 |
| straight -x-y (y wing) 3 | 1.20 | 39.4 | 961 | 1187 / 0 / 10 | 0.7 | 1164.4 | 1.03 | 2.31 | 45% | 39% | 6% | 3.88 |
| straight -x-y (y wing) 4 | 1.20 | 18.8 | 405 | 686 / 0 / 27 | 0.7 | 1065.0 | 0.67 | 2.11 | 20% | 19% | 1% | 4.22 |
| straight -x-y (x wing) 0 | 1.20 | 103.1 | 2323 | 1576 / 748 / 832 | 0.7 | 914.6 | 3.45 | 6.12 | 90% | 86% | 4% | 4.51 |
| straight -x-y (x wing) 1 | 1.20 | 81.5 | 1862 | 1794 / 0 / 123 | 0.7 | 1130.2 | 1.70 | 2.91 | 89% | 77% | 12% | 3.99 |
| straight -x-y (x wing) 2 | 1.20 | 61.0 | 1552 | 1612 / 0 / 31 | 0.7 | 1161.9 | 1.41 | 2.41 | 78% | 66% | 12% | 3.70 |
| straight -x-y (x wing) 3 | 1.20 | 39.4 | 942 | 1161 / 0 / 8 | 0.7 | 1144.4 | 1.02 | 2.21 | 46% | 40% | 6% | 3.84 |
| straight -x-y (x wing) 4 | 1.20 | 18.8 | 402 | 682 / 0 / 18 | 0.7 | 1087.4 | 0.64 | 2.01 | 36% | 18% | 18% | 2.47 |
| corner -x-y | 1.20 | 186.0 | 1720 | 389 / 295 / 1368 | 0.7 | 1114.2 | 1.84 | 4.31 | 93% | 69% | 24% | 2.85 |
| straight +x-y (y wing) 0 | 1.20 | 103.1 | 2362 | 1591 / 773 / 971 | 0.3 | 918.4 | 3.63 | 5.92 | 89% | 85% | 4% | 4.48 |
| straight +x-y (y wing) 1 | 1.20 | 81.5 | 1858 | 1772 / 0 / 151 | 0.7 | 1174.3 | 1.64 | 3.81 | 86% | 75% | 11% | 3.98 |
| straight +x-y (y wing) 2 | 1.20 | 61.0 | 1479 | 1557 / 0 / 33 | 0.7 | 1139.0 | 1.40 | 2.11 | 74% | 64% | 10% | 3.74 |
| straight +x-y (y wing) 3 | 1.20 | 39.4 | 960 | 1141 / 0 / 26 | 0.7 | 1175.0 | 0.99 | 2.61 | 49% | 42% | 8% | 3.60 |
| straight +x-y (y wing) 4 | 1.20 | 18.8 | 409 | 711 / 0 / 30 | 0.7 | 1181.0 | 0.63 | 2.31 | 24% | 17% | 8% | 3.20 |
| straight +x-y (x wing) 0 | 1.20 | 103.1 | 2315 | 1565 / 750 / 779 | 0.5 | 910.0 | 3.40 | 5.52 | 90% | 86% | 4% | 4.52 |
| straight +x-y (x wing) 1 | 1.20 | 81.5 | 1846 | 1794 / 0 / 187 | 0.7 | 1168.0 | 1.70 | 3.21 | 86% | 72% | 14% | 3.91 |
| straight +x-y (x wing) 2 | 1.20 | 61.0 | 1560 | 1611 / 0 / 58 | 0.7 | 1171.2 | 1.43 | 2.61 | 75% | 67% | 8% | 4.01 |
| straight +x-y (x wing) 3 | 1.20 | 39.4 | 939 | 1121 / 0 / 15 | 0.7 | 1153.0 | 0.99 | 2.01 | 50% | 40% | 10% | 3.55 |
| straight +x-y (x wing) 4 | 1.20 | 18.8 | 396 | 703 / 0 / 25 | 0.7 | 1142.1 | 0.64 | 2.31 | 17% | 17% | 1% | 4.05 |
| corner +x-y | 1.20 | 186.0 | 1743 | 491 / 290 / 1382 | 0.7 | 1157.0 | 1.87 | 4.31 | 90% | 63% | 26% | 2.71 |

The last agent out (agent 823, t100 1213.3 s): last gangway straight +x+y (y wing) 1, exit door +x+y (y wall) 1. The gangway that cleared last: straight +x+y (y wing) 1 at 1210.4 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 8804 | 7800.4 | 7.07 | 1198.6 / 1145.5 / 1072.0 | 1112.8 / 1100.3 / 1049.6 | 5613280.2 | 11398143 | 0.198 |
| gangway | 3792 | 3512.9 | 7.07 | 1197.2 / 1145.3 / 1070.3 | 1112.8 / 1100.3 / 1049.6 | 5583881.9 | 10447457 | 0.127 |
| walkway | 276 | 257.4 | 5.48 | 635.3 / 435.5 / 119.8 | 466.8 / 352.6 / 66.8 | 933.9 | 120110 | 0.452 |
| avenue | 1920 | 1801.4 | 3.05 | 816.3 / 38.8 / 0.0 | 609.7 / 1.9 / 0.0 | 0.0 | 467113 | 1.333 |
| exit | 4 | 2.0 | 0.00 | 0.7 / 0.0 / 0.0 | 0.7 / 0.0 / 0.0 | 0.0 | 3 | 0.908 |
| concourse | 2812 | 2226.8 | 6.19 | 1181.5 / 113.2 / 59.1 | 1001.5 / 82.9 / 51.4 | 28464.4 | 363459 | 0.693 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 25392 | 16030.4 | 7.78 | 1088.3 / 1071.3 / 1061.9 | 1072.2 / 1071.3 / 1056.6 | 6922212.1 | 17317911 | 0.029 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 208 x 208 from (-104, -104) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 34.5 | 34.5 | gangway | 1.00 | 5.87 | 1094.7 | 1083.9 | 1041.0 | 5785.0 | 0.010 |
| 2 | 35.5 | -35.5 | gangway | 1.00 | 5.72 | 1071.5 | 1061.7 | 999.6 | 5613.5 | 0.012 |
| 3 | -34.5 | 34.5 | gangway | 1.00 | 5.57 | 1087.4 | 1077.6 | 1043.8 | 5602.4 | 0.004 |
| 4 | -37.5 | 37.5 | gangway | 0.99 | 5.86 | 1097.0 | 1093.0 | 992.1 | 5558.1 | 0.014 |
| 5 | 35.5 | 35.5 | gangway | 1.00 | 5.64 | 1098.4 | 1093.5 | 1029.7 | 5545.3 | 0.008 |
| 6 | -47.5 | 47.5 | gangway | 1.00 | 5.88 | 1034.7 | 1014.8 | 966.5 | 5506.8 | 0.015 |
| 7 | 34.5 | -34.5 | gangway | 1.00 | 5.74 | 1064.7 | 1052.2 | 997.1 | 5502.7 | 0.011 |
| 8 | -38.5 | -38.5 | gangway | 1.00 | 5.88 | 1068.3 | 1059.4 | 943.3 | 5455.1 | 0.022 |
| 9 | -39.5 | 39.5 | gangway | 1.00 | 5.74 | 1104.7 | 1100.3 | 979.3 | 5440.2 | 0.023 |
| 10 | 38.5 | 38.5 | gangway | 1.00 | 5.90 | 1107.0 | 1093.5 | 1002.0 | 5436.1 | 0.019 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -36.5 | 38.5 | seat row | 0.50 | 7.26 | 1071.8 | 1071.3 | 1050.5 | 3717.1 | 0.006 |
| 2 | 36.5 | 38.5 | seat row | 0.50 | 7.46 | 1072.2 | 1068.9 | 1056.6 | 3715.4 | 0.005 |
| 3 | -38.5 | 36.5 | seat row | 0.50 | 7.25 | 1055.0 | 1050.8 | 1027.1 | 3630.8 | 0.004 |
| 4 | 35.5 | 38.5 | seat row | 0.50 | 7.07 | 1062.7 | 1054.3 | 1022.2 | 3573.4 | 0.004 |
| 5 | 38.5 | -36.5 | seat row | 0.50 | 7.22 | 1024.6 | 1022.5 | 1008.2 | 3537.6 | 0.007 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 7643; agent-steps of seated agents on another row's clearway: 1129872.

## Deposit check

Person-seconds deposited: 28722317.8, of them in excluded cells: 6263.472.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 6625094 overlapping pair-steps: p99 0.0030, max 0.1294 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0030 max 0.1294; venue-geometry 15: p99 0.0010 max 0.0010 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00755 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 64 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.47 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 3726 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
