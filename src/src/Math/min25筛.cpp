constexpr int MAXN = 200005, p = (int)1e9 + 7;
bool notp[MAXN];
int prime[MAXN / 5], prime_cnt;
// 线性筛省略
long long val[MAXN]; // n 的所有整除结果
int sqrtn;
void get_val(long long n) {
	for (int i = 1; i <= sqrtn; i++)
		val[++val[0]] = i;
	
	for (int i = sqrtn; i; i--)
		val[++val[0]] = n / i;
	
	assert(is_sorted(val + 1, val + val[0] + 1));
	val[0] = unique(val + 1, val + val[0] + 1) - val - 1;
}
int getid(long long x) { // val[val[0]] 就是 n
	return x <= sqrtn ? x : (val[0] - val[val[0]] / x + 1);
}
int f(long long n) {
	n %= p;
	return n * (n - 1) % p;
}
int g[MAXN];
int dp[MAXN], prime_sum[MAXN];
void get_dp(function<int(long long)> pw, function<int(long long)> sum) {
	memset(dp, 0, sizeof(dp));
	memset(prime_sum, 0, sizeof(prime_sum));
	for (int i = 1; i <= prime_cnt; i++)
		prime_sum[i] = (prime_sum[i - 1] + pw(prime[i])) % p;
	for (int i = 1; i <= val[0]; i++)
		dp[i] = (sum(val[i]) + p - 1) % p;
	for (int i = 1; i <= prime_cnt; i++) {
		int pi = prime[i];
		for (int j = val[0]; (long long)pi * pi <= val[j]; j--) {
			int k = getid(val[j] / pi);
			dp[j] = (dp[j] + (long long)pw(pi) * (prime_sum[i - 1] - dp[k])) % p;
			if (dp[j] < 0)
				dp[j] += p;
		}
	}
}
void calc(long long n) {
	get_val(n);
	get_dp([] (long long x) {
		x %= p;
		return x * x % p;
	}, [] (long long n) {
		n %= p;
		return n * (n + 1) % p * (2 * n + 1) % p * ((p + 1) / 6) % p;
	}); // x ^ 2
	for (int i = 1; i <= val[0]; i++)
		g[i] = dp[i];
	get_dp([] (long long x) {
		return x % p;
	}, [] (long long n) {
		n %= p;
		return n * (n + 1) / 2 % p;
	}); // x
	for (int i = 1; i <= val[0]; i++)
		g[i] = (g[i] - dp[i] + p) % p;
	memset(prime_sum, 0, sizeof(prime_sum));
	for (int i = 1; i <= prime_cnt; i++)
		prime_sum[i] = (prime_sum[i - 1] + f(prime[i])) % p;
}
int S(int i, long long n) {
	if (prime[i] > n || n < 1)
		return 0;
	int sq = sqrt(n + 0.5);
	int tmp = (g[getid(n)] - prime_sum[i - 1] + p) % p;
	for (int k = i; k <= prime_cnt && prime[k] <= sq; k++) {
		int pk = prime[k];
		long long pw = pk;
		for (int c = 1; pw * pk <= n; c++, pw *= pk)
			tmp = (tmp + (long long)S(k + 1, n / pw) * f(pw) + f(pw * pk)) % p;
	}
	return tmp;
}
int main() {
	long long n;
	cin >> n;
	sqrtn = 1; // sqrtn 是全局的
	while ((long long)(sqrtn + 1) * (sqrtn + 1) <= n)
		sqrtn++;
	get_table(sqrtn);
	calc(n);
	int ans = (S(1, n) + 1) % p;
	cout << ans << endl;
	return 0;
}
