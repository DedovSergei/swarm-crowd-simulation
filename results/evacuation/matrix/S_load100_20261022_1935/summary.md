# Experiment `S_load100`

**Task 5.10 stage 4 (AMD 26.10.1): venue S, 100% load, default model**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 3728 agents on 100% of the 3728 seats (spawnSeatedCrowd, seed 1337), buffer N = 4096, 1362 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 143456 evaluations, 3086 switches, 0 forced choices).
Capacity: **within design capacity** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T19:35:33, 11.4 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 657 | 114.9 |
| t90 | 1155 | 202.0 |
| t100 | 1362 | 238.2 |

t_p: the step by which ceil(p x 3728) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 350 | 0 | 24.5 | 232.1 | 17.9 | 24.5 | 49.3-59.3 |
| -x | 5.66 | 354 | 0 | 24.5 | 232.3 | 18.0 | 23.4 | 47.6-57.5 |
| +y | 5.66 | 350 | 0 | 24.5 | 230.9 | 18.0 | 23.4 | 49.1-59.1 |
| -y | 5.66 | 348 | 0 | 24.5 | 231.1 | 17.8 | 24.5 | 49.5-59.5 |
| door +x+y y | 1.20 | 291 | 466 | 4.9 | 229.7 | 64.7 | 85.3 | 25.4-35.3 |
| door +x+y x | 1.20 | 292 | 466 | 4.9 | 224.9 | 66.3 | 85.3 | 25.4-35.3 |
| door -x+y y | 1.20 | 291 | 466 | 4.9 | 237.9 | 62.4 | 85.3 | 25.4-35.3 |
| door -x+y x | 1.20 | 289 | 466 | 4.9 | 228.4 | 64.6 | 90.3 | 34.6-44.6 |
| door -x-y y | 1.20 | 291 | 466 | 4.9 | 238.2 | 62.3 | 85.3 | 27.6-37.6 |
| door -x-y x | 1.20 | 289 | 466 | 4.9 | 232.5 | 63.5 | 85.3 | 27.6-37.6 |
| door +x-y y | 1.20 | 293 | 466 | 4.9 | 237.5 | 62.9 | 90.3 | 27.8-37.8 |
| door +x-y x | 1.20 | 290 | 466 | 4.9 | 232.6 | 63.6 | 90.3 | 29.4-39.4 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 350 | 9.4% | 18.6% |
| -x | avenue | 5.66 | 354 | 9.5% | 18.8% |
| +y | avenue | 5.66 | 350 | 9.4% | 18.6% |
| -y | avenue | 5.66 | 348 | 9.3% | 18.5% |
| door +x+y y | door | 1.20 | 291 | 7.8% | 73.1% |
| door +x+y x | door | 1.20 | 292 | 7.8% | 73.3% |
| door -x+y y | door | 1.20 | 291 | 7.8% | 73.1% |
| door -x+y x | door | 1.20 | 289 | 7.8% | 72.6% |
| door -x-y y | door | 1.20 | 291 | 7.8% | 73.1% |
| door -x-y x | door | 1.20 | 289 | 7.8% | 72.6% |
| door +x-y y | door | 1.20 | 293 | 7.9% | 73.6% |
| door +x-y x | door | 1.20 | 290 | 7.8% | 72.8% |
| **doors (8)** | door | 9.60 | 2326 | 62.4% | |
| **avenues (4)** | avenue | 22.64 | 1402 | 37.6% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 238.2 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 34.8%.

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
| +x | 350 | 24.5 | 232.1 | 0.21 | 0.29 | 0.0% |
| -x | 354 | 24.5 | 232.3 | 0.22 | 0.28 | 0.0% |
| +y | 350 | 24.5 | 230.9 | 0.21 | 0.28 | 0.0% |
| -y | 348 | 24.5 | 231.1 | 0.21 | 0.29 | 0.0% |
| door +x+y y | 291 | 4.9 | 229.7 | 0.77 | 1.02 | 41.7% |
| door +x+y x | 292 | 4.9 | 224.9 | 0.79 | 1.02 | 47.8% |
| door -x+y y | 291 | 4.9 | 237.9 | 0.75 | 1.02 | 37.5% |
| door -x+y x | 289 | 4.9 | 228.4 | 0.77 | 1.08 | 34.8% |
| door -x-y y | 291 | 4.9 | 238.2 | 0.75 | 1.02 | 41.7% |
| door -x-y x | 289 | 4.9 | 232.5 | 0.76 | 1.02 | 33.3% |
| door +x-y y | 293 | 4.9 | 237.5 | 0.75 | 1.08 | 50.0% |
| door +x-y x | 290 | 4.9 | 232.6 | 0.76 | 1.08 | 29.2% |

