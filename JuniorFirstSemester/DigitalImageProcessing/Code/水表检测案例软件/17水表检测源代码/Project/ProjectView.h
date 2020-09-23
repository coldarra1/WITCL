// ProjectView.h : interface of the CProjectView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTVIEW_H__CABB3871_1197_4268_8246_CEDBC9597C7C__INCLUDED_)
#define AFX_PROJECTVIEW_H__CABB3871_1197_4268_8246_CEDBC9597C7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define XLEFT 40
#define XRIGHT 60
#define YTOP 60
#define YBOTTOM 40

#define SXLEFT 30
#define SXRIGHT 70
#define SYTOP 70
#define SYBOTTOM 30

//#define BIGD 20
//#define SMALLD 5
#define SMALLD 3
#define BIGD 15

#define QUEUELEN 100
#define MAXSIZE 100000
#define MAXXYR 120

//两种圆切换，需要改以下三个参数
//#define STEP 40
#define STEP 30
//#define STEP 20
//#define SMALLSTEP 10
#define SMALLSTEP 8
//#define SMALLSTEP 6
#define LEN 20
//#define LEN 15

#define GLOBALVALUE 198
#define pi 3.14159265
#define THITA 135

#include "ProjectDoc.h" 

class CProjectView : public CScrollView
{
protected: // create from serialization only
	CProjectView();
	DECLARE_DYNCREATE(CProjectView)

// Attributes
public:
	CProjectDoc* GetDocument();
	CProjectDoc* pDoc;
	int x1, y1, x2, y2, x3, y3, x, y;
	int fx1, fy1, fx2, fy2, fx3, fy3;
	int nAngle1, nAngle2, nAngle3;
	// Operations
public:
	void DisplayBmp8(CProjectDoc* pDoc, CDC * pDC);
	void DisplayBmp24(CProjectDoc* pDoc, CDC * pDC);
	void EdgeRobert(CProjectDoc* pProjectDoc);
	void EdgePrewitt(CProjectDoc* pProjectDoc);
	void EdgeSobel(CProjectDoc* pProjectDoc);
	void EdgeLaplace(CProjectDoc* pProjectDoc);
	int SearchPoint(int StartX, int StartY, int QUEUE[][2], int * nHead, int * nTail,
		BYTE *DATA, int nLimitedX, int nLimitedY, int Step, int nWidth);
	void Get_A_B_R(double xk, double yk, double xl, double yl, double xm, 
				 double ym, double *d_A, double *d_B, double *d_R);
	void InsertCount(int x, int y, int r, int Counter[]);
	void InsertIntoCount(int x, int y, int r, long i,int Counter[]);
    //void CircleDetect(CProjectDoc * pDoc, int nStep, int nMark,
		//int X_Left, int Y_Top, int R_Small, int *C_X, int *C_Y, double rate);
	void CircleDetect(CProjectDoc * pDoc, int nStep, int nMark, int X_Left, int X_Right, 
		int Y_Top, int Y_Bottom, int R_Small, int *C_X, int *C_Y, double rate);

	void FingerDetect(int x, int y, CProjectDoc * pDoc, int *fx, int *fy);
	void FindStartPoint(int x, int y, int * xStart, int * yStart, CProjectDoc * pDoc);
	void FingerDetectNew(int x, int y, CProjectDoc * pDoc, int *fx, int *fy, int *Angle);
	BOOL BelowUpon(int LineX1,int LineY1, int LineX2, int LineY2, int PointX, 
		int PointY, int nA1, int nA2, int nA3);
	CString LongToString(long data);
	BOOL SearchCount(long Start, long End, int x, int y, int r, int Counter[], long *pos);



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProjectView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CProjectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CProjectView)
	afx_msg void OnBaseinfoHist();
	afx_msg void OnBaseinfoInfo();
	afx_msg void OnEdgeRoberts();
	afx_msg void OnEdgePrewitt();
	afx_msg void OnEdgeSobel();
	afx_msg void OnAddReverse();
	afx_msg void OnAddGlobal();
	afx_msg void OnEdgeLaplace();
	afx_msg void OnAddCircledet();
	afx_msg void OnAddSmallcir();
	afx_msg void OnWygStep();
	afx_msg void OnWygStep2();
	afx_msg void OnAddTest();
	afx_msg void OnAddFinger();
	afx_msg void OnAddEnd();
	afx_msg void OnAddPrewitt();
	afx_msg void OnAddTotal();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ProjectView.cpp
inline CProjectDoc* CProjectView::GetDocument()
   { return (CProjectDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROJECTVIEW_H__CABB3871_1197_4268_8246_CEDBC9597C7C__INCLUDED_)
