# Experiment `S_load150_s2`

**Task 5.9 stage 4: venue S, 150% requested (seed 2): every seat + standing on the walkway and concourse (M, L: the achievable maximum, also the 125% request)**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 5592 agents (load 150.0%, requested 150%): every one of the 3728 seats and 1864 standing (spawnOvercrowdedCrowd, seed 2; below), buffer N = 8192, 1662 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 232087 evaluations, 4626 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.50)** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-20T23:10:37, 15.4 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Spawn (overcrowding)

| | |
|---|---|
| seated | 3728 (every seat) |
| standing | **1864** (requested round((1.50 - 1) x 3728) = 1864; at most 2143 = floor(2.5 p/m^2 x 857.4 m^2)) |
| standing floor | walkway + rear concourse, 857.4 m^2 |
| standing on the walkway / concourse / gangways | 538 / 1326 / 0 |
| **load** | **150.00%** of the seats (requested 150%) |
| standing crowd's mean density | 2.174 p/m^2 |
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 3.84, all circulation cells 3.84 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 2, 24464 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 688 | 120.3 |
| t90 | 1340 | 234.4 |
| t100 | 1662 | 290.7 |

t_p: the step by which ceil(p x 5592) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 540 | 75 | 13.5 | 282.1 | 21.3 | 53.2 | 13.1-23.1 |
| -x | 5.66 | 532 | 73 | 13.5 | 274.1 | 21.6 | 52.1 | 13.1-23.1 |
| +y | 5.66 | 560 | 69 | 13.5 | 275.5 | 22.6 | 55.3 | 13.3-23.3 |
| -y | 5.66 | 519 | 78 | 13.6 | 270.6 | 21.4 | 57.4 | 13.3-23.3 |
| door +x+y y | 1.20 | 431 | 656 | 0.9 | 277.6 | 77.8 | 120.4 | 146.0-156.0 |
| door +x+y x | 1.20 | 425 | 663 | 1.2 | 288.1 | 74.0 | 125.4 | 150.6-160.6 |
| door -x+y y | 1.20 | 438 | 658 | 1.0 | 273.7 | 80.3 | 125.4 | 139.8-149.7 |
| door -x+y x | 1.20 | 427 | 674 | 0.9 | 285.1 | 75.1 | 125.4 | 152.9-162.8 |
| door -x-y y | 1.20 | 422 | 658 | 0.9 | 287.9 | 73.5 | 115.3 | 146.4-156.4 |
| door -x-y x | 1.20 | 434 | 655 | 0.9 | 282.5 | 77.0 | 120.4 | 137.1-147.1 |
| door +x-y y | 1.20 | 428 | 669 | 1.0 | 290.7 | 73.8 | 120.4 | 148.7-158.6 |
| door +x-y x | 1.20 | 436 | 664 | 1.2 | 287.5 | 76.1 | 120.4 | 135.9-145.9 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 540 | 9.7% | 23.6% |
| -x | avenue | 5.66 | 532 | 9.5% | 23.2% |
| +y | avenue | 5.66 | 560 | 10.0% | 24.4% |
| -y | avenue | 5.66 | 519 | 9.3% | 22.6% |
| door +x+y y | door | 1.20 | 431 | 7.7% | 88.7% |
| door +x+y x | door | 1.20 | 425 | 7.6% | 87.4% |
| door -x+y y | door | 1.20 | 438 | 7.8% | 90.1% |
| door -x+y x | door | 1.20 | 427 | 7.6% | 87.9% |
| door -x-y y | door | 1.20 | 422 | 7.5% | 86.8% |
| door -x-y x | door | 1.20 | 434 | 7.8% | 89.3% |
| door +x-y y | door | 1.20 | 428 | 7.7% | 88.1% |
| door +x-y x | door | 1.20 | 436 | 7.8% | 89.7% |
| **doors (8)** | door | 9.60 | 3441 | 61.5% | |
| **avenues (4)** | avenue | 22.64 | 2151 | 38.5% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 290.7 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 42.8%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 453 | 8.1% | 450 | 8.0% |
| straight +x+y (x wing) 0 | straight | yes | 450 | 8.0% | 450 | 8.0% |
| corner +x+y | corner | **no** | 49 | 0.9% | 49 | 0.9% |
| straight -x+y (y wing) 0 | straight | yes | 453 | 8.1% | 451 | 8.1% |
| straight -x+y (x wing) 0 | straight | yes | 449 | 8.0% | 449 | 8.0% |
| corner -x+y | corner | **no** | 56 | 1.0% | 56 | 1.0% |
| straight -x-y (y wing) 0 | straight | yes | 454 | 8.1% | 454 | 8.1% |
| straight -x-y (x wing) 0 | straight | yes | 451 | 8.1% | 447 | 8.0% |
| corner -x-y | corner | **no** | 52 | 0.9% | 52 | 0.9% |
| straight +x-y (y wing) 0 | straight | yes | 453 | 8.1% | 453 | 8.1% |
| straight +x-y (x wing) 0 | straight | yes | 452 | 8.1% | 451 | 8.1% |
| corner +x-y | corner | **no** | 53 | 0.9% | 53 | 0.9% |
| **straight (8)** | | | 3615 | | 3605 | 64.5% |
| **corner (4)** | | | 210 | | 210 | 3.8% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 1777, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 540 | 13.5 | 282.1 | 0.25 | 0.64 | 0.0% |
| -x | 532 | 13.5 | 274.1 | 0.26 | 0.62 | 0.0% |
| +y | 560 | 13.5 | 275.5 | 0.27 | 0.66 | 0.0% |
| -y | 519 | 13.6 | 270.6 | 0.26 | 0.69 | 0.0% |
| door +x+y y | 431 | 0.9 | 277.6 | 0.93 | 1.44 | 71.4% |
| door +x+y x | 425 | 1.2 | 288.1 | 0.89 | 1.50 | 72.4% |
| door -x+y y | 438 | 1.0 | 273.7 | 0.96 | 1.50 | 67.9% |
| door -x+y x | 427 | 0.9 | 285.1 | 0.90 | 1.50 | 75.9% |
| door -x-y y | 422 | 0.9 | 287.9 | 0.88 | 1.38 | 69.0% |
| door -x-y x | 434 | 0.9 | 282.5 | 0.92 | 1.44 | 75.9% |
| door +x-y y | 428 | 1.0 | 290.7 | 0.88 | 1.44 | 70.0% |
| door +x-y x | 436 | 1.2 | 287.5 | 0.91 | 1.44 | 65.5% |

