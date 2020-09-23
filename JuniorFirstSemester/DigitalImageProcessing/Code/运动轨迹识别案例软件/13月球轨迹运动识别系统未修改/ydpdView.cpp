// ydpdView.cpp : implementation of the CYdpdView class
//

#include "stdafx.h"
#include "ydpd.h"

#include "ydpdDoc.h"
#include "ydpdView.h"
#include "DIB.h"
#include "Track.h"
#include "ydgj.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CYdpdView
DIB cDib;
extern HANDLE hDIBBK1;
extern HANDLE hDIBBK2;
extern HANDLE hDIBBKGray;
extern HANDLE hDIBBKGradient;
HANDLE hDIBCurrent = NULL;
CPoint ImportantPoint,ImportantPoint2,ImpPoiCur;
CPoint ImportantPointSecond;
int ImportantColorInfo[RADIUS*2+1][RADIUS*2+1][3];
int locax,locay;

IMPLEMENT_DYNCREATE(CYdpdView, CScrollView)

BEGIN_MESSAGE_MAP(CYdpdView, CScrollView)
	//{{AFX_MSG_MAP(CYdpdView)
	ON_COMMAND(ID_MENU_BK_FIRST, OnMenuBkFirst)
	ON_COMMAND(ID_MENU_BK_SECOND, OnMenuBkSecond)
	ON_COMMAND(ID_MENU_BK_GRAY, OnMenuBkGray)
	ON_COMMAND(ID_MENU_GRADIENT, OnMenuGradient)
	ON_COMMAND(ID_MENU_PIPEIZHONGXIN, OnMenuPipeizhongxin)
	ON_COMMAND(ID_MENU_TEZHENGQUYU, OnMenuTezhengquyu)
	ON_COMMAND(ID_MENU_PIPEI, OnMenuPipei)
	ON_COMMAND(ID_MEDIFILTER, OnMedifilter)
	ON_COMMAND(ID_MENU_FILElOAD, OnMENUFILElOAD)
	ON_COMMAND(ID_MENU_YDPD_PIPEI, OnMenuYdpdPipei)
	ON_COMMAND(ID_MENU_YDPD_MEDI, OnMenuYdpdMedi)
	ON_COMMAND(ID_MENU_YDPD_LKTQ, OnMenuYdpdLktq)
	ON_COMMAND(ID_MENU_YDPD_EDGE_GET, OnMenuYdpdEdgeGet)
	ON_COMMAND(ID_MENU_YDPD_BLACKWHITE, OnMenuYdpdBlackwhite)
	ON_COMMAND(ID_MENU_YDPD_THING, OnMenuYdpdThing)
	ON_COMMAND(ID_MENU_YDPD_DELETESCATER, OnMenuYdpdDeletescater)
	ON_COMMAND(ID_MENU_YDPD_GUIJI, OnMenuYdpdGuiji)
	ON_COMMAND(ID_MENU_YDPD_CENTER, OnMenuYdpdCenter)
	ON_COMMAND(ID_MENU_YCX, OnMenuYcx)
	ON_COMMAND(ID_SECOND_PIPEI, OnSecondPipei)
	ON_COMMAND(ID_MENU_PENGZHANG, OnMenuPengzhang)
	ON_COMMAND(ID_MENU_GETEDGE, OnMenuGetedge)
	ON_COMMAND(ID_MENU_YDPD_GRAY, OnMenuYdpdGray)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CYdpdView construction/destruction

CYdpdView::CYdpdView()
{
	hDIBBK1 = NULL;
	hDIBBK2 = NULL;
	hDIBBKGray = NULL;
	hDIBBKGradient = NULL;
	isTeZhengZhi = false;
	isBKChonsen = false;
	m_Pointnum =0;

}

CYdpdView::~CYdpdView()
{
}

BOOL CYdpdView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CYdpdView drawing

