int dfn[maxn], low[maxn], timer, st[maxn], top, id[maxn], scc;
void dfs(int x)
{
	dfn[x] = low[x] = ++timer; st[++top] = x;
	for (Edge *iter = last[x]; iter; iter = iter -> next)
		if (!dfn[iter -> to])
		{
			dfs(iter -> to);
			cmin(low[x], low[iter -> to]);
			if (dfn[x] == low[iter->to])
			{
				int now, elder = top, minn = c[x];
				++scc;
				do
				{
					now = st[top--];
					cmin(minn, c[now]);
				}
				while (iter -> to != now);
				for (int i = top + 1; i <= elder; ++i)
					add(scc, st[i], minn);
				add(scc, x, minn);
			}
		}
		else if (!id[iter -> to]) cmin(low[x], dfn[iter -> to]);
}
