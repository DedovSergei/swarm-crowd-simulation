# Experiment `L_load100_nearest_level`

**Task 5.9 stage 4 (model variants): venue L, 100% load, nearest exit, level walking speed**

Venue L (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (4000 x 4000), cache key a2f3aaf59c2252b7, content hash 022d17b202313d70). 63424 agents on 100% of the 63424 seats (spawnSeatedCrowd, seed 1337), buffer N = 65536, 6094 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **nearest exit, level speed**.
Capacity: **within design capacity** (the L venue's design capacity 63424, jam capacity 171923: 23822.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-21T17:33:59, 933.1 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1988 | 347.7 |
| t90 | 4573 | 799.8 |
| t100 | 6094 | 1065.9 |

t_p: the step by which ceil(p x 63424) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| -x | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| +y | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| -y | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| door +x+y (y wall) 0 | 2.30 | 2577 | 2577 | 4.2 | 1049.4 | 64.3 | 78.5 | 732.2-742.1 |
| door +x+y (y wall) 1 | 2.30 | 2132 | 2137 | 4.2 | 891.8 | 62.6 | 81.1 | 776.9-786.9 |
| door +x+y (y wall) 2 | 2.30 | 1599 | 1594 | 4.2 | 675.1 | 62.2 | 78.5 | 214.1-224.1 |
| door +x+y (y wall) 3 | 2.30 | 1038 | 1045 | 4.2 | 447.6 | 61.0 | 73.3 | 55.8-65.8 |
| door +x+y (y wall) 4 | 2.30 | 516 | 513 | 4.2 | 236.3 | 58.0 | 73.3 | 12.4-22.4 |
| door +x+y (x wall) 0 | 2.30 | 2577 | 2577 | 4.2 | 1042.4 | 64.7 | 78.5 | 717.6-727.6 |
| door +x+y (x wall) 1 | 2.30 | 2142 | 2137 | 4.2 | 891.3 | 63.0 | 75.9 | 16.1-26.1 |
| door +x+y (x wall) 2 | 2.30 | 1589 | 1594 | 4.2 | 674.8 | 61.8 | 78.5 | 15.9-25.9 |
| door +x+y (x wall) 3 | 2.30 | 1052 | 1045 | 4.2 | 447.4 | 61.9 | 75.9 | 161.6-171.6 |
| door +x+y (x wall) 4 | 2.30 | 510 | 513 | 4.4 | 236.1 | 57.4 | 75.9 | 9.6-19.6 |
| door +x+y (corner) | 2.30 | 124 | 124 | 5.6 | 57.7 | 61.9 | 65.4 | 15.2-25.2 |
| door -x+y (y wall) 0 | 2.30 | 2577 | 2577 | 4.2 | 1056.6 | 63.9 | 78.5 | 914.1-924.0 |
| door -x+y (y wall) 1 | 2.30 | 2135 | 2137 | 4.2 | 900.4 | 62.1 | 75.9 | 386.9-396.9 |
| door -x+y (y wall) 2 | 2.30 | 1597 | 1594 | 4.2 | 668.5 | 62.7 | 78.5 | 321.5-331.4 |
| door -x+y (y wall) 3 | 2.30 | 1047 | 1045 | 4.2 | 451.6 | 61.0 | 78.5 | 265.5-275.5 |
| door -x+y (y wall) 4 | 2.30 | 507 | 513 | 4.4 | 234.0 | 57.5 | 78.5 | 134.9-144.8 |
| door -x+y (x wall) 0 | 2.30 | 2577 | 2577 | 4.2 | 1052.8 | 64.1 | 75.9 | 315.9-325.9 |
| door -x+y (x wall) 1 | 2.30 | 2139 | 2137 | 4.2 | 900.9 | 62.2 | 75.9 | 159.9-169.8 |
| door -x+y (x wall) 2 | 2.30 | 1591 | 1594 | 4.2 | 667.8 | 62.5 | 78.5 | 531.2-541.2 |
| door -x+y (x wall) 3 | 2.30 | 1043 | 1045 | 4.2 | 451.6 | 60.8 | 75.9 | 193.8-203.8 |
| door -x+y (x wall) 4 | 2.30 | 519 | 513 | 4.2 | 234.2 | 58.8 | 75.9 | 13.1-23.1 |
| door -x+y (corner) | 2.30 | 124 | 124 | 5.6 | 59.6 | 59.7 | 65.4 | 15.2-25.2 |
| door -x-y (y wall) 0 | 2.30 | 2577 | 2577 | 4.2 | 1053.6 | 64.0 | 78.5 | 765.9-775.9 |
| door -x-y (y wall) 1 | 2.30 | 2141 | 2137 | 4.2 | 879.6 | 63.8 | 75.9 | 150.6-160.6 |
| door -x-y (y wall) 2 | 2.30 | 1594 | 1594 | 4.2 | 672.3 | 62.2 | 75.9 | 187.8-197.8 |
| door -x-y (y wall) 3 | 2.30 | 1041 | 1045 | 4.2 | 445.8 | 61.5 | 75.9 | 14.2-24.1 |
| door -x-y (y wall) 4 | 2.30 | 516 | 513 | 4.2 | 234.7 | 58.3 | 75.9 | 127.3-137.3 |
| door -x-y (x wall) 0 | 2.30 | 2577 | 2577 | 4.2 | 1062.7 | 63.5 | 75.9 | 330.7-340.7 |
| door -x-y (x wall) 1 | 2.30 | 2133 | 2137 | 4.2 | 879.1 | 63.6 | 78.5 | 460.4-470.3 |
| door -x-y (x wall) 2 | 2.30 | 1594 | 1594 | 4.2 | 672.3 | 62.2 | 75.9 | 608.9-618.8 |
| door -x-y (x wall) 3 | 2.30 | 1049 | 1045 | 4.2 | 447.1 | 61.8 | 78.5 | 145.2-155.1 |
| door -x-y (x wall) 4 | 2.30 | 510 | 513 | 4.4 | 234.4 | 57.8 | 73.3 | 70.0-79.9 |
| door -x-y (corner) | 2.30 | 124 | 124 | 5.6 | 57.7 | 61.9 | 68.0 | 29.2-39.2 |
| door +x-y (y wall) 0 | 2.30 | 2577 | 2577 | 4.2 | 1065.9 | 63.3 | 81.1 | 998.0-1008.0 |
| door +x-y (y wall) 1 | 2.30 | 2135 | 2137 | 4.2 | 879.4 | 63.6 | 78.5 | 436.2-446.2 |
| door +x-y (y wall) 2 | 2.30 | 1595 | 1594 | 4.2 | 666.4 | 62.8 | 75.9 | 540.8-550.8 |
| door +x-y (y wall) 3 | 2.30 | 1047 | 1045 | 4.2 | 449.0 | 61.4 | 75.9 | 75.0-85.0 |
| door +x-y (y wall) 4 | 2.30 | 512 | 513 | 4.4 | 229.7 | 59.2 | 73.3 | 53.3-63.3 |
| door +x-y (x wall) 0 | 2.30 | 2577 | 2577 | 4.2 | 1054.3 | 64.0 | 78.5 | 695.8-705.7 |
| door +x-y (x wall) 1 | 2.30 | 2139 | 2137 | 4.2 | 879.8 | 63.7 | 75.9 | 220.9-230.9 |
| door +x-y (x wall) 2 | 2.30 | 1593 | 1594 | 4.2 | 665.9 | 62.8 | 81.1 | 79.2-89.2 |
| door +x-y (x wall) 3 | 2.30 | 1043 | 1045 | 4.2 | 448.1 | 61.3 | 75.9 | 55.1-65.1 |
| door +x-y (x wall) 4 | 2.30 | 514 | 513 | 4.4 | 230.0 | 59.4 | 78.5 | 159.0-169.0 |
| door +x-y (corner) | 2.30 | 124 | 124 | 5.6 | 58.1 | 61.4 | 68.0 | 20.5-30.4 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (2.30 m; a corner door's: the gap between its wall ends, 2.30 m); agents are removed past the outer wall's outer face (92.71 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 0 | 0.0% | 0.0% |
| -x | avenue | 5.66 | 0 | 0.0% | 0.0% |
| +y | avenue | 5.66 | 0 | 0.0% | 0.0% |
| -y | avenue | 5.66 | 0 | 0.0% | 0.0% |
| door +x+y (y wall) 0 | door | 2.30 | 2577 | 4.1% | 75.4% |
| door +x+y (y wall) 1 | door | 2.30 | 2132 | 3.4% | 62.4% |
| door +x+y (y wall) 2 | door | 2.30 | 1599 | 2.5% | 46.8% |
| door +x+y (y wall) 3 | door | 2.30 | 1038 | 1.6% | 30.4% |
| door +x+y (y wall) 4 | door | 2.30 | 516 | 0.8% | 15.1% |
| door +x+y (x wall) 0 | door | 2.30 | 2577 | 4.1% | 75.4% |
| door +x+y (x wall) 1 | door | 2.30 | 2142 | 3.4% | 62.7% |
| door +x+y (x wall) 2 | door | 2.30 | 1589 | 2.5% | 46.5% |
| door +x+y (x wall) 3 | door | 2.30 | 1052 | 1.7% | 30.8% |
| door +x+y (x wall) 4 | door | 2.30 | 510 | 0.8% | 14.9% |
| door +x+y (corner) | door | 2.30 | 124 | 0.2% | 3.6% |
| door -x+y (y wall) 0 | door | 2.30 | 2577 | 4.1% | 75.4% |
| door -x+y (y wall) 1 | door | 2.30 | 2135 | 3.4% | 62.5% |
| door -x+y (y wall) 2 | door | 2.30 | 1597 | 2.5% | 46.8% |
| door -x+y (y wall) 3 | door | 2.30 | 1047 | 1.7% | 30.7% |
| door -x+y (y wall) 4 | door | 2.30 | 507 | 0.8% | 14.8% |
| door -x+y (x wall) 0 | door | 2.30 | 2577 | 4.1% | 75.4% |
| door -x+y (x wall) 1 | door | 2.30 | 2139 | 3.4% | 62.6% |
| door -x+y (x wall) 2 | door | 2.30 | 1591 | 2.5% | 46.6% |
| door -x+y (x wall) 3 | door | 2.30 | 1043 | 1.6% | 30.5% |
| door -x+y (x wall) 4 | door | 2.30 | 519 | 0.8% | 15.2% |
| door -x+y (corner) | door | 2.30 | 124 | 0.2% | 3.6% |
| door -x-y (y wall) 0 | door | 2.30 | 2577 | 4.1% | 75.4% |
| door -x-y (y wall) 1 | door | 2.30 | 2141 | 3.4% | 62.7% |
| door -x-y (y wall) 2 | door | 2.30 | 1594 | 2.5% | 46.7% |
| door -x-y (y wall) 3 | door | 2.30 | 1041 | 1.6% | 30.5% |
| door -x-y (y wall) 4 | door | 2.30 | 516 | 0.8% | 15.1% |
| door -x-y (x wall) 0 | door | 2.30 | 2577 | 4.1% | 75.4% |
| door -x-y (x wall) 1 | door | 2.30 | 2133 | 3.4% | 62.4% |
| door -x-y (x wall) 2 | door | 2.30 | 1594 | 2.5% | 46.7% |
| door -x-y (x wall) 3 | door | 2.30 | 1049 | 1.7% | 30.7% |
| door -x-y (x wall) 4 | door | 2.30 | 510 | 0.8% | 14.9% |
| door -x-y (corner) | door | 2.30 | 124 | 0.2% | 3.6% |
| door +x-y (y wall) 0 | door | 2.30 | 2577 | 4.1% | 75.4% |
| door +x-y (y wall) 1 | door | 2.30 | 2135 | 3.4% | 62.5% |
| door +x-y (y wall) 2 | door | 2.30 | 1595 | 2.5% | 46.7% |
| door +x-y (y wall) 3 | door | 2.30 | 1047 | 1.7% | 30.7% |
| door +x-y (y wall) 4 | door | 2.30 | 512 | 0.8% | 15.0% |
| door +x-y (x wall) 0 | door | 2.30 | 2577 | 4.1% | 75.4% |
| door +x-y (x wall) 1 | door | 2.30 | 2139 | 3.4% | 62.6% |
| door +x-y (x wall) 2 | door | 2.30 | 1593 | 2.5% | 46.6% |
| door +x-y (x wall) 3 | door | 2.30 | 1043 | 1.6% | 30.5% |
| door +x-y (x wall) 4 | door | 2.30 | 514 | 0.8% | 15.0% |
| door +x-y (corner) | door | 2.30 | 124 | 0.2% | 3.6% |
| **doors (44)** | door | 101.20 | 63424 | 100.0% | |
| **avenues (4)** | avenue | 22.64 | 0 | 0.0% | |

**Unused exit width: 22.6 of 123.8 m (18.3%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 1065.9 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 34.5%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 2577 | 4.1% | 2577 | 4.1% |
| straight +x+y (y wing) 1 | straight | yes | 2132 | 3.4% | 2132 | 3.4% |
| straight +x+y (y wing) 2 | straight | yes | 1599 | 2.5% | 1599 | 2.5% |
| straight +x+y (y wing) 3 | straight | yes | 1038 | 1.6% | 1038 | 1.6% |
| straight +x+y (y wing) 4 | straight | yes | 516 | 0.8% | 516 | 0.8% |
| straight +x+y (x wing) 0 | straight | yes | 2577 | 4.1% | 2577 | 4.1% |
| straight +x+y (x wing) 1 | straight | yes | 2142 | 3.4% | 2142 | 3.4% |
| straight +x+y (x wing) 2 | straight | yes | 1589 | 2.5% | 1589 | 2.5% |
| straight +x+y (x wing) 3 | straight | yes | 1052 | 1.7% | 1052 | 1.7% |
| straight +x+y (x wing) 4 | straight | yes | 510 | 0.8% | 510 | 0.8% |
| corner +x+y | corner | yes | 1018 | 1.6% | 124 | 0.2% |
| straight -x+y (y wing) 0 | straight | yes | 2577 | 4.1% | 2577 | 4.1% |
| straight -x+y (y wing) 1 | straight | yes | 2135 | 3.4% | 2135 | 3.4% |
| straight -x+y (y wing) 2 | straight | yes | 1597 | 2.5% | 1597 | 2.5% |
| straight -x+y (y wing) 3 | straight | yes | 1047 | 1.7% | 1047 | 1.7% |
| straight -x+y (y wing) 4 | straight | yes | 507 | 0.8% | 507 | 0.8% |
| straight -x+y (x wing) 0 | straight | yes | 2577 | 4.1% | 2577 | 4.1% |
| straight -x+y (x wing) 1 | straight | yes | 2139 | 3.4% | 2139 | 3.4% |
| straight -x+y (x wing) 2 | straight | yes | 1591 | 2.5% | 1591 | 2.5% |
| straight -x+y (x wing) 3 | straight | yes | 1043 | 1.6% | 1043 | 1.6% |
| straight -x+y (x wing) 4 | straight | yes | 519 | 0.8% | 519 | 0.8% |
| corner -x+y | corner | yes | 1020 | 1.6% | 124 | 0.2% |
| straight -x-y (y wing) 0 | straight | yes | 2577 | 4.1% | 2577 | 4.1% |
| straight -x-y (y wing) 1 | straight | yes | 2141 | 3.4% | 2141 | 3.4% |
| straight -x-y (y wing) 2 | straight | yes | 1594 | 2.5% | 1594 | 2.5% |
| straight -x-y (y wing) 3 | straight | yes | 1041 | 1.6% | 1041 | 1.6% |
| straight -x-y (y wing) 4 | straight | yes | 516 | 0.8% | 516 | 0.8% |
| straight -x-y (x wing) 0 | straight | yes | 2577 | 4.1% | 2577 | 4.1% |
| straight -x-y (x wing) 1 | straight | yes | 2133 | 3.4% | 2133 | 3.4% |
| straight -x-y (x wing) 2 | straight | yes | 1594 | 2.5% | 1594 | 2.5% |
| straight -x-y (x wing) 3 | straight | yes | 1049 | 1.7% | 1049 | 1.7% |
| straight -x-y (x wing) 4 | straight | yes | 510 | 0.8% | 510 | 0.8% |
| corner -x-y | corner | yes | 1020 | 1.6% | 124 | 0.2% |
| straight +x-y (y wing) 0 | straight | yes | 2577 | 4.1% | 2577 | 4.1% |
| straight +x-y (y wing) 1 | straight | yes | 2135 | 3.4% | 2135 | 3.4% |
| straight +x-y (y wing) 2 | straight | yes | 1595 | 2.5% | 1595 | 2.5% |
| straight +x-y (y wing) 3 | straight | yes | 1047 | 1.7% | 1047 | 1.7% |
| straight +x-y (y wing) 4 | straight | yes | 512 | 0.8% | 512 | 0.8% |
| straight +x-y (x wing) 0 | straight | yes | 2577 | 4.1% | 2577 | 4.1% |
| straight +x-y (x wing) 1 | straight | yes | 2139 | 3.4% | 2139 | 3.4% |
| straight +x-y (x wing) 2 | straight | yes | 1593 | 2.5% | 1593 | 2.5% |
| straight +x-y (x wing) 3 | straight | yes | 1043 | 1.6% | 1043 | 1.6% |
| straight +x-y (x wing) 4 | straight | yes | 514 | 0.8% | 514 | 0.8% |
| corner +x-y | corner | yes | 1020 | 1.6% | 124 | 0.2% |
| **straight (40)** | | | 62928 | | 62928 | 99.2% |
| **corner (4)** | | | 4078 | | 496 | 0.8% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| door +x+y (y wall) 0 | 2577 | 4.2 | 1049.4 | 0.77 | 0.94 | 25.5% |
| door +x+y (y wall) 1 | 2132 | 4.2 | 891.8 | 0.75 | 0.97 | 25.6% |
| door +x+y (y wall) 2 | 1599 | 4.2 | 675.1 | 0.74 | 0.94 | 26.5% |
| door +x+y (y wall) 3 | 1038 | 4.2 | 447.6 | 0.73 | 0.88 | 24.4% |
| door +x+y (y wall) 4 | 516 | 4.2 | 236.3 | 0.69 | 0.88 | 20.8% |
| door +x+y (x wall) 0 | 2577 | 4.2 | 1042.4 | 0.77 | 0.94 | 24.8% |
| door +x+y (x wall) 1 | 2142 | 4.2 | 891.3 | 0.75 | 0.91 | 23.3% |
| door +x+y (x wall) 2 | 1589 | 4.2 | 674.8 | 0.74 | 0.94 | 23.5% |
| door +x+y (x wall) 3 | 1052 | 4.2 | 447.4 | 0.74 | 0.91 | 24.4% |
| door +x+y (x wall) 4 | 510 | 4.4 | 236.1 | 0.69 | 0.91 | 16.7% |
| door +x+y (corner) | 124 | 5.6 | 57.7 | 0.74 | 0.78 | 0.0% |
| door -x+y (y wall) 0 | 2577 | 4.2 | 1056.6 | 0.76 | 0.94 | 28.3% |
| door -x+y (y wall) 1 | 2135 | 4.2 | 900.4 | 0.74 | 0.91 | 17.6% |
| door -x+y (y wall) 2 | 1597 | 4.2 | 668.5 | 0.75 | 0.94 | 25.0% |
| door -x+y (y wall) 3 | 1047 | 4.2 | 451.6 | 0.73 | 0.94 | 17.4% |
| door -x+y (y wall) 4 | 507 | 4.4 | 234.0 | 0.69 | 0.94 | 25.0% |
| door -x+y (x wall) 0 | 2577 | 4.2 | 1052.8 | 0.77 | 0.91 | 23.6% |
| door -x+y (x wall) 1 | 2139 | 4.2 | 900.9 | 0.74 | 0.91 | 15.4% |
| door -x+y (x wall) 2 | 1591 | 4.2 | 667.8 | 0.75 | 0.94 | 23.9% |
| door -x+y (x wall) 3 | 1043 | 4.2 | 451.6 | 0.73 | 0.91 | 32.6% |
| door -x+y (x wall) 4 | 519 | 4.2 | 234.2 | 0.70 | 0.91 | 25.0% |
| door -x+y (corner) | 124 | 5.6 | 59.6 | 0.71 | 0.78 | 0.0% |
| door -x-y (y wall) 0 | 2577 | 4.2 | 1053.6 | 0.77 | 0.94 | 23.6% |
| door -x-y (y wall) 1 | 2141 | 4.2 | 879.6 | 0.76 | 0.91 | 32.6% |
| door -x-y (y wall) 2 | 1594 | 4.2 | 672.3 | 0.74 | 0.91 | 22.1% |
| door -x-y (y wall) 3 | 1041 | 4.2 | 445.8 | 0.74 | 0.91 | 24.4% |
| door -x-y (y wall) 4 | 516 | 4.2 | 234.7 | 0.70 | 0.91 | 25.0% |
| door -x-y (x wall) 0 | 2577 | 4.2 | 1062.7 | 0.76 | 0.91 | 21.5% |
| door -x-y (x wall) 1 | 2133 | 4.2 | 879.1 | 0.76 | 0.94 | 27.0% |
| door -x-y (x wall) 2 | 1594 | 4.2 | 672.3 | 0.74 | 0.91 | 25.0% |
| door -x-y (x wall) 3 | 1049 | 4.2 | 447.1 | 0.74 | 0.94 | 20.0% |
| door -x-y (x wall) 4 | 510 | 4.4 | 234.4 | 0.69 | 0.88 | 20.8% |
| door -x-y (corner) | 124 | 5.6 | 57.7 | 0.74 | 0.81 | 0.0% |
| door +x-y (y wall) 0 | 2577 | 4.2 | 1065.9 | 0.76 | 0.97 | 21.5% |
| door +x-y (y wall) 1 | 2135 | 4.2 | 879.4 | 0.76 | 0.94 | 30.3% |
| door +x-y (y wall) 2 | 1595 | 4.2 | 666.4 | 0.75 | 0.91 | 26.9% |
| door +x-y (y wall) 3 | 1047 | 4.2 | 449.0 | 0.73 | 0.91 | 17.4% |
| door +x-y (y wall) 4 | 512 | 4.4 | 229.7 | 0.71 | 0.88 | 20.8% |
| door +x-y (x wall) 0 | 2577 | 4.2 | 1054.3 | 0.77 | 0.94 | 24.5% |
| door +x-y (x wall) 1 | 2139 | 4.2 | 879.8 | 0.76 | 0.91 | 27.0% |
| door +x-y (x wall) 2 | 1593 | 4.2 | 665.9 | 0.75 | 0.97 | 29.9% |
| door +x-y (x wall) 3 | 1043 | 4.2 | 448.1 | 0.73 | 0.91 | 24.4% |
| door +x-y (x wall) 4 | 514 | 4.4 | 230.0 | 0.71 | 0.94 | 33.3% |
| door +x-y (corner) | 124 | 5.6 | 58.1 | 0.73 | 0.81 | 0.0% |

Mean flow / w J averaged over the doors 0.74, over the avenues nan.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 103.1 | 2577 | 2577 / 0 / 0 | 0.7 | 1046.8 | 2.46 | 2.91 | 94% | 82% | 12% | 3.92 |
| straight +x+y (y wing) 1 | 1.20 | 81.5 | 2022 | 2132 / 0 / 0 | 0.7 | 889.2 | 2.40 | 2.91 | 88% | 74% | 13% | 3.91 |
| straight +x+y (y wing) 2 | 1.20 | 61.0 | 1485 | 1599 / 0 / 1 | 0.7 | 672.5 | 2.38 | 2.71 | 85% | 75% | 10% | 3.96 |
| straight +x+y (y wing) 3 | 1.20 | 39.4 | 930 | 1038 / 0 / 0 | 0.7 | 445.0 | 2.34 | 2.71 | 84% | 71% | 13% | 3.73 |
| straight +x+y (y wing) 4 | 1.20 | 18.8 | 404 | 516 / 0 / 0 | 0.7 | 233.7 | 2.21 | 2.81 | 71% | 62% | 8% | 3.79 |
| straight +x+y (x wing) 0 | 1.20 | 103.1 | 2577 | 2577 / 0 / 0 | 0.7 | 1039.8 | 2.48 | 2.91 | 93% | 82% | 11% | 4.01 |
| straight +x+y (x wing) 1 | 1.20 | 81.5 | 2023 | 2142 / 0 / 0 | 0.7 | 888.7 | 2.41 | 2.91 | 89% | 77% | 12% | 4.03 |
| straight +x+y (x wing) 2 | 1.20 | 61.0 | 1485 | 1589 / 0 / 0 | 0.7 | 672.0 | 2.37 | 2.81 | 88% | 76% | 12% | 3.95 |
| straight +x+y (x wing) 3 | 1.20 | 39.4 | 930 | 1052 / 0 / 0 | 0.7 | 444.8 | 2.37 | 2.81 | 84% | 73% | 11% | 3.83 |
| straight +x+y (x wing) 4 | 1.20 | 18.8 | 405 | 510 / 0 / 0 | 0.7 | 233.5 | 2.19 | 2.71 | 71% | 62% | 8% | 3.66 |
| corner +x+y | 1.20 | 186.0 | 1018 | 124 / 0 / 895 | 0.7 | 844.3 | 1.21 | 6.72 | 98% | 20% | 78% | 1.41 |
| straight -x+y (y wing) 0 | 1.20 | 103.1 | 2577 | 2577 / 0 / 0 | 0.7 | 1054.0 | 2.45 | 2.81 | 94% | 83% | 11% | 4.05 |
| straight -x+y (y wing) 1 | 1.20 | 81.5 | 2022 | 2135 / 0 / 0 | 0.7 | 897.8 | 2.38 | 2.81 | 89% | 77% | 12% | 4.02 |
| straight -x+y (y wing) 2 | 1.20 | 61.0 | 1485 | 1597 / 0 / 2 | 0.7 | 665.9 | 2.40 | 2.81 | 90% | 78% | 12% | 4.01 |
| straight -x+y (y wing) 3 | 1.20 | 39.4 | 930 | 1047 / 0 / 1 | 0.7 | 449.0 | 2.34 | 2.81 | 83% | 70% | 13% | 3.74 |
| straight -x+y (y wing) 4 | 1.20 | 18.8 | 404 | 507 / 0 / 0 | 0.7 | 231.4 | 2.20 | 2.71 | 71% | 62% | 8% | 3.75 |
| straight -x+y (x wing) 0 | 1.20 | 103.1 | 2577 | 2577 / 0 / 0 | 0.7 | 1050.1 | 2.46 | 2.81 | 93% | 82% | 11% | 3.96 |
| straight -x+y (x wing) 1 | 1.20 | 81.5 | 2022 | 2139 / 0 / 1 | 0.7 | 898.3 | 2.38 | 2.81 | 88% | 76% | 12% | 3.96 |
| straight -x+y (x wing) 2 | 1.20 | 61.0 | 1485 | 1591 / 0 / 0 | 0.7 | 665.2 | 2.39 | 2.81 | 88% | 76% | 12% | 3.81 |
| straight -x+y (x wing) 3 | 1.20 | 39.4 | 930 | 1043 / 0 / 0 | 0.7 | 448.8 | 2.33 | 2.81 | 80% | 67% | 13% | 3.76 |
| straight -x+y (x wing) 4 | 1.20 | 18.8 | 404 | 519 / 0 / 0 | 0.7 | 231.6 | 2.25 | 2.71 | 71% | 58% | 12% | 3.78 |
| corner -x+y | 1.20 | 186.0 | 1020 | 124 / 0 / 900 | 0.7 | 853.4 | 1.20 | 6.62 | 97% | 20% | 77% | 1.40 |
| straight -x-y (y wing) 0 | 1.20 | 103.1 | 2577 | 2577 / 0 / 0 | 0.7 | 1051.0 | 2.45 | 2.81 | 93% | 81% | 12% | 3.99 |
| straight -x-y (y wing) 1 | 1.20 | 81.5 | 2022 | 2141 / 0 / 0 | 0.7 | 877.0 | 2.44 | 2.81 | 91% | 80% | 11% | 4.04 |
| straight -x-y (y wing) 2 | 1.20 | 61.0 | 1485 | 1594 / 0 / 0 | 0.7 | 669.7 | 2.38 | 2.71 | 85% | 75% | 10% | 3.97 |
| straight -x-y (y wing) 3 | 1.20 | 39.4 | 930 | 1041 / 0 / 0 | 0.7 | 443.2 | 2.35 | 2.71 | 82% | 71% | 11% | 3.79 |
| straight -x-y (y wing) 4 | 1.20 | 18.8 | 404 | 516 / 0 / 0 | 0.7 | 232.1 | 2.23 | 2.71 | 71% | 58% | 12% | 3.76 |
| straight -x-y (x wing) 0 | 1.20 | 103.1 | 2577 | 2577 / 0 / 0 | 0.7 | 1060.1 | 2.43 | 2.81 | 93% | 81% | 12% | 4.03 |
| straight -x-y (x wing) 1 | 1.20 | 81.5 | 2022 | 2133 / 0 / 0 | 0.7 | 876.5 | 2.44 | 2.91 | 90% | 78% | 11% | 3.98 |
| straight -x-y (x wing) 2 | 1.20 | 61.0 | 1485 | 1594 / 0 / 0 | 0.7 | 669.7 | 2.38 | 2.81 | 87% | 76% | 10% | 4.03 |
| straight -x-y (x wing) 3 | 1.20 | 39.4 | 930 | 1049 / 0 / 1 | 0.7 | 444.4 | 2.37 | 2.91 | 82% | 71% | 11% | 3.74 |
| straight -x-y (x wing) 4 | 1.20 | 18.8 | 404 | 510 / 0 / 0 | 0.7 | 231.8 | 2.21 | 2.71 | 71% | 62% | 8% | 3.73 |
| corner -x-y | 1.20 | 186.0 | 1020 | 124 / 0 / 897 | 0.7 | 832.0 | 1.23 | 6.72 | 96% | 19% | 77% | 1.41 |
| straight +x-y (y wing) 0 | 1.20 | 103.1 | 2577 | 2577 / 0 / 0 | 0.7 | 1063.1 | 2.43 | 2.91 | 94% | 80% | 14% | 4.03 |
| straight +x-y (y wing) 1 | 1.20 | 81.5 | 2022 | 2135 / 0 / 0 | 0.7 | 876.8 | 2.44 | 2.81 | 91% | 78% | 12% | 4.05 |
| straight +x-y (y wing) 2 | 1.20 | 61.0 | 1485 | 1595 / 0 / 0 | 0.7 | 663.8 | 2.40 | 2.91 | 90% | 78% | 12% | 4.04 |
| straight +x-y (y wing) 3 | 1.20 | 39.4 | 930 | 1047 / 0 / 0 | 0.7 | 446.4 | 2.35 | 2.71 | 82% | 71% | 11% | 3.76 |
| straight +x-y (y wing) 4 | 1.20 | 18.8 | 404 | 512 / 0 / 1 | 0.7 | 227.0 | 2.26 | 2.61 | 74% | 65% | 9% | 3.68 |
| straight +x-y (x wing) 0 | 1.20 | 103.1 | 2577 | 2577 / 0 / 0 | 0.7 | 1051.7 | 2.45 | 2.91 | 94% | 81% | 13% | 4.01 |
| straight +x-y (x wing) 1 | 1.20 | 81.5 | 2022 | 2139 / 0 / 0 | 0.7 | 877.2 | 2.44 | 2.81 | 92% | 80% | 12% | 4.07 |
| straight +x-y (x wing) 2 | 1.20 | 61.0 | 1485 | 1593 / 0 / 0 | 0.7 | 663.2 | 2.40 | 2.91 | 90% | 78% | 12% | 3.99 |
| straight +x-y (x wing) 3 | 1.20 | 39.4 | 930 | 1043 / 0 / 0 | 0.7 | 445.5 | 2.34 | 2.91 | 82% | 71% | 11% | 3.86 |
| straight +x-y (x wing) 4 | 1.20 | 18.8 | 404 | 514 / 0 / 0 | 0.7 | 227.4 | 2.27 | 2.91 | 74% | 65% | 9% | 3.75 |
| corner +x-y | 1.20 | 186.0 | 1020 | 124 / 0 / 897 | 0.7 | 832.2 | 1.23 | 6.32 | 98% | 20% | 77% | 1.47 |

The last agent out (agent 47636, t100 1065.9 s): last gangway straight +x-y (y wing) 0, exit -. The gangway that cleared last: straight +x-y (y wing) 0 at 1063.1 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 8804 | 7800.4 | 6.85 | 1061.2 / 1004.3 / 977.2 | 1008.0 / 1002.6 / 970.2 | 5758258.7 | 8288932 | 0.224 |
| gangway | 3792 | 3512.9 | 6.85 | 1055.7 / 1004.3 / 977.2 | 1008.0 / 1002.6 / 970.2 | 5758258.7 | 8099529 | 0.199 |
| walkway | 276 | 257.4 | 0.09 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 19 | 0.015 |
| avenue | 1920 | 1801.4 | 0.17 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 28 | 0.142 |
| exit | 4 | 2.0 | 0.00 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 0 | - |
| concourse | 2812 | 2226.8 | 2.96 | 1059.8 / 720.8 / 0.0 | 773.8 / 129.6 / 0.0 | 0.0 | 189357 | 1.298 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 25392 | 16030.4 | 7.87 | 1006.2 / 1004.3 / 984.7 | 1006.2 / 1004.3 / 981.2 | 6987861.5 | 16493327 | 0.024 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 208 x 208 from (-104, -104) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 16.5 | -10.5 | gangway | 0.96 | 6.00 | 993.8 | 990.7 | 958.5 | 5323.4 | 0.010 |
| 2 | 18.5 | 10.5 | gangway | 0.94 | 6.23 | 985.4 | 972.5 | 929.6 | 5223.4 | 0.015 |
| 3 | 17.5 | 10.5 | gangway | 0.95 | 6.11 | 984.5 | 982.1 | 937.2 | 5213.8 | 0.012 |
| 4 | 18.5 | 11.5 | gangway | 0.86 | 6.76 | 975.3 | 965.0 | 936.3 | 5193.4 | 0.013 |
| 5 | 17.5 | -10.5 | gangway | 0.95 | 6.05 | 995.9 | 991.7 | 950.8 | 5192.4 | 0.012 |
| 6 | 11.5 | -16.5 | gangway | 0.92 | 6.12 | 995.9 | 994.5 | 970.2 | 5186.3 | 0.007 |
| 7 | 18.5 | -10.5 | gangway | 0.94 | 6.21 | 993.6 | 978.6 | 937.2 | 5160.2 | 0.016 |
| 8 | -22.5 | -11.5 | gangway | 0.86 | 6.73 | 973.5 | 945.9 | 913.9 | 5151.2 | 0.023 |
| 9 | -17.5 | -11.5 | gangway | 0.89 | 6.32 | 995.2 | 990.3 | 964.6 | 5148.7 | 0.010 |
| 10 | 11.5 | -17.5 | gangway | 0.89 | 6.43 | 997.8 | 990.0 | 959.7 | 5138.5 | 0.010 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 18.5 | 9.5 | seat row | 0.50 | 7.47 | 972.1 | 970.9 | 961.6 | 3515.9 | 0.006 |
| 2 | 18.5 | -9.5 | seat row | 0.50 | 7.41 | 978.6 | 976.5 | 965.8 | 3468.8 | 0.006 |
| 3 | -9.5 | 18.5 | seat row | 0.50 | 7.51 | 978.6 | 977.0 | 969.2 | 3456.3 | 0.006 |
| 4 | -18.5 | -9.5 | seat row | 0.50 | 7.49 | 989.8 | 988.2 | 979.5 | 3451.0 | 0.007 |
| 5 | 9.5 | -18.5 | seat row | 0.50 | 7.46 | 990.0 | 988.4 | 981.2 | 3448.0 | 0.007 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 0; agent-steps of seated agents on another row's clearway: 0.

## Deposit check

Person-seconds deposited: 24786974.2, of them in excluded cells: 4714.546.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 6322377 overlapping pair-steps: p99 0.0037, max 0.0382 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0037 max 0.0382; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 0 (longest 0 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.41 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 0 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
