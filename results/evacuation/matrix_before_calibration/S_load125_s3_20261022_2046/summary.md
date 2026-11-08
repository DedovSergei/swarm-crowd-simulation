# Experiment `S_load125_s3`

**Task 5.10 stage 4 (AMD 26.10.1): Task 5.8's model (the level spacing on the gangway inclines, --stair-flow off): venue S, 125% load (seed 3)**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 4660 agents (load 125.0%, requested 125%): every one of the 3728 seats and 932 standing (spawnOvercrowdedCrowd, seed 3; below), buffer N = 8192, 1232 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 154202 evaluations, 3730 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.25)** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T20:46:19, 20.1 s wall.

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
| t50 | 572 | 100.0 |
| t90 | 1009 | 176.5 |
| t100 | 1232 | 215.5 |

t_p: the step by which ceil(p x 4660) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 441 | 41 | 13.5 | 207.3 | 24.1 | 38.3 | 13.3-23.3 |
| -x | 5.66 | 433 | 37 | 13.8 | 205.5 | 23.9 | 39.3 | 13.1-23.1 |
| +y | 5.66 | 443 | 41 | 13.5 | 208.0 | 24.1 | 39.3 | 13.5-23.4 |
| -y | 5.66 | 446 | 36 | 13.6 | 208.0 | 24.3 | 36.2 | 12.9-22.9 |
| door +x+y y | 1.20 | 370 | 567 | 0.9 | 213.7 | 86.8 | 120.4 | 105.6-115.6 |
| door +x+y x | 1.20 | 361 | 569 | 0.9 | 210.6 | 86.0 | 135.4 | 106.2-116.1 |
| door -x+y y | 1.20 | 363 | 561 | 1.4 | 209.0 | 87.3 | 125.4 | 114.9-124.9 |
| door -x+y x | 1.20 | 362 | 560 | 1.4 | 207.4 | 87.8 | 140.4 | 103.5-113.5 |
| door -x-y y | 1.20 | 362 | 560 | 1.4 | 209.2 | 87.0 | 135.4 | 99.9-109.8 |
| door -x-y x | 1.20 | 360 | 566 | 1.6 | 215.5 | 84.1 | 130.4 | 99.7-109.7 |
| door +x-y y | 1.20 | 356 | 553 | 0.9 | 207.4 | 86.1 | 135.4 | 97.9-107.9 |
| door +x-y x | 1.20 | 363 | 569 | 1.0 | 208.1 | 87.6 | 125.4 | 100.2-110.2 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 441 | 9.5% | 26.0% |
| -x | avenue | 5.66 | 433 | 9.3% | 25.5% |
| +y | avenue | 5.66 | 443 | 9.5% | 26.1% |
| -y | avenue | 5.66 | 446 | 9.6% | 26.2% |
| door +x+y y | door | 1.20 | 370 | 7.9% | 102.7% |
| door +x+y x | door | 1.20 | 361 | 7.7% | 100.2% |
| door -x+y y | door | 1.20 | 363 | 7.8% | 100.8% |
| door -x+y x | door | 1.20 | 362 | 7.8% | 100.5% |
| door -x-y y | door | 1.20 | 362 | 7.8% | 100.5% |
| door -x-y x | door | 1.20 | 360 | 7.7% | 99.9% |
| door +x-y y | door | 1.20 | 356 | 7.6% | 98.8% |
| door +x-y x | door | 1.20 | 363 | 7.8% | 100.8% |
| **doors (8)** | door | 9.60 | 2897 | 62.2% | |
| **avenues (4)** | avenue | 22.64 | 1763 | 37.8% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 215.5 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 48.1%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 463 | 9.9% | 463 | 9.9% |
| straight +x+y (x wing) 0 | straight | yes | 462 | 9.9% | 462 | 9.9% |
| corner +x+y | corner | **no** | 16 | 0.3% | 16 | 0.3% |
| straight -x+y (y wing) 0 | straight | yes | 462 | 9.9% | 462 | 9.9% |
| straight -x+y (x wing) 0 | straight | yes | 464 | 10.0% | 464 | 10.0% |
| corner -x+y | corner | **no** | 15 | 0.3% | 15 | 0.3% |
| straight -x-y (y wing) 0 | straight | yes | 463 | 9.9% | 462 | 9.9% |
| straight -x-y (x wing) 0 | straight | yes | 464 | 10.0% | 464 | 10.0% |
| corner -x-y | corner | **no** | 15 | 0.3% | 15 | 0.3% |
| straight +x-y (y wing) 0 | straight | yes | 467 | 10.0% | 467 | 10.0% |
| straight +x-y (x wing) 0 | straight | yes | 461 | 9.9% | 461 | 9.9% |
| corner +x-y | corner | **no** | 14 | 0.3% | 14 | 0.3% |
| **straight (8)** | | | 3706 | | 3705 | 79.5% |
| **corner (4)** | | | 60 | | 60 | 1.3% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 895, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 441 | 13.5 | 207.3 | 0.29 | 0.46 | 0.0% |
| -x | 433 | 13.8 | 205.5 | 0.29 | 0.47 | 0.0% |
| +y | 443 | 13.5 | 208.0 | 0.29 | 0.47 | 0.0% |
| -y | 446 | 13.6 | 208.0 | 0.29 | 0.43 | 0.0% |
| door +x+y y | 370 | 0.9 | 213.7 | 1.04 | 1.44 | 86.4% |
| door +x+y x | 361 | 0.9 | 210.6 | 1.03 | 1.62 | 81.8% |
| door -x+y y | 363 | 1.4 | 209.0 | 1.04 | 1.50 | 85.7% |
| door -x+y x | 362 | 1.4 | 207.4 | 1.05 | 1.68 | 85.7% |
| door -x-y y | 362 | 1.4 | 209.2 | 1.04 | 1.62 | 85.7% |
| door -x-y x | 360 | 1.6 | 215.5 | 1.01 | 1.56 | 81.8% |
| door +x-y y | 356 | 0.9 | 207.4 | 1.03 | 1.62 | 85.7% |
| door +x-y x | 363 | 1.0 | 208.1 | 1.05 | 1.50 | 85.7% |

