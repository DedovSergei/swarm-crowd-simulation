# Experiment `S_load150_s2`

**Task 5.8 stage 2: venue S, 150% requested (seed 2): every seat + standing on the walkway and concourse (M, L: the achievable maximum, also the 125% request)**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 5592 agents (load 150.0%, requested 150%): every one of the 3728 seats and 1864 standing (spawnOvercrowdedCrowd, seed 2; below), buffer N = 8192, 1508 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 222969 evaluations, 4615 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.50)** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `cd8e0bbf3411846ca7aa6719887d122a142a7ca1`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-15T16:21:50, 85.4 s wall.

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
| t50 | 691 | 120.9 |
| t90 | 1212 | 212.0 |
| t100 | 1508 | 263.8 |

t_p: the step by which ceil(p x 5592) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 541 | 75 | 13.5 | 247.5 | 24.5 | 53.2 | 13.1-23.1 |
| -x | 5.66 | 536 | 73 | 13.5 | 240.0 | 25.1 | 52.1 | 13.1-23.1 |
| +y | 5.66 | 559 | 69 | 13.5 | 248.0 | 25.2 | 55.3 | 13.3-23.3 |
| -y | 5.66 | 541 | 78 | 13.6 | 242.9 | 25.0 | 57.4 | 13.3-23.3 |
| door +x+y y | 1.20 | 425 | 656 | 0.9 | 257.1 | 82.9 | 135.4 | 208.5-218.5 |
| door +x+y x | 1.20 | 419 | 663 | 1.2 | 263.8 | 79.7 | 135.4 | 178.1-188.0 |
| door -x+y y | 1.20 | 434 | 658 | 1.0 | 259.2 | 84.0 | 135.4 | 156.0-166.0 |
| door -x+y x | 1.20 | 426 | 674 | 0.9 | 262.0 | 81.5 | 135.4 | 173.0-183.0 |
| door -x-y y | 1.20 | 422 | 658 | 0.9 | 257.1 | 82.3 | 135.4 | 170.4-180.3 |
| door -x-y x | 1.20 | 429 | 655 | 0.9 | 256.8 | 83.8 | 130.4 | 157.8-167.7 |
| door +x-y y | 1.20 | 419 | 669 | 1.0 | 258.2 | 81.4 | 135.4 | 173.7-183.7 |
| door +x-y x | 1.20 | 441 | 664 | 1.2 | 248.0 | 89.3 | 130.4 | 157.4-167.4 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 541 | 9.7% | 26.0% |
| -x | avenue | 5.66 | 536 | 9.6% | 25.8% |
| +y | avenue | 5.66 | 559 | 10.0% | 26.9% |
| -y | avenue | 5.66 | 541 | 9.7% | 26.0% |
| door +x+y y | door | 1.20 | 425 | 7.6% | 96.4% |
| door +x+y x | door | 1.20 | 419 | 7.5% | 95.0% |
| door -x+y y | door | 1.20 | 434 | 7.8% | 98.4% |
| door -x+y x | door | 1.20 | 426 | 7.6% | 96.6% |
| door -x-y y | door | 1.20 | 422 | 7.5% | 95.7% |
| door -x-y x | door | 1.20 | 429 | 7.7% | 97.3% |
| door +x-y y | door | 1.20 | 419 | 7.5% | 95.0% |
| door +x-y x | door | 1.20 | 441 | 7.9% | 100.0% |
| **doors (8)** | door | 9.60 | 3415 | 61.1% | |
| **avenues (4)** | avenue | 22.64 | 2177 | 38.9% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 263.8 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 47.2%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 453 | 8.1% | 445 | 8.0% |
| straight +x+y (x wing) 0 | straight | yes | 456 | 8.2% | 456 | 8.2% |
| corner +x+y | corner | **no** | 50 | 0.9% | 50 | 0.9% |
| straight -x+y (y wing) 0 | straight | yes | 454 | 8.1% | 445 | 8.0% |
| straight -x+y (x wing) 0 | straight | yes | 457 | 8.2% | 457 | 8.2% |
| corner -x+y | corner | **no** | 56 | 1.0% | 56 | 1.0% |
| straight -x-y (y wing) 0 | straight | yes | 461 | 8.2% | 461 | 8.2% |
| straight -x-y (x wing) 0 | straight | yes | 453 | 8.1% | 442 | 7.9% |
| corner -x-y | corner | **no** | 52 | 0.9% | 52 | 0.9% |
| straight +x-y (y wing) 0 | straight | yes | 456 | 8.2% | 456 | 8.2% |
| straight +x-y (x wing) 0 | straight | yes | 451 | 8.1% | 447 | 8.0% |
| corner +x-y | corner | **no** | 54 | 1.0% | 54 | 1.0% |
| **straight (8)** | | | 3641 | | 3609 | 64.5% |
| **corner (4)** | | | 212 | | 212 | 3.8% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 1771, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 541 | 13.5 | 247.5 | 0.29 | 0.64 | 0.0% |
| -x | 536 | 13.5 | 240.0 | 0.30 | 0.62 | 0.0% |
| +y | 559 | 13.5 | 248.0 | 0.30 | 0.66 | 0.0% |
| -y | 541 | 13.6 | 242.9 | 0.30 | 0.69 | 0.0% |
| door +x+y y | 425 | 0.9 | 257.1 | 0.99 | 1.62 | 88.5% |
| door +x+y x | 419 | 1.2 | 263.8 | 0.95 | 1.62 | 81.5% |
| door -x+y y | 434 | 1.0 | 259.2 | 1.00 | 1.62 | 88.5% |
| door -x+y x | 426 | 0.9 | 262.0 | 0.98 | 1.62 | 81.5% |
| door -x-y y | 422 | 0.9 | 257.1 | 0.98 | 1.62 | 80.8% |
| door -x-y x | 429 | 0.9 | 256.8 | 1.00 | 1.56 | 84.6% |
| door +x-y y | 419 | 1.0 | 258.2 | 0.97 | 1.62 | 84.6% |
| door +x-y x | 441 | 1.2 | 248.0 | 1.07 | 1.56 | 88.0% |

