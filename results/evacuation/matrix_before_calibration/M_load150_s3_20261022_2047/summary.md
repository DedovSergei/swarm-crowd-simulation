# Experiment `M_load150_s3`

**Task 5.10 stage 4 (AMD 26.10.1): Task 5.8's model (the level spacing on the gangway inclines, --stair-flow off): venue M, 150% requested (seed 3)**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 19223 agents (load 121.4%, requested 150%): every one of the 15832 seats and 3391 standing (spawnOvercrowdedCrowd, seed 3; below), buffer N = 32768, 2766 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 1255938 evaluations, 53985 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.21)** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T20:47:49, 141.0 s wall.

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
| t50 | 1066 | 186.5 |
| t90 | 2130 | 372.6 |
| t100 | 2766 | 483.8 |

t_p: the step by which ceil(p x 19223) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 923 | 86 | 29.0 | 428.7 | 24.5 | 65.9 | 28.3-38.3 |
| -x | 5.66 | 925 | 81 | 29.0 | 442.3 | 23.7 | 56.4 | 28.7-38.7 |
| +y | 5.66 | 926 | 80 | 29.0 | 440.2 | 23.9 | 56.4 | 28.5-38.5 |
| -y | 5.66 | 920 | 90 | 29.0 | 431.0 | 24.3 | 61.7 | 28.5-38.5 |
| door +x+y (y wall) 0 | 1.20 | 755 | 1280 | 0.9 | 462.8 | 81.7 | 125.4 | 115.6-125.6 |
| door +x+y (y wall) 1 | 1.20 | 731 | 801 | 0.9 | 444.1 | 82.4 | 125.4 | 119.1-129.1 |
| door +x+y (y wall) 2 | 1.20 | 367 | 269 | 1.4 | 466.3 | 39.5 | 105.3 | 3.1-13.1 |
| door +x+y (x wall) 0 | 1.20 | 732 | 1274 | 0.9 | 439.7 | 83.4 | 120.4 | 108.3-118.2 |
| door +x+y (x wall) 1 | 1.20 | 723 | 790 | 0.7 | 448.5 | 80.7 | 125.4 | 123.1-133.1 |
| door +x+y (x wall) 2 | 1.20 | 348 | 269 | 1.0 | 467.2 | 37.3 | 110.3 | 93.6-103.5 |
| door +x+y (corner) | 1.20 | 231 | 45 | 0.9 | 459.8 | 25.2 | 115.3 | 3.8-13.8 |
| door -x+y (y wall) 0 | 1.20 | 736 | 1269 | 1.0 | 457.0 | 80.7 | 130.4 | 119.3-129.3 |
| door -x+y (y wall) 1 | 1.20 | 727 | 797 | 1.0 | 456.9 | 79.7 | 130.4 | 127.0-137.0 |
| door -x+y (y wall) 2 | 1.20 | 384 | 265 | 0.7 | 481.0 | 40.0 | 110.3 | 82.6-92.5 |
| door -x+y (x wall) 0 | 1.20 | 740 | 1274 | 0.9 | 459.3 | 80.7 | 135.4 | 125.1-135.0 |
| door -x+y (x wall) 1 | 1.20 | 718 | 805 | 0.9 | 458.1 | 78.5 | 135.4 | 128.2-138.2 |
| door -x+y (x wall) 2 | 1.20 | 338 | 266 | 0.9 | 476.4 | 35.5 | 100.3 | 6.3-16.3 |
| door -x+y (corner) | 1.20 | 228 | 41 | 1.0 | 483.8 | 23.6 | 125.4 | 76.6-86.6 |
| door -x-y (y wall) 0 | 1.20 | 735 | 1270 | 1.0 | 450.2 | 81.8 | 130.4 | 111.4-121.4 |
| door -x-y (y wall) 1 | 1.20 | 669 | 800 | 0.9 | 454.2 | 73.8 | 125.4 | 115.6-125.6 |
| door -x-y (y wall) 2 | 1.20 | 410 | 271 | 1.0 | 475.4 | 43.2 | 135.4 | 91.7-101.6 |
| door -x-y (x wall) 0 | 1.20 | 728 | 1281 | 0.9 | 443.0 | 82.3 | 125.4 | 121.4-131.4 |
| door -x-y (x wall) 1 | 1.20 | 705 | 791 | 1.0 | 448.6 | 78.7 | 115.3 | 123.7-133.6 |
| door -x-y (x wall) 2 | 1.20 | 384 | 269 | 1.0 | 477.1 | 40.3 | 115.3 | 89.7-99.7 |
| door -x-y (corner) | 1.20 | 259 | 39 | 0.9 | 455.3 | 28.5 | 130.4 | 75.4-85.4 |
| door +x-y (y wall) 0 | 1.20 | 722 | 1269 | 1.0 | 440.2 | 82.2 | 130.4 | 131.0-141.0 |
| door +x-y (y wall) 1 | 1.20 | 682 | 799 | 0.9 | 432.5 | 79.0 | 130.4 | 147.1-157.1 |
| door +x-y (y wall) 2 | 1.20 | 390 | 266 | 0.9 | 465.6 | 41.9 | 115.3 | 92.9-102.8 |
| door +x-y (x wall) 0 | 1.20 | 732 | 1272 | 0.9 | 436.4 | 84.0 | 130.4 | 119.5-129.4 |
| door +x-y (x wall) 1 | 1.20 | 695 | 797 | 1.0 | 445.7 | 78.1 | 135.4 | 120.2-130.1 |
| door +x-y (x wall) 2 | 1.20 | 382 | 270 | 0.9 | 466.7 | 41.0 | 105.3 | 31.0-40.9 |
| door +x-y (corner) | 1.20 | 278 | 47 | 0.9 | 470.3 | 29.6 | 120.4 | 88.3-98.3 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 923 | 4.8% | 24.2% |
| -x | avenue | 5.66 | 925 | 4.8% | 24.2% |
| +y | avenue | 5.66 | 926 | 4.8% | 24.3% |
| -y | avenue | 5.66 | 920 | 4.8% | 24.1% |
| door +x+y (y wall) 0 | door | 1.20 | 755 | 3.9% | 93.3% |
| door +x+y (y wall) 1 | door | 1.20 | 731 | 3.8% | 90.4% |
| door +x+y (y wall) 2 | door | 1.20 | 367 | 1.9% | 45.4% |
| door +x+y (x wall) 0 | door | 1.20 | 732 | 3.8% | 90.5% |
| door +x+y (x wall) 1 | door | 1.20 | 723 | 3.8% | 89.4% |
| door +x+y (x wall) 2 | door | 1.20 | 348 | 1.8% | 43.0% |
| door +x+y (corner) | door | 1.20 | 231 | 1.2% | 28.6% |
| door -x+y (y wall) 0 | door | 1.20 | 736 | 3.8% | 91.0% |
| door -x+y (y wall) 1 | door | 1.20 | 727 | 3.8% | 89.9% |
| door -x+y (y wall) 2 | door | 1.20 | 384 | 2.0% | 47.5% |
| door -x+y (x wall) 0 | door | 1.20 | 740 | 3.8% | 91.5% |
| door -x+y (x wall) 1 | door | 1.20 | 718 | 3.7% | 88.8% |
| door -x+y (x wall) 2 | door | 1.20 | 338 | 1.8% | 41.8% |
| door -x+y (corner) | door | 1.20 | 228 | 1.2% | 28.2% |
| door -x-y (y wall) 0 | door | 1.20 | 735 | 3.8% | 90.9% |
| door -x-y (y wall) 1 | door | 1.20 | 669 | 3.5% | 82.7% |
| door -x-y (y wall) 2 | door | 1.20 | 410 | 2.1% | 50.7% |
| door -x-y (x wall) 0 | door | 1.20 | 728 | 3.8% | 90.0% |
| door -x-y (x wall) 1 | door | 1.20 | 705 | 3.7% | 87.2% |
| door -x-y (x wall) 2 | door | 1.20 | 384 | 2.0% | 47.5% |
| door -x-y (corner) | door | 1.20 | 259 | 1.3% | 32.0% |
| door +x-y (y wall) 0 | door | 1.20 | 722 | 3.8% | 89.3% |
| door +x-y (y wall) 1 | door | 1.20 | 682 | 3.5% | 84.3% |
| door +x-y (y wall) 2 | door | 1.20 | 390 | 2.0% | 48.2% |
| door +x-y (x wall) 0 | door | 1.20 | 732 | 3.8% | 90.5% |
| door +x-y (x wall) 1 | door | 1.20 | 695 | 3.6% | 85.9% |
| door +x-y (x wall) 2 | door | 1.20 | 382 | 2.0% | 47.2% |
| door +x-y (corner) | door | 1.20 | 278 | 1.4% | 34.4% |
| **doors (28)** | door | 33.60 | 15529 | 80.8% | |
| **avenues (4)** | avenue | 22.64 | 3694 | 19.2% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 483.8 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 50.7%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 943 | 4.9% | 943 | 4.9% |
| straight +x+y (y wing) 1 | straight | yes | 617 | 3.2% | 612 | 3.2% |
| straight +x+y (y wing) 2 | straight | yes | 288 | 1.5% | 284 | 1.5% |
| straight +x+y (x wing) 0 | straight | yes | 961 | 5.0% | 961 | 5.0% |
| straight +x+y (x wing) 1 | straight | yes | 619 | 3.2% | 613 | 3.2% |
| straight +x+y (x wing) 2 | straight | yes | 257 | 1.3% | 257 | 1.3% |
| corner +x+y | corner | yes | 780 | 4.1% | 297 | 1.5% |
| straight -x+y (y wing) 0 | straight | yes | 961 | 5.0% | 961 | 5.0% |
| straight -x+y (y wing) 1 | straight | yes | 614 | 3.2% | 610 | 3.2% |
| straight -x+y (y wing) 2 | straight | yes | 313 | 1.6% | 309 | 1.6% |
| straight -x+y (x wing) 0 | straight | yes | 942 | 4.9% | 942 | 4.9% |
| straight -x+y (x wing) 1 | straight | yes | 599 | 3.1% | 593 | 3.1% |
| straight -x+y (x wing) 2 | straight | yes | 262 | 1.4% | 258 | 1.3% |
| corner -x+y | corner | yes | 796 | 4.1% | 294 | 1.5% |
| straight -x-y (y wing) 0 | straight | yes | 941 | 4.9% | 941 | 4.9% |
| straight -x-y (y wing) 1 | straight | yes | 597 | 3.1% | 588 | 3.1% |
| straight -x-y (y wing) 2 | straight | yes | 293 | 1.5% | 288 | 1.5% |
| straight -x-y (x wing) 0 | straight | yes | 934 | 4.9% | 934 | 4.9% |
| straight -x-y (x wing) 1 | straight | yes | 617 | 3.2% | 606 | 3.2% |
| straight -x-y (x wing) 2 | straight | yes | 292 | 1.5% | 292 | 1.5% |
| corner -x-y | corner | yes | 817 | 4.3% | 319 | 1.7% |
| straight +x-y (y wing) 0 | straight | yes | 940 | 4.9% | 940 | 4.9% |
| straight +x-y (y wing) 1 | straight | yes | 584 | 3.0% | 573 | 3.0% |
| straight +x-y (y wing) 2 | straight | yes | 294 | 1.5% | 292 | 1.5% |
| straight +x-y (x wing) 0 | straight | yes | 938 | 4.9% | 938 | 4.9% |
| straight +x-y (x wing) 1 | straight | yes | 596 | 3.1% | 588 | 3.1% |
| straight +x-y (x wing) 2 | straight | yes | 297 | 1.5% | 294 | 1.5% |
| corner +x-y | corner | yes | 809 | 4.2% | 343 | 1.8% |
| **straight (24)** | | | 14699 | | 14617 | 76.0% |
| **corner (4)** | | | 3202 | | 1253 | 6.5% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 3353, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 923 | 29.0 | 428.7 | 0.29 | 0.79 | 0.0% |
| -x | 925 | 29.0 | 442.3 | 0.28 | 0.67 | 0.0% |
| +y | 926 | 29.0 | 440.2 | 0.29 | 0.67 | 0.0% |
| -y | 920 | 29.0 | 431.0 | 0.29 | 0.74 | 0.0% |
| door +x+y (y wall) 0 | 755 | 0.9 | 462.8 | 0.98 | 1.50 | 80.9% |
| door +x+y (y wall) 1 | 731 | 0.9 | 444.1 | 0.99 | 1.50 | 80.0% |
| door +x+y (y wall) 2 | 367 | 1.4 | 466.3 | 0.47 | 1.26 | 21.3% |
| door +x+y (x wall) 0 | 732 | 0.9 | 439.7 | 1.00 | 1.44 | 84.4% |
| door +x+y (x wall) 1 | 723 | 0.7 | 448.5 | 0.97 | 1.50 | 73.3% |
| door +x+y (x wall) 2 | 348 | 1.0 | 467.2 | 0.45 | 1.32 | 23.4% |
| door +x+y (corner) | 231 | 0.9 | 459.8 | 0.30 | 1.38 | 17.0% |
| door -x+y (y wall) 0 | 736 | 1.0 | 457.0 | 0.97 | 1.56 | 82.6% |
| door -x+y (y wall) 1 | 727 | 1.0 | 456.9 | 0.95 | 1.56 | 80.4% |
| door -x+y (y wall) 2 | 384 | 0.7 | 481.0 | 0.48 | 1.32 | 22.4% |
| door -x+y (x wall) 0 | 740 | 0.9 | 459.3 | 0.97 | 1.62 | 83.0% |
| door -x+y (x wall) 1 | 718 | 0.9 | 458.1 | 0.94 | 1.62 | 76.1% |
| door -x+y (x wall) 2 | 338 | 0.9 | 476.4 | 0.42 | 1.20 | 22.9% |
| door -x+y (corner) | 228 | 1.0 | 483.8 | 0.28 | 1.50 | 10.2% |
| door -x-y (y wall) 0 | 735 | 1.0 | 450.2 | 0.98 | 1.56 | 80.4% |
| door -x-y (y wall) 1 | 669 | 0.9 | 454.2 | 0.88 | 1.50 | 67.4% |
| door -x-y (y wall) 2 | 410 | 1.0 | 475.4 | 0.52 | 1.62 | 22.9% |
| door -x-y (x wall) 0 | 728 | 0.9 | 443.0 | 0.98 | 1.50 | 82.2% |
| door -x-y (x wall) 1 | 705 | 1.0 | 448.6 | 0.94 | 1.38 | 73.3% |
| door -x-y (x wall) 2 | 384 | 1.0 | 477.1 | 0.48 | 1.38 | 20.8% |
| door -x-y (corner) | 259 | 0.9 | 455.3 | 0.34 | 1.56 | 17.4% |
| door +x-y (y wall) 0 | 722 | 1.0 | 440.2 | 0.98 | 1.56 | 84.4% |
| door +x-y (y wall) 1 | 682 | 0.9 | 432.5 | 0.94 | 1.56 | 75.0% |
| door +x-y (y wall) 2 | 390 | 0.9 | 465.6 | 0.50 | 1.38 | 23.4% |
| door +x-y (x wall) 0 | 732 | 0.9 | 436.4 | 1.00 | 1.56 | 84.1% |
| door +x-y (x wall) 1 | 695 | 1.0 | 445.7 | 0.93 | 1.62 | 73.3% |
| door +x-y (x wall) 2 | 382 | 0.9 | 466.7 | 0.49 | 1.26 | 19.1% |
| door +x-y (corner) | 278 | 0.9 | 470.3 | 0.35 | 1.44 | 16.7% |

