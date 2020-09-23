// DLGBW.cpp : implementation file
//

#include "stdafx.h"
#include "BarCode.h"
#include "DLGBW.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDLGBW dialog


CDLGBW::CDLGBW(CWnd* pParent /*=NULL*/)
	: CDialog(CDLGBW::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDLGBW)
	m_bw = 0;
	//}}AFX_DATA_INIT
}


void CDLGBW::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDLGBW)
	DDX_Text(pDX, IDC_BW, m_bw);
	DDV_MinMaxUInt(pDX, m_bw, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDLGBW, CDialog)
	//{{AFX_MSG_MAP(CDLGBW)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLGBW message handlers

//BOOL CDLGBW::OnInitDialog() 
//{
//	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
//	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
//}
