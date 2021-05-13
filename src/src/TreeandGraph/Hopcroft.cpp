// 左侧n个点, 右侧k个点 ,1-base, 初始化将mx[],my[]都置为0
int n, m, k, q[N], dx[N], dy[N], mx[N], my[N];
vector <int> E[N];
bool bfs() { bool flag = 0; int qt = 0, qh = 0;
	for(int i = 1; i <= k; ++ i) dy[i] = 0;
	for(int i = 1; i <= n; ++ i) { dx[i] = 0;
		if (! mx[i]) q[qt ++] = i; }
	while (qh < qt) { int u = q[qh ++];
		for(auto v : E[u]) {
			if (! dy[v]) { dy[v] = dx[u] + 1;
				if (! my[v]) flag = 1; else {
					dx[my[v]] = dx[u] + 2;
					q[qt ++] = my[v]; } } } }
	return flag; }
bool dfs(int u) {
	for(auto v : E[u]) {
		if (dy[v] == dx[u] + 1) { dy[v] = 0;
			if (! my[v] || dfs(my[v])) {
				mx[u] = v; my[v] = u; return 1; }}}
	return 0; }
void hk() {
fill(mx + 1, mx + n + 1, 0); fill(my + 1, my + k + 1, 0);
while (bfs()) for(int i=1; i<=n; ++i) if (!mx[i]) dfs(i);}
