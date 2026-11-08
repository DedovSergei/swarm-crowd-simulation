# Experiment `S_load150_s9`

**Task 5.11 stage 1 (gridlock robustness, default model, AMD 26.10.1): venue S, 150% load (seed 9)**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 5592 agents (load 150.0%, requested 150%): every one of the 3728 seats and 1864 standing (spawnOvercrowdedCrowd, seed 9; below), buffer N = 8192, 1651 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 231701 evaluations, 4628 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.50)** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `15aa31e8667e4a9417fde7884d907d1832c5e2d6`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-23T17:40:25, 14.6 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Spawn (overcrowding)

| | |
|---|---|
| seated | 3728 (every seat) |
| standing | **1864** (requested round((1.50 - 1) x 3728) = 1864; at most 2143 = floor(2.5 p/m^2 x 857.4 m^2)) |
| standing floor | walkway + rear concourse, 857.4 m^2 |
| standing on the walkway / concourse / gangways | 551 / 1313 / 0 |
| **load** | **150.00%** of the seats (requested 150%) |
| standing crowd's mean density | 2.174 p/m^2 |
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 3.59, all circulation cells 3.59 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 9, 24470 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 683 | 119.5 |
| t90 | 1347 | 235.6 |
| t100 | 1651 | 288.8 |

t_p: the step by which ceil(p x 5592) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 537 | 74 | 13.5 | 276.9 | 21.6 | 55.3 | 13.3-23.3 |
| -x | 5.66 | 548 | 70 | 13.6 | 275.5 | 22.2 | 52.1 | 13.1-23.1 |
| +y | 5.66 | 534 | 74 | 13.6 | 279.0 | 21.3 | 50.0 | 13.3-23.3 |
| -y | 5.66 | 539 | 74 | 13.5 | 276.4 | 21.7 | 58.5 | 12.8-22.7 |
| door +x+y y | 1.20 | 435 | 666 | 1.0 | 279.5 | 78.1 | 120.4 | 138.4-148.3 |
| door +x+y x | 1.20 | 429 | 664 | 1.4 | 282.3 | 76.3 | 110.3 | 134.0-143.9 |
| door -x+y y | 1.20 | 429 | 668 | 0.7 | 288.8 | 74.4 | 115.3 | 138.7-148.7 |
| door -x+y x | 1.20 | 433 | 659 | 0.7 | 272.9 | 79.5 | 130.4 | 138.5-148.5 |
| door -x-y y | 1.20 | 419 | 657 | 1.2 | 284.9 | 73.8 | 125.4 | 142.9-152.9 |
| door -x-y x | 1.20 | 434 | 663 | 1.0 | 271.3 | 80.2 | 115.3 | 141.0-150.9 |
| door +x-y y | 1.20 | 427 | 659 | 0.9 | 268.1 | 79.8 | 120.4 | 139.4-149.4 |
| door +x-y x | 1.20 | 428 | 664 | 1.2 | 282.1 | 76.1 | 120.4 | 140.6-150.6 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 537 | 9.6% | 23.6% |
| -x | avenue | 5.66 | 548 | 9.8% | 24.1% |
| +y | avenue | 5.66 | 534 | 9.5% | 23.4% |
| -y | avenue | 5.66 | 539 | 9.6% | 23.7% |
| door +x+y y | door | 1.20 | 435 | 7.8% | 90.1% |
| door +x+y x | door | 1.20 | 429 | 7.7% | 88.9% |
| door -x+y y | door | 1.20 | 429 | 7.7% | 88.9% |
| door -x+y x | door | 1.20 | 433 | 7.7% | 89.7% |
| door -x-y y | door | 1.20 | 419 | 7.5% | 86.8% |
| door -x-y x | door | 1.20 | 434 | 7.8% | 89.9% |
| door +x-y y | door | 1.20 | 427 | 7.6% | 88.4% |
| door +x-y x | door | 1.20 | 428 | 7.7% | 88.6% |
| **doors (8)** | door | 9.60 | 3434 | 61.4% | |
| **avenues (4)** | avenue | 22.64 | 2158 | 38.6% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 288.8 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 43.1%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 455 | 8.1% | 455 | 8.1% |
| straight +x+y (x wing) 0 | straight | yes | 451 | 8.1% | 451 | 8.1% |
| corner +x+y | corner | **no** | 42 | 0.8% | 42 | 0.8% |
| straight -x+y (y wing) 0 | straight | yes | 458 | 8.2% | 458 | 8.2% |
| straight -x+y (x wing) 0 | straight | yes | 453 | 8.1% | 448 | 8.0% |
| corner -x+y | corner | **no** | 48 | 0.9% | 48 | 0.9% |
| straight -x-y (y wing) 0 | straight | yes | 452 | 8.1% | 452 | 8.1% |
| straight -x-y (x wing) 0 | straight | yes | 450 | 8.0% | 449 | 8.0% |
| corner -x-y | corner | **no** | 53 | 0.9% | 53 | 0.9% |
| straight +x-y (y wing) 0 | straight | yes | 455 | 8.1% | 455 | 8.1% |
| straight +x-y (x wing) 0 | straight | yes | 451 | 8.1% | 451 | 8.1% |
| corner +x-y | corner | **no** | 41 | 0.7% | 41 | 0.7% |
| **straight (8)** | | | 3625 | | 3619 | 64.7% |
| **corner (4)** | | | 184 | | 184 | 3.3% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 1789, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 537 | 13.5 | 276.9 | 0.26 | 0.66 | 0.0% |
| -x | 548 | 13.6 | 275.5 | 0.27 | 0.62 | 0.0% |
| +y | 534 | 13.6 | 279.0 | 0.26 | 0.60 | 0.0% |
| -y | 539 | 13.5 | 276.4 | 0.26 | 0.70 | 0.0% |
| door +x+y y | 435 | 1.0 | 279.5 | 0.93 | 1.44 | 65.5% |
| door +x+y x | 429 | 1.4 | 282.3 | 0.91 | 1.32 | 65.5% |
| door -x+y y | 429 | 0.7 | 288.8 | 0.89 | 1.38 | 65.5% |
| door -x+y x | 433 | 0.7 | 272.9 | 0.95 | 1.56 | 75.0% |
| door -x-y y | 419 | 1.2 | 284.9 | 0.88 | 1.50 | 69.0% |
| door -x-y x | 434 | 1.0 | 271.3 | 0.96 | 1.38 | 67.9% |
| door +x-y y | 427 | 0.9 | 268.1 | 0.95 | 1.44 | 66.7% |
| door +x-y x | 428 | 1.2 | 282.1 | 0.91 | 1.44 | 65.5% |

