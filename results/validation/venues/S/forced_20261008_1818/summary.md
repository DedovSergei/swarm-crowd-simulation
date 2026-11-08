# Venue S: forced-motion validation (Task 5.4 stage 5)

venue_probe forced | commit 34ce181213ce4c8dd3079f50c638860253835407 (dirty 0) | Release | 2026-10-08 18:18 | AMD  Radeon RX 7800 XT | 4.3.0 Core Profile Context 26.8.1.260810 | power throttling off (SetProcessInformation, EXECUTION_SPEED)

The router is bypassed: every agent's desired direction e_goal comes from a table written before every step from the state the
step starts from (physics.comp TEST_DRIVE_TABLE; the CPU reference: setDriveTable), as a field of the agent's cell and plan
(tools/venue_s.hpp). V0 = 1.34 m/s. Checks after every step (venue_s::Checker; (e) also plausibility::runEvacuation).

## (a) INV-row: every seat occupied, every agent driven towards the pitch / away from it for 300 steps (52.5 s)

**towards the pitch** (3728 agents):
  - agent-steps off the agent's own clearway: 0; front-row agents that reached the walkway: 0
  - agent-steps 1118400; row changes (clearway to clearway without an aisle: across a riser, seat block or the barrier) 0; entries onto another row's clearway from an aisle 0 (seated agents' agent-steps there 0); in a solid column 0; paths through a seat block / barrier / wall (tunnelling) 0
  - walls: min clearance none within the probe (BODY_RADIUS 0.2000 m), below BODY_RADIUS - 3e-4: 0 agent-steps; fence crossings 0
  - step-up: max floor rise in a step 0.0000 m, rises above MAX_STEP_UP 0; climbs over a vertical face (a discontinuous floor rise onto a floor above the start floor, any height) 0; faces crossed upwards in a net descent (information) 0 (max 0.0000 m)

**away from the pitch** (3728 agents):
  - agent-steps off the agent's own clearway: 0; front-row agents that reached the walkway: 0
  - agent-steps 1118400; row changes (clearway to clearway without an aisle: across a riser, seat block or the barrier) 0; entries onto another row's clearway from an aisle 0 (seated agents' agent-steps there 0); in a solid column 0; paths through a seat block / barrier / wall (tunnelling) 0
  - walls: min clearance none within the probe (BODY_RADIUS 0.2000 m), below BODY_RADIUS - 3e-4: 0 agent-steps; fence crossings 0
  - step-up: max floor rise in a step 0.0000 m, rises above MAX_STEP_UP 0; climbs over a vertical face (a discontinuous floor rise onto a floor above the start floor, any height) 0; faces crossed upwards in a net descent (information) 0 (max 0.0000 m)

## (b) Junctions: per row, one segment's agents driven along the row towards one adjacent gangway (then down it and out)

| junction | agents | entered the gangway | first / median / last entry | not entered |
|---|---:|---:|---:|---:|
| dead-end segment -> straight gangway | 1904 | 1904 | 0.7 s / 25.5 s / 152.2 s | 0 |
| segment -> straight gangway | 1824 | 1824 | 0.7 s / 34.1 s / 153.4 s | 0 |
| segment -> corner gangway | 1824 | 1824 | 0.7 s / 100.0 s / 309.6 s | 0 |

Per row (agents / entered / last entry), dead-end segment -> straight gangway | segment -> straight gangway | segment -> corner gangway:

