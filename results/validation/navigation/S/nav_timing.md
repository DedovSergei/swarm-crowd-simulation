# Venue S: GPU cost of e_goal from the navigation field (Task 5.5 stage 6)

nav_probe timing | commit 09ddbdf7b2a2cfb60a11cad045bc1e48362ed6ce (dirty 0) | Release | 2026-10-09 21:14 | AMD  Radeon RX 7800 XT | 4.3.0 Core Profile Context 26.8.1.260810 | power throttling off (SetProcessInformation, EXECUTION_SPEED)

Positions: the 2962 active agents of the routed state after 250 steps of the full seat spawn (GPU), repeated to 262144 invocations; each calls the function 64 times along a short walk from its position (dependent inputs), GL_TIME_ELAPSED per dispatch, 15 repetitions after 3 warm-up dispatches. ns per call = time / (invocations x calls): a throughput over the whole GPU, not one call's latency. physics.comp's own @nav block on the venue's preamble.

| function | median ns/call | min | max |
|---|---:|---:|---:|
| navGoal (e_goal: the field's direction, the wall projection) | 0.1447 | 0.1314 | 0.1486 |
| navDirection (the field's direction alone) | 0.1345 | 0.1309 | 0.1367 |
| baseline (the loop without a call) | 0.0005 | 0.0005 | 0.0005 |

e_goal evaluations in one step at this state (physics.comp's predict pass): one per active agent (2962) plus one per in-lane neighbour ahead that the mutual-standoff test reaches (the nearest met so far: order-dependent): between 5909 (one such neighbour per agent that has any: 2947) and 14028 (every in-lane neighbour ahead: 11066). 1067 agents' centres lie in a NOFIT cell (their direction comes from the nearest FIT neighbour).

Estimated e_goal time per step = evaluations x (navGoal - baseline) = 0.0009 to 0.0020 ms (throughput estimate; in the step the calls overlap the neighbour loop's other work).
