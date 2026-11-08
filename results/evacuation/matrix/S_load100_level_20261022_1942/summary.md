# Experiment `S_load100_level`

**Task 5.10 stage 4 (AMD 26.10.1) (model variants): venue S, 100% load, queue-aware exit choice, level walking speed**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 3728 agents on 100% of the 3728 seats (spawnSeatedCrowd, seed 1337), buffer N = 4096, 885 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, level speed** (exit choice: 93449 evaluations, 3070 switches, 0 forced choices).
Capacity: **within design capacity** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T19:42:40, 82.1 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 433 | 75.7 |
| t90 | 734 | 128.4 |
| t100 | 885 | 154.8 |

t_p: the step by which ceil(p x 3728) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 296 | 0 | 24.0 | 154.8 | 24.0 | 25.5 | 41.8-51.8 |
| -x | 5.66 | 293 | 0 | 24.0 | 152.3 | 24.2 | 26.6 | 41.1-51.1 |
| +y | 5.66 | 287 | 0 | 24.0 | 152.7 | 23.6 | 25.5 | 35.9-45.8 |
| -y | 5.66 | 292 | 0 | 24.0 | 153.6 | 23.9 | 26.6 | 40.2-50.2 |
| door +x+y y | 1.20 | 321 | 466 | 4.2 | 141.5 | 116.7 | 140.4 | 109.7-119.6 |
| door +x+y x | 1.20 | 316 | 466 | 4.2 | 141.5 | 114.9 | 140.4 | 75.9-85.9 |
| door -x+y y | 1.20 | 324 | 466 | 4.2 | 144.6 | 115.2 | 140.4 | 27.8-37.8 |
| door -x+y x | 1.20 | 321 | 466 | 4.2 | 141.3 | 116.9 | 145.4 | 89.7-99.7 |
| door -x-y y | 1.20 | 324 | 466 | 4.2 | 148.7 | 112.0 | 140.4 | 44.4-54.4 |
| door -x-y x | 1.20 | 318 | 466 | 4.2 | 141.3 | 115.8 | 140.4 | 103.4-113.3 |
| door +x-y y | 1.20 | 316 | 466 | 4.2 | 144.1 | 112.8 | 145.4 | 97.2-107.2 |
| door +x-y x | 1.20 | 320 | 466 | 4.2 | 140.5 | 117.3 | 135.4 | 26.8-36.7 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 296 | 7.9% | 24.2% |
| -x | avenue | 5.66 | 293 | 7.9% | 24.0% |
| +y | avenue | 5.66 | 287 | 7.7% | 23.5% |
| -y | avenue | 5.66 | 292 | 7.8% | 23.9% |
| door +x+y y | door | 1.20 | 321 | 8.6% | 124.0% |
| door +x+y x | door | 1.20 | 316 | 8.5% | 122.1% |
| door -x+y y | door | 1.20 | 324 | 8.7% | 125.2% |
| door -x+y x | door | 1.20 | 321 | 8.6% | 124.0% |
| door -x-y y | door | 1.20 | 324 | 8.7% | 125.2% |
| door -x-y x | door | 1.20 | 318 | 8.5% | 122.9% |
| door +x-y y | door | 1.20 | 316 | 8.5% | 122.1% |
| door +x-y x | door | 1.20 | 320 | 8.6% | 123.6% |
| **doors (8)** | door | 9.60 | 2560 | 68.7% | |
| **avenues (4)** | avenue | 22.64 | 1168 | 31.3% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 154.8 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 53.6%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 464 | 12.4% | 464 | 12.4% |
| straight +x+y (x wing) 0 | straight | yes | 464 | 12.4% | 464 | 12.4% |
| corner +x+y | corner | **no** | 4 | 0.1% | 4 | 0.1% |
| straight -x+y (y wing) 0 | straight | yes | 464 | 12.4% | 464 | 12.4% |
| straight -x+y (x wing) 0 | straight | yes | 464 | 12.4% | 464 | 12.4% |
| corner -x+y | corner | **no** | 4 | 0.1% | 4 | 0.1% |
| straight -x-y (y wing) 0 | straight | yes | 464 | 12.4% | 464 | 12.4% |
| straight -x-y (x wing) 0 | straight | yes | 464 | 12.4% | 464 | 12.4% |
| corner -x-y | corner | **no** | 4 | 0.1% | 4 | 0.1% |
| straight +x-y (y wing) 0 | straight | yes | 464 | 12.4% | 464 | 12.4% |
| straight +x-y (x wing) 0 | straight | yes | 464 | 12.4% | 464 | 12.4% |
| corner +x-y | corner | **no** | 4 | 0.1% | 4 | 0.1% |
| **straight (8)** | | | 3712 | | 3712 | 99.6% |
| **corner (4)** | | | 16 | | 16 | 0.4% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 296 | 24.0 | 154.8 | 0.29 | 0.31 | 0.0% |
| -x | 293 | 24.0 | 152.3 | 0.29 | 0.32 | 0.0% |
| +y | 287 | 24.0 | 152.7 | 0.28 | 0.31 | 0.0% |
| -y | 292 | 24.0 | 153.6 | 0.29 | 0.32 | 0.0% |
| door +x+y y | 321 | 4.2 | 141.5 | 1.40 | 1.68 | 86.7% |
| door +x+y x | 316 | 4.2 | 141.5 | 1.37 | 1.68 | 86.7% |
| door -x+y y | 324 | 4.2 | 144.6 | 1.38 | 1.68 | 93.3% |
| door -x+y x | 321 | 4.2 | 141.3 | 1.40 | 1.74 | 80.0% |
| door -x-y y | 324 | 4.2 | 148.7 | 1.34 | 1.68 | 86.7% |
| door -x-y x | 318 | 4.2 | 141.3 | 1.39 | 1.68 | 80.0% |
| door +x-y y | 316 | 4.2 | 144.1 | 1.35 | 1.74 | 80.0% |
| door +x-y x | 320 | 4.2 | 140.5 | 1.40 | 1.62 | 93.3% |

