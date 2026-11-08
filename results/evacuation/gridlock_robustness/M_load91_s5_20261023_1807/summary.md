# Experiment `M_load91_s5`

**Task 5.11 stage 1 (gridlock robustness, default model, AMD 26.10.1): venue M, 91% load (seed 5)**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 14407 agents on 91% of the 15832 seats (spawnSeatedCrowd, seed 5), buffer N = 16384, 2996 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 1034191 evaluations, 44051 switches, 0 forced choices).
Capacity: **within design capacity** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `15aa31e8667e4a9417fde7884d907d1832c5e2d6`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-23T18:07:42, 108.8 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1177 | 205.9 |
| t90 | 2279 | 398.6 |
| t100 | 2996 | 524.0 |

t_p: the step by which ceil(p x 14407) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 753 | 0 | 39.4 | 445.3 | 19.7 | 25.5 | 67.2-77.1 |
| -x | 5.66 | 755 | 0 | 39.5 | 447.9 | 19.6 | 26.6 | 135.9-145.9 |
| +y | 5.66 | 749 | 0 | 39.7 | 447.4 | 19.5 | 25.5 | 57.9-67.9 |
| -y | 5.66 | 753 | 0 | 39.7 | 458.6 | 19.0 | 25.5 | 56.1-66.1 |
| door +x+y (y wall) 0 | 1.20 | 556 | 1019 | 4.9 | 469.8 | 59.8 | 80.2 | 10.0-19.9 |
| door +x+y (y wall) 1 | 1.20 | 543 | 620 | 4.9 | 485.0 | 56.5 | 90.3 | 29.0-39.0 |
| door +x+y (y wall) 2 | 1.20 | 271 | 161 | 4.9 | 488.2 | 28.0 | 80.2 | 8.9-18.9 |
| door +x+y (x wall) 0 | 1.20 | 548 | 1000 | 4.9 | 460.9 | 60.1 | 85.3 | 22.9-32.9 |
| door +x+y (x wall) 1 | 1.20 | 545 | 618 | 4.9 | 478.0 | 57.6 | 85.3 | 11.5-21.5 |
| door +x+y (x wall) 2 | 1.20 | 264 | 163 | 4.9 | 506.9 | 26.3 | 80.2 | 7.3-17.3 |
| door +x+y (corner) | 1.20 | 105 | 0 | 75.7 | 496.6 | 12.5 | 55.2 | 445.7-455.6 |
| door -x+y (y wall) 0 | 1.20 | 561 | 1033 | 4.9 | 465.6 | 60.9 | 85.3 | 11.5-21.5 |
| door -x+y (y wall) 1 | 1.20 | 558 | 627 | 4.9 | 483.8 | 58.2 | 90.3 | 24.1-34.1 |
| door -x+y (y wall) 2 | 1.20 | 254 | 153 | 4.9 | 500.1 | 25.6 | 85.3 | 10.0-19.9 |
| door -x+y (x wall) 0 | 1.20 | 556 | 1017 | 4.9 | 461.6 | 60.9 | 85.3 | 6.1-16.1 |
| door -x+y (x wall) 1 | 1.20 | 557 | 623 | 4.9 | 477.5 | 58.9 | 90.3 | 13.8-23.8 |
| door -x+y (x wall) 2 | 1.20 | 271 | 162 | 4.9 | 494.3 | 27.7 | 80.2 | 4.7-14.7 |
| door -x+y (corner) | 1.20 | 105 | 0 | 50.9 | 485.9 | 12.1 | 85.3 | 318.3-328.3 |
| door -x-y (y wall) 0 | 1.20 | 566 | 1035 | 4.9 | 472.1 | 60.6 | 85.3 | 7.2-17.1 |
| door -x-y (y wall) 1 | 1.20 | 564 | 620 | 4.9 | 480.6 | 59.3 | 90.3 | 25.2-35.2 |
| door -x-y (y wall) 2 | 1.20 | 262 | 159 | 5.2 | 524.0 | 25.2 | 80.2 | 9.8-19.8 |
| door -x-y (x wall) 0 | 1.20 | 561 | 1025 | 4.9 | 482.6 | 58.7 | 90.3 | 26.2-36.2 |
| door -x-y (x wall) 1 | 1.20 | 561 | 626 | 4.9 | 481.2 | 58.9 | 85.3 | 20.8-30.8 |
| door -x-y (x wall) 2 | 1.20 | 271 | 166 | 4.9 | 518.2 | 26.4 | 80.2 | 4.7-14.7 |
| door -x-y (corner) | 1.20 | 83 | 0 | 85.0 | 505.5 | 9.9 | 85.3 | 301.7-311.7 |
| door +x-y (y wall) 0 | 1.20 | 547 | 1009 | 4.9 | 452.7 | 61.1 | 90.3 | 15.2-25.2 |
| door +x-y (y wall) 1 | 1.20 | 541 | 603 | 4.9 | 470.3 | 58.1 | 85.3 | 14.5-24.5 |
| door +x-y (y wall) 2 | 1.20 | 239 | 163 | 4.9 | 497.3 | 24.3 | 85.3 | 10.5-20.5 |
| door +x-y (x wall) 0 | 1.20 | 557 | 1038 | 4.9 | 459.5 | 61.2 | 90.3 | 29.2-39.2 |
| door +x-y (x wall) 1 | 1.20 | 546 | 605 | 4.9 | 470.0 | 58.7 | 95.3 | 17.0-26.9 |
| door +x-y (x wall) 2 | 1.20 | 300 | 162 | 4.9 | 505.0 | 30.0 | 80.2 | 9.8-19.8 |
| door +x-y (corner) | 1.20 | 105 | 0 | 38.5 | 481.5 | 11.8 | 90.3 | 399.8-409.8 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 753 | 5.2% | 18.2% |
| -x | avenue | 5.66 | 755 | 5.2% | 18.3% |
| +y | avenue | 5.66 | 749 | 5.2% | 18.1% |
| -y | avenue | 5.66 | 753 | 5.2% | 18.2% |
| door +x+y (y wall) 0 | door | 1.20 | 556 | 3.9% | 63.5% |
| door +x+y (y wall) 1 | door | 1.20 | 543 | 3.8% | 62.0% |
| door +x+y (y wall) 2 | door | 1.20 | 271 | 1.9% | 30.9% |
| door +x+y (x wall) 0 | door | 1.20 | 548 | 3.8% | 62.5% |
| door +x+y (x wall) 1 | door | 1.20 | 545 | 3.8% | 62.2% |
| door +x+y (x wall) 2 | door | 1.20 | 264 | 1.8% | 30.1% |
| door +x+y (corner) | door | 1.20 | 105 | 0.7% | 12.0% |
| door -x+y (y wall) 0 | door | 1.20 | 561 | 3.9% | 64.0% |
| door -x+y (y wall) 1 | door | 1.20 | 558 | 3.9% | 63.7% |
| door -x+y (y wall) 2 | door | 1.20 | 254 | 1.8% | 29.0% |
| door -x+y (x wall) 0 | door | 1.20 | 556 | 3.9% | 63.5% |
| door -x+y (x wall) 1 | door | 1.20 | 557 | 3.9% | 63.6% |
| door -x+y (x wall) 2 | door | 1.20 | 271 | 1.9% | 30.9% |
| door -x+y (corner) | door | 1.20 | 105 | 0.7% | 12.0% |
| door -x-y (y wall) 0 | door | 1.20 | 566 | 3.9% | 64.6% |
| door -x-y (y wall) 1 | door | 1.20 | 564 | 3.9% | 64.4% |
| door -x-y (y wall) 2 | door | 1.20 | 262 | 1.8% | 29.9% |
| door -x-y (x wall) 0 | door | 1.20 | 561 | 3.9% | 64.0% |
| door -x-y (x wall) 1 | door | 1.20 | 561 | 3.9% | 64.0% |
| door -x-y (x wall) 2 | door | 1.20 | 271 | 1.9% | 30.9% |
| door -x-y (corner) | door | 1.20 | 83 | 0.6% | 9.5% |
| door +x-y (y wall) 0 | door | 1.20 | 547 | 3.8% | 62.4% |
| door +x-y (y wall) 1 | door | 1.20 | 541 | 3.8% | 61.7% |
| door +x-y (y wall) 2 | door | 1.20 | 239 | 1.7% | 27.3% |
| door +x-y (x wall) 0 | door | 1.20 | 557 | 3.9% | 63.6% |
| door +x-y (x wall) 1 | door | 1.20 | 546 | 3.8% | 62.3% |
| door +x-y (x wall) 2 | door | 1.20 | 300 | 2.1% | 34.2% |
| door +x-y (corner) | door | 1.20 | 105 | 0.7% | 12.0% |
| **doors (28)** | door | 33.60 | 11397 | 79.1% | |
| **avenues (4)** | avenue | 22.64 | 3010 | 20.9% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 524.0 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 35.1%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 861 | 6.0% | 861 | 6.0% |
| straight +x+y (y wing) 1 | straight | yes | 555 | 3.9% | 548 | 3.8% |
| straight +x+y (y wing) 2 | straight | yes | 266 | 1.8% | 266 | 1.8% |
| straight +x+y (x wing) 0 | straight | yes | 858 | 6.0% | 858 | 6.0% |
| straight +x+y (x wing) 1 | straight | yes | 553 | 3.8% | 548 | 3.8% |
| straight +x+y (x wing) 2 | straight | yes | 261 | 1.8% | 261 | 1.8% |
| corner +x+y | corner | yes | 733 | 5.1% | 239 | 1.7% |
| straight -x+y (y wing) 0 | straight | yes | 866 | 6.0% | 866 | 6.0% |
| straight -x+y (y wing) 1 | straight | yes | 564 | 3.9% | 558 | 3.9% |
| straight -x+y (y wing) 2 | straight | yes | 253 | 1.8% | 253 | 1.8% |
| straight -x+y (x wing) 0 | straight | yes | 858 | 6.0% | 858 | 6.0% |
| straight -x+y (x wing) 1 | straight | yes | 567 | 3.9% | 563 | 3.9% |
| straight -x+y (x wing) 2 | straight | yes | 265 | 1.8% | 265 | 1.8% |
| corner -x+y | corner | yes | 733 | 5.1% | 252 | 1.7% |
| straight -x-y (y wing) 0 | straight | yes | 874 | 6.1% | 874 | 6.1% |
| straight -x-y (y wing) 1 | straight | yes | 571 | 4.0% | 566 | 3.9% |
| straight -x-y (y wing) 2 | straight | yes | 260 | 1.8% | 260 | 1.8% |
| straight -x-y (x wing) 0 | straight | yes | 879 | 6.1% | 879 | 6.1% |
| straight -x-y (x wing) 1 | straight | yes | 564 | 3.9% | 561 | 3.9% |
| straight -x-y (x wing) 2 | straight | yes | 271 | 1.9% | 271 | 1.9% |
| corner -x-y | corner | yes | 734 | 5.1% | 220 | 1.5% |
| straight +x-y (y wing) 0 | straight | yes | 854 | 5.9% | 854 | 5.9% |
| straight +x-y (y wing) 1 | straight | yes | 548 | 3.8% | 544 | 3.8% |
| straight +x-y (y wing) 2 | straight | yes | 236 | 1.6% | 236 | 1.6% |
| straight +x-y (x wing) 0 | straight | yes | 863 | 6.0% | 863 | 6.0% |
| straight +x-y (x wing) 1 | straight | yes | 555 | 3.9% | 550 | 3.8% |
| straight +x-y (x wing) 2 | straight | yes | 296 | 2.1% | 296 | 2.1% |
| corner +x-y | corner | yes | 713 | 4.9% | 237 | 1.6% |
| **straight (24)** | | | 13498 | | 13459 | 93.4% |
| **corner (4)** | | | 2913 | | 948 | 6.6% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 753 | 39.4 | 445.3 | 0.24 | 0.31 | 0.0% |
| -x | 755 | 39.5 | 447.9 | 0.23 | 0.32 | 0.0% |
| +y | 749 | 39.7 | 447.4 | 0.23 | 0.31 | 0.0% |
| -y | 753 | 39.7 | 458.6 | 0.23 | 0.31 | 0.0% |
| door +x+y (y wall) 0 | 556 | 4.9 | 469.8 | 0.72 | 0.96 | 37.5% |
| door +x+y (y wall) 1 | 543 | 4.9 | 485.0 | 0.68 | 1.08 | 26.5% |
| door +x+y (y wall) 2 | 271 | 4.9 | 488.2 | 0.34 | 0.96 | 2.0% |
| door +x+y (x wall) 0 | 548 | 4.9 | 460.9 | 0.72 | 1.02 | 29.8% |
| door +x+y (x wall) 1 | 545 | 4.9 | 478.0 | 0.69 | 1.02 | 25.0% |
| door +x+y (x wall) 2 | 264 | 4.9 | 506.9 | 0.31 | 0.96 | 2.0% |
| door +x+y (corner) | 105 | 75.7 | 496.6 | 0.15 | 0.66 | 0.0% |
| door -x+y (y wall) 0 | 561 | 4.9 | 465.6 | 0.73 | 1.02 | 34.0% |
| door -x+y (y wall) 1 | 558 | 4.9 | 483.8 | 0.70 | 1.08 | 24.5% |
| door -x+y (y wall) 2 | 254 | 4.9 | 500.1 | 0.31 | 1.02 | 2.0% |
| door -x+y (x wall) 0 | 556 | 4.9 | 461.6 | 0.73 | 1.02 | 36.2% |
| door -x+y (x wall) 1 | 557 | 4.9 | 477.5 | 0.70 | 1.08 | 25.0% |
| door -x+y (x wall) 2 | 271 | 4.9 | 494.3 | 0.33 | 0.96 | 6.0% |
| door -x+y (corner) | 105 | 50.9 | 485.9 | 0.14 | 1.02 | 2.3% |
| door -x-y (y wall) 0 | 566 | 4.9 | 472.1 | 0.72 | 1.02 | 33.3% |
| door -x-y (y wall) 1 | 564 | 4.9 | 480.6 | 0.71 | 1.08 | 30.6% |
| door -x-y (y wall) 2 | 262 | 5.2 | 524.0 | 0.30 | 0.96 | 3.8% |
| door -x-y (x wall) 0 | 561 | 4.9 | 482.6 | 0.70 | 1.08 | 32.7% |
| door -x-y (x wall) 1 | 561 | 4.9 | 481.2 | 0.70 | 1.02 | 26.5% |
| door -x-y (x wall) 2 | 271 | 4.9 | 518.2 | 0.32 | 0.96 | 3.8% |
| door -x-y (corner) | 83 | 85.0 | 505.5 | 0.12 | 1.02 | 2.3% |
| door +x-y (y wall) 0 | 547 | 4.9 | 452.7 | 0.73 | 1.08 | 34.8% |
| door +x-y (y wall) 1 | 541 | 4.9 | 470.3 | 0.69 | 1.02 | 27.1% |
| door +x-y (y wall) 2 | 239 | 4.9 | 497.3 | 0.29 | 1.02 | 2.0% |
| door +x-y (x wall) 0 | 557 | 4.9 | 459.5 | 0.73 | 1.08 | 31.9% |
| door +x-y (x wall) 1 | 546 | 4.9 | 470.0 | 0.70 | 1.14 | 25.0% |
| door +x-y (x wall) 2 | 300 | 4.9 | 505.0 | 0.36 | 0.96 | 5.9% |
| door +x-y (corner) | 105 | 38.5 | 481.5 | 0.14 | 1.08 | 2.2% |

