// recognise_yan.h : main header file for the RECOGNISE_YAN application
//

#if !defined(AFX_RECOGNISE_YAN_H__D8CF6D7E_0A2C_43DE_B896_3B10E19DC4A5__INCLUDED_)
#define AFX_RECOGNISE_YAN_H__D8CF6D7E_0A2C_43DE_B896_3B10E19DC4A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRecognise_yanApp:
// See recognise_yan.cpp for the implementation of this class
//

class CRecognise_yanApp : public CWinApp
{
public:
	CRecognise_yanApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecognise_yanApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CRecognise_yanApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECOGNISE_YAN_H__D8CF6D7E_0A2C_43DE_B896_3B10E19DC4A5__INCLUDED_)
