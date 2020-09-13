#if !defined(AFX_DLGDISPLAY_H__C0565635_EBAD_482D_B079_FE9FEB37D1D6__INCLUDED_)
#define AFX_DLGDISPLAY_H__C0565635_EBAD_482D_B079_FE9FEB37D1D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlgdisplay.h : header file
// 2005.1.13гн16г║02 By Superman 

/////////////////////////////////////////////////////////////////////////////
// CDlgdisplay dialog

class CDlgdisplay : public CDialog
{
// Construction
public:
	CDlgdisplay(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgdisplay)
	enum { IDD = IDD_DIALOG4 };
	CString	m_str;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgdisplay)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgdisplay)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDISPLAY_H__C0565635_EBAD_482D_B079_FE9FEB37D1D6__INCLUDED_)
