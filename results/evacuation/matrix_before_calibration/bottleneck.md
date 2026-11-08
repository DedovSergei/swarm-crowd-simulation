# Bottleneck analysis (the level spacing on the gangways)

Runs: 30 in results/evacuation/matrix_before_calibration; GPU driver: 4.3.0 Core Profile Context 26.10.1.261008 (30 runs); run_experiment built at: b6a7874 (30 runs).

From the geometry and the matrix's runs. Definitions: tools/figures/bottleneck.py (header). Runs: results/evacuation/matrix_before_calibration; travel bounds results/validation/navigation/<V>/travel.json; row segments results/validation/venues/<V>/catchments.csv.

## Measured flows

- **Door flow J_door = 83.3 persons/(m min)**: venue S at 100% (default model), the mean over its 8 doors of their mean specific flows (S's doors run at their capacity). The same measure in M / L, whose doors their gangways feed below capacity: M 56.2, L 30.2.
- **Sustained gangway flow q_gw = 2.018 persons/(m s) = 121.1 persons/(m min)**: the straight gangways' outflow per metre in their saturated 10 s windows, pooled over S, M, L at 100%; the corner gangways: 1.596 persons/(m s) (95.8).

| venue | gangway type | saturated windows | mean [p/(m s)] | median [p/(m s)] | mean [p/(m min)] |
|---|---|---:|---:|---:|---:|
| S | straight | 112 | 2.588 | 2.591 | 155.3 |
| S | corner | 0 | - | - | - |
| M | straight | 507 | 2.097 | 1.755 | 125.8 |
| M | corner | 109 | 1.571 | 1.170 | 94.2 |
| L | straight | 2426 | 1.976 | 1.588 | 118.5 |
| L | corner | 301 | 1.605 | 1.505 | 96.3 |

Straight gangways by outlet: gangway 0, the wing's first, empties at both ends (concourse and walkway) and into the corner gangway where they merge; in M and L the other straight gangways have one outlet, the head (the in-situ counterpart of the stair harness's ascending maximum). S has gangway 0 only (both ends).

| venue | straight gangways | saturated windows | mean [p/(m s)] | mean [p/(m min)] |
|---|---|---:|---:|---:|
| S | straight 0 | 112 | 2.588 | 155.3 |
| S | straight >= 1 | 0 | - | - |
| M | straight 0 | 248 | 2.715 | 162.9 |
| M | straight >= 1 | 259 | 1.505 | 90.3 |
| L | straight 0 | 616 | 3.151 | 189.0 |
| L | straight >= 1 | 1810 | 1.576 | 94.6 |

Pooled single-outlet straight gangways (M, L): **1.567 persons/(m s) = 94.0 persons/(m min)**.

## Gangway flow against stair planning flows

| source (as reported there; not yet checked against the original) | persons/(m min) | the model's sustained gangway flow / it |
|---|---:|---:|
| Guide to Safety at Sports Grounds (Green Guide), 6th ed. 2018: maximum rate of passage on stepped surfaces (the exit sizing rule of venues S, M, L; the CONSERVATIVE target) | 66.0 | 121 / 66 = 1.83x |
| Green Guide, earlier editions: 40 persons per 550 mm unit width per minute on stairways | 72.7 | 121 / 73 = 1.67x |
| Burghardt, Seyfried & Klingsch (2013): measured maximum specific flow on stairs, ascending 1.22 persons/(m s) (the EMPIRICAL target) | 73.2 | 121 / 73 = 1.65x |
| the same, descending 1.25 persons/(m s) | 75.0 | 121 / 75 = 1.61x |
| Fruin (1971), Highway Research Record 355: measured stair maxima 18.9 (up) / 20.0 (down) persons/(ft min); here ascending | 62.0 | 121 / 62 = 1.95x |
| Fruin (1971): stairway level of service E's upper bound (17 persons/(ft min)) | 55.8 | 121 / 56 = 2.17x |
| SFPE Handbook (Gwynne & Rosenbaum): stairs 7/11 in, maximum specific flow 1.01 persons/(s m) of EFFECTIVE width | 60.6 | 121 / 61 = 2.00x |
| the same, per metre of a 1.20 m gangway's CLEAR width (effective width 1.20 - 2 x 0.15 m) | 45.5 | 121 / 45 = 2.66x |
| **the model: straight gangways' sustained flow** (26.57 deg incline; free speed up 0.58 / down 0.655 m/s) | **121.1** | |
| the model: single-outlet straight gangways (M, L; one cross-section, ascending) | 94.0 | |

## Capacity lower bounds and efficiency

