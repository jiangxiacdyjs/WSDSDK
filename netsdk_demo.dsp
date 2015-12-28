# Microsoft Developer Studio Project File - Name="netsdk_demo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=netsdk_demo - Win32 Debugable Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "netsdk_demo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "netsdk_demo.mak" CFG="netsdk_demo - Win32 Debugable Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "netsdk_demo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "netsdk_demo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "netsdk_demo - Win32 Debugable Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "netsdk_demo - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\..\tmp\netsdk_demo\Debug"
# PROP Intermediate_Dir "..\..\..\..\..\tmp\netsdk_demo\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\bin\win32\netsdk_demo.exe" /pdbtype:sept /libpath:"../../lib/win32"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy /y ..\..\bin\win32\netsdk_demo.exe ..\..\..\..\..\binvc6
# End Special Build Tool

!ELSEIF  "$(CFG)" == "netsdk_demo - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "netsdk_demo___Win32_Release"
# PROP BASE Intermediate_Dir "netsdk_demo___Win32_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\..\tmp\netsdk_demo\Release"
# PROP Intermediate_Dir "..\..\..\..\..\tmp\netsdk_demo\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\dllsdk" /I "../../libs" /I "../../libs/common/inc" /I "../../thirdParty" /I "../../thirdParty/ffmpeg/inc" /I "../../os" /I "../../ipcSdk/inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /I "../../inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\binvc6\netsdk_demoD.exe" /pdbtype:sept /libpath:"..\dllsdk" /libpath:"../../bin" /libpath:"../../thirdParty/bin/win32"
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\bin\win32\netsdk_demo.exe" /pdbtype:sept /libpath:"../../lib/win32"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy    /y    ..\..\bin\win32\netsdk_demo.exe    ..\..\..\..\..\binvc6   	copy    /y    ..\..\bin\win32\netsdk_demo.exe    ..\..\..\ipc_sdk_eng\bin\win32\ 
# End Special Build Tool

!ELSEIF  "$(CFG)" == "netsdk_demo - Win32 Debugable Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "netsdk_demo___Win32_Debugable_Release"
# PROP BASE Intermediate_Dir "netsdk_demo___Win32_Debugable_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "netsdk_demo___Win32_Debugable_Release"
# PROP Intermediate_Dir "netsdk_demo___Win32_Debugable_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /Gm /GX /ZI /I "../../inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I "../../inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\bin\win32\netsdk_demo.exe" /pdbtype:sept /libpath:"../../lib/win32"
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\bin\win32\netsdk_demo.exe" /pdbtype:sept /libpath:"../../lib/win32"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy    /y    ..\..\bin\win32\netsdk_demo.exe    ..\..\..\..\..\binvc6   	copy    /y    ..\..\bin\win32\netsdk_demo.exe    ..\..\..\ipc_sdk_eng\bin\win32\ 
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "netsdk_demo - Win32 Debug"
# Name "netsdk_demo - Win32 Release"
# Name "netsdk_demo - Win32 Debugable Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\3DPositioningWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\3DRectDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ACDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AlarmDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AudioDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BallVideoMaskDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BPSDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CAMDDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CARecordDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CASensorInDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CAVLDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ComDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomDrawWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\DevRecordDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DevRecSearchDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EmailDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EncryptStrDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FTPDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\HsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LangMan.cpp
# End Source File
# Begin Source File

SOURCE=.\MDDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MDGridCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\NetDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\netsdk_demo.cpp
# End Source File
# Begin Source File

SOURCE=.\netsdk_demo.rc
# End Source File
# Begin Source File

SOURCE=.\netsdk_demoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\OSDDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PortDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PresetDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PTZ20Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SearchDevDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SensorOutDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SystemDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TimeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TrackDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\UpdateDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\UserAddDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\UserDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\VideoLossDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\VideoMaskDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\VideoWndBase.cpp
# End Source File
# Begin Source File

SOURCE=.\WADlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\3DRectDlg.h
# End Source File
# Begin Source File

SOURCE=.\ACDlg.h
# End Source File
# Begin Source File

SOURCE=.\AlarmDlg.h
# End Source File
# Begin Source File

SOURCE=.\AudioDlg.h
# End Source File
# Begin Source File

SOURCE=.\BallVideoMaskDlg.h
# End Source File
# Begin Source File

SOURCE=.\BPSDlg.h
# End Source File
# Begin Source File

SOURCE=.\CAMDDlg.h
# End Source File
# Begin Source File

SOURCE=.\CARecordDlg.h
# End Source File
# Begin Source File

SOURCE=.\CASensorInDlg.h
# End Source File
# Begin Source File

SOURCE=.\CAVLDlg.h
# End Source File
# Begin Source File

SOURCE=.\ColorDlg.h
# End Source File
# Begin Source File

SOURCE=.\ComDlg.h
# End Source File
# Begin Source File

SOURCE=.\DevRecordDlg.h
# End Source File
# Begin Source File

SOURCE=.\DevRecSearchDlg.h
# End Source File
# Begin Source File

SOURCE=.\EmailDlg.h
# End Source File
# Begin Source File

SOURCE=.\EncryptStrDlg.h
# End Source File
# Begin Source File

SOURCE=.\FTPDlg.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl.h
# End Source File
# Begin Source File

SOURCE=.\HsDlg.h
# End Source File
# Begin Source File

SOURCE=.\MDDlg.h
# End Source File
# Begin Source File

SOURCE=.\MDGridCtrl.h
# End Source File
# Begin Source File

SOURCE=.\NetDlg.h
# End Source File
# Begin Source File

SOURCE=.\netsdk_demo.h
# End Source File
# Begin Source File

SOURCE=.\netsdk_demoDlg.h
# End Source File
# Begin Source File

SOURCE=.\OSDDlg.h
# End Source File
# Begin Source File

SOURCE=.\PortDlg.h
# End Source File
# Begin Source File

SOURCE=.\PresetDlg.h
# End Source File
# Begin Source File

SOURCE=.\PTZ20Dlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SensorOutDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SystemDlg.h
# End Source File
# Begin Source File

SOURCE=.\TimeDlg.h
# End Source File
# Begin Source File

SOURCE=.\TrackDlg.h
# End Source File
# Begin Source File

SOURCE=.\UpdateDlg.h
# End Source File
# Begin Source File

SOURCE=.\UserAddDlg.h
# End Source File
# Begin Source File

SOURCE=.\UserDlg.h
# End Source File
# Begin Source File

SOURCE=.\VideoLossDlg.h
# End Source File
# Begin Source File

SOURCE=.\VideoMaskDlg.h
# End Source File
# Begin Source File

SOURCE=.\WADlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\netsdk_demo.ico
# End Source File
# Begin Source File

SOURCE=.\res\netsdk_demo.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\chs.lang.ini
# End Source File
# Begin Source File

SOURCE=.\res\eng.lang.ini
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
