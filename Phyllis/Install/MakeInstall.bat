@echo off

set CabWizPath=C:\Windows CE Tools\wce300\MS Pocket PC\support\ActiveSync\windows ce application installation\cabwiz
set OutputPath=C:\Temp
set OrigDir=%CD%

echo ---- Cab Wiz
pause
"%CabWizPath%\cabwiz" Phyllis.inf /dest "%OutputPath%" /err error.log /cpu MIPS_PPC SH3_PPC ARM_PPC

echo ---- EZ Setup
pause
cd %OutputPath%
copy /y "%OrigDir%\Phyllis.ini"
copy /y "%OrigDir%\readme.txt"
copy /y "%OrigDir%\eula.txt"
"%CabWizPath%\ezsetup" -i Phyllis.ini -r readme.txt -e eula.txt -o InstallExecutable.exe

pause
