; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CBarCodeView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "BarCode.h"
LastPage=0

ClassCount=6
Class1=CBarCodeApp
Class2=CBarCodeDoc
Class3=CBarCodeView
Class4=CMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Class5=CAboutDlg
Class6=CDLGBW
Resource3=IDD_BW

[CLS:CBarCodeApp]
Type=0
HeaderFile=BarCode.h
ImplementationFile=BarCode.cpp
Filter=N

[CLS:CBarCodeDoc]
Type=0
HeaderFile=BarCodeDoc.h
ImplementationFile=BarCodeDoc.cpp
Filter=N

[CLS:CBarCodeView]
Type=0
HeaderFile=BarCodeView.h
ImplementationFile=BarCodeView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=IDC_PIC_QZ


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=IDC_PIC_CUT
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=BarCode.cpp
ImplementationFile=BarCode.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=11
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN
Command2=ID_FILE_MRU_FILE1
Command3=ID_APP_EXIT
Command4=ID_VIEW_TOOLBAR
Command5=ID_VIEW_STATUS_BAR
Command6=IDC_PIC_CUT
Command7=IDC_PIC_GRAY
Command8=IDC_PIC_BW
Command9=IDC_PIC_QZ
Command10=IDC_PIC_SB
Command11=IDC_PIC_PRE
Command12=ID_APP_ABOUT
CommandCount=12

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
Class=?
Command1=ID_FILE_OPEN
Command2=IDC_PIC_CUT
Command3=IDC_PIC_GRAY
Command4=IDC_PIC_BW
Command5=IDC_PIC_QZ
Command6=IDC_PIC_SB
Command7=IDC_PIC_PRE
Command8=ID_APP_ABOUT
CommandCount=8

[DLG:IDD_BW]
Type=1
Class=CDLGBW
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_BW,edit,1350631552

[CLS:CDLGBW]
Type=0
HeaderFile=DLGBW.h
ImplementationFile=DLGBW.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDLGBW

