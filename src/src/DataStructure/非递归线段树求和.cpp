void update(int l, int r, int d) {
	int len = 1, cntl = 0, cntr = 0;
	for (l+=M-1, r+=M+1; l^r^1; l>>=1, r>>=1, len<<=1) {
		tree[l] += cntl * d, tree[r] += cntr * d;
		if (~l & 1) tree[l ^ 1] += d * len, mark[l ^ 1] += d, cntl += len;
		if (r & 1) tree[r ^ 1] += d * len, mark[r ^ 1] += d, cntr += len; }
	for (; l; l >>= 1, r >>= 1)
		tree[l] += cntl * d, tree[r] += cntr * d; }
int query(int l, int r) {
	int ans = 0, len = 1, cntl = 0, cntr = 0;
	for (l+=M-1, r+=M+1; l^r^1; l>>=1, r>>=1, len<<=1) {
		ans += cntl * mark[l] + cntr * mark[r];
		if (~l & 1) ans += tree[l ^ 1], cntl += len;
		if (r & 1) ans += tree[r ^ 1], cntr += len; }
	for (; l; l >>= 1, r >>= 1)
		ans += cntl * mark[l] + cntr * mark[r];
	return ans; }