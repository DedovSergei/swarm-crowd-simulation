# Experiment `M_load150_s1`

**Task 5.8 stage 2: venue M, 150% requested (seed 1): every seat + standing on the walkway and concourse (M, L: the achievable maximum, also the 125% request)**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 19223 agents (load 121.4%, requested 150%): every one of the 15832 seats and 3391 standing (spawnOvercrowdedCrowd, seed 1; below), buffer N = 32768, 2750 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 1244357 evaluations, 54172 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.21)** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `cd8e0bbf3411846ca7aa6719887d122a142a7ca1`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-15T16:30:20, 80.4 s wall.

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
| t50 | 1051 | 183.8 |
| t90 | 2113 | 369.6 |
| t100 | 2750 | 481.0 |

t_p: the step by which ceil(p x 19223) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 932 | 93 | 29.0 | 429.0 | 24.7 | 62.7 | 28.7-38.7 |
| -x | 5.66 | 930 | 89 | 29.0 | 431.7 | 24.5 | 59.5 | 28.7-38.7 |
| +y | 5.66 | 918 | 83 | 29.2 | 429.2 | 24.3 | 61.7 | 28.9-38.8 |
| -y | 5.66 | 925 | 82 | 29.0 | 434.1 | 24.2 | 59.5 | 28.5-38.5 |
| door +x+y (y wall) 0 | 1.20 | 726 | 1267 | 0.7 | 443.0 | 82.0 | 130.4 | 121.9-131.9 |
| door +x+y (y wall) 1 | 1.20 | 722 | 799 | 1.0 | 449.9 | 80.4 | 130.4 | 131.9-141.8 |
| door +x+y (y wall) 2 | 1.20 | 388 | 270 | 1.0 | 477.1 | 40.7 | 100.3 | 44.6-54.6 |
| door +x+y (x wall) 0 | 1.20 | 733 | 1267 | 1.0 | 440.4 | 83.4 | 130.4 | 123.0-132.9 |
| door +x+y (x wall) 1 | 1.20 | 699 | 806 | 1.2 | 437.3 | 80.1 | 140.4 | 123.0-132.9 |
| door +x+y (x wall) 2 | 1.20 | 353 | 271 | 0.9 | 468.7 | 37.7 | 115.3 | 95.7-105.6 |
| door +x+y (corner) | 1.20 | 270 | 47 | 0.7 | 481.0 | 28.1 | 130.4 | 86.6-96.5 |
| door -x+y (y wall) 0 | 1.20 | 737 | 1270 | 0.9 | 446.7 | 82.6 | 130.4 | 130.8-140.8 |
| door -x+y (y wall) 1 | 1.20 | 687 | 797 | 0.9 | 442.3 | 77.8 | 120.4 | 135.6-145.5 |
| door -x+y (y wall) 2 | 1.20 | 376 | 265 | 1.2 | 476.8 | 39.5 | 120.4 | 87.1-97.1 |
| door -x+y (x wall) 0 | 1.20 | 735 | 1275 | 0.9 | 445.5 | 82.6 | 135.4 | 119.5-129.4 |
| door -x+y (x wall) 1 | 1.20 | 704 | 787 | 1.2 | 447.2 | 78.9 | 125.4 | 128.2-138.2 |
| door -x+y (x wall) 2 | 1.20 | 403 | 276 | 0.9 | 480.1 | 42.0 | 120.4 | 89.6-99.5 |
| door -x+y (corner) | 1.20 | 238 | 50 | 0.7 | 474.2 | 25.1 | 120.4 | 81.7-91.7 |
| door -x-y (y wall) 0 | 1.20 | 732 | 1275 | 1.0 | 456.2 | 80.4 | 125.4 | 118.4-128.4 |
| door -x-y (y wall) 1 | 1.20 | 686 | 794 | 0.9 | 442.0 | 77.7 | 130.4 | 128.2-138.2 |
| door -x-y (y wall) 2 | 1.20 | 377 | 277 | 0.9 | 456.5 | 41.4 | 105.3 | 100.0-110.0 |
| door -x-y (x wall) 0 | 1.20 | 730 | 1269 | 0.9 | 442.3 | 82.6 | 135.4 | 122.4-132.4 |
| door -x-y (x wall) 1 | 1.20 | 704 | 792 | 1.6 | 440.8 | 80.1 | 135.4 | 113.0-123.0 |
| door -x-y (x wall) 2 | 1.20 | 387 | 269 | 0.9 | 460.0 | 42.1 | 115.3 | 88.2-98.1 |
| door -x-y (corner) | 1.20 | 263 | 48 | 0.9 | 444.1 | 29.7 | 110.3 | 0.5-10.5 |
| door +x-y (y wall) 0 | 1.20 | 718 | 1272 | 0.9 | 433.9 | 82.9 | 130.4 | 125.9-135.9 |
| door +x-y (y wall) 1 | 1.20 | 687 | 792 | 1.0 | 435.3 | 79.1 | 125.4 | 123.1-133.1 |
| door +x-y (y wall) 2 | 1.20 | 402 | 267 | 0.9 | 456.7 | 44.1 | 115.3 | 93.6-103.5 |
| door +x-y (x wall) 0 | 1.20 | 738 | 1270 | 1.0 | 454.2 | 81.4 | 140.4 | 119.8-129.8 |
| door +x-y (x wall) 1 | 1.20 | 683 | 797 | 1.0 | 429.0 | 79.8 | 135.4 | 126.5-136.4 |
| door +x-y (x wall) 2 | 1.20 | 380 | 261 | 1.2 | 455.6 | 41.8 | 120.4 | 90.3-100.2 |
| door +x-y (corner) | 1.20 | 260 | 46 | 0.9 | 449.9 | 28.9 | 115.3 | 1.6-11.5 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 932 | 4.8% | 24.6% |
| -x | avenue | 5.66 | 930 | 4.8% | 24.5% |
| +y | avenue | 5.66 | 918 | 4.8% | 24.2% |
| -y | avenue | 5.66 | 925 | 4.8% | 24.4% |
| door +x+y (y wall) 0 | door | 1.20 | 726 | 3.8% | 90.3% |
| door +x+y (y wall) 1 | door | 1.20 | 722 | 3.8% | 89.8% |
| door +x+y (y wall) 2 | door | 1.20 | 388 | 2.0% | 48.2% |
| door +x+y (x wall) 0 | door | 1.20 | 733 | 3.8% | 91.1% |
| door +x+y (x wall) 1 | door | 1.20 | 699 | 3.6% | 86.9% |
| door +x+y (x wall) 2 | door | 1.20 | 353 | 1.8% | 43.9% |
| door +x+y (corner) | door | 1.20 | 270 | 1.4% | 33.6% |
| door -x+y (y wall) 0 | door | 1.20 | 737 | 3.8% | 91.6% |
| door -x+y (y wall) 1 | door | 1.20 | 687 | 3.6% | 85.4% |
| door -x+y (y wall) 2 | door | 1.20 | 376 | 2.0% | 46.8% |
| door -x+y (x wall) 0 | door | 1.20 | 735 | 3.8% | 91.4% |
| door -x+y (x wall) 1 | door | 1.20 | 704 | 3.7% | 87.5% |
| door -x+y (x wall) 2 | door | 1.20 | 403 | 2.1% | 50.1% |
| door -x+y (corner) | door | 1.20 | 238 | 1.2% | 29.6% |
| door -x-y (y wall) 0 | door | 1.20 | 732 | 3.8% | 91.0% |
| door -x-y (y wall) 1 | door | 1.20 | 686 | 3.6% | 85.3% |
| door -x-y (y wall) 2 | door | 1.20 | 377 | 2.0% | 46.9% |
| door -x-y (x wall) 0 | door | 1.20 | 730 | 3.8% | 90.8% |
| door -x-y (x wall) 1 | door | 1.20 | 704 | 3.7% | 87.5% |
| door -x-y (x wall) 2 | door | 1.20 | 387 | 2.0% | 48.1% |
| door -x-y (corner) | door | 1.20 | 263 | 1.4% | 32.7% |
| door +x-y (y wall) 0 | door | 1.20 | 718 | 3.7% | 89.3% |
| door +x-y (y wall) 1 | door | 1.20 | 687 | 3.6% | 85.4% |
| door +x-y (y wall) 2 | door | 1.20 | 402 | 2.1% | 50.0% |
| door +x-y (x wall) 0 | door | 1.20 | 738 | 3.8% | 91.8% |
| door +x-y (x wall) 1 | door | 1.20 | 683 | 3.6% | 84.9% |
| door +x-y (x wall) 2 | door | 1.20 | 380 | 2.0% | 47.3% |
| door +x-y (corner) | door | 1.20 | 260 | 1.4% | 32.3% |
| **doors (28)** | door | 33.60 | 15518 | 80.7% | |
| **avenues (4)** | avenue | 22.64 | 3705 | 19.3% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 481.0 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 51.0%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 943 | 4.9% | 943 | 4.9% |
| straight +x+y (y wing) 1 | straight | yes | 616 | 3.2% | 606 | 3.2% |
| straight +x+y (y wing) 2 | straight | yes | 304 | 1.6% | 297 | 1.5% |
| straight +x+y (x wing) 0 | straight | yes | 943 | 4.9% | 943 | 4.9% |
| straight +x+y (x wing) 1 | straight | yes | 599 | 3.1% | 590 | 3.1% |
| straight +x+y (x wing) 2 | straight | yes | 251 | 1.3% | 250 | 1.3% |
| corner +x+y | corner | yes | 812 | 4.2% | 339 | 1.8% |
| straight -x+y (y wing) 0 | straight | yes | 959 | 5.0% | 959 | 5.0% |
| straight -x+y (y wing) 1 | straight | yes | 598 | 3.1% | 592 | 3.1% |
| straight -x+y (y wing) 2 | straight | yes | 269 | 1.4% | 267 | 1.4% |
| straight -x+y (x wing) 0 | straight | yes | 946 | 4.9% | 946 | 4.9% |
| straight -x+y (x wing) 1 | straight | yes | 613 | 3.2% | 603 | 3.1% |
| straight -x+y (x wing) 2 | straight | yes | 312 | 1.6% | 309 | 1.6% |
| corner -x+y | corner | yes | 776 | 4.0% | 293 | 1.5% |
| straight -x-y (y wing) 0 | straight | yes | 940 | 4.9% | 940 | 4.9% |
| straight -x-y (y wing) 1 | straight | yes | 594 | 3.1% | 585 | 3.0% |
| straight -x-y (y wing) 2 | straight | yes | 268 | 1.4% | 268 | 1.4% |
| straight -x-y (x wing) 0 | straight | yes | 957 | 5.0% | 957 | 5.0% |
| straight -x-y (x wing) 1 | straight | yes | 611 | 3.2% | 595 | 3.1% |
| straight -x-y (x wing) 2 | straight | yes | 297 | 1.5% | 292 | 1.5% |
| corner -x-y | corner | yes | 792 | 4.1% | 331 | 1.7% |
| straight +x-y (y wing) 0 | straight | yes | 943 | 4.9% | 943 | 4.9% |
| straight +x-y (y wing) 1 | straight | yes | 603 | 3.1% | 589 | 3.1% |
| straight +x-y (y wing) 2 | straight | yes | 303 | 1.6% | 300 | 1.6% |
| straight +x-y (x wing) 0 | straight | yes | 939 | 4.9% | 939 | 4.9% |
| straight +x-y (x wing) 1 | straight | yes | 588 | 3.1% | 576 | 3.0% |
| straight +x-y (x wing) 2 | straight | yes | 291 | 1.5% | 287 | 1.5% |
| corner +x-y | corner | yes | 816 | 4.2% | 335 | 1.7% |
| **straight (24)** | | | 14687 | | 14576 | 75.8% |
| **corner (4)** | | | 3196 | | 1298 | 6.8% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 3349, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 932 | 29.0 | 429.0 | 0.30 | 0.75 | 0.0% |
| -x | 930 | 29.0 | 431.7 | 0.29 | 0.71 | 0.0% |
| +y | 918 | 29.2 | 429.2 | 0.29 | 0.74 | 0.0% |
| -y | 925 | 29.0 | 434.1 | 0.29 | 0.71 | 0.0% |
| door +x+y (y wall) 0 | 726 | 0.7 | 443.0 | 0.98 | 1.56 | 82.2% |
| door +x+y (y wall) 1 | 722 | 1.0 | 449.9 | 0.96 | 1.56 | 73.9% |
| door +x+y (y wall) 2 | 388 | 1.0 | 477.1 | 0.49 | 1.20 | 22.9% |
| door +x+y (x wall) 0 | 733 | 1.0 | 440.4 | 1.00 | 1.56 | 84.4% |
| door +x+y (x wall) 1 | 699 | 1.2 | 437.3 | 0.96 | 1.68 | 77.3% |
| door +x+y (x wall) 2 | 353 | 0.9 | 468.7 | 0.45 | 1.38 | 22.9% |
| door +x+y (corner) | 270 | 0.7 | 481.0 | 0.34 | 1.56 | 16.3% |
| door -x+y (y wall) 0 | 737 | 0.9 | 446.7 | 0.99 | 1.56 | 86.7% |
| door -x+y (y wall) 1 | 687 | 0.9 | 442.3 | 0.93 | 1.44 | 77.8% |
| door -x+y (y wall) 2 | 376 | 1.2 | 476.8 | 0.47 | 1.44 | 22.9% |
| door -x+y (x wall) 0 | 735 | 0.9 | 445.5 | 0.99 | 1.62 | 84.4% |
| door -x+y (x wall) 1 | 704 | 1.2 | 447.2 | 0.94 | 1.50 | 75.6% |
| door -x+y (x wall) 2 | 403 | 0.9 | 480.1 | 0.50 | 1.44 | 22.4% |
| door -x+y (corner) | 238 | 0.7 | 474.2 | 0.30 | 1.44 | 14.6% |
| door -x-y (y wall) 0 | 732 | 1.0 | 456.2 | 0.96 | 1.50 | 82.6% |
| door -x-y (y wall) 1 | 686 | 0.9 | 442.0 | 0.93 | 1.56 | 80.0% |
| door -x-y (y wall) 2 | 377 | 0.9 | 456.5 | 0.49 | 1.26 | 23.9% |
| door -x-y (x wall) 0 | 730 | 0.9 | 442.3 | 0.99 | 1.62 | 84.4% |
| door -x-y (x wall) 1 | 704 | 1.6 | 440.8 | 0.96 | 1.62 | 73.3% |
| door -x-y (x wall) 2 | 387 | 0.9 | 460.0 | 0.50 | 1.38 | 21.3% |
| door -x-y (corner) | 263 | 0.9 | 444.1 | 0.35 | 1.32 | 17.8% |
| door +x-y (y wall) 0 | 718 | 0.9 | 433.9 | 0.99 | 1.56 | 84.1% |
| door +x-y (y wall) 1 | 687 | 1.0 | 435.3 | 0.95 | 1.50 | 77.3% |
| door +x-y (y wall) 2 | 402 | 0.9 | 456.7 | 0.53 | 1.38 | 21.7% |
| door +x-y (x wall) 0 | 738 | 1.0 | 454.2 | 0.97 | 1.68 | 82.6% |
| door +x-y (x wall) 1 | 683 | 1.0 | 429.0 | 0.95 | 1.62 | 75.0% |
| door +x-y (x wall) 2 | 380 | 1.2 | 455.6 | 0.50 | 1.44 | 21.7% |
| door +x-y (corner) | 260 | 0.9 | 449.9 | 0.35 | 1.38 | 17.4% |

