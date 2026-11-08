# Experiment `S_load95_s2`

**Task 5.8 stage 2: venue S, 95% load (seed 2), default model**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 3542 agents on 95% of the 3728 seats (spawnSeatedCrowd, seed 2), buffer N = 4096, 1022 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 102201 evaluations, 2809 switches, 0 forced choices).
Capacity: **within design capacity** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `cd8e0bbf3411846ca7aa6719887d122a142a7ca1`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-15T16:20:12, 8.6 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 496 | 86.8 |
| t90 | 849 | 148.5 |
| t100 | 1022 | 178.8 |

t_p: the step by which ceil(p x 3542) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 316 | 0 | 24.0 | 174.2 | 22.3 | 24.5 | 43.7-53.7 |
| -x | 5.66 | 320 | 0 | 24.0 | 173.2 | 22.7 | 24.5 | 40.2-50.2 |
| +y | 5.66 | 320 | 0 | 24.0 | 174.2 | 22.6 | 24.5 | 33.6-43.6 |
| -y | 5.66 | 317 | 0 | 24.0 | 171.4 | 22.8 | 25.5 | 50.4-60.3 |
| door +x+y y | 1.20 | 289 | 450 | 4.9 | 177.5 | 83.6 | 115.3 | 50.0-60.0 |
| door +x+y x | 1.20 | 289 | 445 | 4.9 | 171.8 | 86.5 | 115.3 | 55.1-65.1 |
| door -x+y y | 1.20 | 284 | 446 | 4.9 | 178.8 | 81.6 | 110.3 | 31.3-41.3 |
| door -x+y x | 1.20 | 284 | 444 | 4.9 | 178.1 | 81.9 | 110.3 | 25.2-35.2 |
| door -x-y y | 1.20 | 279 | 437 | 4.9 | 174.7 | 82.1 | 110.3 | 53.9-63.8 |
| door -x-y x | 1.20 | 279 | 439 | 4.9 | 167.6 | 85.7 | 110.3 | 44.4-54.4 |
| door +x-y y | 1.20 | 278 | 434 | 4.9 | 175.8 | 81.3 | 110.3 | 12.2-22.2 |
| door +x-y x | 1.20 | 287 | 447 | 4.9 | 173.9 | 84.8 | 110.3 | 43.0-53.0 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 316 | 8.9% | 22.4% |
| -x | avenue | 5.66 | 320 | 9.0% | 22.7% |
| +y | avenue | 5.66 | 320 | 9.0% | 22.7% |
| -y | avenue | 5.66 | 317 | 8.9% | 22.5% |
| door +x+y y | door | 1.20 | 289 | 8.2% | 96.7% |
| door +x+y x | door | 1.20 | 289 | 8.2% | 96.7% |
| door -x+y y | door | 1.20 | 284 | 8.0% | 95.0% |
| door -x+y x | door | 1.20 | 284 | 8.0% | 95.0% |
| door -x-y y | door | 1.20 | 279 | 7.9% | 93.3% |
| door -x-y x | door | 1.20 | 279 | 7.9% | 93.3% |
| door +x-y y | door | 1.20 | 278 | 7.8% | 93.0% |
| door +x-y x | door | 1.20 | 287 | 8.1% | 96.0% |
| **doors (8)** | door | 9.60 | 2269 | 64.1% | |
| **avenues (4)** | avenue | 22.64 | 1273 | 35.9% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 178.8 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 44.1%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 449 | 12.7% | 449 | 12.7% |
| straight +x+y (x wing) 0 | straight | yes | 444 | 12.5% | 444 | 12.5% |
| corner +x+y | corner | **no** | 2 | 0.1% | 2 | 0.1% |
| straight -x+y (y wing) 0 | straight | yes | 444 | 12.5% | 444 | 12.5% |
| straight -x+y (x wing) 0 | straight | yes | 443 | 12.5% | 443 | 12.5% |
| corner -x+y | corner | **no** | 3 | 0.1% | 3 | 0.1% |
| straight -x-y (y wing) 0 | straight | yes | 436 | 12.3% | 436 | 12.3% |
| straight -x-y (x wing) 0 | straight | yes | 437 | 12.3% | 437 | 12.3% |
| corner -x-y | corner | **no** | 3 | 0.1% | 3 | 0.1% |
| straight +x-y (y wing) 0 | straight | yes | 434 | 12.3% | 434 | 12.3% |
| straight +x-y (x wing) 0 | straight | yes | 446 | 12.6% | 446 | 12.6% |
| corner +x-y | corner | **no** | 1 | 0.0% | 1 | 0.0% |
| **straight (8)** | | | 3533 | | 3533 | 99.7% |
| **corner (4)** | | | 9 | | 9 | 0.3% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 316 | 24.0 | 174.2 | 0.27 | 0.29 | 0.0% |
| -x | 320 | 24.0 | 173.2 | 0.27 | 0.29 | 0.0% |
| +y | 320 | 24.0 | 174.2 | 0.27 | 0.29 | 0.0% |
| -y | 317 | 24.0 | 171.4 | 0.27 | 0.31 | 0.0% |
| door +x+y y | 289 | 4.9 | 177.5 | 1.00 | 1.38 | 77.8% |
| door +x+y x | 289 | 4.9 | 171.8 | 1.03 | 1.38 | 77.8% |
| door -x+y y | 284 | 4.9 | 178.8 | 0.98 | 1.32 | 77.8% |
| door -x+y x | 284 | 4.9 | 178.1 | 0.98 | 1.32 | 77.8% |
| door -x-y y | 279 | 4.9 | 174.7 | 0.98 | 1.32 | 77.8% |
| door -x-y x | 279 | 4.9 | 167.6 | 1.02 | 1.32 | 82.4% |
| door +x-y y | 278 | 4.9 | 175.8 | 0.97 | 1.32 | 77.8% |
| door +x-y x | 287 | 4.9 | 173.9 | 1.01 | 1.32 | 77.8% |

