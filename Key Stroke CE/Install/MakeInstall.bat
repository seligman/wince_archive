@echo off

set CabWizPath=C:\Windows CE Tools\wce300\MS Pocket PC\support\ActiveSync\windows ce application installation\cabwiz
set OutputPath=C:\Temp\Output
set CpuTypes=MIPS_PPC SH3_PPC ARM_PPC SH3_CE MIPS_CE

rem Cab Wiz
"%CabWizPath%\cabwiz" KeyStrokeCE.inf /dest "%OutputPath%" /err error.log /cpu %CpuTypes%

rem EZ Setup
rem "%CabWizPath%\ezsetup" -i KeyStrokeCE.ini -r readme.txt -e eula.txt -o InstallExecutable.exe