void CYdpdView::OnDraw(CDC* pDC)
{
	CYdpdDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(hDIBBK1 && hDIBBKGray== NULL)
	{
//		MessageBox("a");
		cDib.PaintDIBTrue(pDC->GetSafeHdc(),CRect(0,0,m_bk_first_width,m_bk_first_height),
		hDIBBK1,CRect(0,0,m_bk_first_width,m_bk_first_height),SRCCOPY);
	}
	if(hDIBBKGray && hDIBBKGradient == NULL)
	{
//		MessageBox("b");
		cDib.PaintDIBTrue(pDC->GetSafeHdc(),CRect(0,0,m_bk_first_width,m_bk_first_height),
		hDIBBKGray,CRect(0,0,m_bk_first_width,m_bk_first_height),SRCCOPY);
	}
	if(hDIBBKGradient)
	{
//		MessageBox("c");
		cDib.PaintDIBTrue(pDC->GetSafeHdc(),CRect(0,0,m_bk_first_width,m_bk_first_height),
		hDIBBKGradient,CRect(0,0,m_bk_first_width,m_bk_first_height),SRCCOPY);
	}
	if(hDIBBK2)
	{		
//		MessageBox("d");
		SetScrollSizes(MM_TEXT,CSize(m_bk_first_width*2+20,m_bk_first_height*2+10));	
		//SetScrollSizes(MM_TEXT,CSize(m_bk_first_width*2+20,m_bk_first_height));
		cDib.PaintDIBTrue(pDC->GetSafeHdc(),CRect(m_bk_first_width+5,0,m_bk_first_width*2+5,m_bk_first_height),
		hDIBBK2,CRect(0,0,m_bk_first_width,m_bk_first_height),SRCCOPY);
	}
	if(hDIBCurrent)
	{
//		MessageBox("e");
		cDib.PaintDIBTrue(pDC->GetSafeHdc(),CRect(m_bk_first_width+5,m_bk_first_height+5,m_bk_first_width*2+5,m_bk_first_height*2+5),
		hDIBCurrent,CRect(0,0,m_bk_first_width,m_bk_first_height),SRCCOPY);
		SetScrollSizes(MM_TEXT,CSize(m_bk_first_width*2+20,m_bk_first_height*2+10));
	}
	if(this->isTeZhengZhi)
	{
//		MessageBox("f");
		cDib.PaintDIBTrue(pDC->GetSafeHdc(),CRect(0,m_bk_first_height+10,RADIUS*2+1,m_bk_first_height+10+RADIUS*2+1),
		hDIBBK1,CRect(ImportantPoint.x-RADIUS,m_bk_first_height -ImportantPoint.y-RADIUS,ImportantPoint.x+RADIUS,m_bk_first_height -ImportantPoint.y +RADIUS),SRCCOPY);
	}
		
}

void CYdpdView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CYdpdView printing

BOOL CYdpdView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CYdpdView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CYdpdView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CYdpdView diagnostics

#ifdef _DEBUG
void CYdpdView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CYdpdView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CYdpdDoc* CYdpdView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CYdpdDoc)));
	return (CYdpdDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CYdpdView message handlers

void CYdpdView::OnMenuBkFirst() 
{
	
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,NULL,NULL);
	if(dlg.DoModal() == IDOK)
	{
		CString a;
		a = dlg.GetPathName();
		hDIBBK1 = cDib.LoadDIB(a);
		if(!hDIBBK1)
		{	
			AfxMessageBox("open file error");
			return;
		}
		LPBITMAPINFOHEADER lpbi;
		lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIBBK1);
		this->m_bk_first_width = lpbi->biWidth;
		this->m_bk_first_height = lpbi->biHeight;
		GlobalUnlock(hDIBBK1);
		Invalidate();
	}

}

void CYdpdView::OnMenuBkSecond() 
{
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,NULL,NULL);
	if(dlg.DoModal() == IDOK)
	{
		hDIBBK2 = cDib.LoadDIB(dlg.GetPathName());
		if(!hDIBBK2)
		{	
			AfxMessageBox("open file error");
			return;
		}
			
		Invalidate();
	}
	
}

void CYdpdView::OnMenuBkGray() 
{
	hDIBBKGray = cDib.ToGray(hDIBBK1);
	Invalidate();
	
}

void CYdpdView::OnMenuGradient() 
{
	hDIBBKGradient = cDib.Gradient(hDIBBKGray);
	Invalidate();
	
}

void CYdpdView::OnMenuPipeizhongxin() 
{
	cDib.LocateImporntPoint(hDIBBKGradient,RADIUS,&ImportantPoint);
	Invalidate();
	
}

