# Experiment `S_load150_gangways_s1`

**Task 5.8 stage 2: venue S, 150% load (seed 1): standing also on the gangways**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 5592 agents (load 150.0%, requested 150%): every one of the 3728 seats and 1864 standing (spawnOvercrowdedCrowd, seed 1; below), buffer N = 8192, 1494 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 221331 evaluations, 4811 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.50)** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `cd8e0bbf3411846ca7aa6719887d122a142a7ca1`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-15T16:23:38, 15.2 s wall.

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
| t50 | 685 | 119.8 |
| t90 | 1206 | 210.9 |
| t100 | 1494 | 261.3 |

t_p: the step by which ceil(p x 5592) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 537 | 61 | 13.6 | 241.0 | 25.0 | 48.9 | 13.5-23.4 |
| -x | 5.66 | 551 | 56 | 13.6 | 247.3 | 25.0 | 47.8 | 13.1-23.1 |
| +y | 5.66 | 541 | 59 | 13.6 | 248.2 | 24.4 | 51.0 | 13.1-23.1 |
| -y | 5.66 | 548 | 59 | 13.6 | 243.6 | 25.2 | 48.9 | 13.3-23.3 |
| door +x+y y | 1.20 | 434 | 667 | 1.2 | 244.0 | 89.3 | 135.4 | 143.6-153.6 |
| door +x+y x | 1.20 | 413 | 659 | 1.2 | 259.9 | 79.8 | 125.4 | 140.5-150.4 |
| door -x+y y | 1.20 | 427 | 676 | 1.0 | 260.3 | 82.3 | 130.4 | 155.1-165.1 |
| door -x+y x | 1.20 | 430 | 670 | 1.2 | 251.9 | 85.7 | 125.4 | 145.0-155.0 |
| door -x-y y | 1.20 | 418 | 669 | 0.9 | 261.3 | 80.2 | 130.4 | 156.2-166.2 |
| door -x-y x | 1.20 | 433 | 674 | 0.9 | 250.1 | 86.8 | 135.4 | 149.7-159.7 |
| door +x-y y | 1.20 | 438 | 666 | 1.0 | 239.6 | 91.7 | 135.4 | 136.1-146.0 |
| door +x-y x | 1.20 | 422 | 676 | 1.0 | 240.1 | 88.2 | 135.4 | 133.6-143.6 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 537 | 9.6% | 26.1% |
| -x | avenue | 5.66 | 551 | 9.9% | 26.7% |
| +y | avenue | 5.66 | 541 | 9.7% | 26.3% |
| -y | avenue | 5.66 | 548 | 9.8% | 26.6% |
| door +x+y y | door | 1.20 | 434 | 7.8% | 99.3% |
| door +x+y x | door | 1.20 | 413 | 7.4% | 94.5% |
| door -x+y y | door | 1.20 | 427 | 7.6% | 97.7% |
| door -x+y x | door | 1.20 | 430 | 7.7% | 98.4% |
| door -x-y y | door | 1.20 | 418 | 7.5% | 95.7% |
| door -x-y x | door | 1.20 | 433 | 7.7% | 99.1% |
| door +x-y y | door | 1.20 | 438 | 7.8% | 100.2% |
| door +x-y x | door | 1.20 | 422 | 7.5% | 96.6% |
| **doors (8)** | door | 9.60 | 3415 | 61.1% | |
| **avenues (4)** | avenue | 22.64 | 2177 | 38.9% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 261.3 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 47.6%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 484 | 8.7% | 479 | 8.6% |
| straight +x+y (x wing) 0 | straight | yes | 488 | 8.7% | 488 | 8.7% |
| corner +x+y | corner | **no** | 81 | 1.4% | 81 | 1.4% |
| straight -x+y (y wing) 0 | straight | yes | 487 | 8.7% | 487 | 8.7% |
| straight -x+y (x wing) 0 | straight | yes | 480 | 8.6% | 473 | 8.5% |
| corner -x+y | corner | **no** | 88 | 1.6% | 88 | 1.6% |
| straight -x-y (y wing) 0 | straight | yes | 485 | 8.7% | 485 | 8.7% |
| straight -x-y (x wing) 0 | straight | yes | 478 | 8.5% | 474 | 8.5% |
| corner -x-y | corner | **no** | 87 | 1.6% | 87 | 1.6% |
| straight +x-y (y wing) 0 | straight | yes | 479 | 8.6% | 479 | 8.6% |
| straight +x-y (x wing) 0 | straight | yes | 484 | 8.7% | 484 | 8.7% |
| corner +x-y | corner | **no** | 82 | 1.5% | 82 | 1.5% |
| **straight (8)** | | | 3865 | | 3849 | 68.8% |
| **corner (4)** | | | 338 | | 338 | 6.0% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 1405, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 537 | 13.6 | 241.0 | 0.30 | 0.59 | 0.0% |
| -x | 551 | 13.6 | 247.3 | 0.30 | 0.57 | 0.0% |
| +y | 541 | 13.6 | 248.2 | 0.29 | 0.61 | 0.0% |
| -y | 548 | 13.6 | 243.6 | 0.30 | 0.59 | 0.0% |
| door +x+y y | 434 | 1.2 | 244.0 | 1.07 | 1.62 | 88.0% |
| door +x+y x | 413 | 1.2 | 259.9 | 0.95 | 1.50 | 81.5% |
| door -x+y y | 427 | 1.0 | 260.3 | 0.98 | 1.56 | 81.5% |
| door -x+y x | 430 | 1.2 | 251.9 | 1.03 | 1.50 | 84.6% |
| door -x-y y | 418 | 0.9 | 261.3 | 0.96 | 1.56 | 81.5% |
| door -x-y x | 433 | 0.9 | 250.1 | 1.04 | 1.62 | 88.5% |
| door +x-y y | 438 | 1.0 | 239.6 | 1.10 | 1.62 | 88.0% |
| door +x-y x | 422 | 1.0 | 240.1 | 1.05 | 1.62 | 88.0% |

