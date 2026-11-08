# Experiment `S_load125_s1`

**Task 5.9 stage 4: venue S, 125% load (seed 1): every seat + standing on the walkway and concourse**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 4660 agents (load 125.0%, requested 125%): every one of the 3728 seats and 932 standing (spawnOvercrowdedCrowd, seed 1; below), buffer N = 8192, 1481 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 172168 evaluations, 3780 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.25)** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-20T23:09:28, 12.3 s wall.

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
| t50 | 588 | 102.8 |
| t90 | 1205 | 210.8 |
| t100 | 1481 | 259.0 |

t_p: the step by which ceil(p x 4660) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 440 | 40 | 13.6 | 248.4 | 19.9 | 41.5 | 13.1-23.1 |
| -x | 5.66 | 440 | 36 | 13.6 | 245.4 | 20.1 | 40.4 | 13.3-23.3 |
| +y | 5.66 | 437 | 39 | 13.6 | 247.8 | 19.8 | 35.1 | 13.1-23.1 |
| -y | 5.66 | 442 | 38 | 13.6 | 246.6 | 20.1 | 40.4 | 13.5-23.4 |
| door +x+y y | 1.20 | 364 | 559 | 1.2 | 245.9 | 74.3 | 115.3 | 86.9-96.9 |
| door +x+y x | 1.20 | 360 | 550 | 2.1 | 250.5 | 72.4 | 125.4 | 70.8-80.8 |
| door -x+y y | 1.20 | 365 | 567 | 1.0 | 251.7 | 72.8 | 115.3 | 95.8-105.8 |
| door -x+y x | 1.20 | 360 | 568 | 1.2 | 239.3 | 75.6 | 120.4 | 89.4-99.3 |
| door -x-y y | 1.20 | 361 | 565 | 1.7 | 242.8 | 74.8 | 130.4 | 84.1-94.1 |
| door -x-y x | 1.20 | 365 | 568 | 1.2 | 247.5 | 74.1 | 120.4 | 93.7-103.7 |
| door +x-y y | 1.20 | 362 | 558 | 1.0 | 259.0 | 70.1 | 110.3 | 53.9-63.8 |
| door +x-y x | 1.20 | 364 | 572 | 1.0 | 235.6 | 77.5 | 115.3 | 77.3-87.3 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 440 | 9.4% | 21.5% |
| -x | avenue | 5.66 | 440 | 9.4% | 21.5% |
| +y | avenue | 5.66 | 437 | 9.4% | 21.4% |
| -y | avenue | 5.66 | 442 | 9.5% | 21.6% |
| door +x+y y | door | 1.20 | 364 | 7.8% | 84.0% |
| door +x+y x | door | 1.20 | 360 | 7.7% | 83.1% |
| door -x+y y | door | 1.20 | 365 | 7.8% | 84.3% |
| door -x+y x | door | 1.20 | 360 | 7.7% | 83.1% |
| door -x-y y | door | 1.20 | 361 | 7.7% | 83.4% |
| door -x-y x | door | 1.20 | 365 | 7.8% | 84.3% |
| door +x-y y | door | 1.20 | 362 | 7.8% | 83.6% |
| door +x-y x | door | 1.20 | 364 | 7.8% | 84.0% |
| **doors (8)** | door | 9.60 | 2901 | 62.3% | |
| **avenues (4)** | avenue | 22.64 | 1759 | 37.7% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 259.0 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 40.0%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 467 | 10.0% | 467 | 10.0% |
| straight +x+y (x wing) 0 | straight | yes | 468 | 10.0% | 468 | 10.0% |
| corner +x+y | corner | **no** | 5 | 0.1% | 5 | 0.1% |
| straight -x+y (y wing) 0 | straight | yes | 463 | 9.9% | 463 | 9.9% |
| straight -x+y (x wing) 0 | straight | yes | 462 | 9.9% | 462 | 9.9% |
| corner -x+y | corner | **no** | 16 | 0.3% | 16 | 0.3% |
| straight -x-y (y wing) 0 | straight | yes | 463 | 9.9% | 463 | 9.9% |
| straight -x-y (x wing) 0 | straight | yes | 460 | 9.9% | 460 | 9.9% |
| corner -x-y | corner | **no** | 16 | 0.3% | 16 | 0.3% |
| straight +x-y (y wing) 0 | straight | yes | 468 | 10.0% | 468 | 10.0% |
| straight +x-y (x wing) 0 | straight | yes | 463 | 9.9% | 461 | 9.9% |
| corner +x-y | corner | **no** | 12 | 0.3% | 12 | 0.3% |
| **straight (8)** | | | 3714 | | 3712 | 79.7% |
| **corner (4)** | | | 49 | | 49 | 1.1% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 899, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 440 | 13.6 | 248.4 | 0.24 | 0.50 | 0.0% |
| -x | 440 | 13.6 | 245.4 | 0.24 | 0.48 | 0.0% |
| +y | 437 | 13.6 | 247.8 | 0.24 | 0.42 | 0.0% |
| -y | 442 | 13.6 | 246.6 | 0.24 | 0.48 | 0.0% |
| door +x+y y | 364 | 1.2 | 245.9 | 0.89 | 1.38 | 56.0% |
| door +x+y x | 360 | 2.1 | 250.5 | 0.87 | 1.50 | 53.8% |
| door -x+y y | 365 | 1.0 | 251.7 | 0.87 | 1.38 | 61.5% |
| door -x+y x | 360 | 1.2 | 239.3 | 0.90 | 1.44 | 58.3% |
| door -x-y y | 361 | 1.7 | 242.8 | 0.90 | 1.56 | 68.0% |
| door -x-y x | 365 | 1.2 | 247.5 | 0.89 | 1.44 | 56.0% |
| door +x-y y | 362 | 1.0 | 259.0 | 0.84 | 1.32 | 57.7% |
| door +x-y x | 364 | 1.0 | 235.6 | 0.93 | 1.38 | 50.0% |

