# Experiment `M_load93_s7`

**Task 5.11 stage 1 (gridlock robustness, default model, AMD 26.10.1): venue M, 93% load (seed 7)**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 14724 agents on 93% of the 15832 seats (spawnSeatedCrowd, seed 7), buffer N = 16384, 2963 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 1074295 evaluations, 44903 switches, 0 forced choices).
Capacity: **within design capacity** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `15aa31e8667e4a9417fde7884d907d1832c5e2d6`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-23T18:11:56, 110.0 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1200 | 209.9 |
| t90 | 2307 | 403.5 |
| t100 | 2963 | 518.2 |

t_p: the step by which ceil(p x 14724) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 764 | 0 | 39.7 | 457.4 | 19.4 | 25.5 | 70.5-80.5 |
| -x | 5.66 | 773 | 0 | 39.7 | 460.7 | 19.5 | 25.5 | 52.5-62.4 |
| +y | 5.66 | 762 | 0 | 39.7 | 453.4 | 19.5 | 25.5 | 50.7-60.7 |
| -y | 5.66 | 772 | 0 | 39.4 | 460.4 | 19.4 | 25.5 | 50.7-60.7 |
| door +x+y (y wall) 0 | 1.20 | 568 | 1037 | 4.9 | 472.6 | 60.7 | 85.3 | 23.3-33.2 |
| door +x+y (y wall) 1 | 1.20 | 562 | 634 | 4.9 | 481.9 | 58.9 | 85.3 | 7.2-17.1 |
| door +x+y (y wall) 2 | 1.20 | 253 | 167 | 4.9 | 513.7 | 24.9 | 85.3 | 29.6-39.5 |
| door +x+y (x wall) 0 | 1.20 | 573 | 1044 | 4.9 | 475.0 | 60.9 | 80.2 | 9.6-19.6 |
| door +x+y (x wall) 1 | 1.20 | 573 | 639 | 4.9 | 493.2 | 58.6 | 85.3 | 10.0-19.9 |
| door +x+y (x wall) 2 | 1.20 | 294 | 166 | 4.9 | 504.8 | 29.4 | 80.2 | 4.7-14.7 |
| door +x+y (corner) | 1.20 | 94 | 0 | 82.6 | 493.6 | 11.4 | 70.2 | 392.8-402.8 |
| door -x+y (y wall) 0 | 1.20 | 570 | 1048 | 4.9 | 463.3 | 62.1 | 90.3 | 24.8-34.8 |
| door -x+y (y wall) 1 | 1.20 | 564 | 621 | 4.9 | 495.0 | 57.5 | 80.2 | 9.8-19.8 |
| door -x+y (y wall) 2 | 1.20 | 279 | 168 | 4.9 | 518.2 | 27.2 | 80.2 | 4.7-14.7 |
| door -x+y (x wall) 0 | 1.20 | 566 | 1041 | 4.9 | 475.0 | 60.2 | 85.3 | 19.2-29.2 |
| door -x+y (x wall) 1 | 1.20 | 562 | 627 | 4.9 | 491.8 | 57.7 | 85.3 | 21.7-31.7 |
| door -x+y (x wall) 2 | 1.20 | 274 | 169 | 4.9 | 510.7 | 27.1 | 80.2 | 4.7-14.7 |
| door -x+y (corner) | 1.20 | 101 | 0 | 67.5 | 506.2 | 11.5 | 75.2 | 81.9-91.8 |
| door -x-y (y wall) 0 | 1.20 | 579 | 1047 | 4.9 | 478.0 | 61.2 | 80.2 | 18.7-28.7 |
| door -x-y (y wall) 1 | 1.20 | 557 | 641 | 4.9 | 492.7 | 57.1 | 90.3 | 23.3-33.2 |
| door -x-y (y wall) 2 | 1.20 | 292 | 162 | 4.9 | 509.9 | 28.9 | 80.2 | 9.8-19.8 |
| door -x-y (x wall) 0 | 1.20 | 566 | 1045 | 4.9 | 482.2 | 59.3 | 85.3 | 6.1-16.1 |
| door -x-y (x wall) 1 | 1.20 | 565 | 637 | 4.9 | 493.9 | 57.7 | 85.3 | 14.7-24.7 |
| door -x-y (x wall) 2 | 1.20 | 269 | 164 | 4.9 | 510.2 | 26.6 | 90.3 | 12.8-22.7 |
| door -x-y (corner) | 1.20 | 85 | 0 | 53.5 | 498.8 | 9.5 | 80.2 | 74.0-84.0 |
| door +x-y (y wall) 0 | 1.20 | 566 | 1043 | 4.9 | 461.1 | 62.0 | 85.3 | 12.4-22.4 |
| door +x-y (y wall) 1 | 1.20 | 557 | 627 | 4.9 | 476.6 | 59.0 | 85.3 | 24.0-33.9 |
| door +x-y (y wall) 2 | 1.20 | 253 | 161 | 4.9 | 509.5 | 25.1 | 80.2 | 4.7-14.7 |
| door +x-y (x wall) 0 | 1.20 | 565 | 1035 | 4.9 | 464.4 | 61.5 | 90.3 | 26.1-36.0 |
| door +x-y (x wall) 1 | 1.20 | 566 | 636 | 4.9 | 485.2 | 58.9 | 85.3 | 54.2-64.2 |
| door +x-y (x wall) 2 | 1.20 | 297 | 165 | 4.9 | 516.8 | 29.0 | 80.2 | 4.7-14.7 |
| door +x-y (corner) | 1.20 | 103 | 0 | 55.6 | 508.6 | 11.4 | 80.2 | 310.3-320.3 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 764 | 5.2% | 18.7% |
| -x | avenue | 5.66 | 773 | 5.2% | 18.9% |
| +y | avenue | 5.66 | 762 | 5.2% | 18.6% |
| -y | avenue | 5.66 | 772 | 5.2% | 18.9% |
| door +x+y (y wall) 0 | door | 1.20 | 568 | 3.9% | 65.6% |
| door +x+y (y wall) 1 | door | 1.20 | 562 | 3.8% | 64.9% |
| door +x+y (y wall) 2 | door | 1.20 | 253 | 1.7% | 29.2% |
| door +x+y (x wall) 0 | door | 1.20 | 573 | 3.9% | 66.1% |
| door +x+y (x wall) 1 | door | 1.20 | 573 | 3.9% | 66.1% |
| door +x+y (x wall) 2 | door | 1.20 | 294 | 2.0% | 33.9% |
| door +x+y (corner) | door | 1.20 | 94 | 0.6% | 10.8% |
| door -x+y (y wall) 0 | door | 1.20 | 570 | 3.9% | 65.8% |
| door -x+y (y wall) 1 | door | 1.20 | 564 | 3.8% | 65.1% |
| door -x+y (y wall) 2 | door | 1.20 | 279 | 1.9% | 32.2% |
| door -x+y (x wall) 0 | door | 1.20 | 566 | 3.8% | 65.3% |
| door -x+y (x wall) 1 | door | 1.20 | 562 | 3.8% | 64.9% |
| door -x+y (x wall) 2 | door | 1.20 | 274 | 1.9% | 31.6% |
| door -x+y (corner) | door | 1.20 | 101 | 0.7% | 11.7% |
| door -x-y (y wall) 0 | door | 1.20 | 579 | 3.9% | 66.8% |
| door -x-y (y wall) 1 | door | 1.20 | 557 | 3.8% | 64.3% |
| door -x-y (y wall) 2 | door | 1.20 | 292 | 2.0% | 33.7% |
| door -x-y (x wall) 0 | door | 1.20 | 566 | 3.8% | 65.3% |
| door -x-y (x wall) 1 | door | 1.20 | 565 | 3.8% | 65.2% |
| door -x-y (x wall) 2 | door | 1.20 | 269 | 1.8% | 31.0% |
| door -x-y (corner) | door | 1.20 | 85 | 0.6% | 9.8% |
| door +x-y (y wall) 0 | door | 1.20 | 566 | 3.8% | 65.3% |
| door +x-y (y wall) 1 | door | 1.20 | 557 | 3.8% | 64.3% |
| door +x-y (y wall) 2 | door | 1.20 | 253 | 1.7% | 29.2% |
| door +x-y (x wall) 0 | door | 1.20 | 565 | 3.8% | 65.2% |
| door +x-y (x wall) 1 | door | 1.20 | 566 | 3.8% | 65.3% |
| door +x-y (x wall) 2 | door | 1.20 | 297 | 2.0% | 34.3% |
| door +x-y (corner) | door | 1.20 | 103 | 0.7% | 11.9% |
| **doors (28)** | door | 33.60 | 11653 | 79.1% | |
| **avenues (4)** | avenue | 22.64 | 3071 | 20.9% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 518.2 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 36.3%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 889 | 6.0% | 889 | 6.0% |
| straight +x+y (y wing) 1 | straight | yes | 570 | 3.9% | 566 | 3.8% |
| straight +x+y (y wing) 2 | straight | yes | 249 | 1.7% | 249 | 1.7% |
| straight +x+y (x wing) 0 | straight | yes | 883 | 6.0% | 883 | 6.0% |
| straight +x+y (x wing) 1 | straight | yes | 579 | 3.9% | 573 | 3.9% |
| straight +x+y (x wing) 2 | straight | yes | 294 | 2.0% | 294 | 2.0% |
| corner +x+y | corner | yes | 738 | 5.0% | 233 | 1.6% |
| straight -x+y (y wing) 0 | straight | yes | 878 | 6.0% | 878 | 6.0% |
| straight -x+y (y wing) 1 | straight | yes | 567 | 3.9% | 564 | 3.8% |
| straight -x+y (y wing) 2 | straight | yes | 280 | 1.9% | 279 | 1.9% |
| straight -x+y (x wing) 0 | straight | yes | 884 | 6.0% | 884 | 6.0% |
| straight -x+y (x wing) 1 | straight | yes | 566 | 3.8% | 562 | 3.8% |
| straight -x+y (x wing) 2 | straight | yes | 274 | 1.9% | 274 | 1.9% |
| corner -x+y | corner | yes | 757 | 5.1% | 233 | 1.6% |
| straight -x-y (y wing) 0 | straight | yes | 900 | 6.1% | 900 | 6.1% |
| straight -x-y (y wing) 1 | straight | yes | 572 | 3.9% | 568 | 3.9% |
| straight -x-y (y wing) 2 | straight | yes | 281 | 1.9% | 281 | 1.9% |
| straight -x-y (x wing) 0 | straight | yes | 885 | 6.0% | 885 | 6.0% |
| straight -x-y (x wing) 1 | straight | yes | 569 | 3.9% | 565 | 3.8% |
| straight -x-y (x wing) 2 | straight | yes | 269 | 1.8% | 269 | 1.8% |
| corner -x-y | corner | yes | 748 | 5.1% | 228 | 1.5% |
| straight +x-y (y wing) 0 | straight | yes | 874 | 5.9% | 874 | 5.9% |
| straight +x-y (y wing) 1 | straight | yes | 564 | 3.8% | 562 | 3.8% |
| straight +x-y (y wing) 2 | straight | yes | 248 | 1.7% | 248 | 1.7% |
| straight +x-y (x wing) 0 | straight | yes | 883 | 6.0% | 883 | 6.0% |
| straight +x-y (x wing) 1 | straight | yes | 572 | 3.9% | 569 | 3.9% |
| straight +x-y (x wing) 2 | straight | yes | 294 | 2.0% | 294 | 2.0% |
| corner +x-y | corner | yes | 728 | 4.9% | 237 | 1.6% |
| **straight (24)** | | | 13824 | | 13793 | 93.7% |
| **corner (4)** | | | 2971 | | 931 | 6.3% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 764 | 39.7 | 457.4 | 0.23 | 0.31 | 0.0% |
| -x | 773 | 39.7 | 460.7 | 0.23 | 0.31 | 0.0% |
| +y | 762 | 39.7 | 453.4 | 0.23 | 0.31 | 0.0% |
| -y | 772 | 39.4 | 460.4 | 0.23 | 0.31 | 0.0% |
| door +x+y (y wall) 0 | 568 | 4.9 | 472.6 | 0.73 | 1.02 | 31.2% |
| door +x+y (y wall) 1 | 562 | 4.9 | 481.9 | 0.70 | 1.02 | 26.5% |
| door +x+y (y wall) 2 | 253 | 4.9 | 513.7 | 0.30 | 1.02 | 5.8% |
| door +x+y (x wall) 0 | 573 | 4.9 | 475.0 | 0.73 | 0.96 | 33.3% |
| door +x+y (x wall) 1 | 573 | 4.9 | 493.2 | 0.70 | 1.02 | 28.0% |
| door +x+y (x wall) 2 | 294 | 4.9 | 504.8 | 0.35 | 0.96 | 5.9% |
| door +x+y (corner) | 94 | 82.6 | 493.6 | 0.14 | 0.84 | 0.0% |
| door -x+y (y wall) 0 | 570 | 4.9 | 463.3 | 0.74 | 1.08 | 34.0% |
| door -x+y (y wall) 1 | 564 | 4.9 | 495.0 | 0.69 | 0.96 | 28.0% |
| door -x+y (y wall) 2 | 279 | 4.9 | 518.2 | 0.32 | 0.96 | 5.8% |
| door -x+y (x wall) 0 | 566 | 4.9 | 475.0 | 0.72 | 1.02 | 39.6% |
| door -x+y (x wall) 1 | 562 | 4.9 | 491.8 | 0.69 | 1.02 | 26.0% |
| door -x+y (x wall) 2 | 274 | 4.9 | 510.7 | 0.32 | 0.96 | 3.8% |
| door -x+y (corner) | 101 | 67.5 | 506.2 | 0.14 | 0.90 | 0.0% |
| door -x-y (y wall) 0 | 579 | 4.9 | 478.0 | 0.73 | 0.96 | 37.5% |
| door -x-y (y wall) 1 | 557 | 4.9 | 492.7 | 0.68 | 1.08 | 28.0% |
| door -x-y (y wall) 2 | 292 | 4.9 | 509.9 | 0.35 | 0.96 | 3.8% |
| door -x-y (x wall) 0 | 566 | 4.9 | 482.2 | 0.71 | 1.02 | 28.6% |
| door -x-y (x wall) 1 | 565 | 4.9 | 493.9 | 0.69 | 1.02 | 26.0% |
| door -x-y (x wall) 2 | 269 | 4.9 | 510.2 | 0.32 | 1.08 | 3.8% |
| door -x-y (corner) | 85 | 53.5 | 498.8 | 0.11 | 0.96 | 0.0% |
| door +x-y (y wall) 0 | 566 | 4.9 | 461.1 | 0.74 | 1.02 | 31.9% |
| door +x-y (y wall) 1 | 557 | 4.9 | 476.6 | 0.71 | 1.02 | 29.2% |
| door +x-y (y wall) 2 | 253 | 4.9 | 509.5 | 0.30 | 0.96 | 3.8% |
| door +x-y (x wall) 0 | 565 | 4.9 | 464.4 | 0.74 | 1.08 | 40.4% |
| door +x-y (x wall) 1 | 566 | 4.9 | 485.2 | 0.70 | 1.02 | 26.5% |
| door +x-y (x wall) 2 | 297 | 4.9 | 516.8 | 0.35 | 0.96 | 5.8% |
| door +x-y (corner) | 103 | 55.6 | 508.6 | 0.14 | 0.96 | 2.1% |

