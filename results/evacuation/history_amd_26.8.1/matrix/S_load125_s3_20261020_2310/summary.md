# Experiment `S_load125_s3`

**Task 5.9 stage 4: venue S, 125% load (seed 3): every seat + standing on the walkway and concourse**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 4660 agents (load 125.0%, requested 125%): every one of the 3728 seats and 932 standing (spawnOvercrowdedCrowd, seed 3; below), buffer N = 8192, 1443 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 172050 evaluations, 3784 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.25)** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-20T23:10:01, 12.7 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Spawn (overcrowding)

| | |
|---|---|
| seated | 3728 (every seat) |
| standing | **932** (requested round((1.25 - 1) x 3728) = 932; at most 2143 = floor(2.5 p/m^2 x 857.4 m^2)) |
| standing floor | walkway + rear concourse, 857.4 m^2 |
| standing on the walkway / concourse / gangways | 278 / 654 / 0 |
| **load** | **125.00%** of the seats (requested 125%) |
| standing crowd's mean density | 1.087 p/m^2 |
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 2.88, all circulation cells 2.88 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 3, 6741 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 583 | 102.0 |
| t90 | 1202 | 210.2 |
| t100 | 1443 | 252.4 |

t_p: the step by which ceil(p x 4660) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 434 | 41 | 13.5 | 246.3 | 19.7 | 38.3 | 13.3-23.3 |
| -x | 5.66 | 428 | 37 | 13.8 | 241.9 | 19.9 | 39.3 | 13.1-23.1 |
| +y | 5.66 | 443 | 41 | 13.5 | 247.8 | 20.0 | 39.3 | 13.5-23.4 |
| -y | 5.66 | 444 | 36 | 13.6 | 246.4 | 20.2 | 36.2 | 12.9-22.9 |
| door +x+y y | 1.20 | 367 | 567 | 0.9 | 252.4 | 72.9 | 120.4 | 89.2-99.2 |
| door +x+y x | 1.20 | 367 | 569 | 0.9 | 240.1 | 76.6 | 125.4 | 89.6-99.5 |
| door -x+y y | 1.20 | 364 | 561 | 1.4 | 244.5 | 74.8 | 125.4 | 79.8-89.7 |
| door -x+y x | 1.20 | 363 | 560 | 1.4 | 246.3 | 74.1 | 115.3 | 84.5-94.4 |
| door -x-y y | 1.20 | 363 | 560 | 1.4 | 249.2 | 73.2 | 120.4 | 88.2-98.1 |
| door -x-y x | 1.20 | 365 | 566 | 1.6 | 242.9 | 75.6 | 130.4 | 90.1-100.0 |
| door +x-y y | 1.20 | 358 | 553 | 0.9 | 244.2 | 73.5 | 110.3 | 77.7-87.6 |
| door +x-y x | 1.20 | 364 | 569 | 1.0 | 247.8 | 73.7 | 120.4 | 91.3-101.3 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 434 | 9.3% | 21.8% |
| -x | avenue | 5.66 | 428 | 9.2% | 21.5% |
| +y | avenue | 5.66 | 443 | 9.5% | 22.3% |
| -y | avenue | 5.66 | 444 | 9.5% | 22.3% |
| door +x+y y | door | 1.20 | 367 | 7.9% | 87.0% |
| door +x+y x | door | 1.20 | 367 | 7.9% | 87.0% |
| door -x+y y | door | 1.20 | 364 | 7.8% | 86.3% |
| door -x+y x | door | 1.20 | 363 | 7.8% | 86.0% |
| door -x-y y | door | 1.20 | 363 | 7.8% | 86.0% |
| door -x-y x | door | 1.20 | 365 | 7.8% | 86.5% |
| door +x-y y | door | 1.20 | 358 | 7.7% | 84.8% |
| door +x-y x | door | 1.20 | 364 | 7.8% | 86.3% |
| **doors (8)** | door | 9.60 | 2911 | 62.5% | |
| **avenues (4)** | avenue | 22.64 | 1749 | 37.5% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 252.4 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 41.1%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 462 | 9.9% | 462 | 9.9% |
| straight +x+y (x wing) 0 | straight | yes | 461 | 9.9% | 461 | 9.9% |
| corner +x+y | corner | **no** | 16 | 0.3% | 16 | 0.3% |
| straight -x+y (y wing) 0 | straight | yes | 462 | 9.9% | 462 | 9.9% |
| straight -x+y (x wing) 0 | straight | yes | 467 | 10.0% | 467 | 10.0% |
| corner -x+y | corner | **no** | 12 | 0.3% | 12 | 0.3% |
| straight -x-y (y wing) 0 | straight | yes | 463 | 9.9% | 463 | 9.9% |
| straight -x-y (x wing) 0 | straight | yes | 461 | 9.9% | 461 | 9.9% |
| corner -x-y | corner | **no** | 15 | 0.3% | 15 | 0.3% |
| straight +x-y (y wing) 0 | straight | yes | 467 | 10.0% | 467 | 10.0% |
| straight +x-y (x wing) 0 | straight | yes | 460 | 9.9% | 460 | 9.9% |
| corner +x-y | corner | **no** | 14 | 0.3% | 14 | 0.3% |
| **straight (8)** | | | 3703 | | 3703 | 79.5% |
| **corner (4)** | | | 57 | | 57 | 1.2% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 900, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 434 | 13.5 | 246.3 | 0.24 | 0.46 | 0.0% |
| -x | 428 | 13.8 | 241.9 | 0.24 | 0.47 | 0.0% |
| +y | 443 | 13.5 | 247.8 | 0.24 | 0.47 | 0.0% |
| -y | 444 | 13.6 | 246.4 | 0.24 | 0.43 | 0.0% |
| door +x+y y | 367 | 0.9 | 252.4 | 0.87 | 1.44 | 57.7% |
| door +x+y x | 367 | 0.9 | 240.1 | 0.92 | 1.50 | 64.0% |
| door -x+y y | 364 | 1.4 | 244.5 | 0.89 | 1.50 | 60.0% |
| door -x+y x | 363 | 1.4 | 246.3 | 0.89 | 1.38 | 64.0% |
| door -x-y y | 363 | 1.4 | 249.2 | 0.88 | 1.44 | 52.0% |
| door -x-y x | 365 | 1.6 | 242.9 | 0.90 | 1.56 | 64.0% |
| door +x-y y | 358 | 0.9 | 244.2 | 0.88 | 1.32 | 56.0% |
| door +x-y x | 364 | 1.0 | 247.8 | 0.88 | 1.44 | 52.0% |

