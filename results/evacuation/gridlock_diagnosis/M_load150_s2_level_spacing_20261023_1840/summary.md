# Experiment `M_load150_s2_level_spacing`

**Task 5.11 stage 1 (diagnosis): Task 5.10's gridlocked run (the model before the calibration, --stair-flow off; M 121.42%, seed 2) to 1 049 s with stall snapshots**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 19223 agents (load 121.4%, requested 150%): every one of the 15832 seats and 3391 standing (spawnOvercrowdedCrowd, seed 2; below), buffer N = 32768, 6000 steps (max steps reached), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 1304403 evaluations, 54583 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.21)** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `15aa31e8667e4a9417fde7884d907d1832c5e2d6`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-23T18:40:23, 352.9 s wall.

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
| t50 | 1084 | 189.6 |
| t90 | 2181 | 381.5 |
| t100 | - | - |

t_p: the step by which ceil(p x 19223) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 939 | 86 | 29.0 | 437.8 | 24.3 | 61.7 | 28.9-38.8 |
| -x | 5.66 | 924 | 84 | 29.0 | 435.0 | 24.1 | 58.5 | 28.9-38.8 |
| +y | 5.66 | 927 | 81 | 29.0 | 442.5 | 23.8 | 59.5 | 28.5-38.5 |
| -y | 5.66 | 944 | 91 | 29.0 | 437.4 | 24.5 | 59.5 | 28.9-38.8 |
| door +x+y (y wall) 0 | 1.20 | 725 | 1273 | 0.9 | 448.8 | 80.9 | 135.4 | 127.9-137.8 |
| door +x+y (y wall) 1 | 1.20 | 712 | 794 | 0.9 | 449.2 | 79.4 | 135.4 | 127.2-137.1 |
| door +x+y (y wall) 2 | 1.20 | 366 | 268 | 0.9 | 483.8 | 37.9 | 110.3 | 83.1-93.1 |
| door +x+y (x wall) 0 | 1.20 | 738 | 1275 | 0.7 | 440.6 | 83.9 | 135.4 | 134.7-144.6 |
| door +x+y (x wall) 1 | 1.20 | 720 | 798 | 0.9 | 446.7 | 80.7 | 130.4 | 126.5-136.4 |
| door +x+y (x wall) 2 | 1.20 | 392 | 270 | 1.0 | 476.1 | 41.2 | 110.3 | 41.1-51.1 |
| door +x+y (corner) | 1.20 | 232 | 44 | 0.9 | 487.6 | 23.8 | 120.4 | 3.3-13.3 |
| door -x+y (y wall) 0 | 1.20 | 734 | 1276 | 1.4 | 461.4 | 79.8 | 135.4 | 136.4-146.4 |
| door -x+y (y wall) 1 | 1.20 | 689 | 796 | 0.7 | 442.2 | 78.0 | 130.4 | 120.9-130.8 |
| door -x+y (y wall) 2 | 1.20 | 392 | 266 | 1.0 | 469.3 | 41.8 | 120.4 | 85.5-95.5 |
| door -x+y (x wall) 0 | 1.20 | 731 | 1275 | 0.9 | 450.6 | 81.2 | 130.4 | 123.3-133.3 |
| door -x+y (x wall) 1 | 1.20 | 696 | 790 | 0.9 | 443.6 | 78.6 | 130.4 | 127.0-137.0 |
| door -x+y (x wall) 2 | 1.20 | 384 | 276 | 1.0 | 467.2 | 41.2 | 105.3 | 97.6-107.6 |
| door -x+y (corner) | 1.20 | 257 | 47 | 0.9 | 458.8 | 28.1 | 120.4 | 78.7-88.7 |
| door -x-y (y wall) 0 | 1.20 | 743 | 1273 | 1.0 | 448.8 | 82.9 | 130.4 | 115.6-125.6 |
| door -x-y (y wall) 1 | 1.20 | 722 | 791 | 1.0 | 461.2 | 78.4 | 130.4 | 128.2-138.2 |
| door -x-y (y wall) 2 | 1.20 | 359 | 261 | 1.0 | 484.7 | 37.1 | 110.3 | 74.3-84.3 |
| door -x-y (x wall) 0 | 1.20 | 741 | 1275 | 1.2 | 449.9 | 82.6 | 125.4 | 125.9-135.9 |
| door -x-y (x wall) 1 | 1.20 | 736 | 799 | 0.7 | 461.1 | 79.9 | 115.3 | 121.0-131.0 |
| door -x-y (x wall) 2 | 1.20 | 328 | 261 | 1.4 | 483.1 | 34.0 | 115.3 | 89.9-99.9 |
| door -x-y (corner) | 1.20 | 232 | 51 | 0.7 | 487.8 | 23.8 | 110.3 | 0.5-10.5 |
| door +x-y (y wall) 0 | 1.20 | 757 | 1275 | 0.7 | 444.4 | 85.3 | 135.4 | 121.4-131.4 |
| door +x-y (y wall) 1 | 1.20 | 840 | 798 | 1.0 | 556.0 | 75.7 | 135.4 | 126.8-136.8 |
| door +x-y (y wall) 2 | 1.20 | 200 | 267 | 1.0 | 137.5 | 73.2 | 125.4 | 80.3-90.3 |
| door +x-y (x wall) 0 | 1.20 | 744 | 1266 | 1.0 | 446.0 | 83.6 | 130.4 | 116.0-125.9 |
| door +x-y (x wall) 1 | 1.20 | 842 | 801 | 0.9 | 545.7 | 77.2 | 125.4 | 117.5-127.5 |
| door +x-y (x wall) 2 | 1.20 | 199 | 270 | 1.0 | 216.7 | 46.1 | 110.3 | 72.1-82.0 |
| door +x-y (corner) | 1.20 | 158 | 45 | 0.9 | 116.0 | 68.5 | 115.3 | 0.7-10.7 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 939 | 4.9% | nan% |
| -x | avenue | 5.66 | 924 | 4.8% | nan% |
| +y | avenue | 5.66 | 927 | 4.9% | nan% |
| -y | avenue | 5.66 | 944 | 4.9% | nan% |
| door +x+y (y wall) 0 | door | 1.20 | 725 | 3.8% | nan% |
| door +x+y (y wall) 1 | door | 1.20 | 712 | 3.7% | nan% |
| door +x+y (y wall) 2 | door | 1.20 | 366 | 1.9% | nan% |
| door +x+y (x wall) 0 | door | 1.20 | 738 | 3.9% | nan% |
| door +x+y (x wall) 1 | door | 1.20 | 720 | 3.8% | nan% |
| door +x+y (x wall) 2 | door | 1.20 | 392 | 2.1% | nan% |
| door +x+y (corner) | door | 1.20 | 232 | 1.2% | nan% |
| door -x+y (y wall) 0 | door | 1.20 | 734 | 3.8% | nan% |
| door -x+y (y wall) 1 | door | 1.20 | 689 | 3.6% | nan% |
| door -x+y (y wall) 2 | door | 1.20 | 392 | 2.1% | nan% |
| door -x+y (x wall) 0 | door | 1.20 | 731 | 3.8% | nan% |
| door -x+y (x wall) 1 | door | 1.20 | 696 | 3.6% | nan% |
| door -x+y (x wall) 2 | door | 1.20 | 384 | 2.0% | nan% |
| door -x+y (corner) | door | 1.20 | 257 | 1.3% | nan% |
| door -x-y (y wall) 0 | door | 1.20 | 743 | 3.9% | nan% |
| door -x-y (y wall) 1 | door | 1.20 | 722 | 3.8% | nan% |
| door -x-y (y wall) 2 | door | 1.20 | 359 | 1.9% | nan% |
| door -x-y (x wall) 0 | door | 1.20 | 741 | 3.9% | nan% |
| door -x-y (x wall) 1 | door | 1.20 | 736 | 3.9% | nan% |
| door -x-y (x wall) 2 | door | 1.20 | 328 | 1.7% | nan% |
| door -x-y (corner) | door | 1.20 | 232 | 1.2% | nan% |
| door +x-y (y wall) 0 | door | 1.20 | 757 | 4.0% | nan% |
| door +x-y (y wall) 1 | door | 1.20 | 840 | 4.4% | nan% |
| door +x-y (y wall) 2 | door | 1.20 | 200 | 1.0% | nan% |
| door +x-y (x wall) 0 | door | 1.20 | 744 | 3.9% | nan% |
| door +x-y (x wall) 1 | door | 1.20 | 842 | 4.4% | nan% |
| door +x-y (x wall) 2 | door | 1.20 | 199 | 1.0% | nan% |
| door +x-y (corner) | door | 1.20 | 158 | 0.8% | nan% |
| **doors (28)** | door | 33.60 | 15369 | 80.5% | |
| **avenues (4)** | avenue | 22.64 | 3734 | 19.5% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = nan s: the share of the exit's nominal throughput over the whole evacuation used; all exits together nan%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 946 | 4.9% | 946 | 5.0% |
| straight +x+y (y wing) 1 | straight | yes | 608 | 3.2% | 601 | 3.1% |
| straight +x+y (y wing) 2 | straight | yes | 276 | 1.4% | 275 | 1.4% |
| straight +x+y (x wing) 0 | straight | yes | 937 | 4.9% | 937 | 4.9% |
| straight +x+y (x wing) 1 | straight | yes | 613 | 3.2% | 605 | 3.2% |
| straight +x+y (x wing) 2 | straight | yes | 313 | 1.6% | 307 | 1.6% |
| corner +x+y | corner | yes | 806 | 4.2% | 298 | 1.6% |
| straight -x+y (y wing) 0 | straight | yes | 937 | 4.9% | 937 | 4.9% |
| straight -x+y (y wing) 1 | straight | yes | 607 | 3.2% | 598 | 3.1% |
| straight -x+y (y wing) 2 | straight | yes | 293 | 1.5% | 290 | 1.5% |
| straight -x+y (x wing) 0 | straight | yes | 949 | 4.9% | 949 | 5.0% |
| straight -x+y (x wing) 1 | straight | yes | 601 | 3.1% | 592 | 3.1% |
| straight -x+y (x wing) 2 | straight | yes | 285 | 1.5% | 282 | 1.5% |
| corner -x+y | corner | yes | 798 | 4.2% | 320 | 1.7% |
| straight -x-y (y wing) 0 | straight | yes | 957 | 5.0% | 957 | 5.0% |
| straight -x-y (y wing) 1 | straight | yes | 628 | 3.3% | 623 | 3.3% |
| straight -x-y (y wing) 2 | straight | yes | 280 | 1.5% | 278 | 1.5% |
| straight -x-y (x wing) 0 | straight | yes | 963 | 5.0% | 963 | 5.0% |
| straight -x-y (x wing) 1 | straight | yes | 624 | 3.2% | 622 | 3.3% |
| straight -x-y (x wing) 2 | straight | yes | 243 | 1.3% | 240 | 1.3% |
| corner -x-y | corner | yes | 773 | 4.0% | 284 | 1.5% |
| straight +x-y (y wing) 0 | straight | yes | 985 | 5.1% | 985 | 5.2% |
| straight +x-y (y wing) 1 | straight | yes | 723 | 3.8% | 722 | 3.8% |
| straight +x-y (y wing) 2 | straight | yes | 138 | 0.7% | 131 | 0.7% |
| straight +x-y (x wing) 0 | straight | yes | 975 | 5.1% | 975 | 5.1% |
| straight +x-y (x wing) 1 | straight | yes | 723 | 3.8% | 722 | 3.8% |
| straight +x-y (x wing) 2 | straight | yes | 111 | 0.6% | 110 | 0.6% |
| corner +x-y | corner | yes | 580 | 3.0% | 203 | 1.1% |
| **straight (24)** | | | 14715 | | 14647 | 76.7% |
| **corner (4)** | | | 2957 | | 1105 | 5.8% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 3351, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 939 | 29.0 | 437.8 | 0.29 | 0.74 | 0.0% |
| -x | 924 | 29.0 | 435.0 | 0.29 | 0.70 | 0.0% |
| +y | 927 | 29.0 | 442.5 | 0.28 | 0.71 | 0.0% |
| -y | 944 | 29.0 | 437.4 | 0.29 | 0.71 | 0.0% |
| door +x+y (y wall) 0 | 725 | 0.9 | 448.8 | 0.97 | 1.62 | 80.4% |
| door +x+y (y wall) 1 | 712 | 0.9 | 449.2 | 0.95 | 1.62 | 71.7% |
| door +x+y (y wall) 2 | 366 | 0.9 | 483.8 | 0.45 | 1.32 | 22.4% |
| door +x+y (x wall) 0 | 738 | 0.7 | 440.6 | 1.00 | 1.62 | 86.7% |
| door +x+y (x wall) 1 | 720 | 0.9 | 446.7 | 0.97 | 1.56 | 77.8% |
| door +x+y (x wall) 2 | 392 | 1.0 | 476.1 | 0.49 | 1.32 | 18.8% |
| door +x+y (corner) | 232 | 0.9 | 487.6 | 0.28 | 1.44 | 12.2% |
| door -x+y (y wall) 0 | 734 | 1.4 | 461.4 | 0.95 | 1.62 | 80.9% |
| door -x+y (y wall) 1 | 689 | 0.7 | 442.2 | 0.93 | 1.56 | 68.9% |
| door -x+y (y wall) 2 | 392 | 1.0 | 469.3 | 0.50 | 1.44 | 22.9% |
| door -x+y (x wall) 0 | 731 | 0.9 | 450.6 | 0.97 | 1.56 | 80.4% |
| door -x+y (x wall) 1 | 696 | 0.9 | 443.6 | 0.94 | 1.56 | 71.1% |
| door -x+y (x wall) 2 | 384 | 1.0 | 467.2 | 0.49 | 1.26 | 23.4% |
| door -x+y (corner) | 257 | 0.9 | 458.8 | 0.34 | 1.44 | 17.0% |
| door -x-y (y wall) 0 | 743 | 1.0 | 448.8 | 0.99 | 1.56 | 84.8% |
| door -x-y (y wall) 1 | 722 | 1.0 | 461.2 | 0.94 | 1.56 | 78.7% |
| door -x-y (y wall) 2 | 359 | 1.0 | 484.7 | 0.44 | 1.32 | 22.4% |
| door -x-y (x wall) 0 | 741 | 1.2 | 449.9 | 0.99 | 1.50 | 84.8% |
| door -x-y (x wall) 1 | 736 | 0.7 | 461.1 | 0.96 | 1.38 | 80.9% |
| door -x-y (x wall) 2 | 328 | 1.4 | 483.1 | 0.41 | 1.38 | 20.4% |
| door -x-y (corner) | 232 | 0.7 | 487.8 | 0.28 | 1.32 | 14.3% |
| door +x-y (y wall) 0 | 757 | 0.7 | 444.4 | 1.02 | 1.62 | 86.7% |
| door +x-y (y wall) 1 | 840 | 1.0 | 556.0 | 0.90 | 1.62 | 78.6% |
| door +x-y (y wall) 2 | 200 | 1.0 | 137.5 | 0.88 | 1.50 | 71.4% |
| door +x-y (x wall) 0 | 744 | 1.0 | 446.0 | 1.00 | 1.56 | 86.7% |
| door +x-y (x wall) 1 | 842 | 0.9 | 545.7 | 0.92 | 1.50 | 78.2% |
| door +x-y (x wall) 2 | 199 | 1.0 | 216.7 | 0.55 | 1.32 | 45.5% |
| door +x-y (corner) | 158 | 0.9 | 116.0 | 0.82 | 1.38 | 50.0% |

