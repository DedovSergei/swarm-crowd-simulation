# Experiment `S_load150_s3`

**Task 5.10 stage 4 (AMD 26.10.1): venue S, 150% requested (seed 3): every seat + standing on the walkway and concourse (M: the achievable maximum, also the 125% request)**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 5592 agents (load 150.0%, requested 150%): every one of the 3728 seats and 1864 standing (spawnOvercrowdedCrowd, seed 3; below), buffer N = 8192, 1613 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 230932 evaluations, 4639 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.50)** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T19:38:07, 16.0 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Spawn (overcrowding)

| | |
|---|---|
| seated | 3728 (every seat) |
| standing | **1864** (requested round((1.50 - 1) x 3728) = 1864; at most 2143 = floor(2.5 p/m^2 x 857.4 m^2)) |
| standing floor | walkway + rear concourse, 857.4 m^2 |
| standing on the walkway / concourse / gangways | 533 / 1331 / 0 |
| **load** | **150.00%** of the seats (requested 150%) |
| standing crowd's mean density | 2.174 p/m^2 |
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 3.74, all circulation cells 3.74 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 3, 25228 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 683 | 119.5 |
| t90 | 1338 | 234.0 |
| t100 | 1613 | 282.1 |

t_p: the step by which ceil(p x 5592) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 542 | 72 | 13.5 | 276.7 | 21.8 | 52.1 | 13.1-23.1 |
| -x | 5.66 | 550 | 74 | 13.6 | 277.9 | 22.0 | 56.4 | 13.3-23.3 |
| +y | 5.66 | 537 | 77 | 13.5 | 274.3 | 21.8 | 54.2 | 12.9-22.9 |
| -y | 5.66 | 536 | 75 | 13.6 | 276.5 | 21.6 | 53.2 | 13.5-23.4 |
| door +x+y y | 1.20 | 428 | 662 | 0.9 | 273.0 | 78.6 | 120.4 | 141.5-151.5 |
| door +x+y x | 1.20 | 434 | 663 | 0.9 | 282.1 | 77.1 | 125.4 | 132.1-142.0 |
| door -x+y y | 1.20 | 423 | 662 | 1.0 | 271.6 | 78.1 | 115.3 | 111.6-121.6 |
| door -x+y x | 1.20 | 425 | 647 | 0.9 | 271.8 | 78.4 | 125.4 | 128.0-138.0 |
| door -x-y y | 1.20 | 424 | 668 | 1.0 | 262.2 | 81.1 | 115.3 | 150.4-160.4 |
| door -x-y x | 1.20 | 431 | 657 | 1.0 | 277.2 | 78.0 | 115.3 | 109.0-118.9 |
| door +x-y y | 1.20 | 427 | 665 | 0.9 | 277.2 | 77.2 | 120.4 | 138.7-148.7 |
| door +x-y x | 1.20 | 435 | 670 | 1.0 | 281.4 | 77.5 | 115.3 | 143.2-153.2 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 542 | 9.7% | 24.4% |
| -x | avenue | 5.66 | 550 | 9.8% | 24.7% |
| +y | avenue | 5.66 | 537 | 9.6% | 24.1% |
| -y | avenue | 5.66 | 536 | 9.6% | 24.1% |
| door +x+y y | door | 1.20 | 428 | 7.7% | 90.7% |
| door +x+y x | door | 1.20 | 434 | 7.8% | 92.0% |
| door -x+y y | door | 1.20 | 423 | 7.6% | 89.7% |
| door -x+y x | door | 1.20 | 425 | 7.6% | 90.1% |
| door -x-y y | door | 1.20 | 424 | 7.6% | 89.9% |
| door -x-y x | door | 1.20 | 431 | 7.7% | 91.4% |
| door +x-y y | door | 1.20 | 427 | 7.6% | 90.5% |
| door +x-y x | door | 1.20 | 435 | 7.8% | 92.2% |
| **doors (8)** | door | 9.60 | 3427 | 61.3% | |
| **avenues (4)** | avenue | 22.64 | 2165 | 38.7% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 282.1 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 44.1%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 450 | 8.0% | 450 | 8.0% |
| straight +x+y (x wing) 0 | straight | yes | 451 | 8.1% | 451 | 8.1% |
| corner +x+y | corner | **no** | 50 | 0.9% | 50 | 0.9% |
| straight -x+y (y wing) 0 | straight | yes | 453 | 8.1% | 453 | 8.1% |
| straight -x+y (x wing) 0 | straight | yes | 452 | 8.1% | 452 | 8.1% |
| corner -x+y | corner | **no** | 51 | 0.9% | 51 | 0.9% |
| straight -x-y (y wing) 0 | straight | yes | 452 | 8.1% | 452 | 8.1% |
| straight -x-y (x wing) 0 | straight | yes | 451 | 8.1% | 451 | 8.1% |
| corner -x-y | corner | **no** | 47 | 0.8% | 47 | 0.8% |
| straight +x-y (y wing) 0 | straight | yes | 454 | 8.1% | 454 | 8.1% |
| straight +x-y (x wing) 0 | straight | yes | 450 | 8.0% | 450 | 8.0% |
| corner +x-y | corner | **no** | 53 | 0.9% | 53 | 0.9% |
| **straight (8)** | | | 3613 | | 3613 | 64.6% |
| **corner (4)** | | | 201 | | 201 | 3.6% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 1778, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 542 | 13.5 | 276.7 | 0.26 | 0.62 | 0.0% |
| -x | 550 | 13.6 | 277.9 | 0.26 | 0.67 | 0.0% |
| +y | 537 | 13.5 | 274.3 | 0.26 | 0.65 | 0.0% |
| -y | 536 | 13.6 | 276.5 | 0.26 | 0.64 | 0.0% |
| door +x+y y | 428 | 0.9 | 273.0 | 0.94 | 1.44 | 67.9% |
| door +x+y x | 434 | 0.9 | 282.1 | 0.92 | 1.50 | 72.4% |
| door -x+y y | 423 | 1.0 | 271.6 | 0.93 | 1.38 | 67.9% |
| door -x+y x | 425 | 0.9 | 271.8 | 0.94 | 1.50 | 64.3% |
| door -x-y y | 424 | 1.0 | 262.2 | 0.97 | 1.38 | 70.4% |
| door -x-y x | 431 | 1.0 | 277.2 | 0.93 | 1.38 | 78.6% |
| door +x-y y | 427 | 0.9 | 277.2 | 0.92 | 1.44 | 60.7% |
| door +x-y x | 435 | 1.0 | 281.4 | 0.93 | 1.38 | 72.4% |

