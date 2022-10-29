int stp, comps, top; // N 开$\text{**两倍**}$
int dfn[N], low[N], comp[N], stk[N], answer[N];
void add(int x, int a, int y, int b) {
//取$X_a$则必取$Y_b$.注意连边对称,即必须$X_b\rightarrow Y_a$.
	E[x << 1 | a].push_back(y << 1 | b); }
void tarjan(int x) {
	dfn[x] = low[x] = ++stp;
	stk[top++] = x;
	for (auto y : E[x]) {
		if (!dfn[y]) 
			tarjan(y), low[x] = min(low[x], low[y]);
		else if (!comp[y])
			low[x] = min(low[x], dfn[y]);
	}
	if (low[x] == dfn[x]) {
		comps++;
		do {int y = stk[--top];
			comp[y] = comps;
		} while (stk[top] != x);
} }
bool solve() {
	int cnt = n + n + 1;
	stp = top = comps = 0;
	fill(dfn, dfn + cnt, 0);
	fill(comp, comp + cnt, 0);
	for (int i = 0; i < cnt; ++i) if (!dfn[i]) tarjan(i);
	for (int i = 0; i < n; ++i) {
		if (comp[i << 1] == comp[i << 1 | 1]) return false;
		answer[i] = (comp[i << 1 | 1] < comp[i << 1]); }
	return true; }
