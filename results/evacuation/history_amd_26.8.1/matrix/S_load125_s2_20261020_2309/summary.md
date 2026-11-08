# Experiment `S_load125_s2`

**Task 5.9 stage 4: venue S, 125% load (seed 2): every seat + standing on the walkway and concourse**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 4660 agents (load 125.0%, requested 125%): every one of the 3728 seats and 932 standing (spawnOvercrowdedCrowd, seed 2; below), buffer N = 8192, 1495 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 174092 evaluations, 3790 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.25)** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-20T23:09:44, 13.0 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Spawn (overcrowding)

| | |
|---|---|
| seated | 3728 (every seat) |
| standing | **932** (requested round((1.25 - 1) x 3728) = 932; at most 2143 = floor(2.5 p/m^2 x 857.4 m^2)) |
| standing floor | walkway + rear concourse, 857.4 m^2 |
| standing on the walkway / concourse / gangways | 254 / 678 / 0 |
| **load** | **125.00%** of the seats (requested 125%) |
| standing crowd's mean density | 1.087 p/m^2 |
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 2.51, all circulation cells 2.51 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 2, 6611 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 597 | 104.4 |
| t90 | 1214 | 212.3 |
| t100 | 1495 | 261.5 |

t_p: the step by which ceil(p x 4660) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 440 | 35 | 13.5 | 248.2 | 19.9 | 38.3 | 12.9-22.9 |
| -x | 5.66 | 446 | 34 | 13.5 | 247.7 | 20.2 | 36.2 | 13.1-23.1 |
| +y | 5.66 | 436 | 30 | 13.8 | 245.6 | 19.9 | 37.2 | 13.3-23.3 |
| -y | 5.66 | 435 | 42 | 13.8 | 247.5 | 19.7 | 40.4 | 13.1-23.1 |
| door +x+y y | 1.20 | 361 | 563 | 1.2 | 258.5 | 70.1 | 115.3 | 90.8-100.7 |
| door +x+y x | 1.20 | 366 | 573 | 1.2 | 255.0 | 72.1 | 115.3 | 98.8-108.8 |
| door -x+y y | 1.20 | 362 | 567 | 0.9 | 254.1 | 71.4 | 125.4 | 89.7-99.7 |
| door -x+y x | 1.20 | 363 | 570 | 1.6 | 247.8 | 73.6 | 115.3 | 98.8-108.8 |
| door -x-y y | 1.20 | 358 | 558 | 1.2 | 239.8 | 75.0 | 120.4 | 92.9-102.8 |
| door -x-y x | 1.20 | 360 | 556 | 0.9 | 244.7 | 73.8 | 125.4 | 86.1-96.0 |
| door +x-y y | 1.20 | 369 | 571 | 1.2 | 240.1 | 77.2 | 125.4 | 95.8-105.8 |
| door +x-y x | 1.20 | 364 | 561 | 1.2 | 261.5 | 69.9 | 120.4 | 85.4-95.3 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 440 | 9.4% | 21.3% |
| -x | avenue | 5.66 | 446 | 9.6% | 21.6% |
| +y | avenue | 5.66 | 436 | 9.4% | 21.1% |
| -y | avenue | 5.66 | 435 | 9.3% | 21.1% |
| door +x+y y | door | 1.20 | 361 | 7.7% | 82.6% |
| door +x+y x | door | 1.20 | 366 | 7.9% | 83.7% |
| door -x+y y | door | 1.20 | 362 | 7.8% | 82.8% |
| door -x+y x | door | 1.20 | 363 | 7.8% | 83.0% |
| door -x-y y | door | 1.20 | 358 | 7.7% | 81.9% |
| door -x-y x | door | 1.20 | 360 | 7.7% | 82.3% |
| door +x-y y | door | 1.20 | 369 | 7.9% | 84.4% |
| door +x-y x | door | 1.20 | 364 | 7.8% | 83.3% |
| **doors (8)** | door | 9.60 | 2903 | 62.3% | |
| **avenues (4)** | avenue | 22.64 | 1757 | 37.7% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 261.5 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 39.7%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 465 | 10.0% | 465 | 10.0% |
| straight +x+y (x wing) 0 | straight | yes | 461 | 9.9% | 460 | 9.9% |
| corner +x+y | corner | **no** | 15 | 0.3% | 15 | 0.3% |
| straight -x+y (y wing) 0 | straight | yes | 461 | 9.9% | 461 | 9.9% |
| straight -x+y (x wing) 0 | straight | yes | 462 | 9.9% | 462 | 9.9% |
| corner -x+y | corner | **no** | 17 | 0.4% | 17 | 0.4% |
| straight -x-y (y wing) 0 | straight | yes | 463 | 9.9% | 463 | 9.9% |
| straight -x-y (x wing) 0 | straight | yes | 464 | 10.0% | 464 | 10.0% |
| corner -x-y | corner | **no** | 13 | 0.3% | 13 | 0.3% |
| straight +x-y (y wing) 0 | straight | yes | 464 | 10.0% | 460 | 9.9% |
| straight +x-y (x wing) 0 | straight | yes | 466 | 10.0% | 466 | 10.0% |
| corner +x-y | corner | **no** | 15 | 0.3% | 15 | 0.3% |
| **straight (8)** | | | 3706 | | 3701 | 79.4% |
| **corner (4)** | | | 60 | | 60 | 1.3% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 899, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 440 | 13.5 | 248.2 | 0.24 | 0.46 | 0.0% |
| -x | 446 | 13.5 | 247.7 | 0.24 | 0.43 | 0.0% |
| +y | 436 | 13.8 | 245.6 | 0.24 | 0.45 | 0.0% |
| -y | 435 | 13.8 | 247.5 | 0.24 | 0.48 | 0.0% |
| door +x+y y | 361 | 1.2 | 258.5 | 0.84 | 1.38 | 61.5% |
| door +x+y x | 366 | 1.2 | 255.0 | 0.86 | 1.38 | 53.8% |
| door -x+y y | 362 | 0.9 | 254.1 | 0.85 | 1.50 | 42.3% |
| door -x+y x | 363 | 1.6 | 247.8 | 0.88 | 1.38 | 64.0% |
| door -x-y y | 358 | 1.2 | 239.8 | 0.90 | 1.44 | 64.0% |
| door -x-y x | 360 | 0.9 | 244.7 | 0.88 | 1.50 | 56.0% |
| door +x-y y | 369 | 1.2 | 240.1 | 0.92 | 1.50 | 68.0% |
| door +x-y x | 364 | 1.2 | 261.5 | 0.84 | 1.44 | 48.1% |

