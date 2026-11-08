# The SWARM viewer

`SWARM.exe` runs the GPU crowd simulation of a venue in real time and shows it in 3D, with a control panel,
an orbit camera, agent colourings, a heatmap of the safety metrics painted onto the floors, and figure
export. The viewer only *watches* the simulation: it steps it exactly as the headless tools do and never changes
its state (checked bit for bit by `SWARM --selftest-ui`, below).

## Build

Visual Studio 2026 (MSVC x64), CMake, Ninja, OpenGL 4.3. From the repository root, with the build folders
configured once (Ninja, from an x64 Native Tools prompt or after `vcvars64.bat`):

```bash
cmake -S . -B out/build/x64-Release -G Ninja -DCMAKE_BUILD_TYPE=Release
```

```bash
cmake --build out/build/x64-Release --target SWARM
```

Use `out/build/x64-Debug` with `-DCMAKE_BUILD_TYPE=Debug` for a debug build. The shaders and the stadium files are
copied next to `SWARM.exe` by the build. The C++ runtime is linked statically; the OpenMP runtime stays a DLL (`vcomp140.dll`, from Visual Studio on a build machine, from the Microsoft
Visual C++ Redistributable elsewhere; the release zip does not carry it). `tools/package/package_release.py` builds the release zips. Third-party code lives in `external/`: GLFW, GLM, glad, Dear ImGui v1.92.9b and
stb_image_write v1.16 (the last two pinned and unmodified, see their `PINNED.txt`).

## Run

```bash
out/build/x64-Release/SWARM.exe
```

It opens a window of at most 2560 x 1440 that fits the primary monitor's work area, with 4096 agents on the stands, playing at
real speed (1 simulated second per second). `SWARM --help` lists the options:

| option | meaning |
|---|---|
| `--venue terrace\|S\|M\|L` | the venue at start (default `terrace`; `S`, `M`, `L`: the seated venues, 3728, 15 832 and 63 424 seats) |
| `--load X` | a seated venue: the share of its seats occupied, 0 - 1 (default 1: every seat); a seeded random subset |
| `--exit-choice nearest\|queue-aware` | seated venues: every agent to its nearest exit, or the queue-aware exit choice (default) |
| `--incline-speed 0\|1` | seated venues: stair walking speeds on the gangway inclines (default 1) |
| `--stair-flow off\|empirical\|conservative` | seated venues: the stair spacing on the gangway inclines, with the incline speed (default empirical; off = the level spacing) |
| `--agents N` | agents at start in the terrace (a power of two, at least 256; default 4096) |
| `--playback X` | playback speed in x real time, 0.1 - 20 (default 1) |
| `--max-steps-per-frame K` | at most K simulation steps per frame (default 8) |
| `--colour speed\|density\|zone` | agent colouring at start |
| `--overlay <metric>` | heatmap overlay on at start: `peak-density`, `density-now`, `time-los-e`, `time-los-f`, `time-crush`, `mean-speed`, `exposure`, `nav-distance` (seated venues) |
| `--camera default\|top-down\|isometric\|exit` | camera preset at start |
| `--panel-hidden` | start with the panel hidden (F1 shows it) |
| `--no-ui` | no panel at all (no Dear ImGui) |
| `--screenshot-dir DIR` | export folder (default: a `screenshots` folder beside the program) |
| `--export-px N` | size of the top-down heatmap export (at least 3000, default 4096) |
| `--run-seconds S` | close after S wall seconds and print run statistics |
| `--export-on-exit` | at the end, write a screenshot and a heatmap export (with `--run-seconds`: scripted figures) |
| `--screenshot-on-exit` | at the end, write the screenshot alone |
| `--include-panel` | the exit screenshot includes the panel |
| `--no-parallel-compile` | compile the shader programs one per frame while loading, as on a driver without `GL_ARB_parallel_shader_compile` (also `SWARM_NO_PARALLEL_COMPILE=1`; see "Loading a venue") |
| `--selftest-ui [--selftest-steps K]` | the automatic self-test (below) |
| `--help` | the options |

