# GPU e_goal against the CPU mirror at test_gpu's points (Task 5.10 stage 1)

nav_probe goaldiff | commit 782fb03dc9cbb3d8b048d18bc717960d1779f977 (dirty 0) | Release | 2026-10-22 18:02 | venue S | variant precise-bounds

Driver: AMD  Radeon RX 7800 XT | 4.3.0 Core Profile Context 26.10.1.261008

## The cell table on the GPU at run time

vsBand / vsCell / vsCellTop for every band and cell (indices from the invocation id) against seated::band / cell / cellTop: 40 bands, 222 cells; bands with a differing bound 0, cells with a differing bound or top 36, cells of another kind, row or count 0; the largest difference 3e-08 model units (criterion (4): at most 1.2e-07: PASS), 1 ulp(s) of a bound. Each distinct differing bound:

| bound | CPU | GPU | ulps | where (band: cell) |
|---|---:|---:|---:|---|
| cell l1 | 0.375359982 | 0.375360012 | 1 | 1: 3, 1: 4, 3: 3, 3: 4, 5: 3, 5: 4, 7: 3, 7: 4, 9: 3, 9: 4, 11: 3, 11: 4, 13: 3, 13: 4 |

The layout's literals (seatedDefines):

```
#define VS_STAND_FRONT 0.419592
#define VS_ROW0 0.429192
#define VS_ROW_DEPTH 0.0256
#define VS_CLEARWAY 0.016
#define VS_ROWS 17
#define VS_CONC_FRONT 0.864392
#define VS_CONC_BACK 0.960392
#define VS_OUTER_FACE 0.969992
#define VS_LANDING_END 0.98599195
#define VS_AVENUE_HALF 0.09056
#define VS_LAT0 0.100159995
#define VS_GANGWAY_LO 0.33056
#define VS_GANGWAY_HI 0.36896
#define VS_EXIT_LO 0.33056
#define VS_EXIT_HI 0.36896
#define VS_CORNER_INSET 0.0303529
#define VS_SEAT_INSET 0.0064
#define VS_FACE_MARGIN 9.6e-06
#define VS_WALL_ABOVE 0.0064
#define VS_WALL_CLEAR 0.0064096
#define VS_FIRST_ROW 0.008
#define VS_ROW_RISE 0.0128
#define VS_SEAT_TOP 0.0272
#define VS_BARRIER_TOP 0.0352
#define VS_CONC_Z 0.21759999
#define VS_WALL_TOP 0.2528
#define VS_RAKE 0.5
#define VS_MAX_BAND_STEPS 4
#define VS_SCAN_CROSSINGS 4
#define VS_SCAN_BISECTIONS 12
```

## navGoal (section 42: seed 23)

FEELER_REACH = 0.00800000038 (0x3c03126f); FEELER_REACH^2: GPU (compiler) 6.39999998e-05 (0x388637bd), CPU float product 6.40000071e-05 (0x388637be), the exact product rounded once 6.40000071e-05 (0x388637be)

53728 points (50 000 random plan points at the rest height, every seat); 12715 closer to a wall than BODY_RADIUS - 3e-4 (excluded, as in the test); compared 41013, bit-identical 27494. The field's direction alone: max |GPU - CPU| 1.9e-07 (22732 points not bit-identical).

| \|GPU - CPU\| | 0 | (0, 1e-7] | (1e-7, 1e-6] | (1e-6, 1e-5] | (1e-5, 1e-4] | (1e-4, 1e-3] | (1e-3, 1e-2] | (1e-2, 0.1] | (0.1, 1] | > 1 |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| points | 27494 | 11568 | 1932 | 19 | 0 | 0 | 0 | 0 | 0 | 0 |

How many of the compared points lie within a distance of each decision (CPU margins; the share a bound would allow):

| margin below | 1e-8 | 1e-7 | 1e-6 | 1e-5 | 1e-4 |
|---|---:|---:|---:|---:|---:|
| \|d - FEELER_REACH\| (model units) | 0 | 3728 | 3731 | 3752 | 3999 |
| nearest other face - nearest face (model units) | 0 | 3729 | 3740 | 3777 | 3948 |
| \|into\| (a face within reach) | 63 | 63 | 64 | 67 | 94 |
| projected length l below 1e4 x the margin (1e-4 ... 1) | 0 | 0 | 0 | 3 | 3850 |

**The criterion (tools/nav_goal_check.hpp): PASS.** (1) away from every decision (37279 of 41013 points; margins > 2.5e-07 model units, projected length >= 0.01): max |GPU - CPU| 4.5e-06 (<= 1e-05; there the projected length 0.976); (2) points beyond 1e-05: 0 (random 0, seats 0), at a decision 0; the GPU's value is the CPU's on the decision's other side: the reach moved by 2.5e-07 0, the point moved by at most 4 ulps 0 (largest 0), neither 0; (3) random points differing 0 of 37285 (at most 0.1%); at a decision: 3734 points, 6 of them random

Points with \|GPU - CPU\| > 1e-5 (or a zero on one side only): 0 ().

## navChoiceGoal (section 45 (c): seed 29, each point asking for one of its cell's first 5 candidates)

FEELER_REACH = 0.00800000038 (0x3c03126f); FEELER_REACH^2: GPU (compiler) 6.39999998e-05 (0x388637bd), CPU float product 6.40000071e-05 (0x388637be), the exact product rounded once 6.40000071e-05 (0x388637be)

53728 points (50 000 random plan points at the rest height, every seat); 12596 closer to a wall than BODY_RADIUS - 3e-4 (excluded, as in the test); compared 41132, bit-identical 18257. The field's direction alone: max |GPU - CPU| 2.1e-07 (31142 points not bit-identical).

| \|GPU - CPU\| | 0 | (0, 1e-7] | (1e-7, 1e-6] | (1e-6, 1e-5] | (1e-5, 1e-4] | (1e-4, 1e-3] | (1e-3, 1e-2] | (1e-2, 0.1] | (0.1, 1] | > 1 |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| points | 18257 | 19910 | 2955 | 10 | 0 | 0 | 0 | 0 | 0 | 0 |

How many of the compared points lie within a distance of each decision (CPU margins; the share a bound would allow):

| margin below | 1e-8 | 1e-7 | 1e-6 | 1e-5 | 1e-4 |
|---|---:|---:|---:|---:|---:|
| \|d - FEELER_REACH\| (model units) | 0 | 3728 | 3729 | 3752 | 3981 |
| nearest other face - nearest face (model units) | 2 | 3733 | 3739 | 3775 | 3933 |
| \|into\| (a face within reach) | 0 | 0 | 1 | 1 | 25 |
| projected length l below 1e4 x the margin (1e-4 ... 1) | 0 | 0 | 0 | 1 | 2123 |

**The criterion (tools/nav_goal_check.hpp): PASS.** (1) away from every decision (37398 of 41132 points; margins > 2.5e-07 model units, projected length >= 0.01): max |GPU - CPU| 4.4e-06 (<= 1e-05; there the projected length 0.998); (2) points beyond 1e-05: 0 (random 0, seats 0), at a decision 0; the GPU's value is the CPU's on the decision's other side: the reach moved by 2.5e-07 0, the point moved by at most 4 ulps 0 (largest 0), neither 0; (3) random points differing 0 of 37404 (at most 0.1%); at a decision: 3734 points, 6 of them random

Points with \|GPU - CPU\| > 1e-5 (or a zero on one side only): 0 ().

