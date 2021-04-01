#include<bits/stdc++.h>
using namespace std;
const int MAX_N = 500000;
int a[MAX_N];
int pos[MAX_N];
int val[MAX_N];
int an[MAX_N];
long long slot[MAX_N];
void solve() {
    int n, m;
    long long k;
    scanf("%d%d%lld", &n, &m, &k);
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    int now = 0;
    int pn = 0;
    int vn = 0;
    for(int i = 0; i < m - 1; i++) pos[pn++] = i;
    for(int i = 0; i < n - m + 1; i++) {
        if(a[i] > now) {
            now = val[vn++] = a[i];
            pos[pn++] = i + m - 1;
        } else {
            an[i + m - 1] = a[i];
        }
    }
    for(int i = n - m + 2; i <= n; i++) val[vn++] = i;
    k--;
    long long bound = 1;
    int num = pn;
    for(int i = 1; i <= pn; i++) {
        if(bound <= k / min(i,m)) {
            bound *= min(i, m);
        } else {
            num = i;
            break;
        }
    }
    //fprintf(stderr,"num: %d\n",num);
    //for(int i = 0; i < pn; i++) printf("pp %d,%d\n",pos[i],val[i]);
    for(int i = 0; i < pn - num; i++) an[pos[i]] = val[i];
    for(int i = 1; i <= num; i++) {
        slot[pn - i] = min(i, m);
    }
    for(int i = pn - num; i < pn; i++) {
        if(!k) {
            for(int j = i; j < pn; j++) an[pos[j]] = val[j];
            break;
        }
        long long tmp = 1;
        for(int j = i + 1; j < pn; j++) {
            tmp *= slot[j];
        }
        for(int j = i; j < pn; j++) {
            if(tmp > k) {
                an[pos[i]] = val[j];
                if(j != i) {
                    rotate(val + i, val + j, val + j + 1);
                    rotate(slot + i, slot + j, slot + j + 1);
                }
                if(pn - j < m) m--;
                break;
            }
            slot[j] --;
            k -= tmp;
            tmp = tmp / slot[j + 1] * slot[j];
        }
    }
    for(int i = 0; i < n; i++) printf("%d%c", an[i], " \n"[i==n-1]);
}
int main() {
    int T;
    scanf("%d", &T);
    for(int tt = 1; tt <= T; tt++) solve();
    return 0;
}