void CYdpdView::OnMenuTezhengquyu() 
{

	long  lOffset;
	WORD wBytesPerLine;
	LPBYTE lpData;
	GlobalLock(hDIBBK1);
	wBytesPerLine = cDib.BytePerLine(hDIBBK1);
	lpData = cDib.FindDIBBits(hDIBBK1);
	for(int i=-RADIUS;i<=RADIUS;i++)
		for(int j=-RADIUS;j<=RADIUS;j++)
		{
			lOffset = cDib.PixelOffset(i+ImportantPoint.y,j+ImportantPoint.x,wBytesPerLine);
			ImportantColorInfo[i+RADIUS][j+RADIUS][0] = *(lpData+lOffset++);
			ImportantColorInfo[i+RADIUS][j+RADIUS][1] = *(lpData+lOffset++);
			ImportantColorInfo[i+RADIUS][j+RADIUS][2] = *(lpData+lOffset++);
		}
		this->isTeZhengZhi = true;
		GlobalUnlock(hDIBBK1);
		Invalidate();
}

void CYdpdView::OnMenuPipei() 
{
	cDib.MatchImportantPoint(hDIBBK2,ImportantColorInfo,&ImportantPoint2);
	if(cDib.ComPareImg(hDIBBK1,hDIBBK2,ImportantPoint,ImportantPoint2))
	{
		AfxMessageBox("match successed");
		this->isBKChonsen = true;
	}
	else
		AfxMessageBox("match failed");
	Invalidate();
}

void CYdpdView::OnMedifilter() 
{	
	
	if(hDIBBK1)
		cDib.MedianFilterDIB(hDIBBK1);
	if(hDIBBK2)
		cDib.MedianFilterDIB(hDIBBK2);
	Invalidate();
}



void CYdpdView::OnMENUFILElOAD() 
{
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,NULL,NULL);
	if(dlg.DoModal() == IDOK)
	{
		CString a;
		a = dlg.GetPathName();
		hDIBCurrent = cDib.LoadDIB(a);
		if(!hDIBCurrent)
		{	
			AfxMessageBox("open file error");
			return;
		}
			
	
	}
	
}

void CYdpdView::OnMenuYdpdPipei() 
{
	bool kk = cDib.MatchImportantPoint(hDIBCurrent,ImportantColorInfo,&ImportantPoint2);
	
	if(cDib.ComPareImg(hDIBBK1,hDIBCurrent,ImportantPoint,ImportantPoint2))
	{
		AfxMessageBox("match successed");
		this->isBKChonsen = true;
	}
	else
		AfxMessageBox("match failed");
		
	Invalidate();
	
}

void CYdpdView::OnMenuYdpdMedi() 
{
	if(hDIBCurrent)
	{
		cDib.MedianFilterDIB(hDIBCurrent);
		Invalidate();
	}

	
}

void CYdpdView::OnMenuYdpdLktq() 
{

	cDib.CompareImg2(hDIBBK1,hDIBCurrent,ImportantPoint,ImportantPoint2);
	LPBITMAPFILEHEADER lpbi;
	lpbi = (LPBITMAPFILEHEADER)GlobalLock(hDIBCurrent);
	LPBYTE lpData = cDib.FindDIBBits(hDIBCurrent);
	long lOffset;
	WORD wBytesPerLine = cDib.BytePerLine(hDIBCurrent);
	
	for(int i= -RADIUS;i<=RADIUS;i++)
		{
			lOffset = cDib.PixelOffset(i+ImportantPoint2.y,RADIUS+ImportantPoint2.x,wBytesPerLine);
			*(lpData+lOffset++) = 0;
			*(lpData+lOffset++) = 0;
			*(lpData+lOffset++) = 0;
		}
	for( i= -RADIUS;i<=RADIUS;i++)
		{
			lOffset = cDib.PixelOffset(i+ImportantPoint2.y,ImportantPoint2.x-RADIUS,wBytesPerLine);
			*(lpData+lOffset++) = 0;
			*(lpData+lOffset++) = 0;
			*(lpData+lOffset++) = 0;
		}
	for( i= -RADIUS;i<=RADIUS;i++)
		{
			lOffset = cDib.PixelOffset(ImportantPoint2.y-RADIUS,i+ImportantPoint2.x,wBytesPerLine);
			*(lpData+lOffset++) = 0;
			*(lpData+lOffset++) = 0;
			*(lpData+lOffset++) = 0;
		}
	for( i= -RADIUS;i<=RADIUS;i++)
		{
			lOffset = cDib.PixelOffset(RADIUS+ImportantPoint2.y,i+ImportantPoint2.x,wBytesPerLine);
			*(lpData+lOffset++) = 0;
			*(lpData+lOffset++) = 0;
			*(lpData+lOffset++) = 0;
		}
	GlobalUnlock(hDIBCurrent);
	Invalidate();
}

