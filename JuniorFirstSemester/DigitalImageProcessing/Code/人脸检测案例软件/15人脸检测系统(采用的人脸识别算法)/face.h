// face.h : main header file for the FACE application
//

#if !defined(AFX_FACE_H__24CC98A6_32C2_472A_B15E_AEB309B93E28__INCLUDED_)
#define AFX_FACE_H__24CC98A6_32C2_472A_B15E_AEB309B93E28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFaceApp:
// See face.cpp for the implementation of this class
//

class CFaceApp : public CWinApp
{
public:
	CFaceApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFaceApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CFaceApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FACE_H__24CC98A6_32C2_472A_B15E_AEB309B93E28__INCLUDED_)
