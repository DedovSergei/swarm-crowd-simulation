# Experiment `M_load150_s3`

**Task 5.9 stage 4: venue M, 150% requested (seed 3): every seat + standing on the walkway and concourse (M, L: the achievable maximum, also the 125% request)**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 19223 agents (load 121.4%, requested 150%): every one of the 15832 seats and 3391 standing (spawnOvercrowdedCrowd, seed 3; below), buffer N = 32768, 3409 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 1469596 evaluations, 59335 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.21)** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-20T23:22:52, 90.1 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Spawn (overcrowding)

| | |
|---|---|
| seated | 15832 (every seat) |
| standing | **3391** (requested round((1.50 - 1) x 15832) = 7916; at most 3391 = floor(2.5 p/m^2 x 1356.6 m^2)) |
| standing floor | walkway + rear concourse, 1356.6 m^2 |
| standing on the walkway / concourse / gangways | 626 / 2765 / 0 |
| **load** | **121.42%** of the seats (requested 150%; the floor takes no more: the achievable maximum) |
| standing crowd's mean density | 2.500 p/m^2 |
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 4.17, all circulation cells 4.17 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 3, 101938 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1190 | 208.1 |
| t90 | 2618 | 457.9 |
| t100 | 3409 | 596.3 |

t_p: the step by which ceil(p x 19223) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 957 | 86 | 29.0 | 530.7 | 20.2 | 65.9 | 28.3-38.3 |
| -x | 5.66 | 956 | 81 | 29.0 | 524.4 | 20.5 | 56.4 | 28.7-38.7 |
| +y | 5.66 | 949 | 80 | 29.0 | 539.4 | 19.7 | 56.4 | 28.5-38.5 |
| -y | 5.66 | 958 | 90 | 29.0 | 530.0 | 20.3 | 61.7 | 28.5-38.5 |
| door +x+y (y wall) 0 | 1.20 | 742 | 1280 | 0.9 | 557.1 | 66.7 | 130.4 | 109.1-119.1 |
| door +x+y (y wall) 1 | 1.20 | 717 | 801 | 0.9 | 578.8 | 62.0 | 125.4 | 107.6-117.5 |
| door +x+y (y wall) 2 | 1.20 | 356 | 269 | 1.4 | 594.7 | 30.0 | 100.3 | 20.8-30.8 |
| door +x+y (x wall) 0 | 1.20 | 723 | 1274 | 0.9 | 540.8 | 66.9 | 115.3 | 97.8-107.7 |
| door +x+y (x wall) 1 | 1.20 | 711 | 790 | 0.7 | 565.5 | 62.9 | 125.4 | 97.8-107.7 |
| door +x+y (x wall) 2 | 1.20 | 396 | 269 | 1.0 | 596.3 | 33.3 | 105.3 | 76.8-86.8 |
| door +x+y (corner) | 1.20 | 205 | 45 | 0.9 | 585.9 | 17.5 | 115.3 | 3.8-13.8 |
| door -x+y (y wall) 0 | 1.20 | 716 | 1269 | 1.0 | 536.3 | 66.9 | 125.4 | 108.4-118.4 |
| door -x+y (y wall) 1 | 1.20 | 704 | 797 | 1.0 | 557.6 | 63.2 | 130.4 | 100.7-110.7 |
| door -x+y (y wall) 2 | 1.20 | 394 | 265 | 0.7 | 562.2 | 35.1 | 115.3 | 77.1-87.1 |
| door -x+y (x wall) 0 | 1.20 | 726 | 1274 | 0.9 | 548.9 | 66.2 | 125.4 | 100.6-110.5 |
| door -x+y (x wall) 1 | 1.20 | 695 | 805 | 0.9 | 548.5 | 63.4 | 115.3 | 107.2-117.2 |
| door -x+y (x wall) 2 | 1.20 | 392 | 266 | 0.9 | 573.9 | 34.2 | 105.3 | 64.9-74.9 |
| door -x+y (corner) | 1.20 | 234 | 41 | 1.0 | 567.6 | 20.6 | 110.3 | 2.1-12.1 |
| door -x-y (y wall) 0 | 1.20 | 714 | 1270 | 1.0 | 525.8 | 68.0 | 125.4 | 100.9-110.9 |
| door -x-y (y wall) 1 | 1.20 | 715 | 800 | 0.9 | 543.4 | 65.9 | 120.4 | 102.8-112.8 |
| door -x-y (y wall) 2 | 1.20 | 385 | 271 | 1.0 | 569.7 | 33.8 | 110.3 | 26.4-36.4 |
| door -x-y (x wall) 0 | 1.20 | 721 | 1281 | 0.9 | 545.4 | 66.2 | 135.4 | 102.8-112.8 |
| door -x-y (x wall) 1 | 1.20 | 726 | 791 | 1.0 | 566.9 | 64.1 | 120.4 | 102.5-112.5 |
| door -x-y (x wall) 2 | 1.20 | 381 | 269 | 1.0 | 562.8 | 33.9 | 110.3 | 81.3-91.3 |
| door -x-y (corner) | 1.20 | 200 | 39 | 0.9 | 570.4 | 17.6 | 115.3 | 0.5-10.5 |
| door +x-y (y wall) 0 | 1.20 | 723 | 1269 | 1.0 | 540.3 | 67.0 | 120.4 | 97.4-107.4 |
| door +x-y (y wall) 1 | 1.20 | 717 | 799 | 0.9 | 538.2 | 66.7 | 125.4 | 99.3-109.3 |
| door +x-y (y wall) 2 | 1.20 | 400 | 266 | 0.9 | 582.3 | 34.4 | 120.4 | 80.8-90.8 |
| door +x-y (x wall) 0 | 1.20 | 725 | 1272 | 0.9 | 547.3 | 66.3 | 120.4 | 111.2-121.2 |
| door +x-y (x wall) 1 | 1.20 | 718 | 797 | 1.0 | 569.1 | 63.2 | 130.4 | 101.4-111.4 |
| door +x-y (x wall) 2 | 1.20 | 358 | 270 | 0.9 | 584.0 | 30.7 | 110.3 | 15.4-25.4 |
| door +x-y (corner) | 1.20 | 209 | 47 | 0.9 | 576.5 | 18.1 | 110.3 | 2.4-12.4 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 957 | 5.0% | 20.4% |
| -x | avenue | 5.66 | 956 | 5.0% | 20.3% |
| +y | avenue | 5.66 | 949 | 4.9% | 20.2% |
| -y | avenue | 5.66 | 958 | 5.0% | 20.4% |
| door +x+y (y wall) 0 | door | 1.20 | 742 | 3.9% | 74.4% |
| door +x+y (y wall) 1 | door | 1.20 | 717 | 3.7% | 71.9% |
| door +x+y (y wall) 2 | door | 1.20 | 356 | 1.9% | 35.7% |
| door +x+y (x wall) 0 | door | 1.20 | 723 | 3.8% | 72.5% |
| door +x+y (x wall) 1 | door | 1.20 | 711 | 3.7% | 71.3% |
| door +x+y (x wall) 2 | door | 1.20 | 396 | 2.1% | 39.7% |
| door +x+y (corner) | door | 1.20 | 205 | 1.1% | 20.6% |
| door -x+y (y wall) 0 | door | 1.20 | 716 | 3.7% | 71.8% |
| door -x+y (y wall) 1 | door | 1.20 | 704 | 3.7% | 70.6% |
| door -x+y (y wall) 2 | door | 1.20 | 394 | 2.0% | 39.5% |
| door -x+y (x wall) 0 | door | 1.20 | 726 | 3.8% | 72.8% |
| door -x+y (x wall) 1 | door | 1.20 | 695 | 3.6% | 69.7% |
| door -x+y (x wall) 2 | door | 1.20 | 392 | 2.0% | 39.3% |
| door -x+y (corner) | door | 1.20 | 234 | 1.2% | 23.5% |
| door -x-y (y wall) 0 | door | 1.20 | 714 | 3.7% | 71.6% |
| door -x-y (y wall) 1 | door | 1.20 | 715 | 3.7% | 71.7% |
| door -x-y (y wall) 2 | door | 1.20 | 385 | 2.0% | 38.6% |
| door -x-y (x wall) 0 | door | 1.20 | 721 | 3.8% | 72.3% |
| door -x-y (x wall) 1 | door | 1.20 | 726 | 3.8% | 72.8% |
| door -x-y (x wall) 2 | door | 1.20 | 381 | 2.0% | 38.2% |
| door -x-y (corner) | door | 1.20 | 200 | 1.0% | 20.1% |
| door +x-y (y wall) 0 | door | 1.20 | 723 | 3.8% | 72.5% |
| door +x-y (y wall) 1 | door | 1.20 | 717 | 3.7% | 71.9% |
| door +x-y (y wall) 2 | door | 1.20 | 400 | 2.1% | 40.1% |
| door +x-y (x wall) 0 | door | 1.20 | 725 | 3.8% | 72.7% |
| door +x-y (x wall) 1 | door | 1.20 | 718 | 3.7% | 72.0% |
| door +x-y (x wall) 2 | door | 1.20 | 358 | 1.9% | 35.9% |
| door +x-y (corner) | door | 1.20 | 209 | 1.1% | 21.0% |
| **doors (28)** | door | 33.60 | 15403 | 80.1% | |
| **avenues (4)** | avenue | 22.64 | 3820 | 19.9% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 596.3 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 41.1%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 960 | 5.0% | 960 | 5.0% |
| straight +x+y (y wing) 1 | straight | yes | 602 | 3.1% | 597 | 3.1% |
| straight +x+y (y wing) 2 | straight | yes | 282 | 1.5% | 278 | 1.4% |
| straight +x+y (x wing) 0 | straight | yes | 969 | 5.0% | 969 | 5.0% |
| straight +x+y (x wing) 1 | straight | yes | 606 | 3.2% | 602 | 3.1% |
| straight +x+y (x wing) 2 | straight | yes | 310 | 1.6% | 306 | 1.6% |
| corner +x+y | corner | yes | 767 | 4.0% | 253 | 1.3% |
| straight -x+y (y wing) 0 | straight | yes | 953 | 5.0% | 953 | 5.0% |
| straight -x+y (y wing) 1 | straight | yes | 608 | 3.2% | 600 | 3.1% |
| straight -x+y (y wing) 2 | straight | yes | 294 | 1.5% | 294 | 1.5% |
| straight -x+y (x wing) 0 | straight | yes | 939 | 4.9% | 939 | 4.9% |
| straight -x+y (x wing) 1 | straight | yes | 601 | 3.1% | 592 | 3.1% |
| straight -x+y (x wing) 2 | straight | yes | 284 | 1.5% | 283 | 1.5% |
| corner -x+y | corner | yes | 801 | 4.2% | 304 | 1.6% |
| straight -x-y (y wing) 0 | straight | yes | 941 | 4.9% | 941 | 4.9% |
| straight -x-y (y wing) 1 | straight | yes | 604 | 3.1% | 598 | 3.1% |
| straight -x-y (y wing) 2 | straight | yes | 294 | 1.5% | 291 | 1.5% |
| straight -x-y (x wing) 0 | straight | yes | 953 | 5.0% | 953 | 5.0% |
| straight -x-y (x wing) 1 | straight | yes | 616 | 3.2% | 615 | 3.2% |
| straight -x-y (x wing) 2 | straight | yes | 293 | 1.5% | 290 | 1.5% |
| corner -x-y | corner | yes | 797 | 4.1% | 279 | 1.5% |
| straight +x-y (y wing) 0 | straight | yes | 955 | 5.0% | 955 | 5.0% |
| straight +x-y (y wing) 1 | straight | yes | 603 | 3.1% | 598 | 3.1% |
| straight +x-y (y wing) 2 | straight | yes | 312 | 1.6% | 312 | 1.6% |
| straight +x-y (x wing) 0 | straight | yes | 958 | 5.0% | 958 | 5.0% |
| straight +x-y (x wing) 1 | straight | yes | 608 | 3.2% | 603 | 3.1% |
| straight +x-y (x wing) 2 | straight | yes | 278 | 1.4% | 272 | 1.4% |
| corner +x-y | corner | yes | 771 | 4.0% | 268 | 1.4% |
| **straight (24)** | | | 14823 | | 14759 | 76.8% |
| **corner (4)** | | | 3136 | | 1104 | 5.7% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 3360, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 957 | 29.0 | 530.7 | 0.24 | 0.79 | 0.0% |
| -x | 956 | 29.0 | 524.4 | 0.24 | 0.67 | 0.0% |
| +y | 949 | 29.0 | 539.4 | 0.24 | 0.67 | 0.0% |
| -y | 958 | 29.0 | 530.0 | 0.24 | 0.74 | 0.0% |
| door +x+y (y wall) 0 | 742 | 0.9 | 557.1 | 0.80 | 1.56 | 42.9% |
| door +x+y (y wall) 1 | 717 | 0.9 | 578.8 | 0.74 | 1.50 | 33.9% |
| door +x+y (y wall) 2 | 356 | 1.4 | 594.7 | 0.36 | 1.20 | 13.3% |
| door +x+y (x wall) 0 | 723 | 0.9 | 540.8 | 0.80 | 1.38 | 47.3% |
| door +x+y (x wall) 1 | 711 | 0.7 | 565.5 | 0.75 | 1.50 | 29.8% |
| door +x+y (x wall) 2 | 396 | 1.0 | 596.3 | 0.40 | 1.26 | 16.7% |
| door +x+y (corner) | 205 | 0.9 | 585.9 | 0.21 | 1.38 | 8.5% |
| door -x+y (y wall) 0 | 716 | 1.0 | 536.3 | 0.80 | 1.50 | 51.9% |
| door -x+y (y wall) 1 | 704 | 1.0 | 557.6 | 0.76 | 1.56 | 30.4% |
| door -x+y (y wall) 2 | 394 | 0.7 | 562.2 | 0.42 | 1.38 | 15.8% |
| door -x+y (x wall) 0 | 726 | 0.9 | 548.9 | 0.79 | 1.50 | 48.2% |
| door -x+y (x wall) 1 | 695 | 0.9 | 548.5 | 0.76 | 1.38 | 41.1% |
| door -x+y (x wall) 2 | 392 | 0.9 | 573.9 | 0.41 | 1.26 | 17.2% |
| door -x+y (corner) | 234 | 1.0 | 567.6 | 0.25 | 1.32 | 12.3% |
| door -x-y (y wall) 0 | 714 | 1.0 | 525.8 | 0.81 | 1.50 | 43.4% |
| door -x-y (y wall) 1 | 715 | 0.9 | 543.4 | 0.79 | 1.44 | 38.2% |
| door -x-y (y wall) 2 | 385 | 1.0 | 569.7 | 0.40 | 1.32 | 15.5% |
| door -x-y (x wall) 0 | 721 | 0.9 | 545.4 | 0.79 | 1.62 | 54.5% |
| door -x-y (x wall) 1 | 726 | 1.0 | 566.9 | 0.77 | 1.44 | 36.8% |
| door -x-y (x wall) 2 | 381 | 1.0 | 562.8 | 0.41 | 1.32 | 17.5% |
| door -x-y (corner) | 200 | 0.9 | 570.4 | 0.21 | 1.38 | 12.1% |
| door +x-y (y wall) 0 | 723 | 1.0 | 540.3 | 0.80 | 1.44 | 47.3% |
| door +x-y (y wall) 1 | 717 | 0.9 | 538.2 | 0.80 | 1.50 | 37.0% |
| door +x-y (y wall) 2 | 400 | 0.9 | 582.3 | 0.41 | 1.44 | 15.3% |
| door +x-y (x wall) 0 | 725 | 0.9 | 547.3 | 0.79 | 1.44 | 45.5% |
| door +x-y (x wall) 1 | 718 | 1.0 | 569.1 | 0.76 | 1.56 | 29.3% |
| door +x-y (x wall) 2 | 358 | 0.9 | 584.0 | 0.37 | 1.32 | 15.3% |
| door +x-y (corner) | 209 | 0.9 | 576.5 | 0.22 | 1.32 | 8.6% |

