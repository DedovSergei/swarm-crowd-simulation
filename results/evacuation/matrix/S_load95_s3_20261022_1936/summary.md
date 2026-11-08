# Experiment `S_load95_s3`

**Task 5.10 stage 4 (AMD 26.10.1): venue S, 95% load (seed 3), default model**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 3542 agents on 95% of the 3728 seats (spawnSeatedCrowd, seed 3), buffer N = 4096, 1327 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 130722 evaluations, 2870 switches, 0 forced choices).
Capacity: **within design capacity** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T19:36:22, 10.6 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 633 | 110.7 |
| t90 | 1106 | 193.4 |
| t100 | 1327 | 232.1 |

t_p: the step by which ceil(p x 3542) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 334 | 0 | 24.3 | 224.8 | 17.6 | 22.3 | 43.9-53.9 |
| -x | 5.66 | 325 | 0 | 24.5 | 219.5 | 17.7 | 21.3 | 46.0-56.0 |
| +y | 5.66 | 330 | 0 | 24.5 | 220.6 | 17.8 | 20.2 | 52.6-62.6 |
| -y | 5.66 | 337 | 0 | 24.5 | 222.1 | 18.1 | 24.5 | 49.7-59.6 |
| door +x+y y | 1.20 | 277 | 446 | 4.9 | 224.6 | 63.0 | 90.3 | 21.5-31.5 |
| door +x+y x | 1.20 | 276 | 439 | 4.9 | 221.1 | 63.8 | 85.3 | 25.2-35.2 |
| door -x+y y | 1.20 | 276 | 441 | 4.9 | 220.9 | 63.8 | 85.3 | 23.3-33.2 |
| door -x+y x | 1.20 | 278 | 442 | 4.9 | 213.9 | 66.4 | 85.3 | 55.1-65.1 |
| door -x-y y | 1.20 | 277 | 443 | 4.9 | 220.6 | 64.2 | 85.3 | 21.9-31.8 |
| door -x-y x | 1.20 | 282 | 445 | 4.9 | 223.4 | 64.5 | 85.3 | 19.4-29.4 |
| door +x-y y | 1.20 | 274 | 440 | 4.9 | 229.5 | 61.0 | 85.3 | 28.7-38.7 |
| door +x-y x | 1.20 | 276 | 446 | 4.9 | 232.1 | 60.7 | 85.3 | 50.4-60.3 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 334 | 9.4% | 18.2% |
| -x | avenue | 5.66 | 325 | 9.2% | 17.8% |
| +y | avenue | 5.66 | 330 | 9.3% | 18.0% |
| -y | avenue | 5.66 | 337 | 9.5% | 18.4% |
| door +x+y y | door | 1.20 | 277 | 7.8% | 71.4% |
| door +x+y x | door | 1.20 | 276 | 7.8% | 71.1% |
| door -x+y y | door | 1.20 | 276 | 7.8% | 71.1% |
| door -x+y x | door | 1.20 | 278 | 7.8% | 71.6% |
| door -x-y y | door | 1.20 | 277 | 7.8% | 71.4% |
| door -x-y x | door | 1.20 | 282 | 8.0% | 72.7% |
| door +x-y y | door | 1.20 | 274 | 7.7% | 70.6% |
| door +x-y x | door | 1.20 | 276 | 7.8% | 71.1% |
| **doors (8)** | door | 9.60 | 2216 | 62.6% | |
| **avenues (4)** | avenue | 22.64 | 1326 | 37.4% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 232.1 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 34.0%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 443 | 12.5% | 443 | 12.5% |
| straight +x+y (x wing) 0 | straight | yes | 437 | 12.3% | 437 | 12.3% |
| corner +x+y | corner | **no** | 5 | 0.1% | 5 | 0.1% |
| straight -x+y (y wing) 0 | straight | yes | 440 | 12.4% | 440 | 12.4% |
| straight -x+y (x wing) 0 | straight | yes | 442 | 12.5% | 442 | 12.5% |
| corner -x+y | corner | **no** | 1 | 0.0% | 1 | 0.0% |
| straight -x-y (y wing) 0 | straight | yes | 443 | 12.5% | 443 | 12.5% |
| straight -x-y (x wing) 0 | straight | yes | 442 | 12.5% | 442 | 12.5% |
| corner -x-y | corner | **no** | 3 | 0.1% | 3 | 0.1% |
| straight +x-y (y wing) 0 | straight | yes | 439 | 12.4% | 439 | 12.4% |
| straight +x-y (x wing) 0 | straight | yes | 444 | 12.5% | 444 | 12.5% |
| corner +x-y | corner | **no** | 3 | 0.1% | 3 | 0.1% |
| **straight (8)** | | | 3530 | | 3530 | 99.7% |
| **corner (4)** | | | 12 | | 12 | 0.3% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 334 | 24.3 | 224.8 | 0.21 | 0.27 | 0.0% |
| -x | 325 | 24.5 | 219.5 | 0.21 | 0.25 | 0.0% |
| +y | 330 | 24.5 | 220.6 | 0.21 | 0.24 | 0.0% |
| -y | 337 | 24.5 | 222.1 | 0.22 | 0.29 | 0.0% |
| door +x+y y | 277 | 4.9 | 224.6 | 0.75 | 1.08 | 34.8% |
| door +x+y x | 276 | 4.9 | 221.1 | 0.76 | 1.02 | 43.5% |
| door -x+y y | 276 | 4.9 | 220.9 | 0.76 | 1.02 | 47.8% |
| door -x+y x | 278 | 4.9 | 213.9 | 0.79 | 1.02 | 40.9% |
| door -x-y y | 277 | 4.9 | 220.6 | 0.77 | 1.02 | 34.8% |
| door -x-y x | 282 | 4.9 | 223.4 | 0.77 | 1.02 | 52.2% |
| door +x-y y | 274 | 4.9 | 229.5 | 0.73 | 1.02 | 37.5% |
| door +x-y x | 276 | 4.9 | 232.1 | 0.73 | 1.02 | 33.3% |