Mean flow / w J averaged over the doors 1.02, over the avenues 0.30.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 484 | 313 / 173 / 17 | 0.2 | 241.0 | 2.09 | 3.11 | 88% | 84% | 4% | 4.46 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 483 | 295 / 193 / 45 | 0.2 | 256.9 | 2.07 | 3.61 | 77% | 77% | 0% | 4.48 |
| corner +x+y | 1.20 | 31.2 | 81 | 4 / 79 / 0 | 0.2 | 102.0 | 0.81 | 1.30 | 9% | 0% | 9% | 1.61 |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 480 | 291 / 196 / 49 | 0.2 | 257.3 | 2.08 | 3.61 | 77% | 77% | 0% | 4.51 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 480 | 309 / 171 / 25 | 0.2 | 248.9 | 2.03 | 3.31 | 84% | 84% | 0% | 4.59 |
| corner -x+y | 1.20 | 31.2 | 88 | 3 / 86 / 0 | 0.2 | 95.5 | 0.93 | 1.50 | 10% | 0% | 10% | 1.86 |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 481 | 293 / 192 / 38 | 0.2 | 258.3 | 2.02 | 3.71 | 77% | 77% | 0% | 4.53 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 478 | 297 / 181 / 31 | 0.2 | 247.1 | 2.06 | 3.61 | 84% | 84% | 0% | 4.55 |
| corner -x-y | 1.20 | 31.2 | 87 | 2 / 85 / 0 | 0.2 | 100.0 | 0.87 | 1.20 | 18% | 9% | 9% | 2.04 |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 479 | 309 / 171 / 21 | 0.2 | 236.6 | 2.12 | 3.31 | 88% | 88% | 0% | 4.42 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 484 | 294 / 190 / 39 | 0.2 | 237.2 | 2.21 | 3.61 | 83% | 83% | 0% | 4.59 |
| corner +x-y | 1.20 | 31.2 | 82 | 5 / 78 / 0 | 0.2 | 92.5 | 0.90 | 1.20 | 10% | 0% | 10% | 1.63 |

