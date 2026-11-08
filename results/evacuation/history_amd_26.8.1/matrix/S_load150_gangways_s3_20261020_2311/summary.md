# Experiment `S_load150_gangways_s3`

**Task 5.9 stage 4: venue S, 150% load (seed 3): standing also on the gangways**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 5592 agents (load 150.0%, requested 150%): every one of the 3728 seats and 1864 standing (spawnOvercrowdedCrowd, seed 3; below), buffer N = 8192, 1711 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 234325 evaluations, 4851 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.50)** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-20T23:11:55, 15.8 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Spawn (overcrowding)

| | |
|---|---|
| seated | 3728 (every seat) |
| standing | **1864** (requested round((1.50 - 1) x 3728) = 1864; at most 2831 = floor(2.5 p/m^2 x 1132.7 m^2)) |
| standing floor | walkway + rear concourse + gangways (the gangway-standing variant), 1132.7 m^2 |
| standing on the walkway / concourse / gangways | 413 / 1015 / 436 |
| **load** | **150.00%** of the seats (requested 150%) |
| standing crowd's mean density | 1.646 p/m^2 |
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 3.29, all circulation cells 3.29 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 3, 14021 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 687 | 120.2 |
| t90 | 1359 | 237.7 |
| t100 | 1711 | 299.3 |

t_p: the step by which ceil(p x 5592) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 535 | 54 | 13.5 | 281.1 | 21.2 | 43.6 | 13.3-23.3 |
| -x | 5.66 | 546 | 60 | 13.6 | 278.6 | 21.8 | 53.2 | 13.3-23.3 |
| +y | 5.66 | 548 | 63 | 13.5 | 271.5 | 22.5 | 50.0 | 13.1-23.1 |
| -y | 5.66 | 557 | 53 | 13.6 | 282.5 | 21.9 | 40.4 | 13.1-23.1 |
| door +x+y y | 1.20 | 419 | 664 | 0.9 | 292.8 | 71.7 | 130.4 | 131.7-141.7 |
| door +x+y x | 1.20 | 430 | 673 | 0.9 | 283.3 | 76.1 | 120.4 | 120.7-130.7 |
| door -x+y y | 1.20 | 421 | 671 | 1.4 | 280.0 | 75.5 | 120.4 | 123.1-133.1 |
| door -x+y x | 1.20 | 435 | 674 | 0.9 | 285.1 | 76.5 | 120.4 | 121.4-131.4 |
| door -x-y y | 1.20 | 433 | 678 | 1.0 | 276.0 | 78.7 | 120.4 | 130.1-140.1 |
| door -x-y x | 1.20 | 417 | 664 | 0.9 | 299.3 | 69.8 | 115.3 | 119.1-129.1 |
| door +x-y y | 1.20 | 428 | 670 | 0.9 | 279.2 | 76.9 | 125.4 | 132.4-142.4 |
| door +x-y x | 1.20 | 423 | 668 | 1.0 | 298.6 | 71.0 | 110.3 | 95.1-105.1 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 535 | 9.6% | 22.7% |
| -x | avenue | 5.66 | 546 | 9.8% | 23.1% |
| +y | avenue | 5.66 | 548 | 9.8% | 23.2% |
| -y | avenue | 5.66 | 557 | 10.0% | 23.6% |
| door +x+y y | door | 1.20 | 419 | 7.5% | 83.7% |
| door +x+y x | door | 1.20 | 430 | 7.7% | 85.9% |
| door -x+y y | door | 1.20 | 421 | 7.5% | 84.1% |
| door -x+y x | door | 1.20 | 435 | 7.8% | 86.9% |
| door -x-y y | door | 1.20 | 433 | 7.7% | 86.5% |
| door -x-y x | door | 1.20 | 417 | 7.5% | 83.3% |
| door +x-y y | door | 1.20 | 428 | 7.7% | 85.5% |
| door +x-y x | door | 1.20 | 423 | 7.6% | 84.5% |
| **doors (8)** | door | 9.60 | 3406 | 60.9% | |
| **avenues (4)** | avenue | 22.64 | 2186 | 39.1% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 299.3 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 41.6%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 479 | 8.6% | 479 | 8.6% |
| straight +x+y (x wing) 0 | straight | yes | 486 | 8.7% | 484 | 8.7% |
| corner +x+y | corner | **no** | 86 | 1.5% | 86 | 1.5% |
| straight -x+y (y wing) 0 | straight | yes | 480 | 8.6% | 480 | 8.6% |
| straight -x+y (x wing) 0 | straight | yes | 486 | 8.7% | 486 | 8.7% |
| corner -x+y | corner | **no** | 95 | 1.7% | 95 | 1.7% |
| straight -x-y (y wing) 0 | straight | yes | 486 | 8.7% | 481 | 8.6% |
| straight -x-y (x wing) 0 | straight | yes | 487 | 8.7% | 487 | 8.7% |
| corner -x-y | corner | **no** | 85 | 1.5% | 85 | 1.5% |
| straight +x-y (y wing) 0 | straight | yes | 485 | 8.7% | 478 | 8.5% |
| straight +x-y (x wing) 0 | straight | yes | 492 | 8.8% | 492 | 8.8% |
| corner +x-y | corner | **no** | 80 | 1.4% | 80 | 1.4% |
| **straight (8)** | | | 3881 | | 3867 | 69.2% |
| **corner (4)** | | | 346 | | 346 | 6.2% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 1379, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 535 | 13.5 | 281.1 | 0.25 | 0.52 | 0.0% |
| -x | 546 | 13.6 | 278.6 | 0.26 | 0.64 | 0.0% |
| +y | 548 | 13.5 | 271.5 | 0.27 | 0.60 | 0.0% |
| -y | 557 | 13.6 | 282.5 | 0.26 | 0.48 | 0.0% |
| door +x+y y | 419 | 0.9 | 292.8 | 0.86 | 1.56 | 60.0% |
| door +x+y x | 430 | 0.9 | 283.3 | 0.91 | 1.44 | 69.0% |
| door -x+y y | 421 | 1.4 | 280.0 | 0.90 | 1.44 | 58.6% |
| door -x+y x | 435 | 0.9 | 285.1 | 0.91 | 1.44 | 65.5% |
| door -x-y y | 433 | 1.0 | 276.0 | 0.94 | 1.44 | 75.0% |
| door -x-y x | 417 | 0.9 | 299.3 | 0.84 | 1.38 | 58.1% |
| door +x-y y | 428 | 0.9 | 279.2 | 0.92 | 1.50 | 71.4% |
| door +x-y x | 423 | 1.0 | 298.6 | 0.85 | 1.32 | 53.3% |

