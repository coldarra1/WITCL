// WaveletPJDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XBPJ_LRY.h"
#include "WaveletPJDlg.h"
#include "CDib.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWaveletPJDlg dialog


CWaveletPJDlg::CWaveletPJDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWaveletPJDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWaveletPJDlg)
	m_col = 0;
	//}}AFX_DATA_INIT
}


void CWaveletPJDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWaveletPJDlg)
	DDX_Text(pDX, IDC_EDIT2, m_col);
	DDV_MinMaxInt(pDX, m_col, 5, 50);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWaveletPJDlg, CDialog)
	//{{AFX_MSG_MAP(CWaveletPJDlg)
	ON_BN_CLICKED(IDC_OpenImage1, OnOpenImage1)
	ON_BN_CLICKED(IDC_OpenImage2, OnOpenImage2)
	ON_BN_CLICKED(IDC_Img1WaveletTran, OnImg1WaveletTran)
	ON_BN_CLICKED(IDC_Img2WaveletTran, OnImg2WaveletTran)
	ON_BN_CLICKED(IDC_WaveletPJ, OnWaveletPJ)
	ON_BN_CLICKED(IDC_ReConstruct, OnReConstruct)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWaveletPJDlg message handlers

void CWaveletPJDlg::OnOpenImage1() 
{
	// TODO: Add your control notification handler code here
//	Invalidate();//清屏
	
	
	int i,j;
	CString cfilename;
	char  szFilter[] = "Bmp Files (*.bmp)|*.bmp|All Files (*.*)|*.*||";
	CFileDialog fdlg(TRUE, "BMP", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);
	if(fdlg.DoModal() == IDOK)
		//	return FALSE;
	{
		cfilename=fdlg.GetPathName();	
	//装载bmp文件,获取图像信息,读取图像数据
	m_dib1.LoadFromFile(cfilename);
	
    //图像长宽，每行字节数,数据区指针
	Height1=m_dib1.GetH();
	Width1=m_dib1.GetW();
	m_bytewidth1=m_dib1.m_ByteWidth;
	m_pdata1=new BYTE[Height1*m_bytewidth1];
	m_pdata1=m_dib1.m_pDIBData;

	//在对话框上显示原图
	CDC *pDC=GetDC();
	for(i=0;i<Height1;i++)
		for(j=0;j<Width1;j++)
		{
			if(m_dib1.m_pBMI->bmiHeader.biBitCount==8)
				pDC->SetPixel(j,i+80,RGB(m_pdata1[(Height1-i-1)*m_bytewidth1+j],m_pdata1[(Height1-i-1)*m_bytewidth1+j],m_pdata1[(Height1-i-1)*m_bytewidth1+j]));
			else if(m_dib1.m_pBMI->bmiHeader.biBitCount==24)
			{
				pDC->SetPixel(j,i+80,RGB(m_pdata1[(Height1-i-1)*m_bytewidth1+j*3+2],m_pdata1[(Height1-i-1)*m_bytewidth1+j*3+1],m_pdata1[(Height1-i-1)*m_bytewidth1+j*3]));
			}
		}
	}	
	
}

