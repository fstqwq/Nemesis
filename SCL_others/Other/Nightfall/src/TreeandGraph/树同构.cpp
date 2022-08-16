// $O(1)$ 求逆 时间复杂度 $O(n)$ MOD 需要是质数
#define fors(i) for (auto i : e[x]) if (i != p)
int ra[N]; void prepare() {
	for (int i = 0; i < N; ++ i) ra[i] = rand() % MOD;}
struct Sub {
	vector<int> s; int d1, d2, H1, H2;
	Sub() {d1 = d2 = 0; s.clear();}
	void add(int d, int v) { s.push_back(v);
		if (d>d1) d2=d1, d1=d; else if (d>d2) d2=d; }
	int hash() { H1 = H2 = 1; for (int i : s) {
			H1 = (ll) H1 * (ra[d1]+i) % MOD;
			H2 = (ll) H2 * (ra[d2]+i) % MOD; } return H1;}
	pii del(int d, int v) { if (d==d1)
		return {d2+1, (ll)H2*reverse(ra[d2]+v) % MOD};
		return {d1+1, (ll)H1*reverse(ra[d1]+v) % MOD};}};
pii U[N]; int A[N]; Sub tree[N]; //A[x]为以x为根的哈希值
void dfsD(int x, int p) { tree[x] = Sub();
	fors(i) { dfsD(i, x);
		tree[x].add(tree[i].d1 + 1, tree[i].H1); }
	tree[x].hash(); }
void dfsU(int x, int p) {
	if (p) tree[x].add(U[x].first, U[x].second);
	A[x] = tree[x].hash();
	fors(i){U[i]=tree[x].del(tree[i].d1+1,tree[i].H1);
		dfsU(i, x); } }