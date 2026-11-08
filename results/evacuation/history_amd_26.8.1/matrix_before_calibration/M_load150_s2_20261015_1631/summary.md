# Experiment `M_load150_s2`

**Task 5.8 stage 2: venue M, 150% requested (seed 2): every seat + standing on the walkway and concourse (M, L: the achievable maximum, also the 125% request)**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 19223 agents (load 121.4%, requested 150%): every one of the 15832 seats and 3391 standing (spawnOvercrowdedCrowd, seed 2; below), buffer N = 32768, 3442 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 1245279 evaluations, 53874 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.21)** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `cd8e0bbf3411846ca7aa6719887d122a142a7ca1`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-15T16:31:55, 95.5 s wall.

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
| t50 | 1048 | 183.3 |
| t90 | 2115 | 369.9 |
| t100 | 3442 | 602.0 |

t_p: the step by which ceil(p x 19223) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 928 | 86 | 29.0 | 442.2 | 23.8 | 61.7 | 28.9-38.8 |
| -x | 5.66 | 912 | 84 | 29.0 | 430.4 | 24.1 | 58.5 | 28.9-38.8 |
| +y | 5.66 | 929 | 81 | 29.0 | 440.1 | 23.9 | 59.5 | 28.5-38.5 |
| -y | 5.66 | 919 | 91 | 29.0 | 430.6 | 24.2 | 59.5 | 28.9-38.8 |
| door +x+y (y wall) 0 | 1.20 | 725 | 1273 | 0.9 | 435.9 | 83.3 | 125.4 | 131.5-141.5 |
| door +x+y (y wall) 1 | 1.20 | 717 | 794 | 0.9 | 449.5 | 79.9 | 130.4 | 122.4-132.4 |
| door +x+y (y wall) 2 | 1.20 | 393 | 268 | 0.9 | 479.9 | 41.0 | 120.4 | 91.1-101.1 |
| door +x+y (x wall) 0 | 1.20 | 743 | 1275 | 0.7 | 451.3 | 82.4 | 135.4 | 144.1-154.1 |
| door +x+y (x wall) 1 | 1.20 | 698 | 798 | 0.9 | 453.4 | 77.1 | 125.4 | 132.4-142.4 |
| door +x+y (x wall) 2 | 1.20 | 367 | 270 | 1.0 | 473.1 | 38.9 | 105.3 | 1.7-11.7 |
| door +x+y (corner) | 1.20 | 234 | 44 | 0.9 | 481.2 | 24.4 | 120.4 | 3.3-13.3 |
| door -x+y (y wall) 0 | 1.20 | 746 | 1276 | 1.4 | 459.8 | 81.3 | 130.4 | 119.5-129.4 |
| door -x+y (y wall) 1 | 1.20 | 698 | 796 | 0.7 | 442.3 | 79.0 | 135.4 | 111.9-121.9 |
| door -x+y (y wall) 2 | 1.20 | 374 | 266 | 1.0 | 472.8 | 39.6 | 125.4 | 88.9-98.8 |
| door -x+y (x wall) 0 | 1.20 | 725 | 1275 | 0.9 | 602.0 | 60.3 | 130.4 | 132.9-142.9 |
| door -x+y (x wall) 1 | 1.20 | 707 | 790 | 0.9 | 447.6 | 79.1 | 125.4 | 111.6-121.6 |
| door -x+y (x wall) 2 | 1.20 | 395 | 276 | 1.0 | 481.9 | 41.1 | 105.3 | 82.2-92.2 |
| door -x+y (corner) | 1.20 | 244 | 47 | 0.9 | 477.5 | 25.6 | 115.3 | 62.4-72.4 |
| door -x-y (y wall) 0 | 1.20 | 729 | 1273 | 1.0 | 435.3 | 83.9 | 130.4 | 105.8-115.8 |
| door -x-y (y wall) 1 | 1.20 | 688 | 791 | 1.0 | 439.9 | 78.4 | 130.4 | 115.4-125.4 |
| door -x-y (y wall) 2 | 1.20 | 373 | 261 | 1.0 | 469.4 | 39.8 | 110.3 | 63.5-73.5 |
| door -x-y (x wall) 0 | 1.20 | 727 | 1275 | 1.2 | 458.3 | 79.5 | 130.4 | 122.8-132.8 |
| door -x-y (x wall) 1 | 1.20 | 680 | 799 | 0.7 | 436.0 | 78.1 | 130.4 | 122.6-132.6 |
| door -x-y (x wall) 2 | 1.20 | 413 | 261 | 1.4 | 471.0 | 44.0 | 105.3 | 93.7-103.7 |
| door -x-y (corner) | 1.20 | 272 | 51 | 0.7 | 463.9 | 29.4 | 110.3 | 0.5-10.5 |
| door +x-y (y wall) 0 | 1.20 | 736 | 1275 | 0.7 | 437.4 | 84.2 | 135.4 | 124.4-134.3 |
| door +x-y (y wall) 1 | 1.20 | 702 | 798 | 1.0 | 433.8 | 81.1 | 135.4 | 124.7-134.7 |
| door +x-y (y wall) 2 | 1.20 | 383 | 267 | 1.0 | 445.5 | 43.1 | 120.4 | 84.8-94.8 |
| door +x-y (x wall) 0 | 1.20 | 722 | 1266 | 1.0 | 441.1 | 82.0 | 125.4 | 111.1-121.0 |
| door +x-y (x wall) 1 | 1.20 | 723 | 801 | 0.9 | 445.5 | 81.3 | 130.4 | 122.4-132.4 |
| door +x-y (x wall) 2 | 1.20 | 366 | 270 | 1.0 | 454.4 | 40.3 | 115.3 | 90.6-100.6 |
| door +x-y (corner) | 1.20 | 255 | 45 | 0.9 | 455.6 | 28.0 | 125.4 | 72.9-82.9 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 928 | 4.8% | 19.5% |
| -x | avenue | 5.66 | 912 | 4.7% | 19.2% |
| +y | avenue | 5.66 | 929 | 4.8% | 19.6% |
| -y | avenue | 5.66 | 919 | 4.8% | 19.4% |
| door +x+y (y wall) 0 | door | 1.20 | 725 | 3.8% | 72.0% |
| door +x+y (y wall) 1 | door | 1.20 | 717 | 3.7% | 71.2% |
| door +x+y (y wall) 2 | door | 1.20 | 393 | 2.0% | 39.0% |
| door +x+y (x wall) 0 | door | 1.20 | 743 | 3.9% | 73.8% |
| door +x+y (x wall) 1 | door | 1.20 | 698 | 3.6% | 69.3% |
| door +x+y (x wall) 2 | door | 1.20 | 367 | 1.9% | 36.5% |
| door +x+y (corner) | door | 1.20 | 234 | 1.2% | 23.2% |
| door -x+y (y wall) 0 | door | 1.20 | 746 | 3.9% | 74.1% |
| door -x+y (y wall) 1 | door | 1.20 | 698 | 3.6% | 69.3% |
| door -x+y (y wall) 2 | door | 1.20 | 374 | 1.9% | 37.2% |
| door -x+y (x wall) 0 | door | 1.20 | 725 | 3.8% | 72.0% |
| door -x+y (x wall) 1 | door | 1.20 | 707 | 3.7% | 70.2% |
| door -x+y (x wall) 2 | door | 1.20 | 395 | 2.1% | 39.2% |
| door -x+y (corner) | door | 1.20 | 244 | 1.3% | 24.2% |
| door -x-y (y wall) 0 | door | 1.20 | 729 | 3.8% | 72.4% |
| door -x-y (y wall) 1 | door | 1.20 | 688 | 3.6% | 68.3% |
| door -x-y (y wall) 2 | door | 1.20 | 373 | 1.9% | 37.1% |
| door -x-y (x wall) 0 | door | 1.20 | 727 | 3.8% | 72.2% |
| door -x-y (x wall) 1 | door | 1.20 | 680 | 3.5% | 67.6% |
| door -x-y (x wall) 2 | door | 1.20 | 413 | 2.1% | 41.0% |
| door -x-y (corner) | door | 1.20 | 272 | 1.4% | 27.0% |
| door +x-y (y wall) 0 | door | 1.20 | 736 | 3.8% | 73.1% |
| door +x-y (y wall) 1 | door | 1.20 | 702 | 3.7% | 69.7% |
| door +x-y (y wall) 2 | door | 1.20 | 383 | 2.0% | 38.0% |
| door +x-y (x wall) 0 | door | 1.20 | 722 | 3.8% | 71.7% |
| door +x-y (x wall) 1 | door | 1.20 | 723 | 3.8% | 71.8% |
| door +x-y (x wall) 2 | door | 1.20 | 366 | 1.9% | 36.4% |
| door +x-y (corner) | door | 1.20 | 255 | 1.3% | 25.3% |
| **doors (28)** | door | 33.60 | 15535 | 80.8% | |
| **avenues (4)** | avenue | 22.64 | 3688 | 19.2% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 602.0 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 40.7%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 951 | 4.9% | 951 | 4.9% |
| straight +x+y (y wing) 1 | straight | yes | 618 | 3.2% | 610 | 3.2% |
| straight +x+y (y wing) 2 | straight | yes | 296 | 1.5% | 296 | 1.5% |
| straight +x+y (x wing) 0 | straight | yes | 942 | 4.9% | 942 | 4.9% |
| straight +x+y (x wing) 1 | straight | yes | 606 | 3.2% | 593 | 3.1% |
| straight +x+y (x wing) 2 | straight | yes | 275 | 1.4% | 269 | 1.4% |
| corner +x+y | corner | yes | 800 | 4.2% | 308 | 1.6% |
| straight -x+y (y wing) 0 | straight | yes | 948 | 4.9% | 948 | 4.9% |
| straight -x+y (y wing) 1 | straight | yes | 608 | 3.2% | 600 | 3.1% |
| straight -x+y (y wing) 2 | straight | yes | 290 | 1.5% | 287 | 1.5% |
| straight -x+y (x wing) 0 | straight | yes | 949 | 4.9% | 949 | 4.9% |
| straight -x+y (x wing) 1 | straight | yes | 620 | 3.2% | 609 | 3.2% |
| straight -x+y (x wing) 2 | straight | yes | 289 | 1.5% | 289 | 1.5% |
| corner -x+y | corner | yes | 792 | 4.1% | 286 | 1.5% |
| straight -x-y (y wing) 0 | straight | yes | 939 | 4.9% | 939 | 4.9% |
| straight -x-y (y wing) 1 | straight | yes | 597 | 3.1% | 587 | 3.1% |
| straight -x-y (y wing) 2 | straight | yes | 278 | 1.4% | 277 | 1.4% |
| straight -x-y (x wing) 0 | straight | yes | 938 | 4.9% | 938 | 4.9% |
| straight -x-y (x wing) 1 | straight | yes | 598 | 3.1% | 585 | 3.0% |
| straight -x-y (x wing) 2 | straight | yes | 308 | 1.6% | 307 | 1.6% |
| corner -x-y | corner | yes | 799 | 4.2% | 334 | 1.7% |
| straight +x-y (y wing) 0 | straight | yes | 950 | 4.9% | 950 | 4.9% |
| straight +x-y (y wing) 1 | straight | yes | 599 | 3.1% | 589 | 3.1% |
| straight +x-y (y wing) 2 | straight | yes | 297 | 1.5% | 294 | 1.5% |
| straight +x-y (x wing) 0 | straight | yes | 939 | 4.9% | 939 | 4.9% |
| straight +x-y (x wing) 1 | straight | yes | 611 | 3.2% | 605 | 3.1% |
| straight +x-y (x wing) 2 | straight | yes | 278 | 1.4% | 273 | 1.4% |
| corner +x-y | corner | yes | 809 | 4.2% | 318 | 1.7% |
| **straight (24)** | | | 14724 | | 14626 | 76.1% |
| **corner (4)** | | | 3200 | | 1246 | 6.5% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 3351, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 928 | 29.0 | 442.2 | 0.28 | 0.74 | 0.0% |
| -x | 912 | 29.0 | 430.4 | 0.29 | 0.70 | 0.0% |
| +y | 929 | 29.0 | 440.1 | 0.29 | 0.71 | 0.0% |
| -y | 919 | 29.0 | 430.6 | 0.29 | 0.71 | 0.0% |
| door +x+y (y wall) 0 | 725 | 0.9 | 435.9 | 1.00 | 1.50 | 86.4% |
| door +x+y (y wall) 1 | 717 | 0.9 | 449.5 | 0.96 | 1.56 | 80.4% |
| door +x+y (y wall) 2 | 393 | 0.9 | 479.9 | 0.49 | 1.44 | 22.4% |
| door +x+y (x wall) 0 | 743 | 0.7 | 451.3 | 0.99 | 1.62 | 84.8% |
| door +x+y (x wall) 1 | 698 | 0.9 | 453.4 | 0.92 | 1.50 | 73.9% |
| door +x+y (x wall) 2 | 367 | 1.0 | 473.1 | 0.46 | 1.26 | 22.9% |
| door +x+y (corner) | 234 | 0.9 | 481.2 | 0.29 | 1.44 | 12.2% |
| door -x+y (y wall) 0 | 746 | 1.4 | 459.8 | 0.97 | 1.56 | 80.9% |
| door -x+y (y wall) 1 | 698 | 0.7 | 442.3 | 0.94 | 1.62 | 68.9% |
| door -x+y (y wall) 2 | 374 | 1.0 | 472.8 | 0.47 | 1.50 | 25.0% |
| door -x+y (x wall) 0 | 725 | 0.9 | 602.0 | 0.72 | 1.56 | 60.7% |
| door -x+y (x wall) 1 | 707 | 0.9 | 447.6 | 0.95 | 1.50 | 71.1% |
| door -x+y (x wall) 2 | 395 | 1.0 | 481.9 | 0.49 | 1.26 | 22.4% |
| door -x+y (corner) | 244 | 0.9 | 477.5 | 0.31 | 1.38 | 12.5% |
| door -x-y (y wall) 0 | 729 | 1.0 | 435.3 | 1.00 | 1.56 | 86.4% |
| door -x-y (y wall) 1 | 688 | 1.0 | 439.9 | 0.94 | 1.56 | 73.3% |
| door -x-y (y wall) 2 | 373 | 1.0 | 469.4 | 0.48 | 1.32 | 22.9% |
| door -x-y (x wall) 0 | 727 | 1.2 | 458.3 | 0.95 | 1.56 | 80.4% |
| door -x-y (x wall) 1 | 680 | 0.7 | 436.0 | 0.93 | 1.56 | 75.0% |
| door -x-y (x wall) 2 | 413 | 1.4 | 471.0 | 0.53 | 1.26 | 25.0% |
| door -x-y (corner) | 272 | 0.7 | 463.9 | 0.35 | 1.32 | 21.3% |
| door +x-y (y wall) 0 | 736 | 0.7 | 437.4 | 1.01 | 1.62 | 84.1% |
| door +x-y (y wall) 1 | 702 | 1.0 | 433.8 | 0.97 | 1.62 | 79.5% |
| door +x-y (y wall) 2 | 383 | 1.0 | 445.5 | 0.52 | 1.44 | 24.4% |
| door +x-y (x wall) 0 | 722 | 1.0 | 441.1 | 0.98 | 1.50 | 82.2% |
| door +x-y (x wall) 1 | 723 | 0.9 | 445.5 | 0.97 | 1.56 | 77.8% |
| door +x-y (x wall) 2 | 366 | 1.0 | 454.4 | 0.48 | 1.38 | 21.7% |
| door +x-y (corner) | 255 | 0.9 | 455.6 | 0.34 | 1.50 | 17.4% |

