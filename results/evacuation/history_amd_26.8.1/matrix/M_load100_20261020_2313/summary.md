# Experiment `M_load100`

**Task 5.9 stage 4: venue M, 100% load, default model**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 15832 agents on 100% of the 15832 seats (spawnSeatedCrowd, seed 1337), buffer N = 16384, 3212 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 1240058 evaluations, 50598 switches, 0 forced choices).
Capacity: **within design capacity** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-20T23:13:08, 76.8 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1286 | 224.9 |
| t90 | 2497 | 436.7 |
| t100 | 3212 | 561.8 |

t_p: the step by which ceil(p x 15832) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 817 | 0 | 39.7 | 490.8 | 19.2 | 25.5 | 49.0-58.9 |
| -x | 5.66 | 809 | 0 | 39.7 | 494.3 | 18.9 | 25.5 | 49.0-58.9 |
| +y | 5.66 | 821 | 0 | 39.7 | 493.4 | 19.2 | 25.5 | 49.7-59.6 |
| -y | 5.66 | 814 | 0 | 39.7 | 498.3 | 18.8 | 26.6 | 105.6-115.6 |
| door +x+y (y wall) 0 | 1.20 | 618 | 1121 | 4.9 | 509.5 | 61.2 | 90.3 | 16.4-26.4 |
| door +x+y (y wall) 1 | 1.20 | 599 | 680 | 4.9 | 525.4 | 57.5 | 90.3 | 16.3-26.2 |
| door +x+y (y wall) 2 | 1.20 | 263 | 178 | 4.9 | 536.8 | 24.7 | 80.2 | 4.7-14.7 |
| door +x+y (x wall) 0 | 1.20 | 616 | 1121 | 4.9 | 509.3 | 61.0 | 90.3 | 16.4-26.4 |
| door +x+y (x wall) 1 | 1.20 | 600 | 680 | 4.9 | 535.2 | 56.6 | 90.3 | 16.3-26.2 |
| door +x+y (x wall) 2 | 1.20 | 328 | 178 | 4.9 | 543.8 | 30.4 | 80.2 | 4.7-14.7 |
| door +x+y (corner) | 1.20 | 113 | 0 | 83.4 | 543.4 | 12.3 | 85.3 | 86.8-96.7 |
| door -x+y (y wall) 0 | 1.20 | 613 | 1121 | 4.9 | 514.9 | 60.1 | 85.3 | 12.9-22.9 |
| door -x+y (y wall) 1 | 1.20 | 600 | 680 | 4.9 | 526.6 | 57.5 | 90.3 | 25.2-35.2 |
| door -x+y (y wall) 2 | 1.20 | 312 | 178 | 4.9 | 534.2 | 29.5 | 80.2 | 4.7-14.7 |
| door -x+y (x wall) 0 | 1.20 | 621 | 1121 | 4.9 | 528.2 | 59.3 | 95.3 | 28.3-38.3 |
| door -x+y (x wall) 1 | 1.20 | 597 | 680 | 4.9 | 528.0 | 57.0 | 85.3 | 12.9-22.9 |
| door -x+y (x wall) 2 | 1.20 | 318 | 178 | 4.9 | 536.4 | 29.9 | 80.2 | 4.7-14.7 |
| door -x+y (corner) | 1.20 | 86 | 0 | 71.9 | 539.6 | 9.2 | 55.2 | 79.6-89.6 |
| door -x-y (y wall) 0 | 1.20 | 620 | 1121 | 4.9 | 521.4 | 60.0 | 85.3 | 12.9-22.9 |
| door -x-y (y wall) 1 | 1.20 | 610 | 680 | 4.9 | 524.5 | 58.7 | 85.3 | 12.8-22.7 |
| door -x-y (y wall) 2 | 1.20 | 315 | 178 | 4.9 | 559.4 | 28.4 | 80.2 | 4.7-14.7 |
| door -x-y (x wall) 0 | 1.20 | 622 | 1121 | 4.9 | 514.8 | 61.0 | 90.3 | 27.3-37.3 |
| door -x-y (x wall) 1 | 1.20 | 613 | 680 | 4.9 | 523.5 | 59.1 | 85.3 | 12.8-22.7 |
| door -x-y (x wall) 2 | 1.20 | 274 | 178 | 4.9 | 561.8 | 24.6 | 80.2 | 4.7-14.7 |
| door -x-y (corner) | 1.20 | 88 | 0 | 85.4 | 559.9 | 9.3 | 75.2 | 99.2-109.1 |
| door +x-y (y wall) 0 | 1.20 | 627 | 1121 | 4.9 | 518.9 | 61.0 | 90.3 | 26.9-36.9 |
| door +x-y (y wall) 1 | 1.20 | 599 | 680 | 4.9 | 501.1 | 60.3 | 85.3 | 12.9-22.9 |
| door +x-y (y wall) 2 | 1.20 | 289 | 178 | 4.9 | 543.3 | 26.8 | 80.2 | 4.7-14.7 |
| door +x-y (x wall) 0 | 1.20 | 618 | 1121 | 4.9 | 511.3 | 61.0 | 85.3 | 12.9-22.9 |
| door +x-y (x wall) 1 | 1.20 | 604 | 680 | 4.9 | 517.5 | 58.9 | 90.3 | 24.0-33.9 |
| door +x-y (x wall) 2 | 1.20 | 289 | 178 | 4.9 | 544.5 | 26.8 | 80.2 | 4.7-14.7 |
| door +x-y (corner) | 1.20 | 119 | 0 | 79.8 | 542.9 | 12.8 | 85.3 | 363.6-373.6 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 817 | 5.2% | 18.4% |
| -x | avenue | 5.66 | 809 | 5.1% | 18.3% |
| +y | avenue | 5.66 | 821 | 5.2% | 18.5% |
| -y | avenue | 5.66 | 814 | 5.1% | 18.4% |
| door +x+y (y wall) 0 | door | 1.20 | 618 | 3.9% | 65.8% |
| door +x+y (y wall) 1 | door | 1.20 | 599 | 3.8% | 63.8% |
| door +x+y (y wall) 2 | door | 1.20 | 263 | 1.7% | 28.0% |
| door +x+y (x wall) 0 | door | 1.20 | 616 | 3.9% | 65.6% |
| door +x+y (x wall) 1 | door | 1.20 | 600 | 3.8% | 63.9% |
| door +x+y (x wall) 2 | door | 1.20 | 328 | 2.1% | 34.9% |
| door +x+y (corner) | door | 1.20 | 113 | 0.7% | 12.0% |
| door -x+y (y wall) 0 | door | 1.20 | 613 | 3.9% | 65.3% |
| door -x+y (y wall) 1 | door | 1.20 | 600 | 3.8% | 63.9% |
| door -x+y (y wall) 2 | door | 1.20 | 312 | 2.0% | 33.2% |
| door -x+y (x wall) 0 | door | 1.20 | 621 | 3.9% | 66.1% |
| door -x+y (x wall) 1 | door | 1.20 | 597 | 3.8% | 63.6% |
| door -x+y (x wall) 2 | door | 1.20 | 318 | 2.0% | 33.9% |
| door -x+y (corner) | door | 1.20 | 86 | 0.5% | 9.2% |
| door -x-y (y wall) 0 | door | 1.20 | 620 | 3.9% | 66.0% |
| door -x-y (y wall) 1 | door | 1.20 | 610 | 3.9% | 64.9% |
| door -x-y (y wall) 2 | door | 1.20 | 315 | 2.0% | 33.5% |
| door -x-y (x wall) 0 | door | 1.20 | 622 | 3.9% | 66.2% |
| door -x-y (x wall) 1 | door | 1.20 | 613 | 3.9% | 65.3% |
| door -x-y (x wall) 2 | door | 1.20 | 274 | 1.7% | 29.2% |
| door -x-y (corner) | door | 1.20 | 88 | 0.6% | 9.4% |
| door +x-y (y wall) 0 | door | 1.20 | 627 | 4.0% | 66.7% |
| door +x-y (y wall) 1 | door | 1.20 | 599 | 3.8% | 63.8% |
| door +x-y (y wall) 2 | door | 1.20 | 289 | 1.8% | 30.8% |
| door +x-y (x wall) 0 | door | 1.20 | 618 | 3.9% | 65.8% |
| door +x-y (x wall) 1 | door | 1.20 | 604 | 3.8% | 64.3% |
| door +x-y (x wall) 2 | door | 1.20 | 289 | 1.8% | 30.8% |
| door +x-y (corner) | door | 1.20 | 119 | 0.8% | 12.7% |
| **doors (28)** | door | 33.60 | 12571 | 79.4% | |
| **avenues (4)** | avenue | 22.64 | 3261 | 20.6% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 561.8 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 36.0%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 961 | 6.1% | 961 | 6.1% |
| straight +x+y (y wing) 1 | straight | yes | 603 | 3.8% | 599 | 3.8% |
| straight +x+y (y wing) 2 | straight | yes | 263 | 1.7% | 263 | 1.7% |
| straight +x+y (x wing) 0 | straight | yes | 955 | 6.0% | 955 | 6.0% |
| straight +x+y (x wing) 1 | straight | yes | 605 | 3.8% | 602 | 3.8% |
| straight +x+y (x wing) 2 | straight | yes | 326 | 2.1% | 326 | 2.1% |
| corner +x+y | corner | yes | 770 | 4.9% | 252 | 1.6% |
| straight -x+y (y wing) 0 | straight | yes | 951 | 6.0% | 951 | 6.0% |
| straight -x+y (y wing) 1 | straight | yes | 608 | 3.8% | 604 | 3.8% |
| straight -x+y (y wing) 2 | straight | yes | 308 | 1.9% | 308 | 1.9% |
| straight -x+y (x wing) 0 | straight | yes | 957 | 6.0% | 957 | 6.0% |
| straight -x+y (x wing) 1 | straight | yes | 612 | 3.9% | 608 | 3.8% |
| straight -x+y (x wing) 2 | straight | yes | 309 | 2.0% | 309 | 2.0% |
| corner -x+y | corner | yes | 775 | 4.9% | 221 | 1.4% |
| straight -x-y (y wing) 0 | straight | yes | 956 | 6.0% | 956 | 6.0% |
| straight -x-y (y wing) 1 | straight | yes | 615 | 3.9% | 610 | 3.9% |
| straight -x-y (y wing) 2 | straight | yes | 316 | 2.0% | 315 | 2.0% |
| straight -x-y (x wing) 0 | straight | yes | 965 | 6.1% | 965 | 6.1% |
| straight -x-y (x wing) 1 | straight | yes | 615 | 3.9% | 613 | 3.9% |
| straight -x-y (x wing) 2 | straight | yes | 274 | 1.7% | 274 | 1.7% |
| corner -x-y | corner | yes | 774 | 4.9% | 225 | 1.4% |
| straight +x-y (y wing) 0 | straight | yes | 966 | 6.1% | 966 | 6.1% |
| straight +x-y (y wing) 1 | straight | yes | 605 | 3.8% | 601 | 3.8% |
| straight +x-y (y wing) 2 | straight | yes | 288 | 1.8% | 288 | 1.8% |
| straight +x-y (x wing) 0 | straight | yes | 956 | 6.0% | 956 | 6.0% |
| straight +x-y (x wing) 1 | straight | yes | 613 | 3.9% | 608 | 3.8% |
| straight +x-y (x wing) 2 | straight | yes | 285 | 1.8% | 285 | 1.8% |
| corner +x-y | corner | yes | 783 | 4.9% | 254 | 1.6% |
| **straight (24)** | | | 14912 | | 14880 | 94.0% |
| **corner (4)** | | | 3102 | | 952 | 6.0% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 817 | 39.7 | 490.8 | 0.23 | 0.31 | 0.0% |
| -x | 809 | 39.7 | 494.3 | 0.23 | 0.31 | 0.0% |
| +y | 821 | 39.7 | 493.4 | 0.23 | 0.31 | 0.0% |
| -y | 814 | 39.7 | 498.3 | 0.22 | 0.32 | 0.0% |
| door +x+y (y wall) 0 | 618 | 4.9 | 509.5 | 0.73 | 1.08 | 34.6% |
| door +x+y (y wall) 1 | 599 | 4.9 | 525.4 | 0.69 | 1.08 | 18.9% |
| door +x+y (y wall) 2 | 263 | 4.9 | 536.8 | 0.30 | 0.96 | 3.7% |
| door +x+y (x wall) 0 | 616 | 4.9 | 509.3 | 0.73 | 1.08 | 36.5% |
| door +x+y (x wall) 1 | 600 | 4.9 | 535.2 | 0.68 | 1.08 | 29.6% |
| door +x+y (x wall) 2 | 328 | 4.9 | 543.8 | 0.36 | 0.96 | 7.3% |
| door +x+y (corner) | 113 | 83.4 | 543.4 | 0.15 | 1.02 | 2.1% |
| door -x+y (y wall) 0 | 613 | 4.9 | 514.9 | 0.72 | 1.02 | 26.9% |
| door -x+y (y wall) 1 | 600 | 4.9 | 526.6 | 0.69 | 1.08 | 24.5% |
| door -x+y (y wall) 2 | 312 | 4.9 | 534.2 | 0.35 | 0.96 | 7.4% |
| door -x+y (x wall) 0 | 621 | 4.9 | 528.2 | 0.71 | 1.14 | 37.7% |
| door -x+y (x wall) 1 | 597 | 4.9 | 528.0 | 0.68 | 1.02 | 30.2% |
| door -x+y (x wall) 2 | 318 | 4.9 | 536.4 | 0.36 | 0.96 | 3.7% |
| door -x+y (corner) | 86 | 71.9 | 539.6 | 0.11 | 0.66 | 0.0% |
| door -x-y (y wall) 0 | 620 | 4.9 | 521.4 | 0.72 | 1.02 | 32.1% |
| door -x-y (y wall) 1 | 610 | 4.9 | 524.5 | 0.70 | 1.02 | 26.4% |
| door -x-y (y wall) 2 | 315 | 4.9 | 559.4 | 0.34 | 0.96 | 3.5% |
| door -x-y (x wall) 0 | 622 | 4.9 | 514.8 | 0.73 | 1.08 | 30.8% |
| door -x-y (x wall) 1 | 613 | 4.9 | 523.5 | 0.71 | 1.02 | 28.3% |
| door -x-y (x wall) 2 | 274 | 4.9 | 561.8 | 0.29 | 0.96 | 5.3% |
| door -x-y (corner) | 88 | 85.4 | 559.9 | 0.11 | 0.90 | 2.0% |
| door +x-y (y wall) 0 | 627 | 4.9 | 518.9 | 0.73 | 1.08 | 41.5% |
| door +x-y (y wall) 1 | 599 | 4.9 | 501.1 | 0.72 | 1.02 | 35.3% |
| door +x-y (y wall) 2 | 289 | 4.9 | 543.3 | 0.32 | 0.96 | 7.3% |
| door +x-y (x wall) 0 | 618 | 4.9 | 511.3 | 0.73 | 1.02 | 34.6% |
| door +x-y (x wall) 1 | 604 | 4.9 | 517.5 | 0.70 | 1.08 | 26.9% |
| door +x-y (x wall) 2 | 289 | 4.9 | 544.5 | 0.32 | 0.96 | 5.5% |
| door +x-y (corner) | 119 | 79.8 | 542.9 | 0.15 | 1.02 | 2.1% |

