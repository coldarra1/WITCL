// FaceDetectionDoc.cpp : implementation of the CFaceDetectionDoc class
//

#include "stdafx.h"
#include "FaceDetection.h"

#include "FaceDetectionDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFaceDetectionDoc

IMPLEMENT_DYNCREATE(CFaceDetectionDoc, CDocument)

BEGIN_MESSAGE_MAP(CFaceDetectionDoc, CDocument)
	//{{AFX_MSG_MAP(CFaceDetectionDoc)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFaceDetectionDoc construction/destruction

CFaceDetectionDoc::CFaceDetectionDoc()
{
	// TODO: add one-time construction code here
	int i,j;
	m_hDIB=NULL;
	for( i=0; i<ImgRange; i++)
		for ( j=0; j<ImgRange; j++)
		{
			emymapc[i][j] = false;
			emymapl[i][j] = false;
			//lab[i][j] = false;
		}
	for( i=0;i<ImgRange; i++)
		for ( j=0; j<ImgRange; j++)
			lab[i][j] = false;

}

CFaceDetectionDoc::~CFaceDetectionDoc()
{
}

BOOL CFaceDetectionDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFaceDetectionDoc serialization

void CFaceDetectionDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFaceDetectionDoc diagnostics

#ifdef _DEBUG
void CFaceDetectionDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFaceDetectionDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFaceDetectionDoc commands

BOOL CFaceDetectionDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	CFile fileM;
	CFileException feM;
	m_hDIB = NULL;
	if (!fileM.Open(lpszPathName, CFile::modeRead | CFile::shareDenyWrite, &feM))
	{
		// 失败
		ReportSaveLoadException(lpszPathName, &feM,FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);	
		// 返回FALSE
		return FALSE;
	}
	if (!fileM2.Open(lpszPathName, CFile::modeRead | CFile::shareDenyWrite, &feM))
	{
		// 失败
		ReportSaveLoadException(lpszPathName, &feM,FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);	
		// 返回FALSE
		return FALSE;
	}
		TRY
	{
		m_hDIB = ::ReadDIBFile(fileM);
	}
	CATCH (CFileException, eLoad)
	{
		// 读取失败
		fileM.Abort();		
		// 恢复光标形状
		EndWaitCursor();		
		// 报告失败
		ReportSaveLoadException(lpszPathName, eLoad,
			FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);	
		// 设置DIB为空
		m_hDIB = NULL;	
		fileM.Close();
		// 返回FALSE
		return FALSE;
	}
	END_CATCH
	m_hDIBtemp=(HDIB)CopyHandle(m_hDIB);
	//if(fileM.Read(&bmfHeaderMulspec,sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
	//return FALSE;

	fileM.Close();
	// TODO: Add your specialized creation code here
	return TRUE;
}
bool CFaceDetectionDoc::LightingCompensate()
{

	LPBITMAPINFOHEADER lpbi;
	lpbi = (LPBITMAPINFOHEADER)::GlobalLock((HGLOBAL) m_hDIB);//读取头文件
	lLineBytesMulspec = WIDTHBYTES((lpbi->biWidth)*24);
	::GlobalUnlock((HGLOBAL) m_hDIB);
	int width,height;
	LPBYTE lpData;
	LONG wBytesPerLine;
	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) m_hDIB);	
	// 获取DIB宽度
	width= (int) ::DIBWidth(lpDIB);		
	// 获取DIB高度
	height= (int) ::DIBHeight(lpDIB);
	::GlobalUnlock((HGLOBAL) m_hDIB);
	lpData = (unsigned char*)::FindDIBBits(lpDIB);
	//得到图片每行的象素所占字节个数
	wBytesPerLine = lLineBytesMulspec;
	//比例系数
	const double thresholdco = 0.05;
	//象素个数的临界常数
	const int thresholdnum = 100;
	//灰度级数组
	int histogram[256];
	for(int i =0;i<256;i++)
		histogram[i] = 0;
	//对于过于小的图片的判断
	if(width*height*thresholdco < thresholdnum)
		return false;
	int colorr,colorg,colorb;
	long lOffset;
	//考察整个图片
	for( i=0;i<height;i++)
		for(int j=0;j<width;j++)
		{	
			//得到象素数据的偏移
			lOffset = i*wBytesPerLine + j*3;
			//得到rgb值
			colorb = *(lpData+lOffset++);
			colorg = *(lpData+lOffset++);
			colorr = *(lpData+lOffset++);
			//计算灰度值
			int gray = (colorr * 299 + colorg * 587 + colorb * 114)/1000;
			histogram[gray]++;
		}
		int calnum =0;
		int total = width*height;
		int num;
		//下面的循环得到满足系数thresholdco的临界灰度级
		for(i =0;i<256;i++)
		{
			if((float)calnum/total < thresholdco)
			{
				calnum+= histogram[255-i];
				num = i;
			}
			else
				break;
		}
		int averagegray = 0;
		calnum =0;
		//得到满足条件的象素总的灰度值
		for(i = 255;i>=255-num;i--)
		{
			averagegray += histogram[i]*i;
			calnum += histogram[i];
		}
		averagegray /=calnum;
		//得到光线补偿的系数
		double co = 255.0/(float)averagegray;
		//下面的循环对图象进行光线补偿
		for(i =0;i<height;i++)
			for(int j=0;j<width;j++)
			{	
				//得到数据便宜
				lOffset =i*wBytesPerLine + j*3;
				//得到蓝色分量
				colorb = *(lpData+lOffset);
				//调整
				colorb *=co;
				//临界判断
				if(colorb >255)
					colorb = 255;
				//保存
				*(lpData+lOffset) = colorb;
				//绿色分量
				colorb = *(lpData+lOffset+1);
				colorb *=co;
				if(colorb >255)
					colorb = 255;
				*(lpData+lOffset+1) = colorb;
				//红色分量
				colorb = *(lpData+lOffset+2);
				colorb *=co;
				if(colorb >255)
					colorb = 255;
				*(lpData+lOffset+2) = colorb;
			}
	return TRUE;
}
void CFaceDetectionDoc::RgbtoYcb(HDIB hDIB,LPBYTE lpYcb)
{
	LPBITMAPINFOHEADER lpbi;
	lpbi = (LPBITMAPINFOHEADER)::GlobalLock((HGLOBAL) hDIB);//读取头文件
	lLineBytesMulspec = WIDTHBYTES((lpbi->biWidth)*24);
	::GlobalUnlock((HGLOBAL)hDIB);
	int width,height;
	WORD wBytesPerLine;
	LPBYTE lpData;
	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) hDIB);	
	// 获取DIB宽度
	width= (int) ::DIBWidth(lpDIB);		
	// 获取DIB高度
	height= (int) ::DIBHeight(lpDIB);
	lpData = (unsigned char*)::FindDIBBits(lpDIB);
	//得到图象的基本信息	
	wBytesPerLine = lLineBytesMulspec;//得到图片每行的象素所占字节个数

	long lOffset;
	//下面的循环实现从rgb到ycc的转化
	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++)
		{
			
			lOffset = i*wBytesPerLine + j*3;	//得到象素数据的偏移
			//得到rgb数值
			int b = *(lpData + lOffset);
			int g = *(lpData + lOffset+1);
			int r = *(lpData + lOffset+2);
			//计算得到y，cr，cb的数值
			int Y = (257*r+504*g+98*b)/1000+16;
			int Cr = (439*r-368*g-71*b)/1000+128;
			int Cb = (-148*r-291*g+439*b)/1000+128;
			//保存计算得到的数值
			*(lpYcb+lOffset++) = Y;
			*(lpYcb+lOffset++) = Cr;
			*(lpYcb+lOffset++) = Cb;
		}
	::GlobalUnlock((HGLOBAL) hDIB);
}

//////////////*皮肤颜色建模*//////////////
int CFaceDetectionDoc::_Cb(int Y)
{	
	int Cb;
	//如果亮度很小的情况
	if(Y<Kl)
		Cb = 108 + ((Kl-Y)*10)/(Kl-Ymin);
	//亮度很大的情况
	else if(Y>Kh)
		Cb = 108 + ((Y-Kh)*10)/(Ymax - Kh);
	else 
		Cb = -1;
	return Cb;
}

