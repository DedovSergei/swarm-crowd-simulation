"""plot_heatmap.py: top-down maps of an experiment's heatmap.csv, one PNG per metric.

  python tools/experiment/plot_heatmap.py <run folder with a heatmap.csv> [more run folders...]

Writes into each run folder:
  map_<metric>.png        one map per heatmap.csv column (1 m x 1 m floor cells, x and y in metres): peak density
                          (colour bar ticks at the LoS E / LoS F / crush thresholds), time at or above each threshold,
                          occupied time, mean speed when occupied, exposure, person-seconds, walkable area, and the zones;
  evacuation_by_exit.png  cumulative evacuated per exit over real time (timeseries.csv);
  Seated venues (heatmap.csv has the column 'scope'): map_<metric>_circulation.png for the peak density, the time at or
                          above the crush threshold and the crush exposure over the CIRCULATION zones only (gangways, walkway,
                          concourse, avenues, exits), the seat rows' clearways drawn apart in a neutral grey (single-file queues:
                          their area-normalised density is not comparable with Fruin's thresholds), on the colour scale of the
                          circulation cells.
Cells without walkable floor are left blank (chart surface); walkable cells where the metric is 0 (or never occupied,
for the mean speed) are light grey, so "nothing happened here" is distinct from "no floor here".
"""
import csv
import os
import sys

import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt  # noqa: E402
import numpy as np  # noqa: E402
from matplotlib.colors import LinearSegmentedColormap, ListedColormap  # noqa: E402
from matplotlib.patches import Patch  # noqa: E402

# The figures' palette (light mode): chrome, one-hue sequential ramp, fixed categorical order
SURFACE, INK, INK2, MUTED, HAIR = "#fcfcfb", "#0b0b0b", "#52514e", "#898781", "#e1e0d9"
ZERO = "#e1e0d9"
SEAT_ROWS = "#b4b2a9"   # the seat rows on the circulation maps (neutral, darker than ZERO)
BLUE_RAMP = ["#b7d3f6", "#9ec5f4", "#86b6ef", "#6da7ec", "#5598e7", "#3987e5", "#2a78d6", "#256abf", "#1c5cab",
             "#184f95", "#104281", "#0d366b"]
CATEGORICAL = ["#2a78d6", "#eb6834", "#1baf7a", "#eda100", "#e87ba4", "#008300", "#4a3aa7", "#e34948"]
ZONES = ["tread", "aisle", "walkway", "avenue", "pitch", "exit", "concourse"]   # metrics::Zone order (+ run_experiment's concourse split)
THRESHOLDS = [(1.08, "LoS E 1.08"), (2.17, "LoS F 2.17"), (5.0, "crush 5")]

GRID_RES, GRID_MIN_M, CELL_M = 64, -32.0, 1.0   # swarm/metrics.hpp
EXTENT = [GRID_MIN_M, GRID_MIN_M + GRID_RES * CELL_M, GRID_MIN_M, GRID_MIN_M + GRID_RES * CELL_M]

METRICS = [   # column, title, unit
    ("peak_density_p_m2", "Peak density", "persons/m²"),
    ("time_above_los_e_s", "Time at or above LoS E (1.08 persons/m²)", "s"),
    ("time_above_los_f_s", "Time at or above LoS F (2.17 persons/m²)", "s"),
    ("time_above_crush_s", "Time at or above the crush threshold (5 persons/m²)", "s"),
    ("occupied_s", "Occupied time", "s"),
    ("mean_speed_occupied_m_s", "Mean speed when occupied (person-time weighted)", "m/s"),
    ("exposure_person_s", "Crush exposure (person-seconds at >= 5 persons/m²)", "person-s"),
    ("person_s", "Person-seconds spent in the cell", "person-s"),
    ("walkable_m2", "Walkable floor area per 1 m cell", "m²"),
]


def style_axes(ax):
    ax.set_facecolor(SURFACE)
    for s in ax.spines.values():
        s.set_color(HAIR)
    ax.tick_params(colors=MUTED, labelsize=8)
    ax.set_xlabel("x [m]", color=INK2, fontsize=9)
    ax.set_ylabel("y [m]", color=INK2, fontsize=9)


def title(fig, ax, text, run):
    ax.set_title(text, loc="left", color=INK, fontsize=11, pad=18)
    ax.text(0.0, 1.01, run, transform=ax.transAxes, color=MUTED, fontsize=8, va="bottom")


CIRCULATION_METRICS = ["peak_density_p_m2", "time_above_crush_s", "exposure_person_s"]


