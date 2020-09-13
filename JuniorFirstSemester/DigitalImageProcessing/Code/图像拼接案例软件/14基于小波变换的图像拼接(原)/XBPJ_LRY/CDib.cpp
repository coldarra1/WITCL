// CDib.cpp: implementation of the CDib class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CDib.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define M 2
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDib::CDib()
{
	m_pBMI = NULL;
	m_pDIBData = NULL;
	m_pFileHeader = NULL;
	m_pBMFHeader = NULL;

	m_ImageData = 0;    
	m_ImageCount = 0;
	m_ByteWidth = 0;
}

CDib::CDib(BYTE *pSrc)
{
	BYTE *temp1;
	
	if(!pSrc) 
	{
		AfxMessageBox("CDib 所带BYTE *pSrc参数为空!");
        	return;
	}
	
	unsigned i = 0;
	m_pBMFHeader = new BITMAPFILEHEADER;
	if(!m_pBMFHeader)
	{
		AfxMessageBox("动态内存分配失败！");
		return;
	}

	// 位图文件信息头
	temp1 = (BYTE*)m_pBMFHeader;
	for(i = 0; i<14; i++)
	{
		*temp1++ = *(pSrc+i);
	}
	//*m_pBMFHeader = *(BITMAPFILEHEADER*)(pSrc);   

	m_ImageCount = m_pBMFHeader->bfSize;
	m_ImageData  = m_pBMFHeader->bfSize - m_pBMFHeader->bfOffBits;

	BYTE *temp;
	temp = new BYTE[m_pBMFHeader->bfOffBits - 14];
	
	if(!temp)
	{
		AfxMessageBox("动态内存分配失败！");
		return;
	}

	for (i = 0; i<m_pBMFHeader->bfOffBits - 14; i++ )
	{
		*(temp + i) = *(pSrc + 14 + i);
	}

	m_pBMI = (BITMAPINFO*)(temp);   // 位图文件信息头

	m_pDIBData = NULL;
	m_pDIBData = new BYTE[m_ImageData];
	if(!m_pDIBData)
	{
		AfxMessageBox("动态内存分配失败！");
		return;
	}
	
	for(i = 0; i<m_ImageData; i++)
	{
		*(m_pDIBData+i) = *(pSrc + i + m_pBMFHeader->bfOffBits);
	}

	m_pFileHeader = new BYTE[m_ImageCount];
	if(!m_pFileHeader)
	{
		AfxMessageBox("动态内存分配失败！");
		return;
	}
	
	for(i = 0; i<m_ImageCount; i++)
	{
		*(m_pFileHeader+i) = *(pSrc + i);
	}

	
}

CDib::CDib(CDib &dib)
{
	m_ImageData = dib.m_ImageData;
	m_ImageCount = dib.m_ImageCount;

	m_pBMFHeader = new BITMAPFILEHEADER;

	if(!m_pBMFHeader)
	{
		AfxMessageBox("动态内存分配失败！");
		return;
	}

	*m_pBMFHeader = *(dib.m_pBMFHeader);

	m_pBMI = (BITMAPINFO*)new BYTE[m_pBMFHeader->bfOffBits - sizeof(BITMAPFILEHEADER)];
	
	if(!m_pBMI)
	{
		AfxMessageBox("动态内存分配失败！");
		return;
	}

	*m_pBMI = *(dib.m_pBMI);

	m_pDIBData = new BYTE[m_ImageData];
	if(!m_pDIBData)
	{
		AfxMessageBox("动态内存分配失败！");
		return;
	}
	
	unsigned i;
	for(i = 0; i<m_ImageData; i++)
	{
		*(m_pDIBData+i) = *(dib.m_pDIBData + i);
	}


	m_pFileHeader = new BYTE[m_ImageCount];
	if(!m_pFileHeader)
	{
		AfxMessageBox("动态内存分配失败！");
		return;
	}
	
	for(i = 0; i<m_ImageCount; i++)
	{
		*(m_pFileHeader+i) = *(dib.m_pFileHeader + i);
	}

	m_ByteWidth=dib.m_ByteWidth;
}

