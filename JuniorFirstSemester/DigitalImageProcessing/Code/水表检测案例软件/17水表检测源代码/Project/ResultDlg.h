#if !defined(AFX_RESULTDLG_H__FBC4A635_EA23_4105_A81B_B9FE7380C0FE__INCLUDED_)
#define AFX_RESULTDLG_H__FBC4A635_EA23_4105_A81B_B9FE7380C0FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResultDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResultDlg dialog

class CResultDlg : public CDialog
{
// Construction
public:
	CResultDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CResultDlg)
	enum { IDD = IDD_RESULT };
	CString	m_X1;
	CString	m_Y1;
	CString	m_X2;
	CString	m_X3;
	CString	m_Y;
	CString	m_X;
	CString	m_Y2;
	CString	m_Y3;
	CString	m_A1;
	CString	m_A2;
	CString	m_A3;
	CString	m_R1;
	CString	m_R2;
	CString	m_R3;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResultDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CResultDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESULTDLG_H__FBC4A635_EA23_4105_A81B_B9FE7380C0FE__INCLUDED_)
