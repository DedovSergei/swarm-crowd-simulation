# Experiment `M_load95_s3`

**Task 5.10 stage 4 (AMD 26.10.1): venue M, 95% load (seed 3), default model**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 15040 agents on 95% of the 15832 seats (spawnSeatedCrowd, seed 3), buffer N = 16384, 3055 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 1116565 evaluations, 46229 switches, 0 forced choices).
Capacity: **within design capacity** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T19:58:10, 111.5 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1218 | 213.0 |
| t90 | 2356 | 412.1 |
| t100 | 3055 | 534.3 |

t_p: the step by which ceil(p x 15040) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 782 | 0 | 39.5 | 473.3 | 19.1 | 25.5 | 76.1-86.1 |
| -x | 5.66 | 774 | 0 | 39.7 | 467.5 | 19.2 | 25.5 | 72.9-82.9 |
| +y | 5.66 | 787 | 0 | 39.5 | 468.7 | 19.4 | 25.5 | 50.0-60.0 |
| -y | 5.66 | 788 | 0 | 39.7 | 464.7 | 19.6 | 25.5 | 50.0-60.0 |
| door +x+y (y wall) 0 | 1.20 | 577 | 1068 | 4.9 | 492.4 | 59.2 | 90.3 | 27.3-37.3 |
| door +x+y (y wall) 1 | 1.20 | 568 | 651 | 4.9 | 495.3 | 57.9 | 85.3 | 18.2-28.2 |
| door +x+y (y wall) 2 | 1.20 | 291 | 168 | 4.9 | 533.6 | 27.5 | 80.2 | 4.7-14.7 |
| door +x+y (x wall) 0 | 1.20 | 576 | 1058 | 4.9 | 469.8 | 61.9 | 85.3 | 19.1-29.0 |
| door +x+y (x wall) 1 | 1.20 | 564 | 650 | 4.9 | 487.8 | 58.4 | 85.3 | 26.2-36.2 |
| door +x+y (x wall) 2 | 1.20 | 290 | 169 | 4.9 | 529.6 | 27.6 | 80.2 | 4.7-14.7 |
| door +x+y (corner) | 1.20 | 115 | 0 | 71.0 | 534.3 | 12.4 | 90.3 | 353.7-363.6 |
| door -x+y (y wall) 0 | 1.20 | 570 | 1050 | 4.9 | 481.3 | 59.8 | 85.3 | 13.3-23.3 |
| door -x+y (y wall) 1 | 1.20 | 570 | 640 | 4.9 | 490.3 | 58.7 | 85.3 | 10.0-19.9 |
| door -x+y (y wall) 2 | 1.20 | 267 | 174 | 4.9 | 510.7 | 26.4 | 80.2 | 4.7-14.7 |
| door -x+y (x wall) 0 | 1.20 | 575 | 1048 | 4.9 | 474.5 | 61.2 | 80.2 | 7.0-17.0 |
| door -x+y (x wall) 1 | 1.20 | 567 | 645 | 4.9 | 493.1 | 58.1 | 80.2 | 15.9-25.9 |
| door -x+y (x wall) 2 | 1.20 | 272 | 175 | 4.9 | 502.9 | 27.3 | 80.2 | 4.7-14.7 |
| door -x+y (corner) | 1.20 | 140 | 0 | 49.0 | 509.9 | 15.2 | 90.3 | 465.6-475.6 |
| door -x-y (y wall) 0 | 1.20 | 584 | 1075 | 4.9 | 491.1 | 60.0 | 85.3 | 31.8-41.8 |
| door -x-y (y wall) 1 | 1.20 | 588 | 654 | 4.9 | 496.6 | 59.8 | 90.3 | 15.7-25.7 |
| door -x-y (y wall) 2 | 1.20 | 318 | 173 | 4.9 | 524.5 | 30.6 | 80.2 | 4.7-14.7 |
| door -x-y (x wall) 0 | 1.20 | 582 | 1071 | 4.9 | 489.9 | 60.0 | 90.3 | 27.1-37.1 |
| door -x-y (x wall) 1 | 1.20 | 574 | 642 | 4.9 | 494.1 | 58.6 | 85.3 | 18.5-28.5 |
| door -x-y (x wall) 2 | 1.20 | 256 | 172 | 4.9 | 516.5 | 25.0 | 80.2 | 6.1-16.1 |
| door -x-y (corner) | 1.20 | 100 | 0 | 82.7 | 527.7 | 11.2 | 70.2 | 99.9-109.8 |
| door +x-y (y wall) 0 | 1.20 | 584 | 1056 | 4.9 | 474.5 | 62.2 | 85.3 | 10.1-20.1 |
| door +x-y (y wall) 1 | 1.20 | 577 | 652 | 4.9 | 496.2 | 58.7 | 85.3 | 13.8-23.8 |
| door +x-y (y wall) 2 | 1.20 | 270 | 170 | 4.9 | 520.3 | 26.2 | 85.3 | 8.6-18.5 |
| door +x-y (x wall) 0 | 1.20 | 587 | 1071 | 4.9 | 487.5 | 60.8 | 85.3 | 10.8-20.8 |
| door +x-y (x wall) 1 | 1.20 | 575 | 639 | 4.9 | 496.0 | 58.5 | 85.3 | 15.7-25.7 |
| door +x-y (x wall) 2 | 1.20 | 288 | 169 | 4.9 | 518.6 | 28.0 | 80.2 | 4.0-14.0 |
| door +x-y (corner) | 1.20 | 84 | 0 | 77.5 | 523.5 | 9.4 | 70.2 | 341.2-351.2 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 782 | 5.2% | 18.6% |
| -x | avenue | 5.66 | 774 | 5.1% | 18.4% |
| +y | avenue | 5.66 | 787 | 5.2% | 18.7% |
| -y | avenue | 5.66 | 788 | 5.2% | 18.7% |
| door +x+y (y wall) 0 | door | 1.20 | 577 | 3.8% | 64.6% |
| door +x+y (y wall) 1 | door | 1.20 | 568 | 3.8% | 63.6% |
| door +x+y (y wall) 2 | door | 1.20 | 291 | 1.9% | 32.6% |
| door +x+y (x wall) 0 | door | 1.20 | 576 | 3.8% | 64.5% |
| door +x+y (x wall) 1 | door | 1.20 | 564 | 3.8% | 63.1% |
| door +x+y (x wall) 2 | door | 1.20 | 290 | 1.9% | 32.5% |
| door +x+y (corner) | door | 1.20 | 115 | 0.8% | 12.9% |
| door -x+y (y wall) 0 | door | 1.20 | 570 | 3.8% | 63.8% |
| door -x+y (y wall) 1 | door | 1.20 | 570 | 3.8% | 63.8% |
| door -x+y (y wall) 2 | door | 1.20 | 267 | 1.8% | 29.9% |
| door -x+y (x wall) 0 | door | 1.20 | 575 | 3.8% | 64.4% |
| door -x+y (x wall) 1 | door | 1.20 | 567 | 3.8% | 63.5% |
| door -x+y (x wall) 2 | door | 1.20 | 272 | 1.8% | 30.4% |
| door -x+y (corner) | door | 1.20 | 140 | 0.9% | 15.7% |
| door -x-y (y wall) 0 | door | 1.20 | 584 | 3.9% | 65.4% |
| door -x-y (y wall) 1 | door | 1.20 | 588 | 3.9% | 65.8% |
| door -x-y (y wall) 2 | door | 1.20 | 318 | 2.1% | 35.6% |
| door -x-y (x wall) 0 | door | 1.20 | 582 | 3.9% | 65.1% |
| door -x-y (x wall) 1 | door | 1.20 | 574 | 3.8% | 64.2% |
| door -x-y (x wall) 2 | door | 1.20 | 256 | 1.7% | 28.7% |
| door -x-y (corner) | door | 1.20 | 100 | 0.7% | 11.2% |
| door +x-y (y wall) 0 | door | 1.20 | 584 | 3.9% | 65.4% |
| door +x-y (y wall) 1 | door | 1.20 | 577 | 3.8% | 64.6% |
| door +x-y (y wall) 2 | door | 1.20 | 270 | 1.8% | 30.2% |
| door +x-y (x wall) 0 | door | 1.20 | 587 | 3.9% | 65.7% |
| door +x-y (x wall) 1 | door | 1.20 | 575 | 3.8% | 64.4% |
| door +x-y (x wall) 2 | door | 1.20 | 288 | 1.9% | 32.2% |
| door +x-y (corner) | door | 1.20 | 84 | 0.6% | 9.4% |
| **doors (28)** | door | 33.60 | 11909 | 79.2% | |
| **avenues (4)** | avenue | 22.64 | 3131 | 20.8% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 534.3 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 35.9%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 898 | 6.0% | 898 | 6.0% |
| straight +x+y (y wing) 1 | straight | yes | 578 | 3.8% | 569 | 3.8% |
| straight +x+y (y wing) 2 | straight | yes | 290 | 1.9% | 290 | 1.9% |
| straight +x+y (x wing) 0 | straight | yes | 898 | 6.0% | 898 | 6.0% |
| straight +x+y (x wing) 1 | straight | yes | 570 | 3.8% | 564 | 3.8% |
| straight +x+y (x wing) 2 | straight | yes | 290 | 1.9% | 290 | 1.9% |
| corner +x+y | corner | yes | 781 | 5.2% | 255 | 1.7% |
| straight -x+y (y wing) 0 | straight | yes | 891 | 5.9% | 891 | 5.9% |
| straight -x+y (y wing) 1 | straight | yes | 577 | 3.8% | 570 | 3.8% |
| straight -x+y (y wing) 2 | straight | yes | 267 | 1.8% | 267 | 1.8% |
| straight -x+y (x wing) 0 | straight | yes | 891 | 5.9% | 891 | 5.9% |
| straight -x+y (x wing) 1 | straight | yes | 573 | 3.8% | 567 | 3.8% |
| straight -x+y (x wing) 2 | straight | yes | 274 | 1.8% | 273 | 1.8% |
| corner -x+y | corner | yes | 757 | 5.0% | 273 | 1.8% |
| straight -x-y (y wing) 0 | straight | yes | 906 | 6.0% | 906 | 6.0% |
| straight -x-y (y wing) 1 | straight | yes | 594 | 3.9% | 588 | 3.9% |
| straight -x-y (y wing) 2 | straight | yes | 317 | 2.1% | 317 | 2.1% |
| straight -x-y (x wing) 0 | straight | yes | 909 | 6.0% | 909 | 6.0% |
| straight -x-y (x wing) 1 | straight | yes | 580 | 3.9% | 574 | 3.8% |
| straight -x-y (x wing) 2 | straight | yes | 256 | 1.7% | 256 | 1.7% |
| corner -x-y | corner | yes | 756 | 5.0% | 237 | 1.6% |
| straight +x-y (y wing) 0 | straight | yes | 913 | 6.1% | 913 | 6.1% |
| straight +x-y (y wing) 1 | straight | yes | 584 | 3.9% | 579 | 3.8% |
| straight +x-y (y wing) 2 | straight | yes | 268 | 1.8% | 268 | 1.8% |
| straight +x-y (x wing) 0 | straight | yes | 912 | 6.1% | 912 | 6.1% |
| straight +x-y (x wing) 1 | straight | yes | 583 | 3.9% | 579 | 3.8% |
| straight +x-y (x wing) 2 | straight | yes | 284 | 1.9% | 284 | 1.9% |
| corner +x-y | corner | yes | 747 | 5.0% | 222 | 1.5% |
| **straight (24)** | | | 14103 | | 14053 | 93.4% |
| **corner (4)** | | | 3041 | | 987 | 6.6% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 782 | 39.5 | 473.3 | 0.23 | 0.31 | 0.0% |
| -x | 774 | 39.7 | 467.5 | 0.23 | 0.31 | 0.0% |
| +y | 787 | 39.5 | 468.7 | 0.23 | 0.31 | 0.0% |
| -y | 788 | 39.7 | 464.7 | 0.23 | 0.31 | 0.0% |
| door +x+y (y wall) 0 | 577 | 4.9 | 492.4 | 0.71 | 1.08 | 34.0% |
| door +x+y (y wall) 1 | 568 | 4.9 | 495.3 | 0.69 | 1.02 | 28.0% |
| door +x+y (y wall) 2 | 291 | 4.9 | 533.6 | 0.33 | 0.96 | 3.7% |
| door +x+y (x wall) 0 | 576 | 4.9 | 469.8 | 0.74 | 1.02 | 37.5% |
| door +x+y (x wall) 1 | 564 | 4.9 | 487.8 | 0.70 | 1.02 | 24.5% |
| door +x+y (x wall) 2 | 290 | 4.9 | 529.6 | 0.33 | 0.96 | 3.7% |
| door +x+y (corner) | 115 | 71.0 | 534.3 | 0.15 | 1.08 | 4.3% |
| door -x+y (y wall) 0 | 570 | 4.9 | 481.3 | 0.72 | 1.02 | 28.6% |
| door -x+y (y wall) 1 | 570 | 4.9 | 490.3 | 0.70 | 1.02 | 18.0% |
| door -x+y (y wall) 2 | 267 | 4.9 | 510.7 | 0.32 | 0.96 | 5.8% |
| door -x+y (x wall) 0 | 575 | 4.9 | 474.5 | 0.73 | 0.96 | 39.6% |
| door -x+y (x wall) 1 | 567 | 4.9 | 493.1 | 0.69 | 0.96 | 26.0% |
| door -x+y (x wall) 2 | 272 | 4.9 | 502.9 | 0.33 | 0.96 | 2.0% |
| door -x+y (corner) | 140 | 49.0 | 509.9 | 0.18 | 1.08 | 2.1% |
| door -x-y (y wall) 0 | 584 | 4.9 | 491.1 | 0.72 | 1.02 | 34.0% |
| door -x-y (y wall) 1 | 588 | 4.9 | 496.6 | 0.72 | 1.08 | 30.0% |
| door -x-y (y wall) 2 | 318 | 4.9 | 524.5 | 0.37 | 0.96 | 3.8% |
| door -x-y (x wall) 0 | 582 | 4.9 | 489.9 | 0.72 | 1.08 | 36.0% |
| door -x-y (x wall) 1 | 574 | 4.9 | 494.1 | 0.70 | 1.02 | 36.0% |
| door -x-y (x wall) 2 | 256 | 4.9 | 516.5 | 0.30 | 0.96 | 3.8% |
| door -x-y (corner) | 100 | 82.7 | 527.7 | 0.13 | 0.84 | 0.0% |
| door +x-y (y wall) 0 | 584 | 4.9 | 474.5 | 0.74 | 1.02 | 37.5% |
| door +x-y (y wall) 1 | 577 | 4.9 | 496.2 | 0.70 | 1.02 | 30.0% |
| door +x-y (y wall) 2 | 270 | 4.9 | 520.3 | 0.31 | 1.02 | 5.7% |
| door +x-y (x wall) 0 | 587 | 4.9 | 487.5 | 0.73 | 1.02 | 30.6% |
| door +x-y (x wall) 1 | 575 | 4.9 | 496.0 | 0.70 | 1.02 | 22.0% |
| door +x-y (x wall) 2 | 288 | 4.9 | 518.6 | 0.34 | 0.96 | 3.8% |
| door +x-y (corner) | 84 | 77.5 | 523.5 | 0.11 | 0.84 | 0.0% |