## GPU requirements

At the start, before any table is built, SWARM reads the OpenGL version and the GPU's limits and compares them with what each venue
needs; the console prints both. The numbers come from the programs' and buffers' own lists in the code (the self-test compares the lists
with the compiled programs, `test_gpu`'s `engine.gpu_capabilities` with the real buffers). [README.md](../README.md) lists the GPUs tested. With the default model:

| venue | OpenGL | SSBO bindings | SSBOs per compute program | per vertex shader | per fragment shader | largest SSBO |
|---|---|---|---|---|---|---|
| terrace | 4.3 | 13 | 6 | 4 | 3 | 2 MB (the agent state at 65536 agents) |
| S | 4.3 | 20 | 11 | 4 | 3 | 99 MB (the exit choice table) |
| M | 4.3 | 20 | 11 | 4 | 3 | 416 MB (the exit choice table) |
| L | 4.3 | 20 | 11 | 4 | 3 | 884 MB (the exit choice table) |

A table's exact size comes from its cache file's header. Without a cache file SWARM uses an upper bound from the venue's floor area (S
145 MB, about 1.45x the real size), so on a GPU whose limit lies between the two the venue stays disabled until a cache file exists.

- A venue this GPU cannot run is **disabled in the venue selector**, with the reason next to it and in the panel, and Restart is
  disabled while such a venue is selected.
- `--venue X` for such a venue shows a **message box** with the reason and the venues that can run, and SWARM exits with code 1.
- **Every fatal error shows a message box** as well as the console line (a console opened by double-clicking closes with the program).
  `--selftest-ui` and `SWARM cell` never show one: scripts drive them.
- `CrowdSim` and `CrowdMetrics` check the same limits themselves, with the exit choice table's exact size, before they compile a program.

`SWARM_GPU_LIMITS=gl=4.1,bindings=16,blocks=16,vertexblocks=4,fragmentblocks=8,blocksize=134217728` (any of them) simulates another GPU's limits, to test all of this;
`gl` below 4.3 makes creating the window fail as on such a driver.

## Loading a venue

The start and every Restart load the venue in the background behind a **loading screen**, so the window keeps responding.
**The first start on a PC compiles the shaders and can take several minutes; later starts take seconds:** the
loading screen says so, and the window title repeats it while the picture pauses. Each venue's first start compiles that venue's own
programs, and moving or renaming the program's folder, or a new graphics driver, compiles them again. The loading screen lists four steps:

1. **Navigation tables, metric grid, mesh and spawn**, on a background thread (CPU work only): the venue's navigation field and
   exit choice table are read from their cache files or, on a venue's first use, built and saved (a progress bar with the stage,
   e.g. "exit choice table: per-exit fields 12 of 48").
2. **Shader programs: compile.** With `GL_ARB_parallel_shader_compile` (or the KHR form) the driver compiles them on its own
   threads; without it, or with `--no-parallel-compile` / `SWARM_NO_PARALLEL_COMPILE=1`, one program per frame (each such frame
   waits for its program: with a cold shader cache that can freeze the window again).
3. **Shader programs: link**, and 4. **the first dispatch of each compute program** (the driver compiles a program once more the
   first time it runs; a dispatch that does no work and reads or writes no simulation buffer), then the GPU buffers. During steps
   3 and 4 **the picture pauses**: the driver does this work in its command stream, and a redraw would wait for it. The window
   keeps responding and its title shows the step and the elapsed time.

Restart and the venue selector are unavailable while loading (the loading screen replaces the panel); a restart requested
meanwhile waits for the load. Esc or closing the window cancels the load and exits cleanly: a navigation build stops within
milliseconds, and a cache file is written only when its build is complete (to a temporary file, then renamed). The run is the
same as a restart within the frame, bit for bit: the same programs from the same sources, the same buffers, the same first step
(`SWARM --selftest-ui` checks it).

