# Experiment `M_load150_s4`

**Task 5.11 stage 1 (gridlock robustness, default model, AMD 26.10.1): venue M, the achievable maximum 121.42% (150% requested, seed 4)**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 19223 agents (load 121.4%, requested 150%): every one of the 15832 seats and 3391 standing (spawnOvercrowdedCrowd, seed 4; below), buffer N = 32768, 3353 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 1472720 evaluations, 59589 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.21)** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `15aa31e8667e4a9417fde7884d907d1832c5e2d6`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-23T17:51:06, 122.2 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Spawn (overcrowding)

| | |
|---|---|
| seated | 15832 (every seat) |
| standing | **3391** (requested round((1.50 - 1) x 15832) = 7916; at most 3391 = floor(2.5 p/m^2 x 1356.6 m^2)) |
| standing floor | walkway + rear concourse, 1356.6 m^2 |
| standing on the walkway / concourse / gangways | 614 / 2777 / 0 |
| **load** | **121.42%** of the seats (requested 150%; the floor takes no more: the achievable maximum) |
| standing crowd's mean density | 2.500 p/m^2 |
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 3.86, all circulation cells 3.86 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 4, 106870 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1200 | 209.9 |
| t90 | 2621 | 458.4 |
| t100 | 3353 | 586.5 |

