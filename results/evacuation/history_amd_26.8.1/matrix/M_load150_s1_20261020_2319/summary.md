# Experiment `M_load150_s1`

**Task 5.9 stage 4: venue M, 150% requested (seed 1): every seat + standing on the walkway and concourse (M, L: the achievable maximum, also the 125% request)**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 19223 agents (load 121.4%, requested 150%): every one of the 15832 seats and 3391 standing (spawnOvercrowdedCrowd, seed 1; below), buffer N = 32768, 3351 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 1463884 evaluations, 58766 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.21)** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-20T23:19:23, 89.9 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Spawn (overcrowding)

| | |
|---|---|
| seated | 15832 (every seat) |
| standing | **3391** (requested round((1.50 - 1) x 15832) = 7916; at most 3391 = floor(2.5 p/m^2 x 1356.6 m^2)) |
| standing floor | walkway + rear concourse, 1356.6 m^2 |
| standing on the walkway / concourse / gangways | 619 / 2772 / 0 |
| **load** | **121.42%** of the seats (requested 150%; the floor takes no more: the achievable maximum) |
| standing crowd's mean density | 2.500 p/m^2 |
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 3.71, all circulation cells 3.71 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 1, 109663 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1182 | 206.7 |
| t90 | 2612 | 456.9 |
| t100 | 3351 | 586.1 |

