# Experiment `M_load150_s5`

**Task 5.11 stage 1 (gridlock robustness, default model, AMD 26.10.1): venue M, the achievable maximum 121.42% (150% requested, seed 5)**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 19223 agents (load 121.4%, requested 150%): every one of the 15832 seats and 3391 standing (spawnOvercrowdedCrowd, seed 5; below), buffer N = 32768, 3368 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 1466596 evaluations, 59525 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.21)** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `15aa31e8667e4a9417fde7884d907d1832c5e2d6`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-23T17:53:24, 124.3 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Spawn (overcrowding)

| | |
|---|---|
| seated | 15832 (every seat) |
| standing | **3391** (requested round((1.50 - 1) x 15832) = 7916; at most 3391 = floor(2.5 p/m^2 x 1356.6 m^2)) |
| standing floor | walkway + rear concourse, 1356.6 m^2 |
| standing on the walkway / concourse / gangways | 635 / 2756 / 0 |
| **load** | **121.42%** of the seats (requested 150%; the floor takes no more: the achievable maximum) |
| standing crowd's mean density | 2.500 p/m^2 |
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 3.96, all circulation cells 3.96 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 5, 105784 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1191 | 208.3 |
| t90 | 2613 | 457.0 |
| t100 | 3368 | 589.1 |

