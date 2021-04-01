#include<cstdio>
const int MAX_N = 26;
int n,m;
int e[MAX_N];
char dp[1<<MAX_N];
int max(int x,int y){return x>y?x:y;}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        e[x]|=1<<y;
        e[y]|=1<<x;
    }
    for(int i=0;i<n;i++){
        e[i]|=1<<i;
        e[i]=~e[i];
    }
    int it=0;
    int an=0;
    for(int i=1;i<(1<<n);i++){
        if(!((i>>it)&1))it++;
        dp[i]=max(dp[i^(1<<it)],dp[i&e[it]]+1);
        an+=dp[i];
    }
    printf("%d\n",an);
    return 0;
}
