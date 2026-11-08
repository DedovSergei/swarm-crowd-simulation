# Venue M: navigation field validation (Task 5.5 stage 3)

nav_probe validate | commit 03f06b747068f28c722980b9870da95c1d91036c (dirty 0) | Release | 2026-10-11 12:11

## (a) Known answers

Rectangle worlds (nav::RectGeometry, point agents: a cell is FIT where its centre is outside every wall), the same
builder (nav::build) on a 0.05 m grid whose cell edges lie on the walls; the exit regions start on a line of cell centres.
Reference: the exact geodesic distance (a shortest path over the visibility graph of the obstacles' corners, the last leg
to the nearest point of the exit region; a ledge is an obstacle for paths on the floor and none for a path that starts on
it). Compared over every cell of the room's (corridor's) interior; limit: one cell (0.05 m), two for the ledge (its floor
path bends at two corners; a grid path bends at a cell centre, up to h/sqrt(2) from the true corner).

| case | cells | without a path | max \|D - D_ref\| | mean | beyond the limit | worst at | result |
|---|---:|---:|---:|---:|---:|---|---|
| room, one door | 43200 | 0 | 0.0499 m (1.00 cells) | 0.0174 m | 0 | (0.025, 8.975) | PASS |
| L corridor | 26400 | 0 | 0.0500 m (1.00 cells) | 0.0241 m | 0 | (0.025, 1.975) | PASS |
| room, two doors | 64000 | 0 | 0.0499 m (1.00 cells) | 0.0170 m | 0 | (15.975, 0.025) | PASS |
| one-way ledge | 38400 | 0 | 0.0819 m (1.64 cells) | 0.0288 m | 0 | (3.975, 0.025) | PASS |

- room, one door: 12 x 9 m room, 0.3 m walls, a 1.2 m door in the top wall (x 5.4 .. 6.6); exit: beyond the wall (y > 9.3).
- L corridor: 2 m wide L-shaped corridor: x 0 .. 20 (y 0 .. 2), then up x 18 .. 20 to y 15; 0.3 m walls; exit: beyond its top end (y > 15).
- room, two doors: 16 x 10 m room, 0.3 m walls, door A (1.2 m) in the top wall at x 2 .. 3.2, door B (1.2 m) in the right wall at y 7 .. 8.2; exits beyond each.
- one-way ledge: 12 x 8 m room, a 0.3 m high ledge x 4 .. 8, y 0 .. 5 (one-way: down off it, never up), a 1.2 m door in the right wall at y 0.5 .. 1.7; from the floor left of the ledge the path goes around it, from the ledge straight down off it.

Two doors: 34967 cells lead to door A, 29033 to door B; 51 take the farther one by the reference, all within 0.0425 m of the equal-distance line (|D_A - D_B|; limit two cells, 0.10 m): the split lies where the two paths are equal.
One-way ledge: the floor cells left of the ledge route around it, on average 2.52 m longer than the straight line over it (the reference treats the ledge as an obstacle for them and matches); the ledge's own cells step straight down off it.

## (b) Venue M: paths

Field: loaded from the cache (2.09 s), content hash 78b7de936597a08c.

- seats: 15832; with a finite distance: 15832; their cell FIT: 15832.
- cells an agent can walk to from a seat (forward over the legal directed edges, FIT and NOFIT): 4394064 (10985.2 m^2); of them without a path to an exit: 0.

Unreachable floor (no legal path to an exit), by kind:

| kind | cells | m^2 |
|---|---:|---:|
| fence collision band | 9816 | 24.5 |
| pitch (fenced off) | 162409 | 406.0 |
| top of a seat block | 989088 | 2472.7 |
| top of a side parapet | 33312 | 83.3 |
| top of an outer / concourse side wall | 44688 | 111.7 |
| top of the front barrier | 7248 | 18.1 |

(b): PASS (every seat has a path; no cell an agent can reach is without one)

## (c) Descent from every seat

A point at each seat's spawn position follows e_goal (nav::goal at the rest height, the GPU's navGoal) in steps of 0.05 m until
it passes the outer wall's outer face (the exit test). Limit: no stall, path <= 1.2 x the field's distance at the seat.

- descents 15832, stalls 0, longest 889 steps;
- path / field distance: mean 1.0069, worst 1.0262 (seat 5830: path 5.20 m, field 5.07 m);
- information (not a criterion: a point has no contacts): steps that are not a legal move (seated geometry: fence, drop, rise, the step-up
  scan): 0, the longest part beyond the face 0.0000 m;

(c): PASS

## (d) Exit choice (each seat's nearest exit)

