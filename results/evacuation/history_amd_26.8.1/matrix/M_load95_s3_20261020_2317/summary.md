# Experiment `M_load95_s3`

**Task 5.9 stage 4: venue M, 95% load (seed 3), default model**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 15040 agents on 95% of the 15832 seats (spawnSeatedCrowd, seed 3), buffer N = 16384, 3101 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 1118153 evaluations, 46633 switches, 0 forced choices).
Capacity: **within design capacity** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-20T23:17:52, 76.6 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1217 | 212.9 |
| t90 | 2364 | 413.5 |
| t100 | 3101 | 542.4 |

t_p: the step by which ceil(p x 15040) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 773 | 0 | 39.5 | 468.1 | 19.1 | 25.5 | 77.8-87.8 |
| -x | 5.66 | 774 | 0 | 39.7 | 469.8 | 19.1 | 25.5 | 73.6-83.6 |
| +y | 5.66 | 780 | 0 | 39.5 | 464.0 | 19.5 | 25.5 | 49.8-59.8 |
| -y | 5.66 | 782 | 0 | 39.7 | 467.4 | 19.4 | 25.5 | 50.2-60.2 |
| door +x+y (y wall) 0 | 1.20 | 584 | 1068 | 4.9 | 487.6 | 60.5 | 85.3 | 20.5-30.4 |
| door +x+y (y wall) 1 | 1.20 | 574 | 651 | 4.9 | 489.9 | 59.2 | 85.3 | 16.6-26.6 |
| door +x+y (y wall) 2 | 1.20 | 305 | 168 | 4.9 | 521.0 | 29.5 | 85.3 | 24.0-33.9 |
| door +x+y (x wall) 0 | 1.20 | 575 | 1058 | 4.9 | 479.2 | 60.6 | 85.3 | 12.4-22.4 |
| door +x+y (x wall) 1 | 1.20 | 566 | 650 | 4.9 | 487.8 | 58.6 | 85.3 | 34.6-44.6 |
| door +x+y (x wall) 2 | 1.20 | 267 | 169 | 4.9 | 514.8 | 26.2 | 85.3 | 24.0-33.9 |
| door +x+y (corner) | 1.20 | 126 | 0 | 57.7 | 519.1 | 13.6 | 90.3 | 470.7-480.6 |
| door -x+y (y wall) 0 | 1.20 | 574 | 1050 | 4.9 | 485.5 | 59.7 | 80.2 | 6.1-16.1 |
| door -x+y (y wall) 1 | 1.20 | 575 | 640 | 4.9 | 511.3 | 56.8 | 85.3 | 19.2-29.2 |
| door -x+y (y wall) 2 | 1.20 | 285 | 174 | 4.9 | 508.8 | 28.3 | 85.3 | 24.0-33.9 |
| door -x+y (x wall) 0 | 1.20 | 578 | 1048 | 4.9 | 475.9 | 61.3 | 90.3 | 29.2-39.2 |
| door -x+y (x wall) 1 | 1.20 | 574 | 645 | 4.9 | 487.1 | 59.5 | 80.2 | 7.3-17.3 |
| door -x+y (x wall) 2 | 1.20 | 276 | 175 | 4.9 | 508.8 | 27.4 | 80.2 | 4.7-14.7 |
| door -x+y (corner) | 1.20 | 97 | 0 | 55.4 | 512.0 | 10.6 | 65.2 | 472.6-482.6 |
| door -x-y (y wall) 0 | 1.20 | 585 | 1075 | 4.9 | 484.7 | 60.9 | 90.3 | 28.5-38.5 |
| door -x-y (y wall) 1 | 1.20 | 574 | 654 | 4.9 | 527.5 | 54.9 | 85.3 | 12.9-22.9 |
| door -x-y (y wall) 2 | 1.20 | 278 | 173 | 4.9 | 541.3 | 25.9 | 80.2 | 4.7-14.7 |
| door -x-y (x wall) 0 | 1.20 | 586 | 1071 | 4.9 | 479.2 | 61.7 | 80.2 | 11.2-21.2 |
| door -x-y (x wall) 1 | 1.20 | 578 | 642 | 4.9 | 510.4 | 57.2 | 85.3 | 12.9-22.9 |
| door -x-y (x wall) 2 | 1.20 | 300 | 172 | 4.9 | 542.4 | 27.9 | 80.2 | 4.7-14.7 |
| door -x-y (corner) | 1.20 | 100 | 0 | 78.2 | 528.6 | 11.1 | 55.2 | 294.9-304.9 |
| door +x-y (y wall) 0 | 1.20 | 572 | 1056 | 4.9 | 482.2 | 59.9 | 85.3 | 21.5-31.5 |
| door +x-y (y wall) 1 | 1.20 | 577 | 652 | 4.9 | 499.2 | 58.3 | 85.3 | 23.6-33.6 |
| door +x-y (y wall) 2 | 1.20 | 249 | 170 | 4.9 | 521.0 | 24.1 | 85.3 | 8.4-18.4 |
| door +x-y (x wall) 0 | 1.20 | 587 | 1071 | 4.9 | 491.1 | 60.3 | 90.3 | 6.1-16.1 |
| door +x-y (x wall) 1 | 1.20 | 559 | 639 | 4.9 | 504.6 | 55.9 | 85.3 | 12.8-22.7 |
| door +x-y (x wall) 2 | 1.20 | 326 | 169 | 4.9 | 525.4 | 31.3 | 85.3 | 5.9-15.9 |
| door +x-y (corner) | 1.20 | 104 | 0 | 47.7 | 526.5 | 10.9 | 75.2 | 359.3-369.2 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 773 | 5.1% | 18.1% |
| -x | avenue | 5.66 | 774 | 5.1% | 18.1% |
| +y | avenue | 5.66 | 780 | 5.2% | 18.2% |
| -y | avenue | 5.66 | 782 | 5.2% | 18.3% |
| door +x+y (y wall) 0 | door | 1.20 | 584 | 3.9% | 64.4% |
| door +x+y (y wall) 1 | door | 1.20 | 574 | 3.8% | 63.3% |
| door +x+y (y wall) 2 | door | 1.20 | 305 | 2.0% | 33.6% |
| door +x+y (x wall) 0 | door | 1.20 | 575 | 3.8% | 63.4% |
| door +x+y (x wall) 1 | door | 1.20 | 566 | 3.8% | 62.4% |
| door +x+y (x wall) 2 | door | 1.20 | 267 | 1.8% | 29.4% |
| door +x+y (corner) | door | 1.20 | 126 | 0.8% | 13.9% |
| door -x+y (y wall) 0 | door | 1.20 | 574 | 3.8% | 63.3% |
| door -x+y (y wall) 1 | door | 1.20 | 575 | 3.8% | 63.4% |
| door -x+y (y wall) 2 | door | 1.20 | 285 | 1.9% | 31.4% |
| door -x+y (x wall) 0 | door | 1.20 | 578 | 3.8% | 63.7% |
| door -x+y (x wall) 1 | door | 1.20 | 574 | 3.8% | 63.3% |
| door -x+y (x wall) 2 | door | 1.20 | 276 | 1.8% | 30.4% |
| door -x+y (corner) | door | 1.20 | 97 | 0.6% | 10.7% |
| door -x-y (y wall) 0 | door | 1.20 | 585 | 3.9% | 64.5% |
| door -x-y (y wall) 1 | door | 1.20 | 574 | 3.8% | 63.3% |
| door -x-y (y wall) 2 | door | 1.20 | 278 | 1.8% | 30.7% |
| door -x-y (x wall) 0 | door | 1.20 | 586 | 3.9% | 64.6% |
| door -x-y (x wall) 1 | door | 1.20 | 578 | 3.8% | 63.7% |
| door -x-y (x wall) 2 | door | 1.20 | 300 | 2.0% | 33.1% |
| door -x-y (corner) | door | 1.20 | 100 | 0.7% | 11.0% |
| door +x-y (y wall) 0 | door | 1.20 | 572 | 3.8% | 63.1% |
| door +x-y (y wall) 1 | door | 1.20 | 577 | 3.8% | 63.6% |
| door +x-y (y wall) 2 | door | 1.20 | 249 | 1.7% | 27.5% |
| door +x-y (x wall) 0 | door | 1.20 | 587 | 3.9% | 64.7% |
| door +x-y (x wall) 1 | door | 1.20 | 559 | 3.7% | 61.6% |
| door +x-y (x wall) 2 | door | 1.20 | 326 | 2.2% | 35.9% |
| door +x-y (corner) | door | 1.20 | 104 | 0.7% | 11.5% |
| **doors (28)** | door | 33.60 | 11931 | 79.3% | |
| **avenues (4)** | avenue | 22.64 | 3109 | 20.7% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 542.4 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 35.4%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 901 | 6.0% | 901 | 6.0% |
| straight +x+y (y wing) 1 | straight | yes | 581 | 3.9% | 574 | 3.8% |
| straight +x+y (y wing) 2 | straight | yes | 304 | 2.0% | 304 | 2.0% |
| straight +x+y (x wing) 0 | straight | yes | 896 | 6.0% | 896 | 6.0% |
| straight +x+y (x wing) 1 | straight | yes | 570 | 3.8% | 566 | 3.8% |
| straight +x+y (x wing) 2 | straight | yes | 268 | 1.8% | 268 | 1.8% |
| corner +x+y | corner | yes | 763 | 5.1% | 255 | 1.7% |
| straight -x+y (y wing) 0 | straight | yes | 897 | 6.0% | 897 | 6.0% |
| straight -x+y (y wing) 1 | straight | yes | 581 | 3.9% | 578 | 3.8% |
| straight -x+y (y wing) 2 | straight | yes | 282 | 1.9% | 282 | 1.9% |
| straight -x+y (x wing) 0 | straight | yes | 894 | 5.9% | 894 | 5.9% |
| straight -x+y (x wing) 1 | straight | yes | 580 | 3.9% | 577 | 3.8% |
| straight -x+y (x wing) 2 | straight | yes | 274 | 1.8% | 274 | 1.8% |
| corner -x+y | corner | yes | 748 | 5.0% | 230 | 1.5% |
| straight -x-y (y wing) 0 | straight | yes | 914 | 6.1% | 914 | 6.1% |
| straight -x-y (y wing) 1 | straight | yes | 580 | 3.9% | 574 | 3.8% |
| straight -x-y (y wing) 2 | straight | yes | 278 | 1.8% | 278 | 1.8% |
| straight -x-y (x wing) 0 | straight | yes | 912 | 6.1% | 912 | 6.1% |
| straight -x-y (x wing) 1 | straight | yes | 588 | 3.9% | 580 | 3.9% |
| straight -x-y (x wing) 2 | straight | yes | 298 | 2.0% | 298 | 2.0% |
| corner -x-y | corner | yes | 748 | 5.0% | 231 | 1.5% |
| straight +x-y (y wing) 0 | straight | yes | 900 | 6.0% | 900 | 6.0% |
| straight +x-y (y wing) 1 | straight | yes | 585 | 3.9% | 581 | 3.9% |
| straight +x-y (y wing) 2 | straight | yes | 245 | 1.6% | 245 | 1.6% |
| straight +x-y (x wing) 0 | straight | yes | 907 | 6.0% | 907 | 6.0% |
| straight +x-y (x wing) 1 | straight | yes | 578 | 3.8% | 572 | 3.8% |
| straight +x-y (x wing) 2 | straight | yes | 313 | 2.1% | 313 | 2.1% |
| corner +x-y | corner | yes | 740 | 4.9% | 239 | 1.6% |
| **straight (24)** | | | 14126 | | 14085 | 93.7% |
| **corner (4)** | | | 2999 | | 955 | 6.3% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 773 | 39.5 | 468.1 | 0.23 | 0.31 | 0.0% |
| -x | 774 | 39.7 | 469.8 | 0.23 | 0.31 | 0.0% |
| +y | 780 | 39.5 | 464.0 | 0.23 | 0.31 | 0.0% |
| -y | 782 | 39.7 | 467.4 | 0.23 | 0.31 | 0.0% |
| door +x+y (y wall) 0 | 584 | 4.9 | 487.6 | 0.72 | 1.02 | 36.7% |
| door +x+y (y wall) 1 | 574 | 4.9 | 489.9 | 0.71 | 1.02 | 20.0% |
| door +x+y (y wall) 2 | 305 | 4.9 | 521.0 | 0.35 | 1.02 | 1.9% |
| door +x+y (x wall) 0 | 575 | 4.9 | 479.2 | 0.72 | 1.02 | 36.7% |
| door +x+y (x wall) 1 | 566 | 4.9 | 487.8 | 0.70 | 1.02 | 24.5% |
| door +x+y (x wall) 2 | 267 | 4.9 | 514.8 | 0.31 | 1.02 | 3.8% |
| door +x+y (corner) | 126 | 57.7 | 519.1 | 0.16 | 1.08 | 2.1% |
| door -x+y (y wall) 0 | 574 | 4.9 | 485.5 | 0.71 | 0.96 | 30.6% |
| door -x+y (y wall) 1 | 575 | 4.9 | 511.3 | 0.68 | 1.02 | 26.9% |
| door -x+y (y wall) 2 | 285 | 4.9 | 508.8 | 0.34 | 1.02 | 3.8% |
| door -x+y (x wall) 0 | 578 | 4.9 | 475.9 | 0.73 | 1.08 | 31.2% |
| door -x+y (x wall) 1 | 574 | 4.9 | 487.1 | 0.71 | 0.96 | 28.6% |
| door -x+y (x wall) 2 | 276 | 4.9 | 508.8 | 0.33 | 0.96 | 3.8% |
| door -x+y (corner) | 97 | 55.4 | 512.0 | 0.13 | 0.78 | 0.0% |
| door -x-y (y wall) 0 | 585 | 4.9 | 484.7 | 0.73 | 1.08 | 34.7% |
| door -x-y (y wall) 1 | 574 | 4.9 | 527.5 | 0.66 | 1.02 | 34.0% |
| door -x-y (y wall) 2 | 278 | 4.9 | 541.3 | 0.31 | 0.96 | 3.6% |
| door -x-y (x wall) 0 | 586 | 4.9 | 479.2 | 0.74 | 0.96 | 34.7% |
| door -x-y (x wall) 1 | 578 | 4.9 | 510.4 | 0.68 | 1.02 | 28.8% |
| door -x-y (x wall) 2 | 300 | 4.9 | 542.4 | 0.33 | 0.96 | 7.3% |
| door -x-y (corner) | 100 | 78.2 | 528.6 | 0.13 | 0.66 | 0.0% |
| door +x-y (y wall) 0 | 572 | 4.9 | 482.2 | 0.72 | 1.02 | 32.7% |
| door +x-y (y wall) 1 | 577 | 4.9 | 499.2 | 0.70 | 1.02 | 29.4% |
| door +x-y (y wall) 2 | 249 | 4.9 | 521.0 | 0.29 | 1.02 | 7.5% |
| door +x-y (x wall) 0 | 587 | 4.9 | 491.1 | 0.72 | 1.08 | 32.0% |
| door +x-y (x wall) 1 | 559 | 4.9 | 504.6 | 0.67 | 1.02 | 21.6% |
| door +x-y (x wall) 2 | 326 | 4.9 | 525.4 | 0.37 | 1.02 | 3.8% |
| door +x-y (corner) | 104 | 47.7 | 526.5 | 0.13 | 0.90 | 0.0% |

