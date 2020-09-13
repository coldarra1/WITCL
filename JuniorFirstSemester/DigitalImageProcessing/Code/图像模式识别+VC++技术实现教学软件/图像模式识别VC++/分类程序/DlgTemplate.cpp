// DlgTemplate.cpp : implementation file
// 2005.1.13－16：02 By Superman 

#include "stdafx.h"
#include "DSPLIT.h"
#include "DlgTemplate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTemplate dialog


CDlgTemplate::CDlgTemplate(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTemplate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTemplate)
	m_num0 = 0;
	m_num1 = 0;
	m_num10 = 0;
	m_num11 = 0;
	m_num12 = 0;
	m_num13 = 0;
	m_num14 = 0;
	m_num15 = 0;
	m_num16 = 0;
	m_num17 = 0;
	m_num18 = 0;
	m_num19 = 0;
	m_num2 = 0;
	m_num20 = 0;
	m_num21 = 0;
	m_num22 = 0;
	m_num23 = 0;
	m_num24 = 0;
	m_num3 = 0;
	m_num4 = 0;
	m_num6 = 0;
	m_num5 = 0;
	m_num7 = 0;
	m_num8 = 0;
	m_num9 = 0;

	//}}AFX_DATA_INIT
	select=1;
	addnew=FALSE;
}


void CDlgTemplate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTemplate)
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT_NUM0, m_num0);
	DDV_MinMaxInt(pDX, m_num0, 0, 1);
	DDX_Text(pDX, IDC_EDIT_NUM1, m_num1);
	DDX_Text(pDX, IDC_EDIT_NUM10, m_num10);
	DDX_Text(pDX, IDC_EDIT_NUM11, m_num11);
	DDX_Text(pDX, IDC_EDIT_NUM12, m_num12);
	DDX_Text(pDX, IDC_EDIT_NUM13, m_num13);
	DDX_Text(pDX, IDC_EDIT_NUM14, m_num14);
	DDX_Text(pDX, IDC_EDIT_NUM15, m_num15);
	DDX_Text(pDX, IDC_EDIT_NUM16, m_num16);
	DDX_Text(pDX, IDC_EDIT_NUM17, m_num17);
	DDX_Text(pDX, IDC_EDIT_NUM18, m_num18);
	DDX_Text(pDX, IDC_EDIT_NUM19, m_num19);
	DDX_Text(pDX, IDC_EDIT_NUM2, m_num2);
	DDX_Text(pDX, IDC_EDIT_NUM20, m_num20);
	DDX_Text(pDX, IDC_EDIT_NUM21, m_num21);
	DDX_Text(pDX, IDC_EDIT_NUM22, m_num22);
	DDX_Text(pDX, IDC_EDIT_NUM23, m_num23);
	DDX_Text(pDX, IDC_EDIT_NUM24, m_num24);
	DDX_Text(pDX, IDC_EDIT_NUM3, m_num3);
	DDX_Text(pDX, IDC_EDIT_NUM4, m_num4);
	DDX_Text(pDX, IDC_EDIT_NUM6, m_num6);
	DDX_Text(pDX, IDC_EDIT_NUM5, m_num5);
	DDX_Text(pDX, IDC_EDIT_NUM7, m_num7);
	DDX_Text(pDX, IDC_EDIT_NUM8, m_num8);
	DDX_Text(pDX, IDC_EDIT_NUM9, m_num9);
	DDX_Text(pDX, IDC_EDIT_TOTAL, m_total);
	DDX_Text(pDX, IDC_EDIT1, m_1);
	DDX_Text(pDX, IDC_EDIT10, m_0);
	DDX_Text(pDX, IDC_EDIT2, m_2);
	DDX_Text(pDX, IDC_EDIT3, m_3);
	DDX_Text(pDX, IDC_EDIT4, m_4);
	DDX_Text(pDX, IDC_EDIT5, m_5);
	DDX_Text(pDX, IDC_EDIT6, m_6);
	DDX_Text(pDX, IDC_EDIT7, m_7);
	DDX_Text(pDX, IDC_EDIT8, m_8);
	DDX_Text(pDX, IDC_EDIT9, m_9);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTemplate, CDialog)
	//{{AFX_MSG_MAP(CDlgTemplate)
	ON_BN_CLICKED(IDC_BUTTON_ADDNEW, OnButtonAddnew)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_PRIOR, OnButtonPrior)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnButtonNext)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_RADIO6, OnRadio6)
	ON_BN_CLICKED(IDC_RADIO7, OnRadio7)
	ON_BN_CLICKED(IDC_RADIO8, OnRadio8)
	ON_BN_CLICKED(IDC_RADIO9, OnRadio9)
	ON_BN_CLICKED(IDC_RADIO10, OnRadio10)
	ON_CBN_CLOSEUP(IDC_COMBO1, OnCloseupCombo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTemplate message handlers

void CDlgTemplate::OnOK() 
{
	CFile TheFile(curDir+"\\template.dat",CFile::modeCreate|CFile::modeReadWrite);
	CArchive ar(&TheFile,CArchive::store,40960);
	TheFile.SeekToBegin();

/*	for(int i=0;i<10;i++)  //initialize
	{
		pattern[i].number=1;
		for(int n=0;n<pattern[i].number;n++)
		for(int j=0;j<25;j++)
		{
			pattern[i].feature[n][j]=0;
		}
	}
*/	
	for(int i=0;i<10;i++)
	{
		ar<<pattern[i].number;
		for(int n=0;n<pattern[i].number;n++)
		for(int j=0;j<25;j++)
			{
				ar<<pattern[i].feature[n][j];
			}
	}
	ar.Close();
	TheFile.Close();

	CDialog::OnOK();
}

void CDlgTemplate::OnButtonAddnew() 
{
	if(pattern[select].number<200)
	{
		::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM0),EM_SETREADONLY,FALSE,0);
		::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM1),EM_SETREADONLY,FALSE,0);
		::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM2),EM_SETREADONLY,FALSE,0);
		::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM3),EM_SETREADONLY,FALSE,0);
		::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM4),EM_SETREADONLY,FALSE,0);
		::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM5),EM_SETREADONLY,FALSE,0);
		::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM6),EM_SETREADONLY,FALSE,0);
		::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM7),EM_SETREADONLY,FALSE,0);
		::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM8),EM_SETREADONLY,FALSE,0);
		::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM9),EM_SETREADONLY,FALSE,0);
		::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM10),EM_SETREADONLY,FALSE,0);
		::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM11),EM_SETREADONLY,FALSE,0);
		::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM12),EM_SETREADONLY,FALSE,0);
		::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM13),EM_SETREADONLY,FALSE,0);
		::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM14),EM_SETREADONLY,FALSE,0);
		::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM15),EM_SETREADONLY,FALSE,0);
		::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM16),EM_SETREADONLY,FALSE,0);
		::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM17),EM_SETREADONLY,FALSE,0);
		::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM18),EM_SETREADONLY,FALSE,0);
		::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM19),EM_SETREADONLY,FALSE,0);
		::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM20),EM_SETREADONLY,FALSE,0);
		::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM21),EM_SETREADONLY,FALSE,0);
		::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM22),EM_SETREADONLY,FALSE,0);
		::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM23),EM_SETREADONLY,FALSE,0);
		::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM24),EM_SETREADONLY,FALSE,0);	
		AfxMessageBox("请输入设计样品，然后保存样品。",MB_OK,NULL);
		GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(TRUE);
		addnew=TRUE;
	}
	else
	{
		AfxMessageBox("样品数量不要超过250个。",MB_OK,NULL);
	}
}

