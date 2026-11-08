# Experiment `S_load150_s10`

**Task 5.11 stage 1 (gridlock robustness, default model, AMD 26.10.1): venue S, 150% load (seed 10)**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 5592 agents (load 150.0%, requested 150%): every one of the 3728 seats and 1864 standing (spawnOvercrowdedCrowd, seed 10; below), buffer N = 8192, 1678 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 229989 evaluations, 4651 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.50)** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `15aa31e8667e4a9417fde7884d907d1832c5e2d6`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-23T17:40:43, 14.5 s wall.

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
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 3.53, all circulation cells 3.53 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 10, 23617 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 680 | 118.9 |
| t90 | 1333 | 233.2 |
| t100 | 1678 | 293.5 |

t_p: the step by which ceil(p x 5592) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 536 | 69 | 13.5 | 276.9 | 21.6 | 53.2 | 13.5-23.4 |
| -x | 5.66 | 536 | 77 | 13.5 | 276.9 | 21.6 | 57.4 | 13.3-23.3 |
| +y | 5.66 | 552 | 67 | 13.6 | 275.0 | 22.4 | 51.0 | 13.5-23.4 |
| -y | 5.66 | 525 | 77 | 13.6 | 272.3 | 21.5 | 58.5 | 13.5-23.4 |
| door +x+y y | 1.20 | 434 | 667 | 1.0 | 267.4 | 81.4 | 115.3 | 150.1-160.0 |
| door +x+y x | 1.20 | 427 | 660 | 0.9 | 288.2 | 74.2 | 120.4 | 138.2-148.1 |
| door -x+y y | 1.20 | 433 | 656 | 1.2 | 283.0 | 76.8 | 120.4 | 141.1-151.1 |
| door -x+y x | 1.20 | 424 | 673 | 0.9 | 267.4 | 79.5 | 120.4 | 150.4-160.4 |
| door -x-y y | 1.20 | 429 | 661 | 0.9 | 287.0 | 74.9 | 120.4 | 153.6-163.5 |
| door -x-y x | 1.20 | 431 | 659 | 0.7 | 276.0 | 78.2 | 120.4 | 140.8-150.8 |
| door +x-y y | 1.20 | 430 | 662 | 1.6 | 293.5 | 73.6 | 115.3 | 129.8-139.8 |
| door +x-y x | 1.20 | 435 | 664 | 1.0 | 278.1 | 78.5 | 125.4 | 142.4-152.3 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 536 | 9.6% | 23.2% |
| -x | avenue | 5.66 | 536 | 9.6% | 23.2% |
| +y | avenue | 5.66 | 552 | 9.9% | 23.8% |
| -y | avenue | 5.66 | 525 | 9.4% | 22.7% |
| door +x+y y | door | 1.20 | 434 | 7.8% | 88.4% |
| door +x+y x | door | 1.20 | 427 | 7.6% | 87.0% |
| door -x+y y | door | 1.20 | 433 | 7.7% | 88.2% |
| door -x+y x | door | 1.20 | 424 | 7.6% | 86.4% |
| door -x-y y | door | 1.20 | 429 | 7.7% | 87.4% |
| door -x-y x | door | 1.20 | 431 | 7.7% | 87.8% |
| door +x-y y | door | 1.20 | 430 | 7.7% | 87.6% |
| door +x-y x | door | 1.20 | 435 | 7.8% | 88.6% |
| **doors (8)** | door | 9.60 | 3443 | 61.6% | |
| **avenues (4)** | avenue | 22.64 | 2149 | 38.4% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 293.5 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 42.4%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 452 | 8.1% | 447 | 8.0% |
| straight +x+y (x wing) 0 | straight | yes | 458 | 8.2% | 458 | 8.2% |
| corner +x+y | corner | **no** | 48 | 0.9% | 48 | 0.9% |
| straight -x+y (y wing) 0 | straight | yes | 453 | 8.1% | 453 | 8.1% |
| straight -x+y (x wing) 0 | straight | yes | 441 | 7.9% | 441 | 7.9% |
| corner -x+y | corner | **no** | 61 | 1.1% | 61 | 1.1% |
| straight -x-y (y wing) 0 | straight | yes | 456 | 8.2% | 456 | 8.2% |
| straight -x-y (x wing) 0 | straight | yes | 456 | 8.2% | 455 | 8.1% |
| corner -x-y | corner | **no** | 39 | 0.7% | 39 | 0.7% |
| straight +x-y (y wing) 0 | straight | yes | 457 | 8.2% | 457 | 8.2% |
| straight +x-y (x wing) 0 | straight | yes | 451 | 8.1% | 440 | 7.9% |
| corner +x-y | corner | **no** | 54 | 1.0% | 54 | 1.0% |
| **straight (8)** | | | 3624 | | 3607 | 64.5% |
| **corner (4)** | | | 202 | | 202 | 3.6% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 1783, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 536 | 13.5 | 276.9 | 0.26 | 0.64 | 0.0% |
| -x | 536 | 13.5 | 276.9 | 0.26 | 0.69 | 0.0% |
| +y | 552 | 13.6 | 275.0 | 0.27 | 0.61 | 0.0% |
| -y | 525 | 13.6 | 272.3 | 0.26 | 0.70 | 0.0% |
| door +x+y y | 434 | 1.0 | 267.4 | 0.97 | 1.38 | 70.4% |
| door +x+y x | 427 | 0.9 | 288.2 | 0.89 | 1.44 | 65.5% |
| door -x+y y | 433 | 1.2 | 283.0 | 0.92 | 1.44 | 62.1% |
| door -x+y x | 424 | 0.9 | 267.4 | 0.95 | 1.44 | 77.8% |
| door -x-y y | 429 | 0.9 | 287.0 | 0.90 | 1.44 | 65.5% |
| door -x-y x | 431 | 0.7 | 276.0 | 0.94 | 1.44 | 64.3% |
| door +x-y y | 430 | 1.6 | 293.5 | 0.88 | 1.38 | 60.0% |
| door +x-y x | 435 | 1.0 | 278.1 | 0.94 | 1.50 | 75.0% |

