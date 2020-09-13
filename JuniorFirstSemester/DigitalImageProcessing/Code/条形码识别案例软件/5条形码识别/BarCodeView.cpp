// BarCodeView.cpp : implementation of the CBarCodeView class
//

#include "stdafx.h"
#include "BarCode.h"

#include "BarCodeDoc.h"
#include "BarCodeView.h"

#include "DLGBW.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBarCodeView

IMPLEMENT_DYNCREATE(CBarCodeView, CView)

BEGIN_MESSAGE_MAP(CBarCodeView, CView)
	//{{AFX_MSG_MAP(CBarCodeView)
	ON_COMMAND(IDC_PIC_BW, OnPicBw)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(IDC_PIC_SB, OnPicSb)
	ON_COMMAND(IDC_PIC_GRAY, OnPicGray)
	ON_COMMAND(IDC_PIC_PRE, OnPicPre)
	ON_COMMAND(IDC_PIC_QZ, OnPicQz)
	ON_COMMAND(IDC_PIC_CUT, OnPicCut)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBarCodeView construction/destruction

CBarCodeView::CBarCodeView()
{
	// TODO: add construction code here
	m_isCut  = FALSE;
	m_isLBDown = FALSE;
	hDataOld = NULL;
	hDataNew = NULL;
	m_isBitmap = FALSE;
}

CBarCodeView::~CBarCodeView()
{
	if(hDataOld != NULL)
	{
		delete[] hDataOld;
	}
	if(hDataNew != NULL)
	{
		delete[] hDataNew;
	}
}

BOOL CBarCodeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBarCodeView drawing

void CBarCodeView::OnDraw(CDC* pDC)
{
	CBarCodeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	if (m_isBitmap)
	{
		CRect rect;
		GetWindowRect(&rect);
		int wdWith = rect.Width();
		int wdHeight = rect.Height();
		BITMAP bmpInfo;
		HBITMAP oldMap;
		CDC MemDC;
		
		MemDC.CreateCompatibleDC(pDC);
		GetObject(hBitmap , sizeof(BITMAP) , &bmpInfo);
		VERIFY(oldMap = (HBITMAP)SelectObject(MemDC , hBitmap));
		pDC->SetStretchBltMode(COLORONCOLOR);
		pDC->StretchBlt(0 , 0 , wdWith , wdHeight , &MemDC , 0 , 0 ,
			bmpInfo.bmWidth , bmpInfo.bmHeight , SRCCOPY);
		if (m_isLBDown)
		{
			pDC->MoveTo(m_start);
			pDC->LineTo(m_start.x , m_end.y);
			pDC->LineTo(m_end);
			pDC->LineTo(m_end.x , m_start.y);
			pDC->LineTo(m_start);
		}
	}
	else
	{
		pDC->TextOut(10 , 10 , "欢迎使用条形码识别系统！");
		pDC->TextOut(10 , 40 , "操作说明请参照帮助！");
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBarCodeView printing

BOOL CBarCodeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBarCodeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBarCodeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CBarCodeView diagnostics

#ifdef _DEBUG
void CBarCodeView::AssertValid() const
{
	CView::AssertValid();
}

void CBarCodeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBarCodeDoc* CBarCodeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBarCodeDoc)));
	return (CBarCodeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBarCodeView message handlers
void CBarCodeView::OnPicCut() 
{
	// TODO: Add your command handler code here
	if (m_isBitmap)
	{
		m_isCut = TRUE;
	}
	else
	{
		MessageBox("请打开一张BMP图片！");
	}
}

void CBarCodeView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_isCut)
	{
		m_isLBDown = TRUE;
		m_start = point;
	}

	CView::OnLButtonDown(nFlags, point);
}

void CBarCodeView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_isLBDown)
	{
		m_end = point;
		Invalidate(FALSE);
	}
	
	CView::OnMouseMove(nFlags, point);
}

