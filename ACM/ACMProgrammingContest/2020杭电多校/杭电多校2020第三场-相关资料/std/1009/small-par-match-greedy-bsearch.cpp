#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;

void solve() {
	static char buf[maxn], out[maxn];
	scanf("%s", buf);
	int n = strlen(buf), L = 0, R = 0, cnt[3] = {};
	for(int i = 0; i < n && R >= 0; ++i) {
		char ch = buf[i];
		if(ch == '(') {
			++L;
			++cnt[0];
		} else {
			(--L) < 0 && (L = 0);
		}
		if(ch == ')') {
			--R;
			++cnt[1];
		} else {
			++R;
		}
	}
	if(R < 0 || L > 0) {
		puts("No solution!");
		return;
	}
	for(int i = 0; i < n && cnt[0] < cnt[1]; ++i)
		if(buf[i] == '*') {
			buf[i] = '(';
			++cnt[0];
		}
	for(int i = n - 1; i >= 0 && cnt[0] > cnt[1]; --i)
		if(buf[i] == '*') {
			buf[i] = ')';
			++cnt[1];
		}
	int cL = 0, cR = (n - cnt[0] - cnt[1]) >> 1;
	while(cL < cR) {
		int cM = (cL + cR) >> 1;
		strcpy(out, buf);
		for(int i = n - 1, suf = cM; i >= 0 && suf > 0; --i)
			if(out[i] == '*') {
				out[i] = ')';
				--suf;
			}
		int sgn = 0;
		for(int i = 0, pre = cM; i < n && sgn >= 0; ++i) {
			char ch = out[i];
			if(ch == '(') {
				++sgn;
			} else if(ch == ')') {
				--sgn;
			} else if(pre > 0) {
				--pre;
				++sgn;
			}
		}
		if(!sgn) {
			cR = cM;
		} else {
			cL = cM + 1;
		}
	}
	for(int i = n - 1, suf = cL; i >= 0 && suf > 0; --i)
		if(buf[i] == '*') {
			buf[i] = ')';
			--suf;
		}
	int m = 0;
	for(int i = 0, pre = cL; i < n; ++i)
		if(buf[i] != '*') {
			out[m++] = buf[i];
		} else if(pre > 0) {
			out[m++] = '(';
			--pre;
		}
	out[m] = '\0';
	puts(out);
}
int main() {
	int T;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		solve();
	}
	return 0;
}
