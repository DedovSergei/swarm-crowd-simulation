# Experiment `S_load150_gangways_s2`

**Task 5.10 stage 4 (AMD 26.10.1): venue S, 150% load (seed 2): standing also on the gangways**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 5592 agents (load 150.0%, requested 150%): every one of the 3728 seats and 1864 standing (spawnOvercrowdedCrowd, seed 2; below), buffer N = 8192, 1723 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 236419 evaluations, 4821 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.50)** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T19:38:48, 17.1 s wall.

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
| t50 | 692 | 121.0 |
| t90 | 1367 | 239.1 |
| t100 | 1723 | 301.4 |

t_p: the step by which ceil(p x 5592) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 541 | 57 | 13.5 | 283.9 | 21.2 | 46.8 | 13.1-23.1 |
| -x | 5.66 | 552 | 58 | 13.5 | 282.6 | 21.7 | 44.7 | 13.1-23.1 |
| +y | 5.66 | 564 | 52 | 13.5 | 284.4 | 22.1 | 46.8 | 13.3-23.3 |
| -y | 5.66 | 550 | 65 | 13.6 | 275.7 | 22.2 | 48.9 | 12.9-22.9 |
| door +x+y y | 1.20 | 427 | 658 | 1.2 | 274.1 | 78.2 | 115.3 | 99.7-109.7 |
| door +x+y x | 1.20 | 419 | 671 | 1.2 | 292.6 | 71.9 | 115.3 | 122.4-132.4 |
| door -x+y y | 1.20 | 427 | 674 | 0.9 | 282.8 | 75.7 | 120.4 | 121.6-131.5 |
| door -x+y x | 1.20 | 428 | 688 | 0.9 | 279.7 | 76.7 | 115.3 | 141.8-151.8 |
| door -x-y y | 1.20 | 413 | 660 | 0.9 | 269.4 | 76.9 | 125.4 | 139.2-149.2 |
| door -x-y x | 1.20 | 424 | 669 | 0.9 | 276.4 | 76.9 | 120.4 | 118.1-128.0 |
| door +x-y y | 1.20 | 423 | 683 | 1.0 | 301.4 | 70.4 | 115.3 | 101.1-111.1 |
| door +x-y x | 1.20 | 424 | 657 | 1.2 | 291.4 | 73.0 | 120.4 | 119.6-129.6 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 541 | 9.7% | 22.8% |
| -x | avenue | 5.66 | 552 | 9.9% | 23.2% |
| +y | avenue | 5.66 | 564 | 10.1% | 23.7% |
| -y | avenue | 5.66 | 550 | 9.8% | 23.1% |
| door +x+y y | door | 1.20 | 427 | 7.6% | 84.7% |
| door +x+y x | door | 1.20 | 419 | 7.5% | 83.2% |
| door -x+y y | door | 1.20 | 427 | 7.6% | 84.7% |
| door -x+y x | door | 1.20 | 428 | 7.7% | 84.9% |
| door -x-y y | door | 1.20 | 413 | 7.4% | 82.0% |
| door -x-y x | door | 1.20 | 424 | 7.6% | 84.1% |
| door +x-y y | door | 1.20 | 423 | 7.6% | 83.9% |
| door +x-y x | door | 1.20 | 424 | 7.6% | 84.1% |
| **doors (8)** | door | 9.60 | 3385 | 60.5% | |
| **avenues (4)** | avenue | 22.64 | 2207 | 39.5% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 301.4 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 41.3%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 481 | 8.6% | 475 | 8.5% |
| straight +x+y (x wing) 0 | straight | yes | 486 | 8.7% | 486 | 8.7% |
| corner +x+y | corner | **no** | 80 | 1.4% | 80 | 1.4% |
| straight -x+y (y wing) 0 | straight | yes | 479 | 8.6% | 479 | 8.6% |
| straight -x+y (x wing) 0 | straight | yes | 481 | 8.6% | 481 | 8.6% |
| corner -x+y | corner | **no** | 96 | 1.7% | 96 | 1.7% |
| straight -x-y (y wing) 0 | straight | yes | 480 | 8.6% | 480 | 8.6% |
| straight -x-y (x wing) 0 | straight | yes | 482 | 8.6% | 482 | 8.6% |
| corner -x-y | corner | **no** | 88 | 1.6% | 88 | 1.6% |
| straight +x-y (y wing) 0 | straight | yes | 485 | 8.7% | 485 | 8.7% |
| straight +x-y (x wing) 0 | straight | yes | 482 | 8.6% | 476 | 8.5% |
| corner +x-y | corner | **no** | 89 | 1.6% | 89 | 1.6% |
| **straight (8)** | | | 3856 | | 3844 | 68.7% |
| **corner (4)** | | | 353 | | 353 | 6.3% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 1395, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 541 | 13.5 | 283.9 | 0.25 | 0.56 | 0.0% |
| -x | 552 | 13.5 | 282.6 | 0.26 | 0.53 | 0.0% |
| +y | 564 | 13.5 | 284.4 | 0.26 | 0.56 | 0.0% |
| -y | 550 | 13.6 | 275.7 | 0.27 | 0.59 | 0.0% |
| door +x+y y | 427 | 1.2 | 274.1 | 0.94 | 1.38 | 64.3% |
| door +x+y x | 419 | 1.2 | 292.6 | 0.86 | 1.38 | 66.7% |
| door -x+y y | 427 | 0.9 | 282.8 | 0.91 | 1.44 | 51.7% |
| door -x+y x | 428 | 0.9 | 279.7 | 0.92 | 1.38 | 69.0% |
| door -x-y y | 413 | 0.9 | 269.4 | 0.92 | 1.50 | 71.4% |
| door -x-y x | 424 | 0.9 | 276.4 | 0.92 | 1.44 | 60.7% |
| door +x-y y | 423 | 1.0 | 301.4 | 0.84 | 1.38 | 61.3% |
| door +x-y x | 424 | 1.2 | 291.4 | 0.87 | 1.44 | 63.3% |

