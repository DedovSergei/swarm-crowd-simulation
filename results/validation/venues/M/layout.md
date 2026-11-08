# Venue M: layout (Task 5.4; generated venue, Task 5.7)

venue_probe layout | commit 51792d01cfb6e8d345bcf4c3702b0131b7c918cb (dirty 0) | Release | 2026-10-11 11:08

## Parameters (real units; model units = metres / 31.25)

| parameter | value | model units |
|---|---:|---:|
| walkway width (fence outer face -> barrier front; the terrace's measured walkway) | 2.630 m | 0.084160 |
| front barrier thickness | 0.300 m | 0.009600 |
| front barrier top above the walkway | 1.100 m | 0.035200 |
| avenue clear width (the terrace's measured avenue mouths) | 5.660 m | 0.181120 |
| side wall thickness | 0.300 m | 0.009600 |
| rows | 43 | |
| row (tread) depth | 0.800 m | 0.025600 |
| row rise | 0.400 m | 0.012800 |
| clearway (front of each tread) | 0.500 m | 0.016000 |
| seat block depth (rowDepth - clearway) | 0.300 m | 0.009600 |
| seat block top above its tread | 0.850 m | 0.027200 |
| seat block top above the next row's tread | 0.450 m | 0.014400 |
| seat pitch | 0.500 m | 0.016000 |
| gangway width | 1.200 m | 0.038400 |
| max seats between two gangways / with a gangway at one end (Green Guide; verify against the cited edition) | 28 / 14 | |
| rear concourse width | 3.000 m | 0.096000 |
| outer wall thickness | 0.300 m | 0.009600 |
| side / outer wall top above the concourse | 1.100 m | 0.035200 |
| exterior landing depth | 0.500 m | 0.016000 |
| concourse exit rule: rate of passage (stairways) / egress time / minimum width / exits per quadrant (verify) | 66 p/(m min) / 8 min / 1.20 m / one per gangway head | |
| neighbour grid: cells per axis (0.05 model units = 1.5625 m) / domain half-width | 76 / 59.375 m | 1.9000 |
| metric grid: 1 m cells per axis | 128 | |

## Derived layout (Chebyshev depth dep = max(|x|, |y|), lateral lat = min(|x|, |y|))

| quantity | m | model units |
|---|---:|---:|
| fence outer face (dep) | 10.4822 | 0.3354320 |
| barrier front = stand front (dep) | 13.1122 | 0.4195920 |
| row 0 front (dep) | 13.4123 | 0.4291920 |
| concourse front = last row's back (dep) | 47.8122 | 1.5299919 |
| outer wall inner face (dep) | 50.8122 | 1.6259918 |
| outer wall outer face = exit depth (dep): the outer half-width | 51.1122 | 1.6355919 |
| exterior landings end (dep) | 51.6122 | 1.6515919 |
| avenue half-width (lat) | 2.8300 | 0.0905600 |
| stand side (side wall's stand face, lat) | 3.1300 | 0.1001600 |
| straight gangway (lat, low edge) | 10.3300 | 0.3305600 |
| straight gangway (lat, high edge) | 11.5300 | 0.3689600 |
| concourse exit (lat, low edge) | 10.3300 | 0.3305600 |
| concourse exit (lat, high edge) | 11.5300 | 0.3689600 |
| concourse exit width | 1.2000 | 0.0384000 |
| corner gangway inset of a clearway (from the diagonal at its row front) | 0.9485 | 0.0303529 |
| seat blocks and barrier end short of the gangways' edges (D17) | 0.2000 | 0.0064000 |
| row 0 tread height H0 = rake x clearway | 0.2500 | 0.0080000 |
| concourse level = rows x rise | 17.2000 | 0.5503999 |
| wall tops | 18.3000 | 0.5855999 |
| gangway rake | 26.57 deg (n_z 0.894) | 0.500 |
| corner gangway clear width (narrowest, between two mirrored seat-block corners) | 1.200 | |
| straight gangway clear width: between clearway ends / between seat-block ends | 1.200 / 1.600 | |

## Straight gangways, doors and the exit sizing rule (Task 5.7)

Gangway placement rule (Green Guide, seated accommodation; verify against the cited edition): at most 28 seats in a row between two gangways and 14 between a gangway and a dead end, applied to every row. Straight gangway i + 1 lies exactly 28 seats beyond gangway i and starts at the first row whose front reaches it (its foot opens onto the corner gangway); while no seat fits after it, it merges with the corner gangway.

| straight gangway | lat low edge (m) | lat high edge (m) | first row | merged with the corner gangway in rows |
|---:|---:|---:|---:|---|
| 0 | 10.330 | 11.530 | 0 | - |
| 1 | 25.930 | 27.130 | 17 | 17 .. 19 (while it is the last) |
| 2 | 41.530 | 42.730 | 37 | 37 .. 38 (while it is the last) |

Per quadrant 6 straight gangways and 1 corner gangway: 28 gangway heads.

Exit sizing rule (Task 5.7; rate of passage and egress time as Task 5.4's, Green Guide; verify against the cited edition): the total exit width, concourse doors and avenues, clears every seat within the egress time at the planning rate: W >= seats / (66 p/(m min) x 8 min) = **29.98 m**. A door at every gangway head (straight and corner), all of one width: the doors carry what the avenues leave, split evenly, rounded up to 0.1 m, at least the gangway's width (wider doors rather than more doors).

| door (per wing) | lat low (m) | lat high (m) | clear width (m) |
|---|---:|---:|---:|
| straight 0 | 10.330 | 11.530 | 1.20 |
| straight 1 | 25.930 | 27.130 | 1.20 |
| straight 2 | 41.530 | 42.730 | 1.20 |
| corner (both wings, from lat to the diagonal) | 49.964 | diagonal | 1.20 (sqrt 2 x (outer wall inner face - lat): the gap between the wall ends) |

| exits | count | width (m) |
|---|---:|---:|
| concourse doors | 28 | 33.60 |
| avenues | 4 | 22.64 |
| **total** | 32 | **56.24** (rule: >= 29.98) |

**Exit width per 1000 seats: 3.55 m** (doors 2.12, avenues 1.43); design egress time at the planning rate 4.3 min (target <= 8 min). Every gangway head leads to a door: **yes** (straight and corner).

Gangway loading (design check, information; not a rule of this generator): each seat counted for the nearer end of its row segment, the time to pass those seats through the gangway's 1.20 m at the planning rate of 66 p/(m min) (the exit rule's figures; verify):

| gangway (one wing; corner: one quadrant) | seats served | at the planning rate (min) |
|---|---:|---:|
| straight 0 | 1081 | 13.6 |
| straight 1 | 572 | 7.2 |
| straight 2 | 91 | 1.1 |
| corner | 470 | 5.9 |

## Seats

Per wing (8 wings: 4 quadrants x 2), per row: the dead-end segment (side wall .. straight gangway 0) and the segments after
each straight gangway (the last up to the corner gangway). Seats centred in their segment at the seat pitch.

| row | front dep (m) | tread z (m) | dead-end | after the straight gangways | largest between | per wing | all 8 wings |
|---:|---:|---:|---:|---|---:|---:|---:|
| 0 | 13.412 | 0.250 | 14 | 1 | 1 | 15 | 120 |
| 1 | 14.212 | 0.650 | 14 | 2 | 2 | 16 | 128 |
| 2 | 15.012 | 1.050 | 14 | 4 | 4 | 18 | 144 |
| 3 | 15.812 | 1.450 | 14 | 5 | 5 | 19 | 152 |
| 4 | 16.612 | 1.850 | 14 | 7 | 7 | 21 | 168 |
| 5 | 17.412 | 2.250 | 14 | 9 | 9 | 23 | 184 |
| 6 | 18.212 | 2.650 | 14 | 10 | 10 | 24 | 192 |
| 7 | 19.012 | 3.050 | 14 | 12 | 12 | 26 | 208 |
| 8 | 19.812 | 3.450 | 14 | 13 | 13 | 27 | 216 |
| 9 | 20.612 | 3.850 | 14 | 15 | 15 | 29 | 232 |
| 10 | 21.412 | 4.250 | 14 | 17 | 17 | 31 | 248 |
| 11 | 22.212 | 4.650 | 14 | 18 | 18 | 32 | 256 |
| 12 | 23.012 | 5.050 | 14 | 20 | 20 | 34 | 272 |
| 13 | 23.812 | 5.450 | 14 | 21 | 21 | 35 | 280 |
| 14 | 24.612 | 5.850 | 14 | 23 | 23 | 37 | 296 |
| 15 | 25.412 | 6.250 | 14 | 25 | 25 | 39 | 312 |
| 16 | 26.212 | 6.650 | 14 | 26 | 26 | 40 | 320 |
| 17 | 27.012 | 7.050 | 14 | 28 | 28 | 42 | 336 |
| 18 | 27.812 | 7.450 | 14 | 28 | 28 | 42 | 336 |
| 19 | 28.612 | 7.850 | 14 | 28 | 28 | 42 | 336 |
| 20 | 29.412 | 8.250 | 14 | 28 + 1 | 28 | 43 | 344 |
| 21 | 30.212 | 8.650 | 14 | 28 + 3 | 28 | 45 | 360 |
| 22 | 31.012 | 9.050 | 14 | 28 + 5 | 28 | 47 | 376 |
| 23 | 31.812 | 9.450 | 14 | 28 + 6 | 28 | 48 | 384 |
| 24 | 32.612 | 9.850 | 14 | 28 + 8 | 28 | 50 | 400 |
| 25 | 33.412 | 10.250 | 14 | 28 + 9 | 28 | 51 | 408 |
| 26 | 34.212 | 10.650 | 14 | 28 + 11 | 28 | 53 | 424 |
| 27 | 35.012 | 11.050 | 14 | 28 + 13 | 28 | 55 | 440 |
| 28 | 35.812 | 11.450 | 14 | 28 + 14 | 28 | 56 | 448 |
| 29 | 36.612 | 11.850 | 14 | 28 + 16 | 28 | 58 | 464 |
| 30 | 37.412 | 12.250 | 14 | 28 + 17 | 28 | 59 | 472 |
| 31 | 38.212 | 12.650 | 14 | 28 + 19 | 28 | 61 | 488 |
| 32 | 39.012 | 13.050 | 14 | 28 + 21 | 28 | 63 | 504 |
| 33 | 39.812 | 13.450 | 14 | 28 + 22 | 28 | 64 | 512 |
| 34 | 40.612 | 13.850 | 14 | 28 + 24 | 28 | 66 | 528 |
| 35 | 41.412 | 14.250 | 14 | 28 + 25 | 28 | 67 | 536 |
| 36 | 42.212 | 14.650 | 14 | 28 + 27 | 28 | 69 | 552 |
| 37 | 43.012 | 15.050 | 14 | 28 + 28 | 28 | 70 | 560 |
| 38 | 43.812 | 15.450 | 14 | 28 + 28 | 28 | 70 | 560 |
| 39 | 44.612 | 15.850 | 14 | 28 + 28 + 1 | 28 | 71 | 568 |
| 40 | 45.412 | 16.250 | 14 | 28 + 28 + 2 | 28 | 72 | 576 |
| 41 | 46.212 | 16.650 | 14 | 28 + 28 + 4 | 28 | 74 | 592 |
| 42 | 47.012 | 17.050 | 14 | 28 + 28 + 5 | 28 | 75 | 600 |

**Seats: 15832** (seated::seats lists 15832); per quadrant 3958.

## Floor areas (exact, m^2) and capacity

| floor | m^2 |
|---|---:|
| walkway (fence outer face -> barrier front) | 248.2 |
| avenues (barrier front -> outer face) | 860.3 |
| clearways | 4140.3 |
| gangways (straight + corner, with the barrier gaps) | 957.8 |
| rear concourse | 1108.4 |
| concourse exits (through the outer wall) | 11.0 |
| **occupiable** | **7326.1** |
| not occupiable: seat blocks / barrier / walls / pitch / landings (beyond the exit test) | 2471.2 / 18.1 / 195.0 / 421.3 / 20.0 |

Design capacity = seats = 15832; jam capacity = occupiable x hexagonal packing 7.2169 p/m^2 = 52871.
