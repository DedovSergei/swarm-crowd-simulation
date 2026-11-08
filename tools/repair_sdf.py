"""Repair the signs of a mesh-to-sdf bake of the stadium and add a CSG ground plane.

stadium.sdf was produced by:
    voxels = mesh_to_sdf.mesh_to_voxels(mesh, voxel_resolution=128, pad=True)
    voxels.astype(np.float32).tofile('stadium.sdf')

Layout of that raw bake:
  * 130^3 float32, NumPy C-order [x][y][z] (z is the fastest-varying axis).
  * Interior 128^3 node grid = np.linspace(-1, 1, 128) per axis in mesh-to-sdf's
    unit-cube space, plus a 1-voxel pad shell filled with 1.0.
  * Unit-cube space: world = bbox_centre + n * (max_extent / 2) (scale_to_unit_cube),
    and distances are scaled by the same factor.
  * Magnitudes |d| are correct, but signs are corrupt: stadium.obj has open edges and
    inconsistent winding, which breaks mesh-to-sdf's inside/outside test.

This tool:
  1. Keeps |d| and converts it to world units (x max_extent/2). The constant pad shell
     is replaced by edge replication of the interior.
  2. Recomputes the sign top-down from the open air above the stadium (+Z): a voxel is
     solid iff it lies below the topmost mesh surface of its vertical column (majority
     vote over a few jittered rays per column), i.e. the stadium is treated as a
     heightfield, which it is: no column has a real overhang.
     A 3D 6-connected flood fill from +Z does NOT work on this mesh: the stands are a
     stepped shell over a cavity that is open to the outside, so the fill leaks in and
     every voxel ends up "outside". Crossing-count parity does NOT work either: each
     step's lip sits on a tread face that continues underneath it, so rays through a lip
     see an odd number of surfaces and flip every voxel below (this left 1-voxel air
     shafts down the stand diagonals that trapped agents).
     |d| is additionally bounded by the distance to the voxelized solid's boundary, which
     closes faces the mesh leaves open without breaking continuity.
  3. Unions an analytic ground half-space z < 0: d = min(d_stands, z).
  4. Writes the result back in the same [x][y][z] float32 layout (world units).

Usage:
    python tools/repair_sdf.py [--sdf stadium.sdf] [--obj stadium.obj] [--out stadium.sdf]
Requires numpy and scipy.
"""

import argparse
import sys

import numpy as np
from scipy import ndimage

RES = 128          # mesh_to_voxels voxel_resolution
N = RES + 2        # with pad=True


def load_obj_triangles(path):
    verts, tris = [], []
    with open(path) as f:
        for line in f:
            if line.startswith("v "):
                verts.append([float(t) for t in line.split()[1:4]])
            elif line.startswith("f "):
                ids = [int(t.split("/")[0]) for t in line.split()[1:]]
                ids = [i - 1 if i > 0 else len(verts) + i for i in ids]
                for j in range(1, len(ids) - 1):
                    tris.append((ids[0], ids[j], ids[j + 1]))
    v = np.asarray(verts, dtype=np.float64)
    return v, v[np.asarray(tris)]


