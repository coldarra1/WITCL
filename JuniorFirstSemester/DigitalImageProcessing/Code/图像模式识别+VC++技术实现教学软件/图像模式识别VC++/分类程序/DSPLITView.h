// DSPLITView.h : interface of the CDSPLITView class
// 2005.1.13гн16г║02 By Superman 
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DSPLITVIEW_H__9FA7BE6A_AEB8_42C7_A006_E34615FDE7D8__INCLUDED_)
#define AFX_DSPLITVIEW_H__9FA7BE6A_AEB8_42C7_A006_E34615FDE7D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
////#include "DSPLITDoc.h"
//#include "DynSplitView2.h"
class CDSPLITView : public CView
{
protected: // create from serialization only
	CDSPLITView();
	DECLARE_DYNCREATE(CDSPLITView)

// Attributes
public:
	int state;
	Classification *classify;
	CPalette hPalette;
	BYTE* m_pData;
	int wide,height,LineBytes;
	BOOL lbtDown;
	BOOL rbtDown;
public:
	CDSPLITDoc* GetDocument();
	CPalette* CreateBitmapPalette(CDib *pBitmap);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDSPLITView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	void clearmem();
	virtual ~CDSPLITView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDSPLITView)
	afx_msg void OnButtonClear();
	afx_msg void OnButtondisplay();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DSPLITView.cpp
inline 
CDSPLITDoc* CDSPLITView::GetDocument()
   { return (CDSPLITDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DSPLITVIEW_H__9FA7BE6A_AEB8_42C7_A006_E34615FDE7D8__INCLUDED_)
