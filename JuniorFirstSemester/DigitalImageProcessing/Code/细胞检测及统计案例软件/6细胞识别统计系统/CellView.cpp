// CellView.cpp : implementation of the CCellView class
//
#include "stdafx.h"
#include "Cell.h"

#include "CellDoc.h"
#include "CellView.h"

#include "HSI.h"
#include "HSIDlg.h"
#include "HistogramDlg.h"
#include "Set.h"
#include  <math.h>  

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_HOLE 625

#define BITMAP_ID 0x4D42 // universal id for a bitmap

#define DISTANCE(x0,y0,x1,y1) sqrt((x0-x1)*(x0-x1)+(y0-y1)*(y0-y1))

/////////////////////////////
// GLOBALS
HBITMAP		g_hBitmap=NULL;
CString		g_csFileName;		// current open file name
int			g_nMapWidth=0;
int			g_nMapHeight=0;
//bool		g_bImgBufferChanged;
RGB			spec_rgb = { 0xff, 0x00, 0x00 };		// 标识色
//RGB		*	g_pOrgImgBuffer;					// 全局的原始图像数据
RGB		*	g_pImgBuffer;							// 全局的图像数据
//RGB		*	g_pImgBufferBack;					// 全局的图像数据 用于redo
BYTE	*	g_pSobelResult;							// Soble运算的结果
HSI		*	g_pHSIBuffer;							// 全局的HSI数据
FLAGS	*	g_pFlags;								// 全局的标志量
FLAGS	*	g_pFlagsBack;							// 全局的标志量

bool		g_bDir4Ero=false;
bool		g_bDir4Dil=false;

long		g_nCellCount=0;
long		g_nCellTotArea=0;


/////////////////////////////////////////////////////////////////////////////
// 用于某些特定函数中的全局
CPoint		scroll_lefttop;							// scroll bar 左上角
double		huegap,intgap,satgap;					// 在FindInVectorHSI中使用.提高效率
long		tot_area,tot_x,tot_y,max_radius;		// 用于递归
vector<CENTER_POINT>	points_temp;				// 用于临时存储CENTER_POINT

int *qh; //queue handle
int *qs, *qst, *qr; //queue save, start, read
long qSz; //queue size (physical)
int xt, yt; //temporary x and y locations
/////////////////////////////////////////////////////////////////////////////
// CCellView

IMPLEMENT_DYNCREATE(CCellView, CScrollView)

BEGIN_MESSAGE_MAP(CCellView, CScrollView)
	//{{AFX_MSG_MAP(CCellView)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_PROC_HSI, OnProcHsi)
	ON_WM_SETCURSOR()
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_COMMAND(ID_PROC_SOBEL, OnProcSobel)
	ON_COMMAND(ID_DISP_SOBEL, OnDispSobel)
	ON_COMMAND(ID_PROC_HISTOGRAM, OnProcHistogram)
	ON_COMMAND(ID_PROC_SPEC_COLOR, OnProcSpecColor)
	ON_COMMAND(ID_DISP_EDGE, OnDispEdge)
	ON_COMMAND(ID_DISP_REGION, OnDispRegion)
	ON_COMMAND(ID_PROC_RELOAD, OnProcReload)
	ON_COMMAND(ID_PROC_FINDCENTER, OnProcFindCenter)
	ON_COMMAND(ID_PROC_SOBEL_CORRECT, OnProcSobelCorrect)
	ON_COMMAND(ID_PROC_FORCE_KILL, OnProcForceKill)
	ON_COMMAND(ID_PROC_FORCE_SELE, OnProcForceSele)
	ON_COMMAND(ID_PROC_DILATION, OnProcDilation)
	ON_COMMAND(ID_PROC_EROSION, OnProcErosion)
	ON_COMMAND(ID_PROC_SMOOTH, OnProcSmooth)
	ON_COMMAND(ID_PROC_STAT, OnProcStat)
	ON_COMMAND(ID_PROC_FILLHOLE, FillHoles)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCellView construction/destruction

CCellView::CCellView()
{
	// TODO: add construction code here
	m_DragRectSize.cx = 1;
	m_DragRectSize.cy = 1;

	g_csFileName = "";
	g_pImgBuffer = NULL;
//	g_pOrgImgBuffer = NULL;
//	g_pImgBufferBack = NULL;
	g_pHSIBuffer = NULL;
	g_pFlags = NULL;
	g_pFlagsBack = NULL;
	g_pSobelResult= NULL;

	// 所有布尔量初始化
//	g_bImgBufferChanged=false;

	m_bDrag=false;
	m_bProcHsi=false;
	m_bDispSobel=false;
	m_bIsDispEdge=false;
	m_bFullEdge=false;
	m_bForceKill=false;
	m_bForceAdd=false;

	CSize sz(g_nMapWidth,g_nMapHeight);
	SetScrollSizes(MM_TEXT, sz);
}

CCellView::~CCellView()
{
	if(g_hBitmap)
		DeleteObject(g_hBitmap);
	if(g_pImgBuffer)
		delete[] g_pImgBuffer;
//	if (g_pOrgImgBuffer)
//		delete[] g_pOrgImgBuffer;
//	if (g_pImgBufferBack)
//		delete[] g_pImgBufferBack;
	if(g_pHSIBuffer)
		delete[] g_pHSIBuffer;
	if (g_pSobelResult)
		delete[] g_pSobelResult;
	if(g_pFlags)
		delete[] g_pFlags;
	if (g_pFlagsBack)
		delete[] g_pFlagsBack;
}

BOOL CCellView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCellView drawing

void CCellView::OnDraw(CDC* pDC)
{
	int x,y;
	CCellDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	if(g_hBitmap)
	{
		scroll_lefttop=GetScrollPosition();
		RECT rect;
		GetClientRect(&rect);
		int drawwd,drawht;
		if (g_nMapWidth>rect.right-rect.left)
			drawwd=rect.right-rect.left+1;
		else drawwd=g_nMapWidth;
		if (g_nMapHeight>rect.bottom-rect.top)
			drawht=rect.bottom-rect.top+1;
		else drawht=g_nMapHeight;

		BITMAPINFO bitmapinfo;
		CDC *pdc = GetDC();
		HDC dc = pdc->m_hDC;
		HDC memdc = ::CreateCompatibleDC(dc);
		::SelectObject(memdc, g_hBitmap);
		if (m_bDispSobel) // 显示Sobel
		{
			BYTE *cur_pos=g_pSobelResult;
			for(y = 0; y < g_nMapHeight; y++)
			{
				for(x = 0; x < g_nMapWidth; x++)
				{
					if (x-scroll_lefttop.x>=0 && x-scroll_lefttop.x<=drawwd && y-scroll_lefttop.y>=0 && y-scroll_lefttop.y<=drawht)
						SetPixel(memdc,x,y,RGB(*cur_pos,*cur_pos,*cur_pos));
					cur_pos++;
				}
			}
//			g_bImgBufferChanged=false;
		}
		else
		{
			bitmapinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			bitmapinfo.bmiHeader.biWidth = g_nMapWidth;
			bitmapinfo.bmiHeader.biHeight = g_nMapHeight;
			bitmapinfo.bmiHeader.biPlanes = 1;
			bitmapinfo.bmiHeader.biBitCount = 24;
			bitmapinfo.bmiHeader.biCompression = BI_RGB;
			GetDIBits(memdc, g_hBitmap, 0, g_nMapHeight, NULL,
				&bitmapinfo, DIB_RGB_COLORS);
			FlipBitmapData(g_pImgBuffer); // flip it
			SetDIBits(memdc, g_hBitmap, 0, g_nMapHeight, g_pImgBuffer,
				&bitmapinfo, DIB_RGB_COLORS);
			FlipBitmapData(g_pImgBuffer); // flip back
/*			if (m_bIsDispEdge)
			{
				FlipBitmapData(g_pImgBuffer); // flip it
				SetDIBits(memdc, g_hBitmap, 0, g_nMapHeight, g_pImgBuffer,
					&bitmapinfo, DIB_RGB_COLORS);
				FlipBitmapData(g_pImgBuffer); // flip back
			}
			else
			{
				FlipBitmapData(g_pImgBuffer); // flip it
				SetDIBits(memdc, g_hBitmap, 0, g_nMapHeight, g_pImgBuffer,
					&bitmapinfo, DIB_RGB_COLORS);
				FlipBitmapData(g_pImgBuffer); // flip back
			}
*/		}
		::BitBlt(dc, 0, 0, drawwd, drawht, memdc, scroll_lefttop.x, scroll_lefttop.y, SRCCOPY);

		FLAGS* cur_flag;
		if(m_bIsDispEdge)
		{
			for(y = 0; y < g_nMapHeight; y++)
			{
				cur_flag=&g_pFlags[y*g_nMapWidth];
				for(x = 0; x < g_nMapWidth; x++)
				{
					if(cur_flag->edged)
						if (x-scroll_lefttop.x>=0 && x-scroll_lefttop.x<=drawwd && y-scroll_lefttop.y>=0 && y-scroll_lefttop.y<=drawht)
							pdc->SetPixel(x-scroll_lefttop.x, y-scroll_lefttop.y, RGB(spec_rgb.r, spec_rgb.g, spec_rgb.b));
					cur_flag++;
				}
			}
		}
		else // region
		{
			for(y = 0; y < g_nMapHeight; y++)
			{
				cur_flag=&g_pFlags[y*g_nMapWidth];
				for(x = 0; x < g_nMapWidth; x++)
				{
					if(cur_flag->marked)
						if (x-scroll_lefttop.x>=0 && x-scroll_lefttop.x<=drawwd && y-scroll_lefttop.y>=0 && y-scroll_lefttop.y<=drawht)
							pdc->SetPixel(x-scroll_lefttop.x, y-scroll_lefttop.y, RGB(spec_rgb.r, spec_rgb.g, spec_rgb.b));
					cur_flag++;
				}
			}
		}
		CENTER_POINT centerp;
		CPen	pen;
		pen.CreatePen(PS_SOLID, 1, RGB(spec_rgb.r, spec_rgb.g, spec_rgb.b));
		pdc->SelectObject(pen);
		for (int i=0;i<m_vCenterPoints.size();i++)
		{
			centerp=m_vCenterPoints.at(i);
			Arc(pdc->m_hDC,
				centerp.x-scroll_lefttop.x-centerp.radius,
				centerp.y-scroll_lefttop.y-centerp.radius,
				centerp.x-scroll_lefttop.x+centerp.radius,
				centerp.y-scroll_lefttop.y+centerp.radius,
				centerp.x-scroll_lefttop.x+centerp.radius,
				centerp.y-scroll_lefttop.y,
				centerp.x-scroll_lefttop.x+centerp.radius,
				centerp.y-scroll_lefttop.y
				);
		}
		DeleteObject(pen);

		ReleaseDC(pdc);
		::DeleteDC(memdc);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCellView printing

BOOL CCellView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCellView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCellView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCellView diagnostics

#ifdef _DEBUG
void CCellView::AssertValid() const
{
	CView::AssertValid();
}

void CCellView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCellDoc* CCellView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCellDoc)));
	return (CCellDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCellView message handlers

void CCellView::OnFileOpen() 
{
	// 打开文件对话框
	char		szFilter[] = "位图文件 (*.bmp)|*.bmp|所有文件(*.*)|*.*||";
	CString		szFilename;
	BITMAP		bmp;
	CFileDialog *FileDlg = new CFileDialog(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, szFilter, NULL);

	if(FileDlg->DoModal() == IDOK)
	{
		szFilename = FileDlg->GetPathName();
		if(!szFilename.IsEmpty())
		{
			HANDLE	handle;
			handle = LoadImage(theApp.m_hInstance, szFilename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			if(handle)
			{
				if(g_hBitmap)
					DeleteObject(g_hBitmap);
				InvalidateRect(0, TRUE);
				g_hBitmap = (struct HBITMAP__ *) handle;
				g_csFileName = FileDlg->GetFileName();
				theApp.m_pMainWnd->SetWindowText((LPCTSTR) (g_csFileName + " - Cell"));
			}
			else
			{
				MessageBox("无法打开文件");
				return;
			}
			m_vAllSelected.clear();
			// 所有布尔量初始化
			m_bDrag=false;
			m_bProcHsi=false;
			m_bForceKill=false;
			m_bForceAdd=false;
			m_bDispSobel=false;
			AfxGetApp()->m_pMainWnd->GetMenu()->CheckMenuItem(ID_DISP_SOBEL, MF_UNCHECKED);
			m_bIsDispEdge=false;
			AfxGetApp()->m_pMainWnd->GetMenu()->CheckMenuItem(ID_DISP_REGION, MF_CHECKED);
			AfxGetApp()->m_pMainWnd->GetMenu()->CheckMenuItem(ID_DISP_EDGE, MF_UNCHECKED);
			m_vCenterPoints.clear(); // 清除!

			CDC *pdc = GetDC();
			HDC dc = pdc->m_hDC;
			HDC memdc = ::CreateCompatibleDC(dc);
			CBitmap::FromHandle(g_hBitmap)->GetBitmap(&bmp);
			::SelectObject(memdc, g_hBitmap);

			g_nMapWidth=bmp.bmWidth;
			g_nMapHeight=bmp.bmHeight;

			// 设置滚动条
			CSize sz(g_nMapWidth,g_nMapHeight);
			SetScrollSizes(MM_TEXT, sz);

			// fill g_pImgBuffer
			if (LoadImageBuffer(memdc,(LPSTR)(LPCTSTR)g_csFileName)==0)
				return;

			// 初始化Flags
			if(g_pFlags)
				delete[] g_pFlags;
			g_pFlags = new FLAGS[g_nMapHeight * g_nMapWidth];
			memset(g_pFlags, 0,	g_nMapHeight * g_nMapWidth * sizeof(FLAGS));
			if (g_pFlagsBack)
				delete[] g_pFlagsBack;
			g_pFlagsBack = new FLAGS[g_nMapHeight * g_nMapWidth];
			memset(g_pFlagsBack, 0,	g_nMapHeight * g_nMapWidth * sizeof(FLAGS));

			GenHSIData();

			OnProcSobel(); // 预先生成Sobel信息

			::BitBlt(dc, 0, 0, g_nMapWidth, g_nMapHeight, memdc, 0, 0, SRCCOPY);
			ReleaseDC(pdc);
			::DeleteDC(memdc);
		}
	}

	delete FileDlg;
}

void CCellView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_LBDnPoint = point;
	m_LastPoint = point;
	m_bDrag = true;

	// draw selection box
	RECT	currect;
	currect.top = m_LBDnPoint.y;
	currect.left = m_LBDnPoint.x;
	currect.right = point.x;
	currect.bottom = point.y;

	CDC *pdc = GetDC();
	pdc->DrawDragRect(&currect, m_DragRectSize, NULL, m_DragRectSize, NULL, NULL);
	ReleaseDC(pdc);

	CView::OnLButtonDown(nFlags, point);
}

void CCellView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(m_bDrag)
	{
		RECT	lastrect, currect;
		lastrect.top =		m_LBDnPoint.y > m_LastPoint.y ? m_LastPoint.y : m_LBDnPoint.y;
		lastrect.left =		m_LBDnPoint.x > m_LastPoint.x ? m_LastPoint.x : m_LBDnPoint.x;
		lastrect.right =	m_LBDnPoint.x > m_LastPoint.x ? m_LBDnPoint.x : m_LastPoint.x;
		lastrect.bottom =	m_LBDnPoint.y > m_LastPoint.y ? m_LBDnPoint.y : m_LastPoint.y;
		currect.top =		m_LBDnPoint.y > point.y ? point.y : m_LBDnPoint.y;
		currect.left =		m_LBDnPoint.x > point.x ? point.x : m_LBDnPoint.x;
		currect.right =		m_LBDnPoint.x > point.x ? m_LBDnPoint.x : point.x;
		currect.bottom =	m_LBDnPoint.y > point.y ? m_LBDnPoint.y : point.y;

		SIZE	sz;
		sz.cx = 1;
		sz.cy = 1;

		CDC *pdc = GetDC();
		pdc->DrawDragRect(&currect, m_DragRectSize, &lastrect, m_DragRectSize, NULL, NULL);
		ReleaseDC(pdc);

		m_LastPoint = point;
	}
	
	CView::OnMouseMove(nFlags, point);
}

