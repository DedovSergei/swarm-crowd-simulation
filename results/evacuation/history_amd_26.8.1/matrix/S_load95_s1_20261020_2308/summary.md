# Experiment `S_load95_s1`

**Task 5.9 stage 4: venue S, 95% load (seed 1), default model**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 3542 agents on 95% of the 3728 seats (spawnSeatedCrowd, seed 1), buffer N = 4096, 1300 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 130322 evaluations, 2862 switches, 0 forced choices).
Capacity: **within design capacity** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-20T23:08:46, 10.1 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 630 | 110.2 |
| t90 | 1102 | 192.7 |
| t100 | 1300 | 227.4 |

t_p: the step by which ceil(p x 3542) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 329 | 0 | 24.5 | 225.6 | 17.3 | 20.2 | 111.4-121.4 |
| -x | 5.66 | 329 | 0 | 24.1 | 221.3 | 17.7 | 22.3 | 50.9-60.9 |
| +y | 5.66 | 331 | 0 | 24.1 | 224.8 | 17.5 | 21.3 | 46.7-56.7 |
| -y | 5.66 | 327 | 0 | 24.3 | 219.3 | 17.8 | 21.3 | 44.3-54.2 |
| door +x+y y | 1.20 | 278 | 445 | 4.9 | 227.4 | 62.4 | 85.3 | 24.5-34.5 |
| door +x+y x | 1.20 | 279 | 440 | 4.9 | 218.1 | 65.4 | 95.3 | 27.1-37.1 |
| door -x+y y | 1.20 | 281 | 445 | 4.9 | 216.7 | 66.3 | 85.3 | 16.4-26.4 |
| door -x+y x | 1.20 | 272 | 436 | 4.9 | 224.6 | 61.9 | 90.3 | 28.7-38.7 |
| door -x-y y | 1.20 | 277 | 439 | 4.9 | 222.5 | 63.6 | 90.3 | 29.0-39.0 |
| door -x-y x | 1.20 | 282 | 445 | 4.9 | 225.3 | 63.9 | 85.3 | 40.2-50.2 |
| door +x-y y | 1.20 | 277 | 442 | 4.9 | 221.8 | 63.8 | 85.3 | 21.9-31.8 |
| door +x-y x | 1.20 | 280 | 450 | 4.9 | 224.1 | 63.8 | 85.3 | 28.0-38.0 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 329 | 9.3% | 18.3% |
| -x | avenue | 5.66 | 329 | 9.3% | 18.3% |
| +y | avenue | 5.66 | 331 | 9.3% | 18.5% |
| -y | avenue | 5.66 | 327 | 9.2% | 18.2% |
| door +x+y y | door | 1.20 | 278 | 7.8% | 73.1% |
| door +x+y x | door | 1.20 | 279 | 7.9% | 73.4% |
| door -x+y y | door | 1.20 | 281 | 7.9% | 73.9% |
| door -x+y x | door | 1.20 | 272 | 7.7% | 71.5% |
| door -x-y y | door | 1.20 | 277 | 7.8% | 72.9% |
| door -x-y x | door | 1.20 | 282 | 8.0% | 74.2% |
| door +x-y y | door | 1.20 | 277 | 7.8% | 72.9% |
| door +x-y x | door | 1.20 | 280 | 7.9% | 73.6% |
| **doors (8)** | door | 9.60 | 2226 | 62.8% | |
| **avenues (4)** | avenue | 22.64 | 1316 | 37.2% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 227.4 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 34.7%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 444 | 12.5% | 444 | 12.5% |
| straight +x+y (x wing) 0 | straight | yes | 439 | 12.4% | 439 | 12.4% |
| corner +x+y | corner | **no** | 2 | 0.1% | 2 | 0.1% |
| straight -x+y (y wing) 0 | straight | yes | 444 | 12.5% | 444 | 12.5% |
| straight -x+y (x wing) 0 | straight | yes | 435 | 12.3% | 435 | 12.3% |
| corner -x+y | corner | **no** | 2 | 0.1% | 2 | 0.1% |
| straight -x-y (y wing) 0 | straight | yes | 438 | 12.4% | 438 | 12.4% |
| straight -x-y (x wing) 0 | straight | yes | 445 | 12.6% | 445 | 12.6% |
| corner -x-y | corner | **no** | 1 | 0.0% | 1 | 0.0% |
| straight +x-y (y wing) 0 | straight | yes | 440 | 12.4% | 440 | 12.4% |
| straight +x-y (x wing) 0 | straight | yes | 449 | 12.7% | 449 | 12.7% |
| corner +x-y | corner | **no** | 3 | 0.1% | 3 | 0.1% |
| **straight (8)** | | | 3534 | | 3534 | 99.8% |
| **corner (4)** | | | 8 | | 8 | 0.2% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 329 | 24.5 | 225.6 | 0.21 | 0.24 | 0.0% |
| -x | 329 | 24.1 | 221.3 | 0.21 | 0.27 | 0.0% |
| +y | 331 | 24.1 | 224.8 | 0.21 | 0.25 | 0.0% |
| -y | 327 | 24.3 | 219.3 | 0.21 | 0.25 | 0.0% |
| door +x+y y | 278 | 4.9 | 227.4 | 0.75 | 1.02 | 30.4% |
| door +x+y x | 279 | 4.9 | 218.1 | 0.78 | 1.14 | 40.9% |
| door -x+y y | 281 | 4.9 | 216.7 | 0.79 | 1.02 | 59.1% |
| door -x+y x | 272 | 4.9 | 224.6 | 0.74 | 1.08 | 39.1% |
| door -x-y y | 277 | 4.9 | 222.5 | 0.76 | 1.08 | 47.8% |
| door -x-y x | 282 | 4.9 | 225.3 | 0.76 | 1.02 | 60.9% |
| door +x-y y | 277 | 4.9 | 221.8 | 0.76 | 1.02 | 47.8% |
| door +x-y x | 280 | 4.9 | 224.1 | 0.76 | 1.02 | 39.1% |

