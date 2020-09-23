
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



