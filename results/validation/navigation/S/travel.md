# Unimpeded travel time from every seat, venue S (Task 5.8)

nav_probe travel | commit efd1899f5144ffdb76fbf993f2affbc175643c48 (dirty 0) | Release | 2026-10-15 16:51 | 20 OpenMP threads | 0.1 s

Each seat's walking time to its fastest exit with nobody else in the venue: along e_goal of each candidate exit's own field (nav::choiceGoal, the default model's steering) in 0.05 m steps to the exit test, every step at the incline speed model's free speed for the floor's slope along it (level 1.34 m/s; the 26.6 deg gangways up 0.580 / down 0.655 m/s, horizontal). The candidates: the seat cell's 24 (the 2 nearest avenues, the nearest door, the nearest others), in increasing distance, stopped once the distance at the level speed exceeds the best time. No reaction time, no other agent: a lower bound on t100.

| seats | descents | stalled descents | seats without an exit | fastest exit: doors / avenues | min [s] | p50 [s] | p90 [s] | p99 [s] | **max [s]** | mean [s] |
|---:|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|
| 3728 | 5200 | 0 | 0 | 3336 / 392 | 3.7 | 15.1 | 22.9 | 26.1 | **27.1** | 15.3 |

**The farthest seat** (in time): quadrant 0, wing 0, row 2, segment 0, seat 0 at (3.38, 15.26) m: **27.1 s** to avenue +y over 34.4 m (up the incline 0.0 m, down 1.7 m, level 32.7 m).

| row | seats | max [s] | mean [s] |
|---:|---:|---:|---:|
| 0 | 120 | 24.6 | 22.0 |
| 1 | 128 | 25.8 | 23.2 |
| 2 | 144 | 27.1 | 24.3 |
| 5 | 184 | 23.7 | 20.9 |
| 10 | 248 | 17.9 | 14.7 |
| 14 | 296 | 14.7 | 10.0 |
| 15 | 312 | 14.0 | 8.8 |
| 16 | 320 | 13.1 | 7.6 |
