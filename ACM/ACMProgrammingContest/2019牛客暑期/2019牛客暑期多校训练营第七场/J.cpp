#include <bits/stdc++.h>
using namespace std;
 
long long cao(long long x) {
    long long ret = 0;
    while (x) {
        ret = ret*10 + x%10;
        x /= 10;
    }
    return ret;
}
int main() {
    long long A, B;
    int T;
    cin>>T;
    while (T--) {
        cin>>A>>B;
        assert(A > 0 && A < (1LL<<31));
        cout<<cao(cao(A) + cao(B))<<endl;
 
    }
    return 0;
}
