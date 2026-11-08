# Experiment `M_load150_s8`

**Task 5.11 stage 1 (gridlock robustness, default model, AMD 26.10.1): venue M, the achievable maximum 121.42% (150% requested, seed 8)**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 19223 agents (load 121.4%, requested 150%): every one of the 15832 seats and 3391 standing (spawnOvercrowdedCrowd, seed 8; below), buffer N = 32768, 3366 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 1474449 evaluations, 60018 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.21)** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `15aa31e8667e4a9417fde7884d907d1832c5e2d6`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-23T18:00:05, 100.5 s wall.

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
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 3.83, all circulation cells 3.83 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 8, 106460 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1200 | 209.9 |
| t90 | 2624 | 459.0 |
| t100 | 3366 | 588.7 |

t_p: the step by which ceil(p x 19223) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 956 | 90 | 29.0 | 523.5 | 20.5 | 64.9 | 28.9-38.8 |
| -x | 5.66 | 965 | 84 | 29.0 | 531.4 | 20.4 | 54.2 | 28.3-38.3 |
| +y | 5.66 | 962 | 87 | 29.0 | 535.2 | 20.1 | 58.5 | 28.9-38.8 |
| -y | 5.66 | 953 | 81 | 29.0 | 526.3 | 20.3 | 55.3 | 28.3-38.3 |
| door +x+y (y wall) 0 | 1.20 | 720 | 1268 | 1.2 | 535.4 | 67.4 | 125.4 | 97.6-107.6 |
| door +x+y (y wall) 1 | 1.20 | 719 | 799 | 0.9 | 547.1 | 65.8 | 120.4 | 97.9-107.9 |
| door +x+y (y wall) 2 | 1.20 | 363 | 265 | 1.0 | 565.1 | 32.2 | 115.3 | 68.9-78.9 |
| door +x+y (x wall) 0 | 1.20 | 723 | 1270 | 0.9 | 539.6 | 67.1 | 120.4 | 102.3-112.3 |
| door +x+y (x wall) 1 | 1.20 | 714 | 792 | 1.4 | 551.3 | 64.9 | 120.4 | 109.5-119.5 |
| door +x+y (x wall) 2 | 1.20 | 379 | 270 | 0.9 | 576.3 | 32.9 | 100.3 | 24.5-34.5 |
| door +x+y (corner) | 1.20 | 222 | 43 | 0.9 | 579.5 | 19.2 | 115.3 | 8.0-18.0 |
| door -x+y (y wall) 0 | 1.20 | 742 | 1275 | 0.7 | 544.3 | 68.2 | 125.4 | 108.6-118.6 |
| door -x+y (y wall) 1 | 1.20 | 735 | 798 | 0.9 | 563.5 | 65.3 | 130.4 | 102.0-111.9 |
| door -x+y (y wall) 2 | 1.20 | 330 | 277 | 0.9 | 579.5 | 28.5 | 110.3 | 51.4-61.4 |
| door -x+y (x wall) 0 | 1.20 | 729 | 1273 | 0.9 | 544.7 | 67.0 | 120.4 | 107.2-117.2 |
| door -x+y (x wall) 1 | 1.20 | 727 | 800 | 0.7 | 562.7 | 64.7 | 120.4 | 104.4-114.4 |
| door -x+y (x wall) 2 | 1.20 | 387 | 270 | 1.4 | 567.2 | 34.2 | 110.3 | 52.3-62.3 |
| door -x+y (corner) | 1.20 | 213 | 43 | 1.0 | 583.7 | 18.3 | 110.3 | 7.7-17.7 |
| door -x-y (y wall) 0 | 1.20 | 724 | 1276 | 0.9 | 536.6 | 67.5 | 130.4 | 97.2-107.2 |
| door -x-y (y wall) 1 | 1.20 | 715 | 792 | 0.9 | 549.7 | 65.1 | 125.4 | 96.0-106.0 |
| door -x-y (y wall) 2 | 1.20 | 380 | 267 | 0.9 | 583.3 | 32.6 | 115.3 | 70.8-80.8 |
| door -x-y (x wall) 0 | 1.20 | 725 | 1275 | 1.0 | 542.2 | 67.0 | 120.4 | 102.7-112.6 |
| door -x-y (x wall) 1 | 1.20 | 706 | 793 | 1.0 | 548.0 | 64.5 | 130.4 | 92.2-102.1 |
| door -x-y (x wall) 2 | 1.20 | 390 | 267 | 0.7 | 575.6 | 33.9 | 120.4 | 82.6-92.5 |
| door -x-y (corner) | 1.20 | 193 | 46 | 0.9 | 571.4 | 16.9 | 110.3 | 0.5-10.5 |
| door +x-y (y wall) 0 | 1.20 | 726 | 1280 | 0.9 | 541.3 | 67.1 | 115.3 | 103.2-113.2 |
| door +x-y (y wall) 1 | 1.20 | 721 | 795 | 1.0 | 565.3 | 63.9 | 125.4 | 103.7-113.7 |
| door +x-y (y wall) 2 | 1.20 | 376 | 264 | 0.9 | 585.6 | 32.1 | 100.3 | 9.1-19.1 |
| door +x-y (x wall) 0 | 1.20 | 722 | 1270 | 0.9 | 545.2 | 66.3 | 130.4 | 106.9-116.8 |
| door +x-y (x wall) 1 | 1.20 | 721 | 795 | 0.9 | 564.8 | 63.9 | 130.4 | 101.8-111.8 |
| door +x-y (x wall) 2 | 1.20 | 361 | 273 | 0.7 | 585.4 | 30.9 | 105.3 | 32.9-42.9 |
| door +x-y (corner) | 1.20 | 224 | 45 | 0.9 | 588.7 | 19.0 | 115.3 | 2.4-12.4 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 956 | 5.0% | 20.6% |
| -x | avenue | 5.66 | 965 | 5.0% | 20.8% |
| +y | avenue | 5.66 | 962 | 5.0% | 20.7% |
| -y | avenue | 5.66 | 953 | 5.0% | 20.5% |
| door +x+y (y wall) 0 | door | 1.20 | 720 | 3.7% | 73.1% |
| door +x+y (y wall) 1 | door | 1.20 | 719 | 3.7% | 73.0% |
| door +x+y (y wall) 2 | door | 1.20 | 363 | 1.9% | 36.9% |
| door +x+y (x wall) 0 | door | 1.20 | 723 | 3.8% | 73.4% |
| door +x+y (x wall) 1 | door | 1.20 | 714 | 3.7% | 72.5% |
| door +x+y (x wall) 2 | door | 1.20 | 379 | 2.0% | 38.5% |
| door +x+y (corner) | door | 1.20 | 222 | 1.2% | 22.6% |
| door -x+y (y wall) 0 | door | 1.20 | 742 | 3.9% | 75.4% |
| door -x+y (y wall) 1 | door | 1.20 | 735 | 3.8% | 74.7% |
| door -x+y (y wall) 2 | door | 1.20 | 330 | 1.7% | 33.5% |
| door -x+y (x wall) 0 | door | 1.20 | 729 | 3.8% | 74.1% |
| door -x+y (x wall) 1 | door | 1.20 | 727 | 3.8% | 73.9% |
| door -x+y (x wall) 2 | door | 1.20 | 387 | 2.0% | 39.3% |
| door -x+y (corner) | door | 1.20 | 213 | 1.1% | 21.6% |
| door -x-y (y wall) 0 | door | 1.20 | 724 | 3.8% | 73.5% |
| door -x-y (y wall) 1 | door | 1.20 | 715 | 3.7% | 72.6% |
| door -x-y (y wall) 2 | door | 1.20 | 380 | 2.0% | 38.6% |
| door -x-y (x wall) 0 | door | 1.20 | 725 | 3.8% | 73.7% |
| door -x-y (x wall) 1 | door | 1.20 | 706 | 3.7% | 71.7% |
| door -x-y (x wall) 2 | door | 1.20 | 390 | 2.0% | 39.6% |
| door -x-y (corner) | door | 1.20 | 193 | 1.0% | 19.6% |
| door +x-y (y wall) 0 | door | 1.20 | 726 | 3.8% | 73.8% |
| door +x-y (y wall) 1 | door | 1.20 | 721 | 3.8% | 73.2% |
| door +x-y (y wall) 2 | door | 1.20 | 376 | 2.0% | 38.2% |
| door +x-y (x wall) 0 | door | 1.20 | 722 | 3.8% | 73.3% |
| door +x-y (x wall) 1 | door | 1.20 | 721 | 3.8% | 73.2% |
| door +x-y (x wall) 2 | door | 1.20 | 361 | 1.9% | 36.7% |
| door +x-y (corner) | door | 1.20 | 224 | 1.2% | 22.8% |
| **doors (28)** | door | 33.60 | 15387 | 80.0% | |
| **avenues (4)** | avenue | 22.64 | 3836 | 20.0% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 588.7 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 41.7%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 958 | 5.0% | 958 | 5.0% |
| straight +x+y (y wing) 1 | straight | yes | 604 | 3.1% | 600 | 3.1% |
| straight +x+y (y wing) 2 | straight | yes | 280 | 1.5% | 279 | 1.5% |
| straight +x+y (x wing) 0 | straight | yes | 952 | 5.0% | 952 | 5.0% |
| straight +x+y (x wing) 1 | straight | yes | 609 | 3.2% | 602 | 3.1% |
| straight +x+y (x wing) 2 | straight | yes | 307 | 1.6% | 300 | 1.6% |
| corner +x+y | corner | yes | 798 | 4.2% | 276 | 1.4% |
| straight -x+y (y wing) 0 | straight | yes | 958 | 5.0% | 958 | 5.0% |
| straight -x+y (y wing) 1 | straight | yes | 622 | 3.2% | 617 | 3.2% |
| straight -x+y (y wing) 2 | straight | yes | 239 | 1.2% | 233 | 1.2% |
| straight -x+y (x wing) 0 | straight | yes | 968 | 5.0% | 968 | 5.0% |
| straight -x+y (x wing) 1 | straight | yes | 613 | 3.2% | 608 | 3.2% |
| straight -x+y (x wing) 2 | straight | yes | 298 | 1.6% | 294 | 1.5% |
| corner -x+y | corner | yes | 786 | 4.1% | 289 | 1.5% |
| straight -x-y (y wing) 0 | straight | yes | 962 | 5.0% | 962 | 5.0% |
| straight -x-y (y wing) 1 | straight | yes | 609 | 3.2% | 604 | 3.1% |
| straight -x-y (y wing) 2 | straight | yes | 300 | 1.6% | 296 | 1.5% |
| straight -x-y (x wing) 0 | straight | yes | 955 | 5.0% | 955 | 5.0% |
| straight -x-y (x wing) 1 | straight | yes | 604 | 3.1% | 595 | 3.1% |
| straight -x-y (x wing) 2 | straight | yes | 301 | 1.6% | 301 | 1.6% |
| corner -x-y | corner | yes | 780 | 4.1% | 255 | 1.3% |
| straight +x-y (y wing) 0 | straight | yes | 955 | 5.0% | 955 | 5.0% |
| straight +x-y (y wing) 1 | straight | yes | 612 | 3.2% | 607 | 3.2% |
| straight +x-y (y wing) 2 | straight | yes | 292 | 1.5% | 289 | 1.5% |
| straight +x-y (x wing) 0 | straight | yes | 954 | 5.0% | 954 | 5.0% |
| straight +x-y (x wing) 1 | straight | yes | 611 | 3.2% | 606 | 3.2% |
| straight +x-y (x wing) 2 | straight | yes | 274 | 1.4% | 270 | 1.4% |
| corner +x-y | corner | yes | 792 | 4.1% | 287 | 1.5% |
| **straight (24)** | | | 14837 | | 14763 | 76.8% |
| **corner (4)** | | | 3156 | | 1107 | 5.8% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 3353, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 956 | 29.0 | 523.5 | 0.25 | 0.78 | 0.0% |
| -x | 965 | 29.0 | 531.4 | 0.24 | 0.65 | 0.0% |
| +y | 962 | 29.0 | 535.2 | 0.24 | 0.70 | 0.0% |
| -y | 953 | 29.0 | 526.3 | 0.24 | 0.66 | 0.0% |
| door +x+y (y wall) 0 | 720 | 1.2 | 535.4 | 0.81 | 1.50 | 40.7% |
| door +x+y (y wall) 1 | 719 | 0.9 | 547.1 | 0.79 | 1.44 | 34.5% |
| door +x+y (y wall) 2 | 363 | 1.0 | 565.1 | 0.38 | 1.38 | 15.8% |
| door +x+y (x wall) 0 | 723 | 0.9 | 539.6 | 0.80 | 1.44 | 41.8% |
| door +x+y (x wall) 1 | 714 | 1.4 | 551.3 | 0.78 | 1.44 | 35.7% |
| door +x+y (x wall) 2 | 379 | 0.9 | 576.3 | 0.39 | 1.20 | 15.5% |
| door +x+y (corner) | 222 | 0.9 | 579.5 | 0.23 | 1.38 | 8.5% |
| door -x+y (y wall) 0 | 742 | 0.7 | 544.3 | 0.82 | 1.50 | 47.3% |
| door -x+y (y wall) 1 | 735 | 0.9 | 563.5 | 0.78 | 1.56 | 45.6% |
| door -x+y (y wall) 2 | 330 | 0.9 | 579.5 | 0.34 | 1.32 | 16.9% |
| door -x+y (x wall) 0 | 729 | 0.9 | 544.7 | 0.80 | 1.44 | 45.5% |
| door -x+y (x wall) 1 | 727 | 0.7 | 562.7 | 0.77 | 1.44 | 40.4% |
| door -x+y (x wall) 2 | 387 | 1.4 | 567.2 | 0.41 | 1.32 | 15.8% |
| door -x+y (corner) | 213 | 1.0 | 583.7 | 0.22 | 1.32 | 8.5% |
| door -x-y (y wall) 0 | 724 | 0.9 | 536.6 | 0.81 | 1.56 | 44.4% |
| door -x-y (y wall) 1 | 715 | 0.9 | 549.7 | 0.78 | 1.50 | 39.3% |
| door -x-y (y wall) 2 | 380 | 0.9 | 583.3 | 0.39 | 1.38 | 20.3% |
| door -x-y (x wall) 0 | 725 | 1.0 | 542.2 | 0.80 | 1.44 | 43.6% |
| door -x-y (x wall) 1 | 706 | 1.0 | 548.0 | 0.77 | 1.56 | 29.1% |
| door -x-y (x wall) 2 | 390 | 0.7 | 575.6 | 0.41 | 1.44 | 17.2% |
| door -x-y (corner) | 193 | 0.9 | 571.4 | 0.20 | 1.32 | 6.9% |
| door +x-y (y wall) 0 | 726 | 0.9 | 541.3 | 0.80 | 1.38 | 49.1% |
| door +x-y (y wall) 1 | 721 | 1.0 | 565.3 | 0.76 | 1.50 | 43.9% |
| door +x-y (y wall) 2 | 376 | 0.9 | 585.6 | 0.38 | 1.20 | 16.9% |
| door +x-y (x wall) 0 | 722 | 0.9 | 545.2 | 0.79 | 1.56 | 43.6% |
| door +x-y (x wall) 1 | 721 | 0.9 | 564.8 | 0.76 | 1.56 | 42.1% |
| door +x-y (x wall) 2 | 361 | 0.7 | 585.4 | 0.37 | 1.26 | 15.3% |
| door +x-y (corner) | 224 | 0.9 | 588.7 | 0.23 | 1.38 | 10.0% |

