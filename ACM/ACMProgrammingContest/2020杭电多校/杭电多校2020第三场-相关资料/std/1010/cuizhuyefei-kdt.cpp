#include<bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(),x.end()
#define L(i,u) for (register int i=head[u]; i; i=nxt[i])
#define rep(i,a,b) for (register int i=(a); i<=(b); i++)
#define per(i,a,b) for (register int i=(a); i>=(b); i--)
using namespace std;
typedef long double ld;
typedef long long ll;
typedef unsigned int ui;
typedef pair<int,int> Pii;
typedef vector<int> Vi;
template<class T> inline void read(T &x){
	x=0; char c=getchar(); int f=1;
	while (!isdigit(c)) {if (c=='-') f=-1; c=getchar();}
	while (isdigit(c)) {x=x*10+c-'0'; c=getchar();} x*=f;
}
template<class T> T gcd(T a, T b){return !b?a:gcd(b,a%b);}
template<class T> inline void umin(T &x, T y){x=x<y?x:y;}
template<class T> inline void umax(T &x, T y){x=x>y?x:y;}
mt19937 R(time(0));
const int N = 366666;
int Abs(int x){return x>0?x:-x;}
int n,A[N],B[N],id[N],rd,f[N],lc[N],rc[N];ll lzy,qz[N],val[N][2][2],g[N];
int l1[N],r1[N],l2[N],r2[N];
bool cmp(int x, int y){
	if(rd){return A[x]<A[y];}
	return B[x]<B[y];
}
int build(int l, int r){
	int mid=(l+r)>>1;rd=R()%2;
	nth_element(id+l,id+mid,id+r+1,cmp);
	int x=id[mid];rep(i,0,1)rep(j,0,1)val[x][i][j]=1e18;
	if(l<mid)lc[x]=build(l,mid-1),f[lc[x]]=x;
	if(mid<r)rc[x]=build(mid+1,r),f[rc[x]]=x;
	return x;
}
ll res;
inline void mdy(int k, ll x){
	int ori=k;
	while(k){
		umin(l1[k],A[k]);umin(l2[k],B[k]);
		umax(r1[k],A[k]);umax(r2[k],B[k]);
		rep(i,0,1)rep(j,0,1)umin(val[k][i][j],x+(i?-A[ori]:A[ori])+(j?-B[ori]:B[ori]));
		k=f[k];
	}
}
void qry(int k, int x, int y){
	rep(i,0,1)rep(j,0,1)if(res<=lzy+val[k][i][j]+(i?x:-x)+(j?y:-y))return;
	if(r1[k]<=x&&r2[k]<=y){umin(res,lzy+val[k][1][1]+x+y);return;}
	if(r1[k]<=x&&l2[k]>=y){umin(res,lzy+val[k][1][0]+x-y);return;}
	if(l1[k]>=x&&r2[k]<=y){umin(res,lzy+val[k][0][1]-x+y);return;}
	if(l1[k]>=x&&l2[k]>=y){umin(res,lzy+val[k][0][0]-x-y);return;}
	umin(res,lzy+g[k]+Abs(x-A[k])+Abs(y-B[k]));
	if(lc[k])qry(lc[k],x,y);
	if(rc[k])qry(rc[k],x,y);
}
int main() {
	int T;read(T);while(T--){
		read(n);lzy=0;
		rep(i,1,n)read(A[i]),read(B[i]),id[i]=i;
		rep(i,1,n)l1[i]=l2[i]=0,r1[i]=r2[i]=1e9,f[i]=g[i]=lc[i]=rc[i]=0;
		int rt=build(1,n);
	//	rep(i,1,n)printf("%d:%d %d %d\n",i,f[i],lc[i],rc[i]);
		//return 0;
		rep(i,2,n)qz[i]=qz[i-1]+Abs(A[i]-A[i-1])+Abs(B[i]-B[i-1]);
		
		rep(i,2,n){
			res=qz[i-1];qry(rt,A[i],B[i]);
		//	printf("%d:%lld (%lld)\n",i,res,lzy+g[1]);
			lzy+=Abs(A[i]-A[i-1])+Abs(B[i]-B[i-1]);
			g[i-1]=res-lzy;mdy(i-1,res-lzy);
		}
		res=qz[n];rep(i,1,n)umin(res,g[i]+lzy);
	//	rep(i,1,n)printf("%d --> %lld\n",i,g[i]+lzy);
		printf("%lld\n",res);
	}
	return 0;
}