Measured load times on the development PC (AMD RX 7800 XT, i5-13600KF, driver 26.10.1, Release; the only hardware measured, and the
window kept responding in every run):

| start | terrace | S | M | L |
|---|---|---|---|---|
| later starts (navigation tables on disk, shaders in the driver's cache) | 1.4 s | 0.6 s | 2.0 s | 4.7 s |
| first start with the tables on disk (the shaders compile) | 5.7 s | 48 s | 2.1 min | 3.6 min |
| first start of all (the tables are built too) | 5.7 s | 54 s | 3.3 min | 11.3 min |

The tables' share of the last row is 6.5 s for S, 73 s for M and 7.8 min for L (`nav_probe build` can prepare them in advance); the
compile's share is 48 s, 2.1 min and 3.5 min. A venue loaded before in the same run takes 0.1-0.3 s. The terrace has no navigation
tables: its 1.2 s is the metric grid and the spawn, at every start.

## Controls

| input | action |
|---|---|
| **Esc** | quit |
| **F1** | show / hide the panel |
| **P** | pause / resume |
| **N** | one simulation step (while paused) |
| **[** / **]** | playback speed / 2, x 2 (within 0.1x - 20x real time) |
| **V** | VSync on / off (off at start: frames are uncapped) |
| **W A S D** | move the orbit centre forward / left / back / right on the ground |
| **1 2 3 4** | camera presets: default, top-down, isometric, exit close-up |
| **M** | next agent colouring (speed, density, zone) |
| **H** | heatmap overlay on / off |
| **F12** | screenshot |
| **F9** | top-down heatmap export |
| left-drag | rotate the camera around the orbit centre |
| right-drag | pan |
| mouse wheel | zoom |

The mouse belongs to the panel while it is over the panel; a drag that starts over the scene keeps moving the camera
even when it crosses the panel. The cursor is never captured. Keys do nothing while you type into a panel field
(Esc and F1 always work).

## The panel

**Capacity** (top line). The terrace is laid out for **4096** people (its design capacity). Its floor that
people can reach (2841 m^2: treads, aisles, walkway, avenues, the platform behind the top row; not the fenced pitch)
holds at most **20 506** of them shoulder to shoulder (0.40 m bodies packed hexagonally): the jam capacity. Above 4096
the panel shows "above design capacity (N / design capacity = x)" in amber; above 20 506 it shows "PHYSICALLY
IMPOSSIBLE: physically impossible (N / jam capacity = x)" in red, and the window title carries the same label. Such
runs still run (they are useful as performance stress tests), but their densities and body overlaps are not physical:
the bodies do not fit on the floor. The N selector lists the label next to every N above the design capacity, and the
console prints a warning on every start or restart above it.

**Simulation.** Play / Pause, Step (pauses, then one step), Restart (a fresh run in the venue selected next to it, loaded
behind the loading screen (see "Loading a venue"): terrace, S, M or L, with the N selected next to that in the terrace
(1024 to 65536 agents) or the share of seats occupied in a seated venue; the metrics start again from zero), for the seated
venues the exit choice (nearest | queue-aware), the incline speed checkbox and, with it, the stair spacing (off | empirical |
conservative): they apply at the restart, "(Restart applies)" shows a pending change; the playback speed slider (0.1x - 20x
real time, "1x" button) with the requested and the achieved speed (steps actually taken in the last second x 0.1749 s; a
restart starts a fresh one-second window, and the time the restart itself took is not counted as dropped), and
"Pause when everyone has left" (on by default).

**Readouts.** Simulated time, active agents, % evacuated and the agents per exit, from small GPU counters that the
viewer reads only once the GPU has finished writing them (it never waits for the GPU), so they can be a few frames
behind the picture; FPS and steps per frame. The **evacuation curve** shows % evacuated over simulated time; hover
over it for the values. When the counters show no agent left, the panel gives the time; this first reading can be a
few steps after the true last exit (the exact evacuation time comes from `run_experiment`).

**Camera.** The presets: Default (perspective, from the south, 35 degrees down), Top-down (orthographic, north up),
Isometric (orthographic) and Exit close-up (perspective, onto the selected exit gap: +x, -x, +y or -y), and an
Orthographic switch for any view.

**Agents.** Colour by speed, density or zone, a checkbox to hide the agents, and the legend. Each agent is a cone
whose base is the hard body (radius 0.20 m): where two cones overlap on screen, the two
bodies really overlap.

**Heatmap overlay.** On / off, the metric, its legend.

**Export.** Screenshot (and "include the panel"), Top-down heatmap export (4096 or 8192 px, "agents" to draw them
too), the export folder and the last file written.

The bottom line lists every key.

## Venues

The **terrace** is the reference venue (stadium.obj, stadium.sdf): bare terraces without seats, 4096 people by design.
**Venues S, M and L** are seated venues from a parametric generator (include/swarm/venue.hpp; their exact distance is computed in
closed form, no texture): four L-shaped stands around the same pitch and walkway, gangways on a continuous incline (drawn as the
incline itself, not as steps), a rear concourse with doors through the outer wall, the four avenues.

| venue | rows | seats | concourse doors | evacuation at 100% (default model) |
|---|---:|---:|---:|---:|
| S | 17 | 3 728 | 8 x 1.20 m | about 238 s (step 1362) |
| M | 43 | 15 832 | 28 x 1.20 m | about 563 s |
| L | 95 | 63 424 | 44 x 2.30 m | about 1 477 s |

In a seated venue the agents spawn one per occupied seat, standing in the strip in front of the seat, and **leave by its navigation
field**. The default model: the **queue-aware exit choice** -- every 3 s the agents compare, per candidate exit, the walk
(distance / 1.34 m/s) plus the queue ahead (the agents assigned to it and nearer to it / (its width x 83.6 persons/(m min))) and the ones that gain the most
switch, a few at a time; the lower rows of every stand go down their gangway and out through the avenues, the upper rows up to the
concourse doors -- the **incline speed** (0.58 m/s up, 0.655 m/s down the gangway inclines; Fruin 1971) and the **stair spacing** (the
headway time gap on the inclines, calibrated to measured stair flows). The panel's routing lines and the window title name the model
("navigation field, queue-aware exit choice, incline speed"); the readouts count the concourse doors per quadrant next to the four
avenues, the doors' and the avenues' shares of the evacuated ("Exit utilisation") and the exit width nobody has used yet. With every
seat of S occupied, the nearest exit at level speed (everyone up to a door) takes about 202 s (step 1153). A seated venue's capacity
line: design capacity = the seat count, jam capacity = its reachable floor at hexagonal packing (S: 18 138, 2513 m^2). In the zone
colouring an agent in a seated venue takes the zone of its 1 m metric cell (tread = the seat rows' standing strips, aisle = the
gangways, walkway = the walkway and the rear concourse). Exports are named `venue_S_N<agents>_...`.

## Agent colours

| colouring | what it shows | scale |
|---|---|---|
| speed | each agent's horizontal speed | 0 - 1.34 m/s (the free walking speed; no agent is faster) |
| density | the crowd density of the 1 m floor cell the agent stands in, in the last step | 0 / 1.08 / 2.17 / 5 / 10 / 20+ persons/m^2 |
| zone | where the agent is: tread, aisle, walkway, avenue, pitch, exit | one colour per zone |

Light blue is low, dark blue is high on both scales. On the density legend the three marks are the safety
thresholds: **LoS E** 1.08 and **LoS F** 2.17 persons/m^2 (the walkway levels of service E and F, Fruin 1971) and
**crush** 5 persons/m^2 (crush risk; Fruin 1993, Still 2000). These values are as reported in those sources and have not yet been
checked against the originals. The density scale gives each
band the same width, so the thresholds sit at fixed places on the bar. Grey agents stand in a cell without counted
floor. The zones are the metric zones: avenue = the four floor-level corridors to the exits, exit = the gap
in the outer wall, walkway = the ring between the pitch fence and the stands, aisle = the stepped passages beside
the avenue walls, tread = the stand rows and the back platform.

Note on the numbers: the bodies are hard (0.40 m across), so at most 7.2 persons/m^2 fit on the floor (hexagonal
packing). A 1 m cell's value can read a little above that, because each agent is shared among the four cells around it,
and cells with little walkable floor can read higher. The 10 and 20+ bands remain for stress runs above the jam
capacity, whose spawn starts stacked.

## Heatmap overlay

The overlay paints the stadium's floors (treads, aisles, walkway, avenues, pitch, platform; walls and risers stay
grey) with one value per **1 m x 1 m floor cell** of the metric grid, accumulated since the last restart. It
is computed and drawn on the GPU (nothing is read back), can be switched on and off at any time (H), and switches on
by itself when everyone has left.