Mean flow / w J averaged over the doors 0.52, over the avenues 0.23.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 901 | 584 / 317 / 182 | 0.7 | 484.7 | 2.24 | 3.11 | 90% | 78% | 12% | 3.69 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 548 | 574 / 0 / 12 | 0.7 | 486.9 | 1.20 | 1.71 | 82% | 63% | 18% | 3.48 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 68 | 304 / 0 / 0 | 0.7 | 518.1 | 0.59 | 1.50 | 12% | 10% | 2% | 2.70 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 896 | 575 / 321 / 233 | 0.7 | 476.3 | 2.37 | 4.11 | 90% | 77% | 12% | 3.69 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 527 | 566 / 0 / 7 | 0.7 | 484.8 | 1.18 | 1.71 | 80% | 63% | 16% | 3.46 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 70 | 268 / 0 / 0 | 0.7 | 511.8 | 0.52 | 1.50 | 12% | 10% | 2% | 2.59 |
| corner +x+y | 1.20 | 85.6 | 754 | 126 / 129 / 518 | 0.7 | 515.3 | 1.50 | 4.01 | 85% | 54% | 31% | 2.41 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 897 | 574 / 323 / 220 | 0.7 | 482.6 | 2.32 | 3.81 | 90% | 76% | 14% | 3.65 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 534 | 578 / 0 / 6 | 0.7 | 508.3 | 1.15 | 1.71 | 76% | 63% | 14% | 3.54 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 68 | 282 / 0 / 0 | 0.7 | 505.8 | 0.56 | 1.50 | 12% | 10% | 2% | 2.67 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 894 | 578 / 316 / 195 | 0.7 | 472.9 | 2.31 | 3.61 | 90% | 79% | 10% | 3.85 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 528 | 577 / 0 / 5 | 0.7 | 484.1 | 1.20 | 1.81 | 80% | 67% | 12% | 3.56 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 69 | 274 / 0 / 0 | 0.7 | 505.8 | 0.54 | 1.50 | 12% | 10% | 2% | 2.63 |
| corner -x+y | 1.20 | 85.6 | 742 | 96 / 134 / 523 | 0.7 | 508.1 | 1.48 | 3.71 | 84% | 63% | 22% | 2.52 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 914 | 585 / 329 / 251 | 0.7 | 481.7 | 2.42 | 3.91 | 90% | 78% | 12% | 3.66 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 551 | 574 / 0 / 12 | 0.7 | 524.5 | 1.12 | 1.91 | 77% | 62% | 15% | 3.46 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 67 | 278 / 0 / 0 | 0.7 | 538.4 | 0.52 | 1.50 | 11% | 11% | 0% | 2.72 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 912 | 586 / 326 / 174 | 0.7 | 476.3 | 2.28 | 3.61 | 90% | 79% | 10% | 3.94 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 541 | 580 / 0 / 11 | 0.7 | 507.4 | 1.17 | 1.91 | 82% | 65% | 18% | 3.31 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 66 | 298 / 0 / 0 | 0.7 | 539.4 | 0.55 | 1.50 | 11% | 9% | 2% | 2.75 |
| corner -x-y | 1.20 | 85.6 | 736 | 100 / 131 / 528 | 0.7 | 533.3 | 1.42 | 3.31 | 83% | 54% | 30% | 2.44 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 900 | 572 / 328 / 207 | 0.7 | 479.2 | 2.31 | 3.91 | 84% | 76% | 8% | 3.96 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 544 | 581 / 0 / 5 | 0.7 | 496.2 | 1.18 | 1.71 | 82% | 66% | 16% | 3.50 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 63 | 245 / 0 / 0 | 0.7 | 518.1 | 0.47 | 1.50 | 10% | 10% | 0% | 2.83 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 907 | 587 / 320 / 206 | 0.7 | 488.2 | 2.28 | 3.61 | 92% | 78% | 14% | 3.62 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 544 | 572 / 0 / 6 | 0.7 | 501.6 | 1.15 | 1.91 | 78% | 67% | 12% | 3.58 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 67 | 313 / 0 / 0 | 0.7 | 522.4 | 0.60 | 1.50 | 11% | 9% | 2% | 2.57 |
| corner +x-y | 1.20 | 85.6 | 732 | 104 / 135 / 504 | 0.7 | 522.6 | 1.42 | 3.31 | 83% | 55% | 28% | 2.43 |

