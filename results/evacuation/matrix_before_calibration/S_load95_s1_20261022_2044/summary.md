# Experiment `S_load95_s1`

**Task 5.10 stage 4 (AMD 26.10.1): Task 5.8's model (the level spacing on the gangway inclines, --stair-flow off): venue S, 95% load (seed 1)**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 3542 agents on 95% of the 3728 seats (spawnSeatedCrowd, seed 1), buffer N = 4096, 1042 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 102615 evaluations, 2799 switches, 0 forced choices).
Capacity: **within design capacity** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T20:44:48, 9.6 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 499 | 87.3 |
| t90 | 852 | 149.0 |
| t100 | 1042 | 182.3 |

t_p: the step by which ceil(p x 3542) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 315 | 0 | 24.0 | 172.5 | 22.5 | 24.5 | 57.4-67.3 |
| -x | 5.66 | 319 | 0 | 24.0 | 172.5 | 22.7 | 25.5 | 50.7-60.7 |
| +y | 5.66 | 321 | 0 | 24.0 | 175.4 | 22.4 | 25.5 | 50.2-60.2 |
| -y | 5.66 | 314 | 0 | 24.0 | 172.8 | 22.3 | 24.5 | 45.5-55.4 |
| door +x+y y | 1.20 | 287 | 445 | 4.9 | 177.9 | 82.9 | 110.3 | 26.2-36.2 |
| door +x+y x | 1.20 | 283 | 440 | 4.9 | 177.7 | 81.8 | 110.3 | 42.3-52.3 |
| door -x+y y | 1.20 | 283 | 445 | 4.9 | 182.3 | 79.7 | 105.3 | 14.3-24.3 |
| door -x+y x | 1.20 | 278 | 436 | 4.9 | 174.9 | 81.7 | 105.3 | 16.3-26.2 |
| door -x-y y | 1.20 | 285 | 439 | 4.9 | 177.0 | 82.7 | 105.3 | 8.2-18.2 |
| door -x-y x | 1.20 | 285 | 445 | 4.9 | 179.5 | 81.6 | 110.3 | 53.9-63.8 |
| door +x-y y | 1.20 | 282 | 442 | 4.9 | 177.9 | 81.4 | 115.3 | 48.4-58.4 |
| door +x-y x | 1.20 | 290 | 450 | 4.9 | 178.9 | 83.2 | 115.3 | 39.7-49.7 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 315 | 8.9% | 21.9% |
| -x | avenue | 5.66 | 319 | 9.0% | 22.2% |
| +y | avenue | 5.66 | 321 | 9.1% | 22.3% |
| -y | avenue | 5.66 | 314 | 8.9% | 21.8% |
| door +x+y y | door | 1.20 | 287 | 8.1% | 94.2% |
| door +x+y x | door | 1.20 | 283 | 8.0% | 92.9% |
| door -x+y y | door | 1.20 | 283 | 8.0% | 92.9% |
| door -x+y x | door | 1.20 | 278 | 7.8% | 91.2% |
| door -x-y y | door | 1.20 | 285 | 8.0% | 93.5% |
| door -x-y x | door | 1.20 | 285 | 8.0% | 93.5% |
| door +x-y y | door | 1.20 | 282 | 8.0% | 92.5% |
| door +x-y x | door | 1.20 | 290 | 8.2% | 95.2% |
| **doors (8)** | door | 9.60 | 2273 | 64.2% | |
| **avenues (4)** | avenue | 22.64 | 1269 | 35.8% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 182.3 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 43.3%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 444 | 12.5% | 444 | 12.5% |
| straight +x+y (x wing) 0 | straight | yes | 439 | 12.4% | 439 | 12.4% |
| corner +x+y | corner | **no** | 2 | 0.1% | 2 | 0.1% |
| straight -x+y (y wing) 0 | straight | yes | 444 | 12.5% | 444 | 12.5% |
| straight -x+y (x wing) 0 | straight | yes | 435 | 12.3% | 435 | 12.3% |
| corner -x+y | corner | **no** | 2 | 0.1% | 2 | 0.1% |
| straight -x-y (y wing) 0 | straight | yes | 438 | 12.4% | 438 | 12.4% |
| straight -x-y (x wing) 0 | straight | yes | 445 | 12.6% | 445 | 12.6% |
| corner -x-y | corner | **no** | 1 | 0.0% | 1 | 0.0% |
| straight +x-y (y wing) 0 | straight | yes | 440 | 12.4% | 440 | 12.4% |
| straight +x-y (x wing) 0 | straight | yes | 449 | 12.7% | 449 | 12.7% |
| corner +x-y | corner | **no** | 3 | 0.1% | 3 | 0.1% |
| **straight (8)** | | | 3534 | | 3534 | 99.8% |
| **corner (4)** | | | 8 | | 8 | 0.2% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 315 | 24.0 | 172.5 | 0.27 | 0.29 | 0.0% |
| -x | 319 | 24.0 | 172.5 | 0.27 | 0.31 | 0.0% |
| +y | 321 | 24.0 | 175.4 | 0.27 | 0.31 | 0.0% |
| -y | 314 | 24.0 | 172.8 | 0.27 | 0.29 | 0.0% |
| door +x+y y | 287 | 4.9 | 177.9 | 0.99 | 1.32 | 77.8% |
| door +x+y x | 283 | 4.9 | 177.7 | 0.98 | 1.32 | 77.8% |
| door -x+y y | 283 | 4.9 | 182.3 | 0.95 | 1.26 | 78.9% |
| door -x+y x | 278 | 4.9 | 174.9 | 0.98 | 1.26 | 77.8% |
| door -x-y y | 285 | 4.9 | 177.0 | 0.99 | 1.26 | 77.8% |
| door -x-y x | 285 | 4.9 | 179.5 | 0.98 | 1.32 | 77.8% |
| door +x-y y | 282 | 4.9 | 177.9 | 0.97 | 1.38 | 77.8% |
| door +x-y x | 290 | 4.9 | 178.9 | 1.00 | 1.38 | 77.8% |

