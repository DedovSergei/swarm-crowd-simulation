# Experiment `S_load150_gangways_s2`

**Task 5.10 stage 4 (AMD 26.10.1): Task 5.8's model (the level spacing on the gangway inclines, --stair-flow off): venue S, 150% load (seed 2), standing also on the gangways**

Venue S (analytic seated venue; e_goal from the navigation field: navigation field: 0.050 m cells (1250 x 1250), cache key c76d5f6f3579ec21, content hash 2619c6d0d7ba75aa). 5592 agents (load 150.0%, requested 150%): every one of the 3728 seats and 1864 standing (spawnOvercrowdedCrowd, seed 2; below), buffer N = 8192, 1492 steps (everyone left), readback every 1 step(s). Engine: GPU (CrowdSim).
Model: **queue-aware exit choice, incline speed** (exit choice: 222833 evaluations, 4826 switches, 0 forced choices).
Capacity: **above design capacity (N / design capacity = 1.50)** (the S venue's design capacity 3728, jam capacity 18138: 2513.3 m^2 of occupiable floor at hexagonal packing of 0.40 m bodies).
Commit `b6a787432cf5e90ad155c2cac4df5c3557af5387`, dirty 0, Release build; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.10.1.261008; started 2026-10-22T20:49:11, 35.3 s wall.

Units: 1 model unit = 31.25 m (hard body radius 0.2 m, personal space 0.25 m), 1 model time unit = 17.4907 s (V_MAX = 1.34 m/s), one step DT = 0.1749 s.

## Spawn (overcrowding)

| | |
|---|---|
| seated | 3728 (every seat) |
| standing | **1864** (requested round((1.50 - 1) x 3728) = 1864; at most 2831 = floor(2.5 p/m^2 x 1132.7 m^2)) |
| standing floor | walkway + rear concourse + gangways (the gangway-standing variant), 1132.7 m^2 |
| standing on the walkway / concourse / gangways | 414 / 1034 / 416 |
| **load** | **150.00%** of the seats (requested 150%) |
| standing crowd's mean density | 1.646 p/m^2 |
| initial density, max over 1 m cells >= 0.5 m^2 (cloud-in-cell of the spawn) | standing zones' cells 3.18, all circulation cells 3.18 p/m^2 |

Placement: seeded uniform random over the standing floor (mt19937, seed 2, 13718 draws), a draw kept if a body fits there (outside the fence's collision band, clear of walls, no step face within its radius) and overlaps no agent placed before it.

## Evacuation

| | step | t [s] |
|---|---:|---:|
| t50 | 693 | 121.2 |
| t90 | 1208 | 211.3 |
| t100 | 1492 | 261.0 |

t_p: the step by which ceil(p x 5592) agents had left (per-agent evacuation steps from the metrics), x DT.

## Exits

| exit | clear width [m] | evacuated | nearest exit of [seats] | first [s] | last [s] | mean flow [p/(m min)] | peak flow [p/(m min)] | peak window [s] |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| +x | 5.66 | 539 | 57 | 13.5 | 250.1 | 24.1 | 46.8 | 13.1-23.1 |
| -x | 5.66 | 551 | 58 | 13.5 | 248.4 | 24.8 | 44.7 | 13.1-23.1 |
| +y | 5.66 | 550 | 52 | 13.5 | 249.9 | 24.6 | 46.8 | 13.3-23.3 |
| -y | 5.66 | 544 | 65 | 13.6 | 240.8 | 25.4 | 48.9 | 12.9-22.9 |
| door +x+y y | 1.20 | 426 | 658 | 1.2 | 254.7 | 84.0 | 125.4 | 166.2-176.1 |
| door +x+y x | 1.20 | 422 | 671 | 1.2 | 260.3 | 81.4 | 130.4 | 154.1-164.1 |
| door -x+y y | 1.20 | 437 | 674 | 0.9 | 248.2 | 88.3 | 125.4 | 145.0-155.0 |
| door -x+y x | 1.20 | 425 | 688 | 0.9 | 248.4 | 85.8 | 125.4 | 169.3-179.3 |
| door -x-y y | 1.20 | 417 | 660 | 0.9 | 238.9 | 87.5 | 130.4 | 148.8-158.8 |
| door -x-y x | 1.20 | 426 | 669 | 0.9 | 240.8 | 88.7 | 125.4 | 146.6-156.5 |
| door +x-y y | 1.20 | 421 | 683 | 1.0 | 261.0 | 80.9 | 125.4 | 148.1-158.1 |
| door +x-y x | 1.20 | 434 | 657 | 1.2 | 244.9 | 89.0 | 130.4 | 146.9-156.9 |
| other | | 0 | | | | | | |

Clear width: an avenue's width between its side walls (5.66 m), a concourse door's width through the outer wall (1.20 m); agents are removed past the outer wall's outer face (30.31 m). Nearest exit of: the seated agents whose seat's navigation-field path leads to that exit (static nearest exit, no congestion-aware rerouting). Mean flow: agents through the exit / its active period, from the step of its first to the step of its last evacuation (inclusive), / width. Peak flow: the most agents in any window of 57 consecutive steps (9.97 s; `--peak-window-s` 10), / window / width. Both from the exit counters read every 1 step(s).

## Exit utilisation

| exit | type | clear width [m] | evacuated | share of the evacuated | capacity used |
|---|---|---:|---:|---:|---:|
| +x | avenue | 5.66 | 539 | 9.6% | 26.2% |
| -x | avenue | 5.66 | 551 | 9.9% | 26.8% |
| +y | avenue | 5.66 | 550 | 9.8% | 26.7% |
| -y | avenue | 5.66 | 544 | 9.7% | 26.4% |
| door +x+y y | door | 1.20 | 426 | 7.6% | 97.6% |
| door +x+y x | door | 1.20 | 422 | 7.5% | 96.7% |
| door -x+y y | door | 1.20 | 437 | 7.8% | 100.2% |
| door -x+y x | door | 1.20 | 425 | 7.6% | 97.4% |
| door -x-y y | door | 1.20 | 417 | 7.5% | 95.6% |
| door -x-y x | door | 1.20 | 426 | 7.6% | 97.6% |
| door +x-y y | door | 1.20 | 421 | 7.5% | 96.5% |
| door +x-y x | door | 1.20 | 434 | 7.8% | 99.5% |
| **doors (8)** | door | 9.60 | 3408 | 60.9% | |
| **avenues (4)** | avenue | 22.64 | 2184 | 39.1% | |

**Unused exit width: 0.0 of 32.2 m (0.0%)** (the exits nobody left through). Capacity used: evacuated / (clear width x J x t100), J = 83.6 persons/(m min) (EXIT_FLOW_P_M_MIN, the exit choice's specific-flow capacity), t100 = 261.0 s: the share of the exit's nominal throughput over the whole evacuation used; all exits together 47.7%.

## Gangway utilisation

| gangway | type | head leads to a door | agents on it | share of the agents | last gangway of | share of the evacuated |
|---|---|---|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | straight | yes | 483 | 8.6% | 472 | 8.4% |
| straight +x+y (x wing) 0 | straight | yes | 492 | 8.8% | 492 | 8.8% |
| corner +x+y | corner | **no** | 80 | 1.4% | 80 | 1.4% |
| straight -x+y (y wing) 0 | straight | yes | 480 | 8.6% | 480 | 8.6% |
| straight -x+y (x wing) 0 | straight | yes | 482 | 8.6% | 482 | 8.6% |
| corner -x+y | corner | **no** | 95 | 1.7% | 95 | 1.7% |
| straight -x-y (y wing) 0 | straight | yes | 480 | 8.6% | 480 | 8.6% |
| straight -x-y (x wing) 0 | straight | yes | 482 | 8.6% | 482 | 8.6% |
| corner -x-y | corner | **no** | 88 | 1.6% | 88 | 1.6% |
| straight +x-y (y wing) 0 | straight | yes | 485 | 8.7% | 485 | 8.7% |
| straight +x-y (x wing) 0 | straight | yes | 483 | 8.6% | 477 | 8.5% |
| corner +x-y | corner | **no** | 90 | 1.6% | 90 | 1.6% |
| **straight (8)** | | | 3867 | | 3850 | 68.8% |
| **corner (4)** | | | 353 | | 353 | 6.3% |

Agents on it: the agents whose centre stood on the gangway (its incline, or the barrier's gap at its foot) at the end of at least one step (each agent counted once per gangway; an agent may use several, so the shares add up to more than 100%). Last gangway of: the evacuated agents whose last gangway it was (a partition of those that used any; the rest, 1389, left without one: front-row agents through the walkway). A straight gangway that merges with the corner gangway (the first rows after it starts) counts as the corner gangway there. From the metric counters (GPU: metrics_deposit.comp; CPU: MetricsReference).

## Flows and limits

Windows of 57 steps (9.97 s). Exits: the exit choice's capacity w J (J = 83.6 persons/(m min)); at capacity: a window at >= 80% of it.

| exit | evacuated | first [s] | last [s] | mean flow / w J | peak (10 s) / w J | share of its active windows at capacity |
|---|---:|---:|---:|---:|---:|---:|
| +x | 539 | 13.5 | 250.1 | 0.29 | 0.56 | 0.0% |
| -x | 551 | 13.5 | 248.4 | 0.30 | 0.53 | 0.0% |
| +y | 550 | 13.5 | 249.9 | 0.29 | 0.56 | 0.0% |
| -y | 544 | 13.6 | 240.8 | 0.30 | 0.59 | 0.0% |
| door +x+y y | 426 | 1.2 | 254.7 | 1.00 | 1.50 | 84.6% |
| door +x+y x | 422 | 1.2 | 260.3 | 0.97 | 1.56 | 77.8% |
| door -x+y y | 437 | 0.9 | 248.2 | 1.06 | 1.50 | 88.0% |
| door -x+y x | 425 | 0.9 | 248.4 | 1.03 | 1.50 | 88.0% |
| door -x-y y | 417 | 0.9 | 238.9 | 1.05 | 1.56 | 87.5% |
| door -x-y x | 426 | 0.9 | 240.8 | 1.06 | 1.50 | 88.0% |
| door +x-y y | 421 | 1.0 | 261.0 | 0.97 | 1.50 | 81.5% |
| door +x-y x | 434 | 1.2 | 244.9 | 1.06 | 1.56 | 88.0% |

Mean flow / w J averaged over the doors 1.03, over the avenues 0.30.

Gangways: people = the agents whose first gangway it was (its catchment); departures by the head (concourse, door) / foot (walkway, avenue) / other (into the corner gangway where a straight gangway merges with it; strays); clear = its last departure; area: its floor (seated::gangwayAt sampled every 0.05 m). Loaded: agents of its catchment still to enter it at the window's end; saturated: loaded and its density (occupancy / area) at or above LoS F (2.17 persons/m^2): the gangway itself is full; entry-limited: loaded while it is below LoS F: the row merges feeding it limit. Shares of the windows from its first entry to its clearing. Per window: gangway_flows.csv.

| gangway | width [m] | area [m^2] | people | head / foot / other | first in [s] | clear [s] | mean outflow [p/s] | peak outflow (10 s) [p/s] | loaded | saturated | entry-limited | mean density while loaded [p/m^2] |
|---|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| straight +x+y (y wing) 0 | 1.20 | 18.8 | 483 | 303 / 180 / 20 | 0.2 | 251.7 | 2.00 | 3.41 | 81% | 81% | 0% | 4.51 |
| straight +x+y (x wing) 0 | 1.20 | 18.8 | 481 | 294 / 198 / 60 | 0.2 | 257.3 | 2.15 | 3.71 | 77% | 77% | 0% | 4.40 |
| corner +x+y | 1.20 | 31.2 | 80 | 3 / 78 / 0 | 0.2 | 94.8 | 0.85 | 1.40 | 10% | 0% | 10% | 1.62 |
| straight -x+y (y wing) 0 | 1.20 | 18.8 | 480 | 309 / 172 / 26 | 0.2 | 245.2 | 2.07 | 3.21 | 88% | 88% | 0% | 4.38 |
| straight -x+y (x wing) 0 | 1.20 | 18.8 | 482 | 289 / 193 / 34 | 0.2 | 245.4 | 2.10 | 3.41 | 84% | 84% | 0% | 4.60 |
| corner -x+y | 1.20 | 31.2 | 95 | 4 / 94 / 0 | 0.2 | 104.1 | 0.94 | 1.50 | 18% | 9% | 9% | 2.09 |
| straight -x-y (y wing) 0 | 1.20 | 18.8 | 480 | 296 / 185 / 43 | 0.2 | 235.9 | 2.22 | 3.51 | 83% | 83% | 0% | 4.51 |
| straight -x-y (x wing) 0 | 1.20 | 18.8 | 482 | 299 / 183 / 37 | 0.2 | 237.9 | 2.18 | 3.61 | 88% | 88% | 0% | 4.47 |
| corner -x-y | 1.20 | 31.2 | 88 | 3 / 86 / 0 | 0.2 | 99.5 | 0.89 | 1.40 | 10% | 0% | 10% | 1.76 |
| straight +x-y (y wing) 0 | 1.20 | 18.8 | 479 | 287 / 198 / 59 | 0.2 | 258.0 | 2.11 | 3.61 | 77% | 77% | 0% | 4.50 |
| straight +x-y (x wing) 0 | 1.20 | 18.8 | 483 | 312 / 171 / 29 | 0.2 | 242.1 | 2.12 | 3.21 | 88% | 88% | 0% | 4.43 |
| corner +x-y | 1.20 | 31.2 | 90 | 2 / 88 / 0 | 0.2 | 105.1 | 0.86 | 1.10 | 9% | 0% | 9% | 1.73 |

The last agent out (agent 3293, t100 261.0 s): last gangway straight +x-y (y wing) 0, exit door +x-y (y wall). The gangway that cleared last: straight +x-y (y wing) 0 at 258.0 s.

## Zones

Density thresholds (persons/m^2, at or above): LoS E 1.08, LoS F 2.17 (Fruin 1971), crush 5 (verify against the cited sources; swarm/metrics.hpp). **Headline: the circulation zones** (gangways, walkway, concourse, avenues, exits), for which the thresholds are meant; the seat rows' clearways are reported apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds).

### Circulation zones (headline)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| **all circulation** | 1728 | 1611.8 | 6.52 | 260.1 / 249.9 / 215.5 | 236.6 / 227.7 / 176.3 | 83645.8 | 343567 | 0.270 |
| gangway | 392 | 351.5 | 6.52 | 256.4 / 228.3 / 200.4 | 236.6 / 227.7 / 176.3 | 69563.4 | 199485 | 0.114 |
| walkway | 276 | 257.4 | 4.83 | 230.4 / 162.7 / 0.0 | 217.4 / 152.9 / 0.0 | 0.0 | 31567 | 0.457 |
| avenue | 408 | 384.3 | 2.39 | 236.5 / 2.3 / 0.0 | 211.6 / 1.0 / 0.0 | 0.0 | 28502 | 1.307 |
| exit | 40 | 9.7 | 0.00 | 257.6 / 249.9 / 201.0 | 219.9 / 199.7 / 74.7 | 936.3 | 3350 | 0.890 |
| concourse | 612 | 609.0 | 5.95 | 233.2 / 174.6 / 103.4 | 201.0 / 172.3 / 79.1 | 13146.1 | 80663 | 0.190 |

### Seat rows (reported apart: single-file seat-row queue; area-normalised density not comparable with Fruin thresholds)

| zone | cells | walkable [m^2] | peak density [p/m^2] | time any cell >= E / F / crush [s] | longest cell >= E / F / crush [s] | exposure [person-s] | person-s | mean speed occupied [m/s] |
|---|---:|---:|---:|---|---|---:|---:|---:|
| seat row | 1512 | 918.7 | 7.62 | 220.0 / 215.3 / 209.9 | 220.0 / 215.3 / 208.0 | 110212.2 | 323699 | 0.050 |

A seat row's clearway is 0.50 m deep: one body (0.40 m) wide, so its occupants queue in single file; the density of the 1 m cell over it (persons / its walkable area) reflects the cell's geometry, not a crowd's packing. (The pitch: no floor an agent reaches.)

Per floor cell (1 m x 1 m, 64 x 64 from (-32, -32) m): density = deposited persons (cloud-in-cell) / walkable floor area of the cell; cells below 0.1 m^2 of floor are excluded; peak densities and the hotspot lists count only cells of at least 0.5 m^2 (a partial cell's cloud-in-cell share over a small area is no crowd's density). Time any cell >= threshold: steps at which at least one included cell of the zone was at or above it (readbacks every 1 step(s)), x DT. Longest cell: the cell of the zone with the most such steps. Exposure: person-seconds spent in cells while their density was at or above the crush threshold. Mean speed when occupied: horizontal speed weighted by the persons present (person-time weighted).

## Top 10 hotspot cells (circulation zones)

Ranked by exposure, then time >= LoS F, then time >= LoS E, then peak density.

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -18.5 | 10.5 | gangway | 0.94 | 5.85 | 220.0 | 215.7 | 176.3 | 893.9 | 0.047 |
| 2 | 18.5 | -10.5 | gangway | 0.94 | 5.93 | 222.8 | 215.5 | 170.5 | 873.7 | 0.043 |
| 3 | -18.5 | -10.5 | gangway | 0.94 | 5.94 | 216.0 | 210.1 | 167.7 | 855.6 | 0.044 |
| 4 | -10.5 | -18.5 | gangway | 0.94 | 5.90 | 212.0 | 203.4 | 165.8 | 848.1 | 0.047 |
| 5 | 10.5 | 19.5 | gangway | 0.96 | 5.79 | 220.0 | 216.7 | 156.5 | 829.8 | 0.039 |
| 6 | 10.5 | 18.5 | gangway | 0.94 | 6.03 | 217.2 | 212.2 | 163.0 | 828.8 | 0.040 |
| 7 | -19.5 | -10.5 | gangway | 0.96 | 5.87 | 217.6 | 209.4 | 155.7 | 805.6 | 0.041 |
| 8 | 19.5 | -10.5 | gangway | 0.96 | 5.60 | 224.6 | 214.1 | 149.9 | 767.1 | 0.042 |
| 9 | 18.5 | 10.5 | gangway | 0.94 | 5.87 | 198.3 | 192.2 | 152.3 | 765.5 | 0.060 |
| 10 | 14.5 | -10.5 | gangway | 0.94 | 5.71 | 229.1 | 227.7 | 153.0 | 762.1 | 0.077 |

The top 5 seat-row cells, apart (single-file seat-row queue; area-normalised density not comparable with Fruin thresholds):

| # | x [m] | y [m] | zone | walkable [m^2] | peak [p/m^2] | >= E [s] | >= F [s] | >= crush [s] | exposure [person-s] | mean speed [m/s] |
|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|
| 1 | -9.5 | 18.5 | seat row | 0.50 | 7.52 | 214.6 | 213.0 | 208.0 | 729.6 | 0.025 |
| 2 | 18.5 | -9.5 | seat row | 0.50 | 7.45 | 216.5 | 215.3 | 206.9 | 725.8 | 0.025 |
| 3 | -18.5 | 9.5 | seat row | 0.50 | 7.47 | 216.0 | 214.6 | 206.7 | 725.8 | 0.025 |
| 4 | 9.5 | 18.5 | seat row | 0.50 | 7.35 | 213.9 | 212.2 | 203.6 | 719.1 | 0.025 |
| 5 | -18.5 | -9.5 | seat row | 0.50 | 7.47 | 210.9 | 209.2 | 205.2 | 714.5 | 0.026 |

## Rows (INV-row)

0 row changes (a move from one row's clearway onto another's without a gangway, the walkway, an avenue or the concourse in between: across a riser, a seat block or the barrier; tools/venue_s.hpp Checker, every step). Rows entered from an aisle (a stray from a gangway onto another row's clearway, not INV-row): 307; agent-steps of seated agents on another row's clearway: 3455.

## Deposit check

Person-seconds deposited: 670334.9, of them in excluded cells: 3067.951.

## Checks (after every step)

| check | result | values |
|---|---|---|
| overlap | PASS | all 33060 overlapping pair-steps: p99 0.0057, max 0.0123 of BODY_DIAM (limits 0.05 / 0.20, every case: analytic venue, no exemption); crowd p99 0.0057 max 0.0123; venue-geometry 1: p99 0.0001 max 0.0001 |
| neighbour grid | PASS | pairs from non-adjacent start cells 0, max displacement 0.00751 (bound 0.01860) |
| floors | PASS | centre in solid 0, below floor + BODY_RADIUS - 1e-4 0 agent-steps; airborne runs 8 (longest 1 steps) |
| fence | PASS | midline crossings 0, in the collision band 0 agent-steps |
| walls | PASS | clearance < BODY_RADIUS - 3e-4: 0 agent-steps (no wall that close) |
| speed | PASS | max |v_xy| 0.750000 (V_MAX 0.75), 0 above |
| density ceiling | PASS | peak 5.95 p/m^2 over fully walkable 1 m cells (ceiling 7.96) |
| INV-row | PASS | 0 row changes |
| step-up rules | PASS | floor rises above MAX_STEP_UP 0; climbs over a vertical face (any height, onto a floor above the start floor) 0 (max rise 0.000 m); faces crossed in a net descent 146 (information) |
| no wall tops, no tunnelling | PASS | agent-steps over a seat block / barrier / wall column 0; steps through one 0; fence-side changes 0 |

Plausibility: tools/plausibility.hpp (test_gpu section 31's checks, the analytic venue); the venue checks: tools/venue_s.hpp Checker (test_gpu sections 36-40).
