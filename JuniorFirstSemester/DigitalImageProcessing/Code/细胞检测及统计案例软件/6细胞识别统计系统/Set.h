#if !defined(AFX_SET_H__0DC1AA05_4632_4644_AE9D_AA4A642B92AF__INCLUDED_)
#define AFX_SET_H__0DC1AA05_4632_4644_AE9D_AA4A642B92AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Set.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSet dialog

class CSet : public CDialog
{
// Construction
public:
	CSet(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSet)
	enum { IDD = IDD_SET };
	int		m_nPreCount;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSet)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SET_H__0DC1AA05_4632_4644_AE9D_AA4A642B92AF__INCLUDED_)
