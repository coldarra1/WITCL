// Wavelet.cpp : implementation file
//

#include "stdafx.h"
#include "XBPJ_LRY.h"
#include "Wavelet.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWavelet dialog


CWavelet::CWavelet(CWnd* pParent /*=NULL*/)
	: CDialog(CWavelet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWavelet)
	m_level = 0;
	//}}AFX_DATA_INIT
}


void CWavelet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWavelet)
	DDX_Text(pDX, IDC_EDIT1, m_level);
	DDV_MinMaxInt(pDX, m_level, 0, 8);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWavelet, CDialog)
	//{{AFX_MSG_MAP(CWavelet)
	ON_BN_CLICKED(IDC_openimg, Onopenimg)
	ON_BN_CLICKED(IDC_waveletfj, Onwaveletfj)
	ON_BN_CLICKED(IDC_waveletcg, Onwaveletcg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWavelet message handlers

void CWavelet::Onopenimg() 
{
	// TODO: Add your control notification handler code here
	int i,j;
	CString cfilename;
	char  szFilter[] = "Bmp Files (*.bmp)|*.bmp|All Files (*.*)|*.*||";
	CFileDialog fdlg(TRUE, "BMP", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);
	if(fdlg.DoModal() == IDOK)
		//	return FALSE;
	{
		cfilename=fdlg.GetPathName();	
	//装载bmp文件,获取图像信息,读取图像数据
	m_dib.LoadFromFile(cfilename);
	
    //图像长宽，每行字节数,数据区指针
	Height=m_dib.GetH();
	Width=m_dib.GetW();
	m_bytewidth=m_dib.m_ByteWidth;
	m_pdata=new BYTE[Height*m_bytewidth];
	m_pdata=m_dib.m_pDIBData;

	//在对话框上显示原图
	CDC *pDC=GetDC();
	for(i=0;i<Height;i++)
		for(j=0;j<Width;j++)
		{
			if(m_dib.m_pBMI->bmiHeader.biBitCount==8)
				pDC->SetPixel(j+30,i+80,RGB(m_pdata[(Height-i-1)*m_bytewidth+j],m_pdata[(Height-i-1)*m_bytewidth+j],m_pdata[(Height-i-1)*m_bytewidth+j]));
			else if(m_dib.m_pBMI->bmiHeader.biBitCount==24)
			{
				pDC->SetPixel(j+30,i+80,RGB(m_pdata[(Height-i-1)*m_bytewidth+j*3+2],m_pdata[(Height-i-1)*m_bytewidth+j*3+1],m_pdata[(Height-i-1)*m_bytewidth+j*3]));
			}
		}
	}	
		
}

void CWavelet::Onwaveletfj() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	pDatewavelet = new double[Height*m_bytewidth];
	int i,j;
		
	for(i=0;i<Height;i++)
	    for(j=0;j<Width;j++)
			{
				pDatewavelet[i*m_bytewidth+j]=m_pdata[i*m_bytewidth+j];
			}
	int level=m_level;
	for(i=1;i<=level;i++)
	WaveletTran(m_dib,pDatewavelet,i,Height,Width,m_bytewidth);


	
	BYTE *lpTemp = new BYTE[Height*m_bytewidth];
	double max=0, min=0;
	double coef;
	for(i=0;i<Height;i++)
		for(j=0;j<Width;j++)
		{ 
			if(pDatewavelet[(Height-i-1)*m_bytewidth+j]>=max)
				max=pDatewavelet[(Height-i-1)*m_bytewidth+j];	
			if(pDatewavelet[(Height-i-1)*m_bytewidth+j]<=min)
				min=pDatewavelet[(Height-i-1)*m_bytewidth+j];
		}
	coef=max-min;
	for(i=0;i<Height;i++)
		for(j=0;j<Width;j++)
		{
			lpTemp[(Height-i-1)*m_bytewidth+j]=(BYTE)((pDatewavelet[(Height-i-1)*m_bytewidth+j]-min)*255/coef);
		}
	
		
	//在对话框上显示变换后的图
	CDC *pDC=GetDC();
	for(i=0;i<Height;i++)
		for(j=0;j<Width;j++)
		{
			if(m_dib.m_pBMI->bmiHeader.biBitCount==8)
				pDC->SetPixel(j+320,i+80,RGB(lpTemp[(Height-i-1)*m_bytewidth+j],lpTemp[(Height-i-1)*m_bytewidth+j],lpTemp[(Height-i-1)*m_bytewidth+j]));
			else if(m_dib.m_pBMI->bmiHeader.biBitCount==24)
			{
				pDC->SetPixel(j+320,i+80,RGB(lpTemp[(Height-i-1)*m_bytewidth+j*3+2],lpTemp[(Height-i-1)*m_bytewidth+j*3+1],lpTemp[(Height-i-1)*m_bytewidth+j*3]));
			}
		}	
}

