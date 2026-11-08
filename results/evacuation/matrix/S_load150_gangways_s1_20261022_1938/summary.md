# Experiment `S_load150_gangways_s1`

**Task 5.10 stage 4 (AMD 26.10.1): venue S, 150% load (seed 1): standing also on the gangways**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 5592 agents (load 150.0%, requested 150%): every one of the 3728 seats and 1864 standing (spawnOvercrowdedCrowd, seed 1; below), buffer N = 8192, 1687 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 233614 evaluations, 4791 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.50)** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T19:38:27, 16.8 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Spawn (overcrowding)

| | |
|---|---|
| seated | 3728 (every seat) |
| standing | **1864** (requested round((1.50 - 1) x 3728) = 1864; at most 2831 = floor(2.5 p/m^2 x 1132.7 m^2)) |
| standing floor | walkway + rear concourse + gangways (the gangway-standing variant), 1132.7 m^2 |
| standing on the walkway / concourse / gangways | 436 / 1020 / 408 |
| **load** | **150.00%** of the seats (requested 150%) |
| standing crowd's mean density | 1.646 p/m^2 |
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 3.32, all circulation cells 3.32 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 1, 13977 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 683 | 119.5 |
| t90 | 1355 | 237.0 |
| t100 | 1687 | 295.1 |

t_p: the step by which ceil(p x 5592) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 537 | 61 | 13.6 | 273.7 | 21.9 | 48.9 | 13.5-23.4 |
| -x | 5.66 | 555 | 56 | 13.6 | 280.6 | 22.0 | 47.8 | 13.1-23.1 |
| +y | 5.66 | 546 | 59 | 13.6 | 277.6 | 21.9 | 51.0 | 13.1-23.1 |
| -y | 5.66 | 558 | 59 | 13.6 | 278.8 | 22.3 | 48.9 | 13.3-23.3 |
| door +x+y y | 1.20 | 425 | 667 | 1.2 | 274.4 | 77.7 | 125.4 | 120.3-130.3 |
| door +x+y x | 1.20 | 418 | 659 | 1.2 | 293.3 | 71.5 | 125.4 | 118.6-128.6 |
| door -x+y y | 1.20 | 425 | 676 | 1.0 | 295.1 | 72.2 | 120.4 | 115.8-125.8 |
| door -x+y x | 1.20 | 429 | 670 | 1.2 | 271.1 | 79.4 | 120.4 | 123.0-132.9 |
| door -x-y y | 1.20 | 418 | 669 | 0.9 | 293.8 | 71.3 | 120.4 | 116.5-126.5 |
| door -x-y x | 1.20 | 429 | 674 | 0.9 | 275.0 | 78.2 | 120.4 | 133.8-143.8 |
| door +x-y y | 1.20 | 433 | 666 | 1.0 | 280.2 | 77.5 | 115.3 | 85.9-95.8 |
| door +x-y x | 1.20 | 419 | 676 | 1.0 | 271.8 | 77.3 | 115.3 | 98.1-108.1 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 537 | 9.6% | 23.1% |
| -x | avenue | 5.66 | 555 | 9.9% | 23.9% |
| +y | avenue | 5.66 | 546 | 9.8% | 23.5% |
| -y | avenue | 5.66 | 558 | 10.0% | 24.0% |
| door +x+y y | door | 1.20 | 425 | 7.6% | 86.1% |
| door +x+y x | door | 1.20 | 418 | 7.5% | 84.7% |
| door -x+y y | door | 1.20 | 425 | 7.6% | 86.1% |
| door -x+y x | door | 1.20 | 429 | 7.7% | 87.0% |
| door -x-y y | door | 1.20 | 418 | 7.5% | 84.7% |
| door -x-y x | door | 1.20 | 429 | 7.7% | 87.0% |
| door +x-y y | door | 1.20 | 433 | 7.7% | 87.8% |
| door +x-y x | door | 1.20 | 419 | 7.5% | 84.9% |
| **doors (8)** | door | 9.60 | 3396 | 60.7% | |
| **avenues (4)** | avenue | 22.64 | 2196 | 39.3% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 295.1 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 42.2%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 485 | 8.7% | 478 | 8.5% |
| straight +x+y (x wing) 0 | straight | yes | 488 | 8.7% | 488 | 8.7% |
| corner +x+y | corner | **no** | 79 | 1.4% | 79 | 1.4% |
| straight -x+y (y wing) 0 | straight | yes | 485 | 8.7% | 485 | 8.7% |
| straight -x+y (x wing) 0 | straight | yes | 480 | 8.6% | 474 | 8.5% |
| corner -x+y | corner | **no** | 86 | 1.5% | 86 | 1.5% |
| straight -x-y (y wing) 0 | straight | yes | 484 | 8.7% | 484 | 8.7% |
| straight -x-y (x wing) 0 | straight | yes | 477 | 8.5% | 474 | 8.5% |
| corner -x-y | corner | **no** | 87 | 1.6% | 87 | 1.6% |
| straight +x-y (y wing) 0 | straight | yes | 479 | 8.6% | 479 | 8.6% |
| straight +x-y (x wing) 0 | straight | yes | 484 | 8.7% | 484 | 8.7% |
| corner +x-y | corner | **no** | 82 | 1.5% | 82 | 1.5% |
| **straight (8)** | | | 3862 | | 3846 | 68.8% |
| **corner (4)** | | | 334 | | 334 | 6.0% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 1412, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 537 | 13.6 | 273.7 | 0.26 | 0.59 | 0.0% |
| -x | 555 | 13.6 | 280.6 | 0.26 | 0.57 | 0.0% |
| +y | 546 | 13.6 | 277.6 | 0.26 | 0.61 | 0.0% |
| -y | 558 | 13.6 | 278.8 | 0.27 | 0.59 | 0.0% |
| door +x+y y | 425 | 1.2 | 274.4 | 0.93 | 1.50 | 64.3% |
| door +x+y x | 418 | 1.2 | 293.3 | 0.86 | 1.50 | 56.7% |
| door -x+y y | 425 | 1.0 | 295.1 | 0.86 | 1.44 | 60.0% |
| door -x+y x | 429 | 1.2 | 271.1 | 0.95 | 1.44 | 57.1% |
| door -x-y y | 418 | 0.9 | 293.8 | 0.85 | 1.44 | 63.3% |
| door -x-y x | 429 | 0.9 | 275.0 | 0.94 | 1.44 | 60.7% |
| door +x-y y | 433 | 1.0 | 280.2 | 0.93 | 1.38 | 69.0% |
| door +x-y x | 419 | 1.0 | 271.8 | 0.92 | 1.38 | 64.3% |

