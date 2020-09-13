// mode.h : main header file for the MODE application
//

#if !defined(AFX_MODE_H__4B3FABC0_C3FB_42A1_9F29_44DF003D08F3__INCLUDED_)
#define AFX_MODE_H__4B3FABC0_C3FB_42A1_9F29_44DF003D08F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CModeApp:
// See mode.cpp for the implementation of this class
//

class CModeApp : public CWinApp
{
public:
	CModeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CModeApp)
	afx_msg void OnAppAbout();
	afx_msg void OnUseguide();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODE_H__4B3FABC0_C3FB_42A1_9F29_44DF003D08F3__INCLUDED_)
