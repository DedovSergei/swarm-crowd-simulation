# Experiment `S_load150_s8`

**Task 5.11 stage 1 (gridlock robustness, default model, AMD 26.10.1): venue S, 150% load (seed 8)**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 5592 agents (load 150.0%, requested 150%): every one of the 3728 seats and 1864 standing (spawnOvercrowdedCrowd, seed 8; below), buffer N = 8192, 1672 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 231200 evaluations, 4618 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.50)** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `15aa31e8667e4a9417fde7884d907d1832c5e2d6`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-23T17:40:06, 14.5 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Spawn (overcrowding)

| | |
|---|---|
| seated | 3728 (every seat) |
| standing | **1864** (requested round((1.50 - 1) x 3728) = 1864; at most 2143 = floor(2.5 p/m^2 x 857.4 m^2)) |
| standing floor | walkway + rear concourse, 857.4 m^2 |
| standing on the walkway / concourse / gangways | 545 / 1319 / 0 |
| **load** | **150.00%** of the seats (requested 150%) |
| standing crowd's mean density | 2.174 p/m^2 |
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 3.47, all circulation cells 3.47 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 8, 24889 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 681 | 119.1 |
| t90 | 1342 | 234.7 |
| t100 | 1672 | 292.4 |

t_p: the step by which ceil(p x 5592) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 540 | 75 | 13.5 | 278.5 | 21.6 | 52.1 | 13.1-23.1 |
| -x | 5.66 | 536 | 78 | 13.5 | 274.6 | 21.7 | 59.5 | 13.1-23.1 |
| +y | 5.66 | 534 | 78 | 13.5 | 273.9 | 21.7 | 53.2 | 13.1-23.1 |
| -y | 5.66 | 556 | 72 | 13.5 | 277.4 | 22.3 | 56.4 | 12.9-22.9 |
| door +x+y y | 1.20 | 422 | 667 | 0.9 | 279.0 | 75.8 | 120.4 | 154.3-164.2 |
| door +x+y x | 1.20 | 436 | 662 | 0.9 | 285.3 | 76.6 | 120.4 | 133.5-143.4 |
| door -x+y y | 1.20 | 426 | 660 | 0.7 | 275.8 | 77.4 | 115.3 | 110.9-120.9 |
| door -x+y x | 1.20 | 430 | 658 | 0.9 | 272.5 | 79.1 | 120.4 | 138.4-148.3 |
| door -x-y y | 1.20 | 433 | 667 | 0.7 | 266.2 | 81.5 | 120.4 | 152.3-162.3 |
| door -x-y x | 1.20 | 424 | 655 | 1.2 | 292.4 | 72.8 | 115.3 | 137.0-146.9 |
| door +x-y y | 1.20 | 436 | 661 | 1.0 | 272.5 | 80.3 | 120.4 | 141.3-151.3 |
| door +x-y x | 1.20 | 419 | 659 | 0.9 | 270.9 | 77.5 | 115.3 | 137.8-147.8 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 540 | 9.7% | 23.4% |
| -x | avenue | 5.66 | 536 | 9.6% | 23.2% |
| +y | avenue | 5.66 | 534 | 9.5% | 23.2% |
| -y | avenue | 5.66 | 556 | 9.9% | 24.1% |
| door +x+y y | door | 1.20 | 422 | 7.5% | 86.3% |
| door +x+y x | door | 1.20 | 436 | 7.8% | 89.2% |
| door -x+y y | door | 1.20 | 426 | 7.6% | 87.1% |
| door -x+y x | door | 1.20 | 430 | 7.7% | 87.9% |
| door -x-y y | door | 1.20 | 433 | 7.7% | 88.6% |
| door -x-y x | door | 1.20 | 424 | 7.6% | 86.7% |
| door +x-y y | door | 1.20 | 436 | 7.8% | 89.2% |
| door +x-y x | door | 1.20 | 419 | 7.5% | 85.7% |
| **doors (8)** | door | 9.60 | 3426 | 61.3% | |
| **avenues (4)** | avenue | 22.64 | 2166 | 38.7% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 292.4 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 42.6%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 452 | 8.1% | 452 | 8.1% |
| straight +x+y (x wing) 0 | straight | yes | 451 | 8.1% | 451 | 8.1% |
| corner +x+y | corner | **no** | 47 | 0.8% | 47 | 0.8% |
| straight -x+y (y wing) 0 | straight | yes | 451 | 8.1% | 451 | 8.1% |
| straight -x+y (x wing) 0 | straight | yes | 455 | 8.1% | 455 | 8.1% |
| corner -x+y | corner | **no** | 44 | 0.8% | 44 | 0.8% |
| straight -x-y (y wing) 0 | straight | yes | 451 | 8.1% | 443 | 7.9% |
| straight -x-y (x wing) 0 | straight | yes | 459 | 8.2% | 459 | 8.2% |
| corner -x-y | corner | **no** | 54 | 1.0% | 54 | 1.0% |
| straight +x-y (y wing) 0 | straight | yes | 451 | 8.1% | 451 | 8.1% |
| straight +x-y (x wing) 0 | straight | yes | 453 | 8.1% | 453 | 8.1% |
| corner +x-y | corner | **no** | 43 | 0.8% | 43 | 0.8% |
| **straight (8)** | | | 3623 | | 3615 | 64.6% |
| **corner (4)** | | | 188 | | 188 | 3.4% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 1789, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 540 | 13.5 | 278.5 | 0.26 | 0.62 | 0.0% |
| -x | 536 | 13.5 | 274.6 | 0.26 | 0.71 | 0.0% |
| +y | 534 | 13.5 | 273.9 | 0.26 | 0.64 | 0.0% |
| -y | 556 | 13.5 | 277.4 | 0.27 | 0.67 | 0.0% |
| door +x+y y | 422 | 0.9 | 279.0 | 0.91 | 1.44 | 67.9% |
| door +x+y x | 436 | 0.9 | 285.3 | 0.92 | 1.44 | 62.1% |
| door -x+y y | 426 | 0.7 | 275.8 | 0.93 | 1.38 | 71.4% |
| door -x+y x | 430 | 0.9 | 272.5 | 0.95 | 1.44 | 64.3% |
| door -x-y y | 433 | 0.7 | 266.2 | 0.97 | 1.44 | 70.4% |
| door -x-y x | 424 | 1.2 | 292.4 | 0.87 | 1.38 | 70.0% |
| door +x-y y | 436 | 1.0 | 272.5 | 0.96 | 1.44 | 71.4% |
| door +x-y x | 419 | 0.9 | 270.9 | 0.93 | 1.38 | 67.9% |