Mean flow / w J averaged over the doors 0.73, over the avenues 0.29.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 951 | 609 / 343 / 191 | 0.5 | 432.9 | 2.64 | 4.61 | 86% | 82% | 5% | 4.44 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 573 | 610 / 0 / 11 | 0.7 | 446.5 | 1.39 | 2.01 | 84% | 73% | 11% | 3.93 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 75 | 296 / 0 / 0 | 0.7 | 477.0 | 0.62 | 1.30 | 19% | 19% | 0% | 4.02 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 942 | 623 / 320 / 178 | 0.5 | 448.3 | 2.50 | 4.51 | 80% | 80% | 0% | 4.63 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 572 | 593 / 0 / 16 | 0.7 | 450.4 | 1.35 | 2.01 | 85% | 72% | 13% | 3.77 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 76 | 269 / 0 / 8 | 0.7 | 470.1 | 0.59 | 1.30 | 17% | 17% | 0% | 3.58 |
| corner +x+y | 1.20 | 85.6 | 780 | 183 / 125 / 507 | 0.7 | 477.3 | 1.71 | 3.81 | 81% | 56% | 25% | 2.53 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 948 | 631 / 319 / 183 | 0.3 | 456.9 | 2.48 | 4.41 | 78% | 78% | 0% | 4.69 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 567 | 600 / 0 / 9 | 0.7 | 439.4 | 1.39 | 1.91 | 84% | 71% | 13% | 3.95 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 75 | 287 / 0 / 5 | 0.7 | 469.8 | 0.62 | 1.91 | 17% | 17% | 0% | 3.74 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 949 | 605 / 344 / 201 | 0.2 | 599.1 | 1.92 | 4.41 | 92% | 57% | 34% | 3.00 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 578 | 609 / 0 / 13 | 0.7 | 444.6 | 1.40 | 2.01 | 82% | 71% | 11% | 4.13 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 74 | 289 / 0 / 0 | 0.7 | 478.9 | 0.60 | 1.30 | 18% | 18% | 0% | 3.95 |
| corner -x+y | 1.20 | 85.6 | 777 | 174 / 112 / 518 | 0.7 | 473.6 | 1.70 | 3.91 | 85% | 60% | 25% | 2.47 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 939 | 611 / 328 / 159 | 0.5 | 432.4 | 2.54 | 4.01 | 77% | 77% | 0% | 4.64 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 580 | 587 / 0 / 14 | 0.7 | 436.9 | 1.38 | 2.01 | 86% | 73% | 14% | 3.93 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 74 | 277 / 0 / 1 | 0.7 | 466.5 | 0.60 | 1.30 | 17% | 17% | 0% | 3.78 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 938 | 611 / 328 / 181 | 0.2 | 455.3 | 2.46 | 4.41 | 76% | 76% | 0% | 4.74 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 580 | 586 / 0 / 17 | 0.7 | 433.1 | 1.39 | 2.21 | 89% | 75% | 14% | 3.90 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 76 | 307 / 0 / 1 | 0.7 | 468.1 | 0.66 | 1.50 | 21% | 19% | 2% | 3.53 |
| corner -x-y | 1.20 | 85.6 | 780 | 223 / 111 / 478 | 0.7 | 461.9 | 1.76 | 4.41 | 83% | 45% | 38% | 2.33 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 950 | 619 / 331 / 194 | 0.3 | 434.5 | 2.63 | 4.81 | 89% | 82% | 7% | 4.30 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 562 | 589 / 0 / 19 | 0.7 | 430.8 | 1.41 | 2.51 | 82% | 70% | 11% | 4.04 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 77 | 294 / 0 / 4 | 0.7 | 442.5 | 0.67 | 1.60 | 18% | 18% | 0% | 3.75 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 939 | 613 / 327 / 176 | 0.3 | 438.1 | 2.55 | 4.71 | 91% | 80% | 11% | 4.14 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 567 | 607 / 0 / 7 | 0.5 | 442.5 | 1.39 | 2.01 | 82% | 71% | 11% | 3.95 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 76 | 273 / 0 / 6 | 0.7 | 451.4 | 0.62 | 1.30 | 17% | 17% | 0% | 3.58 |
| corner +x-y | 1.20 | 85.6 | 797 | 204 / 115 / 515 | 0.7 | 451.8 | 1.85 | 4.91 | 85% | 59% | 26% | 2.52 |

