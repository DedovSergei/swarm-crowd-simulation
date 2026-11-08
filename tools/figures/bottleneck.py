"""bottleneck.py: what governs t100 in venues S, M and L, from the geometry and the matrix's runs.

  python tools/figures/bottleneck.py [--out <the matrix's folder, default thesis_data.MATRIX_DIR>] [--travel results/validation/navigation]
                                     [--catchments results/validation/venues]

The matrix with the stair spacing (EMPIRICAL; thesis_data.MATRIX_DIR); the sustained flow also split by outlet: straight gangway 0 (the wing's
first, which empties at both ends and into the corner gangway) and the other straight gangways (in M and L one outlet, the head: the in-situ
counterpart of the stair harness's ascending maximum); the stair references include the calibration targets.

Inputs: the matrix's runs (thesis_data.CASES; summary.json, gangway_flows.csv), each venue's travel bound (nav_probe travel:
results/validation/navigation/<V>/travel.json) and its row segments' end gangways (venue_probe catchments:
results/validation/venues/<V>/catchments.csv). Writes <out>/bottleneck.md and <out>/bottleneck.json.

Definitions:
- MEASURED DOOR FLOW J_door: the default model's mean specific flow through S's doors at 100% load (the mean over the doors of their mean
  flows; S is the venue whose doors run at their capacity; J = 83.6 of the exit choice is its fixed point).
  With the stair spacing J_door stays the value measured before the calibration (S at 100%, MATRIX_DIR_BEFORE): the gangways then feed S's doors
  below their capacity, so a door flow of the calibrated matrix is a demand-limited rate, not a capacity, and would not give a lower bound; a door
  is a level passage, and the level rule is unchanged bit for bit. The calibrated matrix's door flows are reported as each venue's door utilisation.
- SUSTAINED GANGWAY FLOW: a gangway's outflow per metre of width (both ends: up to the concourse, down to the walkway, into the corner
  gangway at a merge) in its SATURATED 10 s windows (agents of its catchment still waiting to enter it while its density is at or above
  LoS F, run_experiment's definition), averaged over those windows. q_gw: pooled over the straight gangways of S, M and L at 100% load (the
  model's value); the corner gangways' apart.
- Lower bounds on t100: (a) exits N / (W_exits J_door); (b) gangways N_seated / (W_gangways q_gw), W_gangways the sum of the gangways'
  clear widths (1.20 m each, the corner gangways' narrowest); (c) travel: the longest unimpeded walking time from any seat at the model's
  free speeds (nav_probe travel). t_lb = max(a, b, c); efficiency t100 / t_lb.
- Gangway load imbalance: people per gangway (the agents whose first gangway it was): max / mean, coefficient of variation; straight and
  corner gangways together and apart.
- Counterfactuals: each gangway's service time T_g = people_g / c_g at its capacity c_g = (the run's pooled sustained flow of its type: straight
  or corner; the model's pooled value if the run has fewer than 3 such windows) x its width; t100_cf = t100 - max_g T_g + T', the time before
  and after the slowest gangway's service kept.
  (1) MEAN LOAD: every gangway the mean load, T' = max_g mean / c_g.
  (2) ATTAINABLE by route choice: a row segment's occupants can only use the gangways at its two ends (a dead-end segment: one); T' = the least
      max_g load_g / c_g over every split of each segment's seats between its end gangways (bisection on T, max-flow feasibility), for the
      runs whose gangway users are the seated agents (100%, 95% with the seats scaled by the load, nearest exit).
"""
import collections
import csv
import json
import math
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import thesis_data as td  # noqa: E402

