// DSplit.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "DSplit.h"

#include "MainFrm.h"
#include "DSplitDoc.h"
#include "DSplitView.h"
#include "DynSplitView2.h"

#include "CDib.h"
#include "math.h"
#include "stdlib.h"
#include "stdio.h"
#include <vector>




#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;
/////////////////////////////////////////////////////////////////////////////
// CDSplitApp

BEGIN_MESSAGE_MAP(CDSplitApp, CWinApp)
	//{{AFX_MSG_MAP(CDSplitApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDSplitApp construction

CDSplitApp::CDSplitApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDSplitApp object

CDSplitApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDSplitApp initialization

BOOL CDSplitApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CDSplitDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CDSplitView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CDSplitApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CDSplitApp commands
// FingerprintDlg.cpp : implementation file
//


////////////////////////////////////////////////////////////////////////////
//数据类型定义：
/* Basic Types */
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef short sint16;
typedef unsigned long uint32;
typedef int sint32;
//typedef long sint32;
typedef char sint8;

typedef uint32 VF_RETURN;

typedef uint8  VF_FLAG;


#define VF_OK (0)
typedef struct tagMatchResult { 
	sint32    Similarity; 
	sint32    Rotation; 
	sint32    TransX;
	sint32    TransY;
	sint32	MMCount;
} MATCHRESULT, *PMATCHRESULT; 


#define VF_MINUTIA_END        1	// 端点
#define VF_MINUTIA_FORK       2	// 叉点
#define VF_MINUTIA_CORE		  3 //中心点
#define VF_MINUTIA_DELTA	  4 //三角点

// 精确比对模式，主要用在少量比对次数场合
#define	VF_MATCHMODE_VERIFY			1
// 快速比对模式，主要用在大量比对次数场合
#define	VF_MATCHMODE_IDENTIFY		2

////////////////////////////////////////////////////////
#define		MAXIMGW				640		// 处理图像最大宽度
#define		MAXIMGH				480		// 处理图像最大高度
#define		MAXIMGSIZE			(MAXIMGW*MAXIMGH) // 处理图像最大大小

sint32  	IMGW = 256;		// 当前处理图像的宽度
sint32      IMGH = 360;		// 当前处理图像的高度
sint32      IMGSIZE = (IMGW*IMGH);	// 当前处理图像的大小


uint8		g_OrgFinger[MAXIMGSIZE];	// 处理图像数据缓冲区
uint8		g_Orient[MAXIMGSIZE];		// 方向场数据缓冲区
uint8		g_Divide[MAXIMGSIZE];		// 分割图数据缓冲区
uint8		g_Temp[MAXIMGSIZE];			// 临时数据缓冲区

uint8		*g_lpOrgFinger = &g_OrgFinger[0];	// 处理图像数据缓冲区首地址
uint8		*g_lpOrient = &g_Orient[0];			// 方向场数据缓冲区首地址
uint8		*g_lpDivide = &g_Divide[0];			// 分割图数据缓冲区首地址
uint8		*g_lpTemp = &g_Temp[0];				// 临时数据缓冲区首地址

#define     MAXMINUTIANUM			60			// 最大特征点数
#define     MAXRAWMINUTIANUM        100			// 包含虚假特征点的初始特征点最大数目

sint32      g_MinutiaNum = 0;					// 特征点数之和

#define  PI          3.141593
#define  EPI         57.29578

// 以某点为中心的12个量化方向上7个点位置的横纵偏移
sint32  g_DSite[12][7][2] = {
	-3, 0,  -2, 0,  -1, 0,   0, 0,   1, 0,   2, 0,   3, 0,
		-3,-1,  -2,-1,  -1, 0,   0, 0,   1, 0,   2, 1,   3, 1,
		-3,-2,  -2,-1,  -1,-1,   0, 0,   1, 1,   2, 1,   3, 2,
		-3,-3,  -2,-2,  -1,-1,   0, 0,   1, 1,   2, 2,   3, 3,
		-2,-3,  -1,-2,  -1,-1,   0, 0,   1, 1,   1, 2,   2, 3,
		-1,-3,  -1,-2,   0,-1,   0, 0,   0, 1,   1, 2,   1, 3,
		0,-3,   0,-2,   0,-1,   0, 0,   0, 1,   0, 2,   0, 3,
		-1, 3,  -1, 2,   0, 1,   0, 0,   0,-1,   1,-2,   1,-3,
		-2, 3,  -1, 2,  -1, 1,   0, 0,   1,-1,   1,-2,   2,-3,
		-3, 3,  -2, 2,  -1, 1,   0, 0,   1,-1,   2,-2,   3,-3,
		-3, 2,  -2, 1,  -1, 1,   0, 0,   1,-1,   2,-1,   3,-2,
		-3, 1,  -2, 1,  -1, 0,   0, 0,   1, 0,   2,-1,   3,-1
};

// 为节省时间，短距离的两点间距离采用查表法(用于对比匹配)
// DisTbl[m][n] = (int)(sqrt(m*m+n*n)+0.5)
sint32  DisTbl[10][10] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 
		1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 
		2, 2, 2, 3, 4, 5, 6, 7, 8, 9, 
		3, 3, 3, 4, 5, 5, 6, 7, 8, 9, 
		4, 4, 4, 5, 5, 6, 7, 8, 8, 9, 
		5, 5, 5, 5, 6, 7, 7, 8, 9, 10, 
		6, 6, 6, 6, 7, 7, 8, 9, 10, 10, 
		7, 7, 7, 7, 8, 8, 9, 9, 10, 11, 
		8, 8, 8, 8, 8, 9, 10, 10, 11, 12, 
		9, 9, 9, 9, 9, 10, 10, 11, 12, 12
};

// 特征点结构
typedef struct tagMinutiae { 
	sint32    x;				// 横坐标
	sint32    y;				// 纵坐标
	sint32    Direction;		// 方向
	sint32	Triangle[3];	// 特征点为中心外接圆半径为定值的正三角形三个顶点的方向
	sint32    Type;			// 类型
} MINUTIA, *MINUTIAPTR; 

// 指纹特征(模板)结构
typedef struct tagFeature{
	sint32		MinutiaNum;					// 特征点数
	MINUTIA		MinutiaArr[MAXMINUTIANUM];	// 特征点数组
} FEATURE, *FEATUREPTR;

FEATURE    g_Feature;		// 当前指纹的指纹特征

#define SAFE_FREE(x) { if (x != NULL) free((void *)x); x = NULL; }

#define WIDTHBYTES(i)    ((i+3)/4*4)
///////////////////////////////////////////////////////////////
typedef struct DblPont
{
	double x;
	double y;
}DBLPOINT;

/*
typedef struct tagPOINT
{
	long x;
	long y;

}POINT,*PPOINT,NEAR *NPPOINT,FAR *LPPOINT;
*/
#define	MAX_SINGULARYNUM	30
/////////////////////////////////////////////////////////////////
#define		VF_BASE_ERR		10000

#define     VF_LOADFINGER_ERR			(VF_BASE_ERR+100)
#define     VF_SAVEFINGER_ERR			(VF_BASE_ERR+200)
#define     VF_IMPORTFINGER_ERR			(VF_BASE_ERR+300)

#define     VF_PROCESS_ERR				(VF_BASE_ERR+400)
#define     VF_EXTRACT_ERR				(VF_BASE_ERR+500)
#define     VF_FEATUREENCODE_ERR		(VF_BASE_ERR+600)
#define     VF_FEATUREDECODE_ERR		(VF_BASE_ERR+700)
#define     VF_VERIFYMATCH_ERR			(VF_BASE_ERR+800)
#define     VF_SAVEFEATURE_ERR			(VF_BASE_ERR+900)
#define     VF_LOADFEATURE_ERR			(VF_BASE_ERR+1000)


#define SizeCDib 32
/////////////////////////////////////////////////////////////////////////////
//函数定义：
int FPA_CreateImage(LPVOID lpDib);
int FPA_LoadImage(CString filename, LPVOID lpDib, BYTE **lpData, int *lpWidth, int *lpHeight);
int FPA_AnalyzeFeature_File(CString FileName, BYTE *lpFeature, int *lpSize);
int AnalyzeFromFile(LPCSTR lpszFileName, BYTE *lpFeature, int *lpSize);
VF_RETURN	VF_LoadFinger(LPCSTR lpszFileName);
sint32	loadBitmap(sint8 *lpszFileName, uint8 *lpBitmap, sint32 *lpWidth, sint32 *lpHeight);
VF_RETURN	VF_Process();
void smooth(uint8 *lpInBuffer, uint8 *lpOutBuffer, sint32 r, sint32 d);
void zoomout();
void getOrientMap(sint32  r);
sint32	saveBitmap(uint8 *lpBitmap, sint32 Width, sint32 Height, sint8 *lpszFileName);
sint32 divide(sint32  r, sint32 threshold);
void orientFilter();
sint32  DIndex(sint32 angle);
sint32 binary();
void binaryClear();
void clearEdge();
sint32 thin();
sint32  thinClear(sint32  len);
sint32 imageThin(uint8 *lpBits, sint32 Width, sint32 Height);
bool   IsFork(uint8 *lpNow);
sint32  GetNext(uint8 *lpNow, uint8 *lpLast, uint8 **lppNext);
sint32  getMinutia();
bool   IsEnd(uint8 *lpNow);
sint32  PX(uint8 *lpPos);
sint32  PY(uint8 *lpPos);
sint32  GetJiajiao(sint32 angle1, sint32 angle2);
sint32  GetByDis(uint8 *lpEnd, uint8 **lppPos, sint32 d);
sint32  GetAngleDis(sint32 angleBegin, sint32 angleEnd);
sint32  GetAngle(sint32 x0, sint32 y0, sint32 x1, sint32 y1);
int getSingular(BYTE *lpOrient, int Width, int Height, char flag);
int getOriChange(int angle1, int angle2, char flag);
VF_RETURN VF_FeatureEncode(FEATUREPTR lpFeature, uint8 *lpData, sint32 *lpSize);
sint32	EncodeFeature(FEATUREPTR lpFeature, uint8 *lpData);
int FPA_PatternMatch(BYTE *lpFeature1, BYTE *lpFeature2, int *lpScore);
int PatternMatch(BYTE *lpFeature1, BYTE *lpFeature2, int *lpScore);
VF_RETURN VF_FeatureDecode(uint8 *lpData, FEATUREPTR lpFeature);
sint32	DecodeFeature(uint8 *lpData, FEATUREPTR lpFeature);
BOOL	VF_VerifyMatch(FEATUREPTR lpFeature1, FEATUREPTR lpFeature2,PMATCHRESULT lpMatchResult, VF_FLAG matchMode);
void	verify(FEATUREPTR lpFeature, FEATUREPTR lpTemplate, PMATCHRESULT lpMatchResult,VF_FLAG matchMode);
void  globalMatch(FEATUREPTR lpFeature, FEATUREPTR lpTemplate, PMATCHRESULT lpMatchResult, VF_FLAG matchMode);
void align(FEATUREPTR lpFeature, FEATUREPTR lpAlignedFeature, MINUTIAPTR lpFeatureCore,sint32 rotation, sint32 transx, sint32 transy);
void alignMatch(FEATUREPTR lpAlignFeature, FEATUREPTR lpTemplate, PMATCHRESULT lpMatchResult, VF_FLAG matchMode);
sint32  AngleAbs360(sint32 angle1, sint32 angle2);




/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

LPVOID lpImage1 = new BYTE[SizeCDib];
LPVOID lpImage2 = new BYTE[SizeCDib];

BYTE *lpData1;
BYTE *lpData2;

int Width1, Height1;
int Width2, Height2;

CString ImagePathName1, ImagePathName2;

BYTE lpFeature1[430];
BYTE lpFeature2[430];

 


////////////////////////////////////////////////////////////////
//自定义函数实现
int FPA_CreateImage(LPVOID lpDib)
{
	CDib dib;
	memcpy(lpDib, &dib, sizeof(CDib));
	
	return 0;
}



int FPA_LoadImage(CString filename, LPVOID lpDib, BYTE **lpData, int *lpWidth, int *lpHeight)
{
	CDib *dib = (CDib*)(lpDib);
	
	char *path = new char[filename.GetLength()];
	path = filename.GetBuffer(0);
	dib->Open(path);
	
	*lpData = dib->m_pDibBits;
	*lpWidth = dib->GetWidth();
	*lpHeight = dib->GetHeight();
	
	return 0;
}

int FPA_AnalyzeFeature_File(CString FileName, BYTE *lpFeature, int *lpSize)
{
	return AnalyzeFromFile((LPCSTR)FileName, lpFeature, lpSize);

}


//
// ExtractEx: 从指纹图像BMP文件中提取指纹特征
//
int AnalyzeFromFile(LPCSTR lpszFileName, BYTE *lpFeature, int *lpSize)
{
	//////////////////////////////////////////////////////////////////////////
	//  lpszFileName: [in] 指纹图像文件路径
	//  Resolution: [in] 指纹图像分辨率
	//  lpFeature: [out] 提取的指纹特征数据缓冲区指针
	//  lpSize: [out] 提取的指纹特征数据大小
	//////////////////////////////////////////////////////////////////////////
	// TODO: Add your implementation code here
	VF_RETURN	re;
	
	// 读取指纹图像数据
	re = VF_LoadFinger(lpszFileName);
	if(re != VF_OK)
		return re;
	
	// 处理指纹图像，提取指纹特征
	re = VF_Process();
	//if(re != VF_OK)
//		return re;
	  
	// 对指纹特征进行编码
	re = VF_FeatureEncode(&g_Feature, lpFeature, lpSize);
	if(re != VF_OK)
		return re;
	
	return 0;
}