Mean flow / w J averaged over the doors 0.90, over the avenues 0.26.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 481 | 305 / 176 / 34 | 0.2 | 271.1 | 1.90 | 2.81 | 89% | 86% | 4% | 3.98 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 480 | 291 / 195 / 61 | 0.2 | 289.6 | 1.89 | 3.31 | 80% | 77% | 3% | 3.89 |
| corner +x+y | 1.20 | 31.2 | 80 | 3 / 79 / 0 | 0.2 | 113.0 | 0.73 | 1.40 | 17% | 0% | 17% | 1.90 |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 479 | 298 / 181 / 44 | 0.2 | 279.9 | 1.87 | 2.71 | 86% | 83% | 3% | 4.04 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 481 | 290 / 191 / 45 | 0.2 | 276.7 | 1.90 | 2.91 | 89% | 86% | 4% | 3.98 |
| corner -x+y | 1.20 | 31.2 | 96 | 6 / 92 / 0 | 0.2 | 123.3 | 0.79 | 1.40 | 23% | 15% | 8% | 2.19 |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 480 | 292 / 188 / 46 | 0.2 | 266.4 | 1.97 | 2.81 | 89% | 85% | 4% | 3.93 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 482 | 297 / 185 / 27 | 0.2 | 273.4 | 1.86 | 2.51 | 86% | 86% | 0% | 4.07 |
| corner -x-y | 1.20 | 31.2 | 88 | 3 / 86 / 0 | 0.2 | 112.6 | 0.79 | 1.20 | 8% | 0% | 8% | 1.76 |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 479 | 288 / 197 / 59 | 0.2 | 298.4 | 1.82 | 3.01 | 80% | 77% | 3% | 3.88 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 482 | 303 / 181 / 31 | 0.2 | 288.4 | 1.79 | 2.91 | 86% | 83% | 3% | 4.08 |
| corner +x-y | 1.20 | 31.2 | 89 | 4 / 86 / 0 | 0.2 | 124.0 | 0.73 | 1.30 | 23% | 15% | 8% | 2.13 |

