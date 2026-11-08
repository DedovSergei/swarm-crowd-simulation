# Experiment `S_load125_s1`

**Task 5.10 stage 4 (AMD 26.10.1): Task 5.8's model (the level spacing on the gangway inclines, --stair-flow off): venue S, 125% load (seed 1)**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 4660 agents (load 125.0%, requested 125%): every one of the 3728 seats and 932 standing (spawnOvercrowdedCrowd, seed 1; below), buffer N = 8192, 1241 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 155584 evaluations, 3741 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.25)** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T20:45:29, 17.8 s wall.

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
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 3.29, all circulation cells 3.29 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 1, 6536 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 576 | 100.7 |
| t90 | 1018 | 178.1 |
| t100 | 1241 | 217.1 |

t_p: the step by which ceil(p x 4660) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 439 | 40 | 13.6 | 205.3 | 24.3 | 41.5 | 13.1-23.1 |
| -x | 5.66 | 445 | 36 | 13.6 | 208.5 | 24.2 | 40.4 | 13.3-23.3 |
| +y | 5.66 | 445 | 39 | 13.6 | 210.2 | 24.0 | 35.1 | 13.1-23.1 |
| -y | 5.66 | 449 | 38 | 13.6 | 209.9 | 24.2 | 40.4 | 13.5-23.4 |
| door +x+y y | 1.20 | 362 | 559 | 1.2 | 210.6 | 86.4 | 140.4 | 98.8-108.8 |
| door +x+y x | 1.20 | 350 | 550 | 2.1 | 202.5 | 87.2 | 135.4 | 98.8-108.8 |
| door -x+y y | 1.20 | 361 | 567 | 1.0 | 209.9 | 86.4 | 135.4 | 105.5-115.4 |
| door -x+y x | 1.20 | 358 | 568 | 1.2 | 214.1 | 84.0 | 125.4 | 130.3-140.3 |
| door -x-y y | 1.20 | 361 | 565 | 1.7 | 217.1 | 83.8 | 125.4 | 121.7-131.7 |
| door -x-y x | 1.20 | 363 | 568 | 1.2 | 207.3 | 88.0 | 125.4 | 115.1-125.1 |
| door +x-y y | 1.20 | 361 | 558 | 1.0 | 207.8 | 87.2 | 130.4 | 104.4-114.4 |
| door +x-y x | 1.20 | 366 | 572 | 1.0 | 212.0 | 86.7 | 120.4 | 87.8-97.8 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 439 | 9.4% | 25.6% |
| -x | avenue | 5.66 | 445 | 9.5% | 26.0% |
| +y | avenue | 5.66 | 445 | 9.5% | 26.0% |
| -y | avenue | 5.66 | 449 | 9.6% | 26.2% |
| door +x+y y | door | 1.20 | 362 | 7.8% | 99.7% |
| door +x+y x | door | 1.20 | 350 | 7.5% | 96.4% |
| door -x+y y | door | 1.20 | 361 | 7.7% | 99.5% |
| door -x+y x | door | 1.20 | 358 | 7.7% | 98.6% |
| door -x-y y | door | 1.20 | 361 | 7.7% | 99.5% |
| door -x-y x | door | 1.20 | 363 | 7.8% | 100.0% |
| door +x-y y | door | 1.20 | 361 | 7.7% | 99.5% |
| door +x-y x | door | 1.20 | 366 | 7.9% | 100.8% |
| **doors (8)** | door | 9.60 | 2882 | 61.8% | |
| **avenues (4)** | avenue | 22.64 | 1778 | 38.2% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 217.1 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 47.8%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 465 | 10.0% | 465 | 10.0% |
| straight +x+y (x wing) 0 | straight | yes | 468 | 10.0% | 468 | 10.0% |
| corner +x+y | corner | **no** | 8 | 0.2% | 8 | 0.2% |
| straight -x+y (y wing) 0 | straight | yes | 463 | 9.9% | 463 | 9.9% |
| straight -x+y (x wing) 0 | straight | yes | 462 | 9.9% | 462 | 9.9% |
| corner -x+y | corner | **no** | 16 | 0.3% | 16 | 0.3% |
| straight -x-y (y wing) 0 | straight | yes | 463 | 9.9% | 463 | 9.9% |
| straight -x-y (x wing) 0 | straight | yes | 461 | 9.9% | 461 | 9.9% |
| corner -x-y | corner | **no** | 16 | 0.3% | 16 | 0.3% |
| straight +x-y (y wing) 0 | straight | yes | 466 | 10.0% | 466 | 10.0% |
| straight +x-y (x wing) 0 | straight | yes | 463 | 9.9% | 463 | 9.9% |
| corner +x-y | corner | **no** | 12 | 0.3% | 12 | 0.3% |
| **straight (8)** | | | 3711 | | 3711 | 79.6% |
| **corner (4)** | | | 52 | | 52 | 1.1% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 897, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 439 | 13.6 | 205.3 | 0.29 | 0.50 | 0.0% |
| -x | 445 | 13.6 | 208.5 | 0.29 | 0.48 | 0.0% |
| +y | 445 | 13.6 | 210.2 | 0.29 | 0.42 | 0.0% |
| -y | 449 | 13.6 | 209.9 | 0.29 | 0.48 | 0.0% |
| door +x+y y | 362 | 1.2 | 210.6 | 1.03 | 1.68 | 86.4% |
| door +x+y x | 350 | 2.1 | 202.5 | 1.04 | 1.62 | 90.5% |
| door -x+y y | 361 | 1.0 | 209.9 | 1.03 | 1.62 | 86.4% |
| door -x+y x | 358 | 1.2 | 214.1 | 1.01 | 1.50 | 86.4% |
| door -x-y y | 361 | 1.7 | 217.1 | 1.00 | 1.50 | 86.4% |
| door -x-y x | 363 | 1.2 | 207.3 | 1.05 | 1.50 | 90.5% |
| door +x-y y | 361 | 1.0 | 207.8 | 1.04 | 1.56 | 90.5% |
| door +x-y x | 366 | 1.0 | 212.0 | 1.04 | 1.44 | 86.4% |