The last agent out (agent 6387, t100 602.0 s): last gangway straight -x+y (x wing) 0, exit door -x+y (x wall) 0. The gangway that cleared last: straight -x+y (x wing) 0 at 599.1 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 7.00 | 512.8 / 471.5 / 445.1 | 464.7 / 448.1 / 342.3 | 701974.6 | 1719181 | 0.224 |
| gangway | 1212 | 1112.9 | 7.00 | 510.7 / 466.5 / 379.4 | 464.7 / 448.1 / 342.3 | 665484.7 | 1374048 | 0.120 |
| walkway | 276 | 257.4 | 5.31 | 361.0 / 243.3 / 45.5 | 300.8 / 231.9 / 13.6 | 263.5 | 60823 | 0.403 |
| avenue | 912 | 858.9 | 2.52 | 399.3 / 18.9 / 0.0 | 336.2 / 2.4 / 0.0 | 0.0 | 105940 | 1.325 |
| exit | 32 | 3.2 | 0.00 | 463.2 / 460.4 / 436.0 | 327.4 / 299.8 / 184.7 | 1245.5 | 2181 | 1.170 |
| concourse | 1116 | 1043.8 | 6.04 | 445.8 / 177.7 / 91.8 | 319.6 / 142.0 / 60.2 | 34980.9 | 176188 | 0.300 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.59 | 560.8 / 557.6 / 378.8 | 411.4 / 404.0 / 375.7 | 726262.4 | 2004469 | 0.046 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 26.5 | 28.5 | gangway | 1.00 | 6.05 | 401.8 | 398.8 | 336.0 | 1968.2 | 0.022 |
| 2 | 29.5 | -26.5 | gangway | 1.00 | 6.12 | 408.9 | 375.2 | 329.2 | 1948.4 | 0.027 |
| 3 | 27.5 | 27.5 | gangway | 1.00 | 6.29 | 400.7 | 397.6 | 330.2 | 1929.2 | 0.019 |
| 4 | -28.5 | 26.5 | gangway | 1.00 | 6.06 | 409.8 | 403.0 | 336.5 | 1921.0 | 0.025 |
| 5 | 27.5 | 28.5 | gangway | 1.00 | 6.16 | 404.9 | 402.6 | 327.3 | 1899.4 | 0.024 |
| 6 | 29.5 | 26.5 | gangway | 1.00 | 5.93 | 397.2 | 387.8 | 334.8 | 1899.1 | 0.022 |
| 7 | -26.5 | 29.5 | gangway | 1.00 | 6.36 | 398.3 | 358.0 | 322.9 | 1883.1 | 0.028 |
| 8 | -26.5 | -29.5 | gangway | 1.00 | 6.38 | 392.7 | 382.3 | 311.7 | 1881.3 | 0.020 |
| 9 | 26.5 | 29.5 | gangway | 1.00 | 6.02 | 405.8 | 379.0 | 322.0 | 1877.7 | 0.030 |
| 10 | 26.5 | 27.5 | gangway | 1.00 | 6.03 | 397.9 | 394.4 | 328.1 | 1867.8 | 0.020 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 29.5 | -25.5 | seat row | 0.71 | 5.85 | 374.0 | 372.6 | 317.1 | 1266.0 | 0.025 |
| 2 | -30.5 | -25.5 | seat row | 0.64 | 6.51 | 372.7 | 351.9 | 321.1 | 1262.5 | 0.032 |
| 3 | -30.5 | 25.5 | seat row | 0.64 | 6.71 | 368.4 | 348.2 | 319.7 | 1252.3 | 0.033 |
| 4 | -9.5 | 22.5 | seat row | 0.50 | 7.53 | 361.9 | 359.4 | 348.6 | 1234.3 | 0.015 |
| 5 | 30.5 | -25.5 | seat row | 0.64 | 6.56 | 366.8 | 353.7 | 314.8 | 1231.2 | 0.034 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1470; agent-steps of seated agents on another row's clearway: 30094.

## Deposit check

Person-seconds deposited: 3729707.1, of them in excluded cells: 6056.676.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 404177 overlapping pair-steps: p99 0.0036, max 0.0282 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0036 max 0.0282; venue-geometry 4: p99 0.0004 max 0.0004 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 19 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.38 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 640 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