Mean flow / w J averaged over the doors 0.89, over the avenues 0.26.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 477 | 291 / 188 / 55 | 0.2 | 289.8 | 1.84 | 2.91 | 80% | 77% | 3% | 3.97 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 486 | 306 / 180 / 42 | 0.2 | 280.4 | 1.88 | 2.81 | 86% | 83% | 3% | 4.05 |
| corner +x+y | 1.20 | 31.2 | 86 | 4 / 83 / 0 | 0.2 | 118.6 | 0.73 | 1.30 | 17% | 8% | 8% | 1.87 |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 480 | 288 / 194 / 61 | 0.2 | 277.1 | 1.96 | 2.81 | 86% | 82% | 4% | 3.92 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 486 | 312 / 174 / 41 | 0.2 | 282.1 | 1.87 | 3.01 | 83% | 83% | 0% | 4.10 |
| corner -x+y | 1.20 | 31.2 | 95 | 10 / 87 / 0 | 0.2 | 122.8 | 0.79 | 1.20 | 15% | 8% | 8% | 2.20 |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 486 | 305 / 181 / 49 | 0.2 | 273.0 | 1.96 | 3.21 | 89% | 89% | 0% | 4.06 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 482 | 295 / 192 / 47 | 0.2 | 296.3 | 1.80 | 2.71 | 80% | 77% | 3% | 3.90 |
| corner -x-y | 1.20 | 31.2 | 85 | 3 / 83 / 0 | 0.2 | 111.6 | 0.77 | 1.10 | 8% | 0% | 8% | 1.71 |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 485 | 301 / 184 / 37 | 0.2 | 276.2 | 1.89 | 2.91 | 89% | 89% | 0% | 4.07 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 485 | 296 / 196 / 59 | 0.2 | 295.6 | 1.86 | 3.41 | 80% | 77% | 3% | 3.91 |
| corner +x-y | 1.20 | 31.2 | 80 | 3 / 78 / 0 | 0.2 | 107.7 | 0.75 | 1.20 | 18% | 0% | 18% | 1.94 |

