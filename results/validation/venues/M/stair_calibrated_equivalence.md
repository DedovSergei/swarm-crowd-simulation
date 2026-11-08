# Venue M: CPU/GPU equivalence of the production program (Task 5.7)

venue_probe equiv | commit ba86b3ae21b252be1c83e995381b467da49ad033 (dirty 1) | Release | 2026-10-20 23:33 | AMD  Radeon RX 7800 XT | 4.3.0 Core Profile Context 26.8.1.260810 | power throttling off (SetProcessInformation, EXECUTION_SPEED)

The full seat spawn (spawnSeatedCrowd, 100%, seed 1337: 15832 agents, buffer N = 16384), routed by the default model (queue-aware exit choice, incline speed, stair spacing (empirical)), the GPU pipeline (CrowdSim) against the CPU reference (CpuCrowdSim), both sort modes.

- one step from the GPU state after 200 steps (14739 active), CPU counting: cell table identical, gridID sequence differs at 0 slots, (gridID, boidID) pairs at 13919 (counting: boidID order within a cell) -> grid **exact**; |dpos| > 2e-4 for 0 agents (0.000%, limit < 0.5%: PASS), max 4.46e-06
- one step from the GPU state after 200 steps (14739 active), CPU bitonic: cell table identical, gridID sequence differs at 0 slots, (gridID, boidID) pairs at 0 -> grid **exact**; |dpos| > 2e-4 for 0 agents (0.000%, limit < 0.5%: PASS), max 4.46e-06
- CPU thread invariance (counting, 1 thread vs 20, 100 steps, every step's state chained): identical
- determinism: two GPU runs and two CPU runs of 250 steps: identical
- **golden** (FNV-1a 64 of the state after 250 steps): GPU **f01cbab87d50bce0**, CPU counting **dfbb0cd26213add2**, CPU bitonic **06ded25a7094b105** (active 14417 / 14414 / 14414 of 15832)

Result: PASS (139 s)
