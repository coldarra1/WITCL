#include<stdio.h>
int dp[1005];
int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        int n;scanf("%d",&n);
        for(int i=3;i<=n;i++){
            for(int j=i-1;j>=i-i/2+1;j--){
                if(dp[j]==0) {
                    dp[i]=1;break;
                }
            }
        }
        if(dp[n]) puts("cyhnb!!!");
        else puts("wxnb!!!");
////  SOLUTION2
//        int flag=0;
//        for(int i=3;i<=1000;i=i*2-1){
//            if(i==n) {flag=1;break;}
//        }
//        if(flag) puts("wxnb!!!");
//        else puts("cyhnb!!!");
    }
    return 0;
}