Mean flow / w J averaged over the doors 0.74, over the avenues 0.29.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 943 | 611 / 332 / 171 | 0.3 | 440.1 | 2.53 | 4.41 | 78% | 78% | 0% | 4.61 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 568 | 606 / 0 / 13 | 0.7 | 446.9 | 1.39 | 2.01 | 82% | 69% | 13% | 3.94 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 74 | 297 / 0 / 9 | 0.7 | 474.2 | 0.65 | 1.40 | 17% | 17% | 0% | 3.79 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 943 | 622 / 322 / 151 | 0.2 | 437.4 | 2.50 | 4.41 | 89% | 82% | 7% | 4.33 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 568 | 590 / 0 / 12 | 0.7 | 434.3 | 1.39 | 2.01 | 82% | 75% | 7% | 4.11 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 78 | 250 / 0 / 1 | 0.7 | 465.8 | 0.54 | 1.50 | 19% | 19% | 0% | 3.60 |
| corner +x+y | 1.20 | 85.6 | 794 | 212 / 127 / 489 | 0.7 | 477.1 | 1.74 | 3.71 | 83% | 54% | 29% | 2.52 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 959 | 625 / 336 / 216 | 0.2 | 443.7 | 2.65 | 4.61 | 78% | 78% | 0% | 4.69 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 571 | 592 / 0 / 11 | 0.7 | 439.4 | 1.37 | 2.01 | 84% | 76% | 9% | 4.10 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 75 | 267 / 0 / 2 | 0.7 | 473.8 | 0.57 | 1.60 | 19% | 19% | 0% | 3.57 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 946 | 617 / 330 / 157 | 0.5 | 442.5 | 2.50 | 4.31 | 78% | 78% | 0% | 4.62 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 583 | 603 / 0 / 12 | 0.7 | 444.3 | 1.39 | 2.01 | 82% | 73% | 9% | 4.11 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 74 | 309 / 0 / 3 | 0.7 | 477.1 | 0.65 | 2.01 | 19% | 19% | 0% | 3.76 |
| corner -x+y | 1.20 | 85.6 | 761 | 179 / 114 / 496 | 0.2 | 471.0 | 1.68 | 4.31 | 83% | 60% | 23% | 2.46 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 940 | 615 / 325 / 170 | 0.3 | 453.2 | 2.45 | 4.61 | 85% | 78% | 7% | 4.43 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 578 | 585 / 0 / 10 | 0.7 | 439.0 | 1.36 | 2.01 | 87% | 76% | 11% | 4.05 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 76 | 268 / 0 / 0 | 0.7 | 453.5 | 0.59 | 1.40 | 20% | 20% | 0% | 3.72 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 957 | 614 / 343 / 174 | 0.3 | 439.4 | 2.58 | 4.11 | 87% | 80% | 7% | 4.24 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 572 | 595 / 0 / 20 | 0.7 | 437.8 | 1.41 | 2.01 | 84% | 73% | 11% | 3.91 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 73 | 292 / 0 / 7 | 0.7 | 457.0 | 0.65 | 1.30 | 17% | 17% | 0% | 3.65 |
| corner -x-y | 1.20 | 85.6 | 772 | 213 / 118 / 478 | 0.7 | 450.9 | 1.80 | 4.01 | 87% | 52% | 35% | 2.35 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 943 | 601 / 342 / 225 | 0.5 | 431.0 | 2.71 | 4.91 | 77% | 77% | 0% | 4.67 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 574 | 589 / 0 / 14 | 0.7 | 432.4 | 1.40 | 2.21 | 84% | 75% | 9% | 4.04 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 74 | 300 / 0 / 3 | 0.7 | 453.7 | 0.67 | 1.50 | 20% | 20% | 0% | 3.68 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 939 | 620 / 319 / 163 | 0.3 | 451.3 | 2.44 | 4.21 | 76% | 76% | 0% | 4.69 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 567 | 576 / 0 / 12 | 0.7 | 426.1 | 1.38 | 1.91 | 86% | 77% | 9% | 4.12 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 75 | 287 / 0 / 4 | 0.7 | 452.7 | 0.64 | 1.30 | 17% | 17% | 0% | 3.43 |
| corner +x-y | 1.20 | 85.6 | 797 | 213 / 122 / 495 | 0.7 | 447.8 | 1.86 | 3.81 | 84% | 49% | 36% | 2.39 |