void CWaveletPJDlg::OnOpenImage2() 
{
	// TODO: Add your control notification handler code here
	int i,j;
	CString cfilename;
	char  szFilter[] = "Bmp Files (*.bmp)|*.bmp|All Files (*.*)|*.*||";
	CFileDialog fdlg(TRUE, "BMP", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		szFilter);
	if(fdlg.DoModal() == IDOK)
		//	return FALSE;
	{
		cfilename=fdlg.GetPathName();
	
	//装载bmp文件,获取图像信息,读取图像数据
	m_dib2.LoadFromFile(cfilename);
    //图像长宽，每行字节数,数据区指针
	Height2=m_dib2.GetH();
	Width2=m_dib2.GetW();
	m_bytewidth2=m_dib2.m_ByteWidth;
	m_pdata2=new BYTE[Height2*m_bytewidth2];
	m_pdata2=m_dib2.m_pDIBData;
	
	//在对话框上显示原图
	CDC *pDC=GetDC();
	for(i=0;i<Height2;i++)
		for(j=0;j<Width2;j++)
		{
			if(m_dib2.m_pBMI->bmiHeader.biBitCount==8)
				pDC->SetPixel(j,i+440,RGB(m_pdata2[(Height2-i-1)*m_bytewidth2+j],m_pdata2[(Height2-i-1)*m_bytewidth2+j],m_pdata2[(Height2-i-1)*m_bytewidth2+j]));
			else if(m_dib2.m_pBMI->bmiHeader.biBitCount==24)
			{
				pDC->SetPixel(j,i+440,RGB(m_pdata2[(Height2-i-1)*m_bytewidth2+j*3+2],m_pdata2[(Height2-i-1)*m_bytewidth2+j*3+1],m_pdata2[(Height2-i-1)*m_bytewidth2+j*3]));
			}
		}	
	}		
}

void CWaveletPJDlg::OnImg1WaveletTran() 
{
	// TODO: Add your control notification handler code here
    pDatewavelet1 = new double[Height1*m_bytewidth1];
	int i,j;
		
	for(i=0;i<Height1;i++)
	    for(j=0;j<Width1;j++)
			{
				pDatewavelet1[i*m_bytewidth1+j]=m_pdata1[i*m_bytewidth1+j];
			}
	//int level=1;
	//for(i=1;i<=level;i++)
	//WaveletTran(m_dib1,pDatewavelet1,i,Height1,Width1,m_bytewidth1);
	WaveletTran(m_dib1,pDatewavelet1,1,Height1,Width1,m_bytewidth1);


	//将小波变换系数映射到0-255
	BYTE *lpTemp = new BYTE[Height1*m_bytewidth1];
	double max=0, min=0;
	double coef;
	for(i=0;i<Height1;i++)
		for(j=0;j<Width1;j++)
		{ 
			if(pDatewavelet1[(Height1-i-1)*m_bytewidth1+j]>=max)
				max=pDatewavelet1[(Height1-i-1)*m_bytewidth1+j];	
			if(pDatewavelet1[(Height1-i-1)*m_bytewidth1+j]<=min)
				min=pDatewavelet1[(Height1-i-1)*m_bytewidth1+j];
		}
	coef=max-min;	
	for(i=0;i<Height1;i++)
		for(j=0;j<Width1;j++)
		{
			lpTemp[(Height1-i-1)*m_bytewidth1+j]=(BYTE)((pDatewavelet1[(Height1-i-1)*m_bytewidth1+j]-min)*255/coef);
		}

	//在对话框上显示图1小波变换结果
	CDC *pDC=GetDC();
	for(i=0;i<Height1;i++)
		for(j=0;j<Width1;j++)
		{
			if(m_dib1.m_pBMI->bmiHeader.biBitCount==8)
				pDC->SetPixel(j+300,i+80,RGB(lpTemp[(Height1-i-1)*m_bytewidth1+j],lpTemp[(Height1-i-1)*m_bytewidth1+j],lpTemp[(Height1-i-1)*m_bytewidth1+j]));
			else if(m_dib1.m_pBMI->bmiHeader.biBitCount==24)
			{
				pDC->SetPixel(j+300,i+80,RGB(lpTemp[(Height1-i-1)*m_bytewidth1+j*3+2],lpTemp[(Height1-i-1)*m_bytewidth1+j*3+1],lpTemp[(Height1-i-1)*m_bytewidth1+j*3]));
			}
		}
}	

