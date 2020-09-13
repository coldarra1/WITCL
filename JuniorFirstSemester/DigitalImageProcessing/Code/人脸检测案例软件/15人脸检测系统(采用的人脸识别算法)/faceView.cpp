// faceView.cpp : implementation of the CFaceView class
//

#include "stdafx.h"
#include "face.h"
#include "DIB.h"
#include "faceDoc.h"
#include "faceView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern class DIB gDib;
extern HANDLE hDIB;
extern HANDLE hDIBTemp;
extern int gheight;
extern int gwidth;
extern WORD gwBytesPerLine;
/////////////////////////////////////////////////////////////////////////////
// CFaceView

IMPLEMENT_DYNCREATE(CFaceView, CScrollView)

BEGIN_MESSAGE_MAP(CFaceView, CScrollView)
	//{{AFX_MSG_MAP(CFaceView)
	ON_COMMAND(ID_ERASION, OnErasion)
	ON_COMMAND(ID_EYEMAP, OnEyemap)
	ON_COMMAND(ID_EYEMAPC, OnEyemapc)
	ON_COMMAND(ID_EYEMAPL, OnEyemapl)
	ON_COMMAND(ID_GET_FACE_AREA, OnGetFaceArea)
	ON_COMMAND(ID_LIGHTINGCONPENSATE, OnLightingconpensate)
	ON_COMMAND(ID_SKINTONE, OnSkintone)
	ON_COMMAND(ID_DELETE_FALSE_AREA, OnDeleteFalseArea)
	ON_COMMAND(ID_DILATION, OnDilation)
	ON_COMMAND(ID_ERASION_AGAIN, OnErasionAgain)
	ON_COMMAND(ID_DILATION_FIRST, OnDilationFirst)
	ON_COMMAND(ID_EYE_CB, OnEyeCb)
	ON_COMMAND(ID_EYE_Cr, OnEYECr)
	ON_COMMAND(ID_DELETE_FALSE_EYE, OnDeleteFalseEye)
	ON_COMMAND(ID_DELETESCATER, OnDeletescater)
	ON_COMMAND(ID_MOUSEMAP, OnMousemap)
	ON_COMMAND(ID_ERASION_MOUSE, OnErasionMouse)
	ON_COMMAND(ID_MOUTH_CENTER, OnMouthCenter)
	ON_COMMAND(ID_DILATION_EYE, OnDilationEye)
	ON_COMMAND(ID_EYE_CENTER, OnEyeCenter)
	ON_COMMAND(ID_GOULE_FACE, OnGouleFace)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFaceView construction/destruction

CFaceView::CFaceView()
{
	lpRgb = NULL;
	lpYcc = NULL;
	faceNum = 0;
	for(int i=0; i<ImgRange; i++)
		for (int j=0; j<ImgRange; j++)
		{
			this->emymapc[i][j] = false;
			this->emymapl[i][j] = false;
			this->lab[i][j] = false;
		}
	this->result = false;
}

CFaceView::~CFaceView()
{
}

BOOL CFaceView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFaceView drawing

void CFaceView::OnDraw(CDC* pDC)
{
	CFaceDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(hDIB)
		gDib.PaintDIBTrue(pDC->GetSafeHdc(),CRect(0,0,gwidth,gheight),hDIB,CRect(0,0,gwidth,gheight),SRCCOPY);
	
	// TODO: add draw code for native data here
}


void CFaceView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CFaceView printing

BOOL CFaceView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFaceView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFaceView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CFaceView diagnostics

