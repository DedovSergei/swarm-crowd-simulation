# Unimpeded travel time from every seat, venue M (Task 5.8)

nav_probe travel | commit efd1899f5144ffdb76fbf993f2affbc175643c48 (dirty 0) | Release | 2026-10-15 16:51 | 20 OpenMP threads | 4.6 s

Each seat's walking time to its fastest exit with nobody else in the venue: along e_goal of each candidate exit's own field (nav::choiceGoal, the default model's steering) in 0.05 m steps to the exit test, every step at the incline speed model's free speed for the floor's slope along it (level 1.34 m/s; the 26.6 deg gangways up 0.580 / down 0.655 m/s, horizontal). The candidates: the seat cell's 24 (the 2 nearest avenues, the nearest door, the nearest others), in increasing distance, stopped once the distance at the level speed exceeds the best time. No reaction time, no other agent: a lower bound on t100.

| seats | descents | stalled descents | seats without an exit | fastest exit: doors / avenues | min [s] | p50 [s] | p90 [s] | p99 [s] | **max [s]** | mean [s] |
|---:|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|
| 15832 | 60496 | 0 | 0 | 13888 / 1944 | 3.6 | 25.8 | 45.7 | 50.3 | **52.3** | 26.9 |

**The farthest seat** (in time): quadrant 0, wing 0, row 10, segment 0, seat 0 at (3.38, 21.66) m: **52.3 s** to avenue +y over 61.5 m (up the incline 0.0 m, down 8.1 m, level 53.4 m).

| row | seats | max [s] | mean [s] |
|---:|---:|---:|---:|
| 0 | 120 | 40.1 | 37.5 |
| 1 | 128 | 41.3 | 38.6 |
| 2 | 144 | 42.5 | 39.7 |
| 5 | 184 | 46.2 | 43.4 |
| 10 | 248 | 52.3 | 49.8 |
| 15 | 312 | 45.8 | 43.4 |
| 20 | 344 | 38.8 | 36.3 |
| 25 | 408 | 31.9 | 29.4 |
| 30 | 472 | 25.1 | 22.6 |
| 35 | 536 | 18.3 | 15.8 |
| 40 | 576 | 11.3 | 8.8 |
| 41 | 592 | 9.9 | 7.4 |
| 42 | 600 | 8.5 | 6.0 |
