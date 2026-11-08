# The experiment matrix (the level spacing on the gangways)

Runs: 30 in results/evacuation/matrix_before_calibration; GPU driver: 4.3.0 Core Profile Context 26.10.1.261008 (30 runs); run_experiment built at: b6a7874 (30 runs).

GPU, run_experiment with every per-step check (plausibility with no exemption on S / M / L, INV-row, the step-up rules, wall tops; the terrace: its documented exemptions); default model (queue-aware exit choice, incline speed) unless named. Values: the mean over a case's seeds and (min-max); one value: one run. t99: the time by which ceil(0.99 N) had left; longest pause: the longest interval without an evacuation while agents remained (a stall shows here). Runs: results/evacuation/matrix_before_calibration/<name>_<timestamp> (names: thesis_data.CASES).

| venue | case | runs | agents (load) | t50 [s] | t90 [s] | t99 [s] | t100 [s] | longest pause in evacuations [s] | doors / avenues [% of evacuated] | unused exit width | gangways saturated: people-weighted mean share / share of gangways >= 50% | people per gangway: max/mean / CV | circulation peak density [p/m^2] | circulation time >= LoS F / crush [s] | circulation crush exposure [person-s] | top hotspot (seed 1) | INV-row row changes | overlap p99 / max [BODY_DIAM] | checks |
|---|---|---:|---|---:|---:|---:|---:|---:|---|---:|---|---|---:|---|---:|---|---:|---|---|
| terrace | terrace, N = 4096 | not run | | | | | | | | | | | | | | |
| S | 100% | 1 | 3728 (100.00%) | 91.1 | 155.7 | 178.6 | **191.2** | 5.2 | 63.9 / 36.1 | 0.0 m | 75% / 67% | 1.49 / 0.70 | 6.09 | 178.4 / 145.7 | 27084 | gangway (10.5, -18.5) m, 5.77 p/m^2, 477 person-s | 0 | 0.0044 / 0.0105 | PASS |
| S | 95% (3 seeds) | 3 | 3542 (95.00%) | 86.9 (86.8-87.3) | 148.6 (148.3-149.0) | 171.5 (170.7-172.5) | **180.9 (178.9-182.3)** | 2.0 (1.0-2.8) | 64.2 (64.1-64.3) / 35.8 (35.7-35.9) | 0.0 m | 75 (74-75)% / 67% | 1.52 (1.50-1.52) / 0.70 | 6.38 (6.29-6.43) | 172.5 (171.8-173.3) / 138.9 (138.2-139.2) | 24868 (24429-25176) | gangway (-10.5, -18.5) m, 5.82 p/m^2, 441 person-s | 0 | 0.0044 (0.0036-0.0058) / 0.0095 (0.0079-0.0122) | PASS |
| S | 125% (3 seeds) | 3 | 4660 (125.00%) | 100.7 (100.0-101.4) | 177.6 (176.5-178.2) | 204.5 (202.9-206.0) | **215.5 (214.1-217.1)** | 1.8 (0.7-3.0) | 61.9 (61.7-62.2) / 38.1 (37.8-38.3) | 0.0 m | 77 (77-78)% / 67% | 1.49 (1.48-1.49) / 0.67 (0.67-0.68) | 6.39 (6.34-6.44) | 207.6 (206.2-208.7) / 175.4 (173.3-176.5) | 44509 (42821-45835) | gangway (-10.5, -18.5) m, 5.61 p/m^2, 601 person-s | 0 | 0.0051 (0.0040-0.0063) / 0.0138 (0.0093-0.0206) | PASS |
| S | 150% (3 seeds) | 3 | 5592 (150.00%) | 119.9 (119.8-120.0) | 210.2 (209.9-210.6) | 242.1 (239.8-245.0) | **258.3 (251.2-263.4)** | 2.1 (1.0-3.0) | 61.1 (60.8-61.2) / 38.9 (38.8-39.2) | 0.0 m | 76 (74-77)% / 67% | 1.43 / 0.59 | 6.49 (6.45-6.52) | 248.8 (242.6-252.7) / 215.4 (214.3-216.5) | 95300 (94544-96175) | gangway (-18.5, -10.5) m, 6.04 p/m^2, 902 person-s | 0 | 0.0043 (0.0036-0.0049) / 0.0136 (0.0108-0.0182) | PASS |
| S | 150%, standing also on the gangways (3 seeds) | 3 | 5592 (150.00%) | 121.0 (120.3-121.6) | 211.3 (210.9-211.8) | 242.4 (241.9-242.9) | **261.8 (261.0-262.4)** | 1.2 (1.0-1.4) | 61.1 (60.9-61.3) / 38.9 (38.7-39.1) | 0.0 m | 76 (75-76)% / 67% | 1.38 (1.38-1.39) / 0.53 (0.53-0.54) | 6.45 (6.39-6.52) | 249.7 (249.2-249.9) / 215.8 (215.0-217.1) | 84204 (83506-85461) | gangway (-18.5, 10.5) m, 6.07 p/m^2, 930 person-s | 0 | 0.0055 (0.0046-0.0063) / 0.0124 (0.0123-0.0125) | PASS |
| S | 100%, nearest exit | 1 | 3728 (100.00%) | 132.2 | 234.7 | 260.8 | **268.1** | 1.2 | 100.0 / 0.0 | 22.6 m | 86% / 67% | 1.50 / 0.71 | 6.52 | 265.3 / 235.9 | 88653 | gangway (-10.5, 15.5) m, 6.00 p/m^2, 989 person-s | 0 | 0.0041 / 0.0130 | PASS |
| S | 100%, CONSERVATIVE stair spacing | not run | | | | | | | | | | | | | | |
| S | 100%, queue-aware, level walking speed | not run | | | | | | | | | | | | | | |
| S | 100%, nearest exit, level walking speed | not run | | | | | | | | | | | | | | |
| M | 100% | 1 | 15832 (100.00%) | 177.7 | 339.7 | 409.1 | **461.1** | 3.0 | 80.7 / 19.3 | 0.0 m | 69% / 71% | 1.70 / 0.61 | 6.86 | 439.2 / 407.7 | 512676 | gangway (29.5, 26.5) m, 6.38 p/m^2, 1824 person-s | 0 | 0.0045 / 0.0283 | PASS |
| M | 95% (3 seeds) | 3 | 15040 (95.00%) | 170.8 (170.0-171.4) | 322.0 (321.1-323.4) | 392.8 (390.9-393.7) | **434.5 (429.6-442.5)** | 2.7 (1.2-5.4) | 80.7 (80.7-80.8) / 19.3 (19.2-19.3) | 0.0 m | 66 (66-67)% / 71% | 1.69 / 0.61 | 6.83 (6.81-6.86) | 416.3 (413.3-417.9) / 385.3 (382.0-387.1) | 478170 (475066-482475) | gangway (-27.5, -28.5) m, 6.25 p/m^2, 1627 person-s | 0 | 0.0043 (0.0040-0.0044) / 0.0488 (0.0356-0.0706) | PASS |
| M | 125% / 150% requested: the achievable maximum (3 seeds) (seed 2 did not complete: times over the completed runs; checks FAIL = incomplete) | 3 | 19223 (121.42%) | 186.3 (183.0-189.6) | 374.9 (370.8-381.5) | 454.6 (444.1-474.5) | **484.8 (483.8-485.7)** | 6.2 (2.8-12.6) | 80.7 (80.5-80.8) / 19.3 (19.2-19.5) | 0.0 m | 70 (70-71)% / 73 (71-75)% | 1.71 (1.68-1.74) / 0.60 | 6.75 (6.70-6.79) | 2645.2 (464.6-6996.3) / 2629.3 (444.8-6996.1) | 811181 (706320-1005620) | gangway (29.5, -26.5) m, 6.21 p/m^2, 1936 person-s | 0 | 0.0038 (0.0037-0.0039) / 0.0315 (0.0173-0.0501) | **FAIL** |
| M | 100%, nearest exit | 1 | 15832 (100.00%) | 228.3 | 515.5 | 614.3 | **636.1** | 1.1 | 100.0 / 0.0 | 27.4 m | 74% / 57% | 1.98 / 0.71 | 6.80 | 613.2 / 539.4 | 889583 | gangway (-11.5, -18.5) m, 6.76 p/m^2, 2832 person-s | 0 | 0.0034 / 0.0112 | PASS |
| M | 100%, CONSERVATIVE stair spacing | not run | | | | | | | | | | | | | | |
| M | 100%, queue-aware, level walking speed | not run | | | | | | | | | | | | | | |
| M | 100%, nearest exit, level walking speed | not run | | | | | | | | | | | | | | |
| L | 100% | 1 | 63424 (100.00%) | 409.8 | 832.7 | 1077.4 | **1201.1** | 1.2 | 88.3 / 11.7 | 0.0 m | 69% / 64% | 1.62 / 0.45 | 7.10 | 1130.6 / 1070.6 | 5222980 | gangway (-34.5, -34.5) m, 5.99 p/m^2, 5778 person-s | 0 | 0.0031 / 0.1323 | PASS |
| L | 95% (3 seeds) | 3 | 60253 (95.00%) | 395.1 (391.4-397.6) | 794.7 (791.3-801.2) | 1035.3 (1017.4-1054.5) | **1215.6 (1134.3-1301.7)** | 8.8 (3.0-18.2) | 88.3 / 11.7 | 0.0 m | 67 (66-68)% / 64% | 1.63 (1.63-1.64) / 0.46 | 6.99 (6.93-7.05) | 1133.4 (1041.2-1213.2) / 1051.9 (986.5-1088.4) | 5059890 (4998930-5113450) | gangway (-34.5, -34.5) m, 5.91 p/m^2, 5911 person-s | 0 | 0.0031 (0.0030-0.0031) / 0.0976 (0.0762-0.1094) | PASS |
| L | 125% / 150% requested: the achievable maximum (3 seeds) | 3 | 69311 (109.28%) | 382.1 (380.8-383.6) | 838.4 (835.9-841.8) | 1088.3 (1080.8-1093.0) | **1237.8 (1213.3-1271.2)** | 5.8 (5.1-6.3) | 88.7 (88.7-88.8) / 11.3 (11.2-11.3) | 0.0 m | 69 (68-69)% / 64% | 1.64 / 0.45 (0.45-0.46) | 7.00 (6.97-7.07) | 1171.0 (1145.5-1210.2) / 1089.2 (1072.0-1119.6) | 5596893 (5569800-5613280) | gangway (-50.5, -50.5) m, 5.92 p/m^2, 5966 person-s | 0 | 0.0030 (0.0029-0.0031) / 0.1092 (0.0736-0.1294) | PASS |
| L | 100%, nearest exit | 1 | 63424 (100.00%) | 471.4 | 1088.3 | 1385.3 | **1441.1** | 1.2 | 100.0 / 0.0 | 22.6 m | 82% / 91% | 1.79 / 0.52 | 6.83 | 1422.0 / 1271.0 | 7357390 | gangway (-10.5, 17.5) m, 5.92 p/m^2, 6798 person-s | 0 | 0.0029 / 0.0329 | PASS |
| L | 100%, CONSERVATIVE stair spacing | not run | | | | | | | | | | | | | | |
| L | 100%, queue-aware, level walking speed | not run | | | | | | | | | | | | | | |
| L | 100%, nearest exit, level walking speed | not run | | | | | | | | | | | | | | |
| M | 100%, DT / 2 | not run | | | | | | | | | | | | | | |

