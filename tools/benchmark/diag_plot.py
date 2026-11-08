"""diag_plot.py <stage2a_sort.csv> <stage2b_physics.csv> [--out out/results/figures]

Diagnosis figures from gpu_diag (PNG and SVG, no titles, plot.py's style):
  1 fig_diag_sort_dispatch   median GPU us per bitonic-sort dispatch vs N (log-log), one line per buffer
                             allocation (gpu_diag sort, synthetic keys); the 4 MB buffer size marked
  2 fig_diag_physics         physics GPU ns per neighbour candidate vs N, GL_DYNAMIC_DRAW vs GL_DYNAMIC_COPY
                             (gpu_diag physics, original agent order), one panel per state
"""
import argparse
import csv
import os
import statistics as st
from collections import defaultdict

import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt  # noqa: E402

from plot import AQUA, BLUE, GRID, INK2, ORANGE, YELLOW, save  # noqa: E402  (rcParams come with it)

ALLOC_STYLE = {
    "dynamic_draw": ("GL_DYNAMIC_DRAW", ORANGE, "o"),
    "dynamic_copy": ("GL_DYNAMIC_COPY", BLUE, "s"),
    "static_draw": ("GL_STATIC_DRAW", AQUA, "^"),
    "stream_draw": ("GL_STREAM_DRAW", YELLOW, "v"),
    "storage": ("glBufferStorage (flags 0)", INK2, "d"),
}


def read(path):
    with open(path, newline="") as f:
        return list(csv.DictReader(f))


def mark_4mb(ax, bytes_per_elem, text):
    n4 = 4 * 1048576 / bytes_per_elem
    ax.axvline(n4, color=GRID, lw=1.5, zorder=0)
    ax.text(n4 / 1.12, 0.98, text, transform=ax.get_xaxis_transform(), ha="right", va="top", fontsize=7, color=INK2, rotation=90)


def fig_sort(rows, out):
    groups = defaultdict(list)
    for r in rows:
        groups[(r["alloc"], int(r["N"]))].append(float(r["median_us"]))
    fig, ax = plt.subplots(figsize=(4.6, 3.2))
    for alloc, (label, color, marker) in ALLOC_STYLE.items():
        ns = sorted(n for a, n in groups if a == alloc)
        if ns:
            ax.plot(ns, [st.median(groups[(alloc, n)]) for n in ns], marker=marker, color=color, label=label)
    ax.set_xscale("log", base=2)
    ax.set_yscale("log")
    ax.set_xlabel("N (sort elements, 16 bytes each)")
    ax.set_ylabel("GPU us per sort dispatch (median)")
    mark_4mb(ax, 16, "4 MB buffer")
    ax.legend(frameon=False, loc="upper left")
    save(fig, out, "fig_diag_sort_dispatch")


def fig_physics(rows, out):
    fig, axes = plt.subplots(1, 2, figsize=(7.2, 3.2), sharey=True)
    for ax, state in zip(axes, ["spawn", "congested"]):
        for alloc in ("dynamic_draw", "dynamic_copy"):
            label, color, marker = ALLOC_STYLE[alloc]
            sel = sorted((int(r["N"]), float(r["ns_per_candidate"])) for r in rows
                         if r["usage"] == alloc and r["layout"] == "original" and r["state"] == state)
            ax.plot([n for n, _ in sel], [v for _, v in sel], marker=marker, color=color, label=label)
        ax.set_xscale("log", base=2)
        ax.set_yscale("log")
        ax.set_xlabel(f"N agents ({state})")
        mark_4mb(ax, 32, "agent buffer 4 MB")
    axes[0].set_ylabel("physics GPU ns per neighbour candidate")
    handles, labels = axes[0].get_legend_handles_labels()
    fig.legend(handles, labels, frameon=False, loc="lower center", ncol=2, bbox_to_anchor=(0.5, 0.98))
    save(fig, out, "fig_diag_physics")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("sort_csv")
    ap.add_argument("physics_csv")
    ap.add_argument("--out", default="out/results/figures")
    a = ap.parse_args()
    os.makedirs(a.out, exist_ok=True)
    fig_sort(read(a.sort_csv), a.out)
    fig_physics(read(a.physics_csv), a.out)


if __name__ == "__main__":
    main()
