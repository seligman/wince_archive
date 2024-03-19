@echo off

set CabWizPath=C:\Windows CE Tools\wce300\MS Pocket PC\support\ActiveSync\windows ce application installation\cabwiz
rem set OutputPath=C:\Scott\My Projects\PuzzleOfPipes\Install\Output
set OutputPath=C:\Temp\Output

rem Cab Wiz
rem "%CabWizPath%\cabwiz" PuzzleOfPipes.inf /dest "%OutputPath%" /err error.log /cpu MIPS_PPC SH3_PPC ARM_PPC SH3_CE MIPS_CE

rem EZ Setup
"%CabWizPath%\ezsetup" -i PuzzleOfPipes.ini -r readme.txt -e eula.txt -o InstallExecutable.exe
