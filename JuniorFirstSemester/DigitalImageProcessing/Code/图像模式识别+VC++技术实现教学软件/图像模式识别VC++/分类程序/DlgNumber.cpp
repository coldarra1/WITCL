// DlgNumber.cpp : implementation file
// 2005.1.13гн16г║02 By Superman 

#include "stdafx.h"
#include "DSPLIT.h"
#include "DlgNumber.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNumber dialog


CDlgNumber::CDlgNumber(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNumber::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNumber)
	m_num = 0;
	//}}AFX_DATA_INIT
}


void CDlgNumber::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNumber)
	DDX_Text(pDX, IDC_EDIT1, m_num);
	DDV_MinMaxInt(pDX, m_num, 0, 99);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNumber, CDialog)
	//{{AFX_MSG_MAP(CDlgNumber)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNumber message handlers