void CDlgTemplate::OnButtonSave() 
{
	UpdateData();
	if(addnew)
	{
		CString str;
		str.Format("%d",pattern[select].number);
		m_combo.AddString(str);
		m_combo.SetCurSel(0);
		for(int i=pattern[select].number;i>0;i--)
			for(int j=0;j<25;j++)
				pattern[select].feature[i][j]=pattern[select].feature[i-1][j];
		pattern[select].number++;
		switch (select)
		{
		case 0:
			m_0++;break;
		case 1:
			m_1++;break;
		case 2:
			m_2++;break;
		case 3:
			m_3++;break;
		case 4:
			m_4++;break;			
		case 5:
			m_5++;break;			
		case 6:
			m_6++;break;			
		case 7:
			m_7++;break;			
		case 8:
			m_8++;break;			
		case 9:
			m_9++;break;			
		}
		m_total++;
		addnew=FALSE;
	}
	pattern[select].feature[m_combo.GetCurSel()][0]=m_num0;
	pattern[select].feature[m_combo.GetCurSel()][1]=m_num1;	
	pattern[select].feature[m_combo.GetCurSel()][2]=m_num2;
	pattern[select].feature[m_combo.GetCurSel()][3]=m_num3;	
	pattern[select].feature[m_combo.GetCurSel()][4]=m_num4;
	pattern[select].feature[m_combo.GetCurSel()][5]=m_num5;	
	pattern[select].feature[m_combo.GetCurSel()][6]=m_num6;
	pattern[select].feature[m_combo.GetCurSel()][7]=m_num7;	
	pattern[select].feature[m_combo.GetCurSel()][8]=m_num8;
	pattern[select].feature[m_combo.GetCurSel()][9]=m_num9;	
	pattern[select].feature[m_combo.GetCurSel()][10]=m_num10;
	pattern[select].feature[m_combo.GetCurSel()][11]=m_num11;	
	pattern[select].feature[m_combo.GetCurSel()][12]=m_num12;
	pattern[select].feature[m_combo.GetCurSel()][13]=m_num13;	
	pattern[select].feature[m_combo.GetCurSel()][14]=m_num14;
	pattern[select].feature[m_combo.GetCurSel()][15]=m_num15;	
	pattern[select].feature[m_combo.GetCurSel()][16]=m_num16;
	pattern[select].feature[m_combo.GetCurSel()][17]=m_num17;	
	pattern[select].feature[m_combo.GetCurSel()][18]=m_num18;
	pattern[select].feature[m_combo.GetCurSel()][19]=m_num19;	
	pattern[select].feature[m_combo.GetCurSel()][20]=m_num20;
	pattern[select].feature[m_combo.GetCurSel()][21]=m_num21;	
	pattern[select].feature[m_combo.GetCurSel()][22]=m_num22;
	pattern[select].feature[m_combo.GetCurSel()][23]=m_num23;	
	pattern[select].feature[m_combo.GetCurSel()][24]=m_num24;
	UpdateData(FALSE);
	GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(FALSE);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM0),EM_SETREADONLY,TRUE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM1),EM_SETREADONLY,TRUE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM2),EM_SETREADONLY,TRUE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM3),EM_SETREADONLY,TRUE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM4),EM_SETREADONLY,TRUE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM5),EM_SETREADONLY,TRUE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM6),EM_SETREADONLY,TRUE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM7),EM_SETREADONLY,TRUE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM8),EM_SETREADONLY,TRUE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM9),EM_SETREADONLY,TRUE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM10),EM_SETREADONLY,TRUE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM11),EM_SETREADONLY,TRUE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM12),EM_SETREADONLY,TRUE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM13),EM_SETREADONLY,TRUE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM14),EM_SETREADONLY,TRUE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM15),EM_SETREADONLY,TRUE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM16),EM_SETREADONLY,TRUE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM17),EM_SETREADONLY,TRUE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM18),EM_SETREADONLY,TRUE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM19),EM_SETREADONLY,TRUE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM20),EM_SETREADONLY,TRUE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM21),EM_SETREADONLY,TRUE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM22),EM_SETREADONLY,TRUE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM23),EM_SETREADONLY,TRUE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM24),EM_SETREADONLY,TRUE,0);
}

