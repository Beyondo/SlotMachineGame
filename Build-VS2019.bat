@echo off
:build
cls
Vendor\premake5.exe vs2019
pause
goto build