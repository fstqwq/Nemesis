poly poly_power_mod(LL k, const poly& m) { // x^k mod m
	poly ans{1}, a{0, 1}; while (k) { if (k & 1)
			ans = poly_mod(poly_auto_mul(ans, a), m).first;
		a = poly_mod(poly_auto_mul(a, a), m).first; k /= 2; }
	return ans; }
// $a_n = \sum_{i = 1} ^ m c_i a_{n - i}\quad (c_0 = 0)$
struct linear_recurrence { poly f; // f是预处理结果
	linear_recurrence(const poly& c, LL n) {
		assert(c[0] == 0); // c[0] 是没有用的
		int m = (int)c.size() - 1;
		int ntt_n = 1; while (ntt_n < m * 2) ntt_n *= 2;
		ntt_init(ntt_n); // 图省事就直接 ntt_init(1 << 18)
		poly t(m + 1); t[m] = 1;
		for (int i = 0; i < m; i++)t[i] = (p - c[m - i]) % p;
		f = poly_power_mod(n, t); }
	int operator()(const vector<int>& a) { // 0~m-1项初始值
		assert(a.size() == f.size()); int ans = 0;
		for (int i = 0; i < (int)a.size(); i++)
			ans = (ans + (LL)f[i] * a[i]) % p;
		return ans; } };
