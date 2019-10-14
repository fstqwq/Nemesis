void dfs(int u) {
	dep[u] = dep[fa[u][0]] + 1, stk.push(u);
	for(int i = 1; i < logn; i++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for(int i = 0; i < vec[u].size(); i++) {
		int v = vec[u][i];
		if(v == fa[u][0]) continue;
		fa[v][0] = u, dfs(v), size[u] += size[v];
		if(size[u] >= bufsize) {
			++bcnt;
			while(stk.top() != u) {
				block[stk.top()] = bcnt;
				stk.pop();
			}
			size[u] = 0;
		}
	}
	size[u]++;
}
void prework() {
	dfs(1), ++bcnt;
	while(!stk.empty()) block[stk.top()] = bcnt, stk.pop();
}
void rev(int u) {
	now -= (cnt[val[u]] > 0);
	if(used[u]) cnt[val[u]]--, used[u] = false;
	else cnt[val[u]]++, used[u] = true;
	now += (cnt[val[u]] > 0);
}
void move(int &x,int y,int z) {
	int fwd = y;
	rev(getlca(x, z)), rev(getlca(y, z));
	while(x != y) {
		if(dep[x] < dep[y]) std::swap(x, y);
		rev(x), x = fa[x][0];
	}
	x = fwd;
}
void solve() {
	int L = 1, R = 1;
	std::sort(query + 1, query + m + 1);	
	rev(1);
	for(int i = 1; i <= m; i++) {
		int l = query[i].u, r = query[i].v;
		move(L, l, R), move(R, r, L);
		ans[query[i].t] = now;
	}
}