Mean flow / w J averaged over the doors 0.94, over the avenues 0.26.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 450 | 265 / 186 / 47 | 0.3 | 270.1 | 1.85 | 2.81 | 86% | 82% | 4% | 4.09 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 451 | 271 / 180 / 49 | 0.3 | 279.2 | 1.79 | 2.91 | 86% | 86% | 0% | 4.19 |
| corner +x+y | 1.20 | 31.2 | 50 | 1 / 49 / 0 | 0.2 | 82.0 | 0.61 | 1.20 | 11% | 0% | 11% | 0.64 |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 453 | 265 / 188 / 63 | 0.5 | 268.7 | 1.92 | 3.11 | 85% | 85% | 0% | 4.12 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 452 | 277 / 176 / 42 | 0.7 | 268.8 | 1.84 | 3.11 | 89% | 85% | 4% | 4.15 |
| corner -x+y | 1.20 | 31.2 | 51 | 0 / 51 / 0 | 4.4 | 75.4 | 0.72 | 0.80 | 25% | 0% | 25% | 1.07 |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 452 | 260 / 192 / 47 | 0.3 | 259.2 | 1.93 | 3.01 | 92% | 88% | 4% | 4.00 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 451 | 276 / 176 / 46 | 0.5 | 274.3 | 1.82 | 3.01 | 86% | 86% | 0% | 4.16 |
| corner -x-y | 1.20 | 31.2 | 47 | 0 / 47 / 0 | 4.2 | 87.3 | 0.56 | 0.80 | 11% | 0% | 11% | 0.62 |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 454 | 264 / 191 / 42 | 0.3 | 274.3 | 1.81 | 2.91 | 86% | 86% | 0% | 4.08 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 450 | 268 / 182 / 50 | 0.3 | 278.5 | 1.80 | 2.91 | 86% | 86% | 0% | 4.21 |
| corner +x-y | 1.20 | 31.2 | 53 | 0 / 53 / 0 | 4.4 | 79.2 | 0.71 | 1.20 | 25% | 0% | 25% | 1.08 |

