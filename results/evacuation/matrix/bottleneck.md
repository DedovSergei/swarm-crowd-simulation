# Bottleneck analysis (stair spacing EMPIRICAL)

Runs: 41 in results/evacuation/matrix; GPU driver: 4.3.0 Core Profile Context 26.10.1.261008 (41 runs); run_experiment built at: 49b5a27 (11 runs), b6a7874 (30 runs).

From the geometry and the matrix's runs. Definitions: tools/figures/bottleneck.py (header). Runs: results/evacuation/matrix; travel bounds results/validation/navigation/<V>/travel.json; row segments results/validation/venues/<V>/catchments.csv.

## Measured flows

- **Door flow J_door = 83.3 persons/(m min)** (the door capacity): venue S at 100% before the stair calibration (results/evacuation/matrix_before_calibration), the mean over its 8 doors of their mean specific flows, where the doors ran at their capacity. With the stair spacing the gangways feed every venue's doors below it; the same measure in this matrix (door utilisation = it / J_door): S 63.8 (0.77), M 43.3 (0.52), L 23.8 (0.29).
- **Sustained gangway flow q_gw = 1.575 persons/(m s) = 94.5 persons/(m min)**: the straight gangways' outflow per metre in their saturated 10 s windows, pooled over S, M, L at 100%; the corner gangways: 1.400 persons/(m s) (84.0).

| venue | gangway type | saturated windows | mean [p/(m s)] | median [p/(m s)] | mean [p/(m min)] |
|---|---|---:|---:|---:|---:|
| S | straight | 152 | 1.973 | 1.923 | 118.4 |
| S | corner | 0 | - | - | - |
| M | straight | 644 | 1.620 | 1.421 | 97.2 |
| M | corner | 128 | 1.308 | 1.003 | 78.5 |
| L | straight | 2982 | 1.545 | 1.254 | 92.7 |
| L | corner | 372 | 1.431 | 1.337 | 85.9 |

Straight gangways by outlet: gangway 0, the wing's first, empties at both ends (concourse and walkway) and into the corner gangway where they merge; in M and L the other straight gangways have one outlet, the head (the in-situ counterpart of the stair harness's ascending maximum). S has gangway 0 only (both ends).

| venue | straight gangways | saturated windows | mean [p/(m s)] | mean [p/(m min)] |
|---|---|---:|---:|---:|
| S | straight 0 | 152 | 1.973 | 118.4 |
| S | straight >= 1 | 0 | - | - |
| M | straight 0 | 325 | 2.119 | 127.1 |
| M | straight >= 1 | 319 | 1.111 | 66.7 |
| L | straight 0 | 813 | 2.452 | 147.1 |
| L | straight >= 1 | 2169 | 1.205 | 72.3 |

Pooled single-outlet straight gangways (M, L): **1.193 persons/(m s) = 71.6 persons/(m min)**.

## Gangway flow against stair planning flows

| source (as reported there; not yet checked against the original) | persons/(m min) | the model's sustained gangway flow / it |
|---|---:|---:|
| Guide to Safety at Sports Grounds (Green Guide), 6th ed. 2018: maximum rate of passage on stepped surfaces (the exit sizing rule of venues S, M, L; the CONSERVATIVE target) | 66.0 | 94 / 66 = 1.43x |
| Green Guide, earlier editions: 40 persons per 550 mm unit width per minute on stairways | 72.7 | 94 / 73 = 1.30x |
| Burghardt, Seyfried & Klingsch (2013): measured maximum specific flow on stairs, ascending 1.22 persons/(m s) (the EMPIRICAL target) | 73.2 | 94 / 73 = 1.29x |
| the same, descending 1.25 persons/(m s) | 75.0 | 94 / 75 = 1.26x |
| Fruin (1971), Highway Research Record 355: measured stair maxima 18.9 (up) / 20.0 (down) persons/(ft min); here ascending | 62.0 | 94 / 62 = 1.52x |
| Fruin (1971): stairway level of service E's upper bound (17 persons/(ft min)) | 55.8 | 94 / 56 = 1.69x |
| SFPE Handbook (Gwynne & Rosenbaum): stairs 7/11 in, maximum specific flow 1.01 persons/(s m) of EFFECTIVE width | 60.6 | 94 / 61 = 1.56x |
| the same, per metre of a 1.20 m gangway's CLEAR width (effective width 1.20 - 2 x 0.15 m) | 45.5 | 94 / 45 = 2.08x |
| **the model: straight gangways' sustained flow** (26.57 deg incline; free speed up 0.58 / down 0.655 m/s) | **94.5** | |
| the model: single-outlet straight gangways (M, L; one cross-section, ascending) | 71.6 | |

