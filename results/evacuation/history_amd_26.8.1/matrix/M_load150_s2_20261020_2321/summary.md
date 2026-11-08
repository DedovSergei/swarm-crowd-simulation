# Experiment `M_load150_s2`

**Task 5.9 stage 4: venue M, 150% requested (seed 2): every seat + standing on the walkway and concourse (M, L: the achievable maximum, also the 125% request)**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 19223 agents (load 121.4%, requested 150%): every one of the 15832 seats and 3391 standing (spawnOvercrowdedCrowd, seed 2; below), buffer N = 32768, 3415 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 1465749 evaluations, 59710 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.21)** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-20T23:21:08, 90.0 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Spawn (overcrowding)

| | |
|---|---|
| seated | 15832 (every seat) |
| standing | **3391** (requested round((1.50 - 1) x 15832) = 7916; at most 3391 = floor(2.5 p/m^2 x 1356.6 m^2)) |
| standing floor | walkway + rear concourse, 1356.6 m^2 |
| standing on the walkway / concourse / gangways | 628 / 2763 / 0 |
| **load** | **121.42%** of the seats (requested 150%; the floor takes no more: the achievable maximum) |
| standing crowd's mean density | 2.500 p/m^2 |
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 3.98, all circulation cells 3.98 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 2, 110379 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1187 | 207.6 |
| t90 | 2611 | 456.7 |
| t100 | 3415 | 597.3 |

