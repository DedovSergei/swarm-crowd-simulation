# A/B perf protocol

Compares the GPU cost of one simulation step between two versions of the pipeline (or two configurations of one
build). Release builds only; `perf.gpu_pass_timings` in `test_gpu` is a smoke timing, never a verdict.

## Protocol: `ab.py` + `bench cell`

- **Workloads:** the `benchmark_crowd` snapshots in `out/bench/snapshots` (`spawn_<N>.bin`, `congested_<N>.bin` = the
  GPU state after 250 steps), N in {1024, 4096, 16384, 65536, 262144}. `benchmark_crowd run --plan` generates the
  missing ones and runs the golden self-check.
- **One cell, one process:** `bench cell --n N --state S` restores the snapshot into both ping-pong halves with a
  GPU-side copy before every step (outside the timestamps), warms up for >= 2 s, then times 300 / 200 / 100 / 50 steps
  (N <= 16384 / 65536 / 131072 / larger) on CrowdSim's timestamp ring. It prints the per-pass medians, the
  build-time commit and dirty flag of the engine it links (`swarm_build_info`), and the FNV-1a 64 of
  the state one step after the snapshot.
- **Builds:** one Release build per version. `build.bat` compiles the CURRENT `bench.cpp` against each build, so both
  labels run the same harness. It needs MSVC x64: `cl` on PATH, otherwise the file named by `VCVARS64` (default: Visual
  Studio 2026 Community). Keep the paths short: MSVC fails beyond 250 characters per object path.
- **Rotation:** per round, every (N, state) cell runs each label once, in an order rotated by one position per round
  (Latin square). The first label is the reference, the second its A/A control: the reference build under a second
  label, whose delta is the noise floor.
- **Verdict:** per cell and label, the median over rounds of the per-round median (best-of is unreliable at 65536
  agents). A difference is beyond noise when |delta| > 2 x |A/A delta| and a two-sided sign test over the paired rounds
  gives p < 0.05 (>= 10 of 12).
- **Same results:** `ab.py` fails if the labels' state hashes differ in any cell.
- **Quiet GPU:** `--quiet-wait 60` waits for 60 s without other GPU use (`tools/benchmark/gpuwatch.ps1`), and
  `--gpu-log` logs other processes' GPU use every 10 s during the run (`<out>_gpu_other.csv`). No builds, tests or
  other benchmarks while it runs.

## Running it

From the repository root, in Git Bash:

```bash
git worktree add --detach out/perf/base/src <baseline-commit>   # a real checkout: the commit metadata works
cmd //c "tools\perf_ab\build.bat out\perf\base\src out\perf\base\build"
cmd //c "tools\perf_ab\build.bat . out\build\x64-Release"
out/build/x64-Release/benchmark_crowd.exe run --plan              # snapshots + golden self-check
python tools/perf_ab/ab.py --rounds 12 --quiet-wait 60 --gpu-log --out out/results/perf/<name> \
  --label base=out/perf/base/build/bench.exe --label base_aa=out/perf/base/build/bench.exe \
  --label new=out/build/x64-Release/bench.exe
git worktree remove out/perf/base/src
```

## Options

`bench cell --continuous` times the steps back to back from one restore (as the application steps), `--trace` prints
every timed step; `ab.py --continuous`, and a label may carry environment variables for its processes
(`name=path/bench.exe@KEY=VAL;KEY2=VAL2`). At N = 262144 short windows can land in memory-side slow episodes of about
1 s; prefer long traces there.

**Safety metrics.** `bench cell --metrics`, or `SWARM_BENCH_METRICS=1` in a label's environment, runs
`CrowdMetrics::afterStep` (the two metric passes) after every step. They are timed by two timestamps of their own around
them; `total_ms` then includes them and `metrics_ms` is their median. The overhead A/B uses one build under three labels:

```bash
python tools/perf_ab/ab.py --rounds 12 --n 4096,65536 --quiet-wait 60 --gpu-log --out out/results/perf/<name> \
  --label off=out/build/x64-Release/bench.exe --label off_aa=out/build/x64-Release/bench.exe \
  --label on=out/build/x64-Release/bench.exe@SWARM_BENCH_METRICS=1
```

**Viewer UI on / off.** `SWARM cell` has `bench cell`'s arguments and META / CELL output but runs the viewer's
frame loop (one step + the metric passes per frame, render, the panel when `SWARM_VIEWER_UI=1`; `SWARM_VIEWER_OVERLAY=1`
adds density colouring and the heatmap overlay) in a visible window with VSync off; the passes are timed on the same
CrowdSim ring. `--exclude SWARM` keeps the measured process out of the GPU log:

```bash
python tools/perf_ab/ab.py --rounds 12 --n 4096,65536 --continuous --quiet-wait 60 --gpu-log --exclude SWARM \
  --out out/results/perf/<name> --label off=out/build/x64-Release/SWARM.exe@SWARM_VIEWER_UI=0 \
  --label off_aa=out/build/x64-Release/SWARM.exe@SWARM_VIEWER_UI=0 --label on=out/build/x64-Release/SWARM.exe@SWARM_VIEWER_UI=1 \
  "--label=on_overlay=out/build/x64-Release/SWARM.exe@SWARM_VIEWER_UI=1;SWARM_VIEWER_OVERLAY=1"
```

**A seated venue against the terrace.** `bench snapshots <dir> <n> --venue S` writes venue S's inputs (spawn: every seat
occupied, 3728 agents in an N = 4096 buffer; congested: the routed state after 250 steps), and `SWARM_BENCH_VENUE=S` in a
label's environment runs `bench cell` on venue S (routed by its navigation field). Different venues are different models:
`--models-differ`, each label on its own snapshots. One build, the terrace as reference and its A/A control:

```bash
out/build/x64-Release/bench.exe snapshots out/bench/snap_terrace 4096
out/build/x64-Release/bench.exe snapshots out/bench/snap_S 4096 --venue S
python tools/perf_ab/ab.py --rounds 12 --n 4096 --models-differ --quiet-wait 60 --gpu-log --out out/results/perf/<name> \
  "--label=terrace=out/build/x64-Release/bench.exe@SWARM_BENCH_SNAPSHOTS=out/bench/snap_terrace" \
  "--label=terrace_aa=out/build/x64-Release/bench.exe@SWARM_BENCH_SNAPSHOTS=out/bench/snap_terrace" \
  "--label=S=out/build/x64-Release/bench.exe@SWARM_BENCH_VENUE=S;SWARM_BENCH_SNAPSHOTS=out/bench/snap_S"
```

`bench snapshot` and `bench time` remain for older engine versions (they re-upload the input before every step and need
only `CrowdSim::currentStateBuffer()`).
