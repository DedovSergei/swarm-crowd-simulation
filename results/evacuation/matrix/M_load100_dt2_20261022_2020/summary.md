# Experiment `M_load100_dt2`

**Task 5.10 stage 4 (AMD 26.10.1): venue M, 100% load, DT / 2 (DT convergence)**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 15832 agents on 100% of the 15832 seats (spawnSeatedCrowd, seed 1337), buffer N = 16384, 6352 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim), DT / 2.
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 1226407 evaluations, 51488 switches, 0 forced choices).
Capacity: **within design capacity** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T20:20:17, 423.4 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.0875 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 2549 | 222.9 |
| t90 | 4935 | 431.6 |
| t100 | 6352 | 555.5 |

t_p: the step by which ceil(p x 15832) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 801 | 0 | 39.9 | 488.9 | 18.9 | 25.5 | 47.9-57.9 |
| -x | 5.66 | 805 | 0 | 39.9 | 491.7 | 18.9 | 25.5 | 47.9-57.9 |
| +y | 5.66 | 800 | 0 | 39.9 | 486.4 | 19.0 | 25.5 | 47.9-57.9 |
| -y | 5.66 | 806 | 0 | 39.9 | 489.7 | 19.0 | 25.5 | 47.9-57.9 |
| door +x+y (y wall) 0 | 1.20 | 621 | 1121 | 4.8 | 506.5 | 61.9 | 90.3 | 26.2-36.2 |
| door +x+y (y wall) 1 | 1.20 | 598 | 680 | 4.8 | 518.8 | 58.2 | 90.3 | 27.5-37.5 |
| door +x+y (y wall) 2 | 1.20 | 280 | 178 | 4.8 | 546.1 | 25.9 | 85.3 | 8.7-18.7 |
| door +x+y (x wall) 0 | 1.20 | 618 | 1121 | 4.8 | 515.2 | 60.5 | 90.3 | 26.2-36.2 |
| door +x+y (x wall) 1 | 1.20 | 603 | 680 | 4.8 | 518.3 | 58.7 | 90.3 | 26.2-36.2 |
| door +x+y (x wall) 2 | 1.20 | 332 | 178 | 4.8 | 549.8 | 30.5 | 85.3 | 8.7-18.7 |
| door +x+y (corner) | 1.20 | 109 | 0 | 83.8 | 550.4 | 11.7 | 90.3 | 416.6-426.6 |
| door -x+y (y wall) 0 | 1.20 | 618 | 1121 | 4.8 | 502.2 | 62.1 | 90.3 | 30.5-40.5 |
| door -x+y (y wall) 1 | 1.20 | 601 | 680 | 4.8 | 514.6 | 58.9 | 90.3 | 24.6-34.5 |
| door -x+y (y wall) 2 | 1.20 | 316 | 178 | 4.8 | 536.7 | 29.7 | 85.3 | 8.7-18.7 |
| door -x+y (x wall) 0 | 1.20 | 616 | 1121 | 4.8 | 509.1 | 61.1 | 90.3 | 26.2-36.2 |
| door -x+y (x wall) 1 | 1.20 | 605 | 680 | 4.8 | 515.2 | 59.3 | 85.3 | 11.3-21.3 |
| door -x+y (x wall) 2 | 1.20 | 273 | 178 | 4.8 | 540.6 | 25.5 | 80.2 | 4.5-14.5 |
| door -x+y (corner) | 1.20 | 121 | 0 | 82.9 | 534.8 | 13.4 | 65.2 | 83.3-93.3 |
| door -x-y (y wall) 0 | 1.20 | 615 | 1121 | 4.8 | 502.3 | 61.8 | 95.3 | 27.5-37.5 |
| door -x-y (y wall) 1 | 1.20 | 596 | 680 | 4.8 | 514.7 | 58.4 | 90.3 | 26.0-35.9 |
| door -x-y (y wall) 2 | 1.20 | 303 | 178 | 4.8 | 534.4 | 28.6 | 80.2 | 4.5-14.5 |
| door -x-y (x wall) 0 | 1.20 | 613 | 1121 | 4.8 | 500.0 | 61.9 | 85.3 | 10.7-20.6 |
| door -x-y (x wall) 1 | 1.20 | 601 | 680 | 4.8 | 505.1 | 60.1 | 90.3 | 26.0-35.9 |
| door -x-y (x wall) 2 | 1.20 | 315 | 178 | 4.8 | 537.3 | 29.6 | 80.2 | 4.5-14.5 |
| door -x-y (corner) | 1.20 | 116 | 0 | 84.6 | 524.9 | 13.2 | 80.2 | 93.5-103.5 |
| door +x-y (y wall) 0 | 1.20 | 616 | 1121 | 4.8 | 497.5 | 62.5 | 90.3 | 30.3-40.2 |
| door +x-y (y wall) 1 | 1.20 | 600 | 680 | 4.8 | 520.4 | 58.2 | 85.3 | 10.7-20.6 |
| door +x-y (y wall) 2 | 1.20 | 303 | 178 | 4.8 | 550.1 | 27.8 | 80.2 | 4.5-14.5 |
| door +x-y (x wall) 0 | 1.20 | 613 | 1121 | 4.8 | 502.1 | 61.6 | 90.3 | 30.5-40.5 |
| door +x-y (x wall) 1 | 1.20 | 605 | 680 | 4.8 | 519.1 | 58.8 | 90.3 | 24.6-34.5 |
| door +x-y (x wall) 2 | 1.20 | 321 | 178 | 4.8 | 548.6 | 29.5 | 85.3 | 8.7-18.7 |
| door +x-y (corner) | 1.20 | 92 | 0 | 83.9 | 555.5 | 9.8 | 80.2 | 93.0-102.9 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 114 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 801 | 5.1% | 18.3% |
| -x | avenue | 5.66 | 805 | 5.1% | 18.4% |
| +y | avenue | 5.66 | 800 | 5.1% | 18.3% |
| -y | avenue | 5.66 | 806 | 5.1% | 18.4% |
| door +x+y (y wall) 0 | door | 1.20 | 621 | 3.9% | 66.9% |
| door +x+y (y wall) 1 | door | 1.20 | 598 | 3.8% | 64.4% |
| door +x+y (y wall) 2 | door | 1.20 | 280 | 1.8% | 30.1% |
| door +x+y (x wall) 0 | door | 1.20 | 618 | 3.9% | 66.5% |
| door +x+y (x wall) 1 | door | 1.20 | 603 | 3.8% | 64.9% |
| door +x+y (x wall) 2 | door | 1.20 | 332 | 2.1% | 35.7% |
| door +x+y (corner) | door | 1.20 | 109 | 0.7% | 11.7% |
| door -x+y (y wall) 0 | door | 1.20 | 618 | 3.9% | 66.5% |
| door -x+y (y wall) 1 | door | 1.20 | 601 | 3.8% | 64.7% |
| door -x+y (y wall) 2 | door | 1.20 | 316 | 2.0% | 34.0% |
| door -x+y (x wall) 0 | door | 1.20 | 616 | 3.9% | 66.3% |
| door -x+y (x wall) 1 | door | 1.20 | 605 | 3.8% | 65.1% |
| door -x+y (x wall) 2 | door | 1.20 | 273 | 1.7% | 29.4% |
| door -x+y (corner) | door | 1.20 | 121 | 0.8% | 13.0% |
| door -x-y (y wall) 0 | door | 1.20 | 615 | 3.9% | 66.2% |
| door -x-y (y wall) 1 | door | 1.20 | 596 | 3.8% | 64.2% |
| door -x-y (y wall) 2 | door | 1.20 | 303 | 1.9% | 32.6% |
| door -x-y (x wall) 0 | door | 1.20 | 613 | 3.9% | 66.0% |
| door -x-y (x wall) 1 | door | 1.20 | 601 | 3.8% | 64.7% |
| door -x-y (x wall) 2 | door | 1.20 | 315 | 2.0% | 33.9% |
| door -x-y (corner) | door | 1.20 | 116 | 0.7% | 12.5% |
| door +x-y (y wall) 0 | door | 1.20 | 616 | 3.9% | 66.3% |
| door +x-y (y wall) 1 | door | 1.20 | 600 | 3.8% | 64.6% |
| door +x-y (y wall) 2 | door | 1.20 | 303 | 1.9% | 32.6% |
| door +x-y (x wall) 0 | door | 1.20 | 613 | 3.9% | 66.0% |
| door +x-y (x wall) 1 | door | 1.20 | 605 | 3.8% | 65.1% |
| door +x-y (x wall) 2 | door | 1.20 | 321 | 2.0% | 34.6% |
| door +x-y (corner) | door | 1.20 | 92 | 0.6% | 9.9% |
| **doors (28)** | door | 33.60 | 12620 | 79.7% | |
| **avenues (4)** | avenue | 22.64 | 3212 | 20.3% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 555.5 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 36.4%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 952 | 6.0% | 952 | 6.0% |
| straight +x+y (y wing) 1 | straight | yes | 612 | 3.9% | 605 | 3.8% |
| straight +x+y (y wing) 2 | straight | yes | 273 | 1.7% | 273 | 1.7% |
| straight +x+y (x wing) 0 | straight | yes | 950 | 6.0% | 950 | 6.0% |
| straight +x+y (x wing) 1 | straight | yes | 613 | 3.9% | 606 | 3.8% |
| straight +x+y (x wing) 2 | straight | yes | 329 | 2.1% | 329 | 2.1% |
| corner +x+y | corner | yes | 778 | 4.9% | 243 | 1.5% |
| straight -x+y (y wing) 0 | straight | yes | 949 | 6.0% | 949 | 6.0% |
| straight -x+y (y wing) 1 | straight | yes | 608 | 3.8% | 603 | 3.8% |
| straight -x+y (y wing) 2 | straight | yes | 314 | 2.0% | 314 | 2.0% |
| straight -x+y (x wing) 0 | straight | yes | 954 | 6.0% | 954 | 6.0% |
| straight -x+y (x wing) 1 | straight | yes | 607 | 3.8% | 605 | 3.8% |
| straight -x+y (x wing) 2 | straight | yes | 273 | 1.7% | 273 | 1.7% |
| corner -x+y | corner | yes | 787 | 5.0% | 260 | 1.6% |
| straight -x-y (y wing) 0 | straight | yes | 950 | 6.0% | 950 | 6.0% |
| straight -x-y (y wing) 1 | straight | yes | 617 | 3.9% | 608 | 3.8% |
| straight -x-y (y wing) 2 | straight | yes | 291 | 1.8% | 291 | 1.8% |
| straight -x-y (x wing) 0 | straight | yes | 944 | 6.0% | 944 | 6.0% |
| straight -x-y (x wing) 1 | straight | yes | 613 | 3.9% | 604 | 3.8% |
| straight -x-y (x wing) 2 | straight | yes | 313 | 2.0% | 312 | 2.0% |
| corner -x-y | corner | yes | 776 | 4.9% | 249 | 1.6% |
| straight +x-y (y wing) 0 | straight | yes | 954 | 6.0% | 954 | 6.0% |
| straight +x-y (y wing) 1 | straight | yes | 615 | 3.9% | 605 | 3.8% |
| straight +x-y (y wing) 2 | straight | yes | 298 | 1.9% | 298 | 1.9% |
| straight +x-y (x wing) 0 | straight | yes | 948 | 6.0% | 948 | 6.0% |
| straight +x-y (x wing) 1 | straight | yes | 611 | 3.9% | 606 | 3.8% |
| straight +x-y (x wing) 2 | straight | yes | 320 | 2.0% | 320 | 2.0% |
| corner +x-y | corner | yes | 787 | 5.0% | 227 | 1.4% |
| **straight (24)** | | | 14908 | | 14853 | 93.8% |
| **corner (4)** | | | 3128 | | 979 | 6.2% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 114 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 801 | 39.9 | 488.9 | 0.23 | 0.31 | 0.0% |
| -x | 805 | 39.9 | 491.7 | 0.23 | 0.31 | 0.0% |
| +y | 800 | 39.9 | 486.4 | 0.23 | 0.31 | 0.0% |
| -y | 806 | 39.9 | 489.7 | 0.23 | 0.31 | 0.0% |
| door +x+y (y wall) 0 | 621 | 4.8 | 506.5 | 0.74 | 1.08 | 41.2% |
| door +x+y (y wall) 1 | 598 | 4.8 | 518.8 | 0.70 | 1.08 | 24.5% |
| door +x+y (y wall) 2 | 280 | 4.8 | 546.1 | 0.31 | 1.02 | 5.5% |
| door +x+y (x wall) 0 | 618 | 4.8 | 515.2 | 0.72 | 1.08 | 36.5% |
| door +x+y (x wall) 1 | 603 | 4.8 | 518.3 | 0.70 | 1.08 | 30.8% |
| door +x+y (x wall) 2 | 332 | 4.8 | 549.8 | 0.36 | 1.02 | 5.4% |
| door +x+y (corner) | 109 | 83.8 | 550.4 | 0.14 | 1.08 | 4.2% |
| door -x+y (y wall) 0 | 618 | 4.8 | 502.2 | 0.74 | 1.08 | 37.3% |
| door -x+y (y wall) 1 | 601 | 4.8 | 514.6 | 0.71 | 1.08 | 28.8% |
| door -x+y (y wall) 2 | 316 | 4.8 | 536.7 | 0.36 | 1.02 | 5.6% |
| door -x+y (x wall) 0 | 616 | 4.8 | 509.1 | 0.73 | 1.08 | 32.7% |
| door -x+y (x wall) 1 | 605 | 4.8 | 515.2 | 0.71 | 1.02 | 32.7% |
| door -x+y (x wall) 2 | 273 | 4.8 | 540.6 | 0.30 | 0.96 | 5.5% |
| door -x+y (corner) | 121 | 82.9 | 534.8 | 0.16 | 0.78 | 0.0% |
| door -x-y (y wall) 0 | 615 | 4.8 | 502.3 | 0.74 | 1.14 | 47.1% |
| door -x-y (y wall) 1 | 596 | 4.8 | 514.7 | 0.70 | 1.08 | 26.9% |
| door -x-y (y wall) 2 | 303 | 4.8 | 534.4 | 0.34 | 0.96 | 3.7% |
| door -x-y (x wall) 0 | 613 | 4.8 | 500.0 | 0.74 | 1.02 | 39.2% |
| door -x-y (x wall) 1 | 601 | 4.8 | 505.1 | 0.72 | 1.08 | 23.5% |
| door -x-y (x wall) 2 | 315 | 4.8 | 537.3 | 0.35 | 0.96 | 3.7% |
| door -x-y (corner) | 116 | 84.6 | 524.9 | 0.16 | 0.96 | 2.2% |
| door +x-y (y wall) 0 | 616 | 4.8 | 497.5 | 0.75 | 1.08 | 42.0% |
| door +x-y (y wall) 1 | 600 | 4.8 | 520.4 | 0.70 | 1.02 | 30.2% |
| door +x-y (y wall) 2 | 303 | 4.8 | 550.1 | 0.33 | 0.96 | 3.6% |
| door +x-y (x wall) 0 | 613 | 4.8 | 502.1 | 0.74 | 1.08 | 35.3% |
| door +x-y (x wall) 1 | 605 | 4.8 | 519.1 | 0.70 | 1.08 | 37.7% |
| door +x-y (x wall) 2 | 321 | 4.8 | 548.6 | 0.35 | 1.02 | 5.4% |
| door +x-y (corner) | 92 | 83.9 | 555.5 | 0.12 | 0.96 | 0.0% |

