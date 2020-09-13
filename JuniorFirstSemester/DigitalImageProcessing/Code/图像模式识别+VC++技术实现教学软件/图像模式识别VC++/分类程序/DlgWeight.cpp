// DlgWeight.cpp : implementation file
// 2005.1.13гн16г║02 By Superman 

#include "stdafx.h"
#include "DSPLIT.h"
#include "DlgWeight.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgWeight dialog


CDlgWeight::CDlgWeight(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWeight::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgWeight)
	m_00 = 0.0;
	m_01 = 1.0;
	m_02 = 1.0;
	m_03 = 1.0;
	m_04 = 1.0;
	m_05 = 1.0;
	m_06 = 1.0;
	m_07 = 1.0;
	m_08 = 1.0;
	m_09 = 1.0;
	m_10 = 1.0;
	m_11 = 0.0;
	m_12 = 1.0;
	m_13 = 1.0;
	m_14 = 1.0;
	m_15 = 1.0;
	m_16 = 1.0;
	m_17 = 1.0;
	m_18 = 1.0;
	m_19 = 1.0;
	m_20 = 1.0;
	m_21 = 1.0;
	m_22 = 0.0;
	m_23 = 1.0;
	m_24 = 1.0;
	m_25 = 1.0;
	m_26 = 1.0;
	m_27 = 1.0;
	m_28 = 1.0;
	m_29 = 1.0;
	m_30 = 1.0;
	m_31 = 1.0;
	m_32 = 1.0;
	m_33 = 0.0;
	m_34 = 1.0;
	m_35 = 1.0;
	m_36 = 1.0;
	m_37 = 1.0;
	m_38 = 1.0;
	m_39 = 1.0;
	m_40 = 1.0;
	m_41 = 1.0;
	m_42 = 1.0;
	m_43 = 1.0;
	m_44 = 0.0;
	m_45 = 1.0;
	m_46 = 1.0;
	m_47 = 1.0;
	m_48 = 1.0;
	m_49 = 1.0;
	m_50 = 1.0;
	m_51 = 1.0;
	m_52 = 1.0;
	m_53 = 1.0;
	m_54 = 1.0;
	m_55 = 0.0;
	m_56 = 1.0;
	m_57 = 1.0;
	m_58 = 1.0;
	m_59 = 1.0;
	m_60 = 1.0;
	m_61 = 1.0;
	m_62 = 1.0;
	m_63 = 1.0;
	m_64 = 1.0;
	m_65 = 1.0;
	m_66 = 0.0;
	m_67 = 1.0;
	m_68 = 1.0;
	m_69 = 1.0;
	m_70 = 1.0;
	m_71 = 1.0;
	m_72 = 1.0;
	m_73 = 1.0;
	m_74 = 1.0;
	m_75 = 1.0;
	m_76 = 1.0;
	m_77 = 0.0;
	m_78 = 1.0;
	m_79 = 1.0;
	m_80 = 1.0;
	m_81 = 1.0;
	m_82 = 1.0;
	m_83 = 1.0;
	m_84 = 1.0;
	m_85 = 1.0;
	m_86 = 1.0;
	m_87 = 1.0;
	m_88 = 0.0;
	m_89 = 1.0;
	m_90 = 1.0;
	m_91 = 1.0;
	m_92 = 1.0;
	m_93 = 1.0;
	m_94 = 1.0;
	m_95 = 1.0;
	m_96 = 1.0;
	m_97 = 1.0;
	m_98 = 1.0;
	m_99 = 0.0;

	m_risk0 = 0.0;
	m_risk1 = 0.0;
	m_risk2 = 0.0;
	m_risk3 = 0.0;
	m_risk4 = 0.0;
	m_risk5 = 0.0;
	m_risk6 = 0.0;
	m_risk7 = 0.0;
	m_risk8 = 0.0;
	m_risk9 = 0.0;

	//}}AFX_DATA_INIT
	b=false;
}