void CWavelet::WaveletTran(CDib m_dib,double *Source, int level,long int Height,long int Width,long int m_bytewidth)
{
    int i,j;
   
	//计算划分子块
    int m,n,k;
	m=(int)(pow(2,(level-1)*2));
    n=m*2;
    k=(int)(pow(2,(level-1)));

	double *Temp = new double[Height*m_bytewidth/m];
	for(i=0;i<Height/k;i++)
		for(j=0;j<Width/k;j++)
		{
			Temp[i*m_bytewidth/k+j]=Source[(Height-i-1)*m_bytewidth+j];
		}
		
    double *Rlow = new double[Height*m_bytewidth/m];
    double *Rhigh = new double[Height*m_bytewidth/m];
	
	double *Clow = new double[Height*m_bytewidth/n];
    double *Chigh = new double[Height*m_bytewidth/n];

    double *LL1 = new double[Height*m_bytewidth/n];
    double *LH1 = new double[Height*m_bytewidth/n];
    double *HL1 = new double[Height*m_bytewidth/n];
    double *HH1 = new double[Height*m_bytewidth/n];
	
	if(m_dib.m_pBMI->bmiHeader.biBitCount==8)
	{
		/*行变换*/
		//行低，行高
		for(i=0;i<Height/k;i++)
			for(j=0;j<Width/k-1;j++)
			{
				Rlow[i*m_bytewidth/k+j]=Temp[i*m_bytewidth/k+j]+Temp[i*m_bytewidth/k+j+1];
				Rhigh[i*m_bytewidth/k+j]=Temp[i*m_bytewidth/k+j+1]-Temp[i*m_bytewidth/k+j];
			}
		 //最后一列处理
         for(i=0;i<Height/k;i++)
		 {
               Rlow[i*m_bytewidth/k+Width/k-1]=Temp[i*m_bytewidth/k+Width/k-1]+Temp[i*m_bytewidth/k];
			   Rhigh[i*m_bytewidth/k+Width/k-1]=Temp[i*m_bytewidth/k]-Temp[i*m_bytewidth/k+Width/k-1];
		 }
		 //抽取偶列
		 for(i=0;i<Height/k;i++)
			 for(j=0;j<Width/(k*2);j++)
			 {
      		     Clow[i*m_bytewidth/(k*2)+j]=Rlow[i*m_bytewidth/k+j*2+1];
				 Chigh[i*m_bytewidth/(k*2)+j]=Rhigh[i*m_bytewidth/k+j*2+1];
			 }
	
		/*列变换*/
		//列低，列高
        for(i=0;i<Height/k-1;i++)
			for(j=0;j<Width/(k*2);j++)
			{
				LL1[i*m_bytewidth/(k*2)+j]=Clow[i*m_bytewidth/(k*2)+j]+Clow[(i+1)*m_bytewidth/(k*2)+j];
				LH1[i*m_bytewidth/(k*2)+j]=Clow[(i+1)*m_bytewidth/(k*2)+j]-Clow[i*m_bytewidth/(k*2)+j];
                HL1[i*m_bytewidth/(k*2)+j]=Chigh[i*m_bytewidth/(k*2)+j]+Chigh[(i+1)*m_bytewidth/(k*2)+j];
				HH1[i*m_bytewidth/(k*2)+j]=Chigh[(i+1)*m_bytewidth/(k*2)+j]-Chigh[i*m_bytewidth/(k*2)+j];
			}
		//最后一行处理
		for(i=0;i<Width/(k*2);i++)
		{
			  LL1[(Height/k-1)*m_bytewidth/(k*2)+i]=Clow[i]+Clow[(Height/k-1)*m_bytewidth/(k*2)+i];
			  LH1[(Height/k-1)*m_bytewidth/(k*2)+i]=Clow[i]-Clow[(Height/k-1)*m_bytewidth/(k*2)+i];
              HL1[(Height/k-1)*m_bytewidth/(k*2)+i]=Chigh[i]+Chigh[(Height/k-1)*m_bytewidth/(k*2)+i];
			  HH1[(Height/k-1)*m_bytewidth/(k*2)+i]=Chigh[i]-Chigh[(Height/k-1)*m_bytewidth/(k*2)+i];
		}
	    //对四分量取偶行得一次小波变换结果
		for(i=0;i<Height/(k*2);i++)
			for(j=0;j<Width/(k*2);j++)
			{
                Temp[i*m_bytewidth/k+j]=LL1[(i*2+1)*m_bytewidth/(k*2)+j]/2.0;//左上
				Temp[i*m_bytewidth/k+j+Width/(k*2)]=LH1[(i*2+1)*m_bytewidth/(k*2)+j]/2.0;//右上
				Temp[(i+Height/(k*2))*m_bytewidth/k+j]=HL1[(i*2+1)*m_bytewidth/(k*2)+j]/2.0;//左下
				Temp[(i+Height/(k*2))*m_bytewidth/k+j+Width/(k*2)]=HH1[(i*2+1)*m_bytewidth/(k*2)+j]/2.0;//右下
			}
		for(i=0;i<Height/k;i++)
			for(j=0;j<Width/k;j++)
			{
				Source[(Height-i-1)*m_bytewidth+j]=Temp[i*m_bytewidth/k+j];
			}
	}
	else
		AfxMessageBox("只处理灰度图!");

}




