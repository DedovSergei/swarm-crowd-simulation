#!/usr/bin/env bash
# The CPU baseline check for the current model (run from the repository root, a Release build of the committed tree;
# a quiet GPU and nothing else running: tools/benchmark/gpuwatch.ps1 -Mode wait first, on its own).
#   1. cpu_profile at venue M 100% congested (the thesis snapshot, benchmark_crowd thesis), 1 and 20 threads: the step's stages (hash, sort,
#      cells, exit choice, predict, projection, final) and the per-agent phase profile; the exit choice sequential and parallel.
#   2. cpu_tune sweep at 20 threads on S and M, spawn and congested: every (physics, projection) schedule pair of static / dynamic64 /
#      dynamic256 / guided, the exit choice sequential and parallel, the tuned configuration's A/A control; ROUNDS rounds, rotated.
#   3. tools/benchmark/sweep_table.py: the verdicts (A/A, sign test).
# The committed results: results/benchmarks/cpu_tuning/; new runs go under out/ unless OUT says otherwise.
set -e
B=${B:-out/build/x64-Release}
SNAP=${SNAP:-out/bench/snapshots_thesis}
OUT=${OUT:-out/results/benchmarks/cpu_tuning}
ROUNDS=${ROUNDS:-6}
STEP=${STEP:-all}
mkdir -p "$OUT"
if [ "$STEP" = all ] || [ "$STEP" = profile ]; then
  for c in 0 1; do
    name=$([ $c = 0 ] && echo seq || echo par)
    echo "=== profile M congested, exit choice $name $(date +%H:%M:%S)"
    "$B/cpu_profile.exe" "$SNAP" --venue M --state congested --threads 1,20 --steps 5 --schedule dynamic64 --proj-schedule dynamic64 \
      --parallel-choice $c > "$OUT/profile_M_congested_choice_$name.txt"
  done
fi
if [ "$STEP" = all ] || [ "$STEP" = sweep ]; then
  for v in S M; do
    echo "=== sweep $v $(date +%H:%M:%S)"
    "$B/cpu_tune.exe" sweep "$SNAP" "$OUT/sweep_$v.csv" --venue $v --threads 20 --states spawn,congested --rounds "$ROUNDS" \
      --schedules static,dynamic64,dynamic256,guided --proj-schedules static,dynamic64,dynamic256,guided --choice seq,par --aa > "$OUT/sweep_$v.log"
  done
  python tools/benchmark/sweep_table.py "$OUT/sweep.md" "$OUT/sweep_S.csv" "$OUT/sweep_M.csv"
fi
echo "=== CPU tuning sweep ($STEP) done $(date +%H:%M:%S)"