void CWaveletPJDlg::OnImg2WaveletTran() 
{
	// TODO: Add your control notification handler code here
    pDatewavelet2 = new double[Height2*m_bytewidth2];
	int i,j;
		
	for(i=0;i<Height2;i++)
	    for(j=0;j<Width2;j++)
			{
				pDatewavelet2[i*m_bytewidth2+j]=m_pdata2[i*m_bytewidth2+j];
			}
	int level=1;
	for(i=1;i<=level;i++)
	WaveletTran(m_dib2,pDatewavelet2,i,Height2,Width2,m_bytewidth2);

	//将小波变换系数映射到0-255
	BYTE *lpTemp = new BYTE[Height2*m_bytewidth2];
	double max=0, min=0;
	double coef;
	for(i=0;i<Height2;i++)
		for(j=0;j<Width2;j++)
		{ 
			if(pDatewavelet2[(Height2-i-1)*m_bytewidth2+j]>=max)
				max=pDatewavelet2[(Height2-i-1)*m_bytewidth2+j];	
			if(pDatewavelet2[(Height2-i-1)*m_bytewidth2+j]<=min)
				min=pDatewavelet2[(Height2-i-1)*m_bytewidth2+j];
		}
	coef=max-min;	
	for(i=0;i<Height2;i++)
		for(j=0;j<Width2;j++)
		{
			lpTemp[(Height2-i-1)*m_bytewidth2+j]=(BYTE)((pDatewavelet2[(Height2-i-1)*m_bytewidth2+j]-min)*255/coef);
		}

	//在对话框上显示图2小波变换结果
	CDC *pDC=GetDC();
	for(i=0;i<Height2;i++)
		for(j=0;j<Width2;j++)
		{
			if(m_dib1.m_pBMI->bmiHeader.biBitCount==8)
				pDC->SetPixel(j+300,i+440,RGB(lpTemp[(Height2-i-1)*m_bytewidth2+j],lpTemp[(Height2-i-1)*m_bytewidth2+j],lpTemp[(Height2-i-1)*m_bytewidth2+j]));
			else if(m_dib1.m_pBMI->bmiHeader.biBitCount==24)
			{
				pDC->SetPixel(j+300,i+440,RGB(lpTemp[(Height2-i-1)*m_bytewidth2+j*3+2],lpTemp[(Height2-i-1)*m_bytewidth2+j*3+1],lpTemp[(Height2-i-1)*m_bytewidth2+j*3]));
			}
		}
}