VF_RETURN	VF_LoadFinger(LPCSTR lpszFileName)
{
	///////////////////////////////////////////////////////////////////////
	//	lpszFileName: [in] 指纹图像文件名
	///////////////////////////////////////////////////////////////////////
	sint32  bufferSize = 0;
	sint32  Width = 0;
	sint32  Height = 0;
	sint32  re;
	
	//	获取需要内存空间大小，分配内存
	re = loadBitmap((char *)lpszFileName, NULL, &Width, &Height);
	if(re != 0)
	{
		return VF_LOADFINGER_ERR;
	}
	
	if(Width > MAXIMGW || Height > MAXIMGH)
	{
		return VF_LOADFINGER_ERR;
	}
	//	读取数据到图像处理缓冲区
	re = loadBitmap((char *)lpszFileName, g_lpOrgFinger, &Width, &Height);
	if(re != 0)
	{
		return VF_LOADFINGER_ERR;
	}
	
	// 设置处理的图像大小
	IMGW = Width;
	IMGH = Height;
	IMGSIZE = (sint32)(IMGW * IMGH);
	
	return	VF_OK;
}



//
//	loadBitmap: 从BMP文件中读取图像数据
//
sint32	loadBitmap(sint8 *lpszFileName, uint8 *lpBitmap, sint32 *lpWidth, sint32 *lpHeight)
{
	/////////////////////////////////////////////////////////////////////
	//  lpszFileName: [in] BMP文件名
	//	lpBitmap: [out] 读出的图像数据
	//  lpWidth: [out] 图像宽度
	//	lpHeight: [out] 图像高度
	/////////////////////////////////////////////////////////////////////
   	FILE               *fp = NULL;
	uint8			   palatte[1024];
	BITMAPFILEHEADER   bf;
	BITMAPINFOHEADER   bi;
	sint32			   i;
	sint32             lineBytes = 0;
	sint32             Width;
	sint32             Height;
	sint32			   Size = 0;
	
	// 打开文件
	fp = fopen(lpszFileName, "rb");
	if(fp == NULL)
	{
		return 1;
	}
	// 读文件头
	fread((void *)&bf, sizeof(BITMAPFILEHEADER), 1, fp);
	fread((void *)&bi, sizeof(BITMAPINFOHEADER), 1, fp);
	// 检查是否为BMP文件
	if(bf.bfType != 19778)
	{
		fclose(fp);
		return 2;
	}
	// 检查是否为256色灰度图像
	if(bi.biBitCount != 8 && bi.biClrUsed != 256)
	{
		fclose(fp);
		return 3;
	}
	// 得到图像大小
	Height = bi.biHeight;
	Width = bi.biWidth;
	
	// 缓冲区指针不为空则读取图像数据到缓冲区
	if(lpBitmap != NULL)
	{
		lineBytes = (sint32)WIDTHBYTES(Width);
		Size = lineBytes*Height;
		
		fread(palatte, 1, 1024, fp);
		// 按行读取，每行只读取Width个字节
		for(i = 0; i < Height; i++)
		{
			fseek(fp, 1078+lineBytes*i, SEEK_SET);
			fread((void *)(lpBitmap+i*Width), 1, Width, fp);
		}
	}
	fclose(fp);	
	
	*lpWidth = Width;
	*lpHeight = Height;
	
	return 0;
}


//
// 对指纹图像进行处理，并提取指纹特征
//
VF_RETURN	VF_Process()
{
	sint32	re = 0;
	
	// 对指纹图像进行两次平滑，消除噪声
	smooth(g_lpOrgFinger, g_lpTemp, 1, 1);
	memcpy(g_lpOrgFinger, g_lpTemp, IMGSIZE);
	smooth(g_lpOrgFinger, g_lpTemp, 1, 1);
	memcpy(g_lpOrgFinger, g_lpTemp, IMGSIZE);
	
	// 利用图像低频部分计算方向场，提高速度
	zoomout();
	// 计算方向场
	getOrientMap(6);
	saveBitmap(g_lpOrient, IMGW, IMGH, "c:\\0.bmp");
	// 分割前景背景
	re = divide(12, 35);
	if(re != 0)
		return VF_PROCESS_ERR;
	saveBitmap(g_lpDivide, IMGW, IMGH, "c:\\00.bmp");
	
	// 两次定向滤波
	orientFilter();
//	orientFilter();
	saveBitmap(g_lpOrgFinger, IMGW, IMGH, "c:\\1.bmp");
	
	// 二值化
	binary();
	saveBitmap(g_lpOrgFinger, IMGW, IMGH, "c:\\2.bmp");
	
	// 二值化图像去噪声
	binaryClear();
	saveBitmap(g_lpOrgFinger, IMGW, IMGH, "c:\\3.bmp");
	
	// 清除背景
	clearEdge();
	saveBitmap(g_lpOrgFinger, IMGW, IMGH, "c:\\4.bmp");
	
	// 细化
	thin();
	// 细化图像去短棒和毛刺
	thinClear(12);
	saveBitmap(g_lpOrgFinger, IMGW, IMGH, "c:\\5.bmp");

	// 提取指纹特征
	re = getMinutia();
	int re2 = getSingular(g_lpOrient, IMGW, IMGH, -1);
	//int re3 = getSingular(g_lpOrient, IMGW, IMGH, 1);
	
//	if(re != 0 && re2 != 0)
		return VF_PROCESS_ERR;
	
	return VF_OK;
}


//
//	smooth: 对图像进行均值平滑滤波,消除噪声
//
void smooth(uint8 *lpInBuffer, uint8 *lpOutBuffer, sint32 r, sint32 d)
{
	////////////////////////////////////////////////////////////////////////
	//	lpInBuffer: [in] 要平滑的图像数据缓冲区
	//	lpOutBuffer: [out] 平滑后的图像数据缓冲区
	//	r: [in] 平滑滤波器半径
	//	d: [in] 平滑滤波器步长
	////////////////////////////////////////////////////////////////////////
	sint32	x, y, i, j;
	uint8	*lpSrc;
	uint8	*lpRst;
	sint32	sum, num;
	
	if(d == 2)
	{
		for(y = 0; y < IMGH; y++)
		{
			for(x = 0; x < IMGW; x++)
			{
				lpSrc = lpInBuffer + y*IMGW + x;//原图像指针
				lpRst = lpOutBuffer + y*IMGW + x;//目标图像指针
				sum = 0;						//像素和总量
				num = 0;						//像素量
				for(i = -r; i <= r; i+=2)		//在中心为（x，y）边长为2r的矩形中搜索
				{
					if(i+y<0 || i+y>=IMGH)
						continue;
					for(j = -r; j <= r; j+=2)
					{
						if(j+x<0 || j+x>=IMGW)
							continue;
						sum += *(lpSrc + i*IMGW + j);//求像素和
						num++;						//求像素个数
					}
				}
				*lpRst = (uint8)(sum/num);			//求平均
			}
		}
	}
	else
	{
		for(y = 0; y < IMGH; y++)
		{
			for(x = 0; x < IMGW; x++)
			{
				lpSrc = lpInBuffer + y*IMGW + x;
				lpRst = lpOutBuffer + y*IMGW + x;
				sum = 0; 
				num = 0;
				for(i = -r; i <= r; i++)
				{
					if(i+y<0 || i+y>=IMGH)
						continue;
					for(j = -r; j <= r; j++)
					{
						if(j+x<0 || j+x>=IMGW)
							continue;
						sum += *(lpSrc + i*IMGW + j);
						num++;
					}
				}
				*lpRst = (uint8)(sum/num);
			}
		}
	}
	
}


//
// 提取指纹图像低频信息用来计算方向场
//
void zoomout()
{
	sint32	x, y;
	uint8	*lpSrc;
	uint8	*lpRst;
	sint32	sum;
	sint32	SiteD8[8] = {IMGW-1, IMGW, IMGW+1, 1, -IMGW+1, -IMGW, -IMGW-1, -1};
	
	// 边缘部分
	for(y = 0; y < IMGH; y+=2)
	{
		lpSrc = g_lpOrgFinger + y*IMGW;
		lpRst = g_lpTemp + (y/2)*(IMGW/2);
		*lpRst = *lpSrc;
		lpSrc = g_lpOrgFinger + y*IMGW + IMGW - 1;
		lpRst = g_lpTemp + (y/2)*(IMGW/2) + (IMGW/2 - 1);
		*lpRst = *lpSrc;
	}
	for(x = 0; x < IMGW; x+=2)
	{
		lpSrc = g_lpOrgFinger + x;
		lpRst = g_lpTemp + x/2;
		*lpRst = *lpSrc;
		lpSrc = g_lpOrgFinger + (IMGH-1)*IMGW + x;
		lpRst = g_lpTemp + (IMGH/2-1)*(IMGW/2) + x/2;
		*lpRst = *lpSrc;
	}
	
	// 非边缘部分用高斯模板提取低频信息
	for(y = 2; y < IMGH-2; y+=2)
	{
		for(x = 2; x < IMGW-2; x+=2)
		{
			lpSrc = g_lpOrgFinger + y*IMGW + x;
			lpRst = g_lpTemp + (y/2)*(IMGW/2) + x/2;
			sum = *lpSrc*4 + *(lpSrc + SiteD8[0]) +
				*(lpSrc + SiteD8[1])*2 + *(lpSrc + SiteD8[2]) +
				*(lpSrc + SiteD8[3])*2 + *(lpSrc + SiteD8[4]) +
				*(lpSrc + SiteD8[5])*2 + *(lpSrc + SiteD8[6]) +
				*(lpSrc + SiteD8[7])*2;
			sum = sum>>4;
			*lpRst = (uint8)sum;
		}
	}	
}



//
//	getOrientMap: 求指纹方向场
//
void getOrientMap(sint32  r)
{
	/////////////////////////////////////////////////////////////////////////
	//	r: [in] 公式求算纹线方向的窗口半径，最好在(8 - 16)
	/////////////////////////////////////////////////////////////////////////
	sint32	x, y, i, j;
	sint32  vx, vy, lvx, lvy;
	uint8   *lpSrc = NULL;
	uint8   *lpDiv = NULL;
	uint8   *lpOri = NULL;
	sint32	angle, grad, gradSum, num;
	double  fAngle;
	
	for(y = 0; y < IMGH/2; y++)
	{
		for(x = 0; x < IMGW/2; x++)
		{
			lpDiv = g_lpDivide + 2*y*IMGW + 2*x;
			lpOri = g_lpOrient + 2*y*IMGW + 2*x;
			lvx = 0;
			lvy = 0;
			num = 0;
			gradSum = 0;
			for(i = -r; i <= r; i++)	// 为提高速度，步长为2
			{
				if(y+i<1 || y+i>=IMGH/2-1)
					continue;
				for(j = -r; j <= r; j++)	// 为提高速度，步长为2
				{
					if(x+j<1 || x+j>=IMGW/2-1)
						continue;
					lpSrc = g_lpTemp + (y+i)*(IMGW/2) + x+j;
					
					vx = *(lpSrc + IMGW/2 + 1) - *(lpSrc + IMGW/2 - 1) +
						*(lpSrc + 1)*2 - *(lpSrc - 1)*2 +
						*(lpSrc - IMGW/2 + 1) - *(lpSrc - IMGW/2 - 1);
					
					vy = *(lpSrc + IMGW/2 - 1) - *(lpSrc - IMGW/2 - 1) +
						*(lpSrc + IMGW/2)*2 - *(lpSrc - IMGW/2)*2 +
						*(lpSrc + IMGW/2 + 1) - *(lpSrc - IMGW/2 + 1);
					
					gradSum += (abs(vx)+abs(vy));
					lvx += vx * vy * 2;
					lvy += vx*vx - vy*vy;
					num++;
				}
			}
			if(num == 0)
				num = 1;
			// 求幅值，保存到g_lpDivide中，用于分割前景背景
			grad = gradSum/num;
			
			if(grad > 255)
				grad = 255;
			*lpDiv = (uint8)grad;
			*(lpDiv + 1) = (uint8)grad;
			*(lpDiv + IMGW) = (uint8)grad;
			*(lpDiv + IMGW + 1) = (uint8)grad;
			
			// 求弧度
			fAngle = atan2(lvy, lvx);
			// 变换到(0 - 2*pi)
			if(fAngle < 0)
			{
				fAngle += 2*PI;
			}
			// 求纹线角度
			fAngle = (fAngle*EPI*0.5 + 0.5);
			angle = (sint32)fAngle;
			
			// 因为采用 sobel算子，所以角度偏转了135度，所以要旋转求得的角度
			angle -= 135;
			// 角度变换到（0-180）
			if(angle <= 0)
			{
				angle += 180;
			}
			angle = 180-angle;
			// 最终纹线角度
			*lpOri = (uint8)angle;
			*(lpOri + 1) = (uint8)angle;
			*(lpOri + IMGW) = (uint8)angle;
			*(lpOri + IMGW + 1) = (uint8)angle;
			
		}
	}
	
}


