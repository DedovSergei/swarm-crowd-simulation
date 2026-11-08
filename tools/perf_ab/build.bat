@echo off
rem Usage: build.bat <srcDir> <buildDir>
rem Configures (Ninja, Release) and builds the SWARM tree at <srcDir> into <buildDir>, then compiles
rem bench.cpp (next to this script) against that build into <buildDir>\bench.exe.
rem Needs the MSVC x64 environment: run from an x64 Native Tools prompt, or set VCVARS64 to the
rem path of vcvars64.bat (default: Visual Studio 2026 Community).
setlocal
if "%~2"=="" (
    echo usage: build.bat ^<srcDir^> ^<buildDir^>
    exit /b 2
)
set "SRC=%~f1"
set "BLD=%~f2"
set "HERE=%~dp0"

where cl >nul 2>&1 && goto :haveCl
if not defined VCVARS64 set "VCVARS64=C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars64.bat"
call "%VCVARS64%" >nul 2>&1
where cl >nul 2>&1 || (
    echo MSVC not found: set VCVARS64 to your vcvars64.bat
    exit /b 1
)
:haveCl

if not exist "%BLD%\build.ninja" (
    cmake -S "%SRC%" -B "%BLD%" -G Ninja -DCMAKE_BUILD_TYPE=Release || exit /b 1
)
cmake --build "%BLD%" || exit /b 1
rem Build-time commit metadata: older engine versions have no swarm_build_info.lib (bench.exe then says "unknown")
set "INFOLIB="
if exist "%BLD%\swarm_build_info.lib" set "INFOLIB=%BLD%\swarm_build_info.lib"
cl /nologo /std:c++17 /EHsc /O2 /MD /DNDEBUG ^
   /I"%SRC%\external\glad\include" /I"%SRC%\external\glfw\include" /I"%SRC%\external\glm" /I"%SRC%\include" ^
   "%HERE%bench.cpp" /Fe:"%BLD%\bench.exe" /Fo:"%BLD%\bench.obj" ^
   /link "%BLD%\swarm_core.lib" %INFOLIB% "%BLD%\glad.lib" "%BLD%\external\glfw\src\glfw3.lib" opengl32.lib user32.lib gdi32.lib shell32.lib || exit /b 1
echo built %BLD%\bench.exe
