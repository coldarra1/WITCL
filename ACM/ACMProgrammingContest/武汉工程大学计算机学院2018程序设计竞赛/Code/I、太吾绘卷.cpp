#include<bits/stdc++.h>
using namespace std;

int main()
{
	int i,j,m,n,u1=0,u2=0;
	double s1,s2,t1,t2,w1,w2,v1,v2;
	cin>>n;
	for (i=1;i<=n;i++)
	{
		cin>>m;
		u1+=(10-m)*10;
	}
	cin>>u2>>v1>>v2;
	s1=u1*1.0/500;
	t1=u1*1.0/1000;
	s2=u2*1.0/500;
	t2=u2*1.0/1000;
	if (1+s1<=t2 && 1+s2<=t1)
	{
		cout<<"No"<<endl;
		return 0;
	}
	else if (1+s1<=t2 && 1+s2>t1)
	{
		cout<<"No"<<endl;
		return 0;
	}
	else if (1+s2<=t1 && 1+s1>t2)
	{
		printf("%.2lf\n",v1);
		return 0;
	}
	else
	{
		w1=u1*(1+s1-t2);
		w2=u2*(1+s2-t1);
		m=ceil(v2/w1);
		v1=v1-(m-1)*w2;
		if (v1>0)
			printf("%.2lf\n",v1);
		else
			cout<<"No"<<endl;
	}
	return 0;
}
