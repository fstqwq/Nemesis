struct Edge {
	Edge *next;
	int to;
} *last[maxn], e[maxn << 1], *ecnt = e;
inline void link(int a, int b)
{
	*++ecnt = (Edge) {last[a], b}; last[a] = ecnt;
	*++ecnt = (Edge) {last[b], a}; last[b] = ecnt;
}
int a[maxn], n, dfn[maxn], pos[maxn], timer, inv[maxn], st[maxn];
int fa[maxn], size[maxn], dep[maxn], son[maxn], top[maxn];
bool vis[maxn];
void dfs1(int x); // 树剖
void dfs2(int x);
inline int getlca(int a, int b);
inline bool cmp(int a, int b)
{
	return dfn[a] < dfn[b];
}
inline bool isson(int a, int b)
{
	return dfn[a] <= dfn[b] && dfn[b] <= inv[a];
}
typedef long long ll;
bool imp[maxn];
struct sEdge {
	sEdge *next;
	int to, w;
} *slast[maxn], se[maxn << 1], *secnt = se;
inline void slink(int a, int b, int w)
{
	*++secnt = (sEdge) {slast[a], b, w}; slast[a] = secnt;
}
int main()
{
	scanf("%d", &n);
	for (int i = 1; i < n; ++i)
	{
		int a, b; scanf("%d%d", &a, &b);
		link(a, b);
	}
	int m; scanf("%d", &m);
	dfs1(1); dfs2(1);
	memset(size, 0, (n + 1) << 2);
	for (; m; --m)
	{
		int top = 0; scanf("%d", &k);
		for (int i = 1; i <= k; ++i) scanf("%d", &a[i]), vis[a[i]] = imp[a[i]] = 1;
		std::sort(a + 1, a + k + 1, cmp);
		int p = k;
		for (int i = 1; i < k; ++i)
		{
			int lca = getlca(a[i], a[i + 1]);
			if (!vis[lca]) vis[a[++p] = lca] = 1;
		}
		std::sort(a + 1, a + p + 1, cmp);
		st[++top] = a[1];
		for (int i = 2; i <= p; ++i)
		{
			while (!isson(st[top], a[i])) --top;
			slink(st[top], a[i], dep[a[i]] - dep[st[top]]);
			st[++top] = a[i];
		}
		/*
			write your code here.
		*/
		for (int i = 1; i <= p; ++i) vis[a[i]] = imp[a[i]] = 0, slast[a[i]] = 0;
		secnt = se;
	}
	return 0;
}
