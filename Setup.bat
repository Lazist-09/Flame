@echo off
setlocal

set PREMAKE_DIR=vendor\bin\premake
set PREMAKE_EXE=%PREMAKE_DIR%\premake5.exe
set PREMAKE_ZIP=premake.zip
set PREMAKE_VERSION=5.0.0-beta2
set DOWNLOAD_URL=https://github.com/premake/premake-core/releases/download/v%PREMAKE_VERSION%/premake-%PREMAKE_VERSION%-windows.zip

echo ==========================================
echo  Flame Project Setup
echo ==========================================

:: 检查 premake 是否已存在
if exist "%PREMAKE_EXE%" (
    echo [OK] Premake5 found.
    goto Generate
)

:: 不存在则下载
echo [INFO] Premake5 not found. Downloading...
if not exist "%PREMAKE_DIR%" mkdir "%PREMAKE_DIR%"

echo [INFO] Downloading from GitHub...
powershell -Command "Invoke-WebRequest -Uri '%DOWNLOAD_URL%' -OutFile '%PREMAKE_ZIP%'" -ErrorAction Stop
if errorlevel 1 (
    echo [ERROR] Download failed. Check your network or download manually.
    pause
    exit /b 1
)

:: 解压
echo [INFO] Extracting...
powershell -Command "Expand-Archive -Path '%PREMAKE_ZIP%' -DestinationPath '%PREMAKE_DIR%' -Force"
del "%PREMAKE_ZIP%"

:: 验证
if not exist "%PREMAKE_EXE%" (
    echo [ERROR] Extraction failed.
    pause
    exit /b 1
)
echo [OK] Premake5 installed.

:Generate
echo.
echo [INFO] Generating Visual Studio 2026 project files...
call "%PREMAKE_EXE%" vs2026

if errorlevel 1 (
    echo [ERROR] Premake generation failed.
    pause
    exit /b 1
)

echo [OK] Done! You can now open the .sln file.
echo.
pause