Mean flow / w J averaged over the doors 0.59, over the avenues 0.24.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 958 | 606 / 352 / 220 | 0.5 | 532.4 | 2.21 | 3.31 | 81% | 81% | 0% | 4.33 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 554 | 600 / 0 / 10 | 0.7 | 544.1 | 1.12 | 1.60 | 82% | 71% | 11% | 3.69 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 77 | 279 / 0 / 1 | 0.7 | 562.2 | 0.50 | 1.10 | 19% | 14% | 5% | 2.75 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 952 | 608 / 345 / 206 | 0.5 | 536.6 | 2.16 | 3.51 | 93% | 81% | 11% | 3.97 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 561 | 602 / 0 / 8 | 0.7 | 548.3 | 1.11 | 1.60 | 82% | 71% | 11% | 3.73 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 78 | 300 / 0 / 7 | 0.7 | 573.3 | 0.54 | 1.20 | 16% | 10% | 5% | 2.95 |
| corner +x+y | 1.20 | 85.6 | 787 | 163 / 113 / 537 | 0.7 | 575.6 | 1.41 | 3.91 | 86% | 62% | 24% | 2.48 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 958 | 621 / 338 / 210 | 0.7 | 541.3 | 2.16 | 3.81 | 82% | 82% | 0% | 4.24 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 565 | 617 / 0 / 6 | 0.7 | 560.6 | 1.11 | 1.50 | 77% | 68% | 9% | 3.90 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 76 | 233 / 0 / 15 | 0.7 | 576.5 | 0.43 | 1.30 | 16% | 12% | 3% | 3.16 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 968 | 615 / 353 / 203 | 0.3 | 541.7 | 2.16 | 3.71 | 82% | 80% | 2% | 4.32 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 546 | 609 / 0 / 7 | 0.7 | 559.7 | 1.10 | 1.50 | 77% | 68% | 9% | 3.83 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 77 | 294 / 0 / 5 | 0.7 | 564.2 | 0.53 | 1.10 | 18% | 14% | 4% | 2.70 |
| corner -x+y | 1.20 | 85.6 | 777 | 169 / 120 / 521 | 0.2 | 580.0 | 1.40 | 3.11 | 85% | 63% | 22% | 2.54 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 962 | 606 / 356 / 231 | 0.3 | 533.6 | 2.24 | 3.81 | 91% | 81% | 9% | 3.96 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 563 | 604 / 0 / 15 | 0.7 | 546.8 | 1.13 | 1.71 | 84% | 69% | 15% | 3.80 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 78 | 296 / 0 / 4 | 0.7 | 580.3 | 0.52 | 1.50 | 17% | 17% | 0% | 3.12 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 955 | 609 / 346 / 205 | 0.2 | 539.2 | 2.15 | 3.41 | 84% | 82% | 2% | 4.21 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 567 | 595 / 0 / 22 | 0.7 | 545.0 | 1.13 | 1.71 | 85% | 71% | 15% | 3.68 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 76 | 301 / 0 / 0 | 0.7 | 572.6 | 0.53 | 1.40 | 17% | 16% | 2% | 3.17 |
| corner -x-y | 1.20 | 85.6 | 767 | 139 / 116 / 553 | 0.7 | 574.2 | 1.41 | 3.31 | 86% | 50% | 36% | 2.35 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 955 | 605 / 350 / 218 | 0.5 | 538.4 | 2.18 | 4.01 | 87% | 81% | 6% | 4.17 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 562 | 607 / 0 / 12 | 0.7 | 562.3 | 1.10 | 1.60 | 77% | 72% | 5% | 3.86 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 75 | 289 / 0 / 3 | 0.7 | 582.6 | 0.50 | 1.30 | 15% | 14% | 2% | 3.03 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 954 | 608 / 347 / 198 | 0.5 | 542.2 | 2.13 | 3.31 | 91% | 80% | 11% | 3.88 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 564 | 606 / 0 / 8 | 0.7 | 561.8 | 1.09 | 1.60 | 79% | 68% | 11% | 3.79 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 76 | 270 / 0 / 5 | 0.7 | 582.4 | 0.47 | 1.20 | 17% | 14% | 3% | 2.80 |
| corner +x-y | 1.20 | 85.6 | 782 | 175 / 112 / 523 | 0.7 | 584.9 | 1.39 | 3.21 | 85% | 61% | 24% | 2.48 |

