// WaterM.cpp : implementation file
//

#include "stdafx.h"
#include "Project.h"
#include "WaterM.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWaterM dialog


CWaterM::CWaterM(CWnd* pParent /*=NULL*/)
	: CDialog(CWaterM::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWaterM)
	m_direc = 0;
	m_fig1 = 0;
	m_fig2 = 0;
	m_fig3 = 0;
	m_hand1 = 0;
	m_hand2 = 0;
	m_hand3 = 0;
	m_in1r = 0;
	m_in1x = 0;
	m_in1y = 0;
	m_in2r = 0;
	m_in2x = 0;
	m_in2y = 0;
	m_in3r = 0;
	m_in3x = 0;
	m_in3y = 0;
	m_outr = 0;
	m_outx = 0;
	m_outy = 0;
	//}}AFX_DATA_INIT
}


void CWaterM::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWaterM)
	DDX_Text(pDX, IDC_DIREC, m_direc);
	DDX_Text(pDX, IDC_FIG1, m_fig1);
	DDX_Text(pDX, IDC_FIG2, m_fig2);
	DDX_Text(pDX, IDC_FIG3, m_fig3);
	DDX_Text(pDX, IDC_HAND1, m_hand1);
	DDX_Text(pDX, IDC_HAND2, m_hand2);
	DDX_Text(pDX, IDC_HAND3, m_hand3);
	DDX_Text(pDX, IDC_IN1R, m_in1r);
	DDX_Text(pDX, IDC_IN1X, m_in1x);
	DDX_Text(pDX, IDC_IN1Y, m_in1y);
	DDX_Text(pDX, IDC_IN2R, m_in2r);
	DDX_Text(pDX, IDC_IN2X, m_in2x);
	DDX_Text(pDX, IDC_IN2Y, m_in2y);
	DDX_Text(pDX, IDC_IN3R, m_in3r);
	DDX_Text(pDX, IDC_IN3X, m_in3x);
	DDX_Text(pDX, IDC_IN3Y, m_in3y);
	DDX_Text(pDX, IDC_OUTR, m_outr);
	DDX_Text(pDX, IDC_OUTX, m_outx);
	DDX_Text(pDX, IDC_OUTY, m_outy);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWaterM, CDialog)
	//{{AFX_MSG_MAP(CWaterM)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWaterM message handlers
