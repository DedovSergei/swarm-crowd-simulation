"""results_tables.py: the tables of results/RESULTS.md, generated from the matrix (thesis_data.MATRIX_DIR, its bottleneck.json), the matrix
before the stair calibration (thesis_data.MATRIX_DIR_BEFORE, its bottleneck.json) and the stair harness runs, so that
every number in RESULTS.md comes from the runs it names. Prints Markdown (pasted into RESULTS.md, then checked against matrix.md and
bottleneck.md); --out FILE also writes it.

  python tools/figures/results_tables.py [--stair results/validation/stair_flow/harness] [--out out/results_tables.md]
"""
import csv
import glob
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import thesis_data as td  # noqa: E402


def g(n, nd=1):
    """A number with a thin-space-free thousands separator as RESULTS.md writes it ('1 477.4')."""
    s = f"{n:,.{nd}f}"
    return s.replace(",", " ")


def spread(vals, nd=1):
    m, lo, hi = td.stats(vals)
    if len(vals) <= 1 or f"{lo:.{nd}f}" == f"{hi:.{nd}f}":
        return g(m, nd)
    return f"{g(m, nd)} ({g(lo, nd)}-{g(hi, nd)})"


def bottleneck(base):
    p = os.path.join(base, "bottleneck.json")
    return json.load(open(p)) if os.path.exists(p) else None


ROWS = [("terrace", "terrace", "N = 4 096"), ("S", "S_95", "95%"), ("S", "S_100", "**100%**"), ("S", "S_125", "125%"), ("S", "S_150", "150%"),
        ("S", "S_150gw", "150%, standing also on the gangways"), ("S", "S_nearest", "100%, nearest exit"), ("M", "M_95", "95%"), ("M", "M_100", "**100%**"),
        ("M", "M_max", "125% and 150% requested = 121.4% (the floor's maximum)"), ("M", "M_nearest", "100%, nearest exit"), ("L", "L_95", "95%"),
        ("L", "L_100", "**100%**"), ("L", "L_max", "125% and 150% requested = 109.3% (the floor's maximum)"), ("L", "L_nearest", "100%, nearest exit")]


def matrix_table(bn):
    out = ["| venue | case | agents | t50 [s] | t90 [s] | **t100 [s]** | t100 CONSERVATIVE [s] | t100 / t_lb | doors / avenues | exposure to critical density "
           "in circulation areas [person-s] |", "|---|---|---:|---:|---:|---:|---:|---:|---|---:|"]
    for v, key, label in ROWS:
        rs = td.case_runs(key)
        if not rs:
            out.append(f"| {v} | {label} | not run | | | | | | | |")
            continue
        cons = td.case_runs(v + "_cons") if key.endswith("_100") else []
        b = (bn or {}).get("bounds", {}).get(key)
        eff = spread(b["efficiency"], 2) if b else "-"
        da = "(4 gaps)" if v == "terrace" else f"{100 * rs[0]['doors_share']:.0f} / {100 * rs[0]['avenues_share']:.0f}%"
        expo = spread([r["circ_exposure"] for r in rs], 0) + (" (all zones)" if v == "terrace" else "")
        t100 = spread([r["t100"] for r in rs])
        out.append(f"| {v} | {label} | {g(rs[0]['agents'], 0)} | {spread([r['t50'] for r in rs])} | {spread([r['t90'] for r in rs])} | **{t100}** | "
                   f"{('**' + g(cons[0]['t100']) + '**') if cons else ''} | {('**' + eff + '**') if key.endswith('_100') and b else eff if v != 'terrace' else '-'} | "
                   f"{da} | {expo} |")
    return out


