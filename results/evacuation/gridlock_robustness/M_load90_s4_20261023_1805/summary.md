# Experiment `M_load90_s4`

**Task 5.11 stage 1 (gridlock robustness, default model, AMD 26.10.1): venue M, 90% load (seed 4)**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 14249 agents on 90% of the 15832 seats (spawnSeatedCrowd, seed 4), buffer N = 16384, 2905 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 1005951 evaluations, 42064 switches, 0 forced choices).
Capacity: **within design capacity** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `15aa31e8667e4a9417fde7884d907d1832c5e2d6`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-23T18:05:35, 106.8 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1158 | 202.5 |
| t90 | 2237 | 391.3 |
| t100 | 2905 | 508.1 |

t_p: the step by which ceil(p x 14249) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 735 | 0 | 39.7 | 438.3 | 19.5 | 25.5 | 50.4-60.3 |
| -x | 5.66 | 744 | 0 | 39.4 | 442.2 | 19.6 | 25.5 | 74.5-84.5 |
| +y | 5.66 | 737 | 0 | 39.7 | 439.0 | 19.6 | 25.5 | 56.5-66.5 |
| -y | 5.66 | 742 | 0 | 39.7 | 446.0 | 19.4 | 25.5 | 58.8-68.7 |
| door +x+y (y wall) 0 | 1.20 | 550 | 1016 | 4.9 | 458.3 | 60.6 | 85.3 | 16.6-26.6 |
| door +x+y (y wall) 1 | 1.20 | 548 | 610 | 4.9 | 472.9 | 58.5 | 85.3 | 20.8-30.8 |
| door +x+y (y wall) 2 | 1.20 | 256 | 164 | 4.9 | 508.1 | 25.4 | 80.2 | 7.9-17.8 |
| door +x+y (x wall) 0 | 1.20 | 544 | 993 | 4.9 | 475.2 | 57.8 | 85.3 | 11.0-21.0 |
| door +x+y (x wall) 1 | 1.20 | 542 | 595 | 4.9 | 475.0 | 57.6 | 80.2 | 9.3-19.2 |
| door +x+y (x wall) 2 | 1.20 | 286 | 160 | 4.9 | 506.9 | 28.5 | 85.3 | 10.3-20.3 |
| door +x+y (corner) | 1.20 | 76 | 0 | 79.6 | 491.8 | 9.2 | 70.2 | 289.8-299.8 |
| door -x+y (y wall) 0 | 1.20 | 543 | 1006 | 5.8 | 451.1 | 60.9 | 80.2 | 12.4-22.4 |
| door -x+y (y wall) 1 | 1.20 | 541 | 614 | 4.9 | 468.1 | 58.4 | 85.3 | 6.1-16.1 |
| door -x+y (y wall) 2 | 1.20 | 242 | 159 | 4.9 | 498.5 | 24.5 | 85.3 | 10.5-20.5 |
| door -x+y (x wall) 0 | 1.20 | 550 | 1007 | 4.9 | 461.6 | 60.2 | 85.3 | 23.3-33.2 |
| door -x+y (x wall) 1 | 1.20 | 542 | 609 | 4.9 | 465.6 | 58.8 | 90.3 | 28.0-38.0 |
| door -x+y (x wall) 2 | 1.20 | 295 | 159 | 4.9 | 498.8 | 29.9 | 80.2 | 10.0-19.9 |
| door -x+y (corner) | 1.20 | 100 | 0 | 63.7 | 488.7 | 11.8 | 80.2 | 73.6-83.6 |
| door -x-y (y wall) 0 | 1.20 | 558 | 1032 | 4.9 | 461.4 | 61.1 | 90.3 | 27.6-37.6 |
| door -x-y (y wall) 1 | 1.20 | 538 | 620 | 4.9 | 470.3 | 57.8 | 85.3 | 9.8-19.8 |
| door -x-y (y wall) 2 | 1.20 | 287 | 160 | 4.9 | 497.1 | 29.1 | 85.3 | 8.4-18.4 |
| door -x-y (x wall) 0 | 1.20 | 550 | 1017 | 4.9 | 450.7 | 61.7 | 90.3 | 25.5-35.5 |
| door -x-y (x wall) 1 | 1.20 | 566 | 600 | 4.9 | 478.5 | 59.7 | 85.3 | 14.0-24.0 |
| door -x-y (x wall) 2 | 1.20 | 240 | 165 | 4.9 | 489.2 | 24.8 | 85.3 | 10.5-20.5 |
| door -x-y (corner) | 1.20 | 106 | 0 | 64.9 | 500.2 | 12.2 | 70.2 | 275.8-285.8 |
| door +x-y (y wall) 0 | 1.20 | 549 | 1001 | 4.9 | 452.3 | 61.3 | 85.3 | 22.0-32.0 |
| door +x-y (y wall) 1 | 1.20 | 545 | 621 | 4.9 | 471.0 | 58.4 | 90.3 | 13.5-23.4 |
| door +x-y (y wall) 2 | 1.20 | 274 | 154 | 4.9 | 502.7 | 27.5 | 80.2 | 6.1-16.1 |
| door +x-y (x wall) 0 | 1.20 | 550 | 1007 | 4.9 | 460.5 | 60.3 | 80.2 | 13.3-23.3 |
| door +x-y (x wall) 1 | 1.20 | 545 | 620 | 4.9 | 468.2 | 58.8 | 90.3 | 16.4-26.4 |
| door +x-y (x wall) 2 | 1.20 | 262 | 160 | 4.9 | 491.5 | 26.9 | 80.2 | 7.9-17.8 |
| door +x-y (corner) | 1.20 | 106 | 0 | 56.5 | 481.7 | 12.5 | 60.2 | 244.9-254.8 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 735 | 5.2% | 18.3% |
| -x | avenue | 5.66 | 744 | 5.2% | 18.6% |
| +y | avenue | 5.66 | 737 | 5.2% | 18.4% |
| -y | avenue | 5.66 | 742 | 5.2% | 18.5% |
| door +x+y (y wall) 0 | door | 1.20 | 550 | 3.9% | 64.7% |
| door +x+y (y wall) 1 | door | 1.20 | 548 | 3.8% | 64.5% |
| door +x+y (y wall) 2 | door | 1.20 | 256 | 1.8% | 30.1% |
| door +x+y (x wall) 0 | door | 1.20 | 544 | 3.8% | 64.0% |
| door +x+y (x wall) 1 | door | 1.20 | 542 | 3.8% | 63.8% |
| door +x+y (x wall) 2 | door | 1.20 | 286 | 2.0% | 33.7% |
| door +x+y (corner) | door | 1.20 | 76 | 0.5% | 8.9% |
| door -x+y (y wall) 0 | door | 1.20 | 543 | 3.8% | 63.9% |
| door -x+y (y wall) 1 | door | 1.20 | 541 | 3.8% | 63.7% |
| door -x+y (y wall) 2 | door | 1.20 | 242 | 1.7% | 28.5% |
| door -x+y (x wall) 0 | door | 1.20 | 550 | 3.9% | 64.7% |
| door -x+y (x wall) 1 | door | 1.20 | 542 | 3.8% | 63.8% |
| door -x+y (x wall) 2 | door | 1.20 | 295 | 2.1% | 34.7% |
| door -x+y (corner) | door | 1.20 | 100 | 0.7% | 11.8% |
| door -x-y (y wall) 0 | door | 1.20 | 558 | 3.9% | 65.7% |
| door -x-y (y wall) 1 | door | 1.20 | 538 | 3.8% | 63.3% |
| door -x-y (y wall) 2 | door | 1.20 | 287 | 2.0% | 33.8% |
| door -x-y (x wall) 0 | door | 1.20 | 550 | 3.9% | 64.7% |
| door -x-y (x wall) 1 | door | 1.20 | 566 | 4.0% | 66.6% |
| door -x-y (x wall) 2 | door | 1.20 | 240 | 1.7% | 28.3% |
| door -x-y (corner) | door | 1.20 | 106 | 0.7% | 12.5% |
| door +x-y (y wall) 0 | door | 1.20 | 549 | 3.9% | 64.6% |
| door +x-y (y wall) 1 | door | 1.20 | 545 | 3.8% | 64.2% |
| door +x-y (y wall) 2 | door | 1.20 | 274 | 1.9% | 32.3% |
| door +x-y (x wall) 0 | door | 1.20 | 550 | 3.9% | 64.7% |
| door +x-y (x wall) 1 | door | 1.20 | 545 | 3.8% | 64.2% |
| door +x-y (x wall) 2 | door | 1.20 | 262 | 1.8% | 30.8% |
| door +x-y (corner) | door | 1.20 | 106 | 0.7% | 12.5% |
| **doors (28)** | door | 33.60 | 11291 | 79.2% | |
| **avenues (4)** | avenue | 22.64 | 2958 | 20.8% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 508.1 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 35.8%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 854 | 6.0% | 854 | 6.0% |
| straight +x+y (y wing) 1 | straight | yes | 553 | 3.9% | 548 | 3.8% |
| straight +x+y (y wing) 2 | straight | yes | 256 | 1.8% | 256 | 1.8% |
| straight +x+y (x wing) 0 | straight | yes | 839 | 5.9% | 839 | 5.9% |
| straight +x+y (x wing) 1 | straight | yes | 546 | 3.8% | 543 | 3.8% |
| straight +x+y (x wing) 2 | straight | yes | 286 | 2.0% | 286 | 2.0% |
| corner +x+y | corner | yes | 728 | 5.1% | 212 | 1.5% |
| straight -x+y (y wing) 0 | straight | yes | 848 | 6.0% | 848 | 6.0% |
| straight -x+y (y wing) 1 | straight | yes | 549 | 3.9% | 543 | 3.8% |
| straight -x+y (y wing) 2 | straight | yes | 240 | 1.7% | 240 | 1.7% |
| straight -x+y (x wing) 0 | straight | yes | 854 | 6.0% | 854 | 6.0% |
| straight -x+y (x wing) 1 | straight | yes | 555 | 3.9% | 548 | 3.8% |
| straight -x+y (x wing) 2 | straight | yes | 289 | 2.0% | 289 | 2.0% |
| corner -x+y | corner | yes | 735 | 5.2% | 232 | 1.6% |
| straight -x-y (y wing) 0 | straight | yes | 872 | 6.1% | 872 | 6.1% |
| straight -x-y (y wing) 1 | straight | yes | 553 | 3.9% | 546 | 3.8% |
| straight -x-y (y wing) 2 | straight | yes | 280 | 2.0% | 279 | 2.0% |
| straight -x-y (x wing) 0 | straight | yes | 853 | 6.0% | 853 | 6.0% |
| straight -x-y (x wing) 1 | straight | yes | 571 | 4.0% | 567 | 4.0% |
| straight -x-y (x wing) 2 | straight | yes | 239 | 1.7% | 239 | 1.7% |
| corner -x-y | corner | yes | 716 | 5.0% | 238 | 1.7% |
| straight +x-y (y wing) 0 | straight | yes | 846 | 5.9% | 846 | 5.9% |
| straight +x-y (y wing) 1 | straight | yes | 553 | 3.9% | 547 | 3.8% |
| straight +x-y (y wing) 2 | straight | yes | 272 | 1.9% | 272 | 1.9% |
| straight +x-y (x wing) 0 | straight | yes | 847 | 5.9% | 847 | 5.9% |
| straight +x-y (x wing) 1 | straight | yes | 552 | 3.9% | 546 | 3.8% |
| straight +x-y (x wing) 2 | straight | yes | 261 | 1.8% | 261 | 1.8% |
| corner +x-y | corner | yes | 742 | 5.2% | 244 | 1.7% |
| **straight (24)** | | | 13368 | | 13323 | 93.5% |
| **corner (4)** | | | 2921 | | 926 | 6.5% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 735 | 39.7 | 438.3 | 0.23 | 0.31 | 0.0% |
| -x | 744 | 39.4 | 442.2 | 0.23 | 0.31 | 0.0% |
| +y | 737 | 39.7 | 439.0 | 0.23 | 0.31 | 0.0% |
| -y | 742 | 39.7 | 446.0 | 0.23 | 0.31 | 0.0% |
| door +x+y (y wall) 0 | 550 | 4.9 | 458.3 | 0.73 | 1.02 | 37.0% |
| door +x+y (y wall) 1 | 548 | 4.9 | 472.9 | 0.70 | 1.02 | 29.2% |
| door +x+y (y wall) 2 | 256 | 4.9 | 508.1 | 0.30 | 0.96 | 3.9% |
| door +x+y (x wall) 0 | 544 | 4.9 | 475.2 | 0.69 | 1.02 | 33.3% |
| door +x+y (x wall) 1 | 542 | 4.9 | 475.0 | 0.69 | 0.96 | 16.7% |
| door +x+y (x wall) 2 | 286 | 4.9 | 506.9 | 0.34 | 1.02 | 3.9% |
| door +x+y (corner) | 76 | 79.6 | 491.8 | 0.11 | 0.84 | 0.0% |
| door -x+y (y wall) 0 | 543 | 5.8 | 451.1 | 0.73 | 0.96 | 34.8% |
| door -x+y (y wall) 1 | 541 | 4.9 | 468.1 | 0.70 | 1.02 | 27.7% |
| door -x+y (y wall) 2 | 242 | 4.9 | 498.5 | 0.29 | 1.02 | 4.0% |
| door -x+y (x wall) 0 | 550 | 4.9 | 461.6 | 0.72 | 1.02 | 34.0% |
| door -x+y (x wall) 1 | 542 | 4.9 | 465.6 | 0.70 | 1.08 | 25.5% |
| door -x+y (x wall) 2 | 295 | 4.9 | 498.8 | 0.36 | 0.96 | 2.0% |
| door -x+y (corner) | 100 | 63.7 | 488.7 | 0.14 | 0.96 | 2.3% |
| door -x-y (y wall) 0 | 558 | 4.9 | 461.4 | 0.73 | 1.08 | 31.9% |
| door -x-y (y wall) 1 | 538 | 4.9 | 470.3 | 0.69 | 1.02 | 20.8% |
| door -x-y (y wall) 2 | 287 | 4.9 | 497.1 | 0.35 | 1.02 | 4.0% |
| door -x-y (x wall) 0 | 550 | 4.9 | 450.7 | 0.74 | 1.08 | 37.0% |
| door -x-y (x wall) 1 | 566 | 4.9 | 478.5 | 0.71 | 1.02 | 33.3% |
| door -x-y (x wall) 2 | 240 | 4.9 | 489.2 | 0.30 | 1.02 | 6.0% |
| door -x-y (corner) | 106 | 64.9 | 500.2 | 0.15 | 0.84 | 0.0% |
| door +x-y (y wall) 0 | 549 | 4.9 | 452.3 | 0.73 | 1.02 | 34.8% |
| door +x-y (y wall) 1 | 545 | 4.9 | 471.0 | 0.70 | 1.08 | 20.8% |
| door +x-y (y wall) 2 | 274 | 4.9 | 502.7 | 0.33 | 0.96 | 5.9% |
| door +x-y (x wall) 0 | 550 | 4.9 | 460.5 | 0.72 | 0.96 | 34.0% |
| door +x-y (x wall) 1 | 545 | 4.9 | 468.2 | 0.70 | 1.08 | 31.9% |
| door +x-y (x wall) 2 | 262 | 4.9 | 491.5 | 0.32 | 0.96 | 6.0% |
| door +x-y (corner) | 106 | 56.5 | 481.7 | 0.15 | 0.72 | 0.0% |

