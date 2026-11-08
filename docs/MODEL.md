# The crowd model

A short description of what one simulation step computes. The constants live in `include/swarm/sim_params.hpp`, the GPU code in
`shaders/physics.comp` and `shaders/venue_seated.glsl`, the CPU port in `src/cpu_crowd_sim.cpp`. Measured results: `results/RESULTS.md`.

Literature values below are as reported in the cited sources; **they have not yet been checked against the originals.**

## Units

Model units are scaled so that one length unit is 31.25 m and one time unit 17.490671 s. One fixed step `DT` = 0.01 model units =
0.1749 s of real time. Real values reach the simulation through three constants only: gravity (9.81 m/s^2), the relaxation time
`TAU_RELAX` (0.5 s) and the headway time gap `T_HEADWAY` (0.3 s), each folded into model units.

## Pipeline

Each step runs four compute stages on double-buffered agent state:

1. **hash** (`calc_grid.comp`): each agent's 2D grid cell; evacuated agents get a sentinel and sort to the tail.
2. **sort** (`bitonic_sort.comp`, `bitonic_sort_shared.comp`): a bitonic network over (cell, agent); the passes with j < 512 run in shared memory.
3. **cells** (`reorder.comp`): each cell's range in the sorted list, and a gather of the agents' state into slot order.
4. **physics** (`physics.comp`): the optional exit choice pass, then predict, the projection iterations and the final pass.

No readback stalls the pipeline: the viewer reads small counters only after their fence has signalled, and never waits.

## Bodies and speeds

- **Hard body:** a vertical disk of radius 0.20 m, used for every hard contact. The centre rests a body radius above the floor and keeps a
  body radius from walls.
