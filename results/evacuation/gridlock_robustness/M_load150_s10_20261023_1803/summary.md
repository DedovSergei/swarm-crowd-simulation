# Experiment `M_load150_s10`

**Task 5.11 stage 1 (gridlock robustness, default model, AMD 26.10.1): venue M, the achievable maximum 121.42% (150% requested, seed 10)**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 19223 agents (load 121.4%, requested 150%): every one of the 15832 seats and 3391 standing (spawnOvercrowdedCrowd, seed 10; below), buffer N = 32768, 3333 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 1456662 evaluations, 59527 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.21)** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `15aa31e8667e4a9417fde7884d907d1832c5e2d6`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-23T18:03:49, 91.2 s wall.

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
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 4.04, all circulation cells 4.04 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 10, 108403 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1185 | 207.3 |
| t90 | 2600 | 454.8 |
| t100 | 3333 | 583.0 |

t_p: the step by which ceil(p x 19223) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 960 | 88 | 29.0 | 527.5 | 20.4 | 64.9 | 28.9-38.8 |
| -x | 5.66 | 959 | 88 | 29.0 | 526.8 | 20.4 | 60.6 | 28.7-38.7 |
| +y | 5.66 | 940 | 83 | 29.0 | 531.0 | 19.8 | 55.3 | 28.3-38.3 |
| -y | 5.66 | 966 | 82 | 29.0 | 534.9 | 20.2 | 60.6 | 28.5-38.5 |
| door +x+y (y wall) 0 | 1.20 | 725 | 1272 | 0.7 | 539.2 | 67.3 | 120.4 | 95.8-105.8 |
| door +x+y (y wall) 1 | 1.20 | 695 | 796 | 0.9 | 551.3 | 63.1 | 120.4 | 107.2-117.2 |
| door +x+y (y wall) 2 | 1.20 | 394 | 279 | 1.0 | 564.9 | 34.9 | 105.3 | 52.5-62.4 |
| door +x+y (x wall) 0 | 1.20 | 724 | 1271 | 0.7 | 540.8 | 67.0 | 130.4 | 98.1-108.1 |
| door +x+y (x wall) 1 | 1.20 | 696 | 806 | 1.0 | 546.6 | 63.8 | 115.3 | 108.6-118.6 |
| door +x+y (x wall) 2 | 1.20 | 382 | 269 | 0.7 | 553.2 | 34.6 | 120.4 | 79.1-89.0 |
| door +x+y (corner) | 1.20 | 258 | 49 | 0.9 | 569.3 | 22.7 | 110.3 | 1.6-11.5 |
| door -x+y (y wall) 0 | 1.20 | 714 | 1277 | 0.9 | 522.8 | 68.4 | 115.3 | 101.8-111.8 |
| door -x+y (y wall) 1 | 1.20 | 694 | 798 | 0.7 | 544.8 | 63.8 | 120.4 | 105.8-115.8 |
| door -x+y (y wall) 2 | 1.20 | 378 | 266 | 0.7 | 565.5 | 33.5 | 100.3 | 24.3-34.3 |
| door -x+y (x wall) 0 | 1.20 | 718 | 1265 | 1.0 | 532.9 | 67.5 | 120.4 | 87.8-97.8 |
| door -x+y (x wall) 1 | 1.20 | 701 | 796 | 1.0 | 534.5 | 65.7 | 120.4 | 104.1-114.0 |
| door -x+y (x wall) 2 | 1.20 | 394 | 269 | 1.0 | 553.1 | 35.7 | 105.3 | 46.0-56.0 |
| door -x+y (corner) | 1.20 | 255 | 44 | 0.9 | 563.5 | 22.7 | 115.3 | 5.2-15.2 |
| door -x-y (y wall) 0 | 1.20 | 727 | 1273 | 0.9 | 558.0 | 65.2 | 125.4 | 100.6-110.5 |
| door -x-y (y wall) 1 | 1.20 | 702 | 801 | 0.7 | 536.6 | 65.5 | 130.4 | 102.0-111.9 |
| door -x-y (y wall) 2 | 1.20 | 377 | 265 | 0.9 | 581.7 | 32.4 | 105.3 | 6.3-16.3 |
| door -x-y (x wall) 0 | 1.20 | 719 | 1276 | 0.9 | 535.4 | 67.2 | 130.4 | 112.8-122.8 |
| door -x-y (x wall) 1 | 1.20 | 681 | 802 | 0.9 | 542.6 | 62.8 | 125.4 | 104.2-114.2 |
| door -x-y (x wall) 2 | 1.20 | 388 | 265 | 1.0 | 583.0 | 33.3 | 105.3 | 81.5-91.5 |
| door -x-y (corner) | 1.20 | 252 | 46 | 1.0 | 581.2 | 21.7 | 120.4 | 75.9-85.9 |
| door +x-y (y wall) 0 | 1.20 | 716 | 1270 | 1.2 | 533.8 | 67.2 | 120.4 | 105.6-115.6 |
| door +x-y (y wall) 1 | 1.20 | 700 | 792 | 0.9 | 531.0 | 66.0 | 130.4 | 98.8-108.8 |
| door +x-y (y wall) 2 | 1.20 | 388 | 267 | 1.2 | 581.0 | 33.4 | 105.3 | 41.6-51.6 |
| door +x-y (x wall) 0 | 1.20 | 715 | 1263 | 1.0 | 525.9 | 68.1 | 130.4 | 105.3-115.3 |
| door +x-y (x wall) 1 | 1.20 | 711 | 797 | 0.9 | 535.0 | 66.5 | 120.4 | 101.3-111.2 |
| door +x-y (x wall) 2 | 1.20 | 374 | 265 | 1.0 | 577.5 | 32.4 | 115.3 | 84.5-94.4 |
| door +x-y (corner) | 1.20 | 220 | 43 | 0.9 | 560.6 | 19.6 | 105.3 | 0.5-10.5 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 960 | 5.0% | 20.9% |
| -x | avenue | 5.66 | 959 | 5.0% | 20.9% |
| +y | avenue | 5.66 | 940 | 4.9% | 20.4% |
| -y | avenue | 5.66 | 966 | 5.0% | 21.0% |
| door +x+y (y wall) 0 | door | 1.20 | 725 | 3.8% | 74.4% |
| door +x+y (y wall) 1 | door | 1.20 | 695 | 3.6% | 71.3% |
| door +x+y (y wall) 2 | door | 1.20 | 394 | 2.0% | 40.4% |
| door +x+y (x wall) 0 | door | 1.20 | 724 | 3.8% | 74.3% |
| door +x+y (x wall) 1 | door | 1.20 | 696 | 3.6% | 71.4% |
| door +x+y (x wall) 2 | door | 1.20 | 382 | 2.0% | 39.2% |
| door +x+y (corner) | door | 1.20 | 258 | 1.3% | 26.5% |
| door -x+y (y wall) 0 | door | 1.20 | 714 | 3.7% | 73.3% |
| door -x+y (y wall) 1 | door | 1.20 | 694 | 3.6% | 71.2% |
| door -x+y (y wall) 2 | door | 1.20 | 378 | 2.0% | 38.8% |
| door -x+y (x wall) 0 | door | 1.20 | 718 | 3.7% | 73.7% |
| door -x+y (x wall) 1 | door | 1.20 | 701 | 3.6% | 71.9% |
| door -x+y (x wall) 2 | door | 1.20 | 394 | 2.0% | 40.4% |
| door -x+y (corner) | door | 1.20 | 255 | 1.3% | 26.2% |
| door -x-y (y wall) 0 | door | 1.20 | 727 | 3.8% | 74.6% |
| door -x-y (y wall) 1 | door | 1.20 | 702 | 3.7% | 72.0% |
| door -x-y (y wall) 2 | door | 1.20 | 377 | 2.0% | 38.7% |
| door -x-y (x wall) 0 | door | 1.20 | 719 | 3.7% | 73.8% |
| door -x-y (x wall) 1 | door | 1.20 | 681 | 3.5% | 69.9% |
| door -x-y (x wall) 2 | door | 1.20 | 388 | 2.0% | 39.8% |
| door -x-y (corner) | door | 1.20 | 252 | 1.3% | 25.9% |
| door +x-y (y wall) 0 | door | 1.20 | 716 | 3.7% | 73.5% |
| door +x-y (y wall) 1 | door | 1.20 | 700 | 3.6% | 71.8% |
| door +x-y (y wall) 2 | door | 1.20 | 388 | 2.0% | 39.8% |
| door +x-y (x wall) 0 | door | 1.20 | 715 | 3.7% | 73.4% |
| door +x-y (x wall) 1 | door | 1.20 | 711 | 3.7% | 72.9% |
| door +x-y (x wall) 2 | door | 1.20 | 374 | 1.9% | 38.4% |
| door +x-y (corner) | door | 1.20 | 220 | 1.1% | 22.6% |
| **doors (28)** | door | 33.60 | 15398 | 80.1% | |
| **avenues (4)** | avenue | 22.64 | 3825 | 19.9% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 583.0 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 42.1%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 956 | 5.0% | 956 | 5.0% |
| straight +x+y (y wing) 1 | straight | yes | 591 | 3.1% | 581 | 3.0% |
| straight +x+y (y wing) 2 | straight | yes | 307 | 1.6% | 303 | 1.6% |
| straight +x+y (x wing) 0 | straight | yes | 968 | 5.0% | 968 | 5.0% |
| straight +x+y (x wing) 1 | straight | yes | 582 | 3.0% | 574 | 3.0% |
| straight +x+y (x wing) 2 | straight | yes | 287 | 1.5% | 287 | 1.5% |
| corner +x+y | corner | yes | 798 | 4.2% | 299 | 1.6% |
| straight -x+y (y wing) 0 | straight | yes | 950 | 4.9% | 950 | 4.9% |
| straight -x+y (y wing) 1 | straight | yes | 592 | 3.1% | 579 | 3.0% |
| straight -x+y (y wing) 2 | straight | yes | 294 | 1.5% | 290 | 1.5% |
| straight -x+y (x wing) 0 | straight | yes | 941 | 4.9% | 941 | 4.9% |
| straight -x+y (x wing) 1 | straight | yes | 597 | 3.1% | 585 | 3.0% |
| straight -x+y (x wing) 2 | straight | yes | 308 | 1.6% | 306 | 1.6% |
| corner -x+y | corner | yes | 813 | 4.2% | 318 | 1.7% |
| straight -x-y (y wing) 0 | straight | yes | 951 | 4.9% | 951 | 4.9% |
| straight -x-y (y wing) 1 | straight | yes | 591 | 3.1% | 582 | 3.0% |
| straight -x-y (y wing) 2 | straight | yes | 294 | 1.5% | 292 | 1.5% |
| straight -x-y (x wing) 0 | straight | yes | 962 | 5.0% | 962 | 5.0% |
| straight -x-y (x wing) 1 | straight | yes | 585 | 3.0% | 576 | 3.0% |
| straight -x-y (x wing) 2 | straight | yes | 292 | 1.5% | 289 | 1.5% |
| corner -x-y | corner | yes | 797 | 4.1% | 316 | 1.6% |
| straight +x-y (y wing) 0 | straight | yes | 947 | 4.9% | 947 | 4.9% |
| straight +x-y (y wing) 1 | straight | yes | 596 | 3.1% | 588 | 3.1% |
| straight +x-y (y wing) 2 | straight | yes | 324 | 1.7% | 317 | 1.6% |
| straight +x-y (x wing) 0 | straight | yes | 955 | 5.0% | 955 | 5.0% |
| straight +x-y (x wing) 1 | straight | yes | 600 | 3.1% | 594 | 3.1% |
| straight +x-y (x wing) 2 | straight | yes | 286 | 1.5% | 286 | 1.5% |
| corner +x-y | corner | yes | 809 | 4.2% | 282 | 1.5% |
| **straight (24)** | | | 14756 | | 14659 | 76.3% |
| **corner (4)** | | | 3217 | | 1215 | 6.3% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 3349, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 960 | 29.0 | 527.5 | 0.24 | 0.78 | 0.0% |
| -x | 959 | 29.0 | 526.8 | 0.24 | 0.72 | 0.0% |
| +y | 940 | 29.0 | 531.0 | 0.24 | 0.66 | 0.0% |
| -y | 966 | 29.0 | 534.9 | 0.24 | 0.72 | 0.0% |
| door +x+y (y wall) 0 | 725 | 0.7 | 539.2 | 0.80 | 1.44 | 45.5% |
| door +x+y (y wall) 1 | 695 | 0.9 | 551.3 | 0.75 | 1.44 | 37.5% |
| door +x+y (y wall) 2 | 394 | 1.0 | 564.9 | 0.42 | 1.26 | 17.5% |
| door +x+y (x wall) 0 | 724 | 0.7 | 540.8 | 0.80 | 1.56 | 47.3% |
| door +x+y (x wall) 1 | 696 | 1.0 | 546.6 | 0.76 | 1.38 | 36.4% |
| door +x+y (x wall) 2 | 382 | 0.7 | 553.2 | 0.41 | 1.44 | 16.1% |
| door +x+y (corner) | 258 | 0.9 | 569.3 | 0.27 | 1.32 | 10.3% |
| door -x+y (y wall) 0 | 714 | 0.9 | 522.8 | 0.82 | 1.38 | 52.8% |
| door -x+y (y wall) 1 | 694 | 0.7 | 544.8 | 0.76 | 1.44 | 38.2% |
| door -x+y (y wall) 2 | 378 | 0.7 | 565.5 | 0.40 | 1.20 | 15.8% |
| door -x+y (x wall) 0 | 718 | 1.0 | 532.9 | 0.81 | 1.44 | 50.0% |
| door -x+y (x wall) 1 | 701 | 1.0 | 534.5 | 0.79 | 1.44 | 35.2% |
| door -x+y (x wall) 2 | 394 | 1.0 | 553.1 | 0.43 | 1.26 | 16.1% |
| door -x+y (corner) | 255 | 0.9 | 563.5 | 0.27 | 1.38 | 10.5% |
| door -x-y (y wall) 0 | 727 | 0.9 | 558.0 | 0.78 | 1.50 | 44.6% |
| door -x-y (y wall) 1 | 702 | 0.7 | 536.6 | 0.78 | 1.56 | 33.3% |
| door -x-y (y wall) 2 | 377 | 0.9 | 581.7 | 0.39 | 1.26 | 15.3% |
| door -x-y (x wall) 0 | 719 | 0.9 | 535.4 | 0.80 | 1.56 | 46.3% |
| door -x-y (x wall) 1 | 681 | 0.9 | 542.6 | 0.75 | 1.50 | 40.0% |
| door -x-y (x wall) 2 | 388 | 1.0 | 583.0 | 0.40 | 1.26 | 15.3% |
| door -x-y (corner) | 252 | 1.0 | 581.2 | 0.26 | 1.44 | 10.2% |
| door +x-y (y wall) 0 | 716 | 1.2 | 533.8 | 0.80 | 1.44 | 40.7% |
| door +x-y (y wall) 1 | 700 | 0.9 | 531.0 | 0.79 | 1.56 | 40.7% |
| door +x-y (y wall) 2 | 388 | 1.2 | 581.0 | 0.40 | 1.26 | 11.9% |
| door +x-y (x wall) 0 | 715 | 1.0 | 525.9 | 0.81 | 1.56 | 47.2% |
| door +x-y (x wall) 1 | 711 | 0.9 | 535.0 | 0.80 | 1.44 | 38.9% |
| door +x-y (x wall) 2 | 374 | 1.0 | 577.5 | 0.39 | 1.38 | 17.2% |
| door +x-y (corner) | 220 | 0.9 | 560.6 | 0.24 | 1.26 | 8.8% |

