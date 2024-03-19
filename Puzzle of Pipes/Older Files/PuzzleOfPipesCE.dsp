# Microsoft Developer Studio Project File - Name="PuzzleOfPipesCE" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (WCE x86) Application" 0x8301
# TARGTYPE "Win32 (WCE ARM) Application" 0x8501
# TARGTYPE "Win32 (WCE PPC) Application" 0x8401
# TARGTYPE "Win32 (WCE x86em) Application" 0x7f01
# TARGTYPE "Win32 (WCE SH3) Application" 0x8101
# TARGTYPE "Win32 (WCE SH4) Application" 0x8601
# TARGTYPE "Win32 (WCE MIPS) Application" 0x8201
# TARGTYPE "Win32 (WCE MIPSFP) Application" 0x8701

CFG=PuzzleOfPipesCE - Win32 (WCE MIPS) Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PuzzleOfPipesCE.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PuzzleOfPipesCE.mak" CFG="PuzzleOfPipesCE - Win32 (WCE MIPS) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PuzzleOfPipesCE - Win32 (WCE MIPS) Release" (based on "Win32 (WCE MIPS) Application")
!MESSAGE "PuzzleOfPipesCE - Win32 (WCE MIPS) Debug" (based on "Win32 (WCE MIPS) Application")
!MESSAGE "PuzzleOfPipesCE - Win32 (WCE SH4) Release" (based on "Win32 (WCE SH4) Application")
!MESSAGE "PuzzleOfPipesCE - Win32 (WCE SH4) Debug" (based on "Win32 (WCE SH4) Application")
!MESSAGE "PuzzleOfPipesCE - Win32 (WCE SH3) Release" (based on "Win32 (WCE SH3) Application")
!MESSAGE "PuzzleOfPipesCE - Win32 (WCE SH3) Debug" (based on "Win32 (WCE SH3) Application")
!MESSAGE "PuzzleOfPipesCE - Win32 (WCE ARM) Release" (based on "Win32 (WCE ARM) Application")
!MESSAGE "PuzzleOfPipesCE - Win32 (WCE ARM) Debug" (based on "Win32 (WCE ARM) Application")
!MESSAGE "PuzzleOfPipesCE - Win32 (WCE MIPSFP) Release" (based on "Win32 (WCE MIPSFP) Application")
!MESSAGE "PuzzleOfPipesCE - Win32 (WCE MIPSFP) Debug" (based on "Win32 (WCE MIPSFP) Application")
!MESSAGE "PuzzleOfPipesCE - Win32 (WCE x86) Release" (based on "Win32 (WCE x86) Application")
!MESSAGE "PuzzleOfPipesCE - Win32 (WCE x86) Debug" (based on "Win32 (WCE x86) Application")
!MESSAGE "PuzzleOfPipesCE - Win32 (WCE x86em) Release" (based on "Win32 (WCE x86em) Application")
!MESSAGE "PuzzleOfPipesCE - Win32 (WCE x86em) Debug" (based on "Win32 (WCE x86em) Application")
!MESSAGE "PuzzleOfPipesCE - Win32 (WCE PPC) Release" (based on "Win32 (WCE PPC) Application")
!MESSAGE "PuzzleOfPipesCE - Win32 (WCE PPC) Debug" (based on "Win32 (WCE PPC) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath "Palm-size PC 2.01"
# PROP WCE_FormatVersion "6.0"

!IF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE MIPS) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WMIPSRel"
# PROP BASE Intermediate_Dir "WMIPSRel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WMIPSRel"
# PROP Intermediate_Dir "WMIPSRel"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=clmips.exe
# ADD BASE CPP /nologo /M$(CECrt) /W3 /O2 /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "MIPS" /D "_MIPS_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /YX /QMRWCE /c
# ADD CPP /nologo /M$(CECrt) /W4 /WX /O2 /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "MIPS" /D "_MIPS_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /YX /QMRWCE /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /r /d "MIPS" /d "_MIPS_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG"
# ADD RSC /l 0x409 /r /d "MIPS" /d "_MIPS_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG"
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 commctrl.lib coredll.lib /nologo /machine:MIPS /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 commctrl.lib coredll.lib aygshell.lib /nologo /machine:MIPS /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE MIPS) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WMIPSDbg"
# PROP BASE Intermediate_Dir "WMIPSDbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WMIPSDbg"
# PROP Intermediate_Dir "WMIPSDbg"
# PROP Target_Dir ""
CPP=clmips.exe
# ADD BASE CPP /nologo /M$(CECrtDebug) /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "MIPS" /D "_MIPS_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /YX /QMRWCE /c
# ADD CPP /nologo /M$(CECrtDebug) /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "MIPS" /D "_MIPS_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /YX /QMRWCE /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /r /d "MIPS" /d "_MIPS_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG"
# ADD RSC /l 0x409 /r /d "MIPS" /d "_MIPS_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG"
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 commctrl.lib coredll.lib /nologo /debug /machine:MIPS /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 commctrl.lib coredll.lib /nologo /debug /machine:MIPS /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE SH4) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WCESH4Rel"
# PROP BASE Intermediate_Dir "WCESH4Rel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WCESH4Rel"
# PROP Intermediate_Dir "WCESH4Rel"
# PROP Target_Dir ""
LINK32=link.exe
# ADD BASE LINK32 commctrl.lib coredll.lib nologo machine:SH4 nodefaultlib:"$(CENoDefaultLib)" subsystem:$(CESubsystem) STACK:65536,4096 machine:IX86
# ADD LINK32 commctrl.lib coredll.lib nologo machine:SH4 nodefaultlib:"$(CENoDefaultLib)" subsystem:$(CESubsystem) STACK:65536,4096 machine:IX86
BSC32=bscmake.exe
# ADD BASE BSC32 nologo
# ADD BSC32 nologo
MTL=midl.exe
# ADD BASE MTL nologo D "NDEBUG" mktyplib203 o "NUL" win32
# ADD MTL nologo D "NDEBUG" mktyplib203 o "NUL" win32
RSC=rc.exe
# ADD BASE RSC l 0x409 l 0x409 r d "SHx" d "SH4" d "_SH4_" d UNDER_CE=$(CEVersion) d _WIN32_WCE=$(CEVersion) d "$(CEConfigName)" d "UNICODE" d "NDEBUG"
# ADD RSC l 0x409 l 0x409 r d "SHx" d "SH4" d "_SH4_" d UNDER_CE=$(CEVersion) d _WIN32_WCE=$(CEVersion) d "$(CEConfigName)" d "UNICODE" d "NDEBUG"
CPP=shcl.exe
# ADD BASE CPP nologo Qsh4 MC W3 GX- O2 D _WIN32_WCE=$(CEVersion) D "$(CEConfigName)" D "NDEBUG" D "SHx" D "SH4" D "_SH4_" D UNDER_CE=$(CEVersion) D "UNICODE" D "_MBCS" YX c
# ADD CPP nologo Qsh4 MC W3 GX- O2 D _WIN32_WCE=$(CEVersion) D "$(CEConfigName)" D "NDEBUG" D "SHx" D "SH4" D "_SH4_" D UNDER_CE=$(CEVersion) D "UNICODE" D "_MBCS" YX c

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE SH4) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WCESH4Dbg"
# PROP BASE Intermediate_Dir "WCESH4Dbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WCESH4Dbg"
# PROP Intermediate_Dir "WCESH4Dbg"
# PROP Target_Dir ""
LINK32=link.exe
# ADD BASE LINK32 commctrl.lib coredll.lib nologo debug machine:SH4 nodefaultlib:"$(CENoDefaultLib)" subsystem:$(CESubsystem) STACK:65536,4096 machine:IX86
# ADD LINK32 commctrl.lib coredll.lib nologo debug machine:SH4 nodefaultlib:"$(CENoDefaultLib)" subsystem:$(CESubsystem) STACK:65536,4096 machine:IX86
BSC32=bscmake.exe
# ADD BASE BSC32 nologo
# ADD BSC32 nologo
MTL=midl.exe
# ADD BASE MTL nologo D "_DEBUG" mktyplib203 o "NUL" win32
# ADD MTL nologo D "_DEBUG" mktyplib203 o "NUL" win32
RSC=rc.exe
# ADD BASE RSC l 0x409 l 0x409 r d "SHx" d "SH4" d "_SH4_" d UNDER_CE=$(CEVersion) d _WIN32_WCE=$(CEVersion) d "$(CEConfigName)" d "UNICODE" d "DEBUG"
# ADD RSC l 0x409 l 0x409 r d "SHx" d "SH4" d "_SH4_" d UNDER_CE=$(CEVersion) d _WIN32_WCE=$(CEVersion) d "$(CEConfigName)" d "UNICODE" d "DEBUG"
CPP=shcl.exe
# ADD BASE CPP nologo Qsh4 MC W3 GX- Zi Od D _WIN32_WCE=$(CEVersion) D "$(CEConfigName)" D "DEBUG" D "SHx" D "SH4" D "_SH4_" D UNDER_CE=$(CEVersion) D "UNICODE" D "_MBCS" YX c
# ADD CPP nologo Qsh4 MC W3 GX- Zi Od D _WIN32_WCE=$(CEVersion) D "$(CEConfigName)" D "DEBUG" D "SHx" D "SH4" D "_SH4_" D UNDER_CE=$(CEVersion) D "UNICODE" D "_MBCS" YX c

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE SH3) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WCESH3Rel"
# PROP BASE Intermediate_Dir "WCESH3Rel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WCESH3Rel"
# PROP Intermediate_Dir "WCESH3Rel"
# PROP Target_Dir ""
LINK32=link.exe
# ADD BASE LINK32 commctrl.lib coredll.lib nologo machine:SH3 nodefaultlib:"$(CENoDefaultLib)" subsystem:$(CESubsystem) STACK:65536,4096 machine:IX86
# ADD LINK32 commctrl.lib coredll.lib nologo machine:SH3 nodefaultlib:"$(CENoDefaultLib)" subsystem:$(CESubsystem) STACK:65536,4096 machine:IX86
BSC32=bscmake.exe
# ADD BASE BSC32 nologo
# ADD BSC32 nologo
MTL=midl.exe
# ADD BASE MTL nologo D "NDEBUG" mktyplib203 o "NUL" win32
# ADD MTL nologo D "NDEBUG" mktyplib203 o "NUL" win32
RSC=rc.exe
# ADD BASE RSC l 0x409 l 0x409 r d "SHx" d "SH3" d "_SH3_" d UNDER_CE=$(CEVersion) d _WIN32_WCE=$(CEVersion) d "$(CEConfigName)" d "UNICODE" d "NDEBUG"
# ADD RSC l 0x409 l 0x409 r d "SHx" d "SH3" d "_SH3_" d UNDER_CE=$(CEVersion) d _WIN32_WCE=$(CEVersion) d "$(CEConfigName)" d "UNICODE" d "NDEBUG"
CPP=shcl.exe
# ADD BASE CPP nologo M$(CECrt) W3 GX- O2 D _WIN32_WCE=$(CEVersion) D "$(CEConfigName)" D "NDEBUG" D "SHx" D "SH3" D "_SH3_" D UNDER_CE=$(CEVersion) D "UNICODE" D "_MBCS" YX c
# ADD CPP nologo M$(CECrt) W3 GX- O2 D _WIN32_WCE=$(CEVersion) D "$(CEConfigName)" D "NDEBUG" D "SHx" D "SH3" D "_SH3_" D UNDER_CE=$(CEVersion) D "UNICODE" D "_MBCS" YX c

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE SH3) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WCESH3Dbg"
# PROP BASE Intermediate_Dir "WCESH3Dbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WCESH3Dbg"
# PROP Intermediate_Dir "WCESH3Dbg"
# PROP Target_Dir ""
LINK32=link.exe
# ADD BASE LINK32 commctrl.lib coredll.lib nologo debug machine:SH3 nodefaultlib:"$(CENoDefaultLib)" subsystem:$(CESubsystem) STACK:65536,4096 machine:IX86
# ADD LINK32 commctrl.lib coredll.lib nologo debug machine:SH3 nodefaultlib:"$(CENoDefaultLib)" subsystem:$(CESubsystem) STACK:65536,4096 machine:IX86
BSC32=bscmake.exe
# ADD BASE BSC32 nologo
# ADD BSC32 nologo
MTL=midl.exe
# ADD BASE MTL nologo D "_DEBUG" mktyplib203 o "NUL" win32
# ADD MTL nologo D "_DEBUG" mktyplib203 o "NUL" win32
RSC=rc.exe
# ADD BASE RSC l 0x409 l 0x409 r d "SHx" d "SH3" d "_SH3_" d UNDER_CE=$(CEVersion) d _WIN32_WCE=$(CEVersion) d "$(CEConfigName)" d "UNICODE" d "DEBUG"
# ADD RSC l 0x409 l 0x409 r d "SHx" d "SH3" d "_SH3_" d UNDER_CE=$(CEVersion) d _WIN32_WCE=$(CEVersion) d "$(CEConfigName)" d "UNICODE" d "DEBUG"
CPP=shcl.exe
# ADD BASE CPP nologo M$(CECrtDebug) W3 GX- Zi Od D _WIN32_WCE=$(CEVersion) D "$(CEConfigName)" D "DEBUG" D "SHx" D "SH3" D "_SH3_" D UNDER_CE=$(CEVersion) D "UNICODE" D "_MBCS" YX c
# ADD CPP nologo M$(CECrtDebug) W3 GX- Zi Od D _WIN32_WCE=$(CEVersion) D "$(CEConfigName)" D "DEBUG" D "SHx" D "SH3" D "_SH3_" D UNDER_CE=$(CEVersion) D "UNICODE" D "_MBCS" YX c

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE ARM) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WCEARMRel"
# PROP BASE Intermediate_Dir "WCEARMRel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WCEARMRel"
# PROP Intermediate_Dir "WCEARMRel"
# PROP Target_Dir ""
LINK32=link.exe
# ADD BASE LINK32 coredll.lib commctrl.lib nologo machine:ARM nodefaultlib:"$(CENoDefaultLib)" subsystem:$(CESubsystem) STACK:65536,4096 machine:IX86
# ADD LINK32 coredll.lib commctrl.lib nologo machine:ARM nodefaultlib:"$(CENoDefaultLib)" subsystem:$(CESubsystem) STACK:65536,4096 machine:IX86
BSC32=bscmake.exe
# ADD BASE BSC32 nologo
# ADD BSC32 nologo
MTL=midl.exe
# ADD BASE MTL nologo D "NDEBUG" mktyplib203 o "NUL" win32
# ADD MTL nologo D "NDEBUG" mktyplib203 o "NUL" win32
RSC=rc.exe
# ADD BASE RSC l 0x409 l 0x409 r d "ARM" d "_ARM_" d UNDER_CE=$(CEVersion) d _WIN32_WCE=$(CEVersion) d "$(CEConfigName)" d "UNICODE" d "NDEBUG"
# ADD RSC l 0x409 l 0x409 r d "ARM" d "_ARM_" d UNDER_CE=$(CEVersion) d _WIN32_WCE=$(CEVersion) d "$(CEConfigName)" d "UNICODE" d "NDEBUG"
CPP=clarm.exe
# ADD BASE CPP nologo MC W3 GX- O2 D _WIN32_WCE=$(CEVersion) D "$(CEConfigName)" D "NDEBUG" D "ARM" D "_ARM_" D UNDER_CE=$(CEVersion) D "UNICODE" D "_MBCS" YX c
# ADD CPP nologo MC W3 GX- O2 D _WIN32_WCE=$(CEVersion) D "$(CEConfigName)" D "NDEBUG" D "ARM" D "_ARM_" D UNDER_CE=$(CEVersion) D "UNICODE" D "_MBCS" YX c

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE ARM) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WCEARMDbg"
# PROP BASE Intermediate_Dir "WCEARMDbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WCEARMDbg"
# PROP Intermediate_Dir "WCEARMDbg"
# PROP Target_Dir ""
LINK32=link.exe
# ADD BASE LINK32 coredll.lib commctrl.lib nologo debug machine:ARM nodefaultlib:"$(CENoDefaultLib)" subsystem:$(CESubsystem) STACK:65536,4096 machine:IX86
# ADD LINK32 coredll.lib commctrl.lib nologo debug machine:ARM nodefaultlib:"$(CENoDefaultLib)" subsystem:$(CESubsystem) STACK:65536,4096 machine:IX86
BSC32=bscmake.exe
# ADD BASE BSC32 nologo
# ADD BSC32 nologo
MTL=midl.exe
# ADD BASE MTL nologo D "_DEBUG" mktyplib203 o "NUL" win32
# ADD MTL nologo D "_DEBUG" mktyplib203 o "NUL" win32
RSC=rc.exe
# ADD BASE RSC l 0x409 l 0x409 r d "ARM" d "_ARM_" d UNDER_CE=$(CEVersion) d _WIN32_WCE=$(CEVersion) d "$(CEConfigName)" d "UNICODE" d "DEBUG"
# ADD RSC l 0x409 l 0x409 r d "ARM" d "_ARM_" d UNDER_CE=$(CEVersion) d _WIN32_WCE=$(CEVersion) d "$(CEConfigName)" d "UNICODE" d "DEBUG"
CPP=clarm.exe
# ADD BASE CPP nologo MC W3 GX- Zi Od D _WIN32_WCE=$(CEVersion) D "$(CEConfigName)" D "DEBUG" D "ARM" D "_ARM_" D UNDER_CE=$(CEVersion) D "UNICODE" D "_MBCS" YX c
# ADD CPP nologo MC W3 GX- Zi Od D _WIN32_WCE=$(CEVersion) D "$(CEConfigName)" D "DEBUG" D "ARM" D "_ARM_" D UNDER_CE=$(CEVersion) D "UNICODE" D "_MBCS" YX c

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE MIPSFP) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WMIPSFPRel"
# PROP BASE Intermediate_Dir "WMIPSFPRel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WMIPSFPRel"
# PROP Intermediate_Dir "WMIPSFPRel"
# PROP Target_Dir ""
LINK32=link.exe
# ADD BASE LINK32 commctrl.lib coredll.lib nologo machine:MIPS nodefaultlib:"$(CENoDefaultLib)" subsystem:$(CESubsystem) STACK:65536,4096 machine:IX86
# ADD LINK32 commctrl.lib coredll.lib nologo machine:MIPS nodefaultlib:"$(CENoDefaultLib)" subsystem:$(CESubsystem) STACK:65536,4096 machine:IX86
BSC32=bscmake.exe
# ADD BASE BSC32 nologo
# ADD BSC32 nologo
MTL=midl.exe
# ADD BASE MTL nologo D "NDEBUG" mktyplib203 o "NUL" win32
# ADD MTL nologo D "NDEBUG" mktyplib203 o "NUL" win32
RSC=rc.exe
# ADD BASE RSC l 0x409 l 0x409 r d "MIPS" d "_MIPS_" d UNDER_CE=$(CEVersion) d _WIN32_WCE=$(CEVersion) d "$(CEConfigName)" d "UNICODE" d "NDEBUG"
# ADD RSC l 0x409 l 0x409 r d "MIPS" d "_MIPS_" d UNDER_CE=$(CEVersion) d _WIN32_WCE=$(CEVersion) d "$(CEConfigName)" d "UNICODE" d "NDEBUG"
CPP=clmips.exe
# ADD BASE CPP QMFWCE nologo QMFWCE MC W3 GX- O2 D _WIN32_WCE=$(CEVersion) D "$(CEConfigName)" D "NDEBUG" D "MIPS" D "_MIPS_" D UNDER_CE=$(CEVersion) D "UNICODE" D "_MBCS" YX c
# ADD CPP QMFWCE nologo QMFWCE MC W3 GX- O2 D _WIN32_WCE=$(CEVersion) D "$(CEConfigName)" D "NDEBUG" D "MIPS" D "_MIPS_" D UNDER_CE=$(CEVersion) D "UNICODE" D "_MBCS" YX c

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE MIPSFP) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WMIPSFPDbg"
# PROP BASE Intermediate_Dir "WMIPSFPDbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WMIPSFPDbg"
# PROP Intermediate_Dir "WMIPSFPDbg"
# PROP Target_Dir ""
LINK32=link.exe
# ADD BASE LINK32 commctrl.lib coredll.lib nologo debug machine:MIPS nodefaultlib:"$(CENoDefaultLib)" subsystem:$(CESubsystem) STACK:65536,4096 machine:IX86
# ADD LINK32 commctrl.lib coredll.lib nologo debug machine:MIPS nodefaultlib:"$(CENoDefaultLib)" subsystem:$(CESubsystem) STACK:65536,4096 machine:IX86
BSC32=bscmake.exe
# ADD BASE BSC32 nologo
# ADD BSC32 nologo
MTL=midl.exe
# ADD BASE MTL nologo D "_DEBUG" mktyplib203 o "NUL" win32
# ADD MTL nologo D "_DEBUG" mktyplib203 o "NUL" win32
RSC=rc.exe
# ADD BASE RSC l 0x409 l 0x409 r d "MIPS" d "_MIPS_" d UNDER_CE=$(CEVersion) d _WIN32_WCE=$(CEVersion) d "$(CEConfigName)" d "UNICODE" d "DEBUG"
# ADD RSC l 0x409 l 0x409 r d "MIPS" d "_MIPS_" d UNDER_CE=$(CEVersion) d _WIN32_WCE=$(CEVersion) d "$(CEConfigName)" d "UNICODE" d "DEBUG"
CPP=clmips.exe
# ADD BASE CPP QMFWCE nologo QMFWCE MC W3 GX- Zi Od D _WIN32_WCE=$(CEVersion) D "$(CEConfigName)" D "DEBUG" D "MIPS" D "_MIPS_" D UNDER_CE=$(CEVersion) D "UNICODE" D "_MBCS" YX c
# ADD CPP QMFWCE nologo QMFWCE MC W3 GX- Zi Od D _WIN32_WCE=$(CEVersion) D "$(CEConfigName)" D "DEBUG" D "MIPS" D "_MIPS_" D UNDER_CE=$(CEVersion) D "UNICODE" D "_MBCS" YX c

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE x86) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WCEX86Rel"
# PROP BASE Intermediate_Dir "WCEX86Rel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WCEX86Rel"
# PROP Intermediate_Dir "WCEX86Rel"
# PROP Target_Dir ""
LINK32=link.exe
# ADD BASE LINK32 $(CEx86Corelibc) commctrl.lib coredll.lib nologo machine:IX86 nodefaultlib:"$(CENoDefaultLib)" subsystem:$(CESubsystem) STACK:65536,4096 machine:IX86
# ADD LINK32 $(CEx86Corelibc) commctrl.lib coredll.lib nologo machine:IX86 nodefaultlib:"$(CENoDefaultLib)" subsystem:$(CESubsystem) STACK:65536,4096 machine:IX86
BSC32=bscmake.exe
# ADD BASE BSC32 nologo
# ADD BSC32 nologo
MTL=midl.exe
# ADD BASE MTL nologo D "NDEBUG" mktyplib203 o "NUL" win32
# ADD MTL nologo D "NDEBUG" mktyplib203 o "NUL" win32
RSC=rc.exe
# ADD BASE RSC l 0x409 l 0x409 r d "x86" d "_i386_" d "_x86_" d _WIN32_WCE=$(CEVersion) d "$(CEConfigName)" d UNDER_CE=$(CEVersion) d "UNICODE" d "NDEBUG"
# ADD RSC l 0x409 l 0x409 r d "x86" d "_i386_" d "_x86_" d _WIN32_WCE=$(CEVersion) d "$(CEConfigName)" d UNDER_CE=$(CEVersion) d "UNICODE" d "NDEBUG"
CPP=cl.exe
# ADD BASE CPP nologo ML W3 GX- O2 D "x86" D "_i386_" D "_x86_" D _WIN32_WCE=$(CEVersion) D "$(CEConfigName)" D UNDER_CE=$(CEVersion) D "UNICODE" D "NDEBUG" D "i_386_" D "_MBCS" Gs8192 GF c
# ADD CPP nologo ML W3 GX- O2 D "x86" D "_i386_" D "_x86_" D _WIN32_WCE=$(CEVersion) D "$(CEConfigName)" D UNDER_CE=$(CEVersion) D "UNICODE" D "NDEBUG" D "i_386_" D "_MBCS" Gs8192 GF c

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE x86) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WCEX86Dbg"
# PROP BASE Intermediate_Dir "WCEX86Dbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WCEX86Dbg"
# PROP Intermediate_Dir "WCEX86Dbg"
# PROP Target_Dir ""
LINK32=link.exe
# ADD BASE LINK32 $(CEx86Corelibc) commctrl.lib coredll.lib nologo debug machine:IX86 nodefaultlib:"$(CENoDefaultLib)" subsystem:$(CESubsystem) STACK:65536,4096 machine:IX86
# ADD LINK32 $(CEx86Corelibc) commctrl.lib coredll.lib nologo debug machine:IX86 nodefaultlib:"$(CENoDefaultLib)" subsystem:$(CESubsystem) STACK:65536,4096 machine:IX86
BSC32=bscmake.exe
# ADD BASE BSC32 nologo
# ADD BSC32 nologo
MTL=midl.exe
# ADD BASE MTL nologo D "_DEBUG" mktyplib203 o "NUL" win32
# ADD MTL nologo D "_DEBUG" mktyplib203 o "NUL" win32
RSC=rc.exe
# ADD BASE RSC l 0x409 l 0x409 r d "x86" d "_i386_" d "_x86_" d _WIN32_WCE=$(CEVersion) d "$(CEConfigName)" d UNDER_CE=$(CEVersion) d "UNICODE" d "DEBUG"
# ADD RSC l 0x409 l 0x409 r d "x86" d "_i386_" d "_x86_" d _WIN32_WCE=$(CEVersion) d "$(CEConfigName)" d UNDER_CE=$(CEVersion) d "UNICODE" d "DEBUG"
CPP=cl.exe
# ADD BASE CPP nologo MLd W3 GX- Zi Od D "x86" D "_i386_" D "_x86_" D _WIN32_WCE=$(CEVersion) D "$(CEConfigName)" D UNDER_CE=$(CEVersion) D "UNICODE" D "DEBUG" D "i_386_" D "_MBCS" Gs8192 GF c
# ADD CPP nologo MLd W3 GX- Zi Od D "x86" D "_i386_" D "_x86_" D _WIN32_WCE=$(CEVersion) D "$(CEConfigName)" D UNDER_CE=$(CEVersion) D "UNICODE" D "DEBUG" D "i_386_" D "_MBCS" Gs8192 GF c

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE x86em) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "x86emRel"
# PROP BASE Intermediate_Dir "x86emRel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "x86emRel"
# PROP Intermediate_Dir "x86emRel"
# PROP Target_Dir ""
LINK32=link.exe
# ADD BASE LINK32 $(CEx86Corelibc) commctrl.lib coredll.lib nologo stack:0x10000,0x1000 entry:"" subsystem:windows machine:I386 nodefaultlib:"$(CENoDefaultLib)" windowsce:emulation machine:IX86
# ADD LINK32 $(CEx86Corelibc) commctrl.lib coredll.lib nologo stack:0x10000,0x1000 entry:"" subsystem:windows machine:I386 nodefaultlib:"$(CENoDefaultLib)" windowsce:emulation machine:IX86
BSC32=bscmake.exe
# ADD BASE BSC32 nologo
# ADD BSC32 nologo
MTL=midl.exe
# ADD BASE MTL nologo D "NDEBUG" mktyplib203 o "NUL" win32
# ADD MTL nologo D "NDEBUG" mktyplib203 o "NUL" win32
RSC=rc.exe
# ADD BASE RSC l 0x409 l 0x409 d UNDER_CE=$(CEVersion) d "UNICODE" d "_UNICODE" d "WIN32" d "STRICT" d _WIN32_WCE=$(CEVersion) d "$(CEConfigName)" d "_WIN32_WCE_EMULATION" d "INTERNATIONAL" d "USA" d "INTLMSG_CODEPAGE" d "NDEBUG"
# ADD RSC l 0x409 l 0x409 d UNDER_CE=$(CEVersion) d "UNICODE" d "_UNICODE" d "WIN32" d "STRICT" d _WIN32_WCE=$(CEVersion) d "$(CEConfigName)" d "_WIN32_WCE_EMULATION" d "INTERNATIONAL" d "USA" d "INTLMSG_CODEPAGE" d "NDEBUG"
CPP=cl.exe
# ADD BASE CPP nologo ML W3 GX- O2 D UNDER_CE=$(CEVersion) D "UNICODE" D "_UNICODE" D "WIN32" D "STRICT" D _WIN32_WCE=$(CEVersion) D "$(CEConfigName)" D "_WIN32_WCE_EMULATION" D "INTERNATIONAL" D "USA" D "INTLMSG_CODEPAGE" D "NDEBUG" D "x86" D "i486" D "_x86_" D "_MBCS" YX c
# ADD CPP nologo ML W3 GX- O2 D UNDER_CE=$(CEVersion) D "UNICODE" D "_UNICODE" D "WIN32" D "STRICT" D _WIN32_WCE=$(CEVersion) D "$(CEConfigName)" D "_WIN32_WCE_EMULATION" D "INTERNATIONAL" D "USA" D "INTLMSG_CODEPAGE" D "NDEBUG" D "x86" D "i486" D "_x86_" D "_MBCS" YX c

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE x86em) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "x86emDbg"
# PROP BASE Intermediate_Dir "x86emDbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "x86emDbg"
# PROP Intermediate_Dir "x86emDbg"
# PROP Target_Dir ""
LINK32=link.exe
# ADD BASE LINK32 $(CEx86Corelibc) commctrl.lib coredll.lib nologo stack:0x10000,0x1000 entry:"" subsystem:windows debug machine:I386 nodefaultlib:"$(CENoDefaultLib)" windowsce:emulation machine:IX86
# ADD LINK32 $(CEx86Corelibc) commctrl.lib coredll.lib nologo stack:0x10000,0x1000 entry:"" subsystem:windows debug machine:I386 nodefaultlib:"$(CENoDefaultLib)" windowsce:emulation machine:IX86
BSC32=bscmake.exe
# ADD BASE BSC32 nologo
# ADD BSC32 nologo
MTL=midl.exe
# ADD BASE MTL nologo D "_DEBUG" mktyplib203 o "NUL" win32
# ADD MTL nologo D "_DEBUG" mktyplib203 o "NUL" win32
RSC=rc.exe
# ADD BASE RSC l 0x409 l 0x409 d UNDER_CE=$(CEVersion) d "UNICODE" d "_UNICODE" d "WIN32" d "STRICT" d _WIN32_WCE=$(CEVersion) d "$(CEConfigName)" d "_WIN32_WCE_EMULATION" d "INTERNATIONAL" d "USA" d "INTLMSG_CODEPAGE" d "_DEBUG" d "x86" d "i486" d "_x86_"
# ADD RSC l 0x409 l 0x409 d UNDER_CE=$(CEVersion) d "UNICODE" d "_UNICODE" d "WIN32" d "STRICT" d _WIN32_WCE=$(CEVersion) d "$(CEConfigName)" d "_WIN32_WCE_EMULATION" d "INTERNATIONAL" d "USA" d "INTLMSG_CODEPAGE" d "_DEBUG" d "x86" d "i486" d "_x86_"
CPP=cl.exe
# ADD BASE CPP nologo MLd W3 Gm GX- Zi Od D UNDER_CE=$(CEVersion) D "UNICODE" D "_UNICODE" D "WIN32" D "STRICT" D _WIN32_WCE=$(CEVersion) D "$(CEConfigName)" D "_WIN32_WCE_EMULATION" D "INTERNATIONAL" D "USA" D "INTLMSG_CODEPAGE" D "_DEBUG" D "x86" D "i486" D "_x86_" D "_MBCS" YX c
# ADD CPP nologo MLd W3 Gm GX- Zi Od D UNDER_CE=$(CEVersion) D "UNICODE" D "_UNICODE" D "WIN32" D "STRICT" D _WIN32_WCE=$(CEVersion) D "$(CEConfigName)" D "_WIN32_WCE_EMULATION" D "INTERNATIONAL" D "USA" D "INTLMSG_CODEPAGE" D "_DEBUG" D "x86" D "i486" D "_x86_" D "_MBCS" YX c

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE PPC) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WCEPPCRel"
# PROP BASE Intermediate_Dir "WCEPPCRel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WCEPPCRel"
# PROP Intermediate_Dir "WCEPPCRel"
# PROP Target_Dir ""
LINK32=link.exe
# ADD BASE LINK32 commctrl.lib coredll.lib nologo machine:PPC nodefaultlib:"$(CENoDefaultLib)" subsystem:$(CESubsystem) STACK:65536,4096 machine:IX86
# ADD LINK32 commctrl.lib coredll.lib nologo machine:PPC nodefaultlib:"$(CENoDefaultLib)" subsystem:$(CESubsystem) STACK:65536,4096 machine:IX86
BSC32=bscmake.exe
# ADD BASE BSC32 nologo
# ADD BSC32 nologo
MTL=midl.exe
# ADD BASE MTL nologo D "NDEBUG" mktyplib203 o "NUL" win32
# ADD MTL nologo D "NDEBUG" mktyplib203 o "NUL" win32
RSC=rc.exe
# ADD BASE RSC l 0x409 l 0x409 r d "ppc" d "_ppc_" d _WIN32_WCE=$(CEVersion) d "$(CEConfigName)" d UNDER_CE=$(CEVersion) d "UNICODE" d "NDEBUG"
# ADD RSC l 0x409 l 0x409 r d "ppc" d "_ppc_" d _WIN32_WCE=$(CEVersion) d "$(CEConfigName)" d UNDER_CE=$(CEVersion) d "UNICODE" d "NDEBUG"
CPP=clppc.exe
# ADD BASE CPP nologo M$(CECrt) W3 GX- O2 D _WIN32_WCE=$(CEVersion) D "$(CEConfigName)" D "NDEBUG" D "PPC" D "_PPC_" D UNDER_CE=$(CEVersion) D "UNICODE" D "_MBCS" YX c
# ADD CPP nologo M$(CECrt) W3 GX- O2 D _WIN32_WCE=$(CEVersion) D "$(CEConfigName)" D "NDEBUG" D "PPC" D "_PPC_" D UNDER_CE=$(CEVersion) D "UNICODE" D "_MBCS" YX c

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE PPC) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WCEPPCDbg"
# PROP BASE Intermediate_Dir "WCEPPCDbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WCEPPCDbg"
# PROP Intermediate_Dir "WCEPPCDbg"
# PROP Target_Dir ""
LINK32=link.exe
# ADD BASE LINK32 commctrl.lib coredll.lib nologo debug machine:PPC nodefaultlib:"$(CENoDefaultLib)" subsystem:$(CESubsystem) STACK:65536,4096 machine:IX86
# ADD LINK32 commctrl.lib coredll.lib nologo debug machine:PPC nodefaultlib:"$(CENoDefaultLib)" subsystem:$(CESubsystem) STACK:65536,4096 machine:IX86
BSC32=bscmake.exe
# ADD BASE BSC32 nologo
# ADD BSC32 nologo
MTL=midl.exe
# ADD BASE MTL nologo D "_DEBUG" mktyplib203 o "NUL" win32
# ADD MTL nologo D "_DEBUG" mktyplib203 o "NUL" win32
RSC=rc.exe
# ADD BASE RSC l 0x409 l 0x409 r d "ppc" d "_ppc_" d _WIN32_WCE=$(CEVersion) d "$(CEConfigName)" d UNDER_CE=$(CEVersion) d "UNICODE" d "DEBUG"
# ADD RSC l 0x409 l 0x409 r d "ppc" d "_ppc_" d _WIN32_WCE=$(CEVersion) d "$(CEConfigName)" d UNDER_CE=$(CEVersion) d "UNICODE" d "DEBUG"
CPP=clppc.exe
# ADD BASE CPP nologo M$(CECrtDebug) W3 GX- Zi Od D _WIN32_WCE=$(CEVersion) D "$(CEConfigName)" D "DEBUG" D "PPC" D "_PPC_" D UNDER_CE=$(CEVersion) D "UNICODE" D "_MBCS" YX c
# ADD CPP nologo M$(CECrtDebug) W3 GX- Zi Od D _WIN32_WCE=$(CEVersion) D "$(CEConfigName)" D "DEBUG" D "PPC" D "_PPC_" D UNDER_CE=$(CEVersion) D "UNICODE" D "_MBCS" YX c