Mean flow / w J averaged over the doors 0.90, over the avenues 0.26.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 485 | 305 / 181 / 30 | 0.2 | 271.5 | 1.90 | 2.91 | 89% | 86% | 4% | 4.06 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 481 | 299 / 189 / 40 | 0.2 | 290.3 | 1.82 | 2.91 | 77% | 77% | 0% | 3.90 |
| corner +x+y | 1.20 | 31.2 | 79 | 3 / 78 / 0 | 0.2 | 116.3 | 0.70 | 1.00 | 17% | 0% | 17% | 1.84 |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 479 | 289 / 196 / 46 | 0.2 | 292.1 | 1.82 | 2.71 | 80% | 77% | 3% | 3.90 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 480 | 307 / 173 / 24 | 0.2 | 268.1 | 1.88 | 2.61 | 93% | 89% | 4% | 4.14 |
| corner -x+y | 1.20 | 31.2 | 86 | 3 / 84 / 0 | 0.2 | 108.4 | 0.80 | 1.20 | 18% | 9% | 9% | 2.02 |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 481 | 293 / 191 / 38 | 0.2 | 290.9 | 1.79 | 3.21 | 80% | 77% | 3% | 3.91 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 477 | 293 / 185 / 28 | 0.2 | 272.0 | 1.86 | 2.61 | 89% | 86% | 4% | 4.00 |
| corner -x-y | 1.20 | 31.2 | 87 | 2 / 85 / 0 | 0.2 | 114.4 | 0.76 | 1.10 | 17% | 8% | 8% | 2.05 |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 479 | 305 / 177 / 30 | 0.2 | 277.2 | 1.85 | 2.61 | 86% | 86% | 0% | 4.01 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 484 | 291 / 193 / 48 | 0.2 | 268.8 | 1.98 | 2.91 | 85% | 85% | 0% | 4.06 |
| corner +x-y | 1.20 | 31.2 | 82 | 4 / 78 / 0 | 0.2 | 110.9 | 0.74 | 1.20 | 8% | 0% | 8% | 1.62 |

