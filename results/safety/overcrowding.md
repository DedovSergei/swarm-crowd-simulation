# Overcrowding spawn: standing floor, capacity, initial densities (Task 5.8)

venue_probe overcrowd | commit 728ea207af253b1403189184dc65188063e7d8ac (dirty 0) | Release | 2026-10-15 16:18

spawnOvercrowdedCrowd (include/swarm/crowd_sim.hpp): every seat filled (the 100% seat spawn, bit for bit), plus round((load - 1) x seats) people standing at rest on the walkway (fence's outer face -> barrier) and the rear concourse (the gangway variant: also the gangways), seeded uniform random placement, no body overlap, at most OVERCROWD_STANDING_MAX_P_M2 = 2.5 persons/m^2 of standing floor initially. A load the floor cannot take is reduced to the achievable maximum.

## Standing floor and the achievable maximum

| venue | seats | walkway (m^2) | concourse (m^2) | gangways (m^2) | standing floor (m^2) | max standing | **max load** | with gangways: floor (m^2) | max standing | max load | jam capacity |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| S | 3728 | 248.2 | 609.2 | 275.4 | 857.4 | 2143 | **157.48%** | 1132.7 | 2831 | 175.94% | 18138 |
| M | 15832 | 248.2 | 1108.4 | 957.8 | 1356.6 | 3391 | **121.42%** | 2314.4 | 5785 | 136.54% | 52871 |
| L | 63424 | 248.2 | 2106.8 | 3175.0 | 2355.0 | 5887 | **109.28%** | 5530.0 | 13825 | 121.80% | 171923 |

## The matrix's spawns

Initial density: the metric's cloud-in-cell deposit of the spawn (every agent, seated ones included) per 1 m cell of the venue's metric grid, over cells of at least 0.5 m^2 of floor; standing cells: the walkway zone (walkway and concourse; the gangway variant: and the gangways).

| venue | requested | standing areas | seed | standing (requested / max) | walkway / concourse / gangways | **load** | draws | closest centres (m) | mean standing density (p/m^2) | max standing cell (p/m^2) | standing cells >= LoS F / crush | spawn FNV-1a |
|---|---:|---|---:|---|---|---:|---:|---:|---:|---:|---|---|
| S | 125% | circulation | 1 | 932 (932 / 2143) | 278 / 654 / 0 | **125.00%** | 6536 | 0.410 | 1.087 | 3.29 | 16 / 0 of 888 | 992ca4725b650edf |
| S | 125% | circulation | 2 | 932 (932 / 2143) | 254 / 678 / 0 | **125.00%** | 6611 | 0.410 | 1.087 | 2.51 | 17 / 0 of 888 | dc4d274dcb15cd85 |
| S | 125% | circulation | 3 | 932 (932 / 2143) | 278 / 654 / 0 | **125.00%** | 6741 | 0.410 | 1.087 | 2.88 | 13 / 0 of 888 | 3065822f600a8264 |
| S | 150% | circulation | 1 | 1864 (1864 / 2143) | 556 / 1308 / 0 | **150.00%** | 25138 | 0.410 | 2.174 | 3.46 | 354 / 0 of 888 | 909a16b84f68c42a |
| S | 150% | circulation | 2 | 1864 (1864 / 2143) | 538 / 1326 / 0 | **150.00%** | 24464 | 0.410 | 2.174 | 3.84 | 377 / 0 of 888 | bcabf97faa9a51ed |
| S | 150% | circulation | 3 | 1864 (1864 / 2143) | 533 / 1331 / 0 | **150.00%** | 25228 | 0.410 | 2.174 | 3.74 | 367 / 0 of 888 | 7a96c26860ff1e4f |
| M | 125% | circulation | 1 | 3391 (3958 / 3391) | 619 / 2772 / 0 | **121.42%** | 109663 | 0.410 | 2.500 | 3.71 | 996 / 0 of 1392 | 53514ce5e0beee4e |
| M | 125% | circulation | 2 | 3391 (3958 / 3391) | 628 / 2763 / 0 | **121.42%** | 110379 | 0.410 | 2.500 | 3.98 | 979 / 0 of 1392 | d0ebbadd2f2a6923 |
| M | 125% | circulation | 3 | 3391 (3958 / 3391) | 626 / 2765 / 0 | **121.42%** | 101938 | 0.410 | 2.500 | 4.17 | 972 / 0 of 1392 | f54ffc748c6887aa |
| M | 150% | circulation | 1 | 3391 (7916 / 3391) | 619 / 2772 / 0 | **121.42%** | 109663 | 0.410 | 2.500 | 3.71 | 996 / 0 of 1392 | 53514ce5e0beee4e |
| M | 150% | circulation | 2 | 3391 (7916 / 3391) | 628 / 2763 / 0 | **121.42%** | 110379 | 0.410 | 2.500 | 3.98 | 979 / 0 of 1392 | d0ebbadd2f2a6923 |
| M | 150% | circulation | 3 | 3391 (7916 / 3391) | 626 / 2765 / 0 | **121.42%** | 101938 | 0.410 | 2.500 | 4.17 | 972 / 0 of 1392 | f54ffc748c6887aa |
| L | 125% | circulation | 1 | 5887 (15856 / 5887) | 608 / 5279 / 0 | **109.28%** | 349703 | 0.410 | 2.500 | 4.06 | 1967 / 0 of 2488 | fbf80f8aa61f092d |
| L | 125% | circulation | 2 | 5887 (15856 / 5887) | 615 / 5272 / 0 | **109.28%** | 355876 | 0.410 | 2.500 | 4.20 | 1981 / 0 of 2488 | 31ee770641c05cd6 |
| L | 125% | circulation | 3 | 5887 (15856 / 5887) | 626 / 5261 / 0 | **109.28%** | 355962 | 0.410 | 2.500 | 4.11 | 1976 / 0 of 2488 | f9142558d5c10982 |
| L | 150% | circulation | 1 | 5887 (31712 / 5887) | 608 / 5279 / 0 | **109.28%** | 349703 | 0.410 | 2.500 | 4.06 | 1967 / 0 of 2488 | fbf80f8aa61f092d |
| L | 150% | circulation | 2 | 5887 (31712 / 5887) | 615 / 5272 / 0 | **109.28%** | 355876 | 0.410 | 2.500 | 4.20 | 1981 / 0 of 2488 | 31ee770641c05cd6 |
| L | 150% | circulation | 3 | 5887 (31712 / 5887) | 626 / 5261 / 0 | **109.28%** | 355962 | 0.410 | 2.500 | 4.11 | 1976 / 0 of 2488 | f9142558d5c10982 |
| S | 150% | gangways | 1 | 1864 (1864 / 2831) | 436 / 1020 / 408 | **150.00%** | 13977 | 0.410 | 1.646 | 3.32 | 202 / 0 of 1280 | 242184953774e40f |
| S | 150% | gangways | 2 | 1864 (1864 / 2831) | 414 / 1034 / 416 | **150.00%** | 13718 | 0.410 | 1.646 | 3.18 | 195 / 0 of 1280 | 9d5eb0d4fcb5d38c |
| S | 150% | gangways | 3 | 1864 (1864 / 2831) | 413 / 1015 / 436 | **150.00%** | 14021 | 0.410 | 1.646 | 3.29 | 198 / 0 of 1280 | dc4e66aa74892b76 |

Closest centres: of a standing agent to any other agent (3D); BODY_DIAM = 0.40 m, the placement keeps BODY_DIAM + 0.01 m. A requested load whose standing crowd exceeds the cap gets the cap: M and L reach the same maximum at 125% and 150% (the same spawn for a seed).
