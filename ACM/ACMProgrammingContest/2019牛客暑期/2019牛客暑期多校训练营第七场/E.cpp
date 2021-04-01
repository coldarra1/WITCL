#include <bits/stdc++.h>
using namespace std;
 
const int MAXN = 400010;
int a[MAXN*2];
int L[MAXN];
int R[MAXN];
 
struct Node {
    int l, r;
    long long sum;
    int lazy;
}segTree[MAXN<<3];
 
void build(int i, int l, int r) {
    segTree[i].l = l;
    segTree[i].r = r;
    segTree[i].sum = 0;
    segTree[i].lazy = 0;
    if (l+1 == r) return;
    int mid = (l+r)/2;
    build(i<<1, l, mid);
    build((i<<1)|1, mid, r);
}
 
void push_down(int i) {
    if (segTree[i].lazy == 0)return;
    if (segTree[i].l+1 == segTree[i].r) {
        return;
    }
    segTree[i<<1].lazy += segTree[i].lazy;
    segTree[i<<1].sum += (long long) segTree[i].lazy * (a[segTree[i<<1].r] - a[segTree[i<<1].l]);
    segTree[(i<<1)|1].lazy += segTree[i].lazy;
    segTree[(i<<1)|1].sum += (long long) segTree[i].lazy * (a[segTree[(i<<1)|1].r] - a[segTree[(i<<1)|1].l]);
    segTree[i].lazy = 0;
}
 
void push_up(int i) {
    if (segTree[i].l+1 == segTree[i].r) return;
    segTree[i].sum = segTree[i<<1].sum + segTree[(i<<1)|1].sum;
}
 
void update(int i, int l, int r) {
    if (segTree[i].l == l && segTree[i].r == r) {
        segTree[i].sum += a[r] - a[l];
        segTree[i].lazy++;
        return;
    }
    int mid = (segTree[i].l + segTree[i].r)/2;
    push_down(i);
    if (r <= mid) update(i<<1, l, r);
    else if (l >= mid) update((i<<1)|1, l, r);
    else {
        update(i<<1, l, mid);
        update((i<<1)|1, mid, r);
    }
    push_up(i);
}
 
int query(int i, long long num) {
    if (segTree[i].l + 1 == segTree[i].r) {
        long long tmp = segTree[i].sum / (a[segTree[i].r] - a[segTree[i].l]);
        return (int)(a[segTree[i].l] + (num-1)/tmp);
    }
    push_down(i);
    if (num <= segTree[i<<1].sum) return query(i<<1, num);
    else return query((i<<1)|1, num - segTree[i<<1].sum);
}
 
 
void solve(vector<pair<int, int>> vec) {
    int n = vec.size();
 
    int tot = 0;
    for (int i = 0; i < n; i++) {
        vec[i].second++;
        a[tot++] = vec[i].first;
        a[tot++] = vec[i].second;
    }
    sort(a, a+tot);
    tot = unique(a, a+tot) - a;
    for (int i = 0; i < n; i++) {
        L[i] = lower_bound(a, a+tot, vec[i].first) - a;
        R[i] = lower_bound(a, a+tot, vec[i].second) - a;
    }
 
    build(1, 0, tot-1);
 
    long long totNum = 0;
    for (int i = 0; i < n; i++) {
        totNum += vec[i].second - vec[i].first;
        update(1, L[i], R[i]);
 
        printf("%d\n", query(1, (totNum+1)/2));
    }
}
 
void brute_force(vector<pair<int, int>> vec) {
    long long totNum = 0;
    int lmin = vec[0].first;
    int rmax = vec[0].second;
    int n = vec.size();
    for (int i = 0; i < n; i++) {
        totNum += vec[i].second - vec[i].first + 1;
        lmin = min(lmin, vec[i].first);
        rmax = max(rmax, vec[i].second);
        int l = lmin, r = rmax;
        int ans = r;
        while (l <= r) {
            int mid = (l+r)>>1;
            long long tmp = 0;
            for (int j = 0; j <= i; j++) {
                if (mid < vec[j].first) continue;
                tmp += min(mid, vec[j].second) - vec[j].first + 1;
            }
            if (tmp >= (totNum+1)/2) {
                ans = mid;
                r = mid-1;
            } else {
                l = mid+1;
            }
        }
        printf("%d\n", ans);
    }
}
 
int X[MAXN], Y[MAXN];
 
int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        assert(n >= 1 && n <= 400000);
 
        int A1, B1, C1, M1;
        scanf("%d%d%d%d%d%d", &X[1], &X[2], &A1, &B1, &C1, &M1);
        assert(0 <= A1 && A1 < M1);
        assert(0 <= B1 && B1 < M1);
        assert(0 <= C1 && C1 < M1);
        assert(0 <= X[1] && X[1] < M1);
        assert(0 <= X[2] && X[2] < M1);
        assert(1 <= M1 && M1 <= 1000000000);
        for (int i = 3; i <= n; i++) {
            X[i] = ((long long)A1*X[i-1] + (long long)B1*X[i-2] + C1) % M1;
        }
        int A2, B2, C2, M2;
        scanf("%d%d%d%d%d%d", &Y[1], &Y[2], &A2, &B2, &C2, &M2);
        assert(0 <= A2 && A2 < M2);
        assert(0 <= B2 && B2 < M2);
        assert(0 <= C2 && C2 < M2);
        assert(0 <= Y[1] && Y[1] < M2);
        assert(0 <= Y[2] && Y[2] < M2);
        assert(1 <= M2 && M2 <= 1000000000);
        for (int i = 3; i <= n; i++) {
            Y[i] = ((long long)A2*Y[i-1] + (long long)B2*Y[i-2] + C2) % M2;
        }
 
 
        int l, r;
        vector<pair<int, int>>vec;
        for (int i = 1; i <= n; i++) {
            l = min(X[i], Y[i]) + 1;
            r = max(X[i], Y[i]) + 1;
            vec.push_back(make_pair(l, r));
        }
        solve(vec);
    }
    return 0;
}