Mean flow / w J averaged over the doors 0.91, over the avenues 0.26.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 453 | 274 / 179 / 42 | 0.2 | 274.6 | 1.80 | 2.81 | 86% | 86% | 0% | 4.14 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 447 | 261 / 189 / 53 | 0.3 | 285.1 | 1.77 | 2.91 | 83% | 79% | 3% | 3.98 |
| corner +x+y | 1.20 | 31.2 | 49 | 0 / 49 / 0 | 4.5 | 92.7 | 0.55 | 0.80 | 10% | 0% | 10% | 0.66 |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 453 | 281 / 172 / 29 | 0.5 | 270.8 | 1.78 | 2.81 | 86% | 86% | 0% | 4.18 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 447 | 259 / 190 / 58 | 0.3 | 282.1 | 1.80 | 3.21 | 79% | 79% | 0% | 3.99 |
| corner -x+y | 1.20 | 31.2 | 56 | 0 / 56 / 0 | 4.4 | 99.5 | 0.59 | 0.90 | 20% | 0% | 20% | 1.16 |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 450 | 266 / 188 / 42 | 0.7 | 284.9 | 1.74 | 2.81 | 79% | 79% | 0% | 4.03 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 451 | 282 / 169 / 30 | 0.5 | 279.5 | 1.72 | 2.81 | 83% | 83% | 0% | 4.16 |
| corner -x-y | 1.20 | 31.2 | 52 | 0 / 52 / 0 | 4.2 | 90.8 | 0.60 | 0.90 | 20% | 0% | 20% | 1.11 |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 452 | 264 / 189 / 49 | 0.2 | 287.7 | 1.74 | 3.41 | 79% | 79% | 0% | 4.06 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 452 | 277 / 175 / 31 | 0.3 | 284.6 | 1.70 | 2.81 | 86% | 83% | 3% | 4.14 |
| corner +x-y | 1.20 | 31.2 | 53 | 0 / 53 / 0 | 3.8 | 101.4 | 0.54 | 0.80 | 18% | 0% | 18% | 1.11 |