t_p: the step by which ceil(p x 19223) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 959 | 86 | 29.0 | 533.5 | 20.1 | 61.7 | 28.9-38.8 |
| -x | 5.66 | 945 | 84 | 29.0 | 525.8 | 20.2 | 58.5 | 28.9-38.8 |
| +y | 5.66 | 962 | 81 | 29.0 | 541.5 | 19.9 | 59.5 | 28.5-38.5 |
| -y | 5.66 | 961 | 91 | 29.0 | 533.6 | 20.2 | 59.5 | 28.9-38.8 |
| door +x+y (y wall) 0 | 1.20 | 716 | 1273 | 0.9 | 536.3 | 66.8 | 125.4 | 101.6-111.6 |
| door +x+y (y wall) 1 | 1.20 | 711 | 794 | 0.9 | 548.9 | 64.9 | 125.4 | 118.6-128.6 |
| door +x+y (y wall) 2 | 1.20 | 390 | 268 | 0.9 | 571.9 | 34.1 | 120.4 | 77.8-87.8 |
| door +x+y (x wall) 0 | 1.20 | 730 | 1275 | 0.7 | 545.7 | 66.9 | 125.4 | 103.9-113.9 |
| door +x+y (x wall) 1 | 1.20 | 707 | 798 | 0.9 | 542.6 | 65.2 | 125.4 | 112.5-122.4 |
| door +x+y (x wall) 2 | 1.20 | 368 | 270 | 1.0 | 579.1 | 31.8 | 105.3 | 1.7-11.7 |
| door +x+y (corner) | 1.20 | 230 | 44 | 0.9 | 584.4 | 19.7 | 120.4 | 3.3-13.3 |
| door -x+y (y wall) 0 | 1.20 | 738 | 1276 | 1.4 | 551.3 | 67.1 | 125.4 | 105.8-115.8 |
| door -x+y (y wall) 1 | 1.20 | 715 | 796 | 0.7 | 578.4 | 61.9 | 125.4 | 98.1-108.1 |
| door -x+y (y wall) 2 | 1.20 | 408 | 266 | 1.0 | 596.4 | 34.3 | 105.3 | 47.4-57.4 |
| door -x+y (x wall) 0 | 1.20 | 724 | 1275 | 0.9 | 535.6 | 67.7 | 125.4 | 103.0-113.0 |
| door -x+y (x wall) 1 | 1.20 | 716 | 790 | 0.9 | 560.4 | 64.0 | 125.4 | 98.8-108.8 |
| door -x+y (x wall) 2 | 1.20 | 356 | 276 | 1.0 | 597.3 | 29.8 | 110.3 | 87.1-97.1 |
| door -x+y (corner) | 1.20 | 191 | 47 | 0.9 | 583.0 | 16.4 | 110.3 | 0.3-10.3 |
| door -x-y (y wall) 0 | 1.20 | 723 | 1273 | 1.0 | 544.1 | 66.5 | 125.4 | 99.3-109.3 |
| door -x-y (y wall) 1 | 1.20 | 704 | 791 | 1.0 | 544.1 | 64.8 | 130.4 | 98.6-108.6 |
| door -x-y (y wall) 2 | 1.20 | 381 | 261 | 1.0 | 590.1 | 32.3 | 115.3 | 74.7-84.7 |
| door -x-y (x wall) 0 | 1.20 | 723 | 1275 | 1.2 | 536.3 | 67.5 | 125.4 | 103.0-113.0 |
| door -x-y (x wall) 1 | 1.20 | 712 | 799 | 0.7 | 563.7 | 63.2 | 125.4 | 103.4-113.3 |
| door -x-y (x wall) 2 | 1.20 | 399 | 261 | 1.4 | 593.6 | 33.7 | 105.3 | 53.7-63.7 |
| door -x-y (corner) | 1.20 | 204 | 51 | 0.7 | 593.6 | 17.2 | 110.3 | 0.5-10.5 |
| door +x-y (y wall) 0 | 1.20 | 732 | 1275 | 0.7 | 534.5 | 68.5 | 130.4 | 102.5-112.5 |
| door +x-y (y wall) 1 | 1.20 | 695 | 798 | 1.0 | 552.9 | 63.0 | 120.4 | 99.9-109.8 |
| door +x-y (y wall) 2 | 1.20 | 361 | 267 | 1.0 | 588.0 | 30.7 | 110.3 | 77.3-87.3 |
| door +x-y (x wall) 0 | 1.20 | 721 | 1266 | 1.0 | 534.2 | 67.6 | 125.4 | 98.1-108.1 |
| door +x-y (x wall) 1 | 1.20 | 711 | 801 | 0.9 | 553.1 | 64.4 | 125.4 | 102.5-112.5 |
| door +x-y (x wall) 2 | 1.20 | 407 | 270 | 1.0 | 576.3 | 35.4 | 110.3 | 25.7-35.7 |
| door +x-y (corner) | 1.20 | 223 | 45 | 0.9 | 563.9 | 19.8 | 115.3 | 0.7-10.7 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 959 | 5.0% | 20.4% |
| -x | avenue | 5.66 | 945 | 4.9% | 20.1% |
| +y | avenue | 5.66 | 962 | 5.0% | 20.4% |
| -y | avenue | 5.66 | 961 | 5.0% | 20.4% |
| door +x+y (y wall) 0 | door | 1.20 | 716 | 3.7% | 71.7% |
| door +x+y (y wall) 1 | door | 1.20 | 711 | 3.7% | 71.2% |
| door +x+y (y wall) 2 | door | 1.20 | 390 | 2.0% | 39.1% |
| door +x+y (x wall) 0 | door | 1.20 | 730 | 3.8% | 73.1% |
| door +x+y (x wall) 1 | door | 1.20 | 707 | 3.7% | 70.8% |
| door +x+y (x wall) 2 | door | 1.20 | 368 | 1.9% | 36.8% |
| door +x+y (corner) | door | 1.20 | 230 | 1.2% | 23.0% |
| door -x+y (y wall) 0 | door | 1.20 | 738 | 3.8% | 73.9% |
| door -x+y (y wall) 1 | door | 1.20 | 715 | 3.7% | 71.6% |
| door -x+y (y wall) 2 | door | 1.20 | 408 | 2.1% | 40.9% |
| door -x+y (x wall) 0 | door | 1.20 | 724 | 3.8% | 72.5% |
| door -x+y (x wall) 1 | door | 1.20 | 716 | 3.7% | 71.7% |
| door -x+y (x wall) 2 | door | 1.20 | 356 | 1.9% | 35.6% |
| door -x+y (corner) | door | 1.20 | 191 | 1.0% | 19.1% |
| door -x-y (y wall) 0 | door | 1.20 | 723 | 3.8% | 72.4% |
| door -x-y (y wall) 1 | door | 1.20 | 704 | 3.7% | 70.5% |
| door -x-y (y wall) 2 | door | 1.20 | 381 | 2.0% | 38.1% |
| door -x-y (x wall) 0 | door | 1.20 | 723 | 3.8% | 72.4% |
| door -x-y (x wall) 1 | door | 1.20 | 712 | 3.7% | 71.3% |
| door -x-y (x wall) 2 | door | 1.20 | 399 | 2.1% | 40.0% |
| door -x-y (corner) | door | 1.20 | 204 | 1.1% | 20.4% |
| door +x-y (y wall) 0 | door | 1.20 | 732 | 3.8% | 73.3% |
| door +x-y (y wall) 1 | door | 1.20 | 695 | 3.6% | 69.6% |
| door +x-y (y wall) 2 | door | 1.20 | 361 | 1.9% | 36.1% |
| door +x-y (x wall) 0 | door | 1.20 | 721 | 3.8% | 72.2% |
| door +x-y (x wall) 1 | door | 1.20 | 711 | 3.7% | 71.2% |
| door +x-y (x wall) 2 | door | 1.20 | 407 | 2.1% | 40.8% |
| door +x-y (corner) | door | 1.20 | 223 | 1.2% | 22.3% |
| **doors (28)** | door | 33.60 | 15396 | 80.1% | |
| **avenues (4)** | avenue | 22.64 | 3827 | 19.9% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 597.3 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 41.1%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 957 | 5.0% | 957 | 5.0% |
| straight +x+y (y wing) 1 | straight | yes | 606 | 3.2% | 597 | 3.1% |
| straight +x+y (y wing) 2 | straight | yes | 300 | 1.6% | 300 | 1.6% |
| straight +x+y (x wing) 0 | straight | yes | 949 | 4.9% | 949 | 4.9% |
| straight +x+y (x wing) 1 | straight | yes | 594 | 3.1% | 589 | 3.1% |
| straight +x+y (x wing) 2 | straight | yes | 279 | 1.5% | 276 | 1.4% |
| corner +x+y | corner | yes | 784 | 4.1% | 300 | 1.6% |
| straight -x+y (y wing) 0 | straight | yes | 962 | 5.0% | 962 | 5.0% |
| straight -x+y (y wing) 1 | straight | yes | 609 | 3.2% | 605 | 3.1% |
| straight -x+y (y wing) 2 | straight | yes | 326 | 1.7% | 320 | 1.7% |
| straight -x+y (x wing) 0 | straight | yes | 967 | 5.0% | 967 | 5.0% |
| straight -x+y (x wing) 1 | straight | yes | 611 | 3.2% | 606 | 3.2% |
| straight -x+y (x wing) 2 | straight | yes | 260 | 1.4% | 260 | 1.4% |
| corner -x+y | corner | yes | 767 | 4.0% | 248 | 1.3% |
| straight -x-y (y wing) 0 | straight | yes | 951 | 4.9% | 951 | 4.9% |
| straight -x-y (y wing) 1 | straight | yes | 604 | 3.1% | 597 | 3.1% |
| straight -x-y (y wing) 2 | straight | yes | 294 | 1.5% | 293 | 1.5% |
| straight -x-y (x wing) 0 | straight | yes | 951 | 4.9% | 951 | 4.9% |
| straight -x-y (x wing) 1 | straight | yes | 600 | 3.1% | 593 | 3.1% |
| straight -x-y (x wing) 2 | straight | yes | 330 | 1.7% | 327 | 1.7% |
| corner -x-y | corner | yes | 793 | 4.1% | 254 | 1.3% |
| straight +x-y (y wing) 0 | straight | yes | 963 | 5.0% | 963 | 5.0% |
| straight +x-y (y wing) 1 | straight | yes | 588 | 3.1% | 583 | 3.0% |
| straight +x-y (y wing) 2 | straight | yes | 275 | 1.4% | 269 | 1.4% |
| straight +x-y (x wing) 0 | straight | yes | 954 | 5.0% | 954 | 5.0% |
| straight +x-y (x wing) 1 | straight | yes | 595 | 3.1% | 591 | 3.1% |
| straight +x-y (x wing) 2 | straight | yes | 318 | 1.7% | 317 | 1.6% |
| corner +x-y | corner | yes | 794 | 4.1% | 288 | 1.5% |
| **straight (24)** | | | 14843 | | 14777 | 76.9% |
| **corner (4)** | | | 3138 | | 1090 | 5.7% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 3356, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 959 | 29.0 | 533.5 | 0.24 | 0.74 | 0.0% |
| -x | 945 | 29.0 | 525.8 | 0.24 | 0.70 | 0.0% |
| +y | 962 | 29.0 | 541.5 | 0.24 | 0.71 | 0.0% |
| -y | 961 | 29.0 | 533.6 | 0.24 | 0.71 | 0.0% |
| door +x+y (y wall) 0 | 716 | 0.9 | 536.3 | 0.80 | 1.50 | 50.0% |
| door +x+y (y wall) 1 | 711 | 0.9 | 548.9 | 0.78 | 1.50 | 39.3% |
| door +x+y (y wall) 2 | 390 | 0.9 | 571.9 | 0.41 | 1.44 | 15.5% |
| door +x+y (x wall) 0 | 730 | 0.7 | 545.7 | 0.80 | 1.50 | 52.7% |
| door +x+y (x wall) 1 | 707 | 0.9 | 542.6 | 0.78 | 1.50 | 40.0% |
| door +x+y (x wall) 2 | 368 | 1.0 | 579.1 | 0.38 | 1.26 | 15.3% |
| door +x+y (corner) | 230 | 0.9 | 584.4 | 0.24 | 1.44 | 8.5% |
| door -x+y (y wall) 0 | 738 | 1.4 | 551.3 | 0.80 | 1.50 | 53.6% |
| door -x+y (y wall) 1 | 715 | 0.7 | 578.4 | 0.74 | 1.50 | 42.4% |
| door -x+y (y wall) 2 | 408 | 1.0 | 596.4 | 0.41 | 1.26 | 16.7% |
| door -x+y (x wall) 0 | 724 | 0.9 | 535.6 | 0.81 | 1.50 | 46.3% |
| door -x+y (x wall) 1 | 716 | 0.9 | 560.4 | 0.77 | 1.50 | 35.1% |
| door -x+y (x wall) 2 | 356 | 1.0 | 597.3 | 0.36 | 1.32 | 16.7% |
| door -x+y (corner) | 191 | 0.9 | 583.0 | 0.20 | 1.32 | 10.2% |
| door -x-y (y wall) 0 | 723 | 1.0 | 544.1 | 0.80 | 1.50 | 43.6% |
| door -x-y (y wall) 1 | 704 | 1.0 | 544.1 | 0.78 | 1.56 | 36.4% |
| door -x-y (y wall) 2 | 381 | 1.0 | 590.1 | 0.39 | 1.38 | 16.7% |
| door -x-y (x wall) 0 | 723 | 1.2 | 536.3 | 0.81 | 1.50 | 42.6% |
| door -x-y (x wall) 1 | 712 | 0.7 | 563.7 | 0.76 | 1.50 | 38.6% |
| door -x-y (x wall) 2 | 399 | 1.4 | 593.6 | 0.40 | 1.26 | 13.3% |
| door -x-y (corner) | 204 | 0.7 | 593.6 | 0.21 | 1.32 | 6.7% |
| door +x-y (y wall) 0 | 732 | 0.7 | 534.5 | 0.82 | 1.56 | 44.4% |
| door +x-y (y wall) 1 | 695 | 1.0 | 552.9 | 0.75 | 1.44 | 35.7% |
| door +x-y (y wall) 2 | 361 | 1.0 | 588.0 | 0.37 | 1.32 | 15.3% |
| door +x-y (x wall) 0 | 721 | 1.0 | 534.2 | 0.81 | 1.50 | 44.4% |
| door +x-y (x wall) 1 | 711 | 0.9 | 553.1 | 0.77 | 1.50 | 44.6% |
| door +x-y (x wall) 2 | 407 | 1.0 | 576.3 | 0.42 | 1.32 | 15.5% |
| door +x-y (corner) | 223 | 0.9 | 563.9 | 0.24 | 1.38 | 10.5% |

