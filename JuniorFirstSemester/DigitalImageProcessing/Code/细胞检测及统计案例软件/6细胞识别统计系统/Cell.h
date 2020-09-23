// Cell.h : main header file for the CELL application
//

#if !defined(AFX_CELL_H__AE373C3D_CA2F_4FB3_A3D9_E3CB50204329__INCLUDED_)
#define AFX_CELL_H__AE373C3D_CA2F_4FB3_A3D9_E3CB50204329__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCellApp:
// See Cell.cpp for the implementation of this class
//

class CCellApp : public CWinApp
{
public:
	CCellApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCellApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCellApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////


/////////////////////////////
// extern global
extern CCellApp		theApp;
extern HBITMAP		g_hBitmap;
// CHSIDlg dialog
extern int			g_nIntGap;
extern int			g_nSatGap;
extern int			g_nHueGap;

#define INDEX(i,j) j*g_nMapWidth+i

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CELL_H__AE373C3D_CA2F_4FB3_A3D9_E3CB50204329__INCLUDED_)
