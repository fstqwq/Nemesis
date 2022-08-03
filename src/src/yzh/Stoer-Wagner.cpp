const int N = 601;
int f[N], siz[N], G[N][N];
int getf(int x) {return f[x] == x ? x : f[x] = getf(f[x]);}
int dis[N], vis[N], bin[N];
int n, m;
int contract(int &s, int &t) {  // Find s,t
	memset(vis, 0, sizeof(vis));
	memset(dis, 0, sizeof(dis));
	int i, j, k, mincut, maxc;
	for (i = 1; i <= n; i++) {
		k = -1; maxc = -1;
		for (j = 1; j <= n; j++)
			if (!bin[j] && !vis[j] && dis[j] > maxc) {
				k = j;
				maxc = dis[j]; }
		if (k == -1) return mincut;
		s = t; t = k; mincut = maxc; vis[k] = true;
		for (j = 1; j <= n; j++)
			if (!bin[j] && !vis[j]) dis[j] += G[k][j];
	} return mincut; }
const int inf = 0x3f3f3f3f;
int solve() {
	int mincut, i, j, s, t, ans;
	for (mincut = inf, i = 1; i < n; i++) {
		ans = contract(s, t);
		bin[t] = true;
		if (mincut > ans) mincut = ans;
		if (mincut == 0) return 0;
		for (j = 1; j <= n; j++)
			if (!bin[j]) G[s][j] = (G[j][s] += G[j][t]);
	} return mincut; }
int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) f[i] = i, siz[i] = 1;
	for (int i = 1, u, v, w; i <= m; ++i) {
		cin >> u >> v >> w;
		int fu = getf(u), fv = getf(v);
		if (fu != fv) {
			if (siz[fu] > siz[fv]) swap(fu, fv);
			f[fu] = fv, siz[fv] += siz[fu]; }
		G[u][v] += w, G[v][u] += w; }
	cout << (siz[getf(1)] != n ? 0 : solve()); }