The last agent out (agent 1487, t100 295.1 s): last gangway straight -x+y (y wing) 0, exit door -x+y (y wall). The gangway that cleared last: straight -x+y (y wing) 0 at 292.1 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.53 | 287.5 / 279.7 / 243.5 | 262.4 / 255.0 / 187.2 | 78547.3 | 334198 | 0.273 |
| gangway | 392 | 351.5 | 6.53 | 271.6 / 258.3 / 221.6 | 262.4 / 255.0 / 187.2 | 68004.5 | 208387 | 0.102 |
| walkway | 276 | 257.4 | 4.92 | 173.5 / 134.0 / 0.0 | 149.5 / 112.5 / 0.0 | 0.0 | 25151 | 0.574 |
| avenue | 408 | 384.3 | 2.51 | 186.8 / 5.6 / 0.0 | 163.2 / 1.0 / 0.0 | 0.0 | 28637 | 1.310 |
| exit | 40 | 9.7 | 0.00 | 287.2 / 277.6 / 199.9 | 210.1 / 180.3 / 63.5 | 812.7 | 3164 | 0.960 |
| concourse | 612 | 609.0 | 5.89 | 241.4 / 133.6 / 86.8 | 149.7 / 133.5 / 69.8 | 9730.0 | 68860 | 0.219 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.55 | 254.7 / 253.1 / 247.3 | 254.7 / 253.1 / 245.7 | 126356.8 | 365451 | 0.045 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -18.5 | -10.5 | gangway | 0.94 | 5.92 | 255.7 | 250.6 | 187.2 | 945.9 | 0.032 |
| 2 | -18.5 | 10.5 | gangway | 0.94 | 6.01 | 252.9 | 244.0 | 176.1 | 931.1 | 0.027 |
| 3 | 10.5 | 18.5 | gangway | 0.94 | 5.83 | 256.4 | 245.7 | 183.8 | 921.0 | 0.029 |
| 4 | 19.5 | 10.5 | gangway | 0.96 | 5.58 | 238.2 | 232.6 | 175.3 | 894.1 | 0.030 |
| 5 | 11.5 | 18.5 | gangway | 0.86 | 6.22 | 241.9 | 230.5 | 181.7 | 876.3 | 0.028 |
| 6 | -19.5 | -11.5 | gangway | 0.92 | 5.84 | 241.0 | 234.2 | 173.7 | 866.2 | 0.023 |
| 7 | 18.5 | -10.5 | gangway | 0.94 | 6.05 | 235.9 | 234.9 | 162.7 | 845.9 | 0.038 |
| 8 | -10.5 | -18.5 | gangway | 0.94 | 5.89 | 235.4 | 231.8 | 167.4 | 838.7 | 0.037 |
| 9 | 11.5 | 19.5 | gangway | 0.92 | 5.95 | 244.7 | 232.6 | 165.3 | 837.7 | 0.024 |
| 10 | 11.5 | -18.5 | gangway | 0.86 | 6.28 | 231.2 | 225.5 | 172.8 | 835.8 | 0.029 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 9.5 | 18.5 | seat row | 0.50 | 7.42 | 254.7 | 253.1 | 245.7 | 863.2 | 0.021 |
| 2 | -18.5 | -9.5 | seat row | 0.50 | 7.42 | 249.8 | 246.3 | 241.5 | 836.3 | 0.022 |
| 3 | -18.5 | 9.5 | seat row | 0.50 | 7.43 | 250.3 | 248.7 | 237.9 | 829.4 | 0.021 |
| 4 | 9.5 | -18.5 | seat row | 0.50 | 7.46 | 246.6 | 245.0 | 234.9 | 822.5 | 0.022 |
| 5 | 8.5 | 18.5 | seat row | 0.50 | 7.13 | 248.9 | 247.0 | 238.7 | 801.7 | 0.018 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 284; agent-steps of seated agents on another row's clearway: 1913.

## Deposit check

Person-seconds deposited: 702439.5, of them in excluded cells: 2789.841.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 35175 overlapping pair-steps: p99 0.0032, max 0.0079 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0032 max 0.0079; venue-geometry 1: p99 0.0002 max 0.0002 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 7 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 5.89 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 61 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