Mean flow / w J averaged over the doors 0.89, over the avenues 0.24.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 462 | 281 / 181 / 43 | 0.7 | 249.4 | 2.03 | 2.71 | 85% | 81% | 4% | 3.78 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 461 | 284 / 177 / 53 | 0.3 | 237.2 | 2.17 | 2.91 | 88% | 88% | 0% | 3.78 |
| corner +x+y | 1.20 | 31.2 | 16 | 1 / 15 / 0 | 0.2 | 36.9 | 0.43 | 0.70 | 0% | 0% | 0% | nan |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 462 | 280 / 182 / 51 | 0.7 | 241.5 | 2.13 | 3.21 | 84% | 80% | 4% | 3.78 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 467 | 285 / 182 / 44 | 0.7 | 243.3 | 2.10 | 2.81 | 80% | 80% | 0% | 3.86 |
| corner -x+y | 1.20 | 31.2 | 12 | 0 / 12 / 0 | 4.5 | 34.8 | 0.39 | 0.50 | 0% | 0% | 0% | nan |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 463 | 282 / 181 / 42 | 0.3 | 246.3 | 2.05 | 2.81 | 84% | 84% | 0% | 3.91 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 461 | 281 / 180 / 41 | 0.5 | 240.0 | 2.09 | 3.01 | 80% | 80% | 0% | 3.90 |
| corner -x-y | 1.20 | 31.2 | 15 | 0 / 15 / 0 | 4.5 | 37.6 | 0.45 | 0.70 | 0% | 0% | 0% | nan |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 467 | 288 / 179 / 37 | 0.3 | 241.2 | 2.09 | 2.81 | 84% | 80% | 4% | 3.78 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 460 | 276 / 184 / 41 | 0.3 | 244.9 | 2.05 | 2.81 | 84% | 80% | 4% | 3.82 |
| corner +x-y | 1.20 | 31.2 | 14 | 0 / 14 / 0 | 4.5 | 36.9 | 0.43 | 0.70 | 25% | 0% | 25% | 0.12 |

