# results/safety/

`overcrowding.md`: the overcrowding spawn's standing floor, the achievable maximum load per venue and each spawn's initial densities (`venue_probe overcrowd`).

Each run's density metrics (peak density, time at or above the thresholds, exposure to critical density, hotspots) stay in its run folder, `summary.md` and `summary.json`, under `results/evacuation/`; the figures `safety_load_vs_time_and_exposure` and `safety_peak_density_maps` in `results/figures/` draw them. The thresholds (LoS E 1.08, LoS F 2.17, crush 5 persons/m^2) are as reported in the cited sources and not yet checked against the originals: `include/swarm/metrics.hpp`.
