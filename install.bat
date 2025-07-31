@echo off
REM Sales & Expense Management System - Windows Installation Script
REM نظام إدارة المبيعات والمصروفات - سكريبت التثبيت لويندوز

setlocal enabledelayedexpansion

REM Colors (if supported)
set "RED=[31m"
set "GREEN=[32m"
set "YELLOW=[33m"
set "BLUE=[34m"
set "NC=[0m"

REM Header
echo ================================
echo Sales ^& Expense Management System
echo نظام إدارة المبيعات والمصروفات
echo Windows Installation Script
echo ================================
echo.

REM Check if main.cpp exists
if not exist "main.cpp" (
    echo [ERROR] main.cpp not found. Please run this script from the project directory.
    pause
    exit /b 1
)

REM Parse command line arguments
set INSTALL_DEPS=false
set FORCE_DIRECT=false
set SHOW_HELP=false

:parse_args
if "%~1"=="" goto :check_args
if "%~1"=="--install-deps" set INSTALL_DEPS=true
if "%~1"=="--direct" set FORCE_DIRECT=true
if "%~1"=="--help" set SHOW_HELP=true
if "%~1"=="-h" set SHOW_HELP=true
shift
goto :parse_args

:check_args
if "%SHOW_HELP%"=="true" (
    echo Usage: %0 [options]
    echo Options:
    echo   --install-deps  Show dependency installation instructions
    echo   --direct        Use direct compilation instead of CMake
    echo   --help, -h      Show this help message
    pause
    exit /b 0
)

REM Show dependency installation instructions
if "%INSTALL_DEPS%"=="true" (
    call :show_dependency_instructions
    pause
    exit /b 0
)

REM Check for compilers
call :check_prerequisites
if !errorlevel! neq 0 (
    echo [ERROR] Missing prerequisites. Run with --install-deps for installation instructions.
    pause
    exit /b 1
)

REM Build the project
if "%FORCE_DIRECT%"=="true" (
    call :build_direct
) else (
    call :build_project
)

if !errorlevel! neq 0 (
    echo [ERROR] Build failed.
    pause
    exit /b 1
)

REM Test the application
call :test_application

REM Setup UTF-8 encoding
call :setup_encoding

REM Show usage instructions
call :show_usage

echo [SUCCESS] Installation completed successfully!
pause
exit /b 0

REM ============================================================================
REM Functions
REM ============================================================================

:check_prerequisites
echo [INFO] Checking prerequisites...

REM Check for Visual Studio / MSVC
cl.exe /? >nul 2>&1
if !errorlevel! equ 0 (
    echo [OK] MSVC compiler found
    set COMPILER=msvc
    goto :check_cmake
)

REM Check for MinGW GCC
g++.exe --version >nul 2>&1
if !errorlevel! equ 0 (
    echo [OK] MinGW GCC found
    set COMPILER=gcc
    goto :check_cmake
)

REM Check for Clang
clang++.exe --version >nul 2>&1
if !errorlevel! equ 0 (
    echo [OK] Clang found
    set COMPILER=clang
    goto :check_cmake
)

echo [ERROR] No C++ compiler found (cl.exe, g++.exe, or clang++.exe)
exit /b 1

:check_cmake
REM Check for CMake
cmake.exe --version >nul 2>&1
if !errorlevel! equ 0 (
    echo [OK] CMake found
    set HAS_CMAKE=true
) else (
    echo [WARNING] CMake not found (optional but recommended)
    set HAS_CMAKE=false
)

REM Check for Make (if using MinGW)
if "%COMPILER%"=="gcc" (
    mingw32-make.exe --version >nul 2>&1
    if !errorlevel! equ 0 (
        echo [OK] MinGW Make found
    ) else (
        make.exe --version >nul 2>&1
        if !errorlevel! equ 0 (
            echo [OK] Make found
        ) else (
            echo [WARNING] Make not found
        )
    )
)

exit /b 0

:build_direct
echo [INFO] Building with direct compilation...

if "%COMPILER%"=="msvc" (
    echo [INFO] Using MSVC compiler...
    cl.exe /EHsc /std:c++11 /O2 main.cpp /Fe:sales_system.exe
) else if "%COMPILER%"=="gcc" (
    echo [INFO] Using MinGW GCC...
    g++.exe -std=c++11 -Wall -Wextra -O2 -o sales_system.exe main.cpp
) else if "%COMPILER%"=="clang" (
    echo [INFO] Using Clang...
    clang++.exe -std=c++11 -Wall -Wextra -O2 -o sales_system.exe main.cpp
) else (
    echo [ERROR] No suitable compiler available
    exit /b 1
)

