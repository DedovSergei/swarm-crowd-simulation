# Task 5.3b stage C: Stage 0 (a10c431) vs the 5.3b model, with and without the projection

Started 2026-10-05T17:06:29, 9.1 min, 12 rounds, warm-up >= 2.0 s per process, snapshots `out/bench/snapshots`, timed steps each from a restore of the snapshot. GPU before the run: QUIET for 60 s at 17:06:29.

| label | executable | environment | git commit | dirty | GPU | driver | process QoS |
|---|---|---|---|---|---|---|---|
| s0 | `..\hard-body-gravity-calibration-4dc211\out\perf\s0\build\bench.exe` | SWARM_BENCH_SNAPSHOTS=../hard-body-gravity-calibration-4dc211/out/bench/snapshots_s0 | a10c4316bcc83149b795d00a233e1c751173ab8a | 0 | AMD  Radeon RX 7800 XT | 4.3.0 Core Profile Context 26.8.1.260810 | power throttling off (SetProcessInformation, EXECUTION_SPEED) |
| s0_aa | `..\hard-body-gravity-calibration-4dc211\out\perf\s0\build\bench.exe` | SWARM_BENCH_SNAPSHOTS=../hard-body-gravity-calibration-4dc211/out/bench/snapshots_s0 | a10c4316bcc83149b795d00a233e1c751173ab8a | 0 | AMD  Radeon RX 7800 XT | 4.3.0 Core Profile Context 26.8.1.260810 | power throttling off (SetProcessInformation, EXECUTION_SPEED) |
| new | `out\build\x64-Release\bench.exe` | SWARM_BENCH_SNAPSHOTS=out/bench/snapshots_5.3b | b9d468693a08206ae85afed8f0568a334811d181 | 0 | AMD  Radeon RX 7800 XT | 4.3.0 Core Profile Context 26.8.1.260810 | power throttling off (SetProcessInformation, EXECUTION_SPEED) |
| new_noproj | `out\build\x64-Release\bench.exe` | SWARM_BENCH_SNAPSHOTS=out/bench/snapshots_5.3b SWARM_BENCH_PROJ_ITERS=0 | b9d468693a08206ae85afed8f0568a334811d181 | 0 | AMD  Radeon RX 7800 XT | 4.3.0 Core Profile Context 26.8.1.260810 | power throttling off (SetProcessInformation, EXECUTION_SPEED) |

Protocol: tools/perf_ab/ab.py (rotated per cell, Latin square), `bench cell` snapshot mode (GPU-side restore before every step, outside the timestamps), GPU-execution ms from CrowdSim's timestamp ring. Cell value: median over rounds of the per-round median. Noise rule: |delta| > 2 x |A/A delta| and sign test p < 0.05 over the paired rounds.

## Total step

| N | state | s0 ms (min-max) | s0_aa ms (min-max) | vs s0 | new ms (min-max) | vs s0 | new_noproj ms (min-max) | vs s0 | verdict |
|---:|---|---:|---:|---:|---:|---:|---:|---:|---|
| 4096 | spawn | 0.0597 (0.0583-0.0598) | 0.0596 (0.0582-0.0597) | -0.1% (7/12, p 0.549) | 0.6463 (0.6455-0.6468) | +982.8% (0/12, p 0.000) | 0.0827 (0.0802-0.0828) | +38.5% (0/12, p 0.000) | new: slower; new_noproj: slower |
| 4096 | congested | 0.0752 (0.0742-0.0752) | 0.0752 (0.0746-0.0753) | -0.0% (7/12, p 0.774) | 0.7478 (0.7463-0.7491) | +894.4% (0/12, p 0.000) | 0.0877 (0.0837-0.0878) | +16.6% (0/12, p 0.000) | new: slower; new_noproj: slower |
| 65536 | spawn | 0.4604 (0.4482-0.4649) | 0.4605 (0.4479-0.4635) | +0.0% (5/12, p 0.774) | 9.0722 (8.7365-9.1271) | +1870.6% (0/12, p 0.000) | 0.5375 (0.5197-0.5415) | +16.8% (0/12, p 0.000) | new: slower; new_noproj: slower |
| 65536 | congested | 0.7086 (0.6882-0.7190) | 0.7033 (0.6960-0.7182) | -0.7% (7/12, p 0.774) | 19.5158 (19.4187-19.5494) | +2654.2% (0/12, p 0.000) | 0.9594 (0.9370-0.9633) | +35.4% (0/12, p 0.000) | new: slower; new_noproj: slower |

