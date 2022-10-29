vector<int> solve_sparse_equations(const vector<tuple<int, int, int> > &A, const vector<int> &b) {
	int n = (int)b.size(); // 0-based
	vector<vector<int> > f({b});
	for (int i = 1; i < 2 * n; i++) {
		vector<int> v(n); auto &u = f.back();
		for (auto [x, y, z] : A) // [x, y, value]
			v[x] = (v[x] + (long long)u[y] * z) % p;
		f.push_back(v); }
	vector<int> w(n); mt19937 gen;
	for (auto &x : w)
		x = uniform_int_distribution<int>(1, p - 1)(gen);
	vector<int> a(2 * n);
	for (int i = 0; i < 2 * n; i++)
		for (int j = 0; j < n; j++)
			a[i] = (a[i] + (long long)f[i][j] * w[j]) % p;
	auto c = berlekamp_massey(a); int m = (int)c.size();
	vector<int> ans(n);
	for (int i = 0; i < m - 1; i++)
		for (int j = 0; j < n; j++)
			ans[j] = (ans[j] +
				(long long)c[m - 2 - i] * f[i][j]) % p;
	int inv = qpow(p - c[m - 1], p - 2);
	for (int i = 0; i < n; i++)
		ans[i] = (long long)ans[i] * inv % p;
	return ans; }