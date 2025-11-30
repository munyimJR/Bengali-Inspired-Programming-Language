@echo off
REM Run this once to set up your project

echo ================================================
echo   Bangla Compiler - Setup Script
echo ================================================
echo. 

REM Check prerequisites
echo Checking prerequisites...
echo.

node --version >nul 2>&1
IF ERRORLEVEL 1 (
    echo [X] Node.js NOT FOUND
    echo     Install from: https://nodejs.org/
    set MISSING=1
) ELSE (
    echo [OK] Node.js installed
)

flex --version >nul 2>&1
IF ERRORLEVEL 1 (
    echo [X] flex NOT FOUND
    set MISSING=1
) ELSE (
    echo [OK] flex installed
)

bison --version >nul 2>&1
IF ERRORLEVEL 1 (
    echo [X] bison NOT FOUND
    set MISSING=1
) ELSE (
    echo [OK] bison installed
)

gcc --version >nul 2>&1
IF ERRORLEVEL 1 (
    echo [X] gcc NOT FOUND
    set MISSING=1
) ELSE (
    echo [OK] gcc installed
)

IF DEFINED MISSING (
    echo. 
    echo [ERROR] Missing prerequisites! 
    echo Please install the missing components. 
    pause
    exit /b 1
)

echo.
echo All prerequisites installed!
echo. 

REM Install backend dependencies
echo Installing backend dependencies... 
cd backend
call npm install
cd ..

echo.
echo ================================================
echo   Setup Complete!
echo ================================================
echo.
echo You can now run: start.bat
pause