void CDlgTemplate::OnButtonUpdate() 
{
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM0),EM_SETREADONLY,FALSE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM1),EM_SETREADONLY,FALSE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM2),EM_SETREADONLY,FALSE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM3),EM_SETREADONLY,FALSE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM4),EM_SETREADONLY,FALSE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM5),EM_SETREADONLY,FALSE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM6),EM_SETREADONLY,FALSE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM7),EM_SETREADONLY,FALSE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM8),EM_SETREADONLY,FALSE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM9),EM_SETREADONLY,FALSE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM10),EM_SETREADONLY,FALSE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM11),EM_SETREADONLY,FALSE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM12),EM_SETREADONLY,FALSE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM13),EM_SETREADONLY,FALSE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM14),EM_SETREADONLY,FALSE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM15),EM_SETREADONLY,FALSE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM16),EM_SETREADONLY,FALSE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM17),EM_SETREADONLY,FALSE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM18),EM_SETREADONLY,FALSE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM19),EM_SETREADONLY,FALSE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM20),EM_SETREADONLY,FALSE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM21),EM_SETREADONLY,FALSE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM22),EM_SETREADONLY,FALSE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM23),EM_SETREADONLY,FALSE,0);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDIT_NUM24),EM_SETREADONLY,FALSE,0);
	AfxMessageBox("请重新设计样品，然后保存样品。",MB_OK,NULL);
	GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(TRUE);	
}