Mean flow / w J averaged over the doors 0.88, over the avenues 0.24.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 467 | 288 / 179 / 46 | 0.3 | 242.9 | 2.11 | 2.81 | 84% | 80% | 4% | 3.79 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 468 | 289 / 179 / 54 | 0.2 | 247.5 | 2.11 | 2.91 | 84% | 84% | 0% | 3.81 |
| corner +x+y | 1.20 | 31.2 | 5 | 0 / 5 / 0 | 8.2 | 33.1 | 0.20 | 0.30 | 0% | 0% | 0% | nan |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 463 | 276 / 187 / 56 | 0.3 | 248.7 | 2.09 | 3.31 | 84% | 84% | 0% | 3.91 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 462 | 278 / 184 / 44 | 0.5 | 236.3 | 2.14 | 2.81 | 88% | 88% | 0% | 3.79 |
| corner -x+y | 1.20 | 31.2 | 16 | 0 / 16 / 0 | 4.5 | 38.8 | 0.46 | 0.80 | 0% | 0% | 0% | nan |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 463 | 277 / 186 / 54 | 0.2 | 239.8 | 2.16 | 2.91 | 84% | 84% | 0% | 3.81 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 460 | 277 / 183 / 46 | 0.3 | 244.5 | 2.07 | 3.11 | 84% | 84% | 0% | 3.88 |
| corner -x-y | 1.20 | 31.2 | 16 | 0 / 16 / 0 | 4.5 | 37.3 | 0.49 | 0.80 | 0% | 0% | 0% | nan |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 466 | 284 / 185 / 53 | 0.7 | 256.1 | 2.04 | 2.91 | 77% | 77% | 0% | 3.82 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 463 | 278 / 185 / 44 | 0.7 | 232.6 | 2.18 | 2.61 | 88% | 88% | 0% | 3.84 |
| corner +x-y | 1.20 | 31.2 | 12 | 0 / 12 / 0 | 4.5 | 35.7 | 0.38 | 0.60 | 0% | 0% | 0% | nan |

