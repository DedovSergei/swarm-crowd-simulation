#!/usr/bin/env bash
# The harness runs behind results/RESULTS.md and the figures, on AMD 26.10.1 with this commit's fd_harness
# (run from the repository root, Release): the level fundamental diagram (seeds 7, 8, 9) and the stair harness's three diagrams
# (--stair-flow off, EMPIRICAL, CONSERVATIVE; ring mode, the default density grid, seeds 7, 8, 9). The narrow-passage runs
# (tools/fd/narrow_passage.sh) ran on the same driver with the same simulation code and are kept. The committed runs:
# results/validation/fundamental_diagram and results/validation/stair_flow/harness; new runs go under out/ unless FD_OUT and STAIR_OUT say otherwise.
B=${B:-out/build/x64-Release}
FD_OUT=${FD_OUT:-out/results/validation/fundamental_diagram}
STAIR_OUT=${STAIR_OUT:-out/results/validation/stair_flow/harness}
"$B/fd_harness.exe" run --name level_corridor --out "$FD_OUT"
for f in off empirical conservative; do
  n=$f; [ $f = off ] && n=baseline
  "$B/fd_harness.exe" stair --stair-flow $f --name stair_$n --out "$STAIR_OUT"
done
echo "harness runs done"