Mean flow / w J averaged over the doors 0.93, over the avenues 0.26.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 452 | 256 / 196 / 57 | 0.2 | 276.0 | 1.84 | 3.01 | 86% | 86% | 0% | 4.05 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 451 | 275 / 176 / 39 | 0.5 | 282.3 | 1.74 | 3.11 | 83% | 83% | 0% | 4.15 |
| corner +x+y | 1.20 | 31.2 | 47 | 0 / 47 / 0 | 4.5 | 91.5 | 0.54 | 0.80 | 10% | 0% | 10% | 0.62 |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 451 | 266 / 185 / 52 | 0.3 | 272.9 | 1.84 | 2.91 | 86% | 86% | 0% | 4.03 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 455 | 274 / 181 / 34 | 0.5 | 269.5 | 1.82 | 2.71 | 86% | 86% | 0% | 4.16 |
| corner -x+y | 1.20 | 31.2 | 44 | 0 / 44 / 0 | 4.5 | 58.6 | 0.81 | 1.50 | 17% | 0% | 17% | 0.57 |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 451 | 270 / 182 / 41 | 0.5 | 263.2 | 1.88 | 2.81 | 93% | 89% | 4% | 4.12 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 451 | 274 / 185 / 45 | 0.5 | 289.5 | 1.74 | 2.91 | 77% | 77% | 0% | 4.08 |
| corner -x-y | 1.20 | 31.2 | 54 | 0 / 54 / 0 | 3.8 | 88.0 | 0.64 | 1.10 | 22% | 0% | 22% | 1.13 |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 451 | 272 / 179 / 49 | 0.2 | 269.5 | 1.86 | 2.81 | 86% | 86% | 0% | 4.10 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 453 | 263 / 190 / 56 | 0.5 | 268.0 | 1.90 | 3.11 | 85% | 85% | 0% | 4.20 |
| corner +x-y | 1.20 | 31.2 | 43 | 0 / 43 / 0 | 4.5 | 83.6 | 0.54 | 0.80 | 11% | 0% | 11% | 0.61 |