void CDlgWeight::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgWeight)
	DDX_Text(pDX, IDC_EDIT1, m_00);
	DDX_Text(pDX, IDC_EDIT2, m_01);
	DDX_Text(pDX, IDC_EDIT3, m_02);
	DDX_Text(pDX, IDC_EDIT4, m_03);
	DDX_Text(pDX, IDC_EDIT5, m_04);
	DDX_Text(pDX, IDC_EDIT6, m_05);
	DDX_Text(pDX, IDC_EDIT7, m_06);
	DDX_Text(pDX, IDC_EDIT8, m_07);
	DDX_Text(pDX, IDC_EDIT9, m_08);
	DDX_Text(pDX, IDC_EDIT10, m_09);
	DDX_Text(pDX, IDC_EDIT11, m_10);
	DDX_Text(pDX, IDC_EDIT12, m_11);
	DDX_Text(pDX, IDC_EDIT13, m_12);
	DDX_Text(pDX, IDC_EDIT14, m_13);
	DDX_Text(pDX, IDC_EDIT15, m_14);
	DDX_Text(pDX, IDC_EDIT16, m_15);
	DDX_Text(pDX, IDC_EDIT17, m_16);
	DDX_Text(pDX, IDC_EDIT18, m_17);
	DDX_Text(pDX, IDC_EDIT19, m_18);
	DDX_Text(pDX, IDC_EDIT20, m_19);
	DDX_Text(pDX, IDC_EDIT21, m_20);
	DDX_Text(pDX, IDC_EDIT22, m_21);
	DDX_Text(pDX, IDC_EDIT23, m_22);
	DDX_Text(pDX, IDC_EDIT24, m_23);
	DDX_Text(pDX, IDC_EDIT25, m_24);
	DDX_Text(pDX, IDC_EDIT26, m_25);
	DDX_Text(pDX, IDC_EDIT27, m_26);
	DDX_Text(pDX, IDC_EDIT28, m_27);
	DDX_Text(pDX, IDC_EDIT29, m_28);
	DDX_Text(pDX, IDC_EDIT30, m_29);
	DDX_Text(pDX, IDC_EDIT31, m_30);
	DDX_Text(pDX, IDC_EDIT32, m_31);
	DDX_Text(pDX, IDC_EDIT33, m_32);
	DDX_Text(pDX, IDC_EDIT34, m_33);
	DDX_Text(pDX, IDC_EDIT35, m_34);
	DDX_Text(pDX, IDC_EDIT36, m_35);
	DDX_Text(pDX, IDC_EDIT37, m_36);
	DDX_Text(pDX, IDC_EDIT38, m_37);
	DDX_Text(pDX, IDC_EDIT39, m_38);
	DDX_Text(pDX, IDC_EDIT40, m_39);
	DDX_Text(pDX, IDC_EDIT41, m_40);
	DDX_Text(pDX, IDC_EDIT42, m_41);
	DDX_Text(pDX, IDC_EDIT43, m_42);
	DDX_Text(pDX, IDC_EDIT44, m_43);
	DDX_Text(pDX, IDC_EDIT45, m_44);
	DDX_Text(pDX, IDC_EDIT46, m_45);
	DDX_Text(pDX, IDC_EDIT47, m_46);
	DDX_Text(pDX, IDC_EDIT48, m_47);
	DDX_Text(pDX, IDC_EDIT49, m_48);
	DDX_Text(pDX, IDC_EDIT50, m_49);
	DDX_Text(pDX, IDC_EDIT51, m_50);
	DDX_Text(pDX, IDC_EDIT52, m_51);
	DDX_Text(pDX, IDC_EDIT53, m_52);
	DDX_Text(pDX, IDC_EDIT54, m_53);
	DDX_Text(pDX, IDC_EDIT55, m_54);
	DDX_Text(pDX, IDC_EDIT56, m_55);
	DDX_Text(pDX, IDC_EDIT57, m_56);
	DDX_Text(pDX, IDC_EDIT58, m_57);
	DDX_Text(pDX, IDC_EDIT59, m_58);
	DDX_Text(pDX, IDC_EDIT60, m_59);
	DDX_Text(pDX, IDC_EDIT61, m_60);
	DDX_Text(pDX, IDC_EDIT62, m_61);
	DDX_Text(pDX, IDC_EDIT63, m_62);
	DDX_Text(pDX, IDC_EDIT64, m_63);
	DDX_Text(pDX, IDC_EDIT65, m_64);
	DDX_Text(pDX, IDC_EDIT66, m_65);
	DDX_Text(pDX, IDC_EDIT67, m_66);
	DDX_Text(pDX, IDC_EDIT68, m_67);
	DDX_Text(pDX, IDC_EDIT69, m_68);
	DDX_Text(pDX, IDC_EDIT70, m_69);
	DDX_Text(pDX, IDC_EDIT71, m_70);
	DDX_Text(pDX, IDC_EDIT72, m_71);
	DDX_Text(pDX, IDC_EDIT73, m_72);
	DDX_Text(pDX, IDC_EDIT74, m_73);
	DDX_Text(pDX, IDC_EDIT75, m_74);
	DDX_Text(pDX, IDC_EDIT76, m_75);
	DDX_Text(pDX, IDC_EDIT77, m_76);
	DDX_Text(pDX, IDC_EDIT78, m_77);
	DDX_Text(pDX, IDC_EDIT79, m_78);
	DDX_Text(pDX, IDC_EDIT80, m_79);
	DDX_Text(pDX, IDC_EDIT81, m_80);
	DDX_Text(pDX, IDC_EDIT82, m_81);
	DDX_Text(pDX, IDC_EDIT83, m_82);
	DDX_Text(pDX, IDC_EDIT84, m_83);
	DDX_Text(pDX, IDC_EDIT85, m_84);
	DDX_Text(pDX, IDC_EDIT86, m_85);
	DDX_Text(pDX, IDC_EDIT87, m_86);
	DDX_Text(pDX, IDC_EDIT88, m_87);
	DDX_Text(pDX, IDC_EDIT89, m_88);
	DDX_Text(pDX, IDC_EDIT90, m_89);
	DDX_Text(pDX, IDC_EDIT91, m_90);
	DDX_Text(pDX, IDC_EDIT92, m_91);
	DDX_Text(pDX, IDC_EDIT93, m_92);
	DDX_Text(pDX, IDC_EDIT94, m_93);
	DDX_Text(pDX, IDC_EDIT95, m_94);
	DDX_Text(pDX, IDC_EDIT96, m_95);
	DDX_Text(pDX, IDC_EDIT97, m_96);
	DDX_Text(pDX, IDC_EDIT98, m_97);
	DDX_Text(pDX, IDC_EDIT99, m_98);
	DDX_Text(pDX, IDC_EDIT100, m_99);
	DDX_Text(pDX, IDC_EDIT101, m_risk0);
	DDX_Text(pDX, IDC_EDIT102, m_risk1);
	DDX_Text(pDX, IDC_EDIT103, m_risk2);
	DDX_Text(pDX, IDC_EDIT104, m_risk3);
	DDX_Text(pDX, IDC_EDIT105, m_risk4);
	DDX_Text(pDX, IDC_EDIT106, m_risk5);
	DDX_Text(pDX, IDC_EDIT107, m_risk6);
	DDX_Text(pDX, IDC_EDIT108, m_risk7);
	DDX_Text(pDX, IDC_EDIT109, m_risk8);
	DDX_Text(pDX, IDC_EDIT110, m_risk9);


	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgWeight, CDialog)
	//{{AFX_MSG_MAP(CDlgWeight)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgWeight message handlers

