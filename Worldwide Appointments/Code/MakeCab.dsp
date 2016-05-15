# Microsoft Developer Studio Project File - Name="MakeCab" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Generic Project" 0x010a

CFG=MakeCab - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MakeCab.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MakeCab.mak" CFG="MakeCab - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MakeCab - Win32 Release" (based on "Win32 (x86) Generic Project")
!MESSAGE "MakeCab - Win32 Debug" (based on "Win32 (x86) Generic Project")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Worldwide Appointments/Code", BCAAAAAA"
# PROP Scc_LocalPath "."
MTL=midl.exe

!IF  "$(CFG)" == "MakeCab - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Install"
# PROP Intermediate_Dir "Temp"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "MakeCab - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Install"
# PROP Intermediate_Dir "Temp"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "MakeCab - Win32 Release"
# Name "MakeCab - Win32 Debug"
# Begin Source File

SOURCE=.\MoveAppt\ARMRel\MoveAppt.dll

!IF  "$(CFG)" == "MakeCab - Win32 Release"

# Begin Custom Build
IntDir=.\Temp
InputPath=.\MoveAppt\ARMRel\MoveAppt.dll
InputName=MoveAppt

BuildCmds= \
	copy "$(InputPath)" "$(IntDir)\ARM" \
	copy "$(POOMSDK)\pimstore_sa1100.dll" "$(IntDir)\ARM\pimstore.dll" \
	

"$(IntDir)\ARM\$(InputName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(IntDir)\ARM\pimstore.dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "MakeCab - Win32 Debug"

# Begin Custom Build
IntDir=.\Temp
InputPath=.\MoveAppt\ARMRel\MoveAppt.dll
InputName=MoveAppt

BuildCmds= \
	copy "$(InputPath)" "$(IntDir)\ARM" \
	copy "$(POOMSDK)\pimstore_sa1100.dll" "$(IntDir)\ARM\pimstore.dll" \
	

"$(IntDir)\ARM\$(InputName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(IntDir)\ARM\pimstore.dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MoveAppt\MIPSRel\MoveAppt.dll

!IF  "$(CFG)" == "MakeCab - Win32 Release"

# Begin Custom Build
IntDir=.\Temp
InputPath=.\MoveAppt\MIPSRel\MoveAppt.dll
InputName=MoveAppt

BuildCmds= \
	copy "$(InputPath)" "$(IntDir)\MIPS" \
	copy "$(POOMSDK)\pimstore_r4100.dll" "$(IntDir)\MIPS\pimstore.dll" \
	

"$(IntDir)\MIPS\$(InputName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(IntDir)\MIPS\pimstore.dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "MakeCab - Win32 Debug"

# Begin Custom Build
IntDir=.\Temp
InputPath=.\MoveAppt\MIPSRel\MoveAppt.dll
InputName=MoveAppt

BuildCmds= \
	copy "$(InputPath)" "$(IntDir)\MIPS" \
	copy "$(POOMSDK)\pimstore_r4100.dll" "$(IntDir)\MIPS\pimstore.dll" \
	

"$(IntDir)\MIPS\$(InputName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(IntDir)\MIPS\pimstore.dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MoveAppt\SH3Rel\MoveAppt.dll

!IF  "$(CFG)" == "MakeCab - Win32 Release"

# Begin Custom Build
IntDir=.\Temp
InputPath=.\MoveAppt\SH3Rel\MoveAppt.dll
InputName=MoveAppt

BuildCmds= \
	copy "$(InputPath)" "$(IntDir)\SH3" \
	copy "$(POOMSDK)\pimstore_sh3.dll" "$(IntDir)\SH3\pimstore.dll" \
	

"$(IntDir)\SH3\$(InputName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(IntDir)\SH3\pimstore.dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "MakeCab - Win32 Debug"

# Begin Custom Build
IntDir=.\Temp
InputPath=.\MoveAppt\SH3Rel\MoveAppt.dll
InputName=MoveAppt

BuildCmds= \
	copy "$(InputPath)" "$(IntDir)\SH3" \
	copy "$(POOMSDK)\pimstore_sh3.dll" "$(IntDir)\SH3\pimstore.dll" \
	

"$(IntDir)\SH3\$(InputName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(IntDir)\SH3\pimstore.dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MoveAppt.ico

!IF  "$(CFG)" == "MakeCab - Win32 Release"

# Begin Custom Build
OutDir=.\Install
InputPath=.\MoveAppt.ico

"$(OutDir)\MoveAppt.ico" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(OutDir)\MoveAppt.ico"

# End Custom Build

!ELSEIF  "$(CFG)" == "MakeCab - Win32 Debug"

# Begin Custom Build
OutDir=.\Install
InputPath=.\MoveAppt.ico

"$(OutDir)\MoveAppt.ico" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(OutDir)\MoveAppt.ico"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MoveAppt.inf

!IF  "$(CFG)" == "MakeCab - Win32 Release"

USERDEP__MOVEA="$(IntDir)\SH3\MoveAppt.dll"	"$(IntDir)\MIPS\MoveAppt.dll"	"$(IntDir)\ARM\MoveAppt.dll"	"$(IntDir)\SH3\Setup.dll"	"$(IntDir)\MIPS\Setup.dll"	"$(IntDir)\ARM\Setup.dll"	"$(OutDir)\MoveAppt.ico"	"$(IntDir)\SH3\pimstore.dll"	"$(IntDir)\MIPS\pimstore.dll"	"$(IntDir)\ARM\pimstore.dll"	
# Begin Custom Build
IntDir=.\Temp
OutDir=.\Install
WkspDir=.
InputPath=.\MoveAppt.inf

BuildCmds= \
	"$(CABWIZ)\cabwiz.exe" "$(WkspDir)\MoveAppt.inf" /dest "$(WkspDir)\Install" /cpu sh3 mips arm

"$(OutDir)\MoveAppt.sh3.cab" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(OutDir)\MoveAppt.sh3.dat" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(OutDir)\MoveAppt.mips.cab" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(OutDir)\MoveAppt.mips.dat" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(OutDir)\MoveAppt.arm.cab" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(OutDir)\MoveAppt.arm.dat" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "MakeCab - Win32 Debug"

USERDEP__MOVEA="$(IntDir)\SH3\MoveAppt.dll"	"$(IntDir)\MIPS\MoveAppt.dll"	"$(IntDir)\ARM\MoveAppt.dll"	"$(IntDir)\SH3\Setup.dll"	"$(IntDir)\MIPS\Setup.dll"	"$(IntDir)\ARM\Setup.dll"	"$(OutDir)\MoveAppt.ico"	"$(IntDir)\SH3\pimstore.dll"	"$(IntDir)\MIPS\pimstore.dll"	"$(IntDir)\ARM\pimstore.dll"	
# Begin Custom Build
IntDir=.\Temp
OutDir=.\Install
WkspDir=.
InputPath=.\MoveAppt.inf

BuildCmds= \
	"$(CABWIZ)\cabwiz.exe" "$(WkspDir)\MoveAppt.inf" /dest "$(WkspDir)\Install" /cpu sh3 mips arm

"$(OutDir)\MoveAppt.sh3.cab" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(OutDir)\MoveAppt.sh3.dat" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(OutDir)\MoveAppt.mips.cab" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(OutDir)\MoveAppt.mips.dat" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(OutDir)\MoveAppt.arm.cab" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(OutDir)\MoveAppt.arm.dat" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MoveAppt.ini

!IF  "$(CFG)" == "MakeCab - Win32 Release"

# Begin Custom Build
OutDir=.\Install
InputPath=.\MoveAppt.ini

"$(OutDir)\MoveAppt.ini" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(OutDir)\MoveAppt.ini"

# End Custom Build

!ELSEIF  "$(CFG)" == "MakeCab - Win32 Debug"

# Begin Custom Build
OutDir=.\Install
InputPath=.\MoveAppt.ini

"$(OutDir)\MoveAppt.ini" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(OutDir)\MoveAppt.ini"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SetupDLL\ARMRel\Setup.dll

!IF  "$(CFG)" == "MakeCab - Win32 Release"

# Begin Custom Build
IntDir=.\Temp
InputPath=.\SetupDLL\ARMRel\Setup.dll
InputName=Setup

"$(IntDir)\ARM\$(InputName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(IntDir)\ARM"

# End Custom Build

!ELSEIF  "$(CFG)" == "MakeCab - Win32 Debug"

# Begin Custom Build
IntDir=.\Temp
InputPath=.\SetupDLL\ARMRel\Setup.dll
InputName=Setup

"$(IntDir)\ARM\$(InputName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(IntDir)\ARM"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SetupDLL\MIPSRel\Setup.dll

!IF  "$(CFG)" == "MakeCab - Win32 Release"

# Begin Custom Build
IntDir=.\Temp
InputPath=.\SetupDLL\MIPSRel\Setup.dll
InputName=Setup

"$(IntDir)\MIPS\$(InputName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(IntDir)\MIPS"

# End Custom Build

!ELSEIF  "$(CFG)" == "MakeCab - Win32 Debug"

# Begin Custom Build
IntDir=.\Temp
InputPath=.\SetupDLL\MIPSRel\Setup.dll
InputName=Setup

"$(IntDir)\MIPS\$(InputName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(IntDir)\MIPS"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SetupDLL\SH3Rel\Setup.dll

!IF  "$(CFG)" == "MakeCab - Win32 Release"

# Begin Custom Build
IntDir=.\Temp
InputPath=.\SetupDLL\SH3Rel\Setup.dll
InputName=Setup

"$(IntDir)\SH3\$(InputName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(IntDir)\SH3"

# End Custom Build

!ELSEIF  "$(CFG)" == "MakeCab - Win32 Debug"

# Begin Custom Build
IntDir=.\Temp
InputPath=.\SetupDLL\SH3Rel\Setup.dll
InputName=Setup

"$(IntDir)\SH3\$(InputName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(IntDir)\SH3"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SetupEXE\Release\Setup.exe

!IF  "$(CFG)" == "MakeCab - Win32 Release"

# Begin Custom Build
OutDir=.\Install
InputPath=.\SetupEXE\Release\Setup.exe

"$(OutDir)\Setup.exe" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(OutDir)\Setup.exe"

# End Custom Build

!ELSEIF  "$(CFG)" == "MakeCab - Win32 Debug"

# Begin Custom Build
OutDir=.\Install
InputPath=.\SetupEXE\Release\Setup.exe

"$(OutDir)\Setup.exe" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(OutDir)\Setup.exe"

# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
