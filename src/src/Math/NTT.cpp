vector<int> omega[25];
void NTT_init(int n) {
	for (int k = 2, d = 0; k <= n; k *= 2, d++) {
		omega[d].resize(k + 1);
		int wn = qpow(3, (p - 1) / k), tmp = 1;
		for (int i = 0; i <= k; i++) { omega[d][i] = tmp;
			tmp = (long long)tmp * wn % p; } } }
void NTT(int *c, int n, int tp) {
	static unsigned long long a[maxn];
	for (int i = 0; i < n; i++) a[i] = c[i];
	for (int i = 1, j = 0; i < n - 1; i++) {
		int k = n; do j ^= (k >>= 1); while (j < k);
		if (i < j) swap(a[i], a[j]); }
	for (int k = 1, d = 0; k < n; k *= 2, d++) {
		if (d == 16) for (int i = 0; i < n; i++) a[i] %= p;
		for (int i = 0; i < n; i += k * 2)
			for (int j = 0; j < k; j++) {
				int w = omega[d][tp > 0 ? j : k * 2 - j];
				unsigned long long u = a[i + j],
					v = w * a[i + j + k] % p;
				a[i + j] = u + v;
				a[i + j + k] = u - v + p; } }
	if (tp>0) {for (int i = 0; i < n; i++) c[i] = a[i] % p;}
	else { int inv = qpow(n, p - 2);
		for (int i = 0; i < n; i++) c[i] = a[i] * inv % p;}}