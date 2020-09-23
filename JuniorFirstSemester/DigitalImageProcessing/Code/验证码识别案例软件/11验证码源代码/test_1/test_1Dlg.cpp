// test_1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "test_1.h"
#include "test_1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString saveFilename("temp.bmp");
CString filename("");

#include "Lib/JpegToBmpLib.h"
#include "Lib/JpegToBmp.h"
#pragma comment(lib, "Lib/JpegToBmp.lib")
/////////////////////////////////////////////////////////////////////////////
// CTest_1Dlg dialog

CTest_1Dlg::CTest_1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTest_1Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTest_1Dlg)
	m_result = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTest_1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTest_1Dlg)
	DDX_Text(pDX, IDC_EDIT1, m_result);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTest_1Dlg, CDialog)
	//{{AFX_MSG_MAP(CTest_1Dlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnRead)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTest_1Dlg message handlers

BOOL CTest_1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically  设置此对话框的图标。该框架自动执行
	//  when the application's main window is not a dialog     当应用程序的主窗口不是对话框
	SetIcon(m_hIcon, TRUE);			// Set big icon   设置大图标
	SetIcon(m_hIcon, FALSE);		// Set small icon   设置小图标
	 
	// TODO: Add extra initialization here     在此添加额外的初始化
	
	return TRUE;  // return TRUE  unless you set the focus to a control   返回TRUE，除非你将焦点设置到控件
}

// If you add a minimize button to your dialog, you will need the code below    如果你的对话框添加最小化按钮，你将需要下面的代码
//  to draw the icon.  For MFC applications using the document/view model,      来绘制该图标。对于使用文档/视图模型的MFC应用程序，
//  this is automatically done for you by the framework.                         这是自动为你做的框架。

