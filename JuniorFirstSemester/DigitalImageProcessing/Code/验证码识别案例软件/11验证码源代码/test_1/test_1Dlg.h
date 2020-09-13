// test_1Dlg.h : header file
//

#if !defined(AFX_TEST_1DLG_H__805365D8_9C02_4E0D_88F9_A05152F86679__INCLUDED_)
#define AFX_TEST_1DLG_H__805365D8_9C02_4E0D_88F9_A05152F86679__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTest_1Dlg dialog

class CTest_1Dlg : public CDialog
{
// Construction
public:
	int InitBmp();
	CTest_1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTest_1Dlg)
	enum { IDD = IDD_TEST_1_DIALOG };
	CString	m_result;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTest_1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTest_1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRead();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST_1DLG_H__805365D8_9C02_4E0D_88F9_A05152F86679__INCLUDED_)
