# Navigation fields and exit choice tables of the seated venues (Task 5.7)

nav_probe build | commit ba8faa093b0ce962329b0a8501de754cc855362a (dirty 1) | Release | 2026-10-11 21:45 | 20 OpenMP threads

Fresh builds (no cache), then saved to the cache (keyed by the venue's parameters, layout, contact constants and the algorithms' versions: nav::cacheKey) and loaded back. Navigation field: the traversability grid (parallel) and the nearest-exit Lazy Theta* search (sequential). Exit choice table: every exit's own Lazy Theta* field, in parallel batches (at most 4 GB of searches in flight), merged into CHOICE_K = 10 candidates per cell (Task 5.7, correction C1: the 2 nearest avenues and the nearest door, then the nearest other exits; 16-bit distances; 64 B per cell; budget 1 GB = 1024 MB). Peak working set: this process after the venue's builds (cumulative over the venues built so far).

| venue | grid (0.05 m cells) | cells | exits | field: grid [s] | field: search [s] | field arrays [MB] | GPU field [MB] | choice table: build [s] | choice table [MB] | cells changed by the type rule | largest candidate distance [m] | load both from the cache [s] | peak working set [GB] | content hashes (field / table) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---|
| S | 1250 x 1250 | 1562500 | 12 | 0.45 | 2.17 | 36 | 24 | 3.32 | 95 | 0 | 86.7 | 2.84 | 0.50 | 2619c6d0d7ba75aa / 0f8b6c8dd65b4c45 |
| M | 2375 x 2375 | 5640625 | 32 | 1.97 | 15.37 | 129 | 86 | 52.22 | 344 | 0 | 149.2 | 10.31 | 2.36 | 3a93c6e67b76013c / 05cc49de8aa265b2 |
| L | 4000 x 4000 | 16000000 | 48 | 9.54 | 50.75 | 366 | 244 | 384.37 | 977 | 7908241 | 272.7 | 28.99 | 4.17 | 022d17b202313d70 / 551ce86dd7d4360d |

Field arrays: the CPU field's per-cell arrays (floor, class, edges, exit region, distance, anchor, anchor centre, exit id: 24 B per cell). GPU field: GpuNavCell, 16 B per cell (nearest-exit mode only; the queue-aware default uploads the choice table instead).
