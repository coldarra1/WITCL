#if !defined(AFX_ADDSAMPLEDLG_H__D44E080C_CB44_47AD_A94B_3CDB3647F708__INCLUDED_)
#define AFX_ADDSAMPLEDLG_H__D44E080C_CB44_47AD_A94B_3CDB3647F708__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddSampleDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddSampleDlg dialog

class CAddSampleDlg : public CFileDialog
{
	DECLARE_DYNAMIC(CAddSampleDlg)

public:
	CAddSampleDlg(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);

	int DoModal();
	virtual ~CAddSampleDlg();

protected:
	//{{AFX_MSG(CAddSampleDlg)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	TCHAR* m_pszFile;

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDSAMPLEDLG_H__D44E080C_CB44_47AD_A94B_3CDB3647F708__INCLUDED_)
