# Exit choice: excluded exits during a queue-aware evacuation of venue L (Task 5.7, correction C1)

nav_probe excluded | commit 372a5c19c97779f851bd5737b102b7136c2f09ce (dirty 0) | Release | 2026-10-12 19:27 | queue-aware exit choice, incline speed | 100% load, seed 1337 | GPU

Candidate table in use: CHOICE_K = 24 slots per cell, 48 exits (4 avenues, 44 doors), content fff03942436d48d2.

- Reachable FIT cells whose candidates hold **no avenue**: 0 of 6139132 (0.0%); no door: 0.
- Seats whose cell's candidates hold no avenue: 0 of 63424.
- Agents whose cell lookup returned a NOFIT cell (no FIT neighbour with candidates), on every evaluation step until the last snapshot: 0 of 9629673 agent-steps, 0 distinct agents.

E_e = d_e / V0 + Q_e / (w_e J) for every exit e: d_e from e's own exact field at the agent's choice cell (nav::buildExitField, float), Q_e the counts the choice pass read at that step, the pass's own arithmetic (nav::estimatedTime). EXCLUDED: not a candidate of the agent's cell. (A) an excluded exit's E below the assigned exit's; (B) below every candidate's; (C) below every candidate's and the assigned exit's by more than the switching margins max(10% E, 5 s) (the pass would have made the agent eligible to switch there).

### The model's estimate (the queue ahead A_e: the pass's prefix sums, agents assigned to e in nearer 0.49 m distance bins)

| t [s] | step | agents | assigned to an avenue | (A) excluded exit better than the assigned | (A) split: cap / margins / no better candidate | (B) better than every candidate | (C) better by more than the margins | best excluded: avenue / door | max gain over the assigned [s] |
|---:|---:|---:|---:|---:|---|---:|---:|---|---:|
| 5.9 | 34 | 63297 | 20101 | 23701 | 23674 / 27 / 0 | 0 | 0 | 0 / 23701 | 462.6 |
| 32.7 | 187 | 61059 | 9147 | 1209 | 1193 / 16 / 0 | 0 | 0 | 0 / 1209 | 73.4 |
| 62.4 | 357 | 58650 | 9189 | 2539 | 2406 / 133 / 0 | 0 | 0 | 0 / 2539 | 116.7 |
| 121.9 | 697 | 53493 | 8453 | 2212 | 2079 / 133 / 0 | 0 | 0 | 0 / 2212 | 140.8 |
| 240.8 | 1377 | 43713 | 6903 | 766 | 760 / 6 / 0 | 0 | 0 | 0 / 766 | 99.4 |
| 481.7 | 2754 | 26887 | 4178 | 159 | 159 / 0 / 0 | 0 | 0 | 0 / 159 | 34.6 |
| 722.5 | 4131 | 12184 | 1576 | 0 | 0 / 0 / 0 | 0 | 0 | 0 / 0 | - |
| 960.4 | 5491 | 2292 | 0 | 0 | 0 / 0 / 0 | 0 | 0 | 0 / 0 | - |
| **all** | | 321575 | | **30586** | **30271 / 315 / 0** | **0** | **0** | | |

(A) split: a candidate is better still than the excluded exit, and the agent is eligible to switch to it (its gain over the assigned exit exceeds the margins: the per-exit switch cap holds it back this evaluation) / a candidate is better still, within the margins (the hysteresis keeps the assigned exit) / no candidate is better than the excluded exit (counted in (B) too).

Hypothetical candidate rules on the same snapshots (agent-snapshots with an exit outside the rule's set better than every exit in it / better than the agent's assigned exit; the dynamics are the run's, not the rule's):

| candidate rule | slots | outside better than every candidate | outside better than the assigned |
|---|---:|---:|---:|
| the 4 nearest | 4 | 114804 | 91091 |
| 4: the nearest avenue and door, then the nearest | 4 | 90048 | 99728 |
| the 8 nearest | 8 | 35915 | 57137 |
| 8: the 2 nearest avenues, the nearest door, then the nearest | 8 | 40123 | 72916 |
| the 10 nearest | 10 | 16830 | 40238 |
| 10: the 2 nearest avenues, the nearest door, then the nearest | 10 | 20939 | 55128 |
| 10: the 2 nearest avenues, the nearest straight door, the nearest corner door, then the nearest | 10 | 13151 | 47077 |
| 10: the nearest avenue, the nearest straight door, the nearest corner door, then the nearest | 10 | 10173 | 41563 |
| 10: the 2 nearest avenues, the nearest straight door, the 2 nearest corner doors, then the nearest | 10 | 22042 | 54538 |
| the 12 nearest | 12 | 853 | 36768 |
| 12: the 2 nearest avenues, the nearest straight door, the nearest corner door, then the nearest | 12 | 2376 | 37272 |
| the 16 nearest | 16 | 8 | 32835 |
| the 20 nearest | 20 | 0 | 32617 |
| the 24 nearest | 24 | 0 | 30586 |
| 24: the 2 nearest avenues, the nearest straight door, the nearest corner door, then the nearest | 24 | 0 | 30586 |
| the 28 nearest | 28 | 0 | 30577 |

