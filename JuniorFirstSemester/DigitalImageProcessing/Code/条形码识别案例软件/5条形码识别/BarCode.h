// BarCode.h : main header file for the BARCODE application
//

#if !defined(AFX_BARCODE_H__65A39745_0B61_41B3_A548_53C9E93C1400__INCLUDED_)
#define AFX_BARCODE_H__65A39745_0B61_41B3_A548_53C9E93C1400__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBarCodeApp:
// See BarCode.cpp for the implementation of this class
//

class CBarCodeApp : public CWinApp
{
public:
	CBarCodeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBarCodeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CBarCodeApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BARCODE_H__65A39745_0B61_41B3_A548_53C9E93C1400__INCLUDED_)
