# Experiment `M_load150_s1`

**Task 5.10 stage 4 (AMD 26.10.1): Task 5.8's model (the level spacing on the gangway inclines, --stair-flow off): venue M, 150% requested (seed 1)**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 19223 agents (load 121.4%, requested 150%): every one of the 15832 seats and 3391 standing (spawnOvercrowdedCrowd, seed 1; below), buffer N = 32768, 2777 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 1242917 evaluations, 54043 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.21)** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T20:31:21, 132.4 s wall.

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
| t50 | 1046 | 183.0 |
| t90 | 2120 | 370.8 |
| t100 | 2777 | 485.7 |

t_p: the step by which ceil(p x 19223) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 932 | 93 | 29.0 | 433.8 | 24.4 | 62.7 | 28.7-38.7 |
| -x | 5.66 | 927 | 89 | 29.0 | 426.9 | 24.7 | 59.5 | 28.7-38.7 |
| +y | 5.66 | 913 | 83 | 29.2 | 428.9 | 24.2 | 61.7 | 28.9-38.8 |
| -y | 5.66 | 921 | 82 | 29.0 | 431.1 | 24.3 | 59.5 | 28.5-38.5 |
| door +x+y (y wall) 0 | 1.20 | 728 | 1267 | 0.7 | 450.4 | 80.9 | 130.4 | 112.3-122.3 |
| door +x+y (y wall) 1 | 1.20 | 699 | 799 | 1.0 | 438.0 | 80.0 | 105.3 | 41.6-51.6 |
| door +x+y (y wall) 2 | 1.20 | 410 | 270 | 1.0 | 475.7 | 43.2 | 120.4 | 91.1-101.1 |
| door +x+y (x wall) 0 | 1.20 | 731 | 1267 | 1.0 | 448.1 | 81.7 | 135.4 | 118.1-128.0 |
| door +x+y (x wall) 1 | 1.20 | 688 | 806 | 1.2 | 460.2 | 74.9 | 105.3 | 46.2-56.1 |
| door +x+y (x wall) 2 | 1.20 | 369 | 271 | 0.9 | 468.2 | 39.5 | 125.4 | 87.5-97.4 |
| door +x+y (corner) | 1.20 | 263 | 47 | 0.7 | 462.3 | 28.5 | 130.4 | 63.0-72.9 |
| door -x+y (y wall) 0 | 1.20 | 734 | 1270 | 0.9 | 444.1 | 82.8 | 130.4 | 116.1-126.1 |
| door -x+y (y wall) 1 | 1.20 | 709 | 797 | 0.9 | 444.1 | 80.0 | 135.4 | 124.9-134.9 |
| door -x+y (y wall) 2 | 1.20 | 387 | 265 | 1.2 | 481.0 | 40.3 | 110.3 | 57.7-67.7 |
| door -x+y (x wall) 0 | 1.20 | 730 | 1275 | 0.9 | 435.7 | 83.9 | 140.4 | 120.5-130.5 |
| door -x+y (x wall) 1 | 1.20 | 709 | 787 | 1.2 | 442.9 | 80.2 | 130.4 | 114.9-124.9 |
| door -x+y (x wall) 2 | 1.20 | 386 | 276 | 0.9 | 479.9 | 40.3 | 110.3 | 80.8-90.8 |
| door -x+y (corner) | 1.20 | 235 | 50 | 0.7 | 478.9 | 24.6 | 110.3 | 10.5-20.5 |
| door -x-y (y wall) 0 | 1.20 | 740 | 1275 | 1.0 | 457.9 | 81.0 | 135.4 | 125.9-135.9 |
| door -x-y (y wall) 1 | 1.20 | 693 | 794 | 0.9 | 485.7 | 71.4 | 140.4 | 123.1-133.1 |
| door -x-y (y wall) 2 | 1.20 | 391 | 277 | 0.9 | 476.6 | 41.1 | 105.3 | 43.2-53.2 |
| door -x-y (x wall) 0 | 1.20 | 724 | 1269 | 0.9 | 436.0 | 83.2 | 130.4 | 132.6-142.5 |
| door -x-y (x wall) 1 | 1.20 | 694 | 792 | 1.6 | 472.6 | 73.6 | 120.4 | 109.5-119.5 |
| door -x-y (x wall) 2 | 1.20 | 354 | 269 | 0.9 | 470.1 | 37.7 | 120.4 | 89.2-99.2 |
| door -x-y (corner) | 1.20 | 289 | 48 | 0.9 | 476.4 | 30.4 | 130.4 | 85.5-95.5 |
| door +x-y (y wall) 0 | 1.20 | 725 | 1272 | 0.9 | 440.1 | 82.5 | 125.4 | 125.6-135.6 |
| door +x-y (y wall) 1 | 1.20 | 679 | 792 | 1.0 | 467.5 | 72.8 | 120.4 | 116.0-125.9 |
| door +x-y (y wall) 2 | 1.20 | 410 | 267 | 0.9 | 481.3 | 42.7 | 110.3 | 93.7-103.7 |
| door +x-y (x wall) 0 | 1.20 | 729 | 1270 | 1.0 | 442.7 | 82.5 | 130.4 | 126.3-136.3 |
| door +x-y (x wall) 1 | 1.20 | 706 | 797 | 1.0 | 453.0 | 78.1 | 125.4 | 114.9-124.9 |
| door +x-y (x wall) 2 | 1.20 | 376 | 261 | 1.2 | 475.6 | 39.6 | 115.3 | 86.2-96.2 |
| door +x-y (corner) | 1.20 | 242 | 46 | 0.9 | 465.8 | 26.0 | 130.4 | 89.4-99.3 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 932 | 4.8% | 24.3% |
| -x | avenue | 5.66 | 927 | 4.8% | 24.2% |
| +y | avenue | 5.66 | 913 | 4.7% | 23.8% |
| -y | avenue | 5.66 | 921 | 4.8% | 24.0% |
| door +x+y (y wall) 0 | door | 1.20 | 728 | 3.8% | 89.6% |
| door +x+y (y wall) 1 | door | 1.20 | 699 | 3.6% | 86.1% |
| door +x+y (y wall) 2 | door | 1.20 | 410 | 2.1% | 50.5% |
| door +x+y (x wall) 0 | door | 1.20 | 731 | 3.8% | 90.0% |
| door +x+y (x wall) 1 | door | 1.20 | 688 | 3.6% | 84.7% |
| door +x+y (x wall) 2 | door | 1.20 | 369 | 1.9% | 45.4% |
| door +x+y (corner) | door | 1.20 | 263 | 1.4% | 32.4% |
| door -x+y (y wall) 0 | door | 1.20 | 734 | 3.8% | 90.4% |
| door -x+y (y wall) 1 | door | 1.20 | 709 | 3.7% | 87.3% |
| door -x+y (y wall) 2 | door | 1.20 | 387 | 2.0% | 47.7% |
| door -x+y (x wall) 0 | door | 1.20 | 730 | 3.8% | 89.9% |
| door -x+y (x wall) 1 | door | 1.20 | 709 | 3.7% | 87.3% |
| door -x+y (x wall) 2 | door | 1.20 | 386 | 2.0% | 47.5% |
| door -x+y (corner) | door | 1.20 | 235 | 1.2% | 28.9% |
| door -x-y (y wall) 0 | door | 1.20 | 740 | 3.8% | 91.1% |
| door -x-y (y wall) 1 | door | 1.20 | 693 | 3.6% | 85.3% |
| door -x-y (y wall) 2 | door | 1.20 | 391 | 2.0% | 48.1% |
| door -x-y (x wall) 0 | door | 1.20 | 724 | 3.8% | 89.1% |
| door -x-y (x wall) 1 | door | 1.20 | 694 | 3.6% | 85.5% |
| door -x-y (x wall) 2 | door | 1.20 | 354 | 1.8% | 43.6% |
| door -x-y (corner) | door | 1.20 | 289 | 1.5% | 35.6% |
| door +x-y (y wall) 0 | door | 1.20 | 725 | 3.8% | 89.3% |
| door +x-y (y wall) 1 | door | 1.20 | 679 | 3.5% | 83.6% |
| door +x-y (y wall) 2 | door | 1.20 | 410 | 2.1% | 50.5% |
| door +x-y (x wall) 0 | door | 1.20 | 729 | 3.8% | 89.8% |
| door +x-y (x wall) 1 | door | 1.20 | 706 | 3.7% | 86.9% |
| door +x-y (x wall) 2 | door | 1.20 | 376 | 2.0% | 46.3% |
| door +x-y (corner) | door | 1.20 | 242 | 1.3% | 29.8% |
| **doors (28)** | door | 33.60 | 15530 | 80.8% | |
| **avenues (4)** | avenue | 22.64 | 3693 | 19.2% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 485.7 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 50.5%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 954 | 5.0% | 954 | 5.0% |
| straight +x+y (y wing) 1 | straight | yes | 606 | 3.2% | 597 | 3.1% |
| straight +x+y (y wing) 2 | straight | yes | 317 | 1.6% | 313 | 1.6% |
| straight +x+y (x wing) 0 | straight | yes | 941 | 4.9% | 941 | 4.9% |
| straight +x+y (x wing) 1 | straight | yes | 591 | 3.1% | 583 | 3.0% |
| straight +x+y (x wing) 2 | straight | yes | 261 | 1.4% | 260 | 1.4% |
| corner +x+y | corner | yes | 803 | 4.2% | 320 | 1.7% |
| straight -x+y (y wing) 0 | straight | yes | 953 | 5.0% | 953 | 5.0% |
| straight -x+y (y wing) 1 | straight | yes | 613 | 3.2% | 605 | 3.1% |
| straight -x+y (y wing) 2 | straight | yes | 311 | 1.6% | 310 | 1.6% |
| straight -x+y (x wing) 0 | straight | yes | 938 | 4.9% | 938 | 4.9% |
| straight -x+y (x wing) 1 | straight | yes | 619 | 3.2% | 614 | 3.2% |
| straight -x+y (x wing) 2 | straight | yes | 277 | 1.4% | 276 | 1.4% |
| corner -x+y | corner | yes | 778 | 4.0% | 273 | 1.4% |
| straight -x-y (y wing) 0 | straight | yes | 944 | 4.9% | 944 | 4.9% |
| straight -x-y (y wing) 1 | straight | yes | 602 | 3.1% | 592 | 3.1% |
| straight -x-y (y wing) 2 | straight | yes | 288 | 1.5% | 285 | 1.5% |
| straight -x-y (x wing) 0 | straight | yes | 948 | 4.9% | 948 | 4.9% |
| straight -x-y (x wing) 1 | straight | yes | 601 | 3.1% | 592 | 3.1% |
| straight -x-y (x wing) 2 | straight | yes | 268 | 1.4% | 264 | 1.4% |
| corner -x-y | corner | yes | 797 | 4.1% | 343 | 1.8% |
| straight +x-y (y wing) 0 | straight | yes | 944 | 4.9% | 944 | 4.9% |
| straight +x-y (y wing) 1 | straight | yes | 609 | 3.2% | 598 | 3.1% |
| straight +x-y (y wing) 2 | straight | yes | 303 | 1.6% | 299 | 1.6% |
| straight +x-y (x wing) 0 | straight | yes | 933 | 4.9% | 933 | 4.9% |
| straight +x-y (x wing) 1 | straight | yes | 605 | 3.1% | 596 | 3.1% |
| straight +x-y (x wing) 2 | straight | yes | 291 | 1.5% | 287 | 1.5% |
| corner +x-y | corner | yes | 809 | 4.2% | 312 | 1.6% |
| **straight (24)** | | | 14717 | | 14626 | 76.1% |
| **corner (4)** | | | 3187 | | 1248 | 6.5% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 3349, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 932 | 29.0 | 433.8 | 0.29 | 0.75 | 0.0% |
| -x | 927 | 29.0 | 426.9 | 0.30 | 0.71 | 0.0% |
| +y | 913 | 29.2 | 428.9 | 0.29 | 0.74 | 0.0% |
| -y | 921 | 29.0 | 431.1 | 0.29 | 0.71 | 0.0% |
| door +x+y (y wall) 0 | 728 | 0.7 | 450.4 | 0.97 | 1.56 | 82.6% |
| door +x+y (y wall) 1 | 699 | 1.0 | 438.0 | 0.96 | 1.26 | 75.0% |
| door +x+y (y wall) 2 | 410 | 1.0 | 475.7 | 0.52 | 1.44 | 20.8% |
| door +x+y (x wall) 0 | 731 | 1.0 | 448.1 | 0.98 | 1.62 | 84.4% |
| door +x+y (x wall) 1 | 688 | 1.2 | 460.2 | 0.90 | 1.26 | 70.2% |
| door +x+y (x wall) 2 | 369 | 0.9 | 468.2 | 0.47 | 1.50 | 21.3% |
| door +x+y (corner) | 263 | 0.7 | 462.3 | 0.34 | 1.56 | 17.0% |
| door -x+y (y wall) 0 | 734 | 0.9 | 444.1 | 0.99 | 1.56 | 82.2% |
| door -x+y (y wall) 1 | 709 | 0.9 | 444.1 | 0.96 | 1.62 | 75.6% |
| door -x+y (y wall) 2 | 387 | 1.2 | 481.0 | 0.48 | 1.32 | 22.4% |
| door -x+y (x wall) 0 | 730 | 0.9 | 435.7 | 1.00 | 1.68 | 86.4% |
| door -x+y (x wall) 1 | 709 | 1.2 | 442.9 | 0.96 | 1.56 | 73.3% |
| door -x+y (x wall) 2 | 386 | 0.9 | 479.9 | 0.48 | 1.32 | 22.4% |
| door -x+y (corner) | 235 | 0.7 | 478.9 | 0.29 | 1.32 | 12.2% |
| door -x-y (y wall) 0 | 740 | 1.0 | 457.9 | 0.97 | 1.62 | 80.4% |
| door -x-y (y wall) 1 | 693 | 0.9 | 485.7 | 0.85 | 1.68 | 65.3% |
| door -x-y (y wall) 2 | 391 | 0.9 | 476.6 | 0.49 | 1.26 | 20.8% |
| door -x-y (x wall) 0 | 724 | 0.9 | 436.0 | 0.99 | 1.56 | 84.1% |
| door -x-y (x wall) 1 | 694 | 1.6 | 472.6 | 0.88 | 1.44 | 66.7% |
| door -x-y (x wall) 2 | 354 | 0.9 | 470.1 | 0.45 | 1.44 | 25.0% |
| door -x-y (corner) | 289 | 0.9 | 476.4 | 0.36 | 1.56 | 18.8% |
| door +x-y (y wall) 0 | 725 | 0.9 | 440.1 | 0.99 | 1.50 | 84.4% |
| door +x-y (y wall) 1 | 679 | 1.0 | 467.5 | 0.87 | 1.44 | 63.8% |
| door +x-y (y wall) 2 | 410 | 0.9 | 481.3 | 0.51 | 1.32 | 22.4% |
| door +x-y (x wall) 0 | 729 | 1.0 | 442.7 | 0.99 | 1.56 | 82.2% |
| door +x-y (x wall) 1 | 706 | 1.0 | 453.0 | 0.93 | 1.50 | 73.9% |
| door +x-y (x wall) 2 | 376 | 1.2 | 475.6 | 0.47 | 1.38 | 20.8% |
| door +x-y (corner) | 242 | 0.9 | 465.8 | 0.31 | 1.56 | 17.0% |

