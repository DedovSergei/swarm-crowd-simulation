# Experiment `S_load95_s2`

**Task 5.10 stage 4 (AMD 26.10.1): Task 5.8's model (the level spacing on the gangway inclines, --stair-flow off): venue S, 95% load (seed 2)**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 3542 agents on 95% of the 3728 seats (spawnSeatedCrowd, seed 2), buffer N = 4096, 1023 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 102066 evaluations, 2809 switches, 0 forced choices).
Capacity: **within design capacity** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T20:45:03, 8.9 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 496 | 86.8 |
| t90 | 849 | 148.5 |
| t100 | 1023 | 178.9 |

t_p: the step by which ceil(p x 3542) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 320 | 0 | 24.0 | 174.4 | 22.5 | 24.5 | 38.8-48.8 |
| -x | 5.66 | 314 | 0 | 24.0 | 173.5 | 22.2 | 24.5 | 71.7-81.7 |
| +y | 5.66 | 319 | 0 | 24.0 | 174.9 | 22.4 | 24.5 | 78.7-88.7 |
| -y | 5.66 | 312 | 0 | 24.0 | 171.9 | 22.3 | 25.5 | 46.5-56.5 |
| door +x+y y | 1.20 | 289 | 450 | 4.9 | 177.2 | 83.8 | 105.3 | 20.6-30.6 |
| door +x+y x | 1.20 | 284 | 445 | 4.9 | 174.0 | 83.9 | 110.3 | 21.5-31.5 |
| door -x+y y | 1.20 | 285 | 446 | 4.9 | 178.2 | 82.1 | 105.3 | 19.8-29.7 |
| door -x+y x | 1.20 | 288 | 444 | 4.9 | 174.6 | 84.8 | 115.3 | 30.8-40.8 |
| door -x-y y | 1.20 | 280 | 437 | 4.9 | 178.2 | 80.7 | 110.3 | 16.1-26.1 |
| door -x-y x | 1.20 | 281 | 439 | 4.9 | 178.9 | 80.7 | 110.3 | 36.7-46.7 |
| door +x-y y | 1.20 | 282 | 434 | 4.9 | 172.8 | 83.9 | 115.3 | 23.6-33.6 |
| door +x-y x | 1.20 | 288 | 447 | 4.9 | 171.4 | 86.4 | 110.3 | 15.4-25.4 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 320 | 9.0% | 22.7% |
| -x | avenue | 5.66 | 314 | 8.9% | 22.3% |
| +y | avenue | 5.66 | 319 | 9.0% | 22.6% |
| -y | avenue | 5.66 | 312 | 8.8% | 22.1% |
| door +x+y y | door | 1.20 | 289 | 8.2% | 96.6% |
| door +x+y x | door | 1.20 | 284 | 8.0% | 94.9% |
| door -x+y y | door | 1.20 | 285 | 8.0% | 95.3% |
| door -x+y x | door | 1.20 | 288 | 8.1% | 96.3% |
| door -x-y y | door | 1.20 | 280 | 7.9% | 93.6% |
| door -x-y x | door | 1.20 | 281 | 7.9% | 93.9% |
| door +x-y y | door | 1.20 | 282 | 8.0% | 94.3% |
| door +x-y x | door | 1.20 | 288 | 8.1% | 96.3% |
| **doors (8)** | door | 9.60 | 2277 | 64.3% | |
| **avenues (4)** | avenue | 22.64 | 1265 | 35.7% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 178.9 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 44.1%.

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
| +x | 320 | 24.0 | 174.4 | 0.27 | 0.29 | 0.0% |
| -x | 314 | 24.0 | 173.5 | 0.27 | 0.29 | 0.0% |
| +y | 319 | 24.0 | 174.9 | 0.27 | 0.29 | 0.0% |
| -y | 312 | 24.0 | 171.9 | 0.27 | 0.31 | 0.0% |
| door +x+y y | 289 | 4.9 | 177.2 | 1.00 | 1.26 | 83.3% |
| door +x+y x | 284 | 4.9 | 174.0 | 1.00 | 1.32 | 77.8% |
| door -x+y y | 285 | 4.9 | 178.2 | 0.98 | 1.26 | 77.8% |
| door -x+y x | 288 | 4.9 | 174.6 | 1.01 | 1.38 | 77.8% |
| door -x-y y | 280 | 4.9 | 178.2 | 0.97 | 1.32 | 77.8% |
| door -x-y x | 281 | 4.9 | 178.9 | 0.96 | 1.32 | 77.8% |
| door +x-y y | 282 | 4.9 | 172.8 | 1.00 | 1.38 | 77.8% |
| door +x-y x | 288 | 4.9 | 171.4 | 1.03 | 1.32 | 77.8% |

