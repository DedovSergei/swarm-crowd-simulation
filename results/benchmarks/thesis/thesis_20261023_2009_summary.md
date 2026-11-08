# benchmark_crowd thesis thesis_20261023_2009

> Task 5.11 stage 3: the thesis benchmark (AMD 26.10.1.261008; the default model; the CPU's Task 5.11 tuned configuration)

Task 5.11's benchmark: one simulation step of the GPU pipeline (CrowdSim) and of the CPU reference (CpuCrowdSim, SortMode::Counting, schedule dynamic64 (physics), dynamic64 (projection), static (hash), exit choice parallel) at 20 threads and at 1 thread. (A) constant density: venues S, M, L at 100% load, the default model (queue-aware exit choice, incline speed, stair spacing EMPIRICAL); (B) the terrace at N = 1 024 .. 262 144 (the fixed-venue stress sweep, capacity labels). **The safety metrics are off** (CrowdSim alone, as in production benchmarking). Snapshot mode: every timed step starts from the identical agent state (restored outside the timed region); an analytic venue's exit choice runs on with its own 3 s rhythm.

Cell format: the median over rounds of the per-round median ms per step, the min-max of the round medians in brackets; p5 / p95: over every measured step of every round. GPU: GPU-execution time (GL_TIMESTAMP). CPU: steady_clock. Real-time factor = DT_real (174.907 ms of simulated time per step) / ms per step.

## (A) Constant density: venues S, M, L at 100% load

| workload | agents (N) | state | GPU ms | p5-p95 | CPU-20 ms | CPU-1 ms | GPU vs CPU-20 | CPU-20 vs CPU-1 | real-time factor GPU / CPU-20 / CPU-1 | label |
|---|---:|---|---:|---|---:|---:|---:|---:|---|---|
| venue_S | 3728 (4096) | spawn | 0.6775 (0.6600-0.6777) | 0.6541-0.7201 | 5.024 (5.002-5.283) | 53.93 (53.89-54.01) | 7.4x | 10.7x | 258 / 34.8 / 3.24 | within design capacity |
| venue_S | 1864 (4096) | congested | 1.278 (1.255-1.281) | 1.246-1.331 | 4.153 (4.137-4.420) | 37.93 (37.88-38.03) | 3.2x | 9.1x | 137 / 42.1 / 4.61 | within design capacity |
| venue_M | 15832 (16384) | spawn | 0.9737 (0.9474-0.9820) | 0.9350-1.161 | 20.20 (20.18-21.42) | 249.6 (249.0-251.2) | 20.7x | 12.4x | 180 / 8.7 / 0.70 | within design capacity |
| venue_M | 7913 (16384) | congested | 2.363 (2.359-2.393) | 2.306-2.449 | 16.22 (16.18-16.38) | 192.9 (192.7-193.7) | 6.9x | 11.9x | 74 / 10.8 / 0.91 | within design capacity |
| venue_L | 63424 (65536) | spawn | 1.861 (1.856-1.863) | 1.821-2.254 | 92.75 (92.62-93.09) | 1188.1 (1185.7-1188.2) | 49.8x | 12.8x | 94 / 1.9 / 0.15 | within design capacity |
| venue_L | 31703 (65536) | congested | 3.928 (3.921-3.935) | 3.798-4.105 | 67.97 (67.90-68.05) | 839.9 (837.7-841.0) | 17.3x | 12.4x | 45 / 2.6 / 0.21 | within design capacity |

### GPU per pass (GPU-execution ms, median over rounds)

| workload | state | hash | sort | cells / gather | exit choice | predict | projection (K - 1 iterations) | final pass | total | projection share | projection + final share |
|---|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| venue_S | spawn | 0.0016 | 0.0276 | 0.0036 | 0.0925 | 0.1932 | 0.3363 | 0.0221 | 0.6775 | 50% | 53% |
| venue_S | congested | 0.0016 | 0.0245 | 0.0033 | 0.1777 | 0.5096 | 0.4520 | 0.1085 | 1.278 | 35% | 44% |
| venue_M | spawn | 0.0013 | 0.0449 | 0.0055 | 0.1413 | 0.3611 | 0.3735 | 0.0318 | 0.9737 | 38% | 42% |
| venue_M | congested | 0.0018 | 0.0432 | 0.0070 | 0.3022 | 1.218 | 0.5923 | 0.1886 | 2.363 | 25% | 33% |
| venue_L | spawn | 0.0036 | 0.1064 | 0.0087 | 0.2039 | 0.7722 | 0.6953 | 0.0663 | 1.861 | 37% | 41% |
| venue_L | congested | 0.0050 | 0.0919 | 0.0088 | 0.4564 | 2.289 | 0.6879 | 0.3720 | 3.928 | 18% | 27% |

### CPU per stage (CPU-20 / CPU-1, ms, median over rounds)

| workload | state | threads | hash | sort | cells | exit choice | predict | projection | final | total |
|---|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| venue_S | spawn | 20 | 0.0086 | 0.0245 | 0.0210 | 0.1967 | 1.255 | 3.152 | 0.3656 | 5.024 |
| venue_S | spawn | 1 | 0.0306 | 0.0241 | 0.0192 | 1.840 | 12.75 | 35.50 | 3.702 | 53.93 |
| venue_S | congested | 20 | 0.0049 | 0.0228 | 0.0195 | 0.1598 | 1.170 | 2.473 | 0.2915 | 4.153 |
| venue_S | congested | 1 | 0.0248 | 0.0211 | 0.0140 | 1.209 | 11.52 | 22.51 | 2.609 | 37.93 |
| venue_M | spawn | 20 | 0.0173 | 0.0945 | 0.0827 | 0.8596 | 5.257 | 12.27 | 1.632 | 20.20 |
| venue_M | spawn | 1 | 0.1215 | 0.0847 | 0.0678 | 10.06 | 60.96 | 158.8 | 19.13 | 249.6 |
| venue_M | congested | 20 | 0.0185 | 0.0966 | 0.0699 | 0.6593 | 4.852 | 9.211 | 1.277 | 16.22 |
| venue_M | congested | 1 | 0.0994 | 0.0846 | 0.0546 | 7.238 | 55.30 | 115.7 | 14.29 | 192.9 |
| venue_L | spawn | 20 | 0.0762 | 0.3282 | 0.3065 | 4.655 | 30.60 | 48.18 | 8.535 | 92.75 |
| venue_L | spawn | 1 | 0.5111 | 0.3231 | 0.2577 | 56.78 | 371.0 | 653.0 | 105.3 | 1188.1 |
| venue_L | congested | 20 | 0.0758 | 0.3281 | 0.2604 | 2.957 | 22.06 | 36.70 | 5.515 | 67.97 |
| venue_L | congested | 1 | 0.4125 | 0.3306 | 0.2075 | 37.52 | 269.3 | 464.7 | 66.99 | 839.9 |

## (B) Fixed-venue stress sweep: the terrace

| workload | agents (N) | state | GPU ms | p5-p95 | CPU-20 ms | CPU-1 ms | GPU vs CPU-20 | CPU-20 vs CPU-1 | real-time factor GPU / CPU-20 / CPU-1 | label |
|---|---:|---|---:|---|---:|---:|---:|---:|---|---|
| terrace_1024 | 1024 (1024) | spawn | 0.3970 (0.3962-0.3978) | 0.3922-0.4396 | 1.652 (1.641-1.663) | 11.47 (11.46-11.49) | 4.2x | 6.9x | 441 / 105.9 / 15.25 | within design capacity |
| terrace_1024 | 774 (1024) | congested | 0.6013 (0.5869-0.6018) | 0.5821-0.6333 | 1.875 (1.855-1.892) | 10.89 (10.89-10.91) | 3.1x | 5.8x | 291 / 93.3 / 16.05 | within design capacity |
| terrace_4096 | 4096 (4096) | spawn | 0.7239 (0.7118-0.7265) | 0.7087-0.7540 | 8.837 (8.783-9.055) | 96.45 (96.44-96.57) | 12.2x | 10.9x | 242 / 19.8 / 1.81 | within design capacity |
| terrace_4096 | 3795 (4096) | congested | 0.8387 (0.8266-0.8428) | 0.8240-0.8792 | 8.471 (8.462-8.778) | 90.38 (90.30-91.11) | 10.1x | 10.7x | 209 / 20.6 / 1.94 | within design capacity |
| terrace_16384 | 16384 (16384) | spawn | 2.057 (2.056-2.060) | 2.049-2.142 | 72.91 (72.88-72.98) | 1015.5 (1013.5-1017.5) | 35.4x | 13.9x | 85 / 2.4 / 0.17 | above design capacity (N / design capacity = 4.00) |
| terrace_16384 | 15754 (16384) | congested | 3.557 (3.539-3.570) | 3.435-3.675 | 65.04 (64.94-65.10) | 902.4 (898.5-905.6) | 18.3x | 13.9x | 49 / 2.7 / 0.19 | above design capacity (N / design capacity = 4.00) |
| terrace_65536 | 65536 (65536) | spawn | 9.176 (9.170-9.179) | 8.836-9.317 | 954.7 (954.5-955.9) | 13661.0 (13650.5-13671.4) | 104.0x | 14.3x | 19 / 0.2 / 0.01 | physically impossible (N / jam capacity = 3.20) |
| terrace_65536 | 64731 (65536) | congested | 17.28 (17.18-17.30) | 16.97-17.40 | 1252.7 (1251.5-1253.7) | 18388.3 (18387.4-18389.2) | 72.5x | 14.7x | 10 / 0.1 / 0.01 | physically impossible (N / jam capacity = 3.20) |
| terrace_262144 | 262144 (262144) | spawn | 79.61 (79.61-79.68) | 79.32-80.14 | 15230.7 (15225.1-15270.3) | 213963.4 (213963.4-213963.4) | 191.3x | 14.0x | 2 / 0.0 / 0.00 | physically impossible (N / jam capacity = 12.78); over-capacity stress point |
| terrace_262144 | 261023 (262144) | congested | 123.6 (123.5-123.6) | 123.1-124.1 | 19436.9 (19431.9-19690.3) | 284572.6 (284572.6-284572.6) | 157.3x | 14.6x | 1 / 0.0 / 0.00 | physically impossible (N / jam capacity = 12.78); over-capacity stress point |

### GPU per pass (GPU-execution ms, median over rounds)

| workload | state | hash | sort | cells / gather | exit choice | predict | projection (K - 1 iterations) | final pass | total | projection share | projection + final share |
|---|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| terrace_1024 | spawn | 0.0014 | 0.0172 | 0.0031 | 0.0000 | 0.0456 | 0.2718 | 0.0560 | 0.3970 | 68% | 83% |
| terrace_1024 | congested | 0.0014 | 0.0157 | 0.0031 | 0.0000 | 0.0529 | 0.4500 | 0.0728 | 0.6013 | 75% | 87% |
| terrace_4096 | spawn | 0.0016 | 0.0278 | 0.0035 | 0.0000 | 0.0573 | 0.5646 | 0.0671 | 0.7239 | 78% | 87% |
| terrace_4096 | congested | 0.0016 | 0.0274 | 0.0035 | 0.0000 | 0.0616 | 0.6658 | 0.0780 | 0.8387 | 79% | 89% |
| terrace_16384 | spawn | 0.0017 | 0.0423 | 0.0084 | 0.0000 | 0.1079 | 1.780 | 0.1140 | 2.057 | 87% | 92% |
| terrace_16384 | congested | 0.0017 | 0.0425 | 0.0078 | 0.0000 | 0.1344 | 3.212 | 0.1795 | 3.557 | 90% | 95% |
| terrace_65536 | spawn | 0.0061 | 0.1020 | 0.0155 | 0.0000 | 0.3707 | 8.318 | 0.3503 | 9.176 | 91% | 94% |
| terrace_65536 | congested | 0.0065 | 0.1037 | 0.0212 | 0.0000 | 0.6464 | 15.92 | 0.5777 | 17.28 | 92% | 95% |
| terrace_262144 | spawn | 0.0321 | 0.4107 | 0.0682 | 0.0000 | 3.560 | 72.25 | 3.307 | 79.61 | 91% | 95% |
| terrace_262144 | congested | 0.0450 | 0.4146 | 0.0780 | 0.0000 | 4.928 | 113.8 | 4.347 | 123.6 | 92% | 96% |

### CPU per stage (CPU-20 / CPU-1, ms, median over rounds)

| workload | state | threads | hash | sort | cells | exit choice | predict | projection | final | total |
|---|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| terrace_1024 | spawn | 20 | 0.0027 | 0.0073 | 0.0099 | 0.0000 | 0.4576 | 1.031 | 0.1387 | 1.652 |
| terrace_1024 | spawn | 1 | 0.0077 | 0.0070 | 0.0071 | 0.0000 | 3.533 | 7.114 | 0.7916 | 11.47 |
| terrace_1024 | congested | 20 | 0.0028 | 0.0074 | 0.0075 | 0.0000 | 0.4785 | 1.238 | 0.1419 | 1.875 |
| terrace_1024 | congested | 1 | 0.0096 | 0.0069 | 0.0057 | 0.0000 | 2.877 | 7.289 | 0.6966 | 10.89 |
| terrace_4096 | spawn | 20 | 0.0085 | 0.0227 | 0.0269 | 0.0001 | 1.822 | 5.929 | 1.021 | 8.837 |
| terrace_4096 | spawn | 1 | 0.0299 | 0.0206 | 0.0182 | 0.0000 | 17.60 | 69.17 | 9.604 | 96.45 |
| terrace_4096 | congested | 20 | 0.0050 | 0.0216 | 0.0269 | 0.0000 | 1.605 | 6.219 | 0.5968 | 8.471 |
| terrace_4096 | congested | 1 | 0.0337 | 0.0219 | 0.0207 | 0.0000 | 16.01 | 68.56 | 5.715 | 90.38 |
| terrace_16384 | spawn | 20 | 0.0174 | 0.0796 | 0.0749 | 0.0001 | 8.332 | 58.00 | 6.345 | 72.91 |
| terrace_16384 | spawn | 1 | 0.1362 | 0.0794 | 0.0614 | 0.0001 | 90.03 | 849.5 | 75.75 | 1015.5 |
| terrace_16384 | congested | 20 | 0.0178 | 0.0799 | 0.0769 | 0.0001 | 7.474 | 52.78 | 4.567 | 65.04 |
| terrace_16384 | congested | 1 | 0.1273 | 0.0805 | 0.0624 | 0.0000 | 83.00 | 763.2 | 56.01 | 902.4 |
| terrace_65536 | spawn | 20 | 0.0772 | 0.2704 | 0.2826 | 0.0001 | 68.99 | 841.3 | 43.39 | 954.7 |
| terrace_65536 | spawn | 1 | 0.5206 | 0.2885 | 0.2356 | 0.0001 | 784.7 | 12294.4 | 579.2 | 13661.0 |
| terrace_65536 | congested | 20 | 0.0787 | 0.2834 | 0.2848 | 0.0001 | 86.27 | 1114.8 | 50.24 | 1252.7 |
| terrace_65536 | congested | 1 | 0.5318 | 0.2976 | 0.2364 | 0.0001 | 1004.0 | 16687.2 | 695.3 | 18388.3 |
| terrace_262144 | spawn | 20 | 0.3967 | 1.058 | 1.121 | 0.0000 | 877.9 | 13843.9 | 508.0 | 15230.7 |
| terrace_262144 | spawn | 1 | 2.106 | 1.188 | 0.9441 | 0.0000 | 10129.3 | 196779.5 | 7050.3 | 213963.4 |
| terrace_262144 | congested | 20 | 0.4048 | 1.066 | 1.119 | 0.0001 | 1163.2 | 17638.1 | 631.0 | 19436.9 |
| terrace_262144 | congested | 1 | 1.939 | 1.018 | 1.004 | 0.0000 | 13741.4 | 261711.3 | 9116.0 | 284572.6 |

## Measurement stability: reference probe (GPU, terrace N = 4096, spawn snapshot, 300 steps, start of every round)

| round | median ms |
|---:|---:|
| 0 | 0.7240 |
| 1 | 0.7262 |
| 2 | 0.7101 |
| 3 | 0.7282 |
| 4 | 0.7233 |

**Probe coefficient of variation across rounds: 0.99%** (mean 0.7224 ms, min 0.7101, max 0.7282)

## Workloads

| workload | N (buffer) | state | active | definition |
|---|---:|---|---:|---|
| venue_S | 4096 | spawn | 3728 | spawnSeatedCrowd(venue, N, 100%, seed 1337): every seat |
| venue_S | 4096 | congested | 1864 | GPU state at t50 of the 100% run: step 657 (114.9 s), 1864 of 3728 agents left |
| venue_M | 16384 | spawn | 15832 | spawnSeatedCrowd(venue, N, 100%, seed 1337): every seat |
| venue_M | 16384 | congested | 7913 | GPU state at t50 of the 100% run: step 1284 (224.6 s), 7919 of 15832 agents left |
| venue_L | 65536 | spawn | 63424 | spawnSeatedCrowd(venue, N, 100%, seed 1337): every seat |
| venue_L | 65536 | congested | 31703 | GPU state at t50 of the 100% run: step 3044 (532.4 s), 31721 of 63424 agents left |
| terrace_1024 | 1024 | spawn | 1024 | spawnBleacherCrowd(N) |
| terrace_1024 | 1024 | congested | 774 | GPU state after 250 steps from spawn (Task 4.3b's definition) |
| terrace_4096 | 4096 | spawn | 4096 | spawnBleacherCrowd(N) |
| terrace_4096 | 4096 | congested | 3795 | GPU state after 250 steps from spawn (Task 4.3b's definition) |
| terrace_16384 | 16384 | spawn | 16384 | spawnBleacherCrowd(N) |
| terrace_16384 | 16384 | congested | 15754 | GPU state after 250 steps from spawn (Task 4.3b's definition) |
| terrace_65536 | 65536 | spawn | 65536 | spawnBleacherCrowd(N) |
| terrace_65536 | 65536 | congested | 64731 | GPU state after 250 steps from spawn (Task 4.3b's definition) |
| terrace_262144 | 262144 | spawn | 262144 | spawnBleacherCrowd(N) |
| terrace_262144 | 262144 | congested | 261023 | GPU state after 250 steps from spawn (Task 4.3b's definition) |

## Protocol

- Rounds: 5; each starts with the probe, then every (workload, state, implementation) cell in an order rotated between rounds.
- Steps per cell (warm-up + measured) and rounds: `thesis_20261023_2009_cells.csv` (CPU-1 at 65 536 and above: fewer steps and rounds).
- GPU warm-up: >= 200 steps and >= 2 s of sustained load per cell. CPU warm-up: 20 steps, or fewer (>= 2) once 2 s ran.
- The GPU's physics split: timestamps in CrowdSim's dispatch hook (after the cells pass, the exit choice's last dispatch, the predict pass, the projection's last iteration, the final pass); the ring's physics interval = their sum.
- Elapsed: 53 min.

```
self-check (abort on failure):
  (CPU counting N = 4096 at 20 thread(s), schedule dynamic64)
  (CPU bitonic N = 4096 at 20 thread(s), schedule dynamic64)
  (CPU counting N = 4096 at 1 thread(s), schedule dynamic64)
  golden GPU N = 4096           c78d743496d02748 pinned c78d743496d02748: match
  golden GPU N = 65536          e4e589d428d02a31 pinned e4e589d428d02a31: match
  golden CPU counting N = 4096  f6acc34947d51106 pinned f6acc34947d51106: match
  golden CPU bitonic N = 4096   0fe0246dbd6703fe pinned 0fe0246dbd6703fe: match
  golden CPU counting N = 4096  f6acc34947d51106 pinned f6acc34947d51106: match
  equivalence N = 4096 congested, one step, CPU counting (dynamic64): gridID slots != GPU 0, cells != GPU 0, |dpos| > 2e-4: 0 of 3795 active (0.000%, limit 0.5%), 1 thread == 20 threads: bit-identical -> pass
self-check passed
  golden GPU venue S routed             706f97c4846bc167 pinned 706f97c4846bc167: match
  golden CPU counting venue S routed    434356ac8d65471d pinned 434356ac8d65471d: match
  golden CPU bitonic venue S routed     5e72f98915ca108f pinned 5e72f98915ca108f: match
  golden GPU venue M routed             0fa616143c51c4c9 pinned 0fa616143c51c4c9: match
  golden CPU counting venue M routed    dfbb0cd26213add2 pinned dfbb0cd26213add2: match
  golden GPU venue L routed             56ca268d9dfb4bed pinned 56ca268d9dfb4bed: match
  golden CPU counting venue L routed    107e45d468070142 pinned 107e45d468070142: match
venue self-check passed
```

## Metadata

| key | value |
|---|---|
| run_id | thesis_20261023_2009 |
| timestamp | 2026-10-23T20:09:14 |
| git commit | 2460e1c59e38aaecfb32bf43be1679eb3fbcf232 |
| git dirty | 0 (at build time) |
| build | Release |
| simulation core flags | `/DWIN32 /D_WINDOWS /GR /EHsc /O2 /Ob2 /DNDEBUG -openmp /fp:precise` |
| clock note | adrenalin manual min2500 max2620 |
| GPU (GL_RENDERER) | AMD  Radeon RX 7800 XT |
| driver (GL_VERSION) | 4.3.0 Core Profile Context 26.10.1.261008 |
| CPU | 13th Gen Intel(R) Core(TM) i5-13600KF |
| logical cores | 20 |
| OpenMP max threads | 20 |
| CPU schedule | dynamic64 (physics), dynamic64 (projection), static (hash), exit choice parallel |
| CPU sort mode | counting |
| safety metrics | off |
| process QoS | power throttling off (SetProcessInformation, EXECUTION_SPEED) |
