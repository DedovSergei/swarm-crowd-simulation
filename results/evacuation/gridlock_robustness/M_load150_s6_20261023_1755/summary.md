# Experiment `M_load150_s6`

**Task 5.11 stage 1 (gridlock robustness, default model, AMD 26.10.1): venue M, the achievable maximum 121.42% (150% requested, seed 6)**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 19223 agents (load 121.4%, requested 150%): every one of the 15832 seats and 3391 standing (spawnOvercrowdedCrowd, seed 6; below), buffer N = 32768, 3409 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 1472591 evaluations, 59687 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.21)** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `15aa31e8667e4a9417fde7884d907d1832c5e2d6`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-23T17:55:44, 122.3 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Spawn (overcrowding)

| | |
|---|---|
| seated | 15832 (every seat) |
| standing | **3391** (requested round((1.50 - 1) x 15832) = 7916; at most 3391 = floor(2.5 p/m^2 x 1356.6 m^2)) |
| standing floor | walkway + rear concourse, 1356.6 m^2 |
| standing on the walkway / concourse / gangways | 624 / 2767 / 0 |
| **load** | **121.42%** of the seats (requested 150%; the floor takes no more: the achievable maximum) |
| standing crowd's mean density | 2.500 p/m^2 |
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 4.15, all circulation cells 4.15 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 6, 107895 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1196 | 209.2 |
| t90 | 2621 | 458.4 |
| t100 | 3409 | 596.3 |

