poly poly_auto_mul(poly a, poly b) { // 自动判断长度的乘法
	int res_len = (int)a.size() + (int)b.size() - 1;
	int ntt_n = 1; while (ntt_n < res_len) ntt_n *= 2;
	a.resize(ntt_n); b.resize(ntt_n);
	ntt(a.data(), ntt_n, 1); ntt(b.data(), ntt_n, 1);
	for (int i = 0; i < ntt_n; i++)
		a[i] = (LL)a[i] * b[i] % p;
	ntt(a.data(), ntt_n, -1); a.resize(res_len); return a; }
// 多项式除法，a 和 b 长度可以任意
// 商的长度是 n - m + 1，余数的长度是 m - 1
poly poly_div(const poly& a, const poly& b) {
	int n = (int)a.size(), m = (int)b.size();
	if (n < m) return {};
	int ntt_n = 1; while (ntt_n < n - m + 1) ntt_n *= 2;
	poly f(ntt_n), g(ntt_n);
	for (int i = 0; i < n - m + 1; i++) f[i] = a[n - i - 1];
	for (int i = 0; i < m && i < n - m + 1; i++)
		g[i] = b[m - i - 1];
	auto g_inv = poly_inv(g);
	fill(g_inv.begin() + n - m + 1, g_inv.end(), 0);
	auto c = poly_mul(f, g_inv); c.resize(n - m + 1);
	reverse(c.begin(), c.end()); return c; }
// 多项式取模，a 和 b 长度可以任意，返回 (余数，商)
pair<poly, poly> poly_mod(const poly& a, const poly& b) {
	int n = (int)a.size(), m = (int)b.size();
	if (n < m) return {a, {}};
	auto d = poly_div(a, b); auto c = poly_auto_mul(b, d);
	poly r(m - 1);
	for (int i = 0; i < m - 1; i++)
		r[i] = (a[i] - c[i] + p) % p;
	return {r, d}; }