void CWaveletPJDlg::OnWaveletPJ() 
{
	// TODO: Add your control notification handler code here
	double *Pdib1_LeftUp = new double[Height1*m_bytewidth1/4];
	double *Pdib1_LeftDown = new double[Height1*m_bytewidth1/4];
	double *Pdib1_RightUp = new double[Height1*m_bytewidth1/4];
	double *Pdib1_RightDown = new double[Height1*m_bytewidth1/4];

	double *Pdib2_LeftUp = new double[Height2*m_bytewidth2/4];
	double *Pdib2_LeftDown = new double[Height2*m_bytewidth2/4];
	double *Pdib2_RightUp = new double[Height2*m_bytewidth2/4];
	double *Pdib2_RightDown = new double[Height2*m_bytewidth2/4];

    int i,j;
	//分别赋值
	for (i=0;i<Height1/2;i++)
	{
		for (j=0;j<m_bytewidth1/2;j++)
		{
               Pdib1_LeftUp[i*m_bytewidth1/2+j]=pDatewavelet1[i*m_bytewidth1+j];
               Pdib1_RightUp[i*m_bytewidth1/2+j]=pDatewavelet1[i*m_bytewidth1+m_bytewidth1/2+j];
			   Pdib1_LeftDown[i*m_bytewidth1/2+j]=pDatewavelet1[i*m_bytewidth1+Height1/2*m_bytewidth1+j];
			   Pdib1_RightDown[i*m_bytewidth1/2+j]=pDatewavelet1[i*m_bytewidth1+Height1/2*m_bytewidth1+m_bytewidth1/2+j];		
		}
	}

	for (i=0;i<Height2/2;i++)
	{
		for (j=0;j<m_bytewidth2/2;j++)
		{
               Pdib2_LeftUp[i*m_bytewidth2/2+j]=pDatewavelet2[i*m_bytewidth2+j];
               Pdib2_RightUp[i*m_bytewidth2/2+j]=pDatewavelet2[i*m_bytewidth2+m_bytewidth2/2+j];
			   Pdib2_LeftDown[i*m_bytewidth2/2+j]=pDatewavelet2[i*m_bytewidth2+Height2/2*m_bytewidth2+j];
			   Pdib2_RightDown[i*m_bytewidth2/2+j]=pDatewavelet2[i*m_bytewidth2+Height2/2*m_bytewidth2+m_bytewidth2/2+j];		
		}
	}

    //四部分分别拼接
	WaveletPJACT(Pdib_LeftUp,Pdib1_LeftUp,Pdib2_LeftUp,1);
	WaveletPJACT(Pdib_RightUp,Pdib1_RightUp,Pdib2_RightUp,2);
	WaveletPJACT(Pdib_LeftDown,Pdib1_LeftDown,Pdib2_LeftDown,3);
	WaveletPJACT(Pdib_RightDown,Pdib1_RightDown,Pdib2_RightDown,4);


	//寻找四块中的最小宽度
	int MinNewWidth=NewWidth1;
	if (MinNewWidth>NewWidth2)
	{MinNewWidth=NewWidth2;}
	if (MinNewWidth>NewWidth3)
	{MinNewWidth=NewWidth3;}
	if (MinNewWidth>NewWidth4)
	{MinNewWidth=NewWidth4;}

	Height=Height1;
	Width=MinNewWidth*2;
	Pdib=new double[MinNewWidth*2*Height1];
	for (i=0;i<Height/2;i++)//拷贝左上角数据
	{
		for (j=0;j<MinNewWidth;j++)
		{
             Pdib[i*Width+j]=Pdib_LeftUp[i*NewWidth1+j];
		}
        
	}
	for (i=0;i<Height/2;i++)//拷贝右上角数据
	{
		for (j=0;j<MinNewWidth;j++)
		{
             Pdib[i*Width+MinNewWidth+j]=Pdib_RightUp[i*NewWidth2+j];
		}
        
	}
	for (i=0;i<Height/2;i++)//拷贝左下角数据
	{
		for (j=0;j<MinNewWidth;j++)
		{
             Pdib[(i+Height/2)*Width+j]=Pdib_LeftDown[i*NewWidth3+j];
		}
        
	}
	for (i=0;i<Height/2;i++)//拷贝右下角数据
	{
		for (j=0;j<MinNewWidth;j++)
		{
             Pdib[(i+Height/2)*Width+MinNewWidth+j]=Pdib_RightDown[i*NewWidth4+j];
		}
        
	}

	
	//将小波变换系数映射到0-255
	BYTE *lpTemp = new BYTE[Height*Width];
	double max=0, min=0;
	double coef;
	for(i=0;i<Height;i++)
		for(j=0;j<Width;j++)
		{ 
			if(Pdib[(Height-i-1)*Width+j]>=max)
				max=Pdib[(Height-i-1)*Width+j];	
			if(Pdib[(Height-i-1)*Width+j]<=min)
				min=Pdib[(Height-i-1)*Width+j];
		}
	coef=max-min;	
	for(i=0;i<Height;i++)
		for(j=0;j<Width;j++)
		{
			lpTemp[(Height-i-1)*Width+j]=(BYTE)((Pdib[(Height-i-1)*Width+j]-min)*255/coef);
		}

	//在对话框上显示小波域拼接图
	CDC *pDC=GetDC();
	for(i=0;i<Height;i++)
		for(j=0;j<Width;j++)
		{
				pDC->SetPixel(j+700,i+80,RGB(lpTemp[(Height-i-1)*Width+j],lpTemp[(Height-i-1)*Width+j],lpTemp[(Height-i-1)*Width+j]));
		}		

}