void CCellView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (!m_bDrag) // 安全措施
	{
		CView::OnLButtonUp(nFlags, point);
		return;
	}

	int exchange;
	m_bDrag = false;

	// 画选择框
	m_SelectedRect.left = m_LBDnPoint.x;
	m_SelectedRect.top = m_LBDnPoint.y;
	m_SelectedRect.right = point.x;
	m_SelectedRect.bottom = point.y;

	if(m_SelectedRect.left > m_SelectedRect.right)
	{
		exchange = m_SelectedRect.left;
		m_SelectedRect.left = m_SelectedRect.right;
		m_SelectedRect.right = exchange;
	}

	if(m_SelectedRect.top > m_SelectedRect.bottom)
	{
		exchange = m_SelectedRect.top;
		m_SelectedRect.top = m_SelectedRect.bottom;
		m_SelectedRect.bottom = exchange;
	}

	SIZE	zero;
	zero.cx = 0;
	zero.cy = 0;

	CDC *pdc = GetDC();
	pdc->DrawDragRect(&m_SelectedRect, zero, &m_SelectedRect, m_DragRectSize, NULL, NULL);
	ReleaseDC(pdc);

	m_LastPoint.x = 0;	// 设置为0
	
	if(g_hBitmap)
	{
		if(m_bProcHsi)
		{
			if(m_SelectedRect.left >= m_SelectedRect.right || m_SelectedRect.top >= m_SelectedRect.bottom)
				MessageBox("选择的范围不正确.请重新选择!");
			else
			{
				m_bProcHsi = false;
				CHSIDlg hsiDlg(&m_SelectedRect);
				if(hsiDlg.DoModal() == IDOK)
					ProcHSI(hsiDlg.m_bEx);
			}
		}
		else if (m_bForceKill)
		{
			if(m_SelectedRect.left >= m_SelectedRect.right || m_SelectedRect.top >= m_SelectedRect.bottom)
				MessageBox("选择的范围不正确.请重新选择!");
			else
			{
				m_bForceKill = false;
				m_SelectedRect.left+=scroll_lefttop.x;
				m_SelectedRect.right+=scroll_lefttop.x;
				m_SelectedRect.top+=scroll_lefttop.y;
				m_SelectedRect.bottom+=scroll_lefttop.y;
				for(int j = m_SelectedRect.top; j < m_SelectedRect.bottom; j++)
				{
					for(int i = m_SelectedRect.left; i < m_SelectedRect.right; i++)
					{
						if (i<0 || i>=g_nMapWidth || j<0 || j>=g_nMapHeight)
							continue;
						g_pFlags[INDEX(i, j)].marked=0;
					}
				}
				GenEdge();
				InvalidateRect(0,TRUE);
			}
		}
		else if (m_bForceAdd)
		{
			if(m_SelectedRect.left >= m_SelectedRect.right || m_SelectedRect.top >= m_SelectedRect.bottom)
				MessageBox("选择的范围不正确.请重新选择!");
			else
			{
				m_bForceAdd = false;
				m_SelectedRect.left+=scroll_lefttop.x;
				m_SelectedRect.right+=scroll_lefttop.x;
				m_SelectedRect.top+=scroll_lefttop.y;
				m_SelectedRect.bottom+=scroll_lefttop.y;
				for(int j = m_SelectedRect.top; j < m_SelectedRect.bottom; j++)
				{
					for(int i = m_SelectedRect.left; i < m_SelectedRect.right; i++)
					{
						if (i<0 || i>=g_nMapWidth || j<0 || j>=g_nMapHeight)
							continue;
						g_pFlags[INDEX(i, j)].marked=1;
					}
				}
				GenEdge();
				InvalidateRect(0,TRUE);
			}
		}
	}

	CView::OnLButtonUp(nFlags, point);
}

bool CCellView::LoadImageBuffer(HDC memdc,char *szFileName)
{
	BITMAPFILEHEADER bitmapfileheader;
	BITMAPINFOHEADER bitmapinfoheader;
	BITMAPINFO		 bitmapinfo;

	// this function opens a bitmap file and loads the data into bitmap
	int file_handle;  // the file handle
	OFSTRUCT file_data;          // the file data information

	// open the file if it exists
	if ((file_handle = OpenFile(szFileName,&file_data,OF_READ))==-1)
	   return 0;

	// now load the bitmap file header
	_lread(file_handle, &bitmapfileheader,sizeof(BITMAPFILEHEADER));

	// test if this is a bitmap file
	if (bitmapfileheader.bfType!=BITMAP_ID)
	{
		// close the file
		_lclose(file_handle);
		// return error
		return 0;
	} // end if

	// now we know this is a bitmap, so read in all the sections

	// first the bitmap infoheader

	// now load the bitmap file header
	_lread(file_handle, &bitmapinfoheader, sizeof(BITMAPINFOHEADER));

	if (bitmapinfoheader.biWidth%4 != 0) // 宽度不是4的倍数
	{
		MessageBox("文件宽度不是4的倍数");
		_lclose(file_handle);
		return 0;
	}

	if(g_pImgBuffer) // clear it if not null
		delete[] g_pImgBuffer;
	g_pImgBuffer = new RGB[g_nMapHeight * g_nMapWidth];		// make space
	// 申请备份buffer空间
//	if (g_pImgBufferBack)
//		delete[] g_pImgBufferBack;
//	g_pImgBufferBack=new RGB[g_nMapHeight * g_nMapWidth];
//	if (g_pOrgImgBuffer)
//		delete[] g_pOrgImgBuffer;
//	g_pOrgImgBuffer=new RGB[g_nMapHeight * g_nMapWidth];

	// now load the color palette if there is one
	if (bitmapinfoheader.biBitCount != 24)
	{
		// set bitmapinfo
		bitmapinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bitmapinfo.bmiHeader.biWidth = g_nMapWidth;
		bitmapinfo.bmiHeader.biHeight = g_nMapHeight;
		bitmapinfo.bmiHeader.biPlanes = 1;
		bitmapinfo.bmiHeader.biBitCount = 24;
		bitmapinfo.bmiHeader.biCompression = BI_RGB;
		GetDIBits(memdc, g_hBitmap, 0, g_nMapHeight, NULL,
			&bitmapinfo, DIB_RGB_COLORS);
		GetDIBits(memdc, g_hBitmap, 0, g_nMapHeight, g_pImgBuffer,
			&bitmapinfo, DIB_RGB_COLORS);
	}
	else
	{
		_llseek(file_handle, bitmapfileheader.bfOffBits,FILE_BEGIN);
		_lread(file_handle, g_pImgBuffer, 3*g_nMapHeight*g_nMapWidth);
	}
	FlipBitmapData(g_pImgBuffer);

//	memcpy(g_pOrgImgBuffer,g_pImgBuffer,sizeof(RGB)*g_nMapWidth*g_nMapHeight);

	// close the file
	_lclose(file_handle);

	// return success
	return 1;
}

