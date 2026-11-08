# Venue L: forced-motion validation (Task 5.4 stage 5)

venue_probe forced | commit 03f06b747068f28c722980b9870da95c1d91036c (dirty 0) | Release | 2026-10-11 12:18 | AMD  Radeon RX 7800 XT | 4.3.0 Core Profile Context 26.8.1.260810 | power throttling off (SetProcessInformation, EXECUTION_SPEED)

The router is bypassed: every agent's desired direction e_goal comes from a table written before every step from the state the
step starts from (physics.comp TEST_DRIVE_TABLE; the CPU reference: setDriveTable), as a field of the agent's cell and plan
(tools/venue_s.hpp). V0 = 1.34 m/s. Checks after every step (venue_s::Checker; (e) also plausibility::runEvacuation).

Rows of (a)-(c): rows 0, 7, 17, 20, 21, 30, 37, 39, 41, 47, 56, 59, 74, 76, 78, 94 (of 0 .. 94, in all 8 wings: the first, middle and last rows, each straight gangway's first row and first seated row, and 5 drawn with seed 7). Step limits x 5.59 (the venue's rows / 17).

## (a) INV-row: every seat occupied, every agent driven towards the pitch / away from it for 300 steps (52.5 s)

**towards the pitch** (10024 agents):
  - agent-steps off the agent's own clearway: 0; front-row agents that reached the walkway: 0
  - agent-steps 3007200; row changes (clearway to clearway without an aisle: across a riser, seat block or the barrier) 0; entries onto another row's clearway from an aisle 0 (seated agents' agent-steps there 0); in a solid column 0; paths through a seat block / barrier / wall (tunnelling) 0
  - walls: min clearance none within the probe (BODY_RADIUS 0.2000 m), below BODY_RADIUS - 3e-4: 0 agent-steps; fence crossings 0
  - step-up: max floor rise in a step 0.0000 m, rises above MAX_STEP_UP 0; climbs over a vertical face (a discontinuous floor rise onto a floor above the start floor, any height) 0; faces crossed upwards in a net descent (information) 0 (max 0.0000 m)

**away from the pitch** (10024 agents):
  - agent-steps off the agent's own clearway: 0; front-row agents that reached the walkway: 0
  - agent-steps 3007200; row changes (clearway to clearway without an aisle: across a riser, seat block or the barrier) 0; entries onto another row's clearway from an aisle 0 (seated agents' agent-steps there 0); in a solid column 0; paths through a seat block / barrier / wall (tunnelling) 0
  - walls: min clearance none within the probe (BODY_RADIUS 0.2000 m), below BODY_RADIUS - 3e-4: 0 agent-steps; fence crossings 0
  - step-up: max floor rise in a step 0.0000 m, rises above MAX_STEP_UP 0; climbs over a vertical face (a discontinuous floor rise onto a floor above the start floor, any height) 0; faces crossed upwards in a net descent (information) 0 (max 0.0000 m)

## (b) Junctions: per row, one segment's agents driven along the row towards one adjacent gangway (then down it and out)

| junction | agents | entered the gangway | first / median / last entry | not entered |
|---|---:|---:|---:|---:|
| dead-end segment -> straight gangway | 1792 | 1792 | 0.7 s / 7.0 s / 29.4 s | 0 |
| segment -> straight gangway | 8232 | 8232 | 0.7 s / 16.3 s / 113.7 s | 0 |
| segment -> corner gangway | 8232 | 8232 | 0.7 s / 18.9 s / 1291.2 s | 0 |

Per row (agents / entered / last entry), dead-end segment -> straight gangway | segment -> straight gangway | segment -> corner gangway:

