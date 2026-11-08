# Experiment `S_load95_s1`

**Task 5.8 stage 2: venue S, 95% load (seed 1), default model**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 3542 agents on 95% of the 3728 seats (spawnSeatedCrowd, seed 1), buffer N = 4096, 1048 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 102571 evaluations, 2812 switches, 0 forced choices).
Capacity: **within design capacity** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `cd8e0bbf3411846ca7aa6719887d122a142a7ca1`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-15T16:19:59, 8.7 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 499 | 87.3 |
| t90 | 852 | 149.0 |
| t100 | 1048 | 183.3 |

t_p: the step by which ceil(p x 3542) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 318 | 0 | 24.0 | 174.4 | 22.4 | 24.5 | 57.2-67.2 |
| -x | 5.66 | 318 | 0 | 24.0 | 175.6 | 22.2 | 25.5 | 93.6-103.5 |
| +y | 5.66 | 317 | 0 | 24.0 | 173.9 | 22.4 | 25.5 | 46.0-56.0 |
| -y | 5.66 | 315 | 0 | 24.0 | 172.8 | 22.4 | 25.5 | 45.3-55.3 |
| door +x+y y | 1.20 | 287 | 445 | 4.9 | 182.1 | 80.9 | 110.3 | 15.4-25.4 |
| door +x+y x | 1.20 | 281 | 440 | 4.9 | 174.7 | 82.6 | 105.3 | 11.0-21.0 |
| door -x+y y | 1.20 | 287 | 445 | 4.9 | 183.3 | 80.4 | 110.3 | 26.4-36.4 |
| door -x+y x | 1.20 | 279 | 436 | 4.9 | 174.9 | 82.0 | 110.3 | 27.6-37.6 |
| door -x-y y | 1.20 | 285 | 439 | 4.9 | 171.6 | 85.4 | 110.3 | 16.3-26.2 |
| door -x-y x | 1.20 | 285 | 445 | 4.9 | 176.8 | 82.8 | 110.3 | 39.7-49.7 |
| door +x-y y | 1.20 | 281 | 442 | 4.9 | 179.8 | 80.2 | 105.3 | 8.6-18.5 |
| door +x-y x | 1.20 | 289 | 450 | 4.9 | 181.6 | 81.7 | 105.3 | 13.1-23.1 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 318 | 9.0% | 22.0% |
| -x | avenue | 5.66 | 318 | 9.0% | 22.0% |
| +y | avenue | 5.66 | 317 | 8.9% | 21.9% |
| -y | avenue | 5.66 | 315 | 8.9% | 21.8% |
| door +x+y y | door | 1.20 | 287 | 8.1% | 93.6% |
| door +x+y x | door | 1.20 | 281 | 7.9% | 91.7% |
| door -x+y y | door | 1.20 | 287 | 8.1% | 93.6% |
| door -x+y x | door | 1.20 | 279 | 7.9% | 91.0% |
| door -x-y y | door | 1.20 | 285 | 8.0% | 93.0% |
| door -x-y x | door | 1.20 | 285 | 8.0% | 93.0% |
| door +x-y y | door | 1.20 | 281 | 7.9% | 91.7% |
| door +x-y x | door | 1.20 | 289 | 8.2% | 94.3% |
| **doors (8)** | door | 9.60 | 2274 | 64.2% | |
| **avenues (4)** | avenue | 22.64 | 1268 | 35.8% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 183.3 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 43.0%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 444 | 12.5% | 444 | 12.5% |
| straight +x+y (x wing) 0 | straight | yes | 439 | 12.4% | 439 | 12.4% |
| corner +x+y | corner | **no** | 2 | 0.1% | 2 | 0.1% |
| straight -x+y (y wing) 0 | straight | yes | 444 | 12.5% | 444 | 12.5% |
| straight -x+y (x wing) 0 | straight | yes | 435 | 12.3% | 435 | 12.3% |
| corner -x+y | corner | **no** | 2 | 0.1% | 2 | 0.1% |
| straight -x-y (y wing) 0 | straight | yes | 438 | 12.4% | 438 | 12.4% |
| straight -x-y (x wing) 0 | straight | yes | 445 | 12.6% | 445 | 12.6% |
| corner -x-y | corner | **no** | 1 | 0.0% | 1 | 0.0% |
| straight +x-y (y wing) 0 | straight | yes | 440 | 12.4% | 440 | 12.4% |
| straight +x-y (x wing) 0 | straight | yes | 449 | 12.7% | 449 | 12.7% |
| corner +x-y | corner | **no** | 3 | 0.1% | 3 | 0.1% |
| **straight (8)** | | | 3534 | | 3534 | 99.8% |
| **corner (4)** | | | 8 | | 8 | 0.2% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 318 | 24.0 | 174.4 | 0.27 | 0.29 | 0.0% |
| -x | 318 | 24.0 | 175.6 | 0.27 | 0.31 | 0.0% |
| +y | 317 | 24.0 | 173.9 | 0.27 | 0.31 | 0.0% |
| -y | 315 | 24.0 | 172.8 | 0.27 | 0.31 | 0.0% |
| door +x+y y | 287 | 4.9 | 182.1 | 0.97 | 1.32 | 73.7% |
| door +x+y x | 281 | 4.9 | 174.7 | 0.99 | 1.26 | 77.8% |
| door -x+y y | 287 | 4.9 | 183.3 | 0.96 | 1.32 | 73.7% |
| door -x+y x | 279 | 4.9 | 174.9 | 0.98 | 1.32 | 77.8% |
| door -x-y y | 285 | 4.9 | 171.6 | 1.02 | 1.32 | 77.8% |
| door -x-y x | 285 | 4.9 | 176.8 | 0.99 | 1.32 | 83.3% |
| door +x-y y | 281 | 4.9 | 179.8 | 0.96 | 1.26 | 73.7% |
| door +x-y x | 289 | 4.9 | 181.6 | 0.98 | 1.26 | 78.9% |

