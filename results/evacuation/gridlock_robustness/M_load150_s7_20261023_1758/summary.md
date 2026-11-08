# Experiment `M_load150_s7`

**Task 5.11 stage 1 (gridlock robustness, default model, AMD 26.10.1): venue M, the achievable maximum 121.42% (150% requested, seed 7)**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 19223 agents (load 121.4%, requested 150%): every one of the 15832 seats and 3391 standing (spawnOvercrowdedCrowd, seed 7; below), buffer N = 32768, 3381 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 1464802 evaluations, 59346 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.21)** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `15aa31e8667e4a9417fde7884d907d1832c5e2d6`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-23T17:58:02, 105.6 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Spawn (overcrowding)

| | |
|---|---|
| seated | 15832 (every seat) |
| standing | **3391** (requested round((1.50 - 1) x 15832) = 7916; at most 3391 = floor(2.5 p/m^2 x 1356.6 m^2)) |
| standing floor | walkway + rear concourse, 1356.6 m^2 |
| standing on the walkway / concourse / gangways | 634 / 2757 / 0 |
| **load** | **121.42%** of the seats (requested 150%; the floor takes no more: the achievable maximum) |
| standing crowd's mean density | 2.500 p/m^2 |
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 3.93, all circulation cells 3.93 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 7, 104643 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1187 | 207.6 |
| t90 | 2617 | 457.7 |
| t100 | 3381 | 591.4 |

