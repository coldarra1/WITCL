#include<bits/stdc++.h>

using namespace std;
const int MAX_N = 202020;

int fd(int N, int* A, int M, int* B, int K)
{
	if(N==0||M==0)
		return 1<<K;
	if(K==0)
		return 0;
	int X=std::lower_bound(A, A+N, ((A[0]>>K-1)|1)<<K-1)-A;
	int Y=std::lower_bound(B, B+M, ((B[0]>>K-1)|1)<<K-1)-B;
	if(X==0 && Y==M || X==N && Y==0)
		return fd(N, A, M, B, K-1) + (1<<(K-1));
	return std::min(fd(X, A, Y, B, K-1), fd(N-X, A+X, M-Y, B+Y, K-1));
}
long long solve(int N, int* A, int K)
{
	if(N == 1)
		return 0;
	int X = lower_bound(A, A+N, ((A[0] >> (K-1))|1) << (K-1)) - A;
	if(X==0 || X==N)
		return solve(N, A, K-1);
	return (1ll << (K-1)) + fd(X, A, N-X, A+X, K-1) + solve(X, A, K-1)+solve(N-X, A+X, K-1);
}

struct Edge{
	int to, va;
};

vector<Edge> G[MAX_N];

int N, A[MAX_N];

bool vis[MAX_N];

void dfs(int x)
{
	vis[x] = 1;
	for(Edge e: G[x])
	if(!vis[e.to])
	{
		A[e.to] = A[x] ^ e.va;
		dfs(e.to);
	}
}

int main()
{
	scanf("%d", &N);
	for(int i = 1; i < N; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		G[u].push_back({v, w});
		G[v].push_back({u, w});
	}
	A[0] = 0;
	
	
	dfs(0);
	std::sort(A, A+N);
	N = std::unique(A, A+N) - A;
	printf("%lld\n", solve(N, A, 30));
	return 0;
}