## Capacity lower bounds and efficiency

| venue | case | N (seated) | (a) exits [s] | (b) gangways [s] | (c) travel [s] | **t_lb** [s] (binding) | t100 [s] | **t100 / t_lb** | (b) with the venue's own q [s] |
|---|---|---|---:|---:|---:|---:|---:|---:|---:|
| S | 100% | 3728 (3728) | 83.2 | 164.4 | 27.1 | **164.4** (b) | 238.2 | **1.45** | 131.2 |
| S | 95% (3 seeds) | 3542 (3542) | 79.1 | 156.2 | 27.1 | **156.2** (b) | 229.7 (225.5-232.1) | **1.47 (1.44-1.49)** | 124.7 |
| S | 125% (3 seeds) | 4660 (3728) | 104.1 | 164.4 | 27.1 | **164.4** (b) | 254.0 (251.3-256.2) | **1.55 (1.53-1.56)** | 131.2 |
| S | 150% (3 seeds) | 5592 (3728) | 124.9 | 164.4 | 27.1 | **164.4** (b) | 291.0 (282.1-296.6) | **1.77 (1.72-1.80)** | 131.2 |
| S | 150%, standing also on the gangways (3 seeds) | 5592 (3728) | 124.9 | 164.4 | 27.1 | **164.4** (b) | 299.1 (295.1-301.4) | **1.82 (1.79-1.83)** | 131.2 |
| S | 100%, nearest exit | 3728 (3728) | 83.2 | 164.4 | 27.1 | **164.4** (b) | 362.1 | **2.20** | 131.2 |
| S | 100%, CONSERVATIVE stair spacing | 3728 (3728) | 83.2 | 164.4 | 27.1 | **164.4** (b) | 253.6 | **1.54** | 131.2 |
| M | 100% | 15832 (15832) | 202.7 | 299.2 | 52.3 | **299.2** (b) | 563.4 | **1.88** | 290.9 |
| M | 95% (3 seeds) | 15040 (15040) | 192.5 | 284.2 | 52.3 | **284.2** (b) | 534.2 (531.5-536.6) | **1.88 (1.87-1.89)** | 276.3 |
| M | 125% / 150% requested: the achievable maximum (3 seeds) | 19223 (15832) | 246.1 | 299.2 | 52.3 | **299.2** (b) | 590.0 (585.8-592.4) | **1.97 (1.96-1.98)** | 290.9 |
| M | 100%, nearest exit | 15832 (15832) | 202.7 | 299.2 | 52.3 | **299.2** (b) | 857.2 | **2.87** | 290.9 |
| M | 100%, CONSERVATIVE stair spacing | 15832 (15832) | 202.7 | 299.2 | 52.3 | **299.2** (b) | 591.0 | **1.98** | 290.9 |
| L | 100% | 63424 (63424) | 368.7 | 762.7 | 102.8 | **762.7** (b) | 1477.4 | **1.94** | 777.5 |
| L | 95% (3 seeds) | 60253 (60253) | 350.3 | 724.6 | 102.8 | **724.6** (b) | 1453.9 (1423.9-1507.9) | **2.01 (1.97-2.08)** | 738.6 |
| L | 125% / 150% requested: the achievable maximum (3 seeds) | 69311 (63424) | 402.9 | 762.7 | 102.8 | **762.7** (b) | 1523.4 (1512.1-1532.0) | **2.00 (1.98-2.01)** | 777.5 |
| L | 100%, nearest exit | 63424 (63424) | 368.7 | 762.7 | 102.8 | **762.7** (b) | 1958.3 | **2.57** | 777.5 |
| L | 100%, CONSERVATIVE stair spacing | 63424 (63424) | 368.7 | 762.7 | 102.8 | **762.7** (b) | 1588.5 | **2.08** | 777.5 |
| M | 100%, DT / 2 | 15832 (15832) | 202.7 | 299.2 | 52.3 | **299.2** (b) | 555.5 | **1.86** | 290.9 |