t_p: the step by which ceil(p x 19223) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 941 | 85 | 29.0 | 532.4 | 19.8 | 57.4 | 28.9-38.8 |
| -x | 5.66 | 964 | 85 | 29.0 | 539.2 | 20.0 | 59.5 | 28.9-38.8 |
| +y | 5.66 | 954 | 87 | 29.0 | 532.6 | 20.1 | 58.5 | 28.2-38.1 |
| -y | 5.66 | 964 | 91 | 29.0 | 527.0 | 20.5 | 62.7 | 28.5-38.5 |
| door +x+y (y wall) 0 | 1.20 | 728 | 1266 | 0.9 | 544.8 | 66.9 | 125.4 | 110.9-120.9 |
| door +x+y (y wall) 1 | 1.20 | 701 | 794 | 1.0 | 567.9 | 61.8 | 120.4 | 100.7-110.7 |
| door +x+y (y wall) 2 | 1.20 | 387 | 264 | 0.7 | 583.7 | 33.2 | 115.3 | 57.7-67.7 |
| door +x+y (x wall) 0 | 1.20 | 726 | 1274 | 0.9 | 531.5 | 68.4 | 125.4 | 102.5-112.5 |
| door +x+y (x wall) 1 | 1.20 | 689 | 795 | 1.0 | 553.1 | 62.4 | 125.4 | 95.1-105.1 |
| door +x+y (x wall) 2 | 1.20 | 413 | 270 | 1.0 | 584.4 | 35.4 | 110.3 | 72.8-82.7 |
| door +x+y (corner) | 1.20 | 203 | 46 | 0.7 | 578.4 | 17.6 | 115.3 | 0.5-10.5 |
| door -x+y (y wall) 0 | 1.20 | 717 | 1271 | 0.9 | 534.3 | 67.2 | 125.4 | 100.0-110.0 |
| door -x+y (y wall) 1 | 1.20 | 716 | 800 | 1.0 | 546.1 | 65.7 | 120.4 | 103.7-113.7 |
| door -x+y (y wall) 2 | 1.20 | 388 | 272 | 0.9 | 591.4 | 32.8 | 110.3 | 82.0-92.0 |
| door -x+y (x wall) 0 | 1.20 | 739 | 1269 | 1.0 | 547.5 | 67.6 | 120.4 | 100.7-110.7 |
| door -x+y (x wall) 1 | 1.20 | 707 | 797 | 1.0 | 538.2 | 65.8 | 130.4 | 101.4-111.4 |
| door -x+y (x wall) 2 | 1.20 | 347 | 267 | 0.9 | 583.3 | 29.8 | 105.3 | 45.3-55.3 |
| door -x+y (corner) | 1.20 | 236 | 48 | 0.9 | 584.0 | 20.2 | 115.3 | 7.7-17.7 |
| door -x-y (y wall) 0 | 1.20 | 719 | 1271 | 1.2 | 554.5 | 65.0 | 135.4 | 101.4-111.4 |
| door -x-y (y wall) 1 | 1.20 | 708 | 802 | 0.9 | 553.6 | 64.0 | 120.4 | 106.5-116.5 |
| door -x-y (y wall) 2 | 1.20 | 400 | 279 | 0.9 | 573.3 | 34.9 | 100.3 | 1.4-11.4 |
| door -x-y (x wall) 0 | 1.20 | 713 | 1263 | 0.9 | 539.1 | 66.2 | 115.3 | 101.8-111.8 |
| door -x-y (x wall) 1 | 1.20 | 708 | 794 | 0.9 | 552.0 | 64.2 | 120.4 | 99.3-109.3 |
| door -x-y (x wall) 2 | 1.20 | 363 | 261 | 0.9 | 585.9 | 31.0 | 120.4 | 79.4-89.4 |
| door -x-y (corner) | 1.20 | 232 | 43 | 0.9 | 561.6 | 20.7 | 115.3 | 0.7-10.7 |
| door +x-y (y wall) 0 | 1.20 | 713 | 1273 | 1.0 | 540.5 | 66.1 | 120.4 | 104.1-114.0 |
| door +x-y (y wall) 1 | 1.20 | 704 | 787 | 1.2 | 543.8 | 64.9 | 115.3 | 97.2-107.2 |
| door +x-y (y wall) 2 | 1.20 | 394 | 273 | 0.9 | 572.3 | 34.5 | 110.3 | 27.5-37.4 |
| door +x-y (x wall) 0 | 1.20 | 724 | 1282 | 0.9 | 553.8 | 65.5 | 120.4 | 103.0-113.0 |
| door +x-y (x wall) 1 | 1.20 | 704 | 794 | 0.7 | 563.2 | 62.6 | 125.4 | 101.6-111.6 |
| door +x-y (x wall) 2 | 1.20 | 368 | 270 | 1.0 | 577.2 | 31.9 | 110.3 | 51.8-61.7 |
| door +x-y (corner) | 1.20 | 253 | 50 | 0.9 | 569.8 | 22.2 | 115.3 | 0.5-10.5 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 941 | 4.9% | 20.2% |
| -x | avenue | 5.66 | 964 | 5.0% | 20.7% |
| +y | avenue | 5.66 | 954 | 5.0% | 20.5% |
| -y | avenue | 5.66 | 964 | 5.0% | 20.7% |
| door +x+y (y wall) 0 | door | 1.20 | 728 | 3.8% | 73.6% |
| door +x+y (y wall) 1 | door | 1.20 | 701 | 3.6% | 70.9% |
| door +x+y (y wall) 2 | door | 1.20 | 387 | 2.0% | 39.1% |
| door +x+y (x wall) 0 | door | 1.20 | 726 | 3.8% | 73.4% |
| door +x+y (x wall) 1 | door | 1.20 | 689 | 3.6% | 69.7% |
| door +x+y (x wall) 2 | door | 1.20 | 413 | 2.1% | 41.8% |
| door +x+y (corner) | door | 1.20 | 203 | 1.1% | 20.5% |
| door -x+y (y wall) 0 | door | 1.20 | 717 | 3.7% | 72.5% |
| door -x+y (y wall) 1 | door | 1.20 | 716 | 3.7% | 72.4% |
| door -x+y (y wall) 2 | door | 1.20 | 388 | 2.0% | 39.2% |
| door -x+y (x wall) 0 | door | 1.20 | 739 | 3.8% | 74.7% |
| door -x+y (x wall) 1 | door | 1.20 | 707 | 3.7% | 71.5% |
| door -x+y (x wall) 2 | door | 1.20 | 347 | 1.8% | 35.1% |
| door -x+y (corner) | door | 1.20 | 236 | 1.2% | 23.9% |
| door -x-y (y wall) 0 | door | 1.20 | 719 | 3.7% | 72.7% |
| door -x-y (y wall) 1 | door | 1.20 | 708 | 3.7% | 71.6% |
| door -x-y (y wall) 2 | door | 1.20 | 400 | 2.1% | 40.5% |
| door -x-y (x wall) 0 | door | 1.20 | 713 | 3.7% | 72.1% |
| door -x-y (x wall) 1 | door | 1.20 | 708 | 3.7% | 71.6% |
| door -x-y (x wall) 2 | door | 1.20 | 363 | 1.9% | 36.7% |
| door -x-y (corner) | door | 1.20 | 232 | 1.2% | 23.5% |
| door +x-y (y wall) 0 | door | 1.20 | 713 | 3.7% | 72.1% |
| door +x-y (y wall) 1 | door | 1.20 | 704 | 3.7% | 71.2% |
| door +x-y (y wall) 2 | door | 1.20 | 394 | 2.0% | 39.8% |
| door +x-y (x wall) 0 | door | 1.20 | 724 | 3.8% | 73.2% |
| door +x-y (x wall) 1 | door | 1.20 | 704 | 3.7% | 71.2% |
| door +x-y (x wall) 2 | door | 1.20 | 368 | 1.9% | 37.2% |
| door +x-y (corner) | door | 1.20 | 253 | 1.3% | 25.6% |
| **doors (28)** | door | 33.60 | 15400 | 80.1% | |
| **avenues (4)** | avenue | 22.64 | 3823 | 19.9% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 591.4 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 41.5%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 959 | 5.0% | 959 | 5.0% |
| straight +x+y (y wing) 1 | straight | yes | 601 | 3.1% | 598 | 3.1% |
| straight +x+y (y wing) 2 | straight | yes | 290 | 1.5% | 290 | 1.5% |
| straight +x+y (x wing) 0 | straight | yes | 960 | 5.0% | 960 | 5.0% |
| straight +x+y (x wing) 1 | straight | yes | 608 | 3.2% | 601 | 3.1% |
| straight +x+y (x wing) 2 | straight | yes | 303 | 1.6% | 299 | 1.6% |
| corner +x+y | corner | yes | 779 | 4.1% | 261 | 1.4% |
| straight -x+y (y wing) 0 | straight | yes | 964 | 5.0% | 964 | 5.0% |
| straight -x+y (y wing) 1 | straight | yes | 605 | 3.1% | 600 | 3.1% |
| straight -x+y (y wing) 2 | straight | yes | 290 | 1.5% | 290 | 1.5% |
| straight -x+y (x wing) 0 | straight | yes | 969 | 5.0% | 969 | 5.0% |
| straight -x+y (x wing) 1 | straight | yes | 598 | 3.1% | 590 | 3.1% |
| straight -x+y (x wing) 2 | straight | yes | 279 | 1.5% | 275 | 1.4% |
| corner -x+y | corner | yes | 778 | 4.0% | 278 | 1.4% |
| straight -x-y (y wing) 0 | straight | yes | 945 | 4.9% | 945 | 4.9% |
| straight -x-y (y wing) 1 | straight | yes | 604 | 3.1% | 595 | 3.1% |
| straight -x-y (y wing) 2 | straight | yes | 311 | 1.6% | 306 | 1.6% |
| straight -x-y (x wing) 0 | straight | yes | 958 | 5.0% | 958 | 5.0% |
| straight -x-y (x wing) 1 | straight | yes | 601 | 3.1% | 594 | 3.1% |
| straight -x-y (x wing) 2 | straight | yes | 282 | 1.5% | 280 | 1.5% |
| corner -x-y | corner | yes | 807 | 4.2% | 291 | 1.5% |
| straight +x-y (y wing) 0 | straight | yes | 946 | 4.9% | 946 | 4.9% |
| straight +x-y (y wing) 1 | straight | yes | 612 | 3.2% | 606 | 3.2% |
| straight +x-y (y wing) 2 | straight | yes | 308 | 1.6% | 305 | 1.6% |
| straight +x-y (x wing) 0 | straight | yes | 951 | 4.9% | 951 | 4.9% |
| straight +x-y (x wing) 1 | straight | yes | 597 | 3.1% | 590 | 3.1% |
| straight +x-y (x wing) 2 | straight | yes | 277 | 1.4% | 277 | 1.4% |
| corner +x-y | corner | yes | 791 | 4.1% | 290 | 1.5% |
| **straight (24)** | | | 14818 | | 14748 | 76.7% |
| **corner (4)** | | | 3155 | | 1120 | 5.8% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 3355, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 941 | 29.0 | 532.4 | 0.24 | 0.69 | 0.0% |
| -x | 964 | 29.0 | 539.2 | 0.24 | 0.71 | 0.0% |
| +y | 954 | 29.0 | 532.6 | 0.24 | 0.70 | 0.0% |
| -y | 964 | 29.0 | 527.0 | 0.25 | 0.75 | 0.0% |
| door +x+y (y wall) 0 | 728 | 0.9 | 544.8 | 0.80 | 1.50 | 41.8% |
| door +x+y (y wall) 1 | 701 | 1.0 | 567.9 | 0.74 | 1.44 | 38.6% |
| door +x+y (y wall) 2 | 387 | 0.7 | 583.7 | 0.40 | 1.38 | 15.3% |
| door +x+y (x wall) 0 | 726 | 0.9 | 531.5 | 0.82 | 1.50 | 44.4% |
| door +x+y (x wall) 1 | 689 | 1.0 | 553.1 | 0.75 | 1.50 | 41.1% |
| door +x+y (x wall) 2 | 413 | 1.0 | 584.4 | 0.42 | 1.32 | 15.3% |
| door +x+y (corner) | 203 | 0.7 | 578.4 | 0.21 | 1.38 | 11.9% |
| door -x+y (y wall) 0 | 717 | 0.9 | 534.3 | 0.80 | 1.50 | 42.6% |
| door -x+y (y wall) 1 | 716 | 1.0 | 546.1 | 0.79 | 1.44 | 38.2% |
| door -x+y (y wall) 2 | 388 | 0.9 | 591.4 | 0.39 | 1.32 | 16.7% |
| door -x+y (x wall) 0 | 739 | 1.0 | 547.5 | 0.81 | 1.44 | 50.9% |
| door -x+y (x wall) 1 | 707 | 1.0 | 538.2 | 0.79 | 1.56 | 37.0% |
| door -x+y (x wall) 2 | 347 | 0.9 | 583.3 | 0.36 | 1.26 | 15.3% |
| door -x+y (corner) | 236 | 0.9 | 584.0 | 0.24 | 1.38 | 10.2% |
| door -x-y (y wall) 0 | 719 | 1.2 | 554.5 | 0.78 | 1.62 | 39.3% |
| door -x-y (y wall) 1 | 708 | 0.9 | 553.6 | 0.77 | 1.44 | 39.3% |
| door -x-y (y wall) 2 | 400 | 0.9 | 573.3 | 0.42 | 1.20 | 17.2% |
| door -x-y (x wall) 0 | 713 | 0.9 | 539.1 | 0.79 | 1.38 | 45.5% |
| door -x-y (x wall) 1 | 708 | 0.9 | 552.0 | 0.77 | 1.44 | 41.1% |
| door -x-y (x wall) 2 | 363 | 0.9 | 585.9 | 0.37 | 1.44 | 15.3% |
| door -x-y (corner) | 232 | 0.9 | 561.6 | 0.25 | 1.38 | 10.5% |
| door +x-y (y wall) 0 | 713 | 1.0 | 540.5 | 0.79 | 1.44 | 43.6% |
| door +x-y (y wall) 1 | 704 | 1.2 | 543.8 | 0.78 | 1.38 | 38.2% |
| door +x-y (y wall) 2 | 394 | 0.9 | 572.3 | 0.41 | 1.32 | 13.8% |
| door +x-y (x wall) 0 | 724 | 0.9 | 553.8 | 0.78 | 1.44 | 39.3% |
| door +x-y (x wall) 1 | 704 | 0.7 | 563.2 | 0.75 | 1.50 | 35.1% |
| door +x-y (x wall) 2 | 368 | 1.0 | 577.2 | 0.38 | 1.32 | 15.5% |
| door +x-y (corner) | 253 | 0.9 | 569.8 | 0.27 | 1.38 | 12.1% |

