"""driver_effect.py: the GPU driver's effect on every re-run experiment.

Each run of the single-driver matrix (AMD 26.10.1.261008; results/evacuation/matrix and matrix_before_calibration, tools/experiment/thesis_matrix.sh)
against the same run on the old driver (26.8.1.260810; results/evacuation/history_amd_26.8.1). The calibrated model's runs (matrix: the terrace, S
and M): the same binary's simulation code, the same spawn, model and seed. The model before the calibration (matrix_before_calibration, the level
spacing on the gangways, --stair-flow off): cd8e0bb's program, the same program bit for bit (GOLDEN_*_LEVEL_SPACING). Only the driver differs (for the
model before the calibration also the code version). Writes <out>/driver_effect.md and driver_effect.csv.

  python tools/figures/driver_effect.py [--out results/evacuation/matrix]
"""
import csv
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import thesis_data as td  # noqa: E402

MATRIX, BEFORE = "results/evacuation/matrix", "results/evacuation/matrix_before_calibration"
OLD_MATRIX, OLD_BEFORE = "results/evacuation/history_amd_26.8.1/matrix", "results/evacuation/history_amd_26.8.1/matrix_before_calibration"
MODEL_CALIBRATED, MODEL_BEFORE = "calibrated stair spacing", "level spacing on the gangways (the model before the calibration)"


def driver_of(d):
    m = td.load_summary(d)["meta"]
    return m.get("driver", "?")


def pairs():
    """(model label, run name, old dir, new dir) of every run that exists on both drivers."""
    out = []
    names = sorted({n for k, c in td.CASES.items() for n in c[2]})
    for name in names:
        old, new = td.run_dir(name, OLD_MATRIX), td.run_dir(name, MATRIX)
        if old and new and "26.8.1" in driver_of(old) and "26.10.1" in driver_of(new):
            out.append((MODEL_CALIBRATED, name, old, new))
    names_before = sorted({n for k in td.CASES for n in td.CASES[k][2] if not any(n.endswith(s) for s in ("_conservative", "_level", "_dt2"))})
    for name in names_before:
        if name.startswith("terrace"):
            continue
        old, new = td.run_dir(name, OLD_BEFORE), td.run_dir(name, BEFORE)
        if old and new and "26.8.1" in driver_of(old) and "26.10.1" in driver_of(new):
            out.append((MODEL_BEFORE, name, old, new))
    return out


def main():
    out = sys.argv[sys.argv.index("--out") + 1] if "--out" in sys.argv else MATRIX
    rows = []
    for model, name, old, new in pairs():
        a, b = td.run_metrics(old), td.run_metrics(new)
        ch = lambda k: 100.0 * (b[k] / a[k] - 1.0) if a[k] else float("nan")
        rows.append({"model": model, "run": name, "venue": b["venue"], "agents": b["agents"], "seed": b["seed"],
                     "old_dir": old.replace(os.sep, "/"), "old_commit": a["commit"][:7], "new_dir": new.replace(os.sep, "/"), "new_commit": b["commit"][:7],
                     "t50_old": a["t50"], "t50_new": b["t50"], "t50_change_pct": ch("t50"), "t90_old": a["t90"], "t90_new": b["t90"],
                     "t90_change_pct": ch("t90"), "t100_old": a["t100"], "t100_new": b["t100"], "t100_change_pct": ch("t100"),
                     "pause_old": a["max_pause_s"], "pause_new": b["max_pause_s"], "checks_old": a["checks_pass"], "checks_new": b["checks_pass"]})
    os.makedirs(out, exist_ok=True)
    with open(os.path.join(out, "driver_effect.csv"), "w", newline="") as f:
        w = csv.DictWriter(f, fieldnames=list(rows[0].keys()) if rows else ["run"])
        w.writeheader()
        for r in rows:
            w.writerow(r)
    md = ["# The GPU driver's effect", "",
          "Every run of the single-driver matrix on AMD 26.10.1.261008 against the same run (name, spawn, seed, model) on 26.8.1.260810. "
          "The calibrated model: the same simulation code (run_experiment at 49b5a27 on the old driver, at the new driver's commit in summary.json; the same GLSL and simulation C++): "
          "only the driver differs. The model before the calibration: cd8e0bb's level spacing, here selected with --stair-flow off (the same program bit for bit: "
          "GOLDEN_*_LEVEL_SPACING). Times in seconds; change = new / old - 1. tools/figures/driver_effect.py; the CSV beside it.", ""]
    for model in (MODEL_CALIBRATED, MODEL_BEFORE):
        sel = [r for r in rows if r["model"] == model]
        if not sel:
            continue
        md += [f"## {model}", "", "| run | agents | t50 old / new | t90 old / new | t100 old -> new | change | longest pause in evacuations old / new [s] | checks old / new |",
               "|---|---:|---|---|---:|---:|---|---|"]
        for r in sel:
            fin = r["t100_new"] == r["t100_new"]   # not NaN: the run completed
            md.append(f"| {r['run']} | {r['agents']:,} |".replace(",", " ") + f" {r['t50_old']:.1f} / {r['t50_new']:.1f} | {r['t90_old']:.1f} / {r['t90_new']:.1f} | " +
                      (f"{r['t100_old']:.1f} -> {r['t100_new']:.1f} | {r['t100_change_pct']:+.2f}%" if fin else
                       f"{r['t100_old']:.1f} -> **did not complete** (gridlock) | -") +
                      f" | {r['pause_old']:.1f} / {r['pause_new']:.1f} | {'PASS' if r['checks_old'] else 'FAIL'} / {'PASS' if r['checks_new'] else 'FAIL (incomplete)'} |"
                      .replace(",", " "))
        ch = [r["t100_change_pct"] for r in sel if r["t100_change_pct"] == r["t100_change_pct"]]
        ab = [abs(x) for x in ch]
        md += ["", f"t100 change over the {len(ch)} completed of {len(sel)} runs: mean {sum(ch) / len(ch):+.2f}%, mean |change| {sum(ab) / len(ab):.2f}%, range "
                   f"{min(ch):+.2f}% .. {max(ch):+.2f}%; t50 {min(r['t50_change_pct'] for r in sel):+.2f}% .. {max(r['t50_change_pct'] for r in sel):+.2f}%, "
                   f"t90 {min(r['t90_change_pct'] for r in sel):+.2f}% .. {max(r['t90_change_pct'] for r in sel):+.2f}%.", ""]
    with open(os.path.join(out, "driver_effect.md"), "w", encoding="utf-8") as f:
        f.write("\n".join(md) + "\n")
    print("->", os.path.join(out, "driver_effect.md"), len(rows), "pairs")


if __name__ == "__main__":
    main()
