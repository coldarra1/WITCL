// DynSplitView2.cpp : implementation file
// 2005.1.13－16：02 By Superman 

#include "stdafx.h"
#include "DSPLIT.h"

#include "DynSplitView2.h"
#include "dlgNumber.h"
#include "DlgClassify.h"
#include "Dlgdisplay.h"
#include "DlgWeight.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BpNet bpnet1;	
/////////////////////////////////////////////////////////////////////////////
// CDynSplitView2

IMPLEMENT_DYNCREATE(CDynSplitView2, CView)

CDynSplitView2::CDynSplitView2():number(-1),no(0)
{
		
}

CDynSplitView2::~CDynSplitView2()
{
}


BEGIN_MESSAGE_MAP(CDynSplitView2, CView)
	//{{AFX_MSG_MAP(CDynSplitView2)
	ON_COMMAND(ID_BUTTON_SAVE, OnButtonSave)
	ON_COMMAND(ID_BUTTON_LMSEifClassified, OnBUTTONLMSEifClassified)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_MENU_IFCLASSIFICATION, OnMenuIfclassification)
	ON_COMMAND(ID_MENU_LEASTDISTANCE, OnMenuLeastdistance)
	ON_COMMAND(ID_MENU_FISHER, OnMenuFisher)
	ON_COMMAND(ID_MENU_BAYES_ERZHI, OnMenuBayesErzhi)
	ON_COMMAND(ID_MENU_BAYES_LEASTERROR, OnMenuBayesLeasterror)
	ON_COMMAND(ID_MENU_BAYES_LEASTRISK, OnMenuBayesLeastrisk)
	ON_COMMAND(ID_MENU_JIANGCHENG, OnMenuJiangcheng)
	ON_COMMAND(ID_MENU_LMSE, OnMenuLMSE)
	ON_COMMAND(ID_MENU_ZENGLIANGJIAOZHENG, OnMenuZengliangjiaozheng)
	ON_COMMAND(ID_BP_TRAIN, OnBpTrain)
	ON_COMMAND(ID_BP_TEST, OnBpTest)
	ON_COMMAND(ID_BP_CLASSIFY, OnBpClassify)
	ON_COMMAND(ID_MENU_BPQUANZHI, OnMenuBpquanzhi)
	ON_COMMAND(ID_MENU_SHIHANSHU, OnMenuShihanshu)
	ON_WM_CANCELMODE()
	ON_WM_CAPTURECHANGED()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDynSplitView2 drawing

void CDynSplitView2::OnDraw(CDC* pDC)
{
	clearmem();
	CDocument* pDoc = GetDocument();
	int i,j;
	pDC->SetTextColor(RGB(255,0,0));
	for(i=0;i<5;i++)
		for(j=0;j<5;j++)
			if(classify->testsample[5*i+j]>0.1)
				pDC->TextOut(j*15,i*15,"■");
	pDC->TextOut(10,80,"待定样品");
	pDC->SetTextColor(RGB(0,255,0));
	for(i=0;i<5;i++)
		for(j=0;j<5;j++)
			if(number!=-1)
				if(classify->pattern[number].feature[no][i*5+j]>0.1)
					pDC->TextOut(150+j*15,i*15,"■");
	pDC->TextOut(160,80,"最接近样品");

}

/////////////////////////////////////////////////////////////////////////////
// CDynSplitView2 diagnostics

#ifdef _DEBUG
void CDynSplitView2::AssertValid() const
{
	CView::AssertValid();
}