Mean flow / w J averaged over the doors 1.03, over the avenues 0.29.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 465 | 286 / 179 / 45 | 0.3 | 207.6 | 2.46 | 3.41 | 81% | 81% | 0% | 4.31 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 468 | 279 / 189 / 56 | 0.2 | 199.6 | 2.63 | 3.91 | 76% | 76% | 0% | 4.33 |
| corner +x+y | 1.20 | 31.2 | 8 | 0 / 8 / 0 | 4.5 | 32.5 | 0.28 | 0.40 | 0% | 0% | 0% | nan |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 463 | 272 / 191 / 69 | 0.3 | 206.9 | 2.57 | 3.91 | 81% | 81% | 0% | 4.29 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 462 | 276 / 186 / 51 | 0.5 | 211.1 | 2.43 | 3.41 | 77% | 77% | 0% | 4.35 |
| corner -x+y | 1.20 | 31.2 | 16 | 0 / 16 / 0 | 4.5 | 35.0 | 0.52 | 0.90 | 0% | 0% | 0% | nan |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 463 | 277 / 186 / 52 | 0.2 | 214.1 | 2.41 | 3.81 | 77% | 77% | 0% | 4.37 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 461 | 275 / 186 / 46 | 0.3 | 204.3 | 2.48 | 3.71 | 81% | 81% | 0% | 4.27 |
| corner -x-y | 1.20 | 31.2 | 16 | 0 / 16 / 0 | 4.5 | 35.0 | 0.52 | 0.90 | 0% | 0% | 0% | nan |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 466 | 283 / 183 / 55 | 0.7 | 204.8 | 2.55 | 3.91 | 81% | 81% | 0% | 4.26 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 463 | 280 / 183 / 56 | 0.7 | 209.0 | 2.49 | 3.61 | 81% | 81% | 0% | 4.29 |
| corner +x-y | 1.20 | 31.2 | 12 | 0 / 12 / 0 | 4.5 | 35.5 | 0.39 | 0.60 | 0% | 0% | 0% | nan |

