# Venue L: CPU/GPU equivalence of the production program (Task 5.7)

venue_probe equiv | commit ba86b3ae21b252be1c83e995381b467da49ad033 (dirty 1) | Release | 2026-10-20 23:39 | AMD  Radeon RX 7800 XT | 4.3.0 Core Profile Context 26.8.1.260810 | power throttling off (SetProcessInformation, EXECUTION_SPEED)

The full seat spawn (spawnSeatedCrowd, 100%, seed 1337: 63424 agents, buffer N = 65536), routed by the default model (queue-aware exit choice, incline speed, stair spacing (empirical)), the GPU pipeline (CrowdSim) against the CPU reference (CpuCrowdSim), both sort modes.

- one step from the GPU state after 200 steps (61362 active), CPU counting: cell table identical, gridID sequence differs at 0 slots, (gridID, boidID) pairs at 56558 (counting: boidID order within a cell) -> grid **exact**; |dpos| > 2e-4 for 0 agents (0.000%, limit < 0.5%: PASS), max 7.05e-07
- one step from the GPU state after 200 steps (61362 active), CPU bitonic: cell table identical, gridID sequence differs at 0 slots, (gridID, boidID) pairs at 0 -> grid **exact**; |dpos| > 2e-4 for 0 agents (0.000%, limit < 0.5%: PASS), max 7.05e-07
- CPU thread invariance (counting, 1 thread vs 20, 100 steps, every step's state chained): identical
- determinism: two GPU runs and two CPU runs of 250 steps: identical
- **golden** (FNV-1a 64 of the state after 250 steps): GPU **16ead091df60d13b**, CPU counting **107e45d468070142**, CPU bitonic **a0ac9c69b02f5ce6** (active 60800 / 60812 / 60812 of 63424)

Result: PASS (570 s)
