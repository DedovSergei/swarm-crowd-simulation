# Experiment `S_load100`

**Task 5.10 stage 4 (AMD 26.10.1): Task 5.8's model (the level spacing on the gangway inclines, --stair-flow off): venue S, 100% load**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 3728 agents on 100% of the 3728 seats (spawnSeatedCrowd, seed 1337), buffer N = 4096, 1093 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 112708 evaluations, 2994 switches, 0 forced choices).
Capacity: **within design capacity** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T20:42:50, 63.7 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 521 | 91.1 |
| t90 | 890 | 155.7 |
| t100 | 1093 | 191.2 |

t_p: the step by which ceil(p x 3728) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 338 | 0 | 24.0 | 181.6 | 22.7 | 25.5 | 45.7-55.6 |
| -x | 5.66 | 335 | 0 | 24.0 | 179.6 | 22.8 | 25.5 | 48.1-58.1 |
| +y | 5.66 | 336 | 0 | 24.0 | 181.6 | 22.6 | 25.5 | 49.3-59.3 |
| -y | 5.66 | 335 | 0 | 24.0 | 183.0 | 22.3 | 26.6 | 47.2-57.2 |
| door +x+y y | 1.20 | 298 | 466 | 4.9 | 183.5 | 83.4 | 110.3 | 53.9-63.8 |
| door +x+y x | 1.20 | 297 | 466 | 4.9 | 179.8 | 84.8 | 110.3 | 30.1-40.1 |
| door -x+y y | 1.20 | 298 | 466 | 4.9 | 184.0 | 83.1 | 110.3 | 45.8-55.8 |
| door -x+y x | 1.20 | 298 | 466 | 4.9 | 184.4 | 82.9 | 110.3 | 46.0-56.0 |
| door -x-y y | 1.20 | 298 | 466 | 4.9 | 191.2 | 79.9 | 105.3 | 13.8-23.8 |
| door -x-y x | 1.20 | 299 | 466 | 4.9 | 184.9 | 83.0 | 110.3 | 50.2-60.2 |
| door +x-y y | 1.20 | 299 | 466 | 4.9 | 180.5 | 85.0 | 110.3 | 46.4-56.3 |
| door +x-y x | 1.20 | 297 | 466 | 4.9 | 180.3 | 84.6 | 110.3 | 26.1-36.0 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 338 | 9.1% | 22.4% |
| -x | avenue | 5.66 | 335 | 9.0% | 22.2% |
| +y | avenue | 5.66 | 336 | 9.0% | 22.3% |
| -y | avenue | 5.66 | 335 | 9.0% | 22.2% |
| door +x+y y | door | 1.20 | 298 | 8.0% | 93.2% |
| door +x+y x | door | 1.20 | 297 | 8.0% | 92.9% |
| door -x+y y | door | 1.20 | 298 | 8.0% | 93.2% |
| door -x+y x | door | 1.20 | 298 | 8.0% | 93.2% |
| door -x-y y | door | 1.20 | 298 | 8.0% | 93.2% |
| door -x-y x | door | 1.20 | 299 | 8.0% | 93.5% |
| door +x-y y | door | 1.20 | 299 | 8.0% | 93.5% |
| door +x-y x | door | 1.20 | 297 | 8.0% | 92.9% |
| **doors (8)** | door | 9.60 | 2384 | 63.9% | |
| **avenues (4)** | avenue | 22.64 | 1344 | 36.1% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 191.2 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 43.4%.

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
| +x | 338 | 24.0 | 181.6 | 0.27 | 0.31 | 0.0% |
| -x | 335 | 24.0 | 179.6 | 0.27 | 0.31 | 0.0% |
| +y | 336 | 24.0 | 181.6 | 0.27 | 0.31 | 0.0% |
| -y | 335 | 24.0 | 183.0 | 0.27 | 0.32 | 0.0% |
| door +x+y y | 298 | 4.9 | 183.5 | 1.00 | 1.32 | 78.9% |
| door +x+y x | 297 | 4.9 | 179.8 | 1.01 | 1.32 | 78.9% |
| door -x+y y | 298 | 4.9 | 184.0 | 0.99 | 1.32 | 78.9% |
| door -x+y x | 298 | 4.9 | 184.4 | 0.99 | 1.32 | 78.9% |
| door -x-y y | 298 | 4.9 | 191.2 | 0.96 | 1.26 | 75.0% |
| door -x-y x | 299 | 4.9 | 184.9 | 0.99 | 1.32 | 78.9% |
| door +x-y y | 299 | 4.9 | 180.5 | 1.02 | 1.32 | 78.9% |
| door +x-y x | 297 | 4.9 | 180.3 | 1.01 | 1.32 | 78.9% |

