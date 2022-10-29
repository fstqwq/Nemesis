const Complex ima = Complex(0, 1); int p, base;
void DFT(Complex *a, Complex *b, int n) {
	static Complex c[maxn];
	for (int i = 0; i < n; i++)
		c[i] = Complex(a[i].a, b[i].a);
	FFT(c, n, 1);
	for (int i = 0; i < n; i++) { int j = (n - i) & (n - 1);
		a[i] = (c[i] + c[j].conj()) * 0.5;
		b[i] = (c[i] - c[j].conj()) * -0.5 * ima; } }
void IDFT(Complex *a, Complex *b, int n) {
	static Complex c[maxn];
	for (int i = 0; i < n; i++) c[i] = a[i] + ima * b[i];
	FFT(c, n, -1);
	for (int i = 0; i < n; i++) {
		a[i].a = c[i].a;
		b[i].a = c[i].b; } }
Complex a[2][maxn], b[2][maxn], c[3][maxn]; int ans[maxn];
int main() { int n, m;
	scanf("%d%d%d", &n, &m, &p); n++; m++;
	base = (int)(sqrt(p) + 0.5);
	for (int i = 0; i < n; i++) {
		int x; scanf("%d", &x); x %= p;
		a[1][i].a = x / base; a[0][i].a = x % base; }
	for (int i = 0; i < m; i++) {
		int x; scanf("%d", &x); x %= p; 
		b[1][i].a = x / base; b[0][i].a = x % base; }
	int N = 1; while (N < n + m - 1) N <<= 1; FFT_init(N);
	DFT(a[0], a[1], N); DFT(b[0], b[1], N);
	for (int i = 0; i < N; i++) c[0][i] = a[0][i] * b[0][i];
	for (int i = 0; i < N; i++)
		c[1][i] = a[0][i] * b[1][i] + a[1][i] * b[0][i];
	for (int i = 0; i < N; i++) c[2][i] = a[1][i] * b[1][i];
	FFT(c[1], N, -1); IDFT(c[0], c[2], N);
	for (int j = 2; ~j; j--)
		for (int i = 0; i < n + m - 1; i++)
			ans[i] = ((long long)ans[i] * base +
				(long long)(c[j][i].a + 0.5)) % p;
	// 实际上就是 c[2] * base ^ 2 + c[1] * base + c[0]
	return 0; }