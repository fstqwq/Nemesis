// Complexity: O(n^2) Requirement: const MOD, inverse(int)
// Input: the first elements of the sequence
// Output: the recursive equation of the given sequence
// Example In: {1, 1, 2, 3}
// Example Out: {1, 1000000006, 1000000006} (MOD = 1e9+7)
struct Poly { vector<int> a; Poly() { a.clear(); }
	Poly(vector<int> &a): a(a) {}
	int length() const { return a.size(); }
	Poly move(int d) { vector<int> na(d, 0);
		na.insert(na.end(), a.begin(), a.end());
		return Poly(na); }
	int calc(vector<int> &d, int pos) { int ret = 0;
		for (int i = 0; i < (int)a.size(); ++i) {
			if ((ret+=(LL)d[pos - i]*a[i]%MOD) >= MOD) {
				ret -= MOD; }}
		return ret; }
	Poly operator - (const Poly &b) {
		vector<int> na(max(this->length(), b.length()));
		for (int i = 0; i < (int)na.size(); ++i) {
			int aa = i < this->length() ? this->a[i] : 0,
				bb = i < b.length() ? b.a[i] : 0;
			na[i] = (aa + MOD - bb) % MOD; }
		return Poly(na); } };
Poly operator * (const int &c, const Poly &p) {
	vector<int> na(p.length());
	for (int i = 0; i < (int)na.size(); ++i) {
		na[i] = (LL)c * p.a[i] % MOD; }
	return na; }
vector<int> solve(vector<int> a) {
	int n = a.size(); Poly s, b;
	s.a.push_back(1), b.a.push_back(1);
	for (int i = 0, j = -1, ld = 1; i < n; ++i) {
		int d = s.calc(a, i); if (d) {
			if ((s.length() - 1) * 2 <= i) {
				Poly ob = b; b = s;
				s=s-(LL)d*inverse(ld)%MOD*ob.move(i - j);
				j = i; ld = d;
			} else {
				s=s-(LL)d*inverse(ld)%MOD*b.move(i-j);}}}
	//Caution: s.a might be shorter than expected
	return s.a; }
/* 求行列式 -> 求特征多项式 : det(A)=(-1)^nPA(0)
 求矩阵或向量列最小多项式 : 随机投影成数列
 如果最小多项式里面有 x 的因子, 那么行列式为 0, 否则
 随机乘上对角阵 D, det(A)=det(AD)/det(D)*/