!ENDIF 

# Begin Target

# Name "PuzzleOfPipesCE - Win32 (WCE MIPS) Release"
# Name "PuzzleOfPipesCE - Win32 (WCE MIPS) Debug"
# Name "PuzzleOfPipesCE - Win32 (WCE SH4) Release"
# Name "PuzzleOfPipesCE - Win32 (WCE SH4) Debug"
# Name "PuzzleOfPipesCE - Win32 (WCE SH3) Release"
# Name "PuzzleOfPipesCE - Win32 (WCE SH3) Debug"
# Name "PuzzleOfPipesCE - Win32 (WCE ARM) Release"
# Name "PuzzleOfPipesCE - Win32 (WCE ARM) Debug"
# Name "PuzzleOfPipesCE - Win32 (WCE MIPSFP) Release"
# Name "PuzzleOfPipesCE - Win32 (WCE MIPSFP) Debug"
# Name "PuzzleOfPipesCE - Win32 (WCE x86) Release"
# Name "PuzzleOfPipesCE - Win32 (WCE x86) Debug"
# Name "PuzzleOfPipesCE - Win32 (WCE x86em) Release"
# Name "PuzzleOfPipesCE - Win32 (WCE x86em) Debug"
# Name "PuzzleOfPipesCE - Win32 (WCE PPC) Release"
# Name "PuzzleOfPipesCE - Win32 (WCE PPC) Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Grid.cpp