The last agent out (agent 3429, t100 259.0 s): last gangway straight +x-y (y wing) 0, exit door +x-y (y wall). The gangway that cleared last: straight +x-y (y wing) 0 at 256.1 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.32 | 251.0 / 240.5 / 205.7 | 226.7 / 218.3 / 138.2 | 53598.4 | 230616 | 0.314 |
| gangway | 392 | 351.5 | 6.32 | 237.9 / 224.6 / 176.1 | 226.7 / 218.3 / 138.2 | 52140.7 | 157355 | 0.106 |
| walkway | 276 | 257.4 | 4.43 | 80.3 / 32.4 / 0.0 | 51.6 / 22.7 / 0.0 | 0.0 | 11550 | 0.988 |
| avenue | 408 | 384.3 | 2.46 | 113.9 / 6.8 / 0.0 | 82.4 / 0.5 / 0.0 | 0.0 | 22891 | 1.315 |
| exit | 40 | 9.7 | 0.00 | 250.3 / 239.6 / 164.1 | 174.4 / 145.3 / 49.5 | 584.8 | 2517 | 1.009 |
| concourse | 612 | 609.0 | 5.47 | 210.1 / 102.5 / 43.6 | 116.5 / 98.1 / 14.9 | 872.9 | 36302 | 0.321 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.57 | 213.7 / 211.6 / 189.6 | 213.7 / 211.6 / 185.2 | 91924.7 | 286489 | 0.057 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 19.5 | 10.5 | gangway | 0.96 | 5.46 | 210.9 | 203.6 | 138.2 | 693.3 | 0.033 |
| 2 | -19.5 | -10.5 | gangway | 0.96 | 5.62 | 205.7 | 197.1 | 133.3 | 683.0 | 0.032 |
| 3 | -10.5 | -18.5 | gangway | 0.94 | 5.91 | 209.9 | 202.7 | 127.2 | 652.7 | 0.046 |
| 4 | -10.5 | 19.5 | gangway | 0.96 | 5.71 | 214.4 | 198.9 | 125.2 | 641.6 | 0.033 |
| 5 | 19.5 | -10.5 | gangway | 0.96 | 5.49 | 217.6 | 208.5 | 127.3 | 641.6 | 0.032 |
| 6 | -18.5 | 10.5 | gangway | 0.94 | 5.99 | 208.1 | 204.6 | 123.8 | 637.7 | 0.045 |
| 7 | 18.5 | 10.5 | gangway | 0.94 | 5.81 | 209.0 | 200.6 | 124.7 | 627.8 | 0.045 |
| 8 | 11.5 | 19.5 | gangway | 0.92 | 5.84 | 198.3 | 189.2 | 122.6 | 624.2 | 0.029 |
| 9 | 11.5 | 18.5 | gangway | 0.86 | 6.32 | 198.3 | 194.5 | 126.5 | 623.6 | 0.043 |
| 10 | -10.5 | -19.5 | gangway | 0.96 | 5.65 | 205.0 | 195.9 | 120.0 | 620.6 | 0.029 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 9.5 | -18.5 | seat row | 0.50 | 7.52 | 202.0 | 194.8 | 182.6 | 637.1 | 0.028 |
| 2 | 9.5 | 18.5 | seat row | 0.50 | 7.51 | 200.6 | 194.0 | 182.1 | 636.7 | 0.028 |
| 3 | 18.5 | -9.5 | seat row | 0.50 | 7.29 | 208.8 | 195.2 | 185.2 | 636.0 | 0.028 |
| 4 | -18.5 | -9.5 | seat row | 0.50 | 7.48 | 199.7 | 192.9 | 180.9 | 627.5 | 0.029 |
| 5 | -18.5 | 9.5 | seat row | 0.50 | 7.57 | 201.7 | 187.0 | 177.9 | 622.6 | 0.029 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 397; agent-steps of seated agents on another row's clearway: 2433.

## Deposit check

Person-seconds deposited: 518509.0, of them in excluded cells: 1404.512.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 35077 overlapping pair-steps: p99 0.0046, max 0.0097 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0046 max 0.0097; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 4 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 5.47 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 93 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
