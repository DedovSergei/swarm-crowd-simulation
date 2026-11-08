# Experiment `S_load95_s1`

**Task 5.10 stage 4 (AMD 26.10.1): venue S, 95% load (seed 1), default model**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 3542 agents on 95% of the 3728 seats (spawnSeatedCrowd, seed 1), buffer N = 4096, 1323 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 129576 evaluations, 2866 switches, 0 forced choices).
Capacity: **within design capacity** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T19:35:48, 14.6 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 626 | 109.5 |
| t90 | 1098 | 192.0 |
| t100 | 1323 | 231.4 |

t_p: the step by which ceil(p x 3542) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 327 | 0 | 24.5 | 221.8 | 17.6 | 21.3 | 55.8-65.8 |
| -x | 5.66 | 330 | 0 | 24.1 | 223.4 | 17.5 | 23.4 | 50.0-60.0 |
| +y | 5.66 | 335 | 0 | 24.1 | 222.7 | 17.9 | 22.3 | 47.0-57.0 |
| -y | 5.66 | 328 | 0 | 24.3 | 220.7 | 17.7 | 21.3 | 44.4-54.4 |
| door +x+y y | 1.20 | 278 | 445 | 4.9 | 225.5 | 63.0 | 90.3 | 56.8-66.8 |
| door +x+y x | 1.20 | 278 | 440 | 4.9 | 223.4 | 63.6 | 90.3 | 15.9-25.9 |
| door -x+y y | 1.20 | 278 | 445 | 4.9 | 219.3 | 64.8 | 90.3 | 30.3-40.2 |
| door -x+y x | 1.20 | 273 | 436 | 4.9 | 219.7 | 63.5 | 90.3 | 39.9-49.8 |
| door -x-y y | 1.20 | 278 | 439 | 4.9 | 231.4 | 61.3 | 85.3 | 4.7-14.7 |
| door -x-y x | 1.20 | 279 | 445 | 4.9 | 223.9 | 63.7 | 85.3 | 35.5-45.5 |
| door +x-y y | 1.20 | 276 | 442 | 4.9 | 213.9 | 66.0 | 90.3 | 31.7-41.6 |
| door +x-y x | 1.20 | 282 | 450 | 4.9 | 215.1 | 67.0 | 90.3 | 34.1-44.1 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 327 | 9.2% | 17.9% |
| -x | avenue | 5.66 | 330 | 9.3% | 18.1% |
| +y | avenue | 5.66 | 335 | 9.5% | 18.4% |
| -y | avenue | 5.66 | 328 | 9.3% | 18.0% |
| door +x+y y | door | 1.20 | 278 | 7.8% | 71.9% |
| door +x+y x | door | 1.20 | 278 | 7.8% | 71.9% |
| door -x+y y | door | 1.20 | 278 | 7.8% | 71.9% |
| door -x+y x | door | 1.20 | 273 | 7.7% | 70.6% |
| door -x-y y | door | 1.20 | 278 | 7.8% | 71.9% |
| door -x-y x | door | 1.20 | 279 | 7.9% | 72.1% |
| door +x-y y | door | 1.20 | 276 | 7.8% | 71.3% |
| door +x-y x | door | 1.20 | 282 | 8.0% | 72.9% |
| **doors (8)** | door | 9.60 | 2222 | 62.7% | |
| **avenues (4)** | avenue | 22.64 | 1320 | 37.3% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 231.4 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 34.1%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 444 | 12.5% | 444 | 12.5% |
| straight +x+y (x wing) 0 | straight | yes | 438 | 12.4% | 438 | 12.4% |
| corner +x+y | corner | **no** | 3 | 0.1% | 3 | 0.1% |
| straight -x+y (y wing) 0 | straight | yes | 444 | 12.5% | 444 | 12.5% |
| straight -x+y (x wing) 0 | straight | yes | 435 | 12.3% | 435 | 12.3% |
| corner -x+y | corner | **no** | 2 | 0.1% | 2 | 0.1% |
| straight -x-y (y wing) 0 | straight | yes | 439 | 12.4% | 439 | 12.4% |
| straight -x-y (x wing) 0 | straight | yes | 445 | 12.6% | 444 | 12.5% |
| corner -x-y | corner | **no** | 1 | 0.0% | 1 | 0.0% |
| straight +x-y (y wing) 0 | straight | yes | 440 | 12.4% | 440 | 12.4% |
| straight +x-y (x wing) 0 | straight | yes | 449 | 12.7% | 449 | 12.7% |
| corner +x-y | corner | **no** | 3 | 0.1% | 3 | 0.1% |
| **straight (8)** | | | 3534 | | 3533 | 99.7% |
| **corner (4)** | | | 9 | | 9 | 0.3% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 327 | 24.5 | 221.8 | 0.21 | 0.25 | 0.0% |
| -x | 330 | 24.1 | 223.4 | 0.21 | 0.28 | 0.0% |
| +y | 335 | 24.1 | 222.7 | 0.21 | 0.27 | 0.0% |
| -y | 328 | 24.3 | 220.7 | 0.21 | 0.25 | 0.0% |
| door +x+y y | 278 | 4.9 | 225.5 | 0.75 | 1.08 | 39.1% |
| door +x+y x | 278 | 4.9 | 223.4 | 0.76 | 1.08 | 43.5% |
| door -x+y y | 278 | 4.9 | 219.3 | 0.77 | 1.08 | 40.9% |
| door -x+y x | 273 | 4.9 | 219.7 | 0.76 | 1.08 | 30.4% |
| door -x-y y | 278 | 4.9 | 231.4 | 0.73 | 1.02 | 45.8% |
| door -x-y x | 279 | 4.9 | 223.9 | 0.76 | 1.02 | 34.8% |
| door +x-y y | 276 | 4.9 | 213.9 | 0.79 | 1.08 | 50.0% |
| door +x-y x | 282 | 4.9 | 215.1 | 0.80 | 1.08 | 45.5% |