Mean flow / w J averaged over the doors 0.76, over the avenues 0.29.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 946 | 610 / 337 / 197 | 0.5 | 445.8 | 2.57 | 4.41 | 78% | 78% | 0% | 4.69 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 568 | 602 / 0 / 8 | 0.7 | 446.2 | 1.37 | 2.01 | 84% | 73% | 11% | 3.88 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 76 | 275 / 0 / 1 | 0.7 | 480.8 | 0.57 | 1.40 | 20% | 20% | 0% | 3.92 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 937 | 618 / 320 / 177 | 0.5 | 437.6 | 2.55 | 4.31 | 82% | 82% | 0% | 4.65 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 573 | 605 / 0 / 11 | 0.7 | 443.7 | 1.39 | 1.91 | 82% | 73% | 9% | 4.00 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 75 | 307 / 0 / 8 | 0.7 | 473.1 | 0.67 | 1.60 | 15% | 15% | 0% | 3.50 |
| corner +x+y | 1.20 | 85.6 | 794 | 176 / 122 / 523 | 0.7 | 483.8 | 1.70 | 3.61 | 80% | 53% | 27% | 2.52 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 935 | 618 / 320 / 176 | 0.3 | 458.4 | 2.43 | 4.61 | 78% | 78% | 0% | 4.70 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 574 | 598 / 0 / 14 | 0.7 | 439.2 | 1.40 | 2.11 | 82% | 71% | 11% | 4.02 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 75 | 290 / 0 / 3 | 0.7 | 466.3 | 0.63 | 1.40 | 17% | 17% | 0% | 3.68 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 949 | 611 / 338 / 180 | 0.2 | 447.6 | 2.52 | 4.51 | 84% | 80% | 4% | 4.35 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 577 | 592 / 0 / 11 | 0.7 | 440.6 | 1.37 | 2.11 | 82% | 71% | 11% | 4.04 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 75 | 282 / 0 / 4 | 0.7 | 464.2 | 0.62 | 1.40 | 19% | 19% | 0% | 3.79 |
| corner -x+y | 1.20 | 85.6 | 783 | 197 / 125 / 492 | 0.7 | 460.2 | 1.77 | 3.71 | 85% | 55% | 30% | 2.49 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 957 | 625 / 333 / 147 | 0.5 | 445.8 | 2.48 | 4.31 | 78% | 78% | 0% | 4.74 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 565 | 623 / 0 / 9 | 0.7 | 458.3 | 1.38 | 2.11 | 87% | 70% | 17% | 3.79 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 76 | 278 / 0 / 7 | 0.7 | 481.7 | 0.59 | 1.81 | 16% | 16% | 0% | 3.77 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 963 | 625 / 339 / 200 | 0.2 | 446.9 | 2.60 | 4.81 | 80% | 80% | 0% | 4.60 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 565 | 622 / 0 / 5 | 0.7 | 458.1 | 1.37 | 2.01 | 78% | 72% | 7% | 4.07 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 76 | 240 / 0 / 3 | 0.7 | 480.1 | 0.51 | 1.30 | 16% | 16% | 0% | 3.62 |
| corner -x-y | 1.20 | 85.6 | 765 | 167 / 117 / 503 | 0.7 | 484.0 | 1.63 | 4.31 | 86% | 67% | 18% | 2.67 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 985 | 640 / 345 / 234 | 0.3 | 441.5 | 2.76 | 4.61 | 80% | 80% | 0% | 4.63 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 621 | 723 / 0 / 7 | 0.7 | 553.1 | 1.32 | 2.01 | 96% | 68% | 29% | 3.11 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 81 | 131 / 0 / 6 | 0.7 | 134.5 | 1.02 | 1.60 | 57% | 57% | 0% | 3.64 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 975 | 634 / 341 / 191 | 0.3 | 443.0 | 2.63 | 4.91 | 78% | 78% | 0% | 4.62 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 635 | 722 / 0 / 9 | 0.5 | 542.7 | 1.35 | 2.01 | 96% | 69% | 27% | 3.34 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 77 | 110 / 0 / 1 | 0.7 | 213.7 | 0.52 | 1.50 | 41% | 41% | 0% | 3.69 |
| corner +x-y | 1.20 | 85.6 | 573 | 90 / 113 / 296 | 0.7 | 474.9 | 1.05 | 3.91 | 100% | 73% | 27% | 2.55 |