Mean flow / w J averaged over the doors 1.38, over the avenues 0.29.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 464 | 321 / 143 / 33 | 0.7 | 138.9 | 3.59 | 4.21 | 86% | 86% | 0% | 3.83 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 464 | 316 / 148 / 26 | 0.7 | 138.9 | 3.54 | 4.31 | 86% | 86% | 0% | 3.66 |
| corner +x+y | 1.20 | 31.2 | 4 | 0 / 4 / 0 | 8.2 | 22.4 | 0.28 | 0.40 | 0% | 0% | 0% | nan |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 464 | 324 / 140 / 27 | 0.7 | 142.0 | 3.47 | 4.31 | 80% | 80% | 0% | 3.78 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 464 | 321 / 143 / 36 | 0.7 | 138.7 | 3.62 | 4.31 | 86% | 86% | 0% | 3.80 |
| corner -x+y | 1.20 | 31.2 | 4 | 0 / 4 / 0 | 8.2 | 22.4 | 0.28 | 0.40 | 0% | 0% | 0% | nan |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 464 | 324 / 141 / 30 | 0.7 | 145.9 | 3.41 | 4.21 | 80% | 80% | 0% | 3.83 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 464 | 318 / 146 / 36 | 0.7 | 138.7 | 3.62 | 4.61 | 86% | 86% | 0% | 3.74 |
| corner -x-y | 1.20 | 31.2 | 4 | 0 / 4 / 0 | 8.2 | 22.0 | 0.29 | 0.40 | 0% | 0% | 0% | nan |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 464 | 316 / 148 / 37 | 0.7 | 141.3 | 3.56 | 4.41 | 80% | 80% | 0% | 3.77 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 464 | 320 / 144 / 32 | 0.7 | 137.8 | 3.61 | 4.31 | 86% | 86% | 0% | 3.79 |
| corner +x-y | 1.20 | 31.2 | 4 | 0 / 4 / 0 | 8.2 | 22.4 | 0.28 | 0.40 | 0% | 0% | 0% | nan |

