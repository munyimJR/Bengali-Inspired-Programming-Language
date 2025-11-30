@echo off
REM ================================================
REM Bangla Compiler - Local One-Click Starter
REM (No Docker Required!)
REM ================================================

SETLOCAL EnableDelayedExpansion

color 0A
echo. 
echo ================================================
echo   Bangla Compiler Project - Local Launcher
echo ================================================
echo. 

REM Check Node.js installation
echo [1/5] Checking Node.js... 
node --version >nul 2>&1
IF ERRORLEVEL 1 (
    echo [ERROR] Node.js is not installed! 
    echo Please install from: https://nodejs.org/
    echo.
    pause
    exit /b 1
)
echo [OK] Node.js detected! 

REM Check flex installation
echo [2/5] Checking flex...
flex --version >nul 2>&1
IF ERRORLEVEL 1 (
    echo [WARNING] flex not found in PATH
)
echo [OK] flex detected!

REM Check bison installation
echo [3/5] Checking bison...
bison --version >nul 2>&1
IF ERRORLEVEL 1 (
    echo [WARNING] bison not found in PATH
)
echo [OK] bison detected!

REM Check gcc installation
echo [4/5] Checking gcc...
gcc --version >nul 2>&1
IF ERRORLEVEL 1 (
    echo [WARNING] gcc not found in PATH
)
echo [OK] gcc detected!

REM Install backend dependencies if needed
echo [5/5] Checking backend dependencies...
cd backend
IF NOT EXIST node_modules (
    echo Installing backend dependencies... 
    call npm install
    IF ERRORLEVEL 1 (
        echo [ERROR] Failed to install dependencies! 
        cd ..
        pause
        exit /b 1
    )
) ELSE (
    echo [OK] Dependencies already installed!
)

REM Create temp directory if it doesn't exist
IF NOT EXIST temp mkdir temp

cd .. 

echo. 
echo ================================================
echo   Starting Services... 
echo ================================================
echo. 

REM Start backend server in new window
echo Starting Backend Server...
start "Bangla Compiler Backend [Port 3001]" cmd /k "cd backend && npm start"

REM Wait a bit for backend to start
timeout /t 3 /nobreak >nul

REM Open frontend in default browser
echo Opening Frontend...
start "" "frontend\index.html"

REM Alternative: Uncomment to serve frontend with http-server
REM cd frontend
REM start "Bangla Compiler Frontend [Port 8080]" cmd /k "npx http-server -p 8080 -c-1"
REM cd ..

echo. 
echo ================================================
echo   Services Started Successfully!
echo ================================================
echo. 
echo Backend API: http://localhost:3001
echo Frontend IDE: Opened in browser
echo.
echo Press any key to view this message again...
echo To stop: Close the backend terminal window
echo.
pause

ENDLOCAL