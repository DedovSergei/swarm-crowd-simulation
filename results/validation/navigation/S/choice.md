# Exit choice: candidate table of venue S (Task 5.6 stage 1)

nav_probe choice | commit 1fa39425fa116ec208e7b100e65aea443af69fdf (dirty 0) | Release | 2026-10-10 12:10

## Build and memory

- 12 per-exit fields (Lazy Theta* from each exit's region alone, nav::lazyThetaStar), 1250 x 1250 cells of 0.050 m, built in 3.21 s (20 threads, Release); the cache equals this build (content a3919e407f6e9fbe).
- Full per-exit fields at this resolution (anchor + distance, 8 B per cell and exit): venue S 143 MB; the largest planned venue (5000^2 cells of 0.05 m, ~40 exits) 7.5 GB.
- Candidate table (CHOICE_K = 4 nearest exits per cell, 32 B per cell): venue S 47.7 MB; the largest planned venue 763 MB (budget 1 GB = 1024 MB). Queue-aware simulations upload the table only (the nearest-exit field, 16 B per cell, is not needed: the viewer's distance overlay uploads it on demand).

## Accuracy

- The distances are each exit's exact field (float, no reduced precision or resolution). The nearest candidate against Task 5.5's nearest-exit field (one search from every exit at once; Lazy Theta*'s paths depend on the expansion order): 1102720 cells reachable in both (1102720 in the nearest-exit field, 0 only in the table), |difference| max 0.0000 m (0.00 cells), mean 0.00000 m.
- Reachable cells by the number of candidates (1: 0, 2: 0, 3: 0, 4: 1102720).
- Seats with an avenue among their candidates: 3728 of 3728 (the nearest avenue is candidate 1 / 2 / 3 / 4 / none: 0 / 0 / 3728 / 0 / 0).

| candidate exits of a seat (nearest first) | seats |
|---|---:|
| door -x-y (y wall) | door -x-y (x wall) | avenue -y | avenue -x | 466 |
| door -x-y (x wall) | door -x-y (y wall) | avenue -x | avenue -y | 466 |
| door -x+y (y wall) | door -x+y (x wall) | avenue +y | avenue -x | 466 |
| door -x+y (x wall) | door -x+y (y wall) | avenue -x | avenue +y | 466 |
| door +x-y (y wall) | door +x-y (x wall) | avenue -y | avenue +x | 466 |
| door +x-y (x wall) | door +x-y (y wall) | avenue +x | avenue -y | 466 |
| door +x+y (y wall) | door +x+y (x wall) | avenue +y | avenue +x | 466 |
| door +x+y (x wall) | door +x+y (y wall) | avenue +x | avenue +y | 466 |

## Candidate limit during a queue-aware evacuation (CPU reference, 100% load)

- 882 steps (everyone left); 97404 evaluations (re-evaluations and forced choices; the pass counted 93676, switches 3023, forced 0).
- The best exit over all 12 exits (each exit's own field at the agent's cell, the same counts) lay outside the cell's 4 candidates in 0 evaluations (0.000%); its estimate was better by -.

