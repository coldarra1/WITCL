#include<bits/stdc++.h>
#define N 500005
using namespace std;

int son[N * 10][10], tot = 1;
int pos[N * 10], trie[N * 10];


int st, ed, size;
int data[N], L[N], R[N];
void Erase(int x){
	int pre = L[x], succ = R[x];
	if (pre) R[pre] = succ;
	if (succ) L[succ] = pre;
	data[x] = L[x] = R[x] = 0;
	if (x == st) st = succ;
	if (x == ed) ed = pre;
	--size;
}

void Insert(int x, int v){
	data[x] = v;
	if (!st) st = ed = x;
	else L[R[ed] = x] = ed, ed = x;
	++size;
}

void trieInsert(char *s, int it){
	assert(strlen(s) <= 10);
	int p = 1;
	for (int i = 0; s[i]; i++){
		assert(s[i] >= '0' && s[i] <= '9');
		int &t = son[p][s[i] - '0'];
		if (!t) pos[t = ++tot] = 0; p = t;
	}
	pos[trie[it] = p] = it;
}

int trieFind(char *s){
	assert(strlen(s) <= 10);
	int p = 1;
	for (int i = 0; s[i] && p; i++){
		assert(s[i] >= '0' && s[i] <= '9');
		p = son[p][s[i] - '0'];
	}
	return pos[p];
}

int main(){
	//freopen("lru3.in","r",stdin);
	//freopen("lru3.out","w",stdout);
	int T, Case = 0, sumQ = 0;
	scanf("%d", &T);
	while (T--){
		int Q, m;
		scanf("%d %d", &Q, &m);
		sumQ += Q;
		assert(1 <= Q && Q <= 500000);
		assert(1 <= m && m <= 500000);
		st = ed = size = 0;
		pos[tot = 1] = 0;
		int number = 0;
		fprintf(stderr, "%d\n", Q); 
		while (Q--){
			//if (Q % 10000 == 0) fprintf(stderr, "%d\n", Q);
			int opt, v; char s[12];
			scanf("%d %s %d", &opt, s, &v);
			int it = trieFind(s);
			if (opt == 1){
				assert(v == -1 || v == 0 || v == 1);
				if (it == 0 || v == -1 && L[it] == 0 || v == 1 && R[it] == 0)
					puts("Invalid");
				else{
					if (v == -1) it = L[it];
					if (v == 1) it = R[it];
					printf("%d\n", data[it]);
				}
			}
			else {
				if (it)
					v = data[it], Erase(it);
				else if (size == m)
					pos[trie[st]] = 0, Erase(st);
				Insert(++number, v);
				trieInsert(s, number);
				printf("%d\n", v);
			}
		}
		for (int i = 1; i <= tot; i++){
			for (int k = 0; k < 10; k++) son[i][k] = 0;
			pos[i] = 0;
		}
		while (st) Erase(st);
	}
	assert(1 <= sumQ <= 1000000);
}