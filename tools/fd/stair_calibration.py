"""stair_calibration.py: the stair spacing's calibration table from stair-harness grid runs.

  python tools/fd/stair_calibration.py <folder with grid runs> [--out <md>]

Every subfolder is one `fd_harness stair --t-up T --t-down T` run (ring mode): its summary.md names the grid point, its stair.csv holds
the diagram. Per run and direction: the maximum sustained flow (the largest J over the density grid) and the density where it lies; then,
per direction and target (EMPIRICAL, CONSERVATIVE; values as reported in the cited sources, not yet checked against the originals), the time gap at which the
maximum crosses the target (linear interpolation between the bracketing grid points; the maximum falls monotonically with T).
"""
import csv
import glob
import os
import re
import sys

TARGETS = {"EMPIRICAL": {"up": 1.22, "down": 1.25}, "CONSERVATIVE": {"up": 66.0 / 60.0, "down": 66.0 / 60.0}}


def runs(folder):
    out = []
    for d in sorted(glob.glob(os.path.join(folder, "*"))):
        sm, sc = os.path.join(d, "summary.md"), os.path.join(d, "stair.csv")
        if not (os.path.exists(sm) and os.path.exists(sc)):
            continue
        text = open(sm, encoding="utf-8").read()
        m = re.search(r"T_stair up ([0-9.]+) s, down ([0-9.]+) s", text)
        if not m:
            continue
        peak = {}
        for r in csv.DictReader(open(sc)):
            j = float(r["flow_p_m_s"])
            if r["dir"] not in peak or j > peak[r["dir"]][0]:
                peak[r["dir"]] = (j, float(r["rho_p_m2"]), float(r["max_overlap_body_diam"]))
        out.append((float(m.group(1)), float(m.group(2)), os.path.basename(d), peak))
    return out


def crossing(points, target):
    """points: [(T, J)] sorted by T; the T where J crosses target (None outside the range)."""
    for (t0, j0), (t1, j1) in zip(points, points[1:]):
        if (j0 - target) * (j1 - target) <= 0 and j0 != j1:
            return t0 + (target - j0) * (t1 - t0) / (j1 - j0)
    return None


def main(argv):
    if not argv:
        print(__doc__)
        return 2
    folder = argv[0]
    outPath = argv[argv.index("--out") + 1] if "--out" in argv else os.path.join(folder, "calibration.md")
    rs = runs(folder)
    lines = ["# Stair spacing calibration grid (" + folder.replace("\\", "/") + ")", "",
             "Maximum sustained flow (the largest specific flow of the ring's diagram, mean of the seeds) per grid point and direction.", "",
             "| T_stair [s] | up: max J [p/(m s)] | at rho | down: max J | at rho | run |", "|---:|---:|---:|---:|---:|---|"]
    for tu, td, name, pk in sorted(rs):
        u, d = pk.get("up", (float("nan"),) * 3), pk.get("down", (float("nan"),) * 3)
        lines.append(f"| {tu:.3f} / {td:.3f} | {u[0]:.3f} | {u[1]:.2f} | {d[0]:.3f} | {d[1]:.2f} | {name} |")
    lines += ["", "| target | direction | target J [p/(m s)] | T at the crossing [s] |", "|---|---|---:|---:|"]
    for tg, vals in TARGETS.items():
        for dr in ("up", "down"):
            pts = sorted(((tu if dr == "up" else td), pk[dr][0]) for tu, td, _, pk in rs if dr in pk)
            t = crossing(pts, vals[dr])
            lines.append(f"| {tg} | {dr} | {vals[dr]:.3f} | {'-' if t is None else f'{t:.3f}'} |")
    open(outPath, "w", encoding="utf-8").write("\n".join(lines) + "\n")
    print("\n".join(lines))
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