The last agent out (agent 7999, t100 542.4 s): last gangway straight -x-y (x wing) 2, exit door -x-y (x wall) 2. The gangway that cleared last: straight -x-y (x wing) 2 at 539.4 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.78 | 531.7 / 524.4 / 487.5 | 518.9 / 492.0 / 422.6 | 637140.1 | 1509299 | 0.218 |
| gangway | 1212 | 1112.9 | 6.78 | 531.7 / 519.5 / 438.0 | 518.9 / 492.0 / 422.6 | 636314.3 | 1365088 | 0.110 |
| walkway | 276 | 257.4 | 2.96 | 182.4 / 105.6 / 0.0 | 116.0 / 22.7 / 0.0 | 0.0 | 23262 | 0.934 |
| avenue | 912 | 858.9 | 1.76 | 194.7 / 0.0 / 0.0 | 163.7 / 0.0 / 0.0 | 0.0 | 89251 | 1.328 |
| exit | 32 | 3.2 | 0.00 | 508.6 / 505.8 / 457.6 | 246.1 / 220.2 / 130.3 | 825.8 | 1572 | 1.325 |
| concourse | 1116 | 1043.8 | 1.93 | 468.9 / 0.0 / 0.0 | 115.6 / 0.0 / 0.0 | 0.0 | 30127 | 1.196 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.60 | 451.1 / 446.5 / 440.6 | 449.2 / 446.5 / 436.9 | 644452.1 | 1833374 | 0.046 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 26.5 | -29.5 | gangway | 1.00 | 6.10 | 440.4 | 397.4 | 368.7 | 2160.1 | 0.021 |
| 2 | -29.5 | -26.5 | gangway | 1.00 | 6.14 | 457.9 | 410.9 | 374.0 | 2155.2 | 0.025 |
| 3 | -26.5 | -29.5 | gangway | 1.00 | 6.08 | 448.8 | 432.2 | 375.5 | 2153.4 | 0.019 |
| 4 | -26.5 | -28.5 | gangway | 1.00 | 6.08 | 450.0 | 443.0 | 382.3 | 2135.1 | 0.019 |
| 5 | -27.5 | 28.5 | gangway | 1.00 | 5.82 | 430.6 | 422.0 | 378.3 | 2129.0 | 0.017 |
| 6 | -28.5 | 27.5 | gangway | 1.00 | 5.66 | 426.6 | 421.0 | 379.5 | 2104.5 | 0.016 |
| 7 | 29.5 | -26.5 | gangway | 1.00 | 6.01 | 429.2 | 399.0 | 353.8 | 2066.2 | 0.021 |
| 8 | 28.5 | 26.5 | gangway | 1.00 | 6.00 | 428.3 | 416.3 | 356.8 | 2055.7 | 0.024 |
| 9 | 27.5 | 26.5 | gangway | 1.00 | 6.15 | 445.7 | 425.7 | 352.1 | 2048.3 | 0.021 |
| 10 | 28.5 | -27.5 | gangway | 1.00 | 5.86 | 444.3 | 440.4 | 363.1 | 2040.8 | 0.022 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 26.5 | -24.5 | seat row | 0.50 | 7.18 | 447.8 | 446.5 | 436.9 | 1514.2 | 0.015 |
| 2 | -24.5 | 26.5 | seat row | 0.50 | 7.10 | 435.7 | 433.4 | 427.6 | 1464.7 | 0.013 |
| 3 | 30.5 | 25.5 | seat row | 0.64 | 6.66 | 388.8 | 385.7 | 356.6 | 1452.3 | 0.027 |
| 4 | -24.5 | -26.5 | seat row | 0.50 | 7.11 | 444.8 | 440.1 | 422.0 | 1447.9 | 0.013 |
| 5 | 24.5 | 26.5 | seat row | 0.50 | 7.11 | 434.3 | 432.0 | 424.8 | 1445.0 | 0.015 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1667; agent-steps of seated agents on another row's clearway: 14307.

## Deposit check

Person-seconds deposited: 3345611.8, of them in excluded cells: 2938.111.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 274776 overlapping pair-steps: p99 0.0023, max 0.0151 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0023 max 0.0151; venue-geometry 3: p99 0.0004 max 0.0004 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 18 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.26 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 558 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
