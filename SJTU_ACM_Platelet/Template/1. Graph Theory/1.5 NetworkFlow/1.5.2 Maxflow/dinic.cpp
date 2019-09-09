typedef int ans_type;
const int inf = 0x7fffffff;
struct Edge
{
	Edge *next, *rev;
	int to, cap;
}*last[maxn], *cur[maxn], e[maxm], *ecnt = e;
int dep[maxn], q[maxn], s, t;
bool vis[maxn];
ans_type ans;
inline void link(int a, int b, int w)
{
	*++ecnt = (Edge) {last[a], ecnt + 1, b, w}; last[a] = ecnt;
	*++ecnt = (Edge) {last[b], ecnt - 1, a, 0}; last[b] = ecnt;
}
inline bool bfs()
{
	memset(dep, -1, sizeof (dep));
	int head = 0, tail = 1; dep[q[1] = t] = 0;
	while (head < tail)
	{
		int now = q[++head];
		for (Edge *iter = last[now]; iter; iter = iter -> next)
				if (iter -> rev -> cap && dep[iter -> to] == -1)
					dep[q[++tail] = iter -> to] = dep[now] + 1;
	}
	return dep[s] != -1;
}
int dfs(int x, int f)
{
	if (x == t) return f;
	int used = 0;
	for (Edge* &iter = cur[x]; iter; iter = iter -> next)
		if (iter -> cap && dep[x] == dep[iter -> to] + 1)
		{
			int v = dfs(iter -> to, min(f - used, iter -> cap));
			iter -> cap -= v;
			iter -> rev -> cap += v;
			used += v;
			if (used == f) return f;
		}
	if (!used) dep[x] = -1;
	return used;
}
inline void dinic()
{
	while (bfs())
	{
		memset(cur, last, sizeof last);
		ans += dfs(s, inf);
	}
}