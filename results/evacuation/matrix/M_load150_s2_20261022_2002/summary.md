# Experiment `M_load150_s2`

**Task 5.10 stage 4 (AMD 26.10.1): venue M, 150% requested (seed 2): every seat + standing on the walkway and concourse (M: the achievable maximum, also the 125% request)**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 19223 agents (load 121.4%, requested 150%): every one of the 15832 seats and 3391 standing (spawnOvercrowdedCrowd, seed 2; below), buffer N = 32768, 3387 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 1460993 evaluations, 59325 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.21)** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T20:02:59, 137.6 s wall.

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
| t50 | 1183 | 206.9 |
| t90 | 2603 | 455.3 |
| t100 | 3387 | 592.4 |

t_p: the step by which ceil(p x 19223) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 960 | 86 | 29.0 | 531.5 | 20.2 | 61.7 | 28.9-38.8 |
| -x | 5.66 | 956 | 84 | 29.0 | 529.3 | 20.3 | 58.5 | 28.9-38.8 |
| +y | 5.66 | 955 | 81 | 29.0 | 539.6 | 19.8 | 59.5 | 28.5-38.5 |
| -y | 5.66 | 958 | 91 | 29.0 | 526.1 | 20.4 | 59.5 | 28.9-38.8 |
| door +x+y (y wall) 0 | 1.20 | 718 | 1273 | 0.9 | 562.3 | 63.9 | 130.4 | 102.8-112.8 |
| door +x+y (y wall) 1 | 1.20 | 704 | 794 | 0.9 | 543.3 | 64.9 | 120.4 | 105.5-115.4 |
| door +x+y (y wall) 2 | 1.20 | 386 | 268 | 0.9 | 584.2 | 33.1 | 105.3 | 2.8-12.8 |
| door +x+y (x wall) 0 | 1.20 | 729 | 1275 | 0.7 | 545.9 | 66.8 | 115.3 | 101.4-111.4 |
| door +x+y (x wall) 1 | 1.20 | 699 | 798 | 0.9 | 543.1 | 64.4 | 135.4 | 98.6-108.6 |
| door +x+y (x wall) 2 | 1.20 | 382 | 270 | 1.0 | 584.9 | 32.7 | 110.3 | 26.4-36.4 |
| door +x+y (corner) | 1.20 | 232 | 44 | 0.9 | 587.5 | 19.8 | 120.4 | 3.3-13.3 |
| door -x+y (y wall) 0 | 1.20 | 738 | 1276 | 1.4 | 544.0 | 68.0 | 125.4 | 103.5-113.5 |
| door -x+y (y wall) 1 | 1.20 | 712 | 796 | 0.7 | 553.1 | 64.4 | 120.4 | 104.6-114.6 |
| door -x+y (y wall) 2 | 1.20 | 357 | 266 | 1.0 | 573.3 | 31.2 | 105.3 | 17.3-27.3 |
| door -x+y (x wall) 0 | 1.20 | 724 | 1275 | 0.9 | 530.8 | 68.3 | 120.4 | 112.3-122.3 |
| door -x+y (x wall) 1 | 1.20 | 723 | 790 | 0.9 | 553.1 | 65.4 | 125.4 | 98.3-108.3 |
| door -x+y (x wall) 2 | 1.20 | 385 | 276 | 1.0 | 587.9 | 32.8 | 110.3 | 58.2-68.2 |
| door -x+y (corner) | 1.20 | 209 | 47 | 0.9 | 578.8 | 18.1 | 120.4 | 68.9-78.9 |
| door -x-y (y wall) 0 | 1.20 | 727 | 1273 | 1.0 | 545.2 | 66.8 | 120.4 | 105.1-115.1 |
| door -x-y (y wall) 1 | 1.20 | 692 | 791 | 1.0 | 541.7 | 64.0 | 125.4 | 100.7-110.7 |
| door -x-y (y wall) 2 | 1.20 | 374 | 261 | 1.0 | 587.0 | 31.9 | 110.3 | 74.5-84.5 |
| door -x-y (x wall) 0 | 1.20 | 719 | 1275 | 1.2 | 551.1 | 65.4 | 125.4 | 110.4-120.3 |
| door -x-y (x wall) 1 | 1.20 | 713 | 799 | 0.7 | 550.3 | 64.8 | 125.4 | 104.1-114.0 |
| door -x-y (x wall) 2 | 1.20 | 400 | 261 | 1.4 | 592.4 | 33.8 | 110.3 | 60.5-70.5 |
| door -x-y (corner) | 1.20 | 213 | 51 | 0.7 | 569.7 | 18.7 | 110.3 | 0.5-10.5 |
| door +x-y (y wall) 0 | 1.20 | 727 | 1275 | 0.7 | 533.5 | 68.2 | 125.4 | 106.0-116.0 |
| door +x-y (y wall) 1 | 1.20 | 692 | 798 | 1.0 | 530.8 | 65.3 | 130.4 | 108.6-118.6 |
| door +x-y (y wall) 2 | 1.20 | 397 | 267 | 1.0 | 567.6 | 35.0 | 105.3 | 68.4-78.4 |
| door +x-y (x wall) 0 | 1.20 | 711 | 1266 | 1.0 | 548.9 | 64.9 | 125.4 | 87.3-97.2 |
| door +x-y (x wall) 1 | 1.20 | 706 | 801 | 0.9 | 538.4 | 65.7 | 120.4 | 100.2-110.2 |
| door +x-y (x wall) 2 | 1.20 | 393 | 270 | 1.0 | 566.3 | 34.7 | 115.3 | 61.9-71.9 |
| door +x-y (corner) | 1.20 | 232 | 45 | 0.9 | 545.2 | 21.3 | 115.3 | 0.7-10.7 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 960 | 5.0% | 20.5% |
| -x | avenue | 5.66 | 956 | 5.0% | 20.5% |
| +y | avenue | 5.66 | 955 | 5.0% | 20.4% |
| -y | avenue | 5.66 | 958 | 5.0% | 20.5% |
| door +x+y (y wall) 0 | door | 1.20 | 718 | 3.7% | 72.5% |
| door +x+y (y wall) 1 | door | 1.20 | 704 | 3.7% | 71.1% |
| door +x+y (y wall) 2 | door | 1.20 | 386 | 2.0% | 39.0% |
| door +x+y (x wall) 0 | door | 1.20 | 729 | 3.8% | 73.6% |
| door +x+y (x wall) 1 | door | 1.20 | 699 | 3.6% | 70.6% |
| door +x+y (x wall) 2 | door | 1.20 | 382 | 2.0% | 38.6% |
| door +x+y (corner) | door | 1.20 | 232 | 1.2% | 23.4% |
| door -x+y (y wall) 0 | door | 1.20 | 738 | 3.8% | 74.5% |
| door -x+y (y wall) 1 | door | 1.20 | 712 | 3.7% | 71.9% |
| door -x+y (y wall) 2 | door | 1.20 | 357 | 1.9% | 36.0% |
| door -x+y (x wall) 0 | door | 1.20 | 724 | 3.8% | 73.1% |
| door -x+y (x wall) 1 | door | 1.20 | 723 | 3.8% | 73.0% |
| door -x+y (x wall) 2 | door | 1.20 | 385 | 2.0% | 38.9% |
| door -x+y (corner) | door | 1.20 | 209 | 1.1% | 21.1% |
| door -x-y (y wall) 0 | door | 1.20 | 727 | 3.8% | 73.4% |
| door -x-y (y wall) 1 | door | 1.20 | 692 | 3.6% | 69.9% |
| door -x-y (y wall) 2 | door | 1.20 | 374 | 1.9% | 37.8% |
| door -x-y (x wall) 0 | door | 1.20 | 719 | 3.7% | 72.6% |
| door -x-y (x wall) 1 | door | 1.20 | 713 | 3.7% | 72.0% |
| door -x-y (x wall) 2 | door | 1.20 | 400 | 2.1% | 40.4% |
| door -x-y (corner) | door | 1.20 | 213 | 1.1% | 21.5% |
| door +x-y (y wall) 0 | door | 1.20 | 727 | 3.8% | 73.4% |
| door +x-y (y wall) 1 | door | 1.20 | 692 | 3.6% | 69.9% |
| door +x-y (y wall) 2 | door | 1.20 | 397 | 2.1% | 40.1% |
| door +x-y (x wall) 0 | door | 1.20 | 711 | 3.7% | 71.8% |
| door +x-y (x wall) 1 | door | 1.20 | 706 | 3.7% | 71.3% |
| door +x-y (x wall) 2 | door | 1.20 | 393 | 2.0% | 39.7% |
| door +x-y (corner) | door | 1.20 | 232 | 1.2% | 23.4% |
| **doors (28)** | door | 33.60 | 15394 | 80.1% | |
| **avenues (4)** | avenue | 22.64 | 3829 | 19.9% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 592.4 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 41.4%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 961 | 5.0% | 961 | 5.0% |
| straight +x+y (y wing) 1 | straight | yes | 599 | 3.1% | 592 | 3.1% |
| straight +x+y (y wing) 2 | straight | yes | 299 | 1.6% | 294 | 1.5% |
| straight +x+y (x wing) 0 | straight | yes | 953 | 5.0% | 951 | 4.9% |
| straight +x+y (x wing) 1 | straight | yes | 590 | 3.1% | 581 | 3.0% |
| straight +x+y (x wing) 2 | straight | yes | 290 | 1.5% | 290 | 1.5% |
| corner +x+y | corner | yes | 786 | 4.1% | 299 | 1.6% |
| straight -x+y (y wing) 0 | straight | yes | 965 | 5.0% | 965 | 5.0% |
| straight -x+y (y wing) 1 | straight | yes | 601 | 3.1% | 596 | 3.1% |
| straight -x+y (y wing) 2 | straight | yes | 287 | 1.5% | 283 | 1.5% |
| straight -x+y (x wing) 0 | straight | yes | 965 | 5.0% | 965 | 5.0% |
| straight -x+y (x wing) 1 | straight | yes | 617 | 3.2% | 613 | 3.2% |
| straight -x+y (x wing) 2 | straight | yes | 293 | 1.5% | 292 | 1.5% |
| corner -x+y | corner | yes | 772 | 4.0% | 254 | 1.3% |
| straight -x-y (y wing) 0 | straight | yes | 960 | 5.0% | 960 | 5.0% |
| straight -x-y (y wing) 1 | straight | yes | 597 | 3.1% | 588 | 3.1% |
| straight -x-y (y wing) 2 | straight | yes | 286 | 1.5% | 283 | 1.5% |
| straight -x-y (x wing) 0 | straight | yes | 954 | 5.0% | 954 | 5.0% |
| straight -x-y (x wing) 1 | straight | yes | 602 | 3.1% | 594 | 3.1% |
| straight -x-y (x wing) 2 | straight | yes | 320 | 1.7% | 317 | 1.6% |
| corner -x-y | corner | yes | 776 | 4.0% | 270 | 1.4% |
| straight +x-y (y wing) 0 | straight | yes | 946 | 4.9% | 946 | 4.9% |
| straight +x-y (y wing) 1 | straight | yes | 592 | 3.1% | 583 | 3.0% |
| straight +x-y (y wing) 2 | straight | yes | 303 | 1.6% | 303 | 1.6% |
| straight +x-y (x wing) 0 | straight | yes | 947 | 4.9% | 947 | 4.9% |
| straight +x-y (x wing) 1 | straight | yes | 596 | 3.1% | 588 | 3.1% |
| straight +x-y (x wing) 2 | straight | yes | 300 | 1.6% | 299 | 1.6% |
| corner +x-y | corner | yes | 805 | 4.2% | 299 | 1.6% |
| **straight (24)** | | | 14823 | | 14745 | 76.7% |
| **corner (4)** | | | 3139 | | 1122 | 5.8% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 3356, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 960 | 29.0 | 531.5 | 0.24 | 0.74 | 0.0% |
| -x | 956 | 29.0 | 529.3 | 0.24 | 0.70 | 0.0% |
| +y | 955 | 29.0 | 539.6 | 0.24 | 0.71 | 0.0% |
| -y | 958 | 29.0 | 526.1 | 0.24 | 0.71 | 0.0% |
| door +x+y (y wall) 0 | 718 | 0.9 | 562.3 | 0.76 | 1.56 | 43.9% |
| door +x+y (y wall) 1 | 704 | 0.9 | 543.3 | 0.78 | 1.44 | 41.8% |
| door +x+y (y wall) 2 | 386 | 0.9 | 584.2 | 0.40 | 1.26 | 15.3% |
| door +x+y (x wall) 0 | 729 | 0.7 | 545.9 | 0.80 | 1.38 | 47.3% |
| door +x+y (x wall) 1 | 699 | 0.9 | 543.1 | 0.77 | 1.62 | 34.5% |
| door +x+y (x wall) 2 | 382 | 1.0 | 584.9 | 0.39 | 1.32 | 15.3% |
| door +x+y (corner) | 232 | 0.9 | 587.5 | 0.24 | 1.44 | 8.5% |
| door -x+y (y wall) 0 | 738 | 1.4 | 544.0 | 0.81 | 1.50 | 56.4% |
| door -x+y (y wall) 1 | 712 | 0.7 | 553.1 | 0.77 | 1.44 | 37.5% |
| door -x+y (y wall) 2 | 357 | 1.0 | 573.3 | 0.37 | 1.26 | 15.5% |
| door -x+y (x wall) 0 | 724 | 0.9 | 530.8 | 0.82 | 1.44 | 53.7% |
| door -x+y (x wall) 1 | 723 | 0.9 | 553.1 | 0.78 | 1.50 | 41.1% |
| door -x+y (x wall) 2 | 385 | 1.0 | 587.9 | 0.39 | 1.32 | 15.3% |
| door -x+y (corner) | 209 | 0.9 | 578.8 | 0.22 | 1.44 | 8.5% |
| door -x-y (y wall) 0 | 727 | 1.0 | 545.2 | 0.80 | 1.44 | 49.1% |
| door -x-y (y wall) 1 | 692 | 1.0 | 541.7 | 0.77 | 1.50 | 36.4% |
| door -x-y (y wall) 2 | 374 | 1.0 | 587.0 | 0.38 | 1.32 | 15.3% |
| door -x-y (x wall) 0 | 719 | 1.2 | 551.1 | 0.78 | 1.50 | 44.6% |
| door -x-y (x wall) 1 | 713 | 0.7 | 550.3 | 0.78 | 1.50 | 33.9% |
| door -x-y (x wall) 2 | 400 | 1.4 | 592.4 | 0.40 | 1.32 | 13.3% |
| door -x-y (corner) | 213 | 0.7 | 569.7 | 0.22 | 1.32 | 8.6% |
| door +x-y (y wall) 0 | 727 | 0.7 | 533.5 | 0.82 | 1.50 | 48.1% |
| door +x-y (y wall) 1 | 692 | 1.0 | 530.8 | 0.78 | 1.56 | 46.3% |
| door +x-y (y wall) 2 | 397 | 1.0 | 567.6 | 0.42 | 1.26 | 15.8% |
| door +x-y (x wall) 0 | 711 | 1.0 | 548.9 | 0.78 | 1.50 | 37.5% |
| door +x-y (x wall) 1 | 706 | 0.9 | 538.4 | 0.79 | 1.44 | 48.1% |
| door +x-y (x wall) 2 | 393 | 1.0 | 566.3 | 0.42 | 1.38 | 15.8% |
| door +x-y (corner) | 232 | 0.9 | 545.2 | 0.25 | 1.38 | 9.1% |