Mean flow / w J averaged over the doors 0.52, over the avenues 0.23.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 961 | 618 / 343 / 232 | 0.7 | 506.5 | 2.36 | 3.61 | 90% | 78% | 12% | 3.78 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 570 | 599 / 0 / 9 | 0.7 | 522.4 | 1.16 | 1.91 | 83% | 68% | 15% | 3.54 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 69 | 263 / 0 / 0 | 0.7 | 533.8 | 0.49 | 1.50 | 11% | 9% | 2% | 2.64 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 955 | 616 / 339 / 240 | 0.7 | 506.4 | 2.36 | 3.61 | 90% | 80% | 10% | 3.85 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 573 | 602 / 0 / 9 | 0.7 | 532.2 | 1.15 | 1.91 | 81% | 63% | 19% | 3.40 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 69 | 326 / 0 / 0 | 0.7 | 540.8 | 0.60 | 1.50 | 11% | 11% | 0% | 2.67 |
| corner +x+y | 1.20 | 85.6 | 761 | 113 / 139 / 527 | 0.7 | 539.6 | 1.45 | 3.71 | 85% | 53% | 33% | 2.34 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 951 | 613 / 339 / 233 | 0.7 | 512.0 | 2.32 | 3.91 | 90% | 79% | 12% | 3.80 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 578 | 604 / 0 / 9 | 0.7 | 523.7 | 1.17 | 1.91 | 87% | 68% | 19% | 3.36 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 69 | 308 / 0 / 0 | 0.7 | 531.2 | 0.58 | 1.50 | 11% | 11% | 0% | 2.69 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 957 | 619 / 338 / 216 | 0.7 | 505.1 | 2.32 | 3.51 | 90% | 80% | 10% | 3.80 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 566 | 608 / 0 / 7 | 0.7 | 525.1 | 1.17 | 1.91 | 81% | 68% | 13% | 3.49 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 69 | 309 / 0 / 0 | 0.7 | 533.5 | 0.58 | 1.50 | 11% | 11% | 0% | 2.70 |
| corner -x+y | 1.20 | 85.6 | 768 | 86 / 135 / 563 | 0.7 | 535.7 | 1.46 | 3.91 | 89% | 56% | 33% | 2.32 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 956 | 620 / 336 / 185 | 0.7 | 518.4 | 2.20 | 3.71 | 92% | 79% | 13% | 3.72 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 568 | 610 / 0 / 8 | 0.7 | 521.6 | 1.19 | 1.91 | 81% | 68% | 13% | 3.47 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 69 | 315 / 0 / 1 | 0.7 | 556.4 | 0.57 | 1.50 | 11% | 9% | 2% | 2.72 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 965 | 622 / 344 / 236 | 0.7 | 511.8 | 2.35 | 3.91 | 90% | 77% | 13% | 3.74 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 562 | 613 / 0 / 6 | 0.7 | 520.5 | 1.19 | 1.91 | 81% | 64% | 17% | 3.46 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 69 | 274 / 0 / 0 | 0.7 | 558.8 | 0.49 | 1.50 | 11% | 9% | 2% | 2.70 |
| corner -x-y | 1.20 | 85.6 | 769 | 88 / 137 / 559 | 0.7 | 556.0 | 1.41 | 3.71 | 86% | 61% | 25% | 2.41 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 966 | 627 / 339 / 237 | 0.7 | 516.0 | 2.33 | 4.01 | 90% | 77% | 13% | 3.71 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 558 | 601 / 0 / 6 | 0.7 | 498.1 | 1.22 | 1.91 | 84% | 70% | 14% | 3.48 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 70 | 288 / 0 / 0 | 0.7 | 540.3 | 0.53 | 1.50 | 11% | 11% | 0% | 2.69 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 956 | 618 / 338 / 230 | 0.7 | 508.3 | 2.34 | 3.41 | 92% | 78% | 14% | 3.74 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 564 | 608 / 0 / 7 | 0.7 | 514.6 | 1.20 | 1.91 | 81% | 67% | 13% | 3.51 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 69 | 285 / 0 / 0 | 0.7 | 541.5 | 0.53 | 1.50 | 11% | 9% | 2% | 2.67 |
| corner +x-y | 1.20 | 85.6 | 775 | 118 / 136 / 534 | 0.7 | 539.1 | 1.46 | 3.71 | 84% | 58% | 25% | 2.43 |

