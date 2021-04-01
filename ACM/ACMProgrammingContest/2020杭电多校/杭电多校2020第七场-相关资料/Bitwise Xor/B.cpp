#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
int cnt=0,bas[100005][30][2],p[100005],id[100005],n,m,x,y,q,opt,b[100005],w,st[100005];
int dfn;
int T;
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("ttt.out","w",stdout);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&q);
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d",&m,&p[i]);
			for(int j=1;j<=m;j++)
			{
				cnt++;
				id[cnt]=i;
				scanf("%d%d",&x,&y);
				b[cnt]=b[cnt-1]^x;
				y^=x;
				for(int k=0;k<30;k++)bas[cnt][k][0]=bas[cnt-1][k][0],bas[cnt][k][1]=bas[cnt-1][k][1];
				dfn=cnt;
				for(int k=29;k>=0;k--)
				{
					if(!((1<<k)&y))continue;
					if(!bas[cnt][k][0])
					{
						bas[cnt][k][0]=y;
						bas[cnt][k][1]=dfn;
						break;
					}
					else
					{
						if(bas[cnt][k][1]<dfn)swap(y,bas[cnt][k][0]),swap(dfn,bas[cnt][k][1]);
						y^=bas[cnt][k][0];
					}
				}
			}
			st[i]=cnt;
		}
		for(int i=1;i<=q;i++)
		{
			scanf("%d%d%d",&opt,&x,&y);
			if(opt==1)p[x]=y;
			else
			{
				scanf("%d",&w);
				w^=b[st[y]]^b[st[x-1]];
				for(int j=29;j>=0;j--)
				{
					if(!bas[st[y]][j][0]||bas[st[y]][j][1]<=st[x-1])continue;
					if((w&(1<<j))!=(p[id[bas[st[y]][j][1]]]&(1<<j)))w^=bas[st[y]][j][0];
				}
				printf("%d\n",w);
			}
		}
		cnt=0;
	}
	return 0;
}

