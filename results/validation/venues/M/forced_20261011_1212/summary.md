# Venue M: forced-motion validation (Task 5.4 stage 5)

venue_probe forced | commit 03f06b747068f28c722980b9870da95c1d91036c (dirty 0) | Release | 2026-10-11 12:12 | AMD  Radeon RX 7800 XT | 4.3.0 Core Profile Context 26.8.1.260810 | power throttling off (SetProcessInformation, EXECUTION_SPEED)

The router is bypassed: every agent's desired direction e_goal comes from a table written before every step from the state the
step starts from (physics.comp TEST_DRIVE_TABLE; the CPU reference: setDriveTable), as a field of the agent's cell and plan
(tools/venue_s.hpp). V0 = 1.34 m/s. Checks after every step (venue_s::Checker; (e) also plausibility::runEvacuation).

Rows of (a)-(c): rows 0, 3, 9, 13, 17, 18, 20, 21, 33, 37, 39, 42 (of 0 .. 42, in all 8 wings: the first, middle and last rows, each straight gangway's first row and first seated row, and 5 drawn with seed 7). Step limits x 2.53 (the venue's rows / 17).

## (a) INV-row: every seat occupied, every agent driven towards the pitch / away from it for 300 steps (52.5 s)

**towards the pitch** (4400 agents):
  - agent-steps off the agent's own clearway: 0; front-row agents that reached the walkway: 0
  - agent-steps 1320000; row changes (clearway to clearway without an aisle: across a riser, seat block or the barrier) 0; entries onto another row's clearway from an aisle 0 (seated agents' agent-steps there 0); in a solid column 0; paths through a seat block / barrier / wall (tunnelling) 0
  - walls: min clearance none within the probe (BODY_RADIUS 0.2000 m), below BODY_RADIUS - 3e-4: 0 agent-steps; fence crossings 0
  - step-up: max floor rise in a step 0.0000 m, rises above MAX_STEP_UP 0; climbs over a vertical face (a discontinuous floor rise onto a floor above the start floor, any height) 0; faces crossed upwards in a net descent (information) 0 (max 0.0000 m)

**away from the pitch** (4400 agents):
  - agent-steps off the agent's own clearway: 0; front-row agents that reached the walkway: 0
  - agent-steps 1320000; row changes (clearway to clearway without an aisle: across a riser, seat block or the barrier) 0; entries onto another row's clearway from an aisle 0 (seated agents' agent-steps there 0); in a solid column 0; paths through a seat block / barrier / wall (tunnelling) 0
  - walls: min clearance none within the probe (BODY_RADIUS 0.2000 m), below BODY_RADIUS - 3e-4: 0 agent-steps; fence crossings 0
  - step-up: max floor rise in a step 0.0000 m, rises above MAX_STEP_UP 0; climbs over a vertical face (a discontinuous floor rise onto a floor above the start floor, any height) 0; faces crossed upwards in a net descent (information) 0 (max 0.0000 m)

## (b) Junctions: per row, one segment's agents driven along the row towards one adjacent gangway (then down it and out)

| junction | agents | entered the gangway | first / median / last entry | not entered |
|---|---:|---:|---:|---:|
| dead-end segment -> straight gangway | 1344 | 1344 | 0.7 s / 7.9 s / 52.1 s | 0 |
| segment -> straight gangway | 3056 | 3056 | 0.7 s / 19.8 s / 145.5 s | 0 |
| segment -> corner gangway | 3056 | 3056 | 0.7 s / 27.6 s / 424.5 s | 0 |

Per row (agents / entered / last entry), dead-end segment -> straight gangway | segment -> straight gangway | segment -> corner gangway:

| row | dead-end -> straight | segment -> straight | segment -> corner |
|---:|---|---|---|
| 0 | 112 / 112 / 21.7 s | 8 / 8 / 0.7 s | 8 / 8 / 0.7 s |
| 3 | 112 / 112 / 21.5 s | 40 / 40 / 4.0 s | 40 / 40 / 6.3 s |
| 9 | 112 / 112 / 17.5 s | 120 / 120 / 15.9 s | 120 / 120 / 27.1 s |
| 13 | 112 / 112 / 26.4 s | 168 / 168 / 35.0 s | 168 / 168 / 66.1 s |
| 17 | 112 / 112 / 45.0 s | 224 / 224 / 105.6 s | 224 / 224 / 262.5 s |
| 18 | 112 / 112 / 47.2 s | 224 / 224 / 122.4 s | 224 / 224 / 424.5 s |
| 20 | 112 / 112 / 52.1 s | 232 / 232 / 145.5 s | 232 / 232 / 397.9 s |
| 21 | 112 / 112 / 35.2 s | 248 / 248 / 133.3 s | 248 / 248 / 396.0 s |
| 33 | 112 / 112 / 16.1 s | 400 / 400 / 61.7 s | 400 / 400 / 134.2 s |
| 37 | 112 / 112 / 23.6 s | 448 / 448 / 86.2 s | 448 / 448 / 300.0 s |
| 39 | 112 / 112 / 22.4 s | 456 / 456 / 69.4 s | 456 / 456 / 162.5 s |
| 42 | 112 / 112 / 17.8 s | 488 / 488 / 50.0 s | 488 / 488 / 58.1 s |