Mean flow / w J averaged over the doors 0.60, over the avenues 0.24.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 959 | 602 / 359 / 220 | 0.5 | 559.4 | 2.11 | 3.61 | 77% | 77% | 0% | 4.27 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 560 | 592 / 0 / 10 | 0.7 | 540.3 | 1.12 | 1.50 | 82% | 73% | 9% | 3.79 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 76 | 294 / 0 / 5 | 0.7 | 581.2 | 0.51 | 1.30 | 17% | 12% | 5% | 2.80 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 953 | 609 / 345 / 221 | 0.5 | 542.9 | 2.17 | 3.81 | 84% | 82% | 2% | 4.31 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 568 | 581 / 0 / 12 | 0.7 | 540.3 | 1.10 | 1.40 | 87% | 73% | 15% | 3.64 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 78 | 290 / 0 / 0 | 0.7 | 581.9 | 0.50 | 1.30 | 17% | 14% | 3% | 3.10 |
| corner +x+y | 1.20 | 85.6 | 774 | 188 / 111 / 502 | 0.7 | 583.7 | 1.37 | 3.31 | 83% | 49% | 34% | 2.36 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 965 | 622 / 343 / 206 | 0.3 | 541.0 | 2.17 | 4.01 | 84% | 82% | 2% | 4.23 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 553 | 596 / 0 / 6 | 0.7 | 550.3 | 1.10 | 1.50 | 79% | 66% | 12% | 3.74 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 79 | 283 / 0 / 4 | 0.7 | 570.4 | 0.50 | 1.40 | 17% | 14% | 3% | 3.00 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 965 | 604 / 361 / 245 | 0.2 | 527.9 | 2.29 | 4.01 | 92% | 83% | 9% | 3.94 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 567 | 613 / 0 / 23 | 0.7 | 550.1 | 1.16 | 2.41 | 82% | 70% | 12% | 3.79 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 75 | 292 / 0 / 2 | 0.7 | 584.9 | 0.50 | 1.20 | 15% | 12% | 3% | 3.27 |
| corner -x+y | 1.20 | 85.6 | 764 | 143 / 111 / 545 | 0.7 | 578.9 | 1.38 | 3.21 | 85% | 61% | 24% | 2.47 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 960 | 609 / 351 / 227 | 0.5 | 542.2 | 2.19 | 3.81 | 91% | 80% | 11% | 3.93 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 567 | 588 / 0 / 10 | 0.7 | 538.7 | 1.11 | 1.50 | 82% | 73% | 9% | 3.83 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 76 | 283 / 0 / 3 | 0.7 | 584.0 | 0.49 | 1.20 | 17% | 12% | 5% | 2.84 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 954 | 602 / 352 / 235 | 0.2 | 548.2 | 2.17 | 3.61 | 82% | 80% | 2% | 4.19 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 566 | 594 / 0 / 11 | 0.7 | 547.3 | 1.11 | 1.71 | 85% | 71% | 15% | 3.72 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 80 | 317 / 0 / 3 | 0.7 | 589.4 | 0.54 | 1.30 | 17% | 12% | 5% | 2.76 |
| corner -x-y | 1.20 | 85.6 | 763 | 163 / 107 / 520 | 0.7 | 583.3 | 1.36 | 3.21 | 85% | 53% | 32% | 2.39 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 946 | 610 / 337 / 179 | 0.3 | 530.5 | 2.12 | 4.01 | 83% | 81% | 2% | 4.27 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 562 | 583 / 0 / 9 | 0.7 | 527.9 | 1.12 | 1.60 | 87% | 74% | 13% | 3.69 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 79 | 303 / 0 / 0 | 0.7 | 564.6 | 0.54 | 1.20 | 18% | 16% | 2% | 2.97 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 947 | 601 / 346 / 216 | 0.3 | 545.9 | 2.13 | 4.11 | 82% | 80% | 2% | 4.18 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 562 | 589 / 0 / 9 | 0.5 | 535.4 | 1.12 | 1.60 | 85% | 72% | 13% | 3.72 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 78 | 299 / 0 / 1 | 0.7 | 563.4 | 0.53 | 1.20 | 18% | 14% | 4% | 2.98 |
| corner +x-y | 1.20 | 85.6 | 791 | 183 / 116 / 511 | 0.7 | 558.7 | 1.45 | 3.81 | 86% | 53% | 33% | 2.35 |

