# Experiment `L_load150_s4`

**Task 5.11 stage 1 (gridlock robustness, default model, AMD 26.10.1): venue L, the achievable maximum 109.28% (150% requested, seed 4)**

Venue L (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (4000 x 4000), cache key a2f3aaf59c2252b7, content hash 022d17b202313d70). 69311 agents (load 109.3%, requested 150%): every one of the 63424 seats and 5887 standing (spawnOvercrowdedCrowd, seed 4; below), buffer N = 131072, 8725 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 12335986 evaluations, 670629 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.09)** (the L venue's design capacity 63424, jam capacity 171923: 23822.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `15aa31e8667e4a9417fde7884d907d1832c5e2d6`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-23T17:46:29, 1135.7 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Spawn (overcrowding)

| | |
|---|---|
| seated | 63424 (every seat) |
| standing | **5887** (requested round((1.50 - 1) x 63424) = 31712; at most 5887 = floor(2.5 p/m^2 x 2355.0 m^2)) |
| standing floor | walkway + rear concourse, 2355.0 m^2 |
| standing on the walkway / concourse / gangways | 631 / 5256 / 0 |
| **load** | **109.28%** of the seats (requested 150%; the floor takes no more: the achievable maximum) |
| standing crowd's mean density | 2.500 p/m^2 |
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 4.02, all circulation cells 4.02 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 4, 353182 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 2787 | 487.5 |
| t90 | 6224 | 1088.6 |
| t100 | 8725 | 1526.1 |

t_p: the step by which ceil(p x 69311) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 2125 | 81 | 60.2 | 1217.5 | 19.5 | 59.5 | 60.0-70.0 |
| -x | 5.66 | 2169 | 85 | 60.2 | 1210.0 | 20.0 | 59.5 | 59.8-69.8 |
| +y | 5.66 | 2188 | 81 | 60.2 | 1198.6 | 20.4 | 58.5 | 60.0-70.0 |
| -y | 5.66 | 2213 | 90 | 60.2 | 1213.5 | 20.3 | 63.8 | 59.8-69.8 |
| door +x+y (y wall) 0 | 2.30 | 1648 | 2727 | 0.9 | 1206.3 | 35.7 | 107.3 | 0.7-10.7 |
| door +x+y (y wall) 1 | 2.30 | 1864 | 2252 | 0.9 | 1457.0 | 33.4 | 102.0 | 1.4-11.4 |
| door +x+y (y wall) 2 | 2.30 | 1789 | 1708 | 0.9 | 1522.2 | 30.7 | 112.5 | 20.8-30.8 |
| door +x+y (y wall) 3 | 2.30 | 1165 | 1162 | 0.7 | 1518.2 | 20.0 | 109.9 | 30.1-40.1 |
| door +x+y (y wall) 4 | 2.30 | 773 | 640 | 0.9 | 1488.3 | 13.6 | 112.5 | 35.9-45.8 |
| door +x+y (x wall) 0 | 2.30 | 1667 | 2732 | 0.9 | 1178.7 | 36.9 | 109.9 | 13.5-23.4 |
| door +x+y (x wall) 1 | 2.30 | 1835 | 2253 | 0.9 | 1438.8 | 33.3 | 109.9 | 28.7-38.7 |
| door +x+y (x wall) 2 | 2.30 | 1787 | 1711 | 0.7 | 1483.7 | 31.4 | 112.5 | 28.2-38.1 |
| door +x+y (x wall) 3 | 2.30 | 1220 | 1158 | 0.9 | 1521.0 | 20.9 | 109.9 | 15.4-25.4 |
| door +x+y (x wall) 4 | 2.30 | 784 | 643 | 0.9 | 1526.1 | 13.4 | 104.7 | 26.4-36.4 |
| door +x+y (corner) | 2.30 | 562 | 252 | 0.9 | 851.1 | 17.2 | 75.9 | 0.5-10.5 |
| door -x+y (y wall) 0 | 2.30 | 1657 | 2725 | 0.7 | 1256.9 | 34.4 | 112.5 | 30.3-40.2 |
| door -x+y (y wall) 1 | 2.30 | 1854 | 2252 | 0.9 | 1456.4 | 33.2 | 115.1 | 1.4-11.4 |
| door -x+y (y wall) 2 | 2.30 | 1685 | 1702 | 1.2 | 1465.9 | 30.0 | 112.5 | 10.7-20.6 |
| door -x+y (y wall) 3 | 2.30 | 1297 | 1162 | 0.7 | 1491.1 | 22.7 | 109.9 | 36.9-46.9 |
| door -x+y (y wall) 4 | 2.30 | 845 | 645 | 0.9 | 1465.5 | 15.0 | 107.3 | 1.4-11.4 |
| door -x+y (x wall) 0 | 2.30 | 1667 | 2726 | 0.9 | 1268.1 | 34.3 | 107.3 | 0.7-10.7 |
| door -x+y (x wall) 1 | 2.30 | 1841 | 2252 | 0.9 | 1439.0 | 33.4 | 109.9 | 4.4-14.3 |
| door -x+y (x wall) 2 | 2.30 | 1691 | 1708 | 0.7 | 1486.9 | 29.7 | 109.9 | 18.0-28.0 |
| door -x+y (x wall) 3 | 2.30 | 1268 | 1166 | 0.9 | 1492.0 | 22.2 | 112.5 | 24.1-34.1 |
| door -x+y (x wall) 4 | 2.30 | 860 | 643 | 0.7 | 1345.9 | 16.7 | 107.3 | 14.5-24.5 |
| door -x+y (corner) | 2.30 | 502 | 254 | 0.9 | 1136.7 | 11.5 | 75.9 | 0.7-10.7 |
| door -x-y (y wall) 0 | 2.30 | 1646 | 2733 | 0.9 | 1320.0 | 32.5 | 112.5 | 19.9-29.9 |
| door -x-y (y wall) 1 | 2.30 | 1827 | 2252 | 0.9 | 1465.7 | 32.5 | 112.5 | 24.1-34.1 |
| door -x-y (y wall) 2 | 2.30 | 1687 | 1709 | 0.7 | 1479.2 | 29.8 | 109.9 | 34.1-44.1 |
| door -x-y (y wall) 3 | 2.30 | 1323 | 1154 | 0.9 | 1472.4 | 23.5 | 109.9 | 0.7-10.7 |
| door -x-y (y wall) 4 | 2.30 | 774 | 643 | 0.9 | 1485.8 | 13.6 | 112.5 | 10.0-19.9 |
| door -x-y (x wall) 0 | 2.30 | 1704 | 2729 | 0.9 | 1269.6 | 35.0 | 109.9 | 16.3-26.2 |
| door -x-y (x wall) 1 | 2.30 | 1827 | 2246 | 0.9 | 1403.1 | 34.0 | 109.9 | 0.7-10.7 |
| door -x-y (x wall) 2 | 2.30 | 1695 | 1716 | 0.9 | 1475.0 | 30.0 | 112.5 | 1.4-11.4 |
| door -x-y (x wall) 3 | 2.30 | 1331 | 1165 | 0.7 | 1483.7 | 23.4 | 109.9 | 13.1-23.1 |
| door -x-y (x wall) 4 | 2.30 | 786 | 633 | 0.9 | 1486.5 | 13.8 | 109.9 | 20.3-30.3 |
| door -x-y (corner) | 2.30 | 556 | 245 | 0.9 | 1312.3 | 11.1 | 73.3 | 63.8-73.8 |
| door +x-y (y wall) 0 | 2.30 | 1700 | 2735 | 0.9 | 1283.8 | 34.6 | 112.5 | 19.1-29.0 |
| door +x-y (y wall) 1 | 2.30 | 1849 | 2257 | 0.7 | 1452.8 | 33.2 | 104.7 | 0.5-10.5 |
| door +x-y (y wall) 2 | 2.30 | 1719 | 1714 | 0.7 | 1465.2 | 30.6 | 109.9 | 0.5-10.5 |
| door +x-y (y wall) 3 | 2.30 | 1277 | 1169 | 0.7 | 1498.4 | 22.2 | 109.9 | 27.1-37.1 |
| door +x-y (y wall) 4 | 2.30 | 741 | 639 | 1.0 | 1480.6 | 13.1 | 109.9 | 9.6-19.6 |
| door +x-y (x wall) 0 | 2.30 | 1676 | 2735 | 0.9 | 1186.4 | 36.9 | 109.9 | 0.7-10.7 |
| door +x-y (x wall) 1 | 2.30 | 1856 | 2259 | 0.9 | 1448.9 | 33.4 | 107.3 | 23.4-33.4 |
| door +x-y (x wall) 2 | 2.30 | 1699 | 1714 | 0.9 | 1502.3 | 29.5 | 117.7 | 12.2-22.2 |
| door +x-y (x wall) 3 | 2.30 | 1304 | 1166 | 0.9 | 1498.3 | 22.7 | 115.1 | 13.1-23.1 |
| door +x-y (x wall) 4 | 2.30 | 837 | 640 | 0.9 | 1498.6 | 14.6 | 109.9 | 8.2-18.2 |
| door +x-y (corner) | 2.30 | 541 | 248 | 0.9 | 1310.6 | 10.8 | 70.6 | 9.1-19.1 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (2.30 m; a corner door's: the gap between its wall ends, 2.30 m); agents are removed past the outer wall's outer face (92.71 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 2125 | 3.1% | 17.7% |
| -x | avenue | 5.66 | 2169 | 3.1% | 18.0% |
| +y | avenue | 5.66 | 2188 | 3.2% | 18.2% |
| -y | avenue | 5.66 | 2213 | 3.2% | 18.4% |
| door +x+y (y wall) 0 | door | 2.30 | 1648 | 2.4% | 33.7% |
| door +x+y (y wall) 1 | door | 2.30 | 1864 | 2.7% | 38.1% |
| door +x+y (y wall) 2 | door | 2.30 | 1789 | 2.6% | 36.6% |
| door +x+y (y wall) 3 | door | 2.30 | 1165 | 1.7% | 23.8% |
| door +x+y (y wall) 4 | door | 2.30 | 773 | 1.1% | 15.8% |
| door +x+y (x wall) 0 | door | 2.30 | 1667 | 2.4% | 34.1% |
| door +x+y (x wall) 1 | door | 2.30 | 1835 | 2.6% | 37.5% |
| door +x+y (x wall) 2 | door | 2.30 | 1787 | 2.6% | 36.5% |
| door +x+y (x wall) 3 | door | 2.30 | 1220 | 1.8% | 24.9% |
| door +x+y (x wall) 4 | door | 2.30 | 784 | 1.1% | 16.0% |
| door +x+y (corner) | door | 2.30 | 562 | 0.8% | 11.5% |
| door -x+y (y wall) 0 | door | 2.30 | 1657 | 2.4% | 33.9% |
| door -x+y (y wall) 1 | door | 2.30 | 1854 | 2.7% | 37.9% |
| door -x+y (y wall) 2 | door | 2.30 | 1685 | 2.4% | 34.5% |
| door -x+y (y wall) 3 | door | 2.30 | 1297 | 1.9% | 26.5% |
| door -x+y (y wall) 4 | door | 2.30 | 845 | 1.2% | 17.3% |
| door -x+y (x wall) 0 | door | 2.30 | 1667 | 2.4% | 34.1% |
| door -x+y (x wall) 1 | door | 2.30 | 1841 | 2.7% | 37.6% |
| door -x+y (x wall) 2 | door | 2.30 | 1691 | 2.4% | 34.6% |
| door -x+y (x wall) 3 | door | 2.30 | 1268 | 1.8% | 25.9% |
| door -x+y (x wall) 4 | door | 2.30 | 860 | 1.2% | 17.6% |
| door -x+y (corner) | door | 2.30 | 502 | 0.7% | 10.3% |
| door -x-y (y wall) 0 | door | 2.30 | 1646 | 2.4% | 33.7% |
| door -x-y (y wall) 1 | door | 2.30 | 1827 | 2.6% | 37.4% |
| door -x-y (y wall) 2 | door | 2.30 | 1687 | 2.4% | 34.5% |
| door -x-y (y wall) 3 | door | 2.30 | 1323 | 1.9% | 27.1% |
| door -x-y (y wall) 4 | door | 2.30 | 774 | 1.1% | 15.8% |
| door -x-y (x wall) 0 | door | 2.30 | 1704 | 2.5% | 34.8% |
| door -x-y (x wall) 1 | door | 2.30 | 1827 | 2.6% | 37.4% |
| door -x-y (x wall) 2 | door | 2.30 | 1695 | 2.4% | 34.7% |
| door -x-y (x wall) 3 | door | 2.30 | 1331 | 1.9% | 27.2% |
| door -x-y (x wall) 4 | door | 2.30 | 786 | 1.1% | 16.1% |
| door -x-y (corner) | door | 2.30 | 556 | 0.8% | 11.4% |
| door +x-y (y wall) 0 | door | 2.30 | 1700 | 2.5% | 34.8% |
| door +x-y (y wall) 1 | door | 2.30 | 1849 | 2.7% | 37.8% |
| door +x-y (y wall) 2 | door | 2.30 | 1719 | 2.5% | 35.1% |
| door +x-y (y wall) 3 | door | 2.30 | 1277 | 1.8% | 26.1% |
| door +x-y (y wall) 4 | door | 2.30 | 741 | 1.1% | 15.2% |
| door +x-y (x wall) 0 | door | 2.30 | 1676 | 2.4% | 34.3% |
| door +x-y (x wall) 1 | door | 2.30 | 1856 | 2.7% | 38.0% |
| door +x-y (x wall) 2 | door | 2.30 | 1699 | 2.5% | 34.7% |
| door +x-y (x wall) 3 | door | 2.30 | 1304 | 1.9% | 26.7% |
| door +x-y (x wall) 4 | door | 2.30 | 837 | 1.2% | 17.1% |
| door +x-y (corner) | door | 2.30 | 541 | 0.8% | 11.1% |
| **doors (44)** | door | 101.20 | 60616 | 87.5% | |
| **avenues (4)** | avenue | 22.64 | 8695 | 12.5% | |

**Unused exit width: 0.0 of 123.8 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 1526.1 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 26.3%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 2352 | 3.4% | 2352 | 3.4% |
| straight +x+y (y wing) 1 | straight | yes | 1922 | 2.8% | 1750 | 2.5% |
| straight +x+y (y wing) 2 | straight | yes | 1694 | 2.4% | 1692 | 2.4% |
| straight +x+y (y wing) 3 | straight | yes | 1068 | 1.5% | 1061 | 1.5% |
| straight +x+y (y wing) 4 | straight | yes | 632 | 0.9% | 616 | 0.9% |
| straight +x+y (x wing) 0 | straight | yes | 2330 | 3.4% | 2330 | 3.4% |
| straight +x+y (x wing) 1 | straight | yes | 1894 | 2.7% | 1719 | 2.5% |
| straight +x+y (x wing) 2 | straight | yes | 1699 | 2.5% | 1698 | 2.4% |
| straight +x+y (x wing) 3 | straight | yes | 1101 | 1.6% | 1086 | 1.6% |
| straight +x+y (x wing) 4 | straight | yes | 657 | 0.9% | 647 | 0.9% |
| corner +x+y | corner | yes | 2146 | 3.1% | 916 | 1.3% |
| straight -x+y (y wing) 0 | straight | yes | 2338 | 3.4% | 2338 | 3.4% |
| straight -x+y (y wing) 1 | straight | yes | 1863 | 2.7% | 1744 | 2.5% |
| straight -x+y (y wing) 2 | straight | yes | 1624 | 2.3% | 1606 | 2.3% |
| straight -x+y (y wing) 3 | straight | yes | 1161 | 1.7% | 1152 | 1.7% |
| straight -x+y (y wing) 4 | straight | yes | 730 | 1.1% | 712 | 1.0% |
| straight -x+y (x wing) 0 | straight | yes | 2373 | 3.4% | 2373 | 3.4% |
| straight -x+y (x wing) 1 | straight | yes | 1857 | 2.7% | 1731 | 2.5% |
| straight -x+y (x wing) 2 | straight | yes | 1610 | 2.3% | 1603 | 2.3% |
| straight -x+y (x wing) 3 | straight | yes | 1160 | 1.7% | 1150 | 1.7% |
| straight -x+y (x wing) 4 | straight | yes | 701 | 1.0% | 701 | 1.0% |
| corner -x+y | corner | yes | 2118 | 3.1% | 754 | 1.1% |
| straight -x-y (y wing) 0 | straight | yes | 2341 | 3.4% | 2341 | 3.4% |
| straight -x-y (y wing) 1 | straight | yes | 1851 | 2.7% | 1720 | 2.5% |
| straight -x-y (y wing) 2 | straight | yes | 1626 | 2.3% | 1601 | 2.3% |
| straight -x-y (y wing) 3 | straight | yes | 1195 | 1.7% | 1192 | 1.7% |
| straight -x-y (y wing) 4 | straight | yes | 647 | 0.9% | 637 | 0.9% |
| straight -x-y (x wing) 0 | straight | yes | 2384 | 3.4% | 2384 | 3.4% |
| straight -x-y (x wing) 1 | straight | yes | 1852 | 2.7% | 1720 | 2.5% |
| straight -x-y (x wing) 2 | straight | yes | 1596 | 2.3% | 1584 | 2.3% |
| straight -x-y (x wing) 3 | straight | yes | 1220 | 1.8% | 1217 | 1.8% |
| straight -x-y (x wing) 4 | straight | yes | 661 | 1.0% | 649 | 0.9% |
| corner -x-y | corner | yes | 2137 | 3.1% | 821 | 1.2% |
| straight +x-y (y wing) 0 | straight | yes | 2361 | 3.4% | 2361 | 3.4% |
| straight +x-y (y wing) 1 | straight | yes | 1854 | 2.7% | 1744 | 2.5% |
| straight +x-y (y wing) 2 | straight | yes | 1620 | 2.3% | 1608 | 2.3% |
| straight +x-y (y wing) 3 | straight | yes | 1169 | 1.7% | 1163 | 1.7% |
| straight +x-y (y wing) 4 | straight | yes | 611 | 0.9% | 596 | 0.9% |
| straight +x-y (x wing) 0 | straight | yes | 2388 | 3.4% | 2388 | 3.4% |
| straight +x-y (x wing) 1 | straight | yes | 1855 | 2.7% | 1734 | 2.5% |
| straight +x-y (x wing) 2 | straight | yes | 1608 | 2.3% | 1600 | 2.3% |
| straight +x-y (x wing) 3 | straight | yes | 1167 | 1.7% | 1164 | 1.7% |
| straight +x-y (x wing) 4 | straight | yes | 725 | 1.0% | 708 | 1.0% |
| corner +x-y | corner | yes | 2093 | 3.0% | 801 | 1.2% |
| **straight (40)** | | | 61497 | | 60172 | 86.8% |
| **corner (4)** | | | 8494 | | 3292 | 4.7% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 5847, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 2125 | 60.2 | 1217.5 | 0.23 | 0.71 | 0.0% |
| -x | 2169 | 60.2 | 1210.0 | 0.24 | 0.71 | 0.0% |
| +y | 2188 | 60.2 | 1198.6 | 0.24 | 0.70 | 0.0% |
| -y | 2213 | 60.2 | 1213.5 | 0.24 | 0.76 | 0.0% |
| door +x+y (y wall) 0 | 1648 | 0.9 | 1206.3 | 0.43 | 1.28 | 4.1% |
| door +x+y (y wall) 1 | 1864 | 0.9 | 1457.0 | 0.40 | 1.22 | 3.4% |
| door +x+y (y wall) 2 | 1789 | 0.9 | 1522.2 | 0.37 | 1.35 | 3.3% |
| door +x+y (y wall) 3 | 1165 | 0.7 | 1518.2 | 0.24 | 1.31 | 3.3% |
| door +x+y (y wall) 4 | 773 | 0.9 | 1488.3 | 0.16 | 1.35 | 3.3% |
| door +x+y (x wall) 0 | 1667 | 0.9 | 1178.7 | 0.44 | 1.31 | 4.2% |
| door +x+y (x wall) 1 | 1835 | 0.9 | 1438.8 | 0.40 | 1.31 | 3.4% |
| door +x+y (x wall) 2 | 1787 | 0.7 | 1483.7 | 0.38 | 1.35 | 3.4% |
| door +x+y (x wall) 3 | 1220 | 0.9 | 1521.0 | 0.25 | 1.31 | 3.3% |
| door +x+y (x wall) 4 | 784 | 0.9 | 1526.1 | 0.16 | 1.25 | 3.2% |
| door +x+y (corner) | 562 | 0.9 | 851.1 | 0.21 | 0.91 | 2.3% |
| door -x+y (y wall) 0 | 1657 | 0.7 | 1256.9 | 0.41 | 1.35 | 3.1% |
| door -x+y (y wall) 1 | 1854 | 0.9 | 1456.4 | 0.40 | 1.38 | 3.4% |
| door -x+y (y wall) 2 | 1685 | 1.2 | 1465.9 | 0.36 | 1.35 | 2.7% |
| door -x+y (y wall) 3 | 1297 | 0.7 | 1491.1 | 0.27 | 1.31 | 3.3% |
| door -x+y (y wall) 4 | 845 | 0.9 | 1465.5 | 0.18 | 1.28 | 3.4% |
| door -x+y (x wall) 0 | 1667 | 0.9 | 1268.1 | 0.41 | 1.28 | 3.9% |
| door -x+y (x wall) 1 | 1841 | 0.9 | 1439.0 | 0.40 | 1.31 | 3.4% |
| door -x+y (x wall) 2 | 1691 | 0.7 | 1486.9 | 0.36 | 1.31 | 3.3% |
| door -x+y (x wall) 3 | 1268 | 0.9 | 1492.0 | 0.27 | 1.35 | 3.3% |
| door -x+y (x wall) 4 | 860 | 0.7 | 1345.9 | 0.20 | 1.28 | 4.4% |
| door -x+y (corner) | 502 | 0.9 | 1136.7 | 0.14 | 0.91 | 1.7% |
| door -x-y (y wall) 0 | 1646 | 0.9 | 1320.0 | 0.39 | 1.35 | 3.8% |
| door -x-y (y wall) 1 | 1827 | 0.9 | 1465.7 | 0.39 | 1.35 | 3.4% |
| door -x-y (y wall) 2 | 1687 | 0.7 | 1479.2 | 0.36 | 1.31 | 3.4% |
| door -x-y (y wall) 3 | 1323 | 0.9 | 1472.4 | 0.28 | 1.31 | 3.4% |
| door -x-y (y wall) 4 | 774 | 0.9 | 1485.8 | 0.16 | 1.35 | 3.3% |
| door -x-y (x wall) 0 | 1704 | 0.9 | 1269.6 | 0.42 | 1.31 | 3.9% |
| door -x-y (x wall) 1 | 1827 | 0.9 | 1403.1 | 0.41 | 1.31 | 2.8% |
| door -x-y (x wall) 2 | 1695 | 0.9 | 1475.0 | 0.36 | 1.35 | 3.4% |
| door -x-y (x wall) 3 | 1331 | 0.7 | 1483.7 | 0.28 | 1.31 | 3.4% |
| door -x-y (x wall) 4 | 786 | 0.9 | 1486.5 | 0.17 | 1.31 | 3.3% |
| door -x-y (corner) | 556 | 0.9 | 1312.3 | 0.13 | 0.88 | 0.0% |
| door +x-y (y wall) 0 | 1700 | 0.9 | 1283.8 | 0.41 | 1.35 | 3.9% |
| door +x-y (y wall) 1 | 1849 | 0.7 | 1452.8 | 0.40 | 1.25 | 3.4% |
| door +x-y (y wall) 2 | 1719 | 0.7 | 1465.2 | 0.37 | 1.31 | 3.4% |
| door +x-y (y wall) 3 | 1277 | 0.7 | 1498.4 | 0.27 | 1.31 | 3.3% |
| door +x-y (y wall) 4 | 741 | 1.0 | 1480.6 | 0.16 | 1.31 | 3.4% |
| door +x-y (x wall) 0 | 1676 | 0.9 | 1186.4 | 0.44 | 1.31 | 4.2% |
| door +x-y (x wall) 1 | 1856 | 0.9 | 1448.9 | 0.40 | 1.28 | 3.4% |
| door +x-y (x wall) 2 | 1699 | 0.9 | 1502.3 | 0.35 | 1.41 | 3.3% |
| door +x-y (x wall) 3 | 1304 | 0.9 | 1498.3 | 0.27 | 1.38 | 3.3% |
| door +x-y (x wall) 4 | 837 | 0.9 | 1498.6 | 0.17 | 1.31 | 3.3% |
| door +x-y (corner) | 541 | 0.9 | 1310.6 | 0.13 | 0.85 | 2.3% |

Mean flow / w J averaged over the doors 0.31, over the avenues 0.24.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 103.1 | 2352 | 1531 / 821 / 1066 | 0.2 | 1162.6 | 2.94 | 5.22 | 92% | 86% | 6% | 4.45 |
| straight +x+y (y wing) 1 | 1.20 | 81.5 | 1891 | 1750 / 0 / 241 | 0.7 | 1454.0 | 1.37 | 2.11 | 88% | 70% | 18% | 3.79 |
| straight +x+y (y wing) 2 | 1.20 | 61.0 | 1495 | 1692 / 0 / 15 | 0.7 | 1519.2 | 1.12 | 1.71 | 92% | 62% | 29% | 3.20 |
| straight +x+y (y wing) 3 | 1.20 | 39.4 | 948 | 1061 / 0 / 12 | 0.7 | 1515.2 | 0.71 | 1.60 | 49% | 40% | 9% | 3.63 |
| straight +x+y (y wing) 4 | 1.20 | 18.8 | 406 | 616 / 0 / 16 | 0.7 | 1485.3 | 0.43 | 1.71 | 19% | 16% | 3% | 3.72 |
| straight +x+y (x wing) 0 | 1.20 | 103.1 | 2330 | 1549 / 782 / 1048 | 0.3 | 1175.7 | 2.87 | 4.91 | 92% | 89% | 3% | 4.44 |
| straight +x+y (x wing) 1 | 1.20 | 81.5 | 1879 | 1719 / 0 / 253 | 0.7 | 1435.8 | 1.37 | 2.51 | 86% | 66% | 20% | 3.62 |
| straight +x+y (x wing) 2 | 1.20 | 61.0 | 1553 | 1698 / 0 / 9 | 0.7 | 1480.8 | 1.15 | 1.60 | 95% | 68% | 26% | 3.29 |
| straight +x+y (x wing) 3 | 1.20 | 39.4 | 924 | 1086 / 0 / 19 | 0.7 | 1518.0 | 0.73 | 1.71 | 49% | 36% | 13% | 3.34 |
| straight +x+y (x wing) 4 | 1.20 | 18.8 | 395 | 647 / 0 / 15 | 0.7 | 1523.1 | 0.43 | 1.71 | 18% | 16% | 3% | 3.73 |
| corner +x+y | 1.20 | 186.0 | 1694 | 434 / 482 / 1275 | 0.7 | 1499.1 | 1.46 | 3.21 | 93% | 73% | 20% | 2.70 |
| straight -x+y (y wing) 0 | 1.20 | 103.1 | 2338 | 1542 / 797 / 1037 | 0.2 | 1197.1 | 2.82 | 4.71 | 92% | 86% | 6% | 4.15 |
| straight -x+y (y wing) 1 | 1.20 | 81.5 | 1845 | 1744 / 0 / 174 | 0.7 | 1453.5 | 1.32 | 2.41 | 92% | 75% | 18% | 3.72 |
| straight -x+y (y wing) 2 | 1.20 | 61.0 | 1543 | 1606 / 0 / 20 | 0.7 | 1462.9 | 1.11 | 1.91 | 80% | 69% | 11% | 3.69 |
| straight -x+y (y wing) 3 | 1.20 | 39.4 | 930 | 1152 / 0 / 14 | 0.7 | 1488.1 | 0.78 | 1.71 | 50% | 38% | 12% | 3.42 |
| straight -x+y (y wing) 4 | 1.20 | 18.8 | 389 | 712 / 0 / 19 | 0.7 | 1462.6 | 0.50 | 1.81 | 18% | 15% | 3% | 3.72 |
| straight -x+y (x wing) 0 | 1.20 | 103.1 | 2373 | 1551 / 822 / 983 | 0.5 | 1171.5 | 2.87 | 5.12 | 92% | 86% | 6% | 4.37 |
| straight -x+y (x wing) 1 | 1.20 | 81.5 | 1836 | 1731 / 0 / 188 | 0.7 | 1436.0 | 1.34 | 2.51 | 93% | 74% | 19% | 3.71 |
| straight -x+y (x wing) 2 | 1.20 | 61.0 | 1492 | 1603 / 0 / 11 | 0.7 | 1483.9 | 1.09 | 1.81 | 75% | 64% | 11% | 3.80 |
| straight -x+y (x wing) 3 | 1.20 | 39.4 | 940 | 1150 / 0 / 14 | 0.7 | 1489.0 | 0.78 | 1.60 | 48% | 40% | 8% | 3.77 |
| straight -x+y (x wing) 4 | 1.20 | 18.8 | 400 | 701 / 0 / 0 | 0.7 | 1342.9 | 0.52 | 1.60 | 27% | 18% | 10% | 2.95 |
| corner -x+y | 1.20 | 186.0 | 1778 | 372 / 382 / 1401 | 0.7 | 1438.8 | 1.50 | 3.01 | 94% | 60% | 34% | 2.64 |
| straight -x-y (y wing) 0 | 1.20 | 103.1 | 2341 | 1519 / 822 / 988 | 0.2 | 1163.0 | 2.86 | 4.91 | 92% | 85% | 7% | 4.36 |
| straight -x-y (y wing) 1 | 1.20 | 81.5 | 1813 | 1720 / 0 / 185 | 0.7 | 1462.7 | 1.30 | 2.01 | 90% | 71% | 18% | 3.86 |
| straight -x-y (y wing) 2 | 1.20 | 61.0 | 1555 | 1601 / 0 / 26 | 0.7 | 1476.2 | 1.10 | 1.71 | 79% | 68% | 11% | 3.84 |
| straight -x-y (y wing) 3 | 1.20 | 39.4 | 931 | 1192 / 0 / 4 | 0.7 | 1469.4 | 0.81 | 1.71 | 47% | 38% | 9% | 3.76 |
| straight -x-y (y wing) 4 | 1.20 | 18.8 | 405 | 637 / 0 / 24 | 0.7 | 1482.9 | 0.45 | 1.71 | 19% | 17% | 2% | 3.76 |
| straight -x-y (x wing) 0 | 1.20 | 103.1 | 2384 | 1584 / 802 / 928 | 0.2 | 1214.9 | 2.73 | 5.62 | 93% | 85% | 7% | 4.11 |
| straight -x-y (x wing) 1 | 1.20 | 81.5 | 1840 | 1720 / 0 / 167 | 0.7 | 1400.1 | 1.35 | 2.01 | 93% | 79% | 13% | 3.92 |
| straight -x-y (x wing) 2 | 1.20 | 61.0 | 1476 | 1584 / 0 / 13 | 0.7 | 1472.0 | 1.09 | 1.71 | 76% | 64% | 12% | 3.78 |
| straight -x-y (x wing) 3 | 1.20 | 39.4 | 948 | 1217 / 0 / 6 | 0.7 | 1480.8 | 0.83 | 1.71 | 48% | 40% | 8% | 3.68 |
| straight -x-y (x wing) 4 | 1.20 | 18.8 | 393 | 649 / 0 / 13 | 0.7 | 1483.6 | 0.45 | 1.60 | 18% | 16% | 2% | 3.83 |
| corner -x-y | 1.20 | 186.0 | 1780 | 435 / 386 / 1362 | 0.7 | 1459.6 | 1.50 | 4.21 | 91% | 59% | 32% | 2.71 |
| straight +x-y (y wing) 0 | 1.20 | 103.1 | 2361 | 1566 / 795 / 1029 | 0.2 | 1183.1 | 2.87 | 5.72 | 92% | 88% | 4% | 4.27 |
| straight +x-y (y wing) 1 | 1.20 | 81.5 | 1835 | 1744 / 0 / 140 | 0.7 | 1449.8 | 1.30 | 2.61 | 92% | 77% | 14% | 3.88 |
| straight +x-y (y wing) 2 | 1.20 | 61.0 | 1519 | 1608 / 0 / 21 | 0.7 | 1462.2 | 1.11 | 1.91 | 78% | 67% | 10% | 3.84 |
| straight +x-y (y wing) 3 | 1.20 | 39.4 | 933 | 1163 / 0 / 9 | 0.7 | 1495.5 | 0.78 | 1.81 | 47% | 39% | 8% | 3.72 |
| straight +x-y (y wing) 4 | 1.20 | 18.8 | 390 | 596 / 0 / 36 | 0.7 | 1477.6 | 0.43 | 1.71 | 18% | 15% | 3% | 3.74 |
| straight +x-y (x wing) 0 | 1.20 | 103.1 | 2388 | 1555 / 834 / 1087 | 0.3 | 1183.4 | 2.94 | 5.12 | 92% | 85% | 8% | 4.22 |
| straight +x-y (x wing) 1 | 1.20 | 81.5 | 1838 | 1734 / 0 / 181 | 0.7 | 1446.0 | 1.32 | 2.31 | 90% | 75% | 14% | 3.83 |
| straight +x-y (x wing) 2 | 1.20 | 61.0 | 1493 | 1600 / 0 / 13 | 0.7 | 1499.3 | 1.08 | 1.71 | 74% | 64% | 10% | 3.73 |
| straight +x-y (x wing) 3 | 1.20 | 39.4 | 930 | 1164 / 0 / 88 | 0.7 | 1495.3 | 0.84 | 3.01 | 47% | 38% | 9% | 3.65 |
| straight +x-y (x wing) 4 | 1.20 | 18.8 | 406 | 708 / 0 / 17 | 0.7 | 1495.6 | 0.48 | 1.81 | 19% | 15% | 3% | 3.76 |
| corner +x-y | 1.20 | 186.0 | 1774 | 417 / 384 / 1438 | 0.7 | 1471.8 | 1.52 | 3.71 | 93% | 64% | 29% | 2.64 |

The last agent out (agent 9471, t100 1526.1 s): last gangway straight +x+y (x wing) 4, exit door +x+y (x wall) 4. The gangway that cleared last: straight +x+y (x wing) 4 at 1523.1 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 8804 | 7800.4 | 6.96 | 1518.9 / 1456.3 / 1403.1 | 1458.9 / 1427.2 / 1382.8 | 7389343.2 | 13933843 | 0.165 |
| gangway | 3792 | 3512.9 | 6.96 | 1516.3 / 1456.1 / 1401.2 | 1458.9 / 1427.2 / 1382.8 | 7362221.1 | 12981220 | 0.101 |
| walkway | 276 | 257.4 | 5.33 | 742.5 / 502.7 / 18.7 | 482.0 / 202.5 / 10.3 | 149.0 | 90973 | 0.667 |
| avenue | 1920 | 1801.4 | 3.15 | 783.1 / 59.5 / 0.0 | 588.7 / 2.3 / 0.0 | 0.0 | 521079 | 1.334 |
| exit | 4 | 2.0 | 0.00 | 0.7 / 0.3 / 0.0 | 0.7 / 0.3 / 0.0 | 0.0 | 4 | 0.871 |
| concourse | 2812 | 2226.8 | 5.96 | 1461.2 / 72.8 / 50.4 | 1086.5 / 71.7 / 42.0 | 26973.1 | 340567 | 0.711 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 25392 | 16030.4 | 7.89 | 1402.2 / 1398.2 / 1376.7 | 1395.1 / 1390.9 / 1366.0 | 9286171.7 | 22836943 | 0.022 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 208 x 208 from (-104, -104) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 34.5 | -34.5 | gangway | 1.00 | 5.87 | 1388.8 | 1381.6 | 1336.3 | 7759.5 | 0.004 |
| 2 | -34.5 | 34.5 | gangway | 1.00 | 5.72 | 1373.9 | 1362.9 | 1314.1 | 7422.1 | 0.005 |
| 3 | 50.5 | 50.5 | gangway | 1.00 | 5.93 | 1431.6 | 1416.2 | 1313.5 | 7312.8 | 0.010 |
| 4 | -35.5 | -35.5 | gangway | 1.00 | 5.66 | 1378.6 | 1366.4 | 1306.4 | 7285.9 | 0.007 |
| 5 | 47.5 | 47.5 | gangway | 1.00 | 5.40 | 1415.5 | 1413.9 | 1372.8 | 7250.9 | 0.005 |
| 6 | 34.5 | 34.5 | gangway | 1.00 | 6.03 | 1334.7 | 1308.5 | 1255.3 | 7242.4 | 0.005 |
| 7 | 35.5 | 35.5 | gangway | 1.00 | 6.01 | 1324.6 | 1321.2 | 1263.5 | 7232.5 | 0.005 |
| 8 | 35.5 | -35.5 | gangway | 1.00 | 5.61 | 1396.1 | 1386.0 | 1328.6 | 7165.2 | 0.007 |
| 9 | -34.5 | -34.5 | gangway | 1.00 | 5.79 | 1368.6 | 1356.9 | 1297.3 | 7162.2 | 0.006 |
| 10 | -36.5 | 36.5 | gangway | 1.00 | 5.78 | 1385.1 | 1367.2 | 1264.1 | 7146.8 | 0.010 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 36.5 | -38.5 | seat row | 0.50 | 7.54 | 1366.7 | 1363.4 | 1324.6 | 4836.2 | 0.005 |
| 2 | -36.5 | 38.5 | seat row | 0.50 | 7.36 | 1345.6 | 1340.1 | 1328.9 | 4734.0 | 0.004 |
| 3 | 38.5 | -36.5 | seat row | 0.50 | 7.38 | 1347.0 | 1344.2 | 1321.6 | 4717.7 | 0.004 |
| 4 | -38.5 | 36.5 | seat row | 0.50 | 7.29 | 1343.8 | 1340.5 | 1322.3 | 4672.8 | 0.004 |
| 5 | -38.5 | -36.5 | seat row | 0.50 | 7.33 | 1311.1 | 1300.6 | 1286.8 | 4642.2 | 0.004 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 8417; agent-steps of seated agents on another row's clearway: 688871.

## Deposit check

Person-seconds deposited: 36777064.5, of them in excluded cells: 6278.903.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 9549159 overlapping pair-steps: p99 0.0020, max 0.0560 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0020 max 0.0560; venue-geometry 13: p99 0.0032 max 0.0032 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 58 (longest 2 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.44 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 3854 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