| row | dead-end -> straight | segment -> straight | segment -> corner |
|---:|---|---|---|
| 0 | 112 / 112 / 37.1 s | 8 / 8 / 0.7 s | 8 / 8 / 0.7 s |
| 1 | 112 / 112 / 50.9 s | 16 / 16 / 1.6 s | 16 / 16 / 1.7 s |
| 2 | 112 / 112 / 60.5 s | 32 / 32 / 3.5 s | 32 / 32 / 6.1 s |
| 3 | 112 / 112 / 70.3 s | 40 / 40 / 7.5 s | 40 / 40 / 12.6 s |
| 4 | 112 / 112 / 80.1 s | 56 / 56 / 13.1 s | 56 / 56 / 25.4 s |
| 5 | 112 / 112 / 91.0 s | 72 / 72 / 26.9 s | 72 / 72 / 44.6 s |
| 6 | 112 / 112 / 101.1 s | 80 / 80 / 35.5 s | 80 / 80 / 60.3 s |
| 7 | 112 / 112 / 107.9 s | 96 / 96 / 49.3 s | 96 / 96 / 80.3 s |
| 8 | 112 / 112 / 119.5 s | 104 / 104 / 63.1 s | 104 / 104 / 100.7 s |
| 9 | 112 / 112 / 127.9 s | 120 / 120 / 81.3 s | 120 / 120 / 123.7 s |
| 10 | 112 / 112 / 134.5 s | 136 / 136 / 105.6 s | 136 / 136 / 152.7 s |
| 11 | 112 / 112 / 140.3 s | 144 / 144 / 116.8 s | 144 / 144 / 179.5 s |
| 12 | 112 / 112 / 152.2 s | 160 / 160 / 135.7 s | 160 / 160 / 210.2 s |
| 13 | 112 / 112 / 148.5 s | 168 / 168 / 153.4 s | 168 / 168 / 241.4 s |
| 14 | 112 / 112 / 139.1 s | 184 / 184 / 148.5 s | 184 / 184 / 287.7 s |
| 15 | 112 / 112 / 102.3 s | 200 / 200 / 132.1 s | 200 / 200 / 309.6 s |
| 16 | 112 / 112 / 41.1 s | 208 / 208 / 91.1 s | 208 / 208 / 285.8 s |

Checks, dead-end segment -> straight gangway (1258 steps, everyone out at 220.0 s):
  - agent-steps 1306253; row changes (clearway to clearway without an aisle: across a riser, seat block or the barrier) 0; entries onto another row's clearway from an aisle 458 (seated agents' agent-steps there 14302); in a solid column 0; paths through a seat block / barrier / wall (tunnelling) 0
  - walls: min clearance none within the probe (BODY_RADIUS 0.2000 m), below BODY_RADIUS - 3e-4: 0 agent-steps; fence crossings 0
  - step-up: max floor rise in a step 0.0169 m, rises above MAX_STEP_UP 0; climbs over a vertical face (a discontinuous floor rise onto a floor above the start floor, any height) 0; faces crossed upwards in a net descent (information) 10 (max 0.0105 m)

Checks, segment -> straight gangway (1232 steps, everyone out at 215.5 s):
  - agent-steps 1235519; row changes (clearway to clearway without an aisle: across a riser, seat block or the barrier) 0; entries onto another row's clearway from an aisle 169 (seated agents' agent-steps there 2657); in a solid column 0; paths through a seat block / barrier / wall (tunnelling) 0
  - walls: min clearance none within the probe (BODY_RADIUS 0.2000 m), below BODY_RADIUS - 3e-4: 0 agent-steps; fence crossings 0
  - step-up: max floor rise in a step 0.0168 m, rises above MAX_STEP_UP 0; climbs over a vertical face (a discontinuous floor rise onto a floor above the start floor, any height) 0; faces crossed upwards in a net descent (information) 12 (max 0.0219 m)

Checks, segment -> corner gangway (1972 steps, everyone out at 344.9 s):
  - agent-steps 1883983; row changes (clearway to clearway without an aisle: across a riser, seat block or the barrier) 0; entries onto another row's clearway from an aisle 0 (seated agents' agent-steps there 0); in a solid column 0; paths through a seat block / barrier / wall (tunnelling) 0
  - walls: min clearance none within the probe (BODY_RADIUS 0.2000 m), below BODY_RADIUS - 3e-4: 0 agent-steps; fence crossings 0
  - step-up: max floor rise in a step 0.0188 m, rises above MAX_STEP_UP 0; climbs over a vertical face (a discontinuous floor rise onto a floor above the start floor, any height) 0; faces crossed upwards in a net descent (information) 0 (max 0.0000 m)

