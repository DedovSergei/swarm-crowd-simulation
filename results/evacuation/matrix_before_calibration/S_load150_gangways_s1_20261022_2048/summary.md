# Experiment `S_load150_gangways_s1`

**Task 5.10 stage 4 (AMD 26.10.1): Task 5.8's model (the level spacing on the gangway inclines, --stair-flow off): venue S, 150% load (seed 1), standing also on the gangways**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 5592 agents (load 150.0%, requested 150%): every one of the 3728 seats and 1864 standing (spawnOvercrowdedCrowd, seed 1; below), buffer N = 8192, 1498 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 221485 evaluations, 4837 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.50)** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T20:48:26, 37.6 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Spawn (overcrowding)

| | |
|---|---|
| seated | 3728 (every seat) |
| standing | **1864** (requested round((1.50 - 1) x 3728) = 1864; at most 2831 = floor(2.5 p/m^2 x 1132.7 m^2)) |
| standing floor | walkway + rear concourse + gangways (the gangway-standing variant), 1132.7 m^2 |
| standing on the walkway / concourse / gangways | 436 / 1020 / 408 |
| **load** | **150.00%** of the seats (requested 150%) |
| standing crowd's mean density | 1.646 p/m^2 |
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 3.32, all circulation cells 3.32 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 1, 13977 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 688 | 120.3 |
| t90 | 1206 | 210.9 |
| t100 | 1498 | 262.0 |

t_p: the step by which ceil(p x 5592) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 528 | 61 | 13.6 | 240.8 | 24.6 | 48.9 | 13.5-23.4 |
| -x | 5.66 | 548 | 56 | 13.6 | 249.9 | 24.6 | 47.8 | 13.1-23.1 |
| +y | 5.66 | 535 | 59 | 13.6 | 244.0 | 24.6 | 51.0 | 13.1-23.1 |
| -y | 5.66 | 552 | 59 | 13.6 | 247.3 | 25.0 | 48.9 | 13.3-23.3 |
| door +x+y y | 1.20 | 437 | 667 | 1.2 | 251.5 | 87.2 | 130.4 | 140.5-150.4 |
| door +x+y x | 1.20 | 422 | 659 | 1.2 | 258.7 | 81.9 | 125.4 | 133.1-143.1 |
| door -x+y y | 1.20 | 431 | 676 | 1.0 | 262.0 | 82.5 | 135.4 | 152.2-162.1 |
| door -x+y x | 1.20 | 431 | 670 | 1.2 | 255.5 | 84.7 | 120.4 | 141.0-150.9 |
| door -x-y y | 1.20 | 421 | 669 | 0.9 | 258.5 | 81.6 | 130.4 | 158.6-168.6 |
| door -x-y x | 1.20 | 430 | 674 | 0.9 | 246.3 | 87.6 | 130.4 | 158.3-168.3 |
| door +x-y y | 1.20 | 429 | 666 | 1.0 | 241.2 | 89.3 | 130.4 | 141.7-151.6 |
| door +x-y x | 1.20 | 428 | 676 | 1.0 | 256.4 | 83.7 | 130.4 | 132.6-142.5 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 528 | 9.4% | 25.6% |
| -x | avenue | 5.66 | 548 | 9.8% | 26.5% |
| +y | avenue | 5.66 | 535 | 9.6% | 25.9% |
| -y | avenue | 5.66 | 552 | 9.9% | 26.7% |
| door +x+y y | door | 1.20 | 437 | 7.8% | 99.8% |
| door +x+y x | door | 1.20 | 422 | 7.5% | 96.3% |
| door -x+y y | door | 1.20 | 431 | 7.7% | 98.4% |
| door -x+y x | door | 1.20 | 431 | 7.7% | 98.4% |
| door -x-y y | door | 1.20 | 421 | 7.5% | 96.1% |
| door -x-y x | door | 1.20 | 430 | 7.7% | 98.2% |
| door +x-y y | door | 1.20 | 429 | 7.7% | 97.9% |
| door +x-y x | door | 1.20 | 428 | 7.7% | 97.7% |
| **doors (8)** | door | 9.60 | 3429 | 61.3% | |
| **avenues (4)** | avenue | 22.64 | 2163 | 38.7% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 262.0 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 47.5%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 484 | 8.7% | 474 | 8.5% |
| straight +x+y (x wing) 0 | straight | yes | 493 | 8.8% | 493 | 8.8% |
| corner +x+y | corner | **no** | 81 | 1.4% | 81 | 1.4% |
| straight -x+y (y wing) 0 | straight | yes | 494 | 8.8% | 494 | 8.8% |
| straight -x+y (x wing) 0 | straight | yes | 480 | 8.6% | 466 | 8.3% |
| corner -x+y | corner | **no** | 88 | 1.6% | 88 | 1.6% |
| straight -x-y (y wing) 0 | straight | yes | 483 | 8.6% | 483 | 8.6% |
| straight -x-y (x wing) 0 | straight | yes | 477 | 8.5% | 475 | 8.5% |
| corner -x-y | corner | **no** | 88 | 1.6% | 88 | 1.6% |
| straight +x-y (y wing) 0 | straight | yes | 479 | 8.6% | 478 | 8.5% |
| straight +x-y (x wing) 0 | straight | yes | 485 | 8.7% | 485 | 8.7% |
| corner +x-y | corner | **no** | 82 | 1.5% | 82 | 1.5% |
| **straight (8)** | | | 3875 | | 3848 | 68.8% |
| **corner (4)** | | | 339 | | 339 | 6.1% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 1405, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 528 | 13.6 | 240.8 | 0.29 | 0.59 | 0.0% |
| -x | 548 | 13.6 | 249.9 | 0.29 | 0.57 | 0.0% |
| +y | 535 | 13.6 | 244.0 | 0.29 | 0.61 | 0.0% |
| -y | 552 | 13.6 | 247.3 | 0.30 | 0.59 | 0.0% |
| door +x+y y | 437 | 1.2 | 251.5 | 1.04 | 1.56 | 84.6% |
| door +x+y x | 422 | 1.2 | 258.7 | 0.98 | 1.50 | 80.8% |
| door -x+y y | 431 | 1.0 | 262.0 | 0.99 | 1.62 | 81.5% |
| door -x+y x | 431 | 1.2 | 255.5 | 1.01 | 1.44 | 88.5% |
| door -x-y y | 421 | 0.9 | 258.5 | 0.98 | 1.56 | 84.6% |
| door -x-y x | 430 | 0.9 | 246.3 | 1.05 | 1.56 | 92.0% |
| door +x-y y | 429 | 1.0 | 241.2 | 1.07 | 1.56 | 88.0% |
| door +x-y x | 428 | 1.0 | 256.4 | 1.00 | 1.56 | 84.6% |

