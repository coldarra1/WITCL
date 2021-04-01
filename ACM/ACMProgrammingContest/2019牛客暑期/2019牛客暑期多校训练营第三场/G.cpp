#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
using namespace std;
typedef long long ll;
const int N=610001;
ll s[N],ans;
int i,j,k,n,m,a[N],rmq[21][N],tests,lg[N];
void rmqinit(){
	int i,j,k;
	for (m=0;(1<<m)<n;m++);
	for (i=2,lg[1]=0;i<=n;i++) lg[i]=((i-1)&i)?lg[i-1]:lg[i-1]+1;
	for (i=1;i<=n;i++) rmq[0][i]=i;
	for (i=k=1;i<=m;i++,k<<=1)
	 for (j=1;j<=n-k*2+1;j++) rmq[i][j]=(a[rmq[i-1][j]]>a[rmq[i-1][j+k]])?rmq[i-1][j]:rmq[i-1][j+k];
}
int rmqquery(int l,int r){
	int k=lg[r-l+1];
	return (a[rmq[k][l]]>a[rmq[k][r-(1<<k)+1]])?rmq[k][l]:rmq[k][r-(1<<k)+1];
}
int bs1(int l,int r,ll v){
	int m;
	if (s[r]<v) return r+1;
	while (l<r-1){
		m=(l+r)>>1;
		if (s[m]>=v) r=m;else l=m+1;
	}
	return (s[l]>=v)?l:r;
}
int bs2(int l,int r,ll v){
	int m;
	if (s[l-1]>v) return l-1;
	while (l<r-1){
		m=(l+r)>>1;
		if (s[m-1]<=v) l=m;else r=m-1;
	}
	return (s[r-1]<=v)?r:l;
}
void work(int l,int r){
	int i,j,k;
	if (r-l+1<=1) return;
	if (r-l+1==2){
		if (a[l]==a[r]) ans++;
		return;
	}
	k=rmqquery(l,r);
	if (k-l<r-k){
		for (i=l;i<=k;i++){
			j=bs1(k,r,a[k]*2LL+s[i-1]);
			ans+=r-j+1;
		}
	}else{
		for (i=k;i<=r;i++){
			j=bs2(l,k,s[i]-a[k]*2LL);
			ans+=j-l+1;
		}
	}
	work(l,k-1);work(k+1,r);
}
int main(){
	//freopen("a.in","r",stdin);
	for (scanf("%d",&tests);tests--;){
		scanf("%d",&n);s[0]=0;
		for (i=1;i<=n;i++) scanf("%d",&a[i]),s[i]=s[i-1]+a[i];
		rmqinit();
		ans=0;work(1,n);
		printf("%lld\n",ans);
	}
	return 0;
}
