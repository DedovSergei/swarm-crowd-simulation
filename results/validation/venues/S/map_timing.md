# Venue S: GPU cost of map() (Task 5.4 stage 2)

venue_probe timing | commit 34ce181213ce4c8dd3079f50c638860253835407 (dirty 0) | Release | 2026-10-08 18:18 | AMD  Radeon RX 7800 XT | 4.3.0 Core Profile Context 26.8.1.260810 | power throttling off (SetProcessInformation, EXECUTION_SPEED)

262144 invocations x 64 calls each (a dependent walk from near-surface points: the rest height above the floor, +-4 mm), GL_TIME_ELAPSED per dispatch, 15 repetitions after 3 warm-up dispatches; ns per call = time / calls. Physics.comp's own functions (the @sdf block on each venue's preamble).

| function | median ns/call | min | max | ratio to the baked texture |
|---|---:|---:|---:|---:|
| baked texture map() | 0.0456 | 0.0454 | 0.0462 | 1.0x |
| analytic S map() | 0.1425 | 0.1301 | 0.1466 | 3.1x |
| baked texture mapExactGrad() | 0.0462 | 0.0459 | 0.0467 | 1.0x |
| analytic S mapExactGrad() | 0.1422 | 0.1295 | 0.1469 | 3.1x |

Note: ns per call over the whole GPU (all compute units in parallel): a throughput figure, not the latency of one call.
