//DIB.CPP :DIB implementation file
//

#include "stdafx.h"
#include "dib.h"
//#include "mainfrm.h"
#include "math.h"

////////////////////
CDIB::CDIB()
{
	m_pBMI=NULL;
	m_pDIBData=NULL;
	m_pDumpDIBData=NULL;
	m_pR=NULL;
	m_pG=NULL;
	m_pB=NULL;
	m_bLoaded=false;
	dataBytes=0;
	m_pdata=NULL;
	m_pPalette=NULL;
	m_nImType=0;


}

CDIB::~CDIB()
{
//释放内存
	if(m_pBMI!=NULL)
		delete m_pBMI;
	if(m_pDIBData!=NULL)
		delete m_pDIBData;
	if(m_pDumpDIBData!=NULL)
		delete m_pDumpDIBData;

	if(m_pR!=NULL)
		free(m_pR);
	if(m_pG!=NULL)
		free(m_pG);
	if(m_pB!=NULL)
		free(m_pB);
	if(m_pdata!=NULL)
		delete m_pdata;

}

bool CDIB::LoadFromFile(LPCTSTR lpszFileName)
{
	CFile file;
	BITMAPINFO* pBMI=NULL;
	BYTE* pDIBData=NULL;
	BYTE* pDumpDIBData=NULL;

//打开指定的文件
	if(!file.Open(lpszFileName,CFile::modeRead|CFile::typeBinary))
	{	AfxMessageBox("打不开文件!");
		return FALSE;
	}

//读入BMP文件头信息
//	BITMAPFILEHEADER bfh;
	if(file.Read(&bfh,sizeof(bfh))!=sizeof(bfh))
	{
		AfxMessageBox("error in reading file");
		return FALSE;
	}

//若不是BMP,不予处理
	if(bfh.bfType!=0x4d42)      //'BM'
	{
		AfxMessageBox("不是BMP文件");
		return FALSE;
	}

//读入位图信息头
	//
	if(file.Read(&bih,sizeof(bih))!=sizeof(bih))
	{
		AfxMessageBox("读文件出错!");
		return FALSE;
	}

//若不是/24位真彩色位图,则不予处理
/*	if(bih.biBitCount<24)
	{
		AfxMessageBox("this is not 24bit bitmap");
		return FALSE;
	}
*/
	if(bih.biBitCount==8)
	{
		////读取图像信息
		if(m_pBMI!=NULL)
			delete pBMI;
		file.Seek(-bih.biSize,CFile::current);
		m_pBMI=(BITMAPINFO*) new BYTE[sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*256];
		if(file.ReadHuge(m_pBMI,sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*256)!=sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*256)
		{
			AfxMessageBox("读图像数据出错");
			return false;
		}
	
         ////////////////创建调色板
		int ncolor=bih.biClrUsed? bih.biClrUsed:1<<bih.biBitCount;
		UINT nsize=sizeof(LOGPALETTE)+sizeof(PALETTEENTRY)*ncolor;

		LOGPALETTE *pLP=(LOGPALETTE*)new BYTE(nsize);		
		pLP->palVersion=0x300;
		pLP->palNumEntries=ncolor;

		/*for(int i=0;i<ncolor;i++)
		{
			pLP->palPalEntry[i].peRed=m_pBMI->bmiColors[i].rgbRed;
			pLP->palPalEntry[i].peGreen=m_pBMI->bmiColors[i].rgbGreen;
			pLP->palPalEntry[i].peBlue=m_pBMI->bmiColors[i].rgbBlue;
			pLP->palPalEntry[i].peFlags=0;
		}
		*/
		if(m_pPalette!=NULL)
			delete m_pPalette;
		m_pPalette=new CPalette;
		
		m_pPalette->CreatePalette(pLP);


		/////读图像数据
		int nW=m_pBMI->bmiHeader.biWidth;
		int nH=m_pBMI->bmiHeader.biHeight;
		if(m_pDIBData!=NULL)
			delete m_pDIBData;
		m_pDIBData=new BYTE[nW*nH];
		if(!m_pDIBData)
		{
			AfxMessageBox("分配内存出错!");
			return FALSE;
		}
		
		file.Seek(-nH*nW,CFile::end);
		if(file.ReadHuge(m_pDIBData,nW*nH)!=(LONG)nW*nH)
		{
			AfxMessageBox("读图像数据出错");
			delete m_pBMI;
			delete m_pDIBData;
			return FALSE;
		}
		file.Close();
		
		if(m_pdata!=NULL)
			delete m_pdata;
		m_pdata=new BYTE[nW*nH];
		if(m_pdata==NULL)
		{
			AfxMessageBox("分配内存出错");
			return FALSE;
		}

		memcpy(m_pdata,m_pDIBData,nW*nH);

//		delete pLP;
		m_bLoaded=true;
		m_nImType=8;
	    return TRUE;


	}

//为BITMAPINFO结构指针申请内存,由于真彩色位图没有颜色表,所以起BITMAPINFO=BITMAPINFOHEADER
	pBMI=(BITMAPINFO*) new char[sizeof(BITMAPINFOHEADER)];
	if(!pBMI)
	{
		AfxMessageBox("分配内存出错!");
		return FALSE;
	}
	
//由于前面已将BITMAPINFOHERAER读入了内存,所以这里只需拷贝一下
	memcpy(pBMI,&bih,sizeof(BITMAPINFOHEADER));

//为DIB图象数据指针申请内存
	int nW=pBMI->bmiHeader.biWidth;
	int nH=pBMI->bmiHeader.biHeight;
	int length=3*nW;
	while(length%4!=0)length++;
	length=length-3*nW;
	dataBytes=3*nW*nH+nH*length;
	pDIBData=(BYTE*) new char[dataBytes];
	if(!pDIBData)
	{
		AfxMessageBox("分配内存出错");
		return FALSE;
	}
//	dataBytes=bfh.bfSize-bfh.bfOffBits;//图像数据的字节数 ALPHA NO DWORD
	pDumpDIBData=(BYTE*) new char[dataBytes];
	if(!pDIBData)
	{
		AfxMessageBox("分配内存出错");
		return FALSE;
	}

	if(!pDumpDIBData)
	{
		AfxMessageBox("分配内存出错");
		return FALSE;
	}

	//读如位图的图像数据
	if(file.ReadHuge(pDIBData,dataBytes)!=dataBytes)
	{
		AfxMessageBox("读图像数据出错");
		delete pBMI;
		delete pDIBData;
		return FALSE;
	}

	file.Close();

	if(m_pBMI!=NULL)
		delete m_pBMI;
	m_pBMI=pBMI;

	if(m_pDIBData!=NULL)
		delete m_pDIBData;
	m_pDIBData=pDIBData;

	memcpy(pDumpDIBData,pDIBData,dataBytes);

	if(m_pDumpDIBData!=NULL)
		delete m_pDumpDIBData;
	m_pDumpDIBData=pDumpDIBData;

	if(m_pR!=NULL)
		free(m_pR);
	if(m_pG!=NULL)
		free(m_pG);
	if(m_pB!=NULL)
		free(m_pB);

	//m_pR=(BYTE*)malloc(sizeof(BYTE)*nW*nH);
	//m_pG=(BYTE*)malloc(sizeof(BYTE)*nW*nH);
	//m_pB=(BYTE*)malloc(sizeof(BYTE)*nW*nH);

	if(m_pdata!=NULL)
			delete m_pdata;

	m_pdata=new BYTE[nW*nH];
	if(m_pdata==NULL)
	{
		AfxMessageBox("分配内存出错");
		return FALSE;
	}


	int ni,nj;
	for(ni=0;ni<nH;ni++)
		for(nj=0;nj<nW;nj++)
		{
		//	m_pB[(nH-1-nj)*nW+ni]=m_pDIBData[(nj*nW+ni)*3+nj*length];
		//	m_pG[(nH-1-nj)*nW+ni]=m_pDIBData[(nj*nW+ni)*3+1+nj*length];
		//	m_pR[(nH-1-nj)*nW+ni]=m_pDIBData[(nj*nW+ni)*3+2+nj*length];
			m_pdata[ni*nW+nj]=(unsigned char)(m_pDIBData[ni*(3*nW+length)+3*nj]*0.11+m_pDIBData[ni*(3*nW+length)+3*nj+1]*0.59+m_pDIBData[ni*(3*nW+length)+3*nj+2]*0.3);
		}

	m_bLoaded=true;
	m_nImType=24;

	return TRUE;
}