Mean flow / w J averaged over the doors 0.53, over the avenues 0.23.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 952 | 621 / 331 / 104 | 0.7 | 503.7 | 2.10 | 3.01 | 90% | 78% | 12% | 3.68 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 577 | 605 / 0 / 15 | 0.7 | 516.0 | 1.20 | 1.81 | 83% | 69% | 13% | 3.50 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 69 | 273 / 0 / 0 | 0.7 | 543.3 | 0.50 | 1.60 | 11% | 11% | 0% | 2.72 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 950 | 618 / 332 / 83 | 0.7 | 512.3 | 2.02 | 3.01 | 90% | 79% | 12% | 3.68 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 576 | 606 / 0 / 9 | 0.7 | 515.5 | 1.19 | 1.81 | 81% | 63% | 17% | 3.60 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 69 | 329 / 0 / 0 | 0.7 | 546.9 | 0.60 | 1.60 | 11% | 11% | 0% | 2.71 |
| corner +x+y | 1.20 | 85.6 | 765 | 109 / 134 / 546 | 0.7 | 546.7 | 1.44 | 4.11 | 85% | 55% | 31% | 2.33 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 949 | 618 / 331 / 88 | 0.7 | 499.3 | 2.08 | 3.01 | 88% | 78% | 10% | 3.87 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 574 | 603 / 0 / 5 | 0.7 | 511.7 | 1.19 | 1.81 | 81% | 69% | 12% | 3.60 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 69 | 314 / 0 / 0 | 0.7 | 533.8 | 0.59 | 1.60 | 11% | 9% | 2% | 2.67 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 954 | 616 / 338 / 103 | 0.7 | 506.3 | 2.09 | 2.91 | 82% | 80% | 2% | 4.03 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 564 | 605 / 0 / 5 | 0.7 | 512.4 | 1.19 | 1.81 | 81% | 67% | 13% | 3.54 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 69 | 273 / 0 / 0 | 0.7 | 537.8 | 0.51 | 1.60 | 11% | 9% | 2% | 2.73 |
| corner -x+y | 1.20 | 85.6 | 779 | 121 / 139 / 529 | 0.7 | 531.8 | 1.49 | 3.51 | 85% | 54% | 31% | 2.35 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 950 | 615 / 335 / 82 | 0.7 | 499.5 | 2.07 | 3.11 | 86% | 78% | 8% | 3.85 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 580 | 608 / 0 / 14 | 0.7 | 511.9 | 1.22 | 1.81 | 83% | 67% | 15% | 3.59 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 69 | 291 / 0 / 0 | 0.7 | 531.6 | 0.55 | 1.60 | 11% | 11% | 0% | 2.78 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 944 | 613 / 331 / 86 | 0.7 | 497.2 | 2.07 | 2.91 | 92% | 80% | 12% | 3.77 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 585 | 604 / 0 / 12 | 0.7 | 502.3 | 1.23 | 1.81 | 86% | 75% | 12% | 3.51 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 69 | 312 / 0 / 1 | 0.7 | 534.5 | 0.59 | 1.60 | 11% | 9% | 2% | 2.75 |
| corner -x-y | 1.20 | 85.6 | 761 | 116 / 133 / 539 | 0.7 | 528.5 | 1.49 | 4.31 | 83% | 52% | 31% | 2.34 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 954 | 616 / 338 / 104 | 0.7 | 494.7 | 2.14 | 2.91 | 90% | 82% | 8% | 3.83 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 570 | 605 / 0 / 11 | 0.7 | 517.6 | 1.19 | 1.81 | 81% | 67% | 13% | 3.53 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 69 | 298 / 0 / 0 | 0.7 | 547.2 | 0.55 | 1.60 | 11% | 11% | 0% | 2.75 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 948 | 613 / 335 / 106 | 0.7 | 499.3 | 2.11 | 3.21 | 80% | 80% | 0% | 4.09 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 574 | 606 / 0 / 6 | 0.7 | 516.2 | 1.19 | 1.81 | 81% | 69% | 12% | 3.56 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 69 | 320 / 0 / 0 | 0.7 | 545.8 | 0.59 | 1.60 | 11% | 9% | 2% | 2.66 |
| corner +x-y | 1.20 | 85.6 | 774 | 92 / 135 / 564 | 0.7 | 551.8 | 1.44 | 4.31 | 84% | 54% | 30% | 2.33 |

