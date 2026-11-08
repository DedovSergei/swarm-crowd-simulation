# Experiment `S_load125_s1`

**Task 5.10 stage 4 (AMD 26.10.1): venue S, 125% load (seed 1): every seat + standing on the walkway and concourse**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 4660 agents (load 125.0%, requested 125%): every one of the 3728 seats and 932 standing (spawnOvercrowdedCrowd, seed 1; below), buffer N = 8192, 1465 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 172402 evaluations, 3765 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.25)** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T19:36:36, 13.0 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Spawn (overcrowding)

| | |
|---|---|
| seated | 3728 (every seat) |
| standing | **932** (requested round((1.25 - 1) x 3728) = 932; at most 2143 = floor(2.5 p/m^2 x 857.4 m^2)) |
| standing floor | walkway + rear concourse, 857.4 m^2 |
| standing on the walkway / concourse / gangways | 278 / 654 / 0 |
| **load** | **125.00%** of the seats (requested 125%) |
| standing crowd's mean density | 1.087 p/m^2 |
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 3.29, all circulation cells 3.29 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 1, 6536 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 591 | 103.4 |
| t90 | 1205 | 210.8 |
| t100 | 1465 | 256.2 |

t_p: the step by which ceil(p x 4660) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 448 | 40 | 13.6 | 248.5 | 20.2 | 41.5 | 13.1-23.1 |
| -x | 5.66 | 442 | 36 | 13.6 | 245.2 | 20.2 | 40.4 | 13.3-23.3 |
| +y | 5.66 | 436 | 39 | 13.6 | 245.4 | 19.9 | 35.1 | 13.1-23.1 |
| -y | 5.66 | 440 | 38 | 13.6 | 244.5 | 20.2 | 40.4 | 13.5-23.4 |
| door +x+y y | 1.20 | 362 | 559 | 1.2 | 239.8 | 75.8 | 115.3 | 85.4-95.3 |
| door +x+y x | 1.20 | 353 | 550 | 2.1 | 242.6 | 73.3 | 115.3 | 77.3-87.3 |
| door -x+y y | 1.20 | 368 | 567 | 1.0 | 234.7 | 78.7 | 125.4 | 86.2-96.2 |
| door -x+y x | 1.20 | 358 | 568 | 1.2 | 248.5 | 72.3 | 120.4 | 96.2-106.2 |
| door -x-y y | 1.20 | 364 | 565 | 1.7 | 241.5 | 75.8 | 125.4 | 91.1-101.1 |
| door -x-y x | 1.20 | 365 | 568 | 1.2 | 240.8 | 76.1 | 120.4 | 94.8-104.8 |
| door +x-y y | 1.20 | 360 | 558 | 1.0 | 256.2 | 70.5 | 110.3 | 33.8-43.7 |
| door +x-y x | 1.20 | 364 | 572 | 1.0 | 250.6 | 72.9 | 120.4 | 81.0-91.0 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 448 | 9.6% | 22.2% |
| -x | avenue | 5.66 | 442 | 9.5% | 21.9% |
| +y | avenue | 5.66 | 436 | 9.4% | 21.6% |
| -y | avenue | 5.66 | 440 | 9.4% | 21.8% |
| door +x+y y | door | 1.20 | 362 | 7.8% | 84.5% |
| door +x+y x | door | 1.20 | 353 | 7.6% | 82.4% |
| door -x+y y | door | 1.20 | 368 | 7.9% | 85.9% |
| door -x+y x | door | 1.20 | 358 | 7.7% | 83.6% |
| door -x-y y | door | 1.20 | 364 | 7.8% | 85.0% |
| door -x-y x | door | 1.20 | 365 | 7.8% | 85.2% |
| door +x-y y | door | 1.20 | 360 | 7.7% | 84.0% |
| door +x-y x | door | 1.20 | 364 | 7.8% | 85.0% |
| **doors (8)** | door | 9.60 | 2894 | 62.1% | |
| **avenues (4)** | avenue | 22.64 | 1766 | 37.9% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 256.2 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 40.5%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 467 | 10.0% | 467 | 10.0% |
| straight +x+y (x wing) 0 | straight | yes | 468 | 10.0% | 468 | 10.0% |
| corner +x+y | corner | **no** | 5 | 0.1% | 5 | 0.1% |
| straight -x+y (y wing) 0 | straight | yes | 463 | 9.9% | 463 | 9.9% |
| straight -x+y (x wing) 0 | straight | yes | 462 | 9.9% | 462 | 9.9% |
| corner -x+y | corner | **no** | 16 | 0.3% | 16 | 0.3% |
| straight -x-y (y wing) 0 | straight | yes | 463 | 9.9% | 463 | 9.9% |
| straight -x-y (x wing) 0 | straight | yes | 460 | 9.9% | 460 | 9.9% |
| corner -x-y | corner | **no** | 16 | 0.3% | 16 | 0.3% |
| straight +x-y (y wing) 0 | straight | yes | 467 | 10.0% | 467 | 10.0% |
| straight +x-y (x wing) 0 | straight | yes | 463 | 9.9% | 462 | 9.9% |
| corner +x-y | corner | **no** | 12 | 0.3% | 12 | 0.3% |
| **straight (8)** | | | 3713 | | 3712 | 79.7% |
| **corner (4)** | | | 49 | | 49 | 1.1% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 899, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 448 | 13.6 | 248.5 | 0.24 | 0.50 | 0.0% |
| -x | 442 | 13.6 | 245.2 | 0.24 | 0.48 | 0.0% |
| +y | 436 | 13.6 | 245.4 | 0.24 | 0.42 | 0.0% |
| -y | 440 | 13.6 | 244.5 | 0.24 | 0.48 | 0.0% |
| door +x+y y | 362 | 1.2 | 239.8 | 0.91 | 1.38 | 64.0% |
| door +x+y x | 353 | 2.1 | 242.6 | 0.88 | 1.38 | 52.0% |
| door -x+y y | 368 | 1.0 | 234.7 | 0.94 | 1.50 | 70.8% |
| door -x+y x | 358 | 1.2 | 248.5 | 0.87 | 1.44 | 64.0% |
| door -x-y y | 364 | 1.7 | 241.5 | 0.91 | 1.50 | 76.0% |
| door -x-y x | 365 | 1.2 | 240.8 | 0.91 | 1.44 | 52.0% |
| door +x-y y | 360 | 1.0 | 256.2 | 0.84 | 1.32 | 57.7% |
| door +x-y x | 364 | 1.0 | 250.6 | 0.87 | 1.44 | 57.7% |

