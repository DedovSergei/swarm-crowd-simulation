# Experiment `S_load95_s3`

**Task 5.8 stage 2: venue S, 95% load (seed 3), default model**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 3542 agents on 95% of the 3728 seats (spawnSeatedCrowd, seed 3), buffer N = 4096, 1027 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 102633 evaluations, 2799 switches, 0 forced choices).
Capacity: **within design capacity** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `cd8e0bbf3411846ca7aa6719887d122a142a7ca1`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-15T16:20:24, 8.9 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 500 | 87.5 |
| t90 | 851 | 148.8 |
| t100 | 1027 | 179.6 |

t_p: the step by which ceil(p x 3542) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 320 | 0 | 24.0 | 171.8 | 22.9 | 25.5 | 113.2-123.1 |
| -x | 5.66 | 321 | 0 | 24.0 | 174.4 | 22.6 | 25.5 | 58.4-68.4 |
| +y | 5.66 | 317 | 0 | 24.0 | 173.9 | 22.4 | 24.5 | 53.2-63.1 |
| -y | 5.66 | 323 | 0 | 24.0 | 173.2 | 22.9 | 25.5 | 45.1-55.1 |
| door +x+y y | 1.20 | 284 | 446 | 4.9 | 178.9 | 81.5 | 105.3 | 29.9-39.9 |
| door +x+y x | 1.20 | 280 | 439 | 4.9 | 174.6 | 82.4 | 110.3 | 51.2-61.2 |
| door -x+y y | 1.20 | 282 | 441 | 4.9 | 171.9 | 84.3 | 110.3 | 20.5-30.4 |
| door -x+y x | 1.20 | 283 | 442 | 4.9 | 174.7 | 83.2 | 110.3 | 14.5-24.5 |
| door -x-y y | 1.20 | 284 | 443 | 4.9 | 179.6 | 81.2 | 105.3 | 18.5-28.5 |
| door -x-y x | 1.20 | 281 | 445 | 4.9 | 177.7 | 81.2 | 110.3 | 45.1-55.1 |
| door +x-y y | 1.20 | 281 | 440 | 4.9 | 174.6 | 82.7 | 110.3 | 27.5-37.4 |
| door +x-y x | 1.20 | 286 | 446 | 4.9 | 172.8 | 85.1 | 115.3 | 20.5-30.4 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 320 | 9.0% | 22.6% |
| -x | avenue | 5.66 | 321 | 9.1% | 22.7% |
| +y | avenue | 5.66 | 317 | 8.9% | 22.4% |
| -y | avenue | 5.66 | 323 | 9.1% | 22.8% |
| door +x+y y | door | 1.20 | 284 | 8.0% | 94.6% |
| door +x+y x | door | 1.20 | 280 | 7.9% | 93.2% |
| door -x+y y | door | 1.20 | 282 | 8.0% | 93.9% |
| door -x+y x | door | 1.20 | 283 | 8.0% | 94.2% |
| door -x-y y | door | 1.20 | 284 | 8.0% | 94.6% |
| door -x-y x | door | 1.20 | 281 | 7.9% | 93.6% |
| door +x-y y | door | 1.20 | 281 | 7.9% | 93.6% |
| door +x-y x | door | 1.20 | 286 | 8.1% | 95.2% |
| **doors (8)** | door | 9.60 | 2261 | 63.8% | |
| **avenues (4)** | avenue | 22.64 | 1281 | 36.2% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 179.6 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 43.9%.

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
| +x | 320 | 24.0 | 171.8 | 0.27 | 0.31 | 0.0% |
| -x | 321 | 24.0 | 174.4 | 0.27 | 0.31 | 0.0% |
| +y | 317 | 24.0 | 173.9 | 0.27 | 0.29 | 0.0% |
| -y | 323 | 24.0 | 173.2 | 0.27 | 0.31 | 0.0% |
| door +x+y y | 284 | 4.9 | 178.9 | 0.98 | 1.26 | 77.8% |
| door +x+y x | 280 | 4.9 | 174.6 | 0.99 | 1.32 | 77.8% |
| door -x+y y | 282 | 4.9 | 171.9 | 1.01 | 1.32 | 77.8% |
| door -x+y x | 283 | 4.9 | 174.7 | 1.00 | 1.32 | 77.8% |
| door -x-y y | 284 | 4.9 | 179.6 | 0.97 | 1.26 | 78.9% |
| door -x-y x | 281 | 4.9 | 177.7 | 0.97 | 1.32 | 77.8% |
| door +x-y y | 281 | 4.9 | 174.6 | 0.99 | 1.32 | 77.8% |
| door +x-y x | 286 | 4.9 | 172.8 | 1.02 | 1.38 | 77.8% |