| exit | seats |
|---|---:|
| avenue +x | 0 |
| avenue -x | 0 |
| avenue +y | 0 |
| avenue -y | 0 |
| door +x+y (y wall) 0 | 1121 |
| door +x+y (y wall) 1 | 680 |
| door +x+y (y wall) 2 | 178 |
| door +x+y (x wall) 0 | 1121 |
| door +x+y (x wall) 1 | 680 |
| door +x+y (x wall) 2 | 178 |
| door +x+y (corner) | 0 |
| door -x+y (y wall) 0 | 1121 |
| door -x+y (y wall) 1 | 680 |
| door -x+y (y wall) 2 | 178 |
| door -x+y (x wall) 0 | 1121 |
| door -x+y (x wall) 1 | 680 |
| door -x+y (x wall) 2 | 178 |
| door -x+y (corner) | 0 |
| door -x-y (y wall) 0 | 1121 |
| door -x-y (y wall) 1 | 680 |
| door -x-y (y wall) 2 | 178 |
| door -x-y (x wall) 0 | 1121 |
| door -x-y (x wall) 1 | 680 |
| door -x-y (x wall) 2 | 178 |
| door -x-y (corner) | 0 |
| door +x-y (y wall) 0 | 1121 |
| door +x-y (y wall) 1 | 680 |
| door +x-y (y wall) 2 | 178 |
| door +x-y (x wall) 0 | 1121 |
| door +x-y (x wall) 1 | 680 |
| door +x-y (x wall) 2 | 178 |
| door +x-y (corner) | 0 |

Rear doors: 15832 seats (100.0%), avenues: 0 (0.0%).

| row | avenue | door |
|---:|---:|---:|
| 0 | 0 | 120 |
| 1 | 0 | 128 |
| 2 | 0 | 144 |
| 3 | 0 | 152 |
| 4 | 0 | 168 |
| 5 | 0 | 184 |
| 6 | 0 | 192 |
| 7 | 0 | 208 |
| 8 | 0 | 216 |
| 9 | 0 | 232 |
| 10 | 0 | 248 |
| 11 | 0 | 256 |
| 12 | 0 | 272 |
| 13 | 0 | 280 |
| 14 | 0 | 296 |
| 15 | 0 | 312 |
| 16 | 0 | 320 |
| 17 | 0 | 336 |
| 18 | 0 | 336 |
| 19 | 0 | 336 |
| 20 | 0 | 344 |
| 21 | 0 | 360 |
| 22 | 0 | 376 |
| 23 | 0 | 384 |
| 24 | 0 | 400 |
| 25 | 0 | 408 |
| 26 | 0 | 424 |
| 27 | 0 | 440 |
| 28 | 0 | 448 |
| 29 | 0 | 464 |
| 30 | 0 | 472 |
| 31 | 0 | 488 |
| 32 | 0 | 504 |
| 33 | 0 | 512 |
| 34 | 0 | 528 |
| 35 | 0 | 536 |
| 36 | 0 | 552 |
| 37 | 0 | 560 |
| 38 | 0 | 560 |
| 39 | 0 | 568 |
| 40 | 0 | 576 |
| 41 | 0 | 592 |
| 42 | 0 | 600 |

## (e) The 28-seat gangway rule (geometry unchanged in this task; for Task 5.6)

Seats per row in each wing: the dead-end segment (side wall .. straight gangway: one gangway, limit 14) and the segment between the straight and the corner gangway (limit 28).

| row | dead-end segment | between gangways | over 28 |
|---:|---:|---:|---|
| 0 | 14 | 1 | no |
| 1 | 14 | 2 | no |
| 2 | 14 | 4 | no |
| 3 | 14 | 5 | no |
| 4 | 14 | 7 | no |
| 5 | 14 | 9 | no |
| 6 | 14 | 10 | no |
| 7 | 14 | 12 | no |
| 8 | 14 | 13 | no |
| 9 | 14 | 15 | no |
| 10 | 14 | 17 | no |
| 11 | 14 | 18 | no |
| 12 | 14 | 20 | no |
| 13 | 14 | 21 | no |
| 14 | 14 | 23 | no |
| 15 | 14 | 25 | no |
| 16 | 14 | 26 | no |
| 17 | 14 | 28 | no |
| 18 | 14 | 28 | no |
| 19 | 14 | 28 | no |
| 20 | 14 | 28 | no |
| 21 | 14 | 28 | no |
| 22 | 14 | 28 | no |
| 23 | 14 | 28 | no |
| 24 | 14 | 28 | no |
| 25 | 14 | 28 | no |
| 26 | 14 | 28 | no |
| 27 | 14 | 28 | no |
| 28 | 14 | 28 | no |
| 29 | 14 | 28 | no |
| 30 | 14 | 28 | no |
| 31 | 14 | 28 | no |
| 32 | 14 | 28 | no |
| 33 | 14 | 28 | no |
| 34 | 14 | 28 | no |
| 35 | 14 | 28 | no |
| 36 | 14 | 28 | no |
| 37 | 14 | 28 | no |
| 38 | 14 | 28 | no |
| 39 | 14 | 28 | no |
| 40 | 14 | 28 | no |
| 41 | 14 | 28 | no |
| 42 | 14 | 28 | no |

Maximum consecutive seats between two gangways: 28 (rows over 28: 0); in a dead-end segment: 14.

**Validation: ALL PASS**