Mean flow / w J averaged over the doors 0.92, over the avenues 0.26.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 452 | 273 / 179 / 40 | 0.5 | 264.5 | 1.86 | 2.91 | 89% | 89% | 0% | 4.12 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 453 | 271 / 187 / 61 | 0.5 | 285.3 | 1.82 | 3.01 | 79% | 79% | 0% | 4.06 |
| corner +x+y | 1.20 | 31.2 | 48 | 0 / 48 / 0 | 4.2 | 93.6 | 0.54 | 0.80 | 20% | 0% | 20% | 1.03 |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 453 | 277 / 176 / 40 | 0.5 | 280.0 | 1.76 | 3.01 | 83% | 83% | 0% | 4.18 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 441 | 258 / 183 / 44 | 0.2 | 264.5 | 1.83 | 2.91 | 85% | 85% | 0% | 4.15 |
| corner -x+y | 1.20 | 31.2 | 61 | 1 / 60 / 0 | 0.3 | 88.0 | 0.69 | 1.20 | 22% | 0% | 22% | 1.26 |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 455 | 269 / 188 / 58 | 0.3 | 284.0 | 1.81 | 3.01 | 83% | 79% | 3% | 4.09 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 456 | 270 / 186 / 45 | 0.2 | 273.0 | 1.83 | 3.01 | 86% | 86% | 0% | 4.11 |
| corner -x-y | 1.20 | 31.2 | 39 | 0 / 39 / 0 | 4.0 | 47.6 | 0.89 | 1.60 | 0% | 0% | 0% | nan |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 446 | 269 / 188 / 53 | 0.5 | 290.5 | 1.76 | 3.11 | 77% | 73% | 3% | 3.97 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 451 | 271 / 180 / 42 | 0.5 | 275.1 | 1.79 | 3.01 | 89% | 86% | 4% | 4.18 |
| corner +x-y | 1.20 | 31.2 | 54 | 0 / 54 / 0 | 4.2 | 102.7 | 0.55 | 0.80 | 9% | 0% | 9% | 0.70 |