CDib::CDib(LPCTSTR lpszPathName)
{
	m_pBMI = NULL;
	m_pDIBData = NULL;
	m_pFileHeader = NULL;
	m_pBMFHeader = NULL;

	m_ImageData = 0;    
	m_ImageCount = 0;
	m_ByteWidth=0;
	LoadFromFile( lpszPathName );
}


void CDib::operator = (CDib &dib)
{
	m_ImageData = dib.m_ImageData;
	m_ImageCount = dib.m_ImageCount;
	m_ByteWidth = dib.m_ByteWidth;

	if(m_pBMFHeader) delete m_pBMFHeader;
	m_pBMFHeader = new BITMAPFILEHEADER;

	if(!m_pBMFHeader)
	{
		AfxMessageBox("动态内存分配失败！");
		return;
	}

	*m_pBMFHeader = *(dib.m_pBMFHeader);
	
	if(m_pBMI) delete m_pBMI;
	BYTE *temp = new BYTE[m_pBMFHeader->bfOffBits - sizeof(BITMAPFILEHEADER)];
	if(!temp)
	{
		AfxMessageBox("动态内存分配失败！");
		exit(1);
	}
	BYTE *p = (BYTE*)dib.m_pBMI;
	for(DWORD i = 0; i<m_pBMFHeader->bfOffBits-14; i++)
	{
		*(temp+i) = *(p++);
	}
	
	m_pBMI = (BITMAPINFO*)temp;

	if(m_pDIBData) delete []m_pDIBData;	
	m_pDIBData = new BYTE[m_ImageData];
	if(!m_pDIBData)
	{
		AfxMessageBox("动态内存分配失败！");
		return;
	}
	
	for(i = 0; i<m_ImageData; i++)
	{
		*(m_pDIBData+i) = *(dib.m_pDIBData + i);
	}

	if(m_pFileHeader) delete []m_pFileHeader;	
	m_pFileHeader = new BYTE[m_ImageCount];
	if(!m_pFileHeader)
	{
		AfxMessageBox("动态内存分配失败！");
		return;
	}
	
	for(i = 0; i<m_ImageCount; i++)
	{
		*(m_pFileHeader+i) = *(dib.m_pFileHeader + i);
	}
	
}

CDib::~CDib()
{
	if(m_pBMI!=NULL)     delete m_pBMI;
	if(m_pDIBData!=NULL) delete []m_pDIBData;
	if(m_pFileHeader!=NULL) delete []m_pFileHeader;
	if(m_pBMFHeader!=NULL) delete m_pBMFHeader;
}