void CYdpdView::OnMenuYdpdEdgeGet() 
{	
	
	LPBITMAPINFOHEADER lpbi;
	int width ,height;
	WORD wBytesPerLine ;
	LPBYTE lpData;
	long lOffset;
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIBCurrent);
	width = lpbi->biWidth;
	height = lpbi->biHeight;
	wBytesPerLine = cDib.BytePerLine(hDIBCurrent);
	lpData = cDib.FindDIBBits(hDIBCurrent);
	for(int i =0;i<height;i++)
		for(int j=0;j<width;j++)
		{
			 lOffset = cDib.PixelOffset(i,j,wBytesPerLine);
			*(lpData+lOffset) =(*(lpData+lOffset))*5; 
			*(lpData+lOffset+1) =(*(lpData+lOffset+1))*5;
			*(lpData+lOffset+2) =(*(lpData+lOffset+2))*5;
		}
		GlobalUnlock(hDIBCurrent);
	hDIBCurrent = cDib.Gradient(hDIBCurrent);
	lpData = cDib.FindDIBBits(hDIBCurrent);
	for(i =0;i<height;i++)
		{
			lOffset = cDib.PixelOffset(i,0,wBytesPerLine);
			*(lpData+lOffset++) =0;
			*(lpData+lOffset++) =0;
			*(lpData+lOffset++) =0;
		}

		for(i =0;i<height;i++)
		{
			lOffset = cDib.PixelOffset(i,width-1,wBytesPerLine);
			*(lpData+lOffset++) =0;
			*(lpData+lOffset++) =0;
			*(lpData+lOffset++) =0;
		}
		for(i =0;i<width;i++)
		{
			lOffset = cDib.PixelOffset(height-1,i,wBytesPerLine);
			*(lpData+lOffset++) =0;
			*(lpData+lOffset++) =0;
			*(lpData+lOffset++) =0;
		}
		for(i =0;i<width;i++)
		{
			lOffset = cDib.PixelOffset(0,i,wBytesPerLine);
			*(lpData+lOffset++) =0;
			*(lpData+lOffset++) =0;
			*(lpData+lOffset++) =0;
		}
	Invalidate();
	
}

void CYdpdView::OnMenuYdpdBlackwhite() 
{
	cDib.WhiteBlack(hDIBCurrent,110);
	LPBITMAPINFOHEADER lpbi;
	int width ,height;
	WORD wBytesPerLine ;
	LPBYTE lpData;
	long lOffset;
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIBCurrent);
	width = lpbi->biWidth;
	height = lpbi->biHeight;
	wBytesPerLine = cDib.BytePerLine(hDIBCurrent);
	lpData = cDib.FindDIBBits(hDIBCurrent);
		for(int i =0;i<height;i++)
		{
			lOffset = cDib.PixelOffset(i,0,wBytesPerLine);
			*(lpData+lOffset++) =0;
			*(lpData+lOffset++) =0;
			*(lpData+lOffset++) =0;
		}

		for(i =0;i<height;i++)
		{
			lOffset = cDib.PixelOffset(i,width-1,wBytesPerLine);
			*(lpData+lOffset++) =0;
			*(lpData+lOffset++) =0;
			*(lpData+lOffset++) =0;
		}
		for(i =0;i<width;i++)
		{
			lOffset = cDib.PixelOffset(height-1,i,wBytesPerLine);
			*(lpData+lOffset++) =0;
			*(lpData+lOffset++) =0;
			*(lpData+lOffset++) =0;
		}
		for(i =0;i<width;i++)
		{
			lOffset = cDib.PixelOffset(0,i,wBytesPerLine);
			*(lpData+lOffset++) =0;
			*(lpData+lOffset++) =0;
			*(lpData+lOffset++) =0;
		}
		GlobalUnlock(hDIBCurrent);
	Invalidate();
}