Mean flow / w J averaged over the doors 0.76, over the avenues 0.21.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 464 | 291 / 173 / 39 | 0.7 | 226.7 | 2.22 | 2.81 | 83% | 83% | 0% | 3.78 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 464 | 292 / 172 / 33 | 0.7 | 222.0 | 2.24 | 2.81 | 83% | 83% | 0% | 3.74 |
| corner +x+y | 1.20 | 31.2 | 4 | 0 / 4 / 0 | 8.2 | 30.8 | 0.18 | 0.20 | 0% | 0% | 0% | nan |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 464 | 291 / 173 / 46 | 0.7 | 234.9 | 2.18 | 2.81 | 79% | 79% | 0% | 3.74 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 464 | 289 / 175 / 38 | 0.7 | 225.5 | 2.23 | 2.81 | 83% | 83% | 0% | 3.71 |
| corner -x+y | 1.20 | 31.2 | 4 | 0 / 4 / 0 | 8.2 | 30.8 | 0.18 | 0.20 | 0% | 0% | 0% | nan |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 464 | 291 / 173 / 55 | 0.7 | 235.2 | 2.21 | 3.01 | 79% | 79% | 0% | 3.77 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 464 | 289 / 175 / 46 | 0.7 | 229.5 | 2.23 | 3.01 | 79% | 79% | 0% | 3.67 |
| corner -x-y | 1.20 | 31.2 | 4 | 0 / 4 / 0 | 8.2 | 30.6 | 0.18 | 0.20 | 0% | 0% | 0% | nan |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 464 | 293 / 171 / 43 | 0.7 | 234.5 | 2.17 | 3.21 | 83% | 79% | 4% | 3.56 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 464 | 290 / 174 / 61 | 0.7 | 229.7 | 2.29 | 2.81 | 79% | 79% | 0% | 3.70 |
| corner +x-y | 1.20 | 31.2 | 4 | 0 / 4 / 0 | 8.2 | 30.8 | 0.18 | 0.20 | 0% | 0% | 0% | nan |

The last agent out (agent 2005, t100 238.2 s): last gangway straight -x-y (y wing) 0, exit door -x-y (y wall). The gangway that cleared last: straight -x-y (y wing) 0 at 235.2 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.45 | 233.7 / 225.6 / 187.5 | 211.5 / 202.7 / 134.2 | 41880.0 | 174528 | 0.337 |
| gangway | 392 | 351.5 | 6.45 | 220.6 / 208.3 / 159.7 | 211.5 / 202.7 / 134.2 | 41707.5 | 140813 | 0.115 |
| walkway | 276 | 257.4 | 1.87 | 33.8 / 0.0 / 0.0 | 4.5 / 0.0 / 0.0 | 0.0 | 7761 | 1.244 |
| avenue | 408 | 384.3 | 1.48 | 57.0 / 0.0 / 0.0 | 17.5 / 0.0 / 0.0 | 0.0 | 18227 | 1.319 |
| exit | 40 | 9.7 | 0.00 | 223.4 / 212.9 / 100.6 | 120.5 / 79.8 / 12.4 | 172.5 | 1603 | 1.324 |
| concourse | 612 | 609.0 | 1.68 | 174.6 / 0.0 / 0.0 | 34.5 / 0.0 / 0.0 | 0.0 | 6124 | 1.119 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.56 | 197.1 / 195.4 / 181.0 | 197.1 / 195.2 / 178.4 | 81258.6 | 257217 | 0.064 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 19.5 | 11.5 | gangway | 0.92 | 5.68 | 189.2 | 178.6 | 134.2 | 662.9 | 0.029 |
| 2 | 11.5 | 22.5 | gangway | 0.86 | 6.20 | 199.7 | 186.8 | 127.9 | 625.1 | 0.063 |
| 3 | 11.5 | 19.5 | gangway | 0.92 | 5.75 | 178.2 | 173.3 | 125.2 | 604.1 | 0.033 |
| 4 | 18.5 | 11.5 | gangway | 0.86 | 6.38 | 188.9 | 180.2 | 121.9 | 597.2 | 0.044 |
| 5 | 11.5 | -19.5 | gangway | 0.92 | 5.69 | 182.4 | 177.2 | 122.3 | 596.1 | 0.031 |
| 6 | -19.5 | 11.5 | gangway | 0.92 | 5.90 | 181.4 | 177.4 | 115.6 | 572.0 | 0.031 |
| 7 | -19.5 | 10.5 | gangway | 0.96 | 5.69 | 200.8 | 185.2 | 109.1 | 564.6 | 0.033 |
| 8 | 18.5 | -11.5 | gangway | 0.86 | 6.45 | 183.1 | 176.5 | 112.5 | 555.2 | 0.044 |
| 9 | 10.5 | 18.5 | gangway | 0.94 | 5.87 | 196.8 | 189.9 | 108.3 | 553.2 | 0.048 |
| 10 | -22.5 | 11.5 | gangway | 0.86 | 6.03 | 200.8 | 181.6 | 114.6 | 548.6 | 0.065 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 9.5 | -18.5 | seat row | 0.50 | 7.40 | 194.0 | 191.5 | 178.4 | 613.8 | 0.029 |
| 2 | -18.5 | 9.5 | seat row | 0.50 | 7.56 | 189.6 | 186.6 | 174.6 | 608.2 | 0.029 |
| 3 | 9.5 | 18.5 | seat row | 0.50 | 7.52 | 188.5 | 185.4 | 172.3 | 598.3 | 0.030 |
| 4 | 18.5 | 9.5 | seat row | 0.50 | 7.47 | 190.6 | 183.1 | 168.3 | 583.8 | 0.030 |
| 5 | -18.5 | -9.5 | seat row | 0.50 | 7.32 | 191.0 | 181.0 | 168.1 | 582.5 | 0.030 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 361; agent-steps of seated agents on another row's clearway: 2362.

## Deposit check

Person-seconds deposited: 431749.5, of them in excluded cells: 4.199.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 49610 overlapping pair-steps: p99 0.0045, max 0.0099 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0045 max 0.0099; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 4 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 1.87 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 76 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
