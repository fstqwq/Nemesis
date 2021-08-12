// comment : directed
int cur[N]/*, deg[N]*/;
vector<int>E[N];
int id[M]; bool vis[M];
stack<int>stk;
void dfs(int u) {
	for (cur[u]; cur[u] < E[u].size(); cur[u]++) {
		int i = cur[u];
		if (vis[abs(E[u][i])]) continue;
		int v = id[abs(E[u][i])] ^ u;
		vis[abs(E[u][i])] = 1; dfs(v);
		stk.push(E[u][i]); } }
void solve(int n, int m) {
	int s = 1;
	for (int i = 1; i <= m; i++) {
		int u = read(), v = read();
		id[i] = u ^ v; s = u;
		E[u].push_back(i); E[v].push_back(-i);
//		E[u].push_back(i); deg[v]++;
	}
	for (int i = 1; i <= n; i++)
		if (E[i].size() & 1) { puts("NO"); return; }
//		if (E[i].size() != deg[i]) { puts("NO"); return; }
	dfs(s);
	if (stk.size() != m) { puts("NO"); return; }
	puts("YES");
	while (stk.size()) printf("%d ", stk.top()), stk.pop();
}
