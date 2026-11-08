# Experiment `S_load100_nearest`

**Task 5.9 stage 4: venue S, 100% load, nearest exit (incline speed, stair spacing): the uninformed-crowd bound**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 3728 agents on 100% of the 3728 seats (spawnSeatedCrowd, seed 1337), buffer N = 4096, 2078 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **nearest exit, incline speed, stair spacing (empirical)**.
Capacity: **within design capacity** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-20T23:12:15, 14.3 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 999 | 174.7 |
| t90 | 1804 | 315.5 |
| t100 | 2078 | 363.5 |

t_p: the step by which ceil(p x 3728) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| -x | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| +y | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| -y | 5.66 | 0 | 0 | nan | nan | nan | nan | nan-9.6 |
| door +x+y y | 1.20 | 466 | 466 | 4.9 | 353.7 | 66.8 | 85.3 | 21.2-31.1 |
| door +x+y x | 1.20 | 466 | 466 | 4.9 | 355.4 | 66.4 | 85.3 | 21.2-31.1 |
| door -x+y y | 1.20 | 466 | 466 | 4.9 | 356.6 | 66.2 | 90.3 | 52.1-62.1 |
| door -x+y x | 1.20 | 466 | 466 | 4.9 | 353.3 | 66.8 | 90.3 | 19.1-29.0 |
| door -x-y y | 1.20 | 466 | 466 | 4.9 | 357.0 | 66.1 | 90.3 | 19.2-29.2 |
| door -x-y x | 1.20 | 466 | 466 | 4.9 | 363.5 | 65.0 | 90.3 | 19.2-29.2 |
| door +x-y y | 1.20 | 466 | 466 | 4.9 | 355.9 | 66.3 | 90.3 | 18.0-28.0 |
| door +x-y x | 1.20 | 466 | 466 | 4.9 | 357.3 | 66.1 | 85.3 | 32.9-42.9 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 0 | 0.0% | 0.0% |
| -x | avenue | 5.66 | 0 | 0.0% | 0.0% |
| +y | avenue | 5.66 | 0 | 0.0% | 0.0% |
| -y | avenue | 5.66 | 0 | 0.0% | 0.0% |
| door +x+y y | door | 1.20 | 466 | 12.5% | 76.7% |
| door +x+y x | door | 1.20 | 466 | 12.5% | 76.7% |
| door -x+y y | door | 1.20 | 466 | 12.5% | 76.7% |
| door -x+y x | door | 1.20 | 466 | 12.5% | 76.7% |
| door -x-y y | door | 1.20 | 466 | 12.5% | 76.7% |
| door -x-y x | door | 1.20 | 466 | 12.5% | 76.7% |
| door +x-y y | door | 1.20 | 466 | 12.5% | 76.7% |
| door +x-y x | door | 1.20 | 466 | 12.5% | 76.7% |
| **doors (8)** | door | 9.60 | 3728 | 100.0% | |
| **avenues (4)** | avenue | 22.64 | 0 | 0.0% | |

