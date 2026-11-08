# Experiment `M_load150_s3`

**Task 5.8 stage 2: venue M, 150% requested (seed 3): every seat + standing on the walkway and concourse (M, L: the achievable maximum, also the 125% request)**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 19223 agents (load 121.4%, requested 150%): every one of the 15832 seats and 3391 standing (spawnOvercrowdedCrowd, seed 3; below), buffer N = 32768, 2760 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 1245012 evaluations, 54188 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.21)** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `cd8e0bbf3411846ca7aa6719887d122a142a7ca1`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-15T16:33:45, 107.9 s wall.

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
| t50 | 1053 | 184.2 |
| t90 | 2115 | 369.9 |
| t100 | 2760 | 482.7 |

t_p: the step by which ceil(p x 19223) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 914 | 86 | 29.0 | 428.7 | 24.2 | 65.9 | 28.3-38.3 |
| -x | 5.66 | 914 | 81 | 29.0 | 431.8 | 24.0 | 56.4 | 28.7-38.7 |
| +y | 5.66 | 919 | 80 | 29.0 | 436.2 | 23.9 | 56.4 | 28.5-38.5 |
| -y | 5.66 | 921 | 90 | 29.0 | 431.0 | 24.3 | 61.7 | 28.5-38.5 |
| door +x+y (y wall) 0 | 1.20 | 735 | 1280 | 0.9 | 456.5 | 80.6 | 140.4 | 129.6-139.6 |
| door +x+y (y wall) 1 | 1.20 | 706 | 801 | 0.9 | 441.3 | 80.1 | 135.4 | 123.5-133.5 |
| door +x+y (y wall) 2 | 1.20 | 404 | 269 | 1.4 | 482.7 | 42.0 | 130.4 | 80.3-90.3 |
| door +x+y (x wall) 0 | 1.20 | 722 | 1274 | 0.9 | 438.0 | 82.6 | 135.4 | 112.1-122.1 |
| door +x+y (x wall) 1 | 1.20 | 698 | 790 | 0.7 | 438.0 | 79.8 | 140.4 | 119.8-129.8 |
| door +x+y (x wall) 2 | 1.20 | 375 | 269 | 1.0 | 477.3 | 39.4 | 105.3 | 18.5-28.5 |
| door +x+y (corner) | 1.20 | 253 | 45 | 0.9 | 468.7 | 27.0 | 115.3 | 3.8-13.8 |
| door -x+y (y wall) 0 | 1.20 | 727 | 1269 | 1.0 | 428.9 | 84.9 | 130.4 | 120.0-130.0 |
| door -x+y (y wall) 1 | 1.20 | 691 | 797 | 1.0 | 450.9 | 76.8 | 135.4 | 114.6-124.5 |
| door -x+y (y wall) 2 | 1.20 | 380 | 265 | 0.7 | 466.1 | 40.8 | 120.4 | 86.9-96.9 |
| door -x+y (x wall) 0 | 1.20 | 743 | 1274 | 0.9 | 458.3 | 81.2 | 125.4 | 125.1-135.0 |
| door -x+y (x wall) 1 | 1.20 | 712 | 805 | 0.9 | 455.8 | 78.2 | 135.4 | 123.5-133.5 |
| door -x+y (x wall) 2 | 1.20 | 386 | 266 | 0.9 | 470.5 | 41.1 | 120.4 | 89.7-99.7 |
| door -x+y (corner) | 1.20 | 248 | 41 | 1.0 | 471.9 | 26.3 | 110.3 | 2.1-12.1 |
| door -x-y (y wall) 0 | 1.20 | 741 | 1270 | 1.0 | 449.9 | 82.5 | 130.4 | 112.5-122.4 |
| door -x-y (y wall) 1 | 1.20 | 717 | 800 | 0.9 | 463.5 | 77.5 | 125.4 | 136.6-146.6 |
| door -x-y (y wall) 2 | 1.20 | 381 | 271 | 1.0 | 471.5 | 40.5 | 125.4 | 85.7-95.7 |
| door -x-y (x wall) 0 | 1.20 | 740 | 1281 | 0.9 | 449.3 | 82.5 | 140.4 | 130.7-140.6 |
| door -x-y (x wall) 1 | 1.20 | 710 | 791 | 1.0 | 457.2 | 77.8 | 130.4 | 117.0-127.0 |
| door -x-y (x wall) 2 | 1.20 | 360 | 269 | 1.0 | 468.9 | 38.5 | 125.4 | 86.1-96.0 |
| door -x-y (corner) | 1.20 | 240 | 39 | 0.9 | 478.9 | 25.1 | 130.4 | 65.1-75.0 |
| door +x-y (y wall) 0 | 1.20 | 720 | 1269 | 1.0 | 446.9 | 80.7 | 125.4 | 131.7-141.7 |
| door +x-y (y wall) 1 | 1.20 | 685 | 799 | 0.9 | 432.7 | 79.3 | 130.4 | 133.1-143.1 |
| door +x-y (y wall) 2 | 1.20 | 389 | 266 | 0.9 | 457.2 | 42.6 | 115.3 | 86.1-96.0 |
| door +x-y (x wall) 0 | 1.20 | 735 | 1272 | 0.9 | 442.2 | 83.2 | 130.4 | 117.2-127.2 |
| door +x-y (x wall) 1 | 1.20 | 692 | 797 | 1.0 | 432.9 | 80.1 | 125.4 | 110.2-120.2 |
| door +x-y (x wall) 2 | 1.20 | 388 | 270 | 0.9 | 452.8 | 42.9 | 125.4 | 90.6-100.6 |
| door +x-y (corner) | 1.20 | 277 | 47 | 0.9 | 457.6 | 30.3 | 110.3 | 2.4-12.4 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 914 | 4.8% | 24.0% |
| -x | avenue | 5.66 | 914 | 4.8% | 24.0% |
| +y | avenue | 5.66 | 919 | 4.8% | 24.1% |
| -y | avenue | 5.66 | 921 | 4.8% | 24.2% |
| door +x+y (y wall) 0 | door | 1.20 | 735 | 3.8% | 91.1% |
| door +x+y (y wall) 1 | door | 1.20 | 706 | 3.7% | 87.5% |
| door +x+y (y wall) 2 | door | 1.20 | 404 | 2.1% | 50.1% |
| door +x+y (x wall) 0 | door | 1.20 | 722 | 3.8% | 89.5% |
| door +x+y (x wall) 1 | door | 1.20 | 698 | 3.6% | 86.5% |
| door +x+y (x wall) 2 | door | 1.20 | 375 | 2.0% | 46.5% |
| door +x+y (corner) | door | 1.20 | 253 | 1.3% | 31.3% |
| door -x+y (y wall) 0 | door | 1.20 | 727 | 3.8% | 90.1% |
| door -x+y (y wall) 1 | door | 1.20 | 691 | 3.6% | 85.6% |
| door -x+y (y wall) 2 | door | 1.20 | 380 | 2.0% | 47.1% |
| door -x+y (x wall) 0 | door | 1.20 | 743 | 3.9% | 92.1% |
| door -x+y (x wall) 1 | door | 1.20 | 712 | 3.7% | 88.2% |
| door -x+y (x wall) 2 | door | 1.20 | 386 | 2.0% | 47.8% |
| door -x+y (corner) | door | 1.20 | 248 | 1.3% | 30.7% |
| door -x-y (y wall) 0 | door | 1.20 | 741 | 3.9% | 91.8% |
| door -x-y (y wall) 1 | door | 1.20 | 717 | 3.7% | 88.8% |
| door -x-y (y wall) 2 | door | 1.20 | 381 | 2.0% | 47.2% |
| door -x-y (x wall) 0 | door | 1.20 | 740 | 3.8% | 91.7% |
| door -x-y (x wall) 1 | door | 1.20 | 710 | 3.7% | 88.0% |
| door -x-y (x wall) 2 | door | 1.20 | 360 | 1.9% | 44.6% |
| door -x-y (corner) | door | 1.20 | 240 | 1.2% | 29.7% |
| door +x-y (y wall) 0 | door | 1.20 | 720 | 3.7% | 89.2% |
| door +x-y (y wall) 1 | door | 1.20 | 685 | 3.6% | 84.9% |
| door +x-y (y wall) 2 | door | 1.20 | 389 | 2.0% | 48.2% |
| door +x-y (x wall) 0 | door | 1.20 | 735 | 3.8% | 91.1% |
| door +x-y (x wall) 1 | door | 1.20 | 692 | 3.6% | 85.7% |
| door +x-y (x wall) 2 | door | 1.20 | 388 | 2.0% | 48.1% |
| door +x-y (corner) | door | 1.20 | 277 | 1.4% | 34.3% |
| **doors (28)** | door | 33.60 | 15555 | 80.9% | |
| **avenues (4)** | avenue | 22.64 | 3668 | 19.1% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 482.7 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 50.8%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 929 | 4.8% | 929 | 4.8% |
| straight +x+y (y wing) 1 | straight | yes | 605 | 3.1% | 598 | 3.1% |
| straight +x+y (y wing) 2 | straight | yes | 326 | 1.7% | 323 | 1.7% |
| straight +x+y (x wing) 0 | straight | yes | 944 | 4.9% | 944 | 4.9% |
| straight +x+y (x wing) 1 | straight | yes | 609 | 3.2% | 601 | 3.1% |
| straight +x+y (x wing) 2 | straight | yes | 276 | 1.4% | 274 | 1.4% |
| corner +x+y | corner | yes | 813 | 4.2% | 298 | 1.6% |
| straight -x+y (y wing) 0 | straight | yes | 955 | 5.0% | 955 | 5.0% |
| straight -x+y (y wing) 1 | straight | yes | 596 | 3.1% | 588 | 3.1% |
| straight -x+y (y wing) 2 | straight | yes | 281 | 1.5% | 279 | 1.5% |
| straight -x+y (x wing) 0 | straight | yes | 930 | 4.8% | 930 | 4.8% |
| straight -x+y (x wing) 1 | straight | yes | 601 | 3.1% | 594 | 3.1% |
| straight -x+y (x wing) 2 | straight | yes | 306 | 1.6% | 302 | 1.6% |
| corner -x+y | corner | yes | 806 | 4.2% | 319 | 1.7% |
| straight -x-y (y wing) 0 | straight | yes | 948 | 4.9% | 948 | 4.9% |
| straight -x-y (y wing) 1 | straight | yes | 606 | 3.2% | 598 | 3.1% |
| straight -x-y (y wing) 2 | straight | yes | 303 | 1.6% | 296 | 1.5% |
| straight -x-y (x wing) 0 | straight | yes | 947 | 4.9% | 947 | 4.9% |
| straight -x-y (x wing) 1 | straight | yes | 609 | 3.2% | 599 | 3.1% |
| straight -x-y (x wing) 2 | straight | yes | 276 | 1.4% | 275 | 1.4% |
| corner -x-y | corner | yes | 793 | 4.1% | 305 | 1.6% |
| straight +x-y (y wing) 0 | straight | yes | 936 | 4.9% | 936 | 4.9% |
| straight +x-y (y wing) 1 | straight | yes | 591 | 3.1% | 576 | 3.0% |
| straight +x-y (y wing) 2 | straight | yes | 291 | 1.5% | 286 | 1.5% |
| straight +x-y (x wing) 0 | straight | yes | 947 | 4.9% | 947 | 4.9% |
| straight +x-y (x wing) 1 | straight | yes | 601 | 3.1% | 589 | 3.1% |
| straight +x-y (x wing) 2 | straight | yes | 281 | 1.5% | 281 | 1.5% |
| corner +x-y | corner | yes | 805 | 4.2% | 353 | 1.8% |
| **straight (24)** | | | 14694 | | 14595 | 75.9% |
| **corner (4)** | | | 3217 | | 1275 | 6.6% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 3353, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 914 | 29.0 | 428.7 | 0.29 | 0.79 | 0.0% |
| -x | 914 | 29.0 | 431.8 | 0.29 | 0.67 | 0.0% |
| +y | 919 | 29.0 | 436.2 | 0.29 | 0.67 | 0.0% |
| -y | 921 | 29.0 | 431.0 | 0.29 | 0.74 | 0.0% |
| door +x+y (y wall) 0 | 735 | 0.9 | 456.5 | 0.96 | 1.68 | 82.6% |
| door +x+y (y wall) 1 | 706 | 0.9 | 441.3 | 0.96 | 1.62 | 75.6% |
| door +x+y (y wall) 2 | 404 | 1.4 | 482.7 | 0.50 | 1.56 | 20.4% |
| door +x+y (x wall) 0 | 722 | 0.9 | 438.0 | 0.99 | 1.62 | 86.4% |
| door +x+y (x wall) 1 | 698 | 0.7 | 438.0 | 0.95 | 1.68 | 72.7% |
| door +x+y (x wall) 2 | 375 | 1.0 | 477.3 | 0.47 | 1.26 | 22.9% |
| door +x+y (corner) | 253 | 0.9 | 468.7 | 0.32 | 1.38 | 18.8% |
| door -x+y (y wall) 0 | 727 | 1.0 | 428.9 | 1.02 | 1.56 | 84.1% |
| door -x+y (y wall) 1 | 691 | 1.0 | 450.9 | 0.92 | 1.62 | 71.7% |
| door -x+y (y wall) 2 | 380 | 0.7 | 466.1 | 0.49 | 1.44 | 21.3% |
| door -x+y (x wall) 0 | 743 | 0.9 | 458.3 | 0.97 | 1.50 | 80.4% |
| door -x+y (x wall) 1 | 712 | 0.9 | 455.8 | 0.94 | 1.62 | 73.9% |
| door -x+y (x wall) 2 | 386 | 0.9 | 470.5 | 0.49 | 1.44 | 22.9% |
| door -x+y (corner) | 248 | 1.0 | 471.9 | 0.31 | 1.32 | 14.6% |
| door -x-y (y wall) 0 | 741 | 1.0 | 449.9 | 0.99 | 1.56 | 84.8% |
| door -x-y (y wall) 1 | 717 | 0.9 | 463.5 | 0.93 | 1.50 | 74.5% |
| door -x-y (y wall) 2 | 381 | 1.0 | 471.5 | 0.48 | 1.50 | 20.8% |
| door -x-y (x wall) 0 | 740 | 0.9 | 449.3 | 0.99 | 1.68 | 82.6% |
| door -x-y (x wall) 1 | 710 | 1.0 | 457.2 | 0.93 | 1.56 | 71.7% |
| door -x-y (x wall) 2 | 360 | 1.0 | 468.9 | 0.46 | 1.50 | 20.8% |
| door -x-y (corner) | 240 | 0.9 | 478.9 | 0.30 | 1.56 | 16.3% |
| door +x-y (y wall) 0 | 720 | 1.0 | 446.9 | 0.97 | 1.50 | 82.2% |
| door +x-y (y wall) 1 | 685 | 0.9 | 432.7 | 0.95 | 1.56 | 77.3% |
| door +x-y (y wall) 2 | 389 | 0.9 | 457.2 | 0.51 | 1.38 | 23.9% |
| door +x-y (x wall) 0 | 735 | 0.9 | 442.2 | 1.00 | 1.56 | 84.4% |
| door +x-y (x wall) 1 | 692 | 1.0 | 432.9 | 0.96 | 1.50 | 75.0% |
| door +x-y (x wall) 2 | 388 | 0.9 | 452.8 | 0.51 | 1.50 | 21.7% |
| door +x-y (corner) | 277 | 0.9 | 457.6 | 0.36 | 1.32 | 17.4% |

