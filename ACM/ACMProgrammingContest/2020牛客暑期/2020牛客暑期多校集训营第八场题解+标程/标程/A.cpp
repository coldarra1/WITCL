#include <iostream> 
#include <cstdio> 
#include <cstdlib> 
#include <cstring> 
#include <cmath> 
#include <algorithm>
#include <vector> 
#include <map>
using namespace std; 
inline int gi() { 
    register int data = 0, w = 1; 
    register char ch = 0; 
    while (!isdigit(ch) && ch != '-') ch = getchar(); 
    if (ch == '-') w = -1, ch = getchar(); 
    while (isdigit(ch)) data = 10 * data + ch - '0', ch = getchar(); 
    return w * data; 
}
const int MAX_N = 1e6 + 5;
const int MAX_M = 1e6 + 5; 
int N, M; 
vector<int> vec[1400010 * 3]; 
struct Query { int x, y, t, id; } q[700010], lq[700010], rq[700010]; 
struct Modify { int x, y; } p[700010]; 
bool ans[700010]; 
int fa[400010*2], rnk[400010*2];
pair<int, int> stk[400010*2]; int top; 
int getf(int x) { return x == fa[x] ? x : getf(fa[x]); } 
void unite(int x, int y) { 
	x = getf(x), y = getf(y);
	if (x == y) return ; 
	if (rnk[x] < rnk[y]) swap(x, y); 
	fa[y] = x; 
	stk[++top] = make_pair(y, rnk[y]);
	if (rnk[x] == rnk[y]) stk[++top] = make_pair(x, ++rnk[x]); 
} 
void Undo(int cur) {
	while (top > cur) { 
		pair<int, int> pre = stk[top--]; 
		fa[pre.first] = pre.first; 
		rnk[pre.first] = pre.second; 
	} 
} 
#define lson (o << 1) 
#define rson (o << 1 | 1) 
void modify(int o, int l, int r, int ql, int qr, int pos) { 
	if (ql <= l && r <= qr) return (void)vec[o].push_back(pos);
	int mid = (l + r) >> 1; 
	if (ql <= mid) modify(lson, l, mid, ql, qr, pos); 
	if (qr > mid) modify(rson, mid + 1, r, ql, qr, pos); 
} 
void Div(int o, int lval, int rval, int st, int ed) { 
	if (st > ed) return ;
	int cur = top;
	for (int i = 0, l = vec[o].size(); i < l; i++) unite(p[vec[o][i]].x, p[vec[o][i]].y); 
	if (lval == rval) {
		for (int i = st; i <= ed; i++) 
	    	ans[q[i].id] = getf(q[i].x) == getf(q[i].y);
		return ; 
	} 
	int mid = (lval + rval) >> 1, lt = 0, rt = 0; 
	for (int i = st; i <= ed; i++) 
		if (q[i].t <= mid) lq[++lt] = q[i]; 
		else rq[++rt] = q[i]; 
	for (int i = 1; i <= lt; i++) q[st + i - 1] = lq[i]; 
	for (int i = 1; i <= rt; i++) q[st + i + lt - 1] = rq[i]; 
	Div(lson, lval, mid, st, st + lt - 1); 
    Div(rson, mid + 1, rval, st + lt, ed);
	Undo(cur); 
}
int cnt1, cnt2; 

long long code(int u, int v) {
	return (long long)u*MAX_N + v;
}

int du[400010];
int op[700010];

int main() {
	int n, m, qq;
	scanf("%d%d%d", &n, &m, &qq);
	N = n + m;
	for (int i = 1; i <= N; i++) fa[i] = i, rnk[i] = 1;
	vector<pair<int, int>> vec;
	for (int i = 1; i <= n; i++) {
		int k;
		scanf("%d", &k);
		while (k--) {
			int u;
			scanf("%d", &u);
			vec.push_back(make_pair(i, u + n));
		}
	}
	int itot = vec.size();
	for (int i = 1; i <= qq; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		vec.push_back(make_pair(v, u+n));
	}

	int vecsize = vec.size();
	map<long long, int> mp_vec;
	cnt1 = cnt2 = 0;
	M = vecsize + vecsize;
	for (int i = 1;i <= vecsize; i++) {
		int x = vec[i-1].first;
		int y = vec[i-1].second;
		long long tmp = code(x, y);
		int id = 2*i;
		if (mp_vec.count(tmp) && mp_vec[tmp]) {
			id--;
			modify(1, 1, M, mp_vec[tmp], id, ++cnt1);

			p[cnt1] = (Modify){x, y};
			mp_vec[tmp] = 0;
			op[i] = 1;
		} else {
			mp_vec[tmp] = id;
			op[i] = 0;
		}
	}
	for (int i = 1; i <= vecsize; i++) {
		int x = vec[i-1].first;
		int y = vec[i-1].second;
		long long tmp = code(x, y);
		int id = 2*i;
		if (mp_vec.count(tmp) && mp_vec[tmp]) {
			modify(1, 1, M, mp_vec[tmp], M, ++cnt1);
			p[cnt1] = (Modify){x, y};
		}
		q[++cnt2] = (Query){x, y, 2*i - (op[i]==0), cnt2};
	}
	Div(1, 1, M, 1, cnt2);

	memset(du, 0, sizeof(du));
	int c0 = m;
	int d0 = n; 
	int dd = n;
	for (int i = 1; i <= vecsize; i++) {
		int x = vec[i-1].first;
		int y = vec[i-1].second;

		if (op[i] == 0) {
			if (du[y] == 0) c0--;
			if (du[x] == 0) d0--;
			du[x]++;
			du[y]++;
			if (ans[i] == 0) {
				if (du[y] > 1) dd--;
			}
		} else {
			du[x]--;
			du[y]--;
			if (du[y] == 0) c0++;
			if (du[x] == 0) d0++;
			if (ans[i] == 0) {
				if (du[y] > 0) dd++;
			}
		}

		if (i > itot) {
			if (c0 != 0) puts("-1");
			else printf("%d\n", dd - d0);
		}
	}
	return 0;
}
