#if !defined(AFX_DYNSPLITVIEW2_H__106C2C0B_2EEF_4338_83D0_F3AE7B273799__INCLUDED_)
#define AFX_DYNSPLITVIEW2_H__106C2C0B_2EEF_4338_83D0_F3AE7B273799__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DynSplitView2.h : header file
// 2005.1.13гн16г║02 By Superman 
#include "DSPLITDoc.h"
#include "BpNet.h"

/////////////////////////////////////////////////////////////////////////////
// CDynSplitView2 view

class CDynSplitView2 : public CView
{
protected:
	CDynSplitView2();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDynSplitView2)

// Attributes
public:

// Operations
public:
	int number;
	int no;
	Classification *classify;
	BpNet *bpnet;
	void clearmem();
	CDSPLITDoc* GetDocument(); 
	double sp[5];
	double pjp[5];
	double mi;
	CString curDir;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDynSplitView2)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDynSplitView2();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CDynSplitView2)
	afx_msg void OnButtonSave();
	afx_msg void OnBUTTONLMSEifClassified();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMenuIfclassification();
	afx_msg void OnMenuLeastdistance();
	afx_msg void OnMenuFisher();
	afx_msg void OnMenuBayesErzhi();
	afx_msg void OnMenuBayesLeasterror();
	afx_msg void OnMenuBayesLeastrisk();
	afx_msg void OnMenuJiangcheng();
	afx_msg void OnMenuLMSE();
	afx_msg void OnMenuZengliangjiaozheng();
	afx_msg void OnBpTrain();
	afx_msg void OnBpTest();
	afx_msg void OnBpClassify();
	afx_msg void OnMenuBpquanzhi();
	afx_msg void OnMenuShihanshu();
	afx_msg void OnCancelMode();
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DYNSPLITVIEW2_H__106C2C0B_2EEF_4338_83D0_F3AE7B273799__INCLUDED_)