int CFaceDetectionDoc::_Cr(int Y)
{
	int Cr;
	//亮度很小的情况
	if(Y<Kl)
		Cr = 154 - ((Kl-Y)*10)/(Kl-Ymin);
	//亮度很大的情况
	else if(Y>Kh)
		Cr = 154 - ((Y-Kh)*22)/(Ymax - Kh);
	else
		Cr = -1;
	return Cr;
}
int CFaceDetectionDoc::_WCr(int Y)
{
	int WCr;
	if(Y<Kl)
		//亮度很小的情况
		WCr = WLcr + ((Y-Ymin)*(Wcr-WLcr))/(Kl-Ymin);
	else if(Y>Kh)
		//亮度很大的情况
		WCr = WHcr + ((Ymax-Y)*(Wcr-WHcr))/(Ymax-Kh);
	else WCr = -1;
	return WCr;
}

int CFaceDetectionDoc:: _WCb(int Y)
{
	int WCb;
	if(Y<Kl)
		//亮度很小的情况
		WCb = WLcb + ((Y-Ymin)*(Wcb-WLcb))/(Kl-Ymin);
	else if(Y>Kh)
		//亮度很大的情况
		WCb = WHcb + ((Ymax-Y)*(Wcb-WHcb))/(Ymax-Kh);
	else WCb = -1;
	return WCb;
}
void CFaceDetectionDoc::YccTransform(LPBYTE lpYcc,WORD wBytesPerLine,int height,int width)
{	
	int Y,Cr,Cb;
	long lOffset;
	//下面的循环实现ycc色彩空间的非线性转换
	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++)
		{	
			//得到数据偏移
			lOffset = i*wBytesPerLine + j*3;
			//得到y，Cr，Cb数值
			Y = *(lpYcc+lOffset);
			Cr = *(lpYcc+lOffset+1);
			Cb = *(lpYcc+lOffset+2);
			//如果y数值在两个临界值之间，保持不变
			if(Y>=Kl && Y<=Kh)
				continue;
			//调用非线性转换函数调整Cr，Cb的数值
			Cr = (Cr-_Cr(Y))*(Wcr/_WCr(Y))+_Cr(Kh);
			Cb = (Cb-_Cb(Y))*(Wcb/_WCb(Y))+_Cb(Kh);
			*(lpYcc+lOffset+1) = Cr;
			*(lpYcc+lOffset+2) = Cb;
		}
}

void CFaceDetectionDoc::faceear(LPBYTE lpYcc, WORD wBytesPerLine, int height,int width, bool flag[ImgRange][ImgRange])
{	
	//初始化标志位
	for (int i=0; i<ImgRange; i++)
		for (int j=0; j<ImgRange; j++)
		{
			flag[i][j] = false;
		}
	long lOffset;
	int Cr;
	int Cb;
	for (i=0; i<height; i++)
		for (int j=0; j<width; j++)
		{	
			//得到偏移
			lOffset = i*wBytesPerLine + j*3;
			//得到Cr，Cb数值
			Cr = *(lpYcc+lOffset+1);
			Cb = *(lpYcc+lOffset+2);
			//人脸颜色建模
			if(FaceModeling(Cr,Cb))
			{	
				//修改标志位
				flag[i][j] = true;
			}
		}	
}
BOOL CFaceDetectionDoc::FaceModeling(int Cr,int Cb)
{	
	//Cb的系数常量
	const float cx = 122.453;//114.38;
	//cr的系数常量
	const float cy = 158.442;//160.02;
	//角度常量
	const float theta = 2.53;
	//x轴线和y轴线的两个常量
	const float ecx = 1.60;
	const float ecy = 2.41;
	//长轴
	const float a = 25.39;
	//短轴
	const float b = 14.03;
	//相似度常量
	const float judge = 0.5;
	//计算得到x轴数值
	float  x = cos(theta)*(Cb-cx)+sin(theta)*(Cr-cy);
	//y轴数值
	float  y = -sin(theta)*(Cb -cx)+cos(theta)*(Cr-cy);
	//计算离心率
	float temp = pow(x-ecx,2)/pow(a,2)+pow(y-ecy,2)/pow(b,2);
	//如果满足要求返回真，否则假
	if(fabs(temp-1.0)<judge)
		return TRUE;
	else
		return FALSE;
}

void CFaceDetectionDoc::Skintone() 
{	
	LPBITMAPINFOHEADER lpbi;
	lpbi = (LPBITMAPINFOHEADER)::GlobalLock((HGLOBAL) m_hDIB);//读取头文件
	lLineBytesMulspec = WIDTHBYTES((lpbi->biWidth)*24);
	::GlobalUnlock((HGLOBAL) m_hDIB);
	int width,height;
	LPBYTE lpData;
	long wBytesPerLine;
	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) m_hDIB);	
	// 获取DIB宽度
	width= (int) ::DIBWidth(lpDIB);		
	// 获取DIB高度
	height= (int) ::DIBHeight(lpDIB);
	::GlobalUnlock((HGLOBAL) m_hDIB);
	lpData = (unsigned char*)::FindDIBBits(lpDIB);
	//得到图片每行的象素所占字节个数
	wBytesPerLine = lLineBytesMulspec;
	lpYcc = new BYTE[wBytesPerLine * height];
	RgbtoYcb(m_hDIB,lpYcc);
	YccTransform(lpYcc, wBytesPerLine,height,width);
	faceear(lpYcc,wBytesPerLine,height,width,flag);	
	lpData =(LPBYTE)::GlobalLock(lpDIB)+sizeof(BITMAPINFOHEADER);	
	for (int i=0; i<height; i++)
		for (int j=0; j<width; j++)
		{	
			long lOffset = i*wBytesPerLine + j*3;
			if (flag[i][j] == true)
			{
				*(lpData + lOffset++) = 255;
				*(lpData + lOffset++) = 255;
				*(lpData + lOffset++) = 255;
			}
			else
			{
				*(lpData + lOffset++) = 0;
				*(lpData + lOffset++) = 0;
				*(lpData + lOffset++) = 0;
			}
		}
		
		::GlobalUnlock(lpDIB);
}

