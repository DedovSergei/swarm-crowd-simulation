# Experiment `S_load150_gangways_s2`

**Task 5.9 stage 4: venue S, 150% load (seed 2): standing also on the gangways**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 5592 agents (load 150.0%, requested 150%): every one of the 3728 seats and 1864 standing (spawnOvercrowdedCrowd, seed 2; below), buffer N = 8192, 1704 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 236049 evaluations, 4839 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.50)** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-20T23:11:35, 16.2 s wall.

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
| t50 | 689 | 120.5 |
| t90 | 1363 | 238.4 |
| t100 | 1704 | 298.0 |

t_p: the step by which ceil(p x 5592) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 540 | 57 | 13.5 | 283.3 | 21.2 | 46.8 | 13.1-23.1 |
| -x | 5.66 | 548 | 58 | 13.5 | 282.8 | 21.6 | 44.7 | 13.1-23.1 |
| +y | 5.66 | 565 | 52 | 13.5 | 279.3 | 22.5 | 46.8 | 13.3-23.3 |
| -y | 5.66 | 537 | 65 | 13.6 | 271.1 | 22.1 | 48.9 | 12.9-22.9 |
| door +x+y y | 1.20 | 428 | 658 | 1.2 | 274.1 | 78.4 | 125.4 | 118.1-128.0 |
| door +x+y x | 1.20 | 415 | 671 | 1.2 | 295.2 | 70.5 | 125.4 | 125.2-135.2 |
| door -x+y y | 1.20 | 430 | 674 | 0.9 | 279.9 | 77.0 | 125.4 | 117.4-127.3 |
| door -x+y x | 1.20 | 428 | 688 | 0.9 | 278.3 | 77.1 | 120.4 | 133.8-143.8 |
| door -x-y y | 1.20 | 421 | 660 | 0.9 | 291.9 | 72.3 | 115.3 | 120.3-130.3 |
| door -x-y x | 1.20 | 423 | 669 | 0.9 | 270.9 | 78.3 | 120.4 | 120.9-130.8 |
| door +x-y y | 1.20 | 426 | 683 | 1.0 | 298.0 | 71.7 | 125.4 | 110.4-120.3 |
| door +x-y x | 1.20 | 431 | 657 | 1.2 | 280.2 | 77.2 | 115.3 | 108.6-118.6 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 540 | 9.7% | 23.0% |
| -x | avenue | 5.66 | 548 | 9.8% | 23.3% |
| +y | avenue | 5.66 | 565 | 10.1% | 24.0% |
| -y | avenue | 5.66 | 537 | 9.6% | 22.8% |
| door +x+y y | door | 1.20 | 428 | 7.7% | 85.9% |
| door +x+y x | door | 1.20 | 415 | 7.4% | 83.3% |
| door -x+y y | door | 1.20 | 430 | 7.7% | 86.3% |
| door -x+y x | door | 1.20 | 428 | 7.7% | 85.9% |
| door -x-y y | door | 1.20 | 421 | 7.5% | 84.5% |
| door -x-y x | door | 1.20 | 423 | 7.6% | 84.9% |
| door +x-y y | door | 1.20 | 426 | 7.6% | 85.5% |
| door +x-y x | door | 1.20 | 431 | 7.7% | 86.5% |
| **doors (8)** | door | 9.60 | 3402 | 60.8% | |
| **avenues (4)** | avenue | 22.64 | 2190 | 39.2% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 298.0 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 41.8%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 481 | 8.6% | 474 | 8.5% |
| straight +x+y (x wing) 0 | straight | yes | 487 | 8.7% | 487 | 8.7% |
| corner +x+y | corner | **no** | 80 | 1.4% | 80 | 1.4% |
| straight -x+y (y wing) 0 | straight | yes | 479 | 8.6% | 479 | 8.6% |
| straight -x+y (x wing) 0 | straight | yes | 481 | 8.6% | 481 | 8.6% |
| corner -x+y | corner | **no** | 96 | 1.7% | 96 | 1.7% |
| straight -x-y (y wing) 0 | straight | yes | 485 | 8.7% | 485 | 8.7% |
| straight -x-y (x wing) 0 | straight | yes | 482 | 8.6% | 477 | 8.5% |
| corner -x-y | corner | **no** | 88 | 1.6% | 88 | 1.6% |
| straight +x-y (y wing) 0 | straight | yes | 485 | 8.7% | 485 | 8.7% |
| straight +x-y (x wing) 0 | straight | yes | 483 | 8.6% | 477 | 8.5% |
| corner +x-y | corner | **no** | 88 | 1.6% | 88 | 1.6% |
| **straight (8)** | | | 3863 | | 3845 | 68.8% |
| **corner (4)** | | | 352 | | 352 | 6.3% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 1395, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 540 | 13.5 | 283.3 | 0.25 | 0.56 | 0.0% |
| -x | 548 | 13.5 | 282.8 | 0.26 | 0.53 | 0.0% |
| +y | 565 | 13.5 | 279.3 | 0.27 | 0.56 | 0.0% |
| -y | 537 | 13.6 | 271.1 | 0.26 | 0.59 | 0.0% |
| door +x+y y | 428 | 1.2 | 274.1 | 0.94 | 1.50 | 64.3% |
| door +x+y x | 415 | 1.2 | 295.2 | 0.84 | 1.50 | 60.0% |
| door -x+y y | 430 | 0.9 | 279.9 | 0.92 | 1.50 | 65.5% |
| door -x+y x | 428 | 0.9 | 278.3 | 0.92 | 1.44 | 64.3% |
| door -x-y y | 421 | 0.9 | 291.9 | 0.86 | 1.38 | 56.7% |
| door -x-y x | 423 | 0.9 | 270.9 | 0.94 | 1.44 | 64.3% |
| door +x-y y | 426 | 1.0 | 298.0 | 0.86 | 1.50 | 60.0% |
| door +x-y x | 431 | 1.2 | 280.2 | 0.92 | 1.38 | 58.6% |

