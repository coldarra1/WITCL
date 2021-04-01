#include <bits/stdc++.h>
using namespace std;
 
const int MAXN = 100010;
 
struct NN {
    int H, C, P, index;
    void input() {
        scanf("%d%d%d", &H, &C, &P);
    }
}node[MAXN];
 
bool cmp1(NN N1, NN N2) {
    return N1.C < N2.C;
}
 
bool cmp2(NN N1, NN N2) {
    return N1.H < N2.H;
}
 
struct Node {
    int l, r;
    long long num;
    long long sum;
}segTree[MAXN*3];
 
void push_up(int i) {
    if (segTree[i].l == segTree[i].r) {
        return;
    }
    segTree[i].num = segTree[i<<1].num + segTree[(i<<1)|1].num;
    segTree[i].sum = segTree[i<<1].sum + segTree[(i<<1)|1].sum;
}
void build(int i, int l, int r) {
    segTree[i].l = l;
    segTree[i].r = r;
    segTree[i].num = 0;
    segTree[i].sum = 0;
    if (l == r) {
        return;
    }
    int mid = (l+r)/2;
    build(i<<1, l, mid);
    build((i<<1)|1, mid+1, r);
}
 
void add(int i, int index, int C, int P) {
    if (segTree[i].l == index && segTree[i].r == index) {
        segTree[i].num += P;
        segTree[i].sum += (long long)C * P;
        return;
    }
    int mid = (segTree[i].l + segTree[i].r)/2;
    if (index <= mid) add(i<<1, index, C, P);
    else add((i<<1)|1, index, C, P);
    push_up(i);
}
 
long long query(int i, long long num) {
    if (num <= 0) return 0;
    if (num >= segTree[i].num) return segTree[i].sum;
    if (segTree[i].l == segTree[i].r) {
        return segTree[i].sum / segTree[i].num * num;
    }
    return query(i<<1, num) + query((i<<1)|1, num - segTree[i<<1].num);
}
 
 
int main() {
    int n;
    int T = 0;
    while (scanf("%d", &n) == 1) {
        assert(n >= 1 && n <= 100000);
        T++;
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            node[i].input();
            ans += (long long) node[i].C * node[i].P;
            assert(node[i].H >= 1 && node[i].H <= 1000000000);
            assert(node[i].P >= 1 && node[i].P <= 1000000000);
            assert(node[i].C >= 1 && node[i].C <= 200);
        }
        sort(node, node+n, cmp1);
        for (int i = 0; i < n; i++)
            node[i].index = i+1;
        build(1, 1, n);
        sort(node, node+n, cmp2);
 
 
        int j = 0;
        long long tot = 0;
        long long numOfTallest = node[0].P;
        long long res = ans - (long long)node[0].P*node[0].C;
        int ansIndex = 0;
        for (int i = 1; i <= n; i++) {
            if (i == n || node[i].H != node[i-1].H) {
                long long tmp = query(1, tot - (numOfTallest-1)) + res;
                if (ans > tmp) {
                    ans = tmp;
                    ansIndex = i-1;
                }
                numOfTallest = node[i].P;
                if (i < n) {
                    while (j < i) {
                        add(1, node[j].index, node[j].C, node[j].P);
                        tot += node[j].P;
                        j++;
                    }
                }
            } else {
                numOfTallest += node[i].P;
            }
            if (i < n) res -= (long long)node[i].C * node[i].P;
        }
        printf("%lld\n", ans);
    }
    assert(T <= 30);
    return 0;
}