LOS_F = 2.17   # swarm/metrics.hpp LOS_F_P_M2
MIN_SAT_WINDOWS = 3
# Stair planning flows commonly cited (persons per metre width per minute; each as reported in the source named, not yet checked against the original)
STAIR_GUIDANCE = [
    ("Guide to Safety at Sports Grounds (Green Guide), 6th ed. 2018: maximum rate of passage on stepped surfaces (the exit sizing rule of venues S, M, L; "
     "the CONSERVATIVE target)", 66.0),
    ("Green Guide, earlier editions: 40 persons per 550 mm unit width per minute on stairways", 40.0 / 0.55),
    ("Burghardt, Seyfried & Klingsch (2013): measured maximum specific flow on stairs, ascending 1.22 persons/(m s) (the EMPIRICAL target)", 1.22 * 60.0),
    ("the same, descending 1.25 persons/(m s)", 1.25 * 60.0),
    ("Fruin (1971), Highway Research Record 355: measured stair maxima 18.9 (up) / 20.0 (down) persons/(ft min); here ascending", 18.9 / 0.3048),
    ("Fruin (1971): stairway level of service E's upper bound (17 persons/(ft min))", 17.0 / 0.3048),
    ("SFPE Handbook (Gwynne & Rosenbaum): stairs 7/11 in, maximum specific flow 1.01 persons/(s m) of EFFECTIVE width", 1.01 * 60.0),
    ("the same, per metre of a 1.20 m gangway's CLEAR width (effective width 1.20 - 2 x 0.15 m)", 1.01 * 60.0 * 0.90 / 1.20),
]
CALIBRATED = os.path.normpath(td.MATRIX_DIR) != os.path.normpath(td.MATRIX_DIR_BEFORE)


def straight_index(name):
    """A straight gangway's index in its wing (its name's last token: 'straight +x+y (y wing) 0'), None for a corner gangway."""
    return int(name.split()[-1]) if name.startswith("straight") else None


def outlet_flows(gw):
    """The run's saturated windows' outflow per metre: straight gangway 0 (both ends and the corner gangway) and the others (S has none)."""
    q = {"straight 0": [], "straight >= 1": []}
    for name, g in gw.items():
        i = straight_index(name)
        if i is None:
            continue
        q["straight 0" if i == 0 else "straight >= 1"] += [f / g["width"] for f, s in g["windows"] if s]
    return q


def mean(xs):
    xs = [x for x in xs if x is not None and not math.isnan(x)]
    return sum(xs) / len(xs) if xs else float("nan")


