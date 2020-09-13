#if !defined(AFX_DLGINFOR_H__C580E199_A377_4989_93D4_308F6E532546__INCLUDED_)
#define AFX_DLGINFOR_H__C580E199_A377_4989_93D4_308F6E532546__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInfor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgInfor dialog

class DlgInfor : public CDialog
{
// Construction
public:
	int m_ShowType;//1:K均值调用，只显示IDC_EDIT_CENTERNUM;2:只显示IDC_EDIT_T;3:全部显示
	void ShowInfor(double minous, double maxous,double mincos,double maxcos,double minbcos,double maxbcox,double mintan,double maxtan, double minequation,double maxequation);
	void ShowInfor(double minous, double maxous,double mincos,double maxcos,double minbcos,double maxbcox,double mintan,double maxtan);
	void ShowInfor(int i);//i can onle be 1 or 4;
	int m_DisType;
	double mminous,mmaxous,mmincos,mmaxcos,mminbcos,mmaxbcos,mmintan,mmaxtan;
	DlgInfor(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgInfor)
	enum { IDD = IDD_DIALOG_INFOR };
	double	m_T;
	int		m_CenterNum;
	double	m_EquationIn;
	int		m_Times;
	double	m_MinDis;
	double	m_MaxDis;
	double	m_EquationOut;
	double	m_MinEquationOut;
	double	m_MaxEquationOut;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgInfor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgInfor)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioBcos();
	afx_msg void OnRadioCos();
	afx_msg void OnRadioOus();
	afx_msg void OnRadioTan();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINFOR_H__C580E199_A377_4989_93D4_308F6E532546__INCLUDED_)
