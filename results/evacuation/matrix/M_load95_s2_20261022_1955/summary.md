# Experiment `M_load95_s2`

**Task 5.10 stage 4 (AMD 26.10.1): venue M, 95% load (seed 2), default model**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 15040 agents on 95% of the 15832 seats (spawnSeatedCrowd, seed 2), buffer N = 16384, 3039 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 1118324 evaluations, 46424 switches, 0 forced choices).
Capacity: **within design capacity** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T19:55:57, 113.3 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1225 | 214.3 |
| t90 | 2356 | 412.1 |
| t100 | 3039 | 531.5 |

t_p: the step by which ceil(p x 15040) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 780 | 0 | 39.7 | 468.9 | 19.3 | 26.6 | 107.6-117.5 |
| -x | 5.66 | 776 | 0 | 39.5 | 459.5 | 19.6 | 25.5 | 51.2-61.2 |
| +y | 5.66 | 779 | 0 | 39.7 | 463.7 | 19.5 | 25.5 | 50.4-60.3 |
| -y | 5.66 | 774 | 0 | 39.5 | 465.3 | 19.3 | 25.5 | 70.3-80.3 |
| door +x+y (y wall) 0 | 1.20 | 579 | 1065 | 4.9 | 482.9 | 60.5 | 85.3 | 22.9-32.9 |
| door +x+y (y wall) 1 | 1.20 | 581 | 646 | 4.9 | 490.6 | 59.8 | 80.2 | 10.1-20.1 |
| door +x+y (y wall) 2 | 1.20 | 283 | 169 | 4.9 | 499.7 | 28.6 | 80.2 | 4.5-14.5 |
| door +x+y (x wall) 0 | 1.20 | 585 | 1071 | 4.9 | 483.4 | 61.1 | 90.3 | 21.2-31.1 |
| door +x+y (x wall) 1 | 1.20 | 571 | 650 | 4.9 | 491.0 | 58.7 | 85.3 | 11.4-21.3 |
| door +x+y (x wall) 2 | 1.20 | 291 | 170 | 4.9 | 515.6 | 28.5 | 80.2 | 4.7-14.7 |
| door +x+y (corner) | 1.20 | 93 | 0 | 78.5 | 510.9 | 10.8 | 60.2 | 81.3-91.3 |
| door -x+y (y wall) 0 | 1.20 | 588 | 1082 | 4.9 | 479.4 | 61.9 | 85.3 | 7.3-17.3 |
| door -x+y (y wall) 1 | 1.20 | 586 | 648 | 4.9 | 499.5 | 59.2 | 85.3 | 32.0-42.0 |
| door -x+y (y wall) 2 | 1.20 | 270 | 167 | 4.9 | 513.4 | 26.5 | 80.2 | 11.0-21.0 |
| door -x+y (x wall) 0 | 1.20 | 587 | 1051 | 4.9 | 505.5 | 58.6 | 90.3 | 17.3-27.3 |
| door -x+y (x wall) 1 | 1.20 | 577 | 643 | 4.9 | 501.3 | 58.1 | 85.3 | 27.5-37.4 |
| door -x+y (x wall) 2 | 1.20 | 271 | 166 | 4.9 | 509.3 | 26.9 | 80.2 | 4.7-14.7 |
| door -x+y (corner) | 1.20 | 101 | 0 | 71.4 | 517.9 | 11.3 | 80.2 | 337.9-347.9 |
| door -x-y (y wall) 0 | 1.20 | 585 | 1060 | 4.9 | 487.1 | 60.6 | 85.3 | 10.1-20.1 |
| door -x-y (y wall) 1 | 1.20 | 562 | 641 | 4.9 | 490.3 | 57.9 | 90.3 | 24.5-34.5 |
| door -x-y (y wall) 2 | 1.20 | 283 | 171 | 4.9 | 531.5 | 26.9 | 80.2 | 4.7-14.7 |
| door -x-y (x wall) 0 | 1.20 | 584 | 1063 | 4.9 | 484.1 | 60.9 | 85.3 | 25.0-35.0 |
| door -x-y (x wall) 1 | 1.20 | 559 | 650 | 4.9 | 490.3 | 57.6 | 80.2 | 7.3-17.3 |
| door -x-y (x wall) 2 | 1.20 | 291 | 170 | 4.9 | 526.8 | 27.9 | 85.3 | 8.7-18.7 |
| door -x-y (corner) | 1.20 | 118 | 0 | 66.5 | 519.5 | 13.0 | 90.3 | 376.2-386.2 |
| door +x-y (y wall) 0 | 1.20 | 580 | 1064 | 4.9 | 483.4 | 60.6 | 90.3 | 6.1-16.1 |
| door +x-y (y wall) 1 | 1.20 | 571 | 639 | 4.9 | 507.2 | 56.8 | 85.3 | 9.8-19.8 |
| door +x-y (y wall) 2 | 1.20 | 304 | 164 | 4.9 | 514.6 | 29.8 | 85.3 | 14.7-24.7 |
| door +x-y (x wall) 0 | 1.20 | 581 | 1071 | 4.9 | 491.5 | 59.7 | 85.3 | 25.7-35.7 |
| door +x-y (x wall) 1 | 1.20 | 583 | 648 | 4.9 | 514.8 | 57.2 | 85.3 | 9.8-19.8 |
| door +x-y (x wall) 2 | 1.20 | 256 | 171 | 4.9 | 515.3 | 25.1 | 85.3 | 9.1-19.1 |
| door +x-y (corner) | 1.20 | 111 | 0 | 41.3 | 521.4 | 11.6 | 70.2 | 402.8-412.8 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 780 | 5.2% | 18.6% |
| -x | avenue | 5.66 | 776 | 5.2% | 18.5% |
| +y | avenue | 5.66 | 779 | 5.2% | 18.6% |
| -y | avenue | 5.66 | 774 | 5.1% | 18.5% |
| door +x+y (y wall) 0 | door | 1.20 | 579 | 3.8% | 65.1% |
| door +x+y (y wall) 1 | door | 1.20 | 581 | 3.9% | 65.4% |
| door +x+y (y wall) 2 | door | 1.20 | 283 | 1.9% | 31.8% |
| door +x+y (x wall) 0 | door | 1.20 | 585 | 3.9% | 65.8% |
| door +x+y (x wall) 1 | door | 1.20 | 571 | 3.8% | 64.2% |
| door +x+y (x wall) 2 | door | 1.20 | 291 | 1.9% | 32.7% |
| door +x+y (corner) | door | 1.20 | 93 | 0.6% | 10.5% |
| door -x+y (y wall) 0 | door | 1.20 | 588 | 3.9% | 66.2% |
| door -x+y (y wall) 1 | door | 1.20 | 586 | 3.9% | 65.9% |
| door -x+y (y wall) 2 | door | 1.20 | 270 | 1.8% | 30.4% |
| door -x+y (x wall) 0 | door | 1.20 | 587 | 3.9% | 66.0% |
| door -x+y (x wall) 1 | door | 1.20 | 577 | 3.8% | 64.9% |
| door -x+y (x wall) 2 | door | 1.20 | 271 | 1.8% | 30.5% |
| door -x+y (corner) | door | 1.20 | 101 | 0.7% | 11.4% |
| door -x-y (y wall) 0 | door | 1.20 | 585 | 3.9% | 65.8% |
| door -x-y (y wall) 1 | door | 1.20 | 562 | 3.7% | 63.2% |
| door -x-y (y wall) 2 | door | 1.20 | 283 | 1.9% | 31.8% |
| door -x-y (x wall) 0 | door | 1.20 | 584 | 3.9% | 65.7% |
| door -x-y (x wall) 1 | door | 1.20 | 559 | 3.7% | 62.9% |
| door -x-y (x wall) 2 | door | 1.20 | 291 | 1.9% | 32.7% |
| door -x-y (corner) | door | 1.20 | 118 | 0.8% | 13.3% |
| door +x-y (y wall) 0 | door | 1.20 | 580 | 3.9% | 65.3% |
| door +x-y (y wall) 1 | door | 1.20 | 571 | 3.8% | 64.2% |
| door +x-y (y wall) 2 | door | 1.20 | 304 | 2.0% | 34.2% |
| door +x-y (x wall) 0 | door | 1.20 | 581 | 3.9% | 65.4% |
| door +x-y (x wall) 1 | door | 1.20 | 583 | 3.9% | 65.6% |
| door +x-y (x wall) 2 | door | 1.20 | 256 | 1.7% | 28.8% |
| door +x-y (corner) | door | 1.20 | 111 | 0.7% | 12.5% |
| **doors (28)** | door | 33.60 | 11931 | 79.3% | |
| **avenues (4)** | avenue | 22.64 | 3109 | 20.7% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 531.5 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 36.1%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 905 | 6.0% | 905 | 6.0% |
| straight +x+y (y wing) 1 | straight | yes | 584 | 3.9% | 581 | 3.9% |
| straight +x+y (y wing) 2 | straight | yes | 283 | 1.9% | 283 | 1.9% |
| straight +x+y (x wing) 0 | straight | yes | 908 | 6.0% | 908 | 6.0% |
| straight +x+y (x wing) 1 | straight | yes | 579 | 3.8% | 571 | 3.8% |
| straight +x+y (x wing) 2 | straight | yes | 291 | 1.9% | 291 | 1.9% |
| corner +x+y | corner | yes | 766 | 5.1% | 232 | 1.5% |
| straight -x+y (y wing) 0 | straight | yes | 916 | 6.1% | 916 | 6.1% |
| straight -x+y (y wing) 1 | straight | yes | 587 | 3.9% | 586 | 3.9% |
| straight -x+y (y wing) 2 | straight | yes | 269 | 1.8% | 269 | 1.8% |
| straight -x+y (x wing) 0 | straight | yes | 900 | 6.0% | 900 | 6.0% |
| straight -x+y (x wing) 1 | straight | yes | 583 | 3.9% | 578 | 3.8% |
| straight -x+y (x wing) 2 | straight | yes | 271 | 1.8% | 271 | 1.8% |
| corner -x+y | corner | yes | 736 | 4.9% | 237 | 1.6% |
| straight -x-y (y wing) 0 | straight | yes | 901 | 6.0% | 901 | 6.0% |
| straight -x-y (y wing) 1 | straight | yes | 567 | 3.8% | 562 | 3.7% |
| straight -x-y (y wing) 2 | straight | yes | 283 | 1.9% | 283 | 1.9% |
| straight -x-y (x wing) 0 | straight | yes | 910 | 6.1% | 910 | 6.1% |
| straight -x-y (x wing) 1 | straight | yes | 571 | 3.8% | 564 | 3.8% |
| straight -x-y (x wing) 2 | straight | yes | 286 | 1.9% | 286 | 1.9% |
| corner -x-y | corner | yes | 749 | 5.0% | 249 | 1.7% |
| straight +x-y (y wing) 0 | straight | yes | 898 | 6.0% | 898 | 6.0% |
| straight +x-y (y wing) 1 | straight | yes | 585 | 3.9% | 580 | 3.9% |
| straight +x-y (y wing) 2 | straight | yes | 296 | 2.0% | 296 | 2.0% |
| straight +x-y (x wing) 0 | straight | yes | 908 | 6.0% | 908 | 6.0% |
| straight +x-y (x wing) 1 | straight | yes | 587 | 3.9% | 583 | 3.9% |
| straight +x-y (x wing) 2 | straight | yes | 256 | 1.7% | 256 | 1.7% |
| corner +x-y | corner | yes | 768 | 5.1% | 236 | 1.6% |
| **straight (24)** | | | 14124 | | 14086 | 93.7% |
| **corner (4)** | | | 3019 | | 954 | 6.3% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 780 | 39.7 | 468.9 | 0.23 | 0.32 | 0.0% |
| -x | 776 | 39.5 | 459.5 | 0.23 | 0.31 | 0.0% |
| +y | 779 | 39.7 | 463.7 | 0.23 | 0.31 | 0.0% |
| -y | 774 | 39.5 | 465.3 | 0.23 | 0.31 | 0.0% |
| door +x+y (y wall) 0 | 579 | 4.9 | 482.9 | 0.72 | 1.02 | 28.6% |
| door +x+y (y wall) 1 | 581 | 4.9 | 490.6 | 0.72 | 0.96 | 28.0% |
| door +x+y (y wall) 2 | 283 | 4.9 | 499.7 | 0.34 | 0.96 | 5.9% |
| door +x+y (x wall) 0 | 585 | 4.9 | 483.4 | 0.73 | 1.08 | 38.8% |
| door +x+y (x wall) 1 | 571 | 4.9 | 491.0 | 0.70 | 1.02 | 28.0% |
| door +x+y (x wall) 2 | 291 | 4.9 | 515.6 | 0.34 | 0.96 | 3.8% |
| door +x+y (corner) | 93 | 78.5 | 510.9 | 0.13 | 0.72 | 0.0% |
| door -x+y (y wall) 0 | 588 | 4.9 | 479.4 | 0.74 | 1.02 | 36.7% |
| door -x+y (y wall) 1 | 586 | 4.9 | 499.5 | 0.71 | 1.02 | 31.4% |
| door -x+y (y wall) 2 | 270 | 4.9 | 513.4 | 0.32 | 0.96 | 5.8% |
| door -x+y (x wall) 0 | 587 | 4.9 | 505.5 | 0.70 | 1.08 | 37.3% |
| door -x+y (x wall) 1 | 577 | 4.9 | 501.3 | 0.69 | 1.02 | 25.5% |
| door -x+y (x wall) 2 | 271 | 4.9 | 509.3 | 0.32 | 0.96 | 7.7% |
| door -x+y (corner) | 101 | 71.4 | 517.9 | 0.14 | 0.96 | 2.2% |
| door -x-y (y wall) 0 | 585 | 4.9 | 487.1 | 0.73 | 1.02 | 30.6% |
| door -x-y (y wall) 1 | 562 | 4.9 | 490.3 | 0.69 | 1.08 | 26.0% |
| door -x-y (y wall) 2 | 283 | 4.9 | 531.5 | 0.32 | 0.96 | 3.7% |
| door -x-y (x wall) 0 | 584 | 4.9 | 484.1 | 0.73 | 1.02 | 42.9% |
| door -x-y (x wall) 1 | 559 | 4.9 | 490.3 | 0.69 | 0.96 | 26.0% |
| door -x-y (x wall) 2 | 291 | 4.9 | 526.8 | 0.33 | 1.02 | 7.5% |
| door -x-y (corner) | 118 | 66.5 | 519.5 | 0.16 | 1.08 | 2.1% |
| door +x-y (y wall) 0 | 580 | 4.9 | 483.4 | 0.72 | 1.08 | 28.6% |
| door +x-y (y wall) 1 | 571 | 4.9 | 507.2 | 0.68 | 1.02 | 35.3% |
| door +x-y (y wall) 2 | 304 | 4.9 | 514.6 | 0.36 | 1.02 | 5.8% |
| door +x-y (x wall) 0 | 581 | 4.9 | 491.5 | 0.71 | 1.02 | 38.0% |
| door +x-y (x wall) 1 | 583 | 4.9 | 514.8 | 0.68 | 1.02 | 26.9% |
| door +x-y (x wall) 2 | 256 | 4.9 | 515.3 | 0.30 | 1.02 | 5.8% |
| door +x-y (corner) | 111 | 41.3 | 521.4 | 0.14 | 0.84 | 0.0% |