- **Personal space:** radius 0.25 m (Fruin's body ellipse equivalent, Fruin 1971), the support of a soft repulsion.
- **Free speed:** `V_MAX` = 1.34 m/s (Weidmann 1993).

## One agent's step

- **Desired direction e_goal.** On the terrace, the unit vector to a hand router's waypoint. On a seated venue, the direction of the navigation field.
- **Headway speed** (collision-free speed model, Tordeux, Chraibi & Seyfried 2016): `s` is the horizontal centre distance to the nearest agent
  ahead within 0.40 m of the path; `v_des = clamp((s - 0.40 m) / T_HEADWAY, 0, v0)`, with `v0 = V_MAX` on level floors. In a mutual standoff (each
  agent ahead in the other's lane), only the agent that has the other more directly ahead counts it.
- **Incline speed** (seated venues): on a gangway the free speed blends from `V_MAX` to 0.58 m/s up or 0.655 m/s down, by the slope along
  e_goal (a smoothstep up to tan 27 deg). Values: Fruin (1971) as tabulated by Fujiyama & Tyler (2004).
- **Stair spacing** (seated venues): on a gangway the time gap blends the same way from `T_HEADWAY` to 0.625 s up / 0.65 s down (EMPIRICAL, the default;
  calibrated to the measured stair maxima of Burghardt, Seyfried & Klingsch 2013, 1.22 / 1.25 persons/(m s)) or 0.75 / 0.78 s (CONSERVATIVE; the Green
  Guide's 66 persons/(m min)). Level floors keep the level rule bit for bit.
- **Direction:** `e_dir = normalize(e_goal + sum_j K_SEP (1 - d_ij / R_SEP)^2 n_ij)` over neighbours closer than `R_SEP` = 0.50 m; `K_SEP` = 100.
- **Driving term** (social force model, Helbing & Molnar 1995): `dv/dt = (v_des e_dir - v) / TAU_RELAX + a_obs`, integrated exactly for constant inputs, with
  `a_obs` a torso-height obstacle avoidance. The velocity's component along e_goal is then capped at `v_des`: braking is immediate.
- **Gravity** acts on the vertical velocity; there is no upward self-propulsion, and `|v_xy| <= V_MAX`.
- **Static contacts:** the analytic pitch fence with continuous collision, the floor under the centre, the walls (16 feelers on the baked terrace, an
  exact query on seated venues) and a sweep back along the step for a centre left in solid.
- **Hard-body projection:** 32 Jacobi iterations move overlapping pairs apart in XY, each bounded by the fence and the agent's wall plane. The
  projection does not change the velocity. K = 32 comes from a sweep (`results/validation/level_calibration`).
- **Step-up limit:** the last operation of every step, for every agent. A horizontal move is blocked if the floor at its end lies more than 0.30 m above the
  start-of-step floor, or if the move climbs a wall-steep face. A blocked move slides along the face. Level and downward moves are never blocked.

The calibration of `T_HEADWAY` and `K_SEP` fits Weidmann's fundamental diagram (`results/validation/fundamental_diagram`: RMS speed error 0.126 m/s, maximum flow
80.4 persons/(m min)).

## Venues

| venue | geometry | capacity |
|---|---|---:|
| terrace | a baked signed distance field of `stadium.obj` (130^3 floats), bare terraces without seats, a hand router | 4 096 by design |
| S | analytic seated venue, 17 rows, 8 concourse doors of 1.20 m and 4 avenues | 3 728 seats |
| M | generated, 43 rows, 28 doors of 1.20 m | 15 832 seats |
| L | generated, 95 rows, 44 doors of 2.30 m | 63 424 seats |

The seated venues are heightfields of boxes and gangway inclines with an exact signed distance in closed form (`shaders/venue_seated.glsl`, mirrored in
`src/venue.cpp`). Row depth 0.80 m, rise 0.40 m, clearway 0.50 m, seat block 0.30 m deep and 0.85 m above its tread, gangways 1.20 m on a 26.57 degree incline.
Gangways follow the Green Guide's rule of at most 28 seats between gangways and 14 in a dead end. The door width follows its 66 persons/(m min) over 8 minutes.

**INV-row:** in a seated venue agents leave along their row to a gangway; they never cross a row. Every seated evacuation in `results/evacuation` records 0 row changes.
The terrace is exempt: its bare treads let agents drop to the row below.

## Navigation field

A traversability grid of 0.05 m cells holds each cell's floor height and whether a standing body fits there, by the physics' own contact rules. A Lazy Theta* search
(Nash, Koenig & Tovey 2010) over the reversed legal moves gives every cell its walking distance to an exit and the anchor of its shortest polyline. e_goal is the
unit vector from the agent to its cell's anchor, without its component into a wall or step face beside the agent. Seat rows are exits only: no route enters a row from outside it.
The tables are built on the CPU when a venue is first used and cached in `navcache/`, keyed by the venue's parameters.

## Exit choice

Default on seated venues: **queue-aware.** Every agent holds an assigned exit and steers on that exit's own field. Every 3 s all agents evaluate, on the same counts, for each of
the 24 candidates of their cell (the 2 nearest avenues, the nearest door, then the nearest others):

`E_e = d_e / V0 + A_e / (w_e J)`

with `d_e` the walking distance, `V0` = 1.34 m/s, `A_e` the agents assigned to e and nearer to it, `w_e` the exit's clear width and `J` = 83.6 persons/(m min), the model's own measured door flow.
An agent may switch if the gain exceeds 10% of E and 5 s; per exit at most 10% of its assigned agents (at least one) switch per evaluation, the largest gains first. All results use integer
atomics, so the choice is deterministic. The route choice does not consider gangway congestion: a known limitation.

Options: `--exit-choice nearest|queue-aware`, `--incline-speed 0|1`, `--stair-flow off|empirical|conservative`.

## Safety metrics

Write-only side outputs after a step; the simulation never reads them. Density uses 1 m x 1 m floor cells with a cloud-in-cell deposit in integer arithmetic, so the deposited total
is exact. Thresholds, in persons/m^2: LoS E 1.08 and LoS F 2.17 (Fruin 1971), crush risk 5 (Fruin 1993, Still 2000). Crush exposure is person-seconds at or above the crush threshold.
On seated venues the headline metrics cover circulation zones only; a seat row is a single-file queue, so its area-normalised density is reported apart.

## Plausibility checks

After every step of a full evacuation (`tools/plausibility.hpp`): overlap depth of pairs closer than a body diameter (crowd cases p99 <= 5%, max <= 20%), a valid neighbour grid, no centre in solid or
below its rest height, no fence crossing, wall clearance, `|v_xy| <= V_MAX`, peak density at most 7.96 persons/m^2 (hexagonal packing 7.22 plus the cloud-in-cell allowance). Venue-geometry
overlaps (falls off bare treads, the bake's riser ramps) are exempt on the baked terrace only; seated venues meet the crowd limits for all pairs.

## CPU reference and reproducibility

`CpuCrowdSim` ports the compute passes 1:1 with OpenMP. The only intentional difference is the exact CPU sampler instead of 8-bit-weight hardware trilinear filtering; everything else is rounding-level.
Results are bit-identical for any thread count. Every shared constant is checked GPU = CPU bit for bit (`test_gpu`'s `parity.constants`), and `PORTED_SHADERS_FNV1A` pins the ported shaders.

**Golden state:** an FNV-1a 64 hash of the raw agent state after 250 steps, for the GPU and both CPU sort modes (`tools/golden_state.hpp`). GPU pins belong to one driver (`GOLDEN_DRIVER`: AMD 26.10.1.261008);
on another driver the checks warn and compare the CPU pins only. A driver changes GPU results bit for bit, like a different rounding: comparing runs across drivers needs the driver string
every `summary.json` records (`results/evacuation/history_amd_26.8.1` holds the previous driver's matrices). A change that alters a pin must be intentional and re-pinned after re-running the checks.

## Tests

`test_gpu` (`--quick` / `--long`), `test_clock` and `SWARM --selftest-ui` print sections named `<area>.<name>`: `engine`, `parity`, `physics`, `nav`, `venue`, `metrics`, `validation`, `perf`, `viewer`.

## Sources (not yet checked against the originals)

- Burghardt, Seyfried & Klingsch (2013), measured stair flows.
- Fruin (1971), *Pedestrian Planning and Design*; Fruin (1993) and Still (2000), crush risk.
- Fujiyama & Tyler (2004), *An explicit study on walking speeds of pedestrians on stairs*, 10th TRANSED.
- Guide to Safety at Sports Grounds ("Green Guide"), 6th ed. (2018).
- Helbing & Molnar (1995), Phys. Rev. E 51, 4282.
- Nash, Koenig & Tovey (2010), *Lazy Theta\**, AAAI.
- Tordeux, Chraibi & Seyfried (2016), *Collision-free speed model for pedestrian dynamics*, Traffic and Granular Flow '15.
- Weidmann (1993), *Transporttechnik der Fussgaenger*, ETH Zuerich, Schriftenreihe IVT Nr. 90.