!IF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE MIPS) Release"

DEP_CPP_GRID_=\
	".\Grid.h"\
	".\HighScore.h"\
	".\main.h"\
	".\Pipe.h"\
	".\Score.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE MIPS) Debug"

DEP_CPP_GRID_=\
	".\Grid.h"\
	".\main.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE SH4) Release"

DEP_CPP_GRID_=\
	".\Grid.h"\
	".\main.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE SH4) Debug"

DEP_CPP_GRID_=\
	".\Grid.h"\
	".\main.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE SH3) Release"

DEP_CPP_GRID_=\
	".\Grid.h"\
	".\main.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE SH3) Debug"

DEP_CPP_GRID_=\
	".\Grid.h"\
	".\main.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE ARM) Release"

DEP_CPP_GRID_=\
	".\Grid.h"\
	".\main.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE ARM) Debug"

DEP_CPP_GRID_=\
	".\Grid.h"\
	".\main.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE MIPSFP) Release"

DEP_CPP_GRID_=\
	".\Grid.h"\
	".\main.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE MIPSFP) Debug"

DEP_CPP_GRID_=\
	".\Grid.h"\
	".\main.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE x86) Release"

DEP_CPP_GRID_=\
	".\Grid.h"\
	".\main.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE x86) Debug"

DEP_CPP_GRID_=\
	".\Grid.h"\
	".\main.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE x86em) Release"

