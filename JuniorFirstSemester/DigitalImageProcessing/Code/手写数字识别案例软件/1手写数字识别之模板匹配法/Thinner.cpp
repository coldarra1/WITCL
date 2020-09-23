//**************************************************************************
//Thinner.cpp
//细化算法实现文件
//**************************************************************************
#include "StdAfx.h"
#include <stdlib.h>
#include <malloc.h>
#include "Thinner.h"

void beforethin(unsigned char *ip, unsigned char *jp, 
				unsigned long lx, unsigned long ly)
{
	unsigned long i,j;
	for(i=0; i<ly; i++)
	{
		for(j=0; j<lx; j++)
		{
			//这里要视前景是白点还是黑点而定，可以改动
			//如果前景是白点，就是这样；反之反过来
			if(ip[i*lx+j]>0)
				jp[i*lx+j]=1;
			else
				jp[i*lx+j]=0;
		}
	}
}

/////////////////////////////////////////////////////////////////////////
//Hilditch细化算法
//功能：对图象进行细化
//参数：image：代表图象的一维数组
//      lx：图象宽度
//      ly：图象高度
//      无返回值
void ThinnerHilditch(void *image, unsigned long lx, unsigned long ly)
{
	char *f, *g;
	char n[10];
	unsigned int counter;
	short k, shori, xx, nrn;
	unsigned long i, j;
	long kk, kk11, kk12, kk13, kk21, kk22, kk23, kk31, kk32, kk33, size;
	size = (long)lx * (long)ly;
	g = (char *)malloc(size);

	if(g == NULL)
	{
		printf("error in allocating memory!\n");
		return;
	}

	f = (char *)image;
	for(i=0; i<lx; i++)
	{
		for(j=0; j<ly; j++)
		{
			kk=i*ly+j;
			if(f[kk]!=0)
			{
				f[kk]=1;
				g[kk]=f[kk];
			}
		}
	}

	counter = 1;

	do
	{
		printf("%4d*",counter);
		counter++;
		shori = 0;

		for(i=0; i<lx; i++)
		{
			for(j=0; j<ly; j++)
			{
				kk = i*ly+j;
				if(f[kk]<0)
					f[kk] = 0;
				g[kk]= f[kk];
			}
		}

		for(i=1; i<lx-1; i++)
		{
			for(j=1; j<ly-1; j++)
			{
				kk=i*ly+j;

				if(f[kk]!=1)
					continue;

				kk11 = (i-1)*ly+j-1;
				kk12 = kk11 + 1;
				kk13 = kk12 + 1;
				kk21 = i*ly+j-1;
				kk22 = kk21 + 1;
				kk23 = kk22 + 1;
				kk31 = (i+1)*ly+j-1;
				kk32 = kk31 + 1;
				kk33 = kk32 + 1;

				if((g[kk12]&&g[kk21]&&g[kk23]&&g[kk32])!=0)
					continue;

				nrn = g[kk11] + g[kk12] + g[kk13] + g[kk21] + g[kk23] + 
					g[kk31] + g[kk32] + g[kk33];

				if(nrn <= 1)
				{
					f[kk22] = 2;
					continue;
				}

				n[4] = f[kk11];
				n[3] = f[kk12];
				n[2] = f[kk13];
				n[5] = f[kk21];
				n[1] = f[kk23];
				n[6] = f[kk31];
				n[7] = f[kk32];
				n[8] = f[kk33];
				n[9] = n[1];
				xx = 0;

				for(k=1; k<8; k=k+2)
				{
					if((!n[k])&&(n[k+1]||n[k+2]))
						xx++;
				}

				if(xx!=1)
				{
					f[kk22] = 2;
					continue;
				}

				if(f[kk12] == -1)
				{
					f[kk12] = 0;
					n[3] = 0;
					xx = 0;

					for(k=1; k<8; k=k+2)
					{
						if((!n[k])&&(n[k+1]||n[k+2]))
							xx++;
					}

					if(xx != 1)
					{
						f[kk12] = -1;
						continue;
					}

					f[kk12] = -1;
					n[3] = -1;
				}

				if(f[kk21]!=-1)
				{
					f[kk22] = -1;
					shori = 1;
					continue;
				}

				f[kk21] = 0;
				n[5] = 0;
				xx = 0;

				for(k=1; k<8; k=k+2)
				{
					if((!n[k])&&(n[k+1]||n[k+2]))
					{
						xx++;
					}
				}

				if(xx == 1)
				{
					f[kk21] = -1;
					f[kk22] = -1;
					shori =1;
				}
				else
					f[kk21] = -1;
			}
		}
	}while(shori);

	free(g);
}

