r"""thesis_figures.py: the thesis figures, Czech and English, PDF (vector, for LaTeX) + PNG (300 dpi) + SVG, into results/figures/<language>/ with
results/figures/README.md. --verify on renders the same figures with "(ověřit)" / "(verify)" markers on every value cited from a reference still to
be checked, into <out>/<language>_draft/ (VERIFY, set per variant by main(); default off).

  python tools/figures/thesis_figures.py [--out results/figures] [--only 1,2,...] [--lang cs,en] [--verify both|on|off]

Test renders (font, axes, layout checks) go to out/, never into results/figures/.

Run from the repository root after the matrix (tools/experiment/thesis_matrix.sh), matrix_table.py and bottleneck.py (which writes the matrix's
bottleneck.json). No titles are baked in (the thesis captions them); every axis carries its unit.

Language: Czech (cs) labels, legends and annotations with the Czech number format: a decimal comma and a thin space (U+2009) as the thousands
separator, the minus sign U+2212, a no-break space before % and units; English (en): a decimal point, the same thin space. The Czech set has
no English words (the stair-spacing sets "empirický" / "konzervativní", Fruin's levels "stupeň E / F") and no internal names. Typeface: Linux
Biolinum G (Libertinus Sans, the requested face, is its fork and is not installed here; the same design), fallback DejaVu Sans; subscripts by
mathtext in the same face (t_100 as $t_{\mathrm{100}}$: t italic, the index upright); 9 pt text, 8 pt ticks and legends; figures
15 cm wide (the thesis text width); PDF with embedded TrueType fonts (pdf.fonttype 42), SVG with text as text. A mean over seeds is always a
hollow circle with a capped min-max bar (range_marker).

Style: one palette (light, on a white page): venues S / M / L in categorical slots 1-3 (blue, orange, aqua; all pairs validated:
CVD Delta E 9.2, normal vision 24.0; aqua is below 3:1 contrast on white, so every venue series is also direct-labelled or
in a legend), the terrace reference in secondary ink; within a venue the stair-spacing variants by marker fill and line style (the venue's
colour follows the entity); two-way comparisons without venues (queue-aware / nearest, doors / avenues, straight / corner gangways) in slots
1-2; magnitudes on the one-hue blue ramp; model variants without venues (the stair harness) in ink greys and line styles; hairline grids.

Figures, by the number --only takes (README.md beside them says which runs each comes from):
   1 evacuation_curves_by_venue                 % evacuated vs time: S / M / L at 100% (stair spacing EMPIRICAL; CONSERVATIVE dashed) and the terrace
   2 evacuation_time_vs_capacity                t100 vs seats: EMPIRICAL with the CONSERVATIVE upper marker (the stair-flow bracket), the 95% runs'
                                                range, t100 before the stair calibration, the capacity lower bounds, the 8-minute reference
   3 safety_load_vs_time_and_exposure           t100 and circulation crush exposure vs the ACTUAL load (95%, 100%, overcrowded: S 125% / 150%, M 121.4%
                                                and L 109.3% the maximum achievable), min-max over seeds; S 150% with standing on the gangways
   4 evacuation_nearest_vs_queue_aware          t100 and unused exit width per venue: queue-aware (default) vs nearest exit, 100%
   5 evacuation_exit_utilisation                share of the evacuated through doors / avenues per venue, against the exit width's split
   6 evacuation_gangway_saturation              each gangway's saturated share of its active time, sorted, S, M and L at 100%
   7 safety_peak_density_maps                   circulation-zone peak density, top-down: S, M, L at 100% and L at the maximum achievable 109.3% (shared scale)
   8 validation_fundamental_diagram             the model's level corridor fundamental diagram against Weidmann (1993)
   9 evacuation_walking_model_variants          S, M, L at 100%: t100 for {nearest, queue-aware} x {level walking, stairs (incline speed + stair spacing)}
  10 validation_stair_flow_diagram              the stair harness: specific flow vs density on a gangway incline, up / down, the level spacing vs the
                                                EMPIRICAL and CONSERVATIVE stair spacing, against the targets
  11 evacuation_before_after_stair_calibration  t100 of every case: before the stair calibration (level spacing on the gangways) vs after (EMPIRICAL)
  12 validation_corridor_width_flow             the level specific flow vs density in corridors of 1.2, 2.4 and 3.0 m (the FD protocol with
                                                full-height walls, and the stair harness's level corridor with low walls at the same centre spans)
The performance figures (benchmark_crowd thesis and scaling --venue M: results/benchmarks/thesis; implementations in ink greys and line styles,
venues in their colours, the terrace's stress sweep hollow and thin):
  13 benchmark_step_time_vs_agents              ms per step vs active agents (log-log), GPU / CPU at max threads / CPU-1: S, M, L at 100% (constant density)
                                                and the terrace's stress sweep (fixed venue, N = 1 024 .. 262 144) as a separate series; spawn and congested
  14 benchmark_speedup                          GPU vs CPU at max threads and CPU at max threads vs 1 thread, per venue and terrace N (spawn / congested)
  15 benchmark_gpu_pass_shares                  the GPU passes' shares of the step per venue and state (stacked), the step's total ms above each bar
  16 benchmark_realtime_factor                  the real-time factor (simulated per wall second = DT_real / ms per step) per venue and implementation, the 1x line
  17 benchmark_cpu_thread_scaling               CPU ms per step and speedup vs OpenMP threads at M 100% congested, the ideal line, the P-/E-core boundary at 12
  18 benchmark_optimisation_chain               (a) the GPU step at the terrace (congested) through the buffer and sort optimisations (historical model and
                                                driver), the hard-body model (historical driver) and the current model; (b) the current model's per-pass
                                                GPU cost (congested), the terrace sweep and S, M, L
"""
import csv
import glob
import json
import math
import os
import sys

import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt  # noqa: E402
import matplotlib.ticker  # noqa: E402
import numpy as np  # noqa: E402
from matplotlib.colors import LinearSegmentedColormap  # noqa: E402
from matplotlib.lines import Line2D  # noqa: E402
from matplotlib.patches import Patch, Rectangle  # noqa: E402
from matplotlib.transforms import offset_copy  # noqa: E402

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import thesis_data as td  # noqa: E402

# --- style (light mode, on a white page) ---
SURFACE = "#ffffff"
INK, INK2, MUTED, HAIR, AXIS = "#0b0b0b", "#52514e", "#898781", "#e1e0d9", "#c3c2b7"
SLOT = ["#2a78d6", "#eb6834", "#1baf7a"]           # categorical slots 1-3 (fixed order)
VENUE_COLOR = {"S": SLOT[0], "M": SLOT[1], "L": SLOT[2], "terrace": INK2}
BLUE_RAMP = ["#cde2fb", "#b7d3f6", "#9ec5f4", "#86b6ef", "#6da7ec", "#5598e7", "#3987e5", "#2a78d6", "#256abf", "#1c5cab",
             "#184f95", "#104281", "#0d366b"]
SEAT_ROWS, NOT_RATED = "#b4b2a9", "#eeede8"
LOS_E, LOS_F, CRUSH = 1.08, 2.17, 5.0
PEAK_MIN_WALKABLE_M2 = 0.5          # swarm/metrics.hpp: peak densities over cells of at least this much floor
FD_DIR = (sorted(glob.glob("results/validation/fundamental_diagram/level_corridor_*")) or ["(no level corridor run)"])[-1]   # AMD 26.10.1
STAIR_RUNS = {"base": "results/validation/stair_flow/harness/stair_baseline_*", "emp": "results/validation/stair_flow/harness/stair_empirical_*",   # AMD 26.10.1
              "cons": "results/validation/stair_flow/harness/stair_conservative_*"}
EMPIRICAL = {"up": 1.22, "down": 1.25}       # as reported in Burghardt, Seyfried & Klingsch (2013); not yet checked against the original
CONSERVATIVE = 66.0 / 60.0                   # as reported in the Green Guide, 6th ed. 2018; not yet checked against the original
OUTER_HALF_M = {"S": 30.31, "M": 51.13, "L": 92.73}   # results/validation/venues/<V>/layout.md: the outer wall's half-width
W = 15.0 / 2.54                     # inches: the thesis text width (15 cm)
THIN = " "                     # thin space: the thousands separator
NBSP = " "

FONT = "Linux Biolinum G" if any(f.name == "Linux Biolinum G" for f in matplotlib.font_manager.fontManager.ttflist) else "DejaVu Sans"
plt.rcParams.update({
    "font.family": [FONT, "DejaVu Sans"], "font.size": 9, "axes.labelsize": 9, "xtick.labelsize": 8, "ytick.labelsize": 8,
    "legend.fontsize": 8, "axes.edgecolor": AXIS, "axes.linewidth": 0.8, "axes.labelcolor": INK2, "xtick.color": MUTED,
    "ytick.color": MUTED, "xtick.labelcolor": INK2, "ytick.labelcolor": INK2, "text.color": INK, "axes.facecolor": SURFACE,
    "figure.facecolor": SURFACE, "savefig.facecolor": SURFACE, "axes.grid": True, "grid.color": HAIR, "grid.linewidth": 0.6,
    "grid.linestyle": "-", "axes.axisbelow": True, "axes.spines.top": False, "axes.spines.right": False, "legend.frameon": False,
    "lines.linewidth": 1.8, "svg.fonttype": "none", "pdf.fonttype": 42, "axes.titlesize": 9, "axes.titlecolor": INK2,
    "axes.unicode_minus": True, "legend.handlelength": 1.8,
    "mathtext.fontset": "custom", "mathtext.rm": FONT, "mathtext.it": FONT + ":italic", "mathtext.bf": FONT + ":bold",
    "mathtext.default": "it",
})

LANG = "cs"
VERIFY = False       # the "(ověřit)" / "(verify)" markers: main() sets it per variant (--verify)
T100, T50, T90 = r"$t_{\mathrm{100}}$", r"$t_{\mathrm{50}}$", r"$t_{\mathrm{90}}$"   # the index upright, t italic
NARROW_DIR = "results/validation/narrow_passages"   # tools/fd/narrow_passage.sh


def vf():
    """The verify marker of a value cited from a reference, when VERIFY is on."""
    return L(" (ověřit)", " (verify)") if VERIFY else ""


def L(cs, en):
    """The text in the current language."""
    return cs if LANG == "cs" else en


def nf(x, nd=0):
    """A number in the current language's format: thin-space thousands, decimal comma (cs) or point (en), the minus sign U+2212."""
    if x is None or (isinstance(x, float) and math.isnan(x)):
        return "–"
    s = f"{abs(x):,.{nd}f}".replace(",", THIN)
    if LANG == "cs":
        s = s.replace(".", ",")
    return ("−" if x < 0 and float(f"{abs(x):.{nd}f}") != 0 else "") + s


def pc(x, nd=0):
    """A percentage: '95 %' (cs: a no-break space) / '95%' (en)."""
    return nf(x, nd) + (NBSP + "%" if LANG == "cs" else "%")


def sec(x, nd=0):
    return nf(x, nd) + NBSP + "s"


class LangFormatter(matplotlib.ticker.Formatter):
    """Tick labels in the current language's number format with as many decimals as the ticks need (at least nd, at most 3): a tick
    label never rounds its location (0.2-step ticks printed with 0 decimals would read 0, 0, 0, 1, 1)."""

    def __init__(self, nd=0):
        self.nd = nd
        self.digits = nd

    def set_locs(self, locs):
        super().set_locs(locs)
        self.digits = self.nd
        while self.digits < 3 and any(abs(round(v, self.digits) - v) > 1e-9 * max(1.0, abs(v)) for v in locs):
            self.digits += 1

    def __call__(self, v, pos=None):
        return nf(v, self.digits)