DEP_CPP_GRID_=\
	".\Grid.h"\
	".\main.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE x86em) Debug"

DEP_CPP_GRID_=\
	".\Grid.h"\
	".\main.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE PPC) Release"

DEP_CPP_GRID_=\
	".\Grid.h"\
	".\main.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE PPC) Debug"

DEP_CPP_GRID_=\
	".\Grid.h"\
	".\main.h"\
	".\Pipe.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\HighScore.cpp

!IF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE MIPS) Release"

DEP_CPP_HIGHS=\
	".\HighScore.h"\
	".\main.h"\
	
NODEP_CPP_HIGHS=\
	".\ygshell.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE MIPS) Debug"

DEP_CPP_HIGHS=\
	".\HighScore.h"\
	".\main.h"\
	
NODEP_CPP_HIGHS=\
	".\ygshell.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE SH4) Release"

DEP_CPP_HIGHS=\
	".\HighScore.h"\
	".\main.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE SH4) Debug"

DEP_CPP_HIGHS=\
	".\HighScore.h"\
	".\main.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE SH3) Release"

DEP_CPP_HIGHS=\
	".\HighScore.h"\
	".\main.h"\
	
NODEP_CPP_HIGHS=\
	".\ygshell.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE SH3) Debug"

DEP_CPP_HIGHS=\
	".\HighScore.h"\
	".\main.h"\
	
