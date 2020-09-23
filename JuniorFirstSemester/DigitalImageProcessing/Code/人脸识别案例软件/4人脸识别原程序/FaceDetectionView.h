// FaceDetectionView.h : interface of the CFaceDetectionView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FACEDETECTIONVIEW_H__F626FC59_5D81_4DC2_9EF5_E34C712167DE__INCLUDED_)
#define AFX_FACEDETECTIONVIEW_H__F626FC59_5D81_4DC2_9EF5_E34C712167DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFaceDetectionView : public CView
{
protected: // create from serialization only
	CFaceDetectionView();
	DECLARE_DYNCREATE(CFaceDetectionView)

// Attributes
public:
	CFaceDetectionDoc* GetDocument();

// Operations
public:
	CRect faceLocation[10];
	int faceNum;
	CPoint mouthLocation;
	CPoint eye1;
	CPoint eye2;
	bool   result;
	bool  facedetect;
	bool  eyedetect;
	bool  mousedetect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFaceDetectionView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFaceDetectionView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFaceDetectionView)
	afx_msg void OnLightconpensate();
	afx_msg void OnSkintone();
	afx_msg void OnDilationFirst();
	afx_msg void OnErasionFirst();
	afx_msg void OnDeleteFalseArea();
	afx_msg void OnDilationAgain();
	afx_msg void OnErasionAgain();
	afx_msg void OnGetFaceArea();
	afx_msg void OnEyemapc();
	afx_msg void OnEyemapl();
	afx_msg void OnEyemap();
	afx_msg void OnDeleteFalseEye();
	afx_msg void OnDilationEye();
	afx_msg void OnEyeCenter();
	afx_msg void OnMousemap();
	afx_msg void OnErasionMouse();
	afx_msg void OnDeletescater();
	afx_msg void OnMouthCenter();
	afx_msg void OnGouleFace();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FaceDetectionView.cpp
inline CFaceDetectionDoc* CFaceDetectionView::GetDocument()
   { return (CFaceDetectionDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FACEDETECTIONVIEW_H__F626FC59_5D81_4DC2_9EF5_E34C712167DE__INCLUDED_)