Mean flow / w J averaged over the doors 0.98, over the avenues 0.27.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 444 | 287 / 158 / 41 | 0.7 | 179.1 | 2.72 | 3.61 | 78% | 78% | 0% | 3.94 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 439 | 281 / 158 / 44 | 0.7 | 171.8 | 2.82 | 4.11 | 72% | 72% | 0% | 4.02 |
| corner +x+y | 1.20 | 31.2 | 2 | 0 / 2 / 0 | 8.2 | 30.6 | 0.09 | 0.10 | 0% | 0% | 0% | nan |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 444 | 287 / 158 / 45 | 0.7 | 180.3 | 2.73 | 3.51 | 68% | 68% | 0% | 4.07 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 435 | 279 / 156 / 32 | 0.7 | 171.9 | 2.72 | 3.41 | 72% | 72% | 0% | 4.01 |
| corner -x+y | 1.20 | 31.2 | 2 | 0 / 2 / 0 | 8.2 | 30.6 | 0.09 | 0.10 | 0% | 0% | 0% | nan |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 438 | 285 / 153 / 25 | 0.7 | 168.6 | 2.75 | 3.41 | 76% | 76% | 0% | 4.04 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 445 | 285 / 160 / 46 | 0.7 | 173.9 | 2.83 | 3.61 | 78% | 78% | 0% | 4.00 |
| corner -x-y | 1.20 | 31.2 | 1 | 0 / 1 / 0 | 8.2 | 30.6 | 0.04 | 0.10 | 0% | 0% | 0% | nan |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 440 | 281 / 159 / 44 | 0.7 | 176.8 | 2.75 | 3.81 | 78% | 78% | 0% | 4.02 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 449 | 289 / 160 / 32 | 0.7 | 178.6 | 2.70 | 3.41 | 78% | 78% | 0% | 4.00 |
| corner +x-y | 1.20 | 31.2 | 3 | 0 / 3 / 0 | 8.2 | 31.7 | 0.13 | 0.20 | 0% | 0% | 0% | nan |

