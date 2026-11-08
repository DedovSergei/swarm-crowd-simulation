# Experiment `S_load150_s1`

**Task 5.10 stage 4 (AMD 26.10.1): venue S, 150% requested (seed 1): every seat + standing on the walkway and concourse (M: the achievable maximum, also the 125% request)**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 5592 agents (load 150.0%, requested 150%): every one of the 3728 seats and 1864 standing (spawnOvercrowdedCrowd, seed 1; below), buffer N = 8192, 1682 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 230555 evaluations, 4639 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.50)** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T19:37:27, 15.9 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Spawn (overcrowding)

| | |
|---|---|
| seated | 3728 (every seat) |
| standing | **1864** (requested round((1.50 - 1) x 3728) = 1864; at most 2143 = floor(2.5 p/m^2 x 857.4 m^2)) |
| standing floor | walkway + rear concourse, 857.4 m^2 |
| standing on the walkway / concourse / gangways | 556 / 1308 / 0 |
| **load** | **150.00%** of the seats (requested 150%) |
| standing crowd's mean density | 2.174 p/m^2 |
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 3.46, all circulation cells 3.46 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 1, 25138 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 681 | 119.1 |
| t90 | 1335 | 233.5 |
| t100 | 1682 | 294.2 |

t_p: the step by which ceil(p x 5592) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 522 | 79 | 13.6 | 270.2 | 21.6 | 54.2 | 12.9-22.9 |
| -x | 5.66 | 563 | 71 | 13.5 | 278.1 | 22.5 | 55.3 | 12.8-22.7 |
| +y | 5.66 | 543 | 78 | 13.6 | 274.6 | 22.0 | 58.5 | 13.5-23.4 |
| -y | 5.66 | 545 | 78 | 13.5 | 276.9 | 21.9 | 58.5 | 13.3-23.3 |
| door +x+y y | 1.20 | 419 | 653 | 1.0 | 284.2 | 73.9 | 120.4 | 127.9-137.8 |
| door +x+y x | 1.20 | 423 | 647 | 1.2 | 292.1 | 72.7 | 120.4 | 121.6-131.5 |
| door -x+y y | 1.20 | 433 | 672 | 1.0 | 294.2 | 73.8 | 120.4 | 148.7-158.6 |
| door -x+y x | 1.20 | 430 | 664 | 1.2 | 281.2 | 76.7 | 125.4 | 137.8-147.8 |
| door -x-y y | 1.20 | 421 | 662 | 0.9 | 293.7 | 71.9 | 120.4 | 144.1-154.1 |
| door -x-y x | 1.20 | 434 | 661 | 0.9 | 269.5 | 80.7 | 120.4 | 141.0-150.9 |
| door +x-y y | 1.20 | 441 | 670 | 0.9 | 277.6 | 79.6 | 120.4 | 142.2-152.2 |
| door +x-y x | 1.20 | 418 | 657 | 1.0 | 288.2 | 72.7 | 125.4 | 138.7-148.7 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 522 | 9.3% | 22.5% |
| -x | avenue | 5.66 | 563 | 10.1% | 24.3% |
| +y | avenue | 5.66 | 543 | 9.7% | 23.4% |
| -y | avenue | 5.66 | 545 | 9.7% | 23.5% |
| door +x+y y | door | 1.20 | 419 | 7.5% | 85.2% |
| door +x+y x | door | 1.20 | 423 | 7.6% | 86.0% |
| door -x+y y | door | 1.20 | 433 | 7.7% | 88.0% |
| door -x+y x | door | 1.20 | 430 | 7.7% | 87.4% |
| door -x-y y | door | 1.20 | 421 | 7.5% | 85.6% |
| door -x-y x | door | 1.20 | 434 | 7.8% | 88.2% |
| door +x-y y | door | 1.20 | 441 | 7.9% | 89.7% |
| door +x-y x | door | 1.20 | 418 | 7.5% | 85.0% |
| **doors (8)** | door | 9.60 | 3419 | 61.1% | |
| **avenues (4)** | avenue | 22.64 | 2173 | 38.9% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 294.2 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 42.3%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 452 | 8.1% | 446 | 8.0% |
| straight +x+y (x wing) 0 | straight | yes | 461 | 8.2% | 461 | 8.2% |
| corner +x+y | corner | **no** | 46 | 0.8% | 46 | 0.8% |
| straight -x+y (y wing) 0 | straight | yes | 450 | 8.0% | 450 | 8.0% |
| straight -x+y (x wing) 0 | straight | yes | 452 | 8.1% | 445 | 8.0% |
| corner -x+y | corner | **no** | 59 | 1.1% | 59 | 1.1% |
| straight -x-y (y wing) 0 | straight | yes | 456 | 8.2% | 456 | 8.2% |
| straight -x-y (x wing) 0 | straight | yes | 452 | 8.1% | 447 | 8.0% |
| corner -x-y | corner | **no** | 52 | 0.9% | 52 | 0.9% |
| straight +x-y (y wing) 0 | straight | yes | 450 | 8.0% | 449 | 8.0% |
| straight +x-y (x wing) 0 | straight | yes | 455 | 8.1% | 455 | 8.1% |
| corner +x-y | corner | **no** | 52 | 0.9% | 52 | 0.9% |
| **straight (8)** | | | 3628 | | 3609 | 64.5% |
| **corner (4)** | | | 209 | | 209 | 3.7% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 1774, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 522 | 13.6 | 270.2 | 0.26 | 0.65 | 0.0% |
| -x | 563 | 13.5 | 278.1 | 0.27 | 0.66 | 0.0% |
| +y | 543 | 13.6 | 274.6 | 0.26 | 0.70 | 0.0% |
| -y | 545 | 13.5 | 276.9 | 0.26 | 0.70 | 0.0% |
| door +x+y y | 419 | 1.0 | 284.2 | 0.88 | 1.44 | 58.6% |
| door +x+y x | 423 | 1.2 | 292.1 | 0.87 | 1.44 | 66.7% |
| door -x+y y | 433 | 1.0 | 294.2 | 0.88 | 1.44 | 63.3% |
| door -x+y x | 430 | 1.2 | 281.2 | 0.92 | 1.50 | 72.4% |
| door -x-y y | 421 | 0.9 | 293.7 | 0.86 | 1.44 | 63.3% |
| door -x-y x | 434 | 0.9 | 269.5 | 0.97 | 1.44 | 71.4% |
| door +x-y y | 441 | 0.9 | 277.6 | 0.95 | 1.44 | 78.6% |
| door +x-y x | 418 | 1.0 | 288.2 | 0.87 | 1.50 | 62.1% |

