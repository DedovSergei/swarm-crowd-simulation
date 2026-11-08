# Experiment `M_load94_s8`

**Task 5.11 stage 1 (gridlock robustness, default model, AMD 26.10.1): venue M, 94% load (seed 8)**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 14882 agents on 94% of the 15832 seats (spawnSeatedCrowd, seed 8), buffer N = 16384, 3055 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 1092976 evaluations, 45662 switches, 0 forced choices).
Capacity: **within design capacity** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `15aa31e8667e4a9417fde7884d907d1832c5e2d6`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-23T18:14:04, 108.9 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1203 | 210.4 |
| t90 | 2334 | 408.2 |
| t100 | 3055 | 534.3 |

t_p: the step by which ceil(p x 14882) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 776 | 0 | 39.7 | 467.0 | 19.2 | 25.5 | 75.7-85.7 |
| -x | 5.66 | 779 | 0 | 39.5 | 462.5 | 19.5 | 25.5 | 48.8-58.8 |
| +y | 5.66 | 768 | 0 | 39.7 | 460.7 | 19.3 | 25.5 | 54.6-64.5 |
| -y | 5.66 | 764 | 0 | 39.7 | 463.5 | 19.1 | 26.6 | 73.6-83.6 |
| door +x+y (y wall) 0 | 1.20 | 579 | 1062 | 4.9 | 487.1 | 60.0 | 85.3 | 23.3-33.2 |
| door +x+y (y wall) 1 | 1.20 | 561 | 639 | 4.9 | 497.8 | 56.9 | 85.3 | 4.4-14.3 |
| door +x+y (y wall) 2 | 1.20 | 276 | 170 | 4.9 | 528.7 | 26.3 | 80.2 | 6.1-16.1 |
| door +x+y (x wall) 0 | 1.20 | 586 | 1062 | 4.9 | 487.6 | 60.7 | 85.3 | 10.8-20.8 |
| door +x+y (x wall) 1 | 1.20 | 562 | 642 | 4.9 | 500.2 | 56.7 | 80.2 | 15.6-25.5 |
| door +x+y (x wall) 2 | 1.20 | 291 | 167 | 4.9 | 530.8 | 27.7 | 85.3 | 8.9-18.9 |
| door +x+y (corner) | 1.20 | 108 | 0 | 79.9 | 520.0 | 12.3 | 60.2 | 80.6-90.6 |
| door -x+y (y wall) 0 | 1.20 | 571 | 1045 | 4.9 | 488.5 | 59.0 | 85.3 | 7.3-17.3 |
| door -x+y (y wall) 1 | 1.20 | 578 | 642 | 4.9 | 499.7 | 58.4 | 85.3 | 20.3-30.3 |
| door -x+y (y wall) 2 | 1.20 | 270 | 169 | 4.9 | 525.4 | 25.9 | 80.2 | 4.0-14.0 |
| door -x+y (x wall) 0 | 1.20 | 576 | 1056 | 4.9 | 488.2 | 59.6 | 85.3 | 29.0-39.0 |
| door -x+y (x wall) 1 | 1.20 | 570 | 640 | 4.9 | 502.7 | 57.2 | 90.3 | 19.4-29.4 |
| door -x+y (x wall) 2 | 1.20 | 295 | 164 | 4.9 | 534.3 | 27.9 | 85.3 | 8.7-18.7 |
| door -x+y (corner) | 1.20 | 88 | 0 | 68.7 | 515.5 | 9.8 | 65.2 | 80.8-90.8 |
| door -x-y (y wall) 0 | 1.20 | 572 | 1054 | 4.9 | 493.1 | 58.6 | 85.3 | 19.6-29.6 |
| door -x-y (y wall) 1 | 1.20 | 562 | 633 | 4.9 | 488.2 | 58.1 | 85.3 | 16.1-26.1 |
| door -x-y (y wall) 2 | 1.20 | 312 | 164 | 4.9 | 503.6 | 31.3 | 80.2 | 10.5-20.5 |
| door -x-y (x wall) 0 | 1.20 | 574 | 1056 | 4.9 | 471.5 | 61.5 | 85.3 | 7.3-17.3 |
| door -x-y (x wall) 1 | 1.20 | 561 | 632 | 4.9 | 499.0 | 56.7 | 85.3 | 22.2-32.2 |
| door -x-y (x wall) 2 | 1.20 | 259 | 171 | 4.9 | 508.3 | 25.7 | 80.2 | 9.1-19.1 |
| door -x-y (corner) | 1.20 | 104 | 0 | 57.5 | 491.8 | 12.0 | 65.2 | 381.5-391.4 |
| door +x-y (y wall) 0 | 1.20 | 573 | 1052 | 4.9 | 483.4 | 59.8 | 85.3 | 15.7-25.7 |
| door +x-y (y wall) 1 | 1.20 | 572 | 643 | 4.9 | 489.2 | 59.0 | 85.3 | 18.7-28.7 |
| door +x-y (y wall) 2 | 1.20 | 254 | 168 | 4.9 | 503.9 | 25.4 | 80.2 | 4.7-14.7 |
| door +x-y (x wall) 0 | 1.20 | 567 | 1053 | 4.9 | 476.3 | 60.1 | 90.3 | 15.0-25.0 |
| door +x-y (x wall) 1 | 1.20 | 571 | 629 | 4.9 | 478.7 | 60.2 | 90.3 | 24.1-34.1 |
| door +x-y (x wall) 2 | 1.20 | 291 | 169 | 4.9 | 513.2 | 28.6 | 85.3 | 24.1-34.1 |
| door +x-y (corner) | 1.20 | 112 | 0 | 68.9 | 487.5 | 13.4 | 75.2 | 234.7-244.7 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 776 | 5.2% | 18.4% |
| -x | avenue | 5.66 | 779 | 5.2% | 18.5% |
| +y | avenue | 5.66 | 768 | 5.2% | 18.2% |
| -y | avenue | 5.66 | 764 | 5.1% | 18.1% |
| door +x+y (y wall) 0 | door | 1.20 | 579 | 3.9% | 64.8% |
| door +x+y (y wall) 1 | door | 1.20 | 561 | 3.8% | 62.8% |
| door +x+y (y wall) 2 | door | 1.20 | 276 | 1.9% | 30.9% |
| door +x+y (x wall) 0 | door | 1.20 | 586 | 3.9% | 65.6% |
| door +x+y (x wall) 1 | door | 1.20 | 562 | 3.8% | 62.9% |
| door +x+y (x wall) 2 | door | 1.20 | 291 | 2.0% | 32.6% |
| door +x+y (corner) | door | 1.20 | 108 | 0.7% | 12.1% |
| door -x+y (y wall) 0 | door | 1.20 | 571 | 3.8% | 63.9% |
| door -x+y (y wall) 1 | door | 1.20 | 578 | 3.9% | 64.7% |
| door -x+y (y wall) 2 | door | 1.20 | 270 | 1.8% | 30.2% |
| door -x+y (x wall) 0 | door | 1.20 | 576 | 3.9% | 64.5% |
| door -x+y (x wall) 1 | door | 1.20 | 570 | 3.8% | 63.8% |
| door -x+y (x wall) 2 | door | 1.20 | 295 | 2.0% | 33.0% |
| door -x+y (corner) | door | 1.20 | 88 | 0.6% | 9.8% |
| door -x-y (y wall) 0 | door | 1.20 | 572 | 3.8% | 64.0% |
| door -x-y (y wall) 1 | door | 1.20 | 562 | 3.8% | 62.9% |
| door -x-y (y wall) 2 | door | 1.20 | 312 | 2.1% | 34.9% |
| door -x-y (x wall) 0 | door | 1.20 | 574 | 3.9% | 64.2% |
| door -x-y (x wall) 1 | door | 1.20 | 561 | 3.8% | 62.8% |
| door -x-y (x wall) 2 | door | 1.20 | 259 | 1.7% | 29.0% |
| door -x-y (corner) | door | 1.20 | 104 | 0.7% | 11.6% |
| door +x-y (y wall) 0 | door | 1.20 | 573 | 3.9% | 64.1% |
| door +x-y (y wall) 1 | door | 1.20 | 572 | 3.8% | 64.0% |
| door +x-y (y wall) 2 | door | 1.20 | 254 | 1.7% | 28.4% |
| door +x-y (x wall) 0 | door | 1.20 | 567 | 3.8% | 63.5% |
| door +x-y (x wall) 1 | door | 1.20 | 571 | 3.8% | 63.9% |
| door +x-y (x wall) 2 | door | 1.20 | 291 | 2.0% | 32.6% |
| door +x-y (corner) | door | 1.20 | 112 | 0.8% | 12.5% |
| **doors (28)** | door | 33.60 | 11795 | 79.3% | |
| **avenues (4)** | avenue | 22.64 | 3087 | 20.7% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 534.3 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 35.5%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 899 | 6.0% | 899 | 6.0% |
| straight +x+y (y wing) 1 | straight | yes | 569 | 3.8% | 561 | 3.8% |
| straight +x+y (y wing) 2 | straight | yes | 276 | 1.9% | 276 | 1.9% |
| straight +x+y (x wing) 0 | straight | yes | 904 | 6.1% | 904 | 6.1% |
| straight +x+y (x wing) 1 | straight | yes | 571 | 3.8% | 564 | 3.8% |
| straight +x+y (x wing) 2 | straight | yes | 290 | 1.9% | 289 | 1.9% |
| corner +x+y | corner | yes | 762 | 5.1% | 249 | 1.7% |
| straight -x+y (y wing) 0 | straight | yes | 894 | 6.0% | 894 | 6.0% |
| straight -x+y (y wing) 1 | straight | yes | 583 | 3.9% | 578 | 3.9% |
| straight -x+y (y wing) 2 | straight | yes | 270 | 1.8% | 270 | 1.8% |
| straight -x+y (x wing) 0 | straight | yes | 886 | 6.0% | 886 | 6.0% |
| straight -x+y (x wing) 1 | straight | yes | 576 | 3.9% | 570 | 3.8% |
| straight -x+y (x wing) 2 | straight | yes | 295 | 2.0% | 295 | 2.0% |
| corner -x+y | corner | yes | 753 | 5.1% | 223 | 1.5% |
| straight -x-y (y wing) 0 | straight | yes | 892 | 6.0% | 892 | 6.0% |
| straight -x-y (y wing) 1 | straight | yes | 566 | 3.8% | 562 | 3.8% |
| straight -x-y (y wing) 2 | straight | yes | 311 | 2.1% | 311 | 2.1% |
| straight -x-y (x wing) 0 | straight | yes | 888 | 6.0% | 888 | 6.0% |
| straight -x-y (x wing) 1 | straight | yes | 571 | 3.8% | 566 | 3.8% |
| straight -x-y (x wing) 2 | straight | yes | 254 | 1.7% | 254 | 1.7% |
| corner -x-y | corner | yes | 752 | 5.1% | 237 | 1.6% |
| straight +x-y (y wing) 0 | straight | yes | 890 | 6.0% | 890 | 6.0% |
| straight +x-y (y wing) 1 | straight | yes | 581 | 3.9% | 572 | 3.8% |
| straight +x-y (y wing) 2 | straight | yes | 254 | 1.7% | 254 | 1.7% |
| straight +x-y (x wing) 0 | straight | yes | 889 | 6.0% | 889 | 6.0% |
| straight +x-y (x wing) 1 | straight | yes | 576 | 3.9% | 571 | 3.8% |
| straight +x-y (x wing) 2 | straight | yes | 291 | 2.0% | 291 | 2.0% |
| corner +x-y | corner | yes | 748 | 5.0% | 247 | 1.7% |
| **straight (24)** | | | 13976 | | 13926 | 93.6% |
| **corner (4)** | | | 3015 | | 956 | 6.4% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 776 | 39.7 | 467.0 | 0.23 | 0.31 | 0.0% |
| -x | 779 | 39.5 | 462.5 | 0.23 | 0.31 | 0.0% |
| +y | 768 | 39.7 | 460.7 | 0.23 | 0.31 | 0.0% |
| -y | 764 | 39.7 | 463.5 | 0.23 | 0.32 | 0.0% |
| door +x+y (y wall) 0 | 579 | 4.9 | 487.1 | 0.72 | 1.02 | 36.7% |
| door +x+y (y wall) 1 | 561 | 4.9 | 497.8 | 0.68 | 1.02 | 34.0% |
| door +x+y (y wall) 2 | 276 | 4.9 | 528.7 | 0.32 | 0.96 | 3.7% |
| door +x+y (x wall) 0 | 586 | 4.9 | 487.6 | 0.73 | 1.02 | 36.7% |
| door +x+y (x wall) 1 | 562 | 4.9 | 500.2 | 0.68 | 0.96 | 23.5% |
| door +x+y (x wall) 2 | 291 | 4.9 | 530.8 | 0.33 | 1.02 | 5.6% |
| door +x+y (corner) | 108 | 79.9 | 520.0 | 0.15 | 0.72 | 0.0% |
| door -x+y (y wall) 0 | 571 | 4.9 | 488.5 | 0.71 | 1.02 | 28.6% |
| door -x+y (y wall) 1 | 578 | 4.9 | 499.7 | 0.70 | 1.02 | 31.4% |
| door -x+y (y wall) 2 | 270 | 4.9 | 525.4 | 0.31 | 0.96 | 3.8% |
| door -x+y (x wall) 0 | 576 | 4.9 | 488.2 | 0.71 | 1.02 | 32.7% |
| door -x+y (x wall) 1 | 570 | 4.9 | 502.7 | 0.68 | 1.08 | 27.5% |
| door -x+y (x wall) 2 | 295 | 4.9 | 534.3 | 0.33 | 1.02 | 3.7% |
| door -x+y (corner) | 88 | 68.7 | 515.5 | 0.12 | 0.78 | 0.0% |
| door -x-y (y wall) 0 | 572 | 4.9 | 493.1 | 0.70 | 1.02 | 28.0% |
| door -x-y (y wall) 1 | 562 | 4.9 | 488.2 | 0.70 | 1.02 | 24.5% |
| door -x-y (y wall) 2 | 312 | 4.9 | 503.6 | 0.37 | 0.96 | 3.9% |
| door -x-y (x wall) 0 | 574 | 4.9 | 471.5 | 0.74 | 1.02 | 41.7% |
| door -x-y (x wall) 1 | 561 | 4.9 | 499.0 | 0.68 | 1.02 | 27.5% |
| door -x-y (x wall) 2 | 259 | 4.9 | 508.3 | 0.31 | 0.96 | 7.8% |
| door -x-y (corner) | 104 | 57.5 | 491.8 | 0.14 | 0.78 | 0.0% |
| door +x-y (y wall) 0 | 573 | 4.9 | 483.4 | 0.72 | 1.02 | 24.5% |
| door +x-y (y wall) 1 | 572 | 4.9 | 489.2 | 0.71 | 1.02 | 34.0% |
| door +x-y (y wall) 2 | 254 | 4.9 | 503.9 | 0.30 | 0.96 | 5.9% |
| door +x-y (x wall) 0 | 567 | 4.9 | 476.3 | 0.72 | 1.08 | 31.2% |
| door +x-y (x wall) 1 | 571 | 4.9 | 478.7 | 0.72 | 1.08 | 30.6% |
| door +x-y (x wall) 2 | 291 | 4.9 | 513.2 | 0.34 | 1.02 | 5.8% |
| door +x-y (corner) | 112 | 68.9 | 487.5 | 0.16 | 0.90 | 0.0% |