t_p: the step by which ceil(p x 19223) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 959 | 93 | 29.0 | 530.7 | 20.3 | 63.8 | 28.9-38.8 |
| -x | 5.66 | 968 | 93 | 29.0 | 530.0 | 20.5 | 61.7 | 28.7-38.7 |
| +y | 5.66 | 960 | 83 | 29.0 | 530.7 | 20.3 | 55.3 | 28.7-38.7 |
| -y | 5.66 | 952 | 85 | 29.0 | 532.8 | 20.0 | 58.5 | 28.7-38.7 |
| door +x+y (y wall) 0 | 1.20 | 725 | 1272 | 1.2 | 536.3 | 67.7 | 120.4 | 103.0-113.0 |
| door +x+y (y wall) 1 | 1.20 | 706 | 799 | 1.4 | 565.8 | 62.5 | 120.4 | 105.3-115.3 |
| door +x+y (y wall) 2 | 1.20 | 411 | 268 | 0.9 | 593.8 | 34.6 | 100.3 | 8.4-18.4 |
| door +x+y (x wall) 0 | 1.20 | 718 | 1265 | 1.0 | 546.6 | 65.8 | 125.4 | 93.4-103.4 |
| door +x+y (x wall) 1 | 1.20 | 715 | 800 | 0.7 | 551.8 | 64.8 | 130.4 | 99.5-109.5 |
| door +x+y (x wall) 2 | 1.20 | 352 | 266 | 1.0 | 587.3 | 30.0 | 115.3 | 80.1-90.1 |
| door +x+y (corner) | 1.20 | 212 | 44 | 0.9 | 587.9 | 18.1 | 115.3 | 0.7-10.7 |
| door -x+y (y wall) 0 | 1.20 | 732 | 1279 | 1.0 | 550.4 | 66.6 | 130.4 | 108.8-118.8 |
| door -x+y (y wall) 1 | 1.20 | 707 | 795 | 0.7 | 592.9 | 59.7 | 120.4 | 106.2-116.1 |
| door -x+y (y wall) 2 | 1.20 | 382 | 268 | 0.9 | 579.3 | 33.0 | 105.3 | 69.3-79.2 |
| door -x+y (x wall) 0 | 1.20 | 726 | 1267 | 1.0 | 548.7 | 66.3 | 130.4 | 98.1-108.1 |
| door -x+y (x wall) 1 | 1.20 | 717 | 797 | 0.7 | 566.3 | 63.4 | 125.4 | 100.2-110.2 |
| door -x+y (x wall) 2 | 1.20 | 389 | 269 | 0.9 | 593.1 | 32.8 | 115.3 | 84.1-94.1 |
| door -x+y (corner) | 1.20 | 200 | 46 | 0.9 | 596.3 | 16.8 | 120.4 | 0.7-10.7 |
| door -x-y (y wall) 0 | 1.20 | 719 | 1267 | 1.0 | 542.2 | 66.4 | 120.4 | 99.3-109.3 |
| door -x-y (y wall) 1 | 1.20 | 708 | 795 | 1.0 | 562.5 | 63.0 | 125.4 | 104.9-114.9 |
| door -x-y (y wall) 2 | 1.20 | 371 | 267 | 1.0 | 573.2 | 32.4 | 105.3 | 75.9-85.9 |
| door -x-y (x wall) 0 | 1.20 | 718 | 1272 | 0.7 | 541.5 | 66.4 | 130.4 | 105.1-115.1 |
| door -x-y (x wall) 1 | 1.20 | 710 | 789 | 1.0 | 559.2 | 63.6 | 130.4 | 87.8-97.8 |
| door -x-y (x wall) 2 | 1.20 | 384 | 275 | 0.9 | 584.9 | 32.9 | 115.3 | 80.5-90.4 |
| door -x-y (corner) | 1.20 | 227 | 45 | 1.2 | 567.2 | 20.0 | 120.4 | 9.4-19.4 |
| door +x-y (y wall) 0 | 1.20 | 728 | 1267 | 0.9 | 550.1 | 66.3 | 120.4 | 100.0-110.0 |
| door +x-y (y wall) 1 | 1.20 | 711 | 800 | 1.0 | 560.2 | 63.6 | 120.4 | 103.2-113.2 |
| door +x-y (y wall) 2 | 1.20 | 368 | 273 | 0.9 | 577.5 | 31.9 | 120.4 | 79.8-89.7 |
| door +x-y (x wall) 0 | 1.20 | 728 | 1267 | 0.7 | 545.4 | 66.8 | 115.3 | 14.3-24.3 |
| door +x-y (x wall) 1 | 1.20 | 704 | 802 | 0.7 | 562.2 | 62.7 | 125.4 | 110.2-120.2 |
| door +x-y (x wall) 2 | 1.20 | 394 | 270 | 0.7 | 563.4 | 35.0 | 115.3 | 79.6-89.6 |
| door +x-y (corner) | 1.20 | 222 | 45 | 0.9 | 573.9 | 19.4 | 110.3 | 1.0-11.0 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 959 | 5.0% | 20.4% |
| -x | avenue | 5.66 | 968 | 5.0% | 20.6% |
| +y | avenue | 5.66 | 960 | 5.0% | 20.4% |
| -y | avenue | 5.66 | 952 | 5.0% | 20.2% |
| door +x+y (y wall) 0 | door | 1.20 | 725 | 3.8% | 72.7% |
| door +x+y (y wall) 1 | door | 1.20 | 706 | 3.7% | 70.8% |
| door +x+y (y wall) 2 | door | 1.20 | 411 | 2.1% | 41.2% |
| door +x+y (x wall) 0 | door | 1.20 | 718 | 3.7% | 72.0% |
| door +x+y (x wall) 1 | door | 1.20 | 715 | 3.7% | 71.7% |
| door +x+y (x wall) 2 | door | 1.20 | 352 | 1.8% | 35.3% |
| door +x+y (corner) | door | 1.20 | 212 | 1.1% | 21.3% |
| door -x+y (y wall) 0 | door | 1.20 | 732 | 3.8% | 73.4% |
| door -x+y (y wall) 1 | door | 1.20 | 707 | 3.7% | 70.9% |
| door -x+y (y wall) 2 | door | 1.20 | 382 | 2.0% | 38.3% |
| door -x+y (x wall) 0 | door | 1.20 | 726 | 3.8% | 72.8% |
| door -x+y (x wall) 1 | door | 1.20 | 717 | 3.7% | 71.9% |
| door -x+y (x wall) 2 | door | 1.20 | 389 | 2.0% | 39.0% |
| door -x+y (corner) | door | 1.20 | 200 | 1.0% | 20.1% |
| door -x-y (y wall) 0 | door | 1.20 | 719 | 3.7% | 72.1% |
| door -x-y (y wall) 1 | door | 1.20 | 708 | 3.7% | 71.0% |
| door -x-y (y wall) 2 | door | 1.20 | 371 | 1.9% | 37.2% |
| door -x-y (x wall) 0 | door | 1.20 | 718 | 3.7% | 72.0% |
| door -x-y (x wall) 1 | door | 1.20 | 710 | 3.7% | 71.2% |
| door -x-y (x wall) 2 | door | 1.20 | 384 | 2.0% | 38.5% |
| door -x-y (corner) | door | 1.20 | 227 | 1.2% | 22.8% |
| door +x-y (y wall) 0 | door | 1.20 | 728 | 3.8% | 73.0% |
| door +x-y (y wall) 1 | door | 1.20 | 711 | 3.7% | 71.3% |
| door +x-y (y wall) 2 | door | 1.20 | 368 | 1.9% | 36.9% |
| door +x-y (x wall) 0 | door | 1.20 | 728 | 3.8% | 73.0% |
| door +x-y (x wall) 1 | door | 1.20 | 704 | 3.7% | 70.6% |
| door +x-y (x wall) 2 | door | 1.20 | 394 | 2.0% | 39.5% |
| door +x-y (corner) | door | 1.20 | 222 | 1.2% | 22.3% |
| **doors (28)** | door | 33.60 | 15384 | 80.0% | |
| **avenues (4)** | avenue | 22.64 | 3839 | 20.0% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 596.3 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 41.1%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 966 | 5.0% | 966 | 5.0% |
| straight +x+y (y wing) 1 | straight | yes | 594 | 3.1% | 587 | 3.1% |
| straight +x+y (y wing) 2 | straight | yes | 327 | 1.7% | 326 | 1.7% |
| straight +x+y (x wing) 0 | straight | yes | 947 | 4.9% | 947 | 4.9% |
| straight +x+y (x wing) 1 | straight | yes | 601 | 3.1% | 595 | 3.1% |
| straight +x+y (x wing) 2 | straight | yes | 265 | 1.4% | 265 | 1.4% |
| corner +x+y | corner | yes | 803 | 4.2% | 282 | 1.5% |
| straight -x+y (y wing) 0 | straight | yes | 959 | 5.0% | 959 | 5.0% |
| straight -x+y (y wing) 1 | straight | yes | 597 | 3.1% | 592 | 3.1% |
| straight -x+y (y wing) 2 | straight | yes | 314 | 1.6% | 309 | 1.6% |
| straight -x+y (x wing) 0 | straight | yes | 960 | 5.0% | 960 | 5.0% |
| straight -x+y (x wing) 1 | straight | yes | 608 | 3.2% | 600 | 3.1% |
| straight -x+y (x wing) 2 | straight | yes | 301 | 1.6% | 300 | 1.6% |
| corner -x+y | corner | yes | 787 | 4.1% | 246 | 1.3% |
| straight -x-y (y wing) 0 | straight | yes | 959 | 5.0% | 959 | 5.0% |
| straight -x-y (y wing) 1 | straight | yes | 599 | 3.1% | 593 | 3.1% |
| straight -x-y (y wing) 2 | straight | yes | 290 | 1.5% | 285 | 1.5% |
| straight -x-y (x wing) 0 | straight | yes | 948 | 4.9% | 948 | 4.9% |
| straight -x-y (x wing) 1 | straight | yes | 609 | 3.2% | 602 | 3.1% |
| straight -x-y (x wing) 2 | straight | yes | 287 | 1.5% | 287 | 1.5% |
| corner -x-y | corner | yes | 784 | 4.1% | 292 | 1.5% |
| straight +x-y (y wing) 0 | straight | yes | 961 | 5.0% | 961 | 5.0% |
| straight +x-y (y wing) 1 | straight | yes | 598 | 3.1% | 591 | 3.1% |
| straight +x-y (y wing) 2 | straight | yes | 284 | 1.5% | 282 | 1.5% |
| straight +x-y (x wing) 0 | straight | yes | 966 | 5.0% | 966 | 5.0% |
| straight +x-y (x wing) 1 | straight | yes | 588 | 3.1% | 582 | 3.0% |
| straight +x-y (x wing) 2 | straight | yes | 309 | 1.6% | 304 | 1.6% |
| corner +x-y | corner | yes | 797 | 4.1% | 281 | 1.5% |
| **straight (24)** | | | 14837 | | 14766 | 76.8% |
| **corner (4)** | | | 3171 | | 1101 | 5.7% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 3356, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 959 | 29.0 | 530.7 | 0.24 | 0.76 | 0.0% |
| -x | 968 | 29.0 | 530.0 | 0.24 | 0.74 | 0.0% |
| +y | 960 | 29.0 | 530.7 | 0.24 | 0.66 | 0.0% |
| -y | 952 | 29.0 | 532.8 | 0.24 | 0.70 | 0.0% |
| door +x+y (y wall) 0 | 725 | 1.2 | 536.3 | 0.81 | 1.44 | 44.4% |
| door +x+y (y wall) 1 | 706 | 1.4 | 565.8 | 0.75 | 1.44 | 33.3% |
| door +x+y (y wall) 2 | 411 | 0.9 | 593.8 | 0.41 | 1.20 | 16.7% |
| door +x+y (x wall) 0 | 718 | 1.0 | 546.6 | 0.79 | 1.50 | 38.2% |
| door +x+y (x wall) 1 | 715 | 0.7 | 551.8 | 0.78 | 1.56 | 35.7% |
| door +x+y (x wall) 2 | 352 | 1.0 | 587.3 | 0.36 | 1.38 | 15.3% |
| door +x+y (corner) | 212 | 0.9 | 587.9 | 0.22 | 1.38 | 11.9% |
| door -x+y (y wall) 0 | 732 | 1.0 | 550.4 | 0.80 | 1.56 | 48.2% |
| door -x+y (y wall) 1 | 707 | 0.7 | 592.9 | 0.71 | 1.44 | 38.3% |
| door -x+y (y wall) 2 | 382 | 0.9 | 579.3 | 0.39 | 1.26 | 15.3% |
| door -x+y (x wall) 0 | 726 | 1.0 | 548.7 | 0.79 | 1.56 | 41.1% |
| door -x+y (x wall) 1 | 717 | 0.7 | 566.3 | 0.76 | 1.50 | 35.1% |
| door -x+y (x wall) 2 | 389 | 0.9 | 593.1 | 0.39 | 1.38 | 16.7% |
| door -x+y (corner) | 200 | 0.9 | 596.3 | 0.20 | 1.44 | 10.0% |
| door -x-y (y wall) 0 | 719 | 1.0 | 542.2 | 0.79 | 1.44 | 43.6% |
| door -x-y (y wall) 1 | 708 | 1.0 | 562.5 | 0.75 | 1.50 | 35.1% |
| door -x-y (y wall) 2 | 371 | 1.0 | 573.2 | 0.39 | 1.26 | 17.2% |
| door -x-y (x wall) 0 | 718 | 0.7 | 541.5 | 0.79 | 1.56 | 40.0% |
| door -x-y (x wall) 1 | 710 | 1.0 | 559.2 | 0.76 | 1.56 | 40.4% |
| door -x-y (x wall) 2 | 384 | 0.9 | 584.9 | 0.39 | 1.38 | 15.3% |
| door -x-y (corner) | 227 | 1.2 | 567.2 | 0.24 | 1.44 | 12.3% |
| door +x-y (y wall) 0 | 728 | 0.9 | 550.1 | 0.79 | 1.44 | 42.9% |
| door +x-y (y wall) 1 | 711 | 1.0 | 560.2 | 0.76 | 1.44 | 35.1% |
| door +x-y (y wall) 2 | 368 | 0.9 | 577.5 | 0.38 | 1.44 | 19.0% |
| door +x-y (x wall) 0 | 728 | 0.7 | 545.4 | 0.80 | 1.38 | 43.6% |
| door +x-y (x wall) 1 | 704 | 0.7 | 562.2 | 0.75 | 1.50 | 42.1% |
| door +x-y (x wall) 2 | 394 | 0.7 | 563.4 | 0.42 | 1.38 | 15.8% |
| door +x-y (corner) | 222 | 0.9 | 573.9 | 0.23 | 1.32 | 8.6% |

