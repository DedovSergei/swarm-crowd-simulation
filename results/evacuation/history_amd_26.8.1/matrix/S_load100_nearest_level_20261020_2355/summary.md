# Experiment `S_load100_nearest_level`

**Task 5.9 stage 4 (model variants): venue S, 100% load, nearest exit, level walking speed**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 3728 agents on 100% of the 3728 seats (spawnSeatedCrowd, seed 1337), buffer N = 4096, 1150 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **nearest exit, level speed**.
Capacity: **within design capacity** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-20T23:55:20, 15.5 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 568 | 99.3 |
| t90 | 999 | 174.7 |
| t100 | 1150 | 201.1 |

t_p: the step by which ceil(p x 3728) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| -x | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| +y | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| -y | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| door +x+y y | 1.20 | 466 | 466 | 4.2 | 199.9 | 118.9 | 145.4 | 102.7-112.6 |
| door +x+y x | 1.20 | 466 | 466 | 4.2 | 197.5 | 120.4 | 150.5 | 88.9-98.8 |
| door -x+y y | 1.20 | 466 | 466 | 4.2 | 201.1 | 118.2 | 140.4 | 34.3-44.3 |
| door -x+y x | 1.20 | 466 | 466 | 4.2 | 199.4 | 119.3 | 145.4 | 29.6-39.5 |
| door -x-y y | 1.20 | 466 | 466 | 4.2 | 195.7 | 121.5 | 150.5 | 61.6-71.5 |
| door -x-y x | 1.20 | 466 | 466 | 4.2 | 197.1 | 120.7 | 145.4 | 68.7-78.7 |
| door +x-y y | 1.20 | 466 | 466 | 4.2 | 197.6 | 120.3 | 145.4 | 44.6-54.6 |
| door +x-y x | 1.20 | 466 | 466 | 4.2 | 195.5 | 121.7 | 145.4 | 54.6-64.5 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 0 | 0.0% | 0.0% |
| -x | avenue | 5.66 | 0 | 0.0% | 0.0% |
| +y | avenue | 5.66 | 0 | 0.0% | 0.0% |
| -y | avenue | 5.66 | 0 | 0.0% | 0.0% |
| door +x+y y | door | 1.20 | 466 | 12.5% | 138.6% |
| door +x+y x | door | 1.20 | 466 | 12.5% | 138.6% |
| door -x+y y | door | 1.20 | 466 | 12.5% | 138.6% |
| door -x+y x | door | 1.20 | 466 | 12.5% | 138.6% |
| door -x-y y | door | 1.20 | 466 | 12.5% | 138.6% |
| door -x-y x | door | 1.20 | 466 | 12.5% | 138.6% |
| door +x-y y | door | 1.20 | 466 | 12.5% | 138.6% |
| door +x-y x | door | 1.20 | 466 | 12.5% | 138.6% |
| **doors (8)** | door | 9.60 | 3728 | 100.0% | |
| **avenues (4)** | avenue | 22.64 | 0 | 0.0% | |