NODEP_CPP_HIGHS=\
	".\ygshell.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE ARM) Release"

DEP_CPP_HIGHS=\
	".\HighScore.h"\
	".\main.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE ARM) Debug"

DEP_CPP_HIGHS=\
	".\HighScore.h"\
	".\main.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE MIPSFP) Release"

DEP_CPP_HIGHS=\
	".\HighScore.h"\
	".\main.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE MIPSFP) Debug"

DEP_CPP_HIGHS=\
	".\HighScore.h"\
	".\main.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE x86) Release"

DEP_CPP_HIGHS=\
	".\HighScore.h"\
	".\main.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE x86) Debug"

DEP_CPP_HIGHS=\
	".\HighScore.h"\
	".\main.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE x86em) Release"

DEP_CPP_HIGHS=\
	".\HighScore.h"\
	".\main.h"\
	
NODEP_CPP_HIGHS=\
	".\ygshell.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE x86em) Debug"

DEP_CPP_HIGHS=\
	".\HighScore.h"\
	".\main.h"\
	
NODEP_CPP_HIGHS=\
	".\ygshell.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE PPC) Release"

DEP_CPP_HIGHS=\
	".\HighScore.h"\
	".\main.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE PPC) Debug"

DEP_CPP_HIGHS=\
	".\HighScore.h"\
	".\main.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\main.cpp