Mean flow / w J averaged over the doors 1.00, over the avenues 0.27.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 449 | 289 / 160 / 43 | 0.7 | 174.2 | 2.83 | 3.81 | 78% | 78% | 0% | 4.02 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 444 | 284 / 160 / 45 | 0.7 | 171.1 | 2.87 | 3.61 | 78% | 78% | 0% | 4.06 |
| corner +x+y | 1.20 | 31.2 | 2 | 0 / 2 / 0 | 8.2 | 30.6 | 0.09 | 0.10 | 0% | 0% | 0% | nan |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 444 | 285 / 159 / 48 | 0.7 | 175.3 | 2.82 | 4.01 | 78% | 78% | 0% | 3.93 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 443 | 288 / 155 / 37 | 0.7 | 171.6 | 2.81 | 3.41 | 78% | 78% | 0% | 4.04 |
| corner -x+y | 1.20 | 31.2 | 3 | 0 / 3 / 0 | 8.2 | 30.6 | 0.13 | 0.20 | 0% | 0% | 0% | nan |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 436 | 280 / 156 / 43 | 0.7 | 175.3 | 2.74 | 3.51 | 72% | 72% | 0% | 4.07 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 437 | 281 / 156 / 29 | 0.7 | 176.0 | 2.66 | 3.51 | 72% | 72% | 0% | 4.02 |
| corner -x-y | 1.20 | 31.2 | 3 | 0 / 3 / 0 | 8.2 | 32.7 | 0.12 | 0.20 | 0% | 0% | 0% | nan |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 434 | 282 / 152 / 43 | 0.7 | 169.8 | 2.82 | 3.71 | 72% | 72% | 0% | 3.96 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 446 | 288 / 158 / 41 | 0.7 | 168.4 | 2.90 | 3.51 | 76% | 76% | 0% | 4.04 |
| corner +x-y | 1.20 | 31.2 | 1 | 0 / 1 / 0 | 8.4 | 29.0 | 0.05 | 0.10 | 0% | 0% | 0% | nan |

The last agent out (agent 2333, t100 178.9 s): last gangway straight -x-y (x wing) 0, exit door -x-y (x wall). The gangway that cleared last: straight -x-y (x wing) 0 at 176.0 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.41 | 177.0 / 171.8 / 139.2 | 157.1 / 150.1 / 96.2 | 24429.1 | 139044 | 0.394 |
| gangway | 392 | 351.5 | 6.41 | 173.9 / 151.6 / 120.7 | 157.1 / 150.1 / 96.2 | 24249.2 | 108026 | 0.147 |
| walkway | 276 | 257.4 | 1.91 | 82.9 / 0.0 / 0.0 | 19.1 / 0.0 / 0.0 | 0.0 | 6937 | 1.226 |
| avenue | 408 | 384.3 | 1.47 | 133.8 / 0.0 / 0.0 | 59.1 / 0.0 / 0.0 | 0.0 | 16451 | 1.318 |
| exit | 40 | 9.7 | 0.00 | 173.2 / 168.3 / 100.6 | 121.4 / 84.1 / 13.6 | 179.9 | 1547 | 1.293 |
| concourse | 612 | 609.0 | 2.02 | 155.7 / 0.0 / 0.0 | 92.4 / 0.0 / 0.0 | 0.0 | 6084 | 1.104 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.55 | 139.4 / 137.8 / 131.9 | 139.4 / 135.9 / 129.3 | 46654.2 | 169391 | 0.092 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -18.5 | 10.5 | gangway | 0.94 | 5.92 | 140.1 | 133.3 | 90.8 | 457.0 | 0.067 |
| 2 | -11.5 | 22.5 | gangway | 0.86 | 6.01 | 142.4 | 135.7 | 96.2 | 454.7 | 0.088 |
| 3 | -22.5 | 11.5 | gangway | 0.86 | 5.85 | 139.2 | 136.6 | 93.2 | 433.4 | 0.096 |
| 4 | 22.5 | 11.5 | gangway | 0.86 | 6.11 | 140.3 | 134.2 | 90.8 | 429.9 | 0.090 |
| 5 | -10.5 | 18.5 | gangway | 0.94 | 5.81 | 139.1 | 133.1 | 84.8 | 428.8 | 0.068 |
| 6 | -18.5 | -10.5 | gangway | 0.94 | 5.79 | 140.8 | 133.3 | 82.2 | 415.2 | 0.068 |
| 7 | -22.5 | -11.5 | gangway | 0.86 | 5.94 | 140.6 | 134.2 | 88.2 | 409.9 | 0.091 |
| 8 | -11.5 | 19.5 | gangway | 0.92 | 5.87 | 126.8 | 123.8 | 82.7 | 408.5 | 0.049 |
| 9 | 19.5 | 10.5 | gangway | 0.96 | 5.66 | 145.0 | 139.4 | 77.3 | 396.8 | 0.057 |
| 10 | 11.5 | 19.5 | gangway | 0.92 | 5.58 | 136.6 | 134.2 | 82.6 | 395.9 | 0.049 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 18.5 | -9.5 | seat row | 0.50 | 7.40 | 137.1 | 135.6 | 129.3 | 445.3 | 0.040 |
| 2 | -18.5 | -9.5 | seat row | 0.50 | 7.40 | 133.8 | 132.2 | 126.1 | 434.6 | 0.037 |
| 3 | 18.5 | 9.5 | seat row | 0.50 | 7.29 | 135.9 | 135.0 | 125.4 | 425.8 | 0.041 |
| 4 | -18.5 | 9.5 | seat row | 0.50 | 7.39 | 134.3 | 132.6 | 124.4 | 425.0 | 0.041 |
| 5 | 9.5 | 18.5 | seat row | 0.50 | 7.52 | 137.7 | 134.5 | 124.5 | 424.5 | 0.039 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 327; agent-steps of seated agents on another row's clearway: 3158.

## Deposit check

Person-seconds deposited: 308438.4, of them in excluded cells: 3.623.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 20182 overlapping pair-steps: p99 0.0058, max 0.0122 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0058 max 0.0122; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00761 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 1 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 2.02 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 124 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
