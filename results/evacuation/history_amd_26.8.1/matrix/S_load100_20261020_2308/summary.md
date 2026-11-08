# Experiment `S_load100`

**Task 5.9 stage 4: venue S, 100% load, default model**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 3728 agents on 100% of the 3728 seats (spawnSeatedCrowd, seed 1337), buffer N = 4096, 1351 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 142412 evaluations, 3061 switches, 0 forced choices).
Capacity: **within design capacity** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-20T23:08:19, 10.7 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 653 | 114.2 |
| t90 | 1150 | 201.1 |
| t100 | 1351 | 236.3 |

t_p: the step by which ceil(p x 3728) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 344 | 0 | 24.5 | 229.1 | 17.8 | 25.5 | 49.5-59.5 |
| -x | 5.66 | 349 | 0 | 24.5 | 232.3 | 17.8 | 23.4 | 45.7-55.6 |
| +y | 5.66 | 345 | 0 | 24.5 | 229.3 | 17.8 | 23.4 | 47.0-57.0 |
| -y | 5.66 | 349 | 0 | 24.5 | 231.4 | 17.9 | 23.4 | 45.3-55.3 |
| door +x+y y | 1.20 | 294 | 466 | 4.9 | 231.1 | 64.9 | 90.3 | 24.8-34.8 |
| door +x+y x | 1.20 | 297 | 466 | 4.9 | 228.6 | 66.3 | 90.3 | 22.6-32.5 |
| door -x+y y | 1.20 | 293 | 466 | 4.9 | 229.1 | 65.3 | 85.3 | 40.6-50.5 |
| door -x+y x | 1.20 | 291 | 466 | 4.9 | 235.4 | 63.1 | 90.3 | 19.2-29.2 |
| door -x-y y | 1.20 | 289 | 466 | 4.9 | 227.0 | 65.0 | 90.3 | 19.1-29.0 |
| door -x-y x | 1.20 | 292 | 466 | 4.9 | 236.3 | 63.0 | 90.3 | 18.0-28.0 |
| door +x-y y | 1.20 | 294 | 466 | 4.9 | 229.5 | 65.4 | 90.3 | 19.2-29.2 |
| door +x-y x | 1.20 | 291 | 466 | 4.9 | 226.5 | 65.6 | 85.3 | 24.3-34.3 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 344 | 9.2% | 18.5% |
| -x | avenue | 5.66 | 349 | 9.4% | 18.7% |
| +y | avenue | 5.66 | 345 | 9.3% | 18.5% |
| -y | avenue | 5.66 | 349 | 9.4% | 18.7% |
| door +x+y y | door | 1.20 | 294 | 7.9% | 74.4% |
| door +x+y x | door | 1.20 | 297 | 8.0% | 75.2% |
| door -x+y y | door | 1.20 | 293 | 7.9% | 74.2% |
| door -x+y x | door | 1.20 | 291 | 7.8% | 73.7% |
| door -x-y y | door | 1.20 | 289 | 7.8% | 73.1% |
| door -x-y x | door | 1.20 | 292 | 7.8% | 73.9% |
| door +x-y y | door | 1.20 | 294 | 7.9% | 74.4% |
| door +x-y x | door | 1.20 | 291 | 7.8% | 73.7% |
| **doors (8)** | door | 9.60 | 2341 | 62.8% | |
| **avenues (4)** | avenue | 22.64 | 1387 | 37.2% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 236.3 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 35.1%.

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
| +x | 344 | 24.5 | 229.1 | 0.21 | 0.31 | 0.0% |
| -x | 349 | 24.5 | 232.3 | 0.21 | 0.28 | 0.0% |
| +y | 345 | 24.5 | 229.3 | 0.21 | 0.28 | 0.0% |
| -y | 349 | 24.5 | 231.4 | 0.21 | 0.28 | 0.0% |
| door +x+y y | 294 | 4.9 | 231.1 | 0.78 | 1.08 | 37.5% |
| door +x+y x | 297 | 4.9 | 228.6 | 0.79 | 1.08 | 52.2% |
| door -x+y y | 293 | 4.9 | 229.1 | 0.78 | 1.02 | 52.2% |
| door -x+y x | 291 | 4.9 | 235.4 | 0.75 | 1.08 | 50.0% |
| door -x-y y | 289 | 4.9 | 227.0 | 0.78 | 1.08 | 39.1% |
| door -x-y x | 292 | 4.9 | 236.3 | 0.75 | 1.08 | 41.7% |
| door +x-y y | 294 | 4.9 | 229.5 | 0.78 | 1.08 | 45.8% |
| door +x-y x | 291 | 4.9 | 226.5 | 0.78 | 1.02 | 47.8% |