//////////////////




bool CDIB::SaveFile(LPCTSTR lpszFileName)
{
	CFile newFile;
	newFile.Open(lpszFileName,CFile::modeCreate | CFile::modeWrite);
	newFile.Write(&bfh,sizeof(bfh));
	newFile.Write(m_pBMI,sizeof(BITMAPINFOHEADER));
	newFile.WriteHuge(m_pDumpDIBData,dataBytes);
	newFile.Close();
	
	return true;
}


void CDIB::ShowDIB(CDC *pDC, int nLeft, int nTop, int nRight, int nBottom, BYTE *pDIBData,	BITMAPINFO* pBMI)
{
	if(m_pBMI->bmiHeader.biBitCount==8)
	{
	//	pDC->SelectPalette(m_pPalette,FALSE);
	//	pDC->RealizePalette();
	}
	
	pDC->SetStretchBltMode(COLORONCOLOR);    //设置伸缩拷贝模式
	StretchDIBits(pDC->GetSafeHdc(),         //DC的句柄
		          nLeft,                     //目标矩形左上角的X坐标
				  nTop,                      //目标矩形左上角的Y坐标
				  nRight,                    //目标矩形的宽度
				  nBottom,                   //目标矩形的高度
				  0,                         //源矩形左上角的X坐标
				  0,                         //源矩形左上角的Y坐标
		          GetDIBWidth(),             //源矩形的宽度
				  GetDIBHeight(),            //源矩形的高度
				  pDIBData,                  //位图图象数据的地址
				  pBMI,                      //位图信息结构地址
				  DIB_RGB_COLORS,            //标志选项
				  SRCCOPY);                  //光栅操作码

}





