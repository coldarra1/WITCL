#if !defined(AFX_HSIDLG_H__EB5E251E_C2EC_4711_8F9B_063E8E97700A__INCLUDED_)
#define AFX_HSIDLG_H__EB5E251E_C2EC_4711_8F9B_063E8E97700A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HSIDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHSIDlg dialog

class CHSIDlg : public CDialog
{
// Construction
public:
	RECT SelectedRect;
	CHSIDlg(CWnd* pParent = NULL);   // standard constructor
	CHSIDlg(RECT *pSelectedRect, CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(CHSIDlg)
	enum { IDD = IDD_THRESHOLD_HSI };
	BOOL	m_bEx;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHSIDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHSIDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HSIDLG_H__EB5E251E_C2EC_4711_8F9B_063E8E97700A__INCLUDED_)
