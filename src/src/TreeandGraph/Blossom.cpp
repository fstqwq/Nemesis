int n, m, l, r, u, v, res, q[N], p[N], h[N], fa[N], col[N];
vector<int> G[N];
inline int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}
int lca(int u, int v) {
	static int fl[N], tim; ++tim;
	while (fl[u] != tim) {
		if (u) fl[u] = tim, u = find(p[h[u]]);
		swap(u, v);
	} return u; }
void blossom(int u, int v, int t) {
	while (find(u) != t) {
		p[u] = v, v = h[u], fa[u] = fa[v] = t;
		if (col[v] == 1) col[v] = 2, q[++r] = v;
		u = p[v]; } }
bool match(int rt) {
	for (int i = 1; i <= n; i++) fa[i] = i, col[i] = 0;
	l = r = 1, q[1] = rt, col[rt] = 2;
	while (l <= r) {
		u = q[l++];
		for (int v : G[u]) if (!col[v]) {
			col[v] = 1, col[h[v]] = 2, p[v] = u, q[++r] = h[v];
			if (!h[v]) {
				while (u) u = h[p[v]], h[v] = p[v], h[p[v]] = v, v = u;
				return true;
			}
		} else if (col[v] == 2) {
			int t = lca(u, v); blossom(u, v, t), blossom(v, u, t);
		}
	} return false;
} // for(int i=1;i<=n;i++)if(!h[i]&&match(i))++res;