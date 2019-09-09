int fa[maxn][17], mn[maxn][17], dep[maxn];
bool vis[maxn];
void dfs(int x)
{
	vis[x] = 1;
	for (int i = 1; i <= 16; ++i)
	{
		if (dep[x] < (1 << i)) break;
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
		mn[x][i] = dmin(mn[x][i - 1], mn[fa[x][i - 1]][i - 1]);
	}
	for (Edge *iter = last[x]; iter; iter = iter -> next)
		if (!vis[iter -> to])
		{
			fa[iter -> to][0] = x;
			mn[iter -> to][0] = iter -> w;
			dep[iter -> to] = dep[x] + 1;
			dfs(iter -> to);
		}
}
inline int getlca(int x, int y)
{
	if (dep[x] < dep[y]) std::swap(x, y);
	int t = dep[x] - dep[y];
	for (int i = 0; i <= 16 && t; ++i)
		if ((1 << i) & t)
			x = fa[x][i], t ^= 1 << i;
	for (int i = 16; i >= 0; --i)
		if (fa[x][i] != fa[y][i])
		{
			x = fa[x][i];
			y = fa[y][i];
		}
	if (x == y) return x;
	return fa[x][0];
}
inline int getans(int x, int f)
{
	int ans = inf, t = dep[x] - dep[f];
	for (int i = 0; i <= 16 && t; ++i)
		if (t & (1 << i))
		{
			cmin(ans, mn[x][i]);
			x = fa[x][i];
			t ^= 1 << i;
		}
	return ans;
}