Checks, dead-end segment -> straight gangway (1030 steps, everyone out at 180.2 s):
  - agent-steps 833951; row changes (clearway to clearway without an aisle: across a riser, seat block or the barrier) 0; entries onto another row's clearway from an aisle 12 (seated agents' agent-steps there 12); in a solid column 0; paths through a seat block / barrier / wall (tunnelling) 0
  - walls: min clearance none within the probe (BODY_RADIUS 0.2000 m), below BODY_RADIUS - 3e-4: 0 agent-steps; fence crossings 0
  - step-up: max floor rise in a step 0.0138 m, rises above MAX_STEP_UP 0; climbs over a vertical face (a discontinuous floor rise onto a floor above the start floor, any height) 0; faces crossed upwards in a net descent (information) 4 (max 0.0071 m)

Checks, segment -> straight gangway (1938 steps, everyone out at 339.0 s):
  - agent-steps 3273679; row changes (clearway to clearway without an aisle: across a riser, seat block or the barrier) 0; entries onto another row's clearway from an aisle 70 (seated agents' agent-steps there 241); in a solid column 0; paths through a seat block / barrier / wall (tunnelling) 0
  - walls: min clearance none within the probe (BODY_RADIUS 0.2000 m), below BODY_RADIUS - 3e-4: 0 agent-steps; fence crossings 0
  - step-up: max floor rise in a step 0.0142 m, rises above MAX_STEP_UP 0; climbs over a vertical face (a discontinuous floor rise onto a floor above the start floor, any height) 0; faces crossed upwards in a net descent (information) 37 (max 0.0608 m)

Checks, segment -> corner gangway (3281 steps, everyone out at 573.9 s):
  - agent-steps 5298347; row changes (clearway to clearway without an aisle: across a riser, seat block or the barrier) 0; entries onto another row's clearway from an aisle 411 (seated agents' agent-steps there 14160); in a solid column 0; paths through a seat block / barrier / wall (tunnelling) 0
  - walls: min clearance none within the probe (BODY_RADIUS 0.2000 m), below BODY_RADIUS - 3e-4: 0 agent-steps; fence crossings 0
  - step-up: max floor rise in a step 0.0287 m, rises above MAX_STEP_UP 0; climbs over a vertical face (a discontinuous floor rise onto a floor above the start floor, any height) 0; faces crossed upwards in a net descent (information) 282 (max 0.0123 m)

## (c) Gangways: one agent per (sampled) row band on every gangway (a straight gangway from its first row) driven down to the walkway / up to the rear concourse

