#include <cstdio>
#include <cstring>
#include <algorithm>
 
#define R register
#define maxn 500010
#define cmin(_a, _b) (_a > (_b) ? _a = (_b) : 0)
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
struct Edge
{
	Edge *next;
	int to;
} *last[maxn], e[maxn << 1], *ecnt = e;
inline void link(R int a, R int b)
{
	*++ecnt = (Edge) {last[a], b}; last[a] = ecnt;
	*++ecnt = (Edge) {last[b], a}; last[b] = ecnt;
}
int a[maxn], n, dfn[maxn], pos[maxn], timer, inv[maxn], st[maxn];
int fa[maxn], size[maxn], dep[maxn], son[maxn], top[maxn];
bool vis[maxn];
void dfs1(R int x)
{
	vis[x] = 1; size[x] = 1; dep[x] = dep[fa[x]] + 1;
	for (R Edge *iter = last[x]; iter; iter = iter -> next)
		if (!vis[iter -> to])
		{
			fa[iter -> to] = x;
			dfs1(iter -> to);
			size[x] += size[iter -> to];
			size[son[x]] < size[iter -> to] ? son[x] = iter -> to : 0;
		}
}
void dfs2(R int x)
{
	vis[x] = 0; top[x] = x == son[fa[x]] ? top[fa[x]] : x;
	dfn[x] = ++timer; pos[timer] = x;
	if (son[x]) dfs2(son[x]);
	for (R Edge *iter = last[x]; iter; iter = iter -> next)
		if (vis[iter -> to]) dfs2(iter -> to);
	inv[x] = timer;
}
inline int getlca(R int a, R int b)
{
	while (top[a] != top[b])
		dep[top[a]] < dep[top[b]] ? b = fa[top[b]] : a = fa[top[a]];
	return dep[a] < dep[b] ? a : b;
}
inline bool cmp(R int a, R int b)
{
	return dfn[a] < dfn[b];
}
inline bool isson(R int a, R int b)
{
	return dfn[a] <= dfn[b] && dfn[b] <= inv[a];
}
typedef long long ll;
bool imp[maxn];
ll ans1;
int ans2, ans3, k;
int mx[maxn], mn[maxn];
struct sEdge
{
	sEdge *next;
	int to, w;
} *slast[maxn], se[maxn << 1], *secnt = se;
inline void slink(R int a, R int b, R int w)
{
	*++secnt = (sEdge) {slast[a], b, w}; slast[a] = secnt;
}
int main()
{
	scanf("%d", &n);
	for (R int i = 1; i < n; ++i)
	{
		R int a, b; scanf("%d%d", &a, &b);
		link(a, b);
	}
	R int m; scanf("%d", &m);
	dfs1(1); dfs2(1);
	memset(size, 0, (n + 1) << 2);
	for (; m; --m)
	{
		R int top = 0; scanf("%d", &k);
		for (R int i = 1; i <= k; ++i) scanf("%d", &a[i]), vis[a[i]] = imp[a[i]] = 1;
		std::sort(a + 1, a + k + 1, cmp);
		R int p = k;
		for (R int i = 1; i < k; ++i)
		{
			R int lca = getlca(a[i], a[i + 1]);
			if (!vis[lca]) vis[a[++p] = lca] = 1;
		}
		std::sort(a + 1, a + p + 1, cmp);
		st[++top] = a[1];
		for (R int i = 2; i <= p; ++i)
		{
			while (!isson(st[top], a[i])) --top;
			slink(st[top], a[i], dep[a[i]] - dep[st[top]]);
			st[++top] = a[i];
		}
	}
	return 0;
}
