# Experiment `S_load150_s3`

**Task 5.9 stage 4: venue S, 150% requested (seed 3): every seat + standing on the walkway and concourse (M, L: the achievable maximum, also the 125% request)**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 5592 agents (load 150.0%, requested 150%): every one of the 3728 seats and 1864 standing (spawnOvercrowdedCrowd, seed 3; below), buffer N = 8192, 1627 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 232310 evaluations, 4617 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.50)** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-20T23:10:56, 15.5 s wall.

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
| t50 | 688 | 120.3 |
| t90 | 1347 | 235.6 |
| t100 | 1627 | 284.6 |

t_p: the step by which ceil(p x 5592) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 546 | 72 | 13.5 | 278.5 | 21.8 | 52.1 | 13.1-23.1 |
| -x | 5.66 | 554 | 74 | 13.6 | 276.7 | 22.3 | 56.4 | 13.3-23.3 |
| +y | 5.66 | 540 | 77 | 13.5 | 273.6 | 22.0 | 54.2 | 12.9-22.9 |
| -y | 5.66 | 535 | 75 | 13.6 | 277.4 | 21.5 | 53.2 | 13.5-23.4 |
| door +x+y y | 1.20 | 427 | 662 | 0.9 | 278.3 | 76.9 | 115.3 | 131.5-141.5 |
| door +x+y x | 1.20 | 433 | 663 | 0.9 | 271.3 | 80.0 | 110.3 | 93.6-103.5 |
| door -x+y y | 1.20 | 421 | 662 | 1.0 | 284.6 | 74.2 | 120.4 | 143.1-153.0 |
| door -x+y x | 1.20 | 418 | 647 | 0.9 | 277.8 | 75.4 | 125.4 | 146.7-156.7 |
| door -x-y y | 1.20 | 428 | 668 | 1.0 | 281.2 | 76.3 | 120.4 | 145.7-155.7 |
| door -x-y x | 1.20 | 431 | 657 | 1.0 | 281.2 | 76.9 | 115.3 | 142.2-152.2 |
| door +x-y y | 1.20 | 425 | 665 | 0.9 | 269.0 | 79.2 | 120.4 | 151.8-161.8 |
| door +x-y x | 1.20 | 434 | 670 | 1.0 | 280.7 | 77.5 | 125.4 | 151.8-161.8 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 546 | 9.8% | 24.3% |
| -x | avenue | 5.66 | 554 | 9.9% | 24.7% |
| +y | avenue | 5.66 | 540 | 9.7% | 24.1% |
| -y | avenue | 5.66 | 535 | 9.6% | 23.8% |
| door +x+y y | door | 1.20 | 427 | 7.6% | 89.7% |
| door +x+y x | door | 1.20 | 433 | 7.7% | 91.0% |
| door -x+y y | door | 1.20 | 421 | 7.5% | 88.5% |
| door -x+y x | door | 1.20 | 418 | 7.5% | 87.9% |
| door -x-y y | door | 1.20 | 428 | 7.7% | 90.0% |
| door -x-y x | door | 1.20 | 431 | 7.7% | 90.6% |
| door +x-y y | door | 1.20 | 425 | 7.6% | 89.3% |
| door +x-y x | door | 1.20 | 434 | 7.8% | 91.2% |
| **doors (8)** | door | 9.60 | 3417 | 61.1% | |
| **avenues (4)** | avenue | 22.64 | 2175 | 38.9% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 284.6 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 43.7%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 450 | 8.0% | 450 | 8.0% |
| straight +x+y (x wing) 0 | straight | yes | 451 | 8.1% | 451 | 8.1% |
| corner +x+y | corner | **no** | 50 | 0.9% | 50 | 0.9% |
| straight -x+y (y wing) 0 | straight | yes | 454 | 8.1% | 454 | 8.1% |
| straight -x+y (x wing) 0 | straight | yes | 452 | 8.1% | 451 | 8.1% |
| corner -x+y | corner | **no** | 51 | 0.9% | 51 | 0.9% |
| straight -x-y (y wing) 0 | straight | yes | 452 | 8.1% | 452 | 8.1% |
| straight -x-y (x wing) 0 | straight | yes | 451 | 8.1% | 451 | 8.1% |
| corner -x-y | corner | **no** | 47 | 0.8% | 47 | 0.8% |
| straight +x-y (y wing) 0 | straight | yes | 454 | 8.1% | 454 | 8.1% |
| straight +x-y (x wing) 0 | straight | yes | 450 | 8.0% | 450 | 8.0% |
| corner +x-y | corner | **no** | 53 | 0.9% | 53 | 0.9% |
| **straight (8)** | | | 3614 | | 3613 | 64.6% |
| **corner (4)** | | | 201 | | 201 | 3.6% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 1778, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 546 | 13.5 | 278.5 | 0.26 | 0.62 | 0.0% |
| -x | 554 | 13.6 | 276.7 | 0.27 | 0.67 | 0.0% |
| +y | 540 | 13.5 | 273.6 | 0.26 | 0.65 | 0.0% |
| -y | 535 | 13.6 | 277.4 | 0.26 | 0.64 | 0.0% |
| door +x+y y | 427 | 0.9 | 278.3 | 0.92 | 1.38 | 64.3% |
| door +x+y x | 433 | 0.9 | 271.3 | 0.96 | 1.32 | 71.4% |
| door -x+y y | 421 | 1.0 | 284.6 | 0.89 | 1.44 | 69.0% |
| door -x+y x | 418 | 0.9 | 277.8 | 0.90 | 1.50 | 67.9% |
| door -x-y y | 428 | 1.0 | 281.2 | 0.91 | 1.44 | 62.1% |
| door -x-y x | 431 | 1.0 | 281.2 | 0.92 | 1.38 | 62.1% |
| door +x-y y | 425 | 0.9 | 269.0 | 0.95 | 1.44 | 74.1% |
| door +x-y x | 434 | 1.0 | 280.7 | 0.93 | 1.50 | 75.9% |