t_p: the step by which ceil(p x 19223) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 955 | 84 | 29.0 | 529.4 | 20.2 | 58.5 | 28.9-38.8 |
| -x | 5.66 | 946 | 79 | 29.0 | 534.0 | 19.9 | 57.4 | 28.9-38.8 |
| +y | 5.66 | 941 | 82 | 29.0 | 528.4 | 20.0 | 59.5 | 28.7-38.7 |
| -y | 5.66 | 964 | 84 | 29.0 | 529.8 | 20.4 | 63.8 | 28.9-38.8 |
| door +x+y (y wall) 0 | 1.20 | 730 | 1275 | 1.0 | 566.3 | 64.5 | 125.4 | 105.3-115.3 |
| door +x+y (y wall) 1 | 1.20 | 717 | 798 | 1.2 | 545.7 | 65.8 | 125.4 | 98.1-108.1 |
| door +x+y (y wall) 2 | 1.20 | 362 | 265 | 0.9 | 574.7 | 31.5 | 105.3 | 42.9-52.8 |
| door +x+y (x wall) 0 | 1.20 | 729 | 1269 | 0.9 | 540.6 | 67.5 | 115.3 | 94.3-104.2 |
| door +x+y (x wall) 1 | 1.20 | 710 | 787 | 1.0 | 553.8 | 64.2 | 125.4 | 97.4-107.4 |
| door +x+y (x wall) 2 | 1.20 | 382 | 272 | 1.0 | 577.9 | 33.1 | 110.3 | 64.5-74.5 |
| door +x+y (corner) | 1.20 | 223 | 48 | 0.9 | 580.2 | 19.2 | 110.3 | 0.5-10.5 |
| door -x+y (y wall) 0 | 1.20 | 722 | 1272 | 1.0 | 544.7 | 66.4 | 120.4 | 95.0-104.9 |
| door -x+y (y wall) 1 | 1.20 | 720 | 796 | 0.9 | 559.7 | 64.4 | 125.4 | 106.0-116.0 |
| door -x+y (y wall) 2 | 1.20 | 358 | 273 | 0.9 | 567.2 | 31.6 | 105.3 | 18.5-28.5 |
| door -x+y (x wall) 0 | 1.20 | 728 | 1281 | 1.2 | 544.5 | 67.0 | 125.4 | 115.8-125.8 |
| door -x+y (x wall) 1 | 1.20 | 704 | 798 | 1.0 | 559.9 | 63.0 | 130.4 | 111.4-121.4 |
| door -x+y (x wall) 2 | 1.20 | 402 | 275 | 0.9 | 568.1 | 35.4 | 105.3 | 4.0-14.0 |
| door -x+y (corner) | 1.20 | 237 | 46 | 0.9 | 561.3 | 21.1 | 125.4 | 71.4-81.3 |
| door -x-y (y wall) 0 | 1.20 | 723 | 1269 | 0.9 | 548.2 | 66.0 | 135.4 | 104.8-114.7 |
| door -x-y (y wall) 1 | 1.20 | 706 | 792 | 0.9 | 547.6 | 64.5 | 120.4 | 104.9-114.9 |
| door -x-y (y wall) 2 | 1.20 | 370 | 274 | 0.7 | 573.0 | 32.3 | 105.3 | 75.0-85.0 |
| door -x-y (x wall) 0 | 1.20 | 723 | 1273 | 0.7 | 535.6 | 67.6 | 120.4 | 103.9-113.9 |
| door -x-y (x wall) 1 | 1.20 | 704 | 799 | 0.7 | 540.3 | 65.2 | 120.4 | 108.8-118.8 |
| door -x-y (x wall) 2 | 1.20 | 382 | 265 | 1.2 | 577.0 | 33.2 | 100.3 | 34.6-44.6 |
| door -x-y (corner) | 1.20 | 234 | 47 | 0.9 | 572.6 | 20.5 | 120.4 | 73.8-83.8 |
| door +x-y (y wall) 0 | 1.20 | 732 | 1268 | 1.0 | 540.8 | 67.8 | 120.4 | 98.5-108.4 |
| door +x-y (y wall) 1 | 1.20 | 722 | 793 | 0.9 | 557.6 | 64.8 | 115.3 | 89.7-99.7 |
| door +x-y (y wall) 2 | 1.20 | 358 | 270 | 1.0 | 586.5 | 30.6 | 115.3 | 80.6-90.6 |
| door +x-y (x wall) 0 | 1.20 | 727 | 1272 | 0.9 | 525.4 | 69.3 | 125.4 | 96.2-106.2 |
| door +x-y (x wall) 1 | 1.20 | 723 | 800 | 1.2 | 564.2 | 64.2 | 120.4 | 102.3-112.3 |
| door +x-y (x wall) 2 | 1.20 | 378 | 274 | 0.9 | 574.6 | 32.9 | 110.3 | 73.6-83.6 |
| door +x-y (corner) | 1.20 | 211 | 43 | 0.9 | 583.1 | 18.1 | 115.3 | 1.9-11.9 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 955 | 5.0% | 20.6% |
| -x | avenue | 5.66 | 946 | 4.9% | 20.5% |
| +y | avenue | 5.66 | 941 | 4.9% | 20.3% |
| -y | avenue | 5.66 | 964 | 5.0% | 20.8% |
| door +x+y (y wall) 0 | door | 1.20 | 730 | 3.8% | 74.4% |
| door +x+y (y wall) 1 | door | 1.20 | 717 | 3.7% | 73.1% |
| door +x+y (y wall) 2 | door | 1.20 | 362 | 1.9% | 36.9% |
| door +x+y (x wall) 0 | door | 1.20 | 729 | 3.8% | 74.3% |
| door +x+y (x wall) 1 | door | 1.20 | 710 | 3.7% | 72.4% |
| door +x+y (x wall) 2 | door | 1.20 | 382 | 2.0% | 39.0% |
| door +x+y (corner) | door | 1.20 | 223 | 1.2% | 22.7% |
| door -x+y (y wall) 0 | door | 1.20 | 722 | 3.8% | 73.6% |
| door -x+y (y wall) 1 | door | 1.20 | 720 | 3.7% | 73.4% |
| door -x+y (y wall) 2 | door | 1.20 | 358 | 1.9% | 36.5% |
| door -x+y (x wall) 0 | door | 1.20 | 728 | 3.8% | 74.2% |
| door -x+y (x wall) 1 | door | 1.20 | 704 | 3.7% | 71.8% |
| door -x+y (x wall) 2 | door | 1.20 | 402 | 2.1% | 41.0% |
| door -x+y (corner) | door | 1.20 | 237 | 1.2% | 24.2% |
| door -x-y (y wall) 0 | door | 1.20 | 723 | 3.8% | 73.7% |
| door -x-y (y wall) 1 | door | 1.20 | 706 | 3.7% | 72.0% |
| door -x-y (y wall) 2 | door | 1.20 | 370 | 1.9% | 37.7% |
| door -x-y (x wall) 0 | door | 1.20 | 723 | 3.8% | 73.7% |
| door -x-y (x wall) 1 | door | 1.20 | 704 | 3.7% | 71.8% |
| door -x-y (x wall) 2 | door | 1.20 | 382 | 2.0% | 39.0% |
| door -x-y (corner) | door | 1.20 | 234 | 1.2% | 23.9% |
| door +x-y (y wall) 0 | door | 1.20 | 732 | 3.8% | 74.7% |
| door +x-y (y wall) 1 | door | 1.20 | 722 | 3.8% | 73.6% |
| door +x-y (y wall) 2 | door | 1.20 | 358 | 1.9% | 36.5% |
| door +x-y (x wall) 0 | door | 1.20 | 727 | 3.8% | 74.1% |
| door +x-y (x wall) 1 | door | 1.20 | 723 | 3.8% | 73.7% |
| door +x-y (x wall) 2 | door | 1.20 | 378 | 2.0% | 38.5% |
| door +x-y (corner) | door | 1.20 | 211 | 1.1% | 21.5% |
| **doors (28)** | door | 33.60 | 15417 | 80.2% | |
| **avenues (4)** | avenue | 22.64 | 3806 | 19.8% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 586.5 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 41.8%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 965 | 5.0% | 965 | 5.0% |
| straight +x+y (y wing) 1 | straight | yes | 603 | 3.1% | 600 | 3.1% |
| straight +x+y (y wing) 2 | straight | yes | 274 | 1.4% | 274 | 1.4% |
| straight +x+y (x wing) 0 | straight | yes | 957 | 5.0% | 957 | 5.0% |
| straight +x+y (x wing) 1 | straight | yes | 614 | 3.2% | 604 | 3.1% |
| straight +x+y (x wing) 2 | straight | yes | 291 | 1.5% | 287 | 1.5% |
| corner +x+y | corner | yes | 777 | 4.0% | 281 | 1.5% |
| straight -x+y (y wing) 0 | straight | yes | 954 | 5.0% | 954 | 5.0% |
| straight -x+y (y wing) 1 | straight | yes | 610 | 3.2% | 604 | 3.1% |
| straight -x+y (y wing) 2 | straight | yes | 274 | 1.4% | 269 | 1.4% |
| straight -x+y (x wing) 0 | straight | yes | 950 | 4.9% | 950 | 4.9% |
| straight -x+y (x wing) 1 | straight | yes | 594 | 3.1% | 587 | 3.1% |
| straight -x+y (x wing) 2 | straight | yes | 312 | 1.6% | 309 | 1.6% |
| corner -x+y | corner | yes | 794 | 4.1% | 291 | 1.5% |
| straight -x-y (y wing) 0 | straight | yes | 955 | 5.0% | 955 | 5.0% |
| straight -x-y (y wing) 1 | straight | yes | 604 | 3.1% | 594 | 3.1% |
| straight -x-y (y wing) 2 | straight | yes | 283 | 1.5% | 278 | 1.4% |
| straight -x-y (x wing) 0 | straight | yes | 962 | 5.0% | 962 | 5.0% |
| straight -x-y (x wing) 1 | straight | yes | 598 | 3.1% | 589 | 3.1% |
| straight -x-y (x wing) 2 | straight | yes | 309 | 1.6% | 307 | 1.6% |
| corner -x-y | corner | yes | 779 | 4.1% | 282 | 1.5% |
| straight +x-y (y wing) 0 | straight | yes | 958 | 5.0% | 958 | 5.0% |
| straight +x-y (y wing) 1 | straight | yes | 616 | 3.2% | 611 | 3.2% |
| straight +x-y (y wing) 2 | straight | yes | 268 | 1.4% | 268 | 1.4% |
| straight +x-y (x wing) 0 | straight | yes | 960 | 5.0% | 960 | 5.0% |
| straight +x-y (x wing) 1 | straight | yes | 608 | 3.2% | 603 | 3.1% |
| straight +x-y (x wing) 2 | straight | yes | 301 | 1.6% | 299 | 1.6% |
| corner +x-y | corner | yes | 787 | 4.1% | 268 | 1.4% |
| **straight (24)** | | | 14820 | | 14744 | 76.7% |
| **corner (4)** | | | 3137 | | 1122 | 5.8% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 3357, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 955 | 29.0 | 529.4 | 0.24 | 0.70 | 0.0% |
| -x | 946 | 29.0 | 534.0 | 0.24 | 0.69 | 0.0% |
| +y | 941 | 29.0 | 528.4 | 0.24 | 0.71 | 0.0% |
| -y | 964 | 29.0 | 529.8 | 0.24 | 0.76 | 0.0% |
| door +x+y (y wall) 0 | 730 | 1.0 | 566.3 | 0.77 | 1.50 | 42.1% |
| door +x+y (y wall) 1 | 717 | 1.2 | 545.7 | 0.79 | 1.50 | 36.4% |
| door +x+y (y wall) 2 | 362 | 0.9 | 574.7 | 0.38 | 1.26 | 17.2% |
| door +x+y (x wall) 0 | 729 | 0.9 | 540.6 | 0.81 | 1.38 | 47.3% |
| door +x+y (x wall) 1 | 710 | 1.0 | 553.8 | 0.77 | 1.50 | 39.3% |
| door +x+y (x wall) 2 | 382 | 1.0 | 577.9 | 0.40 | 1.32 | 15.5% |
| door +x+y (corner) | 223 | 0.9 | 580.2 | 0.23 | 1.32 | 8.5% |
| door -x+y (y wall) 0 | 722 | 1.0 | 544.7 | 0.79 | 1.44 | 45.5% |
| door -x+y (y wall) 1 | 720 | 0.9 | 559.7 | 0.77 | 1.50 | 36.8% |
| door -x+y (y wall) 2 | 358 | 0.9 | 567.2 | 0.38 | 1.26 | 17.5% |
| door -x+y (x wall) 0 | 728 | 1.2 | 544.5 | 0.80 | 1.50 | 45.5% |
| door -x+y (x wall) 1 | 704 | 1.0 | 559.9 | 0.75 | 1.56 | 36.8% |
| door -x+y (x wall) 2 | 402 | 0.9 | 568.1 | 0.42 | 1.26 | 15.8% |
| door -x+y (corner) | 237 | 0.9 | 561.3 | 0.25 | 1.50 | 10.5% |
| door -x-y (y wall) 0 | 723 | 0.9 | 548.2 | 0.79 | 1.62 | 45.5% |
| door -x-y (y wall) 1 | 706 | 0.9 | 547.6 | 0.77 | 1.44 | 40.0% |
| door -x-y (y wall) 2 | 370 | 0.7 | 573.0 | 0.39 | 1.26 | 17.2% |
| door -x-y (x wall) 0 | 723 | 0.7 | 535.6 | 0.81 | 1.44 | 50.0% |
| door -x-y (x wall) 1 | 704 | 0.7 | 540.3 | 0.78 | 1.44 | 43.6% |
| door -x-y (x wall) 2 | 382 | 1.2 | 577.0 | 0.40 | 1.20 | 13.8% |
| door -x-y (corner) | 234 | 0.9 | 572.6 | 0.24 | 1.44 | 10.3% |
| door +x-y (y wall) 0 | 732 | 1.0 | 540.8 | 0.81 | 1.44 | 49.1% |
| door +x-y (y wall) 1 | 722 | 0.9 | 557.6 | 0.78 | 1.38 | 37.5% |
| door +x-y (y wall) 2 | 358 | 1.0 | 586.5 | 0.37 | 1.38 | 15.3% |
| door +x-y (x wall) 0 | 727 | 0.9 | 525.4 | 0.83 | 1.50 | 52.8% |
| door +x-y (x wall) 1 | 723 | 1.2 | 564.2 | 0.77 | 1.44 | 38.6% |
| door +x-y (x wall) 2 | 378 | 0.9 | 574.6 | 0.39 | 1.32 | 15.5% |
| door +x-y (corner) | 211 | 0.9 | 583.1 | 0.22 | 1.38 | 8.5% |

