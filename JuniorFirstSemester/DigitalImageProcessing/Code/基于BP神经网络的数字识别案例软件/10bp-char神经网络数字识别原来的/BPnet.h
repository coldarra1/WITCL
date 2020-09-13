// BPnet.h : main header file for the BPNET application
//

#if !defined(AFX_BPNET_H__0EEE1D57_C5C3_4B03_B432_5882AD9ADAD0__INCLUDED_)
#define AFX_BPNET_H__0EEE1D57_C5C3_4B03_B432_5882AD9ADAD0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBPnetApp:
// See BPnet.cpp for the implementation of this class
//

class CBPnetApp : public CWinApp
{
public:
	CBPnetApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBPnetApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CBPnetApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BPNET_H__0EEE1D57_C5C3_4B03_B432_5882AD9ADAD0__INCLUDED_)