The last agent out (agent 3376, t100 301.4 s): last gangway straight +x-y (y wing) 0, exit door +x-y (y wall). The gangway that cleared last: straight +x-y (y wing) 0 at 298.4 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.37 | 291.2 / 280.4 / 235.8 | 267.8 / 263.4 / 197.8 | 83230.1 | 339640 | 0.270 |
| gangway | 392 | 351.5 | 6.37 | 277.1 / 264.5 / 208.1 | 267.8 / 263.4 / 197.8 | 70826.6 | 211886 | 0.101 |
| walkway | 276 | 257.4 | 4.85 | 170.4 / 133.8 / 0.0 | 152.0 / 92.7 / 0.0 | 0.0 | 24354 | 0.597 |
| avenue | 408 | 384.3 | 2.39 | 189.8 / 2.3 / 0.0 | 158.8 / 1.0 / 0.0 | 0.0 | 28771 | 1.310 |
| exit | 40 | 9.7 | 0.00 | 290.5 / 279.5 / 200.6 | 212.9 / 187.0 / 69.4 | 829.6 | 3198 | 0.947 |
| concourse | 612 | 609.0 | 5.87 | 242.6 / 146.4 / 98.6 | 164.4 / 140.8 / 77.1 | 11573.9 | 71432 | 0.213 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.57 | 253.1 / 249.9 / 243.3 | 253.1 / 249.9 / 241.4 | 127141.2 | 368241 | 0.044 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 18.5 | -10.5 | gangway | 0.94 | 5.80 | 256.2 | 252.2 | 197.8 | 999.0 | 0.030 |
| 2 | -10.5 | 18.5 | gangway | 0.94 | 5.84 | 249.6 | 244.7 | 185.9 | 956.3 | 0.030 |
| 3 | -18.5 | -10.5 | gangway | 0.94 | 5.90 | 247.0 | 244.5 | 176.7 | 911.9 | 0.035 |
| 4 | -10.5 | 19.5 | gangway | 0.96 | 5.72 | 255.2 | 248.9 | 180.2 | 908.1 | 0.026 |
| 5 | -10.5 | -18.5 | gangway | 0.94 | 5.61 | 236.8 | 232.1 | 174.0 | 868.1 | 0.034 |
| 6 | 17.5 | -10.5 | gangway | 0.95 | 5.71 | 257.1 | 255.0 | 169.8 | 862.6 | 0.039 |
| 7 | -18.5 | 10.5 | gangway | 0.94 | 5.91 | 248.5 | 240.8 | 170.5 | 857.6 | 0.036 |
| 8 | 10.5 | 18.5 | gangway | 0.94 | 5.94 | 246.8 | 237.3 | 167.2 | 855.7 | 0.029 |
| 9 | 19.5 | -11.5 | gangway | 0.92 | 5.62 | 245.6 | 232.6 | 174.0 | 849.4 | 0.022 |
| 10 | -18.5 | -11.5 | gangway | 0.86 | 6.20 | 234.7 | 228.8 | 171.4 | 844.4 | 0.034 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 18.5 | -9.5 | seat row | 0.50 | 7.45 | 252.7 | 248.9 | 241.4 | 850.9 | 0.021 |
| 2 | -9.5 | 18.5 | seat row | 0.50 | 7.55 | 245.4 | 244.5 | 235.6 | 842.6 | 0.021 |
| 3 | -18.5 | -9.5 | seat row | 0.50 | 7.52 | 244.7 | 242.1 | 233.0 | 817.8 | 0.022 |
| 4 | -18.5 | 9.5 | seat row | 0.50 | 7.37 | 244.9 | 242.1 | 235.1 | 812.9 | 0.022 |
| 5 | 9.5 | 18.5 | seat row | 0.50 | 7.37 | 245.2 | 237.9 | 227.9 | 791.6 | 0.022 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 345; agent-steps of seated agents on another row's clearway: 2226.

## Deposit check

Person-seconds deposited: 710784.1, of them in excluded cells: 2903.309.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 31931 overlapping pair-steps: p99 0.0041, max 0.0121 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0041 max 0.0121; venue-geometry 1: p99 0.0014 max 0.0014 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 4 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 5.87 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 83 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