The last agent out (agent 13333, t100 nan s): last gangway straight +x-y (y wing) 1, exit door +x-y (y wall) 1. The gangway that cleared last: straight +x-y (y wing) 1 at 553.1 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.70 | 1049.4 / 1049.4 / 1049.3 | 1049.3 / 1047.9 / 1009.4 | 762519.8 | 1828587 | 0.209 |
| gangway | 1212 | 1112.9 | 6.70 | 1049.4 / 1048.9 / 1046.1 | 1049.3 / 1047.9 / 1009.4 | 725100.6 | 1483060 | 0.108 |
| walkway | 276 | 257.4 | 5.36 | 350.2 / 220.6 / 29.0 | 277.4 / 211.3 / 13.1 | 209.7 | 60048 | 0.413 |
| avenue | 912 | 858.9 | 2.52 | 399.1 / 18.9 / 0.0 | 319.7 / 2.4 / 0.0 | 0.0 | 107262 | 1.325 |
| exit | 32 | 3.2 | 0.00 | 491.8 / 488.2 / 461.1 | 373.8 / 342.3 / 214.6 | 1294.6 | 2243 | 1.169 |
| concourse | 1116 | 1043.8 | 6.21 | 462.5 / 147.3 / 93.1 | 372.2 / 141.8 / 61.0 | 35914.9 | 175974 | 0.295 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.64 | 1049.4 / 1049.4 / 1049.4 | 1049.4 / 1049.4 / 1045.1 | 740667.1 | 2071099 | 0.045 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 38.5 | -38.5 | gangway | 1.00 | 5.99 | 1048.4 | 1047.7 | 994.9 | 5761.2 | 0.003 |
| 2 | 35.5 | -35.5 | gangway | 1.00 | 5.43 | 1048.4 | 1047.7 | 988.7 | 5229.0 | 0.004 |
| 3 | 39.5 | -39.5 | gangway | 1.00 | 5.70 | 1048.4 | 1047.7 | 952.4 | 5213.4 | 0.005 |
| 4 | 40.5 | -40.5 | gangway | 1.00 | 5.38 | 1048.2 | 1047.5 | 973.5 | 5051.2 | 0.005 |
| 5 | 36.5 | -36.5 | gangway | 1.00 | 5.44 | 1048.2 | 1047.5 | 991.5 | 5048.5 | 0.003 |
| 6 | 37.5 | -37.5 | gangway | 0.99 | 5.33 | 1048.2 | 1047.7 | 908.8 | 4580.3 | 0.004 |
| 7 | 38.5 | -39.5 | gangway | 0.80 | 5.69 | 1049.1 | 1047.7 | 1009.4 | 4434.6 | 0.005 |
| 8 | 39.5 | -40.5 | gangway | 0.86 | 5.30 | 1048.7 | 1047.5 | 951.1 | 4256.3 | 0.004 |
| 9 | 39.5 | -38.5 | gangway | 0.80 | 5.89 | 1049.1 | 1047.7 | 493.4 | 2221.0 | 0.004 |
| 10 | 38.5 | -37.5 | gangway | 0.72 | 6.40 | 1049.1 | 1047.9 | 486.8 | 2174.5 | 0.010 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 40.5 | -42.5 | seat row | 0.50 | 7.20 | 1049.4 | 1049.4 | 1045.1 | 3047.3 | 0.009 |
| 2 | 39.5 | -41.5 | seat row | 0.60 | 5.48 | 1049.4 | 1049.4 | 509.0 | 1573.5 | 0.006 |
| 3 | 36.5 | -38.5 | seat row | 0.50 | 7.14 | 1049.4 | 457.0 | 433.9 | 1506.9 | 0.007 |
| 4 | 38.5 | -36.5 | seat row | 0.50 | 7.25 | 466.5 | 450.9 | 439.5 | 1481.0 | 0.008 |
| 5 | 38.5 | -35.5 | seat row | 0.50 | 7.26 | 430.1 | 426.2 | 411.0 | 1458.4 | 0.012 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1501; agent-steps of seated agents on another row's clearway: 25546.

## Deposit check

Person-seconds deposited: 3905637.0, of them in excluded cells: 5951.265.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 405390 overlapping pair-steps: p99 0.0037, max 0.0501 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0037 max 0.0501; venue-geometry 4: p99 0.0004 max 0.0004 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 18 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.32 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 598 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
