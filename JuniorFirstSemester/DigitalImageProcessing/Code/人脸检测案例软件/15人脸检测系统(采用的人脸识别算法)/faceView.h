// faceView.h : interface of the CFaceView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FACEVIEW_H__444D77F2_7A5B_49CB_BE46_F7B2A2C4E742__INCLUDED_)
#define AFX_FACEVIEW_H__444D77F2_7A5B_49CB_BE46_F7B2A2C4E742__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DIB.h"


class CFaceView : public CScrollView
{
protected: // create from serialization only
	CFaceView();
	DECLARE_DYNCREATE(CFaceView)

// Attributes
public:
	CFaceDoc* GetDocument();

// Operations
public:
	CRect faceLocation[10];
	int faceNum;
	bool flag[ImgRange][ImgRange];
	LPBYTE lpYcc;
	LPBYTE lpRB;
	LPBYTE lpYccTemp;
	LPBYTE lpRgb;
	bool   emymapl[ImgRange][ImgRange];
	bool   emymapc[ImgRange][ImgRange];
	bool   lab[ImgRange][ImgRange];
	CPoint mouthLocation;
	CPoint eye1;
	CPoint eye2;
	bool   result;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFaceView)
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
	virtual ~CFaceView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFaceView)
	afx_msg void OnErasion();
	afx_msg void OnEyemap();
	afx_msg void OnEyemapc();
	afx_msg void OnEyemapl();
	afx_msg void OnGetFaceArea();
	afx_msg void OnLightingconpensate();
	afx_msg void OnSkintone();
	afx_msg void OnDeleteFalseArea();
	afx_msg void OnDilation();
	afx_msg void OnErasionAgain();
	afx_msg void OnDilationFirst();
	afx_msg void OnEyeCb();
	afx_msg void OnEYECr();
	afx_msg void OnDeleteFalseEye();
	afx_msg void OnDeletescater();
	afx_msg void OnMousemap();
	afx_msg void OnErasionMouse();
	afx_msg void OnMouthCenter();
	afx_msg void OnDilationEye();
	afx_msg void OnEyeCenter();
	afx_msg void OnGouleFace();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in faceView.cpp
inline CFaceDoc* CFaceView::GetDocument()
   { return (CFaceDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FACEVIEW_H__444D77F2_7A5B_49CB_BE46_F7B2A2C4E742__INCLUDED_)
