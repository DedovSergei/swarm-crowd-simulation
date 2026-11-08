# Experiment `M_load150_s1`

**Task 5.11 stage 1 (gridlock robustness, default model, AMD 26.10.1): venue M, the achievable maximum 121.42% (150% requested, seed 1)**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 19223 agents (load 121.4%, requested 150%): every one of the 15832 seats and 3391 standing (spawnOvercrowdedCrowd, seed 1; below), buffer N = 32768, 3349 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 1460361 evaluations, 58710 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.21)** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `15aa31e8667e4a9417fde7884d907d1832c5e2d6`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-23T17:41:02, 178.4 s wall.

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
| t50 | 1183 | 206.9 |
| t90 | 2609 | 456.3 |
| t100 | 3349 | 585.8 |

t_p: the step by which ceil(p x 19223) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 963 | 93 | 29.0 | 528.2 | 20.4 | 62.7 | 28.7-38.7 |
| -x | 5.66 | 956 | 89 | 29.0 | 525.6 | 20.4 | 59.5 | 28.7-38.7 |
| +y | 5.66 | 937 | 83 | 29.2 | 527.3 | 19.9 | 61.7 | 28.9-38.8 |
| -y | 5.66 | 947 | 82 | 29.0 | 527.7 | 20.1 | 59.5 | 28.5-38.5 |
| door +x+y (y wall) 0 | 1.20 | 721 | 1267 | 0.7 | 544.1 | 66.3 | 130.4 | 108.6-118.6 |
| door +x+y (y wall) 1 | 1.20 | 700 | 799 | 1.0 | 541.2 | 64.8 | 125.4 | 109.3-119.3 |
| door +x+y (y wall) 2 | 1.20 | 382 | 270 | 1.0 | 567.2 | 33.7 | 120.4 | 64.0-74.0 |
| door +x+y (x wall) 0 | 1.20 | 725 | 1267 | 1.0 | 537.1 | 67.6 | 130.4 | 96.9-106.9 |
| door +x+y (x wall) 1 | 1.20 | 712 | 806 | 1.2 | 547.6 | 65.1 | 120.4 | 105.3-115.3 |
| door +x+y (x wall) 2 | 1.20 | 393 | 271 | 0.9 | 579.6 | 33.9 | 115.3 | 79.1-89.0 |
| door +x+y (corner) | 1.20 | 232 | 47 | 0.7 | 558.8 | 20.8 | 115.3 | 0.5-10.5 |
| door -x+y (y wall) 0 | 1.20 | 717 | 1270 | 0.9 | 532.2 | 67.4 | 125.4 | 99.9-109.8 |
| door -x+y (y wall) 1 | 1.20 | 712 | 797 | 0.9 | 551.5 | 64.6 | 120.4 | 110.0-120.0 |
| door -x+y (y wall) 2 | 1.20 | 384 | 265 | 1.2 | 585.2 | 32.9 | 115.3 | 75.7-85.7 |
| door -x+y (x wall) 0 | 1.20 | 714 | 1275 | 0.9 | 526.1 | 67.9 | 125.4 | 105.8-115.8 |
| door -x+y (x wall) 1 | 1.20 | 710 | 787 | 1.2 | 556.6 | 63.9 | 125.4 | 106.7-116.7 |
| door -x+y (x wall) 2 | 1.20 | 391 | 276 | 0.9 | 579.1 | 33.8 | 115.3 | 85.0-95.0 |
| door -x+y (corner) | 1.20 | 229 | 50 | 0.7 | 585.8 | 19.6 | 115.3 | 12.4-22.4 |
| door -x-y (y wall) 0 | 1.20 | 731 | 1275 | 1.0 | 539.1 | 67.9 | 135.4 | 93.6-103.5 |
| door -x-y (y wall) 1 | 1.20 | 708 | 794 | 0.9 | 543.1 | 65.3 | 120.4 | 96.9-106.9 |
| door -x-y (y wall) 2 | 1.20 | 408 | 277 | 0.9 | 584.4 | 35.0 | 115.3 | 61.6-71.5 |
| door -x-y (x wall) 0 | 1.20 | 727 | 1269 | 0.9 | 543.3 | 67.0 | 115.3 | 107.4-117.4 |
| door -x-y (x wall) 1 | 1.20 | 712 | 792 | 1.6 | 546.6 | 65.3 | 110.3 | 91.1-101.1 |
| door -x-y (x wall) 2 | 1.20 | 375 | 269 | 0.9 | 577.7 | 32.5 | 105.3 | 10.3-20.3 |
| door -x-y (corner) | 1.20 | 198 | 48 | 0.9 | 569.0 | 17.4 | 110.3 | 0.5-10.5 |
| door +x-y (y wall) 0 | 1.20 | 721 | 1272 | 0.9 | 536.4 | 67.3 | 125.4 | 100.2-110.2 |
| door +x-y (y wall) 1 | 1.20 | 698 | 792 | 1.0 | 537.8 | 65.0 | 130.4 | 101.4-111.4 |
| door +x-y (y wall) 2 | 1.20 | 379 | 267 | 0.9 | 583.3 | 32.5 | 110.3 | 61.4-71.4 |
| door +x-y (x wall) 0 | 1.20 | 727 | 1270 | 1.0 | 548.2 | 66.4 | 125.4 | 111.4-121.4 |
| door +x-y (x wall) 1 | 1.20 | 706 | 797 | 1.0 | 545.4 | 64.8 | 120.4 | 105.1-115.1 |
| door +x-y (x wall) 2 | 1.20 | 368 | 261 | 1.2 | 574.2 | 32.1 | 110.3 | 70.8-80.8 |
| door +x-y (corner) | 1.20 | 240 | 46 | 0.9 | 574.0 | 20.9 | 115.3 | 1.6-11.5 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 963 | 5.0% | 20.8% |
| -x | avenue | 5.66 | 956 | 5.0% | 20.7% |
| +y | avenue | 5.66 | 937 | 4.9% | 20.3% |
| -y | avenue | 5.66 | 947 | 4.9% | 20.5% |
| door +x+y (y wall) 0 | door | 1.20 | 721 | 3.8% | 73.6% |
| door +x+y (y wall) 1 | door | 1.20 | 700 | 3.6% | 71.5% |
| door +x+y (y wall) 2 | door | 1.20 | 382 | 2.0% | 39.0% |
| door +x+y (x wall) 0 | door | 1.20 | 725 | 3.8% | 74.0% |
| door +x+y (x wall) 1 | door | 1.20 | 712 | 3.7% | 72.7% |
| door +x+y (x wall) 2 | door | 1.20 | 393 | 2.0% | 40.1% |
| door +x+y (corner) | door | 1.20 | 232 | 1.2% | 23.7% |
| door -x+y (y wall) 0 | door | 1.20 | 717 | 3.7% | 73.2% |
| door -x+y (y wall) 1 | door | 1.20 | 712 | 3.7% | 72.7% |
| door -x+y (y wall) 2 | door | 1.20 | 384 | 2.0% | 39.2% |
| door -x+y (x wall) 0 | door | 1.20 | 714 | 3.7% | 72.9% |
| door -x+y (x wall) 1 | door | 1.20 | 710 | 3.7% | 72.5% |
| door -x+y (x wall) 2 | door | 1.20 | 391 | 2.0% | 39.9% |
| door -x+y (corner) | door | 1.20 | 229 | 1.2% | 23.4% |
| door -x-y (y wall) 0 | door | 1.20 | 731 | 3.8% | 74.6% |
| door -x-y (y wall) 1 | door | 1.20 | 708 | 3.7% | 72.3% |
| door -x-y (y wall) 2 | door | 1.20 | 408 | 2.1% | 41.7% |
| door -x-y (x wall) 0 | door | 1.20 | 727 | 3.8% | 74.2% |
| door -x-y (x wall) 1 | door | 1.20 | 712 | 3.7% | 72.7% |
| door -x-y (x wall) 2 | door | 1.20 | 375 | 2.0% | 38.3% |
| door -x-y (corner) | door | 1.20 | 198 | 1.0% | 20.2% |
| door +x-y (y wall) 0 | door | 1.20 | 721 | 3.8% | 73.6% |
| door +x-y (y wall) 1 | door | 1.20 | 698 | 3.6% | 71.3% |
| door +x-y (y wall) 2 | door | 1.20 | 379 | 2.0% | 38.7% |
| door +x-y (x wall) 0 | door | 1.20 | 727 | 3.8% | 74.2% |
| door +x-y (x wall) 1 | door | 1.20 | 706 | 3.7% | 72.1% |
| door +x-y (x wall) 2 | door | 1.20 | 368 | 1.9% | 37.6% |
| door +x-y (corner) | door | 1.20 | 240 | 1.2% | 24.5% |
| **doors (28)** | door | 33.60 | 15420 | 80.2% | |
| **avenues (4)** | avenue | 22.64 | 3803 | 19.8% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 585.8 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 41.9%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 964 | 5.0% | 964 | 5.0% |
| straight +x+y (y wing) 1 | straight | yes | 593 | 3.1% | 584 | 3.0% |
| straight +x+y (y wing) 2 | straight | yes | 290 | 1.5% | 287 | 1.5% |
| straight +x+y (x wing) 0 | straight | yes | 954 | 5.0% | 954 | 5.0% |
| straight +x+y (x wing) 1 | straight | yes | 595 | 3.1% | 586 | 3.0% |
| straight +x+y (x wing) 2 | straight | yes | 305 | 1.6% | 304 | 1.6% |
| corner +x+y | corner | yes | 788 | 4.1% | 289 | 1.5% |
| straight -x+y (y wing) 0 | straight | yes | 952 | 5.0% | 952 | 5.0% |
| straight -x+y (y wing) 1 | straight | yes | 602 | 3.1% | 595 | 3.1% |
| straight -x+y (y wing) 2 | straight | yes | 301 | 1.6% | 298 | 1.6% |
| straight -x+y (x wing) 0 | straight | yes | 943 | 4.9% | 943 | 4.9% |
| straight -x+y (x wing) 1 | straight | yes | 621 | 3.2% | 610 | 3.2% |
| straight -x+y (x wing) 2 | straight | yes | 293 | 1.5% | 290 | 1.5% |
| corner -x+y | corner | yes | 788 | 4.1% | 281 | 1.5% |
| straight -x-y (y wing) 0 | straight | yes | 960 | 5.0% | 960 | 5.0% |
| straight -x-y (y wing) 1 | straight | yes | 606 | 3.2% | 601 | 3.1% |
| straight -x-y (y wing) 2 | straight | yes | 302 | 1.6% | 302 | 1.6% |
| straight -x-y (x wing) 0 | straight | yes | 970 | 5.0% | 970 | 5.0% |
| straight -x-y (x wing) 1 | straight | yes | 603 | 3.1% | 600 | 3.1% |
| straight -x-y (x wing) 2 | straight | yes | 298 | 1.6% | 294 | 1.5% |
| corner -x-y | corner | yes | 774 | 4.0% | 239 | 1.2% |
| straight +x-y (y wing) 0 | straight | yes | 954 | 5.0% | 954 | 5.0% |
| straight +x-y (y wing) 1 | straight | yes | 596 | 3.1% | 589 | 3.1% |
| straight +x-y (y wing) 2 | straight | yes | 292 | 1.5% | 289 | 1.5% |
| straight +x-y (x wing) 0 | straight | yes | 955 | 5.0% | 955 | 5.0% |
| straight +x-y (x wing) 1 | straight | yes | 599 | 3.1% | 592 | 3.1% |
| straight +x-y (x wing) 2 | straight | yes | 287 | 1.5% | 282 | 1.5% |
| corner +x-y | corner | yes | 787 | 4.1% | 306 | 1.6% |
| **straight (24)** | | | 14835 | | 14755 | 76.8% |
| **corner (4)** | | | 3137 | | 1115 | 5.8% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 3353, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 963 | 29.0 | 528.2 | 0.24 | 0.75 | 0.0% |
| -x | 956 | 29.0 | 525.6 | 0.24 | 0.71 | 0.0% |
| +y | 937 | 29.2 | 527.3 | 0.24 | 0.74 | 0.0% |
| -y | 947 | 29.0 | 527.7 | 0.24 | 0.71 | 0.0% |
| door +x+y (y wall) 0 | 721 | 0.7 | 544.1 | 0.79 | 1.56 | 34.5% |
| door +x+y (y wall) 1 | 700 | 1.0 | 541.2 | 0.77 | 1.50 | 41.8% |
| door +x+y (y wall) 2 | 382 | 1.0 | 567.2 | 0.40 | 1.44 | 15.8% |
| door +x+y (x wall) 0 | 725 | 1.0 | 537.1 | 0.81 | 1.56 | 46.3% |
| door +x+y (x wall) 1 | 712 | 1.2 | 547.6 | 0.78 | 1.44 | 45.5% |
| door +x+y (x wall) 2 | 393 | 0.9 | 579.6 | 0.41 | 1.38 | 15.3% |
| door +x+y (corner) | 232 | 0.7 | 558.8 | 0.25 | 1.38 | 7.0% |
| door -x+y (y wall) 0 | 717 | 0.9 | 532.2 | 0.81 | 1.50 | 44.4% |
| door -x+y (y wall) 1 | 712 | 0.9 | 551.5 | 0.77 | 1.44 | 42.9% |
| door -x+y (y wall) 2 | 384 | 1.2 | 585.2 | 0.39 | 1.38 | 15.3% |
| door -x+y (x wall) 0 | 714 | 0.9 | 526.1 | 0.81 | 1.50 | 45.3% |
| door -x+y (x wall) 1 | 710 | 1.2 | 556.6 | 0.76 | 1.50 | 35.7% |
| door -x+y (x wall) 2 | 391 | 0.9 | 579.1 | 0.40 | 1.38 | 16.9% |
| door -x+y (corner) | 229 | 0.7 | 585.8 | 0.23 | 1.38 | 11.9% |
| door -x-y (y wall) 0 | 731 | 1.0 | 539.1 | 0.81 | 1.62 | 45.5% |
| door -x-y (y wall) 1 | 708 | 0.9 | 543.1 | 0.78 | 1.44 | 43.6% |
| door -x-y (y wall) 2 | 408 | 0.9 | 584.4 | 0.42 | 1.38 | 16.9% |
| door -x-y (x wall) 0 | 727 | 0.9 | 543.3 | 0.80 | 1.38 | 54.5% |
| door -x-y (x wall) 1 | 712 | 1.6 | 546.6 | 0.78 | 1.32 | 38.2% |
| door -x-y (x wall) 2 | 375 | 0.9 | 577.7 | 0.39 | 1.26 | 17.2% |
| door -x-y (corner) | 198 | 0.9 | 569.0 | 0.21 | 1.32 | 8.6% |
| door +x-y (y wall) 0 | 721 | 0.9 | 536.4 | 0.80 | 1.50 | 46.3% |
| door +x-y (y wall) 1 | 698 | 1.0 | 537.8 | 0.78 | 1.56 | 37.0% |
| door +x-y (y wall) 2 | 379 | 0.9 | 583.3 | 0.39 | 1.32 | 15.3% |
| door +x-y (x wall) 0 | 727 | 1.0 | 548.2 | 0.79 | 1.50 | 49.1% |
| door +x-y (x wall) 1 | 706 | 1.0 | 545.4 | 0.78 | 1.44 | 36.4% |
| door +x-y (x wall) 2 | 368 | 1.2 | 574.2 | 0.38 | 1.32 | 15.5% |
| door +x-y (corner) | 240 | 0.9 | 574.0 | 0.25 | 1.38 | 10.3% |