void CBarCodeView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_isLBDown)
	{
		m_end = point;
		m_isLBDown = FALSE;
		m_isCut = FALSE;
		CRect rect;
		GetWindowRect(&rect);
		int wdWith = rect.Width();
		int wdHeight = rect.Height();
		int bmWith = bmInfo.bmWidth;
		int bmHeight = bmInfo.bmHeight;
		int cutX1,cutX2,cutY1,cutY2;
		if ((m_start.x<m_end.x) && (m_start.y<m_end.y))
		{
			cutX1 = m_start.x;
			cutY1 = m_start.y;
			cutX2 = m_end.x;
			cutY2 = m_end.y;
		} 
		else if ((m_start.x>m_end.x) && (m_start.y>m_end.y))
		{
			cutX1 = m_end.x;
			cutY1 = m_end.y;
			cutX2 = m_start.x;
			cutY2 = m_start.y;
		}
		else if ((m_start.x<m_end.x) && (m_start.y>m_end.y))
		{
			cutX1 = m_start.x;
			cutY1 = m_end.y;
			cutX2 = m_end.x;
			cutY2 = m_start.y;
		}
		else if ((m_start.x>m_end.x) && (m_start.y<m_end.y))
		{
			cutX1 = m_end.x;
			cutY1 = m_start.y;
			cutX2 = m_start.x;
			cutY2 = m_end.y;
		}

		cutX1 = (int)(bmWith*cutX1/wdWith);
		cutY1 = (int)(bmHeight*cutY1/wdHeight);
		cutX2 = (int)(bmWith*cutX2/wdWith);
		cutY2 = (int)(bmHeight*cutY2/wdHeight);
		
		int bmSize = bmInfo.bmHeight*bmInfo.bmWidth;
		for (int i=0 ; i<4*bmSize ; i++)		//保存处理前的图
		{
			hDataOld[i] = hDataNew[i];
		}
		int j;
		for	(j=0 ; j<cutY1 ; j++)
		{
			for (i=0 ; i<bmWith-1 ; i++)
			{
				hDataNew[4*j*bmWith+4*i] = 255;				//B
				hDataNew[4*j*bmWith+4*i+1] = 255;			//G
				hDataNew[4*j*bmWith+4*i+2] = 255;			//R
			}
		}
		for	(j=cutY1 ; j<cutY2 ; j++)
		{
			for (i=0 ; i<cutX1 ; i++)
			{
				hDataNew[4*j*bmWith+4*i] = 255;				//B
				hDataNew[4*j*bmWith+4*i+1] = 255;			//G
				hDataNew[4*j*bmWith+4*i+2] = 255;			//R
			}
		}
		for	(j=cutY1 ; j<cutY2 ; j++)
		{
			for (i=cutX2 ; i<bmWith-1 ; i++)
			{
				hDataNew[4*j*bmWith+4*i] = 255;				//B
				hDataNew[4*j*bmWith+4*i+1] = 255;			//G
				hDataNew[4*j*bmWith+4*i+2] = 255;			//R
			}
		}
		for	(j=cutY2 ; j<bmHeight-1 ; j++)
		{
			for (i=0 ; i<bmWith-1 ; i++)
			{
				hDataNew[4*j*bmWith+4*i] = 255;				//B
				hDataNew[4*j*bmWith+4*i+1] = 255;			//G
				hDataNew[4*j*bmWith+4*i+2] = 255;			//R
			}
		}
		m_bitmap.SetBitmapBits(4*bmSize , hDataNew);
		Invalidate(FALSE);
	}

	CView::OnLButtonUp(nFlags, point);
}

void CBarCodeView::OnPicGray()
{
	// TODO: Add your command handler code here
	if (m_isBitmap)
	{
		DWORD bmSize = bmInfo.bmHeight*bmInfo.bmWidthBytes;
		for (UINT i=0 ; i<bmSize ; i++)		//保存处理前的图
		{
			hDataOld[i] = hDataNew[i];
		}
		UINT temp;
		for	(i=0 ; i<(bmSize-3) ; i+=4)
		{
			temp = (hDataNew[i]+hDataNew[i+1]+hDataNew[i+2])/3;
			
			hDataNew[i] = temp;				//B
			hDataNew[i+1] = temp;			//G
			hDataNew[i+2] = temp;			//R
		}
		m_bitmap.SetBitmapBits(bmSize , hDataNew);
		Invalidate(TRUE);
	}
	else
	{
		MessageBox("请打开一张BMP图片！");
	}
}

