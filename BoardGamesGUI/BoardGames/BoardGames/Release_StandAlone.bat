@echo off
set RELEASE_DIR=C:\Users\anton\Desktop\BoardGames\cmake-build-release
set OUTPUT_DIR=C:\Users\anton\Desktop\BoardGames\Release
set MINGW_DIR=C:\msys64\mingw64\bin

:: Create Release directory
mkdir "%OUTPUT_DIR%"

:: Copy main executable
copy "%RELEASE_DIR%\BoardGames.exe" "%OUTPUT_DIR%"

:: Copy required MinGW runtime DLLs
copy "%MINGW_DIR%\libgcc_s_seh-1.dll" "%OUTPUT_DIR%"
copy "%MINGW_DIR%\libstdc++-6.dll" "%OUTPUT_DIR%"
copy "%MINGW_DIR%\libwinpthread-1.dll" "%OUTPUT_DIR%"

:: Copy Assets folder if it exists
if exist "%RELEASE_DIR%\Assets" (
    mkdir "%OUTPUT_DIR%\Assets"
    xcopy /E /I "%RELEASE_DIR%\Assets" "%OUTPUT_DIR%\Assets"
)

echo Release package created in %OUTPUT_DIR%
pause