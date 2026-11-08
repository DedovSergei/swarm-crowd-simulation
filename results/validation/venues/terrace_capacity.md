# Venue floor area and jam capacity (step_probe venue)

commit f031a3c6c2398eaff0846d24f960b572bbf4e725 (dirty 0), Release

Metric grid: 64 x 64 cells of 1 m, 40 x 40 walkable samples per cell (metrics::computeMetricVenue). Hexagonal packing of 0.40 m bodies (BODY_RADIUS_M 0.20): 7.2169 persons/m^2.

| floor | area m^2 | jam capacity (x 7.22) |
|---|---:|---:|
| all walkable (sum of the cells' walkable area) | 3241.3 | 23392 |
| included cells only (>= 0.10 m^2) | 3241.1 | 23391 |
| . zone tread (cells by majority) | 1968.9 | 14209 |
| . zone aisle (cells by majority) | 227.3 | 1640 |
| . zone walkway (cells by majority) | 190.8 | 1377 |
| . zone avenue (cells by majority) | 437.9 | 3160 |
| . zone pitch (cells by majority) | 400.0 | 2887 |
| . zone exit (cells by majority) | 16.5 | 119 |
| occupiable: all walkable minus the pitch (fenced, no gates) | 2841.3 | **20506** |

Tread zone by sample point (1988.4 m^2): tread rows 1-7 521.9 m^2, rear platform (row 8) 857.6 m^2, between rows (riser ramps, lips) 609.0 m^2.
Sample-point zones: tread 1988.4, aisle 207.1, walkway 194.9, avenue 405.4, pitch 420.3, exit 25.2 m^2
Occupiable without the rear platform: 1983.8 m^2, jam capacity 14317.
