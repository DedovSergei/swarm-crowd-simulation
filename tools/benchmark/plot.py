"""plot.py <benchmark.csv> <cpu_scaling.csv> [--out out/results/figures]

Thesis figures from a benchmark_crowd run (PNG and SVG, no titles: the thesis adds captions):
  1 fig_ms_vs_n           median ms/step vs N (log-log), GPU / CPU-max / CPU-1, one panel per state,
                          min-max of the round medians as bars
  2 fig_speedup_vs_n      speedup GPU vs CPU-max (ratio of medians) vs N, per state
  3 fig_gpu_passes        GPU per-pass stacked bars (hash, sort, cells, physics) vs N, per state, as
                          shares of the step (100 % stacks), the absolute total above each bar
  4 fig_cpu_scaling       CPU speedup vs threads with the ideal line; P-core/E-core boundary at 12
  5 fig_trajectory        trajectory mode at N = 65536: ms/step vs step (top), active agents vs step (bottom)
The trajectory per-step data is read from <benchmark>_trajectory.csv next to the benchmark CSV.
"""
import argparse
import csv
import os
import statistics as st
from collections import defaultdict

import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt  # noqa: E402

# Categorical slots 1-4 of the validated reference palette (light mode), fixed order
BLUE, ORANGE, AQUA, YELLOW = "#2a78d6", "#eb6834", "#1baf7a", "#eda100"
INK, INK2, GRID = "#0b0b0b", "#52514e", "#e4e3df"
STRESS_N = 262144

plt.rcParams.update({
    "font.size": 9, "axes.labelsize": 9, "legend.fontsize": 8, "xtick.labelsize": 8, "ytick.labelsize": 8,
    "axes.edgecolor": INK2, "axes.labelcolor": INK, "xtick.color": INK2, "ytick.color": INK2,
    "axes.grid": True, "grid.color": GRID, "grid.linewidth": 0.6, "axes.axisbelow": True,
    "axes.spines.top": False, "axes.spines.right": False, "lines.linewidth": 2, "lines.markersize": 5,
    "savefig.dpi": 200, "savefig.bbox": "tight", "svg.fonttype": "none",
})


def read(path):
    with open(path, newline="") as f:
        return list(csv.DictReader(line for line in f if not line.startswith("#")))


def agg(rows):
    """median over rounds of the per-round median, and the min-max of the round medians"""
    v = [float(r["median_ms"]) for r in rows]
    return st.median(v), min(v), max(v)


def impl_key(r):
    return "gpu" if r["impl"] == "gpu" else f"cpu-{r['threads']}" if r["impl"] == "cpu" else r["impl"]


def save(fig, out, name):
    for ext in ("png", "svg"):
        fig.savefig(os.path.join(out, f"{name}.{ext}"))
    plt.close(fig)
    print("wrote", os.path.join(out, name) + ".{png,svg}")


def series(rows, cpu_max):
    return [("gpu", "GPU", BLUE, "o"), (f"cpu-{cpu_max}", f"CPU, {cpu_max} threads", ORANGE, "s"), ("cpu-1", "CPU, 1 thread", AQUA, "^")]


def mark_stress(ax, ns):
    if STRESS_N in ns:
        ax.axvspan(STRESS_N / 1.6, STRESS_N * 1.6, color=GRID, alpha=0.6, lw=0)
        ax.text(STRESS_N, 0.02, "over-capacity\nstress point", transform=ax.get_xaxis_transform(), ha="center", va="bottom",
                fontsize=7, color=INK2)


def fig_ms_vs_n(rows, cpu_max, out):
    states = ["spawn", "congested"]
    fig, axes = plt.subplots(1, 2, figsize=(7.2, 3.2), sharey=True)
    for ax, state in zip(axes, states):
        groups = defaultdict(list)
        for r in rows:
            if r["state"] == state:
                groups[(impl_key(r), int(r["N"]))].append(r)
        ns = sorted({n for _, n in groups})
        for key, name, color, marker in series(rows, cpu_max):
            xs, ys, lo, hi = [], [], [], []
            for n in ns:
                if (key, n) in groups:
                    m, a, b = agg(groups[(key, n)])
                    xs.append(n), ys.append(m), lo.append(m - a), hi.append(b - m)
            ax.errorbar(xs, ys, yerr=[lo, hi], color=color, marker=marker, capsize=3, elinewidth=1, label=name)
        ax.set_xscale("log", base=2)
        ax.set_yscale("log")
        ax.set_xlabel(f"agents N ({state} snapshot)")
        mark_stress(ax, ns)
    axes[0].set_ylabel("time per step [ms] (median over rounds)")
    axes[0].legend(frameon=False, loc="upper left")
    save(fig, out, "fig_ms_vs_n")