Mean flow / w J averaged over the doors 0.99, over the avenues 0.30.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 453 | 268 / 185 / 32 | 0.2 | 254.1 | 1.91 | 3.51 | 85% | 85% | 0% | 4.60 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 448 | 256 / 200 / 56 | 0.3 | 260.8 | 1.96 | 4.01 | 74% | 74% | 0% | 4.58 |
| corner +x+y | 1.20 | 31.2 | 50 | 0 / 50 / 0 | 4.5 | 78.9 | 0.67 | 1.00 | 12% | 0% | 12% | 0.67 |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 454 | 277 / 177 / 31 | 0.5 | 256.2 | 1.90 | 3.51 | 85% | 85% | 0% | 4.47 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 448 | 258 / 200 / 54 | 0.3 | 259.0 | 1.98 | 3.51 | 77% | 77% | 0% | 4.49 |
| corner -x+y | 1.20 | 31.2 | 56 | 0 / 56 / 0 | 4.4 | 88.0 | 0.67 | 0.90 | 11% | 0% | 11% | 0.68 |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 450 | 266 / 195 / 46 | 0.7 | 254.1 | 2.00 | 3.81 | 77% | 77% | 0% | 4.45 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 453 | 277 / 178 / 33 | 0.5 | 253.8 | 1.93 | 3.51 | 81% | 81% | 0% | 4.55 |
| corner -x-y | 1.20 | 31.2 | 52 | 0 / 52 / 0 | 4.2 | 74.7 | 0.74 | 1.00 | 12% | 0% | 12% | 0.68 |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 452 | 255 / 201 / 50 | 0.2 | 255.2 | 1.98 | 3.81 | 77% | 77% | 0% | 4.50 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 451 | 283 / 169 / 25 | 0.3 | 245.0 | 1.95 | 3.61 | 84% | 84% | 0% | 4.59 |
| corner +x-y | 1.20 | 31.2 | 54 | 0 / 54 / 0 | 3.8 | 84.8 | 0.67 | 1.10 | 11% | 0% | 11% | 0.66 |

