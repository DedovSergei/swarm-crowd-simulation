"""thesis_data.py: the experiment matrix's runs and their metrics, shared by matrix_table.py, bottleneck.py and thesis_figures.py. Run the scripts
from the repository root.

The matrix (tools/experiment/thesis_matrix.sh) writes one folder per run, <matrix>/<name>_<yyyymmdd_hhmm>; a name may have several folders (a
re-run): the latest counts. CASES maps each case to its runs' names. MATRIX_DIR is the matrix the scripts report (default results/evacuation/matrix,
the stair spacing EMPIRICAL; env MATRIX_DIR); MATRIX_DIR_BEFORE is the matrix before the stair calibration (default
results/evacuation/matrix_before_calibration, --stair-flow off: the level spacing on the gangways; env MATRIX_DIR_BEFORE), for the before / after
tables.
"""
import csv
import glob
import json
import math
import os

MATRIX_DIR_BEFORE = os.environ.get("MATRIX_DIR_BEFORE", "results/evacuation/matrix_before_calibration")
MATRIX_DIR = os.environ.get("MATRIX_DIR", "results/evacuation/matrix")
SEEDS = (1, 2, 3)
VENUES = ("S", "M", "L")

# Case key -> (venue, label, run names). M and L cannot take 125% or 150% (the standing floor's cap): the 150% request's runs are the
# achievable maximum for both requests (results/safety/overcrowding.md: the same spawns).
CASES = {"terrace": ("terrace", "terrace, N = 4096", ["terrace_n4096"])}
for v in VENUES:
    CASES[v + "_100"] = (v, "100%", [v + "_load100"])
    CASES[v + "_95"] = (v, "95% (3 seeds)", [f"{v}_load95_s{s}" for s in SEEDS])
    if v == "S":
        CASES["S_125"] = ("S", "125% (3 seeds)", [f"S_load125_s{s}" for s in SEEDS])
        CASES["S_150"] = ("S", "150% (3 seeds)", [f"S_load150_s{s}" for s in SEEDS])
        CASES["S_150gw"] = ("S", "150%, standing also on the gangways (3 seeds)", [f"S_load150_gangways_s{s}" for s in SEEDS])
    else:
        CASES[v + "_max"] = (v, "125% / 150% requested: the achievable maximum (3 seeds)", [f"{v}_load150_s{s}" for s in SEEDS])
    CASES[v + "_nearest"] = (v, "100%, nearest exit", [v + "_load100_nearest"])
    CASES[v + "_cons"] = (v, "100%, CONSERVATIVE stair spacing", [v + "_load100_conservative"])
    CASES[v + "_level"] = (v, "100%, queue-aware, level walking speed", [v + "_load100_level"])   # the walking-model variants
    CASES[v + "_nearest_level"] = (v, "100%, nearest exit, level walking speed", [v + "_load100_nearest_level"])
CASES["M_dt2"] = ("M", "100%, DT / 2", ["M_load100_dt2"])   # DT convergence


def run_dir(name, base=None):
    """The latest folder of a run name in the matrix 'base' (default MATRIX_DIR; None if it has not run)."""
    found = sorted(d for d in glob.glob(os.path.join(base or MATRIX_DIR, name + "_*")) if os.path.isdir(d) and
                   os.path.basename(d)[len(name) + 1:].replace("_", "").isdigit())
    return found[-1] if found else None


def load_summary(d):
    with open(os.path.join(d, "summary.json")) as f:
        return json.load(f)


def load_csv(d, name):
    with open(os.path.join(d, name), newline="") as f:
        return list(csv.DictReader(f))


def num(v):
    return float("nan") if v is None else float(v)


