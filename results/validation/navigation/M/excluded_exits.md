# Exit choice: excluded exits during a queue-aware evacuation of venue M (Task 5.7, correction C1)

nav_probe excluded | commit 372a5c19c97779f851bd5737b102b7136c2f09ce (dirty 0) | Release | 2026-10-12 19:19 | queue-aware exit choice, incline speed | 100% load, seed 1337 | GPU

Candidate table in use: CHOICE_K = 24 slots per cell, 32 exits (4 avenues, 28 doors), content f0946bd85c9db29e.

- Reachable FIT cells whose candidates hold **no avenue**: 0 of 2889164 (0.0%); no door: 0.
- Seats whose cell's candidates hold no avenue: 0 of 15832.
- Agents whose cell lookup returned a NOFIT cell (no FIT neighbour with candidates), on every evaluation step until the last snapshot: 0 of 1024612 agent-steps, 0 distinct agents.

E_e = d_e / V0 + Q_e / (w_e J) for every exit e: d_e from e's own exact field at the agent's choice cell (nav::buildExitField, float), Q_e the counts the choice pass read at that step, the pass's own arithmetic (nav::estimatedTime). EXCLUDED: not a candidate of the agent's cell. (A) an excluded exit's E below the assigned exit's; (B) below every candidate's; (C) below every candidate's and the assigned exit's by more than the switching margins max(10% E, 5 s) (the pass would have made the agent eligible to switch there).

### The model's estimate (the queue ahead A_e: the pass's prefix sums, agents assigned to e in nearer 0.49 m distance bins)

| t [s] | step | agents | assigned to an avenue | (A) excluded exit better than the assigned | (A) split: cap / margins / no better candidate | (B) better than every candidate | (C) better by more than the margins | best excluded: avenue / door | max gain over the assigned [s] |
|---:|---:|---:|---:|---:|---|---:|---:|---|---:|
| 5.9 | 34 | 15776 | 2280 | 6200 | 6200 / 0 / 0 | 0 | 0 | 0 / 6200 | 586.2 |
| 32.7 | 187 | 14554 | 5008 | 0 | 0 / 0 / 0 | 0 | 0 | 0 / 0 | - |
| 62.4 | 357 | 13049 | 4766 | 0 | 0 / 0 / 0 | 0 | 0 | 0 / 0 | - |
| 121.9 | 697 | 10328 | 3682 | 0 | 0 / 0 / 0 | 0 | 0 | 0 / 0 | - |
| 240.8 | 1377 | 5234 | 1760 | 0 | 0 / 0 / 0 | 0 | 0 | 0 / 0 | - |
| 362.8 | 2074 | 880 | 162 | 0 | 0 / 0 / 0 | 0 | 0 | 0 / 0 | - |
| 422.2 | 2414 | 29 | 0 | 0 | 0 / 0 / 0 | 0 | 0 | 0 / 0 | - |
| **all** | | 59850 | | **6200** | **6200 / 0 / 0** | **0** | **0** | | |

(A) split: a candidate is better still than the excluded exit, and the agent is eligible to switch to it (its gain over the assigned exit exceeds the margins: the per-exit switch cap holds it back this evaluation) / a candidate is better still, within the margins (the hysteresis keeps the assigned exit) / no candidate is better than the excluded exit (counted in (B) too).

Hypothetical candidate rules on the same snapshots (agent-snapshots with an exit outside the rule's set better than every exit in it / better than the agent's assigned exit; the dynamics are the run's, not the rule's):

| candidate rule | slots | outside better than every candidate | outside better than the assigned |
|---|---:|---:|---:|
| the 4 nearest | 4 | 21370 | 11044 |
| 4: the nearest avenue and door, then the nearest | 4 | 6918 | 13111 |
| the 8 nearest | 8 | 327 | 9188 |
| 8: the 2 nearest avenues, the nearest door, then the nearest | 8 | 0 | 8102 |
| the 10 nearest | 10 | 0 | 7833 |
| 10: the 2 nearest avenues, the nearest door, then the nearest | 10 | 0 | 7833 |
| 10: the 2 nearest avenues, the nearest straight door, the nearest corner door, then the nearest | 10 | 0 | 7833 |
| 10: the nearest avenue, the nearest straight door, the nearest corner door, then the nearest | 10 | 0 | 7833 |
| 10: the 2 nearest avenues, the nearest straight door, the 2 nearest corner doors, then the nearest | 10 | 0 | 7833 |
| the 12 nearest | 12 | 0 | 7833 |
| 12: the 2 nearest avenues, the nearest straight door, the nearest corner door, then the nearest | 12 | 0 | 7833 |
| the 16 nearest | 16 | 0 | 7801 |
| the 20 nearest | 20 | 0 | 6744 |
| the 24 nearest | 24 | 0 | 6200 |
| 24: the 2 nearest avenues, the nearest straight door, the nearest corner door, then the nearest | 24 | 0 | 6200 |
| the 28 nearest | 28 | 0 | 6200 |

