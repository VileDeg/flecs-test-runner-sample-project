<#
.SYNOPSIS
    Builds the project using local sibling directories for dependencies.
.DESCRIPTION
    Configures CMake with local overrides for 'modules' and 'test-runner',
    then runs the build.
.PARAMETER Clean
    If set, deletes the 'build' directory before starting. 
    Use this if CMake gets confused about old paths.
#>
param (
    [switch]$Clean
)

$BuildDir = "build"
$ModulesPath = "../flecs-test-runner-modules"
$TestRunnerPath = "../flecs-test-runner"

# --- Step 1: Clean Build Directory (Optional) ---
if ($Clean) {
    if (Test-Path $BuildDir) {
        Write-Host "[-] Clean requested. Removing '$BuildDir'..." -ForegroundColor Yellow
        Remove-Item -Path $BuildDir -Recurse -Force -ErrorAction SilentlyContinue
    }
}

# --- Step 2: Configure CMake ---
Write-Host "[*] Configuring CMake with local overrides..." -ForegroundColor Cyan
Write-Host "    - Modules: $ModulesPath" -ForegroundColor Gray
Write-Host "    - Test Runner: $TestRunnerPath" -ForegroundColor Gray

# We use the Call Operator (&) and an array for clean argument handling
$CmakeArgs = @(
    "-S", ".",
    "-B", $BuildDir,
    "-DFETCHCONTENT_SOURCE_DIR_MODULES=$ModulesPath",
    "-DFETCHCONTENT_SOURCE_DIR_TEST_RUNNER=$TestRunnerPath"
)

& cmake $CmakeArgs

# Check if configuration failed
if ($LASTEXITCODE -ne 0) {
    Write-Host "[!] Configuration Failed." -ForegroundColor Red
    exit 1
}

# --- Step 3: Build the Project ---
Write-Host "[*] Building project..." -ForegroundColor Cyan

# --parallel uses all available CPU cores for a faster build
cmake --build $BuildDir --parallel 

if ($LASTEXITCODE -eq 0) {
    Write-Host "[+] Build Successful!" -ForegroundColor Green
} else {
    Write-Host "[!] Build Failed." -ForegroundColor Red
    exit 1
}