void CFaceDetectionDoc::Dilation()
{
	LPBITMAPINFOHEADER lpbi;
	lpbi = (LPBITMAPINFOHEADER)::GlobalLock((HGLOBAL) m_hDIB);//读取头文件
	lLineBytesMulspec = WIDTHBYTES((lpbi->biWidth)*24);
	::GlobalUnlock((HGLOBAL) m_hDIB);
	int width,height;
	LPBYTE lpData;
	long wBytesPerLine;
	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) m_hDIB);	
	// 获取DIB宽度
	width= (int) ::DIBWidth(lpDIB);		
	// 获取DIB高度
	height= (int) ::DIBHeight(lpDIB);
	lpData = (unsigned char*)::FindDIBBits(lpDIB);
	//得到图片每行的象素所占字节个数
	wBytesPerLine = lLineBytesMulspec;
	//申请一块和数据区大小相同的内存
	LPBYTE lpTemp;
	lpTemp = (LPBYTE) new BYTE[wBytesPerLine * height];	
	long lOffsetJudge;
	long lOffset;
	for (int i=1; i<height-1; i++)
		for (int j=1; j<width-1; j++)
		{	
			lOffset = i*wBytesPerLine + j*3;
			//如果当前点为白色，接着循环
			if(*(lpData + lOffset) == 255)
			{
				*(lpTemp + lOffset++) = 255;
				*(lpTemp + lOffset++) = 255;
				*(lpTemp + lOffset++) = 255;
				continue;
			}
			//否则考察上下左右四个点
			else
			{	
				lOffsetJudge = (i-1)*wBytesPerLine + j*3;
				//如果上面的点为白色
				if(*(lpData + lOffsetJudge) == 255)
				{	//设置为白色，并继续循环
					*(lpTemp + lOffset++) = 255;
					*(lpTemp + lOffset++) = 255;
					*(lpTemp + lOffset++) = 255;
					continue;
				}

				//考察下面的点
				lOffsetJudge = (i+1)*wBytesPerLine + j*3;
				if(*(lpData + lOffsetJudge) == 255)
				{
					*(lpTemp + lOffset++) = 255;
					*(lpTemp + lOffset++) = 255;
					*(lpTemp + lOffset++) = 255;
					continue;
				}
				
				//考察左边的点
				lOffsetJudge = i*wBytesPerLine + (j-1)*3;
				if(*(lpData + lOffsetJudge) == 255)
				{
					*(lpTemp + lOffset++) = 255;
					*(lpTemp + lOffset++) = 255;
					*(lpTemp + lOffset++) = 255;
					continue;
				}
				//考察右边的点
				lOffsetJudge = i*wBytesPerLine + (j+1)*3;
				if(*(lpData + lOffsetJudge) == 255)
				{
					*(lpTemp + lOffset++) = 255;
					*(lpTemp + lOffset++) = 255;
					*(lpTemp + lOffset++) = 255;
					continue;
				}
				//如果上下左右都是黑色点，则把暂时区域的点设置为黑色
				lOffset = i*wBytesPerLine + j*3;
				*(lpTemp + lOffset++) = 0;
				*(lpTemp + lOffset++) = 0;
				*(lpTemp + lOffset++) = 0;

			}
				
		}
		//处理图象四周的点，设置为黑色
		for(i=0; i<height; i++)
		{
			lOffset = i*wBytesPerLine;
			{
				*(lpTemp + lOffset++) = 0;
				*(lpTemp + lOffset++) = 0;
				*(lpTemp + lOffset++) = 0;
			}
		}

		for(i=0; i<height; i++)
		{
			lOffset = i*wBytesPerLine + (width-1)*3;
			{
				*(lpTemp + lOffset++) = 0;
				*(lpTemp + lOffset++) = 0;
				*(lpTemp + lOffset++) = 0;
			}
		}

		for(i=0; i<width; i++)
		{
			lOffset = i*3;
			{
				*(lpTemp + lOffset++) = 0;
				*(lpTemp + lOffset++) = 0;
				*(lpTemp + lOffset++) = 0;
			}
		}

		for(i=0; i<width; i++)
		{
			lOffset = (height-1)*wBytesPerLine + i*3;
			{
				*(lpTemp + lOffset++) = 0;
				*(lpTemp + lOffset++) = 0;
				*(lpTemp + lOffset++) = 0;
			}
		}
		//把暂时区域的点拷贝到原句柄区域下面
		memcpy(lpData, lpTemp, wBytesPerLine*height);
		delete [] lpTemp;
		::GlobalUnlock((HGLOBAL) m_hDIB);
}

void CFaceDetectionDoc::Erasion()
{
	LPBITMAPINFOHEADER lpbi;
	lpbi = (LPBITMAPINFOHEADER)::GlobalLock((HGLOBAL) m_hDIB);//读取头文件
	lLineBytesMulspec = WIDTHBYTES((lpbi->biWidth)*24);
	::GlobalUnlock((HGLOBAL) m_hDIB);
	int width,height;
	LPBYTE lpData;
	long wBytesPerLine;
	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) m_hDIB);	
	// 获取DIB宽度
	width= (int) ::DIBWidth(lpDIB);		
	// 获取DIB高度
	height= (int) ::DIBHeight(lpDIB);
	lpData = (unsigned char*)::FindDIBBits(lpDIB);
	//得到图片每行的象素所占字节个数
	wBytesPerLine = lLineBytesMulspec;
	//申请一块和数据区大小相同的内存
	LPBYTE lpTemp;
	lpTemp = (LPBYTE) new BYTE[wBytesPerLine * height];	
	long lOffsetJudge;
	long lOffset;
	//下面的循环实现腐蚀功能
	for (int i=1; i<height-1; i++)
		for (int j=1; j<width-1; j++)
		{
			lOffset = i*wBytesPerLine + j*3;
			//如果为白色点
			if (*(lpData+lOffset) == 255)
			{	
				//考察上面的点
				lOffsetJudge = (i-1)*wBytesPerLine + j*3;
				//如果是黑色就把原来的点设置为黑色，并接着循环
				if (*(lpData + lOffsetJudge) ==0)
				{
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					continue;
				}
				//考察下面的点
				lOffsetJudge =  (i+1)*wBytesPerLine + j*3;
				if (*(lpData + lOffsetJudge) ==0)
				{
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					continue;
				}
				//左面的点
				lOffsetJudge = i*wBytesPerLine + (j-1)*3;
				if (*(lpData + lOffsetJudge) ==0)
				{
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					continue;
				}
				//右面的点
				lOffsetJudge = i*wBytesPerLine + (j+1)*3;
				if (*(lpData + lOffsetJudge) ==0)
				{
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					continue;
				}
				//如果上下左右四个点都是白色，则设置为白色
				lOffset = i*wBytesPerLine + j*3;
				*(lpTemp + lOffset)   = 255;
				*(lpTemp + lOffset+1) = 255;
				*(lpTemp + lOffset+2) = 255;
				
			}
			//如果当前点为黑色，则在暂时的目标区域中设置为黑色
			else
			{
				*(lpTemp + lOffset)   = 0;
				*(lpTemp + lOffset+1) = 0;
				*(lpTemp + lOffset+2) = 0;
			}
		}
		
		//把图象周边的点全部设置为黑色
		for(i=0; i<height; i++)
		{
			lOffset = i*wBytesPerLine;
				*(lpTemp + lOffset)   = 0;
				*(lpTemp + lOffset+1) = 0;
				*(lpTemp + lOffset+2) = 0;

		}
		
		for(i=0; i<height; i++)
		{
			lOffset = i*wBytesPerLine + (width-1)*3;
				*(lpTemp + lOffset)   = 0;
				*(lpTemp + lOffset+1) = 0;
				*(lpTemp + lOffset+2) = 0;

		}

	for (i=0; i<width; i++)
		{
			lOffset =i*3;
				*(lpTemp + lOffset)   = 0;
				*(lpTemp + lOffset+1) = 0;
				*(lpTemp + lOffset+2) = 0;

		}
	
	for (i=0; i<width; i++)
		{
			lOffset = (height-1)*wBytesPerLine + i*3;
				*(lpTemp + lOffset)   = 0;
				*(lpTemp + lOffset+1) = 0;
				*(lpTemp + lOffset+2) = 0;

		}
	//把暂时区域的点拷贝到原句柄区域下面
	memcpy(lpData, lpTemp, wBytesPerLine*height);
	delete [] lpTemp;
	::GlobalUnlock((HGLOBAL) m_hDIB);
}
void CFaceDetectionDoc::ErasionMouse()
{
	LPBITMAPINFOHEADER lpbi;
	lpbi = (LPBITMAPINFOHEADER)::GlobalLock((HGLOBAL) m_hDIB);//读取头文件
	lLineBytesMulspec = WIDTHBYTES((lpbi->biWidth)*24);
	::GlobalUnlock((HGLOBAL) m_hDIB);
	int width,height;
	LPBYTE lpData;
	long wBytesPerLine;
	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) m_hDIB);	
	// 获取DIB宽度
	width= (int) ::DIBWidth(lpDIB);		
	// 获取DIB高度
	height= (int) ::DIBHeight(lpDIB);
	lpData = (unsigned char*)::FindDIBBits(lpDIB);
	//得到图片每行的象素所占字节个数
	wBytesPerLine = lLineBytesMulspec;
	//申请一块和数据区大小相同的内存
	LPBYTE lpTemp;
	lpTemp = (LPBYTE) new BYTE[wBytesPerLine * height];	
	long lOffsetJudge;
	long lOffset;
	//下面的代码实现腐蚀功能
	for (int i=1; i<height-1; i++)
		for (int j=1; j<width-1; j++)
		{	
			//如果当前点为白色
			lOffset = i*wBytesPerLine + j*3;
			if (*(lpData+lOffset) == 255)
			{
				
				//判断左边的点，如果是黑色的就把暂时区域中的对应点设置为黑色
				lOffsetJudge = i*wBytesPerLine + (j-1)*3;
				if (*(lpData + lOffsetJudge) ==0)
				{
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					continue;
				}
				//考察右边的点
				lOffsetJudge =i*wBytesPerLine + (j+1)*3;
				if (*(lpData + lOffsetJudge) ==0)
				{
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					continue;
				}

				//如果左右两边的点都是白色把点设置为白色
				lOffset = i*wBytesPerLine + j*3;
				*(lpTemp + lOffset)   = 255;
				*(lpTemp + lOffset+1) = 255;
				*(lpTemp + lOffset+2) = 255;
				
			}
			//如果当前点为黑色，则把暂时区域中对应点设置为黑色
			else
			{
				*(lpTemp + lOffset)   = 0;
				*(lpTemp + lOffset+1) = 0;
				*(lpTemp + lOffset+2) = 0;
			}
		}
		//把图象四周的点设置为黑色
		for(i=0; i<height; i++)
		{
			lOffset = i*wBytesPerLine;
				*(lpTemp + lOffset)   = 0;
				*(lpTemp + lOffset+1) = 0;
				*(lpTemp + lOffset+2) = 0;

		}
		
		for(i=0; i<height; i++)
		{
			lOffset = i*wBytesPerLine + (width-1)*3;
				*(lpTemp + lOffset)   = 0;
				*(lpTemp + lOffset+1) = 0;
				*(lpTemp + lOffset+2) = 0;

		}

	for (i=0; i<width; i++)
		{
			lOffset = i*3;
				*(lpTemp + lOffset)   = 0;
				*(lpTemp + lOffset+1) = 0;
				*(lpTemp + lOffset+2) = 0;

		}
	
	for (i=0; i<width; i++)
		{
			lOffset = (height-1)*wBytesPerLine + i*3;
				*(lpTemp + lOffset)   = 0;
				*(lpTemp + lOffset+1) = 0;
				*(lpTemp + lOffset+2) = 0;

		}
	//把暂时区域的点拷贝到原句柄下
	memcpy(lpData,lpTemp,wBytesPerLine*height);
	delete [] lpTemp;
	::GlobalUnlock((HGLOBAL) m_hDIB);

}

