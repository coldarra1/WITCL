// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Project.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
	ID_INDICATOR_TIME,
	ID_INDICATOR_X,
	ID_INDICATOR_Y,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	SetTimer(1,1000,NULL);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	UINT id = m_wndStatusBar.CommandToIndex(ID_INDICATOR_TIME);
	CString csCurrentTime;
	CTime t = CTime::GetCurrentTime();
	csCurrentTime = t.Format("%H:%M:%S");

	if (csCurrentTime[0] == '0')
		csCurrentTime.SetAt(0,' ');
	m_wndStatusBar.SetPaneText(id, csCurrentTime, TRUE);

	CMDIFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::SetStatus(CString str)
{
	// status line indicator
	UINT id = m_wndStatusBar.CommandToIndex(ID_SEPARATOR);
	//
	//m_wndStatusBar.GetStatusBarCtrl().SetTipText(id, str);
	m_wndStatusBar.SetPaneText(id,str,TRUE);
};

void CMainFrame::SetStatusX(CString str)
{
	// status line indicator
	CString str1;
	UINT id = m_wndStatusBar.CommandToIndex(ID_INDICATOR_X);
	//
	//m_wndStatusBar.GetStatusBarCtrl().SetTipText(id, str);
	str1 = "x=";
	str1 += str;
	m_wndStatusBar.SetPaneText(id,str1,TRUE);
};

void CMainFrame::SetStatusY(CString str)
{
	// status line indicator
	CString str1;
	UINT id = m_wndStatusBar.CommandToIndex(ID_INDICATOR_Y);
	//
	//m_wndStatusBar.GetStatusBarCtrl().SetTipText(id, str);
	str1 = "y=";
	str1 += str;
	m_wndStatusBar.SetPaneText(id,str1,TRUE);
};
