// 求边仙人掌长度为len的简单路径条数ans[len]
const int N = 5005, MOD = 1e9 + 7; vector<int> G[N];
int f[N][N], dfn[N], tot, low[N], n, sz[N];
vector<int> getcycle(int x, int root) {
	vector<int> cyc; // 获得root->x为第一条边的环
	cyc.push_back(root); cyc.push_back(x);
	while (true) { int nex = -1;
		for (int u : G[cyc.back()]) {
			if (low[u] != dfn[root] || cyc[cyc.size() - 2] == u || u == root) continue;
			nex = u; break; }
		if (nex == -1) break; cyc.push_back(nex); }
	return cyc; }
int walk(int x, int root) { // 沿着root->x dp一圈 获得从root出发往子树走所有长度为len的简单路径条数f[root][len]
	vector<int> cycle = getcycle(x, root);
	int szm = 0; // 合并路径时只for到最长长度, 保证复杂度
	for (int i = 1; i < (int) cycle.size(); ++ i) {
		int u = cycle[i], l1 = i, l2 = (int) cycle.size() - i;
		for (int k = 0; k < sz[u]; ++ k) {
			if (k + l1 < n) (f[root][k + l1] += f[u][k]) %= MOD;
			if (k + l2 < n) (f[root][k + l2] += f[u][k]) %= MOD;
			szm = max(szm, k + l1); szm = max(szm, k + l2); } }
	return szm; }
int g[N], msz, ans[N], par[N];
void walk2(int x, int root) { // 统计最浅点在这个环上的路径
	vector<int> cycle = getcycle(x, root);
	for (int i = 1; i < (int) cycle.size(); ++ i) {
		int u = cycle[i]; // 出发点为u往下走
		int l1 = i, l2 = (int) cycle.size() - i;
		for (int k = 0; k < sz[u]; ++ k) {
			for (int l = 0; l < msz; ++ l) {
				//g[l]为root之前子树伸出去长l路径条数 双向*2
				if (l + k + l1 < n)
					(ans[l+k+l1]+=2LL*g[l]*f[u][k]%MOD)%=MOD;
				if (l + k + l2 < n)
					(ans[l+k+l2]+=2LL*g[l]*f[u][k]%MOD)%=MOD;}}}
	for (int i = 1; i < (int) cycle.size(); ++ i) {
		int u = cycle[i], l1 = i, l2 = (int) cycle.size() - i;
		for (int k = 0; k < sz[u]; ++ k) { // 更新g[l]
			if (k + l1 < n) (g[k + l1] += f[u][k]) %= MOD;
			if (k + l2 < n) (g[k + l2] += f[u][k]) %= MOD;
			msz = max(msz, k+l1+1); msz = max(msz, k+l2+1); } }
	for (int i = 1; i < (int) cycle.size(); ++ i) {
		for (int j = 1; j < (int) cycle.size(); ++ j) {
			if (i == j) continue;
			// 环上u和v往下走出两条路径的合并
			int u = cycle[i], v = cycle[j];
			int l1 = abs(i-j), l2 = (int)cycle.size()-l1;
			for (int k = 0; k < sz[u]; ++ k) {
				for (int l = 0; l < sz[v]; ++ l) {
					if (l+k+l1<n) (ans[l+k+l1] += 1LL * f[v][l]*f[u][k] % MOD) %= MOD;
					if (l+k+l2<n) (ans[l+k+l2] += 1LL * f[v][l]*f[u][k] % MOD) %= MOD;}}}}
	msz = min(msz, n); }
void dfs(int x, int p = 0) {
	low[x] = dfn[x] = ++ tot; par[x] = p;
	for (int u : G[x]) if (u != p) {
		if (dfn[u]) low[x] = min(low[x], dfn[u]);
			else { dfs(u, x); low[x] = min(low[x], low[u]); } }
	f[x][0] = 1; sz[x] = 1;
	for (int u : G[x]) if (u != p) {
		if (low[u] == dfn[x] && par[u] != x) {
			// 用环边f[x]
			sz[x]=max(sz[x], walk(u,x)+1); sz[x]=min(sz[x],n); }
		else if (low[u] > dfn[x]) {
			// 树边更新f[x]
			sz[x]=max(sz[x], sz[u] + 2); sz[x]=min(sz[x], n);
			for (int k = 0; k < sz[u]; ++ k)
				(f[x][k + 1] += f[u][k]) %= MOD; } }
	// 子树背包
	for (int i = 0; i < n; ++ i) g[i] = 0;
	g[0] = 1; ans[0] ++; msz = 1;
	for (int u : G[x]) { if (u == p) continue;
		if (low[u]==dfn[x] && par[u]!=x) walk2(u, x); // 环边
		else if (low[u] > dfn[x]) { // 树边
			for (int k = 0; k < sz[u]; ++ k) {
				for (int l = 0; l < msz; ++ l) {
					if (k + l + 1 < n) (ans[k + l + 1] += 2LL * f[u][k] * g[l] % MOD) %= MOD; } }
			for (int k = 0; k < sz[u]; ++ k)
				(g[k + 1] += f[u][k]) %= MOD;
			msz = max(msz, sz[u] + 1); msz = min(msz, n); } } }