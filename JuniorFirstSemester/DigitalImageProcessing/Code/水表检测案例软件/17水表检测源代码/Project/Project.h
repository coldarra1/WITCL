// Project.h : main header file for the PROJECT application
//

#if !defined(AFX_PROJECT_H__6A411418_F145_46D1_AF29_19E33B7A83B0__INCLUDED_)
#define AFX_PROJECT_H__6A411418_F145_46D1_AF29_19E33B7A83B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CProjectApp:
// See Project.cpp for the implementation of this class
//

class CProjectApp : public CWinApp
{
public:
	CProjectApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProjectApp)
	public:
	virtual BOOL InitInstance();
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CProjectApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROJECT_H__6A411418_F145_46D1_AF29_19E33B7A83B0__INCLUDED_)