Mean flow / w J averaged over the doors 0.59, over the avenues 0.24.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 959 | 617 / 343 / 207 | 0.3 | 541.9 | 2.15 | 3.91 | 82% | 82% | 0% | 4.28 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 562 | 598 / 0 / 8 | 0.7 | 564.9 | 1.07 | 1.50 | 79% | 70% | 9% | 3.83 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 74 | 290 / 0 / 0 | 0.7 | 580.7 | 0.50 | 1.20 | 17% | 14% | 3% | 2.99 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 960 | 607 / 353 / 228 | 0.5 | 528.6 | 2.25 | 3.51 | 89% | 81% | 7% | 4.01 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 564 | 601 / 0 / 9 | 0.7 | 550.1 | 1.11 | 1.60 | 84% | 73% | 11% | 3.67 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 80 | 299 / 0 / 4 | 0.7 | 581.4 | 0.52 | 1.20 | 17% | 12% | 5% | 2.86 |
| corner +x+y | 1.20 | 85.6 | 769 | 152 / 109 / 529 | 0.7 | 575.4 | 1.37 | 3.31 | 86% | 57% | 29% | 2.41 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 964 | 604 / 360 / 253 | 0.3 | 531.4 | 2.29 | 3.81 | 83% | 81% | 2% | 4.23 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 559 | 600 / 0 / 6 | 0.7 | 543.1 | 1.12 | 1.50 | 84% | 71% | 13% | 3.69 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 77 | 290 / 0 / 0 | 0.7 | 588.4 | 0.49 | 1.10 | 17% | 13% | 3% | 2.99 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 969 | 628 / 341 / 171 | 0.5 | 544.7 | 2.09 | 3.31 | 85% | 82% | 4% | 4.20 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 550 | 590 / 0 / 12 | 0.7 | 535.2 | 1.13 | 1.50 | 81% | 70% | 11% | 3.80 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 79 | 275 / 0 / 5 | 0.7 | 580.3 | 0.48 | 1.40 | 15% | 15% | 0% | 3.32 |
| corner -x+y | 1.20 | 85.6 | 768 | 171 / 107 / 513 | 0.7 | 582.3 | 1.36 | 3.21 | 83% | 54% | 29% | 2.46 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 945 | 606 / 339 / 200 | 0.2 | 551.5 | 2.08 | 3.61 | 91% | 79% | 12% | 3.84 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 562 | 595 / 0 / 13 | 0.7 | 550.6 | 1.11 | 1.50 | 84% | 70% | 14% | 3.66 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 77 | 306 / 0 / 7 | 0.3 | 570.4 | 0.55 | 1.40 | 17% | 14% | 3% | 3.15 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 958 | 604 / 354 / 210 | 0.2 | 536.1 | 2.18 | 3.31 | 91% | 80% | 11% | 3.96 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 554 | 594 / 0 / 9 | 0.7 | 549.0 | 1.10 | 1.50 | 82% | 68% | 14% | 3.71 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 77 | 280 / 0 / 2 | 0.7 | 583.0 | 0.48 | 1.30 | 15% | 14% | 2% | 3.18 |
| corner -x-y | 1.20 | 85.6 | 796 | 174 / 117 / 536 | 0.7 | 577.0 | 1.43 | 4.21 | 86% | 57% | 29% | 2.48 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 946 | 596 / 350 / 222 | 0.5 | 537.5 | 2.17 | 3.81 | 93% | 81% | 11% | 3.90 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 572 | 606 / 0 / 8 | 0.7 | 540.8 | 1.14 | 1.50 | 85% | 73% | 13% | 3.70 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 78 | 305 / 0 / 4 | 0.7 | 569.3 | 0.54 | 1.40 | 17% | 14% | 3% | 2.90 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 951 | 602 / 350 / 216 | 0.5 | 550.8 | 2.12 | 3.71 | 80% | 79% | 2% | 4.23 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 559 | 590 / 0 / 12 | 0.7 | 560.2 | 1.08 | 1.50 | 81% | 68% | 12% | 3.71 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 78 | 277 / 0 / 0 | 0.7 | 574.2 | 0.48 | 1.20 | 17% | 12% | 5% | 2.73 |
| corner +x-y | 1.20 | 85.6 | 781 | 187 / 103 / 515 | 0.7 | 568.1 | 1.42 | 3.61 | 86% | 54% | 32% | 2.40 |