def before_after():
    out = ["| venue | case | t100 before [s] | **t100 after [s]** | change | t50 change | exposure to critical density before / after [person-s] |",
           "|---|---|---:|---:|---:|---:|---|"]
    for v, key, label in ROWS:
        a, b = td.case_runs(key, td.MATRIX_DIR_BEFORE), td.case_runs(key)
        if key == "terrace":
            a = td.case_runs(key)   # the terrace has no gangways: one run serves both
        if not a or not b:
            continue
        ta, tb = td.stats([r["t100"] for r in a])[0], td.stats([r["t100"] for r in b])[0]
        t5a, t5b = td.stats([r["t50"] for r in a])[0], td.stats([r["t50"] for r in b])[0]
        ea, eb = td.stats([r["circ_exposure"] for r in a])[0], td.stats([r["circ_exposure"] for r in b])[0]
        inc = [r["seed"] for r in a + b if not r["complete"]]
        note = f" (seed {', '.join(str(x) for x in inc)} before: did not complete; the mean over the others)" if inc else ""
        out.append(f"| {v} | {label.strip('*')}{note} | {spread([r['t100'] for r in a])} | **{spread([r['t100'] for r in b])}** | {100 * (tb / ta - 1):+.1f}% | "
                   f"{100 * (t5b / t5a - 1):+.1f}% | {g(ea, 0)} / {g(eb, 0)} |")
    return out


def bottleneck_table(bn, bn_before):
    out = ["| venue | (a) exits | (b) gangways | (c) travel | t_lb | t100 | **efficiency t100 / t_lb** (before the calibration) | people per straight gangway: "
           "max / mean | t100 if each row segment split its seats between its two end gangways to balance them |", "|---|---:|---:|---:|---:|---:|---:|---:|---:|"]
    for v in td.VENUES:
        b = bn["bounds"].get(v + "_100")
        im = bn["imbalance"].get(v + "_100")
        b_before = (bn_before or {}).get("bounds", {}).get(v + "_100")
        if not b:
            continue
        im = im[0] if isinstance(im, list) else im
        eff_before = f"{b_before['efficiency'][0]:.2f}" if b_before else "-"
        split = im.get("t100_cf_attain") if im else None
        out.append(f"| {v} | {b['a_exits_s']:.0f} s | **{b['b_gangways_s']:.0f} s** | {b['c_travel_s']:.0f} s | {b['t_lb_s']:.0f} s | {g(b['t100_s'][0])} s | "
                   f"**{b['efficiency'][0]:.2f}** ({eff_before}) | {im['straight'][0]:.2f} | " +
                   (f"{g(split)} s ({100 * (split / b['t100_s'][0] - 1):+.0f}%)" if split else "-") + " |")
    return out


def flows(bn, bn_before):
    out = ["| in-situ gangway flow [persons/(m min)] | before the calibration | **EMPIRICAL** |", "|---|---:|---:|"]
    for label, key in (("single-outlet straight gangways (M, L), saturated 10 s windows", "q_single_outlet_p_m_s"),
                       ("all straight gangways pooled (the gangway bound's flow)", "q_gw_p_m_s"), ("corner gangways", "q_gw_corner_p_m_s")):
        a = (bn_before or {}).get(key)
        out.append(f"| {label} | {60 * a:.1f} | **{60 * bn[key]:.1f}** |" if a else f"| {label} | - | **{60 * bn[key]:.1f}** |")
    out.append(f"| door capacity J_door (S's doors at 100% before the calibration, where they run at capacity) | | {bn['J_door_p_m_min']:.1f} |")
    out.append("| doors' mean flow S / M / L | | " + " / ".join(f"{bn['door_flows_p_m_min'][v]:.1f}" for v in td.VENUES) + " |")
    return out


def stair(folder):
    out = ["| stair harness, maximum sustained specific flow [persons/(m s)] (at rho) | ascending | descending | level (rake 0) |", "|---|---:|---:|---:|"]
    for name, label in (("stair_baseline", "the level spacing (before the calibration)"), ("stair_empirical", "**EMPIRICAL**"),
                        ("stair_conservative", "CONSERVATIVE")):
        found = sorted(glob.glob(os.path.join(folder, name + "_*")))
        if not found:
            continue
        rows = list(csv.DictReader(open(os.path.join(found[-1], "stair.csv"), newline="")))
        best = {}
        for r in rows:
            d, J, rho = r["dir"], float(r["flow_p_m_s"]), float(r["rho_p_m2"])
            if d not in best or J > best[d][0]:
                best[d] = (J, rho)
        cell = lambda d: f"{best[d][0]:.3f} ({best[d][1]:.2f})" if d in best else "-"
        out.append(f"| {label}: {found[-1].replace(os.sep, '/')} | {cell('up')} | {cell('down')} | {cell('level')} |")
    return out


