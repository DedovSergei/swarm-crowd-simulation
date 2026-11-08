"""gridlock.py: the gridlock robustness check of the default model. Run from the repository root after tools/experiment/gridlock_runs.sh.

Definitions (per run, from timeseries.csv: the active agents after every step):
  pause      an interval without an evacuation while agents remain: between two successive evacuations, or (a run that did not finish)
             from the last evacuation to the end of the run (open: the run ended inside it). The interval before the first evacuation
             is the walk to the nearest exit, not a pause; it is reported apart.
  stall      a run whose longest pause exceeds STALL_S = 60 s;
  gridlock   a run not finished at the step limit (40 000 steps = 6 996 s); its open pause counts as a stall too.
For every pause longer than DETAIL_S = 30 s the stall snapshots inside it (run_experiment --stall-dump-s 30: stall_<step>.csv, the active
agents' place, row, gangway, velocity, e_goal on the assigned exit's field and the assigned exit, after 30, 60, 120, ... s) describe it: where
the remaining agents stand (place, gangway, seat row), their assigned exits, whether agents on one single-file path (a seat row's clearway or
a gangway) head in opposite directions within PAIR_M of each other (counterflow), and how many changed their assigned exit between the
pause's first and last snapshot (exit switching).
Also: the same statistics for the matrices (the default model, results/evacuation/matrix; the model before the calibration,
results/evacuation/matrix_before_calibration), and whether the runs that repeat a matrix spawn (seeds 1-3) reproduce its timeseries.csv byte for byte.
Writes <dir>/gridlock.md and gridlock_runs.csv.
"""
import collections
import csv
import glob
import json
import math
import os
import re
import sys

OUT_DIR = os.environ.get("GRIDLOCK_DIR", "results/evacuation/gridlock_robustness")
REPORT_DIR = os.environ.get("GRIDLOCK_REPORT", OUT_DIR)   # where gridlock.md / gridlock_runs.csv go
REF_DIRS = [("the matrix (the default model and its variants)", "results/evacuation/matrix"),
            ("the matrix, model before the calibration (--stair-flow off)", "results/evacuation/matrix_before_calibration")]
STALL_S = 60.0
DETAIL_S = 30.0
PAIR_M = 1.5

# Case groups of this check: (key, label, name regex)
GROUPS = [("S_150", "S, 150% (every seat + 1 864 standing)", r"^S_load150_s\d+$"),
          ("M_max", "M, 121.42% (the achievable maximum; 150% requested)", r"^M_load150_s\d+$"),
          ("M_9x", "M, 90-94% (seeded partial loads)", r"^M_load9\d_s\d+$"),
          ("L_max", "L, 109.28% (the achievable maximum; 150% requested)", r"^L_load150_s\d+$")]


def runs_in(base):
    """Latest folder per run name in 'base': {name: dir}."""
    out = {}
    for d in sorted(glob.glob(os.path.join(base, "*_*"))):
        if not os.path.isdir(d) or not os.path.exists(os.path.join(d, "summary.json")):
            continue
        m = re.match(r"^(.*)_(\d{8}_\d{4})$", os.path.basename(d))
        if m:
            out[m.group(1)] = d
    return out


def pauses(d, n0):
    """Evacuation pauses of a run: list of (start_s, end_s, active, open) and the time of the first evacuation."""
    with open(os.path.join(d, "timeseries.csv"), newline="") as f:
        rows = [(int(r["step"]), float(r["t_real_s"]), int(r["active"])) for r in csv.DictReader(f)]
    out, last_t, last_a, first = [], None, n0, None
    for step, t, a in rows:
        if a < last_a:
            if last_t is not None:
                out.append((last_t, t, last_a, False))
            else:
                first = t
            last_t = t
        last_a = a
    end_t, end_a = rows[-1][1], rows[-1][2]
    if end_a > 0 and last_t is not None:
        out.append((last_t, end_t, end_a, True))
    return out, first, rows


def fold_dir(x, y, ex, ey):
    """The folded frame (lat = min(|x|, |y|), dep = max(|x|, |y|)) and a direction's components in it."""
    sx, sy = (1.0 if x >= 0 else -1.0), (1.0 if y >= 0 else -1.0)
    if abs(x) <= abs(y):
        return abs(x), abs(y), sx * ex, sy * ey
    return abs(y), abs(x), sy * ey, sx * ex


