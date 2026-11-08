# Experiment `S_load125_s1`

**Task 5.8 stage 2: venue S, 125% load (seed 1): every seat + standing on the walkway and concourse**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 4660 agents (load 125.0%, requested 125%): every one of the 3728 seats and 932 standing (spawnOvercrowdedCrowd, seed 1; below), buffer N = 8192, 1230 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 155910 evaluations, 3736 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.25)** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `cd8e0bbf3411846ca7aa6719887d122a142a7ca1`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-15T16:20:37, 12.9 s wall.

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
| t50 | 578 | 101.1 |
| t90 | 1019 | 178.2 |
| t100 | 1230 | 215.1 |

t_p: the step by which ceil(p x 4660) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 437 | 40 | 13.6 | 205.5 | 24.1 | 41.5 | 13.1-23.1 |
| -x | 5.66 | 450 | 36 | 13.6 | 207.3 | 24.6 | 40.4 | 13.3-23.3 |
| +y | 5.66 | 444 | 39 | 13.6 | 208.3 | 24.2 | 35.1 | 13.1-23.1 |
| -y | 5.66 | 456 | 38 | 13.6 | 211.1 | 24.5 | 40.4 | 13.5-23.4 |
| door +x+y y | 1.20 | 362 | 559 | 1.2 | 206.9 | 87.9 | 130.4 | 113.9-123.8 |
| door +x+y x | 1.20 | 355 | 550 | 2.1 | 213.7 | 83.8 | 130.4 | 97.9-107.9 |
| door -x+y y | 1.20 | 361 | 567 | 1.0 | 215.1 | 84.2 | 135.4 | 112.6-122.6 |
| door -x+y x | 1.20 | 358 | 568 | 1.2 | 211.3 | 85.1 | 130.4 | 126.6-136.6 |
| door -x-y y | 1.20 | 359 | 565 | 1.7 | 213.6 | 84.7 | 130.4 | 112.8-122.8 |
| door -x-y x | 1.20 | 358 | 568 | 1.2 | 214.6 | 83.8 | 130.4 | 111.8-121.7 |
| door +x-y y | 1.20 | 356 | 558 | 1.0 | 210.2 | 85.0 | 135.4 | 111.6-121.6 |
| door +x-y x | 1.20 | 364 | 572 | 1.0 | 211.8 | 86.3 | 135.4 | 106.2-116.1 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 437 | 9.4% | 25.8% |
| -x | avenue | 5.66 | 450 | 9.7% | 26.5% |
| +y | avenue | 5.66 | 444 | 9.5% | 26.2% |
| -y | avenue | 5.66 | 456 | 9.8% | 26.9% |
| door +x+y y | door | 1.20 | 362 | 7.8% | 100.6% |
| door +x+y x | door | 1.20 | 355 | 7.6% | 98.7% |
| door -x+y y | door | 1.20 | 361 | 7.7% | 100.4% |
| door -x+y x | door | 1.20 | 358 | 7.7% | 99.5% |
| door -x-y y | door | 1.20 | 359 | 7.7% | 99.8% |
| door -x-y x | door | 1.20 | 358 | 7.7% | 99.5% |
| door +x-y y | door | 1.20 | 356 | 7.6% | 99.0% |
| door +x-y x | door | 1.20 | 364 | 7.8% | 101.2% |
| **doors (8)** | door | 9.60 | 2873 | 61.7% | |
| **avenues (4)** | avenue | 22.64 | 1787 | 38.3% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 215.1 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 48.2%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 465 | 10.0% | 464 | 10.0% |
| straight +x+y (x wing) 0 | straight | yes | 469 | 10.1% | 469 | 10.1% |
| corner +x+y | corner | **no** | 8 | 0.2% | 8 | 0.2% |
| straight -x+y (y wing) 0 | straight | yes | 463 | 9.9% | 463 | 9.9% |
| straight -x+y (x wing) 0 | straight | yes | 462 | 9.9% | 462 | 9.9% |
| corner -x+y | corner | **no** | 16 | 0.3% | 16 | 0.3% |
| straight -x-y (y wing) 0 | straight | yes | 463 | 9.9% | 463 | 9.9% |
| straight -x-y (x wing) 0 | straight | yes | 461 | 9.9% | 461 | 9.9% |
| corner -x-y | corner | **no** | 16 | 0.3% | 16 | 0.3% |
| straight +x-y (y wing) 0 | straight | yes | 466 | 10.0% | 466 | 10.0% |
| straight +x-y (x wing) 0 | straight | yes | 463 | 9.9% | 463 | 9.9% |
| corner +x-y | corner | **no** | 12 | 0.3% | 12 | 0.3% |
| **straight (8)** | | | 3712 | | 3711 | 79.6% |
| **corner (4)** | | | 52 | | 52 | 1.1% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 897, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 437 | 13.6 | 205.5 | 0.29 | 0.50 | 0.0% |
| -x | 450 | 13.6 | 207.3 | 0.29 | 0.48 | 0.0% |
| +y | 444 | 13.6 | 208.3 | 0.29 | 0.42 | 0.0% |
| -y | 456 | 13.6 | 211.1 | 0.29 | 0.48 | 0.0% |
| door +x+y y | 362 | 1.2 | 206.9 | 1.05 | 1.56 | 85.7% |
| door +x+y x | 355 | 2.1 | 213.7 | 1.00 | 1.56 | 81.8% |
| door -x+y y | 361 | 1.0 | 215.1 | 1.01 | 1.62 | 86.4% |
| door -x+y x | 358 | 1.2 | 211.3 | 1.02 | 1.56 | 86.4% |
| door -x-y y | 359 | 1.7 | 213.6 | 1.01 | 1.56 | 86.4% |
| door -x-y x | 358 | 1.2 | 214.6 | 1.00 | 1.56 | 86.4% |
| door +x-y y | 356 | 1.0 | 210.2 | 1.02 | 1.62 | 86.4% |
| door +x-y x | 364 | 1.0 | 211.8 | 1.03 | 1.62 | 86.4% |

