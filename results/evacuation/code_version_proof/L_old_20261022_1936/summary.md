# Experiment `L_old`

Venue L (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (4000 x 4000), cache key a2f3aaf59c2252b7, content hash 022d17b202313d70). 63424 agents on 100% of the 63424 seats (spawnSeatedCrowd, seed 1337), buffer N = 65536, 400 steps (max steps reached), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 1411627 evaluations, 120063 switches, 0 forced choices).
Capacity: **within design capacity** (the L venue's design capacity 63424, jam capacity 171923: 23822.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T19:36:17, 303.2 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | - | - |
| t90 | - | - |
| t100 | - | - |

t_p: the step by which ceil(p x 63424) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| -x | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| +y | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| -y | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| door +x+y (y wall) 0 | 2.30 | 95 | 2577 | 4.9 | 69.8 | 38.1 | 47.1 | 27.6-37.6 |
| door +x+y (y wall) 1 | 2.30 | 95 | 2137 | 4.9 | 69.3 | 38.4 | 44.5 | 22.6-32.5 |
| door +x+y (y wall) 2 | 2.30 | 91 | 1594 | 4.9 | 69.4 | 36.7 | 41.9 | 5.9-15.9 |
| door +x+y (y wall) 3 | 2.30 | 94 | 1045 | 4.9 | 69.4 | 37.9 | 47.1 | 16.3-26.2 |
| door +x+y (y wall) 4 | 2.30 | 97 | 513 | 4.9 | 69.8 | 38.9 | 49.7 | 24.1-34.1 |
| door +x+y (x wall) 0 | 2.30 | 93 | 2577 | 4.9 | 69.4 | 37.5 | 47.1 | 12.6-22.6 |
| door +x+y (x wall) 1 | 2.30 | 98 | 2137 | 4.9 | 69.8 | 39.3 | 47.1 | 12.6-22.6 |
| door +x+y (x wall) 2 | 2.30 | 95 | 1594 | 4.9 | 70.0 | 38.0 | 47.1 | 25.7-35.7 |
| door +x+y (x wall) 3 | 2.30 | 97 | 1045 | 4.9 | 69.6 | 39.0 | 47.1 | 12.6-22.6 |
| door +x+y (x wall) 4 | 2.30 | 95 | 513 | 5.1 | 69.4 | 38.4 | 44.5 | 16.3-26.2 |
| door +x+y (corner) | 2.30 | 95 | 124 | 6.3 | 69.3 | 39.2 | 41.9 | 5.9-15.9 |
| door -x+y (y wall) 0 | 2.30 | 93 | 2577 | 4.9 | 69.1 | 37.7 | 47.1 | 27.1-37.1 |
| door -x+y (y wall) 1 | 2.30 | 95 | 2137 | 4.9 | 69.4 | 38.3 | 47.1 | 27.1-37.1 |
| door -x+y (y wall) 2 | 2.30 | 96 | 1594 | 4.9 | 69.8 | 38.5 | 44.5 | 11.4-21.3 |
| door -x+y (y wall) 3 | 2.30 | 96 | 1045 | 4.9 | 69.8 | 38.5 | 47.1 | 21.0-31.0 |
| door -x+y (y wall) 4 | 2.30 | 94 | 513 | 5.1 | 69.6 | 37.9 | 44.5 | 13.3-23.3 |
| door -x+y (x wall) 0 | 2.30 | 94 | 2577 | 4.9 | 68.9 | 38.2 | 44.5 | 28.2-38.1 |
| door -x+y (x wall) 1 | 2.30 | 93 | 2137 | 4.9 | 69.3 | 37.6 | 44.5 | 31.0-40.9 |
| door -x+y (x wall) 2 | 2.30 | 91 | 1594 | 4.9 | 68.9 | 37.0 | 44.5 | 29.4-39.4 |
| door -x+y (x wall) 3 | 2.30 | 95 | 1045 | 4.9 | 69.8 | 38.1 | 44.5 | 27.6-37.6 |
| door -x+y (x wall) 4 | 2.30 | 96 | 513 | 4.9 | 70.0 | 38.4 | 47.1 | 8.7-18.7 |
| door -x+y (corner) | 2.30 | 92 | 124 | 6.3 | 68.7 | 38.3 | 41.9 | 5.9-15.9 |
| door -x-y (y wall) 0 | 2.30 | 95 | 2577 | 4.9 | 70.0 | 38.0 | 44.5 | 31.1-41.1 |
| door -x-y (y wall) 1 | 2.30 | 95 | 2137 | 4.9 | 69.8 | 38.1 | 44.5 | 27.1-37.1 |
| door -x-y (y wall) 2 | 2.30 | 94 | 1594 | 4.9 | 70.0 | 37.6 | 44.5 | 27.1-37.1 |
| door -x-y (y wall) 3 | 2.30 | 95 | 1045 | 4.9 | 69.6 | 38.2 | 44.5 | 27.1-37.1 |
| door -x-y (y wall) 4 | 2.30 | 99 | 513 | 4.9 | 69.1 | 40.1 | 47.1 | 14.3-24.3 |
| door -x-y (x wall) 0 | 2.30 | 96 | 2577 | 4.9 | 69.8 | 38.5 | 47.1 | 27.3-37.3 |
| door -x-y (x wall) 1 | 2.30 | 95 | 2137 | 4.9 | 69.4 | 38.3 | 47.1 | 26.9-36.9 |
| door -x-y (x wall) 2 | 2.30 | 95 | 1594 | 4.9 | 69.6 | 38.2 | 47.1 | 26.1-36.0 |
| door -x-y (x wall) 3 | 2.30 | 97 | 1045 | 4.9 | 70.0 | 38.8 | 47.1 | 26.8-36.7 |
| door -x-y (x wall) 4 | 2.30 | 94 | 513 | 5.1 | 68.9 | 38.3 | 44.5 | 13.3-23.3 |
| door -x-y (corner) | 2.30 | 95 | 124 | 6.3 | 69.3 | 39.2 | 44.5 | 35.7-45.7 |
| door +x-y (y wall) 0 | 2.30 | 94 | 2577 | 4.9 | 69.3 | 38.0 | 44.5 | 30.6-40.6 |
| door +x-y (y wall) 1 | 2.30 | 95 | 2137 | 4.9 | 69.1 | 38.5 | 44.5 | 26.8-36.7 |
| door +x-y (y wall) 2 | 2.30 | 93 | 1594 | 4.9 | 69.4 | 37.5 | 47.1 | 22.7-32.7 |
| door +x-y (y wall) 3 | 2.30 | 95 | 1045 | 4.9 | 69.4 | 38.3 | 44.5 | 11.4-21.3 |
| door +x-y (y wall) 4 | 2.30 | 93 | 513 | 5.1 | 69.1 | 37.8 | 44.5 | 13.3-23.3 |
| door +x-y (x wall) 0 | 2.30 | 95 | 2577 | 4.9 | 68.9 | 38.6 | 44.5 | 8.6-18.5 |
| door +x-y (x wall) 1 | 2.30 | 96 | 2137 | 4.9 | 69.6 | 38.6 | 47.1 | 22.6-32.5 |
| door +x-y (x wall) 2 | 2.30 | 101 | 1594 | 4.9 | 69.6 | 40.6 | 47.1 | 12.6-22.6 |
| door +x-y (x wall) 3 | 2.30 | 96 | 1045 | 4.9 | 68.9 | 39.0 | 47.1 | 12.6-22.6 |
| door +x-y (x wall) 4 | 2.30 | 92 | 513 | 5.1 | 69.8 | 37.0 | 47.1 | 20.5-30.4 |
| door +x-y (corner) | 2.30 | 98 | 124 | 6.5 | 69.6 | 40.4 | 44.5 | 40.4-50.4 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (2.30 m; a corner door's: the gap between its wall ends, 2.30 m); agents are removed past the outer wall's outer face (92.71 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 0 | 0.0% | nan% |
| -x | avenue | 5.66 | 0 | 0.0% | nan% |
| +y | avenue | 5.66 | 0 | 0.0% | nan% |
| -y | avenue | 5.66 | 0 | 0.0% | nan% |
| door +x+y (y wall) 0 | door | 2.30 | 95 | 2.3% | nan% |
| door +x+y (y wall) 1 | door | 2.30 | 95 | 2.3% | nan% |
| door +x+y (y wall) 2 | door | 2.30 | 91 | 2.2% | nan% |
| door +x+y (y wall) 3 | door | 2.30 | 94 | 2.2% | nan% |
| door +x+y (y wall) 4 | door | 2.30 | 97 | 2.3% | nan% |
| door +x+y (x wall) 0 | door | 2.30 | 93 | 2.2% | nan% |
| door +x+y (x wall) 1 | door | 2.30 | 98 | 2.3% | nan% |
| door +x+y (x wall) 2 | door | 2.30 | 95 | 2.3% | nan% |
| door +x+y (x wall) 3 | door | 2.30 | 97 | 2.3% | nan% |
| door +x+y (x wall) 4 | door | 2.30 | 95 | 2.3% | nan% |
| door +x+y (corner) | door | 2.30 | 95 | 2.3% | nan% |
| door -x+y (y wall) 0 | door | 2.30 | 93 | 2.2% | nan% |
| door -x+y (y wall) 1 | door | 2.30 | 95 | 2.3% | nan% |
| door -x+y (y wall) 2 | door | 2.30 | 96 | 2.3% | nan% |
| door -x+y (y wall) 3 | door | 2.30 | 96 | 2.3% | nan% |
| door -x+y (y wall) 4 | door | 2.30 | 94 | 2.2% | nan% |
| door -x+y (x wall) 0 | door | 2.30 | 94 | 2.2% | nan% |
| door -x+y (x wall) 1 | door | 2.30 | 93 | 2.2% | nan% |
| door -x+y (x wall) 2 | door | 2.30 | 91 | 2.2% | nan% |
| door -x+y (x wall) 3 | door | 2.30 | 95 | 2.3% | nan% |
| door -x+y (x wall) 4 | door | 2.30 | 96 | 2.3% | nan% |
| door -x+y (corner) | door | 2.30 | 92 | 2.2% | nan% |
| door -x-y (y wall) 0 | door | 2.30 | 95 | 2.3% | nan% |
| door -x-y (y wall) 1 | door | 2.30 | 95 | 2.3% | nan% |
| door -x-y (y wall) 2 | door | 2.30 | 94 | 2.2% | nan% |
| door -x-y (y wall) 3 | door | 2.30 | 95 | 2.3% | nan% |
| door -x-y (y wall) 4 | door | 2.30 | 99 | 2.4% | nan% |
| door -x-y (x wall) 0 | door | 2.30 | 96 | 2.3% | nan% |
| door -x-y (x wall) 1 | door | 2.30 | 95 | 2.3% | nan% |
| door -x-y (x wall) 2 | door | 2.30 | 95 | 2.3% | nan% |
| door -x-y (x wall) 3 | door | 2.30 | 97 | 2.3% | nan% |
| door -x-y (x wall) 4 | door | 2.30 | 94 | 2.2% | nan% |
| door -x-y (corner) | door | 2.30 | 95 | 2.3% | nan% |
| door +x-y (y wall) 0 | door | 2.30 | 94 | 2.2% | nan% |
| door +x-y (y wall) 1 | door | 2.30 | 95 | 2.3% | nan% |
| door +x-y (y wall) 2 | door | 2.30 | 93 | 2.2% | nan% |
| door +x-y (y wall) 3 | door | 2.30 | 95 | 2.3% | nan% |
| door +x-y (y wall) 4 | door | 2.30 | 93 | 2.2% | nan% |
| door +x-y (x wall) 0 | door | 2.30 | 95 | 2.3% | nan% |
| door +x-y (x wall) 1 | door | 2.30 | 96 | 2.3% | nan% |
| door +x-y (x wall) 2 | door | 2.30 | 101 | 2.4% | nan% |
| door +x-y (x wall) 3 | door | 2.30 | 96 | 2.3% | nan% |
| door +x-y (x wall) 4 | door | 2.30 | 92 | 2.2% | nan% |
| door +x-y (corner) | door | 2.30 | 98 | 2.3% | nan% |
| **doors (44)** | door | 101.20 | 4178 | 100.0% | |
| **avenues (4)** | avenue | 22.64 | 0 | 0.0% | |

**Unused exit width: 22.6 of 123.8 m (18.3%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = nan s: the share of the exit's nominal throughput over the whole evacuation used; all exits together nan%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 723 | 1.1% | 95 | 2.3% |
| straight +x+y (y wing) 1 | straight | yes | 590 | 0.9% | 95 | 2.3% |
| straight +x+y (y wing) 2 | straight | yes | 447 | 0.7% | 91 | 2.2% |
| straight +x+y (y wing) 3 | straight | yes | 334 | 0.5% | 94 | 2.2% |
| straight +x+y (y wing) 4 | straight | yes | 197 | 0.3% | 97 | 2.3% |
| straight +x+y (x wing) 0 | straight | yes | 729 | 1.1% | 93 | 2.2% |
| straight +x+y (x wing) 1 | straight | yes | 585 | 0.9% | 98 | 2.3% |
| straight +x+y (x wing) 2 | straight | yes | 443 | 0.7% | 95 | 2.3% |
| straight +x+y (x wing) 3 | straight | yes | 311 | 0.5% | 97 | 2.3% |
| straight +x+y (x wing) 4 | straight | yes | 194 | 0.3% | 95 | 2.3% |
| corner +x+y | corner | yes | 905 | 1.4% | 95 | 2.3% |
| straight -x+y (y wing) 0 | straight | yes | 731 | 1.2% | 93 | 2.2% |
| straight -x+y (y wing) 1 | straight | yes | 570 | 0.9% | 95 | 2.3% |
| straight -x+y (y wing) 2 | straight | yes | 451 | 0.7% | 96 | 2.3% |
| straight -x+y (y wing) 3 | straight | yes | 315 | 0.5% | 96 | 2.3% |
| straight -x+y (y wing) 4 | straight | yes | 190 | 0.3% | 94 | 2.2% |
| straight -x+y (x wing) 0 | straight | yes | 720 | 1.1% | 94 | 2.2% |
| straight -x+y (x wing) 1 | straight | yes | 578 | 0.9% | 93 | 2.2% |
| straight -x+y (x wing) 2 | straight | yes | 452 | 0.7% | 91 | 2.2% |
| straight -x+y (x wing) 3 | straight | yes | 337 | 0.5% | 95 | 2.3% |
| straight -x+y (x wing) 4 | straight | yes | 195 | 0.3% | 96 | 2.3% |
| corner -x+y | corner | yes | 912 | 1.4% | 92 | 2.2% |
| straight -x-y (y wing) 0 | straight | yes | 725 | 1.1% | 95 | 2.3% |
| straight -x-y (y wing) 1 | straight | yes | 565 | 0.9% | 95 | 2.3% |
| straight -x-y (y wing) 2 | straight | yes | 444 | 0.7% | 94 | 2.2% |
| straight -x-y (y wing) 3 | straight | yes | 326 | 0.5% | 95 | 2.3% |
| straight -x-y (y wing) 4 | straight | yes | 204 | 0.3% | 99 | 2.4% |
| straight -x-y (x wing) 0 | straight | yes | 731 | 1.2% | 96 | 2.3% |
| straight -x-y (x wing) 1 | straight | yes | 585 | 0.9% | 95 | 2.3% |
| straight -x-y (x wing) 2 | straight | yes | 454 | 0.7% | 95 | 2.3% |
| straight -x-y (x wing) 3 | straight | yes | 317 | 0.5% | 97 | 2.3% |
| straight -x-y (x wing) 4 | straight | yes | 191 | 0.3% | 94 | 2.2% |
| corner -x-y | corner | yes | 902 | 1.4% | 95 | 2.3% |
| straight +x-y (y wing) 0 | straight | yes | 736 | 1.2% | 94 | 2.2% |
| straight +x-y (y wing) 1 | straight | yes | 581 | 0.9% | 95 | 2.3% |
| straight +x-y (y wing) 2 | straight | yes | 457 | 0.7% | 93 | 2.2% |
| straight +x-y (y wing) 3 | straight | yes | 317 | 0.5% | 95 | 2.3% |
| straight +x-y (y wing) 4 | straight | yes | 193 | 0.3% | 93 | 2.2% |
| straight +x-y (x wing) 0 | straight | yes | 736 | 1.2% | 95 | 2.3% |
| straight +x-y (x wing) 1 | straight | yes | 578 | 0.9% | 96 | 2.3% |
| straight +x-y (x wing) 2 | straight | yes | 446 | 0.7% | 101 | 2.4% |
| straight +x-y (x wing) 3 | straight | yes | 311 | 0.5% | 96 | 2.3% |
| straight +x-y (x wing) 4 | straight | yes | 191 | 0.3% | 92 | 2.2% |
| corner +x-y | corner | yes | 937 | 1.5% | 98 | 2.3% |
| **straight (40)** | | | 18180 | | 3798 | 90.9% |
| **corner (4)** | | | 3656 | | 380 | 9.1% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| door +x+y (y wall) 0 | 95 | 4.9 | 69.8 | 0.46 | 0.56 | 0.0% |
| door +x+y (y wall) 1 | 95 | 4.9 | 69.3 | 0.46 | 0.53 | 0.0% |
| door +x+y (y wall) 2 | 91 | 4.9 | 69.4 | 0.44 | 0.50 | 0.0% |
| door +x+y (y wall) 3 | 94 | 4.9 | 69.4 | 0.45 | 0.56 | 0.0% |
| door +x+y (y wall) 4 | 97 | 4.9 | 69.8 | 0.47 | 0.59 | 0.0% |
| door +x+y (x wall) 0 | 93 | 4.9 | 69.4 | 0.45 | 0.56 | 0.0% |
| door +x+y (x wall) 1 | 98 | 4.9 | 69.8 | 0.47 | 0.56 | 0.0% |
| door +x+y (x wall) 2 | 95 | 4.9 | 70.0 | 0.45 | 0.56 | 0.0% |
| door +x+y (x wall) 3 | 97 | 4.9 | 69.6 | 0.47 | 0.56 | 0.0% |
| door +x+y (x wall) 4 | 95 | 5.1 | 69.4 | 0.46 | 0.53 | 0.0% |
| door +x+y (corner) | 95 | 6.3 | 69.3 | 0.47 | 0.50 | 0.0% |
| door -x+y (y wall) 0 | 93 | 4.9 | 69.1 | 0.45 | 0.56 | 0.0% |
| door -x+y (y wall) 1 | 95 | 4.9 | 69.4 | 0.46 | 0.56 | 0.0% |
| door -x+y (y wall) 2 | 96 | 4.9 | 69.8 | 0.46 | 0.53 | 0.0% |
| door -x+y (y wall) 3 | 96 | 4.9 | 69.8 | 0.46 | 0.56 | 0.0% |
| door -x+y (y wall) 4 | 94 | 5.1 | 69.6 | 0.45 | 0.53 | 0.0% |
| door -x+y (x wall) 0 | 94 | 4.9 | 68.9 | 0.46 | 0.53 | 0.0% |
| door -x+y (x wall) 1 | 93 | 4.9 | 69.3 | 0.45 | 0.53 | 0.0% |
| door -x+y (x wall) 2 | 91 | 4.9 | 68.9 | 0.44 | 0.53 | 0.0% |
| door -x+y (x wall) 3 | 95 | 4.9 | 69.8 | 0.46 | 0.53 | 0.0% |
| door -x+y (x wall) 4 | 96 | 4.9 | 70.0 | 0.46 | 0.56 | 0.0% |
| door -x+y (corner) | 92 | 6.3 | 68.7 | 0.46 | 0.50 | 0.0% |
| door -x-y (y wall) 0 | 95 | 4.9 | 70.0 | 0.45 | 0.53 | 0.0% |
| door -x-y (y wall) 1 | 95 | 4.9 | 69.8 | 0.46 | 0.53 | 0.0% |
| door -x-y (y wall) 2 | 94 | 4.9 | 70.0 | 0.45 | 0.53 | 0.0% |
| door -x-y (y wall) 3 | 95 | 4.9 | 69.6 | 0.46 | 0.53 | 0.0% |
| door -x-y (y wall) 4 | 99 | 4.9 | 69.1 | 0.48 | 0.56 | 0.0% |
| door -x-y (x wall) 0 | 96 | 4.9 | 69.8 | 0.46 | 0.56 | 0.0% |
| door -x-y (x wall) 1 | 95 | 4.9 | 69.4 | 0.46 | 0.56 | 0.0% |
| door -x-y (x wall) 2 | 95 | 4.9 | 69.6 | 0.46 | 0.56 | 0.0% |
| door -x-y (x wall) 3 | 97 | 4.9 | 70.0 | 0.46 | 0.56 | 0.0% |
| door -x-y (x wall) 4 | 94 | 5.1 | 68.9 | 0.46 | 0.53 | 0.0% |
| door -x-y (corner) | 95 | 6.3 | 69.3 | 0.47 | 0.53 | 0.0% |
| door +x-y (y wall) 0 | 94 | 4.9 | 69.3 | 0.45 | 0.53 | 0.0% |
| door +x-y (y wall) 1 | 95 | 4.9 | 69.1 | 0.46 | 0.53 | 0.0% |
| door +x-y (y wall) 2 | 93 | 4.9 | 69.4 | 0.45 | 0.56 | 0.0% |
| door +x-y (y wall) 3 | 95 | 4.9 | 69.4 | 0.46 | 0.53 | 0.0% |
| door +x-y (y wall) 4 | 93 | 5.1 | 69.1 | 0.45 | 0.53 | 0.0% |
| door +x-y (x wall) 0 | 95 | 4.9 | 68.9 | 0.46 | 0.53 | 0.0% |
| door +x-y (x wall) 1 | 96 | 4.9 | 69.6 | 0.46 | 0.56 | 0.0% |
| door +x-y (x wall) 2 | 101 | 4.9 | 69.6 | 0.49 | 0.56 | 0.0% |
| door +x-y (x wall) 3 | 96 | 4.9 | 68.9 | 0.47 | 0.56 | 0.0% |
| door +x-y (x wall) 4 | 92 | 5.1 | 69.8 | 0.44 | 0.56 | 0.0% |
| door +x-y (corner) | 98 | 6.5 | 69.6 | 0.48 | 0.53 | 0.0% |

Mean flow / w J averaged over the doors 0.46, over the avenues nan.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 103.1 | 723 | 99 / 46 / 1 | 0.7 | 69.6 | 2.11 | 2.31 | 86% | 86% | 0% | 4.68 |
| straight +x+y (y wing) 1 | 1.20 | 81.5 | 589 | 99 / 0 / 13 | 0.7 | 69.4 | 1.63 | 2.01 | 86% | 86% | 0% | 4.77 |
| straight +x+y (y wing) 2 | 1.20 | 61.0 | 446 | 95 / 0 / 8 | 0.7 | 69.4 | 1.49 | 1.71 | 86% | 86% | 0% | 4.67 |
| straight +x+y (y wing) 3 | 1.20 | 39.4 | 333 | 96 / 0 / 2 | 0.7 | 68.9 | 1.43 | 1.71 | 86% | 86% | 0% | 4.88 |
| straight +x+y (y wing) 4 | 1.20 | 18.8 | 194 | 101 / 0 / 5 | 0.7 | 68.9 | 1.55 | 1.81 | 86% | 86% | 0% | 4.63 |
| straight +x+y (x wing) 0 | 1.20 | 103.1 | 729 | 97 / 45 / 3 | 0.7 | 69.1 | 2.11 | 2.41 | 86% | 86% | 0% | 4.97 |
| straight +x+y (x wing) 1 | 1.20 | 81.5 | 584 | 102 / 0 / 18 | 0.7 | 69.8 | 1.73 | 2.01 | 86% | 86% | 0% | 4.99 |
| straight +x+y (x wing) 2 | 1.20 | 61.0 | 440 | 99 / 0 / 7 | 0.7 | 69.1 | 1.55 | 1.81 | 86% | 86% | 0% | 4.97 |
| straight +x+y (x wing) 3 | 1.20 | 39.4 | 309 | 100 / 0 / 3 | 0.7 | 69.1 | 1.50 | 1.60 | 100% | 100% | 0% | 4.94 |
| straight +x+y (x wing) 4 | 1.20 | 18.8 | 190 | 98 / 0 / 4 | 0.7 | 69.6 | 1.48 | 1.71 | 86% | 86% | 0% | 4.57 |
| corner +x+y | 1.20 | 186.0 | 874 | 101 / 86 / 21 | 0.7 | 69.1 | 3.03 | 3.31 | 86% | 71% | 14% | 3.33 |
| straight -x+y (y wing) 0 | 1.20 | 103.1 | 731 | 96 / 46 / 1 | 0.7 | 69.4 | 2.08 | 2.41 | 86% | 86% | 0% | 4.95 |
| straight -x+y (y wing) 1 | 1.20 | 81.5 | 569 | 99 / 0 / 12 | 0.7 | 70.0 | 1.60 | 2.01 | 75% | 75% | 0% | 5.01 |
| straight -x+y (y wing) 2 | 1.20 | 61.0 | 449 | 99 / 0 / 10 | 0.7 | 69.4 | 1.58 | 1.91 | 86% | 86% | 0% | 5.01 |
| straight -x+y (y wing) 3 | 1.20 | 39.4 | 313 | 99 / 0 / 4 | 0.7 | 69.4 | 1.49 | 1.71 | 100% | 100% | 0% | 4.93 |
| straight -x+y (y wing) 4 | 1.20 | 18.8 | 184 | 99 / 0 / 3 | 0.7 | 69.8 | 1.47 | 1.60 | 86% | 86% | 0% | 4.72 |
| straight -x+y (x wing) 0 | 1.20 | 103.1 | 720 | 98 / 48 / 2 | 0.7 | 69.3 | 2.15 | 2.31 | 86% | 86% | 0% | 4.67 |
| straight -x+y (x wing) 1 | 1.20 | 81.5 | 577 | 98 / 0 / 11 | 0.7 | 70.0 | 1.57 | 1.91 | 88% | 88% | 0% | 4.90 |
| straight -x+y (x wing) 2 | 1.20 | 61.0 | 450 | 96 / 0 / 5 | 0.7 | 69.4 | 1.47 | 1.60 | 86% | 86% | 0% | 4.74 |
| straight -x+y (x wing) 3 | 1.20 | 39.4 | 335 | 98 / 0 / 2 | 0.7 | 69.8 | 1.44 | 1.81 | 86% | 86% | 0% | 4.90 |
| straight -x+y (x wing) 4 | 1.20 | 18.8 | 192 | 100 / 0 / 3 | 0.7 | 69.8 | 1.49 | 1.60 | 86% | 86% | 0% | 4.65 |
| corner -x+y | 1.20 | 186.0 | 884 | 97 / 78 / 20 | 0.7 | 70.0 | 2.81 | 3.21 | 75% | 62% | 12% | 3.33 |
| straight -x-y (y wing) 0 | 1.20 | 103.1 | 725 | 98 / 48 / 2 | 0.7 | 69.6 | 2.14 | 2.41 | 86% | 86% | 0% | 4.68 |
| straight -x-y (y wing) 1 | 1.20 | 81.5 | 564 | 98 / 0 / 10 | 0.7 | 69.3 | 1.57 | 1.81 | 100% | 100% | 0% | 4.82 |
| straight -x-y (y wing) 2 | 1.20 | 61.0 | 442 | 98 / 0 / 6 | 0.7 | 69.6 | 1.51 | 1.60 | 86% | 86% | 0% | 4.68 |
| straight -x-y (y wing) 3 | 1.20 | 39.4 | 324 | 98 / 0 / 3 | 0.7 | 69.6 | 1.46 | 1.71 | 86% | 86% | 0% | 4.84 |
| straight -x-y (y wing) 4 | 1.20 | 18.8 | 201 | 102 / 0 / 5 | 0.7 | 68.7 | 1.57 | 1.71 | 86% | 86% | 0% | 4.65 |
| straight -x-y (x wing) 0 | 1.20 | 103.1 | 731 | 100 / 45 / 2 | 0.7 | 69.6 | 2.13 | 2.41 | 86% | 86% | 0% | 4.94 |
| straight -x-y (x wing) 1 | 1.20 | 81.5 | 584 | 99 / 0 / 12 | 0.7 | 69.8 | 1.60 | 2.01 | 86% | 86% | 0% | 5.05 |
| straight -x-y (x wing) 2 | 1.20 | 61.0 | 452 | 98 / 0 / 6 | 0.7 | 69.1 | 1.52 | 1.81 | 86% | 86% | 0% | 5.01 |
| straight -x-y (x wing) 3 | 1.20 | 39.4 | 315 | 101 / 0 / 4 | 0.7 | 69.6 | 1.52 | 1.71 | 100% | 100% | 0% | 4.99 |
| straight -x-y (x wing) 4 | 1.20 | 18.8 | 184 | 98 / 0 / 4 | 0.7 | 69.6 | 1.48 | 1.60 | 86% | 86% | 0% | 4.68 |
| corner -x-y | 1.20 | 186.0 | 875 | 101 / 84 / 23 | 0.7 | 69.4 | 3.02 | 3.31 | 86% | 71% | 14% | 3.30 |
| straight +x-y (y wing) 0 | 1.20 | 103.1 | 736 | 98 / 47 / 3 | 0.7 | 70.0 | 2.13 | 2.31 | 75% | 75% | 0% | 4.97 |
| straight +x-y (y wing) 1 | 1.20 | 81.5 | 580 | 99 / 0 / 14 | 0.7 | 69.8 | 1.63 | 1.81 | 86% | 86% | 0% | 5.02 |
| straight +x-y (y wing) 2 | 1.20 | 61.0 | 455 | 97 / 0 / 8 | 0.7 | 69.3 | 1.53 | 2.01 | 100% | 100% | 0% | 5.14 |
| straight +x-y (y wing) 3 | 1.20 | 39.4 | 315 | 99 / 0 / 4 | 0.7 | 69.8 | 1.49 | 1.71 | 86% | 86% | 0% | 4.91 |
| straight +x-y (y wing) 4 | 1.20 | 18.8 | 187 | 98 / 0 / 7 | 0.7 | 70.0 | 1.51 | 1.81 | 75% | 75% | 0% | 4.70 |
| straight +x-y (x wing) 0 | 1.20 | 103.1 | 736 | 100 / 47 / 1 | 0.7 | 69.6 | 2.14 | 2.41 | 86% | 86% | 0% | 4.97 |
| straight +x-y (x wing) 1 | 1.20 | 81.5 | 577 | 99 / 0 / 12 | 0.7 | 69.3 | 1.61 | 2.31 | 86% | 86% | 0% | 4.99 |
| straight +x-y (x wing) 2 | 1.20 | 61.0 | 444 | 104 / 0 / 8 | 0.7 | 69.3 | 1.63 | 1.91 | 86% | 86% | 0% | 4.98 |
| straight +x-y (x wing) 3 | 1.20 | 39.4 | 309 | 102 / 0 / 4 | 0.7 | 69.6 | 1.53 | 1.71 | 86% | 86% | 0% | 4.85 |
| straight +x-y (x wing) 4 | 1.20 | 18.8 | 187 | 95 / 0 / 3 | 0.7 | 69.6 | 1.42 | 1.71 | 86% | 86% | 0% | 4.66 |
| corner +x-y | 1.20 | 186.0 | 904 | 104 / 86 / 24 | 0.7 | 70.0 | 3.08 | 3.31 | 75% | 62% | 12% | 3.31 |

The last agent out (agent 15463, t100 nan s): last gangway straight +x+y (x wing) 2, exit door +x+y (x wall) 2. The gangway that cleared last: straight -x+y (y wing) 1 at 70.0 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 8804 | 7800.4 | 6.83 | 70.0 / 69.8 / 66.5 | 70.0 / 69.8 / 66.3 | 564063.5 | 1133647 | 0.074 |
| gangway | 3792 | 3512.9 | 6.83 | 70.0 / 69.8 / 66.5 | 70.0 / 69.8 / 66.3 | 564063.5 | 1089188 | 0.038 |
| walkway | 276 | 257.4 | 3.12 | 55.4 / 40.1 / 0.0 | 54.7 / 18.4 / 0.0 | 0.0 | 6287 | 0.736 |
| avenue | 1920 | 1801.4 | 1.75 | 49.8 / 0.0 / 0.0 | 48.6 / 0.0 / 0.0 | 0.0 | 15289 | 1.323 |
| exit | 4 | 2.0 | 0.00 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 0 | - |
| concourse | 2812 | 2226.8 | 2.60 | 68.7 / 19.9 / 0.0 | 67.5 / 2.6 / 0.0 | 0.0 | 22883 | 0.797 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 25392 | 16030.4 | 7.74 | 70.0 / 70.0 / 70.0 | 70.0 / 70.0 / 68.6 | 1235161.6 | 3162290 | 0.064 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 208 x 208 from (-104, -104) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -82.5 | 57.5 | gangway | 1.00 | 6.32 | 69.4 | 68.9 | 63.7 | 367.4 | 0.019 |
| 2 | 57.5 | 78.5 | gangway | 1.00 | 6.31 | 69.4 | 68.9 | 63.7 | 362.9 | 0.014 |
| 3 | 57.5 | 82.5 | gangway | 1.00 | 6.16 | 69.4 | 68.9 | 63.5 | 362.9 | 0.017 |
| 4 | -78.5 | 57.5 | gangway | 1.00 | 6.27 | 69.4 | 68.9 | 63.7 | 362.7 | 0.015 |
| 5 | -57.5 | -82.5 | gangway | 1.00 | 6.02 | 69.4 | 68.9 | 63.7 | 359.4 | 0.014 |
| 6 | -57.5 | 77.5 | gangway | 1.00 | 5.91 | 69.4 | 68.9 | 64.2 | 356.9 | 0.017 |
| 7 | 57.5 | -77.5 | gangway | 1.00 | 5.98 | 69.4 | 68.9 | 64.2 | 356.6 | 0.017 |
| 8 | -77.5 | -57.5 | gangway | 1.00 | 5.97 | 69.4 | 68.9 | 64.2 | 356.0 | 0.017 |
| 9 | 73.5 | -57.5 | gangway | 1.00 | 5.72 | 69.3 | 68.7 | 64.4 | 351.0 | 0.016 |
| 10 | -57.5 | -78.5 | gangway | 1.00 | 5.80 | 69.4 | 68.9 | 63.7 | 350.5 | 0.014 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -27.5 | -78.5 | seat row | 0.66 | 6.91 | 70.0 | 70.0 | 67.2 | 287.0 | 0.025 |
| 2 | 27.5 | 78.5 | seat row | 0.66 | 6.92 | 70.0 | 70.0 | 67.2 | 286.0 | 0.025 |
| 3 | -78.5 | 27.5 | seat row | 0.66 | 6.91 | 70.0 | 70.0 | 67.2 | 285.5 | 0.026 |
| 4 | -82.5 | 27.5 | seat row | 0.66 | 6.78 | 70.0 | 70.0 | 67.2 | 285.0 | 0.027 |
| 5 | 27.5 | 82.5 | seat row | 0.66 | 6.74 | 70.0 | 70.0 | 67.2 | 284.6 | 0.027 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 35; agent-steps of seated agents on another row's clearway: 2382.

## Deposit check

Person-seconds deposited: 4296317.4, of them in excluded cells: 380.078.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 681784 overlapping pair-steps: p99 0.0024, max 0.0417 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0024 max 0.0417; venue-geometry 2: p99 0.0002 max 0.0002 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 4 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.35 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 21 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
