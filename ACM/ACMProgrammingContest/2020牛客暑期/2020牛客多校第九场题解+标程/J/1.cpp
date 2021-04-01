#include<bits/stdc++.h>
#define N 505
using namespace std;
int n,m,s[N][N],a[N][N],cnt[N*N*2],ans,M=N*N;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)scanf("%d",&a[i][j]),s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+(a[i][j]==1)-(a[i][j]==0);
    for(int i=1;i<n;i++)
        for(int j=i+1;j<=n;j++){
            for(int k=1;k<m;k++){
                if(!(a[i][k]&a[j][k]&a[i][k+1]&a[j][k+1]))continue;
                int t=k;
                while(a[i][t+1]&a[j][t+1])t++;
                for(int l=k;l<=t;l++){
                    if(s[j][l]-s[j][l-1]-s[i-1][l]+s[i-1][l-1]==j-i+1){
                        int res=s[j-1][l-1]-s[i][l-1]+M;
                        ans+=cnt[res-1]+cnt[res]+cnt[res+1];
                        cnt[s[j-1][l]-s[i][l]+M]++;
                    }
                }
                for(int l=k;l<=t;l++)
                    if(s[j][l]-s[j][l-1]-s[i-1][l]+s[i-1][l-1]==j-i+1)cnt[s[j-1][l]-s[i][l]+M]--;
                k=t+1;
            }
        }
    printf("%d\n",ans);
    return 0;
}
