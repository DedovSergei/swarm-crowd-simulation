# Experiment `S_load150_s3`

**Task 5.10 stage 4 (AMD 26.10.1): Task 5.8's model (the level spacing on the gangway inclines, --stair-flow off): venue S, 150% requested (seed 3)**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 5592 agents (load 150.0%, requested 150%): every one of the 3728 seats and 1864 standing (spawnOvercrowdedCrowd, seed 3; below), buffer N = 8192, 1436 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 220246 evaluations, 4621 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.50)** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T20:47:49, 30.2 s wall.

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
| t90 | 1200 | 209.9 |
| t100 | 1436 | 251.2 |

t_p: the step by which ceil(p x 5592) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 547 | 72 | 13.5 | 244.9 | 25.0 | 52.1 | 13.1-23.1 |
| -x | 5.66 | 549 | 74 | 13.6 | 242.1 | 25.5 | 56.4 | 13.3-23.3 |
| +y | 5.66 | 546 | 77 | 13.5 | 244.7 | 25.0 | 54.2 | 12.9-22.9 |
| -y | 5.66 | 548 | 75 | 13.6 | 245.2 | 25.1 | 53.2 | 13.5-23.4 |
| door +x+y y | 1.20 | 425 | 662 | 0.9 | 245.7 | 86.7 | 130.4 | 186.1-196.1 |
| door +x+y x | 1.20 | 428 | 663 | 0.9 | 251.2 | 85.4 | 130.4 | 167.2-177.2 |
| door -x+y y | 1.20 | 419 | 662 | 1.0 | 243.3 | 86.4 | 130.4 | 163.4-173.3 |
| door -x+y x | 1.20 | 425 | 647 | 0.9 | 242.8 | 87.8 | 125.4 | 156.2-166.2 |
| door -x-y y | 1.20 | 423 | 668 | 1.0 | 245.9 | 86.3 | 135.4 | 167.2-177.2 |
| door -x-y x | 1.20 | 426 | 657 | 1.0 | 243.6 | 87.7 | 125.4 | 158.5-168.4 |
| door +x-y y | 1.20 | 422 | 665 | 0.9 | 251.0 | 84.3 | 135.4 | 168.4-178.4 |
| door +x-y x | 1.20 | 434 | 670 | 1.0 | 248.9 | 87.5 | 130.4 | 169.8-179.8 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 547 | 9.8% | 27.6% |
| -x | avenue | 5.66 | 549 | 9.8% | 27.7% |
| +y | avenue | 5.66 | 546 | 9.8% | 27.6% |
| -y | avenue | 5.66 | 548 | 9.8% | 27.7% |
| door +x+y y | door | 1.20 | 425 | 7.6% | 101.2% |
| door +x+y x | door | 1.20 | 428 | 7.7% | 101.9% |
| door -x+y y | door | 1.20 | 419 | 7.5% | 99.8% |
| door -x+y x | door | 1.20 | 425 | 7.6% | 101.2% |
| door -x-y y | door | 1.20 | 423 | 7.6% | 100.7% |
| door -x-y x | door | 1.20 | 426 | 7.6% | 101.4% |
| door +x-y y | door | 1.20 | 422 | 7.5% | 100.5% |
| door +x-y x | door | 1.20 | 434 | 7.8% | 103.3% |
| **doors (8)** | door | 9.60 | 3402 | 60.8% | |
| **avenues (4)** | avenue | 22.64 | 2190 | 39.2% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 251.2 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 49.6%.

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
| +x | 547 | 13.5 | 244.9 | 0.30 | 0.62 | 0.0% |
| -x | 549 | 13.6 | 242.1 | 0.30 | 0.67 | 0.0% |
| +y | 546 | 13.5 | 244.7 | 0.30 | 0.65 | 0.0% |
| -y | 548 | 13.6 | 245.2 | 0.30 | 0.64 | 0.0% |
| door +x+y y | 425 | 0.9 | 245.7 | 1.04 | 1.56 | 88.0% |
| door +x+y x | 428 | 0.9 | 251.2 | 1.02 | 1.56 | 84.6% |
| door -x+y y | 419 | 1.0 | 243.3 | 1.03 | 1.56 | 88.0% |
| door -x+y x | 425 | 0.9 | 242.8 | 1.05 | 1.50 | 88.0% |
| door -x-y y | 423 | 1.0 | 245.9 | 1.03 | 1.62 | 88.0% |
| door -x-y x | 426 | 1.0 | 243.6 | 1.05 | 1.50 | 88.0% |
| door +x-y y | 422 | 0.9 | 251.0 | 1.01 | 1.62 | 84.6% |
| door +x-y x | 434 | 1.0 | 248.9 | 1.05 | 1.56 | 88.0% |