The last agent out (agent 3461, t100 290.7 s): last gangway straight +x-y (y wing) 0, exit door +x-y (y wall). The gangway that cleared last: straight +x-y (y wing) 0 at 287.7 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.38 | 282.6 / 276.2 / 238.0 | 260.8 / 252.9 / 190.5 | 97012.5 | 354852 | 0.252 |
| gangway | 392 | 351.5 | 6.38 | 270.1 / 259.0 / 212.3 | 260.8 / 252.9 / 190.5 | 74243.1 | 199931 | 0.097 |
| walkway | 276 | 257.4 | 5.16 | 167.2 / 130.8 / 3.7 | 153.0 / 126.6 / 1.2 | 18.6 | 28098 | 0.490 |
| avenue | 408 | 384.3 | 2.49 | 181.4 / 3.7 / 0.0 | 151.3 / 1.2 / 0.0 | 0.0 | 28045 | 1.310 |
| exit | 40 | 9.7 | 0.00 | 282.6 / 275.3 / 207.3 | 216.7 / 193.3 / 73.3 | 904.6 | 3313 | 0.907 |
| concourse | 612 | 609.0 | 6.00 | 241.5 / 157.1 / 117.0 | 170.2 / 154.4 / 96.7 | 21846.2 | 95465 | 0.171 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.52 | 249.2 / 246.1 / 234.9 | 249.2 / 245.9 / 232.3 | 115631.9 | 339126 | 0.047 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -18.5 | -10.5 | gangway | 0.94 | 5.86 | 246.8 | 237.9 | 190.5 | 980.6 | 0.031 |
| 2 | 10.5 | 18.5 | gangway | 0.94 | 5.97 | 242.1 | 237.9 | 179.5 | 928.7 | 0.036 |
| 3 | -10.5 | 18.5 | gangway | 0.94 | 5.76 | 248.9 | 240.0 | 173.5 | 896.1 | 0.032 |
| 4 | -19.5 | -10.5 | gangway | 0.96 | 5.63 | 249.6 | 241.2 | 169.3 | 874.3 | 0.027 |
| 5 | -19.5 | -11.5 | gangway | 0.92 | 5.93 | 237.2 | 232.5 | 169.1 | 852.5 | 0.023 |
| 6 | -10.5 | 19.5 | gangway | 0.96 | 5.76 | 250.6 | 247.3 | 159.5 | 825.7 | 0.028 |
| 7 | 18.5 | -10.5 | gangway | 0.94 | 5.82 | 245.9 | 243.8 | 160.4 | 816.0 | 0.030 |
| 8 | 19.5 | -11.5 | gangway | 0.92 | 5.91 | 238.7 | 226.3 | 164.6 | 803.9 | 0.023 |
| 9 | -11.5 | 19.5 | gangway | 0.92 | 5.97 | 233.5 | 225.6 | 158.8 | 798.2 | 0.026 |
| 10 | -19.5 | 11.5 | gangway | 0.92 | 5.66 | 216.5 | 212.2 | 163.7 | 794.5 | 0.030 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -9.5 | 18.5 | seat row | 0.50 | 7.52 | 243.5 | 242.2 | 232.3 | 820.9 | 0.022 |
| 2 | -18.5 | -9.5 | seat row | 0.50 | 7.39 | 241.0 | 238.6 | 228.4 | 804.1 | 0.022 |
| 3 | 18.5 | -9.5 | seat row | 0.50 | 7.38 | 245.7 | 242.4 | 227.9 | 801.1 | 0.022 |
| 4 | 9.5 | 18.5 | seat row | 0.50 | 7.39 | 239.4 | 236.8 | 225.5 | 789.9 | 0.023 |
| 5 | -8.5 | 18.5 | seat row | 0.50 | 7.05 | 234.5 | 233.0 | 218.3 | 728.5 | 0.019 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 334; agent-steps of seated agents on another row's clearway: 2086.

## Deposit check

Person-seconds deposited: 697894.7, of them in excluded cells: 3916.691.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 25298 overlapping pair-steps: p99 0.0032, max 0.0064 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0032 max 0.0064; venue-geometry 1: p99 0.0008 max 0.0008 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 2 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.00 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 74 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