| row | dead-end -> straight | segment -> straight | segment -> corner |
|---:|---|---|---|
| 0 | 112 / 112 / 19.4 s | 8 / 8 / 0.7 s | 8 / 8 / 0.7 s |
| 7 | 112 / 112 / 13.1 s | 96 / 96 / 10.8 s | 96 / 96 / 20.5 s |
| 17 | 112 / 112 / 16.8 s | 224 / 224 / 43.6 s | 224 / 224 / 199.4 s |
| 20 | 112 / 112 / 29.4 s | 232 / 232 / 74.5 s | 232 / 232 / 268.1 s |
| 21 | 112 / 112 / 26.4 s | 248 / 248 / 71.4 s | 248 / 248 / 414.2 s |
| 30 | 112 / 112 / 14.9 s | 360 / 360 / 65.1 s | 360 / 360 / 87.3 s |
| 37 | 112 / 112 / 21.3 s | 448 / 448 / 90.3 s | 448 / 448 / 948.3 s |
| 39 | 112 / 112 / 25.5 s | 456 / 456 / 113.7 s | 456 / 456 / 1031.8 s |
| 41 | 112 / 112 / 20.5 s | 480 / 480 / 108.4 s | 480 / 480 / 1027.2 s |
| 47 | 112 / 112 / 14.0 s | 552 / 552 / 67.0 s | 552 / 552 / 152.5 s |
| 56 | 112 / 112 / 14.9 s | 672 / 672 / 62.8 s | 672 / 672 / 1252.3 s |
| 59 | 112 / 112 / 15.6 s | 680 / 680 / 53.9 s | 680 / 680 / 1246.6 s |
| 74 | 112 / 112 / 19.1 s | 872 / 872 / 69.6 s | 872 / 872 / 81.7 s |
| 76 | 112 / 112 / 23.4 s | 896 / 896 / 74.0 s | 896 / 896 / 1291.2 s |
| 78 | 112 / 112 / 19.2 s | 904 / 904 / 67.3 s | 904 / 904 / 261.8 s |
| 94 | 112 / 112 / 11.0 s | 1104 / 1104 / 22.2 s | 1104 / 1104 / 38.1 s |

Checks, dead-end segment -> straight gangway (1496 steps, everyone out at 261.7 s):
  - agent-steps 1699963; row changes (clearway to clearway without an aisle: across a riser, seat block or the barrier) 0; entries onto another row's clearway from an aisle 0 (seated agents' agent-steps there 0); in a solid column 0; paths through a seat block / barrier / wall (tunnelling) 0
  - walls: min clearance none within the probe (BODY_RADIUS 0.2000 m), below BODY_RADIUS - 3e-4: 0 agent-steps; fence crossings 0
  - step-up: max floor rise in a step 0.0120 m, rises above MAX_STEP_UP 0; climbs over a vertical face (a discontinuous floor rise onto a floor above the start floor, any height) 0; faces crossed upwards in a net descent (information) 0 (max 0.0000 m)

Checks, segment -> straight gangway (6505 steps, everyone out at 1137.8 s):
  - agent-steps 24293190; row changes (clearway to clearway without an aisle: across a riser, seat block or the barrier) 0; entries onto another row's clearway from an aisle 1666 (seated agents' agent-steps there 66423); in a solid column 0; paths through a seat block / barrier / wall (tunnelling) 0
  - walls: min clearance none within the probe (BODY_RADIUS 0.2000 m), below BODY_RADIUS - 3e-4: 0 agent-steps; fence crossings 0
  - step-up: max floor rise in a step 0.0153 m, rises above MAX_STEP_UP 0; climbs over a vertical face (a discontinuous floor rise onto a floor above the start floor, any height) 0; faces crossed upwards in a net descent (information) 1117 (max 0.0506 m)

Checks, segment -> corner gangway (8897 steps, everyone out at 1556.1 s):
  - agent-steps 37933367; row changes (clearway to clearway without an aisle: across a riser, seat block or the barrier) 0; entries onto another row's clearway from an aisle 4456 (seated agents' agent-steps there 201729); in a solid column 0; paths through a seat block / barrier / wall (tunnelling) 0
  - walls: min clearance none within the probe (BODY_RADIUS 0.2000 m), below BODY_RADIUS - 3e-4: 0 agent-steps; fence crossings 0
  - step-up: max floor rise in a step 0.0285 m, rises above MAX_STEP_UP 0; climbs over a vertical face (a discontinuous floor rise onto a floor above the start floor, any height) 0; faces crossed upwards in a net descent (information) 3099 (max 0.0552 m)

## (c) Gangways: one agent per (sampled) row band on every gangway (a straight gangway from its first row) driven down to the walkway / up to the rear concourse