Mean flow / w J averaged over the doors 0.52, over the avenues 0.23.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 889 | 568 / 321 / 203 | 0.7 | 469.6 | 2.33 | 3.61 | 90% | 77% | 12% | 3.77 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 527 | 566 / 0 / 10 | 0.7 | 478.9 | 1.20 | 2.01 | 80% | 67% | 12% | 3.54 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 64 | 249 / 0 / 0 | 0.7 | 510.7 | 0.49 | 1.60 | 10% | 8% | 2% | 2.67 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 883 | 573 / 310 / 201 | 0.7 | 472.1 | 2.30 | 4.01 | 90% | 77% | 12% | 3.82 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 537 | 573 / 0 / 9 | 0.7 | 490.3 | 1.19 | 1.81 | 76% | 64% | 12% | 3.53 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 60 | 294 / 0 / 0 | 0.7 | 501.8 | 0.59 | 1.50 | 10% | 10% | 0% | 2.83 |
| corner +x+y | 1.20 | 85.6 | 727 | 94 / 139 / 513 | 0.7 | 504.8 | 1.48 | 3.61 | 84% | 55% | 29% | 2.43 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 878 | 570 / 308 / 204 | 0.7 | 460.4 | 2.35 | 3.61 | 85% | 79% | 6% | 3.98 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 515 | 564 / 0 / 6 | 0.7 | 492.0 | 1.16 | 1.71 | 74% | 64% | 10% | 3.43 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 64 | 279 / 0 / 1 | 0.7 | 515.3 | 0.54 | 1.40 | 10% | 10% | 0% | 2.74 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 884 | 566 / 318 / 213 | 0.7 | 472.2 | 2.33 | 4.11 | 90% | 75% | 15% | 3.67 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 516 | 562 / 0 / 10 | 0.7 | 488.9 | 1.17 | 1.81 | 76% | 60% | 16% | 3.43 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 68 | 274 / 0 / 0 | 0.7 | 507.8 | 0.54 | 1.50 | 12% | 10% | 2% | 2.56 |
| corner -x+y | 1.20 | 85.6 | 749 | 101 / 132 / 533 | 0.7 | 509.3 | 1.51 | 4.81 | 85% | 58% | 27% | 2.42 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 900 | 579 / 321 / 188 | 0.7 | 475.0 | 2.29 | 3.51 | 90% | 79% | 10% | 3.69 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 514 | 568 / 0 / 6 | 0.7 | 489.7 | 1.17 | 1.71 | 72% | 64% | 8% | 3.73 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 64 | 281 / 0 / 0 | 0.7 | 506.9 | 0.55 | 1.50 | 14% | 10% | 4% | 2.51 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 885 | 566 / 320 / 235 | 0.7 | 479.2 | 2.34 | 3.81 | 90% | 76% | 14% | 3.68 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 527 | 565 / 0 / 9 | 0.7 | 491.0 | 1.17 | 1.71 | 76% | 66% | 10% | 3.67 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 66 | 269 / 0 / 0 | 0.7 | 507.2 | 0.53 | 1.71 | 12% | 10% | 2% | 2.61 |
| corner -x-y | 1.20 | 85.6 | 740 | 85 / 143 / 527 | 0.7 | 501.1 | 1.51 | 3.61 | 86% | 59% | 27% | 2.41 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 874 | 566 / 309 / 211 | 0.7 | 458.1 | 2.37 | 3.91 | 89% | 80% | 9% | 3.93 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 526 | 562 / 0 / 5 | 0.7 | 473.6 | 1.20 | 1.60 | 79% | 69% | 10% | 3.46 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 67 | 248 / 0 / 0 | 0.7 | 506.5 | 0.49 | 1.60 | 12% | 12% | 0% | 2.67 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 883 | 565 / 318 / 216 | 0.7 | 461.4 | 2.38 | 3.71 | 89% | 77% | 13% | 3.81 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 529 | 569 / 0 / 6 | 0.7 | 482.2 | 1.19 | 1.60 | 80% | 65% | 14% | 3.60 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 66 | 294 / 0 / 0 | 0.7 | 513.9 | 0.57 | 1.50 | 12% | 10% | 2% | 2.53 |
| corner +x-y | 1.20 | 85.6 | 722 | 103 / 134 / 496 | 0.7 | 507.8 | 1.45 | 3.51 | 84% | 51% | 33% | 2.39 |