/////////////////////////////////////////////////////////////////////////
//Pavlidis细化算法
//功能：对图象进行细化
//参数：image：代表图象的一维数组
//      lx：图象宽度
//      ly：图象高度
//      无返回值
void ThinnerPavlidis(void *image, unsigned long lx, unsigned long ly)
{
	char erase, n[8];
	char *f;
	unsigned char bdr1,bdr2,bdr4,bdr5;
	short c,k,b;
	unsigned long i,j;
	long kk,kk1,kk2,kk3;
	f = (char*)image;

	for(i=1; i<lx-1; i++)
	{
		for(j=1; j<ly-1; j++)
		{
			kk = i*ly + j;
			if(f[kk])
				f[kk] = 1;
		}
	}

	for(i=0, kk1=0, kk2=ly-1; i<lx; i++, kk1+=ly, kk2+=ly)
	{
		f[kk1]=0;
		f[kk2]=0;
	}

	for(j=0, kk=(lx-1)*ly; j<ly; j++,kk++)
	{
		f[j]=0;
		f[kk]=0;
	}

	c=5;
	erase =1;
	while(erase)
	{
		c++;
		for(i=1; i<lx-1; i++)
		{
			for(j=1; j<ly-1; j++)
			{
				kk=i*ly+j;
				if(f[kk]!=1)
					continue;

				kk1 = kk-ly -1;
				kk2 = kk1 + 1;
				kk3 = kk2 + 1;
				n[3] = f[kk1];
				n[2] = f[kk2];
				n[1] = f[kk3];
				kk1 = kk - 1;
				kk3 = kk + 1;
				n[4] = f[kk1];
				n[0] = f[kk3];
				kk1 = kk + ly -1;
				kk2 = kk1 + 1;
				kk3 = kk2 + 1;
				n[5] = f[kk1];
				n[6] = f[kk2];
				n[7] = f[kk3];

				bdr1 =0;
				for(k=0; k<8; k++)
				{
					if(n[k]>=1)
						bdr1|=0x80>>k;
				}

				if((bdr1&0252)== 0252)
					continue;
				f[kk] = 2;
				b=0;

				for(k=0; k<=7; k++)
				{
					b+=bdr1&(0x80>>k);
				}

				if(b<=1)
					f[kk]=3;

				if((bdr1&0160)!=0&&(bdr1&07)!=0&&(bdr1&0210)==0)
					f[kk]=3;
				else if((bdr1&&0301)!=0&&(bdr1&034)!=0&&(bdr1&042)==0)
					f[kk]=3;
				else if((bdr1&0202)==0 && (bdr1&01)!=0)
					f[kk]=3;
				else if((bdr1&0240)==0 && (bdr1&0100)!=0)
					f[kk]=3;
				else if((bdr1&050)==0 && (bdr1&020)!=0)
					f[kk]=3;
				else if((bdr1&012)==0 && (bdr1&04)!=0)
					f[kk]=3;
			}
		}

		for(i=1; i<lx-1; i++)
		{
			for(j=1; j<ly-1; j++)
			{
				kk = i*ly + j;
				if(!f[kk])
					continue;

				kk1 = kk - ly -1;
				kk2 = kk1 + 1;
				kk3 = kk2 + 1;
				n[3] = f[kk1];
				n[2] = f[kk2];
				n[1] = f[kk3];
				kk1 = kk - 1;
				kk2 = kk + 1;
				n[4] = f[kk1];
				n[0] = f[kk3];
				kk1 = kk + ly -1;
				kk2 = kk1 + 1;
				kk3 = kk2 + 1;
				n[5] = f[kk1];
				n[6] = f[kk2];
				n[7] = f[kk3];
				bdr1 = bdr2 =0;

				for(k=0; k<=7; k++)
				{
					if(n[k]>=1)
						bdr1|=0x80>>k;
					if(n[k]>=2)
						bdr2|=0x80>>k;
				}

				if(bdr1==bdr2)
				{
					f[kk] = 4;
					continue;
				}

				if(f[kk]!=2)
					continue;

				if((bdr2&0200)!=0 && (bdr1&010)==0 &&
					((bdr1&0100)!=0 &&(bdr1&001)!=0 ||
					((bdr1&0100)!=0 ||(bdr1 & 001)!=0) &&
					(bdr1&060)!=0 &&(bdr1&06)!=0))
				{
					f[kk] = 4;
				}

				else if((bdr2&040)!=0 && (bdr1&02)==0 &&
					((bdr1&020)!=0 && (bdr1&0100)!=0 ||
					((bdr1&020)!=0 || (bdr1&0100)!=0) &&
					(bdr1&014)!=0 && (bdr1&0201)!=0))
				{
					f[kk] = 4;
				}

				else if((bdr2&010)!=0 && (bdr1&0200)==0 &&
					((bdr1&04)!=0 && (bdr1&020)!=0 ||
					((bdr1&04)!=0 || (bdr1&020)!=0) &&
					(bdr1&03)!=0 && (bdr1&0140)!=0))
				{
					f[kk] = 4;
				}

				else if((bdr2&02)!=0 && (bdr1&040)==0 &&
					((bdr1&01)!=0 && (bdr1&04)!=0 ||
					((bdr1&01)!=0 || (bdr1&04)!=0) &&
					(bdr1&0300)!=0 && (bdr1&030)!=0))
				{
					f[kk] = 4;
				}
			}
		}

		for(i=1; i<lx-1; i++)
		{
			for(j=1; j<ly-1; j++)
			{
				kk = i*ly + j;
				if(f[kk]!=2)
					continue;
				kk1 = kk - ly -1;
				kk2 = kk1 + 1;
				kk3 = kk2 + 1;
				n[3] = f[kk1];
				n[2] = f[kk2];
				n[1] = f[kk3];
				kk1 = kk - 1;
				kk2 = kk + 1;
				n[4] = f[kk1];
				n[0] = f[kk3];
				kk1 = kk + ly -1;
				kk2 = kk1 + 1;
				kk3 = kk2 + 1;
				n[5] = f[kk1];
				n[6] = f[kk2];
				n[7] = f[kk3];
				bdr4 = bdr5 =0;
				for(k=0; k<=7; k++)
				{
					if(n[k]>=4)
						bdr4|=0x80>>k;
					if(n[k]>=5)
						bdr5|=0x80>>k;
				}
				if((bdr4&010) == 0)
				{
					f[kk] = 5;
					continue;
				}
				if((bdr4&040) == 0 && bdr5 ==0)
				{
					f[kk] = 5;
					continue;
				}
				if(f[kk]==3||f[kk]==4)
					f[kk] = c;
			}
		}

		erase = 0;
		for(i=1; i<lx-1; i++)
		{
			for(j=1; j<ly-1; j++)
			{
				kk = i*ly +j;
				if(f[kk]==2||f[kk] == 5)
				{
					erase = 1;
					f[kk] = 0;
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////
//Rosenfeld细化算法
//功能：对图象进行细化
//参数：image：代表图象的一维数组
//      lx：图象宽度
//      ly：图象高度
//      无返回值
void ThinnerRosenfeld(void *image, unsigned long lx, unsigned long ly)
{
	char *f, *g;
	char n[10];
	char a[5] = {0, -1, 1, 0, 0};
	char b[5] = {0, 0, 0, 1, -1};
	char nrnd, cond, n48, n26, n24, n46, n68, n82, n123, n345, n567, n781;
	short k, shori;
	unsigned long i, j;
	long ii, jj, kk, kk1, kk2, kk3, size;
	size = (long)lx * (long)ly;

	g = (char *)malloc(size);
	if(g==NULL)
	{
		printf("error in alocating mmeory!\n");
		return;
	}

	f = (char *)image;
	for(kk=0l; kk<size; kk++)
	{
		g[kk] = f[kk];
	}

	do
	{
		shori = 0;
		for(k=1; k<=4; k++)
		{
			for(i=1; i<lx-1; i++)
			{
				ii = i + a[k];

				for(j=1; j<ly-1; j++)
				{
					kk = i*ly + j;

					if(!f[kk])
						continue;

					jj = j + b[k];
					kk1 = ii*ly + jj;

					if(f[kk1])
						continue;

					kk1 = kk - ly -1;
					kk2 = kk1 + 1;
					kk3 = kk2 + 1;
					n[3] = f[kk1];
					n[2] = f[kk2];
					n[1] = f[kk3];
					kk1 = kk - 1;
					kk3 = kk + 1;
					n[4] = f[kk1];
					n[8] = f[kk3];
					kk1 = kk + ly - 1;
					kk2 = kk1 + 1;
					kk3 = kk2 + 1;
					n[5] = f[kk1];
					n[6] = f[kk2];
					n[7] = f[kk3];

					nrnd = n[1] + n[2] + n[3] + n[4]
						+n[5] + n[6] + n[7] + n[8];
					if(nrnd<=1)
						continue;

					cond = 0;
					n48 = n[4] + n[8];
					n26 = n[2] + n[6];
					n24 = n[2] + n[4];
					n46 = n[4] + n[6];
					n68 = n[6] + n[8];
					n82 = n[8] + n[2];
					n123 = n[1] + n[2] + n[3];
					n345 = n[3] + n[4] + n[5];
					n567 = n[5] + n[6] + n[7];
					n781 = n[7] + n[8] + n[1];

					if(n[2]==1 && n48==0 && n567>0)
					{
						if(!cond)
							continue;
						g[kk] = 0;
						shori = 1;
						continue;
					}

					if(n[6]==1 && n48==0 && n123>0)
					{
						if(!cond)
							continue;
						g[kk] = 0;
						shori = 1;
						continue;
					}

					if(n[8]==1 && n26==0 && n345>0)
					{
						if(!cond)
							continue;
						g[kk] = 0;
						shori = 1;
						continue;
					}

					if(n[4]==1 && n26==0 && n781>0)
					{
						if(!cond)
							continue;
						g[kk] = 0;
						shori = 1;
						continue;
					}

					if(n[5]==1 && n46==0)
					{
						if(!cond)
							continue;
						g[kk] = 0;
						shori = 1;
						continue;
					}

					if(n[7]==1 && n68==0)
					{
						if(!cond)
							continue;
						g[kk] = 0;
						shori = 1;
						continue;
					}

					if(n[1]==1 && n82==0)
					{
						if(!cond)
							continue;
						g[kk] = 0;
						shori = 1;
						continue;
					}

					if(n[3]==1 && n24==0)
					{
						if(!cond)
							continue;
						g[kk] = 0;
						shori = 1;
						continue;
					}

					cond = 1;
					if(!cond)
						continue;
					g[kk] = 0;
					shori = 1;
				}
			}

			for(i=0; i<lx; i++)
			{
				for(j=0; j<ly; j++)
				{
					kk = i*ly + j;
					f[kk] = g[kk];
				}
			}
		}
	}while(shori);

	free(g);
}					

/////////////////////////////////////////////////////////////////////////
//基于索引表的细化细化算法
//功能：对图象进行细化
//参数：lpDIBBits：代表图象的一维数组
//      lWidth：图象高度
//      lHeight：图象宽度
//      无返回值
BOOL WINAPI ThiningDIBSkeleton (LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{	
	//循环变量
	long i;
	long j;
	long lLength;
	
	unsigned char deletemark[256] = {
		0,0,0,0,0,0,0,1,	0,0,1,1,0,0,1,1,
		0,0,0,0,0,0,0,0,	0,0,1,1,1,0,1,1,
		0,0,0,0,0,0,0,0,	1,0,0,0,1,0,1,1,
		0,0,0,0,0,0,0,0,	1,0,1,1,1,0,1,1,
		0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,	1,0,0,0,1,0,1,1,
		1,0,0,0,0,0,0,0,	1,0,1,1,1,0,1,1,
		0,0,1,1,0,0,1,1,	0,0,0,1,0,0,1,1,
		0,0,0,0,0,0,0,0,	0,0,0,1,0,0,1,1,
		1,1,0,1,0,0,0,1,	0,0,0,0,0,0,0,0,
		1,1,0,1,0,0,0,1,	1,1,0,0,1,0,0,0,
		0,1,1,1,0,0,1,1,	0,0,0,1,0,0,1,1,
		0,0,0,0,0,0,0,0,	0,0,0,0,0,1,1,1,
		1,1,1,1,0,0,1,1,	1,1,0,0,1,1,0,0,
		1,1,1,1,0,0,1,1,	1,1,0,0,1,1,0,0
	};//索引表

	unsigned char p0, p1, p2, p3, p4, p5, p6, p7;
	unsigned char *pmid, *pmidtemp;
	unsigned char sum;
	int changed;
	bool bStart = true;
	lLength = lWidth * lHeight;
	unsigned char *pTemp = (unsigned char *)malloc(sizeof(unsigned char) * lWidth * lHeight);
	
	//    P0 P1 P2
	//    P7    P3
	//    P6 P5 P4

	while(bStart)
	{
		bStart = false;
		changed = 0;

		//首先求边缘点(并行)
		pmid = (unsigned char *)lpDIBBits + lWidth + 1;
		memset(pTemp, (BYTE) 0, lLength);
		pmidtemp = (unsigned char *)pTemp + lWidth + 1;
		for(i = 1; i < lHeight -1; i++)
		{
			for(j = 1; j < lWidth - 1; j++)
			{
				if( *pmid == 0)
				{
					pmid++;
					pmidtemp++;
					continue;
				}

				p3 = *(pmid + 1);
				p2 = *(pmid + 1 - lWidth);
				p1 = *(pmid - lWidth);
				p0 = *(pmid - lWidth -1);
				p7 = *(pmid - 1);
				p6 = *(pmid + lWidth - 1);
				p5 = *(pmid + lWidth);
				p4 = *(pmid + lWidth + 1);
				
				sum = p0 & p1 & p2 & p3 & p4 & p5 & p6 & p7;
				if(sum == 0)
				{
					*pmidtemp = 1;
				}

				pmid++;
				pmidtemp++;
			}
			pmid++;
			pmid++;
			pmidtemp++;
			pmidtemp++;
		}
		
		//现在开始串行删除
		pmid = (unsigned char *)lpDIBBits + lWidth + 1;
		pmidtemp = (unsigned char *)pTemp + lWidth + 1;

		for(i = 1; i < lHeight -1; i++)
		{
			for(j = 1; j < lWidth - 1; j++)
			{
				if( *pmidtemp == 0)
				{
					pmid++;
					pmidtemp++;
					continue;
				}

				p3 = *(pmid + 1);
				p2 = *(pmid + 1 - lWidth);
				p1 = *(pmid - lWidth);
				p0 = *(pmid - lWidth -1);
				p7 = *(pmid - 1);
				p6 = *(pmid + lWidth - 1);
				p5 = *(pmid + lWidth);
				p4 = *(pmid + lWidth + 1);
				
				p1 *= 2;
				p2 *= 4;
				p3 *= 8;
				p4 *= 16;
				p5 *= 32;
				p6 *= 64;
				p7 *= 128;

				sum = p0 | p1 | p2 | p3 | p4 | p5 | p6 | p7;
				if(deletemark[sum] == 1)
				{
					*pmid = 0;
					bStart = true;
				}

				pmid++;
				pmidtemp++;
			}

			pmid++;
			pmid++;
			pmidtemp++;
			pmidtemp++;
		}
	}

	return true;
}