Mean flow / w J averaged over the doors 1.00, over the avenues 0.27.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 449 | 289 / 160 / 39 | 0.7 | 174.6 | 2.80 | 3.61 | 78% | 78% | 0% | 4.01 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 444 | 289 / 155 / 37 | 0.7 | 168.8 | 2.86 | 3.71 | 76% | 76% | 0% | 4.09 |
| corner +x+y | 1.20 | 31.2 | 2 | 0 / 2 / 0 | 8.2 | 30.6 | 0.09 | 0.10 | 0% | 0% | 0% | nan |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 444 | 284 / 160 / 51 | 0.7 | 175.8 | 2.82 | 3.91 | 78% | 78% | 0% | 3.98 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 443 | 284 / 159 / 40 | 0.7 | 175.1 | 2.77 | 3.61 | 78% | 78% | 0% | 4.05 |
| corner -x+y | 1.20 | 31.2 | 3 | 0 / 3 / 0 | 8.2 | 30.6 | 0.13 | 0.20 | 0% | 0% | 0% | nan |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 436 | 279 / 157 / 37 | 0.7 | 171.8 | 2.76 | 3.71 | 78% | 78% | 0% | 3.99 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 437 | 279 / 158 / 36 | 0.7 | 164.6 | 2.88 | 3.51 | 76% | 76% | 0% | 4.06 |
| corner -x-y | 1.20 | 31.2 | 3 | 0 / 3 / 0 | 8.2 | 32.4 | 0.12 | 0.20 | 0% | 0% | 0% | nan |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 434 | 278 / 156 / 42 | 0.7 | 172.8 | 2.76 | 3.91 | 72% | 72% | 0% | 4.01 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 446 | 287 / 159 / 42 | 0.7 | 170.9 | 2.86 | 3.71 | 72% | 72% | 0% | 4.08 |
| corner +x-y | 1.20 | 31.2 | 1 | 0 / 1 / 0 | 8.4 | 29.0 | 0.05 | 0.10 | 0% | 0% | 0% | nan |

