# Task 4.4-3 A/B: sorted gather for physics (new) vs Task 4.4-2 (base)

Started 2026-10-02T14:20:53, 14.9 min, 12 rounds, warm-up >= 2.0 s per process, snapshots `out/bench/snapshots`, timed steps each from a restore of the snapshot. GPU before the run: QUIET for 60 s at 14:20:53.

| label | executable | environment | git commit | dirty | GPU | driver | process QoS |
|---|---|---|---|---|---|---|---|
| base | `out\perf\s2\build\bench.exe` | - | f85eb185b35b6bf979f480c722ef95008269d722 | 0 | AMD  Radeon RX 7800 XT | 4.3.0 Core Profile Context 26.8.1.260810 | power throttling off (SetProcessInformation, EXECUTION_SPEED) |
| base_aa | `out\perf\s2\build\bench.exe` | - | f85eb185b35b6bf979f480c722ef95008269d722 | 0 | AMD  Radeon RX 7800 XT | 4.3.0 Core Profile Context 26.8.1.260810 | power throttling off (SetProcessInformation, EXECUTION_SPEED) |
| new | `out\perf\s3new\bench.exe` | - | f85eb185b35b6bf979f480c722ef95008269d722 | 1 | AMD  Radeon RX 7800 XT | 4.3.0 Core Profile Context 26.8.1.260810 | power throttling off (SetProcessInformation, EXECUTION_SPEED) |

Protocol: tools/perf_ab/ab.py (rotated per cell, Latin square), `bench cell` snapshot mode (GPU-side restore before every step, outside the timestamps), GPU-execution ms from CrowdSim's timestamp ring. Cell value: median over rounds of the per-round median. Noise rule: |delta| > 2 x |A/A delta| and sign test p < 0.05 over the paired rounds.

## Total step

| N | state | base ms (min-max) | base_aa ms (min-max) | vs base | new ms (min-max) | vs base | verdict |
|---:|---|---:|---:|---:|---:|---:|---|
| 1024 | spawn | 0.0363 (0.0363-0.0363) | 0.0363 (0.0363-0.0364) | +0.1% (3/12, p 0.727) | 0.0342 (0.0342-0.0342) | -5.7% (12/12, p 0.000) | new: faster |
| 1024 | congested | 0.0550 (0.0548-0.0550) | 0.0550 (0.0548-0.0550) | +0.1% (4/12, p 0.754) | 0.0493 (0.0491-0.0493) | -10.4% (12/12, p 0.000) | new: faster |
| 4096 | spawn | 0.0669 (0.0651-0.0670) | 0.0668 (0.0636-0.0670) | -0.2% (9/12, p 0.065) | 0.0596 (0.0583-0.0597) | -10.9% (12/12, p 0.000) | new: faster |
| 4096 | congested | 0.0868 (0.0865-0.0869) | 0.0868 (0.0841-0.0869) | +0.0% (5/12, p 1.000) | 0.0751 (0.0730-0.0752) | -13.5% (12/12, p 0.000) | new: faster |
| 16384 | spawn | 0.1704 (0.1680-0.1722) | 0.1682 (0.1670-0.1715) | -1.3% (10/12, p 0.039) | 0.1255 (0.1204-0.1257) | -26.4% (12/12, p 0.000) | new: faster |
| 16384 | congested | 0.2715 (0.2686-0.2724) | 0.2716 (0.2686-0.2727) | +0.0% (4/12, p 0.388) | 0.1953 (0.1912-0.1961) | -28.1% (12/12, p 0.000) | new: faster |
| 65536 | spawn | 0.6324 (0.6224-0.6406) | 0.6291 (0.6265-0.6456) | -0.5% (7/12, p 0.774) | 0.4610 (0.4551-0.4647) | -27.1% (12/12, p 0.000) | new: faster |
| 65536 | congested | 1.0169 (0.9987-1.0216) | 1.0157 (0.9977-1.0219) | -0.1% (8/12, p 0.388) | 0.7048 (0.6999-0.7233) | -30.7% (12/12, p 0.000) | new: faster |
| 262144 | spawn | 5.5496 (5.4898-6.2142) | 5.5371 (5.5106-5.5684) | -0.2% (8/12, p 0.388) | 3.4370 (3.3268-3.4580) | -38.1% (12/12, p 0.000) | new: faster |
| 262144 | congested | 8.1235 (8.0645-9.0272) | 8.8418 (8.0561-9.0350) | +8.8% (5/12, p 0.774) | 4.9906 (4.9635-5.0214) | -38.6% (12/12, p 0.000) | new: faster |

