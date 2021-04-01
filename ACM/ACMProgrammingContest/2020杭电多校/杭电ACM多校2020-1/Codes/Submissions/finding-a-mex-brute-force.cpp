#include <bits/stdc++.h>
using namespace std;

class FastInput
{
private:
	static const int bufsz = 1 << 16;

	class FastInputBuffer
	{
	public:
		int isz;
		char ibuf[bufsz];
	};

	stack<FastInputBuffer> ibuf_stk;
	int ipt, isz;
	char ibuf[bufsz];
	char word[64];

	void stack_buffer(void);
	void next_buffer(void);
	void trim(void);

	bool integral(void);
	bool real(void);

public:
	FastInput(void);

	operator bool (void);
	
	bool eof(void);

	void putback(const char &);

	FastInput & operator >> (char &);
	FastInput & operator >> (char *);
	FastInput & operator >> (int &);
	FastInput & operator >> (unsigned int &);
	FastInput & operator >> (long long &);
	FastInput & operator >> (unsigned long long &);
	FastInput & operator >> (float &);
	FastInput & operator >> (double &);
	FastInput & operator >> (long double &);
} fin, fin_null;

inline void FastInput::stack_buffer(void)
{
	if (ipt == 0)
	{
		ibuf_stk.push(FastInputBuffer());
		ibuf_stk.top().isz = isz;
		memcpy(ibuf_stk.top().ibuf, ibuf, sizeof ibuf[0] * isz);
		isz = bufsz;
		ipt = isz;
	}
}

inline void FastInput::next_buffer(void)
{
	if (ibuf_stk.empty())
		isz = fread(ibuf, 1, bufsz, stdin);
	else
	{
		isz = ibuf_stk.top().isz;
		memcpy(ibuf, ibuf_stk.top().ibuf, sizeof ibuf[0] * isz);
		ibuf_stk.pop();
	}
	ipt = 0;
}

inline void FastInput::trim(void)
{
	for (; isz > 0; )
	{
		for (; ipt < isz && ibuf[ipt] <= ' '; ++ipt);
		if (ipt < isz)
			break;
		next_buffer();
	}
}

inline bool FastInput::integral(void)
{
	if (eof())
		return false;

	int len = 0;
	bool vld = false;
	if (ibuf[ipt] == '-')
		word[len++] = ibuf[ipt++];
	for (; isz > 0; )
	{
		for (; ipt < isz && isdigit(ibuf[ipt]); ++ipt)
		{
			word[len++] = ibuf[ipt];
			vld = true;
		}
		if (ipt < isz)
			break;
		next_buffer();
	}
	word[len] = '\0';

	return vld;
}

inline bool FastInput::real(void)
{
	if (eof())
		return false;

	int len = 0;
	bool vld = false, rht = false;
	if (ibuf[ipt] == '-')
		word[len++] = ibuf[ipt++];
	for (; isz > 0; )
	{
		for (; ipt < isz && (isdigit(ibuf[ipt]) || ibuf[ipt] == '.'); ++ipt)
		{
			if (ibuf[ipt] == '.')
			{
				if (rht)
					break;
				else
					rht = true;
			}
			else
				vld = true;
			word[len++] = ibuf[ipt];
		}
		if (ipt < isz)
			break;
		next_buffer();
	}
	word[len] = '\0';

	return vld;
}

FastInput::FastInput(void) : ipt(bufsz), isz(bufsz)
{

}

inline FastInput::operator bool (void)
{
	return this != &fin_null;
}

inline bool FastInput::eof(void)
{
	trim();

	return isz == 0;
}

inline void FastInput::putback(const char &c)
{
	if (ipt == 0)
		stack_buffer();
	ibuf[--ipt] = c;
}

inline FastInput & FastInput::operator >> (char &c)
{
	if (this == &fin_null || eof())
		return fin_null;
	else
	{
		c = ibuf[ipt++];

		return *this;
	}
}

inline FastInput & FastInput::operator >> (char *s)
{
	if (this == &fin_null || eof())
		return fin_null;

	int slen = 0;
	for (; isz > 0; )
	{
		for (; ipt < isz && ibuf[ipt] > ' '; ++ipt)
			s[slen++] = ibuf[ipt];
		if (ipt < isz)
			break;
		if (ibuf_stk.empty())
			isz = fread(ibuf, 1, bufsz, stdin);
		else
		{
			isz = ibuf_stk.top().isz;
			memcpy(ibuf, ibuf_stk.top().ibuf, sizeof ibuf[0] * isz);
			ibuf_stk.pop();
		}
		ipt = 0;
	}
	s[slen] = '\0';

	return *this;
}

