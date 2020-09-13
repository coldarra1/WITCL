#if !defined(AFX_DLGWEIGHT_H__23BE85D0_0644_434D_A57A_41F79697C74E__INCLUDED_)
#define AFX_DLGWEIGHT_H__23BE85D0_0644_434D_A57A_41F79697C74E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWeight.h : header file
// 2005.1.13гн16г║02 By Superman 

/////////////////////////////////////////////////////////////////////////////
// CDlgWeight dialog

class CDlgWeight : public CDialog
{
// Construction
public:
	double loss[10][10];
	bool b;
	CDlgWeight(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgWeight)
	enum { IDD = IDD_DIALOG5 };
	double	m_00;
	double	m_01;
	double	m_02;
	double	m_03;
	double	m_04;
	double	m_05;
	double	m_06;
	double	m_07;
	double	m_08;
	double	m_09;
	double	m_10;
	double	m_11;
	double	m_12;
	double	m_13;
	double	m_14;
	double	m_15;
	double	m_16;
	double	m_17;
	double	m_18;
	double	m_19;
	double	m_20;
	double	m_21;
	double	m_22;
	double	m_23;
	double	m_24;
	double	m_25;
	double	m_26;
	double	m_27;
	double	m_28;
	double	m_29;
	double	m_30;
	double	m_31;
	double	m_32;
	double	m_33;
	double	m_34;
	double	m_35;
	double	m_36;
	double	m_37;
	double	m_38;
	double	m_39;
	double	m_40;
	double	m_41;
	double	m_42;
	double	m_43;
	double	m_44;
	double	m_45;
	double	m_46;
	double	m_47;
	double	m_48;
	double	m_49;
	double	m_50;
	double	m_51;
	double	m_52;
	double	m_53;
	double	m_54;
	double	m_55;
	double	m_56;
	double	m_57;
	double	m_58;
	double	m_59;
	double	m_60;
	double	m_61;
	double	m_62;
	double	m_63;
	double	m_64;
	double	m_65;
	double	m_66;
	double	m_67;
	double	m_68;
	double	m_69;
	double	m_70;
	double	m_71;
	double	m_72;
	double	m_73;
	double	m_74;
	double	m_75;
	double	m_76;
	double	m_77;
	double	m_78;
	double	m_79;
	double	m_80;
	double	m_81;
	double	m_82;
	double	m_83;
	double	m_84;
	double	m_85;
	double	m_86;
	double	m_87;
	double	m_88;
	double	m_89;
	double	m_90;
	double	m_91;
	double	m_92;
	double	m_93;
	double	m_94;
	double	m_95;
	double	m_96;
	double	m_97;
	double	m_98;
	double	m_99;

	double	m_risk0;
	double	m_risk1;
	double	m_risk2;
	double	m_risk3;
	double	m_risk4;
	double	m_risk5;
	double	m_risk6;
	double	m_risk7;
	double	m_risk8;
	double	m_risk9;

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgWeight)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgWeight)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGWEIGHT_H__23BE85D0_0644_434D_A57A_41F79697C74E__INCLUDED_)