def read_cells(path):
    with open(path, newline="") as f:
        rows = list(csv.DictReader(f))
    grids = {}
    scope = None
    if rows and "scope" in rows[0]:   # circulation | seat_row | other per cell
        scope = np.full((GRID_RES, GRID_RES), "", dtype=object)
        for r in rows:
            scope[int(r["iy"]), int(r["ix"])] = r["scope"]
    for col, _, _ in METRICS:
        g = np.full((GRID_RES, GRID_RES), np.nan)
        for r in rows:
            v = r[col]
            g[int(r["iy"]), int(r["ix"])] = float(v) if v != "" else 0.0   # never occupied: shown as zero
        grids[col] = g
    zone = np.full((GRID_RES, GRID_RES), np.nan)
    for r in rows:
        zone[int(r["iy"]), int(r["ix"])] = ZONES.index(r["zone"])
    return grids, zone, scope


def plot_metric(run_dir, run, col, label, unit, g, scope=None):
    fig, ax = plt.subplots(figsize=(7.2, 6.4), dpi=150, facecolor=SURFACE)
    style_axes(ax)
    rows = None
    if scope is not None:   # the circulation cells only; the seat rows in neutral grey, the rest blank
        rows = scope == "seat_row"
        g = np.where(scope == "circulation", g, np.nan)
        ax.imshow(np.where(rows, 1.0, np.nan), origin="lower", extent=EXTENT, cmap=ListedColormap([SEAT_ROWS]), vmin=0, vmax=1,
                  interpolation="nearest")
    floor = ~np.isnan(g)
    zero = floor & (g <= 0)
    # zero-valued walkable cells in light grey, positive values on the one-hue ramp, no floor left blank
    ax.imshow(np.where(zero, 1.0, np.nan), origin="lower", extent=EXTENT, cmap=ListedColormap([ZERO]), vmin=0, vmax=1,
              interpolation="nearest")
    pos = np.where(floor & (g > 0), g, np.nan)
    vmax = np.nanmax(pos) if np.any(~np.isnan(pos)) else 1.0
    im = ax.imshow(pos, origin="lower", extent=EXTENT, cmap=LinearSegmentedColormap.from_list("seq", BLUE_RAMP), vmin=0, vmax=vmax,
                   interpolation="nearest")
    cb = fig.colorbar(im, ax=ax, fraction=0.046, pad=0.03)
    cb.set_label(unit, color=INK2, fontsize=9)
    cb.ax.tick_params(colors=MUTED, labelsize=8)
    cb.outline.set_edgecolor(HAIR)
    if col == "peak_density_p_m2":
        for v, name in THRESHOLDS:
            if v <= vmax:
                cb.ax.axhline(v, color=INK, linewidth=1)
                cb.ax.text(-0.15, v, name, transform=cb.ax.get_yaxis_transform(), ha="right", va="center", color=INK2, fontsize=7)
    handles = [Patch(facecolor=ZERO, edgecolor=HAIR, label="walkable, 0"), Patch(facecolor=SURFACE, edgecolor=HAIR, label="no floor")]
    if scope is not None:
        title(fig, ax, "%s, circulation zones [%s]" % (label, unit), run)
        handles.insert(0, Patch(facecolor=SEAT_ROWS, edgecolor=HAIR, label="seat rows: single-file queues, not comparable"))
    else:
        title(fig, ax, "%s [%s]" % (label, unit), run)
    ax.legend(handles=handles, loc="lower left", fontsize=7, frameon=True, facecolor=SURFACE, edgecolor=HAIR, labelcolor=INK2)
    fig.tight_layout()
    out = os.path.join(run_dir, "map_%s%s.png" % (col, "_circulation" if scope is not None else ""))
    fig.savefig(out, facecolor=SURFACE)
    plt.close(fig)
    return out


def plot_zones(run_dir, run, zone):
    fig, ax = plt.subplots(figsize=(7.2, 6.4), dpi=150, facecolor=SURFACE)
    style_axes(ax)
    ax.imshow(zone, origin="lower", extent=EXTENT, cmap=ListedColormap(CATEGORICAL[:len(ZONES)]), vmin=-0.5, vmax=len(ZONES) - 0.5,
              interpolation="nearest")
    # Six categories exceed the palette's all-pairs-safe three: every zone also carries a direct label. Zones are
    # labelled smallest first, each at its cell farthest from any other zone or blank cell, among those at least
    # LABEL_GAP_M from the labels already placed (ties: farthest from them)
    LABEL_GAP_M = 8.0
    placed = []
    blank_y, blank_x = np.nonzero(np.isnan(zone))
    for k in sorted(range(len(ZONES)), key=lambda q: np.count_nonzero(zone == q)):
        iy, ix = np.nonzero(zone == k)
        if len(ix) == 0:
            continue
        oy, ox = np.nonzero(zone != k)
        oy, ox = np.concatenate([oy, blank_y]), np.concatenate([ox, blank_x])
        d = np.array([np.min((ox - x) ** 2 + (oy - y) ** 2) for x, y in zip(ix, iy)])
        xs, ys = GRID_MIN_M + (ix + 0.5) * CELL_M, GRID_MIN_M + (iy + 0.5) * CELL_M
        gap = np.array([min([np.hypot(x - px, y - py) for px, py in placed] or [1e9]) for x, y in zip(xs, ys)])
        order = sorted(range(len(ix)), key=lambda q: (gap[q] < LABEL_GAP_M, -d[q], -gap[q], -iy[q], ix[q]))
        x, y = xs[order[0]], ys[order[0]]
        placed.append((x, y))
        ax.annotate(ZONES[k], (x, y), color=INK, fontsize=8, ha="center", va="center",
                    bbox=dict(boxstyle="round,pad=0.2", facecolor=SURFACE, edgecolor=HAIR, linewidth=0.8))
    title(fig, ax, "Zones (majority zone of each cell's walkable floor)", run)
    ax.legend(handles=[Patch(facecolor=CATEGORICAL[k], label=z) for k, z in enumerate(ZONES)], loc="center left", bbox_to_anchor=(1.02, 0.5),
              fontsize=8, frameon=False, labelcolor=INK2)
    fig.tight_layout()
    out = os.path.join(run_dir, "map_zone.png")
    fig.savefig(out, facecolor=SURFACE)
    plt.close(fig)
    return out


