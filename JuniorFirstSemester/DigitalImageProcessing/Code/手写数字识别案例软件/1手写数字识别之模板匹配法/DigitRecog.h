// DigitRecog.h : main header file for the DIGITRECOG application
//

#if !defined(AFX_DIGITRECOG_H__ACD7B30F_FED7_410A_A8D2_6A0A5B5CB5DF__INCLUDED_)
#define AFX_DIGITRECOG_H__ACD7B30F_FED7_410A_A8D2_6A0A5B5CB5DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDigitRecogApp:
// See DigitRecog.cpp for the implementation of this class
//

class CDigitRecogApp : public CWinApp
{
public:
	CDigitRecogApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDigitRecogApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDigitRecogApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIGITRECOG_H__ACD7B30F_FED7_410A_A8D2_6A0A5B5CB5DF__INCLUDED_)
