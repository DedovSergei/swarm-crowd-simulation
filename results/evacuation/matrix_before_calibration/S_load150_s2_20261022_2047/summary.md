# Experiment `S_load150_s2`

**Task 5.10 stage 4 (AMD 26.10.1): Task 5.8's model (the level spacing on the gangway inclines, --stair-flow off): venue S, 150% requested (seed 2)**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 5592 agents (load 150.0%, requested 150%): every one of the 3728 seats and 1864 standing (spawnOvercrowdedCrowd, seed 2; below), buffer N = 8192, 1489 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 221003 evaluations, 4551 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.50)** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T20:47:17, 25.5 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Spawn (overcrowding)

| | |
|---|---|
| seated | 3728 (every seat) |
| standing | **1864** (requested round((1.50 - 1) x 3728) = 1864; at most 2143 = floor(2.5 p/m^2 x 857.4 m^2)) |
| standing floor | walkway + rear concourse, 857.4 m^2 |
| standing on the walkway / concourse / gangways | 538 / 1326 / 0 |
| **load** | **150.00%** of the seats (requested 150%) |
| standing crowd's mean density | 2.174 p/m^2 |
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 3.84, all circulation cells 3.84 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 2, 24464 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 685 | 119.8 |
| t90 | 1204 | 210.6 |
| t100 | 1489 | 260.4 |

t_p: the step by which ceil(p x 5592) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 543 | 75 | 13.5 | 251.0 | 24.2 | 53.2 | 13.1-23.1 |
| -x | 5.66 | 537 | 73 | 13.5 | 242.2 | 24.9 | 52.1 | 13.1-23.1 |
| +y | 5.66 | 554 | 69 | 13.5 | 248.5 | 25.0 | 55.3 | 13.3-23.3 |
| -y | 5.66 | 539 | 78 | 13.6 | 239.8 | 25.2 | 57.4 | 13.3-23.3 |
| door +x+y y | 1.20 | 427 | 656 | 0.9 | 247.8 | 86.4 | 130.4 | 189.1-199.0 |
| door +x+y x | 1.20 | 427 | 663 | 1.2 | 257.6 | 83.2 | 125.4 | 165.5-175.4 |
| door -x+y y | 1.20 | 434 | 658 | 1.0 | 248.5 | 87.6 | 125.4 | 164.1-174.0 |
| door -x+y x | 1.20 | 425 | 674 | 0.9 | 260.4 | 81.8 | 130.4 | 178.1-188.0 |
| door -x-y y | 1.20 | 416 | 658 | 0.9 | 255.5 | 81.6 | 125.4 | 180.3-190.3 |
| door -x-y x | 1.20 | 432 | 655 | 0.9 | 245.4 | 88.3 | 130.4 | 155.1-165.1 |
| door +x-y y | 1.20 | 421 | 669 | 1.0 | 259.6 | 81.4 | 125.4 | 167.0-177.0 |
| door +x-y x | 1.20 | 437 | 664 | 1.2 | 246.6 | 89.0 | 140.4 | 161.1-171.1 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 543 | 9.7% | 26.4% |
| -x | avenue | 5.66 | 537 | 9.6% | 26.1% |
| +y | avenue | 5.66 | 554 | 9.9% | 27.0% |
| -y | avenue | 5.66 | 539 | 9.6% | 26.2% |
| door +x+y y | door | 1.20 | 427 | 7.6% | 98.1% |
| door +x+y x | door | 1.20 | 427 | 7.6% | 98.1% |
| door -x+y y | door | 1.20 | 434 | 7.8% | 99.7% |
| door -x+y x | door | 1.20 | 425 | 7.6% | 97.6% |
| door -x-y y | door | 1.20 | 416 | 7.4% | 95.5% |
| door -x-y x | door | 1.20 | 432 | 7.7% | 99.2% |
| door +x-y y | door | 1.20 | 421 | 7.5% | 96.7% |
| door +x-y x | door | 1.20 | 437 | 7.8% | 100.4% |
| **doors (8)** | door | 9.60 | 3419 | 61.1% | |
| **avenues (4)** | avenue | 22.64 | 2173 | 38.9% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 260.4 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 47.8%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 453 | 8.1% | 440 | 7.9% |
| straight +x+y (x wing) 0 | straight | yes | 461 | 8.2% | 461 | 8.2% |
| corner +x+y | corner | **no** | 50 | 0.9% | 50 | 0.9% |
| straight -x+y (y wing) 0 | straight | yes | 454 | 8.1% | 447 | 8.0% |
| straight -x+y (x wing) 0 | straight | yes | 455 | 8.1% | 455 | 8.1% |
| corner -x+y | corner | **no** | 56 | 1.0% | 56 | 1.0% |
| straight -x-y (y wing) 0 | straight | yes | 454 | 8.1% | 454 | 8.1% |
| straight -x-y (x wing) 0 | straight | yes | 453 | 8.1% | 449 | 8.0% |
| corner -x-y | corner | **no** | 52 | 0.9% | 52 | 0.9% |
| straight +x-y (y wing) 0 | straight | yes | 455 | 8.1% | 455 | 8.1% |
| straight +x-y (x wing) 0 | straight | yes | 451 | 8.1% | 448 | 8.0% |
| corner +x-y | corner | **no** | 54 | 1.0% | 54 | 1.0% |
| **straight (8)** | | | 3636 | | 3609 | 64.5% |
| **corner (4)** | | | 212 | | 212 | 3.8% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 1771, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 543 | 13.5 | 251.0 | 0.29 | 0.64 | 0.0% |
| -x | 537 | 13.5 | 242.2 | 0.30 | 0.62 | 0.0% |
| +y | 554 | 13.5 | 248.5 | 0.30 | 0.66 | 0.0% |
| -y | 539 | 13.6 | 239.8 | 0.30 | 0.69 | 0.0% |
| door +x+y y | 427 | 0.9 | 247.8 | 1.03 | 1.56 | 92.0% |
| door +x+y x | 427 | 1.2 | 257.6 | 1.00 | 1.50 | 84.6% |
| door -x+y y | 434 | 1.0 | 248.5 | 1.05 | 1.50 | 92.0% |
| door -x+y x | 425 | 0.9 | 260.4 | 0.98 | 1.56 | 81.5% |
| door -x-y y | 416 | 0.9 | 255.5 | 0.98 | 1.50 | 84.6% |
| door -x-y x | 432 | 0.9 | 245.4 | 1.06 | 1.56 | 88.0% |
| door +x-y y | 421 | 1.0 | 259.6 | 0.97 | 1.50 | 81.5% |
| door +x-y x | 437 | 1.2 | 246.6 | 1.06 | 1.68 | 88.0% |