void CDlgTemplate::OnButtonDelete() 
{
	if(pattern[select].number>1)
	{
		if(IDOK==AfxMessageBox("确认要删除该模板么？",MB_OKCANCEL,NULL))
		{
			for(int i=m_combo.GetCurSel();i<pattern[select].number-1;i++)
				for(int j=0;j<25;j++)
					pattern[select].feature[i][j] =pattern[select].feature[i+1][j];		
			pattern[select].number--;
			OnUpdate();
			m_combo.SetCurSel(0);
			OnCloseupCombo();

			AfxMessageBox("成功删除模板！",MB_OK,NULL);
			switch(select)
			{
			case 0:
				m_0--;break;
			case 1:
				m_1--;break;
			case 2:
				m_2--;break;
			case 3:
				m_3--;break;
			case 4:
				m_4--;break;			
			case 5:
				m_5--;break;			
			case 6:
				m_6--;break;			
			case 7:
				m_7--;break;			
			case 8:
				m_8--;break;			
			case 9:
				m_9--;break;
			}
			m_total--;
			UpdateData(FALSE);
		}
	}
	else
		AfxMessageBox("只剩下一个模板，无法完成删除！",MB_OK,NULL);	
	
}

void CDlgTemplate::OnButtonPrior() 
{
	if(m_combo.GetCurSel()>0)
	{
		m_combo.SetCurSel(m_combo.GetCurSel()-1);
		OnCloseupCombo() ;
		UpdateData(FALSE);
	}	
}

void CDlgTemplate::OnButtonNext() 
{
	if(m_combo.GetCurSel()<m_combo.GetCount())
	{
		m_combo.SetCurSel(m_combo.GetCurSel()+1);	
		OnCloseupCombo() ;
		UpdateData(FALSE);
	}	
}

BOOL CDlgTemplate::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CFile TheFile(curDir+"\\template.dat",CFile::modeRead);
	CArchive ar(&TheFile,CArchive::load,40960);
	TheFile.SeekToBegin();

	for(int i=0;i<10;i++)
	{
		ar>>pattern[i].number;
		for(int n=0;n<pattern[i].number;n++)
		for(int j=0;j<25;j++)
		{
			ar>>pattern[i].feature[n][j];
		}
	}
	
	ar.Close();
	TheFile.Close();	

	m_0 = pattern[0].number;	
	m_1 = pattern[1].number;
	m_2 = pattern[2].number;
	m_3 = pattern[3].number;
	m_4 = pattern[4].number;
	m_5 = pattern[5].number;
	m_6 = pattern[6].number;
	m_7 = pattern[7].number;
	m_8 = pattern[8].number;
	m_9 = pattern[9].number;	
	m_total = m_1+m_2+m_3+m_4+m_5
		+m_6+m_7+m_8+m_9+m_0;
	UpdateData(FALSE);
	CheckRadioButton(IDC_RADIO1,IDC_RADIO10,IDC_RADIO1);
	for(i=0;i<pattern[1].number;i++)
	{
		CString str;
		str.Format("%d",i);
		m_combo.AddString(str);
	}
	m_combo.SetCurSel(0);
	OnCloseupCombo();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTemplate::OnRadio1() 
{
	select=1;	
	OnUpdate();
}