Mean flow / w J averaged over the doors 0.90, over the avenues 0.26.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 452 | 274 / 178 / 41 | 0.2 | 281.2 | 1.75 | 2.81 | 83% | 83% | 0% | 4.27 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 455 | 273 / 188 / 51 | 0.2 | 289.1 | 1.77 | 3.41 | 79% | 79% | 0% | 4.05 |
| corner +x+y | 1.20 | 31.2 | 46 | 0 / 46 / 0 | 4.2 | 87.8 | 0.55 | 0.90 | 22% | 0% | 22% | 0.98 |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 443 | 264 / 187 / 50 | 0.3 | 291.2 | 1.72 | 2.81 | 77% | 77% | 0% | 4.05 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 452 | 274 / 180 / 30 | 0.5 | 278.3 | 1.74 | 3.01 | 86% | 86% | 0% | 4.25 |
| corner -x+y | 1.20 | 31.2 | 59 | 0 / 59 / 0 | 4.4 | 95.5 | 0.65 | 1.00 | 20% | 0% | 20% | 1.23 |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 451 | 263 / 193 / 42 | 0.2 | 290.7 | 1.71 | 2.71 | 77% | 77% | 0% | 4.04 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 452 | 273 / 180 / 53 | 0.3 | 266.6 | 1.90 | 2.81 | 93% | 89% | 4% | 4.12 |
| corner -x-y | 1.20 | 31.2 | 52 | 0 / 52 / 0 | 4.2 | 92.0 | 0.59 | 0.90 | 10% | 0% | 10% | 0.69 |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 450 | 278 / 172 / 38 | 0.7 | 274.6 | 1.78 | 2.91 | 86% | 86% | 0% | 4.12 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 454 | 266 / 189 / 50 | 0.7 | 285.3 | 1.77 | 3.01 | 83% | 79% | 3% | 3.91 |
| corner +x-y | 1.20 | 31.2 | 52 | 0 / 52 / 0 | 4.2 | 95.5 | 0.57 | 0.80 | 20% | 0% | 20% | 1.04 |

