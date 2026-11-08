"""Measure the pitch fence (the thin closed rectangular ring around the pitch) in stadium.obj.

The OBJ is one object whose primitives each keep their own vertices, so connected components
are taken over the file's vertex indices (welding by position would merge everything through
the shared floor). The fence pieces are the thin, ground-standing, axis-aligned boxes that lie
along the edge of the pitch floor (the z = 0 face containing the origin). Every gap (gate) is
found by sampling the ring's midline perimeter.

Usage: python tools/measure_fence.py [stadium.obj]      (numpy only)
"""

import sys

import numpy as np

THIN = 0.02        # max wall thickness of a fence piece
MAX_HEIGHT = 0.1   # fence pieces are low barriers, not stands or walls
BAND = 0.02        # pieces must lie within this distance of the pitch-floor edge
STEP = 0.0002      # midline sampling step for gate detection


def load_obj(path):
    verts, faces = [], []
    with open(path) as f:
        for line in f:
            if line.startswith("v "):
                verts.append([float(t) for t in line.split()[1:4]])
            elif line.startswith("f "):
                ids = [int(t.split("/")[0]) for t in line.split()[1:]]
                faces.append([i - 1 if i > 0 else len(verts) + i for i in ids])
    return np.asarray(verts, dtype=np.float64), faces


def components(n_verts, faces):
    parent = list(range(n_verts))

    def find(a):
        while parent[a] != a:
            parent[a] = parent[parent[a]]
            a = parent[a]
        return a

    for f in faces:
        root = find(f[0])
        for i in f[1:]:
            parent[find(i)] = root
    groups = {}
    for fi, f in enumerate(faces):
        groups.setdefault(find(f[0]), []).append(fi)
    return list(groups.values())


