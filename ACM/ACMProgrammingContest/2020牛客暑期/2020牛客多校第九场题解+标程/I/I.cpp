#include<bits/stdc++.h>
#define N 100005
#define re register
#define ll long long
#pragma GCC optimize(3)
using namespace std;
int n,c[N];
#define M 100000000
struct HPC{
	int len;
	ll a[100005];
	void clear(){
		for(re int i=1;i<=len;i++)a[i]=0;
		len=0;
	}
	void Read(){
		len=0;
		for(re int i=n;i>=1;i-=8){
			ll res=0;
			for(re int j=max(1,i-7);j<=i;j++)res=res*10+c[j];
			a[++len]=res;
		}
	}
	void Mul(int x){
		len++;
		for(re int i=1;i<=len;i++)a[i]*=x;
		for(re int i=1;i<=len;i++)
			a[i+1]+=a[i]/M,a[i]%=M;
		while(a[len])len++;
		while(len&&a[len]==0)len--;
		if(len==0)len++;
	}
	void Print(){
		printf("%lld",a[len]);
		for(re int i=len-1;i;i--)printf("%08lld",a[i]);
		puts("");
	}
}S;
int cnt[15];
bool m2; 
int main(){
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	int T;scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		S.clear();
		re char ch;
		for(re int i=1;i<=n;i++){
			while(ch=getchar(),ch<48);
			cnt[ch^48]++;
		}
		int res=0;
		for(re int i=1;i<=9;i++)if(cnt[i]){res=i;cnt[i]--;break;}
		n=0;
		for(re int i=1;i<=9;i++){
			if(cnt[i])c[++n]=i,cnt[i]--;
			if(n)while(cnt[0])c[++n]=0,cnt[0]--;
			while(cnt[i])c[++n]=i,cnt[i]--;
		}
		
		S.Read();
		S.Mul(res);
		S.Print();
	}
	return 0;
}
