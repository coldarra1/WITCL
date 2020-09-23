// HistGramView.cpp : implementation file
//

#include "stdafx.h"
#include "Project.h"
#include "HistGramDoc.h"
#include "HistGramView.h"
#include "GlobalAPI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHistGramView

IMPLEMENT_DYNCREATE(CHistGramView, CScrollView)

CHistGramView::CHistGramView()
{
}

CHistGramView::~CHistGramView()
{
}

BEGIN_MESSAGE_MAP(CHistGramView, CScrollView)
	//{{AFX_MSG_MAP(CHistGramView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHistGramView drawing

void CHistGramView::OnDraw(CDC* pDC)
{
	CHistGramDoc * pDoc = (CHistGramDoc *)GetDocument();
	// TODO: add draw code here
	DrawHist(pDoc->BitCount, pDoc, pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CHistGramView diagnostics

#ifdef _DEBUG
void CHistGramView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CHistGramView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
CHistGramDoc* CHistGramView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHistGramDoc)));
	return (CHistGramDoc*)m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHistGramView message handlers
void CHistGramView::DrawHistSon(CRect rect, CPen *pen, CFont *font, CDC *pDC,
								long *Hist, int Start)
{

	long tempMax;
	int nHeight;
	double rate;
	int i;

	pDC->SelectObject(pen);
	nHeight = rect.bottom - rect.top;
	tempMax = GetMax(Hist, 256, Start);
	pDC->MoveTo(rect.left + 40, rect.top + 10);
	pDC->LineTo(rect.left + 40, rect.bottom - 5);
	pDC->MoveTo(rect.left + 40, rect.bottom - 5);
	pDC->LineTo(rect.right, rect.bottom - 5);
	pDC->SelectObject(&font);
	pDC->TextOut(550, rect.bottom , "255");
	pDC->TextOut(294, rect.bottom , "128");
	pDC->TextOut(40, rect.bottom , "0");


	pDC->TextOut(5, rect.bottom  - (nHeight - 20), LongToString(tempMax));
	pDC->TextOut(5, rect.bottom  - (nHeight - 20) / 2, LongToString(tempMax/2));
	pDC->TextOut(5, rect.bottom  - (nHeight - 20) / 4, LongToString(tempMax/4));

	rate = tempMax / (double)(nHeight - 20);
	for(i = 0; i < 256; i ++)
	{
		pDC->MoveTo(rect.left + 42 + i * 2, rect.bottom - 5);
		pDC->LineTo(rect.left + 42 + i * 2, 
			rect.bottom - 5 - (int)(Hist[Start + i] / rate + 0.5)); 
	}
}

void CHistGramView::DrawHist(long lBitCount, CHistGramDoc * pDoc, CDC *pDC)
{
	CRect rect;
	//int i;
	//double rate;
	//long tempMax;
	CFont fntST;

	fntST.CreateFont(0,0,0,0,0,0,0,0,0,0,0,0,0,"ËÎÌו");

	if (lBitCount == 8)
	{
		CPen blackPen(PS_SOLID, 1, RGB(0,0,0));
		//pDC->SelectObject(blackPen);

		rect.top = 0;
		rect.left = 0;
		rect.bottom = 350;
		rect.right = 600;
		DrawHistSon(rect,&blackPen,&fntST,pDC,pDoc->pHist,0);
		
		//AfxMessageBox(_ecvt(pDoc->pHist[200],10,&i,&j));
	}
	else if (lBitCount == 24)
	{
		CPen redPen(PS_SOLID, 1, RGB(255,0,0));
		CPen greenPen(PS_SOLID, 1, RGB(0,255,0));
		CPen bluePen(PS_SOLID, 1, RGB(0,0,255));


		//red
		rect.top = 0;
		rect.left = 0;
		rect.bottom = 200;
		rect.right = 600;
		DrawHistSon(rect,&redPen,&fntST,pDC,pDoc->pHist,512);

		//green
		rect.top = 220;
		rect.left = 0;
		rect.bottom = 420;
		rect.right = 600;
		DrawHistSon(rect,&greenPen,&fntST,pDC,pDoc->pHist,256);
		
		//blue
		rect.top = 440;
		rect.left = 0;
		rect.bottom = 640;
		rect.right = 600;
		DrawHistSon(rect,&bluePen,&fntST,pDC,pDoc->pHist,0);
	}
}

long CHistGramView::GetMax(long *List, int length, int StartPos)
{
	int i, pos;
	long temp;
	temp = List[StartPos];
	for (i = StartPos; i < length + StartPos; i++)
	{
		if (List[i] > temp)
		{
			temp = List[i];
			pos = i;
		}
	}

	return temp;
}

CString CHistGramView::LongToString(long data)
{
	CString str;
	int dec,sign;
	str = _ecvt(data,10,&dec,&sign);
	//AfxMessageBox(str.Left(dec));
	return str.Left(dec);
}

BOOL CHistGramView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	return CScrollView::PreCreateWindow(cs);
}


void CHistGramView::OnInitialUpdate() 
{
	CScrollView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	CHistGramDoc * pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CSize sizeTotal;
	
	if (pDoc->BitCount == 8)
	{
		sizeTotal.cy = 370;
	}
	else if(pDoc->BitCount == 24)
	{
		sizeTotal.cy = 670;
	}

	//sizeTotal.cy = 600;
	sizeTotal.cx = 600;
	SetScrollSizes(MM_TEXT, sizeTotal);

	ResizeParentToFit(TRUE);

    //LPRECT pRect;
	//GetParentFrame()->RecalcLayout();// GetWindowRect(pRect);
	//SetScaleToFitSize(sizeTotal);
	//this->SetWindowPos(&wndTop, pRect->left, pRect->top, 
	//	sizeTotal.cx, sizeTotal.cy, SWP_SHOWWINDOW);

  }
