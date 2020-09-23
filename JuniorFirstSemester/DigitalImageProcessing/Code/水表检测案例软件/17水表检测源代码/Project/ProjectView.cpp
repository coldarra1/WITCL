// ProjectView.cpp : implementation of the CProjectView class
//

#include "stdafx.h"
#include "Project.h"
#include "ChildFrm.h"
#include "math.h"
#include "ResultDlg.h"

#include "ProjectDoc.h"
#include "ProjectView.h"
#include "HistGramDoc.h"
#include "MainFrm.h"

#include "BmpBaseInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProjectView

IMPLEMENT_DYNCREATE(CProjectView, CScrollView)

BEGIN_MESSAGE_MAP(CProjectView, CScrollView)
	//{{AFX_MSG_MAP(CProjectView)
	ON_COMMAND(ID_BASEINFO_HIST, OnBaseinfoHist)
	ON_COMMAND(ID_BASEINFO_INFO, OnBaseinfoInfo)
	ON_COMMAND(ID_EDGE_ROBERTS, OnEdgeRoberts)
	ON_COMMAND(ID_EDGE_PREWITT, OnEdgePrewitt)
	ON_COMMAND(ID_EDGE_SOBEL, OnEdgeSobel)
	ON_COMMAND(ID_ADD_REVERSE, OnAddReverse)
	ON_COMMAND(ID_ADD_GLOBAL, OnAddGlobal)
	ON_COMMAND(ID_EDGE_LAPLACE, OnEdgeLaplace)
	ON_COMMAND(ID_ADD_CIRCLEDET, OnAddCircledet)
	ON_COMMAND(ID_ADD_SMALLCIR, OnAddSmallcir)
	ON_COMMAND(ID_WYG_STEP, OnWygStep)
	ON_COMMAND(ID_WYG_STEP2, OnWygStep2)
	ON_COMMAND(ID_ADD_TEST, OnAddTest)
	ON_COMMAND(ID_ADD_FINGER, OnAddFinger)
	ON_COMMAND(ID_ADD_END, OnAddEnd)
	ON_COMMAND(ID_ADD_PREWITT, OnAddPrewitt)
	ON_COMMAND(ID_ADD_TOTAL, OnAddTotal)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProjectView construction/destruction

CProjectView::CProjectView()
{
	// TODO: add construction code here

}

CProjectView::~CProjectView()
{
}

BOOL CProjectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CProjectView drawing

void CProjectView::OnDraw(CDC* pDC)
{
	pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	pDC->SetStretchBltMode(COLORONCOLOR);
	((CMainFrame *)AfxGetMainWnd())->SetStatus("正在绘制图像...");
	
	if (pDoc->bImageLoaded)
	{
		if (pDoc->BitCount == 8)   //8bit
		{
			DisplayBmp8(pDoc, pDC);
		}
		else    //24bit
		{
			DisplayBmp24(pDoc,pDC);
		}
	}
	((CMainFrame *)AfxGetMainWnd())->SetStatus("就绪");

}

void CProjectView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	//CSize sizeTotal;
	// TODO: calculate the total size of this view
	CProjectDoc * pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CSize sizeTotal;

	sizeTotal.cy = pDoc->BmpHeight;
	sizeTotal.cx = pDoc->BmpWidth;
	SetScrollSizes(MM_TEXT, sizeTotal);
	ResizeParentToFit(TRUE);

    //LPRECT pRect;
	//GetParentFrame()->RecalcLayout();// GetWindowRect(pRect);
	//SetScaleToFitSize(sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CProjectView printing

BOOL CProjectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CProjectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CProjectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CProjectView diagnostics

