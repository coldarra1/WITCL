// DSPLIT.h : main header file for the DSPLIT application
// 2005.1.13гн16г║02 By Superman 

#if !defined(AFX_DSPLIT_H__9AB08760_A5C4_4466_B207_37087A367C58__INCLUDED_)
#define AFX_DSPLIT_H__9AB08760_A5C4_4466_B207_37087A367C58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDSPLITApp:
// See DSPLIT.cpp for the implementation of this class
//

class CDSPLITApp : public CWinApp
{
public:
	CDSPLITApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDSPLITApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDSPLITApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DSPLIT_H__9AB08760_A5C4_4466_B207_37087A367C58__INCLUDED_)