The last agent out (agent 8291, t100 561.8 s): last gangway straight -x-y (x wing) 2, exit door -x-y (x wall) 2. The gangway that cleared last: straight -x-y (x wing) 2 at 558.8 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.90 | 558.5 / 544.0 / 509.9 | 540.1 / 514.8 / 446.4 | 701860.5 | 1601922 | 0.216 |
| gangway | 1212 | 1112.9 | 6.90 | 556.0 / 540.1 / 462.1 | 540.1 / 514.8 / 446.4 | 700990.0 | 1449301 | 0.109 |
| walkway | 276 | 257.4 | 3.24 | 169.8 / 101.3 / 0.0 | 118.1 / 31.0 / 0.0 | 0.0 | 25679 | 0.889 |
| avenue | 912 | 858.9 | 1.80 | 185.8 / 0.0 / 0.0 | 146.0 / 0.0 / 0.0 | 0.0 | 93609 | 1.328 |
| exit | 32 | 3.2 | 0.00 | 525.4 / 523.0 / 463.3 | 257.3 / 230.7 / 136.4 | 870.5 | 1647 | 1.322 |
| concourse | 1116 | 1043.8 | 2.35 | 492.0 / 0.7 / 0.0 | 123.1 / 0.7 / 0.0 | 0.0 | 31686 | 1.195 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.53 | 490.8 / 478.0 / 470.3 | 479.9 / 478.0 / 466.7 | 755739.1 | 2104222 | 0.042 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 27.5 | -27.5 | gangway | 1.00 | 5.93 | 473.1 | 466.7 | 411.7 | 2360.0 | 0.017 |
| 2 | -28.5 | 26.5 | gangway | 1.00 | 6.16 | 480.3 | 474.0 | 396.7 | 2342.5 | 0.020 |
| 3 | -26.5 | 28.5 | gangway | 1.00 | 5.94 | 477.7 | 475.2 | 404.0 | 2304.5 | 0.018 |
| 4 | -26.5 | -27.5 | gangway | 1.00 | 6.15 | 472.4 | 465.3 | 397.6 | 2296.3 | 0.017 |
| 5 | -27.5 | -28.5 | gangway | 1.00 | 6.12 | 472.1 | 462.8 | 398.6 | 2290.5 | 0.017 |
| 6 | 28.5 | -26.5 | gangway | 1.00 | 6.27 | 465.4 | 450.9 | 378.3 | 2285.3 | 0.020 |
| 7 | 29.5 | 26.5 | gangway | 1.00 | 6.16 | 476.4 | 448.1 | 389.7 | 2285.3 | 0.019 |
| 8 | -27.5 | -27.5 | gangway | 1.00 | 5.90 | 472.2 | 459.1 | 406.8 | 2269.3 | 0.016 |
| 9 | -26.5 | 29.5 | gangway | 1.00 | 6.19 | 481.3 | 474.0 | 383.7 | 2268.9 | 0.018 |
| 10 | 26.5 | 28.5 | gangway | 1.00 | 6.13 | 469.8 | 459.3 | 391.3 | 2266.8 | 0.020 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -26.5 | -24.5 | seat row | 0.50 | 7.35 | 479.9 | 478.0 | 466.7 | 1612.9 | 0.013 |
| 2 | 24.5 | -26.5 | seat row | 0.50 | 7.38 | 467.4 | 463.9 | 452.5 | 1612.2 | 0.014 |
| 3 | -24.5 | 26.5 | seat row | 0.50 | 7.18 | 477.8 | 474.7 | 459.1 | 1599.3 | 0.013 |
| 4 | 26.5 | -24.5 | seat row | 0.50 | 7.16 | 464.2 | 462.3 | 447.6 | 1560.5 | 0.013 |
| 5 | -26.5 | 24.5 | seat row | 0.50 | 7.30 | 467.9 | 459.3 | 446.9 | 1551.6 | 0.014 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1810; agent-steps of seated agents on another row's clearway: 14966.

## Deposit check

Person-seconds deposited: 3709249.2, of them in excluded cells: 3105.411.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 338908 overlapping pair-steps: p99 0.0032, max 0.0808 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0032 max 0.0808; venue-geometry 1: p99 0.0003 max 0.0003 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00751 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 12 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.36 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 625 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
