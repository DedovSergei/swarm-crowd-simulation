# Experiment `venue_M_load100_gpu_c1`

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 15832 agents on 100% of the 15832 seats (spawnSeatedCrowd, seed 1337), buffer N = 16384, 2496 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 964825 evaluations, 42797 switches, 0 forced choices).
Capacity: **within design capacity** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `372a5c19c97779f851bd5737b102b7136c2f09ce`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-12T19:23:50, 458.0 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1021 | 178.6 |
| t90 | 1916 | 335.1 |
| t100 | 2496 | 436.6 |

t_p: the step by which ceil(p x 15832) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 759 | 0 | 39.7 | 382.0 | 23.5 | 25.5 | 50.2-60.2 |
| -x | 5.66 | 757 | 0 | 39.7 | 386.4 | 23.1 | 25.5 | 50.0-60.0 |
| +y | 5.66 | 759 | 0 | 39.7 | 385.5 | 23.3 | 25.5 | 49.1-59.1 |
| -y | 5.66 | 760 | 0 | 39.7 | 382.3 | 23.5 | 25.5 | 49.1-59.1 |
| door +x+y (y wall) 0 | 1.20 | 624 | 1121 | 4.9 | 387.1 | 81.6 | 105.3 | 18.9-28.9 |
| door +x+y (y wall) 1 | 1.20 | 598 | 680 | 4.9 | 403.5 | 75.0 | 105.3 | 29.0-39.0 |
| door +x+y (y wall) 2 | 1.20 | 307 | 178 | 4.9 | 428.0 | 36.3 | 105.3 | 13.3-23.3 |
| door +x+y (x wall) 0 | 1.20 | 620 | 1121 | 4.9 | 399.3 | 78.6 | 110.3 | 34.3-44.3 |
| door +x+y (x wall) 1 | 1.20 | 613 | 680 | 4.9 | 398.4 | 77.8 | 105.3 | 27.8-37.8 |
| door +x+y (x wall) 2 | 1.20 | 301 | 178 | 4.9 | 426.9 | 35.6 | 110.3 | 12.9-22.9 |
| door +x+y (corner) | 1.20 | 135 | 0 | 53.3 | 405.6 | 19.2 | 90.3 | 53.0-63.0 |
| door -x+y (y wall) 0 | 1.20 | 630 | 1121 | 4.9 | 420.0 | 75.9 | 105.3 | 25.0-35.0 |
| door -x+y (y wall) 1 | 1.20 | 600 | 680 | 4.9 | 412.4 | 73.6 | 105.3 | 19.9-29.9 |
| door -x+y (y wall) 2 | 1.20 | 291 | 178 | 4.9 | 426.6 | 34.5 | 110.3 | 17.0-26.9 |
| door -x+y (x wall) 0 | 1.20 | 636 | 1121 | 4.9 | 402.5 | 80.0 | 110.3 | 30.6-40.6 |
| door -x+y (x wall) 1 | 1.20 | 602 | 680 | 4.9 | 412.1 | 73.9 | 105.3 | 19.9-29.9 |
| door -x+y (x wall) 2 | 1.20 | 327 | 178 | 4.9 | 432.0 | 38.3 | 105.3 | 13.3-23.3 |
| door -x+y (corner) | 1.20 | 113 | 0 | 57.0 | 436.6 | 14.9 | 115.3 | 286.0-295.9 |
| door -x-y (y wall) 0 | 1.20 | 636 | 1121 | 4.9 | 402.6 | 79.9 | 115.3 | 28.7-38.7 |
| door -x-y (y wall) 1 | 1.20 | 602 | 680 | 4.9 | 422.7 | 72.0 | 105.3 | 17.8-27.8 |
| door -x-y (y wall) 2 | 1.20 | 279 | 178 | 4.9 | 423.3 | 33.3 | 105.3 | 24.7-34.6 |
| door -x-y (x wall) 0 | 1.20 | 631 | 1121 | 4.9 | 403.0 | 79.2 | 110.3 | 26.1-36.0 |
| door -x-y (x wall) 1 | 1.20 | 614 | 680 | 4.9 | 410.3 | 75.7 | 110.3 | 25.0-35.0 |
| door -x-y (x wall) 2 | 1.20 | 274 | 178 | 4.9 | 428.7 | 32.3 | 100.3 | 7.9-17.8 |
| door -x-y (corner) | 1.20 | 164 | 0 | 57.2 | 413.5 | 23.0 | 110.3 | 234.5-244.5 |
| door +x-y (y wall) 0 | 1.20 | 625 | 1121 | 4.9 | 392.8 | 80.5 | 105.3 | 128.2-138.2 |
| door +x-y (y wall) 1 | 1.20 | 613 | 680 | 4.9 | 400.4 | 77.5 | 105.3 | 19.9-29.9 |
| door +x-y (y wall) 2 | 1.20 | 280 | 178 | 4.9 | 417.9 | 33.9 | 105.3 | 13.3-23.3 |
| door +x-y (x wall) 0 | 1.20 | 625 | 1121 | 4.9 | 384.1 | 82.4 | 110.3 | 23.8-33.8 |
| door +x-y (x wall) 1 | 1.20 | 606 | 680 | 4.9 | 399.1 | 76.8 | 105.3 | 18.9-28.9 |
| door +x-y (x wall) 2 | 1.20 | 315 | 178 | 4.9 | 419.3 | 38.0 | 105.3 | 13.3-23.3 |
| door +x-y (corner) | 1.20 | 136 | 0 | 60.0 | 412.1 | 19.3 | 110.3 | 244.0-254.0 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 759 | 4.8% | 22.0% |
| -x | avenue | 5.66 | 757 | 4.8% | 22.0% |
| +y | avenue | 5.66 | 759 | 4.8% | 22.0% |
| -y | avenue | 5.66 | 760 | 4.8% | 22.1% |
| door +x+y (y wall) 0 | door | 1.20 | 624 | 3.9% | 85.5% |
| door +x+y (y wall) 1 | door | 1.20 | 598 | 3.8% | 81.9% |
| door +x+y (y wall) 2 | door | 1.20 | 307 | 1.9% | 42.1% |
| door +x+y (x wall) 0 | door | 1.20 | 620 | 3.9% | 84.9% |
| door +x+y (x wall) 1 | door | 1.20 | 613 | 3.9% | 84.0% |
| door +x+y (x wall) 2 | door | 1.20 | 301 | 1.9% | 41.2% |
| door +x+y (corner) | door | 1.20 | 135 | 0.9% | 18.5% |
| door -x+y (y wall) 0 | door | 1.20 | 630 | 4.0% | 86.3% |
| door -x+y (y wall) 1 | door | 1.20 | 600 | 3.8% | 82.2% |
| door -x+y (y wall) 2 | door | 1.20 | 291 | 1.8% | 39.9% |
| door -x+y (x wall) 0 | door | 1.20 | 636 | 4.0% | 87.1% |
| door -x+y (x wall) 1 | door | 1.20 | 602 | 3.8% | 82.5% |
| door -x+y (x wall) 2 | door | 1.20 | 327 | 2.1% | 44.8% |
| door -x+y (corner) | door | 1.20 | 113 | 0.7% | 15.5% |
| door -x-y (y wall) 0 | door | 1.20 | 636 | 4.0% | 87.1% |
| door -x-y (y wall) 1 | door | 1.20 | 602 | 3.8% | 82.5% |
| door -x-y (y wall) 2 | door | 1.20 | 279 | 1.8% | 38.2% |
| door -x-y (x wall) 0 | door | 1.20 | 631 | 4.0% | 86.4% |
| door -x-y (x wall) 1 | door | 1.20 | 614 | 3.9% | 84.1% |
| door -x-y (x wall) 2 | door | 1.20 | 274 | 1.7% | 37.5% |
| door -x-y (corner) | door | 1.20 | 164 | 1.0% | 22.5% |
| door +x-y (y wall) 0 | door | 1.20 | 625 | 3.9% | 85.6% |
| door +x-y (y wall) 1 | door | 1.20 | 613 | 3.9% | 84.0% |
| door +x-y (y wall) 2 | door | 1.20 | 280 | 1.8% | 38.4% |
| door +x-y (x wall) 0 | door | 1.20 | 625 | 3.9% | 85.6% |
| door +x-y (x wall) 1 | door | 1.20 | 606 | 3.8% | 83.0% |
| door +x-y (x wall) 2 | door | 1.20 | 315 | 2.0% | 43.2% |
| door +x-y (corner) | door | 1.20 | 136 | 0.9% | 18.6% |
| **doors (28)** | door | 33.60 | 12797 | 80.8% | |
| **avenues (4)** | avenue | 22.64 | 3035 | 19.2% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 436.6 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 46.3%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 942 | 5.9% | 942 | 5.9% |
| straight +x+y (y wing) 1 | straight | yes | 604 | 3.8% | 598 | 3.8% |
| straight +x+y (y wing) 2 | straight | yes | 307 | 1.9% | 307 | 1.9% |
| straight +x+y (x wing) 0 | straight | yes | 937 | 5.9% | 937 | 5.9% |
| straight +x+y (x wing) 1 | straight | yes | 622 | 3.9% | 614 | 3.9% |
| straight +x+y (x wing) 2 | straight | yes | 300 | 1.9% | 300 | 1.9% |
| corner +x+y | corner | yes | 811 | 5.1% | 260 | 1.6% |
| straight -x+y (y wing) 0 | straight | yes | 954 | 6.0% | 954 | 6.0% |
| straight -x+y (y wing) 1 | straight | yes | 611 | 3.9% | 603 | 3.8% |
| straight -x+y (y wing) 2 | straight | yes | 289 | 1.8% | 289 | 1.8% |
| straight -x+y (x wing) 0 | straight | yes | 951 | 6.0% | 951 | 6.0% |
| straight -x+y (x wing) 1 | straight | yes | 616 | 3.9% | 610 | 3.9% |
| straight -x+y (x wing) 2 | straight | yes | 318 | 2.0% | 318 | 2.0% |
| corner -x+y | corner | yes | 786 | 5.0% | 233 | 1.5% |
| straight -x-y (y wing) 0 | straight | yes | 950 | 6.0% | 950 | 6.0% |
| straight -x-y (y wing) 1 | straight | yes | 612 | 3.9% | 607 | 3.8% |
| straight -x-y (y wing) 2 | straight | yes | 274 | 1.7% | 274 | 1.7% |
| straight -x-y (x wing) 0 | straight | yes | 957 | 6.0% | 957 | 6.0% |
| straight -x-y (x wing) 1 | straight | yes | 629 | 4.0% | 620 | 3.9% |
| straight -x-y (x wing) 2 | straight | yes | 267 | 1.7% | 267 | 1.7% |
| corner -x-y | corner | yes | 790 | 5.0% | 283 | 1.8% |
| straight +x-y (y wing) 0 | straight | yes | 944 | 6.0% | 944 | 6.0% |
| straight +x-y (y wing) 1 | straight | yes | 619 | 3.9% | 613 | 3.9% |
| straight +x-y (y wing) 2 | straight | yes | 277 | 1.7% | 277 | 1.7% |
| straight +x-y (x wing) 0 | straight | yes | 940 | 5.9% | 940 | 5.9% |
| straight +x-y (x wing) 1 | straight | yes | 621 | 3.9% | 614 | 3.9% |
| straight +x-y (x wing) 2 | straight | yes | 306 | 1.9% | 306 | 1.9% |
| corner +x-y | corner | yes | 795 | 5.0% | 264 | 1.7% |
| **straight (24)** | | | 14847 | | 14792 | 93.4% |
| **corner (4)** | | | 3182 | | 1040 | 6.6% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 759 | 39.7 | 382.0 | 0.28 | 0.31 | 0.0% |
| -x | 757 | 39.7 | 386.4 | 0.28 | 0.31 | 0.0% |
| +y | 759 | 39.7 | 385.5 | 0.28 | 0.31 | 0.0% |
| -y | 760 | 39.7 | 382.3 | 0.28 | 0.31 | 0.0% |
| door +x+y (y wall) 0 | 624 | 4.9 | 387.1 | 0.98 | 1.26 | 82.1% |
| door +x+y (y wall) 1 | 598 | 4.9 | 403.5 | 0.90 | 1.26 | 65.9% |
| door +x+y (y wall) 2 | 307 | 4.9 | 428.0 | 0.43 | 1.26 | 16.3% |
| door +x+y (x wall) 0 | 620 | 4.9 | 399.3 | 0.94 | 1.32 | 78.0% |
| door +x+y (x wall) 1 | 613 | 4.9 | 398.4 | 0.93 | 1.26 | 72.5% |
| door +x+y (x wall) 2 | 301 | 4.9 | 426.9 | 0.43 | 1.32 | 16.3% |
| door +x+y (corner) | 135 | 53.3 | 405.6 | 0.23 | 1.08 | 2.8% |
| door -x+y (y wall) 0 | 630 | 4.9 | 420.0 | 0.91 | 1.26 | 74.4% |
| door -x+y (y wall) 1 | 600 | 4.9 | 412.4 | 0.88 | 1.26 | 71.4% |
| door -x+y (y wall) 2 | 291 | 4.9 | 426.6 | 0.41 | 1.32 | 11.6% |
| door -x+y (x wall) 0 | 636 | 4.9 | 402.5 | 0.96 | 1.32 | 78.0% |
| door -x+y (x wall) 1 | 602 | 4.9 | 412.1 | 0.88 | 1.26 | 64.3% |
| door -x+y (x wall) 2 | 327 | 4.9 | 432.0 | 0.46 | 1.26 | 15.9% |
| door -x+y (corner) | 113 | 57.0 | 436.6 | 0.18 | 1.38 | 5.1% |
| door -x-y (y wall) 0 | 636 | 4.9 | 402.6 | 0.96 | 1.38 | 78.0% |
| door -x-y (y wall) 1 | 602 | 4.9 | 422.7 | 0.86 | 1.26 | 67.4% |
| door -x-y (y wall) 2 | 279 | 4.9 | 423.3 | 0.40 | 1.26 | 11.6% |
| door -x-y (x wall) 0 | 631 | 4.9 | 403.0 | 0.95 | 1.32 | 78.0% |
| door -x-y (x wall) 1 | 614 | 4.9 | 410.3 | 0.91 | 1.32 | 66.7% |
| door -x-y (x wall) 2 | 274 | 4.9 | 428.7 | 0.39 | 1.20 | 11.6% |
| door -x-y (corner) | 164 | 57.2 | 413.5 | 0.28 | 1.32 | 13.5% |
| door +x-y (y wall) 0 | 625 | 4.9 | 392.8 | 0.96 | 1.26 | 80.0% |
| door +x-y (y wall) 1 | 613 | 4.9 | 400.4 | 0.93 | 1.26 | 73.2% |
| door +x-y (y wall) 2 | 280 | 4.9 | 417.9 | 0.41 | 1.26 | 11.9% |
| door +x-y (x wall) 0 | 625 | 4.9 | 384.1 | 0.99 | 1.32 | 82.1% |
| door +x-y (x wall) 1 | 606 | 4.9 | 399.1 | 0.92 | 1.26 | 70.7% |
| door +x-y (x wall) 2 | 315 | 4.9 | 419.3 | 0.45 | 1.26 | 14.0% |
| door +x-y (corner) | 136 | 60.0 | 412.1 | 0.23 | 1.32 | 8.3% |