Mean flow / w J averaged over the doors 0.92, over the avenues 0.26.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 450 | 264 / 187 / 54 | 0.3 | 275.3 | 1.84 | 3.21 | 86% | 82% | 4% | 4.02 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 451 | 270 / 181 / 38 | 0.3 | 268.3 | 1.82 | 2.71 | 89% | 89% | 0% | 4.12 |
| corner +x+y | 1.20 | 31.2 | 50 | 1 / 49 / 0 | 0.2 | 77.1 | 0.65 | 1.00 | 12% | 0% | 12% | 0.64 |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 453 | 263 / 192 / 52 | 0.5 | 281.6 | 1.80 | 2.91 | 79% | 79% | 0% | 4.16 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 452 | 269 / 183 / 50 | 0.7 | 274.8 | 1.83 | 3.11 | 86% | 86% | 0% | 4.09 |
| corner -x+y | 1.20 | 31.2 | 51 | 0 / 51 / 0 | 4.4 | 81.3 | 0.66 | 1.20 | 22% | 0% | 22% | 1.07 |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 452 | 264 / 188 / 56 | 0.3 | 278.3 | 1.83 | 2.91 | 86% | 86% | 0% | 4.09 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 451 | 277 / 176 / 41 | 0.5 | 278.3 | 1.78 | 2.81 | 86% | 86% | 0% | 4.20 |
| corner -x-y | 1.20 | 31.2 | 47 | 0 / 47 / 0 | 4.2 | 85.5 | 0.58 | 1.00 | 11% | 0% | 11% | 0.62 |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 454 | 263 / 193 / 65 | 0.3 | 266.0 | 1.96 | 2.91 | 89% | 89% | 0% | 4.05 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 450 | 267 / 184 / 43 | 0.3 | 277.8 | 1.78 | 2.91 | 86% | 86% | 0% | 4.24 |
| corner +x-y | 1.20 | 31.2 | 53 | 0 / 53 / 0 | 4.4 | 79.9 | 0.70 | 1.10 | 22% | 0% | 22% | 1.08 |