Mean flow / w J averaged over the doors 0.52, over the avenues 0.23.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 854 | 550 / 304 / 195 | 0.7 | 455.3 | 2.31 | 3.71 | 89% | 76% | 13% | 3.75 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 509 | 548 / 0 / 13 | 0.7 | 470.0 | 1.20 | 1.60 | 75% | 65% | 10% | 3.48 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 66 | 256 / 0 / 0 | 0.7 | 505.1 | 0.51 | 1.50 | 12% | 10% | 2% | 2.63 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 839 | 543 / 296 / 195 | 0.7 | 445.0 | 2.33 | 3.61 | 89% | 76% | 13% | 3.85 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 488 | 543 / 0 / 8 | 0.7 | 472.1 | 1.17 | 1.60 | 75% | 60% | 15% | 3.47 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 63 | 286 / 0 / 0 | 0.7 | 503.9 | 0.57 | 1.40 | 12% | 10% | 2% | 2.47 |
| corner +x+y | 1.20 | 85.6 | 719 | 76 / 136 / 528 | 0.7 | 499.0 | 1.48 | 4.01 | 82% | 57% | 25% | 2.49 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 848 | 543 / 305 / 218 | 0.7 | 448.1 | 2.38 | 3.91 | 91% | 78% | 13% | 3.74 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 510 | 543 / 0 / 14 | 0.7 | 465.1 | 1.20 | 1.71 | 83% | 66% | 17% | 3.37 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 61 | 240 / 0 / 0 | 0.7 | 495.5 | 0.48 | 1.60 | 10% | 10% | 0% | 2.63 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 854 | 550 / 304 / 192 | 0.7 | 458.6 | 2.28 | 3.61 | 91% | 78% | 13% | 3.70 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 498 | 548 / 0 / 9 | 0.7 | 462.6 | 1.21 | 1.71 | 74% | 60% | 15% | 3.47 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 60 | 289 / 0 / 0 | 0.7 | 495.9 | 0.58 | 1.50 | 10% | 10% | 0% | 2.54 |
| corner -x+y | 1.20 | 85.6 | 723 | 100 / 132 / 514 | 0.7 | 489.9 | 1.52 | 3.71 | 82% | 56% | 26% | 2.47 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 872 | 558 / 314 / 191 | 0.7 | 458.4 | 2.32 | 3.71 | 91% | 78% | 13% | 3.64 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 515 | 546 / 0 / 10 | 0.7 | 467.4 | 1.19 | 1.91 | 81% | 62% | 19% | 3.31 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 65 | 279 / 0 / 1 | 0.7 | 494.1 | 0.57 | 1.40 | 12% | 10% | 2% | 2.64 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 853 | 550 / 303 / 186 | 0.7 | 447.8 | 2.32 | 3.91 | 89% | 78% | 11% | 3.86 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 516 | 567 / 0 / 5 | 0.7 | 475.6 | 1.20 | 1.81 | 77% | 67% | 10% | 3.55 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 65 | 239 / 0 / 0 | 0.7 | 486.2 | 0.49 | 1.60 | 10% | 10% | 0% | 2.73 |
| corner -x-y | 1.20 | 85.6 | 708 | 106 / 132 / 486 | 0.7 | 496.4 | 1.46 | 3.21 | 84% | 54% | 30% | 2.37 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 846 | 549 / 297 / 196 | 0.7 | 449.3 | 2.32 | 3.71 | 87% | 76% | 11% | 3.85 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 509 | 547 / 0 / 6 | 0.7 | 468.1 | 1.18 | 1.71 | 81% | 66% | 15% | 3.43 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 58 | 272 / 0 / 0 | 0.7 | 499.7 | 0.54 | 1.50 | 10% | 8% | 2% | 2.64 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 847 | 550 / 298 / 168 | 0.7 | 457.6 | 2.22 | 3.31 | 89% | 78% | 11% | 3.70 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 508 | 546 / 0 / 9 | 0.7 | 465.3 | 1.19 | 1.81 | 81% | 66% | 15% | 3.46 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 61 | 261 / 0 / 0 | 0.7 | 488.5 | 0.53 | 1.60 | 12% | 8% | 4% | 2.48 |
| corner +x-y | 1.20 | 85.6 | 734 | 106 / 138 / 505 | 0.7 | 493.8 | 1.52 | 3.91 | 84% | 52% | 32% | 2.41 |