void CCellView::FlipBitmapData(RGB *buffer)
{
	RGB *tempmem;
	int bytes_per_line=g_nMapWidth*sizeof(RGB);
	
	tempmem=new RGB[g_nMapWidth*g_nMapHeight];
	memcpy(tempmem,buffer,bytes_per_line*g_nMapHeight);
	for (int i=0;i<g_nMapHeight;i++)
		memcpy(&buffer[((g_nMapHeight-1) - i)*g_nMapWidth],
		&tempmem[i*g_nMapWidth], bytes_per_line);
	delete[] tempmem;
}

void CCellView::OnProcHsi() 
{
	if(g_hBitmap)
	{
		m_bProcHsi = true;
		MessageBox("请选择一块小区域作为颜色选取范围");
	}
	else
		MessageBox("请先打开图像文件!");
}

BOOL CCellView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if(m_bProcHsi || m_bForceKill || m_bForceAdd)
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
	else
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	return TRUE;
}

void CCellView::ProcHSI(bool bEx)
{
	m_vHSI.clear();

	// fill vector
	HSI			*hsi;

	huegap=256.0*g_nHueGap/100.0;
	if (huegap>5.12)
		huegap=5.12;
	huegap+=0.0001;
	intgap=g_nIntGap/100.0;
	if (intgap>0.02)
		intgap=0.02;
	intgap+=0.0001;
	satgap=g_nSatGap/100.0;
	if (satgap>0.02)
		satgap=0.02;
	satgap+=0.0001;

	m_SelectedRect.left+=scroll_lefttop.x;
	m_SelectedRect.right+=scroll_lefttop.x;
	m_SelectedRect.top+=scroll_lefttop.y;
	m_SelectedRect.bottom+=scroll_lefttop.y;
	for(int j = m_SelectedRect.top; j < m_SelectedRect.bottom; j++)
	{
		for(int i = m_SelectedRect.left; i < m_SelectedRect.right; i++)
		{
			if (i<0 || i>=g_nMapWidth || j<0 || j>=g_nMapHeight)
				continue;
			if(!g_pFlags[INDEX(i, j)].marked)
			{
				hsi=&g_pHSIBuffer[INDEX(i,j)];
				if(FindInVectorHSI(m_vHSI, *hsi) == false)
				{
					m_vHSI.push_back(*hsi);
					m_vAllSelected.push_back(*hsi);
				}
			}
		}
	}

	if(m_vHSI.size())
	{
		// backup
//		memcpy(g_pImgBufferBack,g_pImgBuffer,
//			sizeof(RGB)*g_nMapWidth*g_nMapHeight);
		memcpy(g_pFlagsBack,g_pFlags,
			sizeof(FLAGS)*g_nMapWidth*g_nMapHeight);

//		g_bImgBufferChanged=true;
		HsiProcess(bEx);
//		m_vHSI.clear();
		GenEdge();
		InvalidateRect(0, TRUE);
	}
}

void CCellView::GenHSIData()
{
	int		wd, ht;
	HSI		tmp;
	RGB	   *cur;

	if(g_pHSIBuffer)
		delete[] g_pHSIBuffer;
	g_pHSIBuffer = new HSI[g_nMapWidth * g_nMapHeight];
	memset(g_pHSIBuffer, 0, sizeof(HSI) * g_nMapWidth * g_nMapHeight);

	HSI	*pHueBuffer = g_pHSIBuffer;

	cur = g_pImgBuffer;
	for(ht = 0; ht < g_nMapHeight; ht++)
	{
		for(wd = 0; wd < g_nMapWidth; wd++)
		{
			RgbToHsi(cur, &tmp);
			pHueBuffer->Hue = tmp.Hue*255.0/360.0;
			pHueBuffer->Intensity = tmp.Intensity;
			pHueBuffer->Saturation = tmp.Saturation;

			pHueBuffer++;
			cur++;
		}
	}
}

bool CCellView::FindInVectorHSI(vector<HSI> v, HSI c)
{
	int size = v.size();
	for(int i = 0; i < size; i++)
//		if(c.Hue == v.at(i).Hue && c.Intensity == v.at(i).Intensity && c.Saturation == v.at(i).Saturation)
		if( fabs(c.Hue - v.at(i).Hue) < huegap &&
			fabs(c.Intensity - v.at(i).Intensity) < intgap && 
			fabs(c.Saturation - v.at(i).Saturation) < satgap )
				return true;
	return false;
}

void CCellView::HsiProcess(bool bEx)
{
	RGB		*cur=g_pImgBuffer;
	HSI		*pHSI=g_pHSIBuffer;

	int		size = m_vHSI.size();
	double	sH, sS, sI, dH, dS, dI;
	HSI		tmp, vtmp;
	int		ht, wd;
	FLAGS	*cur_flag = g_pFlags;				// flag
	for(ht = 0; ht < g_nMapHeight; ht++)
	{
		for(wd = 0; wd < g_nMapWidth; wd++)
		{
			if(cur_flag->marked)
			{
				cur++;
				cur_flag++;						// flag
				pHSI++;
				continue;
			}
			memcpy(&tmp,pHSI,sizeof(HSI));
			pHSI++;
			for(int i = 0; i < size; i++)
			{
				vtmp = m_vHSI.at(i);
				sH = vtmp.Hue;
				sS = vtmp.Saturation;
				sI = vtmp.Intensity;
				dH = tmp.Hue;
				dS = tmp.Saturation;
				dI = tmp.Intensity;
				if(!bEx)					// 排除法
				{
					if
					(
						sH - dH >= 0 - g_nHueGap * 2.55
					&&	sH - dH <= g_nHueGap * 2.55
					&&	sS - dS >= 0 - g_nSatGap / 100.0
					&&	sS - dS <= g_nSatGap / 100.0
					&&	sI - dI >= 0 - g_nIntGap / 100.0
					&&	sI - dI <= g_nIntGap / 100.0
					)
					{
						cur_flag->marked = 1;	// set marked
//						cur->r=cur->g=cur->b=0;
						continue;
					}
				}
				else
				{
					if
					(
						(sH - dH <= 0 - g_nHueGap * 2.55 || sH - dH >= g_nHueGap * 2.55)
					&&	(sS - dS <= 0 - g_nSatGap / 100.0 || sS - dS >= g_nSatGap / 100.0)
					&&	(sI - dI <= 0 - g_nIntGap / 100.0 || sI - dI >= g_nIntGap / 100.0)
					)
					{
						cur_flag->marked = 1;	// set marked
						cur->r=cur->g=cur->b=0;
						continue;
					}
				}
			}

			cur++;
			cur_flag++; // flag
		}
	}
}

void CCellView::OnEditUndo() 
{
	// TODO: Add your command handler code here
//	RGB		*exch;
	FLAGS	*exchf;
	if (g_pFlagsBack)
	{
//		exch=g_pImgBufferBack;
//		g_pImgBufferBack=g_pImgBuffer;
//		g_pImgBuffer=exch;
//		g_bImgBufferChanged=true;

		// 恢复
		if(g_pFlags && g_pFlagsBack)
		{
			exchf=g_pFlags;
			g_pFlags=g_pFlagsBack;
			g_pFlagsBack=exchf;
		}

		InvalidateRect(NULL,TRUE);
	}
}