| gangway | down: arrived / agents, last | up: arrived / agents, last |
|---|---|---|
| quadrant 0 wing 0 straight 0 | 12 / 12, 26.2 s | 12 / 12, 25.9 s |
| quadrant 0 wing 0 straight 1 | 8 / 8, 31.7 s | 8 / 8, 24.5 s |
| quadrant 0 wing 0 straight 2 | 3 / 3, 37.1 s | 3 / 3, 6.3 s |
| quadrant 0 wing 1 straight 0 | 12 / 12, 26.1 s | 12 / 12, 25.9 s |
| quadrant 0 wing 1 straight 1 | 8 / 8, 31.7 s | 8 / 8, 25.2 s |
| quadrant 0 wing 1 straight 2 | 3 / 3, 37.8 s | 3 / 3, 7.2 s |
| quadrant 1 wing 0 straight 0 | 12 / 12, 26.2 s | 12 / 12, 25.9 s |
| quadrant 1 wing 0 straight 1 | 8 / 8, 31.7 s | 8 / 8, 24.5 s |
| quadrant 1 wing 0 straight 2 | 3 / 3, 37.1 s | 3 / 3, 6.3 s |
| quadrant 1 wing 1 straight 0 | 12 / 12, 26.1 s | 12 / 12, 25.9 s |
| quadrant 1 wing 1 straight 1 | 8 / 8, 31.7 s | 8 / 8, 25.2 s |
| quadrant 1 wing 1 straight 2 | 3 / 3, 37.8 s | 3 / 3, 7.2 s |
| quadrant 2 wing 0 straight 0 | 12 / 12, 26.2 s | 12 / 12, 25.9 s |
| quadrant 2 wing 0 straight 1 | 8 / 8, 31.7 s | 8 / 8, 24.5 s |
| quadrant 2 wing 0 straight 2 | 3 / 3, 37.1 s | 3 / 3, 6.3 s |
| quadrant 2 wing 1 straight 0 | 12 / 12, 26.1 s | 12 / 12, 25.9 s |
| quadrant 2 wing 1 straight 1 | 8 / 8, 31.7 s | 8 / 8, 25.2 s |
| quadrant 2 wing 1 straight 2 | 3 / 3, 37.8 s | 3 / 3, 7.2 s |
| quadrant 3 wing 0 straight 0 | 12 / 12, 26.2 s | 12 / 12, 25.9 s |
| quadrant 3 wing 0 straight 1 | 8 / 8, 31.7 s | 8 / 8, 24.5 s |
| quadrant 3 wing 0 straight 2 | 3 / 3, 37.1 s | 3 / 3, 6.3 s |
| quadrant 3 wing 1 straight 0 | 12 / 12, 26.1 s | 12 / 12, 25.9 s |
| quadrant 3 wing 1 straight 1 | 8 / 8, 31.7 s | 8 / 8, 25.2 s |
| quadrant 3 wing 1 straight 2 | 3 / 3, 37.8 s | 3 / 3, 7.2 s |
| quadrant 0 corner | 12 / 12, 38.5 s | 12 / 12, 36.4 s |
| quadrant 1 corner | 12 / 12, 38.5 s | 12 / 12, 36.4 s |
| quadrant 2 corner | 12 / 12, 38.5 s | 12 / 12, 36.4 s |
| quadrant 3 corner | 12 / 12, 38.5 s | 12 / 12, 36.4 s |

Checks, down:
  - agent-steps 76164; row changes (clearway to clearway without an aisle: across a riser, seat block or the barrier) 0; entries onto another row's clearway from an aisle 0 (seated agents' agent-steps there 0); in a solid column 0; paths through a seat block / barrier / wall (tunnelling) 0
  - walls: min clearance none within the probe (BODY_RADIUS 0.2000 m), below BODY_RADIUS - 3e-4: 0 agent-steps; fence crossings 0
  - step-up: max floor rise in a step 0.0025 m, rises above MAX_STEP_UP 0; climbs over a vertical face (a discontinuous floor rise onto a floor above the start floor, any height) 0; faces crossed upwards in a net descent (information) 0 (max 0.0000 m)
Checks, up:
  - agent-steps 20972; row changes (clearway to clearway without an aisle: across a riser, seat block or the barrier) 0; entries onto another row's clearway from an aisle 0 (seated agents' agent-steps there 0); in a solid column 0; paths through a seat block / barrier / wall (tunnelling) 0
  - walls: min clearance none within the probe (BODY_RADIUS 0.2000 m), below BODY_RADIUS - 3e-4: 0 agent-steps; fence crossings 0
  - step-up: max floor rise in a step 0.1172 m, rises above MAX_STEP_UP 0; climbs over a vertical face (a discontinuous floor rise onto a floor above the start floor, any height) 0; faces crossed upwards in a net descent (information) 0 (max 0.0000 m)

## (d) Passages and exits

