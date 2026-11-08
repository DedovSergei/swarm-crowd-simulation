# Experiment `S_load95_s2`

**Task 5.9 stage 4: venue S, 95% load (seed 2), default model**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 3542 agents on 95% of the 3728 seats (spawnSeatedCrowd, seed 2), buffer N = 4096, 1344 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 130277 evaluations, 2852 switches, 0 forced choices).
Capacity: **within design capacity** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `49b5a27fdf6f6a88f959b17d6a8663be2a60e39d`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-20T23:09:00, 10.1 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 631 | 110.4 |
| t90 | 1101 | 192.6 |
| t100 | 1344 | 235.1 |

t_p: the step by which ceil(p x 3542) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 332 | 0 | 24.5 | 222.5 | 17.8 | 22.3 | 44.8-54.7 |
| -x | 5.66 | 331 | 0 | 24.5 | 220.0 | 17.9 | 21.3 | 51.2-61.2 |
| +y | 5.66 | 336 | 0 | 24.3 | 227.6 | 17.5 | 21.3 | 47.7-57.7 |
| -y | 5.66 | 329 | 0 | 24.5 | 219.9 | 17.8 | 23.4 | 45.5-55.4 |
| door +x+y y | 1.20 | 279 | 450 | 4.9 | 235.1 | 60.6 | 85.3 | 40.4-50.4 |
| door +x+y x | 1.20 | 280 | 445 | 4.9 | 224.2 | 63.8 | 90.3 | 26.2-36.2 |
| door -x+y y | 1.20 | 278 | 446 | 4.9 | 220.2 | 64.5 | 90.3 | 26.1-36.0 |
| door -x+y x | 1.20 | 276 | 444 | 4.9 | 222.0 | 63.5 | 85.3 | 30.8-40.8 |
| door -x-y y | 1.20 | 274 | 437 | 4.9 | 219.9 | 63.7 | 85.3 | 16.8-26.8 |
| door -x-y x | 1.20 | 276 | 439 | 4.9 | 212.7 | 66.4 | 85.3 | 23.8-33.8 |
| door +x-y y | 1.20 | 271 | 434 | 4.9 | 213.2 | 65.0 | 85.3 | 7.2-17.1 |
| door +x-y x | 1.20 | 280 | 447 | 4.9 | 225.1 | 63.5 | 85.3 | 26.4-36.4 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 332 | 9.4% | 17.9% |
| -x | avenue | 5.66 | 331 | 9.3% | 17.9% |
| +y | avenue | 5.66 | 336 | 9.5% | 18.1% |
| -y | avenue | 5.66 | 329 | 9.3% | 17.7% |
| door +x+y y | door | 1.20 | 279 | 7.9% | 71.0% |
| door +x+y x | door | 1.20 | 280 | 7.9% | 71.2% |
| door -x+y y | door | 1.20 | 278 | 7.8% | 70.7% |
| door -x+y x | door | 1.20 | 276 | 7.8% | 70.2% |
| door -x-y y | door | 1.20 | 274 | 7.7% | 69.7% |
| door -x-y x | door | 1.20 | 276 | 7.8% | 70.2% |
| door +x-y y | door | 1.20 | 271 | 7.7% | 68.9% |
| door +x-y x | door | 1.20 | 280 | 7.9% | 71.2% |
| **doors (8)** | door | 9.60 | 2214 | 62.5% | |
| **avenues (4)** | avenue | 22.64 | 1328 | 37.5% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 235.1 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 33.5%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 449 | 12.7% | 449 | 12.7% |
| straight +x+y (x wing) 0 | straight | yes | 444 | 12.5% | 444 | 12.5% |
| corner +x+y | corner | **no** | 2 | 0.1% | 2 | 0.1% |
| straight -x+y (y wing) 0 | straight | yes | 444 | 12.5% | 444 | 12.5% |
| straight -x+y (x wing) 0 | straight | yes | 444 | 12.5% | 444 | 12.5% |
| corner -x+y | corner | **no** | 2 | 0.1% | 2 | 0.1% |
| straight -x-y (y wing) 0 | straight | yes | 436 | 12.3% | 436 | 12.3% |
| straight -x-y (x wing) 0 | straight | yes | 437 | 12.3% | 437 | 12.3% |
| corner -x-y | corner | **no** | 3 | 0.1% | 3 | 0.1% |
| straight +x-y (y wing) 0 | straight | yes | 434 | 12.3% | 434 | 12.3% |
| straight +x-y (x wing) 0 | straight | yes | 446 | 12.6% | 446 | 12.6% |
| corner +x-y | corner | **no** | 1 | 0.0% | 1 | 0.0% |
| **straight (8)** | | | 3534 | | 3534 | 99.8% |
| **corner (4)** | | | 8 | | 8 | 0.2% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 0, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 332 | 24.5 | 222.5 | 0.21 | 0.27 | 0.0% |
| -x | 331 | 24.5 | 220.0 | 0.21 | 0.25 | 0.0% |
| +y | 336 | 24.3 | 227.6 | 0.21 | 0.25 | 0.0% |
| -y | 329 | 24.5 | 219.9 | 0.21 | 0.28 | 0.0% |
| door +x+y y | 279 | 4.9 | 235.1 | 0.72 | 1.02 | 25.0% |
| door +x+y x | 280 | 4.9 | 224.2 | 0.76 | 1.08 | 47.8% |
| door -x+y y | 278 | 4.9 | 220.2 | 0.77 | 1.08 | 47.8% |
| door -x+y x | 276 | 4.9 | 222.0 | 0.76 | 1.02 | 34.8% |
| door -x-y y | 274 | 4.9 | 219.9 | 0.76 | 1.02 | 43.5% |
| door -x-y x | 276 | 4.9 | 212.7 | 0.79 | 1.02 | 45.5% |
| door +x-y y | 271 | 4.9 | 213.2 | 0.78 | 1.02 | 54.5% |
| door +x-y x | 280 | 4.9 | 225.1 | 0.76 | 1.02 | 43.5% |