void CDlgTemplate::OnRadio2() 
{
	select=2;	
	OnUpdate();	
}

void CDlgTemplate::OnRadio3() 
{
	select=3;	
	OnUpdate();	
}

void CDlgTemplate::OnRadio4() 
{
	select=4;	
	OnUpdate();	
}

void CDlgTemplate::OnRadio5() 
{
	select=5;	
	OnUpdate();	
}

void CDlgTemplate::OnRadio6() 
{
	select=6;	
	OnUpdate();	
}

void CDlgTemplate::OnRadio7() 
{
	select=7;	
	OnUpdate();	
}

void CDlgTemplate::OnRadio8() 
{
	select=8;	
	OnUpdate();	
}

void CDlgTemplate::OnRadio9() 
{
	select=9;	
	OnUpdate();	
}

void CDlgTemplate::OnRadio10() 
{
	select=0;	
	OnUpdate();	
}

void CDlgTemplate::OnUpdate()
{
	m_combo.ResetContent();
	for(int i=0;i<pattern[select].number;i++)
	{
		CString str;
		str.Format("%d",i);
		m_combo.AddString(str);
	}
	m_combo.SetCurSel(0);
	OnCloseupCombo();
}

void CDlgTemplate::OnCloseupCombo() 
{
	UpdateData(TRUE);
	m_num0=pattern[select].feature[m_combo.GetCurSel()][0];
	m_num1=pattern[select].feature[m_combo.GetCurSel()][1];
	m_num2=pattern[select].feature[m_combo.GetCurSel()][2];
	m_num3=pattern[select].feature[m_combo.GetCurSel()][3];
	m_num4=pattern[select].feature[m_combo.GetCurSel()][4];
	m_num5=pattern[select].feature[m_combo.GetCurSel()][5];
	m_num6=pattern[select].feature[m_combo.GetCurSel()][6];
	m_num7=pattern[select].feature[m_combo.GetCurSel()][7];
	m_num8=pattern[select].feature[m_combo.GetCurSel()][8];
	m_num9=pattern[select].feature[m_combo.GetCurSel()][9];
	m_num10=pattern[select].feature[m_combo.GetCurSel()][10];
	m_num11=pattern[select].feature[m_combo.GetCurSel()][11];
	m_num12=pattern[select].feature[m_combo.GetCurSel()][12];
	m_num13=pattern[select].feature[m_combo.GetCurSel()][13];
	m_num14=pattern[select].feature[m_combo.GetCurSel()][14];
	m_num15=pattern[select].feature[m_combo.GetCurSel()][15];
	m_num16=pattern[select].feature[m_combo.GetCurSel()][16];
	m_num17=pattern[select].feature[m_combo.GetCurSel()][17];
	m_num18=pattern[select].feature[m_combo.GetCurSel()][18];
	m_num19=pattern[select].feature[m_combo.GetCurSel()][19];
	m_num20=pattern[select].feature[m_combo.GetCurSel()][20];
	m_num21=pattern[select].feature[m_combo.GetCurSel()][21];
	m_num22=pattern[select].feature[m_combo.GetCurSel()][22];
	m_num23=pattern[select].feature[m_combo.GetCurSel()][23];
	m_num24=pattern[select].feature[m_combo.GetCurSel()][24];

	UpdateData(FALSE);	
}