| venue | case | N (seated) | (a) exits [s] | (b) gangways [s] | (c) travel [s] | **t_lb** [s] (binding) | t100 [s] | **t100 / t_lb** | (b) with the venue's own q [s] |
|---|---|---|---:|---:|---:|---:|---:|---:|---:|
| S | 100% | 3728 (3728) | 83.2 | 128.3 | 27.1 | **128.3** (b) | 191.2 | **1.49** | 100.0 |
| S | 95% (3 seeds) | 3542 (3542) | 79.1 | 121.9 | 27.1 | **121.9** (b) | 180.9 (178.9-182.3) | **1.48 (1.47-1.50)** | 95.0 |
| S | 125% (3 seeds) | 4660 (3728) | 104.1 | 128.3 | 27.1 | **128.3** (b) | 215.5 (214.1-217.1) | **1.68 (1.67-1.69)** | 100.0 |
| S | 150% (3 seeds) | 5592 (3728) | 124.9 | 128.3 | 27.1 | **128.3** (b) | 258.3 (251.2-263.4) | **2.01 (1.96-2.05)** | 100.0 |
| S | 150%, standing also on the gangways (3 seeds) | 5592 (3728) | 124.9 | 128.3 | 27.1 | **128.3** (b) | 261.8 (261.0-262.4) | **2.04 (2.03-2.05)** | 100.0 |
| S | 100%, nearest exit | 3728 (3728) | 83.2 | 128.3 | 27.1 | **128.3** (b) | 268.1 | **2.09** | 100.0 |
| M | 100% | 15832 (15832) | 202.7 | 233.4 | 52.3 | **233.4** (b) | 461.1 | **1.98** | 224.7 |
| M | 95% (3 seeds) | 15040 (15040) | 192.5 | 221.8 | 52.3 | **221.8** (b) | 434.5 (429.6-442.5) | **1.96 (1.94-2.00)** | 213.5 |
| M | 125% / 150% requested: the achievable maximum (3 seeds) | 19223 (15832) | 246.1 | 233.4 | 52.3 | **246.1** (a) | 484.8 (483.8-485.7) | **1.97** | 224.7 |
| M | 100%, nearest exit | 15832 (15832) | 202.7 | 233.4 | 52.3 | **233.4** (b) | 636.1 | **2.73** | 224.7 |
| L | 100% | 63424 (63424) | 368.7 | 595.1 | 102.8 | **595.1** (b) | 1201.1 | **2.02** | 608.0 |
| L | 95% (3 seeds) | 60253 (60253) | 350.3 | 565.4 | 102.8 | **565.4** (b) | 1215.6 (1134.3-1301.7) | **2.15 (2.01-2.30)** | 577.6 |
| L | 125% / 150% requested: the achievable maximum (3 seeds) | 69311 (63424) | 402.9 | 595.1 | 102.8 | **595.1** (b) | 1237.8 (1213.3-1271.2) | **2.08 (2.04-2.14)** | 608.0 |
| L | 100%, nearest exit | 63424 (63424) | 368.7 | 595.1 | 102.8 | **595.1** (b) | 1441.1 | **2.42** | 608.0 |

Exit widths: S 32.24 m (8 doors 1.20 m + 4 avenues 5.66 m), M 56.24 m (28 doors + avenues), L 123.84 m (44 doors 2.30 m + avenues); gangway widths: 12 / 28 / 44 gangways of 1.20 m. (b) with the venue's own q: the venue's straight gangways' sustained flow at 100% instead of the pooled model value (sensitivity).

## Gangway load imbalance and the counterfactuals

Capacities c_g: the run's pooled sustained flow of the gangway's type x 1.20 m. T: the slowest gangway's service time people_g / c_g. (1) every gangway the mean load; (2) the least slowest service time any split of each row segment between its two end gangways attains (100%, 95%, nearest only: their gangway users are the seated agents).