def axfmt(ax, axis="y", nd=0):
    """Tick labels in the current language's number format (LangFormatter: never rounded)."""
    (ax.yaxis if axis == "y" else ax.xaxis).set_major_formatter(LangFormatter(nd))


def venue_name(v):
    return L("stadion " + v, "venue " + v) if v != "terrace" else L("referenční tribuna k stání", "terrace (reference)")


TICK_PROBLEMS = []


def audit_ticks(fig, name):
    """Every numeric major tick label inside the axis' view must equal its location (no rounded tick labels)."""
    fig.canvas.draw()
    for ax in fig.axes:
        for axis, lim in ((ax.xaxis, ax.get_xlim()), (ax.yaxis, ax.get_ylim())):
            if not isinstance(axis.get_major_formatter(), (LangFormatter, matplotlib.ticker.ScalarFormatter)):
                continue   # category labels (venues, cases) set as text, colour-bar names: not numbers
            lo, hi = min(lim), max(lim)
            for t in axis.get_major_ticks():
                v, txt = t.get_loc(), t.label1.get_text()
                if not txt or not (lo - 1e-9 * abs(hi - lo) <= v <= hi + 1e-9 * abs(hi - lo)):
                    continue
                core = txt.replace(THIN, "").replace(NBSP, "").replace("−", "-").replace(",", ".").strip()
                core = core.split(" ")[0].rstrip("%")
                try:
                    shown = float(core)
                except ValueError:
                    continue   # a category or a named tick (venue, stupeň E ...)
                if abs(shown - v) > 1e-6 * max(1.0, abs(v)):
                    TICK_PROBLEMS.append(f"{name} ({LANG}{', draft' if VERIFY else ''}): tick at {v:g} labelled '{txt}'")


def save(fig, out, name):
    audit_ticks(fig, name)
    os.makedirs(out, exist_ok=True)
    for ext in ("pdf", "png", "svg"):
        fig.savefig(os.path.join(out, f"{name}.{ext}"), dpi=300, bbox_inches="tight", pad_inches=0.03)
    plt.close(fig)
    print("  ->", os.path.join(out, name + ".{pdf,png,svg}"))


def seats(r):
    return r["spawn"]["seated"] if r.get("spawn") else r["agents"]


def bottleneck():
    p = os.path.join(td.MATRIX_DIR, "bottleneck.json")
    if not os.path.exists(p):
        return None
    with open(p) as f:
        return json.load(f)


def range_marker(ax, x, values, col, transform=None, marker="o", zorder=5):
    """The mean over seeds with its min-max range: a hollow marker and a capped bar (the one style for every multi-seed mean)."""
    mean = sum(values) / len(values)
    lo, hi = min(values), max(values)
    kw = {"transform": transform} if transform is not None else {}
    ax.errorbar([x], [mean], yerr=[[mean - lo], [hi - mean]], fmt=marker, ms=4.0, mfc=SURFACE, mec=col, mew=1.1, color=col, elinewidth=1.1,
                capsize=2.4, capthick=1.1, zorder=zorder, **kw)
    return mean


def range_handle(label, marker="o"):
    return Line2D([], [], ls="-", marker=marker, ms=4.0, mfc=SURFACE, mec=INK2, mew=1.1, color=INK2, lw=1.1, label=label)


def first(key, base=None):
    rs = td.case_runs(key, base)
    return rs[0] if rs else None


def panel_label(ax, text):
    """A small in-panel label (the panel's subject), not a title: top left, secondary ink."""
    ax.text(0.0, 1.02, text, transform=ax.transAxes, ha="left", va="bottom", color=INK2, fontsize=9, fontweight="bold")


def curve(d):
    rows = td.load_csv(d, "timeseries.csv")
    n0 = td.run_metrics(d)["agents"]
    t = [0.0] + [float(x["t_real_s"]) for x in rows]
    e = [0.0] + [100.0 * (n0 - int(x["active"])) / n0 for x in rows]
    return t, e


# --- 1 ---
def fig1(out):
    fig, ax = plt.subplots(figsize=(W, 3.3))
    handles = []
    labels = []   # (key, t, e) of the direct-labelled curves
    curves = []   # every drawn curve (t, e), for the labels' placement
    for key in ["terrace"] + list(td.VENUES):
        r = first("terrace" if key == "terrace" else key + "_100")
        if not r:
            continue
        col = VENUE_COLOR[key]
        t, e = curve(r["dir"])
        ax.plot(t, e, color=col, lw=1.8, solid_capstyle="round", zorder=3)
        ax.plot([r["t100"]], [100.0], "o", ms=4.5, color=col, mec=SURFACE, mew=1.2, zorder=5)
        curves.append((t, e))
        if key != "terrace":   # the venues direct-labelled (aqua is below 3:1 on white); the terrace (secondary ink) in the legend
            labels.append((key, t, e))
        txt = (L(f"{venue_name(key)} (100{NBSP}%): {T100} {sec(r['t100'], 1)}", f"{venue_name(key)} (100%): {T100} {sec(r['t100'], 1)}")
               if key != "terrace" else L(f"referenční tribuna k stání (N{NBSP}={NBSP}4{THIN}096): {T100} {sec(r['t100'], 1)}",
                                          f"terrace reference (N = 4{THIN}096): {T100} {sec(r['t100'], 1)}"))
        rc = first(key + "_cons") if key != "terrace" else None
        if rc:
            tc, ec = curve(rc["dir"])
            curves.append((tc, ec))
            ax.plot(tc, ec, color=col, lw=1.0, ls=(0, (4, 2.5)), zorder=2)
            ax.plot([rc["t100"]], [100.0], "o", ms=4.0, mfc=SURFACE, mec=col, mew=1.1, zorder=4)
            txt += L(f"; konzervativní {sec(rc['t100'], 1)}", f"; conservative {sec(rc['t100'], 1)}")
        handles.append(Line2D([], [], color=col, lw=1.8, label=txt))
    # direct labels: each venue's name just above its t100 end dot (the venues' end dots lie far apart; the terrace in the legend)
    for key, t, e in labels:
        ax.annotate(key, (t[-1], 100.0), xytext=(0, 4), textcoords="offset points", color=INK2, fontsize=8.5, ha="center", va="bottom")
    handles.append(Line2D([], [], color=INK2, lw=1.0, ls=(0, (4, 2.5)), label=L("čárkovaně: konzervativní rozestupy na schodech (horní mez)",
                                                                                    "dashed: conservative stair spacing (upper marker)")))
    ax.set_xlabel(L("čas od začátku evakuace [s]", "time since the start of the evacuation [s]"))
    ax.set_ylabel(L("evakuováno [%]", "agents evacuated [%]"))
    ax.set_ylim(0, 108)
    ax.set_yticks([0, 20, 40, 60, 80, 100])
    ax.set_xlim(0, None)
    axfmt(ax, "x")
    axfmt(ax, "y")
    ax.legend(handles=handles, loc="upper center", bbox_to_anchor=(0.5, -0.17), ncol=1, fontsize=7.5)
    save(fig, out, "evacuation_curves_by_venue")


# --- 2 ---
def fig2(out):
    bn = bottleneck()
    fig, ax = plt.subplots(figsize=(W, 3.5))
    xs, lbs, ex, tops = [], [], [], []
    for v in td.VENUES:
        r100, rc, r95 = first(v + "_100"), first(v + "_cons"), td.case_runs(v + "_95")
        r_before = first(v + "_100", td.MATRIX_DIR_BEFORE)
        if not r100:
            continue
        n = seats(r100)
        col = VENUE_COLOR[v]
        # columns beside the venue's seat count: the 95 % range, the default (100 %), the conservative upper marker, before the calibration
        col_at = lambda dx: offset_copy(ax.transData, fig=fig, x=dx, y=0, units="points")
        if r95:
            range_marker(ax, n, [r["t100"] for r in r95], col, transform=col_at(-11), zorder=4)
        if r_before:
            ax.plot([n], [r_before["t100"]], marker="x", ms=5, mew=1.2, color=MUTED, transform=col_at(22), ls="", zorder=4)
        if rc:   # the stair-flow bracket: the default (filled) and the conservative set (open triangle, the upper marker), joined
            ax.plot([n, n], [r100["t100"], rc["t100"]], color=col, lw=0.8, ls=(0, (1, 1.5)), transform=col_at(5.5), zorder=3)
            ax.plot([n], [rc["t100"]], marker="^", ms=6.0, mfc=SURFACE, mec=col, mew=1.2, ls="", transform=col_at(11), zorder=5)
        ax.plot([n], [r100["t100"]], "o", ms=6.5, color=col, mec=SURFACE, mew=1.1, zorder=6)
        top = max(r100["t100"], rc["t100"] if rc else 0.0, r_before["t100"] if r_before else 0.0, max((r["t100"] for r in r95), default=0.0))
        tops.append(top)
        txt = f"{v}: {sec(r100['t100'])}" + (f" ({nf(rc['t100'])})" if rc else "")
        ax.annotate(txt, (n, top), xytext=(5, 8), textcoords="offset points", color=INK2, fontsize=8, ha="center", va="bottom")
        if bn and (v + "_100") in bn["bounds"]:
            b = bn["bounds"][v + "_100"]
            xs.append(n)
            lbs.append(b["t_lb_s"])
            ex.append(b["a_exits_s"])
    if xs:
        ax.plot(xs, lbs, color=INK2, lw=1.1, marker="s", ms=4.5, mfc=SURFACE, mec=INK2, mew=1.1, zorder=3)
        ax.plot(xs, ex, color=MUTED, lw=0.9, marker="D", ms=3.8, mfc=SURFACE, mec=MUTED, mew=1.0, zorder=3)
    ax.axhline(480.0, color=MUTED, lw=0.9, ls=(0, (4, 3)), zorder=2)
    ax.text(0.005, 480.0, L("8 min: plánovací hodnota", "8 min: planning reference") + vf(), transform=ax.get_yaxis_transform(),
            ha="left", va="bottom", color=MUTED, fontsize=7.5)
    ax.set_xscale("log")
    ax.set_xticks([3728, 15832, 63424])
    ax.set_xticklabels([f"{nf(3728)} (S)", f"{nf(15832)} (M)", f"{nf(63424)} (L)"])
    ax.minorticks_off()
    ax.set_xlim(2600, 110000)
    ax.set_ylim(0, 1.12 * max(tops))   # the offset (column) markers do not take part in autoscaling; room for the labels above them
    axfmt(ax, "y")
    ax.set_xlabel(L("počet míst k sezení (projektovaná kapacita), logaritmická osa", "seats (design capacity), log scale"))
    ax.set_ylabel(L("čas [s]", "time [s]"))
    handles = [Line2D([], [], ls="", marker="o", ms=7, color=INK2, mec=SURFACE, label=L(f"{T100} při 100{NBSP}% obsazenosti (kalibrované rozestupy na schodech, výchozí)",
                                                                                         f"{T100} at 100% load (calibrated stair spacing, default)")),
               Line2D([], [], ls="", marker="^", ms=6.5, mfc=SURFACE, mec=INK2, mew=1.3, label=L("konzervativní rozestupy (horní mez; číslo v závorce)",
                                                                                                 "conservative stair spacing (upper marker; in brackets)")),
               range_handle(L(f"obsazenost 95{NBSP}%: průměr a rozsah ze 3 opakování", "95% load: mean and range over 3 repetitions")),
               Line2D([], [], ls="", marker="x", ms=5, mew=1.2, color=MUTED, label=L("před kalibrací schodů (rovinné rozestupy)",
                                                                                    "before the stair calibration (level spacing)")),
               Line2D([], [], color=INK2, lw=1.1, marker="s", ms=4.5, mfc=SURFACE, label=L("dolní mez (nejpomalejší z: východy, schodiště, chůze)",
                                                                                          "lower bound (the slowest of exits, gangways, travel)")),
               Line2D([], [], color=MUTED, lw=0.9, marker="D", ms=3.8, mfc=SURFACE, label=L("mez ze šířky východů", "exit-width bound"))]
    ax.legend(handles=handles, loc="upper center", bbox_to_anchor=(0.5, -0.2), ncol=2, fontsize=7.5)
    save(fig, out, "evacuation_time_vs_capacity")


