cmake_minimum_required(VERSION 3.15)
project(SwarmEngine VERSION 1.0.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# The C++ runtime is linked statically. MSVC has no static OpenMP runtime: vcomp140.dll stays a DLL (vcomp140d.dll in
# Debug), which comes from Visual Studio or the Microsoft Visual C++ Redistributable; the release archive does not carry it.
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# --- 1. CONFIGURATION & DEPENDENCIES ---

# A. GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

if(EXISTS "${CMAKE_SOURCE_DIR}/external/glfw/CMakeLists.txt")
    add_subdirectory(external/glfw)
else()
    message(FATAL_ERROR "Missing external/glfw/CMakeLists.txt")
endif()

# B. GLM
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE "${CMAKE_SOURCE_DIR}/external/glm")

# C. GLAD
if(EXISTS "${CMAKE_SOURCE_DIR}/external/glad/src/glad.c")
    add_library(glad "${CMAKE_SOURCE_DIR}/external/glad/src/glad.c")
    target_include_directories(glad PUBLIC "${CMAKE_SOURCE_DIR}/external/glad/include")
else()
    message(FATAL_ERROR "Could not find external/glad/src/glad.c")
endif()

# --- 2. BUILD CONFIGURATION ---

# A build from the source tree finds its assets there as a last resort. A package build turns this off, so that no
# path of the build machine ends up in the executables; the assets then sit beside the executable.
option(SWARM_EMBED_SOURCE_DIR "Compile the source tree's path into the programs" ON)
set(SWARM_SOURCE_DIR_DEF "")
if(SWARM_EMBED_SOURCE_DIR)
    set(SWARM_SOURCE_DIR_DEF "SWARM_SOURCE_DIR=\"${CMAKE_SOURCE_DIR}\"")
endif()

# Build-time commit metadata (include/swarm/build_info.hpp). The custom target runs
# cmake/build_info.cmake on every build; the script asks git for HEAD and the dirty state and
# rewrites generated/swarm_git_info.h only when they changed. The header is a byproduct, so Ninja
# re-checks its timestamp (restat): an unchanged state rebuilds nothing, a new commit recompiles
# src/build_info.cpp alone and relinks. Unlike a configure-time execute_process, this needs no
# reconfigure and no reflog (a fresh worktree has none when CMake first configures).
find_package(Git QUIET)
set(SWARM_GENERATED_DIR "${CMAKE_BINARY_DIR}/generated")
set(SWARM_GIT_INFO_H "${SWARM_GENERATED_DIR}/swarm_git_info.h")
add_custom_target(swarm_build_info_gen
    COMMAND "${CMAKE_COMMAND}" "-DSRC_DIR=${CMAKE_SOURCE_DIR}" "-DOUT=${SWARM_GIT_INFO_H}" "-DGIT=${GIT_EXECUTABLE}"
            -P "${CMAKE_SOURCE_DIR}/cmake/build_info.cmake"
    BYPRODUCTS "${SWARM_GIT_INFO_H}"
    COMMENT "Checking the git commit metadata"
    VERBATIM
)
add_library(swarm_build_info STATIC src/build_info.cpp)
add_dependencies(swarm_build_info swarm_build_info_gen)
target_include_directories(swarm_build_info PUBLIC "${CMAKE_SOURCE_DIR}/include" PRIVATE "${SWARM_GENERATED_DIR}")
target_compile_definitions(swarm_build_info PRIVATE "SWARM_BUILD_CONFIG=\"$<CONFIG>\"")

