# Intel UHD Graphics: the terrace on a laptop

Screenshots from the laptop in [RESULTS.md](../../../RESULTS.md)'s test platforms: Windows 10 Pro 22H2, Intel Core i5-1035G1, Intel UHD Graphics, driver 31.0.101.2141 (`intel_uhd_driver_31.0.101.2141.png`). Each reading below is one reading of the viewer's panel during one run, not a benchmark. No result in RESULTS.md comes from this machine.

## The v1.0 zip

The program zip built at commit 4f60ee3, which the panel shows. After that commit the release changes only documentation and packaging, moving S's and M's navigation tables into the program zip.

The program started with no DLL error, because the Microsoft Visual C++ Redistributable was already installed there. Its window fit the laptop's screen.

| file | shows | readings |
|---|---|---|
| `intel_uhd_v1.0_terrace_running_1.05x.png` | terrace, 4 096 agents, at 208.5 s | 1.00x real time requested, 1.05x achieved, 305 FPS |
| `intel_uhd_v1.0_terrace_evacuated_475.7s.png` | terrace, 4 096 agents, at the end | stopped at 475.7 s (step 2720), first reading with 0 active at 475.6 s; exits +x 1031, -x 1035, +y 968, -y 1062 |

- The evacuation ends as in the pre-release build below: the same step, the same time and the same count at each exit. The desktop's reference run takes 474.3 s. GPU results are pinned only on the desktop's driver, and another GPU's rounding gives a slightly different run.
- The rate requested was 1.00x, so 1.05x says nothing about this GPU's limit. The pre-release readings below do.
- S, M and L are disabled, with the reasons in the panel. Each needs 20 SSBO bindings and this GPU has 16. Each also needs a buffer above its 134 MB limit: up to 145 MB, 422 MB and 1.37 GB.
- "Up to" is an upper bound from the floor area, which the check uses when a venue's table is not in the folder. That zip held no tables. With a table in the folder the check reads its exact size, as the pre-release selector shows for S and M.

## Pre-release build

A Release build from the development history, commit 803e0bc, as the panel shows. These screenshots are in `pre_release/`, and the terrace ones are cropped to remove the Windows taskbar.

| file | shows | readings |
|---|---|---|
| `intel_uhd_venue_selector_limits.png` | the venue selector, with the capability check's reasons | this GPU has 16 SSBO bindings and allows a 134 MB buffer; S, M and L each need 20 bindings, M also a 416 MB buffer, L one of up to 1.37 GB |
| `intel_uhd_terrace_4096_16.6x.png` | terrace, 4 096 agents, at 127.3 s | 16.54x real time requested, 16.58x achieved, 231 FPS |
| `intel_uhd_terrace_4096_evacuated_475.6s.png` | terrace, 4 096 agents, at the end | stopped at 475.7 s (step 2720), first reading with 0 active at 475.6 s; exits +x 1031, -x 1035, +y 968, -y 1062 |
| `intel_uhd_terrace_16384_7.4x.png` | terrace, 16 384 agents, at 12.2 s | 16.54x requested, 7.42x achieved, 7 FPS |
| `intel_uhd_terrace_32768_1.6x.png` | terrace, 32 768 agents, at 51.8 s | 3.80x requested, 1.60x achieved, 6 FPS |

- At 4 096 agents the run kept up with the rate requested, so 16.58x is not this GPU's limit.
- The title bar and the panel do not update at the same moment, so the title can show a slightly different rate (1.53x at 32 768 agents).
- 16 384 agents is 4.00x the terrace's design capacity and 32 768 agents is 1.60x its jam capacity. They are stress points, and the panel labels them so.