The last agent out (agent 8368, t100 592.4 s): last gangway straight -x-y (x wing) 2, exit door -x-y (x wall) 2. The gangway that cleared last: straight -x-y (x wing) 2 at 589.4 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.86 | 583.8 / 571.4 / 536.1 | 571.2 / 538.9 / 445.3 | 831824.9 | 1924263 | 0.200 |
| gangway | 1212 | 1112.9 | 6.86 | 583.1 / 567.2 / 484.0 | 571.2 / 538.9 / 445.3 | 798040.1 | 1604758 | 0.100 |
| walkway | 276 | 257.4 | 5.41 | 217.2 / 172.8 / 26.1 | 186.5 / 154.4 / 14.7 | 165.8 | 46919 | 0.538 |
| avenue | 912 | 858.9 | 2.52 | 244.0 / 18.9 / 0.0 | 196.6 / 2.4 / 0.0 | 0.0 | 109935 | 1.326 |
| exit | 32 | 3.2 | 0.00 | 559.7 / 556.9 / 511.1 | 325.5 / 298.2 / 181.7 | 1227.1 | 2189 | 1.193 |
| concourse | 1116 | 1043.8 | 6.05 | 520.9 / 116.8 / 78.5 | 207.8 / 116.0 / 59.6 | 32391.9 | 160461 | 0.319 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.60 | 508.1 / 502.9 / 480.6 | 504.8 / 502.3 / 477.0 | 913470.6 | 2440911 | 0.037 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -27.5 | 27.5 | gangway | 1.00 | 5.97 | 501.3 | 493.6 | 445.3 | 2550.7 | 0.013 |
| 2 | -26.5 | 28.5 | gangway | 1.00 | 6.01 | 503.6 | 489.0 | 428.5 | 2458.9 | 0.018 |
| 3 | -29.5 | 26.5 | gangway | 1.00 | 6.37 | 509.3 | 454.2 | 404.2 | 2452.8 | 0.023 |
| 4 | -29.5 | -26.5 | gangway | 1.00 | 6.00 | 510.6 | 465.8 | 416.8 | 2426.0 | 0.018 |
| 5 | 29.5 | 26.5 | gangway | 1.00 | 5.93 | 496.0 | 487.8 | 421.0 | 2407.1 | 0.016 |
| 6 | 26.5 | 29.5 | gangway | 1.00 | 6.13 | 481.0 | 457.2 | 412.8 | 2402.5 | 0.019 |
| 7 | -28.5 | 26.5 | gangway | 1.00 | 5.96 | 508.3 | 494.5 | 416.1 | 2398.7 | 0.019 |
| 8 | -28.5 | -26.5 | gangway | 1.00 | 5.99 | 508.1 | 492.5 | 407.9 | 2367.2 | 0.018 |
| 9 | -26.5 | -28.5 | gangway | 1.00 | 5.77 | 503.7 | 489.4 | 423.8 | 2359.4 | 0.017 |
| 10 | 27.5 | -27.5 | gangway | 1.00 | 6.07 | 494.1 | 490.8 | 407.9 | 2324.3 | 0.020 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 30.5 | 25.5 | seat row | 0.64 | 6.61 | 469.6 | 458.8 | 416.6 | 1624.8 | 0.022 |
| 2 | -30.5 | -25.5 | seat row | 0.64 | 6.70 | 447.4 | 433.8 | 399.7 | 1610.1 | 0.023 |
| 3 | 30.5 | -25.5 | seat row | 0.64 | 6.71 | 456.7 | 442.3 | 393.4 | 1598.5 | 0.024 |
| 4 | 25.5 | 30.5 | seat row | 0.64 | 6.73 | 434.8 | 419.4 | 393.4 | 1585.4 | 0.025 |
| 5 | -26.5 | -9.5 | seat row | 0.50 | 7.44 | 453.5 | 451.3 | 441.6 | 1583.6 | 0.011 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1754; agent-steps of seated agents on another row's clearway: 18651.

## Deposit check

Person-seconds deposited: 4371058.0, of them in excluded cells: 5884.284.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 507418 overlapping pair-steps: p99 0.0025, max 0.0600 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0025 max 0.0600; venue-geometry 12: p99 0.0041 max 0.0041 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 31 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.37 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 560 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