## (c) Gangways: 17 agents per gangway (one per row band) driven down to the walkway / up to the rear concourse

| gangway | down: arrived / agents, last | up: arrived / agents, last |
|---|---|---|
| quadrant 0 wing 0 straight | 17 / 17, 22.2 s | 17 / 17, 10.3 s |
| quadrant 0 wing 1 straight | 17 / 17, 15.7 s | 17 / 17, 10.3 s |
| quadrant 1 wing 0 straight | 17 / 17, 22.7 s | 17 / 17, 10.3 s |
| quadrant 1 wing 1 straight | 17 / 17, 15.7 s | 17 / 17, 10.3 s |
| quadrant 2 wing 0 straight | 17 / 17, 22.2 s | 17 / 17, 10.3 s |
| quadrant 2 wing 1 straight | 17 / 17, 15.7 s | 17 / 17, 10.3 s |
| quadrant 3 wing 0 straight | 17 / 17, 22.7 s | 17 / 17, 10.3 s |
| quadrant 3 wing 1 straight | 17 / 17, 15.7 s | 17 / 17, 10.3 s |
| quadrant 0 corner | 17 / 17, 16.4 s | 17 / 17, 21.9 s |
| quadrant 1 corner | 17 / 17, 16.4 s | 17 / 17, 21.9 s |
| quadrant 2 corner | 17 / 17, 16.4 s | 17 / 17, 21.9 s |
| quadrant 3 corner | 17 / 17, 16.4 s | 17 / 17, 21.9 s |

Checks, down:
  - agent-steps 37590; row changes (clearway to clearway without an aisle: across a riser, seat block or the barrier) 0; entries onto another row's clearway from an aisle 0 (seated agents' agent-steps there 0); in a solid column 0; paths through a seat block / barrier / wall (tunnelling) 0
  - walls: min clearance none within the probe (BODY_RADIUS 0.2000 m), below BODY_RADIUS - 3e-4: 0 agent-steps; fence crossings 0
  - step-up: max floor rise in a step 0.0002 m, rises above MAX_STEP_UP 0; climbs over a vertical face (a discontinuous floor rise onto a floor above the start floor, any height) 0; faces crossed upwards in a net descent (information) 0 (max 0.0000 m)
Checks, up:
  - agent-steps 16532; row changes (clearway to clearway without an aisle: across a riser, seat block or the barrier) 0; entries onto another row's clearway from an aisle 0 (seated agents' agent-steps there 0); in a solid column 0; paths through a seat block / barrier / wall (tunnelling) 0
  - walls: min clearance none within the probe (BODY_RADIUS 0.2000 m), below BODY_RADIUS - 3e-4: 0 agent-steps; fence crossings 0
  - step-up: max floor rise in a step 0.1172 m, rises above MAX_STEP_UP 0; climbs over a vertical face (a discontinuous floor rise onto a floor above the start floor, any height) 0; faces crossed upwards in a net descent (information) 0 (max 0.0000 m)

## (d) Passages and exits