void CDIB::InvalidateData()
{
	if(m_bLoaded==false)
	{
		AfxMessageBox("请先打开要操作的图");
		return;
	}

	int nW=GetDIBWidth();
	int nH=GetDIBHeight();
	if(bih.biBitCount==8)
	{
		memcpy(m_pDIBData,m_pdata,nW*nH);
		return;
	}
	
	int lenght=3*nW;
	while(lenght%4!=0)lenght++;
	lenght=lenght-3*nW;
	int ni,nj;
	for ( ni=0;ni<nH;ni++)
		for ( nj=0;nj<nW;nj++)
		{
			m_pDumpDIBData[ni*(3*nW+lenght)+nj*3]=m_pdata[ni*nW+nj];
            m_pDumpDIBData[ni*(3*nW+lenght)+nj*3+1]=m_pdata[ni*nW+nj];
			m_pDumpDIBData[ni*(3*nW+lenght)+nj*3+2]=m_pdata[ni*nW+nj];
		}
}

void CDIB::close()
{

	//释放内存
	if(m_pBMI!=NULL)
		delete m_pBMI;
	if(m_pDIBData!=NULL)
		delete m_pDIBData;
	if(m_pDumpDIBData!=NULL)
		delete m_pDumpDIBData;

	if(m_pR!=NULL)
		free(m_pR);
	if(m_pG!=NULL)
		free(m_pG);
	if(m_pB!=NULL)
		free(m_pB);
	if(m_pdata!=NULL)
		delete m_pdata;


}

void CDIB::UpdateData()
{
	if(m_bLoaded==false)
	{
		AfxMessageBox("请先打开要操作的图");
		return;
	}

	int nW=GetDIBWidth();
	int nH=GetDIBHeight();
	if(bih.biBitCount==8)
	{
		memcpy(m_pDIBData,m_pdata,nW*nH);
		return;
	}
	
	int lenght=3*nW;
	while(lenght%4!=0)lenght++;
	lenght=lenght-3*nW;
	int ni,nj;
	for ( ni=0;ni<nH;ni++)
		for ( nj=0;nj<nW;nj++)
		{
			m_pDIBData[ni*(3*nW+lenght)+nj*3]=m_pdata[ni*nW+nj];
            m_pDIBData[ni*(3*nW+lenght)+nj*3+1]=m_pdata[ni*nW+nj];
			m_pDIBData[ni*(3*nW+lenght)+nj*3+2]=m_pdata[ni*nW+nj];
		}
}