| metric | definition | colour scale |
|---|---|---|
| Peak density | the highest density the cell had in any step | 0 / LoS E 1.08 / LoS F 2.17 / crush 5 / 10 / 20+ persons/m^2, equal width per band |
| Density (last step) | the cell's density now | same |
| Time >= LoS E (1.08) | how long the cell was at or above 1.08 persons/m^2 | 0 - 120 s (120+) |
| Time >= LoS F (2.17) | how long at or above 2.17 persons/m^2 | 0 - 120 s (120+) |
| Time >= crush (5) | how long at or above 5 persons/m^2 | 0 - 120 s (120+) |
| Mean speed when occupied | the average horizontal speed of the people in the cell, weighted by how many were there and for how long | 0 - 1.34 m/s |
| Crush exposure | person-seconds spent in the cell while it was at or above 5 persons/m^2 | 1 - 1000 person-s, logarithmic (1000+) |
| Distance to the nearest exit (seated venues) | the navigation field's shortest legal walking distance from the point to the nearest exit; static, per 0.05 m field cell, not a metric cell | 0 - 30 m (30+); normal shading where no path exists (seat-block and wall tops, the pitch); not offered on the terrace |

Density = the people in the cell (each agent counts as one person shared among the four cells around it) divided by
the cell's walkable floor area. The ranges are **fixed**, so two screenshots are always comparable; larger crowds reach the dark
end sooner. The terrace's 4096 agents evacuate in about 474 s and wait on the treads long
enough for the time and exposure maps to saturate there. Values beyond the end of a scale take its darkest colour.

