; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFaceView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "face.h"
LastPage=0

ClassCount=5
Class1=CFaceApp
Class2=CFaceDoc
Class3=CFaceView
Class4=CMainFrame

ResourceCount=2
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Resource2=IDD_ABOUTBOX

[CLS:CFaceApp]
Type=0
HeaderFile=face.h
ImplementationFile=face.cpp
Filter=N

[CLS:CFaceDoc]
Type=0
HeaderFile=faceDoc.h
ImplementationFile=faceDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CFaceDoc

[CLS:CFaceView]
Type=0
HeaderFile=faceView.h
ImplementationFile=faceView.cpp
Filter=C
LastObject=ID_DELETE_FALSE_AREA
BaseClass=CScrollView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_LIGHTINGCONPENSATE




[CLS:CAboutDlg]
Type=0
HeaderFile=face.cpp
ImplementationFile=face.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
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
Command16=ID_APP_ABOUT
Command17=ID_LIGHTINGCONPENSATE
Command18=ID_SKINTONE
Command19=ID_DILATION_FIRST
Command20=ID_ERASION
Command21=ID_DELETE_FALSE_AREA
Command22=ID_DILATION
Command23=ID_ERASION_AGAIN
Command24=ID_GET_FACE_AREA
Command25=ID_EYE_Cr
Command26=ID_EYE_CB
Command27=ID_EYEMAPC
Command28=ID_EYEMAPL
Command29=ID_EYEMAP
Command30=ID_DELETE_FALSE_EYE
Command31=ID_DILATION_EYE
Command32=ID_EYE_CENTER
Command33=ID_MOUSEMAP
Command34=ID_ERASION_MOUSE
Command35=ID_DELETESCATER
Command36=ID_MOUTH_CENTER
Command37=ID_GOULE_FACE
CommandCount=37

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
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