def run_metrics(d):
    """The per-run metrics, from summary.json (and gangway flows)."""
    s = load_summary(d)
    m, ev, u = s["meta"], s["evacuation"], s["exit_utilisation"]
    seated = s.get("spawn") is not None
    circ = s.get("circulation") or {}
    rows = s.get("seat_rows") or {}
    ch = s.get("checks") or {}
    r = {
        "dir": d, "name": m["name"], "commit": m["git_commit"], "dirty": m["git_dirty"], "venue": m["venue"],
        "agents": m["initially_active"], "n": m["n"], "load": num(m.get("load")), "requested_load": num(m.get("requested_load", m.get("load"))),
        "seed": m["seed"], "model": m.get("model", ""), "complete": m["complete"] == True,
        "t50": num(ev["t50_s"]), "t90": num(ev["t90_s"]), "t100": num(ev["t100_s"]),
        "doors_share": num(u.get("doors_share")), "avenues_share": num(u.get("avenues_share")),
        "unused_width_m": num(u.get("unused_exit_width_m")), "unused_width_frac": num(u.get("unused_exit_width_fraction")),
        "total_width_m": num(u.get("total_width_m")), "doors_width_m": num(u.get("doors_width_m")), "avenues_width_m": num(u.get("avenues_width_m")),
        "capacity_used_all": num(u.get("capacity_used_all_exits")),
        "circ_peak": num(circ.get("peak_density_p_m2")), "circ_peak_xy": (num(circ.get("peak_cell_x_m")), num(circ.get("peak_cell_y_m"))),
        "circ_time_los_f": num((circ.get("time_any_cell_above_s") or {}).get("los_f")),
        "circ_time_crush": num((circ.get("time_any_cell_above_s") or {}).get("crush")),
        "circ_exposure": num(circ.get("exposure_person_s")),
        "rows_exposure": num(rows.get("exposure_person_s")),
        "hotspots": s.get("hotspots", []),
        "plaus_pass": ch.get("plausibility_pass") == "true" or ch.get("plausibility_pass") is True,
        "overlap_p99": num(ch.get("overlap_all_p99")), "overlap_max": num(ch.get("overlap_all_max")),
        "inv_row_pass": ch.get("inv_row_pass") in ("true", True), "inv_row_exempt": ch.get("inv_row_exempt") in ("true", True),
        "step_up_pass": ch.get("step_up_pass", "true") in ("true", True), "wall_tops_pass": ch.get("wall_tops_pass", "true") in ("true", True),
        "row_changes": (s["inv_row"].get("row_changes") if seated else s["inv_row"].get("row_changes_bypassing_aisles")),
        "spawn": s.get("spawn"), "flows": s.get("flows"), "exits": s["exits"], "exit_util": u.get("exits", []),
        "gangway_util": s.get("gangway_utilisation"), "zones": s["zones"], "wall_s": num(m.get("wall_s")),
    }
    # The terrace: its zones are not split into circulation / seat rows; its headline over every zone but the pitch
    if not seated:
        zs = [z for z in s["zones"] if z["zone"] not in ("pitch",)]
        r["circ_peak"] = max(num(z["peak_density_p_m2"]) for z in zs)
        r["circ_exposure"] = sum(num(z["exposure_person_s"]) for z in zs)
        r["circ_time_los_f"] = max(num(z["time_any_cell_above_s"]["los_f"]) for z in zs)
        r["circ_time_crush"] = max(num(z["time_any_cell_above_s"]["crush"]) for z in zs)
    # Stalls: the longest interval without an evacuation while agents were still active (after the first evacuation), the agents
    # active during it and when it ended; the evacuation's tail: t100 - t99 (the last 1% of the agents)
    ts = load_csv(d, "timeseries.csv")
    gap, gap_end, gap_active, last_t, last_a = 0.0, float("nan"), 0, None, None
    for row in ts:
        t, a = float(row["t_real_s"]), int(row["active"])
        if last_a is not None and a < last_a:
            if last_t is not None and t - last_t > gap:
                gap, gap_end, gap_active = t - last_t, t, last_a
            last_t = t
        elif last_a is not None and last_t is None:
            pass
        last_a = a
    r["max_pause_s"], r["max_pause_end_s"], r["max_pause_active"] = gap, gap_end, gap_active
    n0 = r["agents"]
    need = math.ceil(0.99 * n0)
    r["t99"] = next((float(row["t_real_s"]) for row in ts if n0 - int(row["active"]) >= need), float("nan"))
    r["checks_pass"] = r["plaus_pass"] and (r["inv_row_pass"] or r["inv_row_exempt"]) and r["step_up_pass"] and r["wall_tops_pass"] and r["complete"]
    g = (r["flows"] or {}).get("gangways") or []
    if g:
        people = [x["people"] for x in g]
        mean = sum(people) / len(people)
        sd = math.sqrt(sum((p - mean) ** 2 for p in people) / len(people))
        used = [x for x in g if x["people"] > 0 and x["saturated_share"] is not None]
        r["gw_people_max"] = max(people)
        r["gw_people_mean"] = mean
        r["gw_imbalance"] = max(people) / mean if mean > 0 else float("nan")
        r["gw_cv"] = sd / mean if mean > 0 else float("nan")
        # saturation: people-weighted mean of the gangways' saturated shares; the share of gangways saturated half their active time or more
        wsum = sum(x["people"] for x in used)
        r["gw_saturated_mean"] = sum(x["people"] * num(x["saturated_share"]) for x in used) / wsum if wsum else float("nan")
        r["gw_saturated_half"] = sum(1 for x in used if num(x["saturated_share"]) >= 0.5) / len(g)
        r["gw_loaded_mean"] = sum(x["people"] * num(x["loaded_share"]) for x in used) / wsum if wsum else float("nan")
    return r


def case_runs(key, base=None):
    """The metrics of a case's runs that exist in the matrix 'base' (default MATRIX_DIR; in seed order)."""
    out = []
    for name in CASES[key][2]:
        d = run_dir(name, base)
        if d:
            out.append(run_metrics(d))
    return out


def stats(values):
    """mean, min, max of the finite values."""
    v = [x for x in values if x is not None and not (isinstance(x, float) and math.isnan(x))]
    if not v:
        return (float("nan"),) * 3
    return (sum(v) / len(v), min(v), max(v))


def fmt_spread(values, f="%.1f"):
    """'mean (min-max)' over seeds, or the single value."""
    mean, lo, hi = stats(values)
    if math.isnan(mean):
        return "-"
    if len([x for x in values if not (isinstance(x, float) and math.isnan(x))]) <= 1 or (f % lo) == (f % hi):
        return f % mean
    return (f % mean) + " (" + (f % lo) + "-" + (f % hi) + ")"