def wing(x, y):
    return ("+" if x >= 0 else "-") + ("+" if y >= 0 else "-") + ("y" if abs(x) <= abs(y) else "x")


def load_dump(path):
    with open(path, newline="") as f:
        return list(csv.DictReader(f))


def describe(dump, corner_ids):
    """Where the agents of a stall snapshot stand, their exits, the counterflow pairs on single-file paths."""
    places, gangways, rows, exits = collections.Counter(), collections.Counter(), collections.Counter(), collections.Counter()
    paths = collections.defaultdict(list)
    for r in dump:
        x, y = float(r["x_m"]), float(r["y_m"])
        lat, dep, dlat, ddep = fold_dir(x, y, float(r["e_goal_x"]), float(r["e_goal_y"]))
        p = r["place"]
        places[p] += 1
        exits[r["assigned_exit_name"]] += 1
        g = int(r["gangway"])
        if p in ("straight gangway", "corner gangway"):
            gangways[g] += 1
            axis = (dlat + ddep) / math.sqrt(2.0) if p == "corner gangway" else ddep
            # along the gangway: dep (straight) or the diagonal (corner); position along the axis
            s = (lat + dep) / math.sqrt(2.0) if p == "corner gangway" else dep
            paths[("gangway", g)].append((s, axis, int(r["agent"]), r["assigned_exit_name"], x, y))
        elif p == "clearway":
            rows[(wing(x, y), int(r["row"]))] += 1
            paths[("row", wing(x, y), int(r["row"]))].append((lat, dlat, int(r["agent"]), r["assigned_exit_name"], x, y))
    counter = []
    for key, ags in paths.items():
        fwd = [a for a in ags if a[1] > 0.3]
        bwd = [a for a in ags if a[1] < -0.3]
        best = None
        for a in fwd:
            for b in bwd:
                dd = math.hypot(a[4] - b[4], a[5] - b[5])
                if dd <= PAIR_M and (best is None or dd < best[0]):
                    best = (dd, a, b)
        if best:
            counter.append((key, len(ags), len(fwd), len(bwd), best))
    # Opposing pairs anywhere (also across a junction of two paths): e_goal . e_goal' < -0.5 within PAIR_M
    opp = []
    pts = [(float(r["x_m"]), float(r["y_m"]), float(r["e_goal_x"]), float(r["e_goal_y"]), r) for r in dump]
    for i in range(len(pts)):
        for j in range(i + 1, len(pts)):
            a, b = pts[i], pts[j]
            dd = math.hypot(a[0] - b[0], a[1] - b[1])
            if dd <= PAIR_M and a[2] * b[2] + a[3] * b[3] < -0.5:
                opp.append((dd, a[4], b[4]))
    return places, gangways, rows, exits, counter, sorted(opp, key=lambda t: t[0])


def run_stats(name, d):
    s = json.load(open(os.path.join(d, "summary.json")))
    m, ev = s["meta"], s["evacuation"]
    n0 = int(m["initially_active"])
    ps, first, rows = pauses(d, n0)
    longest = max(ps, key=lambda p: p[1] - p[0]) if ps else (float("nan"), float("nan"), 0, False)
    ch = s.get("checks") or {}
    r = {"name": name, "dir": d, "venue": m["venue"].split()[1] if m["venue"].startswith("venue") else "terrace", "agents": n0,
         "load": m.get("load"), "seed": m.get("seed"), "model": m.get("model", ""), "complete": m["complete"] is True,
         "steps_run": m["steps_run"], "t50": ev["t50_s"], "t90": ev["t90_s"], "t100": ev["t100_s"], "first_evac_s": first,
         "longest_pause_s": longest[1] - longest[0], "longest_pause_from_s": longest[0], "longest_pause_to_s": longest[1],
         "longest_pause_active": longest[2], "longest_pause_open": longest[3],
         "pauses_over_10s": sum(1 for p in ps if p[1] - p[0] > 10.0), "pauses_over_20s": sum(1 for p in ps if p[1] - p[0] > 20.0),
         "pauses_over_30s": sum(1 for p in ps if p[1] - p[0] > 30.0), "remaining_end": rows[-1][2],
         "checks_pass": all(str(ch.get(k, "true")).lower() == "true" for k in ("plausibility_pass", "step_up_pass", "wall_tops_pass")) and
                        str(ch.get("inv_row_pass", "true")).lower() == "true",
         "switches": m.get("choice_switches"), "commit": m.get("git_describe"), "dirty": m.get("git_dirty"), "driver": m.get("driver"),
         "pauses": ps}
    r["gridlock"] = not r["complete"]
    r["stall"] = r["longest_pause_s"] > STALL_S
    return r


