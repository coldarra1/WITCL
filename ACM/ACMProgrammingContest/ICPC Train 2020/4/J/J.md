# 解题报告

## Equidistant

问题可以简化为：给出了无环有向图中每对顶点之间的路径数（取模 10），需要还原该图

因为对于所有i>j，不存在节点i到节点j的边。所以我们开始从顶点1恢复图形。如果a~1,2~数量为0，则代表节点1,2之间没有边；否则有边，且a~1,2~必须等于1，我们删除这条边，那么a~1,i~的数量会减少a~2,i~的数量。接下来，考虑a~1,3~。如果为0，则代表节点1,3之间没有边，如果为1，则有边，我们可以从a~1,i~中减去a~3,i~。一次类推，可以找到节点1和其他节点之间是否有边。时间复杂度为O(n^2^)。

类似的,可以一层一层的遍历,就可以知道每个节点的情况。总时间复杂度为O(n^3^)。


##Std:

```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxx=500+10;
const ll mod=10;
int a[maxx][maxx],ans[maxx][maxx];
int main(){
    int n; cin>>n;
    for(int i=1;i<=n;i++){
        string s; cin>>s;
        for(int j=0;j<n;j++){
            a[i][j+1]=s[j]-'0';
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            ans[i][j]=a[i][j];
            if(ans[i][j]){
                for(int k=j+1;k<=n;k++){
                    a[i][k]=(a[i][k]-a[j][k]+mod)%mod;
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            cout<<ans[i][j]; puts("");
    }
}


```

