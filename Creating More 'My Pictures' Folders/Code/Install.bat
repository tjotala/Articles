@echo off
cd ReleaseMinDependency
rundll32.exe setupapi.dll,InstallHinfSection DefaultInstall 132 .\MyPicSw.inf
cd ..
