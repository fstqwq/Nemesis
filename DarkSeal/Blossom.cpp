struct Blossom { // source from lbn187
	int n, m, h, t, W, tot, fir[N], la[M], ne[M], F[N], mat[N], pre[N], tp[N], q[N], vs[N];
	void ins(int x, int y) {
		la[++tot] = y;
		ne[tot] = fir[x];
		fir[x] = tot;
	}
	void in(int x, int y) {
		n = x, m = y;
		W = tot = 0;
		fill(fir, fir + n + 1, 0);
		for (int i = 1; i <= m; i++) {
			scanf("%d%d", &x, &y), ins(x, y), ins(y, x);
		}
	}
	int getf(int x) {
		return F[x] ? F[x] = getf(F[x]) : x;
	}
	int lca(int u, int v) {
		for (++W; ; u = pre[mat[u]], swap(u, v))
			if (vs[u = getf(u)] == W) return u;
			else vs[u] = u ? W : 0;
	}
	void aug(int u, int v) {
		for (int w; u; v = pre[u = w]) w = mat[v], mat[mat[u] = v] = u;
	}
	void blo(int u, int v, int f) {
		for (int w; getf(u) ^ f; u = pre[v = w]) pre[u] = v, F[u] ? 0 : F[u] = f, F[w = mat[u]] ? 0 : F[w] = f, tp[w] ^ 1 ? 0 : tp[q[++t] = w] = -1;
	}
	int bfs(int u) {
		for (int i = 1; i <= n; i++) tp[i] = F[i] = 0;
		for (--tp[q[h = t = 1] = u]; h <= t; u = q[++h])
			for (int i = fir[u], x, E; i; i = ne[i]) if (!tp[E = la[i]]) {
					if (!mat[E]) return aug(E, u), 1;
					pre[E] = u, ++tp[E], --tp[q[++t] = mat[E]];
				}
				else if (tp[E] ^ 1 && getf(u)^getf(E)) blo(u, E, x = lca(u, E)), blo(E, u, x);
		return 0;
	}
	int solve() {
		int ans = 0;
		for (int i = 1; i <= n; i++) mat[i] ? 0 : ans += bfs(i);
		return ans;
	}
	void out() {
		for (int i = 1; i <= n; i++) printf("%d%c", mat[i], i == n ? '\n' : ' ');
	}
} G;

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	G.in(n, m);
	printf("%d\n", G.solve());
	G.out();
}