void CFaceDetectionDoc::DeleteFalseArea()
{
	int PixelNum[255];
	LPBITMAPINFOHEADER lpbi;
	lpbi = (LPBITMAPINFOHEADER)::GlobalLock((HGLOBAL) m_hDIB);//读取头文件
	lLineBytesMulspec = WIDTHBYTES((lpbi->biWidth)*24);
	::GlobalUnlock((HGLOBAL) m_hDIB);
	int width,height;
	LPBYTE lpData;
	long wBytesPerLine;
	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) m_hDIB);	
	// 获取DIB宽度
	width= (int) ::DIBWidth(lpDIB);		
	// 获取DIB高度
	height= (int) ::DIBHeight(lpDIB);
	lpData = (unsigned char*)::FindDIBBits(lpDIB);
	//得到图片每行的象素所占字节个数
	wBytesPerLine = lLineBytesMulspec;
	long lOffset;	
	//初始化象素累计数组
	for (int i=0; i<255; i++)
	{
		PixelNum[i] = 0;
	}	
	int calNum =1;
	for (i=0; i<height; i++)
		for (int j=0; j<width; j++)
		{
			lOffset = i*wBytesPerLine + j*3;
			//如果象素为白色
			if (*(lpData + lOffset)==255)
			{	
				//递归统计该区域连续的白色点象素点个数
				RecursiveCal(lpData, i,j,wBytesPerLine, PixelNum[calNum],calNum);
				calNum++;
			}
		}
		
		for (i=0; i<calNum; i++)
		{	
			//如果象素点个数小于一定数目则把这个标志设置为0
			if (PixelNum[i] < AREAPIXEL)
			{
				PixelNum[i] = 0;
			}
		}
		//下面的循环根据标志数组来最终设定图象的颜色
		for(i=0; i<height; i++)
			for (int j=0; j<width; j++)
			{
				lOffset = i*wBytesPerLine + j*3;
				int num = *(lpData + lOffset);
				//如果当前点不是黑色点
				if(num != 0)
				{	
					//如果标志数组为0，则设置为黑色
					if(PixelNum[num] == 0)
					{
						*(lpData+lOffset++) =0;
						*(lpData+lOffset++) =0;
						*(lpData+lOffset++) =0;
					}
					//否则设置为白色
					else
					{
						*(lpData+lOffset++) =255;
						*(lpData+lOffset++) =255;
						*(lpData+lOffset++) =255;
					}
				}
			}
}
void CFaceDetectionDoc::RecursiveCal(LPBYTE lpData, int y, int x, WORD wBytesPerLine, int &pixelNum, int num)
{	
	long lOffset;
	
	lOffset = y*wBytesPerLine + x*3;
	//如果当前点为白色点
	if(*(lpData+lOffset) == 255)
	{	
		//把当前点大小设置成为序号值
		*(lpData+lOffset++) = num;
		*(lpData+lOffset++) = num;
		*(lpData+lOffset++) = num;
		//象素个数加一
		pixelNum++;
	
	int tempx;
	int tempy;
	
	//递归当前点上面的点
	tempy = y-1;
	tempx = x;
	RecursiveCal(lpData,tempy,tempx,wBytesPerLine,pixelNum,num);
	
	//下面的点
	tempy = y+1;
	tempx = x;
	RecursiveCal(lpData,tempy,tempx,wBytesPerLine,pixelNum,num);
	
	//左边的点
	tempy = y;
	tempx = x-1;
	RecursiveCal(lpData,tempy,tempx,wBytesPerLine,pixelNum,num);
	//右边的点
	tempy = y;
	tempx = x+1;
	RecursiveCal(lpData,tempy,tempx,wBytesPerLine,pixelNum,num);
	
	}

}

void  CFaceDetectionDoc::FaceLocate(CRect faceLocation[10], int &faceNum)
{	
	HANDLE  hDIBTemp;
	hDIBTemp = CopyHandle(m_hDIB);
	LPBITMAPINFOHEADER lpbi;
	lpbi = (LPBITMAPINFOHEADER)::GlobalLock((HGLOBAL) m_hDIB);//读取头文件
	lLineBytesMulspec = WIDTHBYTES((lpbi->biWidth)*24);
	::GlobalUnlock((HGLOBAL) m_hDIB);
	//保存当前数据
	int width,height;
	LPBYTE lpData;
	long wBytesPerLine;
	wBytesPerLine = lLineBytesMulspec;
	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) m_hDIB);	
	// 获取DIB宽度
	width= (int) ::DIBWidth(lpDIB);		
	// 获取DIB高度
	height= (int) ::DIBHeight(lpDIB);
	lpData = (unsigned char*)::FindDIBBits(lpDIB);
	//得到图片每行的象素所占字节个数
	long lOffset;
	//人脸数目初始化为0
	faceNum =0;
	for(int k=0; k<10; k++)
	{	
		//初始化区域
		faceLocation[k].bottom = 0;
		faceLocation[k].top = height-1;
		faceLocation[k].right = 0;
		faceLocation[k].left = width-1;
	}

	for(int i=0; i<height; i++)            //计算人脸数目
		for (int j=0; j<width; j++)
		{	
			//偏移
			lOffset = i*wBytesPerLine + j*3;
			int num;
			//当前点的数值
			num = *(lpData + lOffset);
			if (num !=0)//不是黑色
			{	
				//递归计算
				RecursiveLocateRect(lpData, wBytesPerLine, i, j, num, faceLocation[faceNum]);
				faceNum++;
			}
		}
	::GlobalUnlock((HGLOBAL) m_hDIB);
	::GlobalFree((HGLOBAL) m_hDIB);
	//数值还原 
	m_hDIB = (HDIB)CopyHandle(hDIBTemp);
	LPSTR lpDIB2 = (LPSTR) ::GlobalLock((HGLOBAL) m_hDIB);
	lpData = (unsigned char*)::FindDIBBits(lpDIB2);
	//int square = faceLocation[]
	for (i=0; i<faceNum; i++)
		for (int j=faceLocation[i].top; j<faceLocation[i].bottom; j++)
		{	
			//把得到的人脸区域用绿色矩形标注，处理竖直的两条边
			lOffset = j*wBytesPerLine + faceLocation[i].left*3;
			*(lpData + lOffset++) = 0;
			*(lpData + lOffset++) = 255;
			*(lpData + lOffset++) = 0;
			lOffset = j*wBytesPerLine + faceLocation[i].right*3;
			*(lpData + lOffset++) = 0;
			*(lpData + lOffset++) = 255;
			*(lpData + lOffset++) = 0;

		}

		for (i=0; i<faceNum; i++)
		for (int j=faceLocation[i].left; j<faceLocation[i].right; j++)
		{	
			//处理水平的两天矩形边
			lOffset = faceLocation[i].top*wBytesPerLine + j*3;
			*(lpData + lOffset++) = 0;
			*(lpData + lOffset++) = 255;
			*(lpData + lOffset++) = 0;
			lOffset = faceLocation[i].bottom*wBytesPerLine + j*3;
			*(lpData + lOffset++) = 0;
			*(lpData + lOffset++) = 255;
			*(lpData + lOffset++) = 0;

		}
	
		::GlobalFree((HGLOBAL)hDIBTemp);	
		::GlobalUnlock((HGLOBAL) m_hDIB);
}