def median(xs):
    xs = sorted(x for x in xs if x is not None and not math.isnan(x))
    if not xs:
        return float("nan")
    n = len(xs)
    return xs[n // 2] if n % 2 else 0.5 * (xs[n // 2 - 1] + xs[n // 2])


def gangway_windows(r):
    """Per gangway of a run: its type, width, people and [(outflow, saturated)] per 10 s window of its active period."""
    meta = {g["gangway"]: g for g in r["flows"]["gangways"]}
    out = {name: {"type": g["type"], "width": g["width_m"], "people": g["people"], "windows": []} for name, g in meta.items()}
    for w in td.load_csv(r["dir"], "gangway_flows.csv"):
        g = out[w["gangway"]]
        g["windows"].append((float(w["outflow_p_s"]), int(w["demand"]) > 0 and float(w["density_p_m2"]) >= LOS_F))
    return out


def type_flows(gw):
    """The run's sustained flow per metre by gangway type: {type: [saturated windows' outflow / width]}."""
    q = {"straight": [], "corner": []}
    for g in gw.values():
        q[g["type"]] += [f / g["width"] for f, s in g["windows"] if s]
    return q


def capacities(gw, model_pooled):
    """c_g [persons/s] per gangway: the run's pooled sustained flow of its type x width (the model's if < MIN_SAT_WINDOWS windows)."""
    q = type_flows(gw)
    per = {t: (mean(v) if len(v) >= MIN_SAT_WINDOWS else model_pooled[t]) for t, v in q.items()}
    return {n: per[g["type"]] * g["width"] for n, g in gw.items()}, per


def maxflow_feasible(pairs, cap, T):
    """Can the seats of every (lo, hi) pair be split between its gangways with load_g <= T cap_g? Pairs: {(lo, hi): seats}; a dead end has
    lo = -1. The bipartite structure is small (pairs x gangways): augmenting paths (Edmonds-Karp) on an adjacency dict."""
    S, Tn = "s", "t"
    graph = collections.defaultdict(dict)
    def add(u, v, c):
        graph[u][v] = graph[u].get(v, 0.0) + c
        graph[v].setdefault(u, 0.0)
    total = 0.0
    for (lo, hi), n in pairs.items():
        node = ("p", lo, hi)
        add(S, node, float(n))
        total += n
        for g in (lo, hi):
            if g >= 0:
                add(node, ("g", g), float("inf"))
    for g, c in cap.items():
        add(("g", g), Tn, T * c)
    flow = 0.0
    while True:
        parent = {S: None}
        queue = collections.deque([S])
        while queue and Tn not in parent:
            u = queue.popleft()
            for v, c in graph[u].items():
                if c > 1e-9 and v not in parent:
                    parent[v] = u
                    queue.append(v)
        if Tn not in parent:
            break
        b, v = float("inf"), Tn
        while parent[v] is not None:
            b = min(b, graph[parent[v]][v])
            v = parent[v]
        v = Tn
        while parent[v] is not None:
            u = parent[v]
            graph[u][v] -= b
            graph[v][u] += b
            v = u
        flow += b
    return flow >= total - 1e-6


def attainable_T(pairs, cap):
    """The least T (bisection, 0.05 s) with a feasible split: the routing-attainable slowest gangway service time."""
    lo, hi = 0.0, sum(pairs.values()) / min(cap.values())
    while hi - lo > 0.05:
        mid = 0.5 * (lo + hi)
        if maxflow_feasible(pairs, cap, mid):
            hi = mid
        else:
            lo = mid
    return hi


def load_pairs(venue, root, scale=1.0):
    """{(gangway_lo, gangway_hi): seats} from the venue's catchments.csv (gangway ids = the metrics' = run_experiment's order)."""
    p = os.path.join(root, venue, "catchments.csv")
    if not os.path.exists(p):
        return None
    pairs = collections.Counter()
    for row in td.load_csv(os.path.dirname(p), "catchments.csv"):
        lo, hi = int(row["gangway_lo"]), int(row["gangway_hi"])
        if lo < 0 and hi < 0:
            continue
        a, b = (lo, hi) if lo >= 0 else (hi, -1)
        pairs[(a, b)] += int(row["seats"]) * scale
    return dict(pairs)


def people_stats(gw):
    names = list(gw)
    def mc(ps):
        if not ps:
            return (float("nan"), float("nan"))
        mm = sum(ps) / len(ps)
        sd = math.sqrt(sum((p - mm) ** 2 for p in ps) / len(ps))
        return (max(ps) / mm if mm else float("nan"), sd / mm if mm else float("nan"))
    people = [gw[n]["people"] for n in names]
    return {"mean_people": sum(people) / len(people), "all": mc(people),
            "straight": mc([gw[n]["people"] for n in names if gw[n]["type"] == "straight"]),
            "corner": mc([gw[n]["people"] for n in names if gw[n]["type"] == "corner"])}


def main():
    out = td.MATRIX_DIR
    if "--out" in sys.argv:
        out = sys.argv[sys.argv.index("--out") + 1]
    travel_root = sys.argv[sys.argv.index("--travel") + 1] if "--travel" in sys.argv else "results/validation/navigation"
    catch_root = sys.argv[sys.argv.index("--catchments") + 1] if "--catchments" in sys.argv else "results/validation/venues"
    runs100 = {v: (td.case_runs(v + "_100") or [None])[0] for v in td.VENUES}
    door_flows = {v: mean([e["mean_flow_p_per_m_min"] for e in r["exits"] if e["exit"].startswith("door") and e["evacuated"] > 0])
                  for v, r in runs100.items() if r}
    J_door = door_flows["S"]
    if CALIBRATED:   # the door capacity: S at 100% before the calibration, where the doors ran at capacity (header)
        r_before = (td.case_runs("S_100", base=td.MATRIX_DIR_BEFORE) or [None])[0]
        J_door = mean([e["mean_flow_p_per_m_min"] for e in r_before["exits"] if e["exit"].startswith("door") and e["evacuated"] > 0])
    gws100 = {v: gangway_windows(r) for v, r in runs100.items() if r}
    q_by = {(v, t): q for v, gw in gws100.items() for t, q in type_flows(gw).items()}
    model_pooled = {t: mean(sum((q_by[(v, t)] for v in gws100), [])) for t in ("straight", "corner")}
    q_gw = model_pooled["straight"]
    travel = {}
    for v in td.VENUES:
        p = os.path.join(travel_root, v, "travel.json")
        if os.path.exists(p):
            with open(p) as f:
                travel[v] = json.load(f)
    import matrix_table   # the runs' drivers and commits (one driver, one simulation code version)
    prov = matrix_table.provenance([(k, r) for k in td.CASES for r in td.case_runs(k)])
    md = ["# Bottleneck analysis (stair spacing EMPIRICAL)" if CALIBRATED else "# Bottleneck analysis (the level spacing on the gangways)", "", prov, "",
          "From the geometry and the matrix's runs. Definitions: tools/figures/bottleneck.py (header)" +
          ". Runs: " + td.MATRIX_DIR + "; travel bounds results/validation/navigation/<V>/travel.json; row segments results/validation/venues/<V>/catchments.csv.", ""]
    door_line = (f"- **Door flow J_door = {J_door:.1f} persons/(m min)** (the door capacity): venue S at 100% before the stair calibration ({td.MATRIX_DIR_BEFORE}), the mean "
                 "over its 8 doors of their mean specific flows, where the doors ran at their capacity. With the stair spacing the gangways feed every "
                 "venue's doors below it; the same measure in this matrix (door utilisation = it / J_door): " +
                 ", ".join(f"{v} {door_flows[v]:.1f} ({door_flows[v] / J_door:.2f})" for v in td.VENUES if v in door_flows) + "."
                 if CALIBRATED else
                 f"- **Door flow J_door = {J_door:.1f} persons/(m min)**: venue S at 100% (default model), the mean over its 8 doors of their mean specific "
                 "flows (S's doors run at their capacity). The same measure in M / L, whose doors their gangways feed below capacity: " +
                 ", ".join(f"{v} {door_flows[v]:.1f}" for v in ("M", "L") if v in door_flows) + ".")
    md += ["## Measured flows", "",
           door_line,
           f"- **Sustained gangway flow q_gw = {q_gw:.3f} persons/(m s) = {60 * q_gw:.1f} persons/(m min)**: the straight gangways' outflow per metre "
           "in their saturated 10 s windows, pooled over S, M, L at 100%; the corner gangways: " +
           f"{model_pooled['corner']:.3f} persons/(m s) ({60 * model_pooled['corner']:.1f}).", "",
           "| venue | gangway type | saturated windows | mean [p/(m s)] | median [p/(m s)] | mean [p/(m min)] |", "|---|---|---:|---:|---:|---:|"]
    for v in gws100:
        for t in ("straight", "corner"):
            q = q_by[(v, t)]
            md.append(f"| {v} | {t} | {len(q)} | {mean(q):.3f} | {median(q):.3f} | {60 * mean(q):.1f} |" if q else f"| {v} | {t} | 0 | - | - | - |")
    md.append("")
    # The straight gangways by outlet
    q_out = {(v, k): q for v, gw in gws100.items() for k, q in outlet_flows(gw).items()}
    pooled_single = mean(sum((q_out[(v, "straight >= 1")] for v in gws100 if v != "S"), []))
    md += ["Straight gangways by outlet: gangway 0, the wing's first, empties at both ends (concourse and walkway) and into the corner "
           "gangway where they merge; in M and L the other straight gangways have one outlet, the head (the in-situ counterpart of the stair "
           "harness's ascending maximum). S has gangway 0 only (both ends).", "",
           "| venue | straight gangways | saturated windows | mean [p/(m s)] | mean [p/(m min)] |", "|---|---|---:|---:|---:|"]
    for v in gws100:
        for k in ("straight 0", "straight >= 1"):
            q = q_out[(v, k)]
            md.append(f"| {v} | {k} | {len(q)} | {mean(q):.3f} | {60 * mean(q):.1f} |" if q else f"| {v} | {k} | 0 | - | - |")
    md += ["", f"Pooled single-outlet straight gangways (M, L): **{pooled_single:.3f} persons/(m s) = {60 * pooled_single:.1f} persons/(m min)**.", ""]
    md += ["## Gangway flow against stair planning flows", "",
           "| source (as reported there; not yet checked against the original) | persons/(m min) | the model's sustained gangway flow / it |", "|---|---:|---:|"]
    for src, val in STAIR_GUIDANCE:
        md.append(f"| {src} | {val:.1f} | {60 * q_gw:.0f} / {val:.0f} = {60 * q_gw / val:.2f}x |")
    md.append(f"| **the model: straight gangways' sustained flow** (26.57 deg incline; free speed up 0.58 / down 0.655 m/s) | **{60 * q_gw:.1f}** | |")
    md.append(f"| the model: single-outlet straight gangways (M, L; one cross-section, ascending) | {60 * pooled_single:.1f} | |")
    md.append("")
    bounds = {}
    md += ["## Capacity lower bounds and efficiency", "",
           "| venue | case | N (seated) | (a) exits [s] | (b) gangways [s] | (c) travel [s] | **t_lb** [s] (binding) | t100 [s] | **t100 / t_lb** | "
           "(b) with the venue's own q [s] |",
           "|---|---|---|---:|---:|---:|---:|---:|---:|---:|"]
    for key, (v, label, names) in td.CASES.items():
        if v not in td.VENUES or key.endswith("_level"):   # the level-speed variants: another walking model
            continue
        rs = td.case_runs(key)
        if not rs:
            continue
        r0 = rs[0]
        n_all = mean([r["agents"] for r in rs])
        n_seat = mean([r["spawn"]["seated"] for r in rs])
        W_ex = r0["total_width_m"]
        W_gw = sum(g["width_m"] for g in r0["flows"]["gangways"])
        a = n_all / (W_ex * J_door / 60.0)
        b = n_seat / (W_gw * q_gw)
        own = mean(q_by.get((v, "straight"), [])) if (v, "straight") in q_by else float("nan")
        b_own = n_seat / (W_gw * own) if own == own else float("nan")
        c = travel[v]["max_s"] if v in travel else float("nan")
        tl = max(a, b, c if not math.isnan(c) else 0.0)
        which = "a" if tl == a else "b" if tl == b else "c"
        t100 = [r["t100"] for r in rs]
        eff = [t / tl for t in t100]
        bounds[key] = {"venue": v, "case": label, "n": n_all, "n_seated": n_seat, "exit_width_m": W_ex, "gangway_width_m": W_gw, "a_exits_s": a,
                       "b_gangways_s": b, "b_gangways_own_q_s": b_own, "c_travel_s": c, "t_lb_s": tl, "binding": which, "t100_s": t100, "efficiency": eff}
        md.append(f"| {v} | {label} | {n_all:.0f} ({n_seat:.0f}) | {a:.1f} | {b:.1f} | {c:.1f} | **{tl:.1f}** ({which}) | {td.fmt_spread(t100)} | "
                  f"**{td.fmt_spread(eff, '%.2f')}** | {b_own:.1f} |")
    md.append("")
    md.append("Exit widths: S 32.24 m (8 doors 1.20 m + 4 avenues 5.66 m), M 56.24 m (28 doors + avenues), L 123.84 m (44 doors 2.30 m + avenues); "
              "gangway widths: 12 / 28 / 44 gangways of 1.20 m. (b) with the venue's own q: the venue's straight gangways' sustained flow at 100% "
              "instead of the pooled model value (sensitivity).")
    md.append("")
    # Imbalance and the counterfactuals
    imb = {}
    md += ["## Gangway load imbalance and the counterfactuals", "",
           "Capacities c_g: the run's pooled sustained flow of the gangway's type x 1.20 m. T: the slowest gangway's service time people_g / c_g. "
           "(1) every gangway the mean load; (2) the least slowest service time any split of each row segment between its two end gangways "
           "attains (100%, 95%, nearest only: their gangway users are the seated agents).", "",
           "| venue | case | people per gangway: mean | max / mean (all; straight; corner) | CV (all; straight; corner) | capacity straight / corner [p/s] | "
           "slowest gangway: people, T [s] | (1) mean load: T' [s], **t100_cf** [s] (saved) | (2) attainable: T' [s], **t100_cf** [s] (saved) | t100 [s] |",
           "|---|---|---:|---|---|---|---|---|---|---:|"]
    for key in [k for k in td.CASES if k.split("_")[0] in td.VENUES and not k.endswith("_level")]:
        rs = td.case_runs(key)
        if not rs:
            continue
        v, label, _ = td.CASES[key]
        res = []
        attain_ok = key.endswith(("_100", "_95", "_nearest", "_cons", "_dt2"))
        for r in rs:
            gw = gangway_windows(r)
            cap, per = capacities(gw, model_pooled)
            st = people_stats(gw)
            T = {n: gw[n]["people"] / cap[n] for n in gw}
            gmax = max(T, key=T.get)
            T_mean = max(st["mean_people"] / cap[n] for n in gw)
            x = dict(st)
            x.update({"t100": r["t100"], "cap_straight": per["straight"] * 1.2, "cap_corner": per["corner"] * 1.2, "T_max": T[gmax],
                      "T_max_gangway": gmax, "T_max_people": gw[gmax]["people"], "T_mean": T_mean, "t100_cf_mean": r["t100"] - T[gmax] + T_mean})
            if attain_ok:
                pairs = load_pairs(v, catch_root, scale=r["load"])
                if pairs:
                    names = {g["gangway"]: i for i, g in enumerate(r["flows"]["gangways"])}   # summary order = gangway id order
                    capid = {names[n]: c for n, c in cap.items()}
                    Ta = attainable_T(pairs, capid)
                    x.update({"T_attain": Ta, "t100_cf_attain": r["t100"] - T[gmax] + Ta})
            res.append(x)
        imb[key] = res
        f = lambda k, i=None, fm="%.2f": td.fmt_spread([(x[k][i] if i is not None else x[k]) for x in res if k in x], fm)
        r0 = res[0]
        sav = lambda k: td.fmt_spread([100 * (x["t100"] - x[k]) / x["t100"] for x in res if k in x], "%.0f") + "%"
        att = (f"{f('T_attain', None, '%.0f')}, **{f('t100_cf_attain', None, '%.1f')}** ({sav('t100_cf_attain')})" if "T_attain" in r0 else "-")
        md.append(f"| {v} | {label} | {f('mean_people', None, '%.0f')} | {f('all', 0)}; {f('straight', 0)}; {f('corner', 0)} | "
                  f"{f('all', 1)}; {f('straight', 1)}; {f('corner', 1)} | {f('cap_straight')} / {f('cap_corner')} | "
                  f"{r0['T_max_gangway']}: {r0['T_max_people']}, {f('T_max', None, '%.0f')} | "
                  f"{f('T_mean', None, '%.0f')}, **{f('t100_cf_mean', None, '%.1f')}** ({sav('t100_cf_mean')}) | {att} | {f('t100', None, '%.1f')} |")
    md.append("")
    os.makedirs(out, exist_ok=True)
    with open(os.path.join(out, "bottleneck.md"), "w", encoding="utf-8") as fo:
        fo.write("\n".join(md) + "\n")
    with open(os.path.join(out, "bottleneck.json"), "w", encoding="utf-8") as fo:
        json.dump({"J_door_p_m_min": J_door, "door_flows_p_m_min": door_flows, "q_gw_p_m_s": q_gw, "q_gw_corner_p_m_s": model_pooled["corner"],
                   "q_single_outlet_p_m_s": pooled_single,
                   "q_by_outlet": {f"{v}_{k}": {"windows": len(q), "mean": mean(q)} for (v, k), q in q_out.items()},
                   "q_by_venue": {f"{v}_{t}": {"windows": len(q), "mean": mean(q), "median": median(q)} for (v, t), q in q_by.items()},
                   "travel": travel, "bounds": bounds, "imbalance": imb, "stair_guidance": STAIR_GUIDANCE}, fo, indent=1)
    print("\n".join(md))
    print("->", os.path.join(out, "bottleneck.md"))


if __name__ == "__main__":
    main()
