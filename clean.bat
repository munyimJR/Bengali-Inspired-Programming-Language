@echo off
echo Cleaning temporary files...
echo.

REM Clean backend temp directory
IF EXIST backend\temp (
    echo Cleaning backend\temp...
    rd /s /q backend\temp
    mkdir backend\temp
)

REM Clean node_modules (optional - uncomment if needed)
REM IF EXIST backend\node_modules (
REM     echo Cleaning node_modules...
REM     rd /s /q backend\node_modules
REM )

echo.
echo Cleanup complete!
pause