Three looks: **blue** (light to dark) = a value; **light grey** = floor with value 0 (for mean speed: nobody was
ever there), e.g. the pitch, which nobody can enter; **normal concrete shading** = no data (no counted floor in that
cell, or not a floor).

## Export

**Screenshot** (F12 or the button): the current view at the window's resolution, without the panel unless "include
the panel" is checked, showing the exact current state.

**Top-down heatmap export** (F9 or the button): a straight-down orthographic image of the venue's whole metric
grid (the terrace and S 64 m x 64 m, M 128 m, L 208 m) with the selected overlay metric, 4096 x 4096 px (8192 selectable), no panel, agents off
unless "agents" is checked. North (+y) is up, +x to the right, the image centre is the pitch centre. A `.json` file
with the same name records what the colours mean (metric, definition, unit, scale stops and ticks, ramp colours),
the extent in metres, the pixel scale, N, the simulated time, the commit and the GPU.

Files go to a `screenshots` folder beside the program (or `--screenshot-dir`), named
`<venue>_N<agents>_t<simulated seconds>s_<commit>[_heatmap-<metric>].png`, for example
`stadium_N4096_t474.3s_1a2b3c4_heatmap-peak-density.png`; `-dirty` after the commit means the build had uncommitted
changes; `_2`, `_3`, ... are added if the name exists. Each export reads the image back from the GPU once, when you
ask for it.