The last agent out (agent 694, t100 282.1 s): last gangway straight +x+y (x wing) 0, exit door +x+y (x wall). The gangway that cleared last: straight +x+y (x wing) 0 at 279.2 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.51 | 277.4 / 269.4 / 232.8 | 254.5 / 249.6 / 178.6 | 98624.4 | 351863 | 0.254 |
| gangway | 392 | 351.5 | 6.51 | 266.9 / 252.9 / 202.7 | 254.5 / 249.6 / 178.6 | 77519.5 | 199014 | 0.096 |
| walkway | 276 | 257.4 | 5.06 | 142.5 / 107.9 / 0.7 | 123.3 / 99.7 / 0.7 | 3.5 | 27055 | 0.511 |
| avenue | 408 | 384.3 | 2.51 | 167.7 / 10.0 / 0.0 | 127.3 / 0.9 / 0.0 | 0.0 | 28225 | 1.310 |
| exit | 40 | 9.7 | 0.00 | 277.2 / 268.3 / 204.5 | 214.4 / 192.2 / 71.2 | 903.5 | 3288 | 0.918 |
| concourse | 612 | 609.0 | 6.08 | 241.0 / 154.4 / 111.1 | 170.5 / 153.7 / 92.0 | 20197.9 | 94282 | 0.173 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.53 | 243.1 / 239.8 / 223.2 | 243.1 / 239.6 / 220.6 | 116633.6 | 338882 | 0.047 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -18.5 | -10.5 | gangway | 0.94 | 5.97 | 242.6 | 238.0 | 174.4 | 900.5 | 0.036 |
| 2 | -19.5 | -11.5 | gangway | 0.92 | 5.89 | 230.5 | 226.5 | 178.6 | 875.3 | 0.024 |
| 3 | -19.5 | -10.5 | gangway | 0.96 | 5.56 | 246.6 | 232.6 | 167.4 | 862.7 | 0.026 |
| 4 | -18.5 | 10.5 | gangway | 0.94 | 6.07 | 232.3 | 228.4 | 160.7 | 847.4 | 0.034 |
| 5 | 10.5 | 18.5 | gangway | 0.94 | 5.78 | 236.6 | 229.8 | 167.0 | 845.9 | 0.041 |
| 6 | -19.5 | 10.5 | gangway | 0.96 | 5.93 | 240.7 | 237.3 | 156.2 | 832.3 | 0.028 |
| 7 | 11.5 | 19.5 | gangway | 0.92 | 5.50 | 225.5 | 221.6 | 168.3 | 818.9 | 0.023 |
| 8 | 19.5 | -10.5 | gangway | 0.96 | 5.54 | 236.8 | 228.6 | 159.9 | 809.9 | 0.027 |
| 9 | 19.5 | 11.5 | gangway | 0.92 | 6.12 | 229.0 | 221.8 | 158.5 | 806.2 | 0.024 |
| 10 | -19.5 | 11.5 | gangway | 0.92 | 5.97 | 220.6 | 214.6 | 155.5 | 800.9 | 0.025 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -18.5 | 9.5 | seat row | 0.50 | 7.46 | 231.6 | 228.8 | 215.7 | 764.6 | 0.023 |
| 2 | 18.5 | 9.5 | seat row | 0.50 | 7.31 | 231.2 | 228.8 | 220.6 | 762.5 | 0.024 |
| 3 | -18.5 | -9.5 | seat row | 0.50 | 7.33 | 234.4 | 229.0 | 218.3 | 757.8 | 0.024 |
| 4 | 9.5 | -18.5 | seat row | 0.50 | 7.38 | 232.1 | 226.3 | 212.2 | 739.8 | 0.024 |
| 5 | 18.5 | -9.5 | seat row | 0.50 | 7.47 | 232.1 | 221.1 | 208.5 | 723.3 | 0.025 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 386; agent-steps of seated agents on another row's clearway: 2678.

## Deposit check

Person-seconds deposited: 694485.3, of them in excluded cells: 3740.261.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 24620 overlapping pair-steps: p99 0.0033, max 0.0098 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0033 max 0.0098; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00752 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 4 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.08 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 94 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