Mean flow / w J averaged over the doors 0.60, over the avenues 0.24.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 964 | 606 / 358 / 220 | 0.3 | 541.2 | 2.19 | 3.81 | 82% | 80% | 2% | 4.27 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 556 | 584 / 0 / 100 | 0.7 | 538.4 | 1.27 | 4.11 | 85% | 72% | 13% | 3.64 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 79 | 287 / 0 / 12 | 0.7 | 564.2 | 0.53 | 1.30 | 18% | 14% | 4% | 2.83 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 954 | 614 / 340 / 217 | 0.2 | 534.2 | 2.19 | 3.81 | 83% | 81% | 2% | 4.17 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 562 | 586 / 0 / 10 | 0.7 | 544.7 | 1.10 | 1.50 | 84% | 71% | 13% | 3.70 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 78 | 304 / 0 / 1 | 0.7 | 576.7 | 0.53 | 1.30 | 17% | 16% | 2% | 3.11 |
| corner +x+y | 1.20 | 85.6 | 775 | 181 / 108 / 609 | 0.7 | 570.7 | 1.57 | 4.01 | 84% | 55% | 29% | 2.45 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 952 | 605 / 347 / 204 | 0.2 | 529.3 | 2.18 | 3.71 | 91% | 80% | 11% | 3.99 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 563 | 595 / 0 / 11 | 0.7 | 548.5 | 1.11 | 1.50 | 88% | 68% | 20% | 3.61 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 79 | 298 / 0 / 6 | 0.7 | 582.3 | 0.52 | 1.40 | 17% | 14% | 3% | 2.93 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 943 | 595 / 348 / 221 | 0.5 | 523.1 | 2.23 | 3.61 | 85% | 83% | 2% | 4.24 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 580 | 610 / 0 / 12 | 0.7 | 553.6 | 1.12 | 1.50 | 86% | 70% | 16% | 3.55 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 77 | 290 / 0 / 3 | 0.7 | 576.1 | 0.51 | 1.20 | 17% | 14% | 3% | 2.97 |
| corner -x+y | 1.20 | 85.6 | 775 | 175 / 106 / 526 | 0.2 | 581.9 | 1.39 | 3.51 | 85% | 46% | 39% | 2.32 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 960 | 614 / 346 / 203 | 0.3 | 536.1 | 2.17 | 3.41 | 83% | 83% | 0% | 4.30 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 561 | 601 / 0 / 8 | 0.7 | 540.1 | 1.13 | 1.50 | 84% | 75% | 9% | 3.67 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 78 | 302 / 0 / 0 | 0.7 | 581.4 | 0.52 | 1.20 | 17% | 15% | 2% | 3.04 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 970 | 611 / 359 / 229 | 0.3 | 540.3 | 2.22 | 3.61 | 87% | 80% | 7% | 4.08 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 549 | 600 / 0 / 9 | 0.7 | 543.6 | 1.12 | 1.50 | 82% | 67% | 15% | 3.78 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 81 | 294 / 0 / 6 | 0.7 | 574.7 | 0.52 | 1.30 | 17% | 17% | 0% | 2.83 |
| corner -x-y | 1.20 | 85.6 | 767 | 140 / 99 / 551 | 0.7 | 575.4 | 1.37 | 3.21 | 86% | 57% | 29% | 2.43 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 954 | 604 / 352 / 251 | 0.5 | 533.5 | 2.26 | 4.11 | 81% | 81% | 0% | 4.18 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 566 | 589 / 0 / 8 | 0.7 | 534.9 | 1.12 | 1.60 | 87% | 72% | 15% | 3.74 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 78 | 289 / 0 / 3 | 0.7 | 580.3 | 0.50 | 1.20 | 15% | 12% | 3% | 2.97 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 955 | 609 / 347 / 206 | 0.3 | 545.2 | 2.13 | 3.71 | 82% | 80% | 2% | 4.23 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 560 | 592 / 0 / 10 | 0.7 | 542.4 | 1.11 | 1.50 | 85% | 71% | 15% | 3.63 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 75 | 282 / 0 / 5 | 0.7 | 571.2 | 0.50 | 1.40 | 17% | 12% | 5% | 2.91 |
| corner +x-y | 1.20 | 85.6 | 779 | 192 / 114 / 499 | 0.7 | 574.4 | 1.40 | 3.21 | 84% | 53% | 31% | 2.43 |