The last agent out (agent 12325, t100 588.7 s): last gangway corner +x-y, exit door +x-y (corner). The gangway that cleared last: corner +x-y at 584.9 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.84 | 579.3 / 570.7 / 546.6 | 567.0 / 529.3 / 460.2 | 856529.7 | 1948199 | 0.197 |
| gangway | 1212 | 1112.9 | 6.84 | 576.7 / 560.8 / 491.0 | 567.0 / 529.3 / 460.2 | 823470.7 | 1627784 | 0.098 |
| walkway | 276 | 257.4 | 5.29 | 219.5 / 169.7 / 27.6 | 185.8 / 145.3 / 10.8 | 274.8 | 48078 | 0.528 |
| avenue | 912 | 858.9 | 2.54 | 247.8 / 21.3 / 0.0 | 197.6 / 1.2 / 0.0 | 0.0 | 110128 | 1.327 |
| exit | 32 | 3.2 | 0.00 | 566.5 / 564.6 / 522.6 | 328.6 / 298.9 / 187.7 | 1240.6 | 2205 | 1.199 |
| concourse | 1116 | 1043.8 | 6.05 | 523.8 / 116.3 / 75.7 | 215.1 / 114.4 / 59.8 | 31543.6 | 160004 | 0.318 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.58 | 527.0 / 500.9 / 488.3 | 511.3 / 500.9 / 484.7 | 906693.4 | 2456914 | 0.037 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -26.5 | -29.5 | gangway | 1.00 | 6.34 | 502.5 | 464.2 | 418.4 | 2562.5 | 0.020 |
| 2 | 26.5 | -28.5 | gangway | 1.00 | 5.99 | 509.5 | 491.5 | 429.2 | 2461.1 | 0.019 |
| 3 | -28.5 | 27.5 | gangway | 1.00 | 5.91 | 522.1 | 520.0 | 460.2 | 2440.5 | 0.015 |
| 4 | -26.5 | -28.5 | gangway | 1.00 | 5.91 | 511.6 | 490.3 | 432.4 | 2430.9 | 0.018 |
| 5 | -27.5 | -27.5 | gangway | 1.00 | 5.70 | 503.0 | 499.7 | 450.7 | 2414.9 | 0.016 |
| 6 | 28.5 | -27.5 | gangway | 1.00 | 5.89 | 523.5 | 522.3 | 433.2 | 2386.5 | 0.016 |
| 7 | -28.5 | -26.5 | gangway | 1.00 | 5.78 | 507.4 | 502.3 | 427.1 | 2380.0 | 0.018 |
| 8 | 27.5 | -28.5 | gangway | 1.00 | 5.86 | 506.9 | 499.4 | 429.7 | 2377.3 | 0.018 |
| 9 | 28.5 | 27.5 | gangway | 1.00 | 5.83 | 503.2 | 496.4 | 426.9 | 2370.3 | 0.018 |
| 10 | 27.5 | -27.5 | gangway | 1.00 | 5.75 | 521.4 | 514.6 | 428.3 | 2368.6 | 0.015 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 26.5 | 24.5 | seat row | 0.50 | 7.35 | 504.8 | 500.9 | 484.7 | 1689.7 | 0.014 |
| 2 | -25.5 | -30.5 | seat row | 0.64 | 6.62 | 449.3 | 435.3 | 402.6 | 1639.8 | 0.026 |
| 3 | 30.5 | -25.5 | seat row | 0.64 | 6.75 | 446.2 | 433.8 | 395.1 | 1603.9 | 0.025 |
| 4 | 30.5 | 25.5 | seat row | 0.64 | 6.55 | 445.5 | 433.4 | 402.6 | 1599.8 | 0.026 |
| 5 | -25.5 | 30.5 | seat row | 0.64 | 6.63 | 437.4 | 429.2 | 404.6 | 1586.4 | 0.025 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1694; agent-steps of seated agents on another row's clearway: 15334.

## Deposit check

Person-seconds deposited: 4410946.5, of them in excluded cells: 5833.971.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 484029 overlapping pair-steps: p99 0.0025, max 0.0561 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0025 max 0.0561; venue-geometry 6: p99 0.0007 max 0.0007 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 20 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.34 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 572 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
