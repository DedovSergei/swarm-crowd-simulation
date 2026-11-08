# Experiment `S_load150_s5`

**Task 5.11 stage 1 (gridlock robustness, default model, AMD 26.10.1): venue S, 150% load (seed 5)**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 5592 agents (load 150.0%, requested 150%): every one of the 3728 seats and 1864 standing (spawnOvercrowdedCrowd, seed 5; below), buffer N = 8192, 1663 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 230620 evaluations, 4608 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.50)** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `15aa31e8667e4a9417fde7884d907d1832c5e2d6`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-23T17:39:10, 14.5 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Spawn (overcrowding)

| | |
|---|---|
| seated | 3728 (every seat) |
| standing | **1864** (requested round((1.50 - 1) x 3728) = 1864; at most 2143 = floor(2.5 p/m^2 x 857.4 m^2)) |
| standing floor | walkway + rear concourse, 857.4 m^2 |
| standing on the walkway / concourse / gangways | 542 / 1322 / 0 |
| **load** | **150.00%** of the seats (requested 150%) |
| standing crowd's mean density | 2.174 p/m^2 |
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 3.70, all circulation cells 3.70 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 5, 24802 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 679 | 118.8 |
| t90 | 1334 | 233.3 |
| t100 | 1663 | 290.9 |

t_p: the step by which ceil(p x 5592) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 541 | 76 | 13.5 | 277.9 | 21.7 | 53.2 | 13.1-23.1 |
| -x | 5.66 | 535 | 73 | 13.5 | 274.6 | 21.7 | 51.0 | 12.9-22.9 |
| +y | 5.66 | 560 | 72 | 13.6 | 276.9 | 22.5 | 54.2 | 12.9-22.9 |
| -y | 5.66 | 526 | 81 | 13.5 | 269.5 | 21.8 | 59.5 | 13.1-23.1 |
| door +x+y y | 1.20 | 434 | 664 | 0.9 | 270.8 | 80.4 | 130.4 | 149.7-159.7 |
| door +x+y x | 1.20 | 426 | 661 | 1.4 | 289.3 | 73.9 | 125.4 | 139.1-149.0 |
| door -x+y y | 1.20 | 425 | 652 | 1.0 | 272.7 | 78.2 | 115.3 | 147.4-157.4 |
| door -x+y x | 1.20 | 425 | 658 | 1.0 | 285.8 | 74.6 | 115.3 | 143.2-153.2 |
| door -x-y y | 1.20 | 429 | 667 | 0.9 | 290.9 | 73.9 | 115.3 | 140.5-150.4 |
| door -x-y x | 1.20 | 425 | 650 | 1.6 | 267.6 | 79.8 | 120.4 | 132.1-142.0 |
| door +x-y y | 1.20 | 427 | 669 | 0.9 | 290.2 | 73.8 | 120.4 | 147.6-157.6 |
| door +x-y x | 1.20 | 439 | 669 | 0.7 | 269.4 | 81.6 | 120.4 | 140.5-150.4 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 541 | 9.7% | 23.6% |
| -x | avenue | 5.66 | 535 | 9.6% | 23.3% |
| +y | avenue | 5.66 | 560 | 10.0% | 24.4% |
| -y | avenue | 5.66 | 526 | 9.4% | 22.9% |
| door +x+y y | door | 1.20 | 434 | 7.8% | 89.2% |
| door +x+y x | door | 1.20 | 426 | 7.6% | 87.6% |
| door -x+y y | door | 1.20 | 425 | 7.6% | 87.4% |
| door -x+y x | door | 1.20 | 425 | 7.6% | 87.4% |
| door -x-y y | door | 1.20 | 429 | 7.7% | 88.2% |
| door -x-y x | door | 1.20 | 425 | 7.6% | 87.4% |
| door +x-y y | door | 1.20 | 427 | 7.6% | 87.8% |
| door +x-y x | door | 1.20 | 439 | 7.9% | 90.3% |
| **doors (8)** | door | 9.60 | 3430 | 61.3% | |
| **avenues (4)** | avenue | 22.64 | 2162 | 38.7% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 290.9 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 42.8%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 453 | 8.1% | 450 | 8.0% |
| straight +x+y (x wing) 0 | straight | yes | 454 | 8.1% | 454 | 8.1% |
| corner +x+y | corner | **no** | 44 | 0.8% | 44 | 0.8% |
| straight -x+y (y wing) 0 | straight | yes | 452 | 8.1% | 449 | 8.0% |
| straight -x+y (x wing) 0 | straight | yes | 457 | 8.2% | 457 | 8.2% |
| corner -x+y | corner | **no** | 46 | 0.8% | 46 | 0.8% |
| straight -x-y (y wing) 0 | straight | yes | 450 | 8.0% | 450 | 8.0% |
| straight -x-y (x wing) 0 | straight | yes | 451 | 8.1% | 445 | 8.0% |
| corner -x-y | corner | **no** | 56 | 1.0% | 56 | 1.0% |
| straight +x-y (y wing) 0 | straight | yes | 453 | 8.1% | 453 | 8.1% |
| straight +x-y (x wing) 0 | straight | yes | 452 | 8.1% | 448 | 8.0% |
| corner +x-y | corner | **no** | 58 | 1.0% | 58 | 1.0% |
| **straight (8)** | | | 3622 | | 3606 | 64.5% |
| **corner (4)** | | | 204 | | 204 | 3.6% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 1782, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 541 | 13.5 | 277.9 | 0.26 | 0.64 | 0.0% |
| -x | 535 | 13.5 | 274.6 | 0.26 | 0.61 | 0.0% |
| +y | 560 | 13.6 | 276.9 | 0.27 | 0.65 | 0.0% |
| -y | 526 | 13.5 | 269.5 | 0.26 | 0.71 | 0.0% |
| door +x+y y | 434 | 0.9 | 270.8 | 0.96 | 1.56 | 71.4% |
| door +x+y x | 426 | 1.4 | 289.3 | 0.88 | 1.50 | 53.3% |
| door -x+y y | 425 | 1.0 | 272.7 | 0.94 | 1.38 | 67.9% |
| door -x+y x | 425 | 1.0 | 285.8 | 0.89 | 1.38 | 72.4% |
| door -x-y y | 429 | 0.9 | 290.9 | 0.88 | 1.38 | 73.3% |
| door -x-y x | 425 | 1.6 | 267.6 | 0.95 | 1.44 | 66.7% |
| door +x-y y | 427 | 0.9 | 290.2 | 0.88 | 1.44 | 56.7% |
| door +x-y x | 439 | 0.7 | 269.4 | 0.98 | 1.44 | 71.4% |