Deltas: (rounds where the label was faster than base / rounds, sign-test p). base_aa is the A/A control (base again): its delta is the noise floor.

## Per pass (median over rounds of the per-round medians, ms): hash / sort / cells / physics

| N | state | base | base_aa | new | new vs base |
|---:|---|---|---|---|---|
| 1024 | spawn | 0.0014 / 0.0148 / 0.0020 / 0.0180 | 0.0013 / 0.0148 / 0.0020 / 0.0180 | 0.0013 / 0.0148 / 0.0029 / 0.0156 | -2.9% / +0.0% / +44.5% / -13.3% |
| 1024 | congested | 0.0014 / 0.0142 / 0.0020 / 0.0372 | 0.0014 / 0.0142 / 0.0020 / 0.0372 | 0.0014 / 0.0136 / 0.0029 / 0.0311 | +2.9% / -4.5% / +41.2% / -16.4% |
| 4096 | spawn | 0.0016 / 0.0249 / 0.0022 / 0.0379 | 0.0016 / 0.0249 / 0.0022 / 0.0378 | 0.0017 / 0.0249 / 0.0025 / 0.0302 | +5.0% / +0.0% / +16.7% / -20.4% |
| 4096 | congested | 0.0016 / 0.0247 / 0.0022 / 0.0579 | 0.0016 / 0.0247 / 0.0022 / 0.0580 | 0.0016 / 0.0247 / 0.0026 / 0.0457 | +2.5% / +0.1% / +14.3% / -21.2% |
| 16384 | spawn | 0.0017 / 0.0402 / 0.0047 / 0.1238 | 0.0017 / 0.0397 / 0.0046 / 0.1226 | 0.0016 / 0.0403 / 0.0063 / 0.0770 | -8.1% / +0.4% / +36.1% / -37.8% |
| 16384 | congested | 0.0017 / 0.0394 / 0.0044 / 0.2262 | 0.0017 / 0.0395 / 0.0044 / 0.2263 | 0.0017 / 0.0402 / 0.0063 / 0.1473 | +2.4% / +2.1% / +42.7% / -34.9% |
| 65536 | spawn | 0.0050 / 0.0904 / 0.0096 / 0.5244 | 0.0052 / 0.0899 / 0.0096 / 0.5228 | 0.0053 / 0.0925 / 0.0150 / 0.3466 | +5.2% / +2.3% / +55.7% / -33.9% |
| 65536 | congested | 0.0064 / 0.0941 / 0.0103 / 0.9012 | 0.0065 / 0.0940 / 0.0106 / 0.8998 | 0.0048 / 0.0909 / 0.0182 / 0.5920 | -25.3% / -3.5% / +75.7% / -34.3% |
| 262144 | spawn | 0.0137 / 0.3318 / 0.0219 / 5.1851 | 0.0137 / 0.3314 / 0.0218 / 5.1766 | 0.0140 / 0.3424 / 0.0418 / 3.0367 | +1.8% / +3.2% / +91.5% / -41.4% |
| 262144 | congested | 0.0140 / 0.3343 / 0.0253 / 7.7501 | 0.0183 / 0.3347 / 0.0264 / 8.4597 | 0.0138 / 0.3365 / 0.0444 / 4.6029 | -1.5% / +0.6% / +75.5% / -40.6% |

## Results identical across builds

State hash one step after each snapshot (FNV-1a 64), every label, every round: identical in every cell.
- N = 1024 spawn: d4f820fdeafa9a90
- N = 1024 congested: 32b915038bb029e9
- N = 4096 spawn: 681aa11cac46b885
- N = 4096 congested: f5a4bacf45344e56
- N = 16384 spawn: 5c3a5fc956feccb0
- N = 16384 congested: f2a1e3e6a2ac6411
- N = 65536 spawn: 04be590fd4621eb6
- N = 65536 congested: 39be924e8b04622b
- N = 262144 spawn: b707425ce5ac9d92
- N = 262144 congested: 9cd2e00348db7365

Other processes' GPU use during the run (every 10 s, `ab_4.4-3_20261002_1419_gpu_other.csv`): max 2.69%, mean 1.07% over 81 samples.