//
//	saveBitmap: 将图像数据保存成BMP文件
//
sint32	saveBitmap(uint8 *lpBitmap, sint32 Width, sint32 Height, sint8 *lpszFileName)
{
	/////////////////////////////////////////////////////////////////////
	//	lpBitmap: [in] 要保存的图像数据
	//  Width: [in] 图像宽度
	//	Height: [in] 图像高度
	//  lpszFileName: [in] BMP文件名
	/////////////////////////////////////////////////////////////////////
   	FILE               *fp = NULL;
	uint8				palatte[1024];
	BITMAPFILEHEADER   bf;
	BITMAPINFOHEADER   bi;
	sint32             lineBytes = 0;
	sint32             i;
	
	lineBytes = (sint32)WIDTHBYTES(Width);
	
	//构造bmp文件头信息
	bf.bfType=19778;
	bf.bfSize = lineBytes*Height+1078;
	bf.bfReserved1=0;
	bf.bfReserved2=0;
	bf.bfOffBits=1078;
	bi.biSize=40;
	bi.biWidth = Width;
	bi.biHeight = Height;
	bi.biPlanes=1;
	bi.biBitCount=8;
	bi.biCompression=0;
	bi.biSizeImage= lineBytes*Height;
	bi.biXPelsPerMeter=0;
	bi.biYPelsPerMeter=0;
	bi.biClrUsed=256;
	
	bi.biClrImportant=0;
	//构造调色板数据
	for(i=0;i<256;i++){
		palatte[i*4]=(unsigned char)i;
		palatte[i*4+1]=(unsigned char)i;
		palatte[i*4+2]=(unsigned char)i;
		palatte[i*4+3]=0;
	}	
	// 创建文件
	fp = fopen(lpszFileName, "wb");
	if(fp == NULL)
	{
		return 1;
	}
	// 写文件头
	fwrite((char *)&bf,sizeof(BITMAPFILEHEADER), 1, fp); 
	// 写BMP图像信息头
	fwrite((char *)&bi, sizeof(BITMAPINFOHEADER), 1, fp);
	// 写调色板
	fwrite((char *)palatte, sizeof(palatte), 1, fp);
	// 按行写，每行写WIDTHBYTES(Width)个字节
	for(i = 0; i < Height; i++)
		fwrite((char *)(lpBitmap+i*Width), lineBytes, 1, fp);
	
	fclose(fp);	
	
	return 0;
}


//
// divide: 根据方向场幅值来分割指纹图像前景背景
//
sint32 divide(sint32  r, sint32 threshold)
{
	///////////////////////////////////////////////////////////////////////
	//	r: [in] 对幅值图像高度平滑滤波的滤波器半径
	//  threshold: [in] 分割的阈值
	///////////////////////////////////////////////////////////////////////
	sint32	x, y;
	sint32  num = 0;
	
	// 对方向场幅值图像进行高度平滑滤波
	smooth(g_lpDivide, g_lpTemp, r, 2);
	
	// 图像边缘均设置为背景
	for(y = 0; y < IMGH; y++)
	{
		*(g_lpDivide + y*IMGW) = 255;
		*(g_lpDivide + y*IMGW + IMGW - 1) = 255;
	}
	for(x = 0; x < IMGW; x++)
	{
		*(g_lpDivide + x) = 255;
		*(g_lpDivide + (IMGH-1)*IMGW + x) = 255;
	}
	
	for(y = 1; y < IMGH-1; y++)
	{
		for(x = 1; x < IMGW-1; x++)
		{
			// 根据幅值与阈值大小判断是否为背景区域
			if(*(g_lpTemp + y*IMGW + x) < threshold)
			{
				*(g_lpDivide + y*IMGW + x) = 255;
			}
			else
			{
				*(g_lpDivide + y*IMGW + x) = 0;
				num++;
			}
		}
	}
	
	// 如果前景区域面积小于总面积的十分之一，则表示前景区域太小，返回错误
	if(num < IMGSIZE/10)
		return 1;
	else
		return 0;
	
}


//
//	orientFilter: 对指纹图像进行定向滤波增强
//
void orientFilter()
{
	sint32 x, y;
	sint32 i;
	sint32 d = 0;
	sint32 sum = 0;
	// 纹线方向上进行平滑滤波的平滑滤波器
	sint32 Hw[7] = {1, 1, 1, 1, 1, 1, 1};
	// 纹线方向的垂直方向上进行锐化滤波的锐化滤波器
	sint32 Vw[7] = {-3, -1, 3, 9, 3, -1, -3};
	sint32 hsum = 0;
	sint32 vsum = 0;
	sint32 temp = 0;
	uint8  *lpSrc = NULL;
	uint8  *lpDir = NULL;

	// 纹线方向上进行平滑滤波
	temp = 0;
	for(y = 0; y < IMGH; y++)
	{
		for(x = 0; x < IMGW; x++)
		{
			lpDir = g_lpOrient + temp + x;
			lpSrc = g_lpOrgFinger + temp + x;
			// 纹线方向的索引
			d = DIndex(*lpDir);
			sum = 0;
			hsum = 0;
			for(i = 0; i < 7; i++)
			{
				if(y+g_DSite[d][i][1] < 0 || y+g_DSite[d][i][1] >= IMGH ||
				   x+g_DSite[d][i][0] < 0 || x+g_DSite[d][i][0] >= IMGW)
				{
					continue;
				}
				sum += Hw[i]*(*(lpSrc + g_DSite[d][i][1]*IMGW + g_DSite[d][i][0]));
				hsum += Hw[i];
			}
			if(hsum != 0)
			{
				*(g_lpTemp + temp + x) = (uint8)(sum/hsum);
			}
			else
			{
				*(g_lpTemp + temp + x) = 255;
			}
		}
		temp += IMGW;
	}

	// 纹线方向的垂直方向上进行锐化滤波
	temp = 0;
	for(y = 0; y < IMGH; y++)
	{
		for(x = 0; x < IMGW; x++)
		{
			lpDir = g_lpOrient + temp + x;
			lpSrc = g_lpTemp + temp + x;
			
			// 纹线方向的垂直方向的索引
			d = (DIndex(*lpDir)+6) % 12;

			sum = 0;
			vsum = 0;
			for(i = 0; i < 7; i++)
			{
				if(y+g_DSite[d][i][1] < 0 || y+g_DSite[d][i][1] >= IMGH ||
				   x+g_DSite[d][i][0] < 0 || x+g_DSite[d][i][0] >= IMGW)
				{
					continue;
				}
				sum += Vw[i]*(*(lpSrc + g_DSite[d][i][1]*IMGW + g_DSite[d][i][0]));
				vsum += Vw[i];
			}
			if(vsum > 0)
			{
				sum /= vsum;
				if(sum > 255)
				{
					*(g_lpOrgFinger + temp + x) = 255;
				}
				else if(sum < 0)
				{
					*(g_lpOrgFinger + temp + x) = 0;
				}
				else
				{
					*(g_lpOrgFinger + temp + x) = (uint8)sum;
				}
			}
			else
			{
				*(g_lpOrgFinger + temp + x) = 255;
			}
		}
		temp += IMGW;
	}

}


//
//	DIndex: 对角度进行量化，得到量化的索引号(0-12)
//
sint32  DIndex(sint32 angle)
{
	/////////////////////////////////////////////////////////////////////////
	//	angle: [in] 角度 （0 - 180）
	/////////////////////////////////////////////////////////////////////////
	if(angle >= 173 || angle < 8)
	{
		return 0;
	}
	else
	{
		return ((angle-8)/15 + 1);
	}
}


//
//	binary: 对指纹图像进行二值化
//
sint32 binary()
{
	sint32 x, y;
	sint32 i;
	sint32 d = 0;
	sint32 sum = 0;
	// 纹线方向上的7个点的权值
	sint32 Hw[7] = {2, 2, 3, 4, 3, 2, 2};
	// 纹线方向的垂直方向上的7个点的权值
	sint32 Vw[7] = {1, 1, 1, 1, 1, 1, 1};
	sint32 hsum = 0;	// 纹线方向上的7个点的加权和
	sint32 vsum = 0;	// 纹线方向的垂直方向上的7个点的加权和
	sint32 Hv = 0;		// 纹线方向上的7个点的加权平均值
	sint32 Vv = 0;		// 纹线方向的垂直方向上的7个点的加权平均值
	sint32 temp = 0;
	uint8  *lpSrc = NULL;	// 指纹图像像素点指针
	uint8  *lpDir = NULL;	// 纹线方向指针

	temp = 0;
	for(y = 0; y < IMGH; y++)
	{
		for(x = 0; x < IMGW; x++)
		{
			lpDir = g_lpOrient + temp + x;
			lpSrc = g_lpOrgFinger + temp + x;
			
			// 如果该点非常黑，则在临时缓冲区内置该点为黑点，值为0
			if(*lpSrc < 4)
			{
				*(g_lpTemp + temp + x) = 0;
				continue;
			}
			// 计算方向索引（量化为12个方向）
			d = DIndex(*lpDir);
			
			// 计算当前点在纹线方向上的加权平均值
			sum = 0;
			hsum = 0;
			for(i = 0; i < 7; i++)
			{
				// 坐标是否越界
				if(y+g_DSite[d][i][1] < 0 || y+g_DSite[d][i][1] >= IMGH ||
				   x+g_DSite[d][i][0] < 0 || x+g_DSite[d][i][0] >= IMGW)
				{
					continue;
				}
				sum += Hw[i]*(*(lpSrc + g_DSite[d][i][1]*IMGW + g_DSite[d][i][0]));
				hsum += Hw[i];
			}
			if(hsum != 0)
			{
				Hv = sum/hsum;
			}
			else
			{
				Hv = 255;
			}

			// 纹线方向的垂直方向的索引
			d = (d+6)%12;

			// 计算当前点在纹线方向的垂直方向上的加权平均值
			sum = 0;
			vsum = 0;
			for(i = 0; i < 7; i++)
			{
				if(y+g_DSite[d][i][1] < 0 || y+g_DSite[d][i][1] >= IMGH ||
				   x+g_DSite[d][i][0] < 0 || x+g_DSite[d][i][0] >= IMGW)
				{
					continue;
				}
				sum += Vw[i]*(*(lpSrc + g_DSite[d][i][1]*IMGW + g_DSite[d][i][0]));
				vsum += Vw[i];
			}
			if(vsum != 0)
			{
				Vv = sum/vsum;
			}
			else
			{
				Vv = 255;
			}

			
			if(Hv < Vv)
			{
				// 纹线方向上加权平均值较小则置当前点为黑点
				*(g_lpTemp + temp + x) = 0;
			}
			else
			{
				// 纹线方向上加权平均值较大则置当前点为白点
				*(g_lpTemp + temp + x) = 255;
			}
		}
		temp += IMGW;
	}

	// 将临时缓冲区内数据拷贝到原始图像数据缓冲区
	memcpy((void *)g_lpOrgFinger, (void *)g_lpTemp, IMGSIZE);
	

	return 0;

}


//
//	binary: 对二值化指纹图像进行去噪声
//
void binaryClear()
{
	sint32 x, y, i;
	sint32 num = 0;
	bool   bWorking;
	sint32 temp;
	uint8  *lpSrc = NULL;
	bWorking = true;
	sint32  n = 0;
	// 某点周围8个点的地址偏移
	sint32	SiteD8[8] = {IMGW-1, IMGW, IMGW+1, 1, -IMGW+1, -IMGW, -IMGW-1, -1};
	
	// 初始化临时缓冲区
	memset((void *)g_lpTemp, 255, IMGSIZE);
	
	// 循环处理直到处理完毕或者处理次数超过8
	while(bWorking && n < 8)
	{
		bWorking = false;
		n++;
		temp = IMGW;
		for(y = 1; y < IMGH-1; y++)
		{
			for(x = 1; x < IMGW-1; x++)
			{
				// 背景的点不处理
				if(*(g_lpDivide + temp + x) == 255)
				{
					continue;
				}
				// 统计当前点周围与它相同类型点的个数
				num = 0;
				lpSrc = g_lpOrgFinger + temp + x;
				for(i = 0; i < 8; i++)
				{
					if(*(lpSrc+SiteD8[i]) == *lpSrc)
					{
						num++;
					}
				}
				// 相同点个数小于二则改变当前点类型
				if(num < 2)
				{
					*(g_lpTemp+temp+x) = 255 - *lpSrc;
					bWorking = true;
				}
				else
				{
					*(g_lpTemp+temp+x) = *lpSrc;
				}
				
			}
			temp += IMGW;
		}
		// 将处理结果拷贝到原始图像缓冲区
		memcpy((void *)g_lpOrgFinger, (void *)g_lpTemp, IMGSIZE);
	}
	
}


//
//	clearEdge: 清除背景
//
void clearEdge()
{
	sint32	x, y;
	sint32  temp;
	temp = 0;
	
	for(y = 0; y < IMGH; y++)
	{
		for(x = 0; x < IMGW; x++)
		{	
			// 如果是背景区域，则置该点为白点
			if(*(g_lpDivide + temp + x) == 255)
			{
				*(g_lpOrgFinger + temp + x) = 255;
				*(g_lpOrient + temp + x) = 255;
			}
		}
		temp += IMGW;
	}
}


//
//	thin : 对当前指纹图像进行细化处理
//
sint32 thin()
{
	imageThin(g_lpOrgFinger, IMGW, IMGH);
	
	return 0;
}

