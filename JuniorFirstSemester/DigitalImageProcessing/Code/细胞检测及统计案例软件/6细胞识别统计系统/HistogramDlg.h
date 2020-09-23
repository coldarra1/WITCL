#if !defined(AFX_HISTOGRAMDLG_H__77409AF7_7EFF_40AA_8EC2_D685336A0732__INCLUDED_)
#define AFX_HISTOGRAMDLG_H__77409AF7_7EFF_40AA_8EC2_D685336A0732__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HistogramDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHistogramDlg dialog

class CHistogramDlg : public CDialog
{
// Construction
public:
	double	ratior, ratiog, ratiob;
	bool	m_bUserRatio;
	RECT	m_ChartRect;
	void	DrawData(CDC *dc, char type);
	void	DrawFrame(CDC *dc, char type);
	DWORD	m_Histogram[3][256];
	void	GenHistogramData(void);
	CHistogramDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHistogramDlg)
	enum { IDD = IDD_HISTOGRAM };
	int m_Thresh_B;
	int m_Thresh_G;
	int m_Thresh_R;
	int m_Thresh_BMax;
	int m_Thresh_GMax;
	int m_Thresh_RMax;
	int m_nMag;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHistogramDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CHistogramDlg)
	virtual BOOL	OnInitDialog(void);
	afx_msg void	OnPaint(void);
	afx_msg void	OnRed(void);
	afx_msg void	OnGreen(void);
	afx_msg void	OnBlue(void);
	afx_msg void	OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void	OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void	OnExclusivePressed(void);
	virtual void	OnOK(void);
	afx_msg void	OnHistogramSame(void);
	afx_msg void	OnChangeHistogramMagnify(void);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_HISTOGRAMDLG_H__77409AF7_7EFF_40AA_8EC2_D685336A0732__INCLUDED_)
