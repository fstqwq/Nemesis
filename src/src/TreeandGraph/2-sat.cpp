int stp, comps, top;//清点清边要两倍
int dfn[N], low[N], comp[N], stk[N];
void add(int x, int a, int y, int b) {
//取$X_a$则必须取$Y_b$,则$X_a$向$Y_b$连边
//注意连边是对称的,即,此时实际上$X_b$也必须向$Y_a$连边.
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
bool answer[N];
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