# --- 3 ---
def load_series(v):
    """(actual load %, runs) points of a venue in increasing load."""
    keys = [v + "_95", v + "_100"] + (["S_125", "S_150"] if v == "S" else [v + "_max"])
    pts = []
    for k in keys:
        rs = td.case_runs(k)
        if rs:
            pts.append((100.0 * sum(r["load"] for r in rs) / len(rs), rs, k))
    return pts


def fig3(out):
    fig, (a1, a2) = plt.subplots(1, 2, figsize=(W, 3.0))
    for v in td.VENUES:
        pts = load_series(v)
        if not pts:
            continue
        col = VENUE_COLOR[v]
        for ax, f in ((a1, lambda r: r["t100"]), (a2, lambda r: r["circ_exposure"])):
            x = [p[0] for p in pts]
            m = [sum(f(r) for r in rs) / len(rs) for _, rs, _ in pts]
            ax.plot(x, m, color=col, lw=1.6, zorder=3)
            for xi, (_, rs, _) in zip(x, pts):
                if len(rs) > 1:
                    range_marker(ax, xi, [f(r) for r in rs], col)        # a mean over seeds
                else:
                    ax.plot([xi], [f(rs[0])], "o", ms=4.5, color=col, mec=SURFACE, mew=1.0, zorder=5)   # one run (100 %)
            ax.annotate(v, (x[-1], m[-1]), xytext=(7, 0), textcoords="offset points", color=INK2, fontsize=8, va="center")
            if v != "S" and pts[-1][2].endswith("_max"):   # the maximum achievable load, labelled at its actual value
                ax.annotate(L(f"{pc(x[-1], 1)}\nmax. dosažitelné", f"{pc(x[-1], 1)}\nmax. achievable"), (x[-1], m[-1]), xytext=(0, -11),
                            textcoords="offset points", color=MUTED, fontsize=6.3, ha="center", va="top")
        gw = td.case_runs("S_150gw") if v == "S" else []
        if gw:
            sh = offset_copy(a1.transData, fig=fig, x=-7, y=0, units="points")
            range_marker(a1, 150.0, [r["t100"] for r in gw], col, transform=sh, marker="D")
            sh2 = offset_copy(a2.transData, fig=fig, x=-7, y=0, units="points")
            range_marker(a2, 150.0, [r["circ_exposure"] for r in gw], col, transform=sh2, marker="D")
    a1.set_ylabel(f"{T100} [s]")
    a2.set_ylabel(L(f"expozice kritické hustotě (≥{NBSP}5{NBSP}osob/m²)\nna komunikacích [osoba·s]",   # two lines: the panel's height
                    f"exposure to critical density (≥{NBSP}5{NBSP}persons/m²)\nin circulation areas [person-s]"))
    a2.set_yscale("log")
    a2.yaxis.set_major_locator(matplotlib.ticker.FixedLocator([1e4, 3e4, 1e5, 3e5, 1e6, 3e6, 1e7]))
    a2.yaxis.set_major_formatter(LangFormatter(0))
    a2.yaxis.set_minor_locator(matplotlib.ticker.NullLocator())
    for ax in (a1, a2):
        ax.set_xlabel(L("obsazenost [% míst k sezení]", "load [% of the seats]"))
        ax.set_xticks([95, 100, 110, 120, 130, 140, 150])
        ax.set_xlim(92, 158)   # room for the end labels inside the axes (the right panel's would leave the figure)
        axfmt(ax, "x")
        ax.minorticks_off()
    axfmt(a1, "y")
    a1.set_ylim(0, None)
    vh = [Line2D([], [], color=VENUE_COLOR[v], lw=1.6, label=venue_name(v)) for v in td.VENUES]
    mh = [range_handle(L("průměr a rozsah ze 3 opakování", "mean and range over 3 repetitions")),
          range_handle(L(f"S 150{NBSP}%, stání i na schodištích", "S 150%, standing also on the gangways"), marker="D"),
          Line2D([], [], ls="", marker="o", ms=4.5, color=INK2, mec=SURFACE, label=L(f"100{NBSP}% (jeden běh)", "100% (one run)"))]
    handles = [h for pair in zip(vh, mh) for h in pair]   # column-major: venues in the first row, markers in the second
    fig.legend(handles=handles, loc="upper center", ncol=3, bbox_to_anchor=(0.5, 1.12), fontsize=7.5)
    fig.tight_layout()
    save(fig, out, "safety_load_vs_time_and_exposure")


# --- 4 ---
def fig4(out):
    fig, (a1, a2) = plt.subplots(1, 2, figsize=(W, 2.8))
    models = [(L("volba východu podle front (výchozí)", "queue-aware (default)"), "_100", SLOT[0]), (L("nejbližší východ", "nearest exit"), "_nearest", SLOT[1])]
    w = 0.36
    for j, (label, suf, col) in enumerate(models):
        for i, v in enumerate(td.VENUES):
            r = first(v + suf)
            if not r:
                continue
            x = i + (j - 0.5) * (w + 0.04)
            a1.bar(x, r["t100"], width=w, color=col, edgecolor=SURFACE, linewidth=0)
            a1.annotate(nf(r["t100"]), (x, r["t100"]), xytext=(0, 2), textcoords="offset points", ha="center", fontsize=7, color=INK2)
            a2.bar(x, r["unused_width_m"], width=w, color=col, edgecolor=SURFACE, linewidth=0)
            a2.annotate(f"{nf(r['unused_width_m'], 1)} m ({pc(100 * r['unused_width_frac'])})" if r["unused_width_m"] > 0 else "0", (x, r["unused_width_m"]),
                        xytext=(0, 2), textcoords="offset points", ha="center", fontsize=6.5, color=INK2)
    for ax in (a1, a2):
        ax.set_xticks(range(len(td.VENUES)))
        ax.set_xticklabels([venue_name(v) for v in td.VENUES])
        ax.grid(axis="x", visible=False)
        axfmt(ax, "y")
    a1.set_ylabel(f"{T100} [s]")
    a2.set_ylabel(L("nevyužitá šířka východů [m]", "unused exit width [m]"))
    fig.legend(handles=[Patch(color=c, label=l) for l, _, c in models], loc="upper center", ncol=2, bbox_to_anchor=(0.5, 1.07), fontsize=7.5)
    fig.tight_layout()
    save(fig, out, "evacuation_nearest_vs_queue_aware")


# --- 5 ---
def fig5(out):
    fig, ax = plt.subplots(figsize=(W, 2.5))
    ylabels, y, yt = [], 0.0, []
    for v in td.VENUES:
        r = first(v + "_100")
        if not r:
            continue
        for what, d, a in ((L("evakuovaní", "evacuated"), r["doors_share"], r["avenues_share"]),
                           (L("šířka východů", "exit width"), r["doors_width_m"] / r["total_width_m"], r["avenues_width_m"] / r["total_width_m"])):
            ax.barh(y, 100 * d, height=0.62, color=SLOT[0], edgecolor=SURFACE, linewidth=2)
            ax.barh(y, 100 * a, left=100 * d, height=0.62, color=SLOT[1], edgecolor=SURFACE, linewidth=2)
            for lft, val, colr in ((0, d, SURFACE), (d, a, INK)):
                if val >= 0.08:
                    ax.text(100 * (lft + val / 2), y, pc(100 * val), ha="center", va="center", fontsize=7.5, color=colr)
            ylabels.append(f"{v}: {what}")
            yt.append(y)
            y += 1
        y += 0.4
    ax.set_yticks(yt)
    ax.set_yticklabels(ylabels)
    ax.invert_yaxis()
    ax.set_xlim(0, 100)
    axfmt(ax, "x")
    ax.set_xlabel(L("podíl [%]", "share [%]"))
    ax.grid(axis="y", visible=False)
    ax.legend(handles=[Patch(color=SLOT[0], label=L("dveře z ochozu", "concourse doors")), Patch(color=SLOT[1], label=L("průchody u hřiště", "avenues"))],
              loc="upper center", ncol=2, bbox_to_anchor=(0.5, 1.18))
    save(fig, out, "evacuation_exit_utilisation")


# --- 6 ---
def fig6(out):
    vs = [v for v in td.VENUES if first(v + "_100")]
    if not vs:
        return
    counts = [len(first(v + "_100")["flows"]["gangways"]) for v in vs]
    fig, axes = plt.subplots(1, len(vs), figsize=(W, 2.8), sharey=True, gridspec_kw={"width_ratios": counts})
    axes = np.atleast_1d(axes)
    for ax, v in zip(axes, vs):
        r = first(v + "_100")
        g = sorted(r["flows"]["gangways"], key=lambda x: -(x["saturated_share"] or 0.0))
        cols = [SLOT[0] if x["type"] == "straight" else SLOT[1] for x in g]
        ax.bar(range(len(g)), [100 * (x["saturated_share"] or 0.0) for x in g], width=0.8, color=cols, edgecolor=SURFACE, linewidth=0)
        ax.set_xlabel(L(f"{v}: schodiště seřazená ({len(g)})", f"{v}: gangways, sorted ({len(g)})"), fontsize=8)
        ax.set_xticks([])
        ax.grid(axis="x", visible=False)
        ax.set_xlim(-0.8, len(g) - 0.2)
    axes[0].set_ylabel(L("podíl aktivní doby v nasycení [%]", "saturated share of the active time [%]"))
    axes[0].set_ylim(0, 100)
    axfmt(axes[0], "y")
    fig.legend(handles=[Patch(color=SLOT[0], label=L("přímé schodiště", "straight gangway")), Patch(color=SLOT[1], label=L("rohové schodiště", "corner gangway"))],
               loc="upper center", ncol=2, bbox_to_anchor=(0.5, 1.07), fontsize=7.5)
    fig.tight_layout()
    save(fig, out, "evacuation_gangway_saturation")


# --- 7 ---
def density_grid(d):
    rows = td.load_csv(d, "heatmap.csv")
    s = td.load_summary(d)
    res = int(s["units"]["grid_res"])
    gmin = float(s["units"]["grid_min_m"])
    val = np.full((res, res), np.nan)
    kind = np.zeros((res, res), dtype=int)   # 0 none, 1 circulation rated, 2 seat row, 3 circulation not rated (< 0.5 m^2)
    for x in rows:
        ix, iy = int(x["ix"]), int(x["iy"])
        sc = x.get("scope", "")
        if sc == "circulation":
            if float(x["walkable_m2"]) >= PEAK_MIN_WALKABLE_M2:
                val[iy, ix] = float(x["peak_density_p_m2"])
                kind[iy, ix] = 1
            else:
                kind[iy, ix] = 3
        elif sc == "seat_row":
            kind[iy, ix] = 2
    return val, kind, [gmin, gmin + res, gmin, gmin + res]


