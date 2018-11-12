; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDataSettingsDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "cplot.h"
LastPage=0

ClassCount=10
Class1=CAxisSettings
Class2=CColorControl
Class3=CCPlotApp
Class4=CAboutDlg
Class5=CCPlotDoc
Class6=CCPlotView
Class7=CDataSettingsDialog
Class8=CImagePlotSettingsDialog
Class9=CMainFrame
Class10=CPlotSettingsDialog

ResourceCount=4
Resource1=IDD_IMAGE_SETTINGS (English (U.S.))
Resource2=IDD_XY_SETTINGS (English (U.S.))
Resource3=IDD_ABOUTBOX (English (U.S.))
Resource4=IDR_MAINFRAME (English (U.S.))

[CLS:CAxisSettings]
Type=0
BaseClass=CDialog
HeaderFile=AxisSettings.h
ImplementationFile=AxisSettings.cpp

[CLS:CColorControl]
Type=0
BaseClass=CWnd
HeaderFile=ColorControl.h
ImplementationFile=ColorControl.cpp

[CLS:CCPlotApp]
Type=0
BaseClass=CWinApp
HeaderFile=CPlot.h
ImplementationFile=CPlot.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=CPlot.cpp
ImplementationFile=CPlot.cpp
LastObject=CAboutDlg

[CLS:CCPlotDoc]
Type=0
BaseClass=CDocument
HeaderFile=CPlotDoc.h
ImplementationFile=CPlotDoc.cpp

[CLS:CCPlotView]
Type=0
BaseClass=CView
HeaderFile=CPlotView.h
ImplementationFile=CPlotView.cpp
Filter=C
VirtualFilter=VWC
LastObject=IDC_MAJOR_GRID_SIZE

[CLS:CDataSettingsDialog]
Type=0
BaseClass=CDialog
HeaderFile=DataSettingsDialog.h
ImplementationFile=DataSettingsDialog.cpp
Filter=D
VirtualFilter=dWC
LastObject=CDataSettingsDialog

[CLS:CImagePlotSettingsDialog]
Type=0
BaseClass=CDialog
HeaderFile=ImagePlotSettingsDialog.h
ImplementationFile=ImagePlotSettingsDialog.cpp
Filter=D
VirtualFilter=dWC

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CPlotSettingsDialog]
Type=0
BaseClass=CDialog
HeaderFile=PlotSettingsDialog.h
ImplementationFile=PlotSettingsDialog.cpp
Filter=D
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
Command9=ID_CHART_XYCHART
Command10=ID_CHART_2DCHART
CommandCount=10

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_CHART_XYCHART
Command17=ID_CHART_2DCHART
Command18=ID_PLOTSETTINGS_PLOTSETUP
Command19=ID_PLOTSETTINGS_AXISSETUP
Command20=ID_PLOTSETTINGS_DATASETUP
Command21=ID_PLOTSETTINGS_COLORTABLE
Command22=ID_APP_ABOUT
CommandCount=22

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=8
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352

[DLG:IDD_XY_SETTINGS (English (U.S.))]
Type=1
Class=CPlotSettingsDialog
ControlCount=40
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_PS_XRANGE_LOW,edit,1350631552
Control8=IDC_PS_XRANGE_HIGH,edit,1350631552
Control9=IDC_STATIC,static,1342308353
Control10=IDC_PS_YRANGE_LOW,edit,1350631552
Control11=IDC_PS_YRANGE_HIGH,edit,1350631552
Control12=IDC_STATIC,static,1342308353
Control13=IDC_PS_AUTO_XRANGE,button,1342242819
Control14=IDC_PS_AUTO_YRANGE,button,1342242819
Control15=IDC_STATIC,button,1342177287
Control16=IDC_PS_MAJOR_HORIZONTAL_GRIDS,button,1342242819
Control17=IDC_MINOR_HORIZONTAL_GRIDS,button,1342242819
Control18=IDC_PS_MAJOR_VERTICAL_GRIDS,button,1342242819
Control19=IDC_MINOR_VERTICAL_GRIDS,button,1342242819
Control20=IDC_STATIC,static,1342308352
Control21=IDC_PS_COLOR_MAJOR_GRIDS,colorcontrol,1342242816
Control22=IDC_STATIC,static,1342308352
Control23=IDC_PS_COLOR_MINOR_GRIDS,colorcontrol,1342242816
Control24=IDC_STATIC,button,1342177287
Control25=IDC_STATIC,static,1342308352
Control26=IDC_PS_PLOT_TITLE,edit,1350631552
Control27=IDC_STATIC,static,1342308352
Control28=IDC_PS_TITLE_FONT,static,1342308352
Control29=IDC_PS_CHOOSE_TITLE_FONT,button,1342242816
Control30=IDC_STATIC,static,1342308352
Control31=IDC_PS_COLOR_TITLE_FONT,colorcontrol,1342242816
Control32=IDC_STATIC,button,1342177287
Control33=IDC_STATIC,static,1342308352
Control34=IDC_STATIC,static,1342308352
Control35=IDC_PS_COLOR_BACKGROUND,colorcontrol,1342242816
Control36=IDC_PS_COLOR_BORDER,colorcontrol,1342242816
Control37=IDC_STATIC,static,1342308352
Control38=IDC_STATIC,static,1342308352
Control39=IDC_MAJOR_GRID_SIZE,edit,1350631552
Control40=IDC_MINOR_GRID_SIZE,edit,1350631552

[DLG:IDD_IMAGE_SETTINGS (English (U.S.))]
Type=1
Class=CImagePlotSettingsDialog
ControlCount=33
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,button,1342177287
Control6=IDC_PS_MAJOR_HORIZONTAL_GRIDS,button,1342242819
Control7=IDC_MINOR_HORIZONTAL_GRIDS,button,1342242819
Control8=IDC_PS_MAJOR_VERTICAL_GRIDS,button,1342242819
Control9=IDC_MINOR_VERTICAL_GRIDS,button,1342242819
Control10=IDC_STATIC,static,1342308352
Control11=IDC_PS_COLOR_MAJOR_GRIDS,colorcontrol,1342242816
Control12=IDC_STATIC,static,1342308352
Control13=IDC_PS_COLOR_MINOR_GRIDS,colorcontrol,1342242816
Control14=IDC_STATIC,button,1342177287
Control15=IDC_STATIC,static,1342308352
Control16=IDC_PS_PLOT_TITLE,edit,1350631552
Control17=IDC_STATIC,static,1342308352
Control18=IDC_PS_TITLE_FONT,static,1342308352
Control19=IDC_PS_CHOOSE_TITLE_FONT,button,1342242816
Control20=IDC_STATIC,static,1342308352
Control21=IDC_PS_COLOR_TITLE_FONT,colorcontrol,1342242816
Control22=IDC_STATIC,button,1342177287
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_PS_COLOR_BACKGROUND,colorcontrol,1342242816
Control26=IDC_PS_COLOR_BORDER,colorcontrol,1342242816
Control27=IDC_PLOT_TO_SIZE,button,1342242819
Control28=IDC_MAINTAIN_ASPECT_RATIO,button,1342242819
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATIC,static,1342308352
Control31=IDC_STATIC,static,1342308352
Control32=IDC_MAJOR_GRID_SIZE,edit,1350631552
Control33=IDC_MINOR_GRID_SIZE,edit,1350631552

