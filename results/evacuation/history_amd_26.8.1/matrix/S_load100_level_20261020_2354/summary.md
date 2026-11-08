# Experiment `S_load100_level`

**Task 5.9 stage 4 (model variants): venue S, 100% load, queue-aware exit choice, level walking speed**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 3728 agents on 100% of the 3728 seats (spawnSeatedCrowd, seed 1337), buffer N = 4096, 884 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, level speed** (exit choice: 92258 evaluations, 3028 switches, 0 forced choices).
Capacity: **within design capacity** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-20T23:54:46, 14.0 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 430 | 75.2 |
| t90 | 730 | 127.7 |
| t100 | 884 | 154.6 |

t_p: the step by which ceil(p x 3728) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 290 | 0 | 24.0 | 152.7 | 23.8 | 26.6 | 42.5-52.5 |
| -x | 5.66 | 290 | 0 | 24.0 | 150.2 | 24.3 | 26.6 | 42.2-52.1 |
| +y | 5.66 | 286 | 0 | 24.0 | 150.2 | 24.0 | 25.5 | 35.9-45.8 |
| -y | 5.66 | 290 | 0 | 24.0 | 154.6 | 23.5 | 26.6 | 37.8-47.7 |
| door +x+y y | 1.20 | 323 | 466 | 4.2 | 141.8 | 117.2 | 140.4 | 9.6-19.6 |
| door +x+y x | 1.20 | 318 | 466 | 4.2 | 145.2 | 112.6 | 140.4 | 9.4-19.4 |
| door -x+y y | 1.20 | 323 | 466 | 4.2 | 146.0 | 113.7 | 145.4 | 12.6-22.6 |
| door -x+y x | 1.20 | 325 | 466 | 4.2 | 142.0 | 117.8 | 145.4 | 32.4-42.3 |
| door -x-y y | 1.20 | 323 | 466 | 4.2 | 143.9 | 115.4 | 140.4 | 36.6-46.5 |
| door -x-y x | 1.20 | 317 | 466 | 4.2 | 146.0 | 111.6 | 140.4 | 28.9-38.8 |
| door +x-y y | 1.20 | 319 | 466 | 4.2 | 141.1 | 116.3 | 140.4 | 11.4-21.3 |
| door +x-y x | 1.20 | 324 | 466 | 4.2 | 144.6 | 115.2 | 140.4 | 10.3-20.3 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 290 | 7.8% | 23.8% |
| -x | avenue | 5.66 | 290 | 7.8% | 23.8% |
| +y | avenue | 5.66 | 286 | 7.7% | 23.5% |
| -y | avenue | 5.66 | 290 | 7.8% | 23.8% |
| door +x+y y | door | 1.20 | 323 | 8.7% | 124.9% |
| door +x+y x | door | 1.20 | 318 | 8.5% | 123.0% |
| door -x+y y | door | 1.20 | 323 | 8.7% | 124.9% |
| door -x+y x | door | 1.20 | 325 | 8.7% | 125.7% |
| door -x-y y | door | 1.20 | 323 | 8.7% | 124.9% |
| door -x-y x | door | 1.20 | 317 | 8.5% | 122.6% |
| door +x-y y | door | 1.20 | 319 | 8.6% | 123.4% |
| door +x-y x | door | 1.20 | 324 | 8.7% | 125.3% |
| **doors (8)** | door | 9.60 | 2572 | 69.0% | |
| **avenues (4)** | avenue | 22.64 | 1156 | 31.0% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 154.6 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 53.7%.

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
| +x | 290 | 24.0 | 152.7 | 0.29 | 0.32 | 0.0% |
| -x | 290 | 24.0 | 150.2 | 0.29 | 0.32 | 0.0% |
| +y | 286 | 24.0 | 150.2 | 0.29 | 0.31 | 0.0% |
| -y | 290 | 24.0 | 154.6 | 0.28 | 0.32 | 0.0% |
| door +x+y y | 323 | 4.2 | 141.8 | 1.40 | 1.68 | 86.7% |
| door +x+y x | 318 | 4.2 | 145.2 | 1.35 | 1.68 | 86.7% |
| door -x+y y | 323 | 4.2 | 146.0 | 1.36 | 1.74 | 86.7% |
| door -x+y x | 325 | 4.2 | 142.0 | 1.41 | 1.74 | 86.7% |
| door -x-y y | 323 | 4.2 | 143.9 | 1.38 | 1.68 | 93.3% |
| door -x-y x | 317 | 4.2 | 146.0 | 1.33 | 1.68 | 86.7% |
| door +x-y y | 319 | 4.2 | 141.1 | 1.39 | 1.68 | 86.7% |
| door +x-y x | 324 | 4.2 | 144.6 | 1.38 | 1.68 | 93.3% |

