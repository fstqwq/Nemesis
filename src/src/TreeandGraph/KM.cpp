struct KM {
int n, nl, nr;
T g[N][N], lx[N], ly[N], slack[N];
int mx[N], my[N], visx[N], visy[N], pre[N], q[N], ql, qr;
int check(int i) {
	visy[i] = 1;
	if (~my[i]) {
		q[qr++] = my[i], visx[my[i]] = 1;
		return 0; }
	while (~i) my[i] = pre[i], swap(i, mx[pre[i]]);
	return 1; }
void bfs(int s) {
	ql = 0, qr = 1;
	q[ql] = s, visx[s] = 1;
	for (T d; ; ) {
		while (ql < qr)
		for (int v = 0, u = q[ql++]; v < n; v++)
		if (!visy[v] && slack[v] >= (d=lx[u]+ly[v]-g[u][v])) {
			pre[v] = u;
			if (d) slack[v] = d; else if (check(v)) return;
		} d = INF;
		for (int i = 0; i < n; i++)
			if (!visy[i]) d = min(d, slack[i]);
		for (int i = 0; i < n; i++) {
			if (visy[i]) ly[i] += d; else slack[i] -= d;
			if (visx[i]) lx[i] -= d; }
		for (int i = 0; i < n; i++)
			if (!visy[i] && !slack[i] && check(i)) return;
	} }
void solve() {
	n = max(nl, nr); // always compute a full matching
	fill(pre, pre + n, -1); 
	fill(mx, mx + n, -1); fill(my, my + n, -1);
	fill(ly, ly + n, 0);
	for (int i = 0; i < n; i++)
		lx[i] = *max_element(g[i], g[i] + n);
	for (int i = 0; i < n; i++) {
		fill(slack, slack + n, INF);
		fill(visx, visx + n, 0); fill(visy, visy + n, 0);
		bfs(i); }
	for (int i = 0; i < n; i++)
		if (g[i][mx[i]] == 0) mx[i] = -1;
} } km;