HANDLE CFaceDetectionDoc::CopyHandle( HANDLE  hSrc)
{	
	HANDLE  hDst;
	LPBITMAPINFOHEADER lpbi;
	int width,height;
	lpbi = (LPBITMAPINFOHEADER)::GlobalLock(hSrc);
	width = lpbi->biWidth;
	height = lpbi->biHeight;
	hDst = ::GlobalAlloc(GMEM_MOVEABLE,lpbi->biSize+lpbi->biSizeImage);
	if(!hDst)
		return NULL;
	LPBYTE lpDest;
	lpDest = (LPBYTE)::GlobalLock(hDst);
	memcpy(lpDest,(LPBYTE)lpbi,lpbi->biSize+lpbi->biSizeImage);
	::GlobalUnlock(hSrc);
	::GlobalUnlock(hDst);
	return hDst;
}
void CFaceDetectionDoc::RecursiveLocateRect(LPBYTE lpData,WORD wBytesPerLine, int y, int x, int num, CRect &faceRect)
{	
	long lOffset;
	//得到偏移
	lOffset = y*wBytesPerLine + x*3;
	//数值判断
	if(*(lpData + lOffset) == num)
	{	
		//更改颜色为黑色
	//	*(lpData + lOffset++) = 0;
	//	*(lpData + lOffset++) = 0;
	//	*(lpData + lOffset++) = 0;
		//修改矩形的上下左右四个点位置
		if(faceRect.bottom < y)
		{
			faceRect.bottom = y;
		}

		if(faceRect.top > y)
		{
			faceRect.top = y;
		}

		if(faceRect.right < x)
		{
			faceRect.right = x;
		}

		if(faceRect.left > x)
		{
			faceRect.left = x;
		}
		//上下左右调用本函数进行区域判定
		RecursiveLocateRect(lpData, wBytesPerLine, y-1, x, num,faceRect);
		RecursiveLocateRect(lpData, wBytesPerLine, y+1, x, num, faceRect);
		RecursiveLocateRect(lpData, wBytesPerLine, y, x-1, num, faceRect);
		RecursiveLocateRect(lpData, wBytesPerLine, y, x+1, num, faceRect);
	}
	
}
void CFaceDetectionDoc::EyeMapR(LPBYTE lpRgb, const LPBYTE lpYcc,  WORD wBytesPerLine, CRect faceLocation)
{
	long lOffset;
	int cr;
	int cb;

	for(int i=faceLocation.top; i<=faceLocation.bottom; i++)
		for (int j=faceLocation.left; j<=faceLocation.right; j++)
		{
			lOffset =i*wBytesPerLine + j*3;
			cr = *(lpYcc + lOffset +1);
			cb = *(lpYcc + lOffset +2);
			*(lpRgb + lOffset++) = cr;
			*(lpRgb + lOffset++) = cr;
			*(lpRgb + lOffset++) = cr;
		}
	
}
void CFaceDetectionDoc::Crmap()
{
	LPBYTE lpRB;
	LPBITMAPINFOHEADER lpbi;
	lpbi = (LPBITMAPINFOHEADER)::GlobalLock((HGLOBAL) m_hDIB);//读取头文件
	lLineBytesMulspec = WIDTHBYTES((lpbi->biWidth)*24);
	::GlobalUnlock((HGLOBAL) m_hDIB);
	int width,height;
	LPBYTE lpData;
	long wBytesPerLine;
	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) m_hDIB);	
	// 获取DIB宽度
	width= (int) ::DIBWidth(lpDIB);		
	// 获取DIB高度
	height= (int) ::DIBHeight(lpDIB);
	//得到图片每行的象素所占字节个数
	wBytesPerLine = lLineBytesMulspec;
	lpRB = new BYTE[wBytesPerLine * height];
	RgbtoYcb(m_hDIB,lpRB);
	lpData = (unsigned char*)::FindDIBBits(lpDIB);
	EyeMapR(lpData,lpRB,wBytesPerLine,CRect(0,0,width-1,height-1));
	::GlobalUnlock((HGLOBAL) m_hDIB);
}
void CFaceDetectionDoc::EyeMapC(LPBYTE lpRgb, const LPBYTE lpYcc,  WORD wBytesPerLine, CRect faceLocation)
{
	long lOffset;
	int cr;
	int cb;
	//根据传进来的矩形区域进行眼睛的色度匹配
	for(int i=faceLocation.top; i<=faceLocation.bottom; i++)
		for (int j=faceLocation.left; j<=faceLocation.right; j++)
		{	
			//得到Cr，Cb数值
			lOffset = i*wBytesPerLine + j*3;
			cr = *(lpYcc + lOffset +1);
			cb = *(lpYcc + lOffset +2);
			//标志
			bool lab;
			//判断Cb分量的数值，并修改标志
			int cmap = cb -120;//116 ;
			if(cmap >-1 && cmap <4)
				lab = true;
			else
				lab = false;
			//判断Cr分量的数值，并修改标志
			 cmap =  cr- 143;//144  ;
			if(cmap <=-2 || cmap>= 2)
			{
				lab = false;
				
			}
			//根据标志设定图像颜色
			if(lab)
				cmap = 255;
			else
				cmap = 0;
			//保存图象颜色
			*(lpRgb + lOffset++) = cmap;
			*(lpRgb + lOffset++) = cmap;
			*(lpRgb + lOffset++) = cmap;
		}	
}
void CFaceDetectionDoc::EyeMappingC()//调用EyeMapC函数进行眼睛的色度匹配
{
	LPBYTE lpYcc2;
	LPBITMAPINFOHEADER lpbi;
	lpbi = (LPBITMAPINFOHEADER)::GlobalLock((HGLOBAL) m_hDIB);//读取头文件
	lLineBytesMulspec = WIDTHBYTES((lpbi->biWidth)*24);
	::GlobalUnlock((HGLOBAL) m_hDIB);
	int width,height;
	LPBYTE lpData;
	long wBytesPerLine;
	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) m_hDIB);	
	// 获取DIB宽度
	width= (int) ::DIBWidth(lpDIB);		
	// 获取DIB高度
	height= (int) ::DIBHeight(lpDIB);
	//得到图片每行的象素所占字节个数
	wBytesPerLine = lLineBytesMulspec;
	lpYcc2 = new BYTE[wBytesPerLine * height];
	RgbtoYcb( m_hDIBtemp,lpYcc2);//转化为YCC空间
	lpData = (unsigned char*)::FindDIBBits(lpDIB);
	//memcpy(lpData,gDib.YcctoRgb(lpYcc,gwBytesPerLine,gheight,gwidth),gwBytesPerLine*gheight);
	EyeMapC(lpData,lpYcc2,wBytesPerLine,CRect(0,0,width-1,height-1));
	for(int i=0; i<height; i++)
		for (int j=0; j<width; j++)
		{
			long lOffset;
			lOffset = i*wBytesPerLine + j*3;
			if(*(lpData + lOffset) == 255)
			{
				emymapc[i][j] = true;
			}
		}
	::GlobalUnlock((HGLOBAL) m_hDIB);
}

