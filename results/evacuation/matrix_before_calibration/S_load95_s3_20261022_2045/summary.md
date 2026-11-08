# Experiment `S_load95_s3`

**Task 5.10 stage 4 (AMD 26.10.1): Task 5.8's model (the level spacing on the gangway inclines, --stair-flow off): venue S, 95% load (seed 3)**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 3542 agents on 95% of the 3728 seats (spawnSeatedCrowd, seed 3), buffer N = 4096, 1038 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 102047 evaluations, 2805 switches, 0 forced choices).
Capacity: **within design capacity** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T20:45:17, 8.3 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 496 | 86.8 |
| t90 | 848 | 148.3 |
| t100 | 1038 | 181.6 |

t_p: the step by which ceil(p x 3542) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 316 | 0 | 24.0 | 174.2 | 22.3 | 24.5 | 43.4-53.3 |
| -x | 5.66 | 316 | 0 | 24.0 | 171.4 | 22.7 | 25.5 | 50.9-60.9 |
| +y | 5.66 | 319 | 0 | 24.0 | 174.0 | 22.5 | 24.5 | 36.6-46.5 |
| -y | 5.66 | 320 | 0 | 24.0 | 172.3 | 22.8 | 26.6 | 49.5-59.5 |
| door +x+y y | 1.20 | 284 | 446 | 4.9 | 170.7 | 85.5 | 105.3 | 13.8-23.8 |
| door +x+y x | 1.20 | 283 | 439 | 4.9 | 175.6 | 82.8 | 110.3 | 16.4-26.4 |
| door -x+y y | 1.20 | 280 | 441 | 4.9 | 174.0 | 82.7 | 110.3 | 41.8-51.8 |
| door -x+y x | 1.20 | 286 | 442 | 4.9 | 178.8 | 82.2 | 110.3 | 58.4-68.4 |
| door -x-y y | 1.20 | 286 | 443 | 4.9 | 178.4 | 82.3 | 105.3 | 31.3-41.3 |
| door -x-y x | 1.20 | 283 | 445 | 4.9 | 171.2 | 85.0 | 110.3 | 17.0-26.9 |
| door +x-y y | 1.20 | 282 | 440 | 4.9 | 175.3 | 82.7 | 110.3 | 26.1-36.0 |
| door +x-y x | 1.20 | 287 | 446 | 4.9 | 181.6 | 81.2 | 110.3 | 27.5-37.4 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 316 | 8.9% | 22.1% |
| -x | avenue | 5.66 | 316 | 8.9% | 22.1% |
| +y | avenue | 5.66 | 319 | 9.0% | 22.3% |
| -y | avenue | 5.66 | 320 | 9.0% | 22.3% |
| door +x+y y | door | 1.20 | 284 | 8.0% | 93.6% |
| door +x+y x | door | 1.20 | 283 | 8.0% | 93.2% |
| door -x+y y | door | 1.20 | 280 | 7.9% | 92.2% |
| door -x+y x | door | 1.20 | 286 | 8.1% | 94.2% |
| door -x-y y | door | 1.20 | 286 | 8.1% | 94.2% |
| door -x-y x | door | 1.20 | 283 | 8.0% | 93.2% |
| door +x-y y | door | 1.20 | 282 | 8.0% | 92.9% |
| door +x-y x | door | 1.20 | 287 | 8.1% | 94.5% |
| **doors (8)** | door | 9.60 | 2271 | 64.1% | |
| **avenues (4)** | avenue | 22.64 | 1271 | 35.9% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 181.6 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 43.4%.

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
| +x | 316 | 24.0 | 174.2 | 0.27 | 0.29 | 0.0% |
| -x | 316 | 24.0 | 171.4 | 0.27 | 0.31 | 0.0% |
| +y | 319 | 24.0 | 174.0 | 0.27 | 0.29 | 0.0% |
| -y | 320 | 24.0 | 172.3 | 0.27 | 0.32 | 0.0% |
| door +x+y y | 284 | 4.9 | 170.7 | 1.02 | 1.26 | 77.8% |
| door +x+y x | 283 | 4.9 | 175.6 | 0.99 | 1.32 | 77.8% |
| door -x+y y | 280 | 4.9 | 174.0 | 0.99 | 1.32 | 77.8% |
| door -x+y x | 286 | 4.9 | 178.8 | 0.98 | 1.32 | 77.8% |
| door -x-y y | 286 | 4.9 | 178.4 | 0.98 | 1.26 | 77.8% |
| door -x-y x | 283 | 4.9 | 171.2 | 1.02 | 1.32 | 77.8% |
| door +x-y y | 282 | 4.9 | 175.3 | 0.99 | 1.32 | 77.8% |
| door +x-y x | 287 | 4.9 | 181.6 | 0.97 | 1.32 | 73.7% |