Mean flow / w J averaged over the doors 1.02, over the avenues 0.29.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 465 | 286 / 179 / 48 | 0.3 | 203.9 | 2.52 | 3.41 | 81% | 81% | 0% | 4.29 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 468 | 284 / 185 / 54 | 0.2 | 210.8 | 2.48 | 3.91 | 73% | 73% | 0% | 4.35 |
| corner +x+y | 1.20 | 31.2 | 8 | 0 / 8 / 0 | 4.5 | 32.5 | 0.28 | 0.40 | 0% | 0% | 0% | nan |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 463 | 272 / 191 / 52 | 0.3 | 212.2 | 2.43 | 3.91 | 77% | 77% | 0% | 4.36 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 462 | 276 / 186 / 55 | 0.5 | 208.3 | 2.49 | 3.61 | 81% | 81% | 0% | 4.34 |
| corner -x+y | 1.20 | 31.2 | 16 | 0 / 16 / 0 | 4.5 | 35.3 | 0.52 | 0.90 | 0% | 0% | 0% | nan |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 463 | 275 / 188 / 51 | 0.2 | 210.6 | 2.44 | 3.61 | 77% | 77% | 0% | 4.34 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 461 | 270 / 191 / 50 | 0.3 | 211.6 | 2.42 | 3.81 | 77% | 77% | 0% | 4.30 |
| corner -x-y | 1.20 | 31.2 | 16 | 0 / 16 / 0 | 4.5 | 35.0 | 0.52 | 0.90 | 0% | 0% | 0% | nan |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 466 | 278 / 188 / 48 | 0.7 | 207.3 | 2.49 | 3.91 | 81% | 81% | 0% | 4.32 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 463 | 278 / 185 / 46 | 0.7 | 208.8 | 2.44 | 3.71 | 81% | 81% | 0% | 4.27 |
| corner +x-y | 1.20 | 31.2 | 12 | 0 / 12 / 0 | 4.5 | 35.3 | 0.39 | 0.60 | 0% | 0% | 0% | nan |