Mean flow / w J averaged over the doors 0.52, over the avenues 0.23.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 861 | 556 / 305 / 187 | 0.7 | 466.8 | 2.25 | 3.61 | 91% | 77% | 15% | 3.72 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 515 | 548 / 0 / 8 | 0.7 | 482.0 | 1.15 | 1.71 | 78% | 63% | 14% | 3.54 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 59 | 266 / 0 / 0 | 0.7 | 485.2 | 0.55 | 1.30 | 12% | 6% | 6% | 2.18 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 858 | 548 / 310 / 209 | 0.7 | 457.9 | 2.33 | 3.61 | 91% | 78% | 13% | 3.71 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 500 | 548 / 0 / 10 | 0.7 | 475.0 | 1.18 | 1.71 | 75% | 62% | 12% | 3.54 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 63 | 261 / 0 / 0 | 0.7 | 503.9 | 0.52 | 1.40 | 12% | 10% | 2% | 2.52 |
| corner +x+y | 1.20 | 85.6 | 725 | 105 / 134 / 504 | 0.7 | 498.0 | 1.49 | 3.21 | 84% | 54% | 30% | 2.42 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 866 | 561 / 305 / 201 | 0.7 | 462.6 | 2.31 | 3.81 | 89% | 77% | 13% | 3.68 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 521 | 558 / 0 / 7 | 0.7 | 480.8 | 1.18 | 1.71 | 78% | 59% | 18% | 3.35 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 59 | 253 / 0 / 0 | 0.7 | 497.1 | 0.51 | 1.30 | 10% | 10% | 0% | 2.54 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 858 | 556 / 302 / 182 | 0.7 | 458.6 | 2.27 | 3.51 | 91% | 78% | 13% | 3.69 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 523 | 563 / 0 / 6 | 0.7 | 474.5 | 1.20 | 1.81 | 79% | 67% | 12% | 3.50 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 64 | 265 / 0 / 0 | 0.7 | 491.3 | 0.54 | 1.50 | 12% | 10% | 2% | 2.46 |
| corner -x+y | 1.20 | 85.6 | 724 | 106 / 146 / 485 | 0.7 | 491.1 | 1.50 | 3.61 | 84% | 58% | 26% | 2.45 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 874 | 566 / 308 / 189 | 0.7 | 469.1 | 2.27 | 3.71 | 90% | 77% | 12% | 3.76 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 515 | 566 / 0 / 6 | 0.7 | 477.7 | 1.20 | 1.81 | 77% | 65% | 12% | 3.54 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 59 | 260 / 0 / 0 | 0.7 | 521.0 | 0.50 | 1.50 | 9% | 9% | 0% | 2.68 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 879 | 561 / 318 / 197 | 0.7 | 479.6 | 2.25 | 3.71 | 90% | 73% | 16% | 3.54 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 512 | 561 / 0 / 7 | 0.7 | 478.2 | 1.19 | 1.60 | 81% | 65% | 17% | 3.33 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 63 | 271 / 0 / 0 | 0.7 | 515.3 | 0.53 | 1.50 | 12% | 10% | 2% | 2.49 |
| corner -x-y | 1.20 | 85.6 | 729 | 83 / 137 / 522 | 0.7 | 515.1 | 1.44 | 3.31 | 83% | 58% | 25% | 2.46 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 854 | 547 / 307 / 209 | 0.7 | 449.7 | 2.37 | 3.81 | 89% | 76% | 13% | 3.63 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 513 | 544 / 0 / 9 | 0.7 | 467.4 | 1.18 | 1.71 | 85% | 66% | 19% | 3.25 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 60 | 236 / 0 / 0 | 0.7 | 494.3 | 0.48 | 1.40 | 10% | 10% | 0% | 2.67 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 863 | 557 / 306 / 186 | 0.7 | 456.5 | 2.30 | 3.81 | 89% | 78% | 11% | 3.87 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 519 | 550 / 0 / 6 | 0.7 | 467.0 | 1.19 | 1.71 | 83% | 64% | 19% | 3.33 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 66 | 296 / 0 / 0 | 0.7 | 502.0 | 0.59 | 1.40 | 12% | 10% | 2% | 2.64 |
| corner +x-y | 1.20 | 85.6 | 705 | 105 / 132 / 483 | 0.7 | 495.9 | 1.45 | 4.11 | 82% | 58% | 24% | 2.49 |

