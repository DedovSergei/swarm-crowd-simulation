# Experiment `S_load150_s3`

**Task 5.8 stage 2: venue S, 150% requested (seed 3): every seat + standing on the walkway and concourse (M, L: the achievable maximum, also the 125% request)**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 5592 agents (load 150.0%, requested 150%): every one of the 3728 seats and 1864 standing (spawnOvercrowdedCrowd, seed 3; below), buffer N = 8192, 1432 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 220171 evaluations, 4613 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.50)** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `cd8e0bbf3411846ca7aa6719887d122a142a7ca1`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-15T16:23:19, 14.8 s wall.

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
| t50 | 686 | 120.0 |
| t90 | 1198 | 209.5 |
| t100 | 1432 | 250.5 |

t_p: the step by which ceil(p x 5592) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 547 | 72 | 13.5 | 244.5 | 25.1 | 52.1 | 13.1-23.1 |
| -x | 5.66 | 552 | 74 | 13.6 | 244.2 | 25.4 | 56.4 | 13.3-23.3 |
| +y | 5.66 | 545 | 77 | 13.5 | 243.3 | 25.1 | 54.2 | 12.9-22.9 |
| -y | 5.66 | 541 | 75 | 13.6 | 242.2 | 25.1 | 53.2 | 13.5-23.4 |
| door +x+y y | 1.20 | 424 | 662 | 0.9 | 245.4 | 86.6 | 125.4 | 174.6-184.5 |
| door +x+y x | 1.20 | 428 | 663 | 0.9 | 243.3 | 88.2 | 135.4 | 166.9-176.8 |
| door -x+y y | 1.20 | 420 | 662 | 1.0 | 244.2 | 86.3 | 135.4 | 166.9-176.8 |
| door -x+y x | 1.20 | 422 | 647 | 0.9 | 246.1 | 86.0 | 135.4 | 173.7-183.7 |
| door -x-y y | 1.20 | 424 | 668 | 1.0 | 247.3 | 86.0 | 125.4 | 184.2-194.1 |
| door -x-y x | 1.20 | 430 | 657 | 1.0 | 245.6 | 87.9 | 135.4 | 154.8-164.8 |
| door +x-y y | 1.20 | 425 | 665 | 0.9 | 242.9 | 87.7 | 135.4 | 168.1-178.1 |
| door +x-y x | 1.20 | 434 | 670 | 1.0 | 250.5 | 86.9 | 135.4 | 174.4-184.4 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 547 | 9.8% | 27.7% |
| -x | avenue | 5.66 | 552 | 9.9% | 27.9% |
| +y | avenue | 5.66 | 545 | 9.7% | 27.6% |
| -y | avenue | 5.66 | 541 | 9.7% | 27.4% |
| door +x+y y | door | 1.20 | 424 | 7.6% | 101.2% |
| door +x+y x | door | 1.20 | 428 | 7.7% | 102.2% |
| door -x+y y | door | 1.20 | 420 | 7.5% | 100.3% |
| door -x+y x | door | 1.20 | 422 | 7.5% | 100.8% |
| door -x-y y | door | 1.20 | 424 | 7.6% | 101.2% |
| door -x-y x | door | 1.20 | 430 | 7.7% | 102.7% |
| door +x-y y | door | 1.20 | 425 | 7.6% | 101.5% |
| door +x-y x | door | 1.20 | 434 | 7.8% | 103.6% |
| **doors (8)** | door | 9.60 | 3407 | 60.9% | |
| **avenues (4)** | avenue | 22.64 | 2185 | 39.1% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 250.5 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 49.7%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 450 | 8.0% | 450 | 8.0% |
| straight +x+y (x wing) 0 | straight | yes | 450 | 8.0% | 450 | 8.0% |
| corner +x+y | corner | **no** | 51 | 0.9% | 51 | 0.9% |
| straight -x+y (y wing) 0 | straight | yes | 453 | 8.1% | 453 | 8.1% |
| straight -x+y (x wing) 0 | straight | yes | 452 | 8.1% | 452 | 8.1% |
| corner -x+y | corner | **no** | 53 | 0.9% | 53 | 0.9% |
| straight -x-y (y wing) 0 | straight | yes | 454 | 8.1% | 454 | 8.1% |
| straight -x-y (x wing) 0 | straight | yes | 451 | 8.1% | 451 | 8.1% |
| corner -x-y | corner | **no** | 47 | 0.8% | 47 | 0.8% |
| straight +x-y (y wing) 0 | straight | yes | 454 | 8.1% | 454 | 8.1% |
| straight +x-y (x wing) 0 | straight | yes | 450 | 8.0% | 450 | 8.0% |
| corner +x-y | corner | **no** | 53 | 0.9% | 53 | 0.9% |
| **straight (8)** | | | 3614 | | 3614 | 64.6% |
| **corner (4)** | | | 204 | | 204 | 3.6% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 1774, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 547 | 13.5 | 244.5 | 0.30 | 0.62 | 0.0% |
| -x | 552 | 13.6 | 244.2 | 0.30 | 0.67 | 0.0% |
| +y | 545 | 13.5 | 243.3 | 0.30 | 0.65 | 0.0% |
| -y | 541 | 13.6 | 242.2 | 0.30 | 0.64 | 0.0% |
| door +x+y y | 424 | 0.9 | 245.4 | 1.04 | 1.50 | 88.0% |
| door +x+y x | 428 | 0.9 | 243.3 | 1.06 | 1.62 | 88.0% |
| door -x+y y | 420 | 1.0 | 244.2 | 1.03 | 1.62 | 84.0% |
| door -x+y x | 422 | 0.9 | 246.1 | 1.03 | 1.62 | 88.0% |
| door -x-y y | 424 | 1.0 | 247.3 | 1.03 | 1.50 | 88.0% |
| door -x-y x | 430 | 1.0 | 245.6 | 1.05 | 1.62 | 88.0% |
| door +x-y y | 425 | 0.9 | 242.9 | 1.05 | 1.62 | 88.0% |
| door +x-y x | 434 | 1.0 | 250.5 | 1.04 | 1.62 | 84.6% |