Mean flow / w J averaged over the doors 0.59, over the avenues 0.24.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 965 | 613 / 352 / 232 | 0.2 | 563.4 | 2.12 | 3.51 | 91% | 77% | 14% | 3.77 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 563 | 600 / 0 / 4 | 0.7 | 542.7 | 1.11 | 1.50 | 84% | 71% | 13% | 3.73 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 75 | 274 / 0 / 0 | 0.7 | 571.8 | 0.48 | 1.20 | 17% | 12% | 5% | 2.94 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 957 | 616 / 341 / 211 | 0.2 | 537.7 | 2.17 | 3.61 | 93% | 81% | 11% | 3.87 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 566 | 604 / 0 / 15 | 0.7 | 550.8 | 1.12 | 1.60 | 82% | 70% | 12% | 3.73 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 76 | 287 / 0 / 4 | 0.7 | 574.9 | 0.51 | 1.10 | 16% | 12% | 3% | 2.92 |
| corner +x+y | 1.20 | 85.6 | 766 | 175 / 106 / 508 | 0.7 | 576.3 | 1.37 | 3.31 | 88% | 55% | 33% | 2.43 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 954 | 608 / 346 / 222 | 0.2 | 541.7 | 2.17 | 3.91 | 84% | 80% | 4% | 4.22 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 559 | 604 / 0 / 6 | 0.7 | 556.7 | 1.10 | 1.40 | 80% | 68% | 12% | 3.75 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 79 | 269 / 0 / 8 | 0.7 | 564.2 | 0.49 | 1.40 | 18% | 12% | 5% | 2.94 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 950 | 607 / 343 / 200 | 0.5 | 541.5 | 2.13 | 3.81 | 89% | 80% | 9% | 4.01 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 557 | 587 / 0 / 8 | 0.7 | 556.9 | 1.07 | 1.50 | 80% | 68% | 12% | 3.79 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 79 | 309 / 0 / 3 | 0.7 | 565.1 | 0.55 | 1.40 | 18% | 12% | 5% | 2.88 |
| corner -x+y | 1.20 | 85.6 | 786 | 180 / 111 / 520 | 0.7 | 559.0 | 1.45 | 3.01 | 88% | 56% | 32% | 2.42 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 955 | 608 / 347 / 216 | 0.2 | 545.2 | 2.15 | 4.01 | 82% | 80% | 2% | 4.23 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 570 | 594 / 0 / 20 | 0.7 | 544.7 | 1.13 | 1.91 | 82% | 73% | 9% | 3.79 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 78 | 279 / 0 / 5 | 0.7 | 570.0 | 0.50 | 1.20 | 17% | 12% | 5% | 2.77 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 962 | 607 / 356 / 198 | 0.3 | 532.6 | 2.18 | 3.71 | 85% | 83% | 2% | 4.18 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 560 | 589 / 0 / 10 | 0.7 | 537.3 | 1.12 | 1.60 | 85% | 72% | 13% | 3.76 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 77 | 307 / 0 / 2 | 0.7 | 574.0 | 0.54 | 1.30 | 17% | 17% | 0% | 3.26 |
| corner -x-y | 1.20 | 85.6 | 765 | 167 / 115 / 520 | 0.7 | 568.8 | 1.41 | 3.11 | 84% | 57% | 28% | 2.42 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 958 | 618 / 341 / 222 | 0.3 | 537.8 | 2.20 | 3.71 | 93% | 81% | 11% | 3.94 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 559 | 611 / 0 / 10 | 0.7 | 554.6 | 1.12 | 1.60 | 82% | 70% | 12% | 3.71 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 78 | 268 / 0 / 0 | 0.7 | 583.5 | 0.46 | 1.10 | 17% | 15% | 2% | 3.06 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 960 | 611 / 349 / 201 | 0.3 | 522.4 | 2.22 | 3.71 | 91% | 85% | 6% | 4.08 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 558 | 603 / 0 / 13 | 0.7 | 561.3 | 1.10 | 1.81 | 77% | 67% | 11% | 3.81 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 78 | 299 / 0 / 9 | 0.7 | 571.6 | 0.54 | 1.50 | 17% | 17% | 0% | 3.07 |
| corner +x-y | 1.20 | 85.6 | 776 | 147 / 121 / 540 | 0.7 | 579.3 | 1.40 | 3.21 | 86% | 59% | 27% | 2.46 |