Mean flow / w J averaged over the doors 0.59, over the avenues 0.24.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 966 | 612 / 354 / 217 | 0.2 | 533.3 | 2.22 | 3.71 | 87% | 81% | 6% | 4.11 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 546 | 587 / 0 / 8 | 0.7 | 562.8 | 1.06 | 1.50 | 79% | 68% | 11% | 3.76 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 80 | 326 / 0 / 4 | 0.7 | 590.8 | 0.56 | 1.40 | 17% | 13% | 3% | 2.96 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 947 | 609 / 338 / 194 | 0.5 | 543.8 | 2.10 | 3.61 | 91% | 80% | 11% | 4.13 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 557 | 595 / 0 / 7 | 0.7 | 548.9 | 1.10 | 1.50 | 82% | 70% | 12% | 3.74 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 78 | 265 / 0 / 0 | 0.7 | 584.4 | 0.45 | 1.20 | 17% | 14% | 3% | 3.22 |
| corner +x+y | 1.20 | 85.6 | 794 | 162 / 120 / 531 | 0.7 | 584.9 | 1.39 | 2.91 | 86% | 58% | 29% | 2.41 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 959 | 611 / 348 / 236 | 0.3 | 547.5 | 2.18 | 3.61 | 93% | 82% | 11% | 3.86 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 556 | 592 / 0 / 12 | 0.7 | 590.0 | 1.02 | 1.71 | 77% | 67% | 10% | 3.74 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 78 | 309 / 0 / 7 | 0.7 | 576.3 | 0.55 | 1.30 | 17% | 17% | 0% | 3.12 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 960 | 613 / 347 / 228 | 0.5 | 545.7 | 2.18 | 3.71 | 82% | 82% | 0% | 4.16 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 557 | 600 / 0 / 9 | 0.7 | 563.4 | 1.08 | 1.50 | 79% | 67% | 12% | 3.72 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 77 | 300 / 0 / 1 | 0.7 | 590.1 | 0.51 | 1.10 | 17% | 15% | 2% | 3.08 |
| corner -x+y | 1.20 | 85.6 | 779 | 135 / 111 / 561 | 0.7 | 592.4 | 1.36 | 2.91 | 85% | 60% | 25% | 2.43 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 958 | 606 / 353 / 227 | 0.2 | 539.2 | 2.20 | 3.71 | 82% | 82% | 0% | 4.32 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 559 | 593 / 0 / 8 | 0.7 | 559.5 | 1.08 | 1.50 | 81% | 68% | 12% | 3.69 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 76 | 285 / 0 / 7 | 0.7 | 570.2 | 0.51 | 1.20 | 16% | 12% | 3% | 3.16 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 948 | 599 / 349 / 184 | 0.2 | 538.5 | 2.10 | 3.81 | 84% | 78% | 5% | 4.12 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 576 | 602 / 0 / 8 | 0.7 | 556.2 | 1.10 | 1.50 | 82% | 70% | 12% | 3.79 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 75 | 287 / 0 / 0 | 0.7 | 581.9 | 0.49 | 1.20 | 17% | 15% | 2% | 3.19 |
| corner -x-y | 1.20 | 85.6 | 774 | 178 / 115 / 504 | 0.7 | 575.8 | 1.39 | 3.61 | 84% | 52% | 33% | 2.39 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 961 | 612 / 350 / 238 | 0.7 | 547.1 | 2.20 | 4.01 | 84% | 80% | 4% | 4.24 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 554 | 591 / 0 / 8 | 0.7 | 557.3 | 1.08 | 1.60 | 86% | 70% | 16% | 3.64 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 77 | 282 / 0 / 3 | 0.7 | 574.6 | 0.50 | 1.50 | 17% | 17% | 0% | 3.37 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 966 | 614 / 352 / 215 | 0.2 | 542.4 | 2.18 | 3.81 | 89% | 80% | 9% | 3.98 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 539 | 582 / 0 / 19 | 0.7 | 559.2 | 1.08 | 1.91 | 75% | 68% | 7% | 3.94 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 82 | 304 / 0 / 5 | 0.7 | 560.4 | 0.55 | 1.40 | 18% | 14% | 4% | 2.92 |
| corner +x-y | 1.20 | 85.6 | 788 | 166 / 115 / 542 | 0.7 | 570.2 | 1.44 | 3.11 | 84% | 59% | 26% | 2.45 |

