#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 3005
using namespace std;

struct Point
{
	long long x,y;
	Point(){}
	Point(long long _x,long long _y):x(_x),y(_y){}
	Point operator -(const Point &a)const{
		return Point(x-a.x,y-a.y);
	}
	bool operator <(const Point &a)const{
		if (x!=a.x) return x<a.x;
		return y<a.y;
	}
	long long operator *(const Point &a)const{
		return x*a.y-y*a.x;
	}
};

Point p[3][MAXN],covu[MAXN],covd[MAXN];
int T,n,cnt[3],x,y,c,u,d;
long long S;

inline void max(long long &a,long long b){if (a<b) a=b;return ;}

inline void ConvexHull(int x)
{
	u=d=0;sort(p[x]+1,p[x]+cnt[x]+1);
	for (int i=1;i<=cnt[x];i++)
	{
		while (d>1&&(covd[d]-covd[d-1])*(p[x][i]-covd[d-1])<=0) covd[d--]=Point(0,0);
		covd[++d]=p[x][i];
	}
	for (int i=cnt[x];i;i--)
	{
		while (u>1&&(covu[u]-covu[u-1])*(p[x][i]-covu[u-1])<=0) covu[u--]=Point(0,0);
		covu[++u]=p[x][i];
	}
	return ;
}

inline long long Tri(Point P,Point Q)
{
	int l=1,r=u,lmid,rmid;long long A,B,C,h=0LL;
	A=P.y-Q.y;B=Q.x-P.x;C=P*Q;
	while (r-l>=3)
	{
		lmid=(l+l+r)/3;rmid=(l+r+r)/3;
		long long _l=A*covu[lmid].x+B*covu[lmid].y+C;
		long long _r=A*covu[rmid].x+B*covu[rmid].y+C;
		if (_l>_r) r=rmid;
		else l=lmid;
	}
	for (int i=l;i<=r;i++) max(h,abs(A*covu[i].x+B*covu[i].y+C));
	l=1;r=u;
	while (r-l>=3)
	{
		lmid=(l+l+r)/3;rmid=(l+r+r)/3;
		long long _l=A*covu[lmid].x+B*covu[lmid].y+C;
		long long _r=A*covu[rmid].x+B*covu[rmid].y+C;
		if (_l<_r) r=rmid;
		else l=lmid;
	}
	for (int i=l;i<=r;i++) max(h,abs(A*covu[i].x+B*covu[i].y+C));
	l=1;r=d;
	while (r-l>=3)
	{
		lmid=(l+l+r)/3;rmid=(l+r+r)/3;
		long long _l=A*covd[lmid].x+B*covd[lmid].y+C;
		long long _r=A*covd[rmid].x+B*covd[rmid].y+C;
		if (_l>_r) l=lmid;
		else r=rmid;
	}
	for (int i=l;i<=r;i++) max(h,abs(A*covd[i].x+B*covd[i].y+C));
	l=1;r=d;
	while (r-l>=3)
	{
		lmid=(l+l+r)/3;rmid=(l+r+r)/3;
		long long _l=A*covd[lmid].x+B*covd[lmid].y+C;
		long long _r=A*covd[rmid].x+B*covd[rmid].y+C;
		if (_l<_r) l=lmid;
		else r=rmid;
	}
	for (int i=l;i<=r;i++) max(h,abs(A*covd[i].x+B*covd[i].y+C));
	return h;
}

inline void Solve()
{
	memset(cnt,0,sizeof cnt);S=0;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d %d %d",&x,&y,&c);
		p[c][++cnt[c]]=Point(x,y);
	}
	if (cnt[0]>cnt[1])
	{
		if (cnt[0]>cnt[2]){x=1;y=2;c=0;}
		else {x=0;y=1;c=2;}
	}
	else
	{
		if (cnt[1]>cnt[2]){x=0;y=2;c=1;}
		else{x=0;y=1;c=2;}
	}
	ConvexHull(c);
	for (int i=1;i<=cnt[x];i++)
		for (int j=1;j<=cnt[y];j++)
			max(S,Tri(p[x][i],p[y][j]));
	if (S&1) printf("%lld.5\n",S>>1);
	else printf("%lld.0\n",S>>1);
	return ;
}

int main()
{
	scanf("%d",&T);
	while (T--) Solve();
	return 0;
}