Mean flow / w J averaged over the doors 0.59, over the avenues 0.24.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 960 | 620 / 341 / 208 | 0.7 | 554.1 | 2.11 | 3.41 | 91% | 82% | 9% | 3.90 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 564 | 597 / 0 / 13 | 0.7 | 575.8 | 1.06 | 1.50 | 79% | 69% | 10% | 3.74 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 78 | 278 / 0 / 4 | 0.7 | 591.7 | 0.48 | 1.50 | 17% | 17% | 0% | 3.28 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 969 | 608 / 362 / 263 | 0.2 | 537.8 | 2.29 | 4.11 | 83% | 81% | 2% | 4.29 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 563 | 602 / 0 / 13 | 0.7 | 562.5 | 1.09 | 1.50 | 82% | 68% | 14% | 3.73 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 75 | 306 / 0 / 6 | 0.7 | 593.3 | 0.53 | 1.20 | 15% | 10% | 5% | 2.88 |
| corner +x+y | 1.20 | 85.6 | 756 | 144 / 109 / 537 | 0.7 | 587.3 | 1.35 | 3.11 | 86% | 58% | 29% | 2.43 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 953 | 600 / 353 / 229 | 0.5 | 533.3 | 2.22 | 4.21 | 91% | 80% | 11% | 3.97 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 561 | 600 / 0 / 13 | 0.7 | 554.6 | 1.11 | 1.60 | 84% | 70% | 14% | 3.64 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 77 | 294 / 0 / 0 | 0.7 | 559.2 | 0.53 | 1.30 | 16% | 14% | 2% | 2.95 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 939 | 609 / 330 / 178 | 0.5 | 545.9 | 2.05 | 3.71 | 91% | 80% | 11% | 3.90 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 569 | 592 / 0 / 12 | 0.7 | 545.5 | 1.11 | 1.50 | 85% | 75% | 11% | 3.78 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 79 | 283 / 0 / 1 | 0.7 | 570.9 | 0.50 | 1.20 | 17% | 14% | 3% | 2.99 |
| corner -x+y | 1.20 | 85.6 | 787 | 192 / 112 / 509 | 0.7 | 564.8 | 1.44 | 3.71 | 88% | 54% | 33% | 2.42 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 941 | 602 / 339 / 187 | 0.3 | 522.8 | 2.16 | 3.81 | 85% | 85% | 0% | 4.33 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 567 | 599 / 0 / 8 | 0.7 | 540.5 | 1.12 | 1.50 | 84% | 71% | 13% | 3.69 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 78 | 291 / 0 / 3 | 0.7 | 566.7 | 0.52 | 1.30 | 16% | 14% | 2% | 3.10 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 953 | 602 / 352 / 236 | 0.5 | 542.4 | 2.20 | 4.21 | 82% | 80% | 2% | 4.31 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 564 | 615 / 0 / 5 | 0.7 | 563.9 | 1.10 | 1.50 | 81% | 67% | 14% | 3.73 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 75 | 290 / 0 / 3 | 0.7 | 559.9 | 0.52 | 1.20 | 18% | 16% | 2% | 2.98 |
| corner -x-y | 1.20 | 85.6 | 789 | 159 / 120 / 529 | 0.7 | 566.5 | 1.43 | 3.71 | 88% | 56% | 32% | 2.45 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 955 | 608 / 347 / 244 | 0.3 | 537.3 | 2.23 | 4.01 | 83% | 81% | 2% | 4.31 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 566 | 598 / 0 / 8 | 0.7 | 535.4 | 1.13 | 1.50 | 87% | 74% | 13% | 3.87 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 77 | 312 / 0 / 0 | 0.7 | 579.3 | 0.54 | 1.20 | 17% | 14% | 3% | 3.17 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 958 | 611 / 347 / 213 | 0.3 | 544.3 | 2.15 | 3.71 | 82% | 82% | 0% | 4.28 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 572 | 603 / 0 / 7 | 0.7 | 566.2 | 1.08 | 1.50 | 81% | 70% | 11% | 3.74 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 75 | 272 / 0 / 10 | 0.7 | 581.0 | 0.49 | 1.40 | 14% | 12% | 2% | 2.96 |
| corner +x-y | 1.20 | 85.6 | 763 | 154 / 114 / 520 | 0.7 | 575.1 | 1.37 | 3.11 | 84% | 57% | 28% | 2.42 |

