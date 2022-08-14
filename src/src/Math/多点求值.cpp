int q[maxn], ans[maxn]; // q是要代入的各个系数，ans是求出的值
int tg[25][maxn * 2], tf[25][maxn]; // tg是预处理乘积
// tf是项数越来越少的f, tf[0]就是原来的函数
void pretreat(int l, int r, int k) { // 多点求值预处理
	static int a[maxn], b[maxn];
	int *g = tg[k] + l * 2;
	if (r - l + 1 <= 200) { g[0] = 1; // 小范围暴力
		for (int i = l; i <= r; i++) {
			for (int j = i - l + 1; j; j--) {
				g[j] = (g[j-1] - (long long)g[j]*q[i]) % p;
				if (g[j] < 0) g[j] += p; }
			g[0] = (long long)g[0] * (p-q[i]) % p;} return;}
	int mid = (l + r) / 2;
	pretreat(l, mid, k + 1); pretreat(mid + 1, r, k + 1);
	if (!k) return;
	int N = 1; while (N <= r - l + 1) N *= 2;
	int *gl = tg[k+1] + l * 2, *gr = tg[k+1] + (mid+1) * 2;
	memset(a, 0, sizeof(int) * N);
	memset(b, 0, sizeof(int) * N);
	memcpy(a, gl, sizeof(int) * (mid - l + 2));
	memcpy(b, gr, sizeof(int) * (r - mid + 1));
	NTT(a, N, 1); NTT(b, N, 1);
	for (int i = 0; i < N; i++)
		a[i] = (long long)a[i] * b[i] % p;
	NTT(a, N, -1);
	for (int i = 0; i <= r - l + 1; i++) g[i] = a[i]; }
void solve(int l, int r, int k) { // 多点求值主过程
	int *f = tf[k];
	if (r - l + 1 <= 200) {
		for (int i = l; i <= r; i++) { int x = q[i];
			for (int j = r - l; ~j; j--)
				ans[i] = ((long long)ans[i]*x + f[j]) % p; }
		return; }
	int mid = (l + r) / 2, *ff = tf[k + 1],
		*gl = tg[k+1] + l * 2, *gr = tg[k+1] + (mid+1) * 2;
	get_mod(f, gl, ff, nullptr, r - l + 1, mid - l + 2);
	solve(l, mid, k + 1);
	memset(gl, 0, sizeof(int) * (mid - l + 2));
	memset(ff, 0, sizeof(int) * (mid - l + 1));
	get_mod(f, gr, ff, nullptr, r - l + 1, r - mid + 1);
	solve(mid + 1, r, k + 1);
	memset(gr, 0, sizeof(int) * (r - mid + 1));
	memset(ff, 0, sizeof(int) * (r - mid)); }
// f < x^n，m个询问，询问是0-based，当然改成1-based也很简单
void get_value(int *f, int *x, int *a, int n, int m) {
	if (m <= n) m = n + 1;
	if (n < m - 1) n = m - 1; // 补零方便处理
	memcpy(tf[0], f, sizeof(int) * n);
	memcpy(q, x, sizeof(int) * m);
	pretreat(0, m - 1, 0); solve(0, m - 1, 0);
	if (a) // 如果a是nullptr，代表不复制答案，直接用ans数组
		memcpy(a, ans, sizeof(int) * m); }