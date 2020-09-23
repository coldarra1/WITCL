// DlgInfor.cpp : implementation file
//

#include "stdafx.h"
#include "mode.h"
#include "DlgInfor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgInfor dialog


DlgInfor::DlgInfor(CWnd* pParent /*=NULL*/)
	: CDialog(DlgInfor::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgInfor)
	m_T = 0.0;
	m_CenterNum = 0;
	m_EquationIn = 0.0;
	m_Times = 0;
	m_MinDis = 0.0;
	m_MaxDis = 0.0;
	m_EquationOut = 0.0;
	m_DisType=1;
	m_MinEquationOut = 0.0;
	m_MaxEquationOut = 0.0;
	//}}AFX_DATA_INIT
	m_ShowType=0;
	mmaxbcos=0;
	mmaxcos=0;
	mmaxous=0;
	mmaxtan=0;
	mminbcos=0;
	mmincos=0;
	mminous=0;
	mmintan=0;
}


void DlgInfor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgInfor)
	DDX_Text(pDX, IDC_EDIT_T, m_T);
	DDX_Text(pDX, IDC_EDIT_CENTERNUM, m_CenterNum);
	DDX_Text(pDX, IDC_EDIT_EQUATIONIN, m_EquationIn);
	DDX_Text(pDX, IDC_EDIT_TIMES, m_Times);
	DDX_Text(pDX, IDC_EDIT_MINDIS, m_MinDis);
	DDX_Text(pDX, IDC_EDIT_MAXDIS, m_MaxDis);
	DDX_Text(pDX, IDC_EDIT_MINEQUATIONOUT, m_MinEquationOut);
	DDX_Text(pDX, IDC_EDIT_MAXEQUATIONOUT, m_MaxEquationOut);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgInfor, CDialog)
	//{{AFX_MSG_MAP(DlgInfor)
	ON_BN_CLICKED(IDC_RADIO_BCOS, OnRadioBcos)
	ON_BN_CLICKED(IDC_RADIO_COS, OnRadioCos)
	ON_BN_CLICKED(IDC_RADIO_OUS, OnRadioOus)
	ON_BN_CLICKED(IDC_RADIO_TAN, OnRadioTan)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgInfor message handlers



void DlgInfor::ShowInfor(int i)//K均值2 and 最大最小距离1
{
	if(i==1 || i==4)
	m_ShowType=i;
}

void DlgInfor::ShowInfor(double minous, double maxous,double mincos,double maxcos,double minbcos,double maxbcos,double mintan,double maxtan)//需要用户输入阈值的
{
	mminous=minous;
	mmaxous=maxous;
	mmincos=mincos;
	mmaxcos=maxcos;
	mminbcos=minbcos;
	mmaxbcos=maxbcos;
	mmintan=mintan;
	mmaxtan=maxtan;
//	UpdateData(false);//加上此句出错！！
	m_ShowType=2;	

}

void DlgInfor::ShowInfor(double minous, double maxous,double mincos,double maxcos,double minbcos,double maxbcos,double mintan,double maxtan, double minequation,double maxequation)//ISODATA
{
	mminous=minous;
	mmaxous=maxous;
	mmincos=mincos;
	mmaxcos=maxcos;
	mminbcos=minbcos;
	mmaxbcos=maxbcos;
	mmintan=mintan;
	mmaxtan=maxtan;
	m_MinEquationOut=minequation;
	m_MaxEquationOut=maxequation;
//	UpdateData(false);
	m_ShowType=3;

}