def fig_speedup(rows, cpu_max, out):
    fig, ax = plt.subplots(figsize=(4.6, 3.2))
    allns = set()
    top = 1.0
    labels = defaultdict(list)
    for state, color, marker in (("spawn", BLUE, "o"), ("congested", ORANGE, "s")):
        groups = defaultdict(list)
        for r in rows:
            if r["state"] == state:
                groups[(impl_key(r), int(r["N"]))].append(r)
        ns = sorted(n for k, n in groups if k == "gpu" and (f"cpu-{cpu_max}", n) in groups)
        allns |= set(ns)
        sp = [agg(groups[(f"cpu-{cpu_max}", n)])[0] / agg(groups[("gpu", n)])[0] for n in ns]
        top = max([top] + sp)
        ax.plot(ns, sp, color=color, marker=marker, label=f"{state} snapshot")
        for n, v in zip(ns, sp):
            labels[n].append(v)
    # Value labels at 65536 and the largest N: the higher of the two states above, the lower below
    for n, vs in labels.items():
        if n in (65536, max(allns)):
            for v in vs:
                dy = 8 if v == max(vs) else -12
                ax.annotate(f"{v:.1f}x", (n, v), textcoords="offset points", xytext=(7, dy), va="center", fontsize=7, color=INK2)
    ax.set_xscale("log", base=2)
    ax.set_yscale("log")
    ymax = max(60.0, 1.6 * top)   # room for the labels above the largest speedup
    ticks = [t for t in (1, 2, 5, 10, 20, 50, 100, 200, 500, 1000) if t <= ymax]
    ax.set_yticks(ticks, [str(t) for t in ticks])
    ax.yaxis.set_minor_formatter(matplotlib.ticker.NullFormatter())
    ax.set_ylim(1, ymax)
    ax.set_xlabel("agents N")
    ax.set_ylabel(f"speedup GPU vs CPU ({cpu_max} threads) [x]")
    mark_stress(ax, sorted(allns))
    ax.legend(frameon=False)
    save(fig, out, "fig_speedup_vs_n")


def fig_gpu_passes(rows, out):
    """Shares of the GPU step per pass (100 % stacks; a log axis cannot stack), total ms on top"""
    passes = [("hash_ms", "hash", YELLOW), ("sort_ms", "sort", BLUE), ("cells_ms", "cells", AQUA), ("physics_ms", "physics", ORANGE)]
    fig, axes = plt.subplots(1, 2, figsize=(7.2, 3.0), sharey=True)
    for ax, state in zip(axes, ("spawn", "congested")):
        groups = defaultdict(list)
        for r in rows:
            if r["impl"] == "gpu" and r["state"] == state:
                groups[int(r["N"])].append(r)
        ns = sorted(groups)
        x = list(range(len(ns)))
        vals = {col: [st.median(float(r[col]) for r in groups[n]) for n in ns] for col, _, _ in passes}
        tot = [sum(vals[c][i] for c, _, _ in passes) for i in range(len(ns))]
        bottom = [0.0] * len(ns)
        for col, name, color in passes:
            v = [100 * a / t for a, t in zip(vals[col], tot)]
            ax.bar(x, v, bottom=bottom, color=color, width=0.62, label=name, edgecolor="white", linewidth=1)
            bottom = [b + y for b, y in zip(bottom, v)]
        med_total = [st.median(float(r["median_ms"]) for r in groups[n]) for n in ns]   # as in the headline table
        for xi, t in zip(x, med_total):
            ax.text(xi, 101.5, f"{t:.3g} ms", ha="center", va="bottom", fontsize=7, color=INK2)
        ax.set_xticks(x, [f"{n}" + ("*" if n == STRESS_N else "") for n in ns])
        ax.set_ylim(0, 108)
        ax.set_yticks(range(0, 101, 20))
        ax.set_xlabel(f"agents N ({state} snapshot)")
        ax.grid(axis="x", visible=False)
    axes[0].set_ylabel("share of GPU execution time per step [%]")
    axes[1].legend(frameon=False, loc="lower left", reverse=True, bbox_to_anchor=(1.0, 0.0))
    fig.text(0.99, -0.09, "segments: median of each pass; above each bar: median GPU execution time per step; * over-capacity stress point",
             ha="right", fontsize=7, color=INK2)
    save(fig, out, "fig_gpu_passes")