The last agent out (agent 3401, t100 293.5 s): last gangway straight +x-y (y wing) 0, exit door +x-y (y wall). The gangway that cleared last: straight +x-y (y wing) 0 at 290.5 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.46 | 289.6 / 275.3 / 233.0 | 255.4 / 251.2 / 173.0 | 97085.5 | 352882 | 0.252 |
| gangway | 392 | 351.5 | 6.46 | 279.5 / 252.6 / 203.2 | 255.4 / 251.2 / 173.0 | 75222.5 | 198170 | 0.097 |
| walkway | 276 | 257.4 | 5.00 | 165.1 / 122.8 / 0.3 | 142.0 / 109.0 / 0.3 | 1.7 | 27496 | 0.501 |
| avenue | 408 | 384.3 | 2.51 | 177.5 / 5.9 / 0.0 | 148.7 / 0.9 / 0.0 | 0.0 | 28008 | 1.310 |
| exit | 40 | 9.7 | 0.00 | 286.0 / 274.6 / 205.7 | 216.7 / 192.6 / 74.2 | 921.4 | 3308 | 0.910 |
| concourse | 612 | 609.0 | 6.05 | 240.1 / 157.6 / 113.0 | 172.3 / 157.6 / 95.0 | 20939.8 | 95901 | 0.170 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.53 | 245.0 / 239.4 / 230.0 | 245.0 / 239.3 / 227.4 | 115551.3 | 334891 | 0.048 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 18.5 | -10.5 | gangway | 0.94 | 5.99 | 244.9 | 241.0 | 173.0 | 894.0 | 0.034 |
| 2 | -10.5 | 18.5 | gangway | 0.94 | 5.97 | 239.3 | 234.7 | 168.6 | 868.2 | 0.033 |
| 3 | 10.5 | 18.5 | gangway | 0.94 | 5.87 | 242.2 | 236.3 | 169.7 | 862.2 | 0.034 |
| 4 | -10.5 | -18.5 | gangway | 0.94 | 6.03 | 237.0 | 226.3 | 160.0 | 830.4 | 0.043 |
| 5 | 19.5 | -11.5 | gangway | 0.92 | 6.05 | 231.1 | 225.6 | 160.6 | 805.6 | 0.023 |
| 6 | -22.5 | -11.5 | gangway | 0.86 | 6.14 | 245.0 | 227.4 | 167.7 | 802.9 | 0.049 |
| 7 | 11.5 | 18.5 | gangway | 0.86 | 6.22 | 230.7 | 227.0 | 165.8 | 799.7 | 0.033 |
| 8 | -19.5 | 10.5 | gangway | 0.96 | 5.54 | 242.8 | 227.9 | 156.9 | 799.6 | 0.027 |
| 9 | 21.5 | -11.5 | gangway | 0.89 | 6.07 | 246.8 | 240.0 | 164.1 | 799.3 | 0.036 |
| 10 | -19.5 | -10.5 | gangway | 0.96 | 5.63 | 247.3 | 240.8 | 154.3 | 794.2 | 0.027 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 18.5 | -9.5 | seat row | 0.50 | 7.47 | 240.0 | 237.7 | 227.4 | 797.8 | 0.023 |
| 2 | -9.5 | 18.5 | seat row | 0.50 | 7.53 | 238.4 | 234.9 | 220.0 | 775.9 | 0.023 |
| 3 | 9.5 | 18.5 | seat row | 0.50 | 7.46 | 235.9 | 230.4 | 218.5 | 766.9 | 0.023 |
| 4 | -18.5 | -9.5 | seat row | 0.50 | 7.50 | 238.6 | 224.2 | 215.5 | 757.7 | 0.024 |
| 5 | -22.5 | -12.5 | seat row | 0.50 | 7.11 | 225.1 | 223.7 | 211.1 | 710.7 | 0.028 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 383; agent-steps of seated agents on another row's clearway: 2586.

## Deposit check

Person-seconds deposited: 691712.1, of them in excluded cells: 3939.370.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 22989 overlapping pair-steps: p99 0.0037, max 0.0074 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0037 max 0.0074; venue-geometry 1: p99 0.0001 max 0.0001 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 6 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.05 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 91 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
