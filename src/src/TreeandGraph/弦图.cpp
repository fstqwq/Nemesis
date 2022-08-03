vector <int> L[N];
int seq[N], lab[N], col[N], id[N], vis[N];
void mcs() {
	for (int i = 0; i < n; i++) L[i].clear();
	fill(lab + 1, lab + n + 1, 0);
	fill(id + 1, id + n + 1, 0);
	for (int i = 1; i <= n; i++) L[0].push_back(i);
	int top = 0;
	for (int k = n; k; k--) {
		int x = -1;
		for ( ; ; ) {
			if (L[top].empty()) top --;
			else {
				x = L[top].back(), L[top].pop_back();
				if (lab[x] == top) break;
			}
		}
		seq[k] = x; id[x] = k;
		for (auto v : E[x]) {
			if (!id[v]) {
				L[++lab[v]].push_back(v);
				top = max(top, lab[v]);
			} } } }
bool check() {
	fill(vis + 1, vis + n + 1, 0);
	for (int i = n; i; i--) {
		int x = seq[i];
		vector <int> to;
		for (auto v : E[x])
			if (id[v] > i) to.push_back(v);
		if (to.empty()) continue;
		int w = to.front();
		for (auto v : to) if (id[v] < id[w]) w = v;
		for (auto v : E[w]) vis[v] = i;
		for (auto v : to)
			if (v != w && vis[v] != i) return false;
	} return true; }
void color() {
	fill(vis + 1, vis + n + 1, 0);
	for (int i = n; i; i--) {
		int x = seq[i];
		for (auto v : E[x]) vis[col[v]] = x;
		for (int c = 1; !col[x]; c++)
			if (vis[c] != x) col[x] = c;
	} }
