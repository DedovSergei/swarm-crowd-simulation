# Experiment `L_load100_conservative`

**Task 5.9 stage 4: venue L, 100% load, the CONSERVATIVE stair spacing (the Green Guide's planning rate)**

Venue L (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (4000 x 4000), cache key a2f3aaf59c2252b7, content hash 022d17b202313d70). 63424 agents on 100% of the 63424 seats (spawnSeatedCrowd, seed 1337), buffer N = 65536, 9082 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (conservative)** (exit choice: 12991417 evaluations, 688522 switches, 0 forced choices).
Capacity: **within design capacity** (the L venue's design capacity 63424, jam capacity 171923: 23822.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-21T17:52:58, 1343.1 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 3298 | 576.8 |
| t90 | 6702 | 1172.2 |
| t100 | 9082 | 1588.5 |

t_p: the step by which ceil(p x 63424) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 2218 | 0 | 71.0 | 1268.1 | 19.6 | 25.5 | 80.5-90.4 |
| -x | 5.66 | 2282 | 0 | 71.0 | 1291.0 | 19.8 | 26.6 | 242.8-252.7 |
| +y | 5.66 | 2263 | 0 | 71.0 | 1268.8 | 20.0 | 26.6 | 510.9-520.9 |
| -y | 5.66 | 2339 | 0 | 71.0 | 1266.3 | 20.7 | 26.6 | 579.8-589.8 |
| door +x+y (y wall) 0 | 2.30 | 1511 | 2577 | 4.9 | 1247.1 | 31.7 | 44.5 | 23.1-33.1 |
| door +x+y (y wall) 1 | 2.30 | 1656 | 2137 | 4.9 | 1506.5 | 28.8 | 44.5 | 18.7-28.7 |
| door +x+y (y wall) 2 | 2.30 | 1602 | 1594 | 4.9 | 1547.4 | 27.1 | 41.9 | 13.8-23.8 |
| door +x+y (y wall) 3 | 2.30 | 1206 | 1045 | 4.9 | 1547.2 | 20.4 | 44.5 | 20.1-30.1 |
| door +x+y (y wall) 4 | 2.30 | 625 | 513 | 4.9 | 1536.4 | 10.6 | 44.5 | 26.2-36.2 |
| door +x+y (x wall) 0 | 2.30 | 1502 | 2577 | 4.9 | 1263.7 | 31.1 | 44.5 | 25.2-35.2 |
| door +x+y (x wall) 1 | 2.30 | 1652 | 2137 | 4.9 | 1511.2 | 28.6 | 44.5 | 21.9-31.8 |
| door +x+y (x wall) 2 | 2.30 | 1589 | 1594 | 4.9 | 1553.7 | 26.8 | 41.9 | 12.4-22.4 |
| door +x+y (x wall) 3 | 2.30 | 1196 | 1045 | 4.9 | 1541.6 | 20.3 | 44.5 | 25.0-35.0 |
| door +x+y (x wall) 4 | 2.30 | 596 | 513 | 5.1 | 1468.2 | 10.6 | 44.5 | 27.1-37.1 |
| door +x+y (corner) | 2.30 | 443 | 124 | 6.3 | 1237.8 | 9.4 | 41.9 | 61.7-71.7 |
| door -x+y (y wall) 0 | 2.30 | 1502 | 2577 | 4.9 | 1390.0 | 28.3 | 44.5 | 24.8-34.8 |
| door -x+y (y wall) 1 | 2.30 | 1665 | 2137 | 4.9 | 1533.4 | 28.4 | 41.9 | 6.3-16.3 |
| door -x+y (y wall) 2 | 2.30 | 1596 | 1594 | 4.9 | 1571.4 | 26.6 | 44.5 | 15.4-25.4 |
| door -x+y (y wall) 3 | 2.30 | 1256 | 1045 | 4.9 | 1547.4 | 21.2 | 44.5 | 15.6-25.5 |
| door -x+y (y wall) 4 | 2.30 | 602 | 513 | 5.1 | 1529.2 | 10.3 | 41.9 | 13.1-23.1 |
| door -x+y (x wall) 0 | 2.30 | 1512 | 2577 | 4.9 | 1251.3 | 31.6 | 41.9 | 14.0-24.0 |
| door -x+y (x wall) 1 | 2.30 | 1640 | 2137 | 4.9 | 1524.7 | 28.1 | 44.5 | 17.7-27.6 |
| door -x+y (x wall) 2 | 2.30 | 1581 | 1594 | 4.9 | 1554.7 | 26.6 | 41.9 | 13.8-23.8 |
| door -x+y (x wall) 3 | 2.30 | 1238 | 1045 | 4.9 | 1571.7 | 20.6 | 41.9 | 13.8-23.8 |
| door -x+y (x wall) 4 | 2.30 | 592 | 513 | 4.9 | 1569.6 | 9.9 | 41.9 | 9.1-19.1 |
| door -x+y (corner) | 2.30 | 404 | 124 | 6.3 | 1453.5 | 7.3 | 41.9 | 61.4-71.4 |
| door -x-y (y wall) 0 | 2.30 | 1490 | 2577 | 4.9 | 1247.8 | 31.3 | 44.5 | 26.9-36.9 |
| door -x-y (y wall) 1 | 2.30 | 1677 | 2137 | 4.9 | 1499.0 | 29.3 | 44.5 | 30.3-40.2 |
| door -x-y (y wall) 2 | 2.30 | 1615 | 1594 | 4.9 | 1586.8 | 26.6 | 44.5 | 20.3-30.3 |
| door -x-y (y wall) 3 | 2.30 | 1099 | 1045 | 4.9 | 1587.8 | 18.1 | 44.5 | 25.7-35.7 |
| door -x-y (y wall) 4 | 2.30 | 767 | 513 | 4.9 | 1566.6 | 12.8 | 44.5 | 17.1-27.1 |
| door -x-y (x wall) 0 | 2.30 | 1485 | 2577 | 4.9 | 1231.2 | 31.6 | 44.5 | 24.8-34.8 |
| door -x-y (x wall) 1 | 2.30 | 1664 | 2137 | 4.9 | 1496.3 | 29.1 | 44.5 | 19.8-29.7 |
| door -x-y (x wall) 2 | 2.30 | 1584 | 1594 | 4.9 | 1580.6 | 26.2 | 44.5 | 24.8-34.8 |
| door -x-y (x wall) 3 | 2.30 | 1136 | 1045 | 4.9 | 1588.5 | 18.7 | 44.5 | 15.7-25.7 |
| door -x-y (x wall) 4 | 2.30 | 632 | 513 | 5.1 | 1522.4 | 10.9 | 44.5 | 26.1-36.0 |
| door -x-y (corner) | 2.30 | 439 | 124 | 6.3 | 1202.5 | 9.6 | 41.9 | 49.7-59.6 |
| door +x-y (y wall) 0 | 2.30 | 1507 | 2577 | 4.9 | 1402.6 | 28.1 | 44.5 | 15.6-25.5 |
| door +x-y (y wall) 1 | 2.30 | 1668 | 2137 | 4.9 | 1479.0 | 29.5 | 44.5 | 15.6-25.5 |
| door +x-y (y wall) 2 | 2.30 | 1635 | 1594 | 4.9 | 1531.0 | 27.9 | 41.9 | 6.3-16.3 |
| door +x-y (y wall) 3 | 2.30 | 1166 | 1045 | 4.9 | 1561.6 | 19.5 | 44.5 | 24.8-34.8 |
| door +x-y (y wall) 4 | 2.30 | 621 | 513 | 5.1 | 1574.7 | 10.3 | 47.1 | 581.2-591.2 |
| door +x-y (x wall) 0 | 2.30 | 1495 | 2577 | 4.9 | 1371.8 | 28.5 | 44.5 | 30.8-40.8 |
| door +x-y (x wall) 1 | 2.30 | 1673 | 2137 | 4.9 | 1458.5 | 30.0 | 41.9 | 12.4-22.4 |
| door +x-y (x wall) 2 | 2.30 | 1656 | 1594 | 4.9 | 1558.1 | 27.8 | 44.5 | 25.2-35.2 |
| door +x-y (x wall) 3 | 2.30 | 1085 | 1045 | 4.9 | 1579.8 | 18.0 | 41.9 | 10.0-19.9 |
| door +x-y (x wall) 4 | 2.30 | 613 | 513 | 5.1 | 1584.0 | 10.1 | 41.9 | 12.6-22.6 |
| door +x-y (corner) | 2.30 | 449 | 124 | 6.5 | 929.5 | 12.7 | 41.9 | 20.5-30.4 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (2.30 m; a corner door's: the gap between its wall ends, 2.30 m); agents are removed past the outer wall's outer face (92.71 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 2218 | 3.5% | 17.7% |
| -x | avenue | 5.66 | 2282 | 3.6% | 18.2% |
| +y | avenue | 5.66 | 2263 | 3.6% | 18.1% |
| -y | avenue | 5.66 | 2339 | 3.7% | 18.7% |
| door +x+y (y wall) 0 | door | 2.30 | 1511 | 2.4% | 29.7% |
| door +x+y (y wall) 1 | door | 2.30 | 1656 | 2.6% | 32.5% |
| door +x+y (y wall) 2 | door | 2.30 | 1602 | 2.5% | 31.5% |
| door +x+y (y wall) 3 | door | 2.30 | 1206 | 1.9% | 23.7% |
| door +x+y (y wall) 4 | door | 2.30 | 625 | 1.0% | 12.3% |
| door +x+y (x wall) 0 | door | 2.30 | 1502 | 2.4% | 29.5% |
| door +x+y (x wall) 1 | door | 2.30 | 1652 | 2.6% | 32.5% |
| door +x+y (x wall) 2 | door | 2.30 | 1589 | 2.5% | 31.2% |
| door +x+y (x wall) 3 | door | 2.30 | 1196 | 1.9% | 23.5% |
| door +x+y (x wall) 4 | door | 2.30 | 596 | 0.9% | 11.7% |
| door +x+y (corner) | door | 2.30 | 443 | 0.7% | 8.7% |
| door -x+y (y wall) 0 | door | 2.30 | 1502 | 2.4% | 29.5% |
| door -x+y (y wall) 1 | door | 2.30 | 1665 | 2.6% | 32.7% |
| door -x+y (y wall) 2 | door | 2.30 | 1596 | 2.5% | 31.4% |
| door -x+y (y wall) 3 | door | 2.30 | 1256 | 2.0% | 24.7% |
| door -x+y (y wall) 4 | door | 2.30 | 602 | 0.9% | 11.8% |
| door -x+y (x wall) 0 | door | 2.30 | 1512 | 2.4% | 29.7% |
| door -x+y (x wall) 1 | door | 2.30 | 1640 | 2.6% | 32.2% |
| door -x+y (x wall) 2 | door | 2.30 | 1581 | 2.5% | 31.1% |
| door -x+y (x wall) 3 | door | 2.30 | 1238 | 2.0% | 24.3% |
| door -x+y (x wall) 4 | door | 2.30 | 592 | 0.9% | 11.6% |
| door -x+y (corner) | door | 2.30 | 404 | 0.6% | 7.9% |
| door -x-y (y wall) 0 | door | 2.30 | 1490 | 2.3% | 29.3% |
| door -x-y (y wall) 1 | door | 2.30 | 1677 | 2.6% | 32.9% |
| door -x-y (y wall) 2 | door | 2.30 | 1615 | 2.5% | 31.7% |
| door -x-y (y wall) 3 | door | 2.30 | 1099 | 1.7% | 21.6% |
| door -x-y (y wall) 4 | door | 2.30 | 767 | 1.2% | 15.1% |
| door -x-y (x wall) 0 | door | 2.30 | 1485 | 2.3% | 29.2% |
| door -x-y (x wall) 1 | door | 2.30 | 1664 | 2.6% | 32.7% |
| door -x-y (x wall) 2 | door | 2.30 | 1584 | 2.5% | 31.1% |
| door -x-y (x wall) 3 | door | 2.30 | 1136 | 1.8% | 22.3% |
| door -x-y (x wall) 4 | door | 2.30 | 632 | 1.0% | 12.4% |
| door -x-y (corner) | door | 2.30 | 439 | 0.7% | 8.6% |
| door +x-y (y wall) 0 | door | 2.30 | 1507 | 2.4% | 29.6% |
| door +x-y (y wall) 1 | door | 2.30 | 1668 | 2.6% | 32.8% |
| door +x-y (y wall) 2 | door | 2.30 | 1635 | 2.6% | 32.1% |
| door +x-y (y wall) 3 | door | 2.30 | 1166 | 1.8% | 22.9% |
| door +x-y (y wall) 4 | door | 2.30 | 621 | 1.0% | 12.2% |
| door +x-y (x wall) 0 | door | 2.30 | 1495 | 2.4% | 29.4% |
| door +x-y (x wall) 1 | door | 2.30 | 1673 | 2.6% | 32.9% |
| door +x-y (x wall) 2 | door | 2.30 | 1656 | 2.6% | 32.5% |
| door +x-y (x wall) 3 | door | 2.30 | 1085 | 1.7% | 21.3% |
| door +x-y (x wall) 4 | door | 2.30 | 613 | 1.0% | 12.0% |
| door +x-y (corner) | door | 2.30 | 449 | 0.7% | 8.8% |
| **doors (44)** | door | 101.20 | 54322 | 85.6% | |
| **avenues (4)** | avenue | 22.64 | 9102 | 14.4% | |

**Unused exit width: 0.0 of 123.8 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 1588.5 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 23.1%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 2324 | 3.7% | 2324 | 3.7% |
| straight +x+y (y wing) 1 | straight | yes | 1908 | 3.0% | 1656 | 2.6% |
| straight +x+y (y wing) 2 | straight | yes | 1618 | 2.6% | 1611 | 2.5% |
| straight +x+y (y wing) 3 | straight | yes | 1198 | 1.9% | 1197 | 1.9% |
| straight +x+y (y wing) 4 | straight | yes | 643 | 1.0% | 625 | 1.0% |
| straight +x+y (x wing) 0 | straight | yes | 2332 | 3.7% | 2331 | 3.7% |
| straight +x+y (x wing) 1 | straight | yes | 1900 | 3.0% | 1653 | 2.6% |
| straight +x+y (x wing) 2 | straight | yes | 1615 | 2.5% | 1610 | 2.5% |
| straight +x+y (x wing) 3 | straight | yes | 1178 | 1.9% | 1176 | 1.9% |
| straight +x+y (x wing) 4 | straight | yes | 611 | 1.0% | 595 | 0.9% |
| corner +x+y | corner | yes | 2317 | 3.7% | 1078 | 1.7% |
| straight -x+y (y wing) 0 | straight | yes | 2321 | 3.7% | 2321 | 3.7% |
| straight -x+y (y wing) 1 | straight | yes | 1902 | 3.0% | 1671 | 2.6% |
| straight -x+y (y wing) 2 | straight | yes | 1601 | 2.5% | 1598 | 2.5% |
| straight -x+y (y wing) 3 | straight | yes | 1256 | 2.0% | 1254 | 2.0% |
| straight -x+y (y wing) 4 | straight | yes | 627 | 1.0% | 602 | 0.9% |
| straight -x+y (x wing) 0 | straight | yes | 2332 | 3.7% | 2332 | 3.7% |
| straight -x+y (x wing) 1 | straight | yes | 1896 | 3.0% | 1640 | 2.6% |
| straight -x+y (x wing) 2 | straight | yes | 1598 | 2.5% | 1585 | 2.5% |
| straight -x+y (x wing) 3 | straight | yes | 1240 | 2.0% | 1240 | 2.0% |
| straight -x+y (x wing) 4 | straight | yes | 603 | 1.0% | 586 | 0.9% |
| corner -x+y | corner | yes | 2311 | 3.6% | 1027 | 1.6% |
| straight -x-y (y wing) 0 | straight | yes | 2315 | 3.7% | 2315 | 3.7% |
| straight -x-y (y wing) 1 | straight | yes | 1916 | 3.0% | 1677 | 2.6% |
| straight -x-y (y wing) 2 | straight | yes | 1627 | 2.6% | 1621 | 2.6% |
| straight -x-y (y wing) 3 | straight | yes | 1122 | 1.8% | 1111 | 1.8% |
| straight -x-y (y wing) 4 | straight | yes | 778 | 1.2% | 749 | 1.2% |
| straight -x-y (x wing) 0 | straight | yes | 2306 | 3.6% | 2306 | 3.6% |
| straight -x-y (x wing) 1 | straight | yes | 1918 | 3.0% | 1664 | 2.6% |
| straight -x-y (x wing) 2 | straight | yes | 1612 | 2.5% | 1606 | 2.5% |
| straight -x-y (x wing) 3 | straight | yes | 1148 | 1.8% | 1134 | 1.8% |
| straight -x-y (x wing) 4 | straight | yes | 634 | 1.0% | 612 | 1.0% |
| corner -x-y | corner | yes | 2325 | 3.7% | 1061 | 1.7% |
| straight +x-y (y wing) 0 | straight | yes | 2324 | 3.7% | 2324 | 3.7% |
| straight +x-y (y wing) 1 | straight | yes | 1915 | 3.0% | 1677 | 2.6% |
| straight +x-y (y wing) 2 | straight | yes | 1654 | 2.6% | 1650 | 2.6% |
| straight +x-y (y wing) 3 | straight | yes | 1161 | 1.8% | 1157 | 1.8% |
| straight +x-y (y wing) 4 | straight | yes | 632 | 1.0% | 615 | 1.0% |
| straight +x-y (x wing) 0 | straight | yes | 2317 | 3.7% | 2316 | 3.7% |
| straight +x-y (x wing) 1 | straight | yes | 1936 | 3.1% | 1686 | 2.7% |
| straight +x-y (x wing) 2 | straight | yes | 1672 | 2.6% | 1664 | 2.6% |
| straight +x-y (x wing) 3 | straight | yes | 1097 | 1.7% | 1095 | 1.7% |
| straight +x-y (x wing) 4 | straight | yes | 623 | 1.0% | 595 | 0.9% |
| corner +x-y | corner | yes | 2308 | 3.6% | 1077 | 1.7% |
| **straight (40)** | | | 61410 | | 59181 | 93.3% |
| **corner (4)** | | | 9261 | | 4243 | 6.7% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 2218 | 71.0 | 1268.1 | 0.23 | 0.31 | 0.0% |
| -x | 2282 | 71.0 | 1291.0 | 0.24 | 0.32 | 0.0% |
| +y | 2263 | 71.0 | 1268.8 | 0.24 | 0.32 | 0.0% |
| -y | 2339 | 71.0 | 1266.3 | 0.25 | 0.32 | 0.0% |
| door +x+y (y wall) 0 | 1511 | 4.9 | 1247.1 | 0.38 | 0.53 | 0.0% |
| door +x+y (y wall) 1 | 1656 | 4.9 | 1506.5 | 0.34 | 0.53 | 0.0% |
| door +x+y (y wall) 2 | 1602 | 4.9 | 1547.4 | 0.32 | 0.50 | 0.0% |
| door +x+y (y wall) 3 | 1206 | 4.9 | 1547.2 | 0.24 | 0.53 | 0.0% |
| door +x+y (y wall) 4 | 625 | 4.9 | 1536.4 | 0.13 | 0.53 | 0.0% |
| door +x+y (x wall) 0 | 1502 | 4.9 | 1263.7 | 0.37 | 0.53 | 0.0% |
| door +x+y (x wall) 1 | 1652 | 4.9 | 1511.2 | 0.34 | 0.53 | 0.0% |
| door +x+y (x wall) 2 | 1589 | 4.9 | 1553.7 | 0.32 | 0.50 | 0.0% |
| door +x+y (x wall) 3 | 1196 | 4.9 | 1541.6 | 0.24 | 0.53 | 0.0% |
| door +x+y (x wall) 4 | 596 | 5.1 | 1468.2 | 0.13 | 0.53 | 0.0% |
| door +x+y (corner) | 443 | 6.3 | 1237.8 | 0.11 | 0.50 | 0.0% |
| door -x+y (y wall) 0 | 1502 | 4.9 | 1390.0 | 0.34 | 0.53 | 0.0% |
| door -x+y (y wall) 1 | 1665 | 4.9 | 1533.4 | 0.34 | 0.50 | 0.0% |
| door -x+y (y wall) 2 | 1596 | 4.9 | 1571.4 | 0.32 | 0.53 | 0.0% |
| door -x+y (y wall) 3 | 1256 | 4.9 | 1547.4 | 0.25 | 0.53 | 0.0% |
| door -x+y (y wall) 4 | 602 | 5.1 | 1529.2 | 0.12 | 0.50 | 0.0% |
| door -x+y (x wall) 0 | 1512 | 4.9 | 1251.3 | 0.38 | 0.50 | 0.0% |
| door -x+y (x wall) 1 | 1640 | 4.9 | 1524.7 | 0.34 | 0.53 | 0.0% |
| door -x+y (x wall) 2 | 1581 | 4.9 | 1554.7 | 0.32 | 0.50 | 0.0% |
| door -x+y (x wall) 3 | 1238 | 4.9 | 1571.7 | 0.25 | 0.50 | 0.0% |
| door -x+y (x wall) 4 | 592 | 4.9 | 1569.6 | 0.12 | 0.50 | 0.0% |
| door -x+y (corner) | 404 | 6.3 | 1453.5 | 0.09 | 0.50 | 0.0% |
| door -x-y (y wall) 0 | 1490 | 4.9 | 1247.8 | 0.37 | 0.53 | 0.0% |
| door -x-y (y wall) 1 | 1677 | 4.9 | 1499.0 | 0.35 | 0.53 | 0.0% |
| door -x-y (y wall) 2 | 1615 | 4.9 | 1586.8 | 0.32 | 0.53 | 0.0% |
| door -x-y (y wall) 3 | 1099 | 4.9 | 1587.8 | 0.22 | 0.53 | 0.0% |
| door -x-y (y wall) 4 | 767 | 4.9 | 1566.6 | 0.15 | 0.53 | 0.0% |
| door -x-y (x wall) 0 | 1485 | 4.9 | 1231.2 | 0.38 | 0.53 | 0.0% |
| door -x-y (x wall) 1 | 1664 | 4.9 | 1496.3 | 0.35 | 0.53 | 0.0% |
| door -x-y (x wall) 2 | 1584 | 4.9 | 1580.6 | 0.31 | 0.53 | 0.0% |
| door -x-y (x wall) 3 | 1136 | 4.9 | 1588.5 | 0.22 | 0.53 | 0.0% |
| door -x-y (x wall) 4 | 632 | 5.1 | 1522.4 | 0.13 | 0.53 | 0.0% |
| door -x-y (corner) | 439 | 6.3 | 1202.5 | 0.11 | 0.50 | 0.0% |
| door +x-y (y wall) 0 | 1507 | 4.9 | 1402.6 | 0.34 | 0.53 | 0.0% |
| door +x-y (y wall) 1 | 1668 | 4.9 | 1479.0 | 0.35 | 0.53 | 0.0% |
| door +x-y (y wall) 2 | 1635 | 4.9 | 1531.0 | 0.33 | 0.50 | 0.0% |
| door +x-y (y wall) 3 | 1166 | 4.9 | 1561.6 | 0.23 | 0.53 | 0.0% |
| door +x-y (y wall) 4 | 621 | 5.1 | 1574.7 | 0.12 | 0.56 | 0.0% |
| door +x-y (x wall) 0 | 1495 | 4.9 | 1371.8 | 0.34 | 0.53 | 0.0% |
| door +x-y (x wall) 1 | 1673 | 4.9 | 1458.5 | 0.36 | 0.50 | 0.0% |
| door +x-y (x wall) 2 | 1656 | 4.9 | 1558.1 | 0.33 | 0.53 | 0.0% |
| door +x-y (x wall) 3 | 1085 | 4.9 | 1579.8 | 0.21 | 0.50 | 0.0% |
| door +x-y (x wall) 4 | 613 | 5.1 | 1584.0 | 0.12 | 0.50 | 0.0% |
| door +x-y (corner) | 449 | 6.5 | 929.5 | 0.15 | 0.50 | 0.0% |

Mean flow / w J averaged over the doors 0.26, over the avenues 0.24.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 103.1 | 2324 | 1511 / 813 / 1037 | 0.7 | 1244.1 | 2.70 | 4.51 | 91% | 89% | 2% | 4.45 |
| straight +x+y (y wing) 1 | 1.20 | 81.5 | 1885 | 1656 / 0 / 335 | 0.7 | 1503.5 | 1.32 | 2.51 | 91% | 59% | 32% | 3.19 |
| straight +x+y (y wing) 2 | 1.20 | 61.0 | 1530 | 1611 / 0 / 9 | 0.7 | 1544.4 | 1.05 | 1.71 | 80% | 67% | 13% | 3.72 |
| straight +x+y (y wing) 3 | 1.20 | 39.4 | 938 | 1197 / 0 / 4 | 0.7 | 1544.3 | 0.78 | 1.71 | 50% | 37% | 12% | 3.48 |
| straight +x+y (y wing) 4 | 1.20 | 18.8 | 393 | 625 / 0 / 22 | 0.7 | 1533.4 | 0.42 | 1.60 | 19% | 16% | 3% | 3.65 |
| straight +x+y (x wing) 0 | 1.20 | 103.1 | 2332 | 1501 / 830 / 1220 | 0.7 | 1235.7 | 2.87 | 4.71 | 92% | 88% | 4% | 4.28 |
| straight +x+y (x wing) 1 | 1.20 | 81.5 | 1868 | 1653 / 0 / 362 | 0.7 | 1508.2 | 1.34 | 2.81 | 91% | 59% | 32% | 3.08 |
| straight +x+y (x wing) 2 | 1.20 | 61.0 | 1531 | 1610 / 0 / 9 | 0.7 | 1550.7 | 1.04 | 1.60 | 79% | 67% | 12% | 3.64 |
| straight +x+y (x wing) 3 | 1.20 | 39.4 | 943 | 1176 / 0 / 12 | 0.7 | 1538.7 | 0.77 | 1.60 | 57% | 39% | 17% | 3.21 |
| straight +x+y (x wing) 4 | 1.20 | 18.8 | 373 | 595 / 0 / 22 | 0.7 | 1465.2 | 0.42 | 1.50 | 18% | 17% | 1% | 3.82 |
| corner +x+y | 1.20 | 186.0 | 1739 | 443 / 635 / 1297 | 0.7 | 1509.4 | 1.57 | 3.81 | 93% | 64% | 30% | 2.75 |
| straight -x+y (y wing) 0 | 1.20 | 103.1 | 2321 | 1496 / 825 / 1272 | 0.7 | 1229.4 | 2.92 | 4.71 | 91% | 87% | 4% | 4.40 |
| straight -x+y (y wing) 1 | 1.20 | 81.5 | 1878 | 1671 / 0 / 334 | 0.7 | 1530.4 | 1.31 | 2.81 | 92% | 57% | 35% | 3.04 |
| straight -x+y (y wing) 2 | 1.20 | 61.0 | 1506 | 1598 / 0 / 8 | 0.7 | 1568.4 | 1.02 | 1.60 | 78% | 65% | 13% | 3.74 |
| straight -x+y (y wing) 3 | 1.20 | 39.4 | 957 | 1254 / 0 / 11 | 0.7 | 1544.4 | 0.82 | 1.60 | 53% | 40% | 13% | 3.53 |
| straight -x+y (y wing) 4 | 1.20 | 18.8 | 393 | 602 / 0 / 29 | 0.7 | 1526.2 | 0.41 | 1.60 | 23% | 16% | 6% | 3.08 |
| straight -x+y (x wing) 0 | 1.20 | 103.1 | 2332 | 1512 / 822 / 1073 | 0.7 | 1248.3 | 2.73 | 4.31 | 91% | 88% | 3% | 4.41 |
| straight -x+y (x wing) 1 | 1.20 | 81.5 | 1875 | 1640 / 0 / 348 | 0.7 | 1521.7 | 1.31 | 2.71 | 91% | 58% | 33% | 3.08 |
| straight -x+y (x wing) 2 | 1.20 | 61.0 | 1521 | 1585 / 0 / 19 | 0.7 | 1551.8 | 1.03 | 1.71 | 82% | 67% | 15% | 3.63 |
| straight -x+y (x wing) 3 | 1.20 | 39.4 | 947 | 1240 / 0 / 6 | 0.7 | 1568.7 | 0.79 | 1.81 | 54% | 41% | 13% | 3.45 |
| straight -x+y (x wing) 4 | 1.20 | 18.8 | 374 | 586 / 0 / 84 | 0.7 | 1566.6 | 0.43 | 2.01 | 17% | 15% | 3% | 3.75 |
| corner -x+y | 1.20 | 186.0 | 1752 | 404 / 623 / 1431 | 0.7 | 1542.7 | 1.59 | 3.91 | 92% | 65% | 28% | 2.77 |
| straight -x-y (y wing) 0 | 1.20 | 103.1 | 2315 | 1490 / 825 / 1129 | 0.7 | 1244.8 | 2.77 | 5.02 | 92% | 87% | 5% | 4.37 |
| straight -x-y (y wing) 1 | 1.20 | 81.5 | 1892 | 1677 / 0 / 313 | 0.7 | 1496.0 | 1.33 | 2.71 | 93% | 60% | 33% | 3.11 |
| straight -x-y (y wing) 2 | 1.20 | 61.0 | 1539 | 1621 / 0 / 7 | 0.7 | 1583.8 | 1.03 | 1.71 | 81% | 67% | 14% | 3.64 |
| straight -x-y (y wing) 3 | 1.20 | 39.4 | 929 | 1111 / 0 / 32 | 0.7 | 1584.8 | 0.72 | 2.01 | 49% | 38% | 11% | 3.56 |
| straight -x-y (y wing) 4 | 1.20 | 18.8 | 406 | 749 / 0 / 30 | 0.7 | 1563.7 | 0.50 | 1.60 | 18% | 16% | 3% | 3.68 |
| straight -x-y (x wing) 0 | 1.20 | 103.1 | 2306 | 1485 / 821 / 1033 | 0.7 | 1228.2 | 2.72 | 4.61 | 92% | 87% | 5% | 4.35 |
| straight -x-y (x wing) 1 | 1.20 | 81.5 | 1895 | 1664 / 0 / 349 | 0.7 | 1493.4 | 1.35 | 2.91 | 93% | 61% | 32% | 3.30 |
| straight -x-y (x wing) 2 | 1.20 | 61.0 | 1521 | 1606 / 0 / 9 | 0.7 | 1577.7 | 1.02 | 1.71 | 81% | 69% | 12% | 3.67 |
| straight -x-y (x wing) 3 | 1.20 | 39.4 | 945 | 1134 / 0 / 19 | 0.7 | 1585.5 | 0.73 | 1.60 | 52% | 41% | 11% | 3.57 |
| straight -x-y (x wing) 4 | 1.20 | 18.8 | 378 | 612 / 0 / 27 | 0.7 | 1519.4 | 0.42 | 1.60 | 19% | 16% | 3% | 3.57 |
| corner -x-y | 1.20 | 186.0 | 1730 | 439 / 622 / 1340 | 0.7 | 1539.7 | 1.56 | 3.11 | 93% | 66% | 27% | 2.58 |
| straight +x-y (y wing) 0 | 1.20 | 103.1 | 2324 | 1498 / 826 / 1186 | 0.7 | 1235.7 | 2.84 | 4.51 | 92% | 89% | 3% | 4.39 |
| straight +x-y (y wing) 1 | 1.20 | 81.5 | 1896 | 1677 / 0 / 332 | 0.7 | 1476.0 | 1.36 | 2.91 | 93% | 60% | 32% | 3.22 |
| straight +x-y (y wing) 2 | 1.20 | 61.0 | 1517 | 1650 / 0 / 12 | 0.7 | 1528.0 | 1.09 | 1.81 | 82% | 67% | 15% | 3.75 |
| straight +x-y (y wing) 3 | 1.20 | 39.4 | 936 | 1157 / 0 / 8 | 0.7 | 1558.6 | 0.75 | 1.71 | 53% | 40% | 13% | 3.45 |
| straight +x-y (y wing) 4 | 1.20 | 18.8 | 378 | 615 / 0 / 21 | 0.7 | 1571.7 | 0.40 | 1.50 | 18% | 15% | 3% | 3.64 |
| straight +x-y (x wing) 0 | 1.20 | 103.1 | 2317 | 1482 / 835 / 1074 | 0.7 | 1234.7 | 2.75 | 4.61 | 91% | 89% | 2% | 4.37 |
| straight +x-y (x wing) 1 | 1.20 | 81.5 | 1908 | 1686 / 0 / 350 | 0.7 | 1455.6 | 1.40 | 2.81 | 94% | 60% | 34% | 3.10 |
| straight +x-y (x wing) 2 | 1.20 | 61.0 | 1521 | 1664 / 0 / 13 | 0.7 | 1555.1 | 1.08 | 1.60 | 79% | 67% | 12% | 3.72 |
| straight +x-y (x wing) 3 | 1.20 | 39.4 | 924 | 1095 / 0 / 14 | 0.7 | 1576.8 | 0.70 | 1.60 | 48% | 40% | 9% | 3.46 |
| straight +x-y (x wing) 4 | 1.20 | 18.8 | 394 | 595 / 0 / 28 | 0.7 | 1581.0 | 0.39 | 1.60 | 18% | 16% | 2% | 3.67 |
| corner +x-y | 1.20 | 186.0 | 1741 | 449 / 628 / 1291 | 0.7 | 1557.0 | 1.52 | 4.31 | 90% | 59% | 31% | 2.73 |

The last agent out (agent 40563, t100 1588.5 s): last gangway straight -x-y (x wing) 3, exit door -x-y (x wall) 3. The gangway that cleared last: straight -x-y (x wing) 3 at 1585.5 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 8804 | 7800.4 | 6.97 | 1585.0 / 1503.5 / 1452.6 | 1511.9 / 1476.0 / 1419.2 | 7765746.7 | 14275229 | 0.160 |
| gangway | 3792 | 3512.9 | 6.97 | 1583.1 / 1503.5 / 1452.6 | 1511.9 / 1476.0 / 1419.2 | 7765746.7 | 13444807 | 0.095 |
| walkway | 276 | 257.4 | 3.40 | 918.1 / 476.4 / 0.0 | 509.7 / 124.0 / 0.0 | 0.0 | 79785 | 0.824 |
| avenue | 1920 | 1801.4 | 1.82 | 935.4 / 0.0 / 0.0 | 658.5 / 0.0 / 0.0 | 0.0 | 545576 | 1.334 |
| exit | 4 | 2.0 | 0.00 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 0 | - |
| concourse | 2812 | 2226.8 | 2.64 | 1519.2 / 19.6 / 0.0 | 981.9 / 3.3 / 0.0 | 0.0 | 205061 | 1.037 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 25392 | 16030.4 | 7.74 | 1454.2 / 1442.1 / 1401.9 | 1439.1 / 1437.0 / 1392.3 | 9961164.3 | 24436437 | 0.020 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 208 x 208 from (-104, -104) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -34.5 | 34.5 | gangway | 1.00 | 6.12 | 1456.6 | 1448.6 | 1388.4 | 8092.2 | 0.004 |
| 2 | -38.5 | -38.5 | gangway | 1.00 | 6.08 | 1491.6 | 1476.0 | 1366.4 | 7889.5 | 0.010 |
| 3 | 38.5 | 38.5 | gangway | 1.00 | 5.97 | 1458.0 | 1432.0 | 1353.4 | 7837.0 | 0.009 |
| 4 | -38.5 | 38.5 | gangway | 1.00 | 6.00 | 1475.2 | 1456.3 | 1350.6 | 7818.0 | 0.009 |
| 5 | -34.5 | -34.5 | gangway | 1.00 | 5.66 | 1473.1 | 1465.4 | 1415.5 | 7813.5 | 0.004 |
| 6 | 36.5 | 36.5 | gangway | 1.00 | 5.77 | 1450.3 | 1436.5 | 1377.2 | 7727.1 | 0.006 |
| 7 | -36.5 | 36.5 | gangway | 1.00 | 5.68 | 1469.6 | 1457.3 | 1391.0 | 7686.9 | 0.005 |
| 8 | 34.5 | -34.5 | gangway | 1.00 | 5.84 | 1425.1 | 1415.2 | 1344.7 | 7646.5 | 0.003 |
| 9 | 34.5 | 34.5 | gangway | 1.00 | 5.87 | 1436.9 | 1429.0 | 1354.1 | 7622.4 | 0.004 |
| 10 | -39.5 | 39.5 | gangway | 1.00 | 5.99 | 1477.8 | 1446.3 | 1308.0 | 7614.7 | 0.012 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -36.5 | 38.5 | seat row | 0.50 | 7.53 | 1412.7 | 1402.9 | 1392.3 | 4947.6 | 0.004 |
| 2 | 40.5 | 42.5 | seat row | 0.50 | 7.48 | 1343.5 | 1340.1 | 1329.3 | 4848.7 | 0.007 |
| 3 | -38.5 | 36.5 | seat row | 0.50 | 7.22 | 1411.5 | 1390.5 | 1374.2 | 4816.8 | 0.003 |
| 4 | 50.5 | -48.5 | seat row | 0.50 | 7.17 | 1414.3 | 1411.7 | 1392.3 | 4780.9 | 0.004 |
| 5 | 38.5 | 36.5 | seat row | 0.50 | 7.52 | 1411.0 | 1397.3 | 1374.6 | 4764.5 | 0.005 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 9858; agent-steps of seated agents on another row's clearway: 1874393.

## Deposit check

Person-seconds deposited: 38717541.0, of them in excluded cells: 5874.370.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 9684175 overlapping pair-steps: p99 0.0019, max 0.0758 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0019 max 0.0758; venue-geometry 6: p99 0.0009 max 0.0009 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 65 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.57 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 4288 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
