# Experiment `M_load150_s9`

**Task 5.11 stage 1 (gridlock robustness, default model, AMD 26.10.1): venue M, the achievable maximum 121.42% (150% requested, seed 9)**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 19223 agents (load 121.4%, requested 150%): every one of the 15832 seats and 3391 standing (spawnOvercrowdedCrowd, seed 9; below), buffer N = 32768, 3326 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 1460751 evaluations, 59330 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.21)** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `15aa31e8667e4a9417fde7884d907d1832c5e2d6`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-23T18:02:03, 91.1 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Spawn (overcrowding)

| | |
|---|---|
| seated | 15832 (every seat) |
| standing | **3391** (requested round((1.50 - 1) x 15832) = 7916; at most 3391 = floor(2.5 p/m^2 x 1356.6 m^2)) |
| standing floor | walkway + rear concourse, 1356.6 m^2 |
| standing on the walkway / concourse / gangways | 618 / 2773 / 0 |
| **load** | **121.42%** of the seats (requested 150%; the floor takes no more: the achievable maximum) |
| standing crowd's mean density | 2.500 p/m^2 |
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 3.82, all circulation cells 3.82 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 9, 107436 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1186 | 207.4 |
| t90 | 2602 | 455.1 |
| t100 | 3326 | 581.7 |

