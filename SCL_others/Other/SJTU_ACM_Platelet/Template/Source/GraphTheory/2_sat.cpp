struct Edge {
	Edge *next;
	int to;
} *last[maxn << 1], e[maxn << 2], *ecnt = e;
inline void link(int a, int b)
{
	*++ecnt = (Edge) {last[a], b}; last[a] = ecnt;
}
int dfn[maxn], low[maxn], timer, st[maxn], top, id[maxn], colcnt, n;
bool fail, used[maxn];
void tarjan(int x, int fa)
{
	dfn[x] = low[x] = ++timer; st[++top] = x;
	for (R Edge *iter = last[x]; iter; iter = iter -> next)
		if (iter -> to != fa)
		{
			if (!dfn[iter -> to])
			{
				tarjan(iter -> to, x);
				cmin(low[x], low[iter -> to]);
			}
			else if (!id[iter -> to]) cmin(low[x], dfn[iter -> to]);
		}
	if (dfn[x] == low[x])
	{
		++colcnt; bool flag = 1;
		for (; ;)
		{
			int now = st[top--];
			id[now] = colcnt;
			if (now <= 2 * n)
			{
				flag &= !used[id[now <= n ? now + n : now - n]];
				now <= n ? fail |= (id[now + n] == id[now]) : fail |= (id[now - n] == id[now]);
			}
			if (now == x) break;
		}
		used[colcnt] = flag;
	}
}
int ans[maxn], tot;
int main()
{
	/*
		build your graph here.
	*/
	for (R int i = 1; !fail && i <= n; ++i) if (!dfn[i]) tarjan(i, 0);
	if (fail)
	{
		puts("Impossible");
		return 0;
	}
	for (R int i = 1; i <= n; ++i) if (used[id[i]]) ans[++tot] = i;
	printf("%d\n", tot);
	std::sort(ans + 1, ans + tot + 1);
	for (R int i = 1; i <= tot; ++i) printf("%d ", ans[i]);
	return 0;
}