Mean flow / w J averaged over the doors 0.78, over the avenues 0.21.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 464 | 294 / 170 / 45 | 0.7 | 228.1 | 2.24 | 2.91 | 83% | 83% | 0% | 3.74 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 464 | 297 / 167 / 36 | 0.7 | 225.6 | 2.22 | 2.71 | 83% | 83% | 0% | 3.65 |
| corner +x+y | 1.20 | 31.2 | 4 | 0 / 4 / 0 | 8.2 | 30.8 | 0.18 | 0.20 | 0% | 0% | 0% | nan |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 464 | 293 / 171 / 52 | 0.7 | 226.2 | 2.29 | 2.91 | 83% | 83% | 0% | 3.66 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 464 | 291 / 173 / 54 | 0.7 | 232.5 | 2.23 | 3.11 | 79% | 79% | 0% | 3.71 |
| corner -x+y | 1.20 | 31.2 | 4 | 0 / 4 / 0 | 8.2 | 30.8 | 0.18 | 0.20 | 0% | 0% | 0% | nan |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 464 | 289 / 175 / 45 | 0.7 | 224.1 | 2.28 | 3.01 | 87% | 83% | 4% | 3.60 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 464 | 292 / 172 / 41 | 0.7 | 233.5 | 2.17 | 2.81 | 83% | 79% | 4% | 3.68 |
| corner -x-y | 1.20 | 31.2 | 4 | 0 / 4 / 0 | 8.2 | 30.6 | 0.18 | 0.20 | 0% | 0% | 0% | nan |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 464 | 294 / 170 / 36 | 0.7 | 226.5 | 2.21 | 2.71 | 83% | 83% | 0% | 3.75 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 464 | 291 / 173 / 44 | 0.7 | 223.5 | 2.28 | 2.91 | 83% | 83% | 0% | 3.74 |
| corner +x-y | 1.20 | 31.2 | 4 | 0 / 4 / 0 | 8.2 | 30.8 | 0.18 | 0.20 | 0% | 0% | 0% | nan |

The last agent out (agent 2471, t100 236.3 s): last gangway straight -x-y (x wing) 0, exit door -x-y (x wall). The gangway that cleared last: straight -x-y (x wing) 0 at 233.5 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.44 | 231.9 / 224.4 / 181.7 | 210.8 / 204.6 / 132.2 | 40082.5 | 173580 | 0.337 |
| gangway | 392 | 351.5 | 6.44 | 219.5 / 207.6 / 151.5 | 210.8 / 204.6 / 132.2 | 39910.8 | 140084 | 0.115 |
| walkway | 276 | 257.4 | 1.80 | 25.9 / 0.0 / 0.0 | 5.1 / 0.0 / 0.0 | 0.0 | 7680 | 1.244 |
| avenue | 408 | 384.3 | 1.46 | 51.6 / 0.0 / 0.0 | 19.4 / 0.0 / 0.0 | 0.0 | 18031 | 1.319 |
| exit | 40 | 9.7 | 0.00 | 220.6 / 210.1 / 101.1 | 123.3 / 79.9 / 14.3 | 171.7 | 1605 | 1.321 |
| concourse | 612 | 609.0 | 1.66 | 172.3 / 0.0 / 0.0 | 36.0 / 0.0 / 0.0 | 0.0 | 6179 | 1.116 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.56 | 197.5 / 193.8 / 179.5 | 197.5 / 193.6 / 176.8 | 79185.9 | 255022 | 0.064 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -19.5 | 11.5 | gangway | 0.92 | 5.78 | 182.6 | 175.4 | 132.2 | 650.4 | 0.031 |
| 2 | -19.5 | -11.5 | gangway | 0.92 | 5.73 | 187.8 | 181.7 | 124.4 | 616.4 | 0.029 |
| 3 | 11.5 | -19.5 | gangway | 0.92 | 5.68 | 184.9 | 179.1 | 123.5 | 605.1 | 0.030 |
| 4 | 19.5 | 11.5 | gangway | 0.92 | 5.94 | 193.4 | 190.1 | 119.3 | 599.4 | 0.029 |
| 5 | -11.5 | -22.5 | gangway | 0.86 | 5.91 | 203.2 | 184.5 | 123.8 | 586.5 | 0.065 |
| 6 | 10.5 | 19.5 | gangway | 0.96 | 5.62 | 199.0 | 188.9 | 111.1 | 580.8 | 0.033 |
| 7 | -22.5 | -11.5 | gangway | 0.86 | 5.99 | 204.3 | 184.5 | 120.2 | 574.9 | 0.065 |
| 8 | -19.5 | -10.5 | gangway | 0.96 | 5.60 | 202.2 | 196.8 | 108.4 | 553.6 | 0.032 |
| 9 | -22.5 | 11.5 | gangway | 0.86 | 6.01 | 201.0 | 179.6 | 117.4 | 548.0 | 0.070 |
| 10 | 11.5 | -22.5 | gangway | 0.86 | 5.92 | 203.2 | 183.1 | 115.3 | 546.3 | 0.069 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 18.5 | 9.5 | seat row | 0.50 | 7.38 | 189.6 | 185.4 | 176.8 | 611.5 | 0.029 |
| 2 | -9.5 | 18.5 | seat row | 0.50 | 7.54 | 190.3 | 185.8 | 174.2 | 605.5 | 0.029 |
| 3 | 9.5 | -18.5 | seat row | 0.50 | 7.41 | 192.2 | 187.2 | 172.8 | 600.1 | 0.029 |
| 4 | 9.5 | 18.5 | seat row | 0.50 | 7.55 | 186.6 | 183.8 | 171.6 | 598.7 | 0.030 |
| 5 | 18.5 | -9.5 | seat row | 0.50 | 7.55 | 184.7 | 181.9 | 170.4 | 589.7 | 0.030 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 353; agent-steps of seated agents on another row's clearway: 2402.

## Deposit check

Person-seconds deposited: 428606.1, of them in excluded cells: 4.121.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 42647 overlapping pair-steps: p99 0.0035, max 0.0090 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0035 max 0.0090; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00764 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 0 (longest 0 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 1.80 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 83 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
