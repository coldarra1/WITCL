; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CChildView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DigitRec.h"
LastPage=0

ClassCount=6
Class1=CDigitRecApp
Class3=CMainFrame
Class4=CAboutDlg

ResourceCount=5
Resource1=IDD_DIALOG2
Resource2=IDD_DIALOG1
Class2=CChildView
Resource3=IDD_ABOUTBOX
Class5=CINPUT1
Resource4=IDR_MAINFRAME
Class6=CDBpParamater
Resource5=IDR_MAINFRAME (English (U.S.))

[CLS:CDigitRecApp]
Type=0
HeaderFile=DigitRec.h
ImplementationFile=DigitRec.cpp
Filter=N

[CLS:CChildView]
Type=0
HeaderFile=ChildView.h
ImplementationFile=ChildView.cpp
Filter=N
LastObject=IDmy_IMGPRC_EQUALIZE
BaseClass=CWnd 
VirtualFilter=WC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_Mid
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=DigitRec.cpp
ImplementationFile=DigitRec.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=IDmy_FILE_OPEN_BMP
Command2=IDmy_FILE_SAVE_BMP
Command3=IDmy_FILE_RE_LOAD_BMP
Command4=ID_APP_EXIT
Command5=ID_INPUT1
Command6=IDmy_IMGPRC_ALL
Command7=IDmy_IMGPRC_256ToGray
Command8=IDmy_IMGPRC_GrayToWhiteBlack
Command9=IDmy_IMGPRC_SHARP
Command10=IDmy_IMGPRC_REMOVE_NOISE
Command11=IDmy_IMGPRC_ADJUST_SLOPE
Command12=IDmy_IMGPRC_DIVIDE
Command13=IDmy_IMGPRC_STANDARIZE
Command14=IDmy_IMGPRC_SHRINK_ALIGN
Command15=IDmy_IMGPRC_TO_DIB_AND_SAVE
Command16=IDmy_BPNET_TRAIN
Command17=IDmy_BPNET_RECOGNIZE
Command18=ID_APP_ABOUT
Command19=IDmy_IMGPRC_THINNING
Command20=ID_aver
Command21=ID_Gass
Command22=ID_Mid
Command23=IDmy_IMGPRC_EQUALIZE
CommandCount=23

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

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=IDmy_FILE_OPEN_BMP
Command2=IDmy_FILE_SAVE_BMP
Command3=IDmy_FILE_RE_LOAD_BMP
Command4=IDmy_BPNET_TRAIN
Command5=IDmy_BPNET_RECOGNIZE
CommandCount=5

[DLG:IDD_DIALOG1]
Type=1
Class=CINPUT1
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_EDIT2,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[CLS:CINPUT1]
Type=0
HeaderFile=INPUT1.h
ImplementationFile=INPUT1.cpp
BaseClass=CDialog
Filter=D
LastObject=CINPUT1
VirtualFilter=dWC

[DLG:IDD_DIALOG2]
Type=1
Class=CDBpParamater
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDC_n_hidden,edit,1350631552
Control3=IDC_eta,edit,1350631552
Control4=IDC_ex,edit,1350631552
Control5=IDC_a,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352

[CLS:CDBpParamater]
Type=0
HeaderFile=DBpParamater.h
ImplementationFile=DBpParamater.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_ex