Mean flow / w J averaged over the doors 0.52, over the avenues 0.23.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 899 | 579 / 320 / 195 | 0.7 | 484.1 | 2.26 | 3.21 | 90% | 78% | 12% | 3.65 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 535 | 561 / 0 / 11 | 0.7 | 494.8 | 1.16 | 1.81 | 82% | 62% | 20% | 3.41 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 63 | 276 / 0 / 0 | 0.7 | 525.8 | 0.53 | 1.40 | 9% | 9% | 0% | 2.70 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 904 | 586 / 318 / 194 | 0.7 | 484.7 | 2.27 | 3.41 | 90% | 78% | 12% | 3.64 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 525 | 564 / 0 / 10 | 0.7 | 497.3 | 1.16 | 1.60 | 82% | 66% | 16% | 3.38 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 63 | 289 / 0 / 1 | 0.7 | 527.9 | 0.55 | 1.50 | 9% | 9% | 0% | 2.68 |
| corner +x+y | 1.20 | 85.6 | 753 | 108 / 141 / 526 | 0.7 | 521.7 | 1.49 | 4.21 | 85% | 49% | 36% | 2.33 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 894 | 571 / 323 / 252 | 0.7 | 485.5 | 2.36 | 4.01 | 90% | 76% | 14% | 3.63 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 531 | 578 / 0 / 10 | 0.7 | 496.7 | 1.18 | 1.71 | 78% | 66% | 12% | 3.47 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 65 | 270 / 0 / 0 | 0.7 | 522.4 | 0.52 | 1.40 | 11% | 9% | 2% | 2.48 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 886 | 576 / 310 / 206 | 0.7 | 485.2 | 2.25 | 3.81 | 90% | 78% | 12% | 3.72 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 533 | 570 / 0 / 9 | 0.7 | 499.7 | 1.16 | 1.81 | 78% | 65% | 14% | 3.45 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 62 | 295 / 0 / 0 | 0.7 | 531.4 | 0.56 | 1.71 | 9% | 9% | 0% | 2.81 |
| corner -x+y | 1.20 | 85.6 | 745 | 88 / 135 / 541 | 0.7 | 525.4 | 1.46 | 4.61 | 83% | 57% | 26% | 2.43 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 892 | 572 / 320 / 203 | 0.7 | 490.1 | 2.24 | 3.91 | 90% | 74% | 16% | 3.57 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 522 | 562 / 0 / 5 | 0.7 | 485.2 | 1.17 | 1.60 | 84% | 65% | 18% | 3.36 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 64 | 311 / 0 / 0 | 0.7 | 500.6 | 0.62 | 1.50 | 12% | 10% | 2% | 2.77 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 888 | 574 / 314 / 213 | 0.7 | 468.6 | 2.35 | 3.91 | 91% | 79% | 13% | 3.77 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 532 | 566 / 0 / 7 | 0.7 | 496.0 | 1.16 | 1.60 | 82% | 66% | 16% | 3.42 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 66 | 254 / 0 / 0 | 0.7 | 505.3 | 0.50 | 1.60 | 12% | 10% | 2% | 2.68 |
| corner -x-y | 1.20 | 85.6 | 746 | 105 / 132 / 521 | 0.7 | 499.4 | 1.52 | 3.61 | 86% | 55% | 31% | 2.43 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 890 | 573 / 317 / 217 | 0.7 | 480.5 | 2.31 | 4.01 | 90% | 78% | 12% | 3.74 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 532 | 572 / 0 / 14 | 0.7 | 486.2 | 1.21 | 1.71 | 80% | 65% | 14% | 3.35 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 66 | 254 / 0 / 0 | 0.7 | 500.9 | 0.51 | 1.50 | 12% | 10% | 2% | 2.63 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 889 | 567 / 322 / 219 | 0.7 | 473.3 | 2.34 | 3.61 | 90% | 77% | 12% | 3.69 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 531 | 571 / 0 / 47 | 0.7 | 475.7 | 1.30 | 2.41 | 81% | 65% | 17% | 3.44 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 68 | 291 / 0 / 0 | 0.7 | 510.2 | 0.57 | 1.50 | 12% | 12% | 0% | 2.67 |
| corner +x-y | 1.20 | 85.6 | 738 | 112 / 135 / 552 | 0.7 | 504.3 | 1.59 | 3.71 | 86% | 57% | 29% | 2.41 |

