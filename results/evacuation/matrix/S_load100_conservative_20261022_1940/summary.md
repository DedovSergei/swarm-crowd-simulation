# Experiment `S_load100_conservative`

**Task 5.10 stage 4 (AMD 26.10.1): venue S, 100% load, the CONSERVATIVE stair spacing (the Green Guide's planning rate)**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 3728 agents on 100% of the 3728 seats (spawnSeatedCrowd, seed 1337), buffer N = 4096, 1450 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (conservative)** (exit choice: 153202 evaluations, 3055 switches, 0 forced choices).
Capacity: **within design capacity** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T19:40:55, 64.8 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 701 | 122.6 |
| t90 | 1244 | 217.6 |
| t100 | 1450 | 253.6 |

t_p: the step by which ceil(p x 3728) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 347 | 0 | 24.7 | 249.2 | 16.4 | 19.1 | 41.3-51.2 |
| -x | 5.66 | 352 | 0 | 24.7 | 251.3 | 16.4 | 20.2 | 44.3-54.2 |
| +y | 5.66 | 348 | 0 | 24.7 | 250.1 | 16.4 | 20.2 | 49.0-58.9 |
| -y | 5.66 | 344 | 0 | 24.7 | 246.8 | 16.4 | 19.1 | 42.3-52.3 |
| door +x+y y | 1.20 | 291 | 466 | 4.9 | 251.3 | 59.0 | 85.3 | 22.0-32.0 |
| door +x+y x | 1.20 | 294 | 466 | 4.9 | 241.2 | 62.2 | 85.3 | 22.0-32.0 |
| door -x+y y | 1.20 | 293 | 466 | 4.9 | 249.8 | 59.8 | 85.3 | 22.0-32.0 |
| door -x+y x | 1.20 | 290 | 466 | 4.9 | 235.4 | 62.9 | 85.3 | 22.0-32.0 |
| door -x-y y | 1.20 | 293 | 466 | 4.9 | 242.2 | 61.7 | 85.3 | 22.0-32.0 |
| door -x-y x | 1.20 | 290 | 466 | 4.9 | 253.6 | 58.3 | 85.3 | 22.0-32.0 |
| door +x-y y | 1.20 | 295 | 466 | 4.9 | 239.4 | 62.8 | 85.3 | 12.1-22.0 |
| door +x-y x | 1.20 | 291 | 466 | 4.9 | 246.6 | 60.1 | 85.3 | 22.0-32.0 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 347 | 9.3% | 17.3% |
| -x | avenue | 5.66 | 352 | 9.4% | 17.6% |
| +y | avenue | 5.66 | 348 | 9.3% | 17.4% |
| -y | avenue | 5.66 | 344 | 9.2% | 17.2% |
| door +x+y y | door | 1.20 | 291 | 7.8% | 68.6% |
| door +x+y x | door | 1.20 | 294 | 7.9% | 69.3% |
| door -x+y y | door | 1.20 | 293 | 7.9% | 69.1% |
| door -x+y x | door | 1.20 | 290 | 7.8% | 68.4% |
| door -x-y y | door | 1.20 | 293 | 7.9% | 69.1% |
| door -x-y x | door | 1.20 | 290 | 7.8% | 68.4% |
| door +x-y y | door | 1.20 | 295 | 7.9% | 69.6% |
| door +x-y x | door | 1.20 | 291 | 7.8% | 68.6% |
| **doors (8)** | door | 9.60 | 2337 | 62.7% | |
| **avenues (4)** | avenue | 22.64 | 1391 | 37.3% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 253.6 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 32.7%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 465 | 12.5% | 465 | 12.5% |
| straight +x+y (x wing) 0 | straight | yes | 465 | 12.5% | 465 | 12.5% |
| corner +x+y | corner | **no** | 2 | 0.1% | 2 | 0.1% |
| straight -x+y (y wing) 0 | straight | yes | 465 | 12.5% | 465 | 12.5% |
| straight -x+y (x wing) 0 | straight | yes | 465 | 12.5% | 465 | 12.5% |
| corner -x+y | corner | **no** | 2 | 0.1% | 2 | 0.1% |
| straight -x-y (y wing) 0 | straight | yes | 465 | 12.5% | 465 | 12.5% |
| straight -x-y (x wing) 0 | straight | yes | 465 | 12.5% | 465 | 12.5% |
| corner -x-y | corner | **no** | 2 | 0.1% | 2 | 0.1% |
| straight +x-y (y wing) 0 | straight | yes | 465 | 12.5% | 465 | 12.5% |
| straight +x-y (x wing) 0 | straight | yes | 465 | 12.5% | 465 | 12.5% |
| corner +x-y | corner | **no** | 2 | 0.1% | 2 | 0.1% |
| **straight (8)** | | | 3720 | | 3720 | 99.8% |
| **corner (4)** | | | 8 | | 8 | 0.2% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 347 | 24.7 | 249.2 | 0.20 | 0.23 | 0.0% |
| -x | 352 | 24.7 | 251.3 | 0.20 | 0.24 | 0.0% |
| +y | 348 | 24.7 | 250.1 | 0.20 | 0.24 | 0.0% |
| -y | 344 | 24.7 | 246.8 | 0.20 | 0.23 | 0.0% |
| door +x+y y | 291 | 4.9 | 251.3 | 0.71 | 1.02 | 15.4% |
| door +x+y x | 294 | 4.9 | 241.2 | 0.74 | 1.02 | 24.0% |
| door -x+y y | 293 | 4.9 | 249.8 | 0.72 | 1.02 | 23.1% |
| door -x+y x | 290 | 4.9 | 235.4 | 0.75 | 1.02 | 20.8% |
| door -x-y y | 293 | 4.9 | 242.2 | 0.74 | 1.02 | 20.0% |
| door -x-y x | 290 | 4.9 | 253.6 | 0.70 | 1.02 | 11.5% |
| door +x-y y | 295 | 4.9 | 239.4 | 0.75 | 1.02 | 24.0% |
| door +x-y x | 291 | 4.9 | 246.6 | 0.72 | 1.02 | 16.0% |

Mean flow / w J averaged over the doors 0.73, over the avenues 0.20.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 465 | 291 / 174 / 47 | 0.7 | 248.4 | 2.07 | 2.71 | 84% | 84% | 0% | 3.66 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 465 | 294 / 171 / 41 | 0.7 | 238.2 | 2.13 | 2.61 | 92% | 88% | 4% | 3.58 |
| corner +x+y | 1.20 | 31.2 | 2 | 0 / 2 / 0 | 8.4 | 29.7 | 0.09 | 0.20 | 0% | 0% | 0% | nan |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 465 | 293 / 172 / 41 | 0.7 | 246.8 | 2.05 | 2.61 | 84% | 84% | 0% | 3.65 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 465 | 290 / 175 / 53 | 0.7 | 232.5 | 2.23 | 2.61 | 88% | 83% | 4% | 3.59 |
| corner -x+y | 1.20 | 31.2 | 2 | 0 / 2 / 0 | 8.4 | 29.7 | 0.09 | 0.20 | 0% | 0% | 0% | nan |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 465 | 293 / 172 / 47 | 0.7 | 239.3 | 2.14 | 2.81 | 88% | 83% | 4% | 3.63 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 465 | 290 / 175 / 49 | 0.7 | 250.6 | 2.06 | 2.61 | 81% | 81% | 0% | 3.67 |
| corner -x-y | 1.20 | 31.2 | 2 | 0 / 2 / 0 | 8.4 | 29.6 | 0.09 | 0.20 | 0% | 0% | 0% | nan |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 465 | 295 / 170 / 42 | 0.7 | 236.5 | 2.15 | 2.61 | 92% | 83% | 8% | 3.53 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 465 | 291 / 174 / 49 | 0.7 | 243.6 | 2.11 | 2.71 | 84% | 80% | 4% | 3.55 |
| corner +x-y | 1.20 | 31.2 | 2 | 0 / 2 / 0 | 8.4 | 29.7 | 0.09 | 0.20 | 0% | 0% | 0% | nan |

The last agent out (agent 2470, t100 253.6 s): last gangway straight -x-y (x wing) 0, exit door -x-y (x wall). The gangway that cleared last: straight -x-y (x wing) 0 at 250.6 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.40 | 249.9 / 241.5 / 195.7 | 229.1 / 222.8 / 138.9 | 45383.2 | 182662 | 0.319 |
| gangway | 392 | 351.5 | 6.40 | 233.9 / 224.4 / 167.4 | 229.1 / 222.8 / 138.9 | 45216.8 | 149135 | 0.106 |
| walkway | 276 | 257.4 | 1.42 | 21.7 / 0.0 / 0.0 | 3.7 / 0.0 / 0.0 | 0.0 | 7687 | 1.249 |
| avenue | 408 | 384.3 | 1.38 | 37.1 / 0.0 / 0.0 | 11.5 / 0.0 / 0.0 | 0.0 | 18081 | 1.320 |
| exit | 40 | 9.7 | 0.00 | 238.6 / 224.8 / 99.5 | 118.6 / 78.7 / 12.4 | 166.4 | 1598 | 1.322 |
| concourse | 612 | 609.0 | 1.69 | 169.1 / 0.0 / 0.0 | 28.9 / 0.0 / 0.0 | 0.0 | 6160 | 1.118 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.53 | 217.4 / 213.2 / 196.8 | 217.4 / 213.2 / 194.1 | 85954.1 | 278027 | 0.059 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 11.5 | 22.5 | gangway | 0.86 | 6.02 | 220.0 | 196.1 | 138.9 | 659.2 | 0.060 |
| 2 | 10.5 | -19.5 | gangway | 0.96 | 5.53 | 220.6 | 216.0 | 126.6 | 648.3 | 0.028 |
| 3 | -11.5 | -22.5 | gangway | 0.86 | 6.03 | 217.9 | 188.7 | 131.5 | 632.3 | 0.063 |
| 4 | 22.5 | -11.5 | gangway | 0.86 | 6.06 | 218.5 | 196.9 | 131.0 | 626.3 | 0.064 |
| 5 | 11.5 | -19.5 | gangway | 0.92 | 5.77 | 195.9 | 189.1 | 125.8 | 623.2 | 0.027 |
| 6 | 10.5 | 19.5 | gangway | 0.96 | 5.48 | 220.2 | 205.2 | 123.8 | 622.1 | 0.030 |
| 7 | -11.5 | 22.5 | gangway | 0.86 | 6.02 | 220.9 | 191.0 | 129.3 | 618.5 | 0.063 |
| 8 | -10.5 | -18.5 | gangway | 0.94 | 6.02 | 209.2 | 203.1 | 121.0 | 616.1 | 0.041 |
| 9 | -18.5 | 10.5 | gangway | 0.94 | 5.98 | 205.9 | 201.7 | 117.0 | 614.4 | 0.039 |
| 10 | 10.5 | 22.5 | gangway | 0.94 | 5.84 | 224.1 | 194.0 | 122.3 | 613.4 | 0.071 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 18.5 | 9.5 | seat row | 0.50 | 7.42 | 209.7 | 202.7 | 194.1 | 670.8 | 0.027 |
| 2 | -18.5 | -9.5 | seat row | 0.50 | 7.36 | 208.0 | 201.7 | 187.7 | 650.4 | 0.027 |
| 3 | 9.5 | -18.5 | seat row | 0.50 | 7.45 | 209.4 | 199.6 | 186.3 | 649.8 | 0.027 |
| 4 | -9.5 | 18.5 | seat row | 0.50 | 7.51 | 208.8 | 196.9 | 185.1 | 647.7 | 0.027 |
| 5 | -9.5 | -18.5 | seat row | 0.50 | 7.34 | 202.9 | 196.4 | 184.2 | 635.3 | 0.028 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 369; agent-steps of seated agents on another row's clearway: 2161.

## Deposit check

Person-seconds deposited: 460692.9, of them in excluded cells: 4.013.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 44569 overlapping pair-steps: p99 0.0021, max 0.0070 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0021 max 0.0070; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00755 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 6 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 1.69 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 90 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