## Run-to-run spread of t100 (the 95% runs, seeds 1-3)

| venue | t100 at 100% [s] | 95%: mean (min-max) [s] | 95%: spread (max - min) / mean | overcrowded: spread (max - min) / mean |
|---|---:|---:|---:|---:|
| S | 191.2 | 180.9 (178.9-182.3) | 1.8% | 4.7% |
| M | 461.1 | 434.5 (429.6-442.5) | 3.0% | 0.4% |
| L | 1201.1 | 1215.6 (1134.3-1301.7) | 13.8% | 4.7% |

## Top circulation hotspots (the case's first run; ranked by crush exposure, then time at or above LoS F)

| venue | case | # | zone | x, y [m] | peak [p/m^2] | >= LoS F [s] | >= crush [s] | crush exposure [person-s] |
|---|---|---:|---|---|---:|---:|---:|---:|
| S | 100% | 1 | gangway | 10.5, -18.5 | 5.77 | 142.2 | 95.3 | 477 |
| S | 100% | 2 | gangway | -11.5, -22.5 | 6.03 | 145.3 | 100.6 | 477 |
| S | 100% | 3 | gangway | -11.5, 22.5 | 5.99 | 143.8 | 97.6 | 464 |
| S | 95% (3 seeds) | 1 | gangway | -10.5, -18.5 | 5.82 | 128.9 | 87.6 | 441 |
| S | 95% (3 seeds) | 2 | gangway | -22.5, -11.5 | 6.04 | 140.3 | 94.6 | 440 |
| S | 95% (3 seeds) | 3 | gangway | -10.5, 18.5 | 5.99 | 136.1 | 85.5 | 436 |
| S | 125% (3 seeds) | 1 | gangway | -10.5, -18.5 | 5.61 | 169.8 | 121.0 | 601 |
| S | 125% (3 seeds) | 2 | gangway | 11.5, -19.5 | 5.96 | 156.5 | 120.0 | 600 |
| S | 125% (3 seeds) | 3 | gangway | -18.5, 11.5 | 6.33 | 157.1 | 112.3 | 541 |
| S | 150% (3 seeds) | 1 | gangway | -18.5, -10.5 | 6.04 | 212.5 | 175.4 | 902 |
| S | 150% (3 seeds) | 2 | gangway | -18.5, 10.5 | 5.94 | 213.9 | 168.1 | 866 |
| S | 150% (3 seeds) | 3 | gangway | 10.5, -18.5 | 6.01 | 212.9 | 159.3 | 827 |
| S | 150%, standing also on the gangways (3 seeds) | 1 | gangway | -18.5, 10.5 | 6.07 | 215.5 | 179.8 | 930 |
| S | 150%, standing also on the gangways (3 seeds) | 2 | gangway | 10.5, 18.5 | 5.91 | 208.3 | 171.8 | 879 |
| S | 150%, standing also on the gangways (3 seeds) | 3 | gangway | 10.5, 17.5 | 5.82 | 215.8 | 171.4 | 865 |
| S | 100%, nearest exit | 1 | gangway | -10.5, 15.5 | 6.00 | 241.0 | 184.5 | 989 |
| S | 100%, nearest exit | 2 | gangway | 16.5, 10.5 | 5.85 | 237.0 | 183.0 | 986 |
| S | 100%, nearest exit | 3 | gangway | 16.5, 11.5 | 6.05 | 219.3 | 184.9 | 947 |
| M | 100% | 1 | gangway | 29.5, 26.5 | 6.38 | 334.1 | 300.1 | 1824 |
| M | 100% | 2 | gangway | -26.5, 29.5 | 6.12 | 347.9 | 298.0 | 1747 |
| M | 100% | 3 | gangway | 28.5, -27.5 | 5.85 | 363.8 | 307.0 | 1724 |
| M | 95% (3 seeds) | 1 | gangway | -27.5, -28.5 | 6.25 | 329.7 | 270.9 | 1627 |
| M | 95% (3 seeds) | 2 | gangway | -26.5, 27.5 | 6.10 | 318.0 | 284.0 | 1556 |
| M | 95% (3 seeds) | 3 | gangway | -27.5, 27.5 | 5.68 | 337.4 | 279.9 | 1554 |
| M | 125% / 150% requested: the achievable maximum (3 seeds) | 1 | gangway | 29.5, -26.5 | 6.21 | 370.1 | 332.3 | 1936 |
| M | 125% / 150% requested: the achievable maximum (3 seeds) | 2 | gangway | 29.5, 26.5 | 6.15 | 389.2 | 330.4 | 1935 |
| M | 125% / 150% requested: the achievable maximum (3 seeds) | 3 | gangway | -26.5, 28.5 | 6.20 | 387.8 | 328.8 | 1899 |
| M | 100%, nearest exit | 1 | gangway | -11.5, -18.5 | 6.76 | 545.5 | 515.1 | 2832 |
| M | 100%, nearest exit | 2 | gangway | -18.5, -11.5 | 6.80 | 537.1 | 494.3 | 2799 |
| M | 100%, nearest exit | 3 | gangway | -10.5, -17.5 | 6.03 | 567.6 | 516.3 | 2780 |
| L | 100% | 1 | gangway | -34.5, -34.5 | 5.99 | 1038.8 | 998.5 | 5778 |
| L | 100% | 2 | gangway | 34.5, 34.5 | 5.86 | 1031.4 | 1009.4 | 5749 |
| L | 100% | 3 | gangway | 34.5, -34.5 | 5.65 | 1073.2 | 1031.2 | 5660 |
| L | 95% (3 seeds) | 1 | gangway | -34.5, -34.5 | 5.91 | 1069.5 | 1021.3 | 5911 |
| L | 95% (3 seeds) | 2 | gangway | -35.5, -35.5 | 5.65 | 1087.6 | 1022.0 | 5332 |
| L | 95% (3 seeds) | 3 | gangway | 35.5, -35.5 | 5.74 | 1032.3 | 944.8 | 5249 |
| L | 125% / 150% requested: the achievable maximum (3 seeds) | 1 | gangway | -50.5, -50.5 | 5.92 | 1144.8 | 1054.0 | 5966 |
| L | 125% / 150% requested: the achievable maximum (3 seeds) | 2 | gangway | -58.5, -59.5 | 6.13 | 1187.6 | 1022.3 | 5793 |
| L | 125% / 150% requested: the achievable maximum (3 seeds) | 3 | gangway | 34.5, 34.5 | 6.30 | 1018.3 | 963.7 | 5771 |
| L | 100%, nearest exit | 1 | gangway | -10.5, 17.5 | 5.92 | 1306.4 | 1251.5 | 6798 |
| L | 100%, nearest exit | 2 | gangway | 10.5, 16.5 | 5.91 | 1289.4 | 1218.4 | 6795 |
| L | 100%, nearest exit | 3 | gangway | -10.5, -18.5 | 6.18 | 1282.8 | 1211.9 | 6759 |