| venue | case | people per gangway: mean | max / mean (all; straight; corner) | CV (all; straight; corner) | capacity straight / corner [p/s] | slowest gangway: people, T [s] | (1) mean load: T' [s], **t100_cf** [s] (saved) | (2) attainable: T' [s], **t100_cf** [s] (saved) | t100 [s] |
|---|---|---:|---|---|---|---|---|---|---:|
| S | 100% | 311 | 1.49; 1.00; 1.00 | 0.70; 0.00; 0.00 | 3.11 / 1.92 | straight +x+y (y wing) 0: 464, 149 | 162, **204.0** (-7%) | 115, **156.5** (18%) | 191.2 |
| S | 95% (3 seeds) | 295 | 1.52 (1.50-1.52); 1.01 (1.01-1.02); 1.50 (1.33-1.67) | 0.70; 0.01; 0.40 (0.35-0.47) | 3.09 (3.07-3.11) / 1.92 | straight +x-y (x wing) 0: 449, 145 (144-146) | 154, **190.2 (188.7-191.9)** (-5 (-6--4)%) | 109 (109-110), **145.5 (143.4-147.2)** (20 (19-20)%) | 180.9 (178.9-182.3) |
| S | 125% (3 seeds) | 314 | 1.49 (1.48-1.49); 1.01 (1.00-1.01); 1.14 (1.07-1.23) | 0.67 (0.67-0.68); 0.00; 0.13 (0.05-0.26) | 2.66 (2.65-2.67) / 1.92 | straight +x+y (x wing) 0: 468, 175 (175-176) | 164, **204.0 (202.7-205.7)** (5%) | - | 215.5 (214.1-217.1) |
| S | 150% (3 seeds) | 318 | 1.43; 1.01 (1.00-1.01); 1.08 (1.04-1.13) | 0.59; 0.00 (0.00-0.01); 0.06 (0.04-0.09) | 2.10 (2.09-2.11) / 1.92 | straight +x+y (x wing) 0: 454, 216 (215-217) | 166, **208.4 (200.4-213.1)** (19 (19-20)%) | - | 258.3 (251.2-263.4) |
| S | 150%, standing also on the gangways (3 seeds) | 350 (349-352) | 1.38 (1.38-1.39); 1.01 (1.00-1.01); 1.07 (1.04-1.11) | 0.53 (0.53-0.54); 0.00 (0.00-0.01); 0.06 (0.04-0.07) | 2.22 (2.21-2.23) / 1.92 | straight +x+y (y wing) 0: 484, 218 (216-219) | 183 (182-184), **226.4 (224.9-227.4)** (14 (13-14)%) | - | 261.8 (261.0-262.4) |
| S | 100%, nearest exit | 311 | 1.50; 1.00; - | 0.71; 0.00; - | 1.81 / 1.92 | straight +x+y (y wing) 0: 466, 257 | 172, **182.3** (32%) | 168, **179.1** (33%) | 268.1 |
| M | 100% | 565 | 1.70; 1.81; 1.01 | 0.61; 0.68; 0.00 | 2.52 / 1.88 | corner -x-y: 781, 414 | 300, **346.7** (25%) | 310, **357.1** (23%) | 461.1 |
| M | 95% (3 seeds) | 537 | 1.69; 1.81; 1.01 (1.01-1.03) | 0.61; 0.68; 0.01 (0.01-0.02) | 2.50 (2.50-2.51) / 1.93 (1.91-1.95) | corner +x+y: 753, 393 (388-397) | 278 (276-281), **319.3 (309.5-330.2)** (27 (25-28)%) | 295 (294-296), **336.6 (328.2-348.8)** (23 (21-24)%) | 434.5 (429.6-442.5) |
| M | 125% / 150% requested: the achievable maximum (3 seeds) | 567 (566-567) | 1.71 (1.68-1.74); 1.81 (1.80-1.83); 1.04 (1.01-1.09) | 0.60; 0.67; 0.05 (0.01-0.12) | 2.04 (2.03-2.05) / 1.75 (1.54-1.87) | straight +x+y (y wing) 0: 954, 485 (466-517) | 327 (303-368), **320.7 (318.7-322.7)** (34%) | - | 484.8 (483.8-485.7) |
| M | 100%, nearest exit | 565 | 1.98; 1.92; 1.00 | 0.71; 0.74; 0.00 | 1.80 / 1.93 | straight +x+y (y wing) 0: 1121, 622 | 314, **328.0** (48%) | 406, **420.0** (34%) | 636.1 |
| L | 100% | 1441 | 1.62; 1.66; 1.02 | 0.45; 0.48; 0.02 | 2.37 / 1.93 | straight +x-y (y wing) 0: 2336, 985 | 748, **964.2** (20%) | 733, **948.8** (21%) | 1201.1 |
| L | 95% (3 seeds) | 1369 | 1.63 (1.63-1.64); 1.67 (1.66-1.68); 1.02 (1.01-1.02) | 0.46; 0.48 (0.48-0.49); 0.01 | 2.40 (2.37-2.42) / 1.92 (1.73-2.02) | straight +x-y (x wing) 0: 2243, 942 (920-972) | 716 (677-791), **989.3 (894.0-1044.3)** (19 (15-21)%) | 690 (681-705), **963.4 (894.5-1051.9)** (21 (19-22)%) | 1215.6 (1134.3-1301.7) |
| L | 125% / 150% requested: the achievable maximum (3 seeds) | 1442 | 1.64; 1.67 (1.67-1.68); 1.02 (1.02-1.03) | 0.45 (0.45-0.46); 0.48; 0.02 (0.01-0.02) | 2.33 (2.33-2.34) / 1.72 (1.71-1.73) | corner +x-y: 1748, 1023 (1013-1043) | 837 (831-845), **1052.1 (1030.6-1094.2)** (15 (14-16)%) | - | 1237.8 (1213.3-1271.2) |
| L | 100%, nearest exit | 1441 | 1.79; 1.74; 1.00 | 0.52; 0.52; 0.00 | 1.81 / 1.22 | straight +x+y (y wing) 0: 2577, 1426 | 1182, **1196.8** (17%) | 981, **996.5** (31%) | 1441.1 |