t_p: the step by which ceil(p x 19223) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 946 | 84 | 29.0 | 530.1 | 20.0 | 58.5 | 28.5-38.5 |
| -x | 5.66 | 960 | 85 | 29.0 | 531.7 | 20.2 | 62.7 | 28.5-38.5 |
| +y | 5.66 | 930 | 79 | 29.0 | 531.0 | 19.6 | 55.3 | 28.9-38.8 |
| -y | 5.66 | 961 | 87 | 29.0 | 531.5 | 20.3 | 59.5 | 28.3-38.3 |
| door +x+y (y wall) 0 | 1.20 | 717 | 1272 | 1.0 | 534.7 | 67.2 | 130.4 | 101.4-111.4 |
| door +x+y (y wall) 1 | 1.20 | 711 | 798 | 0.9 | 545.2 | 65.3 | 125.4 | 104.6-114.6 |
| door +x+y (y wall) 2 | 1.20 | 378 | 267 | 1.0 | 566.2 | 33.4 | 110.3 | 81.9-91.8 |
| door +x+y (x wall) 0 | 1.20 | 725 | 1280 | 1.0 | 538.5 | 67.4 | 130.4 | 104.9-114.9 |
| door +x+y (x wall) 1 | 1.20 | 696 | 795 | 1.6 | 544.8 | 64.0 | 115.3 | 105.5-115.4 |
| door +x+y (x wall) 2 | 1.20 | 391 | 260 | 0.9 | 565.5 | 34.6 | 105.3 | 81.5-91.5 |
| door +x+y (corner) | 1.20 | 234 | 46 | 1.2 | 550.4 | 21.3 | 110.3 | 0.9-10.8 |
| door -x+y (y wall) 0 | 1.20 | 730 | 1272 | 0.9 | 551.8 | 66.2 | 130.4 | 102.5-112.5 |
| door -x+y (y wall) 1 | 1.20 | 712 | 793 | 0.9 | 545.4 | 65.4 | 130.4 | 110.7-120.7 |
| door -x+y (y wall) 2 | 1.20 | 358 | 272 | 0.9 | 578.6 | 31.0 | 105.3 | 8.2-18.2 |
| door -x+y (x wall) 0 | 1.20 | 727 | 1278 | 1.2 | 534.5 | 68.1 | 130.4 | 97.8-107.7 |
| door -x+y (x wall) 1 | 1.20 | 701 | 794 | 0.9 | 542.4 | 64.7 | 115.3 | 99.7-109.7 |
| door -x+y (x wall) 2 | 1.20 | 417 | 275 | 0.9 | 570.0 | 36.6 | 105.3 | 6.8-16.8 |
| door -x+y (corner) | 1.20 | 227 | 51 | 0.7 | 581.7 | 19.5 | 110.3 | 11.4-21.3 |
| door -x-y (y wall) 0 | 1.20 | 726 | 1275 | 1.0 | 554.1 | 65.6 | 115.3 | 94.8-104.8 |
| door -x-y (y wall) 1 | 1.20 | 713 | 807 | 1.4 | 555.5 | 64.3 | 125.4 | 106.2-116.1 |
| door -x-y (y wall) 2 | 1.20 | 393 | 267 | 1.2 | 570.2 | 34.5 | 115.3 | 83.6-93.6 |
| door -x-y (x wall) 0 | 1.20 | 723 | 1272 | 1.2 | 541.3 | 66.9 | 115.3 | 98.1-108.1 |
| door -x-y (x wall) 1 | 1.20 | 706 | 787 | 1.2 | 554.6 | 63.8 | 120.4 | 97.8-107.7 |
| door -x-y (x wall) 2 | 1.20 | 370 | 265 | 0.7 | 580.5 | 31.9 | 110.3 | 63.8-73.8 |
| door -x-y (corner) | 1.20 | 209 | 47 | 0.9 | 579.6 | 18.1 | 110.3 | 10.5-20.5 |
| door +x-y (y wall) 0 | 1.20 | 720 | 1262 | 1.0 | 536.1 | 67.3 | 115.3 | 81.5-91.5 |
| door +x-y (y wall) 1 | 1.20 | 712 | 800 | 0.9 | 541.3 | 65.8 | 120.4 | 97.9-107.9 |
| door +x-y (y wall) 2 | 1.20 | 382 | 269 | 1.2 | 575.4 | 33.3 | 105.3 | 53.2-63.1 |
| door +x-y (x wall) 0 | 1.20 | 723 | 1273 | 1.2 | 529.6 | 68.4 | 120.4 | 104.6-114.6 |
| door +x-y (x wall) 1 | 1.20 | 710 | 795 | 1.0 | 534.0 | 66.6 | 115.3 | 105.6-115.6 |
| door +x-y (x wall) 2 | 1.20 | 384 | 267 | 0.9 | 560.2 | 34.3 | 115.3 | 70.8-80.8 |
| door +x-y (corner) | 1.20 | 231 | 49 | 1.2 | 569.1 | 20.3 | 110.3 | 7.3-17.3 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 946 | 4.9% | 20.6% |
| -x | avenue | 5.66 | 960 | 5.0% | 20.9% |
| +y | avenue | 5.66 | 930 | 4.8% | 20.3% |
| -y | avenue | 5.66 | 961 | 5.0% | 20.9% |
| door +x+y (y wall) 0 | door | 1.20 | 717 | 3.7% | 73.7% |
| door +x+y (y wall) 1 | door | 1.20 | 711 | 3.7% | 73.1% |
| door +x+y (y wall) 2 | door | 1.20 | 378 | 2.0% | 38.9% |
| door +x+y (x wall) 0 | door | 1.20 | 725 | 3.8% | 74.5% |
| door +x+y (x wall) 1 | door | 1.20 | 696 | 3.6% | 71.6% |
| door +x+y (x wall) 2 | door | 1.20 | 391 | 2.0% | 40.2% |
| door +x+y (corner) | door | 1.20 | 234 | 1.2% | 24.1% |
| door -x+y (y wall) 0 | door | 1.20 | 730 | 3.8% | 75.1% |
| door -x+y (y wall) 1 | door | 1.20 | 712 | 3.7% | 73.2% |
| door -x+y (y wall) 2 | door | 1.20 | 358 | 1.9% | 36.8% |
| door -x+y (x wall) 0 | door | 1.20 | 727 | 3.8% | 74.7% |
| door -x+y (x wall) 1 | door | 1.20 | 701 | 3.6% | 72.1% |
| door -x+y (x wall) 2 | door | 1.20 | 417 | 2.2% | 42.9% |
| door -x+y (corner) | door | 1.20 | 227 | 1.2% | 23.3% |
| door -x-y (y wall) 0 | door | 1.20 | 726 | 3.8% | 74.6% |
| door -x-y (y wall) 1 | door | 1.20 | 713 | 3.7% | 73.3% |
| door -x-y (y wall) 2 | door | 1.20 | 393 | 2.0% | 40.4% |
| door -x-y (x wall) 0 | door | 1.20 | 723 | 3.8% | 74.3% |
| door -x-y (x wall) 1 | door | 1.20 | 706 | 3.7% | 72.6% |
| door -x-y (x wall) 2 | door | 1.20 | 370 | 1.9% | 38.0% |
| door -x-y (corner) | door | 1.20 | 209 | 1.1% | 21.5% |
| door +x-y (y wall) 0 | door | 1.20 | 720 | 3.7% | 74.0% |
| door +x-y (y wall) 1 | door | 1.20 | 712 | 3.7% | 73.2% |
| door +x-y (y wall) 2 | door | 1.20 | 382 | 2.0% | 39.3% |
| door +x-y (x wall) 0 | door | 1.20 | 723 | 3.8% | 74.3% |
| door +x-y (x wall) 1 | door | 1.20 | 710 | 3.7% | 73.0% |
| door +x-y (x wall) 2 | door | 1.20 | 384 | 2.0% | 39.5% |
| door +x-y (corner) | door | 1.20 | 231 | 1.2% | 23.7% |
| **doors (28)** | door | 33.60 | 15426 | 80.2% | |
| **avenues (4)** | avenue | 22.64 | 3797 | 19.8% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 581.7 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 42.2%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 957 | 5.0% | 957 | 5.0% |
| straight +x+y (y wing) 1 | straight | yes | 599 | 3.1% | 593 | 3.1% |
| straight +x+y (y wing) 2 | straight | yes | 296 | 1.5% | 292 | 1.5% |
| straight +x+y (x wing) 0 | straight | yes | 943 | 4.9% | 943 | 4.9% |
| straight +x+y (x wing) 1 | straight | yes | 599 | 3.1% | 588 | 3.1% |
| straight +x+y (x wing) 2 | straight | yes | 303 | 1.6% | 303 | 1.6% |
| corner +x+y | corner | yes | 791 | 4.1% | 290 | 1.5% |
| straight -x+y (y wing) 0 | straight | yes | 958 | 5.0% | 958 | 5.0% |
| straight -x+y (y wing) 1 | straight | yes | 605 | 3.1% | 599 | 3.1% |
| straight -x+y (y wing) 2 | straight | yes | 268 | 1.4% | 264 | 1.4% |
| straight -x+y (x wing) 0 | straight | yes | 959 | 5.0% | 959 | 5.0% |
| straight -x+y (x wing) 1 | straight | yes | 596 | 3.1% | 588 | 3.1% |
| straight -x+y (x wing) 2 | straight | yes | 319 | 1.7% | 318 | 1.7% |
| corner -x+y | corner | yes | 770 | 4.0% | 281 | 1.5% |
| straight -x-y (y wing) 0 | straight | yes | 965 | 5.0% | 965 | 5.0% |
| straight -x-y (y wing) 1 | straight | yes | 592 | 3.1% | 587 | 3.1% |
| straight -x-y (y wing) 2 | straight | yes | 304 | 1.6% | 303 | 1.6% |
| straight -x-y (x wing) 0 | straight | yes | 960 | 5.0% | 960 | 5.0% |
| straight -x-y (x wing) 1 | straight | yes | 609 | 3.2% | 602 | 3.1% |
| straight -x-y (x wing) 2 | straight | yes | 287 | 1.5% | 282 | 1.5% |
| corner -x-y | corner | yes | 780 | 4.1% | 269 | 1.4% |
| straight +x-y (y wing) 0 | straight | yes | 957 | 5.0% | 957 | 5.0% |
| straight +x-y (y wing) 1 | straight | yes | 599 | 3.1% | 592 | 3.1% |
| straight +x-y (y wing) 2 | straight | yes | 304 | 1.6% | 301 | 1.6% |
| straight +x-y (x wing) 0 | straight | yes | 950 | 4.9% | 950 | 4.9% |
| straight +x-y (x wing) 1 | straight | yes | 603 | 3.1% | 595 | 3.1% |
| straight +x-y (x wing) 2 | straight | yes | 295 | 1.5% | 295 | 1.5% |
| corner +x-y | corner | yes | 788 | 4.1% | 276 | 1.4% |
| **straight (24)** | | | 14827 | | 14751 | 76.7% |
| **corner (4)** | | | 3129 | | 1116 | 5.8% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 3356, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 946 | 29.0 | 530.1 | 0.24 | 0.70 | 0.0% |
| -x | 960 | 29.0 | 531.7 | 0.24 | 0.75 | 0.0% |
| +y | 930 | 29.0 | 531.0 | 0.23 | 0.66 | 0.0% |
| -y | 961 | 29.0 | 531.5 | 0.24 | 0.71 | 0.0% |
| door +x+y (y wall) 0 | 717 | 1.0 | 534.7 | 0.80 | 1.56 | 48.1% |
| door +x+y (y wall) 1 | 711 | 0.9 | 545.2 | 0.78 | 1.50 | 45.5% |
| door +x+y (y wall) 2 | 378 | 1.0 | 566.2 | 0.40 | 1.32 | 17.5% |
| door +x+y (x wall) 0 | 725 | 1.0 | 538.5 | 0.81 | 1.56 | 43.6% |
| door +x+y (x wall) 1 | 696 | 1.6 | 544.8 | 0.77 | 1.38 | 41.8% |
| door +x+y (x wall) 2 | 391 | 0.9 | 565.5 | 0.41 | 1.26 | 17.5% |
| door +x+y (corner) | 234 | 1.2 | 550.4 | 0.25 | 1.32 | 8.9% |
| door -x+y (y wall) 0 | 730 | 0.9 | 551.8 | 0.79 | 1.56 | 46.4% |
| door -x+y (y wall) 1 | 712 | 0.9 | 545.4 | 0.78 | 1.56 | 41.8% |
| door -x+y (y wall) 2 | 358 | 0.9 | 578.6 | 0.37 | 1.26 | 15.3% |
| door -x+y (x wall) 0 | 727 | 1.2 | 534.5 | 0.82 | 1.56 | 48.1% |
| door -x+y (x wall) 1 | 701 | 0.9 | 542.4 | 0.77 | 1.38 | 34.5% |
| door -x+y (x wall) 2 | 417 | 0.9 | 570.0 | 0.44 | 1.26 | 17.2% |
| door -x+y (corner) | 227 | 0.7 | 581.7 | 0.23 | 1.32 | 8.5% |
| door -x-y (y wall) 0 | 726 | 1.0 | 554.1 | 0.78 | 1.38 | 39.3% |
| door -x-y (y wall) 1 | 713 | 1.4 | 555.5 | 0.77 | 1.50 | 37.5% |
| door -x-y (y wall) 2 | 393 | 1.2 | 570.2 | 0.41 | 1.38 | 17.2% |
| door -x-y (x wall) 0 | 723 | 1.2 | 541.3 | 0.80 | 1.38 | 45.5% |
| door -x-y (x wall) 1 | 706 | 1.2 | 554.6 | 0.76 | 1.44 | 41.1% |
| door -x-y (x wall) 2 | 370 | 0.7 | 580.5 | 0.38 | 1.32 | 16.9% |
| door -x-y (corner) | 209 | 0.9 | 579.6 | 0.22 | 1.32 | 13.6% |
| door +x-y (y wall) 0 | 720 | 1.0 | 536.1 | 0.80 | 1.38 | 48.1% |
| door +x-y (y wall) 1 | 712 | 0.9 | 541.3 | 0.79 | 1.44 | 45.5% |
| door +x-y (y wall) 2 | 382 | 1.2 | 575.4 | 0.40 | 1.26 | 15.5% |
| door +x-y (x wall) 0 | 723 | 1.2 | 529.6 | 0.82 | 1.44 | 46.3% |
| door +x-y (x wall) 1 | 710 | 1.0 | 534.0 | 0.80 | 1.38 | 38.9% |
| door +x-y (x wall) 2 | 384 | 0.9 | 560.2 | 0.41 | 1.38 | 17.5% |
| door +x-y (corner) | 231 | 1.2 | 569.1 | 0.24 | 1.32 | 8.6% |