void CWaveletPJDlg::WaveletPJACT(double *total,double *first,double *second,int flag)
{

	UpdateData(true);
	int i,j;
	int PJ_Col=m_col;
	double First[500];
	double *Second=new double[PJ_Col];
	double Coefficient[500];
	
    //初始化
	for (i=0;i<PJ_Col;i++)
	{Second[i]=0;}
	for (i=0;i<m_bytewidth1/2-PJ_Col;i++)
	{First[i]=0;}



    double E_Second,totalS=0;

	for (i=0;i<PJ_Col;i++)
	{
		for (j=0;j<Height2/2;j++)
		{
		Second[i]=Second[i]+second[j*m_bytewidth2/2+i];
		}
		Second[i]=Second[i]/Height2/2;
      	totalS=totalS+Second[i];	
	}
	E_Second=totalS/PJ_Col;



	for (i=0;i<m_bytewidth1-PJ_Col;i++)
	{
		for (j=0;j<Height1/2;j++)
		{
		First[i]=First[i]+first[j*m_bytewidth1/2+i];
		}
		First[i]=First[i]/Height1/2;
	}

	
	double E_First;
	double up,down1,down2,down;
	double A_E_First,B_E_Second;
	double *A=new double[PJ_Col];

	for (i=0;i<m_bytewidth1/2-PJ_Col;i++)
	{
		    up=0;
            down1=0;
            down2=0;
            down=0;
            E_First=0;

            for (int k=0,j=i;j<i+PJ_Col;j++,k++)
            { A[k]=First[j];}

			for (j=0;j<PJ_Col;j++)
			{
				E_First=E_First+A[j];
			}
			E_First=E_First/PJ_Col;

			//求分子
            for (j=0;j<PJ_Col;j++)
            {
				A_E_First=fabs(A[j]-E_First);
				B_E_Second=fabs(Second[j]-E_Second);
				up=up+A_E_First*B_E_Second;
            }
			//求分母
	         for (j=0;j<PJ_Col;j++)
	         {
                 A_E_First=pow((A[j]-E_First),2);
				 down1=down1+A_E_First;
	         }
	         for (j=0;j<PJ_Col;j++)
	         {
                 B_E_Second=pow((Second[j]-E_Second),2);
				 down2=down2+B_E_Second;
	         }
			 down=pow((down1*down2),1/2);

			 //系数
			 Coefficient[i]=up/down;
			 Coefficient[i]=Coefficient[i]*10000;
	}


	//得到系数最大的列
	double MaxCoefficient=0;
	int MaxCoeCol=0;
	for (i=0;i<m_bytewidth1/2-PJ_Col;i++)
	{
        if (MaxCoefficient<Coefficient[i])
        {
			MaxCoefficient=Coefficient[i];
			MaxCoeCol=i;
        }
	}
    
	
	//整合
	total = new double[Height1/2*MaxCoeCol+Height2*m_bytewidth2/4];
	for (j=0;j<Height1/2;j++)
	{
     	for (i=0;i<MaxCoeCol;i++)
		{
		total[j*(MaxCoeCol+m_bytewidth2/2)+i]=first[j*m_bytewidth1/2+i];
		}
	}
    for (j=0;j<Height1/2;j++)
    {
      for (i=0;i<m_bytewidth2/2;i++)
      {
		  total[j*(MaxCoeCol+m_bytewidth2/2)+MaxCoeCol+i]=second[j*m_bytewidth2/2+i];
      }
    }


    
	
if (flag==1)
{
   NewWidth1=MaxCoeCol+m_bytewidth2/2;
   NewHeight1=Height1/2;
	Pdib_LeftUp = new double[NewWidth1*NewHeight1];
	for (i=0;i<NewHeight1;i++)
	{
		for (j=0;j<NewWidth1;j++)
		{
		Pdib_LeftUp[i*NewWidth1+j]=total[i*NewWidth1+j];	
		}
	}
}
if (flag==2)
{
   NewWidth2=MaxCoeCol+m_bytewidth2/2;
   NewHeight2=Height1/2;
	Pdib_RightUp = new double[NewWidth2*NewHeight2];
	for (i=0;i<NewHeight2;i++)
	{
		for (j=0;j<NewWidth2;j++)
		{
		Pdib_RightUp[i*NewWidth2+j]=total[i*NewWidth2+j];	
		}
	}
}
if (flag==3)
{
   NewWidth3=MaxCoeCol+m_bytewidth2/2;
   NewHeight3=Height1/2;
	Pdib_LeftDown = new double[NewWidth3*NewHeight3];
	for (i=0;i<NewHeight3;i++)
	{
		for (j=0;j<NewWidth3;j++)
		{
		Pdib_LeftDown[i*NewWidth3+j]=total[i*NewWidth3+j];	
		}
	}
}
if (flag==4)
{
   NewWidth4=MaxCoeCol+m_bytewidth2/2;
   NewHeight4=Height1/2;
	Pdib_RightDown = new double[NewWidth4*NewHeight4];
	for (i=0;i<NewHeight4;i++)
	{
		for (j=0;j<NewWidth4;j++)
		{
		Pdib_RightDown[i*NewWidth4+j]=total[i*NewWidth4+j];	
		}
	}

}


}
void CWaveletPJDlg::WaveletTran(CDib m_dib,double *Source, int level,long int Height,long int Width,long int m_bytewidth)
{
    int i,j;
   

	double *Temp = new double[Height*m_bytewidth];
	for(i=0;i<Height;i++)
		for(j=0;j<Width;j++)
		{
			Temp[i*m_bytewidth+j]=Source[(Height-i-1)*m_bytewidth+j];
		}
		
    double *Rlow = new double[Height*m_bytewidth];//依次加，所有
    double *Rhigh = new double[Height*m_bytewidth];//依次减，所有
	
	double *Clow = new double[Height*m_bytewidth/2];//抽取偶列
    double *Chigh = new double[Height*m_bytewidth/2];//抽取偶列

    double *LL1 = new double[Height*m_bytewidth/2];
    double *LH1 = new double[Height*m_bytewidth/2];
    double *HL1 = new double[Height*m_bytewidth/2];
    double *HH1 = new double[Height*m_bytewidth/2];
	
	if(m_dib.m_pBMI->bmiHeader.biBitCount==8)
	{
		/*行变换*/
		//行低，行高
		for(i=0;i<Height;i++)
			for(j=0;j<Width-1;j++)
			{
				Rlow[i*m_bytewidth+j]=Temp[i*m_bytewidth+j]+Temp[i*m_bytewidth+j+1];
				Rhigh[i*m_bytewidth+j]=Temp[i*m_bytewidth+j+1]-Temp[i*m_bytewidth+j];
			}
		 //最后一列处理
         for(i=0;i<Height;i++)
		 {
               Rlow[i*m_bytewidth+Width-1]=Temp[i*m_bytewidth+Width-1]+Temp[i*m_bytewidth];
			   Rhigh[i*m_bytewidth+Width-1]=Temp[i*m_bytewidth]-Temp[i*m_bytewidth+Width-1];
		 }
		 //抽取偶列
		 for(i=0;i<Height;i++)
			 for(j=0;j<Width/2;j++)
			 {
      		     Clow[i*m_bytewidth/2+j]=Rlow[i*m_bytewidth+j*2+1];
				 Chigh[i*m_bytewidth/2+j]=Rhigh[i*m_bytewidth+j*2+1];
			 }
	
		/*列变换*/
		//列低，列高
        for(i=0;i<Height-1;i++)
			for(j=0;j<Width/2;j++)
			{
				LL1[i*m_bytewidth/2+j]=Clow[i*m_bytewidth/2+j]+Clow[(i+1)*m_bytewidth/2+j];
				LH1[i*m_bytewidth/2+j]=Clow[(i+1)*m_bytewidth/2+j]-Clow[i*m_bytewidth/2+j];
                HL1[i*m_bytewidth/2+j]=Chigh[i*m_bytewidth/2+j]+Chigh[(i+1)*m_bytewidth/2+j];
				HH1[i*m_bytewidth/2+j]=Chigh[(i+1)*m_bytewidth/2+j]-Chigh[i*m_bytewidth/2+j];
			}
		//最后一行处理
		for(i=0;i<Width/2;i++)
		{
			  LL1[(Height-1)*m_bytewidth/2+i]=Clow[i]+Clow[(Height-1)*m_bytewidth/2+i];
			  LH1[(Height-1)*m_bytewidth/2+i]=Clow[i]-Clow[(Height-1)*m_bytewidth/2+i];
              HL1[(Height-1)*m_bytewidth/2+i]=Chigh[i]+Chigh[(Height-1)*m_bytewidth/2+i];
			  HH1[(Height-1)*m_bytewidth/2+i]=Chigh[i]-Chigh[(Height-1)*m_bytewidth/2+i];
		}
	    //对四分量取偶行得一次小波变换结果
		for(i=0;i<Height/2;i++)
			for(j=0;j<Width/2;j++)
			{
                Temp[i*m_bytewidth+j]=LL1[(i*2+1)*m_bytewidth/2+j]/2.0;//左上
				Temp[i*m_bytewidth+j+Width/2]=LH1[(i*2+1)*m_bytewidth/2+j]/2.0;//右上
				Temp[(i+Height/2)*m_bytewidth+j]=HL1[(i*2+1)*m_bytewidth/2+j]/2.0;//左下
				Temp[(i+Height/2)*m_bytewidth+j+Width/2]=HH1[(i*2+1)*m_bytewidth/2+j]/2.0;//右下
			}


    //拷贝到存放图1的小波变换结果的变量中
	for(i=0;i<Height;i++)
		for(j=0;j<Width;j++)
		{
				Source[(Height-i-1)*m_bytewidth+j]=Temp[i*m_bytewidth+j];
		}


	}
	else
		AfxMessageBox("只处理灰度图!");
}