#ifdef _DEBUG
void CProjectView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CProjectView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CProjectDoc* CProjectView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProjectDoc)));
	return (CProjectDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CProjectView message handlers

void CProjectView::DisplayBmp8(CProjectDoc * pDoc, CDC * pDC)
{
	CRect rect;
	CSize sizeTotal;
	int nColorIndex, i, j, Width;
	BYTE btBlue,btGreen,btRed;
	COLORREF color;

	rect.top = 0;
	rect.left = 0;
	rect.right = pDoc->BmpWidth - 1;
	rect.bottom = pDoc->BmpHeight - 1;

	//调整视窗大小
	//sizeTotal.cx = pDoc->BmpWidth;
	//sizeTotal.cy = pDoc->BmpHeight;
	//SetScrollSizes(MM_TEXT, sizeTotal);

	if (pDoc->BmpWidth % 4 != 0)
	{
		Width = ((pDoc->BmpWidth / 4) + 1) * 4;
	}
	else
	{
		Width = pDoc->BmpWidth;
	}
	//AfxMessageBox(_ecvt(pDoc->pImage[0],10,&i,&j));

	for (j = 0; j < pDoc->BmpHeight; j++)
		for(i = 0; i < pDoc->BmpWidth; i ++)
		{
			nColorIndex = pDoc->pImage[j * Width + i];
			//nColorIndex = pDoc->pImage[j * pDoc->BmpWidth + i];
			btBlue = pDoc->pBitMapInfo->bmiColors[nColorIndex].rgbBlue;
			btGreen = pDoc->pBitMapInfo->bmiColors[nColorIndex].rgbGreen;
			btRed = pDoc->pBitMapInfo->bmiColors[nColorIndex].rgbRed;
			color = RGB(btBlue, btGreen, btRed);
			pDC->SetPixel(i,rect.bottom - j, color);
		}
}

void CProjectView::DisplayBmp24(CProjectDoc * pDoc, CDC * pDC)
{
	CRect rect;
	CSize sizeTotal;
	//int nColorIndex;
	int i, j, Width;
	BYTE btBlue,btGreen,btRed;
	COLORREF color;

	rect.top = 0;
	rect.left = 0;
	rect.right = pDoc->BmpWidth - 1;
	rect.bottom = pDoc->BmpHeight - 1;

	//调整视窗大小
	sizeTotal.cx = pDoc->BmpWidth;
	if (pDoc->BmpWidth % 4 != 0)
	{
		Width = ((pDoc->BmpWidth * 3 / 4) + 1) * 4;
	}
	else
	{
		Width = pDoc->BmpWidth * 3;
	}
	sizeTotal.cy = pDoc->BmpHeight;
	SetScrollSizes(MM_TEXT, sizeTotal);
	//AfxMessageBox(_ecvt(pDoc->pImage[0],10,&i,&j));

	for (j = 0; j < pDoc->BmpHeight; j++)
		for(i = 0; i < pDoc->BmpWidth; i ++)
		{
			btBlue = pDoc->pImage[j * Width + i * 3];
			btGreen = pDoc->pImage[j * Width + i * 3 + 1];
			btRed = pDoc->pImage[j * Width + i * 3 + 2];
			color = RGB(btRed, btGreen, btBlue);
			pDC->SetPixel(i,rect.bottom - j, color);
		}

}

//显示图像直方图
void CProjectView::OnBaseinfoHist() 
{
	CProjectDoc * pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: Add your command handler code here!
	//AfxMessageBox("Hist");
	//CreateNewFrame(pDoc);
	//CMultiDocTemplate *pTemplate=pDocTemplate.GetHead();
	//LPCTSTR lpszFileName;
	//AfxgetApp
	POSITION Pos;
	CMultiDocTemplate* pDocTemplate;
	CChildFrame * pFrame;
	CHistGramDoc * pHistDoc;

	Pos = AfxGetApp()->m_pDocManager->GetFirstDocTemplatePosition();
	pDocTemplate = (CMultiDocTemplate*)AfxGetApp()->m_pDocManager->GetNextDocTemplate(Pos);
	pDocTemplate = (CMultiDocTemplate*)AfxGetApp()->m_pDocManager->GetNextDocTemplate(Pos);

	pHistDoc = (CHistGramDoc *)pDocTemplate->CreateNewDocument();
	pFrame = (CChildFrame *)pDocTemplate->CreateNewFrame(pHistDoc, NULL);

	pHistDoc->SetDocument(pDoc);

	//pHistDoc->OnNewDocument();
	pDocTemplate->InitialUpdateFrame(pFrame,pHistDoc,TRUE);
} 

//显示图像基本信息
void CProjectView::OnBaseinfoInfo() 
{
	// TODO: Add your command handler code here
	CProjectDoc * pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CBmpBaseInfo dlgBaseInfo;
	dlgBaseInfo.SetInfo(pDoc);	
	((CMainFrame *)AfxGetMainWnd())->SetStatus("当前显示图像基本信息");
	dlgBaseInfo.DoModal();
	((CMainFrame *)AfxGetMainWnd())->SetStatus("就绪");

	//AfxMessageBox("haha");	
}

//Roberts算子菜单
void CProjectView::OnEdgeRoberts() 
{
	// TODO: Add your command handler code here
	CProjectDoc * pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: Add your command handler code here!
	//AfxMessageBox("Hist");
	//CreateNewFrame(pDoc);
	//CMultiDocTemplate *pTemplate=pDocTemplate.GetHead();
	//LPCTSTR lpszFileName;
	//AfxgetApp
	
	if (pDoc->BitCount != 8)
	{
		AfxMessageBox("本系统只处理256色的黑白图片！");
		return;
	}

	POSITION Pos;
	CMultiDocTemplate* pDocTemplate;
	CChildFrame * pFrame;
	CProjectDoc * pProjectDoc;

	Pos = AfxGetApp()->m_pDocManager->GetFirstDocTemplatePosition();
	pDocTemplate = (CMultiDocTemplate*)AfxGetApp()->m_pDocManager->GetNextDocTemplate(Pos);

	pProjectDoc = (CProjectDoc *)pDocTemplate->CreateNewDocument();
	pFrame = (CChildFrame *)pDocTemplate->CreateNewFrame(pProjectDoc, NULL);

	pProjectDoc->SetDocument(pDoc);
	
	EdgeRobert(pProjectDoc);

	//pHistDoc->OnNewDocument();
	pDocTemplate->InitialUpdateFrame(pFrame,pProjectDoc,TRUE);
	
}

void CProjectView::OnEdgePrewitt() 
{
	// TODO: Add your command handler code here
	CProjectDoc * pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: Add your command handler code here!
	//AfxMessageBox("Hist");
	//CreateNewFrame(pDoc);
	//CMultiDocTemplate *pTemplate=pDocTemplate.GetHead();
	//LPCTSTR lpszFileName;
	//AfxgetApp
	
	if (pDoc->BitCount != 8)
	{
		AfxMessageBox("本系统只处理256色的黑白图片！");
		return;
	}

	POSITION Pos;
	CMultiDocTemplate* pDocTemplate;
	CChildFrame * pFrame;
	CProjectDoc * pProjectDoc;

	Pos = AfxGetApp()->m_pDocManager->GetFirstDocTemplatePosition();
	pDocTemplate = (CMultiDocTemplate*)AfxGetApp()->m_pDocManager->GetNextDocTemplate(Pos);

	pProjectDoc = (CProjectDoc *)pDocTemplate->CreateNewDocument();
	pFrame = (CChildFrame *)pDocTemplate->CreateNewFrame(pProjectDoc, NULL);

	pProjectDoc->SetDocument(pDoc);

	EdgePrewitt(pProjectDoc);

	//pHistDoc->OnNewDocument();
	pDocTemplate->InitialUpdateFrame(pFrame,pProjectDoc,TRUE);	
}


void CProjectView::OnEdgeSobel() 
{
	// TODO: Add your command handler code here
	CProjectDoc * pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: Add your command handler code here!
	//AfxMessageBox("Hist");
	//CreateNewFrame(pDoc);
	//CMultiDocTemplate *pTemplate=pDocTemplate.GetHead();
	//LPCTSTR lpszFileName;
	//AfxgetApp
	
	if (pDoc->BitCount != 8)
	{
		AfxMessageBox("本系统只处理256色的黑白图片！");
		return;
	}

	POSITION Pos;
	CMultiDocTemplate* pDocTemplate;
	CChildFrame * pFrame;
	CProjectDoc * pProjectDoc;

	Pos = AfxGetApp()->m_pDocManager->GetFirstDocTemplatePosition();
	pDocTemplate = (CMultiDocTemplate*)AfxGetApp()->m_pDocManager->GetNextDocTemplate(Pos);

	pProjectDoc = (CProjectDoc *)pDocTemplate->CreateNewDocument();
	pFrame = (CChildFrame *)pDocTemplate->CreateNewFrame(pProjectDoc, NULL);

	pProjectDoc->SetDocument(pDoc);
	
	EdgeSobel(pProjectDoc);

	//pHistDoc->OnNewDocument();
	pDocTemplate->InitialUpdateFrame(pFrame,pProjectDoc,TRUE);
}

//拉普拉斯变换
void CProjectView::OnEdgeLaplace() 
{
	// TODO: Add your command handler code here
	CProjectDoc * pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: Add your command handler code here!
	//AfxMessageBox("Hist");
	//CreateNewFrame(pDoc);
	//CMultiDocTemplate *pTemplate=pDocTemplate.GetHead();
	//LPCTSTR lpszFileName;
	//AfxgetApp
	
	if (pDoc->BitCount != 8)
	{
		AfxMessageBox("本系统只处理256色的黑白图片！");
		return;
	}

	POSITION Pos;
	CMultiDocTemplate* pDocTemplate;
	CChildFrame * pFrame;
	CProjectDoc * pProjectDoc;

	Pos = AfxGetApp()->m_pDocManager->GetFirstDocTemplatePosition();
	pDocTemplate = (CMultiDocTemplate*)AfxGetApp()->m_pDocManager->GetNextDocTemplate(Pos);

	pProjectDoc = (CProjectDoc *)pDocTemplate->CreateNewDocument();
	pFrame = (CChildFrame *)pDocTemplate->CreateNewFrame(pProjectDoc, NULL);

	pProjectDoc->SetDocument(pDoc);
	
	EdgeLaplace(pProjectDoc);

	//pHistDoc->OnNewDocument();
	pDocTemplate->InitialUpdateFrame(pFrame,pProjectDoc,TRUE);
}

//图像反色操作
void CProjectView::OnAddReverse() 
{
	// TODO: Add your command handler code here

	CProjectDoc * pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	if (pDoc->BitCount != 8)
	{
		AfxMessageBox("本系统只处理256色的黑白图片！");
		return;
	}
	
	int i, j;
	for (i = 0; i < pDoc->BmpHeight; i ++)
	{
		for(j = 0; j < pDoc->BmpWidth; j ++)
		{
			pDoc->pImage[i * pDoc->nWidth + j] = 255 - pDoc->pImage[i * pDoc->nWidth + j];
		}
	}
	Invalidate(TRUE);
}

//全局阈值分割
void CProjectView::OnAddGlobal() 
{
	// TODO: Add your command handler code here
	CProjectDoc * pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	if (pDoc->BitCount != 8)
	{
		AfxMessageBox("本系统只处理256色的黑白图片！");
		return;
	}
	
	int i, j;
	long count;
	count = 0;
	for (i = 0; i < pDoc->BmpHeight; i ++)
	{
		for(j = 0; j < pDoc->BmpWidth; j ++)
		{
			//test1,全局阈值，198
			if (pDoc->pImage[i * pDoc->nWidth + j] > GLOBALVALUE)
				pDoc->pImage[i * pDoc->nWidth + j] = 255;
			else 
			{
				pDoc->pImage[i * pDoc->nWidth + j] = 0;
				count ++;
			}
/*
			if (pDoc->pImage[i * pDoc->nWidth + j] > 198)
				pDoc->pImage[i * pDoc->nWidth + j] = 255;
			else if (pDoc->pImage[i * pDoc->nWidth + j] < 50)
				pDoc->pImage[i * pDoc->nWidth + j] = 255;
			else
			{
				pDoc->pImage[i * pDoc->nWidth + j] = 0;
				count ++;
			}
*/
		}
	}
	Invalidate(TRUE);
    //AfxMessageBox(_ecvt(count, 10, &i, &j));
}

//利用变形Hough进行圆检测
void CProjectView::OnAddCircledet() 
{
	// TODO: Add your command handler code here
	CProjectDoc * pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	//CircleDetect(pDoc, STEP, 1, 50, 60, 15, &x, &y, 0.2);
	CircleDetect(pDoc, STEP, 1, XLEFT, XRIGHT, YTOP, YBOTTOM, BIGD, &x, &y, 0.2);

	Invalidate(TRUE);

}


void CProjectView::OnAddSmallcir() 
{
	// TODO: Add your command handler code here
	CProjectDoc * pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	//SmallCircleDetect(pDoc, );
	//CircleDetect(pDoc, SMALLSTEP, 0, 50, 60, 3, &x1, &y1, 0.2);
	//CircleDetect(pDoc, SMALLSTEP, 0, 50, 60, 3, &x2, &y2, 0.2);
	//CircleDetect(pDoc, SMALLSTEP, 0, 50, 60, 3, &x3, &y3, 0.2);

	CircleDetect(pDoc, SMALLSTEP, 0, SXLEFT, SXRIGHT, SYTOP, SYBOTTOM, SMALLD, &x1, &y1, 0.2);
	CircleDetect(pDoc, SMALLSTEP, 0, SXLEFT, SXRIGHT, SYTOP, SYBOTTOM, SMALLD, &x2, &y2, 0.2);
	CircleDetect(pDoc, SMALLSTEP, 0, SXLEFT, SXRIGHT, SYTOP, SYBOTTOM, SMALLD, &x3, &y3, 0.2);

	Invalidate(TRUE);

	/*
	CPen greenPen(PS_SOLID, 1, RGB(255,0,0));
	CClientDC pDC(this);
	pDC.SelectObject(greenPen);

	pDC.MoveTo(x1, y1);
	pDC.LineTo(x2, y2);
	pDC.MoveTo(x2, y2);
	pDC.LineTo(x3, y3);
	pDC.MoveTo(x3, y3);
	pDC.LineTo(x1, y1);

	pDC.MoveTo(100, 100);
	pDC.LineTo(300, 300);
    */

}
//Robert算子程序
void CProjectView::EdgeRobert(CProjectDoc* pProjectDoc)
{
	int * Robert1;
	int * Robert2;
	int i, j;
	int nWidth, nTemp1, nTemp2, nTemp3;

	Robert1 = (int *)LocalAlloc(LMEM_FIXED, 
		pProjectDoc->pBitMapInfo->bmiHeader.biSizeImage * 4);
	Robert2 = (int *)LocalAlloc(LMEM_FIXED, pProjectDoc->pBitMapInfo->bmiHeader.biSizeImage * 4);
	
	nWidth = pProjectDoc->nWidth;
    //AfxMessageBox(_ecvt(sizeof(int), 10, &i, &j));
	for (i = pProjectDoc->BmpHeight - 1; i > 1; i --)
		for(j = 0; j < pProjectDoc->BmpWidth - 1; j ++)
		{
			Robert1[i * nWidth + j] = (int)pProjectDoc->pImage[i * nWidth + j] -
				(int)pProjectDoc->pImage[(i-1) * nWidth + j + 1];

			Robert2[i * nWidth + j] = (int)pProjectDoc->pImage[i * nWidth + j + 1] -
				(int)pProjectDoc->pImage[(i-1) * nWidth + j];

			nTemp1 = Robert1[i * nWidth + j] * Robert1[i * nWidth + j];
			nTemp2 = Robert2[i * nWidth + j] * Robert2[i * nWidth + j];
			nTemp3 = (int)(sqrt(nTemp1 + nTemp2) + 0.5);
			if (nTemp3 > 255) 
				nTemp3 = 255;
			pProjectDoc->pImage[i * nWidth + j] = (BYTE)nTemp3;
		}

	LocalFree(Robert1);
	LocalFree(Robert2);
}

void CProjectView::EdgePrewitt(CProjectDoc* pProjectDoc)
{
	int * Robert1;
	int * Robert2;
	int i, j;
	int nWidth, nTemp1, nTemp2, nTemp3;

	Robert1 = (int *)LocalAlloc(LMEM_FIXED, 
		pProjectDoc->pBitMapInfo->bmiHeader.biSizeImage * 4);
	Robert2 = (int *)LocalAlloc(LMEM_FIXED, 
		pProjectDoc->pBitMapInfo->bmiHeader.biSizeImage * 4);
	
	nWidth = pProjectDoc->nWidth;

	for (i = pProjectDoc->BmpHeight - 1; i > 1; i --)
		for(j = 0; j < pProjectDoc->BmpWidth - 2; j ++)
		{
			Robert1[i * nWidth + j] = (int)(pProjectDoc->pImage[i * nWidth + j + 2] +
				(int)pProjectDoc->pImage[(i - 1) * nWidth + j + 2] +
				(int)pProjectDoc->pImage[(i - 2) * nWidth + j + 2] -
				(int)pProjectDoc->pImage[i * nWidth + j ] - 
				(int)pProjectDoc->pImage[(i - 1) * nWidth + j] - 
				(int)pProjectDoc->pImage[(i - 2) * nWidth + j]);
			Robert2[i * nWidth + j] = (int)(pProjectDoc->pImage[i * nWidth + j + 2] +
				(int)pProjectDoc->pImage[i * nWidth + j + 1] +
				(int)pProjectDoc->pImage[i * nWidth + j] -
				(int)pProjectDoc->pImage[(i - 2) * nWidth + j] - 
				(int)pProjectDoc->pImage[(i - 2) * nWidth + j + 1] - 
				(int)pProjectDoc->pImage[(i - 2) * nWidth + j + 2]);

			nTemp1 = Robert1[i * nWidth + j] * Robert1[i * nWidth + j];
			nTemp2 = Robert2[i * nWidth + j] * Robert2[i * nWidth + j];
			nTemp3 = (int)(sqrt(nTemp1 + nTemp2) + 0.5);
			if (nTemp3 > 255)
				nTemp3 = 255;
			pProjectDoc->pImage[i * nWidth + j] = (BYTE)nTemp3;
		}

	LocalFree(Robert1);
	LocalFree(Robert2);

}

void CProjectView::EdgeSobel(CProjectDoc* pProjectDoc)
{
	int * Robert1;
	int * Robert2;
	int i, j;
	int nWidth, nTemp1, nTemp2, nTemp3;

	Robert1 = (int *)LocalAlloc(LMEM_FIXED, 
		pProjectDoc->pBitMapInfo->bmiHeader.biSizeImage * 4);
	Robert2 = (int *)LocalAlloc(LMEM_FIXED, 
		pProjectDoc->pBitMapInfo->bmiHeader.biSizeImage * 4);
	
	nWidth = pProjectDoc->nWidth;

	for (i = pProjectDoc->BmpHeight - 1; i > 1; i --)
		for(j = 0; j < pProjectDoc->BmpWidth - 2; j ++)
		{
			Robert1[i * nWidth + j] = (int)(pProjectDoc->pImage[i * nWidth + j + 2] +
				(int)pProjectDoc->pImage[(i - 1) * nWidth + j + 2] * 2 +
				(int)pProjectDoc->pImage[(i - 2) * nWidth + j + 2] -
				(int)pProjectDoc->pImage[i * nWidth + j ] - 
				(int)pProjectDoc->pImage[(i - 1) * nWidth + j] * 2 - 
				(int)pProjectDoc->pImage[(i - 2) * nWidth + j]);
			Robert2[i * nWidth + j] = (int)(pProjectDoc->pImage[i * nWidth + j + 2] +
				(int)pProjectDoc->pImage[i * nWidth + j + 1] * 2+
				(int)pProjectDoc->pImage[i * nWidth + j] -
				(int)pProjectDoc->pImage[(i - 2) * nWidth + j] - 
				(int)pProjectDoc->pImage[(i - 2) * nWidth + j + 1] * 2 - 
				(int)pProjectDoc->pImage[(i - 2) * nWidth + j + 2]);

			nTemp1 = Robert1[i * nWidth + j] * Robert1[i * nWidth + j];
			nTemp2 = Robert2[i * nWidth + j] * Robert2[i * nWidth + j];
			nTemp3 = (int)(sqrt(nTemp1 + nTemp2) + 0.5);
			if (nTemp3 > 255)
				nTemp3 = 255;
			pProjectDoc->pImage[i * nWidth + j] = (BYTE)nTemp3;
		}

	LocalFree(Robert1);
	LocalFree(Robert2);

}


void CProjectView::EdgeLaplace(CProjectDoc* pProjectDoc)
{
//	int * Robert1;
//	int * Robert2;
	int i, j, h, k;
	int nWidth, nTemp1;
	//int nTemp2, nTemp3;

	int nLaplace[3][3] =   {{0,-1,0},
							{-1,4,-1},
							{0,-1,0}};
/*
	Robert1 = (int *)LocalAlloc(LMEM_FIXED, 
		pProjectDoc->pBitMapInfo->bmiHeader.biSizeImage * 4);
	Robert2 = (int *)LocalAlloc(LMEM_FIXED, 
		pProjectDoc->pBitMapInfo->bmiHeader.biSizeImage * 4);
*/	
	nWidth = pProjectDoc->nWidth;

	for (i = pProjectDoc->BmpHeight - 2; i > 0; i --)
		for(j = 1; j < pProjectDoc->BmpWidth - 1; j ++)
		{
			nTemp1 = 0;
			for (h = -1; h < 2; h ++)
				for(k = -1; k < 2; k ++)
				{
					nTemp1 += (int)pProjectDoc->pImage[(i+h) * nWidth + (j+k)] * 
						nLaplace[h][k];
				}
			if (nTemp1 < 0)
				nTemp1 = 0;
			else if (nTemp1 > 0)
				nTemp1 = 255;

			pProjectDoc->pImage[i * nWidth + j] = (BYTE) nTemp1;

/*
			Robert1[i * nWidth + j] = (int)(pProjectDoc->pImage[i * nWidth + j + 2] +
				(int)pProjectDoc->pImage[(i - 1) * nWidth + j + 2] * 2 +
				(int)pProjectDoc->pImage[(i - 2) * nWidth + j + 2] -
				(int)pProjectDoc->pImage[i * nWidth + j ] - 
				(int)pProjectDoc->pImage[(i - 1) * nWidth + j] * 2 - 
				(int)pProjectDoc->pImage[(i - 2) * nWidth + j]);
			Robert2[i * nWidth + j] = (int)(pProjectDoc->pImage[i * nWidth + j + 2] +
				(int)pProjectDoc->pImage[i * nWidth + j + 1] * 2+
				(int)pProjectDoc->pImage[i * nWidth + j] -
				(int)pProjectDoc->pImage[(i - 2) * nWidth + j] - 
				(int)pProjectDoc->pImage[(i - 2) * nWidth + j + 1] * 2 - 
				(int)pProjectDoc->pImage[(i - 2) * nWidth + j + 2]);

			nTemp1 = Robert1[i * nWidth + j] * Robert1[i * nWidth + j];
			nTemp2 = Robert2[i * nWidth + j] * Robert2[i * nWidth + j];
			nTemp3 = (int)(sqrt(nTemp1 + nTemp2) + 0.5);
			if (nTemp3 > 255)
				nTemp3 = 255;
			pProjectDoc->pImage[i * nWidth + j] = (BYTE)nTemp3;
*/		}
/*
	LocalFree(Robert1);
	LocalFree(Robert2);
*/
}




int CProjectView::SearchPoint(int StartX, int StartY, int QUEUE[][2], int * nHead, 
							  int * nTail, BYTE *DATA, int nLimitedX, int nLimitedY,
							  int Step, int nWidth)
{
	int i;
	//, nCount;

	if (Step < 2)
		return -1;
	for(i = 1; i < Step; i++)
	{
		//左上
		if ((StartX - Step + i >= 0) && (StartY + i < nLimitedY))
		{
			if (DATA[(StartY + i) * nWidth + StartX - Step + i] == 0)
			{
				* nTail = (*nTail) + 1;
				QUEUE[*nTail][0] = StartX - Step + i;
				QUEUE[*nTail][1] = StartY + i;
			}
		}
		//右上
		if ((StartX + i < nLimitedX) && (StartY + Step - i < nLimitedY))
		{
			if (DATA[(StartY + Step - i) * nWidth + StartX + i] == 0)
			{
				* nTail = (*nTail) + 1;
				QUEUE[*nTail][0] = StartX + i;
				QUEUE[*nTail][1] = StartY + Step - i;
			}
		}

		//右下
		if ((StartX + Step - i < nLimitedX) && (StartY - i >= 0))
		{
			if (DATA[(StartY - i) * nWidth + StartX + Step - i] == 0)
			{
				* nTail = (*nTail) + 1;
				QUEUE[*nTail][0] = StartX + Step - i;
				QUEUE[*nTail][1] = StartY - i;
			}
		}

		//左下
		if ((StartX - i >= 0) && (StartY - Step + i >= 0))
		{
			if (DATA[(StartY - Step + i) * nWidth + StartX - i] == 0)
			{
				* nTail = (*nTail) + 1;
				QUEUE[*nTail][0] = StartX - i;
				QUEUE[*nTail][1] = StartY - Step + i;
			}
		}
	}
	return 1;
}

void CProjectView::Get_A_B_R(double xk, double yk, double xl, double yl, double xm, 
							 double ym, double *d_A, double *d_B, double *d_R)
{
	double k_kl, k_lm;
	double d_temp1, d_temp2;
	k_kl = (double)(yk - yl)/(double)(xk - xl);
	k_lm = (double)(ym - yl)/(double)(xm - xl);

	//d_temp1 = (xl + xm)/k_lm - (xk + xl)/k_kl + ym - yk;
	d_temp1 = k_lm * k_kl * (ym - yk) - (xk + xl) * k_lm + (xl + xm) * k_kl;
	(* d_A) = (0.5 / (k_kl-k_lm)) * d_temp1;
	//d_temp1 = xk - xm + k_kl * (yk + yl) - k_lm * (yl + ym);
	d_temp1 = (xk - xm) + k_kl * (yk + yl) - k_lm * (yl + ym);
	(* d_B) = (0.5 / (k_kl-k_lm)) * d_temp1;

	d_temp1 = ((*d_A) - xk) * ((*d_A) - xk);
	d_temp2 = ((*d_B) - yk) * ((*d_B) - yk);
	(*d_R) = sqrt(d_temp1 + d_temp2);

	return;
}

BOOL CProjectView::SearchCount(long Start, long End, int x, int y, int r, 
							   int Counter[], long *pos)
{
	BOOL Result;
	Result = FALSE;
	long count, xyr;
	long mid;
	mid = (Start + End) / 2;
	count = Counter[mid * 4 + 0] * MAXXYR * MAXXYR +
		    Counter[mid * 4 + 1] * MAXXYR +
			Counter[mid * 4 + 2];
	xyr = x * MAXXYR * MAXXYR + y * MAXXYR + r;
	
	if (End == 0)
	{
		(*pos) = 1;
		return FALSE;
	}

	if (count == xyr)
	{
		(*pos) = mid;
		return TRUE;
	}
	else if (Start == End)
	{
		if (count < xyr)
		{
			(*pos) = Start + 1;
			return FALSE;
		}
		else
		{
			(*pos) = Start;
			return FALSE;
		}
	}

	if (count < xyr)
	{
		return SearchCount(mid + 1, End, x, y, r, Counter, pos);
	}
	else
	{
		return SearchCount(Start, mid, x, y, r, Counter, pos);
	}
}

void CProjectView::InsertCount(int x, int y, int r, int Counter[])
{
	long i, nTotal;
	nTotal = Counter[0 * 4 + 3];
	BOOL bResult;
	long pos;

	bResult = SearchCount(1, nTotal, x, y, r, Counter, &pos);
	if (bResult == TRUE)
	{
		Counter[pos * 4 + 3] = Counter[pos * 4 + 3] + 1;
		return;
	}
	else
	{
		InsertIntoCount(x, y, r, pos, Counter);
		return;
	}
/*
	//按照索引从小到大排序
	for (i = 1; i <= nTotal; i ++)
	{
		if (x < Counter[i * 4 + 0])
		{
			InsertIntoCount(x, y, r, i, Counter);
			return;
		}
		else if (x > Counter[i * 4 + 0])
			continue;

		//x == Counter[i][0]情况
		if (y < Counter[i * 4 + 1])
		{
			InsertIntoCount(x, y, r, i, Counter);
			return;
		}
		else if (y > Counter[i * 4 + 1])
			continue;

		//y == Counter[i][1]情况
		if (r < Counter[i * 4 + 2])
		{
			InsertIntoCount(x, y, r, i, Counter);
			return;
		}
		else if (r > Counter[i * 4 + 2])
			continue;
		
		//r == counter[i][2]
		Counter[i * 4 + 3] = Counter[i * 4 + 3] + 1;
		return;
	}

	//说明前面的索引都比现在的小，现在的数值索引是最大的，应该插入在最后
	if (i == nTotal + 1)
	{
		Counter[i * 4 + 0] = x;
		Counter[i * 4 + 1] = y;
		Counter[i * 4 + 2] = r;
		Counter[i * 4 + 3] = 1;
		Counter[0 * 4 + 3] = nTotal + 1;
	}

	return;
*/
}

void CProjectView::InsertIntoCount(int x, int y, int r, long pos, int Counter[])
{
	long i, nTotal;
	nTotal = Counter[0 * 4 + 3];

	if (nTotal >= MAXSIZE - 1)
	{
		AfxMessageBox("稀疏矩阵溢出！");
		return;
	}
	for(i = nTotal + 1; i > pos; i --)
	{
		Counter[i * 4 + 0] = Counter[(i-1) * 4 + 0];
		Counter[i * 4 + 1] = Counter[(i-1) * 4 + 1];
		Counter[i * 4 + 2] = Counter[(i-1) * 4 + 2];
		Counter[i * 4 + 3] = Counter[(i-1) * 4 + 3];
	}

	Counter[i * 4 + 0] = x;
	Counter[i * 4 + 1] = y;
	Counter[i * 4 + 2] = r;
	Counter[i * 4 + 3] = 1;

	Counter[0 * 4 + 3] = Counter[0 * 4 + 3] + 1;
	
	return;
}

void CProjectView::CircleDetect(CProjectDoc * pDoc, int nStep, int nMark, int X_Left, 
								int X_Right, int Y_Top, int Y_Bottom, int R_Small, 
								int *C_X, int *C_Y, double rate)
{

	int x, y, len;
	long i;
	int n_A, n_B, n_R;//得到的圆心坐标和半径
	int qFirst[QUEUELEN][2], nFirstHead, nFirstTail;//第一个队列
	int qSecond[QUEUELEN][2], nSecondHead, nSecondTail;//第二个队列
	int xk,yk,xl,yl,xm,ym;//三点坐标
	int nTemp3, nTemp4, nTotal;
	double d_A, d_B, d_R;//得到的圆心和半径参数
	int *Count;//Hough变换结果计数器所对应的稀疏矩阵
	//int nMax1, nPos1, nMax2, nPos2, nMax3, nPos3,;
	int nMax;
	long nPos;
	//int nTempX, nTempY, nTempR;
	double nTemp1, nTemp2;
	//int *Flag;


	Count = (int *) LocalAlloc(LMEM_FIXED, MAXSIZE * sizeof(int) * 4);
	//for(i = 0; i < pDoc->BmpWidth * pDoc->BmpHeight; i ++)
	//{
	//	Flag[i] = 0;
	//}

	//((CMainFrame *)AfxGetMainWnd())->SetStatus("稀疏矩阵初始化");

//	for(x = 0; i < 10000; i ++)
//		for(y = 0; y < 3; y ++)
//			Count[x][y] = 0;
	Count[0 * 4 + 0] = 120;
	Count[0 * 4 + 1] = 90;
	Count[0 * 4 + 2] = 60;
	Count[0 * 4 + 3] = 0;
	
	//Count[0][0] = 120;
	//Count[0][1] = 90;  
	//Count[0][2] = 25;
	//Count[0][3] = 0;

	nTemp3 = 0;
	nTotal = 0;
	if (pDoc->BitCount != 8)
	{
		AfxMessageBox("本系统只处理256色的黑白图片！");
		return;
	}
	//1.进行变形Hough变换
	//   1)寻找相距为8的三个点
	//   2)变换
	//寻找相距为8的三个点
	((CMainFrame *)AfxGetMainWnd())->SetStatus("进行Hough变换");
	BeginWaitCursor();

	for(y = 0; y < pDoc->BmpHeight; y ++)
	{
		for(x = 0; x < pDoc->BmpWidth; x ++)
		{
			//如果该点为灰度值为0(黑色)，则continue
/*
			if ((x / 100) > 0) 
				len = 3;
			else if (x / 10 > 0)
				len = 2;
			else
				len = 1;
			((CMainFrame *)AfxGetMainWnd())->SetStatusX(_ecvt(x,len,&nTemp3,&nTemp4));

			if ((y / 100) > 0) 
				len = 3;
			else if (y / 10 > 0)
				len = 2;
			else
				len = 1;

			((CMainFrame *)AfxGetMainWnd())->SetStatusY(_ecvt(y,len,&nTemp3,&nTemp4));
*/
			if (pDoc->pImage[y * pDoc->nWidth + x] != 0)
				continue;
			//寻找(x,y)相距为8的点，进队qFirst
			nFirstHead = -1;
			nFirstTail = -1;
			//((CMainFrame *)AfxGetMainWnd())->SetStatus("寻找距离为8的邻点");

			SearchPoint(x, y, qFirst, &nFirstHead, &nFirstTail, pDoc->pImage, 
				pDoc->BmpWidth, pDoc->BmpHeight, nStep, pDoc->nWidth);
			nTemp3 += nFirstTail-nFirstHead;
			//在qFirst非空的情况下，出队 (x1, y1)
			while((nFirstTail - nFirstHead) > 0)
			{
				//AfxMessageBox(_ecvt(nFirstTail-nFirstHead,10,&nTemp1,&nTemp2));
				nFirstHead ++;
				xl = qFirst[nFirstHead][0];
				yl = qFirst[nFirstHead][1];
				nSecondHead = -1;
				nSecondTail = -1;
				//((CMainFrame *)AfxGetMainWnd())->SetStatus("寻找第三个距离为8的邻点");
				//寻找(x1,y1)的相距为8的点，进队qSecond

				SearchPoint(xl, yl, qSecond, &nSecondHead, &nSecondTail, pDoc->pImage, 
					pDoc->BmpWidth, pDoc->BmpHeight, nStep, pDoc->nWidth);
				//在qSecond非空的情况下，出队(x2, y2)
				while((nSecondTail - nSecondHead) > 0)
				{
					
					nSecondHead ++;
					xm = qSecond[nSecondHead][0];
					ym = qSecond[nSecondHead][1];
					xk = x;
					yk = y;
					if ((abs(xk - xm) + abs(yk - ym)) < nStep * 1.5)
						continue;
					if (((xl - xk) == (xl - xm) * (-1)) && ((yl - yk) == (yl - ym) * (-1)))
						continue;
					//进行变换
					Get_A_B_R(xk*rate, yk*rate, xl*rate, yl*rate, xm*rate, ym*rate, 
						&d_A, &d_B, &d_R);
					if (d_A > 120 || d_B > 90 || d_R > 60)
						continue;
					if (d_A < 0 || d_B < 0)
						continue;
					//if (d_A < 50 || d_B > 60)
					if ((d_A < X_Left) || (d_B > Y_Top) || (d_R < R_Small))
						continue;
					//if ((d_A > X_Right) || (d_A < Y_Bottom))
						//continue;
					
					//if (d_R < 15)
					//if (d_R < 15)
					//	continue;

					//n_A = (int)(d_A * 5 + 0.5);
					//n_B = (int)(d_B * 5 + 0.5);
					//n_R = (int)(d_R * 5 + 0.5);
					n_A = (int)(d_A + 0.5);
					n_B = (int)(d_B + 0.5);
					n_R = (int)(d_R + 0.5);
					//计数
					InsertCount(n_A, n_B, n_R, Count);
					nTotal ++; 
				}
			}
		}
	}
	//2.取得最大值

	((CMainFrame *)AfxGetMainWnd())->SetStatus("寻找变换空间中的最大值");
	nMax = 0;
	nPos = 0;
	nTemp3 = 0;
	for(i = 1; i <= Count[0 * 4 + 3]; i++)
	{
		if (Count[i * 4 + 3] > nMax)
		{
			nMax = Count[i * 4 + 3];
			nPos = i;
		}
		nTemp3 ++;
	}

	/*
	for(i = 1; i <= Count[0][3]; i++)
	{
		if (Count[i][3] > nMax1)
		{
			nMax3 = nMax2;
			nPos3 = nPos2;
			nMax2 = nMax1;
			nPos2 = nPos1;
			nMax1 = Count[i][3];
			nPos1 = i;
		}
		else if (Count[i][3] > nMax2)
		{
			nMax3 = nMax2;
			nPos3 = nPos2;
			nMax2 = Count[i][3];
			nPos2 = i;
		}
		else if (Count[i][3] > nMax3)
		{
			nMax3 = Count[i][3];
			nPos3 = i;
		}
		nTemp3 ++;
	}

	nMax = nMax1 + nMax2 + nMax3;
*/
	//3.将原图中圆以外的部分全部去除
		
	((CMainFrame *)AfxGetMainWnd())->SetStatus("检测到圆，更新图像");

	//nTempX = (Count[nPos1][0] + Count[nPos2][0] + Count[nPos3][0])/3;
	//nTempY = (Count[nPos1][1] + Count[nPos2][1] + Count[nPos3][1])/3;
	//nTempR = (Count[nPos1][2] + Count[nPos2][2] + Count[nPos3][2])/3;


	for(y = 0; y < pDoc->BmpHeight; y++)
		for (x = 0; x < pDoc->BmpWidth; x++)
		{
			
			nTemp1 = (x - (double)Count[nPos * 4 + 0] / rate) * 
				(x - (double)Count[nPos * 4 + 0] / rate);
			nTemp2 = (y - (double)Count[nPos * 4 + 1] / rate) * 
				(y - (double)Count[nPos * 4 + 1] / rate);
			//if (sqrt(nTemp1 + nTemp2) > Count[nPos][2] * 5)
			if (nMark == 1)
			{
				if (sqrt(nTemp1 + nTemp2) > Count[nPos * 4 + 2] / rate)
				{
					if (pDoc->pImage[y * pDoc->nWidth + x] == 0)
						pDoc->pImage[y * pDoc->nWidth + x] = 255;
				//pDoc->pImage[y * pDoc->nWidth + x] = 0;
				}
			}
			else if (nMark == 0)
			{
				if (sqrt(nTemp1 + nTemp2) < Count[nPos * 4 + 2] / rate)
				{
					if (pDoc->pImage[y * pDoc->nWidth + x] == 0)
						pDoc->pImage[y * pDoc->nWidth + x] = 128;
				//pDoc->pImage[y * pDoc->nWidth + x] = 0;
				}

			}
		/*
			nTemp1 = (x - nTempX * 5) * (x - nTempX * 5);
			nTemp2 = (y - nTempY * 5) * (y - nTempY * 5);
			//if (sqrt(nTemp1 + nTemp2) > Count[nPos][2] * 5)
			if (sqrt(nTemp1 + nTemp2) < nTempR * 5)
			{
				//pDoc->pImage[y * pDoc->nWidth + x] = 255;
				pDoc->pImage[y * pDoc->nWidth + x] = 0;
			}
*/
		}
	(*C_X) = (int)(Count[nPos * 4 + 0] / rate);
	(*C_Y) = (int)(Count[nPos * 4 + 1] / rate);

	nTotal ++;
	EndWaitCursor();
	//CString aaa;
	//aaa = _ecvt(nTemp3,10,&nTemp1,&nTemp2);
	//aaa += _ecvt(nMax,10,&nTemp1,&nTemp2);
	//AfxMessageBox(aaa);
	LocalFree(Count);
}

void CProjectView::OnWygStep() 
{
	// TODO: Add your command handler code here
	CProjectDoc * pProjectDoc = GetDocument();
	ASSERT_VALID(pProjectDoc);
	// TODO: Add your command handler code here!
	//AfxMessageBox("Hist");
	//CreateNewFrame(pDoc);
	//CMultiDocTemplate *pTemplate=pDocTemplate.GetHead();
	//LPCTSTR lpszFileName;
	//AfxgetApp
	
	if (pProjectDoc->BitCount != 8)
	{
		AfxMessageBox("本系统只处理256色的黑白图片！");
		return;
	}

	//AfxMessageBox("第一步：对图像进行Prewitt变换");
	((CMainFrame *)AfxGetMainWnd())->SetStatus("第一步：对图像进行Prewitt变换");

	POSITION Pos;
	CMultiDocTemplate* pDocTemplate;
	CChildFrame * pFrame;
	CProjectDoc * pDoc;

	Pos = AfxGetApp()->m_pDocManager->GetFirstDocTemplatePosition();
	pDocTemplate = (CMultiDocTemplate*)AfxGetApp()->m_pDocManager->GetNextDocTemplate(Pos);

	pDoc = (CProjectDoc *)pDocTemplate->CreateNewDocument();
	pFrame = (CChildFrame *)pDocTemplate->CreateNewFrame(pDoc, NULL);

	pDoc->SetDocument(pProjectDoc);
	
	EdgePrewitt(pDoc);

	//pHistDoc->OnNewDocument();
	pDocTemplate->InitialUpdateFrame(pFrame,pDoc,TRUE);	
}

void CProjectView::OnWygStep2() 
{
	// TODO: Add your command handler code here
	CProjectDoc * pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	//AfxMessageBox("第二步：将图像颜色取反");
	((CMainFrame *)AfxGetMainWnd())->SetStatus("第二步：将图像颜色取反");

	int i, j;
	for (i = 0; i < pDoc->BmpHeight; i ++)
	{
		for(j = 0; j < pDoc->BmpWidth; j ++)
		{
			pDoc->pImage[i * pDoc->nWidth + j] = 255 - pDoc->pImage[i * pDoc->nWidth + j];
		}
	}
	//Invalidate(TRUE);

	//AfxMessageBox("第三步：将图像进行全局阈值分割");
	((CMainFrame *)AfxGetMainWnd())->SetStatus("第三步：将图像进行全局阈值分割");

	long count;
	count = 0;
	for (i = 0; i < pDoc->BmpHeight; i ++)
	{
		for(j = 0; j < pDoc->BmpWidth; j ++)
		{
			//test1,全局阈值，198
			if (pDoc->pImage[i * pDoc->nWidth + j] > 198)
				pDoc->pImage[i * pDoc->nWidth + j] = 255;
			else 
			{
				pDoc->pImage[i * pDoc->nWidth + j] = 0;
				count ++;
			}
		}
	}
	//Invalidate(TRUE);

	//AfxMessageBox("第四步：用改进的点Hough变换对图像进行圆检测");
	((CMainFrame *)AfxGetMainWnd())->SetStatus("第四步：用改进的点Hough变换对图像进行圆检测");

	int x, y, x1, y1, x2, y2, x3, y3;

	//CircleDetect(pDoc, STEP, 1, 40, 60, 15, &x, &y, 0.2);
	CircleDetect(pDoc, STEP, 1, 40, 60, 60, 40, 15, &x, &y, 0.2);
	//AfxMessageBox("第五步：检测指针圆盘");
	//CircleDetect(pDoc, SMALLSTEP, 0, 50, 60, 3, &x1, &y1, 0.2);
	//CircleDetect(pDoc, SMALLSTEP, 0, 50, 60, 3, &x2, &y2, 0.2);
	//CircleDetect(pDoc, SMALLSTEP, 0, 50, 60, 3, &x3, &y3, 0.2);
	CircleDetect(pDoc, SMALLSTEP, 0, 40, 60, 60, 40, 3, &x1, &y1, 0.2);
	CircleDetect(pDoc, SMALLSTEP, 0, 40, 60, 60, 40, 3, &x2, &y2, 0.2);
	CircleDetect(pDoc, SMALLSTEP, 0, 40, 60, 60, 40, 3, &x3, &y3, 0.2);

}


void CProjectView::OnAddTest() 
{
	// TODO: Add your command handler code here
	CPen greenPen(PS_SOLID, 1, RGB(0,255,0));
	CPen redPen(PS_SOLID, 1, RGB(255,0,0));

	CClientDC pDC(this);
	COLORREF red = RGB(255, 0, 0);
	CProjectDoc * pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	
	//三个指针
	pDC.SelectObject(redPen);
	pDC.MoveTo(x1, pDoc->BmpHeight -1 -y1);
	pDC.LineTo(x1 + (int)(LEN * cos(nAngle1 * 2 * pi / 360)),
		 pDoc->BmpHeight -1- y1 - (int)(LEN * sin(nAngle1 * 2 * pi / 360)));
	pDC.MoveTo(x2, pDoc->BmpHeight - y2);
	pDC.LineTo(x2 + (int)(LEN * cos(nAngle2 * 2 * pi / 360)),
		 pDoc->BmpHeight - y2 -1 - (int)(LEN * sin(nAngle2 * 2 * pi / 360)));
	pDC.MoveTo(x3, pDoc->BmpHeight - y3);
	pDC.LineTo(x3 + (int)(LEN * cos(nAngle3 * 2 * pi / 360)),
		 pDoc->BmpHeight - y3 - 1- (int)(LEN * sin(nAngle3 * 2 * pi / 360)));

	//三个圆心
	pDC.SelectObject(greenPen);
	pDC.MoveTo(x1, pDoc->BmpHeight -1- y1);
	pDC.LineTo(x2, pDoc->BmpHeight -1- y2);
	pDC.MoveTo(x2, pDoc->BmpHeight -1- y2);
	pDC.LineTo(x3, pDoc->BmpHeight -1- y3);
	pDC.MoveTo(x3, pDoc->BmpHeight -1- y3);
	pDC.LineTo(x1, pDoc->BmpHeight -1- y1);


	//pDC.MoveTo(100, 100);
	//pDC.LineTo(300, 300);

	pDC.SetPixel(x, pDoc->BmpHeight - 1- y, red);
/*
	int i ;
	for(i = 0; i < pDoc->nWidth * pDoc->BmpHeight ; i ++)
	{
		pDoc->pImage[i] = pDoc->pImageBak[i];
	}

	Invalidate(TRUE);
*/
}

void CProjectView::OnAddFinger() 
{
	// TODO: Add your command handler code here
	CProjectDoc * pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	((CMainFrame *)AfxGetMainWnd())->SetStatus("检测指针偏转");

	// 检测X1, Y1
	FingerDetectNew(x1, y1, pDoc, &fx1, &fy1, &nAngle1);
	// 检测X2, Y2
	FingerDetectNew(x2, y2, pDoc, &fx2, &fy2, &nAngle2);
	// 检测X3, Y3
	FingerDetectNew(x3, y3, pDoc, &fx3, &fy3, &nAngle3);
	((CMainFrame *)AfxGetMainWnd())->SetStatus("指针偏转检测成功");
	AfxMessageBox("指针检测完毕！");
}

void CProjectView::FingerDetectNew(int x, int y, CProjectDoc * pDoc, 
								   int *fx, int *fy, int *Angle)
{
	int nLen;
	int i, nX, nY, nR;
	int nCount[360], nMin, nPos;

	nLen = LEN;
	nMin = LEN * 255;

	for (i = 0; i < 360; i ++)
	{
		nCount[i] = 0;
		nX = x;
		nY = y;
		for(nR = 0; nR < nLen; nR ++)
		{
			nX = x + (int)(nR * cos(i * 2 * pi / 360));
			nY = y + (int)(nR * sin(i * 2 * pi / 360));
			nCount[i] += pDoc->pImageBak[nY * pDoc->nWidth + nX];
			
			//nCount[i] += pDoc->pImageBak[(nY+1) * pDoc->nWidth + nX];
			//nCount[i] += pDoc->pImageBak[(nY-1) * pDoc->nWidth + nX];

		}
		if (nCount[i] < nMin)
		{
			nMin = nCount[i];
			nPos = i;
		}
	}

	(*fx) = x + (int)(nLen * cos(nPos * pi * 2 / 360));
	(*fy) = y + (int)(nLen * sin(nPos * pi * 2 / 360));
	(*Angle) = nPos;
	//AfxMessageBox(""");
}

void CProjectView::FingerDetect(int x, int y, CProjectDoc * pDoc, int *fx, int *fy)
{
	//int i, Step;
	int xStart, yStart, nTempx, nTempy;
	//int mTempx, mTempy, flag;
	//以x,y为中心往外面找点，一直找到最近的一个为止StartX, StartY
	FindStartPoint(x, y, &xStart, &yStart, pDoc);
	nTempx = xStart;
	nTempy = yStart;
	if (xStart - x > 0) 
	{
		//往上左搜
		while((pDoc->pImage[(nTempy + 1) * pDoc->nWidth + nTempx - 1] == 128) ||
			  (pDoc->pImage[(nTempy + 1) * pDoc->nWidth + nTempx] == 128))
		{
			if (pDoc->pImage[(nTempy + 1) * pDoc->nWidth + nTempx - 1] == 128)
			{
				nTempy = nTempy + 1;
				nTempx = nTempx - 1;
			}
			else if (pDoc->pImage[(nTempy + 1) * pDoc->nWidth + nTempx] == 128)
			{
				nTempy = nTempy + 1;
				nTempx = nTempx;
			}
		}
		//往下右
	}

	AfxMessageBox("ok");
	//以此点为起点进行跟踪，按照两个不同的方向进行跟踪，一个顺时针，一个逆时针

	//	跟踪结束条件为：顺时针的不能往前往右算结束；逆时针为不能往前往左算结束

	//比较两个跟踪的最终结果，取离圆心远的那个点

	return;
}

void CProjectView::FindStartPoint(int x, int y, int * xStart, int * yStart, 
								  CProjectDoc * pDoc)
{
	int i, Step, flag;

	Step = 1;
	while (1)
	{
		flag = 0;
		for(i = 0; i < Step; i++)
		{
			//左上
			if (pDoc->pImage[(y + i) * pDoc->nWidth + x - Step + i] == 128)
			{
				(*xStart) = x - Step + i;
				(*yStart) = y + i;
				flag = 1;
				break;
			}
			
		    //右上
			if (pDoc->pImage[(y + Step - i) * pDoc->nWidth + x + i] == 128)
			{
				(*xStart) = x + i;
				(*yStart) = y + Step - i;
				flag = 1;
				break;
			}

			//右下
			if (pDoc->pImage[(y - i) * pDoc->nWidth + x + Step - i] == 128)
			{
				(*xStart) = x + Step - i;
				(*yStart) = y - i;
				flag = 1;
				break;
			}

			if (pDoc->pImage[(y - Step + i) * pDoc->nWidth + x - i] == 128)
			{
				(*xStart) = x - i;
				(*yStart) = y - Step + i;
				flag = 1;
				break;
			}
		}
		if (flag == 1)
			break;
		Step ++;
	}
}


void CProjectView::OnAddEnd() 
{
	// TODO: Add your command handler code here

	//现在已知x1,y1, x2,y2, x3,y3, fx1,fy1, fx2,fy2, fx3, fy3
	//先确定圆心三角形，对于三个点进行确定 0.01 0.001, 0.0001三个指针
	double d_l12, d_l13, d_l23;
	double nAA1, nAA2, nAA3, nTemp;
	BOOL IsBelow;
	double k;
	int longest, n;

	//1.确定长边
	longest = 0;

	d_l12 = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
	d_l13 = sqrt((x1-x3)*(x1-x3) + (y1-y3)*(y1-y3));
	d_l23 = sqrt((x3-x2)*(x3-x2) + (y3-y2)*(y3-y2));

	if (d_l12 > d_l13)
	{
		if (d_l12 > d_l23)
		{
			longest = 12;
		}
		else
		{
			longest = 23;
		}
	}
	else
	{
		if (d_l13 > d_l23)
		{
			longest = 13;
		}
		else
		{
			longest = 23;
		}
	}

	//2.确定第三点在长边的上边还是下边
	//3.确定三点位置 0.01-> 1; 0.001->2; 0.0001->3;
	switch(longest)
	{
	case 13:
		IsBelow = BelowUpon(x1, y1, x3, y3, x2, y2, nAngle1, nAngle3, nAngle2);
		break;
	case 23:
		IsBelow = BelowUpon(x2, y2, x3, y3, x1, y1, nAngle2, nAngle3, nAngle1);
		break;
	case 12:
		IsBelow = BelowUpon(x1, y1, x2, y2, x3, y3, nAngle1, nAngle2, nAngle3);
		break;
	}
	//输入0指针的偏转角度,以点1为中心，边13顺时针旋转到0指针方向的角度是固定的
	//将这个已知角度转化为跟X轴正方向的转角
	//计算三根指针的偏转，得到最后读数	
	k = (double)(y1-y3)/(double)(x1-x3);

	if (atan(k) < 0)
		nTemp = (-1) * atan(k) * 360 / (2 * pi);
	else
		nTemp = 180 - atan(k) * 360 / (2 * pi);
	nAA1 = (-1) * nAngle1 - THITA - nTemp;
	while (nAA1 < 0)
	{
		nAA1 += 360;
	}
	nAA2 = (-1) * nAngle2 - THITA - nTemp;
	while (nAA2 < 0)
	{
		nAA2 += 360;
	}
	nAA3 = (-1) * nAngle3 - THITA - nTemp;
	while (nAA3 < 0)
	{
		nAA3 += 360;
	}

	CResultDlg dlgResult;
	//dlgBaseInfo.SetInfo(pDoc);
	CString sTemp;
	sTemp = LongToString(x1);
	dlgResult.m_X1 = sTemp;
	sTemp = LongToString(y1);
	dlgResult.m_Y1 = sTemp;

	sTemp = LongToString(x2);
	dlgResult.m_X2 = sTemp;
	sTemp = LongToString(y2);
	dlgResult.m_Y2 = sTemp;

	sTemp = LongToString(x3);
	dlgResult.m_X3 = sTemp;
	sTemp = LongToString(y3);
	dlgResult.m_Y3 = sTemp;

	sTemp = LongToString(x);
	dlgResult.m_X = sTemp;
	sTemp = LongToString(y);
	dlgResult.m_Y = sTemp;

	sTemp = LongToString(nAngle1);
	dlgResult.m_A1 = sTemp;

	sTemp = LongToString(nAngle2);
	dlgResult.m_A2 = sTemp;

	sTemp = LongToString(nAngle3);
	dlgResult.m_A3 = sTemp;


	n = (int)(nAA1 / 36);
	sTemp = LongToString(n);
	dlgResult.m_R1 = sTemp;

	n = (int)(nAA2 / 36);
	sTemp = LongToString(n);
	dlgResult.m_R2 = sTemp;

	n = (int)(nAA3 / 36);
	sTemp = LongToString(n);
	dlgResult.m_R3 = sTemp;

	((CMainFrame *)AfxGetMainWnd())->SetStatus("当前显示最后结果");
	dlgResult.DoModal();
	((CMainFrame *)AfxGetMainWnd())->SetStatus("就绪");


}

CString CProjectView::LongToString(long data)
{
	CString str;
	int dec,sign;
	str = _ecvt(data,10,&dec,&sign);
	//AfxMessageBox(str.Left(dec));
	if (data != 0)
		return str.Left(dec);
	else
		return "0";
}

BOOL CProjectView::BelowUpon(int LineX1,int LineY1, int LineX2, int LineY2, 
							 int PointX, int PointY, int nA1, int nA2, int nA3)
{
	BOOL result;
	result = FALSE;
	double k;

	if (LineX1 == LineX2)
	{
		//point在左边
		if (PointX < LineX1)
		{
			if (LineY1 > LineY2)
			{
				x1 = LineX2;
				y1 = LineY2;
				nAngle1 = nA2;
				x2 = PointX;
				y2 = PointY;
				nAngle2 = nA3;
				x3 = LineX1;
				y3 = LineY1;
				nAngle3 = nA1;
				return TRUE;
			}
			else
			{
				x1 = LineX1;
				y1 = LineY1;
				nAngle1 = nA1;
				x2 = PointX;
				y2 = PointY;
				nAngle2 = nA3;
				x3 = LineX2;
				y3 = LineY2;
				nAngle3 = nA2;
				return TRUE;
			}
		}
		else  // 在右边
		{
			if (LineY1 > LineY2)
			{
				x1 = LineX1;
				y1 = LineY1;
				nAngle1 = nA1;
				x2 = PointX;
				y2 = PointY;
				nAngle2 = nA3;
				x3 = LineX2;
				y3 = LineY2;
				nAngle3 = nA2;
				return TRUE;
			}
			else
			{
				x1 = LineX2;
				y1 = LineY2;
				nAngle1 = nA2;
				x2 = PointX;
				y2 = PointY;
				nAngle2 = nA3;
				x3 = LineX1;
				y3 = LineY1;
				nAngle3 = nA1;
				return TRUE;
			}


		}
	}

	if (LineY1 == LineY2)
	{
		//point在上边
		if (PointY > LineY1)
		{
			if (LineX1 > LineX2)
			{
				x1 = LineX2;
				y1 = LineY2;
				nAngle1 = nA2;
				x2 = PointX;
				y2 = PointY;
				nAngle2 = nA3;
				x3 = LineX1;
				y3 = LineY1;
				nAngle3 = nA1;
				return TRUE;
			}
			else
			{
				x1 = LineX1;
				y1 = LineY1;
				nAngle1 = nA1;
				x2 = PointX;
				y2 = PointY;
				nAngle2 = nA3;
				x3 = LineX2;
				y3 = LineY2;
				nAngle3 = nA2;
				return TRUE;
			}
		}
		else  // 在下边
		{
			if (LineX1 > LineX2)
			{
				x1 = LineX1;
				y1 = LineY1;
				nAngle1 = nA1;
				x2 = PointX;
				y2 = PointY;
				nAngle2 = nA3;
				x3 = LineX2;
				y3 = LineY2;
				nAngle3 = nA2;
				return TRUE;
			}
			else
			{
				x1 = LineX2;
				y1 = LineY2;
				nAngle1 = nA2;
				x2 = PointX;
				y2 = PointY;
				nAngle2 = nA3;
				x3 = LineX1;
				y3 = LineY1;
				nAngle3 = nA1;
				return TRUE;
			}
		}
	}

	k = (double)(LineY1 - LineY2) / (double)(LineX1 - LineX2);
	if ((double)PointY > k * (PointX - LineX1) + LineY1)
	{
		//在上部
			//在右边
		if (LineX1 > LineX2)
		{
			x1 = LineX2;
			y1 = LineY2;
			nAngle1 = nA2;
			x2 = PointX;
			y2 = PointY;
			nAngle2 = nA3;
			x3 = LineX1;
			y3 = LineY1;
			nAngle3 = nA1;
			return TRUE;
		}
		else
		{
			x1 = LineX1;
			y1 = LineY1;
			nAngle1 = nA1;
			x2 = PointX;
			y2 = PointY;
			nAngle2 = nA3;
			x3 = LineX2;
			y3 = LineY2;
			nAngle3 = nA2;
			return TRUE;
		}
	}
	else
	{
		//在下部
		if (LineX1 > LineX2)
		{
			x1 = LineX1;
			y1 = LineY1;
			nAngle1 = nA1;
			x2 = PointX;
			y2 = PointY;
			nAngle2 = nA3;
			x3 = LineX2;
			y3 = LineY2;
			nAngle3 = nA2;
			return TRUE;
		}
		else
		{
			x1 = LineX2;
			y1 = LineY2;
			nAngle1 = nA2;
			x2 = PointX;
			y2 = PointY;
			nAngle2 = nA3;
			x3 = LineX1;
			y3 = LineY1;
			nAngle3 = nA1;
			return TRUE;
		}	
	}
	return TRUE;
}

void CProjectView::OnAddPrewitt() 
{
	// TODO: Add your command handler code here
	CProjectDoc * pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: Add your command handler code here!
	//AfxMessageBox("Hist");
	//CreateNewFrame(pDoc);
	//CMultiDocTemplate *pTemplate=pDocTemplate.GetHead();
	//LPCTSTR lpszFileName;
	//AfxgetApp
	
	if (pDoc->BitCount != 8)
	{
		AfxMessageBox("本系统只处理256色的黑白图片！");
		return;
	}

	POSITION Pos;
	CMultiDocTemplate* pDocTemplate;
	CChildFrame * pFrame;
	CProjectDoc * pProjectDoc;

	Pos = AfxGetApp()->m_pDocManager->GetFirstDocTemplatePosition();
	pDocTemplate = (CMultiDocTemplate*)AfxGetApp()->m_pDocManager->GetNextDocTemplate(Pos);

	pProjectDoc = (CProjectDoc *)pDocTemplate->CreateNewDocument();
	pFrame = (CChildFrame *)pDocTemplate->CreateNewFrame(pProjectDoc, NULL);

	pProjectDoc->SetDocument(pDoc);

	EdgePrewitt(pProjectDoc);

	//pHistDoc->OnNewDocument();
	pDocTemplate->InitialUpdateFrame(pFrame,pProjectDoc,TRUE);	
	
}

void CProjectView::OnAddTotal() 
{
	// TODO: Add your command handler code here
	CProjectDoc * pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	//AfxMessageBox("第二步：将图像颜色取反");
	((CMainFrame *)AfxGetMainWnd())->SetStatus("第二步：将图像颜色取反");

	int i, j;
	for (i = 0; i < pDoc->BmpHeight; i ++)
	{
		for(j = 0; j < pDoc->BmpWidth; j ++)
		{
			pDoc->pImage[i * pDoc->nWidth + j] = 255 - pDoc->pImage[i * pDoc->nWidth + j];
		}
	}
	//Invalidate(TRUE);

	//AfxMessageBox("第三步：将图像进行全局阈值分割");
	((CMainFrame *)AfxGetMainWnd())->SetStatus("第三步：将图像进行全局阈值分割");

	long count;
	count = 0;
	for (i = 0; i < pDoc->BmpHeight; i ++)
	{
		for(j = 0; j < pDoc->BmpWidth; j ++)
		{
			//test1,全局阈值，198
			if (pDoc->pImage[i * pDoc->nWidth + j] > 198)
				pDoc->pImage[i * pDoc->nWidth + j] = 255;
			else 
			{
				pDoc->pImage[i * pDoc->nWidth + j] = 0;
				count ++;
			}
		}
	}
	//Invalidate(TRUE);

	//AfxMessageBox("第四步：用改进的点Hough变换对图像进行圆检测");
	((CMainFrame *)AfxGetMainWnd())->SetStatus("第四步：用改进的点Hough变换对图像进行圆检测");

	//int x, y, x1, y1, x2, y2, x3, y3;

	//CircleDetect(pDoc, STEP, 1, XLEFT, XRIGHT, YTOP, YBOTTOM, 15, &x, &y, 0.2);
	CircleDetect(pDoc, STEP, 1, XLEFT, XRIGHT, YTOP, YBOTTOM, BIGD, &x, &y, 0.2);

	//AfxMessageBox("第五步：检测指针圆盘");
	CircleDetect(pDoc, SMALLSTEP, 0, XLEFT, XRIGHT, YTOP, YBOTTOM, SMALLD, &x1, &y1, 0.2);
	CircleDetect(pDoc, SMALLSTEP, 0, XLEFT, XRIGHT, YTOP, YBOTTOM, SMALLD, &x2, &y2, 0.2);
	CircleDetect(pDoc, SMALLSTEP, 0, XLEFT, XRIGHT, YTOP, YBOTTOM, SMALLD, &x3, &y3, 0.2);

	//检测指针偏转
	((CMainFrame *)AfxGetMainWnd())->SetStatus("检测指针偏转");
	// 检测X1, Y1
	FingerDetectNew(x1, y1, pDoc, &fx1, &fy1, &nAngle1);
	// 检测X2, Y2
	FingerDetectNew(x2, y2, pDoc, &fx2, &fy2, &nAngle2);
	// 检测X3, Y3
	FingerDetectNew(x3, y3, pDoc, &fx3, &fy3, &nAngle3);
	((CMainFrame *)AfxGetMainWnd())->SetStatus("指针偏转检测成功");
	//AfxMessageBox("指针检测完毕！");

	//最后输出结果
	//现在已知x1,y1, x2,y2, x3,y3, fx1,fy1, fx2,fy2, fx3, fy3
	//先确定圆心三角形，对于三个点进行确定 0.01 0.001, 0.0001三个指针
	((CMainFrame *)AfxGetMainWnd())->SetStatus("正在计算最后结果");
	double d_l12, d_l13, d_l23;
	double nAA1, nAA2, nAA3;
	BOOL IsBelow;
	double k;
	int longest, n;

	//1.确定长边
	longest = 0;

	d_l12 = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
	d_l13 = sqrt((x1-x3)*(x1-x3) + (y1-y3)*(y1-y3));
	d_l23 = sqrt((x3-x2)*(x3-x2) + (y3-y2)*(y3-y2));

	if (d_l12 > d_l13)
	{
		if (d_l12 > d_l23)
		{
			longest = 12;
		}
		else
		{
			longest = 23;
		}
	}
	else
	{
		if (d_l13 > d_l23)
		{
			longest = 13;
		}
		else
		{
			longest = 23;
		}
	}

	//2.确定第三点在长边的上边还是下边
	//3.确定三点位置 0.01-> 1; 0.001->2; 0.0001->3;
	switch(longest)
	{
	case 13:
		IsBelow = BelowUpon(x1, y1, x3, y3, x2, y2, nAngle1, nAngle3, nAngle2);
		break;
	case 23:
		IsBelow = BelowUpon(x2, y2, x3, y3, x1, y1, nAngle2, nAngle3, nAngle1);
		break;
	case 12:
		IsBelow = BelowUpon(x1, y1, x2, y2, x3, y3, nAngle1, nAngle2, nAngle3);
		break;
	}
	//输入0指针的偏转角度,以点1为中心，边13顺时针旋转到0指针方向的角度是固定的
	//将这个已知角度转化为跟X轴正方向的转角
	//计算三根指针的偏转，得到最后读数	
	double nTemp;
	k = (double)(y1-y3)/(double)(x1-x3);

	if (atan(k) < 0)
		nTemp = (-1) * atan(k) * 360 / (2 * pi);
	else
		nTemp = 180 - atan(k) * 360 / (2 * pi);
	nAA1 = (-1) * nAngle1 - THITA - nTemp;

	while (nAA1 < 0)
	{
		nAA1 += 360;
	}
	nAA2 = (-1) * nAngle2 - THITA - nTemp;
	while (nAA2 < 0)
	{
		nAA2 += 360;
	}
	nAA3 = (-1) * nAngle3 - THITA - nTemp;
	while (nAA3 < 0)
	{
		nAA3 += 360;
	}

	CResultDlg dlgResult;
	//dlgBaseInfo.SetInfo(pDoc);
	CString sTemp;
	sTemp = LongToString(x1);
	dlgResult.m_X1 = sTemp;
	sTemp = LongToString(y1);
	dlgResult.m_Y1 = sTemp;

	sTemp = LongToString(x2);
	dlgResult.m_X2 = sTemp;
	sTemp = LongToString(y2);
	dlgResult.m_Y2 = sTemp;

	sTemp = LongToString(x3);
	dlgResult.m_X3 = sTemp;
	sTemp = LongToString(y3);
	dlgResult.m_Y3 = sTemp;

	sTemp = LongToString(x);
	dlgResult.m_X = sTemp;
	sTemp = LongToString(y);
	dlgResult.m_Y = sTemp;

	sTemp = LongToString(nAngle1);
	dlgResult.m_A1 = sTemp;

	sTemp = LongToString(nAngle2);
	dlgResult.m_A2 = sTemp;

	sTemp = LongToString(nAngle3);
	dlgResult.m_A3 = sTemp;


	n = (int)(nAA1 / 36);
	sTemp = LongToString(n);
	dlgResult.m_R1 = sTemp;

	n = (int)(nAA2 / 36);
	sTemp = LongToString(n);
	dlgResult.m_R2 = sTemp;

	n = (int)(nAA3 / 36);
	sTemp = LongToString(n);
	dlgResult.m_R3 = sTemp;

	((CMainFrame *)AfxGetMainWnd())->SetStatus("当前显示最后结果");
	dlgResult.DoModal();
	Invalidate(TRUE);

	((CMainFrame *)AfxGetMainWnd())->SetStatus("就绪");
}