The last agent out (agent 2003, t100 292.4 s): last gangway straight -x-y (x wing) 0, exit door -x-y (x wall). The gangway that cleared last: straight -x-y (x wing) 0 at 289.5 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.47 | 285.8 / 274.4 / 233.3 | 257.1 / 252.4 / 181.7 | 95273.9 | 351378 | 0.254 |
| gangway | 392 | 351.5 | 6.47 | 276.2 / 253.4 / 200.1 | 257.1 / 252.4 / 181.7 | 73620.1 | 198221 | 0.096 |
| walkway | 276 | 257.4 | 5.18 | 150.1 / 112.6 / 6.1 | 133.8 / 105.1 / 3.7 | 36.3 | 27315 | 0.503 |
| avenue | 408 | 384.3 | 2.45 | 176.1 / 8.9 / 0.0 | 139.2 / 1.2 / 0.0 | 0.0 | 28231 | 1.310 |
| exit | 40 | 9.7 | 0.00 | 283.0 / 273.7 / 207.3 | 213.7 / 193.1 / 74.0 | 911.0 | 3310 | 0.909 |
| concourse | 612 | 609.0 | 5.99 | 242.2 / 156.4 / 115.8 | 166.2 / 156.2 / 96.4 | 20706.5 | 94302 | 0.173 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.52 | 245.0 / 242.1 / 224.8 | 245.0 / 241.9 / 221.1 | 118557.8 | 340105 | 0.047 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -19.5 | 11.5 | gangway | 0.92 | 5.99 | 234.5 | 224.1 | 181.7 | 910.1 | 0.024 |
| 2 | -19.5 | -11.5 | gangway | 0.92 | 6.03 | 216.0 | 212.2 | 171.4 | 868.8 | 0.029 |
| 3 | 11.5 | -19.5 | gangway | 0.92 | 5.75 | 229.7 | 221.1 | 172.3 | 868.3 | 0.024 |
| 4 | -10.5 | -18.5 | gangway | 0.94 | 5.94 | 240.5 | 234.4 | 162.8 | 857.1 | 0.034 |
| 5 | 10.5 | 19.5 | gangway | 0.96 | 5.72 | 245.9 | 232.1 | 163.0 | 855.1 | 0.032 |
| 6 | -19.5 | 10.5 | gangway | 0.96 | 5.55 | 241.9 | 232.1 | 166.3 | 842.6 | 0.025 |
| 7 | -11.5 | 22.5 | gangway | 0.86 | 6.24 | 243.6 | 221.4 | 172.5 | 834.8 | 0.050 |
| 8 | -18.5 | 10.5 | gangway | 0.94 | 5.99 | 241.2 | 229.1 | 158.6 | 814.1 | 0.037 |
| 9 | 22.5 | 11.5 | gangway | 0.86 | 6.04 | 245.2 | 220.2 | 163.7 | 781.4 | 0.055 |
| 10 | 19.5 | -10.5 | gangway | 0.96 | 5.75 | 243.5 | 220.7 | 149.7 | 775.7 | 0.030 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 18.5 | 9.5 | seat row | 0.50 | 7.45 | 239.8 | 233.5 | 221.1 | 779.2 | 0.023 |
| 2 | -9.5 | -18.5 | seat row | 0.50 | 7.44 | 234.9 | 229.8 | 219.2 | 768.0 | 0.024 |
| 3 | 9.5 | -18.5 | seat row | 0.50 | 7.38 | 236.5 | 232.3 | 218.6 | 760.0 | 0.024 |
| 4 | -18.5 | 9.5 | seat row | 0.50 | 7.39 | 231.2 | 226.7 | 215.8 | 741.8 | 0.024 |
| 5 | 12.5 | 22.5 | seat row | 0.50 | 7.14 | 232.8 | 231.4 | 219.2 | 734.1 | 0.027 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 373; agent-steps of seated agents on another row's clearway: 2719.

## Deposit check

Person-seconds deposited: 695277.1, of them in excluded cells: 3793.517.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 24824 overlapping pair-steps: p99 0.0028, max 0.0062 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0028 max 0.0062; venue-geometry 1: p99 0.0002 max 0.0002 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 10 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 5.99 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 102 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
