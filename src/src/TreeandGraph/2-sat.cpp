int stp, sccs, top; // N 开$\text{**两倍**}$
int dfn[N], low[N], scc[N], stk[N], ans[N];
void add(int x, int a, int y, int b) { // 注意连边对称
	E[x << 1 | a].push_back(y << 1 | b); }
void tarjan(int x) {
	dfn[x] = low[x] = ++stp;
	stk[top++] = x;
	for (auto y : E[x]) {
		if (!dfn[y]) 
			tarjan(y), low[x] = min(low[x], low[y]);
		else if (!scc[y])
			low[x] = min(low[x], dfn[y]); }
	if (low[x] == dfn[x]) {
		sccs++;
		do scc[stk[--top]] = sccs;
		while (stk[top] != x); } }
bool solve() {
	int cnt = n + n; stp = top = sccs = 0;
	fill(dfn, dfn + cnt + 1, 0); fill(scc, scc + cnt + 1, 0);
	for (int i = 0; i < cnt; ++i) if (!dfn[i]) tarjan(i);
	for (int i = 0; i < n; ++i) {
		if (scc[i << 1] == scc[i << 1 | 1]) return false;
		ans[i] = (scc[i << 1 | 1] < scc[i << 1]); }
	return true; }
