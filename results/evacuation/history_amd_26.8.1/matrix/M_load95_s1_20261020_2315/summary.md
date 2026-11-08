# Experiment `M_load95_s1`

**Task 5.9 stage 4: venue M, 95% load (seed 1), default model**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 15040 agents on 95% of the 15832 seats (spawnSeatedCrowd, seed 1), buffer N = 16384, 3062 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 1119683 evaluations, 46952 switches, 0 forced choices).
Capacity: **within design capacity** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-20T23:15:01, 71.8 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1223 | 213.9 |
| t90 | 2360 | 412.8 |
| t100 | 3062 | 535.6 |

t_p: the step by which ceil(p x 15040) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 780 | 0 | 39.5 | 463.9 | 19.5 | 25.5 | 78.9-88.9 |
| -x | 5.66 | 782 | 0 | 39.4 | 467.0 | 19.4 | 25.5 | 72.8-82.7 |
| +y | 5.66 | 781 | 0 | 39.7 | 468.7 | 19.3 | 25.5 | 48.4-58.4 |
| -y | 5.66 | 779 | 0 | 39.7 | 465.1 | 19.4 | 26.6 | 141.1-151.1 |
| door +x+y (y wall) 0 | 1.20 | 585 | 1057 | 4.9 | 486.2 | 60.7 | 85.3 | 29.6-39.5 |
| door +x+y (y wall) 1 | 1.20 | 581 | 649 | 4.9 | 500.8 | 58.6 | 85.3 | 20.5-30.4 |
| door +x+y (y wall) 2 | 1.20 | 302 | 167 | 4.9 | 525.2 | 29.0 | 80.2 | 5.9-15.9 |
| door +x+y (x wall) 0 | 1.20 | 579 | 1061 | 4.9 | 483.1 | 60.5 | 85.3 | 12.6-22.6 |
| door +x+y (x wall) 1 | 1.20 | 585 | 649 | 4.9 | 500.2 | 59.0 | 90.3 | 16.3-26.2 |
| door +x+y (x wall) 2 | 1.20 | 275 | 170 | 4.9 | 535.6 | 25.9 | 80.2 | 4.7-14.7 |
| door +x+y (corner) | 1.20 | 64 | 0 | 71.9 | 523.5 | 7.1 | 65.2 | 80.3-90.3 |
| door -x+y (y wall) 0 | 1.20 | 579 | 1061 | 4.9 | 481.2 | 60.8 | 85.3 | 12.6-22.6 |
| door -x+y (y wall) 1 | 1.20 | 586 | 653 | 4.9 | 511.1 | 57.9 | 85.3 | 12.9-22.9 |
| door -x+y (y wall) 2 | 1.20 | 285 | 168 | 4.9 | 514.8 | 27.9 | 75.2 | 5.1-15.0 |
| door -x+y (x wall) 0 | 1.20 | 578 | 1068 | 4.9 | 481.0 | 60.7 | 80.2 | 5.6-15.6 |
| door -x+y (x wall) 1 | 1.20 | 591 | 643 | 4.9 | 511.1 | 58.4 | 85.3 | 23.4-33.4 |
| door -x+y (x wall) 2 | 1.20 | 263 | 169 | 4.9 | 509.3 | 26.1 | 75.2 | 5.1-15.0 |
| door -x+y (corner) | 1.20 | 100 | 0 | 76.3 | 520.2 | 11.3 | 55.2 | 259.7-269.7 |
| door -x-y (y wall) 0 | 1.20 | 586 | 1058 | 4.9 | 482.6 | 61.3 | 90.3 | 22.6-32.5 |
| door -x-y (y wall) 1 | 1.20 | 567 | 656 | 4.9 | 481.2 | 59.5 | 85.3 | 12.8-22.7 |
| door -x-y (y wall) 2 | 1.20 | 283 | 168 | 4.9 | 489.2 | 29.2 | 80.2 | 6.6-16.6 |
| door -x-y (x wall) 0 | 1.20 | 586 | 1070 | 4.9 | 496.4 | 59.6 | 90.3 | 26.9-36.9 |
| door -x-y (x wall) 1 | 1.20 | 582 | 645 | 4.9 | 493.1 | 59.6 | 85.3 | 9.1-19.1 |
| door -x-y (x wall) 2 | 1.20 | 270 | 174 | 4.9 | 498.3 | 27.4 | 80.2 | 4.7-14.7 |
| door -x-y (corner) | 1.20 | 115 | 0 | 80.1 | 496.7 | 13.8 | 85.3 | 86.4-96.4 |
| door +x-y (y wall) 0 | 1.20 | 583 | 1063 | 4.9 | 482.4 | 61.0 | 85.3 | 17.1-27.1 |
| door +x-y (y wall) 1 | 1.20 | 574 | 642 | 4.9 | 494.8 | 58.6 | 90.3 | 21.5-31.5 |
| door +x-y (y wall) 2 | 1.20 | 300 | 169 | 5.2 | 512.7 | 29.6 | 80.2 | 6.8-16.8 |
| door +x-y (x wall) 0 | 1.20 | 586 | 1062 | 4.9 | 489.7 | 60.4 | 85.3 | 12.4-22.4 |
| door +x-y (x wall) 1 | 1.20 | 578 | 649 | 4.9 | 503.7 | 57.9 | 90.3 | 16.3-26.2 |
| door +x-y (x wall) 2 | 1.20 | 259 | 169 | 4.9 | 516.7 | 25.3 | 80.2 | 4.7-14.7 |
| door +x-y (corner) | 1.20 | 96 | 0 | 60.7 | 502.0 | 10.9 | 65.2 | 84.8-94.8 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 780 | 5.2% | 18.5% |
| -x | avenue | 5.66 | 782 | 5.2% | 18.5% |
| +y | avenue | 5.66 | 781 | 5.2% | 18.5% |
| -y | avenue | 5.66 | 779 | 5.2% | 18.4% |
| door +x+y (y wall) 0 | door | 1.20 | 585 | 3.9% | 65.3% |
| door +x+y (y wall) 1 | door | 1.20 | 581 | 3.9% | 64.9% |
| door +x+y (y wall) 2 | door | 1.20 | 302 | 2.0% | 33.7% |
| door +x+y (x wall) 0 | door | 1.20 | 579 | 3.8% | 64.7% |
| door +x+y (x wall) 1 | door | 1.20 | 585 | 3.9% | 65.3% |
| door +x+y (x wall) 2 | door | 1.20 | 275 | 1.8% | 30.7% |
| door +x+y (corner) | door | 1.20 | 64 | 0.4% | 7.1% |
| door -x+y (y wall) 0 | door | 1.20 | 579 | 3.8% | 64.7% |
| door -x+y (y wall) 1 | door | 1.20 | 586 | 3.9% | 65.4% |
| door -x+y (y wall) 2 | door | 1.20 | 285 | 1.9% | 31.8% |
| door -x+y (x wall) 0 | door | 1.20 | 578 | 3.8% | 64.5% |
| door -x+y (x wall) 1 | door | 1.20 | 591 | 3.9% | 66.0% |
| door -x+y (x wall) 2 | door | 1.20 | 263 | 1.7% | 29.4% |
| door -x+y (corner) | door | 1.20 | 100 | 0.7% | 11.2% |
| door -x-y (y wall) 0 | door | 1.20 | 586 | 3.9% | 65.4% |
| door -x-y (y wall) 1 | door | 1.20 | 567 | 3.8% | 63.3% |
| door -x-y (y wall) 2 | door | 1.20 | 283 | 1.9% | 31.6% |
| door -x-y (x wall) 0 | door | 1.20 | 586 | 3.9% | 65.4% |
| door -x-y (x wall) 1 | door | 1.20 | 582 | 3.9% | 65.0% |
| door -x-y (x wall) 2 | door | 1.20 | 270 | 1.8% | 30.2% |
| door -x-y (corner) | door | 1.20 | 115 | 0.8% | 12.8% |
| door +x-y (y wall) 0 | door | 1.20 | 583 | 3.9% | 65.1% |
| door +x-y (y wall) 1 | door | 1.20 | 574 | 3.8% | 64.1% |
| door +x-y (y wall) 2 | door | 1.20 | 300 | 2.0% | 33.5% |
| door +x-y (x wall) 0 | door | 1.20 | 586 | 3.9% | 65.4% |
| door +x-y (x wall) 1 | door | 1.20 | 578 | 3.8% | 64.5% |
| door +x-y (x wall) 2 | door | 1.20 | 259 | 1.7% | 28.9% |
| door +x-y (corner) | door | 1.20 | 96 | 0.6% | 10.7% |
| **doors (28)** | door | 33.60 | 11918 | 79.2% | |
| **avenues (4)** | avenue | 22.64 | 3122 | 20.8% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 535.6 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 35.8%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 915 | 6.1% | 915 | 6.1% |
| straight +x+y (y wing) 1 | straight | yes | 583 | 3.9% | 581 | 3.9% |
| straight +x+y (y wing) 2 | straight | yes | 302 | 2.0% | 302 | 2.0% |
| straight +x+y (x wing) 0 | straight | yes | 900 | 6.0% | 900 | 6.0% |
| straight +x+y (x wing) 1 | straight | yes | 590 | 3.9% | 588 | 3.9% |
| straight +x+y (x wing) 2 | straight | yes | 272 | 1.8% | 272 | 1.8% |
| corner +x+y | corner | yes | 748 | 5.0% | 195 | 1.3% |
| straight -x+y (y wing) 0 | straight | yes | 903 | 6.0% | 903 | 6.0% |
| straight -x+y (y wing) 1 | straight | yes | 588 | 3.9% | 586 | 3.9% |
| straight -x+y (y wing) 2 | straight | yes | 285 | 1.9% | 285 | 1.9% |
| straight -x+y (x wing) 0 | straight | yes | 903 | 6.0% | 903 | 6.0% |
| straight -x+y (x wing) 1 | straight | yes | 594 | 3.9% | 591 | 3.9% |
| straight -x+y (x wing) 2 | straight | yes | 263 | 1.7% | 263 | 1.7% |
| corner -x+y | corner | yes | 745 | 5.0% | 231 | 1.5% |
| straight -x-y (y wing) 0 | straight | yes | 910 | 6.1% | 909 | 6.0% |
| straight -x-y (y wing) 1 | straight | yes | 575 | 3.8% | 571 | 3.8% |
| straight -x-y (y wing) 2 | straight | yes | 279 | 1.9% | 279 | 1.9% |
| straight -x-y (x wing) 0 | straight | yes | 908 | 6.0% | 908 | 6.0% |
| straight -x-y (x wing) 1 | straight | yes | 590 | 3.9% | 585 | 3.9% |
| straight -x-y (x wing) 2 | straight | yes | 269 | 1.8% | 269 | 1.8% |
| corner -x-y | corner | yes | 756 | 5.0% | 250 | 1.7% |
| straight +x-y (y wing) 0 | straight | yes | 910 | 6.1% | 910 | 6.1% |
| straight +x-y (y wing) 1 | straight | yes | 580 | 3.9% | 576 | 3.8% |
| straight +x-y (y wing) 2 | straight | yes | 298 | 2.0% | 298 | 2.0% |
| straight +x-y (x wing) 0 | straight | yes | 912 | 6.1% | 912 | 6.1% |
| straight +x-y (x wing) 1 | straight | yes | 583 | 3.9% | 578 | 3.8% |
| straight +x-y (x wing) 2 | straight | yes | 261 | 1.7% | 259 | 1.7% |
| corner +x-y | corner | yes | 744 | 4.9% | 221 | 1.5% |
| **straight (24)** | | | 14173 | | 14143 | 94.0% |
| **corner (4)** | | | 2993 | | 897 | 6.0% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 780 | 39.5 | 463.9 | 0.23 | 0.31 | 0.0% |
| -x | 782 | 39.4 | 467.0 | 0.23 | 0.31 | 0.0% |
| +y | 781 | 39.7 | 468.7 | 0.23 | 0.31 | 0.0% |
| -y | 779 | 39.7 | 465.1 | 0.23 | 0.32 | 0.0% |
| door +x+y (y wall) 0 | 585 | 4.9 | 486.2 | 0.73 | 1.02 | 34.7% |
| door +x+y (y wall) 1 | 581 | 4.9 | 500.8 | 0.70 | 1.02 | 25.5% |
| door +x+y (y wall) 2 | 302 | 4.9 | 525.2 | 0.35 | 0.96 | 5.7% |
| door +x+y (x wall) 0 | 579 | 4.9 | 483.1 | 0.72 | 1.02 | 36.7% |
| door +x+y (x wall) 1 | 585 | 4.9 | 500.2 | 0.71 | 1.08 | 31.4% |
| door +x+y (x wall) 2 | 275 | 4.9 | 535.6 | 0.31 | 0.96 | 7.4% |
| door +x+y (corner) | 64 | 71.9 | 523.5 | 0.08 | 0.78 | 0.0% |
| door -x+y (y wall) 0 | 579 | 4.9 | 481.2 | 0.73 | 1.02 | 34.7% |
| door -x+y (y wall) 1 | 586 | 4.9 | 511.1 | 0.69 | 1.02 | 30.8% |
| door -x+y (y wall) 2 | 285 | 4.9 | 514.8 | 0.33 | 0.90 | 7.7% |
| door -x+y (x wall) 0 | 578 | 4.9 | 481.0 | 0.73 | 0.96 | 28.6% |
| door -x+y (x wall) 1 | 591 | 4.9 | 511.1 | 0.70 | 1.02 | 36.5% |
| door -x+y (x wall) 2 | 263 | 4.9 | 509.3 | 0.31 | 0.90 | 3.8% |
| door -x+y (corner) | 100 | 76.3 | 520.2 | 0.13 | 0.66 | 0.0% |
| door -x-y (y wall) 0 | 586 | 4.9 | 482.6 | 0.73 | 1.08 | 36.7% |
| door -x-y (y wall) 1 | 567 | 4.9 | 481.2 | 0.71 | 1.02 | 26.5% |
| door -x-y (y wall) 2 | 283 | 4.9 | 489.2 | 0.35 | 0.96 | 4.0% |
| door -x-y (x wall) 0 | 586 | 4.9 | 496.4 | 0.71 | 1.08 | 46.0% |
| door -x-y (x wall) 1 | 582 | 4.9 | 493.1 | 0.71 | 1.02 | 26.0% |
| door -x-y (x wall) 2 | 270 | 4.9 | 498.3 | 0.33 | 0.96 | 8.0% |
| door -x-y (corner) | 115 | 80.1 | 496.7 | 0.17 | 1.02 | 2.4% |
| door +x-y (y wall) 0 | 583 | 4.9 | 482.4 | 0.73 | 1.02 | 32.7% |
| door +x-y (y wall) 1 | 574 | 4.9 | 494.8 | 0.70 | 1.08 | 32.0% |
| door +x-y (y wall) 2 | 300 | 5.2 | 512.7 | 0.35 | 0.96 | 3.8% |
| door +x-y (x wall) 0 | 586 | 4.9 | 489.7 | 0.72 | 1.02 | 34.0% |
| door +x-y (x wall) 1 | 578 | 4.9 | 503.7 | 0.69 | 1.08 | 27.5% |
| door +x-y (x wall) 2 | 259 | 4.9 | 516.7 | 0.30 | 0.96 | 3.8% |
| door +x-y (corner) | 96 | 60.7 | 502.0 | 0.13 | 0.78 | 0.0% |