void CBarCodeView::OnPicBw() 
{
	// TODO: Add your command handler code here
	if (m_isBitmap)
	{
		CDLGBW dlgBW;
		UINT bwTemp;
		bwTemp = 120;
		dlgBW.m_bw = bwTemp;
		if (dlgBW.DoModal() == IDOK)
		{
			bwTemp = dlgBW.m_bw;
			UpdateData(TRUE);
		}
		bwTemp *= 3;
		DWORD bmSize = bmInfo.bmHeight*bmInfo.bmWidthBytes;
		for (UINT i=0 ; i<bmSize ; i++)		//保存处理前的图
		{
			hDataOld[i] = hDataNew[i];
		}
		UINT temp;
		for(i=0 ; i<(bmSize-3) ; i+=4)
		{
			temp = hDataNew[i]+hDataNew[i+1]+hDataNew[i+2];
			if (temp > bwTemp)
			{
				hDataNew[i] = 255;				//B
				hDataNew[i+1] = 255;			//G
				hDataNew[i+2] = 255;			//R
			} 
			else
			{
				hDataNew[i] = 0;			//B
				hDataNew[i+1] = 0;			//G
				hDataNew[i+2] = 0;			//R
			}
		}
		m_bitmap.SetBitmapBits(bmSize , hDataNew);
		Invalidate(TRUE);
	}
	else
	{
		MessageBox("请打开一张BMP图片！");
	}
}

void CBarCodeView::OnPicPre() 
{
	// TODO: Add your command handler code here
	if (m_isBitmap)
	{
		DWORD bmSize = bmInfo.bmHeight*bmInfo.bmWidthBytes;
		for (UINT i=0 ; i<bmSize ; i++)		//恢复上一次的图
		{
			hDataNew[i] = hDataOld[i];
		}
		m_bitmap.SetBitmapBits(bmSize , hDataNew);
		Invalidate(TRUE);
	}
	else
	{
		MessageBox("请打开一张BMP图片！");
	}
}

void CBarCodeView::OnPicQz() 
{
	// TODO: Add your command handler code here
	if (m_isBitmap)
	{
		DWORD bmSize = bmInfo.bmHeight*bmInfo.bmWidthBytes;
		for (UINT i=0 ; i<bmSize ; i++)		//保存处理前的图
		{
			hDataOld[i] = hDataNew[i];
		}

		BYTE* pData = new BYTE[bmSize/4];
		UINT j;
		for(j=0,i=0 ; i<(bmSize-4) ; i+=4,j++) //提取一个色面进行处理
		{
			pData[j] = hDataNew[i];
		}
		
		LONG width = bmInfo.bmWidth;
		LONG height = bmInfo.bmHeight;
		bmSize = width*height;
		BYTE* pTemp = new BYTE[bmSize];
		for (i=0 ; i<bmSize ; i++)
		{
			pTemp[i] = pData[i];
		}

		LONG averg;
		for (j=1 ; j<(UINT)(height-1) ; j++)
		{
			for (i=1 ; i<(UINT)(width-1) ; i++)
			{
				averg = 0;
				averg = (LONG)((pData[(j-1)*width+(i-1)] + pData[(j-1)*width+i]
							+ pData[(j-1)*width+(i+1)] + pData[j*width+(i-1)]
							+ pData[j*width+(i+1)] + pData[(j+1)*width+(i-1)]
							+ pData[(j+1)*width+i] + pData[(j+1)*width+(i+1)])/8);
				if (averg > 128)
				{
					pTemp[j*width+i] = 255;
				} 
				else
				{
					pTemp[j*width+i] = 0;
				}
			}
		}
		
		for (i=0 ; i<bmSize ; i++)
		{
			hDataNew[4*i] = pTemp[i];			//B
			hDataNew[4*i+1] = pTemp[i];			//G
			hDataNew[4*i+2] = pTemp[i];			//R
		}

		delete[] pData;
		delete[] pTemp;
		m_bitmap.SetBitmapBits(bmSize*4 , hDataNew);
		Invalidate(TRUE);
	} 
	else
	{
		MessageBox("请打开一张BMP图片！");
	}
	
}

void CBarCodeView::OnFileOpen()
{
	// TODO: Add your command handler code here
	CFileDialog dlg(TRUE , _T("bitmap") , _T("*.bmp"),
		OFN_HIDEREADONLY | OFN_FILEMUSTEXIST , _T("位图文件(*.bmp)|*.bmp||"));
	
	if(dlg.DoModal()==IDOK)
	{
		hBitmap = NULL;
		hBitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle() , 
			dlg.GetFileName() , IMAGE_BITMAP , 0 , 0 , LR_LOADFROMFILE);
		if (hBitmap==NULL)
		{
			AfxMessageBox("图片装载失败！");
			m_isBitmap = FALSE;
			return;
		}
		if(hDataOld != NULL)
		{
			delete[] hDataOld;
		}
		if(hDataNew != NULL)
		{
			delete[] hDataNew;
		}
		
		m_isBitmap = TRUE;
		m_bitmap.Detach();
		m_bitmap.Attach(hBitmap);
		Invalidate(TRUE);
		
		m_bitmap.GetBitmap(&bmInfo);
		DWORD bmSize = bmInfo.bmHeight*bmInfo.bmWidthBytes;
		hDataOld = new BYTE[bmSize];
		hDataNew = new BYTE[bmSize];
		m_bitmap.GetBitmapBits(bmSize , hDataOld);
		m_bitmap.GetBitmapBits(bmSize , hDataNew);
	}
	else
	{
		m_isBitmap = FALSE;
		Invalidate(TRUE);
		return;
	}
}

