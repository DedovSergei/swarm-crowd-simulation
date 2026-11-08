# Experiment `M_load95_s2`

**Task 5.9 stage 4: venue M, 95% load (seed 2), default model**

Venue M (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (2375 x 2375), cache key 9dab1161288587e6, content hash 3a93c6e67b76013c). 15040 agents on 95% of the 15832 seats (spawnSeatedCrowd, seed 2), buffer N = 16384, 3065 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 1122647 evaluations, 45652 switches, 0 forced choices).
Capacity: **within design capacity** (the M venue's design capacity 15832, jam capacity 52871: 7326.1 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-20T23:16:28, 70.6 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1228 | 214.8 |
| t90 | 2365 | 413.7 |
| t100 | 3065 | 536.1 |

t_p: the step by which ceil(p x 15040) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 784 | 0 | 39.7 | 477.5 | 19.0 | 25.5 | 54.0-64.0 |
| -x | 5.66 | 781 | 0 | 39.7 | 464.2 | 19.5 | 26.6 | 53.2-63.1 |
| +y | 5.66 | 782 | 0 | 39.7 | 464.0 | 19.5 | 25.5 | 50.0-60.0 |
| -y | 5.66 | 773 | 0 | 39.5 | 461.4 | 19.4 | 25.5 | 70.3-80.3 |
| door +x+y (y wall) 0 | 1.20 | 590 | 1065 | 4.9 | 488.5 | 61.0 | 90.3 | 19.1-29.0 |
| door +x+y (y wall) 1 | 1.20 | 579 | 646 | 4.9 | 498.1 | 58.7 | 80.2 | 10.1-20.1 |
| door +x+y (y wall) 2 | 1.20 | 269 | 169 | 4.9 | 536.1 | 25.3 | 80.2 | 46.2-56.1 |
| door +x+y (x wall) 0 | 1.20 | 580 | 1071 | 4.9 | 495.5 | 59.1 | 85.3 | 27.8-37.8 |
| door +x+y (x wall) 1 | 1.20 | 586 | 650 | 4.9 | 507.2 | 58.3 | 90.3 | 15.9-25.9 |
| door +x+y (x wall) 2 | 1.20 | 298 | 170 | 4.9 | 532.1 | 28.3 | 80.2 | 4.7-14.7 |
| door +x+y (corner) | 1.20 | 78 | 0 | 74.7 | 535.2 | 8.5 | 70.2 | 374.8-384.8 |
| door -x+y (y wall) 0 | 1.20 | 583 | 1082 | 4.9 | 478.2 | 61.6 | 85.3 | 7.3-17.3 |
| door -x+y (y wall) 1 | 1.20 | 583 | 648 | 4.9 | 525.6 | 56.0 | 85.3 | 18.0-28.0 |
| door -x+y (y wall) 2 | 1.20 | 282 | 167 | 4.9 | 525.4 | 27.1 | 80.2 | 9.6-19.6 |
| door -x+y (x wall) 0 | 1.20 | 585 | 1051 | 4.9 | 496.6 | 59.5 | 90.3 | 16.3-26.2 |
| door -x+y (x wall) 1 | 1.20 | 581 | 643 | 4.9 | 502.2 | 58.4 | 85.3 | 12.4-22.4 |
| door -x+y (x wall) 2 | 1.20 | 290 | 166 | 4.9 | 524.4 | 27.9 | 80.2 | 4.7-14.7 |
| door -x+y (corner) | 1.20 | 75 | 0 | 66.8 | 491.8 | 8.8 | 70.2 | 444.8-454.8 |
| door -x-y (y wall) 0 | 1.20 | 578 | 1060 | 4.9 | 485.2 | 60.1 | 85.3 | 16.4-26.4 |
| door -x-y (y wall) 1 | 1.20 | 578 | 641 | 4.9 | 502.2 | 58.1 | 100.3 | 32.7-42.7 |
| door -x-y (y wall) 2 | 1.20 | 287 | 171 | 4.9 | 531.5 | 27.2 | 80.2 | 4.7-14.7 |
| door -x-y (x wall) 0 | 1.20 | 582 | 1063 | 4.9 | 483.8 | 60.7 | 85.3 | 12.2-22.2 |
| door -x-y (x wall) 1 | 1.20 | 567 | 650 | 4.9 | 498.7 | 57.4 | 85.3 | 14.7-24.7 |
| door -x-y (x wall) 2 | 1.20 | 270 | 170 | 4.9 | 525.9 | 25.9 | 85.3 | 10.5-20.5 |
| door -x-y (corner) | 1.20 | 112 | 0 | 72.4 | 532.1 | 12.2 | 75.2 | 259.7-269.7 |
| door +x-y (y wall) 0 | 1.20 | 582 | 1064 | 4.9 | 476.3 | 61.7 | 85.3 | 4.5-14.5 |
| door +x-y (y wall) 1 | 1.20 | 566 | 639 | 4.9 | 488.7 | 58.5 | 80.2 | 4.7-14.7 |
| door +x-y (y wall) 2 | 1.20 | 296 | 164 | 4.9 | 519.1 | 28.8 | 80.2 | 8.9-18.9 |
| door +x-y (x wall) 0 | 1.20 | 569 | 1071 | 4.9 | 473.6 | 60.7 | 85.3 | 12.9-22.9 |
| door +x-y (x wall) 1 | 1.20 | 570 | 648 | 4.9 | 492.0 | 58.5 | 80.2 | 9.6-19.6 |
| door +x-y (x wall) 2 | 1.20 | 270 | 171 | 4.9 | 521.2 | 26.1 | 85.3 | 9.1-19.1 |
| door +x-y (corner) | 1.20 | 134 | 0 | 35.9 | 514.8 | 14.0 | 70.2 | 308.4-318.3 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m; a corner door's: the gap between its wall ends, 1.20 m); agents are removed past the outer wall's outer face (51.11 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 784 | 5.2% | 18.5% |
| -x | avenue | 5.66 | 781 | 5.2% | 18.5% |
| +y | avenue | 5.66 | 782 | 5.2% | 18.5% |
| -y | avenue | 5.66 | 773 | 5.1% | 18.3% |
| door +x+y (y wall) 0 | door | 1.20 | 590 | 3.9% | 65.8% |
| door +x+y (y wall) 1 | door | 1.20 | 579 | 3.8% | 64.6% |
| door +x+y (y wall) 2 | door | 1.20 | 269 | 1.8% | 30.0% |
| door +x+y (x wall) 0 | door | 1.20 | 580 | 3.9% | 64.7% |
| door +x+y (x wall) 1 | door | 1.20 | 586 | 3.9% | 65.4% |
| door +x+y (x wall) 2 | door | 1.20 | 298 | 2.0% | 33.2% |
| door +x+y (corner) | door | 1.20 | 78 | 0.5% | 8.7% |
| door -x+y (y wall) 0 | door | 1.20 | 583 | 3.9% | 65.0% |
| door -x+y (y wall) 1 | door | 1.20 | 583 | 3.9% | 65.0% |
| door -x+y (y wall) 2 | door | 1.20 | 282 | 1.9% | 31.5% |
| door -x+y (x wall) 0 | door | 1.20 | 585 | 3.9% | 65.3% |
| door -x+y (x wall) 1 | door | 1.20 | 581 | 3.9% | 64.8% |
| door -x+y (x wall) 2 | door | 1.20 | 290 | 1.9% | 32.4% |
| door -x+y (corner) | door | 1.20 | 75 | 0.5% | 8.4% |
| door -x-y (y wall) 0 | door | 1.20 | 578 | 3.8% | 64.5% |
| door -x-y (y wall) 1 | door | 1.20 | 578 | 3.8% | 64.5% |
| door -x-y (y wall) 2 | door | 1.20 | 287 | 1.9% | 32.0% |
| door -x-y (x wall) 0 | door | 1.20 | 582 | 3.9% | 64.9% |
| door -x-y (x wall) 1 | door | 1.20 | 567 | 3.8% | 63.3% |
| door -x-y (x wall) 2 | door | 1.20 | 270 | 1.8% | 30.1% |
| door -x-y (corner) | door | 1.20 | 112 | 0.7% | 12.5% |
| door +x-y (y wall) 0 | door | 1.20 | 582 | 3.9% | 64.9% |
| door +x-y (y wall) 1 | door | 1.20 | 566 | 3.8% | 63.1% |
| door +x-y (y wall) 2 | door | 1.20 | 296 | 2.0% | 33.0% |
| door +x-y (x wall) 0 | door | 1.20 | 569 | 3.8% | 63.5% |
| door +x-y (x wall) 1 | door | 1.20 | 570 | 3.8% | 63.6% |
| door +x-y (x wall) 2 | door | 1.20 | 270 | 1.8% | 30.1% |
| door +x-y (corner) | door | 1.20 | 134 | 0.9% | 14.9% |
| **doors (28)** | door | 33.60 | 11920 | 79.3% | |
| **avenues (4)** | avenue | 22.64 | 3120 | 20.7% | |

**Unused exit width: 0.0 of 56.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 536.1 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 35.8%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 915 | 6.1% | 915 | 6.1% |
| straight +x+y (y wing) 1 | straight | yes | 582 | 3.9% | 579 | 3.8% |
| straight +x+y (y wing) 2 | straight | yes | 269 | 1.8% | 269 | 1.8% |
| straight +x+y (x wing) 0 | straight | yes | 909 | 6.0% | 909 | 6.0% |
| straight +x+y (x wing) 1 | straight | yes | 594 | 3.9% | 591 | 3.9% |
| straight +x+y (x wing) 2 | straight | yes | 293 | 1.9% | 293 | 1.9% |
| corner +x+y | corner | yes | 748 | 5.0% | 215 | 1.4% |
| straight -x+y (y wing) 0 | straight | yes | 911 | 6.1% | 911 | 6.1% |
| straight -x+y (y wing) 1 | straight | yes | 595 | 4.0% | 585 | 3.9% |
| straight -x+y (y wing) 2 | straight | yes | 279 | 1.9% | 279 | 1.9% |
| straight -x+y (x wing) 0 | straight | yes | 899 | 6.0% | 899 | 6.0% |
| straight -x+y (x wing) 1 | straight | yes | 589 | 3.9% | 585 | 3.9% |
| straight -x+y (x wing) 2 | straight | yes | 286 | 1.9% | 286 | 1.9% |
| corner -x+y | corner | yes | 749 | 5.0% | 212 | 1.4% |
| straight -x-y (y wing) 0 | straight | yes | 902 | 6.0% | 902 | 6.0% |
| straight -x-y (y wing) 1 | straight | yes | 583 | 3.9% | 578 | 3.8% |
| straight -x-y (y wing) 2 | straight | yes | 287 | 1.9% | 287 | 1.9% |
| straight -x-y (x wing) 0 | straight | yes | 910 | 6.1% | 910 | 6.1% |
| straight -x-y (x wing) 1 | straight | yes | 573 | 3.8% | 569 | 3.8% |
| straight -x-y (x wing) 2 | straight | yes | 268 | 1.8% | 268 | 1.8% |
| corner -x-y | corner | yes | 746 | 5.0% | 241 | 1.6% |
| straight +x-y (y wing) 0 | straight | yes | 899 | 6.0% | 899 | 6.0% |
| straight +x-y (y wing) 1 | straight | yes | 578 | 3.8% | 573 | 3.8% |
| straight +x-y (y wing) 2 | straight | yes | 289 | 1.9% | 289 | 1.9% |
| straight +x-y (x wing) 0 | straight | yes | 898 | 6.0% | 898 | 6.0% |
| straight +x-y (x wing) 1 | straight | yes | 581 | 3.9% | 570 | 3.8% |
| straight +x-y (x wing) 2 | straight | yes | 270 | 1.8% | 270 | 1.8% |
| corner +x-y | corner | yes | 771 | 5.1% | 258 | 1.7% |
| **straight (24)** | | | 14159 | | 14114 | 93.8% |
| **corner (4)** | | | 3014 | | 926 | 6.2% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 784 | 39.7 | 477.5 | 0.23 | 0.31 | 0.0% |
| -x | 781 | 39.7 | 464.2 | 0.23 | 0.32 | 0.0% |
| +y | 782 | 39.7 | 464.0 | 0.23 | 0.31 | 0.0% |
| -y | 773 | 39.5 | 461.4 | 0.23 | 0.31 | 0.0% |
| door +x+y (y wall) 0 | 590 | 4.9 | 488.5 | 0.73 | 1.08 | 36.7% |
| door +x+y (y wall) 1 | 579 | 4.9 | 498.1 | 0.70 | 0.96 | 24.0% |
| door +x+y (y wall) 2 | 269 | 4.9 | 536.1 | 0.30 | 0.96 | 5.6% |
| door +x+y (x wall) 0 | 580 | 4.9 | 495.5 | 0.71 | 1.02 | 26.0% |
| door +x+y (x wall) 1 | 586 | 4.9 | 507.2 | 0.70 | 1.08 | 25.5% |
| door +x+y (x wall) 2 | 298 | 4.9 | 532.1 | 0.34 | 0.96 | 5.6% |
| door +x+y (corner) | 78 | 74.7 | 535.2 | 0.10 | 0.84 | 0.0% |
| door -x+y (y wall) 0 | 583 | 4.9 | 478.2 | 0.74 | 1.02 | 37.5% |
| door -x+y (y wall) 1 | 583 | 4.9 | 525.6 | 0.67 | 1.02 | 28.3% |
| door -x+y (y wall) 2 | 282 | 4.9 | 525.4 | 0.32 | 0.96 | 3.8% |
| door -x+y (x wall) 0 | 585 | 4.9 | 496.6 | 0.71 | 1.08 | 28.0% |
| door -x+y (x wall) 1 | 581 | 4.9 | 502.2 | 0.70 | 1.02 | 29.4% |
| door -x+y (x wall) 2 | 290 | 4.9 | 524.4 | 0.33 | 0.96 | 7.5% |
| door -x+y (corner) | 75 | 66.8 | 491.8 | 0.11 | 0.84 | 0.0% |
| door -x-y (y wall) 0 | 578 | 4.9 | 485.2 | 0.72 | 1.02 | 30.6% |
| door -x-y (y wall) 1 | 578 | 4.9 | 502.2 | 0.69 | 1.20 | 27.5% |
| door -x-y (y wall) 2 | 287 | 4.9 | 531.5 | 0.33 | 0.96 | 3.7% |
| door -x-y (x wall) 0 | 582 | 4.9 | 483.8 | 0.73 | 1.02 | 34.7% |
| door -x-y (x wall) 1 | 567 | 4.9 | 498.7 | 0.69 | 1.02 | 21.6% |
| door -x-y (x wall) 2 | 270 | 4.9 | 525.9 | 0.31 | 1.02 | 3.8% |
| door -x-y (corner) | 112 | 72.4 | 532.1 | 0.15 | 0.90 | 4.3% |
| door +x-y (y wall) 0 | 582 | 4.9 | 476.3 | 0.74 | 1.02 | 39.6% |
| door +x-y (y wall) 1 | 566 | 4.9 | 488.7 | 0.70 | 0.96 | 30.0% |
| door +x-y (y wall) 2 | 296 | 4.9 | 519.1 | 0.34 | 0.96 | 3.8% |
| door +x-y (x wall) 0 | 569 | 4.9 | 473.6 | 0.73 | 1.02 | 31.2% |
| door +x-y (x wall) 1 | 570 | 4.9 | 492.0 | 0.70 | 0.96 | 32.0% |
| door +x-y (x wall) 2 | 270 | 4.9 | 521.2 | 0.31 | 1.02 | 5.7% |
| door +x-y (corner) | 134 | 35.9 | 514.8 | 0.17 | 0.84 | 0.0% |

Mean flow / w J averaged over the doors 0.52, over the avenues 0.23.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 46.9 | 915 | 590 / 325 / 186 | 0.7 | 485.5 | 2.27 | 3.41 | 90% | 78% | 12% | 3.71 |
| straight +x+y (y wing) 1 | 1.20 | 25.3 | 528 | 579 / 0 / 4 | 0.7 | 495.2 | 1.18 | 1.71 | 82% | 66% | 16% | 3.46 |
| straight +x+y (y wing) 2 | 1.20 | 4.8 | 63 | 269 / 0 / 0 | 0.7 | 533.1 | 0.51 | 1.40 | 9% | 9% | 0% | 2.81 |
| straight +x+y (x wing) 0 | 1.20 | 46.9 | 909 | 580 / 329 / 225 | 0.7 | 492.5 | 2.30 | 3.81 | 90% | 80% | 10% | 3.75 |
| straight +x+y (x wing) 1 | 1.20 | 25.3 | 548 | 591 / 0 / 5 | 0.7 | 504.3 | 1.18 | 1.81 | 78% | 65% | 14% | 3.51 |
| straight +x+y (x wing) 2 | 1.20 | 4.8 | 67 | 293 / 0 / 0 | 0.7 | 529.1 | 0.55 | 1.60 | 11% | 7% | 4% | 2.56 |
| corner +x+y | 1.20 | 85.6 | 741 | 78 / 137 / 535 | 0.7 | 531.4 | 1.41 | 3.91 | 85% | 57% | 28% | 2.39 |
| straight -x+y (y wing) 0 | 1.20 | 46.9 | 911 | 583 / 328 / 224 | 0.7 | 475.2 | 2.39 | 3.81 | 90% | 77% | 12% | 3.81 |
| straight -x+y (y wing) 1 | 1.20 | 25.3 | 547 | 585 / 0 / 13 | 0.7 | 522.6 | 1.15 | 1.81 | 77% | 64% | 13% | 3.40 |
| straight -x+y (y wing) 2 | 1.20 | 4.8 | 62 | 279 / 0 / 0 | 0.7 | 522.4 | 0.53 | 1.50 | 9% | 9% | 0% | 2.61 |
| straight -x+y (x wing) 0 | 1.20 | 46.9 | 899 | 585 / 314 / 204 | 0.7 | 493.6 | 2.24 | 3.91 | 90% | 76% | 14% | 3.67 |
| straight -x+y (x wing) 1 | 1.20 | 25.3 | 535 | 585 / 0 / 4 | 0.7 | 499.2 | 1.18 | 1.91 | 76% | 65% | 12% | 3.60 |
| straight -x+y (x wing) 2 | 1.20 | 4.8 | 66 | 286 / 0 / 0 | 0.7 | 521.4 | 0.55 | 1.50 | 11% | 11% | 0% | 2.71 |
| corner -x+y | 1.20 | 85.6 | 737 | 76 / 136 / 542 | 0.7 | 516.5 | 1.46 | 3.61 | 88% | 60% | 29% | 2.42 |
| straight -x-y (y wing) 0 | 1.20 | 46.9 | 902 | 578 / 324 / 216 | 0.7 | 482.2 | 2.32 | 3.81 | 90% | 78% | 12% | 3.78 |
| straight -x-y (y wing) 1 | 1.20 | 25.3 | 533 | 578 / 0 / 12 | 0.7 | 499.2 | 1.18 | 1.91 | 75% | 59% | 16% | 3.51 |
| straight -x-y (y wing) 2 | 1.20 | 4.8 | 66 | 287 / 0 / 0 | 0.7 | 528.6 | 0.54 | 1.50 | 11% | 9% | 2% | 2.64 |
| straight -x-y (x wing) 0 | 1.20 | 46.9 | 910 | 582 / 328 / 217 | 0.7 | 480.8 | 2.35 | 3.51 | 90% | 78% | 12% | 3.82 |
| straight -x-y (x wing) 1 | 1.20 | 25.3 | 540 | 569 / 0 / 5 | 0.7 | 495.7 | 1.16 | 1.71 | 82% | 68% | 14% | 3.41 |
| straight -x-y (x wing) 2 | 1.20 | 4.8 | 67 | 268 / 0 / 0 | 0.7 | 523.0 | 0.51 | 1.60 | 11% | 9% | 2% | 2.74 |
| corner -x-y | 1.20 | 85.6 | 737 | 112 / 129 / 513 | 0.7 | 528.2 | 1.43 | 3.31 | 85% | 49% | 36% | 2.34 |
| straight +x-y (y wing) 0 | 1.20 | 46.9 | 899 | 582 / 317 / 207 | 0.7 | 473.3 | 2.34 | 3.81 | 90% | 79% | 10% | 3.80 |
| straight +x-y (y wing) 1 | 1.20 | 25.3 | 534 | 573 / 0 / 8 | 0.7 | 485.7 | 1.20 | 1.71 | 82% | 67% | 14% | 3.47 |
| straight +x-y (y wing) 2 | 1.20 | 4.8 | 63 | 289 / 0 / 0 | 0.7 | 516.1 | 0.56 | 1.50 | 12% | 10% | 2% | 2.61 |
| straight +x-y (x wing) 0 | 1.20 | 46.9 | 898 | 569 / 329 / 217 | 0.7 | 470.7 | 2.37 | 3.51 | 81% | 79% | 2% | 4.06 |
| straight +x-y (x wing) 1 | 1.20 | 25.3 | 543 | 570 / 0 / 11 | 0.7 | 489.0 | 1.19 | 1.71 | 82% | 66% | 16% | 3.36 |
| straight +x-y (x wing) 2 | 1.20 | 4.8 | 64 | 270 / 0 / 0 | 0.7 | 518.2 | 0.52 | 1.40 | 12% | 10% | 2% | 2.65 |
| corner +x-y | 1.20 | 85.6 | 756 | 134 / 124 / 517 | 0.7 | 512.1 | 1.51 | 3.61 | 85% | 52% | 33% | 2.36 |

The last agent out (agent 434, t100 536.1 s): last gangway straight +x+y (y wing) 2, exit door +x+y (y wall) 2. The gangway that cleared last: straight +x+y (y wing) 2 at 533.1 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 3548 | 3276.2 | 6.80 | 531.9 / 517.5 / 488.7 | 516.3 / 478.0 / 434.5 | 647344.3 | 1512779 | 0.218 |
| gangway | 1212 | 1112.9 | 6.80 | 526.6 / 508.1 / 443.6 | 516.3 / 478.0 / 434.5 | 646509.7 | 1367571 | 0.110 |
| walkway | 276 | 257.4 | 3.17 | 187.2 / 122.4 / 0.0 | 123.7 / 31.5 / 0.0 | 0.0 | 24016 | 0.909 |
| avenue | 912 | 858.9 | 1.92 | 196.4 / 0.0 / 0.0 | 162.7 / 0.0 / 0.0 | 0.0 | 89569 | 1.327 |
| exit | 32 | 3.2 | 0.00 | 509.0 / 505.5 / 451.8 | 248.5 / 220.2 / 131.7 | 834.6 | 1576 | 1.324 |
| concourse | 1116 | 1043.8 | 2.19 | 471.5 / 0.2 / 0.0 | 119.6 / 0.2 / 0.0 | 0.0 | 30047 | 1.195 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 6488 | 4061.4 | 7.64 | 465.1 / 455.8 / 449.5 | 461.1 / 455.8 / 445.7 | 645471.7 | 1843398 | 0.046 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 128 x 128 from (-64, -64) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -26.5 | -28.5 | gangway | 1.00 | 6.12 | 436.4 | 414.7 | 378.0 | 2192.9 | 0.021 |
| 2 | 27.5 | 27.5 | gangway | 1.00 | 5.85 | 461.4 | 458.1 | 398.3 | 2174.5 | 0.015 |
| 3 | 28.5 | 26.5 | gangway | 1.00 | 5.69 | 466.8 | 448.1 | 387.6 | 2151.0 | 0.020 |
| 4 | -28.5 | 27.5 | gangway | 1.00 | 6.20 | 438.3 | 426.6 | 361.0 | 2140.9 | 0.018 |
| 5 | -26.5 | 28.5 | gangway | 1.00 | 6.09 | 452.7 | 446.0 | 359.3 | 2122.5 | 0.023 |
| 6 | -26.5 | 26.5 | gangway | 1.00 | 5.72 | 464.6 | 455.8 | 397.2 | 2119.1 | 0.020 |
| 7 | 29.5 | 26.5 | gangway | 1.00 | 6.19 | 461.8 | 431.5 | 352.8 | 2100.6 | 0.023 |
| 8 | -27.5 | 27.5 | gangway | 1.00 | 5.88 | 475.0 | 454.6 | 364.2 | 2084.5 | 0.015 |
| 9 | -26.5 | 27.5 | gangway | 1.00 | 5.86 | 469.6 | 449.2 | 363.8 | 2065.4 | 0.018 |
| 10 | 27.5 | 26.5 | gangway | 1.00 | 6.00 | 464.2 | 450.0 | 386.4 | 2061.0 | 0.019 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 26.5 | 24.5 | seat row | 0.50 | 7.28 | 457.7 | 455.8 | 445.7 | 1529.9 | 0.014 |
| 2 | -26.5 | 24.5 | seat row | 0.50 | 7.21 | 445.1 | 444.3 | 430.8 | 1492.1 | 0.013 |
| 3 | -24.5 | -26.5 | seat row | 0.50 | 7.31 | 446.5 | 440.4 | 429.7 | 1491.5 | 0.014 |
| 4 | -24.5 | 26.5 | seat row | 0.50 | 7.27 | 444.1 | 432.9 | 424.8 | 1486.2 | 0.012 |
| 5 | -26.5 | 23.5 | seat row | 0.50 | 6.94 | 445.8 | 445.3 | 436.9 | 1468.1 | 0.016 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 1700; agent-steps of seated agents on another row's clearway: 21160.

## Deposit check

Person-seconds deposited: 3359116.7, of them in excluded cells: 2939.256.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 308674 overlapping pair-steps: p99 0.0029, max 0.0476 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0029 max 0.0476; venue-geometry 7: p99 0.0005 max 0.0005 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00759 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 15 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.26 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 587 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
