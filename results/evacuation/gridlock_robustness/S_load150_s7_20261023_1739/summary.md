# Experiment `S_load150_s7`

**Task 5.11 stage 1 (gridlock robustness, default model, AMD 26.10.1): venue S, 150% load (seed 7)**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 5592 agents (load 150.0%, requested 150%): every one of the 3728 seats and 1864 standing (spawnOvercrowdedCrowd, seed 7; below), buffer N = 8192, 1705 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 231354 evaluations, 4628 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.50)** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `15aa31e8667e4a9417fde7884d907d1832c5e2d6`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-23T17:39:47, 14.9 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Spawn (overcrowding)

| | |
|---|---|
| seated | 3728 (every seat) |
| standing | **1864** (requested round((1.50 - 1) x 3728) = 1864; at most 2143 = floor(2.5 p/m^2 x 857.4 m^2)) |
| standing floor | walkway + rear concourse, 857.4 m^2 |
| standing on the walkway / concourse / gangways | 551 / 1313 / 0 |
| **load** | **150.00%** of the seats (requested 150%) |
| standing crowd's mean density | 2.174 p/m^2 |
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 3.57, all circulation cells 3.57 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 7, 25417 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 683 | 119.5 |
| t90 | 1340 | 234.4 |
| t100 | 1705 | 298.2 |

t_p: the step by which ceil(p x 5592) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 544 | 73 | 13.5 | 276.2 | 21.9 | 54.2 | 13.5-23.4 |
| -x | 5.66 | 543 | 79 | 13.6 | 274.6 | 22.0 | 59.5 | 13.3-23.3 |
| +y | 5.66 | 527 | 80 | 13.6 | 270.4 | 21.7 | 57.4 | 13.3-23.3 |
| -y | 5.66 | 542 | 77 | 13.5 | 280.0 | 21.5 | 57.4 | 12.9-22.9 |
| door +x+y y | 1.20 | 427 | 663 | 1.0 | 275.8 | 77.6 | 125.4 | 144.5-154.4 |
| door +x+y x | 1.20 | 427 | 654 | 1.0 | 283.3 | 75.6 | 120.4 | 140.8-150.8 |
| door -x+y y | 1.20 | 436 | 668 | 1.2 | 298.2 | 73.4 | 115.3 | 109.7-119.6 |
| door -x+y x | 1.20 | 436 | 669 | 0.9 | 289.6 | 75.4 | 120.4 | 155.3-165.3 |
| door -x-y y | 1.20 | 437 | 667 | 0.9 | 287.9 | 76.1 | 115.3 | 134.0-143.9 |
| door -x-y x | 1.20 | 427 | 662 | 0.7 | 291.7 | 73.3 | 115.3 | 99.3-109.3 |
| door +x-y y | 1.20 | 422 | 656 | 1.2 | 287.0 | 73.8 | 115.3 | 143.6-153.6 |
| door +x-y x | 1.20 | 424 | 644 | 1.0 | 272.5 | 78.0 | 120.4 | 138.0-148.0 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 544 | 9.7% | 23.1% |
| -x | avenue | 5.66 | 543 | 9.7% | 23.1% |
| +y | avenue | 5.66 | 527 | 9.4% | 22.4% |
| -y | avenue | 5.66 | 542 | 9.7% | 23.0% |
| door +x+y y | door | 1.20 | 427 | 7.6% | 85.6% |
| door +x+y x | door | 1.20 | 427 | 7.6% | 85.6% |
| door -x+y y | door | 1.20 | 436 | 7.8% | 87.4% |
| door -x+y x | door | 1.20 | 436 | 7.8% | 87.4% |
| door -x-y y | door | 1.20 | 437 | 7.8% | 87.6% |
| door -x-y x | door | 1.20 | 427 | 7.6% | 85.6% |
| door +x-y y | door | 1.20 | 422 | 7.5% | 84.6% |
| door +x-y x | door | 1.20 | 424 | 7.6% | 85.0% |
| **doors (8)** | door | 9.60 | 3436 | 61.4% | |
| **avenues (4)** | avenue | 22.64 | 2156 | 38.6% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 298.2 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 41.7%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 450 | 8.0% | 450 | 8.0% |
| straight +x+y (x wing) 0 | straight | yes | 451 | 8.1% | 451 | 8.1% |
| corner +x+y | corner | **no** | 49 | 0.9% | 49 | 0.9% |
| straight -x+y (y wing) 0 | straight | yes | 461 | 8.2% | 461 | 8.2% |
| straight -x+y (x wing) 0 | straight | yes | 452 | 8.1% | 441 | 7.9% |
| corner -x+y | corner | **no** | 56 | 1.0% | 56 | 1.0% |
| straight -x-y (y wing) 0 | straight | yes | 454 | 8.1% | 448 | 8.0% |
| straight -x-y (x wing) 0 | straight | yes | 456 | 8.2% | 456 | 8.2% |
| corner -x-y | corner | **no** | 46 | 0.8% | 46 | 0.8% |
| straight +x-y (y wing) 0 | straight | yes | 455 | 8.1% | 455 | 8.1% |
| straight +x-y (x wing) 0 | straight | yes | 452 | 8.1% | 448 | 8.0% |
| corner +x-y | corner | **no** | 43 | 0.8% | 43 | 0.8% |
| **straight (8)** | | | 3631 | | 3610 | 64.6% |
| **corner (4)** | | | 194 | | 194 | 3.5% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 1788, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 544 | 13.5 | 276.2 | 0.26 | 0.65 | 0.0% |
| -x | 543 | 13.6 | 274.6 | 0.26 | 0.71 | 0.0% |
| +y | 527 | 13.6 | 270.4 | 0.26 | 0.69 | 0.0% |
| -y | 542 | 13.5 | 280.0 | 0.26 | 0.69 | 0.0% |
| door +x+y y | 427 | 1.0 | 275.8 | 0.93 | 1.50 | 67.9% |
| door +x+y x | 427 | 1.0 | 283.3 | 0.90 | 1.44 | 69.0% |
| door -x+y y | 436 | 1.2 | 298.2 | 0.88 | 1.38 | 63.3% |
| door -x+y x | 436 | 0.9 | 289.6 | 0.90 | 1.44 | 66.7% |
| door -x-y y | 437 | 0.9 | 287.9 | 0.91 | 1.38 | 69.0% |
| door -x-y x | 427 | 0.7 | 291.7 | 0.88 | 1.38 | 63.3% |
| door +x-y y | 422 | 1.2 | 287.0 | 0.88 | 1.38 | 75.9% |
| door +x-y x | 424 | 1.0 | 272.5 | 0.93 | 1.44 | 67.9% |

