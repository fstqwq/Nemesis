struct edge
{
	int a, b, w;
	inline bool operator < (const edge &that) const {return w > that.w;}
} e[maxm];
int fa[maxn], f1[maxn], f2[maxn], f1cnt, f2cnt, val[maxn], size[maxn];
int main()
{
	int n, m; scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i)
		scanf("%d%d%d", &e[i].a, &e[i].b, &e[i].w);
	for (int i = 1; i <= n; ++i) size[i] = 1;
	std::sort(e + 1, e + m + 1);
	for (int i = 1; i <= m; ++i)
	{
		int x = e[i].a, y = e[i].b;
		for ( ; fa[x]; x = fa[x]) ;
		for ( ; fa[y]; y = fa[y]) ;
		if (x != y)
		{
			if (size[x] < size[y]) std::swap(x, y);
			size[x] += size[y];
			val[y] = e[i].w;
			fa[y] = x;
		}
	}

	int q; scanf("%d", &q);
	for (; q; --q)
	{
		int a, b; scanf("%d%d", &a, &b); f1cnt = f2cnt = 0;
		for (; fa[a]; a = fa[a]) f1[++f1cnt] = a;
		for (; fa[b]; b = fa[b]) f2[++f2cnt] = b;
		if (a != b) {puts("-1"); continue;}
		while (f1cnt && f2cnt && f1[f1cnt] == f2[f2cnt]) --f1cnt, --f2cnt;
		int ret = 0x7fffffff;
		for (; f1cnt; --f1cnt) cmin(ret, val[f1[f1cnt]]);
		for (; f2cnt; --f2cnt) cmin(ret, val[f2[f2cnt]]);
		printf("%d\n", ret);
	}
	return 0;
}