Mean flow / w J averaged over the doors 0.89, over the avenues 0.24.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 467 | 286 / 181 / 53 | 0.3 | 236.8 | 2.20 | 2.91 | 88% | 88% | 0% | 3.83 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 468 | 282 / 186 / 56 | 0.2 | 239.6 | 2.19 | 3.11 | 84% | 84% | 0% | 3.80 |
| corner +x+y | 1.20 | 31.2 | 5 | 0 / 5 / 0 | 8.2 | 33.1 | 0.20 | 0.30 | 0% | 0% | 0% | nan |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 463 | 279 / 184 / 64 | 0.3 | 231.8 | 2.28 | 3.01 | 88% | 88% | 0% | 3.80 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 462 | 276 / 186 / 42 | 0.5 | 245.6 | 2.06 | 2.81 | 84% | 84% | 0% | 3.86 |
| corner -x+y | 1.20 | 31.2 | 16 | 0 / 16 / 0 | 4.5 | 38.8 | 0.46 | 0.80 | 0% | 0% | 0% | nan |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 463 | 280 / 183 / 48 | 0.2 | 238.6 | 2.14 | 2.81 | 88% | 88% | 0% | 3.76 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 460 | 277 / 183 / 50 | 0.3 | 237.9 | 2.15 | 3.01 | 88% | 88% | 0% | 3.84 |
| corner -x-y | 1.20 | 31.2 | 16 | 0 / 16 / 0 | 4.5 | 37.3 | 0.49 | 0.80 | 0% | 0% | 0% | nan |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 466 | 282 / 185 / 49 | 0.7 | 253.3 | 2.04 | 3.11 | 81% | 77% | 4% | 3.76 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 463 | 278 / 185 / 54 | 0.7 | 247.7 | 2.09 | 3.01 | 84% | 84% | 0% | 3.89 |
| corner +x-y | 1.20 | 31.2 | 12 | 0 / 12 / 0 | 4.5 | 35.7 | 0.38 | 0.60 | 0% | 0% | 0% | nan |

