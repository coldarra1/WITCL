// FaceDetectionView.cpp : implementation of the CFaceDetectionView class
//

#include "stdafx.h"
#include "FaceDetection.h"

#include "FaceDetectionDoc.h"
#include "FaceDetectionView.h"
#include "dibapi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFaceDetectionView

IMPLEMENT_DYNCREATE(CFaceDetectionView, CView)

BEGIN_MESSAGE_MAP(CFaceDetectionView, CView)
	//{{AFX_MSG_MAP(CFaceDetectionView)
	ON_COMMAND(ID_LIGHT, OnLightconpensate)
	ON_COMMAND(ID_SKINTONE, OnSkintone)
	ON_COMMAND(ID_DILATION_FIRST, OnDilationFirst)
	ON_COMMAND(ID_ERASION, OnErasionFirst)
	ON_COMMAND(ID_DELETE_FALSE_AREA, OnDeleteFalseArea)
	ON_COMMAND(ID_DILATION, OnDilationAgain)
	ON_COMMAND(ID_ERASION_AGAIN, OnErasionAgain)
	ON_COMMAND(ID_GET_FACE_AREA, OnGetFaceArea)
	ON_COMMAND(ID_EYEMAPC, OnEyemapc)
	ON_COMMAND(ID_EYEMAPL, OnEyemapl)
	ON_COMMAND(ID_EYEMAP, OnEyemap)
	ON_COMMAND(ID_DELETE_FALSE_EYE, OnDeleteFalseEye)
	ON_COMMAND(ID_DILATION_EYE, OnDilationEye)
	ON_COMMAND(ID_EYE_CENTER, OnEyeCenter)
	ON_COMMAND(ID_MOUSEMAP, OnMousemap)
	ON_COMMAND(ID_ERASION_MOUSE, OnErasionMouse)
	ON_COMMAND(ID_DELETESCATER, OnDeletescater)
	ON_COMMAND(ID_MOUTH_CENTER, OnMouthCenter)
	ON_COMMAND(ID_GOULE_FACE, OnGouleFace)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFaceDetectionView construction/destruction

CFaceDetectionView::CFaceDetectionView()
{
	// TODO: add construction code here
	faceNum = 0;
	facedetect=false;
	eyedetect=false;
	mousedetect=false;
}

CFaceDetectionView::~CFaceDetectionView()
{
}

BOOL CFaceDetectionView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFaceDetectionView drawing

void CFaceDetectionView::OnDraw(CDC* pDC)
{
	CFaceDetectionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
		
	HDIB m_hDIB = pDoc->m_hDIB;

	// 判断DIB是否为空
	if (m_hDIB != NULL)
	{
		LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) m_hDIB);
		
		// 获取DIB宽度
		int cxDIB = (int) ::DIBWidth(lpDIB);
		
		// 获取DIB高度
		int cyDIB = (int) ::DIBHeight(lpDIB);

		::GlobalUnlock((HGLOBAL) m_hDIB);
		
		CRect rcDIB;
		rcDIB.top = rcDIB.left = 0;
		rcDIB.right = cxDIB;
		rcDIB.bottom = cyDIB;
		
		CRect rcDest;
		
		// 判断是否是打印
		if (pDC->IsPrinting())
		{
			// 是打印，计算输出图像的位置和大小，以便符合页面
			
			// 获取打印页面的水平宽度(象素)
			int cxPage = pDC->GetDeviceCaps(HORZRES);
			
			// 获取打印页面的垂直高度(象素)
			int cyPage = pDC->GetDeviceCaps(VERTRES);
			
			// 获取打印机每英寸象素数
			int cxInch = pDC->GetDeviceCaps(LOGPIXELSX);
			int cyInch = pDC->GetDeviceCaps(LOGPIXELSY);
			
			// 计算打印图像大小（缩放，根据页面宽度调整图像大小）
			rcDest.top = rcDest.left = 0;
			rcDest.bottom = (int)(((double)cyDIB * cxPage * cyInch)
					/ ((double)cxDIB * cxInch));
			rcDest.right = cxPage;
			
			// 计算打印图像位置（垂直居中）
			int temp = cyPage - (rcDest.bottom - rcDest.top);
			rcDest.bottom += temp/2;
			rcDest.top += temp/2;

		}
		else   
		// 非打印
		{
			// 不必缩放图像
			rcDest = rcDIB;
		}
		

		::PaintDIB(pDC->m_hDC, &rcDest, pDoc->m_hDIB,
			&rcDIB, NULL);
	}
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CFaceDetectionView printing

BOOL CFaceDetectionView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFaceDetectionView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFaceDetectionView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CFaceDetectionView diagnostics

#ifdef _DEBUG
void CFaceDetectionView::AssertValid() const
{
	CView::AssertValid();
}