void CYdpdView::OnMenuYdpdThing() 
{
		cDib.ThinningDIB(hDIBCurrent);
		Invalidate();
}
//函数实现去除图片中离散点的功能
void CYdpdView::OnMenuYdpdDeletescater() 
{
	LPBITMAPINFOHEADER lpbi;
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIBCurrent);
	int width = lpbi->biWidth;
	int height = lpbi->biHeight;
	//令lpdata指向数据区
	LPBYTE lpData = cDib.FindDIBBits(hDIBCurrent);
	//得到图片每行的字节个数
	WORD wBytesPerLine = cDib.BytePerLine(hDIBCurrent);
	long lOffset;
	int lenth;
	bool lab[m_HEIGHT][m_WIDTH];
    //扫描整个图片，进行去离散操作
	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++)
		{	lenth = 0;
		    //得到点在数据区中的偏移
			lOffset = cDib.PixelOffset(i,j,wBytesPerLine);
			if(*(lpData+lOffset) == 255)//象素为白色
			{  //初始化标志数组
				for(int k=0;k<m_HEIGHT;k++)
					for(int kk=0;kk<m_WIDTH;kk++)
						lab[k][kk] = false;
					//初始化连续点长度
					cDib.lenth =0;
					//判断是否为离散点
			if(cDib.IsScaterPoint(j,i,width,height,lpData,wBytesPerLine,3,lab))
			{   //不是是离散点
				*(lpData+lOffset++) = 255;
				*(lpData+lOffset++) = 255;
				*(lpData+lOffset++) = 255;
			}
			else 
			{   //是离散点，把点设置为黑色
				*(lpData+lOffset++) = 0;
				*(lpData+lOffset++) = 0;
				*(lpData+lOffset++) = 0;
			}
			}
			else
			{  //否则设置为黑色
				*(lpData+lOffset++) = 0;
				*(lpData+lOffset++) = 0;
				*(lpData+lOffset++) = 0;
			}

		}
		GlobalUnlock(hDIBCurrent);
		Invalidate();
}




void CYdpdView::OnMenuYdpdGuiji() 
{
	Track  tk;
	
	tk.m_YDGJ.m_Guiji[tk.m_YDGJ.m_Len].x =locax;
    tk.m_YDGJ.m_Guiji[tk.m_YDGJ.m_Len].y = locay;
	tk.m_YDGJ.m_Len++;
	//tk.DoModal();
	
}
//得到物体的中心点
void CYdpdView::OnMenuYdpdCenter() 
{
	
		LPBYTE lpData;
		int height,width;
		LPBITMAPINFOHEADER lpbi;
		WORD wBytesPerLine;
		long lOffset;
		int xsum = 0,ysum=0,pointnum;
		//lpdata指向数据区
		lpData = cDib.FindDIBBits(hDIBCurrent);
		lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIBCurrent);
		//得到图片的长宽信息
		height = lpbi->biHeight;
		width = lpbi->biWidth;
		//得到图片的每行的字节数
		wBytesPerLine = cDib.BytePerLine(hDIBCurrent);
		//初始化 横坐标，纵坐标和点数的值
			xsum =0;ysum =0;pointnum =0;
			//扫描整个图片
			for(int i = 0;i<height;i++)
				for(int j=0;j<width;j++)
				{   
					//得到点在图片中的偏移
					lOffset = cDib.PixelOffset(i,j,wBytesPerLine);
					if(*(lpData+lOffset) !=0)//不是黑色点
					{  
						//增加横坐标，纵坐标的值
						xsum +=j;
						ysum +=i;
						//增加点数值
						pointnum++;
					}
				}
				//得到中心点在数据区中的偏移
				lOffset = cDib.PixelOffset(ysum/pointnum,xsum/pointnum,wBytesPerLine);
				//把中心点设置为绿色
				*(lpData+lOffset++) =0;
				*(lpData+lOffset++) =255;
				*(lpData+lOffset++) =0;
				GlobalUnlock(hDIBCurrent);
				Invalidate();

}

