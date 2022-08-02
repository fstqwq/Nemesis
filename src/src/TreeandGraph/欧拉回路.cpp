/* comment : directed */
int e, cur[N]/*, deg[N]*/;
vector<int>E[N];
int id[M]; bool vis[M];
stack<int>stk;
void dfs(int u) {
	for (cur[u]; cur[u] < E[u].size(); cur[u]++) {
		int i = cur[u];
		if (vis[abs(E[u][i])]) continue;
		int v = id[abs(E[u][i])] ^ u;
		vis[abs(E[u][i])] = 1; dfs(v);
		stk.push(E[u][i]); }
}// dfs for all when disconnect 
void add(int u, int v) {
	id[++e] = u ^ v; // s = u
	E[u].push_back(e); E[v].push_back(-e);
/* 	E[u].push_back(e); deg[v]++; */
} bool valid() {
	for (int i = 1; i <= n; i++)
		if (E[i].size() & 1) return 0;
/*		if (E[i].size() != deg[i]) return 0;*/
	return 1;}
