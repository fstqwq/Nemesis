void dft(cp* a, cp* b, int n) { static cp c[MAXN];
	for (int i = 0; i < n; i++)
		c[i] = cp(a[i].real(), b[i].real());
	fft(c, n, 1);
	for (int i = 0; i < n; i++) { int j = (n - i) & (n - 1);
		a[i] = (c[i] + conj(c[j])) * 0.5;
		b[i] = (c[i] - conj(c[j])) * -0.5i; } }
void idft(cp* a, cp* b, int n) { static cp c[MAXN];
	for (int i = 0; i < n; i++) c[i] = a[i] + 1i * b[i];
	fft(c, n, -1);
	for (int i = 0; i < n; i++) {
		a[i] = c[i].real(); b[i] = c[i].imag(); } }
vector<int> multiply(const vector<int>& u,
		const vector<int>& v, int mod) { // 任意模数卷积
	static cp a[2][MAXN], b[2][MAXN], c[3][MAXN];
	int base = ceil(sqrt(mod));
	int n = (int)u.size(), m = (int)v.size();
	int fft_n = 1; while (fft_n < n + m - 1) fft_n *= 2;
	for (int i = 0; i < 2; i++) {
		fill(a[i], a[i] + fft_n, 0);
		fill(b[i], b[i] + fft_n, 0); }
	for (int i = 0; i < 3; i++)
		fill(c[i], c[i] + fft_n, 0);
	for (int i = 0; i < n; i++) { // 一定要取模！
		a[0][i] = (u[i] % mod) % base;
		a[1][i] = (u[i] % mod) / base; }
	for (int i = 0; i < m; i++) { // 一定要取模！
		b[0][i] = (v[i] % mod) % base;
		b[1][i] = (v[i] % mod) / base; }
	dft(a[0], a[1], fft_n); dft(b[0], b[1], fft_n);
	for (int i = 0; i < fft_n; i++) {
		c[0][i] = a[0][i] * b[0][i];
		c[1][i] = a[0][i] * b[1][i] + a[1][i] * b[0][i];
		c[2][i] = a[1][i] * b[1][i]; }
	fft(c[1], fft_n, -1); idft(c[0], c[2], fft_n);
	int base2 = base * base % mod;
	vector<int> ans(n + m - 1);
	for (int i = 0; i < n + m - 1; i++)
		ans[i] = ((LL)(c[0][i].real() + 0.5) +
			(LL)(c[1][i].real() + 0.5) % mod * base +
			(LL)(c[2][i].real() + 0.5) % mod * base2) % mod;
	return ans; }