Mean flow / w J averaged over the doors 0.52, over the avenues 0.23.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 905 | 579 / 326 / 184 | 0.7 | 479.9 | 2.27 | 3.41 | 90% | 78% | 12% | 3.69 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 532 | 581 / 0 / 11 | 0.7 | 487.6 | 1.22 | 1.60 | 82% | 63% | 18% | 3.42 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 64 | 283 / 0 / 0 | 0.7 | 496.9 | 0.57 | 1.50 | 12% | 10% | 2% | 2.58 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 908 | 585 / 323 / 215 | 0.7 | 480.5 | 2.34 | 3.71 | 88% | 78% | 10% | 3.89 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 538 | 571 / 0 / 12 | 0.7 | 488.0 | 1.20 | 1.81 | 82% | 65% | 16% | 3.60 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 66 | 291 / 0 / 0 | 0.7 | 512.7 | 0.57 | 1.50 | 12% | 8% | 4% | 2.59 |
| corner +x+y | 1.20 | 85.6 | 758 | 93 / 139 / 549 | 0.7 | 507.1 | 1.54 | 4.11 | 86% | 53% | 33% | 2.38 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 916 | 588 / 328 / 232 | 0.7 | 476.4 | 2.41 | 4.11 | 90% | 79% | 10% | 3.76 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 547 | 586 / 0 / 4 | 0.7 | 496.6 | 1.19 | 1.60 | 86% | 68% | 18% | 3.46 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 63 | 269 / 0 / 0 | 0.7 | 510.4 | 0.53 | 1.50 | 12% | 8% | 4% | 2.54 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 900 | 586 / 314 / 194 | 0.7 | 470.3 | 2.33 | 3.71 | 88% | 77% | 10% | 3.84 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 534 | 578 / 0 / 9 | 0.7 | 498.3 | 1.18 | 1.71 | 80% | 66% | 14% | 3.49 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 67 | 271 / 0 / 0 | 0.7 | 506.4 | 0.54 | 1.60 | 12% | 12% | 0% | 2.72 |
| corner -x+y | 1.20 | 85.6 | 730 | 102 / 135 / 506 | 0.7 | 514.1 | 1.45 | 4.41 | 85% | 58% | 27% | 2.46 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 901 | 585 / 316 / 177 | 0.7 | 484.1 | 2.23 | 3.61 | 90% | 78% | 12% | 3.75 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 536 | 562 / 0 / 9 | 0.7 | 487.3 | 1.17 | 1.81 | 84% | 67% | 16% | 3.39 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 66 | 283 / 0 / 0 | 0.7 | 528.6 | 0.54 | 1.50 | 11% | 9% | 2% | 2.63 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 910 | 584 / 326 / 218 | 0.7 | 481.2 | 2.35 | 3.71 | 80% | 78% | 2% | 4.08 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 533 | 564 / 0 / 10 | 0.7 | 487.3 | 1.18 | 1.60 | 84% | 67% | 16% | 3.48 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 67 | 286 / 0 / 0 | 0.7 | 523.8 | 0.55 | 1.71 | 11% | 9% | 2% | 2.74 |
| corner -x-y | 1.20 | 85.6 | 742 | 118 / 131 / 512 | 0.7 | 522.6 | 1.46 | 3.81 | 83% | 53% | 30% | 2.36 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 898 | 580 / 318 / 213 | 0.7 | 480.5 | 2.31 | 4.21 | 90% | 78% | 12% | 3.82 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 527 | 580 / 0 / 7 | 0.7 | 504.4 | 1.16 | 1.60 | 73% | 65% | 8% | 3.66 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 63 | 296 / 0 / 0 | 0.7 | 511.6 | 0.58 | 1.60 | 10% | 10% | 0% | 2.69 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 908 | 581 / 327 / 246 | 0.7 | 488.5 | 2.36 | 4.01 | 92% | 76% | 16% | 3.61 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 536 | 583 / 0 / 7 | 0.7 | 511.8 | 1.15 | 1.91 | 75% | 63% | 12% | 3.52 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 64 | 256 / 0 / 1 | 0.7 | 512.3 | 0.50 | 1.60 | 10% | 8% | 2% | 2.60 |
| corner +x-y | 1.20 | 85.6 | 761 | 110 / 126 / 540 | 0.7 | 517.7 | 1.50 | 3.51 | 88% | 62% | 27% | 2.44 |