# Simulation core shared by the app and the headless GPU test
add_library(swarm_core STATIC
    src/shader.cpp
    src/assets.cpp
    src/sdf.cpp
    src/gpu_caps.cpp
    src/crowd_sim.cpp
    src/cpu_crowd_sim.cpp
    src/metrics.cpp
    src/async_counters.cpp
    src/venue.cpp
    src/nav_field.cpp
    src/exit_choice.cpp
)
target_include_directories(swarm_core PUBLIC "${CMAKE_SOURCE_DIR}/include")
# OpenMP for the CPU reference (cpu_crowd_sim.cpp). On MSVC this is plain /openmp (OpenMP 2.0,
# vcomp140.dll; OpenMP_RUNTIME_MSVC left unset): 'parallel for' with a schedule clause and num_threads
# over a signed int index is all the CPU reference uses, and 2.0 has it. /openmp:llvm would add
# the LLVM runtime (libomp140) as a dependency for no functional gain.
find_package(OpenMP REQUIRED)
target_link_libraries(swarm_core PRIVATE OpenMP::OpenMP_CXX)
# IEEE float semantics for the CPU reference: /fp:precise (MSVC's default, stated explicitly).
# Never /fp:fast: it licenses reassociation and contraction, so the port would no longer follow
# the shaders' operation order.
if(MSVC)
    target_compile_options(swarm_core PRIVATE /fp:precise)
endif()
# Last-resort asset lookup when neither the exe directory nor the CWD has the assets
target_compile_definitions(swarm_core PRIVATE ${SWARM_SOURCE_DIR_DEF})
target_link_libraries(swarm_core PUBLIC glad glm swarm_build_info)

# Link System OpenGL
if(WIN32)
    target_link_libraries(swarm_core PUBLIC opengl32)
else()
    target_link_libraries(swarm_core PUBLIC GL)
endif()

# D. Dear ImGui (the viewer's control panel): pinned release, unmodified, GLFW + OpenGL3 backends
# (external/imgui/PINNED.txt). The OpenGL3 backend carries its own GL loader; only SWARM links it.
add_library(imgui STATIC
    external/imgui/imgui.cpp
    external/imgui/imgui_demo.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/backends/imgui_impl_glfw.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC "${CMAKE_SOURCE_DIR}/external/imgui" "${CMAKE_SOURCE_DIR}/external/imgui/backends")
target_link_libraries(imgui PUBLIC glfw)
# ImGui's test-engine item hooks, implemented by src/viewer/imgui_id_check.cpp (SWARM --selftest-ui counts widget ID
# conflicts with them; they run only while the self-test enables them). A build definition only: the sources stay unmodified.
target_compile_definitions(imgui PUBLIC IMGUI_ENABLE_TEST_ENGINE)

# The viewer application (src/viewer). It steps the simulation and reads its buffers for rendering; it never writes
# simulation state.
add_executable(SWARM
    src/main.cpp
    src/viewer/export.cpp
    src/viewer/imgui_id_check.cpp
    src/viewer/legend.cpp
    src/viewer/message_box.cpp
    src/viewer/orbit_camera.cpp
    src/viewer/scene.cpp
    src/viewer/selftest.cpp
    src/viewer/timing_cell.cpp
    src/viewer/viewer.cpp
)
# tools/: golden_state.hpp (self-test) and benchmark/bench_common.hpp (timing cell)
target_include_directories(SWARM PRIVATE "${CMAKE_SOURCE_DIR}/src" "${CMAKE_SOURCE_DIR}/external/stb" "${CMAKE_SOURCE_DIR}/tools")
# The self-test's output folder: <source tree>/out/selftest (src/viewer/selftest.cpp)
target_compile_definitions(SWARM PRIVATE ${SWARM_SOURCE_DIR_DEF})
target_link_libraries(SWARM PRIVATE swarm_core glfw imgui)

# Headless GPU verification (hidden 4.3 core context): shaders, SDF, pipeline invariants, timings
add_executable(test_gpu tools/test_gpu.cpp)
# OpenMP: the per-step plausibility checks run over the agents in parallel
target_link_libraries(test_gpu PRIVATE swarm_core glfw OpenMP::OpenMP_CXX)

