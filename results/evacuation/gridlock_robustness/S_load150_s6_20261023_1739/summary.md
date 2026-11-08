# Experiment `S_load150_s6`

**Task 5.11 stage 1 (gridlock robustness, default model, AMD 26.10.1): venue S, 150% load (seed 6)**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 5592 agents (load 150.0%, requested 150%): every one of the 3728 seats and 1864 standing (spawnOvercrowdedCrowd, seed 6; below), buffer N = 8192, 1659 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 230900 evaluations, 4688 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.50)** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `15aa31e8667e4a9417fde7884d907d1832c5e2d6`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-23T17:39:29, 14.7 s wall.

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
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 3.65, all circulation cells 3.65 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 6, 23927 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 685 | 119.8 |
| t90 | 1337 | 233.9 |
| t100 | 1659 | 290.2 |

t_p: the step by which ceil(p x 5592) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 545 | 75 | 13.5 | 279.2 | 21.7 | 54.2 | 13.1-23.1 |
| -x | 5.66 | 540 | 70 | 13.5 | 275.7 | 21.8 | 58.5 | 13.1-23.1 |
| +y | 5.66 | 543 | 77 | 13.6 | 272.9 | 22.2 | 54.2 | 12.8-22.7 |
| -y | 5.66 | 545 | 77 | 13.5 | 274.4 | 22.1 | 57.4 | 13.3-23.3 |
| door +x+y y | 1.20 | 428 | 662 | 0.9 | 290.2 | 73.9 | 120.4 | 146.4-156.4 |
| door +x+y x | 1.20 | 427 | 663 | 1.6 | 270.4 | 79.4 | 120.4 | 147.1-157.1 |
| door -x+y y | 1.20 | 423 | 658 | 1.2 | 274.8 | 77.3 | 125.4 | 153.7-163.7 |
| door -x+y x | 1.20 | 430 | 664 | 1.2 | 282.3 | 76.4 | 125.4 | 145.0-155.0 |
| door -x-y y | 1.20 | 426 | 662 | 1.0 | 275.7 | 77.5 | 125.4 | 151.5-161.4 |
| door -x-y x | 1.20 | 427 | 660 | 0.9 | 276.4 | 77.5 | 110.3 | 100.2-110.2 |
| door +x-y y | 1.20 | 428 | 661 | 0.9 | 266.6 | 80.5 | 120.4 | 137.3-147.3 |
| door +x-y x | 1.20 | 430 | 663 | 0.9 | 274.1 | 78.6 | 110.3 | 35.0-45.0 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 545 | 9.7% | 23.8% |
| -x | avenue | 5.66 | 540 | 9.7% | 23.6% |
| +y | avenue | 5.66 | 543 | 9.7% | 23.7% |
| -y | avenue | 5.66 | 545 | 9.7% | 23.8% |
| door +x+y y | door | 1.20 | 428 | 7.7% | 88.2% |
| door +x+y x | door | 1.20 | 427 | 7.6% | 88.0% |
| door -x+y y | door | 1.20 | 423 | 7.6% | 87.2% |
| door -x+y x | door | 1.20 | 430 | 7.7% | 88.6% |
| door -x-y y | door | 1.20 | 426 | 7.6% | 87.8% |
| door -x-y x | door | 1.20 | 427 | 7.6% | 88.0% |
| door +x-y y | door | 1.20 | 428 | 7.7% | 88.2% |
| door +x-y x | door | 1.20 | 430 | 7.7% | 88.6% |
| **doors (8)** | door | 9.60 | 3419 | 61.1% | |
| **avenues (4)** | avenue | 22.64 | 2173 | 38.9% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 290.2 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 42.9%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 455 | 8.1% | 455 | 8.1% |
| straight +x+y (x wing) 0 | straight | yes | 451 | 8.1% | 448 | 8.0% |
| corner +x+y | corner | **no** | 48 | 0.9% | 48 | 0.9% |
| straight -x+y (y wing) 0 | straight | yes | 450 | 8.0% | 450 | 8.0% |
| straight -x+y (x wing) 0 | straight | yes | 451 | 8.1% | 451 | 8.1% |
| corner -x+y | corner | **no** | 54 | 1.0% | 54 | 1.0% |
| straight -x-y (y wing) 0 | straight | yes | 446 | 8.0% | 446 | 8.0% |
| straight -x-y (x wing) 0 | straight | yes | 452 | 8.1% | 452 | 8.1% |
| corner -x-y | corner | **no** | 56 | 1.0% | 56 | 1.0% |
| straight +x-y (y wing) 0 | straight | yes | 454 | 8.1% | 454 | 8.1% |
| straight +x-y (x wing) 0 | straight | yes | 451 | 8.1% | 451 | 8.1% |
| corner +x-y | corner | **no** | 48 | 0.9% | 48 | 0.9% |
| **straight (8)** | | | 3610 | | 3607 | 64.5% |
| **corner (4)** | | | 206 | | 206 | 3.7% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 1779, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 545 | 13.5 | 279.2 | 0.26 | 0.65 | 0.0% |
| -x | 540 | 13.5 | 275.7 | 0.26 | 0.70 | 0.0% |
| +y | 543 | 13.6 | 272.9 | 0.27 | 0.65 | 0.0% |
| -y | 545 | 13.5 | 274.4 | 0.26 | 0.69 | 0.0% |
| door +x+y y | 428 | 0.9 | 290.2 | 0.88 | 1.44 | 63.3% |
| door +x+y x | 427 | 1.6 | 270.4 | 0.95 | 1.44 | 64.3% |
| door -x+y y | 423 | 1.2 | 274.8 | 0.92 | 1.50 | 71.4% |
| door -x+y x | 430 | 1.2 | 282.3 | 0.91 | 1.50 | 65.5% |
| door -x-y y | 426 | 1.0 | 275.7 | 0.93 | 1.50 | 67.9% |
| door -x-y x | 427 | 0.9 | 276.4 | 0.93 | 1.32 | 67.9% |
| door +x-y y | 428 | 0.9 | 266.6 | 0.96 | 1.44 | 66.7% |
| door +x-y x | 430 | 0.9 | 274.1 | 0.94 | 1.32 | 67.9% |