Mean flow / w J averaged over the doors 0.77, over the avenues 0.21.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 444 | 278 / 166 / 45 | 0.7 | 222.5 | 2.20 | 2.71 | 78% | 78% | 0% | 3.73 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 438 | 278 / 160 / 40 | 0.7 | 220.4 | 2.17 | 2.91 | 78% | 78% | 0% | 3.77 |
| corner +x+y | 1.20 | 31.2 | 3 | 0 / 3 / 0 | 8.2 | 32.0 | 0.13 | 0.20 | 0% | 0% | 0% | nan |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 444 | 278 / 166 / 41 | 0.7 | 216.4 | 2.25 | 2.91 | 86% | 82% | 5% | 3.60 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 435 | 273 / 162 / 53 | 0.7 | 216.7 | 2.26 | 3.31 | 82% | 82% | 0% | 3.74 |
| corner -x+y | 1.20 | 31.2 | 2 | 0 / 2 / 0 | 8.2 | 30.6 | 0.09 | 0.10 | 0% | 0% | 0% | nan |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 438 | 278 / 161 / 34 | 0.7 | 228.6 | 2.07 | 2.81 | 78% | 78% | 0% | 3.62 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 445 | 279 / 166 / 35 | 0.7 | 220.9 | 2.18 | 3.11 | 83% | 78% | 4% | 3.71 |
| corner -x-y | 1.20 | 31.2 | 1 | 0 / 1 / 0 | 8.2 | 30.6 | 0.04 | 0.10 | 0% | 0% | 0% | nan |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 440 | 276 / 164 / 41 | 0.7 | 210.9 | 2.29 | 2.81 | 86% | 82% | 5% | 3.64 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 449 | 282 / 167 / 47 | 0.7 | 212.2 | 2.34 | 2.91 | 86% | 82% | 5% | 3.62 |
| corner +x-y | 1.20 | 31.2 | 3 | 0 / 3 / 0 | 8.2 | 32.0 | 0.13 | 0.20 | 0% | 0% | 0% | nan |