Deltas: (rounds where the label was faster than s0 / rounds, sign-test p). s0_aa is the A/A control (s0 again): its delta is the noise floor.

## Per pass (median over rounds of the per-round medians, ms): hash / sort / cells / physics

| N | state | s0 | s0_aa | new | new_noproj | new vs s0 | new_noproj vs s0 |
|---:|---|---|---|---|---|---|---|
| 4096 | spawn | 0.0017 / 0.0250 / 0.0025 / 0.0303 | 0.0017 / 0.0249 / 0.0025 / 0.0300 | 0.0016 / 0.0244 / 0.0032 / 0.6174 | 0.0024 / 0.0253 / 0.0029 / 0.0521 | -4.8% / -2.1% / +26.4% / +1940.4% | +40.5% / +1.3% / +17.6% / +72.1% |
| 4096 | congested | 0.0016 / 0.0247 / 0.0026 / 0.0458 | 0.0016 / 0.0247 / 0.0026 / 0.0458 | 0.0016 / 0.0243 / 0.0031 / 0.7187 | 0.0024 / 0.0251 / 0.0030 / 0.0572 | -2.4% / -1.8% / +21.8% / +1469.1% | +43.9% / +1.5% / +16.0% / +24.8% |
| 65536 | spawn | 0.0052 / 0.0923 / 0.0149 / 0.3466 | 0.0052 / 0.0923 / 0.0150 / 0.3464 | 0.0052 / 0.0889 / 0.0148 / 8.9629 | 0.0053 / 0.0929 / 0.0154 / 0.4202 | -0.2% / -3.8% / -0.7% / +2485.7% | +2.1% / +0.6% / +3.4% / +21.2% |
| 65536 | congested | 0.0055 / 0.0917 / 0.0170 / 0.5922 | 0.0048 / 0.0907 / 0.0144 / 0.5915 | 0.0066 / 0.0897 / 0.0205 / 19.3949 | 0.0044 / 0.0912 / 0.0148 / 0.8462 | +19.3% / -2.2% / +21.0% / +3174.8% | -20.0% / -0.6% / -13.1% / +42.9% |

## Results per label (the labels run different models: --models-differ)

State hash one step after each snapshot (FNV-1a 64): one hash per label and cell in every round, the A/A control identical to the reference.
- N = 4096 spawn: s0 681aa11cac46b885; s0_aa 681aa11cac46b885; new a32e35b90b9ded1d; new_noproj 70ff3edf69935572
- N = 4096 congested: s0 f5a4bacf45344e56; s0_aa f5a4bacf45344e56; new 5929bcb9b539fc30; new_noproj 135ae40b4b084ee3
- N = 65536 spawn: s0 04be590fd4621eb6; s0_aa 04be590fd4621eb6; new fe7543a85ee40b66; new_noproj 12c8cb4be1189665
- N = 65536 congested: s0 39be924e8b04622b; s0_aa 39be924e8b04622b; new 16c9207a2f16cc99; new_noproj a568c03202442698

Snapshots and projection iterations per label (META): s0: `../hard-body-gravity-calibration-4dc211/out/bench/snapshots_s0`, K -; s0_aa: `../hard-body-gravity-calibration-4dc211/out/bench/snapshots_s0`, K -; new: `out/bench/snapshots_5.3b`, K 32; new_noproj: `out/bench/snapshots_5.3b`, K 0.

Other processes' GPU use during the run (every 10 s, `ab_5.3b_20261005_1705_gpu_other.csv`): max 2.47%, mean 0.98% over 49 samples.