The last agent out (agent 447, t100 508.1 s): last gangway straight +x+y (y wing) 2, exit door +x+y (y wall) 2. The gangway that cleared last: straight +x+y (y wing) 2 at 505.1 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.93 | 498.7 / 487.3 / 460.9 | 481.7 / 452.0 / 398.6 | 560811.6 | 1407661 | 0.222 |
| gangway | 1212 | 1112.9 | 6.93 | 498.1 / 482.4 / 409.3 | 481.7 / 452.0 / 398.6 | 560025.4 | 1270036 | 0.113 |
| walkway | 276 | 257.4 | 3.15 | 188.2 / 118.8 / 0.0 | 124.4 / 26.8 / 0.0 | 0.0 | 22722 | 0.911 |
| avenue | 912 | 858.9 | 1.84 | 202.9 / 0.0 / 0.0 | 161.1 / 0.0 / 0.0 | 0.0 | 84925 | 1.327 |
| exit | 32 | 3.2 | 0.00 | 479.1 / 475.4 / 429.2 | 239.8 / 213.7 / 124.9 | 786.3 | 1493 | 1.322 |
| concourse | 1116 | 1043.8 | 1.99 | 444.8 / 0.0 / 0.0 | 111.6 / 0.0 / 0.0 | 0.0 | 28485 | 1.195 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.57 | 428.5 / 421.9 / 412.3 | 424.5 / 421.9 / 408.4 | 547110.0 | 1600569 | 0.051 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 26.5 | 28.5 | gangway | 1.00 | 6.24 | 417.5 | 405.3 | 363.3 | 2155.3 | 0.021 |
| 2 | 27.5 | 27.5 | gangway | 1.00 | 5.98 | 420.5 | 410.7 | 348.1 | 2031.3 | 0.015 |
| 3 | 27.5 | -28.5 | gangway | 1.00 | 5.92 | 426.2 | 421.5 | 350.9 | 2012.4 | 0.020 |
| 4 | 26.5 | 27.5 | gangway | 1.00 | 5.89 | 415.2 | 411.7 | 348.6 | 2012.3 | 0.021 |
| 5 | -27.5 | 27.5 | gangway | 1.00 | 6.06 | 414.5 | 405.4 | 346.1 | 2002.2 | 0.018 |
| 6 | 26.5 | -28.5 | gangway | 1.00 | 6.16 | 422.9 | 406.0 | 339.3 | 1993.4 | 0.022 |
| 7 | 27.5 | -27.5 | gangway | 1.00 | 5.73 | 425.5 | 417.2 | 361.5 | 1989.0 | 0.018 |
| 8 | 26.5 | 26.5 | gangway | 1.00 | 5.78 | 430.1 | 420.5 | 357.2 | 1988.2 | 0.022 |
| 9 | -27.5 | -28.5 | gangway | 1.00 | 5.87 | 426.8 | 417.3 | 348.8 | 1943.3 | 0.022 |
| 10 | -28.5 | 27.5 | gangway | 1.00 | 6.02 | 406.8 | 397.7 | 329.3 | 1928.5 | 0.021 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 24.5 | 26.5 | seat row | 0.50 | 7.35 | 424.5 | 421.9 | 408.4 | 1392.4 | 0.015 |
| 2 | -24.5 | 26.5 | seat row | 0.50 | 7.24 | 413.8 | 410.3 | 396.5 | 1391.1 | 0.016 |
| 3 | 24.5 | -26.5 | seat row | 0.50 | 7.19 | 418.9 | 416.1 | 402.6 | 1390.7 | 0.014 |
| 4 | 26.5 | 24.5 | seat row | 0.50 | 7.20 | 421.7 | 418.0 | 399.5 | 1389.4 | 0.013 |
| 5 | -24.5 | -26.5 | seat row | 0.50 | 7.24 | 418.7 | 412.6 | 395.5 | 1376.7 | 0.016 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1542; agent-steps of seated agents on another row's clearway: 14619.

## Deposit check

Person-seconds deposited: 3011008.8, of them in excluded cells: 2779.250.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 214975 overlapping pair-steps: p99 0.0031, max 0.0597 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0031 max 0.0597; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 12 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.29 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 512 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