Mean flow / w J averaged over the doors 1.04, over the avenues 0.30.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 450 | 261 / 190 / 38 | 0.3 | 242.4 | 2.02 | 3.81 | 80% | 80% | 0% | 4.66 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 450 | 265 / 185 / 45 | 0.3 | 240.3 | 2.06 | 3.71 | 84% | 84% | 0% | 4.50 |
| corner +x+y | 1.20 | 31.2 | 51 | 1 / 50 / 0 | 0.2 | 79.6 | 0.64 | 0.90 | 12% | 0% | 12% | 0.66 |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 453 | 264 / 190 / 56 | 0.5 | 241.2 | 2.12 | 4.21 | 80% | 80% | 0% | 4.56 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 452 | 273 / 179 / 37 | 0.7 | 243.1 | 2.02 | 3.71 | 80% | 80% | 0% | 4.64 |
| corner -x+y | 1.20 | 31.2 | 53 | 0 / 53 / 0 | 4.4 | 79.1 | 0.71 | 1.10 | 12% | 0% | 12% | 0.65 |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 454 | 260 / 194 / 49 | 0.3 | 244.3 | 2.06 | 3.61 | 80% | 80% | 0% | 4.55 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 451 | 275 / 176 / 24 | 0.5 | 242.6 | 1.96 | 3.21 | 84% | 84% | 0% | 4.46 |
| corner -x-y | 1.20 | 31.2 | 47 | 0 / 47 / 0 | 4.2 | 73.8 | 0.67 | 1.10 | 12% | 0% | 12% | 0.64 |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 454 | 262 / 193 / 53 | 0.3 | 240.0 | 2.12 | 3.91 | 84% | 84% | 0% | 4.49 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 450 | 267 / 183 / 46 | 0.3 | 247.7 | 2.00 | 3.81 | 84% | 84% | 0% | 4.57 |
| corner +x-y | 1.20 | 31.2 | 53 | 0 / 53 / 0 | 4.4 | 80.8 | 0.69 | 1.10 | 11% | 0% | 11% | 0.64 |