if !errorlevel! equ 0 (
    echo [OK] Build completed: sales_system.exe
) else (
    echo [ERROR] Build failed
    exit /b 1
)

exit /b 0

:build_cmake
echo [INFO] Building with CMake...

REM Create build directory
if not exist "build" mkdir build
cd build

REM Configure
cmake.exe ..
if !errorlevel! neq 0 (
    echo [ERROR] CMake configuration failed
    cd ..
    exit /b 1
)

REM Build
cmake.exe --build . --config Release
if !errorlevel! neq 0 (
    echo [ERROR] CMake build failed
    cd ..
    exit /b 1
)

REM Copy executable to project root for convenience
if exist "bin\sales_system.exe" (
    copy "bin\sales_system.exe" "..\sales_system.exe" >nul
    echo [OK] Build completed: sales_system.exe
) else if exist "Release\sales_system.exe" (
    copy "Release\sales_system.exe" "..\sales_system.exe" >nul
    echo [OK] Build completed: sales_system.exe
) else (
    echo [ERROR] Build failed - executable not found
    cd ..
    exit /b 1
)

cd ..
exit /b 0

:build_project
echo [INFO] Starting build process...

if "%HAS_CMAKE%"=="true" (
    call :build_cmake
    if !errorlevel! equ 0 (
        exit /b 0
    ) else (
        echo [WARNING] CMake build failed, trying direct compilation...
        call :build_direct
    )
) else (
    call :build_direct
)

exit /b 0

:test_application
echo [INFO] Testing the application...

if exist "sales_system.exe" (
    REM Test run (exit immediately)
    echo 0 | sales_system.exe >nul 2>&1
    if !errorlevel! equ 0 (
        echo [OK] Application test passed
    ) else (
        echo [WARNING] Application test failed, but build appears successful
    )
) else (
    echo [ERROR] Executable not found
    exit /b 1
)

exit /b 0

:setup_encoding
echo [INFO] Setting up UTF-8 encoding for Arabic text support...

REM Set console to UTF-8
chcp 65001 >nul 2>&1
if !errorlevel! equ 0 (
    echo [OK] UTF-8 encoding configured for this session
    echo [INFO] To make this permanent, add 'chcp 65001' to your batch files
) else (
    echo [WARNING] Could not set UTF-8 encoding
)

exit /b 0

:show_dependency_instructions
echo [INFO] Dependency Installation Instructions for Windows:
echo.
echo 1. Install a C++ compiler:
echo.
echo    Option A: Visual Studio Community (Recommended)
echo    - Download from: https://visualstudio.microsoft.com/downloads/
echo    - Install with "Desktop development with C++" workload
echo    - Includes MSVC compiler and MSBuild
echo.
echo    Option B: MinGW-w64
echo    - Download from: https://www.mingw-w64.org/downloads/
echo    - Or install via MSYS2: https://www.msys2.org/
echo    - Add to PATH: C:\mingw64\bin
echo.
echo    Option C: LLVM/Clang
echo    - Download from: https://llvm.org/builds/
echo    - Add to PATH during installation
echo.
echo 2. Install CMake (Optional but recommended):
echo    - Download from: https://cmake.org/download/
echo    - Choose "Windows x64 Installer"
echo    - Add CMake to PATH during installation
echo.
echo 3. Verify installation:
echo    - Open Command Prompt or PowerShell
echo    - Run: cl /? (for MSVC) or g++ --version (for MinGW)
echo    - Run: cmake --version (if installed)
echo.
echo 4. For Arabic text support:
echo    - Use Windows Terminal (recommended)
echo    - Or PowerShell with UTF-8 support
echo    - Install a font that supports Arabic (e.g., Cascadia Code)
echo.
exit /b 0

:show_usage
echo.
echo [INFO] Installation completed! Usage instructions:
echo.
echo To run the application:
echo   sales_system.exe
echo.
echo To rebuild the project:
echo   # Using CMake (recommended):
echo   mkdir build ^&^& cd build ^&^& cmake .. ^&^& cmake --build .
echo.
echo   # Using direct compilation (MSVC):
echo   cl /EHsc /std:c++11 main.cpp /Fe:sales_system.exe
echo.
echo   # Using direct compilation (MinGW):
echo   g++ -std=c++11 -Wall -Wextra -O2 -o sales_system.exe main.cpp
echo.
echo For Arabic text support:
echo   - Use Windows Terminal or PowerShell
echo   - Run: chcp 65001 (to set UTF-8 encoding)
echo   - Use a font that supports Arabic characters
echo.
echo Documentation: README.md
echo Requirements: requirements.txt
echo.
exit /b 0