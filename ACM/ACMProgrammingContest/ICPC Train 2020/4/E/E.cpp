#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxx=2e5+10;
vector<int> a[maxx];
int c[maxx],num[maxx],d[maxx],f[maxx];
void dfs(int x,int fa){
    f[x]=fa;
    d[x]=d[fa]+1;
    for(auto t:a[x]){
        if(t==fa) continue;
        dfs(t,x);
    }
}
int main(){
    int n,m; cin>>n>>m;
    for(int i=1;i<n;i++){
        int x,y; scanf("%d%d",&x,&y);
        a[x].push_back(y);
        a[y].push_back(x);
    }
    for(int i=1;i<=m;i++){
        scanf("%d",c+i);
    }
    if(m==1) return 0*puts("YES\n1");
    dfs(c[1],0);
    int key=c[2];
    for(int i=2;i<=m;i++)
        if(d[key]<d[c[i]]) key=c[i];
    if((d[c[1]]+d[key])&1) return 0*puts("NO");
    int ans=(d[c[1]]+d[key])>>1;
    int x=key;
    while(d[x]!=ans){
        x=f[x];
    }
    dfs(x,0);
    for(int i=2;i<=m;i++){
        if(d[c[i]]!=d[c[i-1]])
            return 0*puts("NO");
    }
    puts("YES");
    cout<<x<<endl;
}