Mean flow / w J averaged over the doors 0.52, over the avenues 0.23.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 915 | 585 / 330 / 218 | 0.7 | 483.3 | 2.35 | 3.61 | 90% | 78% | 12% | 3.66 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 523 | 581 / 0 / 5 | 0.7 | 497.8 | 1.18 | 1.91 | 76% | 66% | 10% | 3.58 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 64 | 302 / 0 / 0 | 0.7 | 522.3 | 0.58 | 1.40 | 9% | 9% | 0% | 2.62 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 900 | 579 / 321 / 209 | 0.7 | 480.1 | 2.31 | 3.71 | 90% | 78% | 12% | 3.68 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 545 | 588 / 0 / 6 | 0.7 | 497.3 | 1.20 | 1.91 | 80% | 68% | 12% | 3.68 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 66 | 272 / 0 / 0 | 0.7 | 532.6 | 0.51 | 1.50 | 11% | 11% | 0% | 2.81 |
| corner +x+y | 1.20 | 85.6 | 740 | 64 / 131 / 556 | 0.7 | 526.6 | 1.43 | 4.51 | 85% | 64% | 21% | 2.50 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 903 | 579 / 324 / 246 | 0.7 | 478.2 | 2.41 | 4.11 | 92% | 79% | 12% | 3.68 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 536 | 586 / 0 / 10 | 0.7 | 508.1 | 1.17 | 1.81 | 76% | 63% | 14% | 3.55 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 64 | 285 / 0 / 0 | 0.7 | 511.8 | 0.56 | 1.40 | 12% | 10% | 2% | 2.54 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 903 | 578 / 325 / 228 | 0.7 | 478.0 | 2.37 | 3.61 | 92% | 79% | 12% | 3.71 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 550 | 591 / 0 / 6 | 0.7 | 508.1 | 1.18 | 1.71 | 76% | 65% | 12% | 3.64 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 68 | 263 / 0 / 0 | 0.7 | 506.4 | 0.52 | 1.40 | 12% | 12% | 0% | 2.61 |
| corner -x+y | 1.20 | 85.6 | 738 | 100 / 131 / 523 | 0.7 | 516.3 | 1.46 | 3.91 | 87% | 63% | 23% | 2.50 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 910 | 586 / 324 / 221 | 0.7 | 479.6 | 2.36 | 4.11 | 80% | 78% | 2% | 4.09 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 534 | 571 / 0 / 6 | 0.7 | 478.2 | 1.21 | 1.81 | 81% | 69% | 12% | 3.57 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 62 | 279 / 0 / 0 | 0.7 | 486.2 | 0.57 | 1.50 | 12% | 12% | 0% | 2.59 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 907 | 584 / 324 / 212 | 0.7 | 493.4 | 2.27 | 3.51 | 86% | 74% | 12% | 3.71 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 541 | 585 / 0 / 8 | 0.7 | 490.1 | 1.21 | 1.81 | 80% | 70% | 10% | 3.58 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 69 | 269 / 0 / 0 | 0.7 | 495.3 | 0.54 | 1.50 | 12% | 10% | 2% | 2.67 |
| corner -x-y | 1.20 | 85.6 | 748 | 115 / 135 / 512 | 0.7 | 492.9 | 1.55 | 3.41 | 88% | 60% | 28% | 2.43 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 910 | 583 / 327 / 228 | 0.7 | 479.4 | 2.38 | 3.81 | 90% | 76% | 14% | 3.71 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 537 | 576 / 0 / 4 | 0.7 | 491.8 | 1.18 | 1.81 | 78% | 64% | 14% | 3.47 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 66 | 298 / 0 / 0 | 0.7 | 509.7 | 0.59 | 1.40 | 12% | 10% | 2% | 2.63 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 912 | 586 / 326 / 217 | 0.7 | 486.8 | 2.32 | 3.81 | 90% | 78% | 12% | 3.71 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 529 | 578 / 0 / 7 | 0.7 | 500.8 | 1.17 | 1.81 | 75% | 61% | 14% | 3.55 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 65 | 259 / 0 / 3 | 0.7 | 513.7 | 0.51 | 1.50 | 10% | 10% | 0% | 2.83 |
| corner +x-y | 1.20 | 85.6 | 735 | 96 / 125 / 528 | 0.7 | 507.6 | 1.48 | 3.81 | 88% | 63% | 25% | 2.43 |