!IF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE MIPS) Release"

DEP_CPP_MAIN_=\
	".\Grid.h"\
	".\HighScore.h"\
	".\main.h"\
	".\MainWnd.h"\
	".\Pipe.h"\
	".\Score.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE MIPS) Debug"

DEP_CPP_MAIN_=\
	".\Grid.h"\
	".\main.h"\
	".\MainWnd.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE SH4) Release"

DEP_CPP_MAIN_=\
	".\Grid.h"\
	".\main.h"\
	".\MainWnd.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE SH4) Debug"

DEP_CPP_MAIN_=\
	".\Grid.h"\
	".\main.h"\
	".\MainWnd.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE SH3) Release"

DEP_CPP_MAIN_=\
	".\Grid.h"\
	".\main.h"\
	".\MainWnd.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE SH3) Debug"

DEP_CPP_MAIN_=\
	".\Grid.h"\
	".\main.h"\
	".\MainWnd.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE ARM) Release"

DEP_CPP_MAIN_=\
	".\Grid.h"\
	".\main.h"\
	".\MainWnd.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE ARM) Debug"

DEP_CPP_MAIN_=\
	".\Grid.h"\
	".\main.h"\
	".\MainWnd.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE MIPSFP) Release"

DEP_CPP_MAIN_=\
	".\Grid.h"\
	".\main.h"\
	".\MainWnd.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE MIPSFP) Debug"

