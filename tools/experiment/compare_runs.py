"""compare_runs.py: one comparison table (markdown) of run_experiment runs from their summary.json files.

  python tools/experiment/compare_runs.py <run folder> [more run folders...] [--labels a,b,...] > table.md

Per run: model, t50 / t90 / t100 [s], evacuated through the doors / the avenues, unused exit width, mean door / avenue specific flow
(mean over the exits used of their mean flows) and the highest peak flow, circulation peak density (all circulation; gangways),
crush exposure (circulation; seat rows apart), the top circulation hotspot, INV-row row changes, plausibility (overlap p99 / max over
all pair-steps), the exit choice's switches.
"""
import json
import math
import os
import sys


def load(run_dir):
    with open(os.path.join(run_dir, "summary.json")) as f:
        return json.load(f)


def num(v, fmt="%.1f"):
    return "-" if v is None or (isinstance(v, float) and math.isnan(v)) else fmt % v


def row(run_dir, label):
    s = load(run_dir)
    m, ev, u = s["meta"], s["evacuation"], s["exit_utilisation"]
    door = [e for e in s["exits"] if e["exit"].startswith("door") and e.get("mean_flow_p_per_m_min") is not None and e["evacuated"] > 0]
    avenue = [e for e in s["exits"] if e["exit"] in ("+x", "-x", "+y", "-y") and e.get("mean_flow_p_per_m_min") is not None and e["evacuated"] > 0]
    mean = lambda xs: sum(xs) / len(xs) if xs else float("nan")
    circ, rows = s.get("circulation") or {}, s.get("seat_rows") or {}
    gang = next((z for z in s["zones"] if z["zone"] == "gangway"), {})
    hot = s["hotspots"][0] if s["hotspots"] else None
    ch = s.get("checks", {})
    return {
        "label": label or m["name"],
        "model": m.get("model", ""),
        "engine": m["engine"] + ("" if m.get("dt_div", 1) == 1 else " DT/%d" % m["dt_div"]),
        "agents": m["initially_active"],
        "t": "%s / %s / %s" % (num(ev["t50_s"]), num(ev["t90_s"]), num(ev["t100_s"])),
        "t100": ev["t100_s"],
        "doors": "%d (%s%%)" % (u["doors_evacuated"], num(100 * u["doors_share"], "%.0f")),
        "avenues": "%d (%s%%)" % (u["avenues_evacuated"], num(100 * u["avenues_share"], "%.0f")),
        "unused": "%s m (%s%%)" % (num(u["unused_exit_width_m"]), num(100 * u["unused_exit_width_fraction"], "%.0f")),
        "door_flow": "%s / %s" % (num(mean([e["mean_flow_p_per_m_min"] for e in door])), num(max([e["peak_flow_p_per_m_min"] for e in door], default=float("nan")))),
        "avenue_flow": "%s / %s" % (num(mean([e["mean_flow_p_per_m_min"] for e in avenue])), num(max([e["peak_flow_p_per_m_min"] for e in avenue], default=float("nan")))),
        "peak": "%s / %s" % (num(circ.get("peak_density_p_m2"), "%.2f"), num(gang.get("peak_density_p_m2"), "%.2f")),
        "exposure": "%s / %s" % (num(circ.get("exposure_person_s"), "%.0f"), num(rows.get("exposure_person_s"), "%.0f")),
        "hotspot": "%s (%s, %s) m %s person-s" % (hot["zone"], num(hot["x_m"]), num(hot["y_m"]), num(hot["exposure_person_s"], "%.0f")) if hot else "-",
        "invrow": str(s["inv_row"].get("row_changes", s["inv_row"].get("row_changes_bypassing_aisles", "-"))),
        "plaus": ("PASS" if ch.get("plausibility_pass") else "FAIL") + " (%s / %s)" % (num(ch.get("overlap_all_p99"), "%.4f"), num(ch.get("overlap_all_max"), "%.4f")) if ch else "-",
        "switches": str(m.get("choice_switches", "-")),
        "dir": os.path.basename(os.path.normpath(run_dir)),
    }


COLUMNS = [("label", "run"), ("engine", "engine"), ("agents", "agents"), ("t", "t50 / t90 / t100 [s]"), ("doors", "doors"), ("avenues", "avenues"),
           ("unused", "unused exit width"), ("door_flow", "door flow mean / peak [p/(m min)]"), ("avenue_flow", "avenue flow mean / peak [p/(m min)]"),
           ("peak", "peak density circulation / gangways [p/m^2]"), ("exposure", "crush exposure circulation / seat rows [person-s]"),
           ("hotspot", "top circulation hotspot"), ("invrow", "INV-row"), ("plaus", "plausibility (overlap p99 / max)"), ("switches", "switches")]


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--labels")]
    labels = []
    for a in sys.argv[1:]:
        if a.startswith("--labels"):
            labels = a.split("=", 1)[1].split(",")
    if not args:
        sys.exit(__doc__)
    rows = [row(d, labels[i] if i < len(labels) else None) for i, d in enumerate(args)]
    print("| " + " | ".join(h for _, h in COLUMNS) + " |")
    print("|" + "---|" * len(COLUMNS))
    for r in rows:
        print("| " + " | ".join(str(r[k]) for k, _ in COLUMNS) + " |")
    print()
    for r in rows:
        print("- %s: `%s` (%s)" % (r["label"], r["dir"], r["model"]))


if __name__ == "__main__":
    main()