| passage | arrived / agents | last arrival |
|---|---:|---:|
| walkway ring, quadrant 0 | 8 / 8 | 15.9 s |
| walkway ring, quadrant 1 | 8 / 8 | 15.9 s |
| walkway ring, quadrant 2 | 8 / 8 | 15.9 s |
| walkway ring, quadrant 3 | 8 / 8 | 15.9 s |
| rear concourse ring, quadrant 0 | 4 / 4 | 42.3 s |
| rear concourse ring, quadrant 1 | 4 / 4 | 42.3 s |
| rear concourse ring, quadrant 2 | 4 / 4 | 42.3 s |
| rear concourse ring, quadrant 3 | 4 / 4 | 42.3 s |
| avenue +y out through its exit | 4 / 4 | 14.5 s |
| avenue -x out through its exit | 4 / 4 | 14.5 s |
| avenue -y out through its exit | 4 / 4 | 14.5 s |
| avenue +x out through its exit | 4 / 4 | 14.5 s |
| concourse exit, quadrant 0 wing 0 | 2 / 2 | 1.6 s |
| concourse exit, quadrant 0 wing 1 | 2 / 2 | 1.6 s |
| concourse exit, quadrant 1 wing 0 | 2 / 2 | 1.6 s |
| concourse exit, quadrant 1 wing 1 | 2 / 2 | 1.6 s |
| concourse exit, quadrant 2 wing 0 | 2 / 2 | 1.6 s |
| concourse exit, quadrant 2 wing 1 | 2 / 2 | 1.6 s |
| concourse exit, quadrant 3 wing 0 | 2 / 2 | 1.6 s |
| concourse exit, quadrant 3 wing 1 | 2 / 2 | 1.6 s |

Checks, rings:
  - agent-steps 29184; row changes (clearway to clearway without an aisle: across a riser, seat block or the barrier) 0; entries onto another row's clearway from an aisle 0 (seated agents' agent-steps there 0); in a solid column 0; paths through a seat block / barrier / wall (tunnelling) 0
  - walls: min clearance none within the probe (BODY_RADIUS 0.2000 m), below BODY_RADIUS - 3e-4: 0 agent-steps; fence crossings 0
  - step-up: max floor rise in a step 0.0000 m, rises above MAX_STEP_UP 0; climbs over a vertical face (a discontinuous floor rise onto a floor above the start floor, any height) 0; faces crossed upwards in a net descent (information) 0 (max 0.0000 m)
Checks, exits:
  - agent-steps 1440; row changes (clearway to clearway without an aisle: across a riser, seat block or the barrier) 0; entries onto another row's clearway from an aisle 0 (seated agents' agent-steps there 0); in a solid column 0; paths through a seat block / barrier / wall (tunnelling) 0
  - walls: min clearance none within the probe (BODY_RADIUS 0.2000 m), below BODY_RADIUS - 3e-4: 0 agent-steps; fence crossings 0
  - step-up: max floor rise in a step 0.0000 m, rises above MAX_STEP_UP 0; climbs over a vertical face (a discontinuous floor rise onto a floor above the start floor, any height) 0; faces crossed upwards in a net descent (information) 0 (max 0.0000 m)

## (e) Dense: every seat occupied (3728), along the row to the nearer gangway, down it, along the walkway, out through the nearer avenue

plausibility::runEvacuation, analytic venue (no exemption: every overlap case held to the crowd limits):

```
evacuated at step 2146 (375.3 s); t50 179.6 s, t90 331.3 s
all overlaps: 15358 pair-steps, p99 0.0005, max 0.0039 of BODY_DIAM
crowd cases: 15350 pair-steps, p99 0.0005, max 0.0020
venue-geometry cases (fall, step-down, ramp): 8 pair-steps, p99 0.0039, max 0.0039
overlap limits (p99 <= 0.05, max <= 0.20, ALL cases): PASS
neighbour grid: max displacement 0.00796 (bound 0.01860), misses 0
floors: centre in solid 0, below floor + R 0; airborne runs 8, longest 1; step-downs 0
fence: crossings 0, band 0; walls: violations 0, min clearance -1.000000
speed: max 0.750000, above V_MAX 0; density: peak 5.95 p/m^2 over fully walkable cells (ceiling 7.96)
all plausibility checks: PASS
```

Overlap depth by population and zone (pair-steps, share, p50 / p99 / max, above 2 / 5 / 10 / 20% of BODY_DIAM):