Mean flow / w J averaged over the doors 0.73, over the avenues 0.29.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 942 | 632 / 311 / 162 | 0.7 | 459.8 | 2.41 | 4.51 | 77% | 77% | 0% | 4.65 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 577 | 612 / 0 / 9 | 0.7 | 441.1 | 1.41 | 1.91 | 82% | 73% | 9% | 4.10 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 77 | 285 / 0 / 5 | 0.7 | 463.3 | 0.63 | 1.50 | 17% | 17% | 0% | 3.81 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 961 | 617 / 344 / 224 | 0.2 | 436.7 | 2.71 | 4.91 | 80% | 80% | 0% | 4.67 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 564 | 613 / 0 / 8 | 0.7 | 445.5 | 1.40 | 2.01 | 78% | 69% | 9% | 4.13 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 75 | 257 / 0 / 1 | 0.7 | 464.2 | 0.56 | 1.40 | 19% | 19% | 0% | 3.92 |
| corner +x+y | 1.20 | 85.6 | 771 | 176 / 122 / 496 | 0.7 | 458.3 | 1.73 | 3.81 | 87% | 70% | 17% | 2.62 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 961 | 620 / 342 / 210 | 0.5 | 454.1 | 2.58 | 4.81 | 89% | 78% | 11% | 4.13 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 555 | 610 / 0 / 7 | 0.7 | 453.9 | 1.36 | 1.91 | 78% | 70% | 9% | 4.10 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 78 | 309 / 0 / 4 | 0.7 | 478.0 | 0.66 | 1.71 | 19% | 19% | 0% | 3.65 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 942 | 623 / 319 / 173 | 0.5 | 456.3 | 2.45 | 4.51 | 78% | 78% | 0% | 4.62 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 562 | 593 / 0 / 7 | 0.7 | 455.1 | 1.32 | 2.01 | 80% | 70% | 11% | 4.01 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 80 | 258 / 0 / 64 | 0.7 | 473.5 | 0.68 | 1.60 | 17% | 17% | 0% | 3.73 |
| corner -x+y | 1.20 | 85.6 | 789 | 167 / 127 / 577 | 0.7 | 479.9 | 1.82 | 3.81 | 80% | 65% | 14% | 2.70 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 941 | 624 / 319 / 144 | 0.3 | 447.2 | 2.43 | 4.01 | 78% | 78% | 0% | 4.56 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 564 | 588 / 0 / 12 | 0.7 | 451.3 | 1.33 | 2.01 | 83% | 74% | 9% | 4.07 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 78 | 288 / 0 / 5 | 0.7 | 472.4 | 0.62 | 1.81 | 21% | 21% | 0% | 3.56 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 934 | 608 / 326 / 179 | 0.5 | 440.1 | 2.53 | 4.81 | 78% | 78% | 0% | 4.65 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 574 | 606 / 0 / 14 | 0.7 | 445.7 | 1.39 | 2.01 | 80% | 71% | 9% | 3.99 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 73 | 292 / 0 / 0 | 0.7 | 474.2 | 0.62 | 1.40 | 17% | 17% | 0% | 4.02 |
| corner -x-y | 1.20 | 85.6 | 804 | 199 / 120 / 516 | 0.7 | 468.1 | 1.79 | 4.31 | 85% | 55% | 30% | 2.50 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 940 | 608 / 334 / 198 | 0.3 | 437.4 | 2.61 | 4.61 | 77% | 77% | 0% | 4.74 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 562 | 573 / 0 / 14 | 0.7 | 429.6 | 1.37 | 2.01 | 86% | 73% | 14% | 3.99 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 80 | 292 / 0 / 2 | 0.7 | 462.6 | 0.64 | 1.40 | 19% | 19% | 0% | 3.59 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 938 | 619 / 320 / 135 | 0.3 | 433.4 | 2.48 | 3.91 | 80% | 80% | 0% | 4.66 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 577 | 588 / 0 / 13 | 0.7 | 442.7 | 1.36 | 2.01 | 87% | 73% | 13% | 3.79 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 76 | 294 / 0 / 5 | 0.7 | 463.7 | 0.65 | 2.01 | 17% | 17% | 0% | 3.73 |
| corner +x-y | 1.20 | 85.6 | 795 | 217 / 126 / 486 | 0.7 | 466.7 | 1.78 | 4.11 | 83% | 51% | 32% | 2.43 |

