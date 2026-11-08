#!/usr/bin/env bash
# The level specific flow against the corridor width, no model change (run from the repository root, Release).
#   (1) the FD protocol (fd_harness run: periodic 50 m corridor, full-height walls, wall-to-wall width W, seeds 7, 8, 9, 300 s
#       warm-up + 300 s measured, densities 0.1-6) at W = 1.2, 2.4, 3.0 m (3.0 m: the calibration corridor);
#   (2) the stair harness's level corridor (fd_harness stair --dirs level: rake 0, walls ending 0.85 m above the floor, below the
#       torso-height obstacle avoidance) with the same centre spans (W - 0.40 m: 0.8, 2.0, 2.6 m) and the gangway's 1.2 m.
# The committed results: results/validation/narrow_passages/; new runs go under out/ unless OUT says otherwise.
B=${B:-out/build/x64-Release}
OUT=${OUT:-out/results/validation/narrow_passages}
for w in 1.2 2.4 3; do
  "$B/fd_harness.exe" run --width-m $w --name fd_w${w} --out $OUT
done
for s in 0.8 2 2.6 1.2; do
  "$B/fd_harness.exe" stair --dirs level --width-m $s --name lowwall_span${s} --out $OUT
done
echo "narrow passage done"
