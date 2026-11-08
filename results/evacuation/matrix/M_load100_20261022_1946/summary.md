# Experiment `M_load100`

**Task 5.10 stage 4 (AMD 26.10.1): venue M, 100% load, default model**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 15832 agents on 100% of the 15832 seats (spawnSeatedCrowd, seed 1337), buffer N = 16384, 3221 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 1238302 evaluations, 50756 switches, 0 forced choices).
Capacity: **within design capacity** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T19:46:54, 260.1 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1284 | 224.6 |
| t90 | 2485 | 434.6 |
| t100 | 3221 | 563.4 |

t_p: the step by which ceil(p x 15832) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 818 | 0 | 39.7 | 490.6 | 19.2 | 25.5 | 49.7-59.6 |
| -x | 5.66 | 822 | 0 | 39.7 | 494.6 | 19.1 | 25.5 | 48.8-58.8 |
| +y | 5.66 | 819 | 0 | 39.7 | 486.9 | 19.4 | 25.5 | 48.8-58.8 |
| -y | 5.66 | 819 | 0 | 39.7 | 492.0 | 19.2 | 25.5 | 49.1-59.1 |
| door +x+y (y wall) 0 | 1.20 | 622 | 1121 | 4.9 | 510.2 | 61.5 | 90.3 | 16.8-26.8 |
| door +x+y (y wall) 1 | 1.20 | 593 | 680 | 4.9 | 530.0 | 56.4 | 80.2 | 30.8-40.8 |
| door +x+y (y wall) 2 | 1.20 | 310 | 178 | 4.9 | 558.8 | 28.0 | 80.2 | 4.7-14.7 |
| door +x+y (x wall) 0 | 1.20 | 621 | 1121 | 4.9 | 513.4 | 61.0 | 90.3 | 16.8-26.8 |
| door +x+y (x wall) 1 | 1.20 | 591 | 680 | 4.9 | 530.1 | 56.2 | 80.2 | 28.3-38.3 |
| door +x+y (x wall) 2 | 1.20 | 325 | 178 | 4.9 | 555.7 | 29.5 | 80.2 | 4.7-14.7 |
| door +x+y (corner) | 1.20 | 79 | 0 | 82.7 | 537.3 | 8.7 | 70.2 | 93.4-103.4 |
| door -x+y (y wall) 0 | 1.20 | 617 | 1121 | 4.9 | 505.5 | 61.6 | 90.3 | 16.8-26.8 |
| door -x+y (y wall) 1 | 1.20 | 586 | 680 | 4.9 | 544.7 | 54.3 | 90.3 | 18.9-28.9 |
| door -x+y (y wall) 2 | 1.20 | 277 | 178 | 4.9 | 547.3 | 25.5 | 80.2 | 4.7-14.7 |
| door -x+y (x wall) 0 | 1.20 | 609 | 1121 | 4.9 | 509.0 | 60.4 | 80.2 | 13.3-23.3 |
| door -x+y (x wall) 1 | 1.20 | 602 | 680 | 4.9 | 527.0 | 57.6 | 85.3 | 25.2-35.2 |
| door -x+y (x wall) 2 | 1.20 | 318 | 178 | 4.9 | 559.0 | 28.7 | 80.2 | 4.7-14.7 |
| door -x+y (corner) | 1.20 | 133 | 0 | 65.4 | 563.4 | 13.3 | 90.3 | 439.4-449.3 |
| door -x-y (y wall) 0 | 1.20 | 617 | 1121 | 4.9 | 505.8 | 61.6 | 85.3 | 22.4-32.4 |
| door -x-y (y wall) 1 | 1.20 | 607 | 680 | 4.9 | 515.8 | 59.4 | 85.3 | 18.9-28.9 |
| door -x-y (y wall) 2 | 1.20 | 292 | 178 | 4.9 | 542.6 | 27.1 | 80.2 | 4.7-14.7 |
| door -x-y (x wall) 0 | 1.20 | 614 | 1121 | 4.9 | 505.7 | 61.3 | 85.3 | 22.4-32.4 |
| door -x-y (x wall) 1 | 1.20 | 599 | 680 | 4.9 | 515.8 | 58.6 | 90.3 | 25.7-35.7 |
| door -x-y (x wall) 2 | 1.20 | 309 | 178 | 4.9 | 537.7 | 29.0 | 80.2 | 4.7-14.7 |
| door -x-y (corner) | 1.20 | 95 | 0 | 69.6 | 528.7 | 10.3 | 70.2 | 297.9-307.8 |
| door +x-y (y wall) 0 | 1.20 | 616 | 1121 | 4.9 | 508.8 | 61.1 | 80.2 | 13.1-23.1 |
| door +x-y (y wall) 1 | 1.20 | 588 | 680 | 4.9 | 525.9 | 56.4 | 85.3 | 21.3-31.3 |
| door +x-y (y wall) 2 | 1.20 | 325 | 178 | 4.9 | 539.9 | 30.4 | 80.2 | 4.7-14.7 |
| door +x-y (x wall) 0 | 1.20 | 618 | 1121 | 4.9 | 508.3 | 61.4 | 90.3 | 16.8-26.8 |
| door +x-y (x wall) 1 | 1.20 | 589 | 680 | 4.9 | 529.4 | 56.1 | 90.3 | 25.5-35.5 |
| door +x-y (x wall) 2 | 1.20 | 314 | 178 | 4.9 | 555.2 | 28.5 | 80.2 | 4.7-14.7 |
| door +x-y (corner) | 1.20 | 88 | 0 | 69.3 | 551.7 | 9.1 | 65.2 | 108.3-118.2 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 818 | 5.2% | 18.4% |
| -x | avenue | 5.66 | 822 | 5.2% | 18.5% |
| +y | avenue | 5.66 | 819 | 5.2% | 18.4% |
| -y | avenue | 5.66 | 819 | 5.2% | 18.4% |
| door +x+y (y wall) 0 | door | 1.20 | 622 | 3.9% | 66.0% |
| door +x+y (y wall) 1 | door | 1.20 | 593 | 3.7% | 63.0% |
| door +x+y (y wall) 2 | door | 1.20 | 310 | 2.0% | 32.9% |
| door +x+y (x wall) 0 | door | 1.20 | 621 | 3.9% | 65.9% |
| door +x+y (x wall) 1 | door | 1.20 | 591 | 3.7% | 62.7% |
| door +x+y (x wall) 2 | door | 1.20 | 325 | 2.1% | 34.5% |
| door +x+y (corner) | door | 1.20 | 79 | 0.5% | 8.4% |
| door -x+y (y wall) 0 | door | 1.20 | 617 | 3.9% | 65.5% |
| door -x+y (y wall) 1 | door | 1.20 | 586 | 3.7% | 62.2% |
| door -x+y (y wall) 2 | door | 1.20 | 277 | 1.7% | 29.4% |
| door -x+y (x wall) 0 | door | 1.20 | 609 | 3.8% | 64.7% |
| door -x+y (x wall) 1 | door | 1.20 | 602 | 3.8% | 63.9% |
| door -x+y (x wall) 2 | door | 1.20 | 318 | 2.0% | 33.8% |
| door -x+y (corner) | door | 1.20 | 133 | 0.8% | 14.1% |
| door -x-y (y wall) 0 | door | 1.20 | 617 | 3.9% | 65.5% |
| door -x-y (y wall) 1 | door | 1.20 | 607 | 3.8% | 64.4% |
| door -x-y (y wall) 2 | door | 1.20 | 292 | 1.8% | 31.0% |
| door -x-y (x wall) 0 | door | 1.20 | 614 | 3.9% | 65.2% |
| door -x-y (x wall) 1 | door | 1.20 | 599 | 3.8% | 63.6% |
| door -x-y (x wall) 2 | door | 1.20 | 309 | 2.0% | 32.8% |
| door -x-y (corner) | door | 1.20 | 95 | 0.6% | 10.1% |
| door +x-y (y wall) 0 | door | 1.20 | 616 | 3.9% | 65.4% |
| door +x-y (y wall) 1 | door | 1.20 | 588 | 3.7% | 62.4% |
| door +x-y (y wall) 2 | door | 1.20 | 325 | 2.1% | 34.5% |
| door +x-y (x wall) 0 | door | 1.20 | 618 | 3.9% | 65.6% |
| door +x-y (x wall) 1 | door | 1.20 | 589 | 3.7% | 62.5% |
| door +x-y (x wall) 2 | door | 1.20 | 314 | 2.0% | 33.3% |
| door +x-y (corner) | door | 1.20 | 88 | 0.6% | 9.3% |
| **doors (28)** | door | 33.60 | 12554 | 79.3% | |
| **avenues (4)** | avenue | 22.64 | 3278 | 20.7% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 563.4 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 35.9%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 961 | 6.1% | 961 | 6.1% |
| straight +x+y (y wing) 1 | straight | yes | 601 | 3.8% | 598 | 3.8% |
| straight +x+y (y wing) 2 | straight | yes | 305 | 1.9% | 305 | 1.9% |
| straight +x+y (x wing) 0 | straight | yes | 960 | 6.1% | 960 | 6.1% |
| straight +x+y (x wing) 1 | straight | yes | 601 | 3.8% | 596 | 3.8% |
| straight +x+y (x wing) 2 | straight | yes | 320 | 2.0% | 320 | 2.0% |
| corner +x+y | corner | yes | 785 | 5.0% | 218 | 1.4% |
| straight -x+y (y wing) 0 | straight | yes | 958 | 6.1% | 958 | 6.1% |
| straight -x+y (y wing) 1 | straight | yes | 592 | 3.7% | 586 | 3.7% |
| straight -x+y (y wing) 2 | straight | yes | 277 | 1.7% | 277 | 1.7% |
| straight -x+y (x wing) 0 | straight | yes | 948 | 6.0% | 948 | 6.0% |
| straight -x+y (x wing) 1 | straight | yes | 610 | 3.9% | 602 | 3.8% |
| straight -x+y (x wing) 2 | straight | yes | 318 | 2.0% | 317 | 2.0% |
| corner -x+y | corner | yes | 791 | 5.0% | 270 | 1.7% |
| straight -x-y (y wing) 0 | straight | yes | 958 | 6.1% | 958 | 6.1% |
| straight -x-y (y wing) 1 | straight | yes | 611 | 3.9% | 608 | 3.8% |
| straight -x-y (y wing) 2 | straight | yes | 291 | 1.8% | 291 | 1.8% |
| straight -x-y (x wing) 0 | straight | yes | 960 | 6.1% | 960 | 6.1% |
| straight -x-y (x wing) 1 | straight | yes | 604 | 3.8% | 599 | 3.8% |
| straight -x-y (x wing) 2 | straight | yes | 309 | 2.0% | 309 | 2.0% |
| corner -x-y | corner | yes | 796 | 5.0% | 233 | 1.5% |
| straight +x-y (y wing) 0 | straight | yes | 956 | 6.0% | 956 | 6.0% |
| straight +x-y (y wing) 1 | straight | yes | 605 | 3.8% | 599 | 3.8% |
| straight +x-y (y wing) 2 | straight | yes | 312 | 2.0% | 312 | 2.0% |
| straight +x-y (x wing) 0 | straight | yes | 960 | 6.1% | 960 | 6.1% |
| straight +x-y (x wing) 1 | straight | yes | 613 | 3.9% | 608 | 3.8% |
| straight +x-y (x wing) 2 | straight | yes | 295 | 1.9% | 295 | 1.9% |
| corner +x-y | corner | yes | 788 | 5.0% | 228 | 1.4% |
| **straight (24)** | | | 14925 | | 14883 | 94.0% |
| **corner (4)** | | | 3160 | | 949 | 6.0% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 818 | 39.7 | 490.6 | 0.23 | 0.31 | 0.0% |
| -x | 822 | 39.7 | 494.6 | 0.23 | 0.31 | 0.0% |
| +y | 819 | 39.7 | 486.9 | 0.23 | 0.31 | 0.0% |
| -y | 819 | 39.7 | 492.0 | 0.23 | 0.31 | 0.0% |
| door +x+y (y wall) 0 | 622 | 4.9 | 510.2 | 0.74 | 1.08 | 38.5% |
| door +x+y (y wall) 1 | 593 | 4.9 | 530.0 | 0.68 | 0.96 | 25.9% |
| door +x+y (y wall) 2 | 310 | 4.9 | 558.8 | 0.33 | 0.96 | 7.0% |
| door +x+y (x wall) 0 | 621 | 4.9 | 513.4 | 0.73 | 1.08 | 30.8% |
| door +x+y (x wall) 1 | 591 | 4.9 | 530.1 | 0.67 | 0.96 | 25.9% |
| door +x+y (x wall) 2 | 325 | 4.9 | 555.7 | 0.35 | 0.96 | 3.6% |
| door +x+y (corner) | 79 | 82.7 | 537.3 | 0.10 | 0.84 | 0.0% |
| door -x+y (y wall) 0 | 617 | 4.9 | 505.5 | 0.74 | 1.08 | 37.3% |
| door -x+y (y wall) 1 | 586 | 4.9 | 544.7 | 0.65 | 1.08 | 23.6% |
| door -x+y (y wall) 2 | 277 | 4.9 | 547.3 | 0.31 | 0.96 | 3.6% |
| door -x+y (x wall) 0 | 609 | 4.9 | 509.0 | 0.72 | 0.96 | 30.8% |
| door -x+y (x wall) 1 | 602 | 4.9 | 527.0 | 0.69 | 1.02 | 35.8% |
| door -x+y (x wall) 2 | 318 | 4.9 | 559.0 | 0.34 | 0.96 | 3.5% |
| door -x+y (corner) | 133 | 65.4 | 563.4 | 0.16 | 1.08 | 3.9% |
| door -x-y (y wall) 0 | 617 | 4.9 | 505.8 | 0.74 | 1.02 | 37.3% |
| door -x-y (y wall) 1 | 607 | 4.9 | 515.8 | 0.71 | 1.02 | 25.0% |
| door -x-y (y wall) 2 | 292 | 4.9 | 542.6 | 0.32 | 0.96 | 3.6% |
| door -x-y (x wall) 0 | 614 | 4.9 | 505.7 | 0.73 | 1.02 | 37.3% |
| door -x-y (x wall) 1 | 599 | 4.9 | 515.8 | 0.70 | 1.08 | 26.9% |
| door -x-y (x wall) 2 | 309 | 4.9 | 537.7 | 0.35 | 0.96 | 7.4% |
| door -x-y (corner) | 95 | 69.6 | 528.7 | 0.12 | 0.84 | 2.1% |
| door +x-y (y wall) 0 | 616 | 4.9 | 508.8 | 0.73 | 0.96 | 34.6% |
| door +x-y (y wall) 1 | 588 | 4.9 | 525.9 | 0.67 | 1.02 | 18.9% |
| door +x-y (y wall) 2 | 325 | 4.9 | 539.9 | 0.36 | 0.96 | 5.5% |
| door +x-y (x wall) 0 | 618 | 4.9 | 508.3 | 0.73 | 1.08 | 39.2% |
| door +x-y (x wall) 1 | 589 | 4.9 | 529.4 | 0.67 | 1.08 | 18.5% |
| door +x-y (x wall) 2 | 314 | 4.9 | 555.2 | 0.34 | 0.96 | 3.6% |
| door +x-y (corner) | 88 | 69.3 | 551.7 | 0.11 | 0.78 | 0.0% |