The last agent out (agent 2373, t100 231.4 s): last gangway straight -x-y (y wing) 0, exit door -x-y (y wall). The gangway that cleared last: straight -x-y (y wing) 0 at 228.6 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.54 | 223.9 / 215.3 / 177.9 | 200.8 / 195.2 / 115.6 | 38475.7 | 164437 | 0.338 |
| gangway | 392 | 351.5 | 6.54 | 210.4 / 198.7 / 157.2 | 200.8 / 195.2 / 115.6 | 38313.7 | 132613 | 0.115 |
| walkway | 276 | 257.4 | 1.94 | 24.1 / 0.0 / 0.0 | 4.5 / 0.0 / 0.0 | 0.0 | 7283 | 1.245 |
| avenue | 408 | 384.3 | 1.46 | 57.5 / 0.0 / 0.0 | 18.2 / 0.0 / 0.0 | 0.0 | 17159 | 1.319 |
| exit | 40 | 9.7 | 0.00 | 219.0 / 208.0 / 102.1 | 117.0 / 77.1 / 12.9 | 162.0 | 1521 | 1.321 |
| concourse | 612 | 609.0 | 1.63 | 177.7 / 0.0 / 0.0 | 33.2 / 0.0 / 0.0 | 0.0 | 5860 | 1.117 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.55 | 190.6 / 186.3 / 169.0 | 190.6 / 186.1 / 166.3 | 69166.7 | 225819 | 0.069 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 18.5 | 10.5 | gangway | 0.94 | 5.88 | 179.6 | 175.4 | 114.4 | 585.8 | 0.046 |
| 2 | 19.5 | 11.5 | gangway | 0.92 | 6.12 | 170.0 | 162.0 | 112.3 | 583.9 | 0.029 |
| 3 | 19.5 | 10.5 | gangway | 0.96 | 5.85 | 186.8 | 174.0 | 109.3 | 577.8 | 0.036 |
| 4 | -19.5 | -10.5 | gangway | 0.96 | 5.40 | 193.3 | 182.3 | 112.5 | 561.6 | 0.031 |
| 5 | 11.5 | 22.5 | gangway | 0.86 | 5.95 | 189.1 | 179.1 | 115.6 | 556.8 | 0.062 |
| 6 | -22.5 | 11.5 | gangway | 0.86 | 6.54 | 184.9 | 173.7 | 112.8 | 553.1 | 0.062 |
| 7 | 22.5 | 11.5 | gangway | 0.86 | 6.25 | 188.7 | 173.7 | 112.1 | 546.4 | 0.067 |
| 8 | 11.5 | -22.5 | gangway | 0.86 | 6.40 | 189.6 | 178.6 | 109.7 | 542.3 | 0.064 |
| 9 | -11.5 | -18.5 | gangway | 0.86 | 6.09 | 171.6 | 164.2 | 114.0 | 538.7 | 0.043 |
| 10 | 19.5 | -11.5 | gangway | 0.92 | 5.92 | 174.4 | 160.6 | 107.0 | 538.7 | 0.029 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 18.5 | -9.5 | seat row | 0.50 | 7.52 | 179.5 | 173.5 | 166.3 | 573.9 | 0.031 |
| 2 | 18.5 | 9.5 | seat row | 0.50 | 7.44 | 177.7 | 173.7 | 164.8 | 571.5 | 0.031 |
| 3 | -9.5 | 18.5 | seat row | 0.50 | 7.54 | 178.8 | 173.0 | 163.2 | 567.9 | 0.029 |
| 4 | 9.5 | 18.5 | seat row | 0.50 | 7.55 | 178.6 | 169.7 | 157.2 | 547.9 | 0.031 |
| 5 | -9.5 | -18.5 | seat row | 0.50 | 7.51 | 178.2 | 173.0 | 157.4 | 544.8 | 0.031 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 336; agent-steps of seated agents on another row's clearway: 2139.

## Deposit check

Person-seconds deposited: 390259.2, of them in excluded cells: 3.675.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 38534 overlapping pair-steps: p99 0.0030, max 0.0092 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0030 max 0.0092; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 2 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 1.94 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 86 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
