# Experiment `S_load150_s2`

**Task 5.11 stage 1 (gridlock robustness, default model, AMD 26.10.1): venue S, 150% load (seed 2)**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 5592 agents (load 150.0%, requested 150%): every one of the 3728 seats and 1864 standing (spawnOvercrowdedCrowd, seed 2; below), buffer N = 8192, 1696 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 231475 evaluations, 4625 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.50)** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `15aa31e8667e4a9417fde7884d907d1832c5e2d6`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-23T17:38:15, 14.6 s wall.

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
| t50 | 682 | 119.3 |
| t90 | 1338 | 234.0 |
| t100 | 1696 | 296.6 |

t_p: the step by which ceil(p x 5592) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 533 | 75 | 13.5 | 277.9 | 21.4 | 53.2 | 13.1-23.1 |
| -x | 5.66 | 538 | 73 | 13.5 | 276.4 | 21.7 | 52.1 | 13.1-23.1 |
| +y | 5.66 | 558 | 69 | 13.5 | 276.0 | 22.5 | 55.3 | 13.3-23.3 |
| -y | 5.66 | 527 | 78 | 13.6 | 271.3 | 21.7 | 57.4 | 13.3-23.3 |
| door +x+y y | 1.20 | 429 | 656 | 0.9 | 265.7 | 80.9 | 120.4 | 138.0-148.0 |
| door +x+y x | 1.20 | 430 | 663 | 1.2 | 291.2 | 74.1 | 130.4 | 143.9-153.9 |
| door -x+y y | 1.20 | 433 | 658 | 1.0 | 268.1 | 81.0 | 125.4 | 136.3-146.2 |
| door -x+y x | 1.20 | 431 | 674 | 0.9 | 294.2 | 73.4 | 130.4 | 166.9-176.8 |
| door -x-y y | 1.20 | 424 | 658 | 0.9 | 292.8 | 72.6 | 115.3 | 152.3-162.3 |
| door -x-y x | 1.20 | 427 | 655 | 0.9 | 265.9 | 80.5 | 120.4 | 134.9-144.8 |
| door +x-y y | 1.20 | 429 | 669 | 1.0 | 296.6 | 72.5 | 120.4 | 140.8-150.8 |
| door +x-y x | 1.20 | 433 | 664 | 1.2 | 276.4 | 78.6 | 115.3 | 146.0-156.0 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 533 | 9.5% | 22.8% |
| -x | avenue | 5.66 | 538 | 9.6% | 23.0% |
| +y | avenue | 5.66 | 558 | 10.0% | 23.9% |
| -y | avenue | 5.66 | 527 | 9.4% | 22.5% |
| door +x+y y | door | 1.20 | 429 | 7.7% | 86.5% |
| door +x+y x | door | 1.20 | 430 | 7.7% | 86.7% |
| door -x+y y | door | 1.20 | 433 | 7.7% | 87.3% |
| door -x+y x | door | 1.20 | 431 | 7.7% | 86.9% |
| door -x-y y | door | 1.20 | 424 | 7.6% | 85.5% |
| door -x-y x | door | 1.20 | 427 | 7.6% | 86.1% |
| door +x-y y | door | 1.20 | 429 | 7.7% | 86.5% |
| door +x-y x | door | 1.20 | 433 | 7.7% | 87.3% |
| **doors (8)** | door | 9.60 | 3436 | 61.4% | |
| **avenues (4)** | avenue | 22.64 | 2156 | 38.6% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 296.6 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 42.0%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 453 | 8.1% | 446 | 8.0% |
| straight +x+y (x wing) 0 | straight | yes | 454 | 8.1% | 454 | 8.1% |
| corner +x+y | corner | **no** | 49 | 0.9% | 49 | 0.9% |
| straight -x+y (y wing) 0 | straight | yes | 453 | 8.1% | 446 | 8.0% |
| straight -x+y (x wing) 0 | straight | yes | 454 | 8.1% | 454 | 8.1% |
| corner -x+y | corner | **no** | 56 | 1.0% | 56 | 1.0% |
| straight -x-y (y wing) 0 | straight | yes | 458 | 8.2% | 458 | 8.2% |
| straight -x-y (x wing) 0 | straight | yes | 451 | 8.1% | 443 | 7.9% |
| corner -x-y | corner | **no** | 52 | 0.9% | 52 | 0.9% |
| straight +x-y (y wing) 0 | straight | yes | 459 | 8.2% | 459 | 8.2% |
| straight +x-y (x wing) 0 | straight | yes | 451 | 8.1% | 444 | 7.9% |
| corner +x-y | corner | **no** | 54 | 1.0% | 54 | 1.0% |
| **straight (8)** | | | 3633 | | 3604 | 64.4% |
| **corner (4)** | | | 211 | | 211 | 3.8% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 1777, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 533 | 13.5 | 277.9 | 0.26 | 0.64 | 0.0% |
| -x | 538 | 13.5 | 276.4 | 0.26 | 0.62 | 0.0% |
| +y | 558 | 13.5 | 276.0 | 0.27 | 0.66 | 0.0% |
| -y | 527 | 13.6 | 271.3 | 0.26 | 0.69 | 0.0% |
| door +x+y y | 429 | 0.9 | 265.7 | 0.97 | 1.44 | 70.4% |
| door +x+y x | 430 | 1.2 | 291.2 | 0.89 | 1.56 | 66.7% |
| door -x+y y | 433 | 1.0 | 268.1 | 0.97 | 1.50 | 70.4% |
| door -x+y x | 431 | 0.9 | 294.2 | 0.88 | 1.56 | 63.3% |
| door -x-y y | 424 | 0.9 | 292.8 | 0.87 | 1.38 | 70.0% |
| door -x-y x | 427 | 0.9 | 265.9 | 0.96 | 1.44 | 70.4% |
| door +x-y y | 429 | 1.0 | 296.6 | 0.87 | 1.44 | 63.3% |
| door +x-y x | 433 | 1.2 | 276.4 | 0.94 | 1.38 | 67.9% |

