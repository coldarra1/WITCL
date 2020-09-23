// ModeViewRight.cpp : implementation file
//

#include "stdafx.h"
#include "mode.h"
#include "ModeViewRight.h"
#include "DlgInfor.h"

//#include "modeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModeViewRight

IMPLEMENT_DYNCREATE(CModeViewRight, CView)

CModeViewRight::CModeViewRight()
{
	stateDoc=false;
}

CModeViewRight::~CModeViewRight()
{
}


BEGIN_MESSAGE_MAP(CModeViewRight, CView)
	//{{AFX_MSG_MAP(CModeViewRight)
	ON_COMMAND(ID_SHOWRIGHT, OnShowright)
	ON_COMMAND(ID_GETFEATURE, OnGetfeature)
	ON_COMMAND(ID_ZHONGJINAJULIFA, OnZhongjinajulifa)
	ON_COMMAND(ID_ZHONGXINFA, OnZhongxinfa)
	ON_COMMAND(ID_ZUICHANGJULIFA, OnZuichangjulifa)
	ON_COMMAND(ID_ZUIDAZUIXIAOJULI, OnZuidazuixiaojuli)
	ON_COMMAND(ID_ZUIDUANJULIFA, OnZuiduanjulifa)
	ON_COMMAND(ID_ZUILINJINGUIZE, OnZuilinjinguize)
	ON_COMMAND(ID_LEIPINGJUNJULIFA, OnLeipingjunjulifa)
	ON_COMMAND(ID_KJUNZHI, OnKjunzhi)
	ON_COMMAND(ID_ISODATA, OnIsodata)
	ON_COMMAND(ID_GA, OnGa)
	ON_COMMAND(ID_FUZZYCLUSTER, OnFuzzycluster)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModeViewRight drawing

CPalette * CModeViewRight::CreateBitmapPalette(CCluster * pCluster)
{
		struct
		{
			WORD Version;
			WORD NumberOfEntries;
			PALETTEENTRY aEntries[256];
		} palette = { 0x300, 256 };
		
		LPRGBQUAD pRGBTable = pCluster->GetRGB();
		UINT numberOfColors = pCluster->GetNumberOfColors();
		
		for(UINT x=0; x<numberOfColors; ++x)
		{
			palette.aEntries[x].peRed =
				pRGBTable[x].rgbRed;
			palette.aEntries[x].peGreen =
				pRGBTable[x].rgbGreen;
			palette.aEntries[x].peBlue =
				pRGBTable[x].rgbBlue;
			palette.aEntries[x].peFlags = 0;
		}
		
			hPalette.CreatePalette((LPLOGPALETTE)&palette);
		//CPalette hPale=&hPalette;
		return &hPalette;
}


void CModeViewRight::OnDraw(CDC* pDC)
{
	CDocument	* pDoc = GetDocument();
	CClientDC	dc(this);

	
	if(stateDoc)
	{
		BYTE* pBitmapData = pCluster->GetData();
		LPBITMAPINFO pBitmapInfo = pCluster->GetInfo();
		int bitmapHeight = pCluster->GetHeight();
		int bitmapWidth = pCluster->GetWidth();
		
		if (pCluster->GetRGB()) // Has a color table
		{
			CPalette * hPalette1=CreateBitmapPalette(pCluster);
			CPalette * hOldPalette =
				pDC->SelectPalette(hPalette1, true);
			pDC->RealizePalette();
			::StretchDIBits(pDC->GetSafeHdc(),0,0, bitmapWidth, bitmapHeight,
				0, 0, bitmapWidth , bitmapHeight ,
				pBitmapData, pBitmapInfo,
				DIB_RGB_COLORS, SRCCOPY);
			pDC->SelectPalette(hOldPalette, true);
			hPalette.DeleteObject();
		}
//		AfxMessageBox();
		for (int i=0; i<pCluster->patternnum; i++)
		{
//			dc.MoveTo(pCluster->m_pattern[i].lefttop);
//			dc.LineTo(pCluster->m_pattern[i].rightbottom);
			CString s;
			s.Format("%d",pCluster->m_pattern[i].index);
			dc.TextOut(pCluster->m_pattern[i].lefttop.x-8,pCluster->m_pattern[i].lefttop.y-10,s);
			s.Format("%d",pCluster->m_pattern[i].category);
			dc.TextOut(pCluster->m_pattern[i].rightbottom.x,pCluster->m_pattern[i].rightbottom.y,s);

		}

/*
		dc.SetTextColor(0);
		CString out,str;
		for(int j=1;j<255;j++)//CDib->=templatenum
		{
			if (CDib->pppp[j].pp_area!=0)
			{
				out.Format("%d",CDib->pppp[j].pp_number);
				dc.TextOut(CDib->pppp[j].rightbottom.x,CDib->pppp[j].rightbottom.y,out);
				if (CDib->p_Mode[j].sort!=0)//1
				{
					dc.SetTextColor(50*CDib->p_Mode[j].sort);
					dc.TextOut(CDib->pppp[j].rightbottom.x,CDib->pppp[j].rightbottom.y,out);
					str.Format("%d",CDib->p_Mode[j].sort);
					out.Insert(out.GetLength(),"号:");
					out.Insert(out.GetLength(),str);
					out.Insert(out.GetLength(),"类");
					dc.TextOut(CDib->pppp[j].rightbottom.x,CDib->pppp[j].rightbottom.y,out);
				
				}

			}
*/

/*			out.Format("%d",CDib->pppp[j].pp_number);
			if (CDib->p_Mode[j].sort!=0)//1
			{
				str.Format("%d",CDib->p_Mode[j].sort);
				out.Insert(out.GetLength(),"号属于");
				out.Insert(out.GetLength(),str);
				out.Insert(out.GetLength(),"类");

			}

			dc.TextOut(CDib->pppp[j].rightbottom.x,CDib->pppp[j].rightbottom.y,out);
			CPoint point;
			point.x=CDib->pppp[j].rightbottom.x;
			point.y=CDib->pppp[j].rightbottom.y;
			dc.MoveTo(point);
			point.x=CDib->pppp[j].lefttop.x;
			point.y=CDib->pppp[j].lefttop.y;
			dc.LineTo(point);
		}*/
	}
}

