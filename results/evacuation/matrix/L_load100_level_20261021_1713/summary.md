# Experiment `L_load100_level`

**Task 5.9 stage 4 (model variants): venue L, 100% load, queue-aware exit choice, level walking speed**

Venue L (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (4000 x 4000), cache key a2f3aaf59c2252b7, content hash 022d17b202313d70). 63424 agents on 100% of the 63424 seats (spawnSeatedCrowd, seed 1337), buffer N = 65536, 5651 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, level speed** (exit choice: 7129946 evaluations, 425321 switches, 0 forced choices).
Capacity: **within design capacity** (the L venue's design capacity 63424, jam capacity 171923: 23822.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-21T17:13:00, 995.0 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1807 | 316.1 |
| t90 | 3649 | 638.2 |
| t100 | 5651 | 988.4 |

t_p: the step by which ceil(p x 63424) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 1487 | 0 | 70.5 | 734.6 | 23.7 | 25.5 | 77.0-86.9 |
| -x | 5.66 | 1493 | 0 | 70.5 | 738.6 | 23.7 | 26.6 | 76.8-86.8 |
| +y | 5.66 | 1483 | 0 | 70.7 | 743.9 | 23.3 | 26.6 | 257.6-267.6 |
| -y | 5.66 | 1488 | 0 | 70.5 | 737.4 | 23.6 | 26.6 | 76.8-86.8 |
| door +x+y (y wall) 0 | 2.30 | 1698 | 2577 | 4.2 | 742.8 | 60.0 | 81.1 | 638.8-648.7 |
| door +x+y (y wall) 1 | 2.30 | 1824 | 2137 | 4.2 | 842.2 | 56.8 | 75.9 | 343.2-353.1 |
| door +x+y (y wall) 2 | 2.30 | 1656 | 1594 | 4.2 | 877.7 | 49.4 | 78.5 | 163.4-173.3 |
| door +x+y (y wall) 3 | 2.30 | 1101 | 1045 | 4.2 | 853.5 | 33.8 | 78.5 | 249.6-259.6 |
| door +x+y (y wall) 4 | 2.30 | 670 | 513 | 4.2 | 872.6 | 20.1 | 89.0 | 212.5-222.5 |
| door +x+y (x wall) 0 | 2.30 | 1679 | 2577 | 4.2 | 746.2 | 59.0 | 78.5 | 545.5-555.5 |
| door +x+y (x wall) 1 | 2.30 | 1844 | 2137 | 4.2 | 842.4 | 57.4 | 75.9 | 53.9-63.8 |
| door +x+y (x wall) 2 | 2.30 | 1618 | 1594 | 4.2 | 876.8 | 48.4 | 81.1 | 557.1-567.0 |
| door +x+y (x wall) 3 | 2.30 | 1104 | 1045 | 4.2 | 867.4 | 33.4 | 78.5 | 222.1-232.1 |
| door +x+y (x wall) 4 | 2.30 | 714 | 513 | 4.4 | 867.0 | 21.6 | 73.3 | 21.5-31.5 |
| door +x+y (corner) | 2.30 | 463 | 124 | 5.6 | 730.9 | 16.6 | 70.6 | 119.6-129.6 |
| door -x+y (y wall) 0 | 2.30 | 1686 | 2577 | 4.2 | 753.1 | 58.7 | 78.5 | 650.8-660.8 |
| door -x+y (y wall) 1 | 2.30 | 1848 | 2137 | 4.2 | 840.1 | 57.7 | 75.9 | 580.2-590.1 |
| door -x+y (y wall) 2 | 2.30 | 1654 | 1594 | 4.2 | 863.5 | 50.2 | 81.1 | 203.6-213.6 |
| door -x+y (y wall) 3 | 2.30 | 1299 | 1045 | 4.2 | 834.1 | 40.8 | 75.9 | 309.1-319.0 |
| door -x+y (y wall) 4 | 2.30 | 524 | 513 | 4.4 | 823.1 | 16.7 | 78.5 | 114.2-124.2 |
| door -x+y (x wall) 0 | 2.30 | 1702 | 2577 | 4.2 | 746.0 | 59.8 | 78.5 | 373.3-383.2 |
| door -x+y (x wall) 1 | 2.30 | 1802 | 2137 | 4.2 | 830.6 | 56.9 | 75.9 | 257.8-267.8 |
| door -x+y (x wall) 2 | 2.30 | 1627 | 1594 | 4.2 | 856.2 | 49.8 | 78.5 | 557.4-567.4 |
| door -x+y (x wall) 3 | 2.30 | 1275 | 1045 | 4.2 | 853.9 | 39.1 | 78.5 | 289.8-299.8 |
| door -x+y (x wall) 4 | 2.30 | 625 | 513 | 4.2 | 845.5 | 19.4 | 73.3 | 24.1-34.1 |
| door -x+y (corner) | 2.30 | 329 | 124 | 5.6 | 641.2 | 13.5 | 68.0 | 28.2-38.1 |
| door -x-y (y wall) 0 | 2.30 | 1689 | 2577 | 4.2 | 743.5 | 59.6 | 75.9 | 98.6-108.6 |
| door -x-y (y wall) 1 | 2.30 | 1858 | 2137 | 4.2 | 962.3 | 50.6 | 75.9 | 88.2-98.1 |
| door -x-y (y wall) 2 | 2.30 | 1624 | 1594 | 4.2 | 971.4 | 43.8 | 75.9 | 255.9-265.9 |
| door -x-y (y wall) 3 | 2.30 | 1137 | 1045 | 4.2 | 988.4 | 30.1 | 75.9 | 24.1-34.1 |
| door -x-y (y wall) 4 | 2.30 | 741 | 513 | 4.2 | 683.0 | 28.5 | 75.9 | 45.3-55.3 |
| door -x-y (x wall) 0 | 2.30 | 1680 | 2577 | 4.2 | 740.0 | 59.5 | 78.5 | 401.9-411.9 |
| door -x-y (x wall) 1 | 2.30 | 1857 | 2137 | 4.2 | 908.6 | 53.6 | 78.5 | 12.9-22.9 |
| door -x-y (x wall) 2 | 2.30 | 1597 | 1594 | 4.2 | 983.2 | 42.5 | 81.1 | 540.5-550.4 |
| door -x-y (x wall) 3 | 2.30 | 1082 | 1045 | 4.2 | 968.1 | 29.3 | 81.1 | 315.7-325.7 |
| door -x-y (x wall) 4 | 2.30 | 704 | 513 | 4.4 | 904.3 | 20.4 | 75.9 | 48.1-58.1 |
| door -x-y (corner) | 2.30 | 392 | 124 | 5.6 | 719.6 | 14.3 | 68.0 | 21.7-31.7 |
| door +x-y (y wall) 0 | 2.30 | 1681 | 2577 | 4.2 | 745.5 | 59.1 | 78.5 | 607.1-617.1 |
| door +x-y (y wall) 1 | 2.30 | 1833 | 2137 | 4.2 | 907.6 | 52.9 | 75.9 | 140.1-150.1 |
| door +x-y (y wall) 2 | 2.30 | 1636 | 1594 | 4.2 | 920.7 | 46.6 | 75.9 | 18.7-28.7 |
| door +x-y (y wall) 3 | 2.30 | 1364 | 1045 | 4.2 | 908.6 | 39.3 | 75.9 | 300.5-310.5 |
| door +x-y (y wall) 4 | 2.30 | 516 | 513 | 4.4 | 907.8 | 14.9 | 73.3 | 19.8-29.7 |
| door +x-y (x wall) 0 | 2.30 | 1699 | 2577 | 4.2 | 744.9 | 59.8 | 78.5 | 428.9-438.8 |
| door +x-y (x wall) 1 | 2.30 | 1851 | 2137 | 4.2 | 881.7 | 55.0 | 75.9 | 12.4-22.4 |
| door +x-y (x wall) 2 | 2.30 | 1637 | 1594 | 4.2 | 918.1 | 46.7 | 78.5 | 434.5-444.4 |
| door +x-y (x wall) 3 | 2.30 | 1351 | 1045 | 4.2 | 928.2 | 38.1 | 73.3 | 13.1-23.1 |
| door +x-y (x wall) 4 | 2.30 | 495 | 513 | 4.4 | 932.4 | 13.9 | 75.9 | 123.0-132.9 |
| door +x-y (corner) | 2.30 | 307 | 124 | 5.6 | 698.4 | 11.6 | 70.6 | 79.8-89.7 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (2.30 m; a corner door's: the gap between its wall ends, 2.30 m); agents are removed past the outer wall's outer face (92.71 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 1487 | 2.3% | 19.1% |
| -x | avenue | 5.66 | 1493 | 2.4% | 19.2% |
| +y | avenue | 5.66 | 1483 | 2.3% | 19.0% |
| -y | avenue | 5.66 | 1488 | 2.3% | 19.1% |
| door +x+y (y wall) 0 | door | 2.30 | 1698 | 2.7% | 53.6% |
| door +x+y (y wall) 1 | door | 2.30 | 1824 | 2.9% | 57.6% |
| door +x+y (y wall) 2 | door | 2.30 | 1656 | 2.6% | 52.3% |
| door +x+y (y wall) 3 | door | 2.30 | 1101 | 1.7% | 34.8% |
| door +x+y (y wall) 4 | door | 2.30 | 670 | 1.1% | 21.2% |
| door +x+y (x wall) 0 | door | 2.30 | 1679 | 2.6% | 53.0% |
| door +x+y (x wall) 1 | door | 2.30 | 1844 | 2.9% | 58.2% |
| door +x+y (x wall) 2 | door | 2.30 | 1618 | 2.6% | 51.1% |
| door +x+y (x wall) 3 | door | 2.30 | 1104 | 1.7% | 34.9% |
| door +x+y (x wall) 4 | door | 2.30 | 714 | 1.1% | 22.5% |
| door +x+y (corner) | door | 2.30 | 463 | 0.7% | 14.6% |
| door -x+y (y wall) 0 | door | 2.30 | 1686 | 2.7% | 53.2% |
| door -x+y (y wall) 1 | door | 2.30 | 1848 | 2.9% | 58.3% |
| door -x+y (y wall) 2 | door | 2.30 | 1654 | 2.6% | 52.2% |
| door -x+y (y wall) 3 | door | 2.30 | 1299 | 2.0% | 41.0% |
| door -x+y (y wall) 4 | door | 2.30 | 524 | 0.8% | 16.5% |
| door -x+y (x wall) 0 | door | 2.30 | 1702 | 2.7% | 53.7% |
| door -x+y (x wall) 1 | door | 2.30 | 1802 | 2.8% | 56.9% |
| door -x+y (x wall) 2 | door | 2.30 | 1627 | 2.6% | 51.4% |
| door -x+y (x wall) 3 | door | 2.30 | 1275 | 2.0% | 40.3% |
| door -x+y (x wall) 4 | door | 2.30 | 625 | 1.0% | 19.7% |
| door -x+y (corner) | door | 2.30 | 329 | 0.5% | 10.4% |
| door -x-y (y wall) 0 | door | 2.30 | 1689 | 2.7% | 53.3% |
| door -x-y (y wall) 1 | door | 2.30 | 1858 | 2.9% | 58.7% |
| door -x-y (y wall) 2 | door | 2.30 | 1624 | 2.6% | 51.3% |
| door -x-y (y wall) 3 | door | 2.30 | 1137 | 1.8% | 35.9% |
| door -x-y (y wall) 4 | door | 2.30 | 741 | 1.2% | 23.4% |
| door -x-y (x wall) 0 | door | 2.30 | 1680 | 2.6% | 53.0% |
| door -x-y (x wall) 1 | door | 2.30 | 1857 | 2.9% | 58.6% |
| door -x-y (x wall) 2 | door | 2.30 | 1597 | 2.5% | 50.4% |
| door -x-y (x wall) 3 | door | 2.30 | 1082 | 1.7% | 34.2% |
| door -x-y (x wall) 4 | door | 2.30 | 704 | 1.1% | 22.2% |
| door -x-y (corner) | door | 2.30 | 392 | 0.6% | 12.4% |
| door +x-y (y wall) 0 | door | 2.30 | 1681 | 2.7% | 53.1% |
| door +x-y (y wall) 1 | door | 2.30 | 1833 | 2.9% | 57.9% |
| door +x-y (y wall) 2 | door | 2.30 | 1636 | 2.6% | 51.6% |
| door +x-y (y wall) 3 | door | 2.30 | 1364 | 2.2% | 43.1% |
| door +x-y (y wall) 4 | door | 2.30 | 516 | 0.8% | 16.3% |
| door +x-y (x wall) 0 | door | 2.30 | 1699 | 2.7% | 53.6% |
| door +x-y (x wall) 1 | door | 2.30 | 1851 | 2.9% | 58.4% |
| door +x-y (x wall) 2 | door | 2.30 | 1637 | 2.6% | 51.7% |
| door +x-y (x wall) 3 | door | 2.30 | 1351 | 2.1% | 42.7% |
| door +x-y (x wall) 4 | door | 2.30 | 495 | 0.8% | 15.6% |
| door +x-y (corner) | door | 2.30 | 307 | 0.5% | 9.7% |
| **doors (44)** | door | 101.20 | 57473 | 90.6% | |
| **avenues (4)** | avenue | 22.64 | 5951 | 9.4% | |

**Unused exit width: 0.0 of 123.8 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 988.4 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 37.2%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 2309 | 3.6% | 2309 | 3.6% |
| straight +x+y (y wing) 1 | straight | yes | 1890 | 3.0% | 1844 | 2.9% |
| straight +x+y (y wing) 2 | straight | yes | 1688 | 2.7% | 1680 | 2.6% |
| straight +x+y (y wing) 3 | straight | yes | 1135 | 1.8% | 1126 | 1.8% |
| straight +x+y (y wing) 4 | straight | yes | 637 | 1.0% | 621 | 1.0% |
| straight +x+y (x wing) 0 | straight | yes | 2307 | 3.6% | 2307 | 3.6% |
| straight +x+y (x wing) 1 | straight | yes | 1899 | 3.0% | 1862 | 2.9% |
| straight +x+y (x wing) 2 | straight | yes | 1673 | 2.6% | 1669 | 2.6% |
| straight +x+y (x wing) 3 | straight | yes | 1111 | 1.8% | 1105 | 1.7% |
| straight +x+y (x wing) 4 | straight | yes | 683 | 1.1% | 662 | 1.0% |
| corner +x+y | corner | yes | 1940 | 3.1% | 671 | 1.1% |
| straight -x+y (y wing) 0 | straight | yes | 2283 | 3.6% | 2283 | 3.6% |
| straight -x+y (y wing) 1 | straight | yes | 1922 | 3.0% | 1863 | 2.9% |
| straight -x+y (y wing) 2 | straight | yes | 1658 | 2.6% | 1653 | 2.6% |
| straight -x+y (y wing) 3 | straight | yes | 1306 | 2.1% | 1306 | 2.1% |
| straight -x+y (y wing) 4 | straight | yes | 530 | 0.8% | 516 | 0.8% |
| straight -x+y (x wing) 0 | straight | yes | 2298 | 3.6% | 2298 | 3.6% |
| straight -x+y (x wing) 1 | straight | yes | 1898 | 3.0% | 1823 | 2.9% |
| straight -x+y (x wing) 2 | straight | yes | 1644 | 2.6% | 1628 | 2.6% |
| straight -x+y (x wing) 3 | straight | yes | 1294 | 2.0% | 1291 | 2.0% |
| straight -x+y (x wing) 4 | straight | yes | 620 | 1.0% | 608 | 1.0% |
| corner -x+y | corner | yes | 1941 | 3.1% | 587 | 0.9% |
| straight -x-y (y wing) 0 | straight | yes | 2283 | 3.6% | 2283 | 3.6% |
| straight -x-y (y wing) 1 | straight | yes | 1935 | 3.1% | 1875 | 3.0% |
| straight -x-y (y wing) 2 | straight | yes | 1653 | 2.6% | 1641 | 2.6% |
| straight -x-y (y wing) 3 | straight | yes | 1171 | 1.8% | 1157 | 1.8% |
| straight -x-y (y wing) 4 | straight | yes | 711 | 1.1% | 698 | 1.1% |
| straight -x-y (x wing) 0 | straight | yes | 2305 | 3.6% | 2305 | 3.6% |
| straight -x-y (x wing) 1 | straight | yes | 1934 | 3.0% | 1878 | 3.0% |
| straight -x-y (x wing) 2 | straight | yes | 1623 | 2.6% | 1617 | 2.5% |
| straight -x-y (x wing) 3 | straight | yes | 1108 | 1.7% | 1099 | 1.7% |
| straight -x-y (x wing) 4 | straight | yes | 667 | 1.1% | 660 | 1.0% |
| corner -x-y | corner | yes | 1920 | 3.0% | 643 | 1.0% |
| straight +x-y (y wing) 0 | straight | yes | 2306 | 3.6% | 2306 | 3.6% |
| straight +x-y (y wing) 1 | straight | yes | 1902 | 3.0% | 1850 | 2.9% |
| straight +x-y (y wing) 2 | straight | yes | 1668 | 2.6% | 1659 | 2.6% |
| straight +x-y (y wing) 3 | straight | yes | 1345 | 2.1% | 1344 | 2.1% |
| straight +x-y (y wing) 4 | straight | yes | 519 | 0.8% | 513 | 0.8% |
| straight +x-y (x wing) 0 | straight | yes | 2290 | 3.6% | 2288 | 3.6% |
| straight +x-y (x wing) 1 | straight | yes | 1920 | 3.0% | 1868 | 2.9% |
| straight +x-y (x wing) 2 | straight | yes | 1642 | 2.6% | 1637 | 2.6% |
| straight +x-y (x wing) 3 | straight | yes | 1352 | 2.1% | 1351 | 2.1% |
| straight +x-y (x wing) 4 | straight | yes | 522 | 0.8% | 494 | 0.8% |
| corner +x-y | corner | yes | 1857 | 2.9% | 546 | 0.9% |
| **straight (40)** | | | 61641 | | 60977 | 96.1% |
| **corner (4)** | | | 7658 | | 2447 | 3.9% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 1487 | 70.5 | 734.6 | 0.28 | 0.31 | 0.0% |
| -x | 1493 | 70.5 | 738.6 | 0.28 | 0.32 | 0.0% |
| +y | 1483 | 70.7 | 743.9 | 0.28 | 0.32 | 0.0% |
| -y | 1488 | 70.5 | 737.4 | 0.28 | 0.32 | 0.0% |
| door +x+y (y wall) 0 | 1698 | 4.2 | 742.8 | 0.72 | 0.97 | 26.7% |
| door +x+y (y wall) 1 | 1824 | 4.2 | 842.2 | 0.68 | 0.91 | 14.1% |
| door +x+y (y wall) 2 | 1656 | 4.2 | 877.7 | 0.59 | 0.94 | 18.0% |
| door +x+y (y wall) 3 | 1101 | 4.2 | 853.5 | 0.40 | 0.94 | 9.3% |
| door +x+y (y wall) 4 | 670 | 4.2 | 872.6 | 0.24 | 1.06 | 10.2% |
| door +x+y (x wall) 0 | 1679 | 4.2 | 746.2 | 0.71 | 0.94 | 22.7% |
| door +x+y (x wall) 1 | 1844 | 4.2 | 842.4 | 0.69 | 0.91 | 21.2% |
| door +x+y (x wall) 2 | 1618 | 4.2 | 876.8 | 0.58 | 0.97 | 18.2% |
| door +x+y (x wall) 3 | 1104 | 4.2 | 867.4 | 0.40 | 0.94 | 11.5% |
| door +x+y (x wall) 4 | 714 | 4.4 | 867.0 | 0.26 | 0.88 | 3.4% |
| door +x+y (corner) | 463 | 5.6 | 730.9 | 0.20 | 0.85 | 1.4% |
| door -x+y (y wall) 0 | 1686 | 4.2 | 753.1 | 0.70 | 0.94 | 21.1% |
| door -x+y (y wall) 1 | 1848 | 4.2 | 840.1 | 0.69 | 0.91 | 27.1% |
| door -x+y (y wall) 2 | 1654 | 4.2 | 863.5 | 0.60 | 0.97 | 14.9% |
| door -x+y (y wall) 3 | 1299 | 4.2 | 834.1 | 0.49 | 0.91 | 10.7% |
| door -x+y (y wall) 4 | 524 | 4.4 | 823.1 | 0.20 | 0.94 | 3.6% |
| door -x+y (x wall) 0 | 1702 | 4.2 | 746.0 | 0.72 | 0.94 | 32.0% |
| door -x+y (x wall) 1 | 1802 | 4.2 | 830.6 | 0.68 | 0.91 | 16.7% |
| door -x+y (x wall) 2 | 1627 | 4.2 | 856.2 | 0.60 | 0.94 | 15.1% |
| door -x+y (x wall) 3 | 1275 | 4.2 | 853.9 | 0.47 | 0.94 | 9.3% |
| door -x+y (x wall) 4 | 625 | 4.2 | 845.5 | 0.23 | 0.88 | 3.5% |
| door -x+y (corner) | 329 | 5.6 | 641.2 | 0.16 | 0.81 | 0.0% |
| door -x-y (y wall) 0 | 1689 | 4.2 | 743.5 | 0.71 | 0.91 | 22.7% |
| door -x-y (y wall) 1 | 1858 | 4.2 | 962.3 | 0.60 | 0.91 | 20.6% |
| door -x-y (y wall) 2 | 1624 | 4.2 | 971.4 | 0.52 | 0.91 | 13.3% |
| door -x-y (y wall) 3 | 1137 | 4.2 | 988.4 | 0.36 | 0.91 | 9.0% |
| door -x-y (y wall) 4 | 741 | 4.2 | 683.0 | 0.34 | 0.91 | 7.2% |
| door -x-y (x wall) 0 | 1680 | 4.2 | 740.0 | 0.71 | 0.94 | 32.0% |
| door -x-y (x wall) 1 | 1857 | 4.2 | 908.6 | 0.64 | 0.94 | 23.9% |
| door -x-y (x wall) 2 | 1597 | 4.2 | 983.2 | 0.51 | 0.97 | 17.2% |
| door -x-y (x wall) 3 | 1082 | 4.2 | 968.1 | 0.35 | 0.97 | 7.1% |
| door -x-y (x wall) 4 | 704 | 4.4 | 904.3 | 0.24 | 0.91 | 4.4% |
| door -x-y (corner) | 392 | 5.6 | 719.6 | 0.17 | 0.81 | 0.0% |
| door +x-y (y wall) 0 | 1681 | 4.2 | 745.5 | 0.71 | 0.94 | 22.7% |
| door +x-y (y wall) 1 | 1833 | 4.2 | 907.6 | 0.63 | 0.91 | 22.8% |
| door +x-y (y wall) 2 | 1636 | 4.2 | 920.7 | 0.56 | 0.91 | 12.9% |
| door +x-y (y wall) 3 | 1364 | 4.2 | 908.6 | 0.47 | 0.91 | 12.0% |
| door +x-y (y wall) 4 | 516 | 4.4 | 907.8 | 0.18 | 0.88 | 5.4% |
| door +x-y (x wall) 0 | 1699 | 4.2 | 744.9 | 0.72 | 0.94 | 30.7% |
| door +x-y (x wall) 1 | 1851 | 4.2 | 881.7 | 0.66 | 0.91 | 20.2% |
| door +x-y (x wall) 2 | 1637 | 4.2 | 918.1 | 0.56 | 0.94 | 19.4% |
| door +x-y (x wall) 3 | 1351 | 4.2 | 928.2 | 0.46 | 0.88 | 8.5% |
| door +x-y (x wall) 4 | 495 | 4.4 | 932.4 | 0.17 | 0.91 | 4.3% |
| door +x-y (corner) | 307 | 5.6 | 698.4 | 0.14 | 0.85 | 1.4% |

Mean flow / w J averaged over the doors 0.49, over the avenues 0.28.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 103.1 | 2309 | 1678 / 631 / 626 | 0.7 | 691.4 | 4.25 | 6.12 | 93% | 84% | 9% | 4.35 |
| straight +x+y (y wing) 1 | 1.20 | 81.5 | 1875 | 1844 / 0 / 96 | 0.7 | 839.6 | 2.31 | 3.61 | 93% | 75% | 18% | 3.70 |
| straight +x+y (y wing) 2 | 1.20 | 61.0 | 1507 | 1680 / 0 / 11 | 0.7 | 875.1 | 1.93 | 3.01 | 69% | 56% | 14% | 3.64 |
| straight +x+y (y wing) 3 | 1.20 | 39.4 | 950 | 1126 / 0 / 13 | 0.7 | 850.9 | 1.34 | 2.71 | 56% | 35% | 21% | 2.87 |
| straight +x+y (y wing) 4 | 1.20 | 18.8 | 409 | 621 / 0 / 46 | 0.7 | 870.0 | 0.77 | 2.91 | 17% | 14% | 3% | 3.74 |
| straight +x+y (x wing) 0 | 1.20 | 103.1 | 2307 | 1661 / 647 / 658 | 0.7 | 699.5 | 4.24 | 6.12 | 92% | 83% | 8% | 4.21 |
| straight +x+y (x wing) 1 | 1.20 | 81.5 | 1873 | 1862 / 0 / 121 | 0.7 | 839.7 | 2.36 | 3.71 | 93% | 74% | 19% | 3.67 |
| straight +x+y (x wing) 2 | 1.20 | 61.0 | 1519 | 1669 / 0 / 13 | 0.7 | 874.2 | 1.93 | 3.01 | 69% | 59% | 10% | 3.73 |
| straight +x+y (x wing) 3 | 1.20 | 39.4 | 939 | 1105 / 0 / 22 | 0.7 | 864.7 | 1.30 | 2.91 | 46% | 34% | 11% | 3.48 |
| straight +x+y (x wing) 4 | 1.20 | 18.8 | 393 | 662 / 0 / 29 | 0.7 | 864.4 | 0.80 | 3.01 | 18% | 14% | 5% | 3.42 |
| corner +x+y | 1.20 | 186.0 | 1775 | 463 / 208 / 1401 | 0.7 | 859.7 | 2.41 | 6.12 | 92% | 66% | 26% | 2.51 |
| straight -x+y (y wing) 0 | 1.20 | 103.1 | 2283 | 1673 / 612 / 666 | 0.7 | 711.7 | 4.15 | 6.42 | 90% | 85% | 6% | 4.44 |
| straight -x+y (y wing) 1 | 1.20 | 81.5 | 1906 | 1863 / 0 / 125 | 0.7 | 837.5 | 2.38 | 4.21 | 94% | 76% | 18% | 3.66 |
| straight -x+y (y wing) 2 | 1.20 | 61.0 | 1525 | 1653 / 0 / 8 | 0.7 | 860.9 | 1.93 | 2.81 | 72% | 59% | 14% | 3.65 |
| straight -x+y (y wing) 3 | 1.20 | 39.4 | 946 | 1306 / 0 / 6 | 0.7 | 831.5 | 1.58 | 2.81 | 65% | 35% | 31% | 2.71 |
| straight -x+y (y wing) 4 | 1.20 | 18.8 | 400 | 516 / 0 / 16 | 0.7 | 820.5 | 0.65 | 2.91 | 23% | 16% | 7% | 3.14 |
| straight -x+y (x wing) 0 | 1.20 | 103.1 | 2298 | 1681 / 618 / 561 | 0.7 | 693.2 | 4.13 | 6.82 | 93% | 86% | 7% | 4.28 |
| straight -x+y (x wing) 1 | 1.20 | 81.5 | 1883 | 1823 / 0 / 152 | 0.7 | 828.0 | 2.39 | 4.01 | 93% | 75% | 18% | 3.58 |
| straight -x+y (x wing) 2 | 1.20 | 61.0 | 1500 | 1628 / 0 / 26 | 0.7 | 853.5 | 1.94 | 3.11 | 70% | 56% | 14% | 3.65 |
| straight -x+y (x wing) 3 | 1.20 | 39.4 | 981 | 1291 / 0 / 20 | 0.7 | 851.3 | 1.54 | 2.71 | 62% | 35% | 27% | 2.74 |
| straight -x+y (x wing) 4 | 1.20 | 18.8 | 416 | 608 / 0 / 16 | 0.7 | 842.9 | 0.74 | 2.71 | 20% | 16% | 4% | 3.65 |
| corner -x+y | 1.20 | 186.0 | 1718 | 329 / 258 / 1419 | 0.7 | 832.6 | 2.41 | 5.52 | 95% | 70% | 25% | 2.77 |
| straight -x-y (y wing) 0 | 1.20 | 103.1 | 2283 | 1678 / 605 / 516 | 0.7 | 696.8 | 4.02 | 6.12 | 93% | 86% | 7% | 4.30 |
| straight -x-y (y wing) 1 | 1.20 | 81.5 | 1918 | 1875 / 0 / 138 | 0.7 | 959.7 | 2.10 | 4.51 | 95% | 65% | 30% | 3.15 |
| straight -x-y (y wing) 2 | 1.20 | 61.0 | 1507 | 1641 / 0 / 20 | 0.7 | 968.8 | 1.72 | 3.01 | 65% | 50% | 15% | 3.42 |
| straight -x-y (y wing) 3 | 1.20 | 39.4 | 957 | 1157 / 0 / 17 | 0.7 | 985.8 | 1.19 | 2.81 | 42% | 30% | 12% | 3.24 |
| straight -x-y (y wing) 4 | 1.20 | 18.8 | 417 | 698 / 0 / 13 | 0.7 | 680.4 | 1.05 | 3.01 | 23% | 19% | 4% | 3.71 |
| straight -x-y (x wing) 0 | 1.20 | 103.1 | 2305 | 1666 / 639 / 559 | 0.7 | 692.6 | 4.14 | 6.52 | 93% | 84% | 9% | 4.17 |
| straight -x-y (x wing) 1 | 1.20 | 81.5 | 1910 | 1878 / 0 / 151 | 0.7 | 906.0 | 2.24 | 4.41 | 95% | 69% | 25% | 3.37 |
| straight -x-y (x wing) 2 | 1.20 | 61.0 | 1511 | 1617 / 0 / 26 | 0.7 | 980.5 | 1.68 | 3.01 | 67% | 53% | 14% | 3.56 |
| straight -x-y (x wing) 3 | 1.20 | 39.4 | 934 | 1099 / 0 / 13 | 0.7 | 965.5 | 1.15 | 2.91 | 45% | 33% | 12% | 3.19 |
| straight -x-y (x wing) 4 | 1.20 | 18.8 | 393 | 660 / 0 / 11 | 0.7 | 901.6 | 0.74 | 2.81 | 24% | 13% | 11% | 2.68 |
| corner -x-y | 1.20 | 186.0 | 1721 | 392 / 251 / 1368 | 0.7 | 964.1 | 2.09 | 5.42 | 90% | 51% | 39% | 2.40 |
| straight +x-y (y wing) 0 | 1.20 | 103.1 | 2306 | 1664 / 644 / 638 | 0.7 | 684.8 | 4.31 | 6.52 | 93% | 87% | 6% | 4.37 |
| straight +x-y (y wing) 1 | 1.20 | 81.5 | 1883 | 1850 / 0 / 110 | 0.7 | 905.0 | 2.17 | 3.81 | 95% | 70% | 24% | 3.36 |
| straight +x-y (y wing) 2 | 1.20 | 61.0 | 1526 | 1659 / 0 / 17 | 0.7 | 918.1 | 1.83 | 2.91 | 68% | 55% | 13% | 3.65 |
| straight +x-y (y wing) 3 | 1.20 | 39.4 | 974 | 1344 / 0 / 6 | 0.7 | 906.0 | 1.49 | 2.91 | 63% | 32% | 31% | 2.60 |
| straight +x-y (y wing) 4 | 1.20 | 18.8 | 405 | 513 / 0 / 16 | 0.7 | 905.1 | 0.58 | 2.91 | 22% | 14% | 8% | 2.93 |
| straight +x-y (x wing) 0 | 1.20 | 103.1 | 2290 | 1683 / 606 / 587 | 0.7 | 686.5 | 4.19 | 6.82 | 93% | 87% | 6% | 4.37 |
| straight +x-y (x wing) 1 | 1.20 | 81.5 | 1899 | 1868 / 0 / 146 | 0.7 | 879.1 | 2.29 | 4.31 | 92% | 71% | 21% | 3.47 |
| straight +x-y (x wing) 2 | 1.20 | 61.0 | 1508 | 1637 / 0 / 19 | 0.7 | 915.5 | 1.81 | 2.91 | 67% | 54% | 13% | 3.70 |
| straight +x-y (x wing) 3 | 1.20 | 39.4 | 990 | 1351 / 0 / 5 | 0.7 | 925.6 | 1.47 | 2.91 | 57% | 32% | 25% | 2.78 |
| straight +x-y (x wing) 4 | 1.20 | 18.8 | 401 | 494 / 0 / 32 | 0.7 | 929.8 | 0.57 | 3.11 | 16% | 13% | 3% | 3.63 |
| corner +x-y | 1.20 | 186.0 | 1674 | 307 / 239 / 1376 | 0.7 | 919.3 | 2.09 | 5.82 | 91% | 63% | 28% | 2.70 |

The last agent out (agent 40967, t100 988.4 s): last gangway straight -x-y (y wing) 3, exit door -x-y (y wall) 3. The gangway that cleared last: straight -x-y (y wing) 3 at 985.8 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 8804 | 7800.4 | 7.12 | 977.6 / 944.5 / 864.2 | 943.6 / 915.3 / 854.8 | 4278792.0 | 7989640 | 0.263 |
| gangway | 3792 | 3512.9 | 7.12 | 976.0 / 944.5 / 864.2 | 943.6 / 915.3 / 854.8 | 4278792.0 | 7393999 | 0.183 |
| walkway | 276 | 257.4 | 3.88 | 656.6 / 262.7 / 0.0 | 630.2 / 153.2 / 0.0 | 0.0 | 60317 | 0.689 |
| avenue | 1920 | 1801.4 | 2.10 | 665.5 / 0.0 / 0.0 | 643.5 / 0.0 / 0.0 | 0.0 | 356714 | 1.334 |
| exit | 4 | 2.0 | 0.00 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 0 | - |
| concourse | 2812 | 2226.8 | 3.34 | 884.2 / 648.7 / 0.0 | 656.9 / 109.8 / 0.0 | 0.0 | 178611 | 1.288 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 25392 | 16030.4 | 7.87 | 916.5 / 866.7 / 855.5 | 899.5 / 865.8 / 850.7 | 5303577.9 | 13294669 | 0.037 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 208 x 208 from (-104, -104) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -34.5 | -34.5 | gangway | 1.00 | 5.93 | 891.1 | 883.3 | 840.8 | 4802.5 | 0.008 |
| 2 | -35.5 | -35.5 | gangway | 1.00 | 5.94 | 900.1 | 895.9 | 838.3 | 4793.7 | 0.008 |
| 3 | 34.5 | -34.5 | gangway | 1.00 | 5.85 | 864.0 | 858.1 | 813.0 | 4668.2 | 0.009 |
| 4 | -36.5 | -36.5 | gangway | 1.00 | 5.91 | 909.5 | 907.9 | 804.7 | 4508.6 | 0.011 |
| 5 | 33.5 | -33.5 | gangway | 0.99 | 5.75 | 858.4 | 850.2 | 813.0 | 4489.4 | 0.007 |
| 6 | -32.5 | -32.5 | gangway | 1.00 | 6.02 | 801.8 | 786.0 | 728.7 | 4304.2 | 0.007 |
| 7 | 34.5 | 34.5 | gangway | 1.00 | 5.71 | 817.5 | 805.6 | 762.8 | 4286.6 | 0.012 |
| 8 | 35.5 | -35.5 | gangway | 1.00 | 5.65 | 866.8 | 860.9 | 772.7 | 4258.9 | 0.011 |
| 9 | 35.5 | 35.5 | gangway | 1.00 | 5.79 | 821.7 | 814.2 | 753.0 | 4252.7 | 0.013 |
| 10 | -36.5 | 36.5 | gangway | 1.00 | 5.85 | 813.7 | 795.5 | 731.3 | 4181.5 | 0.015 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -38.5 | -36.5 | seat row | 0.50 | 7.18 | 866.0 | 861.4 | 850.7 | 2996.9 | 0.006 |
| 2 | -36.5 | -38.5 | seat row | 0.50 | 7.25 | 868.6 | 861.9 | 845.0 | 2988.6 | 0.007 |
| 3 | -35.5 | -38.5 | seat row | 0.50 | 7.17 | 850.4 | 839.9 | 823.1 | 2865.1 | 0.009 |
| 4 | 38.5 | -36.5 | seat row | 0.50 | 7.35 | 842.2 | 832.6 | 809.8 | 2831.5 | 0.007 |
| 5 | -38.5 | -35.5 | seat row | 0.50 | 7.13 | 860.9 | 856.0 | 826.1 | 2827.2 | 0.010 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 5233; agent-steps of seated agents on another row's clearway: 788923.

## Deposit check

Person-seconds deposited: 21289031.2, of them in excluded cells: 4721.907.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 5939067 overlapping pair-steps: p99 0.0034, max 0.1583 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0034 max 0.1583; venue-geometry 12: p99 0.0032 max 0.0032 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00774 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 52 (longest 2 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.40 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 2409 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