The last agent out (agent 411, t100 481.0 s): last gangway corner +x+y, exit door +x+y (corner). The gangway that cleared last: corner +x+y at 477.1 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.76 | 479.2 / 466.5 / 441.8 | 463.2 / 451.1 / 341.8 | 699220.6 | 1710403 | 0.225 |
| gangway | 1212 | 1112.9 | 6.76 | 476.3 / 461.6 / 389.0 | 463.2 / 451.1 / 341.8 | 662135.0 | 1366527 | 0.120 |
| walkway | 276 | 257.4 | 5.32 | 334.8 / 208.7 / 24.0 | 270.4 / 190.1 / 5.6 | 152.1 | 56788 | 0.431 |
| avenue | 912 | 858.9 | 2.69 | 393.2 / 28.0 / 0.0 | 305.2 / 1.6 / 0.0 | 0.0 | 106395 | 1.325 |
| exit | 32 | 3.2 | 0.00 | 458.3 / 455.8 / 430.3 | 330.2 / 304.5 / 183.0 | 1241.6 | 2180 | 1.168 |
| concourse | 1116 | 1043.8 | 6.11 | 447.6 / 161.6 / 86.9 | 316.4 / 143.1 / 62.6 | 35691.9 | 178512 | 0.296 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.57 | 411.7 / 398.1 / 374.5 | 406.7 / 397.6 / 361.4 | 725419.3 | 2010379 | 0.045 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -26.5 | 29.5 | gangway | 1.00 | 6.29 | 405.8 | 389.0 | 341.8 | 2050.7 | 0.023 |
| 2 | -29.5 | 26.5 | gangway | 1.00 | 6.24 | 401.6 | 369.8 | 336.5 | 2006.5 | 0.021 |
| 3 | -26.5 | -29.5 | gangway | 1.00 | 6.29 | 393.4 | 376.0 | 335.3 | 1985.2 | 0.018 |
| 4 | 26.5 | 28.5 | gangway | 1.00 | 6.00 | 404.7 | 402.1 | 339.5 | 1965.9 | 0.022 |
| 5 | -28.5 | 26.5 | gangway | 1.00 | 5.97 | 401.8 | 399.1 | 336.0 | 1949.0 | 0.021 |
| 6 | 29.5 | 26.5 | gangway | 1.00 | 6.14 | 401.1 | 389.2 | 336.3 | 1946.6 | 0.022 |
| 7 | 27.5 | 28.5 | gangway | 1.00 | 6.01 | 408.2 | 403.5 | 339.7 | 1915.4 | 0.025 |
| 8 | 29.5 | -26.5 | gangway | 1.00 | 6.10 | 381.3 | 367.1 | 323.9 | 1903.9 | 0.020 |
| 9 | 27.5 | 27.5 | gangway | 1.00 | 6.07 | 396.7 | 394.4 | 327.8 | 1888.3 | 0.021 |
| 10 | 26.5 | -29.5 | gangway | 1.00 | 6.13 | 382.0 | 367.5 | 315.4 | 1833.4 | 0.024 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -30.5 | 25.5 | seat row | 0.64 | 6.74 | 373.4 | 365.4 | 326.6 | 1325.7 | 0.030 |
| 2 | -25.5 | 29.5 | seat row | 0.71 | 5.86 | 401.4 | 388.6 | 330.7 | 1285.1 | 0.026 |
| 3 | -25.5 | 30.5 | seat row | 0.64 | 6.67 | 377.4 | 365.4 | 317.3 | 1274.3 | 0.031 |
| 4 | -29.5 | 25.5 | seat row | 0.71 | 5.62 | 385.3 | 375.2 | 326.4 | 1271.0 | 0.025 |
| 5 | 30.5 | -25.5 | seat row | 0.64 | 6.61 | 361.2 | 348.9 | 318.9 | 1252.8 | 0.030 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1427; agent-steps of seated agents on another row's clearway: 24674.

## Deposit check

Person-seconds deposited: 3726884.5, of them in excluded cells: 6102.913.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 427263 overlapping pair-steps: p99 0.0038, max 0.0466 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0038 max 0.0466; venue-geometry 5: p99 0.0008 max 0.0008 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 15 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.39 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 582 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
