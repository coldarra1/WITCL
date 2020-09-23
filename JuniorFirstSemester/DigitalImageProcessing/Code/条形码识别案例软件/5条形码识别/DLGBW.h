#if !defined(AFX_DLGBW_H__CBC97ADB_EC4D_400B_ADFF_BFDBBA7257D3__INCLUDED_)
#define AFX_DLGBW_H__CBC97ADB_EC4D_400B_ADFF_BFDBBA7257D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DLGBW.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDLGBW dialog

class CDLGBW : public CDialog
{
// Construction
public:
	CDLGBW(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDLGBW)
	enum { IDD = IDD_BW };
	UINT	m_bw;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDLGBW)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDLGBW)
//	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBW_H__CBC97ADB_EC4D_400B_ADFF_BFDBBA7257D3__INCLUDED_)
