#!/usr/bin/env bash
# The gridlock robustness check of the DEFAULT model (queue-aware exit choice, incline speed, stair spacing EMPIRICAL) on
# AMD 26.10.1.261008. Run from the repository root with a Release build of the committed tree. Every per-step check on; stall snapshots
# (--stall-dump-s 30: the active agents' place, gangway, velocity, e_goal and assigned exit after 30, 60, 120, ... s without an evacuation);
# a step limit of 40 000 steps = 6 996 s: a run that has not finished by then is a gridlock.
#   S at 150% (every seat + standing on the walkway and concourse), seeds 1-10 (1-3: the matrix's spawns, reproduced);
#   M at its achievable maximum 121.42% (the 150% request), seeds 1-10 (1-3: the matrix's spawns);
#   M at seeded partial loads 90-94%, seeds 4-8 (one load per seed; the matrix's 95% seeds 1-3 are counted beside them);
#   L at its achievable maximum 109.28% (the 150% request), seeds 4-6, then 7-9 if the time box allows (the matrix: seeds 1-3).
# Analysis: tools/figures/gridlock.py. WORKER=a (L) | b (S, M) | all; ONLY=<regex>; SKIP_DONE=1.
set +e   # a run that fails a check exits 3: keep going, the summaries record it
RUN=${RUN:-out/build/x64-Release/run_experiment.exe}
OUT=${OUT:-out/results/evacuation/gridlock_robustness}   # the committed runs: results/evacuation/gridlock_robustness
LOGS=${LOGS:-out/gridlock_logs}
WORKER=${WORKER:-all}
L_SEEDS=${L_SEEDS:-"4 5 6"}
NOTE="gridlock robustness, default model, AMD 26.10.1"
mkdir -p "$OUT" "$LOGS"
run() {
  local name=$1; shift
  if [ -n "$ONLY" ] && ! [[ $name =~ $ONLY ]]; then return; fi
  if [ -n "$SKIP_DONE" ] && ls -d "$OUT/${name}_"[0-9]* >/dev/null 2>&1; then echo "skip $name (done)"; return; fi
  local log="$LOGS/$name.log"
  echo "=== $name $(date +%H:%M:%S)"
  "$RUN" --out "$OUT" --name "$name" --max-steps 40000 --stall-dump-s 30 "$@" > "$log" 2>&1
  echo "    exit $? $(grep -E 't50 .*t100' "$log" | head -1) $(grep -E 'checks:' "$log" | head -1) $(grep -c '  stall:' "$log") stall snapshots"
}
worker_b() {
  for s in 1 2 3 4 5 6 7 8 9 10; do run S_load150_s$s --venue S --load 1.5 --seed $s --note "$NOTE: venue S, 150% load (seed $s)"; done
  for s in 1 2 3 4 5 6 7 8 9 10; do run M_load150_s$s --venue M --load 1.5 --seed $s --note "$NOTE: venue M, the achievable maximum 121.42% (150% requested, seed $s)"; done
  local s=4
  for l in 90 91 92 93 94; do
    run M_load${l}_s$s --venue M --load 0.$l --seed $s --note "$NOTE: venue M, $l% load (seed $s)"
    s=$((s + 1))
  done
}
worker_a() {
  for s in $L_SEEDS; do run L_load150_s$s --venue L --load 1.5 --seed $s --note "$NOTE: venue L, the achievable maximum 109.28% (150% requested, seed $s)"; done
}
case $WORKER in
  a) worker_a ;;
  b) worker_b ;;
  *) worker_b; worker_a ;;
esac
echo "=== gridlock runs ($WORKER) done $(date +%H:%M:%S)"
