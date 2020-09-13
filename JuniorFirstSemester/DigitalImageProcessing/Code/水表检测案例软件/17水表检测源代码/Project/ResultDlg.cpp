// ResultDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Project.h"
#include "ResultDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResultDlg dialog


CResultDlg::CResultDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CResultDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CResultDlg)
	m_X1 = _T("");
	m_Y1 = _T("");
	m_X2 = _T("");
	m_X3 = _T("");
	m_Y = _T("");
	m_X = _T("");
	m_Y2 = _T("");
	m_Y3 = _T("");
	m_A1 = _T("");
	m_A2 = _T("");
	m_A3 = _T("");
	m_R1 = _T("");
	m_R2 = _T("");
	m_R3 = _T("");
	//}}AFX_DATA_INIT
}


void CResultDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResultDlg)
	DDX_Text(pDX, IDC_EDITX1, m_X1);
	DDX_Text(pDX, IDC_EDITY1, m_Y1);
	DDX_Text(pDX, IDC_EDITX2, m_X2);
	DDX_Text(pDX, IDC_EDITX3, m_X3);
	DDX_Text(pDX, IDC_EDITY, m_Y);
	DDX_Text(pDX, IDC_EDITX, m_X);
	DDX_Text(pDX, IDC_EDITY2, m_Y2);
	DDX_Text(pDX, IDC_EDITY3, m_Y3);
	DDX_Text(pDX, IDC_EDITA1, m_A1);
	DDX_Text(pDX, IDC_EDITA2, m_A2);
	DDX_Text(pDX, IDC_EDITA3, m_A3);
	DDX_Text(pDX, IDC_EDITR1, m_R1);
	DDX_Text(pDX, IDC_EDITR2, m_R2);
	DDX_Text(pDX, IDC_EDITR3, m_R3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResultDlg, CDialog)
	//{{AFX_MSG_MAP(CResultDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResultDlg message handlers