| gangway | down: arrived / agents, last | up: arrived / agents, last |
|---|---|---|
| quadrant 0 wing 0 straight 0 | 16 / 16, 57.2 s | 16 / 16, 56.8 s |
| quadrant 0 wing 0 straight 1 | 14 / 14, 65.2 s | 14 / 14, 66.8 s |
| quadrant 0 wing 0 straight 2 | 10 / 10, 72.2 s | 10 / 10, 50.2 s |
| quadrant 0 wing 0 straight 3 | 6 / 6, 76.3 s | 6 / 6, 33.9 s |
| quadrant 0 wing 0 straight 4 | 3 / 3, 77.8 s | 3 / 3, 17.3 s |
| quadrant 0 wing 1 straight 0 | 16 / 16, 57.2 s | 16 / 16, 56.8 s |
| quadrant 0 wing 1 straight 1 | 14 / 14, 65.9 s | 14 / 14, 67.5 s |
| quadrant 0 wing 1 straight 2 | 10 / 10, 72.9 s | 10 / 10, 51.1 s |
| quadrant 0 wing 1 straight 3 | 6 / 6, 77.0 s | 6 / 6, 34.6 s |
| quadrant 0 wing 1 straight 4 | 3 / 3, 78.7 s | 3 / 3, 18.0 s |
| quadrant 1 wing 0 straight 0 | 16 / 16, 57.2 s | 16 / 16, 56.8 s |
| quadrant 1 wing 0 straight 1 | 14 / 14, 63.8 s | 14 / 14, 66.8 s |
| quadrant 1 wing 0 straight 2 | 10 / 10, 72.4 s | 10 / 10, 50.2 s |
| quadrant 1 wing 0 straight 3 | 6 / 6, 77.1 s | 6 / 6, 33.9 s |
| quadrant 1 wing 0 straight 4 | 3 / 3, 78.4 s | 3 / 3, 17.3 s |
| quadrant 1 wing 1 straight 0 | 16 / 16, 57.2 s | 16 / 16, 56.8 s |
| quadrant 1 wing 1 straight 1 | 14 / 14, 64.5 s | 14 / 14, 67.5 s |
| quadrant 1 wing 1 straight 2 | 10 / 10, 73.5 s | 10 / 10, 51.1 s |
| quadrant 1 wing 1 straight 3 | 6 / 6, 77.8 s | 6 / 6, 34.6 s |
| quadrant 1 wing 1 straight 4 | 3 / 3, 79.2 s | 3 / 3, 18.0 s |
| quadrant 2 wing 0 straight 0 | 16 / 16, 57.2 s | 16 / 16, 56.8 s |
| quadrant 2 wing 0 straight 1 | 14 / 14, 65.2 s | 14 / 14, 66.8 s |
| quadrant 2 wing 0 straight 2 | 10 / 10, 72.2 s | 10 / 10, 50.2 s |
| quadrant 2 wing 0 straight 3 | 6 / 6, 76.3 s | 6 / 6, 33.9 s |
| quadrant 2 wing 0 straight 4 | 3 / 3, 77.8 s | 3 / 3, 17.3 s |
| quadrant 2 wing 1 straight 0 | 16 / 16, 57.2 s | 16 / 16, 56.8 s |
| quadrant 2 wing 1 straight 1 | 14 / 14, 65.9 s | 14 / 14, 67.5 s |
| quadrant 2 wing 1 straight 2 | 10 / 10, 72.9 s | 10 / 10, 51.1 s |
| quadrant 2 wing 1 straight 3 | 6 / 6, 77.0 s | 6 / 6, 34.6 s |
| quadrant 2 wing 1 straight 4 | 3 / 3, 78.7 s | 3 / 3, 18.0 s |
| quadrant 3 wing 0 straight 0 | 16 / 16, 57.2 s | 16 / 16, 56.8 s |
| quadrant 3 wing 0 straight 1 | 14 / 14, 63.8 s | 14 / 14, 66.8 s |
| quadrant 3 wing 0 straight 2 | 10 / 10, 72.4 s | 10 / 10, 50.2 s |
| quadrant 3 wing 0 straight 3 | 6 / 6, 77.1 s | 6 / 6, 33.9 s |
| quadrant 3 wing 0 straight 4 | 3 / 3, 78.4 s | 3 / 3, 17.3 s |
| quadrant 3 wing 1 straight 0 | 16 / 16, 57.2 s | 16 / 16, 56.8 s |
| quadrant 3 wing 1 straight 1 | 14 / 14, 64.5 s | 14 / 14, 67.5 s |
| quadrant 3 wing 1 straight 2 | 10 / 10, 73.5 s | 10 / 10, 51.1 s |
| quadrant 3 wing 1 straight 3 | 6 / 6, 77.8 s | 6 / 6, 34.6 s |
| quadrant 3 wing 1 straight 4 | 3 / 3, 79.2 s | 3 / 3, 18.0 s |
| quadrant 0 corner | 16 / 16, 80.6 s | 16 / 16, 80.3 s |
| quadrant 1 corner | 16 / 16, 80.6 s | 16 / 16, 80.3 s |
| quadrant 2 corner | 16 / 16, 80.6 s | 16 / 16, 80.3 s |
| quadrant 3 corner | 16 / 16, 80.6 s | 16 / 16, 80.3 s |

