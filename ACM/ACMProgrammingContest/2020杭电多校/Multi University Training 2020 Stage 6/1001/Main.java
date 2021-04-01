import java.io.*;
import java.util.*;

public class Main {

	static final int MOD = 1000000007;
	static final int MAXN = 200005;

	static int [] inv = new int [MAXN];
	static int [] sinv = new int [MAXN];
	static int [] a = new int [MAXN];

	static long fpow(long a, long b) {
		a %= MOD;
		long r = 1;
		while (b != 0) {
			if (b % 2 == 1) r = (r * a) % MOD;
			a = (a * a) % MOD;
			b >>= 1;
		}
		return r;
	}

	static void init(int n) {
		inv[1] = 1;
		for (int i = 2; i <= n; i++)
			inv[i] = (int)((long)(MOD - MOD / i) * (long)inv[MOD % i] % (long)MOD);
		for (int i = 1; i <= n; i++)
			sinv[i] = (sinv[i - 1] + inv[i]) % MOD;
		return ;
	}

	static Scanner in = new Scanner(System.in);
	static PrintWriter out = new PrintWriter(System.out);

	static void Solve() throws Exception {
		int n = in.nextInt();
		int C = 0, ans = 0, hn = n >> 1;
		for (int i = 1; i <= n; i++) a[i] = in.nextInt();
		for (int i = 1; i <= hn; i++)
		{
			long cov = i;
			cov += (long)i * (long)(sinv[n - i] - sinv[i] + MOD) % MOD;
			cov %= MOD;
			C += (long)i * (long)inv[n - i + 1] % MOD;
			C %= MOD;
			cov = (cov + C) % MOD;
			ans += (long)a[i] * (long)cov % MOD;
			ans %= MOD;
			ans += (long)a[n + 1 - i] * (long)cov % MOD;
			ans %= MOD;
		}
		if (n % 2 == 1)
		{
			long cov = 0;
			for (int i = 1; i <= n; i++) {
				cov += (long)Math.min(i, n + 1 - i) * (long)inv[i] % MOD;
				cov %= MOD;
			}
			ans += (long)cov * (long)a[hn + 1] % MOD;
			ans %= MOD;
		}
		ans = (int)((long)ans * fpow((long)n * (long)(n + 1) / 2, (long)MOD - 2) % (long)MOD);
		out.println(ans);
		return ;
	}

	public static void main(String[] args) throws Exception {
		init(200000);
		int t = in.nextInt();
		for (int i = 0; i < t; i++)
			Solve();
		out.close();
	}

	static class Scanner {
		StringTokenizer st;
		BufferedReader br;

		public Scanner(InputStream s) {
			br = new BufferedReader(new InputStreamReader(s));
		}

		public String next() throws IOException {
			while (st == null || !st.hasMoreTokens())
				st = new StringTokenizer(br.readLine());
			return st.nextToken();
		}

		public int nextInt() throws IOException {
			return Integer.parseInt(next());
		}

		public long nextLong() throws IOException {
			return Long.parseLong(next());
		}

		public String nextLine() throws IOException {
			return br.readLine();
		}

		public boolean ready() throws IOException, IOException {
			return br.ready();
		}
	}
}