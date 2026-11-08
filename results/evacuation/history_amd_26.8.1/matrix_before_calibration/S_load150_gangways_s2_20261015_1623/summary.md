# Experiment `S_load150_gangways_s2`

**Task 5.8 stage 2: venue S, 150% load (seed 2): standing also on the gangways**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 5592 agents (load 150.0%, requested 150%): every one of the 3728 seats and 1864 standing (spawnOvercrowdedCrowd, seed 2; below), buffer N = 8192, 1503 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 223467 evaluations, 4852 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.50)** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `cd8e0bbf3411846ca7aa6719887d122a142a7ca1`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-15T16:23:57, 15.4 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Spawn (overcrowding)

| | |
|---|---|
| seated | 3728 (every seat) |
| standing | **1864** (requested round((1.50 - 1) x 3728) = 1864; at most 2831 = floor(2.5 p/m^2 x 1132.7 m^2)) |
| standing floor | walkway + rear concourse + gangways (the gangway-standing variant), 1132.7 m^2 |
| standing on the walkway / concourse / gangways | 414 / 1034 / 416 |
| **load** | **150.00%** of the seats (requested 150%) |
| standing crowd's mean density | 1.646 p/m^2 |
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 3.18, all circulation cells 3.18 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 2, 13718 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 695 | 121.6 |
| t90 | 1210 | 211.6 |
| t100 | 1503 | 262.9 |

t_p: the step by which ceil(p x 5592) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 541 | 57 | 13.5 | 254.3 | 23.8 | 46.8 | 13.1-23.1 |
| -x | 5.66 | 545 | 58 | 13.5 | 248.2 | 24.6 | 44.7 | 13.1-23.1 |
| +y | 5.66 | 551 | 52 | 13.5 | 250.6 | 24.6 | 46.8 | 13.3-23.3 |
| -y | 5.66 | 547 | 65 | 13.6 | 242.8 | 25.3 | 48.9 | 12.9-22.9 |
| door +x+y y | 1.20 | 427 | 658 | 1.2 | 256.4 | 83.6 | 125.4 | 168.8-178.8 |
| door +x+y x | 1.20 | 422 | 671 | 1.2 | 258.3 | 82.0 | 135.4 | 143.4-153.4 |
| door -x+y y | 1.20 | 437 | 674 | 0.9 | 244.3 | 89.7 | 130.4 | 154.4-164.4 |
| door -x+y x | 1.20 | 427 | 688 | 0.9 | 243.6 | 87.9 | 125.4 | 153.9-163.9 |
| door -x-y y | 1.20 | 418 | 660 | 0.9 | 245.7 | 85.3 | 130.4 | 166.3-176.3 |
| door -x-y x | 1.20 | 426 | 669 | 0.9 | 249.9 | 85.5 | 135.4 | 142.7-152.7 |
| door +x-y y | 1.20 | 417 | 683 | 1.0 | 262.9 | 79.6 | 135.4 | 145.3-155.3 |
| door +x-y x | 1.20 | 434 | 657 | 1.2 | 249.2 | 87.4 | 130.4 | 138.7-148.7 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 541 | 9.7% | 26.1% |
| -x | avenue | 5.66 | 545 | 9.7% | 26.3% |
| +y | avenue | 5.66 | 551 | 9.9% | 26.6% |
| -y | avenue | 5.66 | 547 | 9.8% | 26.4% |
| door +x+y y | door | 1.20 | 427 | 7.6% | 97.1% |
| door +x+y x | door | 1.20 | 422 | 7.5% | 96.0% |
| door -x+y y | door | 1.20 | 437 | 7.8% | 99.4% |
| door -x+y x | door | 1.20 | 427 | 7.6% | 97.1% |
| door -x-y y | door | 1.20 | 418 | 7.5% | 95.1% |
| door -x-y x | door | 1.20 | 426 | 7.6% | 96.9% |
| door +x-y y | door | 1.20 | 417 | 7.5% | 94.9% |
| door +x-y x | door | 1.20 | 434 | 7.8% | 98.7% |
| **doors (8)** | door | 9.60 | 3408 | 60.9% | |
| **avenues (4)** | avenue | 22.64 | 2184 | 39.1% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 262.9 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 47.4%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 483 | 8.6% | 469 | 8.4% |
| straight +x+y (x wing) 0 | straight | yes | 495 | 8.9% | 495 | 8.9% |
| corner +x+y | corner | **no** | 80 | 1.4% | 80 | 1.4% |
| straight -x+y (y wing) 0 | straight | yes | 479 | 8.6% | 479 | 8.6% |
| straight -x+y (x wing) 0 | straight | yes | 482 | 8.6% | 482 | 8.6% |
| corner -x+y | corner | **no** | 96 | 1.7% | 96 | 1.7% |
| straight -x-y (y wing) 0 | straight | yes | 480 | 8.6% | 480 | 8.6% |
| straight -x-y (x wing) 0 | straight | yes | 482 | 8.6% | 482 | 8.6% |
| corner -x-y | corner | **no** | 88 | 1.6% | 88 | 1.6% |
| straight +x-y (y wing) 0 | straight | yes | 480 | 8.6% | 480 | 8.6% |
| straight +x-y (x wing) 0 | straight | yes | 483 | 8.6% | 482 | 8.6% |
| corner +x-y | corner | **no** | 90 | 1.6% | 90 | 1.6% |
| **straight (8)** | | | 3864 | | 3849 | 68.8% |
| **corner (4)** | | | 354 | | 354 | 6.3% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 1389, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 541 | 13.5 | 254.3 | 0.28 | 0.56 | 0.0% |
| -x | 545 | 13.5 | 248.2 | 0.29 | 0.53 | 0.0% |
| +y | 551 | 13.5 | 250.6 | 0.29 | 0.56 | 0.0% |
| -y | 547 | 13.6 | 242.8 | 0.30 | 0.59 | 0.0% |
| door +x+y y | 427 | 1.2 | 256.4 | 1.00 | 1.50 | 88.5% |
| door +x+y x | 422 | 1.2 | 258.3 | 0.98 | 1.62 | 84.6% |
| door -x+y y | 437 | 0.9 | 244.3 | 1.07 | 1.56 | 88.0% |
| door -x+y x | 427 | 0.9 | 243.6 | 1.05 | 1.50 | 88.0% |
| door -x-y y | 418 | 0.9 | 245.7 | 1.02 | 1.56 | 88.0% |
| door -x-y x | 426 | 0.9 | 249.9 | 1.02 | 1.62 | 88.5% |
| door +x-y y | 417 | 1.0 | 262.9 | 0.95 | 1.62 | 81.5% |
| door +x-y x | 434 | 1.2 | 249.2 | 1.05 | 1.56 | 88.0% |