inline FastInput & FastInput::operator >> (int &x)
{
	if (this == &fin_null || !(this->integral()))
		return fin_null;

	int i = 0, sgn;
	int ans = 0;
	if (word[0] == '-')
		sgn = -1, ++i;
	else
		sgn = 1;
	for (; word[i]; ++i)
		ans = ans * 10 + word[i] - '0';
	x = ans * sgn;

	return *this;
}

inline FastInput & FastInput::operator >> (unsigned int &x)
{
	if (this == &fin_null || !(this->integral()))
		return fin_null;

	int i = 0, sgn;
	int ans = 0;
	if (word[0] == '-')
		sgn = -1, ++i;
	else
		sgn = 1;
	for (; word[i]; ++i)
		ans = ans * 10 + word[i] - '0';
	x = ans * sgn;

	return *this;
}

inline FastInput & FastInput::operator >> (long long &x)
{
	if (this == &fin_null || !(this->integral()))
		return fin_null;

	int i = 0, sgn;
	long long ans = 0;
	if (word[0] == '-')
		sgn = -1, ++i;
	else
		sgn = 1;
	for (; word[i]; ++i)
		ans = ans * 10 + word[i] - '0';
	x = ans * sgn;

	return *this;
}

inline FastInput & FastInput::operator >> (unsigned long long &x)
{
	if (this == &fin_null || !(this->integral()))
		return fin_null;

	int i = 0, sgn;
	long long ans = 0;
	if (word[0] == '-')
		sgn = -1, ++i;
	else
		sgn = 1;
	for (; word[i]; ++i)
		ans = ans * 10 + word[i] - '0';
	x = ans * sgn;

	return *this;
}

inline FastInput & FastInput::operator >> (float &x)
{
	if (this == &fin_null || !(this->real()))
		return fin_null;

	int i = 0, sgn;
	bool vis = false;
	float ans = 0, factor = 1;
	if (word[0] == '-')
		sgn = -1, ++i;
	else
		sgn = 1;
	for (; word[i]; ++i)
	{
		if (word[i] == '.')
		{
			vis = true;
			continue;
		}

		if (!vis)
			ans = ans * 10 + word[i] - '0';
		else
		{
			factor /= 10;
			ans += factor * (word[i] - '0');
		}
	}
	x = ans * sgn;

	return *this;
}

inline FastInput & FastInput::operator >> (double &x)
{
	if (this == &fin_null || !(this->real()))
		return fin_null;

	int i = 0, sgn;
	bool vis = false;
	double ans = 0, factor = 1;
	if (word[0] == '-')
		sgn = -1, ++i;
	else
		sgn = 1;
	for (; word[i]; ++i)
	{
		if (word[i] == '.')
		{
			vis = true;
			continue;
		}

		if (!vis)
			ans = ans * 10 + word[i] - '0';
		else
		{
			factor /= 10;
			ans += factor * (word[i] - '0');
		}
	}
	x = ans * sgn;

	return *this;
}

inline FastInput & FastInput::operator >> (long double &x)
{
	if (this == &fin_null || !(this->real()))
		return fin_null;

	int i = 0, sgn;
	bool vis = false;
	long double ans = 0, factor = 1;
	if (word[0] == '-')
		sgn = -1, ++i;
	else
		sgn = 1;
	for (; word[i]; ++i)
	{
		if (word[i] == '.')
		{
			vis = true;
			continue;
		}

		if (!vis)
			ans = ans * 10 + word[i] - '0';
		else
		{
			factor /= 10;
			ans += factor * (word[i] - '0');
		}
	}
	x = ans * sgn;

	return *this;
}

class FastOutput
{
private:
	static const int bufsz = 1 << 16;
	int opt;
	char obuf[bufsz];
	char word[64];
	int pcs;
	string format_float, format_double, format_long_double;

public:
	class FastOutputPrecision
	{
	public:
		int pcs;

		FastOutputPrecision(void) : pcs(0)
		{

		}

		FastOutputPrecision(const int &pcs) : pcs(pcs)
		{

		}
	};

	FastOutput(void);
	~FastOutput(void);

	void precision(const int &);
	FastOutput & operator << (const FastOutputPrecision &);

	FastOutput & operator << (const char &);
	FastOutput & operator << (const char *);
	FastOutput & operator << (const int &);
	FastOutput & operator << (const unsigned int &);
	FastOutput & operator << (const long long &);
	FastOutput & operator << (const unsigned long long &);
	FastOutput & operator << (const float &);
	FastOutput & operator << (const double &);
	FastOutput & operator << (const long double &);

	void flush(void);
} fout;

