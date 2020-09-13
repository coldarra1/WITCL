// DlgClassify.cpp : implementation file
// 2005.1.13гн16г║02 By Superman 

#include "stdafx.h"
#include "DSPLIT.h"
#include "DlgClassify.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgClassify dialog


DlgClassify::DlgClassify(CWnd* pParent /*=NULL*/)
	: CDialog(DlgClassify::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgClassify)
	m_num1 = 0;
	m_num2 = 0;
	//}}AFX_DATA_INIT
}


void DlgClassify::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgClassify)
	DDX_Text(pDX, IDC_EDIT1, m_num1);
	DDV_MinMaxInt(pDX, m_num1, 0, 9);
	DDX_Text(pDX, IDC_EDIT2, m_num2);
	DDV_MinMaxInt(pDX, m_num2, 0, 9);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgClassify, CDialog)
	//{{AFX_MSG_MAP(DlgClassify)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgClassify message handlers



void DlgClassify::OnButton1() 
{
	m_num1--;
	if (m_num1<0)
		m_num1=9;
	UpdateData(FALSE);
}

void DlgClassify::OnButton2() 
{
	m_num1++;
	if(m_num1>9)
		m_num1=0;
	UpdateData(FALSE);	
}

void DlgClassify::OnButton3() 
{
	m_num2--;
	if (m_num2<0)
		m_num2=9;
	UpdateData(FALSE);	
}

void DlgClassify::OnButton4() 
{
	m_num2++;
	if(m_num2>9)
		m_num2=0;
	UpdateData(FALSE);	
}
