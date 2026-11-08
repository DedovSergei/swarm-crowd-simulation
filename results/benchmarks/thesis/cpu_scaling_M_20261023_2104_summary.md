# CPU thread scaling cpu_scaling_M_20261023_2104

CpuCrowdSim on venue M at 100% load (7913 agents in N = 16384), the default model, SortMode::Counting, schedule dynamic64 (physics), dynamic64 (projection), static (hash), exit choice parallel, snapshot mode (restoreAgentState: the exit choice runs on), steady_clock ms per step: the median over 3 rounds of the per-round median (20 measured steps per round). CPU: 13th Gen Intel(R) Core(TM) i5-13600KF (20 logical cores: 6 P-cores with 2 threads each = 12, plus 8 E-cores). Commit 2460e1c59e38aaecfb32bf43be1679eb3fbcf232 (dirty 0), Release, flags `/DWIN32 /D_WINDOWS /GR /EHsc /O2 /Ob2 /DNDEBUG -openmp /fp:precise`, process QoS: power throttling off (SetProcessInformation, EXECUTION_SPEED). Safety metrics off.

| state | threads | ms/step (min-max of the rounds) | exit choice | predict | projection | final | speedup vs 1 | efficiency |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| congested | 1 | 192.6 (192.5-193.1) | 7.196 | 55.13 | 115.6 | 14.28 | 1.00x | 100% |
| congested | 2 | 96.36 (96.33-96.64) | 3.555 | 27.68 | 57.73 | 7.171 | 2.00x | 100% |
| congested | 4 | 48.56 (48.50-48.59) | 1.838 | 14.00 | 28.89 | 3.628 | 3.97x | 99% |
| congested | 6 | 32.64 (32.60-32.68) | 1.250 | 9.344 | 19.41 | 2.471 | 5.90x | 98% |
| congested | 8 | 26.39 (26.35-26.48) | 1.035 | 7.619 | 15.53 | 2.003 | 7.30x | 91% |
| congested | 12 | 21.30 (20.38-21.95) | 0.8728 | 6.161 | 12.25 | 1.639 | 9.04x | 75% |
| congested | 14 | 18.73 (17.87-20.15) | 0.7601 | 5.466 | 10.77 | 1.472 | 10.29x | 73% |
| congested | 16 | 17.67 (17.66-17.83) | 0.7314 | 5.235 | 10.13 | 1.377 | 10.90x | 68% |
| congested | 20 | 16.20 (16.14-16.21) | 0.6553 | 4.809 | 9.206 | 1.281 | 11.89x | 59% |