The last agent out (agent 167, t100 252.4 s): last gangway straight +x+y (y wing) 0, exit door +x+y (y wall). The gangway that cleared last: straight +x+y (y wing) 0 at 249.4 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.36 | 250.5 / 241.4 / 206.2 | 228.3 / 220.2 / 139.1 | 53069.6 | 231365 | 0.313 |
| gangway | 392 | 351.5 | 6.36 | 245.9 / 225.5 / 178.1 | 228.3 / 220.2 / 139.1 | 51545.1 | 157201 | 0.107 |
| walkway | 276 | 257.4 | 4.23 | 83.3 / 49.0 / 0.0 | 62.3 / 31.1 / 0.0 | 0.0 | 11996 | 0.947 |
| avenue | 408 | 384.3 | 2.20 | 109.5 / 0.9 / 0.0 | 84.7 / 0.2 / 0.0 | 0.0 | 22760 | 1.315 |
| exit | 40 | 9.7 | 0.00 | 249.1 / 239.6 / 163.4 | 169.5 / 142.5 / 48.6 | 599.3 | 2530 | 1.003 |
| concourse | 612 | 609.0 | 5.41 | 208.3 / 96.2 / 46.0 | 110.2 / 93.9 / 19.1 | 925.1 | 36877 | 0.319 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.57 | 216.9 / 215.3 / 189.1 | 216.9 / 215.3 / 186.1 | 91651.2 | 285295 | 0.057 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 11.5 | -19.5 | gangway | 0.92 | 5.85 | 192.4 | 186.8 | 139.1 | 674.1 | 0.029 |
| 2 | -18.5 | -10.5 | gangway | 0.94 | 6.07 | 208.5 | 203.2 | 128.4 | 663.3 | 0.044 |
| 3 | -10.5 | -19.5 | gangway | 0.96 | 5.71 | 217.8 | 206.0 | 128.9 | 653.5 | 0.033 |
| 4 | -10.5 | -18.5 | gangway | 0.94 | 5.65 | 210.2 | 203.1 | 129.8 | 649.9 | 0.045 |
| 5 | -11.5 | -19.5 | gangway | 0.92 | 5.89 | 198.0 | 192.7 | 129.8 | 649.2 | 0.031 |
| 6 | -19.5 | -11.5 | gangway | 0.92 | 5.67 | 198.0 | 193.3 | 130.5 | 640.2 | 0.029 |
| 7 | 18.5 | -10.5 | gangway | 0.94 | 5.90 | 207.6 | 203.1 | 122.1 | 619.6 | 0.046 |
| 8 | 10.5 | 18.5 | gangway | 0.94 | 5.88 | 211.8 | 206.2 | 118.9 | 612.6 | 0.047 |
| 9 | 11.5 | 19.5 | gangway | 0.92 | 5.54 | 200.4 | 197.1 | 124.2 | 610.7 | 0.028 |
| 10 | -11.5 | 19.5 | gangway | 0.92 | 5.87 | 194.3 | 189.1 | 123.1 | 610.5 | 0.030 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 9.5 | -18.5 | seat row | 0.50 | 7.54 | 204.1 | 200.1 | 186.1 | 649.6 | 0.027 |
| 2 | 18.5 | 9.5 | seat row | 0.50 | 7.57 | 203.1 | 196.6 | 183.1 | 648.3 | 0.027 |
| 3 | -9.5 | -18.5 | seat row | 0.50 | 7.54 | 201.3 | 190.1 | 180.2 | 627.6 | 0.028 |
| 4 | -9.5 | 18.5 | seat row | 0.50 | 7.52 | 201.0 | 192.9 | 178.6 | 626.3 | 0.028 |
| 5 | 18.5 | -9.5 | seat row | 0.50 | 7.44 | 198.7 | 191.9 | 180.0 | 623.3 | 0.029 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 352; agent-steps of seated agents on another row's clearway: 2260.

## Deposit check

Person-seconds deposited: 518109.3, of them in excluded cells: 1448.862.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 37587 overlapping pair-steps: p99 0.0034, max 0.0075 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0034 max 0.0075; venue-geometry 1: p99 0.0003 max 0.0003 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 6 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 5.41 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 93 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
