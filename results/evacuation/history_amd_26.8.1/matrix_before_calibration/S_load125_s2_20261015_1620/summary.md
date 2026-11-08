# Experiment `S_load125_s2`

**Task 5.8 stage 2: venue S, 125% load (seed 2): every seat + standing on the walkway and concourse**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 4660 agents (load 125.0%, requested 125%): every one of the 3728 seats and 932 standing (spawnOvercrowdedCrowd, seed 2; below), buffer N = 8192, 1283 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 155180 evaluations, 3761 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.25)** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `cd8e0bbf3411846ca7aa6719887d122a142a7ca1`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-15T16:20:54, 12.1 s wall.

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
| t50 | 576 | 100.7 |
| t90 | 1015 | 177.5 |
| t100 | 1283 | 224.4 |

t_p: the step by which ceil(p x 4660) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 442 | 35 | 13.5 | 206.6 | 24.2 | 38.3 | 12.9-22.9 |
| -x | 5.66 | 447 | 34 | 13.5 | 209.9 | 24.1 | 36.2 | 13.1-23.1 |
| +y | 5.66 | 441 | 30 | 13.8 | 205.9 | 24.3 | 37.2 | 13.3-23.3 |
| -y | 5.66 | 442 | 42 | 13.8 | 209.5 | 23.9 | 40.4 | 13.1-23.1 |
| door +x+y y | 1.20 | 356 | 563 | 1.2 | 211.5 | 84.6 | 135.4 | 118.8-128.7 |
| door +x+y x | 1.20 | 367 | 573 | 1.2 | 215.0 | 85.8 | 125.4 | 127.5-137.5 |
| door -x+y y | 1.20 | 363 | 567 | 0.9 | 224.4 | 81.1 | 130.4 | 111.1-121.0 |
| door -x+y x | 1.20 | 363 | 570 | 1.6 | 220.9 | 82.7 | 135.4 | 125.2-135.2 |
| door -x-y y | 1.20 | 360 | 558 | 1.2 | 208.1 | 86.9 | 125.4 | 102.5-112.5 |
| door -x-y x | 1.20 | 357 | 556 | 0.9 | 210.1 | 85.3 | 130.4 | 103.5-113.5 |
| door +x-y y | 1.20 | 363 | 571 | 1.2 | 217.6 | 83.8 | 130.4 | 100.7-110.7 |
| door +x-y x | 1.20 | 359 | 561 | 1.2 | 208.5 | 86.5 | 135.4 | 119.8-129.8 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 442 | 9.5% | 25.0% |
| -x | avenue | 5.66 | 447 | 9.6% | 25.3% |
| +y | avenue | 5.66 | 441 | 9.5% | 24.9% |
| -y | avenue | 5.66 | 442 | 9.5% | 25.0% |
| door +x+y y | door | 1.20 | 356 | 7.6% | 94.9% |
| door +x+y x | door | 1.20 | 367 | 7.9% | 97.8% |
| door -x+y y | door | 1.20 | 363 | 7.8% | 96.7% |
| door -x+y x | door | 1.20 | 363 | 7.8% | 96.7% |
| door -x-y y | door | 1.20 | 360 | 7.7% | 95.9% |
| door -x-y x | door | 1.20 | 357 | 7.7% | 95.1% |
| door +x-y y | door | 1.20 | 363 | 7.8% | 96.7% |
| door +x-y x | door | 1.20 | 359 | 7.7% | 95.7% |
| **doors (8)** | door | 9.60 | 2888 | 62.0% | |
| **avenues (4)** | avenue | 22.64 | 1772 | 38.0% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 224.4 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 46.2%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 465 | 10.0% | 465 | 10.0% |
| straight +x+y (x wing) 0 | straight | yes | 462 | 9.9% | 462 | 9.9% |
| corner +x+y | corner | **no** | 14 | 0.3% | 14 | 0.3% |
| straight -x+y (y wing) 0 | straight | yes | 464 | 10.0% | 464 | 10.0% |
| straight -x+y (x wing) 0 | straight | yes | 463 | 9.9% | 460 | 9.9% |
| corner -x+y | corner | **no** | 17 | 0.4% | 17 | 0.4% |
| straight -x-y (y wing) 0 | straight | yes | 463 | 9.9% | 463 | 9.9% |
| straight -x-y (x wing) 0 | straight | yes | 463 | 9.9% | 463 | 9.9% |
| corner -x-y | corner | **no** | 14 | 0.3% | 14 | 0.3% |
| straight +x-y (y wing) 0 | straight | yes | 465 | 10.0% | 465 | 10.0% |
| straight +x-y (x wing) 0 | straight | yes | 462 | 9.9% | 462 | 9.9% |
| corner +x-y | corner | **no** | 15 | 0.3% | 15 | 0.3% |
| **straight (8)** | | | 3707 | | 3704 | 79.5% |
| **corner (4)** | | | 60 | | 60 | 1.3% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 896, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 442 | 13.5 | 206.6 | 0.29 | 0.46 | 0.0% |
| -x | 447 | 13.5 | 209.9 | 0.29 | 0.43 | 0.0% |
| +y | 441 | 13.8 | 205.9 | 0.29 | 0.45 | 0.0% |
| -y | 442 | 13.8 | 209.5 | 0.29 | 0.48 | 0.0% |
| door +x+y y | 356 | 1.2 | 211.5 | 1.01 | 1.62 | 86.4% |
| door +x+y x | 367 | 1.2 | 215.0 | 1.03 | 1.50 | 86.4% |
| door -x+y y | 363 | 0.9 | 224.4 | 0.97 | 1.56 | 78.3% |
| door -x+y x | 363 | 1.6 | 220.9 | 0.99 | 1.62 | 82.6% |
| door -x-y y | 360 | 1.2 | 208.1 | 1.04 | 1.50 | 85.7% |
| door -x-y x | 357 | 0.9 | 210.1 | 1.02 | 1.56 | 81.8% |
| door +x-y y | 363 | 1.2 | 217.6 | 1.00 | 1.56 | 86.4% |
| door +x-y x | 359 | 1.2 | 208.5 | 1.04 | 1.62 | 90.5% |