void CCellView::OnProcSobel() 
{
	if(!g_hBitmap)
		MessageBox("请先打开文件");
	else	// here we go~
	{
		double SobelTemplateGx[9];
		double SobelTemplateGy[9];
		// -1 -2 -1
		//  0  0  0
		//  1  2  1
		SobelTemplateGx[0] = -1;
		SobelTemplateGx[1] = -2;
		SobelTemplateGx[2] = -1;
		SobelTemplateGx[3] = 0;
		SobelTemplateGx[4] = 0;
		SobelTemplateGx[5] = 0;
		SobelTemplateGx[6] = 1;
		SobelTemplateGx[7] = 2;
		SobelTemplateGx[8] = 1;

		// -1 0 1
		// -2 0 2
		// -1 0 1
		SobelTemplateGy[0] = -1;
		SobelTemplateGy[1] = 0;
		SobelTemplateGy[2] = 1;
		SobelTemplateGy[3] = -2;
		SobelTemplateGy[4] = 0;
		SobelTemplateGy[5] = 2;
		SobelTemplateGy[6] = -1;
		SobelTemplateGy[7] = 0;
		SobelTemplateGy[8] = 1;
		if(g_pSobelResult)
			delete[] g_pSobelResult;
		g_pSobelResult = new BYTE[g_nMapWidth * g_nMapHeight];
		if(!g_pSobelResult)
		{
			MessageBox("not enough memory");
			return;
		}

		RGB		*got;
		double		tempr, tempg, tempb;
		double		multi;
		double		result;
		int		x, y;

		BYTE	*cur_pos=g_pSobelResult;

		for(y = 0; y < g_nMapHeight; y++)
		{
			for(x = 0; x < g_nMapWidth; x++)
			{
				// 计算Gx方向
				tempr = tempg = tempb = 0;

				got = GetBit(x - 1, y - 1);
				if(got)
				{
					multi = SobelTemplateGx[0];
					tempr += multi * got->r;
					tempg += multi * got->g;
					tempb += multi * got->b;
				}

				got = GetBit(x, y - 1);
				if(got)
				{
					multi = SobelTemplateGx[1];
					tempr += multi * got->r;
					tempg += multi * got->g;
					tempb += multi * got->b;
				}

				got = GetBit(x + 1, y - 1);
				if(got)
				{
					multi = SobelTemplateGx[2];
					tempr += multi * got->r;
					tempg += multi * got->g;
					tempb += multi * got->b;
				}

				got = GetBit(x - 1, y);
				if(got)
				{
					multi = SobelTemplateGx[3];
					tempr += multi * got->r;
					tempg += multi * got->g;
					tempb += multi * got->b;
				}

				got = GetBit(x, y);
				if(got)
				{
					multi = SobelTemplateGx[4];
					tempr += multi * got->r;
					tempg += multi * got->g;
					tempb += multi * got->b;
				}

				got = GetBit(x + 1, y);
				if(got)
				{
					multi = SobelTemplateGx[5];
					tempr += multi * got->r;
					tempg += multi * got->g;
					tempb += multi * got->b;
				}

				got = GetBit(x - 1, y + 1);
				if(got)
				{
					multi = SobelTemplateGx[6];
					tempr += multi * got->r;
					tempg += multi * got->g;
					tempb += multi * got->b;
				}

				got = GetBit(x, y + 1);
				if(got)
				{
					multi = SobelTemplateGx[7];
					tempr += multi * got->r;
					tempg += multi * got->g;
					tempb += multi * got->b;
				}

				got = GetBit(x + 1, y + 1);
				if(got)
				{
					multi = SobelTemplateGx[8];
					tempr += multi * got->r;
					tempg += multi * got->g;
					tempb += multi * got->b;
				}

				result = fabs(tempr) + fabs(tempg) + fabs(tempb);

				// 计算Gy方向
				tempr = tempg = tempb = 0;

				got = GetBit(x - 1, y - 1);
				if(got)
				{
					multi = SobelTemplateGy[0];
					tempr += multi * got->r;
					tempg += multi * got->g;
					tempb += multi * got->b;
				}

				got = GetBit(x, y - 1);
				if(got)
				{
					multi = SobelTemplateGy[1];
					tempr += multi * got->r;
					tempg += multi * got->g;
					tempb += multi * got->b;
				}

				got = GetBit(x + 1, y - 1);
				if(got)
				{
					multi = SobelTemplateGy[2];
					tempr += multi * got->r;
					tempg += multi * got->g;
					tempb += multi * got->b;
				}

				got = GetBit(x - 1, y);
				if(got)
				{
					multi = SobelTemplateGy[3];
					tempr += multi * got->r;
					tempg += multi * got->g;
					tempb += multi * got->b;
				}

				got = GetBit(x, y);
				if(got)
				{
					multi = SobelTemplateGy[4];
					tempr += multi * got->r;
					tempg += multi * got->g;
					tempb += multi * got->b;
				}

				got = GetBit(x + 1, y);
				if(got)
				{
					multi = SobelTemplateGy[5];
					tempr += multi * got->r;
					tempg += multi * got->g;
					tempb += multi * got->b;
				}

				got = GetBit(x - 1, y + 1);
				if(got)
				{
					multi = SobelTemplateGy[6];
					tempr += multi * got->r;
					tempg += multi * got->g;
					tempb += multi * got->b;
				}

				got = GetBit(x, y + 1);
				if(got)
				{
					multi = SobelTemplateGy[7];
					tempr += multi * got->r;
					tempg += multi * got->g;
					tempb += multi * got->b;
				}

				got = GetBit(x + 1, y + 1);
				if(got)
				{
					multi = SobelTemplateGy[8];
					tempr += multi * got->r;
					tempg += multi * got->g;
					tempb += multi * got->b;
				}

				result += fabs(tempr) + fabs(tempg) + fabs(tempb);

				if(result > 255 * 8)
					*cur_pos++ = 255;
				else
					*cur_pos++ = result / 8;
			}
		}
//		m_bDispSobel = true;
//		AfxGetApp()->m_pMainWnd->GetMenu()->CheckMenuItem(ID_DISP_SOBEL, MF_CHECKED);
//		InvalidateRect(0, TRUE);
	}
}

RGB* CCellView::GetBit(int x, int y)
{
	if(x < 0 || x >= g_nMapWidth || y < 0 || y >= g_nMapHeight)
		return 0;
	return (g_pImgBuffer + y * g_nMapWidth + x);
}

void CCellView::OnProcHistogram() 
{
	if(g_hBitmap)
	{
		CHistogramDlg	hDlg;
		if(hDlg.DoModal() == IDOK)
		{
			// backup
//			memcpy(g_pImgBufferBack,g_pImgBuffer,
//				sizeof(RGB)*g_nMapWidth*g_nMapHeight);
			memcpy(g_pFlagsBack,g_pFlags,
				sizeof(FLAGS)*g_nMapWidth*g_nMapHeight);

//			g_bImgBufferChanged=true;

			FLAGS	*cur_flag = g_pFlags;
			RGB		*cur=g_pImgBuffer;
			for(int j = 0; j < g_nMapHeight; j++)
			{
				for(int i = 0; i < g_nMapWidth; i++)
				{
					if(!(cur_flag->marked))
					{
						if (	(cur->b >= hDlg.m_Thresh_B && cur->b <= hDlg.m_Thresh_BMax)
							&&	(cur->r >= hDlg.m_Thresh_R && cur->r <= hDlg.m_Thresh_RMax)
							&&	(cur->g >= hDlg.m_Thresh_G && cur->g <= hDlg.m_Thresh_GMax))
						{
								cur_flag->marked = 1;
//								cur->r=cur->g=cur->b=0; // 不改变了原图了!
						}
					}
					cur_flag++;
					cur++;
				}
			}
			GenEdge();
			InvalidateRect(0, TRUE);
		}
	}
	else MessageBox("请先打开图像文件!");
}

void CCellView::GenEdge() // 八方向生成边界
{
	FLAGS	*cur = g_pFlags;
	int		width = g_nMapWidth;
	int		height = g_nMapHeight;
	for(int j = 0; j < g_nMapHeight; j++)
	{
		for(int i = 0; i < g_nMapWidth; i++)
		{
			cur->edged = 0;
			if(cur->marked)
			{
				if(j == 0 && i == 0)	// left top
				{
					if(!((cur + 1)->marked && (cur + width)->marked && (cur + width + 1)->marked)) cur->edged = 1;
				}
				else if(j == 0 && i == width - 1)			// right top
				{
					if(!((cur - 1)->marked && (cur + width)->marked && (cur + width - 1)->marked)) cur->edged = 1;
				}
				else if(j == height - 1 && i == 0)			// bottom left
				{
					if(!((cur + 1)->marked && (cur - width)->marked && (cur - width + 1)->marked)) cur->edged = 1;
				}
				else if(j == height - 1 && i == width - 1)	// bottom right
				{
					if(!((cur - 1)->marked && (cur - width)->marked && (cur - width - 1)->marked)) cur->edged = 1;
				}
				else if(j == 0)				// top
				{
					if
					(
						!((cur - 1)->marked
						&&	(cur + 1)->marked
						&&	(cur + width - 1)->marked
						&&	(cur + width + 1)->marked
						&&	(cur + width)->marked
						)
					) cur->edged = 1;
				}
				else if(i == 0)				// left
				{
					if
					(
						!((cur - width)->marked
						&&	(cur - width + 1)->marked
						&&	(cur + 1)->marked
						&&	(cur + width)->marked
						&&	(cur + width + 1)->marked
						)
					) cur->edged = 1;
				}
				else if(j == height - 1)	// bottom
				{
					if
					(
						!((cur - 1)->marked
						&&	(cur + 1)->marked
						&&	(cur - width - 1)->marked
						&&	(cur - width + 1)->marked
						&&	(cur - width)->marked
						)
					) cur->edged = 1;
				}
				else if(i == width - 1)		// right
				{
					if
					(
						!((cur - width)->marked
						&&	(cur - width - 1)->marked
						&&	(cur - 1)->marked
						&&	(cur + width)->marked
						&&	(cur + width - 1)->marked
						)
					) cur->edged = 1;
				}
				else						// normal
				{
					if
					(
						!((cur - width - 1)->marked
						&&	(cur - width)->marked
						&&	(cur - width + 1)->marked
						&&	(cur - 1)->marked
						&&	(cur + 1)->marked
						&&	(cur + width - 1)->marked
						&&	(cur + width)->marked
						&&	(cur + width + 1)->marked
						)
					) cur->edged = 1;
				}
			}
			cur++;
		}
	}
}

void CCellView::GenEdge4()// 四方向生成边界
{
	FLAGS	*cur = g_pFlags;
	int		width = g_nMapWidth;
	int		height = g_nMapHeight;
	for(int j = 0; j < g_nMapHeight; j++)
	{
		for(int i = 0; i < g_nMapWidth; i++)
		{
			cur->edged = 0;
			if(cur->marked)
			{
				if(j == 0 && i == 0)	// left top
				{
					if(!((cur + 1)->marked && (cur + width)->marked && (cur + width + 1)->marked)) cur->edged = 1;
				}
				else if(j == 0 && i == width - 1)			// right top
				{
					if(!((cur - 1)->marked && (cur + width)->marked && (cur + width - 1)->marked)) cur->edged = 1;
				}
				else if(j == height - 1 && i == 0)			// bottom left
				{
					if(!((cur + 1)->marked && (cur - width)->marked && (cur - width + 1)->marked)) cur->edged = 1;
				}
				else if(j == height - 1 && i == width - 1)	// bottom right
				{
					if(!((cur - 1)->marked && (cur - width)->marked && (cur - width - 1)->marked)) cur->edged = 1;
				}
				else if(j == 0)				// top
				{
					if
					(
						!((cur - 1)->marked
						&&	(cur + 1)->marked
						&&	(cur + width - 1)->marked
						&&	(cur + width + 1)->marked
						&&	(cur + width)->marked
						)
					) cur->edged = 1;
				}
				else if(i == 0)				// left
				{
					if
					(
						!((cur - width)->marked
						&&	(cur - width + 1)->marked
						&&	(cur + 1)->marked
						&&	(cur + width)->marked
						&&	(cur + width + 1)->marked
						)
					) cur->edged = 1;
				}
				else if(j == height - 1)	// bottom
				{
					if
					(
						!((cur - 1)->marked
						&&	(cur + 1)->marked
						&&	(cur - width - 1)->marked
						&&	(cur - width + 1)->marked
						&&	(cur - width)->marked
						)
					) cur->edged = 1;
				}
				else if(i == width - 1)		// right
				{
					if
					(
						!((cur - width)->marked
						&&	(cur - width - 1)->marked
						&&	(cur - 1)->marked
						&&	(cur + width)->marked
						&&	(cur + width - 1)->marked
						)
					) cur->edged = 1;
				}
				else						// normal
				{
					if
					(
						!((cur - width)->marked
						&&	(cur - 1)->marked
						&&	(cur + 1)->marked
						&&	(cur + width)->marked
						)
					) cur->edged = 1;
				}
			}
			cur++;
		}
	}
}

void CCellView::OnProcSpecColor() 
{
	CColorDialog	cDlg;

	if(cDlg.DoModal() == IDOK)
	{
		COLORREF	cr = cDlg.GetColor();
		spec_rgb.b = cr >> 16 & 0xff;
		spec_rgb.g = cr >> 8 & 0xff;
		spec_rgb.r = cr & 0xff;
		InvalidateRect(0, TRUE);
	}
}

void CCellView::OnDispEdge() 
{
	if (g_hBitmap)
	{
		if(!m_bIsDispEdge)
		{
			m_bIsDispEdge = true;
			AfxGetApp()->m_pMainWnd->GetMenu()->CheckMenuItem(ID_DISP_EDGE, MF_CHECKED);
			AfxGetApp()->m_pMainWnd->GetMenu()->CheckMenuItem(ID_DISP_REGION, MF_UNCHECKED);
			InvalidateRect(0, TRUE);
		}
	}
	else
		MessageBox("请先打开文件");
}

