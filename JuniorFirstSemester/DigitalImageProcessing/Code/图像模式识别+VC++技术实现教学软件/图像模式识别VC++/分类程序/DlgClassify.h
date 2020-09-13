#if !defined(AFX_DLGCLASSIFY_H__CF7E8A0B_066F_4107_9096_D3B4BEA2B7CF__INCLUDED_)
#define AFX_DLGCLASSIFY_H__CF7E8A0B_066F_4107_9096_D3B4BEA2B7CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgClassify.h : header file
// 2005.1.13гн16г║02 By Superman 

/////////////////////////////////////////////////////////////////////////////
// DlgClassify dialog

class DlgClassify : public CDialog
{
// Construction
public:
	DlgClassify(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgClassify)
	enum { IDD = IDD_DIALOG3 };
	int		m_num1;
	int		m_num2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgClassify)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgClassify)
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCLASSIFY_H__CF7E8A0B_066F_4107_9096_D3B4BEA2B7CF__INCLUDED_)
