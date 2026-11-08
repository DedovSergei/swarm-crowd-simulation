# Experiment `S_load100_nearest`

**Task 5.10 stage 4 (AMD 26.10.1): venue S, 100% load, nearest exit (incline speed, stair spacing): the uninformed-crowd bound**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 3728 agents on 100% of the 3728 seats (spawnSeatedCrowd, seed 1337), buffer N = 4096, 2070 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **nearest exit, incline speed, stair spacing (empirical)**.
Capacity: **within design capacity** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T19:39:30, 46.7 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1002 | 175.3 |
| t90 | 1810 | 316.6 |
| t100 | 2070 | 362.1 |

t_p: the step by which ceil(p x 3728) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| -x | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| +y | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| -y | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| door +x+y y | 1.20 | 466 | 466 | 4.9 | 358.2 | 65.9 | 85.3 | 27.8-37.8 |
| door +x+y x | 1.20 | 466 | 466 | 4.9 | 357.9 | 66.0 | 85.3 | 27.5-37.4 |
| door -x+y y | 1.20 | 466 | 466 | 4.9 | 354.7 | 66.6 | 90.3 | 27.8-37.8 |
| door -x+y x | 1.20 | 466 | 466 | 4.9 | 362.1 | 65.2 | 85.3 | 19.4-29.4 |
| door -x-y y | 1.20 | 466 | 466 | 4.9 | 357.5 | 66.0 | 90.3 | 29.4-39.4 |
| door -x-y x | 1.20 | 466 | 466 | 4.9 | 357.0 | 66.1 | 90.3 | 27.8-37.8 |
| door +x-y y | 1.20 | 466 | 466 | 4.9 | 354.4 | 66.6 | 85.3 | 27.3-37.3 |
| door +x-y x | 1.20 | 466 | 466 | 4.9 | 359.3 | 65.7 | 90.3 | 36.6-46.5 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 0 | 0.0% | 0.0% |
| -x | avenue | 5.66 | 0 | 0.0% | 0.0% |
| +y | avenue | 5.66 | 0 | 0.0% | 0.0% |
| -y | avenue | 5.66 | 0 | 0.0% | 0.0% |
| door +x+y y | door | 1.20 | 466 | 12.5% | 77.0% |
| door +x+y x | door | 1.20 | 466 | 12.5% | 77.0% |
| door -x+y y | door | 1.20 | 466 | 12.5% | 77.0% |
| door -x+y x | door | 1.20 | 466 | 12.5% | 77.0% |
| door -x-y y | door | 1.20 | 466 | 12.5% | 77.0% |
| door -x-y x | door | 1.20 | 466 | 12.5% | 77.0% |
| door +x-y y | door | 1.20 | 466 | 12.5% | 77.0% |
| door +x-y x | door | 1.20 | 466 | 12.5% | 77.0% |
| **doors (8)** | door | 9.60 | 3728 | 100.0% | |
| **avenues (4)** | avenue | 22.64 | 0 | 0.0% | |