void CCellView::OnDispRegion() 
{
	if (g_hBitmap)
	{
		if(m_bIsDispEdge)
		{
			m_bIsDispEdge = false;
			AfxGetApp()->m_pMainWnd->GetMenu()->CheckMenuItem(ID_DISP_REGION, MF_CHECKED);
			AfxGetApp()->m_pMainWnd->GetMenu()->CheckMenuItem(ID_DISP_EDGE, MF_UNCHECKED);
			InvalidateRect(0, TRUE);
		}
	}
	else
		MessageBox("请先打开文件");
}

void CCellView::OnDispSobel() 
{
	if (!g_hBitmap)
	{
		MessageBox("请先打开文件");
		return;
	}
	if (!g_pSobelResult)
	{
		MessageBox("请选择菜单[处理]-[显示→Sobel]来查看梯度信息");
		return;
	}
	m_bDispSobel ^= 1;
	if(m_bDispSobel)
		AfxGetApp()->m_pMainWnd->GetMenu()->CheckMenuItem(ID_DISP_SOBEL, MF_CHECKED);
	else
		AfxGetApp()->m_pMainWnd->GetMenu()->CheckMenuItem(ID_DISP_SOBEL, MF_UNCHECKED);
//	g_bImgBufferChanged=true;
	InvalidateRect(0, TRUE);
}

void CCellView::OnProcReload() 
{
	// TODO: Add your command handler code here
	if (g_hBitmap)
	{
		// g_pFlags置0
		memset(g_pFlags, 0,	g_nMapHeight * g_nMapWidth * sizeof(FLAGS));
//		memcpy(g_pImgBuffer,g_pOrgImgBuffer,sizeof(RGB)*g_nMapWidth*g_nMapHeight);
//		g_bImgBufferChanged=true;

		m_bProcHsi=false;
		m_bDispSobel=false;
		AfxGetApp()->m_pMainWnd->GetMenu()->CheckMenuItem(ID_DISP_SOBEL, MF_UNCHECKED);
		m_bIsDispEdge=false;
		AfxGetApp()->m_pMainWnd->GetMenu()->CheckMenuItem(ID_DISP_REGION, MF_CHECKED);
		AfxGetApp()->m_pMainWnd->GetMenu()->CheckMenuItem(ID_DISP_EDGE, MF_UNCHECKED);
		m_vCenterPoints.clear(); // 清除!
		InvalidateRect(0,TRUE);
	}
	else
		MessageBox("请先打开文件");
}

void CCellView::OnProcFindCenter() 
{
	if(g_hBitmap)
	{
		// backup
		memcpy(g_pFlagsBack,g_pFlags,
			sizeof(FLAGS)*g_nMapWidth*g_nMapHeight);

		int		pre_shrink_count;
		CSet setdlg;
		if (IDOK==setdlg.DoModal()) // 对话框.输入腐蚀次数
		{
			pre_shrink_count=setdlg.m_nPreCount;
		}
		else return;

		int i,j,x,y;
		FLAGS *cur_flag;
		// 先去掉pre_shrink_count层皮
		GenEdge();
		for (i=0;i<pre_shrink_count;i++)
		{
			cur_flag=g_pFlags;
			for(y = 0; y < g_nMapHeight; y++)
				for(x = 0; x < g_nMapWidth; x++)
				{
					// 去掉边界!
					if (cur_flag->edged)
						cur_flag->marked=0;
					cur_flag++;
				}
			if (i==0)
				GenEdge4();
			else
				GenEdge();
		}
		InvalidateRect(NULL,TRUE);
		MessageBox("去掉了噪声");

		cur_flag=g_pFlags; // 清除visited标志
		for(y = 0; y < g_nMapHeight; y++)
			for(x = 0; x < g_nMapWidth; x++)
			{
				cur_flag->visited=0;
				cur_flag->center=0;
				cur_flag++;
			}

		GenEdge();
		CENTER_POINT pt;
		points_temp.clear();
		bool changed;

		for (i=0;i<40;i++) // 标志中心点的腐蚀	
		{
			changed=false;
			// 清除visited标志
			cur_flag=g_pFlags;
			for(y = 0; y < g_nMapHeight; y++)
				for(x = 0; x < g_nMapWidth; x++)
				{
					cur_flag->visited=0;
					cur_flag++;
				}
			cur_flag=g_pFlags;
			for(y = 0; y < g_nMapHeight; y++)
				for(x = 0; x < g_nMapWidth; x++)
				{
					if (y>0 && y<g_nMapHeight-1 && x>0 && x<g_nMapWidth-1) // 最边上的不用处理
					{
						m_bFullEdge=true;
						if (cur_flag->edged && !cur_flag->visited) // 没有访问过的边界
						{
							if ( !(cur_flag-1)->marked &&
								 !(cur_flag+1)->marked &&
								 !(cur_flag+g_nMapWidth)->marked &&
								 !(cur_flag-g_nMapWidth)->marked )
//								 !(cur_flag+g_nMapWidth-1)->marked &&
//								 !(cur_flag+g_nMapWidth+1)->marked &&
//								 !(cur_flag-g_nMapWidth-1)->marked &&
//								 !(cur_flag-g_nMapWidth+1)->marked )
							{
								if (i==0) // 基本上这种是噪音
								{
									cur_flag++;
									continue;
								}
								// 孤立的点
								cur_flag->center=1;
								// 保存一下CENTER_POINT信息
								pt.x=x;
								pt.y=y;
								pt.radius=i+4+pre_shrink_count*2;
								points_temp.push_back(pt);

								cur_flag++;
								continue;
							}
							else
								MarkIt(x,y); // 判断是否需要保存

							if (m_bFullEdge) // 需要保存!
								SaveIt(x,y,i+6);
						}
					}
					cur_flag++;
				}

			cur_flag=g_pFlags;
			for(y = 0; y < g_nMapHeight; y++)
				for(x = 0; x < g_nMapWidth; x++)
				{
					// 去掉边界!
					if (cur_flag->edged)
					{
						changed=true;
						cur_flag->marked=0;
					}
					cur_flag++;
				}
			if (i%2==0)
				GenEdge4();
			else
				GenEdge();

			if (!changed)
				break;
		}

		// 清除visited标志
		cur_flag=g_pFlags;
		for(y = 0; y < g_nMapHeight; y++)
			for(x = 0; x < g_nMapWidth; x++)
			{
				cur_flag->visited=0;
				cur_flag++;
			}
		// 取平均值,获得中心点
		vector<CENTER_POINT>	points;
		cur_flag=g_pFlags;
		for(y = 0; y < g_nMapHeight; y++)
			for(x = 0; x < g_nMapWidth; x++)
			{
				if (y>0 && y<g_nMapHeight-1 && x>0 && x<g_nMapWidth-1) // 最边上的不用处理
				{
					if (cur_flag->center)
					{
						if ( !(cur_flag-1)->center && !(cur_flag+1)->center &&
							 !(cur_flag+g_nMapWidth)->center &&
							 !(cur_flag-g_nMapWidth)->center &&
							 !(cur_flag+g_nMapWidth-1)->center &&
							 !(cur_flag+g_nMapWidth+1)->center &&
							 !(cur_flag-g_nMapWidth-1)->center &&
							 !(cur_flag-g_nMapWidth+1)->center )
						{
							// 孤立的点
							pt.x=x;
							pt.y=y;
							points.push_back(pt);
							cur_flag++;
							continue;
						}
						else
						{
							tot_area=0;
							max_radius=0;
							tot_x=0;
							tot_y=0;
							CalcCenterArea(x,y);
							pt.x=tot_x/tot_area;
							pt.y=tot_y/tot_area;
							pt.radius=max_radius;
							g_pFlags[pt.y*g_nMapWidth+pt.x].center=1;
							points.push_back(pt);
						}
					}
				}
				cur_flag++;
			}

		m_vCenterPoints.clear();
		int x0,y0;
		bool adj;
		// 清除center标志
		cur_flag=g_pFlags;
		for(y = 0; y < g_nMapHeight; y++)
			for(x = 0; x < g_nMapWidth; x++)
			{
				cur_flag->center=0;
				cur_flag++;
			}
		// 平均化相近的中心点
		for (i=0;i<points.size();i++)
		{
			x0=points.at(i).x;
			y0=points.at(i).y;
			adj=false;
			for (j=i+1;j<points.size();j++)
			{
				x=points.at(j).x;
				y=points.at(j).y;
				if (abs(x0-x)+abs(y0-y)<10) // 相近
				{
					points.at(j).x=(x+x0)/2;
					points.at(j).y=(y+y0)/2;
					points.at(j).radius=points.at(i).radius;
					points.erase(&points.at(j));
					i--;
					adj=true;
					break;
				}
			}
			if (!adj) // 非相近
			{
				if (points.at(i).radius>5)
				{
					m_vCenterPoints.push_back(points.at(i));
					g_pFlags[points.at(i).y*g_nMapWidth+points.at(i).x].center=1;
				}
			}
		}

		double max_intensity=0.0;
		double hue,inte;
		double min_hue=255.0;
		double max_hue=0.0;
		double overmax;
		double overmin;
		if (m_vAllSelected.size()>0) // 保存着的选项
		{
			for (int i=0;i<m_vAllSelected.size();i++)
			{
				if (m_vAllSelected.at(i).Intensity>max_intensity)
					max_intensity=m_vAllSelected.at(i).Intensity;
				if (m_vAllSelected.at(i).Hue>max_hue)
					max_hue=m_vAllSelected.at(i).Hue;
				if (m_vAllSelected.at(i).Hue<min_hue)
					min_hue=m_vAllSelected.at(i).Hue;
			}

			InvalidateRect(0,TRUE);
			MessageBox("准备开始修正");
		}
		else
		{
			InvalidateRect(0,TRUE);
			return;
		}
		max_hue+=max_hue*0.02;
		min_hue-=min_hue*0.02;
		overmax=max_hue*1.08;
		overmin=min_hue*0.92;

		int r0,r;
		int tx,ty;
		int area,toobad;
		// 去掉被包含的圆
		for (i=0;i<m_vCenterPoints.size();i++)
		{
			x0=m_vCenterPoints.at(i).x;
			y0=m_vCenterPoints.at(i).y;
			r0=m_vCenterPoints.at(i).radius;
			for (j=i+1;j<m_vCenterPoints.size();j++)
			{
				x=m_vCenterPoints.at(j).x;
				y=m_vCenterPoints.at(j).y;
				r=m_vCenterPoints.at(j).radius;
				if (DISTANCE(x0,y0,x,y)<abs(r0-r)+4) // 包含
				{
					CDC *pdc=GetDC();
					CENTER_POINT centerp;
					CPen	pen;
					pen.CreatePen(PS_DOT, 1, RGB(255,0,0));
					pdc->SelectObject(pen);
					if (r0>r) // 去掉r0
						centerp=m_vCenterPoints.at(i);
					else
						centerp=m_vCenterPoints.at(j);
					Arc(pdc->m_hDC,
						centerp.x-scroll_lefttop.x-centerp.radius,
						centerp.y-scroll_lefttop.y-centerp.radius,
						centerp.x-scroll_lefttop.x+centerp.radius,
						centerp.y-scroll_lefttop.y+centerp.radius,
						centerp.x-scroll_lefttop.x+centerp.radius,
						centerp.y-scroll_lefttop.y,
						centerp.x-scroll_lefttop.x+centerp.radius,
						centerp.y-scroll_lefttop.y
						);
					DeleteObject(pen);
					if (r0>r) // 去掉r0
					{
						m_vCenterPoints.erase(&m_vCenterPoints.at(i));
						i--;
					}
					else
						m_vCenterPoints.erase(&m_vCenterPoints.at(j));
				}
			}
		}
		vector<CENTER_POINT> tocheck;
		int n,size,total;
		bool isok;
		// 去掉潜在的错误(同两个圆相交,并且不相交的部分是噪声)
		for (i=0;i<m_vCenterPoints.size();i++)
		{
			tocheck.clear();
			x0=m_vCenterPoints.at(i).x;
			y0=m_vCenterPoints.at(i).y;
			r0=m_vCenterPoints.at(i).radius;
			for (j=0;j<m_vCenterPoints.size();j++)
			{
				if (i==j)
					continue;
				x=m_vCenterPoints.at(j).x;
				y=m_vCenterPoints.at(j).y;
				r=m_vCenterPoints.at(j).radius;
				if (DISTANCE(x0,y0,x,y)<abs(r0+r)) // 相交
				{
					pt.x=x; pt.y=y; pt.radius=r;
					tocheck.push_back(pt);
				}
			}
			size=tocheck.size();
			if (size>1) // 同两个以上的圆相交
			{
				area=0;
				total=0;
				toobad=0;
				for (tx=x0-r0;tx<x0+r0;tx++)
					for (ty=y0-r0;ty<y0+r0;ty++)
					{
						if (DISTANCE(x0,y0,tx,ty)<r0) // 所有圆内部的点
						{
							if (tx<0 || tx>g_nMapWidth-1 || ty<0 || ty>g_nMapHeight-1)
								continue;
							isok=true;
							for (n=0;n<size;n++)
							{
								pt=tocheck.at(n);// 取得
								if (DISTANCE(tx,ty,pt.x,pt.y)<pt.radius)
								{
									isok=false;
									break;
								}
							}
							if (isok) // 同所有的圆都不相交的部分
							{
								total++;
								hue=g_pHSIBuffer[ty*g_nMapWidth+tx].Hue;
								inte=g_pHSIBuffer[ty*g_nMapWidth+tx].Intensity;
								if (inte>max_intensity || hue > max_hue || hue < min_hue)
									area++;
								if (hue > overmax || hue < overmin)
									toobad++;
							}
						}
					}
				if (total<r0*r0 || (total<r0*r0*1.5 && area>total*0.5) || toobad>total/6) // need adjust
				{
					CDC *pdc=GetDC();
					CENTER_POINT centerp;
					CPen	pen;
					if (total<r0*r0)			// 红色 面积过小
						pen.CreatePen(PS_SOLID, 2, RGB(255,0,0));
					else if (toobad>total/6)	// 绿色 错误点过多
						pen.CreatePen(PS_SOLID, 2, RGB(0,255,0));
					else						// 浅蓝 误差过大
						pen.CreatePen(PS_SOLID, 2, RGB(0,255,255));
					pdc->SelectObject(pen);
					centerp=m_vCenterPoints.at(i);
					Arc(pdc->m_hDC,
						centerp.x-scroll_lefttop.x-centerp.radius,
						centerp.y-scroll_lefttop.y-centerp.radius,
						centerp.x-scroll_lefttop.x+centerp.radius,
						centerp.y-scroll_lefttop.y+centerp.radius,
						centerp.x-scroll_lefttop.x+centerp.radius,
						centerp.y-scroll_lefttop.y,
						centerp.x-scroll_lefttop.x+centerp.radius,
						centerp.y-scroll_lefttop.y
						);
					DeleteObject(pen);
					m_vCenterPoints.erase(&m_vCenterPoints.at(i));
					i--;
				}
			}
		}
		for (i=0;i<m_vCenterPoints.size();i++)
		{
			r0=m_vCenterPoints.at(i).radius;
			if (r0<10)
			{
				x0=m_vCenterPoints.at(i).x;
				y0=m_vCenterPoints.at(i).y;
				area=0;
				toobad=0;
				for (tx=x0-r0;tx<x0+r0;tx++)
					for (ty=y0-r0;ty<y0+r0;ty++)
						if (sqrt((x0-tx)*(x0-tx)+(y0-ty)*(y0-ty))<r0)
						{
							if (tx<0 || tx>g_nMapWidth-1 || ty<0 || ty>g_nMapHeight-1)
								continue;
							hue=g_pHSIBuffer[ty*g_nMapWidth+tx].Hue;
							if (hue > max_hue || hue < min_hue)
								area++;
							if (hue > overmax || hue < overmin)
								toobad++;
						}
				if (area>r0*r0 || toobad>r0*r0/2) // need adjust
				{
					CDC *pdc=GetDC();
					CENTER_POINT centerp;
					CPen	pen;
					if (toobad>r0*r0/2)
						pen.CreatePen(PS_DOT, 1, RGB(0,128,0));
					else
						pen.CreatePen(PS_DOT, 1, RGB(0,0,255));
					pdc->SelectObject(pen);
					centerp=m_vCenterPoints.at(i);
					Arc(pdc->m_hDC,
						centerp.x-scroll_lefttop.x-centerp.radius,
						centerp.y-scroll_lefttop.y-centerp.radius,
						centerp.x-scroll_lefttop.x+centerp.radius,
						centerp.y-scroll_lefttop.y+centerp.radius,
						centerp.x-scroll_lefttop.x+centerp.radius,
						centerp.y-scroll_lefttop.y,
						centerp.x-scroll_lefttop.x+centerp.radius,
						centerp.y-scroll_lefttop.y
						);
					DeleteObject(pen);
					m_vCenterPoints.erase(&m_vCenterPoints.at(i));
					i--;
				}
			}
		}
/*		// 去掉潜在的错误(相交,并且包含许多色调范围外的象素)
		for (i=0;i<m_vCenterPoints.size();i++)
		{
			x0=m_vCenterPoints.at(i).x;
			y0=m_vCenterPoints.at(i).y;
			r0=m_vCenterPoints.at(i).radius;
			for (j=i+1;j<m_vCenterPoints.size();j++)
			{
				x=m_vCenterPoints.at(j).x;
				y=m_vCenterPoints.at(j).y;
				r=m_vCenterPoints.at(j).radius;
				if (sqrt((x0-x)*(x0-x)+(y0-y)*(y0-y))<abs(r0+r)) // 相交
				{
					area=0;
					toobad=0;
					for (tx=x0-r0;tx<x0+r0;tx++)
						for (ty=y0-r0;ty<y0+r0;ty++)
							if (sqrt((x0-tx)*(x0-tx)+(y0-ty)*(y0-ty))<r0)
							{
								if (tx<0 || tx>g_nMapWidth-1 || ty<0 || ty>g_nMapHeight-1)
									continue;
								hue=g_pHSIBuffer[ty*g_nMapWidth+tx].Hue;
								if (hue > max_hue || hue < min_hue)
									area++;
								if (hue > overmax || hue < overmin)
									toobad++;
							}
					if (area>r0*r0 || toobad>r0*r0/2) // need adjust
					{
						InvalidateRect(0,TRUE);
						{
							CDC *pdc=GetDC();
							CENTER_POINT centerp;
							CPen	pen;
							if (toobad>r0*r0/6)
								pen.CreatePen(PS_SOLID, 3, RGB(255,0,0));
							else
								pen.CreatePen(PS_SOLID, 3, RGB(0,0,0));
							pdc->SelectObject(pen);
							centerp=m_vCenterPoints.at(i);
							Arc(pdc->m_hDC,
								centerp.x-scroll_lefttop.x-centerp.radius,
								centerp.y-scroll_lefttop.y-centerp.radius,
								centerp.x-scroll_lefttop.x+centerp.radius,
								centerp.y-scroll_lefttop.y+centerp.radius,
								centerp.x-scroll_lefttop.x+centerp.radius,
								centerp.y-scroll_lefttop.y,
								centerp.x-scroll_lefttop.x+centerp.radius,
								centerp.y-scroll_lefttop.y
								);
							DeleteObject(pen);
						}
						m_vCenterPoints.erase(&m_vCenterPoints.at(i));
						i--;
						Sleep(2000);
						break;
					}
				}
			}
		}
*///		Sleep(10000);
//		InvalidateRect(0,TRUE);
	}
	else
		MessageBox("请先打开图像文件!");

}

