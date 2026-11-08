# Experiment `S_load150_s1`

**Task 5.10 stage 4 (AMD 26.10.1): Task 5.8's model (the level spacing on the gangway inclines, --stair-flow off): venue S, 150% requested (seed 1)**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 5592 agents (load 150.0%, requested 150%): every one of the 3728 seats and 1864 standing (spawnOvercrowdedCrowd, seed 1; below), buffer N = 8192, 1506 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 220907 evaluations, 4600 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.50)** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T20:46:45, 25.5 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Spawn (overcrowding)

| | |
|---|---|
| seated | 3728 (every seat) |
| standing | **1864** (requested round((1.50 - 1) x 3728) = 1864; at most 2143 = floor(2.5 p/m^2 x 857.4 m^2)) |
| standing floor | walkway + rear concourse, 857.4 m^2 |
| standing on the walkway / concourse / gangways | 556 / 1308 / 0 |
| **load** | **150.00%** of the seats (requested 150%) |
| standing crowd's mean density | 2.174 p/m^2 |
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 3.46, all circulation cells 3.46 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 1, 25138 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 685 | 119.8 |
| t90 | 1202 | 210.2 |
| t100 | 1506 | 263.4 |

t_p: the step by which ceil(p x 5592) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 524 | 79 | 13.6 | 237.9 | 24.8 | 54.2 | 12.9-22.9 |
| -x | 5.66 | 553 | 71 | 13.5 | 247.0 | 25.1 | 55.3 | 12.8-22.7 |
| +y | 5.66 | 546 | 78 | 13.6 | 244.7 | 25.0 | 58.5 | 13.5-23.4 |
| -y | 5.66 | 548 | 78 | 13.5 | 245.7 | 25.0 | 58.5 | 13.3-23.3 |
| door +x+y y | 1.20 | 418 | 653 | 1.0 | 253.6 | 82.7 | 120.4 | 165.3-175.3 |
| door +x+y x | 1.20 | 427 | 647 | 1.2 | 262.4 | 81.7 | 135.4 | 159.0-169.0 |
| door -x+y y | 1.20 | 428 | 672 | 1.0 | 260.8 | 82.3 | 140.4 | 169.0-178.9 |
| door -x+y x | 1.20 | 434 | 664 | 1.2 | 255.4 | 85.3 | 130.4 | 159.2-169.1 |
| door -x-y y | 1.20 | 426 | 662 | 0.9 | 263.4 | 81.1 | 135.4 | 166.3-176.3 |
| door -x-y x | 1.20 | 428 | 661 | 0.9 | 257.8 | 83.2 | 135.4 | 178.1-188.0 |
| door +x-y y | 1.20 | 436 | 670 | 0.9 | 247.5 | 88.3 | 135.4 | 168.1-178.1 |
| door +x-y x | 1.20 | 424 | 657 | 1.0 | 260.3 | 81.7 | 135.4 | 159.9-169.8 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 524 | 9.4% | 25.2% |
| -x | avenue | 5.66 | 553 | 9.9% | 26.6% |
| +y | avenue | 5.66 | 546 | 9.8% | 26.3% |
| -y | avenue | 5.66 | 548 | 9.8% | 26.4% |
| door +x+y y | door | 1.20 | 418 | 7.5% | 94.9% |
| door +x+y x | door | 1.20 | 427 | 7.6% | 97.0% |
| door -x+y y | door | 1.20 | 428 | 7.7% | 97.2% |
| door -x+y x | door | 1.20 | 434 | 7.8% | 98.5% |
| door -x-y y | door | 1.20 | 426 | 7.6% | 96.7% |
| door -x-y x | door | 1.20 | 428 | 7.7% | 97.2% |
| door +x-y y | door | 1.20 | 436 | 7.8% | 99.0% |
| door +x-y x | door | 1.20 | 424 | 7.6% | 96.3% |
| **doors (8)** | door | 9.60 | 3421 | 61.2% | |
| **avenues (4)** | avenue | 22.64 | 2171 | 38.8% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 263.4 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 47.3%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 452 | 8.1% | 441 | 7.9% |
| straight +x+y (x wing) 0 | straight | yes | 465 | 8.3% | 465 | 8.3% |
| corner +x+y | corner | **no** | 46 | 0.8% | 46 | 0.8% |
| straight -x+y (y wing) 0 | straight | yes | 456 | 8.2% | 456 | 8.2% |
| straight -x+y (x wing) 0 | straight | yes | 452 | 8.1% | 441 | 7.9% |
| corner -x+y | corner | **no** | 59 | 1.1% | 59 | 1.1% |
| straight -x-y (y wing) 0 | straight | yes | 459 | 8.2% | 459 | 8.2% |
| straight -x-y (x wing) 0 | straight | yes | 452 | 8.1% | 443 | 7.9% |
| corner -x-y | corner | **no** | 52 | 0.9% | 52 | 0.9% |
| straight +x-y (y wing) 0 | straight | yes | 450 | 8.0% | 442 | 7.9% |
| straight +x-y (x wing) 0 | straight | yes | 462 | 8.3% | 462 | 8.3% |
| corner +x-y | corner | **no** | 52 | 0.9% | 52 | 0.9% |
| **straight (8)** | | | 3648 | | 3609 | 64.5% |
| **corner (4)** | | | 209 | | 209 | 3.7% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 1774, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 524 | 13.6 | 237.9 | 0.30 | 0.65 | 0.0% |
| -x | 553 | 13.5 | 247.0 | 0.30 | 0.66 | 0.0% |
| +y | 546 | 13.6 | 244.7 | 0.30 | 0.70 | 0.0% |
| -y | 548 | 13.5 | 245.7 | 0.30 | 0.70 | 0.0% |
| door +x+y y | 418 | 1.0 | 253.6 | 0.99 | 1.44 | 84.6% |
| door +x+y x | 427 | 1.2 | 262.4 | 0.98 | 1.62 | 77.8% |
| door -x+y y | 428 | 1.0 | 260.8 | 0.98 | 1.68 | 81.5% |
| door -x+y x | 434 | 1.2 | 255.4 | 1.02 | 1.56 | 88.5% |
| door -x-y y | 426 | 0.9 | 263.4 | 0.97 | 1.62 | 81.5% |
| door -x-y x | 428 | 0.9 | 257.8 | 1.00 | 1.62 | 84.6% |
| door +x-y y | 436 | 0.9 | 247.5 | 1.06 | 1.62 | 92.0% |
| door +x-y x | 424 | 1.0 | 260.3 | 0.98 | 1.62 | 77.8% |

