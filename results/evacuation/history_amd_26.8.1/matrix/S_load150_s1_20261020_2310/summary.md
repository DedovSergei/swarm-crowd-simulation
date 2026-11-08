# Experiment `S_load150_s1`

**Task 5.9 stage 4: venue S, 150% requested (seed 1): every seat + standing on the walkway and concourse (M, L: the achievable maximum, also the 125% request)**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 5592 agents (load 150.0%, requested 150%): every one of the 3728 seats and 1864 standing (spawnOvercrowdedCrowd, seed 1; below), buffer N = 8192, 1684 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 230225 evaluations, 4640 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.50)** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-20T23:10:17, 15.5 s wall.

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
| t50 | 680 | 118.9 |
| t90 | 1335 | 233.5 |
| t100 | 1684 | 294.5 |

t_p: the step by which ceil(p x 5592) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 518 | 79 | 13.6 | 268.3 | 21.5 | 54.2 | 12.9-22.9 |
| -x | 5.66 | 559 | 71 | 13.5 | 277.8 | 22.4 | 55.3 | 13.1-23.1 |
| +y | 5.66 | 547 | 78 | 13.6 | 276.7 | 22.0 | 58.5 | 13.5-23.4 |
| -y | 5.66 | 543 | 78 | 13.5 | 280.2 | 21.6 | 58.5 | 13.3-23.3 |
| door +x+y y | 1.20 | 423 | 653 | 1.0 | 277.1 | 76.6 | 125.4 | 147.1-157.1 |
| door +x+y x | 1.20 | 418 | 647 | 1.2 | 265.7 | 79.0 | 115.3 | 113.7-123.7 |
| door -x+y y | 1.20 | 424 | 672 | 1.0 | 289.3 | 73.5 | 130.4 | 150.1-160.0 |
| door -x+y x | 1.20 | 435 | 664 | 1.2 | 269.2 | 81.1 | 125.4 | 149.7-159.7 |
| door -x-y y | 1.20 | 432 | 662 | 0.9 | 294.5 | 73.5 | 120.4 | 134.9-144.8 |
| door -x-y x | 1.20 | 435 | 661 | 0.9 | 291.4 | 74.8 | 125.4 | 129.8-139.8 |
| door +x-y y | 1.20 | 437 | 670 | 0.9 | 279.5 | 78.4 | 120.4 | 134.0-143.9 |
| door +x-y x | 1.20 | 421 | 657 | 1.0 | 262.0 | 80.6 | 120.4 | 135.7-145.7 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 518 | 9.3% | 22.3% |
| -x | avenue | 5.66 | 559 | 10.0% | 24.1% |
| +y | avenue | 5.66 | 547 | 9.8% | 23.5% |
| -y | avenue | 5.66 | 543 | 9.7% | 23.4% |
| door +x+y y | door | 1.20 | 423 | 7.6% | 85.9% |
| door +x+y x | door | 1.20 | 418 | 7.5% | 84.9% |
| door -x+y y | door | 1.20 | 424 | 7.6% | 86.1% |
| door -x+y x | door | 1.20 | 435 | 7.8% | 88.3% |
| door -x-y y | door | 1.20 | 432 | 7.7% | 87.7% |
| door -x-y x | door | 1.20 | 435 | 7.8% | 88.3% |
| door +x-y y | door | 1.20 | 437 | 7.8% | 88.7% |
| door +x-y x | door | 1.20 | 421 | 7.5% | 85.5% |
| **doors (8)** | door | 9.60 | 3425 | 61.2% | |
| **avenues (4)** | avenue | 22.64 | 2167 | 38.8% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 294.5 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 42.3%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 452 | 8.1% | 452 | 8.1% |
| straight +x+y (x wing) 0 | straight | yes | 455 | 8.1% | 455 | 8.1% |
| corner +x+y | corner | **no** | 46 | 0.8% | 46 | 0.8% |
| straight -x+y (y wing) 0 | straight | yes | 445 | 8.0% | 445 | 8.0% |
| straight -x+y (x wing) 0 | straight | yes | 452 | 8.1% | 450 | 8.0% |
| corner -x+y | corner | **no** | 59 | 1.1% | 59 | 1.1% |
| straight -x-y (y wing) 0 | straight | yes | 461 | 8.2% | 461 | 8.2% |
| straight -x-y (x wing) 0 | straight | yes | 452 | 8.1% | 442 | 7.9% |
| corner -x-y | corner | **no** | 52 | 0.9% | 52 | 0.9% |
| straight +x-y (y wing) 0 | straight | yes | 450 | 8.0% | 450 | 8.0% |
| straight +x-y (x wing) 0 | straight | yes | 454 | 8.1% | 454 | 8.1% |
| corner +x-y | corner | **no** | 52 | 0.9% | 52 | 0.9% |
| **straight (8)** | | | 3621 | | 3609 | 64.5% |
| **corner (4)** | | | 209 | | 209 | 3.7% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 1774, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 518 | 13.6 | 268.3 | 0.26 | 0.65 | 0.0% |
| -x | 559 | 13.5 | 277.8 | 0.27 | 0.66 | 0.0% |
| +y | 547 | 13.6 | 276.7 | 0.26 | 0.70 | 0.0% |
| -y | 543 | 13.5 | 280.2 | 0.26 | 0.70 | 0.0% |
| door +x+y y | 423 | 1.0 | 277.1 | 0.92 | 1.50 | 75.0% |
| door +x+y x | 418 | 1.2 | 265.7 | 0.94 | 1.38 | 74.1% |
| door -x+y y | 424 | 1.0 | 289.3 | 0.88 | 1.56 | 66.7% |
| door -x+y x | 435 | 1.2 | 269.2 | 0.97 | 1.50 | 74.1% |
| door -x-y y | 432 | 0.9 | 294.5 | 0.88 | 1.44 | 73.3% |
| door -x-y x | 435 | 0.9 | 291.4 | 0.89 | 1.50 | 66.7% |
| door +x-y y | 437 | 0.9 | 279.5 | 0.94 | 1.44 | 69.0% |
| door +x-y x | 421 | 1.0 | 262.0 | 0.96 | 1.44 | 74.1% |