Mean flow / w J averaged over the doors 0.90, over the avenues 0.26.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 481 | 306 / 175 / 42 | 0.2 | 271.1 | 1.93 | 3.01 | 86% | 86% | 0% | 4.15 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 480 | 287 / 200 / 45 | 0.2 | 292.3 | 1.82 | 2.81 | 80% | 77% | 3% | 3.87 |
| corner +x+y | 1.20 | 31.2 | 80 | 3 / 79 / 0 | 0.2 | 117.9 | 0.70 | 1.10 | 17% | 0% | 17% | 1.90 |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 479 | 301 / 179 / 35 | 0.2 | 276.9 | 1.86 | 2.71 | 86% | 86% | 0% | 4.09 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 481 | 289 / 192 / 44 | 0.2 | 275.3 | 1.91 | 3.11 | 89% | 86% | 4% | 3.98 |
| corner -x+y | 1.20 | 31.2 | 96 | 7 / 91 / 0 | 0.2 | 119.8 | 0.82 | 1.40 | 23% | 15% | 8% | 2.19 |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 480 | 300 / 185 / 43 | 0.2 | 288.9 | 1.83 | 3.11 | 83% | 79% | 3% | 3.89 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 482 | 296 / 186 / 38 | 0.2 | 268.0 | 1.94 | 2.91 | 89% | 89% | 0% | 4.10 |
| corner -x-y | 1.20 | 31.2 | 88 | 3 / 86 / 0 | 0.2 | 116.7 | 0.76 | 1.10 | 8% | 0% | 8% | 1.76 |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 479 | 292 / 193 / 37 | 0.2 | 295.1 | 1.77 | 2.71 | 80% | 77% | 3% | 3.91 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 483 | 309 / 174 / 25 | 0.2 | 277.2 | 1.83 | 2.51 | 93% | 89% | 4% | 3.98 |
| corner +x-y | 1.20 | 31.2 | 88 | 3 / 86 / 0 | 0.2 | 125.2 | 0.71 | 1.40 | 15% | 8% | 8% | 2.03 |