Mean flow / w J averaged over the doors 0.92, over the avenues 0.26.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 455 | 273 / 182 / 35 | 0.3 | 276.5 | 1.77 | 2.71 | 86% | 86% | 0% | 4.15 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 451 | 268 / 183 / 47 | 0.5 | 279.3 | 1.79 | 2.81 | 83% | 83% | 0% | 4.08 |
| corner +x+y | 1.20 | 31.2 | 42 | 0 / 42 / 0 | 4.5 | 56.0 | 0.81 | 1.60 | 17% | 0% | 17% | 0.56 |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 453 | 268 / 190 / 55 | 0.2 | 285.8 | 1.79 | 2.91 | 79% | 79% | 0% | 4.08 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 453 | 277 / 177 / 31 | 0.3 | 269.9 | 1.80 | 2.81 | 86% | 86% | 0% | 4.24 |
| corner -x+y | 1.20 | 31.2 | 48 | 0 / 48 / 0 | 4.4 | 85.9 | 0.59 | 0.80 | 11% | 0% | 11% | 0.64 |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 451 | 268 / 184 / 57 | 0.5 | 281.9 | 1.81 | 2.91 | 79% | 79% | 0% | 4.15 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 450 | 274 / 176 / 35 | 0.2 | 268.3 | 1.81 | 2.81 | 89% | 89% | 0% | 4.19 |
| corner -x-y | 1.20 | 31.2 | 53 | 0 / 53 / 0 | 0.3 | 88.0 | 0.60 | 1.00 | 22% | 0% | 22% | 1.10 |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 455 | 270 / 185 / 39 | 0.2 | 265.2 | 1.86 | 2.71 | 89% | 89% | 0% | 4.10 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 451 | 263 / 188 / 48 | 0.7 | 279.2 | 1.79 | 2.81 | 86% | 86% | 0% | 4.05 |
| corner +x-y | 1.20 | 31.2 | 41 | 0 / 41 / 0 | 4.4 | 49.3 | 0.91 | 1.60 | 20% | 0% | 20% | 0.57 |