Mean flow / w J averaged over the doors 0.98, over the avenues 0.27.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 444 | 287 / 157 / 38 | 0.7 | 174.9 | 2.76 | 3.51 | 72% | 72% | 0% | 4.09 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 439 | 283 / 156 / 26 | 0.7 | 174.7 | 2.67 | 3.71 | 78% | 78% | 0% | 3.91 |
| corner +x+y | 1.20 | 31.2 | 2 | 0 / 2 / 0 | 8.2 | 30.6 | 0.09 | 0.10 | 0% | 0% | 0% | nan |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 444 | 283 / 161 / 42 | 0.7 | 179.3 | 2.72 | 3.51 | 78% | 78% | 0% | 4.04 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 435 | 278 / 157 / 40 | 0.7 | 172.1 | 2.77 | 3.61 | 72% | 72% | 0% | 4.06 |
| corner -x+y | 1.20 | 31.2 | 2 | 0 / 2 / 0 | 8.2 | 30.6 | 0.09 | 0.10 | 0% | 0% | 0% | nan |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 438 | 285 / 153 / 32 | 0.7 | 174.0 | 2.71 | 3.51 | 72% | 72% | 0% | 4.01 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 445 | 285 / 160 / 41 | 0.7 | 176.5 | 2.76 | 3.71 | 78% | 78% | 0% | 3.89 |
| corner -x-y | 1.20 | 31.2 | 1 | 0 / 1 / 0 | 8.2 | 30.6 | 0.04 | 0.10 | 0% | 0% | 0% | nan |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 440 | 282 / 158 / 36 | 0.7 | 174.9 | 2.73 | 3.71 | 72% | 72% | 0% | 4.06 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 449 | 290 / 159 / 43 | 0.7 | 176.0 | 2.80 | 3.51 | 78% | 78% | 0% | 4.02 |
| corner +x-y | 1.20 | 31.2 | 3 | 0 / 3 / 0 | 8.2 | 31.7 | 0.13 | 0.20 | 0% | 0% | 0% | nan |