BOOL CDib::LoadFromFile(LPCTSTR lpszFileName)
{
	CFile file;
//位图指针初始化
	BITMAPINFO          *pBMI = NULL;
	BYTE				*pDIBData = NULL;
	BYTE				*pFileHeader = NULL;//位图文件指针
	BITMAPFILEHEADER	*pBMFHeader = NULL;

	//打开指定的文件
	if(!file.Open(lpszFileName,CFile::modeRead|CFile::typeBinary))
	   {
	    	AfxMessageBox("can't open this file!");
		    return FALSE;
	   }
	            
	//读入位图BITMAPFILEHEADER文件  14个字节
	pBMFHeader = (BITMAPFILEHEADER*) new BYTE[sizeof(BITMAPFILEHEADER)];
	if(file.Read(pBMFHeader,sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
	{
		AfxMessageBox("error");
		return FALSE;
	}
	
	//若不是BMP位图,不于处理
	if(pBMFHeader->bfType != 0x4d42) //0X4D42 是'BM'的十六进制表示         
	{
		AfxMessageBox("isn't BMP image.");
		return FALSE;
	}

	if(m_pBMFHeader != NULL)  delete m_pBMFHeader;// m_FileHeader记录图象实际的指针位置
		m_pBMFHeader = pBMFHeader;

	//读入位图文件信息
	pBMI=(BITMAPINFO*) new BYTE[pBMFHeader->bfOffBits - sizeof(BITMAPFILEHEADER)];
	if(!pBMI)//如果（bfh.bfOffBits-sizeof(BITMAPFILEHEADER)）的值为0，
	{        //则位图文件信息内存分配出错！
		AfxMessageBox(" 位图文件信息内存分配出错！");	
		return FALSE;
	}
	
	if(file.Read(pBMI, pBMFHeader->bfOffBits-sizeof(BITMAPFILEHEADER)) != pBMFHeader->bfOffBits-sizeof(BITMAPFILEHEADER))
	{
		AfxMessageBox("读文件信息头出错!");
		return FALSE;
	}

	if(m_pBMI != NULL)	delete m_pBMI;  
		m_pBMI = pBMI; 
	
	// ******开始读取数据****************************************

	
   		m_ImageData = pBMFHeader->bfSize - pBMFHeader->bfOffBits;//位图实际数据大小
		pDIBData = new BYTE[m_ImageData];//存储位图实际数据的内存空间

		if(!pDIBData)// 若pDIBData值为0，出错！
		{
			AfxMessageBox("图象实际数据内存分配错误！");
			return FALSE;
		}
	
		//使指向位图文件的指针指向位图文件的实际数据部分
		file.Seek(pBMFHeader->bfOffBits,CFile::begin);
		if(file.Read(pDIBData, m_ImageData) != m_ImageData)//读位图实际数据失败
		{
			AfxMessageBox("读位图实际数据出错！");
			return FALSE;
		}

		file.SeekToBegin();//使指向文件的指针回到文件的开始位置
		m_ImageCount = file.GetLength();
		       //位图文件大小为ImageCount        
		pFileHeader = new BYTE[m_ImageCount];
		       //FilePointerHeader位图文件头指针,FilePointerHeader
               //是指向刚分配的图象大小的一块内存的指针
		file.Read(pFileHeader,m_ImageCount);
               //利用FILE的函数打开图象             
		file.Close();	       
				//计算图象每行实际宽度  单位：字节
		//m_ByteWidth=(GetW()*m_pBMI->bmiHeader.biBitCount+31)/32*4;
		m_ByteWidth=((GetW()*m_pBMI->bmiHeader.biBitCount+31)&~31)>>3;

		if(m_pDIBData != NULL)   delete []m_pDIBData; //释放旧的指针内容
		m_pDIBData = pDIBData;                    //赋予新值
	
		if(m_pFileHeader != NULL)   delete []m_pFileHeader; //释放旧的指针内容
		m_pFileHeader = pFileHeader;                    //赋予新值
		return TRUE;

}


BOOL CDib::SaveFile(CString filename)
{	
	CFile file;
	//保存指定的文件
	if(!file.Open(filename, CFile::modeCreate|CFile::modeWrite))
	{
		AfxMessageBox("can't be saved for that it existed already !");
		return FALSE;
	}

	file.SeekToBegin();
	file.Write(m_pFileHeader,m_ImageCount);//写入图象文件
	file.Close();
	return TRUE;
}

void CDib::ShowDIB(CDC  *pDC,int nLeft,int nTop)
{
	//pDC->SetStretchBltMode(COLORONCOLOR);//设置伸缩拷贝模式
	StretchDIBits(pDC->GetSafeHdc(),//DC的句炳
		nLeft,                      //目标矩形左上角的x坐标
		nTop,                       //目标矩形左上角的Y坐标
		GetW(),                     //目标矩形的宽度
 		GetH(),                     //目标矩形的高度
		0,                          //原矩形左上角的x坐标
		0,                          //原矩形左上角的Y坐标
		GetW(),                     //原矩形的宽度     **
		GetH(),                     //原矩形的高度     **
		m_pDIBData,                 //位图图像数据的地址**
		m_pBMI,                     //位图信息结构地址 **
		DIB_RGB_COLORS,             //标志选项
		SRCCOPY);                   //光栅操作码
}

UINT CDib::GetW()
{	
	return m_pBMI->bmiHeader.biWidth;
}
	

UINT CDib::GetH()
{	
	return m_pBMI->bmiHeader.biHeight;
}

void CDib::updatedata(void)
{
	unsigned long i = 0;
	BYTE *p = m_pFileHeader + m_pBMFHeader->bfOffBits;
	
	for(i = 0; i<m_ImageData; i++)
	{
		*(p++) = *(m_pDIBData + i);
	}
}
