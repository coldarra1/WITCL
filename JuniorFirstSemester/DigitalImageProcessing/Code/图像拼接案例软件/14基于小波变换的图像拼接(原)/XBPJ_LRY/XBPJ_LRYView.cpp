// XBPJ_LRYView.cpp : implementation of the CXBPJ_LRYView class
//

#include "stdafx.h"
#include "XBPJ_LRY.h"

#include "XBPJ_LRYDoc.h"
#include "XBPJ_LRYView.h"

#include "Wavelet.h"
#include "WaveletPJDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXBPJ_LRYView

IMPLEMENT_DYNCREATE(CXBPJ_LRYView, CScrollView)

BEGIN_MESSAGE_MAP(CXBPJ_LRYView, CScrollView)
	//{{AFX_MSG_MAP(CXBPJ_LRYView)
	ON_COMMAND(ID_wavelet, Onwavelet)
	ON_COMMAND(ID_waveletPJ, OnwaveletPJ)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXBPJ_LRYView construction/destruction

CXBPJ_LRYView::CXBPJ_LRYView()
{
	// TODO: add construction code here

}

CXBPJ_LRYView::~CXBPJ_LRYView()
{
}

BOOL CXBPJ_LRYView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CXBPJ_LRYView drawing

void CXBPJ_LRYView::OnDraw(CDC* pDC)
{
	CXBPJ_LRYDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CXBPJ_LRYView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CXBPJ_LRYView printing

BOOL CXBPJ_LRYView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CXBPJ_LRYView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CXBPJ_LRYView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CXBPJ_LRYView diagnostics

#ifdef _DEBUG
void CXBPJ_LRYView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CXBPJ_LRYView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CXBPJ_LRYDoc* CXBPJ_LRYView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CXBPJ_LRYDoc)));
	return (CXBPJ_LRYDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CXBPJ_LRYView message handlers

void CXBPJ_LRYView::Onwavelet() 
{
	// TODO: Add your command handler code here
CWavelet dlg;
dlg.DoModal();	
}

void CXBPJ_LRYView::OnwaveletPJ() 
{
	// TODO: Add your command handler code here
CWaveletPJDlg dlg;
dlg.DoModal();	
}
