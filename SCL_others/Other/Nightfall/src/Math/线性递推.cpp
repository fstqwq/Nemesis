// Complexity: init O(n^2log) query O(n^2logk)
// Requirement: const LOG const MOD
// Example: In: {1, 3} {2, 1} an = 2an-1 + an-2
//          Out: calc(3) = 7
typedef vector<int> poly;
struct LinearRec {
	int n; poly first, trans; vector<poly> bin;
poly add(poly &a, poly &b) {
	poly res(n * 2 + 1, 0);
	// 不要每次新开 vector, 可以使用矩阵乘法优化
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= n; ++j) {
			(res[i+j]+=(LL)a[i] * b[j] % MOD) %= MOD;
	for (int i = 2 * n; i > n; --i) {
		for (int j = 0; j < n; ++j) {
			(res[i-1-j]+=(LL)res[i]*trans[j]%MOD) %=MOD;}
		res[i] = 0; }
	res.erase(res.begin() + n + 1, res.end());
	return res; }
LinearRec(poly &first, poly &trans): first(first), trans(trans) {
	n = first.size(); poly a(n + 1, 0); a[1] = 1;
	bin.push_back(a); for (int i = 1; i < LOG; ++i)
		bin.push_back(add(bin[i - 1], bin[i - 1])); }
int calc(int k) { poly a(n + 1, 0); a[0] = 1;
	for (int i = 0; i < LOG; ++i)
		if (k >> i & 1) a = add(a, bin[i]);
	int ret = 0; for (int i = 0; i < n; ++i)
		if ((ret += (LL)a[i + 1] * first[i] % MOD) >= MOD)
			ret -= MOD;
	return ret; }};