/////////////////////////////////////////////////////////////////////////////
// CModeViewRight diagnostics

#ifdef _DEBUG
void CModeViewRight::AssertValid() const
{
	CView::AssertValid();
}

void CModeViewRight::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CModeViewRight message handlers

void CModeViewRight::GetData()
{
	CModeDoc	* pDoc = (CModeDoc*)GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->state!=0)
	{
		pCluster=&pDoc->mCluster;
		stateDoc=true;
	}
	else
	{
		AfxMessageBox("No data!");
	}
	
}

void CModeViewRight::OnShowright() 
{
	GetData();
	Invalidate();
}

void CModeViewRight::OnGetfeature() 
{
	GetData();
	if (stateDoc)
	{
		pCluster->GetFeature();
		CString s;
		s.Format("%d",pCluster->patternnum);
//		AfxMessageBox(s);
		Invalidate();
	}
}

void CModeViewRight::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CView::CalcWindowRect(lpClientRect, nAdjustType);
}

void CModeViewRight::OnZhongjinajulifa() 
{
	GetData();
	if(stateDoc)
	{
		pCluster->Zhongjianjulifa();	
		Invalidate();
	}

}

void CModeViewRight::OnZhongxinfa() 
{
	GetData();
	if(stateDoc)
	{
		pCluster->Zhongxinfa();
		Invalidate();		
	}
		
}

void CModeViewRight::OnZuichangjulifa() 
{
	GetData();
	if(stateDoc)
	{
		pCluster->Zuichangjulifa();
		Invalidate();		
	}

}

void CModeViewRight::OnZuidazuixiaojuli() 
{
	GetData();
	if(stateDoc)
	{
		pCluster->Zuidazuixiaojulifa();
		Invalidate();		
	}
	
}

void CModeViewRight::OnZuiduanjulifa() 
{
	GetData();
	if(stateDoc)
	{
		pCluster->Zuiduanjulifa();
		Invalidate();		
	}
	
}

void CModeViewRight::OnZuilinjinguize() 
{
	GetData();
	if(stateDoc)
	{
		pCluster->Zuilinjinguize();
		Invalidate();		
	}

}

void CModeViewRight::OnLeipingjunjulifa() 
{
	GetData();
	if(stateDoc)
	{
		pCluster->Leipingjunjulifa();
		Invalidate();		
	}
	
}

void CModeViewRight::OnKjunzhi() 
{
	GetData();
	if(stateDoc)
	{
		pCluster->Kjunzhi();
		Invalidate();		
	}	
}

void CModeViewRight::OnIsodata() 
{
	GetData();
	if(stateDoc)
	{
		pCluster->ISODATA();
		Invalidate();		
	}		
}

void CModeViewRight::OnGa() 
{
	GetData();
	if (stateDoc)
	    pCluster->GetFeature();
	else
		return;
	
	DlgInfor	mDlgInfor;
	mDlgInfor.ShowInfor(4);
	if(mDlgInfor.DoModal()==IDOK)
	{
		ga.centernum=mDlgInfor.m_CenterNum;
		ga.MaxGeneration=mDlgInfor.m_Times;
        ga.m_pattern=pCluster->m_pattern;
		ga.patternnum=pCluster->patternnum;

		ga.main();

		Invalidate();
	}

}



void CModeViewRight::OnFuzzycluster() 
{
	GetData();
	if(stateDoc)
	{
		pCluster->FuzzyCluster();
		Invalidate();		
	}			
}

void CModeViewRight::OnFileSave() 
{
/*	CString  filename;
	memcpy(pCluster->m_pData,pCluster->mData,pCluster->GetWidth()*pCluster->GetHeight());
	CFileDialog dlg(FALSE,_T("BMP"),_T("*.BMP"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("位图文件(*.BMP)|*.BMP|"));	
    if(IDOK==dlg.DoModal())
	{
		filename.Format("%s", dlg.GetPathName() );    
	}
    pCluster->SaveFile(filename);
	Invalidate();*/		
}
