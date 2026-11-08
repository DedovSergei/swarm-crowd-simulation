# Exit choice: excluded exits during a queue-aware evacuation of venue S (Task 5.7, correction C1)

nav_probe excluded | commit 372a5c19c97779f851bd5737b102b7136c2f09ce (dirty 0) | Release | 2026-10-12 19:17 | queue-aware exit choice, incline speed | 100% load, seed 1337 | GPU

Candidate table in use: CHOICE_K = 24 slots per cell, 12 exits (4 avenues, 8 doors), content f65873da25306068.

- Reachable FIT cells whose candidates hold **no avenue**: 0 of 690216 (0.0%); no door: 0.
- Seats whose cell's candidates hold no avenue: 0 of 3728.
- Agents whose cell lookup returned a NOFIT cell (no FIT neighbour with candidates), on every evaluation step until the last snapshot: 0 of 125549 agent-steps, 0 distinct agents.

E_e = d_e / V0 + Q_e / (w_e J) for every exit e: d_e from e's own exact field at the agent's choice cell (nav::buildExitField, float), Q_e the counts the choice pass read at that step, the pass's own arithmetic (nav::estimatedTime). EXCLUDED: not a candidate of the agent's cell. (A) an excluded exit's E below the assigned exit's; (B) below every candidate's; (C) below every candidate's and the assigned exit's by more than the switching margins max(10% E, 5 s) (the pass would have made the agent eligible to switch there).

### The model's estimate (the queue ahead A_e: the pass's prefix sums, agents assigned to e in nearer 0.49 m distance bins)

| t [s] | step | agents | assigned to an avenue | (A) excluded exit better than the assigned | (A) split: cap / margins / no better candidate | (B) better than every candidate | (C) better by more than the margins | best excluded: avenue / door | max gain over the assigned [s] |
|---:|---:|---:|---:|---:|---|---:|---:|---|---:|
| 5.9 | 34 | 3704 | 360 | 0 | 0 / 0 / 0 | 0 | 0 | 0 / 0 | - |
| 32.7 | 187 | 3230 | 2105 | 0 | 0 / 0 / 0 | 0 | 0 | 0 / 0 | - |
| 62.4 | 357 | 2520 | 1624 | 0 | 0 / 0 / 0 | 0 | 0 | 0 / 0 | - |
| 92.2 | 527 | 1836 | 1142 | 0 | 0 / 0 / 0 | 0 | 0 | 0 / 0 | - |
| 121.9 | 697 | 1151 | 695 | 0 | 0 / 0 / 0 | 0 | 0 | 0 / 0 | - |
| 151.6 | 867 | 473 | 293 | 0 | 0 / 0 / 0 | 0 | 0 | 0 / 0 | - |
| 181.4 | 1037 | 21 | 3 | 0 | 0 / 0 / 0 | 0 | 0 | 0 / 0 | - |
| **all** | | 12935 | | **0** | **0 / 0 / 0** | **0** | **0** | | |

(A) split: a candidate is better still than the excluded exit, and the agent is eligible to switch to it (its gain over the assigned exit exceeds the margins: the per-exit switch cap holds it back this evaluation) / a candidate is better still, within the margins (the hysteresis keeps the assigned exit) / no candidate is better than the excluded exit (counted in (B) too).

Hypothetical candidate rules on the same snapshots (agent-snapshots with an exit outside the rule's set better than every exit in it / better than the agent's assigned exit; the dynamics are the run's, not the rule's):

| candidate rule | slots | outside better than every candidate | outside better than the assigned |
|---|---:|---:|---:|
| the 4 nearest | 4 | 0 | 2600 |
| 4: the nearest avenue and door, then the nearest | 4 | 0 | 2600 |
| the 8 nearest | 8 | 0 | 2600 |
| 8: the 2 nearest avenues, the nearest door, then the nearest | 8 | 0 | 2600 |
| the 10 nearest | 10 | 0 | 0 |
| 10: the 2 nearest avenues, the nearest door, then the nearest | 10 | 0 | 0 |
| 10: the 2 nearest avenues, the nearest straight door, the nearest corner door, then the nearest | 10 | 0 | 0 |
| 10: the nearest avenue, the nearest straight door, the nearest corner door, then the nearest | 10 | 0 | 0 |
| 10: the 2 nearest avenues, the nearest straight door, the 2 nearest corner doors, then the nearest | 10 | 0 | 0 |
| the 12 nearest | 12 | 0 | 0 |
| 12: the 2 nearest avenues, the nearest straight door, the nearest corner door, then the nearest | 12 | 0 | 0 |
| the 16 nearest | 16 | 0 | 0 |
| the 20 nearest | 20 | 0 | 0 |
| the 24 nearest | 24 | 0 | 0 |
| 24: the 2 nearest avenues, the nearest straight door, the nearest corner door, then the nearest | 24 | 0 | 0 |
| the 28 nearest | 28 | 0 | 0 |

