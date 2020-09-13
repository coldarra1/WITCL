#if !defined(AFX_DYNSPLITVIEW2_H__76E949DA_9CAD_11D1_907F_00A024782894__INCLUDED_)
#define AFX_DYNSPLITVIEW2_H__76E949DA_9CAD_11D1_907F_00A024782894__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DynSplitView2.h : header file
//
#include"DSplitDoc.h"
/////////////////////////////////////////////////////////////////////////////
// CDynSplitView2 view
#include "TeXiaoXianShiDib.h"
#include "CDIB.h"

class CDynSplitView2 : public CView
{
protected:
	DECLARE_DYNCREATE(CDynSplitView2)

// Attributes
public:
	CDSplitDoc* GetDocument();

// Operations
public:
		CPalette *CreateBitmapPalette( TeXiaoXianShiDib* pBitmap);
 		CString filename;
		TeXiaoXianShiDib *CDibNew1;
		CDib *CDib1;
		CPalette hPalette;
		int state2;
		void clearmem();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDynSplitView2)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
#ifdef _DEBUG
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CDynSplitView2)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnFilesave();
	afx_msg void OnOpenFileTwo();
	afx_msg void OndeleteNoise2();
	afx_msg void Onthin2();
	afx_msg void Onmatch();
	afx_msg void OnLvBo2();
	afx_msg void Ondirection2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DYNSPLITVIEW2_H__76E949DA_9CAD_11D1_907F_00A024782894__INCLUDED_)
