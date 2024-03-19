# Microsoft Developer Studio Project File - Name="KeyStrokeCE" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (WCE MIPS) Dynamic-Link Library" 0x8202

CFG=KeyStrokeCE - Win32 (WCE MIPS) Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "KeyStrokeCE.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "KeyStrokeCE.mak" CFG="KeyStrokeCE - Win32 (WCE MIPS) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "KeyStrokeCE - Win32 (WCE MIPS) Release" (based on "Win32 (WCE MIPS) Dynamic-Link Library")
!MESSAGE "KeyStrokeCE - Win32 (WCE MIPS) Debug" (based on "Win32 (WCE MIPS) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath "Palm-size PC 2.01"
# PROP WCE_FormatVersion "6.0"
CPP=clmips.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "KeyStrokeCE - Win32 (WCE MIPS) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WMIPSRel"
# PROP BASE Intermediate_Dir "WMIPSRel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WMIPSRel"
# PROP Intermediate_Dir "WMIPSRel"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /M$(CECrt) /W3 /O2 /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "MIPS" /D "_MIPS_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /D "_USRDLL" /D "KEYStrokeCE_EXPORTS" /YX /QMRWCE /c
# ADD CPP /nologo /M$(CECrt) /W3 /O2 /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "MIPS" /D "_MIPS_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /D "_USRDLL" /D "KEYStrokeCE_EXPORTS" /YX /QMRWCE /c
# ADD BASE RSC /l 0x409 /r /d "MIPS" /d "_MIPS_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG"
# ADD RSC /l 0x409 /r /d "MIPS" /d "_MIPS_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG"
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 commctrl.lib coredll.lib /nologo /dll /machine:MIPS /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 commctrl.lib coredll.lib /nologo /dll /machine:MIPS /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ELSEIF  "$(CFG)" == "KeyStrokeCE - Win32 (WCE MIPS) Debug"

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
# ADD BASE CPP /nologo /M$(CECrtDebug) /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "MIPS" /D "_MIPS_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /D "_USRDLL" /D "KEYStrokeCE_EXPORTS" /YX /QMRWCE /c
# ADD CPP /nologo /M$(CECrtDebug) /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "MIPS" /D "_MIPS_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /D "_USRDLL" /D "KEYStrokeCE_EXPORTS" /YX /QMRWCE /c
# ADD BASE RSC /l 0x409 /r /d "MIPS" /d "_MIPS_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG"
# ADD RSC /l 0x409 /r /d "MIPS" /d "_MIPS_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG"
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 commctrl.lib coredll.lib /nologo /dll /debug /machine:MIPS /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 commctrl.lib coredll.lib /nologo /dll /debug /machine:MIPS /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ENDIF 

# Begin Target

# Name "KeyStrokeCE - Win32 (WCE MIPS) Release"
# Name "KeyStrokeCE - Win32 (WCE MIPS) Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\exports.def
# End Source File
# Begin Source File

SOURCE=.\KeyStrokeCE.cpp
DEP_CPP_KEYST=\
	".\KeyStrokeCE.h"\
	".\main.h"\
	".\MainWnd.h"\
	".\Movement.h"\
	{$(INCLUDE)}"aygshell.h"\
	{$(INCLUDE)}"coguid.h"\
	{$(INCLUDE)}"sip.h"\
	
# End Source File
# Begin Source File

SOURCE=.\MainWnd.cpp
DEP_CPP_MAINW=\
	".\main.h"\
	".\MainWnd.h"\
	".\Movement.h"\
	{$(INCLUDE)}"aygshell.h"\
	{$(INCLUDE)}"keybd.h"\
	{$(INCLUDE)}"sip.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Movement.cpp
DEP_CPP_MOVEM=\
	".\Movement.h"\
	
# End Source File
# Begin Source File

SOURCE=.\resource.rc
# End Source File
# Begin Source File

SOURCE=.\Sip_i.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\KeyStrokeCE.h
# End Source File
# Begin Source File

SOURCE=.\main.h
# End Source File
# Begin Source File

SOURCE=.\MainWnd.h
# End Source File
# Begin Source File

SOURCE=.\Movement.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\alt.bmp
# End Source File
# Begin Source File

SOURCE=.\altlocke.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\bkimg.bmp
# End Source File
# Begin Source File

SOURCE=.\cells.bmp
# End Source File
# Begin Source File

SOURCE=.\Snipper\key_alt_1.bmp
# End Source File
# Begin Source File

SOURCE=.\Snipper\key_alt_2.bmp
# End Source File
# Begin Source File

SOURCE=.\Snipper\key_cap_1.bmp
# End Source File
# Begin Source File

SOURCE=.\Snipper\key_cap_2.bmp
# End Source File
# Begin Source File

SOURCE=.\Snipper\key_nrm_1.bmp
# End Source File
# Begin Source File

SOURCE=.\Snipper\key_nrm_2.bmp
# End Source File
# Begin Source File

SOURCE=.\Snipper\key_num_1.bmp
# End Source File
# Begin Source File

SOURCE=.\Snipper\key_num_2.bmp
# End Source File
# Begin Source File

SOURCE=.\keycap.bmp
# End Source File
# Begin Source File

SOURCE=.\keycaplo.bmp
# End Source File
# Begin Source File

SOURCE=.\keynrm.bmp
# End Source File
# Begin Source File

SOURCE=.\ArtWork\keypad.bmp
# End Source File
# Begin Source File

SOURCE=.\DrawStuff\keypad.bmp
# End Source File
# Begin Source File

SOURCE=.\Snipper\keypad.bmp
# End Source File
# Begin Source File

SOURCE=.\DrawStuff\keypad_down.bmp
# End Source File
# Begin Source File

SOURCE=.\Snipper\keypad_down.bmp
# End Source File
# Begin Source File

SOURCE=.\left.bmp
# End Source File
# Begin Source File

SOURCE=.\mask.bmp
# End Source File
# Begin Source File

SOURCE=.\Snipper\middle.bmp
# End Source File
# Begin Source File

SOURCE=.\narrow.bmp
# End Source File
# Begin Source File

SOURCE=.\narrow_mask.bmp
# End Source File
# Begin Source File

SOURCE=.\NKBD.BMP
# End Source File
# Begin Source File

SOURCE=.\NMASK.BMP
# End Source File
# Begin Source File

SOURCE=.\numlocke.bmp
# End Source File
# Begin Source File

SOURCE=.\NumPanel.ico
# End Source File
# Begin Source File

SOURCE=.\right.bmp
# End Source File
# Begin Source File

SOURCE=.\Snipper\state_alt_1.bmp
# End Source File
# Begin Source File

SOURCE=.\Snipper\state_alt_2.bmp
# End Source File
# Begin Source File

SOURCE=.\Snipper\state_alt_locked_1.bmp
# End Source File
# Begin Source File

SOURCE=.\Snipper\state_alt_locked_2.bmp
# End Source File
# Begin Source File

SOURCE=.\Snipper\state_cap_1.bmp
# End Source File
# Begin Source File

SOURCE=.\Snipper\state_cap_2.bmp
# End Source File
# Begin Source File

SOURCE=.\Snipper\state_cap_locked_1.bmp
# End Source File
# Begin Source File

SOURCE=.\Snipper\state_cap_locked_2.bmp
# End Source File
# Begin Source File

SOURCE=.\Snipper\state_nrm_1.bmp
# End Source File
# Begin Source File

SOURCE=.\Snipper\state_nrm_2.bmp
# End Source File
# Begin Source File

SOURCE=.\Snipper\state_num_1.bmp
# End Source File
# Begin Source File

SOURCE=.\Snipper\state_num_2.bmp
# End Source File
# Begin Source File

SOURCE=.\Snipper\state_num_locked_1.bmp
# End Source File
# Begin Source File

SOURCE=.\Snipper\state_num_locked_2.bmp
# End Source File
# Begin Source File

SOURCE=.\wide.bmp
# End Source File
# Begin Source File

SOURCE=.\wide_mask.bmp
# End Source File
# Begin Source File

SOURCE=.\WIDEKBD.BMP
# End Source File
# Begin Source File

SOURCE=.\WIDEMASK.BMP
# End Source File
# End Group
# Begin Group "Other"

# PROP Default_Filter "txt"
# Begin Source File

SOURCE=".\Unconverted Code.txt"
# End Source File
# Begin Source File

SOURCE=.\Workspace.txt
# End Source File
# End Group
# Begin Source File

SOURCE=.\cells.dat
# End Source File
# Begin Source File

SOURCE=.\Snipper\cells.dat
# End Source File
# End Target
# End Project
