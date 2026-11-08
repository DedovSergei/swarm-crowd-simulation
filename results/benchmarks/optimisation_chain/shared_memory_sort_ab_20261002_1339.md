# Task 4.4-2 A/B: shared-memory bitonic stages (new) vs Task 4.4-1 (base)

Started 2026-10-02T13:40:45, 14.9 min, 12 rounds, warm-up >= 2.0 s per process, snapshots `out/bench/snapshots`. GPU before the run: QUIET for 60 s at 13:40:45.

| label | executable | git commit | dirty | GPU | driver | process QoS |
|---|---|---|---|---|---|---|
| base | `out\perf\s1\build\bench.exe` | 9b9c81861eb38a7326390c9c256a75f2429e6732 | 0 | AMD  Radeon RX 7800 XT | 4.3.0 Core Profile Context 26.8.1.260810 | power throttling off (SetProcessInformation, EXECUTION_SPEED) |
| base_aa | `out\perf\s1\build\bench.exe` | 9b9c81861eb38a7326390c9c256a75f2429e6732 | 0 | AMD  Radeon RX 7800 XT | 4.3.0 Core Profile Context 26.8.1.260810 | power throttling off (SetProcessInformation, EXECUTION_SPEED) |
| new | `out\perf\s2new\bench.exe` | 9b9c81861eb38a7326390c9c256a75f2429e6732 | 1 | AMD  Radeon RX 7800 XT | 4.3.0 Core Profile Context 26.8.1.260810 | power throttling off (SetProcessInformation, EXECUTION_SPEED) |

Protocol: tools/perf_ab/ab.py (rotated per cell, Latin square), `bench cell` snapshot mode (GPU-side restore before every step, outside the timestamps), GPU-execution ms from CrowdSim's timestamp ring. Cell value: median over rounds of the per-round median. Noise rule: |delta| > 2 x |A/A delta| and sign test p < 0.05 over the paired rounds.

## Total step

| N | state | base ms (min-max) | base_aa ms (min-max) | vs base | new ms (min-max) | vs base | verdict |
|---:|---|---:|---:|---:|---:|---:|---|
| 1024 | spawn | 0.0710 (0.0707-0.0712) | 0.0709 (0.0706-0.0712) | -0.1% (5/12, p 0.774) | 0.0363 (0.0363-0.0364) | -48.8% (12/12, p 0.000) | new: faster |
| 1024 | congested | 0.0900 (0.0897-0.0902) | 0.0900 (0.0896-0.0902) | -0.1% (8/12, p 0.388) | 0.0550 (0.0543-0.0550) | -38.9% (12/12, p 0.000) | new: faster |
| 4096 | spawn | 0.1128 (0.1125-0.1130) | 0.1128 (0.1124-0.1132) | -0.1% (6/12, p 1.000) | 0.0667 (0.0657-0.0670) | -40.9% (12/12, p 0.000) | new: faster |
| 4096 | congested | 0.1329 (0.1312-0.1331) | 0.1329 (0.1316-0.1330) | -0.0% (7/12, p 0.344) | 0.0869 (0.0865-0.0870) | -34.6% (12/12, p 0.000) | new: faster |
| 16384 | spawn | 0.2372 (0.2331-0.2375) | 0.2367 (0.2362-0.2377) | -0.2% (7/12, p 0.774) | 0.1707 (0.1645-0.1721) | -28.0% (12/12, p 0.000) | new: faster |
| 16384 | congested | 0.3444 (0.3381-0.3470) | 0.3442 (0.3414-0.3451) | -0.1% (9/12, p 0.146) | 0.2716 (0.2686-0.2734) | -21.1% (12/12, p 0.000) | new: faster |
| 65536 | spawn | 0.7496 (0.7464-0.7553) | 0.7519 (0.7351-0.7544) | +0.3% (6/12, p 1.000) | 0.6311 (0.6251-0.6487) | -15.8% (12/12, p 0.000) | new: faster |
| 65536 | congested | 1.1291 (1.1206-1.1325) | 1.1271 (1.1167-1.1333) | -0.2% (7/12, p 0.774) | 1.0186 (1.0112-1.0239) | -9.8% (12/12, p 0.000) | new: faster |
| 262144 | spawn | 5.9392 (5.8865-5.9542) | 5.9358 (5.8977-5.9664) | -0.1% (5/12, p 0.774) | 5.5483 (5.4907-6.2669) | -6.6% (9/12, p 0.146) | new: within noise |
| 262144 | congested | 8.4895 (8.4438-8.5604) | 8.4909 (8.4259-8.5324) | +0.0% (7/12, p 0.774) | 8.9712 (8.0124-9.0579) | +5.7% (4/12, p 0.388) | new: within noise |

