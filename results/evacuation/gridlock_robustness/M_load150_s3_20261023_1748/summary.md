# Experiment `M_load150_s3`

**Task 5.11 stage 1 (gridlock robustness, default model, AMD 26.10.1): venue M, the achievable maximum 121.42% (150% requested, seed 3)**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 19223 agents (load 121.4%, requested 150%): every one of the 15832 seats and 3391 standing (spawnOvercrowdedCrowd, seed 3; below), buffer N = 32768, 3384 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 1460153 evaluations, 59087 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.21)** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `15aa31e8667e4a9417fde7884d907d1832c5e2d6`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-23T17:48:54, 114.8 s wall.

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
| t50 | 1180 | 206.4 |
| t90 | 2608 | 456.2 |
| t100 | 3384 | 591.9 |

t_p: the step by which ceil(p x 19223) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 950 | 86 | 29.0 | 530.8 | 20.1 | 65.9 | 28.3-38.3 |
| -x | 5.66 | 967 | 81 | 29.0 | 527.0 | 20.6 | 56.4 | 28.7-38.7 |
| +y | 5.66 | 955 | 80 | 29.0 | 532.2 | 20.1 | 56.4 | 28.5-38.5 |
| -y | 5.66 | 959 | 90 | 29.0 | 527.5 | 20.4 | 61.7 | 28.5-38.5 |
| door +x+y (y wall) 0 | 1.20 | 729 | 1280 | 0.9 | 545.7 | 66.9 | 130.4 | 100.7-110.7 |
| door +x+y (y wall) 1 | 1.20 | 704 | 801 | 0.9 | 556.9 | 63.3 | 115.3 | 111.4-121.4 |
| door +x+y (y wall) 2 | 1.20 | 385 | 269 | 1.4 | 580.2 | 33.3 | 120.4 | 78.9-88.9 |
| door +x+y (x wall) 0 | 1.20 | 720 | 1274 | 0.9 | 530.7 | 67.9 | 120.4 | 104.1-114.0 |
| door +x+y (x wall) 1 | 1.20 | 688 | 790 | 0.7 | 554.3 | 62.1 | 120.4 | 91.5-101.4 |
| door +x+y (x wall) 2 | 1.20 | 403 | 269 | 1.0 | 578.9 | 34.9 | 115.3 | 85.0-95.0 |
| door +x+y (corner) | 1.20 | 228 | 45 | 0.9 | 583.3 | 19.6 | 115.3 | 3.8-13.8 |
| door -x+y (y wall) 0 | 1.20 | 719 | 1269 | 1.0 | 528.9 | 68.1 | 120.4 | 103.9-113.9 |
| door -x+y (y wall) 1 | 1.20 | 711 | 797 | 1.0 | 554.6 | 64.2 | 120.4 | 113.3-123.3 |
| door -x+y (y wall) 2 | 1.20 | 379 | 265 | 0.7 | 591.9 | 32.0 | 110.3 | 67.7-77.7 |
| door -x+y (x wall) 0 | 1.20 | 730 | 1274 | 0.9 | 532.9 | 68.6 | 135.4 | 104.2-114.2 |
| door -x+y (x wall) 1 | 1.20 | 706 | 805 | 0.9 | 556.9 | 63.5 | 115.3 | 116.7-126.6 |
| door -x+y (x wall) 2 | 1.20 | 392 | 266 | 0.9 | 588.2 | 33.4 | 110.3 | 71.7-81.7 |
| door -x+y (corner) | 1.20 | 210 | 41 | 1.0 | 579.5 | 18.1 | 110.3 | 2.1-12.1 |
| door -x-y (y wall) 0 | 1.20 | 724 | 1270 | 1.0 | 530.1 | 68.4 | 115.3 | 102.7-112.6 |
| door -x-y (y wall) 1 | 1.20 | 712 | 800 | 0.9 | 570.5 | 62.5 | 120.4 | 102.5-112.5 |
| door -x-y (y wall) 2 | 1.20 | 377 | 271 | 1.0 | 580.9 | 32.5 | 110.3 | 29.6-39.5 |
| door -x-y (x wall) 0 | 1.20 | 724 | 1281 | 0.9 | 544.0 | 66.6 | 125.4 | 106.0-116.0 |
| door -x-y (x wall) 1 | 1.20 | 712 | 791 | 1.0 | 549.2 | 64.9 | 125.4 | 102.1-112.1 |
| door -x-y (x wall) 2 | 1.20 | 394 | 269 | 1.0 | 584.7 | 33.7 | 110.3 | 70.5-80.5 |
| door -x-y (corner) | 1.20 | 199 | 39 | 0.9 | 586.1 | 17.0 | 115.3 | 0.5-10.5 |
| door +x-y (y wall) 0 | 1.20 | 722 | 1269 | 1.0 | 547.6 | 66.0 | 125.4 | 104.2-114.2 |
| door +x-y (y wall) 1 | 1.20 | 725 | 799 | 0.9 | 549.0 | 66.1 | 125.4 | 107.6-117.5 |
| door +x-y (y wall) 2 | 1.20 | 362 | 266 | 0.9 | 573.7 | 31.6 | 115.3 | 73.6-83.6 |
| door +x-y (x wall) 0 | 1.20 | 723 | 1272 | 0.9 | 541.9 | 66.8 | 120.4 | 97.8-107.7 |
| door +x-y (x wall) 1 | 1.20 | 720 | 797 | 1.0 | 550.8 | 65.5 | 125.4 | 107.6-117.5 |
| door +x-y (x wall) 2 | 1.20 | 380 | 270 | 0.9 | 569.0 | 33.4 | 110.3 | 37.6-47.6 |
| door +x-y (corner) | 1.20 | 214 | 47 | 0.9 | 578.1 | 18.5 | 115.3 | 10.7-20.6 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 950 | 4.9% | 20.4% |
| -x | avenue | 5.66 | 967 | 5.0% | 20.7% |
| +y | avenue | 5.66 | 955 | 5.0% | 20.5% |
| -y | avenue | 5.66 | 959 | 5.0% | 20.5% |
| door +x+y (y wall) 0 | door | 1.20 | 729 | 3.8% | 73.7% |
| door +x+y (y wall) 1 | door | 1.20 | 704 | 3.7% | 71.1% |
| door +x+y (y wall) 2 | door | 1.20 | 385 | 2.0% | 38.9% |
| door +x+y (x wall) 0 | door | 1.20 | 720 | 3.7% | 72.8% |
| door +x+y (x wall) 1 | door | 1.20 | 688 | 3.6% | 69.5% |
| door +x+y (x wall) 2 | door | 1.20 | 403 | 2.1% | 40.7% |
| door +x+y (corner) | door | 1.20 | 228 | 1.2% | 23.0% |
| door -x+y (y wall) 0 | door | 1.20 | 719 | 3.7% | 72.7% |
| door -x+y (y wall) 1 | door | 1.20 | 711 | 3.7% | 71.8% |
| door -x+y (y wall) 2 | door | 1.20 | 379 | 2.0% | 38.3% |
| door -x+y (x wall) 0 | door | 1.20 | 730 | 3.8% | 73.8% |
| door -x+y (x wall) 1 | door | 1.20 | 706 | 3.7% | 71.3% |
| door -x+y (x wall) 2 | door | 1.20 | 392 | 2.0% | 39.6% |
| door -x+y (corner) | door | 1.20 | 210 | 1.1% | 21.2% |
| door -x-y (y wall) 0 | door | 1.20 | 724 | 3.8% | 73.2% |
| door -x-y (y wall) 1 | door | 1.20 | 712 | 3.7% | 71.9% |
| door -x-y (y wall) 2 | door | 1.20 | 377 | 2.0% | 38.1% |
| door -x-y (x wall) 0 | door | 1.20 | 724 | 3.8% | 73.2% |
| door -x-y (x wall) 1 | door | 1.20 | 712 | 3.7% | 71.9% |
| door -x-y (x wall) 2 | door | 1.20 | 394 | 2.0% | 39.8% |
| door -x-y (corner) | door | 1.20 | 199 | 1.0% | 20.1% |
| door +x-y (y wall) 0 | door | 1.20 | 722 | 3.8% | 73.0% |
| door +x-y (y wall) 1 | door | 1.20 | 725 | 3.8% | 73.3% |
| door +x-y (y wall) 2 | door | 1.20 | 362 | 1.9% | 36.6% |
| door +x-y (x wall) 0 | door | 1.20 | 723 | 3.8% | 73.1% |
| door +x-y (x wall) 1 | door | 1.20 | 720 | 3.7% | 72.8% |
| door +x-y (x wall) 2 | door | 1.20 | 380 | 2.0% | 38.4% |
| door +x-y (corner) | door | 1.20 | 214 | 1.1% | 21.6% |
| **doors (28)** | door | 33.60 | 15392 | 80.1% | |
| **avenues (4)** | avenue | 22.64 | 3831 | 19.9% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 591.9 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 41.4%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 944 | 4.9% | 944 | 4.9% |
| straight +x+y (y wing) 1 | straight | yes | 601 | 3.1% | 590 | 3.1% |
| straight +x+y (y wing) 2 | straight | yes | 288 | 1.5% | 287 | 1.5% |
| straight +x+y (x wing) 0 | straight | yes | 960 | 5.0% | 960 | 5.0% |
| straight +x+y (x wing) 1 | straight | yes | 605 | 3.1% | 593 | 3.1% |
| straight +x+y (x wing) 2 | straight | yes | 297 | 1.5% | 297 | 1.5% |
| corner +x+y | corner | yes | 790 | 4.1% | 294 | 1.5% |
| straight -x+y (y wing) 0 | straight | yes | 963 | 5.0% | 963 | 5.0% |
| straight -x+y (y wing) 1 | straight | yes | 600 | 3.1% | 594 | 3.1% |
| straight -x+y (y wing) 2 | straight | yes | 297 | 1.5% | 292 | 1.5% |
| straight -x+y (x wing) 0 | straight | yes | 952 | 5.0% | 952 | 5.0% |
| straight -x+y (x wing) 1 | straight | yes | 596 | 3.1% | 590 | 3.1% |
| straight -x+y (x wing) 2 | straight | yes | 299 | 1.6% | 296 | 1.5% |
| corner -x+y | corner | yes | 793 | 4.1% | 278 | 1.4% |
| straight -x-y (y wing) 0 | straight | yes | 952 | 5.0% | 952 | 5.0% |
| straight -x-y (y wing) 1 | straight | yes | 596 | 3.1% | 592 | 3.1% |
| straight -x-y (y wing) 2 | straight | yes | 298 | 1.6% | 293 | 1.5% |
| straight -x-y (x wing) 0 | straight | yes | 951 | 4.9% | 951 | 4.9% |
| straight -x-y (x wing) 1 | straight | yes | 606 | 3.2% | 601 | 3.1% |
| straight -x-y (x wing) 2 | straight | yes | 313 | 1.6% | 310 | 1.6% |
| corner -x-y | corner | yes | 799 | 4.2% | 267 | 1.4% |
| straight +x-y (y wing) 0 | straight | yes | 954 | 5.0% | 954 | 5.0% |
| straight +x-y (y wing) 1 | straight | yes | 614 | 3.2% | 606 | 3.2% |
| straight +x-y (y wing) 2 | straight | yes | 277 | 1.4% | 277 | 1.4% |
| straight +x-y (x wing) 0 | straight | yes | 962 | 5.0% | 962 | 5.0% |
| straight +x-y (x wing) 1 | straight | yes | 608 | 3.2% | 603 | 3.1% |
| straight +x-y (x wing) 2 | straight | yes | 298 | 1.6% | 293 | 1.5% |
| corner +x-y | corner | yes | 784 | 4.1% | 271 | 1.4% |
| **straight (24)** | | | 14831 | | 14752 | 76.7% |
| **corner (4)** | | | 3166 | | 1110 | 5.8% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 3361, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 950 | 29.0 | 530.8 | 0.24 | 0.79 | 0.0% |
| -x | 967 | 29.0 | 527.0 | 0.25 | 0.67 | 0.0% |
| +y | 955 | 29.0 | 532.2 | 0.24 | 0.67 | 0.0% |
| -y | 959 | 29.0 | 527.5 | 0.24 | 0.74 | 0.0% |
| door +x+y (y wall) 0 | 729 | 0.9 | 545.7 | 0.80 | 1.56 | 45.5% |
| door +x+y (y wall) 1 | 704 | 0.9 | 556.9 | 0.76 | 1.38 | 39.3% |
| door +x+y (y wall) 2 | 385 | 1.4 | 580.2 | 0.40 | 1.44 | 15.3% |
| door +x+y (x wall) 0 | 720 | 0.9 | 530.7 | 0.81 | 1.44 | 48.1% |
| door +x+y (x wall) 1 | 688 | 0.7 | 554.3 | 0.74 | 1.44 | 41.1% |
| door +x+y (x wall) 2 | 403 | 1.0 | 578.9 | 0.42 | 1.38 | 16.9% |
| door +x+y (corner) | 228 | 0.9 | 583.3 | 0.23 | 1.38 | 8.5% |
| door -x+y (y wall) 0 | 719 | 1.0 | 528.9 | 0.81 | 1.44 | 48.1% |
| door -x+y (y wall) 1 | 711 | 1.0 | 554.6 | 0.77 | 1.44 | 37.5% |
| door -x+y (y wall) 2 | 379 | 0.7 | 591.9 | 0.38 | 1.32 | 15.0% |
| door -x+y (x wall) 0 | 730 | 0.9 | 532.9 | 0.82 | 1.62 | 51.9% |
| door -x+y (x wall) 1 | 706 | 0.9 | 556.9 | 0.76 | 1.38 | 41.1% |
| door -x+y (x wall) 2 | 392 | 0.9 | 588.2 | 0.40 | 1.32 | 15.3% |
| door -x+y (corner) | 210 | 1.0 | 579.5 | 0.22 | 1.32 | 8.5% |
| door -x-y (y wall) 0 | 724 | 1.0 | 530.1 | 0.82 | 1.38 | 53.7% |
| door -x-y (y wall) 1 | 712 | 0.9 | 570.5 | 0.75 | 1.44 | 32.8% |
| door -x-y (y wall) 2 | 377 | 1.0 | 580.9 | 0.39 | 1.32 | 15.3% |
| door -x-y (x wall) 0 | 724 | 0.9 | 544.0 | 0.80 | 1.50 | 41.8% |
| door -x-y (x wall) 1 | 712 | 1.0 | 549.2 | 0.78 | 1.50 | 37.5% |
| door -x-y (x wall) 2 | 394 | 1.0 | 584.7 | 0.40 | 1.32 | 16.9% |
| door -x-y (corner) | 199 | 0.9 | 586.1 | 0.20 | 1.38 | 8.5% |
| door +x-y (y wall) 0 | 722 | 1.0 | 547.6 | 0.79 | 1.50 | 45.5% |
| door +x-y (y wall) 1 | 725 | 0.9 | 549.0 | 0.79 | 1.50 | 42.9% |
| door +x-y (y wall) 2 | 362 | 0.9 | 573.7 | 0.38 | 1.38 | 17.2% |
| door +x-y (x wall) 0 | 723 | 0.9 | 541.9 | 0.80 | 1.44 | 43.6% |
| door +x-y (x wall) 1 | 720 | 1.0 | 550.8 | 0.78 | 1.50 | 48.2% |
| door +x-y (x wall) 2 | 380 | 0.9 | 569.0 | 0.40 | 1.32 | 15.5% |
| door +x-y (corner) | 214 | 0.9 | 578.1 | 0.22 | 1.38 | 12.1% |

