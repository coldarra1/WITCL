#if !defined(AFX_DLGFUZZYDISTANCE_H__CAA89C81_1C70_4216_9E7D_661D672F2BA3__INCLUDED_)
#define AFX_DLGFUZZYDISTANCE_H__CAA89C81_1C70_4216_9E7D_661D672F2BA3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFuzzyDistance.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgFuzzyDistance dialog

class DlgFuzzyDistance : public CDialog
{
// Construction
public:
	int mfuzzydistance;
	DlgFuzzyDistance(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgFuzzyDistance)
	enum { IDD = IDD_FUZZYDIATANCE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgFuzzyDistance)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgFuzzyDistance)
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	afx_msg void OnRadio6();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFUZZYDISTANCE_H__CAA89C81_1C70_4216_9E7D_661D672F2BA3__INCLUDED_)