Mean flow / w J averaged over the doors 0.99, over the avenues 0.27.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 443 | 284 / 159 / 37 | 0.7 | 167.7 | 2.87 | 3.51 | 76% | 76% | 0% | 4.12 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 437 | 283 / 154 / 37 | 0.7 | 172.6 | 2.75 | 3.61 | 72% | 72% | 0% | 4.07 |
| corner +x+y | 1.20 | 31.2 | 5 | 0 / 5 / 0 | 8.2 | 32.0 | 0.21 | 0.30 | 0% | 0% | 0% | nan |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 440 | 280 / 160 / 42 | 0.7 | 171.1 | 2.83 | 3.81 | 72% | 72% | 0% | 4.06 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 442 | 286 / 156 / 39 | 0.7 | 175.8 | 2.74 | 3.81 | 72% | 72% | 0% | 4.06 |
| corner -x+y | 1.20 | 31.2 | 1 | 0 / 1 / 0 | 8.4 | 29.2 | 0.05 | 0.10 | 0% | 0% | 0% | nan |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 443 | 286 / 157 / 45 | 0.7 | 175.4 | 2.79 | 3.71 | 72% | 72% | 0% | 4.04 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 442 | 283 / 159 / 32 | 0.7 | 168.3 | 2.83 | 3.51 | 82% | 82% | 0% | 3.94 |
| corner -x-y | 1.20 | 31.2 | 3 | 0 / 3 / 0 | 8.2 | 30.6 | 0.13 | 0.20 | 0% | 0% | 0% | nan |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 439 | 282 / 157 / 48 | 0.7 | 172.3 | 2.84 | 3.71 | 72% | 72% | 0% | 4.07 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 444 | 287 / 157 / 34 | 0.7 | 178.6 | 2.68 | 3.41 | 78% | 78% | 0% | 3.93 |
| corner +x-y | 1.20 | 31.2 | 3 | 0 / 3 / 0 | 8.2 | 31.7 | 0.13 | 0.20 | 0% | 0% | 0% | nan |

The last agent out (agent 3232, t100 181.6 s): last gangway straight +x-y (x wing) 0, exit door +x-y (x wall). The gangway that cleared last: straight +x-y (x wing) 0 at 178.6 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.43 | 177.4 / 172.3 / 139.2 | 155.5 / 149.0 / 93.1 | 25176.4 | 138822 | 0.396 |
| gangway | 392 | 351.5 | 6.43 | 172.3 / 153.2 / 122.3 | 155.5 / 149.0 / 93.1 | 25006.8 | 107721 | 0.148 |
| walkway | 276 | 257.4 | 2.35 | 78.4 / 0.7 / 0.0 | 19.1 / 0.7 / 0.0 | 0.0 | 6989 | 1.223 |
| avenue | 408 | 384.3 | 1.56 | 132.2 / 0.0 / 0.0 | 60.2 / 0.0 / 0.0 | 0.0 | 16531 | 1.318 |
| exit | 40 | 9.7 | 0.00 | 173.2 / 168.4 / 94.1 | 120.5 / 85.0 / 12.6 | 169.6 | 1537 | 1.303 |
| concourse | 612 | 609.0 | 1.92 | 154.8 / 0.0 / 0.0 | 90.1 / 0.0 / 0.0 | 0.0 | 6044 | 1.108 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.59 | 139.9 / 138.0 / 134.9 | 139.9 / 138.0 / 132.2 | 47779.8 | 169534 | 0.092 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -10.5 | -18.5 | gangway | 0.94 | 5.79 | 140.1 | 135.0 | 89.0 | 445.5 | 0.071 |
| 2 | -11.5 | 19.5 | gangway | 0.92 | 5.52 | 132.4 | 126.8 | 93.1 | 445.4 | 0.049 |
| 3 | -18.5 | 10.5 | gangway | 0.94 | 5.80 | 139.6 | 130.8 | 87.5 | 435.3 | 0.066 |
| 4 | -11.5 | -22.5 | gangway | 0.86 | 6.03 | 139.2 | 134.2 | 91.3 | 432.5 | 0.088 |
| 5 | -11.5 | 22.5 | gangway | 0.86 | 6.43 | 142.5 | 136.8 | 90.1 | 431.7 | 0.089 |
| 6 | 18.5 | 10.5 | gangway | 0.94 | 6.02 | 138.4 | 131.5 | 84.1 | 421.9 | 0.068 |
| 7 | 10.5 | 18.5 | gangway | 0.94 | 5.62 | 141.8 | 134.2 | 84.3 | 419.2 | 0.070 |
| 8 | 22.5 | -11.5 | gangway | 0.86 | 6.17 | 141.0 | 134.2 | 87.5 | 415.5 | 0.091 |
| 9 | -22.5 | 11.5 | gangway | 0.86 | 6.08 | 138.5 | 127.2 | 87.3 | 411.3 | 0.093 |
| 10 | -18.5 | -10.5 | gangway | 0.94 | 5.89 | 140.1 | 131.5 | 80.5 | 406.8 | 0.062 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 18.5 | -9.5 | seat row | 0.50 | 7.26 | 139.9 | 138.0 | 132.2 | 447.1 | 0.039 |
| 2 | -18.5 | -9.5 | seat row | 0.50 | 7.50 | 135.7 | 133.6 | 126.8 | 440.4 | 0.040 |
| 3 | -9.5 | -18.5 | seat row | 0.50 | 7.24 | 137.3 | 135.6 | 126.8 | 433.4 | 0.039 |
| 4 | 18.5 | 9.5 | seat row | 0.50 | 7.52 | 133.3 | 132.2 | 126.5 | 432.2 | 0.038 |
| 5 | -9.5 | 18.5 | seat row | 0.50 | 7.42 | 137.0 | 135.4 | 126.5 | 430.2 | 0.040 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 313; agent-steps of seated agents on another row's clearway: 2941.

## Deposit check

Person-seconds deposited: 308359.8, of them in excluded cells: 3.833.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 23531 overlapping pair-steps: p99 0.0036, max 0.0079 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0036 max 0.0079; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00756 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 2 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 2.35 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 116 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