The last agent out (agent 3404, t100 298.0 s): last gangway straight +x-y (y wing) 0, exit door +x-y (y wall). The gangway that cleared last: straight +x-y (y wing) 0 at 295.1 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.42 | 290.0 / 281.6 / 241.2 | 266.2 / 259.0 / 205.2 | 82488.5 | 338693 | 0.270 |
| gangway | 392 | 351.5 | 6.42 | 276.0 / 261.7 / 220.6 | 266.2 / 259.0 / 205.2 | 70653.9 | 212526 | 0.101 |
| walkway | 276 | 257.4 | 4.85 | 172.3 / 137.1 / 0.0 | 154.1 / 97.9 / 0.0 | 0.0 | 24206 | 0.597 |
| avenue | 408 | 384.3 | 2.39 | 190.1 / 2.3 / 0.0 | 156.7 / 1.0 / 0.0 | 0.0 | 28550 | 1.310 |
| exit | 40 | 9.7 | 0.00 | 289.6 / 280.7 / 195.9 | 213.0 / 182.1 / 66.8 | 803.8 | 3163 | 0.959 |
| concourse | 612 | 609.0 | 5.96 | 237.3 / 136.3 / 96.4 | 153.2 / 135.2 / 74.2 | 11030.9 | 70248 | 0.217 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.54 | 258.0 / 256.9 / 250.8 | 258.0 / 256.9 / 248.9 | 126921.7 | 368139 | 0.044 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 18.5 | -10.5 | gangway | 0.94 | 5.76 | 261.8 | 257.3 | 205.2 | 1052.4 | 0.027 |
| 2 | 10.5 | 18.5 | gangway | 0.94 | 6.00 | 250.3 | 246.6 | 191.2 | 1006.6 | 0.028 |
| 3 | -18.5 | -10.5 | gangway | 0.94 | 6.01 | 251.3 | 240.0 | 187.0 | 960.8 | 0.034 |
| 4 | 11.5 | 18.5 | gangway | 0.86 | 6.28 | 240.3 | 233.9 | 184.0 | 918.9 | 0.027 |
| 5 | 17.5 | -10.5 | gangway | 0.95 | 5.68 | 256.2 | 253.3 | 179.3 | 912.9 | 0.038 |
| 6 | 10.5 | -18.5 | gangway | 0.94 | 5.69 | 233.3 | 230.4 | 171.2 | 868.5 | 0.037 |
| 7 | -18.5 | 10.5 | gangway | 0.94 | 5.81 | 244.2 | 240.5 | 165.1 | 843.4 | 0.034 |
| 8 | -18.5 | -11.5 | gangway | 0.86 | 6.02 | 237.9 | 236.1 | 177.5 | 842.1 | 0.035 |
| 9 | -10.5 | 19.5 | gangway | 0.96 | 5.60 | 255.2 | 249.2 | 167.2 | 840.7 | 0.027 |
| 10 | 18.5 | -11.5 | gangway | 0.86 | 6.08 | 245.0 | 237.2 | 175.3 | 829.3 | 0.028 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 18.5 | -9.5 | seat row | 0.50 | 7.53 | 258.0 | 256.9 | 248.9 | 875.9 | 0.020 |
| 2 | 9.5 | 18.5 | seat row | 0.50 | 7.40 | 247.7 | 247.1 | 238.2 | 835.8 | 0.021 |
| 3 | -9.5 | 18.5 | seat row | 0.50 | 7.44 | 244.9 | 244.0 | 237.3 | 832.6 | 0.021 |
| 4 | -18.5 | -9.5 | seat row | 0.50 | 7.42 | 246.3 | 245.0 | 235.6 | 824.5 | 0.022 |
| 5 | 18.5 | -8.5 | seat row | 0.50 | 7.11 | 251.7 | 249.1 | 239.4 | 808.8 | 0.018 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 308; agent-steps of seated agents on another row's clearway: 2070.

## Deposit check

Person-seconds deposited: 709717.2, of them in excluded cells: 2884.993.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 36837 overlapping pair-steps: p99 0.0038, max 0.0076 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0038 max 0.0076; venue-geometry 2: p99 0.0010 max 0.0010 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 8 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 5.96 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 76 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
