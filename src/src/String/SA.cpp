void Sort(int in[], int out[], int p[], int n, int m) {
	static int P[N];
	for (int i = 1; i <= m; i++) P[i] = 0;
	for (int i = 1; i <= n; i++) P[in[i]]++;
	for (int i = 2; i <= m; i++) P[i] += P[i - 1];
	for (int i = n; i; i--) out[P[in[p[i]]]--] = p[i]; }
int n; char s[N]; int sa[N], rk[N], h[N];
void getsa() {
	static int t1[N], t2[N], *x = t1, *y = t2; //clear n + 1
	int m = 127;
	for (int i = 1; i <= n; i++) x[i] = s[i], y[i] = i;
	Sort(x, sa, y, n, m);
	for (int j = 1, i, k = 0; k < n; m = k, j <<= 1) {
		for (i = n - j + 1, k = 0; i <= n; i++) y[++k] = i;
		for (i = 1; i <= n; i++)
			if (sa[i] > j) y[++k] = sa[i] - j;
		Sort(x, sa, y, n, m);
		for(swap(x, y), i = 2, x[sa[1]] = k = 1; i <= n; i++){
			x[sa[i]] = (y[sa[i - 1]] == y[sa[i]] &&
			y[sa[i - 1] + j] == y[sa[i] + j]) ? k : ++k; } }
	for (int i = 1; i <= n; i++) rk[sa[i]] = i;
	for (int i = 1, k = 0; i <= n; h[rk[i++]] = k) {
		k -= !!k;
		for(int j = sa[rk[i] - 1];s[i + k]==s[j + k];k++);}}