The last agent out (agent 2398, t100 261.3 s): last gangway straight -x-y (y wing) 0, exit door -x-y (y wall). The gangway that cleared last: straight -x-y (y wing) 0 at 258.3 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.46 | 260.8 / 246.6 / 213.7 | 236.5 / 226.9 / 173.2 | 83894.5 | 339339 | 0.272 |
| gangway | 392 | 351.5 | 6.46 | 257.5 / 228.4 / 200.3 | 236.5 / 226.9 / 173.2 | 70907.7 | 198821 | 0.113 |
| walkway | 276 | 257.4 | 4.81 | 232.1 / 168.3 / 0.0 | 216.0 / 156.7 / 0.0 | 0.0 | 31943 | 0.450 |
| avenue | 408 | 384.3 | 2.51 | 234.5 / 5.6 / 0.0 | 222.0 / 1.0 / 0.0 | 0.0 | 28435 | 1.305 |
| exit | 40 | 9.7 | 0.00 | 255.2 / 246.4 / 199.4 | 216.5 / 193.8 / 74.2 | 898.2 | 3290 | 0.910 |
| concourse | 612 | 609.0 | 5.93 | 229.1 / 161.4 / 100.4 | 195.0 / 159.5 / 72.1 | 12088.7 | 76850 | 0.198 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.53 | 216.7 / 215.5 / 211.1 | 216.7 / 215.5 / 210.8 | 111486.1 | 323595 | 0.050 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 10.5 | 18.5 | gangway | 0.94 | 5.87 | 222.7 | 214.1 | 173.2 | 883.2 | 0.044 |
| 2 | -18.5 | 10.5 | gangway | 0.94 | 5.91 | 220.4 | 217.6 | 169.1 | 869.9 | 0.042 |
| 3 | -17.5 | 10.5 | gangway | 0.95 | 5.80 | 217.2 | 213.0 | 166.9 | 845.3 | 0.044 |
| 4 | -18.5 | -10.5 | gangway | 0.94 | 5.86 | 220.2 | 214.8 | 164.4 | 843.4 | 0.040 |
| 5 | -10.5 | -18.5 | gangway | 0.94 | 5.77 | 212.7 | 207.3 | 162.3 | 815.5 | 0.050 |
| 6 | -18.5 | 11.5 | gangway | 0.86 | 6.46 | 201.8 | 198.3 | 164.2 | 803.9 | 0.038 |
| 7 | -17.5 | -10.5 | gangway | 0.95 | 5.72 | 217.9 | 215.1 | 158.1 | 803.2 | 0.047 |
| 8 | 10.5 | 17.5 | gangway | 0.95 | 5.79 | 220.4 | 215.0 | 153.2 | 771.7 | 0.048 |
| 9 | 18.5 | -10.5 | gangway | 0.94 | 5.79 | 213.2 | 205.0 | 151.5 | 763.5 | 0.052 |
| 10 | -19.5 | -11.5 | gangway | 0.92 | 5.97 | 191.9 | 187.2 | 150.1 | 754.7 | 0.033 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -18.5 | -9.5 | seat row | 0.50 | 7.51 | 216.7 | 215.5 | 210.8 | 740.3 | 0.025 |
| 2 | 9.5 | 18.5 | seat row | 0.50 | 7.53 | 215.1 | 214.1 | 208.3 | 730.7 | 0.025 |
| 3 | -18.5 | 9.5 | seat row | 0.50 | 7.50 | 216.2 | 214.8 | 204.3 | 720.5 | 0.025 |
| 4 | -9.5 | -18.5 | seat row | 0.50 | 7.51 | 206.2 | 204.8 | 200.3 | 702.3 | 0.026 |
| 5 | 18.5 | -9.5 | seat row | 0.50 | 7.51 | 206.2 | 205.0 | 201.0 | 701.9 | 0.027 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 260; agent-steps of seated agents on another row's clearway: 2909.

## Deposit check

Person-seconds deposited: 665872.5, of them in excluded cells: 2938.648.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 39674 overlapping pair-steps: p99 0.0043, max 0.0119 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0043 max 0.0119; venue-geometry 3: p99 0.0003 max 0.0003 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 10 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 5.93 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 102 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
