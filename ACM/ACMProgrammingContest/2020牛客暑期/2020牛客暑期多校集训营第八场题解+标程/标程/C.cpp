#include <bits/stdc++.h>
using namespace std;

const int MAXM = 16;
int bit[MAXM];
const int MAXN = 6600;
int states[MAXN];
int idOfState[13000000];
int totStates;
void dfs(int pos, int now, int m) {
	if (pos == m) {
		if (pos >= 2 && (now%3 == 1) && (now/3%3 == 1) && (pos-2 < 0 || now/9%3 != 2)) {
			return;
		}
		idOfState[now] = totStates;
		states[totStates++] = now;
		return;
	}
	if (pos == 0) {
		dfs(pos+1, now*3 + 0, m);
		dfs(pos+1, now*3 + 1, m);
		dfs(pos+1, now*3 + 2, m);
		return;
	}
	if (now%3 == 2) {
		dfs(pos+1, now*3 + 1, m);
		return;
	}
	if (now%3 == 0) {
		dfs(pos+1, now*3 + 1, m);
		return;
	}
	// 1->2
	dfs(pos+1, now*3+2, m);

	if (pos >= 2 && (now%3 == 1) && (now/3%3 == 1) && (pos-2 < 0 || now/9%3 != 2)) {
		// No 0 or 1.
	} else {
		dfs(pos+1, now*3+0, m);
		dfs(pos+1, now*3+1, m);
	}
}

int getState(int a[], int m) {
	int ret = 0;
	for (int i = m-1; i >= 0; i--) {
		ret = ret*3 + a[i];
	}
	return ret;
}

void output(int s, int m) {
	for (int i = 0; i < m; i++) {
		printf("%d", s%3);
		s /= 3;
	}
}

void searchNextStates(vector<int> &res, int a[], int m, int now, int pos) {
	if (pos >= m) {
		res.push_back(now);
		return;
	}
	if (a[pos] == 2) {
		searchNextStates(res, a, m, now*3 + 1, pos+1);
	} else if (a[pos] == 0) {
		if (pos+1 < m) {
			searchNextStates(res, a, m, (now*3 + 2)*3 + 1, pos+2);
		} else {
			searchNextStates(res, a, m, now*3 + 2, pos+1);
		}
	} else {
		if (pos+1 < m) {
			if (a[pos+1] == 0) {
				searchNextStates(res, a, m, now*3 + 1, pos+1);
			} else if (a[pos+1] == 2) {
				searchNextStates(res, a, m, now*3, pos+1);
				searchNextStates(res, a, m, now*3 + 2, pos+1);
			} else {
				if (pos+2 >= m || a[pos+2] == 2) {
					searchNextStates(res, a, m, (now*3 + 2)*3 + 1, pos+2);
					searchNextStates(res, a, m, (now*3 + 1)*3 + 2, pos+2);
				} else if (a[pos+2] == 0) {
					searchNextStates(res, a, m, (now*3 + 0)*3 + 1, pos+2);
					// example: 15*10
					searchNextStates(res, a, m, (now*3 + 2)*3 + 1, pos+2);
				} else {
					if (pos + 3 >= m || a[pos+3] == 2) {
						searchNextStates(res, a, m, (now*3 + 2)*3 + 1, pos+2);
						searchNextStates(res, a, m, ((now*3 + 0)*3 + 1)*3 + 2, pos+3);
						searchNextStates(res, a, m, ((now*3 + 1)*3 + 2)*3 + 1, pos+3);
					}
				}
			}
		} else {
			searchNextStates(res, a, m, now*3, pos+1);
			searchNextStates(res, a, m, now*3 + 2, pos+1);
		}
	}
}


int get2(int s) {
	int ret = 0;
	while (s) {
		if (s%3 == 2) ret++;
		s /= 3;
	}
	return ret;
}
int get0(int s, int m) {
	int ret = 0;
	for (int i = 0; i < m; i++) {
		if (s%3 == 0) ret++;
		s /= 3;
	}
	return ret;
}


