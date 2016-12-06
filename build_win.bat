echo off & color 0A

set WORK_DIR=%cd%
set MODE="Release"
set BUILD_PATH="build\build_vs2015"
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64

if not exist %BUILD_PATH% md %BUILD_PATH%
cd %BUILD_PATH%
cmake ../.. -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=%MODE% -DCMAKE_INSTALL_PREFIX=%INSTALL_PATH%
nmake /f Makefile

cd %WORK_DIR%