| passage | arrived / agents | last arrival |
|---|---:|---:|
| walkway ring, quadrant 0 | 8 / 8 | 15.9 s |
| walkway ring, quadrant 1 | 8 / 8 | 15.9 s |
| walkway ring, quadrant 2 | 8 / 8 | 15.9 s |
| walkway ring, quadrant 3 | 8 / 8 | 15.9 s |
| rear concourse ring, quadrant 0 | 4 / 4 | 74.7 s |
| rear concourse ring, quadrant 1 | 4 / 4 | 75.0 s |
| rear concourse ring, quadrant 2 | 4 / 4 | 74.7 s |
| rear concourse ring, quadrant 3 | 4 / 4 | 75.0 s |
| avenue +y out through its exit | 4 / 4 | 30.1 s |
| avenue -x out through its exit | 4 / 4 | 30.1 s |
| avenue -y out through its exit | 4 / 4 | 30.1 s |
| avenue +x out through its exit | 4 / 4 | 30.1 s |
| concourse exit: door +x+y (y wall) 0 | 2 / 2 | 1.6 s |
| concourse exit: door +x+y (y wall) 1 | 2 / 2 | 1.6 s |
| concourse exit: door +x+y (y wall) 2 | 2 / 2 | 1.6 s |
| concourse exit: door +x+y (x wall) 0 | 2 / 2 | 1.6 s |
| concourse exit: door +x+y (x wall) 1 | 2 / 2 | 1.6 s |
| concourse exit: door +x+y (x wall) 2 | 2 / 2 | 1.6 s |
| concourse exit: door +x+y (corner) | 2 / 2 | 2.6 s |
| concourse exit: door -x+y (y wall) 0 | 2 / 2 | 1.6 s |
| concourse exit: door -x+y (y wall) 1 | 2 / 2 | 1.6 s |
| concourse exit: door -x+y (y wall) 2 | 2 / 2 | 1.6 s |
| concourse exit: door -x+y (x wall) 0 | 2 / 2 | 1.6 s |
| concourse exit: door -x+y (x wall) 1 | 2 / 2 | 1.6 s |
| concourse exit: door -x+y (x wall) 2 | 2 / 2 | 1.6 s |
| concourse exit: door -x+y (corner) | 2 / 2 | 2.6 s |
| concourse exit: door -x-y (y wall) 0 | 2 / 2 | 1.6 s |
| concourse exit: door -x-y (y wall) 1 | 2 / 2 | 1.6 s |
| concourse exit: door -x-y (y wall) 2 | 2 / 2 | 1.6 s |
| concourse exit: door -x-y (x wall) 0 | 2 / 2 | 1.6 s |
| concourse exit: door -x-y (x wall) 1 | 2 / 2 | 1.6 s |
| concourse exit: door -x-y (x wall) 2 | 2 / 2 | 1.6 s |
| concourse exit: door -x-y (corner) | 2 / 2 | 2.6 s |
| concourse exit: door +x-y (y wall) 0 | 2 / 2 | 1.6 s |
| concourse exit: door +x-y (y wall) 1 | 2 / 2 | 1.6 s |
| concourse exit: door +x-y (y wall) 2 | 2 / 2 | 1.6 s |
| concourse exit: door +x-y (x wall) 0 | 2 / 2 | 1.6 s |
| concourse exit: door +x-y (x wall) 1 | 2 / 2 | 1.6 s |
| concourse exit: door +x-y (x wall) 2 | 2 / 2 | 1.6 s |
| concourse exit: door +x-y (corner) | 2 / 2 | 2.6 s |

Checks, rings:
  - agent-steps 68734; row changes (clearway to clearway without an aisle: across a riser, seat block or the barrier) 0; entries onto another row's clearway from an aisle 0 (seated agents' agent-steps there 0); in a solid column 0; paths through a seat block / barrier / wall (tunnelling) 0
  - walls: min clearance none within the probe (BODY_RADIUS 0.2000 m), below BODY_RADIUS - 3e-4: 0 agent-steps; fence crossings 0
  - step-up: max floor rise in a step 0.0000 m, rises above MAX_STEP_UP 0; climbs over a vertical face (a discontinuous floor rise onto a floor above the start floor, any height) 0; faces crossed upwards in a net descent (information) 0 (max 0.0000 m)
Checks, exits:
  - agent-steps 3220; row changes (clearway to clearway without an aisle: across a riser, seat block or the barrier) 0; entries onto another row's clearway from an aisle 0 (seated agents' agent-steps there 0); in a solid column 0; paths through a seat block / barrier / wall (tunnelling) 0
  - walls: min clearance none within the probe (BODY_RADIUS 0.2000 m), below BODY_RADIUS - 3e-4: 0 agent-steps; fence crossings 0
  - step-up: max floor rise in a step 0.0000 m, rises above MAX_STEP_UP 0; climbs over a vertical face (a discontinuous floor rise onto a floor above the start floor, any height) 0; faces crossed upwards in a net descent (information) 0 (max 0.0000 m)

## (f) The step-up rules over every scenario above (12215067 agent-steps)

- floor rises above MAX_STEP_UP (0.30 m) in one step: 0 (max rise 0.1172 m)
- climbs over a vertical face (a discontinuous floor rise, any height, along a step's path onto a floor above the start-of-step floor; checked every 2 mm): 0
- information: faces crossed upwards within a step that ends at or below its start floor (the path dipped onto the incline first; the step-up rule never blocks level or downward moves): 323 (max 0.0608 m)
- paths through a seat block, the barrier or a wall: 0

Total time 47 s.