def plot_exits(run_dir, run):
    path = os.path.join(run_dir, "timeseries.csv")
    if not os.path.exists(path):
        return None
    with open(path, newline="") as f:
        rows = list(csv.DictReader(f))
    t = np.array([float(r["t_real_s"]) for r in rows])
    exits = [("cum_evacuated_pos_x", "+x"), ("cum_evacuated_neg_x", "-x"), ("cum_evacuated_pos_y", "+y"), ("cum_evacuated_neg_y", "-y")]
    doors = [c for c in rows[0].keys() if c.startswith("cum_evacuated_door_")]
    if doors:   # a seated venue: its concourse doors, the 4 avenues as one line
        for r in rows:
            r["cum_evacuated_avenues"] = str(sum(float(r[c]) for c, _ in exits))
        exits = [(c, "door " + c[len("cum_evacuated_door_"):].replace("_", " ")) for c in doors] + [("cum_evacuated_avenues", "avenues (4)")]
    fig, ax = plt.subplots(figsize=(7.2, 4.2), dpi=150, facecolor=SURFACE)
    ax.set_facecolor(SURFACE)
    for s in ("top", "right"):
        ax.spines[s].set_visible(False)
    for s in ("left", "bottom"):
        ax.spines[s].set_color(HAIR)
    ax.grid(axis="y", color=HAIR, linewidth=0.6)
    ax.set_axisbelow(True)
    ax.tick_params(colors=MUTED, labelsize=8)
    ends = []
    for k, (col, name) in enumerate(exits):
        y = np.array([float(r[col]) for r in rows])
        ax.plot(t, y, color=CATEGORICAL[k] if k < len(CATEGORICAL) else MUTED, linewidth=2, label="exit %s" % name)
        ends.append((y[-1], k, "%s %d" % (name, y[-1])))
    # direct end labels, nudged apart vertically so they never overlap (sorted by value, min gap 4% of the range)
    top = max(e[0] for e in ends) or 1.0
    gap, last = 0.04 * top, -1e9
    for v, k, text in sorted(ends):
        pos = max(v, last + gap)
        last = pos
        ax.annotate(text, (t[-1], v), xytext=(t[-1] * 1.01, pos), textcoords="data", color=INK2, fontsize=8, va="center")
    ax.set_xlabel("time [s]", color=INK2, fontsize=9)
    ax.set_ylabel("evacuated (cumulative)", color=INK2, fontsize=9)
    ax.set_ylim(bottom=0)
    ax.set_xlim(left=0, right=t[-1] * 1.12)
    ax.legend(loc="upper left", fontsize=8, frameon=False, labelcolor=INK2)
    ax.set_title("Evacuated per exit", loc="left", color=INK, fontsize=11, pad=16)
    ax.text(0.0, 1.01, run, transform=ax.transAxes, color=MUTED, fontsize=8, va="bottom")
    fig.tight_layout()
    out = os.path.join(run_dir, "evacuation_by_exit.png")
    fig.savefig(out, facecolor=SURFACE)
    plt.close(fig)
    return out


def main():
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    for run_dir in sys.argv[1:]:
        run = os.path.basename(os.path.normpath(run_dir))
        grids, zone, scope = read_cells(os.path.join(run_dir, "heatmap.csv"))
        outs = [plot_metric(run_dir, run, col, label, unit, grids[col]) for col, label, unit in METRICS]
        if scope is not None:   # the headline maps over the circulation zones
            outs += [plot_metric(run_dir, run, col, label, unit, grids[col], scope) for col, label, unit in METRICS if col in CIRCULATION_METRICS]
        outs.append(plot_zones(run_dir, run, zone))
        e = plot_exits(run_dir, run)
        if e:
            outs.append(e)
        print("%s: %d figures" % (run_dir, len(outs)))


if __name__ == "__main__":
    main()