void CFaceDetectionDoc::EyeMapL(LPBYTE lpRgb, WORD wBytesPerLine, CRect faceLocation)
{
	int r;
	int g;
	int b;
	int gray ;
	long lOffset;
	//下面的循环实现眼睛的亮度匹配
	for (int i=faceLocation.top; i<=faceLocation.bottom; i++)
		for (int j=faceLocation.left; j<=faceLocation.right; j++)
		{
			lOffset = i*wBytesPerLine + j*3;
			//得到rgb值
			b = *(lpRgb + lOffset);
			g = *(lpRgb + lOffset+1);
			r = *(lpRgb + lOffset+2);
			//计算得到灰度
			gray = (r*10+g*30+b*60)/100;
			//根据眼睛的亮度区域来设定图象的数值
			if(/*100*/120<gray && /*125*/160>gray)
				gray =255;
			else
				gray = 0;
			*(lpRgb + lOffset++) = gray;
			*(lpRgb + lOffset++) = gray;
			*(lpRgb + lOffset++) = gray;
		}
}
void CFaceDetectionDoc::EyeMappingL()//调用EyeMapC函数进行眼睛的色度匹配
{
	LPBYTE lpYcc2;
	LPBYTE lpDataR,lpDataD;
	LPBITMAPINFOHEADER lpbi;
	lpbi = (LPBITMAPINFOHEADER)::GlobalLock((HGLOBAL) m_hDIB);//读取头文件
	lLineBytesMulspec = WIDTHBYTES((lpbi->biWidth)*24);
	::GlobalUnlock((HGLOBAL) m_hDIB);
	int width,height;
	LPBYTE lpData;
	long wBytesPerLine;
	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) m_hDIB);
	LPSTR lpDIBtemp = (LPSTR) ::GlobalLock((HGLOBAL) m_hDIBtemp);
	// 获取DIB宽度
	width= (int) ::DIBWidth(lpDIB);		
	// 获取DIB高度
	height= (int) ::DIBHeight(lpDIB);
	//得到图片每行的象素所占字节个数
	wBytesPerLine = lLineBytesMulspec;
	lpYcc2 = new BYTE[wBytesPerLine * height];
	lpDataR = (unsigned char*)::FindDIBBits(lpDIBtemp);
	RgbtoYcb(m_hDIBtemp,lpYcc2);
	lpDataD = (unsigned char*)::FindDIBBits(lpDIB);
	memcpy(lpDataD,lpDataR,wBytesPerLine*height);
	EyeMapL(lpDataD,wBytesPerLine, CRect(0,0,width-1,height-1));
	for (int i=0; i<height; i++)
		for (int j=0; j<width; j++)
		{
			long lOffset;
			lOffset =  i*wBytesPerLine + j*3;
			if(*(lpDataD + lOffset) == 255)
			{
				emymapl[i][j] = true;
			}
		}
	::GlobalUnlock((HGLOBAL) m_hDIB);
	::GlobalUnlock((HGLOBAL) m_hDIBtemp);
}

void CFaceDetectionDoc::Eyemap() 
{
	LPBITMAPINFOHEADER lpbi;
	lpbi = (LPBITMAPINFOHEADER)::GlobalLock((HGLOBAL) m_hDIB);//读取头文件
	lLineBytesMulspec = WIDTHBYTES((lpbi->biWidth)*24);
	::GlobalUnlock((HGLOBAL) m_hDIB);
	int width,height;
	long wBytesPerLine;
	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) m_hDIB);	
	// 获取DIB宽度
	width= (int) ::DIBWidth(lpDIB);		
	// 获取DIB高度
	height= (int) ::DIBHeight(lpDIB);
	//得到图片每行的象素所占字节个数
	wBytesPerLine = lLineBytesMulspec;
	LPBYTE lpData;
	long lOffset;
	lpData = (unsigned char*)::FindDIBBits(lpDIB);
	for (int i=0; i<height; i++)
		for (int j=0; j<width; j++)
		{
			lOffset =  i*wBytesPerLine + j*3;
			if( emymapc[i][j] && emymapl[i][j])
			{
				*(lpData + lOffset++) = 255;
				*(lpData + lOffset++) = 255;
				*(lpData + lOffset++) = 255;
			}

			else
			{
				*(lpData + lOffset++) = 0;
				*(lpData + lOffset++) = 0;
				*(lpData + lOffset++) = 0;
			}
		}
}
void CFaceDetectionDoc::DeleteFasleEye(CRect facelocation)
{
	LPBITMAPINFOHEADER lpbi;
	lpbi = (LPBITMAPINFOHEADER)::GlobalLock((HGLOBAL) m_hDIB);//读取头文件
	lLineBytesMulspec = WIDTHBYTES((lpbi->biWidth)*24);
	::GlobalUnlock((HGLOBAL) m_hDIB);
	int width,height;
	long wBytesPerLine;
	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) m_hDIB);	
	// 获取DIB宽度
	width= (int) ::DIBWidth(lpDIB);		
	// 获取DIB高度
	height= (int) ::DIBHeight(lpDIB);
	//得到图片每行的象素所占字节个数
	wBytesPerLine = lLineBytesMulspec;
	LPBYTE lpData;
	long lOffset;
	lpData = (unsigned char*)::FindDIBBits(lpDIB);
	for (int i=0; i<height; i++)
		for (int j=0; j<width; j++)
		{
			lOffset =  i*wBytesPerLine + j*3;
			if(*(lpData + lOffset) == 255)
			{
				if(i<(facelocation.bottom+facelocation.top)/2)
				{
					*(lpData + lOffset++) = 0;
					*(lpData + lOffset++) = 0;
					*(lpData + lOffset++) = 0;
				}
			}
		}
	::GlobalUnlock((HGLOBAL) m_hDIB);
}

/////////////////////*计算人眼中心的位置*///////////////////////
void CFaceDetectionDoc::EyeCenter(CPoint &eye1, CPoint &eye2)
{
	
	LPBITMAPINFOHEADER lpbi;
	lpbi = (LPBITMAPINFOHEADER)::GlobalLock((HGLOBAL) m_hDIB);//读取头文件
	lLineBytesMulspec = WIDTHBYTES((lpbi->biWidth)*24);
	::GlobalUnlock((HGLOBAL) m_hDIB);
	int width,height;
	long wBytesPerLine;
	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) m_hDIB);	
	// 获取DIB宽度
	width= (int) ::DIBWidth(lpDIB);		
	// 获取DIB高度
	height= (int) ::DIBHeight(lpDIB);
	//得到图片每行的象素所占字节个数
	wBytesPerLine = lLineBytesMulspec;
	LPBYTE lpData;
	long lOffset;
	lpData = (unsigned char*)::FindDIBBits(lpDIB);
	
	int pixelnum =0;
	int num =0;
	CRect faceLocation(0,0,width-1,height-1);
	//考察人脸区域
	for(int i=faceLocation.top; i<faceLocation.bottom; i++)
		for (int j=faceLocation.left; j<faceLocation.right; j++)
		{
			lOffset =  i*wBytesPerLine + j*3;
			//白色点
			if(*(lpData + lOffset) == 255)
				//递归统计象素并修改象素值
				RecursiveCal(lpData,i,j,wBytesPerLine,pixelnum,++num);
		}
		//初始化眼睛的坐标
		eye1.x =0;
		eye1.y =0;
		eye2.x =0;
		eye2.y =0;
		//初始化象素点个数
		int eye1count=0;
		int eye2count =0;
		for (i=faceLocation.top; i<faceLocation.bottom; i++)
			for (int j=faceLocation.left; j<faceLocation.right; j++)
			{
				lOffset =  i*wBytesPerLine + j*3;
				//如果象素点的数值为1
				if(*(lpData + lOffset) == 1)
				{	
					//眼睛1的横坐标和纵坐标加上当前点的坐标值
					eye1.x +=j;
					eye1.y +=i;
					eye1count++;
					//把当前点改成白色
					*(lpData + lOffset++) = 255;
					*(lpData + lOffset++) = 255;
					*(lpData + lOffset++) = 255;

				}
				//如果当前象素的数值为2
				else if(*(lpData + lOffset) == 2)
				{	
					//眼睛2的横坐标和纵坐标加上当前点的坐标值
					eye2.x +=j;
					eye2.y +=i;
					//象素点个数加一
					eye2count++;
					//把当前点设置为白色
					*(lpData + lOffset++) = 255;
					*(lpData + lOffset++) = 255;
					*(lpData + lOffset++) = 255;
				}
			}
			//计算眼睛的中心点坐标
			eye1.x /=eye1count;
			eye1.y /=eye1count;
			eye2.x /=eye2count;
			eye2.y /=eye2count;
			//把中心点设置为绿色
			lOffset = eye1.y*wBytesPerLine + eye1.x*3; 
			*(lpData + lOffset++) = 0;
			*(lpData + lOffset++) = 255;
			*(lpData + lOffset++) = 0;

			lOffset = eye2.y*wBytesPerLine + eye2.x*3; 
			*(lpData + lOffset++) = 0;
			*(lpData + lOffset++) = 255;
			*(lpData + lOffset++) = 0;
	::GlobalUnlock((HGLOBAL) m_hDIB);
}