void CYdpdView::OnMenuYcx() 
{
	FILE *fpname;
	char a[15];
	CString aa;
	fpname = fopen("filename.txt","r");
	fscanf(fpname,"%s",aa);
	if(hDIBBK1)
		GlobalFree(hDIBBK1);
				hDIBBK1 = cDib.LoadDIB(aa);
				LPBITMAPINFOHEADER lpbi;
				lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIBBK1);
				this->m_bk_first_width = lpbi->biWidth;
				this->m_bk_first_height = lpbi->biHeight;
				GlobalUnlock(hDIBBK1);
				
				
				
				int num;
				LPBYTE lpData;
				LPBYTE lpDataS;
				int height,width;
	
		WORD wBytesPerLine;
		long lOffset;
		fscanf(fpname,"%d",&num);
		bool lab = false;
		int xsum = 0,ysum=0,pointnum;
		for(int i=0;i<num;i++)
		{
			fscanf(fpname,"%s",a);
			if(hDIBCurrent)
				GlobalFree(hDIBCurrent);
				hDIBCurrent = cDib.LoadDIB(a);
				if(!hDIBCurrent)
			{
				AfxMessageBox("Load DIB file failed");
				fclose(fpname);
				return;
			}
		lpData = cDib.FindDIBBits(hDIBCurrent);
		lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIBCurrent);
		height = lpbi->biHeight;
		width = lpbi->biWidth;
		lpDataS = cDib.FindDIBBits(hDIBBK1);
		wBytesPerLine = cDib.BytePerLine(hDIBBK1);
		for(int i=0;i<height;i++)
			for(int j=0;j<width;j++)
			{
				int cr,cg,cb;
				lOffset = cDib.PixelOffset(i,j,wBytesPerLine);
				cr = abs(*(lpData+lOffset) - *(lpDataS+lOffset));
				cg = abs(*(lpData+lOffset+1) - *(lpDataS+lOffset+1));
				cb = abs(*(lpData+lOffset+2) - *(lpDataS+lOffset+2));
				int gray = (cb*39+cg*50+cr*11)/100;
				*(lpData+lOffset) = gray;
				*(lpData+lOffset+1) = gray;
				*(lpData+lOffset+2) = gray;

			}
			xsum =0;ysum =0;pointnum =0;
			for(i = 0;i<height;i++)
				for(int j=0;j<width;j++)
				{
					lOffset = cDib.PixelOffset(i,j,wBytesPerLine);
					if(*(lpData+lOffset) !=0)
					{
						xsum +=j;
						ysum +=i;
						pointnum++;
					}
				}
			
		this->m_center[this->m_Pointnum].x = xsum/pointnum;
		this->m_center[this->m_Pointnum].y = ysum/pointnum;
		this->m_Pointnum++;
		
						
	
		}
	Track tk;
	for(i=0;i<this->m_Pointnum;i++)
	{
		tk.m_YDGJ.m_Guiji[i].x = m_center[i].x;
		tk.m_YDGJ.m_Guiji[i].y = m_center[i].y;
	}
	tk.m_YDGJ.m_Len = this->m_Pointnum;
	tk.m_mapheight = height;
	tk.m_mapwidth = width;
	tk.DoModal();
}
//实现图片特征区域的再次匹配
void CYdpdView::OnSecondPipei() 
{
		LPBITMAPINFOHEADER lpbi;
		LPBYTE lpData;
		WORD wBytesPerLine;
		int height1,width1,height2,width2;
		lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIBBK1);
		//下面的一段代码设定第二个特征区域的查找范围
		//第一个特征区域的纵坐标大于原图高度的一半
		if(lpbi->biHeight/2 < ImportantPoint.y)
		{
		    //设定考察的两个纵坐标位置
			height2 = lpbi->biHeight/2;
			height1 = 0;
		}
		else//第一个特征区域的坐标小于等于原图高度的一半
		{   //设定纵坐标位置
			height2 = lpbi->biHeight;
			height1 = lpbi->biHeight/2;
		}
		//如果第一个特征区域的横坐标大于原来图片的一半
		if(lpbi->biWidth/2 < ImportantPoint.x)
		{  //设定考察区域横坐标的两个值
			width1 = 0;
			width2 = lpbi->biWidth/2;
		}
		else //第一个特征区域的横坐标小于等于原来图片的一半
		{  //设定考察区域的横坐标的两个值
			width1 = lpbi->biWidth/2;
			width2 = lpbi->biWidth;
		}
		
	lpData = cDib.FindDIBBits(hDIBBK1);
	//得到每行象素的字节数
	wBytesPerLine = cDib.BytePerLine(hDIBBK1);
	int tempsum=0,sum=0;
	long lOffset;
	//在设定的区域内部查找第二个特征区域
	for(int i=height1+RADIUS;i<height2-RADIUS;i++)
		for(int j=width2+ RADIUS;j<width2-RADIUS;j++)
		{	tempsum =0;
		   //考察以RADIUS82+1为边长的正方形区域
			for(int k1=-RADIUS;k1<=RADIUS;k1++)
				for(int k2 =-RADIUS;k2<=RADIUS;k2++)
				{   
					//得到数据偏移
					lOffset = cDib.PixelOffset(i+k1,j+k2,wBytesPerLine);
					//得到颜色值
					int color = *(lpData+lOffset);
					//增加当前tempsum的值
					tempsum +=color;
				}
				if(tempsum>sum)//当前区域特征更明显
				{
					sum = tempsum;
					//设定区域中心点坐标
					ImportantPointSecond.x = j;
					ImportantPointSecond.y = i;
								

				}
		}
		GlobalUnlock(hDIBBK1);
   //按照新找到的特征区域，再次匹配中心点
	bool kk = cDib.MatchImportantPoint(hDIBCurrent,ImportantColorInfo,&ImportantPoint2);
	//比较图片的相似度
	if(cDib.ComPareImg(hDIBBK1,hDIBCurrent,ImportantPoint,ImportantPoint2))
		AfxMessageBox("match successed");
	else
		AfxMessageBox("match failed");
		
	Invalidate();
}

