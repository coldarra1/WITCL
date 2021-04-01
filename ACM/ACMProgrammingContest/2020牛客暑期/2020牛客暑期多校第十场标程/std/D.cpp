#include<bits/stdc++.h>

#define pb push_back
#define mp make_pair
#define fi first
#define se second

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

template <typename T> bool chkmax(T &x,T y){return x<y?x=y,true:false;}
template <typename T> bool chkmin(T &x,T y){return x>y?x=y,true:false;}

int readint(){
	int x=0,f=1; char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

int a[10],b[10];

void brute(){
	if(a[1]+a[2]+a[3]+a[4]+a[5]==0){
		printf("No\n");
		return;
	}
	if(b[1]+b[2]+b[3]+b[4]+b[5]==0){
		printf("Yes\n");
		return;
	}
	if((a[3]||a[4])&&b[5]) b[5]=0;
	else if(a[5]&&b[1]) a[5]--,b[1]--,b[3]++;
	else if(a[5]&&b[2]) a[5]--,b[2]--,b[4]++;
	else if(a[3]){
		if(b[3]) a[3]--,a[5]++,b[3]--,b[5]++;
		else if(b[4]) a[3]--,a[5]++,b[4]--;
		else if(b[1]) a[3]--,a[5]++,b[1]--,b[3]++;
		else if(b[2]) a[3]--,a[5]++,b[2]--,b[4]++;
	}
	else if(a[1]){
		if(b[3]) a[1]--,a[3]++,b[3]--,b[5]++;
		else if(b[4]) a[1]--,a[3]++,b[4]--;
		else if(b[1]) a[1]--,a[3]++,b[1]--,b[3]++;
		else if(b[2]) a[1]--,a[3]++,b[2]--,b[4]++;
		else if(b[5]) a[1]--,a[3]++,b[5]--;
	}
	else if(a[2]){
		if(b[3]) a[2]--,a[4]++,b[3]--,b[5]++;
		else if(b[4]) a[2]--,a[4]++,b[4]--;
		else if(b[1]) a[2]--,a[4]++,b[1]--,b[3]++;
		else if(b[2]) a[2]--,a[4]++,b[2]--,b[4]++;
		else if(b[5]) a[2]--,a[4]++,b[5]--;
	}
	else if(a[4]){
		if(b[3]) a[4]--,b[3]--,b[5]++;
		else if(b[4]) a[4]--,b[4]--;
		else if(b[1]) a[4]--,b[1]--,b[3]++;
		else if(b[2]) a[4]--,b[2]--,b[4]++;
	}
	else if(a[5]&&b[5]) a[5]--,b[5]--;
	else if(a[5]) a[5]=0;
	brute();
}

int main(){
	int T=readint();
	while(T--){
		for(int i=1;i<=4;i++) a[i]=readint();
		for(int i=1;i<=4;i++) b[i]=readint();
		a[5]=b[5]=0;
		brute();
	}
	return 0;
}