Mean flow / w J averaged over the doors 0.93, over the avenues 0.26.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 452 | 269 / 187 / 55 | 0.5 | 287.2 | 1.78 | 2.91 | 83% | 79% | 3% | 4.00 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 451 | 264 / 188 / 56 | 0.3 | 267.4 | 1.90 | 3.01 | 89% | 89% | 0% | 4.05 |
| corner +x+y | 1.20 | 31.2 | 48 | 0 / 48 / 0 | 4.4 | 80.8 | 0.63 | 1.10 | 11% | 0% | 11% | 0.61 |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 450 | 268 / 182 / 46 | 0.3 | 271.8 | 1.83 | 3.01 | 86% | 86% | 0% | 4.13 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 451 | 271 / 180 / 32 | 0.3 | 279.3 | 1.73 | 2.61 | 83% | 83% | 0% | 4.07 |
| corner -x+y | 1.20 | 31.2 | 54 | 0 / 54 / 0 | 4.0 | 84.5 | 0.67 | 1.30 | 11% | 0% | 11% | 0.67 |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 446 | 262 / 184 / 56 | 0.2 | 272.7 | 1.84 | 3.01 | 86% | 82% | 4% | 4.13 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 452 | 272 / 181 / 44 | 0.2 | 273.4 | 1.82 | 3.01 | 86% | 82% | 4% | 4.09 |
| corner -x-y | 1.20 | 31.2 | 56 | 0 / 56 / 0 | 4.4 | 88.7 | 0.66 | 1.10 | 22% | 0% | 22% | 1.18 |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 454 | 269 / 185 / 46 | 0.2 | 263.6 | 1.90 | 2.81 | 89% | 89% | 0% | 4.07 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 451 | 270 / 183 / 43 | 0.2 | 271.1 | 1.83 | 3.11 | 86% | 86% | 0% | 4.13 |
| corner +x-y | 1.20 | 31.2 | 48 | 0 / 48 / 0 | 4.2 | 78.2 | 0.65 | 1.00 | 12% | 0% | 12% | 0.61 |