bool isValidStateForFirstRow(int s, int m) {
	int a[MAXM];
	for (int i = 0; i < m; i++) {
		a[i] = s%3;
		s /= 3;
	}
	for (int i = 0; i < m; i++) {
		if (a[i] == 1 && (i == 0 || a[i-1] != 2) && (i == m-1 || a[i+1] != 2))
			return false;
	}
	return true;
}

vector<int> nextStates[MAXN];
int dp[1001][MAXN];
int pre[1001][MAXN];
int num2[MAXN];
int num0[MAXN];
int a[MAXM];

int queryAns[1001];
vector<int> querySol[1001];

void gao(vector<pair<int, int>> query, int m) {
	int qsize = query.size();
	if (qsize == 0) return;
	sort(query.begin(), query.end());
	totStates = 0;
	dfs(0, 0, m);
	for (int i = 0; i < totStates; i++) {
		num2[i] = get2(states[i]);
		num0[i] = get0(states[i], m);

		nextStates[i].clear();
		int ts = states[i];
		for (int j = m-1; j >= 0; j--) {
			a[j] = ts%3;
			ts /= 3;
		}
		searchNextStates(nextStates[i], a, m, 0, 0);
	}
	
	memset(dp, -1, sizeof(dp));

	for (int i = 0; i < totStates; i++) {
		if (isValidStateForFirstRow(states[i], m)) {
			dp[1][i] = num2[i];
		}
	}
	int qid = 0;
	for (int i = 1; i <= 1000; i++) {
		while (qid < qsize && query[qid].first == i) {
			int qIndex = query[qid].second;
			queryAns[qIndex] = i * m;
			querySol[qIndex].clear();
			int tmp = -1;
			for (int j = 0; j < totStates; j++) {
				if (dp[i][j] != -1 && queryAns[qIndex] > dp[i][j] + num0[j]) {
					tmp = j;
					queryAns[qIndex] = dp[i][j] + num0[j];
				}
			}
			querySol[qIndex].push_back(states[tmp]);
			for (int j = i; j > 1; j--) {
				tmp = pre[j][tmp];
				querySol[qIndex].push_back(states[tmp]);
			}
			qid++;
		}

		if (qid == qsize) break;

		for (int j = 0; j < totStates; j++) {
			if (dp[i][j] == -1) {
			 	continue;
			}
			int sz = nextStates[j].size();
			for (int k = 0; k < sz; k++) {
				int ns = nextStates[j][k];
				int id = idOfState[ns];
				if (dp[i+1][id] == -1 || dp[i+1][id] > dp[i][j] + num2[id]) {
					dp[i+1][id] = dp[i][j] + num2[id];
					pre[i+1][id] = j;
				}
			}
		}
	}
}

vector<pair<int, int>> queries[16];
int qm[1001];

void outputSol(vector<int> vec, int m) {
	int sz = vec.size();
	for (int i = sz-1; i >= 0; i--) {
		int s = vec[i];
		for (int j = 0; j < m; j++) {
			int bs = s%3;
			s /= 3;
			if (bs == 2) printf("*");
			else if (i == 0 && bs == 0) printf("*");
			else printf(".");
		}
		printf("\n");
	}
}

int main() {
	bit[0] = 1;
	for (int i = 1; i < MAXM; i++)
		bit[i] = bit[i-1] * 2;


	int T;
	scanf("%d", &T);
	for (int i = 1; i <= 15; i++)
		queries[i].clear();
	for (int i = 0; i < T; i++) {
		int n, m;
		scanf("%d%d", &n, &m);
		queries[m].push_back(make_pair(n, i));
		qm[i] = m;
	}
	for (int i = 1; i <= 15; i++) {
		gao(queries[i], i);
	}
	for (int i = 0; i < T; i++) {
		printf("Case #%d: %d\n", i+1, queryAns[i]);
		outputSol(querySol[i], qm[i]);
	}
	return 0;
}