Deltas: (rounds where the label was faster than base / rounds, sign-test p). base_aa is the A/A control (base again): its delta is the noise floor.

## Per pass (median over rounds of the per-round medians, ms): hash / sort / cells / physics

| N | state | base | base_aa | new | new vs base |
|---:|---|---|---|---|---|
| 1024 | spawn | 0.0013 / 0.0495 / 0.0020 / 0.0180 | 0.0013 / 0.0495 / 0.0020 / 0.0180 | 0.0014 / 0.0148 / 0.0020 / 0.0180 | +2.3% / -70.0% / +2.0% / +0.2% |
| 1024 | congested | 0.0014 / 0.0493 / 0.0020 / 0.0372 | 0.0013 / 0.0493 / 0.0020 / 0.0372 | 0.0014 / 0.0142 / 0.0020 / 0.0372 | +0.0% / -71.1% / +2.0% / +0.1% |
| 4096 | spawn | 0.0016 / 0.0712 / 0.0022 / 0.0378 | 0.0016 / 0.0711 / 0.0022 / 0.0377 | 0.0016 / 0.0249 / 0.0022 / 0.0378 | +0.0% / -65.0% / +0.0% / +0.0% |
| 4096 | congested | 0.0016 / 0.0710 / 0.0022 / 0.0579 | 0.0016 / 0.0710 / 0.0022 / 0.0578 | 0.0016 / 0.0247 / 0.0022 / 0.0581 | +0.0% / -65.3% / +0.0% / +0.3% |
| 16384 | spawn | 0.0017 / 0.1056 / 0.0048 / 0.1247 | 0.0017 / 0.1055 / 0.0047 / 0.1246 | 0.0017 / 0.0403 / 0.0047 / 0.1241 | +0.0% / -61.9% / -1.5% / -0.5% |
| 16384 | congested | 0.0017 / 0.1056 / 0.0046 / 0.2321 | 0.0017 / 0.1056 / 0.0046 / 0.2319 | 0.0017 / 0.0395 / 0.0044 / 0.2263 | -2.3% / -62.6% / -3.5% / -2.5% |
| 65536 | spawn | 0.0069 / 0.1964 / 0.0109 / 0.5320 | 0.0067 / 0.1969 / 0.0110 / 0.5333 | 0.0053 / 0.0901 / 0.0096 / 0.5236 | -23.4% / -54.1% / -11.9% / -1.6% |
| 65536 | congested | 0.0068 / 0.1955 / 0.0109 / 0.9117 | 0.0067 / 0.1951 / 0.0105 / 0.9107 | 0.0068 / 0.0949 / 0.0108 / 0.9009 | -0.3% / -51.5% / -1.0% / -1.2% |
| 262144 | spawn | 0.0138 / 0.6822 / 0.0187 / 5.2274 | 0.0138 / 0.6823 / 0.0188 / 5.2181 | 0.0138 / 0.3315 / 0.0213 / 5.1859 | -0.1% / -51.4% / +13.5% / -0.8% |
| 262144 | congested | 0.0139 / 0.6752 / 0.0220 / 7.7817 | 0.0138 / 0.6742 / 0.0220 / 7.7741 | 0.0187 / 0.3388 / 0.0270 / 8.5844 | +34.9% / -49.8% / +22.7% / +10.3% |

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

Other processes' GPU use during the run (every 10 s, `ab_4.4-2_20261002_1339_gpu_other.csv`): max 4.25%, mean 1.03% over 81 samples.