The last agent out (agent 6471, t100 585.8 s): last gangway corner -x+y, exit door -x+y (corner). The gangway that cleared last: straight -x+y (y wing) 2 at 582.3 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.79 | 578.8 / 570.7 / 543.8 | 562.7 / 522.3 / 441.1 | 834708.6 | 1921863 | 0.200 |
| gangway | 1212 | 1112.9 | 6.79 | 576.7 / 562.7 / 491.8 | 562.7 / 522.3 / 441.1 | 801419.5 | 1603363 | 0.100 |
| walkway | 276 | 257.4 | 5.37 | 231.2 / 166.9 / 22.2 | 181.0 / 123.1 / 7.0 | 171.6 | 44664 | 0.560 |
| avenue | 912 | 858.9 | 2.69 | 246.4 / 28.0 / 0.0 | 197.3 / 1.6 / 0.0 | 0.0 | 109174 | 1.327 |
| exit | 32 | 3.2 | 0.00 | 565.3 / 562.0 / 513.2 | 326.7 / 295.6 / 182.3 | 1229.5 | 2193 | 1.195 |
| concourse | 1116 | 1043.8 | 6.09 | 524.2 / 117.9 / 80.6 | 208.7 / 116.8 / 59.5 | 31888.0 | 162469 | 0.316 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.61 | 508.3 / 493.6 / 482.2 | 504.3 / 493.6 / 472.1 | 907670.3 | 2441366 | 0.037 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -27.5 | -27.5 | gangway | 1.00 | 6.00 | 498.0 | 495.0 | 434.8 | 2510.0 | 0.015 |
| 2 | -28.5 | -27.5 | gangway | 1.00 | 6.08 | 498.3 | 488.9 | 422.6 | 2464.9 | 0.015 |
| 3 | -27.5 | 27.5 | gangway | 1.00 | 6.06 | 506.9 | 504.1 | 433.6 | 2433.8 | 0.018 |
| 4 | -26.5 | -28.5 | gangway | 1.00 | 6.22 | 502.7 | 492.7 | 422.7 | 2433.6 | 0.019 |
| 5 | -28.5 | -26.5 | gangway | 1.00 | 6.05 | 493.2 | 478.5 | 421.0 | 2432.7 | 0.021 |
| 6 | -26.5 | -29.5 | gangway | 1.00 | 6.14 | 495.7 | 452.8 | 420.3 | 2409.3 | 0.021 |
| 7 | 29.5 | -26.5 | gangway | 1.00 | 6.10 | 501.5 | 470.5 | 413.7 | 2393.9 | 0.019 |
| 8 | -27.5 | -28.5 | gangway | 1.00 | 5.98 | 500.6 | 496.9 | 414.9 | 2388.1 | 0.016 |
| 9 | -26.5 | 29.5 | gangway | 1.00 | 5.98 | 504.1 | 470.0 | 401.8 | 2341.5 | 0.019 |
| 10 | 27.5 | -27.5 | gangway | 1.00 | 6.03 | 497.4 | 494.1 | 405.3 | 2334.7 | 0.017 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -30.5 | 25.5 | seat row | 0.64 | 6.50 | 466.7 | 451.1 | 410.7 | 1636.2 | 0.025 |
| 2 | -26.5 | -24.5 | seat row | 0.50 | 7.41 | 485.4 | 482.7 | 468.4 | 1629.2 | 0.013 |
| 3 | -25.5 | -30.5 | seat row | 0.64 | 6.60 | 448.1 | 428.5 | 405.6 | 1625.7 | 0.024 |
| 4 | 30.5 | 25.5 | seat row | 0.64 | 6.59 | 455.1 | 444.1 | 402.3 | 1620.0 | 0.025 |
| 5 | -24.5 | -26.5 | seat row | 0.50 | 7.26 | 498.3 | 493.6 | 472.1 | 1586.7 | 0.014 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1754; agent-steps of seated agents on another row's clearway: 14916.

## Deposit check

Person-seconds deposited: 4369143.5, of them in excluded cells: 5914.371.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 489994 overlapping pair-steps: p99 0.0028, max 0.0628 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0028 max 0.0628; venue-geometry 5: p99 0.0007 max 0.0007 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 23 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.32 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 591 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
