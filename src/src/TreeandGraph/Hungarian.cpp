int n, k, mat[N], vis[N]; vector<int> E[N];
bool dfs(int tim, int x) {
	for (auto y : E[x]) {
		if (vis[y] == tim) continue;
		vis[y] = tim;
		if (!mat[y] || dfs(tim, mat[y])) {
			mat[y] = x; return 1; } }
	return 0; }
int solve() {
	fill(vis + 1, vis + k + 1, 0);
	int ans = 0;
	for (int i = 1; i <= n; ++i) 
		if (dfs(i, i)) ans++;
	return ans; }