### Diagnostic: the queue ahead by exact distances (the agents assigned to e nearer to it than the agent at this snapshot)

| t [s] | step | agents | assigned to an avenue | (A) excluded exit better than the assigned | (A) split: cap / margins / no better candidate | (B) better than every candidate | (C) better by more than the margins | best excluded: avenue / door | max gain over the assigned [s] |
|---:|---:|---:|---:|---:|---|---:|---:|---|---:|
| 5.9 | 34 | 63297 | 20101 | 24037 | 24010 / 27 / 0 | 0 | 0 | 0 / 24037 | 463.8 |
| 32.7 | 187 | 61059 | 9147 | 1304 | 1280 / 24 / 0 | 0 | 0 | 0 / 1304 | 73.4 |
| 62.4 | 357 | 58650 | 9189 | 2673 | 2545 / 128 / 0 | 0 | 0 | 0 / 2673 | 121.1 |
| 121.9 | 697 | 53493 | 8453 | 2290 | 2154 / 136 / 0 | 0 | 0 | 0 / 2290 | 142.7 |
| 240.8 | 1377 | 43713 | 6903 | 806 | 798 / 8 / 0 | 0 | 0 | 0 / 806 | 99.7 |
| 481.7 | 2754 | 26887 | 4178 | 180 | 180 / 0 / 0 | 0 | 0 | 0 / 180 | 34.6 |
| 722.5 | 4131 | 12184 | 1576 | 0 | 0 / 0 / 0 | 0 | 0 | 0 / 0 | - |
| 960.4 | 5491 | 2292 | 0 | 0 | 0 / 0 / 0 | 0 | 0 | 0 / 0 | - |
| **all** | | 321575 | | **31290** | **30967 / 323 / 0** | **0** | **0** | | |

(A) split: a candidate is better still than the excluded exit, and the agent is eligible to switch to it (its gain over the assigned exit exceeds the margins: the per-exit switch cap holds it back this evaluation) / a candidate is better still, within the margins (the hysteresis keeps the assigned exit) / no candidate is better than the excluded exit (counted in (B) too).

Hypothetical candidate rules on the same snapshots (agent-snapshots with an exit outside the rule's set better than every exit in it / better than the agent's assigned exit; the dynamics are the run's, not the rule's):

| candidate rule | slots | outside better than every candidate | outside better than the assigned |
|---|---:|---:|---:|
| the 4 nearest | 4 | 114966 | 93454 |
| 4: the nearest avenue and door, then the nearest | 4 | 90387 | 102209 |
| the 8 nearest | 8 | 36335 | 58398 |
| 8: the 2 nearest avenues, the nearest door, then the nearest | 8 | 40645 | 74899 |
| the 10 nearest | 10 | 16675 | 41024 |
| 10: the 2 nearest avenues, the nearest door, then the nearest | 10 | 21572 | 56481 |
| 10: the 2 nearest avenues, the nearest straight door, the nearest corner door, then the nearest | 10 | 14101 | 48360 |
| 10: the nearest avenue, the nearest straight door, the nearest corner door, then the nearest | 10 | 10498 | 42448 |
| 10: the 2 nearest avenues, the nearest straight door, the 2 nearest corner doors, then the nearest | 10 | 22632 | 56132 |
| the 12 nearest | 12 | 711 | 37412 |
| 12: the 2 nearest avenues, the nearest straight door, the nearest corner door, then the nearest | 12 | 3828 | 38137 |
| the 16 nearest | 16 | 8 | 33577 |
| the 20 nearest | 20 | 0 | 33357 |
| the 24 nearest | 24 | 0 | 31290 |
| 24: the 2 nearest avenues, the nearest straight door, the nearest corner door, then the nearest | 24 | 0 | 31290 |
| the 28 nearest | 28 | 0 | 31283 |


Per-agent rows with (A) or (B): excluded_c1.csv.
