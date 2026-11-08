# Experiment `S_load95_s2`

**Task 5.10 stage 4 (AMD 26.10.1): venue S, 95% load (seed 2), default model**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 3542 agents on 95% of the 3728 seats (spawnSeatedCrowd, seed 2), buffer N = 4096, 1289 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 128947 evaluations, 2861 switches, 0 forced choices).
Capacity: **within design capacity** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T19:36:07, 10.7 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 623 | 109.0 |
| t90 | 1093 | 191.2 |
| t100 | 1289 | 225.5 |

t_p: the step by which ceil(p x 3542) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 329 | 0 | 24.5 | 223.4 | 17.5 | 21.3 | 42.9-52.8 |
| -x | 5.66 | 327 | 0 | 24.5 | 219.7 | 17.7 | 22.3 | 45.5-55.4 |
| +y | 5.66 | 330 | 0 | 24.3 | 220.4 | 17.8 | 21.3 | 51.9-61.9 |
| -y | 5.66 | 323 | 0 | 24.5 | 215.5 | 17.9 | 23.4 | 46.9-56.8 |
| door +x+y y | 1.20 | 282 | 450 | 4.9 | 219.9 | 65.5 | 90.3 | 30.8-40.8 |
| door +x+y x | 1.20 | 281 | 445 | 4.9 | 223.7 | 64.2 | 85.3 | 16.6-26.6 |
| door -x+y y | 1.20 | 281 | 446 | 4.9 | 212.9 | 67.5 | 85.3 | 10.1-20.1 |
| door -x+y x | 1.20 | 282 | 444 | 4.9 | 214.4 | 67.2 | 85.3 | 18.9-28.9 |
| door -x-y y | 1.20 | 275 | 437 | 4.9 | 219.5 | 64.0 | 85.3 | 39.5-49.5 |
| door -x-y x | 1.20 | 274 | 439 | 4.9 | 217.2 | 64.5 | 90.3 | 26.1-36.0 |
| door +x-y y | 1.20 | 276 | 434 | 4.9 | 215.5 | 65.5 | 90.3 | 31.1-41.1 |
| door +x-y x | 1.20 | 282 | 447 | 4.9 | 225.5 | 63.9 | 85.3 | 18.9-28.9 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 329 | 9.3% | 18.5% |
| -x | avenue | 5.66 | 327 | 9.2% | 18.4% |
| +y | avenue | 5.66 | 330 | 9.3% | 18.6% |
| -y | avenue | 5.66 | 323 | 9.1% | 18.2% |
| door +x+y y | door | 1.20 | 282 | 8.0% | 74.8% |
| door +x+y x | door | 1.20 | 281 | 7.9% | 74.5% |
| door -x+y y | door | 1.20 | 281 | 7.9% | 74.5% |
| door -x+y x | door | 1.20 | 282 | 8.0% | 74.8% |
| door -x-y y | door | 1.20 | 275 | 7.8% | 73.0% |
| door -x-y x | door | 1.20 | 274 | 7.7% | 72.7% |
| door +x-y y | door | 1.20 | 276 | 7.8% | 73.2% |
| door +x-y x | door | 1.20 | 282 | 8.0% | 74.8% |
| **doors (8)** | door | 9.60 | 2233 | 63.0% | |
| **avenues (4)** | avenue | 22.64 | 1309 | 37.0% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 225.5 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 35.0%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 449 | 12.7% | 449 | 12.7% |
| straight +x+y (x wing) 0 | straight | yes | 444 | 12.5% | 444 | 12.5% |
| corner +x+y | corner | **no** | 2 | 0.1% | 2 | 0.1% |
| straight -x+y (y wing) 0 | straight | yes | 444 | 12.5% | 444 | 12.5% |
| straight -x+y (x wing) 0 | straight | yes | 444 | 12.5% | 444 | 12.5% |
| corner -x+y | corner | **no** | 2 | 0.1% | 2 | 0.1% |
| straight -x-y (y wing) 0 | straight | yes | 436 | 12.3% | 436 | 12.3% |
| straight -x-y (x wing) 0 | straight | yes | 437 | 12.3% | 437 | 12.3% |
| corner -x-y | corner | **no** | 3 | 0.1% | 3 | 0.1% |
| straight +x-y (y wing) 0 | straight | yes | 434 | 12.3% | 434 | 12.3% |
| straight +x-y (x wing) 0 | straight | yes | 446 | 12.6% | 446 | 12.6% |
| corner +x-y | corner | **no** | 1 | 0.0% | 1 | 0.0% |
| **straight (8)** | | | 3534 | | 3534 | 99.8% |
| **corner (4)** | | | 8 | | 8 | 0.2% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 329 | 24.5 | 223.4 | 0.21 | 0.25 | 0.0% |
| -x | 327 | 24.5 | 219.7 | 0.21 | 0.27 | 0.0% |
| +y | 330 | 24.3 | 220.4 | 0.21 | 0.25 | 0.0% |
| -y | 323 | 24.5 | 215.5 | 0.21 | 0.28 | 0.0% |
| door +x+y y | 282 | 4.9 | 219.9 | 0.78 | 1.08 | 43.5% |
| door +x+y x | 281 | 4.9 | 223.7 | 0.77 | 1.02 | 43.5% |
| door -x+y y | 281 | 4.9 | 212.9 | 0.81 | 1.02 | 54.5% |
| door -x+y x | 282 | 4.9 | 214.4 | 0.80 | 1.02 | 54.5% |
| door -x-y y | 275 | 4.9 | 219.5 | 0.77 | 1.02 | 47.8% |
| door -x-y x | 274 | 4.9 | 217.2 | 0.77 | 1.08 | 31.8% |
| door +x-y y | 276 | 4.9 | 215.5 | 0.78 | 1.08 | 40.9% |
| door +x-y x | 282 | 4.9 | 225.5 | 0.76 | 1.02 | 47.8% |

