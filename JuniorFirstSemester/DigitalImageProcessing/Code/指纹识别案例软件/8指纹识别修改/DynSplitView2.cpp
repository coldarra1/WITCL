// DynSplitView2.cpp : implementation file
//

#include "stdafx.h"
#include "DSplit.h"
#include "DynSplitView2.h"
 
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDynSplitView2

IMPLEMENT_DYNCREATE(CDynSplitView2, CView)

//DEL CDynSplitView2::CDynSplitView2()
//DEL {
//DEL 	state2=0;
//DEL }


/*初始化图像数据*/
void CDynSplitView2::clearmem()
{
	CDSplitDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc ->statedoc=0;
    state2=1;
	
	CDibNew1=&pDoc->CDibNew;
   // CDib1=&pDoc->CDib;
//	long int  size=CDib1->GetHeight()*CDib1->GetWidth();
//	memcpy(CDibNew1->m_pData,CDib1->m_pData,size);//复制原图像到处理区
	

}

/*CPalette * CDynSplitView2::CreateBitmapPalette(TeXiaoXianShiDib * pBitmap)
	{
		struct
		{
			WORD Version;
			WORD NumberOfEntries;
			PALETTEENTRY aEntries[256];
		} palette = { 0x300, 256 };
		
		LPRGBQUAD pRGBTable = pBitmap->GetRGB();
		UINT numberOfColors = pBitmap->GetNumberOfColors();
		
		for(UINT x=0; x<numberOfColors; ++x)
		{
			palette.aEntries[x].peRed =
				pRGBTable[x].rgbRed;
			palette.aEntries[x].peGreen =
				pRGBTable[x].rgbGreen;
			palette.aEntries[x].peBlue =
				pRGBTable[x].rgbBlue;
			palette.aEntries[x].peFlags = 0;
		}
		
			hPalette.CreatePalette((LPLOGPALETTE)&palette);
		//CPalette hPale=&hPalette;
		return &hPalette;
	}*/

//DEL CDynSplitView2::~CDynSplitView2()
//DEL {
//DEL }
CDSplitDoc* CDynSplitView2::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDSplitDoc)));
	return (CDSplitDoc*)m_pDocument;
}


BEGIN_MESSAGE_MAP(CDynSplitView2, CView)
	//{{AFX_MSG_MAP(CDynSplitView2)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_FILESAVE, OnFilesave)
	ON_COMMAND(ID_OpenFileTwo, OnOpenFileTwo)
	ON_COMMAND(ID_thin2, Onthin2)
	ON_COMMAND(ID_match, Onmatch)
	ON_COMMAND(ID_LvBo2, OnLvBo2)
	ON_COMMAND(ID_direction2, Ondirection2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDynSplitView2 drawing

void CDynSplitView2::OnDraw(CDC* pDC)
{ 
	CDSplitDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	

		 CBitmap m_bitmap;

	    HBITMAP hBitmap=(HBITMAP)LoadImage(NULL,_T(filename),IMAGE_BITMAP,
		   0,0,LR_CREATEDIBSECTION|LR_DEFAULTSIZE|LR_LOADFROMFILE);

        m_bitmap.Attach (hBitmap);
	    CDC dcImage;
	    if(!dcImage.CreateCompatibleDC (pDC))
		    return;
	    BITMAP bm;
	    m_bitmap.GetBitmap (&bm);
        dcImage.SelectObject (&m_bitmap);
	    pDC->BitBlt (0,0,bm.bmWidth ,bm.bmHeight ,&dcImage,0,0,SRCCOPY);

}


/////////////////////////////////////////////////////////////////////////////
// CDynSplitView2 diagnostics

#ifdef _DEBUG
//DEL void CDynSplitView2::AssertValid() const
//DEL {
//DEL 	CView::AssertValid();
//DEL }

void CDynSplitView2::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDynSplitView2 message handlers

BOOL CDynSplitView2::OnEraseBkgnd(CDC* pDC) 
{
	CRect rect;
	GetClientRect(&rect);
	pDC->FillSolidRect(&rect,::GetSysColor(COLOR_WINDOW));
	return TRUE;
}

void CDynSplitView2::OnFilesave() 
{
	// TODO: Add your command handler code here
/*	CFileDialog dlg(FALSE,_T("BMP"),_T("*.BMP"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("位图文件(*.BMP)|*.BMP|"));	
    if(IDOK==dlg.DoModal())
		CString  filename;
    filename.Format ("%s",dlg.GetPathName() );    
    CDibNew1->SaveFile(filename);
	state2=1;
	Invalidate();*/
}



//DEL void CDynSplitView2::OnYuantu() 
//DEL {
//DEL 	// TODO: Add your command handler code here
//DEL 	CDSplitDoc* pDoc = GetDocument();
//DEL 	ASSERT_VALID(pDoc);
//DEL     filename=pDoc->filename;
//DEL  	state2 = 1;
//DEL 	clearmem();
//DEL 	Invalidate();
//DEL 	
//DEL }




