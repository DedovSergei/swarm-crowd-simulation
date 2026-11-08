# Experiment `terrace_n4096`

**Task 5.10 stage 4 (AMD 26.10.1): the terrace reference, N = 4096, every per-step check**

Venue: the current stadium (`stadium.sdf`, `stadium.obj`). N = 4096 (4096 active), spawn `bleacher` (spawnBleacherCrowd, seed 1337), 2712 steps (everyone left), readback every 1 step(s).
Capacity: **within design capacity** (the terrace venue's design capacity 4096, jam capacity 20506: 2841.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T19:35:13, 14.6 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1288 | 225.3 |
| t90 | 2310 | 404.0 |
| t100 | 2712 | 474.3 |

t_p: the step by which ceil(p x 4096) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---|
| +x | 5.71 | 1030 | 15.9 | 454.2 | 24.7 | 31.6 | 25.9-35.9 |
| -x | 5.70 | 1035 | 16.1 | 459.0 | 24.6 | 33.8 | 43.4-53.3 |
| +y | 5.72 | 968 | 15.9 | 443.6 | 23.8 | 30.5 | 43.6-53.5 |
| -y | 5.67 | 1063 | 15.7 | 474.3 | 24.5 | 32.9 | 30.1-40.1 |
| other | | 0 | | | | | |

Clear width: geometric width of the gap in the outer wall, lateral section at dep 0.93 (29.06 m, where agents are removed) at the agent rest height, measured on the SDF (CPU sampler). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | gap | 5.71 | 1030 | 25.1% | 27.3% |
| -x | gap | 5.70 | 1035 | 25.3% | 27.5% |
| +y | gap | 5.72 | 968 | 23.6% | 25.6% |
| -y | gap | 5.67 | 1063 | 26.0% | 28.4% |

**Unused exit width: 0.0 of 22.8 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 474.3 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 27.2%.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp).

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| tread | 2048 | 1968.8 | 6.83 | 433.4 / 426.4 / 380.4 | 433.4 / 426.4 / 302.6 | 212567.7 | 676334 | 0.049 |
| aisle | 256 | 227.2 | 6.63 | 456.9 / 451.3 / 403.5 | 456.0 / 446.2 / 333.2 | 62437.2 | 187743 | 0.112 |
| walkway | 204 | 190.8 | 3.80 | 456.7 / 281.9 / 0.0 | 454.9 / 115.3 / 0.0 | 0.0 | 10368 | 0.462 |
| avenue | 456 | 437.9 | 2.78 | 456.7 / 50.7 / 0.0 | 425.5 / 21.7 / 0.0 | 0.0 | 55834 | 1.247 |
| pitch | 400 | 400.0 | 0.00 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 0 | - |
| exit | 24 | 16.5 | 1.66 | 7.2 / 0.0 / 0.0 | 1.6 / 0.0 / 0.0 | 0.0 | 982 | 1.340 |

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -4.5 | -19.5 | aisle | 1.00 | 6.63 | 433.2 | 428.9 | 333.2 | 1838.4 | 0.049 |
| 2 | -8.5 | -19.5 | tread | 1.00 | 6.73 | 404.4 | 399.3 | 301.0 | 1755.7 | 0.016 |
| 3 | -9.5 | -19.5 | tread | 1.00 | 6.45 | 386.7 | 383.6 | 302.6 | 1733.9 | 0.015 |
| 4 | -7.5 | -19.5 | tread | 1.00 | 6.59 | 411.6 | 406.5 | 291.2 | 1706.0 | 0.018 |
| 5 | -11.5 | -19.5 | tread | 1.00 | 6.29 | 372.9 | 368.4 | 294.2 | 1679.1 | 0.015 |
| 6 | -10.5 | -19.5 | tread | 1.00 | 6.28 | 381.1 | 375.3 | 282.8 | 1623.5 | 0.016 |
| 7 | 19.5 | 4.5 | aisle | 1.00 | 6.16 | 413.0 | 406.8 | 293.5 | 1607.8 | 0.054 |
| 8 | -4.5 | -21.5 | aisle | 1.00 | 6.05 | 376.9 | 361.9 | 289.6 | 1599.5 | 0.026 |
| 9 | -6.5 | -19.5 | tread | 1.00 | 6.56 | 424.5 | 411.4 | 275.0 | 1596.5 | 0.021 |
| 10 | -5.5 | -19.5 | tread | 1.00 | 6.46 | 433.4 | 426.4 | 278.6 | 1583.7 | 0.027 |

## Tread rows (INV-row)

4244 row changes by 2710 agents that did not pass through a non-tread zone (aisle, walkway, ...): an agent in the tread zone resting within 0.3 rises of row k (centre at k x 0.0176 + BODY_RADIUS) is on row k; a change of row without leaving the tread zone in between counts (sampled every 1 step(s)). Down (towards the pitch) 4244, up 0; more than one row at once 0; in steps 1-50 / 51-200 / after 200: 213 / 742 / 3289. The first events are in `crossings.csv`.

## Deposit check

Person-seconds deposited: 931261.6, of them in excluded cells: 0.000.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 125831 overlapping pair-steps: p99 0.0742, max 0.3923 of BODY_DIAM (limits 0.05 / 0.20, crowd cases; venue-geometry cases exempt in the baked terrace); crowd p99 0.0346 max 0.1248; venue-geometry 14496: p99 0.2496 max 0.3923 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.01046 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 8334 (longest 15 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.83 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | exempt | 4244 row changes (the baked terrace is exempt: bare treads without seat backs, docs/MODEL.md INV-row) |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the baked terrace reference venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