Mean flow / w J averaged over the doors 0.60, over the avenues 0.24.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 957 | 601 / 356 / 227 | 0.3 | 531.7 | 2.23 | 3.91 | 83% | 80% | 4% | 4.17 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 560 | 593 / 0 / 7 | 0.7 | 542.2 | 1.11 | 1.60 | 84% | 69% | 15% | 3.77 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 78 | 292 / 0 / 5 | 0.7 | 563.2 | 0.53 | 1.20 | 16% | 12% | 4% | 3.04 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 943 | 604 / 339 / 193 | 0.3 | 535.6 | 2.12 | 3.41 | 83% | 81% | 2% | 4.27 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 573 | 588 / 0 / 160 | 0.7 | 541.9 | 1.38 | 3.31 | 85% | 73% | 13% | 3.83 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 77 | 303 / 0 / 0 | 0.7 | 562.5 | 0.54 | 1.20 | 18% | 14% | 4% | 2.89 |
| corner +x+y | 1.20 | 85.6 | 778 | 184 / 106 / 660 | 0.7 | 557.3 | 1.71 | 3.41 | 88% | 54% | 34% | 2.38 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 958 | 616 / 343 / 187 | 0.5 | 548.9 | 2.09 | 3.81 | 80% | 80% | 0% | 4.27 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 563 | 599 / 0 / 7 | 0.7 | 542.4 | 1.12 | 1.50 | 85% | 73% | 13% | 3.73 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 79 | 264 / 0 / 6 | 0.7 | 575.6 | 0.47 | 1.20 | 17% | 12% | 5% | 3.01 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 959 | 605 / 354 / 200 | 0.7 | 531.5 | 2.18 | 3.91 | 87% | 81% | 6% | 4.08 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 573 | 588 / 0 / 10 | 0.7 | 539.4 | 1.11 | 1.50 | 87% | 69% | 18% | 3.65 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 77 | 318 / 0 / 1 | 0.7 | 567.0 | 0.56 | 1.20 | 18% | 14% | 4% | 2.97 |
| corner -x+y | 1.20 | 85.6 | 758 | 177 / 104 / 501 | 0.7 | 577.9 | 1.35 | 3.21 | 84% | 53% | 31% | 2.38 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 965 | 608 / 357 / 228 | 0.2 | 551.1 | 2.16 | 3.51 | 89% | 79% | 11% | 3.95 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 556 | 587 / 0 / 7 | 0.7 | 552.5 | 1.08 | 1.60 | 86% | 70% | 16% | 3.60 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 79 | 303 / 0 / 1 | 0.7 | 567.2 | 0.54 | 1.20 | 18% | 14% | 4% | 3.18 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 960 | 607 / 353 / 222 | 0.5 | 538.4 | 2.20 | 3.61 | 93% | 81% | 11% | 3.95 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 562 | 602 / 0 / 9 | 0.7 | 551.7 | 1.11 | 1.71 | 82% | 68% | 14% | 3.68 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 76 | 282 / 0 / 5 | 0.7 | 577.5 | 0.50 | 1.50 | 16% | 12% | 3% | 3.06 |
| corner -x-y | 1.20 | 85.6 | 770 | 160 / 109 / 522 | 0.7 | 575.8 | 1.38 | 3.91 | 86% | 57% | 29% | 2.44 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 957 | 612 / 345 / 221 | 0.2 | 533.1 | 2.21 | 3.61 | 87% | 81% | 6% | 4.08 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 559 | 592 / 0 / 8 | 0.7 | 538.4 | 1.12 | 1.50 | 85% | 72% | 13% | 3.80 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 77 | 301 / 0 / 4 | 0.7 | 572.5 | 0.53 | 1.40 | 16% | 12% | 3% | 3.01 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 950 | 606 / 345 / 193 | 0.5 | 526.6 | 2.17 | 3.31 | 85% | 83% | 2% | 4.20 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 567 | 596 / 0 / 9 | 0.7 | 531.0 | 1.14 | 1.50 | 85% | 70% | 15% | 3.77 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 79 | 295 / 0 / 0 | 0.7 | 557.3 | 0.53 | 1.20 | 18% | 14% | 4% | 3.12 |
| corner +x-y | 1.20 | 85.6 | 777 | 172 / 104 / 522 | 0.7 | 566.3 | 1.41 | 3.51 | 84% | 54% | 30% | 2.42 |

