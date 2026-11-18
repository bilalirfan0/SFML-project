# SFML-project

Space Shooter mid-evaluation project using C++17 and SFML 3.1.0.

The combined mid-evaluation game is implemented in a single `main.cpp`.
Bilal, Humail and Abdullah's sections have been merged into `main`. The game
logic matches the original 98-line laptop source; the current source has
additional blank lines and different indentation.

## Current gameplay and controls

The game opens directly in a 780 x 780 window with a space background, the
player ship, and six stationary enemies in two rows of three.

| Control | Action |
| --- | --- |
| Arrow keys | Move the player left, right, up and down. |
| Space | Fire one bullet; release Space before firing again. |
| Escape or the window's close button | Exit the game. |

Player bullets move upward and are removed after leaving the top of the screen.
This is the mid-evaluation prototype: bullets pass through enemies, enemies do
not move or attack, and there is no collision damage, scoring, lives, menu or
level progression. Player movement has no screen-boundary restriction. Movement
and bullet speeds are per frame, so their speed depends on the frame rate.

## Member sections in main.cpp

| Member | Sections identified by the source comments |
| --- | --- |
| Bilal | Artwork loading, background/player/window setup, and four-way player movement. |
| Humail | Sprite containers, two rows of enemies, and drawing the scene. |
| Abdullah | Firing state, window/keyboard events, shot rearming, bullet creation, movement and removal. |

## Requirements and bundled SFML version

- **Windows 64-bit** for the supplied binaries and build/debug configuration.
- **C++17** with a compatible **MSYS2 UCRT64 GCC** toolchain. The verified local
  compiler is GCC **15.2.0**, installed at `C:\msys64\ucrt64\bin\g++.exe`.
- **GDB** for F5 debugging, at `C:\msys64\ucrt64\bin\gdb.exe` by default.
- **SFML 3.1.0**, bundled in `vendor/SFML3`. Its headers, CMake package version
  and all three supplied SFML DLLs identify version 3.1.0.
- VS Code and its Microsoft C/C++ extension are optional for editing/debugging;
  `run.cmd` and the PowerShell build command work without VS Code.

The supplied SFML package includes the headers, import libraries and runtime
DLLs needed for this game. The build links `sfml-graphics`, `sfml-window` and
`sfml-system`. The compiler and debugger must be installed separately. A
different compiler toolchain requires compatible SFML binaries.

## Build and run on Windows

Clone this repository, or download and extract it. Open the folder containing
`main.cpp`, `build.ps1`, `assets` and `vendor` in VS Code, or double-click
`run.cmd`. Close any running game/debug session before rebuilding.

Run these commands from the repository root:

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
`build`: `sfml-graphics-3.dll`, `sfml-window-3.dll`, `sfml-system-3.dll`,
`libgcc_s_seh-1.dll`, `libstdc++-6.dll` and `libwinpthread-1.dll`. Keep these
DLLs beside `space-shooter-mid.exe`. Generated executables and object files
are ignored by Git and are created when you build.

## Included images

All five images loaded by `main.cpp` are committed to this repository:

| File | Purpose |
| --- | --- |
| [assets/img/abdullah.jpg](assets/img/abdullah.jpg) | Space background. |
| [assets/img/level1c.png](assets/img/level1c.png) | Player ship. |
| [assets/img/enemy_laser.png](assets/img/enemy_laser.png) | Player bullet. |
| [assets/img/PNG/Enemies/enemyGreen1.png](assets/img/PNG/Enemies/enemyGreen1.png) | First enemy row. |
| [assets/img/PNG/Enemies/enemyBlue1.png](assets/img/PNG/Enemies/enemyBlue1.png) | Second enemy row. |

Preserve these filenames and folder paths. `main.cpp` loads them as `img/...`
relative to the `assets` working directory. If artwork cannot be loaded, start
the game with `run.cmd` or the supplied build/debug commands.

## Repository contents

- `main.cpp`: the combined game with all three member sections.
- `assets`: all five required images listed above.
- `vendor/SFML3`: SFML 3.1.0 headers, libraries, DLLs and license.
- `build.ps1`, `run.cmd`, `.vscode`: build, launch and editor configuration.
- `.gitignore`: excludes generated build outputs and object files.
- `build`: generated locally when compiling; not committed.

The combined source has compiled with `-Wall -Wextra -Wpedantic -Werror` on
the verified local setup. Local controlled-input checks passed for enemy
placement, all four movement directions, one-shot limiting/rearming, bullets
passing through stationary enemies, off-screen bullet removal and rendering
with the real images. The verification scripts/previews used for those checks
are local build artifacts and are not included in the repository.

SFML's license is included at
[vendor/SFML3/share/doc/SFML/license.md](vendor/SFML3/share/doc/SFML/license.md).