The last agent out (agent 117, t100 263.8 s): last gangway straight +x+y (x wing) 0, exit door +x+y (x wall). The gangway that cleared last: straight +x+y (x wing) 0 at 260.8 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.58 | 263.1 / 254.3 / 216.2 | 234.0 / 228.8 / 169.1 | 95347.5 | 366714 | 0.249 |
| gangway | 392 | 351.5 | 6.58 | 259.9 / 231.6 / 199.4 | 233.9 / 228.8 / 169.1 | 70548.1 | 193351 | 0.108 |
| walkway | 276 | 257.4 | 5.06 | 230.2 / 163.7 / 0.9 | 226.0 / 153.7 / 0.5 | 4.4 | 35018 | 0.401 |
| avenue | 408 | 384.3 | 2.49 | 234.2 / 3.5 / 0.0 | 213.6 / 1.2 / 0.0 | 0.0 | 28432 | 1.305 |
| exit | 40 | 9.7 | 0.00 | 261.0 / 254.0 / 207.4 | 234.0 / 219.3 / 84.8 | 1015.0 | 3475 | 0.851 |
| concourse | 612 | 609.0 | 6.04 | 230.4 / 213.2 / 136.6 | 221.8 / 204.3 / 109.8 | 23780.0 | 106437 | 0.154 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.66 | 219.5 / 218.6 / 213.2 | 219.3 / 218.6 / 210.6 | 104468.4 | 299874 | 0.054 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -18.5 | -10.5 | gangway | 0.94 | 5.96 | 215.8 | 208.3 | 169.1 | 868.7 | 0.043 |
| 2 | 10.5 | 18.5 | gangway | 0.94 | 5.84 | 221.1 | 215.0 | 168.6 | 856.2 | 0.045 |
| 3 | 18.5 | -10.5 | gangway | 0.94 | 5.82 | 221.8 | 208.8 | 168.1 | 843.8 | 0.047 |
| 4 | 17.5 | -10.5 | gangway | 0.95 | 5.69 | 220.0 | 214.6 | 161.6 | 815.1 | 0.049 |
| 5 | -10.5 | 18.5 | gangway | 0.94 | 5.72 | 218.8 | 211.3 | 159.9 | 805.2 | 0.046 |
| 6 | -10.5 | 17.5 | gangway | 0.95 | 5.80 | 221.8 | 217.9 | 152.5 | 773.6 | 0.050 |
| 7 | 20.5 | 10.5 | gangway | 0.96 | 5.79 | 212.2 | 207.1 | 145.7 | 768.6 | 0.048 |
| 8 | 19.5 | -10.5 | gangway | 0.96 | 5.78 | 222.3 | 211.5 | 146.7 | 757.2 | 0.046 |
| 9 | -17.5 | -10.5 | gangway | 0.95 | 5.61 | 218.3 | 213.4 | 146.6 | 733.1 | 0.048 |
| 10 | 21.5 | 11.5 | gangway | 0.89 | 6.26 | 210.6 | 201.0 | 145.5 | 716.7 | 0.047 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 9.5 | 18.5 | seat row | 0.50 | 7.50 | 219.3 | 218.6 | 210.6 | 747.6 | 0.024 |
| 2 | -18.5 | -9.5 | seat row | 0.50 | 7.47 | 214.1 | 213.0 | 207.1 | 734.6 | 0.025 |
| 3 | -9.5 | 18.5 | seat row | 0.50 | 7.51 | 216.7 | 215.8 | 209.5 | 729.8 | 0.025 |
| 4 | 18.5 | -9.5 | seat row | 0.50 | 7.51 | 211.5 | 209.2 | 203.8 | 720.7 | 0.025 |
| 5 | 9.5 | -18.5 | seat row | 0.50 | 7.66 | 204.8 | 203.4 | 195.9 | 689.1 | 0.027 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 327; agent-steps of seated agents on another row's clearway: 4291.

## Deposit check

Person-seconds deposited: 670747.5, of them in excluded cells: 4159.463.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 28517 overlapping pair-steps: p99 0.0057, max 0.0120 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0057 max 0.0120; venue-geometry 1: p99 0.0007 max 0.0007 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 8 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.04 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 126 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