void CTest_1Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting  涂装设备上下文

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle    在客户端矩形的中心图标
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
  
		// Draw the icon     绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		InitBmp();
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags    当用户拖动系统调用此函数取得光标显示
//  the minimized window.   最小化窗口
HCURSOR CTest_1Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTest_1Dlg::OnRead() 
{   
	CFileDialog fg(TRUE);
	if(IDOK==fg.DoModal())
	{
       filename=fg.GetPathName();
	}
	HWND hPic=GetDlgItem(IDC_STATIC)->m_hWnd;
	HDC hPicDc=::GetWindowDC(hPic);
	RGBTRIPLE *rgb=NULL;
//    CString filename = "2489.jpg";   CString的文件名=“2489.jpg”;
	saveFilename = _T("temp.bmp");
	BITMAPFILEHEADER filehead;
	BITMAPINFOHEADER fileinfo;
	JpegToBmp(filename, saveFilename);
	InitBmp();
    CFile ff(saveFilename,CFile::modeReadWrite);
	ff.Read(&filehead,sizeof(filehead));
	ff.Read(&fileinfo,sizeof(fileinfo));
	rgb = new RGBTRIPLE[fileinfo.biWidth*fileinfo.biHeight];
	ff.Read(rgb,fileinfo.biWidth*fileinfo.biHeight*3);
	//黑白处理
	for (int i=0; i<fileinfo.biHeight;i++)
	{
		for (int j=0; j<fileinfo.biWidth; j++)
		{   
  
			if((rgb[i*fileinfo.biWidth+j].rgbtRed +rgb[i*fileinfo.biWidth+j].rgbtGreen + rgb[i*fileinfo.biWidth+j].rgbtBlue)/3<=140)
			{
              rgb[i*fileinfo.biWidth+j].rgbtBlue=0;
			  rgb[i*fileinfo.biWidth+j].rgbtGreen=0;
              rgb[i*fileinfo.biWidth+j].rgbtRed=0;
			}
			else
			{
              rgb[i*fileinfo.biWidth+j].rgbtBlue=255;
			  rgb[i*fileinfo.biWidth+j].rgbtGreen=255;
              rgb[i*fileinfo.biWidth+j].rgbtRed=255;
			}
            ff.Seek(54,CFile::begin);
			ff.Write(rgb,sizeof(RGBTRIPLE)*fileinfo.biWidth*fileinfo.biHeight);
		}
	}
	ff.Close();
	InitBmp();
	//开始识别
	int Num1[4]={0};    //下行结果存储
	int Num2[4]={0};    //上行结果存储
	int Num[4]={0};     //存储最终结果 
	int Num3[4]={0};    //区别5和8的标记
	int count=0;       //计数器

	int m=4;                                        //从0开始的
    int x=0;
	int y=0;
	
	for (int n=7; n<fileinfo.biWidth;n++)           //下面一行
	{
		if(rgb[m*fileinfo.biWidth+n].rgbtRed==0 && y<3)
		{
			x=x+1; 
		}
		else
		{
			if(x >=2)
			{
				while(Num1[y]!=0)
				{
					y=y+1;
				}
				Num1[y]=x;
				x=0;
			}
		}
	}
	
    m=fileinfo.biHeight-4;                     //上面一行
    x=0;
	y=0;
	for (int a=7; a<fileinfo.biWidth;a++)                    
	{
		if(rgb[m*fileinfo.biWidth+a].rgbtRed==0 && y<3)
		{
			x=x+1; 
		}
		else
		{  
			if(x >=2)
			{
				while(Num3[y]!=0)
				{
					y=y+1;
				}
				Num3[y]=x;
				x=0;
			}
		}
	}
	
	m=fileinfo.biHeight-5;
    x=0;
	y=0;
	
	for (int c=7; c<fileinfo.biWidth;c++)          //中间一行
	{
		if(rgb[m*fileinfo.biWidth+c].rgbtRed==0 && y<3)
		{
			x=x+1; 
		}
		else
		{  
			if(x >=2)
			{
				while(Num2[y]!=0)
				{
					y=y+1;
				}	
				Num2[y]=x;
				x=0;
			}
		}
	}
	
	for(int z=0;z<4;z++)
	{
		if(Num1[z]==3 &&Num3[z]==3)
		{
          Num[z]=0;
		}
        if(Num1[z]==8 &&Num3[z]==3)
		{
          Num[z]=1;
		}
		if(Num1[z]==8 && Num3[z]==5)
		{
          Num[z]=2;
		}
		if(Num1[z]==5 &&Num3[z]==5 && Num2[z]==8)
		{
          Num[z]=3;
		}
		if(Num1[z]==2 &&Num3[z]==2)
		{
          Num[z]=4;
		}
		if(Num1[z]==5 && Num3[z]==8 )
		{
          Num[z]=5;
		}
		if(Num1[z]==4 &&Num3[z]==4 && Num2[z]==6)
		{
          Num[z]=6;
		}
		if(Num1[z]==2 &&Num3[z]==8)
		{
          Num[z]=7;
		}
		if(Num1[z]==5 &&Num3[z]==5 && Num2[z]==7)
		{
          Num[z]=8;
		}
		if(Num1[z]==4 && Num3[z]==4 &&Num2[z]==7)
		{
          Num[z]=9;
		}
	}
	::DeleteFile("temp.bmp");
	CString msg;
	msg.Format("%d%d%d%d",Num[0],Num[1],Num[2],Num[3]);
	MessageBox(msg);

}

int CTest_1Dlg::InitBmp()
{
    HWND hPic=GetDlgItem(IDC_STATIC)->m_hWnd;
	RECT rt;
	::GetClientRect(hPic,&rt);
	HDC hPicDc=::GetWindowDC(hPic);
	HDC hMemDC=CreateCompatibleDC(hPicDc);
	HBITMAP hbitmap=(HBITMAP)LoadImage(GetModuleHandle(NULL),saveFilename,IMAGE_BITMAP,0,0,LR_LOADFROMFILE | LR_CREATEDIBSECTION );
    HBITMAP hOld=(HBITMAP)::SelectObject(hMemDC,hbitmap);
    ::StretchBlt(hPicDc,0,0,rt.right-rt.left,rt.bottom-rt.top,hMemDC,0,0,60,20,SRCCOPY);
    ::SelectObject(hMemDC,hOld);
	::ReleaseDC(hPic,hPicDc);
	return 0;
}
