# Experiment `S_load125_s3`

**Task 5.10 stage 4 (AMD 26.10.1): venue S, 125% load (seed 3): every seat + standing on the walkway and concourse**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 4660 agents (load 125.0%, requested 125%): every one of the 3728 seats and 932 standing (spawnOvercrowdedCrowd, seed 3; below), buffer N = 8192, 1437 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 172721 evaluations, 3770 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.25)** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T19:37:10, 13.0 s wall.

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
| t50 | 589 | 103.0 |
| t90 | 1206 | 210.9 |
| t100 | 1437 | 251.3 |

t_p: the step by which ceil(p x 4660) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 437 | 41 | 13.5 | 244.0 | 20.1 | 38.3 | 13.3-23.3 |
| -x | 5.66 | 432 | 37 | 13.8 | 247.3 | 19.6 | 39.3 | 13.1-23.1 |
| +y | 5.66 | 446 | 41 | 13.5 | 247.0 | 20.2 | 39.3 | 13.5-23.4 |
| -y | 5.66 | 448 | 36 | 13.6 | 246.4 | 20.4 | 36.2 | 12.9-22.9 |
| door +x+y y | 1.20 | 368 | 567 | 0.9 | 245.4 | 75.2 | 120.4 | 94.3-104.2 |
| door +x+y x | 1.20 | 365 | 569 | 0.9 | 244.9 | 74.7 | 125.4 | 88.2-98.1 |
| door -x+y y | 1.20 | 360 | 561 | 1.4 | 251.3 | 72.0 | 110.3 | 63.8-73.8 |
| door -x+y x | 1.20 | 359 | 560 | 1.4 | 247.1 | 73.0 | 115.3 | 92.2-102.1 |
| door -x-y y | 1.20 | 362 | 560 | 1.4 | 251.0 | 72.5 | 120.4 | 87.3-97.2 |
| door -x-y x | 1.20 | 365 | 566 | 1.6 | 249.1 | 73.7 | 120.4 | 79.1-89.0 |
| door +x-y y | 1.20 | 355 | 553 | 0.9 | 238.4 | 74.7 | 125.4 | 81.7-91.7 |
| door +x-y x | 1.20 | 363 | 569 | 1.0 | 238.6 | 76.4 | 115.3 | 94.8-104.8 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 437 | 9.4% | 22.0% |
| -x | avenue | 5.66 | 432 | 9.3% | 21.8% |
| +y | avenue | 5.66 | 446 | 9.6% | 22.5% |
| -y | avenue | 5.66 | 448 | 9.6% | 22.6% |
| door +x+y y | door | 1.20 | 368 | 7.9% | 87.6% |
| door +x+y x | door | 1.20 | 365 | 7.8% | 86.9% |
| door -x+y y | door | 1.20 | 360 | 7.7% | 85.7% |
| door -x+y x | door | 1.20 | 359 | 7.7% | 85.4% |
| door -x-y y | door | 1.20 | 362 | 7.8% | 86.1% |
| door -x-y x | door | 1.20 | 365 | 7.8% | 86.9% |
| door +x-y y | door | 1.20 | 355 | 7.6% | 84.5% |
| door +x-y x | door | 1.20 | 363 | 7.8% | 86.4% |
| **doors (8)** | door | 9.60 | 2897 | 62.2% | |
| **avenues (4)** | avenue | 22.64 | 1763 | 37.8% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 251.3 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 41.3%.

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
| +x | 437 | 13.5 | 244.0 | 0.24 | 0.46 | 0.0% |
| -x | 432 | 13.8 | 247.3 | 0.23 | 0.47 | 0.0% |
| +y | 446 | 13.5 | 247.0 | 0.24 | 0.47 | 0.0% |
| -y | 448 | 13.6 | 246.4 | 0.24 | 0.43 | 0.0% |
| door +x+y y | 368 | 0.9 | 245.4 | 0.90 | 1.44 | 64.0% |
| door +x+y x | 365 | 0.9 | 244.9 | 0.89 | 1.50 | 64.0% |
| door -x+y y | 360 | 1.4 | 251.3 | 0.86 | 1.32 | 53.8% |
| door -x+y x | 359 | 1.4 | 247.1 | 0.87 | 1.38 | 64.0% |
| door -x-y y | 362 | 1.4 | 251.0 | 0.87 | 1.44 | 53.8% |
| door -x-y x | 365 | 1.6 | 249.1 | 0.88 | 1.44 | 56.0% |
| door +x-y y | 355 | 0.9 | 238.4 | 0.89 | 1.50 | 58.3% |
| door +x-y x | 363 | 1.0 | 238.6 | 0.91 | 1.38 | 62.5% |

