# Experiment `S_load100`

**Task 5.8 stage 2: venue S, 100% load, default model**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 3728 agents on 100% of the 3728 seats (spawnSeatedCrowd, seed 1337), buffer N = 4096, 1089 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 112645 evaluations, 3010 switches, 0 forced choices).
Capacity: **within design capacity** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `cd8e0bbf3411846ca7aa6719887d122a142a7ca1`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-15T16:19:45, 9.4 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 520 | 91.0 |
| t90 | 892 | 156.0 |
| t100 | 1089 | 190.5 |

t_p: the step by which ceil(p x 3728) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 335 | 0 | 24.0 | 181.4 | 22.5 | 25.5 | 43.9-53.9 |
| -x | 5.66 | 340 | 0 | 24.0 | 183.0 | 22.6 | 25.5 | 46.4-56.3 |
| +y | 5.66 | 334 | 0 | 24.0 | 181.0 | 22.5 | 25.5 | 48.3-58.2 |
| -y | 5.66 | 333 | 0 | 24.0 | 179.6 | 22.7 | 25.5 | 47.9-57.9 |
| door +x+y y | 1.20 | 300 | 466 | 4.9 | 184.7 | 83.3 | 110.3 | 54.9-64.9 |
| door +x+y x | 1.20 | 300 | 466 | 4.9 | 185.2 | 83.1 | 110.3 | 14.5-24.5 |
| door -x+y y | 1.20 | 298 | 466 | 4.9 | 183.1 | 83.5 | 110.3 | 14.3-24.3 |
| door -x+y x | 1.20 | 296 | 466 | 4.9 | 190.5 | 79.7 | 110.3 | 15.4-25.4 |
| door -x-y y | 1.20 | 300 | 466 | 4.9 | 188.4 | 81.7 | 110.3 | 15.4-25.4 |
| door -x-y x | 1.20 | 296 | 466 | 4.9 | 183.0 | 83.0 | 105.3 | 14.5-24.5 |
| door +x-y y | 1.20 | 299 | 466 | 4.9 | 184.0 | 83.4 | 110.3 | 31.5-41.5 |
| door +x-y x | 1.20 | 297 | 466 | 4.9 | 180.5 | 84.5 | 115.3 | 47.4-57.4 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 335 | 9.0% | 22.3% |
| -x | avenue | 5.66 | 340 | 9.1% | 22.6% |
| +y | avenue | 5.66 | 334 | 9.0% | 22.2% |
| -y | avenue | 5.66 | 333 | 8.9% | 22.2% |
| door +x+y y | door | 1.20 | 300 | 8.0% | 94.2% |
| door +x+y x | door | 1.20 | 300 | 8.0% | 94.2% |
| door -x+y y | door | 1.20 | 298 | 8.0% | 93.6% |
| door -x+y x | door | 1.20 | 296 | 7.9% | 92.9% |
| door -x-y y | door | 1.20 | 300 | 8.0% | 94.2% |
| door -x-y x | door | 1.20 | 296 | 7.9% | 92.9% |
| door +x-y y | door | 1.20 | 299 | 8.0% | 93.9% |
| door +x-y x | door | 1.20 | 297 | 8.0% | 93.3% |
| **doors (8)** | door | 9.60 | 2386 | 64.0% | |
| **avenues (4)** | avenue | 22.64 | 1342 | 36.0% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 190.5 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 43.6%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 464 | 12.4% | 464 | 12.4% |
| straight +x+y (x wing) 0 | straight | yes | 464 | 12.4% | 464 | 12.4% |
| corner +x+y | corner | **no** | 4 | 0.1% | 4 | 0.1% |
| straight -x+y (y wing) 0 | straight | yes | 464 | 12.4% | 464 | 12.4% |
| straight -x+y (x wing) 0 | straight | yes | 464 | 12.4% | 464 | 12.4% |
| corner -x+y | corner | **no** | 4 | 0.1% | 4 | 0.1% |
| straight -x-y (y wing) 0 | straight | yes | 464 | 12.4% | 464 | 12.4% |
| straight -x-y (x wing) 0 | straight | yes | 464 | 12.4% | 464 | 12.4% |
| corner -x-y | corner | **no** | 4 | 0.1% | 4 | 0.1% |
| straight +x-y (y wing) 0 | straight | yes | 464 | 12.4% | 464 | 12.4% |
| straight +x-y (x wing) 0 | straight | yes | 464 | 12.4% | 464 | 12.4% |
| corner +x-y | corner | **no** | 4 | 0.1% | 4 | 0.1% |
| **straight (8)** | | | 3712 | | 3712 | 99.6% |
| **corner (4)** | | | 16 | | 16 | 0.4% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 335 | 24.0 | 181.4 | 0.27 | 0.31 | 0.0% |
| -x | 340 | 24.0 | 183.0 | 0.27 | 0.31 | 0.0% |
| +y | 334 | 24.0 | 181.0 | 0.27 | 0.31 | 0.0% |
| -y | 333 | 24.0 | 179.6 | 0.27 | 0.31 | 0.0% |
| door +x+y y | 300 | 4.9 | 184.7 | 1.00 | 1.32 | 78.9% |
| door +x+y x | 300 | 4.9 | 185.2 | 0.99 | 1.32 | 78.9% |
| door -x+y y | 298 | 4.9 | 183.1 | 1.00 | 1.32 | 78.9% |
| door -x+y x | 296 | 4.9 | 190.5 | 0.95 | 1.32 | 75.0% |
| door -x-y y | 300 | 4.9 | 188.4 | 0.98 | 1.32 | 78.9% |
| door -x-y x | 296 | 4.9 | 183.0 | 0.99 | 1.26 | 78.9% |
| door +x-y y | 299 | 4.9 | 184.0 | 1.00 | 1.32 | 78.9% |
| door +x-y x | 297 | 4.9 | 180.5 | 1.01 | 1.38 | 78.9% |