Mean flow / w J averaged over the doors 0.76, over the avenues 0.21.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 449 | 279 / 170 / 48 | 0.7 | 232.1 | 2.15 | 2.91 | 79% | 79% | 0% | 3.69 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 444 | 280 / 164 / 50 | 0.7 | 221.3 | 2.24 | 2.91 | 83% | 78% | 4% | 3.67 |
| corner +x+y | 1.20 | 31.2 | 2 | 0 / 2 / 0 | 8.2 | 30.6 | 0.09 | 0.10 | 0% | 0% | 0% | nan |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 444 | 278 / 166 / 60 | 0.7 | 217.2 | 2.33 | 3.31 | 82% | 82% | 0% | 3.63 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 444 | 276 / 168 / 50 | 0.7 | 219.0 | 2.26 | 3.21 | 82% | 82% | 0% | 3.72 |
| corner -x+y | 1.20 | 31.2 | 2 | 0 / 2 / 0 | 8.2 | 30.6 | 0.09 | 0.10 | 0% | 0% | 0% | nan |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 436 | 274 / 162 / 33 | 0.7 | 216.9 | 2.17 | 2.91 | 86% | 82% | 5% | 3.53 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 437 | 276 / 161 / 35 | 0.7 | 209.7 | 2.26 | 2.81 | 82% | 82% | 0% | 3.79 |
| corner -x-y | 1.20 | 31.2 | 3 | 0 / 3 / 0 | 8.2 | 33.1 | 0.12 | 0.20 | 0% | 0% | 0% | nan |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 434 | 271 / 163 / 42 | 0.7 | 210.2 | 2.27 | 2.91 | 82% | 82% | 0% | 3.76 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 446 | 280 / 166 / 44 | 0.7 | 222.1 | 2.21 | 2.91 | 78% | 78% | 0% | 3.75 |
| corner +x-y | 1.20 | 31.2 | 1 | 0 / 1 / 0 | 8.4 | 29.0 | 0.05 | 0.10 | 0% | 0% | 0% | nan |