void CBarCodeView::OnPicSb() 
{
	// TODO: Add your command handler code here
	if (m_isBitmap)
	{
		char LeftNum[2][10] = {13,25,19,61,35,49,47,59,55,11,39,51,27,33,29,57, 5,17, 9,23};
		char RightNum[10] = {114,102,108,66,92,78,80,68,72,116};
		char FirstNum[10] = {31,20,18,17,12,6,3,10,9,5};
		
		DWORD bmSize = bmInfo.bmHeight*bmInfo.bmWidthBytes;
		BYTE* pData = new BYTE[bmSize/4];
		for(UINT i=0,j=0 ; i<(bmSize-4) ; i+=4,j++) //提取一个色面进行处理
		{
			pData[j] = hDataNew[i];
		}
		
		UINT* pBar = new UINT[bmInfo.bmHeight*60];  //用于存储条形码转折点
		UINT temp = bmInfo.bmHeight*60;
		for(i=0 ; i<temp ; i++)
		{
			pBar[i] = 0;
		}
		
		UINT k = 0;
		UINT l = 0;
		for(i=0 ; i<(UINT)bmInfo.bmHeight-1 ; i++)
		{
			k = 0;
			temp = i*bmInfo.bmWidth;
			for(j=0 ; j<(UINT)bmInfo.bmWidth-2 ; j++)
			{
				if (pData[temp+j] != pData[temp+j+1])
				{
					if (k < 60)
					{
						pBar[l*60+k] = j;
						k++;
					} 
					else
					{
						break;
					}
				}
			}
			if(k == 60)
			{
				l++;
			}
		}
		
		UINT* pBar_new = new UINT[l*60];  //记录条形码转折点
		for (i=0 ; i<l*60 ; i++)
		{
			pBar_new[i] = pBar[i];
		}
		delete[] pBar;

		if (l < 1)
		{
			MessageBox("无法分辨条形码！");
			return;
		}

		int* pBar_size = new int[l*59];  //计算每根条形码的宽度
		for (i=0 ; i<l ; i++)
		{
			for (j=0 ; j<59 ; j++)
			{
				pBar_size[59*i+j] = pBar_new[60*i+j+1] - pBar_new[60*i+j];
				if (pBar_size[59*i+j] < 0)
				{
					pBar_size[59*i+j] = 0;
				}
			}
		}
		delete[] pBar_new;

		float* pBarAvg = new float[59];
		for (i=0 ; i<59 ; i++)
		{
			pBarAvg[i] = 0.0;
		}
		for (j=0 ; j<59 ; j++)
		{
			for (i=0 ; i<l ; i++)
			{
				pBarAvg[j] += pBar_size[59*i+j];
			}
			pBarAvg[j] /= l;
		}
		delete[] pBar_size;

		float perSize = 0.0;
		for (i=0 ; i<3 ; i++)
		{
			pBarAvg[i] = 1;
		}
		for (i=0 ; i<6 ; i++)
		{
			perSize = 0.0;
			for (j=0 ; j<4 ; j++)
			{
				perSize += pBarAvg[3+4*i+j];
			}
			perSize /= 7;
			for (j=0 ; j<4 ; j++)
			{
				pBarAvg[3+4*i+j] /= perSize;
			}
		}
		for (i=27 ; i<32 ; i++)
		{
			pBarAvg[i] = 1;
		}
		for (i=0 ; i<6 ; i++)
		{
			perSize = 0.0;
			for (j=0 ; j<4 ; j++)
			{
				perSize += pBarAvg[32+4*i+j];
			}
			perSize /= 7;
			for (j=0 ; j<4 ; j++)
			{
				pBarAvg[32+4*i+j] /= perSize;
			}
		}
		for (i=56 ; i<59 ; i++)
		{
			pBarAvg[i] = 1;
		}
		
		char* pBarsize = new char[59];
		for (i=0 ; i<59 ; i++)
		{
			if (pBarAvg[i] <= 1.5)
			{
				pBarsize[i] = 1;
			} 
			else if (pBarAvg[i]>1.5 && pBarAvg[i]<=2.5)
			{
				pBarsize[i] = 2;
			} 
			else if (pBarAvg[i]>2.5 && pBarAvg[i]<=3.5)
			{
				pBarsize[i] = 3;
			} 
			else if (pBarAvg[i] > 3.5)
			{
				pBarsize[i] = 4;
			} 
		}
		delete[] pBarAvg;

		char perNum;
		char* barNum = new char[12];
		for (i=0 ; i<12 ; i++)
		{
			barNum[i] = 0;
		}
		for (i=0 ; i<6 ; i++)
		{
			perNum = 0;
			for (j=0 ; j<4 ; j++)
			{
				if (j%2 == 1)
				{
					for (char k=0 ; k<pBarsize[3+i*4+j] ; k++)
					{
						perNum = (perNum<<1) | 1;
					}
				}
				else
				{
					for (char k=0 ; k<pBarsize[3+i*4+j] ; k++)
					{
						perNum = perNum<<1;
					}
				}
			}
			barNum[i] = perNum;
		}
		for (i=0 ; i<6 ; i++)
		{
			perNum = 0;
			for (j=0 ; j<4 ; j++)
			{
				if (j%2 == 1)
				{
					for (char k=0 ; k<pBarsize[32+i*4+j] ; k++)
					{
						perNum = perNum<<1;
					}
				}
				else
				{
					for (char k=0 ; k<pBarsize[32+i*4+j] ; k++)
					{
						perNum = (perNum<<1) | 1;
					}
				}
			}
			barNum[i+6] = perNum;
		}
		delete[] pBarsize;

		char firstNum = 0;
		char position = 2;
		unsigned long leftNum = 0;
		for (i=0 ; i<6 ; i++)
		{
			for (j=0 ; j<2 ; j++)
			{
				for (k=0 ; k<10 ; k++)
				{
					if (barNum[i] == LeftNum[j][k])
					{
						leftNum = leftNum*10 + k;
						switch (position)
						{
						case 2:
							position = j;
							break;
						case 1:
							firstNum = firstNum<<1 | j;
							break;
						case 0:
							firstNum = firstNum<<1 | !j;
							break;
						default:
							break;
						}
					} 
				}
			}
		}
		for (i=0 ; i<10 ; i++)
		{
			if (firstNum == FirstNum[i])
			{
				leftNum += i*1000000;
			}
		}
		unsigned long rightNum = 0;
		for (i=6 ; i<12 ; i++)
		{
			for (k=0 ; k<10 ; k++)
			{
				if (barNum[i] == RightNum[k])
				{
					rightNum = rightNum*10 + k;
				}
			}
		}

		CString strBarCode;
		CString strLeft;
		strLeft.Format("%d" , leftNum);
		if (strLeft.GetLength() < 7)
		{
			for (i=strLeft.GetLength() ; i<7 ; i++)
			{
				strBarCode.operator +=("0");
			}
		}
		strBarCode.operator +=(strLeft);
		CString strRight;
		strRight.Format("%d" , rightNum);
		if (strRight.GetLength() < 6)
		{
			for (i=strRight.GetLength() ; i<6 ; i++)
			{
				strBarCode.operator +=("0");
			}
		}
		strBarCode.operator +=(strRight);
		char checkStr;
		int checkNum = 0;
		for (i=0 ; i<12 ; i++)
		{
			checkStr = strBarCode.GetAt(i)-48;
			if (i%2 == 0)
			{
				checkNum += int(checkStr);
			} 
			else
			{
				checkNum += 3*int(checkStr);
			}
		}
		checkNum %= 10;
		if (checkNum > 0)
		{
			checkNum = 10 - checkNum;
		}
		checkStr = strBarCode.GetAt(12)-48;
		if (checkNum == (int)checkStr)
		{
			CString barCode("条形码为：");
			barCode.operator +=(strBarCode);
			MessageBox(barCode);
		} 
		else
		{
			MessageBox("校验错误！");
		}
	} 
	else
	{
		MessageBox("请打开一张BMP图片！");
	}
}
