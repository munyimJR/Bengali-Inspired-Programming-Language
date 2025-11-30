@echo off
REM This version serves frontend with http-server for better development

SETLOCAL

echo Starting with local web server...
echo.

REM Start backend
cd backend
IF NOT EXIST node_modules call npm install
start "Backend [3001]" cmd /k "npm start"
cd ..

REM Wait for backend
timeout /t 3 /nobreak >nul

REM Start frontend server
cd frontend
start "Frontend [8080]" cmd /k "npx http-server -p 8080 -c-1 -o"
cd ..

echo.
echo Backend: http://localhost:3001
echo Frontend: http://localhost:8080
echo.
pause

ENDLOCAL