The last agent out (agent 1049, t100 183.3 s): last gangway straight -x+y (y wing) 0, exit door -x+y (y wall). The gangway that cleared last: straight -x+y (y wing) 0 at 180.3 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.22 | 181.6 / 172.8 / 142.2 | 157.9 / 151.5 / 95.0 | 25349.0 | 139290 | 0.394 |
| gangway | 392 | 351.5 | 6.22 | 178.9 / 153.0 / 123.1 | 157.9 / 151.5 / 95.0 | 25163.9 | 108244 | 0.147 |
| walkway | 276 | 257.4 | 2.11 | 79.4 / 0.0 / 0.0 | 17.8 / 0.0 / 0.0 | 0.0 | 6938 | 1.227 |
| avenue | 408 | 384.3 | 1.43 | 134.3 / 0.0 / 0.0 | 54.0 / 0.0 / 0.0 | 0.0 | 16490 | 1.318 |
| exit | 40 | 9.7 | 0.00 | 176.1 / 169.1 / 101.6 | 118.9 / 82.4 / 12.9 | 185.2 | 1549 | 1.293 |
| concourse | 612 | 609.0 | 2.03 | 156.9 / 0.0 / 0.0 | 89.6 / 0.0 / 0.0 | 0.0 | 6069 | 1.106 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.53 | 140.6 / 138.2 / 130.8 | 140.6 / 138.2 / 128.2 | 49376.5 | 170608 | 0.092 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -10.5 | -18.5 | gangway | 0.94 | 5.86 | 138.7 | 130.7 | 95.0 | 472.4 | 0.068 |
| 2 | 11.5 | -22.5 | gangway | 0.86 | 6.09 | 146.0 | 142.5 | 93.2 | 441.8 | 0.086 |
| 3 | 19.5 | -11.5 | gangway | 0.92 | 5.83 | 131.5 | 125.1 | 89.7 | 434.7 | 0.051 |
| 4 | -18.5 | 10.5 | gangway | 0.94 | 5.98 | 137.1 | 129.6 | 84.1 | 426.2 | 0.072 |
| 5 | -22.5 | -11.5 | gangway | 0.86 | 5.90 | 142.2 | 139.6 | 89.7 | 422.1 | 0.091 |
| 6 | -18.5 | -10.5 | gangway | 0.94 | 5.93 | 141.5 | 137.8 | 82.0 | 418.1 | 0.064 |
| 7 | 22.5 | -11.5 | gangway | 0.86 | 6.04 | 143.8 | 134.9 | 88.0 | 415.1 | 0.092 |
| 8 | 10.5 | -18.5 | gangway | 0.94 | 5.80 | 143.8 | 133.3 | 83.1 | 415.1 | 0.073 |
| 9 | -10.5 | 19.5 | gangway | 0.96 | 5.70 | 145.5 | 137.3 | 79.6 | 412.5 | 0.058 |
| 10 | 10.5 | -19.5 | gangway | 0.96 | 5.70 | 140.6 | 124.5 | 77.5 | 396.6 | 0.060 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 18.5 | -9.5 | seat row | 0.50 | 7.46 | 138.0 | 136.1 | 128.2 | 439.8 | 0.041 |
| 2 | -9.5 | 18.5 | seat row | 0.50 | 7.46 | 136.3 | 135.4 | 127.2 | 438.7 | 0.038 |
| 3 | 18.5 | 9.5 | seat row | 0.50 | 7.53 | 133.3 | 132.2 | 127.0 | 434.7 | 0.040 |
| 4 | -18.5 | -9.5 | seat row | 0.50 | 7.41 | 138.0 | 134.9 | 125.9 | 434.2 | 0.037 |
| 5 | -9.5 | -18.5 | seat row | 0.50 | 7.37 | 133.3 | 132.4 | 126.1 | 431.7 | 0.041 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 308; agent-steps of seated agents on another row's clearway: 2854.

## Deposit check

Person-seconds deposited: 309902.0, of them in excluded cells: 3.713.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 17709 overlapping pair-steps: p99 0.0049, max 0.0084 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0049 max 0.0084; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00781 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 2 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 2.11 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 112 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
