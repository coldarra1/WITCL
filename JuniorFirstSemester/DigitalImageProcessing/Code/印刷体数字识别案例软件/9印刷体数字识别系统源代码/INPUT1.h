#if !defined(AFX_INPUT1_H__C3A931E6_C8DD_430A_B5A0_E66F355D3F54__INCLUDED_)
#define AFX_INPUT1_H__C3A931E6_C8DD_430A_B5A0_E66F355D3F54__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// INPUT1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CINPUT1 dialog

class CINPUT1 : public CDialog
{
// Construction
public:
	CINPUT1(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CINPUT1)
	enum { IDD = IDD_DIALOG1 };
	int		w;
	int		h;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CINPUT1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CINPUT1)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUT1_H__C3A931E6_C8DD_430A_B5A0_E66F355D3F54__INCLUDED_)