The last agent out (agent 6426, t100 591.4 s): last gangway straight -x+y (y wing) 2, exit door -x+y (y wall) 2. The gangway that cleared last: straight -x+y (y wing) 2 at 588.4 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.79 | 583.7 / 572.1 / 546.9 | 568.4 / 532.9 / 451.8 | 853266.3 | 1933089 | 0.199 |
| gangway | 1212 | 1112.9 | 6.79 | 583.0 / 565.6 / 496.0 | 568.4 / 532.9 / 451.8 | 820304.1 | 1613297 | 0.099 |
| walkway | 276 | 257.4 | 5.41 | 229.7 / 177.4 / 43.4 | 198.9 / 166.5 / 26.9 | 343.9 | 47763 | 0.528 |
| avenue | 912 | 858.9 | 2.53 | 255.5 / 15.4 / 0.0 | 200.3 / 1.9 / 0.0 | 0.0 | 109747 | 1.327 |
| exit | 32 | 3.2 | 0.00 | 565.5 / 562.2 / 518.1 | 322.0 / 297.2 / 184.0 | 1230.9 | 2192 | 1.195 |
| concourse | 1116 | 1043.8 | 6.03 | 528.4 / 146.2 / 82.6 | 209.5 / 114.4 / 56.3 | 31387.4 | 160089 | 0.323 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.63 | 512.8 / 503.7 / 499.0 | 505.1 / 503.7 / 495.3 | 909848.8 | 2443320 | 0.037 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 26.5 | 28.5 | gangway | 1.00 | 6.09 | 504.3 | 495.2 | 436.9 | 2538.9 | 0.017 |
| 2 | -26.5 | -28.5 | gangway | 1.00 | 6.31 | 512.0 | 497.1 | 426.4 | 2514.7 | 0.021 |
| 3 | 27.5 | 27.5 | gangway | 1.00 | 6.00 | 505.0 | 501.1 | 423.1 | 2442.9 | 0.015 |
| 4 | -26.5 | -29.5 | gangway | 1.00 | 6.33 | 501.3 | 463.3 | 413.0 | 2442.9 | 0.020 |
| 5 | 29.5 | 26.5 | gangway | 1.00 | 6.07 | 504.3 | 473.1 | 422.6 | 2440.1 | 0.022 |
| 6 | -26.5 | 28.5 | gangway | 1.00 | 5.82 | 495.5 | 486.2 | 426.6 | 2434.8 | 0.017 |
| 7 | 28.5 | 26.5 | gangway | 1.00 | 5.97 | 514.6 | 505.7 | 425.2 | 2432.3 | 0.019 |
| 8 | -27.5 | 28.5 | gangway | 1.00 | 6.01 | 503.6 | 498.1 | 419.4 | 2393.8 | 0.017 |
| 9 | -28.5 | -26.5 | gangway | 1.00 | 6.12 | 510.0 | 496.7 | 407.0 | 2386.4 | 0.020 |
| 10 | 26.5 | 27.5 | gangway | 1.00 | 5.87 | 503.7 | 495.9 | 426.9 | 2384.3 | 0.016 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -24.5 | -26.5 | seat row | 0.50 | 7.09 | 503.9 | 503.2 | 495.3 | 1658.3 | 0.015 |
| 2 | -25.5 | -30.5 | seat row | 0.64 | 6.67 | 461.9 | 452.3 | 413.3 | 1658.3 | 0.025 |
| 3 | 25.5 | -30.5 | seat row | 0.64 | 6.66 | 453.4 | 442.5 | 402.1 | 1615.0 | 0.024 |
| 4 | -26.5 | -24.5 | seat row | 0.50 | 7.14 | 503.0 | 500.1 | 478.7 | 1613.1 | 0.016 |
| 5 | 25.5 | 30.5 | seat row | 0.64 | 6.58 | 454.8 | 447.6 | 400.9 | 1610.9 | 0.024 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1711; agent-steps of seated agents on another row's clearway: 22070.

## Deposit check

Person-seconds deposited: 4382269.2, of them in excluded cells: 5860.181.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 505579 overlapping pair-steps: p99 0.0028, max 0.0542 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0028 max 0.0542; venue-geometry 6: p99 0.0006 max 0.0006 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00751 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 22 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.33 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 547 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