def column_solid_mask(tri, xs, ys, zs, jitter):
    """solid[i, j, k]: True if (xs[i], ys[j], zs[k]) is below the topmost surface of its column."""
    nx, ny = len(xs), len(ys)
    dx, dy = xs[1] - xs[0], ys[1] - ys[0]
    votes = np.zeros((nx, ny, len(zs)), dtype=np.int32)
    A, B, C = tri[:, 0], tri[:, 1], tri[:, 2]
    e0, e1 = B[:, :2] - A[:, :2], C[:, :2] - A[:, :2]
    den = e0[:, 0] * e1[:, 1] - e1[:, 0] * e0[:, 1]
    flat = np.abs(den) > 1e-14            # vertical triangles never cross a vertical ray
    for ox, oy in jitter:
        hits = [[[] for _ in range(ny)] for _ in range(nx)]
        for t in np.nonzero(flat)[0]:
            lo = tri[t, :, :2].min(0)
            hi = tri[t, :, :2].max(0)
            i0 = max(int(np.ceil((lo[0] - xs[0] - ox) / dx)), 0)
            i1 = min(int(np.floor((hi[0] - xs[0] - ox) / dx)), nx - 1)
            j0 = max(int(np.ceil((lo[1] - ys[0] - oy) / dy)), 0)
            j1 = min(int(np.floor((hi[1] - ys[0] - oy) / dy)), ny - 1)
            if i0 > i1 or j0 > j1:
                continue
            I, J = np.meshgrid(np.arange(i0, i1 + 1), np.arange(j0, j1 + 1), indexing="ij")
            px = xs[I] + ox - A[t, 0]
            py = ys[J] + oy - A[t, 1]
            u = (px * e1[t, 1] - e1[t, 0] * py) / den[t]
            v = (e0[t, 0] * py - px * e0[t, 1]) / den[t]
            inside = (u >= 0) & (v >= 0) & (u + v <= 1)
            z = A[t, 2] + u * (B[t, 2] - A[t, 2]) + v * (C[t, 2] - A[t, 2])
            for i, j, zz in zip(I[inside], J[inside], z[inside]):
                hits[i][j].append(zz)
        for i in range(nx):
            for j in range(ny):
                if hits[i][j]:
                    votes[i, j] += zs < max(hits[i][j])       # internal faces below the top don't matter
    return votes * 2 > len(jitter)


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--sdf", default="stadium.sdf", help="raw mesh-to-sdf bake (input)")
    ap.add_argument("--obj", default="stadium.obj", help="mesh the bake was generated from")
    ap.add_argument("--out", default="stadium.sdf", help="output path (default: overwrite input)")
    args = ap.parse_args()

    raw = np.fromfile(args.sdf, dtype=np.float32)
    if raw.size != N**3:
        sys.exit(f"{args.sdf}: expected {N**3} floats ({N}^3), got {raw.size}")
    raw = raw.reshape(N, N, N)

    shell = np.concatenate([raw[[0, -1]].ravel(), raw[:, [0, -1]].ravel(), raw[:, :, [0, -1]].ravel()])
    if not np.all(shell == 1.0):
        sys.exit(f"{args.sdf}: pad shell is not all 1.0 -- this is not a raw mesh-to-sdf bake "
                 "(already repaired?). Restore the raw file before re-running.")

    # --- Grid geometry (mesh-to-sdf scale_to_unit_cube + linspace(-1, 1, RES) + 1-voxel pad) ---
    verts, tri = load_obj_triangles(args.obj)
    lo, hi = verts.min(0), verts.max(0)
    centre = (lo + hi) / 2.0
    scale = float((hi - lo).max()) / 2.0             # world units per unit-cube unit
    spacing = 2.0 / (RES - 1) * scale                 # world distance between samples
    axis_n = -1.0 + (np.arange(N) - 1) * (2.0 / (RES - 1))
    wx = centre[0] + axis_n * scale                   # world coordinate of each index
    wy = centre[1] + axis_n * scale
    wz = centre[2] + axis_n * scale
    sdf_min = centre - scale                          # world position of sample (1, 1, 1)

    mag = np.abs(raw).astype(np.float64) * scale      # |d| in world units
    # The pad shell is a constant 1.0 placeholder; replicate the edge so the field stays continuous
    mag = np.pad(mag[1:-1, 1:-1, 1:-1], 1, mode="edge")

    # --- Sign from the sky, top-down along each column ---
    # Off-grid jitter keeps rays off the grid-aligned edges of the stadium geometry.
    jitter = [(0.0, 0.0), (0.31, 0.17), (-0.23, 0.29), (0.19, -0.33), (-0.27, -0.21)]
    jitter = [(ox * spacing, oy * spacing) for ox, oy in jitter]
    solid = column_solid_mask(tri, wx, wy, wz, jitter)
    # Parity counts the floor as a surface, which makes it meaningless below z = 0;
    # the CSG ground half-space owns that region instead.
    solid &= (wz > 0.0)[None, None, :]

    # Where the mesh leaves a solid open (e.g. the sides of the cavity under the treads)
    # |d| knows nothing about that face. Bound |d| by the distance to the voxelized solid's
    # boundary so the field stays continuous (1-Lipschitz) across those virtual faces.
    to_solid = ndimage.distance_transform_edt(~solid) * spacing - 0.5 * spacing
    to_air = ndimage.distance_transform_edt(solid) * spacing - 0.5 * spacing
    boundary = np.where(solid, to_air, to_solid)
    virtual = boundary < mag - spacing
    mag = np.minimum(mag, boundary)

    d_stands = np.where(solid, -mag, mag)

    # --- CSG union with the ground half-space z < 0 ---
    d = np.minimum(d_stands, wz[None, None, :])

    # --- Verification ---
    h = spacing
    bad = 0
    for ax in range(3):
        bad += int(np.count_nonzero(np.abs(np.diff(d, axis=ax)) > 1.01 * h))
    X, Y, Z = np.meshgrid(wx, wy, wz, indexing="ij")
    air = (np.abs(X) < 0.2) & (np.abs(Y) < 0.2) & (Z > 0.5 * h) & (Z < 0.9)
    ground = Z < -0.5 * h
    above = Z > hi[2] + h
    print(f"grid: SDF_MIN = ({sdf_min[0]:.7f}, {sdf_min[1]:.7f}, {sdf_min[2]:.7f}), "
          f"spacing = {spacing:.7f}, distance scale applied = {scale:.6f}")
    stand_zone = (Z > 0.5 * h) & (Z < hi[2])
    print(f"sign: {np.count_nonzero(solid & stand_zone)} solid stand voxels above ground, "
          f"{np.count_nonzero(d < 0)} negative after CSG ground")
    print(f"magnitude: {np.count_nonzero(virtual)} voxels bounded by open-mesh (virtual) faces")
    print(f"check: neighbour jumps > 1 voxel (non-Lipschitz): {bad}")
    print(f"check: open air above pitch positive: {np.mean(d[air] > 0) * 100:.2f}%")
    print(f"check: above all geometry positive:   {np.mean(d[above] > 0) * 100:.2f}%")
    print(f"check: subterranean negative:         {np.mean(d[ground] < 0) * 100:.2f}%")

    d.astype(np.float32).tofile(args.out)
    print(f"wrote {args.out} ({N}^3 float32, [x][y][z], world units)")


if __name__ == "__main__":
    main()
