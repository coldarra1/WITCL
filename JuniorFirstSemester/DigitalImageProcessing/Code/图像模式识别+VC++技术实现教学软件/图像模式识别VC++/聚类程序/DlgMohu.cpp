// DlgMohu.cpp : implementation file
//

#include "stdafx.h"
#include "mode.h"
#include "DlgMohu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgMohu dialog


DlgMohu::DlgMohu(CWnd* pParent /*=NULL*/)
	: CDialog(DlgMohu::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgMohu)
	m_Mohuxishu = _T("");
	m_Mohuyuzhi = 0.0;
	//}}AFX_DATA_INIT
}


void DlgMohu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgMohu)
	DDX_Text(pDX, IDC_EDIT_MOHUXISHU, m_Mohuxishu);
	DDX_Text(pDX, IDC_EDIT_MOHUYUZHI, m_Mohuyuzhi);
	DDV_MinMaxDouble(pDX, m_Mohuyuzhi, 0., 1.);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgMohu, CDialog)
	//{{AFX_MSG_MAP(DlgMohu)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgMohu message handlers