def main():
    path = sys.argv[1] if len(sys.argv) > 1 else "stadium.obj"
    verts, faces = load_obj(path)
    comps = []
    for fs in components(len(verts), faces):
        idx = np.unique(np.concatenate([faces[i] for i in fs]))
        p = verts[idx]
        comps.append({"faces": len(fs), "verts": len(idx), "lo": p.min(0), "hi": p.max(0)})

    # Pitch floor: flat z = 0 component whose footprint contains the origin
    floors = [c for c in comps if c["hi"][2] - c["lo"][2] < 1e-9 and abs(c["lo"][2]) < 1e-9
              and np.all(c["lo"][:2] < 0) and np.all(c["hi"][:2] > 0)]
    if len(floors) != 1:
        sys.exit(f"expected exactly one pitch floor component, found {len(floors)}")
    pitch_lo, pitch_hi = floors[0]["lo"][:2], floors[0]["hi"][:2]

    # Fence pieces: thin ground-standing axis-aligned boxes along the pitch-floor edge
    def on_edge(c):
        lo, hi = c["lo"][:2], c["hi"][:2]
        near_outer = np.all(lo > pitch_lo - BAND) and np.all(hi < pitch_hi + BAND)
        touches_edge = (np.any(hi >= pitch_hi - 1e-6) or np.any(lo <= pitch_lo + 1e-6))
        return near_outer and touches_edge

    pieces = [c for c in comps
              if abs(c["lo"][2]) < 1e-9 and 0 < c["hi"][2] - c["lo"][2] <= MAX_HEIGHT
              and min(c["hi"][0] - c["lo"][0], c["hi"][1] - c["lo"][1]) <= THIN
              and c["faces"] == 6 and c["verts"] == 8 and on_edge(c)]
    if not pieces:
        sys.exit("no fence pieces found")

    lo = np.min([c["lo"] for c in pieces], axis=0)
    hi = np.max([c["hi"] for c in pieces], axis=0)
    centre = 0.5 * (lo[:2] + hi[:2])
    outer = 0.5 * (hi[:2] - lo[:2])

    # Inner faces per side: pieces running along y form the +/-x sides, along x the +/-y sides
    def side(axis, sign):
        run = 1 - axis
        cand = [c for c in pieces
                if (c["hi"][run] - c["lo"][run]) > (c["hi"][axis] - c["lo"][axis])
                and sign * (0.5 * (c["lo"][axis] + c["hi"][axis]) - centre[axis]) > 0]
        if not cand:
            sys.exit(f"fence side {'+-'[sign < 0]}{'xy'[axis]} missing")
        inner = min(sign * (c["lo"][axis] if sign > 0 else c["hi"][axis]) - sign * centre[axis] for c in cand)
        outer_s = max(sign * (c["hi"][axis] if sign > 0 else c["lo"][axis]) - sign * centre[axis] for c in cand)
        return inner, outer_s

    sides = {f"{'+-'[s < 0]}{'xy'[a]}": side(a, s) for a in (0, 1) for s in (1, -1)}
    inner = np.array([0.5 * (sides["+x"][0] + sides["-x"][0]), 0.5 * (sides["+y"][0] + sides["-y"][0])])
    mid = 0.5 * (inner + outer)
    thickness = {k: v[1] - v[0] for k, v in sides.items()}

    # Gates: walk the midline rectangle; a sample is covered if it lies in any piece footprint
    corners = [centre + mid * np.array(s) for s in ((1, 1), (-1, 1), (-1, -1), (1, -1))]
    samples, arc = [], []
    s_acc = 0.0
    for a, b in zip(corners, corners[1:] + corners[:1]):
        seg = np.linalg.norm(b - a)
        n = int(np.ceil(seg / STEP))
        for i in range(n):
            samples.append(a + (b - a) * (i / n))
            arc.append(s_acc + seg * i / n)
        s_acc += seg
    samples = np.array(samples)
    covered = np.zeros(len(samples), bool)
    for c in pieces:
        covered |= np.all((samples >= c["lo"][:2] - 1e-9) & (samples <= c["hi"][:2] + 1e-9), axis=1)
    gates = []
    if not covered.all():
        start = int(np.argmax(covered))  # begin the scan on a covered sample so runs don't wrap
        run = []
        for k in range(len(samples) + 1):
            i = (start + k) % len(samples)
            if not covered[i] and k < len(samples):
                run.append(i)
            elif run:
                pts = samples[run]
                gates.append((0.5 * (pts[0] + pts[-1]), len(run) * STEP))
                run = []

    out = [
        f"stadium.obj pitch fence (tools/measure_fence.py)",
        f"  components: {len(comps)} (by OBJ vertex index); pitch floor x[{pitch_lo[0]:+.6f},{pitch_hi[0]:+.6f}] y[{pitch_lo[1]:+.6f},{pitch_hi[1]:+.6f}]",
        f"  fence pieces: {len(pieces)} axis-aligned boxes",
    ]
    for c in pieces:
        out.append(f"    x[{c['lo'][0]:+.6f},{c['hi'][0]:+.6f}] y[{c['lo'][1]:+.6f},{c['hi'][1]:+.6f}] z[{c['lo'][2]:.6f},{c['hi'][2]:.6f}]")
    out += [
        f"  center             ({centre[0]:+.6f}, {centre[1]:+.6f})",
        f"  outer half-extents ({outer[0]:.6f}, {outer[1]:.6f})",
        f"  inner half-extents ({inner[0]:.6f}, {inner[1]:.6f})",
        f"  midline half-ext.  ({mid[0]:.6f}, {mid[1]:.6f})",
        "  thickness          " + ", ".join(f"{k} {v:.6f}" for k, v in thickness.items()),
        f"  z_min, z_max       {lo[2]:.6f}, {hi[2]:.6f}",
        f"  gates              {len(gates)} (midline perimeter {s_acc:.6f} sampled every {STEP})",
    ]
    for g, w in gates:
        out.append(f"    gate at ({g[0]:+.6f}, {g[1]:+.6f}) width {w:.6f}")
    print("\n".join(out))


if __name__ == "__main__":
    main()
