param(
    [switch]$Run,
    [string]$Compiler = 'C:\msys64\ucrt64\bin\g++.exe'
)

$ErrorActionPreference = 'Stop'
$compilerDirectory = Split-Path -Parent $Compiler
$sfmlDirectory = Join-Path $PSScriptRoot 'vendor\SFML3'
$buildDirectory = Join-Path $PSScriptRoot 'build'
$source = Join-Path $PSScriptRoot 'main.cpp'
$executable = Join-Path $buildDirectory 'space-shooter-mid.exe'

if (!(Test-Path -LiteralPath $Compiler)) {
    throw "The compiler was not found at $Compiler. Set -Compiler to your compatible UCRT64 g++.exe."
}
if (!(Test-Path -LiteralPath (Join-Path $sfmlDirectory 'include\SFML\Graphics.hpp'))) {
    throw 'The local SFML 3.1 library is missing from vendor\SFML3.'
}
if (Test-Path -LiteralPath $executable) {
    try {
        $outputCheck = [IO.File]::Open($executable, 'Open', 'ReadWrite', 'None')
        $outputCheck.Dispose()
    } catch [System.IO.IOException], [System.UnauthorizedAccessException] {
        throw 'Close this game window and stop its debugger before building again.'
    }
}

New-Item -ItemType Directory -Path $buildDirectory -Force | Out-Null
$env:PATH = "$compilerDirectory;$env:PATH"
& $Compiler -std=c++17 -g -O0 -Wall -Wextra -Wpedantic -Werror `
    "-I$sfmlDirectory\include" $source "-L$sfmlDirectory\lib" `
    -lsfml-graphics -lsfml-window -lsfml-system -o $executable
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

Get-ChildItem -LiteralPath (Join-Path $sfmlDirectory 'bin') -Filter '*.dll' |
    Copy-Item -Destination $buildDirectory -Force
foreach ($runtime in @('libgcc_s_seh-1.dll', 'libstdc++-6.dll', 'libwinpthread-1.dll')) {
    Copy-Item -LiteralPath (Join-Path $compilerDirectory $runtime) -Destination $buildDirectory -Force
}
Write-Host "Built: $executable"
if ($Run) {
    Push-Location (Join-Path $PSScriptRoot 'assets')
    try {
        & $executable
        $gameExitCode = $LASTEXITCODE
    } finally { Pop-Location }
    exit $gameExitCode
}
