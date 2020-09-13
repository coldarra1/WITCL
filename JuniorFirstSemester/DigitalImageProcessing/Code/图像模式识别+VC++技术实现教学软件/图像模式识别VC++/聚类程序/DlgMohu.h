#if !defined(AFX_DLGMOHU_H__352A1F87_B8C8_45BC_A0E1_041C1F6F95AB__INCLUDED_)
#define AFX_DLGMOHU_H__352A1F87_B8C8_45BC_A0E1_041C1F6F95AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMohu.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgMohu dialog

class DlgMohu : public CDialog
{
// Construction
public:
	DlgMohu(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgMohu)
	enum { IDD = IDD_DIALOG_MOHU };
	CString	m_Mohuxishu;
	double	m_Mohuyuzhi;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgMohu)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgMohu)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMOHU_H__352A1F87_B8C8_45BC_A0E1_041C1F6F95AB__INCLUDED_)
