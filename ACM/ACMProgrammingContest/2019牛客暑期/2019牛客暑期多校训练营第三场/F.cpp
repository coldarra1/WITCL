#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=611;
int i,j,k,n,m,tests,a[N][N],q1[N],q2[N],l1,r1,l2,r2,b1[N],b2[N],ans,w;
int main(){
//	freopen("a.in","r",stdin);
	for (scanf("%d",&tests);tests--;){
		scanf("%d%d",&n,&m);ans=0;
		for (i=1;i<=n;i++)
		 for (j=1;j<=n;j++) scanf("%d",&a[i][j]);
		for (i=1;i<=n;i++){
			for (j=1;j<=n;j++) b1[j]=b2[j]=a[i][j];
			for (j=i;j<=n;j++){
				for (k=1;k<=n;k++) b1[k]=min(b1[k],a[j][k]),b2[k]=max(b2[k],a[j][k]);
				l1=l2=1;r1=r2=0;
				if ((j-i+1)*n<ans) continue;
				for (k=w=1;k<=n;k++){
					while (l1<=r1&&b1[q1[r1]]>=b1[k]) r1--;
					q1[++r1]=k;
					while (l2<=r2&&b2[q2[r2]]<=b2[k]) r2--;
					q2[++r2]=k;
					while (w<=k&&b2[q2[l2]]-b1[q1[l1]]>m){
						w++;
						while (l1<=r1&&q1[l1]<w) l1++;
						while (l2<=r2&&q2[l2]<w) l2++;
					}
					if ((j-i+1)*(n-w+1)<ans) break;
					if (w<=k) ans=max(ans,(j-i+1)*(k-w+1));
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}