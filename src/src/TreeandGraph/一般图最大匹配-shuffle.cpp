int n, m, mat[N], vis[N]; vector<int> E[N];
bool dfs(int tim, int x) {
	shuffle(E[x].begin(), E[x].end(), rng);
	vis[x] = tim;
	for (auto y : E[x]) {
		int z = mat[y]; if (vis[z] == tim) continue;
		mat[x] = y, mat[y] = x, mat[z] = 0;
		if (!z || dfs(tim, z)) return true;
		mat[x] = 0, mat[y] = z, mat[z] = y; }
	return false; }
int main() { // 暗含二分图性质跑一次即可
	for (int T = 0; T < 10; ++T) {
		fill(vis + 1, vis + n + 1, 0);
		for (int i = 1; i <= n; ++i) 
			if (!mat[i]) dfs(i, i); } }
