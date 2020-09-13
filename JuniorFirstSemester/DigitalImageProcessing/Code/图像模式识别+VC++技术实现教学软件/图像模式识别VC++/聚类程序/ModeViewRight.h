#if !defined(AFX_MODEVIEWRIGHT_H__7257FF8C_65D4_4F26_B131_16ACEFAC1F84__INCLUDED_)
#define AFX_MODEVIEWRIGHT_H__7257FF8C_65D4_4F26_B131_16ACEFAC1F84__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModeViewRight.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CModeViewRight view
#include "YIchuansuanfa.h"

#include "modeDoc.h"
#include "CDib.h"
#include "Cluster.h"

class CModeViewRight : public CView
{
protected:
	CModeViewRight();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CModeViewRight)

// Attributes
public:

	CPalette hPalette;

	CCluster	*pCluster;
	YIchuansuanfa ga;
	bool		stateDoc;//关联文档状态。ture＝关联	

// Operations
public:
	void GetData();
	
	CPalette *CreateBitmapPalette( CCluster* pCluster);

		
		
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModeViewRight)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CModeViewRight();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CModeViewRight)
	afx_msg void OnShowright();
	afx_msg void OnGetfeature();
	afx_msg void OnZhongjinajulifa();
	afx_msg void OnZhongxinfa();
	afx_msg void OnZuichangjulifa();
	afx_msg void OnZuidazuixiaojuli();
	afx_msg void OnZuiduanjulifa();
	afx_msg void OnZuilinjinguize();
	afx_msg void OnLeipingjunjulifa();
	afx_msg void OnKjunzhi();
	afx_msg void OnIsodata();
	afx_msg void OnGa();
	afx_msg void OnFuzzycluster();
	afx_msg void OnFileSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODEVIEWRIGHT_H__7257FF8C_65D4_4F26_B131_16ACEFAC1F84__INCLUDED_)
