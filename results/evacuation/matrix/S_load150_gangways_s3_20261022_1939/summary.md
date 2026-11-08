# Experiment `S_load150_gangways_s3`

**Task 5.10 stage 4 (AMD 26.10.1): venue S, 150% load (seed 3): standing also on the gangways**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 5592 agents (load 150.0%, requested 150%): every one of the 3728 seats and 1864 standing (spawnOvercrowdedCrowd, seed 3; below), buffer N = 8192, 1720 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 235162 evaluations, 4858 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.50)** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T19:39:10, 16.7 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Spawn (overcrowding)

| | |
|---|---|
| seated | 3728 (every seat) |
| standing | **1864** (requested round((1.50 - 1) x 3728) = 1864; at most 2831 = floor(2.5 p/m^2 x 1132.7 m^2)) |
| standing floor | walkway + rear concourse + gangways (the gangway-standing variant), 1132.7 m^2 |
| standing on the walkway / concourse / gangways | 413 / 1015 / 436 |
| **load** | **150.00%** of the seats (requested 150%) |
| standing crowd's mean density | 1.646 p/m^2 |
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 3.29, all circulation cells 3.29 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 3, 14021 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 687 | 120.2 |
| t90 | 1365 | 238.7 |
| t100 | 1720 | 300.8 |

t_p: the step by which ceil(p x 5592) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 537 | 54 | 13.5 | 285.1 | 20.9 | 43.6 | 13.3-23.3 |
| -x | 5.66 | 550 | 60 | 13.6 | 282.1 | 21.7 | 53.2 | 13.3-23.3 |
| +y | 5.66 | 556 | 63 | 13.5 | 275.0 | 22.5 | 50.0 | 13.1-23.1 |
| -y | 5.66 | 551 | 53 | 13.6 | 280.2 | 21.9 | 40.4 | 13.1-23.1 |
| door +x+y y | 1.20 | 414 | 664 | 0.9 | 291.2 | 71.3 | 105.3 | 128.4-138.4 |
| door +x+y x | 1.20 | 429 | 673 | 0.9 | 285.8 | 75.2 | 120.4 | 120.3-130.3 |
| door -x+y y | 1.20 | 420 | 671 | 1.4 | 292.1 | 72.2 | 115.3 | 113.2-123.1 |
| door -x+y x | 1.20 | 428 | 674 | 0.9 | 287.2 | 74.7 | 115.3 | 129.1-139.1 |
| door -x-y y | 1.20 | 432 | 678 | 1.0 | 290.0 | 74.7 | 125.4 | 123.0-132.9 |
| door -x-y x | 1.20 | 423 | 664 | 0.9 | 294.9 | 71.9 | 120.4 | 85.9-95.8 |
| door +x-y y | 1.20 | 427 | 670 | 0.9 | 286.7 | 74.7 | 115.3 | 126.5-136.4 |
| door +x-y x | 1.20 | 425 | 668 | 1.0 | 300.8 | 70.8 | 115.3 | 118.2-128.2 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 537 | 9.6% | 22.6% |
| -x | avenue | 5.66 | 550 | 9.8% | 23.2% |
| +y | avenue | 5.66 | 556 | 9.9% | 23.4% |
| -y | avenue | 5.66 | 551 | 9.9% | 23.2% |
| door +x+y y | door | 1.20 | 414 | 7.4% | 82.3% |
| door +x+y x | door | 1.20 | 429 | 7.7% | 85.3% |
| door -x+y y | door | 1.20 | 420 | 7.5% | 83.5% |
| door -x+y x | door | 1.20 | 428 | 7.7% | 85.1% |
| door -x-y y | door | 1.20 | 432 | 7.7% | 85.9% |
| door -x-y x | door | 1.20 | 423 | 7.6% | 84.1% |
| door +x-y y | door | 1.20 | 427 | 7.6% | 84.9% |
| door +x-y x | door | 1.20 | 425 | 7.6% | 84.5% |
| **doors (8)** | door | 9.60 | 3398 | 60.8% | |
| **avenues (4)** | avenue | 22.64 | 2194 | 39.2% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 300.8 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 41.4%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 479 | 8.6% | 479 | 8.6% |
| straight +x+y (x wing) 0 | straight | yes | 486 | 8.7% | 484 | 8.7% |
| corner +x+y | corner | **no** | 86 | 1.5% | 86 | 1.5% |
| straight -x+y (y wing) 0 | straight | yes | 481 | 8.6% | 481 | 8.6% |
| straight -x+y (x wing) 0 | straight | yes | 484 | 8.7% | 483 | 8.6% |
| corner -x+y | corner | **no** | 97 | 1.7% | 97 | 1.7% |
| straight -x-y (y wing) 0 | straight | yes | 486 | 8.7% | 475 | 8.5% |
| straight -x-y (x wing) 0 | straight | yes | 493 | 8.8% | 493 | 8.8% |
| corner -x-y | corner | **no** | 85 | 1.5% | 85 | 1.5% |
| straight +x-y (y wing) 0 | straight | yes | 485 | 8.7% | 476 | 8.5% |
| straight +x-y (x wing) 0 | straight | yes | 494 | 8.8% | 494 | 8.8% |
| corner +x-y | corner | **no** | 80 | 1.4% | 80 | 1.4% |
| **straight (8)** | | | 3888 | | 3865 | 69.1% |
| **corner (4)** | | | 348 | | 348 | 6.2% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 1379, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 537 | 13.5 | 285.1 | 0.25 | 0.52 | 0.0% |
| -x | 550 | 13.6 | 282.1 | 0.26 | 0.64 | 0.0% |
| +y | 556 | 13.5 | 275.0 | 0.27 | 0.60 | 0.0% |
| -y | 551 | 13.6 | 280.2 | 0.26 | 0.48 | 0.0% |
| door +x+y y | 414 | 0.9 | 291.2 | 0.85 | 1.26 | 63.3% |
| door +x+y x | 429 | 0.9 | 285.8 | 0.90 | 1.44 | 69.0% |
| door -x+y y | 420 | 1.4 | 292.1 | 0.86 | 1.38 | 50.0% |
| door -x+y x | 428 | 0.9 | 287.2 | 0.89 | 1.38 | 69.0% |
| door -x-y y | 432 | 1.0 | 290.0 | 0.89 | 1.50 | 60.0% |
| door -x-y x | 423 | 0.9 | 294.9 | 0.86 | 1.44 | 53.3% |
| door +x-y y | 427 | 0.9 | 286.7 | 0.89 | 1.38 | 55.2% |
| door +x-y x | 425 | 1.0 | 300.8 | 0.85 | 1.38 | 58.1% |

