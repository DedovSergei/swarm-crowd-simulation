# Venue L: layout (Task 5.4; generated venue, Task 5.7)

venue_probe layout | commit 51792d01cfb6e8d345bcf4c3702b0131b7c918cb (dirty 0) | Release | 2026-10-11 11:08

## Parameters (real units; model units = metres / 31.25)

| parameter | value | model units |
|---|---:|---:|
| walkway width (fence outer face -> barrier front; the terrace's measured walkway) | 2.630 m | 0.084160 |
| front barrier thickness | 0.300 m | 0.009600 |
| front barrier top above the walkway | 1.100 m | 0.035200 |
| avenue clear width (the terrace's measured avenue mouths) | 5.660 m | 0.181120 |
| side wall thickness | 0.300 m | 0.009600 |
| rows | 95 | |
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
| neighbour grid: cells per axis (0.05 model units = 1.5625 m) / domain half-width | 128 / 100.000 m | 3.2000 |
| metric grid: 1 m cells per axis | 208 | |

## Derived layout (Chebyshev depth dep = max(|x|, |y|), lateral lat = min(|x|, |y|))

| quantity | m | model units |
|---|---:|---:|
| fence outer face (dep) | 10.4822 | 0.3354320 |
| barrier front = stand front (dep) | 13.1122 | 0.4195920 |
| row 0 front (dep) | 13.4123 | 0.4291920 |
| concourse front = last row's back (dep) | 89.4122 | 2.8611920 |
| outer wall inner face (dep) | 92.4122 | 2.9571919 |
| outer wall outer face = exit depth (dep): the outer half-width | 92.7122 | 2.9667919 |
| exterior landings end (dep) | 93.2122 | 2.9827919 |
| avenue half-width (lat) | 2.8300 | 0.0905600 |
| stand side (side wall's stand face, lat) | 3.1300 | 0.1001600 |
| straight gangway (lat, low edge) | 10.3300 | 0.3305600 |
| straight gangway (lat, high edge) | 11.5300 | 0.3689600 |
| concourse exit (lat, low edge) | 9.7800 | 0.3129600 |
| concourse exit (lat, high edge) | 12.0800 | 0.3865600 |
| concourse exit width | 2.3000 | 0.0736000 |
| corner gangway inset of a clearway (from the diagonal at its row front) | 0.9485 | 0.0303529 |
| seat blocks and barrier end short of the gangways' edges (D17) | 0.2000 | 0.0064000 |
| row 0 tread height H0 = rake x clearway | 0.2500 | 0.0080000 |
| concourse level = rows x rise | 38.0000 | 1.2160000 |
| wall tops | 39.1000 | 1.2512000 |
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
| 3 | 57.130 | 58.330 | 56 | 56 .. 58 (while it is the last) |
| 4 | 72.730 | 73.930 | 76 | 76 .. 77 (while it is the last) |

Per quadrant 10 straight gangways and 1 corner gangway: 44 gangway heads.

Exit sizing rule (Task 5.7; rate of passage and egress time as Task 5.4's, Green Guide; verify against the cited edition): the total exit width, concourse doors and avenues, clears every seat within the egress time at the planning rate: W >= seats / (66 p/(m min) x 8 min) = **120.12 m**. A door at every gangway head (straight and corner), all of one width: the doors carry what the avenues leave, split evenly, rounded up to 0.1 m, at least the gangway's width (wider doors rather than more doors).

| door (per wing) | lat low (m) | lat high (m) | clear width (m) |
|---|---:|---:|---:|
| straight 0 | 9.780 | 12.080 | 2.30 |
| straight 1 | 25.380 | 27.680 | 2.30 |
| straight 2 | 40.980 | 43.280 | 2.30 |
| straight 3 | 56.580 | 58.880 | 2.30 |
| straight 4 | 72.180 | 74.480 | 2.30 |
| corner (both wings, from lat to the diagonal) | 90.786 | diagonal | 2.30 (sqrt 2 x (outer wall inner face - lat): the gap between the wall ends) |

| exits | count | width (m) |
|---|---:|---:|
| concourse doors | 44 | 101.20 |
| avenues | 4 | 22.64 |
| **total** | 48 | **123.84** (rule: >= 120.12) |

**Exit width per 1000 seats: 1.95 m** (doors 1.60, avenues 0.36); design egress time at the planning rate 7.8 min (target <= 8 min). Every gangway head leads to a door: **yes** (straight and corner).

Gangway loading (design check, information; not a rule of this generator): each seat counted for the nearer end of its row segment, the time to pass those seats through the gangway's 1.20 m at the planning rate of 66 p/(m min) (the exit rule's figures; verify):

| gangway (one wing; corner: one quadrant) | seats served | at the planning rate (min) |
|---|---:|---:|
| straight 0 | 2537 | 32.0 |
| straight 1 | 2028 | 25.6 |
| straight 2 | 1477 | 18.6 |
| straight 3 | 936 | 11.8 |
| straight 4 | 382 | 4.8 |
| corner | 1136 | 14.3 |

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
| 43 | 47.812 | 17.450 | 14 | 28 + 28 + 7 | 28 | 77 | 616 |
| 44 | 48.612 | 17.850 | 14 | 28 + 28 + 9 | 28 | 79 | 632 |
| 45 | 49.412 | 18.250 | 14 | 28 + 28 + 10 | 28 | 80 | 640 |
| 46 | 50.212 | 18.650 | 14 | 28 + 28 + 12 | 28 | 82 | 656 |
| 47 | 51.012 | 19.050 | 14 | 28 + 28 + 13 | 28 | 83 | 664 |
| 48 | 51.812 | 19.450 | 14 | 28 + 28 + 15 | 28 | 85 | 680 |
| 49 | 52.612 | 19.850 | 14 | 28 + 28 + 17 | 28 | 87 | 696 |
| 50 | 53.412 | 20.250 | 14 | 28 + 28 + 18 | 28 | 88 | 704 |
| 51 | 54.212 | 20.650 | 14 | 28 + 28 + 20 | 28 | 90 | 720 |
| 52 | 55.012 | 21.050 | 14 | 28 + 28 + 21 | 28 | 91 | 728 |
| 53 | 55.812 | 21.450 | 14 | 28 + 28 + 23 | 28 | 93 | 744 |
| 54 | 56.612 | 21.850 | 14 | 28 + 28 + 25 | 28 | 95 | 760 |
| 55 | 57.412 | 22.250 | 14 | 28 + 28 + 26 | 28 | 96 | 768 |
| 56 | 58.212 | 22.650 | 14 | 28 + 28 + 28 | 28 | 98 | 784 |
| 57 | 59.012 | 23.050 | 14 | 28 + 28 + 28 | 28 | 98 | 784 |
| 58 | 59.812 | 23.450 | 14 | 28 + 28 + 28 | 28 | 98 | 784 |
| 59 | 60.612 | 23.850 | 14 | 28 + 28 + 28 + 1 | 28 | 99 | 792 |
| 60 | 61.412 | 24.250 | 14 | 28 + 28 + 28 + 3 | 28 | 101 | 808 |
| 61 | 62.212 | 24.650 | 14 | 28 + 28 + 28 + 5 | 28 | 103 | 824 |
| 62 | 63.012 | 25.050 | 14 | 28 + 28 + 28 + 6 | 28 | 104 | 832 |
| 63 | 63.812 | 25.450 | 14 | 28 + 28 + 28 + 8 | 28 | 106 | 848 |
| 64 | 64.612 | 25.850 | 14 | 28 + 28 + 28 + 9 | 28 | 107 | 856 |
| 65 | 65.412 | 26.250 | 14 | 28 + 28 + 28 + 11 | 28 | 109 | 872 |
| 66 | 66.212 | 26.650 | 14 | 28 + 28 + 28 + 13 | 28 | 111 | 888 |
| 67 | 67.012 | 27.050 | 14 | 28 + 28 + 28 + 14 | 28 | 112 | 896 |
| 68 | 67.812 | 27.450 | 14 | 28 + 28 + 28 + 16 | 28 | 114 | 912 |
| 69 | 68.612 | 27.850 | 14 | 28 + 28 + 28 + 17 | 28 | 115 | 920 |
| 70 | 69.412 | 28.250 | 14 | 28 + 28 + 28 + 19 | 28 | 117 | 936 |
| 71 | 70.212 | 28.650 | 14 | 28 + 28 + 28 + 21 | 28 | 119 | 952 |
| 72 | 71.012 | 29.050 | 14 | 28 + 28 + 28 + 22 | 28 | 120 | 960 |
| 73 | 71.812 | 29.450 | 14 | 28 + 28 + 28 + 24 | 28 | 122 | 976 |
| 74 | 72.612 | 29.850 | 14 | 28 + 28 + 28 + 25 | 28 | 123 | 984 |
| 75 | 73.412 | 30.250 | 14 | 28 + 28 + 28 + 27 | 28 | 125 | 1000 |
| 76 | 74.212 | 30.650 | 14 | 28 + 28 + 28 + 28 | 28 | 126 | 1008 |
| 77 | 75.012 | 31.050 | 14 | 28 + 28 + 28 + 28 | 28 | 126 | 1008 |
| 78 | 75.812 | 31.450 | 14 | 28 + 28 + 28 + 28 + 1 | 28 | 127 | 1016 |
| 79 | 76.612 | 31.850 | 14 | 28 + 28 + 28 + 28 + 2 | 28 | 128 | 1024 |
| 80 | 77.412 | 32.250 | 14 | 28 + 28 + 28 + 28 + 4 | 28 | 130 | 1040 |
| 81 | 78.212 | 32.650 | 14 | 28 + 28 + 28 + 28 + 5 | 28 | 131 | 1048 |
| 82 | 79.012 | 33.050 | 14 | 28 + 28 + 28 + 28 + 7 | 28 | 133 | 1064 |
| 83 | 79.812 | 33.450 | 14 | 28 + 28 + 28 + 28 + 9 | 28 | 135 | 1080 |
| 84 | 80.612 | 33.850 | 14 | 28 + 28 + 28 + 28 + 10 | 28 | 136 | 1088 |
| 85 | 81.412 | 34.250 | 14 | 28 + 28 + 28 + 28 + 12 | 28 | 138 | 1104 |
| 86 | 82.212 | 34.650 | 14 | 28 + 28 + 28 + 28 + 13 | 28 | 139 | 1112 |
| 87 | 83.012 | 35.050 | 14 | 28 + 28 + 28 + 28 + 15 | 28 | 141 | 1128 |
| 88 | 83.812 | 35.450 | 14 | 28 + 28 + 28 + 28 + 17 | 28 | 143 | 1144 |
| 89 | 84.612 | 35.850 | 14 | 28 + 28 + 28 + 28 + 18 | 28 | 144 | 1152 |
| 90 | 85.412 | 36.250 | 14 | 28 + 28 + 28 + 28 + 20 | 28 | 146 | 1168 |
| 91 | 86.212 | 36.650 | 14 | 28 + 28 + 28 + 28 + 21 | 28 | 147 | 1176 |
| 92 | 87.012 | 37.050 | 14 | 28 + 28 + 28 + 28 + 23 | 28 | 149 | 1192 |
| 93 | 87.812 | 37.450 | 14 | 28 + 28 + 28 + 28 + 25 | 28 | 151 | 1208 |
| 94 | 88.612 | 37.850 | 14 | 28 + 28 + 28 + 28 + 26 | 28 | 152 | 1216 |

**Seats: 63424** (seated::seats lists 63424); per quadrant 15856.

## Floor areas (exact, m^2) and capacity

| floor | m^2 |
|---|---:|
| walkway (fence outer face -> barrier front) | 248.2 |
| avenues (barrier front -> outer face) | 1802.1 |
| clearways | 16458.3 |
| gangways (straight + corner, with the barrier gaps) | 3175.0 |
| rear concourse | 2106.8 |
| concourse exits (through the outer wall) | 31.9 |
| **occupiable** | **23822.3** |
| not occupiable: seat blocks / barrier / walls / pitch / landings (beyond the exit test) | 9728.5 / 18.1 / 373.8 / 421.3 / 54.7 |

Design capacity = seats = 63424; jam capacity = occupiable x hexagonal packing 7.2169 p/m^2 = 171923.
