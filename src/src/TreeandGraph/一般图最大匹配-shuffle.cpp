mt19937 rng(233);
int n, m, match[N], vis[N]; vector<int> E[N];
bool dfs(int tim, int x) {
	shuffle(E[x].begin(), E[x].end(), rng);
	vis[x] = tim;
	for (auto y : E[x]) {
		int z = match[y]; if (vis[z] == tim) continue;
		match[x] = y, match[y] = x, match[z] = 0;
		if (!z || dfs(tim, z)) return true;
		match[x] = 0, match[y] = z, match[z] = y; }
	return false; }
int main() {
	for (int T = 0; T < 10; ++T) {
		for (int i = 1; i <= n; i++) vis[i] = 0;
		for (int i = 1; i <= n; ++i) if (!match[i]) dfs(i, i); } }