Mean flow / w J averaged over the doors 1.01, over the avenues 0.30.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 484 | 316 / 168 / 19 | 0.2 | 248.5 | 2.02 | 3.11 | 88% | 84% | 4% | 4.37 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 483 | 304 / 189 / 41 | 0.2 | 255.7 | 2.09 | 3.81 | 77% | 77% | 0% | 4.40 |
| corner +x+y | 1.20 | 31.2 | 81 | 4 / 79 / 0 | 0.2 | 99.7 | 0.83 | 1.10 | 10% | 0% | 10% | 1.61 |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 480 | 295 / 199 / 51 | 0.2 | 259.0 | 2.10 | 3.71 | 77% | 77% | 0% | 4.44 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 480 | 310 / 170 / 32 | 0.2 | 252.6 | 2.03 | 3.61 | 85% | 85% | 0% | 4.48 |
| corner -x+y | 1.20 | 31.2 | 88 | 3 / 86 / 0 | 0.2 | 98.8 | 0.90 | 1.30 | 10% | 0% | 10% | 1.86 |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 481 | 296 / 187 / 34 | 0.2 | 255.5 | 2.02 | 3.41 | 77% | 77% | 0% | 4.59 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 477 | 294 / 183 / 31 | 0.2 | 243.3 | 2.09 | 3.51 | 88% | 88% | 0% | 4.38 |
| corner -x-y | 1.20 | 31.2 | 88 | 2 / 86 / 0 | 0.2 | 98.6 | 0.89 | 1.20 | 20% | 10% | 10% | 2.04 |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 479 | 300 / 180 / 32 | 0.2 | 238.2 | 2.15 | 3.31 | 88% | 88% | 0% | 4.45 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 484 | 301 / 185 / 35 | 0.2 | 253.4 | 2.06 | 3.71 | 77% | 77% | 0% | 4.54 |
| corner +x-y | 1.20 | 31.2 | 82 | 5 / 78 / 0 | 0.2 | 94.4 | 0.88 | 1.20 | 10% | 0% | 10% | 1.63 |

