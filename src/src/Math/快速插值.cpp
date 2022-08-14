int qx[maxn], qy[maxn];
int th[25][maxn * 2], ansf[maxn]; // th存的是各阶段的M(x)
void pretreat2(int l, int r, int k) { // 预处理
	static int A[maxn], B[maxn];
	int *h = th[k] + l * 2;
	if (l == r) { h[0] = p - qx[l]; h[1] = 1; return; }
	int mid = (l + r) / 2;
	pretreat2(l, mid, k + 1); pretreat2(mid + 1, r, k + 1);
	int N = 1; while (N <= r - l + 1) N *= 2;
	int *hl = th[k+1] + l * 2, *hr = th[k+1] + (mid+1) * 2;
	memset(A, 0, sizeof(int) * N);
	memset(B, 0, sizeof(int) * N);
	memcpy(A, hl, sizeof(int) * (mid - l + 2));
	memcpy(B, hr, sizeof(int) * (r - mid + 1));
	NTT(A, N, 1); NTT(B, N, 1);
	for (int i = 0; i < N; i++)
		A[i] = (long long)A[i] * B[i] % p;
	NTT(A, N, -1);
	for (int i = 0; i <= r - l + 1; i++) h[i] = A[i]; }
void solve2(int l, int r, int k) { // 分治
	static int A[maxn], B[maxn], t[maxn];
	if (l == r) return;
	int mid = (l + r) / 2;
	solve2(l, mid, k + 1); solve2(mid + 1, r, k + 1);
	int *hl = th[k+1] + l * 2, *hr = th[k+1] + (mid+1) * 2;
	int N = 1; while (N < r - l + 1) N *= 2;
	memset(A, 0, sizeof(int) * N);
	memset(B, 0, sizeof(int) * N);
	memcpy(A, ansf + l, sizeof(int) * (mid - l + 1));
	memcpy(B, hr, sizeof(int) * (r - mid + 1));
	NTT(A, N, 1); NTT(B, N, 1);
	for (int i = 0; i < N; i++)
		t[i] = (long long)A[i] * B[i] % p;
	memset(A, 0, sizeof(int) * N);
	memset(B, 0, sizeof(int) * N);
	memcpy(A, ansf + mid + 1, sizeof(int) * (r - mid));
	memcpy(B, hl, sizeof(int) * (mid - l + 2));
	NTT(A, N, 1); NTT(B, N, 1);
	for (int i = 0; i < N; i++)
		t[i] = (t[i] + (long long)A[i] * B[i]) % p;
	NTT(t, N, -1);
	memcpy(ansf + l, t, sizeof(int) * (r - l + 1)); }
// 主过程，如果x, y传nullptr表示询问已经存在了qx, qy里
void interpolation(int *x, int *y, int n, int *f=nullptr) {
	static int d[maxn];
	if (x) memcpy(qx, x, sizeof(int) * n);
	if (y) memcpy(qy, y, sizeof(int) * n);
	pretreat2(0, n - 1, 0);
	get_derivative(th[0], d, n + 1);
	multipoint_eval(d, qx, nullptr, n, n);
	for (int i = 0; i < n; i++)
		ansf[i] = (long long)qy[i] * qpow(ans[i], p-2) % p;
	solve2(0, n - 1, 0);
	if (f) memcpy(f, ansf, sizeof(int) * n); }