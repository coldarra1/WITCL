// FaceDetection.h : main header file for the FACEDETECTION application
//

#if !defined(AFX_FACEDETECTION_H__69483FEB_EBAB_4E9D_A22D_88FAC3A6993C__INCLUDED_)
#define AFX_FACEDETECTION_H__69483FEB_EBAB_4E9D_A22D_88FAC3A6993C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFaceDetectionApp:
// See FaceDetection.cpp for the implementation of this class
//

class CFaceDetectionApp : public CWinApp
{
public:
	CFaceDetectionApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFaceDetectionApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CFaceDetectionApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FACEDETECTION_H__69483FEB_EBAB_4E9D_A22D_88FAC3A6993C__INCLUDED_)
