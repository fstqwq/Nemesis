// $a \leq b \leq c \leq d:$ $w(b, c) \leq w(a, d),$ $w(a,c)+w(b,d) \leq w(a,d) + w(b,c)$
for (int len = 2; len <= n; ++len) {
	for (int l = 1, r = len; r <= n; ++l, ++r) {
		f[l][r] = INF;
		for (int k = m[l][r - 1]; k <= m[l + 1][r]; ++k) {
			if (f[l][r] > f[l][k] + f[k + 1][r] + w(l, r)) {
				f[l][r] = f[l][k] + f[k + 1][r] + w(l, r);
				m[l][r] = k;
	} } }
