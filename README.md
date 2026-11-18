# SFML-project

Space Shooter mid-evaluation project using C++17 and SFML 3.1.0.

This initial contribution contains Bilal's two commented sections from the
original 98-line, single-file mid-evaluation `main.cpp`:

- Loading the five artwork textures and setting up the background, player,
  and 780 x 780 window.
- Moving the player with the four arrow keys.

A small shared event/render loop keeps this contribution runnable: it handles
window closing and displays the background and player. Humail's enemy formation
and Abdullah's firing/bullet logic are left for their own contributions. The
preview currently shows the background and a movable player, without enemies
or shooting. Movement retains the original per-frame speed and has no boundary
restriction. Close the window with its X button to exit.

## Build and run on Windows

Install MSYS2 UCRT64 GCC and GDB compatible with the bundled SFML libraries
(the original setup uses GCC 15.2.0 at `C:\msys64\ucrt64\bin`). The compiler
is installed separately; the SFML headers, libraries, DLLs and license are
included in `vendor/SFML3`.

Open this repository folder in VS Code, or double-click `run.cmd`.

```powershell
# Build
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1

# Build and run
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Run

# Use a compatible compiler installed elsewhere
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Compiler 'D:\msys64\ucrt64\bin\g++.exe' -Run
```

In VS Code, use Ctrl+Shift+B to build and F5 to debug with the Microsoft C/C++
extension. If MSYS2 is installed elsewhere, update the compiler path in
`.vscode/c_cpp_properties.json` and the debugger path in `.vscode/launch.json`.
For the default VS Code build and launcher, also update `build.ps1`'s default
compiler path.

The launcher and debugger use `assets` as the working directory. When starting
the executable manually, run it from that folder so `img/...` paths resolve:

```powershell
cd assets
..\build\space-shooter-mid.exe
```

The build copies SFML and compiler runtime DLLs beside the executable in
`build`. Generated executables and object files are ignored by Git.

## Repository contents

- `main.cpp`: Bilal's original setup and movement sections, plus shared preview support.
- `assets`: the five images loaded by the original setup section.
- `vendor/SFML3`: the matching SFML dependency package and its license.
- `build.ps1`, `run.cmd`, `.vscode`: build, launch and editor configuration.

Keep subsequent game contributions in this same `main.cpp`. SFML's license is
included at `vendor/SFML3/share/doc/SFML/license.md`.