### Diagnostic: the queue ahead by exact distances (the agents assigned to e nearer to it than the agent at this snapshot)

| t [s] | step | agents | assigned to an avenue | (A) excluded exit better than the assigned | (A) split: cap / margins / no better candidate | (B) better than every candidate | (C) better by more than the margins | best excluded: avenue / door | max gain over the assigned [s] |
|---:|---:|---:|---:|---:|---|---:|---:|---|---:|
| 5.9 | 34 | 15776 | 2280 | 6456 | 6456 / 0 / 0 | 0 | 0 | 0 / 6456 | 586.8 |
| 32.7 | 187 | 14554 | 5008 | 0 | 0 / 0 / 0 | 0 | 0 | 0 / 0 | - |
| 62.4 | 357 | 13049 | 4766 | 0 | 0 / 0 / 0 | 0 | 0 | 0 / 0 | - |
| 121.9 | 697 | 10328 | 3682 | 6 | 6 / 0 / 0 | 0 | 0 | 0 / 6 | 7.7 |
| 240.8 | 1377 | 5234 | 1760 | 0 | 0 / 0 / 0 | 0 | 0 | 0 / 0 | - |
| 362.8 | 2074 | 880 | 162 | 0 | 0 / 0 / 0 | 0 | 0 | 0 / 0 | - |
| 422.2 | 2414 | 29 | 0 | 0 | 0 / 0 / 0 | 0 | 0 | 0 / 0 | - |
| **all** | | 59850 | | **6462** | **6462 / 0 / 0** | **0** | **0** | | |

(A) split: a candidate is better still than the excluded exit, and the agent is eligible to switch to it (its gain over the assigned exit exceeds the margins: the per-exit switch cap holds it back this evaluation) / a candidate is better still, within the margins (the hysteresis keeps the assigned exit) / no candidate is better than the excluded exit (counted in (B) too).

Hypothetical candidate rules on the same snapshots (agent-snapshots with an exit outside the rule's set better than every exit in it / better than the agent's assigned exit; the dynamics are the run's, not the rule's):

| candidate rule | slots | outside better than every candidate | outside better than the assigned |
|---|---:|---:|---:|
| the 4 nearest | 4 | 21066 | 11434 |
| 4: the nearest avenue and door, then the nearest | 4 | 6811 | 13465 |
| the 8 nearest | 8 | 290 | 9478 |
| 8: the 2 nearest avenues, the nearest door, then the nearest | 8 | 0 | 8445 |
| the 10 nearest | 10 | 0 | 8115 |
| 10: the 2 nearest avenues, the nearest door, then the nearest | 10 | 0 | 8115 |
| 10: the 2 nearest avenues, the nearest straight door, the nearest corner door, then the nearest | 10 | 0 | 8115 |
| 10: the nearest avenue, the nearest straight door, the nearest corner door, then the nearest | 10 | 0 | 8115 |
| 10: the 2 nearest avenues, the nearest straight door, the 2 nearest corner doors, then the nearest | 10 | 0 | 8115 |
| the 12 nearest | 12 | 0 | 8115 |
| 12: the 2 nearest avenues, the nearest straight door, the nearest corner door, then the nearest | 12 | 0 | 8115 |
| the 16 nearest | 16 | 0 | 8080 |
| the 20 nearest | 20 | 0 | 6970 |
| the 24 nearest | 24 | 0 | 6462 |
| 24: the 2 nearest avenues, the nearest straight door, the nearest corner door, then the nearest | 24 | 0 | 6462 |
| the 28 nearest | 28 | 0 | 6456 |


Per-agent rows with (A) or (B): excluded_c1.csv.