Mean flow / w J averaged over the doors 0.59, over the avenues 0.24.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 944 | 606 / 338 / 204 | 0.7 | 542.7 | 2.12 | 3.51 | 84% | 80% | 4% | 4.24 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 568 | 590 / 0 / 13 | 0.7 | 553.9 | 1.09 | 1.60 | 86% | 70% | 16% | 3.72 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 77 | 287 / 0 / 1 | 0.7 | 577.2 | 0.50 | 1.20 | 19% | 14% | 5% | 2.93 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 960 | 605 / 356 / 239 | 0.2 | 527.7 | 2.27 | 3.81 | 91% | 83% | 8% | 4.03 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 566 | 593 / 0 / 14 | 0.7 | 551.3 | 1.10 | 1.50 | 80% | 70% | 11% | 3.81 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 75 | 297 / 0 / 0 | 0.7 | 576.0 | 0.52 | 1.20 | 17% | 16% | 2% | 3.21 |
| corner +x+y | 1.20 | 85.6 | 775 | 183 / 111 / 509 | 0.7 | 579.5 | 1.39 | 3.41 | 85% | 49% | 36% | 2.34 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 963 | 604 / 360 / 249 | 0.5 | 525.9 | 2.31 | 4.01 | 92% | 83% | 9% | 3.91 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 547 | 594 / 0 / 7 | 0.7 | 551.7 | 1.09 | 1.50 | 80% | 66% | 14% | 3.75 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 79 | 292 / 0 / 5 | 0.7 | 588.9 | 0.50 | 1.30 | 17% | 13% | 3% | 2.98 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 952 | 613 / 339 / 198 | 0.5 | 530.0 | 2.17 | 3.91 | 87% | 81% | 6% | 4.17 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 561 | 590 / 0 / 8 | 0.7 | 553.9 | 1.08 | 1.50 | 82% | 71% | 11% | 3.77 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 80 | 296 / 0 / 3 | 0.7 | 585.2 | 0.51 | 1.30 | 17% | 14% | 3% | 2.88 |
| corner -x+y | 1.20 | 85.6 | 783 | 168 / 110 / 528 | 0.7 | 583.0 | 1.38 | 3.21 | 83% | 56% | 27% | 2.51 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 952 | 612 / 341 / 197 | 0.3 | 527.2 | 2.18 | 4.01 | 89% | 83% | 6% | 4.09 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 555 | 592 / 0 / 8 | 0.7 | 567.6 | 1.06 | 1.50 | 79% | 68% | 11% | 3.78 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 83 | 294 / 0 / 9 | 0.7 | 577.9 | 0.52 | 1.40 | 19% | 14% | 5% | 2.86 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 951 | 604 / 347 / 226 | 0.5 | 541.0 | 2.18 | 3.91 | 91% | 80% | 11% | 3.89 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 556 | 601 / 0 / 6 | 0.7 | 546.2 | 1.11 | 1.50 | 82% | 69% | 13% | 3.68 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 78 | 310 / 0 / 3 | 0.7 | 581.7 | 0.54 | 1.30 | 17% | 14% | 3% | 3.08 |
| corner -x-y | 1.20 | 85.6 | 791 | 144 / 123 / 550 | 0.7 | 582.3 | 1.40 | 3.81 | 83% | 59% | 24% | 2.52 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 954 | 607 / 347 / 201 | 0.3 | 544.7 | 2.12 | 3.51 | 82% | 80% | 2% | 4.18 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 562 | 606 / 0 / 12 | 0.7 | 546.1 | 1.13 | 1.60 | 82% | 73% | 9% | 3.77 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 79 | 277 / 0 / 0 | 0.7 | 570.7 | 0.49 | 1.30 | 17% | 14% | 3% | 3.12 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 962 | 610 / 353 / 206 | 0.3 | 538.9 | 2.17 | 3.31 | 82% | 80% | 2% | 4.24 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 561 | 603 / 0 / 10 | 0.7 | 547.8 | 1.12 | 1.50 | 80% | 69% | 11% | 3.70 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 78 | 293 / 0 / 5 | 0.7 | 566.0 | 0.53 | 1.20 | 16% | 12% | 4% | 2.85 |
| corner +x-y | 1.20 | 85.6 | 770 | 159 / 112 / 526 | 0.7 | 574.2 | 1.39 | 3.11 | 84% | 57% | 28% | 2.45 |