Mean flow / w J averaged over the doors 1.02, over the avenues 0.29.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 483 | 304 / 180 / 21 | 0.2 | 253.4 | 1.99 | 3.61 | 85% | 85% | 0% | 4.45 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 481 | 294 / 201 / 60 | 0.2 | 255.4 | 2.17 | 4.01 | 77% | 77% | 0% | 4.40 |
| corner +x+y | 1.20 | 31.2 | 80 | 3 / 78 / 0 | 0.2 | 91.1 | 0.89 | 1.10 | 10% | 0% | 10% | 1.62 |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 479 | 308 / 171 / 25 | 0.2 | 241.4 | 2.09 | 3.41 | 88% | 84% | 4% | 4.42 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 482 | 291 / 191 / 36 | 0.2 | 240.7 | 2.15 | 3.71 | 84% | 84% | 0% | 4.53 |
| corner -x+y | 1.20 | 31.2 | 96 | 4 / 94 / 0 | 0.2 | 107.0 | 0.92 | 1.50 | 18% | 9% | 9% | 2.09 |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 480 | 297 / 183 / 31 | 0.2 | 242.8 | 2.10 | 3.51 | 84% | 84% | 0% | 4.44 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 482 | 299 / 184 / 25 | 0.2 | 247.0 | 2.06 | 3.51 | 84% | 84% | 0% | 4.41 |
| corner -x-y | 1.20 | 31.2 | 88 | 3 / 87 / 0 | 0.2 | 101.1 | 0.89 | 1.20 | 9% | 0% | 9% | 1.76 |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 479 | 283 / 197 / 58 | 0.2 | 259.9 | 2.07 | 3.71 | 78% | 78% | 0% | 4.42 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 483 | 312 / 171 / 21 | 0.2 | 246.3 | 2.05 | 3.11 | 88% | 84% | 4% | 4.42 |
| corner +x-y | 1.20 | 31.2 | 90 | 2 / 88 / 0 | 0.2 | 107.4 | 0.84 | 1.20 | 9% | 0% | 9% | 1.73 |