### Diagnostic: the queue ahead by exact distances (the agents assigned to e nearer to it than the agent at this snapshot)

| t [s] | step | agents | assigned to an avenue | (A) excluded exit better than the assigned | (A) split: cap / margins / no better candidate | (B) better than every candidate | (C) better by more than the margins | best excluded: avenue / door | max gain over the assigned [s] |
|---:|---:|---:|---:|---:|---|---:|---:|---|---:|
| 5.9 | 34 | 3704 | 360 | 0 | 0 / 0 / 0 | 0 | 0 | 0 / 0 | - |
| 32.7 | 187 | 3230 | 2105 | 0 | 0 / 0 / 0 | 0 | 0 | 0 / 0 | - |
| 62.4 | 357 | 2520 | 1624 | 0 | 0 / 0 / 0 | 0 | 0 | 0 / 0 | - |
| 92.2 | 527 | 1836 | 1142 | 0 | 0 / 0 / 0 | 0 | 0 | 0 / 0 | - |
| 121.9 | 697 | 1151 | 695 | 0 | 0 / 0 / 0 | 0 | 0 | 0 / 0 | - |
| 151.6 | 867 | 473 | 293 | 0 | 0 / 0 / 0 | 0 | 0 | 0 / 0 | - |
| 181.4 | 1037 | 21 | 3 | 0 | 0 / 0 / 0 | 0 | 0 | 0 / 0 | - |
| **all** | | 12935 | | **0** | **0 / 0 / 0** | **0** | **0** | | |

(A) split: a candidate is better still than the excluded exit, and the agent is eligible to switch to it (its gain over the assigned exit exceeds the margins: the per-exit switch cap holds it back this evaluation) / a candidate is better still, within the margins (the hysteresis keeps the assigned exit) / no candidate is better than the excluded exit (counted in (B) too).

Hypothetical candidate rules on the same snapshots (agent-snapshots with an exit outside the rule's set better than every exit in it / better than the agent's assigned exit; the dynamics are the run's, not the rule's):

| candidate rule | slots | outside better than every candidate | outside better than the assigned |
|---|---:|---:|---:|
| the 4 nearest | 4 | 0 | 2664 |
| 4: the nearest avenue and door, then the nearest | 4 | 0 | 2664 |
| the 8 nearest | 8 | 0 | 2664 |
| 8: the 2 nearest avenues, the nearest door, then the nearest | 8 | 0 | 2664 |
| the 10 nearest | 10 | 0 | 0 |
| 10: the 2 nearest avenues, the nearest door, then the nearest | 10 | 0 | 0 |
| 10: the 2 nearest avenues, the nearest straight door, the nearest corner door, then the nearest | 10 | 0 | 0 |
| 10: the nearest avenue, the nearest straight door, the nearest corner door, then the nearest | 10 | 0 | 0 |
| 10: the 2 nearest avenues, the nearest straight door, the 2 nearest corner doors, then the nearest | 10 | 0 | 0 |
| the 12 nearest | 12 | 0 | 0 |
| 12: the 2 nearest avenues, the nearest straight door, the nearest corner door, then the nearest | 12 | 0 | 0 |
| the 16 nearest | 16 | 0 | 0 |
| the 20 nearest | 20 | 0 | 0 |
| the 24 nearest | 24 | 0 | 0 |
| 24: the 2 nearest avenues, the nearest straight door, the nearest corner door, then the nearest | 24 | 0 | 0 |
| the 28 nearest | 28 | 0 | 0 |


Per-agent rows with (A) or (B): excluded_c1.csv.
