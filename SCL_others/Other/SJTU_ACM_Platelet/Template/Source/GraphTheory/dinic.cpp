struct Edge {
	Edge *next, *rev;
	int to, cap;
} *last[maxn], *cur[maxn], e[maxm], *ecnt = e;
inline void link(R int a, R int b, R int w)
{
	*++ecnt = (Edge) {last[a], ecnt + 1, b, w}; last[a] = ecnt;
	*++ecnt = (Edge) {last[b], ecnt - 1, a, 0}; last[b] = ecnt;
}
int ans, s, t, q[maxn], dep[maxn];
inline bool bfs()
{
	memset(dep, -1, (t + 1) << 2);
	dep[q[1] = t] = 0; int head = 0, tail = 1;
	while (head < tail)
	{
		int now = q[++head];
		for (Edge *iter = last[now]; iter; iter = iter -> next)
			if (dep[iter -> to] == -1 && iter -> rev -> cap)
				dep[q[++tail] = iter -> to] = dep[now] + 1;
	}
	return dep[s] != -1;
}
int dfs(int x, int f)
{
	if (x == t) return f;
	int used = 0;
	for (Edge* &iter = cur[x]; iter; iter = iter -> next)
		if (iter -> cap && dep[iter -> to] + 1 == dep[x])
		{
			int v = dfs(iter -> to, dmin(f - used, iter -> cap));
			iter -> cap -= v;
			iter -> rev -> cap += v;
			used += v;
			if (used == f) return f;
		}
	return used;
}
inline void dinic()
{
	while (bfs())
	{
		memcpy(cur, last, sizeof cur);
		ans += dfs(s, inf);
	}
}
