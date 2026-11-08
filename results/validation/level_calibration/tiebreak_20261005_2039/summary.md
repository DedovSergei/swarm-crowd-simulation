# Mutual-standoff tie-break activations `tiebreak_5.3c`

commit `b239736a037263b633ac3e1085d0d9635b827a60`, dirty 1, Release; AMD  Radeon RX 7800 XT, 4.3.0 Core Profile Context 26.8.1.260810; 2026-10-05T20:39:45.

N = 4096 terrace evacuation from spawn, the predict pass built with DIAG_TIEBREAK (tools/tiebreak.hpp; counters per step, raw: tiebreak.csv). Evacuated at step 2735 (478.4 s); t50 / t90 at steps 1296 / 2309; 5338624 agent-steps. The instrumented run is the production run bit for bit (chained state hash of every step, evacuation step): **yes**.

A standoff: two agents each ahead in the other's lane (along the other's own e_goal); the tie-break lets only the one that has the other more directly ahead count it as its leader (ties: the larger boidID). 'Standoffs resolved' counts one activation per standoff pair and step; the agent counts compare the headway with the literal rule's (without the tie-break) for the same state.

| counter | total | per agent-step | max per step (step) | steps with any | mean per step | up to t50 | t50-t90 | t90-t100 |
|---|---:|---:|---|---:|---:|---:|---:|---:|
| mutual candidates | 198046 | 0.03710 | 182 (191) | 2383 | 72.41 | 152464 | 45332 | 250 |
| standoffs resolved (activations) | 99023 | 0.01855 | 91 (191) | 2383 | 36.21 | 76232 | 22666 | 125 |
| exact ties (by boidID) | 0 | 0.00000 | 0 (0) | 0 | 0.00 | 0 | 0 | 0 |
| agents: leader changed | 48336 | 0.00905 | 46 (191) | 2369 | 17.67 | 35494 | 12726 | 116 |
| agents: v_des changed | 41709 | 0.00781 | 38 (406) | 2368 | 15.25 | 29329 | 12264 | 116 |
| agents: released from v_des 0 | 12296 | 0.00230 | 19 (228) | 1922 | 4.50 | 10022 | 2271 | 3 |