DEP_CPP_MAIN_=\
	".\Grid.h"\
	".\main.h"\
	".\MainWnd.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE x86) Release"

DEP_CPP_MAIN_=\
	".\Grid.h"\
	".\main.h"\
	".\MainWnd.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE x86) Debug"

DEP_CPP_MAIN_=\
	".\Grid.h"\
	".\main.h"\
	".\MainWnd.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE x86em) Release"

DEP_CPP_MAIN_=\
	".\Grid.h"\
	".\main.h"\
	".\MainWnd.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE x86em) Debug"

DEP_CPP_MAIN_=\
	".\Grid.h"\
	".\main.h"\
	".\MainWnd.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE PPC) Release"

DEP_CPP_MAIN_=\
	".\Grid.h"\
	".\main.h"\
	".\MainWnd.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE PPC) Debug"

DEP_CPP_MAIN_=\
	".\Grid.h"\
	".\main.h"\
	".\MainWnd.h"\
	".\Pipe.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MainWnd.cpp

!IF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE MIPS) Release"

DEP_CPP_MAINW=\
	".\Grid.h"\
	".\HighScore.h"\
	".\main.h"\
	".\MainWnd.h"\
	".\Pipe.h"\
	".\Score.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE MIPS) Debug"

DEP_CPP_MAINW=\
	".\Grid.h"\
	".\main.h"\
	".\MainWnd.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE SH4) Release"

DEP_CPP_MAINW=\
	".\Grid.h"\
	".\main.h"\
	".\MainWnd.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE SH4) Debug"

DEP_CPP_MAINW=\
	".\Grid.h"\
	".\main.h"\
	".\MainWnd.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE SH3) Release"

DEP_CPP_MAINW=\
	".\Grid.h"\
	".\main.h"\
	".\MainWnd.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE SH3) Debug"

DEP_CPP_MAINW=\
	".\Grid.h"\
	".\main.h"\
	".\MainWnd.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE ARM) Release"