void  CFaceDetectionDoc::FunctionMouseMap(LPBYTE lpRgb, const LPBYTE lpYcc,  WORD wBytesPerLine, CRect faceLocation)
{	
	//下面的循环在人脸的区域内实现嘴巴的匹配
	for (int i=faceLocation.top; i<faceLocation.bottom; i++)
		for (int j=faceLocation.left; j<faceLocation.right; j++)
		{	
			//得到偏移
			long lOffset = i*wBytesPerLine + j*3;
			//得到cr，cb的数值
			int cr = *(lpYcc+lOffset+1);
			int cb = *(lpYcc+lOffset+2);
			//标志
			bool lab;
			int mapm;
			//根据cr的数值设定标志
			cr = cr-157;//143;
			if(cr <-6 || cr>6)
			{
				cr = 0;
				
			}
			cr *=cr;
			
			if(cr>16)
				 lab = true;
			else
				lab = false;
			//根据cb的时值设定标志
			cb= cb-118;//120;
			if(cb<-5 || cb >5)
				
			{
				cb = 0;
				if(lab = true)
					lab = false;
			}
			//如果cr，cb两项数值都在设定的范围之内，则设定颜色位白色，否则黑色
			if(lab)
				mapm = 255;
			else
				mapm = 0;
			 
			*(lpRgb + lOffset++) = mapm;
			*(lpRgb + lOffset++) = mapm;
			*(lpRgb + lOffset++) = mapm;

			
		}
}
void  CFaceDetectionDoc::MouseMap()
{
	LPBYTE lpYcc2;
	LPBITMAPINFOHEADER lpbi;
	lpbi = (LPBITMAPINFOHEADER)::GlobalLock((HGLOBAL) m_hDIB);//读取头文件
	lLineBytesMulspec = WIDTHBYTES((lpbi->biWidth)*24);
	::GlobalUnlock((HGLOBAL) m_hDIB);
	int width,height;
	long wBytesPerLine;
	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) m_hDIB);	
	// 获取DIB宽度
	width= (int) ::DIBWidth(lpDIB);		
	// 获取DIB高度
	height= (int) ::DIBHeight(lpDIB);
	//得到图片每行的象素所占字节个数
	wBytesPerLine = lLineBytesMulspec;
	LPBYTE lpData;
	long lOffset;
	lpData = (unsigned char*)::FindDIBBits(lpDIB);
	lpYcc2 = new BYTE[wBytesPerLine * height];
	RgbtoYcb(m_hDIBtemp,lpYcc2);
	FunctionMouseMap(lpData,lpYcc2,wBytesPerLine,CRect(0,0,width-1,height-1));
	::GlobalUnlock((HGLOBAL) m_hDIB);

}
void CFaceDetectionDoc::DeleteScatePoint()
{	
	LPBITMAPINFOHEADER lpbi;
	lpbi = (LPBITMAPINFOHEADER)::GlobalLock((HGLOBAL) m_hDIB);//读取头文件
	lLineBytesMulspec = WIDTHBYTES((lpbi->biWidth)*24);
	::GlobalUnlock((HGLOBAL) m_hDIB);
	int width,height;
	long wBytesPerLine;
	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) m_hDIB);	
	// 获取DIB宽度
	width= (int) ::DIBWidth(lpDIB);		
	// 获取DIB高度
	height= (int) ::DIBHeight(lpDIB);
	//得到图片每行的象素所占字节个数
	wBytesPerLine = lLineBytesMulspec;
	LPBYTE lpData;
	long lOffset;
	lpData = (unsigned char*)::FindDIBBits(lpDIB);
	for (int i=0; i<height; i++)
		for(int j=0; j<width; j++)
		{	
			//得到偏移
			lOffset =i*wBytesPerLine + j*3;
			//如果当前点为白色点
			if(*(lpData + lOffset) == 255)
			{	
				//设定判断数组
				for(int ii = 0;ii<ImgRange;ii++)
					for (int jj=0; jj<ImgRange; jj++)
						this->lab[ii][jj] = false;
					//设定判断长度
					lenth=0;
					//判断是否为离散点
				bool judge = IsScaterPoint(j, i, width,height,lpData,wBytesPerLine,3,lab);
				if(!judge)
				{	
					//是离散点则把该点设置为黑色
					*(lpData + lOffset++) = 0;
					*(lpData + lOffset++) = 0;
					*(lpData + lOffset++) = 0;
				}
			}
		}
	::GlobalUnlock((HGLOBAL) m_hDIB);
}
BOOL CFaceDetectionDoc::IsScaterPoint(int x, int y, int width, int height, LPBYTE lpData,WORD wBytesPerLine,  int threshold,bool lab[m_HEIGHT][m_WIDTH])
{
	long lOffset;
	//得到数据的偏移
	lOffset = y*wBytesPerLine + x*3;
	//判断该点是否为白色以及是否计算过了
	if(*(lpData+lOffset) == 255 && lab[y][x] == false)
	{	
		//链长度加一
		lenth++;
		//更改标志位
		lab[y][x] = true;
		//如果链长度达到临界值则返回真
	if(lenth >= threshold)
		return true;
	//对右边点的边界判断以及标志位判断
	if(x+1<width && lab[y][x+1] == false)
	{	
		//递归调用本函数，对右边的点进行判断
		IsScaterPoint(x+1,y,width,height,lpData,wBytesPerLine,threshold,lab);
		if(lenth>=threshold)
			return true;
		
	}
	//处理左边的点
	if(x-1>=0 && lab[y][x-1] == false)
	{
		(IsScaterPoint(x-1,y,width,height,lpData,wBytesPerLine,threshold,lab));
		if(lenth>=threshold)
			return true;
		
	}
	//处理上面的点
	if(y-1>=0 && lab[y-1][x]==false)
	{
		(IsScaterPoint(x,y-1,width,height,lpData,wBytesPerLine,threshold,lab));
		if(lenth>=threshold)
			return true;
		
	}
	//处理下面的点
	if(y+1<height && lab[y+1][x]==false)
	{	(IsScaterPoint(x,y+1,width,height,lpData,wBytesPerLine,threshold,lab));
			if(lenth>=threshold)
			return true;
			
	}
	//处理右下的点
	if(y+1<height  && x+1 <width && lab[y+1][x+1]==false)
	{	(IsScaterPoint(x+1,y+1,width,height,lpData,wBytesPerLine,threshold,lab));
			if(lenth>=threshold)
			return true;
			
	}
	//处理左下的点
	if(y+1<height && x-1 >=0 && lab[y+1][x-1]==false)
	{	(IsScaterPoint(x-1,y+1,width,height,lpData,wBytesPerLine,threshold,lab));
			if(lenth>=threshold)
			return true;
			
	}
	//处理左上的点
	if(y-1>=0 && x-1 >=0 &&lab[y-1][x-1]==false)
	{	(IsScaterPoint(x-1,y-1,width,height,lpData,wBytesPerLine,threshold,lab));
			if(lenth>=threshold)
			return true;
			
	}
	//处理右上的点
	if(y-1<height && x+1<width && lab[y+1][x]==false)
	{	(IsScaterPoint(x+1,y-1,width,height,lpData,wBytesPerLine,threshold,lab));
			if(lenth>=threshold)
			return true;
			
	}
	}	
		//如果递归结束，长度达不到临界值，返回假
		return false;
}

