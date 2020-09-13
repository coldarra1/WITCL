// DlgDisType.cpp : implementation file
//

#include "stdafx.h"
#include "mode.h"
#include "DlgDisType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDisType dialog


CDlgDisType::CDlgDisType(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDisType::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDisType)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgDisType::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDisType)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDisType, CDialog)
	//{{AFX_MSG_MAP(CDlgDisType)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDisType message handlers
/////////////////////////////////////////////////////////////////////////////
// CDlgDisType dialog


CDlgDisType::CDlgDisType(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDisType::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDisType)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgDisType::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDisType)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDisType, CDialog)
	//{{AFX_MSG_MAP(CDlgDisType)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDisType message handlers
/////////////////////////////////////////////////////////////////////////////
// CDlgDisType dialog


CDlgDisType::CDlgDisType(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDisType::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDisType)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgDisType::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDisType)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDisType, CDialog)
	//{{AFX_MSG_MAP(CDlgDisType)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDisType message handlers
/////////////////////////////////////////////////////////////////////////////
// CDlgDisType dialog


CDlgDisType::CDlgDisType(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDisType::IDD, pParent)
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgDisType)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgDisType::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialog::OnFinalRelease();
}

void CDlgDisType::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDisType)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDisType, CDialog)
	//{{AFX_MSG_MAP(CDlgDisType)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgDisType, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgDisType)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IDlgDisType to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {1B32C53D-8436-4A2E-BDC7-995A455DDE7A}
static const IID IID_IDlgDisType =
{ 0x1b32c53d, 0x8436, 0x4a2e, { 0xbd, 0xc7, 0x99, 0x5a, 0x45, 0x5d, 0xde, 0x7a } };

BEGIN_INTERFACE_MAP(CDlgDisType, CDialog)
	INTERFACE_PART(CDlgDisType, IID_IDlgDisType, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDisType message handlers
/////////////////////////////////////////////////////////////////////////////
// DlgDisType dialog


DlgDisType::DlgDisType(CWnd* pParent /*=NULL*/)
	: CDialog(DlgDisType::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgDisType)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DlgDisType::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgDisType)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgDisType, CDialog)
	//{{AFX_MSG_MAP(DlgDisType)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgDisType message handlers
/////////////////////////////////////////////////////////////////////////////
// CDlgDisType dialog


CDlgDisType::CDlgDisType(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDisType::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDisType)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgDisType::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDisType)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDisType, CDialog)
	//{{AFX_MSG_MAP(CDlgDisType)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDisType message handlers
/////////////////////////////////////////////////////////////////////////////
// CDlgDisType dialog


CDlgDisType::CDlgDisType(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDisType::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDisType)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgDisType::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDisType)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDisType, CDialog)
	//{{AFX_MSG_MAP(CDlgDisType)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDisType message handlers