void CFaceDetectionView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFaceDetectionDoc* CFaceDetectionView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFaceDetectionDoc)));
	return (CFaceDetectionDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFaceDetectionView message handlers

void CFaceDetectionView::OnLightconpensate() 
{
	// TODO: Add your command handler code here
	CFaceDetectionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->LightingCompensate();
	pDoc->UpdateAllViews(NULL);
		
}

void CFaceDetectionView::OnSkintone() 
{
	CFaceDetectionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->Skintone();
	pDoc->UpdateAllViews(NULL);
	
}

void CFaceDetectionView::OnDilationFirst() 
{
	// TODO: Add your command handler code here
	CFaceDetectionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->Dilation();
	pDoc->Dilation();
	pDoc->UpdateAllViews(NULL);
	
}

void CFaceDetectionView::OnErasionFirst() 
{
	// TODO: Add your command handler code here
	CFaceDetectionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->Erasion();
	pDoc->Erasion();
	pDoc->UpdateAllViews(NULL);
	
}

void CFaceDetectionView::OnDeleteFalseArea() 
{
	// TODO: Add your command handler code here
	CFaceDetectionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->DeleteFalseArea();
	pDoc->UpdateAllViews(NULL);
	
}

void CFaceDetectionView::OnDilationAgain() 
{
	// TODO: Add your command handler code here
	CFaceDetectionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->Dilation();
	pDoc->Dilation();
	pDoc->Dilation();
	pDoc->Dilation();
	pDoc->Dilation();
	pDoc->Dilation();
	pDoc->Dilation();
	pDoc->Dilation();
	pDoc->Dilation();
	pDoc->Dilation();
	pDoc->Dilation();
	pDoc->Dilation();
	pDoc->UpdateAllViews(NULL);	
}

void CFaceDetectionView::OnErasionAgain() 
{
	// TODO: Add your command handler code here
	CFaceDetectionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->Erasion();
	pDoc->Erasion();
	pDoc->Erasion();
	pDoc->Erasion();
	pDoc->Erasion();
	pDoc->Erasion();
	pDoc->Erasion();
	pDoc->Erasion();
	pDoc->Erasion();
	pDoc->Erasion();
	pDoc->Erasion();
	pDoc->Erasion();
	pDoc->UpdateAllViews(NULL);
	
}

void CFaceDetectionView::OnGetFaceArea() 
{
	// TODO: Add your command handler code here
	CFaceDetectionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->FaceLocate(faceLocation,faceNum);
	facedetect=true;
	pDoc->UpdateAllViews(NULL);
	
}


void CFaceDetectionView::OnEyemapc() 
{
	// TODO: Add your command handler code here
	CFaceDetectionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->EyeMappingC();
	pDoc->UpdateAllViews(NULL);
	
}

void CFaceDetectionView::OnEyemapl() 
{
	// TODO: Add your command handler code here
	CFaceDetectionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->EyeMappingL();
	pDoc->UpdateAllViews(NULL);
	
}

void CFaceDetectionView::OnEyemap() 
{
	// TODO: Add your command handler code here
	CFaceDetectionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->Eyemap();
	pDoc->UpdateAllViews(NULL);
	
}

void CFaceDetectionView::OnDeleteFalseEye() 
{
	// TODO: Add your command handler code here
	if (!facedetect)
	{
		AfxMessageBox("请先检测人脸！");
			return;
	}
	CFaceDetectionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->DeleteFasleEye(faceLocation[0]);
	pDoc->UpdateAllViews(NULL);
}

void CFaceDetectionView::OnDilationEye() 
{
	// TODO: Add your command handler code here
	CFaceDetectionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->Dilation();
	pDoc->UpdateAllViews(NULL);	
}

void CFaceDetectionView::OnEyeCenter() 
{
	CFaceDetectionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->EyeCenter(eye1,eye2);
	eyedetect=true;
	pDoc->UpdateAllViews(NULL);		
}

void CFaceDetectionView::OnMousemap() 
{
	// TODO: Add your command handler code here
	CFaceDetectionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->MouseMap();
	pDoc->UpdateAllViews(NULL);	
	
}

void CFaceDetectionView::OnErasionMouse() 
{
	// TODO: Add your command handler code here
	CFaceDetectionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->ErasionMouse();
	pDoc->UpdateAllViews(NULL);
	
}

void CFaceDetectionView::OnDeletescater() 
{
	// TODO: Add your command handler code here
	CFaceDetectionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->DeleteScatePoint();
	pDoc->Dilation();
	pDoc->UpdateAllViews(NULL);
	
}

void CFaceDetectionView::OnMouthCenter() 
{
	// TODO: Add your command handler code here
	CFaceDetectionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->MouthCenter(mouthLocation);
	mousedetect=true;
	pDoc->UpdateAllViews(NULL);
	result = true;
}

void CFaceDetectionView::OnGouleFace() 
{
	// TODO: Add your command handler code here
	if(!(facedetect&&mousedetect&&eyedetect))
	{
		AfxMessageBox("请先完成人脸检测、人眼定位和嘴巴定位！");
			return;
	}
	CFaceDetectionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->EllipseFace(mouthLocation,eye1,eye2,faceLocation[0]);
	pDoc->UpdateAllViews(NULL);
	
}