DEP_CPP_MAINW=\
	".\Grid.h"\
	".\main.h"\
	".\MainWnd.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE ARM) Debug"

DEP_CPP_MAINW=\
	".\Grid.h"\
	".\main.h"\
	".\MainWnd.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE MIPSFP) Release"

DEP_CPP_MAINW=\
	".\Grid.h"\
	".\main.h"\
	".\MainWnd.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE MIPSFP) Debug"

DEP_CPP_MAINW=\
	".\Grid.h"\
	".\main.h"\
	".\MainWnd.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE x86) Release"

DEP_CPP_MAINW=\
	".\Grid.h"\
	".\main.h"\
	".\MainWnd.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE x86) Debug"

DEP_CPP_MAINW=\
	".\Grid.h"\
	".\main.h"\
	".\MainWnd.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE x86em) Release"

DEP_CPP_MAINW=\
	".\Grid.h"\
	".\main.h"\
	".\MainWnd.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE x86em) Debug"

DEP_CPP_MAINW=\
	".\Grid.h"\
	".\main.h"\
	".\MainWnd.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE PPC) Release"

DEP_CPP_MAINW=\
	".\Grid.h"\
	".\main.h"\
	".\MainWnd.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE PPC) Debug"

DEP_CPP_MAINW=\
	".\Grid.h"\
	".\main.h"\
	".\MainWnd.h"\
	".\Pipe.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Pipe.cpp

!IF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE MIPS) Release"

DEP_CPP_PIPE_=\
	".\main.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE MIPS) Debug"

DEP_CPP_PIPE_=\
	".\main.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE SH4) Release"

DEP_CPP_PIPE_=\
	".\main.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE SH4) Debug"

DEP_CPP_PIPE_=\
	".\main.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE SH3) Release"

DEP_CPP_PIPE_=\
	".\main.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE SH3) Debug"

DEP_CPP_PIPE_=\
	".\main.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE ARM) Release"

DEP_CPP_PIPE_=\
	".\main.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE ARM) Debug"

DEP_CPP_PIPE_=\
	".\main.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE MIPSFP) Release"

DEP_CPP_PIPE_=\
	".\main.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE MIPSFP) Debug"

DEP_CPP_PIPE_=\
	".\main.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE x86) Release"

DEP_CPP_PIPE_=\
	".\main.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE x86) Debug"

DEP_CPP_PIPE_=\
	".\main.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE x86em) Release"

DEP_CPP_PIPE_=\
	".\main.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE x86em) Debug"

DEP_CPP_PIPE_=\
	".\main.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE PPC) Release"

DEP_CPP_PIPE_=\
	".\main.h"\
	".\Pipe.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE PPC) Debug"

DEP_CPP_PIPE_=\
	".\main.h"\
	".\Pipe.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\resource.rc

!IF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE MIPS) Release"

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE MIPS) Debug"

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE SH4) Release"

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE SH4) Debug"

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE SH3) Release"

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE SH3) Debug"

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE ARM) Release"

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE ARM) Debug"

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE MIPSFP) Release"

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE MIPSFP) Debug"

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE x86) Release"

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE x86) Debug"

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE x86em) Release"

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE x86em) Debug"

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE PPC) Release"

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE PPC) Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Score.cpp

!IF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE MIPS) Release"

DEP_CPP_SCORE=\
	".\HighScore.h"\
	".\main.h"\
	".\Score.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE MIPS) Debug"

DEP_CPP_SCORE=\
	".\main.h"\
	".\Score.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE SH4) Release"

DEP_CPP_SCORE=\
	".\HighScore.h"\
	".\main.h"\
	".\Score.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE SH4) Debug"

DEP_CPP_SCORE=\
	".\HighScore.h"\
	".\main.h"\
	".\Score.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE SH3) Release"

DEP_CPP_SCORE=\
	".\HighScore.h"\
	".\main.h"\
	".\Score.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE SH3) Debug"

DEP_CPP_SCORE=\
	".\HighScore.h"\
	".\main.h"\
	".\Score.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE ARM) Release"

DEP_CPP_SCORE=\
	".\HighScore.h"\
	".\main.h"\
	".\Score.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE ARM) Debug"

DEP_CPP_SCORE=\
	".\HighScore.h"\
	".\main.h"\
	".\Score.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE MIPSFP) Release"

DEP_CPP_SCORE=\
	".\HighScore.h"\
	".\main.h"\
	".\Score.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE MIPSFP) Debug"

DEP_CPP_SCORE=\
	".\HighScore.h"\
	".\main.h"\
	".\Score.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE x86) Release"

DEP_CPP_SCORE=\
	".\HighScore.h"\
	".\main.h"\
	".\Score.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE x86) Debug"

DEP_CPP_SCORE=\
	".\HighScore.h"\
	".\main.h"\
	".\Score.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE x86em) Release"

DEP_CPP_SCORE=\
	".\HighScore.h"\
	".\main.h"\
	".\Score.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE x86em) Debug"

DEP_CPP_SCORE=\
	".\HighScore.h"\
	".\main.h"\
	".\Score.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE PPC) Release"

DEP_CPP_SCORE=\
	".\HighScore.h"\
	".\main.h"\
	".\Score.h"\
	

!ELSEIF  "$(CFG)" == "PuzzleOfPipesCE - Win32 (WCE PPC) Debug"

DEP_CPP_SCORE=\
	".\HighScore.h"\
	".\main.h"\
	".\Score.h"\
	

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Grid.h
# End Source File
# Begin Source File

SOURCE=.\HighScore.h
# End Source File
# Begin Source File

SOURCE=.\main.h
# End Source File
# Begin Source File

SOURCE=.\MainWnd.h
# End Source File
# Begin Source File

SOURCE=.\Pipe.h
# End Source File
# Begin Source File

SOURCE=.\Score.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\2tart_do.bmp
# End Source File
# Begin Source File

SOURCE=.\2tart_le.bmp
# End Source File
# Begin Source File

SOURCE=.\2tart_ri.bmp
# End Source File
# Begin Source File

SOURCE=.\2tart_to.bmp
# End Source File
# Begin Source File

SOURCE=.\blank.bmp
# End Source File
# Begin Source File

SOURCE=.\mainicon.ico
# End Source File
# Begin Source File

SOURCE=.\start_do.bmp
# End Source File
# Begin Source File

SOURCE=.\start_le.bmp
# End Source File
# Begin Source File

SOURCE=.\start_ri.bmp
# End Source File
# Begin Source File

SOURCE=.\start_to.bmp
# End Source File
# End Group
# End Target
# End Project
