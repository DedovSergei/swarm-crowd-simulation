"""ab.py: rotated A/B of two (or more) builds of the pipeline, the perf protocol (README.md).

  python tools/perf_ab/ab.py --label base=<base build>/bench.exe --label base_aa=<base build>/bench.exe
                             --label new=<new build>/bench.exe --out out/results/perf/<name>
                             [--rounds 12] [--n 1024,4096,16384,65536,262144] [--states spawn,congested]
                             [--snapshots out/bench/snapshots] [--warm-ms 2000] [--quiet-wait 60] [--gpu-log]
                             [--title "..."]

The first label is the reference, the second its A/A control (the same executable again). Each
round visits every (N, state) cell; within a cell every label runs once, as its own 'bench cell'
process, in an order rotated by one position per round (Latin square: with rounds a multiple of the
label count, each label takes each position equally often). Per cell and label the verdict figure is
the median over rounds of the per-round median step time; per pass likewise.

Noise rule (fixed before any measurement): a label differs from the reference beyond noise
when |delta| > 2 x |A/A delta| of the same cell AND a two-sided sign test over the paired per-round
totals (label vs reference, same round, adjacent in time) gives p < 0.05 (>= 10 of 12 rounds).

Also checked: every label must produce the same state hash per cell (FNV-1a 64 of the state one step
after the snapshot), i.e. the builds compute identical results on every measured input.
--models-differ (an A/B across a deliberate model change): instead, every label must produce
one state hash per cell in every round (deterministic), and the reference and its A/A control the same
one; labels may differ from each other. Per-label environment (name=exe@KEY=VAL;...) can point a label
at its own snapshots (SWARM_BENCH_SNAPSHOTS) or set SWARM_BENCH_PROJ_ITERS (bench.cpp).

--quiet-wait S runs tools/benchmark/gpuwatch.ps1 first (no other process above 1% GPU for S s);
--gpu-log logs other processes' GPU use every 10 s during the run into <out>_gpu_other.csv.
Outputs: <out>.csv (one row per process run) and <out>.md (tables).
"""
import argparse
import csv
import math
import os
import re
import statistics as st
import subprocess
import sys
import tempfile
import time
from datetime import datetime

HERE = os.path.dirname(os.path.abspath(__file__))
GPUWATCH = os.path.join(HERE, "..", "benchmark", "gpuwatch.ps1")
PASSES = ["hash_ms", "sort_ms", "cells_ms", "physics_ms", "total_ms"]
KV = re.compile(r'(\w+)=("[^"]*"|\S+)')


def parse_kv(line):
    return {k: v.strip('"') for k, v in KV.findall(line)}


def sign_test_p(wins, losses):
    """Two-sided exact binomial sign test, ties dropped."""
    n = wins + losses
    if n == 0:
        return 1.0
    k = min(wins, losses)
    tail = sum(math.comb(n, i) for i in range(k + 1)) / 2.0 ** n
    return min(1.0, 2.0 * tail)


