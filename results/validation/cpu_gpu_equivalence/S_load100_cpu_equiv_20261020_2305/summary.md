# Experiment `S_load100_cpu_equiv`

**Task 5.9 stage 3: CPU reference (counting sort), default model**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 3728 agents on 100% of the 3728 seats (spawnSeatedCrowd, seed 1337), buffer N = 4096, 1361 steps (everyone left), readback every 1 step(s). Engine: CPU reference (CpuCrowdSim, counting sort, all threads).
Model: **queue-aware exit choice, incline speed, stair spacing (empirical)** (exit choice: 141886 evaluations, 3057 switches, 0 forced choices).
Capacity: **within design capacity** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `ba86b3ae21b252be1c83e995381b467da49ad033`, dirty 1, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; started 2026-10-20T23:05:51, 8.4 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 649 | 113.5 |
| t90 | 1148 | 200.8 |
| t100 | 1361 | 238.0 |

t_p: the step by which ceil(p x 3728) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 347 | 0 | 24.5 | 230.4 | 17.9 | 23.4 | 45.7-55.6 |
| -x | 5.66 | 350 | 0 | 24.5 | 231.4 | 17.9 | 24.5 | 46.2-56.1 |
| +y | 5.66 | 346 | 0 | 24.5 | 229.3 | 17.9 | 23.4 | 45.3-55.3 |
| -y | 5.66 | 348 | 0 | 24.5 | 230.7 | 17.9 | 23.4 | 45.3-55.3 |
| door +x+y y | 1.20 | 291 | 466 | 4.9 | 223.9 | 66.4 | 90.3 | 23.6-33.6 |
| door +x+y x | 1.20 | 295 | 466 | 4.9 | 234.0 | 64.3 | 90.3 | 22.6-32.5 |
| door -x+y y | 1.20 | 295 | 466 | 4.9 | 234.5 | 64.2 | 90.3 | 52.3-62.3 |
| door -x+y x | 1.20 | 289 | 466 | 4.9 | 228.8 | 64.5 | 90.3 | 19.2-29.2 |
| door -x-y y | 1.20 | 291 | 466 | 4.9 | 234.4 | 63.4 | 90.3 | 19.1-29.0 |
| door -x-y x | 1.20 | 293 | 466 | 4.9 | 226.2 | 66.2 | 90.3 | 19.2-29.2 |
| door +x-y y | 1.20 | 293 | 466 | 4.9 | 238.0 | 62.8 | 90.3 | 19.2-29.2 |
| door +x-y x | 1.20 | 290 | 466 | 4.9 | 226.3 | 65.4 | 90.3 | 52.3-62.3 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 347 | 9.3% | 18.5% |
| -x | avenue | 5.66 | 350 | 9.4% | 18.6% |
| +y | avenue | 5.66 | 346 | 9.3% | 18.4% |
| -y | avenue | 5.66 | 348 | 9.3% | 18.5% |
| door +x+y y | door | 1.20 | 291 | 7.8% | 73.1% |
| door +x+y x | door | 1.20 | 295 | 7.9% | 74.1% |
| door -x+y y | door | 1.20 | 295 | 7.9% | 74.1% |
| door -x+y x | door | 1.20 | 289 | 7.8% | 72.6% |
| door -x-y y | door | 1.20 | 291 | 7.8% | 73.1% |
| door -x-y x | door | 1.20 | 293 | 7.9% | 73.6% |
| door +x-y y | door | 1.20 | 293 | 7.9% | 73.6% |
| door +x-y x | door | 1.20 | 290 | 7.8% | 72.9% |
| **doors (8)** | door | 9.60 | 2337 | 62.7% | |
| **avenues (4)** | avenue | 22.64 | 1391 | 37.3% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 238.0 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 34.9%.

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
| +x | 347 | 24.5 | 230.4 | 0.21 | 0.28 | 0.0% |
| -x | 350 | 24.5 | 231.4 | 0.21 | 0.29 | 0.0% |
| +y | 346 | 24.5 | 229.3 | 0.21 | 0.28 | 0.0% |
| -y | 348 | 24.5 | 230.7 | 0.21 | 0.28 | 0.0% |
| door +x+y y | 291 | 4.9 | 223.9 | 0.79 | 1.08 | 47.8% |
| door +x+y x | 295 | 4.9 | 234.0 | 0.77 | 1.08 | 54.2% |
| door -x+y y | 295 | 4.9 | 234.5 | 0.77 | 1.08 | 54.2% |
| door -x+y x | 289 | 4.9 | 228.8 | 0.77 | 1.08 | 39.1% |
| door -x-y y | 291 | 4.9 | 234.4 | 0.76 | 1.08 | 50.0% |
| door -x-y x | 293 | 4.9 | 226.2 | 0.79 | 1.08 | 43.5% |
| door +x-y y | 293 | 4.9 | 238.0 | 0.75 | 1.08 | 45.8% |
| door +x-y x | 290 | 4.9 | 226.3 | 0.78 | 1.08 | 52.2% |

