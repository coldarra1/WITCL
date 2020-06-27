# 解题报告

## Equidistant

我们将树挂在顶点 c~1~ 上，找到最深的节点 c~f~和相应的深度 d，令 v 为从 c~1~ 到 c~f~ 的路径中间的顶点。我们只要证明这个点是否满足要求，则可以知道答案存不存在。

注意到，答案必须位于以 v 为顶点的且不包括 c~f~ 节点的子树中，因为这样才可以保证到 c~1~、c~f~ 的距离相等。并且，以 v 为顶点的且不包括 c~f~ 节点的子树中的 c~i~ 的深度都不会大于 c~f~ 的深度，因为 c~f~ 是深度最深的，那么答案的深度就不能比 v 节点深。因此，我们要做的就是验证节点 v 是否能作为答案。可以以 v 为顶点，dfs 一次，判断所有 c~i~ 距离是否相等即可。

时间复杂度，就为两次 dfs 的复杂度 ：O(n)。


##Std:

```c++
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

```

