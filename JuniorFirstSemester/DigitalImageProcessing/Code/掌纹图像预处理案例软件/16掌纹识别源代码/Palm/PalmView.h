// PalmView.h : interface of the CPalmView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PALMVIEW_H__72163389_EC7F_4A3D_8DA3_1906BF30A7DC__INCLUDED_)
#define AFX_PALMVIEW_H__72163389_EC7F_4A3D_8DA3_1906BF30A7DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <deque>

#include "dibapi.h"
#include <iostream>



using namespace std;
typedef deque<BYTE**> ARRAYLINK;


class CPalmView : public CView
{
protected: // create from serialization only
	CPalmView();
	DECLARE_DYNCREATE(CPalmView)

// Attributes
public:
	CPalmDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPalmView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPalmView();
	int value;
	int corn_v;
	CPoint squrt[4];
	double squrt_k1,squrt_b1,squrt_k2,squrt_b2;
	long cur_x,cur_y;
	ARRAYLINK arraylink;


#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPalmView)
	afx_msg void OnGaosi();
	afx_msg void OnGray();
	afx_msg void OnWaveLet();
	afx_msg void OnReWaveLet();
	afx_msg void OnHarris();
	afx_msg void OnImToBool();
	afx_msg void OnUp();
	afx_msg void Ondown();
	afx_msg void Onleft();
	afx_msg void Onright();
	afx_msg void OnBig();
	afx_msg void OnSmall();
	afx_msg void OnFront();
	afx_msg void OnBack();
	afx_msg void OnAverage();
	afx_msg void OnAlog();
	afx_msg void OnSobelH();
	afx_msg void OnSobelV();
	afx_msg void OnRobertH();
	afx_msg void OnPrewiitH();
	afx_msg void OnIsotropicSobelH();
	afx_msg void OnPalmCur();
	afx_msg void OnPalmROI();
	afx_msg void OnPalmBig();
	afx_msg void OnRoiPro();
	afx_msg void OnROISave();
	afx_msg void OnTotal();
	afx_msg void OnThin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PalmView.cpp
inline CPalmDoc* CPalmView::GetDocument()
   { return (CPalmDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PALMVIEW_H__72163389_EC7F_4A3D_8DA3_1906BF30A7DC__INCLUDED_)