The last agent out (agent 3423, t100 256.2 s): last gangway straight +x-y (y wing) 0, exit door +x-y (y wall). The gangway that cleared last: straight +x-y (y wing) 0 at 253.3 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.44 | 248.4 / 238.4 / 209.2 | 226.0 / 220.0 / 136.3 | 51552.8 | 231042 | 0.314 |
| gangway | 392 | 351.5 | 6.44 | 232.3 / 224.9 / 178.2 | 226.0 / 220.0 / 136.3 | 50202.6 | 157294 | 0.106 |
| walkway | 276 | 257.4 | 4.43 | 84.7 / 40.9 / 0.0 | 54.0 / 22.7 / 0.0 | 0.0 | 11692 | 0.979 |
| avenue | 408 | 384.3 | 2.46 | 112.6 / 6.8 / 0.0 | 80.1 / 0.5 / 0.0 | 0.0 | 22985 | 1.315 |
| exit | 40 | 9.7 | 0.00 | 248.4 / 237.9 / 165.3 | 174.6 / 146.7 / 51.4 | 594.3 | 2518 | 1.007 |
| concourse | 612 | 609.0 | 5.41 | 209.9 / 102.3 / 37.3 | 117.0 / 100.7 / 18.7 | 755.9 | 36552 | 0.319 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.60 | 212.9 / 208.3 / 191.7 | 212.9 / 208.3 / 189.1 | 93866.1 | 286665 | 0.057 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 10.5 | 19.5 | gangway | 0.96 | 5.78 | 212.7 | 202.7 | 136.3 | 704.1 | 0.031 |
| 2 | 10.5 | -19.5 | gangway | 0.96 | 5.63 | 215.3 | 197.6 | 128.6 | 661.1 | 0.031 |
| 3 | 10.5 | 18.5 | gangway | 0.94 | 5.88 | 205.2 | 202.2 | 125.8 | 650.4 | 0.043 |
| 4 | 19.5 | -11.5 | gangway | 0.92 | 5.79 | 204.1 | 199.0 | 129.4 | 635.1 | 0.031 |
| 5 | -11.5 | -19.5 | gangway | 0.92 | 5.64 | 194.8 | 192.2 | 122.4 | 610.3 | 0.030 |
| 6 | -21.5 | 11.5 | gangway | 0.89 | 5.89 | 214.1 | 210.9 | 127.0 | 603.4 | 0.038 |
| 7 | 11.5 | -19.5 | gangway | 0.92 | 5.80 | 196.8 | 187.8 | 122.1 | 601.2 | 0.031 |
| 8 | -18.5 | 10.5 | gangway | 0.94 | 5.72 | 205.7 | 202.2 | 119.3 | 598.6 | 0.047 |
| 9 | 11.5 | 19.5 | gangway | 0.92 | 5.68 | 196.9 | 185.9 | 121.4 | 598.1 | 0.030 |
| 10 | 18.5 | -10.5 | gangway | 0.94 | 5.77 | 209.0 | 207.4 | 119.8 | 597.4 | 0.047 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 9.5 | 18.5 | seat row | 0.50 | 7.41 | 204.1 | 201.1 | 189.1 | 657.3 | 0.027 |
| 2 | 18.5 | -9.5 | seat row | 0.50 | 7.59 | 205.7 | 196.2 | 181.6 | 629.1 | 0.028 |
| 3 | -18.5 | 9.5 | seat row | 0.50 | 7.54 | 202.0 | 191.3 | 178.6 | 620.4 | 0.029 |
| 4 | 22.5 | -12.5 | seat row | 0.50 | 7.09 | 197.3 | 195.2 | 184.4 | 619.9 | 0.036 |
| 5 | 9.5 | -18.5 | seat row | 0.50 | 7.37 | 202.5 | 189.9 | 176.3 | 614.8 | 0.029 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 415; agent-steps of seated agents on another row's clearway: 2631.

## Deposit check

Person-seconds deposited: 519133.3, of them in excluded cells: 1426.579.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 37425 overlapping pair-steps: p99 0.0053, max 0.0104 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0053 max 0.0104; venue-geometry 1: p99 0.0002 max 0.0002 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 5 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 5.41 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 110 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