Mean flow / w J averaged over the doors 0.90, over the avenues 0.26.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 450 | 266 / 184 / 42 | 0.7 | 272.9 | 1.81 | 2.81 | 86% | 82% | 4% | 4.00 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 451 | 274 / 177 / 44 | 0.5 | 280.4 | 1.77 | 2.91 | 83% | 83% | 0% | 4.09 |
| corner +x+y | 1.20 | 31.2 | 49 | 0 / 49 / 0 | 4.5 | 71.7 | 0.73 | 1.30 | 12% | 0% | 12% | 0.66 |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 450 | 271 / 190 / 51 | 0.3 | 295.2 | 1.74 | 2.71 | 77% | 77% | 0% | 4.05 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 452 | 271 / 181 / 44 | 0.3 | 286.7 | 1.73 | 2.81 | 86% | 86% | 0% | 4.13 |
| corner -x+y | 1.20 | 31.2 | 56 | 0 / 56 / 0 | 4.4 | 102.5 | 0.57 | 0.90 | 18% | 0% | 18% | 1.10 |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 454 | 275 / 180 / 47 | 0.5 | 284.9 | 1.76 | 3.01 | 83% | 83% | 0% | 4.25 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 450 | 271 / 185 / 38 | 0.2 | 288.8 | 1.71 | 2.61 | 79% | 79% | 0% | 4.11 |
| corner -x-y | 1.20 | 31.2 | 46 | 0 / 46 / 0 | 4.0 | 98.1 | 0.49 | 0.80 | 10% | 0% | 10% | 0.60 |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 451 | 266 / 189 / 49 | 0.3 | 284.0 | 1.78 | 3.11 | 79% | 79% | 0% | 4.11 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 452 | 273 / 179 / 27 | 0.7 | 269.5 | 1.78 | 2.61 | 86% | 86% | 0% | 4.21 |
| corner +x-y | 1.20 | 31.2 | 43 | 0 / 43 / 0 | 4.5 | 81.9 | 0.55 | 0.80 | 11% | 0% | 11% | 0.62 |

