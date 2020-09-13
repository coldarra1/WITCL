// Set.cpp : implementation file
//

#include "stdafx.h"
#include "cell.h"
#include "Set.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSet dialog


CSet::CSet(CWnd* pParent /*=NULL*/)
	: CDialog(CSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSet)
	m_nPreCount = 3;
	//}}AFX_DATA_INIT
}


void CSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSet)
	DDX_Text(pDX, IDC_PRE_COUNT, m_nPreCount);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSet, CDialog)
	//{{AFX_MSG_MAP(CSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSet message handlers

void CSet::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	if (m_nPreCount<0 || m_nPreCount>20)
	{
		MessageBox("预先腐蚀次数应该在0-20之间");
		return;
	}
	CDialog::OnOK();
}