Mean flow / w J averaged over the doors 0.74, over the avenues 0.29.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 929 | 613 / 317 / 148 | 0.7 | 453.5 | 2.38 | 4.31 | 78% | 78% | 0% | 4.59 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 571 | 598 / 0 / 10 | 0.7 | 438.3 | 1.39 | 1.91 | 86% | 75% | 11% | 4.00 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 80 | 323 / 0 / 4 | 0.7 | 479.8 | 0.68 | 1.71 | 20% | 20% | 0% | 3.85 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 944 | 607 / 337 / 199 | 0.2 | 435.0 | 2.63 | 4.51 | 86% | 80% | 7% | 4.29 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 565 | 602 / 0 / 9 | 0.7 | 435.0 | 1.41 | 1.91 | 82% | 73% | 9% | 3.97 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 77 | 274 / 0 / 2 | 0.7 | 474.3 | 0.58 | 1.30 | 19% | 17% | 2% | 3.81 |
| corner +x+y | 1.20 | 85.6 | 801 | 182 / 116 / 528 | 0.7 | 473.8 | 1.75 | 3.71 | 83% | 52% | 31% | 2.44 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 955 | 611 / 344 / 225 | 0.5 | 425.9 | 2.77 | 4.61 | 91% | 81% | 9% | 4.26 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 566 | 588 / 0 / 17 | 0.7 | 447.9 | 1.35 | 2.21 | 84% | 71% | 13% | 3.85 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 76 | 279 / 0 / 2 | 0.7 | 463.2 | 0.61 | 1.60 | 19% | 19% | 0% | 3.68 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 930 | 626 / 304 / 140 | 0.5 | 455.3 | 2.35 | 4.31 | 78% | 78% | 0% | 4.65 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 572 | 594 / 0 / 12 | 0.7 | 452.8 | 1.34 | 2.01 | 83% | 70% | 13% | 3.98 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 76 | 302 / 0 / 5 | 0.7 | 467.5 | 0.66 | 1.91 | 17% | 17% | 0% | 3.65 |
| corner -x+y | 1.20 | 85.6 | 792 | 196 / 123 / 509 | 0.7 | 468.1 | 1.77 | 3.81 | 85% | 53% | 32% | 2.42 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 948 | 629 / 319 / 205 | 0.3 | 446.9 | 2.58 | 4.71 | 78% | 78% | 0% | 4.63 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 568 | 598 / 0 / 11 | 0.7 | 460.5 | 1.32 | 1.91 | 79% | 68% | 11% | 3.98 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 77 | 296 / 0 / 10 | 0.7 | 468.6 | 0.65 | 1.50 | 21% | 21% | 0% | 3.44 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 947 | 620 / 327 / 182 | 0.5 | 446.4 | 2.53 | 4.71 | 87% | 80% | 7% | 4.29 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 574 | 599 / 0 / 11 | 0.7 | 454.2 | 1.34 | 2.01 | 78% | 67% | 11% | 4.02 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 76 | 275 / 0 / 1 | 0.7 | 466.0 | 0.59 | 1.60 | 19% | 19% | 0% | 3.76 |
| corner -x-y | 1.20 | 85.6 | 778 | 186 / 119 / 506 | 0.7 | 475.2 | 1.71 | 3.71 | 83% | 62% | 21% | 2.55 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 936 | 605 / 331 / 196 | 0.3 | 443.9 | 2.55 | 4.61 | 78% | 78% | 0% | 4.74 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 573 | 576 / 0 / 20 | 0.7 | 429.7 | 1.39 | 2.01 | 86% | 75% | 11% | 4.02 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 74 | 286 / 0 / 8 | 0.7 | 454.2 | 0.65 | 1.40 | 20% | 20% | 0% | 3.91 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 947 | 621 / 327 / 156 | 0.3 | 439.2 | 2.51 | 4.11 | 78% | 78% | 0% | 4.57 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 581 | 589 / 0 / 14 | 0.7 | 429.9 | 1.40 | 2.01 | 86% | 77% | 9% | 4.04 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 74 | 281 / 0 / 0 | 0.7 | 449.9 | 0.63 | 1.30 | 17% | 17% | 0% | 4.01 |
| corner +x-y | 1.20 | 85.6 | 783 | 236 / 117 / 472 | 0.7 | 453.7 | 1.82 | 4.31 | 85% | 46% | 39% | 2.33 |

