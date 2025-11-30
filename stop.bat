@echo off
echo Stopping Bangla Compiler services...
echo. 

REM Kill Node.js processes running on port 3001
for /f "tokens=5" %%a in ('netstat -aon ^| find ":3001" ^| find "LISTENING"') do (
    echo Stopping backend server (PID: %%a)
    taskkill /F /PID %%a >nul 2>&1
)

echo.
echo All services stopped! 
pause