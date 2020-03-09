#include<bits/stdc++.h>
using namespace std;

int main()
{
	int i,j,m,n,t,s;
	string s1[105],s2[105];
	string x,y;
	cin>>n;
	t=0;
	for (i=1;i<=n;i++)
	{
		cin>>s1[i]>>s2[i];
		if (s2[i][0]=='y')
		t=1;
	}
	cin>>x>>y;
	if (x==s1[n])
	{
		if (y[0]=='y')
			cout<<s1[n-1]<<endl;
		else if (y[2]=='e' && t!=1)
		{
			for (i=n-1;i>=1;i--)
			{
				if (s2[i][2]=='a')
				{
					cout<<s1[i]<<endl;
					break;
				}
			}
		}
		else
			cout<<x<<endl;
	}
	else
	{
		if (s2[n-1][0]=='y')
			cout<<s1[n-2]<<endl;
		else if (s2[n-1][2]=='e' && t!=1)
		{
			for (i=n-2;i>=1;i--)
			{
				if (s2[i][2]=='a')
				{
					cout<<s1[i]<<endl;
					break;
				}
			}
		}
		else
		cout<<s1[n-1]<<endl;
	}
	return 0;
}