Mean flow / w J averaged over the doors 0.52, over the avenues 0.23.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 961 | 622 / 339 / 226 | 0.7 | 507.2 | 2.34 | 3.51 | 90% | 78% | 12% | 3.78 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 558 | 598 / 0 / 6 | 0.7 | 527.0 | 1.15 | 1.60 | 79% | 64% | 15% | 3.52 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 72 | 305 / 0 / 0 | 0.7 | 555.9 | 0.55 | 1.50 | 12% | 9% | 4% | 2.53 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 960 | 621 / 339 / 213 | 0.7 | 510.4 | 2.30 | 3.61 | 90% | 79% | 12% | 3.77 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 557 | 596 / 0 / 9 | 0.7 | 527.2 | 1.15 | 1.71 | 77% | 68% | 9% | 3.63 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 71 | 320 / 0 / 0 | 0.7 | 552.7 | 0.58 | 1.50 | 12% | 9% | 4% | 2.56 |
| corner +x+y | 1.20 | 85.6 | 779 | 79 / 139 / 576 | 0.7 | 549.9 | 1.45 | 3.91 | 84% | 55% | 29% | 2.37 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 958 | 617 / 341 / 233 | 0.7 | 502.5 | 2.37 | 4.41 | 88% | 78% | 10% | 3.88 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 561 | 586 / 0 / 23 | 0.7 | 541.7 | 1.13 | 2.21 | 76% | 65% | 11% | 3.56 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 70 | 277 / 0 / 0 | 0.7 | 544.3 | 0.51 | 1.50 | 13% | 9% | 4% | 2.56 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 948 | 609 / 339 / 218 | 0.7 | 506.0 | 2.31 | 3.61 | 80% | 80% | 0% | 4.20 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 568 | 602 / 0 / 9 | 0.7 | 524.0 | 1.17 | 1.60 | 77% | 62% | 15% | 3.47 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 71 | 317 / 0 / 1 | 0.7 | 556.0 | 0.57 | 1.50 | 11% | 9% | 2% | 2.63 |
| corner -x+y | 1.20 | 85.6 | 782 | 134 / 136 / 545 | 0.7 | 559.5 | 1.46 | 4.01 | 82% | 58% | 25% | 2.40 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 958 | 617 / 341 / 205 | 0.7 | 502.9 | 2.32 | 3.81 | 90% | 78% | 12% | 3.88 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 557 | 608 / 0 / 12 | 0.7 | 512.8 | 1.21 | 1.60 | 79% | 65% | 13% | 3.57 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 71 | 291 / 0 / 0 | 0.7 | 539.6 | 0.54 | 1.50 | 13% | 9% | 4% | 2.51 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 960 | 614 / 346 / 212 | 0.7 | 502.7 | 2.33 | 3.51 | 90% | 80% | 10% | 3.86 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 552 | 599 / 0 / 7 | 0.7 | 512.8 | 1.18 | 1.71 | 79% | 65% | 13% | 3.55 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 70 | 309 / 0 / 0 | 0.7 | 534.7 | 0.58 | 1.50 | 13% | 11% | 2% | 2.54 |
| corner -x-y | 1.20 | 85.6 | 790 | 95 / 138 / 576 | 0.7 | 533.5 | 1.52 | 4.01 | 85% | 61% | 24% | 2.46 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 956 | 616 / 340 / 238 | 0.7 | 505.8 | 2.36 | 3.81 | 90% | 80% | 10% | 3.82 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 563 | 599 / 0 / 6 | 0.7 | 523.0 | 1.16 | 1.71 | 85% | 66% | 19% | 3.37 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 71 | 312 / 0 / 0 | 0.7 | 537.0 | 0.58 | 1.50 | 11% | 9% | 2% | 2.65 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 960 | 618 / 342 / 232 | 0.7 | 505.3 | 2.36 | 3.81 | 90% | 80% | 10% | 3.95 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 558 | 608 / 0 / 9 | 0.7 | 526.5 | 1.17 | 1.71 | 81% | 68% | 13% | 3.53 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 70 | 295 / 0 / 0 | 0.7 | 552.2 | 0.53 | 1.50 | 12% | 9% | 4% | 2.56 |
| corner +x-y | 1.20 | 85.6 | 780 | 90 / 138 / 567 | 0.7 | 547.8 | 1.45 | 3.91 | 84% | 56% | 27% | 2.43 |

