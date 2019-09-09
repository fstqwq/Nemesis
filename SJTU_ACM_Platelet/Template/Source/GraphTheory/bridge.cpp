int dfn[maxn], low[maxn], timer;
void tarjan(int x, int fa)
{
	dfn[x] = low[x] = ++timer;
	for (R Edge *iter = last[x]; iter; iter = iter -> next)
		if (iter -> to != fa)
		{
			if (!dfn[iter -> to])
			{
				dfs(iter -> to, x);
				cmin(low[x], low[iter -> to]);
				if (dfn[x] < low[iter -> to]) ans[x][iter -> to] = ans[iter -> to][x] = 1;
			}
			else cmin(low[x], dfn[iter -> to]);
		}
}
