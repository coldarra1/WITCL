// test_1.h : main header file for the TEST_1 application
//

#if !defined(AFX_TEST_1_H__2A3AF8D5_6879_43AB_9138_081E6F22393D__INCLUDED_)
#define AFX_TEST_1_H__2A3AF8D5_6879_43AB_9138_081E6F22393D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTest_1App:
// See test_1.cpp for the implementation of this class
//

class CTest_1App : public CWinApp
{
public:
	CTest_1App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTest_1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTest_1App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST_1_H__2A3AF8D5_6879_43AB_9138_081E6F22393D__INCLUDED_)
