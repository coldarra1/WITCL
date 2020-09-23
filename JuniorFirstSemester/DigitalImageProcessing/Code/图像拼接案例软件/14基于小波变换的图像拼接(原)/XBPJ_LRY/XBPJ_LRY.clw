; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CWaveletPJDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "XBPJ_LRY.h"
LastPage=0

ClassCount=7
Class1=CXBPJ_LRYApp
Class2=CXBPJ_LRYDoc
Class3=CXBPJ_LRYView
Class4=CMainFrame

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Class6=CWavelet
Resource3=IDD_DIALOG1
Class7=CWaveletPJDlg
Resource4=IDD_DIALOG2

[CLS:CXBPJ_LRYApp]
Type=0
HeaderFile=XBPJ_LRY.h
ImplementationFile=XBPJ_LRY.cpp
Filter=N

[CLS:CXBPJ_LRYDoc]
Type=0
HeaderFile=XBPJ_LRYDoc.h
ImplementationFile=XBPJ_LRYDoc.cpp
Filter=N

[CLS:CXBPJ_LRYView]
Type=0
HeaderFile=XBPJ_LRYView.h
ImplementationFile=XBPJ_LRYView.cpp
Filter=C
BaseClass=CScrollView
VirtualFilter=VWC
LastObject=ID_waveletPJ


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=ID_waveletPJ




[CLS:CAboutDlg]
Type=0
HeaderFile=XBPJ_LRY.cpp
ImplementationFile=XBPJ_LRY.cpp
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
Command10=ID_APP_ABOUT
Command11=ID_wavelet
Command12=ID_waveletPJ
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

[DLG:IDD_DIALOG1]
Type=1
Class=CWavelet
ControlCount=6
Control1=IDC_openimg,button,1342242816
Control2=IDC_waveletfj,button,1342242816
Control3=IDC_waveletcg,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT1,edit,1350631552
Control6=IDC_BUTTON1,button,1342242816

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

[CLS:CWavelet]
Type=0
HeaderFile=Wavelet.h
ImplementationFile=Wavelet.cpp
BaseClass=CDialog
Filter=D
LastObject=CWavelet
VirtualFilter=dWC

[DLG:IDD_DIALOG2]
Type=1
Class=CWaveletPJDlg
ControlCount=9
Control1=IDC_OpenImage1,button,1342242816
Control2=IDC_OpenImage2,button,1342242816
Control3=IDC_Img1WaveletTran,button,1342242816
Control4=IDC_Img2WaveletTran,button,1342242816
Control5=IDC_WaveletPJ,button,1342242816
Control6=IDC_ReConstruct,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT2,edit,1350631552
Control9=IDC_BUTTON2,button,1342242816

[CLS:CWaveletPJDlg]
Type=0
HeaderFile=WaveletPJDlg.h
ImplementationFile=WaveletPJDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CWaveletPJDlg
VirtualFilter=dWC