Exit widths: S 32.24 m (8 doors 1.20 m + 4 avenues 5.66 m), M 56.24 m (28 doors + avenues), L 123.84 m (44 doors 2.30 m + avenues); gangway widths: 12 / 28 / 44 gangways of 1.20 m. (b) with the venue's own q: the venue's straight gangways' sustained flow at 100% instead of the pooled model value (sensitivity).

## Gangway load imbalance and the counterfactuals

Capacities c_g: the run's pooled sustained flow of the gangway's type x 1.20 m. T: the slowest gangway's service time people_g / c_g. (1) every gangway the mean load; (2) the least slowest service time any split of each row segment between its two end gangways attains (100%, 95%, nearest only: their gangway users are the seated agents).

| venue | case | people per gangway: mean | max / mean (all; straight; corner) | CV (all; straight; corner) | capacity straight / corner [p/s] | slowest gangway: people, T [s] | (1) mean load: T' [s], **t100_cf** [s] (saved) | (2) attainable: T' [s], **t100_cf** [s] (saved) | t100 [s] |
|---|---|---:|---|---|---|---|---|---|---:|
| S | 100% | 311 | 1.49; 1.00; 1.00 | 0.70; 0.00; 0.00 | 2.37 / 1.68 | straight +x+y (y wing) 0: 464, 196 | 185, **227.2** (5%) | 145, **187.5** (21%) | 238.2 |
| S | 95% (3 seeds) | 295 | 1.52 (1.50-1.52); 1.01 (1.01-1.02); 1.50 (1.33-1.67) | 0.70; 0.01; 0.40 (0.35-0.47) | 2.38 (2.37-2.40) / 1.68 | straight +x-y (x wing) 0: 449, 188 (187-189) | 176, **217.7 (214.0-221.1)** (5 (5-6)%) | 137 (137-138), **179.3 (175.0-183.0)** (22 (21-22)%) | 229.7 (225.5-232.1) |
| S | 125% (3 seeds) | 313 | 1.49 (1.48-1.49); 1.01 (1.00-1.01); 1.19 (1.12-1.31) | 0.68 (0.67-0.68); 0.00 (0.00-0.01); 0.19 (0.09-0.37) | 2.23 (2.22-2.24) / 1.68 | straight +x+y (x wing) 0: 468, 209 | 187, **231.8 (228.9-234.0)** (9%) | - | 254.0 (251.3-256.2) |
| S | 150% (3 seeds) | 318 | 1.43 (1.42-1.43); 1.01; 1.08 (1.05-1.13) | 0.59 (0.59-0.60); 0.01 (0.00-0.01); 0.06 (0.04-0.09) | 1.89 (1.88-1.90) / 1.68 | straight +x+y (x wing) 0: 455, 240 (240-241) | 189, **239.8 (231.8-244.7)** (18 (17-18)%) | - | 291.0 (282.1-296.6) |
| S | 150%, standing also on the gangways (3 seeds) | 350 (348-351) | 1.38 (1.38-1.39); 1.01 (1.00-1.01); 1.08 (1.04-1.11) | 0.53 (0.53-0.54); 0.00 (0.00-0.01); 0.06 (0.04-0.07) | 1.96 (1.95-1.98) / 0.91 (0.53-1.68) | straight +x+y (y wing) 0: 485, 247 (245-249) | 509 (207-664), **561.6 (253.3-719.2)** (-87 (-139-14)%) | - | 299.1 (295.1-301.4) |
| S | 100%, nearest exit | 311 | 1.50; 1.00; - | 0.71; 0.00; - | 1.34 / 1.68 | straight +x+y (y wing) 0: 466, 348 | 232, **246.0** (32%) | 214, **227.8** (37%) | 362.1 |
| S | 100%, CONSERVATIVE stair spacing | 311 | 1.50; 1.00; 1.00 | 0.70; 0.00; 0.00 | 2.21 / 1.68 | straight +x+y (y wing) 0: 465, 211 | 185, **227.7** (10%) | 153, **195.8** (23%) | 253.6 |
| M | 100% | 565 | 1.70; 1.82; 1.01 | 0.61; 0.69; 0.01 | 1.94 / 1.57 | corner -x-y: 790, 503 | 360, **420.3** (25%) | 397, **457.1** (19%) | 563.4 |
| M | 95% (3 seeds) | 537 | 1.70 (1.69-1.71); 1.82 (1.81-1.82); 1.02 (1.02-1.03) | 0.61; 0.68 (0.68-0.69); 0.01 (0.01-0.02) | 1.95 (1.94-1.96) / 1.60 (1.59-1.61) | corner -x-y: 770, 480 (479-481) | 336 (335-338), **390.5 (389.3-391.3)** (27 (26-27)%) | 375 (374-376), **429.6 (427.1-432.2)** (20 (19-20)%) | 534.2 (531.5-536.6) |
| M | 125% / 150% requested: the achievable maximum (3 seeds) | 567 (566-567) | 1.70 (1.70-1.71); 1.82 (1.81-1.82); 1.01 (1.01-1.02) | 0.61; 0.67 (0.67-0.68); 0.01 | 1.73 (1.72-1.74) / 1.53 (1.52-1.55) | straight -x-y (x wing) 0: 970, 559 (558-560) | 370 (365-373), **401.2 (392.4-406.1)** (32 (31-33)%) | - | 590.0 (585.8-592.4) |
| M | 100%, nearest exit | 565 | 1.98; 1.92; 1.00 | 0.71; 0.74; 0.00 | 1.33 / 1.42 | straight +x+y (y wing) 0: 1121, 841 | 424, **440.2** (49%) | 549, **565.1** (34%) | 857.2 |
| M | 100%, CONSERVATIVE stair spacing | 565 | 1.71; 1.82; 1.01 | 0.61; 0.69; 0.01 | 1.81 / 1.50 | straight -x-y (x wing) 0: 965, 532 | 377, **436.4** (26%) | 424, **482.9** (18%) | 591.0 |
| L | 100% | 1441 | 1.63; 1.66; 1.03 | 0.46; 0.48; 0.02 | 1.85 / 1.72 | straight -x+y (y wing) 0: 2350, 1268 | 839, **1049.1** (29%) | 925, **1135.0** (23%) | 1477.4 |
| L | 95% (3 seeds) | 1369 | 1.63 (1.63-1.64); 1.67 (1.67-1.68); 1.02 | 0.46; 0.49; 0.01 (0.01-0.02) | 1.85 (1.84-1.86) / 1.77 (1.74-1.80) | straight +x-y (x wing) 0: 2247, 1210 (1204-1215) | 773 (761-787), **1017.3 (981.6-1068.8)** (30 (29-31)%) | 880 (877-886), **1124.7 (1098.5-1175.2)** (23 (22-23)%) | 1453.9 (1423.9-1507.9) |
| L | 125% / 150% requested: the achievable maximum (3 seeds) | 1442 | 1.66; 1.70; 1.02 (1.01-1.03) | 0.46; 0.49; 0.02 (0.01-0.02) | 1.80 (1.78-1.81) / 1.49 (1.44-1.54) | straight -x-y (x wing) 0: 2401, 1332 (1324-1348) | 967 (937-1001), **1158.3 (1124.8-1202.9)** (24 (21-26)%) | - | 1523.4 (1512.1-1532.0) |
| L | 100%, nearest exit | 1441 | 1.79; 1.74; 1.00 | 0.52; 0.52; 0.00 | 1.33 / 0.95 | straight +x+y (y wing) 0: 2577, 1940 | 1524, **1542.5** (21%) | 1328, **1346.0** (31%) | 1958.3 |
| L | 100%, CONSERVATIVE stair spacing | 1441 | 1.62; 1.65; 1.01 | 0.46; 0.48; 0.00 | 1.75 / 1.69 | straight +x+y (x wing) 0: 2332, 1330 | 854, **1112.7** (30%) | 978, **1236.7** (22%) | 1588.5 |
| M | 100%, DT / 2 | 565 | 1.69; 1.80; 1.01 | 0.61; 0.68; 0.01 | 1.81 / 1.65 | straight -x+y (x wing) 0: 954, 527 | 343, **371.8** (33%) | 417, **445.9** (20%) | 555.5 |

