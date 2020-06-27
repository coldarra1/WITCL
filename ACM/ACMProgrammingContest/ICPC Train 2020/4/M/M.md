题意：

给一个数组a，求(i,j,k)三元组的数量满足$1\leq i<j<k\leq n$且$a_k-a_j = a_j-a_i$。

题解：

枚举$j$,用一个map来记录j后面所有的$a_k$及其出现的次数，再枚举$i$，根据$a_i$和$a_j$的值，算出$a_k$的值，再从map中获取对应的次数。map初始化时可以先将所有$a_i$加进去，在枚举$j$的过程中不断地更新map，从中将$a_j$的次数减一。

时间复杂度：$n^2logn$

```c++
#include <bits/stdc++.h>
#define N 2005
#define fi first
#define sc second
using namespace std;

int a[N];

unordered_map<int,int> mp;

int main(){
    int tt;
    scanf("%d",&tt);
    while(tt--){
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]); mp[a[i]]++;
        }
        int num=0;
        mp[a[1]]--;
        for(int j=2;j<=n-1;j++){
            mp[a[j]]--;
            for(int i=1;i<j;i++){
                int val=2*a[j]-a[i];
                if(mp.find(val)!=mp.end()){
                    num+=mp[val];
                }
            }
        }
        printf("%d\n",num);
        mp.clear();
    }
}
/*
1
5
1 2 1 2 1
*/

```