The last agent out (agent 1072, t100 215.1 s): last gangway straight -x+y (y wing) 0, exit door -x+y (y wall). The gangway that cleared last: straight -x+y (y wing) 0 at 212.2 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.36 | 215.0 / 207.1 / 173.7 | 192.4 / 187.3 / 106.3 | 44789.4 | 227128 | 0.325 |
| gangway | 392 | 351.5 | 6.36 | 211.3 / 188.0 / 146.2 | 192.4 / 187.3 / 106.3 | 41909.1 | 144874 | 0.123 |
| walkway | 276 | 257.4 | 4.43 | 141.0 / 48.3 / 0.0 | 83.8 / 27.1 / 0.0 | 0.0 | 12688 | 0.893 |
| avenue | 408 | 384.3 | 2.46 | 188.0 / 6.8 / 0.0 | 134.3 / 0.5 / 0.0 | 0.0 | 23285 | 1.312 |
| exit | 40 | 9.7 | 0.00 | 214.4 / 206.9 / 164.6 | 179.1 / 156.5 / 57.9 | 673.8 | 2644 | 0.943 |
| concourse | 612 | 609.0 | 5.70 | 191.0 / 132.2 / 60.2 | 157.1 / 123.5 / 39.5 | 2206.5 | 43636 | 0.268 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.49 | 174.2 / 171.6 / 164.1 | 174.2 / 171.6 / 161.4 | 75941.3 | 241424 | 0.069 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -10.5 | -18.5 | gangway | 0.94 | 5.90 | 174.2 | 169.8 | 105.6 | 539.9 | 0.062 |
| 2 | 19.5 | 11.5 | gangway | 0.92 | 5.78 | 152.7 | 148.1 | 106.3 | 528.8 | 0.051 |
| 3 | 10.5 | 18.5 | gangway | 0.94 | 5.96 | 171.4 | 165.1 | 105.3 | 524.3 | 0.063 |
| 4 | -19.5 | 11.5 | gangway | 0.92 | 5.95 | 159.3 | 156.5 | 104.2 | 516.7 | 0.048 |
| 5 | 18.5 | 10.5 | gangway | 0.94 | 5.79 | 163.5 | 159.7 | 102.1 | 515.6 | 0.066 |
| 6 | 18.5 | -10.5 | gangway | 0.94 | 5.75 | 172.1 | 166.0 | 102.0 | 508.7 | 0.065 |
| 7 | -21.5 | 11.5 | gangway | 0.89 | 5.71 | 171.9 | 169.7 | 105.3 | 508.2 | 0.051 |
| 8 | 19.5 | 10.5 | gangway | 0.96 | 5.73 | 167.2 | 163.2 | 97.6 | 507.7 | 0.054 |
| 9 | -18.5 | -10.5 | gangway | 0.94 | 5.82 | 172.5 | 167.0 | 100.2 | 500.7 | 0.066 |
| 10 | 11.5 | 19.5 | gangway | 0.92 | 5.99 | 158.6 | 155.5 | 100.2 | 499.5 | 0.048 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 9.5 | -18.5 | seat row | 0.50 | 7.49 | 171.6 | 169.0 | 161.4 | 556.2 | 0.032 |
| 2 | 9.5 | 18.5 | seat row | 0.50 | 7.48 | 166.9 | 165.3 | 158.1 | 548.9 | 0.033 |
| 3 | -9.5 | -18.5 | seat row | 0.50 | 7.49 | 170.5 | 163.5 | 151.1 | 526.6 | 0.034 |
| 4 | -18.5 | 9.5 | seat row | 0.50 | 7.48 | 168.1 | 166.0 | 151.3 | 521.7 | 0.034 |
| 5 | 18.5 | -9.5 | seat row | 0.50 | 7.42 | 164.6 | 162.1 | 150.2 | 519.4 | 0.034 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 401; agent-steps of seated agents on another row's clearway: 3881.

## Deposit check

Person-seconds deposited: 470125.4, of them in excluded cells: 1573.656.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 23616 overlapping pair-steps: p99 0.0038, max 0.0118 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0038 max 0.0118; venue-geometry 1: p99 0.0001 max 0.0001 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 3 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 5.70 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 156 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
