#if !defined(AFX_WAVELET_H__B15ABAEB_9958_4CE4_BB4C_52B934519B44__INCLUDED_)
#define AFX_WAVELET_H__B15ABAEB_9958_4CE4_BB4C_52B934519B44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Wavelet.h : header file
//
#include "CDib.h"

/////////////////////////////////////////////////////////////////////////////
// CWavelet dialog

class CWavelet : public CDialog
{
// Construction
public:
	CWavelet(CWnd* pParent = NULL);   // standard constructor
    CDib m_dib;
    long int Height,Width,m_bytewidth;
	BYTE  *m_pdata;//DIB图像数据指针
   	double *pDatewavelet;
    //小波变换
	void WaveletTran(CDib m_dib,double *Source,int level,long int Height,long int Width,long int m_bytewidth);
	void WaveRecstr(double*pDatewavelet,int level);

// Dialog Data
	//{{AFX_DATA(CWavelet)
	enum { IDD = IDD_DIALOG1 };
	int		m_level;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWavelet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWavelet)
	afx_msg void Onopenimg();
	afx_msg void Onwaveletfj();
	afx_msg void Onwaveletcg();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAVELET_H__B15ABAEB_9958_4CE4_BB4C_52B934519B44__INCLUDED_)
