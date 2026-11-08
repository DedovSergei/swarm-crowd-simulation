# Experiment `L_load100`

**Task 5.8 stage 2: venue L, 100% load, default model**

Venue L (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (4000 x 4000), cache key a2f3aaf59c2252b7, content hash 022d17b202313d70). 63424 agents on 100% of the 63424 seats (spawnSeatedCrowd, seed 1337), buffer N = 65536, 6800 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 9308098 evaluations, 522754 switches, 0 forced choices).
Capacity: **within design capacity** (the L venue's design capacity 63424, jam capacity 171923: 23822.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `cd8e0bbf3411846ca7aa6719887d122a142a7ca1`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-15T16:37:38, 771.5 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 2362 | 413.1 |
| t90 | 4748 | 830.5 |
| t100 | 6800 | 1189.4 |

t_p: the step by which ceil(p x 63424) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 1854 | 0 | 70.3 | 919.1 | 23.1 | 26.6 | 152.3-162.3 |
| -x | 5.66 | 1866 | 0 | 70.5 | 910.2 | 23.6 | 26.6 | 273.4-283.3 |
| +y | 5.66 | 1854 | 0 | 70.5 | 904.6 | 23.6 | 26.6 | 84.3-94.3 |
| -y | 5.66 | 1867 | 0 | 70.5 | 906.5 | 23.7 | 26.6 | 227.9-237.9 |
| door +x+y (y wall) 0 | 2.30 | 1595 | 2577 | 4.9 | 1015.9 | 41.2 | 60.2 | 16.4-26.4 |
| door +x+y (y wall) 1 | 2.30 | 1759 | 2137 | 4.9 | 1161.4 | 39.7 | 57.6 | 14.2-24.1 |
| door +x+y (y wall) 2 | 2.30 | 1565 | 1594 | 4.9 | 1160.3 | 35.3 | 57.6 | 19.1-29.0 |
| door +x+y (y wall) 3 | 2.30 | 1067 | 1045 | 4.9 | 1150.2 | 24.3 | 57.6 | 19.1-29.0 |
| door +x+y (y wall) 4 | 2.30 | 766 | 513 | 4.9 | 1061.9 | 18.9 | 54.9 | 7.9-17.8 |
| door +x+y (x wall) 0 | 2.30 | 1562 | 2577 | 4.9 | 994.9 | 41.2 | 54.9 | 13.3-23.3 |
| door +x+y (x wall) 1 | 2.30 | 1772 | 2137 | 4.9 | 1132.0 | 41.0 | 57.6 | 80.8-90.8 |
| door +x+y (x wall) 2 | 2.30 | 1598 | 1594 | 4.9 | 1148.3 | 36.5 | 54.9 | 10.7-20.6 |
| door +x+y (x wall) 3 | 2.30 | 1144 | 1045 | 4.9 | 1152.3 | 26.0 | 54.9 | 13.3-23.3 |
| door +x+y (x wall) 4 | 2.30 | 711 | 513 | 5.1 | 1092.5 | 17.1 | 57.6 | 27.6-37.6 |
| door +x+y (corner) | 2.30 | 476 | 124 | 6.3 | 1017.6 | 12.3 | 54.9 | 90.6-100.6 |
| door -x+y (y wall) 0 | 2.30 | 1569 | 2577 | 4.9 | 1028.8 | 40.0 | 57.6 | 11.7-21.7 |
| door -x+y (y wall) 1 | 2.30 | 1789 | 2137 | 4.9 | 1125.0 | 41.7 | 60.2 | 11.5-21.5 |
| door -x+y (y wall) 2 | 2.30 | 1568 | 1594 | 4.9 | 1158.4 | 35.5 | 60.2 | 11.5-21.5 |
| door -x+y (y wall) 3 | 2.30 | 1141 | 1045 | 4.9 | 1162.3 | 25.7 | 60.2 | 11.5-21.5 |
| door -x+y (y wall) 4 | 2.30 | 673 | 513 | 5.1 | 1161.4 | 15.2 | 57.6 | 8.6-18.5 |
| door -x+y (x wall) 0 | 2.30 | 1582 | 2577 | 4.9 | 1016.7 | 40.8 | 60.2 | 16.4-26.4 |
| door -x+y (x wall) 1 | 2.30 | 1785 | 2137 | 4.9 | 1100.5 | 42.5 | 54.9 | 30.3-40.2 |
| door -x+y (x wall) 2 | 2.30 | 1536 | 1594 | 4.9 | 1133.6 | 35.5 | 57.6 | 24.0-33.9 |
| door -x+y (x wall) 3 | 2.30 | 1168 | 1045 | 4.9 | 1148.4 | 26.6 | 60.2 | 28.2-38.1 |
| door -x+y (x wall) 4 | 2.30 | 760 | 513 | 4.9 | 1139.9 | 17.5 | 57.6 | 10.5-20.5 |
| door -x+y (corner) | 2.30 | 447 | 124 | 6.3 | 839.4 | 14.0 | 52.3 | 28.9-38.8 |
| door -x-y (y wall) 0 | 2.30 | 1573 | 2577 | 4.9 | 1012.2 | 40.7 | 54.9 | 27.1-37.1 |
| door -x-y (y wall) 1 | 2.30 | 1761 | 2137 | 4.9 | 1094.9 | 42.1 | 57.6 | 16.8-26.8 |
| door -x-y (y wall) 2 | 2.30 | 1555 | 1594 | 4.9 | 1150.0 | 35.4 | 57.6 | 614.8-624.8 |
| door -x-y (y wall) 3 | 2.30 | 1207 | 1045 | 4.9 | 1156.7 | 27.3 | 60.2 | 16.6-26.6 |
| door -x-y (y wall) 4 | 2.30 | 722 | 513 | 4.9 | 1163.7 | 16.3 | 57.6 | 26.9-36.9 |
| door -x-y (x wall) 0 | 2.30 | 1580 | 2577 | 4.9 | 1002.0 | 41.3 | 60.2 | 11.5-21.5 |
| door -x-y (x wall) 1 | 2.30 | 1758 | 2137 | 4.9 | 1140.2 | 40.4 | 57.6 | 10.7-20.6 |
| door -x-y (x wall) 2 | 2.30 | 1521 | 1594 | 4.9 | 1130.6 | 35.2 | 57.6 | 10.7-20.6 |
| door -x-y (x wall) 3 | 2.30 | 1209 | 1045 | 4.9 | 1151.9 | 27.5 | 57.6 | 11.7-21.7 |
| door -x-y (x wall) 4 | 2.30 | 701 | 513 | 5.1 | 1128.7 | 16.3 | 54.9 | 27.8-37.8 |
| door -x-y (corner) | 2.30 | 395 | 124 | 6.3 | 918.8 | 11.3 | 54.9 | 46.7-56.7 |
| door +x-y (y wall) 0 | 2.30 | 1578 | 2577 | 4.9 | 1000.3 | 41.3 | 57.6 | 10.7-20.6 |
| door +x-y (y wall) 1 | 2.30 | 1739 | 2137 | 4.9 | 1189.4 | 38.3 | 60.2 | 11.7-21.7 |
| door +x-y (y wall) 2 | 2.30 | 1578 | 1594 | 4.9 | 1132.5 | 36.5 | 57.6 | 20.1-30.1 |
| door +x-y (y wall) 3 | 2.30 | 1229 | 1045 | 4.9 | 1162.3 | 27.7 | 60.2 | 11.7-21.7 |
| door +x-y (y wall) 4 | 2.30 | 669 | 513 | 5.1 | 1124.3 | 15.6 | 57.6 | 8.6-18.5 |
| door +x-y (x wall) 0 | 2.30 | 1588 | 2577 | 4.9 | 996.3 | 41.8 | 60.2 | 17.8-27.8 |
| door +x-y (x wall) 1 | 2.30 | 1754 | 2137 | 4.9 | 1103.5 | 41.6 | 54.9 | 10.8-20.8 |
| door +x-y (x wall) 2 | 2.30 | 1549 | 1594 | 4.9 | 1169.6 | 34.7 | 54.9 | 11.0-21.0 |
| door +x-y (x wall) 3 | 2.30 | 1246 | 1045 | 4.9 | 1174.5 | 27.8 | 57.6 | 614.8-624.8 |
| door +x-y (x wall) 4 | 2.30 | 617 | 513 | 5.1 | 1166.6 | 13.9 | 57.6 | 15.0-25.0 |
| door +x-y (corner) | 2.30 | 421 | 124 | 6.5 | 981.2 | 11.3 | 54.9 | 46.9-56.8 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (2.30 m; a corner door's: the gap between its wall ends, 2.30 m); agents are removed past the outer wall's outer face (92.71 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 1854 | 2.9% | 19.8% |
| -x | avenue | 5.66 | 1866 | 2.9% | 19.9% |
| +y | avenue | 5.66 | 1854 | 2.9% | 19.8% |
| -y | avenue | 5.66 | 1867 | 2.9% | 19.9% |
| door +x+y (y wall) 0 | door | 2.30 | 1595 | 2.5% | 41.8% |
| door +x+y (y wall) 1 | door | 2.30 | 1759 | 2.8% | 46.1% |
| door +x+y (y wall) 2 | door | 2.30 | 1565 | 2.5% | 41.1% |
| door +x+y (y wall) 3 | door | 2.30 | 1067 | 1.7% | 28.0% |
| door +x+y (y wall) 4 | door | 2.30 | 766 | 1.2% | 20.1% |
| door +x+y (x wall) 0 | door | 2.30 | 1562 | 2.5% | 41.0% |
| door +x+y (x wall) 1 | door | 2.30 | 1772 | 2.8% | 46.5% |
| door +x+y (x wall) 2 | door | 2.30 | 1598 | 2.5% | 41.9% |
| door +x+y (x wall) 3 | door | 2.30 | 1144 | 1.8% | 30.0% |
| door +x+y (x wall) 4 | door | 2.30 | 711 | 1.1% | 18.7% |
| door +x+y (corner) | door | 2.30 | 476 | 0.8% | 12.5% |
| door -x+y (y wall) 0 | door | 2.30 | 1569 | 2.5% | 41.2% |
| door -x+y (y wall) 1 | door | 2.30 | 1789 | 2.8% | 46.9% |
| door -x+y (y wall) 2 | door | 2.30 | 1568 | 2.5% | 41.1% |
| door -x+y (y wall) 3 | door | 2.30 | 1141 | 1.8% | 29.9% |
| door -x+y (y wall) 4 | door | 2.30 | 673 | 1.1% | 17.7% |
| door -x+y (x wall) 0 | door | 2.30 | 1582 | 2.5% | 41.5% |
| door -x+y (x wall) 1 | door | 2.30 | 1785 | 2.8% | 46.8% |
| door -x+y (x wall) 2 | door | 2.30 | 1536 | 2.4% | 40.3% |
| door -x+y (x wall) 3 | door | 2.30 | 1168 | 1.8% | 30.6% |
| door -x+y (x wall) 4 | door | 2.30 | 760 | 1.2% | 19.9% |
| door -x+y (corner) | door | 2.30 | 447 | 0.7% | 11.7% |
| door -x-y (y wall) 0 | door | 2.30 | 1573 | 2.5% | 41.3% |
| door -x-y (y wall) 1 | door | 2.30 | 1761 | 2.8% | 46.2% |
| door -x-y (y wall) 2 | door | 2.30 | 1555 | 2.5% | 40.8% |
| door -x-y (y wall) 3 | door | 2.30 | 1207 | 1.9% | 31.7% |
| door -x-y (y wall) 4 | door | 2.30 | 722 | 1.1% | 18.9% |
| door -x-y (x wall) 0 | door | 2.30 | 1580 | 2.5% | 41.5% |
| door -x-y (x wall) 1 | door | 2.30 | 1758 | 2.8% | 46.1% |
| door -x-y (x wall) 2 | door | 2.30 | 1521 | 2.4% | 39.9% |
| door -x-y (x wall) 3 | door | 2.30 | 1209 | 1.9% | 31.7% |
| door -x-y (x wall) 4 | door | 2.30 | 701 | 1.1% | 18.4% |
| door -x-y (corner) | door | 2.30 | 395 | 0.6% | 10.4% |
| door +x-y (y wall) 0 | door | 2.30 | 1578 | 2.5% | 41.4% |
| door +x-y (y wall) 1 | door | 2.30 | 1739 | 2.7% | 45.6% |
| door +x-y (y wall) 2 | door | 2.30 | 1578 | 2.5% | 41.4% |
| door +x-y (y wall) 3 | door | 2.30 | 1229 | 1.9% | 32.2% |
| door +x-y (y wall) 4 | door | 2.30 | 669 | 1.1% | 17.6% |
| door +x-y (x wall) 0 | door | 2.30 | 1588 | 2.5% | 41.7% |
| door +x-y (x wall) 1 | door | 2.30 | 1754 | 2.8% | 46.0% |
| door +x-y (x wall) 2 | door | 2.30 | 1549 | 2.4% | 40.6% |
| door +x-y (x wall) 3 | door | 2.30 | 1246 | 2.0% | 32.7% |
| door +x-y (x wall) 4 | door | 2.30 | 617 | 1.0% | 16.2% |
| door +x-y (corner) | door | 2.30 | 421 | 0.7% | 11.0% |
| **doors (44)** | door | 101.20 | 55983 | 88.3% | |
| **avenues (4)** | avenue | 22.64 | 7441 | 11.7% | |

**Unused exit width: 0.0 of 123.8 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 1189.4 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 30.9%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 2322 | 3.7% | 2322 | 3.7% |
| straight +x+y (y wing) 1 | straight | yes | 1872 | 3.0% | 1784 | 2.8% |
| straight +x+y (y wing) 2 | straight | yes | 1614 | 2.5% | 1604 | 2.5% |
| straight +x+y (y wing) 3 | straight | yes | 1126 | 1.8% | 1107 | 1.7% |
| straight +x+y (y wing) 4 | straight | yes | 706 | 1.1% | 687 | 1.1% |
| straight +x+y (x wing) 0 | straight | yes | 2333 | 3.7% | 2333 | 3.7% |
| straight +x+y (x wing) 1 | straight | yes | 1868 | 2.9% | 1783 | 2.8% |
| straight +x+y (x wing) 2 | straight | yes | 1628 | 2.6% | 1616 | 2.5% |
| straight +x+y (x wing) 3 | straight | yes | 1172 | 1.8% | 1165 | 1.8% |
| straight +x+y (x wing) 4 | straight | yes | 700 | 1.1% | 672 | 1.1% |
| corner +x+y | corner | yes | 2094 | 3.3% | 783 | 1.2% |
| straight -x+y (y wing) 0 | straight | yes | 2332 | 3.7% | 2332 | 3.7% |
| straight -x+y (y wing) 1 | straight | yes | 1883 | 3.0% | 1798 | 2.8% |
| straight -x+y (y wing) 2 | straight | yes | 1639 | 2.6% | 1628 | 2.6% |
| straight -x+y (y wing) 3 | straight | yes | 1107 | 1.7% | 1095 | 1.7% |
| straight -x+y (y wing) 4 | straight | yes | 675 | 1.1% | 659 | 1.0% |
| straight -x+y (x wing) 0 | straight | yes | 2331 | 3.7% | 2331 | 3.7% |
| straight -x+y (x wing) 1 | straight | yes | 1884 | 3.0% | 1809 | 2.9% |
| straight -x+y (x wing) 2 | straight | yes | 1620 | 2.6% | 1606 | 2.5% |
| straight -x+y (x wing) 3 | straight | yes | 1151 | 1.8% | 1133 | 1.8% |
| straight -x+y (x wing) 4 | straight | yes | 745 | 1.2% | 725 | 1.1% |
| corner -x+y | corner | yes | 2016 | 3.2% | 740 | 1.2% |
| straight -x-y (y wing) 0 | straight | yes | 2312 | 3.6% | 2312 | 3.6% |
| straight -x-y (y wing) 1 | straight | yes | 1899 | 3.0% | 1784 | 2.8% |
| straight -x-y (y wing) 2 | straight | yes | 1615 | 2.5% | 1597 | 2.5% |
| straight -x-y (y wing) 3 | straight | yes | 1210 | 1.9% | 1199 | 1.9% |
| straight -x-y (y wing) 4 | straight | yes | 701 | 1.1% | 688 | 1.1% |
| straight -x-y (x wing) 0 | straight | yes | 2315 | 3.7% | 2315 | 3.7% |
| straight -x-y (x wing) 1 | straight | yes | 1896 | 3.0% | 1779 | 2.8% |
| straight -x-y (x wing) 2 | straight | yes | 1604 | 2.5% | 1588 | 2.5% |
| straight -x-y (x wing) 3 | straight | yes | 1173 | 1.8% | 1168 | 1.8% |
| straight -x-y (x wing) 4 | straight | yes | 695 | 1.1% | 675 | 1.1% |
| corner -x-y | corner | yes | 2104 | 3.3% | 751 | 1.2% |
| straight +x-y (y wing) 0 | straight | yes | 2318 | 3.7% | 2318 | 3.7% |
| straight +x-y (y wing) 1 | straight | yes | 1889 | 3.0% | 1774 | 2.8% |
| straight +x-y (y wing) 2 | straight | yes | 1611 | 2.5% | 1595 | 2.5% |
| straight +x-y (y wing) 3 | straight | yes | 1216 | 1.9% | 1212 | 1.9% |
| straight +x-y (y wing) 4 | straight | yes | 690 | 1.1% | 669 | 1.1% |
| straight +x-y (x wing) 0 | straight | yes | 2316 | 3.7% | 2316 | 3.7% |
| straight +x-y (x wing) 1 | straight | yes | 1892 | 3.0% | 1772 | 2.8% |
| straight +x-y (x wing) 2 | straight | yes | 1610 | 2.5% | 1584 | 2.5% |
| straight +x-y (x wing) 3 | straight | yes | 1222 | 1.9% | 1219 | 1.9% |
| straight +x-y (x wing) 4 | straight | yes | 615 | 1.0% | 609 | 1.0% |
| corner +x-y | corner | yes | 2161 | 3.4% | 788 | 1.2% |
| **straight (40)** | | | 61507 | | 60362 | 95.2% |
| **corner (4)** | | | 8375 | | 3062 | 4.8% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 1854 | 70.3 | 919.1 | 0.28 | 0.32 | 0.0% |
| -x | 1866 | 70.5 | 910.2 | 0.28 | 0.32 | 0.0% |
| +y | 1854 | 70.5 | 904.6 | 0.28 | 0.32 | 0.0% |
| -y | 1867 | 70.5 | 906.5 | 0.28 | 0.32 | 0.0% |
| door +x+y (y wall) 0 | 1595 | 4.9 | 1015.9 | 0.49 | 0.72 | 0.0% |
| door +x+y (y wall) 1 | 1759 | 4.9 | 1161.4 | 0.47 | 0.69 | 0.0% |
| door +x+y (y wall) 2 | 1565 | 4.9 | 1160.3 | 0.42 | 0.69 | 0.0% |
| door +x+y (y wall) 3 | 1067 | 4.9 | 1150.2 | 0.29 | 0.69 | 0.0% |
| door +x+y (y wall) 4 | 766 | 4.9 | 1061.9 | 0.23 | 0.66 | 0.0% |
| door +x+y (x wall) 0 | 1562 | 4.9 | 994.9 | 0.49 | 0.66 | 0.0% |
| door +x+y (x wall) 1 | 1772 | 4.9 | 1132.0 | 0.49 | 0.69 | 0.0% |
| door +x+y (x wall) 2 | 1598 | 4.9 | 1148.3 | 0.44 | 0.66 | 0.0% |
| door +x+y (x wall) 3 | 1144 | 4.9 | 1152.3 | 0.31 | 0.66 | 0.0% |
| door +x+y (x wall) 4 | 711 | 5.1 | 1092.5 | 0.20 | 0.69 | 0.0% |
| door +x+y (corner) | 476 | 6.3 | 1017.6 | 0.15 | 0.66 | 0.0% |
| door -x+y (y wall) 0 | 1569 | 4.9 | 1028.8 | 0.48 | 0.69 | 0.0% |
| door -x+y (y wall) 1 | 1789 | 4.9 | 1125.0 | 0.50 | 0.72 | 0.0% |
| door -x+y (y wall) 2 | 1568 | 4.9 | 1158.4 | 0.42 | 0.72 | 0.0% |
| door -x+y (y wall) 3 | 1141 | 4.9 | 1162.3 | 0.31 | 0.72 | 0.0% |
| door -x+y (y wall) 4 | 673 | 5.1 | 1161.4 | 0.18 | 0.69 | 0.0% |
| door -x+y (x wall) 0 | 1582 | 4.9 | 1016.7 | 0.49 | 0.72 | 0.0% |
| door -x+y (x wall) 1 | 1785 | 4.9 | 1100.5 | 0.51 | 0.66 | 0.0% |
| door -x+y (x wall) 2 | 1536 | 4.9 | 1133.6 | 0.42 | 0.69 | 0.0% |
| door -x+y (x wall) 3 | 1168 | 4.9 | 1148.4 | 0.32 | 0.72 | 0.0% |
| door -x+y (x wall) 4 | 760 | 4.9 | 1139.9 | 0.21 | 0.69 | 0.0% |
| door -x+y (corner) | 447 | 6.3 | 839.4 | 0.17 | 0.63 | 0.0% |
| door -x-y (y wall) 0 | 1573 | 4.9 | 1012.2 | 0.49 | 0.66 | 0.0% |
| door -x-y (y wall) 1 | 1761 | 4.9 | 1094.9 | 0.50 | 0.69 | 0.0% |
| door -x-y (y wall) 2 | 1555 | 4.9 | 1150.0 | 0.42 | 0.69 | 0.0% |
| door -x-y (y wall) 3 | 1207 | 4.9 | 1156.7 | 0.33 | 0.72 | 0.0% |
| door -x-y (y wall) 4 | 722 | 4.9 | 1163.7 | 0.19 | 0.69 | 0.0% |
| door -x-y (x wall) 0 | 1580 | 4.9 | 1002.0 | 0.49 | 0.72 | 0.0% |
| door -x-y (x wall) 1 | 1758 | 4.9 | 1140.2 | 0.48 | 0.69 | 0.0% |
| door -x-y (x wall) 2 | 1521 | 4.9 | 1130.6 | 0.42 | 0.69 | 0.0% |
| door -x-y (x wall) 3 | 1209 | 4.9 | 1151.9 | 0.33 | 0.69 | 0.0% |
| door -x-y (x wall) 4 | 701 | 5.1 | 1128.7 | 0.19 | 0.66 | 0.0% |
| door -x-y (corner) | 395 | 6.3 | 918.8 | 0.14 | 0.66 | 0.0% |
| door +x-y (y wall) 0 | 1578 | 4.9 | 1000.3 | 0.49 | 0.69 | 0.0% |
| door +x-y (y wall) 1 | 1739 | 4.9 | 1189.4 | 0.46 | 0.72 | 0.0% |
| door +x-y (y wall) 2 | 1578 | 4.9 | 1132.5 | 0.44 | 0.69 | 0.0% |
| door +x-y (y wall) 3 | 1229 | 4.9 | 1162.3 | 0.33 | 0.72 | 0.0% |
| door +x-y (y wall) 4 | 669 | 5.1 | 1124.3 | 0.19 | 0.69 | 0.0% |
| door +x-y (x wall) 0 | 1588 | 4.9 | 996.3 | 0.50 | 0.72 | 0.0% |
| door +x-y (x wall) 1 | 1754 | 4.9 | 1103.5 | 0.50 | 0.66 | 0.0% |
| door +x-y (x wall) 2 | 1549 | 4.9 | 1169.6 | 0.41 | 0.66 | 0.0% |
| door +x-y (x wall) 3 | 1246 | 4.9 | 1174.5 | 0.33 | 0.69 | 0.0% |
| door +x-y (x wall) 4 | 617 | 5.1 | 1166.6 | 0.17 | 0.69 | 0.0% |
| door +x-y (corner) | 421 | 6.5 | 981.2 | 0.13 | 0.66 | 0.0% |

Mean flow / w J averaged over the doors 0.36, over the avenues 0.28.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 103.1 | 2322 | 1570 / 753 / 839 | 0.7 | 893.8 | 3.54 | 6.82 | 90% | 86% | 4% | 4.58 |
| straight +x+y (y wing) 1 | 1.20 | 81.5 | 1855 | 1784 / 0 / 183 | 0.7 | 1158.4 | 1.70 | 3.51 | 87% | 73% | 15% | 3.97 |
| straight +x+y (y wing) 2 | 1.20 | 61.0 | 1520 | 1604 / 0 / 32 | 0.7 | 1157.4 | 1.41 | 2.41 | 76% | 66% | 10% | 3.85 |
| straight +x+y (y wing) 3 | 1.20 | 39.4 | 932 | 1107 / 0 / 20 | 0.7 | 1147.2 | 0.98 | 2.41 | 50% | 41% | 9% | 3.68 |
| straight +x+y (y wing) 4 | 1.20 | 18.8 | 376 | 687 / 0 / 19 | 0.7 | 1058.9 | 0.67 | 2.11 | 21% | 17% | 4% | 3.66 |
| straight +x+y (x wing) 0 | 1.20 | 103.1 | 2333 | 1551 / 782 / 997 | 0.7 | 896.7 | 3.72 | 6.12 | 90% | 84% | 6% | 4.40 |
| straight +x+y (x wing) 1 | 1.20 | 81.5 | 1846 | 1783 / 0 / 180 | 0.7 | 1129.0 | 1.74 | 3.71 | 88% | 73% | 15% | 3.88 |
| straight +x+y (x wing) 2 | 1.20 | 61.0 | 1523 | 1616 / 0 / 15 | 0.7 | 1145.3 | 1.42 | 2.31 | 76% | 64% | 11% | 3.82 |
| straight +x+y (x wing) 3 | 1.20 | 39.4 | 938 | 1165 / 0 / 12 | 0.7 | 1149.3 | 1.02 | 2.11 | 47% | 41% | 6% | 3.69 |
| straight +x+y (x wing) 4 | 1.20 | 18.8 | 408 | 672 / 0 / 28 | 0.7 | 1089.5 | 0.64 | 2.41 | 17% | 17% | 0% | 4.07 |
| corner +x+y | 1.20 | 186.0 | 1803 | 476 / 307 / 1378 | 0.7 | 1099.3 | 1.97 | 5.32 | 94% | 66% | 28% | 2.66 |
| straight -x+y (y wing) 0 | 1.20 | 103.1 | 2332 | 1560 / 772 / 950 | 0.7 | 887.0 | 3.70 | 5.72 | 90% | 87% | 3% | 4.47 |
| straight -x+y (y wing) 1 | 1.20 | 81.5 | 1865 | 1798 / 0 / 185 | 0.7 | 1122.0 | 1.77 | 3.91 | 91% | 77% | 14% | 3.67 |
| straight -x+y (y wing) 2 | 1.20 | 61.0 | 1523 | 1628 / 0 / 28 | 0.7 | 1155.4 | 1.43 | 2.61 | 75% | 66% | 9% | 3.77 |
| straight -x+y (y wing) 3 | 1.20 | 39.4 | 935 | 1095 / 0 / 23 | 0.7 | 1159.3 | 0.96 | 2.41 | 47% | 38% | 9% | 3.65 |
| straight -x+y (y wing) 4 | 1.20 | 18.8 | 394 | 659 / 0 / 19 | 0.7 | 1158.4 | 0.59 | 2.51 | 16% | 16% | 0% | 4.00 |
| straight -x+y (x wing) 0 | 1.20 | 103.1 | 2331 | 1558 / 774 / 863 | 0.7 | 884.7 | 3.61 | 5.92 | 90% | 87% | 3% | 4.60 |
| straight -x+y (x wing) 1 | 1.20 | 81.5 | 1860 | 1809 / 0 / 149 | 0.7 | 1097.5 | 1.78 | 3.71 | 90% | 77% | 14% | 4.10 |
| straight -x+y (x wing) 2 | 1.20 | 61.0 | 1530 | 1606 / 0 / 21 | 0.7 | 1130.6 | 1.44 | 2.11 | 78% | 68% | 10% | 3.98 |
| straight -x+y (x wing) 3 | 1.20 | 39.4 | 932 | 1133 / 0 / 22 | 0.7 | 1145.5 | 1.01 | 2.51 | 48% | 39% | 9% | 3.69 |
| straight -x+y (x wing) 4 | 1.20 | 18.8 | 399 | 725 / 0 / 23 | 0.7 | 1136.9 | 0.66 | 2.31 | 17% | 17% | 0% | 4.19 |
| corner -x+y | 1.20 | 186.0 | 1755 | 447 / 293 / 1354 | 0.7 | 1134.4 | 1.85 | 4.21 | 90% | 68% | 22% | 2.71 |
| straight -x-y (y wing) 0 | 1.20 | 103.1 | 2312 | 1550 / 762 / 920 | 0.7 | 856.3 | 3.78 | 6.22 | 88% | 88% | 0% | 4.88 |
| straight -x-y (y wing) 1 | 1.20 | 81.5 | 1873 | 1784 / 0 / 254 | 0.7 | 1091.9 | 1.87 | 3.51 | 91% | 74% | 17% | 3.84 |
| straight -x-y (y wing) 2 | 1.20 | 61.0 | 1526 | 1597 / 0 / 21 | 0.7 | 1147.0 | 1.41 | 2.21 | 77% | 67% | 9% | 3.82 |
| straight -x-y (y wing) 3 | 1.20 | 39.4 | 935 | 1199 / 0 / 20 | 0.7 | 1153.7 | 1.06 | 2.41 | 47% | 39% | 8% | 3.64 |
| straight -x-y (y wing) 4 | 1.20 | 18.8 | 392 | 688 / 0 / 16 | 0.7 | 1160.7 | 0.61 | 2.31 | 19% | 15% | 3% | 3.63 |
| straight -x-y (x wing) 0 | 1.20 | 103.1 | 2315 | 1559 / 756 / 875 | 0.7 | 888.2 | 3.59 | 5.42 | 89% | 86% | 3% | 4.50 |
| straight -x-y (x wing) 1 | 1.20 | 81.5 | 1875 | 1779 / 0 / 258 | 0.7 | 1137.2 | 1.79 | 3.71 | 89% | 72% | 17% | 3.53 |
| straight -x-y (x wing) 2 | 1.20 | 61.0 | 1520 | 1588 / 0 / 24 | 0.7 | 1127.6 | 1.43 | 2.21 | 79% | 68% | 11% | 3.64 |
| straight -x-y (x wing) 3 | 1.20 | 39.4 | 936 | 1168 / 0 / 9 | 0.7 | 1149.0 | 1.02 | 2.31 | 47% | 40% | 7% | 3.73 |
| straight -x-y (x wing) 4 | 1.20 | 18.8 | 415 | 675 / 0 / 30 | 0.7 | 1125.7 | 0.63 | 2.11 | 22% | 17% | 5% | 3.40 |
| corner -x-y | 1.20 | 186.0 | 1757 | 395 / 356 / 1433 | 0.7 | 1136.7 | 1.92 | 4.21 | 90% | 66% | 23% | 2.79 |
| straight +x-y (y wing) 0 | 1.20 | 103.1 | 2318 | 1543 / 775 / 956 | 0.7 | 860.9 | 3.81 | 6.02 | 89% | 89% | 0% | 4.61 |
| straight +x-y (y wing) 1 | 1.20 | 81.5 | 1867 | 1774 / 0 / 230 | 0.7 | 1186.4 | 1.69 | 3.71 | 87% | 72% | 14% | 3.53 |
| straight +x-y (y wing) 2 | 1.20 | 61.0 | 1521 | 1595 / 0 / 23 | 0.7 | 1129.5 | 1.43 | 2.31 | 75% | 65% | 11% | 3.70 |
| straight +x-y (y wing) 3 | 1.20 | 39.4 | 930 | 1212 / 0 / 32 | 0.7 | 1159.3 | 1.07 | 2.51 | 43% | 38% | 5% | 3.92 |
| straight +x-y (y wing) 4 | 1.20 | 18.8 | 396 | 669 / 0 / 35 | 0.7 | 1121.3 | 0.63 | 2.51 | 19% | 16% | 4% | 3.65 |
| straight +x-y (x wing) 0 | 1.20 | 103.1 | 2316 | 1570 / 747 / 812 | 0.7 | 891.0 | 3.51 | 6.42 | 90% | 87% | 3% | 4.55 |
| straight +x-y (x wing) 1 | 1.20 | 81.5 | 1876 | 1772 / 0 / 266 | 0.7 | 1100.5 | 1.85 | 4.51 | 91% | 72% | 19% | 3.53 |
| straight +x-y (x wing) 2 | 1.20 | 61.0 | 1513 | 1584 / 0 / 32 | 0.7 | 1166.6 | 1.39 | 2.21 | 75% | 63% | 12% | 3.76 |
| straight +x-y (x wing) 3 | 1.20 | 39.4 | 920 | 1219 / 0 / 13 | 0.7 | 1171.5 | 1.05 | 2.21 | 42% | 38% | 4% | 3.90 |
| straight +x-y (x wing) 4 | 1.20 | 18.8 | 385 | 609 / 0 / 31 | 0.7 | 1163.7 | 0.55 | 2.21 | 27% | 15% | 12% | 2.68 |
| corner +x-y | 1.20 | 186.0 | 1814 | 421 / 367 / 1498 | 0.7 | 1139.7 | 2.01 | 4.41 | 90% | 63% | 27% | 2.82 |

The last agent out (agent 56319, t100 1189.4 s): last gangway straight +x-y (y wing) 1, exit door +x-y (y wall) 1. The gangway that cleared last: straight +x-y (y wing) 1 at 1186.4 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 8804 | 7800.4 | 7.06 | 1177.8 / 1096.8 / 1034.7 | 1079.0 / 1064.0 / 1011.8 | 5257551.0 | 10843254 | 0.202 |
| gangway | 3792 | 3512.9 | 7.06 | 1176.8 / 1096.8 / 1034.7 | 1079.0 / 1064.0 / 1011.8 | 5257551.0 | 10100586 | 0.131 |
| walkway | 276 | 257.4 | 4.05 | 625.5 / 394.8 / 0.0 | 419.1 / 287.2 / 0.0 | 0.0 | 80403 | 0.652 |
| avenue | 1920 | 1801.4 | 2.11 | 794.3 / 0.0 / 0.0 | 560.8 / 0.0 / 0.0 | 0.0 | 445972 | 1.334 |
| exit | 4 | 2.0 | 0.00 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 0 | - |
| concourse | 2812 | 2226.8 | 3.12 | 1160.9 / 83.6 / 0.0 | 956.6 / 20.3 / 0.0 | 0.0 | 216293 | 1.044 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 25392 | 16030.4 | 7.72 | 1051.9 / 1031.1 / 1015.7 | 1034.4 / 1031.1 / 1005.5 | 6721817.2 | 16916776 | 0.029 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 208 x 208 from (-104, -104) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 34.5 | 34.5 | gangway | 1.00 | 5.96 | 1046.3 | 1038.6 | 1011.8 | 5818.9 | 0.008 |
| 2 | 35.5 | 35.5 | gangway | 1.00 | 5.83 | 1052.1 | 1040.0 | 994.2 | 5688.4 | 0.009 |
| 3 | -35.5 | 35.5 | gangway | 1.00 | 5.97 | 1049.4 | 1038.1 | 973.5 | 5598.7 | 0.009 |
| 4 | -34.5 | 34.5 | gangway | 1.00 | 5.79 | 1043.7 | 1036.7 | 996.8 | 5597.6 | 0.009 |
| 5 | -35.5 | -35.5 | gangway | 1.00 | 5.83 | 1053.3 | 1045.6 | 981.4 | 5531.1 | 0.008 |
| 6 | -38.5 | 38.5 | gangway | 1.00 | 5.97 | 1063.4 | 1055.6 | 950.1 | 5493.2 | 0.016 |
| 7 | 35.5 | -35.5 | gangway | 1.00 | 5.77 | 1061.7 | 1052.6 | 989.3 | 5487.9 | 0.010 |
| 8 | -39.5 | 39.5 | gangway | 1.00 | 5.85 | 1067.3 | 1061.0 | 943.1 | 5372.9 | 0.022 |
| 9 | 36.5 | -36.5 | gangway | 1.00 | 5.79 | 1067.3 | 1060.1 | 962.5 | 5341.3 | 0.011 |
| 10 | -36.5 | -36.5 | gangway | 1.00 | 5.69 | 1057.7 | 1049.1 | 966.2 | 5317.9 | 0.012 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -36.5 | 38.5 | seat row | 0.50 | 7.42 | 1019.5 | 1019.0 | 1004.1 | 3669.2 | 0.005 |
| 2 | 36.5 | -38.5 | seat row | 0.50 | 7.44 | 1025.0 | 1018.1 | 1003.3 | 3643.5 | 0.006 |
| 3 | -36.5 | -38.5 | seat row | 0.50 | 7.30 | 1028.3 | 1025.3 | 1005.5 | 3576.5 | 0.006 |
| 4 | -38.5 | 36.5 | seat row | 0.50 | 7.33 | 1022.9 | 1008.3 | 986.6 | 3543.0 | 0.005 |
| 5 | 38.5 | -36.5 | seat row | 0.50 | 7.16 | 1022.3 | 1019.7 | 1001.9 | 3500.2 | 0.006 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 8008; agent-steps of seated agents on another row's clearway: 1911544.

## Deposit check

Person-seconds deposited: 27765896.4, of them in excluded cells: 5866.393.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 5938609 overlapping pair-steps: p99 0.0032, max 0.1343 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0032 max 0.1343; venue-geometry 9: p99 0.0021 max 0.0021 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00773 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 51 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.50 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 3834 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