Mean flow / w J averaged over the doors 0.92, over the avenues 0.26.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 453 | 272 / 182 / 45 | 0.3 | 267.8 | 1.86 | 3.11 | 93% | 89% | 4% | 4.07 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 451 | 263 / 191 / 52 | 0.3 | 286.3 | 1.77 | 3.01 | 79% | 79% | 0% | 4.10 |
| corner +x+y | 1.20 | 31.2 | 44 | 0 / 44 / 0 | 4.5 | 84.8 | 0.55 | 0.80 | 11% | 0% | 11% | 0.62 |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 452 | 274 / 178 / 49 | 0.7 | 269.7 | 1.86 | 3.01 | 86% | 86% | 0% | 4.18 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 454 | 268 / 189 / 55 | 0.5 | 282.8 | 1.81 | 3.31 | 79% | 79% | 0% | 4.03 |
| corner -x+y | 1.20 | 31.2 | 46 | 0 / 46 / 0 | 4.5 | 90.4 | 0.53 | 0.80 | 10% | 0% | 10% | 0.58 |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 444 | 263 / 187 / 50 | 0.7 | 287.9 | 1.74 | 3.01 | 79% | 79% | 0% | 4.05 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 451 | 275 / 176 / 32 | 0.2 | 264.6 | 1.83 | 2.71 | 89% | 89% | 0% | 4.17 |
| corner -x-y | 1.20 | 31.2 | 56 | 0 / 56 / 0 | 4.5 | 93.9 | 0.63 | 0.80 | 10% | 0% | 10% | 0.71 |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 449 | 264 / 189 / 47 | 0.7 | 287.2 | 1.74 | 3.21 | 79% | 79% | 0% | 4.06 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 452 | 276 / 177 / 31 | 0.3 | 266.4 | 1.82 | 2.91 | 89% | 89% | 0% | 4.26 |
| corner +x-y | 1.20 | 31.2 | 58 | 1 / 58 / 0 | 4.4 | 101.8 | 0.60 | 0.80 | 18% | 0% | 18% | 1.15 |

