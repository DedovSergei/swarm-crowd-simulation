# Experiment `terrace_n4096`

**Task 5.9 stage 4: the terrace reference, N = 4096, every per-step check**

Venue: the current stadium (`stadium.sdf`, `stadium.obj`). N = 4096 (4096 active), spawn `bleacher` (spawnBleacherCrowd, seed 1337), 2704 steps (everyone left), readback every 1 step(s).
Capacity: **within design capacity** (the terrace venue's design capacity 4096, jam capacity 20506: 2841.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-20T23:08:04, 11.7 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 1296 | 226.7 |
| t90 | 2311 | 404.2 |
| t100 | 2704 | 472.9 |

t_p: the step by which ceil(p x 4096) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---|
| +x | 5.71 | 1031 | 15.9 | 457.7 | 24.5 | 30.6 | 23.3-33.2 |
| -x | 5.70 | 1035 | 16.1 | 461.9 | 24.4 | 31.7 | 34.1-44.1 |
| +y | 5.72 | 968 | 15.9 | 441.1 | 23.9 | 31.6 | 38.7-48.6 |
| -y | 5.67 | 1062 | 15.7 | 472.9 | 24.6 | 34.0 | 41.5-51.4 |
| other | | 0 | | | | | |

Clear width: geometric width of the gap in the outer wall, lateral section at dep 0.93 (29.06 m, where agents are removed) at the agent rest height, measured on the SDF (CPU sampler). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | gap | 5.71 | 1031 | 25.2% | 27.4% |
| -x | gap | 5.70 | 1035 | 25.3% | 27.5% |
| +y | gap | 5.72 | 968 | 23.6% | 25.7% |
| -y | gap | 5.67 | 1062 | 25.9% | 28.4% |

**Unused exit width: 0.0 of 22.8 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 472.9 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 27.3%.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp).

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| tread | 2048 | 1968.8 | 6.77 | 431.5 / 423.4 / 380.4 | 431.5 / 423.1 / 280.2 | 199640.5 | 678486 | 0.049 |
| aisle | 256 | 227.2 | 6.44 | 455.8 / 451.6 / 401.6 | 454.9 / 446.7 / 301.9 | 61050.9 | 187270 | 0.113 |
| walkway | 204 | 190.8 | 4.11 | 454.9 / 297.9 / 0.0 | 453.7 / 112.5 / 0.0 | 0.0 | 10572 | 0.452 |
| avenue | 456 | 437.9 | 2.78 | 456.3 / 47.6 / 0.0 | 430.8 / 20.8 / 0.0 | 0.0 | 55886 | 1.245 |
| pitch | 400 | 400.0 | 0.00 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 0 | - |
| exit | 24 | 16.5 | 1.59 | 5.8 / 0.0 / 0.0 | 1.4 / 0.0 / 0.0 | 0.0 | 982 | 1.340 |

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 19.5 | -4.5 | aisle | 1.00 | 6.31 | 402.5 | 397.6 | 301.9 | 1674.9 | 0.052 |
| 2 | 19.5 | 13.5 | tread | 1.00 | 6.51 | 340.5 | 333.5 | 274.4 | 1605.9 | 0.016 |
| 3 | -4.5 | -19.5 | aisle | 1.00 | 6.10 | 430.1 | 427.8 | 296.1 | 1605.7 | 0.055 |
| 4 | 10.5 | -19.5 | tread | 1.00 | 6.54 | 369.4 | 346.0 | 272.0 | 1601.5 | 0.020 |
| 5 | 4.5 | -21.5 | aisle | 1.00 | 6.14 | 358.2 | 351.9 | 286.5 | 1596.5 | 0.026 |
| 6 | 19.5 | -5.5 | tread | 1.00 | 6.38 | 399.1 | 395.1 | 279.0 | 1564.9 | 0.030 |
| 7 | -19.5 | -9.5 | tread | 1.00 | 6.06 | 380.4 | 368.2 | 280.2 | 1562.9 | 0.022 |
| 8 | 19.5 | 9.5 | tread | 1.00 | 6.46 | 386.7 | 350.0 | 266.6 | 1552.0 | 0.020 |
| 9 | 19.5 | 12.5 | tread | 1.00 | 6.43 | 345.8 | 343.5 | 260.8 | 1528.0 | 0.016 |
| 10 | 7.5 | -19.5 | tread | 1.00 | 6.61 | 396.3 | 373.6 | 257.1 | 1518.6 | 0.022 |

## Tread rows (INV-row)

4213 row changes by 2719 agents that did not pass through a non-tread zone (aisle, walkway, ...): an agent in the tread zone resting within 0.3 rises of row k (centre at k x 0.0176 + BODY_RADIUS) is on row k; a change of row without leaving the tread zone in between counts (sampled every 1 step(s)). Down (towards the pitch) 4213, up 0; more than one row at once 0; in steps 1-50 / 51-200 / after 200: 216 / 749 / 3248. The first events are in `crossings.csv`.

## Deposit check

Person-seconds deposited: 933196.9, of them in excluded cells: 0.000.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 125099 overlapping pair-steps: p99 0.0720, max 0.3922 of BODY_DIAM (limits 0.05 / 0.20, crowd cases; venue-geometry cases exempt in the baked terrace); crowd p99 0.0329 max 0.0990; venue-geometry 14256: p99 0.2498 max 0.3922 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00996 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 8348 (longest 11 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 6.77 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | exempt | 4213 row changes (the baked terrace is exempt: bare treads without seat backs, docs/MODEL.md INV-row) |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the baked terrace reference venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
