vector<int> prec[N], succ[N];
vector<int> ord;
int stamp, vis[N];
int num[N];
int fa[N];
void dfs(int u) {
	vis[u] = stamp;
	num[u] = ord.size();
	ord.push_back(u);
	for (int i = 0; i < (int)succ[u].size(); ++i) {
		int v = succ[u][i];
		if (vis[v] != stamp) {
			fa[v] = u;
			dfs(v);
		}
	}
}
int fs[N], mins[N], dom[N], sem[N];
int find(int u) {
	if (u != fs[u]) {
		int v = fs[u];
		fs[u] = find(fs[u]);
		if (mins[v] != -1 && num[sem[mins[v]]] < num[sem[mins[u]]]) {
			mins[u] = mins[v];
		}
	}
	return fs[u];
}
void merge(int u, int v) { fs[u] = v; }
vector<int> buf[N];
int buf2[N];
void mark(int source) {
	ord.clear();
	++stamp;
	dfs(source);
	for (int i = 0; i < (int)ord.size(); ++i) {
		int u = ord[i];
		fs[u] = u, mins[u] = -1, buf2[u] = -1;
	}
	for (int i = (int)ord.size() - 1; i > 0; --i) {
		int u = ord[i], p = fa[u];
		sem[u] = p;
		for (int j = 0; j < (int)prec[u].size(); ++j) {
			int v = prec[u][j];
			if (use[v] != stamp) continue;
			if (num[v] > num[u]) {
				find(v); v = sem[mins[v]];
			}
			if (num[v] < num[sem[u]]) {
				sem[u] = v;
			}
		}
		buf[sem[u]].push_back(u);
		mins[u] = u;
		merge(u, p);
		while (buf[p].size()) {
			int v = buf[p].back();
			buf[p].pop_back();
			find(v);
			if (sem[v] == sem[mins[v]]) {
				dom[v] = sem[v];
			} else {
				buf2[v] = mins[v];
			}
		}
	}
	dom[ord[0]] = ord[0];
	for (int i = 0; i < (int)ord.size(); ++i) {
		int u = ord[i];
		if (~buf2[u]) {
			dom[u] = dom[buf2[u]];
		}
	}
}