def fig_scaling(rows, out):
    fig, ax = plt.subplots(figsize=(4.6, 3.4))
    tmax = 1
    ticks = []
    for state, color, marker in (("spawn", BLUE, "o"), ("congested", ORANGE, "s")):
        by_t = defaultdict(list)
        n = None
        for r in rows:
            if r["state"] == state and r["impl"] == "cpu":
                by_t[int(r["threads"])].append(float(r["median_ms"]))
                n = r["N"]
        if not by_t:
            continue
        ts = sorted(by_t)
        tmax = max(tmax, ts[-1])
        base = st.median(by_t[1])
        sp = [base / st.median(by_t[t]) for t in ts]
        lo = [base / max(by_t[t]) for t in ts]
        hi = [base / min(by_t[t]) for t in ts]
        ax.errorbar(ts, sp, yerr=[[s - a for s, a in zip(sp, lo)], [b - s for s, b in zip(sp, hi)]], color=color, marker=marker,
                    capsize=3, elinewidth=1, label=f"N = {n}, {state}")
        ax.annotate(f"{sp[-1]:.1f}x", (ts[-1], sp[-1]), textcoords="offset points", xytext=(6, 6 if state == "congested" else -7),
                    va="center", fontsize=7, color=INK2)
        ticks = ts
    ax.plot([1, tmax], [1, tmax], color=INK2, lw=1, ls="--", label="ideal (linear)")
    ax.axvline(12, color=INK2, lw=1, ls=":")
    ax.text(12.4, 0.04, "12 = 6 P-cores x 2 threads;\nthreads 13-20 run on E-cores", transform=ax.get_xaxis_transform(),
            va="bottom", fontsize=7, color=INK2)
    ax.set_xticks(ticks)
    ax.set_xlabel("OpenMP threads")
    ax.set_ylabel("speedup vs 1 thread [x]")
    ax.set_xlim(0, tmax + 1)
    ax.set_ylim(0, tmax + 1)
    ax.legend(frameon=False, loc="upper left")
    save(fig, out, "fig_cpu_scaling")


def fig_trajectory(traj_rows, cpu_max, out, n=65536):
    per = defaultdict(lambda: defaultdict(list))   # impl -> step -> [ms]
    active = defaultdict(lambda: defaultdict(list))
    for r in traj_rows:
        if int(r["N"]) != n:
            continue
        key = "gpu" if r["impl"] == "gpu" else f"cpu-{r['threads']}"
        per[key][int(r["step"])].append(float(r["total_ms"]))
        active[key][int(r["step"])].append(int(r["active"]))
    if not per:
        print(f"no trajectory data at N = {n}: fig_trajectory skipped")
        return
    fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(6.4, 4.8), sharex=True, gridspec_kw={"height_ratios": [3, 2]})
    for key, name, color, _ in series(None, cpu_max):
        if key not in per:
            continue
        steps = sorted(per[key])
        ax1.plot(steps, [st.median(per[key][s]) for s in steps], color=color, lw=1.2 if len(steps) > 50 else 2,
                 marker=None if len(steps) > 50 else "^", label=name)
    ax1.set_yscale("log")
    ax1.set_ylabel("time per step [ms]\n(median over rounds)")
    ax1.legend(frameon=False, loc="lower right", bbox_to_anchor=(1.0, 0.12))
    for key, name, color, ls in (("gpu", "GPU", BLUE, "-"), (f"cpu-{cpu_max}", "CPU", ORANGE, "--")):
        if key in active:
            steps = sorted(active[key])
            ax2.plot(steps, [st.median(active[key][s]) for s in steps], color=color, ls=ls, lw=1.5, label=f"{name} trajectory")
    ax2.set_ylabel("active agents")
    ax2.set_xlabel(f"simulation step (trajectory from spawn, N = {n})")
    ax2.legend(frameon=False)
    save(fig, out, "fig_trajectory")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("benchmark_csv")
    ap.add_argument("scaling_csv")
    ap.add_argument("--out", default="out/results/figures")
    a = ap.parse_args()
    os.makedirs(a.out, exist_ok=True)
    rows = read(a.benchmark_csv)
    snap = [r for r in rows if r["state"] in ("spawn", "congested") and r["impl"] in ("gpu", "cpu")]
    cpu_max = max(int(r["threads"]) for r in snap if r["impl"] == "cpu")
    fig_ms_vs_n(snap, cpu_max, a.out)
    fig_speedup(snap, cpu_max, a.out)
    fig_gpu_passes(snap, a.out)
    fig_scaling(read(a.scaling_csv), a.out)
    traj = a.benchmark_csv[:-4] + "_trajectory.csv"
    if os.path.exists(traj):
        fig_trajectory(read(traj), cpu_max, a.out)


if __name__ == "__main__":
    main()