The last agent out (agent 141, t100 235.1 s): last gangway straight +x+y (y wing) 0, exit door +x+y (y wall). The gangway that cleared last: straight +x+y (y wing) 0 at 232.1 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.50 | 224.4 / 216.4 / 175.8 | 205.3 / 194.0 / 121.4 | 37544.9 | 164959 | 0.338 |
| gangway | 392 | 351.5 | 6.50 | 213.6 / 201.1 / 153.4 | 205.3 / 194.0 / 121.4 | 37388.0 | 133011 | 0.115 |
| walkway | 276 | 257.4 | 1.75 | 31.1 / 0.0 / 0.0 | 4.9 / 0.0 / 0.0 | 0.0 | 7329 | 1.246 |
| avenue | 408 | 384.3 | 1.53 | 60.9 / 0.0 / 0.0 | 18.0 / 0.0 / 0.0 | 0.0 | 17263 | 1.319 |
| exit | 40 | 9.7 | 0.00 | 219.5 / 210.6 / 99.0 | 114.4 / 76.3 / 12.6 | 156.9 | 1521 | 1.322 |
| concourse | 612 | 609.0 | 1.66 | 175.1 / 0.0 / 0.0 | 33.8 / 0.0 / 0.0 | 0.0 | 5835 | 1.118 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.57 | 193.4 / 191.0 / 172.1 | 193.4 / 191.0 / 169.3 | 67388.2 | 227337 | 0.068 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -11.5 | -22.5 | gangway | 0.86 | 6.02 | 190.5 | 175.3 | 119.8 | 575.4 | 0.065 |
| 2 | 22.5 | 11.5 | gangway | 0.86 | 6.09 | 189.4 | 178.9 | 121.4 | 573.6 | 0.065 |
| 3 | -22.5 | 11.5 | gangway | 0.86 | 5.91 | 195.0 | 182.4 | 120.9 | 573.1 | 0.063 |
| 4 | 11.5 | -22.5 | gangway | 0.86 | 6.50 | 184.5 | 169.0 | 115.1 | 564.6 | 0.067 |
| 5 | 11.5 | 22.5 | gangway | 0.86 | 6.30 | 195.4 | 181.0 | 115.1 | 564.1 | 0.065 |
| 6 | 10.5 | 18.5 | gangway | 0.94 | 5.76 | 185.9 | 182.4 | 108.3 | 553.6 | 0.041 |
| 7 | 11.5 | 18.5 | gangway | 0.86 | 6.32 | 181.4 | 178.4 | 110.7 | 545.2 | 0.043 |
| 8 | 11.5 | 19.5 | gangway | 0.92 | 5.81 | 178.8 | 175.4 | 108.8 | 541.8 | 0.028 |
| 9 | 22.5 | -11.5 | gangway | 0.86 | 6.16 | 189.1 | 178.9 | 114.6 | 539.7 | 0.067 |
| 10 | -19.5 | -11.5 | gangway | 0.92 | 6.17 | 175.8 | 168.4 | 102.1 | 532.7 | 0.027 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 18.5 | 9.5 | seat row | 0.50 | 7.57 | 182.4 | 180.7 | 169.3 | 589.2 | 0.030 |
| 2 | 9.5 | -18.5 | seat row | 0.50 | 7.30 | 180.0 | 179.1 | 168.8 | 580.2 | 0.030 |
| 3 | -18.5 | 9.5 | seat row | 0.50 | 7.32 | 181.6 | 175.6 | 164.8 | 556.4 | 0.031 |
| 4 | 18.5 | -9.5 | seat row | 0.50 | 7.44 | 181.2 | 171.4 | 161.3 | 555.8 | 0.031 |
| 5 | 9.5 | 18.5 | seat row | 0.50 | 7.53 | 188.0 | 172.8 | 156.9 | 548.2 | 0.030 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 362; agent-steps of seated agents on another row's clearway: 2330.

## Deposit check

Person-seconds deposited: 392300.2, of them in excluded cells: 3.769.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 41791 overlapping pair-steps: p99 0.0037, max 0.0112 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0037 max 0.0112; venue-geometry 0: p99 0.0000 max 0.0000 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00750 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 5 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 1.75 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 85 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
