const int MAXN = MAXL * 2 + 1;
int a[MAXN], x[MAXN], y[MAXN], c[MAXN], sa[MAXN], rank[MAXN], height[MAXN];
void calc_sa(int n) {
	int m = alphabet, k = 1;
	memset(c, 0, sizeof(*c) * (m + 1));
	for (int i = 1; i <= n; ++i) c[x[i] = a[i]]++;
	for (int i = 1; i <= m; ++i) c[i] += c[i - 1];
	for (int i = n; i; --i) sa[c[x[i]]--] = i;
	for (; k <= n; k <<= 1) {
		int tot = k;
		for (int i = n - k + 1; i <= n; ++i) y[i - n + k] = i;
		for (int i = 1; i <= n; ++i)
			if (sa[i] > k) y[++tot] = sa[i] - k;
		memset(c, 0, sizeof(*c) * (m + 1));
		for (int i = 1; i <= n; ++i) c[x[i]]++;
		for (int i = 1; i <= m; ++i) c[i] += c[i - 1];
		for (int i = n; i; --i) sa[c[x[y[i]]]--] = y[i];
		for (int i = 1; i <= n; ++i) y[i] = x[i];
		tot = 1; x[sa[1]] = 1;
		for (int i = 2; i <= n; ++i) {
			if (max(sa[i], sa[i - 1]) + k > n || y[sa[i]] != y[sa[i - 1]] || y[sa[i] + k] != y[sa[i - 1] + k]) ++tot;
			x[sa[i]] = tot;
		}
		if (tot == n) break; else m = tot;
	}
}
void calc_height(int n) {
	for (int i = 1; i <= n; ++i) rank[sa[i]] = i;
	for (int i = 1; i <= n; ++i) {
		height[rank[i]] = max(0, height[rank[i - 1]] - 1);
		if (rank[i] == 1) continue;
		int j = sa[rank[i] - 1];
		while (max(i, j) + height[rank[i]] <= n && a[i + height[rank[i]]] == a[j + height[rank[i]]]) ++height[rank[i]];
	}
}
