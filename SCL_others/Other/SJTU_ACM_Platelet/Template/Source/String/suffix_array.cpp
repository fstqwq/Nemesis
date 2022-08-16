char s[maxn];
int sa[maxn], rank[maxn], wa[maxn], wb[maxn], cnt[maxn], height[maxn];
inline void build(int n, int m)
{
	int *x = wa, *y = wb, *t;
	for (int i = 1; i <= n; ++i) cnt[x[i] = s[i] - 'a' + 1]++;
	for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
	for (int i = n; i; --i) sa[cnt[x[i]]--] = i;

	for (int j = 1; j < n || (j == 1 && m < n); j <<= 1, t = x, x = y, y = t)
	{
		memset(cnt + 1, 0, m << 2);
		int p = 0;
		for (int i = n - j + 1; i <= n; ++i) y[++p] = i;
		for (int i = 1; i <= n; ++i)
		{
			++cnt[x[i]];
			sa[i] > j ? y[++p] = sa[i] - j : 0;
		}
		for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
		for (int i = n; i; --i) sa[cnt[x[y[i]]]--] = y[i];
                m = 0;
		for (int i = 1; i <= n; ++i)
			y[sa[i]] = (i == 1 || x[sa[i]] != x[sa[i - 1]] || x[sa[i - 1] + j] != x[sa[i] + j]) ? ++m : m;
	}
	for (int i = 1; i <= n; ++i) rank[sa[i]] = i;
	for (int i = 1, j, k = 0; i <= n; height[rank[i++]] = k)
		for (k ? --k : 0, j = sa[rank[i] - 1]; s[i + k] == s[j + k]; ++k);
}