void CYdpdView::OnMenuPengzhang() 
{
	LPBITMAPINFOHEADER lpbi;
	int height,width;
	WORD wBytesPerLine;
	LPBYTE lpData;
	long lOffset;
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIBCurrent);
	height = lpbi->biHeight;
	width = lpbi->biWidth;
	lpData = cDib.FindDIBBits(hDIBCurrent);
	wBytesPerLine = cDib.BytePerLine(hDIBCurrent);


	HANDLE hNewDIB;
	
	LPBYTE lpT;

	hNewDIB = GlobalAlloc(GHND,lpbi->biSize+lpbi->biSizeImage);
	if(!hNewDIB)
		return ;
		
	lpT = cDib.FindDIBBits(hNewDIB);


	for(int i =1;i<height-1;i++)
		for(int j=1;j<width-1;j++)
		{
			lOffset = cDib.PixelOffset(i,j,wBytesPerLine);
			if(*(lpData+lOffset) == 255)
			{
				*(lpT+lOffset++) = 255;
				*(lpT+lOffset++) = 255;
				*(lpT+lOffset++) = 255;
				continue;
				
			}
			else if(*(lpData+lOffset) == 0)
			{
				lOffset = cDib.PixelOffset(i+1,j,wBytesPerLine);
				if(*(lpData+lOffset) == 255)
				{
					lOffset = cDib.PixelOffset(i,j,wBytesPerLine);
					*(lpT+lOffset++) = 255;
					*(lpT+lOffset++) = 255;
					*(lpT+lOffset++) = 255;
					continue;
				}
				lOffset = cDib.PixelOffset(i-1,j,wBytesPerLine);
				if(*(lpData+lOffset) == 255)
				{
					lOffset = cDib.PixelOffset(i,j,wBytesPerLine);
					*(lpT+lOffset++) = 255;
					*(lpT+lOffset++) = 255;
					*(lpT+lOffset++) = 255;
					continue;

				}
				lOffset = cDib.PixelOffset(i,j+1,wBytesPerLine);
				if(*(lpData+lOffset) == 255)
				{
					lOffset = cDib.PixelOffset(i,j,wBytesPerLine);
					*(lpT+lOffset++) = 255;
					*(lpT+lOffset++) = 255;
					*(lpT+lOffset++) = 255;
					continue;

				}
				lOffset = cDib.PixelOffset(i,j-1,wBytesPerLine);
				if(*(lpData+lOffset) == 255)
				{
					lOffset = cDib.PixelOffset(i,j,wBytesPerLine);
					*(lpT+lOffset++) = 255;
					*(lpT+lOffset++) = 255;
					*(lpT+lOffset++) = 255;

				}
			}
		}
		for(i = 1;i<height-1;i++)
			for(int j=1;j<width-1;j++)
			{	
				lOffset = cDib.PixelOffset(i,j,wBytesPerLine);
				*(lpData + lOffset) = *(lpT+lOffset);
				*(lpData + lOffset+1) = *(lpT+lOffset+1);
				*(lpData + lOffset+2) = *(lpT+lOffset+2);
			}
			for(i =0;i<height;i++)
		{
			lOffset = cDib.PixelOffset(i,0,wBytesPerLine);
			*(lpData+lOffset++) =0;
			*(lpData+lOffset++) =0;
			*(lpData+lOffset++) =0;
		}

		for(i =0;i<height;i++)
		{
			lOffset = cDib.PixelOffset(i,width-1,wBytesPerLine);
			*(lpData+lOffset++) =0;
			*(lpData+lOffset++) =0;
			*(lpData+lOffset++) =0;
		}
		for(i =0;i<width;i++)
		{
			lOffset = cDib.PixelOffset(height-1,i,wBytesPerLine);
			*(lpData+lOffset++) =0;
			*(lpData+lOffset++) =0;
			*(lpData+lOffset++) =0;
		}
		for(i =0;i<width;i++)
		{
			lOffset = cDib.PixelOffset(0,i,wBytesPerLine);
			*(lpData+lOffset++) =0;
			*(lpData+lOffset++) =0;
			*(lpData+lOffset++) =0;
		}
		GlobalUnlock(hDIBCurrent);
		GlobalUnlock(hNewDIB);
		Invalidate();
}