The last agent out (agent 6312, t100 563.4 s): last gangway corner -x+y, exit door -x+y (corner). The gangway that cleared last: corner -x+y at 559.5 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.81 | 560.9 / 545.0 / 513.9 | 537.1 / 502.0 / 438.8 | 711285.8 | 1608167 | 0.216 |
| gangway | 1212 | 1112.9 | 6.81 | 558.3 / 539.2 / 460.7 | 537.1 / 502.0 / 438.8 | 710430.6 | 1453905 | 0.109 |
| walkway | 276 | 257.4 | 3.19 | 181.9 / 105.1 / 0.0 | 121.7 / 38.7 / 0.0 | 0.0 | 26619 | 0.864 |
| avenue | 912 | 858.9 | 1.83 | 201.8 / 0.0 / 0.0 | 160.9 / 0.0 / 0.0 | 0.0 | 94105 | 1.327 |
| exit | 32 | 3.2 | 0.00 | 528.0 / 524.4 / 469.4 | 251.5 / 230.0 / 136.4 | 855.1 | 1627 | 1.324 |
| concourse | 1116 | 1043.8 | 2.74 | 488.5 / 13.1 / 0.0 | 117.4 / 11.5 / 0.0 | 0.0 | 31912 | 1.192 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.59 | 481.5 / 472.1 / 462.6 | 475.0 / 472.1 / 457.6 | 754308.2 | 2092857 | 0.042 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -27.5 | -27.5 | gangway | 1.00 | 5.96 | 466.5 | 464.4 | 420.7 | 2427.2 | 0.015 |
| 2 | 27.5 | -27.5 | gangway | 1.00 | 6.01 | 483.6 | 481.3 | 407.0 | 2347.7 | 0.016 |
| 3 | 28.5 | -26.5 | gangway | 1.00 | 6.23 | 485.5 | 470.7 | 397.7 | 2347.0 | 0.022 |
| 4 | 27.5 | 27.5 | gangway | 1.00 | 6.07 | 480.8 | 466.1 | 407.5 | 2338.0 | 0.015 |
| 5 | 29.5 | -26.5 | gangway | 1.00 | 6.05 | 470.3 | 431.8 | 390.9 | 2276.6 | 0.026 |
| 6 | -27.5 | -28.5 | gangway | 1.00 | 5.80 | 461.9 | 454.2 | 403.9 | 2263.6 | 0.017 |
| 7 | 26.5 | 28.5 | gangway | 1.00 | 5.95 | 467.4 | 453.0 | 399.0 | 2260.7 | 0.022 |
| 8 | 27.5 | -26.5 | gangway | 1.00 | 5.89 | 486.9 | 482.6 | 399.5 | 2256.7 | 0.019 |
| 9 | 26.5 | 27.5 | gangway | 1.00 | 5.79 | 473.3 | 456.5 | 401.6 | 2256.0 | 0.019 |
| 10 | -28.5 | -26.5 | gangway | 1.00 | 6.04 | 463.2 | 443.7 | 390.0 | 2253.7 | 0.021 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 26.5 | 24.5 | seat row | 0.50 | 7.41 | 469.8 | 464.7 | 455.8 | 1587.6 | 0.013 |
| 2 | -24.5 | 26.5 | seat row | 0.50 | 7.12 | 469.6 | 466.7 | 456.7 | 1575.2 | 0.013 |
| 3 | -26.5 | -24.5 | seat row | 0.50 | 7.31 | 465.6 | 464.4 | 451.6 | 1564.1 | 0.013 |
| 4 | 26.5 | -24.5 | seat row | 0.50 | 7.27 | 459.1 | 458.8 | 445.7 | 1561.1 | 0.014 |
| 5 | 24.5 | -26.5 | seat row | 0.50 | 7.11 | 466.3 | 461.1 | 452.0 | 1559.0 | 0.013 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1779; agent-steps of seated agents on another row's clearway: 16136.

## Deposit check

Person-seconds deposited: 3704155.7, of them in excluded cells: 3131.248.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 377643 overlapping pair-steps: p99 0.0030, max 0.0318 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0030 max 0.0318; venue-geometry 3: p99 0.0002 max 0.0002 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 14 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.25 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 554 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
