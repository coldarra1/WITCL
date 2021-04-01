#include<bits/stdc++.h>
#define N 100005
using namespace std;
const int oo=(1e9)-(1e6);
struct Point{
	int x,y;
	int operator < (const Point &b)const{
		return x<b.x||x==b.x&&y<b.y;
	}
	long long operator * (const Point &b)const{
		return 1ll*x*b.y-1ll*y*b.x;
	}
	Point operator - (const Point &b)const{
		return (Point){x-b.x,y-b.y};
	}
	int operator == (const Point &b)const{
		return x==b.x&&y==b.y;
	}
}a[N];
int main(){
	//freopen("C.in","r",stdin);
	//freopen("C.out","w",stdout);
	int T=1e9;
	scanf("%d",&T);
	while (T--){
		int n;scanf("%d",&n);
		for (int i=1;i<=n;i++)
			scanf("%d%d",&a[i].x,&a[i].y);
		/*int n;
		while (true){
			n=rand()%4+1;
			for (int i=1;i<=n;i++) a[i].x=rand()%11-5,a[i].y=rand()%11-5;
			int line=0;
			for (int i=1;i<=n;i++)
				for (int j=i+1;j<=n;j++){
					line|=a[i]==a[j];
					for (int k=j+1;k<=n;k++)
						if ((a[k]-a[i])*(a[j]-a[i])==0) line=1;
				}
			if (!line) break;
		}*/
		//printf("%d\n",n);
		sort(a+1,a+n+1);
		printf("%d %d %d %d\n", a[n/2].x-1,a[n/2].y+oo+1,a[n/2].x+1,a[n/2].y-oo);
	}
}
