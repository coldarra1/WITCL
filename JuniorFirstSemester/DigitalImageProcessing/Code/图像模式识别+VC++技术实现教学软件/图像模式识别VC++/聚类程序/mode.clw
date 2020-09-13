; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CModeView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "mode.h"
LastPage=0

ClassCount=9
Class1=CModeApp
Class2=CModeDoc
Class3=CModeView
Class4=CMainFrame

ResourceCount=7
Resource1=IDD_ABOUTBOX
Resource2=IDR_MINEICON
Class5=CAboutDlg
Class6=CModeViewRight
Resource3=IDD_DIALOG_INFOR
Resource4=IDR_NUMBER
Class7=DlgInfor
Resource5=IDD_DIALOG_MOHU
Class8=DlgMohu
Resource6=IDR_MAINFRAME
Class9=DlgFuzzyDistance
Resource7=IDD_FUZZYDIATANCE

[CLS:CModeApp]
Type=0
HeaderFile=mode.h
ImplementationFile=mode.cpp
Filter=N
LastObject=ID_USEGUIDE
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CModeDoc]
Type=0
HeaderFile=modeDoc.h
ImplementationFile=modeDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CModeDoc

[CLS:CModeView]
Type=0
HeaderFile=modeView.h
ImplementationFile=modeView.cpp
Filter=C
LastObject=ID_FILENEW
BaseClass=CView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=ID_PEN




[CLS:CAboutDlg]
Type=0
HeaderFile=mode.cpp
ImplementationFile=mode.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=3
Control1=IDC_STATIC,static,1342308480
Control2=IDC_STATIC,static,1342308352
Control3=IDOK,button,1342373889

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
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

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILENEW
Command2=ID_PEN
Command3=ID_ERASER
Command4=ID_FILEOPEN
Command5=ID_SHOWRIGHT
CommandCount=5

[CLS:CModeViewRight]
Type=0
HeaderFile=ModeViewRight.h
ImplementationFile=ModeViewRight.cpp
BaseClass=CView
Filter=C
VirtualFilter=VWC
LastObject=CModeViewRight

[TB:IDR_NUMBER]
Type=1
Class=?
Command1=ID_1
Command2=ID_2
Command3=ID_3
Command4=ID_4
Command5=ID_5
Command6=ID_6
Command7=ID_7
Command8=ID_8
Command9=ID_9
Command10=ID_0
CommandCount=10

[MNU:IDR_MINEICON]
Type=1
Class=CMainFrame
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
Command16=ID_GETFEATURE
Command17=ID_STANDARDNUM
Command18=ID_ZUILINJINGUIZE
Command19=ID_ZUIDAZUIXIAOJULI
Command20=ID_ZUIDUANJULIFA
Command21=ID_ZUICHANGJULIFA
Command22=ID_ZHONGJINAJULIFA
Command23=ID_ZHONGXINFA
Command24=ID_LEIPINGJUNJULIFA
Command25=ID_KJUNZHI
Command26=ID_ISODATA
Command27=ID_GA
Command28=ID_APP_ABOUT
Command29=ID_USEGUIDE
CommandCount=29

[DLG:IDD_DIALOG_INFOR]
Type=1
Class=DlgInfor
ControlCount=24
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC1,button,1342177287
Control4=IDC_RADIO_OUS,button,1342308361
Control5=IDC_RADIO_COS,button,1342177289
Control6=IDC_RADIO_BCOS,button,1342177289
Control7=IDC_RADIO_TAN,button,1342177289
Control8=IDC_STATIC2,button,1342177287
Control9=IDC_EDIT_T,edit,1350631552
Control10=IDC_STATIC4,static,1342308352
Control11=IDC_STATIC9,static,1342308352
Control12=IDC_EDIT_CENTERNUM,edit,1350631552
Control13=IDC_STATIC7,static,1342308352
Control14=IDC_EDIT_EQUATIONIN,edit,1350631552
Control15=IDC_STATIC10,static,1342308352
Control16=IDC_EDIT_TIMES,edit,1350631552
Control17=IDC_STATIC3,static,1342308352
Control18=IDC_STATIC5,static,1342308352
Control19=IDC_STATIC6,static,1342308352
Control20=IDC_EDIT_MINDIS,edit,1476460672
Control21=IDC_EDIT_MAXDIS,edit,1476460672
Control22=IDC_EDIT_MINEQUATIONOUT,edit,1476460672
Control23=IDC_STATIC8,static,1342308352
Control24=IDC_EDIT_MAXEQUATIONOUT,edit,1476460672

[CLS:DlgInfor]
Type=0
HeaderFile=DlgInfor.h
ImplementationFile=DlgInfor.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT_CENTERNUM
VirtualFilter=dWC

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT
Command4=ID_FILE_PRINT_PREVIEW
Command5=ID_FILE_PRINT_SETUP
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_VIEW_TOOLBAR
Command13=ID_VIEW_STATUS_BAR
Command14=ID_GETFEATURE
Command15=ID_STANDARDNUM
Command16=ID_ZUILINJINGUIZE
Command17=ID_ZUIDAZUIXIAOJULI
Command18=ID_ZUIDUANJULIFA
Command19=ID_ZUICHANGJULIFA
Command20=ID_ZHONGJINAJULIFA
Command21=ID_ZHONGXINFA
Command22=ID_LEIPINGJUNJULIFA
Command23=ID_KJUNZHI
Command24=ID_ISODATA
Command25=ID_FUZZYCLUSTER
Command26=ID_GA
Command27=ID_APP_ABOUT
Command28=ID_HELP
CommandCount=28

[DLG:IDD_DIALOG_MOHU]
Type=1
Class=DlgMohu
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_MOHUXISHU,edit,1350633601
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_MOHUYUZHI,edit,1350631552
Control7=IDC_STATIC,static,1342308352

[CLS:DlgMohu]
Type=0
HeaderFile=DlgMohu.h
ImplementationFile=DlgMohu.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=DlgMohu

[CLS:DlgFuzzyDistance]
Type=0
HeaderFile=DlgFuzzyDistance.h
ImplementationFile=DlgFuzzyDistance.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_RADIO6
VirtualFilter=dWC

[DLG:IDD_FUZZYDIATANCE]
Type=1
Class=DlgFuzzyDistance
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_RADIO1,button,1342177289
Control4=IDC_RADIO2,button,1342177289
Control5=IDC_RADIO3,button,1342177289
Control6=IDC_RADIO4,button,1342177289
Control7=IDC_RADIO5,button,1342177289
Control8=IDC_RADIO6,button,1342177289