The last agent out (agent 2229, t100 535.6 s): last gangway straight +x+y (x wing) 2, exit door +x+y (x wall) 2. The gangway that cleared last: straight +x+y (x wing) 2 at 532.6 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.76 | 526.1 / 512.1 / 484.3 | 512.8 / 480.5 / 415.1 | 646922.8 | 1513517 | 0.217 |
| gangway | 1212 | 1112.9 | 6.76 | 526.1 / 505.3 / 436.6 | 512.8 / 480.5 / 415.1 | 646088.7 | 1369487 | 0.110 |
| walkway | 276 | 257.4 | 2.93 | 202.7 / 102.1 / 0.0 | 118.6 / 16.8 / 0.0 | 0.0 | 22886 | 0.950 |
| avenue | 912 | 858.9 | 1.88 | 218.6 / 0.0 / 0.0 | 164.4 / 0.0 / 0.0 | 0.0 | 89626 | 1.327 |
| exit | 32 | 3.2 | 0.00 | 503.6 / 500.4 / 447.9 | 249.8 / 222.5 / 133.3 | 834.1 | 1573 | 1.322 |
| concourse | 1116 | 1043.8 | 2.00 | 466.7 / 0.0 / 0.0 | 124.5 / 0.0 / 0.0 | 0.0 | 29946 | 1.194 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.65 | 465.6 / 450.9 / 444.3 | 460.2 / 450.4 / 440.6 | 641357.1 | 1833764 | 0.046 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -27.5 | 27.5 | gangway | 1.00 | 5.99 | 459.0 | 455.3 | 387.4 | 2260.0 | 0.015 |
| 2 | -27.5 | 26.5 | gangway | 1.00 | 5.83 | 463.9 | 432.2 | 381.6 | 2157.5 | 0.021 |
| 3 | 28.5 | 27.5 | gangway | 1.00 | 6.02 | 444.8 | 440.2 | 367.1 | 2152.0 | 0.016 |
| 4 | -27.5 | 28.5 | gangway | 1.00 | 5.76 | 461.1 | 458.1 | 383.7 | 2095.4 | 0.017 |
| 5 | -26.5 | -28.5 | gangway | 1.00 | 5.98 | 439.2 | 411.9 | 359.1 | 2084.1 | 0.021 |
| 6 | -27.5 | -27.5 | gangway | 1.00 | 6.00 | 435.7 | 432.2 | 364.9 | 2084.1 | 0.017 |
| 7 | 28.5 | 26.5 | gangway | 1.00 | 5.86 | 447.8 | 440.2 | 365.0 | 2060.4 | 0.022 |
| 8 | -29.5 | -26.5 | gangway | 1.00 | 5.91 | 432.4 | 400.4 | 360.8 | 2059.7 | 0.025 |
| 9 | -26.5 | 27.5 | gangway | 1.00 | 5.90 | 461.9 | 457.2 | 371.0 | 2058.5 | 0.019 |
| 10 | 29.5 | 26.5 | gangway | 1.00 | 6.02 | 446.2 | 407.4 | 347.0 | 2036.4 | 0.024 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 24.5 | 26.5 | seat row | 0.50 | 7.37 | 451.3 | 450.4 | 440.6 | 1537.7 | 0.013 |
| 2 | -24.5 | -26.5 | seat row | 0.50 | 7.28 | 444.8 | 442.3 | 427.1 | 1494.7 | 0.014 |
| 3 | 24.5 | -26.5 | seat row | 0.50 | 7.21 | 447.1 | 442.3 | 428.0 | 1486.0 | 0.013 |
| 4 | 26.5 | 24.5 | seat row | 0.50 | 7.30 | 446.9 | 445.3 | 428.0 | 1483.6 | 0.015 |
| 5 | -26.5 | -24.5 | seat row | 0.50 | 7.31 | 433.6 | 432.4 | 418.7 | 1478.4 | 0.014 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1779; agent-steps of seated agents on another row's clearway: 16805.

## Deposit check

Person-seconds deposited: 3350215.2, of them in excluded cells: 2934.559.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 283142 overlapping pair-steps: p99 0.0026, max 0.0542 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0026 max 0.0542; venue-geometry 1: p99 0.0004 max 0.0004 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 20 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.26 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 588 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