The last agent out (agent 449, t100 482.7 s): last gangway straight +x+y (y wing) 2, exit door +x+y (y wall) 2. The gangway that cleared last: straight +x+y (y wing) 2 at 479.8 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.72 | 478.7 / 470.0 / 444.1 | 466.7 / 436.7 / 340.0 | 686110.9 | 1712170 | 0.225 |
| gangway | 1212 | 1112.9 | 6.72 | 478.0 / 462.1 / 385.0 | 466.7 / 436.7 / 340.0 | 649136.1 | 1366442 | 0.121 |
| walkway | 276 | 257.4 | 5.41 | 338.4 / 219.5 / 39.7 | 257.1 / 212.5 / 24.8 | 363.4 | 62461 | 0.392 |
| avenue | 912 | 858.9 | 2.59 | 394.4 / 11.9 / 0.0 | 293.1 / 1.4 / 0.0 | 0.0 | 105361 | 1.325 |
| exit | 32 | 3.2 | 0.00 | 466.7 / 463.7 / 435.3 | 328.6 / 301.0 / 182.8 | 1241.7 | 2179 | 1.173 |
| concourse | 1116 | 1043.8 | 6.01 | 444.4 / 156.5 / 94.1 | 313.3 / 139.4 / 62.1 | 35369.7 | 175727 | 0.300 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.58 | 422.9 / 399.1 / 374.5 | 403.0 / 398.6 / 371.3 | 726304.6 | 2010578 | 0.046 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -29.5 | 26.5 | gangway | 1.00 | 6.10 | 396.5 | 360.7 | 339.5 | 2002.3 | 0.023 |
| 2 | -26.5 | -29.5 | gangway | 1.00 | 6.02 | 390.9 | 376.7 | 340.0 | 1943.5 | 0.026 |
| 3 | -26.5 | 29.5 | gangway | 1.00 | 6.31 | 392.7 | 380.4 | 327.6 | 1935.7 | 0.024 |
| 4 | 26.5 | 29.5 | gangway | 1.00 | 6.01 | 405.4 | 394.1 | 329.3 | 1919.4 | 0.024 |
| 5 | -26.5 | -28.5 | gangway | 1.00 | 6.07 | 400.5 | 397.9 | 329.0 | 1918.3 | 0.022 |
| 6 | 26.5 | -29.5 | gangway | 1.00 | 5.83 | 386.7 | 376.7 | 336.5 | 1885.5 | 0.022 |
| 7 | -29.5 | -26.5 | gangway | 1.00 | 5.92 | 392.0 | 371.2 | 328.1 | 1877.9 | 0.027 |
| 8 | 29.5 | -26.5 | gangway | 1.00 | 5.95 | 384.6 | 378.7 | 318.2 | 1816.8 | 0.022 |
| 9 | -28.5 | 26.5 | gangway | 1.00 | 5.88 | 399.7 | 397.0 | 325.5 | 1779.7 | 0.024 |
| 10 | 29.5 | 26.5 | gangway | 1.00 | 5.92 | 398.6 | 364.3 | 312.6 | 1776.1 | 0.028 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -29.5 | 25.5 | seat row | 0.71 | 5.73 | 385.1 | 383.6 | 335.1 | 1322.0 | 0.025 |
| 2 | 25.5 | 30.5 | seat row | 0.64 | 6.87 | 375.3 | 373.1 | 326.6 | 1306.9 | 0.030 |
| 3 | 25.5 | 29.5 | seat row | 0.71 | 5.64 | 403.0 | 388.3 | 322.9 | 1256.3 | 0.027 |
| 4 | -25.5 | -30.5 | seat row | 0.64 | 6.40 | 363.6 | 354.7 | 315.2 | 1245.8 | 0.031 |
| 5 | -25.5 | 29.5 | seat row | 0.71 | 5.69 | 380.4 | 378.8 | 319.0 | 1238.9 | 0.023 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1452; agent-steps of seated agents on another row's clearway: 24068.

## Deposit check

Person-seconds deposited: 3728772.8, of them in excluded cells: 6024.397.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 407935 overlapping pair-steps: p99 0.0038, max 0.0918 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0038 max 0.0918; venue-geometry 3: p99 0.0018 max 0.0018 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 11 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.34 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 588 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