Mean flow / w J averaged over the doors 0.92, over the avenues 0.26.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 453 | 272 / 181 / 44 | 0.2 | 262.7 | 1.89 | 2.81 | 89% | 89% | 0% | 4.18 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 447 | 266 / 188 / 58 | 0.3 | 288.2 | 1.78 | 3.11 | 79% | 76% | 3% | 4.06 |
| corner +x+y | 1.20 | 31.2 | 49 | 0 / 49 / 0 | 4.5 | 91.7 | 0.56 | 0.80 | 10% | 0% | 10% | 0.66 |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 453 | 276 / 177 / 41 | 0.5 | 265.2 | 1.87 | 2.91 | 93% | 89% | 4% | 4.08 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 447 | 263 / 191 / 50 | 0.3 | 291.2 | 1.73 | 2.91 | 77% | 77% | 0% | 4.06 |
| corner -x+y | 1.20 | 31.2 | 56 | 0 / 56 / 0 | 4.4 | 102.3 | 0.57 | 0.80 | 18% | 0% | 18% | 1.16 |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 450 | 268 / 190 / 54 | 0.7 | 289.8 | 1.77 | 3.11 | 77% | 73% | 3% | 3.96 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 451 | 275 / 176 / 44 | 0.5 | 262.9 | 1.89 | 3.01 | 89% | 89% | 0% | 4.12 |
| corner -x-y | 1.20 | 31.2 | 52 | 0 / 52 / 0 | 4.2 | 93.9 | 0.58 | 0.90 | 20% | 0% | 20% | 1.11 |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 452 | 265 / 194 / 66 | 0.2 | 293.7 | 1.79 | 3.21 | 77% | 77% | 0% | 4.06 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 451 | 275 / 177 / 30 | 0.3 | 273.4 | 1.76 | 2.81 | 89% | 86% | 4% | 4.16 |
| corner +x-y | 1.20 | 31.2 | 54 | 0 / 54 / 0 | 3.8 | 94.3 | 0.60 | 0.90 | 20% | 0% | 20% | 1.12 |