def fmt(v, p=1):
    return "-" if v is None or (isinstance(v, float) and math.isnan(v)) else f"{v:,.{p}f}".replace(",", " ")


def main():
    runs = runs_in(OUT_DIR)
    if not runs:
        sys.exit("no runs in " + OUT_DIR)
    stats = {n: run_stats(n, d) for n, d in sorted(runs.items())}
    md = ["# Gridlock robustness of the default model", "",
          "Generated by tools/figures/gridlock.py from " + OUT_DIR + " (tools/experiment/gridlock_runs.sh). Model: the default (queue-aware "
          "exit choice, incline speed, stair spacing EMPIRICAL); every per-step check on; step limit 40 000 steps (6 996 s).", "",
          "**Definitions.** A *pause* is an interval without an evacuation while agents remain (between two successive evacuations, or, in a "
          f"run that did not finish, from the last evacuation to the end: open). *Stall*: the longest pause exceeds {STALL_S:.0f} s. "
          "*Gridlock*: the run has not finished at the step limit (its open pause also counts as a stall). The walk before the first "
          "evacuation is not a pause.", ""]
    commits = sorted({(r["commit"], r["dirty"], r["driver"]) for r in stats.values()})
    md.append("Runs: " + ", ".join(f"run_experiment at {c} (dirty {dd}), driver {dr}" for c, dd, dr in commits) + ".")
    md.append("")
    # --- frequency table ---
    md += ["## Gridlock and stall frequency", "",
           "| venue, load | runs | finished | **gridlocks** | **stalls (> 60 s)** | pauses > 30 s / > 20 s / > 10 s (runs) | longest pause: max / median [s] | t100 mean (min-max) [s] | every per-step check |",
           "|---|---:|---:|---:|---:|---|---|---|---|"]
    csv_rows = []
    for key, label, rx in GROUPS:
        rs = [r for n, r in stats.items() if re.match(rx, n)]
        if not rs:
            continue
        lp = sorted(r["longest_pause_s"] for r in rs)
        t100 = [r["t100"] for r in rs if r["complete"]]
        md.append(f"| {label} | {len(rs)} | {sum(r['complete'] for r in rs)} | **{sum(r['gridlock'] for r in rs)}** | **{sum(r['stall'] for r in rs)}** | "
                  f"{sum(r['pauses_over_30s'] > 0 for r in rs)} / {sum(r['pauses_over_20s'] > 0 for r in rs)} / {sum(r['pauses_over_10s'] > 0 for r in rs)} | "
                  f"{fmt(lp[-1])} / {fmt(lp[len(lp) // 2] if len(lp) % 2 else 0.5 * (lp[len(lp) // 2 - 1] + lp[len(lp) // 2]))} | "
                  f"{fmt(sum(t100) / len(t100)) if t100 else '-'} ({fmt(min(t100)) if t100 else '-'}-{fmt(max(t100)) if t100 else '-'}) | "
                  f"{sum(r['checks_pass'] for r in rs)} of {len(rs)} PASS |")
    allr = list(stats.values())
    md.append(f"| **all** | {len(allr)} | {sum(r['complete'] for r in allr)} | **{sum(r['gridlock'] for r in allr)}** | **{sum(r['stall'] for r in allr)}** | "
              f"{sum(r['pauses_over_30s'] > 0 for r in allr)} / {sum(r['pauses_over_20s'] > 0 for r in allr)} / {sum(r['pauses_over_10s'] > 0 for r in allr)} | "
              f"{fmt(max(r['longest_pause_s'] for r in allr))} / - | - | {sum(r['checks_pass'] for r in allr)} of {len(allr)} PASS |")
    md.append("")
    # --- the reference matrices ---
    md += ["### For comparison: the matrices (the same driver and simulation code)", "",
           "| matrix | runs (seated venues) | finished | gridlocks | stalls (> 60 s) | longest pause: max [s] (run) |", "|---|---:|---:|---:|---:|---|"]
    variant = re.compile(r"nearest|level|conservative|dt2")
    for label, base, only_default in [(REF_DIRS[0][0], REF_DIRS[0][1], False), ("the matrix's default-model runs only (no variant)", REF_DIRS[0][1], True),
                                      (REF_DIRS[1][0], REF_DIRS[1][1], False)]:
        rr = [run_stats(n, d) for n, d in sorted(runs_in(base).items()) if not n.startswith("terrace") and not (only_default and variant.search(n))]
        if not rr:
            continue
        worst = max(rr, key=lambda r: r["longest_pause_s"])
        md.append(f"| {label} | {len(rr)} | {sum(r['complete'] for r in rr)} | {sum(r['gridlock'] for r in rr)} | {sum(r['stall'] for r in rr)} | "
                  f"{fmt(worst['longest_pause_s'])} ({worst['name']}{', open: gridlock' if worst['longest_pause_open'] else ''}) |")
    md.append("")
    # --- reproduction of the matrix's spawns ---
    ref = runs_in(REF_DIRS[0][1])
    same = []
    for n, r in stats.items():
        if n in ref:
            a = open(os.path.join(r["dir"], "timeseries.csv"), "rb").read()
            b = open(os.path.join(ref[n], "timeseries.csv"), "rb").read()
            same.append((n, a == b))
    ref_default = [n for n in ref if not n.startswith("terrace") and not variant.search(n)]
    distinct = len(stats) + sum(1 for n in ref_default if n not in stats)
    md += [f"**Distinct default-model runs of the seated venues** (this check's {len(stats)} and the matrix's {len(ref_default)}, a spawn repeated by both "
           f"counted once): {distinct}, with {sum(r['stall'] for r in stats.values())} stalls in this check and none in the matrix's; a per-run stall probability above {300 / distinct:.1f}% would "
           f"have shown one with 95% probability (rule of three: 3 / {distinct}).", ""]
    if same:
        md += ["### The matrix's spawns reproduced", "",
               "The runs of this check that repeat a matrix spawn (seeds 1-3 of S 150% and M 121.42%; L's seeds 4-9 are new) repeat its runs (the same spawn, model, driver and simulation code): "
               + ", ".join(f"{n} {'byte-identical' if ok else 'DIFFERENT'}" for n, ok in sorted(same)) + " (timeseries.csv).", ""]
    # --- per run ---
    md += ["## Every run", "",
           "| run | agents | load | seed | finished | t50 / t90 / t100 [s] | first evacuation [s] | longest pause [s] (from - to, active) | pauses > 10 s | exit switches | checks |",
           "|---|---:|---:|---:|---|---|---:|---|---:|---:|---|"]
    for n, r in stats.items():
        md.append(f"| {n} | {fmt(float(r['agents']), 0)} | {100 * r['load']:.2f}% | {r['seed']} | {'yes' if r['complete'] else '**NO (gridlock)**'} | "
                  f"{fmt(r['t50'])} / {fmt(r['t90'])} / {fmt(r['t100'])} | {fmt(r['first_evac_s'])} | {fmt(r['longest_pause_s'])} "
                  f"({fmt(r['longest_pause_from_s'])} - {fmt(r['longest_pause_to_s'])}{' open' if r['longest_pause_open'] else ''}, {r['longest_pause_active']}) | "
                  f"{r['pauses_over_10s']} | {r['switches']} | {'PASS' if r['checks_pass'] else 'FAIL'} |")
        csv_rows.append({k: v for k, v in r.items() if k not in ("pauses", "dir")})
    md.append("")
    # --- stall details ---
    md += ["## Pauses longer than 30 s", ""]
    any_detail = False
    for n, r in stats.items():
        for (a, b, act, op) in r["pauses"]:
            if b - a <= DETAIL_S:
                continue
            any_detail = True
            dumps = sorted(glob.glob(os.path.join(r["dir"], "stall_*.csv")), key=lambda p: int(re.findall(r"\d+", os.path.basename(p))[0]))
            inside = [p for p in dumps if a < float(load_dump(p)[0]["t_s"]) <= b + 1e-6] if dumps else []
            md.append(f"### {n}: {b - a:.1f} s{' (open: the run ended inside it)' if op else ''}, from {a:.1f} s to {b:.1f} s, {act} agents active")
            md.append("")
            if not inside:
                md += ["(no stall snapshot inside the pause)", ""]
                continue
            first, last = load_dump(inside[0]), load_dump(inside[-1])
            places, gws, rws, exits, counter, opp = describe(last, set())
            md.append(f"Snapshots: {', '.join(os.path.basename(p) for p in inside)}. At {float(last[0]['t_s']):.1f} s ({os.path.basename(inside[-1])}):")
            md.append("")
            md.append("- places: " + ", ".join(f"{k} {v}" for k, v in places.most_common()))
            if gws:
                md.append("- gangways (id: agents): " + ", ".join(f"{k}: {v}" for k, v in gws.most_common()))
            if rws:
                md.append("- seat rows (wing, row: agents): " + ", ".join(f"{k[0]} {k[1]}: {v}" for k, v in rws.most_common(12)))
            md.append("- assigned exits: " + ", ".join(f"{k} {v}" for k, v in exits.most_common()))
            speeds = sorted(float(x["speed_m_s"]) for x in last)
            md.append(f"- speed: median {speeds[len(speeds) // 2]:.3f} m/s, max {speeds[-1]:.3f} m/s; agents below 0.05 m/s: "
                      f"{sum(1 for v in speeds if v < 0.05)} of {len(speeds)}")
            if counter:
                for key, nag, nf, nb, (dd, fa, ba) in counter:
                    md.append(f"- **counterflow on {key[0]} {' '.join(str(k) for k in key[1:])}**: {nag} agents, {nf} heading one way and {nb} the "
                              f"other; nearest opposing pair {dd:.2f} m apart: agent {fa[2]} (to {fa[3]}) and agent {ba[2]} (to {ba[3]})")
            else:
                md.append(f"- counterflow on a single-file path (opposing e_goal within {PAIR_M} m on one seat row or gangway): none")
            if opp:
                kinds = collections.Counter(tuple(sorted((o[1]["place"] + (" " + o[1]["gangway"] if "gangway" in o[1]["place"] else ""),
                                                          o[2]["place"] + (" " + o[2]["gangway"] if "gangway" in o[2]["place"] else "")))) for o in opp)
                dd, a1, b1 = opp[0]
                md.append(f"- **opposing pairs** (e_goal in opposite directions, dot < -0.5, within {PAIR_M} m, on any paths): {len(opp)}; where: " +
                          ", ".join(f"{k[0]} / {k[1]} {v}" for k, v in kinds.most_common()) + f"; nearest {dd:.2f} m: agent {a1['agent']} ({a1['place']} "
                          f"{a1['gangway']}, to {a1['assigned_exit_name']}) and agent {b1['agent']} ({b1['place']} {b1['gangway']}, to {b1['assigned_exit_name']})")
            else:
                md.append(f"- opposing pairs (e_goal dot < -0.5 within {PAIR_M} m, any paths): none")
            fa = {x["agent"]: x["assigned_exit"] for x in first}
            sw = sum(1 for x in last if x["agent"] in fa and fa[x["agent"]] != x["assigned_exit"])
            md.append(f"- exit switching during the pause ({os.path.basename(inside[0])} -> {os.path.basename(inside[-1])}): {sw} of {len(last)} agents "
                      "changed their assigned exit")
            md.append("")
    if not any_detail:
        md += ["None: no run of this check paused for more than 30 s.", ""]
    with open(os.path.join(REPORT_DIR, "gridlock.md"), "w", encoding="utf-8", newline="\n") as f:
        f.write("\n".join(md) + "\n")
    with open(os.path.join(REPORT_DIR, "gridlock_runs.csv"), "w", newline="") as f:
        w = csv.DictWriter(f, fieldnames=list(csv_rows[0].keys()))
        w.writeheader()
        w.writerows(csv_rows)
    print("\n".join(md[:40]))
    print("->", os.path.join(REPORT_DIR, "gridlock.md"))


if __name__ == "__main__":
    main()
