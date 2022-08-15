struct BCC {
	Graph *g, forest;
	int dfn[N], low[N], stack[N], tot[N], belong[N], vis[N], top, dfs_clock; 
	// tot[] is the size of each BCC, belong[] is the BCC that each node belongs to
	pair<int, int > ori[M]; // bridge in raw_graph(raw node)
	bool is_bridge[M];
	__inline void init(Graph *raw_graph) {
		g = raw_graph;
		memset(is_bridge, false, sizeof(*is_bridge) * g -> e);
		memset(vis + g -> base, 0, sizeof(*vis) * g -> n);
	}
	void tarjan(int u, int from) {
		dfn[u] = low[u] = ++dfs_clock; vis[u] = 1; stack[++top] = u;
		for (int p = g -> adj[u]; ~p; p = g -> nxt[p]) {
			if ((p ^ 1) == from) continue;
			int v = g -> v[p];
			if (vis[v]) {
				if (vis[v] == 1) low[u] = min(low[u], dfn[v]);
			} else {
				tarjan(v, p);
				low[u] = min(low[u], low[v]);
				if (low[v] > dfn[u]) is_bridge[p / 2] = true;
			}
		}
		if (dfn[u] != low[u]) return;
		tot[forest.new_node()] = 0;
		do {
			belong[stack[top]] = forest.n;
			vis[stack[top]] = 2;
			tot[forest.n]++;
			--top;
		} while (stack[top + 1] != u);
	}
	void solve() {
		forest.init(g -> base);
		int n = g -> n;
		for (int i = 0; i < n; ++i)
			if (!vis[i + g -> base]) {
				top = dfs_clock = 0;
				tarjan(i + g -> base, -1);
			}
		for (int i = 0; i < g -> e / 2; ++i)
			if (is_bridge[i]) {
				int e = forest.e;
				forest.bi_ins(belong[g -> v[i * 2]], belong[g -> v[i * 2 + 1]], g -> w[i * 2]);
				ori[e] = make_pair(g -> v[i * 2 + 1], g -> v[i * 2]);
				ori[e + 1] = make_pair(g -> v[i * 2], g -> v[i * 2 + 1]);
			}
	}
} bcc;