Mean flow / w J averaged over the doors 0.92, over the avenues 0.26.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 452 | 278 / 174 / 40 | 0.2 | 274.1 | 1.80 | 2.71 | 86% | 86% | 0% | 4.20 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 455 | 268 / 187 / 51 | 0.2 | 262.7 | 1.93 | 2.91 | 85% | 85% | 0% | 3.98 |
| corner +x+y | 1.20 | 31.2 | 46 | 0 / 46 / 0 | 4.2 | 86.8 | 0.56 | 0.90 | 22% | 0% | 22% | 0.98 |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 443 | 255 / 191 / 56 | 0.3 | 286.3 | 1.75 | 2.91 | 79% | 79% | 0% | 4.03 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 452 | 279 / 173 / 38 | 0.5 | 266.2 | 1.84 | 2.91 | 89% | 89% | 0% | 4.21 |
| corner -x+y | 1.20 | 31.2 | 59 | 0 / 59 / 0 | 4.4 | 98.6 | 0.62 | 0.80 | 20% | 0% | 20% | 1.22 |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 451 | 274 / 187 / 48 | 0.2 | 291.6 | 1.75 | 3.11 | 77% | 77% | 0% | 4.05 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 452 | 274 / 178 / 33 | 0.3 | 288.4 | 1.68 | 2.71 | 83% | 83% | 0% | 4.21 |
| corner -x-y | 1.20 | 31.2 | 52 | 0 / 52 / 0 | 4.2 | 91.5 | 0.59 | 0.90 | 10% | 0% | 10% | 0.69 |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 450 | 274 / 176 / 35 | 0.7 | 276.5 | 1.76 | 2.81 | 89% | 86% | 4% | 4.04 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 454 | 269 / 185 / 43 | 0.7 | 259.0 | 1.92 | 2.81 | 88% | 88% | 0% | 4.06 |
| corner +x-y | 1.20 | 31.2 | 52 | 0 / 52 / 0 | 4.2 | 94.4 | 0.58 | 0.80 | 20% | 0% | 20% | 1.04 |