void CWavelet::Onwaveletcg() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	int i,j;
	int level=m_level;

	for(i=level;i>=1;i--)
	WaveRecstr(pDatewavelet,i);

	  	  

    //将小波变换系数映射到0-255
	BYTE *lpTemp = new BYTE[Height*m_bytewidth];
	for(i=0;i<Height;i++)
		for(j=0;j<Width;j++)
		{
			if(pDatewavelet[(Height-i-1)*m_bytewidth+j]>255)
				pDatewavelet[(Height-i-1)*m_bytewidth+j]=255;
			if(pDatewavelet[(Height-i-1)*m_bytewidth+j]<0)
				pDatewavelet[(Height-i-1)*m_bytewidth+j]=0;
			lpTemp[(Height-i-1)*m_bytewidth+j]=(BYTE)(pDatewavelet[(Height-i-1)*m_bytewidth+j]);
		}
	//在对话框上显示原图
	CDC *pDC=GetDC();
	for(i=0;i<Height;i++)
		for(j=0;j<Width;j++)
		{
			pDC->SetPixel(j+630,i+80,RGB(lpTemp[(Height-i-1)*m_bytewidth+j],lpTemp[(Height-i-1)*m_bytewidth+j],lpTemp[(Height-i-1)*m_bytewidth+j]));
		}






}
void CWavelet::WaveRecstr(double *WaveTran, int level)
{
	int i,j;

	//计算划分子块
    int m,n,k;
	m=(int)(pow(2,(level-1)*2));
    n=m*2;
    k=(int)(pow(2,(level-1)));
	
	double *Temp = new double[Height*m_bytewidth/m];
    for(i=0;i<Height/k;i++)
		for(j=0;j<Width/k;j++)
		{
			//Temp[(Height/k-i-1)*m_bytewidth/k+j]=WaveTran[(Height-i-1)*m_bytewidth+j];
			Temp[i*m_bytewidth/k+j]=WaveTran[(Height-i-1)*m_bytewidth+j];
		}
		
	double *Temp1 = new double[Height*m_bytewidth/m];
	double *Temp2 = new double[Height*m_bytewidth/m];
	double *lptemp1 = new double[Height*m_bytewidth/m];
    double *lptemp2 = new double[Height*m_bytewidth/m];
	
    double *Rlow = new double[Height*m_bytewidth/m];
    double *Rhigh = new double[Height*m_bytewidth/m];
	
    for(i=0;i<Height/k;i++)
		for(j=0;j<Width/k;j++)
		{
            Rlow[i*m_bytewidth/k+j]=0;
			Rhigh[i*m_bytewidth/k+j]=0;
			lptemp1[i*m_bytewidth/k+j]=0;
			lptemp2[i*m_bytewidth/k+j]=0;
		}
		
	double *Clow = new double[Height*m_bytewidth/n];
	double *Chigh = new double[Height*m_bytewidth/n];
		
	double *LL1 = new double[Height*m_bytewidth/n];
	double *LH1 = new double[Height*m_bytewidth/n];
	double *HL1 = new double[Height*m_bytewidth/n];
	double *HH1 = new double[Height*m_bytewidth/n];
	for(i=0;i<Height/k;i++)
		for(j=0;j<Width/(k*2);j++)
		{
			Clow[i*m_bytewidth/(k*2)+j]=0;
			Chigh[i*m_bytewidth/(k*2)+j]=0;
			LL1[i*m_bytewidth/(k*2)+j]=0;
			LH1[i*m_bytewidth/(k*2)+j]=0;
			HL1[i*m_bytewidth/(k*2)+j]=0;
			HH1[i*m_bytewidth/(k*2)+j]=0;
		}
			
	//将四分量分别补零扩展
	for(i=0;i<Height/(k*2);i++)
		for(j=0;j<Width/(k*2);j++)
		{
			/*LL1[(i*2+1)*m_bytewidth/(k*2)+j]=Temp[(i+Height/(k*2))*m_bytewidth/k+j];//左下
			LH1[(i*2+1)*m_bytewidth/(k*2)+j]=Temp[(i+Height/(k*2))*m_bytewidth/k+j+Width/(k*2)];//右下
			HL1[(i*2+1)*m_bytewidth/(k*2)+j]=Temp[i*m_bytewidth/k+j];//左上
			HH1[(i*2+1)*m_bytewidth/(k*2)+j]=Temp[i*m_bytewidth/k+j+Width/(k*2)];//右上*/
            LL1[(i*2+1)*m_bytewidth/(k*2)+j]=Temp[i*m_bytewidth/k+j];//左上
			LH1[(i*2+1)*m_bytewidth/(k*2)+j]=Temp[i*m_bytewidth/k+j+Width/(k*2)];//右上
			HL1[(i*2+1)*m_bytewidth/(k*2)+j]=Temp[(i+Height/(k*2))*m_bytewidth/k+j];//左下
			HH1[(i*2+1)*m_bytewidth/(k*2)+j]=Temp[(i+Height/(k*2))*m_bytewidth/k+j+Width/(k*2)];//右下
		}
	/*列变换*/
	//列低，列高
	for(i=0;i<Height/k-1;i++)
		for(j=0;j<Width/(k*2);j++)
		{
			Clow[i*m_bytewidth/(k*2)+j]=LL1[i*m_bytewidth/(k*2)+j]+LL1[(i+1)*m_bytewidth/(k*2)+j]+LH1[i*m_bytewidth/(k*2)+j]-LH1[(i+1)*m_bytewidth/(k*2)+j];
			Chigh[i*m_bytewidth/(k*2)+j]=HL1[i*m_bytewidth/(k*2)+j]+HL1[(i+1)*m_bytewidth/(k*2)+j]+HH1[i*m_bytewidth/(k*2)+j]-HH1[(i+1)*m_bytewidth/(k*2)+j];
		}
	//最后一行处理
	for(i=0;i<Width/(k*2);i++)
	{
		Clow[(Height/k-1)*m_bytewidth/(k*2)+i]=LL1[i]+LL1[(Height/k-1)*m_bytewidth/(k*2)+i]+LH1[(Height/k-1)*m_bytewidth/(k*2)+i]-LH1[i];	
		Chigh[(Height/k-1)*m_bytewidth/(k*2)+i]=HL1[i]+HL1[(Height/k-1)*m_bytewidth/(k*2)+i]+HH1[(Height/k-1)*m_bytewidth/(k*2)+i]-HH1[i];
	}
	/*行变换*/
	//补零
	for(i=0;i<Height/k;i++)
		for(j=0;j<Width/(k*2);j++)
		{
			Rlow[i*m_bytewidth/k+j*2+1]=Clow[i*m_bytewidth/(k*2)+j];
			Rhigh[i*m_bytewidth/k+j*2+1]=Chigh[i*m_bytewidth/(k*2)+j];
		}
	//行低，行高
	for(i=0;i<Height/k;i++)
		for(j=0;j<Width/k-1;j++)
		{
			lptemp1[i*m_bytewidth/k+j]=Rlow[i*m_bytewidth/k+j]+Rlow[i*m_bytewidth/k+j+1];
			lptemp2[i*m_bytewidth/k+j]=Rhigh[i*m_bytewidth/k+j]-Rhigh[i*m_bytewidth/k+j+1];
		}
	//最后一列处理
	for(i=0;i<Height/k;i++)
		{
		    lptemp1[i*m_bytewidth/k+Width/k-1]=Rlow[i*m_bytewidth/k+Width/k-1]+Rlow[i*m_bytewidth/k];
			lptemp2[i*m_bytewidth/k+Width/k-1]=Rhigh[i*m_bytewidth/k+Width/k-1]-Rhigh[i*m_bytewidth/k];
		}
	//合并
	for(i=0;i<Height/k;i++)
		for(j=0;j<Width/k;j++)
		{
			Temp1[i*m_bytewidth/k+j]=(lptemp1[i*m_bytewidth/k+j]+lptemp2[i*m_bytewidth/k+j])/2.0;
		}
	//行移位
	for(i=0;i<Height/k;i++)
	{
		for(j=1;j<Width/k;j++)
            Temp2[i*m_bytewidth/k+j]=Temp1[i*m_bytewidth/k+j-1];
		Temp2[i*m_bytewidth/k]=Temp1[i*m_bytewidth/k+Width/k-1];
	}
	//列移位
	for(j=0;j<Width/k;j++)
	{
        for(i=1;i<Height/k;i++)
            Temp[i*m_bytewidth/k+j]=Temp2[(i-1)*m_bytewidth/k+j];
		Temp[j]=Temp2[(Height/k-1)*m_bytewidth/k+j];
	}
    for(i=0;i<Height/k;i++)
		for(j=0;j<Width/k;j++)
		{
			//WaveTran[(Height-i-1)*m_bytewidth+j]=Temp[(Height/k-i-1)*m_bytewidth/k+j];
			WaveTran[(Height-i-1)*m_bytewidth+j]=Temp[i*m_bytewidth/k+j];
		}
}

void CWavelet::OnButton1() 
{
	// TODO: Add your control notification handler code here
Invalidate();	
}
