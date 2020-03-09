#include<bits/stdc++.h>
using namespace std;
int main()
{
	double p1,p2,p3,q1,q2,q3;
	double ans1,ans2,ans3;
	while(~scanf("%lf%% %lf%% %lf%%",&p1,&p2,&p3))
	{
		p1/=100; p2/=100; p3/=100;
		scanf("%lf%% %lf%% %lf%%",&q1,&q2,&q3);
		q1/=100; q2/=100; q3/=100;
		ans1=p1*q2+p2*q3+p3*q1;
		ans2=p1*q1+p2*q2+p3*q3;
		ans3=p2*q1+p3*q2+p1*q3;
		if (ans1>ans3)
			cout<<"A"<<endl;
		else if (ans1<ans3)
			cout<<"B"<<endl;
		else
			cout<<"equal"<<endl;
	}
	return 0;
}