Mean flow / w J averaged over the doors 0.52, over the avenues 0.23.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 898 | 577 / 321 / 211 | 0.7 | 489.4 | 2.27 | 3.61 | 78% | 76% | 2% | 4.01 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 530 | 569 / 0 / 12 | 0.7 | 492.4 | 1.18 | 1.71 | 78% | 64% | 14% | 3.50 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 69 | 290 / 0 / 1 | 0.7 | 530.7 | 0.55 | 1.60 | 11% | 11% | 0% | 2.64 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 898 | 576 / 322 / 228 | 0.7 | 466.8 | 2.41 | 4.01 | 89% | 79% | 11% | 3.86 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 529 | 564 / 0 / 12 | 0.7 | 484.8 | 1.19 | 1.71 | 80% | 65% | 14% | 3.55 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 70 | 290 / 0 / 0 | 0.7 | 526.6 | 0.55 | 1.50 | 13% | 9% | 4% | 2.54 |
| corner +x+y | 1.20 | 85.6 | 770 | 115 / 140 / 540 | 0.7 | 530.5 | 1.50 | 4.31 | 81% | 52% | 30% | 2.38 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 891 | 570 / 321 / 208 | 0.7 | 478.4 | 2.30 | 4.11 | 92% | 77% | 15% | 3.61 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 532 | 570 / 0 / 11 | 0.7 | 487.3 | 1.19 | 1.81 | 82% | 65% | 16% | 3.47 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 68 | 267 / 0 / 0 | 0.7 | 507.8 | 0.53 | 1.50 | 12% | 10% | 2% | 2.65 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 891 | 575 / 316 / 169 | 0.7 | 471.5 | 2.25 | 3.41 | 90% | 77% | 12% | 3.79 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 534 | 567 / 0 / 10 | 0.7 | 490.1 | 1.18 | 1.60 | 84% | 66% | 18% | 3.30 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 70 | 273 / 0 / 1 | 0.7 | 499.9 | 0.55 | 1.50 | 14% | 10% | 4% | 2.45 |
| corner -x+y | 1.20 | 85.6 | 746 | 139 / 134 / 495 | 0.7 | 506.0 | 1.52 | 3.31 | 86% | 53% | 33% | 2.42 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 906 | 584 / 322 / 212 | 0.7 | 488.2 | 2.29 | 3.61 | 92% | 78% | 14% | 3.69 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 556 | 588 / 0 / 22 | 0.7 | 493.6 | 1.24 | 1.81 | 82% | 68% | 14% | 3.43 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 68 | 317 / 0 / 0 | 0.7 | 521.6 | 0.61 | 1.50 | 13% | 9% | 4% | 2.61 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 909 | 582 / 327 / 235 | 0.7 | 486.9 | 2.35 | 4.11 | 92% | 78% | 14% | 3.74 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 534 | 574 / 0 / 11 | 0.7 | 491.1 | 1.19 | 1.71 | 80% | 64% | 16% | 3.40 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 66 | 256 / 0 / 0 | 0.7 | 513.5 | 0.50 | 1.60 | 10% | 10% | 0% | 2.80 |
| corner -x-y | 1.20 | 85.6 | 748 | 101 / 136 / 543 | 0.7 | 523.8 | 1.49 | 3.81 | 85% | 55% | 30% | 2.38 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 913 | 584 / 329 / 245 | 0.7 | 471.5 | 2.46 | 3.71 | 90% | 79% | 10% | 3.75 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 536 | 579 / 0 / 7 | 0.7 | 493.2 | 1.19 | 1.81 | 76% | 66% | 10% | 3.63 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 64 | 268 / 0 / 0 | 0.7 | 517.4 | 0.52 | 1.60 | 12% | 10% | 2% | 2.71 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 912 | 587 / 325 / 202 | 0.7 | 484.5 | 2.30 | 3.71 | 90% | 80% | 10% | 3.73 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 527 | 579 / 0 / 10 | 0.7 | 493.1 | 1.20 | 1.71 | 76% | 68% | 8% | 3.66 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 68 | 284 / 0 / 0 | 0.7 | 515.6 | 0.55 | 1.50 | 12% | 10% | 2% | 2.55 |
| corner +x-y | 1.20 | 85.6 | 737 | 84 / 138 / 532 | 0.7 | 519.6 | 1.45 | 3.61 | 83% | 60% | 23% | 2.46 |

