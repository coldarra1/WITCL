// Dlgdisplay.cpp : implementation file
// 2005.1.13гн16г║02 By Superman 

#include "stdafx.h"
#include "DSPLIT.h"
#include "Dlgdisplay.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgdisplay dialog


CDlgdisplay::CDlgdisplay(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgdisplay::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgdisplay)
	m_str = _T("");
	//}}AFX_DATA_INIT
}


void CDlgdisplay::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgdisplay)
	DDX_Text(pDX, IDC_EDIT1, m_str);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgdisplay, CDialog)
	//{{AFX_MSG_MAP(CDlgdisplay)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgdisplay message handlers