def variants():
    out = ["| venue | level walking, queue-aware | level walking, nearest | incline speed, level spacing (before the calibration) | **stairs (default)** | stairs, nearest |",
           "|---|---:|---:|---:|---:|---:|"]
    for v in td.VENUES:
        t = lambda k, base=None: (td.case_runs(k, base) or [{"t100": float("nan")}])[0]["t100"]
        out.append(f"| {v} | {g(t(v + '_level'))} | {g(t(v + '_nearest_level'))} | {g(t(v + '_100', td.MATRIX_DIR_BEFORE))} | **{g(t(v + '_100'))}** | {g(t(v + '_nearest'))} |")
    return out


def facts():
    """Single numbers RESULTS.md quotes in its text."""
    out = []
    runs = [r for k in td.CASES for r in td.case_runs(k)]
    seated = [r for r in runs if r["spawn"]]   # the seated venues (the terrace has no seat spawn)
    out.append(f"- runs {len(runs)}: every check {'PASS' if all(r['checks_pass'] for r in runs) else 'FAIL'}; seated row changes "
               f"{sum(int(r['row_changes'] or 0) for r in seated)}; overlap p99 <= {max(r['overlap_p99'] for r in seated):.4f}, max <= {max(r['overlap_max'] for r in seated):.3f}")
    out.append("- drivers: " + ", ".join(sorted({td.load_summary(r['dir'])['meta'].get('driver', '?') for r in runs})) + "; commits: " +
               ", ".join(sorted({r['commit'][:7] for r in runs})))
    for v in td.VENUES:
        r95 = [r["t100"] for r in td.case_runs(v + "_95")]
        m, lo, hi = td.stats(r95)
        e, c = td.case_runs(v + "_100"), td.case_runs(v + "_cons")
        rov = [r["t100"] for r in td.case_runs(v + ("_150" if v == "S" else "_max"))]
        mo, loo, hio = td.stats(rov)
        if e:
            out.append(f"- {v}: 95% spread {100 * (hi - lo) / m:.1f}%; overcrowded spread {100 * (hio - loo) / mo:.1f}%; CONSERVATIVE / EMPIRICAL "
                       f"{c[0]['t100'] / e[0]['t100']:.3f}; circulation time >= crush {e[0]['circ_time_crush']:.0f} s; peak circulation density "
                       f"{e[0]['circ_peak']:.2f}; t99 {e[0]['t99']:.1f}")
    pauses = [(r["max_pause_s"], r["name"]) for r in seated]
    out.append(f"- longest pause: {max(pauses)[0]:.1f} s ({max(pauses)[1]})")
    d1, d2 = td.case_runs("M_100"), td.case_runs("M_dt2")
    if d1 and d2:
        out.append(f"- M DT / 2: t100 {d1[0]['t100']:.1f} -> {d2[0]['t100']:.1f} ({100 * (d2[0]['t100'] / d1[0]['t100'] - 1):+.2f}%), t50 "
                   f"{100 * (d2[0]['t50'] / d1[0]['t50'] - 1):+.2f}%, t90 {100 * (d2[0]['t90'] / d1[0]['t90'] - 1):+.2f}%")
    return out


def main():
    stair_dir = sys.argv[sys.argv.index("--stair") + 1] if "--stair" in sys.argv else "results/validation/stair_flow/harness"
    bn, bn_before = bottleneck(td.MATRIX_DIR), bottleneck(td.MATRIX_DIR_BEFORE)
    md = [f"<!-- results_tables.py: MATRIX_DIR {td.MATRIX_DIR}, MATRIX_DIR_BEFORE {td.MATRIX_DIR_BEFORE}, stair {stair_dir} -->", "",
          "## matrix", ""] + matrix_table(bn) + ["", "## before / after", ""] + before_after()
    if bn:
        md += ["", "## bottleneck", ""] + bottleneck_table(bn, bn_before) + ["", "## flows", ""] + flows(bn, bn_before)
    md += ["", "## stair harness", ""] + stair(stair_dir) + ["", "## walking-model variants (t100 at 100%)", ""] + variants() + ["", "## facts", ""] + facts()
    text = "\n".join(md) + "\n"
    print(text)
    if "--out" in sys.argv:
        p = sys.argv[sys.argv.index("--out") + 1]
        os.makedirs(os.path.dirname(p) or ".", exist_ok=True)
        open(p, "w", encoding="utf-8").write(text)


if __name__ == "__main__":
    main()
