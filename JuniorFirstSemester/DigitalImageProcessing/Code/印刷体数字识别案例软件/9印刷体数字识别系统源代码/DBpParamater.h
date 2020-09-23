#if !defined(AFX_DBPPARAMATER_H__19AC59FE_976C_4187_9F25_1C1197E7FA4C__INCLUDED_)
#define AFX_DBPPARAMATER_H__19AC59FE_976C_4187_9F25_1C1197E7FA4C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBpParamater.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDBpParamater dialog

class CDBpParamater : public CDialog
{
// Construction
public:
	CDBpParamater(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDBpParamater)
	enum { IDD = IDD_DIALOG2 };
	double	m_a;
	double	m_eta;
	int		m_hn;
	double	m_ex;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBpParamater)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDBpParamater)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBPPARAMATER_H__19AC59FE_976C_4187_9F25_1C1197E7FA4C__INCLUDED_)
