struct Edge {
	Edge *next;
	int to;
} ;
Edge *last[maxn], e[maxm], *ecnt = e; // original graph
Edge *rlast[maxn], re[maxm], *recnt = re; // reversed-edge graph
Edge *tlast[maxn], te[maxn << 1], *tecnt = te; // dominate tree graph
int deg[maxn], q[maxn], fa[maxn][20], all_fa[maxn], fa_cnt, size[maxn], dep[maxn];
inline void link(int a, int b)
{
	*++ecnt = (Edge) {last[a], b}; last[a] = ecnt; ++deg[b];
}
inline void link_rev(R int a, R int b)
{
	*++recnt = (Edge) {rlast[a], b}; rlast[a] = recnt;
}
inline void link_tree(R int a, R int b)
{
	*++tecnt = (Edge) {tlast[a], b}; tlast[a] = tecnt;
}
inline int getlca(R int a, R int b)
{
	if (dep[a] < dep[b]) std::swap(a, b);
	R int temp = dep[a] - dep[b];
	for (R int i; temp; temp -= 1 << i)
		a = fa[a][i = __builtin_ctz(temp)];
	for (R int i = 16; ~i; --i)
		if (fa[a][i] != fa[b][i])
			a = fa[a][i], b = fa[b][i];
	if (a == b) return a;
	return fa[a][0];
}
void dfs(R int x)
{
	size[x] = 1;
	for (R Edge *iter = tlast[x]; iter; iter = iter -> next)
		dfs(iter -> to), size[x] += size[iter -> to];
}
int main()
{
	q[1] = 0;
	R int head = 0, tail = 1;
	while (head < tail)
	{
		R int now = q[++head];
		fa_cnt = 0;
		for (R Edge *iter = rlast[now]; iter; iter = iter -> next)
			all_fa[++fa_cnt] = iter -> to;
		for (; fa_cnt > 1; --fa_cnt)
			all_fa[fa_cnt - 1] = getlca(all_fa[fa_cnt], all_fa[fa_cnt - 1]);
		fa[now][0] = all_fa[fa_cnt];
		dep[now] = dep[all_fa[fa_cnt]] + 1;
		if (now) link_tree(fa[now][0], now);
 
		for (R int i = 1; i <= 16; ++i)
			fa[now][i] = fa[fa[now][i - 1]][i - 1];
		for (R Edge *iter = last[now]; iter; iter = iter -> next)
			if (--deg[iter -> to] == 0) q[++tail] = iter -> to;
	}
	dfs(0);
	for (R int i = 1; i <= n; ++i) printf("%d\n", size[i] - 1 );
	return 0;
}