void CCellView::MarkIt(int i, int j)
{
//	if (!m_bFullEdge)
//		return; // 如果已经知道不是FullEdge了,那么不用做了!
	if (i<1 || i>g_nMapWidth-2 || j<1 || j>g_nMapHeight-2)
	{
		return;
	}
	g_pFlags[j*g_nMapWidth+i].visited=1;
	if ( !g_pFlags[j*g_nMapWidth+i-1].visited &&	// 没有访问过
		  g_pFlags[j*g_nMapWidth+i-1].marked )		// 标志了
	{
		if (g_pFlags[j*g_nMapWidth+i-1].edged )		// 并且是边缘
			MarkIt(i-1,j); // 左边
		else
			m_bFullEdge=false;
	}

	if ( !g_pFlags[j*g_nMapWidth+i+1].visited &&	// 没有访问过
		  g_pFlags[j*g_nMapWidth+i+1].marked )		// 标志了
	{
		if (g_pFlags[j*g_nMapWidth+i+1].edged )		// 并且是边缘
			MarkIt(i+1,j); // 右边
		else
			m_bFullEdge=false;
	}

	if ( !g_pFlags[(j-1)*g_nMapWidth+i].visited &&	// 没有访问过
		  g_pFlags[(j-1)*g_nMapWidth+i].marked )	// 标志了
	{
		if (g_pFlags[(j-1)*g_nMapWidth+i].edged )		// 并且是边缘
			MarkIt(i,j-1); // 上面
		else
			m_bFullEdge=false;
	}

	if ( !g_pFlags[(j+1)*g_nMapWidth+i].visited &&	// 没有访问过
		  g_pFlags[(j+1)*g_nMapWidth+i].marked )	// 标志了
	{
		if (g_pFlags[(j+1)*g_nMapWidth+i].edged )		// 并且是边缘
			MarkIt(i,j+1); // 下面
		else
			m_bFullEdge=false;
	}

	if ( !g_pFlags[(j-1)*g_nMapWidth+i-1].visited &&	// 没有访问过
		  g_pFlags[(j-1)*g_nMapWidth+i-1].marked )		// 标志了
	{
		if (g_pFlags[(j-1)*g_nMapWidth+i-1].edged )		// 并且是边缘
			MarkIt(i-1,j-1); // 左上
		else
			m_bFullEdge=false;
	}

	if ( !g_pFlags[(j+1)*g_nMapWidth+i-1].visited &&	// 没有访问过
		  g_pFlags[(j+1)*g_nMapWidth+i-1].marked )		// 标志了
	{
		if (g_pFlags[(j+1)*g_nMapWidth+i-1].edged )		// 并且是边缘
			MarkIt(i-1,j+1); // 左下
		else
			m_bFullEdge=false;
	}

	if ( !g_pFlags[(j-1)*g_nMapWidth+i+1].visited &&	// 没有访问过
		  g_pFlags[(j-1)*g_nMapWidth+i+1].marked )		// 标志了
	{
		if (g_pFlags[(j-1)*g_nMapWidth+i+1].edged )		// 并且是边缘
			MarkIt(i+1,j-1); // 右上
		else
			m_bFullEdge=false;
	}

	if ( !g_pFlags[(j+1)*g_nMapWidth+i+1].visited &&	// 没有访问过
		  g_pFlags[(j+1)*g_nMapWidth+i+1].marked )		// 标志了
	{
		if (g_pFlags[(j+1)*g_nMapWidth+i+1].edged )		// 并且是边缘
			MarkIt(i+1,j+1); // 右下
		else
			m_bFullEdge=false;
	}
}

