题意：

令Treap的一对二维点权为\(f, sin(x)\)，现在要给出n个x，使得这个Treap的深度最大

题解：

考虑很小的时候，\(x = sin(x)\)，那么它两维都是单调的，深度最大

```c++

#include <bits/stdc++.h>
#define P pair<double,int>
using namespace std;

int main(){
    int n;
    cin>>n;
    vector<P> v; vector<int> vv;
    for(int i=1;i<=50000;i++){
        if(sin(i)>0) v.push_back(P(sin(i),i));
    }
    double t=v[0].first;
    sort(v.begin(),v.end());
    for(int i=-25000;i<=25000;i++){
        vv.push_back(i*v[0].second);
    }
    sort(vv.begin(),vv.end());
    for(int i=0;i<n;i++) printf("%d\n",vv[i]);
}

```