The last agent out (agent 12404, t100 586.5 s): last gangway straight +x-y (y wing) 2, exit door +x-y (y wall) 2. The gangway that cleared last: straight +x-y (y wing) 2 at 583.5 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.83 | 582.6 / 568.8 / 545.7 | 563.9 / 531.7 / 449.2 | 859408.7 | 1942424 | 0.198 |
| gangway | 1212 | 1112.9 | 6.83 | 579.6 / 560.1 / 492.7 | 563.9 / 531.7 / 449.2 | 825923.7 | 1620743 | 0.099 |
| walkway | 276 | 257.4 | 5.38 | 231.8 / 173.3 / 17.1 | 192.2 / 160.7 / 8.9 | 105.0 | 47963 | 0.526 |
| avenue | 912 | 858.9 | 2.75 | 255.4 / 29.9 / 0.0 | 206.0 / 1.6 / 0.0 | 0.0 | 109265 | 1.327 |
| exit | 32 | 3.2 | 0.00 | 568.4 / 565.1 / 521.6 | 326.4 / 298.2 / 184.5 | 1243.2 | 2203 | 1.193 |
| concourse | 1116 | 1043.8 | 6.06 | 527.3 / 120.0 / 75.6 | 210.9 / 119.1 / 55.4 | 32136.8 | 162250 | 0.316 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.63 | 525.6 / 506.7 / 488.3 | 517.4 / 506.2 / 484.7 | 916230.8 | 2457581 | 0.037 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 27.5 | -27.5 | gangway | 1.00 | 5.91 | 509.0 | 501.5 | 449.2 | 2560.7 | 0.013 |
| 2 | 28.5 | -27.5 | gangway | 1.00 | 5.99 | 518.1 | 512.1 | 439.0 | 2525.9 | 0.015 |
| 3 | 28.5 | -26.5 | gangway | 1.00 | 5.99 | 518.9 | 511.1 | 436.0 | 2510.5 | 0.020 |
| 4 | 26.5 | 28.5 | gangway | 1.00 | 5.94 | 507.9 | 501.6 | 431.1 | 2487.2 | 0.017 |
| 5 | 27.5 | 27.5 | gangway | 1.00 | 5.80 | 504.8 | 494.3 | 439.9 | 2462.1 | 0.014 |
| 6 | -28.5 | 26.5 | gangway | 1.00 | 5.98 | 501.3 | 489.7 | 436.7 | 2460.5 | 0.017 |
| 7 | -27.5 | 27.5 | gangway | 1.00 | 6.00 | 513.9 | 501.8 | 437.1 | 2440.7 | 0.018 |
| 8 | -26.5 | -29.5 | gangway | 1.00 | 6.17 | 488.9 | 460.9 | 420.8 | 2437.5 | 0.018 |
| 9 | -28.5 | 27.5 | gangway | 1.00 | 5.94 | 503.9 | 487.6 | 434.6 | 2411.5 | 0.018 |
| 10 | -28.5 | -26.5 | gangway | 1.00 | 5.91 | 502.3 | 491.8 | 409.5 | 2381.2 | 0.017 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -26.5 | -9.5 | seat row | 0.50 | 7.42 | 453.9 | 451.8 | 442.9 | 1590.2 | 0.011 |
| 2 | -9.5 | -26.5 | seat row | 0.50 | 7.55 | 448.3 | 446.5 | 438.3 | 1585.4 | 0.011 |
| 3 | 9.5 | 26.5 | seat row | 0.50 | 7.45 | 451.6 | 449.3 | 439.5 | 1584.4 | 0.011 |
| 4 | -25.5 | -30.5 | seat row | 0.64 | 6.54 | 449.7 | 427.3 | 402.6 | 1584.0 | 0.024 |
| 5 | 30.5 | 25.5 | seat row | 0.64 | 6.75 | 442.9 | 424.8 | 386.7 | 1582.7 | 0.027 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1705; agent-steps of seated agents on another row's clearway: 16732.

## Deposit check

Person-seconds deposited: 4405858.0, of them in excluded cells: 5852.781.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 507214 overlapping pair-steps: p99 0.0024, max 0.0940 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0024 max 0.0940; venue-geometry 12: p99 0.0007 max 0.0007 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 29 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.31 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 536 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