The last agent out (agent 1511, t100 294.2 s): last gangway straight -x+y (y wing) 0, exit door -x+y (y wall). The gangway that cleared last: straight -x+y (y wing) 0 at 291.2 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.41 | 289.3 / 276.0 / 233.3 | 259.4 / 252.7 / 181.0 | 96546.5 | 352810 | 0.254 |
| gangway | 392 | 351.5 | 6.41 | 274.4 / 256.9 / 205.5 | 259.4 / 252.7 / 181.0 | 75525.3 | 199880 | 0.098 |
| walkway | 276 | 257.4 | 5.10 | 166.0 / 124.2 / 3.0 | 148.1 / 124.2 / 1.7 | 15.0 | 28636 | 0.484 |
| avenue | 408 | 384.3 | 2.66 | 184.4 / 8.0 / 0.0 | 143.1 / 1.6 / 0.0 | 0.0 | 28334 | 1.309 |
| exit | 40 | 9.7 | 0.00 | 286.8 / 275.1 / 203.2 | 211.8 / 190.1 / 71.5 | 899.2 | 3282 | 0.917 |
| concourse | 612 | 609.0 | 6.10 | 240.8 / 152.9 / 110.4 | 167.7 / 150.8 / 93.7 | 20107.0 | 92678 | 0.174 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.56 | 247.0 / 244.3 / 231.9 | 247.0 / 244.2 / 229.3 | 115691.6 | 336811 | 0.047 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 11.5 | -19.5 | gangway | 0.92 | 6.10 | 238.9 | 231.6 | 181.0 | 934.5 | 0.024 |
| 2 | 10.5 | 18.5 | gangway | 0.94 | 6.13 | 241.5 | 238.6 | 179.3 | 924.5 | 0.032 |
| 3 | -19.5 | 11.5 | gangway | 0.92 | 5.90 | 239.3 | 232.6 | 180.3 | 916.6 | 0.022 |
| 4 | -18.5 | 10.5 | gangway | 0.94 | 5.85 | 244.0 | 240.0 | 178.2 | 907.7 | 0.032 |
| 5 | -19.5 | -11.5 | gangway | 0.92 | 5.90 | 231.4 | 227.4 | 180.3 | 901.2 | 0.023 |
| 6 | -19.5 | 10.5 | gangway | 0.96 | 5.81 | 248.5 | 242.8 | 174.2 | 898.8 | 0.024 |
| 7 | -18.5 | -10.5 | gangway | 0.94 | 5.65 | 244.7 | 240.7 | 177.0 | 883.7 | 0.032 |
| 8 | 10.5 | -19.5 | gangway | 0.96 | 5.71 | 244.9 | 236.6 | 167.7 | 874.6 | 0.027 |
| 9 | 10.5 | -18.5 | gangway | 0.94 | 5.89 | 240.1 | 234.7 | 165.1 | 840.8 | 0.035 |
| 10 | -18.5 | 11.5 | gangway | 0.86 | 6.19 | 238.7 | 231.6 | 174.7 | 825.5 | 0.034 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -18.5 | 9.5 | seat row | 0.50 | 7.49 | 240.5 | 238.4 | 229.3 | 810.6 | 0.022 |
| 2 | -18.5 | -9.5 | seat row | 0.50 | 7.41 | 241.4 | 235.4 | 228.6 | 801.1 | 0.023 |
| 3 | 9.5 | 18.5 | seat row | 0.50 | 7.48 | 239.4 | 237.5 | 226.2 | 791.2 | 0.023 |
| 4 | 9.5 | -18.5 | seat row | 0.50 | 7.41 | 234.7 | 229.7 | 217.1 | 758.0 | 0.023 |
| 5 | -18.5 | 8.5 | seat row | 0.50 | 6.92 | 233.0 | 226.9 | 210.9 | 698.9 | 0.020 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 355; agent-steps of seated agents on another row's clearway: 2446.

## Deposit check

Person-seconds deposited: 693394.9, of them in excluded cells: 3774.607.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 23077 overlapping pair-steps: p99 0.0036, max 0.0059 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0036 max 0.0059; venue-geometry 1: p99 0.0001 max 0.0001 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 5 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.10 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 102 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
