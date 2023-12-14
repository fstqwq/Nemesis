struct poly_eval { poly f; vector<int> x; // 函数和询问点
	vector<poly> gs; vector<int> ans; // gs 是预处理数组
	poly_eval(poly f, vector<int> x) : f(f), x(x) {}
	void pretreat(int l, int r, int o) { poly& g = gs[o];
		if (l == r) { g = poly{p - x[l], 1}; return; }
		int mid = (l + r) / 2; pretreat(l, mid, o * 2);
		pretreat(mid + 1, r, o * 2 + 1);
		if (o > 1)
			g = poly_auto_mul(gs[o * 2], gs[o * 2 + 1]); }
	void solve(int l, int r, int o, const poly& f) {
		if (l == r) { ans[l] = f[0]; return; }
		int mid = (l + r) / 2;
		solve(l, mid, o * 2, poly_mod(f, gs[o * 2]).first);
		solve(mid + 1, r, o * 2 + 1,
			poly_mod(f, gs[o * 2 + 1]).first); }
	vector<int> operator() () { // 包装好的接口
		int n = (int)f.size(), m = (int)x.size();
		if (m <= n) x.resize(m = n + 1);
		else if (n < m - 1) f.resize(n = m - 1);
		int bit_ceil = 1; while (bit_ceil < m) bit_ceil *= 2;
		ntt_init(bit_ceil * 2); // 注意这里 ntt_init 过了
		gs.resize(2 * bit_ceil + 1); pretreat(0, m - 1, 1);
		ans.resize(m); solve(0, m - 1, 1, f); return ans;} };