Mean flow / w J averaged over the doors 0.78, over the avenues 0.21.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 449 | 282 / 167 / 39 | 0.7 | 216.9 | 2.26 | 3.11 | 86% | 82% | 5% | 3.61 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 444 | 281 / 163 / 40 | 0.7 | 220.7 | 2.20 | 2.91 | 83% | 83% | 0% | 3.68 |
| corner +x+y | 1.20 | 31.2 | 2 | 0 / 2 / 0 | 8.2 | 30.6 | 0.09 | 0.10 | 0% | 0% | 0% | nan |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 444 | 281 / 163 / 36 | 0.7 | 209.9 | 2.29 | 2.91 | 86% | 82% | 5% | 3.65 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 444 | 282 / 162 / 48 | 0.7 | 211.5 | 2.33 | 2.81 | 82% | 82% | 0% | 3.63 |
| corner -x+y | 1.20 | 31.2 | 2 | 0 / 2 / 0 | 8.2 | 30.6 | 0.09 | 0.10 | 0% | 0% | 0% | nan |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 436 | 275 / 161 / 44 | 0.7 | 216.5 | 2.22 | 3.11 | 77% | 77% | 0% | 3.72 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 437 | 274 / 163 / 43 | 0.7 | 214.3 | 2.25 | 2.81 | 82% | 82% | 0% | 3.66 |
| corner -x-y | 1.20 | 31.2 | 3 | 0 / 3 / 0 | 8.2 | 32.9 | 0.12 | 0.20 | 0% | 0% | 0% | nan |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 434 | 276 / 158 / 47 | 0.7 | 212.5 | 2.27 | 2.91 | 82% | 82% | 0% | 3.75 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 446 | 282 / 164 / 44 | 0.7 | 222.5 | 2.21 | 2.91 | 78% | 78% | 0% | 3.73 |
| corner +x-y | 1.20 | 31.2 | 1 | 0 / 1 / 0 | 8.4 | 29.0 | 0.05 | 0.10 | 0% | 0% | 0% | nan |

