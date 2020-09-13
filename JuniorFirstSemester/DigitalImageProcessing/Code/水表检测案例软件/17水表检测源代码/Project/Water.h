#if !defined(AFX_WATER_H__89CB7B16_2D21_49A8_8F58_5CF6007E6018__INCLUDED_)
#define AFX_WATER_H__89CB7B16_2D21_49A8_8F58_5CF6007E6018__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Water.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWater dialog

class CWater : public CDialog
{
// Construction
public:
	CWater(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWater)
	enum { IDD = IDD_WATER };
	CButton	m_idok;
	int		m_direc;
	int		m_fig1;
	int		m_fig2;
	int		m_fig3;
	int		m_hand1;
	int		m_hand2;
	int		m_hand3;
	int		m_in1r;
	int		m_in1x;
	int		m_in1y;
	int		m_in2r;
	int		m_in2x;
	int		m_in2y;
	int		m_in3r;
	int		m_in3x;
	int		m_in3y;
	int		m_outr;
	int		m_outx;
	int		m_outy;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWater)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWater)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WATER_H__89CB7B16_2D21_49A8_8F58_5CF6007E6018__INCLUDED_)
