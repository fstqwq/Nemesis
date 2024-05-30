int bostan_mori(int k, poly a, poly b) {
	int n = (int)a.size(); while (k) { poly c = b;
		for (int i = 1; i < n; i += 2) c[i] = (p - c[i]) % p;
		a = poly_mul(a, c); b = poly_mul(b, c);
		for (int i = 0; i < n; i++) {
			a[i] = a[i * 2 + k % 2]; b[i] = b[i * 2]; }
		a.resize(n); b.resize(n); k /= 2; }
	return (LL)a[0] * qpow(b[0], p - 2) % p; }
// $a_n = \sum_{i = 1} ^ m f_i a_{n - i}\quad (f_0 = 0)$, f.size() = a.size() + 1
int linear_recurrance(int n, poly f, poly a) {
	int m = (int)a.size(), ntt_n = 1;
	while (ntt_n <= m) ntt_n *= 2; ntt_init(ntt_n * 2);
	f.resize(ntt_n); a.resize(ntt_n); f[0] = 1;
	for (int i = 1; i <= m; i++) f[i] = (p - f[i]) % p;
	a = poly_mul(a, f); a.resize(ntt_n);
	fill(a.data() + m, a.data() + ntt_n, 0);
	return bostan_mori(n, a, f); }