Mean flow / w J averaged over the doors 1.04, over the avenues 0.29.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 463 | 284 / 179 / 44 | 0.7 | 210.8 | 2.41 | 3.51 | 77% | 77% | 0% | 4.35 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 462 | 278 / 184 / 47 | 0.3 | 207.6 | 2.45 | 3.61 | 81% | 81% | 0% | 4.24 |
| corner +x+y | 1.20 | 31.2 | 16 | 1 / 15 / 0 | 0.2 | 37.6 | 0.43 | 0.70 | 0% | 0% | 0% | nan |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 462 | 279 / 183 / 59 | 0.7 | 206.0 | 2.54 | 3.91 | 76% | 76% | 0% | 4.34 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 464 | 284 / 180 / 41 | 0.7 | 204.5 | 2.48 | 3.61 | 81% | 81% | 0% | 4.29 |
| corner -x+y | 1.20 | 31.2 | 15 | 0 / 15 / 0 | 4.5 | 35.9 | 0.48 | 0.70 | 0% | 0% | 0% | nan |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 463 | 281 / 182 / 33 | 0.3 | 206.2 | 2.41 | 3.41 | 81% | 81% | 0% | 4.30 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 463 | 276 / 189 / 56 | 0.5 | 212.5 | 2.46 | 3.81 | 77% | 77% | 0% | 4.23 |
| corner -x-y | 1.20 | 31.2 | 15 | 0 / 15 / 0 | 4.5 | 35.7 | 0.48 | 0.70 | 0% | 0% | 0% | nan |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 467 | 286 / 181 / 52 | 0.3 | 204.5 | 2.54 | 3.81 | 76% | 76% | 0% | 4.30 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 461 | 275 / 186 / 54 | 0.3 | 205.2 | 2.51 | 3.41 | 76% | 76% | 0% | 4.33 |
| corner +x-y | 1.20 | 31.2 | 14 | 0 / 14 / 0 | 4.5 | 35.7 | 0.45 | 0.60 | 25% | 0% | 25% | 0.12 |

