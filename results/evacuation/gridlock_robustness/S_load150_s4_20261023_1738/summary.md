# Experiment `S_load150_s4`

**Task 5.11 stage 1 (gridlock robustness, default model, AMD 26.10.1): venue S, 150% load (seed 4)**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 5592 agents (load 150.0%, requested 150%): every one of the 3728 seats and 1864 standing (spawnOvercrowdedCrowd, seed 4; below), buffer N = 8192, 1664 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 231088 evaluations, 4594 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.50)** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `15aa31e8667e4a9417fde7884d907d1832c5e2d6`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-23T17:38:52, 14.6 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Spawn (overcrowding)

| | |
|---|---|
| seated | 3728 (every seat) |
| standing | **1864** (requested round((1.50 - 1) x 3728) = 1864; at most 2143 = floor(2.5 p/m^2 x 857.4 m^2)) |
| standing floor | walkway + rear concourse, 857.4 m^2 |
| standing on the walkway / concourse / gangways | 549 / 1315 / 0 |
| **load** | **150.00%** of the seats (requested 150%) |
| standing crowd's mean density | 2.174 p/m^2 |
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 3.66, all circulation cells 3.66 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 4, 23980 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 683 | 119.5 |
| t90 | 1339 | 234.2 |
| t100 | 1664 | 291.0 |

t_p: the step by which ceil(p x 5592) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 542 | 76 | 13.5 | 276.5 | 21.8 | 53.2 | 13.3-23.3 |
| -x | 5.66 | 539 | 78 | 13.5 | 277.8 | 21.6 | 57.4 | 13.3-23.3 |
| +y | 5.66 | 566 | 75 | 13.5 | 278.5 | 22.6 | 56.4 | 13.3-23.3 |
| -y | 5.66 | 529 | 86 | 13.5 | 270.6 | 21.8 | 58.5 | 13.1-23.1 |
| door +x+y y | 1.20 | 437 | 663 | 0.9 | 272.9 | 80.3 | 115.3 | 146.2-156.2 |
| door +x+y x | 1.20 | 416 | 660 | 0.7 | 274.8 | 75.8 | 125.4 | 138.4-148.3 |
| door -x+y y | 1.20 | 433 | 662 | 0.9 | 268.5 | 80.8 | 120.4 | 133.5-143.4 |
| door -x+y x | 1.20 | 428 | 666 | 0.7 | 290.9 | 73.7 | 125.4 | 145.2-155.1 |
| door -x-y y | 1.20 | 417 | 662 | 0.9 | 291.0 | 71.8 | 125.4 | 162.0-171.9 |
| door -x-y x | 1.20 | 425 | 648 | 1.0 | 274.8 | 77.6 | 130.4 | 128.4-138.4 |
| door +x-y y | 1.20 | 424 | 657 | 1.4 | 290.3 | 73.3 | 120.4 | 144.3-154.3 |
| door +x-y x | 1.20 | 436 | 659 | 0.9 | 268.3 | 81.5 | 120.4 | 110.0-120.0 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 542 | 9.7% | 23.6% |
| -x | avenue | 5.66 | 539 | 9.6% | 23.5% |
| +y | avenue | 5.66 | 566 | 10.1% | 24.7% |
| -y | avenue | 5.66 | 529 | 9.5% | 23.0% |
| door +x+y y | door | 1.20 | 437 | 7.8% | 89.8% |
| door +x+y x | door | 1.20 | 416 | 7.4% | 85.5% |
| door -x+y y | door | 1.20 | 433 | 7.7% | 89.0% |
| door -x+y x | door | 1.20 | 428 | 7.7% | 88.0% |
| door -x-y y | door | 1.20 | 417 | 7.5% | 85.7% |
| door -x-y x | door | 1.20 | 425 | 7.6% | 87.3% |
| door +x-y y | door | 1.20 | 424 | 7.6% | 87.1% |
| door +x-y x | door | 1.20 | 436 | 7.8% | 89.6% |
| **doors (8)** | door | 9.60 | 3416 | 61.1% | |
| **avenues (4)** | avenue | 22.64 | 2176 | 38.9% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 291.0 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 42.8%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 453 | 8.1% | 453 | 8.1% |
| straight +x+y (x wing) 0 | straight | yes | 455 | 8.1% | 455 | 8.1% |
| corner +x+y | corner | **no** | 50 | 0.9% | 50 | 0.9% |
| straight -x+y (y wing) 0 | straight | yes | 452 | 8.1% | 447 | 8.0% |
| straight -x+y (x wing) 0 | straight | yes | 458 | 8.2% | 458 | 8.2% |
| corner -x+y | corner | **no** | 51 | 0.9% | 51 | 0.9% |
| straight -x-y (y wing) 0 | straight | yes | 450 | 8.0% | 450 | 8.0% |
| straight -x-y (x wing) 0 | straight | yes | 452 | 8.1% | 448 | 8.0% |
| corner -x-y | corner | **no** | 55 | 1.0% | 55 | 1.0% |
| straight +x-y (y wing) 0 | straight | yes | 451 | 8.1% | 451 | 8.1% |
| straight +x-y (x wing) 0 | straight | yes | 450 | 8.0% | 443 | 7.9% |
| corner +x-y | corner | **no** | 57 | 1.0% | 57 | 1.0% |
| **straight (8)** | | | 3621 | | 3605 | 64.5% |
| **corner (4)** | | | 213 | | 213 | 3.8% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 1774, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 542 | 13.5 | 276.5 | 0.26 | 0.64 | 0.0% |
| -x | 539 | 13.5 | 277.8 | 0.26 | 0.69 | 0.0% |
| +y | 566 | 13.5 | 278.5 | 0.27 | 0.67 | 0.0% |
| -y | 529 | 13.5 | 270.6 | 0.26 | 0.70 | 0.0% |
| door +x+y y | 437 | 0.9 | 272.9 | 0.96 | 1.38 | 64.3% |
| door +x+y x | 416 | 0.7 | 274.8 | 0.91 | 1.50 | 57.1% |
| door -x+y y | 433 | 0.9 | 268.5 | 0.97 | 1.44 | 77.8% |
| door -x+y x | 428 | 0.7 | 290.9 | 0.88 | 1.50 | 63.3% |
| door -x-y y | 417 | 0.9 | 291.0 | 0.86 | 1.50 | 66.7% |
| door -x-y x | 425 | 1.0 | 274.8 | 0.93 | 1.56 | 67.9% |
| door +x-y y | 424 | 1.4 | 290.3 | 0.88 | 1.44 | 60.0% |
| door +x-y x | 436 | 0.9 | 268.3 | 0.97 | 1.44 | 66.7% |