The last agent out (agent 3402, t100 296.6 s): last gangway straight +x-y (y wing) 0, exit door +x-y (y wall). The gangway that cleared last: straight +x-y (y wing) 0 at 293.7 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.50 | 288.8 / 277.6 / 234.7 | 261.8 / 252.7 / 183.3 | 95773.1 | 355480 | 0.252 |
| gangway | 392 | 351.5 | 6.50 | 276.2 / 260.1 / 206.0 | 261.8 / 252.7 / 183.3 | 72676.9 | 199782 | 0.098 |
| walkway | 276 | 257.4 | 5.04 | 160.4 / 123.3 / 1.9 | 144.6 / 119.6 / 0.9 | 9.7 | 27973 | 0.495 |
| avenue | 408 | 384.3 | 2.49 | 180.3 / 3.7 / 0.0 | 146.4 / 1.2 / 0.0 | 0.0 | 28111 | 1.310 |
| exit | 40 | 9.7 | 0.00 | 285.6 / 277.2 / 207.6 | 221.6 / 203.1 / 78.4 | 925.7 | 3336 | 0.902 |
| concourse | 612 | 609.0 | 5.99 | 243.6 / 172.1 / 113.3 | 182.4 / 172.1 / 96.7 | 22160.9 | 96277 | 0.170 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.53 | 249.1 / 246.6 / 237.2 | 249.1 / 246.4 / 234.5 | 117842.0 | 336760 | 0.047 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -10.5 | 18.5 | gangway | 0.94 | 5.79 | 244.9 | 241.5 | 183.3 | 926.1 | 0.031 |
| 2 | 19.5 | -10.5 | gangway | 0.96 | 5.76 | 252.9 | 242.1 | 174.6 | 912.1 | 0.022 |
| 3 | 19.5 | -11.5 | gangway | 0.92 | 5.83 | 238.2 | 233.5 | 176.3 | 897.6 | 0.021 |
| 4 | -11.5 | 19.5 | gangway | 0.92 | 5.89 | 245.6 | 236.5 | 178.6 | 892.8 | 0.024 |
| 5 | 18.5 | -10.5 | gangway | 0.94 | 5.81 | 248.7 | 243.1 | 166.2 | 844.4 | 0.033 |
| 6 | 11.5 | 18.5 | gangway | 0.86 | 6.21 | 233.7 | 221.4 | 169.0 | 826.8 | 0.033 |
| 7 | 10.5 | 18.5 | gangway | 0.94 | 5.77 | 241.4 | 238.2 | 161.4 | 820.9 | 0.034 |
| 8 | -10.5 | 19.5 | gangway | 0.96 | 5.62 | 251.5 | 247.7 | 159.2 | 820.1 | 0.026 |
| 9 | -11.5 | 18.5 | gangway | 0.86 | 6.24 | 240.8 | 234.5 | 163.2 | 811.5 | 0.031 |
| 10 | 17.5 | -10.5 | gangway | 0.95 | 5.67 | 253.4 | 244.7 | 160.9 | 804.5 | 0.048 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -9.5 | 18.5 | seat row | 0.50 | 7.50 | 244.5 | 242.4 | 234.5 | 827.0 | 0.022 |
| 2 | 18.5 | -9.5 | seat row | 0.50 | 7.40 | 244.2 | 237.0 | 228.1 | 801.3 | 0.022 |
| 3 | -18.5 | -9.5 | seat row | 0.50 | 7.44 | 241.7 | 237.5 | 227.4 | 798.9 | 0.022 |
| 4 | 9.5 | 18.5 | seat row | 0.50 | 7.36 | 235.6 | 231.1 | 218.5 | 766.0 | 0.023 |
| 5 | -8.5 | 18.5 | seat row | 0.50 | 7.12 | 238.6 | 236.5 | 219.0 | 734.0 | 0.019 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 387; agent-steps of seated agents on another row's clearway: 2834.

## Deposit check

Person-seconds deposited: 696172.6, of them in excluded cells: 3932.272.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 23771 overlapping pair-steps: p99 0.0024, max 0.0072 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0024 max 0.0072; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 6 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 5.99 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 90 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
