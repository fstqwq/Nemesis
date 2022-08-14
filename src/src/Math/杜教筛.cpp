const int maxn = 5000005, table_size = 5000000,
	p = 1000000007, inv_2 = (p + 1) / 2;
bool notp[maxn];
int prime[maxn / 20], phi[maxn], tbl[100005];
long long N;
memset(tbl, -1, sizeof(tbl));
int S_phi(long long n) {
	if (n <= table_size) return phi[n];
	else if (~tbl[N / n]) return tbl[N / n];
	int ans = 0;
	for (long long i = 2, last; i <= n; i = last + 1) {
		last = n / (n / i); // 如果n是int，下面要强转
		ans = (ans + (last - i + 1) % p * S_phi(n / i)) % p; }
	ans = (n % p * ((n + 1) % p) % p * inv_2 - ans + p) % p;
	return tbl[N / n] = ans; } // 上一行也要强转