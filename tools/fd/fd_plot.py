"""Fundamental-diagram plot: tools/fd/fd_plot.py <run folder> [--compare <other run folder> --label-a A --label-b B]

Reads <run folder>/fd.csv (fd_harness run) and writes <run folder>/fd.png: speed vs density and flow vs density, the model
against Weidmann (1993), with Fruin's ~82 persons per metre per minute as a reference line on the flow panel. With
--compare, a second run is drawn as a second model series (e.g. before / after calibration).

Palette: the figures' palette: categorical colour 1 (blue)
for the model, colour 2 (orange) for the reference curve, a second model run in colour 3 (aqua); text in ink tones.
"""
import argparse
import csv
import math
import os

import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt  # noqa: E402

SURFACE, INK, INK2, MUTED, HAIR = "#fcfcfb", "#0b0b0b", "#52514e", "#898781", "#e1e0d9"
BLUE, ORANGE, AQUA = "#2a78d6", "#eb6834", "#1baf7a"
V0, GAMMA, RHO_MAX = 1.34, 1.913, 5.4
FRUIN = 82.0


def weidmann(rho):
    return 0.0 if rho >= RHO_MAX else V0 * (1.0 - math.exp(-GAMMA * (1.0 / rho - 1.0 / RHO_MAX)))


def read(folder):
    with open(os.path.join(folder, "fd.csv"), newline="") as f:
        rows = list(csv.DictReader(f))
    rho = [float(r["rho_p_m2"]) for r in rows]
    v = [float(r["speed_m_s"]) for r in rows]
    j = [float(r["flow_p_m_min"]) for r in rows]
    return rho, v, j


def style(ax, xlabel, ylabel):
    ax.set_facecolor(SURFACE)
    for side in ("top", "right"):
        ax.spines[side].set_visible(False)
    for side in ("left", "bottom"):
        ax.spines[side].set_color(HAIR)
    ax.tick_params(colors=INK2, labelsize=9)
    ax.grid(True, color=HAIR, linewidth=0.6)
    ax.set_axisbelow(True)
    ax.set_xlabel(xlabel, color=INK2, fontsize=10)
    ax.set_ylabel(ylabel, color=INK2, fontsize=10)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("folder")
    ap.add_argument("--compare", default=None)
    ap.add_argument("--label-a", default="model")
    ap.add_argument("--label-b", default="model (compare)")
    ap.add_argument("--title", default="Fundamental diagram: 3 m periodic corridor, goal +x")
    a = ap.parse_args()

    runs = [(read(a.folder), a.label_a, BLUE)]
    if a.compare:
        runs.append((read(a.compare), a.label_b, AQUA))
    rmax = max(max(r[0][0]) for r in runs)
    grid = [0.05 + i * (rmax - 0.05) / 400 for i in range(401)]
    wv = [weidmann(r) for r in grid]
    wj = [60.0 * r * v for r, v in zip(grid, wv)]

    fig, axes = plt.subplots(1, 2, figsize=(11, 4.4), dpi=150, facecolor=SURFACE)
    ax1, ax2 = axes
    style(ax1, "density [persons/m²]", "speed [m/s]")
    style(ax2, "density [persons/m²]", "specific flow [persons/(m·min)]")

    ax1.plot(grid, wv, color=ORANGE, linewidth=2, label="Weidmann 1993")
    ax2.plot(grid, wj, color=ORANGE, linewidth=2, label="Weidmann 1993")
    ax2.axhline(FRUIN, color=MUTED, linewidth=1, linestyle=(0, (4, 3)))
    ax2.text(0.05, FRUIN, "Fruin ~82", color=INK2, fontsize=8, ha="left", va="bottom")
    for (rho, v, j), label, color in runs:
        for ax, y in ((ax1, v), (ax2, j)):
            ax.plot(rho, y, color=color, linewidth=2, marker="o", markersize=5, markeredgecolor=SURFACE, markeredgewidth=1.5, label=label,
                    zorder=3)
    # direct labels at the right end of each series
    for ax, getter in ((ax1, lambda run: run[0][1]), (ax2, lambda run: run[0][2])):
        for run in runs:
            ax.annotate(run[1], (run[0][0][-1], getter(run)[-1]), xytext=(6, 0), textcoords="offset points", color=INK2, fontsize=8, va="center")
    ax1.annotate("Weidmann", (grid[len(grid) // 6], wv[len(grid) // 6]), xytext=(6, 6), textcoords="offset points", color=INK2, fontsize=8)
    ax1.set_ylim(0, max(1.45, max(max(r[0][1]) for r in runs) * 1.1))
    ax2.set_ylim(0, max(max(wj), FRUIN, max(max(r[0][2]) for r in runs)) * 1.15)
    for ax, loc in ((ax1, "upper right"), (ax2, "upper left")):   # flow panel: the upper left stays free of data
        ax.set_xlim(0, rmax * 1.08)
        leg = ax.legend(frameon=False, fontsize=8, loc=loc)
        for t in leg.get_texts():
            t.set_color(INK2)
    fig.suptitle(a.title, color=INK, fontsize=11, x=0.01, ha="left")
    fig.tight_layout()
    out = os.path.join(a.folder, "fd.png")
    fig.savefig(out, facecolor=SURFACE)
    print(out)


if __name__ == "__main__":
    main()
