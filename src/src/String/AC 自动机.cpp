void build() {
	q[he = 0] = 1, ta = 1;
	fail[0] = 1; fill(t[0], t[0] + A, 1);
	while (he < ta) {
		int x = q[he++];
		for (int i = 0; i < A; i++) {
			int to = t[x][i], j = fail[x];
			if (!to) t[x][i] = t[fail[x]][i];
			else {
				if (!t[j][i]) j = fail[j];
				fail[to] = t[j][i];
				q[ta++] = to; } } } }