def fig7(out):
    panels = [("S", "S_100", L("S, 100 %", "S, 100%")), ("M", "M_100", L("M, 100 %", "M, 100%")), ("L", "L_100", L("L, 100 %", "L, 100%")),
              ("L", "L_max", None)]
    data = []
    for v, key, label in panels:
        r = first(key)
        if r:
            if label is None:
                label = L(f"L, {pc(100 * r['load'], 1)} (max. dosažitelné)", f"L, {pc(100 * r['load'], 1)} (max. achievable)")
            data.append((v, label, density_grid(r["dir"]), r))
    if not data:
        return
    vmax = max(7.0, math.ceil(max(np.nanmax(g[0]) for _, _, g, _ in data)))
    cmap = LinearSegmentedColormap.from_list("blue_ramp", BLUE_RAMP)
    fig = plt.figure(figsize=(W, W * 1.02))
    gs = fig.add_gridspec(3, 2, height_ratios=[1, 1, 0.07], hspace=0.12, wspace=0.06, left=0.01, right=0.99, top=0.99, bottom=0.10)
    axes = [fig.add_subplot(gs[i // 2, i % 2]) for i in range(4)]
    im = None
    for ax, (v, label, (val, kind, ext), r) in zip(axes, data):
        base = np.full(kind.shape + (4,), 0.0)
        for k, c in ((2, SEAT_ROWS), (3, NOT_RATED)):
            base[kind == k] = matplotlib.colors.to_rgba(c)
        ax.imshow(base, origin="lower", extent=ext, interpolation="nearest")
        im = ax.imshow(np.ma.masked_invalid(val), origin="lower", extent=ext, cmap=cmap, vmin=0.0, vmax=vmax, interpolation="nearest")
        h = OUTER_HALF_M[v] + 1.5   # each panel filled by its venue (its own scale; a scale bar instead of axes)
        ax.set_xlim(-h, h)
        ax.set_ylim(-h, h)
        ax.set_aspect("equal")
        ax.axis("off")
        bar = {"S": 10, "M": 20, "L": 40}[v]
        x0, y0 = -h + 0.06 * 2 * h, -h + 0.05 * 2 * h
        ax.add_patch(Rectangle((x0, y0), bar, 0.012 * 2 * h, color=INK, lw=0))
        ax.text(x0 + bar / 2, y0 + 0.025 * 2 * h, f"{bar}{NBSP}m", ha="center", va="bottom", fontsize=7, color=INK,
                bbox=dict(boxstyle="square,pad=0.15", fc=SURFACE, ec="none"))   # legible over the map (L's corner gangways cross it)
        ax.text(0.02, 0.98, label + "\n" + L(f"špička {nf(r['circ_peak'], 2)} osob/m²", f"peak {nf(r['circ_peak'], 2)} persons/m²"),
                transform=ax.transAxes, ha="left", va="top", fontsize=7.5, color=INK, bbox=dict(boxstyle="round,pad=0.25", fc=SURFACE, ec=HAIR, lw=0.6))
    for ax in axes[len(data):]:
        ax.axis("off")
    cax = fig.add_subplot(gs[2, :])
    cb = fig.colorbar(im, cax=cax, orientation="horizontal")
    cb.set_label(L("špičková hustota na komunikačních plochách [osob/m²]", "circulation-zone peak density [persons/m²]"), color=INK2, fontsize=8)
    cb.set_ticks([0, LOS_E, LOS_F, CRUSH, vmax])
    cb.set_ticklabels(["0", L(f"stupeň E {nf(LOS_E, 2)}", f"LoS E {nf(LOS_E, 2)}"), L(f"stupeň F {nf(LOS_F, 2)}", f"LoS F {nf(LOS_F, 2)}"),
                       L(f"kritická {nf(CRUSH)}", f"crush {nf(CRUSH)}"), nf(vmax)])
    cb.ax.tick_params(labelsize=7)
    cb.outline.set_edgecolor(AXIS)
    fig.legend(handles=[Patch(color=SEAT_ROWS, label=L("řady sedadel (fronty v jednom zástupu, nehodnoceny)", "seat rows (single-file queues, not rated)")),
                        Patch(color=NOT_RATED, label=L(f"buňky komunikací pod {nf(PEAK_MIN_WALKABLE_M2, 1)} m² plochy (nehodnoceny)",
                                                       f"circulation cells below {nf(PEAK_MIN_WALKABLE_M2, 1)} m² of floor (not rated)"))],
               loc="lower center", ncol=2, bbox_to_anchor=(0.5, -0.005), fontsize=7)
    save(fig, out, "safety_peak_density_maps")


# --- 8 ---
def fig8(out):
    rows = td.load_csv(FD_DIR, "fd.csv")
    rho = [float(r["rho_p_m2"]) for r in rows]
    v = [float(r["speed_m_s"]) for r in rows]
    J = [float(r["flow_p_m_min"]) for r in rows]
    V0, GAMMA, RHO_MAX = 1.34, 1.913, 5.4
    rr = np.linspace(0.05, RHO_MAX, 300)
    vw = V0 * (1.0 - np.exp(-GAMMA * (1.0 / rr - 1.0 / RHO_MAX)))
    fig, (a1, a2) = plt.subplots(1, 2, figsize=(W, 2.8))
    a1.plot(rr, vw, color=INK2, lw=1.4)
    a1.plot(rho, v, color=SLOT[0], lw=1.4, marker="o", ms=4.5, mec=SURFACE, mew=1.0)
    a2.plot(rr, rr * vw * 60.0, color=INK2, lw=1.4)
    a2.plot(rho, J, color=SLOT[0], lw=1.4, marker="o", ms=4.5, mec=SURFACE, mew=1.0)
    a1.set_ylabel(L("rychlost [m/s]", "speed [m/s]"))
    a2.set_ylabel(L("měrný průtok [osob/(m·min)]", "specific flow [persons/(m min)]"))
    for ax in (a1, a2):
        ax.set_xlabel(L("hustota [osob/m²]", "density [persons/m²]"))
        ax.set_xlim(0, 6.2)
        ax.set_ylim(0, None)
        axfmt(ax, "x")
    axfmt(a1, "y", 1)
    axfmt(a2, "y")
    fig.legend(handles=[Line2D([], [], color=SLOT[0], lw=1.4, marker="o", ms=4.5, mec=SURFACE, label=L("model (rovinná chodba 3 m, průměr ze 3 opakování)",
                                                                                                              "model (level 3 m corridor, mean of 3 repetitions)")),
                        Line2D([], [], color=INK2, lw=1.4, label="Weidmann (1993)" + vf())], loc="upper center", ncol=2, bbox_to_anchor=(0.5, 1.07), fontsize=7.5)
    fig.tight_layout()
    save(fig, out, "validation_fundamental_diagram")


# --- 9 ---
def fig9(out):
    walks = [("level", L("rovinná\nchůze", "level\nwalking")), ("stairs", L("schody\n(výchozí)", "stairs\n(default)"))]
    exits = [(L("volba východu podle front", "queue-aware exit choice"), SLOT[0], {"level": "_level", "stairs": "_100"}),
             (L("nejbližší východ", "nearest exit"), SLOT[1], {"level": "_nearest_level", "stairs": "_nearest"})]
    vs = [v for v in td.VENUES if first(v + "_100")]
    fig, axes = plt.subplots(1, len(vs), figsize=(W, 2.7))
    axes = np.atleast_1d(axes)
    w = 0.36
    for ax, v in zip(axes, vs):
        for j, (label, col, suf) in enumerate(exits):
            for i, (wk, _) in enumerate(walks):
                r = first(v + suf[wk])
                if not r:
                    continue
                x = i + (j - 0.5) * (w + 0.04)
                ax.bar(x, r["t100"], width=w, color=col, edgecolor=SURFACE, linewidth=0)
                ax.annotate(nf(r["t100"]), (x, r["t100"]), xytext=(0, 2), textcoords="offset points", ha="center", fontsize=6.5, color=INK2)
        ax.set_xticks(range(len(walks)))
        ax.set_xticklabels([x[1] for x in walks], fontsize=7.5)
        ax.grid(axis="x", visible=False)
        axfmt(ax, "y")
        panel_label(ax, venue_name(v))
        ax.set_xlim(-0.6, 1.6)
        ax.set_ylim(0, ax.get_ylim()[1] * 1.08)
    axes[0].set_ylabel(f"{T100} [s]")
    fig.legend(handles=[Patch(color=c, label=l) for l, c, _ in exits], loc="upper center", ncol=2, bbox_to_anchor=(0.5, 1.08), fontsize=7.5)
    fig.text(0.5, -0.04, L("schody = rychlost na schodech a kalibrované rozestupy na schodech; rovinná chůze = rovinná rychlost i rozestupy",
                           "stairs = stair speed and calibrated stair spacing; level walking = level speed and spacing"), ha="center", va="top",
             fontsize=7, color=INK2)
    fig.tight_layout()
    save(fig, out, "evacuation_walking_model_variants")


# --- 10 ---
def stair_rows(pattern):
    found = sorted(glob.glob(pattern))
    if not found:
        return None, None
    rows = td.load_csv(found[-1], "stair.csv")
    out = {}
    for r in rows:
        out.setdefault(r["dir"], []).append((float(r["rho_p_m2"]), float(r["flow_p_m_s"])))
    return out, found[-1]


def fig10(out):
    runs = {k: stair_rows(p) for k, p in STAIR_RUNS.items()}
    styles = {"base": (MUTED, (0, (1.2, 1.5)), "o", L("před kalibrací: rovinné rozestupy ($T$ = 0,3 s)", "before the calibration: level spacing ($T$ = 0.3 s)")),
              "emp": (INK, "-", "o", L("kalibrované rozestupy (výchozí; $T$ nahoru 0,625 s, dolů 0,65 s)", "calibrated stair spacing (default; $T$ up 0.625 s, down 0.65 s)")),
              "cons": (INK2, (0, (4, 2)), "s", L("konzervativní rozestupy ($T$ 0,75 / 0,78 s)", "conservative stair spacing ($T$ 0.75 / 0.78 s)"))}
    fig, axes = plt.subplots(1, 2, figsize=(W, 2.9), sharey=True)
    for ax, d, name in zip(axes, ("up", "down"), (L("nahoru (výstup)", "ascending"), L("dolů (sestup)", "descending"))):
        for k in ("base", "emp", "cons"):
            data, _ = runs[k]
            if data and d in data:
                col, ls, mk, _ = styles[k]
                ax.plot(*zip(*data[d]), color=col, ls=ls, lw=1.4 if k != "base" else 1.2, marker=mk, ms=2.8, mfc=col, mec=col)
        ax.axhline(EMPIRICAL[d], color=SLOT[0], lw=0.9)
        ax.axhline(CONSERVATIVE, color=SLOT[1], lw=0.9)
        ax.text(0.985, EMPIRICAL[d], L(f"empirický cíl {nf(EMPIRICAL[d], 2)}", f"empirical target {nf(EMPIRICAL[d], 2)}"), transform=ax.get_yaxis_transform(),
                ha="right", va="bottom", fontsize=7, color=INK2)
        ax.text(0.985, CONSERVATIVE, L(f"konzervativní cíl {nf(CONSERVATIVE, 2)}", f"conservative target {nf(CONSERVATIVE, 2)}"),
                transform=ax.get_yaxis_transform(), ha="right", va="top", fontsize=7, color=INK2)
        ax.set_xlabel(L("hustota [osob/m²]", "density [persons/m²]"))
        panel_label(ax, name)
        ax.set_xlim(0, 5.2)
        ax.set_ylim(0, 2.1)
        ax.yaxis.set_major_locator(matplotlib.ticker.MultipleLocator(0.2))
        axfmt(ax, "x")
        axfmt(ax, "y", 1)
    axes[0].set_ylabel(L("měrný průtok [osob/(m·s)]", "specific flow [persons/(m s)]"))
    handles = [Line2D([], [], color=styles[k][0], ls=styles[k][1], lw=1.4, marker=styles[k][2], ms=2.8, label=styles[k][3]) for k in ("base", "emp", "cons")]
    handles += [Line2D([], [], color=SLOT[0], lw=0.9, label=L("Burghardt a kol. (2013): naměřená maxima", "Burghardt et al. (2013): measured maxima") + vf()),
                Line2D([], [], color=SLOT[1], lw=0.9, label=L("příručka Green Guide (2018): 66 osob/(m·min)", "Green Guide (2018): 66 persons/(m min)") + vf())]
    fig.legend(handles=handles, loc="lower center", ncol=2, bbox_to_anchor=(0.5, -0.17), fontsize=7)
    fig.tight_layout()
    save(fig, out, "validation_stair_flow_diagram")


# --- 11 ---
def fig11(out):
    keys = {"S": ["S_95", "S_100", "S_125", "S_150", "S_150gw", "S_nearest"], "M": ["M_95", "M_100", "M_max", "M_nearest"],
            "L": ["L_95", "L_100", "L_max", "L_nearest"]}
    names = {"95": L("95 %", "95%"), "100": L("100 %", "100%"), "125": L("125 %", "125%"), "150": L("150 %", "150%"),
             "150gw": L("150 %, stání i na schodištích", "150%, standing on the gangways too"), "nearest": L("100 %, nejbližší východ", "100%, nearest exit")}
    fig, axes = plt.subplots(3, 1, figsize=(W, 4.6), gridspec_kw={"height_ratios": [6, 4, 4]})
    incomplete = []
    for ax, v in zip(axes, td.VENUES):
        col = VENUE_COLOR[v]
        ys, labels = [], []
        for i, k in enumerate(keys[v]):
            a, b = td.case_runs(k, td.MATRIX_DIR_BEFORE), td.case_runs(k)
            if not a or not b:
                continue
            mean_done = lambda rs: sum(r["t100"] for r in rs if r["complete"]) / max(1, sum(1 for r in rs if r["complete"]))
            ta, tb = mean_done(a), mean_done(b)   # over the completed runs (a gridlocked run has no t100; marked below)
            y = -i
            ax.plot([ta, tb], [y, y], color=HAIR, lw=2.2, solid_capstyle="round", zorder=2)
            ax.plot([ta], [y], "o", ms=5, mfc=SURFACE, mec=MUTED, mew=1.2, zorder=3)
            if any(not r["complete"] for r in a):   # a run that did not complete (gridlock): the mean of the others, marked
                incomplete.append((v, k))
                ax.annotate("*", (ta, y), xytext=(0, 3.5), textcoords="offset points", ha="center", va="bottom", fontsize=8, color=INK2)
            ax.plot([tb], [y], "o", ms=5.5, color=col, mec=SURFACE, mew=1.0, zorder=4)
            ax.annotate(f"{nf(tb)} ({'+' if tb >= ta else ''}{pc(100 * (tb / ta - 1), 0)})", (tb, y), xytext=(6, 0), textcoords="offset points",
                        va="center", fontsize=6.8, color=INK2)
            suf = k.split("_", 1)[1]
            label = names.get(suf) or (L(f"{pc(100 * b[0]['load'], 1)} (max. dosažitelné)", f"{pc(100 * b[0]['load'], 1)} (max. achievable)") if suf == "max" else suf)
            ys.append(y)
            labels.append(label)
        ax.set_yticks(ys)
        ax.set_yticklabels(labels, fontsize=7)
        ax.grid(axis="y", visible=False)
        ax.set_ylim(min(ys) - 0.6 if ys else -1, 0.6)
        lo, hi = ax.get_xlim()
        ax.set_xlim(lo, hi + 0.12 * (hi - lo))
        axfmt(ax, "x")
        panel_label(ax, venue_name(v))
    axes[-1].set_xlabel(f"{T100} [s]")
    fig.legend(handles=[Line2D([], [], ls="", marker="o", ms=5, mfc=SURFACE, mec=MUTED, mew=1.2, label=L("před kalibrací schodů (rovinné rozestupy)", "before the stair calibration (level spacing)")),
                        Line2D([], [], ls="", marker="o", ms=5.5, color=INK2, mec=SURFACE, label=L("kalibrované rozestupy na schodech (výchozí; barva = stadion)",
                                                                                                   "calibrated stair spacing (default; colour = venue)"))],
               loc="upper center", ncol=2, bbox_to_anchor=(0.5, 1.04), fontsize=7.5)
    fig.tight_layout()
    if incomplete:
        fig.text(0.01, -0.01, L("* před kalibrací schodů: jeden ze tří běhů nedokončen (trvalé uváznutí protiproudů na rohovém schodišti); "
                                "průměr ze zbylých dvou", "* before the stair calibration: one of three runs did not complete (a permanent counterflow "
                                "gridlock on a corner gangway); the mean of the other two"), ha="left", va="top", fontsize=6.8, color=INK2)
    save(fig, out, "evacuation_before_after_stair_calibration")


# --- 12 ---
def narrow_runs():
    """{label: (width_m, [(rho, J)])} of the narrow-passage runs (tools/fd/narrow_passage.sh): the FD protocol (fd.csv, per metre of the
    wall-to-wall width) and the low-walled level corridor (stair.csv 'level', per metre of the centre span, converted to the wall-to-wall width
    span + 0.40 m: density and flow scale by span / width)."""
    out = {"full": {}, "low": {}}
    for w in ("1.2", "2.4", "3"):
        found = sorted(glob.glob(os.path.join(NARROW_DIR, f"fd_w{w}_*")))
        if found:
            rows = td.load_csv(found[-1], "fd.csv")
            out["full"][float(w)] = [(float(r["rho_p_m2"]), float(r["flow_p_m_s"])) for r in rows]
    for sp in ("0.8", "2", "2.6"):
        found = sorted(glob.glob(os.path.join(NARROW_DIR, f"lowwall_span{sp}_*")))
        if found:
            span = float(sp)
            k = span / (span + 0.40)
            rows = [r for r in td.load_csv(found[-1], "stair.csv") if r["dir"] == "level"]
            out["low"][span + 0.40] = [(k * float(r["rho_p_m2"]), k * float(r["flow_p_m_s"])) for r in rows]
    return out


def fig12(out):
    runs = narrow_runs()
    if not runs["full"] and not runs["low"]:
        return
    shades = {1.2: BLUE_RAMP[12], 2.4: BLUE_RAMP[8], 3.0: BLUE_RAMP[4]}
    fig, axes = plt.subplots(1, 2, figsize=(W, 2.9), sharey=True)
    for ax, key, name in ((axes[0], "full", L("stěny v plné výšce", "full-height walls")),
                          (axes[1], "low", L("nízké stěny (0,85 m)", "low walls (0.85 m)"))):
        for w, pts in sorted(runs[key].items()):
            col = shades.get(round(w, 1), INK2)
            ax.plot(*zip(*pts), color=col, lw=1.4, marker="o", ms=3.2, mfc=col, mec=col)
        panel_label(ax, name)
        ax.set_xlabel(L("hustota [osob/m²]", "density [persons/m²]"))
        ax.set_xlim(0, 6.2)
        ax.set_ylim(0, 2.1)
        ax.yaxis.set_major_locator(matplotlib.ticker.MultipleLocator(0.2))
        axfmt(ax, "x")
        axfmt(ax, "y", 1)
    axes[0].set_ylabel(L("měrný průtok [osob/(m·s)]", "specific flow [persons/(m s)]"))
    fig.legend(handles=[Line2D([], [], color=shades[w], lw=1.4, marker="o", ms=3.2, label=L(f"šířka chodby {nf(w, 1)} m (stěna–stěna)", f"corridor {nf(w, 1)} m wide (wall to wall)"))
                        for w in (1.2, 2.4, 3.0)], loc="upper center", ncol=3, bbox_to_anchor=(0.5, 1.1), fontsize=7.5)
    fig.tight_layout()
    save(fig, out, "validation_corridor_width_flow")


# --- 13-18: the performance figures (benchmark_crowd thesis, results/benchmarks/thesis) ---
BENCH_DIR = "results/benchmarks/thesis"
PERF_CELLS = os.environ.get("PERF_CELLS", os.path.join(BENCH_DIR, "thesis_2*_cells.csv"))     # the latest full (not quick) run
PERF_SCALING = os.environ.get("PERF_SCALING", os.path.join(BENCH_DIR, "cpu_scaling_M_*.csv"))
PERF_VENUES = ("S", "M", "L")
TERRACE_NS = (1024, 4096, 16384, 65536, 262144)
DT_REAL_MS = 174.90671      # simulated milliseconds per step (DT_REAL_S, sim_params.hpp)
# The historical optimisation chain (GPU ms per step, snapshot mode, the terrace; AMD 26.8.1, the point / disk model before the hard bodies for the
# first four steps): A/B medians from results/benchmarks/optimisation_chain/: vram_buffers_ab_20261002_1047.md (base: GL_DYNAMIC_DRAW buffers in host
# memory; new: GL_DYNAMIC_COPY), shared_memory_sort_ab_20261002_1339.md, sorted_gather_ab_20261002_1419.md and hard_body_model_ab_20261005_1705.md
# (the hard-body model with the projection, K = 32; its base = the sorted gather's program)
CHAIN = [  # (key, {N: (spawn, congested)})
    ("host", {4096: (0.1198, 0.1399), 65536: (1.297, 1.500), 262144: (87.67, 90.17)}),
    ("vram", {4096: (0.1129, 0.1329), 65536: (0.7513, 1.129), 262144: (5.972, 8.527)}),
    ("sort", {4096: (0.0667, 0.0869), 65536: (0.6311, 1.0186), 262144: (5.5483, 8.9712)}),
    ("gather", {4096: (0.0596, 0.0751), 65536: (0.4610, 0.7048), 262144: (3.4370, 4.9906)}),
    ("hardbody", {4096: (0.6463, 0.7478), 65536: (9.0722, 19.5158)}),
]
CHAIN_SOURCES = ["results/benchmarks/optimisation_chain/vram_buffers_ab_20261002_1047.md", "results/benchmarks/optimisation_chain/shared_memory_sort_ab_20261002_1339.md",
                 "results/benchmarks/optimisation_chain/sorted_gather_ab_20261002_1419.md", "results/benchmarks/optimisation_chain/hard_body_model_ab_20261005_1705.md"]
PASSES = ("hash", "sort", "cells", "choice", "predict", "project", "final")


def chain_label(k):
    return {"host": L("vyrovnávací paměti v paměti hostitele", "buffers in host memory"),
            "vram": L("vyrovnávací paměti ve VRAM", "buffers in VRAM"),
            "sort": L("třídění ve sdílené paměti", "shared-memory sort"),
            "gather": L("seřazená kopie stavu", "sorted state gather"),
            "hardbody": L("model tuhých těles s projekcí", "hard-body model with projection"),
            "current": L("současný model a ovladač", "current model and driver")}[k]


def pass_label(p):
    return {"hash": L("hašování", "hash"), "sort": L("třídění", "sort"), "cells": L("buňky a kopie", "cells / gather"),
            "choice": L("volba východu", "exit choice"), "predict": L("predikce", "predict"), "project": L("projekce", "projection"),
            "final": L("závěrečný průchod", "final pass")}[p]


def perf_rows():
    files = sorted(f for f in glob.glob(PERF_CELLS) if "_quick_" not in os.path.basename(f) or "PERF_CELLS" in os.environ)
    if not files:
        return None, None
    with open(files[-1], newline="") as f:
        rows = list(csv.DictReader(f))
    for r in rows:
        for k, v in r.items():
            if k.endswith("_ms") or k in ("realtime_factor",):
                r[k] = float(v)
        r["N"], r["agents"], r["threads"] = int(r["N"]), int(r["agents"]), int(r["threads"])
    return rows, files[-1]


def pcell(rows, workload, state, impl, threads=0):
    for r in rows:
        if r["workload"] == workload and r["state"] == state and r["impl"] == impl and (impl == "gpu" or r["threads"] == threads):
            return r
    return None


def cpu_max(rows):
    return max((r["threads"] for r in rows if r["impl"] == "cpu"), default=20)


def impl_keys(rows):
    t = cpu_max(rows)
    return [("gpu", 0), ("cpu", t), ("cpu", 1)]


def impl_label(impl, threads):
    if impl == "gpu":
        return L("GPU", "GPU")
    return L(f"CPU, {threads} vláken", f"CPU, {threads} threads") if threads > 1 else L("CPU, 1 vlákno", "CPU, 1 thread")


IMPL_STYLE = {0: dict(color=INK, ls="-", marker="o"), 1: dict(color=INK2, ls="--", marker="s"), 2: dict(color=MUTED, ls=":", marker="^")}


class LogLangFormatter(LangFormatter):
    """Log axes: each tick label with the decimals its own location needs (0,002 and 100 on one axis), never rounded."""

    def set_locs(self, locs):
        matplotlib.ticker.Formatter.set_locs(self, locs)

    def __call__(self, v, pos=None):
        d = 0
        while d < 4 and abs(round(v, d) - v) > 1e-9 * max(1.0, abs(v)):
            d += 1
        return nf(v, d)


def logfmt(ax, axis="y", subs=(1.0, 2.0, 5.0)):
    """Log-axis tick labels in the language's number format (decades and their 2, 5 multiples)."""
    a = ax.yaxis if axis == "y" else ax.xaxis
    a.set_major_locator(matplotlib.ticker.LogLocator(base=10, subs=subs))
    a.set_minor_locator(matplotlib.ticker.NullLocator())
    a.set_major_formatter(LogLangFormatter(0))


def state_name(s):
    return {"spawn": L("start (všichni usazeni)", "spawn (everyone seated)"), "congested": L(f"zahlcení (stav v čase {T50})", f"congested (the state at {T50})")}[s]


def state_name_t(s):   # the terrace's states
    return {"spawn": L("start", "spawn"), "congested": L("po 250 krocích", "after 250 steps")}[s]


def fig13(out):
    rows, _ = perf_rows()
    if not rows:
        return
    keys = impl_keys(rows)
    fig, axes = plt.subplots(1, 2, figsize=(W, 3.4), sharey=True)
    for ax, state in zip(axes, ("spawn", "congested")):
        for k, (impl, th) in enumerate(keys):
            st = IMPL_STYLE[k]
            tx, ty = [], []
            for n in TERRACE_NS:
                c = pcell(rows, f"terrace_{n}", state, impl, th)
                if c:
                    tx.append(c["agents"]); ty.append(c["round_median_ms"])
            if tx:
                ax.plot(tx, ty, color=st["color"], ls=st["ls"], lw=0.9, marker=st["marker"], ms=3.6, mfc=SURFACE, mec=st["color"], mew=0.9, alpha=0.75, zorder=2)
            vx, vy, vc = [], [], []
            for v in PERF_VENUES:
                c = pcell(rows, f"venue_{v}", state, impl, th)
                if c:
                    vx.append(c["agents"]); vy.append(c["round_median_ms"]); vc.append(VENUE_COLOR[v])
            if vx:
                ax.plot(vx, vy, color=st["color"], ls=st["ls"], lw=1.6, zorder=3)
                ax.scatter(vx, vy, s=26, marker=st["marker"], c=vc, edgecolors=SURFACE, linewidths=0.6, zorder=4)
        for v in PERF_VENUES:   # the venues direct-labelled at their GPU point
            c = pcell(rows, f"venue_{v}", state, "gpu")
            if c:
                ax.annotate(v, (c["agents"], c["round_median_ms"]), xytext=(0, -6), textcoords="offset points", ha="center", va="top", fontsize=8,
                            color=VENUE_COLOR[v], fontweight="bold")
        ax.set_xscale("log")
        ax.set_yscale("log")
        logfmt(ax, "x", subs=(1.0,))
        logfmt(ax, "y", subs=(1.0,))
        ax.set_xlabel(L("aktivní agenti", "active agents"))
        panel_label(ax, state_name(state))
    axes[0].set_ylabel(L("čas jednoho kroku [ms]", "time per step [ms]"))
    hs = [Line2D([], [], color=IMPL_STYLE[k]["color"], ls=IMPL_STYLE[k]["ls"], lw=1.6, marker=IMPL_STYLE[k]["marker"], ms=4.5, mfc=INK2, mec=SURFACE,
                 label=impl_label(i, t)) for k, (i, t) in enumerate(keys)]
    hs.append(Line2D([], [], color=MUTED, lw=0.9, marker="o", ms=3.6, mfc=SURFACE, mec=MUTED,
                     label=L("referenční tribuna: stresové měření (pevné místo, rostoucí N)", "terrace: stress sweep (fixed venue, growing N)")))
    fig.legend(handles=hs, loc="upper center", ncol=2, bbox_to_anchor=(0.5, 1.1), fontsize=7.5)
    fig.tight_layout()
    save(fig, out, "benchmark_step_time_vs_agents")


def fig14(out):
    rows, _ = perf_rows()
    if not rows:
        return
    t = cpu_max(rows)
    groups = [(f"venue_{v}", v, VENUE_COLOR[v]) for v in PERF_VENUES] + [(f"terrace_{n}", nf(n), MUTED) for n in TERRACE_NS]
    fig, axes = plt.subplots(1, 2, figsize=(W, 3.0), sharex=True)
    for ax, (num, den, ylab) in zip(axes, ((("cpu", t), ("gpu", 0), L(f"zrychlení GPU vůči CPU ({t} vláken)", f"GPU speedup over CPU ({t} threads)")),
                                          (("cpu", 1), ("cpu", t), L(f"zrychlení CPU {t} vláken vůči 1 vláknu", f"CPU speedup, {t} threads over 1")))):
        xt, xl = [], []
        x = 0.0
        for gi, (wk, name, col) in enumerate(groups):
            if gi == len(PERF_VENUES):
                x += 0.6
            for j, state in enumerate(("spawn", "congested")):
                a, b = pcell(rows, wk, state, *num), pcell(rows, wk, state, *den)
                if not (a and b):
                    continue
                sp = a["round_median_ms"] / b["round_median_ms"]
                xx = x + (j - 0.5) * 0.38
                ax.bar(xx, sp, width=0.36, color=col if j == 0 else SURFACE, edgecolor=col, linewidth=1.0, hatch=None if j == 0 else "////")
                ax.annotate(nf(sp, 0 if sp >= 10 else 1), (xx, sp), xytext=(0, 1.5), textcoords="offset points", ha="center", va="bottom", fontsize=6.2,
                            color=INK2, rotation=90)
            xt.append(x)
            xl.append(name)
            x += 1.0
        ax.set_xticks(xt)
        ax.set_xticklabels(xl, fontsize=7)
        for lab in ax.get_xticklabels()[len(PERF_VENUES):]:
            lab.set_rotation(35)
            lab.set_ha("right")
            lab.set_fontsize(6.5)
        ax.set_ylabel(ylab)
        ax.grid(axis="x", visible=False)
        axfmt(ax, "y")
        ax.set_ylim(0, ax.get_ylim()[1] * 1.12)
        ax.axvline(len(PERF_VENUES) - 0.2, color=AXIS, lw=0.8)
        ax.text(len(PERF_VENUES) + 0.1, 0.98, L("tribuna, N", "terrace, N"), transform=ax.get_xaxis_transform(), fontsize=7, color=INK2, va="top")
        ax.text(-0.4, 0.98, L("stadiony", "venues"), transform=ax.get_xaxis_transform(), fontsize=7, color=INK2, va="top")
    fig.legend(handles=[Patch(facecolor=INK2, edgecolor=INK2, label=L("start", "spawn")),
                        Patch(facecolor=SURFACE, edgecolor=INK2, hatch="////", label=L("zahlcení", "congested"))],
               loc="upper center", ncol=2, bbox_to_anchor=(0.5, 1.07), fontsize=7.5)
    fig.tight_layout()
    save(fig, out, "benchmark_speedup")


def fig15(out):
    rows, _ = perf_rows()
    if not rows:
        return
    cols = {"hash": BLUE_RAMP[0], "sort": BLUE_RAMP[2], "cells": BLUE_RAMP[4], "choice": "#b4b2a9", "predict": BLUE_RAMP[7], "project": BLUE_RAMP[10],
            "final": BLUE_RAMP[12]}
    bars = []
    for v in PERF_VENUES:
        for state in ("spawn", "congested"):
            c = pcell(rows, f"venue_{v}", state, "gpu")
            if c:
                bars.append((v, state, c))
    if not bars:
        return
    fig, ax = plt.subplots(figsize=(W, 3.0))
    x = 0.0
    xt, xl = [], []
    last_v = None
    for v, state, c in bars:
        if last_v is not None and v != last_v:
            x += 0.4
        last_v = v
        parts = {p: c[p + "_ms"] for p in PASSES}
        tot = c["round_median_ms"]
        s = sum(parts.values())
        bottom = 0.0
        for p in PASSES:
            share = 100.0 * parts[p] / s
            ax.bar(x, share, bottom=bottom, width=0.7, color=cols[p], edgecolor=SURFACE, linewidth=0.6)
            if share >= 7:
                dark = p in ("predict", "project", "final")
                ax.text(x, bottom + share / 2, pc(share), ha="center", va="center", fontsize=6.3, color=SURFACE if dark else INK)
            bottom += share
        ax.text(x, 101.5, nf(tot, 2 if tot < 10 else 1) + NBSP + "ms", ha="center", va="bottom", fontsize=6.8, color=INK2)
        xt.append(x)
        xl.append(f"{v}\n" + (L("start", "spawn") if state == "spawn" else L("zahlcení", "congested")))
        x += 1.0
    ax.set_xticks(xt)
    ax.set_xticklabels(xl, fontsize=7.5)
    ax.set_ylim(0, 108)
    ax.set_yticks([0, 20, 40, 60, 80, 100])
    axfmt(ax, "y")
    ax.set_ylabel(L("podíl na čase kroku GPU [%]", "share of the GPU step time [%]"))
    ax.grid(axis="x", visible=False)
    ax.legend(handles=[Patch(color=cols[p], label=pass_label(p)) for p in reversed(PASSES)], loc="center left", bbox_to_anchor=(1.0, 0.5), fontsize=7.5)
    fig.tight_layout()
    save(fig, out, "benchmark_gpu_pass_shares")


def fig16(out):
    rows, _ = perf_rows()
    if not rows:
        return
    keys = impl_keys(rows)
    fig, ax = plt.subplots(figsize=(W, 2.9))
    for i, v in enumerate(PERF_VENUES):
        for k, (impl, th) in enumerate(keys):
            for state, filled in (("spawn", True), ("congested", False)):
                c = pcell(rows, f"venue_{v}", state, impl, th)
                if not c:
                    continue
                rt = DT_REAL_MS / c["round_median_ms"]
                xx = i + (k - 1) * 0.26 + (-0.05 if filled else 0.05)
                ax.plot([xx], [rt], marker=IMPL_STYLE[k]["marker"], ms=5.5, color=VENUE_COLOR[v], mfc=VENUE_COLOR[v] if filled else SURFACE,
                        mec=VENUE_COLOR[v], mew=1.1, ls="none", zorder=4)
                if filled:
                    ax.annotate(nf(rt, 0 if rt >= 10 else (1 if rt >= 1 else 2)) + "×", (xx, rt), xytext=(-4, 0), textcoords="offset points",
                                ha="right", va="center", fontsize=6.3, color=INK2)
    ax.axhline(1.0, color=INK2, lw=1.0, ls="--", zorder=2)
    ax.text(len(PERF_VENUES) - 0.45, 1.0, L("reálný čas (1×)", "real time (1×)"), ha="right", va="bottom", fontsize=7, color=INK2)
    ax.set_yscale("log")
    logfmt(ax, "y")
    ax.set_xticks(range(len(PERF_VENUES)))
    ax.set_xticklabels([venue_name(v) for v in PERF_VENUES])
    ax.set_xlim(-0.6, len(PERF_VENUES) - 0.4)
    ax.grid(axis="x", visible=False)
    ax.set_ylabel(L("násobek reálného času", "real-time factor"))
    hs = [Line2D([], [], marker=IMPL_STYLE[k]["marker"], ms=5, color=INK2, mfc=INK2, ls="none", label=impl_label(i, t)) for k, (i, t) in enumerate(keys)]
    hs += [Line2D([], [], marker="o", ms=5, color=INK2, mfc=INK2, ls="none", label=L("plné: start", "filled: spawn")),
           Line2D([], [], marker="o", ms=5, color=INK2, mfc=SURFACE, ls="none", label=L("prázdné: zahlcení", "hollow: congested"))]
    ax.legend(handles=hs, loc="upper center", ncol=5, bbox_to_anchor=(0.5, 1.14), fontsize=7, handletextpad=0.3, columnspacing=1.0)
    fig.tight_layout()
    save(fig, out, "benchmark_realtime_factor")


def scaling_rows():
    files = sorted(glob.glob(PERF_SCALING))
    if not files:
        return None, None
    with open(files[-1], newline="") as f:
        rows = list(csv.DictReader(f))
    return rows, files[-1]


def fig17(out):
    rows, _ = scaling_rows()
    if not rows:
        return
    by = {}
    for r in rows:
        by.setdefault(int(r["threads"]), []).append(float(r["median_ms"]))
    th = sorted(by)
    med = {t: sorted(by[t])[len(by[t]) // 2] if len(by[t]) % 2 else 0.5 * (sorted(by[t])[len(by[t]) // 2 - 1] + sorted(by[t])[len(by[t]) // 2]) for t in th}
    base = med[1]
    venue = rows[0]["venue"]
    fig, (a1, a2) = plt.subplots(1, 2, figsize=(W, 2.9))
    col = VENUE_COLOR.get(venue, INK)
    a1.plot(th, [med[t] for t in th], color=col, lw=1.6, marker="o", ms=3.8, mfc=col, mec=SURFACE)
    a1.set_yscale("log")
    logfmt(a1, "y")
    a1.set_ylabel(L("čas jednoho kroku [ms]", "time per step [ms]"))
    a2.plot(th, th, color=MUTED, lw=1.0, ls="--")
    a2.text(th[-1], th[-1], L(" ideální", " ideal"), fontsize=7, color=INK2, va="center", ha="left")
    sp = [base / med[t] for t in th]
    a2.plot(th, sp, color=col, lw=1.6, marker="o", ms=3.8, mfc=col, mec=SURFACE)
    for t, s in zip(th, sp):
        if t in (6, 12, th[-1]):
            a2.annotate(nf(s, 1) + "×", (t, s), xytext=(0, -11), textcoords="offset points", ha="center", fontsize=6.5, color=INK2)
    a2.set_ylabel(L("zrychlení vůči 1 vláknu", "speedup over 1 thread"))
    a2.set_ylim(0, th[-1] * 1.05)
    for ax in (a1, a2):
        ax.axvline(12, color=AXIS, lw=1.0, ls=":")
        ax.text(12.3, 0.03 if ax is a2 else 0.97, L("12 vláken: všechna P-jádra (6 × 2)", "12 threads: all P-cores (6 × 2)"), transform=ax.get_xaxis_transform(),
                fontsize=6.5, color=INK2, va="bottom" if ax is a2 else "top", ha="left")
        ax.set_xlabel(L("vlákna OpenMP", "OpenMP threads"))
        ax.set_xticks(th)
        axfmt(ax, "x")
        if ax is a2:
            axfmt(ax, "y")
    panel_label(a1, L(f"stadion {venue}, 100 %, zahlcení", f"venue {venue}, 100%, congested"))
    fig.tight_layout()
    save(fig, out, "benchmark_cpu_thread_scaling")


def fig18(out):
    rows, _ = perf_rows()
    fig, (a1, a2) = plt.subplots(1, 2, figsize=(W, 3.3), gridspec_kw={"width_ratios": [1.15, 1.0]})
    stages = [k for k, _ in CHAIN] + ["current"]
    shades = {4096: BLUE_RAMP[4], 65536: BLUE_RAMP[8], 262144: BLUE_RAMP[12]}
    for n, colr in shades.items():
        xs, ys = [], []
        for i, (k, vals) in enumerate(CHAIN):
            if n in vals:
                xs.append(i); ys.append(vals[n][1])
        c = pcell(rows, f"terrace_{n}", "congested", "gpu") if rows else None
        if c:
            xs.append(len(CHAIN)); ys.append(c["round_median_ms"])
        a1.plot(xs[3:], ys[3:], color=colr, lw=1.0, ls=":", zorder=2)
        a1.plot(xs[4:], ys[4:], ls="none", marker="o", ms=3.8, mfc=SURFACE, mec=colr, mew=1.2, zorder=3)
        a1.plot(xs[:4], ys[:4], color=colr, lw=1.5, marker="o", ms=3.8, mfc=colr, mec=SURFACE, zorder=3)
        a1.annotate(f"N{NBSP}={NBSP}{nf(n)}", (xs[0], ys[0]), xytext=(-4, 0), textcoords="offset points", ha="right", va="center", fontsize=6.5, color=colr)
    a1.axvspan(-0.5, 3.5, color="#f4f3ee", zorder=0)
    a1.text(2.0, 0.98, L("historický model a ovladač", "historical model and driver"), transform=a1.get_xaxis_transform(), ha="center", va="top",
            fontsize=7, color=INK2)
    panel_label(a1, L("tribuna: krok GPU v optimalizacích", "terrace: the GPU step through the optimisations"))
    a1.set_xticks(range(len(stages)))
    a1.set_xticklabels([chain_label(k) for k in stages], rotation=35, ha="right", fontsize=6.5)
    a1.set_xlim(-1.6, len(stages) - 0.5)
    a1.set_yscale("log")
    logfmt(a1, "y")
    a1.grid(axis="x", visible=False)
    a1.set_ylabel(L("čas kroku GPU, tribuna, zahlcení [ms]", "GPU step time, terrace, congested [ms]"))
    if rows:   # (b) the current model's per-pass cost, congested
        series = [(f"terrace_{n}", L(f"tribuna N{NBSP}={NBSP}{nf(n)}", f"terrace N = {nf(n)}"), shades[n], "o") for n in (4096, 65536, 262144)]
        series += [(f"venue_{v}", venue_name(v), VENUE_COLOR[v], "s") for v in PERF_VENUES]
        for j, (wk, lab, colr, mk) in enumerate(series):
            c = pcell(rows, wk, "congested", "gpu")
            if not c:
                continue
            xs = [i + (j - 2.5) * 0.1 for i in range(len(PASSES)) if c[PASSES[i] + "_ms"] > 0]
            ys = [c[p + "_ms"] for p in PASSES if c[p + "_ms"] > 0]
            a2.plot(xs, ys, ls="none", marker=mk, ms=3.8, color=colr, mfc=colr, mec=SURFACE, mew=0.4, label=lab)
        a2.set_yscale("log")
        logfmt(a2, "y")
        a2.set_xticks(range(len(PASSES)))
        a2.set_xticklabels([pass_label(p) for p in PASSES], rotation=35, ha="right", fontsize=6.5)
        a2.grid(axis="x", visible=False)
        a2.set_ylabel(L("čas průchodu GPU, zahlcení [ms]", "GPU pass time, congested [ms]"))
        a2.legend(loc="upper left", fontsize=6.2, ncol=1, handletextpad=0.2)
        panel_label(a2, L("současný model: průchody", "current model: passes"))
    fig.tight_layout()
    save(fig, out, "benchmark_optimisation_chain")


FIGS = {1: fig1, 2: fig2, 3: fig3, 4: fig4, 5: fig5, 6: fig6, 7: fig7, 8: fig8, 9: fig9, 10: fig10, 11: fig11, 12: fig12,
        13: fig13, 14: fig14, 15: fig15, 16: fig16, 17: fig17, 18: fig18}
NAMES = {1: "evacuation_curves_by_venue", 2: "evacuation_time_vs_capacity", 3: "safety_load_vs_time_and_exposure", 4: "evacuation_nearest_vs_queue_aware", 5: "evacuation_exit_utilisation",
         6: "evacuation_gangway_saturation", 7: "safety_peak_density_maps", 8: "validation_fundamental_diagram", 9: "evacuation_walking_model_variants",
         10: "validation_stair_flow_diagram", 11: "evacuation_before_after_stair_calibration", 12: "validation_corridor_width_flow", 13: "benchmark_step_time_vs_agents", 14: "benchmark_speedup",
         15: "benchmark_gpu_pass_shares", 16: "benchmark_realtime_factor", 17: "benchmark_cpu_thread_scaling", 18: "benchmark_optimisation_chain"}


def run_prov(names, base=None):
    """(runs, 'commit (n runs), ...', 'driver; ...') of the runs of these names (the latest folder of each) in the matrix 'base'."""
    commits, drivers, n = {}, {}, 0
    for name in names:
        d = td.run_dir(name, base)
        if not d:
            continue
        m = td.load_summary(d)["meta"]
        c = m["git_commit"][:7] + ("" if str(m["git_dirty"]) == "0" else " dirty")
        commits[c] = commits.get(c, 0) + 1
        drivers[m.get("driver", "?")] = 1
        n += 1
    return n, ", ".join(f"{c} ({k} runs)" for c, k in sorted(commits.items())), "; ".join(sorted(drivers))


def harness_prov(folder):
    """'commit, driver' of a harness run (its summary.md's header line: commit `<sha>`, dirty 0, Release; <GPU>, <GL_VERSION>; <time>)."""
    try:
        with open(os.path.join(folder, "summary.md"), encoding="utf-8") as f:
            for line in f:
                if line.startswith("commit `"):
                    parts = line.split("; ")
                    commit = line.split("`")[1][:7] + ("" if "dirty 0" in parts[0] else " dirty")
                    gl = parts[1].split(", ", 1)[1] if len(parts) > 1 and ", " in parts[1] else "?"
                    return f"{commit}, {gl}"
    except OSError:
        pass
    return "?"


def write_readme(out):
    """README.md: one line per figure: what it shows, its runs (folder, count), the commit their binary was built at and the GPU driver."""
    case = lambda *keys: sum((td.CASES[k][2] for k in keys), [])
    m, m_before = td.MATRIX_DIR.replace(os.sep, "/"), td.MATRIX_DIR_BEFORE.replace(os.sep, "/")
    stair = {k: (sorted(glob.glob(p)) or [""])[-1].replace(os.sep, "/") for k, p in STAIR_RUNS.items()}
    narrow = [d.replace(os.sep, "/") for d in sorted(glob.glob(os.path.join(NARROW_DIR, "*_*"))) if os.path.isdir(d)]
    expo = "exposure to critical density (>= 5 persons/m^2; person-s) in circulation areas"
    all_cases = ("S_95", "S_100", "S_125", "S_150", "S_150gw", "S_nearest", "M_95", "M_100", "M_max", "M_nearest", "L_95", "L_100", "L_max", "L_nearest")
    figs = [
        (1, "% evacuated vs time, S / M / L at 100% (stair spacing EMPIRICAL, solid; CONSERVATIVE, dashed) and the terrace reference (N = 4096); dots: t100",
         case("terrace", "S_100", "M_100", "L_100", "S_cons", "M_cons", "L_cons"), []),
        (2, "t100 vs seats (log): 100% EMPIRICAL (filled) with the CONSERVATIVE upper marker (open triangle; the stair-flow bracket), the 95% runs' mean and "
            "min-max (3 seeds), t100 before the stair calibration (crosses: the level spacing, " + m_before + "), the capacity lower bound t_lb and the exit-width "
            "bound (bottleneck.json), the 8-minute planning reference",
         case("S_100", "M_100", "L_100", "S_cons", "M_cons", "L_cons", "S_95", "M_95", "L_95"), case("S_100", "M_100", "L_100")),
        (3, "t100 and the " + expo + " (log) vs the actual load: 95%, 100%, S 125% / 150%, M and L at their maximum achievable 121.4% / 109.3% "
            "(labelled), mean and min-max over 3 seeds; diamond: S 150% with standing also on the gangways, drawn 7 pt left of 150% so that it does not "
            "cover the S 150% marker (both cases are at 150% load)",
         case("S_95", "S_100", "S_125", "S_150", "S_150gw", "M_95", "M_100", "M_max", "L_95", "L_100", "L_max"), []),
        (4, "t100 and unused exit width per venue at 100%: queue-aware exit choice (default) vs nearest exit (both with the stair model)",
         case("S_100", "M_100", "L_100", "S_nearest", "M_nearest", "L_nearest"), []),
        (5, "doors / avenues share of the evacuated per venue at 100% against the exit width's split", case("S_100", "M_100", "L_100"), []),
        (6, "each gangway's saturated share of its active time (10 s windows, its catchment waiting, density >= LoS F), sorted; straight vs corner; S, M, L at 100%",
         case("S_100", "M_100", "L_100"), []),
        (7, "circulation-zone peak density maps (1 m cells of >= 0.5 m^2; seat rows grey; one colour scale; each panel at its venue's scale with a scale bar): "
            "S, M, L at 100% and L at the maximum achievable 109.3% (seed 1)", case("S_100", "M_100", "L_100") + [td.CASES["L_max"][2][0]], []),
        (8, "the model's level corridor fundamental diagram (3 m x 50 m, periodic; speed and specific flow vs density, seeds 7-9) against Weidmann (1993): "
            + FD_DIR.replace(os.sep, "/") + " (" + harness_prov(FD_DIR) + ")", [], []),
        (9, "S, M, L at 100%: t100 for {nearest, queue-aware} exit choice x {level walking speed, stairs = incline speed + EMPIRICAL stair spacing}",
         case("S_100", "S_nearest", "S_level", "S_nearest_level", "M_100", "M_nearest", "M_level", "M_nearest_level", "L_100", "L_nearest", "L_level", "L_nearest_level"), []),
        (10, "the stair harness (inclined periodic corridor at a gangway's 1.20 m, rake 0.5): specific flow vs density, ascending / descending, the level "
             "spacing (before the calibration, --stair-flow off) vs EMPIRICAL and CONSERVATIVE stair spacing, against the targets (Burghardt et al. 2013; "
             "Green Guide 2018): " + ", ".join(f"{stair[k]} ({harness_prov(stair[k])})" for k in ("base", "emp", "cons")), [], []),
        (11, "t100 of every case (mean over seeds): before the stair calibration (the level spacing, selected with --stair-flow off: " + m_before +
             ") vs after (EMPIRICAL), with the change; a before run that did not complete (M at 121.42%, seed 2: a counterflow gridlock on a corner "
             "gangway) is left out of its mean, which is marked with an asterisk and a note", case(*all_cases), case(*all_cases)),
        (12, "the level specific flow vs density in corridors 1.2, 2.4 and 3.0 m wide (wall to wall): the FD protocol with full-height walls and the stair "
             "harness's level corridor with low walls at the same centre spans (tools/fd/narrow_passage.sh): " + NARROW_DIR + " (" +
             "; ".join(sorted({harness_prov(d) for d in narrow})) + ")", [], []),
    ]
    perf, perf_file = perf_rows()
    scal, scal_file = scaling_rows()

    def bench_prov(rows, f):
        if not rows:
            return "(not yet run)"
        r = rows[0]
        c = r.get("git_commit", "?")[:7] + ("" if str(r.get("git_dirty", "0")) == "0" else " dirty")
        drv = ("driver " + r["driver"]) if r.get("driver") else "CPU only, no GPU work"
        return f"{f.replace(os.sep, '/')} (benchmark_crowd built at {c}, {drv})"
    perf_lines = [
        (13, "ms per step vs active agents (log-log) for the GPU, the CPU at max threads and the CPU at 1 thread: S, M, L at 100% load (constant density; "
             "filled markers in the venue colours) and the terrace's stress sweep (fixed venue, N = 1 024 .. 262 144; hollow, thin), spawn and congested "
             "(a venue's state at t50 of its 100% run; the terrace's after 250 steps). Median over rounds of the per-round medians", bench_prov(perf, perf_file)),
        (14, "speedups: GPU vs CPU at max threads and CPU at max threads vs 1 thread, per venue and per terrace N (spawn filled, congested hatched)",
         bench_prov(perf, perf_file)),
        (15, "the GPU passes' shares of the step (hash, sort, cells / gather, exit choice, predict, projection iterations, final pass), per venue and state, "
             "with the step's total ms above each bar", bench_prov(perf, perf_file)),
        (16, "the real-time factor (DT_real 174.9 ms / ms per step) per venue and implementation (filled: spawn, hollow: congested), the 1x line",
         bench_prov(perf, perf_file)),
        (17, "CPU thread scaling at M 100% congested: ms per step and the speedup over 1 thread vs OpenMP threads, the ideal line and the P-/E-core boundary "
             "at 12 threads (6 P-cores x 2)", bench_prov(scal, scal_file)),
        (18, "(a) the GPU step at the terrace (congested; N = 4 096 / 65 536 / 262 144) through the optimisations (buffers in VRAM, "
             "shared-memory sort, sorted gather), shaded: the historical model and driver (AMD 26.8.1; " + ", ".join(CHAIN_SOURCES[:3]) + "), then the "
             "hard-body model with the projection (AMD 26.8.1; " + CHAIN_SOURCES[3] + ") and the current model (this benchmark); (b) the current "
             "model's per-pass GPU cost (congested) for the terrace sweep and S, M, L", bench_prov(perf, perf_file)),
    ]
    drivers = set()
    for r in (perf or [])[:1] + (scal or [])[:1]:
        if r.get("driver"):
            drivers.add(r["driver"])
    for _, _, names, names_before in figs:
        for base, ns in ((None, names), (td.MATRIX_DIR_BEFORE, names_before)):
            if ns:
                drivers.update(x for x in run_prov(ns, base)[2].split("; ") if x)
    for d in [FD_DIR] + list(stair.values()) + narrow:
        drivers.add(harness_prov(d).split(", ", 1)[-1])
    lines = ["# Thesis figures (one GPU driver, one simulation code version)", "",
             "Generated by `python tools/figures/thesis_figures.py` (style, language and definitions in its header) from the experiment matrix "
             f"(`tools/experiment/thesis_matrix.sh`: runs under {m}/; the model before the stair calibration, selected by --stair-flow off, "
             f"runs under {m_before}/; GPU, every per-step check on), its bottleneck analysis (`tools/figures/bottleneck.py` -> {m}/bottleneck.json) and the "
             "harness runs named below. **cs/**: Czech (labels, legends, annotations; decimal comma, thin space as the thousands separator; no English "
             "words, no internal names); **en/**: English. The literature values they show are as reported in the cited sources, not yet checked against the "
             "originals (results/README.md). Each figure as PDF "
             "(vector, embedded fonts, for LaTeX), PNG (300 dpi) and SVG; 15 cm wide; subscripts by mathtext in the same face (t italic, the index "
             "upright); Linux Biolinum G (Libertinus Sans' parent face; Libertinus Sans is not installed); no titles baked in; tick labels never "
             "rounded (the script checks every numeric tick label against its location). Venue colours: S blue, M orange, L aqua, the terrace grey.",
             "",
             "**GPU driver of every run and harness result: " + "; ".join(sorted(drivers)) + "** (AMD Radeon RX 7800 XT). Each "
             "figure's line names its runs and the commit their binary (run_experiment / fd_harness) was built at; every such binary has the same "
             "simulation code (results/evacuation/code_version_proof). Commit IDs refer to the private development history; the public release is v1.0. "
             "Numbers: results/RESULTS.md.", ""]
    for k, what, names, names_before in figs:
        src = []
        if names:
            n, c, d = run_prov(names)
            src.append(f"{n} runs in {m}/ (" + ", ".join(sorted({x.rsplit('_s', 1)[0] if x[-3:-1] == '_s' else x for x in names})) + f"), built at {c}, driver {d}")
        if names_before:
            n, c, d = run_prov(names_before, td.MATRIX_DIR_BEFORE)
            src.append(f"{n} runs in {m_before}/, built at {c}, driver {d}")
        lines.append(f"- **{NAMES[k]}**: {what}." + (" Runs: " + "; ".join(src) + "." if src else ""))
    lines += ["", "Performance figures (benchmark_crowd thesis, results/benchmarks/thesis; numbers: results/RESULTS.md, 'Performance'):", ""]
    for k, what, src in perf_lines:
        lines.append(f"- **{NAMES[k]}**: {what}. Data: {src}.")
    with open(os.path.join(out, "README.md"), "w", encoding="utf-8") as f:
        f.write("\n".join(lines) + "\n")
    print("  ->", os.path.join(out, "README.md"))


def main():
    global LANG
    out = "results/figures"
    if "--out" in sys.argv:
        out = sys.argv[sys.argv.index("--out") + 1]
    only = [int(x) for x in sys.argv[sys.argv.index("--only") + 1].split(",")] if "--only" in sys.argv else list(FIGS)
    langs = sys.argv[sys.argv.index("--lang") + 1].split(",") if "--lang" in sys.argv else ["cs", "en"]
    mode = sys.argv[sys.argv.index("--verify") + 1] if "--verify" in sys.argv else "off"
    verifies = {"both": [False, True], "on": [True], "off": [False]}[mode]
    print("font:", FONT)
    global VERIFY
    for lang in langs:
        LANG = lang
        for ver in verifies:
            VERIFY = ver
            folder = os.path.join(out, lang + ("_draft" if ver else ""))
            for k in only:
                print(f"figure {k} ({lang}{', draft' if ver else ''})")
                FIGS[k](folder)
    LANG = "en"
    write_readme(out)
    print("tick labels:", "every numeric tick label equals its location" if not TICK_PROBLEMS else f"{len(TICK_PROBLEMS)} ROUNDED:")
    for t in TICK_PROBLEMS:
        print("  ", t)
    if TICK_PROBLEMS:
        sys.exit(1)


if __name__ == "__main__":
    main()