t_p: the step by which ceil(p x 19223) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 966 | 93 | 29.0 | 534.9 | 20.2 | 62.7 | 28.7-38.7 |
| -x | 5.66 | 949 | 89 | 29.0 | 525.8 | 20.2 | 59.5 | 28.7-38.7 |
| +y | 5.66 | 941 | 83 | 29.2 | 530.5 | 19.9 | 61.7 | 28.9-38.8 |
| -y | 5.66 | 951 | 82 | 29.0 | 534.7 | 19.9 | 59.5 | 28.5-38.5 |
| door +x+y (y wall) 0 | 1.20 | 726 | 1267 | 0.7 | 544.0 | 66.8 | 125.4 | 96.9-106.9 |
| door +x+y (y wall) 1 | 1.20 | 720 | 799 | 1.0 | 554.3 | 65.1 | 120.4 | 111.8-121.7 |
| door +x+y (y wall) 2 | 1.20 | 361 | 270 | 1.0 | 586.1 | 30.8 | 115.3 | 79.8-89.7 |
| door +x+y (x wall) 0 | 1.20 | 731 | 1267 | 1.0 | 541.7 | 67.6 | 125.4 | 106.7-116.7 |
| door +x+y (x wall) 1 | 1.20 | 723 | 806 | 1.2 | 554.1 | 65.4 | 125.4 | 110.5-120.5 |
| door +x+y (x wall) 2 | 1.20 | 398 | 271 | 0.9 | 578.2 | 34.5 | 120.4 | 74.2-84.1 |
| door +x+y (corner) | 1.20 | 199 | 47 | 0.7 | 562.8 | 17.7 | 115.3 | 0.5-10.5 |
| door -x+y (y wall) 0 | 1.20 | 727 | 1270 | 0.9 | 520.9 | 69.9 | 120.4 | 94.1-104.1 |
| door -x+y (y wall) 1 | 1.20 | 707 | 797 | 0.9 | 543.4 | 65.1 | 115.3 | 99.0-109.0 |
| door -x+y (y wall) 2 | 1.20 | 427 | 265 | 1.2 | 586.1 | 36.5 | 120.4 | 72.6-82.6 |
| door -x+y (x wall) 0 | 1.20 | 723 | 1275 | 0.9 | 537.1 | 67.4 | 130.4 | 107.4-117.4 |
| door -x+y (x wall) 1 | 1.20 | 717 | 787 | 1.2 | 555.7 | 64.6 | 125.4 | 106.2-116.1 |
| door -x+y (x wall) 2 | 1.20 | 349 | 276 | 0.9 | 573.0 | 30.5 | 115.3 | 79.1-89.0 |
| door -x+y (corner) | 1.20 | 209 | 50 | 0.7 | 584.4 | 17.9 | 110.3 | 10.5-20.5 |
| door -x-y (y wall) 0 | 1.20 | 733 | 1275 | 1.0 | 542.2 | 67.7 | 120.4 | 107.6-117.5 |
| door -x-y (y wall) 1 | 1.20 | 701 | 794 | 0.9 | 538.5 | 65.2 | 120.4 | 98.6-108.6 |
| door -x-y (y wall) 2 | 1.20 | 365 | 277 | 0.9 | 581.0 | 31.4 | 120.4 | 89.6-99.5 |
| door -x-y (x wall) 0 | 1.20 | 721 | 1269 | 0.9 | 539.8 | 66.9 | 120.4 | 98.3-108.3 |
| door -x-y (x wall) 1 | 1.20 | 690 | 792 | 1.6 | 536.8 | 64.4 | 125.4 | 107.0-117.0 |
| door -x-y (x wall) 2 | 1.20 | 412 | 269 | 0.9 | 584.9 | 35.3 | 105.3 | 64.7-74.7 |
| door -x-y (corner) | 1.20 | 231 | 48 | 0.9 | 584.9 | 19.8 | 110.3 | 0.5-10.5 |
| door +x-y (y wall) 0 | 1.20 | 721 | 1272 | 0.9 | 536.4 | 67.3 | 120.4 | 102.7-112.6 |
| door +x-y (y wall) 1 | 1.20 | 696 | 792 | 1.0 | 562.2 | 62.0 | 130.4 | 102.3-112.3 |
| door +x-y (y wall) 2 | 1.20 | 410 | 267 | 0.9 | 579.1 | 35.4 | 115.3 | 71.4-81.3 |
| door +x-y (x wall) 0 | 1.20 | 722 | 1270 | 1.0 | 534.2 | 67.7 | 130.4 | 103.2-113.2 |
| door +x-y (x wall) 1 | 1.20 | 715 | 797 | 1.0 | 541.3 | 66.1 | 125.4 | 104.4-114.4 |
| door +x-y (x wall) 2 | 1.20 | 376 | 261 | 1.2 | 568.3 | 33.1 | 115.3 | 71.0-81.0 |
| door +x-y (corner) | 1.20 | 206 | 46 | 0.9 | 564.1 | 18.3 | 115.3 | 1.6-11.5 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 966 | 5.0% | 20.9% |
| -x | avenue | 5.66 | 949 | 4.9% | 20.5% |
| +y | avenue | 5.66 | 941 | 4.9% | 20.4% |
| -y | avenue | 5.66 | 951 | 4.9% | 20.6% |
| door +x+y (y wall) 0 | door | 1.20 | 726 | 3.8% | 74.1% |
| door +x+y (y wall) 1 | door | 1.20 | 720 | 3.7% | 73.5% |
| door +x+y (y wall) 2 | door | 1.20 | 361 | 1.9% | 36.8% |
| door +x+y (x wall) 0 | door | 1.20 | 731 | 3.8% | 74.6% |
| door +x+y (x wall) 1 | door | 1.20 | 723 | 3.8% | 73.8% |
| door +x+y (x wall) 2 | door | 1.20 | 398 | 2.1% | 40.6% |
| door +x+y (corner) | door | 1.20 | 199 | 1.0% | 20.3% |
| door -x+y (y wall) 0 | door | 1.20 | 727 | 3.8% | 74.2% |
| door -x+y (y wall) 1 | door | 1.20 | 707 | 3.7% | 72.1% |
| door -x+y (y wall) 2 | door | 1.20 | 427 | 2.2% | 43.6% |
| door -x+y (x wall) 0 | door | 1.20 | 723 | 3.8% | 73.8% |
| door -x+y (x wall) 1 | door | 1.20 | 717 | 3.7% | 73.2% |
| door -x+y (x wall) 2 | door | 1.20 | 349 | 1.8% | 35.6% |
| door -x+y (corner) | door | 1.20 | 209 | 1.1% | 21.3% |
| door -x-y (y wall) 0 | door | 1.20 | 733 | 3.8% | 74.8% |
| door -x-y (y wall) 1 | door | 1.20 | 701 | 3.6% | 71.5% |
| door -x-y (y wall) 2 | door | 1.20 | 365 | 1.9% | 37.2% |
| door -x-y (x wall) 0 | door | 1.20 | 721 | 3.8% | 73.6% |
| door -x-y (x wall) 1 | door | 1.20 | 690 | 3.6% | 70.4% |
| door -x-y (x wall) 2 | door | 1.20 | 412 | 2.1% | 42.0% |
| door -x-y (corner) | door | 1.20 | 231 | 1.2% | 23.6% |
| door +x-y (y wall) 0 | door | 1.20 | 721 | 3.8% | 73.6% |
| door +x-y (y wall) 1 | door | 1.20 | 696 | 3.6% | 71.0% |
| door +x-y (y wall) 2 | door | 1.20 | 410 | 2.1% | 41.8% |
| door +x-y (x wall) 0 | door | 1.20 | 722 | 3.8% | 73.7% |
| door +x-y (x wall) 1 | door | 1.20 | 715 | 3.7% | 73.0% |
| door +x-y (x wall) 2 | door | 1.20 | 376 | 2.0% | 38.4% |
| door +x-y (corner) | door | 1.20 | 206 | 1.1% | 21.0% |
| **doors (28)** | door | 33.60 | 15416 | 80.2% | |
| **avenues (4)** | avenue | 22.64 | 3807 | 19.8% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 586.1 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 41.9%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 968 | 5.0% | 968 | 5.0% |
| straight +x+y (y wing) 1 | straight | yes | 605 | 3.1% | 601 | 3.1% |
| straight +x+y (y wing) 2 | straight | yes | 271 | 1.4% | 269 | 1.4% |
| straight +x+y (x wing) 0 | straight | yes | 965 | 5.0% | 965 | 5.0% |
| straight +x+y (x wing) 1 | straight | yes | 602 | 3.1% | 598 | 3.1% |
| straight +x+y (x wing) 2 | straight | yes | 306 | 1.6% | 306 | 1.6% |
| corner +x+y | corner | yes | 780 | 4.1% | 261 | 1.4% |
| straight -x+y (y wing) 0 | straight | yes | 963 | 5.0% | 963 | 5.0% |
| straight -x+y (y wing) 1 | straight | yes | 612 | 3.2% | 607 | 3.2% |
| straight -x+y (y wing) 2 | straight | yes | 325 | 1.7% | 323 | 1.7% |
| straight -x+y (x wing) 0 | straight | yes | 952 | 5.0% | 952 | 5.0% |
| straight -x+y (x wing) 1 | straight | yes | 617 | 3.2% | 610 | 3.2% |
| straight -x+y (x wing) 2 | straight | yes | 251 | 1.3% | 251 | 1.3% |
| corner -x+y | corner | yes | 763 | 4.0% | 263 | 1.4% |
| straight -x-y (y wing) 0 | straight | yes | 965 | 5.0% | 965 | 5.0% |
| straight -x-y (y wing) 1 | straight | yes | 597 | 3.1% | 587 | 3.1% |
| straight -x-y (y wing) 2 | straight | yes | 267 | 1.4% | 266 | 1.4% |
| straight -x-y (x wing) 0 | straight | yes | 957 | 5.0% | 957 | 5.0% |
| straight -x-y (x wing) 1 | straight | yes | 592 | 3.1% | 582 | 3.0% |
| straight -x-y (x wing) 2 | straight | yes | 319 | 1.7% | 318 | 1.7% |
| corner -x-y | corner | yes | 788 | 4.1% | 291 | 1.5% |
| straight +x-y (y wing) 0 | straight | yes | 954 | 5.0% | 954 | 5.0% |
| straight +x-y (y wing) 1 | straight | yes | 602 | 3.1% | 597 | 3.1% |
| straight +x-y (y wing) 2 | straight | yes | 309 | 1.6% | 308 | 1.6% |
| straight +x-y (x wing) 0 | straight | yes | 943 | 4.9% | 943 | 4.9% |
| straight +x-y (x wing) 1 | straight | yes | 605 | 3.1% | 598 | 3.1% |
| straight +x-y (x wing) 2 | straight | yes | 293 | 1.5% | 293 | 1.5% |
| corner +x-y | corner | yes | 793 | 4.1% | 274 | 1.4% |
| **straight (24)** | | | 14840 | | 14781 | 76.9% |
| **corner (4)** | | | 3124 | | 1089 | 5.7% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 3353, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 966 | 29.0 | 534.9 | 0.24 | 0.75 | 0.0% |
| -x | 949 | 29.0 | 525.8 | 0.24 | 0.71 | 0.0% |
| +y | 941 | 29.2 | 530.5 | 0.24 | 0.74 | 0.0% |
| -y | 951 | 29.0 | 534.7 | 0.24 | 0.71 | 0.0% |
| door +x+y (y wall) 0 | 726 | 0.7 | 544.0 | 0.80 | 1.50 | 45.5% |
| door +x+y (y wall) 1 | 720 | 1.0 | 554.3 | 0.78 | 1.44 | 39.3% |
| door +x+y (y wall) 2 | 361 | 1.0 | 586.1 | 0.37 | 1.38 | 15.3% |
| door +x+y (x wall) 0 | 731 | 1.0 | 541.7 | 0.81 | 1.50 | 47.3% |
| door +x+y (x wall) 1 | 723 | 1.2 | 554.1 | 0.78 | 1.50 | 33.9% |
| door +x+y (x wall) 2 | 398 | 0.9 | 578.2 | 0.41 | 1.44 | 17.2% |
| door +x+y (corner) | 199 | 0.7 | 562.8 | 0.21 | 1.38 | 7.0% |
| door -x+y (y wall) 0 | 727 | 0.9 | 520.9 | 0.84 | 1.44 | 50.9% |
| door -x+y (y wall) 1 | 707 | 0.9 | 543.4 | 0.78 | 1.38 | 43.6% |
| door -x+y (y wall) 2 | 427 | 1.2 | 586.1 | 0.44 | 1.44 | 15.3% |
| door -x+y (x wall) 0 | 723 | 0.9 | 537.1 | 0.81 | 1.56 | 50.0% |
| door -x+y (x wall) 1 | 717 | 1.2 | 555.7 | 0.77 | 1.50 | 39.3% |
| door -x+y (x wall) 2 | 349 | 0.9 | 573.0 | 0.36 | 1.38 | 17.2% |
| door -x+y (corner) | 209 | 0.7 | 584.4 | 0.21 | 1.32 | 8.5% |
| door -x-y (y wall) 0 | 733 | 1.0 | 542.2 | 0.81 | 1.44 | 43.6% |
| door -x-y (y wall) 1 | 701 | 0.9 | 538.5 | 0.78 | 1.44 | 38.2% |
| door -x-y (y wall) 2 | 365 | 0.9 | 581.0 | 0.38 | 1.44 | 16.9% |
| door -x-y (x wall) 0 | 721 | 0.9 | 539.8 | 0.80 | 1.44 | 43.6% |
| door -x-y (x wall) 1 | 690 | 1.6 | 536.8 | 0.77 | 1.50 | 37.0% |
| door -x-y (x wall) 2 | 412 | 0.9 | 584.9 | 0.42 | 1.26 | 16.9% |
| door -x-y (corner) | 231 | 0.9 | 584.9 | 0.24 | 1.32 | 13.6% |
| door +x-y (y wall) 0 | 721 | 0.9 | 536.4 | 0.80 | 1.44 | 42.6% |
| door +x-y (y wall) 1 | 696 | 1.0 | 562.2 | 0.74 | 1.56 | 35.1% |
| door +x-y (y wall) 2 | 410 | 0.9 | 579.1 | 0.42 | 1.38 | 15.3% |
| door +x-y (x wall) 0 | 722 | 1.0 | 534.2 | 0.81 | 1.56 | 42.6% |
| door +x-y (x wall) 1 | 715 | 1.0 | 541.3 | 0.79 | 1.50 | 41.8% |
| door +x-y (x wall) 2 | 376 | 1.2 | 568.3 | 0.40 | 1.38 | 15.8% |
| door +x-y (corner) | 206 | 0.9 | 564.1 | 0.22 | 1.38 | 8.8% |

