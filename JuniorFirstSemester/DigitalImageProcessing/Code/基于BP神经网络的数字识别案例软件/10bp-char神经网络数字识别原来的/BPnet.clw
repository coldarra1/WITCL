; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CChildView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "BPnet.h"
LastPage=0

ClassCount=4
Class1=CBPnetApp
Class3=CMainFrame
Class4=CAboutDlg

ResourceCount=9
Resource1=IDD_ABOUTBOX
Resource2=IDD_PROPPAGE_MEDIUM (English (U.S.))
Class2=CChildView
Resource8=IDR_MAINFRAME
Resource9=IDR_MAINFRAME (English (U.S.))

[CLS:CBPnetApp]
Type=0
HeaderFile=BPnet.h
ImplementationFile=BPnet.cpp
Filter=N

[CLS:CChildView]
Type=0
HeaderFile=ChildView.h
ImplementationFile=ChildView.cpp
Filter=N
BaseClass=CWnd 
VirtualFilter=WC
LastObject=ID_SAVEWEIGHT

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_DISP_SAMPLES




[CLS:CAboutDlg]
Type=0
HeaderFile=BPnet.cpp
ImplementationFile=BPnet.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=?
ControlCount=6
Control1=IDC_STATIC,static,1342308480
Control2=IDC_STATIC,static,1342308352
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_SAVEERROR
Command2=ID_SAVEWEIGHT
Command3=ID_APP_EXIT
Command4=ID_DISP_SAMPLES
Command5=ID_PREWB
Command6=ID_BPN_TRAIN
Command7=ID_BPTRAIN_Optimal1
Command8=ID_DRAW_ERROR
Command9=ID_BPN_Verify
Command10=ID_BPN_RUN
Command11=ID_APP_ABOUT
CommandCount=11

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
CommandCount=13
Command4=ID_EDIT_UNDO
Command13=ID_PREV_PANE


[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_CUT
Command2=ID_EDIT_COPY
Command3=ID_EDIT_PASTE
Command4=ID_FILE_PRINT
Command5=ID_APP_ABOUT
CommandCount=5

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_APP_EXIT
Command2=ID_EDIT_UNDO
Command3=ID_EDIT_CUT
Command4=ID_EDIT_COPY
Command5=ID_EDIT_PASTE
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_EDIT_PASTE
Command3=ID_EDIT_UNDO
Command4=ID_EDIT_CUT
Command5=ID_NEXT_PANE
Command6=ID_PREV_PANE
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_CUT
Command10=ID_EDIT_UNDO
CommandCount=10

[DLG:IDD_PROPPAGE_MEDIUM (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342308352

