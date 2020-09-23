# Microsoft Developer Studio Project File - Name="DSPLIT" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DSPLIT - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DSPLIT.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DSPLIT.mak" CFG="DSPLIT - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DSPLIT - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DSPLIT - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DSPLIT - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "DSPLIT - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "DSPLIT - Win32 Release"
# Name "DSPLIT - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BpNet.cpp
# End Source File
# Begin Source File

SOURCE=.\Cdib.cpp
# End Source File
# Begin Source File

SOURCE=.\Classification.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgClassify.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlgdisplay.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNumber.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTemplate.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWeight.cpp
# End Source File
# Begin Source File

SOURCE=.\DSPLIT.cpp
# End Source File
# Begin Source File

SOURCE=.\DSPLIT.rc
# End Source File
# Begin Source File

SOURCE=.\DSPLITDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\DSPLITView.cpp
# End Source File
# Begin Source File

SOURCE=.\DYNSPLITTERWND.CPP
# End Source File
# Begin Source File

SOURCE=.\DynSplitView2.cpp
# End Source File
# Begin Source File

SOURCE=.\GetFeature.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BpNet.h
# End Source File
# Begin Source File

SOURCE=.\Cdib.h
# End Source File
# Begin Source File

SOURCE=.\Classification.h
# End Source File
# Begin Source File

SOURCE=.\DlgClassify.h
# End Source File
# Begin Source File

SOURCE=.\Dlgdisplay.h
# End Source File
# Begin Source File

SOURCE=.\DlgNumber.h
# End Source File
# Begin Source File

SOURCE=.\DlgTemplate.h
# End Source File
# Begin Source File

SOURCE=.\DlgWeight.h
# End Source File
# Begin Source File

SOURCE=.\DSPLIT.h
# End Source File
# Begin Source File

SOURCE=.\DSPLITDoc.h
# End Source File
# Begin Source File

SOURCE=.\DSPLITView.h
# End Source File
# Begin Source File

SOURCE=.\DYNSPLITTERWND.H
# End Source File
# Begin Source File

SOURCE=.\DynSplitView2.h
# End Source File
# Begin Source File

SOURCE=.\GetFeature.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Matrix.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor2.cur
# End Source File
# Begin Source File

SOURCE=.\res\DSPLIT.ico
# End Source File
# Begin Source File

SOURCE=.\res\DSPLIT.rc2
# End Source File
# Begin Source File

SOURCE=.\res\DSPLITDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