Mean flow / w J averaged over the doors 0.87, over the avenues 0.24.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 464 | 280 / 185 / 47 | 0.2 | 255.5 | 2.00 | 2.81 | 77% | 77% | 0% | 3.92 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 461 | 272 / 189 / 63 | 0.7 | 252.0 | 2.08 | 3.51 | 81% | 81% | 0% | 3.85 |
| corner +x+y | 1.20 | 31.2 | 15 | 0 / 15 / 0 | 4.5 | 37.1 | 0.46 | 0.70 | 25% | 0% | 25% | 0.15 |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 461 | 277 / 184 / 55 | 0.7 | 251.2 | 2.06 | 2.91 | 81% | 81% | 0% | 3.86 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 462 | 276 / 186 / 45 | 0.7 | 244.9 | 2.07 | 2.71 | 84% | 84% | 0% | 3.90 |
| corner -x+y | 1.20 | 31.2 | 17 | 0 / 17 / 0 | 4.5 | 37.4 | 0.51 | 0.80 | 0% | 0% | 0% | nan |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 463 | 278 / 185 / 38 | 0.7 | 236.8 | 2.12 | 2.61 | 88% | 88% | 0% | 3.79 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 464 | 280 / 184 / 55 | 0.7 | 241.7 | 2.15 | 2.81 | 84% | 84% | 0% | 3.81 |
| corner -x-y | 1.20 | 31.2 | 13 | 0 / 13 / 0 | 4.5 | 36.0 | 0.41 | 0.70 | 25% | 0% | 25% | 0.13 |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 464 | 279 / 185 / 52 | 0.3 | 237.2 | 2.18 | 2.91 | 92% | 88% | 4% | 3.82 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 462 | 283 / 183 / 51 | 0.7 | 258.5 | 2.00 | 3.11 | 77% | 77% | 0% | 3.91 |
| corner +x-y | 1.20 | 31.2 | 15 | 0 / 15 / 0 | 4.5 | 36.2 | 0.47 | 0.70 | 0% | 0% | 0% | nan |