The last agent out (agent 429, t100 534.3 s): last gangway corner +x+y, exit door +x+y (corner). The gangway that cleared last: straight +x+y (y wing) 2 at 530.7 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.90 | 523.3 / 511.8 / 482.2 | 510.7 / 471.7 / 406.1 | 617150.4 | 1504284 | 0.219 |
| gangway | 1212 | 1112.9 | 6.90 | 521.0 / 508.8 / 429.4 | 510.7 / 471.7 / 406.1 | 616317.4 | 1358656 | 0.111 |
| walkway | 276 | 257.4 | 3.23 | 193.8 / 118.9 / 0.0 | 127.3 / 22.6 / 0.0 | 0.0 | 24241 | 0.904 |
| avenue | 912 | 858.9 | 1.84 | 208.3 / 0.0 / 0.0 | 170.4 / 0.0 / 0.0 | 0.0 | 89890 | 1.327 |
| exit | 32 | 3.2 | 0.00 | 499.4 / 496.4 / 445.3 | 245.7 / 220.6 / 130.8 | 833.0 | 1579 | 1.324 |
| concourse | 1116 | 1043.8 | 1.94 | 467.7 / 0.0 / 0.0 | 114.6 / 0.0 / 0.0 | 0.0 | 29918 | 1.195 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.58 | 453.0 / 446.9 / 437.1 | 448.5 / 446.9 / 433.4 | 643941.0 | 1833775 | 0.046 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -27.5 | -27.5 | gangway | 1.00 | 5.93 | 442.0 | 439.5 | 375.2 | 2161.2 | 0.018 |
| 2 | -26.5 | -28.5 | gangway | 1.00 | 5.90 | 444.4 | 431.7 | 373.8 | 2117.9 | 0.021 |
| 3 | -28.5 | 26.5 | gangway | 1.00 | 6.17 | 447.2 | 442.3 | 356.6 | 2087.4 | 0.021 |
| 4 | 26.5 | -26.5 | gangway | 1.00 | 6.06 | 453.4 | 449.9 | 354.4 | 2084.9 | 0.020 |
| 5 | 28.5 | -27.5 | gangway | 1.00 | 5.86 | 451.4 | 440.9 | 363.6 | 2075.4 | 0.018 |
| 6 | -27.5 | -26.5 | gangway | 1.00 | 5.93 | 446.9 | 428.7 | 361.2 | 2072.6 | 0.020 |
| 7 | -28.5 | -27.5 | gangway | 1.00 | 5.95 | 443.2 | 433.9 | 360.8 | 2072.5 | 0.020 |
| 8 | 28.5 | -26.5 | gangway | 1.00 | 5.88 | 454.2 | 441.6 | 369.1 | 2050.5 | 0.024 |
| 9 | -29.5 | 26.5 | gangway | 1.00 | 6.02 | 437.4 | 408.2 | 346.5 | 2011.1 | 0.022 |
| 10 | 27.5 | -28.5 | gangway | 1.00 | 5.62 | 448.1 | 421.2 | 357.0 | 1987.9 | 0.018 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 26.5 | -24.5 | seat row | 0.50 | 7.28 | 446.4 | 443.9 | 428.7 | 1513.9 | 0.015 |
| 2 | -26.5 | -24.5 | seat row | 0.50 | 7.30 | 448.5 | 446.9 | 433.4 | 1511.7 | 0.014 |
| 3 | -24.5 | -26.5 | seat row | 0.50 | 7.30 | 445.1 | 442.2 | 427.5 | 1476.6 | 0.015 |
| 4 | 24.5 | 26.5 | seat row | 0.50 | 7.25 | 440.8 | 439.7 | 425.7 | 1474.5 | 0.016 |
| 5 | 24.5 | -26.5 | seat row | 0.50 | 7.25 | 432.5 | 429.9 | 418.9 | 1469.7 | 0.013 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1710; agent-steps of seated agents on another row's clearway: 15808.

## Deposit check

Person-seconds deposited: 3340989.9, of them in excluded cells: 2931.544.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 323685 overlapping pair-steps: p99 0.0025, max 0.0214 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0025 max 0.0214; venue-geometry 4: p99 0.0011 max 0.0011 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00752 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 16 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.27 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 568 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
