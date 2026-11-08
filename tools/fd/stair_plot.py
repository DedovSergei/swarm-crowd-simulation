"""stair_plot.py: the stair harness's diagrams (fd_harness stair, ring mode) against the calibration targets.

  python tools/fd/stair_plot.py <ring folder>[=label] [<ring folder>[=label] ...] [--out <png path>]

One panel per direction (ascending, descending): the specific flow J [persons/(m s)] against the density [persons/m^2] of every folder
given (a model variant each, e.g. the baseline and the calibrated sets: categorical slots in the given order), the level control of the
first folder in secondary ink, the targets as reference lines (EMPIRICAL per direction, CONSERVATIVE; values as reported in the cited
sources, not yet checked against the originals). Writes <first folder>/stair.png (or --out) and the same as .svg.
"""
import csv
import os
import sys

import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt  # noqa: E402
from matplotlib.lines import Line2D  # noqa: E402

SURFACE = "#ffffff"
INK, INK2, MUTED, HAIR, AXIS = "#0b0b0b", "#52514e", "#898781", "#e1e0d9", "#c3c2b7"
SLOT = ["#2a78d6", "#eb6834", "#1baf7a"]   # the figures' categorical colours 1-3
EMPIRICAL = {"up": 1.22, "down": 1.25}     # Burghardt, Seyfried & Klingsch (2013), persons/(m s) (as reported there; not yet checked against the original)
CONSERVATIVE = 66.0 / 60.0                 # Green Guide (6th ed., 2018), stepped surfaces (as reported there; not yet checked against the original)

plt.rcParams.update({
    "font.family": ["Segoe UI", "DejaVu Sans"], "font.size": 9, "axes.labelsize": 9, "xtick.labelsize": 8, "ytick.labelsize": 8,
    "legend.fontsize": 8, "axes.edgecolor": AXIS, "axes.linewidth": 0.8, "axes.labelcolor": INK2, "xtick.color": MUTED,
    "ytick.color": MUTED, "xtick.labelcolor": INK2, "ytick.labelcolor": INK2, "text.color": INK, "axes.facecolor": SURFACE,
    "figure.facecolor": SURFACE, "savefig.facecolor": SURFACE, "axes.grid": True, "grid.color": HAIR, "grid.linewidth": 0.6,
    "axes.axisbelow": True, "axes.spines.top": False, "axes.spines.right": False, "legend.frameon": False, "lines.linewidth": 2.0,
    "svg.fonttype": "none",
})


def load(folder):
    rows = list(csv.DictReader(open(os.path.join(folder, "stair.csv"))))
    out = {}
    for r in rows:
        out.setdefault(r["dir"], []).append((float(r["rho_p_m2"]), float(r["flow_p_m_s"])))
    return out


def main(argv):
    args, outPath = [], None
    i = 0
    while i < len(argv):
        if argv[i] == "--out":
            outPath = argv[i + 1]
            i += 2
            continue
        args.append(argv[i])
        i += 1
    if not args:
        print(__doc__)
        return 2
    runs = []
    for a in args:
        folder, _, label = a.partition("=")
        runs.append((folder, label or os.path.basename(os.path.normpath(folder)), load(folder)))
    fig, axes = plt.subplots(1, 2, figsize=(6.3, 2.9), sharey=True)
    for ax, d, name in zip(axes, ("up", "down"), ("ascending", "descending")):
        lv = runs[0][2].get("level")
        if lv:
            ax.plot(*zip(*lv), color=INK2, lw=1.2, label="level (rake 0)")
        for k, (folder, label, data) in enumerate(runs):
            if d in data:
                ax.plot(*zip(*data[d]), color=SLOT[k % 3], lw=2.0, marker="o", ms=3.5, mec=SURFACE, mew=0.8, label=label)
        ax.axhline(EMPIRICAL[d], color=INK2, lw=0.9, ls=(0, (4, 3)))
        ax.axhline(CONSERVATIVE, color=MUTED, lw=0.9, ls=(0, (1, 2)))
        ax.text(0.98, EMPIRICAL[d], f"EMPIRICAL {EMPIRICAL[d]:.2f}", transform=ax.get_yaxis_transform(), ha="right", va="bottom", fontsize=7.5, color=INK2)
        ax.text(0.98, CONSERVATIVE, f"CONSERVATIVE {CONSERVATIVE:.2f}", transform=ax.get_yaxis_transform(), ha="right", va="top", fontsize=7.5, color=MUTED)
        ax.set_xlabel("density [persons/m$^2$]")
        ax.text(0.0, 1.02, name, transform=ax.transAxes, ha="left", va="bottom", color=INK2, fontsize=9, fontweight="bold")
        ax.set_xlim(0, None)
        ax.set_ylim(0, None)
    axes[0].set_ylabel("specific flow [persons/(m s)]")
    handles = [Line2D([], [], color=SLOT[k % 3], lw=2.0, marker="o", ms=3.5, label=lab) for k, (_, lab, _) in enumerate(runs)]
    if runs[0][2].get("level"):
        handles.append(Line2D([], [], color=INK2, lw=1.2, label="level (rake 0)"))
    fig.legend(handles=handles, loc="lower center", ncol=len(handles), bbox_to_anchor=(0.5, -0.06))
    fig.tight_layout(rect=(0, 0.06, 1, 1))
    outPath = outPath or os.path.join(runs[0][0], "stair.png")
    for ext in (".png", ".svg"):
        fig.savefig(os.path.splitext(outPath)[0] + ext, dpi=200, bbox_inches="tight")
    print("->", outPath)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