Mean flow / w J averaged over the doors 0.59, over the avenues 0.24.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 957 | 600 / 357 / 225 | 0.5 | 533.3 | 2.22 | 4.01 | 85% | 80% | 6% | 4.14 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 569 | 597 / 0 / 11 | 0.7 | 545.9 | 1.11 | 1.50 | 87% | 71% | 16% | 3.71 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 75 | 301 / 0 / 1 | 0.7 | 569.0 | 0.53 | 1.30 | 17% | 14% | 3% | 3.04 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 949 | 610 / 339 / 220 | 0.5 | 542.7 | 2.16 | 3.61 | 89% | 82% | 7% | 4.16 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 570 | 589 / 0 / 6 | 0.7 | 539.6 | 1.10 | 1.60 | 85% | 71% | 15% | 3.73 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 77 | 276 / 0 / 5 | 0.7 | 576.1 | 0.49 | 1.20 | 17% | 12% | 5% | 2.99 |
| corner +x+y | 1.20 | 85.6 | 771 | 186 / 114 / 494 | 0.7 | 580.5 | 1.37 | 3.11 | 85% | 56% | 29% | 2.36 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 962 | 622 / 340 / 208 | 0.3 | 548.3 | 2.13 | 3.51 | 84% | 82% | 2% | 4.38 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 566 | 605 / 0 / 8 | 0.7 | 575.4 | 1.07 | 1.60 | 79% | 66% | 14% | 3.64 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 74 | 320 / 0 / 7 | 0.7 | 593.5 | 0.55 | 1.40 | 13% | 12% | 2% | 3.08 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 967 | 604 / 363 / 213 | 0.2 | 532.6 | 2.22 | 4.21 | 91% | 81% | 9% | 4.00 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 568 | 606 / 0 / 6 | 0.7 | 557.6 | 1.10 | 1.50 | 80% | 66% | 14% | 3.65 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 73 | 260 / 0 / 0 | 0.7 | 594.3 | 0.44 | 1.10 | 17% | 13% | 3% | 3.29 |
| corner -x+y | 1.20 | 85.6 | 758 | 136 / 112 / 531 | 0.7 | 588.4 | 1.33 | 3.61 | 83% | 58% | 25% | 2.43 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 951 | 605 / 346 / 193 | 0.5 | 541.2 | 2.12 | 3.61 | 91% | 80% | 11% | 3.89 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 564 | 597 / 0 / 9 | 0.7 | 541.2 | 1.12 | 1.50 | 84% | 71% | 13% | 3.67 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 77 | 293 / 0 / 1 | 0.7 | 587.2 | 0.50 | 1.20 | 17% | 12% | 5% | 2.94 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 951 | 607 / 345 / 215 | 0.2 | 533.3 | 2.19 | 3.81 | 91% | 81% | 9% | 3.99 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 562 | 593 / 0 / 9 | 0.7 | 560.8 | 1.07 | 1.60 | 81% | 70% | 11% | 3.73 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 80 | 327 / 0 / 3 | 0.7 | 590.7 | 0.56 | 1.30 | 17% | 17% | 0% | 3.10 |
| corner -x-y | 1.20 | 85.6 | 781 | 143 / 111 / 549 | 0.7 | 589.8 | 1.36 | 3.51 | 83% | 48% | 35% | 2.36 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 963 | 615 / 348 / 221 | 0.3 | 531.5 | 2.23 | 3.51 | 85% | 83% | 2% | 4.25 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 551 | 583 / 0 / 166 | 0.7 | 549.9 | 1.36 | 3.51 | 82% | 70% | 12% | 3.72 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 77 | 269 / 0 / 7 | 0.7 | 585.1 | 0.47 | 1.30 | 14% | 14% | 0% | 2.95 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 954 | 611 / 343 / 214 | 0.3 | 531.2 | 2.20 | 3.51 | 83% | 81% | 2% | 4.29 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 561 | 592 / 0 / 12 | 0.5 | 550.1 | 1.10 | 1.81 | 84% | 70% | 14% | 3.72 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 75 | 317 / 0 / 1 | 0.7 | 573.3 | 0.56 | 1.20 | 16% | 12% | 3% | 3.03 |
| corner +x-y | 1.20 | 85.6 | 784 | 173 / 115 / 682 | 0.7 | 579.1 | 1.68 | 3.71 | 85% | 53% | 32% | 2.37 |

