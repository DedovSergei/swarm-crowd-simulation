# Unimpeded travel time from every seat, venue L (Task 5.8)

nav_probe travel | commit efd1899f5144ffdb76fbf993f2affbc175643c48 (dirty 0) | Release | 2026-10-15 16:53 | 20 OpenMP threads | 87.7 s

Each seat's walking time to its fastest exit with nobody else in the venue: along e_goal of each candidate exit's own field (nav::choiceGoal, the default model's steering) in 0.05 m steps to the exit test, every step at the incline speed model's free speed for the floor's slope along it (level 1.34 m/s; the 26.6 deg gangways up 0.580 / down 0.655 m/s, horizontal). The candidates: the seat cell's 24 (the 2 nearest avenues, the nearest door, the nearest others), in increasing distance, stopped once the distance at the level speed exceeds the best time. No reaction time, no other agent: a lower bound on t100.

| seats | descents | stalled descents | seats without an exit | fastest exit: doors / avenues | min [s] | p50 [s] | p90 [s] | p99 [s] | **max [s]** | mean [s] |
|---:|---:|---:|---:|---|---:|---:|---:|---:|---:|---:|
| 63424 | 383444 | 0 | 0 | 56688 / 6736 | 3.6 | 47.4 | 90.7 | 100.3 | **102.8** | 49.9 |

**The farthest seat** (in time): quadrant 1, wing 0, row 25, segment 1, seat 16 at (-19.98, 33.66) m: **102.8 s** to avenue +y over 116.7 m (up the incline 0.0 m, down 20.1 m, level 96.6 m).

| row | seats | max [s] | mean [s] |
|---:|---:|---:|---:|
| 0 | 120 | 71.2 | 68.6 |
| 1 | 128 | 72.4 | 69.7 |
| 2 | 144 | 73.6 | 70.8 |
| 5 | 184 | 77.3 | 74.5 |
| 10 | 248 | 83.4 | 81.1 |
| 15 | 312 | 91.2 | 88.0 |
| 20 | 344 | 98.0 | 94.4 |
| 25 | 408 | 102.8 | 99.9 |
| 30 | 472 | 96.7 | 94.2 |
| 35 | 536 | 89.9 | 87.5 |
| 40 | 576 | 83.0 | 80.4 |
| 45 | 640 | 76.1 | 73.5 |
| 50 | 704 | 69.2 | 66.7 |
| 55 | 768 | 62.4 | 59.9 |
| 60 | 808 | 55.4 | 52.9 |
| 65 | 872 | 48.5 | 46.0 |
| 70 | 936 | 41.7 | 39.1 |
| 75 | 1000 | 34.8 | 32.3 |
| 80 | 1040 | 27.9 | 25.3 |
| 85 | 1104 | 21.0 | 18.5 |
| 90 | 1168 | 14.1 | 11.6 |
| 92 | 1192 | 11.4 | 8.9 |
| 93 | 1208 | 10.2 | 7.6 |
| 94 | 1216 | 9.0 | 6.2 |