//
//	thinClear: 清除细化图像中短棒和毛刺
//
sint32  thinClear(sint32  len)
{
	/////////////////////////////////////////////////////////////////
	//	len: [in] 短棒和毛刺的最大长度
	/////////////////////////////////////////////////////////////////
	sint32	x, y;
	sint32  i, n, num;
	sint32  temp;
	uint8   *Line[25];
	uint8   *lpNow = NULL;
	uint8   *lpLast = NULL;
	uint8   *lpNext = NULL;
	uint8   *tempPtr[8];
	sint32	SiteD8[8] = {IMGW-1, IMGW, IMGW+1, 1, -IMGW+1, -IMGW, -IMGW-1, -1};
	
	temp = 0;
	for(y = 0; y < IMGH; y++)
	{
		for(x = 0; x < IMGW; x++)
		{
			lpNow = g_lpOrgFinger + temp + x;
			if(*lpNow != 0)
			{
				continue;
			}
			Line[0] = lpNow;
			// 统计当前点的周围黑点个数
			n = 0;
			for(i = 0; i < 8; i++)
			{
				lpNext = lpNow + SiteD8[i];
				if(*lpNext == 0)
				{
					tempPtr[n] = lpNext;
					n++;
				}
			}
			// 黑点个数为零，表示当前点是孤点，置为白色
			if(n == 0)
			{
				*lpNow = 255;
				continue;
			}
			// 黑点个数为1，表示为端点
			else if(n == 1)
			{
				num = 0;
				lpLast = lpNow;
				lpNow = tempPtr[0];
				// 沿纹线跟踪len个点
				for(i = 0; i < len; i++)
				{
					// 如果遇到叉点则跳出循环
					if(IsFork(lpNow))
					{
						break;
					}
					num++;
					Line[num] = lpNow;
					if(GetNext(lpNow, lpLast, &lpNext) == 0)
					{
						lpLast = lpNow;
						lpNow = lpNext;
					}
					else // 如果遇到异常跳出循环
					{
						break;
					}
					
				}
				
				// 纹线较短，表示为短棒或者是毛刺
				if(num < len)
				{
					for(i = 0; i <= num; i++)
					{
						*Line[i] = 255;
					}
				}
				
			}
		}
		temp += IMGW;
	}
	
	return 0;
}


//
//	imageThin: 图像细化处理
//
sint32 imageThin(uint8 *lpBits, sint32 Width, sint32 Height)
{
/////////////////////////////////////////////////////////////////
//	lpBits: [in, out] 要细化的图像数据缓冲区 
//	Width: [in] 要细化的图像宽度
//	Height: [in] 要细化的图像高度
/////////////////////////////////////////////////////////////////
	uint8  erasetable[256]={
			0,0,1,1,0,0,1,1,             1,1,0,1,1,1,0,1,
			1,1,0,0,1,1,1,1,             0,0,0,0,0,0,0,1,
			0,0,1,1,0,0,1,1,             1,1,0,1,1,1,0,1,
			1,1,0,0,1,1,1,1,             0,0,0,0,0,0,0,1,
			1,1,0,0,1,1,0,0,             0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,             0,0,0,0,0,0,0,0,
			1,1,0,0,1,1,0,0,             1,1,0,1,1,1,0,1,
			0,0,0,0,0,0,0,0,             0,0,0,0,0,0,0,0,
			0,0,1,1,0,0,1,1,             1,1,0,1,1,1,0,1,
			1,1,0,0,1,1,1,1,             0,0,0,0,0,0,0,1,
			0,0,1,1,0,0,1,1,             1,1,0,1,1,1,0,1,
			1,1,0,0,1,1,1,1,             0,0,0,0,0,0,0,0,
			1,1,0,0,1,1,0,0,             0,0,0,0,0,0,0,0,
			1,1,0,0,1,1,1,1,             0,0,0,0,0,0,0,0,
			1,1,0,0,1,1,0,0,             1,1,0,1,1,1,0,0,
			1,1,0,0,1,1,1,0,             1,1,0,0,1,0,0,0
	};
	sint32		x,y;
	sint32      num;
	BOOL        Finished;
	uint8       nw,n,ne,w,e,sw,s,se;
	uint8       *lpPtr = NULL;
	uint8       *lpTempPtr = NULL;	

	memcpy((void *)g_lpTemp, (void *)lpBits, Width*Height);
	
	//结束标志置成假
	Finished=FALSE;
	while(!Finished){ //还没有结束
              //结束标志置成假
            Finished=TRUE;
       //先进行水平方向的细化
              for (y=1;y<Height-1;y++)
			  { //注意为防止越界，y的范围从1到高度-2
                     //lpPtr指向原图数据，lpTempPtr指向新图数据

                     lpPtr=(uint8 *)lpBits+y*Width;
                     lpTempPtr=(uint8 *)g_lpTemp+y*Width;

                     x=1; //注意为防止越界，x的范围从1到宽度-2

                     while(x<Width-1)
					 {
                            if(*(lpPtr+x)==0)
							{ //是黑点才做处理
                                   w = *(lpPtr+x-1);  //左邻点
                                   e = *(lpPtr+x+1);  //右邻点

                                   if( (w==255)|| (e==255)){ 

									//如果左右两个邻居中至少有一个是白点才处理

                                          nw=*(lpPtr+x+Width-1); //左上邻点

                                          n=*(lpPtr+x+Width); //上邻点

                                          ne=*(lpPtr+x+Width+1); //右上邻点

                                          sw=*(lpPtr+x-Width-1); //左下邻点

                                          s=*(lpPtr+x-Width); //下邻点

                                          se=*(lpPtr+x-Width+1); //右下邻点

                                          //计算索引

                            num=nw/255+n/255*2+ne/255*4+w/255*8+e/255*16+
								sw/255*32+s/255*64+se/255*128;

                                          if(erasetable[num]==1){ //经查表，可以删除

												//在原图缓冲区中将该黑点删除

                                                 *(lpPtr+x)=255; 

													//结果图中该黑点也删除

                                                 *(lpTempPtr+x)=255; 

                                                 Finished=FALSE; //有改动，结束标志置成假

                                                 x++; //水平方向跳过一个象素

                                          }

                                   }

                            }

                            x++; //扫描下一个象素

                     }

              }

       //再进行垂直方向的细化

              for (x=1;x<Width-1;x++){ //注意为防止越界，x的范围从1到宽度-2

                     y=1; //注意为防止越界，y的范围从1到高度-2

                     while(y<Height-1){

                            lpPtr=lpBits+y*Width;

                            lpTempPtr=g_lpTemp+y*Width;

                            if(*(lpPtr+x)==0){ //是黑点才做处理

                                   n=*(lpPtr+x+Width);

                                   s=*(lpPtr+x-Width);

                                   if( (n==255)|| (s==255)){

//如果上下两个邻居中至少有一个是白点才处理

                                          nw=*(lpPtr+x+Width-1);

                                          ne=*(lpPtr+x+Width+1);

                                          w=*(lpPtr+x-1);

                                          e=*(lpPtr+x+1);

                                          sw=*(lpPtr+x-Width-1);

                                          se=*(lpPtr+x-Width+1);

                                          //计算索引

										num=nw/255+n/255*2+ne/255*4+w/255*8+e/255*16+

											sw/255*32+s/255*64+se/255*128;

                                          if(erasetable[num]==1){ //经查表，可以删除

//在原图缓冲区中将该黑点删除

                                                 *(lpPtr+x)=255; 

//结果图中该黑点也删除

                                                 *(lpTempPtr+x)=255; 

                                                 Finished=FALSE; //有改动，结束标志置成假

                                                 y++;//垂直方向跳过一个象素

                                          }

                                   }

                            }

                            y++; //扫描下一个象素

                     }

              } 

	}
	
	memcpy((void *)lpBits, (void *)g_lpTemp, Width*Height);

	return 0;
}


