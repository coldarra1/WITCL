#include<bits/stdc++.h>
#define PI acos(-1)
#define pb push_back
#define all(x) x.begin(),x.end()
#define INF 0x3f3f3f3f
#define dd(x) cout<<#x<<" = "<<x<<","
#define de(x) cout<<#x<<" = "<<x<<"\n"
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int N=1e5+5; 
int n,m,q;ll t;
int d,a[2*N],b[N],c[N],sum1[2*N],sum2[2*N],sum3[2*N];
ll qpow(ll a,ll n,ll mod){
	ll re=1;
	while(n>0){
		if(n&1){
			re*=a;
			re%=mod;
		}
		a*=a;
		a%=mod;
		n>>=1;
	}
	return re;
}
int tree[N][5];
void add(int i,int v,int num){
	for(;i<=n;i+=i&-i){
		tree[i][num]+=v;
		tree[i][num]%=n;
	}
}
int query(int i,int num){
	int re=0;
	for(;i>0;i-=i&-i){
		re+=tree[i][num];
		re%=n;
	}
	return re;
}
void init(){
	a[2*n]=c[2*n]=sum1[2*n]=sum2[2*n]=sum3[2*n]=0;
	for(int i=n-1;i>=1;i--){
		a[i]=(a[i+1]-d+n)%n;
	}
	for(int i=n+1;i<=2*n-1;i++){
		a[i]=(a[i-1]+d)%n;
	}
	for(int i=1;i<=2*n-1;i++){
		c[i]=qpow(a[i],t,n);
	}
	for(int i=1;i<=2*n-1;i++){
		sum1[i]=(c[i]+sum1[i-1])%n;
	}
	for(int i=1;i<=2*n-1;i++){
		sum2[i]=(1ll*c[i]*i+sum2[i-1])%n;
	}
	for(int i=2*n-1;i>=1;i--){
		sum3[i]=(1ll*c[i]*(2*n-i)+sum3[i+1])%n;
	}
//	for(int i=1;i<=2*n-1;i++){
//		dd(i),dd(a[i]),dd(sum1[i]),dd(sum2[i]),de(sum3[i]);
//	}
} 
int cal(int x,int y){
	int re=0;
	if(x<0||y<0){
		return re;
	}
	if(x<=y){
		re=1ll*(x+1)*(sum1[n+y-x]-sum1[n-1]+n)%n;
		re+=sum2[n-1]-sum2[n-1-x]+n-1ll*(n-1-x)*(sum1[n-1]-sum1[n-1-x]+n)%n+n;
		re%=n;
		re+=sum3[n+y-x+1]-sum3[n+y+1]+n-1ll*(n-1-y)*(sum1[n+y]-sum1[n+y-x]+n)%n+n;
		re%=n;
	}
	else if(x>y){
		re=1ll*(y+1)*(sum1[n]-sum1[n-1-x+y]+n)%n;
		re+=sum2[n-1-x+y]-sum2[n-1-x]+n-1ll*(n-1-x)*(sum1[n-1-x+y]-sum1[n-1-x]+n)%n+n; 
		re%=n;
		re+=sum3[n+1]-sum3[n+y+1]+n-1ll*(n-1-y)*(sum1[n+y]-sum1[n]+n)%n+n;
		re%=n;
	}
	return re;                            
}
int cal2(int px,int py,int qx,int qy){
	int re=0;
	px++;py++;qx++;qy++;
	re+=1ll*(query(qx,1)-query(px-1,1)+n)*(qy-py+1)%n;
	re%=n;
	re+=1ll*(query(qy,3)-query(py-1,3)+n)*(qx-px+1)%n;
	re%=n;
	int d=(query(qx,2)-query(px-1,2)+n)%n;
	re+=(1ll*(1ll*d*(py-1)+1ll*d*(qy-1))*(qy-py+1)/2)%n;
	re%=n;
	
	d=(query(qy,4)-query(py-1,4)+n)%n;
	re+=(1ll*(1ll*d*(px-1)+1ll*d*(qx-1))*(qx-px+1)/2)%n;
	re%=n;
	
	return re;
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d%lld%d%d",&n,&t,&m,&q);
		for(int i=0;i<n;i++){
			scanf("%d",&b[i]);
		}
		a[n]=d=0;
		for(int i=0,j=0;i<n;i++){
			a[n]+=(ll)i*b[j]%n;
			a[n]%=n;
			j=(j-1+n)%n;
		}
		for(int i=0;i<n;i++){
			d+=b[i];
			d%=n;
		}
//		dd(a[n]),de(d);
		init();
//		for(int i=0;i<n;i++){
//			for(int j=0;j<n;j++){
//				printf("%d ",cal1(i,j));
//			}
//			printf("\n");
//		} 
		int op;
		while(m--){
			scanf("%d",&op);
			int px,py,qx,qy;
			scanf("%d%d%d%d",&px,&py,&qx,&qy);
			int ans=(cal(qx,qy)-cal(qx,py-1)-cal(px-1,qy)+cal(px-1,py-1)+n+n)%n;
			printf("%d\n",ans);
		}
		for(int i=0;i<n;i++){
			add(i+1,a[n-i],1); 
			add(i+1,d,2);
		}
		while(q--){
//			for(int i=0;i<n;i++){
//				for(int j=0;j<n;j++){
//					printf("%d ",cal2(i,j,i,j));
//				}
//				printf("\n");
//			}
//			printf("\n");
			scanf("%d",&op);
			if(op==1){
				int i,k,v;
				scanf("%d%d%d",&i,&k,&v);
				add(i+1,1ll*k*(n-v)%n,1);
				add(i+1,k,2);
			} 
			else if(op==2){
				int j,k,v;
				scanf("%d%d%d",&j,&k,&v);
				add(j+1,1ll*k*(n-v)%n,3);
				add(j+1,k,4);
			}
			else if(op==3){
				int px,py,qx,qy;
				scanf("%d%d%d%d",&px,&py,&qx,&qy);
				printf("%d\n",cal2(px,py,qx,qy));
			}
		}
		for(int i=1;i<=n;i++){
			tree[i][1]=tree[i][2]=tree[i][3]=tree[i][4]=0;
		}
	} 
}
/*
1
5 1 0 5
0 4 3 2 1
1 2 2 1
2 2 3 2
3 1 1 3 3
3 0 0 4 1
3 0 2 4 2

1
3
2

*/