The last agent out (agent 7584, t100 524.0 s): last gangway straight -x-y (y wing) 2, exit door -x-y (y wall) 2. The gangway that cleared last: straight -x-y (y wing) 2 at 521.0 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.79 | 515.3 / 499.9 / 469.8 | 501.1 / 477.8 / 395.6 | 583438.9 | 1434515 | 0.221 |
| gangway | 1212 | 1112.9 | 6.79 | 515.3 / 498.3 / 418.0 | 501.1 / 477.8 / 395.6 | 582648.3 | 1294769 | 0.112 |
| walkway | 276 | 257.4 | 3.16 | 177.4 / 104.9 / 0.0 | 116.8 / 16.1 / 0.0 | 0.0 | 23043 | 0.915 |
| avenue | 912 | 858.9 | 2.01 | 194.7 / 0.0 / 0.0 | 167.6 / 0.0 / 0.0 | 0.0 | 86417 | 1.327 |
| exit | 32 | 3.2 | 0.00 | 485.7 / 484.1 / 438.3 | 237.7 / 215.0 / 124.0 | 790.6 | 1511 | 1.323 |
| concourse | 1116 | 1043.8 | 1.92 | 455.3 / 0.0 / 0.0 | 111.4 / 0.0 / 0.0 | 0.0 | 28774 | 1.195 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.61 | 439.4 / 429.2 / 422.4 | 432.0 / 429.2 / 418.9 | 566753.9 | 1657886 | 0.050 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -27.5 | -27.5 | gangway | 1.00 | 5.96 | 431.8 | 423.6 | 378.3 | 2175.6 | 0.015 |
| 2 | -28.5 | -27.5 | gangway | 1.00 | 6.06 | 426.1 | 423.3 | 372.6 | 2092.8 | 0.016 |
| 3 | 27.5 | 27.5 | gangway | 1.00 | 5.88 | 430.3 | 427.1 | 364.7 | 2059.8 | 0.021 |
| 4 | -27.5 | 27.5 | gangway | 1.00 | 5.86 | 435.7 | 433.4 | 367.5 | 2059.8 | 0.019 |
| 5 | 28.5 | 26.5 | gangway | 1.00 | 6.29 | 416.1 | 402.8 | 343.5 | 2034.0 | 0.026 |
| 6 | -26.5 | -28.5 | gangway | 1.00 | 6.03 | 435.7 | 424.5 | 352.8 | 2020.2 | 0.023 |
| 7 | 28.5 | 27.5 | gangway | 1.00 | 6.10 | 429.9 | 400.9 | 343.0 | 1996.6 | 0.020 |
| 8 | -27.5 | -28.5 | gangway | 1.00 | 5.91 | 438.7 | 426.6 | 366.1 | 1987.5 | 0.019 |
| 9 | -28.5 | -26.5 | gangway | 1.00 | 6.00 | 437.8 | 427.3 | 340.2 | 1986.6 | 0.023 |
| 10 | 28.5 | -26.5 | gangway | 1.00 | 5.89 | 431.1 | 422.2 | 342.5 | 1968.6 | 0.020 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -26.5 | -24.5 | seat row | 0.50 | 7.40 | 426.1 | 424.8 | 412.8 | 1456.3 | 0.014 |
| 2 | -24.5 | -26.5 | seat row | 0.50 | 7.38 | 432.0 | 428.7 | 418.9 | 1456.2 | 0.013 |
| 3 | 24.5 | 26.5 | seat row | 0.50 | 7.21 | 420.5 | 420.0 | 407.9 | 1435.9 | 0.016 |
| 4 | -24.5 | 26.5 | seat row | 0.50 | 7.29 | 416.8 | 414.5 | 408.8 | 1392.0 | 0.015 |
| 5 | 24.5 | -26.5 | seat row | 0.50 | 7.39 | 415.2 | 401.8 | 394.9 | 1390.8 | 0.014 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1558; agent-steps of seated agents on another row's clearway: 13227.

## Deposit check

Person-seconds deposited: 3095209.1, of them in excluded cells: 2808.110.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 241166 overlapping pair-steps: p99 0.0022, max 0.0292 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0022 max 0.0292; venue-geometry 2: p99 0.0002 max 0.0002 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00752 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 16 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.29 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 532 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