**Unused exit width: 22.6 of 32.2 m (70.2%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 201.1 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 41.3%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 466 | 12.5% | 466 | 12.5% |
| straight +x+y (x wing) 0 | straight | yes | 466 | 12.5% | 466 | 12.5% |
| corner +x+y | corner | **no** | 0 | 0.0% | 0 | 0.0% |
| straight -x+y (y wing) 0 | straight | yes | 466 | 12.5% | 466 | 12.5% |
| straight -x+y (x wing) 0 | straight | yes | 466 | 12.5% | 466 | 12.5% |
| corner -x+y | corner | **no** | 0 | 0.0% | 0 | 0.0% |
| straight -x-y (y wing) 0 | straight | yes | 466 | 12.5% | 466 | 12.5% |
| straight -x-y (x wing) 0 | straight | yes | 466 | 12.5% | 466 | 12.5% |
| corner -x-y | corner | **no** | 0 | 0.0% | 0 | 0.0% |
| straight +x-y (y wing) 0 | straight | yes | 466 | 12.5% | 466 | 12.5% |
| straight +x-y (x wing) 0 | straight | yes | 466 | 12.5% | 466 | 12.5% |
| corner +x-y | corner | **no** | 0 | 0.0% | 0 | 0.0% |
| **straight (8)** | | | 3728 | | 3728 | 100.0% |
| **corner (4)** | | | 0 | | 0 | 0.0% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| door +x+y y | 466 | 4.2 | 199.9 | 1.42 | 1.74 | 95.2% |
| door +x+y x | 466 | 4.2 | 197.5 | 1.44 | 1.80 | 95.0% |
| door -x+y y | 466 | 4.2 | 201.1 | 1.41 | 1.68 | 90.5% |
| door -x+y x | 466 | 4.2 | 199.4 | 1.43 | 1.74 | 100.0% |
| door -x-y y | 466 | 4.2 | 195.7 | 1.45 | 1.80 | 95.0% |
| door -x-y x | 466 | 4.2 | 197.1 | 1.44 | 1.74 | 95.0% |
| door +x-y y | 466 | 4.2 | 197.6 | 1.44 | 1.74 | 95.0% |
| door +x-y x | 466 | 4.2 | 195.5 | 1.46 | 1.74 | 95.0% |

Mean flow / w J averaged over the doors 1.44, over the avenues nan.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 466 | 466 / 0 / 0 | 0.7 | 197.3 | 2.37 | 2.81 | 90% | 80% | 10% | 3.61 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 466 | 466 / 0 / 0 | 0.7 | 194.8 | 2.40 | 2.71 | 90% | 80% | 10% | 3.54 |
| corner +x+y | 1.20 | 31.2 | 0 | 0 / 0 / 0 | - | - | nan | nan | nan% | nan% | nan% | nan |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 466 | 466 / 0 / 0 | 0.7 | 198.5 | 2.35 | 2.61 | 90% | 80% | 10% | 3.70 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 466 | 466 / 0 / 0 | 0.7 | 196.8 | 2.37 | 2.71 | 90% | 80% | 10% | 3.56 |
| corner -x+y | 1.20 | 31.2 | 0 | 0 / 0 / 0 | - | - | nan | nan | nan% | nan% | nan% | nan |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 466 | 466 / 0 / 0 | 0.7 | 193.1 | 2.42 | 2.81 | 90% | 80% | 10% | 3.65 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 466 | 466 / 0 / 0 | 0.7 | 194.5 | 2.40 | 2.81 | 90% | 80% | 10% | 3.75 |
| corner -x-y | 1.20 | 31.2 | 0 | 0 / 0 / 0 | - | - | nan | nan | nan% | nan% | nan% | nan |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 466 | 466 / 0 / 0 | 0.7 | 195.0 | 2.40 | 2.81 | 90% | 80% | 10% | 3.61 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 466 | 466 / 0 / 0 | 0.7 | 192.9 | 2.42 | 2.71 | 90% | 80% | 10% | 3.68 |
| corner +x-y | 1.20 | 31.2 | 0 | 0 / 0 / 0 | - | - | nan | nan | nan% | nan% | nan% | nan |

The last agent out (agent 963, t100 201.1 s): last gangway straight -x+y (y wing) 0, exit -. The gangway that cleared last: straight -x+y (y wing) 0 at 198.5 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.64 | 200.4 / 199.2 / 176.7 | 189.2 / 185.4 / 139.9 | 59685.7 | 137109 | 0.269 |
| gangway | 392 | 351.5 | 6.64 | 192.0 / 185.6 / 154.4 | 189.2 / 185.4 / 139.9 | 59358.5 | 126214 | 0.188 |
| walkway | 276 | 257.4 | 0.08 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 11 | 0.015 |
| avenue | 408 | 384.3 | 0.17 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 5 | 0.142 |
| exit | 40 | 9.7 | 0.00 | 197.3 / 196.1 / 141.3 | 174.2 / 126.8 / 22.9 | 327.1 | 1597 | 1.257 |
| concourse | 612 | 609.0 | 2.77 | 191.2 / 29.0 / 0.0 | 114.2 / 6.3 / 0.0 | 0.0 | 9281 | 1.204 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.63 | 187.2 / 186.1 / 178.1 | 187.2 / 186.1 / 174.9 | 71181.3 | 231136 | 0.063 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -10.5 | 16.5 | gangway | 0.96 | 5.66 | 189.2 | 177.4 | 139.9 | 728.5 | 0.058 |
| 2 | -10.5 | -16.5 | gangway | 0.96 | 5.62 | 184.5 | 177.4 | 139.8 | 715.9 | 0.058 |
| 3 | -16.5 | -10.5 | gangway | 0.96 | 5.74 | 185.4 | 172.3 | 135.9 | 703.5 | 0.060 |
| 4 | -10.5 | 15.5 | gangway | 0.96 | 5.63 | 188.9 | 181.2 | 135.6 | 691.3 | 0.046 |
| 5 | 16.5 | -10.5 | gangway | 0.96 | 5.69 | 183.8 | 173.7 | 131.7 | 688.4 | 0.058 |
| 6 | -15.5 | -10.5 | gangway | 0.96 | 5.67 | 184.4 | 180.7 | 133.5 | 680.8 | 0.046 |
| 7 | -17.5 | -10.5 | gangway | 0.95 | 5.86 | 176.0 | 165.6 | 127.2 | 672.9 | 0.079 |
| 8 | -10.5 | 17.5 | gangway | 0.95 | 5.89 | 178.9 | 173.2 | 128.4 | 666.1 | 0.079 |
| 9 | 11.5 | 18.5 | gangway | 0.86 | 6.42 | 171.6 | 153.9 | 132.2 | 662.8 | 0.078 |
| 10 | 10.5 | 16.5 | gangway | 0.96 | 5.64 | 187.8 | 177.5 | 126.8 | 650.4 | 0.057 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 9.5 | 14.5 | seat row | 0.50 | 7.16 | 184.0 | 182.4 | 174.9 | 590.8 | 0.029 |
| 2 | -14.5 | 9.5 | seat row | 0.50 | 7.23 | 183.1 | 181.9 | 174.4 | 590.1 | 0.029 |
| 3 | 14.5 | 9.5 | seat row | 0.50 | 7.14 | 180.5 | 178.6 | 169.8 | 569.8 | 0.030 |
| 4 | 9.5 | -14.5 | seat row | 0.50 | 7.03 | 179.6 | 176.7 | 171.4 | 569.5 | 0.030 |
| 5 | -9.5 | -14.5 | seat row | 0.50 | 7.14 | 177.2 | 174.4 | 165.8 | 557.0 | 0.031 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 0; agent-steps of seated agents on another row's clearway: 0.

## Deposit check

Person-seconds deposited: 368247.9, of them in excluded cells: 2.689.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 58326 overlapping pair-steps: p99 0.0037, max 0.0111 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0037 max 0.0111; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 0 (longest 0 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 2.77 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 0 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
