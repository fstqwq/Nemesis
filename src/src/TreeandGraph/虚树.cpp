int one = 0, top = 0;
for (auto i : q) one |= i == 1;
if (!one) q.push_back(1);
sort(q.begin(), q.end(), [](auto u, auto v) {
	return dfn[u] < dfn[v]; });
for (auto x : q) {
	used.push_back(x);
	if (top == 0) stk[++top] = x;
	else {
		int lca = LCA(stk[top], x);
		used.push_back(lca);
		while (top > 1 && dep[lca] < dep[stk[top - 1]]) {
			h[stk[top - 1]].push_back(stk[top]);
			--top; }
		if (dep[lca] < dep[stk[top]])
			h[lca].push_back(stk[top--]);
		if (stk[top] != lca)
			stk[++top] = lca;
		stk[++top] = x; } }
while (--top) // assert (top)
	h[stk[top]].push_back(stk[top + 1]);
LL ans = solve(1, 0);
for (auto i : used) h[i].clear();