//
//	IsFork: 判断某点是否为叉点
//
bool   IsFork(uint8 *lpNow)
{
	/////////////////////////////////////////////////////////////////////////////
	//	lpNow : [in] 当前点的地址
	/////////////////////////////////////////////////////////////////////////////
	sint32 i, sum;
	// 某点周围8个点的地址偏移
	sint32	SiteD8[8] = {IMGW-1, IMGW, IMGW+1, 1, -IMGW+1, -IMGW, -IMGW-1, -1};
	
	// 8个点所有相邻两个点的差的绝对值的和如果为6*255则为叉点
	sum = 0;
	for(i = 0; i < 8; i++)
	{
		sum += abs(*(lpNow + SiteD8[(i+1)%8]) - *(lpNow + SiteD8[i]));
	}
	if(sum == 255*6)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//
//	GetNext: 在纹线上根据当前点和前驱点地址找到下一个点的地址
//
sint32  GetNext(uint8 *lpNow, uint8 *lpLast, uint8 **lppNext)
{
	/////////////////////////////////////////////////////////////////////////////
	//	lpNow : [in] 当前点的地址
	//	lpLast : [in] 前驱点的地址
	//	lppNext : [out] 下一个点的地址的指针
	/////////////////////////////////////////////////////////////////////////////
	sint32  i;
	uint8   *lpSrc = NULL;
	sint32  n;
	uint8   *Temp[8];	// 某点周围8个点的地址
	sint32	SiteD8[8] = {IMGW-1, IMGW, IMGW+1, 1, -IMGW+1, -IMGW, -IMGW-1, -1};
	
	*lppNext = NULL;
	
	// 找到当前点周围的是黑点并且不是前驱点的黑点，保存到数组
	n = 0;
	for(i = 0; i < 8; i++)
	{
		lpSrc = lpNow + SiteD8[i];
		if(*lpSrc == 0 && lpSrc != lpLast)
		{
			Temp[n] = lpSrc;
			n++;
		}
	}
	
	if(n == 0)	// 没有找到其他黑点则表示没有后继点
	{
		*lppNext = NULL;
		return 1;
	}
	else if(n == 1) // 找到了一个，则其为后继点
	{
		*lppNext = Temp[0];
		return 0;
	}
	else // 找到多个点则返回错误
	{
		*lppNext = NULL;
		return 1;
	}
	
	return 0;
}


//
//	getMinutia: 提取指纹特征
//
sint32  getMinutia()
{
	sint32	x, y, i, j, k, n;
	sint32  temp;
	sint32  sum;
	uint8   *lpNow;
	uint8   *lpDis;
	sint32  r = 16;		// 允许特征点靠近前景边缘的最近距离
	double  d, d1, d2, d0, a;
	sint32  dGate = 16;
	bool    flag;
	sint32  x11, y11;
	sint32  x21, y21;
	sint32  angle1, angle2, angle3, angle4;
	uint8   *tempPtr[8];
	uint8   *disPtr[3];
	uint8   *lpOri;
	sint32  tempForkNum;
	sint32  tempEndNum;
	sint32  ForkNum;
	sint32  EndNum;
	// 临时特征点数组
	MINUTIA     tempFork[MAXRAWMINUTIANUM];
	MINUTIA     tempEnd[MAXRAWMINUTIANUM];
	MINUTIA     ForkArr[MAXRAWMINUTIANUM];
	MINUTIA     EndArr[MAXRAWMINUTIANUM];
	// 某点为圆心，半径为5的圆上所有点的地址偏移
	sint32	SiteR5[28] = {
		-5, IMGW-5, 2*IMGW-5, 3*IMGW-4, 4*IMGW-3, 5*IMGW-2, 5*IMGW-1, 5*IMGW,
		5*IMGW+1, 5*IMGW+2, 4*IMGW+3, 3*IMGW+4, 2*IMGW+5, IMGW+5, 5, -IMGW+5,
		-2*IMGW+5, -3*IMGW+4, -4*IMGW+3, -5*IMGW+2, -5*IMGW+1, -5*IMGW,
		-5*IMGW-1, -5*IMGW-2, -4*IMGW-3, -3*IMGW-4, -2*IMGW-5, -IMGW-5
	}; 
	// 某点周围8个点的地址偏移
	sint32	SiteU8[8] = {IMGW-1, IMGW, IMGW+1, 1, -IMGW+1, -IMGW, -IMGW-1, -1};

	// 初始化临时特征点数组
	memset((void *)&tempFork[0], 0, MAXRAWMINUTIANUM*sizeof(MINUTIA));
	memset((void *)&tempEnd[0], 0, MAXRAWMINUTIANUM*sizeof(MINUTIA));
	memset((void *)&ForkArr[0], 0, MAXRAWMINUTIANUM*sizeof(MINUTIA));
	memset((void *)&EndArr[0], 0, MAXRAWMINUTIANUM*sizeof(MINUTIA));


	bool    bGood = false;	// 标记阈值是否调整好，使特征点数目在允许范围内
	sint32  densD = 7;	// 允许两个特征点间最近的距离
	sint32  loopnum;	// 循环次数
	sint32  trilen = 16;
	// 第一遍寻找所有端点和叉点	
	ForkNum = 0; 
	EndNum = 0; 
	temp = 17 * IMGW;
	for(y = 17; y < IMGH-17; y++)
	{
		for(x = 17; x < IMGW-17; x++)
		{
			lpNow = g_lpOrgFinger + temp + x;//原图像指针
			lpOri = g_lpOrient + y*IMGW + x;//原图像方向场指针
			// 不是黑点则不考虑
			if(*lpNow != 0)
			{
				continue;
			}
			// 是叉点
			if(IsFork(lpNow))
			{
				// 检查是否靠近边缘, 靠近边缘则不考虑
				flag = true;
				for(i = -r; i <= r && flag; i++)
				{
					for(j = -r; j <= r && flag; j++)
					{
						if(y+i<0 || y+i>=IMGH || x+j<0 || x+j>=IMGW)
						{
							continue;
						}

						if(*(g_lpOrient + temp + i*IMGW + x + j) == 255)
						{
							flag = false;
							break;
						}
					}
				}
				// 检查该点周围方向场是否变化剧烈，变化剧烈则不考虑，因为很可能是虚假点
				sum = 0;
				for(i = 0; i < 28; i++)
				{
					sum += GetJiajiao(*(lpOri+SiteR5[(i+1)%28]), *(lpOri+SiteR5[i]));//相邻两个方向的夹角
				}
				if(sum > 96)
					flag = false;
				
				// 达到所有要求则记录下来该点
				if(flag)
				{
					ForkArr[ForkNum].x = x;
					ForkArr[ForkNum].y = y;
					ForkNum++;
					// 如果总数已经超过允许最大数目，则返回错误
					if(ForkNum >= MAXRAWMINUTIANUM)
					{
						ForkNum = 0;
						return 1;
					}

				}

			}
			else if(IsEnd(lpNow))	// 如果是端点
			{
				// 检查是否靠近边缘, 靠近边缘则不考虑
				flag = true;
				for(i = -r; i <= r && flag; i++)
				{
					for(j = -r; j <= r && flag; j++)
					{
						if(y+i<0 || y+i>=IMGH || x+j<0 || x+j>=IMGW)
						{
							continue;
						}

						if(*(g_lpOrient + temp + i*IMGW + x + j) == 255)
						{
							flag = false;
							break;
						}
					}
				}

				// 检查该点周围方向场是否变化剧烈，变化剧烈则不考虑，因为很可能是虚假点
				sum = 0;
				for(i = 0; i < 28; i++)
				{
					sum += GetJiajiao(*(lpOri+SiteR5[(i+1)%28]), *(lpOri+SiteR5[i]));
				}
				if(sum > 96)
					flag = false;

				// 达到所有要求则记录下来该点
				if(flag)
				{
					EndArr[EndNum].x = x;
					EndArr[EndNum].y = y;
					EndNum++;
					// 如果总数已经超过允许最大数目，则返回错误
					if(EndNum >= MAXRAWMINUTIANUM)
					{
						EndNum = 0;
						return 1;
					}

				}

			}
		}
		temp += IMGW;
	}

	// 初始化临时缓冲区，准备循环调整两个特征点间允许的最小距离，使之增大到一个合适的值
	// 因为如果特征点非常密集的地方很有可能是质量很差的地方
	for(i = 0; i < MAXRAWMINUTIANUM; i++)
	{
		tempEnd[i] = EndArr[i];
	}
	for(i = 0; i < MAXRAWMINUTIANUM; i++)
	{
		tempFork[i] = ForkArr[i];
	}
	tempForkNum = ForkNum;
	tempEndNum = EndNum;

	// 循环调整
	bGood = false;
	loopnum = 0;	// 调整的次数
	while(!bGood && loopnum < 32) // 最多调整32次
	{
		loopnum++;	// 调整次数加一
		// 得到新的特征点数组
		for(i = 0; i < MAXRAWMINUTIANUM; i++)
		{
			EndArr[i] = tempEnd[i];
		}
		for(i = 0; i < MAXRAWMINUTIANUM; i++)
		{
			ForkArr[i] = tempFork[i];
		}
		// 新的特征点数
		ForkNum = tempForkNum;	// 叉点
		EndNum = tempEndNum;	// 端点

		// 去掉虚假的端点
		bGood = true;
		for(i = 0; i < EndNum-1; i++)
		{
			flag = false;
			for(j = i+1; j < EndNum; j++)
			{
				// 求两个端点的距离
				d = sqrt((double)((EndArr[i].x-EndArr[j].x)*(EndArr[i].x-EndArr[j].x) +
					(EndArr[i].y-EndArr[j].y)*(EndArr[i].y-EndArr[j].y)));
				// 距离足够大则检查下一个端点
				if(d > dGate && d > densD)
				{
					continue;
				}
				// 距离太小，则将其坐标置为（0，0）
				if(d <= densD)
				{
					EndArr[j].x = 0;
					EndArr[j].y = 0;
					flag = true;
					continue;
				}
				// 求第一个端点所在纹线的角度
				lpNow = g_lpOrgFinger + EndArr[i].y*IMGW + EndArr[i].x;
				if(GetByDis(lpNow, &lpDis, 8) != 0)
				{
					break;
				}
				angle1 = GetAngle(EndArr[i].x, EndArr[i].y, PX(lpDis), PY(lpDis));
				
				// 求第二个端点所在纹线的角度
				lpNow = g_lpOrgFinger + EndArr[j].y*IMGW + EndArr[j].x;
				if(GetByDis(lpNow, &lpDis, 8) != 0)
				{
					continue;
				}
				angle2 = GetAngle(EndArr[j].x, EndArr[j].y, PX(lpDis), PY(lpDis));

				// 求两个角度间的距离
				angle3 = GetAngleDis(angle1, angle2);
				
				// 如果两个角度间成锐角，则不是虚假特征点
				if(angle3 > 270 || angle3 < 90)
				{
					continue;
				}

				// 求两个端点连线的角度
				angle3 = GetAngle(EndArr[i].x, EndArr[i].y, EndArr[j].x, EndArr[j].y);
				// 求第一个端点纹线与连线的夹角
				angle3 = GetAngleDis(angle1, angle3);
				// 如果夹角较大则不是虚假点
				if(angle3 < 150 || angle3 > 210)
				{
					continue;
				}

				// 求第二个端点纹线与连线的夹角
				angle4 = GetAngle(EndArr[j].x, EndArr[j].y, EndArr[i].x, EndArr[i].y);
				angle4 = GetAngleDis(angle2, angle4);
				
				// 如果夹角较大则不是虚假点
				if(angle4 < 150 || angle4 > 210)
				{
					continue;
				}
				// 否则表示这两个点是同一条纹线上的断裂处的两个端点,坐标置原点
				EndArr[j].x = 0;
				EndArr[j].y = 0;
				flag = true;
			}
			if(flag)// 表示这两个点是同一条纹线上的断裂处的两个端点,坐标置原点
			{
				EndArr[i].x = 0;
				EndArr[i].y = 0;
			}
		}

		// 统计新的端点数目
		j = 0;
		for(i = 0; i < EndNum; i++)
		{
			if(EndArr[i].x == 0 || EndArr[i].y == 0)
			{
				continue;
			}
			lpNow = g_lpOrgFinger + EndArr[i].y*IMGW + EndArr[i].x;
			if(GetByDis(lpNow, &lpDis, 8) != 0)
			{
				continue;
			}

			j++;
			// 如果端点数目还是过多，则需要调整densD
			if(j >= MAXMINUTIANUM)
			{
				bGood = false;
				break;
			}

		}
		// 调整densD
		if(!bGood)
		{
			densD++; // 加一
			continue;
		}

		// 将端点装配到g_Feature
		j = 0;
		for(i = 0; i < EndNum; i++)
		{
			if(EndArr[i].x == 0 || EndArr[i].y == 0)
			{
				continue;
			}
			// 沿纹线找到第8个点
			lpNow = g_lpOrgFinger + EndArr[i].y * IMGW + EndArr[i].x;
			if(GetByDis(lpNow, &lpDis, 8) != 0)
			{
				continue;
			}
			// 求该点与端点连线的角度
			angle1 = GetAngle(EndArr[i].x, EndArr[i].y, PX(lpDis), PY(lpDis));
			angle2 = *(g_lpOrient + EndArr[i].y*IMGW + EndArr[i].x);
			angle3 = GetAngleDis(angle1, angle2);
			// 如果成钝角，则表示该特征点方向与该点方向场方向相反
			if(angle3 > 90 && angle3 < 270)
			{
				g_Feature.MinutiaArr[j].Direction = angle2 + 180;
			}
			else // 如果成锐角，则表示该特征点方向与该点方向场方向相同
			{
				g_Feature.MinutiaArr[j].Direction = angle2;
			}

			//若两点互相匹配，则两点周围的相对方向场相似
			a = g_Feature.MinutiaArr[j].Direction / EPI + PI/4.0;
			x11 = EndArr[i].x + (sint32)(trilen*cos(a)+ 0.5);
			y11 = EndArr[i].y + (sint32)(trilen*sin(a)+ 0.5);
			g_Feature.MinutiaArr[j].Triangle[0] = *(g_lpOrient + y11*IMGW + x11);
			a += PI*2/3.0;
			x11 = EndArr[i].x + (sint32)(trilen*cos(a)+ 0.5);
			y11 = EndArr[i].y + (sint32)(trilen*sin(a)+ 0.5);
			g_Feature.MinutiaArr[j].Triangle[1] = *(g_lpOrient + y11*IMGW + x11);
			a += PI*2/3.0;
			x11 = EndArr[i].x + (sint32)(trilen*cos(a)+ 0.5);
			y11 = EndArr[i].y + (sint32)(trilen*sin(a)+ 0.5);
			g_Feature.MinutiaArr[j].Triangle[2] = *(g_lpOrient + y11*IMGW + x11);

			g_Feature.MinutiaArr[j].x = EndArr[i].x;	//横坐标
			g_Feature.MinutiaArr[j].y = EndArr[i].y;	//纵坐标
			g_Feature.MinutiaArr[j].Type = VF_MINUTIA_END;	//类型

			j++;

		}

		EndNum = j;	// 端点数目


		// 去掉距离太近的叉点
		for(i = 0; i < ForkNum-1; i++)
		{
			flag = false;
			for(j = i+1; j < ForkNum; j++)
			{
				d = sqrt((double)((ForkArr[i].x-ForkArr[j].x)*(ForkArr[i].x-ForkArr[j].x) +
					(ForkArr[i].y-ForkArr[j].y)*(ForkArr[i].y-ForkArr[j].y)));

				if(d <= densD-2)
				{
					ForkArr[j].x = 0;
					ForkArr[j].y = 0;
					flag = true;
				}
			}
			if(flag)
			{
				ForkArr[i].x = 0;
				ForkArr[i].y = 0;
			}
		}

		// 统计新的真正的叉点
		j = 0;
		for(i = 0; i < ForkNum; i++)
		{
			if(ForkArr[i].x == 0 || ForkArr[i].y == 0)
			{
				continue;
			}
			lpNow = g_lpOrgFinger + ForkArr[i].y*IMGW + ForkArr[i].x;

			tempPtr[0] = lpNow;
			*tempPtr[0] = 255;
			// 检查是否真正叉点
			n = 0;
			for(k = 0; k < 8; k++)
			{
				if(*(lpNow + SiteU8[k]) == 0)
				{
					tempPtr[n+1] = lpNow + SiteU8[k];
					*tempPtr[n+1] = 255;
					n++;
				}
			}
			for(k = 0; k < 4; k++)
			{
				*tempPtr[k] = 0;
			}

			if(n != 3)
			{
				continue;
			}
			j++;
			// 特征点总数大于允许最大数目则要调整densD
			if(EndNum + j >= MAXMINUTIANUM)
			{
				densD++;
				bGood = false;
				break;
			}

		}

		if(!bGood)
		{
			continue;
		}

		// 装配叉点到g_Feature
		j = 0;
		for(i = 0; i < ForkNum; i++)
		{
			if(ForkArr[i].x == 0 || ForkArr[i].y == 0)
			{
				continue;
			}
			lpNow = g_lpOrgFinger + ForkArr[i].y*IMGW + ForkArr[i].x;

			tempPtr[0] = lpNow;
			*tempPtr[0] = 255;
			n = 0;
			for(k = 0; k < 8; k++)
			{
				if(*(lpNow + SiteU8[k]) == 0)
				{
					tempPtr[n+1] = lpNow + SiteU8[k];
					*tempPtr[n+1] = 255;
					n++;
				}
			}
			if(n != 3)
			{
				continue;
			}
			// 找到叉点三个方向纹线上距离为8的点
			for(k = 0; k < 3; k++)
			{
				GetByDis(tempPtr[k+1], &disPtr[k], 8);
			}
			for(k = 0; k < 4; k++)
			{
				*tempPtr[k] = 0;
			}
			// 求该三个点两两间的距离
			d0 = sqrt((double)((PX(disPtr[1]) - PX(disPtr[2]))*(PX(disPtr[1]) - PX(disPtr[2])) +
				(PY(disPtr[1]) - PY(disPtr[2]))*(PY(disPtr[1]) - PY(disPtr[2]))));
			d1 = sqrt((double)((PX(disPtr[0]) - PX(disPtr[2]))*(PX(disPtr[0]) - PX(disPtr[2])) +
				(PY(disPtr[0]) - PY(disPtr[2]))*(PY(disPtr[0]) - PY(disPtr[2]))));
			d2 = sqrt((double)((PX(disPtr[1]) - PX(disPtr[0]))*(PX(disPtr[1]) - PX(disPtr[0])) +
				(PY(disPtr[1]) - PY(disPtr[0]))*(PY(disPtr[1]) - PY(disPtr[0]))));

			// 距离最短的边对应的是叉线方向
			if(d0 < d1 && d0 < d2)
			{
				x11 = PX(disPtr[1]);
				y11 = PY(disPtr[1]);
				x21 = PX(disPtr[2]);
				y21 = PY(disPtr[2]);
				lpDis = disPtr[0];
			}
			else if(d1 < d0 && d1 < d2)
			{
				x11 = PX(disPtr[0]);
				y11 = PY(disPtr[0]);
				x21 = PX(disPtr[2]);
				y21 = PY(disPtr[2]);
				lpDis = disPtr[1];
			}
			else
			{
				x11 = PX(disPtr[0]);
				y11 = PY(disPtr[0]);
				x21 = PX(disPtr[1]);
				y21 = PY(disPtr[1]);
				lpDis = disPtr[2];
			}
			// 求最短边中点与叉点连线的方向与该点方向场方向的夹角
			angle1 = GetAngle(ForkArr[i].x, ForkArr[i].y, (x11+x21)/2, (y11+y21)/2);
			angle2 = *(g_lpOrient + ForkArr[i].y*IMGW + ForkArr[i].x);
			angle3 = GetAngleDis(angle1, angle2);
			// 如果成钝角，则表示该特征点方向与该点方向场方向相反
			if(angle3 > 90 && angle3 < 270)
			{
				g_Feature.MinutiaArr[EndNum + j].Direction = angle2 + 180;
			}
			else // 如果成锐角，则表示该特征点方向与该点方向场方向相同
			{
				g_Feature.MinutiaArr[EndNum + j].Direction = angle2;
			}
			// 纪录以特征点为中心外接圆半径为trilen的正三角形三个顶点的方向
			a = g_Feature.MinutiaArr[EndNum + j].Direction / EPI + PI/4.0;
			x11 = EndArr[i].x + (sint32)(trilen*cos(a)+ 0.5);
			y11 = EndArr[i].y + (sint32)(trilen*sin(a)+ 0.5);
			g_Feature.MinutiaArr[EndNum + j].Triangle[0] = *(g_lpOrient + y11*IMGW + x11);
			a += PI*2/3.0;
			x11 = EndArr[i].x + (sint32)(trilen*cos(a)+ 0.5);
			y11 = EndArr[i].y + (sint32)(trilen*sin(a)+ 0.5);
			g_Feature.MinutiaArr[EndNum + j].Triangle[1] = *(g_lpOrient + y11*IMGW + x11);
			a += PI*2/3.0;
			x11 = EndArr[i].x + (sint32)(trilen*cos(a)+ 0.5);
			y11 = EndArr[i].y + (sint32)(trilen*sin(a)+ 0.5);
			g_Feature.MinutiaArr[EndNum + j].Triangle[2] = *(g_lpOrient + y11*IMGW + x11);

			g_Feature.MinutiaArr[EndNum + j].x = ForkArr[i].x; //横坐标
			g_Feature.MinutiaArr[EndNum + j].y = ForkArr[i].y; //纵坐标
			g_Feature.MinutiaArr[EndNum + j].Type = VF_MINUTIA_FORK; // 类型


			j++;
		}
		ForkNum = j; // 叉点数目


	}

	// 如果循环32次都不能得到理想结果，则表示图像质量差，返回错误
	if(loopnum >= 32)
	{
		EndNum = 0;
		ForkNum = 0;
		return 1;
	}
	// 特征点数目等于端点数加叉点数
	g_Feature.MinutiaNum = (uint8)(EndNum+ForkNum);

	//  特征点数目太少则返回错误
	if(ForkNum + EndNum < 8)
	{
		EndNum = 0;
		ForkNum = 0;
		return 1;
	}

	return 0;
}


//
//	IsEnd: 判断某点是否为端点
//
bool   IsEnd(uint8 *lpNow)
{
	/////////////////////////////////////////////////////////////////////////////
	//	lpNow : [in] 当前点的地址
	/////////////////////////////////////////////////////////////////////////////
	sint32 i, sum;
	// 某点周围8个点的地址偏移
	sint32	SiteD8[8] = {IMGW-1, IMGW, IMGW+1, 1, -IMGW+1, -IMGW, -IMGW-1, -1};
	
	// 8个点所有相邻两个点的差的绝对值的和如果为2*255则为端点
	sum = 0;
	for(i = 0; i < 8; i++)
	{
		sum += abs(*(lpNow + SiteD8[(i+1)%8]) - *(lpNow + SiteD8[i]));
	}
	if(sum == 255*2)
	{
		return true;
	}
	else
	{
		return false;
	}
}


//
//	GetByDis: 在纹线上找到距离当前端点为d的点的地址
//
sint32  GetByDis(uint8 *lpEnd, uint8 **lppPos, sint32 d)
{
/////////////////////////////////////////////////////////////////////////////
//	lpEnd : [in] 当前端点的地址
//	lppPos : [out] 目的点的地址(如果在距离d内有端点或者叉点，则返回他们的邻点)
//	d : [in] 距离（点数）
/////////////////////////////////////////////////////////////////////////////
	sint32  i, n;
	uint8   *lpNow = NULL;
	uint8   *lpLast = NULL;
	uint8   *lpNext = NULL;
	sint32	SiteD8[8] = {IMGW-1, IMGW, IMGW+1, 1, -IMGW+1, -IMGW, -IMGW-1, -1};

	*lppPos = NULL;
	
	// 找到当前点周围的是黑点并且不是前驱点的黑点，保存到数组
	n = 0;
	for(i = 0; i < 8; i++)
	{
		if(*(lpEnd + SiteD8[i]) == 0)
		{
			lpNow = lpEnd + SiteD8[i];
			n++;
		}
	}
	if(n != 1) // 数目如果不是1则返回错误
	{
		return 1;
	}
	// 找到的黑点地址为lpNow
	// 端点作为前驱点,地址保存到lpLast
	lpLast = lpEnd; 
	// 循环找d次后继点
	for(i = 0; i < d; i++)
	{
		// 如果是叉点则跳出循环
		if(IsFork(lpNow))
		{
			break;
		}
		// 成功找到下一个点则更改当前点和前驱点
		if(GetNext(lpNow, lpLast, &lpNext) == 0)
		{
			lpLast = lpNow;
			lpNow = lpNext;
		}
		else
		{
			break;
		}

	}
	// 如果找到的点为叉点，则返回其前驱点
	if(IsFork(lpNow))
	{
		*lppPos = lpLast;
	}	
	else	// 否则返回当前点
	{
		*lppPos = lpNow;
	}

	return 0;
}

//
//	PX: 根据地址得到当前点的横坐标
//
sint32  PX(uint8 *lpPos)
{
/////////////////////////////////////////////////////////////////////////
//	lpPos: [in] 当前点地址
/////////////////////////////////////////////////////////////////////////
	return ((lpPos - g_lpOrgFinger) % IMGW);
}

//
//	PY: 根据地址得到当前点的纵坐标
//
sint32  PY(uint8 *lpPos)
{
/////////////////////////////////////////////////////////////////////////
//	lpPos: [in] 当前点地址
/////////////////////////////////////////////////////////////////////////
	return ((lpPos - g_lpOrgFinger) / IMGW);
}

//
//	GetJiajiao: 求两个角度的夹角(0 - 90)
//
sint32  GetJiajiao(sint32 angle1, sint32 angle2)
{
/////////////////////////////////////////////////////////////////////////
//	angle1: [in] 角度一 （0 - 180）
//	angle2: [in] 角度二 （0 - 180）
/////////////////////////////////////////////////////////////////////////
	sint32  a;

	a = abs(angle1-angle2);
	if(a > 90)
	{
		a = 180-a;
	}
	return a;
}


//
//	GetAngleDis： 两个角度间的距离(0-360)  (逆时针方向)
//
sint32  GetAngleDis(sint32 angleBegin, sint32 angleEnd)
{
	/////////////////////////////////////////////////////////////////////////
	//	angleBegin: [in] 起始角度 （0 - 360）
	//	angleEnd: [in] 终结角度 （0 - 360）
	/////////////////////////////////////////////////////////////////////////
	sint32  a;
	
	a = angleEnd-angleBegin;
	if(a < 0)
	{
		a += 360;
	}
	return a;
}

//
//	GetAngle： 两个点连线与x轴方向的角度
//
sint32  GetAngle(sint32 x0, sint32 y0, sint32 x1, sint32 y1)
{
	/////////////////////////////////////////////////////////////////////////
	//	x0: [in] 第一个点横坐标
	//	y0: [in] 第一个点纵坐标
	//	x1: [in] 第二个点横坐标
	//	y1: [in] 第二个点纵坐标
	/////////////////////////////////////////////////////////////////////////
	double angle;
	
	angle = atan2((double)(y1-y0), (double)(x1-x0));
	// 弧度转化到0 - 2*PI
	if(angle < 0)
	{
		angle += 2*PI;
	}
	// 弧度转化为角度
	return (sint32)(angle*EPI + 0.5);
}



int getSingular(BYTE *lpOrient, int Width, int Height, char flag)
{
	int    x, y, i;
	int    num;
	int    sum1, sum2;
	int    d;
	unsigned char *pOriMap;

	int    oriV;
	int    a1, a2;
	DBLPOINT  singuArr[30];

	int    value;
	double dis;
	bool   bFound = false;
	bool   fg = false;
	int    D3[8][2] = {
		-1,-1, -1,0,  -1,1,  0,1,  1,1,  1,0,  1,-1,  0,-1
	};
	int    D5[12][2] = {
		-2,-1, -2,0,  -2,1, -1,2,  0,2,  1,2, 2,1,  2,0,  2,-1, 1,-2, 0,-2, -1,-2
	};
	int    D7[24][2] = {
		-3,-3, -3,-2, -3,-1, -3,0, -3,1, -3,2, -3,3, -2,3, -1,3, 0,3, 1,3, 2,3, 3,3, 3,2, 3,1, 3,0,
			3,-1, 3,-2, 3,-3, 2,-3, 1,-3, 0,-3, -1,-3, -2,-3
	};
	

	num = 0;

	memset(singuArr, 0, sizeof(singuArr));				//初始化奇异点数组，清零

	for(y = 3; y < Height-3; y++)
	{
		for(x = 3; x < Width-3; x++)					//遍历整幅图
		{
			pOriMap = lpOrient + y*Width + x;			//获得某点的方向场指针
			oriV = *pOriMap;							//获取某点的方向场的值

			if(oriV == 255)								//若是背景区域，则跳入下一个循环
			{
				continue;
			}

			fg = false;									
			for(i = 0; i < 24; i++)
			{
				if(pOriMap[D7[i][1]*Width + D7[i][0]]==255)
				{
					fg = true;
					break;
				}
			}
			if(fg)
			{
				continue;
			}

			sum1 = 0;
			for(i = 0; i < 8; i++)
			{
				a1 = pOriMap[D3[i][1]*Width + D3[i][0]]/24;
				a2 = pOriMap[D3[(i+1)%8][1]*Width + D3[(i+1)%8][0]]/24;
				d = getOriChange(a1, a2, flag);
				
				if(abs(d) > 5)
				{
					break;
				}
				
				sum1 += d;
			}
			sum2 = 0;
			for(i = 0; i < 12; i++)
			{
				a1 = pOriMap[D5[i][1]*Width + D5[i][0]]/24;
				a2 = pOriMap[D5[(i+1)%12][1]*Width + D5[(i+1)%12][0]]/24;
				d = getOriChange(a1, a2, flag);
				
				if(abs(d) > 5)
				{
					break;
				}
				
				sum2 += d;
			}
		    
			if(flag == -1)									//中心点
			{
				value = -10;
			}
			else if(flag == 1)								//三角点
			{
				value = 10;
			}
			if(sum2 == value && sum1 == value)
			{
				bFound = false;
				for(i = 0; i < num; i++)
				{
					dis = sqrt((double)((x - singuArr[i].x)*(x - singuArr[i].x) +
						(y - singuArr[i].y)*(y - singuArr[i].y)));
					if(dis < 4)
					{
						singuArr[i].x = (singuArr[i].x + x)/2.0;
						singuArr[i].y = (singuArr[i].y + y)/2.0;
						bFound = true;
						break;
					}

				}
				if(!bFound)
				{
					singuArr[num].x = x;
					singuArr[num].y = y;
					num++;
					if(num >= MAX_SINGULARYNUM)				//若奇异点数量超过最大限制，则停止寻找奇异点
					{
						goto next;
					}
				}

			}
		}
	}

next:

	int  trilen = 16;
	int N = 0;											//奇异点的个数
	for(i = 0; i < num; i++)								//将找到的奇异点存入输入数组
	{
		//lpArr[*lpNum + i].x = (long)singuArr[i].x;
		//lpArr[*lpNum + i].y = (long)singuArr[i].y;	

		int x = (long)singuArr[i].x;
		int y = (long)singuArr[i].y;
		
		if (*(g_lpDivide + y * Width + x) == 255) 
			continue;

		if (((x + 0.0) / Width < 0.1) || ((x + 0.0) / Width > 0.9)) 
			continue;

		if (((y + 0.0) / Height < 0.1 ) || ((y + 0.0) / Height > 0.9))
			continue;

		

		g_Feature.MinutiaArr[g_Feature.MinutiaNum + N].x = x;
		g_Feature.MinutiaArr[g_Feature.MinutiaNum + N].y = y;

		g_Feature.MinutiaArr[g_Feature.MinutiaNum + N].Type = (flag == -1) ? VF_MINUTIA_CORE : VF_MINUTIA_DELTA;				
		g_Feature.MinutiaArr[g_Feature.MinutiaNum + N].Direction = 0;				

		N++;
	}

	g_Feature.MinutiaNum += N;

	return 0;
}


int getOriChange(int angle1, int angle2, char flag)
{
	int  d;
	
	d = angle2 - angle1;
	if(flag >= 1)
	{
		if(d < 0)
		{
			d += 10;
		}
		
	}
	else if(flag <= -1)
	{
		if(d > 0)
		{
			d -= 10;
		}
	}
	
	return d;
}


//
//	VF_FeatureEncode: 对指纹特征进行压缩编码
//
VF_RETURN VF_FeatureEncode(FEATUREPTR lpFeature, uint8 *lpData, sint32 *lpSize)
{
	///////////////////////////////////////////////////////////////////////
	//	lpFeature: [in] 要编码的指纹特征指针
	//  lpData:	[out] 编码后的指纹特征数据缓冲区指针
	//  lpSize:	[out] 编码后的指纹特征大小
	///////////////////////////////////////////////////////////////////////
	
	sint32 re;
	
	// 压缩编码
	re = EncodeFeature(lpFeature, lpData);
	if(re == 0)
		return VF_FEATUREENCODE_ERR;
	
	*lpSize = re;
	
	return VF_OK;
}

//
//	EncodeFeature: 对指纹特征进行压缩编码
//
sint32	EncodeFeature(FEATUREPTR lpFeature, uint8 *lpData)
{
	/////////////////////////////////////////////////////////////////////
	//	lpFeature: [in] 要编码的指纹特征指针
	//  lpData: [out] 压缩编码后的指纹特征缓冲区指针
	/////////////////////////////////////////////////////////////////////
	sint32	i;
	sint32	totalLen = 0;
	sint32	len = 0;
	sint32	x, y, o;
	uint8	v, t, mn;
	sint32  boSize = 0;
	
	if(lpData == NULL || lpFeature == NULL)
		return 0;
	
	// 特征点数目
	mn = (uint8)lpFeature->MinutiaNum;
	// 特征总长度
	totalLen = 4 + 7*mn;////////7*mn
	// 第一个字节为特征总长度
	lpData[0] = (uint8)(totalLen / 256);
	lpData[1] = (uint8)(totalLen-lpData[0]*256);
	
	// 第二个字节为特征点数目
	lpData[2] = mn;
	
	len = 3;
	
	// 对每个特征点进行压缩
	for(i = 0; i < mn; i++)
	{
		x = lpFeature->MinutiaArr[i].x;		// 10位表示
		y = lpFeature->MinutiaArr[i].y;		// 10位表示
		o = lpFeature->MinutiaArr[i].Direction; // 9位表示
		t = (uint8)lpFeature->MinutiaArr[i].Type;	// 3位表示
		lpData[len] = (uint8)(x >> 2);
		lpData[len+1] = (uint8)((x & 0x3) << 6) + (uint8)(y >> 4);
		lpData[len+2] = (uint8)((y & 0xF) << 4) + (uint8)(o >> 5);
		lpData[len+3] = (uint8)((o & 0x1F) << 3) + (uint8)(t & 0x7);
		lpData[len+4] = (uint8)lpFeature->MinutiaArr[i].Triangle[0];
		lpData[len+5] = (uint8)lpFeature->MinutiaArr[i].Triangle[1];
		lpData[len+6] = (uint8)lpFeature->MinutiaArr[i].Triangle[2];
		
		len += 7;
	}
	
	// 计算校验位
	v = 0;
	for(i = 0; i < totalLen-1; i++)
	{
		v = v ^ lpData[i];
	}
	// 最后一个字节放校验字节
	lpData[len] = v;
	
	
	return totalLen;
}


int FPA_PatternMatch(BYTE *lpFeature1, BYTE *lpFeature2, int *lpScore)
{
	return PatternMatch(lpFeature1, lpFeature2, lpScore);	
}


//
// VerifyMatch: 两个指纹特征间的比对
//
 int PatternMatch(BYTE *lpFeature1, BYTE *lpFeature2, int *lpScore)
{
	//////////////////////////////////////////////////////////////////////////
	//	lpFeature1:		[in] 第一个指纹特征
	//	lpFeature2:		[in] 第二个指纹特征
	//	lpScore:		[out] 比对的相似度
	//	FastMode:		[in] 是否进行快速模式比对
	//////////////////////////////////////////////////////////////////////////
	// TODO: Add your implementation code here
	VF_RETURN	re;
	MATCHRESULT mr;
	FEATURE		feat1, feat2;
	
	// 第一个指纹特征的解码
	re = VF_FeatureDecode(lpFeature1, &feat1);
	if(re != VF_OK)
		return re;
	
	// 第二个指纹特征的解码
	re = VF_FeatureDecode(lpFeature2, &feat2);
	if(re != VF_OK)
		return re;
	
	*lpScore = 0;
	
	bool FastMode = true;
	
	if(FastMode)
	{
		// 快速模式的比对
		VF_VerifyMatch(&feat1, &feat2, &mr, VF_MATCHMODE_IDENTIFY);
	}
	else
	{
		// 精确模式的比对
//		VF_VerifyMatch(&feat1, &feat2, &mr, VF_MATCHMODE_VERIFY);
	}
	
	// 匹配的相似度
	if(mr.MMCount < 8)
		*lpScore = 0;
	else
		*lpScore = mr.Similarity;
	
	return 0;
}


 //
 //	VF_FeatureDecode: 对指纹特征进行解码
 //
 VF_RETURN VF_FeatureDecode(uint8 *lpData, FEATUREPTR lpFeature)
 {
	 ///////////////////////////////////////////////////////////////////////
	 //  lpData:	[in] 要解码的指纹特征数据缓冲区指针
	 //  lpFeature:	[out] 解码后的指纹特征
	 ///////////////////////////////////////////////////////////////////////
	 
	 sint32 re;
	 // 解码
	 re = DecodeFeature(lpData, lpFeature);
	 
	 if(re != 0)
		 return VF_FEATUREDECODE_ERR;
	 
	 return VF_OK;
}

 //
 //	DecodeFeature: 对指纹特征进行解码
 //
 sint32	DecodeFeature(uint8 *lpData, FEATUREPTR lpFeature)
 {
	 /////////////////////////////////////////////////////////////////////
	 //  lpData: [in] 压缩编码的指纹特征缓冲区指针
	 //	lpFeature: [out] 解码后的指纹特征指针
	 /////////////////////////////////////////////////////////////////////
	 sint32	i;
	 sint32	totalLen = 0;
	 sint32	len = 0;
	 uint8	v;
	 sint32	boSize = 0;
	 if(lpData == NULL || lpFeature == NULL)
		 return 1;
	 
	 memset((void *)lpFeature, 0, sizeof(FEATURE));
	 // 第一个字节为特征总长
	 totalLen = (sint32)(lpData[0]*256 + lpData[1]);
	 // 计算校验位
	 v = 0;
	 for(i = 0; i < totalLen; i++)
	 {
		 v = v ^ lpData[i];
	 }
	 if(v != 0)	// 校验失败则返回错误
		 return 2;
	 
	 // 第二个字节为指纹特征点数目
	 lpFeature->MinutiaNum = (uint8)lpData[2]; 
	 
	 len = 3;
	 
	 // 解码
	 for(i = 0; i < lpFeature->MinutiaNum; i++)
	 {
		 lpFeature->MinutiaArr[i].x = (sint32)(((sint32)lpData[len])<<2) + 
			 (sint32)(((sint32)(lpData[len+1] & 0xC0))>>6);
		 lpFeature->MinutiaArr[i].y = (sint32)(((sint32)(lpData[len+1] & 0x3F))<<4) + 
			 (sint32)(((sint32)(lpData[len+2] & 0xF0))>>4);
		 lpFeature->MinutiaArr[i].Direction = (sint32)(((sint32)(lpData[len+2] & 0xF))<<5) + 
			 (sint32)(((sint32)(lpData[len+3] & 0xF8))>>3);
		 lpFeature->MinutiaArr[i].Type = (uint8)(lpData[len+3] & 0x7);
		 lpFeature->MinutiaArr[i].Triangle[0] = lpData[len+4];
		 lpFeature->MinutiaArr[i].Triangle[1] = lpData[len+5];
		 lpFeature->MinutiaArr[i].Triangle[2] = lpData[len+6];
		 
		 len += 7;
	 }
	 
	 return 0;
 }


 //
 // VF_VerifyMatch: 两个指纹特征的比对
 //
 BOOL	VF_VerifyMatch(FEATUREPTR lpFeature1, FEATUREPTR lpFeature2, 
	 PMATCHRESULT lpMatchResult, VF_FLAG matchMode)
 {
	 ///////////////////////////////////////////////////////////////////////
	 //  lpFeature1:	[in] 第一个指纹特征
	 //  lpFeature2:	[in] 第二个指纹特征
	 //  lpMatchResult:	[out] 比对结果
	 //  matchMode:	[in] 比对模式
	 ///////////////////////////////////////////////////////////////////////
	 
	 // 比对
	 verify(lpFeature1, lpFeature2, lpMatchResult, matchMode);
	 
	 // 默认阈值为50。相似度>=50则认为比对成功，否则比对失败,
	 // 一般情况下，在35以上即可认为相似, 为安全起见，最好在50-100
	 if(lpMatchResult->Similarity >= 50)
		 return TRUE;
	 else
		 return FALSE;
 }

 //
 //	verify : 指纹比对
 //
 void	verify(FEATUREPTR lpFeature, FEATUREPTR lpTemplate, PMATCHRESULT lpMatchResult,
	 VF_FLAG matchMode)
 {
	 /////////////////////////////////////////////////////////////////////////////
	 //	lpFeature: [in] 要比对的第一个指纹特征指针
	 //	lpTemplate: [in] 要比对的第二个指纹特征指针
	 //	lpMatchResult: [out] 比对结果指针
	 //	matchMode: [in] 比对模式
	 /////////////////////////////////////////////////////////////////////////////
	 
	 MATCHRESULT globalMatchResult;
	 sint32		score = 0;
	 
	 //全局比对
	 globalMatch(lpFeature, lpTemplate, &globalMatchResult, matchMode);
	 //patternMatch(lpFeature, lpTemplate, &globalMatchResult, matchMode);
	 *lpMatchResult = globalMatchResult;
	 //如果匹配特征点数较少，则对比对结果相似度进行修正
	 if(matchMode != VF_MATCHMODE_IDENTIFY && lpMatchResult->MMCount < 15)
	 {
		 score = (sint32)(lpMatchResult->Similarity*sin(lpMatchResult->MMCount*PI/30.0) + 0.5);
		 lpMatchResult->Similarity = score;
	 }
	 
}


 //
//	globalMatch: 指纹特征的全局比对
//
void  globalMatch(FEATUREPTR lpFeature, FEATUREPTR lpTemplate, 
				  PMATCHRESULT lpMatchResult, VF_FLAG matchMode)
{
/////////////////////////////////////////////////////////////////////////////
//	lpFeature: [in] 要比对的第一个指纹特征指针
//	lpTemplate: [in] 要比对的第二个指纹特征指针
//	lpMatchResult: [out] 比对结果指针
//	matchMode: [in] 比对模式
/////////////////////////////////////////////////////////////////////////////
	sint32	m, n, a1, a2;
	sint32	rotation;		// 旋转角度
	sint32	transx, transy;	// 位置偏移
	FEATURE	alignFeature;	// 对齐后的指纹特征
	MATCHRESULT alignMax;	// 相似度最大的比对结果
	MATCHRESULT globalMatchResult;	// 比对结果
	sint32  agate = 8;		// 三角拓扑结构角度误差
	sint32  num = 0;
	// 初始化最好的比对结果
	alignMax.Similarity = 0;
	alignMax.MMCount = 0;
	alignMax.Rotation = 0;
	alignMax.TransX = 0;
	alignMax.TransY = 0;


	// 对相同类型的指纹特征两两作为同一个指纹特征进行对齐比对
	for(n = 0; n < lpTemplate->MinutiaNum; n++)
	{
		for(m = 0; m < lpFeature->MinutiaNum; m++)
		{
			// 不同类型则不比对
			if(lpFeature->MinutiaArr[m].Type != lpTemplate->MinutiaArr[n].Type)
				continue;
			if(matchMode == VF_MATCHMODE_IDENTIFY)
			{
				// 特征点三角拓扑结构比对，相似则进行配准
				if(lpFeature->MinutiaArr[m].Triangle[0] != 255 && lpTemplate->MinutiaArr[n].Triangle[0] != 255)
				{
					a1 = GetJiajiao(lpFeature->MinutiaArr[m].Triangle[0], lpFeature->MinutiaArr[m].Direction % 180);
					a2 = GetJiajiao(lpTemplate->MinutiaArr[n].Triangle[0], lpTemplate->MinutiaArr[n].Direction % 180);
					if(abs(a1-a2)>agate)
						continue;
				}
				if(lpFeature->MinutiaArr[m].Triangle[0] != 255 && lpTemplate->MinutiaArr[n].Triangle[0] != 255 &&
					lpFeature->MinutiaArr[m].Triangle[1] != 255 && lpTemplate->MinutiaArr[n].Triangle[1] != 255)
				{
					a1 = GetJiajiao(lpFeature->MinutiaArr[m].Triangle[0], lpFeature->MinutiaArr[m].Triangle[1]);
					a2 = GetJiajiao(lpTemplate->MinutiaArr[n].Triangle[0], lpTemplate->MinutiaArr[n].Triangle[1]);
					if(abs(a1-a2)>agate)
						continue;
				}
				if(lpFeature->MinutiaArr[m].Triangle[2] != 255 && lpTemplate->MinutiaArr[n].Triangle[2] != 255 &&
					lpFeature->MinutiaArr[m].Triangle[1] != 255 && lpTemplate->MinutiaArr[n].Triangle[1] != 255)
				{
					a1 = GetJiajiao(lpFeature->MinutiaArr[m].Triangle[1], lpFeature->MinutiaArr[m].Triangle[2]);
					a2 = GetJiajiao(lpTemplate->MinutiaArr[n].Triangle[1], lpTemplate->MinutiaArr[n].Triangle[2]);
					if(abs(a1-a2)>agate)
						continue;
				}
				if(lpFeature->MinutiaArr[m].Triangle[0] != 255 && lpTemplate->MinutiaArr[n].Triangle[0] != 255 &&
					lpFeature->MinutiaArr[m].Triangle[2] != 255 && lpTemplate->MinutiaArr[n].Triangle[2] != 255)
				{
					a1 = GetJiajiao(lpFeature->MinutiaArr[m].Triangle[0], lpFeature->MinutiaArr[m].Triangle[2]);
					a2 = GetJiajiao(lpTemplate->MinutiaArr[n].Triangle[0], lpTemplate->MinutiaArr[n].Triangle[2]);
					if(abs(a1-a2)>agate)
						continue;
				}
			}
			alignFeature.MinutiaNum = 0;
			// 旋转角度
			rotation = GetAngleDis(lpFeature->MinutiaArr[m].Direction, 
									lpTemplate->MinutiaArr[n].Direction);
			// 位置偏移
			transx = (lpTemplate->MinutiaArr[n].x - lpFeature->MinutiaArr[m].x);
			transy = (lpTemplate->MinutiaArr[n].y - lpFeature->MinutiaArr[m].y);
			
			// 将lpFeature与lpTemplate对齐
			align(lpFeature, &alignFeature, &lpFeature->MinutiaArr[m],
					rotation, transx, transy);
			// 将两个对齐的指纹特征进行比对
			alignMatch(&alignFeature, lpTemplate, &globalMatchResult, matchMode);
			// 如果比对结果比最好的比对结果更好，则更新alignMax
			if(globalMatchResult.Similarity > alignMax.Similarity)
			{
				alignMax.MMCount = globalMatchResult.MMCount;
				alignMax.Similarity = globalMatchResult.Similarity;
				alignMax.Rotation = rotation;
				alignMax.TransX = transx;
				alignMax.TransY = transy;
				
				// 如果是快速比对模式，则相似度达到一定程度则退出
				if(matchMode == VF_MATCHMODE_IDENTIFY && alignMax.MMCount >= 8 )
				{
					if(alignMax.Similarity > 100)
					{
						*lpMatchResult = alignMax;
						return;
					}
				}
			}
		}
	}
	
	//最终比对结果
	*lpMatchResult = alignMax;
}


//
//	align: 将指纹特征按一定的角度和位置偏移进行坐标变换
//
void align(FEATUREPTR lpFeature, FEATUREPTR lpAlignedFeature, MINUTIAPTR lpFeatureCore,
				  sint32 rotation, sint32 transx, sint32 transy)
{
///////////////////////////////////////////////////////////////////////
//  lpFeature:	[in] 要变换的指纹特征
//  lpAlignedFeature:	[out] 进行坐标变换后的指纹特征
//  lpFeatureCore:	[in] 旋转变换的中心特征点
//  rotation:	[in] 旋转角度
//  transx:	[in] 水平偏移
//  transy: [in] 垂直偏移
///////////////////////////////////////////////////////////////////////

	sint32  i;
	sint32  x, y;
	sint32  cx, cy;
	double  rota, sinv, cosv;

	// 复制整个结构信息
	*lpAlignedFeature = *lpFeature;
	
	// 坐标转换的中心点坐标
	cx = lpFeatureCore->x;
	cy = lpFeatureCore->y;
	// 旋转的弧度
	rota = rotation/EPI;
	// 旋转弧度的sin值
	sinv = sin(rota);
	// 旋转弧度的cos值
	cosv = cos(rota);
	for(i = 0; i < lpFeature->MinutiaNum; i++)
	{
		x = lpFeature->MinutiaArr[i].x;
		y = lpFeature->MinutiaArr[i].y;
		//  坐标转换后的新坐标
		lpAlignedFeature->MinutiaArr[i].x = (sint32)(cx + cosv*(x-cx) - sinv*(y-cy) + transx + 0.5);
		lpAlignedFeature->MinutiaArr[i].y = (sint32)(cy + sinv*(x-cx) + cosv*(y-cy) + transy + 0.5);
		// 旋转后特征点的新方向
		lpAlignedFeature->MinutiaArr[i].Direction = (lpFeature->MinutiaArr[i].Direction + rotation) % 360;
	}

}

//
// alignMatch: 两个坐标系对齐的指纹特征进行比对
//
void alignMatch(FEATUREPTR lpAlignFeature, FEATUREPTR lpTemplate, 
				PMATCHRESULT lpMatchResult, VF_FLAG matchMode)
{
	sint32	i, j;
	uint8	flagA[MAXMINUTIANUM];	// 标记lpAlignFeature中特征点是否已经有匹配对象
	uint8	flagT[MAXMINUTIANUM];	// 标记lpTemplate中特征点是否已经有匹配对象
	sint32	x1, y1, x2, y2;
	sint32  dis, angle;
	sint32  score, matchNum, s;
	sint32	num1, num2;
	sint32  step = 1;
	num1 = lpAlignFeature->MinutiaNum;
	num2 = lpTemplate->MinutiaNum;
	// 标记清零
	memset(flagA, 0, MAXMINUTIANUM);
	memset(flagT, 0, MAXMINUTIANUM);

	score = 0;		// 总分清零
	matchNum = 0;	// 匹配特征点数清零



	// 相同类型特征点的匹配分数
	for(i = 0; i < lpTemplate->MinutiaNum; i++)
	{
		if(flagT[i])	// 是否已有匹配对象
			continue;
		for(j = 0; j < lpAlignFeature->MinutiaNum; j++)
		{
			if(flagA[j])	// 是否已有匹配对象
				continue;
			// 特征点类型是否相同
			if(lpTemplate->MinutiaArr[i].Type != lpAlignFeature->MinutiaArr[j].Type)
				continue;
			// 特征点方向夹角
			angle = AngleAbs360(lpTemplate->MinutiaArr[i].Direction, 
								lpAlignFeature->MinutiaArr[j].Direction);
			// 夹角>=10则不匹配
			if(angle >= 10)
				continue;
			x1 = lpTemplate->MinutiaArr[i].x;
			y1 = lpTemplate->MinutiaArr[i].y;
			x2 = lpAlignFeature->MinutiaArr[j].x;
			y2 = lpAlignFeature->MinutiaArr[j].y;
			// 水平距离>=10则不匹配
			if(abs(x1-x2) >= 10)
				continue;
			// 垂直距离>=10则不匹配
			if(abs(y1-y2) >= 10)
				continue;
			// 两特征点间的距离
			dis = DisTbl[abs(y1-y2)][abs(x1-x2)];
			// 距离>=10则不匹配
			if(dis >= 10)
				continue;
			// 对这两个特征点做标记，表示已经有匹配对象
			flagA[j] = 1;
			flagT[i] = 1;
			// 总分加上此两个特征点的匹配分数
			// 此表明dis,angle越大，分数越小
			score += (10-angle);
			score += (10-dis);
			// 匹配特征点数加一
			matchNum++;
			
			// 如果是快速比对模式
			if(matchMode == VF_MATCHMODE_IDENTIFY && matchNum >= 8)
			{
				// 计算相似度
				s = 4 * score * matchNum * MAXMINUTIANUM / ((num1 + num2) * ( num1 + num2));
				if(s > 100)  // 相似度足够大则返回比对结果
				{
					lpMatchResult->MMCount = matchNum;
					lpMatchResult->Rotation = 0;
					lpMatchResult->Similarity = s;
					lpMatchResult->TransX = 0;
					lpMatchResult->TransX = 0;
					return;
				}
			}

		}
	}

	if(matchMode != VF_MATCHMODE_IDENTIFY)
	{
		// 由于图像处理的误差导致可能端点处理成叉点或叉点处理成端点，假设概率为50%，计算
		// 此种情况的分数
		for(i = 0; i < lpTemplate->MinutiaNum; i++)
		{
			if(flagT[i])	// 是否已有匹配对象
				continue;
			for(j = 0; j < lpAlignFeature->MinutiaNum; j++)
			{
				if(flagA[j])	// 是否已有匹配对象
					continue;
				// 是否类型不同
				if(lpTemplate->MinutiaArr[i].Type == lpAlignFeature->MinutiaArr[j].Type)
					continue; 
				// 特征点方向夹角
				angle = AngleAbs360(lpTemplate->MinutiaArr[i].Direction, 
									lpAlignFeature->MinutiaArr[j].Direction);
				// 夹角>=10则不匹配
				if(angle >= 10)
					continue;
				x1 = lpTemplate->MinutiaArr[i].x;
				y1 = lpTemplate->MinutiaArr[i].y;
				x2 = lpAlignFeature->MinutiaArr[j].x;
				y2 = lpAlignFeature->MinutiaArr[j].y;

				// 水平距离>=10则不匹配
				if(abs(x1-x2) >= 10)
					continue;
				// 垂直距离>=10则不匹配
				if(abs(y1-y2) >= 10)
					continue;
				// 两特征点间的距离
				dis = DisTbl[abs(y1-y2)][abs(x1-x2)];
				// 距离>=10则不匹配
				if(dis >= 10)
					continue;
				// 对这两个特征点做标记，表示已经有匹配对象
				flagA[j] = 1;
				flagT[i] = 1;
				// 总分加上此两个特征点的匹配分数
				score += ((10-angle)/2);
				score += ((10-dis)/2);
				// 匹配特征点数加一
				matchNum++;

			}
		}								
	}
	// 计算相似度，返回比对结果
	s = 4 * score * matchNum * MAXMINUTIANUM / ((num1+num2)*(num1+num2));

	lpMatchResult->MMCount = matchNum;
	lpMatchResult->Rotation = 0;
	lpMatchResult->Similarity = s;
	lpMatchResult->TransX = 0;
	lpMatchResult->TransX = 0;

}


//
//	AngleAbs360: 求两个角度的夹角(0 - 180)
//
sint32  AngleAbs360(sint32 angle1, sint32 angle2)
{
	/////////////////////////////////////////////////////////////////////////
	//	angle1: [in] 角度一 （0 - 360）
	//	angle2: [in] 角度二 （0 - 360）
	/////////////////////////////////////////////////////////////////////////
	sint32 a;
	a = abs(angle1 - angle2);
	if(a > 180)
	{
		return (360 - a);
	}
	else
	{
		return a;
	}
}


void CDSplitView::OnOpenFileOne() 
{
	// TODO: Add your command handler code here
		CFileDialog dlg(TRUE,"bmp",".bmp",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"Bitmap (*.BMP)|*.BMP||");/////////打开文件选择对话框
//	HBITMAP m_hImage;//////定义位图变量

	if (dlg.DoModal() != IDOK) return;//////////点击了取消键

		ImagePathName1 = dlg.GetPathName();				/////////////点击了确定键
		
	
	int lpSize1;
	FPA_CreateImage(lpImage1);
	FPA_LoadImage(ImagePathName1, lpImage1, &lpData1, &Width1, &Height1);
	

	FPA_AnalyzeFeature_File(ImagePathName1, lpFeature1, &lpSize1);
	int i;
	CString   stemp,str;   
	
	str   =   "";   
	for(i=0;i<lpSize1;i++)
	{
		stemp.Format("%d ",lpFeature1[i]);
		str+=stemp;
	}
		filename = ImagePathName1;
		Invalidate();
}



void CDynSplitView2::OnOpenFileTwo() 
{
	// TODO: Add your command handler code here
		CFileDialog dlg(TRUE,"bmp",".bmp",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"Bitmap (*.BMP)|*.BMP||");

	if (dlg.DoModal() != IDOK) return;

		ImagePathName2 = dlg.GetPathName();				


   int lpSize2;
	FPA_CreateImage(lpImage2);
	FPA_LoadImage(ImagePathName2, lpImage2, &lpData2, &Width2, &Height2);			
 
	
	FPA_AnalyzeFeature_File(ImagePathName2, lpFeature2, &lpSize2);
	int j;
	CString   stemp2,str2;   
	
	str2   =   "";   
	for(j=0;j<lpSize2;j++)
	{
		stemp2.Format("%d ",lpFeature2[j]);
		str2+=stemp2;
	}
	filename = ImagePathName2;
	Invalidate();
	
}





void CDynSplitView2::OndeleteNoise2() 
{
	// TODO: Add your command handler code here
	filename = "C:\\3.bmp";
	Invalidate();
}

void CDynSplitView2::Onthin2() 
{
	// TODO: Add your command handler code here
	filename = "C:\\5.bmp";
	Invalidate();
	
}

void CDynSplitView2::OnLvBo2() 
{
	// TODO: Add your command handler code here
	filename = "C:\\1.bmp";
		Invalidate();
	
}

void CDynSplitView2::Ondirection2() 
{
	// TODO: Add your command handler code here
	filename = "C:\\0.bmp";
	Invalidate();
	
}


void CDynSplitView2::Onmatch() 
{
	// TODO: Add your command handler code here

	int score;

	FPA_PatternMatch(lpFeature1, lpFeature2, &score);
	//FPA_Match(lpFeature1, lpFeature2, &score);


	
	if (score > 70)
	{
		AfxMessageBox("Same Fingerprint!");
	}
	else
	{
		AfxMessageBox("Different Fingerprints");
	}
	Invalidate();
	
}







void CDSplitView::OnLvBo1() 
{
	// TODO: Add your command handler code here
	filename = "C:\\1.bmp";
	Invalidate();
}

void CDSplitView::Onthin1() 
{
	// TODO: Add your command handler code here
	filename = "C:\\5.bmp";
	Invalidate();
}


void CDSplitView::Ondirection1() 
{
	// TODO: Add your command handler code here
	filename = "C:\\0.bmp";
	Invalidate();
	
}



