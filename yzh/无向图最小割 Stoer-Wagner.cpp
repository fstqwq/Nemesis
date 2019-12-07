int f[N], dis[N]; bool vis[N];
int solve(int n) { // MAXN = 500
	int ans = INT_MAX;
	for (int i = 0; i < n; ++i) f[i] = i;
	while (n > 1) {
		int mx = 1;
		for (int i = 0; i < n; ++i) {
			dis[f[i]] = G[f[0]][f[i]];
			if (dis[f[i]] > dis[f[mx]]) mx = i;
		}
		int pre = 0;
		memset(vis, 0, sizeof(vis));
		vis[f[0]] = true;
		for (int i = 1; i < n; ++i) {
			if (i == n - 1) {
				ans = min(ans, dis[f[mx]]);
				for (int k = 0; k < n; ++k) 
					G[f[k]][f[pre]] = (G[f[pre]][f[k]] += G[f[k]][f[mx]]);
				f[mx] = f[--n];
			}
			vis[f[mx]] = true;
			pre = mx;
			mx = -1;
			for (int j = 1; j < n; ++j) if (!vis[f[j]]) {
				dis[f[j]] += G[f[pre]][f[j]];
				if (mx == -1 || dis[f[mx]] < dis[f[j]]) mx = j;
			}
		}
	}
	return ans;
}