#ifdef _DEBUG
void CFaceView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CFaceView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CFaceDoc* CFaceView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFaceDoc)));
	return (CFaceDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFaceView message handlers

void CFaceView::OnErasion() 
{
	gDib.Erasion(hDIB);
	gDib.Erasion(hDIB);
	gDib.Erasion(hDIB);
	Invalidate();
	
}

void CFaceView::OnEyemap() 
{
	LPBYTE lpData;
	long lOffset;
	lpData = gDib.FindDIBBits(hDIB);
	for (int i=0; i<gheight; i++)
		for (int j=0; j<gwidth; j++)
		{
			lOffset = gDib.PixelOffset(i, j, gwBytesPerLine);
			if( this->emymapc[i][j] && this->emymapl[i][j])
			{
				*(lpData + lOffset++) = 255;
				*(lpData + lOffset++) = 255;
				*(lpData + lOffset++) = 255;
			}

			else
			{
				*(lpData + lOffset++) = 0;
				*(lpData + lOffset++) = 0;
				*(lpData + lOffset++) = 0;
			}
		}
	Invalidate();
}

void CFaceView::OnEyemapc() 
{	
	LPBYTE lpData;
	if(lpYcc)
		delete[] lpYcc;
	lpYcc = new BYTE[gwBytesPerLine * gheight];
	 gDib.RgbtoYcb(hDIBTemp,lpYcc);
	 
	GlobalLock(hDIB);
	lpData = gDib.FindDIBBits(hDIB);
	//memcpy(lpData,gDib.YcctoRgb(lpYcc,gwBytesPerLine,gheight,gwidth),gwBytesPerLine*gheight);

	gDib.EyeMapC(lpData,lpYcc,gwBytesPerLine,CRect(0,0,gwidth-1,gheight-1));
	for(int i=0; i<gheight; i++)
		for (int j=0; j<gwidth; j++)
		{
			long lOffset;
			lOffset = gDib.PixelOffset(i, j, gwBytesPerLine);
			if(*(lpData + lOffset) == 255)
			{
				this->emymapc[i][j] = true;
			}
		}
	GlobalUnlock(hDIB);
	Invalidate();
	
}

void CFaceView::OnEyemapl() 
{
	LPBYTE lpDataR,lpDataD;
	if(lpYcc)
		delete[] lpYcc;
	GlobalLock(hDIBTemp);
	lpDataR = gDib.FindDIBBits(hDIBTemp);
	lpYcc = new BYTE[gwBytesPerLine * gheight];
	gDib.RgbtoYcb(hDIBTemp,lpYcc);
	lpDataD = gDib.FindDIBBits(hDIB);
	memcpy(lpDataD,lpDataR,gwBytesPerLine*gheight);
	gDib.EyeMapL(lpDataD,gwBytesPerLine, CRect(0,0,gwidth-1,gheight-1));
	for (int i=0; i<gheight; i++)
		for (int j=0; j<gwidth; j++)
		{
			long lOffset;
			lOffset = gDib.PixelOffset(i, j, gwBytesPerLine);
			if(*(lpDataD + lOffset) == 255)
			{
				this->emymapl[i][j] = true;
			}
		}
		GlobalUnlock(hDIBTemp);
	Invalidate();
	
}

void CFaceView::OnGetFaceArea() 
{
	gDib.FaceLocate(hDIB,faceLocation,faceNum);
	Invalidate();
	
}

void CFaceView::OnLightingconpensate() 
{	
	hDIBTemp = gDib.CopyHandle(hDIB);
	gDib.LightingCompensate(hDIB);
	GlobalUnlock(hDIB);
	Invalidate();
	
}

void CFaceView::OnSkintone() //¼ì²â·ôÉ«
{	
	lpYcc = new BYTE[gwBytesPerLine * gheight];
	gDib.RgbtoYcb(hDIB,lpYcc);
	gDib.YccTransform(lpYcc, gwBytesPerLine,gheight,gwidth);
	gDib.faceear(lpYcc,gwBytesPerLine,gheight,gwidth,flag);
	
	LPBYTE lpData = (LPBYTE)GlobalLock(hDIB)+sizeof(BITMAPINFOHEADER);
	
	for (int i=0; i<gheight; i++)
		for (int j=0; j<gwidth; j++)
		{	
			long lOffset = gDib.PixelOffset(i, j, gwBytesPerLine);
			if (flag[i][j] == true)
			{
				*(lpData + lOffset++) = 255;
				*(lpData + lOffset++) = 255;
				*(lpData + lOffset++) = 255;
			}
			else
			{
				*(lpData + lOffset++) = 0;
				*(lpData + lOffset++) = 0;
				*(lpData + lOffset++) = 0;
			}
		}
		
		GlobalUnlock(hDIB);
		Invalidate();
}

void CFaceView::OnDeleteFalseArea() 
{
	gDib.ErasionFalseArea(hDIB);
	
	Invalidate();
	
}

void CFaceView::OnDilation() //ÅòÕÍ
{
	gDib.Dilation(hDIB);
	gDib.Dilation(hDIB);
	gDib.Dilation(hDIB);
	gDib.Dilation(hDIB);
	gDib.Dilation(hDIB);
	gDib.Dilation(hDIB);
	gDib.Dilation(hDIB);
	gDib.Dilation(hDIB);
	gDib.Dilation(hDIB);
	gDib.Dilation(hDIB);
	gDib.Dilation(hDIB);
	gDib.Dilation(hDIB);
	gDib.Dilation(hDIB);
	Invalidate();
	
}

void CFaceView::OnErasionAgain() //¸¯Ê´
{
	gDib.Erasion(hDIB);
	gDib.Erasion(hDIB);
	gDib.Erasion(hDIB);
	gDib.Erasion(hDIB);
	gDib.Erasion(hDIB);
	gDib.Erasion(hDIB);
	gDib.Erasion(hDIB);
	gDib.Erasion(hDIB);
	gDib.Erasion(hDIB);
	gDib.Erasion(hDIB);
	gDib.Erasion(hDIB);
	gDib.Erasion(hDIB);
	gDib.Erasion(hDIB);
	gDib.Erasion(hDIB);
	LPBYTE lpData;
	GlobalLock(hDIB);
	lpData = gDib.FindDIBBits(hDIB);
	for (int i=0;i<gheight; i++)
		for (int j=0; j<gwidth; j++)
		{
			long lOffset = gDib.PixelOffset(i, j, gwBytesPerLine);
			if(*(lpData + lOffset) == 255)
			{
				this->lab[i][j] = true;
			}
		}
	GlobalUnlock(hDIB);
	Invalidate();
	
}

void CFaceView::OnDilationFirst() //µÚÒ»´Î¸¯Ê´
{
	gDib.Dilation(hDIB);
	gDib.Dilation(hDIB);
	Invalidate();
	
}

void CFaceView::OnEyeCb() 
{	
	lpRB = new BYTE[gwBytesPerLine * gheight];
	gDib.RgbtoYcb(hDIBTemp,lpRB);
	LPBYTE lpData =gDib.FindDIBBits(hDIB);
	gDib.EyeMapb(lpData,lpRB,gwBytesPerLine,CRect(0,0,gwidth-1,gheight-1));
	Invalidate();
	
}

void CFaceView::OnEYECr() 
{
	lpRB = new BYTE[gwBytesPerLine * gheight];
	gDib.RgbtoYcb(hDIBTemp,lpRB);
	LPBYTE lpData =gDib.FindDIBBits(hDIB);
	gDib.EyeMapR(lpData,lpRB,gwBytesPerLine,CRect(0,0,gwidth-1,gheight-1));
	Invalidate();
}

void CFaceView::OnDeleteFalseEye() 
{
	gDib.DeleteFasleEye(hDIB,faceLocation[0]);
	Invalidate();
}

void CFaceView::OnDeletescater() 
{
	gDib.DeleteScatePoint(hDIB);
	gDib.Dilation(hDIB);
	Invalidate();
	
}

void CFaceView::OnMousemap() 
{	
	if(lpYcc)
		delete [] lpYcc;
	lpYcc = new BYTE[gwBytesPerLine * gheight];
	if(!lpYcc)
		return;
	gDib.RgbtoYcb(hDIBTemp,lpYcc);
	LPBYTE lpData = gDib.FindDIBBits(hDIB);
	gDib.MouseMap(lpData,lpYcc,gwBytesPerLine,CRect(0,0,gwidth-1,gheight-1));
	//gDib.Erasion2(hDIB);
	
	Invalidate();
	

	
}

void CFaceView::OnErasionMouse() 
{
	gDib.Erasion2(hDIB);
	//gDib.DeleteScatePoint(hDIB);
	//gDib.Dilation(hDIB);
	//gDib.Dilation(hDIB);
	//gDib.DeleteScatePoint(hDIB);
	Invalidate();
}

void CFaceView::OnMouthCenter() 
{
	gDib.MouthCenter(hDIB,CRect(0,0,gwidth-1,gheight-1),mouthLocation);
	this->result = true;
	Invalidate();
}

void CFaceView::OnDilationEye() 
{
	gDib.Dilation(hDIB);
	Invalidate();
		
}

void CFaceView::OnEyeCenter() 
{
	gDib.EyeCenter(hDIB,CRect(0,0,gwidth-1,gheight-1),eye1,eye2);
	Invalidate();
}

void CFaceView::OnGouleFace() 
{
	gDib.EllipseFace(hDIBTemp,this->mouthLocation,this->eye1,this->eye2);
	if(hDIB)
		GlobalFree(hDIB);
	hDIB = gDib.CopyHandle(hDIBTemp);
	Invalidate();

}