The last agent out (agent 606, t100 290.2 s): last gangway straight +x+y (y wing) 0, exit door +x+y (y wall). The gangway that cleared last: straight +x+y (y wing) 0 at 287.2 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.42 | 279.5 / 272.0 / 233.3 | 257.8 / 248.9 / 191.0 | 97687.5 | 352822 | 0.254 |
| gangway | 392 | 351.5 | 6.42 | 262.2 / 256.6 / 208.0 | 257.8 / 248.9 / 191.0 | 74782.5 | 198109 | 0.097 |
| walkway | 276 | 257.4 | 5.10 | 140.8 / 104.8 / 1.6 | 121.0 / 94.8 / 1.4 | 8.0 | 26981 | 0.512 |
| avenue | 408 | 384.3 | 2.44 | 164.2 / 12.6 / 0.0 | 137.0 / 0.9 / 0.0 | 0.0 | 28321 | 1.310 |
| exit | 40 | 9.7 | 0.00 | 279.3 / 270.2 / 202.0 | 215.8 / 192.7 / 73.6 | 923.3 | 3331 | 0.903 |
| concourse | 612 | 609.0 | 6.09 | 240.8 / 158.1 / 116.0 | 172.1 / 156.9 / 95.3 | 21973.7 | 96080 | 0.169 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.55 | 241.5 / 238.7 / 222.1 | 241.5 / 238.6 / 219.5 | 117817.0 | 337631 | 0.047 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 19.5 | 11.5 | gangway | 0.92 | 5.86 | 234.0 | 230.4 | 191.0 | 958.5 | 0.023 |
| 2 | 19.5 | 10.5 | gangway | 0.96 | 5.65 | 243.6 | 232.1 | 171.4 | 898.5 | 0.026 |
| 3 | -11.5 | 19.5 | gangway | 0.92 | 5.73 | 224.9 | 221.4 | 177.9 | 888.0 | 0.025 |
| 4 | 18.5 | -10.5 | gangway | 0.94 | 6.01 | 237.9 | 235.1 | 170.7 | 874.0 | 0.039 |
| 5 | -19.5 | -11.5 | gangway | 0.92 | 5.81 | 224.6 | 220.7 | 168.4 | 846.1 | 0.024 |
| 6 | -18.5 | 10.5 | gangway | 0.94 | 5.96 | 239.3 | 236.3 | 159.3 | 822.8 | 0.036 |
| 7 | -19.5 | 11.5 | gangway | 0.92 | 5.93 | 239.1 | 229.3 | 160.2 | 817.8 | 0.024 |
| 8 | -10.5 | 18.5 | gangway | 0.94 | 6.09 | 232.3 | 229.8 | 156.0 | 805.1 | 0.036 |
| 9 | -21.5 | 11.5 | gangway | 0.89 | 5.93 | 246.8 | 234.0 | 162.5 | 802.7 | 0.035 |
| 10 | -10.5 | -18.5 | gangway | 0.94 | 5.93 | 229.8 | 227.9 | 156.5 | 800.2 | 0.040 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -18.5 | 9.5 | seat row | 0.50 | 7.39 | 234.0 | 231.4 | 219.5 | 765.5 | 0.024 |
| 2 | 18.5 | -9.5 | seat row | 0.50 | 7.40 | 236.6 | 231.6 | 219.0 | 762.1 | 0.023 |
| 3 | 9.5 | -18.5 | seat row | 0.50 | 7.49 | 233.7 | 229.0 | 216.7 | 756.2 | 0.024 |
| 4 | -9.5 | 18.5 | seat row | 0.50 | 7.37 | 233.0 | 221.4 | 211.3 | 737.5 | 0.025 |
| 5 | 22.5 | 12.5 | seat row | 0.50 | 7.14 | 227.2 | 225.8 | 215.7 | 732.4 | 0.028 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 378; agent-steps of seated agents on another row's clearway: 2593.

## Deposit check

Person-seconds deposited: 694360.7, of them in excluded cells: 3907.557.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 24676 overlapping pair-steps: p99 0.0022, max 0.0057 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0022 max 0.0057; venue-geometry 2: p99 0.0006 max 0.0006 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 10 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.09 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 91 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