The last agent out (agent 2472, t100 294.5 s): last gangway straight -x-y (y wing) 0, exit door -x-y (y wall). The gangway that cleared last: straight -x-y (y wing) 0 at 291.6 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.36 | 287.7 / 275.5 / 237.5 | 260.1 / 254.1 / 184.2 | 95134.0 | 352393 | 0.254 |
| gangway | 392 | 351.5 | 6.36 | 273.2 / 261.1 / 211.5 | 260.1 / 254.1 / 184.2 | 74802.7 | 199383 | 0.098 |
| walkway | 276 | 257.4 | 5.13 | 168.3 / 126.5 / 3.8 | 152.0 / 122.3 / 3.0 | 19.4 | 28921 | 0.478 |
| avenue | 408 | 384.3 | 2.66 | 187.0 / 8.0 / 0.0 | 148.7 / 1.6 / 0.0 | 0.0 | 28262 | 1.309 |
| exit | 40 | 9.7 | 0.00 | 285.8 / 274.4 / 208.5 | 215.3 / 192.9 / 72.2 | 898.0 | 3295 | 0.914 |
| concourse | 612 | 609.0 | 6.11 | 243.5 / 156.2 / 107.7 | 169.8 / 156.2 / 97.4 | 19413.8 | 92533 | 0.175 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.51 | 246.6 / 244.9 / 233.7 | 246.6 / 244.7 / 231.1 | 114935.6 | 336284 | 0.047 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -19.5 | -10.5 | gangway | 0.96 | 5.82 | 248.5 | 245.2 | 184.2 | 949.4 | 0.024 |
| 2 | -18.5 | -10.5 | gangway | 0.94 | 5.84 | 244.0 | 240.5 | 182.6 | 934.5 | 0.032 |
| 3 | 11.5 | -19.5 | gangway | 0.92 | 5.86 | 230.4 | 225.3 | 184.0 | 924.7 | 0.025 |
| 4 | -19.5 | 11.5 | gangway | 0.92 | 5.73 | 236.5 | 228.3 | 183.5 | 918.1 | 0.022 |
| 5 | -18.5 | 10.5 | gangway | 0.94 | 5.85 | 248.5 | 239.1 | 178.8 | 908.8 | 0.030 |
| 6 | -19.5 | -11.5 | gangway | 0.92 | 5.80 | 236.3 | 230.9 | 180.5 | 908.5 | 0.022 |
| 7 | 10.5 | -19.5 | gangway | 0.96 | 5.83 | 250.8 | 247.3 | 172.6 | 895.3 | 0.025 |
| 8 | -18.5 | 11.5 | gangway | 0.86 | 6.28 | 234.5 | 231.2 | 178.6 | 882.4 | 0.032 |
| 9 | -19.5 | 10.5 | gangway | 0.96 | 5.80 | 252.2 | 242.9 | 169.7 | 867.1 | 0.025 |
| 10 | 10.5 | -18.5 | gangway | 0.94 | 5.70 | 242.8 | 237.3 | 170.4 | 863.0 | 0.032 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -18.5 | 9.5 | seat row | 0.50 | 7.45 | 243.6 | 240.7 | 231.1 | 816.6 | 0.022 |
| 2 | 9.5 | -18.5 | seat row | 0.50 | 7.50 | 243.5 | 237.7 | 229.8 | 802.7 | 0.022 |
| 3 | 9.5 | 18.5 | seat row | 0.50 | 7.51 | 235.8 | 232.8 | 223.0 | 788.7 | 0.023 |
| 4 | -18.5 | -9.5 | seat row | 0.50 | 7.47 | 241.9 | 234.9 | 221.4 | 782.0 | 0.023 |
| 5 | -18.5 | 8.5 | seat row | 0.50 | 7.10 | 234.9 | 232.8 | 223.0 | 746.2 | 0.019 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 344; agent-steps of seated agents on another row's clearway: 2410.

## Deposit check

Person-seconds deposited: 692405.8, of them in excluded cells: 3728.705.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 25489 overlapping pair-steps: p99 0.0032, max 0.0082 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0032 max 0.0082; venue-geometry 2: p99 0.0002 max 0.0002 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 8 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.11 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 94 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
