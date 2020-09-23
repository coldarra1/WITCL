// DBpParamater.cpp : implementation file
//

#include "stdafx.h"
#include "DigitRec.h"
#include "DBpParamater.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBpParamater dialog


CDBpParamater::CDBpParamater(CWnd* pParent /*=NULL*/)
	: CDialog(CDBpParamater::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDBpParamater)
	m_a = 0.0;
	m_eta = 0.0;
	m_hn = 0;
	m_ex = 0.0;
	//}}AFX_DATA_INIT
}


void CDBpParamater::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDBpParamater)
	DDX_Text(pDX, IDC_a, m_a);
	DDX_Text(pDX, IDC_eta, m_eta);
	DDX_Text(pDX, IDC_n_hidden, m_hn);
	DDX_Text(pDX, IDC_ex, m_ex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDBpParamater, CDialog)
	//{{AFX_MSG_MAP(CDBpParamater)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBpParamater message handlers