Mean flow / w J averaged over the doors 1.00, over the avenues 0.27.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 464 | 298 / 166 / 41 | 0.7 | 180.5 | 2.81 | 3.61 | 74% | 74% | 0% | 4.11 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 464 | 297 / 167 / 42 | 0.7 | 176.8 | 2.87 | 3.51 | 78% | 78% | 0% | 4.05 |
| corner +x+y | 1.20 | 31.2 | 4 | 0 / 4 / 0 | 8.2 | 30.6 | 0.18 | 0.20 | 0% | 0% | 0% | nan |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 464 | 298 / 166 / 55 | 0.7 | 181.0 | 2.88 | 3.61 | 74% | 74% | 0% | 4.05 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 464 | 298 / 166 / 46 | 0.7 | 181.4 | 2.82 | 3.51 | 74% | 74% | 0% | 4.02 |
| corner -x+y | 1.20 | 31.2 | 4 | 0 / 4 / 0 | 8.2 | 30.6 | 0.18 | 0.20 | 0% | 0% | 0% | nan |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 464 | 298 / 166 / 34 | 0.7 | 188.2 | 2.65 | 3.51 | 74% | 74% | 0% | 4.07 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 464 | 299 / 165 / 40 | 0.7 | 181.9 | 2.78 | 3.61 | 74% | 74% | 0% | 4.10 |
| corner -x-y | 1.20 | 31.2 | 4 | 0 / 4 / 0 | 8.2 | 30.6 | 0.18 | 0.20 | 0% | 0% | 0% | nan |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 464 | 299 / 165 / 44 | 0.7 | 177.7 | 2.87 | 3.91 | 78% | 78% | 0% | 4.08 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 464 | 297 / 167 / 44 | 0.7 | 177.4 | 2.87 | 3.61 | 78% | 78% | 0% | 4.09 |
| corner +x-y | 1.20 | 31.2 | 4 | 0 / 4 / 0 | 8.2 | 30.6 | 0.18 | 0.20 | 0% | 0% | 0% | nan |

The last agent out (agent 2062, t100 191.2 s): last gangway straight -x-y (y wing) 0, exit door -x-y (y wall). The gangway that cleared last: straight -x-y (y wing) 0 at 188.2 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.09 | 188.0 / 178.4 / 145.7 | 165.8 / 159.0 / 100.6 | 27084.4 | 147653 | 0.393 |
| gangway | 392 | 351.5 | 6.09 | 185.9 / 161.4 / 130.3 | 165.8 / 159.0 / 100.6 | 26900.0 | 114806 | 0.146 |
| walkway | 276 | 257.4 | 1.96 | 81.2 / 0.0 / 0.0 | 21.9 / 0.0 / 0.0 | 0.0 | 7390 | 1.222 |
| avenue | 408 | 384.3 | 1.45 | 136.1 / 0.0 / 0.0 | 61.0 / 0.0 / 0.0 | 0.0 | 17481 | 1.318 |
| exit | 40 | 9.7 | 0.00 | 178.4 / 169.0 / 94.8 | 124.2 / 87.5 / 13.5 | 184.4 | 1626 | 1.300 |
| concourse | 612 | 609.0 | 2.04 | 159.2 / 0.0 / 0.0 | 93.9 / 0.0 / 0.0 | 0.0 | 6349 | 1.108 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.56 | 147.4 / 146.2 / 141.8 | 147.3 / 146.2 / 139.2 | 56280.0 | 192717 | 0.085 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 10.5 | -18.5 | gangway | 0.94 | 5.77 | 149.2 | 142.2 | 95.3 | 477.3 | 0.063 |
| 2 | -11.5 | -22.5 | gangway | 0.86 | 6.03 | 151.5 | 145.3 | 100.6 | 477.0 | 0.089 |
| 3 | -11.5 | 22.5 | gangway | 0.86 | 5.99 | 146.0 | 143.8 | 97.6 | 463.7 | 0.088 |
| 4 | -22.5 | 11.5 | gangway | 0.86 | 6.01 | 148.8 | 146.2 | 95.3 | 452.0 | 0.089 |
| 5 | 22.5 | -11.5 | gangway | 0.86 | 6.01 | 143.8 | 141.7 | 95.7 | 450.0 | 0.090 |
| 6 | -10.5 | 18.5 | gangway | 0.94 | 5.76 | 149.4 | 141.5 | 89.9 | 450.0 | 0.067 |
| 7 | -10.5 | -18.5 | gangway | 0.94 | 5.90 | 151.8 | 144.1 | 88.5 | 445.9 | 0.067 |
| 8 | -18.5 | 10.5 | gangway | 0.94 | 6.03 | 148.0 | 141.1 | 87.5 | 444.0 | 0.064 |
| 9 | 10.5 | 18.5 | gangway | 0.94 | 5.77 | 149.9 | 143.6 | 88.5 | 443.7 | 0.068 |
| 10 | -18.5 | -10.5 | gangway | 0.94 | 5.97 | 149.7 | 141.0 | 89.4 | 440.9 | 0.068 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 18.5 | -9.5 | seat row | 0.50 | 7.42 | 147.3 | 146.2 | 139.2 | 476.2 | 0.037 |
| 2 | 9.5 | 18.5 | seat row | 0.50 | 7.47 | 144.8 | 143.8 | 137.5 | 472.2 | 0.038 |
| 3 | -18.5 | 9.5 | seat row | 0.50 | 7.45 | 143.6 | 142.9 | 136.1 | 467.7 | 0.039 |
| 4 | 9.5 | -18.5 | seat row | 0.50 | 7.38 | 145.2 | 144.1 | 135.4 | 466.3 | 0.038 |
| 5 | -9.5 | 18.5 | seat row | 0.50 | 7.40 | 143.6 | 143.1 | 135.9 | 466.1 | 0.038 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 341; agent-steps of seated agents on another row's clearway: 3303.

## Deposit check

Person-seconds deposited: 340373.7, of them in excluded cells: 4.186.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 30683 overlapping pair-steps: p99 0.0044, max 0.0105 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0044 max 0.0105; venue-geometry 1: p99 0.0003 max 0.0003 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00754 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 1 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 2.04 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 128 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