The last agent out (agent 1979, t100 299.3 s): last gangway straight -x-y (x wing) 0, exit door -x-y (x wall). The gangway that cleared last: straight -x-y (x wing) 0 at 296.3 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.52 | 291.4 / 281.6 / 239.4 | 264.8 / 259.2 / 190.5 | 81817.5 | 334319 | 0.273 |
| gangway | 392 | 351.5 | 6.52 | 278.5 / 262.9 / 214.3 | 264.8 / 259.2 / 190.5 | 71406.4 | 209411 | 0.102 |
| walkway | 276 | 257.4 | 5.00 | 171.9 / 126.8 / 0.0 | 141.0 / 110.7 / 0.0 | 0.0 | 24191 | 0.595 |
| avenue | 408 | 384.3 | 2.40 | 181.4 / 9.1 / 0.0 | 152.3 / 0.7 / 0.0 | 0.0 | 28493 | 1.310 |
| exit | 40 | 9.7 | 0.00 | 289.6 / 280.4 / 198.0 | 212.5 / 181.2 / 68.4 | 835.7 | 3198 | 0.950 |
| concourse | 612 | 609.0 | 5.92 | 239.4 / 137.3 / 87.1 | 151.3 / 134.3 / 62.4 | 9575.3 | 69025 | 0.220 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.58 | 255.4 / 252.6 / 245.2 | 255.4 / 252.6 / 244.2 | 127402.4 | 367564 | 0.044 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -18.5 | 10.5 | gangway | 0.94 | 6.01 | 248.9 | 243.8 | 190.5 | 976.2 | 0.031 |
| 2 | -10.5 | -18.5 | gangway | 0.94 | 5.76 | 254.1 | 251.2 | 187.5 | 948.1 | 0.029 |
| 3 | 18.5 | 10.5 | gangway | 0.94 | 6.04 | 252.4 | 248.7 | 181.7 | 928.7 | 0.029 |
| 4 | -19.5 | 11.5 | gangway | 0.92 | 5.99 | 241.4 | 237.2 | 172.5 | 885.7 | 0.022 |
| 5 | 10.5 | -18.5 | gangway | 0.94 | 5.66 | 258.9 | 249.1 | 178.4 | 885.1 | 0.031 |
| 6 | -10.5 | 19.5 | gangway | 0.96 | 5.68 | 242.4 | 233.2 | 168.4 | 857.6 | 0.030 |
| 7 | -18.5 | 11.5 | gangway | 0.86 | 6.46 | 234.4 | 231.6 | 174.4 | 855.8 | 0.028 |
| 8 | -11.5 | -18.5 | gangway | 0.86 | 5.92 | 240.1 | 238.0 | 176.3 | 845.4 | 0.029 |
| 9 | 10.5 | 19.5 | gangway | 0.96 | 5.78 | 245.2 | 239.4 | 161.3 | 839.9 | 0.030 |
| 10 | 10.5 | 18.5 | gangway | 0.94 | 6.03 | 235.6 | 228.3 | 158.8 | 815.6 | 0.037 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 18.5 | 9.5 | seat row | 0.50 | 7.45 | 249.6 | 248.0 | 241.4 | 857.9 | 0.021 |
| 2 | -9.5 | -18.5 | seat row | 0.50 | 7.21 | 251.5 | 249.8 | 244.2 | 838.7 | 0.022 |
| 3 | 9.5 | -18.5 | seat row | 0.50 | 7.38 | 255.4 | 252.6 | 237.7 | 832.8 | 0.021 |
| 4 | -18.5 | 9.5 | seat row | 0.50 | 7.29 | 247.1 | 245.2 | 235.8 | 820.6 | 0.022 |
| 5 | 8.5 | -18.5 | seat row | 0.50 | 7.17 | 248.7 | 245.4 | 233.3 | 797.4 | 0.018 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 391; agent-steps of seated agents on another row's clearway: 2524.

## Deposit check

Person-seconds deposited: 704628.8, of them in excluded cells: 2746.604.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 35268 overlapping pair-steps: p99 0.0048, max 0.0136 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0048 max 0.0136; venue-geometry 1: p99 0.0001 max 0.0001 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 6 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 5.92 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 100 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