Figures without touching the mouse: run to the end at 20x and export the final state, e.g.

```bash
out/build/x64-Release/SWARM.exe --playback 20 --run-seconds 10 --overlay exposure --camera isometric --export-on-exit
```

(the run pauses itself when everyone has left; the 4096-agent evacuation takes 474 simulated seconds,
about 24 s at 20x).

## Checks

`SWARM --selftest-ui` runs the viewer in a hidden window for about 420 frames with the panel: it restarts with
another N and back, cycles every agent colouring, overlay metric, camera preset and key, writes a screenshot (with
the panel) and a heatmap export to `out/selftest/` (`selftest_out/` in the current folder for a package build), checks for OpenGL errors after every frame, and checks that the
agent state after 250 steps (the golden state's step count) is bit-identical to a run without any viewer (and to the
pinned golden state). It also restarts at 16384 and 65536 agents to check the capacity labels in the panel and the
title, switches to venue S through the venue selector (every seat occupied; the agents move off their seats; the state after
250 steps is bit-identical to a run without the viewer; the capacity label and the title naming the default model; the distance
overlay colours the floor; a screenshot; the evacuation completes within 5 frames of step 1362, through the doors and the avenues;
a restart at 50% of the seats), and it fails if any two widgets of the panel share an ID (Dear ImGui would let them share their
state); a planted pair of identical buttons proves
the check sees such conflicts. Then it
runs to the end of the evacuation and checks that the overlay switched on and the playback paused. It prints
`SELFTEST ALL PASSED` and exits 0.

The self-test's restarts complete within their frame; one phase (`viewer.background_loading`) instead switches from venue L to venue S
through the loading screen and checks that its 12 programs were compiled ahead and all of them used, and that the state after
250 steps is bit-identical to the restart within the frame (and to the pinned golden state).
`SWARM --selftest-ui --no-parallel-compile` (or `SWARM_NO_PARALLEL_COMPILE=1`) runs that phase with one program per frame.

`viewer.gpu_capabilities` checks the GPU capability check: every program's SSBO bindings (every venue, S also with the nearest exit) against the binding
lists the requirements come from, then a simulated GPU with 16 bindings, clicking the real venue selector: a disabled venue cannot be
selected, an enabled one can.

`SWARM cell --n N --state spawn|congested ...` times the simulation passes inside the viewer's frame loop (with the
panel when `SWARM_VIEWER_UI=1`); `tools/perf_ab/ab.py` drives it for the UI on / off comparison.

## Known limitations

- The panel's readouts trail the picture by a few frames (they are never waited for).
- `stadium.obj`'s stand blocks are modelled inside-out; the viewer lights both sides of every face, so this does not
  show. The simulation uses `stadium.sdf` and is unaffected.
- Frames are uncapped unless VSync is on (V): the GPU renders as fast as it can even at 1x real time.
- While a venue loads, the picture pauses during the link and the first dispatch of its shader programs (seconds when the driver's
  shader cache is warm, minutes when it is cold); the window keeps responding. On a driver without `GL_ARB_parallel_shader_compile`
  each program's compile waits in its own frame, so a cold compile can still make the window "Not Responding" for a while.
- `SWARM.exe` is a console program. Started outside a console on Windows 11 with Windows Terminal as the default terminal, it also opens a
  Terminal window; on the development PC those windows stayed open, blank, after SWARM exited, and closing one while SWARM runs ends SWARM.
  Started repeatedly about 2 s apart that way, 9 of 246 starts failed with Windows' "The application was unable to start correctly
  (0xc0000142)", and a Windows tool (`whoami.exe`) failed the same way; 174 starts with no new console all succeeded. A single start by hand
  was not tested. Scripts should start SWARM with no new console window.