void CFaceDetectionDoc::MouthCenter(CPoint &mouthLocation)
{
	LPBITMAPINFOHEADER lpbi;
	lpbi = (LPBITMAPINFOHEADER)::GlobalLock((HGLOBAL) m_hDIB);//读取头文件
	lLineBytesMulspec = WIDTHBYTES((lpbi->biWidth)*24);
	::GlobalUnlock((HGLOBAL) m_hDIB);
	int width,height;
	long wBytesPerLine;
	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) m_hDIB);	
	// 获取DIB宽度
	width= (int) ::DIBWidth(lpDIB);		
	// 获取DIB高度
	height= (int) ::DIBHeight(lpDIB);
	//得到图片每行的象素所占字节个数
	wBytesPerLine = lLineBytesMulspec;
	LPBYTE lpData;
	long lOffset;
	lpData = (unsigned char*)::FindDIBBits(lpDIB);
	
	//下面的三个变量用来累计嘴巴区域的象素的x，y和象素点数
	int xnum = 0 ;
	int ynum = 0 ;
	int count = 0;
	CRect faceLocation(0,0,width-1,height-1);
	for (int i=faceLocation.top; i<faceLocation.bottom; i++)
		for (int j=faceLocation.left; j<faceLocation.right; j++)
		{
			lOffset = i*wBytesPerLine + j*3;
			//白色点
			if(*(lpData + lOffset) == 255)
			{	
				//x值加
				xnum +=j;
				//y值加
				ynum +=i;
				//点数加
				count++;
			}
		}
		//得到中心点位置
	mouthLocation.x = xnum/count;
	mouthLocation.y = ynum/count;
	
	//把中心点设置位绿色
	lOffset = mouthLocation.y*wBytesPerLine + mouthLocation.x*3;
	*(lpData + lOffset++) =0;
	*(lpData + lOffset++) =255;
	*(lpData + lOffset++) =0;
	::GlobalUnlock((HGLOBAL) m_hDIB);
}
void CFaceDetectionDoc::EllipseFace(CPoint mouth, CPoint eye1, CPoint eye2,CRect faceLocation)
{
	LPBITMAPINFOHEADER lpbi;
	lpbi = (LPBITMAPINFOHEADER)::GlobalLock((HGLOBAL) m_hDIBtemp);//读取头文件
	lLineBytesMulspec = WIDTHBYTES((lpbi->biWidth)*24);
	::GlobalUnlock((HGLOBAL) m_hDIBtemp);
	int width,height;
	long wBytesPerLine;
	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) m_hDIBtemp);	
	// 获取DIB宽度
	width= (int) ::DIBWidth(lpDIB);		
	// 获取DIB高度
	height= (int) ::DIBHeight(lpDIB);
	//得到图片每行的象素所占字节个数
	wBytesPerLine = lLineBytesMulspec;
	LPBYTE lpData;
	long lOffset;
	lpData = (unsigned char*)::FindDIBBits(lpDIB);
	
	//用dda算法画三角形
	DdaLine(mouth,eye1,lpData,wBytesPerLine);
	DdaLine(mouth,eye2,lpData,wBytesPerLine);
	DdaLine(eye1,eye2,lpData,wBytesPerLine);
	/*
	
	//椭圆的中心点和两个焦点坐标
	int ellipsecenter_x;
	int ellipsecenter_y;
	int ellipseFocusTop_x;
	int ellipseFocusTop_y;
	int ellipseFocusBottom_x;
	int ellipseFocusBottom_y;
	
	//根据眼睛和嘴巴的坐标计算椭圆的中心点坐标
	ellipsecenter_x = (eye1.x + eye2.x + mouth.x )/3;
	ellipsecenter_y = (eye1.y + eye2.y)/2 -abs(eye2.x - eye1.x)/2;

	//上面的焦点
	ellipseFocusTop_x = ellipsecenter_x;
	ellipseFocusBottom_x = ellipsecenter_x;

	//下面的焦点
	ellipseFocusTop_y =  ellipsecenter_y + (eye1.y +eye2.y)/2 -mouth.y;
	ellipseFocusBottom_y = ellipsecenter_y - ((eye1.y +eye2.y)/2 -mouth.y)+2;

	//长轴
	int a = (eye1.x-eye2.x)*2-2;
	
	for (int i=0; i<height; i++)
		for (int j=0; j<width; j++)
		{	
			//得到一个点到两个焦点的距离和
			int lenth = sqrt(pow(j-ellipseFocusTop_x,2)+pow(i-ellipseFocusTop_y,2))
				+sqrt(pow(j-ellipseFocusBottom_x,2)+ pow(i-ellipseFocusBottom_y,2));
			//判断距离和与长轴的关系
			if(lenth<2*a+2 && lenth >2*a-2)
			{	
				//把点设置为绿色
				lOffset =i*wBytesPerLine + j*3;
				*(lpData + lOffset++) = 0;
				*(lpData + lOffset++) = 255;
				*(lpData + lOffset++) = 0;
			}
		}*/
		for (int j=faceLocation[0].top; j<faceLocation[0].bottom; j++)
		{	
			//把得到的人脸区域用绿色矩形标注，处理竖直的两条边
			lOffset = j*wBytesPerLine + faceLocation[0].left*3;
			*(lpData + lOffset++) = 0;
			*(lpData + lOffset++) = 255;
			*(lpData + lOffset++) = 0;
			lOffset = j*wBytesPerLine + faceLocation[0].right*3;
			*(lpData + lOffset++) = 0;
			*(lpData + lOffset++) = 255;
			*(lpData + lOffset++) = 0;

		}

		for (j=faceLocation[0].left; j<faceLocation[0].right; j++)
		{	
			//处理水平的两天矩形边
			lOffset = faceLocation[0].top*wBytesPerLine + j*3;
			*(lpData + lOffset++) = 0;
			*(lpData + lOffset++) = 255;
			*(lpData + lOffset++) = 0;
			lOffset = faceLocation[0].bottom*wBytesPerLine + j*3;
			*(lpData + lOffset++) = 0;
			*(lpData + lOffset++) = 255;
			*(lpData + lOffset++) = 0;

		}
	

	::GlobalUnlock((HGLOBAL) m_hDIBtemp);
	m_hDIB = (HDIB)CopyHandle(m_hDIBtemp);

}


void CFaceDetectionDoc::DdaLine(CPoint from, CPoint end, LPBYTE lpData, WORD wBytesPerLine)
{	
	//x，y的增量
	float delta_x;
	float delta_y;
	//x，y的坐标
	float x;
	float y;
	//x，y上的差值
	int dx;
	int dy;
	//总的步长
	int steps;
	int k;
	//得到x，y的差值
	dx = end.x - from.x;
	dy = end.y - from.y;
	//判断x，y上的差值大小，确定步长
	if(abs(dx) > abs(dy))
	{
		steps = abs(dx);
	}
	else
	{
		steps = abs(dy);
	}

	//得到每次增量的大小
	delta_x = (float)dx / (float)steps;
	delta_y = (float)dy / (float)steps;
	//设定x，y的起点
	x = (float)from.x;
	y = (float)from.y;

	//设定初始点的颜色为绿色
	long lOffset = y*wBytesPerLine + x*3;
	*(lpData + lOffset++) = 0;
	*(lpData + lOffset++) = 255;
	*(lpData + lOffset++) = 0;

	//根据计算得到的步长，把直线上的点填充成绿色
	for (k=1;k<=steps; k++)
	{	
		//x，y分别加上各自的增量
		x+=delta_x;
		y+=delta_y;
		//设置点的颜色
		lOffset = y*wBytesPerLine + x*3;
		*(lpData + lOffset++) = 0;
		*(lpData + lOffset++) = 255;
		*(lpData + lOffset++) = 0;
	}
	
}

void CFaceDetectionDoc::OnFileSaveAs(LPCTSTR lpszPathName) 
{
	CFile file;
	if(!file.Open(lpszPathName, CFile::modeCreate |// 打开文件
	  CFile::modeReadWrite | CFile::shareExclusive))
	{
		return;// 返回FALSE
	}
	BOOL bSuccess = FALSE;	
	bSuccess = ::SaveDIB(m_hDIB, file);	// 保存图象	
	file.Close();// 关闭文件	
	SetModifiedFlag(FALSE);// 重置胀标记为FALSE
	if (!bSuccess)
	{			
		AfxMessageBox("保存BMP图象时出错");// 提示出错
	}	
	
}