Mean flow / w J averaged over the doors 0.60, over the avenues 0.24.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 968 | 611 / 358 / 220 | 0.3 | 541.0 | 2.20 | 3.41 | 82% | 82% | 0% | 4.30 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 554 | 601 / 0 / 9 | 0.7 | 551.3 | 1.11 | 1.50 | 80% | 70% | 11% | 3.85 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 76 | 269 / 0 / 3 | 0.7 | 583.1 | 0.47 | 1.30 | 17% | 14% | 3% | 2.88 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 965 | 621 / 345 / 219 | 0.2 | 538.7 | 2.20 | 3.81 | 82% | 82% | 0% | 4.39 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 555 | 598 / 0 / 4 | 0.7 | 551.1 | 1.09 | 1.50 | 82% | 71% | 11% | 3.72 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 78 | 306 / 0 / 0 | 0.7 | 575.3 | 0.53 | 1.30 | 16% | 14% | 2% | 3.21 |
| corner +x+y | 1.20 | 85.6 | 772 | 150 / 111 / 527 | 0.7 | 577.2 | 1.37 | 3.31 | 86% | 60% | 26% | 2.49 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 963 | 615 / 348 / 215 | 0.2 | 517.9 | 2.27 | 3.71 | 87% | 87% | 0% | 4.31 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 568 | 607 / 0 / 10 | 0.7 | 540.5 | 1.14 | 1.60 | 84% | 73% | 11% | 3.74 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 76 | 323 / 0 / 2 | 0.7 | 583.1 | 0.56 | 1.20 | 17% | 12% | 5% | 2.90 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 952 | 604 / 348 / 203 | 0.5 | 534.2 | 2.16 | 3.81 | 91% | 81% | 9% | 3.92 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 584 | 610 / 0 / 10 | 0.7 | 552.7 | 1.12 | 1.50 | 84% | 70% | 14% | 3.72 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 73 | 251 / 0 / 0 | 0.7 | 570.0 | 0.44 | 1.30 | 16% | 14% | 2% | 3.19 |
| corner -x+y | 1.20 | 85.6 | 753 | 160 / 103 / 512 | 0.2 | 580.5 | 1.34 | 3.31 | 85% | 56% | 29% | 2.39 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 965 | 616 / 349 / 222 | 0.3 | 539.2 | 2.20 | 3.71 | 82% | 82% | 0% | 4.25 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 559 | 588 / 0 / 14 | 0.7 | 535.6 | 1.13 | 1.60 | 85% | 74% | 11% | 3.77 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 76 | 266 / 0 / 1 | 0.7 | 578.1 | 0.46 | 1.10 | 17% | 14% | 3% | 3.08 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 957 | 605 / 352 / 223 | 0.3 | 536.8 | 2.20 | 3.91 | 83% | 81% | 2% | 4.33 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 564 | 582 / 0 / 15 | 0.7 | 533.8 | 1.12 | 1.50 | 85% | 72% | 13% | 3.82 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 75 | 318 / 0 / 1 | 0.7 | 581.9 | 0.55 | 1.50 | 15% | 12% | 3% | 3.07 |
| corner -x-y | 1.20 | 85.6 | 770 | 182 / 109 / 510 | 0.7 | 581.0 | 1.38 | 3.31 | 83% | 51% | 32% | 2.38 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 954 | 604 / 350 / 219 | 0.5 | 533.5 | 2.20 | 3.81 | 91% | 80% | 11% | 3.91 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 572 | 597 / 0 / 9 | 0.7 | 559.2 | 1.08 | 1.50 | 81% | 70% | 11% | 3.80 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 75 | 308 / 0 / 1 | 0.7 | 576.1 | 0.54 | 1.20 | 16% | 12% | 3% | 3.07 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 943 | 604 / 340 / 194 | 0.3 | 531.2 | 2.14 | 3.41 | 89% | 81% | 7% | 4.08 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 564 | 598 / 0 / 9 | 0.7 | 538.4 | 1.13 | 1.50 | 87% | 74% | 13% | 3.70 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 77 | 293 / 0 / 0 | 0.7 | 565.3 | 0.52 | 1.30 | 18% | 12% | 5% | 2.72 |
| corner +x-y | 1.20 | 85.6 | 782 | 160 / 114 / 527 | 0.7 | 570.2 | 1.41 | 3.21 | 84% | 48% | 36% | 2.36 |

