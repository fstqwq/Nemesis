// x^2=a (mod p),0 <=a<p,返回 true or false 代表是否存在解
// p必须是质数, 若是多个单次质数的乘积，可以分别求解再用CRT合并
// 复杂度为 O(log n)
void multiply(ll &c, ll &d, ll a, ll b, ll w) {
	int cc = (a * c + b * d % MOD * w) % MOD;
	int dd = (a * d + b * c) % MOD; c = cc, d = dd; }
bool solve(int n, int &x) {
	if (n==0) return x=0,true; if (MOD==2) return x=1,true;
	if (power(n, MOD / 2, MOD) == MOD - 1) return false;
	ll c = 1, d = 0, b = 1, a, w;
	// finding a such that a^2 - n is not a square
	do { a = rand() % MOD; w = (a * a - n + MOD) % MOD;
		if (w == 0) return x = a, true;
	} while (power(w, MOD / 2, MOD) != MOD - 1);
	for (int times = (MOD + 1) / 2; times; times >>= 1) {
		if (times & 1) multiply(c, d, a, b, w);
		multiply(a, b, a, b, w); }
	// x = (a + sqrt(w)) ^ ((p + 1) / 2)
	return x = c, true; }
