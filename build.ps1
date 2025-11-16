# Simple PowerShell build script for Windows
# This script compiles all .cpp files in src/ into build/ folder

$srcDir = "src"
$buildDir = "build"
$includeDir = "include"

# Create build directory if it doesn't exist
if (!(Test-Path $buildDir)) {
    New-Item -ItemType Directory -Path $buildDir | Out-Null
    Write-Host "Created $buildDir directory"
}

# Find all .cpp files
$cppFiles = Get-ChildItem $srcDir -Filter "*.cpp" -File

if ($cppFiles.Count -eq 0) {
    Write-Host "Error: No .cpp files found in $srcDir"
    exit 1
}

Write-Host "Found $($cppFiles.Count) source file(s) to compile"

# Try to find a C++ compiler
$compiler = $null
$compilerArgs = @()

# Try cl.exe (MSVC) first
if (Get-Command cl.exe -ErrorAction SilentlyContinue) {
    $compiler = "cl.exe"
    $compilerArgs = @("/std:c++17", "/I$includeDir", "/W3", "/Fo$buildDir\", "/Fe$buildDir\main.exe")
    Write-Host "Using MSVC compiler (cl.exe)"
}
# Try g++ (MinGW/GCC)
elseif (Get-Command g++ -ErrorAction SilentlyContinue) {
    $compiler = "g++"
    $compilerArgs = @("-std=c++17", "-I$includeDir", "-Wall", "-o", "$buildDir\main.exe")
    Write-Host "Using GCC compiler (g++)"
}
else {
    Write-Host "Error: No C++ compiler found (cl.exe or g++)"
    Write-Host "Please install Visual Studio C++ Build Tools or MinGW"
    exit 1
}

# Compile
Write-Host "Compiling..."
$sourceFiles = $cppFiles | ForEach-Object { $_.FullName }

if ($compiler -eq "cl.exe") {
    & $compiler @compilerArgs $sourceFiles
} else {
    & $compiler @compilerArgs $sourceFiles
}

if ($LASTEXITCODE -eq 0) {
    Write-Host "Compilation successful!"
    Write-Host "Executable created at: $buildDir\main.exe"
} else {
    Write-Host "Compilation failed!"
    exit 1
}
