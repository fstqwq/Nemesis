struct edge {
	int v, nxt; LL f;
} e[M * 2];
int ecnt = 1, head[N], cur[N];
void add(int u, int v, LL f) {
	e[++ecnt] = {v, head[u], f};   head[u] = ecnt;
	e[++ecnt] = {u, head[v], 0ll}; head[v] = ecnt; }
int n, S, T;
int q[N], tag[N], he = 0, ta = 1;
bool bfs() {
	for (int i = S; i<= T; i++) tag[i] = 0;
	he = 0, ta = 1; q[0] = S;
	tag[S] = 1; 
	while (he < ta) {
		int x = q[he++];
		for (int o = head[x]; o; o = e[o].nxt) 
			if (e[o].f && !tag[e[o].v])
				tag[e[o].v] = tag[x] + 1, q[ta++] = e[o].v;
	}
	return !!tag[T]; }
LL dfs(int x, LL flow) {
	if (x == T) return flow;
	LL used = 0;
	for (int &o = cur[x]; o; o = e[o].nxt) {
		if (e[o].f && tag[x] < tag[e[o].v]) {
			LL ret = dfs(e[o].v, min(flow - used, e[o].f));
			if (ret) {
				e[o].f -= ret; e[o ^ 1].f += ret;
				used += ret;
				if (used == flow) return flow;
			} } }
	return used; }
LL dinic() {
	LL ans = 0;
	while (bfs()) {
		for (int i = S; i <= T; i++) cur[i] = head[i];
		ans += dfs(S, INF);
	} return ans; }
