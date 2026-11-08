"""matrix_table.py: the experiment matrix's tables from the runs' summary.json files.

  python tools/figures/matrix_table.py [--out <the matrix's folder, default thesis_data.MATRIX_DIR>]

Writes <out>/matrix.md (one row per case: mean and min-max over its seeds; the 95% runs' t100 spread; the stair-flow bracket, the
before / after table against the matrix before the stair calibration and M's DT convergence) and <out>/matrix_runs.csv (one row per run). Definitions:
thesis_data.py and each run's summary.md.
"""
import csv
import math
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import thesis_data as td  # noqa: E402


def pct(x):
    return "-" if x is None or math.isnan(x) else "%.1f%%" % (100.0 * x)


def main():
    out = td.MATRIX_DIR
    if "--out" in sys.argv:
        out = sys.argv[sys.argv.index("--out") + 1]
    rows, runs = [], []
    for key, (venue, label, names) in td.CASES.items():
        rs = td.case_runs(key)
        runs += [(key, r) for r in rs]
        if not rs:
            rows.append(f"| {venue} | {label} | not run | | | | | | | | | | | | | | |")
            continue
        sp = lambda f, fmtS="%.1f": td.fmt_spread([f(r) for r in rs], fmtS)
        hot = rs[0]["hotspots"][0] if rs[0]["hotspots"] else None
        hot_s = (f"{hot['zone']} ({hot['x_m']:.1f}, {hot['y_m']:.1f}) m, {hot['peak_density_p_m2']:.2f} p/m^2, {hot['exposure_person_s']:.0f} person-s"
                 if hot else "-")
        checks = all(r["checks_pass"] for r in rs)
        inc = [r for r in rs if not r["complete"]]
        if inc:   # a run that did not complete (a gridlock): the times are over the completed runs
            label += " (seed " + ", ".join(str(r["seed"]) for r in inc) + " did not complete: times over the completed runs; checks FAIL = incomplete)"
        inv = sum(int(r["row_changes"] or 0) for r in rs)
        inv_s = (f"exempt ({inv})" if rs[0]["inv_row_exempt"] else str(inv))
        load_s = td.fmt_spread([r["agents"] for r in rs], "%.0f") + " (" + td.fmt_spread([100.0 * r["load"] for r in rs], "%.2f") + "%)"
        sat_s = (sp(lambda r: 100.0 * r.get("gw_saturated_mean", float("nan")), "%.0f") + "% / " +
                 sp(lambda r: 100.0 * r.get("gw_saturated_half", float("nan")), "%.0f") + "%") if "gw_saturated_mean" in rs[0] else "-"
        imb_s = (sp(lambda r: r["gw_imbalance"], "%.2f") + " / " + sp(lambda r: r["gw_cv"], "%.2f")) if "gw_imbalance" in rs[0] else "-"
        rows.append(" | ".join([
            "| " + venue, label, str(len(rs)), load_s,
            sp(lambda r: r["t50"]), sp(lambda r: r["t90"]), sp(lambda r: r["t99"]), "**" + sp(lambda r: r["t100"]) + "**",
            sp(lambda r: r["max_pause_s"]),
            sp(lambda r: 100.0 * r["doors_share"], "%.1f") + " / " + sp(lambda r: 100.0 * r["avenues_share"], "%.1f"),
            sp(lambda r: r["unused_width_m"], "%.1f") + " m",
            sat_s, imb_s,
            sp(lambda r: r["circ_peak"], "%.2f"),
            sp(lambda r: r["circ_time_los_f"]) + " / " + sp(lambda r: r["circ_time_crush"]),
            sp(lambda r: r["circ_exposure"], "%.0f"),
            hot_s, inv_s,
            sp(lambda r: r["overlap_p99"], "%.4f") + " / " + sp(lambda r: r["overlap_max"], "%.4f"),
            ("PASS" if checks else "**FAIL**") + " |"]))
    calibrated = os.path.normpath(td.MATRIX_DIR) != os.path.normpath(td.MATRIX_DIR_BEFORE)
    md = ["# The experiment matrix (stair spacing EMPIRICAL)" if calibrated else "# The experiment matrix (the level spacing on the gangways)", "",
          provenance(runs), "",
          "GPU, run_experiment with every per-step check (plausibility with no exemption on S / M / L, INV-row, the step-up rules, wall tops; "
          "the terrace: its documented exemptions); default model (queue-aware exit choice, incline speed" +
          (", stair spacing EMPIRICAL" if calibrated else "") + ") unless named. Values: the mean over "
          "a case's seeds and (min-max); one value: one run. t99: the time by which ceil(0.99 N) had left; longest pause: the longest interval without an evacuation while agents remained (a stall shows here). Runs: " + td.MATRIX_DIR + "/<name>_<timestamp> (names: thesis_data.CASES).", "",
          "| venue | case | runs | agents (load) | t50 [s] | t90 [s] | t99 [s] | t100 [s] | longest pause in evacuations [s] | doors / avenues [% of evacuated] | unused exit width | "
          "gangways saturated: people-weighted mean share / share of gangways >= 50% | people per gangway: max/mean / CV | "
          "circulation peak density [p/m^2] | circulation time >= LoS F / crush [s] | circulation crush exposure [person-s] | top hotspot (seed 1) | "
          "INV-row row changes | overlap p99 / max [BODY_DIAM] | checks |",
          "|---|---|---:|---|---:|---:|---:|---:|---:|---|---:|---|---|---:|---|---:|---|---:|---|---|"] + rows
    # The run-to-run spread of t100 from the 95% runs
    md += ["", "## Run-to-run spread of t100 (the 95% runs, seeds 1-3)", "",
           "| venue | t100 at 100% [s] | 95%: mean (min-max) [s] | 95%: spread (max - min) / mean | overcrowded: spread (max - min) / mean |",
           "|---|---:|---:|---:|---:|"]
    for v in td.VENUES:
        r100 = td.case_runs(v + "_100")
        r95 = td.case_runs(v + "_95")
        rov = td.case_runs(v + ("_150" if v == "S" else "_max"))
        m95 = td.stats([r["t100"] for r in r95])
        mov = td.stats([r["t100"] for r in rov])
        md.append(f"| {v} | {r100[0]['t100']:.1f} | " if r100 else f"| {v} | - | ")
        md[-1] += (td.fmt_spread([r["t100"] for r in r95]) + " | " + (pct((m95[2] - m95[1]) / m95[0]) if r95 else "-") + " | " +
                   (pct((mov[2] - mov[1]) / mov[0]) if rov else "-") + " |")
    # The top 3 circulation hotspots of each case (its first run; ranked by crush exposure, then time >= LoS F; every run's top 10: its
    # summary.md)
    md += ["", "## Top circulation hotspots (the case's first run; ranked by crush exposure, then time at or above LoS F)", "",
           "| venue | case | # | zone | x, y [m] | peak [p/m^2] | >= LoS F [s] | >= crush [s] | crush exposure [person-s] |",
           "|---|---|---:|---|---|---:|---:|---:|---:|"]
    for key, (venue, label, names) in td.CASES.items():
        rs = td.case_runs(key)
        if not rs:
            continue
        for i, h in enumerate(rs[0]["hotspots"][:3]):
            md.append(f"| {venue} | {label} | {i + 1} | {h['zone']} | {h['x_m']:.1f}, {h['y_m']:.1f} | {h['peak_density_p_m2']:.2f} | "
                      f"{h['time_above_los_f_s']:.1f} | {h['time_above_crush_s']:.1f} | {h['exposure_person_s']:.0f} |")
    if calibrated:
        md += stair_sections()
    os.makedirs(out, exist_ok=True)
    with open(os.path.join(out, "matrix.md"), "w", encoding="utf-8") as f:
        f.write("\n".join(md) + "\n")
    cols = ["case", "name", "commit", "dirty", "agents", "n", "load", "requested_load", "seed", "model", "complete", "t50", "t90", "t99", "t100", "max_pause_s", "max_pause_end_s", "max_pause_active",
            "doors_share", "avenues_share", "unused_width_m", "total_width_m", "circ_peak", "circ_time_los_f", "circ_time_crush", "circ_exposure",
            "rows_exposure", "gw_people_max", "gw_people_mean", "gw_imbalance", "gw_cv", "gw_saturated_mean", "gw_saturated_half",
            "row_changes", "overlap_p99", "overlap_max", "checks_pass", "wall_s", "dir"]
    with open(os.path.join(out, "matrix_runs.csv"), "w", newline="", encoding="utf-8") as f:
        w = csv.writer(f)
        w.writerow(cols)
        for key, r in runs:
            w.writerow([key] + [r.get(c, "") for c in cols[1:]])
    print("\n".join(md))
    print("->", os.path.join(out, "matrix.md"))