The last agent out (agent 2471, t100 290.9 s): last gangway straight -x-y (y wing) 0, exit door -x-y (y wall). The gangway that cleared last: straight -x-y (y wing) 0 at 287.9 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.57 | 283.0 / 274.4 / 235.1 | 257.3 / 252.6 / 191.2 | 95913.3 | 353063 | 0.253 |
| gangway | 392 | 351.5 | 6.57 | 266.4 / 255.4 / 206.7 | 257.3 / 252.6 / 191.2 | 74038.0 | 199488 | 0.097 |
| walkway | 276 | 257.4 | 5.11 | 160.7 / 125.2 / 3.8 | 142.5 / 119.1 / 3.0 | 20.3 | 27620 | 0.500 |
| avenue | 408 | 384.3 | 2.54 | 178.4 / 4.4 / 0.0 | 145.0 / 2.4 / 0.0 | 0.0 | 28182 | 1.310 |
| exit | 40 | 9.7 | 0.00 | 283.0 / 273.6 / 206.6 | 218.6 / 193.4 / 75.2 | 909.9 | 3310 | 0.908 |
| concourse | 612 | 609.0 | 6.06 | 240.7 / 156.7 / 111.4 | 168.6 / 155.7 / 97.4 | 20945.0 | 94464 | 0.171 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.59 | 249.9 / 246.3 / 229.0 | 249.9 / 246.1 / 226.3 | 115775.7 | 336716 | 0.047 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 18.5 | -10.5 | gangway | 0.94 | 5.96 | 243.5 | 238.4 | 191.2 | 988.4 | 0.032 |
| 2 | -11.5 | 19.5 | gangway | 0.92 | 6.11 | 227.7 | 223.4 | 177.9 | 915.6 | 0.023 |
| 3 | 10.5 | 19.5 | gangway | 0.96 | 5.87 | 254.0 | 243.8 | 175.4 | 900.9 | 0.025 |
| 4 | -18.5 | -10.5 | gangway | 0.94 | 5.82 | 244.9 | 239.4 | 175.6 | 891.3 | 0.033 |
| 5 | 10.5 | 18.5 | gangway | 0.94 | 5.91 | 237.7 | 234.4 | 167.4 | 855.5 | 0.033 |
| 6 | 11.5 | 19.5 | gangway | 0.92 | 5.95 | 229.8 | 223.7 | 169.3 | 843.6 | 0.023 |
| 7 | -10.5 | 18.5 | gangway | 0.94 | 5.99 | 243.5 | 238.9 | 156.4 | 828.3 | 0.034 |
| 8 | -18.5 | -11.5 | gangway | 0.86 | 6.21 | 239.3 | 224.1 | 167.2 | 818.8 | 0.034 |
| 9 | 19.5 | -11.5 | gangway | 0.92 | 5.84 | 236.3 | 230.9 | 163.2 | 813.2 | 0.023 |
| 10 | 18.5 | -11.5 | gangway | 0.86 | 6.26 | 236.3 | 232.8 | 163.9 | 802.8 | 0.034 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 18.5 | -9.5 | seat row | 0.50 | 7.39 | 238.6 | 235.1 | 225.5 | 796.2 | 0.023 |
| 2 | -9.5 | 18.5 | seat row | 0.50 | 7.40 | 238.9 | 236.6 | 226.3 | 792.0 | 0.023 |
| 3 | -18.5 | -9.5 | seat row | 0.50 | 7.43 | 237.2 | 234.2 | 221.1 | 776.9 | 0.023 |
| 4 | 9.5 | 18.5 | seat row | 0.50 | 7.36 | 244.3 | 228.1 | 217.6 | 758.0 | 0.023 |
| 5 | 18.5 | -8.5 | seat row | 0.50 | 7.13 | 229.1 | 224.9 | 211.1 | 715.6 | 0.020 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 361; agent-steps of seated agents on another row's clearway: 2331.

## Deposit check

Person-seconds deposited: 693593.9, of them in excluded cells: 3814.042.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 23595 overlapping pair-steps: p99 0.0030, max 0.0059 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0030 max 0.0059; venue-geometry 1: p99 0.0002 max 0.0002 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 7 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.06 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 88 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