BOOL DlgInfor::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if (m_ShowType==1)//读取距离形式
	{
/*		GetDlgItem(IDC_EDIT_T)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_EQUATIONIN)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_CENTERNUM)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_TIMES)->EnableWindow(false);

		GetDlgItem(IDC_EDIT_MAXEQUATIONOUT)->ShowWindow(false);
		GetDlgItem(IDC_EDIT_MINEQUATIONOUT)->ShowWindow(false);
*/

		GetDlgItem(IDC_STATIC2)->ShowWindow(false);
		GetDlgItem(IDC_STATIC3)->ShowWindow(false);
		GetDlgItem(IDC_STATIC4)->ShowWindow(false);
		GetDlgItem(IDC_STATIC5)->ShowWindow(false);
		GetDlgItem(IDC_STATIC6)->ShowWindow(false);
		GetDlgItem(IDC_STATIC7)->ShowWindow(false);
		GetDlgItem(IDC_STATIC8)->ShowWindow(false);
		GetDlgItem(IDC_STATIC9)->ShowWindow(false);
		GetDlgItem(IDC_STATIC10)->ShowWindow(false);

		GetDlgItem(IDC_EDIT_MINDIS)->ShowWindow(false);
		GetDlgItem(IDC_EDIT_T)->ShowWindow(false);
		GetDlgItem(IDC_EDIT_MAXDIS)->ShowWindow(false);

		GetDlgItem(IDC_EDIT_EQUATIONIN)->ShowWindow(false);
		GetDlgItem(IDC_EDIT_CENTERNUM)->ShowWindow(false);
		GetDlgItem(IDC_EDIT_TIMES)->ShowWindow(false);

		GetDlgItem(IDC_EDIT_EQUATIONIN)->ShowWindow(false);
		GetDlgItem(IDC_EDIT_MAXEQUATIONOUT)->ShowWindow(false);
		GetDlgItem(IDC_EDIT_MINEQUATIONOUT)->ShowWindow(false);

//		::SetWindowPos((HWND)GetDlgItem(IDC_STATIC1),NULL,200,200,500,500,TRUE);
//		MessageBox("");
		
	}
	else if (m_ShowType==2)//读取阈值
	{
		GetDlgItem(IDC_STATIC9)->ShowWindow(false);
		GetDlgItem(IDC_STATIC10)->ShowWindow(false);
		GetDlgItem(IDC_EDIT_CENTERNUM)->ShowWindow(false);
		GetDlgItem(IDC_EDIT_TIMES)->ShowWindow(false);	

		GetDlgItem(IDC_STATIC6)->ShowWindow(false);
		GetDlgItem(IDC_STATIC7)->ShowWindow(false);
		GetDlgItem(IDC_STATIC8)->ShowWindow(false);
		GetDlgItem(IDC_EDIT_EQUATIONIN)->ShowWindow(false);	
		GetDlgItem(IDC_EDIT_MAXEQUATIONOUT)->ShowWindow(false);
		GetDlgItem(IDC_EDIT_MINEQUATIONOUT)->ShowWindow(false);
	}
	else if (m_ShowType==3)//阈值、类中心数、方差、循环次数
	{
//		GetDlgItem(IDC_EDIT_TIMES)->EnableWindow(false);
		
//		::SetWindowPos(this->m_hWnd,NULL,0,0,500,500,TRUE);
//		GetDlgItem(IDC_STATIC1)->ShowWindow(false);

	}
	else if (m_ShowType==4)////读取类中心数、循环次数
	{
		GetDlgItem(IDC_STATIC3)->ShowWindow(false);
		GetDlgItem(IDC_STATIC4)->ShowWindow(false);
		GetDlgItem(IDC_STATIC5)->ShowWindow(false);
		GetDlgItem(IDC_STATIC6)->ShowWindow(false);
		GetDlgItem(IDC_STATIC7)->ShowWindow(false);
		GetDlgItem(IDC_STATIC8)->ShowWindow(false);
		
		GetDlgItem(IDC_EDIT_MINDIS)->ShowWindow(false);
		GetDlgItem(IDC_EDIT_T)->ShowWindow(false);
		GetDlgItem(IDC_EDIT_MAXDIS)->ShowWindow(false);		

		GetDlgItem(IDC_EDIT_EQUATIONIN)->ShowWindow(false);
		GetDlgItem(IDC_EDIT_MAXEQUATIONOUT)->ShowWindow(false);
		GetDlgItem(IDC_EDIT_MINEQUATIONOUT)->ShowWindow(false);

//		GetDlgItem(IDC_EDIT_CENTERNUM)->EnableWindow(true);
//		GetDlgItem(IDC_EDIT_TIMES)->EnableWindow(true);


	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgInfor::OnRadioBcos() 
{
	m_DisType=3;//特征是二值时的夹角余弦
	m_MinDis=mminbcos;
	m_MaxDis=mmaxbcos;
	UpdateData(false);
}

void DlgInfor::OnRadioCos() 
{
	m_DisType=2;//	夹角余弦距离
	m_MinDis=mmincos;
	m_MaxDis=mmaxcos;
	UpdateData(false);

}

void DlgInfor::OnRadioOus() 
{
	m_DisType=1;//	欧氏距离
	m_MinDis=mminous;
	m_MaxDis=mmaxous;
	UpdateData(false);
}

void DlgInfor::OnRadioTan() 
{
	m_DisType=4;//	Tanimoto测度
	m_MinDis=mmintan;
	m_MaxDis=mmaxtan;
	UpdateData(false);
}
