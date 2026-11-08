# Experiment `L_load150_s7`

**Task 5.11 stage 1 (gridlock robustness, default model, AMD 26.10.1): venue L, the achievable maximum 109.28% (150% requested, seed 7)**

Venue L (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (4000 x 4000), cache key a2f3aaf59c2252b7, content hash 022d17b202313d70). 69311 agents (load 109.3%, requested 150%): every one of the 63424 seats and 5887 standing (spawnOvercrowdedCrowd, seed 7; below), buffer N = 131072, 8706 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 12276838 evaluations, 664177 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.09)** (the L venue's design capacity 63424, jam capacity 171923: 23822.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `15aa31e8667e4a9417fde7884d907d1832c5e2d6`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-23T18:22:11, 1228.2 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Spawn (overcrowding)

| | |
|---|---|
| seated | 63424 (every seat) |
| standing | **5887** (requested round((1.50 - 1) x 63424) = 31712; at most 5887 = floor(2.5 p/m^2 x 2355.0 m^2)) |
| standing floor | walkway + rear concourse, 2355.0 m^2 |
| standing on the walkway / concourse / gangways | 636 / 5251 / 0 |
| **load** | **109.28%** of the seats (requested 150%; the floor takes no more: the achievable maximum) |
| standing crowd's mean density | 2.500 p/m^2 |
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 4.06, all circulation cells 4.06 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 7, 355594 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 2774 | 485.2 |
| t90 | 6188 | 1082.3 |
| t100 | 8706 | 1522.7 |

t_p: the step by which ceil(p x 69311) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 2224 | 86 | 60.2 | 1195.8 | 20.8 | 59.5 | 59.5-69.4 |
| -x | 5.66 | 2246 | 89 | 60.2 | 1185.9 | 21.1 | 62.7 | 59.8-69.8 |
| +y | 5.66 | 2202 | 85 | 60.2 | 1198.5 | 20.5 | 60.6 | 60.0-70.0 |
| -y | 5.66 | 2172 | 82 | 60.2 | 1198.6 | 20.2 | 59.5 | 59.8-69.8 |
| door +x+y (y wall) 0 | 2.30 | 1663 | 2733 | 0.9 | 1301.7 | 33.3 | 117.7 | 21.5-31.5 |
| door +x+y (y wall) 1 | 2.30 | 1850 | 2255 | 0.9 | 1459.1 | 33.1 | 107.3 | 12.9-22.9 |
| door +x+y (y wall) 2 | 2.30 | 1704 | 1715 | 0.9 | 1522.7 | 29.2 | 109.9 | 14.9-24.8 |
| door +x+y (y wall) 3 | 2.30 | 1199 | 1164 | 0.7 | 1521.0 | 20.6 | 109.9 | 29.9-39.9 |
| door +x+y (y wall) 4 | 2.30 | 890 | 635 | 0.7 | 1461.7 | 15.9 | 115.1 | 3.3-13.3 |
| door +x+y (x wall) 0 | 2.30 | 1669 | 2731 | 0.9 | 1200.4 | 36.3 | 112.5 | 28.7-38.7 |
| door +x+y (x wall) 1 | 2.30 | 1855 | 2248 | 0.9 | 1454.2 | 33.3 | 107.3 | 18.7-28.7 |
| door +x+y (x wall) 2 | 2.30 | 1613 | 1707 | 0.7 | 1499.1 | 28.1 | 107.3 | 2.8-12.8 |
| door +x+y (x wall) 3 | 2.30 | 1247 | 1153 | 0.9 | 1517.7 | 21.4 | 109.9 | 1.9-11.9 |
| door +x+y (x wall) 4 | 2.30 | 860 | 640 | 0.7 | 1463.1 | 15.3 | 107.3 | 0.5-10.5 |
| door +x+y (corner) | 2.30 | 588 | 247 | 0.7 | 1354.0 | 11.3 | 75.9 | 0.5-10.5 |
| door -x+y (y wall) 0 | 2.30 | 1668 | 2734 | 0.9 | 1184.5 | 36.8 | 109.9 | 32.0-42.0 |
| door -x+y (y wall) 1 | 2.30 | 1848 | 2259 | 0.7 | 1472.7 | 32.7 | 115.1 | 34.8-44.8 |
| door -x+y (y wall) 2 | 2.30 | 1694 | 1709 | 0.9 | 1508.2 | 29.3 | 115.1 | 25.5-35.5 |
| door -x+y (y wall) 3 | 2.30 | 1323 | 1163 | 0.7 | 1479.9 | 23.3 | 117.7 | 30.8-40.8 |
| door -x+y (y wall) 4 | 2.30 | 758 | 640 | 1.0 | 1501.2 | 13.2 | 107.3 | 40.4-50.4 |
| door -x+y (x wall) 0 | 2.30 | 1647 | 2729 | 0.7 | 1310.1 | 32.8 | 112.5 | 33.9-43.9 |
| door -x+y (x wall) 1 | 2.30 | 1824 | 2258 | 0.9 | 1443.3 | 33.0 | 115.1 | 6.3-16.3 |
| door -x+y (x wall) 2 | 2.30 | 1744 | 1705 | 0.9 | 1500.2 | 30.3 | 112.5 | 12.4-22.4 |
| door -x+y (x wall) 3 | 2.30 | 1261 | 1161 | 0.9 | 1455.4 | 22.6 | 115.1 | 23.8-33.8 |
| door -x+y (x wall) 4 | 2.30 | 810 | 644 | 0.7 | 1457.1 | 14.5 | 104.7 | 16.8-26.8 |
| door -x+y (corner) | 2.30 | 552 | 251 | 1.0 | 1355.4 | 10.6 | 68.0 | 0.5-10.5 |
| door -x-y (y wall) 0 | 2.30 | 1635 | 2725 | 1.0 | 1154.2 | 37.0 | 107.3 | 17.5-27.5 |
| door -x-y (y wall) 1 | 2.30 | 1822 | 2254 | 0.9 | 1400.3 | 34.0 | 115.1 | 18.0-28.0 |
| door -x-y (y wall) 2 | 2.30 | 1710 | 1711 | 0.9 | 1475.0 | 30.3 | 112.5 | 22.9-32.9 |
| door -x-y (y wall) 3 | 2.30 | 1249 | 1162 | 0.7 | 1467.3 | 22.2 | 112.5 | 13.8-23.8 |
| door -x-y (y wall) 4 | 2.30 | 829 | 640 | 0.9 | 1402.8 | 15.4 | 117.7 | 9.4-19.4 |
| door -x-y (x wall) 0 | 2.30 | 1670 | 2731 | 0.9 | 1189.5 | 36.6 | 112.5 | 25.7-35.7 |
| door -x-y (x wall) 1 | 2.30 | 1793 | 2254 | 1.0 | 1415.3 | 33.1 | 107.3 | 29.0-39.0 |
| door -x-y (x wall) 2 | 2.30 | 1695 | 1712 | 1.0 | 1468.2 | 30.1 | 109.9 | 21.3-31.3 |
| door -x-y (x wall) 3 | 2.30 | 1255 | 1157 | 0.9 | 1478.0 | 22.2 | 115.1 | 23.6-33.6 |
| door -x-y (x wall) 4 | 2.30 | 853 | 633 | 0.7 | 1448.2 | 15.4 | 109.9 | 0.3-10.3 |
| door -x-y (corner) | 2.30 | 545 | 244 | 0.9 | 1271.6 | 11.2 | 68.0 | 0.7-10.7 |
| door +x-y (y wall) 0 | 2.30 | 1680 | 2734 | 0.7 | 1176.4 | 37.3 | 107.3 | 0.5-10.5 |
| door +x-y (y wall) 1 | 2.30 | 1837 | 2257 | 0.9 | 1431.8 | 33.5 | 112.5 | 16.6-26.6 |
| door +x-y (y wall) 2 | 2.30 | 1725 | 1715 | 0.9 | 1490.9 | 30.2 | 104.7 | 1.0-11.0 |
| door +x-y (y wall) 3 | 2.30 | 1236 | 1163 | 0.9 | 1488.1 | 21.7 | 112.5 | 0.7-10.7 |
| door +x-y (y wall) 4 | 2.30 | 828 | 643 | 0.7 | 1446.7 | 14.9 | 112.5 | 25.9-35.9 |
| door +x-y (x wall) 0 | 2.30 | 1655 | 2730 | 0.7 | 1298.3 | 33.3 | 112.5 | 20.5-30.4 |
| door +x-y (x wall) 1 | 2.30 | 1857 | 2261 | 0.9 | 1461.0 | 33.2 | 112.5 | 14.3-24.3 |
| door +x-y (x wall) 2 | 2.30 | 1710 | 1705 | 0.9 | 1482.7 | 30.1 | 112.5 | 27.6-37.6 |
| door +x-y (x wall) 3 | 2.30 | 1203 | 1163 | 0.9 | 1476.2 | 21.3 | 109.9 | 16.4-26.4 |
| door +x-y (x wall) 4 | 2.30 | 882 | 644 | 0.7 | 1466.6 | 15.7 | 112.5 | 21.2-31.1 |
| door +x-y (corner) | 2.30 | 531 | 250 | 0.9 | 1144.8 | 12.1 | 73.3 | 0.3-10.3 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (2.30 m; a corner door's: the gap between its wall ends, 2.30 m); agents are removed past the outer wall's outer face (92.71 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 2224 | 3.2% | 18.5% |
| -x | avenue | 5.66 | 2246 | 3.2% | 18.7% |
| +y | avenue | 5.66 | 2202 | 3.2% | 18.3% |
| -y | avenue | 5.66 | 2172 | 3.1% | 18.1% |
| door +x+y (y wall) 0 | door | 2.30 | 1663 | 2.4% | 34.1% |
| door +x+y (y wall) 1 | door | 2.30 | 1850 | 2.7% | 37.9% |
| door +x+y (y wall) 2 | door | 2.30 | 1704 | 2.5% | 34.9% |
| door +x+y (y wall) 3 | door | 2.30 | 1199 | 1.7% | 24.6% |
| door +x+y (y wall) 4 | door | 2.30 | 890 | 1.3% | 18.2% |
| door +x+y (x wall) 0 | door | 2.30 | 1669 | 2.4% | 34.2% |
| door +x+y (x wall) 1 | door | 2.30 | 1855 | 2.7% | 38.0% |
| door +x+y (x wall) 2 | door | 2.30 | 1613 | 2.3% | 33.1% |
| door +x+y (x wall) 3 | door | 2.30 | 1247 | 1.8% | 25.6% |
| door +x+y (x wall) 4 | door | 2.30 | 860 | 1.2% | 17.6% |
| door +x+y (corner) | door | 2.30 | 588 | 0.8% | 12.0% |
| door -x+y (y wall) 0 | door | 2.30 | 1668 | 2.4% | 34.2% |
| door -x+y (y wall) 1 | door | 2.30 | 1848 | 2.7% | 37.9% |
| door -x+y (y wall) 2 | door | 2.30 | 1694 | 2.4% | 34.7% |
| door -x+y (y wall) 3 | door | 2.30 | 1323 | 1.9% | 27.1% |
| door -x+y (y wall) 4 | door | 2.30 | 758 | 1.1% | 15.5% |
| door -x+y (x wall) 0 | door | 2.30 | 1647 | 2.4% | 33.8% |
| door -x+y (x wall) 1 | door | 2.30 | 1824 | 2.6% | 37.4% |
| door -x+y (x wall) 2 | door | 2.30 | 1744 | 2.5% | 35.7% |
| door -x+y (x wall) 3 | door | 2.30 | 1261 | 1.8% | 25.8% |
| door -x+y (x wall) 4 | door | 2.30 | 810 | 1.2% | 16.6% |
| door -x+y (corner) | door | 2.30 | 552 | 0.8% | 11.3% |
| door -x-y (y wall) 0 | door | 2.30 | 1635 | 2.4% | 33.5% |
| door -x-y (y wall) 1 | door | 2.30 | 1822 | 2.6% | 37.3% |
| door -x-y (y wall) 2 | door | 2.30 | 1710 | 2.5% | 35.0% |
| door -x-y (y wall) 3 | door | 2.30 | 1249 | 1.8% | 25.6% |
| door -x-y (y wall) 4 | door | 2.30 | 829 | 1.2% | 17.0% |
| door -x-y (x wall) 0 | door | 2.30 | 1670 | 2.4% | 34.2% |
| door -x-y (x wall) 1 | door | 2.30 | 1793 | 2.6% | 36.7% |
| door -x-y (x wall) 2 | door | 2.30 | 1695 | 2.4% | 34.7% |
| door -x-y (x wall) 3 | door | 2.30 | 1255 | 1.8% | 25.7% |
| door -x-y (x wall) 4 | door | 2.30 | 853 | 1.2% | 17.5% |
| door -x-y (corner) | door | 2.30 | 545 | 0.8% | 11.2% |
| door +x-y (y wall) 0 | door | 2.30 | 1680 | 2.4% | 34.4% |
| door +x-y (y wall) 1 | door | 2.30 | 1837 | 2.7% | 37.6% |
| door +x-y (y wall) 2 | door | 2.30 | 1725 | 2.5% | 35.3% |
| door +x-y (y wall) 3 | door | 2.30 | 1236 | 1.8% | 25.3% |
| door +x-y (y wall) 4 | door | 2.30 | 828 | 1.2% | 17.0% |
| door +x-y (x wall) 0 | door | 2.30 | 1655 | 2.4% | 33.9% |
| door +x-y (x wall) 1 | door | 2.30 | 1857 | 2.7% | 38.1% |
| door +x-y (x wall) 2 | door | 2.30 | 1710 | 2.5% | 35.0% |
| door +x-y (x wall) 3 | door | 2.30 | 1203 | 1.7% | 24.7% |
| door +x-y (x wall) 4 | door | 2.30 | 882 | 1.3% | 18.1% |
| door +x-y (corner) | door | 2.30 | 531 | 0.8% | 10.9% |
| **doors (44)** | door | 101.20 | 60467 | 87.2% | |
| **avenues (4)** | avenue | 22.64 | 8844 | 12.8% | |

**Unused exit width: 0.0 of 123.8 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 1522.7 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 26.4%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 2343 | 3.4% | 2343 | 3.4% |
| straight +x+y (y wing) 1 | straight | yes | 1864 | 2.7% | 1741 | 2.5% |
| straight +x+y (y wing) 2 | straight | yes | 1644 | 2.4% | 1632 | 2.4% |
| straight +x+y (y wing) 3 | straight | yes | 1115 | 1.6% | 1096 | 1.6% |
| straight +x+y (y wing) 4 | straight | yes | 716 | 1.0% | 703 | 1.0% |
| straight +x+y (x wing) 0 | straight | yes | 2377 | 3.4% | 2377 | 3.4% |
| straight +x+y (x wing) 1 | straight | yes | 1890 | 2.7% | 1744 | 2.5% |
| straight +x+y (x wing) 2 | straight | yes | 1587 | 2.3% | 1574 | 2.3% |
| straight +x+y (x wing) 3 | straight | yes | 1135 | 1.6% | 1112 | 1.6% |
| straight +x+y (x wing) 4 | straight | yes | 705 | 1.0% | 686 | 1.0% |
| corner +x+y | corner | yes | 2133 | 3.1% | 856 | 1.2% |
| straight -x+y (y wing) 0 | straight | yes | 2376 | 3.4% | 2376 | 3.4% |
| straight -x+y (y wing) 1 | straight | yes | 1878 | 2.7% | 1726 | 2.5% |
| straight -x+y (y wing) 2 | straight | yes | 1601 | 2.3% | 1589 | 2.3% |
| straight -x+y (y wing) 3 | straight | yes | 1204 | 1.7% | 1199 | 1.7% |
| straight -x+y (y wing) 4 | straight | yes | 635 | 0.9% | 627 | 0.9% |
| straight -x+y (x wing) 0 | straight | yes | 2328 | 3.4% | 2328 | 3.4% |
| straight -x+y (x wing) 1 | straight | yes | 1862 | 2.7% | 1706 | 2.5% |
| straight -x+y (x wing) 2 | straight | yes | 1657 | 2.4% | 1646 | 2.4% |
| straight -x+y (x wing) 3 | straight | yes | 1136 | 1.6% | 1134 | 1.6% |
| straight -x+y (x wing) 4 | straight | yes | 695 | 1.0% | 677 | 1.0% |
| corner -x+y | corner | yes | 2141 | 3.1% | 857 | 1.2% |
| straight -x-y (y wing) 0 | straight | yes | 2321 | 3.3% | 2321 | 3.3% |
| straight -x-y (y wing) 1 | straight | yes | 1885 | 2.7% | 1705 | 2.5% |
| straight -x-y (y wing) 2 | straight | yes | 1625 | 2.3% | 1600 | 2.3% |
| straight -x-y (y wing) 3 | straight | yes | 1160 | 1.7% | 1153 | 1.7% |
| straight -x-y (y wing) 4 | straight | yes | 692 | 1.0% | 674 | 1.0% |
| straight -x-y (x wing) 0 | straight | yes | 2349 | 3.4% | 2349 | 3.4% |
| straight -x-y (x wing) 1 | straight | yes | 1880 | 2.7% | 1676 | 2.4% |
| straight -x-y (x wing) 2 | straight | yes | 1600 | 2.3% | 1590 | 2.3% |
| straight -x-y (x wing) 3 | straight | yes | 1165 | 1.7% | 1158 | 1.7% |
| straight -x-y (x wing) 4 | straight | yes | 724 | 1.0% | 705 | 1.0% |
| corner -x-y | corner | yes | 2245 | 3.2% | 936 | 1.4% |
| straight +x-y (y wing) 0 | straight | yes | 2392 | 3.5% | 2392 | 3.5% |
| straight +x-y (y wing) 1 | straight | yes | 1873 | 2.7% | 1717 | 2.5% |
| straight +x-y (y wing) 2 | straight | yes | 1629 | 2.4% | 1622 | 2.3% |
| straight +x-y (y wing) 3 | straight | yes | 1157 | 1.7% | 1147 | 1.7% |
| straight +x-y (y wing) 4 | straight | yes | 662 | 1.0% | 651 | 0.9% |
| straight +x-y (x wing) 0 | straight | yes | 2340 | 3.4% | 2340 | 3.4% |
| straight +x-y (x wing) 1 | straight | yes | 1872 | 2.7% | 1738 | 2.5% |
| straight +x-y (x wing) 2 | straight | yes | 1634 | 2.4% | 1627 | 2.3% |
| straight +x-y (x wing) 3 | straight | yes | 1114 | 1.6% | 1104 | 1.6% |
| straight +x-y (x wing) 4 | straight | yes | 716 | 1.0% | 704 | 1.0% |
| corner +x-y | corner | yes | 2106 | 3.0% | 824 | 1.2% |
| **straight (40)** | | | 61538 | | 59989 | 86.6% |
| **corner (4)** | | | 8625 | | 3473 | 5.0% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 5849, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 2224 | 60.2 | 1195.8 | 0.25 | 0.71 | 0.0% |
| -x | 2246 | 60.2 | 1185.9 | 0.25 | 0.75 | 0.0% |
| +y | 2202 | 60.2 | 1198.5 | 0.25 | 0.72 | 0.0% |
| -y | 2172 | 60.2 | 1198.6 | 0.24 | 0.71 | 0.0% |
| door +x+y (y wall) 0 | 1663 | 0.9 | 1301.7 | 0.40 | 1.41 | 3.8% |
| door +x+y (y wall) 1 | 1850 | 0.9 | 1459.1 | 0.40 | 1.28 | 3.4% |
| door +x+y (y wall) 2 | 1704 | 0.9 | 1522.7 | 0.35 | 1.31 | 3.3% |
| door +x+y (y wall) 3 | 1199 | 0.7 | 1521.0 | 0.25 | 1.31 | 3.3% |
| door +x+y (y wall) 4 | 890 | 0.7 | 1461.7 | 0.19 | 1.38 | 3.4% |
| door +x+y (x wall) 0 | 1669 | 0.9 | 1200.4 | 0.43 | 1.35 | 4.1% |
| door +x+y (x wall) 1 | 1855 | 0.9 | 1454.2 | 0.40 | 1.28 | 3.4% |
| door +x+y (x wall) 2 | 1613 | 0.7 | 1499.1 | 0.34 | 1.28 | 3.3% |
| door +x+y (x wall) 3 | 1247 | 0.9 | 1517.7 | 0.26 | 1.31 | 3.3% |
| door +x+y (x wall) 4 | 860 | 0.7 | 1463.1 | 0.18 | 1.28 | 3.4% |
| door +x+y (corner) | 588 | 0.7 | 1354.0 | 0.14 | 0.91 | 1.5% |
| door -x+y (y wall) 0 | 1668 | 0.9 | 1184.5 | 0.44 | 1.31 | 3.4% |
| door -x+y (y wall) 1 | 1848 | 0.7 | 1472.7 | 0.39 | 1.38 | 3.4% |
| door -x+y (y wall) 2 | 1694 | 0.9 | 1508.2 | 0.35 | 1.38 | 3.3% |
| door -x+y (y wall) 3 | 1323 | 0.7 | 1479.9 | 0.28 | 1.41 | 3.4% |
| door -x+y (y wall) 4 | 758 | 1.0 | 1501.2 | 0.16 | 1.28 | 3.3% |
| door -x+y (x wall) 0 | 1647 | 0.7 | 1310.1 | 0.39 | 1.35 | 3.8% |
| door -x+y (x wall) 1 | 1824 | 0.9 | 1443.3 | 0.39 | 1.38 | 3.4% |
| door -x+y (x wall) 2 | 1744 | 0.9 | 1500.2 | 0.36 | 1.35 | 2.6% |
| door -x+y (x wall) 3 | 1261 | 0.9 | 1455.4 | 0.27 | 1.38 | 3.4% |
| door -x+y (x wall) 4 | 810 | 0.7 | 1457.1 | 0.17 | 1.25 | 4.1% |
| door -x+y (corner) | 552 | 1.0 | 1355.4 | 0.13 | 0.81 | 0.0% |
| door -x-y (y wall) 0 | 1635 | 1.0 | 1154.2 | 0.44 | 1.28 | 4.3% |
| door -x-y (y wall) 1 | 1822 | 0.9 | 1400.3 | 0.41 | 1.38 | 3.5% |
| door -x-y (y wall) 2 | 1710 | 0.9 | 1475.0 | 0.36 | 1.35 | 3.4% |
| door -x-y (y wall) 3 | 1249 | 0.7 | 1467.3 | 0.27 | 1.35 | 3.4% |
| door -x-y (y wall) 4 | 829 | 0.9 | 1402.8 | 0.18 | 1.41 | 3.5% |
| door -x-y (x wall) 0 | 1670 | 0.9 | 1189.5 | 0.44 | 1.35 | 4.2% |
| door -x-y (x wall) 1 | 1793 | 1.0 | 1415.3 | 0.40 | 1.28 | 3.5% |
| door -x-y (x wall) 2 | 1695 | 1.0 | 1468.2 | 0.36 | 1.31 | 3.4% |
| door -x-y (x wall) 3 | 1255 | 0.9 | 1478.0 | 0.27 | 1.38 | 3.4% |
| door -x-y (x wall) 4 | 853 | 0.7 | 1448.2 | 0.18 | 1.31 | 3.4% |
| door -x-y (corner) | 545 | 0.9 | 1271.6 | 0.13 | 0.81 | 0.0% |
| door +x-y (y wall) 0 | 1680 | 0.7 | 1176.4 | 0.45 | 1.28 | 4.2% |
| door +x-y (y wall) 1 | 1837 | 0.9 | 1431.8 | 0.40 | 1.35 | 3.5% |
| door +x-y (y wall) 2 | 1725 | 0.9 | 1490.9 | 0.36 | 1.25 | 4.0% |
| door +x-y (y wall) 3 | 1236 | 0.9 | 1488.1 | 0.26 | 1.35 | 3.3% |
| door +x-y (y wall) 4 | 828 | 0.7 | 1446.7 | 0.18 | 1.35 | 3.4% |
| door +x-y (x wall) 0 | 1655 | 0.7 | 1298.3 | 0.40 | 1.35 | 3.8% |
| door +x-y (x wall) 1 | 1857 | 0.9 | 1461.0 | 0.40 | 1.35 | 3.4% |
| door +x-y (x wall) 2 | 1710 | 0.9 | 1482.7 | 0.36 | 1.35 | 2.7% |
| door +x-y (x wall) 3 | 1203 | 0.9 | 1476.2 | 0.25 | 1.31 | 3.4% |
| door +x-y (x wall) 4 | 882 | 0.7 | 1466.6 | 0.19 | 1.35 | 3.4% |
| door +x-y (corner) | 531 | 0.9 | 1144.8 | 0.14 | 0.88 | 1.7% |

Mean flow / w J averaged over the doors 0.31, over the avenues 0.25.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 103.1 | 2343 | 1536 / 807 / 990 | 0.2 | 1156.8 | 2.88 | 5.52 | 91% | 87% | 4% | 4.42 |
| straight +x+y (y wing) 1 | 1.20 | 81.5 | 1827 | 1741 / 0 / 190 | 0.7 | 1456.1 | 1.33 | 2.61 | 93% | 73% | 20% | 3.68 |
| straight +x+y (y wing) 2 | 1.20 | 61.0 | 1559 | 1632 / 0 / 17 | 0.7 | 1519.8 | 1.09 | 1.60 | 79% | 67% | 12% | 3.73 |
| straight +x+y (y wing) 3 | 1.20 | 39.4 | 932 | 1096 / 0 / 24 | 0.7 | 1518.0 | 0.74 | 1.71 | 50% | 41% | 9% | 3.60 |
| straight +x+y (y wing) 4 | 1.20 | 18.8 | 400 | 703 / 0 / 15 | 0.7 | 1458.7 | 0.49 | 1.81 | 18% | 16% | 2% | 3.83 |
| straight +x+y (x wing) 0 | 1.20 | 103.1 | 2377 | 1548 / 829 / 1154 | 0.3 | 1197.4 | 2.95 | 5.02 | 92% | 85% | 7% | 4.27 |
| straight +x+y (x wing) 1 | 1.20 | 81.5 | 1865 | 1744 / 0 / 188 | 0.7 | 1451.2 | 1.33 | 2.51 | 92% | 75% | 16% | 3.78 |
| straight +x+y (x wing) 2 | 1.20 | 61.0 | 1478 | 1574 / 0 / 15 | 0.7 | 1496.2 | 1.06 | 1.71 | 77% | 66% | 12% | 3.68 |
| straight +x+y (x wing) 3 | 1.20 | 39.4 | 947 | 1112 / 0 / 31 | 0.7 | 1514.7 | 0.75 | 2.01 | 45% | 41% | 5% | 3.79 |
| straight +x+y (x wing) 4 | 1.20 | 18.8 | 392 | 686 / 0 / 21 | 0.7 | 1460.1 | 0.48 | 1.71 | 18% | 16% | 2% | 3.89 |
| corner +x+y | 1.20 | 186.0 | 1744 | 465 / 391 / 1334 | 0.7 | 1467.8 | 1.49 | 4.21 | 93% | 57% | 36% | 2.50 |
| straight -x+y (y wing) 0 | 1.20 | 103.1 | 2376 | 1551 / 825 / 1142 | 0.3 | 1181.5 | 2.98 | 5.22 | 92% | 87% | 5% | 4.24 |
| straight -x+y (y wing) 1 | 1.20 | 81.5 | 1858 | 1726 / 0 / 200 | 0.7 | 1469.7 | 1.31 | 2.41 | 91% | 71% | 20% | 3.61 |
| straight -x+y (y wing) 2 | 1.20 | 61.0 | 1488 | 1589 / 0 / 14 | 0.7 | 1505.2 | 1.07 | 1.91 | 75% | 64% | 11% | 3.67 |
| straight -x+y (y wing) 3 | 1.20 | 39.4 | 947 | 1199 / 0 / 6 | 0.7 | 1476.9 | 0.82 | 1.60 | 47% | 40% | 7% | 3.73 |
| straight -x+y (y wing) 4 | 1.20 | 18.8 | 395 | 627 / 0 / 15 | 0.7 | 1498.3 | 0.43 | 1.91 | 28% | 16% | 12% | 2.70 |
| straight -x+y (x wing) 0 | 1.20 | 103.1 | 2328 | 1529 / 800 / 964 | 0.3 | 1195.7 | 2.75 | 5.52 | 92% | 85% | 8% | 4.33 |
| straight -x+y (x wing) 1 | 1.20 | 81.5 | 1830 | 1706 / 0 / 217 | 0.7 | 1440.4 | 1.34 | 2.21 | 92% | 70% | 21% | 3.68 |
| straight -x+y (x wing) 2 | 1.20 | 61.0 | 1560 | 1646 / 0 / 17 | 0.7 | 1497.2 | 1.11 | 1.60 | 78% | 68% | 11% | 3.80 |
| straight -x+y (x wing) 3 | 1.20 | 39.4 | 926 | 1134 / 0 / 5 | 0.7 | 1452.4 | 0.78 | 1.81 | 49% | 39% | 10% | 3.68 |
| straight -x+y (x wing) 4 | 1.20 | 18.8 | 408 | 677 / 0 / 31 | 0.7 | 1454.2 | 0.49 | 1.60 | 19% | 16% | 3% | 3.78 |
| corner -x+y | 1.20 | 186.0 | 1749 | 425 / 432 / 1342 | 0.7 | 1474.3 | 1.49 | 2.91 | 92% | 61% | 30% | 2.68 |
| straight -x-y (y wing) 0 | 1.20 | 103.1 | 2321 | 1528 / 794 / 923 | 0.2 | 1151.2 | 2.82 | 4.91 | 92% | 88% | 4% | 4.44 |
| straight -x-y (y wing) 1 | 1.20 | 81.5 | 1851 | 1705 / 0 / 246 | 0.7 | 1397.3 | 1.40 | 2.51 | 93% | 69% | 24% | 3.59 |
| straight -x-y (y wing) 2 | 1.20 | 61.0 | 1543 | 1600 / 0 / 28 | 0.7 | 1472.0 | 1.11 | 1.71 | 78% | 68% | 11% | 3.85 |
| straight -x-y (y wing) 3 | 1.20 | 39.4 | 939 | 1153 / 0 / 17 | 0.7 | 1464.3 | 0.80 | 1.60 | 51% | 39% | 12% | 3.62 |
| straight -x-y (y wing) 4 | 1.20 | 18.8 | 405 | 674 / 0 / 27 | 0.7 | 1399.8 | 0.50 | 1.71 | 19% | 17% | 2% | 3.83 |
| straight -x-y (x wing) 0 | 1.20 | 103.1 | 2349 | 1553 / 796 / 877 | 0.2 | 1186.6 | 2.72 | 4.61 | 92% | 86% | 6% | 4.25 |
| straight -x-y (x wing) 1 | 1.20 | 81.5 | 1866 | 1676 / 0 / 253 | 0.7 | 1412.4 | 1.37 | 2.11 | 93% | 70% | 23% | 3.56 |
| straight -x-y (x wing) 2 | 1.20 | 61.0 | 1484 | 1590 / 0 / 19 | 0.7 | 1465.2 | 1.10 | 2.21 | 77% | 65% | 12% | 3.73 |
| straight -x-y (x wing) 3 | 1.20 | 39.4 | 946 | 1158 / 0 / 11 | 0.7 | 1475.0 | 0.79 | 1.71 | 52% | 40% | 12% | 3.44 |
| straight -x-y (x wing) 4 | 1.20 | 18.8 | 397 | 705 / 0 / 19 | 0.7 | 1445.3 | 0.50 | 1.81 | 19% | 17% | 1% | 3.82 |
| corner -x-y | 1.20 | 186.0 | 1766 | 425 / 511 / 1378 | 0.7 | 1425.0 | 1.62 | 3.31 | 94% | 65% | 29% | 2.65 |
| straight +x-y (y wing) 0 | 1.20 | 103.1 | 2392 | 1558 / 835 / 1187 | 0.3 | 1173.4 | 3.05 | 5.32 | 92% | 88% | 4% | 4.26 |
| straight +x-y (y wing) 1 | 1.20 | 81.5 | 1857 | 1717 / 0 / 231 | 0.7 | 1428.8 | 1.36 | 2.41 | 93% | 70% | 23% | 3.59 |
| straight +x-y (y wing) 2 | 1.20 | 61.0 | 1488 | 1622 / 0 / 12 | 0.7 | 1487.9 | 1.10 | 1.81 | 73% | 63% | 9% | 3.88 |
| straight +x-y (y wing) 3 | 1.20 | 39.4 | 950 | 1147 / 0 / 16 | 0.7 | 1485.1 | 0.78 | 1.81 | 48% | 42% | 6% | 3.67 |
| straight +x-y (y wing) 4 | 1.20 | 18.8 | 411 | 651 / 0 / 22 | 0.7 | 1443.7 | 0.47 | 1.71 | 20% | 18% | 2% | 3.88 |
| straight +x-y (x wing) 0 | 1.20 | 103.1 | 2340 | 1530 / 810 / 947 | 0.2 | 1164.0 | 2.82 | 4.71 | 91% | 87% | 4% | 4.33 |
| straight +x-y (x wing) 1 | 1.20 | 81.5 | 1841 | 1738 / 0 / 197 | 0.7 | 1458.0 | 1.33 | 2.41 | 92% | 71% | 21% | 3.61 |
| straight +x-y (x wing) 2 | 1.20 | 61.0 | 1540 | 1627 / 0 / 12 | 0.7 | 1479.7 | 1.11 | 1.91 | 79% | 68% | 11% | 3.74 |
| straight +x-y (x wing) 3 | 1.20 | 39.4 | 936 | 1104 / 0 / 15 | 0.7 | 1473.2 | 0.76 | 1.60 | 61% | 40% | 21% | 3.01 |
| straight +x-y (x wing) 4 | 1.20 | 18.8 | 396 | 704 / 0 / 19 | 0.7 | 1463.6 | 0.49 | 1.91 | 21% | 16% | 5% | 3.39 |
| corner +x-y | 1.20 | 186.0 | 1715 | 405 / 419 / 1344 | 0.7 | 1439.7 | 1.51 | 3.81 | 94% | 75% | 19% | 2.68 |

The last agent out (agent 8851, t100 1522.7 s): last gangway straight +x+y (y wing) 2, exit door +x+y (y wall) 2. The gangway that cleared last: straight +x+y (y wing) 2 at 1519.8 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 8804 | 7800.4 | 7.10 | 1514.9 / 1426.4 / 1378.3 | 1430.7 / 1416.9 / 1354.0 | 7317695.7 | 13843924 | 0.167 |
| gangway | 3792 | 3512.9 | 7.10 | 1513.3 / 1426.2 / 1376.7 | 1430.7 / 1416.9 / 1354.0 | 7291111.1 | 12881598 | 0.101 |
| walkway | 276 | 257.4 | 5.29 | 800.4 / 454.2 / 23.3 | 439.9 / 181.9 / 12.6 | 175.0 | 90593 | 0.682 |
| avenue | 1920 | 1801.4 | 3.51 | 826.1 / 60.7 / 0.0 | 622.0 / 2.4 / 0.0 | 0.0 | 530059 | 1.334 |
| exit | 4 | 2.0 | 0.00 | 0.7 / 0.2 / 0.0 | 0.7 / 0.2 / 0.0 | 0.0 | 3 | 0.890 |
| concourse | 2812 | 2226.8 | 6.03 | 1446.7 / 76.1 / 50.9 | 1066.4 / 74.9 / 43.9 | 26409.5 | 341671 | 0.713 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 25392 | 16030.4 | 7.86 | 1384.7 / 1367.2 / 1354.3 | 1374.4 / 1367.2 / 1349.9 | 9225507.8 | 22750939 | 0.022 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 208 x 208 from (-104, -104) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 34.5 | -34.5 | gangway | 1.00 | 5.86 | 1383.0 | 1371.6 | 1338.9 | 7464.2 | 0.008 |
| 2 | 36.5 | 36.5 | gangway | 1.00 | 5.75 | 1416.7 | 1412.7 | 1354.0 | 7378.8 | 0.007 |
| 3 | -35.5 | -35.5 | gangway | 1.00 | 5.96 | 1370.9 | 1365.8 | 1278.9 | 7359.3 | 0.006 |
| 4 | 38.5 | -38.5 | gangway | 1.00 | 6.08 | 1395.2 | 1369.3 | 1241.3 | 7289.0 | 0.012 |
| 5 | -36.5 | 36.5 | gangway | 1.00 | 5.77 | 1394.4 | 1379.3 | 1304.5 | 7226.2 | 0.007 |
| 6 | 35.5 | -35.5 | gangway | 1.00 | 5.61 | 1388.6 | 1380.9 | 1301.7 | 7171.0 | 0.007 |
| 7 | 36.5 | -36.5 | gangway | 1.00 | 5.60 | 1391.2 | 1378.3 | 1317.7 | 7029.9 | 0.007 |
| 8 | 38.5 | 38.5 | gangway | 1.00 | 5.91 | 1424.4 | 1409.2 | 1306.2 | 7025.1 | 0.013 |
| 9 | -33.5 | 33.5 | gangway | 0.99 | 5.79 | 1372.8 | 1366.4 | 1304.8 | 6909.9 | 0.004 |
| 10 | 39.5 | 39.5 | gangway | 1.00 | 5.76 | 1430.7 | 1394.4 | 1233.6 | 6890.9 | 0.015 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 38.5 | 36.5 | seat row | 0.50 | 7.14 | 1370.7 | 1367.2 | 1349.9 | 4718.1 | 0.003 |
| 2 | -36.5 | 38.5 | seat row | 0.50 | 7.32 | 1344.5 | 1342.6 | 1322.8 | 4692.7 | 0.004 |
| 3 | 36.5 | 38.5 | seat row | 0.50 | 7.08 | 1368.3 | 1361.1 | 1346.4 | 4687.5 | 0.003 |
| 4 | 38.5 | -36.5 | seat row | 0.50 | 7.47 | 1340.0 | 1334.9 | 1312.5 | 4646.3 | 0.003 |
| 5 | -38.5 | 36.5 | seat row | 0.50 | 7.09 | 1347.0 | 1342.4 | 1322.1 | 4631.4 | 0.003 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 8500; agent-steps of seated agents on another row's clearway: 703652.

## Deposit check

Person-seconds deposited: 36601146.8, of them in excluded cells: 6283.570.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 9872016 overlapping pair-steps: p99 0.0019, max 0.0920 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0019 max 0.0920; venue-geometry 13: p99 0.0025 max 0.0025 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00770 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 62 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.44 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 3862 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
