#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int>pii;
typedef vector<int>vi;

#define rep(i,a,b) for(int i=(a);i<(b);i++)
#define fi first
#define se second
#define de(x) cout<<#x<<"="<<x<<"\n"
#define dd(x) cout<<#x<<"="<<x<<" "
#define pb(x) push_back(x)
#define all(x) x.begin(),x.end()
#define sz(x) (int)x.size()
#define lowbit(a) ((a)&-(a))
#define per(i,a,b) for(int i=(b)-1;i>=(a);--i)
const int N=6e6+5;
const int M = 4e5 + 5;
const int mod = 998244353;
char s[M];
vector<pii> suf;
int stk[N],top,n,L,rt,x[M],nrt;
void toSuf(){
	top = 0;
	int ct = 0,op;
	for(int i = 1,j ;i <= L;){
		if(s[i] == '['){
			j = i + 1,ct = 0;
			while(s[j] != ']')ct = ct*10 + s[j] - '0',j++;
			i = j + 1;
			suf.pb(pii(0,ct));
		}
		else{
			if(s[i] == ')'){
				while(top > 0 && stk[top] != 1)suf.pb(pii(1,stk[top--]));
				top--;
			}
			else if(s[i] == '(')stk[++top] = 1;
			else if(s[i] == '+' || s[i] == '-'){
				while(top > 0 && stk[top] >= 2)suf.pb(pii(1,stk[top--]));
				if(s[i] == '+')stk[++top] = 2;
				else stk[++top] = 3;
			}
			else if(s[i] == '*'){
				while(top > 0 && stk[top] >= 4)suf.pb(pii(1,stk[top--]));
				stk[++top] = 4;
			}
			i++;
		}
	}
	while(top > 0){
		if(stk[top] != 1)
			suf.pb(pii(1,stk[top]));
		top--;
	}
}
struct node{
	int val,op;
	node(){};
	node(int v,int o){
		val = v,op = o;
	}
}t[N];
inline int add(int a,int b){
	return a + b >= mod?a + b - mod:a + b;
}
inline int sub(int a,int b){
	return a >= b?a - b:a + mod - b;
}
inline int mul(int a,int b){
	if(a < 0)a += mod;
	if(b < 0)b += mod;
	return (ll)a*b%mod;
}
vector<pii> g[N],ng[N];
int id,oe,noe,zo,dp[N],lab[N],ans[105];
bool vis[N];
void build(){
	top = 0;
	id = n + 3;
	oe = n + 1,zo = n + 2,noe = n + 3;
	t[oe] = node(1,-1),t[noe] = node(-1,-1),t[zo] = node(0,-1);
	rep(i , 1 , n + 1)t[i] = node(x[i],0);
	for(auto it : suf){
		if(it.fi == 0)stk[++top] = it.se;
		else {
			id++;
			int w1,w2,val,u,v,pd;
			v = stk[top],u = stk[top - 1]; 
			if(it.se == 2)w1 = w2 = oe;	
			else if(it.se == 3)w1 = oe,w2 = noe;
			else{
				w1 = v,w2 = u;
			}
			t[id] = node(0,it.se);
			g[id].pb(pii(u,w1));
			g[id].pb(pii(v,w2));
			top -= 2;
			rt = id;
			stk[++top] = id;
		}
	}
}
int dfs(int u){
	if(vis[u])return lab[u];
	vis[u] = true;
	int cur = ++id; 
	for(int i = 0;i < sz(g[u]);++i){
		int  v = g[u][i].fi,w = g[u][i].se;
		if(t[v].op <= 0){
			int tmp = oe;
			if(t[w].op == -1)tmp = zo;
			g[cur].pb(pii(w,tmp));
		}
		else{
			int cd = dfs(v); 
			id++;
			t[id] = node(0,4);
			if(cd <= n + 3 && cd > n) 
				g[id].pb(pii(cd,zo));
			else g[id].pb(pii(cd,w));
			if(w <= n + 3 && w > n) 
				g[id].pb(pii(w,zo));
			else g[id].pb(pii(w,cd));
			g[cur].pb(pii(id,oe));
		}
	}
	t[cur] = node(0,2);
	lab[u] = cur;
	return cur;
}
int calc(int u){
	if(vis[u])return dp[u];
	vis[u] = true;
	if(t[u].op <= 0)return dp[u] = t[u].val;
	int v[3],ct = 0;
	for(auto it:g[u]){
		v[++ct] = calc(it.fi);
	}
	if(t[u].op == 2)dp[u] = add(v[1],v[2]);
	if(t[u].op == 3)dp[u] = sub(v[1],v[2]);
	if(t[u].op == 4)dp[u] = mul(v[1],v[2]);
	return dp[u];
}
void rebuild(){
	rep(i , 1 , id + 1)vis[i] = false;
	rt = dfs(rt);
}
struct LCARMQ{
    static const int N = 101010 << 1;
    int a[20][N] , lft[N] , dep[N] , lg[N] , L,dfn[N],D;
    int rmin(int x,int y){return dep[x] < dep[y] ? x : y;}
    pii w[N],invw[N],lc[N],rc[N],invlc[N],invrc[N];
	int qpow(int x,int n){
    	int res = 1;
    	while(n > 0){
    		if(n&1)res = (ll)res*x%mod;
    		x = (ll)x*x%mod;
    		n>>=1;
    	}
    	return res;
    }
	pii pmul(pii a,pii b){
    	pii res;
		res.fi = mul(a.fi,b.fi),res.se = a.se+b.se;
		return res;	
	}
	pii pdiv(pii a,pii b){
		pii res;
		res.fi = mul(a.fi,b.fi),res.se = a.se-b.se;
		return res;
	}
	void add(int x){ a[0][L++] = x;}
    void dfs(int c,int fa,const vector<pii> g[]){
        lft[c]=L;add(c);dfn[c] = ++D;
        if(sz(g[c])){
			if(g[c][0].se == 0)lc[c] = invlc[c] = pii(1,1);
			else lc[c] = pii(g[c][0].se,0),invlc[c] = pii(qpow(g[c][0].se,mod-2),0);
			if(g[c][1].se == 0)rc[c] = invrc[c] = pii(1,1);
			else rc[c] = pii(g[c][1].se,0),invrc[c] = pii(qpow(g[c][1].se,mod-2),0);
		}
		
        for(auto t : g[c]) 
			if(t.fi!=fa){
				w[t.fi] = w[c],invw[t.fi] = invw[c];
				if(t.se == 0)w[t.fi].se++,invw[t.fi].se++;
				else w[t.fi].fi = mul(w[t.fi].fi,t.se),invw[t.fi].fi = mul(invw[t.fi].fi,qpow(t.se,mod - 2));
			 	dep[t.fi]=dep[c]+1,dfs(t.fi,c,g),add(c);
			}
    }
    void Build(int rt,const vector<pii> g[]){
        w[rt] = invw[rt] = pii(1,0);D = 0;
		L = 0;dfs(rt,0,g);dep[0] = -1;
        rep(i,2,L) lg[i]=lg[i>>1]+1;
        rep(i,1,20){
            int lim = L+1-(1<<i);
            rep(j,0,lim) a[i][j] = rmin(a[i-1][j] , a[i-1][j+(1<<i>>1)]);
        }
    }
    int lca(int x,int y){
        x = lft[x] , y = lft[y];
        if(x > y) swap(x , y);
        int i = lg[y-x+1];
        return rmin(a[i][x] , a[i][y+1-(1<<i)]);
    }
	void solve(int u,int v,pii &ans){
   		int fa = lca(u,v);
   		if(t[fa].op != 4)ans.fi = 0;
		ans = pmul(ans,w[u]);
		ans = pdiv(ans,invw[fa]);
   		ans = pdiv(ans,invlc[fa]);
   		ans = pdiv(ans,invrc[fa]);
    }
    pii getAns(vi p){
    	pii ans = w[p[0]];
    	rep(i , 1 , sz(p)){
    		if(p[i] == p[i-1])return pii(0,0);
			solve(p[i],p[i-1],ans);
    	}
    	return ans;
	}
}LCA;
bool cmp(int a,int b){
	return LCA.dfn[a] < LCA.dfn[b];
}
void getNewTree(){
	nrt = rt;
	rep(i , 1 , id + 1)vis[i] = false;
	ans[0] = calc(rt);
	dp[oe] = 1,dp[zo] = 0,dp[noe] = -1;
	rep(i , 1 , id + 1){
		for(auto it:g[i]){
			ng[i].pb(pii(it.fi,dp[it.se]));
		}
	}
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--){
		suf.clear();
		scanf("%d%d",&L,&n);
		scanf("%s",s + 1);	
		rep(i , 1 , n + 1)
			scanf("%d",&x[i]);
		toSuf();
		build();
		getNewTree();
		LCA.Build(nrt,ng);
		rep(i , 1 , 6){
			rebuild();
			rep(j , 1 , id + 1)vis[i] = false;
			ans[i] = calc(rt);
		}
		rep(i , 0 , 6){
			printf("%d",ans[i]);
			if(i == 5)printf("\n");
			else printf(" ");
		}
		int m;
		scanf("%d",&m);
		int t,y;vi p;
		pii res;
		int cc = 0;
		rep(i , 1 , m + 1){
			p.clear();
			scanf("%d",&t);
			rep(j , 1, t + 1) {
				scanf("%d",&y);
				p.pb(y);
			}
			sort(all(p),cmp);
			res = LCA.getAns(p);
			if(res.se == 0){
				printf("%d\n",res.fi);
			}
			else printf("0\n");
		}
		rep(i , 1 ,id + 1)
			g[i].clear(),ng[i].clear(),vis[i] = false;
	}
	return 0;
}