The last agent out (agent 6350, t100 597.3 s): last gangway straight -x+y (x wing) 2, exit door -x+y (x wall) 2. The gangway that cleared last: straight -x+y (x wing) 2 at 594.3 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.82 | 592.8 / 583.5 / 541.3 | 573.9 / 540.1 / 448.3 | 847154.4 | 1931570 | 0.199 |
| gangway | 1212 | 1112.9 | 6.82 | 590.0 / 575.8 / 490.3 | 573.9 / 540.1 / 448.3 | 813979.2 | 1612218 | 0.100 |
| walkway | 276 | 257.4 | 5.38 | 221.3 / 171.8 / 27.6 | 187.0 / 162.0 / 13.5 | 170.5 | 47474 | 0.533 |
| avenue | 912 | 858.9 | 2.52 | 248.0 / 18.9 / 0.0 | 192.9 / 2.4 / 0.0 | 0.0 | 109882 | 1.326 |
| exit | 32 | 3.2 | 0.00 | 570.7 / 566.5 / 511.6 | 328.0 / 298.9 / 180.0 | 1225.2 | 2183 | 1.193 |
| concourse | 1116 | 1043.8 | 6.11 | 523.8 / 124.5 / 74.7 | 212.2 / 123.1 / 58.1 | 31779.4 | 159813 | 0.319 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.59 | 512.1 / 503.7 / 488.3 | 504.8 / 503.7 / 484.7 | 918807.9 | 2447790 | 0.037 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -26.5 | 28.5 | gangway | 1.00 | 6.20 | 506.0 | 503.4 | 435.9 | 2604.8 | 0.017 |
| 2 | 26.5 | 29.5 | gangway | 1.00 | 6.34 | 498.8 | 471.7 | 430.6 | 2598.1 | 0.019 |
| 3 | -28.5 | 26.5 | gangway | 1.00 | 5.98 | 519.6 | 496.0 | 435.3 | 2504.2 | 0.019 |
| 4 | -26.5 | 27.5 | gangway | 1.00 | 5.82 | 509.9 | 501.8 | 440.2 | 2459.1 | 0.014 |
| 5 | 29.5 | -26.5 | gangway | 1.00 | 6.21 | 502.5 | 465.4 | 403.7 | 2426.9 | 0.020 |
| 6 | -27.5 | 28.5 | gangway | 1.00 | 5.58 | 517.0 | 507.4 | 440.4 | 2388.1 | 0.019 |
| 7 | -28.5 | 27.5 | gangway | 1.00 | 5.85 | 518.2 | 514.2 | 438.1 | 2376.2 | 0.019 |
| 8 | -27.5 | -27.5 | gangway | 1.00 | 5.84 | 504.4 | 499.2 | 425.4 | 2361.0 | 0.017 |
| 9 | 28.5 | 26.5 | gangway | 1.00 | 5.95 | 501.1 | 485.0 | 410.3 | 2338.4 | 0.016 |
| 10 | -29.5 | -26.5 | gangway | 1.00 | 6.02 | 498.5 | 464.4 | 407.0 | 2324.2 | 0.019 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 25.5 | 30.5 | seat row | 0.64 | 6.81 | 453.9 | 443.4 | 409.3 | 1636.4 | 0.025 |
| 2 | 30.5 | 25.5 | seat row | 0.64 | 6.52 | 468.2 | 465.4 | 405.3 | 1608.2 | 0.024 |
| 3 | -26.5 | 24.5 | seat row | 0.50 | 6.94 | 492.0 | 488.0 | 481.3 | 1604.7 | 0.013 |
| 4 | 26.5 | 24.5 | seat row | 0.50 | 7.27 | 496.2 | 495.7 | 483.4 | 1596.1 | 0.016 |
| 5 | 30.5 | -25.5 | seat row | 0.64 | 6.87 | 430.8 | 417.9 | 381.8 | 1581.7 | 0.024 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1713; agent-steps of seated agents on another row's clearway: 17724.

## Deposit check

Person-seconds deposited: 4385229.7, of them in excluded cells: 5869.655.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 525115 overlapping pair-steps: p99 0.0027, max 0.0465 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0027 max 0.0465; venue-geometry 3: p99 0.0005 max 0.0005 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 19 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.34 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 558 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
