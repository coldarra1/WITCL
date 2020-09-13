#if !defined(AFX_DLGTEMPLATE_H__F315D845_820E_4F06_89C3_1780DF7511BC__INCLUDED_)
#define AFX_DLGTEMPLATE_H__F315D845_820E_4F06_89C3_1780DF7511BC__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTemplate.h : header file
// 2005.1.13гн16г║02 By Superman 

#include "Classification.h"	// Added by ClassView
/////////////////////////////////////////////////////////////////////////////
// CDlgTemplate dialog

class CDlgTemplate : public CDialog
{
// Construction
public:
	void OnUpdate();
	pattern pattern[10];
	int select;
	BOOL addnew;
	CString curDir;
	CDlgTemplate(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTemplate)
	enum { IDD = IDD_DIALOG1 };
	CComboBox	m_combo;
	double		m_num0;
	double		m_num1;
	double		m_num10;
	double		m_num11;
	double		m_num12;
	double		m_num13;
	double		m_num14;
	double		m_num15;
	double		m_num16;
	double		m_num17;
	double		m_num18;
	double		m_num19;
	double		m_num2;
	double		m_num20;
	double		m_num21;
	double		m_num22;
	double		m_num23;
	double		m_num24;
	double		m_num3;
	double		m_num4;
	double		m_num6;
	double		m_num5;
	double		m_num7;
	double		m_num8;
	double		m_num9;
	int		m_total;
	int		m_1;
	int		m_0;
	int		m_2;
	int		m_3;
	int		m_4;
	int		m_5;
	int		m_6;
	int		m_7;
	int		m_8;
	int		m_9;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTemplate)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTemplate)
	virtual void OnOK();
	afx_msg void OnButtonAddnew();
	afx_msg void OnButtonSave();
	afx_msg void OnButtonUpdate();
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonPrior();
	afx_msg void OnButtonNext();
	virtual BOOL OnInitDialog();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	afx_msg void OnRadio6();
	afx_msg void OnRadio7();
	afx_msg void OnRadio8();
	afx_msg void OnRadio9();
	afx_msg void OnRadio10();
	afx_msg void OnCloseupCombo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTEMPLATE_H__F315D845_820E_4F06_89C3_1780DF7511BC__INCLUDED_)