The last agent out (agent 2935, t100 261.5 s): last gangway straight +x-y (x wing) 0, exit door +x-y (x wall). The gangway that cleared last: straight +x-y (x wing) 0 at 258.5 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.46 | 254.3 / 243.5 / 209.4 | 227.7 / 222.0 / 149.5 | 54739.9 | 235032 | 0.310 |
| gangway | 392 | 351.5 | 6.46 | 247.0 / 226.0 / 180.2 | 227.7 / 222.0 / 149.5 | 52575.3 | 159167 | 0.106 |
| walkway | 276 | 257.4 | 4.02 | 81.0 / 21.7 / 0.0 | 53.3 / 17.0 / 0.0 | 0.0 | 11064 | 1.040 |
| avenue | 408 | 384.3 | 2.38 | 109.7 / 0.9 / 0.0 | 79.4 / 0.7 / 0.0 | 0.0 | 22866 | 1.315 |
| exit | 40 | 9.7 | 0.00 | 252.6 / 242.4 / 168.1 | 175.6 / 152.0 / 52.3 | 617.8 | 2576 | 0.983 |
| concourse | 612 | 609.0 | 5.56 | 207.6 / 106.2 / 44.1 | 120.7 / 103.9 / 32.7 | 1546.8 | 39359 | 0.299 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.58 | 215.5 / 213.4 / 193.8 | 215.5 / 213.4 / 191.2 | 92766.2 | 287597 | 0.057 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 11.5 | -19.5 | gangway | 0.92 | 5.74 | 200.4 | 187.3 | 149.5 | 729.2 | 0.029 |
| 2 | 18.5 | -10.5 | gangway | 0.94 | 5.72 | 205.3 | 202.0 | 137.7 | 691.2 | 0.046 |
| 3 | 11.5 | 19.5 | gangway | 0.92 | 5.73 | 198.9 | 191.3 | 135.6 | 678.0 | 0.030 |
| 4 | 10.5 | -18.5 | gangway | 0.94 | 5.72 | 214.8 | 209.7 | 134.2 | 675.2 | 0.043 |
| 5 | -19.5 | 10.5 | gangway | 0.96 | 5.70 | 215.1 | 205.7 | 131.4 | 673.2 | 0.030 |
| 6 | -19.5 | -10.5 | gangway | 0.96 | 5.53 | 210.1 | 198.5 | 132.4 | 665.3 | 0.032 |
| 7 | -19.5 | 11.5 | gangway | 0.92 | 5.90 | 205.5 | 195.5 | 132.4 | 664.3 | 0.031 |
| 8 | 10.5 | 19.5 | gangway | 0.96 | 5.59 | 211.5 | 205.5 | 128.0 | 656.7 | 0.032 |
| 9 | -11.5 | -19.5 | gangway | 0.92 | 5.73 | 194.1 | 186.6 | 133.6 | 653.9 | 0.029 |
| 10 | 10.5 | 18.5 | gangway | 0.94 | 5.74 | 204.5 | 201.8 | 128.7 | 653.1 | 0.044 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 9.5 | -18.5 | seat row | 0.50 | 7.56 | 209.4 | 201.5 | 191.2 | 675.5 | 0.027 |
| 2 | -9.5 | 18.5 | seat row | 0.50 | 7.44 | 205.3 | 198.5 | 185.9 | 649.4 | 0.028 |
| 3 | -18.5 | 9.5 | seat row | 0.50 | 7.56 | 205.2 | 193.4 | 182.3 | 640.5 | 0.028 |
| 4 | 9.5 | 18.5 | seat row | 0.50 | 7.55 | 201.8 | 194.3 | 181.6 | 636.8 | 0.028 |
| 5 | 18.5 | -9.5 | seat row | 0.50 | 7.39 | 201.3 | 195.5 | 181.7 | 634.9 | 0.028 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 406; agent-steps of seated agents on another row's clearway: 2613.

## Deposit check

Person-seconds deposited: 524164.4, of them in excluded cells: 1534.750.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 33492 overlapping pair-steps: p99 0.0031, max 0.0074 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0031 max 0.0074; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 10 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 5.56 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 90 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