Mean flow / w J averaged over the doors 0.88, over the avenues 0.26.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 477 | 286 / 193 / 48 | 0.2 | 288.2 | 1.83 | 2.91 | 83% | 83% | 0% | 3.95 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 486 | 305 / 182 / 36 | 0.2 | 282.8 | 1.85 | 2.91 | 86% | 86% | 0% | 3.99 |
| corner +x+y | 1.20 | 31.2 | 86 | 4 / 83 / 0 | 0.2 | 115.3 | 0.75 | 1.30 | 17% | 8% | 8% | 1.87 |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 480 | 287 / 194 / 51 | 0.2 | 289.1 | 1.84 | 2.81 | 83% | 79% | 3% | 3.95 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 484 | 305 / 179 / 39 | 0.2 | 284.2 | 1.84 | 3.01 | 86% | 83% | 3% | 3.99 |
| corner -x+y | 1.20 | 31.2 | 97 | 10 / 89 / 0 | 0.2 | 118.4 | 0.84 | 1.20 | 25% | 17% | 8% | 2.28 |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 486 | 304 / 184 / 40 | 0.2 | 287.0 | 1.84 | 3.01 | 86% | 86% | 0% | 4.09 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 482 | 301 / 192 / 50 | 0.2 | 291.9 | 1.86 | 2.81 | 77% | 73% | 3% | 3.92 |
| corner -x-y | 1.20 | 31.2 | 85 | 3 / 83 / 0 | 0.2 | 111.8 | 0.77 | 1.10 | 8% | 0% | 8% | 1.71 |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 485 | 300 / 187 / 44 | 0.2 | 283.7 | 1.87 | 2.81 | 86% | 86% | 0% | 4.00 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 485 | 298 / 196 / 52 | 0.2 | 297.9 | 1.83 | 2.91 | 80% | 77% | 3% | 3.99 |
| corner +x-y | 1.20 | 31.2 | 80 | 3 / 78 / 0 | 0.2 | 105.1 | 0.77 | 1.30 | 18% | 0% | 18% | 1.94 |

