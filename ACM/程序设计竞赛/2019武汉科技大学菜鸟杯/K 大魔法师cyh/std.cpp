#include<iostream>
#include<cassert>
using namespace std;
int n, m;
void solve(){
    cin >> n >> m;
    assert(1 <= n && n <= 1e3);
	assert(1 <= m && m <= 1e9);
    int mmaxhurt = -1e9, mmax = -1e9;
    for(int i = 1; i <= n; i ++){
        int x, y;  cin >> x >> y;
        assert(1 <= x && x <= 1e9);
        assert(1 <= y && y <= 1e9);
        if(x > mmaxhurt) mmaxhurt = x;
        if(x - y > mmax) mmax = x - y;
    }
    if(mmaxhurt < m && mmax <= 0) { cout << "X_X\n"; return; }
    if(mmaxhurt >= m) { cout << "cyhnb!\n1\n"; return ;}
    int ans = 1 + (m - mmaxhurt + mmax - 1) / mmax;
    cout << "cyhnb!\n" << ans << '\n';
}
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
    int T; cin >> T;
    while(T --)solve();
    return 0;
}