The last agent out (agent 6426, t100 581.7 s): last gangway corner -x+y, exit door -x+y (corner). The gangway that cleared last: corner -x+y at 577.9 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.88 | 574.7 / 562.3 / 539.6 | 557.8 / 509.3 / 437.3 | 846499.3 | 1919596 | 0.200 |
| gangway | 1212 | 1112.9 | 6.88 | 570.0 / 555.0 / 477.0 | 557.8 / 509.3 / 437.3 | 813370.2 | 1601784 | 0.100 |
| walkway | 276 | 257.4 | 5.33 | 215.7 / 162.3 / 28.3 | 177.2 / 145.3 / 16.8 | 239.3 | 44932 | 0.556 |
| avenue | 912 | 858.9 | 2.62 | 247.7 / 27.1 / 0.0 | 200.4 / 2.3 / 0.0 | 0.0 | 109001 | 1.327 |
| exit | 32 | 3.2 | 0.00 | 560.1 / 557.6 / 513.0 | 322.5 / 298.9 / 181.9 | 1237.7 | 2197 | 1.190 |
| concourse | 1116 | 1043.8 | 5.97 | 526.8 / 118.6 / 78.2 | 215.8 / 118.2 / 54.6 | 31652.1 | 161682 | 0.317 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.60 | 510.6 / 500.9 / 486.9 | 503.7 / 500.9 / 482.2 | 914597.8 | 2444903 | 0.037 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -28.5 | -26.5 | gangway | 1.00 | 6.13 | 515.5 | 507.9 | 424.1 | 2509.7 | 0.018 |
| 2 | 29.5 | -26.5 | gangway | 1.00 | 6.34 | 498.0 | 464.7 | 414.9 | 2433.0 | 0.019 |
| 3 | -29.5 | -26.5 | gangway | 1.00 | 6.18 | 499.9 | 458.1 | 408.9 | 2422.7 | 0.022 |
| 4 | -29.5 | 26.5 | gangway | 1.00 | 6.05 | 491.3 | 467.0 | 419.4 | 2420.8 | 0.016 |
| 5 | -28.5 | 26.5 | gangway | 1.00 | 5.69 | 497.3 | 490.1 | 436.2 | 2412.8 | 0.016 |
| 6 | -28.5 | -27.5 | gangway | 1.00 | 5.93 | 511.1 | 504.6 | 417.9 | 2396.6 | 0.016 |
| 7 | -26.5 | 28.5 | gangway | 1.00 | 5.80 | 495.3 | 486.4 | 418.4 | 2380.8 | 0.019 |
| 8 | 29.5 | 26.5 | gangway | 1.00 | 6.22 | 491.5 | 470.5 | 394.1 | 2360.0 | 0.018 |
| 9 | 27.5 | -27.5 | gangway | 1.00 | 5.95 | 490.4 | 487.5 | 408.6 | 2353.8 | 0.019 |
| 10 | -27.5 | 27.5 | gangway | 1.00 | 5.98 | 502.7 | 498.8 | 437.3 | 2337.8 | 0.018 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 25.5 | -30.5 | seat row | 0.64 | 6.67 | 446.4 | 433.1 | 404.6 | 1625.4 | 0.024 |
| 2 | 30.5 | -25.5 | seat row | 0.64 | 6.73 | 464.9 | 461.6 | 413.5 | 1623.5 | 0.022 |
| 3 | -30.5 | 25.5 | seat row | 0.64 | 6.58 | 456.3 | 445.1 | 411.6 | 1613.2 | 0.024 |
| 4 | -26.5 | -9.5 | seat row | 0.50 | 7.44 | 451.4 | 449.9 | 440.9 | 1572.7 | 0.011 |
| 5 | 25.5 | 30.5 | seat row | 0.64 | 6.61 | 449.9 | 443.2 | 392.1 | 1567.5 | 0.027 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1674; agent-steps of seated agents on another row's clearway: 15527.

## Deposit check

Person-seconds deposited: 4370374.7, of them in excluded cells: 5875.570.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 514929 overlapping pair-steps: p99 0.0027, max 0.0343 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0027 max 0.0343; venue-geometry 10: p99 0.0007 max 0.0007 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 29 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.34 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 526 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
