void update(int l, int r, int d) {
	for (l += M-1, r += M+1; l^r^1; l >>= 1, r >>= 1) {
		if (l < M) {
			tree[l] = max(tree[l*2], tree[l*2+1]) + mark[l];
			tree[r] = max(tree[r*2], tree[r*2+1]) + mark[r]; }
		if (~l & 1) { tree[l ^ 1] += d; mark[l ^ 1] += d; }
		if (r & 1) { tree[r ^ 1] += d; mark[r ^ 1] += d; } }
	for (; l; l >>= 1, r >>= 1)
		if (l < M) tree[l] = max(tree[l*2], tree[l*2+1]) + mark[l],
				tree[r] = max(tree[r*2], tree[r*2+1]) + mark[r]; }
int query(int l, int r) {
	int maxl = -INF, maxr = -INF;
	for (l += M-1, r += M+1; l^r^1; l >>= 1, r >>= 1) {
		maxl += mark[l]; maxr += mark[r];
		if (~l & 1) maxl = max(maxl, tree[l ^ 1]);
		if (r & 1) maxr = max(maxr, tree[r ^ 1]); }
	while (l) { maxl += mark[l]; maxr += mark[r];
		l >>= 1; r >>= 1; }
	return max(maxl, maxr); }