void CDlgWeight::OnOK() 
{
	if(b)
		CDialog::OnCancel();
	else
	{
	loss[0][0]=m_00;
	loss[0][1]=m_01;
	loss[0][2]=m_02;
	loss[0][3]=m_03;
	loss[0][4]=m_04;
	loss[0][5]=m_05;
	loss[0][6]=m_06;
	loss[0][7]=m_07;
	loss[0][8]=m_08;
	loss[0][9]=m_09;

	loss[1][0]=m_10;
	loss[1][1]=m_11;
	loss[1][2]=m_12;
	loss[1][3]=m_13;
	loss[1][4]=m_14;
	loss[1][5]=m_15;
	loss[1][6]=m_16;
	loss[1][7]=m_17;
	loss[1][8]=m_18;
	loss[1][9]=m_19;

	loss[2][0]=m_20;
	loss[2][1]=m_21;
	loss[2][2]=m_22;
	loss[2][3]=m_23;
	loss[2][4]=m_24;
	loss[2][5]=m_25;
	loss[2][6]=m_26;
	loss[2][7]=m_27;
	loss[2][8]=m_28;
	loss[2][9]=m_29;

	loss[3][0]=m_30;
	loss[3][1]=m_31;
	loss[3][2]=m_32;
	loss[3][3]=m_33;
	loss[3][4]=m_34;
	loss[3][5]=m_35;
	loss[3][6]=m_36;
	loss[3][7]=m_37;
	loss[3][8]=m_38;
	loss[3][9]=m_39;

	loss[4][0]=m_40;
	loss[4][1]=m_41;
	loss[4][2]=m_42;
	loss[4][3]=m_43;
	loss[4][4]=m_44;
	loss[4][5]=m_45;
	loss[4][6]=m_46;
	loss[4][7]=m_47;
	loss[4][8]=m_48;
	loss[4][9]=m_49;

	loss[5][0]=m_50;
	loss[5][1]=m_51;
	loss[5][2]=m_52;
	loss[5][3]=m_53;
	loss[5][4]=m_54;
	loss[5][5]=m_55;
	loss[5][6]=m_56;
	loss[5][7]=m_57;
	loss[5][8]=m_58;
	loss[5][9]=m_59;

	loss[6][0]=m_60;
	loss[6][1]=m_61;
	loss[6][2]=m_62;
	loss[6][3]=m_63;
	loss[6][4]=m_64;
	loss[6][5]=m_65;
	loss[6][6]=m_66;
	loss[6][7]=m_67;
	loss[6][8]=m_68;
	loss[6][9]=m_69;

	loss[7][0]=m_70;
	loss[7][1]=m_71;
	loss[7][2]=m_72;
	loss[7][3]=m_73;
	loss[7][4]=m_74;
	loss[7][5]=m_75;
	loss[7][6]=m_76;
	loss[7][7]=m_77;
	loss[7][8]=m_78;
	loss[7][9]=m_79;

	loss[8][0]=m_80;
	loss[8][1]=m_81;
	loss[8][2]=m_82;
	loss[8][3]=m_83;
	loss[8][4]=m_84;
	loss[8][5]=m_85;
	loss[8][6]=m_86;
	loss[8][7]=m_87;
	loss[8][8]=m_88;
	loss[8][9]=m_89;

	loss[9][0]=m_90;
	loss[9][1]=m_91;
	loss[9][2]=m_92;
	loss[9][3]=m_93;
	loss[9][4]=m_94;
	loss[9][5]=m_95;
	loss[9][6]=m_96;
	loss[9][7]=m_97;
	loss[9][8]=m_98;
	loss[9][9]=m_99;

	CDialog::OnOK();
	}
}