Mean flow / w J averaged over the doors 0.60, over the avenues 0.24.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 956 | 611 / 345 / 193 | 0.3 | 536.3 | 2.14 | 3.91 | 83% | 83% | 0% | 4.23 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 558 | 581 / 0 / 11 | 0.7 | 548.3 | 1.08 | 1.50 | 84% | 71% | 13% | 3.75 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 77 | 303 / 0 / 5 | 0.7 | 562.0 | 0.55 | 1.40 | 18% | 18% | 0% | 3.09 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 968 | 613 / 355 / 244 | 0.5 | 537.8 | 2.25 | 3.81 | 83% | 81% | 2% | 4.29 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 544 | 575 / 0 / 13 | 0.7 | 543.6 | 1.08 | 1.50 | 84% | 71% | 13% | 3.69 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 79 | 287 / 0 / 0 | 0.7 | 550.3 | 0.52 | 1.30 | 18% | 14% | 4% | 2.91 |
| corner +x+y | 1.20 | 85.6 | 786 | 197 / 102 / 516 | 0.7 | 565.5 | 1.44 | 3.11 | 88% | 56% | 32% | 2.35 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 950 | 595 / 356 / 250 | 0.7 | 519.8 | 2.31 | 3.81 | 83% | 81% | 2% | 4.22 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 562 | 579 / 0 / 14 | 0.7 | 541.9 | 1.10 | 1.60 | 85% | 69% | 16% | 3.65 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 74 | 290 / 0 / 4 | 0.7 | 562.5 | 0.52 | 1.20 | 16% | 12% | 4% | 3.13 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 941 | 608 / 334 / 176 | 0.7 | 530.0 | 2.11 | 3.41 | 83% | 80% | 4% | 4.30 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 570 | 585 / 0 / 17 | 0.7 | 531.5 | 1.13 | 1.60 | 87% | 72% | 15% | 3.64 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 78 | 306 / 0 / 2 | 0.7 | 550.1 | 0.56 | 1.30 | 18% | 12% | 5% | 3.01 |
| corner -x+y | 1.20 | 85.6 | 794 | 205 / 113 / 512 | 0.7 | 559.7 | 1.48 | 3.01 | 84% | 53% | 32% | 2.41 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 951 | 608 / 344 / 176 | 0.3 | 555.0 | 2.03 | 3.81 | 82% | 80% | 2% | 4.30 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 559 | 583 / 0 / 13 | 0.7 | 533.6 | 1.12 | 1.50 | 87% | 72% | 15% | 3.62 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 81 | 293 / 0 / 2 | 0.7 | 578.8 | 0.51 | 1.40 | 17% | 12% | 5% | 2.84 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 962 | 603 / 359 / 241 | 0.3 | 532.4 | 2.26 | 4.21 | 83% | 81% | 2% | 4.24 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 555 | 576 / 0 / 12 | 0.7 | 539.6 | 1.09 | 1.50 | 84% | 73% | 11% | 3.88 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 77 | 289 / 0 / 3 | 0.7 | 580.0 | 0.50 | 1.30 | 17% | 14% | 3% | 2.90 |
| corner -x-y | 1.20 | 85.6 | 783 | 198 / 118 / 497 | 0.7 | 577.4 | 1.41 | 3.41 | 84% | 48% | 36% | 2.36 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 947 | 604 / 343 / 193 | 0.2 | 530.8 | 2.15 | 3.71 | 91% | 81% | 9% | 3.96 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 555 | 588 / 0 / 8 | 0.7 | 528.0 | 1.13 | 1.60 | 87% | 70% | 17% | 3.64 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 81 | 317 / 0 / 10 | 0.7 | 578.1 | 0.57 | 1.30 | 16% | 12% | 3% | 2.82 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 955 | 610 / 345 / 214 | 0.5 | 523.0 | 2.24 | 3.41 | 83% | 83% | 0% | 4.26 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 558 | 594 / 0 / 11 | 0.7 | 532.1 | 1.14 | 1.50 | 85% | 69% | 17% | 3.66 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 76 | 286 / 0 / 0 | 0.7 | 574.6 | 0.50 | 1.20 | 17% | 16% | 2% | 3.14 |
| corner +x-y | 1.20 | 85.6 | 797 | 160 / 122 / 544 | 0.7 | 572.1 | 1.45 | 3.21 | 84% | 52% | 33% | 2.40 |