The last agent out (agent 4092, t100 534.3 s): last gangway straight -x+y (x wing) 2, exit door -x+y (x wall) 2. The gangway that cleared last: straight -x+y (x wing) 2 at 531.4 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 7.05 | 524.9 / 512.0 / 475.7 | 513.2 / 477.1 / 402.8 | 623900.5 | 1484777 | 0.220 |
| gangway | 1212 | 1112.9 | 7.05 | 524.9 / 506.9 / 433.9 | 513.2 / 477.1 / 402.8 | 623076.5 | 1341207 | 0.112 |
| walkway | 276 | 257.4 | 3.15 | 199.9 / 108.1 / 0.0 | 121.2 / 33.9 / 0.0 | 0.0 | 23786 | 0.909 |
| avenue | 912 | 858.9 | 1.99 | 211.3 / 0.0 / 0.0 | 166.3 / 0.0 / 0.0 | 0.0 | 88622 | 1.327 |
| exit | 32 | 3.2 | 0.00 | 499.0 / 495.5 / 438.3 | 240.7 / 216.0 / 128.7 | 824.1 | 1554 | 1.323 |
| concourse | 1116 | 1043.8 | 2.17 | 468.4 / 0.2 / 0.0 | 116.1 / 0.2 / 0.0 | 0.0 | 29609 | 1.195 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.62 | 461.9 / 452.0 / 432.7 | 454.2 / 452.0 / 422.2 | 624266.9 | 1783071 | 0.047 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 26.5 | 28.5 | gangway | 1.00 | 6.10 | 444.3 | 439.4 | 365.2 | 2131.3 | 0.020 |
| 2 | 29.5 | -26.5 | gangway | 1.00 | 6.03 | 425.0 | 383.9 | 347.0 | 2028.0 | 0.026 |
| 3 | 26.5 | 29.5 | gangway | 1.00 | 5.87 | 435.2 | 411.0 | 352.6 | 2025.1 | 0.023 |
| 4 | 27.5 | -27.5 | gangway | 1.00 | 6.04 | 426.9 | 423.6 | 354.4 | 2023.2 | 0.018 |
| 5 | -28.5 | -26.5 | gangway | 1.00 | 6.01 | 454.1 | 435.3 | 349.3 | 2021.4 | 0.022 |
| 6 | -27.5 | -27.5 | gangway | 1.00 | 5.70 | 442.9 | 432.9 | 363.6 | 2007.5 | 0.022 |
| 7 | -28.5 | 26.5 | gangway | 1.00 | 5.86 | 435.9 | 424.0 | 351.6 | 1994.3 | 0.023 |
| 8 | 28.5 | -26.5 | gangway | 1.00 | 5.99 | 439.2 | 422.7 | 341.6 | 1979.7 | 0.024 |
| 9 | -27.5 | -28.5 | gangway | 1.00 | 6.06 | 439.7 | 432.4 | 334.1 | 1970.0 | 0.024 |
| 10 | 27.5 | -26.5 | gangway | 1.00 | 5.78 | 437.3 | 429.7 | 352.1 | 1954.3 | 0.021 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 26.5 | 24.5 | seat row | 0.50 | 7.31 | 454.2 | 452.0 | 420.8 | 1466.1 | 0.014 |
| 2 | -24.5 | -26.5 | seat row | 0.50 | 7.19 | 435.9 | 434.8 | 421.0 | 1442.8 | 0.016 |
| 3 | -26.5 | 24.5 | seat row | 0.50 | 7.27 | 438.3 | 436.6 | 422.2 | 1439.5 | 0.015 |
| 4 | 26.5 | -24.5 | seat row | 0.50 | 7.12 | 436.9 | 435.3 | 421.7 | 1437.5 | 0.015 |
| 5 | -24.5 | 26.5 | seat row | 0.50 | 7.14 | 437.8 | 426.4 | 404.4 | 1385.7 | 0.015 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1700; agent-steps of seated agents on another row's clearway: 15793.

## Deposit check

Person-seconds deposited: 3270755.3, of them in excluded cells: 2906.555.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 247912 overlapping pair-steps: p99 0.0029, max 0.0353 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0029 max 0.0353; venue-geometry 4: p99 0.0004 max 0.0004 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00755 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 9 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.29 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 584 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
