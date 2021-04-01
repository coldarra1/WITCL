#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

struct Sam{
	Sam *fa, *go[10];
	int val;
	
	void clear()
	{
		fa = 0;
		val = 0;
		memset(go, 0, sizeof(go));
	}
}*now, *root, *last, *cur, Pool[N * 10 * 2], *a[N];

char s[N];
int pos[N], ne[N];

void Prepare()
{
	cur = Pool;
	cur -> clear();
	root = last = cur;
}

Sam *Insert(Sam *last, int now)
{
	Sam *p = last;
	if(p -> go[now])
	{
		Sam *q = p -> go[now];
		if(q -> val == p -> val + 1)return q;
		Sam *nt = ++cur;
		nt -> clear();
		nt -> val = p -> val + 1;
		memcpy(nt -> go, q -> go, sizeof(q -> go));
		nt -> fa = q -> fa;
		q -> fa = nt;
		while(p && p -> go[now] == q)p -> go[now] = nt, p = p -> fa;
		return nt;
	}
	Sam *np = ++cur;
	np -> clear();
	np -> val = p -> val + 1;
	while(p && !p -> go[now])p -> go[now] = np, p = p -> fa;
	if(!p)np -> fa = root;
	else
	{
		Sam *q = p -> go[now];
		if(q -> val == p -> val + 1)
		{
			np -> fa = q;
		}
		else
		{
			Sam *nt = ++cur;
			nt -> clear();
			nt -> val = p -> val + 1;
			memcpy(nt -> go, q -> go, sizeof q -> go);
			nt -> fa = q -> fa;
			q -> fa = nt;
			np -> fa = nt;
			while(p && p -> go[now] == q)p -> go[now] = nt, p = p -> fa;
		}
	}
	return np;
}

int main() {
	scanf("%s", s + 1);
	int n = strlen(s + 1);
	for(int i = 0; i < 10; i++)
		pos[i] = n + 1;
	for(int i = n; i; i--) {
		ne[i] = n + 1;
		for(int j = s[i] - 'a'; j < 10; j++)
			ne[i] = min(ne[i], pos[j]);
		pos[s[i] - 'a'] = i;
	}
	Prepare();
	a[n + 1] = last;
	for(int i = n; i; i--) {
		Sam *last = a[ne[i]];
		for(int j = ne[i] - 1; j >= i; j--) {
			last = Insert(last, s[i] - 'a');
		}
		a[i] = last;
	}
	long long ans = 0;
	for(Sam *now = cur; now > Pool; now--) {
		ans += now -> val - now -> fa -> val;
	}
	printf("%lld\n", ans);
}