The last agent out (agent 1021, t100 182.3 s): last gangway straight -x+y (y wing) 0, exit door -x+y (y wall). The gangway that cleared last: straight -x+y (y wing) 0 at 179.3 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.29 | 180.9 / 173.3 / 138.2 | 158.1 / 152.0 / 94.6 | 24997.2 | 139260 | 0.395 |
| gangway | 392 | 351.5 | 6.29 | 178.1 / 153.9 / 118.6 | 158.1 / 152.0 / 94.6 | 24827.4 | 108210 | 0.148 |
| walkway | 276 | 257.4 | 2.04 | 84.7 / 0.0 / 0.0 | 19.4 / 0.0 / 0.0 | 0.0 | 6954 | 1.225 |
| avenue | 408 | 384.3 | 1.55 | 136.6 / 0.0 / 0.0 | 51.9 / 0.0 / 0.0 | 0.0 | 16503 | 1.318 |
| exit | 40 | 9.7 | 0.00 | 177.0 / 170.0 / 97.6 | 121.6 / 83.4 / 12.8 | 169.7 | 1544 | 1.301 |
| concourse | 612 | 609.0 | 2.00 | 155.8 / 0.0 / 0.0 | 90.4 / 0.0 / 0.0 | 0.0 | 6049 | 1.108 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.53 | 144.1 / 143.2 / 132.9 | 144.1 / 143.2 / 130.1 | 48716.3 | 170761 | 0.092 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -10.5 | -18.5 | gangway | 0.94 | 5.82 | 139.2 | 128.9 | 87.6 | 441.1 | 0.065 |
| 2 | -22.5 | -11.5 | gangway | 0.86 | 6.04 | 143.8 | 140.3 | 94.6 | 439.8 | 0.094 |
| 3 | -10.5 | 18.5 | gangway | 0.94 | 5.99 | 142.5 | 136.1 | 85.5 | 435.5 | 0.068 |
| 4 | -22.5 | 11.5 | gangway | 0.86 | 6.04 | 137.8 | 135.7 | 88.3 | 418.1 | 0.086 |
| 5 | -11.5 | 19.5 | gangway | 0.92 | 5.74 | 125.9 | 122.8 | 84.0 | 416.7 | 0.052 |
| 6 | 10.5 | -18.5 | gangway | 0.94 | 5.61 | 139.1 | 133.6 | 83.6 | 415.2 | 0.072 |
| 7 | 10.5 | 19.5 | gangway | 0.96 | 5.79 | 143.1 | 126.8 | 81.0 | 414.2 | 0.060 |
| 8 | 19.5 | 11.5 | gangway | 0.92 | 5.58 | 125.8 | 122.3 | 85.0 | 411.2 | 0.050 |
| 9 | 11.5 | 22.5 | gangway | 0.86 | 6.04 | 139.6 | 135.7 | 85.4 | 408.1 | 0.090 |
| 10 | -11.5 | 18.5 | gangway | 0.86 | 6.29 | 133.8 | 129.4 | 85.2 | 402.4 | 0.070 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 18.5 | 9.5 | seat row | 0.50 | 7.38 | 138.2 | 137.0 | 130.1 | 444.9 | 0.039 |
| 2 | -9.5 | 18.5 | seat row | 0.50 | 7.44 | 138.0 | 137.3 | 128.4 | 443.9 | 0.038 |
| 3 | 18.5 | -9.5 | seat row | 0.50 | 7.51 | 138.0 | 137.1 | 129.4 | 441.6 | 0.040 |
| 4 | -18.5 | -9.5 | seat row | 0.50 | 7.22 | 137.5 | 134.7 | 126.1 | 431.2 | 0.037 |
| 5 | -9.5 | -18.5 | seat row | 0.50 | 7.53 | 136.3 | 135.0 | 124.7 | 424.4 | 0.041 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 297; agent-steps of seated agents on another row's clearway: 2777.

## Deposit check

Person-seconds deposited: 310025.1, of them in excluded cells: 3.970.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 20013 overlapping pair-steps: p99 0.0038, max 0.0084 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0038 max 0.0084; venue-geometry 1: p99 0.0001 max 0.0001 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 6 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 2.04 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 105 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