The last agent out (agent 6387, t100 596.3 s): last gangway corner -x+y, exit door -x+y (corner). The gangway that cleared last: corner -x+y at 592.4 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.86 | 589.3 / 579.1 / 547.5 | 571.4 / 535.4 / 448.5 | 871858.7 | 1948010 | 0.198 |
| gangway | 1212 | 1112.9 | 6.86 | 585.8 / 571.2 / 498.0 | 571.4 / 535.4 / 448.5 | 837747.8 | 1625862 | 0.099 |
| walkway | 276 | 257.4 | 5.50 | 227.4 / 174.2 / 40.9 | 194.7 / 152.2 / 22.0 | 411.9 | 48625 | 0.523 |
| avenue | 912 | 858.9 | 2.53 | 249.9 / 29.4 / 0.0 | 199.7 / 1.4 / 0.0 | 0.0 | 110231 | 1.326 |
| exit | 32 | 3.2 | 0.00 | 575.1 / 571.9 / 518.6 | 326.2 / 298.4 / 181.0 | 1224.9 | 2197 | 1.195 |
| concourse | 1116 | 1043.8 | 6.10 | 525.6 / 117.7 / 76.6 | 211.1 / 116.3 / 55.6 | 32474.1 | 161095 | 0.316 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.60 | 523.5 / 509.2 / 503.9 | 513.5 / 509.2 / 500.2 | 902857.6 | 2451683 | 0.037 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -26.5 | 28.5 | gangway | 1.00 | 6.13 | 508.1 | 497.4 | 428.7 | 2520.6 | 0.018 |
| 2 | -27.5 | 28.5 | gangway | 1.00 | 6.06 | 514.2 | 502.5 | 422.7 | 2504.4 | 0.018 |
| 3 | -27.5 | -27.5 | gangway | 1.00 | 5.87 | 508.6 | 504.3 | 445.1 | 2490.3 | 0.016 |
| 4 | 27.5 | -27.5 | gangway | 1.00 | 6.04 | 502.3 | 493.9 | 426.2 | 2455.3 | 0.016 |
| 5 | 26.5 | -28.5 | gangway | 1.00 | 6.00 | 509.7 | 486.4 | 421.2 | 2445.7 | 0.018 |
| 6 | -28.5 | 26.5 | gangway | 1.00 | 6.00 | 513.4 | 482.9 | 421.2 | 2440.6 | 0.019 |
| 7 | -28.5 | 27.5 | gangway | 1.00 | 5.91 | 523.5 | 503.6 | 430.1 | 2435.9 | 0.019 |
| 8 | 28.5 | 26.5 | gangway | 1.00 | 5.98 | 510.4 | 498.5 | 425.7 | 2412.4 | 0.020 |
| 9 | 29.5 | 26.5 | gangway | 1.00 | 6.20 | 497.3 | 461.9 | 408.1 | 2412.0 | 0.021 |
| 10 | 28.5 | -26.5 | gangway | 1.00 | 6.08 | 486.8 | 464.4 | 420.7 | 2411.5 | 0.020 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -24.5 | 26.5 | seat row | 0.50 | 7.19 | 513.5 | 509.2 | 500.2 | 1725.6 | 0.014 |
| 2 | -26.5 | 24.5 | seat row | 0.50 | 7.19 | 498.3 | 490.6 | 478.9 | 1640.1 | 0.014 |
| 3 | 25.5 | 30.5 | seat row | 0.64 | 6.68 | 451.3 | 440.6 | 398.8 | 1624.0 | 0.024 |
| 4 | -30.5 | -25.5 | seat row | 0.64 | 6.44 | 458.8 | 445.0 | 411.4 | 1608.9 | 0.026 |
| 5 | 30.5 | 25.5 | seat row | 0.64 | 6.89 | 459.0 | 450.0 | 395.8 | 1597.0 | 0.026 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1743; agent-steps of seated agents on another row's clearway: 16199.

## Deposit check

Person-seconds deposited: 4405603.5, of them in excluded cells: 5909.886.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 540440 overlapping pair-steps: p99 0.0027, max 0.0263 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0027 max 0.0263; venue-geometry 12: p99 0.0007 max 0.0007 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 30 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.28 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 573 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
