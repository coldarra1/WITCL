#if !defined(AFX_DLGNUMBER_H__2A842C21_403D_488E_9E42_9E1BA20AD98A__INCLUDED_)
#define AFX_DLGNUMBER_H__2A842C21_403D_488E_9E42_9E1BA20AD98A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgNumber.h : header file
// 2005.1.13гн16г║02 By Superman 

/////////////////////////////////////////////////////////////////////////////
// CDlgNumber dialog

class CDlgNumber : public CDialog
{
// Construction
public:
	CDlgNumber(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgNumber)
	enum { IDD = IDD_DIALOG2 };
	int		m_num;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNumber)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgNumber)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNUMBER_H__2A842C21_403D_488E_9E42_9E1BA20AD98A__INCLUDED_)
