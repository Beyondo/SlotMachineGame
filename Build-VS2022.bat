@echo off
:build
cls
Vendor\premake5.exe vs2022
pause
goto build