The last agent out (agent 6422, t100 483.8 s): last gangway corner -x+y, exit door -x+y (corner). The gangway that cleared last: corner -x+y at 479.9 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.77 | 477.1 / 464.6 / 444.8 | 466.1 / 451.3 / 350.0 | 721604.0 | 1740277 | 0.221 |
| gangway | 1212 | 1112.9 | 6.77 | 476.4 / 461.2 / 389.9 | 466.1 / 451.3 / 350.0 | 682613.2 | 1391395 | 0.118 |
| walkway | 276 | 257.4 | 5.39 | 333.2 / 220.2 / 43.9 | 268.8 / 214.4 / 24.7 | 351.9 | 63160 | 0.391 |
| avenue | 912 | 858.9 | 2.59 | 396.9 / 11.9 / 0.0 | 301.9 / 1.4 / 0.0 | 0.0 | 106108 | 1.325 |
| exit | 32 | 3.2 | 0.00 | 461.9 / 459.0 / 434.5 | 335.8 / 308.5 / 185.8 | 1249.4 | 2197 | 1.166 |
| concourse | 1116 | 1043.8 | 6.09 | 450.2 / 156.9 / 92.9 | 324.8 / 150.4 / 61.9 | 37389.6 | 177417 | 0.296 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.56 | 416.6 / 406.5 / 388.8 | 408.1 / 404.7 / 376.9 | 731920.7 | 2014891 | 0.046 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -26.5 | -29.5 | gangway | 1.00 | 5.97 | 405.6 | 370.3 | 346.3 | 1989.9 | 0.023 |
| 2 | 26.5 | 27.5 | gangway | 1.00 | 5.93 | 405.3 | 394.9 | 345.1 | 1987.4 | 0.020 |
| 3 | 27.5 | 26.5 | gangway | 1.00 | 5.98 | 395.8 | 393.2 | 345.8 | 1981.4 | 0.020 |
| 4 | 26.5 | -29.5 | gangway | 1.00 | 6.23 | 397.0 | 382.7 | 334.1 | 1971.3 | 0.019 |
| 5 | -28.5 | 27.5 | gangway | 1.00 | 5.88 | 406.3 | 398.4 | 350.0 | 1958.8 | 0.021 |
| 6 | -26.5 | 28.5 | gangway | 1.00 | 6.05 | 409.1 | 392.7 | 336.3 | 1947.9 | 0.025 |
| 7 | -27.5 | 28.5 | gangway | 1.00 | 5.78 | 416.3 | 410.5 | 346.8 | 1943.2 | 0.023 |
| 8 | 29.5 | -26.5 | gangway | 1.00 | 5.96 | 396.2 | 383.7 | 338.3 | 1941.0 | 0.019 |
| 9 | 28.5 | 27.5 | gangway | 1.00 | 5.73 | 400.4 | 396.5 | 348.4 | 1933.3 | 0.020 |
| 10 | 26.5 | 28.5 | gangway | 1.00 | 5.90 | 406.8 | 401.2 | 343.7 | 1929.7 | 0.022 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 25.5 | -30.5 | seat row | 0.64 | 6.93 | 370.5 | 362.4 | 327.6 | 1337.4 | 0.028 |
| 2 | 25.5 | 30.5 | seat row | 0.64 | 6.73 | 368.5 | 363.5 | 326.6 | 1313.5 | 0.029 |
| 3 | 25.5 | -29.5 | seat row | 0.71 | 5.82 | 396.2 | 385.3 | 325.3 | 1298.9 | 0.023 |
| 4 | 30.5 | -25.5 | seat row | 0.64 | 6.56 | 378.0 | 372.7 | 326.9 | 1289.6 | 0.030 |
| 5 | -30.5 | -25.5 | seat row | 0.64 | 6.50 | 365.6 | 362.2 | 321.3 | 1285.8 | 0.031 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1422; agent-steps of seated agents on another row's clearway: 19956.

## Deposit check

Person-seconds deposited: 3761181.4, of them in excluded cells: 6013.422.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 392298 overlapping pair-steps: p99 0.0039, max 0.0270 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0039 max 0.0270; venue-geometry 3: p99 0.0009 max 0.0009 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 24 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.37 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 591 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
