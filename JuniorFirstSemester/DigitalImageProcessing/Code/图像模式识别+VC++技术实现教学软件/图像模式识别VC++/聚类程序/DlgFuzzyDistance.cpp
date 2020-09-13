// DlgFuzzyDistance.cpp : implementation file
//

#include "stdafx.h"
#include "mode.h"
#include "DlgFuzzyDistance.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgFuzzyDistance dialog


DlgFuzzyDistance::DlgFuzzyDistance(CWnd* pParent /*=NULL*/)
	: CDialog(DlgFuzzyDistance::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgFuzzyDistance)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	mfuzzydistance=1;
}


void DlgFuzzyDistance::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgFuzzyDistance)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgFuzzyDistance, CDialog)
	//{{AFX_MSG_MAP(DlgFuzzyDistance)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_RADIO6, OnRadio6)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgFuzzyDistance message handlers

void DlgFuzzyDistance::OnRadio1() 
{
	mfuzzydistance=1;
	
}

void DlgFuzzyDistance::OnRadio2() 
{
	mfuzzydistance=2;
	
}

void DlgFuzzyDistance::OnRadio3() 
{
	mfuzzydistance=3;
	
}

void DlgFuzzyDistance::OnRadio4() 
{
	mfuzzydistance=4;
	
}

void DlgFuzzyDistance::OnRadio5() 
{
	mfuzzydistance=5;
	
}

void DlgFuzzyDistance::OnRadio6() 
{
	mfuzzydistance=6;
	
}