def provenance(runs):
    """The drivers and commits of the runs the tables come from (one driver, one simulation code version)."""
    drivers, commits = {}, {}
    for _, r in runs:
        m = td.load_summary(r["dir"])["meta"]
        drivers[m.get("driver", "?")] = drivers.get(m.get("driver", "?"), 0) + 1
        c = m["git_commit"][:7] + ("" if str(m["git_dirty"]) == "0" else " (dirty)")
        commits[c] = commits.get(c, 0) + 1
    return ("Runs: " + str(len(runs)) + " in " + td.MATRIX_DIR + "; GPU driver: " + "; ".join(f"{d} ({n} runs)" for d, n in drivers.items()) +
            "; run_experiment built at: " + ", ".join(f"{c} ({n} runs)" for c, n in sorted(commits.items())) + ".")


def stair_sections():
    """The stair-flow bracket (100%: EMPIRICAL and CONSERVATIVE), before / after the stair calibration (before: the level spacing on the
    gangways), M's DT convergence."""
    md = ["", "## The stair-flow bracket (100% load)", "",
          "t100 with the default stair spacing (EMPIRICAL: the gangways' maximum sustained flow at the measured stair maxima, 1.22 / 1.25 persons/(m s)) "
          "and with the CONSERVATIVE set (the Green Guide's planning rate, 66 persons/(m min)) as the upper marker.", "",
          "| venue | agents | t50 EMPIRICAL / CONSERVATIVE [s] | t90 [s] | **t100 EMPIRICAL [s]** | **t100 CONSERVATIVE [s]** | CONSERVATIVE / EMPIRICAL | circulation crush exposure EMPIRICAL / CONSERVATIVE [person-s] | checks |",
          "|---|---:|---|---|---:|---:|---:|---|---|"]
    for v in td.VENUES:
        e, c = td.case_runs(v + "_100"), td.case_runs(v + "_cons")
        if not e or not c:
            md.append(f"| {v} | - | | | | | | | not run |")
            continue
        e, c = e[0], c[0]
        md.append(f"| {v} | {e['agents']} | {e['t50']:.1f} / {c['t50']:.1f} | {e['t90']:.1f} / {c['t90']:.1f} | **{e['t100']:.1f}** | **{c['t100']:.1f}** | "
                  f"{c['t100'] / e['t100']:.3f} | {e['circ_exposure']:.0f} / {c['circ_exposure']:.0f} | "
                  f"{'PASS' if e['checks_pass'] and c['checks_pass'] else '**FAIL**'} |")
    before = [(k, r) for k in td.CASES for r in td.case_runs(k, td.MATRIX_DIR_BEFORE)]
    md += ["", "## Before / after the stair calibration (before: the level spacing on the gangways; after: EMPIRICAL)", "",
           "Before: " + provenance(before).replace(td.MATRIX_DIR, td.MATRIX_DIR_BEFORE) + " The same cases, spawns and seeds.", "",
           "| venue | case | t50 before / after [s] | t90 before / after [s] | **t100 before / after [s]** | t100 change | doors / avenues after [%] | circulation crush exposure before / after [person-s] |",
           "|---|---|---|---|---|---:|---|---|"]
    for key, (venue, label, names) in td.CASES.items():
        if key.endswith("_cons") or key == "M_dt2":
            continue
        a, b = td.case_runs(key, td.MATRIX_DIR_BEFORE), td.case_runs(key)
        if not a or not b:
            continue
        ta, tb = td.stats([r["t100"] for r in a])[0], td.stats([r["t100"] for r in b])[0]
        fs = td.fmt_spread
        inc = sum(not r["complete"] for r in a) + sum(not r["complete"] for r in b)
        if inc:   # a run that did not complete has no t100; the means are over the completed runs
            label += f" ({inc} run(s) did not complete: means over the completed ones)"
        md.append(f"| {venue} | {label} | {fs([r['t50'] for r in a])} / {fs([r['t50'] for r in b])} | {fs([r['t90'] for r in a])} / {fs([r['t90'] for r in b])} | "
                  f"**{fs([r['t100'] for r in a])} / {fs([r['t100'] for r in b])}** | {100.0 * (tb / ta - 1.0):+.1f}% | "
                  f"{fs([100.0 * r['doors_share'] for r in b])} / {fs([100.0 * r['avenues_share'] for r in b])} | "
                  f"{fs([r['circ_exposure'] for r in a], '%.0f')} / {fs([r['circ_exposure'] for r in b], '%.0f')} |")
    d1, d2 = td.case_runs("M_100"), td.case_runs("M_dt2")
    md += ["", "## DT convergence (venue M, 100%)", ""]
    if d1 and d2:
        d1, d2 = d1[0], d2[0]
        md += ["| step | t50 [s] | t90 [s] | t100 [s] | checks |", "|---|---:|---:|---:|---|",
               f"| DT | {d1['t50']:.1f} | {d1['t90']:.1f} | {d1['t100']:.1f} | {'PASS' if d1['checks_pass'] else '**FAIL**'} |",
               f"| DT / 2 | {d2['t50']:.1f} | {d2['t90']:.1f} | {d2['t100']:.1f} | {'PASS' if d2['checks_pass'] else '**FAIL**'} |",
               f"| change | {100.0 * (d2['t50'] / d1['t50'] - 1.0):+.2f}% | {100.0 * (d2['t90'] / d1['t90'] - 1.0):+.2f}% | {100.0 * (d2['t100'] / d1['t100'] - 1.0):+.2f}% | |"]
    else:
        md.append("not run")
    return md


if __name__ == "__main__":
    main()