Mean flow / w J averaged over the doors 0.92, over the avenues 0.26.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 453 | 278 / 176 / 41 | 0.3 | 269.9 | 1.84 | 2.81 | 86% | 86% | 0% | 4.16 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 455 | 261 / 194 / 65 | 0.3 | 271.8 | 1.91 | 3.31 | 86% | 82% | 4% | 3.99 |
| corner +x+y | 1.20 | 31.2 | 50 | 0 / 50 / 0 | 4.4 | 93.1 | 0.56 | 0.90 | 20% | 0% | 20% | 1.00 |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 452 | 275 / 179 / 38 | 0.5 | 265.5 | 1.86 | 2.81 | 93% | 89% | 4% | 4.18 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 453 | 268 / 190 / 57 | 0.3 | 287.9 | 1.79 | 2.91 | 79% | 79% | 0% | 4.13 |
| corner -x+y | 1.20 | 31.2 | 51 | 0 / 51 / 0 | 4.2 | 96.4 | 0.55 | 0.80 | 10% | 0% | 10% | 0.63 |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 446 | 255 / 195 / 55 | 0.5 | 288.1 | 1.76 | 2.91 | 79% | 79% | 0% | 4.17 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 452 | 276 / 176 / 31 | 0.7 | 271.8 | 1.78 | 2.71 | 86% | 86% | 0% | 4.24 |
| corner -x-y | 1.20 | 31.2 | 55 | 0 / 55 / 0 | 4.2 | 87.5 | 0.66 | 0.90 | 11% | 0% | 11% | 0.70 |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 444 | 267 / 184 / 45 | 0.3 | 287.4 | 1.73 | 2.71 | 79% | 79% | 0% | 4.04 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 450 | 276 / 175 / 39 | 0.5 | 265.3 | 1.85 | 2.91 | 93% | 89% | 4% | 4.11 |
| corner +x-y | 1.20 | 31.2 | 57 | 0 / 57 / 0 | 4.0 | 90.6 | 0.66 | 1.10 | 10% | 0% | 10% | 0.73 |