Mean flow / w J averaged over the doors 0.99, over the avenues 0.27.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 464 | 300 / 164 / 40 | 0.7 | 181.7 | 2.78 | 3.51 | 74% | 74% | 0% | 4.08 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 464 | 300 / 164 / 44 | 0.7 | 182.3 | 2.80 | 3.61 | 74% | 74% | 0% | 3.98 |
| corner +x+y | 1.20 | 31.2 | 4 | 0 / 4 / 0 | 8.2 | 30.6 | 0.18 | 0.20 | 0% | 0% | 0% | nan |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 464 | 298 / 166 / 44 | 0.7 | 180.2 | 2.83 | 3.51 | 74% | 74% | 0% | 4.02 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 464 | 296 / 168 / 41 | 0.7 | 187.5 | 2.70 | 3.61 | 74% | 74% | 0% | 4.12 |
| corner -x+y | 1.20 | 31.2 | 4 | 0 / 4 / 0 | 8.2 | 30.6 | 0.18 | 0.20 | 0% | 0% | 0% | nan |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 464 | 300 / 165 / 47 | 0.7 | 185.4 | 2.77 | 3.51 | 74% | 74% | 0% | 4.02 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 464 | 296 / 168 / 42 | 0.7 | 180.0 | 2.82 | 3.61 | 79% | 79% | 0% | 3.97 |
| corner -x-y | 1.20 | 31.2 | 4 | 0 / 4 / 0 | 8.2 | 30.6 | 0.18 | 0.20 | 0% | 0% | 0% | nan |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 464 | 299 / 165 / 52 | 0.7 | 181.0 | 2.86 | 3.61 | 74% | 74% | 0% | 4.04 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 464 | 297 / 167 / 43 | 0.7 | 177.5 | 2.86 | 3.61 | 78% | 78% | 0% | 4.02 |
| corner +x-y | 1.20 | 31.2 | 4 | 0 / 4 / 0 | 8.2 | 30.6 | 0.18 | 0.20 | 0% | 0% | 0% | nan |

