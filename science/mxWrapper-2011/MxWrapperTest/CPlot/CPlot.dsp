# Microsoft Developer Studio Project File - Name="CPlot" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=CPlot - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CPlot.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CPlot.mak" CFG="CPlot - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CPlot - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "CPlot - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CPlot - Win32 Release"

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
# ADD BASE RSC /l 0x1409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "CPlot - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x1409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "CPlot - Win32 Release"
# Name "CPlot - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=".\CPlot Sources\Axis.cpp"
# End Source File
# Begin Source File

SOURCE=".\CPlot Sources\AxisSettings.cpp"
# End Source File
# Begin Source File

SOURCE=".\CPlot Sources\Chart.cpp"
# End Source File
# Begin Source File

SOURCE=".\CPlot Sources\ChartData.cpp"
# End Source File
# Begin Source File

SOURCE=".\CPlot Sources\ColorControl.cpp"
# End Source File
# Begin Source File

SOURCE=.\CPlot.cpp
# End Source File
# Begin Source File

SOURCE=.\CPlot.rc
# End Source File
# Begin Source File

SOURCE=.\CPlotDoc.cpp
# End Source File
# Begin Source File

SOURCE=".\CPlot Sources\CPlotResources.rc"
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=".\CPlot Sources\CPlotUtility.cpp"
# End Source File
# Begin Source File

SOURCE=.\CPlotView.cpp
# End Source File
# Begin Source File

SOURCE=".\CPlot Sources\DataSettingsDialog.cpp"
# End Source File
# Begin Source File

SOURCE=".\CPlot Sources\ImageChart.cpp"
# End Source File
# Begin Source File

SOURCE=".\CPlot Sources\ImagePalette.cpp"
# End Source File
# Begin Source File

SOURCE=".\CPlot Sources\ImagePlotSettingsDialog.cpp"
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=".\CPlot Sources\PlotSettingsDialog.cpp"
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=".\CPlot Sources\XYChart.cpp"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=".\CPlot Sources\Axis.h"
# End Source File
# Begin Source File

SOURCE=".\CPlot Sources\AxisSettings.h"
# End Source File
# Begin Source File

SOURCE=".\CPlot Sources\Chart.h"
# End Source File
# Begin Source File

SOURCE=".\CPlot Sources\ChartData.h"
# End Source File
# Begin Source File

SOURCE=".\CPlot Sources\ColorControl.h"
# End Source File
# Begin Source File

SOURCE=".\CPlot Sources\ColorTables.h"
# End Source File
# Begin Source File

SOURCE=.\CPlot.h
# End Source File
# Begin Source File

SOURCE=.\CPlotDoc.h
# End Source File
# Begin Source File

SOURCE=".\CPlot Sources\CPlotUtility.h"
# End Source File
# Begin Source File

SOURCE=.\CPlotView.h
# End Source File
# Begin Source File

SOURCE=".\CPlot Sources\DataSettingsDialog.h"
# End Source File
# Begin Source File

SOURCE=".\CPlot Sources\ImagePalette.h"
# End Source File
# Begin Source File

SOURCE=".\CPlot Sources\ImagePlotSettingsDialog.h"
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=".\CPlot Sources\PlotSettingsDialog.h"
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

SOURCE=".\CPlotResources\res\16 LEVEL.bin"
# End Source File
# Begin Source File

SOURCE=".\CPlotResources\res\B-W LINEAR.bin"
# End Source File
# Begin Source File

SOURCE=.\CPlotResources\res\Beach.bin
# End Source File
# Begin Source File

SOURCE=".\CPlotResources\res\Blue - Pastel - Red.bin"
# End Source File
# Begin Source File

SOURCE=".\CPlotResources\res\Blue Waves.bin"
# End Source File
# Begin Source File

SOURCE=".\CPlotResources\res\BLUE-RED.bin"
# End Source File
# Begin Source File

SOURCE=.\res\CPlot.ico
# End Source File
# Begin Source File

SOURCE=.\res\CPlotDoc.ico
# End Source File
# Begin Source File

SOURCE=".\CPlotResources\res\Eos A.bin"
# End Source File
# Begin Source File

SOURCE=".\CPlotResources\res\Eos B.bin"
# End Source File
# Begin Source File

SOURCE=".\CPlotResources\res\GREEN-PINK.bin"
# End Source File
# Begin Source File

SOURCE=".\CPlotResources\res\GRN-RED-BLU-WHT.bin"
# End Source File
# Begin Source File

SOURCE=.\CPlotResources\res\Hardcandy.bin
# End Source File
# Begin Source File

SOURCE=.\CPlotResources\res\Haze.bin
# End Source File
# Begin Source File

SOURCE=".\CPlotResources\res\Hue Sat Lightness 1.bin"
# End Source File
# Begin Source File

SOURCE=".\CPlotResources\res\Hue Sat Lightness 2.bin"
# End Source File
# Begin Source File

SOURCE=".\CPlotResources\res\Mac Style.bin"
# End Source File
# Begin Source File

SOURCE=.\CPlotResources\res\Nature.bin
# End Source File
# Begin Source File

SOURCE=.\CPlotResources\res\Ocean.bin
# End Source File
# Begin Source File

SOURCE=.\CPlotResources\res\Pastels.bin
# End Source File
# Begin Source File

SOURCE=.\CPlotResources\res\Peppermint.bin
# End Source File
# Begin Source File

SOURCE=.\CPlotResources\res\Plasma.bin
# End Source File
# Begin Source File

SOURCE=.\CPlotResources\res\PRISM.bin
# End Source File
# Begin Source File

SOURCE=".\CPlotResources\res\Purple-Red + Stripes.bin"
# End Source File
# Begin Source File

SOURCE=".\CPlotResources\res\Rainbow + black.bin"
# End Source File
# Begin Source File

SOURCE=".\CPlotResources\res\Rainbow + white.bin"
# End Source File
# Begin Source File

SOURCE=.\CPlotResources\res\RAINBOW.bin
# End Source File
# Begin Source File

SOURCE=.\CPlotResources\res\Rainbow18.bin
# End Source File
# Begin Source File

SOURCE=".\CPlotResources\res\RED TEMPERATURE.bin"
# End Source File
# Begin Source File

SOURCE=".\CPlotResources\res\RED-PURPLE.bin"
# End Source File
# Begin Source File

SOURCE=".\CPlotResources\res\STD GAMMA-II.bin"
# End Source File
# Begin Source File

SOURCE=.\CPlotResources\res\STEPS.bin
# End Source File
# Begin Source File

SOURCE=".\CPlotResources\res\STERN SPECIAL.bin"
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\CPlotResources\res\Volcano.bin
# End Source File
# Begin Source File

SOURCE=.\CPlotResources\res\Waves.bin
# End Source File
# End Group
# Begin Source File

SOURCE=.\CHANGELOG.txt
# End Source File
# Begin Source File

SOURCE=.\LICENSE.txt
# End Source File
# End Target
# End Project
