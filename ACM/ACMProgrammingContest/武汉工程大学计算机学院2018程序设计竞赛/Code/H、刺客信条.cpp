#include<bits/stdc++.h>
using namespace std;

int ans,t,n,m;
int sx,sy,ex,ey;
int a[105][105]={0};
int b[105][105]={0};
int f[4][2]={{1,0},{-1,0},{0,1},{0,-1}};

struct abc
{
	int x,y,t;
};

void BFS(int x,int y)
{
	queue<abc> q;
	abc start;
	start.x=x,start.y=y,start.t=0;
	q.push(start);
	while (!q.empty())
	{
		abc front=q.front();
		q.pop();
		if (front.x<1 || front.x>n || front.y<1 || front.y>m)
			continue;
		else if (front.x==ex && front.y==ey)
		{
			if (ans>front.t)
				ans=front.t;
			continue;
		}
		else if (front.t>ans)
		{
			b[front.x][front.y]=1;
			continue;
		}
		else
		{
			b[front.x][front.y]=1;
			int x1,y1;
			for (int i=0;i<4;i++)
			{
				x1=front.x+f[i][0];
				y1=front.y+f[i][1];
				if (!b[x1][y1])
				{
					abc v;
					v.x=x1;
					v.y=y1;
					v.t=front.t+a[x1][y1];
					q.push(v);
				}
			}
		}
	}
}
int main()
{
	int i,j;
	char c;
	cin>>n>>m;
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++)
		{
			cin>>c;
			if (c=='S')
				sx=i,sy=j;
			else if (c=='E')
				ex=i,ey=j;
			else if (c=='A' || c=='B' || c=='C')
				a[i][j]=100;
			else
				a[i][j]=c-'0';
			getchar();
		}
	ans=10000,t=0;
	BFS(sx,sy);
	cout<<ans<<endl;
	return 0;
}