The last agent out (agent 1539, t100 190.5 s): last gangway straight -x+y (x wing) 0, exit door -x+y (x wall). The gangway that cleared last: straight -x+y (x wing) 0 at 187.5 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.22 | 186.8 / 179.3 / 146.2 | 165.1 / 157.4 / 97.4 | 27290.8 | 147353 | 0.394 |
| gangway | 392 | 351.5 | 6.22 | 183.7 / 160.4 / 125.9 | 165.1 / 157.4 / 97.4 | 27104.5 | 114518 | 0.147 |
| walkway | 276 | 257.4 | 2.12 | 86.4 / 0.0 / 0.0 | 23.4 / 0.0 / 0.0 | 0.0 | 7384 | 1.222 |
| avenue | 408 | 384.3 | 1.64 | 133.8 / 0.0 / 0.0 | 59.5 / 0.0 / 0.0 | 0.0 | 17454 | 1.318 |
| exit | 40 | 9.7 | 0.00 | 180.9 / 172.5 / 101.3 | 127.2 / 88.0 / 13.3 | 186.4 | 1625 | 1.297 |
| concourse | 612 | 609.0 | 1.99 | 159.9 / 0.0 / 0.0 | 90.6 / 0.0 / 0.0 | 0.0 | 6371 | 1.105 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.52 | 149.4 / 148.3 / 143.8 | 149.4 / 148.3 / 141.1 | 56986.0 | 192817 | 0.085 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -22.5 | 11.5 | gangway | 0.86 | 6.04 | 150.8 | 148.1 | 97.4 | 467.8 | 0.085 |
| 2 | -22.5 | -11.5 | gangway | 0.86 | 6.21 | 148.5 | 146.2 | 95.0 | 457.6 | 0.084 |
| 3 | 11.5 | 22.5 | gangway | 0.86 | 6.10 | 146.4 | 143.6 | 93.7 | 450.8 | 0.089 |
| 4 | 18.5 | 10.5 | gangway | 0.94 | 5.74 | 149.5 | 141.0 | 89.2 | 446.2 | 0.069 |
| 5 | -18.5 | 10.5 | gangway | 0.94 | 5.75 | 150.6 | 143.4 | 87.8 | 442.8 | 0.070 |
| 6 | -19.5 | 11.5 | gangway | 0.92 | 5.93 | 135.7 | 130.5 | 89.0 | 442.2 | 0.049 |
| 7 | 19.5 | -10.5 | gangway | 0.96 | 5.57 | 152.0 | 139.2 | 84.7 | 433.4 | 0.060 |
| 8 | 18.5 | -10.5 | gangway | 0.94 | 5.84 | 149.0 | 140.5 | 85.0 | 425.5 | 0.066 |
| 9 | 10.5 | -18.5 | gangway | 0.94 | 5.75 | 149.7 | 141.1 | 84.1 | 421.2 | 0.066 |
| 10 | -18.5 | -10.5 | gangway | 0.94 | 5.79 | 153.4 | 143.8 | 82.6 | 413.3 | 0.065 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -18.5 | -9.5 | seat row | 0.50 | 7.42 | 149.4 | 148.3 | 141.1 | 488.6 | 0.037 |
| 2 | 18.5 | -9.5 | seat row | 0.50 | 7.50 | 145.7 | 143.8 | 138.7 | 477.5 | 0.038 |
| 3 | 9.5 | -18.5 | seat row | 0.50 | 7.52 | 144.8 | 143.8 | 138.4 | 477.3 | 0.038 |
| 4 | -18.5 | 9.5 | seat row | 0.50 | 7.41 | 145.7 | 145.2 | 136.6 | 474.7 | 0.038 |
| 5 | -9.5 | 18.5 | seat row | 0.50 | 7.44 | 144.6 | 143.9 | 137.7 | 473.9 | 0.037 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 352; agent-steps of seated agents on another row's clearway: 3515.

## Deposit check

Person-seconds deposited: 340174.0, of them in excluded cells: 4.064.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 30799 overlapping pair-steps: p99 0.0041, max 0.0094 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0041 max 0.0094; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00758 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 1 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 2.12 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 133 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