Mean flow / w J averaged over the doors 0.99, over the avenues 0.27.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 443 | 284 / 159 / 39 | 0.7 | 176.0 | 2.75 | 3.71 | 72% | 72% | 0% | 4.02 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 437 | 280 / 157 / 45 | 0.7 | 171.6 | 2.82 | 3.61 | 72% | 72% | 0% | 4.02 |
| corner +x+y | 1.20 | 31.2 | 5 | 0 / 5 / 0 | 8.2 | 32.0 | 0.21 | 0.30 | 0% | 0% | 0% | nan |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 440 | 282 / 158 / 36 | 0.7 | 169.0 | 2.83 | 3.51 | 76% | 76% | 0% | 4.12 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 442 | 283 / 159 / 34 | 0.7 | 171.8 | 2.78 | 3.41 | 78% | 78% | 0% | 3.98 |
| corner -x+y | 1.20 | 31.2 | 1 | 0 / 1 / 0 | 8.4 | 29.2 | 0.05 | 0.10 | 0% | 0% | 0% | nan |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 443 | 284 / 159 / 46 | 0.7 | 176.7 | 2.78 | 3.91 | 78% | 78% | 0% | 3.99 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 442 | 281 / 161 / 53 | 0.7 | 174.7 | 2.84 | 3.81 | 78% | 78% | 0% | 3.96 |
| corner -x-y | 1.20 | 31.2 | 3 | 0 / 3 / 0 | 8.2 | 30.6 | 0.13 | 0.20 | 0% | 0% | 0% | nan |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 439 | 281 / 158 / 45 | 0.7 | 171.6 | 2.83 | 3.91 | 78% | 78% | 0% | 3.96 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 444 | 286 / 158 / 46 | 0.7 | 169.8 | 2.89 | 3.61 | 72% | 72% | 0% | 4.15 |
| corner +x-y | 1.20 | 31.2 | 3 | 0 / 3 / 0 | 8.2 | 31.7 | 0.13 | 0.20 | 0% | 0% | 0% | nan |

The last agent out (agent 1876, t100 179.6 s): last gangway straight -x-y (y wing) 0, exit door -x-y (y wall). The gangway that cleared last: straight -x-y (y wing) 0 at 176.7 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.48 | 178.6 / 170.0 / 141.0 | 157.4 / 152.5 / 91.5 | 24912.9 | 139924 | 0.394 |
| gangway | 392 | 351.5 | 6.48 | 175.4 / 152.5 / 122.1 | 157.4 / 152.5 / 91.5 | 24747.3 | 108626 | 0.147 |
| walkway | 276 | 257.4 | 2.29 | 79.4 / 0.9 / 0.0 | 19.1 / 0.9 / 0.0 | 0.0 | 7061 | 1.220 |
| avenue | 408 | 384.3 | 1.65 | 132.6 / 0.0 / 0.0 | 66.6 / 0.0 / 0.0 | 0.0 | 16663 | 1.317 |
| exit | 40 | 9.7 | 0.00 | 173.2 / 166.0 / 97.2 | 120.3 / 82.0 / 13.1 | 165.6 | 1543 | 1.298 |
| concourse | 612 | 609.0 | 1.96 | 155.8 / 0.0 / 0.0 | 90.1 / 0.0 / 0.0 | 0.0 | 6031 | 1.106 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.56 | 138.9 / 137.0 / 131.5 | 138.9 / 137.0 / 128.9 | 47721.3 | 170167 | 0.092 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 18.5 | 10.5 | gangway | 0.94 | 5.76 | 138.2 | 132.8 | 90.1 | 442.9 | 0.067 |
| 2 | 10.5 | -18.5 | gangway | 0.94 | 5.83 | 140.6 | 132.9 | 86.4 | 434.6 | 0.068 |
| 3 | 11.5 | -22.5 | gangway | 0.86 | 6.00 | 142.0 | 137.8 | 91.0 | 432.9 | 0.091 |
| 4 | 22.5 | 11.5 | gangway | 0.86 | 6.05 | 140.3 | 136.3 | 91.5 | 432.0 | 0.088 |
| 5 | 22.5 | -11.5 | gangway | 0.86 | 6.15 | 139.1 | 134.9 | 85.4 | 411.0 | 0.087 |
| 6 | -11.5 | -22.5 | gangway | 0.86 | 6.19 | 143.4 | 139.9 | 85.2 | 411.0 | 0.083 |
| 7 | -18.5 | 10.5 | gangway | 0.94 | 5.99 | 138.5 | 131.7 | 79.9 | 404.8 | 0.064 |
| 8 | -11.5 | 22.5 | gangway | 0.86 | 5.83 | 138.4 | 135.2 | 84.3 | 396.9 | 0.092 |
| 9 | -22.5 | -11.5 | gangway | 0.86 | 5.90 | 144.3 | 141.0 | 86.9 | 395.8 | 0.085 |
| 10 | 11.5 | 22.5 | gangway | 0.86 | 5.96 | 141.3 | 134.9 | 84.1 | 395.6 | 0.091 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 9.5 | 18.5 | seat row | 0.50 | 7.39 | 136.4 | 135.7 | 128.9 | 442.4 | 0.040 |
| 2 | -18.5 | -9.5 | seat row | 0.50 | 7.56 | 136.6 | 135.4 | 128.4 | 438.4 | 0.041 |
| 3 | -9.5 | 18.5 | seat row | 0.50 | 7.39 | 134.9 | 134.3 | 125.1 | 431.8 | 0.040 |
| 4 | -9.5 | -18.5 | seat row | 0.50 | 7.34 | 135.7 | 134.2 | 126.5 | 431.3 | 0.039 |
| 5 | 9.5 | -18.5 | seat row | 0.50 | 7.52 | 134.9 | 131.4 | 122.8 | 426.5 | 0.038 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 344; agent-steps of seated agents on another row's clearway: 2976.

## Deposit check

Person-seconds deposited: 310094.7, of them in excluded cells: 3.842.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 18420 overlapping pair-steps: p99 0.0046, max 0.0111 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0046 max 0.0111; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00753 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 1 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 2.29 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 110 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