The last agent out (agent 5943, t100 518.2 s): last gangway straight -x+y (y wing) 2, exit door -x+y (y wall) 2. The gangway that cleared last: straight -x+y (y wing) 2 at 515.3 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.84 | 509.9 / 500.1 / 476.6 | 494.5 / 462.5 / 408.4 | 621737.6 | 1473870 | 0.219 |
| gangway | 1212 | 1112.9 | 6.84 | 509.3 / 493.6 / 425.9 | 494.5 / 462.5 / 408.4 | 620928.1 | 1331624 | 0.111 |
| walkway | 276 | 257.4 | 3.07 | 206.2 / 98.3 / 0.0 | 116.8 / 31.8 / 0.0 | 0.0 | 23155 | 0.927 |
| avenue | 912 | 858.9 | 1.63 | 209.7 / 0.0 / 0.0 | 159.3 / 0.0 / 0.0 | 0.0 | 88165 | 1.327 |
| exit | 32 | 3.2 | 0.00 | 492.9 / 489.7 / 441.3 | 241.5 / 216.5 / 125.9 | 809.5 | 1531 | 1.325 |
| concourse | 1116 | 1043.8 | 2.44 | 462.3 / 1.6 / 0.0 | 116.3 / 1.6 / 0.0 | 0.0 | 29395 | 1.195 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.62 | 454.4 / 442.3 / 428.2 | 445.8 / 442.3 / 424.3 | 602704.0 | 1738186 | 0.048 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -27.5 | -27.5 | gangway | 1.00 | 6.36 | 442.3 | 432.9 | 367.5 | 2253.1 | 0.015 |
| 2 | -28.5 | -27.5 | gangway | 1.00 | 6.20 | 443.2 | 436.0 | 368.0 | 2170.9 | 0.015 |
| 3 | -28.5 | -26.5 | gangway | 1.00 | 6.11 | 432.4 | 425.9 | 367.5 | 2156.5 | 0.018 |
| 4 | -27.5 | 26.5 | gangway | 1.00 | 5.89 | 440.9 | 429.0 | 374.5 | 2115.8 | 0.021 |
| 5 | -26.5 | -27.5 | gangway | 1.00 | 6.11 | 440.1 | 418.4 | 361.9 | 2100.0 | 0.021 |
| 6 | 26.5 | 28.5 | gangway | 1.00 | 6.00 | 430.8 | 417.3 | 366.6 | 2090.4 | 0.023 |
| 7 | 28.5 | -27.5 | gangway | 1.00 | 6.07 | 433.6 | 425.9 | 357.3 | 2085.1 | 0.022 |
| 8 | -26.5 | -28.5 | gangway | 1.00 | 6.01 | 432.4 | 410.3 | 351.0 | 2073.7 | 0.025 |
| 9 | -27.5 | -26.5 | gangway | 1.00 | 5.89 | 445.3 | 429.0 | 358.0 | 2063.4 | 0.017 |
| 10 | -26.5 | -26.5 | gangway | 1.00 | 5.92 | 451.4 | 441.5 | 361.4 | 2054.1 | 0.019 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -24.5 | -26.5 | seat row | 0.50 | 7.42 | 445.8 | 435.5 | 424.3 | 1487.9 | 0.012 |
| 2 | 24.5 | 26.5 | seat row | 0.50 | 7.34 | 432.0 | 427.3 | 417.5 | 1472.2 | 0.013 |
| 3 | -24.5 | 26.5 | seat row | 0.50 | 7.20 | 443.0 | 442.3 | 421.5 | 1458.5 | 0.017 |
| 4 | 26.5 | -24.5 | seat row | 0.50 | 7.30 | 433.4 | 431.0 | 413.8 | 1458.5 | 0.015 |
| 5 | 24.5 | -26.5 | seat row | 0.50 | 7.14 | 432.5 | 429.2 | 416.1 | 1440.3 | 0.016 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1672; agent-steps of seated agents on another row's clearway: 16549.

## Deposit check

Person-seconds deposited: 3214929.2, of them in excluded cells: 2873.678.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 273497 overlapping pair-steps: p99 0.0024, max 0.0521 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0024 max 0.0521; venue-geometry 3: p99 0.0011 max 0.0011 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 16 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.36 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 593 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
