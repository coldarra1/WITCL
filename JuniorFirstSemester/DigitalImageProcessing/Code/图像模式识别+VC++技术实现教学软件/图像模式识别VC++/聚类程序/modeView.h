// modeView.h : interface of the CModeView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODEVIEW_H__123C9597_B4CD_4744_BD2E_6BAA96F34A9C__INCLUDED_)
#define AFX_MODEVIEW_H__123C9597_B4CD_4744_BD2E_6BAA96F34A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cluster.h"

class CModeView : public CView
{

struct StandardNum 
{
	int wide;
	int height;
};

protected: // create from serialization only
	CModeView();
	DECLARE_DYNCREATE(CModeView)

// Attributes
public:
	CModeDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModeView)
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
	virtual ~CModeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
public:
	void display();
	CCluster * pCluster;

protected:
	CPalette hPalette;
	bool stateDoc;//doc关联状态，true为已经关联。
	bool lButtonDown;//左键状态。true为按下
	bool statePen;//true为改写状态，false为橡皮状态；

	CPalette * CreateBitmapPalette(CCluster * pBitmap);

private:
	int wide;
	int height;
	BYTE * m_pData;
	StandardNum snum[10];
	int positionx,positiony;
	CString dir;

// Generated message map functions
protected:
	//{{AFX_MSG(CModeView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPen();
	afx_msg void OnEraser();
	afx_msg void OnStandardNum(UINT ID);
	afx_msg void OnFilenew();
	afx_msg void OnFileopen();
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in modeView.cpp
inline CModeDoc* CModeView::GetDocument()
   { return (CModeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODEVIEW_H__123C9597_B4CD_4744_BD2E_6BAA96F34A9C__INCLUDED_)