The last agent out (agent 453, t100 596.3 s): last gangway straight +x+y (x wing) 2, exit door +x+y (x wall) 2. The gangway that cleared last: straight +x+y (x wing) 2 at 593.3 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.99 | 587.9 / 576.0 / 549.0 | 574.9 / 546.6 / 463.7 | 855889.1 | 1939535 | 0.199 |
| gangway | 1212 | 1112.9 | 6.99 | 587.9 / 569.5 / 495.9 | 574.9 / 546.6 / 463.7 | 822523.4 | 1619678 | 0.099 |
| walkway | 276 | 257.4 | 5.36 | 230.9 / 183.7 / 18.4 | 205.7 / 171.4 / 6.6 | 138.5 | 47150 | 0.536 |
| avenue | 912 | 858.9 | 2.59 | 253.3 / 11.9 / 0.0 | 200.4 / 1.4 / 0.0 | 0.0 | 109667 | 1.327 |
| exit | 32 | 3.2 | 0.00 | 571.6 / 569.0 / 518.2 | 328.3 / 297.9 / 181.2 | 1230.9 | 2191 | 1.196 |
| concourse | 1116 | 1043.8 | 6.06 | 531.5 / 125.6 / 76.6 | 212.5 / 115.8 / 57.9 | 31996.2 | 160849 | 0.319 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.52 | 518.2 / 507.8 / 496.6 | 513.2 / 507.8 / 492.9 | 918990.4 | 2451174 | 0.037 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 28.5 | 26.5 | gangway | 1.00 | 6.28 | 520.3 | 509.0 | 452.1 | 2674.7 | 0.018 |
| 2 | 26.5 | -29.5 | gangway | 1.00 | 6.19 | 488.0 | 473.5 | 414.5 | 2459.7 | 0.018 |
| 3 | -26.5 | -28.5 | gangway | 1.00 | 6.11 | 503.2 | 494.6 | 418.7 | 2449.9 | 0.017 |
| 4 | 26.5 | 28.5 | gangway | 1.00 | 5.83 | 516.3 | 513.2 | 431.7 | 2400.7 | 0.017 |
| 5 | -29.5 | 26.5 | gangway | 1.00 | 6.13 | 503.9 | 474.3 | 409.5 | 2396.2 | 0.019 |
| 6 | -28.5 | -27.5 | gangway | 1.00 | 5.88 | 521.0 | 515.5 | 423.4 | 2393.2 | 0.019 |
| 7 | -28.5 | 26.5 | gangway | 1.00 | 6.17 | 504.6 | 498.5 | 404.6 | 2389.4 | 0.020 |
| 8 | 29.5 | -26.5 | gangway | 1.00 | 5.98 | 496.6 | 463.7 | 406.1 | 2387.2 | 0.017 |
| 9 | -27.5 | -27.5 | gangway | 1.00 | 5.82 | 517.7 | 503.7 | 424.1 | 2378.9 | 0.017 |
| 10 | -28.5 | -26.5 | gangway | 1.00 | 6.06 | 508.5 | 497.8 | 422.4 | 2375.9 | 0.022 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 24.5 | 26.5 | seat row | 0.50 | 7.13 | 510.0 | 507.8 | 492.9 | 1671.2 | 0.014 |
| 2 | 25.5 | -30.5 | seat row | 0.64 | 6.78 | 443.7 | 433.1 | 408.9 | 1664.8 | 0.024 |
| 3 | -24.5 | -26.5 | seat row | 0.50 | 7.18 | 505.0 | 504.1 | 487.5 | 1642.4 | 0.015 |
| 4 | 25.5 | -29.5 | seat row | 0.71 | 5.71 | 481.3 | 472.1 | 410.9 | 1617.1 | 0.019 |
| 5 | -24.5 | 26.5 | seat row | 0.50 | 7.20 | 503.2 | 499.0 | 475.7 | 1616.2 | 0.014 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1761; agent-steps of seated agents on another row's clearway: 16933.

## Deposit check

Person-seconds deposited: 4396562.2, of them in excluded cells: 5853.190.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 514576 overlapping pair-steps: p99 0.0024, max 0.0304 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0024 max 0.0304; venue-geometry 4: p99 0.0007 max 0.0007 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 19 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.28 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 551 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
