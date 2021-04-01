#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<ctime>
#include<set>
#include<vector>
#include<map>
#include<queue>

#define N 70005 
#define M 100005 

#define ls (t<<1)
#define rs ((t<<1)|1)
#define mid ((l+r)>>1)

#define mk make_pair
#define pb push_back
#define fi first
#define se second

using namespace std;

int i,j,m,n,p,k,size[N],fa[N],OutSum[N],S,sm[N];

long long ans;

set<int>Ed[N],BigEd[N];

set<int>::iterator it;

struct Edge{
	int x,y,w;
}E[M];

inline int read()
{
		int x; char c;
		while (c=getchar(),c<'0'||c>'9');
		x=c-'0';
		while (c=getchar(),c>='0'&&c<='9') x=(x<<1)+(x<<3)+c-'0';
		return x; 
}

inline int cmp(Edge a,Edge b)
{
		return a.w<b.w;
}

void BuildBig(int x)
{
	OutSum[x]=0;
	for (it=Ed[x].begin();it!=Ed[x].end();++it)
	{
			int ID=*it;
			OutSum[x]+=sm[ID];
			BigEd[ID].insert(x);
	}
}

long long GetSum(int x)
{
		if (size[x]>S) return OutSum[x];
		long long sum=0;
		for (it=Ed[x].begin();it!=Ed[x].end();++it)
		{
			int ID=*it;
			sum+=sm[ID];
		}		
		return sum;
}

int get(int x)
{
		return fa[x]==x?x:fa[x]=get(fa[x]); 
}

int MergeEdge(int x,int y)
{
		int sum=0;
		for (it=Ed[y].begin();it!=Ed[y].end();++it)
		{
				int ID=*it; Ed[ID].erase(y);
				if (Ed[x].find(ID)!=Ed[x].end())
				{
						sum+=sm[ID];
						continue;
				}
				Ed[ID].insert(x);
				Ed[x].insert(ID);
				if (size[y]>S)
				{
						BigEd[ID].erase(y);
						BigEd[ID].insert(x);
				}
				else if (size[x]>S) BigEd[ID].insert(x);
		}
		return sum;
}

void MergeBigEdge(int x,int y)
{
		for (it=BigEd[x].begin();it!=BigEd[x].end();++it)
		{
				int ID=*it;
				OutSum[ID]-=sm[x];
		}	
		for (it=BigEd[y].begin();it!=BigEd[y].end();++it)
		{
				int ID=*it;
				OutSum[ID]-=sm[y];
				BigEd[x].insert(ID);
		}	
		for (it=BigEd[x].begin();it!=BigEd[x].end();++it)
		{
				int ID=*it;
				OutSum[ID]+=sm[x]+sm[y];
		}			
}

int main()
{
		n=read(); m=read();
		for (i=1;i<=m;++i)
		{
			E[i].x=read(),E[i].y=read(),E[i].w=read();
			if (E[i].x==E[i].y) continue; 
			Ed[E[i].x].insert(E[i].y),Ed[E[i].y].insert(E[i].x);
		} 
		sort(E+1,E+m+1,cmp);
		for (i=1;i<=n;++i) size[i]=Ed[i].size(),fa[i]=i,sm[i]=1;
		S=(int)sqrt(m);
		for (i=1;i<=n;++i) if (size[i]>S) BuildBig(i);
		for (i=1;i<=m;++i)
		{
				int x=get(E[i].x),y=get(E[i].y);
				if (x==y) continue;
				if (size[x]<size[y]) swap(x,y); fa[y]=x;
				Ed[x].erase(y); Ed[y].erase(x); OutSum[x]-=sm[y]; OutSum[y]-=sm[x];
				if (size[x]>S) BigEd[y].erase(x);
				if (size[y]>S) BigEd[x].erase(y);
			    long long A=GetSum(x),B=GetSum(y),C=MergeEdge(x,y);
				ans+=(A*sm[y]+B*sm[x]-C*(sm[x]+sm[y]))*E[i].w;
				MergeBigEdge(x,y);
				if (size[x]<=S&&size[x]+size[y]>S) BuildBig(x);
				else if (size[x]>S) OutSum[x]+=B-C;
				size[x]+=size[y]; sm[x]+=sm[y];
		}
		cout<<ans<<endl; 
}