Mean flow / w J averaged over the doors 0.89, over the avenues 0.24.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 462 | 282 / 180 / 51 | 0.7 | 242.4 | 2.12 | 3.01 | 80% | 80% | 0% | 3.99 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 461 | 282 / 179 / 56 | 0.3 | 241.9 | 2.14 | 3.11 | 84% | 84% | 0% | 3.90 |
| corner +x+y | 1.20 | 31.2 | 16 | 1 / 15 / 0 | 0.2 | 36.9 | 0.43 | 0.70 | 0% | 0% | 0% | nan |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 462 | 276 / 186 / 55 | 0.7 | 248.4 | 2.09 | 2.91 | 84% | 84% | 0% | 3.86 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 467 | 281 / 186 / 49 | 0.7 | 244.2 | 2.12 | 3.01 | 84% | 84% | 0% | 3.94 |
| corner -x+y | 1.20 | 31.2 | 12 | 0 / 12 / 0 | 4.5 | 34.8 | 0.39 | 0.50 | 0% | 0% | 0% | nan |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 463 | 281 / 182 / 53 | 0.3 | 248.0 | 2.08 | 3.11 | 84% | 84% | 0% | 3.87 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 461 | 281 / 180 / 42 | 0.5 | 246.1 | 2.05 | 2.71 | 84% | 84% | 0% | 3.81 |
| corner -x-y | 1.20 | 31.2 | 15 | 0 / 15 / 0 | 4.5 | 37.6 | 0.45 | 0.70 | 0% | 0% | 0% | nan |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 467 | 285 / 182 / 44 | 0.3 | 235.4 | 2.17 | 3.11 | 88% | 88% | 0% | 3.86 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 460 | 275 / 185 / 53 | 0.3 | 235.6 | 2.18 | 3.11 | 88% | 88% | 0% | 3.89 |
| corner +x-y | 1.20 | 31.2 | 14 | 0 / 14 / 0 | 4.5 | 36.9 | 0.43 | 0.70 | 25% | 0% | 25% | 0.12 |

The last agent out (agent 1101, t100 251.3 s): last gangway straight -x+y (y wing) 0, exit door -x+y (y wall). The gangway that cleared last: straight -x+y (y wing) 0 at 248.4 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.48 | 250.3 / 242.1 / 203.2 | 225.6 / 219.7 / 133.8 | 53767.2 | 233396 | 0.312 |
| gangway | 392 | 351.5 | 6.48 | 244.5 / 222.0 / 173.7 | 225.6 / 219.7 / 133.8 | 52369.3 | 158925 | 0.106 |
| walkway | 276 | 257.4 | 4.23 | 90.4 / 48.4 / 0.0 | 62.6 / 32.7 / 0.0 | 0.0 | 12051 | 0.949 |
| avenue | 408 | 384.3 | 2.20 | 113.7 / 0.9 / 0.0 | 86.4 / 0.2 / 0.0 | 0.0 | 22942 | 1.315 |
| exit | 40 | 9.7 | 0.00 | 249.8 / 241.4 / 160.4 | 173.5 / 143.8 / 47.7 | 595.8 | 2535 | 1.001 |
| concourse | 612 | 609.0 | 5.56 | 205.0 / 99.5 / 36.9 | 111.2 / 94.4 / 17.8 | 802.1 | 36943 | 0.317 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.58 | 212.7 / 206.9 / 190.1 | 212.7 / 206.9 / 185.1 | 92289.4 | 285224 | 0.057 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -19.5 | 10.5 | gangway | 0.96 | 5.87 | 215.0 | 209.0 | 127.2 | 660.8 | 0.033 |
| 2 | -11.5 | 18.5 | gangway | 0.86 | 6.20 | 201.8 | 187.2 | 133.8 | 647.9 | 0.047 |
| 3 | 19.5 | 10.5 | gangway | 0.96 | 5.71 | 207.6 | 193.8 | 121.4 | 636.1 | 0.033 |
| 4 | -10.5 | 18.5 | gangway | 0.94 | 5.78 | 213.4 | 208.3 | 127.3 | 635.7 | 0.047 |
| 5 | 10.5 | -18.5 | gangway | 0.94 | 5.58 | 208.5 | 201.8 | 127.0 | 633.4 | 0.043 |
| 6 | 19.5 | 11.5 | gangway | 0.92 | 5.84 | 193.6 | 189.9 | 123.0 | 622.0 | 0.030 |
| 7 | 10.5 | 18.5 | gangway | 0.94 | 5.93 | 204.1 | 201.0 | 120.2 | 619.8 | 0.044 |
| 8 | 11.5 | -18.5 | gangway | 0.86 | 6.17 | 199.9 | 196.8 | 127.0 | 617.2 | 0.044 |
| 9 | 11.5 | -19.5 | gangway | 0.92 | 5.97 | 194.3 | 189.9 | 122.1 | 616.2 | 0.030 |
| 10 | -19.5 | 11.5 | gangway | 0.92 | 5.93 | 197.6 | 193.1 | 123.0 | 610.8 | 0.032 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 9.5 | 18.5 | seat row | 0.50 | 7.57 | 201.3 | 198.3 | 185.1 | 643.1 | 0.028 |
| 2 | -18.5 | -9.5 | seat row | 0.50 | 7.56 | 204.5 | 196.9 | 184.4 | 638.4 | 0.028 |
| 3 | 9.5 | -18.5 | seat row | 0.50 | 7.32 | 203.4 | 193.3 | 181.9 | 629.9 | 0.028 |
| 4 | 18.5 | 9.5 | seat row | 0.50 | 7.42 | 201.1 | 193.4 | 179.3 | 625.2 | 0.028 |
| 5 | -12.5 | 22.5 | seat row | 0.50 | 7.09 | 200.1 | 197.8 | 184.2 | 619.1 | 0.035 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 402; agent-steps of seated agents on another row's clearway: 2581.

## Deposit check

Person-seconds deposited: 520074.1, of them in excluded cells: 1453.775.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 37654 overlapping pair-steps: p99 0.0042, max 0.0099 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0042 max 0.0099; venue-geometry 1: p99 0.0002 max 0.0002 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 10 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 5.56 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 94 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
