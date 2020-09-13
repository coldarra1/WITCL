// Palm.h : main header file for the PALM application
//

#if !defined(AFX_PALM_H__22291074_FA16_4B82_AE3A_AF78FEAC4ACF__INCLUDED_)
#define AFX_PALM_H__22291074_FA16_4B82_AE3A_AF78FEAC4ACF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPalmApp:
// See Palm.cpp for the implementation of this class
//

class CPalmApp : public CWinApp
{
public:
	CPalmApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPalmApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CPalmApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PALM_H__22291074_FA16_4B82_AE3A_AF78FEAC4ACF__INCLUDED_)