Checks, down:
  - agent-steps 292420; row changes (clearway to clearway without an aisle: across a riser, seat block or the barrier) 0; entries onto another row's clearway from an aisle 0 (seated agents' agent-steps there 0); in a solid column 0; paths through a seat block / barrier / wall (tunnelling) 0
  - walls: min clearance none within the probe (BODY_RADIUS 0.2000 m), below BODY_RADIUS - 3e-4: 0 agent-steps; fence crossings 0
  - step-up: max floor rise in a step 0.0086 m, rises above MAX_STEP_UP 0; climbs over a vertical face (a discontinuous floor rise onto a floor above the start floor, any height) 0; faces crossed upwards in a net descent (information) 0 (max 0.0000 m)
Checks, up:
  - agent-steps 80104; row changes (clearway to clearway without an aisle: across a riser, seat block or the barrier) 0; entries onto another row's clearway from an aisle 0 (seated agents' agent-steps there 0); in a solid column 0; paths through a seat block / barrier / wall (tunnelling) 0
  - walls: min clearance none within the probe (BODY_RADIUS 0.2000 m), below BODY_RADIUS - 3e-4: 0 agent-steps; fence crossings 0
  - step-up: max floor rise in a step 0.1172 m, rises above MAX_STEP_UP 0; climbs over a vertical face (a discontinuous floor rise onto a floor above the start floor, any height) 0; faces crossed upwards in a net descent (information) 0 (max 0.0000 m)

## (d) Passages and exits

| passage | arrived / agents | last arrival |
|---|---:|---:|
| walkway ring, quadrant 0 | 8 / 8 | 15.9 s |
| walkway ring, quadrant 1 | 8 / 8 | 15.9 s |
| walkway ring, quadrant 2 | 8 / 8 | 15.9 s |
| walkway ring, quadrant 3 | 8 / 8 | 15.9 s |
| rear concourse ring, quadrant 0 | 4 / 4 | 136.6 s |
| rear concourse ring, quadrant 1 | 4 / 4 | 136.6 s |
| rear concourse ring, quadrant 2 | 4 / 4 | 136.6 s |
| rear concourse ring, quadrant 3 | 4 / 4 | 136.6 s |
| avenue +y out through its exit | 4 / 4 | 61.0 s |
| avenue -x out through its exit | 4 / 4 | 61.0 s |
| avenue -y out through its exit | 4 / 4 | 61.0 s |
| avenue +x out through its exit | 4 / 4 | 61.0 s |
| concourse exit: door +x+y (y wall) 0 | 2 / 2 | 1.6 s |
| concourse exit: door +x+y (y wall) 1 | 2 / 2 | 1.6 s |
| concourse exit: door +x+y (y wall) 2 | 2 / 2 | 1.6 s |
| concourse exit: door +x+y (y wall) 3 | 2 / 2 | 1.6 s |
| concourse exit: door +x+y (y wall) 4 | 2 / 2 | 1.6 s |
| concourse exit: door +x+y (x wall) 0 | 2 / 2 | 1.6 s |
| concourse exit: door +x+y (x wall) 1 | 2 / 2 | 1.6 s |
| concourse exit: door +x+y (x wall) 2 | 2 / 2 | 1.6 s |
| concourse exit: door +x+y (x wall) 3 | 2 / 2 | 1.6 s |
| concourse exit: door +x+y (x wall) 4 | 2 / 2 | 1.6 s |
| concourse exit: door +x+y (corner) | 2 / 2 | 2.6 s |
| concourse exit: door -x+y (y wall) 0 | 2 / 2 | 1.6 s |
| concourse exit: door -x+y (y wall) 1 | 2 / 2 | 1.6 s |
| concourse exit: door -x+y (y wall) 2 | 2 / 2 | 1.6 s |
| concourse exit: door -x+y (y wall) 3 | 2 / 2 | 1.6 s |
| concourse exit: door -x+y (y wall) 4 | 2 / 2 | 1.6 s |
| concourse exit: door -x+y (x wall) 0 | 2 / 2 | 1.6 s |
| concourse exit: door -x+y (x wall) 1 | 2 / 2 | 1.6 s |
| concourse exit: door -x+y (x wall) 2 | 2 / 2 | 1.6 s |
| concourse exit: door -x+y (x wall) 3 | 2 / 2 | 1.6 s |
| concourse exit: door -x+y (x wall) 4 | 2 / 2 | 1.6 s |
| concourse exit: door -x+y (corner) | 2 / 2 | 2.6 s |
| concourse exit: door -x-y (y wall) 0 | 2 / 2 | 1.6 s |
| concourse exit: door -x-y (y wall) 1 | 2 / 2 | 1.6 s |
| concourse exit: door -x-y (y wall) 2 | 2 / 2 | 1.6 s |
| concourse exit: door -x-y (y wall) 3 | 2 / 2 | 1.6 s |
| concourse exit: door -x-y (y wall) 4 | 2 / 2 | 1.6 s |
| concourse exit: door -x-y (x wall) 0 | 2 / 2 | 1.6 s |
| concourse exit: door -x-y (x wall) 1 | 2 / 2 | 1.6 s |
| concourse exit: door -x-y (x wall) 2 | 2 / 2 | 1.6 s |
| concourse exit: door -x-y (x wall) 3 | 2 / 2 | 1.6 s |
| concourse exit: door -x-y (x wall) 4 | 2 / 2 | 1.6 s |
| concourse exit: door -x-y (corner) | 2 / 2 | 2.6 s |
| concourse exit: door +x-y (y wall) 0 | 2 / 2 | 1.6 s |
| concourse exit: door +x-y (y wall) 1 | 2 / 2 | 1.6 s |
| concourse exit: door +x-y (y wall) 2 | 2 / 2 | 1.6 s |
| concourse exit: door +x-y (y wall) 3 | 2 / 2 | 1.6 s |
| concourse exit: door +x-y (y wall) 4 | 2 / 2 | 1.6 s |
| concourse exit: door +x-y (x wall) 0 | 2 / 2 | 1.6 s |
| concourse exit: door +x-y (x wall) 1 | 2 / 2 | 1.6 s |
| concourse exit: door +x-y (x wall) 2 | 2 / 2 | 1.6 s |
| concourse exit: door +x-y (x wall) 3 | 2 / 2 | 1.6 s |
| concourse exit: door +x-y (x wall) 4 | 2 / 2 | 1.6 s |
| concourse exit: door +x-y (corner) | 2 / 2 | 2.6 s |

