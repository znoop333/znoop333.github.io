; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCPlotView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "cplotresources.h"
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
Resource1=IDD_XY_SETTINGS (English (U.S.))
Resource2=IDD_IMAGE_SETTINGS (English (U.S.))
Resource3=IDD_AXIS_SETTINGS
Resource4=IDD_DATA_SETTINGS

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
LastObject=CCPlotView

[CLS:CDataSettingsDialog]
Type=0
BaseClass=CDialog
HeaderFile=DataSettingsDialog.h
ImplementationFile=DataSettingsDialog.cpp
LastObject=IDC_DATA_LINESTYLE
Filter=D
VirtualFilter=dWC

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

[DLG:IDD_AXIS_SETTINGS]
Type=1
Class=CAxisSettings
ControlCount=37
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_AXIS_PREVIOUS,button,1342242816
Control4=IDC_AXIS_NEXT,button,1342242816
Control5=IDC_AXIS_LABEL,button,1342177287
Control6=IDC_STATIC,button,1342177287
Control7=IDC_AS_XRANGE_LOW,edit,1350631552
Control8=IDC_AS_XRANGE_HIGH,edit,1350631552
Control9=IDC_STATIC,static,1342308353
Control10=IDC_AS_AUTO_XRANGE,button,1342242819
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_NUMBER_MAJOR_TICKS,edit,1350631552
Control15=IDC_AS_NUMBER_MINOR_TICKS,edit,1350631552
Control16=IDC_AS_AUTO_MAJOR_TICKS,button,1342242819
Control17=IDC_AS_AUTO_MINOR_TICKS,button,1342242819
Control18=IDC_STATIC,button,1342177287
Control19=IDC_STATIC,static,1342308352
Control20=IDC_AS_PLOT_TITLE,edit,1350631552
Control21=IDC_STATIC,static,1342308352
Control22=IDC_PS_TITLE_FONT,static,1342308352
Control23=IDC_AS_CHOOSE_TITLE_FONT,button,1342242816
Control24=IDC_STATIC,static,1342308352
Control25=IDC_AS_COLOR_TITLE_FONT,colorcontrol,1342242816
Control26=IDC_AS_COLOR_LINE,colorcontrol,1342242816
Control27=IDC_STATIC,static,1342308352
Control28=IDC_AS_MAJOR_TICK_LENGTH,edit,1350631552
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATIC,static,1342308352
Control31=IDC_AS_MINOR_TICK_LENGTH,edit,1350631552
Control32=IDC_STATIC,static,1342308352
Control33=IDC_STATIC,button,1342177287
Control34=IDC_STATIC,static,1342308352
Control35=IDC_AS_LABEL_FONT,static,1342308352
Control36=IDC_AS_CHOOSE_LABEL_FONT,button,1342242816
Control37=IDC_STATIC,static,1342308352

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[DLG:IDD_DATA_SETTINGS]
Type=1
Class=CDataSettingsDialog
ControlCount=32
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_DATA_PREVIOUS,button,1342242816
Control4=IDC_DATA_NEXT,button,1342242816
Control5=IDC_DATASET_LABEL,button,1342177287
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC,button,1342177287
Control8=IDC_STATIC,static,1342308352
Control9=IDC_DS_DATA_TITLE,edit,1350631552
Control10=IDC_DS_COLOR_LINE,colorcontrol,1342242816
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,button,1342177287
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_MARKER_SIZE,edit,1350631552
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_MARKER_FREQUENCY_EVERY,button,1342177289
Control20=IDC_MARKER_FREQUENCY_NTH,button,1342177289
Control21=IDC_MARKER_FREQUENCY_NUMBER,edit,1350631552
Control22=IDC_STATIC,static,1342308352
Control23=IDC_MARKER_FREQUENCY_TOTAL,button,1342177289
Control24=IDC_MARKER_FREQUENCY_TOTAL_DATA,edit,1350631552
Control25=IDC_STATIC,static,1342308352
Control26=IDC_MARKER_SHAPE,combobox,1344339971
Control27=IDC_CHART_TYPE,combobox,1344339971
Control28=IDC_STATIC,static,1342308352
Control29=IDC_DATA_LINE_SIZE,edit,1350631552
Control30=IDC_DATA_MARKER_FILL,button,1342242819
Control31=IDC_STATIC,static,1342308352
Control32=IDC_DATA_LINESTYLE,combobox,1344339971

[DLG:IDD_IMAGE_SETTINGS]
Type=1
Class=CImagePlotSettingsDialog

[DLG:IDD_XY_SETTINGS]
Type=1
Class=CPlotSettingsDialog

[DLG:IDD_IMAGE_SETTINGS (English (U.S.))]
Type=1
Class=CImagePlotSettingsDialog
ControlCount=37
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
Control34=IDC_STATIC,static,1342308352
Control35=IDC_PLOT_MAJOR_LINESTYLE,combobox,1344339971
Control36=IDC_STATIC,static,1342308352
Control37=IDC_PLOT_MINOR_LINESTYLE,combobox,1344339971

[DLG:IDD_XY_SETTINGS (English (U.S.))]
Type=1
Class=CPlotSettingsDialog
ControlCount=44
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
Control41=IDC_STATIC,static,1342308352
Control42=IDC_PLOT_MAJOR_LINESTYLE,combobox,1344339971
Control43=IDC_STATIC,static,1342308352
Control44=IDC_PLOT_MINOR_LINESTYLE,combobox,1344339971