Mean flow / w J averaged over the doors 1.02, over the avenues 0.30.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 453 | 270 / 183 / 32 | 0.2 | 244.9 | 1.98 | 3.51 | 84% | 84% | 0% | 4.56 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 448 | 264 / 197 / 55 | 0.3 | 254.7 | 2.03 | 3.71 | 77% | 77% | 0% | 4.49 |
| corner +x+y | 1.20 | 31.2 | 50 | 0 / 50 / 0 | 4.5 | 76.3 | 0.70 | 0.90 | 12% | 0% | 12% | 0.67 |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 454 | 277 / 177 / 31 | 0.5 | 245.6 | 1.98 | 3.61 | 88% | 88% | 0% | 4.45 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 448 | 257 / 198 / 59 | 0.3 | 257.5 | 2.00 | 3.71 | 77% | 77% | 0% | 4.55 |
| corner -x+y | 1.20 | 31.2 | 56 | 0 / 56 / 0 | 4.4 | 87.6 | 0.67 | 0.90 | 11% | 0% | 11% | 0.68 |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 450 | 261 / 194 / 51 | 0.7 | 252.6 | 2.01 | 3.61 | 77% | 77% | 0% | 4.61 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 453 | 280 / 174 / 33 | 0.5 | 242.4 | 2.01 | 3.31 | 84% | 84% | 0% | 4.54 |
| corner -x-y | 1.20 | 31.2 | 52 | 0 / 52 / 0 | 4.2 | 76.8 | 0.71 | 1.00 | 12% | 0% | 12% | 0.68 |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 452 | 257 / 198 / 62 | 0.2 | 256.6 | 2.01 | 3.61 | 77% | 77% | 0% | 4.66 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 451 | 278 / 173 / 32 | 0.3 | 243.6 | 1.98 | 3.41 | 84% | 84% | 0% | 4.62 |
| corner +x-y | 1.20 | 31.2 | 54 | 0 / 54 / 0 | 3.8 | 84.3 | 0.67 | 1.10 | 11% | 0% | 11% | 0.66 |