Mean flow / w J averaged over the doors 0.76, over the avenues 0.21.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 444 | 278 / 166 / 47 | 0.7 | 224.4 | 2.19 | 2.91 | 78% | 78% | 0% | 3.75 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 439 | 279 / 160 / 37 | 0.7 | 215.1 | 2.22 | 3.11 | 86% | 82% | 5% | 3.54 |
| corner +x+y | 1.20 | 31.2 | 2 | 0 / 2 / 0 | 8.2 | 30.6 | 0.09 | 0.10 | 0% | 0% | 0% | nan |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 444 | 281 / 163 / 49 | 0.7 | 213.7 | 2.31 | 2.71 | 82% | 82% | 0% | 3.71 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 435 | 272 / 163 / 52 | 0.7 | 221.6 | 2.20 | 2.81 | 78% | 78% | 0% | 3.65 |
| corner -x+y | 1.20 | 31.2 | 2 | 0 / 2 / 0 | 8.2 | 30.6 | 0.09 | 0.10 | 0% | 0% | 0% | nan |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 438 | 277 / 161 / 40 | 0.7 | 219.5 | 2.18 | 2.81 | 78% | 78% | 0% | 3.62 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 445 | 282 / 163 / 38 | 0.7 | 222.3 | 2.18 | 2.71 | 78% | 78% | 0% | 3.71 |
| corner -x-y | 1.20 | 31.2 | 1 | 0 / 1 / 0 | 8.2 | 30.6 | 0.04 | 0.10 | 0% | 0% | 0% | nan |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 440 | 277 / 163 / 43 | 0.7 | 218.8 | 2.21 | 2.91 | 82% | 82% | 0% | 3.71 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 449 | 280 / 169 / 47 | 0.7 | 221.1 | 2.25 | 2.81 | 83% | 83% | 0% | 3.70 |
| corner +x-y | 1.20 | 31.2 | 3 | 0 / 3 / 0 | 8.2 | 32.0 | 0.13 | 0.20 | 0% | 0% | 0% | nan |

