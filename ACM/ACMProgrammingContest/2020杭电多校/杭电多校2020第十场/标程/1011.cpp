#include<bits/stdc++.h>
using namespace std;
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        int n,k;
        scanf("%d%*d%d",&n,&k);
        vector<int> t(n),idx(n);
        for(int i=0;i<n;i++)
            scanf("%d",&t[i]);
        iota(idx.begin(),idx.end(),0);
        if(k)stable_sort(idx.begin(),idx.end(),[&](int a,int b){
             return t[a]>t[b];
        });
        for(int i=0;i<n;i++)
            printf("%d%c",idx[i]+1," \n"[i==n-1]);
    }
    return 0;
}