**Unused exit width: 22.6 of 32.2 m (70.2%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 362.1 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 22.9%.

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
| door +x+y y | 466 | 4.9 | 358.2 | 0.79 | 1.02 | 36.1% |
| door +x+y x | 466 | 4.9 | 357.9 | 0.79 | 1.02 | 36.1% |
| door -x+y y | 466 | 4.9 | 354.7 | 0.80 | 1.08 | 44.4% |
| door -x+y x | 466 | 4.9 | 362.1 | 0.78 | 1.02 | 32.4% |
| door -x-y y | 466 | 4.9 | 357.5 | 0.79 | 1.08 | 38.9% |
| door -x-y x | 466 | 4.9 | 357.0 | 0.79 | 1.08 | 41.7% |
| door +x-y y | 466 | 4.9 | 354.4 | 0.80 | 1.02 | 47.2% |
| door +x-y x | 466 | 4.9 | 359.3 | 0.79 | 1.08 | 37.8% |

Mean flow / w J averaged over the doors 0.79, over the avenues nan.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 466 | 466 / 0 / 0 | 0.7 | 355.2 | 1.31 | 1.60 | 92% | 81% | 11% | 3.87 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 466 | 466 / 0 / 0 | 0.7 | 354.9 | 1.32 | 1.50 | 92% | 83% | 8% | 3.87 |
| corner +x+y | 1.20 | 31.2 | 0 | 0 / 0 / 0 | - | - | nan | nan | nan% | nan% | nan% | nan |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 466 | 466 / 0 / 0 | 0.7 | 351.7 | 1.33 | 1.71 | 89% | 81% | 8% | 3.96 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 466 | 466 / 0 / 0 | 0.7 | 359.1 | 1.30 | 1.60 | 89% | 84% | 5% | 3.92 |
| corner -x+y | 1.20 | 31.2 | 0 | 0 / 0 / 0 | - | - | nan | nan | nan% | nan% | nan% | nan |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 466 | 466 / 0 / 0 | 0.7 | 354.5 | 1.32 | 1.60 | 92% | 83% | 8% | 3.88 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 466 | 466 / 0 / 0 | 0.7 | 354.0 | 1.32 | 1.71 | 92% | 83% | 8% | 3.86 |
| corner -x-y | 1.20 | 31.2 | 0 | 0 / 0 / 0 | - | - | nan | nan | nan% | nan% | nan% | nan |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 466 | 466 / 0 / 0 | 0.7 | 351.4 | 1.33 | 1.71 | 89% | 81% | 8% | 3.93 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 466 | 466 / 0 / 0 | 0.7 | 356.3 | 1.31 | 1.71 | 92% | 83% | 8% | 3.86 |
| corner +x-y | 1.20 | 31.2 | 0 | 0 / 0 / 0 | - | - | nan | nan | nan% | nan% | nan% | nan |

The last agent out (agent 1413, t100 362.1 s): last gangway straight -x+y (x wing) 0, exit -. The gangway that cleared last: straight -x+y (x wing) 0 at 359.1 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.74 | 359.8 / 357.3 / 317.1 | 338.8 / 333.2 / 256.9 | 124831.3 | 248923 | 0.150 |
| gangway | 392 | 351.5 | 6.74 | 356.5 / 334.4 / 294.9 | 338.8 / 333.2 / 256.9 | 124546.3 | 237453 | 0.101 |
| walkway | 276 | 257.4 | 0.11 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 4 | 0.015 |
| avenue | 408 | 384.3 | 0.17 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 5 | 0.142 |
| exit | 40 | 9.7 | 0.00 | 349.1 / 342.3 / 170.7 | 190.6 / 128.4 / 19.1 | 284.9 | 1702 | 1.317 |
| concourse | 612 | 609.0 | 1.72 | 291.0 / 0.0 / 0.0 | 51.4 / 0.0 / 0.0 | 0.0 | 9759 | 1.125 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.58 | 333.2 / 331.4 / 326.7 | 333.2 / 331.4 / 324.1 | 138992.9 | 406236 | 0.036 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 10.5 | -15.5 | gangway | 0.96 | 5.88 | 330.7 | 323.6 | 253.4 | 1348.7 | 0.022 |
| 2 | 15.5 | 10.5 | gangway | 0.96 | 5.84 | 334.2 | 326.4 | 250.8 | 1328.1 | 0.022 |
| 3 | -10.5 | -15.5 | gangway | 0.96 | 5.85 | 333.9 | 327.6 | 250.1 | 1321.3 | 0.022 |
| 4 | 10.5 | 14.5 | gangway | 0.94 | 5.72 | 330.2 | 321.5 | 254.0 | 1308.6 | 0.018 |
| 5 | -17.5 | -11.5 | gangway | 0.89 | 6.32 | 319.6 | 301.7 | 251.3 | 1303.1 | 0.035 |
| 6 | -10.5 | 15.5 | gangway | 0.96 | 5.95 | 330.4 | 325.7 | 242.2 | 1300.2 | 0.022 |
| 7 | 16.5 | 11.5 | gangway | 0.92 | 5.91 | 321.0 | 309.8 | 254.0 | 1285.0 | 0.025 |
| 8 | 17.5 | 11.5 | gangway | 0.89 | 6.27 | 319.2 | 299.4 | 248.4 | 1284.4 | 0.034 |
| 9 | 16.5 | -11.5 | gangway | 0.92 | 5.89 | 319.0 | 309.9 | 256.9 | 1279.6 | 0.025 |
| 10 | -11.5 | -17.5 | gangway | 0.89 | 6.31 | 315.7 | 284.9 | 245.7 | 1273.4 | 0.034 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -14.5 | 9.5 | seat row | 0.50 | 7.22 | 333.2 | 331.4 | 324.1 | 1079.7 | 0.017 |
| 2 | 9.5 | 14.5 | seat row | 0.50 | 7.30 | 328.8 | 325.9 | 318.5 | 1078.7 | 0.017 |
| 3 | -9.5 | -14.5 | seat row | 0.50 | 7.26 | 329.2 | 327.8 | 319.6 | 1070.5 | 0.017 |
| 4 | 9.5 | -14.5 | seat row | 0.50 | 7.23 | 327.3 | 325.5 | 316.9 | 1056.8 | 0.017 |
| 5 | 14.5 | -9.5 | seat row | 0.50 | 7.23 | 330.4 | 326.7 | 316.4 | 1052.2 | 0.017 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 0; agent-steps of seated agents on another row's clearway: 0.

## Deposit check

Person-seconds deposited: 655164.3, of them in excluded cells: 5.665.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 148020 overlapping pair-steps: p99 0.0026, max 0.0109 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0026 max 0.0109; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00751 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 0 (longest 0 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.748559 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 1.72 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 0 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
