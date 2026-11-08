# Experiment `M_load100_dt2`

**Task 5.9 stage 4: venue M, 100% load, DT / 2 (DT convergence)**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 15832 agents on 100% of the 15832 seats (spawnSeatedCrowd, seed 1337), buffer N = 16384, 6390 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim), DT / 2.
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 1223511 evaluations, 50828 switches, 0 forced choices).
Capacity: **within design capacity** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-20T23:28:34, 141.0 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.0875 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 2537 | 221.9 |
| t90 | 4920 | 430.3 |
| t100 | 6390 | 558.8 |

t_p: the step by which ceil(p x 15832) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 815 | 0 | 39.9 | 489.1 | 19.2 | 25.5 | 47.9-57.9 |
| -x | 5.66 | 799 | 0 | 39.9 | 486.2 | 19.0 | 25.5 | 47.9-57.9 |
| +y | 5.66 | 800 | 0 | 39.9 | 489.9 | 18.8 | 25.5 | 47.8-57.8 |
| -y | 5.66 | 800 | 0 | 39.9 | 488.8 | 18.9 | 25.5 | 47.8-57.8 |
| door +x+y (y wall) 0 | 1.20 | 615 | 1121 | 4.8 | 509.2 | 60.9 | 90.3 | 13.6-23.6 |
| door +x+y (y wall) 1 | 1.20 | 610 | 680 | 4.8 | 534.1 | 57.6 | 90.3 | 13.7-23.7 |
| door +x+y (y wall) 2 | 1.20 | 312 | 178 | 4.8 | 539.3 | 29.2 | 80.2 | 4.5-14.5 |
| door +x+y (x wall) 0 | 1.20 | 614 | 1121 | 4.8 | 501.5 | 61.8 | 90.3 | 13.6-23.6 |
| door +x+y (x wall) 1 | 1.20 | 610 | 680 | 4.8 | 525.3 | 58.6 | 90.3 | 13.7-23.7 |
| door +x+y (x wall) 2 | 1.20 | 295 | 178 | 4.8 | 544.6 | 27.3 | 80.2 | 4.5-14.5 |
| door +x+y (corner) | 1.20 | 89 | 0 | 81.6 | 547.7 | 9.5 | 65.2 | 373.5-383.5 |
| door -x+y (y wall) 0 | 1.20 | 621 | 1121 | 4.8 | 501.7 | 62.5 | 90.3 | 13.6-23.6 |
| door -x+y (y wall) 1 | 1.20 | 593 | 680 | 4.8 | 521.0 | 57.4 | 90.3 | 13.6-23.6 |
| door -x+y (y wall) 2 | 1.20 | 319 | 178 | 4.8 | 533.6 | 30.2 | 80.2 | 4.5-14.5 |
| door -x+y (x wall) 0 | 1.20 | 606 | 1121 | 4.8 | 488.2 | 62.7 | 90.3 | 13.6-23.6 |
| door -x+y (x wall) 1 | 1.20 | 607 | 680 | 4.8 | 509.5 | 60.1 | 90.3 | 13.6-23.6 |
| door -x+y (x wall) 2 | 1.20 | 271 | 178 | 4.8 | 535.0 | 25.6 | 80.2 | 4.5-14.5 |
| door -x+y (corner) | 1.20 | 143 | 0 | 84.4 | 536.9 | 15.8 | 80.2 | 102.1-112.1 |
| door -x-y (y wall) 0 | 1.20 | 609 | 1121 | 4.8 | 499.8 | 61.5 | 90.3 | 13.6-23.6 |
| door -x-y (y wall) 1 | 1.20 | 591 | 680 | 4.8 | 557.9 | 53.4 | 90.3 | 13.6-23.6 |
| door -x-y (y wall) 2 | 1.20 | 326 | 178 | 4.8 | 537.8 | 30.6 | 85.3 | 20.1-30.1 |
| door -x-y (x wall) 0 | 1.20 | 611 | 1121 | 4.8 | 492.8 | 62.6 | 90.3 | 13.6-23.6 |
| door -x-y (x wall) 1 | 1.20 | 589 | 680 | 4.8 | 558.8 | 53.1 | 90.3 | 13.6-23.6 |
| door -x-y (x wall) 2 | 1.20 | 302 | 178 | 4.8 | 531.3 | 28.7 | 85.3 | 20.1-30.1 |
| door -x-y (corner) | 1.20 | 136 | 0 | 83.9 | 519.9 | 15.6 | 85.3 | 98.6-108.6 |
| door +x-y (y wall) 0 | 1.20 | 614 | 1121 | 4.8 | 502.0 | 61.7 | 90.3 | 13.6-23.6 |
| door +x-y (y wall) 1 | 1.20 | 589 | 680 | 4.8 | 506.9 | 58.6 | 90.3 | 13.6-23.6 |
| door +x-y (y wall) 2 | 1.20 | 330 | 178 | 4.8 | 542.0 | 30.7 | 80.2 | 4.5-14.5 |
| door +x-y (x wall) 0 | 1.20 | 609 | 1121 | 4.8 | 495.8 | 62.0 | 90.3 | 13.6-23.6 |
| door +x-y (x wall) 1 | 1.20 | 601 | 680 | 4.8 | 514.3 | 59.0 | 90.3 | 13.7-23.7 |
| door +x-y (x wall) 2 | 1.20 | 306 | 178 | 4.8 | 540.8 | 28.5 | 80.2 | 4.5-14.5 |
| door +x-y (corner) | 1.20 | 100 | 0 | 82.4 | 544.0 | 10.8 | 65.2 | 362.8-372.8 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 114 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 815 | 5.1% | 18.5% |
| -x | avenue | 5.66 | 799 | 5.0% | 18.1% |
| +y | avenue | 5.66 | 800 | 5.1% | 18.2% |
| -y | avenue | 5.66 | 800 | 5.1% | 18.2% |
| door +x+y (y wall) 0 | door | 1.20 | 615 | 3.9% | 65.8% |
| door +x+y (y wall) 1 | door | 1.20 | 610 | 3.9% | 65.3% |
| door +x+y (y wall) 2 | door | 1.20 | 312 | 2.0% | 33.4% |
| door +x+y (x wall) 0 | door | 1.20 | 614 | 3.9% | 65.7% |
| door +x+y (x wall) 1 | door | 1.20 | 610 | 3.9% | 65.3% |
| door +x+y (x wall) 2 | door | 1.20 | 295 | 1.9% | 31.6% |
| door +x+y (corner) | door | 1.20 | 89 | 0.6% | 9.5% |
| door -x+y (y wall) 0 | door | 1.20 | 621 | 3.9% | 66.5% |
| door -x+y (y wall) 1 | door | 1.20 | 593 | 3.7% | 63.5% |
| door -x+y (y wall) 2 | door | 1.20 | 319 | 2.0% | 34.1% |
| door -x+y (x wall) 0 | door | 1.20 | 606 | 3.8% | 64.9% |
| door -x+y (x wall) 1 | door | 1.20 | 607 | 3.8% | 65.0% |
| door -x+y (x wall) 2 | door | 1.20 | 271 | 1.7% | 29.0% |
| door -x+y (corner) | door | 1.20 | 143 | 0.9% | 15.3% |
| door -x-y (y wall) 0 | door | 1.20 | 609 | 3.8% | 65.2% |
| door -x-y (y wall) 1 | door | 1.20 | 591 | 3.7% | 63.3% |
| door -x-y (y wall) 2 | door | 1.20 | 326 | 2.1% | 34.9% |
| door -x-y (x wall) 0 | door | 1.20 | 611 | 3.9% | 65.4% |
| door -x-y (x wall) 1 | door | 1.20 | 589 | 3.7% | 63.0% |
| door -x-y (x wall) 2 | door | 1.20 | 302 | 1.9% | 32.3% |
| door -x-y (corner) | door | 1.20 | 136 | 0.9% | 14.6% |
| door +x-y (y wall) 0 | door | 1.20 | 614 | 3.9% | 65.7% |
| door +x-y (y wall) 1 | door | 1.20 | 589 | 3.7% | 63.0% |
| door +x-y (y wall) 2 | door | 1.20 | 330 | 2.1% | 35.3% |
| door +x-y (x wall) 0 | door | 1.20 | 609 | 3.8% | 65.2% |
| door +x-y (x wall) 1 | door | 1.20 | 601 | 3.8% | 64.3% |
| door +x-y (x wall) 2 | door | 1.20 | 306 | 1.9% | 32.7% |
| door +x-y (corner) | door | 1.20 | 100 | 0.6% | 10.7% |
| **doors (28)** | door | 33.60 | 12618 | 79.7% | |
| **avenues (4)** | avenue | 22.64 | 3214 | 20.3% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 558.8 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 36.2%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 958 | 6.1% | 958 | 6.1% |
| straight +x+y (y wing) 1 | straight | yes | 615 | 3.9% | 610 | 3.9% |
| straight +x+y (y wing) 2 | straight | yes | 312 | 2.0% | 312 | 2.0% |
| straight +x+y (x wing) 0 | straight | yes | 959 | 6.1% | 959 | 6.1% |
| straight +x+y (x wing) 1 | straight | yes | 612 | 3.9% | 610 | 3.9% |
| straight +x+y (x wing) 2 | straight | yes | 295 | 1.9% | 295 | 1.9% |
| corner +x+y | corner | yes | 763 | 4.8% | 214 | 1.4% |
| straight -x+y (y wing) 0 | straight | yes | 949 | 6.0% | 949 | 6.0% |
| straight -x+y (y wing) 1 | straight | yes | 604 | 3.8% | 599 | 3.8% |
| straight -x+y (y wing) 2 | straight | yes | 313 | 2.0% | 313 | 2.0% |
| straight -x+y (x wing) 0 | straight | yes | 942 | 5.9% | 942 | 5.9% |
| straight -x+y (x wing) 1 | straight | yes | 613 | 3.9% | 607 | 3.8% |
| straight -x+y (x wing) 2 | straight | yes | 271 | 1.7% | 271 | 1.7% |
| corner -x+y | corner | yes | 791 | 5.0% | 277 | 1.7% |
| straight -x-y (y wing) 0 | straight | yes | 943 | 6.0% | 943 | 6.0% |
| straight -x-y (y wing) 1 | straight | yes | 615 | 3.9% | 609 | 3.8% |
| straight -x-y (y wing) 2 | straight | yes | 308 | 1.9% | 308 | 1.9% |
| straight -x-y (x wing) 0 | straight | yes | 942 | 5.9% | 942 | 5.9% |
| straight -x-y (x wing) 1 | straight | yes | 613 | 3.9% | 604 | 3.8% |
| straight -x-y (x wing) 2 | straight | yes | 287 | 1.8% | 287 | 1.8% |
| corner -x-y | corner | yes | 790 | 5.0% | 265 | 1.7% |
| straight +x-y (y wing) 0 | straight | yes | 947 | 6.0% | 947 | 6.0% |
| straight +x-y (y wing) 1 | straight | yes | 612 | 3.9% | 608 | 3.8% |
| straight +x-y (y wing) 2 | straight | yes | 311 | 2.0% | 311 | 2.0% |
| straight +x-y (x wing) 0 | straight | yes | 948 | 6.0% | 948 | 6.0% |
| straight +x-y (x wing) 1 | straight | yes | 611 | 3.9% | 606 | 3.8% |
| straight +x-y (x wing) 2 | straight | yes | 301 | 1.9% | 301 | 1.9% |
| corner +x-y | corner | yes | 777 | 4.9% | 237 | 1.5% |
| **straight (24)** | | | 14881 | | 14839 | 93.7% |
| **corner (4)** | | | 3121 | | 993 | 6.3% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 114 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 815 | 39.9 | 489.1 | 0.23 | 0.31 | 0.0% |
| -x | 799 | 39.9 | 486.2 | 0.23 | 0.31 | 0.0% |
| +y | 800 | 39.9 | 489.9 | 0.23 | 0.31 | 0.0% |
| -y | 800 | 39.9 | 488.8 | 0.23 | 0.31 | 0.0% |
| door +x+y (y wall) 0 | 615 | 4.8 | 509.2 | 0.73 | 1.08 | 38.5% |
| door +x+y (y wall) 1 | 610 | 4.8 | 534.1 | 0.69 | 1.08 | 33.3% |
| door +x+y (y wall) 2 | 312 | 4.8 | 539.3 | 0.35 | 0.96 | 5.5% |
| door +x+y (x wall) 0 | 614 | 4.8 | 501.5 | 0.74 | 1.08 | 39.2% |
| door +x+y (x wall) 1 | 610 | 4.8 | 525.3 | 0.70 | 1.08 | 30.2% |
| door +x+y (x wall) 2 | 295 | 4.8 | 544.6 | 0.33 | 0.96 | 7.3% |
| door +x+y (corner) | 89 | 81.6 | 547.7 | 0.11 | 0.78 | 0.0% |
| door -x+y (y wall) 0 | 621 | 4.8 | 501.7 | 0.75 | 1.08 | 45.1% |
| door -x+y (y wall) 1 | 593 | 4.8 | 521.0 | 0.69 | 1.08 | 24.5% |
| door -x+y (y wall) 2 | 319 | 4.8 | 533.6 | 0.36 | 0.96 | 3.7% |
| door -x+y (x wall) 0 | 606 | 4.8 | 488.2 | 0.75 | 1.08 | 32.7% |
| door -x+y (x wall) 1 | 607 | 4.8 | 509.5 | 0.72 | 1.08 | 23.1% |
| door -x+y (x wall) 2 | 271 | 4.8 | 535.0 | 0.31 | 0.96 | 5.6% |
| door -x+y (corner) | 143 | 84.4 | 536.9 | 0.19 | 0.96 | 2.2% |
| door -x-y (y wall) 0 | 609 | 4.8 | 499.8 | 0.74 | 1.08 | 43.1% |
| door -x-y (y wall) 1 | 591 | 4.8 | 557.9 | 0.64 | 1.08 | 30.4% |
| door -x-y (y wall) 2 | 326 | 4.8 | 537.8 | 0.37 | 1.02 | 5.6% |
| door -x-y (x wall) 0 | 611 | 4.8 | 492.8 | 0.75 | 1.08 | 38.0% |
| door -x-y (x wall) 1 | 589 | 4.8 | 558.8 | 0.64 | 1.08 | 22.8% |
| door -x-y (x wall) 2 | 302 | 4.8 | 531.3 | 0.34 | 1.02 | 5.6% |
| door -x-y (corner) | 136 | 83.9 | 519.9 | 0.19 | 1.02 | 4.4% |
| door +x-y (y wall) 0 | 614 | 4.8 | 502.0 | 0.74 | 1.08 | 33.3% |
| door +x-y (y wall) 1 | 589 | 4.8 | 506.9 | 0.70 | 1.08 | 27.5% |
| door +x-y (y wall) 2 | 330 | 4.8 | 542.0 | 0.37 | 0.96 | 5.5% |
| door +x-y (x wall) 0 | 609 | 4.8 | 495.8 | 0.74 | 1.08 | 30.0% |
| door +x-y (x wall) 1 | 601 | 4.8 | 514.3 | 0.71 | 1.08 | 26.9% |
| door +x-y (x wall) 2 | 306 | 4.8 | 540.8 | 0.34 | 0.96 | 5.5% |
| door +x-y (corner) | 100 | 82.4 | 544.0 | 0.13 | 0.78 | 0.0% |

