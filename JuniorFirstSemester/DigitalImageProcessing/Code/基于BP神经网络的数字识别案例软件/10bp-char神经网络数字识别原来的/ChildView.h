// ChildView.h : interface of the CChildView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDVIEW_H__B4322D71_1449_4F00_B1A2_5CCD873AE4C5__INCLUDED_)
#define AFX_CHILDVIEW_H__B4322D71_1449_4F00_B1A2_5CCD873AE4C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include"pred.h"

/////////////////////////////////////////////////////////////////////////////
// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildView)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
private:
    enum {r=N_P};//输入数据是8维的
	enum {s1=N_Layer1};//隐层有7个神经元
	enum {s2=N_Out};//输出层有4个神经元
public:
	DrawPoint(CPoint point,int gray,int area);
	void DrawNumber(double p[],CPoint pcenter);
	CRect rect;
	CString strt;//训练所用时间
	CString stre;//最终误差
	double* dW1;
	double* dW2;
	double* dB1;
	double* dB2;
	double* T;//当前输入样本的期望输出的指针
	double* E;
	double* f1(double A[],int m);//对列向量进行函数运算，并返回一个列向量
	double* f2(double A[],int m);
	double* F1(double N[],int m);
	double* F2(double N[],int m);
	double* B2;
	double* B1;
	double* S2;
	double* S1;
	double* A2;
	double* N2;
	double* W2;
	double* A1;
	double* N1;
	double* W1;
	double W1_init[s1*r];
	double W2_init[s2*s1];
	double B1_init[s1];
	double B2_init[s2];
	double W1_final[s1*r];
	double W2_final[s2*s1];
	double B1_final[s1];
	double B2_final[s2];
	double* P;//当前输入样本的指针
	int TargetTest(double A[]);//返回T代表的数字，为0到9
	long int learncount;   //最终学习次数
	//double* P_samples[10];
	//double* T_output[10];
	virtual ~CChildView();
	void initwb();
	void savewb();
	void loadwb();
	// Generated message map functions
protected:
	//{{AFX_MSG(CChildView)
	afx_msg void OnPaint();
	afx_msg void OnMatrixT();
	afx_msg void OnBpnTrain();
	afx_msg void OnDrawError();
	afx_msg void OnPrewb();
	afx_msg void OnDispSamples();
	afx_msg void OnBpnRun();
	afx_msg void OnBPNVerify();
	afx_msg void OnBPTRAINOptimal1();
	afx_msg void OnSaveerror();
	afx_msg void OnSaveweight();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDVIEW_H__B4322D71_1449_4F00_B1A2_5CCD873AE4C5__INCLUDED_)