void CCellView::SaveIt(int i, int j, int radius)
{
	if (i<1 || i>g_nMapWidth-2 || j<1 || j>g_nMapHeight-2)
	{
		return;
	}
	CENTER_POINT pt;
	pt.x=i;
	pt.y=j;
	pt.radius=radius;
	points_temp.push_back(pt);

	// marke current point
	g_pFlags[j*g_nMapWidth+i].center=1;
	g_pFlags[j*g_nMapWidth+i].visited=0;

	if ( g_pFlags[j*g_nMapWidth+i-1].visited )
	{
		SaveIt(i-1,j,radius);
	}
	if ( g_pFlags[j*g_nMapWidth+i+1].visited )
	{
		SaveIt(i+1,j,radius);
	}
	if ( g_pFlags[(j-1)*g_nMapWidth+i].visited )
	{
		SaveIt(i,j-1,radius);
	}
	if ( g_pFlags[(j+1)*g_nMapWidth+i].visited )
	{
		SaveIt(i,j+1,radius);
	}

	if ( g_pFlags[(j+1)*g_nMapWidth+i+1].visited )
	{
		SaveIt(i+1,j+1,radius);
	}
	if ( g_pFlags[(j+1)*g_nMapWidth+i-1].visited )
	{
		SaveIt(i-1,j+1,radius);
	}
	if ( g_pFlags[(j-1)*g_nMapWidth+i+1].visited )
	{
		SaveIt(i+1,j-1,radius);
	}
	if ( g_pFlags[(j-1)*g_nMapWidth+i-1].visited )
	{
		SaveIt(i-1,j-1,radius);
	}
}

// 利用sobel信息进行修正
void CCellView::OnProcSobelCorrect() 
{
	if (!g_hBitmap)
	{
		MessageBox("请先打开图片");
		return;
	}
	// backup
	memcpy(g_pFlagsBack,g_pFlags,
		sizeof(FLAGS)*g_nMapWidth*g_nMapHeight);

	double max_intensity=0.0;
	double min_hue=255.0;
	double max_hue=0.0;
	if (m_vAllSelected.size()) // 还保存着啊!
		for (int i=0;i<m_vAllSelected.size();i++)
		{
			if (m_vAllSelected.at(i).Intensity>max_intensity)
				max_intensity=m_vAllSelected.at(i).Intensity;
			if (m_vAllSelected.at(i).Hue>max_hue)
				max_hue=m_vAllSelected.at(i).Hue;
			if (m_vAllSelected.at(i).Hue<min_hue)
				min_hue=m_vAllSelected.at(i).Hue;
		}
	max_hue-=max_hue*0.1;
	min_hue+=min_hue*0.1;

	int x,y;
	FLAGS *cur_flag=g_pFlags;
	BYTE  *cur_sobel=g_pSobelResult;
	HSI   *cur_hsi=g_pHSIBuffer;
	for(y = 0; y < g_nMapHeight; y++)
		for(x = 0; x < g_nMapWidth; x++)
		{
			if ( cur_flag->marked )
			{
				if (*cur_sobel > 40) // 参数需要调整
				{
					if (max_intensity>0.01)
						if (/*cur_hsi->Intensity>max_intensity &&*/ // 亮度大于最大值并且色调超出范围
							(cur_hsi->Hue>max_hue || cur_hsi->Hue<min_hue) )
							cur_flag->marked=0;
				}
			}

			cur_hsi++;
			cur_flag++;
			cur_sobel++;
		}
	GenEdge();
	InvalidateRect(0,TRUE);
}

void CCellView::CalcCenterArea(int i, int j)
{
	if (i<1 || i>g_nMapWidth-2 || j<1 || j>g_nMapHeight-2)
	{
		return;
	}
	tot_area++;
	tot_x+=i;
	tot_y+=j;
	g_pFlags[j*g_nMapWidth+i].center=0;

	for ( int n=0; n<points_temp.size(); n++ )
	{
		if (points_temp.at(n).x==i && points_temp.at(n).y==j)
		{
			if (points_temp.at(n).radius>max_radius)
				max_radius=points_temp.at(n).radius;
			break;
		}
	}

	if ( g_pFlags[j*g_nMapWidth+i-1].center )
	{
		CalcCenterArea(i-1,j);
	}
	if ( g_pFlags[j*g_nMapWidth+i+1].center )
	{
		CalcCenterArea(i+1,j);
	}
	if ( g_pFlags[(j-1)*g_nMapWidth+i].center )
	{
		CalcCenterArea(i,j-1);
	}
	if ( g_pFlags[(j+1)*g_nMapWidth+i].center )
	{
		CalcCenterArea(i,j+1);
	}

	if ( g_pFlags[(j+1)*g_nMapWidth+i+1].center )
	{
		CalcCenterArea(i+1,j+1);
	}
	if ( g_pFlags[(j+1)*g_nMapWidth+i-1].center )
	{
		CalcCenterArea(i-1,j+1);
	}
	if ( g_pFlags[(j-1)*g_nMapWidth+i+1].center )
	{
		CalcCenterArea(i+1,j-1);
	}
	if ( g_pFlags[(j-1)*g_nMapWidth+i-1].center )
	{
		CalcCenterArea(i-1,j-1);
	}
}

void CCellView::OnProcForceKill() 
{
	// TODO: Add your command handler code here
	if(g_hBitmap)
	{
		m_bForceKill = true;
	}
	else
		MessageBox("请先打开图像文件!");
}

void CCellView::OnProcForceSele() 
{
	// TODO: Add your command handler code here
	if(g_hBitmap)
	{
		m_bForceAdd = true;
	}
	else
		MessageBox("请先打开图像文件!");
}

void CCellView::OnProcDilation() 
{
	if (g_bDir4Dil)
		g_bDir4Dil=false;
	else g_bDir4Dil=true;

	// backup
	memcpy(g_pFlagsBack,g_pFlags,
		sizeof(FLAGS)*g_nMapWidth*g_nMapHeight);

	// 膨胀
	RGB *cur=g_pImgBuffer;
	FLAGS *cur_flag=g_pFlags;

	vector<long> addr;
	for (int ht=0;ht<g_nMapHeight;ht++)
		for (int wd=0;wd<g_nMapWidth;wd++)
		{
			if (!cur_flag->marked)
			{
				if (ht==0 || wd==0 || ht==g_nMapHeight-1 || wd==g_nMapWidth-1)
				{
					cur++;
					cur_flag++;
					continue;
				}
				else if (g_bDir4Dil)
				{
					if (  (cur_flag-1)->marked || // left
						  (cur_flag+1)->marked || // right
						  (cur_flag-g_nMapWidth-1)->marked || // left up
						  (cur_flag-g_nMapWidth+1)->marked || // right up
						  (cur_flag+g_nMapWidth-1)->marked || // left down
						  (cur_flag+g_nMapWidth+1)->marked || // right down
						  (cur_flag-g_nMapWidth)->marked || // up
						  (cur_flag+g_nMapWidth)->marked ) // down
						addr.push_back((long)cur_flag);
				}
				else
				{
					if (  (cur_flag-1)->marked || // left
						  (cur_flag+1)->marked || // right
						  (cur_flag-g_nMapWidth)->marked || // up
						  (cur_flag+g_nMapWidth)->marked ) // down
						addr.push_back((long)cur_flag);
				}
			}
			cur++;
			cur_flag++;
		}

	int size=addr.size();
	for (int i=0;i<size;i++)
		((FLAGS *)addr.at(i))->marked=1;
	addr.clear();

	GenEdge();

	InvalidateRect(0,TRUE);
}

void CCellView::OnProcErosion() 
{
	if (g_bDir4Ero)
		g_bDir4Ero=false;
	else g_bDir4Ero=true;

	// backup
	memcpy(g_pFlagsBack,g_pFlags,
		sizeof(FLAGS)*g_nMapWidth*g_nMapHeight);

	// 腐蚀
	RGB *cur=g_pImgBuffer;
	FLAGS *cur_flag=g_pFlags;

	vector<long> addr;
	for (int ht=0;ht<g_nMapHeight;ht++)
		for (int wd=0;wd<g_nMapWidth;wd++)
		{
			if (cur_flag->marked)
			{
				if (ht==0 || wd==0 || ht==g_nMapHeight-1 || wd==g_nMapWidth-1)
				{
					cur_flag->marked=0;
					cur++;
					cur_flag++;
					continue;
				}
				else if (g_bDir4Ero)
				{
					if (  !(cur_flag-1)->marked || // left
						  !(cur_flag+1)->marked || // right
						  !(cur_flag-g_nMapWidth-1)->marked || // left up
						  !(cur_flag-g_nMapWidth+1)->marked || // right up
						  !(cur_flag+g_nMapWidth-1)->marked || // left down
						  !(cur_flag+g_nMapWidth+1)->marked || // right down
						  !(cur_flag-g_nMapWidth)->marked || // up
						  !(cur_flag+g_nMapWidth)->marked ) // down
						addr.push_back((long)cur_flag);
				}
				else
				{
					if (  !(cur_flag-1)->marked || // left
						  !(cur_flag+1)->marked || // right
						  !(cur_flag-g_nMapWidth)->marked || // up
						  !(cur_flag+g_nMapWidth)->marked ) // down
						addr.push_back((long)cur_flag);
				}
			}
			cur++;
			cur_flag++;
		}

	int size=addr.size();
	for (int i=0;i<size;i++)
		((FLAGS *)addr.at(i))->marked=0;
	addr.clear();

	GenEdge();

	InvalidateRect(0,TRUE);
}

