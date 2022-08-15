int col[maxn], hash[maxn], hcnt, n, m;
int near[maxn];
bool vis[maxn];
int mark[maxn], mcnt, tcnt[maxn], tans;
int pre[256][maxn];
struct Block {
	int cnt[256];
} mem[maxn], *tot = mem;
inline Block *nw(Block *last, int v)
{
	Block *ret = ++tot;
	memcpy(ret -> cnt, last -> cnt, sizeof (ret -> cnt));
	++ret -> cnt[v & 255];
	return ret;
}
struct Arr {
	Block *b[256];
	inline int v(int c) {return b[c >> 8] -> cnt[c & 255];}
} c[maxn];
inline Arr cp(Arr last, int v)
{
	Arr ret;
	memcpy(ret.b, last.b, sizeof (ret.b));
	ret.b[v >> 8] = nw(last.b[v >> 8], v);
	return ret;
}
void bfs()
{
	int head = 0, tail = 1; q[1] = 1;
	while (head < tail)
	{
		int now = q[++head]; size[now] = 1; vis[now] = 1; dep[now] = dep[fa[now]] + 1;
		for (Edge *iter = last[now]; iter; iter = iter -> next)
			if (!vis[iter -> to])
				fa[q[++tail] = iter -> to] = now;
	}
	for (int i = n; i; --i)
	{
		int now = q[i];
		size[fa[now]] += size[now];
		size[son[fa[now]]] < size[now] ? son[fa[now]] = now : 0;
	}
	for (int i = 0; i < 256; ++i) c[0].b[i] = mem;
	for (int i = 1; i <= n; ++i)
	{
		int now = q[i];
		c[now] = cp(c[fa[now]], col[now]);
		top[now] = son[fa[now]] == now ? top[fa[now]] : now;
	}
}
inline int getlca(int a, int b) ;
void dfs_init(int x)
{
	vis[x] = 1; ++tcnt[col[x]] == 1 ? ++tans : 0;
	pre[mcnt][x] = tans;
	for (Edge *iter = last[x]; iter; iter = iter -> next)
		if (!vis[iter -> to]) dfs_init(iter -> to);
	--tcnt[col[x]] == 0 ? --tans : 0;
}
int jp[maxn];
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", &col[i]), hash[++hcnt] = col[i];
	std::sort(hash + 1, hash + hcnt + 1);
	hcnt = std::unique(hash + 1, hash + hcnt + 1) - hash - 1;
	for (int i = 1; i <= n; ++i) col[i] = std::lower_bound(hash + 1, hash + hcnt + 1, col[i]) - hash;
	for (int i = 1; i < n; ++i)
	{
		int a, b; scanf("%d%d", &a, &b); link(a, b);
	}
	bfs();
	int D = sqrt(n);
	for (int i = 1; i <= n; ++i)
		if (dep[i] % D == 0 && size[i] >= D)
		{
			memset(vis, 0, n + 1);
			mark[i] = ++mcnt;
			dfs_init(i);
		}
	for (int i = 1; i <= n; ++i) near[q[i]] = mark[q[i]] ? q[i] : near[fa[q[i]]];
	int ans = 0;
	memset(vis, 0, n + 1);
	for (; m; --m)
	{
		int x, y; scanf("%d%d", &x, &y);
		x ^= ans; ans = 0;
		int lca = getlca(x, y);
		if (dep[near[x]] < dep[lca]) std::swap(x, y);
		if (dep[near[x]] >= dep[lca])
		{
			Arr *_a = c + near[x];
			Arr *_b = c + y;
			Arr *_c = c + lca;
			Arr *_d = c + fa[lca];
			for (; !mark[x]; x = fa[x])
				if (_a -> v(col[x]) + _b -> v(col[x]) == _c -> v(col[x]) + _d -> v(col[x]) && !vis[col[x]])
					vis[jp[++ans] = col[x]] = 1;
			for (int i = 1; i <= ans; ++i) vis[jp[i]] = 0;
			ans += pre[mark[near[x]]][y];
		}
		else
		{
			for (; x != lca; x = fa[x]) !vis[col[x]] ? vis[jp[++ans] = col[x]] = 1 : 0;
			for (; y != lca; y = fa[y]) !vis[col[y]] ? vis[jp[++ans] = col[y]] = 1 : 0;
			!vis[col[lca]] ? vis[jp[++ans] = col[lca]] = 1 : 0;
			for (int i = 1; i <= ans; ++i) vis[jp[i]] = 0;
		}
		printf("%d\n", ans);
	}
	return 0;
}
