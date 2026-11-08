# Venue M: CPU/GPU equivalence of the production program (Task 5.7)

venue_probe equiv | commit 372a5c19c97779f851bd5737b102b7136c2f09ce (dirty 0) | Release | 2026-10-12 19:57 | AMD  Radeon RX 7800 XT | 4.3.0 Core Profile Context 26.8.1.260810 | power throttling off (SetProcessInformation, EXECUTION_SPEED)

The full seat spawn (spawnSeatedCrowd, 100%, seed 1337: 15832 agents, buffer N = 16384), routed by the default model (queue-aware exit choice, incline speed), the GPU pipeline (CrowdSim) against the CPU reference (CpuCrowdSim), both sort modes.

- one step from the GPU state after 200 steps (14453 active), CPU counting: cell table identical, gridID sequence differs at 0 slots, (gridID, boidID) pairs at 14029 (counting: boidID order within a cell) -> grid **exact**; |dpos| > 2e-4 for 0 agents (0.000%, limit < 0.5%: PASS), max 4.66e-07
- one step from the GPU state after 200 steps (14453 active), CPU bitonic: cell table identical, gridID sequence differs at 0 slots, (gridID, boidID) pairs at 0 -> grid **exact**; |dpos| > 2e-4 for 0 agents (0.000%, limit < 0.5%: PASS), max 4.66e-07
- CPU thread invariance (counting, 1 thread vs 20, 100 steps, every step's state chained): identical
- determinism: two GPU runs and two CPU runs of 250 steps: identical
- **golden** (FNV-1a 64 of the state after 250 steps): GPU **c3682e4998ef9673**, CPU counting **c7d9dce76083ce21**, CPU bitonic **518d0c2aa349a17c** (active 14030 / 14034 / 14034 of 15832)

Result: PASS (110 s)