t_p: the step by which ceil(p x 19223) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 958 | 93 | 29.0 | 533.6 | 20.1 | 65.9 | 28.9-38.8 |
| -x | 5.66 | 946 | 81 | 29.0 | 535.6 | 19.8 | 57.4 | 28.7-38.7 |
| +y | 5.66 | 964 | 91 | 29.0 | 528.4 | 20.5 | 62.7 | 28.9-38.8 |
| -y | 5.66 | 935 | 86 | 29.0 | 526.8 | 19.9 | 59.5 | 28.7-38.7 |
| door +x+y (y wall) 0 | 1.20 | 727 | 1269 | 0.9 | 542.9 | 67.0 | 120.4 | 99.5-109.5 |
| door +x+y (y wall) 1 | 1.20 | 725 | 799 | 0.9 | 561.5 | 64.6 | 125.4 | 106.5-116.5 |
| door +x+y (y wall) 2 | 1.20 | 366 | 271 | 1.2 | 575.8 | 31.8 | 110.3 | 63.7-73.6 |
| door +x+y (x wall) 0 | 1.20 | 732 | 1274 | 0.7 | 549.7 | 66.6 | 115.3 | 99.7-109.7 |
| door +x+y (x wall) 1 | 1.20 | 717 | 799 | 0.9 | 558.7 | 64.3 | 125.4 | 98.3-108.3 |
| door +x+y (x wall) 2 | 1.20 | 386 | 269 | 0.9 | 589.1 | 32.8 | 110.3 | 86.9-96.9 |
| door +x+y (corner) | 1.20 | 211 | 46 | 0.9 | 569.7 | 18.5 | 115.3 | 1.4-11.4 |
| door -x+y (y wall) 0 | 1.20 | 727 | 1266 | 0.9 | 540.5 | 67.3 | 120.4 | 95.5-105.5 |
| door -x+y (y wall) 1 | 1.20 | 714 | 793 | 1.4 | 555.7 | 64.4 | 130.4 | 102.7-112.6 |
| door -x+y (y wall) 2 | 1.20 | 396 | 268 | 1.0 | 569.1 | 34.8 | 100.3 | 0.3-10.3 |
| door -x+y (x wall) 0 | 1.20 | 720 | 1265 | 0.7 | 544.8 | 66.1 | 125.4 | 102.8-112.8 |
| door -x+y (x wall) 1 | 1.20 | 713 | 795 | 1.0 | 553.4 | 64.5 | 120.4 | 105.5-115.4 |
| door -x+y (x wall) 2 | 1.20 | 342 | 268 | 0.7 | 558.1 | 30.7 | 110.3 | 74.9-84.8 |
| door -x+y (corner) | 1.20 | 226 | 44 | 1.0 | 572.1 | 19.8 | 115.3 | 83.6-93.6 |
| door -x-y (y wall) 0 | 1.20 | 715 | 1273 | 0.9 | 545.0 | 65.7 | 130.4 | 95.8-105.8 |
| door -x-y (y wall) 1 | 1.20 | 716 | 794 | 0.9 | 544.0 | 65.9 | 120.4 | 109.5-119.5 |
| door -x-y (y wall) 2 | 1.20 | 403 | 268 | 0.9 | 580.3 | 34.8 | 110.3 | 68.0-78.0 |
| door -x-y (x wall) 0 | 1.20 | 729 | 1281 | 0.9 | 552.0 | 66.1 | 115.3 | 105.8-115.8 |
| door -x-y (x wall) 1 | 1.20 | 706 | 793 | 1.0 | 540.5 | 65.4 | 115.3 | 96.5-106.5 |
| door -x-y (x wall) 2 | 1.20 | 366 | 262 | 0.9 | 571.2 | 32.1 | 115.3 | 79.9-89.9 |
| door -x-y (corner) | 1.20 | 215 | 50 | 0.7 | 563.7 | 19.1 | 115.3 | 1.6-11.5 |
| door +x-y (y wall) 0 | 1.20 | 728 | 1266 | 1.0 | 543.4 | 67.1 | 115.3 | 103.0-113.0 |
| door +x-y (y wall) 1 | 1.20 | 690 | 794 | 1.0 | 566.0 | 61.0 | 120.4 | 106.2-116.1 |
| door +x-y (y wall) 2 | 1.20 | 377 | 266 | 0.9 | 572.8 | 32.9 | 110.3 | 71.0-81.0 |
| door +x-y (x wall) 0 | 1.20 | 727 | 1281 | 1.2 | 547.5 | 66.5 | 125.4 | 100.0-110.0 |
| door +x-y (x wall) 1 | 1.20 | 704 | 797 | 0.9 | 538.0 | 65.5 | 120.4 | 108.8-118.8 |
| door +x-y (x wall) 2 | 1.20 | 398 | 274 | 0.7 | 573.9 | 34.7 | 105.3 | 40.9-50.9 |
| door +x-y (corner) | 1.20 | 244 | 47 | 0.9 | 567.0 | 21.5 | 110.3 | 0.7-10.7 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 958 | 5.0% | 20.6% |
| -x | avenue | 5.66 | 946 | 4.9% | 20.4% |
| +y | avenue | 5.66 | 964 | 5.0% | 20.8% |
| -y | avenue | 5.66 | 935 | 4.9% | 20.1% |
| door +x+y (y wall) 0 | door | 1.20 | 727 | 3.8% | 73.8% |
| door +x+y (y wall) 1 | door | 1.20 | 725 | 3.8% | 73.6% |
| door +x+y (y wall) 2 | door | 1.20 | 366 | 1.9% | 37.2% |
| door +x+y (x wall) 0 | door | 1.20 | 732 | 3.8% | 74.3% |
| door +x+y (x wall) 1 | door | 1.20 | 717 | 3.7% | 72.8% |
| door +x+y (x wall) 2 | door | 1.20 | 386 | 2.0% | 39.2% |
| door +x+y (corner) | door | 1.20 | 211 | 1.1% | 21.4% |
| door -x+y (y wall) 0 | door | 1.20 | 727 | 3.8% | 73.8% |
| door -x+y (y wall) 1 | door | 1.20 | 714 | 3.7% | 72.5% |
| door -x+y (y wall) 2 | door | 1.20 | 396 | 2.1% | 40.2% |
| door -x+y (x wall) 0 | door | 1.20 | 720 | 3.7% | 73.1% |
| door -x+y (x wall) 1 | door | 1.20 | 713 | 3.7% | 72.4% |
| door -x+y (x wall) 2 | door | 1.20 | 342 | 1.8% | 34.7% |
| door -x+y (corner) | door | 1.20 | 226 | 1.2% | 22.9% |
| door -x-y (y wall) 0 | door | 1.20 | 715 | 3.7% | 72.6% |
| door -x-y (y wall) 1 | door | 1.20 | 716 | 3.7% | 72.7% |
| door -x-y (y wall) 2 | door | 1.20 | 403 | 2.1% | 40.9% |
| door -x-y (x wall) 0 | door | 1.20 | 729 | 3.8% | 74.0% |
| door -x-y (x wall) 1 | door | 1.20 | 706 | 3.7% | 71.7% |
| door -x-y (x wall) 2 | door | 1.20 | 366 | 1.9% | 37.2% |
| door -x-y (corner) | door | 1.20 | 215 | 1.1% | 21.8% |
| door +x-y (y wall) 0 | door | 1.20 | 728 | 3.8% | 73.9% |
| door +x-y (y wall) 1 | door | 1.20 | 690 | 3.6% | 70.1% |
| door +x-y (y wall) 2 | door | 1.20 | 377 | 2.0% | 38.3% |
| door +x-y (x wall) 0 | door | 1.20 | 727 | 3.8% | 73.8% |
| door +x-y (x wall) 1 | door | 1.20 | 704 | 3.7% | 71.5% |
| door +x-y (x wall) 2 | door | 1.20 | 398 | 2.1% | 40.4% |
| door +x-y (corner) | door | 1.20 | 244 | 1.3% | 24.8% |
| **doors (28)** | door | 33.60 | 15420 | 80.2% | |
| **avenues (4)** | avenue | 22.64 | 3803 | 19.8% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 589.1 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 41.6%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 960 | 5.0% | 960 | 5.0% |
| straight +x+y (y wing) 1 | straight | yes | 609 | 3.2% | 606 | 3.2% |
| straight +x+y (y wing) 2 | straight | yes | 284 | 1.5% | 278 | 1.4% |
| straight +x+y (x wing) 0 | straight | yes | 967 | 5.0% | 967 | 5.0% |
| straight +x+y (x wing) 1 | straight | yes | 604 | 3.1% | 598 | 3.1% |
| straight +x+y (x wing) 2 | straight | yes | 302 | 1.6% | 297 | 1.5% |
| corner +x+y | corner | yes | 778 | 4.0% | 264 | 1.4% |
| straight -x+y (y wing) 0 | straight | yes | 952 | 5.0% | 952 | 5.0% |
| straight -x+y (y wing) 1 | straight | yes | 607 | 3.2% | 601 | 3.1% |
| straight -x+y (y wing) 2 | straight | yes | 322 | 1.7% | 320 | 1.7% |
| straight -x+y (x wing) 0 | straight | yes | 966 | 5.0% | 966 | 5.0% |
| straight -x+y (x wing) 1 | straight | yes | 608 | 3.2% | 600 | 3.1% |
| straight -x+y (x wing) 2 | straight | yes | 256 | 1.3% | 252 | 1.3% |
| corner -x+y | corner | yes | 795 | 4.1% | 276 | 1.4% |
| straight -x-y (y wing) 0 | straight | yes | 964 | 5.0% | 964 | 5.0% |
| straight -x-y (y wing) 1 | straight | yes | 609 | 3.2% | 602 | 3.1% |
| straight -x-y (y wing) 2 | straight | yes | 315 | 1.6% | 313 | 1.6% |
| straight -x-y (x wing) 0 | straight | yes | 945 | 4.9% | 945 | 4.9% |
| straight -x-y (x wing) 1 | straight | yes | 603 | 3.1% | 595 | 3.1% |
| straight -x-y (x wing) 2 | straight | yes | 280 | 1.5% | 280 | 1.5% |
| corner -x-y | corner | yes | 779 | 4.1% | 269 | 1.4% |
| straight +x-y (y wing) 0 | straight | yes | 964 | 5.0% | 964 | 5.0% |
| straight +x-y (y wing) 1 | straight | yes | 595 | 3.1% | 584 | 3.0% |
| straight +x-y (y wing) 2 | straight | yes | 285 | 1.5% | 282 | 1.5% |
| straight +x-y (x wing) 0 | straight | yes | 948 | 4.9% | 948 | 4.9% |
| straight +x-y (x wing) 1 | straight | yes | 594 | 3.1% | 589 | 3.1% |
| straight +x-y (x wing) 2 | straight | yes | 306 | 1.6% | 302 | 1.6% |
| corner +x-y | corner | yes | 788 | 4.1% | 299 | 1.6% |
| **straight (24)** | | | 14845 | | 14765 | 76.8% |
| **corner (4)** | | | 3140 | | 1108 | 5.8% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 3350, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 958 | 29.0 | 533.6 | 0.24 | 0.79 | 0.0% |
| -x | 946 | 29.0 | 535.6 | 0.24 | 0.69 | 0.0% |
| +y | 964 | 29.0 | 528.4 | 0.24 | 0.75 | 0.0% |
| -y | 935 | 29.0 | 526.8 | 0.24 | 0.71 | 0.0% |
| door +x+y (y wall) 0 | 727 | 0.9 | 542.9 | 0.80 | 1.44 | 45.5% |
| door +x+y (y wall) 1 | 725 | 0.9 | 561.5 | 0.77 | 1.50 | 42.1% |
| door +x+y (y wall) 2 | 366 | 1.2 | 575.8 | 0.38 | 1.32 | 17.2% |
| door +x+y (x wall) 0 | 732 | 0.7 | 549.7 | 0.80 | 1.38 | 51.8% |
| door +x+y (x wall) 1 | 717 | 0.9 | 558.7 | 0.77 | 1.50 | 40.4% |
| door +x+y (x wall) 2 | 386 | 0.9 | 589.1 | 0.39 | 1.32 | 16.7% |
| door +x+y (corner) | 211 | 0.9 | 569.7 | 0.22 | 1.38 | 10.3% |
| door -x+y (y wall) 0 | 727 | 0.9 | 540.5 | 0.81 | 1.44 | 52.7% |
| door -x+y (y wall) 1 | 714 | 1.4 | 555.7 | 0.77 | 1.56 | 42.9% |
| door -x+y (y wall) 2 | 396 | 1.0 | 569.1 | 0.42 | 1.20 | 15.5% |
| door -x+y (x wall) 0 | 720 | 0.7 | 544.8 | 0.79 | 1.50 | 49.1% |
| door -x+y (x wall) 1 | 713 | 1.0 | 553.4 | 0.77 | 1.44 | 32.1% |
| door -x+y (x wall) 2 | 342 | 0.7 | 558.1 | 0.37 | 1.32 | 16.1% |
| door -x+y (corner) | 226 | 1.0 | 572.1 | 0.24 | 1.38 | 12.1% |
| door -x-y (y wall) 0 | 715 | 0.9 | 545.0 | 0.79 | 1.56 | 41.8% |
| door -x-y (y wall) 1 | 716 | 0.9 | 544.0 | 0.79 | 1.44 | 40.0% |
| door -x-y (y wall) 2 | 403 | 0.9 | 580.3 | 0.42 | 1.32 | 15.3% |
| door -x-y (x wall) 0 | 729 | 0.9 | 552.0 | 0.79 | 1.38 | 44.6% |
| door -x-y (x wall) 1 | 706 | 1.0 | 540.5 | 0.78 | 1.38 | 38.2% |
| door -x-y (x wall) 2 | 366 | 0.9 | 571.2 | 0.38 | 1.38 | 15.5% |
| door -x-y (corner) | 215 | 0.7 | 563.7 | 0.23 | 1.38 | 5.3% |
| door +x-y (y wall) 0 | 728 | 1.0 | 543.4 | 0.80 | 1.38 | 49.1% |
| door +x-y (y wall) 1 | 690 | 1.0 | 566.0 | 0.73 | 1.44 | 40.4% |
| door +x-y (y wall) 2 | 377 | 0.9 | 572.8 | 0.39 | 1.32 | 15.5% |
| door +x-y (x wall) 0 | 727 | 1.2 | 547.5 | 0.80 | 1.50 | 45.5% |
| door +x-y (x wall) 1 | 704 | 0.9 | 538.0 | 0.78 | 1.44 | 46.3% |
| door +x-y (x wall) 2 | 398 | 0.7 | 573.9 | 0.42 | 1.26 | 17.2% |
| door +x-y (corner) | 244 | 0.9 | 567.0 | 0.26 | 1.32 | 14.0% |

