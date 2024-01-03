const int N = 1005;
const int MOD = 1e9 + 7;
int n, m;
int g[N][N], deg[N], del[N];
LL t[1 << 25];
int c[1 << 25];
LL ans = 0;
void solve (int x) {
	vector <int> out;
	for (int i = 1; i <= n; i++) if (g[x][i] && !del[i]) {
		out.push_back(i);
	}
	int k = (int) out.size();
	vector <LL> e;
	for (int i = 0; i < k; i++) {
		LL w = 0;
		for (int j = 0; j < k; j++) {
			if (g[out[i]][out[j]]) w |= 1ll << j;
		}
		e.push_back(w);
	}
	int left = min(k, (k + 4) / 2), right = k - left;
	for (int i = 0; i < (1 << right); i++) c[i] = 0;
	t[0] = (1ll << k) - 1; c[t[0] >> left] = 1;
	for (int i = 1; i < (1 << left); i++) {
		int lb = __builtin_ctz(i);
		int j = i ^ (1 << lb);
		if ((t[j] >> lb) & 1) {
			t[i] = t[j] & e[lb];
			c[t[i] >> left] ++; 
		} else {
			t[i] = 0;
		}
	}
	for (int i = 0; i < right; i++) {
		for (int j = 0; j < (1 << right); j++) if ((~j >> i) & 1) {
			c[j] += c[j | (1 << i)];
		}
	}
	t[0] = ((1ll << k) - 1) ^ ((1 << left) - 1);
    (ans += c[0]) %= MOD;
	for (int i = 1; i < (1 << right); i++) {
		int lb = __builtin_ctz(i);
		int j = i ^ (1 << lb);
		if ((t[j] >> (lb + left)) & 1) {
			t[i] = t[j] & e[lb + left];
			(ans += c[i]) %= MOD;
		} else {
			t[i] = 0;
		}
	}
	ans %= MOD;
	del[x] = 1;
	for (int i = 1; i <= n; i++) if (g[x][i]) --deg[i];
}
void work() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		g[u][v] = 1;
		g[v][u] = 1;
		++ deg[u]; ++ deg[v];
	}
	for (int i = 1; i <= n; i++) {
		pair <int, int> w = {n, -1};
		for (int j = 1; j <= n; j++) if (!del[j]) {
			w = min(w, pii(deg[j], j));
		}
		solve (w.second);
	}
	cout << ans << endl;
}