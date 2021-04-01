#include<bits/stdc++.h>
#define N 2000005
#define re register
using namespace std;
int n,m,K,tot;
void Rd(int &res) {
	res=0;
	char ch=getchar();
	while('0'>ch||ch>'9')ch=getchar();
	while('0'<=ch&&ch<='9')res=(res<<3)+(res<<1)+(ch-'0'),ch=getchar();
}
struct data {
	int x,v;
} a[N],b[N];
int cnt[N],ans=1e9;
inline bool cmp(data a,data b) {
	return a.v<b.v;
}
void Sort() {
	n=tot;
	for(re int i=1; i<=n; i++)cnt[a[i].v&65535]++;
	for(re int i=1; i<=65535; i++)cnt[i]+=cnt[i-1];
	for(re int i=n; i>=1; i--)b[cnt[a[i].v&65535]--]=a[i];
	for(re int i=1; i<=n; i++)a[i]=b[i];
	for(re int i=0; i<=65535; i++)cnt[i]=0;
	for(re int i=1; i<=n; i++)cnt[a[i].v>>16&65535]++;
	for(re int i=1; i<=65535; i++)cnt[i]+=cnt[i-1];
	for(re int i=n; i>=1; i--)b[cnt[a[i].v>>16&65535]--]=a[i];
	for(re int i=1; i<=n; i++)a[i]=b[i];
	for(re int i=0; i<=65535; i++)cnt[i]=0;
}
int main() {
	Rd(n),Rd(m);
	for(re int i=1; i<=n; i++) {
		Rd(K);
		for(re int j=1; j<=K; j++)Rd(a[++tot].v),a[tot].x=i;
	}
	Sort();
	re int r=0,res=0;
	for(re int l=1; l<=tot; l++) {
		while(r<tot&&res<m)(!cnt[a[++r].x]++)&&(res++);
		(res>=m)&&(ans>a[r].v-a[l].v)&&(ans=a[r].v-a[l].v);
		(!--cnt[a[l].x])&&(res--);
	}
	printf("%d\n",ans);
	return 0;
}