Mean flow / w J averaged over the doors 1.00, over the avenues 0.30.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 452 | 273 / 180 / 34 | 0.2 | 250.6 | 1.94 | 3.31 | 81% | 81% | 0% | 4.61 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 454 | 277 / 188 / 54 | 0.2 | 259.4 | 2.00 | 3.61 | 70% | 70% | 0% | 4.45 |
| corner +x+y | 1.20 | 31.2 | 46 | 0 / 46 / 0 | 4.2 | 77.0 | 0.63 | 1.00 | 12% | 0% | 12% | 0.60 |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 445 | 258 / 198 / 58 | 0.3 | 257.8 | 2.00 | 3.71 | 77% | 77% | 0% | 4.50 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 452 | 279 / 174 / 32 | 0.5 | 252.4 | 1.92 | 3.41 | 85% | 85% | 0% | 4.54 |
| corner -x+y | 1.20 | 31.2 | 59 | 0 / 59 / 0 | 4.4 | 83.1 | 0.75 | 1.00 | 11% | 0% | 11% | 0.72 |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 450 | 269 / 192 / 46 | 0.2 | 260.4 | 1.95 | 3.51 | 74% | 74% | 0% | 4.56 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 452 | 267 / 186 / 31 | 0.3 | 254.8 | 1.90 | 3.41 | 81% | 81% | 0% | 4.61 |
| corner -x-y | 1.20 | 31.2 | 52 | 0 / 52 / 0 | 4.2 | 75.4 | 0.73 | 1.10 | 12% | 0% | 12% | 0.70 |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 450 | 273 / 177 / 35 | 0.7 | 244.5 | 1.99 | 3.61 | 84% | 84% | 0% | 4.60 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 454 | 273 / 190 / 41 | 0.7 | 257.3 | 1.96 | 3.41 | 77% | 77% | 0% | 4.59 |
| corner +x-y | 1.20 | 31.2 | 52 | 0 / 52 / 0 | 4.2 | 79.8 | 0.69 | 1.00 | 12% | 0% | 12% | 0.62 |