The last agent out (agent 2471, t100 291.0 s): last gangway straight -x-y (y wing) 0, exit door -x-y (y wall). The gangway that cleared last: straight -x-y (y wing) 0 at 288.1 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.46 | 283.9 / 275.0 / 237.3 | 257.3 / 253.8 / 180.5 | 97418.6 | 353870 | 0.254 |
| gangway | 392 | 351.5 | 6.46 | 265.2 / 255.7 / 209.7 | 257.3 / 253.8 / 180.5 | 77878.0 | 200613 | 0.097 |
| walkway | 276 | 257.4 | 5.03 | 159.0 / 123.0 / 0.7 | 141.8 / 120.7 / 0.5 | 3.5 | 28545 | 0.486 |
| avenue | 408 | 384.3 | 2.52 | 176.3 / 9.4 / 0.0 | 143.1 / 1.4 / 0.0 | 0.0 | 28358 | 1.310 |
| exit | 40 | 9.7 | 0.00 | 283.9 / 273.9 / 211.6 | 217.9 / 199.0 / 75.2 | 925.1 | 3317 | 0.908 |
| concourse | 612 | 609.0 | 5.98 | 244.7 / 165.5 / 112.6 | 176.5 / 164.1 / 91.1 | 18612.0 | 93036 | 0.174 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.52 | 247.8 / 244.0 / 232.1 | 247.8 / 243.8 / 229.5 | 116266.1 | 337387 | 0.047 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 18.5 | -10.5 | gangway | 0.94 | 6.05 | 241.9 | 239.1 | 178.2 | 932.3 | 0.029 |
| 2 | -19.5 | -11.5 | gangway | 0.92 | 6.09 | 234.4 | 229.0 | 180.5 | 925.6 | 0.021 |
| 3 | -18.5 | -10.5 | gangway | 0.94 | 5.88 | 244.3 | 238.2 | 177.9 | 916.1 | 0.032 |
| 4 | 10.5 | 18.5 | gangway | 0.94 | 5.92 | 246.3 | 240.5 | 176.3 | 904.6 | 0.034 |
| 5 | 19.5 | -10.5 | gangway | 0.96 | 5.78 | 250.6 | 243.6 | 170.9 | 901.7 | 0.023 |
| 6 | -10.5 | 18.5 | gangway | 0.94 | 5.79 | 242.8 | 238.7 | 177.2 | 890.2 | 0.032 |
| 7 | 19.5 | -11.5 | gangway | 0.92 | 5.76 | 235.9 | 230.7 | 171.9 | 857.5 | 0.022 |
| 8 | -19.5 | -10.5 | gangway | 0.96 | 5.76 | 249.8 | 244.5 | 163.5 | 853.8 | 0.024 |
| 9 | -11.5 | 19.5 | gangway | 0.92 | 5.80 | 237.5 | 230.9 | 170.5 | 848.6 | 0.023 |
| 10 | 11.5 | 19.5 | gangway | 0.92 | 5.73 | 230.9 | 226.7 | 165.1 | 810.2 | 0.025 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 9.5 | 18.5 | seat row | 0.50 | 7.42 | 241.5 | 238.4 | 229.5 | 806.8 | 0.022 |
| 2 | 18.5 | -9.5 | seat row | 0.50 | 7.46 | 242.6 | 240.0 | 223.7 | 789.9 | 0.023 |
| 3 | -18.5 | -9.5 | seat row | 0.50 | 7.44 | 241.9 | 238.7 | 224.4 | 785.0 | 0.023 |
| 4 | -9.5 | 18.5 | seat row | 0.50 | 7.49 | 242.9 | 235.2 | 222.1 | 773.3 | 0.023 |
| 5 | 8.5 | 18.5 | seat row | 0.50 | 7.11 | 233.7 | 229.0 | 211.5 | 715.4 | 0.019 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 371; agent-steps of seated agents on another row's clearway: 2403.

## Deposit check

Person-seconds deposited: 694992.3, of them in excluded cells: 3734.982.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 22618 overlapping pair-steps: p99 0.0029, max 0.0175 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0029 max 0.0175; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 6 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 5.98 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 99 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