The last agent out (agent 1024, t100 260.4 s): last gangway straight -x+y (x wing) 0, exit door -x+y (x wall). The gangway that cleared last: straight -x+y (x wing) 0 at 257.5 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.45 | 259.4 / 251.2 / 215.3 | 232.5 / 228.8 / 173.3 | 94544.0 | 363277 | 0.251 |
| gangway | 392 | 351.5 | 6.45 | 256.4 / 229.0 / 196.4 | 232.5 / 228.8 / 173.3 | 70346.5 | 191667 | 0.109 |
| walkway | 276 | 257.4 | 5.10 | 223.0 / 160.6 / 2.6 | 206.4 / 150.4 / 1.2 | 13.2 | 34202 | 0.408 |
| avenue | 408 | 384.3 | 2.49 | 233.3 / 3.7 / 0.0 | 215.1 / 1.2 / 0.0 | 0.0 | 28375 | 1.305 |
| exit | 40 | 9.7 | 0.00 | 258.0 / 251.2 / 208.8 | 224.2 / 208.7 / 82.4 | 1029.2 | 3464 | 0.853 |
| concourse | 612 | 609.0 | 6.01 | 230.0 / 192.7 / 128.4 | 208.3 / 186.8 / 109.1 | 23155.0 | 105570 | 0.156 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.58 | 218.8 / 216.4 / 209.0 | 218.8 / 216.4 / 206.4 | 103616.5 | 297591 | 0.054 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 18.5 | -10.5 | gangway | 0.94 | 5.83 | 219.7 | 210.4 | 173.3 | 888.2 | 0.043 |
| 2 | -18.5 | -10.5 | gangway | 0.94 | 5.91 | 217.4 | 213.9 | 162.7 | 830.4 | 0.046 |
| 3 | -10.5 | 17.5 | gangway | 0.95 | 5.87 | 218.8 | 216.4 | 157.2 | 802.8 | 0.045 |
| 4 | -10.5 | 18.5 | gangway | 0.94 | 5.89 | 219.3 | 212.7 | 155.1 | 791.4 | 0.043 |
| 5 | -10.5 | -20.5 | gangway | 0.96 | 5.83 | 211.5 | 203.8 | 144.8 | 773.1 | 0.044 |
| 6 | 10.5 | -18.5 | gangway | 0.94 | 6.07 | 205.7 | 200.4 | 150.2 | 766.7 | 0.057 |
| 7 | -20.5 | 10.5 | gangway | 0.96 | 5.87 | 212.7 | 207.4 | 144.1 | 751.7 | 0.044 |
| 8 | 10.5 | 18.5 | gangway | 0.94 | 5.73 | 216.4 | 209.2 | 147.4 | 740.0 | 0.044 |
| 9 | 17.5 | -10.5 | gangway | 0.95 | 5.76 | 217.6 | 215.5 | 146.6 | 737.0 | 0.047 |
| 10 | 10.5 | -21.5 | gangway | 0.95 | 6.02 | 214.4 | 205.5 | 134.5 | 733.7 | 0.052 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -9.5 | 18.5 | seat row | 0.50 | 7.58 | 215.8 | 214.1 | 206.4 | 731.7 | 0.025 |
| 2 | 18.5 | -9.5 | seat row | 0.50 | 7.48 | 212.9 | 211.1 | 205.2 | 721.0 | 0.025 |
| 3 | -18.5 | -9.5 | seat row | 0.50 | 7.46 | 211.8 | 210.6 | 203.8 | 713.7 | 0.026 |
| 4 | 9.5 | 18.5 | seat row | 0.50 | 7.55 | 212.7 | 211.3 | 203.1 | 713.2 | 0.026 |
| 5 | -8.5 | 18.5 | seat row | 0.50 | 7.20 | 209.5 | 207.8 | 199.4 | 664.8 | 0.021 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 353; agent-steps of seated agents on another row's clearway: 3947.

## Deposit check

Person-seconds deposited: 664975.7, of them in excluded cells: 4106.877.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 32788 overlapping pair-steps: p99 0.0036, max 0.0119 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0036 max 0.0119; venue-geometry 1: p99 0.0004 max 0.0004 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 5 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.01 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 150 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