The last agent out (agent 2435, t100 586.1 s): last gangway straight +x+y (y wing) 2, exit door +x+y (y wall) 2. The gangway that cleared last: straight +x+y (y wing) 2 at 583.1 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.80 | 578.8 / 564.8 / 541.5 | 565.3 / 531.5 / 459.7 | 852426.2 | 1930283 | 0.199 |
| gangway | 1212 | 1112.9 | 6.80 | 577.7 / 562.8 / 495.7 | 565.3 / 531.5 / 459.7 | 818680.9 | 1611610 | 0.100 |
| walkway | 276 | 257.4 | 5.37 | 213.2 / 167.2 / 21.9 | 184.4 / 128.0 / 9.4 | 166.0 | 44197 | 0.566 |
| avenue | 912 | 858.9 | 2.69 | 242.1 / 28.0 / 0.0 | 201.0 / 1.6 / 0.0 | 0.0 | 109285 | 1.327 |
| exit | 32 | 3.2 | 0.00 | 560.1 / 558.0 / 515.1 | 328.1 / 299.8 / 186.8 | 1237.1 | 2189 | 1.190 |
| concourse | 1116 | 1043.8 | 6.12 | 529.1 / 122.1 / 78.9 | 215.0 / 120.9 / 65.8 | 32342.1 | 163003 | 0.315 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.54 | 513.4 / 503.2 / 482.6 | 508.6 / 503.2 / 478.0 | 911897.0 | 2443462 | 0.037 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 26.5 | 27.5 | gangway | 1.00 | 6.10 | 506.2 | 498.8 | 443.2 | 2569.3 | 0.015 |
| 2 | 27.5 | 27.5 | gangway | 1.00 | 6.20 | 499.9 | 496.6 | 448.8 | 2568.1 | 0.012 |
| 3 | 29.5 | -26.5 | gangway | 1.00 | 6.29 | 498.8 | 478.2 | 408.8 | 2497.6 | 0.021 |
| 4 | 27.5 | 26.5 | gangway | 1.00 | 6.19 | 507.9 | 499.0 | 422.7 | 2456.4 | 0.016 |
| 5 | 26.5 | 28.5 | gangway | 1.00 | 6.12 | 508.8 | 498.3 | 425.0 | 2435.0 | 0.021 |
| 6 | 29.5 | 26.5 | gangway | 1.00 | 6.18 | 499.0 | 453.9 | 404.4 | 2425.3 | 0.019 |
| 7 | 28.5 | 26.5 | gangway | 1.00 | 6.06 | 507.9 | 497.3 | 421.4 | 2414.3 | 0.018 |
| 8 | -29.5 | -26.5 | gangway | 1.00 | 6.22 | 491.1 | 469.3 | 415.8 | 2371.1 | 0.019 |
| 9 | 27.5 | 28.5 | gangway | 1.00 | 6.05 | 502.3 | 499.2 | 421.5 | 2353.3 | 0.016 |
| 10 | -26.5 | 27.5 | gangway | 1.00 | 5.82 | 500.6 | 495.0 | 414.2 | 2340.9 | 0.018 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -30.5 | -25.5 | seat row | 0.64 | 6.81 | 457.9 | 449.3 | 407.4 | 1659.0 | 0.023 |
| 2 | -30.5 | 25.5 | seat row | 0.64 | 6.59 | 460.5 | 443.4 | 412.3 | 1646.5 | 0.022 |
| 3 | 30.5 | -25.5 | seat row | 0.64 | 6.80 | 452.5 | 445.8 | 404.2 | 1636.9 | 0.024 |
| 4 | 24.5 | 26.5 | seat row | 0.50 | 7.28 | 505.8 | 503.2 | 478.0 | 1631.2 | 0.014 |
| 5 | 25.5 | -30.5 | seat row | 0.64 | 6.46 | 462.6 | 459.3 | 409.8 | 1590.2 | 0.023 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1717; agent-steps of seated agents on another row's clearway: 14554.

## Deposit check

Person-seconds deposited: 4379692.6, of them in excluded cells: 5947.589.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 477042 overlapping pair-steps: p99 0.0028, max 0.0950 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0028 max 0.0950; venue-geometry 3: p99 0.0004 max 0.0004 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 23 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.29 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 592 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