The last agent out (agent 3332, t100 262.9 s): last gangway straight +x-y (y wing) 0, exit door +x-y (y wall). The gangway that cleared last: straight +x-y (y wing) 0 at 259.9 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.55 | 257.6 / 249.9 / 217.2 | 237.2 / 230.0 / 176.1 | 84692.1 | 344278 | 0.269 |
| gangway | 392 | 351.5 | 6.55 | 253.8 / 232.3 / 206.6 | 237.2 / 230.0 / 176.1 | 70122.0 | 200002 | 0.113 |
| walkway | 276 | 257.4 | 4.83 | 225.6 / 163.2 / 0.0 | 207.1 / 149.4 / 0.0 | 0.0 | 32203 | 0.449 |
| avenue | 408 | 384.3 | 2.39 | 238.7 / 2.3 / 0.0 | 218.3 / 1.0 / 0.0 | 0.0 | 28508 | 1.306 |
| exit | 40 | 9.7 | 0.00 | 256.4 / 249.8 / 201.3 | 219.2 / 198.7 / 77.7 | 949.3 | 3348 | 0.890 |
| concourse | 612 | 609.0 | 5.93 | 230.2 / 173.7 / 103.5 | 199.2 / 166.7 / 83.1 | 13620.9 | 80217 | 0.191 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.54 | 222.1 / 217.4 / 208.7 | 222.1 / 217.4 / 206.7 | 112401.6 | 324938 | 0.050 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -18.5 | -10.5 | gangway | 0.94 | 5.80 | 212.0 | 206.2 | 176.1 | 885.9 | 0.045 |
| 2 | 18.5 | -10.5 | gangway | 0.94 | 5.84 | 221.3 | 212.7 | 167.9 | 856.8 | 0.047 |
| 3 | -10.5 | 18.5 | gangway | 0.94 | 6.06 | 223.4 | 216.7 | 163.7 | 852.9 | 0.044 |
| 4 | -18.5 | 10.5 | gangway | 0.94 | 5.99 | 220.0 | 216.2 | 168.1 | 847.2 | 0.047 |
| 5 | 10.5 | 18.5 | gangway | 0.94 | 6.04 | 218.5 | 211.1 | 166.2 | 847.0 | 0.043 |
| 6 | -10.5 | -18.5 | gangway | 0.94 | 5.82 | 213.9 | 206.6 | 163.5 | 830.9 | 0.044 |
| 7 | 17.5 | -10.5 | gangway | 0.95 | 5.81 | 220.9 | 214.4 | 159.3 | 804.4 | 0.048 |
| 8 | -10.5 | -19.5 | gangway | 0.96 | 5.75 | 215.8 | 206.7 | 153.4 | 792.3 | 0.042 |
| 9 | -10.5 | 17.5 | gangway | 0.95 | 5.69 | 223.0 | 215.7 | 155.1 | 780.1 | 0.045 |
| 10 | 10.5 | 19.5 | gangway | 0.96 | 5.84 | 217.9 | 212.0 | 149.7 | 759.0 | 0.040 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 18.5 | -9.5 | seat row | 0.50 | 7.47 | 213.9 | 211.8 | 206.7 | 724.7 | 0.025 |
| 2 | -18.5 | 9.5 | seat row | 0.50 | 7.53 | 214.4 | 212.2 | 205.3 | 724.5 | 0.025 |
| 3 | -9.5 | 18.5 | seat row | 0.50 | 7.46 | 215.0 | 213.2 | 205.3 | 721.2 | 0.025 |
| 4 | 9.5 | 18.5 | seat row | 0.50 | 7.47 | 213.4 | 210.2 | 203.4 | 716.2 | 0.026 |
| 5 | 9.5 | -18.5 | seat row | 0.50 | 7.49 | 211.1 | 209.7 | 205.0 | 712.7 | 0.026 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 275; agent-steps of seated agents on another row's clearway: 2399.

## Deposit check

Person-seconds deposited: 672273.2, of them in excluded cells: 3057.034.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 35718 overlapping pair-steps: p99 0.0037, max 0.0110 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0037 max 0.0110; venue-geometry 2: p99 0.0004 max 0.0004 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 6 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 5.93 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 127 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
