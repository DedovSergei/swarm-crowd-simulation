# Venue S: traversability grid (Task 5.5 stage 1)

nav_probe grid | commit c3a6185968a7cc0547c0c657f81a8242680f3669 (dirty 0) | Release | 2026-10-09 15:25

## Grid

| quantity | value |
|---|---|
| cell size | 0.050 m (0.0016 model units) |
| cells | 1250 x 1250 = 1562500 over the domain [-31.25, 31.25] m in x and y |
| built in | 0.26 s (20 logical cores, OpenMP) |

Per cell, at its centre: the floor (seated::floorHeight, the physics' floor); FIT if a standing body fits (the centre at
floor + BODY_RADIUS clears the walls of the plane at the body's top, floor + 2 BODY_RADIUS (Task 5.4 D20, seated::wall), by
BODY_RADIUS, and lies outside the fence's collision band), else NOFIT. Edges to the 8 neighbours, directed: legal if the
move from centre to centre crosses no fence midline, drops at most MAX_STEP_UP (deeper: a fall), rises at most
MAX_STEP_UP and passes the step-up limit's own scan (seated::stepUpScan = physics.comp venueStepUpScan, with the start
cell's floor as f0: no climb over a vertical face onto a floor above it); a diagonal between FIT cells needs both side
cells FIT (no corner cutting).

## Classes

| where (the venue cell under the centre) | FIT cells | FIT m^2 | NOFIT cells | NOFIT m^2 | floor [m] |
|---|---:|---:|---:|---:|---|
| avenues | 143312 | 358.3 | 10816 | 27.0 | 0.00 .. 0.00 |
| barrier gaps (gangway feet) | 4464 | 11.2 | 768 | 1.9 | 0.00 .. 0.00 |
| beyond the outer face: avenue ends | 8544 | 21.4 | 120 | 0.3 | 0.00 .. 0.00 |
| beyond the outer face: landings, outside ground | 66448 | 166.1 | 18444 | 46.1 | 0.00 .. 6.80 |
| clearways | 79696 | 199.2 | 314704 | 786.8 | 0.25 .. 6.65 |
| concourse exits (through the outer wall) | 768 | 1.9 | 384 | 1.0 | 6.80 .. 6.80 |
| fence band | 0 | 0.0 | 21532 | 53.8 | 0.00 .. 0.00 |
| gangways (incline) | 89624 | 224.1 | 18088 | 45.2 | 0.01 .. 6.78 |
| pitch | 161604 | 404.0 | 0 | 0.0 | 0.00 .. 0.00 |
| rear concourse | 211312 | 528.3 | 32048 | 80.1 | 6.80 .. 6.80 |
| tops of barrier | 7200 | 18.0 | 0 | 0.0 | 1.10 .. 1.10 |
| tops of seat | 239552 | 598.9 | 352 | 0.9 | 1.10 .. 7.50 |
| tops of side wall | 12576 | 31.4 | 768 | 1.9 | 1.10 .. 7.50 |
| tops of wall | 27936 | 69.8 | 0 | 0.0 | 7.90 .. 7.90 |
| walkway | 86048 | 215.1 | 5392 | 13.5 | 0.00 .. 0.00 |
| **all** | 1139084 | 2847.7 | 423416 | 1058.5 | |

## Directed edges

Neighbour pairs (each pair once): legal both ways 5922254, one way only 15504 (between two FIT cells: 5712), neither way 304744.

| reason the other direction (one-way pairs) / both directions (neither) is not legal | one way | neither |
|---|---:|---:|
| legal (a diagonal cutting a NOFIT corner) | 0 | 2412 |
| fence crossing | 0 | 4964 |
| drop deeper than MAX_STEP_UP | 0 | 148072 |
| rise above MAX_STEP_UP | 0 | 148072 |
| climb over a vertical face (step-up scan) | 15504 | 1224 |

One-way pairs between FIT cells, by where they are (legal direction first is not distinguished):

| pair (cell -> its +x / +x+y / +y / -x+y neighbour) | pairs |
|---|---:|
| clearways -> gangways (incline) | 2856 |
| gangways (incline) -> clearways | 2856 |

## Seats and clearways

Seats whose spawn position (clearway centre) lies in a FIT cell: 3728 of 3728.

The clearway's standing strip: the FIT cells across a clearway (along its depth, at the middle of the wing's dead-end
segment), per row; a body (0.40 m) in a 0.50 m clearway between two seat blocks leaves its centre a 0.10 m strip.

| row | FIT cells across the clearway | strip [m] |
|---:|---:|---|
| 0 | 2 | 0.213 .. 0.263 behind the row front |
| 1 | 2 | 0.213 .. 0.263 behind the row front |
| 2 | 2 | 0.213 .. 0.263 behind the row front |
| 3 | 2 | 0.213 .. 0.263 behind the row front |
| 4 | 2 | 0.213 .. 0.263 behind the row front |
| 5 | 2 | 0.213 .. 0.263 behind the row front |
| 6 | 2 | 0.213 .. 0.263 behind the row front |
| 7 | 2 | 0.213 .. 0.263 behind the row front |
| 8 | 2 | 0.213 .. 0.263 behind the row front |
| 9 | 2 | 0.213 .. 0.263 behind the row front |
| 10 | 2 | 0.213 .. 0.263 behind the row front |
| 11 | 2 | 0.213 .. 0.263 behind the row front |
| 12 | 2 | 0.213 .. 0.263 behind the row front |
| 13 | 2 | 0.213 .. 0.263 behind the row front |
| 14 | 2 | 0.213 .. 0.263 behind the row front |
| 15 | 2 | 0.213 .. 0.263 behind the row front |
| 16 | 2 | 0.213 .. 0.263 behind the row front |

## Exit regions

The physics parks an agent past the outer wall's outer face (30.31 m); the exit regions are
the four avenue ends (lat < 2.83 m) and the eight concourse door landings (lat 10.33 .. 11.53 m, dep up to 30.81 m).

| exit | FIT cells | m^2 |
|---|---:|---:|
| avenue +x | 2136 | 5.34 |
| avenue -x | 2136 | 5.34 |
| avenue +y | 2136 | 5.34 |
| avenue -y | 2136 | 5.34 |
| door +x+y (y wall) | 213 | 0.53 |
| door +x+y (x wall) | 213 | 0.53 |
| door -x+y (y wall) | 213 | 0.53 |
| door -x+y (x wall) | 213 | 0.53 |
| door -x-y (y wall) | 213 | 0.53 |
| door -x-y (x wall) | 213 | 0.53 |
| door +x-y (y wall) | 213 | 0.53 |
| door +x-y (x wall) | 213 | 0.53 |

Map (grid.png, one pixel per cell, +x right, +y up): clearways blue, gangways green, concourse and exits yellow, ground light,
NOFIT grey, seat-block / barrier / wall tops dark red, exit cells red, FIT cells with a one-way edge black.

**Checks: PASS** (every seat's cell FIT; every row's clearway has FIT cells across it)