Mean flow / w J averaged over the doors 1.38, over the avenues 0.29.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 464 | 323 / 141 / 34 | 0.7 | 139.1 | 3.59 | 4.11 | 86% | 86% | 0% | 3.77 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 464 | 318 / 147 / 32 | 0.7 | 142.5 | 3.50 | 4.31 | 80% | 80% | 0% | 3.66 |
| corner +x+y | 1.20 | 31.2 | 4 | 0 / 4 / 0 | 8.2 | 22.4 | 0.28 | 0.40 | 0% | 0% | 0% | nan |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 464 | 323 / 142 / 36 | 0.7 | 143.4 | 3.51 | 4.61 | 80% | 80% | 0% | 3.77 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 464 | 325 / 139 / 30 | 0.7 | 139.4 | 3.56 | 4.81 | 86% | 86% | 0% | 3.66 |
| corner -x+y | 1.20 | 31.2 | 4 | 0 / 4 / 0 | 8.2 | 22.4 | 0.28 | 0.40 | 0% | 0% | 0% | nan |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 464 | 323 / 141 / 33 | 0.7 | 141.3 | 3.53 | 4.41 | 80% | 80% | 0% | 3.89 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 464 | 317 / 147 / 34 | 0.7 | 143.2 | 3.49 | 4.51 | 80% | 80% | 0% | 3.72 |
| corner -x-y | 1.20 | 31.2 | 4 | 0 / 4 / 0 | 8.2 | 22.0 | 0.29 | 0.40 | 0% | 0% | 0% | nan |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 464 | 319 / 145 / 39 | 0.7 | 138.5 | 3.64 | 4.31 | 86% | 86% | 0% | 3.70 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 464 | 324 / 140 / 26 | 0.7 | 142.0 | 3.46 | 3.91 | 80% | 80% | 0% | 3.74 |
| corner +x-y | 1.20 | 31.2 | 4 | 0 / 4 / 0 | 8.2 | 22.4 | 0.28 | 0.40 | 0% | 0% | 0% | nan |

The last agent out (agent 1983, t100 154.6 s): last gangway straight -x-y (y wing) 0, exit avenue -y. The gangway that cleared last: straight -x+y (y wing) 0 at 143.4 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.38 | 151.8 / 142.7 / 124.0 | 131.9 / 130.3 / 89.0 | 24139.8 | 118498 | 0.460 |
| gangway | 392 | 351.5 | 6.38 | 135.4 / 131.2 / 106.5 | 131.9 / 130.3 / 89.0 | 23911.9 | 88798 | 0.194 |
| walkway | 276 | 257.4 | 2.03 | 117.4 / 0.0 / 0.0 | 57.9 / 0.0 / 0.0 | 0.0 | 6587 | 1.183 |
| avenue | 408 | 384.3 | 1.51 | 123.5 / 0.0 / 0.0 | 114.6 / 0.0 / 0.0 | 0.0 | 15049 | 1.315 |
| exit | 40 | 9.7 | 0.00 | 148.7 / 139.6 / 101.3 | 121.9 / 92.2 / 15.9 | 227.9 | 1566 | 1.268 |
| concourse | 612 | 609.0 | 2.66 | 133.1 / 17.5 / 0.0 | 85.0 / 7.5 / 0.0 | 0.0 | 6497 | 1.186 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.47 | 125.9 / 124.7 / 119.5 | 125.9 / 124.7 / 117.5 | 46516.5 | 161044 | 0.100 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 10.5 | -18.5 | gangway | 0.94 | 5.63 | 122.1 | 117.4 | 89.0 | 442.7 | 0.076 |
| 2 | -10.5 | -18.5 | gangway | 0.94 | 5.79 | 128.0 | 123.3 | 82.0 | 410.9 | 0.073 |
| 3 | -10.5 | 19.5 | gangway | 0.96 | 5.96 | 127.7 | 118.6 | 77.3 | 400.0 | 0.074 |
| 4 | -18.5 | -10.5 | gangway | 0.94 | 5.84 | 124.4 | 117.4 | 78.4 | 398.0 | 0.077 |
| 5 | -10.5 | 18.5 | gangway | 0.94 | 5.80 | 127.3 | 122.3 | 78.9 | 396.0 | 0.075 |
| 6 | 11.5 | 18.5 | gangway | 0.86 | 6.00 | 114.9 | 109.8 | 83.3 | 395.7 | 0.070 |
| 7 | 10.5 | 18.5 | gangway | 0.94 | 5.69 | 125.2 | 123.3 | 78.5 | 392.8 | 0.076 |
| 8 | -19.5 | -10.5 | gangway | 0.96 | 5.80 | 125.8 | 123.0 | 75.4 | 391.3 | 0.069 |
| 9 | -10.5 | -19.5 | gangway | 0.96 | 5.69 | 125.1 | 117.9 | 75.4 | 385.0 | 0.075 |
| 10 | -11.5 | -18.5 | gangway | 0.86 | 5.95 | 117.2 | 113.9 | 81.3 | 380.9 | 0.073 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -9.5 | 18.5 | seat row | 0.50 | 7.47 | 125.8 | 123.8 | 117.5 | 404.5 | 0.044 |
| 2 | -9.5 | -18.5 | seat row | 0.50 | 7.43 | 125.9 | 124.7 | 115.3 | 395.6 | 0.044 |
| 3 | -18.5 | -9.5 | seat row | 0.50 | 7.40 | 121.0 | 120.3 | 115.8 | 392.5 | 0.046 |
| 4 | 18.5 | -9.5 | seat row | 0.50 | 7.37 | 125.1 | 123.7 | 114.6 | 389.7 | 0.045 |
| 5 | -18.5 | 9.5 | seat row | 0.50 | 7.26 | 123.3 | 122.6 | 112.3 | 386.2 | 0.045 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 261; agent-steps of seated agents on another row's clearway: 2248.

## Deposit check

Person-seconds deposited: 279544.5, of them in excluded cells: 2.529.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 9253 overlapping pair-steps: p99 0.0083, max 0.0330 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0083 max 0.0330; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 2 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 2.66 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 89 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