The last agent out (agent 3261, t100 225.5 s): last gangway straight +x-y (x wing) 0, exit door +x-y (x wall). The gangway that cleared last: straight +x-y (x wing) 0 at 222.5 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.41 | 222.0 / 212.9 / 175.4 | 200.3 / 196.8 / 124.5 | 37635.9 | 163548 | 0.338 |
| gangway | 392 | 351.5 | 6.41 | 211.3 / 197.5 / 151.1 | 200.3 / 196.8 / 124.5 | 37469.5 | 131898 | 0.116 |
| walkway | 276 | 257.4 | 1.67 | 22.0 / 0.0 / 0.0 | 3.5 / 0.0 / 0.0 | 0.0 | 7228 | 1.246 |
| avenue | 408 | 384.3 | 1.41 | 54.7 / 0.0 / 0.0 | 17.1 / 0.0 / 0.0 | 0.0 | 17015 | 1.319 |
| exit | 40 | 9.7 | 0.00 | 217.2 / 206.0 / 107.6 | 116.1 / 76.8 / 12.8 | 166.5 | 1521 | 1.321 |
| concourse | 612 | 609.0 | 1.70 | 177.7 / 0.0 / 0.0 | 35.7 / 0.0 / 0.0 | 0.0 | 5886 | 1.118 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.56 | 189.6 / 185.6 / 170.5 | 189.6 / 185.6 / 167.9 | 67499.1 | 224758 | 0.069 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 22.5 | 11.5 | gangway | 0.86 | 6.33 | 194.8 | 182.8 | 124.5 | 607.1 | 0.063 |
| 2 | 19.5 | -11.5 | gangway | 0.92 | 5.90 | 172.3 | 167.9 | 114.9 | 574.5 | 0.030 |
| 3 | -19.5 | 11.5 | gangway | 0.92 | 5.57 | 176.8 | 168.6 | 117.2 | 567.8 | 0.031 |
| 4 | 11.5 | -22.5 | gangway | 0.86 | 6.14 | 188.2 | 170.9 | 117.7 | 562.2 | 0.072 |
| 5 | -11.5 | -22.5 | gangway | 0.86 | 6.12 | 182.8 | 167.7 | 116.3 | 557.5 | 0.066 |
| 6 | -22.5 | -11.5 | gangway | 0.86 | 5.87 | 192.0 | 171.4 | 116.3 | 552.7 | 0.063 |
| 7 | 19.5 | 10.5 | gangway | 0.96 | 5.55 | 192.0 | 172.3 | 106.2 | 545.5 | 0.033 |
| 8 | 11.5 | 22.5 | gangway | 0.86 | 6.31 | 187.8 | 171.1 | 111.6 | 542.6 | 0.068 |
| 9 | 18.5 | -11.5 | gangway | 0.86 | 6.09 | 174.9 | 171.6 | 111.9 | 538.7 | 0.045 |
| 10 | -11.5 | 22.5 | gangway | 0.86 | 6.41 | 189.2 | 175.1 | 108.8 | 538.4 | 0.064 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 9.5 | 18.5 | seat row | 0.50 | 7.56 | 185.1 | 178.2 | 167.9 | 588.0 | 0.029 |
| 2 | 18.5 | 9.5 | seat row | 0.50 | 7.56 | 184.5 | 179.6 | 164.8 | 577.2 | 0.030 |
| 3 | 9.5 | -18.5 | seat row | 0.50 | 7.37 | 174.6 | 171.8 | 163.5 | 569.2 | 0.030 |
| 4 | -18.5 | 9.5 | seat row | 0.50 | 7.48 | 175.8 | 170.9 | 160.2 | 554.5 | 0.031 |
| 5 | 18.5 | -9.5 | seat row | 0.50 | 7.52 | 177.9 | 173.3 | 160.9 | 553.1 | 0.032 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 341; agent-steps of seated agents on another row's clearway: 2219.

## Deposit check

Person-seconds deposited: 388309.2, of them in excluded cells: 3.740.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 31635 overlapping pair-steps: p99 0.0034, max 0.0095 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0034 max 0.0095; venue-geometry 1: p99 0.0002 max 0.0002 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00757 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 2 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 1.70 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 72 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