The last agent out (agent 1541, t100 262.0 s): last gangway straight -x+y (y wing) 0, exit door -x+y (y wall). The gangway that cleared last: straight -x+y (y wing) 0 at 259.0 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.44 | 260.6 / 249.9 / 217.1 | 234.4 / 227.2 / 179.8 | 83505.6 | 339433 | 0.271 |
| gangway | 392 | 351.5 | 6.44 | 257.3 / 229.5 / 206.0 | 234.4 / 227.2 / 179.8 | 70012.6 | 198021 | 0.114 |
| walkway | 276 | 257.4 | 5.06 | 232.8 / 161.4 / 1.0 | 220.6 / 148.8 / 1.0 | 5.3 | 32594 | 0.440 |
| avenue | 408 | 384.3 | 2.51 | 230.7 / 5.6 / 0.0 | 211.3 / 1.0 / 0.0 | 0.0 | 28240 | 1.306 |
| exit | 40 | 9.7 | 0.00 | 257.8 / 249.9 / 196.1 | 216.9 / 194.8 / 70.5 | 903.3 | 3298 | 0.910 |
| concourse | 612 | 609.0 | 5.96 | 230.7 / 164.1 / 103.7 | 198.3 / 160.4 / 74.0 | 12584.5 | 77281 | 0.197 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.56 | 220.7 / 219.5 / 210.8 | 220.7 / 219.5 / 210.8 | 112032.7 | 323966 | 0.050 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -18.5 | 10.5 | gangway | 0.94 | 6.07 | 222.0 | 215.5 | 179.8 | 930.0 | 0.040 |
| 2 | 10.5 | 18.5 | gangway | 0.94 | 5.91 | 214.6 | 208.3 | 171.8 | 879.2 | 0.042 |
| 3 | 10.5 | 17.5 | gangway | 0.95 | 5.82 | 220.9 | 215.8 | 171.4 | 865.5 | 0.047 |
| 4 | 10.5 | -18.5 | gangway | 0.94 | 5.76 | 219.9 | 215.8 | 171.6 | 864.8 | 0.047 |
| 5 | -10.5 | -18.5 | gangway | 0.94 | 5.93 | 209.7 | 203.1 | 166.3 | 848.7 | 0.050 |
| 6 | -18.5 | -10.5 | gangway | 0.94 | 5.84 | 221.6 | 217.8 | 164.4 | 832.7 | 0.043 |
| 7 | -17.5 | 10.5 | gangway | 0.95 | 5.62 | 223.4 | 219.9 | 162.3 | 823.6 | 0.043 |
| 8 | 10.5 | -17.5 | gangway | 0.95 | 5.76 | 216.4 | 211.5 | 155.1 | 787.6 | 0.050 |
| 9 | 18.5 | 10.5 | gangway | 0.94 | 5.96 | 205.3 | 195.2 | 154.8 | 785.8 | 0.056 |
| 10 | -10.5 | -17.5 | gangway | 0.95 | 5.80 | 211.8 | 207.8 | 151.3 | 764.8 | 0.057 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -18.5 | -9.5 | seat row | 0.50 | 7.40 | 218.6 | 216.7 | 210.8 | 741.1 | 0.025 |
| 2 | -18.5 | 9.5 | seat row | 0.50 | 7.50 | 217.2 | 216.0 | 207.8 | 728.3 | 0.025 |
| 3 | 9.5 | 18.5 | seat row | 0.50 | 7.49 | 211.3 | 210.8 | 205.7 | 727.8 | 0.025 |
| 4 | 9.5 | -18.5 | seat row | 0.50 | 7.41 | 214.6 | 213.0 | 206.0 | 724.3 | 0.025 |
| 5 | 18.5 | -9.5 | seat row | 0.50 | 7.48 | 206.4 | 205.2 | 201.7 | 710.4 | 0.026 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 272; agent-steps of seated agents on another row's clearway: 3076.

## Deposit check

Person-seconds deposited: 666366.9, of them in excluded cells: 2967.777.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 36029 overlapping pair-steps: p99 0.0063, max 0.0125 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0063 max 0.0125; venue-geometry 6: p99 0.0006 max 0.0006 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 13 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 5.96 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 109 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