Mean flow / w J averaged over the doors 0.53, over the avenues 0.23.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 958 | 615 / 343 / 109 | 0.7 | 506.4 | 2.11 | 3.01 | 90% | 80% | 10% | 3.74 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 576 | 610 / 0 / 5 | 0.7 | 531.2 | 1.16 | 1.71 | 80% | 65% | 15% | 3.51 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 70 | 312 / 0 / 0 | 0.7 | 536.4 | 0.58 | 1.60 | 13% | 9% | 4% | 2.62 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 959 | 614 / 345 / 108 | 0.7 | 498.7 | 2.14 | 2.91 | 90% | 78% | 12% | 3.70 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 568 | 610 / 0 / 5 | 0.7 | 522.5 | 1.18 | 1.71 | 79% | 62% | 17% | 3.43 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 70 | 295 / 0 / 0 | 0.7 | 541.8 | 0.55 | 1.60 | 13% | 11% | 2% | 2.64 |
| corner +x+y | 1.20 | 85.6 | 757 | 89 / 125 / 553 | 0.7 | 544.0 | 1.41 | 3.41 | 85% | 62% | 24% | 2.46 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 949 | 621 / 328 / 87 | 0.7 | 498.9 | 2.08 | 3.01 | 90% | 78% | 12% | 3.76 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 572 | 599 / 0 / 10 | 0.7 | 518.1 | 1.18 | 1.81 | 83% | 69% | 13% | 3.57 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 70 | 313 / 0 / 0 | 0.7 | 530.8 | 0.59 | 1.60 | 11% | 11% | 0% | 2.85 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 942 | 606 / 336 / 97 | 0.7 | 485.4 | 2.14 | 2.91 | 84% | 82% | 2% | 4.03 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 575 | 607 / 0 / 9 | 0.7 | 506.6 | 1.22 | 1.71 | 82% | 67% | 16% | 3.51 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 70 | 271 / 0 / 0 | 0.7 | 532.2 | 0.51 | 1.60 | 13% | 9% | 4% | 2.62 |
| corner -x+y | 1.20 | 85.6 | 780 | 143 / 134 / 522 | 0.7 | 533.1 | 1.50 | 3.91 | 83% | 46% | 37% | 2.28 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 943 | 609 / 334 / 91 | 0.7 | 497.0 | 2.08 | 3.01 | 86% | 80% | 6% | 3.89 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 577 | 609 / 0 / 8 | 0.7 | 555.1 | 1.11 | 1.71 | 77% | 66% | 11% | 3.47 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 70 | 308 / 0 / 0 | 0.7 | 535.0 | 0.58 | 1.60 | 13% | 9% | 4% | 2.52 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 942 | 611 / 331 / 116 | 0.7 | 490.0 | 2.16 | 2.91 | 90% | 80% | 10% | 3.74 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 577 | 604 / 0 / 13 | 0.7 | 556.0 | 1.11 | 1.81 | 75% | 64% | 11% | 3.63 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 70 | 287 / 0 / 0 | 0.7 | 528.5 | 0.54 | 1.60 | 13% | 9% | 4% | 2.51 |
| corner -x-y | 1.20 | 85.6 | 779 | 136 / 129 / 535 | 0.7 | 529.0 | 1.51 | 4.11 | 94% | 52% | 43% | 2.11 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 947 | 614 / 334 / 87 | 0.7 | 499.1 | 2.08 | 2.81 | 90% | 78% | 12% | 3.75 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 577 | 608 / 0 / 6 | 0.7 | 504.1 | 1.22 | 1.71 | 82% | 69% | 14% | 3.60 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 70 | 311 / 0 / 0 | 0.7 | 539.2 | 0.58 | 1.60 | 11% | 11% | 0% | 2.79 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 948 | 609 / 339 / 98 | 0.7 | 493.0 | 2.12 | 3.01 | 90% | 80% | 10% | 3.81 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 577 | 606 / 0 / 5 | 0.7 | 511.5 | 1.20 | 1.71 | 87% | 67% | 19% | 3.42 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 70 | 301 / 0 / 0 | 0.7 | 538.0 | 0.56 | 1.60 | 11% | 11% | 0% | 2.83 |
| corner +x-y | 1.20 | 85.6 | 769 | 100 / 137 / 543 | 0.7 | 540.2 | 1.45 | 3.81 | 84% | 47% | 36% | 2.30 |