Mean flow / w J averaged over the doors 0.76, over the avenues 0.21.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 443 | 277 / 166 / 43 | 0.7 | 221.6 | 2.20 | 2.81 | 78% | 78% | 0% | 3.66 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 437 | 276 / 161 / 48 | 0.7 | 218.1 | 2.23 | 3.21 | 82% | 82% | 0% | 3.69 |
| corner +x+y | 1.20 | 31.2 | 5 | 0 / 5 / 0 | 8.2 | 33.1 | 0.20 | 0.30 | 0% | 0% | 0% | nan |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 440 | 276 / 164 / 38 | 0.7 | 217.9 | 2.20 | 2.71 | 82% | 82% | 0% | 3.68 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 442 | 278 / 164 / 37 | 0.7 | 210.9 | 2.28 | 2.71 | 82% | 82% | 0% | 3.81 |
| corner -x+y | 1.20 | 31.2 | 1 | 0 / 1 / 0 | 8.4 | 29.2 | 0.05 | 0.10 | 0% | 0% | 0% | nan |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 443 | 277 / 166 / 54 | 0.7 | 217.6 | 2.29 | 3.11 | 82% | 82% | 0% | 3.76 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 442 | 282 / 160 / 57 | 0.7 | 220.4 | 2.27 | 3.41 | 78% | 78% | 0% | 3.71 |
| corner -x-y | 1.20 | 31.2 | 3 | 0 / 3 / 0 | 8.2 | 30.6 | 0.13 | 0.20 | 0% | 0% | 0% | nan |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 439 | 274 / 165 / 40 | 0.7 | 226.5 | 2.12 | 2.71 | 78% | 78% | 0% | 3.72 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 444 | 276 / 168 / 52 | 0.7 | 229.1 | 2.17 | 3.01 | 83% | 83% | 0% | 3.64 |
| corner +x-y | 1.20 | 31.2 | 3 | 0 / 3 / 0 | 8.2 | 32.0 | 0.13 | 0.20 | 0% | 0% | 0% | nan |