Mean flow / w J averaged over the doors 1.01, over the avenues 0.29.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 465 | 275 / 190 / 44 | 0.2 | 208.5 | 2.44 | 3.61 | 81% | 81% | 0% | 4.26 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 462 | 273 / 189 / 62 | 0.7 | 212.0 | 2.48 | 3.91 | 77% | 77% | 0% | 4.25 |
| corner +x+y | 1.20 | 31.2 | 14 | 0 / 14 / 0 | 4.5 | 34.5 | 0.47 | 0.60 | 0% | 0% | 0% | nan |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 461 | 278 / 186 / 49 | 0.7 | 221.4 | 2.32 | 3.61 | 74% | 74% | 0% | 4.21 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 463 | 276 / 187 / 58 | 0.7 | 217.9 | 2.40 | 3.71 | 82% | 82% | 0% | 4.28 |
| corner -x+y | 1.20 | 31.2 | 17 | 0 / 17 / 0 | 4.5 | 36.7 | 0.53 | 0.80 | 0% | 0% | 0% | nan |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 463 | 280 / 183 / 42 | 0.7 | 205.2 | 2.47 | 3.51 | 76% | 76% | 0% | 4.24 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 463 | 277 / 186 / 55 | 0.7 | 207.1 | 2.51 | 3.71 | 81% | 81% | 0% | 4.13 |
| corner -x-y | 1.20 | 31.2 | 14 | 0 / 14 / 0 | 4.5 | 36.6 | 0.44 | 0.80 | 0% | 0% | 0% | nan |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 465 | 273 / 193 / 47 | 0.3 | 214.6 | 2.39 | 3.71 | 77% | 77% | 0% | 4.31 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 462 | 278 / 184 / 52 | 0.7 | 205.5 | 2.51 | 3.81 | 81% | 81% | 0% | 4.26 |
| corner +x-y | 1.20 | 31.2 | 15 | 0 / 15 / 0 | 4.5 | 34.5 | 0.50 | 0.70 | 0% | 0% | 0% | nan |