Mean flow / w J averaged over the doors 0.73, over the avenues 0.29.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 954 | 613 / 341 / 187 | 0.3 | 447.4 | 2.55 | 4.51 | 78% | 78% | 0% | 4.56 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 558 | 597 / 0 / 12 | 0.7 | 435.0 | 1.40 | 2.11 | 84% | 73% | 11% | 4.01 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 79 | 313 / 0 / 5 | 0.7 | 472.8 | 0.67 | 1.81 | 17% | 17% | 0% | 3.73 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 941 | 620 / 321 / 182 | 0.2 | 445.1 | 2.52 | 4.71 | 84% | 80% | 4% | 4.49 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 563 | 583 / 0 / 10 | 0.7 | 457.2 | 1.30 | 2.21 | 83% | 72% | 11% | 4.09 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 80 | 260 / 0 / 3 | 0.7 | 465.3 | 0.57 | 1.91 | 21% | 21% | 0% | 3.78 |
| corner +x+y | 1.20 | 85.6 | 793 | 199 / 121 / 503 | 0.7 | 466.8 | 1.76 | 4.11 | 83% | 57% | 26% | 2.55 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 953 | 622 / 331 / 215 | 0.2 | 441.1 | 2.65 | 4.81 | 87% | 80% | 7% | 4.26 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 570 | 605 / 0 / 9 | 0.7 | 441.1 | 1.39 | 2.11 | 80% | 71% | 9% | 4.11 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 78 | 310 / 0 / 1 | 0.7 | 478.0 | 0.65 | 1.71 | 19% | 19% | 0% | 3.61 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 938 | 611 / 327 / 165 | 0.5 | 432.7 | 2.55 | 4.71 | 86% | 80% | 7% | 4.40 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 588 | 614 / 0 / 9 | 0.7 | 439.9 | 1.42 | 2.01 | 84% | 73% | 11% | 3.95 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 73 | 276 / 0 / 1 | 0.7 | 477.0 | 0.58 | 1.40 | 19% | 19% | 0% | 3.73 |
| corner -x+y | 1.20 | 85.6 | 769 | 163 / 110 / 516 | 0.2 | 475.2 | 1.66 | 3.91 | 83% | 58% | 25% | 2.46 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 944 | 623 / 321 / 166 | 0.3 | 454.9 | 2.44 | 4.61 | 76% | 76% | 0% | 4.56 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 574 | 592 / 0 / 15 | 0.7 | 482.7 | 1.26 | 2.01 | 78% | 67% | 10% | 3.88 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 74 | 285 / 0 / 4 | 0.7 | 473.6 | 0.61 | 1.50 | 17% | 17% | 0% | 3.99 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 948 | 608 / 340 / 169 | 0.3 | 433.1 | 2.58 | 4.01 | 84% | 80% | 5% | 4.46 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 570 | 592 / 0 / 9 | 0.7 | 469.6 | 1.28 | 1.91 | 79% | 67% | 12% | 3.88 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 75 | 264 / 0 / 5 | 0.7 | 467.2 | 0.58 | 1.91 | 19% | 19% | 0% | 3.55 |
| corner -x-y | 1.20 | 85.6 | 783 | 224 / 119 / 473 | 0.7 | 472.6 | 1.73 | 3.71 | 81% | 54% | 27% | 2.50 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 944 | 608 / 336 / 204 | 0.5 | 437.1 | 2.63 | 5.02 | 89% | 80% | 9% | 4.26 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 576 | 600 / 0 / 15 | 0.7 | 464.6 | 1.33 | 2.01 | 79% | 70% | 9% | 4.06 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 74 | 299 / 0 / 8 | 0.7 | 478.4 | 0.64 | 1.71 | 17% | 17% | 0% | 3.79 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 933 | 611 / 323 / 190 | 0.3 | 439.7 | 2.56 | 4.61 | 82% | 80% | 2% | 4.53 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 574 | 596 / 0 / 19 | 0.7 | 450.0 | 1.37 | 2.21 | 80% | 72% | 9% | 4.05 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 75 | 287 / 0 / 4 | 0.7 | 472.6 | 0.62 | 1.50 | 19% | 19% | 0% | 3.61 |
| corner +x-y | 1.20 | 85.6 | 793 | 186 / 126 / 527 | 0.7 | 472.2 | 1.78 | 4.21 | 81% | 54% | 27% | 2.50 |