The last agent out (agent 3331, t100 250.5 s): last gangway straight +x-y (x wing) 0, exit door +x-y (x wall). The gangway that cleared last: straight +x-y (x wing) 0 at 247.7 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.52 | 248.9 / 243.5 / 216.4 | 228.4 / 222.3 / 162.7 | 93798.5 | 359675 | 0.253 |
| gangway | 392 | 351.5 | 6.52 | 245.6 / 223.2 / 195.9 | 228.4 / 222.3 / 162.7 | 69736.7 | 190731 | 0.107 |
| walkway | 276 | 257.4 | 4.99 | 214.6 / 143.1 / 0.0 | 192.9 / 128.4 / 0.0 | 0.0 | 32439 | 0.429 |
| avenue | 408 | 384.3 | 2.51 | 228.8 / 10.0 / 0.0 | 214.8 / 0.9 / 0.0 | 0.0 | 28514 | 1.306 |
| exit | 40 | 9.7 | 0.00 | 248.2 / 243.5 / 209.0 | 220.4 / 205.3 / 84.0 | 1028.9 | 3461 | 0.857 |
| concourse | 612 | 609.0 | 6.06 | 229.5 / 186.1 / 129.1 | 206.9 / 183.5 / 101.8 | 23032.9 | 104531 | 0.157 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.54 | 210.8 / 209.0 / 202.9 | 210.8 / 209.0 / 200.3 | 104432.7 | 298777 | 0.054 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 10.5 | 18.5 | gangway | 0.94 | 5.82 | 211.3 | 204.1 | 162.7 | 823.3 | 0.051 |
| 2 | 18.5 | -10.5 | gangway | 0.94 | 5.87 | 212.5 | 205.3 | 161.8 | 822.2 | 0.051 |
| 3 | 19.5 | -10.5 | gangway | 0.96 | 5.74 | 215.5 | 203.2 | 155.7 | 805.5 | 0.045 |
| 4 | -18.5 | 10.5 | gangway | 0.94 | 6.02 | 213.7 | 202.5 | 154.3 | 787.8 | 0.052 |
| 5 | 10.5 | 19.5 | gangway | 0.96 | 5.81 | 213.7 | 209.0 | 151.3 | 779.3 | 0.045 |
| 6 | -10.5 | 18.5 | gangway | 0.94 | 5.84 | 206.2 | 199.4 | 147.3 | 741.8 | 0.053 |
| 7 | 10.5 | 20.5 | gangway | 0.96 | 5.81 | 215.5 | 203.9 | 139.2 | 724.9 | 0.045 |
| 8 | 10.5 | -18.5 | gangway | 0.94 | 5.99 | 210.6 | 200.4 | 141.7 | 723.3 | 0.049 |
| 9 | -20.5 | 11.5 | gangway | 0.92 | 5.84 | 202.7 | 200.8 | 141.7 | 720.2 | 0.035 |
| 10 | -10.5 | -20.5 | gangway | 0.96 | 5.87 | 213.2 | 202.4 | 137.1 | 714.2 | 0.042 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -18.5 | -9.5 | seat row | 0.50 | 7.33 | 208.5 | 206.2 | 200.3 | 697.6 | 0.026 |
| 2 | 18.5 | -9.5 | seat row | 0.50 | 7.52 | 206.0 | 204.3 | 197.5 | 696.5 | 0.026 |
| 3 | 18.5 | 9.5 | seat row | 0.50 | 7.54 | 206.4 | 202.7 | 195.7 | 686.5 | 0.027 |
| 4 | 9.5 | 18.5 | seat row | 0.50 | 7.43 | 205.9 | 204.8 | 195.7 | 684.4 | 0.027 |
| 5 | -18.5 | 9.5 | seat row | 0.50 | 7.52 | 203.4 | 201.0 | 194.1 | 678.3 | 0.027 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 348; agent-steps of seated agents on another row's clearway: 4171.

## Deposit check

Person-seconds deposited: 662458.1, of them in excluded cells: 4005.902.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 27453 overlapping pair-steps: p99 0.0041, max 0.0104 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0041 max 0.0104; venue-geometry 2: p99 0.0002 max 0.0002 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 11 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.06 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 156 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