Mean flow / w J averaged over the doors 0.59, over the avenues 0.24.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 959 | 613 / 347 / 197 | 0.2 | 539.9 | 2.14 | 3.61 | 89% | 82% | 7% | 3.98 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 566 | 606 / 0 / 4 | 0.7 | 558.5 | 1.09 | 1.50 | 82% | 70% | 12% | 3.66 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 78 | 278 / 0 / 8 | 0.7 | 572.8 | 0.50 | 1.40 | 16% | 12% | 3% | 2.98 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 967 | 616 / 352 / 225 | 0.3 | 546.8 | 2.18 | 3.91 | 84% | 82% | 2% | 4.20 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 551 | 598 / 0 / 6 | 0.7 | 555.7 | 1.09 | 1.50 | 80% | 68% | 12% | 3.74 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 77 | 297 / 0 / 5 | 0.7 | 586.1 | 0.52 | 1.30 | 15% | 14% | 2% | 3.20 |
| corner +x+y | 1.20 | 85.6 | 772 | 158 / 107 / 530 | 0.7 | 580.2 | 1.37 | 3.41 | 86% | 56% | 31% | 2.39 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 952 | 617 / 337 / 192 | 0.5 | 537.5 | 2.13 | 3.81 | 93% | 81% | 11% | 3.93 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 556 | 601 / 0 / 7 | 0.7 | 552.7 | 1.10 | 1.50 | 82% | 68% | 14% | 3.72 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 76 | 320 / 0 / 2 | 0.7 | 566.2 | 0.57 | 1.40 | 16% | 12% | 4% | 3.17 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 966 | 608 / 358 / 223 | 0.3 | 535.2 | 2.22 | 3.91 | 93% | 80% | 13% | 3.85 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 559 | 600 / 0 / 10 | 0.7 | 550.4 | 1.11 | 1.60 | 84% | 70% | 14% | 3.78 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 75 | 252 / 0 / 5 | 0.7 | 555.2 | 0.46 | 1.10 | 16% | 12% | 4% | 3.01 |
| corner -x+y | 1.20 | 85.6 | 783 | 167 / 109 / 531 | 0.7 | 568.4 | 1.42 | 3.61 | 86% | 60% | 26% | 2.50 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 964 | 601 / 363 / 224 | 0.5 | 542.0 | 2.19 | 3.41 | 91% | 80% | 11% | 3.90 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 563 | 602 / 0 / 9 | 0.7 | 541.0 | 1.13 | 1.50 | 84% | 67% | 16% | 3.74 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 76 | 313 / 0 / 2 | 0.7 | 577.4 | 0.55 | 1.10 | 16% | 12% | 3% | 3.11 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 945 | 606 / 339 / 198 | 0.3 | 549.0 | 2.08 | 3.91 | 82% | 80% | 2% | 4.26 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 577 | 595 / 0 / 10 | 0.7 | 537.5 | 1.13 | 1.50 | 87% | 74% | 13% | 3.65 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 76 | 280 / 0 / 0 | 0.7 | 568.3 | 0.49 | 1.30 | 18% | 14% | 4% | 3.10 |
| corner -x-y | 1.20 | 85.6 | 767 | 165 / 104 / 519 | 0.7 | 571.2 | 1.38 | 3.41 | 86% | 50% | 36% | 2.36 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 964 | 616 / 348 / 214 | 0.3 | 540.5 | 2.18 | 3.81 | 82% | 80% | 2% | 4.27 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 559 | 584 / 0 / 14 | 0.7 | 563.0 | 1.06 | 1.50 | 79% | 68% | 11% | 3.76 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 77 | 282 / 0 / 3 | 0.7 | 569.8 | 0.50 | 1.20 | 17% | 10% | 7% | 2.76 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 948 | 604 / 346 / 205 | 0.3 | 544.5 | 2.12 | 4.11 | 82% | 80% | 2% | 4.24 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 568 | 589 / 0 / 15 | 0.7 | 535.0 | 1.13 | 1.60 | 87% | 72% | 15% | 3.68 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 78 | 302 / 0 / 4 | 0.7 | 570.9 | 0.54 | 1.30 | 17% | 12% | 5% | 2.93 |
| corner +x-y | 1.20 | 85.6 | 774 | 194 / 105 / 510 | 0.7 | 564.9 | 1.43 | 3.11 | 84% | 51% | 33% | 2.34 |