The last agent out (agent 2049, t100 215.5 s): last gangway straight -x-y (x wing) 0, exit door -x-y (x wall). The gangway that cleared last: straight -x-y (x wing) 0 at 212.5 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.34 | 213.0 / 206.2 / 173.3 | 191.7 / 183.8 / 116.1 | 42821.3 | 223717 | 0.328 |
| gangway | 392 | 351.5 | 6.34 | 208.0 / 185.6 / 149.5 | 191.7 / 183.8 / 116.1 | 40301.2 | 142911 | 0.124 |
| walkway | 276 | 257.4 | 4.21 | 151.6 / 58.2 / 0.0 | 110.4 / 33.9 / 0.0 | 0.0 | 13270 | 0.846 |
| avenue | 408 | 384.3 | 2.20 | 187.0 / 0.9 / 0.0 | 151.5 / 0.2 / 0.0 | 0.0 | 22975 | 1.311 |
| exit | 40 | 9.7 | 0.00 | 212.7 / 206.0 / 162.1 | 177.4 / 150.1 / 52.6 | 653.3 | 2607 | 0.958 |
| concourse | 612 | 609.0 | 5.68 | 189.8 / 121.6 / 52.3 | 160.9 / 112.8 / 30.3 | 1866.8 | 41952 | 0.281 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.49 | 172.3 / 170.7 / 160.7 | 172.3 / 170.5 / 158.1 | 76108.4 | 239787 | 0.069 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -10.5 | -18.5 | gangway | 0.94 | 5.90 | 175.3 | 168.3 | 116.1 | 586.9 | 0.061 |
| 2 | 10.5 | 18.5 | gangway | 0.94 | 5.78 | 171.6 | 167.2 | 112.8 | 567.3 | 0.062 |
| 3 | -18.5 | 10.5 | gangway | 0.94 | 5.85 | 171.1 | 164.6 | 108.1 | 542.7 | 0.062 |
| 4 | 10.5 | -18.5 | gangway | 0.94 | 5.87 | 173.5 | 166.7 | 100.7 | 504.6 | 0.061 |
| 5 | -18.5 | -10.5 | gangway | 0.94 | 5.79 | 171.6 | 163.9 | 101.1 | 501.3 | 0.070 |
| 6 | 10.5 | -19.5 | gangway | 0.96 | 5.84 | 177.2 | 163.5 | 96.9 | 494.1 | 0.052 |
| 7 | 11.5 | -19.5 | gangway | 0.92 | 5.99 | 157.9 | 153.0 | 99.2 | 493.2 | 0.044 |
| 8 | 11.5 | 18.5 | gangway | 0.86 | 6.03 | 163.2 | 160.7 | 103.4 | 488.1 | 0.063 |
| 9 | -19.5 | -11.5 | gangway | 0.92 | 5.91 | 157.6 | 151.1 | 97.2 | 483.7 | 0.049 |
| 10 | -10.5 | 18.5 | gangway | 0.94 | 5.80 | 172.6 | 164.4 | 95.7 | 479.6 | 0.067 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 9.5 | -18.5 | seat row | 0.50 | 7.44 | 167.9 | 166.9 | 158.1 | 542.2 | 0.033 |
| 2 | -18.5 | 9.5 | seat row | 0.50 | 7.42 | 166.5 | 165.5 | 155.7 | 536.2 | 0.034 |
| 3 | -9.5 | -18.5 | seat row | 0.50 | 7.48 | 168.6 | 166.5 | 153.4 | 532.8 | 0.034 |
| 4 | 9.5 | 18.5 | seat row | 0.50 | 7.44 | 167.7 | 164.4 | 153.9 | 530.7 | 0.034 |
| 5 | 18.5 | -9.5 | seat row | 0.50 | 7.27 | 167.4 | 165.1 | 155.1 | 522.9 | 0.034 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 383; agent-steps of seated agents on another row's clearway: 3649.

## Deposit check

Person-seconds deposited: 465020.1, of them in excluded cells: 1516.015.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 29656 overlapping pair-steps: p99 0.0063, max 0.0115 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0063 max 0.0115; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 3 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 5.68 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 152 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
