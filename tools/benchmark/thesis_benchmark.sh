#!/usr/bin/env bash
# The thesis benchmark (run from the repository root, a Release build of the committed tree; a quiet GPU and nothing
# else running: tools/benchmark/gpuwatch.ps1 -Mode wait first, on its own).
#   1. benchmark_crowd thesis: (A) S, M, L at 100% load, (B) the terrace sweep N = 1024 .. 262144; ROUNDS rounds; the clock note of the
#      GPU's Adrenalin setting; other processes' GPU use logged every 10 s (gpuwatch -Mode log, *_gpu_other.csv).
#   2. benchmark_crowd scaling --venue M --states congested: CPU thread scaling, threads 1 .. 20, 3 rounds.
# The committed results: results/benchmarks/thesis/; new runs go under out/ unless OUT says otherwise.
set -e
B=${B:-out/build/x64-Release}
OUT=${OUT:-out/results/benchmarks/thesis}
ROUNDS=${ROUNDS:-5}
CLOCK=${CLOCK:-"adrenalin manual min2500 max2620"}
STEP=${STEP:-all}
mkdir -p "$OUT"
log_gpu() {   # gpuwatch -Mode log until the stop file appears
  local csv=$1 stop=$2
  rm -f "$stop"
  powershell -ExecutionPolicy Bypass -File tools/benchmark/gpuwatch.ps1 -Mode log -Log "$csv" -StopFile "$stop" -Exclude benchmark_crowd > /dev/null 2>&1 &
}
if [ "$STEP" = all ] || [ "$STEP" = thesis ]; then
  echo "=== thesis $(date +%H:%M:%S)"
  stamp=$(date +%Y%m%d_%H%M)
  log_gpu "$OUT/thesis_${stamp}_gpu_other.csv" out/bench_stop_thesis
  "$B/benchmark_crowd.exe" thesis --rounds "$ROUNDS" --clock-note "$CLOCK" --out "$OUT" \
    --note "the thesis benchmark (AMD 26.10.1.261008; the default model; the CPU's tuned configuration)" > "$OUT/thesis_${stamp}_log.txt" 2>&1
  touch out/bench_stop_thesis
fi
if [ "$STEP" = all ] || [ "$STEP" = scaling ]; then
  echo "=== scaling $(date +%H:%M:%S)"
  stamp=$(date +%Y%m%d_%H%M)
  "$B/benchmark_crowd.exe" scaling --venue M --states congested --threads 1,2,4,6,8,12,14,16,20 --rounds 3 --steps 20 --clock-note "$CLOCK" \
    --out "$OUT" > "$OUT/cpu_scaling_M_${stamp}_log.txt" 2>&1
fi
echo "=== thesis benchmark ($STEP) done $(date +%H:%M:%S)"