Mean flow / w J averaged over the doors 0.68, over the avenues 0.28.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 942 | 624 / 318 / 187 | 0.7 | 384.1 | 2.94 | 5.12 | 77% | 77% | 0% | 4.50 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 566 | 598 / 0 / 7 | 0.7 | 400.5 | 1.51 | 2.11 | 78% | 66% | 12% | 3.63 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 70 | 307 / 0 / 0 | 0.7 | 425.0 | 0.72 | 2.01 | 12% | 12% | 0% | 3.08 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 937 | 620 / 317 / 195 | 0.7 | 396.3 | 2.86 | 4.61 | 88% | 78% | 10% | 4.06 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 571 | 614 / 0 / 11 | 0.7 | 395.5 | 1.58 | 2.11 | 78% | 68% | 10% | 3.71 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 70 | 300 / 0 / 0 | 0.7 | 424.0 | 0.71 | 2.11 | 12% | 12% | 0% | 3.03 |
| corner +x+y | 1.20 | 85.6 | 802 | 135 / 125 / 560 | 0.7 | 418.9 | 1.96 | 5.22 | 81% | 56% | 26% | 2.47 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 954 | 629 / 326 / 224 | 0.7 | 392.8 | 3.01 | 4.91 | 88% | 78% | 10% | 4.05 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 570 | 603 / 0 / 8 | 0.7 | 409.5 | 1.49 | 2.11 | 81% | 64% | 17% | 3.53 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 70 | 289 / 0 / 0 | 0.7 | 423.6 | 0.68 | 2.11 | 12% | 12% | 0% | 2.93 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 951 | 636 / 315 / 177 | 0.7 | 399.5 | 2.83 | 4.91 | 85% | 76% | 10% | 4.07 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 569 | 610 / 0 / 11 | 0.7 | 409.1 | 1.52 | 2.11 | 71% | 64% | 7% | 3.83 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 69 | 318 / 0 / 0 | 0.7 | 429.0 | 0.74 | 1.91 | 11% | 11% | 0% | 2.95 |
| corner -x+y | 1.20 | 85.6 | 775 | 114 / 119 / 560 | 0.7 | 432.7 | 1.83 | 4.91 | 80% | 64% | 16% | 2.59 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 950 | 636 / 314 / 168 | 0.7 | 399.7 | 2.80 | 4.61 | 88% | 76% | 12% | 4.00 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 568 | 607 / 0 / 12 | 0.7 | 419.8 | 1.48 | 2.21 | 67% | 63% | 5% | 3.88 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 69 | 274 / 0 / 0 | 0.7 | 420.3 | 0.65 | 1.91 | 12% | 12% | 0% | 3.00 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 957 | 631 / 326 / 199 | 0.7 | 400.0 | 2.89 | 4.81 | 88% | 76% | 12% | 3.96 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 567 | 620 / 0 / 13 | 0.7 | 407.4 | 1.56 | 2.21 | 71% | 63% | 7% | 3.81 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 69 | 267 / 0 / 0 | 0.7 | 425.7 | 0.63 | 1.91 | 12% | 12% | 0% | 3.06 |
| corner -x-y | 1.20 | 85.6 | 778 | 165 / 118 / 519 | 0.7 | 419.6 | 1.91 | 4.61 | 81% | 65% | 16% | 2.60 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 944 | 625 / 319 / 194 | 0.7 | 389.9 | 2.92 | 4.41 | 85% | 78% | 8% | 4.12 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 575 | 613 / 0 / 7 | 0.7 | 397.4 | 1.56 | 2.01 | 80% | 68% | 12% | 3.58 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 70 | 277 / 0 / 0 | 0.7 | 414.9 | 0.67 | 1.91 | 12% | 12% | 0% | 2.94 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 940 | 625 / 316 / 172 | 0.7 | 381.1 | 2.92 | 4.41 | 85% | 79% | 5% | 4.23 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 574 | 614 / 0 / 7 | 0.7 | 396.2 | 1.57 | 2.11 | 78% | 70% | 8% | 3.68 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 69 | 306 / 0 / 0 | 0.7 | 416.3 | 0.74 | 1.91 | 12% | 12% | 0% | 3.03 |
| corner +x-y | 1.20 | 85.6 | 786 | 140 / 124 / 536 | 0.7 | 410.3 | 1.95 | 5.52 | 83% | 57% | 26% | 2.49 |

