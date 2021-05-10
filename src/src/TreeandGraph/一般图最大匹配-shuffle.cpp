mt19937 rng(233);
int n, m, vis[505], match[505];
vector<int> g[505];
bool dfs(int tim, int x) {
	shuffle(g[x].begin(), g[x].end(), rng);
	vis[x] = tim;
	for (int y : g[x]) {
		int z = match[y];
		if (vis[z] == tim) continue;
		match[x] = y, match[y] = x, match[z] = 0;
		if (!z || dfs(tim, z)) return true;
		match[x] = 0, match[y] = z, match[z] = y; }
	return false; }
int main() {
	for (int T = 0; T < 10; ++T) {
		fill(vis + 1, vis + 1 + n, 0);
		for (int i = 1; i <= n; ++i) if (!match[i]) dfs(i, i);
	}
}

