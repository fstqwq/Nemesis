vector<int> G[maxn], R[maxn], son[maxn];
int ufs[maxn]; // R是反图, son存的是sdom树上的儿子
int idom[maxn], sdom[maxn], anc[maxn];
// anc: sdom的dfn最小的祖先
int p[maxn], dfn[maxn], id[maxn], tim;
int findufs(int x) { if (ufs[x] == x) return x;
	int t = ufs[x]; ufs[x] = findufs(ufs[x]);
	if (dfn[sdom[anc[x]]] > dfn[sdom[anc[t]]])
		anc[x] = anc[t];
	return ufs[x]; }
void dfs(int x) {
	dfn[x] = ++tim; id[tim] = x; sdom[x] = x;
	for (int y : G[x]) if (!dfn[y]) {
		p[y] = x; dfs(y); } }
void get_dominator(int n) {
	for (int i = 1; i <= n; i++) ufs[i] = anc[i] = i;
	dfs(1);
	for (int i = n; i > 1; i--) { int x = id[i];
		for (int y : R[x]) if (dfn[y]) { findufs(y);
			if (dfn[sdom[x]] > dfn[sdom[anc[y]]])
				sdom[x] = sdom[anc[y]]; }
		son[sdom[x]].push_back(x); ufs[x] = p[x];
		for (int u : son[p[x]]) { findufs(u);
			idom[u] = (sdom[u] == sdom[anc[u]] ? p[x] : anc[u]); }
		son[p[x]].clear(); }
	for (int i = 2; i <= n; i++) { int x = id[i];
		if (idom[x] != sdom[x]) idom[x] = idom[idom[x]];
		son[idom[x]].push_back(x); } }