The last agent out (agent 2911, t100 300.8 s): last gangway straight +x-y (x wing) 0, exit door +x-y (x wall). The gangway that cleared last: straight +x-y (x wing) 0 at 297.9 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.47 | 293.5 / 284.7 / 242.1 | 264.6 / 257.6 / 204.1 | 80831.7 | 335925 | 0.273 |
| gangway | 392 | 351.5 | 6.47 | 277.6 / 261.7 / 218.8 | 264.6 / 257.6 / 204.1 | 70304.1 | 209792 | 0.102 |
| walkway | 276 | 257.4 | 5.00 | 165.8 / 132.2 / 0.0 | 138.5 / 112.3 / 0.0 | 0.0 | 24394 | 0.594 |
| avenue | 408 | 384.3 | 2.40 | 182.8 / 9.1 / 0.0 | 161.8 / 0.7 / 0.0 | 0.0 | 28597 | 1.310 |
| exit | 40 | 9.7 | 0.00 | 292.1 / 283.7 / 197.6 | 210.1 / 181.6 / 66.1 | 818.6 | 3185 | 0.955 |
| concourse | 612 | 609.0 | 5.86 | 241.4 / 137.7 / 88.3 | 151.3 / 137.0 / 71.7 | 9709.0 | 69956 | 0.217 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.57 | 254.5 / 253.6 / 246.6 | 254.5 / 253.6 / 244.7 | 128297.1 | 368372 | 0.044 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 18.5 | 10.5 | gangway | 0.94 | 5.72 | 254.1 | 245.0 | 204.1 | 1028.1 | 0.032 |
| 2 | -10.5 | -18.5 | gangway | 0.94 | 5.95 | 253.1 | 243.6 | 201.0 | 1014.5 | 0.030 |
| 3 | -19.5 | 10.5 | gangway | 0.96 | 5.82 | 254.7 | 249.9 | 174.2 | 910.1 | 0.027 |
| 4 | -18.5 | 10.5 | gangway | 0.94 | 5.83 | 250.3 | 246.1 | 181.2 | 906.3 | 0.032 |
| 5 | 11.5 | -18.5 | gangway | 0.86 | 6.16 | 243.3 | 235.8 | 186.5 | 906.2 | 0.031 |
| 6 | 18.5 | 11.5 | gangway | 0.86 | 6.01 | 241.4 | 237.9 | 188.2 | 905.8 | 0.030 |
| 7 | -10.5 | -19.5 | gangway | 0.96 | 5.50 | 257.5 | 253.3 | 178.4 | 899.7 | 0.025 |
| 8 | -11.5 | -18.5 | gangway | 0.86 | 6.30 | 242.1 | 236.8 | 178.8 | 875.7 | 0.031 |
| 9 | 11.5 | 19.5 | gangway | 0.92 | 5.69 | 223.0 | 220.6 | 177.0 | 862.1 | 0.026 |
| 10 | 10.5 | -18.5 | gangway | 0.94 | 5.81 | 256.1 | 249.9 | 158.3 | 809.0 | 0.029 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 9.5 | -18.5 | seat row | 0.50 | 7.50 | 254.5 | 253.6 | 244.7 | 857.6 | 0.021 |
| 2 | -9.5 | -18.5 | seat row | 0.50 | 7.42 | 249.9 | 248.4 | 242.2 | 844.3 | 0.021 |
| 3 | 18.5 | 9.5 | seat row | 0.50 | 7.41 | 250.1 | 248.5 | 242.2 | 843.8 | 0.021 |
| 4 | -18.5 | 9.5 | seat row | 0.50 | 7.52 | 246.6 | 245.7 | 240.1 | 842.5 | 0.021 |
| 5 | -8.5 | -18.5 | seat row | 0.50 | 7.21 | 243.5 | 241.5 | 231.8 | 784.2 | 0.018 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 360; agent-steps of seated agents on another row's clearway: 2364.

## Deposit check

Person-seconds deposited: 707038.2, of them in excluded cells: 2741.457.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 33804 overlapping pair-steps: p99 0.0034, max 0.0099 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0034 max 0.0099; venue-geometry 1: p99 0.0001 max 0.0001 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00751 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 4 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 5.86 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 92 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
