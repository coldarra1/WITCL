// BpNet.h: interface for the BpNet class.
// 2005.1.13－16：02 By Superman 
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BPNET_H__3A171E41_1E8B_11D7_BA67_936006E9954B__INCLUDED_)
#define AFX_BPNET_H__3A171E41_1E8B_11D7_BA67_936006E9954B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class BpNet  
{
public:
	double tjpt[4];
	double shuchu[4];
	double m[4];
	double * sim(double *psim);
	void train(double p[200][5],double t[200][4],int samplenum);

	BpNet();

	virtual ~BpNet();

	int inNum;  //输入结点数
	int hideNum;//隐含结点数
	int outNum;  //输出结点数

	double x[200]; //输入向量
	double x1[200];//隐含结点状态值
	double x2[200];//输出结点状态值
	double o1[200];//隐含层激活值
	double o2[200];//输出层激活值
	double w[5][10];//隐含结点权值
	double w1[10][4];//输出结点权值
	double rate_w; //权值学习率（输入层-隐含层)
	double rate_w1;//权值学习率 (隐含层-输出层)
	double rate_b1;//隐含层阀值学习率
	double rate_b2;//输出层阀值学习率
	double b1[10];//隐含结点阀值
	double b2[4];//输出结点阀值
	double pp[200];
	double qq[200];
    double yd[200];//希望输出值
	double e;
	double error;//允许的最大误差
};

#endif // !defined(AFX_BPNET_H__3A171E41_1E8B_11D7_BA67_936006E9954B__INCLUDED_)
