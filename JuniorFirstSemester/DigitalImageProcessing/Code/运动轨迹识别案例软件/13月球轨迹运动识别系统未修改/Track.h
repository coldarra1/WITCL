#if !defined(AFX_TRACK_H__8BD62390_DE4B_4555_8905_8A67ABF41F55__INCLUDED_)
#define AFX_TRACK_H__8BD62390_DE4B_4555_8905_8A67ABF41F55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Track.h : header file
//
//#include "ydpdview.h"
#include "ydgj.h"
/////////////////////////////////////////////////////////////////////////////
// Track dialog

class Track : public CDialog
{
// Construction
public:
	int m_mapwidth;
	int m_mapheight;
	GUIJI m_YDGJ;
	Track(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Track)
	enum { IDD = IDD_DIALOG_GUIJI };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Track)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Track)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRACK_H__8BD62390_DE4B_4555_8905_8A67ABF41F55__INCLUDED_)
