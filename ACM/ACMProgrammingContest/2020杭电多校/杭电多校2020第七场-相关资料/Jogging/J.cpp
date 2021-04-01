#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const int ux[] = {1, 1, 1, 0, 0, -1, -1, -1};
const int uy[] = {1, 0, -1, 1, -1, 1, 0, -1};
int gcd(int a,int b){return b==0?a:gcd(b,a%b);}
void calc(i64 x0, i64 y0){
    static const int C = 20000;
    int deg = 0, ord = 0;
    queue<pair<int, int>> q;
    set<pair<int, int>> vis;
    q.emplace(0, 0);
    vis.emplace(0, 0);
    while (q.size()) {
        if (ord > C)
        {
            deg=0;ord=1;
            goto tag;
        }
        int dx, dy;
        tie(dx, dy) = q.front();
        q.pop();
        ++ord;
        for (int dir = 0; dir < 8; ++dir) {
            int dx0 = dx + ux[dir];
            int dy0 = dy + uy[dir];
            if (__gcd(x0 + dx0, y0 + dy0) > 1) {
                ++ord;
                if (vis.count(make_pair(dx0, dy0))) {
                    continue;
                }
                vis.insert(make_pair(dx0, dy0));
                q.emplace(dx0, dy0);
            }
        }
        if (!deg) deg = ord;
    }
    if (!ord)deg=1,ord=1;
    tag:;
    int tp=gcd(deg,ord);
    deg/=tp;ord/=tp;
    cout<<deg <<"/"<< ord<<"\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    for(cin>>T;T;--T){
        i64 x,y;
        cin>>x>>y;
        calc(x,y);
    }
}