The last agent out (agent 1597, t100 288.8 s): last gangway straight -x+y (y wing) 0, exit door -x+y (y wall). The gangway that cleared last: straight -x+y (y wing) 0 at 285.8 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.44 | 283.2 / 274.4 / 234.5 | 257.1 / 252.0 / 181.0 | 95777.6 | 351143 | 0.253 |
| gangway | 392 | 351.5 | 6.44 | 272.7 / 253.4 / 207.1 | 257.1 / 252.0 / 181.0 | 75013.6 | 198043 | 0.096 |
| walkway | 276 | 257.4 | 5.24 | 154.6 / 117.2 / 4.0 | 137.0 / 117.2 / 2.4 | 24.0 | 28568 | 0.483 |
| avenue | 408 | 384.3 | 2.44 | 172.1 / 9.1 / 0.0 | 138.7 / 1.7 / 0.0 | 0.0 | 28122 | 1.310 |
| exit | 40 | 9.7 | 0.00 | 282.5 / 274.3 / 203.2 | 213.4 / 186.8 / 72.8 | 913.1 | 3299 | 0.914 |
| concourse | 612 | 609.0 | 6.08 | 240.0 / 148.5 / 108.1 | 160.2 / 147.6 / 99.0 | 19827.0 | 93110 | 0.174 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.55 | 245.4 / 241.2 / 224.2 | 245.4 / 241.0 / 221.6 | 119402.2 | 341911 | 0.047 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 10.5 | 19.5 | gangway | 0.96 | 5.67 | 246.4 | 237.7 | 171.2 | 886.1 | 0.025 |
| 2 | -11.5 | 21.5 | gangway | 0.89 | 5.91 | 238.6 | 235.2 | 181.0 | 885.7 | 0.034 |
| 3 | -18.5 | 10.5 | gangway | 0.94 | 5.74 | 243.3 | 239.3 | 174.4 | 877.1 | 0.033 |
| 4 | -19.5 | -10.5 | gangway | 0.96 | 5.80 | 244.2 | 229.5 | 161.1 | 851.4 | 0.023 |
| 5 | 11.5 | 19.5 | gangway | 0.92 | 6.16 | 230.5 | 226.0 | 164.9 | 838.5 | 0.024 |
| 6 | 10.5 | 18.5 | gangway | 0.94 | 5.82 | 242.1 | 237.5 | 165.5 | 835.6 | 0.036 |
| 7 | -11.5 | -19.5 | gangway | 0.92 | 5.92 | 222.1 | 213.9 | 164.2 | 828.4 | 0.025 |
| 8 | 22.5 | 11.5 | gangway | 0.86 | 5.91 | 245.6 | 227.4 | 172.5 | 820.5 | 0.052 |
| 9 | 18.5 | 10.5 | gangway | 0.94 | 5.87 | 239.8 | 234.9 | 156.5 | 799.7 | 0.041 |
| 10 | 19.5 | 11.5 | gangway | 0.92 | 5.74 | 226.9 | 223.7 | 159.0 | 789.7 | 0.026 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -18.5 | 9.5 | seat row | 0.50 | 7.51 | 242.2 | 236.3 | 221.6 | 784.8 | 0.023 |
| 2 | 9.5 | 18.5 | seat row | 0.50 | 7.36 | 238.0 | 232.8 | 221.4 | 771.3 | 0.023 |
| 3 | 9.5 | -18.5 | seat row | 0.50 | 7.43 | 234.2 | 230.0 | 219.2 | 768.5 | 0.023 |
| 4 | -18.5 | -9.5 | seat row | 0.50 | 7.37 | 233.0 | 228.1 | 218.6 | 768.0 | 0.024 |
| 5 | 18.5 | 9.5 | seat row | 0.50 | 7.40 | 234.9 | 221.3 | 209.9 | 734.2 | 0.024 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 347; agent-steps of seated agents on another row's clearway: 2380.

## Deposit check

Person-seconds deposited: 696802.6, of them in excluded cells: 3748.584.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 25689 overlapping pair-steps: p99 0.0027, max 0.0078 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0027 max 0.0078; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 10 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.08 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 84 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