The last agent out (agent 1565, t100 284.6 s): last gangway straight -x+y (y wing) 0, exit door -x+y (y wall). The gangway that cleared last: straight -x+y (y wing) 0 at 281.6 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.44 | 280.7 / 272.2 / 235.8 | 256.1 / 249.4 / 169.7 | 97728.7 | 354038 | 0.253 |
| gangway | 392 | 351.5 | 6.44 | 277.1 / 254.5 / 207.4 | 256.1 / 249.4 / 169.7 | 75506.4 | 199396 | 0.096 |
| walkway | 276 | 257.4 | 5.06 | 143.4 / 104.8 / 0.9 | 127.0 / 98.3 / 0.7 | 4.4 | 26737 | 0.520 |
| avenue | 408 | 384.3 | 2.51 | 161.6 / 10.0 / 0.0 | 128.7 / 0.9 / 0.0 | 0.0 | 28347 | 1.310 |
| exit | 40 | 9.7 | 0.00 | 280.2 / 271.6 / 208.0 | 216.7 / 194.3 / 72.8 | 935.5 | 3349 | 0.896 |
| concourse | 612 | 609.0 | 6.03 | 245.6 / 156.9 / 116.7 | 173.0 / 156.5 / 95.8 | 21282.4 | 96210 | 0.170 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.51 | 244.0 / 240.8 / 227.6 | 244.0 / 240.7 / 224.9 | 116015.4 | 340676 | 0.047 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 10.5 | 19.5 | gangway | 0.96 | 5.86 | 238.7 | 228.8 | 165.5 | 877.2 | 0.027 |
| 2 | 19.5 | 11.5 | gangway | 0.92 | 6.07 | 230.4 | 226.3 | 168.6 | 867.2 | 0.024 |
| 3 | -19.5 | -10.5 | gangway | 0.96 | 5.74 | 250.6 | 244.3 | 165.8 | 860.3 | 0.025 |
| 4 | -18.5 | 10.5 | gangway | 0.94 | 5.87 | 235.9 | 232.6 | 169.0 | 857.8 | 0.037 |
| 5 | -19.5 | -11.5 | gangway | 0.92 | 6.03 | 232.6 | 227.6 | 169.7 | 853.4 | 0.026 |
| 6 | 19.5 | -11.5 | gangway | 0.92 | 6.00 | 230.0 | 225.3 | 167.2 | 845.8 | 0.027 |
| 7 | 11.5 | 19.5 | gangway | 0.92 | 5.85 | 224.4 | 212.7 | 163.2 | 819.0 | 0.025 |
| 8 | 19.5 | -10.5 | gangway | 0.96 | 5.74 | 248.0 | 233.3 | 157.9 | 816.5 | 0.027 |
| 9 | -10.5 | -19.5 | gangway | 0.96 | 5.85 | 238.6 | 229.5 | 154.8 | 814.0 | 0.031 |
| 10 | 18.5 | -10.5 | gangway | 0.94 | 5.83 | 242.2 | 237.9 | 157.2 | 801.7 | 0.037 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -18.5 | -9.5 | seat row | 0.50 | 7.51 | 237.2 | 235.6 | 224.9 | 792.7 | 0.022 |
| 2 | 18.5 | -9.5 | seat row | 0.50 | 7.47 | 235.1 | 230.7 | 217.6 | 758.7 | 0.024 |
| 3 | -18.5 | 9.5 | seat row | 0.50 | 7.37 | 233.2 | 223.0 | 211.3 | 734.4 | 0.025 |
| 4 | 18.5 | 9.5 | seat row | 0.50 | 7.30 | 232.1 | 226.2 | 210.4 | 733.1 | 0.024 |
| 5 | 12.5 | -22.5 | seat row | 0.50 | 7.08 | 227.9 | 225.3 | 213.7 | 716.8 | 0.027 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 399; agent-steps of seated agents on another row's clearway: 2769.

## Deposit check

Person-seconds deposited: 698595.6, of them in excluded cells: 3881.752.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 27124 overlapping pair-steps: p99 0.0057, max 0.0118 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0057 max 0.0118; venue-geometry 1: p99 0.0002 max 0.0002 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 6 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.03 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 107 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