The last agent out (agent 2048, t100 217.1 s): last gangway straight -x-y (y wing) 0, exit door -x-y (y wall). The gangway that cleared last: straight -x-y (y wing) 0 at 214.1 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.39 | 213.9 / 208.0 / 176.5 | 192.2 / 185.6 / 121.0 | 44871.5 | 225952 | 0.326 |
| gangway | 392 | 351.5 | 6.39 | 210.2 / 187.5 / 147.1 | 192.2 / 185.6 / 121.0 | 41982.9 | 144486 | 0.123 |
| walkway | 276 | 257.4 | 4.43 | 146.2 / 53.9 / 0.0 | 78.7 / 28.3 / 0.0 | 0.0 | 12661 | 0.890 |
| avenue | 408 | 384.3 | 2.46 | 186.8 / 6.8 / 0.0 | 136.8 / 0.5 / 0.0 | 0.0 | 23166 | 1.312 |
| exit | 40 | 9.7 | 0.00 | 213.6 / 208.0 / 166.3 | 179.1 / 155.0 / 53.5 | 666.7 | 2630 | 0.951 |
| concourse | 612 | 609.0 | 5.64 | 195.9 / 127.7 / 56.1 | 158.8 / 120.5 / 28.2 | 2221.9 | 43010 | 0.273 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.52 | 174.9 / 170.2 / 158.5 | 174.9 / 170.0 / 155.1 | 77329.2 | 241714 | 0.069 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -10.5 | -18.5 | gangway | 0.94 | 5.61 | 174.4 | 169.8 | 121.0 | 601.0 | 0.063 |
| 2 | 11.5 | -19.5 | gangway | 0.92 | 5.96 | 160.9 | 156.5 | 120.0 | 600.0 | 0.044 |
| 3 | -18.5 | 11.5 | gangway | 0.86 | 6.33 | 168.8 | 157.1 | 112.3 | 541.4 | 0.067 |
| 4 | -10.5 | 18.5 | gangway | 0.94 | 5.99 | 175.3 | 169.3 | 105.8 | 532.7 | 0.066 |
| 5 | -19.5 | -11.5 | gangway | 0.92 | 5.89 | 158.8 | 156.2 | 106.7 | 527.7 | 0.050 |
| 6 | -18.5 | 10.5 | gangway | 0.94 | 6.04 | 174.7 | 169.8 | 103.5 | 527.3 | 0.066 |
| 7 | 10.5 | -18.5 | gangway | 0.94 | 5.86 | 171.1 | 166.0 | 103.7 | 521.1 | 0.063 |
| 8 | 10.5 | 18.5 | gangway | 0.94 | 5.78 | 173.7 | 166.0 | 103.7 | 516.6 | 0.061 |
| 9 | 18.5 | -10.5 | gangway | 0.94 | 5.95 | 174.4 | 165.1 | 102.7 | 515.8 | 0.065 |
| 10 | 10.5 | -19.5 | gangway | 0.96 | 5.78 | 175.4 | 160.4 | 99.5 | 513.2 | 0.050 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -9.5 | 18.5 | seat row | 0.50 | 7.35 | 167.9 | 165.5 | 155.0 | 531.1 | 0.034 |
| 2 | -9.5 | -18.5 | seat row | 0.50 | 7.36 | 171.1 | 164.4 | 151.8 | 519.1 | 0.034 |
| 3 | -18.5 | 9.5 | seat row | 0.50 | 7.46 | 168.3 | 163.2 | 150.4 | 518.1 | 0.035 |
| 4 | -12.5 | 22.5 | seat row | 0.50 | 7.15 | 165.8 | 164.4 | 155.1 | 517.8 | 0.043 |
| 5 | -18.5 | -9.5 | seat row | 0.50 | 7.37 | 165.6 | 163.7 | 149.9 | 517.3 | 0.034 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 430; agent-steps of seated agents on another row's clearway: 4115.

## Deposit check

Person-seconds deposited: 469213.7, of them in excluded cells: 1546.840.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 27539 overlapping pair-steps: p99 0.0040, max 0.0093 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0040 max 0.0093; venue-geometry 2: p99 0.0003 max 0.0003 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 2 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 5.64 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 176 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
