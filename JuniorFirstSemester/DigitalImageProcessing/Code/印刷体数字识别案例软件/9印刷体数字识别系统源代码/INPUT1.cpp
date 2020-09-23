// INPUT1.cpp : implementation file
//

#include "stdafx.h"
#include "DigitRec.h"
#include "INPUT1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CINPUT1 dialog


CINPUT1::CINPUT1(CWnd* pParent /*=NULL*/)
	: CDialog(CINPUT1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CINPUT1)
	w = 0;
	h = 0;
	//}}AFX_DATA_INIT
}


void CINPUT1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CINPUT1)
	DDX_Text(pDX, IDC_EDIT1, w);
	DDV_MinMaxInt(pDX, w, 4, 128);
	DDX_Text(pDX, IDC_EDIT2, h);
	DDV_MinMaxInt(pDX, h, 4, 64);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CINPUT1, CDialog)
	//{{AFX_MSG_MAP(CINPUT1)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CINPUT1 message handlers