void CYdpdView::OnMenuGetedge() 
{	
	LPBITMAPINFOHEADER lpbi;
	int height,width;
	WORD wBytesPerLine;
	LPBYTE lpData;
	long lOffset;
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIBCurrent);
	height = lpbi->biHeight;
	width = lpbi->biWidth;
	lpData = cDib.FindDIBBits(hDIBCurrent);
	wBytesPerLine = cDib.BytePerLine(hDIBCurrent);


	HANDLE hNewDIB;
	
	LPBYTE lpT;

	hNewDIB = GlobalAlloc(GHND,lpbi->biSize+lpbi->biSizeImage);
	if(!hNewDIB)
		return ;
		
	lpT = cDib.FindDIBBits(hNewDIB);
	for(int i=1;i<height-1;i++)
		for(int j=1;j<width-1;j++)
		{	
			lOffset = cDib.PixelOffset(i-1,j+1,wBytesPerLine);
			int color1 = *(lpData+lOffset);
			lOffset = cDib.PixelOffset(i+1,j-1,wBytesPerLine);
			int color2 = *(lpData+lOffset);
			lOffset = cDib.PixelOffset(i,j,wBytesPerLine);
			*(lpT +lOffset++) = abs(color1-color2);
			*(lpT +lOffset++) = abs(color1-color2);
			*(lpT +lOffset++) = abs(color1-color2);
		}
		for(i = 1;i<height-1;i++)
			for(int j=1;j<width-1;j++)
			{
				lOffset = cDib.PixelOffset(i,j,wBytesPerLine);
				*(lpData+lOffset) = *(lpT+lOffset);
				*(lpData+lOffset+1) = *(lpT+lOffset+1);
				*(lpData+lOffset+2) = *(lpT+lOffset+2);
			}
			GlobalUnlock(hDIBCurrent);
			GlobalUnlock(hNewDIB);
			GlobalFree(hNewDIB);
			Invalidate();
}

void CYdpdView::OnMenuYdpdGray() 
{
	hDIBCurrent = cDib.ToGray(hDIBCurrent);
	Invalidate();
	
}