**Unused exit width: 22.6 of 32.2 m (70.2%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 363.5 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 22.8%.

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
| door +x+y y | 466 | 4.9 | 353.7 | 0.80 | 1.02 | 38.9% |
| door +x+y x | 466 | 4.9 | 355.4 | 0.79 | 1.02 | 47.2% |
| door -x+y y | 466 | 4.9 | 356.6 | 0.79 | 1.08 | 38.9% |
| door -x+y x | 466 | 4.9 | 353.3 | 0.80 | 1.08 | 33.3% |
| door -x-y y | 466 | 4.9 | 357.0 | 0.79 | 1.08 | 33.3% |
| door -x-y x | 466 | 4.9 | 363.5 | 0.78 | 1.08 | 32.4% |
| door +x-y y | 466 | 4.9 | 355.9 | 0.79 | 1.08 | 36.1% |
| door +x-y x | 466 | 4.9 | 357.3 | 0.79 | 1.02 | 38.9% |

Mean flow / w J averaged over the doors 0.79, over the avenues nan.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 466 | 466 / 0 / 0 | 0.7 | 350.7 | 1.33 | 1.60 | 89% | 83% | 6% | 3.90 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 466 | 466 / 0 / 0 | 0.7 | 352.4 | 1.32 | 1.71 | 92% | 81% | 11% | 3.81 |
| corner +x+y | 1.20 | 31.2 | 0 | 0 / 0 / 0 | - | - | nan | nan | nan% | nan% | nan% | nan |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 466 | 466 / 0 / 0 | 0.7 | 353.7 | 1.32 | 1.71 | 92% | 81% | 11% | 3.78 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 466 | 466 / 0 / 0 | 0.7 | 350.3 | 1.33 | 1.81 | 92% | 81% | 11% | 3.81 |
| corner -x+y | 1.20 | 31.2 | 0 | 0 / 0 / 0 | - | - | nan | nan | nan% | nan% | nan% | nan |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 466 | 466 / 0 / 0 | 0.7 | 354.0 | 1.32 | 1.71 | 92% | 81% | 11% | 3.81 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 466 | 466 / 0 / 0 | 0.7 | 360.5 | 1.29 | 1.81 | 89% | 81% | 8% | 3.86 |
| corner -x-y | 1.20 | 31.2 | 0 | 0 / 0 / 0 | - | - | nan | nan | nan% | nan% | nan% | nan |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 466 | 466 / 0 / 0 | 0.7 | 353.0 | 1.32 | 1.60 | 92% | 83% | 8% | 3.87 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 466 | 466 / 0 / 0 | 0.7 | 354.4 | 1.32 | 1.71 | 92% | 83% | 8% | 3.88 |
| corner +x-y | 1.20 | 31.2 | 0 | 0 / 0 / 0 | - | - | nan | nan | nan% | nan% | nan% | nan |

The last agent out (agent 2345, t100 363.5 s): last gangway straight -x-y (x wing) 0, exit -. The gangway that cleared last: straight -x-y (x wing) 0 at 360.5 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.52 | 361.0 / 357.5 / 314.7 | 340.5 / 333.2 / 249.6 | 120778.5 | 245422 | 0.152 |
| gangway | 392 | 351.5 | 6.52 | 358.7 / 333.2 / 281.2 | 340.5 / 333.2 / 249.6 | 120482.9 | 233938 | 0.103 |
| walkway | 276 | 257.4 | 0.09 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 6 | 0.011 |
| avenue | 408 | 384.3 | 0.17 | 0.0 / 0.0 / 0.0 | 0.0 / 0.0 / 0.0 | 0.0 | 5 | 0.142 |
| exit | 40 | 9.7 | 0.00 | 348.6 / 342.1 / 174.7 | 190.5 / 127.9 / 20.3 | 295.5 | 1703 | 1.319 |
| concourse | 612 | 609.0 | 1.69 | 288.8 / 0.0 / 0.0 | 53.0 / 0.0 / 0.0 | 0.0 | 9770 | 1.124 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.38 | 335.1 / 333.5 / 327.8 | 335.1 / 333.5 / 325.2 | 136333.7 | 406348 | 0.036 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -10.5 | -15.5 | gangway | 0.96 | 5.65 | 332.8 | 323.6 | 249.6 | 1314.6 | 0.023 |
| 2 | -10.5 | -16.5 | gangway | 0.96 | 5.72 | 331.4 | 316.6 | 246.4 | 1307.9 | 0.033 |
| 3 | -15.5 | 10.5 | gangway | 0.96 | 5.79 | 329.5 | 324.3 | 245.0 | 1302.7 | 0.023 |
| 4 | -16.5 | 10.5 | gangway | 0.96 | 5.84 | 331.4 | 314.7 | 243.3 | 1299.0 | 0.032 |
| 5 | -10.5 | 15.5 | gangway | 0.96 | 5.89 | 332.8 | 324.3 | 246.8 | 1290.1 | 0.023 |
| 6 | -15.5 | -10.5 | gangway | 0.96 | 5.54 | 339.8 | 333.2 | 244.9 | 1275.0 | 0.022 |
| 7 | 16.5 | -10.5 | gangway | 0.96 | 5.82 | 332.5 | 316.8 | 234.2 | 1264.6 | 0.031 |
| 8 | -16.5 | -10.5 | gangway | 0.96 | 5.71 | 340.5 | 325.5 | 236.6 | 1260.5 | 0.030 |
| 9 | 10.5 | -15.5 | gangway | 0.96 | 5.78 | 332.5 | 327.8 | 236.5 | 1255.3 | 0.023 |
| 10 | -10.5 | 16.5 | gangway | 0.96 | 5.82 | 333.5 | 322.9 | 234.5 | 1245.1 | 0.033 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -14.5 | -9.5 | seat row | 0.50 | 7.24 | 335.1 | 333.5 | 325.2 | 1103.4 | 0.016 |
| 2 | 9.5 | -14.5 | seat row | 0.50 | 7.27 | 328.0 | 326.6 | 319.0 | 1091.6 | 0.017 |
| 3 | 14.5 | 9.5 | seat row | 0.50 | 7.24 | 329.0 | 326.2 | 318.9 | 1088.0 | 0.017 |
| 4 | -9.5 | 14.5 | seat row | 0.50 | 7.24 | 329.7 | 328.0 | 315.9 | 1074.4 | 0.017 |
| 5 | -9.5 | -14.5 | seat row | 0.50 | 7.24 | 330.7 | 329.3 | 317.8 | 1071.9 | 0.017 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 0; agent-steps of seated agents on another row's clearway: 0.

## Deposit check

Person-seconds deposited: 651776.0, of them in excluded cells: 5.706.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 141695 overlapping pair-steps: p99 0.0024, max 0.0136 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0024 max 0.0136; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00753 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 0 (longest 0 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.748556 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 1.69 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 0 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
