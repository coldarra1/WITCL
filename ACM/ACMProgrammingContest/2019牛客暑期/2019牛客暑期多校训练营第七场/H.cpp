#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
int a[31];
int b[31];
int c[31];
int d[31];
long long dp[33][2][2][2][2][2];
long long dfs(int pos,int a1,int b1,int c1, int zero1, int zero2)
{
    if(pos == -1)
    {
        if(c1 == 0 && zero1 == 0 && zero2 == 0)
            return 1;
        else return 0;
    }
    if(dp[pos][a1][b1][c1][zero1][zero2] != -1)return dp[pos][a1][b1][c1][zero1][zero2];
    long long ans = 0;
    int enda = a1?a[pos]:1;
    int endb = b1?b[pos]:1;
    for(int i = 0;i <= enda;i++)
        for(int j = 0;j <= endb;j++)
        {
            if(c1 == 1 && (i&j) < c[pos])
                continue;
            ans += dfs(pos-1,a1 && i == enda,b1 && j==endb,c1 && (i&j) == c[pos], zero1 && i == 0, zero2 && j == 0);
        }
    return dp[pos][a1][b1][c1][zero1][zero2] = ans;
}
 
long long dfs2(int pos, int a1, int b1, int c1, int zero1, int zero2) {
    if (pos == -1) {
        if (c1 == 0 && zero1 == 0 && zero2 == 0) return 1;
        else return 0;
    }
    if (dp[pos][a1][b1][c1][zero1][zero2] != -1) return dp[pos][a1][b1][c1][zero1][zero2];
    long long ans = 0;
    int enda = a1?a[pos]:1;
    int endb = b1?b[pos]:1;
    for (int i = 0; i <= enda; i++)
        for (int j = 0; j <= endb; j++) {
            if (c1 == 1 && (i^j) > c[pos])continue;
            ans += dfs2(pos-1, a1 && i == enda, b1 && j == endb, c1 && (i^j) == c[pos], zero1 && i == 0, zero2 && j == 0);
        }
    return dp[pos][a1][b1][c1][zero1][zero2] = ans;
}
long long dp2[33][2][2][2][2][2][2];
long long dfs3(int pos, int a1, int b1, int c1, int c2, int zero1, int zero2) {
    if (pos == -1) {
        if (c1 == 0 && c2 == 0 && zero1 == 0 && zero2 == 0)return 1;
        else return 0;
    }
    if (dp2[pos][a1][b1][c1][c2][zero1][zero2] != -1) return dp2[pos][a1][b1][c1][c2][zero1][zero2];
    long long ans = 0;
    int enda = a1?a[pos]:1;
    int endb = b1?b[pos]:1;
    for (int i  = 0; i <= enda; i++)
        for (int j = 0; j <= endb; j++) {
            if (c1 == 1 && (i&j) < c[pos])continue;
            if (c2 == 1 && (i^j) > c[pos])continue;
            ans += dfs3(pos-1, a1 && i == enda, b1 && j == endb, c1 && (i&j) == c[pos], c2 && (i^j) == c[pos], zero1 && i == 0, zero2 && j == 0);
        }
    return dp2[pos][a1][b1][c1][c2][zero1][zero2] = ans;
}
 
 
int main()
{
    int T;
    int iCase = 0;
    int A,B,K;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&A,&B,&K);
        iCase++;
        for(int i = 0;i <= 30;i++)
        {
            if(A & (1<<i))
                a[i] = 1;
            else a[i] = 0;
            if(B & (1<<i))
                b[i] = 1;
            else b[i] = 0;
            if(K & (1<<i))
                c[i] = 1;
            else c[i] = 0;
        }
        memset(dp,-1,sizeof(dp));
        long long tmp1 = dfs(30, 1, 1, 1, 1, 1);
 
        /*
        printf("tmp1: %I64d\n", tmp1);
        long long tmp11 = 0;
        for (int i = 1; i <= A; i++)
            for (int j = 1; j <= B; j++)
                if ((i&j) > K)
                    tmp11++;
        printf("tmp11: %I64d\n", tmp11);
        */
 
        memset(dp,-1,sizeof(dp));
        long long tmp2 = dfs2(30, 1, 1, 1, 1, 1);
 
        /*
        printf("tmp2: %I64d\n", tmp2);
        long long tmp22 = 0;
        for (int i = 1; i <= A; i++)
            for (int j = 1; j <= B; j++)
                if ((i^j) < K)
                    tmp22++;
        printf("tmp22: %I64d\n", tmp22);
        */
 
        memset(dp2, -1, sizeof(dp2));
        long long tmp3 = dfs3(30, 1, 1, 1, 1, 1, 1);
        long long ans = tmp1+tmp2-tmp3;
        cout<<ans<<endl;
    }
    return 0;
}