The last agent out (agent 4341, t100 436.6 s): last gangway corner -x+y, exit door -x+y (corner). The gangway that cleared last: corner -x+y at 432.7 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.84 | 432.7 / 414.2 / 398.1 | 417.7 / 396.5 / 325.7 | 504771.0 | 1309662 | 0.259 |
| gangway | 1212 | 1112.9 | 6.84 | 431.0 / 410.5 / 340.7 | 417.7 / 396.5 / 325.7 | 503873.8 | 1161430 | 0.140 |
| walkway | 276 | 257.4 | 3.45 | 267.4 / 121.0 / 0.0 | 170.9 / 48.1 / 0.0 | 0.0 | 26890 | 0.776 |
| avenue | 912 | 858.9 | 1.81 | 328.3 / 0.0 / 0.0 | 249.4 / 0.0 / 0.0 | 0.0 | 87171 | 1.326 |
| exit | 32 | 3.2 | 0.00 | 406.0 / 403.7 / 376.4 | 255.7 / 231.4 / 138.2 | 897.2 | 1638 | 1.318 |
| concourse | 1116 | 1043.8 | 2.39 | 406.3 / 1.6 / 0.0 | 252.0 / 1.2 / 0.0 | 0.0 | 32533 | 1.193 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.58 | 368.7 / 353.7 / 349.8 | 356.6 / 352.8 / 346.7 | 558736.5 | 1578072 | 0.057 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -28.5 | 26.5 | gangway | 1.00 | 6.09 | 346.7 | 340.2 | 301.5 | 1738.0 | 0.026 |
| 2 | -26.5 | -28.5 | gangway | 1.00 | 5.87 | 355.9 | 347.2 | 309.8 | 1737.6 | 0.026 |
| 3 | -29.5 | 26.5 | gangway | 1.00 | 6.42 | 351.4 | 323.4 | 265.0 | 1607.0 | 0.031 |
| 4 | 28.5 | -26.5 | gangway | 1.00 | 5.82 | 361.5 | 355.1 | 283.9 | 1605.4 | 0.030 |
| 5 | 29.5 | -26.5 | gangway | 1.00 | 5.90 | 347.0 | 314.0 | 283.3 | 1597.6 | 0.033 |
| 6 | -26.5 | 28.5 | gangway | 1.00 | 6.05 | 363.6 | 348.4 | 272.9 | 1576.9 | 0.028 |
| 7 | 26.5 | -29.5 | gangway | 1.00 | 6.09 | 363.5 | 329.3 | 269.0 | 1576.3 | 0.031 |
| 8 | 26.5 | 29.5 | gangway | 1.00 | 5.89 | 343.2 | 313.8 | 273.4 | 1573.4 | 0.026 |
| 9 | 26.5 | 28.5 | gangway | 1.00 | 6.14 | 345.3 | 343.0 | 270.2 | 1571.5 | 0.024 |
| 10 | -27.5 | -28.5 | gangway | 1.00 | 5.85 | 362.4 | 360.3 | 282.5 | 1548.0 | 0.027 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -26.5 | -24.5 | seat row | 0.50 | 7.05 | 356.6 | 352.1 | 346.7 | 1184.5 | 0.016 |
| 2 | -24.5 | -26.5 | seat row | 0.50 | 7.34 | 352.3 | 350.7 | 343.7 | 1180.0 | 0.018 |
| 3 | 26.5 | -24.5 | seat row | 0.50 | 7.30 | 346.5 | 341.9 | 334.2 | 1174.0 | 0.019 |
| 4 | -26.5 | 24.5 | seat row | 0.50 | 7.28 | 354.9 | 350.7 | 334.8 | 1161.8 | 0.019 |
| 5 | -24.5 | 26.5 | seat row | 0.50 | 7.26 | 350.2 | 346.7 | 333.4 | 1152.8 | 0.020 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1516; agent-steps of seated agents on another row's clearway: 21697.

## Deposit check

Person-seconds deposited: 2890841.3, of them in excluded cells: 3107.541.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 273188 overlapping pair-steps: p99 0.0039, max 0.0842 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0039 max 0.0842; venue-geometry 2: p99 0.0002 max 0.0002 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00752 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 9 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.42 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 626 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