The last agent out (agent 2428, t100 589.1 s): last gangway straight +x+y (x wing) 2, exit door +x+y (x wall) 2. The gangway that cleared last: straight +x+y (x wing) 2 at 586.1 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.91 | 578.9 / 567.0 / 548.7 | 565.1 / 538.0 / 457.4 | 838000.6 | 1930223 | 0.199 |
| gangway | 1212 | 1112.9 | 6.91 | 578.9 / 559.4 / 504.1 | 565.1 / 538.0 / 457.4 | 805070.0 | 1610829 | 0.100 |
| walkway | 276 | 257.4 | 5.38 | 229.5 / 184.5 / 31.5 | 202.5 / 184.5 / 12.4 | 258.7 | 48826 | 0.514 |
| avenue | 912 | 858.9 | 2.47 | 253.4 / 21.0 / 0.0 | 200.4 / 0.9 / 0.0 | 0.0 | 109180 | 1.327 |
| exit | 32 | 3.2 | 0.00 | 565.5 / 564.1 / 519.3 | 327.4 / 300.0 / 180.9 | 1234.4 | 2198 | 1.194 |
| concourse | 1116 | 1043.8 | 6.05 | 519.5 / 116.0 / 79.1 | 212.0 / 115.3 / 56.3 | 31437.5 | 159191 | 0.321 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.62 | 514.9 / 505.0 / 490.8 | 513.2 / 505.0 / 487.1 | 914728.8 | 2451595 | 0.037 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -28.5 | -26.5 | gangway | 1.00 | 6.15 | 498.3 | 495.3 | 422.2 | 2419.6 | 0.016 |
| 2 | -27.5 | 27.5 | gangway | 1.00 | 5.89 | 493.9 | 490.6 | 439.9 | 2416.0 | 0.016 |
| 3 | 27.5 | 28.5 | gangway | 1.00 | 5.79 | 510.4 | 506.5 | 430.1 | 2410.2 | 0.018 |
| 4 | -26.5 | 29.5 | gangway | 1.00 | 6.05 | 493.8 | 469.4 | 407.9 | 2409.5 | 0.022 |
| 5 | -26.5 | -29.5 | gangway | 1.00 | 5.91 | 492.7 | 463.3 | 414.9 | 2382.7 | 0.022 |
| 6 | -29.5 | -26.5 | gangway | 1.00 | 6.19 | 498.8 | 475.7 | 409.8 | 2376.9 | 0.017 |
| 7 | 28.5 | 27.5 | gangway | 1.00 | 5.74 | 513.7 | 511.6 | 426.1 | 2374.3 | 0.014 |
| 8 | -26.5 | 28.5 | gangway | 1.00 | 5.99 | 503.9 | 485.4 | 417.5 | 2369.4 | 0.021 |
| 9 | 26.5 | 28.5 | gangway | 1.00 | 5.83 | 520.5 | 510.0 | 420.1 | 2364.3 | 0.018 |
| 10 | -28.5 | -27.5 | gangway | 1.00 | 5.83 | 498.8 | 495.3 | 415.8 | 2340.2 | 0.019 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 26.5 | 24.5 | seat row | 0.50 | 7.24 | 512.5 | 505.0 | 482.4 | 1703.3 | 0.013 |
| 2 | 24.5 | 26.5 | seat row | 0.50 | 7.22 | 513.2 | 500.8 | 484.1 | 1703.0 | 0.013 |
| 3 | 25.5 | 30.5 | seat row | 0.64 | 6.66 | 452.8 | 430.6 | 411.7 | 1661.5 | 0.025 |
| 4 | -24.5 | 26.5 | seat row | 0.50 | 7.19 | 503.2 | 502.7 | 487.1 | 1654.5 | 0.015 |
| 5 | 25.5 | 29.5 | seat row | 0.71 | 5.78 | 486.9 | 475.2 | 411.6 | 1652.1 | 0.018 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1680; agent-steps of seated agents on another row's clearway: 15359.

## Deposit check

Person-seconds deposited: 4387678.9, of them in excluded cells: 5861.256.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 482395 overlapping pair-steps: p99 0.0024, max 0.0220 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0024 max 0.0220; venue-geometry 12: p99 0.0007 max 0.0007 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 31 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.34 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 518 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
