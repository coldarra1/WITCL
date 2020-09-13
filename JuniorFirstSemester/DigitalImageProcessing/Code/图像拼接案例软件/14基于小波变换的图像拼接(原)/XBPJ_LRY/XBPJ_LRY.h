// XBPJ_LRY.h : main header file for the XBPJ_LRY application
//

#if !defined(AFX_XBPJ_LRY_H__E8F1DD11_B29C_40CF_A44A_16F558A1D2AE__INCLUDED_)
#define AFX_XBPJ_LRY_H__E8F1DD11_B29C_40CF_A44A_16F558A1D2AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CXBPJ_LRYApp:
// See XBPJ_LRY.cpp for the implementation of this class
//

class CXBPJ_LRYApp : public CWinApp
{
public:
	CXBPJ_LRYApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXBPJ_LRYApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CXBPJ_LRYApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XBPJ_LRY_H__E8F1DD11_B29C_40CF_A44A_16F558A1D2AE__INCLUDED_)
