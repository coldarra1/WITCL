// recognise_yanView.h : interface of the CRecognise_yanView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECOGNISE_YANVIEW_H__AAEF4CBD_8D10_4F50_B079_80A6D822EC23__INCLUDED_)
#define AFX_RECOGNISE_YANVIEW_H__AAEF4CBD_8D10_4F50_B079_80A6D822EC23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "dib.h"

class CRecognise_yanView : public CView
{
protected: // create from serialization only
	CRecognise_yanView();
	DECLARE_DYNCREATE(CRecognise_yanView)

// Attributes
public:
	CRecognise_yanDoc* GetDocument();
	CDIB m_dib;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecognise_yanView)
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
	virtual ~CRecognise_yanView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRecognise_yanView)
	afx_msg void OnOpenImage();
	afx_msg void OnRecogniseImage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in recognise_yanView.cpp
inline CRecognise_yanDoc* CRecognise_yanView::GetDocument()
   { return (CRecognise_yanDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECOGNISE_YANVIEW_H__AAEF4CBD_8D10_4F50_B079_80A6D822EC23__INCLUDED_)
