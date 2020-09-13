// XBPJ_LRYView.h : interface of the CXBPJ_LRYView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XBPJ_LRYVIEW_H__CC449655_B1A7_45D2_B076_8AA497868216__INCLUDED_)
#define AFX_XBPJ_LRYVIEW_H__CC449655_B1A7_45D2_B076_8AA497868216__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CXBPJ_LRYView : public CScrollView
{
protected: // create from serialization only
	CXBPJ_LRYView();
	DECLARE_DYNCREATE(CXBPJ_LRYView)

// Attributes
public:
	CXBPJ_LRYDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXBPJ_LRYView)
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
	virtual ~CXBPJ_LRYView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CXBPJ_LRYView)
	afx_msg void Onwavelet();
	afx_msg void OnwaveletPJ();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in XBPJ_LRYView.cpp
inline CXBPJ_LRYDoc* CXBPJ_LRYView::GetDocument()
   { return (CXBPJ_LRYDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XBPJ_LRYVIEW_H__CC449655_B1A7_45D2_B076_8AA497868216__INCLUDED_)