# Fixed-step clock unit tests (header-only clock, no GL)
add_executable(test_clock tools/test_clock.cpp)
target_include_directories(test_clock PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(test_clock PRIVATE swarm_build_info)

# --- Benchmark tools (tools/benchmark) ---
# Run metadata: the commit and dirty flag come from swarm_build_info at build time (above); the
# build type and the compile flags of the simulation core are configure-time facts (they only
# change on a reconfigure) and go in as definitions.
string(TOUPPER "${CMAKE_BUILD_TYPE}" SWARM_BUILD_TYPE_UC)
get_target_property(SWARM_CORE_OPTS swarm_core COMPILE_OPTIONS)
if(NOT SWARM_CORE_OPTS)
    set(SWARM_CORE_OPTS "")
endif()
string(REPLACE ";" " " SWARM_CORE_OPTS "${SWARM_CORE_OPTS}")
set(SWARM_CORE_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_${SWARM_BUILD_TYPE_UC}} ${OpenMP_CXX_FLAGS} ${SWARM_CORE_OPTS}")
string(STRIP "${SWARM_CORE_FLAGS}" SWARM_CORE_FLAGS)
set(SWARM_BENCH_DEFS
    SWARM_BUILD_TYPE="${CMAKE_BUILD_TYPE}"
    SWARM_CORE_FLAGS="${SWARM_CORE_FLAGS}")
message(STATUS "Benchmark metadata: ${CMAKE_BUILD_TYPE}, core flags: ${SWARM_CORE_FLAGS} (commit: at build time)")

# CPU tuning: snapshots, golden admissibility check, OpenMP schedule sweep
add_executable(cpu_tune tools/benchmark/cpu_tune.cpp)
target_link_libraries(cpu_tune PRIVATE swarm_core glfw)
target_compile_definitions(cpu_tune PRIVATE ${SWARM_BENCH_DEFS})
add_dependencies(cpu_tune SWARM_assets)

# Physics sub-phase profile: its own copy of the CPU reference, compiled with SWARM_CPU_PROFILE
add_executable(cpu_profile tools/benchmark/cpu_profile.cpp src/cpu_crowd_sim.cpp src/sdf.cpp src/assets.cpp src/venue.cpp src/shader.cpp src/nav_field.cpp src/exit_choice.cpp)
target_include_directories(cpu_profile PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_compile_definitions(cpu_profile PRIVATE SWARM_CPU_PROFILE ${SWARM_SOURCE_DIR_DEF} ${SWARM_BENCH_DEFS})
target_link_libraries(cpu_profile PRIVATE OpenMP::OpenMP_CXX glad glm glfw swarm_build_info)
if(MSVC)
    target_compile_options(cpu_profile PRIVATE /fp:precise)
endif()
if(WIN32)
    target_link_libraries(cpu_profile PRIVATE opengl32)
endif()
add_dependencies(cpu_profile SWARM_assets)

# GPU vs CPU benchmark: snapshot and trajectory modes, drift-controlled rounds, CSV + summary output
# (tools/benchmark/benchmark_crowd.cpp)
add_executable(benchmark_crowd tools/benchmark/benchmark_crowd.cpp)
target_link_libraries(benchmark_crowd PRIVATE swarm_core glfw OpenMP::OpenMP_CXX)
target_compile_definitions(benchmark_crowd PRIVATE ${SWARM_BENCH_DEFS})
add_dependencies(benchmark_crowd SWARM_assets)

# GPU diagnostics: correctness at every benchmark size, sort and physics scaling, buffer placement, the sort's
# byte-identity check (tools/benchmark/gpu_diag.cpp)
add_executable(gpu_diag tools/benchmark/gpu_diag.cpp)
target_link_libraries(gpu_diag PRIVATE swarm_core glfw OpenMP::OpenMP_CXX)
target_compile_definitions(gpu_diag PRIVATE ${SWARM_BENCH_DEFS})
add_dependencies(gpu_diag SWARM_assets)

# Experiment runner: headless evacuation with the safety metrics, outputs in real units
# (tools/experiment/run_experiment.cpp; plot_heatmap.py draws heatmap.csv)
add_executable(run_experiment tools/experiment/run_experiment.cpp)
# OpenMP: the per-step checks (tools/plausibility.hpp Monitor, tools/venue_s.hpp Checker) run over the agents in parallel,
# as in test_gpu; without it their loops run on one thread
target_link_libraries(run_experiment PRIVATE swarm_core glfw OpenMP::OpenMP_CXX)
target_compile_definitions(run_experiment PRIVATE ${SWARM_BENCH_DEFS})
add_dependencies(run_experiment SWARM_assets)

# Fundamental diagram and calibration: periodic corridor scenario, Weidmann comparison, parameter grid
# with the plausibility checks (tools/fd/fd_harness.cpp; fd_plot.py draws fd.csv)
add_executable(fd_harness tools/fd/fd_harness.cpp)
target_link_libraries(fd_harness PRIVATE swarm_core glfw)
target_compile_definitions(fd_harness PRIVATE ${SWARM_BENCH_DEFS})
add_dependencies(fd_harness SWARM_assets)

# Step-up probe: floor rises per step, unreachable floors and riser climbs in the terrace evacuation, the
# venue's floor area and jam capacity (tools/stepup/step_probe.cpp; tools/stepup.hpp is shared with test_gpu)
add_executable(step_probe tools/stepup/step_probe.cpp)
target_link_libraries(step_probe PRIVATE swarm_core glfw OpenMP::OpenMP_CXX)
target_compile_definitions(step_probe PRIVATE ${SWARM_BENCH_DEFS})
add_dependencies(step_probe SWARM_assets)

# Seated venues: the generator's layout report, the analytic distance's exactness and GPU cost, the render mesh
# (tools/venue/venue_probe.cpp)
add_executable(venue_probe tools/venue/venue_probe.cpp)
target_link_libraries(venue_probe PRIVATE swarm_core glfw OpenMP::OpenMP_CXX)
target_compile_definitions(venue_probe PRIVATE ${SWARM_BENCH_DEFS})
add_dependencies(venue_probe SWARM_assets)

# Navigation field: the traversability grid and the distance field of an analytic venue, their reports and checks
# (tools/nav/nav_probe.cpp)
add_executable(nav_probe tools/nav/nav_probe.cpp)
target_include_directories(nav_probe PRIVATE "${CMAKE_SOURCE_DIR}/external/stb")
target_link_libraries(nav_probe PRIVATE swarm_core glfw OpenMP::OpenMP_CXX)
target_compile_definitions(nav_probe PRIVATE ${SWARM_BENCH_DEFS})
add_dependencies(nav_probe SWARM_assets)

# --- 3. RUNTIME ASSETS ---
# Copy shaders and stadium data next to the executable. One rule per file, each depending
# on its source, so editing a shader re-copies it on the next build even without a relink.
file(GLOB SWARM_SHADER_FILES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/shaders/*")
set(SWARM_ASSET_FILES
    ${SWARM_SHADER_FILES}
    "${CMAKE_SOURCE_DIR}/stadium.obj"
    "${CMAKE_SOURCE_DIR}/stadium.sdf"
    "${CMAKE_SOURCE_DIR}/venue_s.obj"
)
set(SWARM_ASSET_OUTPUTS)
foreach(asset IN LISTS SWARM_ASSET_FILES)
    file(RELATIVE_PATH asset_rel "${CMAKE_SOURCE_DIR}" "${asset}")
    set(asset_out "${CMAKE_CURRENT_BINARY_DIR}/${asset_rel}")
    add_custom_command(
        OUTPUT "${asset_out}"
        COMMAND ${CMAKE_COMMAND} -E copy "${asset}" "${asset_out}"
        DEPENDS "${asset}"
        COMMENT "Copying ${asset_rel}"
        VERBATIM
    )
    list(APPEND SWARM_ASSET_OUTPUTS "${asset_out}")
endforeach()
add_custom_target(SWARM_assets ALL DEPENDS ${SWARM_ASSET_OUTPUTS})
add_dependencies(SWARM SWARM_assets)
add_dependencies(test_gpu SWARM_assets)
