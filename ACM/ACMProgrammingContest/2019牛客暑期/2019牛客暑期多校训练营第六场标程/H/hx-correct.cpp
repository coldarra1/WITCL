#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define rpm(x, l, r) for(int x = l; x < (r); ++x)
//segment tree
#define ls (t << 1)
#define rs ((t << 1) | 1)
#define mid ((l + r) >> 1)
#define lt t, l, mid
#define rt t, mid + 1, r

typedef pair<int, int> pii;
typedef long long ll;
typedef unsigned long long ull;
const int M = 1000000007;

const int maxn = 100005;
int n, m, k1, k2;

int he[maxn], ne[maxn << 1], to[maxn << 1], e;

int dis[41][maxn], d[maxn];
int p[21], q[21];
ll ans;

int tot, inx;
int vis[maxn << 1];
int head[maxn << 1], nex[maxn];

int que[maxn];

void dij(int s, int dis[]){
	memset(dis, 127, sizeof(int) * (n + 1));
	dis[s] = 0;
	queue<int> q;
	q.push(s);
	while(!q.empty()){
		int u = q.front(); q.pop();
		for(int j = he[u]; j; j = ne[j]){
			int v = to[j];
			if(dis[v] > dis[u] + 1){
				dis[v] = dis[u] + 1;
				q.push(v);
			}
		}
	}
}

void solve(int d1[], int d2[]){
	int step_min = n << 1, step_max = 0;
	tot = 0; ++inx;
	for(int i = 1; i <= n; ++i){
		d[i] = d1[i] + d2[i];
		step_min = min(step_min, d[i]);
		step_max = max(step_max, d[i]);

		if(vis[d[i]] < inx) vis[d[i]] = inx, head[d[i]] = 0;
		nex[i] = head[d[i]], head[d[i]] = i;
	}
	
	int l = 1, r = 0;
	for(int step = step_min; step < step_max - 1; ++step){
		if(vis[step] == inx)
			for(int i = head[step]; i; i = nex[i])
				if(d[i] == step) que[++r] = i;
		assert(r <= n);
		int pre_r = r;
		for(int i = l; i <= pre_r; ++i){
			int u = que[i];
			for(int j = he[u]; j; j = ne[j]){
				int v = to[j];
				if(d[v] > d[u] + 1){
					d[v] = d[u] + 1;
					que[++r] = v;
				}
			}
		}
		l = pre_r + 1;
	}

	for(int i = 1; i <= n; ++i) ans += d[i];
}

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &m);
		e = 0;
		fill(he + 1, he + n + 1, 0);
		for(int i = 1; i <= m; ++i){
			static int u, v;
			scanf("%d%d", &u, &v);
			to[++e] = v, ne[e] = he[u], he[u] = e;
			to[++e] = u, ne[e] = he[v], he[v] = e;
		}
		scanf("%d", &k1);
		for(int i = 1; i <= k1; ++i){
			scanf("%d", p + i);
			dij(p[i], dis[i]);
		}
		scanf("%d", &k2);
		for(int i = 1; i <= k2; ++i){
			scanf("%d", q + i);
			dij(q[i], dis[i + k1]);
		}
		
		ans = 0;
		for(int i = 1; i <= k1; ++i)
			for(int j = 1; j <= k2; ++j)
				solve(dis[i], dis[j + k1]);

		ll g = __gcd(ans, 1LL * k1 * k2 * n);
		static int t = 0;
		printf("Case #%d: %lld/%lld\n", ++t, ans / g, k1 * k2 * n / g);
	}
	return 0;
}
