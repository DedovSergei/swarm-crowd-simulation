#!/usr/bin/env bash
# The thesis experiment matrix: every experiment that feeds results/RESULTS.md or a figure, on one GPU driver (AMD 26.10.1.261008) with ONE
# simulation code version (this commit's run_experiment; run from the repository root, a Release build of the committed tree). Every per-step
# check on (plausibility with no exemption on the seated venues, INV-row, the step-up rules, wall tops; the terrace: its documented exemptions).
#   OUT: the default model's cases on the terrace, S and M (names, arguments, spawns and seeds as each run's summary records them).
#        L's 11 runs ran on the same driver with the same simulation code and are kept (results/evacuation/code_version_proof).
#        The committed runs: results/evacuation/matrix and results/evacuation/matrix_before_calibration; new runs go under out/ unless OUT and OUT_BEFORE say otherwise.
#   OUT_BEFORE: the model before the stair calibration on S, M and L: --stair-flow off (the level spacing on the gangway inclines;
#        {queue-aware, incline speed, off} = GOLDEN_S / M / L_LEVEL_SPACING bit for bit). The terrace is unaffected by the stair spacing: its run
#        in OUT serves both.
# WORKER=a|b|all: the runs of one worker (two at a time: a = L and M of OUT_BEFORE; b = the rest), ONLY=<regex>, SKIP_DONE=1 (a name that already
# has a folder <name>_<timestamp> in its output directory).
set +e   # a run that fails a check exits 3: keep going, the summaries record it
RUN=${RUN:-out/build/x64-Release/run_experiment.exe}
OUT=${OUT:-out/results/evacuation/matrix}
OUT_BEFORE=${OUT_BEFORE:-out/results/evacuation/matrix_before_calibration}
LOGS=${LOGS:-out/matrix_logs}
WORKER=${WORKER:-all}
NOTE="thesis matrix (AMD 26.10.1)"
mkdir -p "$OUT" "$OUT_BEFORE" "$LOGS"
run() {
  local out=$1 name=$2; shift 2
  if [ -n "$ONLY" ] && ! [[ $name =~ $ONLY ]]; then return; fi
  if [ -n "$SKIP_DONE" ] && ls -d "$out/${name}_"[0-9]* >/dev/null 2>&1; then echo "skip $out/$name (done)"; return; fi
  local log="$LOGS/$(basename "$out")_$name.log"
  echo "=== $out/$name $(date +%H:%M:%S)"
  "$RUN" --out "$out" --name "$name" --max-steps 40000 "$@" > "$log" 2>&1
  echo "    exit $? $(grep -E 't50 .*t100' "$log" | head -1) $(grep -E 'checks:' "$log" | head -1)"
}
# The default model's cases (queue-aware exit choice, incline speed, stair spacing EMPIRICAL), terrace, S, M
default_model_cases() {
  run "$OUT" terrace_n4096 --n 4096 --checks 1 --note "$NOTE: the terrace reference, N = 4096, every per-step check"
  for v in S M; do
    run "$OUT" ${v}_load100 --venue $v --load 1 --note "$NOTE: venue $v, 100% load, default model"
    for s in 1 2 3; do run "$OUT" ${v}_load95_s$s --venue $v --load 0.95 --seed $s --note "$NOTE: venue $v, 95% load (seed $s), default model"; done
    if [ $v = S ]; then
      for s in 1 2 3; do run "$OUT" S_load125_s$s --venue S --load 1.25 --seed $s --note "$NOTE: venue S, 125% load (seed $s): every seat + standing on the walkway and concourse"; done
    fi
    for s in 1 2 3; do run "$OUT" ${v}_load150_s$s --venue $v --load 1.5 --seed $s --note "$NOTE: venue $v, 150% requested (seed $s): every seat + standing on the walkway and concourse (M: the achievable maximum, also the 125% request)"; done
    if [ $v = S ]; then
      for s in 1 2 3; do run "$OUT" S_load150_gangways_s$s --venue S --load 1.5 --seed $s --standing gangways --note "$NOTE: venue S, 150% load (seed $s): standing also on the gangways"; done
    fi
    run "$OUT" ${v}_load100_nearest --venue $v --load 1 --exit-choice nearest --note "$NOTE: venue $v, 100% load, nearest exit (incline speed, stair spacing): the uninformed-crowd bound"
    run "$OUT" ${v}_load100_conservative --venue $v --load 1 --stair-flow conservative --note "$NOTE: venue $v, 100% load, the CONSERVATIVE stair spacing (the Green Guide's planning rate)"
    if [ $v = M ]; then
      run "$OUT" M_load100_dt2 --venue M --load 1 --dt-div 2 --note "$NOTE: venue M, 100% load, DT / 2 (DT convergence)"
    fi
    run "$OUT" ${v}_load100_level --venue $v --load 1 --incline-speed 0 --note "$NOTE (model variants): venue $v, 100% load, queue-aware exit choice, level walking speed"
    run "$OUT" ${v}_load100_nearest_level --venue $v --load 1 --exit-choice nearest --incline-speed 0 --note "$NOTE (model variants): venue $v, 100% load, nearest exit, level walking speed"
  done
}
# The cases before the stair calibration (--stair-flow off), venue v
before_calibration_cases() {
  local v=$1 note_before="$NOTE: the model before the stair calibration (the level spacing on the gangway inclines, --stair-flow off)"
  run "$OUT_BEFORE" ${v}_load100 --venue $v --load 1 --stair-flow off --note "$note_before: venue $v, 100% load"
  for s in 1 2 3; do run "$OUT_BEFORE" ${v}_load95_s$s --venue $v --load 0.95 --seed $s --stair-flow off --note "$note_before: venue $v, 95% load (seed $s)"; done
  if [ $v = S ]; then
    for s in 1 2 3; do run "$OUT_BEFORE" S_load125_s$s --venue S --load 1.25 --seed $s --stair-flow off --note "$note_before: venue S, 125% load (seed $s)"; done
  fi
  for s in 1 2 3; do run "$OUT_BEFORE" ${v}_load150_s$s --venue $v --load 1.5 --seed $s --stair-flow off --note "$note_before: venue $v, 150% requested (seed $s)"; done
  if [ $v = S ]; then
    for s in 1 2 3; do run "$OUT_BEFORE" S_load150_gangways_s$s --venue S --load 1.5 --seed $s --standing gangways --stair-flow off --note "$note_before: venue S, 150% load (seed $s), standing also on the gangways"; done
  fi
  run "$OUT_BEFORE" ${v}_load100_nearest --venue $v --load 1 --exit-choice nearest --stair-flow off --note "$note_before: venue $v, 100% load, nearest exit (incline speed)"
}
case $WORKER in
  a) before_calibration_cases L; before_calibration_cases M ;;
  b) default_model_cases; before_calibration_cases S ;;
  *) default_model_cases; before_calibration_cases S; before_calibration_cases M; before_calibration_cases L ;;
esac
echo "=== thesis matrix ($WORKER) done $(date +%H:%M:%S)"