The last agent out (agent 158, t100 227.4 s): last gangway straight +x+y (y wing) 0, exit door +x+y (y wall). The gangway that cleared last: straight +x+y (y wing) 0 at 224.4 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.59 | 224.8 / 216.7 / 178.8 | 202.7 / 196.6 / 125.1 | 37014.0 | 164643 | 0.337 |
| gangway | 392 | 351.5 | 6.59 | 209.5 / 200.1 / 153.4 | 202.7 / 196.6 / 125.1 | 36851.7 | 132898 | 0.115 |
| walkway | 276 | 257.4 | 1.60 | 22.0 / 0.0 / 0.0 | 3.0 / 0.0 / 0.0 | 0.0 | 7251 | 1.248 |
| avenue | 408 | 384.3 | 1.42 | 51.4 / 0.0 / 0.0 | 13.1 / 0.0 / 0.0 | 0.0 | 17106 | 1.319 |
| exit | 40 | 9.7 | 0.00 | 219.9 / 210.6 / 99.0 | 113.9 / 74.5 / 11.9 | 162.3 | 1520 | 1.323 |
| concourse | 612 | 609.0 | 1.61 | 173.9 / 0.0 / 0.0 | 35.0 / 0.0 / 0.0 | 0.0 | 5867 | 1.118 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.57 | 186.1 / 183.0 / 170.5 | 186.1 / 182.8 / 167.7 | 69902.7 | 227768 | 0.068 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -19.5 | -11.5 | gangway | 0.92 | 5.75 | 175.3 | 171.8 | 124.5 | 613.9 | 0.031 |
| 2 | 22.5 | -11.5 | gangway | 0.86 | 6.21 | 196.8 | 183.3 | 125.1 | 609.6 | 0.063 |
| 3 | -19.5 | -10.5 | gangway | 0.96 | 5.61 | 190.3 | 181.6 | 111.6 | 580.4 | 0.030 |
| 4 | 10.5 | 19.5 | gangway | 0.96 | 5.55 | 186.3 | 181.6 | 108.8 | 558.6 | 0.033 |
| 5 | 10.5 | 18.5 | gangway | 0.94 | 5.86 | 187.8 | 184.7 | 109.0 | 556.7 | 0.048 |
| 6 | -11.5 | 22.5 | gangway | 0.86 | 6.19 | 188.0 | 167.4 | 115.1 | 544.5 | 0.070 |
| 7 | -18.5 | -10.5 | gangway | 0.94 | 5.77 | 182.4 | 178.2 | 105.8 | 536.5 | 0.044 |
| 8 | 18.5 | -11.5 | gangway | 0.86 | 6.38 | 178.1 | 172.8 | 107.0 | 533.4 | 0.045 |
| 9 | 10.5 | -19.5 | gangway | 0.96 | 5.55 | 188.0 | 180.0 | 104.1 | 531.4 | 0.035 |
| 10 | 19.5 | -11.5 | gangway | 0.92 | 5.77 | 177.9 | 168.1 | 104.6 | 522.2 | 0.031 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 18.5 | 9.5 | seat row | 0.50 | 7.57 | 181.6 | 178.2 | 167.7 | 586.3 | 0.029 |
| 2 | 9.5 | 18.5 | seat row | 0.50 | 7.36 | 180.9 | 177.4 | 166.3 | 576.6 | 0.031 |
| 3 | 18.5 | -9.5 | seat row | 0.50 | 7.37 | 182.4 | 177.4 | 162.7 | 565.7 | 0.031 |
| 4 | -9.5 | 18.5 | seat row | 0.50 | 7.51 | 177.5 | 173.0 | 160.6 | 561.0 | 0.029 |
| 5 | 9.5 | -18.5 | seat row | 0.50 | 7.56 | 180.5 | 177.9 | 160.0 | 558.6 | 0.029 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 353; agent-steps of seated agents on another row's clearway: 2294.

## Deposit check

Person-seconds deposited: 392415.4, of them in excluded cells: 3.846.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 35095 overlapping pair-steps: p99 0.0037, max 0.0093 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0037 max 0.0093; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 2 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 1.61 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 86 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
