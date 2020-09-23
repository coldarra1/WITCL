// DigitRecogDlg.h : header file
//

#if !defined(AFX_DIGITRECOGDLG_H__0F3395B1_6BD6_40F9_8520_22C16616EDFC__INCLUDED_)
#define AFX_DIGITRECOGDLG_H__0F3395B1_6BD6_40F9_8520_22C16616EDFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DigitClass.h"

/////////////////////////////////////////////////////////////////////////////
// CDigitRecogDlg dialog

class CDigitRecogDlg : public CDialog
{
// Construction
public:
	CDigitRecogDlg(CWnd* pParent = NULL);	// standard constructor
	CDigitClass digitTrain;
	CDigitClass digitTest;
	CDC * pDCTest; //测试
	CDC * pDCOrig; //模板
	CEdit *pEditResult; //显示结果
	CStringArray arTrainSetFilePath;	//训练样本集的文件路径，不过它只有一个变量
	CStringArray arTestSetFilePath;	//测试样本集的文件路径
	int iCurTrainNum,iTotalTrainNum;
	int iCurTestNum,iTotalTestNum;
	Sample digitTemplate[10];

// Dialog Data
	//{{AFX_DATA(CDigitRecogDlg)
	enum { IDD = IDD_DIGITRECOG_DIALOG };
	int		m_nDigitTemp;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDigitRecogDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDigitRecogDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonInputTest();
	afx_msg void OnButtonInputTrain();
	afx_msg void OnButtonNext();
	afx_msg void OnButtonPrev();
	afx_msg void OnButtonRecog();
	afx_msg void OnButtonTemplate();
	afx_msg void OnButtonSaveTemplate();
	afx_msg void OnButtonOpenTemplate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIGITRECOGDLG_H__0F3395B1_6BD6_40F9_8520_22C16616EDFC__INCLUDED_)