The last agent out (agent 1510, t100 224.4 s): last gangway straight -x+y (y wing) 0, exit door -x+y (y wall). The gangway that cleared last: straight -x+y (y wing) 0 at 221.4 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.36 | 220.6 / 210.8 / 176.5 | 195.9 / 188.9 / 108.3 | 43637.8 | 226160 | 0.326 |
| gangway | 392 | 351.5 | 6.36 | 216.9 / 191.2 / 149.0 | 195.9 / 188.9 / 108.3 | 40750.1 | 143128 | 0.124 |
| walkway | 276 | 257.4 | 4.01 | 153.9 / 48.1 / 0.0 | 101.6 / 18.5 / 0.0 | 0.0 | 12306 | 0.922 |
| avenue | 408 | 384.3 | 2.38 | 187.8 / 0.9 / 0.0 | 143.2 / 0.7 / 0.0 | 0.0 | 23093 | 1.311 |
| exit | 40 | 9.7 | 0.00 | 216.2 / 210.6 / 165.3 | 179.5 / 158.1 / 58.1 | 693.3 | 2661 | 0.936 |
| concourse | 612 | 609.0 | 5.66 | 193.6 / 134.0 / 62.3 | 160.6 / 123.3 / 34.6 | 2194.4 | 44972 | 0.263 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.54 | 176.5 / 175.1 / 159.7 | 176.5 / 175.1 / 156.9 | 77218.8 | 240125 | 0.069 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -10.5 | 18.5 | gangway | 0.94 | 5.77 | 169.7 | 163.2 | 108.3 | 541.3 | 0.066 |
| 2 | -20.5 | 10.5 | gangway | 0.96 | 5.62 | 181.4 | 170.5 | 103.7 | 537.3 | 0.045 |
| 3 | -18.5 | 10.5 | gangway | 0.94 | 5.69 | 181.4 | 171.6 | 103.7 | 514.0 | 0.067 |
| 4 | 11.5 | 21.5 | gangway | 0.89 | 5.70 | 173.2 | 170.5 | 103.9 | 506.0 | 0.052 |
| 5 | -10.5 | -18.5 | gangway | 0.94 | 5.83 | 169.1 | 161.3 | 101.3 | 503.9 | 0.065 |
| 6 | 20.5 | -10.5 | gangway | 0.96 | 5.75 | 177.9 | 167.7 | 97.2 | 498.7 | 0.052 |
| 7 | -11.5 | -19.5 | gangway | 0.92 | 5.87 | 153.6 | 150.8 | 101.3 | 498.2 | 0.050 |
| 8 | 18.5 | -10.5 | gangway | 0.94 | 5.80 | 171.9 | 164.8 | 98.6 | 493.2 | 0.066 |
| 9 | -18.5 | -10.5 | gangway | 0.94 | 5.76 | 171.9 | 167.4 | 97.2 | 489.1 | 0.065 |
| 10 | 11.5 | -21.5 | gangway | 0.89 | 6.24 | 176.0 | 172.5 | 97.2 | 489.0 | 0.050 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -9.5 | -18.5 | seat row | 0.50 | 7.32 | 163.7 | 162.5 | 153.2 | 526.1 | 0.034 |
| 2 | -18.5 | -9.5 | seat row | 0.50 | 7.54 | 167.2 | 164.8 | 152.2 | 521.7 | 0.034 |
| 3 | 12.5 | -22.5 | seat row | 0.50 | 7.16 | 166.2 | 164.9 | 156.9 | 520.1 | 0.043 |
| 4 | 18.5 | 9.5 | seat row | 0.50 | 7.47 | 165.3 | 163.7 | 151.3 | 518.0 | 0.034 |
| 5 | -22.5 | 12.5 | seat row | 0.50 | 7.07 | 167.4 | 164.8 | 154.8 | 516.6 | 0.042 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 407; agent-steps of seated agents on another row's clearway: 3769.

## Deposit check

Person-seconds deposited: 467901.2, of them in excluded cells: 1615.590.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 24009 overlapping pair-steps: p99 0.0029, max 0.0075 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0029 max 0.0075; venue-geometry 1: p99 0.0001 max 0.0001 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 3 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 5.66 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 163 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