Mean flow / w J averaged over the doors 0.77, over the avenues 0.21.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 464 | 291 / 173 / 42 | 0.7 | 220.9 | 2.30 | 3.01 | 83% | 83% | 0% | 3.68 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 464 | 295 / 169 / 46 | 0.7 | 231.1 | 2.21 | 2.81 | 79% | 79% | 0% | 3.69 |
| corner +x+y | 1.20 | 31.2 | 4 | 0 / 4 / 0 | 8.2 | 30.8 | 0.18 | 0.20 | 0% | 0% | 0% | nan |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 464 | 295 / 169 / 45 | 0.7 | 231.6 | 2.20 | 2.91 | 79% | 79% | 0% | 3.68 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 464 | 289 / 175 / 52 | 0.7 | 225.8 | 2.29 | 2.81 | 87% | 83% | 4% | 3.66 |
| corner -x+y | 1.20 | 31.2 | 4 | 0 / 4 / 0 | 8.2 | 30.8 | 0.18 | 0.20 | 0% | 0% | 0% | nan |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 464 | 291 / 173 / 57 | 0.7 | 231.4 | 2.26 | 3.21 | 79% | 79% | 0% | 3.72 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 464 | 293 / 171 / 41 | 0.7 | 223.2 | 2.27 | 2.91 | 83% | 83% | 0% | 3.76 |
| corner -x-y | 1.20 | 31.2 | 4 | 0 / 4 / 0 | 8.2 | 30.6 | 0.18 | 0.20 | 0% | 0% | 0% | nan |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 464 | 293 / 171 / 53 | 0.7 | 235.1 | 2.20 | 3.31 | 83% | 79% | 4% | 3.66 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 464 | 290 / 174 / 55 | 0.7 | 223.4 | 2.33 | 2.81 | 83% | 83% | 0% | 3.76 |
| corner +x-y | 1.20 | 31.2 | 4 | 0 / 4 / 0 | 8.2 | 30.8 | 0.18 | 0.20 | 0% | 0% | 0% | nan |

The last agent out (agent 2965, t100 238.0 s): last gangway straight +x-y (y wing) 0, exit door +x-y (y wall). The gangway that cleared last: straight +x-y (y wing) 0 at 235.1 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.45 | 232.1 / 222.7 / 183.1 | 208.3 / 201.7 / 126.5 | 39847.5 | 173251 | 0.338 |
| gangway | 392 | 351.5 | 6.45 | 217.4 / 206.4 / 157.2 | 208.3 / 201.7 / 126.5 | 39670.9 | 139696 | 0.115 |
| walkway | 276 | 257.4 | 1.84 | 26.9 / 0.0 / 0.0 | 4.4 / 0.0 / 0.0 | 0.0 | 7695 | 1.244 |
| avenue | 408 | 384.3 | 1.49 | 53.5 / 0.0 / 0.0 | 19.1 / 0.0 / 0.0 | 0.0 | 18084 | 1.319 |
| exit | 40 | 9.7 | 0.00 | 220.9 / 207.4 / 96.2 | 119.5 / 81.5 / 13.3 | 176.7 | 1606 | 1.320 |
| concourse | 612 | 609.0 | 1.69 | 174.6 / 0.0 / 0.0 | 36.2 / 0.0 / 0.0 | 0.0 | 6169 | 1.116 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.55 | 198.9 / 195.5 / 180.2 | 198.9 / 195.5 / 177.5 | 79200.1 | 253793 | 0.064 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 11.5 | -19.5 | gangway | 0.92 | 5.99 | 180.2 | 176.1 | 126.5 | 637.3 | 0.032 |
| 2 | 10.5 | -19.5 | gangway | 0.96 | 5.80 | 203.6 | 192.2 | 118.6 | 621.1 | 0.035 |
| 3 | -11.5 | -22.5 | gangway | 0.86 | 6.23 | 199.0 | 178.2 | 124.9 | 605.4 | 0.065 |
| 4 | -19.5 | 10.5 | gangway | 0.96 | 5.72 | 192.2 | 182.8 | 113.5 | 589.9 | 0.032 |
| 5 | 22.5 | -11.5 | gangway | 0.86 | 6.10 | 198.5 | 179.5 | 120.3 | 580.2 | 0.067 |
| 6 | -11.5 | -19.5 | gangway | 0.92 | 5.57 | 182.3 | 174.9 | 119.3 | 578.8 | 0.031 |
| 7 | 11.5 | -22.5 | gangway | 0.86 | 6.00 | 199.0 | 182.8 | 120.2 | 573.4 | 0.065 |
| 8 | -19.5 | 11.5 | gangway | 0.92 | 5.82 | 183.5 | 179.3 | 114.7 | 568.8 | 0.032 |
| 9 | 19.5 | -10.5 | gangway | 0.96 | 5.60 | 199.6 | 190.6 | 110.2 | 568.1 | 0.034 |
| 10 | 22.5 | 11.5 | gangway | 0.86 | 6.20 | 199.2 | 177.9 | 116.0 | 557.5 | 0.069 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | 9.5 | -18.5 | seat row | 0.50 | 7.43 | 194.0 | 191.9 | 177.5 | 614.4 | 0.028 |
| 2 | 18.5 | 9.5 | seat row | 0.50 | 7.46 | 189.4 | 187.3 | 176.1 | 611.6 | 0.029 |
| 3 | -18.5 | -9.5 | seat row | 0.50 | 7.43 | 188.2 | 184.9 | 172.5 | 600.1 | 0.029 |
| 4 | -9.5 | -18.5 | seat row | 0.50 | 7.54 | 187.8 | 185.8 | 170.4 | 590.2 | 0.030 |
| 5 | 18.5 | -9.5 | seat row | 0.50 | 7.52 | 188.7 | 183.5 | 169.3 | 583.9 | 0.030 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 0; agent-steps of seated agents on another row's clearway: 0.

## Deposit check

Person-seconds deposited: 427048.0, of them in excluded cells: 4.160.