The last agent out (agent 4416, t100 591.9 s): last gangway straight -x+y (y wing) 2, exit door -x+y (y wall) 2. The gangway that cleared last: straight -x+y (y wing) 2 at 588.9 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.70 | 583.3 / 578.6 / 545.9 | 567.9 / 546.8 / 446.2 | 847103.2 | 1934756 | 0.199 |
| gangway | 1212 | 1112.9 | 6.70 | 580.5 / 571.6 / 487.6 | 567.9 / 546.8 / 446.2 | 812802.1 | 1613490 | 0.099 |
| walkway | 276 | 257.4 | 5.33 | 237.7 / 178.8 / 25.2 | 201.0 / 169.5 / 17.3 | 193.3 | 47420 | 0.535 |
| avenue | 912 | 858.9 | 2.59 | 255.5 / 11.9 / 0.0 | 199.6 / 1.4 / 0.0 | 0.0 | 109986 | 1.327 |
| exit | 32 | 3.2 | 0.00 | 567.2 / 564.4 / 514.4 | 326.0 / 295.9 / 182.1 | 1230.0 | 2189 | 1.192 |
| concourse | 1116 | 1043.8 | 6.04 | 523.1 / 130.5 / 79.1 | 213.9 / 122.1 / 57.7 | 32877.8 | 161672 | 0.316 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.55 | 514.8 / 501.1 / 478.7 | 510.9 / 500.6 / 475.0 | 898486.9 | 2427997 | 0.037 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -28.5 | -27.5 | gangway | 1.00 | 6.08 | 502.2 | 494.1 | 425.7 | 2509.9 | 0.016 |
| 2 | -28.5 | -26.5 | gangway | 1.00 | 6.06 | 499.2 | 478.4 | 418.2 | 2456.0 | 0.020 |
| 3 | 26.5 | -29.5 | gangway | 1.00 | 6.17 | 503.9 | 458.1 | 415.8 | 2446.1 | 0.022 |
| 4 | -29.5 | 26.5 | gangway | 1.00 | 6.40 | 506.2 | 466.1 | 413.7 | 2415.9 | 0.019 |
| 5 | 28.5 | -26.5 | gangway | 1.00 | 6.04 | 492.2 | 487.3 | 414.9 | 2401.8 | 0.019 |
| 6 | 27.5 | -27.5 | gangway | 1.00 | 5.95 | 506.7 | 480.3 | 433.9 | 2396.9 | 0.014 |
| 7 | -26.5 | -28.5 | gangway | 1.00 | 5.79 | 492.4 | 482.2 | 427.5 | 2391.0 | 0.015 |
| 8 | 28.5 | 26.5 | gangway | 1.00 | 6.05 | 506.7 | 501.1 | 408.8 | 2370.2 | 0.017 |
| 9 | -26.5 | 28.5 | gangway | 1.00 | 6.08 | 499.0 | 486.4 | 410.0 | 2364.9 | 0.021 |
| 10 | -27.5 | -28.5 | gangway | 1.00 | 5.82 | 507.8 | 501.8 | 415.2 | 2359.5 | 0.018 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 25.5 | 30.5 | seat row | 0.64 | 6.62 | 474.0 | 468.4 | 423.4 | 1673.5 | 0.022 |
| 2 | 25.5 | -30.5 | seat row | 0.64 | 6.80 | 438.5 | 419.3 | 394.8 | 1611.6 | 0.025 |
| 3 | -24.5 | 26.5 | seat row | 0.50 | 6.92 | 487.3 | 482.9 | 475.0 | 1578.5 | 0.015 |
| 4 | -25.5 | -30.5 | seat row | 0.64 | 6.67 | 448.3 | 432.2 | 401.1 | 1572.2 | 0.025 |
| 5 | -26.5 | 9.5 | seat row | 0.50 | 7.44 | 445.7 | 443.7 | 434.8 | 1567.0 | 0.011 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1726; agent-steps of seated agents on another row's clearway: 20307.

## Deposit check

Person-seconds deposited: 4368633.6, of them in excluded cells: 5880.101.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 483967 overlapping pair-steps: p99 0.0032, max 0.0749 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0032 max 0.0749; venue-geometry 6: p99 0.0007 max 0.0007 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 26 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.40 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 560 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