The last agent out (agent 10381, t100 583.0 s): last gangway straight -x-y (x wing) 2, exit door -x-y (x wall) 2. The gangway that cleared last: straight -x-y (x wing) 2 at 580.0 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.87 | 578.8 / 566.3 / 534.7 | 559.9 / 521.9 / 423.6 | 854541.9 | 1918941 | 0.202 |
| gangway | 1212 | 1112.9 | 6.87 | 575.6 / 562.2 / 473.6 | 559.9 / 521.9 / 423.6 | 821122.5 | 1598143 | 0.101 |
| walkway | 276 | 257.4 | 5.42 | 231.2 / 180.0 / 22.4 | 203.8 / 140.6 / 14.3 | 196.1 | 47376 | 0.533 |
| avenue | 912 | 858.9 | 2.48 | 253.1 / 29.7 / 0.0 | 205.9 / 1.4 / 0.0 | 0.0 | 109817 | 1.326 |
| exit | 32 | 3.2 | 0.00 | 558.1 / 555.2 / 509.3 | 319.0 / 293.5 / 177.2 | 1225.7 | 2196 | 1.193 |
| concourse | 1116 | 1043.8 | 6.07 | 523.1 / 117.2 / 79.8 | 206.0 / 115.6 / 56.8 | 31997.6 | 161409 | 0.318 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.57 | 506.9 / 492.2 / 470.7 | 503.4 / 491.7 / 467.0 | 902566.8 | 2433282 | 0.037 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -29.5 | -26.5 | gangway | 1.00 | 6.23 | 497.3 | 461.4 | 410.9 | 2455.2 | 0.016 |
| 2 | 29.5 | -26.5 | gangway | 1.00 | 6.32 | 495.0 | 469.6 | 403.0 | 2406.7 | 0.021 |
| 3 | 26.5 | 29.5 | gangway | 1.00 | 6.04 | 499.4 | 472.4 | 410.3 | 2389.1 | 0.019 |
| 4 | -26.5 | 29.5 | gangway | 1.00 | 6.18 | 480.3 | 464.2 | 399.3 | 2376.4 | 0.018 |
| 5 | -29.5 | 26.5 | gangway | 1.00 | 6.08 | 495.9 | 467.2 | 415.2 | 2358.7 | 0.018 |
| 6 | 29.5 | 26.5 | gangway | 1.00 | 6.11 | 510.2 | 474.0 | 406.0 | 2352.5 | 0.020 |
| 7 | -26.5 | -29.5 | gangway | 1.00 | 5.99 | 491.7 | 453.0 | 407.5 | 2330.8 | 0.019 |
| 8 | 28.5 | -26.5 | gangway | 1.00 | 5.87 | 495.5 | 481.9 | 407.4 | 2307.4 | 0.021 |
| 9 | 26.5 | 28.5 | gangway | 1.00 | 6.06 | 497.4 | 492.9 | 394.8 | 2289.2 | 0.019 |
| 10 | 26.5 | -28.5 | gangway | 1.00 | 5.90 | 492.9 | 475.6 | 394.9 | 2271.2 | 0.017 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -30.5 | 25.5 | seat row | 0.64 | 6.68 | 467.4 | 461.8 | 407.5 | 1638.1 | 0.023 |
| 2 | -25.5 | 30.5 | seat row | 0.64 | 6.74 | 445.8 | 424.7 | 395.6 | 1625.3 | 0.023 |
| 3 | -25.5 | -30.5 | seat row | 0.64 | 6.65 | 456.3 | 443.6 | 398.8 | 1620.9 | 0.024 |
| 4 | -30.5 | -25.5 | seat row | 0.64 | 6.55 | 457.9 | 437.3 | 411.6 | 1607.9 | 0.024 |
| 5 | 30.5 | -25.5 | seat row | 0.64 | 6.64 | 458.1 | 452.7 | 399.7 | 1597.6 | 0.024 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1691; agent-steps of seated agents on another row's clearway: 20758.

## Deposit check

Person-seconds deposited: 4358095.5, of them in excluded cells: 5872.902.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 494543 overlapping pair-steps: p99 0.0028, max 0.0276 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0028 max 0.0276; venue-geometry 9: p99 0.0007 max 0.0007 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 22 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.32 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 524 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
