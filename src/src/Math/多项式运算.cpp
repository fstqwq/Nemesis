void get_inv(int *a, int *c, int n) { // 求逆
	static int b[maxn];
	memset(c, 0, sizeof(int) * (n * 2));
	c[0] = qpow(a[0], p - 2);
	for (int k = 2; k <= n; k *= 2) {
		memcpy(b, a, sizeof(int) * k);
		memset(b + k, 0, sizeof(int) * k);
		NTT(b, k * 2, 1); NTT(c, k * 2, 1);
		for (int i = 0; i < k * 2; i++) {
			c[i] = (2-(long long)b[i]*c[i]) % p * c[i] % p;
			if (c[i] < 0) c[i] += p; }
		NTT(c, k * 2, -1);
		memset(c + k, 0, sizeof(int) * k); } }
void get_sqrt(int *a, int *c, int n) { // 开根
	static int b[maxn], d[maxn];
	memset(c, 0, sizeof(int) * (n * 2));
	c[0] = 1; // 如果不是1就要考虑二次剩余
	for (int k = 2; k <= n; k *= 2) {
		memcpy(b, a, sizeof(int) * k);
		memset(b + k, 0, sizeof(int) * k);
		get_inv(c, d, k);
		NTT(b, k * 2, 1); NTT(d, k * 2, 1);
		for (int i = 0; i < k * 2; i++)
			b[i] = (long long)b[i] * d[i] % p;
		NTT(b, k * 2, -1);
		for (int i = 0; i < k; i++)
			c[i] = (long long)(c[i] + b[i]) * inv_2 % p; } }
void get_derivative(int *a, int *c, int n) { // 求导
	for (int i = 1; i < n; i++)
		c[i - 1] = (long long)a[i] * i % p;
	c[n - 1] = 0; }
void get_integrate(int *a, int *c, int n) { // 不定积分
	for (int i = 1; i < n; i++)
		c[i] = (long long)a[i - 1] * qpow(i, p - 2) % p;
	c[0] = 0; } // 不定积分没有常数项
void get_ln(int *a, int *c, int n) { // 通常A常数项都是1
	static int b[maxn];
	get_derivative(a, b, n);
	memset(b + n, 0, sizeof(int) * n);
	get_inv(a, c, n);
	NTT(b, n * 2, 1); NTT(c, n * 2, 1);
	for (int i = 0;i < n * 2; i++)
		b[i] = (long long)b[i] * c[i] % p;
	NTT(b, n * 2, -1);
	get_integrate(b, c, n);
	memset(c + n, 0, sizeof(int) * n); }
// 多项式exp可以替换成分治FFT，依据: 设$G(x) = \exp F(x)$，
// 则有 $g_i = \sum_{k=1}^{i-1} f_{i-k} * k * g_k$
void get_exp(int *a, int *c, int n) { // 要求A没有常数项
	static int b[maxn];
	memset(c, 0, sizeof(int) * (n * 2));
	c[0] = 1;
	for (int k = 2; k <= n; k *= 2) {
		get_ln(c, b, k);
		for (int i = 0; i < k; i++) {
			b[i] = a[i] - b[i]; if (b[i] < 0) b[i] += p; }
		(++b[0]) %= p;
		NTT(b, k * 2, 1); NTT(c, k * 2, 1);
		for (int i = 0; i < k * 2; i++)
			c[i] = (long long)c[i] * b[i] % p;
		NTT(c, k * 2, -1);
		memset(c + k, 0, sizeof(int) * k); } }
void get_pow(int *a, int *c, int n, int k) {
	static int b[maxn]; // A常数项不为1时需要转化
	get_ln(a, b, n);
	for (int i = 0; i < n; i++) b[i] = (long long)b[i]*k%p;
	get_exp(b, c, n); }
// 多项式除法, a / b, 结果输出在C
// A的次数为n, B的次数为m
void get_div(int *a, int *b, int *c, int n, int m) {
	static int f[maxn], g[maxn], gi[maxn];
	if (n < m) { memset(c, 0, sizeof(int) * m); return; }
	int N = 1; while (N < (n - m + 1)) N *= 2;
	memset(f, 0, sizeof(int) * N * 2);
	memset(g, 0, sizeof(int) * N * 2);
	// memset(gi, 0, sizeof(int) * N);
	for (int i = 0; i < n - m + 1; i++)
		f[i] = a[n - i - 1];
	for (int i = 0; i < m && i < n - m + 1; i++)
		g[i] = b[m - i - 1];
	get_inv(g, gi, N);
	for (int i = n - m + 1; i < N; i++) gi[i] = 0;
	NTT(f, N * 2, 1); NTT(gi, N * 2, 1);
	for (int i = 0; i < N * 2; i++)
		f[i] = (long long)f[i] * gi[i] % p;
	NTT(f, N * 2, -1);
	for (int i = 0; i < n - m + 1; i++)
		c[i] = f[n - m - i]; }
// 多项式取模, 余数输出到c, 商输出到d
void get_mod(int *a, int *b, int *c, int *d, int n, int m){
	static int u[maxn], v[maxn];
	if (n < m) { memcpy(c, a, sizeof(int) * n);
		if (d) memset(d, 0, sizeof(int) * m); return; }
	get_div(a, b, v, n, m); // d是商, 可以选择不要
	if (d){for (int i = 0; i < n - m + 1; i++) d[i] = v[i];}
	int N = 1; while (N < n) N *= 2;
	memcpy(u, b, sizeof(int) * m);
	NTT(u, N, 1); NTT(v, N, 1);
	for (int i = 0; i < N; i++)
		u[i] = (long long)v[i] * u[i] % p;
	NTT(u, N, -1);
	for (int i = 0; i < m - 1; i++)
		c[i] = (a[i] - u[i] + p) % p;
	memset(u, 0, sizeof(int) * N);
	memset(v, 0, sizeof(int) * N); }