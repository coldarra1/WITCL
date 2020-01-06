#include<bits/stdc++.h>
using namespace std;

struct abc
{
	int x,y,f;
}s[10005];

int a[10005];

bool cmp(abc a,abc b)
{
	return (a.x<b.x || (a.x==b.x && a.y<b.y));
}

int main()
{
	int i,j,m,n,t,x,y,xx,yy;
	cin>>n>>m;
	for (i=1;i<=m;i++)
	{
		cin>>x>>y;
		xx=min(x,y);
		yy=max(x,y);
		s[i].x=xx;
		s[i].y=yy;
		s[i].f=1;
	}
	sort(s+1,s+m+1,cmp);
	for (i=1;i<m;i++)
	{
		if (s[i].x==s[i+1].x && s[i].y==s[i+1].y)
			s[i+1].f=0;
	}
	memset(a,0,sizeof(a));
	for (i=1;i<=m;i++)
		if (s[i].f && s[i].x!=s[i].y)
		{
			a[s[i].x]++;
			a[s[i].y]++;
		}
	bool ans=true;
	for (i=1;i<=n;i++)
		if (a[i]>=2)
		{
			ans=false;
			break;
		}
	if (ans)
		cout<<"Nice"<<endl;
	else
		cout<<"Error"<<endl;
	return 0;
}