```
all                                            15358  p50 0.0001  p99 0.0005  max 0.0039  > 2%     0  > 5%     0  > 10%    0  > 20%    0
crowd, tread                                   15327  p50 0.0001  p99 0.0005  max 0.0020  > 2%     0  > 5%     0  > 10%    0  > 20%    0
crowd, aisle                                      21  p50 0.0002  p99 0.0005  max 0.0005  > 2%     0  > 5%     0  > 10%    0  > 20%    0
crowd, walkway                                     2  p50 0.0001  p99 0.0002  max 0.0002  > 2%     0  > 5%     0  > 10%    0  > 20%    0
fall / step-down / landing, tread                  1  p50 0.0003  p99 0.0003  max 0.0003  > 2%     0  > 5%     0  > 10%    0  > 20%    0
fall / step-down / landing, aisle                  1  p50 0.0001  p99 0.0001  max 0.0001  > 2%     0  > 5%     0  > 10%    0  > 20%    0
riser / step ramp, tread                           4  p50 0.0003  p99 0.0011  max 0.0011  > 2%     0  > 5%     0  > 10%    0  > 20%    0
riser / step ramp, aisle                           2  p50 0.0001  p99 0.0039  max 0.0039  > 2%     0  > 5%     0  > 10%    0  > 20%    0
```

Checks (venue_s::Checker):
  - agent-steps 4191921; row changes (clearway to clearway without an aisle: across a riser, seat block or the barrier) 0; entries onto another row's clearway from an aisle 574 (seated agents' agent-steps there 4561); in a solid column 0; paths through a seat block / barrier / wall (tunnelling) 0
  - walls: min clearance none within the probe (BODY_RADIUS 0.2000 m), below BODY_RADIUS - 3e-4: 0 agent-steps; fence crossings 0
  - step-up: max floor rise in a step 0.0233 m, rises above MAX_STEP_UP 0; climbs over a vertical face (a discontinuous floor rise onto a floor above the start floor, any height) 0; faces crossed upwards in a net descent (information) 31 (max 0.0113 m)

## (f) The step-up rules over every scenario above (10939222 agent-steps)

- floor rises above MAX_STEP_UP (0.30 m) in one step: 0 (max rise 0.1172 m)
- climbs over a vertical face (a discontinuous floor rise, any height, along a step's path onto a floor above the start-of-step floor; checked every 2 mm): 0
- information: faces crossed upwards within a step that ends at or below its start floor (the path dipped onto the incline first; the step-up rule never blocks level or downward moves): 53 (max 0.0219 m)
- paths through a seat block, the barrier or a wall: 0

## (g) CPU/GPU equivalence on venue S (the dense scenario's drive field) and the golden hashes

- one step from the GPU state after 200 steps (3598 active), CPU counting: cell table identical, gridID sequence differs at 0 slots, (gridID, boidID) pairs at 3431 (counting: boidID order within a cell); |dpos| > 2e-4 for 0 agents (0.000%, limit < 0.5%), max 1.79e-07
- one step from the GPU state after 200 steps (3598 active), CPU bitonic: cell table identical, gridID sequence differs at 0 slots, (gridID, boidID) pairs at 0; |dpos| > 2e-4 for 0 agents (0.000%, limit < 0.5%), max 1.79e-07
- CPU thread invariance (counting, 1 thread vs 20, 100 steps): trajectory hashes identical
- determinism over 250 steps: two GPU runs identical, two CPU runs identical (trajectory hashes)
- golden (FNV-1a 64 of the state after 250 steps of the dense scenario from the full seat spawn): GPU 26197a2f52864a16, CPU counting fd0f346cb70ccd0d, CPU bitonic f17ecc0c3995dc54 (active 3508 / 3506 / 3506)
- the dense scenario to the last agent out: GPU step 2146, CPU counting step 2142 (-0.19%; limit +-5%); CPU run 10 s

Total time 67 s.
