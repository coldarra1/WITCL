// ydpd.h : main header file for the YDPD application
//

#if !defined(AFX_YDPD_H__9548E51E_B92C_46F3_AF04_9E34E4C6E6B9__INCLUDED_)
#define AFX_YDPD_H__9548E51E_B92C_46F3_AF04_9E34E4C6E6B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CYdpdApp:
// See ydpd.cpp for the implementation of this class
//

class CYdpdApp : public CWinApp
{
public:
	CYdpdApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CYdpdApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CYdpdApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YDPD_H__9548E51E_B92C_46F3_AF04_9E34E4C6E6B9__INCLUDED_)