The last agent out (agent 12329, t100 555.5 s): last gangway corner +x-y, exit door +x-y (corner). The gangway that cleared last: corner +x-y at 551.8 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.99 | 553.1 / 537.2 / 479.9 | 531.5 / 497.8 / 434.8 | 673918.3 | 1576751 | 0.218 |
| gangway | 1212 | 1112.9 | 6.99 | 550.2 / 532.9 / 451.8 | 531.5 / 497.8 / 434.8 | 673538.7 | 1427172 | 0.112 |
| walkway | 276 | 257.4 | 3.06 | 150.7 / 95.8 / 0.0 | 112.6 / 36.8 / 0.0 | 0.0 | 24701 | 0.907 |
| avenue | 912 | 858.9 | 1.59 | 165.8 / 0.0 / 0.0 | 145.4 / 0.0 / 0.0 | 0.0 | 92160 | 1.328 |
| exit | 32 | 3.2 | 0.00 | 512.7 / 501.5 / 332.1 | 213.6 / 170.3 / 65.6 | 379.6 | 1105 | 1.318 |
| concourse | 1116 | 1043.8 | 1.95 | 482.7 / 0.0 / 0.0 | 119.8 / 0.0 / 0.0 | 0.0 | 31613 | 1.202 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.66 | 474.2 / 471.5 / 458.3 | 473.3 / 471.5 / 452.9 | 754706.5 | 2090589 | 0.042 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 29.5 | 26.5 | gangway | 1.00 | 6.27 | 454.8 | 433.8 | 388.9 | 2335.3 | 0.018 |
| 2 | -26.5 | 28.5 | gangway | 1.00 | 5.90 | 454.3 | 446.3 | 398.1 | 2270.2 | 0.017 |
| 3 | 26.5 | 28.5 | gangway | 1.00 | 5.92 | 471.8 | 461.6 | 384.5 | 2209.4 | 0.019 |
| 4 | 27.5 | -27.5 | gangway | 1.00 | 6.19 | 471.6 | 466.4 | 375.3 | 2192.3 | 0.019 |
| 5 | -29.5 | -26.5 | gangway | 1.00 | 6.17 | 455.9 | 438.7 | 374.1 | 2190.6 | 0.019 |
| 6 | -28.5 | 26.5 | gangway | 1.00 | 6.06 | 456.5 | 442.1 | 374.5 | 2176.2 | 0.021 |
| 7 | 26.5 | 27.5 | gangway | 1.00 | 5.86 | 468.5 | 465.1 | 381.1 | 2165.3 | 0.019 |
| 8 | 26.5 | 29.5 | gangway | 1.00 | 5.93 | 467.7 | 433.7 | 376.4 | 2163.9 | 0.019 |
| 9 | -28.5 | 27.5 | gangway | 1.00 | 6.06 | 457.7 | 452.4 | 379.6 | 2161.0 | 0.020 |
| 10 | -27.5 | -27.5 | gangway | 1.00 | 5.96 | 461.8 | 456.8 | 386.5 | 2148.2 | 0.019 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 26.5 | 24.5 | seat row | 0.50 | 7.27 | 467.1 | 465.8 | 452.9 | 1559.7 | 0.014 |
| 2 | 24.5 | 26.5 | seat row | 0.50 | 7.28 | 473.3 | 471.5 | 450.3 | 1557.5 | 0.013 |
| 3 | -26.5 | 24.5 | seat row | 0.50 | 7.33 | 464.0 | 462.4 | 450.0 | 1529.4 | 0.014 |
| 4 | -25.5 | -30.5 | seat row | 0.64 | 6.57 | 438.8 | 436.0 | 382.8 | 1522.9 | 0.025 |
| 5 | -24.5 | 26.5 | seat row | 0.50 | 7.13 | 459.5 | 455.5 | 445.3 | 1519.2 | 0.013 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 757; agent-steps of seated agents on another row's clearway: 11433.

## Deposit check

Person-seconds deposited: 3669374.2, of them in excluded cells: 2034.756.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 472765 overlapping pair-steps: p99 0.0016, max 0.0046 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0016 max 0.0046; venue-geometry 3: p99 0.0004 max 0.0004 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00375 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 14336 (longest 14 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.27 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 472 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
