// ydpdView.h : interface of the CYdpdView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_YDPDVIEW_H__EFC5D39E_6423_4029_A8D9_5E14B33E44D0__INCLUDED_)
#define AFX_YDPDVIEW_H__EFC5D39E_6423_4029_A8D9_5E14B33E44D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ydgj.h"

class CYdpdView : public CScrollView
{
protected: // create from serialization only
	CYdpdView();
	DECLARE_DYNCREATE(CYdpdView)

// Attributes
public:
	CYdpdDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CYdpdView)
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
	GUIJI m_GuiJi;
	int m_bk_first_width;
	int m_bk_first_height;
	bool isBKChonsen;
	bool isTeZhengZhi;
	CPoint m_center[10];
	int m_Pointnum;
	virtual ~CYdpdView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CYdpdView)
	afx_msg void OnMenuBkFirst();
	afx_msg void OnMenuBkSecond();
	afx_msg void OnMenuBkGray();
	afx_msg void OnMenuGradient();
	afx_msg void OnMenuPipeizhongxin();
	afx_msg void OnMenuTezhengquyu();
	afx_msg void OnMenuPipei();
	afx_msg void OnMedifilter();
	afx_msg void OnMENUFILElOAD();
	afx_msg void OnMenuYdpdPipei();
	afx_msg void OnMenuYdpdMedi();
	afx_msg void OnMenuYdpdLktq();
	afx_msg void OnMenuYdpdEdgeGet();
	afx_msg void OnMenuYdpdBlackwhite();
	afx_msg void OnMenuYdpdThing();
	afx_msg void OnMenuYdpdDeletescater();
	afx_msg void OnMenuYdpdGuiji();
	afx_msg void OnMenuYdpdCenter();
	afx_msg void OnMenuYcx();
	afx_msg void OnSecondPipei();
	afx_msg void OnMenuPengzhang();
	afx_msg void OnMenuGetedge();
	afx_msg void OnMenuYdpdGray();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ydpdView.cpp
inline CYdpdDoc* CYdpdView::GetDocument()
   { return (CYdpdDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YDPDVIEW_H__EFC5D39E_6423_4029_A8D9_5E14B33E44D0__INCLUDED_)