Checks, rings:
  - agent-steps 147816; row changes (clearway to clearway without an aisle: across a riser, seat block or the barrier) 0; entries onto another row's clearway from an aisle 0 (seated agents' agent-steps there 0); in a solid column 0; paths through a seat block / barrier / wall (tunnelling) 0
  - walls: min clearance none within the probe (BODY_RADIUS 0.2000 m), below BODY_RADIUS - 3e-4: 0 agent-steps; fence crossings 0
  - step-up: max floor rise in a step 0.0000 m, rises above MAX_STEP_UP 0; climbs over a vertical face (a discontinuous floor rise onto a floor above the start floor, any height) 0; faces crossed upwards in a net descent (information) 0 (max 0.0000 m)
Checks, exits:
  - agent-steps 6308; row changes (clearway to clearway without an aisle: across a riser, seat block or the barrier) 0; entries onto another row's clearway from an aisle 0 (seated agents' agent-steps there 0); in a solid column 0; paths through a seat block / barrier / wall (tunnelling) 0
  - walls: min clearance none within the probe (BODY_RADIUS 0.2000 m), below BODY_RADIUS - 3e-4: 0 agent-steps; fence crossings 0
  - step-up: max floor rise in a step 0.0000 m, rises above MAX_STEP_UP 0; climbs over a vertical face (a discontinuous floor rise onto a floor above the start floor, any height) 0; faces crossed upwards in a net descent (information) 0 (max 0.0000 m)

## (f) The step-up rules over every scenario above (70467568 agent-steps)

- floor rises above MAX_STEP_UP (0.30 m) in one step: 0 (max rise 0.1172 m)
- climbs over a vertical face (a discontinuous floor rise, any height, along a step's path onto a floor above the start-of-step floor; checked every 2 mm): 0
- information: faces crossed upwards within a step that ends at or below its start floor (the path dipped onto the incline first; the step-up rule never blocks level or downward moves): 4216 (max 0.0552 m)
- paths through a seat block, the barrier or a wall: 0

Total time 370 s.