void CCellView::OnProcSmooth() 
{
	int wd,ht;
	if(g_hBitmap)
	{//申请与图像同样大小的空间
		RGB *g_pTemp=new RGB[g_nMapWidth*g_nMapHeight];
		RGB *ptemp=g_pTemp;
		//目标区域内容清空
		memset(g_pTemp,0,g_nMapWidth*g_nMapHeight*sizeof(RGB));
		RGB *cur=g_pImgBuffer;
		for (ht=0;ht<g_nMapHeight;ht++)
			for (wd=0;wd<g_nMapWidth;wd++)
			{
				if (ht==0 || wd==0 || ht==g_nMapHeight-1 || wd==g_nMapWidth-1)
				{ }
				else
				{//对当前点周围的9个点取平均，对R进行操作
					ptemp->r=( (cur-g_nMapWidth-1)->r +
								 (cur-g_nMapWidth  )->r +
								 (cur-g_nMapWidth+1)->r +
								 (cur-1)->r +
								 cur->r +
								 (cur+1)->r +
								 (cur+g_nMapWidth-1)->r +
								 (cur+g_nMapWidth  )->r +
								 (cur+g_nMapWidth+1)->r )/9;
					//对当前点周围的9个点取平均，对G进行操作
					ptemp->g=( (cur-g_nMapWidth-1)->g +
								 (cur-g_nMapWidth  )->g +
								 (cur-g_nMapWidth+1)->g +
								 (cur-1)->g +
								 cur->g +
								 (cur+1)->g +
								 (cur+g_nMapWidth-1)->g +
								 (cur+g_nMapWidth  )->g +
								 (cur+g_nMapWidth+1)->g )/9;
					//对当前点周围的9个点取平均，对B进行操作
					ptemp->b=( (cur-g_nMapWidth-1)->b +
								 (cur-g_nMapWidth  )->b +
								 (cur-g_nMapWidth+1)->b +
								 (cur-1)->b +
								 cur->b +
								 (cur+1)->b +
								 (cur+g_nMapWidth-1)->b +
								 (cur+g_nMapWidth  )->b +
								 (cur+g_nMapWidth+1)->b )/9;
				}
				cur++;
				ptemp++;
			}
			//保存计算得到的值
		memcpy(g_pImgBuffer,g_pTemp,g_nMapWidth*g_nMapHeight*sizeof(RGB));
		delete[] g_pTemp;
		InvalidateRect(0,TRUE);
	}
	else
		MessageBox("请先打开图像文件!");
}

void CCellView::CountSeeds()
{
	int wd,ht;
	FLAGS *cur_flag;

	g_nCellCount=0;
	g_nCellTotArea=0;

	cur_flag=g_pFlags;
	for (ht=0;ht<g_nMapHeight;ht++)
		for (wd=0;wd<g_nMapWidth;wd++)
		{
			cur_flag->visited=0; // clear visited
			cur_flag++;
		}

	cur_flag=g_pFlags;
	for (ht=0;ht<g_nMapHeight;ht++)
		for (wd=0;wd<g_nMapWidth;wd++)
		{
			if (cur_flag->marked && !cur_flag->visited)
			{
				g_nCellCount++;
				ProcessCountSeeds(wd,ht,cur_flag);
			}
			cur_flag++;
		}

	InvalidateRect(0,TRUE);

	char msg[256];
	double avgarea=(double)g_nCellTotArea/(double)g_nCellCount;
	sprintf(msg,"一共有%d个细胞,平均面积%d象素(大约%d*%d)",
		g_nCellCount,(int)avgarea,(int)sqrt(avgarea),(int)sqrt(avgarea));
	MessageBox(msg);
}

void CCellView::ProcessCountSeeds(int wd, int ht, FLAGS *curf)
{
	if (wd<0 || wd>g_nMapWidth-1 || ht<0 || ht>g_nMapHeight-1)
		return;
	FLAGS *next;
	g_nCellTotArea++;
	curf->visited=1;
	if (ht>0)
	{
		next=curf-g_nMapWidth;
		if (next->marked && !next->visited)
			ProcessCountSeeds(wd,ht-1,next); // up
	}
	if (ht<g_nMapHeight-1)
	{
		next=curf+g_nMapWidth;
		if (next->marked && !next->visited)
			ProcessCountSeeds(wd,ht+1,next); // down
	}
	if (wd>0)
	{
		next=curf-1;
		if (next->marked && !next->visited)
			ProcessCountSeeds(wd-1,ht,next); // left
	}
	if (wd<g_nMapWidth-1)
	{
		next=curf+1;
		if (next->marked && !next->visited)
			ProcessCountSeeds(wd+1,ht,next); // right
	}
}

void CCellView::OnProcStat() 
{
	int result;
	result=MessageBox("是否使用中心点标注信息?",NULL,MB_YESNO);
	if (result==IDYES)
	{
		CounterSeedsCenter();
	}
	else
	{
		CountSeeds();
	}
}

void CCellView::CounterSeedsCenter()
{
	if (m_vCenterPoints.size==0)
		MessageBox("中心点数据似乎没有生成...");
	else
	{
		long tota,totr;
		tota=0; totr=0;
		for (int i=0;i<m_vCenterPoints.size();i++)
		{
			tota+=m_vCenterPoints.at(i).radius*m_vCenterPoints.at(i).radius*3.14;
			totr+=m_vCenterPoints.at(i).radius;
		}
		char msg[256];
		sprintf(msg,"共有%d个细胞,平均半径%d,平均面积%d",
			m_vCenterPoints.size(),
			totr/m_vCenterPoints.size(),
			tota/m_vCenterPoints.size());
		MessageBox(msg);
	}
}

void CCellView::FillHoles()
{
	int wd,ht;
	FLAGS *cur_flag=g_pFlags;

	// backup
	memcpy(g_pFlagsBack,g_pFlags,
		sizeof(FLAGS)*g_nMapWidth*g_nMapHeight);

	qSz=g_nMapWidth*g_nMapHeight*2;
	qh=new int[qSz+1];
	if(!qh) return;

	for (ht=0;ht<g_nMapHeight;ht++)
		for (wd=0;wd<g_nMapWidth;wd++)
		{
			cur_flag->visited=0; // clear visited
			cur_flag++;
		}

	cur_flag=g_pFlags;
	for (ht=0;ht<g_nMapHeight;ht++)
		for (wd=0;wd<g_nMapWidth;wd++)
		{
			if (!cur_flag->marked && !cur_flag->visited)
			{
				g_nCellTotArea=0;
				ProcessFillHoles(wd,ht);
				if (g_nCellTotArea<MAX_HOLE && g_nCellTotArea>0)
					FillTheHole(wd,ht);
//				char msg[128];
//				sprintf(msg,"%d",g_nCellTotArea);
//				InvalidateRect(0,TRUE);
//				MessageBox(msg);
			}
			cur_flag++;
		}

	delete[] qh;
	GenEdge();
	InvalidateRect(0,TRUE);
}

void CCellView::ProcessFillHoles(int wd, int ht)
{
	if (wd<0 || wd>g_nMapWidth-1 || ht<0 || ht>g_nMapHeight-1)
		return;
	qst=qh;
	memset(qst,0,qSz); //Clear the contents
	qs=qr=qst;
	*qs=xt=wd;
	qs++;
	*qs=yt=ht;
	qs++;
	g_pFlags[INDEX(xt,yt)].visited=1;
	g_nCellTotArea++;

	//Main queue loop
	while(qr!=qs)
	{
		//Add new members to queue
		//Above current pixel
		if (yt>0)
		if(!g_pFlags[(yt-1)*g_nMapWidth+xt].visited &&
			!g_pFlags[(yt-1)*g_nMapWidth+xt].marked)
		{
			g_nCellTotArea++;
			*qs=xt;
			qs++;
			*qs=yt-1;
			qs++;
			g_pFlags[(yt-1)*g_nMapWidth+xt].visited=1;
		}
		//Below current pixel
		if (yt<g_nMapHeight-1)
		if(!g_pFlags[(yt+1)*g_nMapWidth+xt].visited &&
			!g_pFlags[(yt+1)*g_nMapWidth+xt].marked)
		{
			g_nCellTotArea++;
			*qs=xt;
			qs++;
			*qs=yt+1;
			qs++;
			g_pFlags[(yt+1)*g_nMapWidth+xt].visited=1;
		}
		//Left of current pixel
		if (xt>0)
		if(!g_pFlags[yt*g_nMapWidth+xt-1].visited &&
			!g_pFlags[yt*g_nMapWidth+xt-1].marked)
		{
			g_nCellTotArea++;
			*qs=xt-1;
			qs++;
			*qs=yt;
			qs++;
			g_pFlags[yt*g_nMapWidth+xt-1].visited=1;
		}
		//Right of current pixel
		if (yt<g_nMapWidth-1)
		if(!g_pFlags[yt*g_nMapWidth+xt+1].visited &&
			!g_pFlags[yt*g_nMapWidth+xt+1].marked)
		{
			g_nCellTotArea++;
			*qs=xt+1;
			qs++;
			*qs=yt;
			qs++;
			g_pFlags[yt*g_nMapWidth+xt+1].visited=1;
		}

		//Retrieve current queue member
		qr+=2;
		xt=*qr;
		yt=*(qr+1);
	} //Back to beginning of loop
}

void CCellView::FillTheHole(int wd, int ht)
{
	if (wd<0 || wd>g_nMapWidth-1 || ht<0 || ht>g_nMapHeight-1)
		return;
	g_nCellTotArea--;
	if (g_nCellTotArea<0)
		return;
	qst=qh;
	memset(qst,0,qSz); //Clear the contents
	qs=qr=qst;
	*qs=xt=wd;
	qs++;
	*qs=yt=ht;
	qs++;
	g_pFlags[INDEX(xt,yt)].marked=1;

	//Main queue loop
	while(qr!=qs)
	{
		//Add new members to queue
		//Above current pixel
		if (yt>0)
		if(g_pFlags[(yt-1)*g_nMapWidth+xt].visited &&
			!g_pFlags[(yt-1)*g_nMapWidth+xt].marked)
		{
			g_nCellTotArea--;
			if (g_nCellTotArea<0)
				return;
			*qs=xt;
			qs++;
			*qs=yt-1;
			qs++;
			g_pFlags[(yt-1)*g_nMapWidth+xt].marked=1;
		}
		//Below current pixel
		if (yt<g_nMapHeight-1)
		if(g_pFlags[(yt+1)*g_nMapWidth+xt].visited &&
			!g_pFlags[(yt+1)*g_nMapWidth+xt].marked)
		{
			g_nCellTotArea--;
			if (g_nCellTotArea<0)
				return;
			*qs=xt;
			qs++;
			*qs=yt+1;
			qs++;
			g_pFlags[(yt+1)*g_nMapWidth+xt].marked=1;
		}
		//Left of current pixel
		if (xt>0)
		if(g_pFlags[yt*g_nMapWidth+xt-1].visited &&
			!g_pFlags[yt*g_nMapWidth+xt-1].marked)
		{
			g_nCellTotArea--;
			if (g_nCellTotArea<0)
				return;
			*qs=xt-1;
			qs++;
			*qs=yt;
			qs++;
			g_pFlags[yt*g_nMapWidth+xt-1].marked=1;
		}
		//Right of current pixel
		if (yt<g_nMapWidth-1)
		if(g_pFlags[yt*g_nMapWidth+xt+1].visited &&
			!g_pFlags[yt*g_nMapWidth+xt+1].marked)
		{
			g_nCellTotArea--;
			if (g_nCellTotArea<0)
				return;
			*qs=xt+1;
			qs++;
			*qs=yt;
			qs++;
			g_pFlags[yt*g_nMapWidth+xt+1].marked=1;
		}

		//Retrieve current queue member
		qr+=2;
		xt=*qr;
		yt=*(qr+1);
	} //Back to beginning of loop
}
