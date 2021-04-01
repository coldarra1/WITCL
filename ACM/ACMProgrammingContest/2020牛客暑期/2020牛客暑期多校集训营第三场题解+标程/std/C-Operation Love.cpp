#include<bits/stdc++.h>
using namespace std;
double x[40], y[40];
double EPS = 1e-3;
double sqr(double v) {return v * v;}
double dis(int id_1,int id_2) {
    return sqrt(sqr(x[id_1] - x[id_2]) + sqr(y[id_1] - y[id_2]));
}
void solve() {
    for(int i = 0; i < 20; i++) {
        scanf("%lf%lf", &x[i], &y[i]);
    }
    x[20] = x[0];
    y[20] = y[0];
    double v = 0;
    for(int i = 0; i < 20; i++) {
        v += x[i] * y[i + 1] - x[i + 1] * y[i];
    }
    if(v < 0) {
        reverse(x, x + 20);
        reverse(y, y + 20);
    }
    x[20] = x[0];
    y[20] = y[0];
    x[21] = x[1];
    y[21] = y[1];
    for(int i = 0; i < 20; i++) {
        if(fabs(dis(i,i  + 1) - 9)<EPS) {
            if(fabs(dis(i + 1, i + 2) - 8) < EPS) {
                puts("right");
            } else {
                puts("left");
            }
            return;
        }
    }
    assert(0);
}
int main() {
    int T;
    scanf("%d", &T);
    for(int i = 1; i <= T; i++) solve();
    return 0;
}