void CDynSplitView2::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDSPLITDoc* CDynSplitView2::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDSPLITDoc)));
	return (CDSPLITDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDynSplitView2 message handlers

void CDynSplitView2::OnButtonSave() 
{
	CDlgNumber dlg;
	if(IDOK==dlg.DoModal())
	{
		if(classify->pattern[dlg.m_num].number>200)
			MessageBox("模板个数不能超过200个！",NULL,MB_OK);
		else
		{
			if (classify->Saveable(dlg.m_num))
			{
				classify->Save(dlg.m_num);
			}
			else
				MessageBox("此样品已存在于样品库中，请改变样品的特征。",NULL,MB_OK);
		}


		CFile TheFile(curDir+"\\template.dat",CFile::modeCreate|CFile::modeReadWrite);//
		CArchive ar(&TheFile,CArchive::store,40960);
		TheFile.SeekToBegin();
		for(int n=0;n<10;n++)
		{
			ar<<classify->pattern[n].number;
			for(int i=0;i<classify->pattern[n].number;i++)
			for(int j=0;j<25;j++)
			{
				ar<<classify->pattern[n].feature[i][j];
			}
		}
		ar.Close();
		TheFile.Close();
	}
	
}

void CDynSplitView2::OnBUTTONLMSEifClassified() 
{
	DlgClassify dlg;
	dlg.m_num2=1;
	if(IDOK==dlg.DoModal())
	{
		CDlgdisplay dlg1;
		BeginWaitCursor();
		dlg1.m_str=classify->ifClassified(dlg.m_num1,dlg.m_num2);
		EndWaitCursor();
		dlg1.DoModal();
	}
}

void CDynSplitView2::clearmem()
{
	CDSPLITDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
    classify=&pDoc->classify;
	bpnet=&bpnet1;
	curDir=pDoc->curDir;
}

void CDynSplitView2::OnLButtonDown(UINT nFlags, CPoint point) 
{
	clearmem();
	classify->GetPosition();
	classify->SetFeature();
	Invalidate();	
	CView::OnLButtonDown(nFlags, point);
}

void CDynSplitView2::OnMenuIfclassification() 
{
	OnBUTTONLMSEifClassified();	
}

void CDynSplitView2::OnMenuLeastdistance() 
{
	number_no number_no;
	number_no=classify->LeastDistance();
	number=number_no.number;
	no=number_no.no;
	CString str;
	str.Format("应用最小距离法，\n自动分类识别结果为：%d",number);
	AfxMessageBox(str,MB_OK,NULL);
	Invalidate();	
}

void CDynSplitView2::OnMenuFisher() 
{
	BeginWaitCursor();
	number=classify->Fisher();
	EndWaitCursor();
	CString str;
	str.Format("应用Fisher算法，\n自动分类识别结果为：%d",number);
	AfxMessageBox(str,MB_OK,NULL);	
	Invalidate();
	
}

void CDynSplitView2::OnMenuBayesErzhi() 
{
	BeginWaitCursor();
	number=classify->BayesErzhishuju();
	EndWaitCursor();
	CString str;
	str.Format("应用二值数据的Bayes算法，\n自动分类识别结果为：%d",number);
	AfxMessageBox(str,MB_OK,NULL);	
	Invalidate();
}

void CDynSplitView2::OnMenuBayesLeasterror() 
{
	BeginWaitCursor();
	number=classify->BayesLeasterror();
	EndWaitCursor();
	CString str;
	str.Format("应用最小错误概率的Bayes算法，\n自动分类识别结果为：%d",number);
	AfxMessageBox(str,MB_OK,NULL);	
	Invalidate();	
}

void CDynSplitView2::OnMenuBayesLeastrisk() 
{
	CDlgWeight dlg;
	if(dlg.DoModal()==IDOK)
	{
		BeginWaitCursor();
		double *hx;
		hx=classify->BayesLeastRisk(dlg.loss);
		//判别函数的最小值
		double minval=hx[0];
		int number=0;
		for(int i=1;i<10;i++)
		{
			if(hx[i]<minval)
			{
				minval=hx[i];
				number=i;
			}
		}
		EndWaitCursor();
		CString str;
		str.Format("应用最小风险的Bayes算法，\n自动分类识别结果为：%d",number);
		AfxMessageBox(str,MB_OK,NULL);
		Invalidate();
		dlg.b=true;
		dlg.m_risk0=hx[0];
		dlg.m_risk1=hx[1];
		dlg.m_risk2=hx[2];
		dlg.m_risk3=hx[3];
		dlg.m_risk4=hx[4];
		dlg.m_risk5=hx[5];
		dlg.m_risk6=hx[6];
		dlg.m_risk7=hx[7];
		dlg.m_risk8=hx[8];
		dlg.m_risk9=hx[9];
		dlg.DoModal();
	}
}

void CDynSplitView2::OnMenuJiangcheng() 
{
	BeginWaitCursor();
	number=classify->Jiangcheng();
	EndWaitCursor();
	CString str;
	str.Format("应用感知器奖惩算法，\n自动分类识别结果为：%d",number);
	AfxMessageBox(str,MB_OK,NULL);	
	Invalidate();	
}

void CDynSplitView2::OnMenuLMSE() 
{
	BeginWaitCursor();
	number=classify->LMSE();
	EndWaitCursor();
	CString str;
	str.Format("应用LMSE算法，\n自动分类识别结果为：%d",number);
	AfxMessageBox(str,MB_OK,NULL);	
	Invalidate();	
}

void CDynSplitView2::OnMenuZengliangjiaozheng() 
{
	BeginWaitCursor();
	number=classify->Zengliangjiaozheng();
	EndWaitCursor();
	CString str;
	str.Format("应用增量校正算法，\n自动分类识别结果为：%d",number);
	AfxMessageBox(str,MB_OK,NULL);	
	Invalidate();	
}



void CDynSplitView2::OnBpTrain() 
{
	double p[500][5];
	double t[500][4];
	int samplenum=500;
	int innum=bpnet->inNum;
	int outnum=bpnet->outNum;
	int i,j;

	for(i=0;i<10;i++)
	for(j=0;j<50;j++)		
	{
		t[i+j*10][0]=i%2;
		t[i+j*10][1]=i/2%2;	
		t[i+j*10][2]=i/4%2;
		t[i+j*10][3]=i/8%2;
	}

	for(i=0;i<10;i++)
		for(j=0;j<50;j++)
		{
			int k1,k2;
			for(k1=0;k1<5;k1++)
			{
				double num=0.0;	
				for(k2=0;k2<5;k2++)
					num+=classify->pattern[i].feature[j][k1*5+k2];
				p[i+j*10][k1]=num;
			}
		}

	BeginWaitCursor();
	for(i=0;i<20000;i++)
		bpnet->train(p,t,samplenum);
	CString str,s;
	CStdioFile cf;
	str.Insert(-1,"隐含结点权值:\n");
	for(i=0;i<5;i++)
	{
		for(j=0;j<10;j++)
		{
			s.Format("w[%d][%d]:%f\n",i,j,bpnet->w[i][j]);
			str.Insert(str.GetLength(),s);
		}
		str.Insert(str.GetLength(),"\n");
	}
	str.Insert(str.GetLength(),"输出结点权值:\n");
	for(i=0;i<10;i++)
	{
		for(j=0;j<4;j++)
		{
			s.Format("w1[%d][%d]:%f\n",i,j,bpnet->w1[i][j]);
			str.Insert(str.GetLength(),s);
		}
		str.Insert(str.GetLength(),"\n");
	}
	if(cf.Open("quanzhi.txt",CFile::modeCreate|CFile::modeWrite))
	{
		cf.WriteString(str);
		cf.Close();
	}
	EndWaitCursor();

}

void CDynSplitView2::OnBpTest() 
{
	double p[500][5],data[5];
	int i,j;
	int samplenum=500;
	int innum=bpnet->inNum;
	int outnum=bpnet->outNum;

	for(i=0;i<10;i++)
		for(j=0;j<50;j++)
		{
			int k1,k2;
			for(k1=0;k1<5;k1++)
			{
				double num=0.0;	
				for(k2=0;k2<5;k2++)
					num+=classify->pattern[i].feature[j][k1*5+k2];
				p[i+j*10][k1]=num;
			}
		}
	CString s,str;

	for(i=0;i<samplenum;i++)
	{
		for(j=0;j<5;j++)
			data[j]=p[i][j];
		bpnet->sim(data);
		int d;
		d=(int)(bpnet->shuchu[0]+bpnet->shuchu[1]*2+bpnet->shuchu[2]*4+bpnet->shuchu[3]*8+0.5);
		str.Format("%d\t%d           %d\n",i,i%10,d);
		s.Insert(s.GetLength(),str);
	}
	s.Insert(-1,"序号   已知样品    验证结果\n");
	s.Insert(-1,"****************************************\n");
	s.Insert(-1,"*样品库训练集，神经网络自动分类输出结果*\n");
	s.Insert(-1,"****************************************\n");
	CStdioFile cf;
	if(cf.Open("bpnet.txt",CFile::modeCreate|CFile::modeWrite))
	{
		cf.WriteString(s);
		cf.Close();
	}
	WinExec("notepad.exe bpnet.txt",SW_SHOW);
}

void CDynSplitView2::OnBpClassify() 
{
	double data[5];
	int innum=bpnet->inNum;
	int i,j;

	for(i=0;i<5;i++)
	{
		double num=0.0;	
		for(j=0;j<5;j++)
			num+=classify->testsample[i*5+j];
		data[i]=num;
	}

	bpnet->sim(data);
	number=(int)(bpnet->shuchu[0]+bpnet->shuchu[1]*2+bpnet->shuchu[2]*4+bpnet->shuchu[3]*8+0.5);
	CString str;
	str.Format("应用神经网络算法，将25维特征垂直投影降维至5维，\n分类识别结果为：%d",number);
	AfxMessageBox(str,MB_OK,NULL);
	Invalidate();
}

void CDynSplitView2::OnMenuBpquanzhi() 
{
	WinExec("notepad.exe quanzhi.txt",SW_SHOW);
	
}

void CDynSplitView2::OnMenuShihanshu() 
{
	BeginWaitCursor();
	number=classify->Shihanshu();
	EndWaitCursor();
	CString str;
	str.Format("应用势函数法，\n自动分类识别结果为：%d",number);
	AfxMessageBox(str,MB_OK,NULL);	
	Invalidate();
}





void CDynSplitView2::OnCancelMode() 
{
	CView::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}


void CDynSplitView2::OnCaptureChanged(CWnd *pWnd) 
{
	// TODO: Add your message handler code here
	
	CView::OnCaptureChanged(pWnd);
}