The last agent out (agent 10305, t100 558.8 s): last gangway straight -x-y (x wing) 1, exit door -x-y (x wall) 1. The gangway that cleared last: straight -x-y (x wing) 1 at 556.0 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.67 | 537.8 / 526.0 / 480.7 | 525.2 / 498.7 / 422.2 | 654884.2 | 1565281 | 0.220 |
| gangway | 1212 | 1112.9 | 6.67 | 535.7 / 520.2 / 454.8 | 525.2 / 498.7 / 422.2 | 654502.9 | 1415953 | 0.112 |
| walkway | 276 | 257.4 | 3.16 | 163.9 / 89.7 / 0.0 | 112.0 / 31.3 / 0.0 | 0.0 | 24110 | 0.929 |
| avenue | 912 | 858.9 | 1.66 | 183.5 / 0.0 / 0.0 | 163.0 / 0.0 / 0.0 | 0.0 | 92217 | 1.328 |
| exit | 32 | 3.2 | 0.00 | 509.8 / 497.1 / 322.2 | 212.2 / 172.3 / 64.7 | 381.3 | 1104 | 1.321 |
| concourse | 1116 | 1043.8 | 1.90 | 491.8 / 0.0 / 0.0 | 123.5 / 0.0 / 0.0 | 0.0 | 31896 | 1.204 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.63 | 516.1 / 468.3 / 451.9 | 515.1 / 468.3 / 448.3 | 754240.8 | 2093496 | 0.042 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 27.5 | 28.5 | gangway | 1.00 | 6.18 | 461.7 | 445.1 | 385.9 | 2246.3 | 0.020 |
| 2 | 29.5 | -26.5 | gangway | 1.00 | 6.19 | 472.9 | 438.0 | 383.7 | 2231.0 | 0.021 |
| 3 | 26.5 | 28.5 | gangway | 1.00 | 6.05 | 460.1 | 452.3 | 398.8 | 2228.3 | 0.018 |
| 4 | 26.5 | 29.5 | gangway | 1.00 | 5.97 | 463.8 | 439.8 | 386.6 | 2201.3 | 0.021 |
| 5 | 28.5 | 26.5 | gangway | 1.00 | 5.89 | 462.5 | 446.3 | 385.8 | 2164.0 | 0.019 |
| 6 | -26.5 | 29.5 | gangway | 1.00 | 6.09 | 440.9 | 424.4 | 362.9 | 2150.6 | 0.019 |
| 7 | -28.5 | -26.5 | gangway | 1.00 | 6.07 | 450.1 | 440.0 | 369.3 | 2145.5 | 0.022 |
| 8 | 27.5 | 27.5 | gangway | 1.00 | 5.83 | 473.7 | 461.2 | 392.0 | 2128.7 | 0.020 |
| 9 | 28.5 | -26.5 | gangway | 1.00 | 5.99 | 471.0 | 457.4 | 361.6 | 2104.4 | 0.021 |
| 10 | 28.5 | 27.5 | gangway | 1.00 | 5.69 | 469.3 | 453.5 | 377.8 | 2097.0 | 0.021 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 26.5 | 24.5 | seat row | 0.50 | 7.22 | 473.4 | 468.3 | 448.3 | 1564.7 | 0.012 |
| 2 | 24.5 | -26.5 | seat row | 0.50 | 7.21 | 457.6 | 453.7 | 445.5 | 1547.0 | 0.014 |
| 3 | 26.5 | -24.5 | seat row | 0.50 | 7.40 | 459.0 | 457.8 | 438.1 | 1535.7 | 0.014 |
| 4 | -24.5 | 26.5 | seat row | 0.50 | 7.23 | 456.6 | 455.0 | 443.7 | 1533.8 | 0.015 |
| 5 | -26.5 | -24.5 | seat row | 0.50 | 7.33 | 465.1 | 460.7 | 443.2 | 1523.5 | 0.016 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 794; agent-steps of seated agents on another row's clearway: 12867.

## Deposit check

Person-seconds deposited: 3660808.0, of them in excluded cells: 2030.963.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 475292 overlapping pair-steps: p99 0.0026, max 0.0056 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0026 max 0.0056; venue-geometry 1: p99 0.0002 max 0.0002 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00375 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 14449 (longest 7 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.19 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 488 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
