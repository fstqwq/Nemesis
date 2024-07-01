vector<int> G[MAXN], R[MAXN], son[MAXN];
int ufs[MAXN]; // R 是反图，son 存的是 sdom 树上的儿子
int idom[MAXN], sdom[MAXN], anc[MAXN];
// anc: sdom的dfn最小的祖先
int pr[MAXN], dfn[MAXN], id[MAXN], stamp;
int findufs(int x) { if (ufs[x] == x) return x;
	int t = ufs[x]; ufs[x] = findufs(ufs[x]);
	if (dfn[sdom[anc[x]]] > dfn[sdom[anc[t]]])
		anc[x] = anc[t];
	return ufs[x]; }
void dfs(int x) {
	dfn[x] = ++stamp; id[stamp] = x; sdom[x] = x;
	for (int y : G[x]) if (!dfn[y]) { pr[y] = x; dfs(y); } }
void get_dominator(int n) {
	for (int i = 1; i <= n; i++) ufs[i] = anc[i] = i;
	dfs(1);
	for (int i = n; i > 1; i--) { int x = id[i];
		for (int y : R[x]) if (dfn[y]) { findufs(y);
			if (dfn[sdom[x]] > dfn[sdom[anc[y]]])
				sdom[x] = sdom[anc[y]]; }
		son[sdom[x]].push_back(x); ufs[x] = pr[x];
		for (int u : son[pr[x]]) { findufs(u);
			idom[u] = (sdom[u] == sdom[anc[u]] ?
				pr[x] : anc[u]); }
		son[pr[x]].clear(); }
	for (int i = 2; i <= n; i++) { int x = id[i];
		if (idom[x] != sdom[x]) idom[x] = idom[idom[x]];
		son[idom[x]].push_back(x); } }