The last agent out (agent 1582, t100 298.2 s): last gangway straight -x+y (y wing) 0, exit door -x+y (y wall). The gangway that cleared last: straight -x+y (y wing) 0 at 295.2 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.55 | 292.4 / 279.2 / 236.1 | 259.2 / 254.8 / 178.2 | 95764.2 | 352984 | 0.253 |
| gangway | 392 | 351.5 | 6.55 | 278.8 / 263.4 / 208.0 | 259.2 / 254.8 / 178.2 | 74382.5 | 199000 | 0.097 |
| walkway | 276 | 257.4 | 5.14 | 160.4 / 126.8 / 4.7 | 145.5 / 108.1 / 1.9 | 29.2 | 27219 | 0.504 |
| avenue | 408 | 384.3 | 2.45 | 181.0 / 5.8 / 0.0 | 155.0 / 1.2 / 0.0 | 0.0 | 28091 | 1.310 |
| exit | 40 | 9.7 | 0.00 | 290.0 / 276.9 / 207.6 | 222.3 / 196.2 / 72.8 | 917.1 | 3319 | 0.907 |
| concourse | 612 | 609.0 | 6.01 | 242.1 / 159.2 / 116.0 | 172.6 / 157.4 / 96.7 | 20435.4 | 95356 | 0.171 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.54 | 252.2 / 249.8 / 231.9 | 252.2 / 249.6 / 229.3 | 117864.9 | 338902 | 0.047 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -10.5 | -18.5 | gangway | 0.94 | 5.99 | 244.7 | 242.2 | 178.2 | 926.3 | 0.033 |
| 2 | 19.5 | 10.5 | gangway | 0.96 | 5.85 | 247.7 | 240.7 | 164.9 | 874.8 | 0.027 |
| 3 | -11.5 | -19.5 | gangway | 0.92 | 6.23 | 236.1 | 231.4 | 171.9 | 873.9 | 0.024 |
| 4 | -19.5 | 10.5 | gangway | 0.96 | 5.51 | 256.4 | 247.0 | 169.5 | 862.7 | 0.023 |
| 5 | 19.5 | -11.5 | gangway | 0.92 | 6.01 | 225.8 | 221.8 | 170.0 | 858.3 | 0.025 |
| 6 | -19.5 | -10.5 | gangway | 0.96 | 5.86 | 238.0 | 226.5 | 163.4 | 851.4 | 0.031 |
| 7 | 19.5 | -10.5 | gangway | 0.96 | 5.84 | 247.8 | 243.5 | 162.7 | 845.6 | 0.025 |
| 8 | -18.5 | 10.5 | gangway | 0.94 | 5.71 | 249.4 | 246.3 | 166.3 | 839.1 | 0.032 |
| 9 | 18.5 | -10.5 | gangway | 0.94 | 5.90 | 237.0 | 232.6 | 160.9 | 838.7 | 0.033 |
| 10 | 19.5 | 11.5 | gangway | 0.92 | 5.98 | 235.6 | 223.0 | 161.3 | 831.0 | 0.024 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -9.5 | -18.5 | seat row | 0.50 | 7.52 | 244.5 | 242.4 | 229.3 | 800.4 | 0.023 |
| 2 | -18.5 | 9.5 | seat row | 0.50 | 7.46 | 247.5 | 234.7 | 220.9 | 780.1 | 0.023 |
| 3 | 18.5 | 9.5 | seat row | 0.50 | 7.40 | 236.8 | 231.8 | 222.7 | 775.2 | 0.023 |
| 4 | 18.5 | -9.5 | seat row | 0.50 | 7.43 | 237.7 | 230.7 | 218.5 | 766.0 | 0.024 |
| 5 | -8.5 | -18.5 | seat row | 0.50 | 7.15 | 235.1 | 230.0 | 211.6 | 718.5 | 0.019 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 342; agent-steps of seated agents on another row's clearway: 2379.

## Deposit check

Person-seconds deposited: 695712.6, of them in excluded cells: 3826.550.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 28242 overlapping pair-steps: p99 0.0043, max 0.0119 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0043 max 0.0119; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 1 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.01 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 85 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