The last agent out (agent 3257, t100 232.1 s): last gangway straight +x-y (x wing) 0, exit door +x-y (x wall). The gangway that cleared last: straight +x-y (x wing) 0 at 229.1 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.61 | 225.5 / 215.3 / 176.5 | 203.2 / 192.6 / 121.0 | 37247.5 | 165439 | 0.337 |
| gangway | 392 | 351.5 | 6.61 | 218.5 / 200.8 / 152.5 | 203.2 / 192.6 / 121.0 | 37092.1 | 133503 | 0.115 |
| walkway | 276 | 257.4 | 1.95 | 34.5 / 0.0 / 0.0 | 8.0 / 0.0 / 0.0 | 0.0 | 7337 | 1.244 |
| avenue | 408 | 384.3 | 1.42 | 56.7 / 0.0 / 0.0 | 22.6 / 0.0 / 0.0 | 0.0 | 17237 | 1.319 |
| exit | 40 | 9.7 | 0.00 | 219.9 / 208.3 / 100.7 | 114.9 / 77.1 / 12.6 | 155.4 | 1522 | 1.321 |
| concourse | 612 | 609.0 | 1.77 | 174.0 / 0.0 / 0.0 | 36.6 / 0.0 / 0.0 | 0.0 | 5839 | 1.118 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.44 | 186.1 / 183.5 / 171.8 | 186.1 / 183.3 / 169.0 | 69881.3 | 228162 | 0.068 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -11.5 | -22.5 | gangway | 0.86 | 5.98 | 189.9 | 179.5 | 121.0 | 578.2 | 0.063 |
| 2 | 19.5 | 10.5 | gangway | 0.96 | 5.55 | 191.7 | 183.5 | 108.8 | 561.2 | 0.033 |
| 3 | -22.5 | -11.5 | gangway | 0.86 | 5.93 | 190.8 | 171.6 | 118.1 | 555.3 | 0.068 |
| 4 | -22.5 | 11.5 | gangway | 0.86 | 6.14 | 190.3 | 168.3 | 116.5 | 554.6 | 0.065 |
| 5 | 22.5 | -11.5 | gangway | 0.86 | 5.94 | 194.0 | 177.2 | 117.4 | 552.8 | 0.064 |
| 6 | 11.5 | -22.5 | gangway | 0.86 | 6.06 | 193.6 | 180.7 | 112.1 | 542.2 | 0.067 |
| 7 | 10.5 | 19.5 | gangway | 0.96 | 5.67 | 191.7 | 182.6 | 103.9 | 537.0 | 0.032 |
| 8 | -11.5 | 22.5 | gangway | 0.86 | 6.02 | 188.7 | 170.0 | 111.4 | 534.3 | 0.066 |
| 9 | 22.5 | -10.5 | gangway | 0.94 | 5.91 | 201.0 | 164.4 | 103.5 | 530.5 | 0.075 |
| 10 | 19.5 | 11.5 | gangway | 0.92 | 5.90 | 169.8 | 165.8 | 105.8 | 527.4 | 0.032 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 9.5 | -18.5 | seat row | 0.50 | 7.33 | 184.7 | 182.3 | 169.0 | 585.7 | 0.028 |
| 2 | -9.5 | 18.5 | seat row | 0.50 | 7.38 | 179.8 | 176.8 | 168.4 | 585.4 | 0.030 |
| 3 | 9.5 | 18.5 | seat row | 0.50 | 7.34 | 180.3 | 174.9 | 163.2 | 565.5 | 0.030 |
| 4 | -9.5 | -18.5 | seat row | 0.50 | 7.38 | 180.2 | 175.1 | 163.9 | 564.1 | 0.030 |
| 5 | -18.5 | 9.5 | seat row | 0.50 | 7.44 | 180.9 | 178.1 | 162.3 | 563.8 | 0.031 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 369; agent-steps of seated agents on another row's clearway: 2420.

## Deposit check

Person-seconds deposited: 393604.8, of them in excluded cells: 3.771.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 34363 overlapping pair-steps: p99 0.0034, max 0.0191 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0034 max 0.0191; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00751 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 4 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 1.95 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 83 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