Mean flow / w J averaged over the doors 1.03, over the avenues 0.30.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 450 | 262 / 189 / 49 | 0.3 | 242.8 | 2.06 | 3.71 | 84% | 84% | 0% | 4.64 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 450 | 265 / 185 / 38 | 0.3 | 248.2 | 1.97 | 3.71 | 80% | 80% | 0% | 4.67 |
| corner +x+y | 1.20 | 31.2 | 51 | 1 / 50 / 0 | 0.2 | 79.8 | 0.64 | 0.90 | 12% | 0% | 12% | 0.66 |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 453 | 263 / 190 / 49 | 0.5 | 240.3 | 2.09 | 3.81 | 80% | 80% | 0% | 4.60 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 452 | 277 / 177 / 31 | 0.7 | 239.8 | 2.03 | 3.41 | 80% | 80% | 0% | 4.69 |
| corner -x+y | 1.20 | 31.2 | 53 | 0 / 53 / 0 | 4.4 | 77.3 | 0.72 | 1.10 | 12% | 0% | 12% | 0.65 |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 454 | 260 / 195 / 38 | 0.3 | 242.9 | 2.03 | 3.51 | 84% | 84% | 0% | 4.55 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 451 | 271 / 180 / 27 | 0.5 | 240.7 | 1.99 | 3.41 | 80% | 80% | 0% | 4.64 |
| corner -x-y | 1.20 | 31.2 | 47 | 0 / 47 / 0 | 4.2 | 73.6 | 0.68 | 1.10 | 12% | 0% | 12% | 0.64 |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 454 | 260 / 196 / 50 | 0.3 | 248.0 | 2.04 | 3.51 | 80% | 80% | 0% | 4.68 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 450 | 268 / 183 / 45 | 0.3 | 245.9 | 2.02 | 3.61 | 84% | 84% | 0% | 4.54 |
| corner +x-y | 1.20 | 31.2 | 53 | 0 / 53 / 0 | 4.4 | 77.1 | 0.73 | 1.30 | 12% | 0% | 12% | 0.64 |

The last agent out (agent 695, t100 251.2 s): last gangway straight +x+y (x wing) 0, exit door +x+y (x wall). The gangway that cleared last: straight +x+y (x wing) 0 at 248.2 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.49 | 249.9 / 242.6 / 214.3 | 230.4 / 220.6 / 166.3 | 96174.7 | 359475 | 0.253 |
| gangway | 392 | 351.5 | 6.49 | 247.3 / 222.8 / 195.2 | 230.4 / 220.6 / 166.3 | 71848.5 | 191520 | 0.107 |
| walkway | 276 | 257.4 | 4.97 | 210.9 / 127.9 / 0.0 | 185.4 / 115.6 / 0.0 | 0.0 | 31998 | 0.434 |
| avenue | 408 | 384.3 | 2.51 | 229.3 / 10.0 / 0.0 | 209.5 / 0.9 / 0.0 | 0.0 | 28575 | 1.307 |
| exit | 40 | 9.7 | 0.00 | 248.2 / 242.6 / 205.9 | 222.1 / 204.3 / 81.7 | 1002.4 | 3437 | 0.864 |
| concourse | 612 | 609.0 | 6.13 | 228.1 / 187.8 / 129.6 | 208.1 / 182.8 / 107.4 | 23323.7 | 103946 | 0.157 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.56 | 210.1 / 208.8 / 203.9 | 210.1 / 208.8 / 201.3 | 105036.5 | 299335 | 0.054 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 18.5 | -10.5 | gangway | 0.94 | 6.02 | 212.9 | 205.9 | 166.3 | 834.0 | 0.048 |
| 2 | 10.5 | 18.5 | gangway | 0.94 | 5.75 | 211.5 | 204.3 | 162.7 | 823.1 | 0.049 |
| 3 | -18.5 | 10.5 | gangway | 0.94 | 5.86 | 210.6 | 203.6 | 156.4 | 800.4 | 0.047 |
| 4 | -18.5 | -10.5 | gangway | 0.94 | 5.94 | 211.3 | 206.2 | 152.0 | 792.2 | 0.049 |
| 5 | -10.5 | 18.5 | gangway | 0.94 | 5.86 | 205.7 | 199.0 | 149.7 | 764.5 | 0.053 |
| 6 | -10.5 | -18.5 | gangway | 0.94 | 5.83 | 212.7 | 206.2 | 150.6 | 759.8 | 0.053 |
| 7 | -10.5 | -20.5 | gangway | 0.96 | 5.71 | 220.4 | 205.9 | 142.0 | 755.4 | 0.040 |
| 8 | 10.5 | 20.5 | gangway | 0.96 | 5.98 | 217.4 | 201.3 | 140.5 | 755.1 | 0.044 |
| 9 | 10.5 | 19.5 | gangway | 0.96 | 5.67 | 215.3 | 210.1 | 146.9 | 750.7 | 0.045 |
| 10 | 20.5 | 10.5 | gangway | 0.96 | 5.89 | 215.5 | 208.7 | 137.7 | 738.7 | 0.042 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 18.5 | -9.5 | seat row | 0.50 | 7.52 | 210.1 | 208.8 | 201.3 | 699.4 | 0.026 |
| 2 | -18.5 | 9.5 | seat row | 0.50 | 7.51 | 203.8 | 202.5 | 197.1 | 698.5 | 0.026 |
| 3 | -18.5 | -9.5 | seat row | 0.50 | 7.48 | 205.3 | 203.9 | 196.9 | 688.1 | 0.027 |
| 4 | -9.5 | -18.5 | seat row | 0.50 | 7.56 | 207.3 | 205.2 | 195.4 | 680.8 | 0.027 |
| 5 | 9.5 | -18.5 | seat row | 0.50 | 7.50 | 203.9 | 201.8 | 190.8 | 668.4 | 0.028 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 326; agent-steps of seated agents on another row's clearway: 3711.

## Deposit check

Person-seconds deposited: 662755.8, of them in excluded cells: 3945.732.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 31630 overlapping pair-steps: p99 0.0045, max 0.0108 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0045 max 0.0108; venue-geometry 3: p99 0.0011 max 0.0011 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 8 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.13 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 152 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