def run_cell(exe, env, label, n, state, args):
    cmd = [exe, "cell", "--n", str(n), "--state", state, "--label", label, "--snapshots", args.snapshots,
           "--warm-ms", str(args.warm_ms)] + (["--continuous"] if args.continuous else [])
    p = subprocess.run(cmd, capture_output=True, text=True, env=dict(os.environ, **env) if env else None)
    if p.returncode != 0:
        sys.exit("FAILED (%d): %s\n%s%s" % (p.returncode, " ".join(cmd), p.stdout, p.stderr))
    meta, cell = None, None
    for line in p.stdout.splitlines():
        if line.startswith("META "):
            meta = parse_kv(line)
        elif line.startswith("CELL "):
            cell = parse_kv(line)
    if not cell:
        sys.exit("no CELL line from %s:\n%s" % (" ".join(cmd), p.stdout))
    return meta, cell


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--label", action="append", required=True,
                    help="name=path/to/bench.exe[@KEY=VAL[;KEY=VAL]] (first: reference, second: A/A control; @: environment of its processes)")
    ap.add_argument("--out", required=True, help="output path without extension")
    ap.add_argument("--rounds", type=int, default=12)
    ap.add_argument("--n", default="1024,4096,16384,65536,262144")
    ap.add_argument("--states", default="spawn,congested")
    ap.add_argument("--snapshots", default="out/bench/snapshots")
    ap.add_argument("--warm-ms", type=int, default=2000)
    ap.add_argument("--quiet-wait", type=int, default=0, help="seconds of a quiet GPU required before starting (0: no check)")
    ap.add_argument("--gpu-log", action="store_true")
    ap.add_argument("--title", default="A/B")
    ap.add_argument("--continuous", action="store_true", help="bench cell --continuous: timed steps back to back from one restore")
    ap.add_argument("--models-differ", action="store_true",
                    help="labels run different models: check per-label determinism and A/A identity instead of identical hashes")
    ap.add_argument("--exclude", default="bench",
                    help="process name the --gpu-log logger leaves out (the measured executable, e.g. SWARM)")
    args = ap.parse_args()

    labels = []
    envs = {}
    for spec in args.label:
        name, _, rest = spec.partition("=")
        exe, _, envspec = rest.partition("@")
        if not exe or not os.path.isfile(exe):
            sys.exit("--label %s: no such executable" % spec)
        envs[name] = dict(kv.split("=", 1) for kv in envspec.split(";") if kv)
        labels.append((name, os.path.abspath(exe)))
    if len(labels) < 3:
        sys.exit("need a reference, its A/A control and at least one variant")
    ns = [int(x) for x in args.n.split(",")]
    states = args.states.split(",")
    os.makedirs(os.path.dirname(os.path.abspath(args.out)), exist_ok=True)

    if args.quiet_wait > 0:
        print("waiting for a quiet GPU (%d s below 1%% other use)..." % args.quiet_wait, flush=True)
        q = subprocess.run(["powershell", "-NoProfile", "-ExecutionPolicy", "Bypass", "-File", GPUWATCH, "-Mode", "wait",
                            "-QuietSeconds", str(args.quiet_wait), "-MaxMinutes", "60"], capture_output=True, text=True)
        print(q.stdout.strip(), flush=True)
        if q.returncode != 0:
            sys.exit("GPU not quiet; A/B not started")
        quiet_note = q.stdout.strip().splitlines()[-1] if q.stdout.strip() else "quiet"
    else:
        quiet_note = "no quiet check"

    logger, stop_file = None, None
    if args.gpu_log:
        stop_file = os.path.join(tempfile.gettempdir(), "ab_gpuwatch_stop_%d" % os.getpid())
        if os.path.exists(stop_file):
            os.remove(stop_file)
        logger = subprocess.Popen(["powershell", "-NoProfile", "-ExecutionPolicy", "Bypass", "-File", GPUWATCH, "-Mode", "log",
                                   "-Log", args.out + "_gpu_other.csv", "-Exclude", args.exclude, "-StopFile", stop_file])

    started = datetime.now().strftime("%Y-%m-%dT%H:%M:%S")
    t0 = time.time()
    metas = {}
    res = {}   # (n, state, label) -> list of per-round dicts
    with open(args.out + ".csv", "w", newline="") as f:
        w = csv.writer(f)
        w.writerow(["round", "position", "label", "N", "state", "steps"] + PASSES + ["state_fnv", "git_commit", "git_dirty"])
        try:
            for r in range(args.rounds):
                for n in ns:
                    for state in states:
                        for pos in range(len(labels)):
                            name, exe = labels[(pos + r) % len(labels)]
                            meta, cell = run_cell(exe, envs[name], name, n, state, args)
                            metas.setdefault(name, (meta, cell))
                            res.setdefault((n, state, name), []).append(cell)
                            w.writerow([r, pos, name, n, state, cell["steps"]] + [cell[p] for p in PASSES] +
                                       [cell["state_fnv"], cell["commit"], cell["dirty"]])
                            f.flush()
                print("  round %d/%d done [%.0f s]" % (r + 1, args.rounds, time.time() - t0), flush=True)
        finally:
            if logger:
                open(stop_file, "w").close()
                logger.wait(timeout=60)
                os.remove(stop_file)
    elapsed = time.time() - t0

    ref, aa = labels[0][0], labels[1][0]
    med = lambda v, p: st.median(float(c[p]) for c in v)
    lines = ["# %s" % args.title, ""]
    lines.append("Started %s, %.1f min, %d rounds, warm-up >= %.1f s per process, snapshots `%s`, timed steps %s. GPU before the run: %s." %
                 (started, elapsed / 60, args.rounds, args.warm_ms / 1000, args.snapshots,
                  "back to back from one restore (--continuous)" if args.continuous else "each from a restore of the snapshot", quiet_note))
    lines.append("")
    lines.append("| label | executable | environment | git commit | dirty | GPU | driver | process QoS |")
    lines.append("|---|---|---|---|---|---|---|---|")
    for name, exe in labels:
        meta, cell = metas[name]
        env = " ".join("%s=%s" % kv for kv in envs[name].items()) or "-"
        lines.append("| %s | `%s` | %s | %s | %s | %s | %s | %s |" % (name, os.path.relpath(exe), env, cell["commit"], cell["dirty"],
                                                              meta.get("gpu", "?"), meta.get("driver", "?"), meta.get("qos", "?")))
    lines.append("")
    lines.append("Protocol: tools/perf_ab/ab.py (rotated per cell, Latin square), `bench cell` snapshot mode (GPU-side restore before "
                 "every step, outside the timestamps), GPU-execution ms from CrowdSim's timestamp ring. Cell value: median over rounds "
                 "of the per-round median. Noise rule: |delta| > 2 x |A/A delta| and sign test p < 0.05 over the paired rounds.")
    lines.append("")
    # Total step: per label median (min-max), delta vs reference, verdict
    hdr = "| N | state |" + "".join(" %s ms (min-max) |%s" % (nm, "" if nm == ref else " vs %s |" % ref) for nm, _ in labels) + " verdict |"
    lines += ["## Total step", "", hdr, "|---:|---|" + "".join("---:|" + ("" if nm == ref else "---:|") for nm, _ in labels) + "---|"]
    verdicts = {}
    hashes_ok = True
    for n in ns:
        for state in states:
            vr = res[(n, state, ref)]
            mr = med(vr, "total_ms")
            aa_delta = med(res[(n, state, aa)], "total_ms") / mr - 1
            row = "| %d | %s |" % (n, state)
            verdict = []
            for nm, _ in labels:
                v = res[(n, state, nm)]
                tot = [float(c["total_ms"]) for c in v]
                m = st.median(tot)
                row += " %.4f (%.4f-%.4f) |" % (m, min(tot), max(tot))
                if nm != ref:
                    d = m / mr - 1
                    pairs = list(zip([float(c["total_ms"]) for c in v], [float(c["total_ms"]) for c in vr]))
                    wins = sum(a < b for a, b in pairs)
                    losses = sum(a > b for a, b in pairs)
                    p = sign_test_p(wins, losses)
                    row += " %+.1f%% (%d/%d, p %.3f) |" % (100 * d, wins, len(pairs), p)
                    if nm != aa:
                        beyond = abs(d) > 2 * abs(aa_delta) and p < 0.05
                        verdicts[(n, state, nm)] = ("faster" if d < 0 else "slower") if beyond else "within noise"
                        verdict.append("%s: %s" % (nm, verdicts[(n, state, nm)]))
                if args.models_differ:
                    if len({c["state_fnv"] for c in v}) != 1 or (nm == aa and {c["state_fnv"] for c in v} != {c["state_fnv"] for c in vr}):
                        hashes_ok = False
                elif len({c["state_fnv"] for c in v} | {c["state_fnv"] for c in vr}) != 1:
                    hashes_ok = False
            lines.append(row + " " + "; ".join(verdict) + " |")
    lines.append("")
    lines.append("Deltas: (rounds where the label was faster than %s / rounds, sign-test p). %s is the A/A control (%s again): its delta "
                 "is the noise floor." % (ref, aa, ref))
    lines.append("")
    # Per pass
    lines += ["## Per pass (median over rounds of the per-round medians, ms): hash / sort / cells / physics", "",
              "| N | state |" + "".join(" %s |" % nm for nm, _ in labels) + "".join(" %s vs %s |" % (nm, ref) for nm, _ in labels[2:]),
              "|---:|---|" + "---|" * len(labels) + "---|" * (len(labels) - 2)]
    for n in ns:
        for state in states:
            row = "| %d | %s |" % (n, state)
            for nm, _ in labels:
                v = res[(n, state, nm)]
                row += " %s |" % " / ".join("%.4f" % med(v, p) for p in PASSES[:4])
            vr = res[(n, state, ref)]
            for nm, _ in labels[2:]:
                v = res[(n, state, nm)]
                row += " %s |" % " / ".join("%+.1f%%" % (100 * (med(v, p) / med(vr, p) - 1)) if med(vr, p) > 0 else "-" for p in PASSES[:4])
            lines.append(row)
    lines.append("")
    if args.models_differ:
        lines.append("## Results per label (the labels run different models: --models-differ)")
        lines.append("")
        lines.append("State hash one step after each snapshot (FNV-1a 64): %s." %
                     ("one hash per label and cell in every round, the A/A control identical to the reference" if hashes_ok
                      else "**NOT deterministic or A/A different** in at least one cell"))
        for n in ns:
            for state in states:
                lines.append("- N = %d %s: %s" % (n, state, "; ".join("%s %s" % (nm, ", ".join(sorted({c["state_fnv"] for c in res[(n, state, nm)]})))
                                                                    for nm, _ in labels)))
        lines.append("")
        lines.append("Snapshots and projection iterations per label (META): %s." %
                     "; ".join("%s: `%s`, K %s" % (nm, metas[nm][0].get("snapshots", "?"), metas[nm][0].get("proj_iters", "?")) for nm, _ in labels))
    else:
        lines.append("## Results identical across builds")
        lines.append("")
        lines.append("State hash one step after each snapshot (FNV-1a 64), every label, every round: %s." %
                     ("identical in every cell" if hashes_ok else "**DIFFERENT** in at least one cell"))
        for n in ns:
            for state in states:
                hs = sorted({c["state_fnv"] for nm, _ in labels for c in res[(n, state, nm)]})
                lines.append("- N = %d %s: %s" % (n, state, ", ".join(hs)))
    if args.gpu_log and os.path.exists(args.out + "_gpu_other.csv"):
        vals = []
        with open(args.out + "_gpu_other.csv", encoding="utf-8-sig") as g:
            for row in csv.DictReader(g):
                try:
                    vals.append(float(row["other_total_pct"]))
                except (KeyError, ValueError):
                    pass
        if vals:
            lines.append("")
            lines.append("Other processes' GPU use during the run (every 10 s, `%s`): max %.2f%%, mean %.2f%% over %d samples." %
                         (os.path.basename(args.out) + "_gpu_other.csv", max(vals), st.mean(vals), len(vals)))
    with open(args.out + ".md", "w", encoding="utf-8") as f:
        f.write("\n".join(lines) + "\n")
    print("\n".join(lines))
    return 0 if hashes_ok else 1


if __name__ == "__main__":
    sys.exit(main())
