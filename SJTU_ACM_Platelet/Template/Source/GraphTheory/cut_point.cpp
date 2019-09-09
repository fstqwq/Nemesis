int dfn[maxn], low[maxn], timer, ans, num;
void tarjan(int x, int fa)
{
	dfn[x] = low[x] = ++timer;
	for (Edge *iter = last[x]; iter; iter = iter -> next)
		if (iter -> to != fa)
		{
			if (!dfn[iter -> to])
			{
				tarjan(iter -> to, x);
				cmin(low[x], low[iter -> to]);
				if (dfn[x] <= low[iter -> to])
				{
					cut[x] = 1;
					if (!fa && dfn[x] < low[iter -> to]) num = 233;
					else if (!fa) ++num;
				}
			}
			else cmin(low[x], dfn[iter -> to]);
		}
}
int main()
{
	for (int i = 1; i <= n; ++i)
		if (!dfn[i])
		{
			num = 0;
			tarjan(i, 0);
			if (num == 1) cut[i] = 0;
		}
}
