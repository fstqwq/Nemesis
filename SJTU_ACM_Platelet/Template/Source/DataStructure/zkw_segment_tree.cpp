inline void build()
{
	for (int i = M - 1; i; --i) tr[i] = dmax(tr[i << 1], tr[i << 1 | 1]);
}
inline void Change(int x, int v)
{
	x += M; tr[x] = v; x >>= 1;
	for (; x; x >>= 1) tr[x] = dmax(tr[x << 1], tr[x << 1 | 1]);
}
inline int Query(int s, int t)
{
	int ret = -0x7fffffff;
	for (s = s + M - 1, t = t + M + 1; s ^ t ^ 1; s >>= 1, t >>= 1)
	{
		if (~s & 1) cmax(ret, tr[s ^ 1]);
		if (t & 1) cmax(ret, tr[t ^ 1]);
	}
	return ret;
}
int main()
{
	int n; scanf("%d", &n);
	for (M = 1; M < n; M <<= 1) ;
	for (int i = 0; i < n; ++i)
		scanf("%d", &tr[i + M]);
	for (int i = n; i < M; ++i) tr[i + M] = -0x7fffffff;
	build();
	int q; scanf("%d", &q);
	for (; q; --q)
	{
		int l, r; scanf("%d%d", &l, &r); --l, --r;
		printf("%d\n", Query(l, r));
	}
	return 0;
}
