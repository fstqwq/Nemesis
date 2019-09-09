#define maxn 1000010
const int mod = 1e9 + 7;
int f[maxn], pre[maxn], suf[maxn], inp[maxn], p[maxn];
inline int qpow(R int base, R int power)
{
	R int ret = 1;
	for (; power; power >>= 1, base = 1ll * base * base % mod)
		power & 1 ? ret = 1ll * ret * base % mod : 0;
	return ret;
}
bool vis[maxn];
int pr[maxn], prcnt, fpow[maxn];
int main()
{
	R int n = F(), k = F();
	for (R int i = 2; i <= k + 2; ++i)
	{
		if (!vis[i]) pr[++prcnt] = i, fpow[i] = qpow(i, k);
		for (R int j = 1; j <= prcnt && i * pr[j] <= k + 2; ++j)
		{
			vis[i * pr[j]] = 1;
			fpow[i * pr[j]] = 1ll * fpow[i] * fpow[pr[j]] % mod;
			if (i % pr[j] == 0) break;
		}
	}
	fpow[1] = 1;
	for (R int i = 1; i <= k + 2; ++i) f[i] = (f[i - 1] + fpow[i]) % mod;
	if (n <= k + 2) return !printf("%d\n", f[n] );
	pre[0] = 1;
	for (R int i = 1; i <= k + 3; ++i) pre[i] = 1ll * pre[i - 1] * (n - i) % mod;
	suf[k + 3] = 1;
	for (R int i = k + 2; i >= 0; --i) suf[i] = 1ll * suf[i + 1] * (n - i) % mod;
 
	p[0] = 1;
	for (R int i = 1; i <= k + 2; ++i) p[i] = (1ll * p[i - 1] * i) % mod;
 
	inp[k + 2] = qpow(p[k + 2], mod - 2);
	
	for (R int i = k + 1; i >= 0; --i) inp[i] = (1ll * inp[i + 1] * (i + 1)) % mod;
 
	R int ans = 0;
	for (R int i = 1; i <= k + 2; ++i)
	{
		R int temp = inp[k + 2 - i]; if ((k + 2 - i) & 1) temp = mod - temp;
		R int tmp = 1ll * pre[i - 1] * suf[i + 1] % mod * temp % mod * inp[i - 1] % mod * f[i] % mod;
		ans = (ans + tmp) % mod;
	}
	printf("%d\n", ans );
	return 0;
}
/*
\sum_{i=1}^n i^k (mod 1e9 + 7)
*/