The last agent out (agent 1083, t100 178.8 s): last gangway straight -x+y (y wing) 0, exit door -x+y (y wall). The gangway that cleared last: straight -x+y (y wing) 0 at 175.8 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.25 | 178.1 / 172.8 / 139.6 | 156.5 / 151.5 / 94.4 | 25384.0 | 139427 | 0.394 |
| gangway | 392 | 351.5 | 6.25 | 174.0 / 151.5 / 123.3 | 156.5 / 151.5 / 94.4 | 25201.7 | 108297 | 0.147 |
| walkway | 276 | 257.4 | 1.76 | 78.4 / 0.0 / 0.0 | 19.2 / 0.0 / 0.0 | 0.0 | 6989 | 1.225 |
| avenue | 408 | 384.3 | 1.53 | 133.1 / 0.0 / 0.0 | 59.5 / 0.0 / 0.0 | 0.0 | 16556 | 1.318 |
| exit | 40 | 9.7 | 0.00 | 173.7 / 169.1 / 101.4 | 116.7 / 81.5 / 14.3 | 182.3 | 1542 | 1.300 |
| concourse | 612 | 609.0 | 2.04 | 155.3 / 0.0 / 0.0 | 94.6 / 0.0 / 0.0 | 0.0 | 6044 | 1.107 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.51 | 140.3 / 137.8 / 133.5 | 140.3 / 137.8 / 130.8 | 47523.9 | 169481 | 0.092 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -18.5 | 10.5 | gangway | 0.94 | 5.76 | 143.9 | 133.6 | 94.4 | 470.4 | 0.064 |
| 2 | -22.5 | 11.5 | gangway | 0.86 | 6.07 | 142.2 | 136.6 | 89.6 | 435.2 | 0.086 |
| 3 | 11.5 | 19.5 | gangway | 0.92 | 5.83 | 135.0 | 127.7 | 87.6 | 433.5 | 0.051 |
| 4 | 11.5 | 22.5 | gangway | 0.86 | 5.89 | 143.1 | 138.4 | 89.9 | 417.5 | 0.094 |
| 5 | 10.5 | 18.5 | gangway | 0.94 | 5.68 | 144.6 | 134.2 | 84.0 | 416.0 | 0.064 |
| 6 | 10.5 | -18.5 | gangway | 0.94 | 5.80 | 139.4 | 129.6 | 81.9 | 409.0 | 0.071 |
| 7 | 18.5 | 10.5 | gangway | 0.94 | 5.72 | 141.8 | 132.2 | 81.5 | 405.5 | 0.065 |
| 8 | -11.5 | 22.5 | gangway | 0.86 | 6.09 | 141.0 | 135.9 | 84.8 | 400.1 | 0.089 |
| 9 | -10.5 | -19.5 | gangway | 0.96 | 5.77 | 142.0 | 124.9 | 77.5 | 394.5 | 0.059 |
| 10 | -10.5 | -18.5 | gangway | 0.94 | 5.89 | 141.5 | 134.2 | 78.2 | 394.0 | 0.069 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 18.5 | -9.5 | seat row | 0.50 | 7.51 | 137.7 | 136.1 | 130.8 | 447.0 | 0.041 |
| 2 | 9.5 | 18.5 | seat row | 0.50 | 7.43 | 138.5 | 135.9 | 129.4 | 444.1 | 0.038 |
| 3 | 18.5 | 9.5 | seat row | 0.50 | 7.35 | 137.0 | 136.4 | 127.9 | 442.5 | 0.039 |
| 4 | 9.5 | -18.5 | seat row | 0.50 | 7.39 | 134.3 | 133.6 | 125.9 | 431.0 | 0.040 |
| 5 | -18.5 | 9.5 | seat row | 0.50 | 7.39 | 137.7 | 135.7 | 121.6 | 419.2 | 0.041 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 324; agent-steps of seated agents on another row's clearway: 2774.

## Deposit check

Person-seconds deposited: 308911.7, of them in excluded cells: 3.925.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 19593 overlapping pair-steps: p99 0.0045, max 0.0102 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0045 max 0.0102; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 3 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 2.04 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 124 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
