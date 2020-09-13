; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPalmView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Palm.h"
LastPage=0

ClassCount=5
Class1=CPalmApp
Class2=CPalmDoc
Class3=CPalmView
Class4=CMainFrame

ResourceCount=2
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Resource2=IDD_ABOUTBOX

[CLS:CPalmApp]
Type=0
HeaderFile=Palm.h
ImplementationFile=Palm.cpp
Filter=N
LastObject=CPalmApp

[CLS:CPalmDoc]
Type=0
HeaderFile=PalmDoc.h
ImplementationFile=PalmDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CPalmDoc

[CLS:CPalmView]
Type=0
HeaderFile=PalmView.h
ImplementationFile=PalmView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CPalmView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=ID_ROI_PRO




[CLS:CAboutDlg]
Type=0
HeaderFile=Palm.cpp
ImplementationFile=Palm.cpp
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
Command10=ID_Gray
Command11=ID_Big
Command12=ID_Small
Command13=ID_Up
Command14=ID_down
Command15=ID_left
Command16=ID_right
Command17=ID_Front
Command18=ID_Back
Command19=ID_ImToBool
Command20=ID_VIEW_TOOLBAR
Command21=ID_VIEW_STATUS_BAR
Command22=ID_WaveLet
Command23=ID_ReWaveLet
Command24=ID_HARRIS
Command25=ID_Sobel_H
Command26=ID_Sobel_V
Command27=ID_Total
Command28=ID_Robert_H
Command29=ID_Rorber_V
Command30=ID_Prewiit_H
Command31=ID_Prewiit_V
Command32=ID_IsotropicSobel_H
Command33=ID_IsotropicSobel_V
Command34=ID_THIN
Command35=ID_MENUITEM32773
Command36=ID_Gaosi
Command37=ID_Average
Command38=ID_Alog
Command39=ID_Palm_Cur
Command40=ID_PalmBig
Command41=ID_PalmROI
Command42=ID_ROI_PRO
Command43=ID_ROISave
CommandCount=43

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

