# Experiment `L_load95_s1`

**Task 5.10 stage 4 (AMD 26.10.1): Task 5.8's model (the level spacing on the gangway inclines, --stair-flow off): venue L, 95% load (seed 1)**

Venue L (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (4000 x 4000), cache key a2f3aaf59c2252b7, content hash 022d17b202313d70). 60253 agents on 95% of the 63424 seats (spawnSeatedCrowd, seed 1), buffer N = 65536, 7442 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 8460243 evaluations, 473952 switches, 0 forced choices).
Capacity: **within design capacity** (the L venue's design capacity 63424, jam capacity 171923: 23822.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T19:54:42, 714.1 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 2273 | 397.6 |
| t90 | 4526 | 791.6 |
| t100 | 7442 | 1301.7 |

t_p: the step by which ceil(p x 60253) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 1774 | 0 | 70.5 | 867.0 | 23.6 | 25.5 | 79.6-89.6 |
| -x | 5.66 | 1763 | 0 | 70.5 | 877.3 | 23.2 | 26.6 | 80.1-90.1 |
| +y | 5.66 | 1765 | 0 | 70.5 | 867.4 | 23.5 | 26.6 | 79.9-89.9 |
| -y | 5.66 | 1755 | 0 | 70.5 | 863.9 | 23.4 | 26.6 | 81.5-91.5 |
| door +x+y (y wall) 0 | 2.30 | 1483 | 2445 | 4.9 | 941.0 | 41.3 | 57.6 | 54.4-64.4 |
| door +x+y (y wall) 1 | 2.30 | 1677 | 2029 | 4.9 | 1053.5 | 41.7 | 57.6 | 12.6-22.6 |
| door +x+y (y wall) 2 | 2.30 | 1538 | 1513 | 4.9 | 1099.1 | 36.7 | 57.6 | 11.0-21.0 |
| door +x+y (y wall) 3 | 2.30 | 1208 | 999 | 4.9 | 1107.5 | 28.6 | 57.6 | 28.5-38.5 |
| door +x+y (y wall) 4 | 2.30 | 494 | 485 | 4.9 | 1068.7 | 12.1 | 60.2 | 22.9-32.9 |
| door +x+y (x wall) 0 | 2.30 | 1502 | 2443 | 5.1 | 869.5 | 45.3 | 54.9 | 11.4-21.3 |
| door +x+y (x wall) 1 | 2.30 | 1669 | 2019 | 4.9 | 1049.4 | 41.7 | 54.9 | 10.7-20.6 |
| door +x+y (x wall) 2 | 2.30 | 1515 | 1499 | 4.9 | 1099.3 | 36.1 | 57.6 | 18.2-28.2 |
| door +x+y (x wall) 3 | 2.30 | 1228 | 990 | 4.9 | 1111.4 | 28.9 | 57.6 | 268.8-278.8 |
| door +x+y (x wall) 4 | 2.30 | 607 | 487 | 5.1 | 1054.0 | 15.1 | 57.6 | 8.2-18.2 |
| door +x+y (corner) | 2.30 | 337 | 116 | 6.3 | 938.4 | 9.4 | 57.6 | 76.8-86.8 |
| door -x+y (y wall) 0 | 2.30 | 1488 | 2445 | 4.9 | 938.7 | 41.6 | 60.2 | 11.7-21.7 |
| door -x+y (y wall) 1 | 2.30 | 1670 | 2024 | 4.9 | 1002.2 | 43.7 | 57.6 | 7.9-17.8 |
| door -x+y (y wall) 2 | 2.30 | 1534 | 1511 | 4.9 | 1087.6 | 37.0 | 57.6 | 20.5-30.4 |
| door -x+y (y wall) 3 | 2.30 | 1244 | 1004 | 4.9 | 1090.9 | 29.9 | 57.6 | 24.8-34.8 |
| door -x+y (y wall) 4 | 2.30 | 516 | 494 | 5.1 | 1102.4 | 12.3 | 57.6 | 8.6-18.5 |
| door -x+y (x wall) 0 | 2.30 | 1499 | 2451 | 4.9 | 935.1 | 42.0 | 60.2 | 14.5-24.5 |
| door -x+y (x wall) 1 | 2.30 | 1669 | 2036 | 4.9 | 1071.8 | 40.8 | 60.2 | 18.9-28.9 |
| door -x+y (x wall) 2 | 2.30 | 1551 | 1521 | 4.9 | 1089.8 | 37.3 | 57.6 | 27.6-37.6 |
| door -x+y (x wall) 3 | 2.30 | 1242 | 998 | 4.9 | 1076.7 | 30.2 | 57.6 | 21.0-31.0 |
| door -x+y (x wall) 4 | 2.30 | 530 | 482 | 4.9 | 1035.3 | 13.4 | 54.9 | 11.9-21.9 |
| door -x+y (corner) | 2.30 | 354 | 115 | 6.3 | 935.8 | 9.9 | 54.9 | 31.5-41.5 |
| door -x-y (y wall) 0 | 2.30 | 1498 | 2430 | 4.9 | 942.0 | 41.7 | 57.6 | 5.6-15.6 |
| door -x-y (y wall) 1 | 2.30 | 1710 | 2027 | 4.9 | 1185.5 | 37.8 | 57.6 | 10.1-20.1 |
| door -x-y (y wall) 2 | 2.30 | 1464 | 1522 | 4.9 | 1301.7 | 29.4 | 60.2 | 15.2-25.2 |
| door -x-y (y wall) 3 | 2.30 | 1108 | 989 | 4.9 | 1295.4 | 22.4 | 60.2 | 16.4-26.4 |
| door -x-y (y wall) 4 | 2.30 | 662 | 490 | 4.9 | 1168.6 | 14.8 | 60.2 | 20.1-30.1 |
| door -x-y (x wall) 0 | 2.30 | 1478 | 2430 | 4.9 | 942.6 | 41.1 | 57.6 | 22.4-32.4 |
| door -x-y (x wall) 1 | 2.30 | 1679 | 2025 | 4.9 | 1185.2 | 37.1 | 57.6 | 10.7-20.6 |
| door -x-y (x wall) 2 | 2.30 | 1491 | 1515 | 4.9 | 1290.6 | 30.2 | 57.6 | 32.4-42.3 |
| door -x-y (x wall) 3 | 2.30 | 1147 | 998 | 4.9 | 1299.7 | 23.1 | 60.2 | 11.7-21.7 |
| door -x-y (x wall) 4 | 2.30 | 621 | 493 | 5.1 | 1293.6 | 12.6 | 54.9 | 19.9-29.9 |
| door -x-y (corner) | 2.30 | 434 | 120 | 6.3 | 909.7 | 12.5 | 54.9 | 51.1-61.0 |
| door +x-y (y wall) 0 | 2.30 | 1500 | 2435 | 4.9 | 952.7 | 41.3 | 60.2 | 11.5-21.5 |
| door +x-y (y wall) 1 | 2.30 | 1698 | 2029 | 4.9 | 1142.7 | 38.9 | 54.9 | 17.3-27.3 |
| door +x-y (y wall) 2 | 2.30 | 1516 | 1531 | 4.9 | 1148.8 | 34.6 | 57.6 | 19.1-29.0 |
| door +x-y (y wall) 3 | 2.30 | 1091 | 992 | 4.9 | 1155.4 | 24.7 | 54.9 | 15.4-25.4 |
| door +x-y (y wall) 4 | 2.30 | 659 | 479 | 5.1 | 1129.2 | 15.3 | 54.9 | 12.9-22.9 |
| door +x-y (x wall) 0 | 2.30 | 1515 | 2464 | 4.9 | 961.5 | 41.3 | 60.2 | 13.3-23.3 |
| door +x-y (x wall) 1 | 2.30 | 1688 | 2061 | 4.9 | 1152.1 | 38.4 | 57.6 | 18.0-28.0 |
| door +x-y (x wall) 2 | 2.30 | 1513 | 1517 | 4.9 | 1147.2 | 34.5 | 57.6 | 21.2-31.1 |
| door +x-y (x wall) 3 | 2.30 | 1144 | 997 | 4.9 | 1140.7 | 26.3 | 57.6 | 18.2-28.2 |
| door +x-y (x wall) 4 | 2.30 | 665 | 482 | 5.1 | 1144.4 | 15.2 | 60.2 | 8.0-18.0 |
| door +x-y (corner) | 2.30 | 360 | 121 | 6.5 | 943.8 | 10.0 | 54.9 | 120.7-130.7 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (2.30 m; a corner door's: the gap between its wall ends, 2.30 m); agents are removed past the outer wall's outer face (92.71 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 1774 | 2.9% | 17.3% |
| -x | avenue | 5.66 | 1763 | 2.9% | 17.2% |
| +y | avenue | 5.66 | 1765 | 2.9% | 17.2% |
| -y | avenue | 5.66 | 1755 | 2.9% | 17.1% |
| door +x+y (y wall) 0 | door | 2.30 | 1483 | 2.5% | 35.6% |
| door +x+y (y wall) 1 | door | 2.30 | 1677 | 2.8% | 40.2% |
| door +x+y (y wall) 2 | door | 2.30 | 1538 | 2.6% | 36.9% |
| door +x+y (y wall) 3 | door | 2.30 | 1208 | 2.0% | 29.0% |
| door +x+y (y wall) 4 | door | 2.30 | 494 | 0.8% | 11.8% |
| door +x+y (x wall) 0 | door | 2.30 | 1502 | 2.5% | 36.0% |
| door +x+y (x wall) 1 | door | 2.30 | 1669 | 2.8% | 40.0% |
| door +x+y (x wall) 2 | door | 2.30 | 1515 | 2.5% | 36.3% |
| door +x+y (x wall) 3 | door | 2.30 | 1228 | 2.0% | 29.4% |
| door +x+y (x wall) 4 | door | 2.30 | 607 | 1.0% | 14.6% |
| door +x+y (corner) | door | 2.30 | 337 | 0.6% | 8.1% |
| door -x+y (y wall) 0 | door | 2.30 | 1488 | 2.5% | 35.7% |
| door -x+y (y wall) 1 | door | 2.30 | 1670 | 2.8% | 40.0% |
| door -x+y (y wall) 2 | door | 2.30 | 1534 | 2.5% | 36.8% |
| door -x+y (y wall) 3 | door | 2.30 | 1244 | 2.1% | 29.8% |
| door -x+y (y wall) 4 | door | 2.30 | 516 | 0.9% | 12.4% |
| door -x+y (x wall) 0 | door | 2.30 | 1499 | 2.5% | 35.9% |
| door -x+y (x wall) 1 | door | 2.30 | 1669 | 2.8% | 40.0% |
| door -x+y (x wall) 2 | door | 2.30 | 1551 | 2.6% | 37.2% |
| door -x+y (x wall) 3 | door | 2.30 | 1242 | 2.1% | 29.8% |
| door -x+y (x wall) 4 | door | 2.30 | 530 | 0.9% | 12.7% |
| door -x+y (corner) | door | 2.30 | 354 | 0.6% | 8.5% |
| door -x-y (y wall) 0 | door | 2.30 | 1498 | 2.5% | 35.9% |
| door -x-y (y wall) 1 | door | 2.30 | 1710 | 2.8% | 41.0% |
| door -x-y (y wall) 2 | door | 2.30 | 1464 | 2.4% | 35.1% |
| door -x-y (y wall) 3 | door | 2.30 | 1108 | 1.8% | 26.6% |
| door -x-y (y wall) 4 | door | 2.30 | 662 | 1.1% | 15.9% |
| door -x-y (x wall) 0 | door | 2.30 | 1478 | 2.5% | 35.4% |
| door -x-y (x wall) 1 | door | 2.30 | 1679 | 2.8% | 40.3% |
| door -x-y (x wall) 2 | door | 2.30 | 1491 | 2.5% | 35.7% |
| door -x-y (x wall) 3 | door | 2.30 | 1147 | 1.9% | 27.5% |
| door -x-y (x wall) 4 | door | 2.30 | 621 | 1.0% | 14.9% |
| door -x-y (corner) | door | 2.30 | 434 | 0.7% | 10.4% |
| door +x-y (y wall) 0 | door | 2.30 | 1500 | 2.5% | 36.0% |
| door +x-y (y wall) 1 | door | 2.30 | 1698 | 2.8% | 40.7% |
| door +x-y (y wall) 2 | door | 2.30 | 1516 | 2.5% | 36.3% |
| door +x-y (y wall) 3 | door | 2.30 | 1091 | 1.8% | 26.2% |
| door +x-y (y wall) 4 | door | 2.30 | 659 | 1.1% | 15.8% |
| door +x-y (x wall) 0 | door | 2.30 | 1515 | 2.5% | 36.3% |
| door +x-y (x wall) 1 | door | 2.30 | 1688 | 2.8% | 40.5% |
| door +x-y (x wall) 2 | door | 2.30 | 1513 | 2.5% | 36.3% |
| door +x-y (x wall) 3 | door | 2.30 | 1144 | 1.9% | 27.4% |
| door +x-y (x wall) 4 | door | 2.30 | 665 | 1.1% | 15.9% |
| door +x-y (corner) | door | 2.30 | 360 | 0.6% | 8.6% |
| **doors (44)** | door | 101.20 | 53196 | 88.3% | |
| **avenues (4)** | avenue | 22.64 | 7057 | 11.7% | |

**Unused exit width: 0.0 of 123.8 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 1301.7 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 26.8%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 2210 | 3.7% | 2210 | 3.7% |
| straight +x+y (y wing) 1 | straight | yes | 1784 | 3.0% | 1691 | 2.8% |
| straight +x+y (y wing) 2 | straight | yes | 1558 | 2.6% | 1544 | 2.6% |
| straight +x+y (y wing) 3 | straight | yes | 1219 | 2.0% | 1217 | 2.0% |
| straight +x+y (y wing) 4 | straight | yes | 492 | 0.8% | 479 | 0.8% |
| straight +x+y (x wing) 0 | straight | yes | 2224 | 3.7% | 2224 | 3.7% |
| straight +x+y (x wing) 1 | straight | yes | 1778 | 3.0% | 1673 | 2.8% |
| straight +x+y (x wing) 2 | straight | yes | 1533 | 2.5% | 1521 | 2.5% |
| straight +x+y (x wing) 3 | straight | yes | 1241 | 2.1% | 1240 | 2.1% |
| straight +x+y (x wing) 4 | straight | yes | 608 | 1.0% | 587 | 1.0% |
| corner +x+y | corner | yes | 1957 | 3.2% | 639 | 1.1% |
| straight -x+y (y wing) 0 | straight | yes | 2203 | 3.7% | 2203 | 3.7% |
| straight -x+y (y wing) 1 | straight | yes | 1799 | 3.0% | 1675 | 2.8% |
| straight -x+y (y wing) 2 | straight | yes | 1551 | 2.6% | 1540 | 2.6% |
| straight -x+y (y wing) 3 | straight | yes | 1243 | 2.1% | 1242 | 2.1% |
| straight -x+y (y wing) 4 | straight | yes | 528 | 0.9% | 512 | 0.8% |
| straight -x+y (x wing) 0 | straight | yes | 2210 | 3.7% | 2209 | 3.7% |
| straight -x+y (x wing) 1 | straight | yes | 1798 | 3.0% | 1673 | 2.8% |
| straight -x+y (x wing) 2 | straight | yes | 1564 | 2.6% | 1551 | 2.6% |
| straight -x+y (x wing) 3 | straight | yes | 1251 | 2.1% | 1250 | 2.1% |
| straight -x+y (x wing) 4 | straight | yes | 545 | 0.9% | 522 | 0.9% |
| corner -x+y | corner | yes | 2038 | 3.4% | 704 | 1.2% |
| straight -x-y (y wing) 0 | straight | yes | 2201 | 3.7% | 2201 | 3.7% |
| straight -x-y (y wing) 1 | straight | yes | 1798 | 3.0% | 1722 | 2.9% |
| straight -x-y (y wing) 2 | straight | yes | 1524 | 2.5% | 1502 | 2.5% |
| straight -x-y (y wing) 3 | straight | yes | 1099 | 1.8% | 1094 | 1.8% |
| straight -x-y (y wing) 4 | straight | yes | 658 | 1.1% | 638 | 1.1% |
| straight -x-y (x wing) 0 | straight | yes | 2205 | 3.7% | 2205 | 3.7% |
| straight -x-y (x wing) 1 | straight | yes | 1778 | 3.0% | 1693 | 2.8% |
| straight -x-y (x wing) 2 | straight | yes | 1575 | 2.6% | 1560 | 2.6% |
| straight -x-y (x wing) 3 | straight | yes | 1093 | 1.8% | 1090 | 1.8% |
| straight -x-y (x wing) 4 | straight | yes | 625 | 1.0% | 609 | 1.0% |
| corner -x-y | corner | yes | 1988 | 3.3% | 725 | 1.2% |
| straight +x-y (y wing) 0 | straight | yes | 2228 | 3.7% | 2228 | 3.7% |
| straight +x-y (y wing) 1 | straight | yes | 1791 | 3.0% | 1709 | 2.8% |
| straight +x-y (y wing) 2 | straight | yes | 1557 | 2.6% | 1539 | 2.6% |
| straight +x-y (y wing) 3 | straight | yes | 1110 | 1.8% | 1104 | 1.8% |
| straight +x-y (y wing) 4 | straight | yes | 635 | 1.1% | 622 | 1.0% |
| straight +x-y (x wing) 0 | straight | yes | 2243 | 3.7% | 2243 | 3.7% |
| straight +x-y (x wing) 1 | straight | yes | 1812 | 3.0% | 1709 | 2.8% |
| straight +x-y (x wing) 2 | straight | yes | 1553 | 2.6% | 1535 | 2.5% |
| straight +x-y (x wing) 3 | straight | yes | 1158 | 1.9% | 1158 | 1.9% |
| straight +x-y (x wing) 4 | straight | yes | 644 | 1.1% | 629 | 1.0% |
| corner +x-y | corner | yes | 1962 | 3.3% | 632 | 1.0% |
| **straight (40)** | | | 58626 | | 57553 | 95.5% |
| **corner (4)** | | | 7945 | | 2700 | 4.5% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 1774 | 70.5 | 867.0 | 0.28 | 0.31 | 0.0% |
| -x | 1763 | 70.5 | 877.3 | 0.28 | 0.32 | 0.0% |
| +y | 1765 | 70.5 | 867.4 | 0.28 | 0.32 | 0.0% |
| -y | 1755 | 70.5 | 863.9 | 0.28 | 0.32 | 0.0% |
| door +x+y (y wall) 0 | 1483 | 4.9 | 941.0 | 0.49 | 0.69 | 0.0% |
| door +x+y (y wall) 1 | 1677 | 4.9 | 1053.5 | 0.50 | 0.69 | 0.0% |
| door +x+y (y wall) 2 | 1538 | 4.9 | 1099.1 | 0.44 | 0.69 | 0.0% |
| door +x+y (y wall) 3 | 1208 | 4.9 | 1107.5 | 0.34 | 0.69 | 0.0% |
| door +x+y (y wall) 4 | 494 | 4.9 | 1068.7 | 0.14 | 0.72 | 0.0% |
| door +x+y (x wall) 0 | 1502 | 5.1 | 869.5 | 0.54 | 0.66 | 0.0% |
| door +x+y (x wall) 1 | 1669 | 4.9 | 1049.4 | 0.50 | 0.66 | 0.0% |
| door +x+y (x wall) 2 | 1515 | 4.9 | 1099.3 | 0.43 | 0.69 | 0.0% |
| door +x+y (x wall) 3 | 1228 | 4.9 | 1111.4 | 0.35 | 0.69 | 0.0% |
| door +x+y (x wall) 4 | 607 | 5.1 | 1054.0 | 0.18 | 0.69 | 0.0% |
| door +x+y (corner) | 337 | 6.3 | 938.4 | 0.11 | 0.69 | 0.0% |
| door -x+y (y wall) 0 | 1488 | 4.9 | 938.7 | 0.50 | 0.72 | 0.0% |
| door -x+y (y wall) 1 | 1670 | 4.9 | 1002.2 | 0.52 | 0.69 | 0.0% |
| door -x+y (y wall) 2 | 1534 | 4.9 | 1087.6 | 0.44 | 0.69 | 0.0% |
| door -x+y (y wall) 3 | 1244 | 4.9 | 1090.9 | 0.36 | 0.69 | 0.0% |
| door -x+y (y wall) 4 | 516 | 5.1 | 1102.4 | 0.15 | 0.69 | 0.0% |
| door -x+y (x wall) 0 | 1499 | 4.9 | 935.1 | 0.50 | 0.72 | 0.0% |
| door -x+y (x wall) 1 | 1669 | 4.9 | 1071.8 | 0.49 | 0.72 | 0.0% |
| door -x+y (x wall) 2 | 1551 | 4.9 | 1089.8 | 0.45 | 0.69 | 0.0% |
| door -x+y (x wall) 3 | 1242 | 4.9 | 1076.7 | 0.36 | 0.69 | 0.0% |
| door -x+y (x wall) 4 | 530 | 4.9 | 1035.3 | 0.16 | 0.66 | 0.0% |
| door -x+y (corner) | 354 | 6.3 | 935.8 | 0.12 | 0.66 | 0.0% |
| door -x-y (y wall) 0 | 1498 | 4.9 | 942.0 | 0.50 | 0.69 | 0.0% |
| door -x-y (y wall) 1 | 1710 | 4.9 | 1185.5 | 0.45 | 0.69 | 0.0% |
| door -x-y (y wall) 2 | 1464 | 4.9 | 1301.7 | 0.35 | 0.72 | 0.0% |
| door -x-y (y wall) 3 | 1108 | 4.9 | 1295.4 | 0.27 | 0.72 | 0.0% |
| door -x-y (y wall) 4 | 662 | 4.9 | 1168.6 | 0.18 | 0.72 | 0.0% |
| door -x-y (x wall) 0 | 1478 | 4.9 | 942.6 | 0.49 | 0.69 | 0.0% |
| door -x-y (x wall) 1 | 1679 | 4.9 | 1185.2 | 0.44 | 0.69 | 0.0% |
| door -x-y (x wall) 2 | 1491 | 4.9 | 1290.6 | 0.36 | 0.69 | 0.0% |
| door -x-y (x wall) 3 | 1147 | 4.9 | 1299.7 | 0.28 | 0.72 | 0.0% |
| door -x-y (x wall) 4 | 621 | 5.1 | 1293.6 | 0.15 | 0.66 | 0.0% |
| door -x-y (corner) | 434 | 6.3 | 909.7 | 0.15 | 0.66 | 0.0% |
| door +x-y (y wall) 0 | 1500 | 4.9 | 952.7 | 0.49 | 0.72 | 0.0% |
| door +x-y (y wall) 1 | 1698 | 4.9 | 1142.7 | 0.47 | 0.66 | 0.0% |
| door +x-y (y wall) 2 | 1516 | 4.9 | 1148.8 | 0.41 | 0.69 | 0.0% |
| door +x-y (y wall) 3 | 1091 | 4.9 | 1155.4 | 0.30 | 0.66 | 0.0% |
| door +x-y (y wall) 4 | 659 | 5.1 | 1129.2 | 0.18 | 0.66 | 0.0% |
| door +x-y (x wall) 0 | 1515 | 4.9 | 961.5 | 0.49 | 0.72 | 0.0% |
| door +x-y (x wall) 1 | 1688 | 4.9 | 1152.1 | 0.46 | 0.69 | 0.0% |
| door +x-y (x wall) 2 | 1513 | 4.9 | 1147.2 | 0.41 | 0.69 | 0.0% |
| door +x-y (x wall) 3 | 1144 | 4.9 | 1140.7 | 0.31 | 0.69 | 0.0% |
| door +x-y (x wall) 4 | 665 | 5.1 | 1144.4 | 0.18 | 0.72 | 0.0% |
| door +x-y (corner) | 360 | 6.5 | 943.8 | 0.12 | 0.66 | 0.0% |

Mean flow / w J averaged over the doors 0.35, over the avenues 0.28.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 103.1 | 2210 | 1469 / 741 / 781 | 0.7 | 844.8 | 3.54 | 5.92 | 89% | 85% | 5% | 4.54 |
| straight +x+y (y wing) 1 | 1.20 | 81.5 | 1763 | 1691 / 0 / 204 | 0.7 | 1050.5 | 1.80 | 3.71 | 90% | 75% | 15% | 3.90 |
| straight +x+y (y wing) 2 | 1.20 | 61.0 | 1454 | 1544 / 0 / 17 | 0.7 | 1096.1 | 1.42 | 2.21 | 70% | 65% | 5% | 4.14 |
| straight +x+y (y wing) 3 | 1.20 | 39.4 | 880 | 1217 / 0 / 6 | 0.7 | 1104.5 | 1.11 | 2.31 | 59% | 40% | 20% | 3.23 |
| straight +x+y (y wing) 4 | 1.20 | 18.8 | 387 | 479 / 0 / 414 | 0.7 | 1065.7 | 0.84 | 3.41 | 42% | 17% | 25% | 2.06 |
| straight +x+y (x wing) 0 | 1.20 | 103.1 | 2224 | 1500 / 724 / 891 | 0.7 | 855.3 | 3.64 | 6.02 | 90% | 86% | 3% | 4.59 |
| straight +x+y (x wing) 1 | 1.20 | 81.5 | 1762 | 1673 / 0 / 196 | 0.7 | 1046.5 | 1.79 | 3.91 | 90% | 75% | 15% | 3.72 |
| straight +x+y (x wing) 2 | 1.20 | 61.0 | 1417 | 1521 / 0 / 18 | 0.7 | 1096.3 | 1.40 | 2.31 | 69% | 63% | 6% | 4.05 |
| straight +x+y (x wing) 3 | 1.20 | 39.4 | 877 | 1240 / 0 / 19 | 0.7 | 1108.4 | 1.14 | 2.51 | 68% | 38% | 29% | 2.87 |
| straight +x+y (x wing) 4 | 1.20 | 18.8 | 380 | 587 / 0 / 24 | 0.7 | 1051.0 | 0.58 | 2.41 | 17% | 17% | 0% | 4.05 |
| corner +x+y | 1.20 | 186.0 | 1671 | 337 / 302 / 1786 | 0.7 | 1058.4 | 2.29 | 6.72 | 91% | 71% | 20% | 2.89 |
| straight -x+y (y wing) 0 | 1.20 | 103.1 | 2203 | 1483 / 720 / 980 | 0.7 | 849.7 | 3.75 | 6.62 | 90% | 85% | 5% | 4.55 |
| straight -x+y (y wing) 1 | 1.20 | 81.5 | 1781 | 1675 / 0 / 258 | 0.7 | 999.2 | 1.94 | 3.71 | 90% | 75% | 15% | 3.78 |
| straight -x+y (y wing) 2 | 1.20 | 61.0 | 1434 | 1540 / 0 / 18 | 0.7 | 1084.6 | 1.44 | 2.31 | 70% | 64% | 6% | 4.08 |
| straight -x+y (y wing) 3 | 1.20 | 39.4 | 898 | 1242 / 0 / 9 | 0.7 | 1087.9 | 1.15 | 2.21 | 66% | 39% | 27% | 2.93 |
| straight -x+y (y wing) 4 | 1.20 | 18.8 | 371 | 512 / 0 / 34 | 0.7 | 1099.5 | 0.50 | 2.21 | 16% | 16% | 0% | 4.05 |
| straight -x+y (x wing) 0 | 1.20 | 103.1 | 2210 | 1495 / 714 / 799 | 0.7 | 844.6 | 3.56 | 5.92 | 89% | 87% | 2% | 4.63 |
| straight -x+y (x wing) 1 | 1.20 | 81.5 | 1774 | 1673 / 0 / 253 | 0.7 | 1068.9 | 1.80 | 4.21 | 85% | 71% | 14% | 3.86 |
| straight -x+y (x wing) 2 | 1.20 | 61.0 | 1454 | 1551 / 0 / 20 | 0.7 | 1086.9 | 1.45 | 2.41 | 73% | 64% | 9% | 3.90 |
| straight -x+y (x wing) 3 | 1.20 | 39.4 | 895 | 1250 / 0 / 7 | 0.7 | 1073.8 | 1.17 | 2.31 | 64% | 40% | 24% | 3.13 |
| straight -x+y (x wing) 4 | 1.20 | 18.8 | 378 | 522 / 0 / 35 | 0.7 | 1032.3 | 0.54 | 2.41 | 24% | 16% | 8% | 3.17 |
| corner -x+y | 1.20 | 186.0 | 1683 | 354 / 350 / 1418 | 0.7 | 1075.7 | 1.97 | 6.52 | 90% | 70% | 19% | 2.95 |
| straight -x-y (y wing) 0 | 1.20 | 103.1 | 2201 | 1486 / 715 / 856 | 0.7 | 851.1 | 3.59 | 6.22 | 90% | 85% | 5% | 4.54 |
| straight -x-y (y wing) 1 | 1.20 | 81.5 | 1784 | 1722 / 0 / 169 | 0.7 | 1182.7 | 1.60 | 3.81 | 87% | 67% | 20% | 3.65 |
| straight -x-y (y wing) 2 | 1.20 | 61.0 | 1414 | 1502 / 0 / 37 | 0.7 | 1298.7 | 1.19 | 2.31 | 63% | 52% | 11% | 3.78 |
| straight -x-y (y wing) 3 | 1.20 | 39.4 | 882 | 1094 / 0 / 7 | 0.7 | 1292.4 | 0.85 | 2.21 | 38% | 32% | 5% | 3.76 |
| straight -x-y (y wing) 4 | 1.20 | 18.8 | 383 | 638 / 0 / 25 | 0.7 | 1165.6 | 0.57 | 2.21 | 19% | 15% | 4% | 3.58 |
| straight -x-y (x wing) 0 | 1.20 | 103.1 | 2205 | 1464 / 741 / 830 | 0.7 | 852.3 | 3.56 | 6.22 | 90% | 84% | 6% | 4.39 |
| straight -x-y (x wing) 1 | 1.20 | 81.5 | 1762 | 1693 / 0 / 178 | 0.7 | 1182.2 | 1.58 | 3.81 | 87% | 67% | 19% | 3.68 |
| straight -x-y (x wing) 2 | 1.20 | 61.0 | 1449 | 1560 / 0 / 30 | 0.7 | 1287.7 | 1.24 | 2.51 | 63% | 55% | 8% | 3.88 |
| straight -x-y (x wing) 3 | 1.20 | 39.4 | 881 | 1090 / 0 / 20 | 0.7 | 1296.8 | 0.86 | 2.31 | 40% | 33% | 7% | 3.71 |
| straight -x-y (x wing) 4 | 1.20 | 18.8 | 363 | 609 / 0 / 23 | 0.7 | 1290.6 | 0.49 | 2.41 | 16% | 13% | 3% | 3.57 |
| corner -x-y | 1.20 | 186.0 | 1715 | 434 / 291 / 1350 | 0.7 | 1266.7 | 1.64 | 4.11 | 83% | 53% | 30% | 2.52 |
| straight +x-y (y wing) 0 | 1.20 | 103.1 | 2228 | 1490 / 738 / 917 | 0.7 | 835.7 | 3.77 | 5.82 | 89% | 86% | 4% | 4.56 |
| straight +x-y (y wing) 1 | 1.20 | 81.5 | 1751 | 1709 / 0 / 179 | 0.7 | 1139.7 | 1.66 | 3.81 | 86% | 71% | 15% | 3.76 |
| straight +x-y (y wing) 2 | 1.20 | 61.0 | 1451 | 1539 / 0 / 53 | 0.7 | 1145.8 | 1.39 | 2.31 | 72% | 63% | 10% | 3.84 |
| straight +x-y (y wing) 3 | 1.20 | 39.4 | 884 | 1104 / 0 / 23 | 0.7 | 1152.5 | 0.98 | 2.31 | 46% | 37% | 9% | 3.67 |
| straight +x-y (y wing) 4 | 1.20 | 18.8 | 366 | 622 / 0 / 19 | 0.7 | 1126.2 | 0.57 | 2.11 | 18% | 14% | 4% | 3.74 |
| straight +x-y (x wing) 0 | 1.20 | 103.1 | 2243 | 1494 / 749 / 826 | 0.7 | 858.8 | 3.58 | 5.42 | 89% | 84% | 5% | 4.48 |
| straight +x-y (x wing) 1 | 1.20 | 81.5 | 1796 | 1709 / 0 / 172 | 0.7 | 1149.1 | 1.64 | 3.81 | 84% | 71% | 13% | 3.99 |
| straight +x-y (x wing) 2 | 1.20 | 61.0 | 1446 | 1535 / 0 / 30 | 0.7 | 1144.2 | 1.37 | 2.51 | 73% | 62% | 11% | 3.75 |
| straight +x-y (x wing) 3 | 1.20 | 39.4 | 870 | 1158 / 0 / 22 | 0.7 | 1137.8 | 1.04 | 2.51 | 43% | 37% | 7% | 3.78 |
| straight +x-y (x wing) 4 | 1.20 | 18.8 | 379 | 629 / 0 / 37 | 0.7 | 1141.4 | 0.58 | 2.21 | 29% | 15% | 14% | 2.49 |
| corner +x-y | 1.20 | 186.0 | 1694 | 360 / 272 / 1479 | 0.7 | 1117.7 | 1.89 | 4.11 | 88% | 62% | 27% | 2.77 |

The last agent out (agent 38599, t100 1301.7 s): last gangway straight -x-y (y wing) 2, exit door -x-y (y wall) 2. The gangway that cleared last: straight -x-y (y wing) 2 at 1298.7 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 8804 | 7800.4 | 6.93 | 1297.5 / 1213.2 / 1088.4 | 1204.9 / 1140.6 / 1022.5 | 5113453.1 | 10366060 | 0.201 |
| gangway | 3792 | 3512.9 | 6.93 | 1295.2 / 1213.2 / 1088.4 | 1204.9 / 1140.6 / 1022.5 | 5113453.1 | 9667820 | 0.130 |
| walkway | 276 | 257.4 | 4.06 | 561.5 / 353.0 / 0.0 | 409.8 / 213.6 / 0.0 | 0.0 | 73078 | 0.678 |
| avenue | 1920 | 1801.4 | 1.90 | 750.2 / 0.0 / 0.0 | 573.2 / 0.0 / 0.0 | 0.0 | 422947 | 1.334 |
| exit | 4 | 2.0 | 0.00 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 0 | - |
| concourse | 2812 | 2226.8 | 2.76 | 1120.6 / 54.2 / 0.0 | 922.8 / 21.3 / 0.0 | 0.0 | 202215 | 1.042 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 25392 | 16030.4 | 7.74 | 1053.1 / 1046.5 / 1022.5 | 1052.6 / 1039.5 / 1011.7 | 5720007.7 | 14868692 | 0.031 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 208 x 208 from (-104, -104) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -34.5 | -34.5 | gangway | 1.00 | 5.91 | 1080.9 | 1069.6 | 1021.3 | 5911.5 | 0.009 |
| 2 | -35.5 | -35.5 | gangway | 1.00 | 5.65 | 1091.9 | 1087.6 | 1022.0 | 5331.5 | 0.013 |
| 3 | 35.5 | -35.5 | gangway | 1.00 | 5.74 | 1039.3 | 1032.3 | 944.8 | 5249.2 | 0.011 |
| 4 | -38.5 | -38.5 | gangway | 1.00 | 5.89 | 1128.3 | 1122.9 | 924.9 | 5247.6 | 0.017 |
| 5 | -34.5 | 34.5 | gangway | 1.00 | 6.00 | 983.2 | 974.9 | 900.4 | 5246.2 | 0.011 |
| 6 | 36.5 | 36.5 | gangway | 1.00 | 5.91 | 1004.7 | 1002.7 | 916.2 | 5242.2 | 0.014 |
| 7 | -39.5 | -39.5 | gangway | 1.00 | 5.80 | 1135.5 | 1133.4 | 924.7 | 5222.0 | 0.022 |
| 8 | 35.5 | 35.5 | gangway | 1.00 | 5.85 | 1000.1 | 995.6 | 934.4 | 5215.0 | 0.013 |
| 9 | 38.5 | -38.5 | gangway | 1.00 | 5.81 | 1054.2 | 1048.2 | 922.1 | 5077.4 | 0.020 |
| 10 | 36.5 | -36.5 | gangway | 1.00 | 5.69 | 1046.5 | 1044.4 | 916.5 | 5032.0 | 0.013 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -36.5 | -38.5 | seat row | 0.50 | 7.40 | 1047.5 | 1027.1 | 978.3 | 3493.7 | 0.006 |
| 2 | -38.5 | -36.5 | seat row | 0.50 | 7.18 | 1037.0 | 1029.7 | 1011.7 | 3483.5 | 0.006 |
| 3 | 38.5 | -36.5 | seat row | 0.50 | 7.27 | 991.9 | 988.7 | 969.7 | 3463.8 | 0.006 |
| 4 | -38.5 | -35.5 | seat row | 0.50 | 7.07 | 1016.7 | 1013.2 | 985.1 | 3428.1 | 0.005 |
| 5 | -35.5 | -38.5 | seat row | 0.50 | 7.20 | 1022.9 | 975.6 | 958.7 | 3389.2 | 0.005 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 7632; agent-steps of seated agents on another row's clearway: 1562920.

## Deposit check

Person-seconds deposited: 25240338.2, of them in excluded cells: 5585.722.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 5071910 overlapping pair-steps: p99 0.0031, max 0.1070 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0031 max 0.1070; venue-geometry 7: p99 0.0023 max 0.0023 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00765 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 53 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.44 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 3749 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
