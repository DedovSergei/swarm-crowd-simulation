# Experiment `L_load100_nearest`

**Task 5.9 stage 4: venue L, 100% load, nearest exit (incline speed, stair spacing): the uninformed-crowd bound**

Venue L (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (4000 x 4000), cache key a2f3aaf59c2252b7, content hash 022d17b202313d70). 63424 agents on 100% of the 63424 seats (spawnSeatedCrowd, seed 1337), buffer N = 65536, 11196 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **nearest exit, incline speed, stair spacing (empirical)**.
Capacity: **within design capacity** (the L venue's design capacity 63424, jam capacity 171923: 23822.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-21T18:41:41, 1056.1 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 3659 | 640.0 |
| t90 | 8474 | 1482.2 |
| t100 | 11196 | 1958.3 |

t_p: the step by which ceil(p x 63424) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| -x | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| +y | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| -y | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| door +x+y (y wall) 0 | 2.30 | 2577 | 2577 | 4.9 | 1942.5 | 34.7 | 41.9 | 5.9-15.9 |
| door +x+y (y wall) 1 | 2.30 | 2132 | 2137 | 4.9 | 1643.9 | 33.9 | 44.5 | 25.9-35.9 |
| door +x+y (y wall) 2 | 2.30 | 1606 | 1594 | 4.9 | 1239.0 | 33.9 | 44.5 | 22.6-32.5 |
| door +x+y (y wall) 3 | 2.30 | 1046 | 1045 | 4.9 | 816.3 | 33.6 | 47.1 | 16.3-26.2 |
| door +x+y (y wall) 4 | 2.30 | 512 | 513 | 4.9 | 417.7 | 32.3 | 47.1 | 8.7-18.7 |
| door +x+y (x wall) 0 | 2.30 | 2577 | 2577 | 4.9 | 1958.3 | 34.4 | 47.1 | 12.6-22.6 |
| door +x+y (x wall) 1 | 2.30 | 2142 | 2137 | 4.9 | 1650.2 | 34.0 | 47.1 | 12.6-22.6 |
| door +x+y (x wall) 2 | 2.30 | 1582 | 1594 | 4.9 | 1236.2 | 33.5 | 47.1 | 12.6-22.6 |
| door +x+y (x wall) 3 | 2.30 | 1044 | 1045 | 4.9 | 821.9 | 33.3 | 47.1 | 21.9-31.8 |
| door +x+y (x wall) 4 | 2.30 | 514 | 513 | 5.1 | 419.4 | 32.3 | 47.1 | 26.2-36.2 |
| door +x+y (corner) | 2.30 | 124 | 124 | 6.3 | 86.1 | 40.5 | 47.1 | 55.8-65.8 |
| door -x+y (y wall) 0 | 2.30 | 2577 | 2577 | 4.9 | 1950.6 | 34.5 | 47.1 | 27.1-37.1 |
| door -x+y (y wall) 1 | 2.30 | 2127 | 2137 | 4.9 | 1639.2 | 33.9 | 47.1 | 27.1-37.1 |
| door -x+y (y wall) 2 | 2.30 | 1584 | 1594 | 4.9 | 1238.0 | 33.5 | 44.5 | 11.4-21.3 |
| door -x+y (y wall) 3 | 2.30 | 1045 | 1045 | 4.9 | 817.5 | 33.5 | 47.1 | 19.6-29.6 |
| door -x+y (y wall) 4 | 2.30 | 511 | 513 | 5.1 | 423.3 | 31.9 | 44.5 | 13.3-23.3 |
| door -x+y (x wall) 0 | 2.30 | 2577 | 2577 | 4.9 | 1957.2 | 34.4 | 44.5 | 28.3-38.3 |
| door -x+y (x wall) 1 | 2.30 | 2147 | 2137 | 4.9 | 1639.2 | 34.3 | 44.5 | 24.1-34.1 |
| door -x+y (x wall) 2 | 2.30 | 1604 | 1594 | 4.9 | 1240.1 | 33.9 | 47.1 | 29.4-39.4 |
| door -x+y (x wall) 3 | 2.30 | 1045 | 1045 | 4.9 | 813.5 | 33.7 | 44.5 | 16.1-26.1 |
| door -x+y (x wall) 4 | 2.30 | 515 | 513 | 4.9 | 422.2 | 32.2 | 47.1 | 8.7-18.7 |
| door -x+y (corner) | 2.30 | 124 | 124 | 6.3 | 86.2 | 40.4 | 47.1 | 60.5-70.5 |
| door -x-y (y wall) 0 | 2.30 | 2577 | 2577 | 4.9 | 1946.2 | 34.6 | 44.5 | 27.1-37.1 |
| door -x-y (y wall) 1 | 2.30 | 2148 | 2137 | 4.9 | 1639.9 | 34.3 | 44.5 | 27.1-37.1 |
| door -x-y (y wall) 2 | 2.30 | 1606 | 1594 | 4.9 | 1233.3 | 34.1 | 44.5 | 26.9-36.9 |
| door -x-y (y wall) 3 | 2.30 | 1044 | 1045 | 4.9 | 815.6 | 33.6 | 44.5 | 27.1-37.1 |
| door -x-y (y wall) 4 | 2.30 | 514 | 513 | 4.9 | 418.9 | 32.4 | 47.1 | 14.3-24.3 |
| door -x-y (x wall) 0 | 2.30 | 2577 | 2577 | 4.9 | 1956.0 | 34.5 | 47.1 | 27.1-37.1 |
| door -x-y (x wall) 1 | 2.30 | 2126 | 2137 | 4.9 | 1640.6 | 33.9 | 47.1 | 21.0-31.0 |
| door -x-y (x wall) 2 | 2.30 | 1582 | 1594 | 4.9 | 1234.0 | 33.6 | 44.5 | 11.4-21.3 |
| door -x-y (x wall) 3 | 2.30 | 1046 | 1045 | 4.9 | 818.9 | 33.5 | 44.5 | 11.4-21.3 |
| door -x-y (x wall) 4 | 2.30 | 512 | 513 | 5.1 | 422.6 | 32.0 | 44.5 | 13.6-23.6 |
| door -x-y (corner) | 2.30 | 124 | 124 | 6.3 | 88.0 | 39.5 | 47.1 | 66.1-76.1 |
| door +x-y (y wall) 0 | 2.30 | 2577 | 2577 | 4.9 | 1956.9 | 34.4 | 47.1 | 20.8-30.8 |
| door +x-y (y wall) 1 | 2.30 | 2145 | 2137 | 4.9 | 1642.9 | 34.2 | 44.5 | 11.5-21.5 |
| door +x-y (y wall) 2 | 2.30 | 1593 | 1594 | 4.9 | 1231.2 | 33.9 | 44.5 | 11.4-21.3 |
| door +x-y (y wall) 3 | 2.30 | 1049 | 1045 | 4.9 | 823.3 | 33.4 | 44.5 | 21.9-31.8 |
| door +x-y (y wall) 4 | 2.30 | 515 | 513 | 5.1 | 425.2 | 32.0 | 44.5 | 13.6-23.6 |
| door +x-y (x wall) 0 | 2.30 | 2577 | 2577 | 4.9 | 1949.0 | 34.6 | 47.1 | 16.3-26.2 |
| door +x-y (x wall) 1 | 2.30 | 2129 | 2137 | 4.9 | 1638.9 | 34.0 | 44.5 | 8.6-18.5 |
| door +x-y (x wall) 2 | 2.30 | 1595 | 1594 | 4.9 | 1233.6 | 33.9 | 44.5 | 8.6-18.5 |
| door +x-y (x wall) 3 | 2.30 | 1041 | 1045 | 4.9 | 818.7 | 33.4 | 47.1 | 12.6-22.6 |
| door +x-y (x wall) 4 | 2.30 | 511 | 513 | 5.1 | 420.7 | 32.1 | 44.5 | 16.6-26.6 |
| door +x-y (corner) | 2.30 | 124 | 124 | 6.5 | 86.4 | 40.4 | 47.1 | 46.9-56.8 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (2.30 m; a corner door's: the gap between its wall ends, 2.30 m); agents are removed past the outer wall's outer face (92.71 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 0 | 0.0% | 0.0% |
| -x | avenue | 5.66 | 0 | 0.0% | 0.0% |
| +y | avenue | 5.66 | 0 | 0.0% | 0.0% |
| -y | avenue | 5.66 | 0 | 0.0% | 0.0% |
| door +x+y (y wall) 0 | door | 2.30 | 2577 | 4.1% | 41.1% |
| door +x+y (y wall) 1 | door | 2.30 | 2132 | 3.4% | 34.0% |
| door +x+y (y wall) 2 | door | 2.30 | 1606 | 2.5% | 25.6% |
| door +x+y (y wall) 3 | door | 2.30 | 1046 | 1.6% | 16.7% |
| door +x+y (y wall) 4 | door | 2.30 | 512 | 0.8% | 8.2% |
| door +x+y (x wall) 0 | door | 2.30 | 2577 | 4.1% | 41.1% |
| door +x+y (x wall) 1 | door | 2.30 | 2142 | 3.4% | 34.1% |
| door +x+y (x wall) 2 | door | 2.30 | 1582 | 2.5% | 25.2% |
| door +x+y (x wall) 3 | door | 2.30 | 1044 | 1.6% | 16.6% |
| door +x+y (x wall) 4 | door | 2.30 | 514 | 0.8% | 8.2% |
| door +x+y (corner) | door | 2.30 | 124 | 0.2% | 2.0% |
| door -x+y (y wall) 0 | door | 2.30 | 2577 | 4.1% | 41.1% |
| door -x+y (y wall) 1 | door | 2.30 | 2127 | 3.4% | 33.9% |
| door -x+y (y wall) 2 | door | 2.30 | 1584 | 2.5% | 25.2% |
| door -x+y (y wall) 3 | door | 2.30 | 1045 | 1.6% | 16.7% |
| door -x+y (y wall) 4 | door | 2.30 | 511 | 0.8% | 8.1% |
| door -x+y (x wall) 0 | door | 2.30 | 2577 | 4.1% | 41.1% |
| door -x+y (x wall) 1 | door | 2.30 | 2147 | 3.4% | 34.2% |
| door -x+y (x wall) 2 | door | 2.30 | 1604 | 2.5% | 25.6% |
| door -x+y (x wall) 3 | door | 2.30 | 1045 | 1.6% | 16.7% |
| door -x+y (x wall) 4 | door | 2.30 | 515 | 0.8% | 8.2% |
| door -x+y (corner) | door | 2.30 | 124 | 0.2% | 2.0% |
| door -x-y (y wall) 0 | door | 2.30 | 2577 | 4.1% | 41.1% |
| door -x-y (y wall) 1 | door | 2.30 | 2148 | 3.4% | 34.2% |
| door -x-y (y wall) 2 | door | 2.30 | 1606 | 2.5% | 25.6% |
| door -x-y (y wall) 3 | door | 2.30 | 1044 | 1.6% | 16.6% |
| door -x-y (y wall) 4 | door | 2.30 | 514 | 0.8% | 8.2% |
| door -x-y (x wall) 0 | door | 2.30 | 2577 | 4.1% | 41.1% |
| door -x-y (x wall) 1 | door | 2.30 | 2126 | 3.4% | 33.9% |
| door -x-y (x wall) 2 | door | 2.30 | 1582 | 2.5% | 25.2% |
| door -x-y (x wall) 3 | door | 2.30 | 1046 | 1.6% | 16.7% |
| door -x-y (x wall) 4 | door | 2.30 | 512 | 0.8% | 8.2% |
| door -x-y (corner) | door | 2.30 | 124 | 0.2% | 2.0% |
| door +x-y (y wall) 0 | door | 2.30 | 2577 | 4.1% | 41.1% |
| door +x-y (y wall) 1 | door | 2.30 | 2145 | 3.4% | 34.2% |
| door +x-y (y wall) 2 | door | 2.30 | 1593 | 2.5% | 25.4% |
| door +x-y (y wall) 3 | door | 2.30 | 1049 | 1.7% | 16.7% |
| door +x-y (y wall) 4 | door | 2.30 | 515 | 0.8% | 8.2% |
| door +x-y (x wall) 0 | door | 2.30 | 2577 | 4.1% | 41.1% |
| door +x-y (x wall) 1 | door | 2.30 | 2129 | 3.4% | 33.9% |
| door +x-y (x wall) 2 | door | 2.30 | 1595 | 2.5% | 25.4% |
| door +x-y (x wall) 3 | door | 2.30 | 1041 | 1.6% | 16.6% |
| door +x-y (x wall) 4 | door | 2.30 | 511 | 0.8% | 8.1% |
| door +x-y (corner) | door | 2.30 | 124 | 0.2% | 2.0% |
| **doors (44)** | door | 101.20 | 63424 | 100.0% | |
| **avenues (4)** | avenue | 22.64 | 0 | 0.0% | |

**Unused exit width: 22.6 of 123.8 m (18.3%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 1958.3 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 18.8%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 2577 | 4.1% | 2577 | 4.1% |
| straight +x+y (y wing) 1 | straight | yes | 2132 | 3.4% | 2132 | 3.4% |
| straight +x+y (y wing) 2 | straight | yes | 1606 | 2.5% | 1606 | 2.5% |
| straight +x+y (y wing) 3 | straight | yes | 1046 | 1.6% | 1046 | 1.6% |
| straight +x+y (y wing) 4 | straight | yes | 512 | 0.8% | 512 | 0.8% |
| straight +x+y (x wing) 0 | straight | yes | 2577 | 4.1% | 2577 | 4.1% |
| straight +x+y (x wing) 1 | straight | yes | 2142 | 3.4% | 2142 | 3.4% |
| straight +x+y (x wing) 2 | straight | yes | 1582 | 2.5% | 1582 | 2.5% |
| straight +x+y (x wing) 3 | straight | yes | 1044 | 1.6% | 1044 | 1.6% |
| straight +x+y (x wing) 4 | straight | yes | 514 | 0.8% | 514 | 0.8% |
| corner +x+y | corner | yes | 1017 | 1.6% | 124 | 0.2% |
| straight -x+y (y wing) 0 | straight | yes | 2577 | 4.1% | 2577 | 4.1% |
| straight -x+y (y wing) 1 | straight | yes | 2127 | 3.4% | 2127 | 3.4% |
| straight -x+y (y wing) 2 | straight | yes | 1584 | 2.5% | 1584 | 2.5% |
| straight -x+y (y wing) 3 | straight | yes | 1045 | 1.6% | 1045 | 1.6% |
| straight -x+y (y wing) 4 | straight | yes | 511 | 0.8% | 511 | 0.8% |
| straight -x+y (x wing) 0 | straight | yes | 2577 | 4.1% | 2577 | 4.1% |
| straight -x+y (x wing) 1 | straight | yes | 2147 | 3.4% | 2147 | 3.4% |
| straight -x+y (x wing) 2 | straight | yes | 1604 | 2.5% | 1604 | 2.5% |
| straight -x+y (x wing) 3 | straight | yes | 1045 | 1.6% | 1045 | 1.6% |
| straight -x+y (x wing) 4 | straight | yes | 515 | 0.8% | 515 | 0.8% |
| corner -x+y | corner | yes | 1020 | 1.6% | 124 | 0.2% |
| straight -x-y (y wing) 0 | straight | yes | 2577 | 4.1% | 2577 | 4.1% |
| straight -x-y (y wing) 1 | straight | yes | 2148 | 3.4% | 2148 | 3.4% |
| straight -x-y (y wing) 2 | straight | yes | 1606 | 2.5% | 1606 | 2.5% |
| straight -x-y (y wing) 3 | straight | yes | 1044 | 1.6% | 1044 | 1.6% |
| straight -x-y (y wing) 4 | straight | yes | 514 | 0.8% | 514 | 0.8% |
| straight -x-y (x wing) 0 | straight | yes | 2577 | 4.1% | 2577 | 4.1% |
| straight -x-y (x wing) 1 | straight | yes | 2126 | 3.4% | 2126 | 3.4% |
| straight -x-y (x wing) 2 | straight | yes | 1582 | 2.5% | 1582 | 2.5% |
| straight -x-y (x wing) 3 | straight | yes | 1046 | 1.6% | 1046 | 1.6% |
| straight -x-y (x wing) 4 | straight | yes | 512 | 0.8% | 512 | 0.8% |
| corner -x-y | corner | yes | 1019 | 1.6% | 124 | 0.2% |
| straight +x-y (y wing) 0 | straight | yes | 2577 | 4.1% | 2577 | 4.1% |
| straight +x-y (y wing) 1 | straight | yes | 2145 | 3.4% | 2145 | 3.4% |
| straight +x-y (y wing) 2 | straight | yes | 1593 | 2.5% | 1593 | 2.5% |
| straight +x-y (y wing) 3 | straight | yes | 1049 | 1.7% | 1049 | 1.7% |
| straight +x-y (y wing) 4 | straight | yes | 515 | 0.8% | 515 | 0.8% |
| straight +x-y (x wing) 0 | straight | yes | 2577 | 4.1% | 2577 | 4.1% |
| straight +x-y (x wing) 1 | straight | yes | 2129 | 3.4% | 2129 | 3.4% |
| straight +x-y (x wing) 2 | straight | yes | 1595 | 2.5% | 1595 | 2.5% |
| straight +x-y (x wing) 3 | straight | yes | 1041 | 1.6% | 1041 | 1.6% |
| straight +x-y (x wing) 4 | straight | yes | 511 | 0.8% | 511 | 0.8% |
| corner +x-y | corner | yes | 1020 | 1.6% | 124 | 0.2% |
| **straight (40)** | | | 62928 | | 62928 | 99.2% |
| **corner (4)** | | | 4076 | | 496 | 0.8% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| door +x+y (y wall) 0 | 2577 | 4.9 | 1942.5 | 0.41 | 0.50 | 0.0% |
| door +x+y (y wall) 1 | 2132 | 4.9 | 1643.9 | 0.41 | 0.53 | 0.0% |
| door +x+y (y wall) 2 | 1606 | 4.9 | 1239.0 | 0.41 | 0.53 | 0.0% |
| door +x+y (y wall) 3 | 1046 | 4.9 | 816.3 | 0.40 | 0.56 | 0.0% |
| door +x+y (y wall) 4 | 512 | 4.9 | 417.7 | 0.39 | 0.56 | 0.0% |
| door +x+y (x wall) 0 | 2577 | 4.9 | 1958.3 | 0.41 | 0.56 | 0.0% |
| door +x+y (x wall) 1 | 2142 | 4.9 | 1650.2 | 0.41 | 0.56 | 0.0% |
| door +x+y (x wall) 2 | 1582 | 4.9 | 1236.2 | 0.40 | 0.56 | 0.0% |
| door +x+y (x wall) 3 | 1044 | 4.9 | 821.9 | 0.40 | 0.56 | 0.0% |
| door +x+y (x wall) 4 | 514 | 5.1 | 419.4 | 0.39 | 0.56 | 0.0% |
| door +x+y (corner) | 124 | 6.3 | 86.1 | 0.48 | 0.56 | 0.0% |
| door -x+y (y wall) 0 | 2577 | 4.9 | 1950.6 | 0.41 | 0.56 | 0.0% |
| door -x+y (y wall) 1 | 2127 | 4.9 | 1639.2 | 0.41 | 0.56 | 0.0% |
| door -x+y (y wall) 2 | 1584 | 4.9 | 1238.0 | 0.40 | 0.53 | 0.0% |
| door -x+y (y wall) 3 | 1045 | 4.9 | 817.5 | 0.40 | 0.56 | 0.0% |
| door -x+y (y wall) 4 | 511 | 5.1 | 423.3 | 0.38 | 0.53 | 0.0% |
| door -x+y (x wall) 0 | 2577 | 4.9 | 1957.2 | 0.41 | 0.53 | 0.0% |
| door -x+y (x wall) 1 | 2147 | 4.9 | 1639.2 | 0.41 | 0.53 | 0.0% |
| door -x+y (x wall) 2 | 1604 | 4.9 | 1240.1 | 0.41 | 0.56 | 0.0% |
| door -x+y (x wall) 3 | 1045 | 4.9 | 813.5 | 0.40 | 0.53 | 0.0% |
| door -x+y (x wall) 4 | 515 | 4.9 | 422.2 | 0.38 | 0.56 | 0.0% |
| door -x+y (corner) | 124 | 6.3 | 86.2 | 0.48 | 0.56 | 0.0% |
| door -x-y (y wall) 0 | 2577 | 4.9 | 1946.2 | 0.41 | 0.53 | 0.0% |
| door -x-y (y wall) 1 | 2148 | 4.9 | 1639.9 | 0.41 | 0.53 | 0.0% |
| door -x-y (y wall) 2 | 1606 | 4.9 | 1233.3 | 0.41 | 0.53 | 0.0% |
| door -x-y (y wall) 3 | 1044 | 4.9 | 815.6 | 0.40 | 0.53 | 0.0% |
| door -x-y (y wall) 4 | 514 | 4.9 | 418.9 | 0.39 | 0.56 | 0.0% |
| door -x-y (x wall) 0 | 2577 | 4.9 | 1956.0 | 0.41 | 0.56 | 0.0% |
| door -x-y (x wall) 1 | 2126 | 4.9 | 1640.6 | 0.41 | 0.56 | 0.0% |
| door -x-y (x wall) 2 | 1582 | 4.9 | 1234.0 | 0.40 | 0.53 | 0.0% |
| door -x-y (x wall) 3 | 1046 | 4.9 | 818.9 | 0.40 | 0.53 | 0.0% |
| door -x-y (x wall) 4 | 512 | 5.1 | 422.6 | 0.38 | 0.53 | 0.0% |
| door -x-y (corner) | 124 | 6.3 | 88.0 | 0.47 | 0.56 | 0.0% |
| door +x-y (y wall) 0 | 2577 | 4.9 | 1956.9 | 0.41 | 0.56 | 0.0% |
| door +x-y (y wall) 1 | 2145 | 4.9 | 1642.9 | 0.41 | 0.53 | 0.0% |
| door +x-y (y wall) 2 | 1593 | 4.9 | 1231.2 | 0.41 | 0.53 | 0.0% |
| door +x-y (y wall) 3 | 1049 | 4.9 | 823.3 | 0.40 | 0.53 | 0.0% |
| door +x-y (y wall) 4 | 515 | 5.1 | 425.2 | 0.38 | 0.53 | 0.0% |
| door +x-y (x wall) 0 | 2577 | 4.9 | 1949.0 | 0.41 | 0.56 | 0.0% |
| door +x-y (x wall) 1 | 2129 | 4.9 | 1638.9 | 0.41 | 0.53 | 0.0% |
| door +x-y (x wall) 2 | 1595 | 4.9 | 1233.6 | 0.41 | 0.53 | 0.0% |
| door +x-y (x wall) 3 | 1041 | 4.9 | 818.7 | 0.40 | 0.56 | 0.0% |
| door +x-y (x wall) 4 | 511 | 5.1 | 420.7 | 0.38 | 0.53 | 0.0% |
| door +x-y (corner) | 124 | 6.5 | 86.4 | 0.48 | 0.56 | 0.0% |

Mean flow / w J averaged over the doors 0.41, over the avenues nan.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 103.1 | 2577 | 2577 / 0 / 0 | 0.7 | 1939.5 | 1.33 | 1.60 | 93% | 86% | 7% | 4.18 |
| straight +x+y (y wing) 1 | 1.20 | 81.5 | 2022 | 2132 / 0 / 0 | 0.7 | 1641.0 | 1.30 | 1.60 | 88% | 81% | 7% | 4.21 |
| straight +x+y (y wing) 2 | 1.20 | 61.0 | 1487 | 1606 / 0 / 0 | 0.7 | 1236.1 | 1.30 | 1.60 | 89% | 84% | 5% | 4.22 |
| straight +x+y (y wing) 3 | 1.20 | 39.4 | 931 | 1046 / 0 / 0 | 0.7 | 813.3 | 1.29 | 1.60 | 84% | 79% | 5% | 4.16 |
| straight +x+y (y wing) 4 | 1.20 | 18.8 | 404 | 512 / 0 / 0 | 0.7 | 414.7 | 1.24 | 1.60 | 71% | 69% | 2% | 3.94 |
| straight +x+y (x wing) 0 | 1.20 | 103.1 | 2577 | 2577 / 0 / 0 | 0.7 | 1955.3 | 1.32 | 1.60 | 93% | 85% | 8% | 3.86 |
| straight +x+y (x wing) 1 | 1.20 | 81.5 | 2022 | 2142 / 0 / 7 | 0.7 | 1647.3 | 1.30 | 2.01 | 88% | 80% | 8% | 3.92 |
| straight +x+y (x wing) 2 | 1.20 | 61.0 | 1485 | 1582 / 0 / 0 | 0.7 | 1233.3 | 1.28 | 1.60 | 87% | 80% | 7% | 3.93 |
| straight +x+y (x wing) 3 | 1.20 | 39.4 | 930 | 1044 / 0 / 0 | 0.7 | 818.9 | 1.28 | 1.60 | 82% | 76% | 6% | 3.91 |
| straight +x+y (x wing) 4 | 1.20 | 18.8 | 404 | 514 / 0 / 0 | 0.7 | 416.5 | 1.24 | 1.71 | 74% | 69% | 5% | 3.88 |
| corner +x+y | 1.20 | 186.0 | 1017 | 124 / 0 / 900 | 0.7 | 1543.4 | 0.66 | 2.51 | 97% | 21% | 77% | 1.45 |
| straight -x+y (y wing) 0 | 1.20 | 103.1 | 2577 | 2577 / 0 / 0 | 0.7 | 1947.6 | 1.32 | 1.60 | 93% | 86% | 7% | 3.97 |
| straight -x+y (y wing) 1 | 1.20 | 81.5 | 2022 | 2127 / 0 / 0 | 0.7 | 1636.3 | 1.30 | 1.60 | 88% | 81% | 7% | 4.02 |
| straight -x+y (y wing) 2 | 1.20 | 61.0 | 1485 | 1584 / 0 / 0 | 0.7 | 1235.0 | 1.28 | 1.71 | 86% | 79% | 7% | 3.88 |
| straight -x+y (y wing) 3 | 1.20 | 39.4 | 930 | 1045 / 0 / 0 | 0.7 | 814.5 | 1.28 | 1.71 | 85% | 78% | 7% | 4.05 |
| straight -x+y (y wing) 4 | 1.20 | 18.8 | 404 | 511 / 0 / 0 | 0.7 | 420.3 | 1.22 | 1.60 | 72% | 67% | 5% | 3.95 |
| straight -x+y (x wing) 0 | 1.20 | 103.1 | 2577 | 2577 / 0 / 0 | 0.7 | 1954.2 | 1.32 | 1.60 | 93% | 85% | 8% | 4.17 |
| straight -x+y (x wing) 1 | 1.20 | 81.5 | 2022 | 2147 / 0 / 1 | 0.7 | 1636.3 | 1.31 | 1.60 | 90% | 82% | 8% | 4.31 |
| straight -x+y (x wing) 2 | 1.20 | 61.0 | 1485 | 1604 / 0 / 0 | 0.7 | 1237.1 | 1.30 | 1.50 | 86% | 81% | 6% | 4.27 |
| straight -x+y (x wing) 3 | 1.20 | 39.4 | 930 | 1045 / 0 / 0 | 0.7 | 810.5 | 1.29 | 1.60 | 85% | 80% | 5% | 4.28 |
| straight -x+y (x wing) 4 | 1.20 | 18.8 | 404 | 515 / 0 / 0 | 0.7 | 419.3 | 1.23 | 1.60 | 70% | 65% | 5% | 3.93 |
| corner -x+y | 1.20 | 186.0 | 1020 | 124 / 0 / 897 | 0.7 | 1532.4 | 0.67 | 2.41 | 97% | 21% | 75% | 1.47 |
| straight -x-y (y wing) 0 | 1.20 | 103.1 | 2577 | 2577 / 0 / 0 | 0.7 | 1943.2 | 1.33 | 1.60 | 93% | 85% | 8% | 4.26 |
| straight -x-y (y wing) 1 | 1.20 | 81.5 | 2022 | 2148 / 0 / 0 | 0.7 | 1637.0 | 1.31 | 1.60 | 91% | 84% | 7% | 4.33 |
| straight -x-y (y wing) 2 | 1.20 | 61.0 | 1486 | 1606 / 0 / 0 | 0.7 | 1230.3 | 1.31 | 1.60 | 87% | 81% | 6% | 4.18 |
| straight -x-y (y wing) 3 | 1.20 | 39.4 | 930 | 1044 / 0 / 0 | 0.7 | 812.6 | 1.29 | 1.60 | 84% | 80% | 4% | 4.29 |
| straight -x-y (y wing) 4 | 1.20 | 18.8 | 404 | 514 / 0 / 0 | 0.7 | 415.9 | 1.24 | 1.71 | 71% | 67% | 5% | 3.98 |
| straight -x-y (x wing) 0 | 1.20 | 103.1 | 2577 | 2577 / 0 / 0 | 0.7 | 1953.0 | 1.32 | 1.60 | 93% | 86% | 7% | 3.89 |
| straight -x-y (x wing) 1 | 1.20 | 81.5 | 2022 | 2126 / 0 / 0 | 0.7 | 1637.7 | 1.30 | 1.71 | 89% | 82% | 7% | 3.92 |
| straight -x-y (x wing) 2 | 1.20 | 61.0 | 1485 | 1582 / 0 / 0 | 0.7 | 1231.0 | 1.29 | 1.71 | 87% | 81% | 6% | 4.00 |
| straight -x-y (x wing) 3 | 1.20 | 39.4 | 930 | 1046 / 0 / 0 | 0.7 | 815.9 | 1.28 | 1.71 | 84% | 78% | 6% | 4.11 |
| straight -x-y (x wing) 4 | 1.20 | 18.8 | 404 | 512 / 0 / 0 | 0.7 | 419.6 | 1.22 | 1.60 | 72% | 65% | 7% | 3.87 |
| corner -x-y | 1.20 | 186.0 | 1019 | 124 / 0 / 895 | 0.7 | 1533.9 | 0.66 | 2.41 | 97% | 22% | 75% | 1.44 |
| straight +x-y (y wing) 0 | 1.20 | 103.1 | 2577 | 2577 / 0 / 0 | 0.7 | 1953.9 | 1.32 | 1.71 | 93% | 85% | 8% | 3.89 |
| straight +x-y (y wing) 1 | 1.20 | 81.5 | 2022 | 2145 / 0 / 0 | 0.7 | 1639.9 | 1.31 | 1.71 | 88% | 82% | 7% | 3.96 |
| straight +x-y (y wing) 2 | 1.20 | 61.0 | 1485 | 1593 / 0 / 0 | 0.7 | 1228.2 | 1.30 | 1.71 | 87% | 80% | 7% | 3.96 |
| straight +x-y (y wing) 3 | 1.20 | 39.4 | 930 | 1049 / 0 / 0 | 0.7 | 820.3 | 1.28 | 1.60 | 83% | 76% | 7% | 4.04 |
| straight +x-y (y wing) 4 | 1.20 | 18.8 | 404 | 515 / 0 / 0 | 0.7 | 422.2 | 1.22 | 1.60 | 72% | 65% | 7% | 3.98 |
| straight +x-y (x wing) 0 | 1.20 | 103.1 | 2577 | 2577 / 0 / 0 | 0.7 | 1946.0 | 1.32 | 1.60 | 93% | 85% | 8% | 3.86 |
| straight +x-y (x wing) 1 | 1.20 | 81.5 | 2022 | 2129 / 0 / 1 | 0.7 | 1635.9 | 1.30 | 1.60 | 88% | 81% | 7% | 3.92 |
| straight +x-y (x wing) 2 | 1.20 | 61.0 | 1485 | 1595 / 0 / 0 | 0.7 | 1230.6 | 1.30 | 1.60 | 86% | 79% | 7% | 3.90 |
| straight +x-y (x wing) 3 | 1.20 | 39.4 | 930 | 1041 / 0 / 0 | 0.7 | 815.8 | 1.28 | 1.60 | 82% | 76% | 6% | 3.88 |
| straight +x-y (x wing) 4 | 1.20 | 18.8 | 404 | 511 / 0 / 0 | 0.7 | 417.7 | 1.22 | 1.60 | 74% | 69% | 5% | 3.83 |
| corner +x-y | 1.20 | 186.0 | 1020 | 124 / 0 / 897 | 0.7 | 1536.0 | 0.66 | 3.11 | 97% | 21% | 77% | 1.42 |

The last agent out (agent 7959, t100 1958.3 s): last gangway straight +x+y (x wing) 0, exit -. The gangway that cleared last: straight +x+y (x wing) 0 at 1955.3 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 8804 | 7800.4 | 6.84 | 1954.6 / 1823.1 / 1790.5 | 1832.8 / 1821.7 / 1761.7 | 10449674.4 | 15392003 | 0.121 |
| gangway | 3792 | 3512.9 | 6.84 | 1953.4 / 1823.1 / 1790.5 | 1832.8 / 1821.7 / 1761.7 | 10449674.4 | 15157047 | 0.106 |
| walkway | 276 | 257.4 | 0.09 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 98 | 0.005 |
| avenue | 1920 | 1801.4 | 0.17 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 28 | 0.142 |
| exit | 4 | 2.0 | 0.00 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 0 | - |
| concourse | 2812 | 2226.8 | 2.60 | 1949.5 / 21.7 / 0.0 | 1362.9 / 3.5 / 0.0 | 0.0 | 234830 | 1.039 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 25392 | 16030.4 | 7.91 | 1825.7 / 1821.1 / 1800.1 | 1825.7 / 1821.0 / 1791.2 | 12954096.3 | 30260361 | 0.013 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 208 x 208 from (-104, -104) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -17.5 | 11.5 | gangway | 0.89 | 6.42 | 1820.6 | 1811.3 | 1761.7 | 9793.8 | 0.006 |
| 2 | -11.5 | -18.5 | gangway | 0.86 | 6.75 | 1807.8 | 1788.8 | 1747.5 | 9750.5 | 0.007 |
| 3 | -10.5 | -18.5 | gangway | 0.94 | 6.19 | 1820.3 | 1802.6 | 1717.4 | 9666.3 | 0.009 |
| 4 | -18.5 | 11.5 | gangway | 0.86 | 6.73 | 1820.4 | 1786.7 | 1746.4 | 9645.1 | 0.007 |
| 5 | -18.5 | 10.5 | gangway | 0.94 | 6.21 | 1828.5 | 1807.5 | 1729.8 | 9594.6 | 0.008 |
| 6 | -10.5 | 15.5 | gangway | 0.96 | 5.85 | 1817.8 | 1813.4 | 1721.4 | 9585.5 | 0.004 |
| 7 | -11.5 | -17.5 | gangway | 0.89 | 6.44 | 1805.6 | 1801.7 | 1745.9 | 9567.8 | 0.006 |
| 8 | -18.5 | -10.5 | gangway | 0.94 | 6.07 | 1826.9 | 1788.9 | 1729.1 | 9540.7 | 0.010 |
| 9 | 11.5 | 18.5 | gangway | 0.86 | 6.74 | 1798.7 | 1766.2 | 1712.0 | 9537.3 | 0.007 |
| 10 | 11.5 | 17.5 | gangway | 0.89 | 6.37 | 1796.6 | 1789.6 | 1738.7 | 9528.6 | 0.006 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -9.5 | -18.5 | seat row | 0.50 | 7.61 | 1799.4 | 1798.0 | 1783.5 | 6613.2 | 0.004 |
| 2 | -18.5 | 9.5 | seat row | 0.50 | 7.51 | 1804.9 | 1802.1 | 1791.2 | 6573.6 | 0.003 |
| 3 | 9.5 | 18.5 | seat row | 0.50 | 7.45 | 1774.8 | 1772.3 | 1759.9 | 6395.9 | 0.003 |
| 4 | 18.5 | 8.5 | seat row | 0.50 | 7.26 | 1766.2 | 1763.8 | 1753.4 | 6291.1 | 0.002 |
| 5 | 18.5 | -8.5 | seat row | 0.50 | 7.27 | 1765.0 | 1762.4 | 1753.1 | 6261.7 | 0.003 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 0; agent-steps of seated agents on another row's clearway: 0.

## Deposit check

Person-seconds deposited: 45658463.8, of them in excluded cells: 6099.176.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 7030493 overlapping pair-steps: p99 0.0019, max 0.1091 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0019 max 0.1091; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00749 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 0 (longest 0 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.748625 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.50 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 0 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