const char fendl = '\n';

FastOutput::FastOutput(void) : opt(0), pcs(3), format_float("%.3f"), format_double("%.3lf"), format_long_double("%.3Lf")
{

}

FastOutput::~FastOutput(void)
{
	flush();
}

inline void FastOutput::precision(const int &x)
{
	pcs = x;
	sprintf(word, "%%.%d", pcs);
	(format_float = word) += "f";
	(format_double = word) += "lf";
	(format_long_double = word) += "Lf";
}

inline FastOutput & FastOutput::operator << (const FastOutputPrecision &rhs)
{
	precision(rhs.pcs);

	return *this;
}

inline FastOutput & FastOutput::operator << (const char &c)
{
	obuf[opt++] = c;
	if (opt == bufsz)
		flush();

	return *this;
}

inline FastOutput & FastOutput::operator << (const char *s)
{
	for (int i = 0; s[i]; ++i)
	{
		obuf[opt++] = s[i];
		if (opt == bufsz)
			flush();
	}

	return *this;
}

inline FastOutput & FastOutput::operator << (const int &x)
{
	int len = 0;
	unsigned int y;
	if (x < 0)
		word[len++] = '-', y = -x;
	else
		y = x;
	if (y == 0)
		word[len++] = '0';
	else
	{
		for (; y > 0; y /= 10)
			word[len++] = '0' + y % 10;
	}
	reverse(word + (x < 0 ? 1 : 0), word + len);
	word[len] = '\0';

	*this << word;

	return *this;
}

inline FastOutput & FastOutput::operator << (const unsigned int &x)
{
	int len = 0;
	if (x == 0)
		word[len++] = '0';
	else
	{
		for (unsigned int y = x; y > 0; y /= 10)
			word[len++] = '0' + y % 10;
	}
	reverse(word, word + len);
	word[len] = '\0';

	*this << word;

	return *this;
}

inline FastOutput & FastOutput::operator << (const long long &x)
{
	int len = 0;
	unsigned long long y;
	if (x < 0)
		word[len++] = '-', y = -x;
	else
		y = x;
	if (y == 0)
		word[len++] = '0';
	else
	{
		for (; y > 0; y /= 10)
			word[len++] = '0' + y % 10;
	}
	reverse(word + (x < 0 ? 1 : 0), word + len);
	word[len] = '\0';

	*this << word;

	return *this;
}

inline FastOutput & FastOutput::operator << (const unsigned long long &x)
{
	int len = 0;
	if (x == 0)
		word[len++] = '0';
	else
	{
		for (unsigned long long y = x; y > 0; y /= 10)
			word[len++] = '0' + y % 10;
	}
	reverse(word, word + len);
	word[len] = '\0';

	*this << word;

	return *this;
}

inline FastOutput & FastOutput::operator << (const float &x)
{
	sprintf(word, format_float.c_str(), x);
	*this << word;

	return *this;
}

inline FastOutput & FastOutput::operator << (const double &x)
{
	sprintf(word, format_double.c_str(), x);
	*this << word;

	return *this;
}

inline FastOutput & FastOutput::operator << (const long double &x)
{
	sprintf(word, format_long_double.c_str(), x);
	*this << word;

	return *this;
}

inline void FastOutput::flush(void)
{
	if (opt > 0)
	{
		fwrite(obuf, 1, opt, stdout);
		opt = 0;
	}
}

inline FastOutput::FastOutputPrecision fsetprecision(const int &x)
{
	return FastOutput::FastOutputPrecision(x);
}

#define MX 100050
int a[MX];
bool flag[MX];
vector<int> g[MX];

int main() {
	int tc;
	fin >> tc;
	while(tc--) {
		int n, m;
		fin >> n >> m;
		for(int i = 1; i <= n; i++) {
			fin >> a[i];
		}
		for(int i = 1; i <= n; i++) g[i].clear();
		while(m--) {
			int u, v;
			fin >> u >> v;
			g[u].push_back(v);
			g[v].push_back(u);
		}
		for(int i = 1; i <= n; i++)
			if(a[i] > n) a[i] = n;
		int q;
		fin >> q;
		while(q--) {
			int type;
			fin >> type;
			if(type == 1) {
				int u, k;
				fin >> u >> k;
				if(k > n) k = n;
				a[u] = k;
			}
			else {
				int u;
				fin >> u;
				int sz = g[u].size();
				memset(flag, 0, sz + 1);
				for(auto v : g[u]) flag[a[v]] = true;
				for(int i = 0; i <= sz; i++)
					if(!flag[i]) {
						fout << i << '\n';
						break;
					}
			}
		}
	}
	return 0;
}