void CWaveletPJDlg::OnReConstruct() 
{
	int i,j;

	//计算划分子块	
	double *Temp = new double[Height*Width];
    for(i=0;i<Height;i++)
		for(j=0;j<Width;j++)
		{
			Temp[i*Width+j]=Pdib[(Height-i-1)*Width+j];
		}
		
	double *Temp1 = new double[Height*Width];
	double *Temp2 = new double[Height*Width];
	double *lptemp1 = new double[Height*Width];
    double *lptemp2 = new double[Height*Width];
	
    double *Rlow = new double[Height*Width];
    double *Rhigh = new double[Height*Width];
	
    for(i=0;i<Height;i++)
		for(j=0;j<Width;j++)
		{
            Rlow[i*Width+j]=0;
			Rhigh[i*Width+j]=0;
			lptemp1[i*Width+j]=0;
			lptemp2[i*Width+j]=0;
		}
		
	double *Clow = new double[Height*Width/2];
	double *Chigh = new double[Height*Width/2];
		
	double *LL1 = new double[Height*Width/2];
	double *LH1 = new double[Height*Width/2];
	double *HL1 = new double[Height*Width/2];
	double *HH1 = new double[Height*Width/2];
	for(i=0;i<Height;i++)
		for(j=0;j<Width/2;j++)
		{
			Clow[i*Width/2+j]=0;
			Chigh[i*Width/2+j]=0;
			LL1[i*Width/2+j]=0;
			LH1[i*Width/2+j]=0;
			HL1[i*Width/2+j]=0;
			HH1[i*Width/2+j]=0;
		}
			
	//将四分量分别补零扩展
	for(i=0;i<Height/2;i++)
		for(j=0;j<Width/2;j++)
		{
            LL1[(i*2+1)*Width/2+j]=Temp[i*Width+j];//左上
			LH1[(i*2+1)*Width/2+j]=Temp[i*Width+j+Width/2];//右上
			HL1[(i*2+1)*Width/2+j]=Temp[(i+Height/2)*Width+j];//左下
			HH1[(i*2+1)*Width/2+j]=Temp[(i+Height/2)*Width+j+Width/2];//右下
		}
	/*列变换*/
	//列低，列高
	for(i=0;i<Height-1;i++)
		for(j=0;j<Width/2;j++)
		{
			Clow[i*Width/2+j]=LL1[i*Width/2+j]+LL1[(i+1)*Width/2+j]+LH1[i*Width/2+j]-LH1[(i+1)*Width/2+j];
			Chigh[i*Width/2+j]=HL1[i*Width/2+j]+HL1[(i+1)*Width/2+j]+HH1[i*Width/2+j]-HH1[(i+1)*Width/2+j];
		}
	//最后一行处理
	for(i=0;i<Width/2;i++)
	{
		Clow[(Height-1)*Width/2+i]=LL1[i]+LL1[(Height-1)*Width/2+i]+LH1[(Height-1)*Width/2+i]-LH1[i];	
		Chigh[(Height-1)*Width/2+i]=HL1[i]+HL1[(Height-1)*Width/2+i]+HH1[(Height-1)*Width/2+i]-HH1[i];
	}
	/*行变换*/
	//补零
	for(i=0;i<Height;i++)
		for(j=0;j<Width/2;j++)
		{
			Rlow[i*Width+j*2+1]=Clow[i*Width/2+j];
			Rhigh[i*Width+j*2+1]=Chigh[i*Width/2+j];
		}
	//行低，行高
	for(i=0;i<Height;i++)
		for(j=0;j<Width-1;j++)
		{
			lptemp1[i*Width+j]=Rlow[i*Width+j]+Rlow[i*Width+j+1];
			lptemp2[i*Width+j]=Rhigh[i*Width+j]-Rhigh[i*Width+j+1];
		}
	//最后一列处理
	for(i=0;i<Height;i++)
		{
		    lptemp1[i*Width+Width-1]=Rlow[i*Width+Width-1]+Rlow[i*Width];
			lptemp2[i*Width+Width-1]=Rhigh[i*Width+Width-1]-Rhigh[i*Width];
		}
	//合并
	for(i=0;i<Height;i++)
		for(j=0;j<Width;j++)
		{
			Temp1[i*Width+j]=(lptemp1[i*Width+j]+lptemp2[i*Width+j])/2.0;
		}
	//行移位
	for(i=0;i<Height;i++)
	{
		for(j=1;j<Width;j++)
            Temp2[i*Width+j]=Temp1[i*Width+j-1];
		Temp2[i*Width]=Temp1[i*Width+Width-1];
	}
	//列移位
	for(j=0;j<Width;j++)
	{
        for(i=1;i<Height;i++)
            Temp[i*Width+j]=Temp2[(i-1)*Width+j];
		Temp[j]=Temp2[(Height-1)*Width+j];
	}


	PdibSuccess=new double[Height*Width];
    for(i=0;i<Height;i++)
		for(j=0;j<Width;j++)
		{
			PdibSuccess[(Height-i-1)*Width+j]=Temp[i*Width+j];
		}	
	



    //将小波变换映射到0-255
	BYTE *lpTemp = new BYTE[Height*Width];
	for(i=0;i<Height;i++)
		for(j=0;j<Width;j++)
		{
			if(PdibSuccess[(Height-i-1)*Width+j]>255)
				PdibSuccess[(Height-i-1)*Width+j]=255;
			if(PdibSuccess[(Height-i-1)*Width+j]<0)
				PdibSuccess[(Height-i-1)*Width+j]=0;
			lpTemp[(Height-i-1)*Width+j]=(BYTE)(PdibSuccess[(Height-i-1)*Width+j]);
		}
	//在对话框上图
	CDC *pDC=GetDC();
	for(i=0;i<Height;i++)
		for(j=0;j<Width;j++)
		{
			pDC->SetPixel(j+700,i+440,RGB(lpTemp[(Height-i-1)*Width+j],lpTemp[(Height-i-1)*Width+j],lpTemp[(Height-i-1)*Width+j]));
		}

}


void CWaveletPJDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
Invalidate();	
}