The last agent out (agent 557, t100 154.8 s): last gangway straight +x+y (x wing) 0, exit avenue +x. The gangway that cleared last: straight -x-y (y wing) 0 at 145.9 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.15 | 153.7 / 143.8 / 120.0 | 133.5 / 130.1 / 82.0 | 23566.0 | 119789 | 0.457 |
| gangway | 392 | 351.5 | 6.15 | 138.2 / 132.2 / 102.5 | 133.5 / 130.1 / 82.0 | 23350.4 | 89820 | 0.192 |
| walkway | 276 | 257.4 | 2.31 | 119.8 / 0.5 / 0.0 | 81.9 / 0.3 / 0.0 | 0.0 | 6778 | 1.161 |
| avenue | 408 | 384.3 | 1.69 | 127.5 / 0.0 / 0.0 | 116.5 / 0.0 / 0.0 | 0.0 | 15207 | 1.315 |
| exit | 40 | 9.7 | 0.00 | 150.4 / 140.3 / 94.8 | 121.9 / 90.3 / 15.0 | 215.5 | 1568 | 1.274 |
| concourse | 612 | 609.0 | 2.51 | 137.0 / 9.6 / 0.0 | 85.0 / 3.5 / 0.0 | 0.0 | 6417 | 1.195 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.56 | 126.8 / 124.9 / 119.8 | 126.8 / 124.9 / 117.4 | 45723.2 | 163285 | 0.099 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 18.5 | -10.5 | gangway | 0.94 | 6.01 | 129.1 | 127.3 | 82.0 | 416.3 | 0.071 |
| 2 | 10.5 | 18.5 | gangway | 0.94 | 5.74 | 125.2 | 122.4 | 77.8 | 385.7 | 0.080 |
| 3 | -10.5 | -18.5 | gangway | 0.94 | 5.77 | 124.2 | 120.3 | 77.7 | 385.4 | 0.077 |
| 4 | -10.5 | 18.5 | gangway | 0.94 | 5.68 | 128.0 | 124.0 | 75.7 | 372.6 | 0.079 |
| 5 | 10.5 | -18.5 | gangway | 0.94 | 5.59 | 126.6 | 123.7 | 75.0 | 370.6 | 0.081 |
| 6 | -18.5 | 10.5 | gangway | 0.94 | 5.73 | 128.2 | 122.3 | 72.9 | 368.1 | 0.075 |
| 7 | -18.5 | -10.5 | gangway | 0.94 | 5.69 | 125.4 | 119.5 | 72.4 | 361.0 | 0.078 |
| 8 | 18.5 | 10.5 | gangway | 0.94 | 5.72 | 125.1 | 120.7 | 72.4 | 361.0 | 0.075 |
| 9 | 19.5 | -10.5 | gangway | 0.96 | 5.76 | 128.2 | 122.8 | 66.1 | 347.1 | 0.074 |
| 10 | -18.5 | -11.5 | gangway | 0.86 | 6.07 | 111.2 | 106.3 | 72.4 | 346.3 | 0.069 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 18.5 | -9.5 | seat row | 0.50 | 7.36 | 126.8 | 124.9 | 117.4 | 402.5 | 0.043 |
| 2 | -9.5 | -18.5 | seat row | 0.50 | 7.53 | 122.4 | 120.9 | 115.1 | 399.6 | 0.044 |
| 3 | -9.5 | 18.5 | seat row | 0.50 | 7.43 | 123.7 | 122.1 | 114.6 | 398.5 | 0.044 |
| 4 | 9.5 | 18.5 | seat row | 0.50 | 7.46 | 124.0 | 122.4 | 116.3 | 398.3 | 0.044 |
| 5 | 9.5 | -18.5 | seat row | 0.50 | 7.44 | 125.9 | 124.7 | 113.5 | 393.9 | 0.044 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 257; agent-steps of seated agents on another row's clearway: 2265.

## Deposit check

Person-seconds deposited: 283076.9, of them in excluded cells: 2.837.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 13721 overlapping pair-steps: p99 0.0056, max 0.0106 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0056 max 0.0106; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 1 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 2.51 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 87 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
