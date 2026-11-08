# Experiment `L_load95_s2`

**Task 5.9 stage 4: venue L, 95% load (seed 2), default model**

Venue L (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (4000 x 4000), cache key a2f3aaf59c2252b7, content hash 022d17b202313d70). 60253 agents on 95% of the 63424 seats (spawnSeatedCrowd, seed 2), buffer N = 65536, 8141 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 10835782 evaluations, 577953 switches, 0 forced choices).
Capacity: **within design capacity** (the L venue's design capacity 63424, jam capacity 171923: 23822.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-21T17:37:02, 944.8 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 2907 | 508.5 |
| t90 | 5845 | 1022.3 |
| t100 | 8141 | 1423.9 |

t_p: the step by which ceil(p x 60253) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 2039 | 0 | 70.8 | 1123.8 | 20.5 | 26.6 | 195.0-205.0 |
| -x | 5.66 | 1982 | 0 | 70.5 | 1125.0 | 19.9 | 26.6 | 390.9-400.9 |
| +y | 5.66 | 2054 | 0 | 70.5 | 1115.4 | 20.8 | 26.6 | 280.9-290.9 |
| -y | 5.66 | 2024 | 0 | 70.5 | 1124.1 | 20.4 | 26.6 | 81.5-91.5 |
| door +x+y (y wall) 0 | 2.30 | 1445 | 2446 | 4.9 | 1106.5 | 34.2 | 47.1 | 20.3-30.3 |
| door +x+y (y wall) 1 | 2.30 | 1595 | 2033 | 4.9 | 1389.8 | 30.0 | 44.5 | 4.7-14.7 |
| door +x+y (y wall) 2 | 2.30 | 1496 | 1513 | 4.9 | 1402.2 | 27.9 | 44.5 | 24.1-34.1 |
| door +x+y (y wall) 3 | 2.30 | 1171 | 988 | 4.9 | 1406.1 | 21.8 | 47.1 | 10.0-19.9 |
| door +x+y (y wall) 4 | 2.30 | 600 | 488 | 4.9 | 1352.0 | 11.6 | 47.1 | 8.9-18.9 |
| door +x+y (x wall) 0 | 2.30 | 1457 | 2451 | 5.1 | 1114.7 | 34.2 | 44.5 | 16.1-26.1 |
| door +x+y (x wall) 1 | 2.30 | 1594 | 2018 | 4.9 | 1391.4 | 30.0 | 44.5 | 11.5-21.5 |
| door +x+y (x wall) 2 | 2.30 | 1514 | 1527 | 4.9 | 1395.1 | 28.4 | 47.1 | 19.8-29.7 |
| door +x+y (x wall) 3 | 2.30 | 1197 | 997 | 4.7 | 1350.3 | 23.2 | 47.1 | 16.8-26.8 |
| door +x+y (x wall) 4 | 2.30 | 542 | 483 | 5.1 | 1389.8 | 10.2 | 44.5 | 17.0-26.9 |
| door +x+y (corner) | 2.30 | 405 | 120 | 6.3 | 1247.1 | 8.5 | 47.1 | 59.1-69.1 |
| door -x+y (y wall) 0 | 2.30 | 1450 | 2456 | 4.9 | 1120.1 | 33.9 | 44.5 | 8.6-18.5 |
| door -x+y (y wall) 1 | 2.30 | 1591 | 2023 | 4.9 | 1325.3 | 31.4 | 44.5 | 17.8-27.8 |
| door -x+y (y wall) 2 | 2.30 | 1488 | 1517 | 4.9 | 1390.2 | 28.0 | 47.1 | 11.4-21.3 |
| door -x+y (y wall) 3 | 2.30 | 1027 | 1003 | 4.9 | 1397.9 | 19.2 | 44.5 | 11.4-21.3 |
| door -x+y (y wall) 4 | 2.30 | 754 | 490 | 5.1 | 1314.1 | 15.0 | 47.1 | 16.4-26.4 |
| door -x+y (x wall) 0 | 2.30 | 1459 | 2457 | 4.9 | 1176.2 | 32.5 | 41.9 | 9.4-19.4 |
| door -x+y (x wall) 1 | 2.30 | 1595 | 2016 | 4.9 | 1317.4 | 31.7 | 44.5 | 4.7-14.7 |
| door -x+y (x wall) 2 | 2.30 | 1455 | 1499 | 4.9 | 1373.0 | 27.7 | 44.5 | 12.4-22.4 |
| door -x+y (x wall) 3 | 2.30 | 1029 | 995 | 4.9 | 1390.7 | 19.4 | 44.5 | 17.5-27.5 |
| door -x+y (x wall) 4 | 2.30 | 712 | 493 | 4.9 | 1319.7 | 14.1 | 52.3 | 540.3-550.3 |
| door -x+y (corner) | 2.30 | 499 | 119 | 6.3 | 1154.9 | 11.3 | 44.5 | 31.1-41.1 |
| door -x-y (y wall) 0 | 2.30 | 1454 | 2459 | 4.9 | 1125.9 | 33.8 | 47.1 | 20.3-30.3 |
| door -x-y (y wall) 1 | 2.30 | 1618 | 2034 | 4.9 | 1315.5 | 32.2 | 44.5 | 5.1-15.0 |
| door -x-y (y wall) 2 | 2.30 | 1504 | 1513 | 4.9 | 1403.3 | 28.1 | 44.5 | 26.9-36.9 |
| door -x-y (y wall) 3 | 2.30 | 1049 | 986 | 4.9 | 1406.4 | 19.5 | 44.5 | 21.0-31.0 |
| door -x-y (y wall) 4 | 2.30 | 687 | 485 | 4.9 | 1316.7 | 13.7 | 47.1 | 8.9-18.9 |
| door -x-y (x wall) 0 | 2.30 | 1464 | 2445 | 4.9 | 1126.0 | 34.1 | 47.1 | 22.4-32.4 |
| door -x-y (x wall) 1 | 2.30 | 1612 | 2040 | 4.9 | 1312.5 | 32.2 | 47.1 | 22.9-32.9 |
| door -x-y (x wall) 2 | 2.30 | 1490 | 1501 | 4.9 | 1365.0 | 28.6 | 44.5 | 9.8-19.8 |
| door -x-y (x wall) 3 | 2.30 | 1080 | 983 | 4.9 | 1406.4 | 20.1 | 44.5 | 29.9-39.9 |
| door -x-y (x wall) 4 | 2.30 | 700 | 489 | 5.1 | 1404.3 | 13.0 | 44.5 | 16.1-26.1 |
| door -x-y (corner) | 2.30 | 416 | 118 | 6.3 | 1098.8 | 9.9 | 44.5 | 48.3-58.2 |
| door +x-y (y wall) 0 | 2.30 | 1447 | 2456 | 5.1 | 1139.5 | 33.3 | 44.5 | 9.3-19.2 |
| door +x-y (y wall) 1 | 2.30 | 1588 | 2038 | 4.9 | 1370.7 | 30.3 | 47.1 | 24.8-34.8 |
| door +x-y (y wall) 2 | 2.30 | 1500 | 1522 | 4.9 | 1410.3 | 27.8 | 44.5 | 12.8-22.7 |
| door +x-y (y wall) 3 | 2.30 | 1201 | 984 | 4.9 | 1377.4 | 22.8 | 41.9 | 4.7-14.7 |
| door +x-y (y wall) 4 | 2.30 | 562 | 487 | 5.1 | 1373.9 | 10.7 | 41.9 | 17.0-26.9 |
| door +x-y (x wall) 0 | 2.30 | 1450 | 2443 | 5.1 | 1130.8 | 33.6 | 47.1 | 19.9-29.9 |
| door +x-y (x wall) 1 | 2.30 | 1586 | 2040 | 4.9 | 1401.0 | 29.6 | 47.1 | 17.7-27.6 |
| door +x-y (x wall) 2 | 2.30 | 1504 | 1499 | 4.9 | 1394.2 | 28.2 | 41.9 | 6.3-16.3 |
| door +x-y (x wall) 3 | 2.30 | 1210 | 989 | 4.9 | 1423.9 | 22.2 | 47.1 | 15.4-25.4 |
| door +x-y (x wall) 4 | 2.30 | 571 | 494 | 5.1 | 1350.8 | 11.1 | 47.1 | 20.5-30.4 |
| door +x-y (corner) | 2.30 | 386 | 116 | 6.5 | 1058.7 | 9.6 | 44.5 | 32.9-42.9 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (2.30 m; a corner door's: the gap between its wall ends, 2.30 m); agents are removed past the outer wall's outer face (92.71 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 2039 | 3.4% | 18.2% |
| -x | avenue | 5.66 | 1982 | 3.3% | 17.7% |
| +y | avenue | 5.66 | 2054 | 3.4% | 18.3% |
| -y | avenue | 5.66 | 2024 | 3.4% | 18.0% |
| door +x+y (y wall) 0 | door | 2.30 | 1445 | 2.4% | 31.7% |
| door +x+y (y wall) 1 | door | 2.30 | 1595 | 2.6% | 35.0% |
| door +x+y (y wall) 2 | door | 2.30 | 1496 | 2.5% | 32.8% |
| door +x+y (y wall) 3 | door | 2.30 | 1171 | 1.9% | 25.7% |
| door +x+y (y wall) 4 | door | 2.30 | 600 | 1.0% | 13.1% |
| door +x+y (x wall) 0 | door | 2.30 | 1457 | 2.4% | 31.9% |
| door +x+y (x wall) 1 | door | 2.30 | 1594 | 2.6% | 34.9% |
| door +x+y (x wall) 2 | door | 2.30 | 1514 | 2.5% | 33.2% |
| door +x+y (x wall) 3 | door | 2.30 | 1197 | 2.0% | 26.2% |
| door +x+y (x wall) 4 | door | 2.30 | 542 | 0.9% | 11.9% |
| door +x+y (corner) | door | 2.30 | 405 | 0.7% | 8.9% |
| door -x+y (y wall) 0 | door | 2.30 | 1450 | 2.4% | 31.8% |
| door -x+y (y wall) 1 | door | 2.30 | 1591 | 2.6% | 34.9% |
| door -x+y (y wall) 2 | door | 2.30 | 1488 | 2.5% | 32.6% |
| door -x+y (y wall) 3 | door | 2.30 | 1027 | 1.7% | 22.5% |
| door -x+y (y wall) 4 | door | 2.30 | 754 | 1.3% | 16.5% |
| door -x+y (x wall) 0 | door | 2.30 | 1459 | 2.4% | 32.0% |
| door -x+y (x wall) 1 | door | 2.30 | 1595 | 2.6% | 35.0% |
| door -x+y (x wall) 2 | door | 2.30 | 1455 | 2.4% | 31.9% |
| door -x+y (x wall) 3 | door | 2.30 | 1029 | 1.7% | 22.6% |
| door -x+y (x wall) 4 | door | 2.30 | 712 | 1.2% | 15.6% |
| door -x+y (corner) | door | 2.30 | 499 | 0.8% | 10.9% |
| door -x-y (y wall) 0 | door | 2.30 | 1454 | 2.4% | 31.9% |
| door -x-y (y wall) 1 | door | 2.30 | 1618 | 2.7% | 35.5% |
| door -x-y (y wall) 2 | door | 2.30 | 1504 | 2.5% | 33.0% |
| door -x-y (y wall) 3 | door | 2.30 | 1049 | 1.7% | 23.0% |
| door -x-y (y wall) 4 | door | 2.30 | 687 | 1.1% | 15.1% |
| door -x-y (x wall) 0 | door | 2.30 | 1464 | 2.4% | 32.1% |
| door -x-y (x wall) 1 | door | 2.30 | 1612 | 2.7% | 35.3% |
| door -x-y (x wall) 2 | door | 2.30 | 1490 | 2.5% | 32.7% |
| door -x-y (x wall) 3 | door | 2.30 | 1080 | 1.8% | 23.7% |
| door -x-y (x wall) 4 | door | 2.30 | 700 | 1.2% | 15.3% |
| door -x-y (corner) | door | 2.30 | 416 | 0.7% | 9.1% |
| door +x-y (y wall) 0 | door | 2.30 | 1447 | 2.4% | 31.7% |
| door +x-y (y wall) 1 | door | 2.30 | 1588 | 2.6% | 34.8% |
| door +x-y (y wall) 2 | door | 2.30 | 1500 | 2.5% | 32.9% |
| door +x-y (y wall) 3 | door | 2.30 | 1201 | 2.0% | 26.3% |
| door +x-y (y wall) 4 | door | 2.30 | 562 | 0.9% | 12.3% |
| door +x-y (x wall) 0 | door | 2.30 | 1450 | 2.4% | 31.8% |
| door +x-y (x wall) 1 | door | 2.30 | 1586 | 2.6% | 34.8% |
| door +x-y (x wall) 2 | door | 2.30 | 1504 | 2.5% | 33.0% |
| door +x-y (x wall) 3 | door | 2.30 | 1210 | 2.0% | 26.5% |
| door +x-y (x wall) 4 | door | 2.30 | 571 | 0.9% | 12.5% |
| door +x-y (corner) | door | 2.30 | 386 | 0.6% | 8.5% |
| **doors (44)** | door | 101.20 | 52154 | 86.6% | |
| **avenues (4)** | avenue | 22.64 | 8099 | 13.4% | |

**Unused exit width: 0.0 of 123.8 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 1423.9 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 24.5%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 2215 | 3.7% | 2215 | 3.7% |
| straight +x+y (y wing) 1 | straight | yes | 1793 | 3.0% | 1595 | 2.6% |
| straight +x+y (y wing) 2 | straight | yes | 1525 | 2.5% | 1511 | 2.5% |
| straight +x+y (y wing) 3 | straight | yes | 1179 | 2.0% | 1177 | 2.0% |
| straight +x+y (y wing) 4 | straight | yes | 601 | 1.0% | 579 | 1.0% |
| straight +x+y (x wing) 0 | straight | yes | 2222 | 3.7% | 2222 | 3.7% |
| straight +x+y (x wing) 1 | straight | yes | 1777 | 2.9% | 1594 | 2.6% |
| straight +x+y (x wing) 2 | straight | yes | 1545 | 2.6% | 1527 | 2.5% |
| straight +x+y (x wing) 3 | straight | yes | 1195 | 2.0% | 1192 | 2.0% |
| straight +x+y (x wing) 4 | straight | yes | 557 | 0.9% | 534 | 0.9% |
| corner +x+y | corner | yes | 2179 | 3.6% | 918 | 1.5% |
| straight -x+y (y wing) 0 | straight | yes | 2212 | 3.7% | 2212 | 3.7% |
| straight -x+y (y wing) 1 | straight | yes | 1773 | 2.9% | 1591 | 2.6% |
| straight -x+y (y wing) 2 | straight | yes | 1532 | 2.5% | 1503 | 2.5% |
| straight -x+y (y wing) 3 | straight | yes | 1077 | 1.8% | 1054 | 1.7% |
| straight -x+y (y wing) 4 | straight | yes | 733 | 1.2% | 712 | 1.2% |
| straight -x+y (x wing) 0 | straight | yes | 2232 | 3.7% | 2232 | 3.7% |
| straight -x+y (x wing) 1 | straight | yes | 1768 | 2.9% | 1598 | 2.7% |
| straight -x+y (x wing) 2 | straight | yes | 1502 | 2.5% | 1476 | 2.4% |
| straight -x+y (x wing) 3 | straight | yes | 1081 | 1.8% | 1062 | 1.8% |
| straight -x+y (x wing) 4 | straight | yes | 679 | 1.1% | 658 | 1.1% |
| corner -x+y | corner | yes | 2225 | 3.7% | 970 | 1.6% |
| straight -x-y (y wing) 0 | straight | yes | 2233 | 3.7% | 2233 | 3.7% |
| straight -x-y (y wing) 1 | straight | yes | 1770 | 2.9% | 1618 | 2.7% |
| straight -x-y (y wing) 2 | straight | yes | 1532 | 2.5% | 1516 | 2.5% |
| straight -x-y (y wing) 3 | straight | yes | 1087 | 1.8% | 1077 | 1.8% |
| straight -x-y (y wing) 4 | straight | yes | 663 | 1.1% | 647 | 1.1% |
| straight -x-y (x wing) 0 | straight | yes | 2233 | 3.7% | 2233 | 3.7% |
| straight -x-y (x wing) 1 | straight | yes | 1763 | 2.9% | 1612 | 2.7% |
| straight -x-y (x wing) 2 | straight | yes | 1511 | 2.5% | 1493 | 2.5% |
| straight -x-y (x wing) 3 | straight | yes | 1101 | 1.8% | 1088 | 1.8% |
| straight -x-y (x wing) 4 | straight | yes | 711 | 1.2% | 689 | 1.1% |
| corner -x-y | corner | yes | 2167 | 3.6% | 847 | 1.4% |
| straight +x-y (y wing) 0 | straight | yes | 2211 | 3.7% | 2211 | 3.7% |
| straight +x-y (y wing) 1 | straight | yes | 1792 | 3.0% | 1591 | 2.6% |
| straight +x-y (y wing) 2 | straight | yes | 1536 | 2.5% | 1516 | 2.5% |
| straight +x-y (y wing) 3 | straight | yes | 1192 | 2.0% | 1190 | 2.0% |
| straight +x-y (y wing) 4 | straight | yes | 574 | 1.0% | 557 | 0.9% |
| straight +x-y (x wing) 0 | straight | yes | 2218 | 3.7% | 2218 | 3.7% |
| straight +x-y (x wing) 1 | straight | yes | 1784 | 3.0% | 1587 | 2.6% |
| straight +x-y (x wing) 2 | straight | yes | 1521 | 2.5% | 1508 | 2.5% |
| straight +x-y (x wing) 3 | straight | yes | 1214 | 2.0% | 1214 | 2.0% |
| straight +x-y (x wing) 4 | straight | yes | 586 | 1.0% | 563 | 0.9% |
| corner +x-y | corner | yes | 2217 | 3.7% | 913 | 1.5% |
| **straight (40)** | | | 58430 | | 56605 | 93.9% |
| **corner (4)** | | | 8788 | | 3648 | 6.1% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 2039 | 70.8 | 1123.8 | 0.25 | 0.32 | 0.0% |
| -x | 1982 | 70.5 | 1125.0 | 0.24 | 0.32 | 0.0% |
| +y | 2054 | 70.5 | 1115.4 | 0.25 | 0.32 | 0.0% |
| -y | 2024 | 70.5 | 1124.1 | 0.24 | 0.32 | 0.0% |
| door +x+y (y wall) 0 | 1445 | 4.9 | 1106.5 | 0.41 | 0.56 | 0.0% |
| door +x+y (y wall) 1 | 1595 | 4.9 | 1389.8 | 0.36 | 0.53 | 0.0% |
| door +x+y (y wall) 2 | 1496 | 4.9 | 1402.2 | 0.33 | 0.53 | 0.0% |
| door +x+y (y wall) 3 | 1171 | 4.9 | 1406.1 | 0.26 | 0.56 | 0.0% |
| door +x+y (y wall) 4 | 600 | 4.9 | 1352.0 | 0.14 | 0.56 | 0.0% |
| door +x+y (x wall) 0 | 1457 | 5.1 | 1114.7 | 0.41 | 0.53 | 0.0% |
| door +x+y (x wall) 1 | 1594 | 4.9 | 1391.4 | 0.36 | 0.53 | 0.0% |
| door +x+y (x wall) 2 | 1514 | 4.9 | 1395.1 | 0.34 | 0.56 | 0.0% |
| door +x+y (x wall) 3 | 1197 | 4.7 | 1350.3 | 0.28 | 0.56 | 0.0% |
| door +x+y (x wall) 4 | 542 | 5.1 | 1389.8 | 0.12 | 0.53 | 0.0% |
| door +x+y (corner) | 405 | 6.3 | 1247.1 | 0.10 | 0.56 | 0.0% |
| door -x+y (y wall) 0 | 1450 | 4.9 | 1120.1 | 0.41 | 0.53 | 0.0% |
| door -x+y (y wall) 1 | 1591 | 4.9 | 1325.3 | 0.38 | 0.53 | 0.0% |
| door -x+y (y wall) 2 | 1488 | 4.9 | 1390.2 | 0.34 | 0.56 | 0.0% |
| door -x+y (y wall) 3 | 1027 | 4.9 | 1397.9 | 0.23 | 0.53 | 0.0% |
| door -x+y (y wall) 4 | 754 | 5.1 | 1314.1 | 0.18 | 0.56 | 0.0% |
| door -x+y (x wall) 0 | 1459 | 4.9 | 1176.2 | 0.39 | 0.50 | 0.0% |
| door -x+y (x wall) 1 | 1595 | 4.9 | 1317.4 | 0.38 | 0.53 | 0.0% |
| door -x+y (x wall) 2 | 1455 | 4.9 | 1373.0 | 0.33 | 0.53 | 0.0% |
| door -x+y (x wall) 3 | 1029 | 4.9 | 1390.7 | 0.23 | 0.53 | 0.0% |
| door -x+y (x wall) 4 | 712 | 4.9 | 1319.7 | 0.17 | 0.63 | 0.0% |
| door -x+y (corner) | 499 | 6.3 | 1154.9 | 0.14 | 0.53 | 0.0% |
| door -x-y (y wall) 0 | 1454 | 4.9 | 1125.9 | 0.40 | 0.56 | 0.0% |
| door -x-y (y wall) 1 | 1618 | 4.9 | 1315.5 | 0.39 | 0.53 | 0.0% |
| door -x-y (y wall) 2 | 1504 | 4.9 | 1403.3 | 0.34 | 0.53 | 0.0% |
| door -x-y (y wall) 3 | 1049 | 4.9 | 1406.4 | 0.23 | 0.53 | 0.0% |
| door -x-y (y wall) 4 | 687 | 4.9 | 1316.7 | 0.16 | 0.56 | 0.0% |
| door -x-y (x wall) 0 | 1464 | 4.9 | 1126.0 | 0.41 | 0.56 | 0.0% |
| door -x-y (x wall) 1 | 1612 | 4.9 | 1312.5 | 0.38 | 0.56 | 0.0% |
| door -x-y (x wall) 2 | 1490 | 4.9 | 1365.0 | 0.34 | 0.53 | 0.0% |
| door -x-y (x wall) 3 | 1080 | 4.9 | 1406.4 | 0.24 | 0.53 | 0.0% |
| door -x-y (x wall) 4 | 700 | 5.1 | 1404.3 | 0.16 | 0.53 | 0.0% |
| door -x-y (corner) | 416 | 6.3 | 1098.8 | 0.12 | 0.53 | 0.0% |
| door +x-y (y wall) 0 | 1447 | 5.1 | 1139.5 | 0.40 | 0.53 | 0.0% |
| door +x-y (y wall) 1 | 1588 | 4.9 | 1370.7 | 0.36 | 0.56 | 0.0% |
| door +x-y (y wall) 2 | 1500 | 4.9 | 1410.3 | 0.33 | 0.53 | 0.0% |
| door +x-y (y wall) 3 | 1201 | 4.9 | 1377.4 | 0.27 | 0.50 | 0.0% |
| door +x-y (y wall) 4 | 562 | 5.1 | 1373.9 | 0.13 | 0.50 | 0.0% |
| door +x-y (x wall) 0 | 1450 | 5.1 | 1130.8 | 0.40 | 0.56 | 0.0% |
| door +x-y (x wall) 1 | 1586 | 4.9 | 1401.0 | 0.35 | 0.56 | 0.0% |
| door +x-y (x wall) 2 | 1504 | 4.9 | 1394.2 | 0.34 | 0.50 | 0.0% |
| door +x-y (x wall) 3 | 1210 | 4.9 | 1423.9 | 0.27 | 0.56 | 0.0% |
| door +x-y (x wall) 4 | 571 | 5.1 | 1350.8 | 0.13 | 0.56 | 0.0% |
| door +x-y (corner) | 386 | 6.5 | 1058.7 | 0.11 | 0.53 | 0.0% |

Mean flow / w J averaged over the doors 0.29, over the avenues 0.24.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 103.1 | 2215 | 1445 / 771 / 960 | 0.7 | 1103.5 | 2.88 | 4.91 | 92% | 86% | 5% | 4.40 |
| straight +x+y (y wing) 1 | 1.20 | 81.5 | 1783 | 1595 / 0 / 291 | 0.7 | 1386.8 | 1.36 | 2.71 | 85% | 61% | 24% | 3.43 |
| straight +x+y (y wing) 2 | 1.20 | 61.0 | 1432 | 1511 / 0 / 21 | 0.7 | 1399.3 | 1.10 | 1.71 | 77% | 66% | 11% | 3.75 |
| straight +x+y (y wing) 3 | 1.20 | 39.4 | 883 | 1177 / 0 / 4 | 0.7 | 1403.1 | 0.84 | 1.81 | 55% | 39% | 16% | 3.43 |
| straight +x+y (y wing) 4 | 1.20 | 18.8 | 381 | 579 / 0 / 24 | 0.7 | 1349.1 | 0.45 | 1.71 | 19% | 16% | 3% | 3.66 |
| straight +x+y (x wing) 0 | 1.20 | 103.1 | 2222 | 1457 / 765 / 1054 | 0.7 | 1111.7 | 2.95 | 5.02 | 92% | 86% | 6% | 4.19 |
| straight +x+y (x wing) 1 | 1.20 | 81.5 | 1759 | 1594 / 0 / 266 | 0.7 | 1388.4 | 1.34 | 2.91 | 86% | 62% | 24% | 3.38 |
| straight +x+y (x wing) 2 | 1.20 | 61.0 | 1445 | 1527 / 0 / 22 | 0.7 | 1392.1 | 1.11 | 1.71 | 76% | 66% | 11% | 3.81 |
| straight +x+y (x wing) 3 | 1.20 | 39.4 | 897 | 1192 / 0 / 6 | 0.7 | 1347.3 | 0.89 | 1.60 | 57% | 42% | 15% | 3.32 |
| straight +x+y (x wing) 4 | 1.20 | 18.8 | 381 | 534 / 0 / 30 | 0.7 | 1386.8 | 0.41 | 1.91 | 20% | 16% | 4% | 3.53 |
| corner +x+y | 1.20 | 186.0 | 1666 | 405 / 513 / 1327 | 0.7 | 1362.9 | 1.65 | 3.91 | 92% | 62% | 30% | 2.68 |
| straight -x+y (y wing) 0 | 1.20 | 103.1 | 2212 | 1450 / 762 / 1080 | 0.7 | 1117.1 | 2.95 | 5.22 | 92% | 85% | 7% | 4.16 |
| straight -x+y (y wing) 1 | 1.20 | 81.5 | 1754 | 1591 / 0 / 269 | 0.7 | 1322.3 | 1.41 | 2.51 | 92% | 67% | 26% | 3.34 |
| straight -x+y (y wing) 2 | 1.20 | 61.0 | 1461 | 1503 / 0 / 35 | 0.7 | 1387.2 | 1.11 | 2.01 | 77% | 69% | 9% | 3.76 |
| straight -x+y (y wing) 3 | 1.20 | 39.4 | 876 | 1054 / 0 / 26 | 0.7 | 1394.9 | 0.77 | 1.81 | 49% | 40% | 9% | 3.50 |
| straight -x+y (y wing) 4 | 1.20 | 18.8 | 377 | 712 / 0 / 22 | 0.7 | 1311.1 | 0.56 | 2.01 | 20% | 18% | 2% | 3.71 |
| straight -x+y (x wing) 0 | 1.20 | 103.1 | 2231 | 1456 / 776 / 924 | 0.7 | 1098.9 | 2.87 | 4.81 | 92% | 86% | 6% | 4.39 |
| straight -x+y (x wing) 1 | 1.20 | 81.5 | 1758 | 1598 / 0 / 240 | 0.7 | 1314.4 | 1.40 | 3.31 | 92% | 73% | 19% | 3.50 |
| straight -x+y (x wing) 2 | 1.20 | 61.0 | 1418 | 1476 / 0 / 39 | 0.7 | 1370.0 | 1.11 | 1.91 | 78% | 67% | 11% | 3.76 |
| straight -x+y (x wing) 3 | 1.20 | 39.4 | 877 | 1062 / 0 / 19 | 0.7 | 1387.7 | 0.78 | 1.71 | 48% | 41% | 6% | 3.68 |
| straight -x+y (x wing) 4 | 1.20 | 18.8 | 400 | 658 / 0 / 24 | 0.7 | 1316.7 | 0.52 | 1.71 | 20% | 18% | 2% | 3.70 |
| corner -x+y | 1.20 | 186.0 | 1704 | 499 / 472 / 1327 | 0.7 | 1344.7 | 1.71 | 3.61 | 93% | 60% | 33% | 2.52 |
| straight -x-y (y wing) 0 | 1.20 | 103.1 | 2233 | 1454 / 779 / 961 | 0.7 | 1122.9 | 2.85 | 4.61 | 92% | 84% | 8% | 4.44 |
| straight -x-y (y wing) 1 | 1.20 | 81.5 | 1745 | 1618 / 0 / 235 | 0.7 | 1312.5 | 1.41 | 2.81 | 92% | 71% | 21% | 3.47 |
| straight -x-y (y wing) 2 | 1.20 | 61.0 | 1450 | 1516 / 0 / 23 | 0.7 | 1400.3 | 1.10 | 1.91 | 79% | 65% | 15% | 3.65 |
| straight -x-y (y wing) 3 | 1.20 | 39.4 | 884 | 1077 / 0 / 12 | 0.7 | 1403.5 | 0.78 | 1.60 | 48% | 38% | 10% | 3.65 |
| straight -x-y (y wing) 4 | 1.20 | 18.8 | 353 | 647 / 0 / 40 | 0.7 | 1313.7 | 0.52 | 2.11 | 21% | 15% | 6% | 3.05 |
| straight -x-y (x wing) 0 | 1.20 | 103.1 | 2233 | 1464 / 769 / 903 | 0.7 | 1123.1 | 2.79 | 5.12 | 92% | 86% | 6% | 4.20 |
| straight -x-y (x wing) 1 | 1.20 | 81.5 | 1755 | 1612 / 0 / 283 | 0.7 | 1309.5 | 1.45 | 2.81 | 92% | 75% | 17% | 3.60 |
| straight -x-y (x wing) 2 | 1.20 | 61.0 | 1430 | 1493 / 0 / 23 | 0.7 | 1362.0 | 1.11 | 2.01 | 80% | 68% | 12% | 3.60 |
| straight -x-y (x wing) 3 | 1.20 | 39.4 | 875 | 1088 / 0 / 15 | 0.7 | 1403.5 | 0.79 | 1.60 | 49% | 39% | 10% | 3.51 |
| straight -x-y (x wing) 4 | 1.20 | 18.8 | 367 | 689 / 0 / 24 | 0.7 | 1401.4 | 0.51 | 1.81 | 17% | 14% | 3% | 3.67 |
| corner -x-y | 1.20 | 186.0 | 1728 | 416 / 431 / 1469 | 0.7 | 1377.4 | 1.68 | 4.11 | 91% | 60% | 32% | 2.56 |
| straight +x-y (y wing) 0 | 1.20 | 103.1 | 2211 | 1444 / 767 / 1022 | 0.7 | 1114.0 | 2.90 | 5.02 | 89% | 87% | 3% | 4.37 |
| straight +x-y (y wing) 1 | 1.20 | 81.5 | 1781 | 1591 / 0 / 295 | 0.7 | 1367.8 | 1.38 | 3.21 | 90% | 61% | 29% | 3.29 |
| straight +x-y (y wing) 2 | 1.20 | 61.0 | 1451 | 1516 / 0 / 22 | 0.7 | 1407.3 | 1.09 | 2.21 | 77% | 65% | 12% | 3.63 |
| straight +x-y (y wing) 3 | 1.20 | 39.4 | 881 | 1190 / 0 / 5 | 0.7 | 1374.6 | 0.87 | 1.60 | 58% | 39% | 19% | 3.23 |
| straight +x-y (y wing) 4 | 1.20 | 18.8 | 363 | 557 / 0 / 20 | 0.7 | 1370.9 | 0.42 | 1.81 | 17% | 17% | 1% | 3.74 |
| straight +x-y (x wing) 0 | 1.20 | 103.1 | 2218 | 1449 / 769 / 941 | 0.7 | 1112.2 | 2.84 | 5.12 | 92% | 85% | 7% | 4.17 |
| straight +x-y (x wing) 1 | 1.20 | 81.5 | 1771 | 1587 / 0 / 280 | 0.7 | 1398.0 | 1.34 | 2.81 | 87% | 60% | 27% | 3.30 |
| straight +x-y (x wing) 2 | 1.20 | 61.0 | 1417 | 1508 / 0 / 16 | 0.7 | 1391.2 | 1.10 | 1.81 | 74% | 64% | 11% | 3.71 |
| straight +x-y (x wing) 3 | 1.20 | 39.4 | 893 | 1214 / 0 / 5 | 0.7 | 1420.9 | 0.86 | 1.60 | 57% | 39% | 17% | 3.18 |
| straight +x-y (x wing) 4 | 1.20 | 18.8 | 376 | 563 / 0 / 29 | 0.7 | 1347.8 | 0.44 | 1.71 | 18% | 17% | 1% | 3.89 |
| corner +x-y | 1.20 | 186.0 | 1706 | 386 / 527 / 1358 | 0.7 | 1370.9 | 1.66 | 4.61 | 92% | 63% | 29% | 2.64 |

The last agent out (agent 53549, t100 1423.9 s): last gangway straight +x-y (x wing) 3, exit door +x-y (x wall) 3. The gangway that cleared last: straight +x-y (x wing) 3 at 1420.9 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 8804 | 7800.4 | 6.93 | 1420.4 / 1326.1 / 1268.4 | 1317.9 / 1299.4 / 1242.7 | 6528520.9 | 12558007 | 0.171 |
| gangway | 3792 | 3512.9 | 6.93 | 1419.4 / 1326.1 / 1268.4 | 1317.9 / 1299.4 / 1242.7 | 6528520.9 | 11804354 | 0.105 |
| walkway | 276 | 257.4 | 3.25 | 756.8 / 319.0 / 0.0 | 402.6 / 95.5 / 0.0 | 0.0 | 70845 | 0.822 |
| avenue | 1920 | 1801.4 | 1.98 | 782.4 / 0.0 / 0.0 | 537.3 / 0.0 / 0.0 | 0.0 | 485416 | 1.334 |
| exit | 4 | 2.0 | 0.00 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 0 | - |
| concourse | 2812 | 2226.8 | 2.62 | 1347.8 / 25.4 / 0.0 | 985.4 / 3.7 / 0.0 | 0.0 | 197392 | 1.041 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 25392 | 16030.4 | 7.84 | 1264.6 / 1261.4 / 1231.2 | 1264.2 / 1258.3 / 1220.7 | 7810185.4 | 19739843 | 0.023 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 208 x 208 from (-104, -104) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 35.5 | -35.5 | gangway | 1.00 | 5.79 | 1308.7 | 1299.4 | 1238.5 | 7042.8 | 0.008 |
| 2 | 34.5 | -34.5 | gangway | 1.00 | 5.73 | 1304.8 | 1290.5 | 1242.7 | 6904.5 | 0.007 |
| 3 | -34.5 | 34.5 | gangway | 1.00 | 5.72 | 1284.3 | 1273.1 | 1188.3 | 6698.4 | 0.009 |
| 4 | 34.5 | 34.5 | gangway | 1.00 | 5.84 | 1287.5 | 1277.2 | 1210.9 | 6664.5 | 0.008 |
| 5 | -36.5 | 36.5 | gangway | 1.00 | 5.64 | 1289.8 | 1280.3 | 1190.2 | 6656.3 | 0.009 |
| 6 | 36.5 | 36.5 | gangway | 1.00 | 5.75 | 1296.9 | 1290.8 | 1203.9 | 6622.8 | 0.008 |
| 7 | 35.5 | 35.5 | gangway | 1.00 | 5.90 | 1291.9 | 1286.1 | 1192.5 | 6619.7 | 0.007 |
| 8 | -37.5 | -37.5 | gangway | 0.99 | 5.86 | 1305.0 | 1280.5 | 1171.5 | 6616.6 | 0.011 |
| 9 | -35.5 | 35.5 | gangway | 1.00 | 5.67 | 1287.3 | 1281.0 | 1199.2 | 6615.5 | 0.007 |
| 10 | -38.5 | -38.5 | gangway | 1.00 | 6.02 | 1307.6 | 1275.4 | 1135.3 | 6539.3 | 0.016 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 38.5 | -36.5 | seat row | 0.50 | 7.36 | 1259.2 | 1258.3 | 1209.7 | 4371.1 | 0.007 |
| 2 | -38.5 | 36.5 | seat row | 0.50 | 7.32 | 1218.4 | 1213.7 | 1202.7 | 4326.1 | 0.005 |
| 3 | 36.5 | 38.5 | seat row | 0.50 | 7.36 | 1246.6 | 1241.1 | 1214.2 | 4320.6 | 0.004 |
| 4 | -36.5 | -38.5 | seat row | 0.50 | 7.16 | 1241.5 | 1239.9 | 1218.2 | 4275.4 | 0.005 |
| 5 | -42.5 | -25.5 | seat row | 0.64 | 6.92 | 1054.3 | 1050.7 | 1039.5 | 4264.6 | 0.010 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 8424; agent-steps of seated agents on another row's clearway: 1396782.

## Deposit check

Person-seconds deposited: 32303425.7, of them in excluded cells: 5575.594.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 7034993 overlapping pair-steps: p99 0.0020, max 0.0974 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0020 max 0.0974; venue-geometry 13: p99 0.0026 max 0.0026 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00761 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 58 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.42 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 3749 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