The last agent out (agent 2472, t100 263.4 s): last gangway straight -x-y (y wing) 0, exit door -x-y (y wall). The gangway that cleared last: straight -x-y (y wing) 0 at 260.4 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.52 | 262.9 / 252.7 / 216.5 | 231.9 / 226.3 / 175.4 | 95181.9 | 362202 | 0.251 |
| gangway | 392 | 351.5 | 6.52 | 259.6 / 231.2 / 202.9 | 231.9 / 226.3 / 175.4 | 70514.8 | 191925 | 0.109 |
| walkway | 276 | 257.4 | 5.29 | 235.2 / 166.5 / 5.4 | 217.1 / 152.3 / 5.2 | 30.3 | 35641 | 0.392 |
| avenue | 408 | 384.3 | 2.66 | 232.6 / 7.9 / 0.0 | 213.9 / 1.6 / 0.0 | 0.0 | 28346 | 1.305 |
| exit | 40 | 9.7 | 0.00 | 260.1 / 252.2 / 206.7 | 223.7 / 204.8 / 79.8 | 994.6 | 3432 | 0.866 |
| concourse | 612 | 609.0 | 6.09 | 229.0 / 180.5 / 127.9 | 212.3 / 180.5 / 109.1 | 23642.2 | 102857 | 0.158 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.60 | 216.4 / 215.3 / 209.2 | 216.4 / 215.3 / 206.6 | 104941.5 | 298487 | 0.054 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -18.5 | -10.5 | gangway | 0.94 | 6.04 | 217.4 | 212.5 | 175.4 | 901.7 | 0.042 |
| 2 | -18.5 | 10.5 | gangway | 0.94 | 5.94 | 216.9 | 213.9 | 168.1 | 866.3 | 0.041 |
| 3 | 10.5 | -18.5 | gangway | 0.94 | 6.01 | 215.5 | 212.9 | 159.3 | 827.5 | 0.041 |
| 4 | 10.5 | 18.5 | gangway | 0.94 | 5.85 | 218.1 | 212.9 | 160.9 | 815.5 | 0.044 |
| 5 | -17.5 | 10.5 | gangway | 0.95 | 5.85 | 220.4 | 217.1 | 158.3 | 803.2 | 0.045 |
| 6 | -19.5 | -11.5 | gangway | 0.92 | 5.96 | 207.4 | 199.0 | 150.8 | 748.0 | 0.037 |
| 7 | -20.5 | 10.5 | gangway | 0.96 | 5.74 | 220.2 | 210.6 | 143.6 | 745.1 | 0.045 |
| 8 | -19.5 | 11.5 | gangway | 0.92 | 5.82 | 197.1 | 191.0 | 147.8 | 742.7 | 0.036 |
| 9 | -10.5 | -18.5 | gangway | 0.94 | 5.88 | 201.0 | 195.2 | 145.2 | 736.3 | 0.058 |
| 10 | 10.5 | 17.5 | gangway | 0.95 | 5.72 | 223.4 | 218.8 | 147.3 | 735.3 | 0.051 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -18.5 | 9.5 | seat row | 0.50 | 7.60 | 216.4 | 215.1 | 206.6 | 735.2 | 0.025 |
| 2 | 9.5 | -18.5 | seat row | 0.50 | 7.44 | 211.5 | 210.8 | 205.9 | 721.6 | 0.025 |
| 3 | -18.5 | -9.5 | seat row | 0.50 | 7.55 | 214.8 | 212.9 | 204.1 | 718.4 | 0.025 |
| 4 | 9.5 | 18.5 | seat row | 0.50 | 7.47 | 215.8 | 215.3 | 203.6 | 715.6 | 0.025 |
| 5 | -18.5 | 8.5 | seat row | 0.50 | 7.08 | 210.2 | 206.2 | 197.1 | 662.4 | 0.022 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 330; agent-steps of seated agents on another row's clearway: 4176.

## Deposit check

Person-seconds deposited: 664647.1, of them in excluded cells: 3958.981.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 26355 overlapping pair-steps: p99 0.0049, max 0.0182 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0049 max 0.0182; venue-geometry 3: p99 0.0003 max 0.0003 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 5 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.09 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 135 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