The last agent out (agent 7984, t100 531.5 s): last gangway straight -x-y (y wing) 2, exit door -x-y (y wall) 2. The gangway that cleared last: straight -x-y (y wing) 2 at 528.6 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.82 | 521.0 / 516.0 / 487.5 | 509.0 / 469.1 / 409.6 | 644037.0 | 1505749 | 0.218 |
| gangway | 1212 | 1112.9 | 6.82 | 519.8 / 508.1 / 432.4 | 509.0 / 469.1 / 409.6 | 643202.0 | 1361219 | 0.111 |
| walkway | 276 | 257.4 | 3.17 | 183.1 / 104.8 / 0.0 | 113.2 / 19.6 / 0.0 | 0.0 | 23649 | 0.919 |
| avenue | 912 | 858.9 | 1.84 | 198.9 / 0.0 / 0.0 | 166.2 / 0.0 / 0.0 | 0.0 | 89254 | 1.327 |
| exit | 32 | 3.2 | 0.00 | 507.9 / 505.5 / 455.3 | 245.7 / 219.9 / 131.7 | 835.0 | 1572 | 1.323 |
| concourse | 1116 | 1043.8 | 2.07 | 473.6 / 0.0 / 0.0 | 121.6 / 0.0 / 0.0 | 0.0 | 30054 | 1.194 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.60 | 467.0 / 441.6 / 433.6 | 453.4 / 441.6 / 429.9 | 651733.4 | 1837563 | 0.046 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -26.5 | 29.5 | gangway | 1.00 | 6.28 | 438.5 | 410.5 | 374.5 | 2274.2 | 0.020 |
| 2 | -29.5 | 26.5 | gangway | 1.00 | 6.28 | 434.6 | 404.7 | 370.1 | 2204.8 | 0.023 |
| 3 | -28.5 | 26.5 | gangway | 1.00 | 6.36 | 459.7 | 415.9 | 365.2 | 2191.3 | 0.022 |
| 4 | 28.5 | -27.5 | gangway | 1.00 | 5.97 | 473.3 | 469.1 | 373.8 | 2153.2 | 0.020 |
| 5 | -27.5 | 27.5 | gangway | 1.00 | 5.96 | 447.2 | 443.6 | 377.6 | 2144.0 | 0.016 |
| 6 | 27.5 | -26.5 | gangway | 1.00 | 6.02 | 469.8 | 452.1 | 375.2 | 2124.5 | 0.021 |
| 7 | -27.5 | -27.5 | gangway | 1.00 | 6.08 | 445.0 | 441.8 | 365.2 | 2118.7 | 0.019 |
| 8 | 27.5 | -27.5 | gangway | 1.00 | 5.87 | 466.1 | 459.1 | 380.1 | 2102.5 | 0.019 |
| 9 | 28.5 | -26.5 | gangway | 1.00 | 6.29 | 469.6 | 444.3 | 350.2 | 2095.2 | 0.024 |
| 10 | -26.5 | -28.5 | gangway | 1.00 | 6.15 | 447.9 | 435.5 | 355.4 | 2090.4 | 0.018 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 26.5 | 24.5 | seat row | 0.50 | 7.25 | 443.2 | 441.6 | 429.9 | 1513.1 | 0.014 |
| 2 | 30.5 | 25.5 | seat row | 0.64 | 6.84 | 399.0 | 391.6 | 351.7 | 1455.4 | 0.026 |
| 3 | 24.5 | 26.5 | seat row | 0.50 | 7.20 | 434.6 | 433.6 | 425.5 | 1449.5 | 0.016 |
| 4 | -25.5 | 29.5 | seat row | 0.71 | 5.70 | 429.2 | 426.4 | 364.7 | 1442.4 | 0.020 |
| 5 | -24.5 | -26.5 | seat row | 0.50 | 7.35 | 440.9 | 438.0 | 415.1 | 1436.9 | 0.014 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1678; agent-steps of seated agents on another row's clearway: 14053.

## Deposit check

Person-seconds deposited: 3346251.6, of them in excluded cells: 2940.409.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 310563 overlapping pair-steps: p99 0.0026, max 0.0243 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0026 max 0.0243; venue-geometry 4: p99 0.0005 max 0.0005 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00763 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 14 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.36 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 559 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