The last agent out (agent 10342, t100 485.7 s): last gangway straight -x-y (y wing) 1, exit door -x-y (y wall) 1. The gangway that cleared last: straight -x-y (y wing) 1 at 482.7 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.79 | 479.1 / 474.9 / 446.9 | 463.9 / 449.7 / 335.5 | 706320.1 | 1715499 | 0.225 |
| gangway | 1212 | 1112.9 | 6.79 | 476.8 / 468.9 / 389.2 | 463.9 / 449.7 / 335.5 | 669865.0 | 1372470 | 0.120 |
| walkway | 276 | 257.4 | 5.32 | 338.3 / 208.8 / 23.8 | 271.8 / 197.3 / 11.2 | 150.2 | 57362 | 0.426 |
| avenue | 912 | 858.9 | 2.69 | 393.7 / 28.0 / 0.0 | 300.5 / 1.6 / 0.0 | 0.0 | 106067 | 1.325 |
| exit | 32 | 3.2 | 0.00 | 465.4 / 463.2 / 438.5 | 328.3 / 302.4 / 180.7 | 1241.9 | 2183 | 1.169 |
| concourse | 1116 | 1043.8 | 5.98 | 448.1 / 174.4 / 93.7 | 310.3 / 133.8 / 65.8 | 35063.0 | 177417 | 0.301 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.58 | 409.8 / 392.7 / 368.9 | 405.3 / 392.1 / 365.6 | 725832.7 | 2000978 | 0.046 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 29.5 | -26.5 | gangway | 1.00 | 6.21 | 405.3 | 370.1 | 332.3 | 1936.5 | 0.025 |
| 2 | 29.5 | 26.5 | gangway | 1.00 | 6.15 | 397.0 | 389.2 | 330.4 | 1935.0 | 0.022 |
| 3 | -26.5 | 28.5 | gangway | 1.00 | 6.20 | 390.6 | 387.8 | 328.8 | 1898.9 | 0.025 |
| 4 | -28.5 | -26.5 | gangway | 1.00 | 6.19 | 393.7 | 388.6 | 319.6 | 1882.4 | 0.021 |
| 5 | 26.5 | -29.5 | gangway | 1.00 | 5.93 | 389.0 | 368.7 | 335.5 | 1874.9 | 0.024 |
| 6 | -26.5 | -29.5 | gangway | 1.00 | 6.06 | 401.4 | 382.0 | 326.9 | 1864.9 | 0.024 |
| 7 | -29.5 | -26.5 | gangway | 1.00 | 6.03 | 389.3 | 379.2 | 318.2 | 1861.1 | 0.024 |
| 8 | -27.5 | 28.5 | gangway | 1.00 | 6.00 | 400.5 | 393.9 | 326.4 | 1854.8 | 0.027 |
| 9 | 28.5 | -26.5 | gangway | 1.00 | 6.04 | 406.1 | 403.2 | 317.6 | 1840.7 | 0.025 |
| 10 | 26.5 | 29.5 | gangway | 1.00 | 6.08 | 398.6 | 362.8 | 317.5 | 1829.4 | 0.029 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 30.5 | 25.5 | seat row | 0.64 | 6.49 | 376.9 | 369.6 | 324.6 | 1298.7 | 0.030 |
| 2 | 30.5 | -25.5 | seat row | 0.64 | 6.53 | 374.5 | 367.7 | 331.3 | 1287.9 | 0.032 |
| 3 | -30.5 | 25.5 | seat row | 0.64 | 6.53 | 376.0 | 368.2 | 326.4 | 1281.2 | 0.031 |
| 4 | -29.5 | 25.5 | seat row | 0.71 | 5.63 | 386.4 | 378.7 | 332.7 | 1278.7 | 0.025 |
| 5 | 29.5 | -25.5 | seat row | 0.71 | 5.67 | 387.8 | 375.9 | 326.2 | 1275.5 | 0.025 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1478; agent-steps of seated agents on another row's clearway: 22728.

## Deposit check

Person-seconds deposited: 3722546.3, of them in excluded cells: 6069.183.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 386783 overlapping pair-steps: p99 0.0038, max 0.0173 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0038 max 0.0173; venue-geometry 2: p99 0.0001 max 0.0001 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 18 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.22 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 566 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
