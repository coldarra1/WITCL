#include <bits/stdc++.h>
using namespace std;
const int N = 1005;

int n, m;
long long c[N][N] , mx[N] , l[N];
int d[N];

void work() {
    scanf("%d%d" , &n , &m);
    for (int i = 0 ; i < n ; ++ i) {
        for (int j = 1 ; j <= m ; ++ j) {
            scanf("%lld" , &c[i][j]);
            c[i][j] = -c[i][j];
        }
        for (int j = 0 ; j < m ; ++ j) {
            c[i][j + 1] += c[i][j];
        }
    }
    long long bonus = 0;
    for (int i = 1 ; i <= m ; ++ i) {
        scanf("%d" , &d[i]);
        bonus += d[i];
    }
    long long res = 0;
    for (int i = m ; i >= 0 ; -- i) {
        long long sum = 0;
        for (int j = 0 ; j < n ; ++ j) {
            mx[j] = i == m ? c[j][i] : max(mx[j] , c[j][i]);
            sum += mx[j];
        }
        for (int j = 0 ; j < n ; ++ j) {
            res = max(res, sum - mx[j] + c[j][i] + bonus);
        }
        bonus -= d[i];
    }
    static int ca = 0;
    printf("Case #%d: %lld\n" , ++ ca , res);
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --) {
        work();
    }
}