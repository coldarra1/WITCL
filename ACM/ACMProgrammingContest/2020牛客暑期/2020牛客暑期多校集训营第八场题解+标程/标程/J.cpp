#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000010;
const double eps = 1e-6;
int L[MAXN], R[MAXN];
int n;
pair<int, int> staR[MAXN];
pair<int, int> staL[MAXN];

vector<pair<int, double>> gao(int st, int ed) {
	int L1 = L[1];
	int R1 = R[1];
	int Ln = L[n];
	int Rn = R[n];
	L[1] = R[1] = st;
	L[n] = R[n] = ed;
	vector<pair<int, double>> vec;
	vec.push_back(make_pair(1, (double)st));
	int now = 1;
	int cur = st;
	int front1 = 0, tail1 = 0;
	int front2 = 0, tail2 = 0;

	staR[front1++] = make_pair(1, st);
	staL[front2++] = make_pair(1, st);

	int nxt = 2;
	while (now < n) {

		int nnow = n;
		int ncur = L[n];
		while (nxt <= n) {
			if (front1 - tail1 > 1) {
				if ((long long)(staR[tail1+1].first - staR[tail1].first) * (L[nxt] - staR[tail1+1].second)
						- (long long)(nxt - staR[tail1+1].first) * (staR[tail1+1].second - staR[tail1].second) > 0) {
					// 位于上方，取上凸壳的点。
					nnow = staR[tail1+1].first;
					ncur = staR[tail1+1].second;
					tail1++;
					front2 = tail2 = 0;
					staL[front2++] = make_pair(nnow, ncur);
					break;
				}
			}
			if (front2 - tail2 > 1) {
				if ((long long)(staL[tail2+1].first - staL[tail2].first) * (R[nxt] - staL[tail2+1].second)
						- (long long)(nxt - staL[tail2+1].first) * (staL[tail2+1].second - staL[tail2].second) < 0) {
					// 位于下方，取下凸壳的点。
					nnow = staL[tail2+1].first;
					ncur = staL[tail2+1].second;
					tail2++;
					front1 = tail1 = 0;
					staR[front1++] = make_pair(nnow, ncur);
					break;
				}
			}

			while (front1 - tail1 > 1 &&
					(long long)(staR[front1-1].first - staR[front1-2].first) * (R[nxt] - staR[front1-1].second)
						- (long long) (nxt - staR[front1-1].first) * (staR[front1-1].second - staR[front1-2].second) <= 0
					) {
				front1--;
			}
			staR[front1++] = make_pair(nxt, R[nxt]);

			while (front2 - tail2 > 1 &&
					(long long)(staL[front2-1].first - staL[front2-2].first) * (L[nxt] - staL[front2-1].second)
					  - (long long) (nxt - staL[front2-1].first) * (staL[front2-1].second - staL[front2-2].second) >= 0
					) {
				front2--;
			}
			staL[front2++] = make_pair(nxt, L[nxt]);
			nxt++;
		}


		for (int i = now+1; i <= nnow; i++) {
			vec.push_back(make_pair(i, (double)(ncur - cur) / (nnow - now) * (i - now) + cur));
		}
		now = nnow;
		cur = ncur;
	}

	L[1] = L1; R[1] = R1;
	L[n] = Ln; R[n] = Rn;

	int mL = L[1];
	int mR = R[1];
	for (int i = 1; i <= n; i++) {
		mL = max(L[i], mL);
		mR = min(R[i], mR);
		if (vec[i-1].second < mL - eps || vec[i-1].second > mR + eps) {
			for (int j = i-2; j >= 0; j--)
				vec[j].second = vec[i-2].second;
			break;
		}
	}
	mL = L[n];
	mR = R[n];
	for (int i = n; i >= 1; i--) {
		mL = max(L[i], mL);
		mR = min(R[i], mR);
		if (vec[i-1].second < mL - eps || vec[i-1].second > mR + eps) {
			for (int j = i; j < n; j++)
				vec[j].second = vec[i].second;
			break;
		}
	}
	return vec;
}

double calc(vector<pair<int, double>> ret) {
	int sz = ret.size();
	double ans = 0;
	for (int i = 1; i < sz; i++) {
		ans += sqrt((ret[i].first - ret[i-1].first) * (ret[i].first - ret[i-1].first) 
			+ (ret[i].second - ret[i-1].second) * (ret[i].second - ret[i-1].second));
	}
	return ans;
}

int main() {
	int T;
	scanf("%d", &T);
	int iCase = 0;
	while (T--) {
		iCase++;
		scanf("%d", &n);
		int mL = 0, mR = 2000000000;
		for (int i = 1; i <= n; i++) {
			scanf("%d%d", &L[i], &R[i]);
			mL = max(mL, L[i]);
			mR = min(mR, R[i]);
		}
		printf("Case #%d:\n", iCase);
		if (mL <= mR) {
			for (int i = 1; i <= n; i++) {
				printf("%d %d\n", i, mL);
			}
			continue;
		}

		vector<pair<int, double>> ret1 = gao(R[1], R[n]);
		vector<pair<int, double>> ret2 = gao(L[1], R[n]);
		vector<pair<int, double>> ret3 = gao(L[1], L[n]);
		vector<pair<int, double>> ret4 = gao(R[1], L[n]);
		double tmp = calc(ret1);
		vector<pair<int, double>> ret = ret1;
		if (calc(ret2) < tmp) {
			tmp = calc(ret2);
			ret = ret2;
		}
		if (calc(ret3) < tmp) {
			tmp = calc(ret3);
			ret = ret3;
		}
		if (calc(ret4) < tmp) {
			tmp = calc(ret4);
			ret = ret4;
		}
		for (int i = 0; i < n; i++)
			printf("%d %.6f\n", ret[i].first, ret[i].second);
	}
	return 0;
}
